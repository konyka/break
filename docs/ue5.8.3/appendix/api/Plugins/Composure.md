# Plugins / Composure

- module root: `Plugins/Compositing/Composure/Source/Composure`
- headers: 43; symbols: 777
- symbol kinds: class=62, delegate=9, enum=7, enumerator=27, function=83, macro=3, member=212, namespace=2, prototype=345, struct=18, typedef=9
- PrivateDependencyModuleNames: ActorLayerUtilities, EditorFramework, ImageWriteQueue, MediaAssets, MediaFrameworkUtilities, MovieSceneCapture, RHI, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LensComponent, MediaIOCore, MovieScene, MovieSceneTracks, OpenColorIO, TimeManagement

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingCaptureBase.h` (Public)


#### class `ACompositingCaptureBase`  
`class ACompositingCaptureBase : public ACompositingElement`  
_L20-71_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ACompositingElement`
- desc: Base class for CG Compositing Elements
- L27 _public member_ `TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D = nullptr;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "SceneCapture")` — Component used to generate the scene capture for this CG Layer
- L32 _protected member_ `bool bApplyDistortion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composure|LensDistortion")` — Whether to apply distortion as a post-process effect on this CG Layer
- L36 _protected member_ `FComponentReference LensComponentPicker;` — `UPROPERTY(EditInstanceOnly, Category = "Composure|LensDistortion", meta=(DisplayName="Lens Component", UseComponentPicker, AllowedClasses = "/Script/CameraCalibrationCore.LensComponent", AllowAnyActor))` — A component reference (customized) that allows the user to specify a component that this controller should control
- L40 _protected member_ `float OverscanFactor = 1.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "Composure|LensDistortion")` — Value used to augment the FOV of the scene capture to produce a CG image with enough data to distort
- L44 _protected member_ `float OriginalFocalLength = 35.0f;` — `UPROPERTY(BlueprintReadOnly, Category = "Composure|LensDistortion")` — Focal length of the target camera before any overscan has been applied
- L48 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> LastDistortionMID = nullptr;` — `UPROPERTY()` — Cached distortion MID produced by the Lens Distortion Handler, used to clean up the post-process materials in the case that the the MID changes
- L52 _public prototype_ `ACompositingCaptureBase();` — Default constructor
- L56 _public prototype_ `void UpdateDistortion();` — `UFUNCTION(BlueprintCallable, Category = "Composure|LensDistortion")` — Update the state of the Lens Distortion Data Handler, and updates or removes the Distortion MID from the SceneCaptureComponent's post process materials, depending on whether distortion should be applied
- L59 _public prototype_ `virtual void PostInitProperties() override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L67 _public prototype_ `void SetApplyDistortion(bool bInApplyDistortion);` — Sets whether distortion should be applied or not
- L70 _public prototype_ `void SetLens(ULensComponent* InLens);` — Set the Lens Component this CG layer will use to drive distortion on the scene capture

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElement.h` (Public)


#### enum `ESceneCameraLinkType`  
`enum class ESceneCameraLinkType`  
_L33-38_
- reflection: `UENUM()`
- L35 _public enumerator_ `Inherited`
- L36 _public enumerator_ `Override`
- L37 _public enumerator_ `Unused` — EDITOR-ONLY value, used to clean up the UI and remove needless params from the details UI on elements that don't need a camera

#### enum `EInheritedSourceType`  
`enum class EInheritedSourceType`  
_L41-45_
- reflection: `UENUM()`
- L43 _public enumerator_ `Inherited`
- L44 _public enumerator_ `Override`

#### enum `ETargetUsageFlags`  
`enum class ETargetUsageFlags : uint8`  
_L48-60_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L50 _public enumerator_ `USAGE_None = 0x00`
- L51 _public enumerator_ `USAGE_Input = 1<<0`
- L52 _public enumerator_ `USAGE_Transform = 1<<1`
- L53 _public enumerator_ `USAGE_Output = 1<<2`
- L54 _public enumerator_ `USAGE_Persistent = 1<<5`
- L58 _public enumerator_ `USAGE_Intermediate0 = 1<<3 UMETA(Hidden)` — If a pass is tagged 'intermediate' it is still available to the pass immediately after it. So we ping-pong between intermediate tags, clearing the older one.
- L59 _public enumerator_ `USAGE_Intermediate1 = 1<<4 UMETA(Hidden)`

#### enum `ECompPassConstructionType`  
`enum class ECompPassConstructionType`  
_L64-70_
- reflection: `UENUM()`
- L66 _public enumerator_ `Unknown`
- L67 _public enumerator_ `EditorConstructed`
- L68 _public enumerator_ `BlueprintConstructed`
- L69 _public enumerator_ `CodeConstructed`

#### class `ACompositingElement`  
`class ACompositingElement : public AComposurePipelineBaseActor, public ICompImageColorPickerInterface`  
_L76-523_
- reflection: `UCLASS(BlueprintType, meta=(DisplayName="Empty Comp Shot", ShortTooltip="A simple base actor used to composite multiple render layers together."))`
- inherits: `AComposurePipelineBaseActor,ICompImageColorPickerInterface`
- L82 _public member_ `TObjectPtr<UComposureCompositingTargetComponent> CompositingTarget;` — `UPROPERTY(BlueprintReadOnly, Category = "Composure")`
- L85 _public member_ `TObjectPtr<UComposurePostProcessingPassProxy> PostProcessProxy;` — `UPROPERTY(BlueprintReadOnly, Category = "Composure")`
- L93 _protected member_ `TArray<TObjectPtr<UCompositingElementInput>> Inputs;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, BlueprintGetter = GetInputsList, Category = "Composure|Input", meta=(ShowOnlyInnerProperties))`
- L96 _protected member_ `TArray<TObjectPtr<UCompositingElementTransform>> TransformPasses;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, BlueprintGetter = GetTransformsList, Category = "Composure|Transform/Compositing Passes", meta=(DisplayName = "Transform Passes", ShowOnlyInnerProperties, DisplayAfter="Inputs"))`
- L99 _protected member_ `TArray<TObjectPtr<UCompositingElementOutput>> Outputs;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, BlueprintGetter = GetOutputsList, Category = "Composure|Output", meta = (ShowOnlyInnerProperties))`
- L107 _public member_ `ESceneCameraLinkType CameraSource = ESceneCameraLinkType::Unused;` — `UPROPERTY(EditAnywhere, Category = "Composure|Input")`
- L111 _public member_ `TLazyObjectPtr<ACameraActor> TargetCameraActor_DEPRECATED;` — `UPROPERTY()`
- L115 _public member_ `TWeakObjectPtr<ACameraActor> TargetCameraActorPtr;` — `UPROPERTY(EditInstanceOnly, Category = "Composure|Input", DisplayName = "Target Camera Actor")`
- L121 _public member_ `EInheritedSourceType ResolutionSource = EInheritedSourceType::Inherited;` — `UPROPERTY(EditAnywhere, Category = "Composure|Output")`
- L125 _protected member_ `FIntPoint RenderResolution;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetRenderResolution, BlueprintGetter=GetRenderResolution, Category="Composure|Output")`
- L129 _public member_ `TEnumAsByte<ETextureRenderTargetFormat> RenderFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Composure|Output", AdvancedDisplay)`
- L132 _public member_ `bool bUseSharedTargetPool;` — `UPROPERTY(EditDefaultsOnly, Category = "Composure|Output", AdvancedDisplay)`
- L135 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTransformPassRendered, ACompositingElement*, UTexture*, FName);` — Called when this comp shot element has rendered one of its internal transform passes
- L136 _public member_ `FOnTransformPassRendered OnTransformPassRendered;`
- L139 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinalPassRendered, ACompositingElement*, UTexture*);` — Called when this comp shot element has rendered its final output
- L140 _public member_ `FOnFinalPassRendered OnFinalPassRendered;`
- L147 _private member_ `int32 FreezeFrameMask = 0x00;` — `UPROPERTY(/*BlueprintReadWrite, Category = "Composure",*/ meta = (Bitmask, BitmaskEnum = "/Script/Composure.ETargetUsageFlags"))`
- L152 _public member_ `EInheritedSourceType PreviewTransformSource = EInheritedSourceType::Inherited;` — `UPROPERTY(EditAnywhere, Category = "Composure|Preview")`
- L155 _public member_ `TObjectPtr<UCompositingElementTransform> PreviewTransform;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Composure|Preview")`
- L158 _public member_ `TSubclassOf<UCompositingElementInput> DefaultInputType;` — `UPROPERTY(EditDefaultsOnly, Category = "Composure|Editor")`
- L161 _public member_ `TSubclassOf<UCompositingElementTransform> DefaultTransformType;` — `UPROPERTY(EditDefaultsOnly, Category = "Composure|Editor")`
- L164 _public member_ `TSubclassOf<UCompositingElementOutput> DefaultOutputType;` — `UPROPERTY(EditDefaultsOnly, Category = "Composure|Editor")`
- L166 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompElementConstructed, ACompositingElement*);`
- L167 _public member_ `FOnCompElementConstructed OnConstructed;`
- L169 _public member_ `FCompFreezeFrameController FreezeFrameController;`
- L178 _public prototype_ `void SetElementName(const FName NewName);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Element")` — Rename composure actor's name @param NewName             New name for current composure element.
- L180 _public prototype_ `bool AttachAsChildLayer(ACompositingElement* Child);`
- L182 _public prototype_ `bool DetatchAsChildLayer(ACompositingElement* Child);`
- L189 _public prototype_ `bool IsSubElement() const;` — `UFUNCTION(BlueprintPure, Category = "Composure|Element")` — Determines whether current composure element is a child of another composure element or not. @return bool                Whether current composure actor is a child actor or not.
- L196 _public prototype_ `ACompositingElement* GetElementParent() const;` — `UFUNCTION(BlueprintPure, Category = "Composure|Element")` — Get the parent composure element of current element. @return bool                Whether the function successfully finds the parent or not.
- L203 _public prototype_ `const TArray<ACompositingElement*> GetChildElements() const;` — `UFUNCTION(BlueprintCallable, Category = "Composure|Element")` — Get the first level of current element's child composure elements. @return TArray<ACompositingElement*>   The array containing all the first level children without any grandchildren.
- L206 _public function_ `template<class T> T* AddNewPass(FName PassName, ECompPassConstructionType ConstructedBy = ECompPassConstructionType::CodeConstructed)`
- L211 _public prototype_ `UCompositingElementPass* AddNewPass(FName PassName, TSubclassOf<UCompositingElementPass> PassType, ECompPassConstructionType ConstructedBy = ECompPassConstructionType::CodeConstructed);`
- L218 _public prototype_ `bool RemovePass(UCompositingElementPass* ElementPass);` — Remove a pass from inner pass. This function will not deal with public list shown in the editor. Use DeletePass instead. @param  ElementPass          The pass that is going to be removed. @return bool                 True if deletion operation is successful.
- L220 _public prototype_ `int32 RemovePassesOfType(TSubclassOf<UCompositingElementPass> PassType);`
- L227 _public function_ `float GetOpacity() const` — `UFUNCTION(BlueprintPure, Category = "Composure|Element")` — Return the rendering opacity of current composure actor. @return float                The rendering opacity of current composure element.
- L234 _public prototype_ `void SetOpacity(const float NewOpacity);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Element")` — Set the rendering opacity of current composure actor. @param NewOpacity            The new opacity value set to the composure element.
- L241 _public prototype_ `virtual void SetAutoRunChildrenAndSelf(bool bAutoRunChildAndSelf = true) override;` — When set to false, all children composure actor and current actor's auto-rendering behavior will be disabled. This option is available in the detail panel of the composure element actor as well. @param bAutoRunChildAndSelf    Enable/Disable all the children and itself's rendering. By default, all rendering is enabled.
- L254 _public prototype_ `void SetEditorColorPickingTarget(UTextureRenderTarget2D* PickingTarget);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Editor")` — EDITOR ONLY - Specifies which intermediate target to pick colors from (if left unset, we default to the display image)
- L258 _public prototype_ `void SetEditorColorPickerDisplayImage(UTexture* PickerDisplayImage);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Editor")` — EDITOR ONLY - Specifies an intermediate image to display when picking (if left unset, we default to the final output image)
- L261 _public prototype_ `virtual void OnBeginPreview() override;`
- L262 _public prototype_ `virtual UTexture* GetEditorPreviewImage() override;`
- L263 _public prototype_ `virtual void OnEndPreview() override;`
- L264 _public prototype_ `virtual bool UseImplicitGammaForPreview() const override;`
- L265 _public prototype_ `virtual UTexture* GetColorPickerDisplayImage() override;`
- L266 _public prototype_ `virtual UTextureRenderTarget2D* GetColorPickerTarget() override;`
- L267 _public prototype_ `virtual FCompFreezeFrameController* GetFreezeFrameController() override;`
- L272 _public prototype_ `UTexture* RenderCompElement(bool bCameraCutThisFrame);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure", meta = (CallInEditor = "true"))`
- L279 _public member_ `FDynamicOnTransformPassRendered OnTransformPassRendered_BP;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, DisplayName=OnTransformPassRendered, Category="Composure")` — Called when a transform pass on this element is rendered
- L283 _public member_ `FDynamicOnFinalPassRendered OnFinalPassRendered_BP;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, DisplayName=OnFinalPassRendered, Category="Composure")` — Called when the final output of this element is rendered
- L287 _public function_ `FName GetCompElementName() const` — `UFUNCTION(BlueprintPure, Category = "Composure|Element")` — Return the FName of the composure element object
- L290 _public prototype_ `UTextureRenderTarget2D* RequestNamedRenderTarget(const FName ReferenceName, const float RenderPercentage = 1.f, ETargetUsageFlags UsageTag = ETargetUsageFlags::USAGE_None);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L293 _public prototype_ `bool ReleaseOwnedTarget(UTextureRenderTarget2D* OwnedTarget);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L296 _public prototype_ `UTexture* RenderCompositingMaterial(UPARAM(ref) FCompositingMaterial& CompMaterial, float RenderScale = 1.f, FName ResultLookupName = NAME_None, ETargetUsageFlags UsageTag = ETargetUsageFlags::USAGE_None);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L299 _public prototype_ `UTextureRenderTarget2D* RenderCompositingMaterialToTarget(UPARAM(ref) FCompositingMaterial& CompMaterial, UTextureRenderTarget2D* RenderTarget, FName ResultLookupName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L302 _public prototype_ `ACameraActor* FindTargetCamera() const;` — `UFUNCTION(BlueprintPure, Category = "Composure|Input")`
- L305 _public prototype_ `void SetTargetCamera(ACameraActor* NewCameraActor);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Input")`
- L308 _public prototype_ `void RegisterPassResult(FName ReferenceName, UTexture* PassResult, bool bSetAsLatestRenderResult = true);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L310 _public prototype_ `UTexture* FindNamedRenderResult(FName PassName, bool bSearchSubElements = true);` — `UFUNCTION(BlueprintCallable, Category = "Composure")` — const;
- L312 _public prototype_ `UTexture* GetLatestRenderResult() const;` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L315 _public prototype_ `FIntPoint GetRenderResolution() const;` — `UFUNCTION(BlueprintGetter)`
- L318 _public function_ `void SetRenderResolution(FIntPoint NewResolution)` — `UFUNCTION(BlueprintSetter)`
- L324 _public prototype_ `UCompositingElementInput* FindInputPass(UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementInput> InputType, UTexture*& PassResult, FName OptionalPassName = NAME_N` — `UFUNCTION(BlueprintCallable, Category = "Composure", meta = (DeterminesOutputType = "InputType"))`
- L326 _public prototype_ `UCompositingElementTransform* FindTransformPass(UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementTransform> TransformType, UTexture*& PassResult, FName OptionalPassName = NAME_N` — `UFUNCTION(BlueprintCallable, Category = "Composure", meta = (DeterminesOutputType = "TransformType"))`
- L328 _public prototype_ `UCompositingElementOutput* FindOutputPass(UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementOutput> OutputType, FName OptionalPassName = NAME_N` — `UFUNCTION(BlueprintCallable, Category = "Composure", meta = (DeterminesOutputType = "OutputType"))`
- L331 _public function_ `TArray<UCompositingElementInput*> GetInputsList() const` — `UFUNCTION(BlueprintGetter)`
- L333 _public function_ `TArray<UCompositingElementTransform*> GetTransformsList() const` — `UFUNCTION(BlueprintGetter)`
- L335 _public function_ `TArray<UCompositingElementOutput*> GetOutputsList() const` — `UFUNCTION(BlueprintGetter)`
- L343 _public prototype_ `bool DeletePass(UCompositingElementPass* PassToDelete);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Pass")` — Delete a specific pass. This function deals with the public list where deletion is directly reflected in the editor. @param  PassToDelete			  The pass that will be deleted. @return bool                   Whether the delete operation is successful or not
- L352 _public prototype_ `UCompositingElementInput* CreateNewInputPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementInput> InputT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Pass", meta = (DeterminesOutputType = "InputType"))` — Create a new input pass into the public list which directly shows in the editor. @param  PassName                       The name for the new pass. @param  InputType                      The class type of the created pass. @return CompositingElementInput        The newly created input pass object.
- L361 _public prototype_ `UCompositingElementTransform* CreateNewTransformPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementTransform> TransformT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Pass", meta = (DeterminesOutputType = "TransformType"))` — Create a new Transform pass into the public list which directly shows in the editor. @param  PassName                       The name for the new pass. @param  TransformType                  The class type of the created pass. @return CompositingElementTransform    The newly created transform pass object.
- L370 _public prototype_ `UCompositingElementOutput* CreateNewOutputPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementOutput> OutputT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Pass", meta = (DeterminesOutputType = "OutputType"))` — Create a new Output pass into the public list which directly shows in the editor. @param  PassName                       The name for the new pass. @param  OutputType                     The class type of the created pass. @return CompositingElementOutput       The newly created output pass object.
- L374 _protected prototype_ `UCompositingElementInput* AddNewInputPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementInput> InputT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Input", meta = (DeterminesOutputType = "InputType", BlueprintProtected))`
- L376 _protected prototype_ `UCompositingElementTransform* AddNewTransformPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementTransform> TransformT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Input", meta = (DeterminesOutputType = "TransformType", BlueprintProtected))`
- L378 _protected prototype_ `UCompositingElementOutput* AddNewOutputPass(FName PassName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UCompositingElementOutput> OutputT` — `UFUNCTION(BlueprintCallable, Category = "Composure|Input", meta = (DeterminesOutputType = "OutputType", BlueprintProtected))`
- L382 _public prototype_ `virtual void BeginPlay() override;`
- L383 _public prototype_ `virtual void PostInitProperties() override;`
- L384 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L385 _public prototype_ `virtual void PostLoad() override;`
- L386 _public prototype_ `virtual void BeginDestroy() override;`
- L388 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L389 _public prototype_ `virtual void PostEditUndo() override;`
- L390 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L396 _public prototype_ `virtual void RerunConstructionScripts() override;`
- L397 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L402 _public prototype_ `virtual void SetAutoRun(bool bNewAutoRunVal) override;`
- L404 _public prototype_ `virtual void EnqueueRendering_Implementation(bool bCameraCutThisFrame) override;`
- L405 _public prototype_ `virtual bool IsActivelyRunning_Implementation() const;`
- L408 _public prototype_ `virtual int32 GetRenderPriority() const override;` — `UFUNCTION(BlueprintPure, Category = "Composure")`
- L412 _private prototype_ `void FrameReset();`
- L414 _private prototype_ `void PostSerializeCompatUpgrade(const int32 ComposureVersion);`
- L415 _private prototype_ `void PostLoadCompatUpgrade(const int32 ComposureVersion);`
- L418 _private prototype_ `UCompositingElementTransform* GetPreviewPass() const;`
- L419 _private prototype_ `bool IsPreviewing() const;`
- L421 _private prototype_ `void OnPIEStarted(bool bIsSimulating);`
- L422 _private prototype_ `void SetDebugDisplayImage(UTexture* DebugDisplayImg);`
- L424 _private prototype_ `void OnDisabled();`
- L426 _private prototype_ `void RefreshAllInternalPassLists();`
- L427 _private prototype_ `void RefreshInternalInputsList();`
- L428 _private prototype_ `void RefreshInternalTransformsList();`
- L429 _private prototype_ `void RefreshInternalOutputsList();`
- L431 _private prototype_ `const decltype(Inputs)& GetInternalInputsList() const;`
- L432 _private prototype_ `const decltype(TransformPasses)& GetInternalTransformsList() const;`
- L433 _private prototype_ `const decltype(Outputs)& GetInternalOutputsList() const;`
- L435 _private prototype_ `void BeginFrameForAllPasses(bool bCameraCutThisFrame);`
- L436 _private prototype_ `void GenerateInputs();`
- L437 _private prototype_ `void ApplyTransforms(FInheritedTargetPool& RenderTargetPool);`
- L438 _private prototype_ `void RelayOutputs(const FInheritedTargetPool& RenderTargetPool);`
- L439 _private prototype_ `void EndFrameForAllPasses();`
- L441 _private prototype_ `void UpdateFinalRenderResult(UTexture* RenderResult);`
- L443 _private typedef_ `typedef TSharedPtr<FCompElementRenderTargetPool> FSharedTargetPoolPtr;`
- L444 _private prototype_ `const FSharedTargetPoolPtr& GetRenderTargetPool();`
- L446 _private prototype_ `void RegisterTaggedPassResult(FName ReferenceName, UTexture* PassResult, ETargetUsageFlags UsageFlags = ETargetUsageFlags::USAGE_None);`
- L447 _private prototype_ `void ResetResultsLookupTable(bool bKeepPassResults = false);`
- L449 _private prototype_ `void IncIntermediateTrackingTag();`
- L453 _private member_ `FName CompShotIdName;` — `UPROPERTY()`
- L456 _private member_ `TObjectPtr<ACompositingElement> Parent;` — `UPROPERTY()`
- L458 _private member_ `TArray<TObjectPtr<ACompositingElement>> ChildLayers;` — `UPROPERTY()`
- L463 _private member_ `TObjectPtr<UTexture> DisabledMsgImage;` — `UPROPERTY(Transient)`
- L465 _private member_ `TObjectPtr<UTexture> EmptyWarnImage;` — `UPROPERTY(Transient)`
- L467 _private member_ `TObjectPtr<UTexture> SuspendedDbgImage;` — `UPROPERTY(Transient)`
- L469 _private member_ `TObjectPtr<UTexture> CompilerErrImage;` — `UPROPERTY(Transient)`
- L472 _private member_ `bool bUsingDebugDisplayImage = false;` — `UPROPERTY(Transient, DuplicateTransient)`
- L475 _private member_ `TObjectPtr<UTexture> ColorPickerDisplayImage;` — `UPROPERTY(Transient, DuplicateTransient)`
- L477 _private member_ `TObjectPtr<UTexture> EditorPreviewImage;` — `UPROPERTY(Transient, DuplicateTransient)`
- L480 _private member_ `TObjectPtr<UTextureRenderTarget2D> ColorPickerTarget;` — `UPROPERTY(Transient, DuplicateTransient)`
- L482 _private member_ `uint32 LastEnqueuedFrameId = (uint32)-1;`
- L483 _private member_ `int32 PreviewCount = 0;`
- L486 _private member_ `ETargetUsageFlags NextIntermediateTrackingTag = ETargetUsageFlags::USAGE_Intermediate0;`
- L489 _private member_ `float OutputOpacity = 1.f;` — `UPROPERTY()`
- L497 _private member_ `TMap<TObjectPtr<UCompositingElementInput>, ECompPassConstructionType> UserConstructedInputs;` — `UPROPERTY()` — Lists containing passes added programatically (or through Blueprints) via the AddNewPass() functions. These need their own separate lists to: 1) hide from the details panel, and 2) clear on re-construction, so we don't perpetually grow the lists.
- L499 _private member_ `TMap<TObjectPtr<UCompositingElementTransform>, ECompPassConstructionType> UserConstructedTransforms;` — `UPROPERTY()`
- L501 _private member_ `TMap<TObjectPtr<UCompositingElementOutput>, ECompPassConstructionType> UserConstructedOutputs;` — `UPROPERTY()`
- L510 _private member_ `TArray<TObjectPtr<UCompositingElementInput>> InternalInputs;` — `UPROPERTY(Instanced, Transient, DuplicateTransient, SkipSerialization)` — Authoritative lists that we use to iterate on the passes - conjoined from the public lists and the internal 'UserConstructed' ones. Used to: 1) have a single 'goto' list (w/ no nullptrs), and 2) determine passes that were cleared from the public lists so we can halt their processing (still alive via the transaction buffer).
- L512 _private member_ `TArray<TObjectPtr<UCompositingElementTransform>> InternalTransformPasses;` — `UPROPERTY(Instanced, Transient, DuplicateTransient, SkipSerialization)`
- L514 _private member_ `TArray<TObjectPtr<UCompositingElementOutput>> InternalOutputs;` — `UPROPERTY(Instanced, Transient, DuplicateTransient, SkipSerialization)`
- L517 _private member_ `TObjectPtr<UAlphaTransformPass> InternalAlphaPass = nullptr;` — `UPROPERTY(Transient)`
- L520 _private member_ `FCompositingTextureLookupTable PassResultsTable;`
- L522 _private member_ `FSharedTargetPoolPtr RenderTargetPool;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDynamicOnTransformPassRendered, class ACompositingElement*, CompElement, UTexture*, Texture, FName, PassName);`
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDynamicOnTransformPassRendered, class ACompositingElement*, CompElement, UTexture*, Texture, FName, PassName);`
- L30 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynamicOnFinalPassRendered, class ACompositingElement*, CompElement, UTexture*, Texture);`
- L30 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynamicOnFinalPassRendered, class ACompositingElement*, CompElement, UTexture*, Texture);`
- L61 _prototype_ `ENUM_CLASS_FLAGS(ETargetUsageFlags);`
- L135 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTransformPassRendered, ACompositingElement*, UTexture*, FName);` — Called when this comp shot element has rendered one of its internal transform passes
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFinalPassRendered, ACompositingElement*, UTexture*);` — Called when this comp shot element has rendered its final output
- L166 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompElementConstructed, ACompositingElement*);`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/CompositingElementInputs.h` (Public)


#### class `UCompositingMediaInput`  
`class UCompositingMediaInput : public UCompositingElementInput`  
_L16-48_
- reflection: `UCLASS(Abstract)`
- inherits: `UCompositingElementInput`
- L21 _public prototype_ `UCompositingMediaInput();`
- L24 _public member_ `FCompositingMaterial MediaTransformMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "MediaSource", EditCondition = "bEnabled"))`
- L32 _public prototype_ `virtual void PostInitProperties() override;`
- L36 _public prototype_ `virtual UTexture* GenerateInput_Implementation() override;`
- L40 _private prototype_ `virtual UTexture* GetMediaTexture() const PURE_VIRTUAL(UCompositingMediaInput::GetMediaTexture, return nullptr;);`
- L43 _private member_ `TObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY(Transient)`
- L45 _private member_ `TObjectPtr<UMaterialInterface> DefaultTestPlateMaterial;` — `UPROPERTY(Transient)`
- L47 _private member_ `TObjectPtr<UMaterialInstanceDynamic> FallbackMID;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`

#### class `UMediaTextureCompositingInput`  
`class UMediaTextureCompositingInput : public UCompositingMediaInput`  
_L75-88_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UCompositingMediaInput`
- L80 _public prototype_ `UMediaTextureCompositingInput();`
- L83 _public member_ `TObjectPtr<UMediaTexture> MediaSource;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L87 _private prototype_ `virtual UTexture* GetMediaTexture() const override;`

#### class `UCompositingInputInterface`  
`class UCompositingInputInterface : public UInterface`  
_L94-97_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ICompositingInputInterface`  
`class ICompositingInputInterface`  
_L99-112_
- L105 _public prototype_ `void OnFrameBegin(class UCompositingInputInterfaceProxy* Proxy, bool bCameraCutThisFrame);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure", meta = (CallInEditor = "true"))`
- L108 _public prototype_ `UTexture* GenerateInput(class UCompositingInputInterfaceProxy* Proxy);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Input", meta = (CallInEditor = "true"))`
- L111 _public prototype_ `void OnFrameEnd(class UCompositingInputInterfaceProxy* Proxy);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure", meta = (CallInEditor = "true"))`

