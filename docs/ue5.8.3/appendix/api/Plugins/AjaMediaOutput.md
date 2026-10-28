# Plugins / AjaMediaOutput

- module root: `Plugins/Media/AjaMedia/Source/AjaMediaOutput`
- headers: 5; symbols: 124
- symbol kinds: class=5, delegate=1, enum=3, enumerator=6, function=4, member=48, namespace=3, prototype=53, struct=1
- PrivateDependencyModuleNames: AjaCore, Core, CoreUObject, EditorFramework, Engine, GPUTextureTransfer, MainFrame, MovieSceneCapture, RHI, RenderCore, Slate, SlateCore, TimeManagement, UnrealEd
- PublicDependencyModuleNames: AjaMedia, MediaIOCore

### `Plugins/Media/AjaMedia/Source/AjaMediaOutput/Private/AjaMediaOutputModule.h` (Private)


#### class `FAjaMediaOutputModule`  
`class FAjaMediaOutputModule : public IAjaMediaOutputModule`  
_L8-13_
- inherits: `IAjaMediaOutputModule`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Media/AjaMedia/Source/AjaMediaOutput/Public/AjaMediaCapture.h` (Public)


#### class `UAjaMediaCapture`  
`class UAjaMediaCapture : public UMediaCapture`  
_L33-147_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaCapture`
- desc: Output Media for AJA streams. The output format could be any of EAjaMediaOutputPixelFormat.
- L38 _public prototype_ `UAjaMediaCapture();`
- L39 _public prototype_ `~UAjaMediaCapture();`
- L42 _public prototype_ `virtual bool HasFinishedProcessing() const override;`
- L44 _protected prototype_ `virtual bool ValidateMediaOutput() const override;`
- L45 _protected prototype_ `virtual bool InitializeCapture() override;`
- L46 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L47 _protected prototype_ `virtual bool UpdateSceneViewportImpl(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L48 _protected prototype_ `virtual bool UpdateRenderTargetImpl(UTextureRenderTarget2D* InRenderTarget) override;`
- L49 _protected prototype_ `virtual bool UpdateMediaTextureImpl(UMediaTexture* InMediaTexture) override;`
- L50 _protected prototype_ `virtual bool UpdateAudioDeviceImpl(const FAudioDeviceHandle& InAudioDeviceHandle) override;`
- L51 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L52 _protected prototype_ `virtual void PostCaptureCleanupImpl() override;`
- L53 _protected function_ `virtual bool SupportsStopCapture_Future() const override`
- L54 _protected prototype_ `virtual TFuture<void> StopCapture_Future() override;`
- L55 _protected prototype_ `virtual bool ShouldCaptureRHIResource() const override;`
- L56 _protected prototype_ `virtual bool ShouldCaptureThisFrame(const FCaptureBaseData& InBaseData) const override;`
- L58 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L59 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L60 _protected prototype_ `virtual void OnRHIResourceCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L61 _protected prototype_ `virtual void LockDMATexture_RenderThread(FTextureRHIRef InTexture) override;`
- L62 _protected prototype_ `virtual void UnlockDMATexture_RenderThread(FTextureRHIRef InTexture) override;`
- L63 _protected prototype_ `virtual void OnFrameCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData) override;`
- L64 _protected prototype_ `virtual bool SupportsAnyThreadCapture() const override;`
- L65 _protected prototype_ `virtual const FMatrix& GetRGBToYUVConversionMatrix() const override;`
- L66 _protected prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L69 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L70 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L79 _private prototype_ `bool InitAJA(UAjaMediaOutput* InMediaOutput);`
- L80 _private prototype_ `bool CreateAudioOutput(const FAudioDeviceHandle& InAudioDeviceHandle, const UAjaMediaOutput* InAjaMediaOutput);`
- L81 _private prototype_ `void WaitForSync_AnyThread() const;`
- L82 _private prototype_ `void OutputAudio_AnyThread(const AJA::AJAOutputFrameBufferData& FrameBuffer) const;`
- L83 _private prototype_ `void ApplyViewportTextureAlpha(TSharedPtr<FSceneViewport> InSceneViewport);`
- L84 _private prototype_ `void RestoreViewportTextureAlpha(TSharedPtr<FSceneViewport> InSceneViewport);`
- L85 _private prototype_ `bool CleanupPreEditorExit();`
- L86 _private prototype_ `void OnEnginePreExit();`
- L87 _private prototype_ `void OnFrameCapturedInternal_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData);`
- L88 _private prototype_ `void OnAudioBufferReceived_AudioThread(Audio::FDeviceId DeviceId, float* Data, int32 NumSamples) const;`
- L98 _private member_ `TPimplPtr<FAJAOutputChannel> OutputChannel;` — AJA Port for outputting
- L99 _private member_ `TPimplPtr<FAjaOutputCallback> OutputCallback;`
- L102 _private member_ `FString PortName;` — Name of this output port
- L105 _private member_ `bool bWaitForSyncEvent;` — Option from MediaOutput
- L106 _private member_ `bool bLogDropFrame;`
- L107 _private member_ `bool bEncodeTimecodeInTexel;`
- L108 _private member_ `EAjaMediaOutputPixelFormat PixelFormat;`
- L109 _private member_ `bool UseKey;`
- L112 _private member_ `bool bSavedIgnoreTextureAlpha;` — Saved IgnoreTextureAlpha flag from viewport
- L113 _private member_ `bool bIgnoreTextureAlphaChanged;`
- L116 _private member_ `FFrameRate FrameRate;` — Selected FrameRate of this output
- L119 _private member_ `FCriticalSection CopyingCriticalSection;` — Critical section for synchronizing access to the OutputChannel
- L122 _private member_ `FEvent* WakeUpEvent;` — Event to wakeup When waiting for sync
- L125 _private member_ `TSharedPtr<class FMediaIOAudioOutput> AudioOutput;` — Holds an audio output that captures audio from the engine.
- L128 _private member_ `int32 NumOutputChannels = 0;` — Number of audio channels output to the AJA card.
- L131 _private member_ `int32 NumInputChannels =0;` — Number of audio channels the engine is rendering to.
- L133 _private member_ `bool bOutputAudio = false;`
- L136 _private member_ `bool bDirectlyWriteAudio = false;` — Whether to write audio on the audio thread instead of collecting samples and outputting on the render thread..
- L139 _private member_ `TArray<FTextureRHIRef> TexturesToRelease;` — Textures to release when the capture has stopped. Must be released after GPUTextureTransfer textures have been unregistered.
- L142 _private member_ `FDelegateHandle CanCloseEditorDelegateHandle;` — Handle for the delegate used to clean up AJA on editor shutdown.
- L144 _private member_ `mutable int32 AudioSamplesSentLastFrame = 0;`
- L146 _private member_ `TSharedPtr<UE::GPUTextureTransfer::ITextureTransfer> TextureTransfer;`

