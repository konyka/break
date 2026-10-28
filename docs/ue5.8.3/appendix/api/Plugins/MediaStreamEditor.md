# Plugins / MediaStreamEditor

- module root: `Plugins/Experimental/MediaStream/Source/MediaStreamEditor`
- headers: 10; symbols: 112
- symbol kinds: class=10, function=5, member=17, namespace=12, prototype=68
- PrivateDependencyModuleNames: CoreUObject, DesktopWidgets, LevelSequence, LevelSequenceEditor, MediaAssets, MediaCompositing, MediaPlayerEditor, MediaStream, MediaUtils, MovieScene, Projects, PropertyEditor, Sequencer, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/DetailsPanel/MediaStreamCustomization.h` (Private)


#### class `UE::MediaStreamEditor::FMediaStreamCustomization`  
`class FMediaStreamCustomization : public IDetailCustomization`  
_L21-63_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UMediaStreamComponent class.
- L28 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L33 _public prototype_ `virtual ~FMediaStreamCustomization() override = default;`
- L36 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L41 _private member_ `TArray<TWeakObjectPtr<UMediaStream>> MediaStreamsList;` — List of the media streams we are editing.
- L44 _private prototype_ `UMediaStream* GetMediaStream() const;` — Returns the first media stream being edited.
- L47 _private prototype_ `void AddControlCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds a scrubbable track and media control buttons
- L50 _private prototype_ `void AddSourceCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds options for the media source.
- L53 _private prototype_ `void AddDetailsCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds media and player details.
- L56 _private prototype_ `void AddTextureCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds media texture object and options.
- L59 _private prototype_ `void AddCacheCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds media cache settings.
- L62 _private prototype_ `void AddPlayerCategory(IDetailLayoutBuilder& InDetailBuilder);` — Adds player config options.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaStreamEditor` (scope `UE`)

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/DetailsPanel/MediaStreamSourceCustomization.h` (Private)


#### class `UE::MediaStreamEditor::FMediaStreamSourceCustomization`  
`class FMediaStreamSourceCustomization : public TSharedFromThis<FMediaStreamSourceCustomization>`  
_L25-51_
- inherits: `TSharedFromThis<FMediaStreamSourceCustomization>`
- desc: Generates custom widgets for source scheme types. Object should not last behind the local scope.
- L28 _public prototype_ `virtual ~FMediaStreamSourceCustomization() = default;`
- L31 _public prototype_ `IMediaStreamSchemeHandler::FCustomWidgets Customize(UMediaStream* InMediaStream);` — Produces widgets for scheme customizations
- L35 _private prototype_ `static ECheckBoxState GetSourceCheckBoxState(TWeakObjectPtr<UMediaStream> InMediaStreamWeak, FName InSourceScheme);` — Whether a particular scheme is active.
- L38 _private prototype_ `static void OnSourceCheckBoxStateChanged(ECheckBoxState InState, TWeakObjectPtr<UMediaStream> InMediaStreamWeak, FName InSourceScheme);` — Changes the source to a new scheme.
- L41 _private member_ `UMediaStream* MediaStream = nullptr;` — Temporarily stored media stream.
- L44 _private prototype_ `void AddSourceSchemeSelector(IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets);` — Adds the scheme selector widget. @see AddSourceSchemeSelectRow.
- L47 _private prototype_ `void AddSourceSchemeSelectRow(TSharedRef<SGridPanel> InContainer, int32 InRow, const FName& InName);` — Adds the widget for a particular scheme type.
- L50 _private prototype_ `void AddSchemeCustomizations(IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets);` — Adds a customization for a particular scheme.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MediaStreamEditor` (scope `UE`)

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/DetailsPanel/SMediaStreamMediaDetails.h` (Private)


