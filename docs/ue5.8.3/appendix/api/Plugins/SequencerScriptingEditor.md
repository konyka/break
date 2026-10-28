# Plugins / SequencerScriptingEditor

- module root: `Plugins/MovieScene/SequencerScripting/Source/SequencerScriptingEditor`
- headers: 3; symbols: 73
- symbol kinds: class=3, delegate=2, function=8, macro=2, member=14, prototype=40, struct=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: BlueprintGraph, CoreUObject, CurveEditor, EditorFramework, Engine, Kismet, LevelSequence, MovieSceneCapture, PythonScriptPlugin, Sequencer, SequencerCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Core, MovieScene, MovieSceneCaptureDialog, MovieSceneTools, MovieSceneTracks, SequencerScripting, TimeManagement

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScriptingEditor/Public/SequencerCurveEditorObject.h` (Public)


#### struct `FSequencerChannelProxy`  
`struct FSequencerChannelProxy`  
_L20-38_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public function_ `FSequencerChannelProxy() : Section(nullptr)`
- L28 _public function_ `FSequencerChannelProxy(const FName& InChannelName, UMovieSceneSection* InSection) : ChannelName(InChannelName) , Section(InSection)`
- L34 _public member_ `FName ChannelName;` — `UPROPERTY(BlueprintReadWrite, Category = Channel)`
- L37 _public member_ `TObjectPtr<UMovieSceneSection> Section;` — `UPROPERTY(BlueprintReadWrite, Category = Channel)`

#### class `USequencerCurveEditorObject`  
`class USequencerCurveEditorObject : public UObject`  
_L45-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Class to hold sequencer curve editor functions
- L54 _public prototype_ `void OpenCurveEditor();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Open curve editor
- L58 _public prototype_ `bool IsCurveEditorOpen();` — Is curve editor open
- L62 _public prototype_ `void CloseCurveEditor();` — Close curve editor
- L65 _public prototype_ `void ApplyFilter(UCurveEditorFilterBase* Filter);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")`
- L71 _public prototype_ `TArray<FSequencerChannelProxy> GetChannelsWithSelectedKeys();` — `UFUNCTION(BlueprintPure, Category = "Sequencer Curve Editor")` — Gets the channel with selected keys
- L75 _public prototype_ `TArray<int32> GetSelectedKeys(const FSequencerChannelProxy& ChannelProxy);` — `UFUNCTION(BlueprintPure, Category = "Sequencer Curve Editor")` — Gets the selected keys with this channel
- L79 _public prototype_ `void ShowCurve(const FSequencerChannelProxy& Channel, bool bShowCurve);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Show curve
- L83 _public prototype_ `bool IsCurveShown(const FSequencerChannelProxy& Channel);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Is the curve displayed
- L87 _public prototype_ `void SelectKeys(const FSequencerChannelProxy& Channel, const TArray<int32>& Indices);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Select keys
- L91 _public prototype_ `void EmptySelection();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Empties the current selection.
- L97 _public prototype_ `bool HasCustomColorForChannel(UClass* Class, const FString& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Get if a custom color for specified channel idendified by it's class and identifier exists
- L101 _public prototype_ `FLinearColor GetCustomColorForChannel(UClass* Class, const FString& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Get custom color for specified channel idendified by it's class and identifier,if none exists will return white
- L105 _public prototype_ `void SetCustomColorForChannel(UClass* Class, const FString& Identifier, const FLinearColor& NewColor);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Set Custom Color for specified channel idendified by it's class and identifier. This will be stored in editor user preferences.
- L109 _public prototype_ `void SetCustomColorForChannels(UClass* Class, const TArray<FString>& Identifiers, const TArray<FLinearColor>& NewColors);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Set Custom Color for specified channels idendified by it's class and identifiers. This will be stored in editor user preferences.
- L113 _public prototype_ `void SetRandomColorForChannels(UClass* Class, const TArray<FString>& Identifiers);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Set Random Colors for specified channels idendified by it's class and identifiers. This will be stored in editor user preferences.
- L117 _public prototype_ `void DeleteColorForChannels(UClass* Class, FString& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer Curve Editor")` — Delete for specified channel idendified by it's class and identifier.
- L125 _public prototype_ `void SetSequencer(TSharedPtr<ISequencer>& InSequencer);` — Function to assign a sequencer singleton. NOTE: Only to be called by ULevelSequenceBlueprintLibrary::SetSequencer.
- L132 _public prototype_ `TOptional<FCurveModelID> GetCurve(UMovieSceneSection* InSection, const FName& InName);` — Utility function to get curve, if it exists,  from a section and a name
- L137 _public prototype_ `TSharedPtr<FCurveEditor> GetCurveEditor();` — Utility function to get curve editor
- L141 _private member_ `TWeakPtr<ISequencer> CurrentSequencer;` — internal sequencer

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCERSCRIPTINGEDITOR_API`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScriptingEditor/Public/SequencerScriptingEditor.h` (Public)


#### class `FSequencerScriptingEditorModule`  
`class FSequencerScriptingEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MovieScene/SequencerScripting/Source/SequencerScriptingEditor/Public/SequencerTools.h` (Public)


#### struct `FSequencerBoundObjects`  
`struct FSequencerBoundObjects`  
_L39-56_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public function_ `FSequencerBoundObjects()`
- L46 _public function_ `FSequencerBoundObjects(FMovieSceneBindingProxy InBindingProxy, const TArray<UObject*>& InBoundObjects) : BindingProxy(InBindingProxy) , BoundObjects(InBoundObjects)`
- L52 _public member_ `FMovieSceneBindingProxy BindingProxy;` — `UPROPERTY(BlueprintReadWrite, Category=Binding)`
- L55 _public member_ `TArray<TObjectPtr<UObject>> BoundObjects;` — `UPROPERTY(BlueprintReadWrite, Category=Binding)`

#### struct `FSequencerQuickBindingResult`  
`struct FSequencerQuickBindingResult`  
_L60-74_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper around result of quick binding for event track in sequencer.
- L64 _public function_ `FSequencerQuickBindingResult() : EventEndpoint(nullptr)`
- L68 _public member_ `TObjectPtr<UK2Node_CustomEvent> EventEndpoint;` — `UPROPERTY()` — Actual endpoint wrapped by this structure.
- L72 _public member_ `TArray<FString> PayloadNames;` — `UPROPERTY(BlueprintReadOnly, Category = Data)` — Names of the payload variables of the event.

#### struct `FSequencerExportFBXParams`  
`struct FSequencerExportFBXParams`  
_L77-111_
- reflection: `USTRUCT(BlueprintType)`
- L81 _public function_ `FSequencerExportFBXParams()`
- L82 _public function_ `FSequencerExportFBXParams(UWorld* InWorld, ULevelSequence* InSequence, ULevelSequence* InRootSequence, const TArray<FMovieSceneBindingProxy>& InBindings, const TArray<UMovieSceneTrack*>& InTracks, UFbxExportOption* InOverrideOptions, const FString& InFBXFileName) : World(InWorld) , Sequence(InSequence) , RootSequence(InRootSequence) , Bindings(InBindings) , Tracks(InTracks) , OverrideOptions(InOverrideOptions) , FBXFileName(InFBXFileName)`
- L92 _public member_ `TObjectPtr<UWorld> World;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L95 _public member_ `TObjectPtr<ULevelSequence> Sequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L98 _public member_ `TObjectPtr<ULevelSequence> RootSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L101 _public member_ `TArray<FMovieSceneBindingProxy> Bindings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L104 _public member_ `TArray<TObjectPtr<UMovieSceneTrack>> Tracks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L107 _public member_ `TObjectPtr<UFbxExportOption> OverrideOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`
- L110 _public member_ `FString FBXFileName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movie Scene")`

#### class `USequencerToolsFunctionLibrary`  
`class USequencerToolsFunctionLibrary : public UBlueprintFunctionLibrary`  
_L118-297_
- reflection: `UCLASS(MinimalAPI, Transient, meta=(ScriptName="SequencerTools"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: This is a set of helper functions to access various parts of the Sequencer API via Python. Because Sequencer itself is not suitable for exposing, most functionality gets wrapped by UObjects that have an easier API to work with. This UObject provides access to these wrapper UObjects where needed.
- L130 _public prototype_ `static bool RenderMovie(class UMovieSceneCapture* InCaptureSettings, FOnRenderMovieStopped OnFinishedCallback);` — `UE_DEPRECATED(5.3, "SequencerTools::RenderMovie has been deprecated, please use Movie Render Queue")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Movie Rendering", meta=(DeprecatedFunction))` — Attempts to render a sequence to movie based on the specified settings. This will automatically detect if we're rendering via a PIE instance or a new process based on the passed in settings. Will return false if the state is not valid (ie: null or missing required parameters, capture in progress, etc.), true otherwise.
- L137 _public function_ `static bool IsRenderingMovie()` — `UE_DEPRECATED(5.3, "SequencerTools::IsRenderingMovie has been deprecated, please use Movie Render Queue")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Movie Rendering", meta=(DeprecatedFunction))` — Returns if Render to Movie is currently in progress.
- L148 _public prototype_ `static void CancelMovieRender();` — `UE_DEPRECATED(5.3, "SequencerTools::CancelMovieRender has been deprecated, please use Movie Render Queue")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Movie Rendering", meta=(DeprecatedFunction))` — Attempts to cancel an in-progress Render to Movie. Does nothing if there is no render in progress.
- L158 _public prototype_ `static TArray<FSequencerBoundObjects> GetBoundObjects(UWorld* InWorld, ULevelSequence* InSequence, const TArray<FMovieSceneBindingProxy>& InBindings, const FSequencerScriptingRange& InRange);` — `UE_DEPRECATED(5.3, "SequencerTools::GetBoundObjects has been deprecated because it doesn't work with Spawnables, please use ULevelSequenceEditorBlueprintLibrary::GetBoundObjects which operates on the currently opened sequence in Editor")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools", meta=(DeprecatedFunction))` — Retrieve all objects currently bound to the specified binding identifiers. The sequence will be evaluated in lower bound of the specified range, which allows for retrieving spawnables in that period of time.
- L166 _public prototype_ `static TArray<FSequencerBoundObjects> GetObjectBindings(UWorld* InWorld, ULevelSequence* InSequence, const TArray<UObject*>& InObject, const FSequencerScriptingRange& InRange);` — `UE_DEPRECATED(5.3, "SequencerTools::GetObjectBindings has been deprecated because it doesn't work with Spawnables, please use ULevelSequenceEditorBlueprintLibrary::GetObjectBindings which operates on the currently opened sequence in Editor")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools", meta=(DeprecatedFunction))` — Get the object bindings for the requested object. The sequence will be evaluated in lower bound of the specified range, which allows for retrieving spawnables in that period of time.
- L174 _public prototype_ `static bool ExportLevelSequenceFBX(const FSequencerExportFBXParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Export Passed in Bindings and Tracks to FBX
- L190 _public prototype_ `static bool ExportAnimSequence(UWorld* World, ULevelSequence* Sequence, UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOptions, const FMovieSceneBindingProxy& Binding, bool bCreateLink);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Export Passed in Binding as an Anim Sequence. Note use this when you want to export without an open Level Sequence in Sequencer, and know that all spawnables that may be dynamically created and destroyed will be valid. If the spawnable won't be fully created and you have an open Sequencer use UControlRigSequencerEditorLibrary::ExportAnimSequenceFromSequencer instead. @InWorld World to export @InSequence Sequence to export @AnimSequence The AnimSequence to save into. @ExportOption The export options for the sequence. @InBinding Binding to export that has a skelmesh component on it @InAnimSequenceFilename File to create @bCreateLink If true will create a link between the animation sequence and the level sequence
- L196 _public prototype_ `static bool ExportAnimSequenceWaitForDelegate(UWorld* World, ULevelSequence* Sequence, UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOptions, const FMovieSceneBindingProxy& Binding, bool bCreateLink, const FCheckCanCompleteDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Version of ExportAnimSequence, which will spawn in all actors in the sequence and then wait for the provided Delegate to return true before exporting.
- L207 _public prototype_ `static bool LinkAnimSequence(ULevelSequence* Sequence, UAnimSequence* AnimSequence, const UAnimSeqExportOption* ExportOptions, const FMovieSceneBindingProxy& Binding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Links a LevelSequence's SkeletalMesh binding to an existing anim sequence. @InSequence Sequence to link from @AnimSequence The AnimSequence to link to. @ExportOption The export options that should be used when baking the LevelSequence. @InBinding Binding that has a skelmesh component on it
- L215 _public prototype_ `static void ClearLinkedAnimSequences(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Clear all linked anim sequences between this level sequence and any linked anim sequences @InLevelSequence LevelSequence to clean links for
- L224 _public prototype_ `static UAnimSequenceLevelSequenceLink* GetLevelSequenceLinkFromAnimSequence(UAnimSequence* InAnimSequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Get the link to the level sequence if it exists on this anim sequence @InAnimSequence AnimSequence to get links from @return Returns the link object if it exists, nullptr if it doesn't
- L233 _public prototype_ `static ULevelSequenceAnimSequenceLink* GetAnimSequenceLinkFromLevelSequence(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Get the links to the anim sequences if they exist on this level sequence @InLevelSequence LevelSequence to get links from @return Returns the link object if it exists, nullptr if it doesn't
- L246 _public prototype_ `static bool ImportLevelSequenceFBX(UWorld* InWorld, ULevelSequence* InSequence, const TArray<FMovieSceneBindingProxy>& InBindings, UMovieSceneUserImportFBXSettings* InImportFBXSettings, const FString& InImportFilename, ALevelSequenceActor* ActorContext = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Import FBX onto Passed in Bindings @InWorld World to import to @InSequence InSequence to import @InBindings InBindings to import @InImportFBXSettings Settings to control import. @InImportFileName Path to fbx file to import from @InPlayer Player to bind to
- L260 _public prototype_ `static FMovieSceneEvent CreateEvent(UMovieSceneSequence* InSequence, UMovieSceneEventSectionBase* InSection, const FSequencerQuickBindingResult& InEndpoint, const TArray<FString>& InPayload);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Create an event from a previously created blueprint endpoint and a payload. The resulting event should be added only to a channel of the section that was given as a parameter. @param InSequence Main level sequence that holds the event track and to which the resulting event should be added. @param InSection Section of the event track of the main sequence. @param InEndpoint Previously created endpoint. @param InPayload Values passed as payload to event, count must match the numbers of payload variable names in @InEndpoint. @return The created movie event. @see CreateQuickBinding
- L267 _public prototype_ `static bool IsEventEndpointValid(const FSequencerQuickBindingResult& InEndpoint);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Check if an endpoint is valid and can be used to create movie scene event. @param InEndpoint Endpoint to check.
- L277 _public prototype_ `static FSequencerQuickBindingResult CreateQuickBinding(UMovieSceneSequence* InSequence, UObject* InObject, const FString& InFunctionName, bool bCallInEditor);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Create a quick binding to an actor's member method to be used in an event sequence. @param InActor Actor that will be bound @param InFunctionName Name of the method, as it is displayed in the Blueprint Editor. eg. "Set Actor Scale 3D" @param bCallInEditor Should the event be callable in editor. @return The created binding.
- L290 _public prototype_ `static bool ImportFBXToControlRig(UWorld* World, ULevelSequence* InSequence, const FString& ActorWithControlRigTrack, const TArray<FString>& SelectedControlRigNames, UMovieSceneUserImportFBXControlRigSettings* ImportFBXControlRigSettings, const FString& ImportFilename);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Import FBX onto a control rig with the specified track name @InWorld World to import to @InSequence InSequence to import @ActorWithControlRigTrack ActorWithControlRigTrack The name of the actor with the control rig track we are importing onto @SelectedControlRigNames  List of selected control rig names. Will use them if  ImportFBXControlRigSettings->bImportOntoSelectedControls is true @ImportFBXControlRigSettings Settings to control import. @InImportFileName Path to fbx file to create
- L296 _public prototype_ `static bool ExportFBXFromControlRig(ULevelSequence* Sequence, const FString& ActorWithControlRigTrack, const UMovieSceneUserExportFBXControlRigSettings* ExportFBXControlRigSettings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Exports an FBX from the section to key of the control rig track of the actor with the given name.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCERSCRIPTINGEDITOR_API`
- L34 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRenderMovieStopped, bool, bSuccess);`
- L34 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRenderMovieStopped, bool, bSuccess);`
- L35 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FCheckCanCompleteDelegate);`
- L35 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FCheckCanCompleteDelegate);`
