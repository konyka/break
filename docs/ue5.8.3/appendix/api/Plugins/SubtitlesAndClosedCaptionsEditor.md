# Plugins / SubtitlesAndClosedCaptionsEditor

- module root: `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor`
- headers: 7; symbols: 47
- symbol kinds: class=7, function=6, member=6, prototype=27, struct=1
- PrivateDependencyModuleNames: AssetTools, Blutility, LevelSequence, MovieScene, MovieSceneTools, Overlay, Sequencer, SequencerCore, Slate, SlateCore, SubtitlesAndClosedCaptions
- PublicDependencyModuleNames: AssetDefinition, Core, CoreUObject, Engine, UnrealEd

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Private/SubtitleAssetDefinitions.h` (Private)


#### class `USubtitleAssetDefinitions`  
`class USubtitleAssetDefinitions : public UAssetDefinitionDefault`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Private/SubtitleFactory.h` (Private)


#### class `USubtitleFactory`  
`class USubtitleFactory : public UFactory`  
_L11-18_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InFeedbackContext) override;` — UFactory Begin

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Private/SubtitleSequencerSection.h` (Private)


#### class `FSubtitleSequencerSection`  
`class FSubtitleSequencerSection : public FSequencerSection , public TSharedFromThis<FSubtitleSequencerSection>`  
_L9-21_
- inherits: `FSequencerSection,TSharedFromThis<FSubtitleSequencerSection>`
- L14 _public function_ `FSubtitleSequencerSection(UMovieSceneSection& InSection) : FSequencerSection(InSection)`
- L19 _public prototype_ `virtual FText GetSectionTitle() const override;` — ISequencerSection interface
- L20 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Private/SubtitlesTrackEditor.h` (Private)


#### struct `DragDropValidInfo`  
`struct DragDropValidInfo`  
_L16-22_
- L18 _public member_ `TSharedPtr<FDragDropOperation> Operation = nullptr;`
- L19 _public member_ `TSharedPtr<ISequencer> SequencerPtr = nullptr;`
- L20 _public member_ `UMovieSceneSequence* FocusedSequence = nullptr;`
- L21 _public member_ `TSharedPtr<FAssetDragDropOp> DragDropOp = nullptr;`

#### class `FSubtitlesTrackEditor`  
`class FSubtitlesTrackEditor : public FMovieSceneTrackEditor`  
_L27-76_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for subtitles tracks
- L37 _public prototype_ `FSubtitlesTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L45 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L50 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L51 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L53 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L54 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L55 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L56 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L57 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L58 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L62 _protected prototype_ `FKeyPropertyResult AddNewSubtitle(FFrameNumber KeyTime, class USubtitleAssetUserData* Subtitle, UMovieSceneSubtitlesTrack* InDestinationTrack, int32 RowIndex);` — Delegate for AnimatablePropertyChanged in HandleAssetAdded for subtitles
- L64 _protected prototype_ `FKeyPropertyResult AddNewAttachedSubtitle(FFrameNumber KeyTime, class USubtitleAssetUserData* Subtitle, UMovieSceneSubtitlesTrack* InDestinationTrack, TArray<TWeakObjectPtr<UObject>> ObjectsToAttachTo);` — Delegate for AnimatablePropertyChanged in HandleAssetAdded for attached subtitles
- L69 _private prototype_ `TSharedRef<SWidget> BuildSubMenu(FOnAssetSelected OnAssetSelected, FOnAssetEnterPressed OnAssetEnterPressed);`
- L70 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData, UMovieSceneTrack* Track);`
- L71 _private prototype_ `void OnAssetEnterPressed(const TArray<FAssetData>& AssetData, UMovieSceneTrack* Track);`
- L72 _private prototype_ `void HandleAddMenuEntryExecute();`
- L75 _private prototype_ `bool IsDragDropValid(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams, DragDropValidInfo& OutDragDropInfo);` — Helper function: packages up and null-checks common info used by OnAllowDrop and OnDrop

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Public/SubtitleAssetActionUtility.h` (Public)


#### class `USubtitleAssetActionUtility`  
`class USubtitleAssetActionUtility : public UAssetActionUtility`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UAssetActionUtility`
- desc: Asset Action Utility class for any editor right-click actions relevant to subtitles.
- L16 _public prototype_ `USubtitleAssetActionUtility();`
- L19 _public prototype_ `void ConvertBasicOverlaysToSubtitles();` — `UFUNCTION(CallInEditor, Category="Subtitles")`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Public/SubtitleMigrationUtility.h` (Public)


#### class `USubtitleMigrationUtility`  
`class USubtitleMigrationUtility : public UAssetActionUtility`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetActionUtility`
- desc: Asset Action Utility class for migrating subtitles Associated asset SubtitleMigrationAction.uasset required to show up in editor.
- L17 _private member_ `const static FString UndoContext;`
- L20 _public prototype_ `USubtitleMigrationUtility();`
- L23 _public prototype_ `void AddBlankSubtitle();` — `UFUNCTION(CallInEditor, Category = "Subtitles")`
- L26 _public prototype_ `void RemoveLegacySubtitles();` — `UFUNCTION(CallInEditor, Category = "Subtitles")`
- L29 _public prototype_ `void ConvertLegacySubtitles();` — `UFUNCTION(CallInEditor, Category = "Subtitles")`

### `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptionsEditor/Public/SubtitlesAndClosedCaptionsEditorModule.h` (Public)


#### class `ISubtitlesAndClosedCaptionsEditorModule`  
`class ISubtitlesAndClosedCaptionsEditorModule : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L11 _public function_ `static FText GetAssetTypeCategory()` — `UE_DEPRECATED(5.8, "Subtitle was moved over to the Data menu, use EAssetCategoryPaths::Data instead")`
- L16 _protected member_ `static FText AssetTypeCategory;`