#### class `UE::MediaStreamEditor::SMediaStreamMediaDetails`  
`class SMediaStreamMediaDetails : public SCompoundWidget`  
_L21-58_
- inherits: `SCompoundWidget`
- desc: Displays details about the media texture and its player.
- L23 _private function_ `SLATE_BEGIN_ARGS(SMediaStreamMediaDetails)`
- L25 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMediaStream* InMediaStream);`
- L30 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _protected member_ `TWeakObjectPtr<UMediaStream> MediaStreamWeak;`
- L37 _protected member_ `TSharedPtr<STextBlock> MediaPlayerName;` — Our widgets.
- L38 _protected member_ `TSharedPtr<STextBlock> FormatText;`
- L39 _protected member_ `TSharedPtr<STextBlock> FrameRateText;`
- L40 _protected member_ `TSharedPtr<STextBlock> LODBiasText;`
- L41 _protected member_ `TSharedPtr<STextBlock> MethodText;`
- L42 _protected member_ `TSharedPtr<STextBlock> NumMipsText;`
- L43 _protected member_ `TSharedPtr<STextBlock> NumTilesText;`
- L44 _protected member_ `TSharedPtr<STextBlock> ResolutionText;`
- L45 _protected member_ `TSharedPtr<STextBlock> ResourceSizeText;`
- L48 _protected prototype_ `UMediaPlayer* GetMediaPlayer() const;` — Retrieves the media player.
- L51 _protected prototype_ `UMediaTexture* GetMediaTexture() const;` — Retrieves the media texture.
- L54 _protected prototype_ `EVisibility AreDetailsVisible() const;` — Determines whether the entire widget should be visible.
- L57 _protected prototype_ `void UpdateDetails();` — Updates our widgets to reflect the current state.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MediaStreamEditor` (scope `UE`)

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/DetailsPanel/SMediaStreamMediaTrack.h` (Private)


#### class `UE::MediaStreamEditor::SMediaStreamMediaTrack`  
`class SMediaStreamMediaTrack : public SCompoundWidget`  
_L19-46_
- inherits: `SCompoundWidget`
- desc: Shows a scrubbable track for controlling media playback position.
- L21 _private function_ `SLATE_BEGIN_ARGS(SMediaStreamMediaTrack)`
- L23 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<UMediaStream*>& InMediaStreams);`
- L28 _private prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L33 _private member_ `TArray<TWeakObjectPtr<UMediaStream>> MediaStreamsWeak;` — The media stream for this track.
- L36 _private member_ `TArray<TWeakObjectPtr<UMediaPlayer>> MediaPlayersWeak;` — The active media player. If this changes, recreate the track.
- L39 _private member_ `TSharedPtr<SBox> Content;` — The container for the track.
- L42 _private prototype_ `TArray<UMediaPlayer*> GetMediaPlayers() const;` — Returns the currently active media player. May different from @see MediaPlayerWeak.
- L45 _private prototype_ `TSharedRef<SWidget> CreateTrack();` — Creates the track widget.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MediaStreamEditor` (scope `UE`)

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/DetailsPanel/SMediaStreamPlaybackControls.h` (Private)


#### class `UE::MediaStreamEditor::SMediaStreamPlaybackControls`  
`class SMediaStreamPlaybackControls : public SCompoundWidget`  
_L22-80_
- inherits: `SCompoundWidget`
- desc: Displays media playback controls, such as play, pause, etc.
- L24 _private function_ `SLATE_BEGIN_ARGS(SMediaStreamPlaybackControls)`
- L26 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<UMediaStream*>& InMediaStreams);`
- L32 _private member_ `TArray<TWeakObjectPtr<UMediaStream>> MediaStreamsWeak;` — The media stream for these controls.
- L35 _private prototype_ `TArray<UMediaStream*> GetMediaStreams() const;` — Returns the media streams associated with these controls.
- L38 _private prototype_ `TArray<UMediaPlayer*> GetMediaPlayers() const;` — Returns the media players associated with these controls.
- L41 _private prototype_ `void OnChangePlaybackState(EMediaStreamPlaybackState InState);` — Changes the state of selected media streams.
- L44 _private prototype_ `void OnChangePlaybackDirection(EMediaStreamPlaybackDirection InDirection);` — Changes the state of selected media streams.
- L47 _private prototype_ `void OnPlaybackSeek(EMediaStreamPlaybackSeek InPosition);` — Changes the state of selected media streams.
- L50 _private prototype_ `bool IsRateSupported(float InRate) const;` — Returns true if the given rate is supported by the media/player.
- L54 _private prototype_ `EVisibility Open_GetVisibility() const;`
- L55 _private prototype_ `FReply Open_OnClicked();`
- L57 _private prototype_ `EVisibility Close_GetVisibility() const;`
- L58 _private prototype_ `FReply Close_OnClicked();`
- L60 _private prototype_ `bool Rewind_IsEnabled() const;`
- L61 _private prototype_ `FReply Rewind_OnClicked();`
- L63 _private prototype_ `bool Reverse_IsEnabled() const;`
- L64 _private prototype_ `FReply Reverse_OnClicked();`
- L66 _private prototype_ `EVisibility Play_GetVisibility() const;`
- L67 _private prototype_ `bool Play_IsEnabled() const;`
- L68 _private prototype_ `FReply Play_OnClicked();`
- L70 _private prototype_ `EVisibility Pause_GetVisibility() const;`
- L71 _private prototype_ `bool Pause_IsEnabled() const;`
- L72 _private prototype_ `FReply Pause_OnClicked();`
- L74 _private prototype_ `bool Forward_IsEnabled() const;`
- L75 _private prototype_ `FReply Forward_OnClicked();`
- L77 _private prototype_ `bool AddTrack_GetEnabled() const;`
- L78 _private prototype_ `FText AddTrack_GetToolTip() const;`
- L79 _private prototype_ `FReply AddTrack_OnClicked();`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MediaStreamEditor` (scope `UE`)

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/MediaStreamEditorModule.h` (Private)


#### class `FMediaStreamEditorModule`  
`class FMediaStreamEditorModule : public IModuleInterface`  
_L15-25_
- inherits: `IModuleInterface`
- desc: Media Stream Editor - Content/type agnostic chainable media proxy with media player integration.
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _protected member_ `TSharedPtr<FMediaStreamObjectSchema> MediaStreamObjectSchema;`

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/MediaStreamEditorSequencerLibrary.h` (Private)


