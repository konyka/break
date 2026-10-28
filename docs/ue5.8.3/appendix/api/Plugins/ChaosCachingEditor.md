# Plugins / ChaosCachingEditor

- module root: `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor`
- headers: 11; symbols: 145
- symbol kinds: class=14, function=13, macro=2, member=25, namespace=2, prototype=89
- PrivateDependencyModuleNames: AssetDefinition
- PublicDependencyModuleNames: BlueprintGraph, ChaosCaching, Core, CoreUObject, EditorFramework, Engine, GeometryCollectionEngine, InputCore, LevelEditor, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, PhysicsCore, PropertyEditor, SceneOutliner, Sequencer, SequencerCore, Slate, SlateCore, TakeRecorder, TakeTrackRecorders, TakesCore, TimeManagement, ToolMenus, UnrealEd

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Private/Chaos/AssetDefinition_ChaosCacheCollection.h` (Private)


#### class `UAssetDefinition_ChaosCacheCollection`  
`class UAssetDefinition_ChaosCacheCollection : public UAssetDefinitionDefault`  
_L9-43_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L24 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L29 _public function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override`
- L34 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Private/Chaos/ChaosCachingEditorStyle.h` (Private)


#### class `FChaosCachingEditorStyle`  
`class FChaosCachingEditorStyle : public FSlateStyleSet`  
_L10-23_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the take recorder UI
- L14 _public member_ `static FName StyleName;`
- L17 _public prototype_ `static FChaosCachingEditorStyle& Get();` — Access the singleton instance for this style set
- L21 _private prototype_ `FChaosCachingEditorStyle();`
- L22 _private prototype_ `~FChaosCachingEditorStyle();`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/ActorFactoryCacheManager.h` (Public)


#### class `UActorFactoryCacheManager`  
`class UActorFactoryCacheManager : public UActorFactory`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L19 _private prototype_ `UActorFactoryCacheManager();`
- L22 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L23 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L24 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCACHINGEDITOR_API`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/CacheCollectionCustomization.h` (Public)


#### class `FCacheCollectionDetails`  
`class FCacheCollectionDetails : public IDetailCustomization`  
_L20-41_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _private prototype_ `UChaosCacheCollection* GetSelectedCollection();`
- L29 _private prototype_ `const UChaosCacheCollection* GetSelectedCollection() const;`
- L30 _private prototype_ `const UChaosCache* GetCacheCollection(int32 Index) const;`
- L31 _private prototype_ `FText GetCacheName(int32 InCacheIndex) const;`
- L32 _private prototype_ `void OnDeleteCache(int32 InArrayIndex, IDetailLayoutBuilder* InLayoutBuilder);`
- L34 _private prototype_ `void OnChangeCacheName(const FText& InNewName, int32 InIndex);`
- L35 _private prototype_ `void OnCommitCacheName(const FText& InNewName, ETextCommit::Type InTextCommit, int32 InIndex);`
- L37 _private prototype_ `void GenerateCacheArrayElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L38 _private member_ `TWeakObjectPtr<UObject> Item;`
- L40 _private member_ `TMap< int, TSharedPtr<SEditableTextBox>> NameEditBoxes;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/CacheCollectionFactory.h` (Public)


#### class `UCacheCollectionFactory`  
`class UCacheCollectionFactory : public UFactory`  
_L10-32_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UCacheCollectionFactory();`
- L18 _public prototype_ `bool CanCreateNew() const override;` — UFactory Interface
- L19 _public prototype_ `bool FactoryCanImport(const FString& Filename) override;`
- L20 _public prototype_ `UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L27 _public prototype_ `bool ShouldShowInNewMenu() const override;`
- L28 _public prototype_ `bool ConfigureProperties() override;`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/CacheEditorCommands.h` (Public)


#### class `FCachingEditorCommands`  
`class FCachingEditorCommands : public TCommands<FCachingEditorCommands>`  
_L8-22_
- inherits: `TCommands<FCachingEditorCommands>`
- L11 _public function_ `FCachingEditorCommands() : TCommands<FCachingEditorCommands>( TEXT("ChaosCacheEditor"), NSLOCTEXT("ChaosCacheEditorCommands", "ContextDesc", "Chaos Cache"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L17 _public prototype_ `virtual ~FCachingEditorCommands() = default;`
- L19 _public prototype_ `virtual void RegisterCommands();`
- L21 _public member_ `TSharedPtr<FUICommandInfo> CreateCacheManager;`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/CacheManagerCustomization.h` (Public)


