# Plugins / ComposureEditor

- module root: `Plugins/Compositing/Composure/Source/ComposureEditor`
- headers: 4; symbols: 44
- symbol kinds: class=3, delegate=3, function=3, member=7, prototype=28
- PrivateDependencyModuleNames: Composure, DesktopWidgets, EditorFramework, EditorWidgets, Layers, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore

### `Plugins/Compositing/Composure/Source/ComposureEditor/Private/Sequencer/ComposureExportTrackEditor.h` (Private)


#### class `FComposureExportTrackEditor`  
`class FComposureExportTrackEditor : public FKeyframeTrackEditor<UMovieSceneComposureExportTrack>`  
_L8-27_
- inherits: `FKeyframeTrackEditor<UMovieSceneComposureExportTrack>`
- L12 _public prototype_ `FComposureExportTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L13 _public prototype_ `~FComposureExportTrackEditor();`
- L17 _private prototype_ `virtual FText GetDisplayName() const override;`
- L18 _private prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L19 _private prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L20 _private prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L21 _private prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L23 _private prototype_ `void HandleActorAdded(AActor* Actor, FGuid TargetObjectGuid);`
- L24 _private prototype_ `void AddNewTrack(TArray<FGuid> ObjectBindings, FName InPassName, bool bRenamePass, FName ExportAs);`
- L26 _private member_ `FDelegateHandle OnActorAddedToSequencerHandle;`

### `Plugins/Compositing/Composure/Source/ComposureEditor/Private/Sequencer/ComposurePostMoveSettingsPropertyTrackEditor.h` (Private)


#### class `FComposurePostMoveSettingsPropertyTrackEditor`  
`class FComposurePostMoveSettingsPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneComposurePostMoveSettingsTrack>`  
_L9-59_
- inherits: `FPropertyTrackEditor<UMovieSceneComposurePostMoveSettingsTrack>`
- desc: A property track editor for FComposurePostMoveSettings properties.
- L14 _public function_ `FComposurePostMoveSettingsPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L25 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L35 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L44 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L49 _private prototype_ `void ShowImportPostMoveSettingsDialog(UMovieSceneComposurePostMoveSettingsTrack* PostMoveSettingsTrack);` — Shows a dialog for importing post move animation from an external file.
- L52 _private prototype_ `void ImportPostMoveSettings(FString ImportFilePath, FFrameRate FrameRate, FFrameNumber StartFrame, UMovieSceneComposurePostMoveSettingsTrack* PostMoveSettingsTrack);` — Imports post move settings from an external file to the specified track with the specified settings.
- L55 _private prototype_ `void ImportCanceled();` — Handles closing the import settings dialog when the import it canceled.
- L58 _private member_ `TWeakPtr<SWindow> ImportDialog;`

### `Plugins/Compositing/Composure/Source/ComposureEditor/Private/Sequencer/SComposurePostMoveSettingsImportDialog.h` (Private)


#### class `SComposurePostMoveSettingsImportDialog`  
`class SComposurePostMoveSettingsImportDialog : public SWindow`  
_L9-53_
- inherits: `SWindow`
- desc: A dialog for collecting settings for importing post move settings from an external file.
- L12 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnImportSelected, FString, FFrameRate, FFrameNumber);`
- L13 _public prototype_ `DECLARE_DELEGATE(FOnImportCanceled);`
- L16 _public function_ `SLATE_BEGIN_ARGS(SComposurePostMoveSettingsImportDialog)`
- L18 _public prototype_ `SLATE_EVENT(FOnImportSelected, OnImportSelected) SLATE_EVENT(FOnImportCanceled, OnImportCanceled) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FFrameRate InFrameRate, FFrameNumber InStartFrame);` — Event which is executed when the user selects import.
- L34 _private prototype_ `FString GetFilePath() const;`
- L35 _private prototype_ `void FilePathPicked(const FString& PickedPath);`
- L37 _private prototype_ `FFrameRate GetFrameRate() const;`
- L38 _private prototype_ `void FrameRateChanged(FFrameRate Value);`
- L40 _private prototype_ `int32 GetStartFrame() const;`
- L41 _private prototype_ `void StartFrameChanged(int32 Value);`
- L43 _private prototype_ `FReply OnCancelPressed();`
- L44 _private prototype_ `FReply OnImportPressed();`
- L47 _private member_ `FString FilePath;`
- L48 _private member_ `FFrameRate FrameRate;`
- L49 _private member_ `FFrameNumber StartFrame;`
- L51 _private member_ `FOnImportSelected OnImportSelected;`
- L52 _private member_ `FOnImportCanceled OnImportCanceled;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnImportSelected, FString, FFrameRate, FFrameNumber);`
- L13 _delegate_ `DECLARE_DELEGATE(FOnImportCanceled);`

### `Plugins/Compositing/Composure/Source/ComposureEditor/Public/ComposureEditorModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogComposureEditor, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogComposureEditor, All, All);`
