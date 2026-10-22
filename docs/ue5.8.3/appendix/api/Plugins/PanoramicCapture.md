# Plugins / PanoramicCapture

- module root: `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture`
- headers: 5; symbols: 179
- symbol kinds: class=6, delegate=3, enum=3, enumerator=16, externvar=1, function=8, member=104, prototype=37, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, ImageWrapper, InputCore, MessageLog, RHI, RenderCore, Slate, UnrealEd

### `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Private/SceneCapturer.h` (Private)


#### struct `FPostProcessVolumeData`  
`struct FPostProcessVolumeData`  
_L27-35_
- reflection: `USTRUCT()`
- L32 _public member_ `TObjectPtr<APostProcessVolume> Object;` — `UPROPERTY()`
- L34 _public member_ `bool WasEnabled;`

#### enum `ECaptureStep`  
`enum class ECaptureStep : uint8`  
_L37-45_
- L39 _public enumerator_ `Reset`
- L40 _public enumerator_ `SetStartPosition`
- L41 _public enumerator_ `SetPosition`
- L42 _public enumerator_ `Read`
- L43 _public enumerator_ `Pause`
- L44 _public enumerator_ `Unpause`

#### enum `ERenderPass`  
`enum class ERenderPass : uint8`  
_L47-56_
- L49 _public enumerator_ `WorldNormal`
- L50 _public enumerator_ `AO`
- L51 _public enumerator_ `BaseColor`
- L52 _public enumerator_ `Metallic`
- L53 _public enumerator_ `Roughness`
- L54 _public enumerator_ `FinalColor`
- L55 _public enumerator_ `SceneDepth`