#### struct `UAjaMediaCapture::FAudioBuffer`  
`struct FAudioBuffer`  
_L90-94_
- L92 _public member_ `Audio::FAlignedFloatBuffer Data;`
- L93 _public member_ `int32 NumChannels = 0;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace AJA`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)

### `Plugins/Media/AjaMedia/Source/AjaMediaOutput/Public/AjaMediaFrameGrabberProtocol.h` (Public)


#### class `UAjaFrameGrabberProtocol`  
`class UAjaFrameGrabberProtocol : public UMovieSceneImageCaptureProtocolBase`  
_L15-48_
- reflection: `UCLASS(meta=(DisplayName="AJA Output", CommandLineID="AJAOutput"))`
- inherits: `UMovieSceneImageCaptureProtocolBase`
- L20 _public prototype_ `UAjaFrameGrabberProtocol(const FObjectInitializer& ObjInit);`
- L23 _public prototype_ `virtual bool StartCaptureImpl() override;` — ~UMovieSceneCaptureProtocolBase implementation
- L24 _public prototype_ `virtual bool HasFinishedProcessingImpl() const override;`
- L25 _public prototype_ `virtual void FinalizeImpl() override;`
- L26 _public function_ `virtual bool CanWriteToFileImpl(const TCHAR* InFilename, bool bOverwriteExisting) const`
- L33 _public member_ `FSoftObjectPath MediaOutput;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category=AJA, meta=(AllowedClasses="/Script/AjaMediaOutput.AjaMediaOutput"))` — AJA Setting to use for the FrameGrabberProtocol
- L37 _public member_ `FString Information;` — `UPROPERTY(VisibleAnywhere, Transient, Category=AJA)` — States unused options for AJAFrameGrabberProtocolSettings
- L43 _private member_ `TObjectPtr<UAjaMediaOutput> TransientMediaOutputPtr;` — `UPROPERTY(Transient)` — Transient media output pointer to keep the media output alive while this protocol is in use
- L47 _private member_ `TObjectPtr<UAjaMediaCapture> TransientMediaCapturePtr;` — `UPROPERTY(Transient)` — Transient media capture pointer that will capture the viewport

### `Plugins/Media/AjaMedia/Source/AjaMediaOutput/Public/AjaMediaOutput.h` (Public)


#### enum `EAjaMediaOutputPixelFormat`  
`enum class EAjaMediaOutputPixelFormat : uint8`  
_L16-20_
- reflection: `UENUM()`
- desc: Native data format.
- L18 _public enumerator_ `PF_8BIT_YUV UMETA(DisplayName = "8bit YUV")`
- L19 _public enumerator_ `PF_10BIT_YUV UMETA(DisplayName = "10bit YUV")`

#### enum `EAjaMediaOutputAudioSampleRate`  
`enum class EAjaMediaOutputAudioSampleRate : uint32`  
_L23-26_
- reflection: `UENUM()`
- L25 _public enumerator_ `SR_48k = 48000 UMETA(DisplayName = "48 kHz")`

#### enum `EAjaMediaOutputChannelConfiguration`  
`enum class EAjaMediaOutputChannelConfiguration : uint8`  
_L32-37_
- reflection: `UENUM()`
- desc: Number of output audio channels
- L34 _public enumerator_ `CH_6 = 6 UMETA(DisplayName = "6 Channels")`
- L35 _public enumerator_ `CH_8 = 8 UMETA(DisplayName = "8 Channels")`
- L36 _public enumerator_ `CH_16 = 16 UMETA(DisplayName = "16 Channels")`

