# Plugins / MetaHumanFaceAnimationSolver

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolver`
- headers: 2; symbols: 43
- symbol kinds: class=2, delegate=1, enum=2, enumerator=5, macro=1, member=10, prototype=22
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, MetaHumanConfig, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolver/Private/MetaHumanFaceAnimationSolverStyle.h` (Private)


#### class `FMetaHumanFaceAnimationSolverStyle`  
`class FMetaHumanFaceAnimationSolverStyle : public FSlateStyleSet`  
_L9-26_
- inherits: `FSlateStyleSet`
- desc: A Style set for MetaHuman Face Animation Solver asset
- L13 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FMetaHumanFaceAnimationSolverStyle& Get();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L23 _private prototype_ `FMetaHumanFaceAnimationSolverStyle();`
- L25 _private member_ `static FName StyleName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceAnimationSolver/Public/MetaHumanFaceAnimationSolver.h` (Public)


#### enum `EDepthMapInfluenceValue`  
`enum class EDepthMapInfluenceValue : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Low`
- L17 _public enumerator_ `High`

#### enum `ETeethMode`  
`enum class ETeethMode : uint8`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `TrackingPoints = 0`
- L24 _public enumerator_ `Estimated`

#### class `UMetaHumanFaceAnimationSolver`  
`class UMetaHumanFaceAnimationSolver : public UObject`  
_L33-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: MetaHuman Face Animation Solver Holds configuration info used by the solver.
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInternalsChanged) #if WITH_EDITOR` — Delegate called when something changes in the face animation solver that others should know about
- L46 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L52 _public member_ `bool bOverrideDeviceConfig = false;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (InlineEditConditionToggle))`
- L55 _public member_ `TObjectPtr<class UMetaHumanConfig> DeviceConfig;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (EditCondition = "bOverrideDeviceConfig"))`
- L58 _public member_ `bool bOverrideDepthMapInfluence = false;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (InlineEditConditionToggle))`
- L62 _public member_ `EDepthMapInfluenceValue DepthMapInfluence = EDepthMapInfluenceValue::High;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (EditCondition = "bOverrideDepthMapInfluence"))` — The amount by which the depth-map is used to influence the solve result
- L65 _public member_ `bool bOverrideEyeSolveSmoothness = false;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (InlineEditConditionToggle))`
- L69 _public member_ `float EyeSolveSmoothness = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bOverrideEyeSolveSmoothness"))` — The amount of smoothing to be applied to the eye gaze control results
- L72 _public member_ `bool bOverrideTeethMode = false;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (InlineEditConditionToggle))`
- L76 _public member_ `ETeethMode TeethMode = ETeethMode::TrackingPoints;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (EditCondition = "bOverrideTeethMode"))` — Whether teeth tracking points are used or teeth position is estimated
- L78 _public prototype_ `bool CanProcess() const;`
- L79 _public prototype_ `bool SettingsOverridden() const;`
- L80 _public prototype_ `bool GetConfigDisplayName(class UCaptureData* InCaptureData, FString& OutName) const;`
- L82 _public prototype_ `FString GetSolverTemplateData(class UCaptureData* InCaptureData = nullptr) const;`
- L83 _public prototype_ `FString GetSolverConfigData(class UCaptureData* InCaptureData = nullptr) const;`
- L84 _public prototype_ `FString GetSolverDefinitionsData(class UCaptureData* InCaptureData = nullptr) const;`
- L85 _public prototype_ `FString GetSolverHierarchicalDefinitionsData(class UCaptureData* InCaptureData = nullptr) const;`
- L86 _public prototype_ `FString GetSolverHierarchicalDefinitionsPlusChinCompressData(class UCaptureData* InCaptureData = nullptr) const;`
- L87 _public prototype_ `FString GetSolverPCAFromDNAData(class UCaptureData* InCaptureData = nullptr) const;`
- L89 _public prototype_ `FOnInternalsChanged& OnInternalsChanged();`
- L91 _public prototype_ `static FString SetEasyToEditControlConstraints(const FString& InSolverConfigData);`
- L95 _private prototype_ `class UMetaHumanConfig* GetEffectiveConfig(class UCaptureData* InCaptureData) const;`
- L97 _private prototype_ `static FString JsonObjectAsString(TSharedPtr<class FJsonObject> InJsonObject);`
- L99 _private member_ `FOnInternalsChanged OnInternalsChangedDelegate;`
- L101 _private prototype_ `void NotifyInternalsChanged();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANFACEANIMATIONSOLVER_API`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInternalsChanged) #if WITH_EDITOR` — Delegate called when something changes in the face animation solver that others should know about
