# Plugins / MetaHumanLocalLiveLinkSource

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource`
- headers: 33; symbols: 563
- symbol kinds: class=39, delegate=2, enum=13, enumerator=63, function=11, member=225, namespace=24, prototype=178, struct=7, typedef=1
- PrivateDependencyModuleNames: AudioMixerWasapi, AudioPlatformConfiguration, Core, CoreUObject, EditorWidgets, Engine, InputCore, LiveLink, LiveLinkInterface, MediaAssets, MediaFrameworkUtilities, MediaProfile, MediaUtils, MetaHumanCoreTech, MetaHumanImageViewer, MetaHumanPipelineCore, PropertyEditor, Slate, SlateCore, SpeechAnimationSolver, UMG, UnrealEd
- PublicDependencyModuleNames: MetaHumanLiveLinkSource

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanAudioLiveLinkSource.h` (Private)


#### class `FMetaHumanAudioLiveLinkSource`  
`class FMetaHumanAudioLiveLinkSource : public FMetaHumanLocalLiveLinkSource`  
_L9-21_
- inherits: `FMetaHumanLocalLiveLinkSource`
- L13 _public member_ `static FText SourceType;`
- L15 _public prototype_ `virtual FText GetSourceType() const override;`
- L16 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L20 _protected prototype_ `virtual TSharedPtr<FMetaHumanLocalLiveLinkSubject> CreateSubject(const FName& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InSettings) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanAudioLiveLinkSourceFactory.h` (Private)


#### class `UMetaHumanAudioLiveLinkSourceFactory`  
`class UMetaHumanAudioLiveLinkSourceFactory : public ULiveLinkSourceFactory`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L19 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L21 _public function_ `virtual EMenuType GetMenuType() const override`
- L22 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& InConnectionString) const override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanAudioLiveLinkSubject.h` (Private)


#### class `FMetaHumanAudioLiveLinkSubject`  
`class FMetaHumanAudioLiveLinkSubject : public FMetaHumanAudioBaseLiveLinkSubject`  
_L11-25_
- inherits: `FMetaHumanAudioBaseLiveLinkSubject`
- L15 _public prototype_ `FMetaHumanAudioLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanAudioLiveLinkSubjectSettings* InSettings);`
- L16 _public prototype_ `virtual ~FMetaHumanAudioLiveLinkSubject();`
- L20 _protected prototype_ `virtual void MediaSamplerMain() override;`
- L24 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FMediaPlayerNode> MediaPlayer;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineAudioSourceNode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FAudioSourceNode`  
`class FAudioSourceNode : public FNode`  
_L14-49_
- inherits: `FNode`
- L18 _public prototype_ `FAudioSourceNode(const FString& InName);`
- L20 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L21 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L37 _public prototype_ `void AddAudioSample(FAudioSample&& InAudioSample);`
- L38 _public prototype_ `void SetError(const FString& InErrorMessage);`
- L42 _private member_ `FCriticalSection Mutex;`
- L43 _private member_ `TArray<FAudioSample> AudioSamples;`
- L44 _private member_ `FString ErrorMessage;`
- L46 _private member_ `float FPS = -1;`
- L47 _private member_ `int32 FPSCount = 0;`
- L48 _private member_ `double FPSStart = 0;`

#### enum `UE::MetaHuman::Pipeline::FAudioSourceNode::ErrorCode`  
`enum ErrorCode`  
_L23-26_
- L25 _public enumerator_ `GeneralError = 0`

#### class `UE::MetaHuman::Pipeline::FAudioSourceNode::FAudioSample`  
`class FAudioSample`  
_L28-35_
- L31 _public member_ `FAudioDataType Audio;`
- L32 _public member_ `FQualifiedFrameTime Time;`
- L33 _public member_ `FMetaHumanLocalLiveLinkSubject::ETimeSource TimeSource = FMetaHumanLocalLiveLinkSubject::ETimeSource::NotSet;`
- L34 _public member_ `int32 NumDropped = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineMediaPlayerNode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FVideoSample`  
`class FVideoSample`  
_L14-20_
- L17 _public member_ `TArray<uint8> Data;`
- L18 _public member_ `FQualifiedFrameTime SampleTime;`
- L19 _public member_ `FMetaHumanLocalLiveLinkSubject::ETimeSource SampleTimeSource = FMetaHumanLocalLiveLinkSubject::ETimeSource::NotSet;`

#### class `UE::MetaHuman::Pipeline::FMediaPlayerNode`  
`class FMediaPlayerNode : public FNode`  
_L22-61_
- inherits: `FNode`
- L26 _public prototype_ `FMediaPlayerNode(const FString& InTypeName, const FString& InName);`
- L28 _public prototype_ `virtual bool Play(const FString& InVideoURL, int32 InVideoTrack = -1, int32 InVideoTrackFormat = -1, const FString& InAudioURL = "", int32 InAudioTrack = -1, int32 InAudioTrackFormat = -1) = 0;`
- L30 _public prototype_ `virtual bool Close() = 0;` — Must be called from the game thread
- L32 _public member_ `static FString BundleURL;`
- L33 _public member_ `static FString MediaSourceURL;`
- L34 _public member_ `static FString MediaProfileURL;`
- L36 _public member_ `double StartTimeout = 5;`
- L37 _public member_ `double FormatWaitTime = 0.1;`
- L38 _public member_ `double SampleTimeout = 5;`
- L42 _protected prototype_ `void ConvertSample(const FIntPoint& InRes, const int32 InStride, const EMediaTextureSampleFormat InFormat, const uint8* InVideoSampleData, FUEImageDataType& OutImage) const;`
- L44 _protected member_ `bool bIsFirstVideoFrame = false;`
- L45 _protected member_ `bool bIsFirstAudioFrame = false;`
- L46 _protected member_ `bool bAllowFrameDropping = true;`
- L48 _protected member_ `const double StartWaitTime = 0.1;`
- L49 _protected member_ `const double SampleWaitTime = 0.001;`
- L51 _protected member_ `FFrameRate FrameRate;`
- L53 _protected function_ `template <class T> void SafeRelease(T** InPointer)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineMediaPlayerUENode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FMediaPlayerUENode`  
`class FMediaPlayerUENode : public FMediaPlayerNode, public FGCObject`  
_L17-85_
- inherits: `FMediaPlayerNode,FGCObject`
- L21 _public prototype_ `FMediaPlayerUENode(const FString& InName);`
- L23 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L24 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L25 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L27 _public prototype_ `virtual bool Play(const FString& InVideoURL, int32 InVideoTrack = -1, int32 InVideoTrackFormat = -1, const FString& InAudioURL = "", int32 InAudioTrack = -1, int32 InAudioTrackFormat = -1) override;`
- L29 _public prototype_ `virtual bool Close() override;` — Must be called from the game thread
- L49 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L50 _public prototype_ `virtual FString GetReferencerName() const;`
- L56 _private member_ `FString VideoURL;`
- L57 _private member_ `int32 VideoTrack = -1;`
- L58 _private member_ `int32 VideoTrackFormat = -1;`
- L60 _private member_ `FString AudioURL;`
- L61 _private member_ `int32 AudioTrack = -1;`
- L62 _private member_ `int32 AudioTrackFormat = -1;`
- L64 _private member_ `bool bIsBundle = false;`
- L65 _private member_ `bool bIsMediaSource = false;`
- L66 _private member_ `bool bIsMediaProfile = false;`
- L68 _private member_ `TObjectPtr<UMediaPlayer> VideoPlayer = nullptr;`
- L69 _private member_ `TObjectPtr<UMediaPlayer> AudioPlayer = nullptr;`
- L71 _private member_ `TObjectPtr<UMediaBundle> Bundle = nullptr;`
- L72 _private member_ `TObjectPtr<UMediaSource> VideoMediaSource = nullptr;`
- L73 _private member_ `TObjectPtr<UMediaSource> AudioMediaSource = nullptr;`
- L74 _private member_ `TWeakObjectPtr<UMediaProfile> MediaProfile = nullptr;`
- L76 _private member_ `TSharedPtr<FMediaTextureSampleQueue> VideoFrames = nullptr;`
- L77 _private member_ `TSharedPtr<FMediaAudioSampleQueue> AudioFrames = nullptr;`
- L79 _private member_ `TArray<float> AudioBuffer;`
- L80 _private member_ `int32 AudioBufferSampleRate = -1;`
- L81 _private member_ `int32 AudioBufferNumChannels = -1;`
- L82 _private member_ `int32 AudioBufferDataSizePerFrame = -1;`
- L83 _private member_ `int32 AudioFrameNumber = -1;`
- L84 _private member_ `double AudioFrameStartTime = -1;`