#### class `UCompositingInputInterfaceProxy`  
`class UCompositingInputInterfaceProxy : public UCompositingElementInput`  
_L115-128_
- reflection: `UCLASS(noteditinlinenew, hidedropdown)`
- inherits: `UCompositingElementInput`
- L121 _public member_ `TScriptInterface<ICompositingInputInterface> CompositingInput;` — `UPROPERTY(BlueprintReadWrite, Category = "Compositing Pass")`
- L125 _public prototype_ `virtual void OnFrameBegin_Implementation(bool bCameraCutThisFrame) override;`
- L126 _public prototype_ `virtual UTexture* GenerateInput_Implementation() override;`
- L127 _public prototype_ `virtual void OnFrameEnd_Implementation() override;`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/CompositingElementOutputs.h` (Public)


#### class `UColorConverterOutputPass`  
`class UColorConverterOutputPass : public UCompositingElementOutput, public ICompEditorImagePreviewInterface`  
_L20-61_
- reflection: `UCLASS(Abstract)`
- inherits: `UCompositingElementOutput,ICompEditorImagePreviewInterface`
- L26 _public member_ `TObjectPtr<UCompositingElementTransform> ColorConverter;` — `UPROPERTY(EditAnywhere, Instanced, Category="Compositing Pass", meta=(DisplayName="Color Conversion", DisplayAfter = "PassName", EditCondition = "bEnabled", ShowOnlyInnerProperties))`
- L30 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void OnFrameBegin_Implementation(bool bCameraCutThisFrame) override;`
- L35 _public prototype_ `virtual void Reset_Implementation() override;`
- L36 _public prototype_ `virtual void OnDisabled_Implementation() override;`
- L41 _public function_ `virtual UTexture* GetEditorPreviewImage() override`
- L42 _public function_ `virtual bool UseImplicitGammaForPreview() const override`
- L47 _protected prototype_ `UTexture* ApplyColorTransform(UTexture* RenderResult, UComposurePostProcessingPassProxy* PostProcessProxy, FInheritedTargetPool& TargetPool);`
- L48 _protected prototype_ `UTexture* ApplyColorTransform(UTexture* RenderResult, UComposurePostProcessingPassProxy* PostProcessProxy, FIntPoint TargetResolution, ETextureRenderTargetFormat TargetFormat);`
- L49 _protected prototype_ `UTexture* ApplyColorTransform(UTexture* RenderResult, UComposurePostProcessingPassProxy* PostProcessProxy);`
- L52 _protected member_ `TSubclassOf<UCompositingElementTransform> DefaultConverterClass;` — `UPROPERTY(Transient)`
- L56 _protected member_ `TObjectPtr<UTexture> PreviewResult = nullptr;` — `UPROPERTY(Transient)`
- L60 _private prototype_ `void InternalReset();`

