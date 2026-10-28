# Plugins / MovieSceneMixedControlRigEditor

- module root: `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRigEditor`
- headers: 2; symbols: 11
- symbol kinds: class=3, member=2, namespace=2, prototype=4
- PrivateDependencyModuleNames: ControlRig, ControlRigEditor, Core, CoreUObject, EditorFramework, Engine, LevelEditor, MovieScene, MovieSceneAnimMixer, MovieSceneTools, Sequencer, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRigEditor/Private/MixedControlRigBakeProvider.h` (Private)


#### class `FMixedControlRigBakeProvider`  
`class FMixedControlRigBakeProvider : public IMovieSceneAnimMixerBakeProvider`  
_L12-18_
- inherits: `IMovieSceneAnimMixerBakeProvider`
- desc: Concrete implementation of IMovieSceneAnimMixerBakeProvider. Delegates to UE::ControlRig::BuildBakeToControlRigMenu() and manages FControlRigEditMode activation after a successful bake.
- L15 _public prototype_ `virtual void BuildBakeToControlRigMenuSection( FMenuBuilder& MenuBuilder, const FAnimMixerBakeMenuParams& Params) override;`

### `Plugins/Experimental/MovieSceneMixedControlRig/Source/MovieSceneMixedControlRigEditor/Private/MovieSceneMixedControlRigEditorModule.h` (Private)


#### class `UE::MovieScene::FMixedControlRigLayerResolver`  
`class FMixedControlRigLayerResolver : public IMovieSceneEditingContextLayerResolver`  
_L14-20_
- inherits: `IMovieSceneEditingContextLayerResolver`
- L17 _public prototype_ `virtual UObject* ResolveEditingContextToMixerLayer( const UMovieSceneEntitySystemLinker* Linker, const UObject* EditingContext) const override;`

#### class `UE::MovieScene::FMovieSceneMixedControlRigEditorModule`  
`class FMovieSceneMixedControlRigEditorModule : public IModuleInterface`  
_L22-31_
- inherits: `IModuleInterface`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _private member_ `FMixedControlRigLayerResolver LayerResolver;`
- L30 _private member_ `TUniquePtr<FMixedControlRigBakeProvider> BakeProvider;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)
