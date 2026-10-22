# Plugins / AvalancheFunctionalTest

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheFunctionalTest`
- headers: 1; symbols: 32
- symbol kinds: class=1, function=2, member=18, prototype=10, struct=1
- PrivateDependencyModuleNames: LevelEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Avalanche, Core, CoreUObject, Engine, FunctionalTesting, Niagara, RenderCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheFunctionalTest/Public/ScreenshotFunctionalTestAvalanche.h` (Public)


#### class `AScreenshotFunctionalTestAvalanche`  
`class AScreenshotFunctionalTestAvalanche : public AScreenshotFunctionalTest`  
_L41-158_
- reflection: `UCLASS(Blueprintable, MinimalAPI, DisplayName = "Screenshot Functional Test Motion Design")`
- inherits: `AScreenshotFunctionalTest`
- desc: Screenshot functional test optimized for Avalanche (Motion Design) levels. This class works around two critical issues that prevent regular screenshot tests from working correctly in Avalanche/Motion Design levels: 1. CVar Priority Conflicts: - Avalanche's custom viewport client (UAvaGameViewportClient) sets rendering CVars at Constructor/Code priority levels - Base AScreenshotFunctionalTest uses SetWithCurrentPriority() which cannot override Constructor-level CVars, causing 12 CVars to fail with priority errors - This class uses ECVF_SetByConsole priority to successfully override during test 2. PIE Screenshot Delegate Mismatch: - PIE uses FEditorViewportClient::ProcessScreenShots() which fires the static FScreenshotRequest::OnScreenshotCaptured() delegate - Base class only registers to the instance UGameViewportClient::OnScreenshotCaptured() - This class registers to BOTH delegates to support PIE and standalone execution Usage: Use this class instead of AScreenshotFunctionalTest when creating screenshot tests for Avalanche/Motion Design levels. It's only available when the Avalanche plugin is enabled. Note: CVars are NOT restored after test completion to avoid priority stickiness issues. Test-friendly values (AA=0, ScreenPercentage=100, MotionBlur=0) remain in place.
- L46 _public prototype_ `AScreenshotFunctionalTestAvalanche(const FObjectInitializer& ObjectInitializer);`
- L55 _public member_ `bool bWaitForActorReady = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot|Actor Readiness", meta = (DisplayName = "Wait For Actor Ready"))` — If enabled, the test will wait for the specified actor to be fully initialized before taking the screenshot, instead of relying on fixed time/frame delays. This ensures actors with Niagara systems, async loading, or complex initialization are fully ready before screenshot capture.
- L64 _public member_ `TSoftObjectPtr<AActor> ActorToWaitFor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot|Actor Readiness", meta = (EditCondition = "bWaitForActorReady", DisplayName = "Actor To Wait For"))` — The actor to wait for before taking the screenshot. The test will check if this actor and all its components (especially Niagara systems) are fully initialized before proceeding. Only used when bWaitForActorReady is enabled.
- L72 _public member_ `float MaxActorWaitTime = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot|Actor Readiness", meta = (EditCondition = "bWaitForActorReady", ClampMin = "0.1", ClampMax = "30.0", UIMin = "0.5", UIMax = "10.0"))` — Maximum time to wait for the actor to be ready (in seconds). If the actor is not ready within this time, the test will proceed anyway to avoid hanging indefinitely.
- L76 _protected prototype_ `virtual void PrepareTest() override;` — Override to set up CVars with explicit priority before base class setup
- L79 _protected prototype_ `virtual bool IsReady_Implementation() override;` — Override to check if actor is ready before proceeding
- L82 _protected prototype_ `virtual void RequestScreenshot() override;` — Override to register to both instance and static screenshot delegates for PIE support
- L83 _protected prototype_ `virtual void OnScreenShotCaptured(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData) override;`
- L87 _protected prototype_ `virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;` — Override to root NiagaraSystem assets before test teardown, preventing GC from freeing them while async Niagara compilation tasks still hold TWeakObjectPtr refs.
- L90 _protected prototype_ `virtual void BeginDestroy() override;` — Override to unroot NiagaraSystem assets once the test actor is being destroyed.
- L101 _private prototype_ `bool IsActorFullyInitialized(AActor* Actor) const;` — Checks if the specified actor is fully initialized and ready for screenshot. Returns true if: - Actor has completed BeginPlay - All Niagara components are active and have valid system instances - All primitive components are registered - Niagara systems have had time to spawn particles (at least 0.1s age)
- L104 _private member_ `float ActorWaitStartTime = 0.0f;` — Time when PrepareTest() was called, used to enforce MaxActorWaitTime
- L108 _private member_ `TArray<TObjectPtr<UNiagaraSystem>> RootedNiagaraSystems;` — NiagaraSystem assets temporarily rooted in FinishTest() to outlive async compilation tasks that may fire during test teardown. Unrooted in BeginDestroy().
- L143 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> AntiAliasingOverride;` — CVar overrides managed with explicit priority
- L144 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> AutoExposureOverride;`
- L145 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> MotionBlurOverride;`
- L146 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> MotionBlurQualityOverride;`
- L147 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> ContactShadowsOverride;`
- L148 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> ScreenSpaceReflectionQualityOverride;`
- L149 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> EyeAdaptationQualityOverride;`
- L150 _private member_ `FScreenshotTestAvalancheCVarOverride<float> TonemapperGammaOverride;`
- L151 _private member_ `FScreenshotTestAvalancheCVarOverride<float> ScreenPercentageOverride;`
- L152 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> DynamicResTestScreenPercentageOverride;`
- L153 _private member_ `FScreenshotTestAvalancheCVarOverride<int32> DynamicResOperationModeOverride;`
- L154 _private member_ `FScreenshotTestAvalancheCVarOverride<float> SecondaryScreenPercentageOverride;`
- L157 _private prototype_ `void ApplyAvalancheRenderingOverrides();` — Apply Avalanche-compatible rendering overrides

#### struct `AScreenshotFunctionalTestAvalanche::FScreenshotTestAvalancheCVarOverride`  
`template<typename T> struct FScreenshotTestAvalancheCVarOverride`  
_L117-140_
- desc: Helper struct to manage CVar overrides at Console priority. Note: CVars are NOT restored after test to avoid priority stickiness issues. Test-friendly values (AA=0, ScreenPercentage=100) are left in place.
- L119 _public prototype_ `FScreenshotTestAvalancheCVarOverride() = default;`
- L121 _public function_ `FScreenshotTestAvalancheCVarOverride(const FString& InCVarName) : CVarName(InCVarName)`
- L126 _public function_ `void SetOverride(T NewValue)`
- L139 _private member_ `FString CVarName;`