#### class `UCompositingMediaCaptureOutput`  
`class UCompositingMediaCaptureOutput : public UColorConverterOutputPass`  
_L72-106_
- reflection: `UCLASS()`
- inherits: `UColorConverterOutputPass`
- L77 _public prototype_ `UCompositingMediaCaptureOutput();`
- L80 _public member_ `TObjectPtr<UMediaOutput> CaptureOutput;` — `UPROPERTY(EditAnywhere, Category="Compositing Pass", BlueprintReadWrite, meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L83 _public prototype_ `bool IsCapturing() const;`
- L88 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L93 _public prototype_ `virtual void Reset_Implementation() override;`
- L94 _public prototype_ `virtual void RelayOutput_Implementation(UTexture* FinalResult, UComposurePostProcessingPassProxy* PostProcessProxy) override;`
- L95 _public prototype_ `virtual void OnDisabled_Implementation() override;`
- L96 _public prototype_ `virtual void OnEnabled_Implementation() override;`
- L100 _protected prototype_ `bool StartCapture(UTextureRenderTarget2D* RenderTarget);`
- L101 _protected prototype_ `void StopCapture();`
- L105 _private member_ `TObjectPtr<UMediaCapture> ActiveCapture = nullptr;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`

#### class `URenderTargetCompositingOutput`  
`class URenderTargetCompositingOutput : public UCompositingElementOutput`  
_L114-125_
- reflection: `UCLASS()`
- inherits: `UCompositingElementOutput`
- L120 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L124 _public prototype_ `virtual void RelayOutput_Implementation(UTexture* FinalResult, UComposurePostProcessingPassProxy* PostProcessProxy) override;`

#### enum `EExrCompressionOptions`  
`enum class EExrCompressionOptions : uint8`  
_L131-135_
- reflection: `UENUM()`
- L133 _public enumerator_ `Compressed = 0`
- L134 _public enumerator_ `Uncompressed = 1`

#### class `UEXRFileCompositingOutput`  
`class UEXRFileCompositingOutput : public UCompositingElementOutput`  
_L138-179_
- reflection: `UCLASS()`
- inherits: `UCompositingElementOutput`
- L143 _public prototype_ `UEXRFileCompositingOutput();`
- L146 _public member_ `FDirectoryPath OutputDirectiory;` — `UPROPERTY(EditAnywhere, Category="Compositing Pass", BlueprintReadWrite ,meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L153 _public member_ `FString FilenameFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))` — The format to use for the resulting filename. Extension will be added automatically. Any tokens of the form {token} will be replaced with the corresponding value: {frame} - The current frame number
- L156 _public member_ `FFrameRate OutputFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Compositing Pass", meta=(ClampMin=1, UIMin=1, ClampMax=200, UIMax=200, DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L159 _public member_ `EExrCompressionOptions Compression = EExrCompressionOptions::Uncompressed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L164 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L169 _public prototype_ `virtual void Reset_Implementation() override;`
- L170 _public prototype_ `virtual void RelayOutput_Implementation(UTexture* FinalResult, UComposurePostProcessingPassProxy* PostProcessProxy) override;`
- L171 _public prototype_ `virtual void OnDisabled_Implementation() override;`
- L175 _private prototype_ `void InternalReset();`
- L177 _private member_ `int32 FrameNumber = 0;`
- L178 _private member_ `double SecondsSinceLastCapture = 0.0;`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/CompositingElementPasses.h` (Public)


#### class `UCompositingElementPass`  
`class UCompositingElementPass : public UObject`  
_L19-80_
- reflection: `UCLASS(editinlinenew, Abstract)`
- inherits: `UObject`
- L25 _protected member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = IsPassEnabled, BlueprintSetter = SetPassEnabled, Category = "Compositing Pass")`
- L28 _public prototype_ `UCompositingElementPass();`
- L31 _public member_ `FName PassName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compositing Pass", meta = (EditCondition = "bEnabled"))`
- L34 _public member_ `ECompPassConstructionType ConstructionMethod;`
- L39 _public prototype_ `void OnFrameBegin(bool bCameraCutThisFrame);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Compositing Pass", meta=(CallInEditor = "true"))`
- L42 _public prototype_ `void OnFrameEnd();` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Compositing Pass", meta=(CallInEditor = "true"))`
- L45 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Compositing Pass", meta=(CallInEditor = "true"))`
- L48 _public function_ `bool IsPassEnabled() const` — `UFUNCTION(BlueprintGetter)`
- L51 _public prototype_ `void SetPassEnabled(bool bSetEnabledTo = true);` — `UFUNCTION(BlueprintSetter)`
- L56 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L61 _protected prototype_ `void SetRenderTargetPool(const FInheritedTargetPool& TargetPool);`
- L64 _protected prototype_ `void OnDisabled();` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Compositing Pass", meta=(CallInEditor = "true"))`
- L66 _protected prototype_ `void OnEnabled();` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure|Compositing Pass", meta=(CallInEditor = "true"))`
- L69 _protected prototype_ `UTextureRenderTarget2D* RequestRenderTarget(FIntPoint Dimensions, ETextureRenderTargetFormat Format);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Compositing Pass"/*, meta = (BlueprintProtected = "true")*/)`
- L70 _protected prototype_ `UTextureRenderTarget2D* RequestRenderTarget(FIntPoint Dimensions, EPixelFormat Format);`
- L73 _protected prototype_ `UTextureRenderTarget2D* RequestNativelyFormattedTarget(float RenderScale = 1.f);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Compositing Pass"/*, meta = (BlueprintProtected = "true")*/)`
- L76 _protected prototype_ `bool ReleaseRenderTarget(UTextureRenderTarget2D* AssignedTarget);` — `UFUNCTION(BlueprintCallable, Category = "Composure|CompositingPass"/*, meta = (BlueprintProtected = "true")*/)`
- L79 _protected member_ `FInheritedTargetPool SharedTargetPool;`

#### class `UCompositingElementInput`  
`class UCompositingElementInput : public UCompositingElementPass`  
_L88-105_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract)`
- inherits: `UCompositingElementPass`
- L99 _public member_ `bool bIntermediate = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayName = "Intermediate", EditCondition = "bEnabled", DisplayAfter = "EndOfCategory"), AdvancedDisplay)` — Marks this pass for 'internal use only' - prevents it from being exposed to parent elements. When set, render target resources used by this element will be reused. For inputs, all 'Intermediate' passes are available to the first transform pass, and released after that.
- L101 _public prototype_ `UTexture* GenerateInput(const FInheritedTargetPool& InheritedPool);`
- L104 _protected prototype_ `UTexture* GenerateInput();` — `UFUNCTION(BlueprintNativeEvent, Category="Composure|Compositing Pass", meta = (CallInEditor))`

#### class `UCompositingElementTransform`  
`class UCompositingElementTransform : public UCompositingElementPass`  
_L116-139_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract)`
- inherits: `UCompositingElementPass`
- L127 _public member_ `bool bIntermediate = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayName = "Intermediate", EditCondition = "bEnabled", DisplayAfter = "EndOfCategory"), AdvancedDisplay)` — Marks this pass for 'internal use only' - prevents it from being exposed to parent elements. When set, render target resources used by this element will be reused. For transforms, all 'Intermediate' passes are available to the next transform pass, and released after that.
- L129 _public prototype_ `UTexture* ApplyTransform(UTexture* Input, ICompositingTextureLookupTable* PrePassLookupTable, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera, const FInheritedTargetPool& InheritedPool);`
- L132 _protected prototype_ `UTexture* ApplyTransform(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera);` — `UFUNCTION(BlueprintNativeEvent, Category="Composure|Compositing Pass", meta = (CallInEditor))`
- L136 _protected prototype_ `UTexture* FindNamedPrePassResult(FName PassLookupName);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Compositing Pass", meta = (BlueprintProtected = "true"))`
- L138 _protected member_ `ICompositingTextureLookupTable* PrePassLookupTable = nullptr;`

#### class `UCompositingElementOutput`  
`class UCompositingElementOutput : public UCompositingElementPass`  
_L148-157_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract)`
- inherits: `UCompositingElementPass`
- L153 _public prototype_ `void RelayOutput(UTexture* FinalResult, UComposurePostProcessingPassProxy* PostProcessProxy, const FInheritedTargetPool& InheritedPool);`
- L156 _protected prototype_ `void RelayOutput(UTexture* FinalResult, UComposurePostProcessingPassProxy* PostProcessProxy);` — `UFUNCTION(BlueprintNativeEvent, Category="Composure|Compositing Pass", meta = (CallInEditor))`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/CompositingElementTransforms.h` (Public)


#### class `UCompositingPostProcessPass`  
`class UCompositingPostProcessPass : public UCompositingElementTransform`  
_L19-36_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UCompositingElementTransform`
- L25 _public member_ `float RenderScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L28 _public member_ `TArray<TObjectPtr<UComposurePostProcessPassPolicy>> PostProcessPasses;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "RenderScale"))`
- L32 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L35 _protected prototype_ `void RenderPostPassesToSwapChain(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, FCompositingTargetSwapChain& TargetSwapChain);`