#### class `USceneCapturer`  
`class USceneCapturer : public UObject , public FTickableGameObject`  
_L62-244_
- reflection: `UCLASS()`
- inherits: `UObject,FTickableGameObject`
- L70 _public prototype_ `USceneCapturer();`
- L74 _public prototype_ `USceneCapturer(FVTableHelper& Helper);` — NOTE: ikrimae: Adding this ctor hack to fix the 4.8p2 problem with hot reload macros calling empty constructors https://answers.unrealengine.com/questions/228042/48p2-compile-fails-on-class-with-non-default-const.html
- L80 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L82 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L87 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L92 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L94 _public function_ `virtual TStatId GetStatId() const override`
- L101 _public prototype_ `void InitCaptureComponent( USceneCaptureComponent2D* CaptureComponent, float HFov, float VFov);`
- L103 _public prototype_ `void CaptureComponent(int32 CurrentHorizontalStep, int32 CurrentVerticalStep, FString Folder, USceneCaptureComponent2D* CaptureComponent, TArray<FLinearColor>& Atlas);`
- L105 _public prototype_ `void CopyToUnprojAtlas(int32 CurrentHorizontalStep, int32 CurrentVerticalStep, TArray<FLinearColor>& Atlas, TArray<FLinearColor>& SurfaceData);`
- L107 _public prototype_ `TArray<FLinearColor> SaveAtlas(FString Folder, const TArray<FLinearColor>& SurfaceData);`
- L109 _public prototype_ `void SetPositionAndRotation( int32 CurrentHorizontalStep, int32 CurrentVerticalStep, int32 CaptureIndex );`
- L111 _public prototype_ `void SetCaptureComponentRequirements( int32 CaptureIndex);`
- L113 _public prototype_ `void DisableAllPostProcessVolumes();`
- L115 _public prototype_ `void CacheAllPostProcessVolumes();`
- L117 _public prototype_ `void EnablePostProcessVolumes();`
- L119 _public prototype_ `void DisableUnsupportedPostProcesses(USceneCaptureComponent2D* CaptureComponent);`
- L121 _public prototype_ `void RemoveAllBlendables(USceneCaptureComponent2D* CaptureComponent);`
- L123 _public prototype_ `void ValidateParameters();`
- L125 _public prototype_ `void SetInitialState( int32 InStartFrame, int32 InEndFrame, FStereoCaptureDoneDelegate& InStereoCaptureDoneDelegate );`
- L127 _public prototype_ `FString GetCurrentRenderPassName();`
- L129 _public prototype_ `UMaterial* GetCurrentBlendableMaterial();`
- L131 _public prototype_ `void Reset();`
- L135 _public member_ `IImageWrapperModule& ImageWrapperModule;`
- L137 _public member_ `bool bIsTicking;`
- L138 _public member_ `FDateTime OverallStartTime;`
- L139 _public member_ `FDateTime StartTime;`
- L141 _public member_ `FVector StartLocation;`
- L142 _public member_ `FRotator StartRotation;`
- L143 _public member_ `FString Timestamp;`
- L144 _public member_ `int32 StartFrame;`
- L145 _public member_ `int32 EndFrame;`
- L147 _public member_ `ECaptureStep CaptureStep;`
- L148 _public member_ `int32 CurrentFrameCount;`
- L150 _public member_ `int32 CaptureWidth;`
- L151 _public member_ `int32 CaptureHeight;`
- L153 _public member_ `int32 StripWidth;`
- L154 _public member_ `int32 StripHeight;`
- L157 _public member_ `UMaterial* MaterialBlendableWorldNormal;` — blendable materials for each pass
- L158 _public member_ `UMaterial* MaterialBlendableAO;`
- L159 _public member_ `UMaterial* MaterialBlendableBaseColor;`
- L160 _public member_ `UMaterial* MaterialBlendableMetallic;`
- L161 _public member_ `UMaterial* MaterialBlendableRoughness;`
- L164 _public member_ `TArray<ERenderPass> RenderPasses;` — store which passes to do per frame
- L165 _public member_ `int CurrentRenderPassIndex;`
- L169 _public member_ `TArray <FPostProcessVolumeData> PPVolumeArray;` — `UPROPERTY(Transient)` — store post process volumes data
- L171 _public member_ `class APlayerController* CapturePlayerController;`
- L172 _public member_ `class AGameModeBase* CaptureGameMode;`
- L174 _public member_ `TArray<USceneCaptureComponent2D*> LeftEyeCaptureComponents;`
- L175 _public member_ `TArray<USceneCaptureComponent2D*> RightEyeCaptureComponents;`
- L179 _public member_ `TObjectPtr<USceneComponent> CaptureSceneComponent;` — `UPROPERTY(Transient)` — CaptureSceneComponent will be used as parent of capturecomponents to provide world location and rotation.
- L181 _public function_ `bool GetComponentSteps( int32 Step, int32& CurrentHorizontalStep, int32& CurrentVerticalStep )`
- L195 _private member_ `const float hAngIncrement;`
- L196 _private member_ `const float vAngIncrement;`
- L197 _private member_ `float eyeSeparation;`
- L199 _private member_ `float sliceHFov;`
- L200 _private member_ `float sliceVFov;`
- L202 _private member_ `const int32 NumberOfHorizontalSteps;`
- L203 _private member_ `const int32 NumberOfVerticalSteps;`
- L205 _private member_ `int32 UnprojectedAtlasWidth;`
- L206 _private member_ `int32 UnprojectedAtlasHeight;`
- L208 _private member_ `const int32 SphericalAtlasWidth;`
- L209 _private member_ `const int32 SphericalAtlasHeight;`
- L211 _private member_ `int32 CurrentStep;`
- L212 _private member_ `int32 TotalSteps;`
- L214 _private member_ `TArray<FLinearColor> UnprojectedLeftEyeAtlas;`
- L215 _private member_ `TArray<FLinearColor> UnprojectedRightEyeAtlas;`
- L217 _private member_ `const bool bForceAlpha;`
- L218 _private member_ `const bool bEnableBilerp;`
- L219 _private member_ `const int32 SSMethod;`
- L220 _private member_ `const bool bOverrideInitialYaw;`
- L221 _private member_ `const float ForcedInitialYaw;`
- L222 _private member_ `const FString OutputDir;`
- L223 _private member_ `bool ErrorFound;`
- L225 _private member_ `const int32 UseCameraRotation;` — UseCameraRotation will be used for gathering selected rotational axis of user's camera.
- L227 _private member_ `bool dbgMatchCaptureSliceFovToAtlasSliceFov;`
- L228 _private member_ `bool dbgDisableOffsetRotation;`
- L229 _private member_ `FString FrameDescriptors;`
- L231 _private member_ `const int32 OutputBitDepth;`
- L232 _private member_ `const bool bOutputSceneDepth;`
- L233 _private member_ `const bool bOutputFinalColor;`
- L234 _private member_ `const bool bOutputWorldNormal;`
- L235 _private member_ `const bool bOutputRoughness;`
- L236 _private member_ `const bool bOutputMetallic;`
- L237 _private member_ `const bool bOutputBaseColor;`
- L238 _private member_ `const bool bOutputAmbientOcclusion;`
- L241 _private member_ `const bool bMonoscopicMode;` — output in mono (1 eye)
- L243 _private member_ `FStereoCaptureDoneDelegate StereoCaptureDoneDelegate;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogStereoPanorama, Log, All );`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogStereoPanorama, Log, All );`
- L17 _delegate_ `DECLARE_STATS_GROUP( TEXT( "SP" ), STATGROUP_SP, STATCAT_Advanced`
- L24 _externvar_ `extern const FName StereoPanoramaLogName;`
- L58 _delegate_ `DECLARE_DELEGATE_TwoParams(FStereoCaptureDoneDelegate, const TArray<FLinearColor>&, const TArray<FLinearColor>&);`
- L58 _prototype_ `DECLARE_DELEGATE_TwoParams(FStereoCaptureDoneDelegate, const TArray<FLinearColor>&, const TArray<FLinearColor>&);`

### `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Private/StereoPanoramaManager.h` (Private)


#### class `FStereoPanoramaManager`  
`class FStereoPanoramaManager`  
_L7-91_
- L11 _public function_ `FStereoPanoramaManager() : SceneCapturer(nullptr) , PanoramicScreenshotCommand( TEXT("SP.PanoramicScreenshot"), *NSLOCTEXT("StereoPanorama", "CommandText_ScreenShot", "Takes a panoramic screenshot").ToString(), FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicScreenshot)) , PanoramicMovieCommand( TEXT("SP.PanoramicMovie"), *NSLOCTEXT("StereoPanorama", "CommandText_MovieCapture", "Takes a sequence of panoramic screenshots").ToString(), FConsoleCommandWithWorldAndArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicMovie)) , PanoramicQualityCommand( TEXT("SP.PanoramicQuality"), *NSLOCTEXT("StereoPanorama", "CommandText_Quality", "Sets the quality of the panoramic screenshot to 'preview | average | improved'").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicQuality)) , PanoramicPauseCommand( TEXT("SP.TogglePause"), *NSLOCTEXT("StereoPanorama", "CommandText_PauseGame", "Toggles Pausing/Unpausing of the game through StereoPanorama Plugin").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw(this, &FStereoPanoramaManager::PanoramicTogglePause))`
- L33 _public prototype_ `void Cleanup();`
- L34 _public prototype_ `bool ValidateRendererState() const;`
- L37 _public prototype_ `bool CheckPreviousJobState() const;` — To check previous job is finished.
- L39 _public prototype_ `void PanoramicScreenshot(const TArray<FString>& Args, UWorld* World);`
- L40 _public prototype_ `void PanoramicScreenshot(const int32 InStartFrame, const int32 InEndFrame, FStereoCaptureDoneDelegate& InStereoCaptureDoneDelegate, UWorld* World);`
- L41 _public prototype_ `void PanoramicMovie(const TArray<FString>& Args, UWorld* World);`
- L42 _public prototype_ `void PanoramicQuality(const TArray<FString>& Args);`
- L43 _public prototype_ `void PanoramicTogglePause(const TArray<FString>& Args);`
- L47 _public member_ `static IConsoleVariable* HorizontalAngularIncrement;`
- L48 _public member_ `static IConsoleVariable* VerticalAngularIncrement;`
- L49 _public member_ `static IConsoleVariable* StepCaptureWidth;`
- L50 _public member_ `static IConsoleVariable* EyeSeparation;`
- L51 _public member_ `static IConsoleVariable* ForceAlpha;`
- L52 _public member_ `static IConsoleVariable* GenerateDebugImages;`
- L53 _public member_ `static IConsoleVariable* ConcurrentCaptures;`
- L54 _public member_ `static IConsoleVariable* CaptureHorizontalFOV;`
- L55 _public member_ `static IConsoleVariable* CaptureSlicePixelWidth;`
- L56 _public member_ `static IConsoleVariable* EnableBilerp;`
- L57 _public member_ `static IConsoleVariable* SuperSamplingMethod;`
- L58 _public member_ `static IConsoleVariable* OutputDir;`
- L59 _public member_ `static IConsoleVariable* ShouldOverrideInitialYaw;`
- L60 _public member_ `static IConsoleVariable* ForcedInitialYaw;`
- L61 _public member_ `static IConsoleVariable* FadeStereoToZeroAtSides;`
- L63 _public member_ `static IConsoleVariable* OutputFinalColor;`
- L64 _public member_ `static IConsoleVariable* OutputSceneDepth;`
- L65 _public member_ `static IConsoleVariable* OutputWorldNormal;`
- L66 _public member_ `static IConsoleVariable* OutputRoughness;`
- L67 _public member_ `static IConsoleVariable* OutputMetalic;`
- L68 _public member_ `static IConsoleVariable* OutputBaseColor;`
- L69 _public member_ `static IConsoleVariable* OutputAmbientOcclusion;`
- L70 _public member_ `static IConsoleVariable* OutputBitDepth;`
- L73 _public member_ `static IConsoleVariable* MonoscopicMode;` — Output in mono
- L76 _public member_ `static IConsoleVariable* UseCameraRotation;` — This will use camera's rotation. Use param by adding desired axis. Pitch=1 Yaw=2 Roll=4, All axis is 7 (=1+2+4)
- L81 _private member_ `class USceneCapturer* SceneCapturer;` — The scene capturer object.
- L85 _private prototype_ `void EndPIE(bool bIsSimulating);`
- L87 _private member_ `FAutoConsoleCommandWithWorldAndArgs PanoramicScreenshotCommand;`
- L88 _private member_ `FAutoConsoleCommandWithWorldAndArgs PanoramicMovieCommand;`
- L89 _private member_ `FAutoConsoleCommand PanoramicQualityCommand;`
- L90 _private member_ `FAutoConsoleCommand PanoramicPauseCommand;`

### `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Private/StereoStaticMeshComponent.h` (Private)


#### enum `ESPStereoCameraLayer`  
`enum class ESPStereoCameraLayer : uint8`  
_L11-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `LeftEye`
- L14 _public enumerator_ `RightEye`
- L15 _public enumerator_ `BothEyes`

#### class `UStereoStaticMeshComponent`  
`class UStereoStaticMeshComponent : public UStaticMeshComponent`  
_L23-35_
- reflection: `UCLASS(ClassGroup = (Rendering, Common), hidecategories = (Object, Activation, "Components|Activation"), ShowCategories = (Mobility), editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UStaticMeshComponent`
- L31 _public member_ `ESPStereoCameraLayer EyeToRender;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite)`
- L33 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`

