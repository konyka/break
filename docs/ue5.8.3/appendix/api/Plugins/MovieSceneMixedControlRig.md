# Plugins / MovieSceneMixedControlRig

- module root: `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRig`
- headers: 2; symbols: 10
- symbol kinds: class=2, namespace=2, prototype=6
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationCore, ControlRig, Core, CoreUObject, DeveloperSettings, Engine, MovieScene, MovieSceneAnimMixer, MovieSceneTracks, RigVM, UAF, UAFAnimGraph, UAFControlRig

### `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRig/Public/MovieSceneMixedControlRigModule.h` (Public)


#### class `UE::MovieScene::FMovieSceneMixedControlRigModule`  
`class FMovieSceneMixedControlRigModule : public IModuleInterface`  
_L13-18_
- inherits: `IModuleInterface`
- L16 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L17 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieSceneMixedControlRig, Log, All);`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRig/Public/Systems/MovieSceneMixedControlRigSystem.h` (Public)


#### class `UMovieSceneMixedControlRigSystem`  
`class UMovieSceneMixedControlRigSystem : public UMovieSceneEntityInstantiatorSystem`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System to handle creating evaluation tasks from control rig tracks for the anim mixer.
- L17 _public prototype_ `UMovieSceneMixedControlRigSystem(const FObjectInitializer& ObjInit);`
- L21 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L22 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