#### class `FCacheManagerDetails`  
`class FCacheManagerDetails : public IDetailCustomization`  
_L15-35_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `void SetCacheModeOptions(bool bRecord);`
- L23 _private prototype_ `int32 GetClampedCacheModeIndex() const;`
- L24 _private prototype_ `FSlateColor GetCacheModeTextColor() const;`
- L26 _private prototype_ `void GenerateCacheArrayElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L27 _private prototype_ `TSharedRef<SWidget> GenerateCacheModeWidget(TSharedPtr<FText> InItem);`
- L28 _private prototype_ `void OnCacheModeChanged(TSharedPtr<FText> NewSelection, ESelectInfo::Type SelectInfo);`
- L29 _private prototype_ `FText GetCacheModeComboBoxContent() const;`
- L30 _private prototype_ `TSharedPtr<FText> GetCurrentCacheMode() const;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> CacheModeHandle;`
- L33 _private member_ `TArray<TSharedPtr<FText>> CacheModeComboList;`
- L34 _private member_ `TArray<FSlateColor> CacheModeColor;`

#### class `FObservedComponentDetails`  
`class FObservedComponentDetails : public IPropertyTypeCustomization`  
_L37-43_
- inherits: `IPropertyTypeCustomization`
- L40 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L41 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L42 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ESelectInfo`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Chaos/ChaosCachingEditorPlugin.h` (Public)


#### class `IChaosCachingEditorPlugin`  
`class IChaosCachingEditorPlugin : public IModuleInterface`  
_L22-60_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L27 _public prototype_ `virtual void StartupModule();`
- L28 _public prototype_ `virtual void ShutdownModule();`
- L36 _public function_ `static inline IChaosCachingEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L46 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L50 _private prototype_ `TSharedRef<FExtender> ExtendLevelViewportContextMenu(const TSharedRef<FUICommandList> InCommandList, const TArray<AActor*> SelectedActors);`
- L51 _private prototype_ `void RegisterCachingSubMenu(FMenuBuilder& InMenuBuilder);`
- L53 _private prototype_ `void OnCreateCacheManager();`
- L55 _private member_ `FDelegateHandle StartupHandle;`
- L56 _private member_ `FDelegateHandle TrackEditorBindingHandle;`
- L57 _private member_ `FDelegateHandle SourcesMenuExtension;`
- L59 _private member_ `FMovieSceneChaosCacheTrackRecorderFactory MovieSceneChaosCacheTrackRecorder;`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Sequencer/ChaosCacheTrackEditor.h` (Public)


#### class `FChaosCacheTrackEditor`  
`class FChaosCacheTrackEditor : public FMovieSceneTrackEditor`  
_L13-53_
- inherits: `FMovieSceneTrackEditor`
- desc: Editor for chaos Cache tracks
- L21 _public prototype_ `FChaosCacheTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L24 _public prototype_ `virtual ~FChaosCacheTrackEditor() = default;` — Virtual destructor.
- L32 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L37 _public prototype_ `virtual FText GetDisplayName() const override;`
- L38 _public prototype_ `virtual void BuildObjectBindingTrackMenu(class FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L39 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L40 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L41 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L42 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L43 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L49 _private prototype_ `void BuildChaosCacheTrack(TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);` — Build an internal chaos cache track
- L52 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, class AChaosCacheManager* ChaosCache, UMovieSceneTrack* Track);` — Delegate for AnimatablePropertyChanged in AddKey

#### class `FChaosCacheSection`  
`class FChaosCacheSection : public ISequencerSection , public TSharedFromThis<FChaosCacheSection>`  
_L56-98_
- inherits: `ISequencerSection,TSharedFromThis<FChaosCacheSection>`
- desc: Chaos cache sequencer section
- L63 _public prototype_ `FChaosCacheSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L66 _public prototype_ `virtual ~FChaosCacheSection() = default;` — Virtual destructor.
- L71 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L72 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L73 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L74 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L75 _public prototype_ `virtual void BeginResizeSection() override;`
- L76 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L77 _public prototype_ `virtual void BeginSlipSection() override;`
- L78 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L79 _public prototype_ `virtual void BeginDilateSection() override;`
- L80 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L85 _private prototype_ `void UpdateSection(FFrameNumber& UpdateTime) const;`
- L88 _private member_ `class UMovieSceneChaosCacheSection& Section;` — The section we are visualizing
- L91 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L94 _private member_ `FFrameNumber InitialFirstLoopStartOffsetDuringResize;` — Cached first loop start offset value valid only during resize
- L97 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Sequencer/MovieSceneChaosCacheTrackRecorder.h` (Public)