#### enum `UE::MetaHuman::Pipeline::FMediaPlayerUENode::ErrorCode`  
`enum ErrorCode`  
_L31-45_
- L33 _public enumerator_ `VideoTimeout = 0`
- L34 _public enumerator_ `AudioTimeout`
- L35 _public enumerator_ `NoVideoPlayer`
- L36 _public enumerator_ `NoAudioPlayer`
- L37 _public enumerator_ `BadVideoTrack`
- L38 _public enumerator_ `BadVideoTrackFormat`
- L39 _public enumerator_ `BadAudioTrack`
- L40 _public enumerator_ `BadAudioTrackFormat`
- L41 _public enumerator_ `UnsupportedVideoFormat`
- L42 _public enumerator_ `FailedToPlayVideo`
- L43 _public enumerator_ `FailedToPlayAudio`
- L44 _public enumerator_ `NoVideoSampleData`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineMediaPlayerWMFNode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FMediaPlayerWMFNode`  
`class FMediaPlayerWMFNode : public FMediaPlayerNode`  
_L14-50_
- inherits: `FMediaPlayerNode`
- L18 _public prototype_ `FMediaPlayerWMFNode(const FString& InName);`
- L20 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L21 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L23 _public prototype_ `virtual bool Play(const FString& InVideoURL, int32 InVideoTrack = -1, int32 InVideoTrackFormat = -1, const FString& InAudioURL = "", int32 InAudioTrack = -1, int32 InAudioTrackFormat = -1) override;`
- L25 _public prototype_ `virtual bool Close() override;` — Must be called from the game thread
- L39 _private member_ `TSharedPtr<class FMediaPlayerWMFNodeImpl> Impl;`
- L40 _private member_ `class SampleGrabberCallback *SampleGrabber = nullptr;`
- L41 _private member_ `FVideoSample VideoSample;`
- L43 _private member_ `uint32 Width = 0;`
- L44 _private member_ `uint32 Height = 0;`
- L45 _private member_ `int32 Stride = 0;`
- L46 _private member_ `EMediaTextureSampleFormat Format = EMediaTextureSampleFormat::Undefined;`
- L48 _private member_ `float FixedFPS = 0;`
- L49 _private member_ `double NodeStart = 0;`

#### enum `UE::MetaHuman::Pipeline::FMediaPlayerWMFNode::ErrorCode`  
`enum ErrorCode`  
_L27-35_
- L29 _public enumerator_ `VideoTimeout = 0`
- L30 _public enumerator_ `NoVideoPlayer`
- L31 _public enumerator_ `FailedToGetVideoSample`
- L32 _public enumerator_ `FailedToGetVideoSampleBuffer`
- L33 _public enumerator_ `FailedToGetVideoSampleLength`
- L34 _public enumerator_ `FailedToGetVideoSampleData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineMediaPlayerWMFReaderNode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FMediaPlayerWMFReaderNode`  
`class FMediaPlayerWMFReaderNode : public FMediaPlayerNode`  
_L14-44_
- inherits: `FMediaPlayerNode`
- L18 _public prototype_ `FMediaPlayerWMFReaderNode(const FString& InName);`
- L20 _public prototype_ `virtual bool Start(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L21 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L23 _public prototype_ `virtual bool Play(const FString& InVideoURL, int32 InVideoTrack = -1, int32 InVideoTrackFormat = -1, const FString& InAudioURL = "", int32 InAudioTrack = -1, int32 InAudioTrackFormat = -1) override;`
- L25 _public prototype_ `virtual bool Close() override;` — Must be called from the game thread
- L40 _private member_ `TSharedPtr<class FMediaPlayerWMFReaderNodeImpl> Impl;`
- L41 _private member_ `uint32 Width = 0;`
- L42 _private member_ `uint32 Height = 0;`
- L43 _private member_ `EMediaTextureSampleFormat Format = EMediaTextureSampleFormat::Undefined;`

#### enum `UE::MetaHuman::Pipeline::FMediaPlayerWMFReaderNode::ErrorCode`  
`enum ErrorCode`  
_L27-36_
- L29 _public enumerator_ `VideoTimeout = 0`
- L30 _public enumerator_ `NoVideoPlayer`
- L31 _public enumerator_ `FailedToGetVideoSample`
- L32 _public enumerator_ `FailedToGetVideoSampleBuffer`
- L33 _public enumerator_ `FailedToGetVideoSampleLength`
- L34 _public enumerator_ `FailedToGetVideoSampleData`
- L35 _public enumerator_ `FailedToReleaseVideoSampleData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanPipelineVideoSourceNode.h` (Private)


#### class `UE::MetaHuman::Pipeline::FVideoSourceNode`  
`class FVideoSourceNode : public FNode`  
_L14-49_
- inherits: `FNode`
- L18 _public prototype_ `FVideoSourceNode(const FString& InName);`
- L20 _public prototype_ `virtual bool Process(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L21 _public prototype_ `virtual bool End(const TSharedPtr<FPipelineData>& InPipelineData) override;`
- L37 _public prototype_ `void AddVideoSample(FVideoSample&& InVideoSample);`
- L38 _public prototype_ `void SetError(const FString& InErrorMessage);`
- L42 _private member_ `FCriticalSection Mutex;`
- L43 _private member_ `TArray<FVideoSample> VideoSamples;`
- L44 _private member_ `FString ErrorMessage;`
- L46 _private member_ `float FPS = -1;`
- L47 _private member_ `int32 FPSCount = 0;`
- L48 _private member_ `double FPSStart = 0;`

#### enum `UE::MetaHuman::Pipeline::FVideoSourceNode::ErrorCode`  
`enum ErrorCode`  
_L23-26_
- L25 _public enumerator_ `GeneralError = 0`

#### class `UE::MetaHuman::Pipeline::FVideoSourceNode::FVideoSample`  
`class FVideoSample`  
_L28-35_
- L31 _public member_ `FUEImageDataType Image;`
- L32 _public member_ `FQualifiedFrameTime Time;`
- L33 _public member_ `FMetaHumanLocalLiveLinkSubject::ETimeSource TimeSource = FMetaHumanLocalLiveLinkSubject::ETimeSource::NotSet;`
- L34 _public member_ `int32 NumDropped = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanStringCombo.h` (Private)


#### class `SMetaHumanStringCombo`  
`class SMetaHumanStringCombo : public SCompoundWidget`  
_L10-39_
- inherits: `SCompoundWidget`
- L14 _public typedef_ `typedef TSharedPtr<TPair<FString, FString>> FComboItemType;`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, FComboItemType InSelectedItem);`
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanStringCombo)`
- L19 _public prototype_ `SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<FComboItemType>* InItemSource);`
- L24 _public prototype_ `void RefreshOptions();`
- L26 _public member_ `FComboItemType CurrentItem = nullptr;`
- L30 _private member_ `TSharedPtr<SComboBox<FComboItemType>> Combo;`
- L32 _private prototype_ `TSharedRef<SWidget> MakeWidgetForItem(FComboItemType InItem) const;`
- L34 _private prototype_ `void OnSelectionChanged(FComboItemType InItem, ESelectInfo::Type InSelectType);`
- L36 _private prototype_ `FText GetCurrentItemLabel() const;`
- L38 _private member_ `FOnItemSelected OnItemSelected;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, FComboItemType InSelectedItem);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanVideoLiveLinkSource.h` (Private)


#### class `FMetaHumanVideoLiveLinkSource`  
`class FMetaHumanVideoLiveLinkSource : public FMetaHumanLocalLiveLinkSource`  
_L9-21_
- inherits: `FMetaHumanLocalLiveLinkSource`
- L13 _public member_ `static FText SourceType;`
- L15 _public prototype_ `virtual FText GetSourceType() const override;`
- L16 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L20 _protected prototype_ `virtual TSharedPtr<FMetaHumanLocalLiveLinkSubject> CreateSubject(const FName& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InSettings) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanVideoLiveLinkSourceFactory.h` (Private)


#### class `UMetaHumanVideoLiveLinkSourceFactory`  
`class UMetaHumanVideoLiveLinkSourceFactory : public ULiveLinkSourceFactory`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L19 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L21 _public function_ `virtual EMenuType GetMenuType() const override`
- L22 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& InConnectionString) const override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Private/MetaHumanVideoLiveLinkSubject.h` (Private)


