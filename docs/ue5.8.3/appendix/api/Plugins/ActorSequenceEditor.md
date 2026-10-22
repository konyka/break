# Plugins / ActorSequenceEditor

- module root: `Plugins/MovieScene/ActorSequence/Source/ActorSequenceEditor`
- headers: 4; symbols: 31
- symbol kinds: class=3, function=8, member=7, prototype=11, struct=2
- PrivateDependencyModuleNames: ActorSequence, BlueprintGraph, ClassViewer, Core, CoreUObject, EditorFramework, Engine, InputCore, Kismet, MovieScene, MovieSceneTools, Sequencer, Slate, SlateCore, SubobjectDataInterface, SubobjectEditor, TimeManagement, ToolMenus, UnrealEd

### `Plugins/MovieScene/ActorSequence/Source/ActorSequenceEditor/Private/ActorSequenceComponentCustomization.h` (Private)


#### class `FActorSequenceComponentCustomization`  
`class FActorSequenceComponentCustomization : public IDetailCustomization`  
_L19-35_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _private prototype_ `FReply InvokeSequencer();`
- L29 _private prototype_ `UActorSequence* GetActorSequence() const;`
- L31 _private member_ `TWeakObjectPtr<UActorSequenceComponent> WeakSequenceComponent;`
- L32 _private member_ `TWeakPtr<FTabManager> WeakTabManager;`
- L33 _private member_ `TSharedPtr<SBox> InlineSequencer;`
- L34 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

### `Plugins/MovieScene/ActorSequence/Source/ActorSequenceEditor/Private/ActorSequenceEditorStyle.h` (Private)


#### class `FActorSequenceEditorStyle`  
`class FActorSequenceEditorStyle final : public FSlateStyleSet`  
_L11-37_
- inherits: `FSlateStyleSet`
- L15 _public function_ `FActorSequenceEditorStyle() : FSlateStyleSet("ActorSequenceEditorStyle")`
- L27 _public function_ `static FActorSequenceEditorStyle& Get()`
- L33 _public function_ `~FActorSequenceEditorStyle()`

### `Plugins/MovieScene/ActorSequence/Source/ActorSequenceEditor/Private/ActorSequenceEditorTabSummoner.h` (Private)


#### class `SActorSequenceEditorWidget`  
`class SActorSequenceEditorWidget : public SCompoundWidget`  
_L15-31_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SActorSequenceEditorWidget)`
- L21 _public prototype_ `SLATE_END_ARGS();`
- L23 _public prototype_ `void Construct(const FArguments&, TWeakPtr<FBlueprintEditor> InBlueprintEditor);`
- L24 _public prototype_ `void AssignSequence(UActorSequence* NewActorSequence);`
- L25 _public prototype_ `UActorSequence* GetSequence() const;`
- L26 _public prototype_ `FText GetDisplayLabel() const;`
- L30 _private member_ `TWeakPtr<SActorSequenceEditorWidgetImpl> Impl;`

#### struct `FActorSequenceEditorSummoner`  
`struct FActorSequenceEditorSummoner : public FWorkflowTabFactory`  
_L34-45_
- inherits: `FWorkflowTabFactory`
- L37 _public prototype_ `FActorSequenceEditorSummoner(TSharedPtr<FBlueprintEditor> BlueprintEditor);`
- L39 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L43 _protected member_ `TWeakObjectPtr<UActorSequenceComponent> WeakComponent;`
- L44 _protected member_ `TWeakPtr<FBlueprintEditor> WeakBlueprintEditor;`

### `Plugins/MovieScene/ActorSequence/Source/ActorSequenceEditor/Private/MovieSceneSequenceEditor_ActorSequence.h` (Private)


#### struct `FMovieSceneSequenceEditor_ActorSequence`  
`struct FMovieSceneSequenceEditor_ActorSequence : FMovieSceneSequenceEditor`  
_L14-63_
- inherits: `FMovieSceneSequenceEditor`
- L16 _public function_ `virtual bool CanCreateEvents(UMovieSceneSequence* InSequence) const`
- L21 _public function_ `virtual bool CanCreateDirectorBlueprint(UMovieSceneSequence* Sequence) const override`
- L37 _public function_ `virtual UBlueprint* GetBlueprintForSequence(UMovieSceneSequence* InSequence) const override`
- L52 _public function_ `virtual UBlueprint* CreateBlueprintForSequence(UMovieSceneSequence* InSequence) const override`
