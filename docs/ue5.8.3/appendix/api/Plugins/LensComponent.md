# Plugins / LensComponent

- module root: `Plugins/VirtualProduction/LensComponent/Source/LensComponent`
- headers: 1; symbols: 118
- symbol kinds: class=1, delegate=1, enum=3, enumerator=11, function=1, macro=1, member=38, prototype=62
- PrivateDependencyModuleNames: CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine
- PublicDependencyModuleNames: LiveLinkComponents, LiveLinkInterface

### `Plugins/VirtualProduction/LensComponent/Source/LensComponent/Public/LensComponent.h` (Public)


#### enum `EFIZEvaluationMode`  
`enum class EFIZEvaluationMode : uint8`  
_L25-37_
- reflection: `UENUM(BlueprintType)`
- desc: Mode that controls where FIZ inputs are sourced from and how they are used to evaluate the LensFile
- L28 _public enumerator_ `UseLiveLink` — Evaluate the Lens File with the latest FIZ data received from LiveLink
- L30 _public enumerator_ `UseCameraSettings` — Evaluate the Lens File using the current FIZ settings of the target camera
- L32 _public enumerator_ `UseRecordedValues` — Evaluate the Lens File using values recorded in a level sequence (set automatically when the sequence is opened)
- L34 _public enumerator_ `Manual` — Evaluate the Lens File using values set directly in the details panel or via BP/scripting
- L36 _public enumerator_ `DoNotEvaluate` — Do not evaluate the Lens File

#### enum `EFilmbackOverrideSource`  
`enum class EFilmbackOverrideSource : uint8`  
_L41-49_
- reflection: `UENUM(BlueprintType)`
- desc: Controls whether this component can override the camera's filmback, and if so, which override to use
- L44 _public enumerator_ `LensFile` — Override the camera's filmback using the sensor dimensions recorded in the LensInfo of the LensFile
- L46 _public enumerator_ `CroppedFilmbackSetting` — Override the camera's filmback using the CroppedFilmback setting below
- L48 _public enumerator_ `DoNotOverride` — Do not override the camera's filmback

#### enum `EDistortionSource`  
`enum class EDistortionSource : uint8`  
_L53-61_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies from where the distortion state information comes
- L56 _public enumerator_ `LensFile` — Distortion state is evaluated using the LensFile
- L58 _public enumerator_ `LiveLinkLensSubject` — Distortion state is inputted directly from a LiveLink subject
- L60 _public enumerator_ `Manual` — Distortion state is set manually by the user using the Distortion State setting below