#### class `FMetaHumanVideoLiveLinkSubject`  
`class FMetaHumanVideoLiveLinkSubject : public FMetaHumanVideoBaseLiveLinkSubject`  
_L11-25_
- inherits: `FMetaHumanVideoBaseLiveLinkSubject`
- L15 _public prototype_ `FMetaHumanVideoLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanVideoLiveLinkSubjectSettings* InSettings);`
- L16 _public prototype_ `virtual ~FMetaHumanVideoLiveLinkSubject();`
- L20 _protected prototype_ `virtual void MediaSamplerMain() override;`
- L24 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FMediaPlayerNode> MediaPlayer;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanAudioBaseLiveLinkSubject.h` (Public)


#### class `FMetaHumanAudioBaseLiveLinkSubject`  
`class FMetaHumanAudioBaseLiveLinkSubject : public FMetaHumanMediaSamplerLiveLinkSubject`  
_L16-48_
- inherits: `FMetaHumanMediaSamplerLiveLinkSubject`
- L20 _public prototype_ `FMetaHumanAudioBaseLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanAudioBaseLiveLinkSubjectSettings* InSettings);`
- L22 _public prototype_ `void SetMood(const EAudioDrivenAnimationMood& InMood, float InMoodIntensity);`
- L23 _public prototype_ `void SetLookahead(int32 InLookahead);`
- L39 _protected prototype_ `void AddAudioSample(FAudioSample&& InAudioSample);`
- L40 _protected prototype_ `void SetError(const FString& InErrorMessage);`
- L42 _protected prototype_ `virtual void ExtractPipelineData(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData) override;`
- L46 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FAudioSourceNode> AudioSource;`
- L47 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FRealtimeSpeechToAnimNode> RealtimeAudioSolver;`

#### class `FMetaHumanAudioBaseLiveLinkSubject::FAudioSample`  
`class FAudioSample`  
_L27-37_
- L30 _public member_ `int32 NumChannels = -1;`
- L31 _public member_ `int32 SampleRate = -1;`
- L32 _public member_ `int32 NumSamples = -1;`
- L33 _public member_ `TArray<float> Data;`
- L34 _public member_ `FQualifiedFrameTime Time;`
- L35 _public member_ `ETimeSource TimeSource = ETimeSource::NotSet;`
- L36 _public member_ `int32 NumDropped = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanAudioBaseLiveLinkSubjectMonitorWidget.h` (Public)


#### class `SMetaHumanAudioBaseLiveLinkSubjectMonitorWidget`  
`class SMetaHumanAudioBaseLiveLinkSubjectMonitorWidget : public SCompoundWidget, public FGCObject`  
_L11-30_
- inherits: `SCompoundWidget,FGCObject`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanAudioBaseLiveLinkSubjectMonitorWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanAudioBaseLiveLinkSubjectSettings* InSettings);`
- L23 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L24 _public prototype_ `virtual FString GetReferencerName() const override;`
- L29 _private member_ `TObjectPtr<UMetaHumanAudioBaseLiveLinkSubjectSettings> Settings = nullptr;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanAudioBaseLiveLinkSubjectSettings.h` (Public)


