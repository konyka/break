# Plugins / MovieSceneAnimMixerScripting

- module root: `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting`
- headers: 5; symbols: 34
- symbol kinds: class=5, function=2, macro=4, prototype=23
- PrivateDependencyModuleNames: CoreUObject, Engine, MovieSceneAnimMixer
- PublicDependencyModuleNames: Core, MovieScene, MovieSceneTracks

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting/Private/MovieSceneAnimMixerScriptingModule.h` (Private)


#### class `FMovieSceneAnimMixerScriptingModule`  
`class FMovieSceneAnimMixerScriptingModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public function_ `virtual void StartupModule() override`
- L11 _public function_ `virtual void ShutdownModule() override`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting/Public/MovieSceneAnimMixerLayerExtensions.h` (Public)


#### class `UMovieSceneAnimMixerLayerExtensions`  
`class UMovieSceneAnimMixerLayerExtensions : public UBlueprintFunctionLibrary`  
_L18-43_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that extend UMovieSceneAnimationMixerLayer for scripting.
- L26 _public prototype_ `static FText GetDisplayName(UMovieSceneAnimationMixerLayer* Layer);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod, DevelopmentOnly))` — Get the display name for this layer
- L30 _public prototype_ `static void SetDisplayName(UMovieSceneAnimationMixerLayer* Layer, const FText& InName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer", meta=(ScriptMethod, DevelopmentOnly))` — Set a custom display name for this layer
- L34 _public prototype_ `static int32 GetLayerIndex(UMovieSceneAnimationMixerLayer* Layer);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get the index of this layer within its parent mixer track
- L38 _public prototype_ `static TArray<UMovieSceneSection*> GetSections(UMovieSceneAnimationMixerLayer* Layer);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get all sections on this layer
- L42 _public prototype_ `static bool IsEmpty(UMovieSceneAnimationMixerLayer* Layer);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Check if this layer is empty (no sections and no child track)

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENEANIMMIXERSCRIPTING_API`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting/Public/MovieSceneAnimMixerTrackExtensions.h` (Public)


#### class `UMovieSceneAnimMixerTrackExtensions`  
`class UMovieSceneAnimMixerTrackExtensions : public UBlueprintFunctionLibrary`  
_L25-65_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that extend UMovieSceneAnimationMixerTrack for scripting.
- L33 _public prototype_ `static TArray<UMovieSceneAnimationMixerLayer*> GetLayers(UMovieSceneAnimationMixerTrack* Track);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get all layers in this mixer track
- L37 _public prototype_ `static int32 GetLayerCount(UMovieSceneAnimationMixerTrack* Track);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get the number of layers in this mixer track
- L41 _public prototype_ `static UMovieSceneAnimationMixerLayer* AddLayer(UMovieSceneAnimationMixerTrack* Track);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Add a new empty layer at the end
- L45 _public prototype_ `static UMovieSceneAnimationMixerLayer* InsertLayer(UMovieSceneAnimationMixerTrack* Track, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Insert a new empty layer at the specified index, shifting existing layers down
- L49 _public prototype_ `static UMovieSceneSection* AddAnimation(UMovieSceneAnimationMixerTrack* Track, int32 LayerIndex, FFrameNumber StartFrame, UAnimSequenceBase* AnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Add a skeletal animation to a specific layer at the given start frame
- L53 _public prototype_ `static TArray<UMovieSceneAnimTransitionSectionBase*> GetTransitionsForSection(UMovieSceneAnimationMixerTrack* Track, UMovieSceneSection* Section);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get all transition sections that reference the given section as either "from" or "to"
- L57 _public prototype_ `static UMovieSceneAnimTransitionSectionBase* GetTransitionBetween(UMovieSceneAnimationMixerTrack* Track, UMovieSceneSection* FromSection, UMovieSceneSection* ToSection);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Get the transition between two specific sections, or nullptr if none exists
- L63 _public prototype_ `static UMovieSceneTrack* AddChildTrackToLayer(UMovieSceneAnimationMixerTrack* Track, FGuid ObjectBinding, TSubclassOf<UMovieSceneTrack> TrackClass, int32 LayerIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer", meta=(ScriptMethod))` — Add a child track (e.g. Control Rig) to a specific layer. This is the UI operation of adding a track type to an empty mixer layer. The track will occupy the entire layer (layers support either sections or a child track, not both).

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MOVIESCENEANIMMIXERSCRIPTING_API`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting/Public/MovieSceneAnimMixerTransitionExtensions.h` (Public)


#### class `UMovieSceneAnimMixerTransitionExtensions`  
`class UMovieSceneAnimMixerTransitionExtensions : public UBlueprintFunctionLibrary`  
_L18-44_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that extend UMovieSceneAnimTransitionSectionBase for scripting.
- L26 _public prototype_ `static FText GetTransitionDisplayName(UMovieSceneAnimTransitionSectionBase* Transition);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer|Transition", meta=(ScriptMethod))` — Get the display name for this transition type
- L30 _public prototype_ `static bool IsTransitionValid(UMovieSceneAnimTransitionSectionBase* Transition);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer|Transition", meta=(ScriptMethod))` — Check if this transition is structurally valid (both sections exist, same row, overlap exists)
- L34 _public prototype_ `static UMovieSceneSection* GetFromSection(UMovieSceneAnimTransitionSectionBase* Transition);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer|Transition", meta=(ScriptMethod))` — Get the section this transition blends from
- L38 _public prototype_ `static UMovieSceneSection* GetToSection(UMovieSceneAnimTransitionSectionBase* Transition);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|AnimMixer|Transition", meta=(ScriptMethod))` — Get the section this transition blends to
- L43 _public prototype_ `static UMovieSceneAnimTransitionSectionBase* ChangeTransitionType(UMovieSceneAnimTransitionSectionBase* Transition, TSubclassOf<UMovieSceneAnimTransitionSectionBase> NewTransitionClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|AnimMixer|Transition", meta=(ScriptMethod))` — Replace this transition with a new one of the given class, preserving blend data where possible. Returns the new transition, or nullptr on failure.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENEANIMMIXERSCRIPTING_API`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixerScripting/Public/MovieSceneDecorationContainerExtensions.h` (Public)


#### class `UMovieSceneDecorationContainerExtensions`  
`class UMovieSceneDecorationContainerExtensions : public UBlueprintFunctionLibrary`  
_L18-43_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods that extend UMovieSceneDecorationContainerObject for scripting. Exposes the generic decoration API for discovering, adding, and removing decorations on any container.
- L26 _public prototype_ `static TArray<UClass*> GetCompatibleDecorations(UMovieSceneDecorationContainerObject* Container);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Decorations", meta=(ScriptMethod))` — Get all decoration classes that can be added to this container
- L30 _public prototype_ `static TArray<UObject*> GetDecorations(UMovieSceneDecorationContainerObject* Container);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Decorations", meta=(ScriptMethod))` — Get all decorations currently on this container
- L34 _public prototype_ `static UObject* FindDecoration(UMovieSceneDecorationContainerObject* Container, TSubclassOf<UObject> DecorationClass);` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Decorations", meta=(ScriptMethod))` — Find a decoration of a specific class on this container, or nullptr if not present
- L38 _public prototype_ `static UObject* AddDecoration(UMovieSceneDecorationContainerObject* Container, TSubclassOf<UObject> DecorationClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Decorations", meta=(ScriptMethod))` — Add a decoration by class. Returns the decoration (existing or newly created).
- L42 _public prototype_ `static void RemoveDecoration(UMovieSceneDecorationContainerObject* Container, TSubclassOf<UObject> DecorationClass);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Decorations", meta=(ScriptMethod))` — Remove a decoration by class

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENEANIMMIXERSCRIPTING_API`
