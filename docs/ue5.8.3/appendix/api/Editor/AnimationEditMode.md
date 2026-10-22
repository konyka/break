# Editor / AnimationEditMode

- module root: `Source/Editor/AnimationEditMode`
- headers: 2; symbols: 21
- symbol kinds: class=4, function=4, macro=1, member=2, prototype=10
- PrivateDependencyModuleNames: Core, CoreUObject, EditorInteractiveToolsFramework, Engine, InteractiveToolsFramework, UnrealEd

### `Source/Editor/AnimationEditMode/Public/AnimationEditContext.h` (Public)


#### class `UAnimationEditContext`  
`class UAnimationEditContext : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAnimationEditContext`  
`class IAnimationEditContext`  
_L16-37_
- L25 _public function_ `virtual bool GetCameraTarget(FSphere& OutTarget) const` — Get a camera target used to focus the viewport on an object when a user presses 'F' (default). @param	 OutTarget	 The target object @return true if the target sphere was filled-in
- L28 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const = 0;` — @return the anim preview scene
- L36 _public function_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const` — Function to collect strings from nodes to display in the viewport. Use this rather than DrawHUD when adding general text to the viewport. Display of this assumes that this will be mostly used by skeletal controls. @param	OutDebugInfo	Text to display

### `Source/Editor/AnimationEditMode/Public/AnimationEditMode.h` (Public)


#### class `UAnimationEditModeContext`  
`class UAnimationEditModeContext : public UObject, public IAnimationEditContext`  
_L27-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IAnimationEditContext`
- desc: A compatibility context object to support IPersonaEditMode-based code. It simply calls into a different IAnimationEditContext in its implementations.
- L31 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;`
- L32 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L33 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L35 _private member_ `IAnimationEditContext* EditMode = nullptr;`
- L36 _private function_ `static UAnimationEditModeContext* CreateFor(IAnimationEditContext* InEditMode)`

#### class `FAnimationEditMode`  
`class FAnimationEditMode : public FEdMode, public IAnimationEditContext`  
_L45-60_
- inherits: `FEdMode,IAnimationEditContext`
- L48 _public prototype_ `FAnimationEditMode();`
- L50 _public prototype_ `FAnimationEditMode(const FAnimationEditMode&) = delete;`
- L51 _public prototype_ `FAnimationEditMode& operator=(const FAnimationEditMode&) = delete;`
- L53 _public prototype_ `virtual void Enter() override;`
- L54 _public prototype_ `virtual void Exit() override;`
- L55 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L57 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L59 _private member_ `TObjectPtr<UAnimationEditModeContext> AnimationEditModeContext;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API ANIMATIONEDITMODE_API`