### `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Public/StereoCapturePawn.h` (Public)


#### class `FStereoCaptureDoneAction`  
`class FStereoCaptureDoneAction : public FPendingLatentAction`  
_L13-45_
- inherits: `FPendingLatentAction`
- L18 _public member_ `FName ExecutionFunction;`
- L19 _public member_ `int32 OutputLink;`
- L20 _public member_ `FWeakObjectPtr CallbackTarget;`
- L21 _public member_ `bool IsStereoCaptureDone;`
- L25 _public function_ `FStereoCaptureDoneAction(const FLatentActionInfo& LatentInfo) : ExecutionFunction(LatentInfo.ExecutionFunction) , OutputLink(LatentInfo.Linkage) , CallbackTarget(LatentInfo.CallbackTarget) , IsStereoCaptureDone(false)`
- L33 _public function_ `virtual void UpdateOperation(FLatentResponse& Response)`
- L40 _public function_ `virtual FString GetDescription() const override` — Returns a human readable description of the latent operation's current state

#### class `AStereoCapturePawn`  
`class AStereoCapturePawn : public ADefaultPawn`  
_L52-72_
- reflection: `UCLASS(config = Game, Blueprintable, BlueprintType)`
- inherits: `ADefaultPawn`
- L60 _public prototype_ `void UpdateStereoAtlas(UObject* WorldContextObject, struct FLatentActionInfo LatentInfo);` — `UFUNCTION(BlueprintCallable, Category = "Pawn", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo"))`
- L63 _public member_ `TObjectPtr<UTexture2D> LeftEyeAtlas;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)`
- L66 _public member_ `TObjectPtr<UTexture2D> RightEyeAtlas;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn)`
- L69 _public member_ `FStereoCaptureDoneAction* StereoCaptureDoneAction;`
- L71 _public prototype_ `void CopyAtlasDataToTextures(const TArray<FLinearColor>& LeftEyeAtlasData, const TArray<FLinearColor>& RightEyeAtlasData);`

### `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Public/StereoPanorama.h` (Public)


#### class `FStereoPanoramaModule`  
`class FStereoPanoramaModule : public IModuleInterface`  
_L13-26_
- inherits: `IModuleInterface`
- desc: Implements the StereoPanorama module.
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `static TSharedPtr<FStereoPanoramaManager> Get();`