#### class `UMetaHumanAudioBaseLiveLinkSubjectSettings`  
`class UMetaHumanAudioBaseLiveLinkSubjectSettings : public UMetaHumanLocalLiveLinkSubjectSettings`  
_L13-62_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanLocalLiveLinkSubjectSettings`
- L21 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L25 _public prototype_ `virtual void Setup() override;`
- L29 _public member_ `float Level = 0;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "Audio", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — A very simplistic volume indicator to show if audio is being received - it is not a true audio level monitoring tool.
- L32 _public member_ `EAudioDrivenAnimationMood Mood = EAudioDrivenAnimationMood::AutoDetect;` — `UPROPERTY(EditAnywhere, Category = "AudioControls")`
- L35 _public prototype_ `void SetMood(UPARAM(DisplayName = "Mood") EAudioDrivenAnimationMood InMo` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L38 _public prototype_ `void GetMood(UPARAM(DisplayName = "Mood") EAudioDrivenAnimationMood& OutMood) co` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L41 _public member_ `float MoodIntensity = 1.0;` — `UPROPERTY(EditAnywhere, Category = "AudioControls", Meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, Delta = 0.01))`
- L44 _public prototype_ `void SetMoodIntensity(UPARAM(DisplayName = "MoodIntensity") float InMo` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L47 _public prototype_ `void GetMoodIntensity(UPARAM(DisplayName = "MoodIntensity") float& OutMoodInte` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L51 _public member_ `int32 Lookahead = 80.0;` — `UPROPERTY(EditAnywhere, Category = "AudioControls", Meta = (UIMin = 80.0, ClampMin = 80.0, UIMax = 240.0, ClampMax = 240.0, Delta = 20.0))` — The amount of time, in milliseconds, that the audio solver looks ahead into the audio stream to produce the current frame of animation. A larger value will produce higher quality animation but will come at the cost of increased latency.
- L54 _public prototype_ `void SetLookahead(UPARAM(DisplayName = "Lookahead") int32 InLo` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L57 _public prototype_ `void GetLookahead(UPARAM(DisplayName = "Lookahead") int32& OutLookahea` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L61 _protected prototype_ `virtual void OnUpdate(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData) override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanAudioLiveLinkSourceSettings.h` (Public)


#### class `UMetaHumanAudioLiveLinkSourceSettings`  
`class UMetaHumanAudioLiveLinkSourceSettings : public UMetaHumanLocalLiveLinkSourceSettings`  
_L14-19_
- reflection: `UCLASS()`
- inherits: `UMetaHumanLocalLiveLinkSourceSettings`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanAudioLiveLinkSubjectSettings.h` (Public)


#### class `UMetaHumanAudioLiveLinkSubjectSettings`  
`class UMetaHumanAudioLiveLinkSubjectSettings : public UMetaHumanAudioBaseLiveLinkSubjectSettings`  
_L12-20_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanAudioBaseLiveLinkSubjectSettings`
- L19 _public member_ `FMetaHumanMediaSourceCreateParams MediaSourceCreateParams;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSource.h` (Public)


#### class `FMetaHumanLocalLiveLinkSource`  
`class FMetaHumanLocalLiveLinkSource : public ILiveLinkSource, public TSharedFromThis<FMetaHumanLocalLiveLinkSource>`  
_L15-67_
- inherits: `ILiveLinkSource,TSharedFromThis<FMetaHumanLocalLiveLinkSource>`
- L22 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L23 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L24 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L25 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L26 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L27 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L28 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* InSettings) override;`
- L33 _public function_ `template<class T> T* CreateSubjectSettings()`
- L41 _public prototype_ `FLiveLinkSubjectKey RequestSubjectCreation(const FString& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InMetaHumanLocalLiveLinkSubjectSettings);`
- L43 _public prototype_ `const FGuid& GetSourceGuid() const;`
- L48 _protected member_ `ILiveLinkClient* LiveLinkClient = nullptr;` — The Live Link client used to push Live Link data to the editor
- L51 _protected member_ `FGuid SourceGuid;` — The GUID of the Live Link Source
- L53 _protected function_ `virtual void OnSourceCreated(bool bIsPreset)`
- L55 _protected prototype_ `virtual TSharedPtr<FMetaHumanLocalLiveLinkSubject> CreateSubject(const FName& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InSettings) = 0;`
- L59 _private prototype_ `void SubjectAdded(FLiveLinkSubjectKey InSubject);`
- L60 _private prototype_ `void SubjectRemoved(FLiveLinkSubjectKey InSubject);`
- L62 _private member_ `TMap<FLiveLinkSubjectKey, TSharedPtr<FMetaHumanLocalLiveLinkSubject>> Subjects;`
- L64 _private member_ `bool bIsActive = false;`
- L66 _private member_ `UMetaHumanLocalLiveLinkSourceSettings* Settings = nullptr;`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanLocalLiveLinkSource, Log, All);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSourceBlueprint.h` (Public)