#### class `UAjaMediaOutput`  
`class UAjaMediaOutput : public UMediaOutput`  
_L45-176_
- reflection: `UCLASS(BlueprintType, PrioritizeCategories=(AJA, Output, Synchronization, Debug), meta=(MediaIOCustomLayout="AJA"))`
- inherits: `UMediaOutput`
- desc: Output information for an aja media capture. @note	'Frame Buffer Pixel Format' must be set to at least 8 bits of alpha to enabled the Key. @note	'Enable alpha channel support in post-processing' must be set to 'Allow through tonemapper' to enabled the Key.
- L53 _public member_ `FMediaIOOutputConfiguration OutputConfiguration;` — `UPROPERTY(EditAnywhere, Category="AJA", meta=(DisplayName="Configuration"))` — The device, port and video settings that correspond to the output.
- L59 _public member_ `bool bStopOutputOnCardTimeout = true;` — `UPROPERTY(EditAnywhere, Category = "AJA")` — If this is disabled, output will keep going even if we hit a timeout when waiting for a vertical interrupt from the card.
- L67 _public member_ `bool bOutputWithAutoCirculating;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Output")` — The output of the Audio, Ancillary and/or video will be perform at the same time. This may decrease transfer performance but each the data will be sync in relation with each other.
- L71 _public member_ `EMediaIOTimecodeFormat TimecodeFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Output")` — Whether to embed the Engine's timecode to the output frame.
- L75 _public member_ `EAjaMediaOutputPixelFormat PixelFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Output")` — Native data format internally used by the device before being converted to SDI/HDMI signal.
- L79 _public member_ `bool bOutputIn3GLevelB;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Output")` — If the video format is compatible with 3G Level A, do the conversion to output in LevelB.
- L83 _public member_ `bool bInvertKeyOutput;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — Invert Key Output
- L87 _public member_ `bool bOutputAudio;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Whether to capture and output audio from the engine.
- L91 _public member_ `int32 AudioBufferSize = 5*1024;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Size of the buffer that holds rendered audio samples, a bigger buffer will produce a more stable output signal but will introduce more delay.
- L95 _public member_ `EAjaMediaOutputChannelConfiguration NumOutputAudioChannels = EAjaMediaOutputChannelConfiguration::CH_8;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Number of audio channels used when output audio on the card.
- L99 _public member_ `EAjaMediaOutputAudioSampleRate AudioSampleRate = EAjaMediaOutputAudioSampleRate::SR_48k;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Audio output sample rate.
- L103 _public member_ `bool bOutputAudioOnAudioThread = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output", meta = (EditCondition = "bOutputWithAutoCirculating == false"))` — Whether to output audio on the audio thread instead of the rendering thread. Only available in Ping Pong mode. (Experimental)
- L111 _public member_ `int32 NumberOfAJABuffers;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Output", meta=(ClampMin=1, ClampMax=4))` — Number of frame used to transfer from the system memory to the AJA card. A smaller number is most likely to cause missed frame. A bigger number is most likely to increase latency.
- L119 _public member_ `bool bInterlacedFieldsTimecodeNeedToMatch;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Output")` — Only make sense in interlaced mode. When creating a new Frame the 2 fields need to have the same timecode value. The Engine's need a TimecodeProvider (or the default system clock) that is in sync with the generated fields.
- L125 _public member_ `bool bOutputInterlaceAsProgressive = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — If this is enabled when outputting media in interlace format, frames will be treated as progressive and will be outputted as-is. (Experimental)
- L132 _public member_ `bool bOutputInterlaceOnEvenFrames = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — Whether to only schedule interlace frames if we land on an even timecode. Useful when you have an interlace input and want to ensure that we interlace the original frames. (Experimental)
- L138 _public member_ `FAjaMediaHDROptions HDROptions;` — `UPROPERTY(EditAnywhere, Category = "Output", DisplayName="HDR")` — HDR Metadata of the video signal.
- L142 _public member_ `bool bWaitForSyncEvent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Synchronization")` — Try to maintain a the engine "Genlock" with the VSync signal.
- L147 _public member_ `bool bLogDropFrame;` — `UPROPERTY(EditAnywhere, Category="Debug")` — Log a warning when there's a drop frame.
- L151 _public member_ `bool bEncodeTimecodeInTexel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug", meta=(DisplayName="Burn Frame Timecode"))` — Burn Frame Timecode on the output without any frame number clipping.
- L154 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L156 _public prototype_ `FFrameRate GetRequestedFrameRate() const;`
- L157 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L158 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L159 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L162 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L163 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L167 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L172 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L173 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`

### `Plugins/Media/AjaMedia/Source/AjaMediaOutput/Public/IAjaMediaOutputModule.h` (Public)


#### class `IAjaMediaOutputModule`  
`class IAjaMediaOutputModule : public IModuleInterface`  
_L16-40_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L26 _public function_ `static inline IAjaMediaOutputModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaMediaOutput, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaMediaOutput, Log, All);`