#### class `UCompositingElementMaterialPass`  
`class UCompositingElementMaterialPass : public UCompositingPostProcessPass`  
_L42-75_
- reflection: `UCLASS(BlueprintType, Blueprintable, editinlinenew)`
- inherits: `UCompositingPostProcessPass`
- L48 _public member_ `FCompositingMaterial Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compositing Pass", meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L52 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L60 _public prototype_ `void SetMaterialInterface(UMaterialInterface* NewMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Compositing Pass")` — Set the material interface used by current material pass. @param NewMaterial            The new material interface users want to set.
- L70 _public prototype_ `bool SetParameterMapping(FName TextureParamName, FName ComposureLayerName);` — `UFUNCTION(BlueprintCallable, Category = "Compositing Pass")` — Set the parameter mappings between texture parameters and composure layers. Users can not create new entries into the map as the keys are read only. Invalid Texture parameter names will result in a failed setting operation. @param TextureParamName       The name of the texture parameter inside the material interface. Used as key. @param ComposureLayerName     The name of the composure layer the texture parameter is mapped to. Used as value. @return bool                  True if set operation is successful.
- L74 _protected prototype_ `void ApplyMaterialParams(UMaterialInstanceDynamic* MID);` — `UFUNCTION(BlueprintImplementableEvent)`

#### class `UCompositingTonemapPass`  
`class UCompositingTonemapPass : public UCompositingElementTransform`  
_L83-107_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UCompositingElementTransform`
- L90 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(Interp, Category = "Compositing Pass",meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))` — Color grading settings.
- L94 _public member_ `FFilmStockSettings FilmStockSettings;` — `UPROPERTY(Interp, Category = "Compositing Pass",meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))` — Film stock settings.
- L98 _public member_ `float ChromaticAberration = 0.0f;` — `UPROPERTY(Interp, Category = "Compositing Pass", meta = (UIMin = "0.0", UIMax = "5.0", DisplayAfter = "PassName", EditCondition = "bEnabled"))` — in percent, Scene chromatic aberration / color fringe (camera imperfection) to simulate an artifact that happens in real-world lens, mostly visible in the image corners.
- L102 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L106 _private member_ `TObjectPtr<UComposureTonemapperPassPolicy> TonemapPolicy;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`

#### class `UMultiPassChromaKeyer`  
`class UMultiPassChromaKeyer : public UCompositingElementTransform`  
_L117-137_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UCompositingElementTransform`
- L122 _public prototype_ `UMultiPassChromaKeyer();`
- L125 _public member_ `TArray<FLinearColor> KeyColors;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L128 _public member_ `FCompositingMaterial KeyerMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L132 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L136 _private member_ `TObjectPtr<UTexture> DefaultWhiteTexture = nullptr;` — `UPROPERTY(Transient)`

#### class `UMultiPassDespill`  
`class UMultiPassDespill : public UCompositingElementTransform`  
_L148-168_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UCompositingElementTransform`
- L153 _public prototype_ `UMultiPassDespill();`
- L156 _public member_ `TArray<FLinearColor> KeyColors;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L159 _public member_ `FCompositingMaterial KeyerMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Compositing Pass", meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L163 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L167 _private member_ `TObjectPtr<UTexture> DefaultWhiteTexture = nullptr;` — `UPROPERTY(Transient)`

#### class `UAlphaTransformPass`  
`class UAlphaTransformPass : public UCompositingElementTransform`  
_L176-196_
- reflection: `UCLASS(noteditinlinenew, hidedropdown)`
- inherits: `UCompositingElementTransform`
- L181 _public prototype_ `UAlphaTransformPass();`
- L184 _public member_ `float AlphaScale = 1.f;` — `UPROPERTY(EditAnywhere,Category = "Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L188 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`
- L193 _private member_ `TObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY(Transient)`
- L195 _private member_ `TObjectPtr<UMaterialInstanceDynamic> AlphaTransformMID;` — `UPROPERTY(Transient)`

#### class `UCompositingOpenColorIOPass`  
`class UCompositingOpenColorIOPass : public UCompositingElementTransform`  
_L203-215_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "OpenColorIO Pass"))`
- inherits: `UCompositingElementTransform`
- L210 _public member_ `FOpenColorIOColorConversionSettings ColorConversionSettings;` — `UPROPERTY(Interp, Category = "OpenColorIO Settings",meta = (ShowOnlyInnerProperties, DisplayAfter = "PassName", EditCondition = "bEnabled"))` — Color grading settings.
- L214 _public prototype_ `virtual UTexture* ApplyTransform_Implementation(UTexture* Input, UComposurePostProcessingPassProxy* PostProcessProxy, ACameraActor* TargetCamera) override;`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/ICompositingTextureLookupTable.h` (Public)


#### class `UCompositingTextureLookupTable`  
`class UCompositingTextureLookupTable : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ICompositingTextureLookupTable`  
`class ICompositingTextureLookupTable`  
_L18-25_
- L24 _public prototype_ `virtual bool FindNamedPassResult(FName LookupName, UTexture*& OutTexture) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Composure")`

### `Plugins/Compositing/Composure/Source/Composure/Classes/CompositingElements/PlayerViewportCompositingOutput.h` (Public)


#### class `UPlayerViewportCompositingOutput`  
`class UPlayerViewportCompositingOutput : public UColorConverterOutputPass, public IBlendableInterface`  
_L21-74_
- reflection: `UCLASS()`
- inherits: `UColorConverterOutputPass,IBlendableInterface`
- L26 _public prototype_ `UPlayerViewportCompositingOutput();`
- L27 _public prototype_ `~UPlayerViewportCompositingOutput();`
- L30 _public member_ `int32 PlayerIndex = 0;` — `UPROPERTY(EditAnywhere, Category="Compositing Pass", meta = (DisplayAfter = "PassName", EditCondition = "bEnabled"))`
- L34 _public member_ `bool ApplyToneCurve = false;` — `UPROPERTY(EditAnywhere, Category = "Compositing Pass", meta = (DisplayAfter = "ColorConversion", EditCondition = "bEnabled"))` — Enable or disable the tone curve (and expand gamut) when the tonemap pass settings are passed down to the main viewport post-processing.
- L38 _public prototype_ `virtual void OnFrameBegin_Implementation(bool bCameraCutThisFrame) override;`
- L39 _public prototype_ `virtual void RelayOutput_Implementation(UTexture* RenderResult, UComposurePostProcessingPassProxy* PostProcessProxy) override;`
- L40 _public prototype_ `virtual void Reset_Implementation() override;`
- L44 _public prototype_ `virtual void OverrideBlendableSettings(FSceneView& View, float Weight) const override;`
- L49 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L52 _protected prototype_ `bool OverridePlayerCamera(int32 PlayerIndex);`
- L53 _protected prototype_ `void ClearViewportOverride();`
- L54 _protected prototype_ `UMaterialInstanceDynamic* GetBlendableMID();`
- L57 _protected prototype_ `bool UseBuiltInColorConversion() const;`
- L60 _private member_ `int32 ActiveOverrideIndex = INDEX_NONE;`
- L63 _private member_ `TObjectPtr<UPlayerCompOutputCameraModifier> ActiveCamModifier;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`
- L66 _private member_ `TObjectPtr<UMaterialInterface> TonemapperBaseMat;` — `UPROPERTY(Transient)`
- L68 _private member_ `TObjectPtr<UMaterialInterface> PreTonemapBaseMat;` — `UPROPERTY(Transient)`
- L71 _private member_ `TObjectPtr<UMaterialInstanceDynamic> ViewportOverrideMID;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`
- L73 _private member_ `TWeakObjectPtr<APlayerController> TargetedPlayerController;`

#### class `UPlayerCompOutputCameraModifier`  
`class UPlayerCompOutputCameraModifier : public UCameraModifier`  
_L80-94_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UCameraModifier`
- L85 _public prototype_ `void SetOwner(UPlayerViewportCompositingOutput* Owner);`
- L89 _public prototype_ `virtual bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;`
- L93 _private member_ `TObjectPtr<UPlayerViewportCompositingOutput> Owner;` — `UPROPERTY(Transient)`

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposureBlueprintLibrary.h` (Public)


