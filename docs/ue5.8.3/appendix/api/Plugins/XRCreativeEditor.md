# Plugins / XRCreativeEditor

- module root: `Plugins/Experimental/XRCreativeFramework/Source/XRCreativeEditor`
- headers: 3; symbols: 36
- symbol kinds: class=2, delegate=1, function=3, member=6, prototype=24
- PrivateDependencyModuleNames: EnhancedInput, HeadMountedDisplay, InputCore, InputEditor, InteractiveToolsFramework, LevelEditor, OpenXRHMD, OpenXRInput, RenderCore, Slate, SlateCore, UMG, UnrealEd, VREditor, XRCreative
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreativeEditor/Private/XRCreativeEditorModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreativeEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXRCreativeEditor, Log, All);`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreativeEditor/Private/XRCreativeVREditorMode.h` (Private)


#### class `UXRCreativeVREditorMode`  
`class UXRCreativeVREditorMode : public UVREditorModeBase`  
_L21-82_
- reflection: `UCLASS(Abstract)`
- inherits: `UVREditorModeBase`
- L26 _public prototype_ `UXRCreativeVREditorMode();`
- L29 _public prototype_ `virtual void Enter() override;`
- L30 _public prototype_ `virtual void Exit(bool bInShouldDisableStereo) override;`
- L31 _public function_ `virtual bool WantsToExitMode() const`
- L34 _public prototype_ `virtual FTransform GetRoomTransform() const override;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L37 _public prototype_ `virtual FTransform GetHeadTransform() const override;` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L39 _public prototype_ `virtual bool GetLaserForHand(EControllerHand InHand, FVector& OutLaserStart, FVector& OutLaserEnd) const override;`
- L43 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L44 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L48 _public prototype_ `void BP_OnEnter();` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Enter"))`
- L51 _public prototype_ `void BP_OnExit();` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Exit"))`
- L54 _public prototype_ `void BP_Tick(float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Tick"))`
- L57 _public prototype_ `void SetRoomTransform(const FTransform& RoomToWorld);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L60 _public prototype_ `void SetHeadTransform(const FTransform& HeadToWorld);` — `UFUNCTION(BlueprintCallable, Category="XR Creative")`
- L64 _protected prototype_ `virtual void EnableStereo() override;`
- L65 _protected prototype_ `virtual void DisableStereo() override;`
- L68 _protected prototype_ `bool ValidateSettings();`
- L70 _protected prototype_ `void InvalidSettingNotification(const FText& ErrorDetails);`
- L75 _protected member_ `TSoftObjectPtr<UXRCreativeToolset> ToolsetClass;` — `UPROPERTY(EditDefaultsOnly, Category="XR Creative")`
- L78 _protected member_ `TObjectPtr<AXRCreativeAvatar> Avatar;` — `UPROPERTY(BlueprintReadOnly, Category="XR Creative")`
- L80 _protected member_ `bool bWantsToExitMode = false;`
- L81 _protected member_ `bool bFirstTick = false;`

### `Plugins/Experimental/XRCreativeFramework/Source/XRCreativeEditor/Public/XRCreativeEditorUtilityToolActor.h` (Public)


#### class `AXRCreativeEditorUtilityToolActor`  
`class AXRCreativeEditorUtilityToolActor : public AXRCreativeToolActor`  
_L28-71_
- reflection: `UCLASS(Blueprintable, Abstract, meta = (ShowWorldContextPin))`
- inherits: `AXRCreativeToolActor`
- L34 _private prototype_ `void Run();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Editor")` — Standard function to execute
- L36 _private prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L38 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _private function_ `UInputComponent* GetInputComponent() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input|Editor")` — Returns the current InputComponent on this utility actor. This will be NULL unless bReceivesEditorInput is set to true.
- L49 _private prototype_ `void SetReceivesEditorInput(bool bInValue);` — `UFUNCTION(BlueprintSetter, Category = "Input|Editor")`
- L52 _private function_ `bool GetReceivesEditorInput() const` — `UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Input|Editor")`
- L60 _private prototype_ `void CreateEditorInput();` — Creates the EditorOnlyInputComponent if it does not already exist and registers all subobject callbacks to it
- L63 _private prototype_ `void RemoveEditorInput();` — Removes the EditorOnlyInputComponent from this utility actor
- L66 _private member_ `TObjectPtr<UInputComponent> EditorOnlyInputComponent;` — `UPROPERTY(Transient, DuplicateTransient)`
- L70 _private member_ `bool bReceivesEditorInput = false;` — `UPROPERTY(EditAnywhere, Category = "Input|Editor", BlueprintSetter = SetReceivesEditorInput, BlueprintGetter = GetReceivesEditorInput)` — If set to true, then this actor will be able to recieve input delegate callbacks when in the editor.