#### class `FMovieSceneChaosCacheTrackRecorderFactory`  
`class FMovieSceneChaosCacheTrackRecorderFactory : public IMovieSceneTrackRecorderFactory`  
_L22-34_
- inherits: `IMovieSceneTrackRecorderFactory`
- L25 _public prototype_ `virtual ~FMovieSceneChaosCacheTrackRecorderFactory() = default;`
- L28 _public prototype_ `virtual bool CanRecordObject(class UObject* InObjectToRecord) const override;`
- L29 _public prototype_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForObject() const override;`
- L30 _public function_ `virtual bool CanRecordProperty(class UObject* InObjectToRecord, class FProperty* InPropertyToRecord) const override`
- L31 _public function_ `virtual UMovieSceneTrackRecorder* CreateTrackRecorderForProperty(UObject* InObjectToRecord, const FName& InPropertyToRecord) const override`
- L32 _public function_ `virtual FText GetDisplayName() const override`

#### class `UMovieSceneChaosCacheTrackRecorder`  
`class UMovieSceneChaosCacheTrackRecorder : public UMovieSceneTrackRecorder`  
_L40-78_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneTrackRecorder`
- desc: Track recorder implementation for the chaos cache
- L47 _public prototype_ `virtual void RecordSampleImpl(const FQualifiedFrameTime& CurrentFrameTime) override;`
- L48 _public prototype_ `virtual void FinalizeTrackImpl() override;`
- L49 _public prototype_ `virtual void SetSectionStartTimecodeImpl(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame) override;`
- L50 _public prototype_ `virtual UMovieSceneSection* GetMovieSceneSection() const override;`
- L51 _public prototype_ `virtual void StopRecordingImpl() override;`
- L52 _public prototype_ `virtual bool LoadRecordedFile(const FString& InFileName, UMovieScene *InMovieScene, TMap<FGuid, AActor*>& ActorGuidToActorMap, TFunction<void()> InCompletionCallback) override;`
- L53 _public prototype_ `virtual void CreateTrackImpl() override;`
- L57 _public function_ `TWeakObjectPtr<UMovieSceneChaosCacheTrack> GetChaosCacheTrack() const` — Returns the chaos cache track on which the cache manager will be recorded
- L62 _private member_ `TWeakObjectPtr<UMovieSceneChaosCacheTrack> ChaosCacheTrack;` — The ChaosCache Track to record onto
- L65 _private member_ `TWeakObjectPtr<UMovieSceneChaosCacheSection> ChaosCacheSection;` — Sections to record to on each track
- L68 _private member_ `AChaosCacheManager* ChaosCacheManager;` — Chaos cache that will be used to record the simulation
- L71 _private member_ `ECacheMode StoredCacheMode;` — Stored cahce mode that will be set back onto the manager once the recording will be finished
- L74 _private member_ `double RecordStartTime;` — The time at the start of this recording section
- L77 _private member_ `FFrameNumber RecordStartFrame;` — The frame at the start of this recording section

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCACHINGEDITOR_API`

### `Plugins/Experimental/ChaosCaching/Source/ChaosCachingEditor/Public/Sequencer/TakeRecorderChaosCacheSource.h` (Public)


#### class `UTakeRecorderChaosCacheSource`  
`class UTakeRecorderChaosCacheSource : public UTakeRecorderSource`  
_L20-63_
- reflection: `UCLASS(Category = "Chaos")`
- inherits: `UTakeRecorderSource`
- L26 _public prototype_ `UTakeRecorderChaosCacheSource(const FObjectInitializer& ObjInit);`
- L30 _public member_ `TSoftObjectPtr<AChaosCacheManager> ChaosCacheManager;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (DisplayName = "Chaos Cache"))` — Chaos Cache manager to be used as take recorder source
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _public prototype_ `virtual void PostLoad() override;`
- L39 _protected function_ `virtual bool SupportsSubscenes() const override`
- L44 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;`
- L45 _private prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L46 _private prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L47 _private prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentTime) override;`
- L48 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L49 _private prototype_ `virtual void AddContentsToFolder(UMovieSceneFolder* InFolder) override;`
- L50 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L51 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L56 _private member_ `TObjectPtr<UMovieSceneChaosCacheTrackRecorder> TrackRecorder;` — `UPROPERTY()` — Chaos cache track recorder used by this source
- L62 _private member_ `TWeakObjectPtr<UMovieSceneChaosCacheTrack> CachedChaosCacheTrack;` — Stores an existing Chaos cache track track in the Sequence to be recorded or a new one created for recording. Set during PreRecording.