#### class `UComposureBlueprintLibrary`  
`class UComposureBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-137_
- reflection: `UCLASS(meta=(ScriptName="ComposureLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _private prototype_ `static class UComposurePlayerCompositingTarget* CreatePlayerCompositingTarget(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Composure", meta = (WorldContext = "WorldContextObject"))` — Creates a Player Compositing Target which you can modify during gameplay.
- L32 _private prototype_ `static void GetProjectionMatrixFromPostMoveSettings( const FComposurePostMoveSettings& PostMoveSettings, float HorizontalFOVAngle, float AspectRatio, FMatrix& ProjectionMatrix);` — `UFUNCTION(BlueprintPure, Category = "Composure")` — Returns a non-centered projection matrix. @param HorizontalFOVAngle The desired horizontal FOV in degrees. @param AspectRatio The desired aspect ratio.
- L40 _private prototype_ `static void GetCroppingUVTransformationMatrixFromPostMoveSettings( const FComposurePostMoveSettings& PostMoveSettings, float AspectRatio, FMatrix& CropingUVTransformationMatrix, FMatrix& UncropingUVTransformationMatrix);` — `UFUNCTION(BlueprintPure, Category = "Composure")` — Returns UV transformation matrix and its inversed to crop. @param AspectRatio The desired aspect ratio.
- L46 _private function_ `static void SetUVMapSettingsToMaterialParameters( const FComposureUVMapSettings& UVMapSettings, class UMaterialInstanceDynamic* Material)` — `UFUNCTION(BlueprintCallable, Category = "Composure")` — Sets parameters of a material that uses Composure's MF_UVMap_SampleLocation material function.
- L57 _private function_ `static void InvertUVDisplacementMapEncodingParameters( const FVector2D& In, FVector2D& Out)` — `UFUNCTION(BlueprintPure, Category = "Composure")` — Converts displacement encoding parameters to decoding parameters. Can also be used to convert displacement decoding parameters to encoding parameters.
- L65 _private prototype_ `static void GetRedGreenUVFactorsFromChromaticAberration(float ChromaticAberrationAmount, FVector2D& RedGreenUVFactors);` — `UFUNCTION(BlueprintPure, Category = "Composure")` — Returns the red and green channel factors from percentage of chromatic aberration.
- L69 _private prototype_ `static void GetPlayerDisplayGamma(const APlayerCameraManager* PlayerCameraManager, float& DisplayGamma);` — `UFUNCTION(BlueprintPure, Category = "Composure")` — Returns display gamma of a given player camera manager, or 0 if no scene viewport attached.
- L72 _private prototype_ `static void CopyCameraSettingsToSceneCapture(UCameraComponent* SrcCamera, USceneCaptureComponent2D* DstCaptureComponent, float OriginalFocalLength, float OverscanFactor = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L82 _private prototype_ `static ACompositingElement* CreateComposureElement(const FName ElementName,UPARAM(meta=(AllowAbstract="false")) TSubclassOf<ACompositingElement> ClassType, AActor* LevelContext = null` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager", meta = (DeterminesOutputType = "ClassType"))` — Create a new Composure in the level without any parenting relationship. @param ElementName              The name for the newly created composure element @param ClassType                The type for the new composure element @param LevelContext             The level context of current level. Default value is nullptr. @return CompositingElement      The created composure element.
- L90 _private prototype_ `static ACompositingElement* GetComposureElement(const FName ElementName);` — `UFUNCTION(BlueprintPure, Category = "Composure|Manager")` — Get a specific composure element @param ElementName              The name of the composure element that we want to get. @return CompositingElement      The composure element found. It can be nullptr if there is no composure element matches the input name.
- L97 _private prototype_ `static void DeleteComposureElementAndChildren(const FName ElementToDelete);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager")` — Delete a specific composure element without evoking prompt window. Will delete all of its children as well. @param ElementToDelete           The name of the composure element that we want to delete.
- L106 _private prototype_ `static bool RenameComposureElement(const FName OriginalElementName, const FName NewElementName);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager")` — Rename a specific composure element @param OriginalElementName       The name of the composure element that we want to rename. @param NewElementName            The new name for the composure element. @return bool                     Whether the renaming operation is successful or not.
- L115 _private prototype_ `static bool AttachComposureElement(const FName ParentName, const FName ChildName);` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager")` — Attach one composure element as the child to another composure element in the scene. @param ParentName                The name of the parent composure element. @param ChildName                 The name of the child composure element. @return bool                     Whether the attaching process is successful or not.
- L123 _private prototype_ `static bool IsComposureElementDrawing(ACompositingElement* CompElement);` — `UFUNCTION(BlueprintPure, Category = "Composure|Manager")` — Determines if the specified element is being rendered by the hidden compositing viewport. @param  CompElement	The element actor you're querying for @return True if the game-thread is in the middle of queuing the specified element.
- L130 _private prototype_ `static void RequestRedrawComposureViewport();` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager")` — Request redrawing the compositing editor viewport  if it is valid. If it is invalid, this function will create a new view port client.
- L136 _private prototype_ `static void RefreshComposureElementList();` — `UFUNCTION(BlueprintCallable, Category = "Composure|Manager")` — Re-queries the scene for element actors and rebuilds the authoritative list used by the editor.

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposureLensBloomPass.h` (Public)


#### class `UComposureLensBloomPass`  
`class UComposureLensBloomPass : public UComposurePostProcessPass`  
_L18-43_
- reflection: `UCLASS(hidecategories = (Collision, Object, Physics, SceneComponent, Transform), ClassGroup = "Composure", editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UComposurePostProcessPass`
- desc: Bloom only pass implemented on top of the in-engine bloom.
- L26 _public member_ `FLensBloomSettings Settings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Lens Bloom Settings")` — Bloom settings.
- L31 _public prototype_ `void SetTonemapperReplacingMaterial(UMaterialInstanceDynamic* Material);` — `UFUNCTION(BlueprintCallable, Category = "Lens Bloom Settings")` — Sets a custom tonemapper replacing material instance.
- L38 _public prototype_ `void BloomToRenderTarget();` — `UFUNCTION(BlueprintCallable, Category = "Outputs")` — Blurs the input into the output.
- L42 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TonemapperReplacingMID;` — `UPROPERTY(Transient)`

#### class `UComposureLensBloomPassPolicy`  
`class UComposureLensBloomPassPolicy : public UComposurePostProcessPassPolicy`  
_L49-72_
- reflection: `UCLASS(BlueprintType, Blueprintable, editinlinenew, meta=(DisplayName="Lens Bloom Pass"))`
- inherits: `UComposurePostProcessPassPolicy`
- desc: Bloom only rules used for configuring how UComposurePostProcessingPassProxy executes
- L52 _private prototype_ `UComposureLensBloomPassPolicy();`
- L57 _public member_ `FLensBloomSettings Settings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Lens Bloom Settings")` — Bloom settings.
- L60 _public member_ `TObjectPtr<UMaterialInterface> ReplacementMaterial;` — `UPROPERTY(EditAnywhere, Category = "Tonemapper Settings", AdvancedDisplay)`
- L63 _public member_ `FName BloomIntensityParamName;` — `UPROPERTY(EditAnywhere, Category = "Tonemapper Settings", AdvancedDisplay)`
- L67 _public prototype_ `void SetupPostProcess_Implementation(USceneCaptureComponent2D* SceneCapture, UMaterialInterface*& OutTonemapperOverride) override;`
- L71 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TonemapperReplacmentMID;` — `UPROPERTY(Transient)`

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposurePipelineBaseActor.h` (Public)


#### class `AComposurePipelineBaseActor`  
`class AComposurePipelineBaseActor : public AActor`  
_L15-77_
- reflection: `UCLASS(BlueprintType, Blueprintable, config=Engine, meta=(ShortTooltip="Actor designed to implement compositing pipeline in a blueprint."))`
- inherits: `AActor`
- desc: Actor designed to implement compositing pipeline in a blueprint.
- L26 _public member_ `bool bAutoRun;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetAutoRun, Category="Composure|Ticking", meta = (DisplayAfter = "bEnableChildElementsAndSelf"))` — When set, we'll call EnqueueRendering() each frame automatically. If left off, it is up to the user to manually call their composure rendering. Toggle this on/off at runtime to enable/disable this pipeline.
- L31 _public member_ `bool bRunInEditor;` — `UPROPERTY(EditAnywhere, Category="Composure|Ticking", meta = (EditCondition = "bAutoRun", DisplayAfter = "bAutoRun"))` — With bAutoRun, this will run EnqueueRendering() in editor - enqueuing render calls along with Editor scene rendering.
- L35 _public function_ `virtual void SetAutoRun(bool bNewAutoRunVal)` — `UFUNCTION(BlueprintSetter)`
- L38 _public function_ `bool AreChildrenAndSelfAutoRun() const` — `UFUNCTION(BlueprintGetter)`
- L45 _public prototype_ `bool IsActivelyRunning() const;` — `UFUNCTION(BlueprintNativeEvent, Category="Composure", meta = (CallInEditor = "true"))`
- L47 _public prototype_ `bool IsAutoRunSuspended() const;`
- L54 _public prototype_ `void EnqueueRendering(bool bCameraCutThisFrame);` — `UFUNCTION(BlueprintNativeEvent, Category="Composure", meta = (CallInEditor = "true"))` — Entry point for a composure Blueprint to do its render enqueuing from.
- L56 _public function_ `virtual int32 GetRenderPriority() const`
- L59 _public function_ `virtual void SetAutoRunChildrenAndSelf(bool bAutoRunChildAndSelf)` — `UFUNCTION(BlueprintSetter, Category = "Composure|Element")`
- L64 _public prototype_ `virtual void RerunConstructionScripts() override;`
- L73 _protected member_ `bool bAutoRunChildElementsAndSelf = true;` — `UPROPERTY(EditAnywhere, BlueprintGetter = AreChildrenAndSelfAutoRun, BlueprintSetter = SetAutoRunChildrenAndSelf,Category = "Composure|Ticking", meta = (DisplayName = "Auto run children and self"))` — When set to false, all composure elements including itself's rendering will not automatically be called in the pipeline. When set to true, all of its children and its self's rendering will be called every frame.
- L76 _private member_ `TSharedPtr<FComposureViewExtension, ESPMode::ThreadSafe> ViewExtension;`

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposurePlayerCompositingTarget.h` (Public)


#### class `UComposurePlayerCompositingTarget`  
`class UComposurePlayerCompositingTarget : public UObject, public IComposurePlayerCompositingInterface`  
_L36-87_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject,IComposurePlayerCompositingInterface`
- desc: Object to bind to a APlayerCameraManager with a UTextureRenderTarget2D to be used as a player's render target. @TODO-BADGER: deprecate this (UComposurePlayerCompositingTarget) once we're comfortable using the new UComposureCompositingTargetComponent in its place
- L40 _private prototype_ `~UComposurePlayerCompositingTarget();`
- L46 _public function_ `APlayerCameraManager* GetPlayerCameraManager() const` — `UFUNCTION(BlueprintCallable, Category = "Player Compositing target")` — Current player camera manager the target is bind on.
- L53 _public prototype_ `APlayerCameraManager* SetPlayerCameraManager(APlayerCameraManager* PlayerCameraManager);` — `UFUNCTION(BlueprintCallable, Category = "Player Compositing target")` — Set player camera manager to bind the render target to.
- L57 _public prototype_ `void SetRenderTarget(UTextureRenderTarget2D* RenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Player Compositing target")` — Set the render target of the player.
- L61 _public prototype_ `virtual void FinishDestroy() override;` — Begins UObject
- L68 _private member_ `TObjectPtr<APlayerCameraManager> PlayerCameraManager;` — `UPROPERTY(Transient)` — Current player camera manager the target is bind on.
- L72 _private member_ `TObjectPtr<class UComposurePlayerCompositingCameraModifier> PlayerCameraModifier;` — `UPROPERTY(Transient)` — Underlying player camera modifier
- L76 _private member_ `TObjectPtr<class UMaterialInstanceDynamic> ReplaceTonemapperMID;` — `UPROPERTY(Transient)` — Post process material that replaces the tonemapper to dump the player's render target.
- L79 _private member_ `FEngineShowFlags EngineShowFlagsBackup;` — Backup of the engine showflags to restore when unbinding the compositing target from the camera manager.
- L83 _private prototype_ `virtual void OverrideBlendableSettings(class FSceneView& View, float Weight) const override;` — Entries called by PlayerCameraModifier.

#### class `UComposureCompositingTargetComponent`  
`class UComposureCompositingTargetComponent : public UActorComponent, public ICompEditorImagePreviewInterface`  
_L100-145_
- reflection: `UCLASS(ClassGroup = Rendering, Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,ICompEditorImagePreviewInterface`
- desc: Component intended to replace UComposurePlayerCompositingTarget - a object to bind to a APlayerCameraManager with a UTextureRenderTarget2D to be used as a player's render target. Made into a component so we can hook into preview rendering in editor.
- L106 _public prototype_ `void SetDisplayTexture(UTexture* DisplayTexture);` — `UFUNCTION(BlueprintCallable, Category = "Composure|CompositingTarget")`
- L109 _public function_ `UTexture* GetDisplayTexture() const` — `UFUNCTION(BlueprintCallable, Category = "Composure|CompositingTarget")`
- L112 _public prototype_ `bool IsPreviewing() const;`
- L113 _public function_ `void SetUseImplicitGammaForPreview(const bool bInUseImplicitGammaOnPreview)`
- L119 _public prototype_ `virtual bool GetEditorPreviewInfo(float DeltaTime, FMinimalViewInfo& ViewOut) override;`
- L120 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomEditorPreviewWidget() override;`
- L126 _public prototype_ `virtual void OnBeginPreview() override;`
- L127 _public prototype_ `virtual UTexture* GetEditorPreviewImage() override;`
- L128 _public prototype_ `virtual void OnEndPreview() override;`
- L129 _public function_ `virtual bool UseImplicitGammaForPreview() const override`
- L135 _private member_ `TObjectPtr<UTexture> DisplayTexture;` — `UPROPERTY(Transient)`
- L139 _private member_ `TObjectPtr<UTexture> CompilerErrImage;` — `UPROPERTY(Transient)`
- L141 _private member_ `int32 PreviewCount = 0;`
- L142 _private member_ `bool bUseImplicitGammaOnPreview = true;`
- L143 _private member_ `bool bHasCompilerError = false;`

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposurePostProcessPass.h` (Public)


#### class `UComposurePostProcessPass`  
`class UComposurePostProcessPass : public USceneComponent`  
_L24-87_
- reflection: `UCLASS()`
- inherits: `USceneComponent`
- desc: In engine post process based pass.
- L35 _public prototype_ `void SetSetupMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "Inputs")` — Sets a custom setup post process material. The material location must be set at BeforeTranslucency.
- L39 _public function_ `UMaterialInterface* GetSetupMaterial() const` — `UFUNCTION(BlueprintPure, Category = "Inputs")` — Gets current setup material.
- L48 _public prototype_ `UTextureRenderTarget2D* GetOutputRenderTarget() const;` — `UFUNCTION(BlueprintCallable, Category = "Outputs")` — Gets current output render target.
- L54 _public prototype_ `void SetOutputRenderTarget(UTextureRenderTarget2D* RenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Outputs")` — Sets current output render target.
- L59 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L60 _public prototype_ `virtual void Deactivate() override;`
- L61 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L67 _protected member_ `TObjectPtr<USceneCaptureComponent2D> SceneCapture;` — `UPROPERTY(Transient, NonTransactional)` — Underlying scene capture.
- L71 _protected member_ `TObjectPtr<UComposurePostProcessBlendable> BlendableInterface;` — `UPROPERTY(Transient, NonTransactional)` — Blendable interface to intercept the OverrideBlendableSettings.
- L75 _protected member_ `TObjectPtr<UMaterialInterface> SetupMaterial;` — `UPROPERTY(Transient, NonTransactional)` — Setup post process material.
- L79 _protected member_ `TObjectPtr<UMaterialInterface> TonemapperReplacement;` — `UPROPERTY(Transient, NonTransactional)` — Internal material that replace the tonemapper to output linear color space.
- L82 _protected prototype_ `void OverrideBlendableSettings(class FSceneView& View, float Weight) const;` — Called by UComposurePostProcessBlendable::OverrideBlendableSettings.

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposurePostProcessingPassProxy.h` (Public)


#### class `UComposurePostProcessPassPolicy`  
`class UComposurePostProcessPassPolicy : public UObject`  
_L18-28_
- reflection: `UCLASS(Blueprintable, BlueprintType, Abstract)`
- inherits: `UObject`
- desc: Abstract base class for setting up post passes. Used in conjuntion with UComposurePostProcessingPassProxy.
- L23 _public function_ `UComposurePostProcessPassPolicy()`
- L27 _public prototype_ `void SetupPostProcess(USceneCaptureComponent2D* SceneCapture, UMaterialInterface*& TonemapperOverride);` — `UFUNCTION(BlueprintNativeEvent, Category = "Composure")`

#### class `UComposurePostProcessingPassProxy`  
`class UComposurePostProcessingPassProxy : public UComposurePostProcessPass`  
_L35-52_
- reflection: `UCLASS(hidecategories = (Collision, Object, Physics, SceneComponent, Transform), ClassGroup = "Composure", editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UComposurePostProcessPass`
- desc: Generic component class which takes a UComposurePostProcessPassPolicy and executes it, enqueuing a post-process pass for the render frame.
- L42 _public prototype_ `void Execute(UTexture* PrePassInput, UComposurePostProcessPassPolicy* PostProcessPass);` — `UFUNCTION(BlueprintCallable, Category = "Composure")`
- L45 _public prototype_ `virtual void PostInitProperties() override;`
- L46 _public prototype_ `virtual void PostLoad() override;`
- L51 _private member_ `TObjectPtr<UMaterialInstanceDynamic> SetupMID;` — `UPROPERTY(Transient, DuplicateTransient, SkipSerialization)`

### `Plugins/Compositing/Composure/Source/Composure/Classes/ComposureTonemapperPass.h` (Public)


#### class `FComposureTonemapperUtils`  
`class FComposureTonemapperUtils`  
_L15-19_
- L18 _public prototype_ `static void ApplyTonemapperSettings(const FColorGradingSettings& ColorGradingSettings, const FFilmStockSettings& FilmStockSettings, const float ChromaticAberration, FPostProcessSettings& OutSettings);`

#### class `UComposureTonemapperPass`  
`class UComposureTonemapperPass : public UComposurePostProcessPass`  
_L25-49_
- reflection: `UCLASS(hidecategories = (Collision, Object, Physics, SceneComponent, Transform), ClassGroup = "Composure", editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UComposurePostProcessPass`
- desc: Tonemapper only pass implemented on top of the in-engine tonemapper.
- L33 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Settings")` — Color grading settings.
- L37 _public member_ `FFilmStockSettings FilmStockSettings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Settings")` — Film stock settings.
- L41 _public member_ `float ChromaticAberration;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Lens", meta = (UIMin = "0.0", UIMax = "5.0"))` — in percent, Scene chromatic aberration / color fringe (camera imperfection) to simulate an artifact that happens in real-world lens, mostly visible in the image corners.
- L48 _public prototype_ `void TonemapToRenderTarget();` — `UFUNCTION(BlueprintCallable, Category = "Outputs")` — Tone map the input into the output.

#### class `UComposureTonemapperPassPolicy`  
`class UComposureTonemapperPassPolicy : public UComposurePostProcessPassPolicy`  
_L55-76_
- reflection: `UCLASS(BlueprintType, Blueprintable, editinlinenew, meta=(DisplayName="Tonemapper Pass"))`
- inherits: `UComposurePostProcessPassPolicy`
- desc: Tonemapper only rules used for configuring how UComposurePostProcessingPassProxy executes
- L58 _private function_ `UComposureTonemapperPassPolicy()`
- L63 _public member_ `FColorGradingSettings ColorGradingSettings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Tonemapper Settings")` — Color grading settings.
- L67 _public member_ `FFilmStockSettings FilmStockSettings;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Tonemapper Settings")` — Film stock settings.
- L71 _public member_ `float ChromaticAberration = 0.0f;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Lens Settings", meta = (UIMin = "0.0", UIMax = "5.0"))` — in percent, Scene chromatic aberration / color fringe (camera imperfection) to simulate an artifact that happens in real-world lens, mostly visible in the image corners.
- L75 _public prototype_ `void SetupPostProcess_Implementation(USceneCaptureComponent2D* SceneCapture, UMaterialInterface*& OutTonemapperOverride) override;`

### `Plugins/Compositing/Composure/Source/Composure/Private/CompositingElements/CompElementRenderTargetPool.h` (Private)


#### class `FCompElementRenderTargetPool`  
`class FCompElementRenderTargetPool : public FGCObject #if WITH_EDITOR , public FTickableEditorObject #endif`  
_L23-117_
- inherits: `FGCObject,FTickableEditorObject`
- L29 _public prototype_ `static FSharedTargetPoolRef GetSharedInstance();`
- L30 _public member_ `static int32 ExtensionPriority;`
- L32 _public prototype_ `FCompElementRenderTargetPool(UObject* Outer);`
- L33 _public prototype_ `~FCompElementRenderTargetPool();`
- L37 _public prototype_ `UTextureRenderTarget2D* AssignTarget(UObject* Owner, FIntPoint Dimensions, ETextureRenderTargetFormat Format, const int32 UsageTags = 0x00);` — Finds a matching render target from the pool, allocates a new one if one doesn't exist. Persists for the Owner object, until released.
- L40 _public prototype_ `bool ReleaseTarget(UTextureRenderTarget2D* Target);` — Returns a specified target to the pool. Assumes the assigned Owner is the one releasing (and taking care of any dangling refs).
- L43 _public prototype_ `void ReleaseAssignedTargets(UObject* Owner, const int32 KeepTags = 0x00);` — Returns all targets assigned to the specified Owner, back to the pool. Items in the optional RetainList will be kept.
- L44 _public prototype_ `void ReleaseTaggedTargets(const int32 TargetTags, UObject* Owner = nullptr);`
- L47 _public prototype_ `int32 FindAssignedUsageTags(UTextureRenderTarget2D* Target);`
- L50 _public prototype_ `int32 GetTargetCount() const;`
- L54 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L55 _public function_ `virtual FString GetReferencerName() const override`
- L63 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L64 _public prototype_ `virtual bool IsTickable() const override;`
- L65 _public prototype_ `virtual TStatId GetStatId() const override;`
- L70 _private prototype_ `void FlushUnusedTargetPool();`
- L71 _private prototype_ `void ForceRePoolAllTargets();`
- L72 _private prototype_ `void FlushAllTargets();`
- L75 _private prototype_ `void FlushStaleTargets();`
- L79 _private member_ `static FWeakTargetPoolPtr SharedInstance;`
- L81 _private member_ `TWeakObjectPtr<UObject> PoolOwner;`
- L89 _private function_ `friend uint32 GetTypeHash(const FRenderTargetDesc& InTargetDesc)`
- L99 _private function_ `friend bool operator==(UTextureRenderTarget2D* Lhs, const FPooledTarget& Rhs)`
- L106 _private member_ `TMultiMap<FRenderTargetDesc, FPooledTarget> RenderTargetPool;`
- L116 _private member_ `TMap<TObjectPtr<UTextureRenderTarget2D>, FTargetAssignee> AssignedTargets;`

#### struct `FCompElementRenderTargetPool::FRenderTargetDesc`  
`struct FRenderTargetDesc`  
_L83-90_
- L85 _public member_ `FIntPoint Dimensions;`
- L86 _public member_ `ETextureRenderTargetFormat Format;`
- L88 _public function_ `bool operator==(const FRenderTargetDesc& Rhs) const`

#### struct `FCompElementRenderTargetPool::FPooledTarget`  
`struct FPooledTarget`  
_L91-105_
- L93 _public function_ `FPooledTarget(UTextureRenderTarget2D* InTextureTarget) : TextureTarget(InTextureTarget)`
- L97 _public function_ `operator UTextureRenderTarget2D*()`
- L98 _public function_ `bool operator==(UTextureRenderTarget2D* Rhs) const`
- L102 _public member_ `int32 StaleFrameCount = 0;`
- L104 _public member_ `TObjectPtr<UTextureRenderTarget2D> TextureTarget = nullptr;`

#### struct `FCompElementRenderTargetPool::FTargetAssignee`  
`struct FTargetAssignee`  
_L108-115_
- L110 _public function_ `FTargetAssignee(UObject* AssigneeObj, int32 InUsageTags) : Assignee(AssigneeObj), UsageTags(InUsageTags)`
- L113 _public member_ `TWeakObjectPtr<UObject> Assignee;`
- L114 _public member_ `int32 UsageTags = 0x00;`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TSharedPtr<class FCompElementRenderTargetPool> FSharedTargetPoolPtr;`
- L20 _typedef_ `typedef TSharedRef<class FCompElementRenderTargetPool> FSharedTargetPoolRef;`
- L21 _typedef_ `typedef TWeakPtr< class FCompElementRenderTargetPool> FWeakTargetPoolPtr;`

### `Plugins/Compositing/Composure/Source/Composure/Private/CompositingElements/CompositingElementPassUtils.h` (Private)


#### class `FCompositingElementPassUtils`  
`class FCompositingElementPassUtils`  
_L17-40_
- L21 _public prototype_ `static void FillOutMID(UMaterialInterface* SrcMaterial, UMaterialInstanceDynamic*& TargetMID, UObject* MIDOuter = nullptr);`
- L24 _public prototype_ `static void FillOutMID(UMaterialInterface* SrcMaterial, TObjectPtr<UMaterialInstanceDynamic>& TargetMID, UObject* MIDOuter = nullptr);`
- L27 _public prototype_ `static void RenderMaterialToRenderTarget(UObject* WorldContextObj, UMaterialInterface* Material, UTextureRenderTarget2D* RenderTarget);`
- L31 _public prototype_ `template<typename T> static T* NewInstancedSubObj(UObject* Outer, UClass* Class = nullptr);`
- L34 _public prototype_ `static bool CopyToTarget(UObject* WorldContext, UTexture* Src, UTextureRenderTarget2D* Dst);`
- L37 _public prototype_ `static bool GetTargetFormatFromPixelFormat(const EPixelFormat PixelFormat, ETextureRenderTargetFormat& OutRTFormat);`
- L46 _function_ `template<typename T> T* FCompositingElementPassUtils::NewInstancedSubObj(UObject* Outer, UClass* Class)`

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposureConfigSettings.h` (Private)


#### class `UComposureGameSettings`  
`class UComposureGameSettings : public UObject`  
_L10-28_
- reflection: `UCLASS(config=Game)`
- inherits: `UObject`
- L16 _public member_ `FSoftObjectPath StaticVideoPlateDebugImage;` — `UPROPERTY(Config, BlueprintReadOnly, Category="Composure|Media")`
- L19 _public member_ `bool bSceneCapWarnOfMissingCam;` — `UPROPERTY(Config, BlueprintReadOnly, Category="Composure|Editor")`
- L22 _public member_ `FSoftObjectPath FallbackCompositingTexture;` — `UPROPERTY(Config, BlueprintReadOnly, Category="Composure")`
- L23 _public prototype_ `static UTexture* GetFallbackCompositingTexture();`
- L27 _private member_ `TObjectPtr<UTexture> FallbackCompositingTextureObj;` — `UPROPERTY(Transient)`

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposureCustomVersion.h` (Private)


#### struct `FComposureCustomVersion`  
`struct FComposureCustomVersion`  
_L9-28_
- desc: Custom serialization version for all packages containing Paper2D asset types
- L24 _public member_ `static const FGuid GUID;` — The GUID for this custom version number
- L27 _private function_ `FComposureCustomVersion()`

#### enum `FComposureCustomVersion::Type`  
`enum Type`  
_L11-21_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L16 _public enumerator_ `NewPassSystem`
- L19 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L20 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposureInternals.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define COMPOSURE_GET_MATERIAL(MaterialType,DestMemberName,MaterialDirName,MaterialFileName) \` — Macro to create a composure material and set it to <DestMemberName>.
- L16 _macro_ `#define COMPOSURE_CREATE_DYMAMIC_MATERIAL(MaterialType,DestMemberName,MaterialDirName,MaterialFileName) \` — Macro to create a composure dynamic material instance and set it to <DestMemberName>.
- L21 _macro_ `#define COMPOSURE_GET_TEXTURE(TextureType,DestMemberName,TextureDirName,TextureFileName) \`
- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(Composure, Log, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(Composure, Log, All);`

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposurePlayerCompositingCameraModifier.h` (Private)


#### class `UComposurePlayerCompositingCameraModifier`  
`class UComposurePlayerCompositingCameraModifier : public UCameraModifier , public IBlendableInterface`  
_L17-40_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UCameraModifier,IBlendableInterface`
- desc: Private camera manager for  UComposurePlayerCompositingTarget.
- L26 _public prototype_ `bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;` — Begins UCameraModifier
- L30 _public prototype_ `void OverrideBlendableSettings(class FSceneView& View, float Weight) const override;` — Begins IBlendableInterface
- L36 _private member_ `TScriptInterface<IComposurePlayerCompositingInterface> Target;` — `UPROPERTY(Transient)` — Current player camera manager the target is bind on.

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposurePostProcessBlendable.h` (Private)


#### class `UComposurePostProcessBlendable`  
`class UComposurePostProcessBlendable : public UObject , public IBlendableInterface`  
_L13-31_
- reflection: `UCLASS(NotBlueprintType)`
- inherits: `UObject,IBlendableInterface`
- desc: Private blendable interface for  UComposurePostProcessPass.
- L22 _public prototype_ `void OverrideBlendableSettings(class FSceneView& View, float Weight) const override;` — Begins IBlendableInterface
- L28 _private member_ `TObjectPtr<class UComposurePostProcessPass> Target;` — `UPROPERTY(Transient)` — Current player camera manager the target is bind on.

### `Plugins/Compositing/Composure/Source/Composure/Private/ComposureViewExtension.h` (Private)


#### class `FComposureViewExtension`  
`class FComposureViewExtension : public FSceneViewExtensionBase`  
_L13-26_
- inherits: `FSceneViewExtensionBase`
- L16 _public prototype_ `FComposureViewExtension(const FAutoRegister& AutoRegister, AComposurePipelineBaseActor* Owner);`
- L20 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L21 _public prototype_ `virtual int32 GetPriority() const override;`
- L22 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L25 _private member_ `TWeakObjectPtr<AComposurePipelineBaseActor> AssociatedPipelineObj;`

### `Plugins/Compositing/Composure/Source/Composure/Private/EditorSupport/CompositingEditorSupportLibrary.h` (Private)


#### class `UCompositingPickerAsyncTask`  
`class UCompositingPickerAsyncTask : public UBlueprintAsyncActionBase, public ICompImageColorPickerInterface`  
_L15-55_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase,ICompImageColorPickerInterface`
- L21 _public prototype_ `static UCompositingPickerAsyncTask* OpenCompositingPicker(UTextureRenderTarget2D* PickerTarget, UTexture* DisplayImage, FText WindowTitle, const bool bAverageColorOnDrag = true, const bool bUseImplicitGamma = true);` — `UFUNCTION(BlueprintCallable, Category="Composure|Editor", meta=(DevelopmentOnly, BlueprintInternalUseOnly = "true"))`
- L25 _public prototype_ `virtual UTexture* GetEditorPreviewImage() override;`
- L26 _public prototype_ `virtual UTexture* GetColorPickerDisplayImage() override;`
- L27 _public prototype_ `virtual UTextureRenderTarget2D* GetColorPickerTarget() override;`
- L28 _public prototype_ `virtual FCompFreezeFrameController* GetFreezeFrameController() override;`
- L29 _public function_ `virtual bool UseImplicitGammaForPreview() const override`
- L35 _public member_ `FOnPixelPicked OnPick;` — `UPROPERTY(BlueprintAssignable)`
- L38 _public member_ `FOnPixelPicked OnCancel;` — `UPROPERTY(BlueprintAssignable)`
- L41 _public member_ `FOnPixelPicked OnAccept;` — `UPROPERTY(BlueprintAssignable)`
- L44 _private prototype_ `void Open(UTextureRenderTarget2D* PickerTarget, UTexture* DisplayImage, const bool bAverageColorOnDrag, const FText& WindowTitle);`
- L46 _private prototype_ `void InternalOnPick(const FVector2D& PickedUV, const FLinearColor& PickedColor, bool bInteractive);`
- L47 _private prototype_ `void InternalOnCancel();`
- L50 _private member_ `TObjectPtr<UTextureRenderTarget2D> PickerTarget;` — `UPROPERTY(Transient)`
- L52 _private member_ `TObjectPtr<UTexture> PickerDisplayImage;` — `UPROPERTY(Transient)`
- L54 _private member_ `bool bUseImplicitGamma = true;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPixelPicked, const FVector2D&, PickedUV, const FLinearColor&, SampledColor);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPixelPicked, const FVector2D&, PickedUV, const FLinearColor&, SampledColor);`

### `Plugins/Compositing/Composure/Source/Composure/Private/MovieScene/MovieSceneComposureExportSectionTemplate.h` (Private)


#### class `UMovieSceneComposureExportInitializer`  
`class UMovieSceneComposureExportInitializer : public UObject`  
_L22-40_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Object passed to comp shot elements to initialize them for export. Currenly only allows scene captures to initialize a new extension that can capture GBuffers and other buffer visualization targets
- L32 _public prototype_ `void ExportSceneCaptureBuffers(ACompositingElement* CompShotElement, USceneCaptureComponent2D* SceneCapture, const TArray<FString>& BuffersToExport);` — `UFUNCTION(BlueprintCallable, Category="Composure|Export")` — Initialize the export to capture the specified named buffer visualization targets from a scene capture
- L35 _public prototype_ `TArray<TSharedPtr<FExportIntermediateBuffersViewExtension, ESPMode::ThreadSafe>> InitializeCompShotElement(ACompositingElement* CompShotElement);` — Implementation function
- L39 _private member_ `TArray<TSharedPtr<FExportIntermediateBuffersViewExtension, ESPMode::ThreadSafe>> TmpExtensions;`

#### struct `FMovieSceneComposureExportSectionTemplate`  
`struct FMovieSceneComposureExportSectionTemplate : public FMovieSceneEvalTemplate`  
_L45-58_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L49 _public function_ `FMovieSceneComposureExportSectionTemplate()`
- L50 _public prototype_ `FMovieSceneComposureExportSectionTemplate(const UMovieSceneComposureExportTrack& Track);`
- L53 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L54 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L57 _private member_ `FMovieSceneComposureExportPass Pass;` — `UPROPERTY()`

### `Plugins/Compositing/Composure/Source/Composure/Private/MovieScene/MovieSceneComposurePostMoveSettingsSectionTemplate.h` (Private)


#### struct `FMovieSceneComposurePostMoveSettingsSectionTemplate`  
`struct FMovieSceneComposurePostMoveSettingsSectionTemplate : public FMovieScenePropertySectionTemplate`  
_L17-43_
- reflection: `USTRUCT()`
- inherits: `FMovieScenePropertySectionTemplate`
- desc: A movie scene evaluation template for post move settings sections.
- L21 _public function_ `FMovieSceneComposurePostMoveSettingsSectionTemplate() : BlendType(EMovieSceneBlendType::Absolute)`
- L22 _public prototype_ `FMovieSceneComposurePostMoveSettingsSectionTemplate(const UMovieSceneComposurePostMoveSettingsSection& Section, const UMovieScenePropertyTrack& Track);`
- L25 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L27 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L30 _private member_ `FMovieSceneFloatChannel Pivot[2];` — `UPROPERTY()`
- L33 _private member_ `FMovieSceneFloatChannel Translation[2];` — `UPROPERTY()`
- L36 _private member_ `FMovieSceneFloatChannel RotationAngle;` — `UPROPERTY()`
- L39 _private member_ `FMovieSceneFloatChannel Scale;` — `UPROPERTY()`
- L42 _private member_ `EMovieSceneBlendType BlendType;` — `UPROPERTY()`

#### struct `TBlendableTokenTraits`  
`template<> struct TBlendableTokenTraits<FComposurePostMoveSettings>`  
_L47-50_
- L49 _public typedef_ `typedef UE::MovieScene::TMaskedBlendable<float, 6> WorkingDataType;`

#### Free symbols / members of external scopes

- L45 _prototype_ `template<> FMovieSceneAnimTypeID GetBlendingDataType<FComposurePostMoveSettings>();`
- L52 _namespace_ `namespace UE`
- L54 _namespace_ `namespace MovieScene` (scope `UE`)
- L56 _function_ `inline void MultiChannelFromData(const FComposurePostMoveSettings& In, TMultiChannelValue<float, 6>& Out)` (scope `UE::MovieScene`)
- L61 _function_ `inline void ResolveChannelsToData(const TMultiChannelValue<float, 6>& In, FComposurePostMoveSettings& Out)` (scope `UE::MovieScene`)

### `Plugins/Compositing/Composure/Source/Composure/Public/CompositingElements/CompositingMaterialPass.h` (Public)


#### struct `FCompositingParamPayload`  
`struct FCompositingParamPayload`  
_L19-34_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `TMap<FName, float> ScalarParamOverrides;` — `UPROPERTY()` — Map of scalar material parameter names to their corresponding override values
- L29 _public member_ `TMap<FName, FLinearColor> VectorParamOverrides;` — `UPROPERTY()` — Map of vector material parameter names to their corresponding override values
- L33 _public member_ `TMap<FName, TObjectPtr<UTexture>> TextureParamOverrides;` — `UPROPERTY()` — Map of texture material parameter names to their corresponding override values

#### enum `EParamType`  
`enum class EParamType : uint8`  
_L40-47_
- reflection: `UENUM()`
- L42 _public enumerator_ `UnknownParamType`
- L43 _public enumerator_ `ScalarParam`
- L44 _public enumerator_ `VectorParam`
- L45 _public enumerator_ `TextureParam`
- L46 _public enumerator_ `MediaTextureParam`

#### struct `FNamedCompMaterialParam`  
`struct FNamedCompMaterialParam`  
_L50-84_
- reflection: `USTRUCT(BlueprintType)`
- L54 _public function_ `FNamedCompMaterialParam(const FName InParamName = NAME_None) : ParamName(InParamName)`
- L57 _public function_ `FNamedCompMaterialParam(const TCHAR* InParamName) : ParamName(InParamName)`
- L63 _public member_ `EParamType ParamType = EParamType::UnknownParamType;` — `UPROPERTY(EditAnywhere, Category = "CompositingMaterial")`
- L67 _public member_ `FName ParamName;` — `UPROPERTY(EditAnywhere, Category = "CompositingMaterial", meta = (DisplayName = "Default Parameter Name"))`
- L70 _public function_ `operator FName()`
- L75 _public function_ `bool operator==(const FNamedCompMaterialParam& Rhs) const`

#### struct `FCompositingMaterial`  
`struct FCompositingMaterial : public FCompositingParamPayload`  
_L93-168_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FCompositingParamPayload`
- L98 _public prototype_ `FCompositingMaterial();`
- L101 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CompositingMaterial")`
- L105 _public member_ `TMap<FName, FName> ParamPassMappings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CompositingMaterial", meta = (ReadOnlyKeys, DisplayName = "Input Elements"))` — Maps material texture param names to prior passes/elements. Overrides the element's param mapping list above.
- L108 _public member_ `TMap<FName, FNamedCompMaterialParam> RequiredMaterialParams;` — `UPROPERTY(EditDefaultsOnly, Category = "CompositingMaterial", meta = (DisplayName="Expected Param Mappings"))`
- L112 _public prototype_ `bool ApplyParamOverrides(const ICompositingTextureLookupTable* TextureLookupTable);`
- L114 _public prototype_ `void ResetMaterial();`
- L116 _public prototype_ `void RenderToRenderTarget(UObject* WorldContext, UTextureRenderTarget2D* Target);`
- L119 _public prototype_ `bool SetMaterialParam(const FName ParamName, float ScalarValue);`
- L120 _public prototype_ `bool SetMaterialParam(const FName ParamName, FLinearColor VectorValue);`
- L121 _public prototype_ `bool SetMaterialParam(const FName ParamName, UTexture* TextureValue);`
- L124 _public prototype_ `void SetScalarOverride(const FName ParamName, const float ParamVal);`
- L125 _public prototype_ `bool GetScalarOverride(const FName ParamName, float& OutParamVal);`
- L126 _public prototype_ `void ResetScalarOverride(const FName ParamName);`
- L128 _public prototype_ `void SetVectorOverride(const FName ParamName, const FLinearColor ParamVal);`
- L129 _public prototype_ `bool GetVectorOverride(const FName ParamName, FLinearColor& OutParamVal);`
- L130 _public prototype_ `void ResetVectorOverride(const FName ParamName);`
- L133 _public prototype_ `void SetTextureOverride(const FName ParamName, UTexture* ParamVal);` — Set the override UTexture value for the named input material parameter
- L136 _public prototype_ `bool GetTextureOverride(const FName ParamName, UTexture*& OutParamVal);` — Get the override UTexture value for the named input material parameter
- L139 _public prototype_ `void ResetTextureOverride(const FName ParamName);` — Remove the override for the named input material parameter and reset its value to the default
- L141 _public prototype_ `void ResetAllParamOverrides();`
- L143 _public function_ `void MarkDirty()`
- L146 _public prototype_ `UMaterialInstanceDynamic* GetMID();`
- L152 _public member_ `TArray<FName> EditorHiddenParams;` — `UPROPERTY(EditDefaultsOnly, Category = "CompositingMaterial|Editor")`
- L155 _public prototype_ `void UpdateProxyMap();`
- L160 _private member_ `TMap<FName, FLinearColor> VectorOverrideProxies;` — `UPROPERTY(EditAnywhere, Category = "CompositingMaterial|Editor", meta=(ReadOnlyKeys))` — Required for customizing the color picker widget - need a property to wrap (one for each material param).
- L164 _private member_ `bool bParamsModified = true;`
- L167 _private member_ `TObjectPtr<UMaterialInstanceDynamic> CachedMID;` — `UPROPERTY(Transient, SkipSerialization)`

#### Free symbols / members of external scopes

- L80 _function_ `friend uint32 GetTypeHash(const FNamedCompMaterialParam& InNamedParam)`

### `Plugins/Compositing/Composure/Source/Composure/Public/CompositingElements/CompositingTextureLookupTable.h` (Public)


#### class `FCompositingTextureLookupTable`  
`class FCompositingTextureLookupTable : public ICompositingTextureLookupTable`  
_L11-56_
- inherits: `ICompositingTextureLookupTable`
- L14 _public function_ `virtual ~FCompositingTextureLookupTable()`
- L16 _public prototype_ `void RegisterPassResult(FName KeyName, UTexture* Result, const int32 UsageTags = 0x00);`
- L17 _public prototype_ `void SetMostRecentResult(UTexture* Result);`
- L19 _public prototype_ `void ResetAll();`
- L20 _public prototype_ `void Empty(const int32 KeepTags = 0x00);`
- L21 _public prototype_ `void ClearTaggedEntries(const int32 UsageTags, const bool bRemove = false);`
- L22 _public prototype_ `void Remove(UTexture* Texture);`
- L24 _public prototype_ `void LinkNestedSearchTable(FName KeyName, ICompositingTextureLookupTable* NestedLookupTable);`
- L25 _public prototype_ `void ClearLinkedSearchTables();`
- L27 _public prototype_ `int32 FindUsageTags(FName LookupName);`
- L31 _public prototype_ `virtual bool FindNamedPassResult(FName LookupName, UTexture*& OutTexture) const override;`
- L32 _public prototype_ `bool FindNamedPassResult(FName LookupName, bool bSearchLinkedTables, UTexture*& OutTexture) const;`
- L41 _private typedef_ `typedef TMap<FName, FTaggedTexture> FInternalLookupTable;`
- L42 _private member_ `FInternalLookupTable LookupTable;`
- L44 _private member_ `TMap<FName, ICompositingTextureLookupTable*> LinkedSearchTables;`
- L52 _public function_ `FORCEINLINE FInternalLookupTable::TRangedForIterator begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L53 _public function_ `FORCEINLINE FInternalLookupTable::TRangedForConstIterator begin() const`
- L54 _public function_ `FORCEINLINE FInternalLookupTable::TRangedForIterator end ()`
- L55 _public function_ `FORCEINLINE FInternalLookupTable::TRangedForConstIterator end () const`

#### struct `FCompositingTextureLookupTable::FTaggedTexture`  
`struct FTaggedTexture`  
_L36-40_
- L38 _public member_ `int32 UsageTags = 0x00;`
- L39 _public member_ `UTexture* Texture = nullptr;`

### `Plugins/Compositing/Composure/Source/Composure/Public/CompositingElements/InheritedCompositingTargetPool.h` (Public)


#### struct `FInheritedTargetPool`  
`struct FInheritedTargetPool`  
_L19-42_
- L22 _public prototype_ `FInheritedTargetPool(UObject* Owner, FIntPoint NativeTargetResolution, ETextureRenderTargetFormat NativeTargetFormat, const FSharedTargetPoolPtr& InheritedPool, int32 UsageTags = 0x00);`
- L23 _public function_ `FInheritedTargetPool()`
- L24 _public prototype_ `FInheritedTargetPool(FInheritedTargetPool& Other, FIntPoint NewTargetResolution, ETextureRenderTargetFormat NewTargetFormat);`
- L26 _public prototype_ `bool IsValid() const;`
- L27 _public prototype_ `void Reset();`
- L29 _public prototype_ `UTextureRenderTarget2D* RequestRenderTarget(float RenderScale = 1.f);`
- L30 _public prototype_ `UTextureRenderTarget2D* RequestRenderTarget(FIntPoint Dimensions, ETextureRenderTargetFormat Format);`
- L31 _public prototype_ `bool ReleaseRenderTarget(UTextureRenderTarget2D* UsedTarget);`
- L34 _private member_ `FWeakTargetPoolPtr InheritedPool;`
- L35 _private member_ `TWeakObjectPtr<UObject> Owner;`
- L38 _private member_ `int32 UsageTags = 0x00;`
- L40 _private member_ `FIntPoint NativeTargetResolution = FIntPoint(1920.f, 1080.f);`
- L41 _private member_ `ETextureRenderTargetFormat NativeTargetFormat = RTF_RGBA16f;`

#### struct `FScopedTargetPoolTagAddendum`  
`struct FScopedTargetPoolTagAddendum`  
_L47-56_
- L50 _public prototype_ `FScopedTargetPoolTagAddendum(int32 NewTags, FInheritedTargetPool& TargetPool);`
- L51 _public prototype_ `~FScopedTargetPoolTagAddendum();`
- L54 _private member_ `FInheritedTargetPool& TargetPool;`
- L55 _private member_ `int32 TagsToRestore = 0x00;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef TSharedPtr<FCompElementRenderTargetPool> FSharedTargetPoolPtr;`
- L17 _typedef_ `typedef TWeakPtr<FCompElementRenderTargetPool> FWeakTargetPoolPtr;`

### `Plugins/Compositing/Composure/Source/Composure/Public/ComposurePlayerCompositingInterface.h` (Public)


#### class `UComposurePlayerCompositingInterface`  
`class UComposurePlayerCompositingInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IComposurePlayerCompositingInterface`  
`class IComposurePlayerCompositingInterface`  
_L16-22_
- L21 _private function_ `virtual void OverrideBlendableSettings(class FSceneView& View, float Weight) const` — Entries called by PlayerCameraModifier.

### `Plugins/Compositing/Composure/Source/Composure/Public/ComposurePostMoves.h` (Public)


#### struct `FComposurePostMoveSettings`  
`struct FComposurePostMoveSettings`  
_L10-52_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public function_ `FComposurePostMoveSettings()`
- L24 _public member_ `FVector2D Pivot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Moves")` — The normalized pivot point for applying rotation and scale to the image. The x and y values are normalized to the range 0-1 where 1 represents the full width and height of the image.
- L28 _public member_ `FVector2D Translation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Moves")` — The translation to apply to the image.  The x and y values are normalized to the range 0-1 where 1 represents the full width and height of the image.
- L32 _public member_ `float RotationAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Moves")` — The anti clockwise rotation to apply to the image in degrees.
- L36 _public member_ `float Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Moves")` — The scale to apply to the image.
- L43 _public prototype_ `FMatrix GetProjectionMatrix(float HorizontalFOVAngle, float AspectRatio) const;` — Returns a non-centered projection matrix. @param HorizontalFOVAngle The desired horizontal FOV in degrees. @param AspectRatio The desired aspect ratio.
- L48 _public prototype_ `void GetCroppingUVTransformationMatrix( float AspectRatio, FMatrix* OutCropingUVTransformationMatrix, FMatrix* OutUncropingUVTransformationMatrix) const;` — Returns UV transformation matrix and its inversed to crop. @param AspectRatio The desired aspect ratio.

### `Plugins/Compositing/Composure/Source/Composure/Public/ComposureUVMap.h` (Public)


#### struct `FComposureUVMapSettings`  
`struct FComposureUVMapSettings`  
_L10-55_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public function_ `FComposureUVMapSettings() : PreUVDisplacementMatrix(FMatrix::Identity) , PostUVDisplacementMatrix(FMatrix::Identity) , DisplacementDecodeParameters(FVector2D(1, 0)) , DisplacementTexture(nullptr) , bUseDisplacementBlueAndAlphaChannels(false)`
- L24 _public member_ `FMatrix PreUVDisplacementMatrix;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Mapping")` — UV Matrix to apply before sampling DisplacementTexture.
- L28 _public member_ `FMatrix PostUVDisplacementMatrix;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Mapping")` — UV Matrix to apply after displacing UV using DisplacementTexture.
- L32 _public member_ `FVector2D DisplacementDecodeParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Mapping")` — Decoding parameters for DisplacementTexture. DeltaUV = ((RedChannel, GreenChannel) - Y) * X.
- L36 _public member_ `TObjectPtr<class UTexture> DisplacementTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Mapping")` — Displacement texture to use.
- L40 _public member_ `uint32 bUseDisplacementBlueAndAlphaChannels : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Mapping")` — Whether to use blue and alpha channel instead of red and green channel in computation of DeltaUV.
- L44 _public prototype_ `void SetMaterialParameters(class UMaterialInstanceDynamic* MID) const;` — Sets parameters of a material that uses MF_UVMap_SampleLocation material function.
- L51 _public function_ `static inline FVector2D InvertEncodingParameters(FVector2D EncodingParameters)` — Converts displacement encoding parameters to decoding parameters. Can also be used to convert displacement decoding parameters to encoding parameters.

### `Plugins/Compositing/Composure/Source/Composure/Public/ComposureUtils.h` (Public)


#### struct `FComposureUtils`  
`struct FComposureUtils`  
_L8-18_
- L12 _public prototype_ `static void SetEngineShowFlagsForPostprocessingOnly(struct FEngineShowFlags& InOutEngineShowflags);` — Disables the showflags to a scene capture post processing only.
- L16 _public prototype_ `static FVector2D GetRedGreenUVFactorsFromChromaticAberration(float ChromaticAberrationAmount);` — Returns the red and green channel fringe factors from percentage of chromatic aberration.

### `Plugins/Compositing/Composure/Source/Composure/Public/EditorSupport/CompEditorImagePreviewInterface.h` (Public)


#### class `UCompEditorImagePreviewInterface`  
`class UCompEditorImagePreviewInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ICompEditorImagePreviewInterface`  
`class ICompEditorImagePreviewInterface`  
_L18-29_
- L24 _public function_ `virtual void OnBeginPreview()`
- L25 _public prototype_ `virtual UTexture* GetEditorPreviewImage() = 0;`
- L26 _public function_ `virtual void OnEndPreview()`
- L27 _public prototype_ `virtual bool UseImplicitGammaForPreview() const = 0;`

### `Plugins/Compositing/Composure/Source/Composure/Public/EditorSupport/CompFreezeFrameController.h` (Public)


#### struct `FCompFreezeFrameController`  
`struct FCompFreezeFrameController`  
_L12-63_
- L15 _public function_ `FCompFreezeFrameController(int32& FreezeFlagsRef) : FreezeFlags(FreezeFlagsRef)`
- L19 _public function_ `FORCEINLINE bool IsLocked() const`
- L24 _public function_ `FFreezeFrameControlHandle Lock()`
- L34 _public function_ `FORCEINLINE bool Unlock(const FFreezeFrameControlHandle& InLockKey)`
- L43 _public function_ `FORCEINLINE ETargetUsageFlags GetFreezeFlags() const`
- L45 _public prototype_ `bool SetFreezeFlags(ETargetUsageFlags InFreezeFlags, bool bClearOthers = false, const FFreezeFrameControlHandle& LockKey = FFreezeFrameControlHandle());`
- L46 _public prototype_ `bool ClearFreezeFlags(ETargetUsageFlags InFreezeFlags, const FFreezeFrameControlHandle& LockKey = FFreezeFrameControlHandle());`
- L47 _public prototype_ `bool ClearFreezeFlags(const FFreezeFrameControlHandle& LockKey = FFreezeFrameControlHandle());`
- L49 _public function_ `FORCEINLINE operator ETargetUsageFlags() const`
- L50 _public function_ `FORCEINLINE operator int32()`
- L52 _public prototype_ `bool HasAnyFlags(ETargetUsageFlags InFreezeFlags);`
- L53 _public prototype_ `bool HasAllFlags(ETargetUsageFlags InFreezeFlags);`
- L56 _private member_ `FFreezeFrameControlHandle LockKey;`
- L57 _private member_ `int32& FreezeFlags;`
- L62 _public prototype_ `FCompFreezeFrameController(EForceInit Default = ForceInit);` — DO NOT USE - For UObject construction only

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef FGuid FFreezeFrameControlHandle;`

### `Plugins/Compositing/Composure/Source/Composure/Public/EditorSupport/CompImageColorPickerInterface.h` (Public)


#### class `UCompImageColorPickerInterface`  
`class UCompImageColorPickerInterface : public UCompEditorImagePreviewInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UCompEditorImagePreviewInterface`

#### class `ICompImageColorPickerInterface`  
`class ICompImageColorPickerInterface : public ICompEditorImagePreviewInterface`  
_L20-30_
- inherits: `ICompEditorImagePreviewInterface`
- L26 _public prototype_ `virtual UTexture* GetColorPickerDisplayImage() = 0;`
- L27 _public prototype_ `virtual UTextureRenderTarget2D* GetColorPickerTarget() = 0;`
- L28 _public prototype_ `virtual FCompFreezeFrameController* GetFreezeFrameController() = 0;`

### `Plugins/Compositing/Composure/Source/Composure/Public/EditorSupport/ICompositingEditor.h` (Public)


#### class `ICompositingEditor`  
`class ICompositingEditor : public IModularFeature`  
_L18-39_
- inherits: `IModularFeature`
- L21 _public function_ `static FName GetModularFeatureName()`
- L26 _public prototype_ `static ICompositingEditor* Get();`
- L29 _public prototype_ `DECLARE_DELEGATE_RetVal(UTexture*, FGetPreviewTexture);`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> ConstructCompositingPreviewPane(TWeakUIntrfacePtr<ICompEditorImagePreviewInterface> PreviewTarget) = 0;`
- L33 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FPickerResultHandler, const FVector2D& , const FLinearColor& , bool );`
- L34 _public prototype_ `virtual TSharedPtr<SWindow> RequestCompositingPickerWindow(TWeakUIntrfacePtr<ICompImageColorPickerInterface> PickerTarget, const bool bAverageColorOnDrag, const FPickerResultHandler& OnPick, const FSimpleDelegate& OnCancel, const FText& WindowTitle) = 0;`
- L37 _public prototype_ `virtual bool DeferCompositingDraw(ACompositingElement* CompElement) = 0;`
- L38 _public prototype_ `virtual void RequestRedraw() = 0;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_RetVal(UTexture*, FGetPreviewTexture);`
- L33 _delegate_ `DECLARE_DELEGATE_ThreeParams(FPickerResultHandler, const FVector2D& , const FLinearColor& , bool );`

### `Plugins/Compositing/Composure/Source/Composure/Public/EditorSupport/WeakUInterfacePtr.h` (Public)


#### class `TWeakUIntrfacePtr`  
`template<class T> class TWeakUIntrfacePtr`  
_L12-64_
- L15 _public function_ `TWeakUIntrfacePtr(UObject* InObject = nullptr) : Object(InObject)`
- L22 _public function_ `template<class U> TWeakUIntrfacePtr(const TWeakUIntrfacePtr<U>& Rhs)`
- L28 _public function_ `FORCEINLINE bool IsValid() const`
- L33 _public function_ `FORCEINLINE T* Get() const`
- L38 _public function_ `FORCEINLINE T& operator*() const`
- L44 _public function_ `FORCEINLINE T* operator->() const`
- L50 _public function_ `FORCEINLINE void Reset()`
- L56 _public function_ `FORCEINLINE TWeakObjectPtr<UObject> GetObject() const`
- L62 _private member_ `T* IntrefacePtr;`
- L63 _private member_ `TWeakObjectPtr<UObject> Object;`

### `Plugins/Compositing/Composure/Source/Composure/Public/IComposure.h` (Public)


#### class `IComposure`  
`class IComposure : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IComposure& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Compositing/Composure/Source/Composure/Public/MovieScene/IMovieSceneComposureExportClient.h` (Public)


#### class `UMovieSceneComposureExportClient`  
`class UMovieSceneComposureExportClient : public UInterface`  
_L16-20_
- reflection: `UINTERFACE(Category="Sequencer", Blueprintable, meta=(DisplayName = "Composure Export Client"))`
- inherits: `UInterface`

#### class `IMovieSceneComposureExportClient`  
`class IMovieSceneComposureExportClient`  
_L25-35_
- desc: Interface that can be implemented for any custom composure element to initialize it for export.
- L34 _public prototype_ `void InitializeForExport(UMovieSceneComposureExportInitializer* ExportInitializer);` — `UFUNCTION(BlueprintImplementableEvent, Category="Composure|Export")` — Initialize this object for export by setting up any of the necessary scene view extensions with the specified initializer.

### `Plugins/Compositing/Composure/Source/Composure/Public/MovieScene/MovieSceneComposureExportTrack.h` (Public)


#### struct `FMovieSceneComposureExportPass`  
`struct FMovieSceneComposureExportPass`  
_L15-30_
- reflection: `USTRUCT()`
- desc: Export configuration options for a single internal pass on an ACompositingElement, or its output pass (where TransformPassName is None)
- L21 _public member_ `FName TransformPassName;` — `UPROPERTY(EditAnywhere, Category="Export")` — The name of the transform pass in the comp to export. None signifies the element's output.
- L25 _public member_ `bool bRenamePass = false;` — `UPROPERTY(EditAnywhere, Category="Export", meta=(InlineEditConditionToggle))` — Whether to rename this pass when rendering out
- L29 _public member_ `FName ExportedAs;` — `UPROPERTY(EditAnywhere, Category="Export", meta=(EditCondition="bRenamePass"))` — The name to use for this pass when rendering out

#### class `UMovieSceneComposureExportTrack`  
`class UMovieSceneComposureExportTrack : public UMovieSceneTrack, public IMovieSceneTrackTemplateProducer`  
_L37-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneTrack,IMovieSceneTrackTemplateProducer`
- desc: Movie scene track that exports a single pass (either the element's output, or an internal transform pass) during burnouts
- L46 _public member_ `FMovieSceneComposureExportPass Pass;` — `UPROPERTY(EditAnywhere, Category="Export", meta=(ShowOnlyInnerProperties))` — Configuration options for the pass to export
- L49 _public prototype_ `UMovieSceneComposureExportTrack(const FObjectInitializer& ObjectInitializer);`
- L52 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L54 _public function_ `virtual bool IsEmpty() const override`
- L55 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L56 _public function_ `virtual void AddSection(UMovieSceneSection& Section) override`
- L57 _public function_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override`
- L58 _public function_ `virtual bool HasSection(const UMovieSceneSection& Section) const override`
- L59 _public function_ `virtual void RemoveSection(UMovieSceneSection& Section) override`
- L60 _public function_ `virtual void RemoveSectionAt(int32 SectionIndex) override`
- L61 _public function_ `virtual bool SupportsMultipleRows() const override`
- L62 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L65 _public prototype_ `virtual FText GetDisplayName() const override;`
- L71 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`

#### class `UMovieSceneComposureExportSection`  
`class UMovieSceneComposureExportSection : public UMovieSceneSection`  
_L75-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- L80 _public prototype_ `UMovieSceneComposureExportSection(const FObjectInitializer& ObjectInitializer);`

### `Plugins/Compositing/Composure/Source/Composure/Public/MovieScene/MovieSceneComposurePostMoveSettingsSection.h` (Public)


#### class `UMovieSceneComposurePostMoveSettingsSection`  
`class UMovieSceneComposurePostMoveSettingsSection : public UMovieSceneSection`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: A movie scene section for animating FComposurePostMoveSettings properties.
- L22 _public member_ `FMovieSceneFloatChannel Pivot[2];` — `UPROPERTY()` — The curves for animating the pivot property.
- L26 _public member_ `FMovieSceneFloatChannel Translation[2];` — `UPROPERTY()` — The curves for animating the translation property.
- L30 _public member_ `FMovieSceneFloatChannel RotationAngle;` — `UPROPERTY()` — The curve for animating the rotation angle property.
- L34 _public member_ `FMovieSceneFloatChannel Scale;` — `UPROPERTY()` — The curve for animating the scale property.

### `Plugins/Compositing/Composure/Source/Composure/Public/MovieScene/MovieSceneComposurePostMoveSettingsTrack.h` (Public)


#### class `UMovieSceneComposurePostMoveSettingsTrack`  
`class UMovieSceneComposurePostMoveSettingsTrack : public UMovieScenePropertyTrack, public IMovieSceneTrackTemplateProducer`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneTrackTemplateProducer`
- desc: A track for animating FComposurePostMoveSettings properties.
- L19 _public prototype_ `UMovieSceneComposurePostMoveSettingsTrack(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L24 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L25 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