#### class `FMediaStreamEditorSequencerLibrary`  
`class FMediaStreamEditorSequencerLibrary`  
_L9-19_
- L12 _public prototype_ `static ULevelSequence* GetLevelSequence();`
- L14 _public prototype_ `static bool HasTrack(UMediaStream* InMediaStream);`
- L16 _public prototype_ `static bool CanAddTrack(UMediaStream* InMediaStream);`
- L18 _public prototype_ `static bool AddTrack(UMediaStream* InMediaStream);`

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/MediaStreamEditorStyle.h` (Private)


#### class `FMediaStreamEditorStyle`  
`class FMediaStreamEditorStyle : public FSlateStyleSet`  
_L10-30_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the media plate editor UI.
- L14 _public prototype_ `FMediaStreamEditorStyle();` — Default constructor.
- L17 _public prototype_ `~FMediaStreamEditorStyle();` — Destructor.
- L19 _public function_ `static TSharedRef<FMediaStreamEditorStyle> Get()`

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Private/MediaStreamObjectSchema.h` (Private)


#### class `FMediaStreamObjectSchema`  
`class FMediaStreamObjectSchema : public UE::Sequencer::IObjectSchema`  
_L7-16_
- inherits: `UE::Sequencer::IObjectSchema`
- L11 _public prototype_ `virtual UObject* GetParentObject(UObject* InObject) const override;`
- L12 _public prototype_ `virtual UE::Sequencer::FObjectSchemaRelevancy GetRelevancy(const UObject* InObject) const override;`
- L13 _public prototype_ `virtual TSharedPtr<FExtender> ExtendObjectBindingMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<ISequencer> InSequencerWeak, TConstArrayView<UObject*> InContextSensitiveObjects) const override;`
- L14 _public prototype_ `virtual FText GetPrettyName(const UObject* InObject) const;`

### `Plugins/Experimental/MediaStream/Source/MediaStreamEditor/Public/MediaStreamWidgets.h` (Public)


#### class `UE::MediaStreamEditor::FMediaStreamWidgets`  
`class FMediaStreamWidgets`  
_L14-37_
- L20 _public prototype_ `static IMediaStreamSchemeHandler::FCustomWidgets GenerateSourceSchemeRows(UMediaStream* InMediaStream);` — Generates custom widgets for source scheme types.
- L25 _public prototype_ `static TSharedRef<SWidget> CreateTextureDetailsWidget(UMediaStream* InMediaStreams);` — Creates a widget representing the details of the owned Media Texture.
- L30 _public prototype_ `static TSharedRef<SWidget> CreateTrackWidget(const TArray<UMediaStream*>& InMediaStreams);` — Creates a widget allowing the user to scrub the media.
- L36 _public prototype_ `static TSharedRef<SWidget> CreateControlsWidget(const TArray<UMediaStream*>& InMediaStreams);` — Creates a widget allowing the user to control the media playback. If providing multiple media streams, the first should be the one that can have tracks.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MediaStreamEditor` (scope `UE`)