#### struct `FMetaHumanLiveLinkVideoDevice`  
`struct FMetaHumanLiveLinkVideoDevice`  
_L15-27_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L23 _public member_ `FString Url;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L26 _public member_ `bool IsMediaBundle = false;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### struct `FMetaHumanLiveLinkVideoTrack`  
`struct FMetaHumanLiveLinkVideoTrack`  
_L30-42_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L38 _public member_ `int32 Index = -1;` — `UPROPERTY()`
- L41 _public member_ `FMetaHumanLiveLinkVideoDevice VideoDevice;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### struct `FMetaHumanLiveLinkVideoFormat`  
`struct FMetaHumanLiveLinkVideoFormat`  
_L45-66_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `FIntPoint Resolution = FIntPoint(0, 0);` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L53 _public member_ `float FrameRate = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L56 _public member_ `FString Type;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L59 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L62 _public member_ `int32 Index = -1;` — `UPROPERTY()`
- L65 _public member_ `FMetaHumanLiveLinkVideoTrack VideoTrack;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### struct `FMetaHumanLiveLinkAudioDevice`  
`struct FMetaHumanLiveLinkAudioDevice`  
_L76-88_
- reflection: `USTRUCT(BlueprintType)`
- L81 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L84 _public member_ `FString Url;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L87 _public member_ `bool IsMediaBundle = false;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### struct `FMetaHumanLiveLinkAudioTrack`  
`struct FMetaHumanLiveLinkAudioTrack`  
_L91-103_
- reflection: `USTRUCT(BlueprintType)`
- L96 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L99 _public member_ `int32 Index = -1;` — `UPROPERTY()`
- L102 _public member_ `FMetaHumanLiveLinkAudioDevice AudioDevice;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### struct `FMetaHumanLiveLinkAudioFormat`  
`struct FMetaHumanLiveLinkAudioFormat`  
_L106-127_
- reflection: `USTRUCT(BlueprintType)`
- L111 _public member_ `int32 NumChannels = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L114 _public member_ `int32 SampleRate = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L117 _public member_ `FString Type;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L120 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`
- L123 _public member_ `int32 Index = -1;` — `UPROPERTY()`
- L126 _public member_ `FMetaHumanLiveLinkAudioTrack AudioTrack;` — `UPROPERTY(BlueprintReadOnly, Category = "MetaHuman Live Link")`

#### class `UMetaHumanLocalLiveLinkSourceBlueprint`  
`class UMetaHumanLocalLiveLinkSourceBlueprint : public UBlueprintFunctionLibrary`  
_L130-175_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBlueprintFunctionLibrary`
- L138 _public prototype_ `static void GetVideoDevicesOfType(TArray<FMetaHumanLiveLinkVideoDevice>& VideoDevices, EMetaHumanLocalLiveLinkSourceDeviceType DeviceType);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L141 _public prototype_ `static void GetVideoDevices(TArray<FMetaHumanLiveLinkVideoDevice>& VideoDevices, bool IncludeMediaBundles = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L144 _public prototype_ `static void GetVideoTracks(const FMetaHumanLiveLinkVideoDevice& VideoDevice, TArray<FMetaHumanLiveLinkVideoTrack>& VideoTracks, bool& TimedOut, float Timeout = 5);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L147 _public prototype_ `static void GetVideoFormats(const FMetaHumanLiveLinkVideoTrack& VideoTrack, TArray<FMetaHumanLiveLinkVideoFormat>& VideoFormats, bool& TimedOut, bool FilterFormats = true, float Timeout = 5);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L150 _public prototype_ `static void CreateVideoSource(FLiveLinkSourceHandle& VideoSource, bool& Succeeded);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L153 _public prototype_ `static void CreateVideoSubject(const FLiveLinkSourceHandle& VideoSource, const FMetaHumanLiveLinkVideoFormat& VideoFormat, const FString& SubjectName, FLiveLinkSubjectKey& VideoSubject, bool& Succeeded, float StartTimeout = 5, float FormatWaitTime = 0.1, float SampleTimeout = 5, const FMonocularAnimationPipelineModels& MonocularAnimationPipelineModels = FMonocularAnimationPipelineModels());` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link", meta = (AutoCreateRefTerm = "MonocularAnimationPipelineModels"))`
- L156 _public prototype_ `static void GetAudioDevicesOfType(TArray<FMetaHumanLiveLinkAudioDevice>& AudioDevices, EMetaHumanLocalLiveLinkSourceDeviceType DeviceType);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L159 _public prototype_ `static void GetAudioDevices(TArray<FMetaHumanLiveLinkAudioDevice>& AudioDevices, bool IncludeMediaBundles = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L162 _public prototype_ `static void GetAudioTracks(const FMetaHumanLiveLinkAudioDevice& AudioDevice, TArray<FMetaHumanLiveLinkAudioTrack>& AudioTracks, bool& TimedOut, float Timeout = 5);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L165 _public prototype_ `static void GetAudioFormats(const FMetaHumanLiveLinkAudioTrack& AudioTrack, TArray<FMetaHumanLiveLinkAudioFormat>& AudioFormats, bool& TimedOut, float Timeout = 5);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L168 _public prototype_ `static void CreateAudioSource(FLiveLinkSourceHandle& AudioSource, bool& Succeeded);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L171 _public prototype_ `static void CreateAudioSubject(const FLiveLinkSourceHandle& AudioSource, const FMetaHumanLiveLinkAudioFormat& AudioFormat, const FString& SubjectName, FLiveLinkSubjectKey& AudioSubject, bool& Succeeded, float StartTimeout = 5, float FormatWaitTime = 0.1, float SampleTimeout = 5);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L174 _public prototype_ `static void GetSubjectSettings(const FLiveLinkSubjectKey& Subject, UObject*& Settings);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSourceSettings.h` (Public)


#### enum `EMetaHumanLocalLiveLinkSourceDeviceType`  
`enum class EMetaHumanLocalLiveLinkSourceDeviceType : uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `CaptureDevice = 0 UMETA(DisplayName = "Capture Device")`
- L16 _public enumerator_ `MediaBundle = 1 UMETA(DisplayName = "Media Bundle")`
- L17 _public enumerator_ `MediaSource = 2 UMETA(DisplayName = "Media Source")`
- L18 _public enumerator_ `MediaProfile = 3 UMETA(DisplayName = "Media Profile")`

#### class `UMetaHumanLocalLiveLinkSourceSettings`  
`class UMetaHumanLocalLiveLinkSourceSettings : public ULiveLinkSourceSettings`  
_L23-38_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L29 _public prototype_ `void SetSource(class FMetaHumanLocalLiveLinkSource* InSource);`
- L30 _public prototype_ `FLiveLinkSubjectKey RequestSubjectCreation(const FString& InSubjectName, class UMetaHumanLocalLiveLinkSubjectSettings* InMetaHumanLocalLiveLinkSubjectSettings);`
- L33 _public member_ `bool bIsPreset = false;` — `UPROPERTY()`
- L37 _private member_ `class FMetaHumanLocalLiveLinkSource* Source = nullptr;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSubject.h` (Public)


#### class `FMetaHumanLocalLiveLinkSubject`  
`class FMetaHumanLocalLiveLinkSubject : public FRunnable`  
_L15-102_
- inherits: `FRunnable`
- L19 _public prototype_ `FMetaHumanLocalLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InSettings);`
- L23 _public prototype_ `virtual uint32 Run() override;`
- L24 _public prototype_ `virtual void Stop() override;`
- L27 _public prototype_ `virtual void Start();`
- L28 _public prototype_ `void SendLatestUpdate();`
- L30 _public prototype_ `void RemoveSubject();`
- L31 _public prototype_ `void ReloadSubject();`
- L40 _public prototype_ `static void GetSampleTime(const FFrameRate& InFrameRate, FQualifiedFrameTime& OutSampleTime, ETimeSource& OutSampleTimeSource);`
- L41 _public prototype_ `static void GetSampleTime(const TOptional<FTimecode>& InOptionalTimecode, const FFrameRate& InFrameRate, FQualifiedFrameTime& OutSampleTime, ETimeSource& OutSampleTimeSource);`
- L46 _protected member_ `FName SubjectName;` — Name to use as the Live Link subject
- L48 _protected prototype_ `virtual void ExtractPipelineData(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData) = 0;`
- L50 _protected function_ `virtual void FinalizeAnalyticsItems()`
- L53 _protected member_ `UE::MetaHuman::Pipeline::FPipeline Pipeline;` — Processing pipeline
- L55 _protected member_ `FFrameAnimationData Animation;`
- L56 _protected member_ `bool bIsNeutralFrame = false;`
- L57 _protected member_ `EMetaHumanLiveLinkHeadPoseMode HeadPoseMode = EMetaHumanLiveLinkHeadPoseMode::None;`
- L58 _protected member_ `TMap<FName, double> Timestamps;`
- L59 _protected member_ `FQualifiedFrameTime SceneTime;`
- L60 _protected member_ `float HeadControlSwitch = 0;`
- L62 _protected prototype_ `bool IsRunning() const;`
- L63 _protected prototype_ `const bool* GetIsRunningPtr() const;`
- L65 _protected member_ `TMap<FString, FString> AnalyticsItems;`
- L70 _private member_ `ILiveLinkClient* LiveLinkClient = nullptr;` — The Live Link client used to push Live Link data to the editor
- L73 _private member_ `FGuid SourceGuid;` — The GUID of the Live Link Source
- L76 _private member_ `TUniquePtr<FRunnableThread> Thread;` — The thread currently running this instance of the class
- L78 _private member_ `TWeakObjectPtr<UMetaHumanLocalLiveLinkSubjectSettings> Settings;`
- L80 _private member_ `bool bStopTask = false;`
- L81 _private member_ `bool bPipelineCompleted = true;`
- L82 _private member_ `double ProcessingStarted = 0;`
- L83 _private member_ `int32 NumProcessedFrames = 0;`
- L84 _private member_ `int32 NumAnimationFrames = 0;`
- L85 _private member_ `double LatencyTotal = 0;`
- L88 _private member_ `bool bIsFirstFrame = false;` — Processing pipeline support
- L90 _private prototype_ `void FrameComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L91 _private prototype_ `void ProcessComplete(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L92 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> ProcessCompletePipelineData;`
- L95 _private member_ `FLiveLinkBaseStaticData StaticData;` — Push new static data through Live Link
- L96 _private prototype_ `bool PushStaticData();`
- L99 _private prototype_ `bool PushFrameData();` — Push a new frame through Live Link
- L101 _private prototype_ `void SendAnalytics();`

#### enum `FMetaHumanLocalLiveLinkSubject::ETimeSource`  
`enum class ETimeSource : uint8`  
_L33-38_
- L35 _public enumerator_ `NotSet = 0`
- L36 _public enumerator_ `System`
- L37 _public enumerator_ `Media`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanLocalLiveLinkSubject, Log, All);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSubjectMonitorWidget.h` (Public)


#### class `SMetaHumanLocalLiveLinkSubjectMonitorWidget`  
`class SMetaHumanLocalLiveLinkSubjectMonitorWidget : public SCompoundWidget, public FGCObject`  
_L11-30_
- inherits: `SCompoundWidget,FGCObject`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanLocalLiveLinkSubjectMonitorWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanLocalLiveLinkSubjectSettings* InSettings);`
- L23 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L24 _public prototype_ `virtual FString GetReferencerName() const override;`
- L29 _private member_ `TObjectPtr<UMetaHumanLocalLiveLinkSubjectSettings> Settings = nullptr;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanLocalLiveLinkSubjectSettings.h` (Public)


