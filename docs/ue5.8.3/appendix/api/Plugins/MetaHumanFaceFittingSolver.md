# Plugins / MetaHumanFaceFittingSolver

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolver`
- headers: 2; symbols: 33
- symbol kinds: class=2, delegate=1, macro=1, member=6, prototype=23
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, MetaHumanConfig, MetaHumanFaceAnimationSolver, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolver/Private/MetaHumanFaceFittingSolverStyle.h` (Private)


#### class `FMetaHumanFaceFittingSolverStyle`  
`class FMetaHumanFaceFittingSolverStyle : public FSlateStyleSet`  
_L9-26_
- inherits: `FSlateStyleSet`
- desc: A Style set for MetaHuman Face Fitting Solver asset
- L13 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FMetaHumanFaceFittingSolverStyle& Get();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L23 _private prototype_ `FMetaHumanFaceFittingSolverStyle();`
- L25 _private member_ `static FName StyleName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceFittingSolver/Public/MetaHumanFaceFittingSolver.h` (Public)


#### class `UMetaHumanFaceFittingSolver`  
`class UMetaHumanFaceFittingSolver : public UObject`  
_L19-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: MetaHuman Face Fitting Solver Holds configuration info used by the solver.
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInternalsChanged) #if WITH_EDITOR` — Delegate called when something changes in the face fitting solver data that others should know about
- L32 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L38 _public member_ `bool bOverrideDeviceConfig = false;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (InlineEditConditionToggle))`
- L41 _public member_ `TObjectPtr<class UMetaHumanConfig> DeviceConfig;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (EditCondition = "bOverrideDeviceConfig"))`
- L44 _public member_ `TObjectPtr<class UMetaHumanFaceAnimationSolver> FaceAnimationSolver;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<class UMetaHumanConfig> PredictiveSolver;` — `UPROPERTY(EditAnywhere, Category = "Parameters")`
- L50 _public prototype_ `void LoadFaceFittingSolvers();` — Load the solvers for face fitting
- L53 _public prototype_ `void LoadPredictiveSolver();` — Load Solver that will be trained as part of preparing identity for performance
- L55 _public prototype_ `bool CanProcess() const;`
- L56 _public prototype_ `bool GetConfigDisplayName(class UCaptureData* InCaptureData, FString& OutName) const;`
- L58 _public prototype_ `FString GetFittingTemplateData(class UCaptureData* InCaptureData = nullptr) const;`
- L59 _public prototype_ `FString GetFittingConfigData(class UCaptureData* InCaptureData = nullptr) const;`
- L60 _public prototype_ `FString GetFittingConfigTeethData(class UCaptureData* InCaptureData = nullptr) const;`
- L61 _public prototype_ `FString GetFittingIdentityModelData(class UCaptureData* InCaptureData = nullptr) const;`
- L62 _public prototype_ `FString GetFittingControlsData(class UCaptureData* InCaptureData = nullptr) const;`
- L64 _public prototype_ `TArray<uint8> GetPredictiveGlobalTeethTrainingData() const;`
- L65 _public prototype_ `TArray<uint8> GetPredictiveTrainingData() const;`
- L67 _public prototype_ `FOnInternalsChanged& OnInternalsChanged();`
- L71 _private prototype_ `class UMetaHumanConfig* GetEffectiveConfig(class UCaptureData* InCaptureData) const;`
- L73 _private prototype_ `FString JsonObjectAsString(TSharedPtr<class FJsonObject> InJsonObject) const;`
- L75 _private member_ `FOnInternalsChanged OnInternalsChangedDelegate;`
- L77 _private prototype_ `void NotifyInternalsChanged();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANFACEFITTINGSOLVER_API`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInternalsChanged) #if WITH_EDITOR` — Delegate called when something changes in the face fitting solver data that others should know about