#### class `ULensComponent`  
`class ULensComponent : public UActorComponent`  
_L65-446_
- reflection: `UCLASS(MinimalAPI, HideCategories=(Tags, Activation, Cooking, AssetUserData, Collision), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Component for applying a post-process lens distortion effect to a CineCameraComponent on the same actor
- L72 _public prototype_ `ULensComponent();`
- L75 _public prototype_ `virtual void OnRegister() override;`
- L76 _public prototype_ `virtual void OnUnregister() override;`
- L77 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L78 _public prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L82 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L83 _public prototype_ `virtual void PostEditImport() override;`
- L84 _public prototype_ `virtual void PostLoad() override;`
- L86 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L89 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L94 _public function_ `FOnLensComponentModelChanged& OnLensComponentModelChanged()` — Returns the delegate that is triggered when the LensModel changes
- L101 _public prototype_ `FLensFilePicker GetLensFilePicker() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the LensFile picker used by this component
- L105 _public prototype_ `ULensFile* GetLensFile() const;` — `UFUNCTION(BlueprintPure, Category="Lens Component")` — Get the LensFile used by this component
- L109 _public prototype_ `void SetLensFilePicker(FLensFilePicker LensFile);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the LensFile picker used by this component
- L113 _public prototype_ `void SetLensFile(ULensFile* LensFile);` — `UFUNCTION(BlueprintCallable, Category="Lens Component")` — Set the LensFile used by this component
- L117 _public prototype_ `EFIZEvaluationMode GetFIZEvaluationMode() const;` — `UFUNCTION(BlueprintPure, Category="Lens Component", meta = (DisplayName = "Get FIZ Evaluation Mode"))` — Get the evaluation mode used to evaluate the LensFile
- L121 _public prototype_ `void SetFIZEvaluationMode(EFIZEvaluationMode Mode);` — `UFUNCTION(BlueprintCallable, Category="Lens Component", meta=(DisplayName="Set FIZ Evaluation Mode"))` — Set the evaluation mode used to evaluate the LensFile
- L125 _public prototype_ `float GetOverscanMultiplier() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the evaluation mode used to evaluate the LensFile
- L129 _public prototype_ `void SetOverscanMultiplier(float Multiplier);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the LensFile used by this component
- L133 _public prototype_ `EFilmbackOverrideSource GetFilmbackOverrideSetting() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the filmback override setting
- L137 _public prototype_ `void SetFilmbackOverrideSetting(EFilmbackOverrideSource Setting);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the filmback override setting
- L141 _public prototype_ `FCameraFilmbackSettings GetCroppedFilmback() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the cropped filmback (only relevant if the filmback override setting is set to use the CroppedFilmback
- L145 _public prototype_ `void SetCroppedFilmback(FCameraFilmbackSettings Filmback);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the cropped filmback (only relevant if the filmback override setting is set to use the CroppedFilmback
- L149 _public prototype_ `bool ShouldApplyNodalOffsetOnTick() const;` — `UFUNCTION(BlueprintPure, Category="Lens Component")` — Returns true if nodal offset will be automatically applied during this component's tick, false otherwise
- L153 _public prototype_ `void SetApplyNodalOffsetOnTick(bool bApplyNodalOffset);` — `UFUNCTION(BlueprintCallable, Category="Lens Component")` — Set whether nodal offset should be automatically applied during this component's tick
- L157 _public prototype_ `EDistortionSource GetDistortionSource() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the distortion source setting
- L161 _public prototype_ `void SetDistortionSource(EDistortionSource Source);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the distortion source setting
- L165 _public prototype_ `bool ShouldApplyDistortion() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Whether distortion should be applied to the target camera
- L169 _public prototype_ `void SetApplyDistortion(bool bApply);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set whether distortion should be applied to the target camera
- L173 _public prototype_ `bool GetOverrideCameraOverscan() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get whether the camera overscan is overriden.
- L177 _public prototype_ `void SetOverrideCameraOverscan(bool bOverride);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set whether the camera overscan should be overriden.
- L181 _public prototype_ `TSubclassOf<ULensModel> GetLensModel() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the current lens model
- L185 _public prototype_ `void SetLensModel(TSubclassOf<ULensModel> Model);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the current lens model
- L189 _public prototype_ `FLensDistortionState GetDistortionState() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the current distortion state
- L193 _public prototype_ `void SetDistortionState(FLensDistortionState State);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the current distortion state
- L197 _public prototype_ `void ClearDistortionState();` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Reset the distortion state to defaults to represent "no distortion"
- L201 _public prototype_ `float GetOriginalFocalLength() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the original (not adjusted for overscan) focal length of the camera
- L205 _public prototype_ `const FLensFileEvaluationInputs& GetLensFileEvaluationInputs() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Get the data used by this component to evaluate the LensFile
- L209 _public prototype_ `void SetLensFileEvaluationInputs(float InFocus, float InZoom);` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Set the data used by this component to evaluate the LensFile
- L213 _public prototype_ `bool WasNodalOffsetAppliedThisTick() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Returns true if nodal offset was applied during the current tick, false otherwise
- L217 _public prototype_ `bool WasDistortionEvaluated() const;` — `UFUNCTION(BlueprintPure, Category = "Lens Component")` — Returns true if distortion was evaluated this tick
- L225 _public prototype_ `void ApplyNodalOffset(USceneComponent* ComponentToOffset, bool bUseManualInputs = false, float ManualFocusInput = 0.0f, float ManualZoomInput = 0.0f);` — `UFUNCTION(BlueprintCallable, Category="Lens Component", meta=(AdvancedDisplay=1))` — Manually apply nodal offset to the specified component. If bUseManualInputs is true, the input Focus and Zoom values will be used to evaluate the LensFile . If bUseManualInputs is false, the LensFile be will evaluated based on the Lens Component's evaluation mode.
- L230 _public prototype_ `ULensDistortionModelHandlerBase* GetLensDistortionHandler() const;` — `UFUNCTION(BlueprintCallable, Category = "Lens Component")` — Returns the LensDistortionHandler in use for the current LensModel
- L233 _public prototype_ `void ReapplyNodalOffset();` — Reset the tracked component back to its original tracked pose and reapply nodal offset to it by re-evaluating the LensFile
- L237 _public prototype_ `FDistortionHandlerPicker GetDistortionHandlerPicker() const;` — `UE_DEPRECATED(5.1, "This property is deprecated. Use GetDistortionSource() and SetDistortionSource() instead.")`
- L242 _private prototype_ `void ApplyNodalOffset();` — Evaluate the LensFile for nodal offset (using the current evaluation mode) and apply it to the latest component to offset
- L245 _private prototype_ `void EvaluateFocalLength(UCineCameraComponent* CineCameraComponent);` — Evaluate the focal length from the LensFile and applies the calibrated value to the camera
- L248 _private prototype_ `void InitDefaultCamera();` — If TargetCameraComponent is not set, initialize it to the first CineCameraComponent on the same actor as this component
- L251 _private prototype_ `void CleanupDistortion(UCineCameraComponent* CineCameraComponent);` — Remove the last distortion MID applied to the input CineCameraComponent and reset its FOV to use no overscan
- L254 _private prototype_ `void CreateDistortionHandler();` — Register a new lens distortion handler with the camera calibration subsystem using the selected lens file
- L257 _private prototype_ `void OnLiveLinkComponentRegistered(ULiveLinkComponentController* LiveLinkComponent);` — Register to the new LiveLink component's callback to be notified when its controller map changes
- L260 _private prototype_ `void OnLensFileModelChanged(const TSubclassOf<ULensModel>& Model);` — Triggered when the LensFile model changes
- L263 _private prototype_ `void ProcessLiveLinkData(const ULiveLinkComponentController* const LiveLinkComponent, const FLiveLinkSubjectFrameData& SubjectData);` — Callback executed when a LiveLink component on the same actor ticks
- L266 _private prototype_ `void UpdateTrackedComponent(const ULiveLinkComponentController* const LiveLinkComponent, const FLiveLinkSubjectFrameData& SubjectData);` — Inspects the subject data and LiveLink transform controller to determine which component (if any) had tracking data applied to it
- L269 _private prototype_ `void UpdateLiveLinkFIZ(const ULiveLinkComponentController* const LiveLinkComponent, const FLiveLinkSubjectFrameData& SubjectData);` — Inspects the subject data and LiveLink camera controller cache the FIZ that was input for the target camera
- L272 _private prototype_ `void UpdateLensFileEvaluationInputs(UCineCameraComponent* CineCameraComponent);` — Updates the focus and zoom inputs that will be used to evaluate the LensFile based on the evaluation mode
- L275 _private prototype_ `void UpdateCameraFilmback(UCineCameraComponent* CineCameraComponent);` — Updates the camera's filmback based on the filmback override settings
- L278 _private prototype_ `float GetDesqueezedSensorWidth(UCineCameraComponent* const CineCameraComponent) const;` — Returns the sensor width of the input CineCamera, factoring in its squeeze factor
- L281 _private prototype_ `FTransform GetOriginalTrackedComponentTransform();` — Get the original transform of the tracked component (rebuilt from the location and rotation vectors)
- L284 _private prototype_ `void SetOriginalTrackedComponentTransform(const FTransform& NewTransform);` — Set the original transform of the tracked component (and also the location and rotation vectors)
- L287 _private prototype_ `void RestoreCameraOverscanDefaults();` — Convenience function to restore the camera overscan defaults.
- L292 _protected member_ `FLensFilePicker LensFilePicker;` — `UPROPERTY(EditAnywhere, Category="Lens File", meta=(ShowOnlyInnerProperties))` — Lens File used to drive distortion with current camera settings
- L296 _protected member_ `EFIZEvaluationMode EvaluationMode = EFIZEvaluationMode::UseLiveLink;` — `UPROPERTY(EditAnywhere, Category="Lens File")` — Specify how the Lens File should be evaluated
- L300 _protected member_ `FComponentReference TargetCameraComponent;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, Category="Lens File", meta=(UseComponentPicker, AllowedClasses="/Script/CinematicCamera.CineCameraComponent"))` — The CineCameraComponent on which to apply the post-process distortion effect
- L304 _protected member_ `FLensFileEvaluationInputs EvalInputs;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Lens File")` — Inputs to LensFile evaluation
- L308 _protected member_ `EDistortionSource DistortionStateSource = EDistortionSource::LensFile;` — `UPROPERTY(EditAnywhere, Category = "Distortion", meta = (DisplayName = "Distortion Source"))` — Specifies from where the distortion state information comes
- L312 _protected member_ `bool bApplyDistortion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = ShouldApplyDistortion, Setter = SetApplyDistortion, Category = "Distortion")` — Whether or not to apply distortion to the target camera component
- L316 _protected member_ `EDistortionRenderingMode DistortionRenderingMode = EDistortionRenderingMode::Preferred;` — `UPROPERTY(EditAnywhere, Category = "Distortion", meta = (EditCondition = "bApplyDistortion"))` — Specifies how the distortion should be rendered in the post-processing pipeline
- L325 _protected member_ `bool bOverrideCameraOverscan = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = GetOverrideCameraOverscan, Setter = SetOverrideCameraOverscan, Category = "Distortion")` — If checked, the camera's overscan value will be driven by the lens component to automatically compensate for distortion. The camera's overscan crop property will also be driven based on the distortion rendering mode: Disabled for Post Process Material or pass after tonemap Enabled for Temporal Super Resolution
- L329 _protected member_ `TSubclassOf<ULensModel> LensModel;` — `UPROPERTY(EditAnywhere, Category = "Distortion", meta = (EditCondition = "DistortionStateSource == EDistortionSource::Manual"))` — The current lens model used for distortion
- L333 _protected member_ `FLensDistortionState DistortionState;` — `UPROPERTY(Interp, EditAnywhere, Category = "Distortion", meta = (EditCondition = "DistortionStateSource == EDistortionSource::Manual"))` — The current distortion state
- L337 _protected member_ `bool bScaleOverscan = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Distortion", meta = (InlineEditConditionToggle))` — Whether to scale the computed overscan by the overscan percentage
- L341 _protected member_ `float OverscanMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Distortion", meta = (EditCondition = "bScaleOverscan", ClampMin = "0.0", ClampMax = "2.0"))` — The percentage of the computed overscan that should be applied to the target camera
- L345 _protected member_ `EFilmbackOverrideSource FilmbackOverride = EFilmbackOverrideSource::DoNotOverride;` — `UPROPERTY(EditAnywhere, Category = "Filmback")` — Controls whether this component can override the camera's filmback, and if so, which override to use
- L349 _protected member_ `FCameraFilmbackSettings CroppedFilmback;` — `UPROPERTY(EditAnywhere, Category = "Filmback", meta=(EditCondition="FilmbackOverride == EFilmbackOverrideSource::CroppedFilmbackSetting"))` — Cropped filmback to use if the filmback override settings are set to use it
- L356 _protected member_ `bool bApplyNodalOffsetOnTick = true;` — `UPROPERTY(EditAnywhere, Category="Nodal Offset")` — If checked, nodal offset will be applied automatically when this component ticks. Set to false if nodal offset needs to be manually applied at some other time (via Blueprints).
- L365 _protected member_ `FVector OriginalTrackedComponentLocation;` — `UPROPERTY(Interp, Category = "Nodal Offset", meta = (EditCondition=false, EditConditionHides))` — Location and Rotation of the TrackedComponent prior to nodal offset being applied Note: These are marked Interp so that they will be recorded in a level sequence to support re-applying nodal offset However, recording of FTransform properties is not currently supported by the transform track recorder. FRotator and FQuat are also not supported by the basic property track recorder, but FVector is, so we use that for both location and rotation.
- L367 _protected member_ `FVector OriginalTrackedComponentRotation;` — `UPROPERTY(Interp, Category = "Nodal Offset", meta = (EditCondition=false, EditConditionHides))`
- L371 _protected member_ `FTransform OriginalTrackedComponentTransform;` — `UPROPERTY(Interp, VisibleAnywhere, AdvancedDisplay, Category = "Nodal Offset")` — Serialized transform of the TrackedComponent prior to nodal offset being applied
- L375 _protected member_ `bool bIsDistortionSetup = false;` — `UPROPERTY()` — Whether a distortion effect is currently being applied to the target camera component
- L379 _protected member_ `float OriginalFocalLength = 35.0f;` — `UPROPERTY()` — Focal length of the target camera before any overscan has been applied
- L383 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> LastDistortionMID = nullptr;` — `UPROPERTY()` — Cached MID last applied to the target camera
- L386 _protected member_ `EDistortionRenderingMode LastAppliedRenderingMode = EDistortionRenderingMode::Preferred;` — Track the last applied rendering mode to detect changes when using Preferred mode
- L390 _protected member_ `TObjectPtr<UCineCameraComponent> LastCameraComponent = nullptr;` — `UPROPERTY()` — Cached most recent target camera, used to clean up the old camera when the user changes the target
- L394 _protected member_ `TMap<TSubclassOf<ULensModel>, TObjectPtr<ULensDistortionModelHandlerBase>> LensDistortionHandlerMap;` — `UPROPERTY(Transient)` — Map of lens models to handlers
- L398 _protected member_ `TWeakObjectPtr<USceneComponent> TrackedComponent;` — `UPROPERTY(Transient)` — Scene component that should have nodal offset applied
- L402 _protected member_ `FString TrackedComponentName;` — `UPROPERTY()` — Serialized name of the TrackedComponent, used to determine which component to re-apply nodal offset to in spawnables
- L405 _protected member_ `TWeakObjectPtr<ULensFile> WeakCachedLensFile;` — Weak pointer to the currently set LensFile. Useful to unregister events from the previous LensFile when the asset is swapped out
- L410 _protected member_ `FRotator OriginalCameraRotation_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LensDistortion component no longer tracks the attached camera's original rotation.")` — `UPROPERTY()`
- L414 _protected member_ `FVector OriginalCameraLocation_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The LensDistortion component no longer tracks the attached camera's original location.")` — `UPROPERTY()`
- L419 _protected member_ `FDistortionHandlerPicker DistortionSource_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. The handler picker is no longer used to identify a distortion handler. Use the LensDistortionHandlerMap to get a handler for the current LensModel.")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="This property has been deprecated. Use GetDistortionSource() and SetDistortionSource() instead."))`
- L425 _private member_ `float LiveLinkFocus = 0.0f;` — Latest LiveLink FIZ data, used to evaluate the LensFile
- L426 _private member_ `float LiveLinkIris = 0.0f;`
- L427 _private member_ `float LiveLinkZoom = 0.0f;`
- L430 _private member_ `bool bWasLiveLinkFIZUpdated = false;` — Whether LiveLink FIZ was received this tick
- L433 _private member_ `bool bWasDistortionEvaluated = false;` — Whether distortion was evaluated this tick
- L436 _private member_ `bool bWasNodalOffsetAppliedThisTick = false;` — Whether or not nodal offset was applied to a tracked component this tick
- L439 _private member_ `float LastFocalLength = -1.0f;` — Latest focal length of the target camera, used to track external changes to the original (no overscan applied) focal length
- L442 _private member_ `FOnLensComponentModelChanged OnLensComponentModelChangedDelegate;` — Delegate that is triggered when the LensModel changes
- L445 _private prototype_ `EDistortionRenderingMode GetDistortionRenderingMode() const;` — Resolves the distortion rendering mode to the actual mode that will be used (resolving Preferred if necessary)

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LENSCOMPONENT_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLensComponentModelChanged, const TSubclassOf<ULensModel>&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLensComponentModelChanged, const TSubclassOf<ULensModel>&);`