#### enum `EMetaHumanLocalLiveLinkSubjectMonitoring`  
`enum class EMetaHumanLocalLiveLinkSubjectMonitoring : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Basic = 0` — Quick to calculate, eg fps counter
- L18 _public enumerator_ `Advanced` — Slow to calculate, eg video preview texture

#### enum `EMetaHumanLocalLiveLinkSubjectState`  
`enum class EMetaHumanLocalLiveLinkSubjectState : uint8`  
_L22-29_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Unknown = 0`
- L25 _public enumerator_ `OK`
- L26 _public enumerator_ `Completed`
- L27 _public enumerator_ `Error`
- L28 _public enumerator_ `DeviceSpecific`

#### class `UMetaHumanLocalLiveLinkSubjectSettings`  
`class UMetaHumanLocalLiveLinkSubjectSettings : public UMetaHumanLiveLinkSubjectSettings`  
_L34-103_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanLiveLinkSubjectSettings`
- L40 _public prototype_ `virtual void Setup();`
- L41 _public prototype_ `virtual void SetSubject(class FMetaHumanLocalLiveLinkSubject* InSubject);`
- L43 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdate, TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L44 _public member_ `FOnUpdate UpdateDelegate;`
- L46 _public member_ `class FMetaHumanLocalLiveLinkSubject* Subject = nullptr;`
- L50 _public member_ `FString State;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "10"))` — The state of the processing.
- L53 _public member_ `EMetaHumanLocalLiveLinkSubjectState StateEnum = EMetaHumanLocalLiveLinkSubjectState::Unknown;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L56 _public member_ `FString StateError;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L59 _public member_ `FColor StateLED;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "15"))`
- L63 _public member_ `FString Frame;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "100"))` — Frame number being processed.
- L66 _public member_ `int32 FrameNumber = -1;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L70 _public member_ `FString FPS;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "110"))` — Processing frame rate.
- L73 _public member_ `float ProcessingRate = -1;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L76 _public member_ `float CaptureRate = -1;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L79 _public member_ `FString Timecode;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "120"))`
- L82 _public member_ `FString Remove;` — `UPROPERTY(Transient, VisibleAnywhere, Category = "nocategory", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L85 _public prototype_ `void ReloadSubject();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L88 _public prototype_ `void RemoveSubject();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L91 _public prototype_ `void SetMonitoring(EMetaHumanLocalLiveLinkSubjectMonitoring InMonitoringLevel, bool bInIsMonitoring);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L95 _protected member_ `TMap<EMetaHumanLocalLiveLinkSubjectMonitoring, int32> Monitoring;`
- L97 _protected prototype_ `virtual void OnUpdate(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L101 _private member_ `int32 FPSCount = 0;`
- L102 _private member_ `double FPSStart = 0;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdate, TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanMediaSamplerLiveLinkSubject.h` (Public)


#### class `FMetaHumanMediaSamplerLiveLinkSubject`  
`class FMetaHumanMediaSamplerLiveLinkSubject : public FMetaHumanLocalLiveLinkSubject`  
_L11-40_
- inherits: `FMetaHumanLocalLiveLinkSubject`
- L15 _public prototype_ `FMetaHumanMediaSamplerLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanLocalLiveLinkSubjectSettings* InSettings);`
- L17 _public prototype_ `virtual void Start() override;`
- L18 _public prototype_ `virtual void Stop() override;`
- L22 _protected prototype_ `virtual void MediaSamplerMain() = 0;`
- L39 _private member_ `FMediaSamplerRunnable MediaSamplerRunnable;`

#### class `FMetaHumanMediaSamplerLiveLinkSubject::FMediaSamplerRunnable`  
`class FMediaSamplerRunnable : public FRunnable`  
_L26-37_
- inherits: `FRunnable`
- L30 _public prototype_ `virtual uint32 Run() override;`
- L32 _public prototype_ `void Start(TFunction<void()> InMainFunction);`
- L34 _public member_ `TFunction<void()> MainFunction;`
- L36 _public member_ `TUniquePtr<FRunnableThread> Thread;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanMediaSourceCreateParams.h` (Public)


#### struct `FMetaHumanMediaSourceCreateParams`  
`struct FMetaHumanMediaSourceCreateParams`  
_L10-54_
- reflection: `USTRUCT()`
- L17 _public member_ `FString VideoName;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L20 _public member_ `FString VideoURL;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L23 _public member_ `int32 VideoTrack = -1;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L26 _public member_ `int32 VideoTrackFormat = -1;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L29 _public member_ `FString VideoTrackFormatName;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L32 _public member_ `FString AudioName;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L35 _public member_ `FString AudioURL;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L38 _public member_ `int32 AudioTrack = -1;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L41 _public member_ `int32 AudioTrackFormat = -1;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L44 _public member_ `FString AudioTrackFormatName;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L47 _public member_ `double StartTimeout = 5;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L50 _public member_ `double FormatWaitTime = 0.1;` — `UPROPERTY(EditAnywhere, Category = "Params")`
- L53 _public member_ `double SampleTimeout = 5;` — `UPROPERTY(EditAnywhere, Category = "Params")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanMediaSourceWidget.h` (Public)


#### class `SMetaHumanMediaSourceWidget`  
`class SMetaHumanMediaSourceWidget : public SCompoundWidget`  
_L11-55_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanMediaSourceWidget)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, EMediaType InMediaType = EMediaType::VideoAndAudio);`
- L27 _public prototype_ `FMetaHumanMediaSourceCreateParams GetCreateParams() const;`
- L28 _public prototype_ `bool CanCreate() const;`
- L48 _public prototype_ `TSharedPtr<SWidget> GetWidget(EWidgetType InWidgetType) const;`
- L50 _public prototype_ `void Repopulate();`
- L54 _private member_ `TSharedPtr<class SMetaHumanMediaSourceWidgetImpl> Impl;`

#### enum `SMetaHumanMediaSourceWidget::EMediaType`  
`enum EMediaType`  
_L18-23_
- L20 _public enumerator_ `Video = 0`
- L21 _public enumerator_ `Audio`
- L22 _public enumerator_ `VideoAndAudio`

#### enum `SMetaHumanMediaSourceWidget::EWidgetType`  
`enum EWidgetType`  
_L30-46_
- L32 _public enumerator_ `VideoDevice = 0`
- L33 _public enumerator_ `VideoTrack`
- L34 _public enumerator_ `VideoTrackFormat`
- L35 _public enumerator_ `AudioDevice`
- L36 _public enumerator_ `AudioTrack`
- L37 _public enumerator_ `AudioTrackFormat`
- L38 _public enumerator_ `Filtered`
- L39 _public enumerator_ `StartTimeout`
- L40 _public enumerator_ `FormatWaitTime`
- L41 _public enumerator_ `SampleTimeout`
- L43 _public enumerator_ `VideoDeviceType`
- L44 _public enumerator_ `AudioDeviceType #endif`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoBaseLiveLinkSubject.h` (Public)


#### class `FMetaHumanVideoBaseLiveLinkSubject`  
`class FMetaHumanVideoBaseLiveLinkSubject : public FMetaHumanMediaSamplerLiveLinkSubject`  
_L18-67_
- inherits: `FMetaHumanMediaSamplerLiveLinkSubject`
- L22 _public prototype_ `FMetaHumanVideoBaseLiveLinkSubject(ILiveLinkClient* InLiveLinkClient, const FGuid& InSourceGuid, const FName& InSubjectName, UMetaHumanVideoBaseLiveLinkSubjectSettings* InSettings);`
- L24 _public prototype_ `void SetHeadOrientation(bool bInHeadOrientation);`
- L25 _public prototype_ `void SetHeadTranslation(bool bInHeadTranslation);`
- L26 _public prototype_ `void SetHeadStabilization(bool bInHeadStabilization);`
- L27 _public prototype_ `void SetMonitorImage(EHyprsenseRealtimeNodeDebugImage InMonitorImage);`
- L28 _public prototype_ `void SetRotation(EMetaHumanVideoRotation InRotation);`
- L29 _public prototype_ `void SetFocalLength(float bInFocalLength);`
- L31 _public prototype_ `void MarkNeutralFrame();`
- L46 _protected prototype_ `void AddVideoSample(FVideoSample&& InVideoSample);`
- L47 _protected prototype_ `void SetError(const FString& InErrorMessage);`
- L49 _protected prototype_ `virtual void ExtractPipelineData(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData) override;`
- L51 _protected prototype_ `virtual void FinalizeAnalyticsItems() override;`
- L55 _private member_ `UMetaHumanVideoBaseLiveLinkSubjectSettings* VideoBaseLiveLinkSubjectSettings = nullptr;`
- L57 _private member_ `bool bHeadOrientation = true;`
- L58 _private member_ `bool bHeadTranslation = true;`
- L60 _private member_ `FString MonitorImageHistory;`
- L61 _private member_ `TArray<int32> SolverStates;`
- L63 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FNeutralFrameNode> NeutralFrame;`
- L64 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FVideoSourceNode> VideoSource;`
- L65 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FUEImageRotateNode> Rotation;`
- L66 _private member_ `TSharedPtr<UE::MetaHuman::Pipeline::FHyprsenseRealtimeNode> RealtimeMonoSolver;`

#### class `FMetaHumanVideoBaseLiveLinkSubject::FVideoSample`  
`class FVideoSample`  
_L35-44_
- L38 _public member_ `int32 Width = 0;`
- L39 _public member_ `int32 Height = 0;`
- L40 _public member_ `TArray<uint8> Data;`
- L41 _public member_ `FQualifiedFrameTime Time;`
- L42 _public member_ `ETimeSource TimeSource = ETimeSource::NotSet;`
- L43 _public member_ `int32 NumDropped = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace Pipeline` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoBaseLiveLinkSubjectMonitorWidget.h` (Public)


#### class `SMetaHumanVideoBaseLiveLinkSubjectMonitorWidget`  
`class SMetaHumanVideoBaseLiveLinkSubjectMonitorWidget : public SCompoundWidget, public FGCObject`  
_L19-54_
- inherits: `SCompoundWidget,FGCObject`
- L23 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanVideoBaseLiveLinkSubjectMonitorWidget)`
- L26 _public prototype_ `virtual ~SMetaHumanVideoBaseLiveLinkSubjectMonitorWidget();`
- L28 _public prototype_ `void Construct(const FArguments& InArgs, UMetaHumanVideoBaseLiveLinkSubjectSettings* InSettings, bool bInAllowResize);`
- L31 _public prototype_ `virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;`
- L35 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L36 _public prototype_ `virtual FString GetReferencerName() const override;`
- L41 _private member_ `TObjectPtr<UMetaHumanVideoBaseLiveLinkSubjectSettings> Settings = nullptr;`
- L43 _private prototype_ `void OnUpdate(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData);`
- L46 _private member_ `TSharedPtr<SMetaHumanImageViewer> ImageViewer;` — 2D Image review window
- L47 _private member_ `FSlateBrush ImageViewerBrush;`
- L48 _private member_ `TObjectPtr<UTexture2D> ImageTexture;`
- L50 _private prototype_ `void FillTexture(const UE::MetaHuman::Pipeline::FUEImageDataType& InImage);`
- L51 _private prototype_ `void ClearTexture();`
- L53 _private member_ `FTimerHandle EditorTimerHandle;`

#### class `UMetaHumanVideoBaseLiveLinkSubjectMonitorWidget`  
`class UMetaHumanVideoBaseLiveLinkSubjectMonitorWidget : public UWidget`  
_L59-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- L66 _public prototype_ `void SetSubjectSettings(UMetaHumanVideoBaseLiveLinkSubjectSettings* InSettings);` — `UFUNCTION(BlueprintCallable, Category = "MetaHumanLiveLink")`
- L71 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L72 _protected prototype_ `virtual void ReleaseSlateResources(bool) override;`
- L77 _private member_ `TSharedPtr<SMetaHumanVideoBaseLiveLinkSubjectMonitorWidget> Widget = nullptr;`
- L80 _private member_ `TObjectPtr<UMetaHumanVideoBaseLiveLinkSubjectSettings> Settings = nullptr;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoBaseLiveLinkSubjectSettings.h` (Public)


#### enum `EMetaHumanVideoRotation`  
`enum class EMetaHumanVideoRotation : uint8`  
_L14-20_
- reflection: `UENUM()`
- L16 _public enumerator_ `Zero = 0`
- L17 _public enumerator_ `Ninety`
- L18 _public enumerator_ `OneEighty`
- L19 _public enumerator_ `TwoSeventy`

#### enum `EMetaHumanVideoBaseLiveLinkSubjectState`  
`enum class EMetaHumanVideoBaseLiveLinkSubjectState : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Unknown = 0`
- L26 _public enumerator_ `NoFaceDetected`
- L27 _public enumerator_ `SubjectTooFar`

#### class `UMetaHumanVideoBaseLiveLinkSubjectSettings`  
`class UMetaHumanVideoBaseLiveLinkSubjectSettings : public UMetaHumanLocalLiveLinkSubjectSettings`  
_L31-146_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanLocalLiveLinkSubjectSettings`
- L38 _public prototype_ `UMetaHumanVideoBaseLiveLinkSubjectSettings();`
- L42 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L51 _public member_ `EMetaHumanVideoBaseLiveLinkSubjectState VideoStateEnum = EMetaHumanVideoBaseLiveLinkSubjectState::Unknown;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")` — This is only set when the base class StateEnum == EMetaHumanLocalLiveLinkSubjectState::DeviceSpecific
- L55 _public member_ `bool bHeadOrientation = true;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — When enabled the rotational orientation of the head is output. You may want to disable this option if the head is being tracked by other means (eg mocap) or if you wish to analyze the facial animation on a static head.
- L58 _public prototype_ `void SetHeadOrientation(bool HeadOrientation);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L61 _public prototype_ `void GetHeadOrientation(bool& HeadOrientation) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L65 _public member_ `bool bHeadTranslation = true;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — When enabled, and a neutral head position has been set, the position of the head is output. You may want to disable this option if the head is being tracked by other means (eg mocap) or if you wish to analyze the facial animation on a static head.
- L68 _public prototype_ `void SetHeadTranslation(bool HeadTranslation);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L71 _public prototype_ `void GetHeadTranslation(bool& HeadTranslation) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L75 _public member_ `bool bHeadStabilization = true;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Reduces noise in head position and orientation.
- L78 _public prototype_ `void SetHeadStabilization(bool HeadStabilization);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L81 _public prototype_ `void GetHeadStabilization(bool& HeadStabilization) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L85 _public member_ `FMonocularAnimationPipelineModels MonocularAnimationPipelineModels;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Information", meta = (DisplayName = "Models"), meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — The models to be used by the realtime pipeline
- L89 _public member_ `EHyprsenseRealtimeNodeDebugImage MonitorImage = EHyprsenseRealtimeNodeDebugImage::None;` — `UPROPERTY(EditAnywhere, Category = "Image", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Shows the video being processed. Options are None (no image), Input Video (the raw video), or Trackers (the video with tracking markers overlaid which can be useful in analysing the stability of the animation solve). Note this monitoring takes up resources so you may want to use it sparingly especially at high webcam frame rate or heavily loaded scenes
- L92 _public prototype_ `void SetMonitorImage(UPARAM(DisplayName = "MonitorImage") EHyprsenseRealtimeNodeDebugImage InMo` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L95 _public prototype_ `void GetMonitorImage(UPARAM(DisplayName = "MonitorImage") EHyprsenseRealtimeNodeDebugImage& OutMonitorI` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L99 _public member_ `FVector2D MonitorImageSize = FVector2D::ZeroVector;` — `UPROPERTY()` — Size of the widget showing the video being processed.
- L103 _public member_ `EMetaHumanVideoRotation Rotation = EMetaHumanVideoRotation::Zero;` — `UPROPERTY(EditAnywhere, Category = "Controls", DisplayName = "Image Rotation", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — Allows for the input video to be rotated by 90, 180, or 270 degrees prior to processing. This can be used to account for different camera mountings.
- L106 _public prototype_ `void SetRotation(UPARAM(DisplayName = "Rotation") EMetaHumanVideoRotation InRo` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L109 _public prototype_ `void GetRotation(UPARAM(DisplayName = "Rotation") EMetaHumanVideoRotation& OutRotation` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman Live Link")`
- L113 _public member_ `double FocalLength = -1;` — `UPROPERTY(VisibleAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))` — The focal length of the video being processed.
- L115 _public prototype_ `virtual void CaptureNeutralHeadPose() override;`
- L119 _public member_ `FString Confidence;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")` — A confidence value produced by the processing between 0 (poor) and 1 (good).
- L122 _public member_ `float ConfidenceValue = -1;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L126 _public member_ `FString Resolution;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "60"))` — The resolution of the video being processed.
- L129 _public member_ `FIntPoint ImageResolution = FIntPoint(-1, -1);` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L133 _public member_ `FString Dropping;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Information", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides, DisplayPriority = "70"))` — Whether video frames are being dropped because they can not be processed fast enough.
- L136 _public member_ `int32 Dropped = -1;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Information")`
- L140 _protected prototype_ `virtual void OnUpdate(TSharedPtr<UE::MetaHuman::Pipeline::FPipelineData> InPipelineData) override;`
- L144 _private member_ `int32 DroppedCount = -1;`
- L145 _private member_ `double DroppedStart = 0;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoLiveLinkSettings.h` (Public)


#### class `UMetaHumanVideoLiveLinkSettings`  
`class UMetaHumanVideoLiveLinkSettings : public UObject`  
_L14-31_
- reflection: `UCLASS(config = Editor, defaultconfig)`
- inherits: `UObject`
- L21 _public member_ `bool bHeadOrientation = true;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`
- L24 _public member_ `bool bHeadTranslation = true;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`
- L27 _public member_ `EHyprsenseRealtimeNodeDebugImage MonitorImage = EHyprsenseRealtimeNodeDebugImage::None;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`
- L30 _public member_ `int32 MonitorImageHeight = 200;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoLiveLinkSourceSettings.h` (Public)


#### class `UMetaHumanVideoLiveLinkSourceSettings`  
`class UMetaHumanVideoLiveLinkSourceSettings : public UMetaHumanLocalLiveLinkSourceSettings`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UMetaHumanLocalLiveLinkSourceSettings`
- L22 _public member_ `FMonocularAnimationPipelineModels MonocularAnimationPipelineModels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Create", meta = (DisplayName = "Models"))` — The models to be used by the realtime pipeline

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoLiveLinkSubjectSettings.h` (Public)


#### class `UMetaHumanVideoLiveLinkSubjectSettings`  
`class UMetaHumanVideoLiveLinkSubjectSettings : public UMetaHumanVideoBaseLiveLinkSubjectSettings`  
_L12-20_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanVideoBaseLiveLinkSubjectSettings`
- L19 _public member_ `FMetaHumanMediaSourceCreateParams MediaSourceCreateParams;` — `UPROPERTY()`
