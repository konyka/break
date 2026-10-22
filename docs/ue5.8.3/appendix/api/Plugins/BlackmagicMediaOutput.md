# Plugins / BlackmagicMediaOutput

- module root: `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaOutput`
- headers: 3; symbols: 95
- symbol kinds: class=2, delegate=1, enum=4, enumerator=8, member=36, namespace=4, prototype=40
- PrivateDependencyModuleNames: BlackmagicCore, Core, CoreUObject, Engine, GPUTextureTransfer, RHI, RenderCore, Slate
- PublicDependencyModuleNames: BlackmagicMedia, MediaIOCore

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaOutput/Private/BlackmagicMediaOutputModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicMediaOutput, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicMediaOutput, Log, All);`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaOutput/Public/BlackmagicMediaCapture.h` (Public)


#### class `UBlackmagicMediaCapture`  
`class UBlackmagicMediaCapture : public UMediaCapture`  
_L35-128_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaCapture`
- desc: Output Media for Blackmagic streams. The output format could be any of EBlackmagicMediaOutputPixelFormat.
- L40 _public prototype_ `UBlackmagicMediaCapture();`
- L43 _public prototype_ `virtual bool HasFinishedProcessing() const override;`
- L45 _protected prototype_ `virtual bool ValidateMediaOutput() const override;`
- L46 _protected prototype_ `virtual bool InitializeCapture() override;`
- L47 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L48 _protected prototype_ `virtual bool UpdateSceneViewportImpl(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L49 _protected prototype_ `virtual bool UpdateRenderTargetImpl(UTextureRenderTarget2D* InRenderTarget) override;`
- L50 _protected prototype_ `virtual bool UpdateAudioDeviceImpl(const FAudioDeviceHandle& InAudioDeviceHandle) override;`
- L51 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L52 _protected prototype_ `virtual bool ShouldCaptureRHIResource() const override;`
- L54 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L55 _protected prototype_ `virtual void OnFrameCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData) override;`
- L56 _protected prototype_ `virtual void OnRHIResourceCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L57 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L58 _protected prototype_ `virtual void LockDMATexture_RenderThread(FTextureRHIRef InTexture) override;`
- L59 _protected prototype_ `virtual void UnlockDMATexture_RenderThread(FTextureRHIRef InTexture) override;`
- L60 _protected prototype_ `virtual bool SupportsAnyThreadCapture() const override;`
- L61 _protected prototype_ `virtual const FMatrix& GetRGBToYUVConversionMatrix() const override;`
- L62 _protected prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L63 _protected prototype_ `virtual bool ShouldCaptureThisFrame(const FCaptureBaseData& InBaseData) const override;`
- L66 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L67 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L75 _private prototype_ `bool InitBlackmagic(UBlackmagicMediaOutput* InMediaOutput);`
- L76 _private prototype_ `bool CreateAudioOutput(const FAudioDeviceHandle& InAudioDeviceHandle, const UBlackmagicMediaOutput* InBlackmagicMediaOutput);`
- L77 _private prototype_ `void WaitForSync_AnyThread();`
- L78 _private prototype_ `void OutputAudio_AnyThread(const FCaptureBaseData& InBaseData, const BlackmagicDesign::FTimecode& Timecode);`
- L79 _private prototype_ `void ApplyViewportTextureAlpha(TSharedPtr<FSceneViewport> InSceneViewport);`
- L80 _private prototype_ `void RestoreViewportTextureAlpha(TSharedPtr<FSceneViewport> InSceneViewport);`
- L81 _private prototype_ `void OnFrameCapturedInternal_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData);`
- L85 _private member_ `BlackmagicMediaCaptureHelpers::FBlackmagicMediaCaptureEventCallback* EventCallback = nullptr;`
- L88 _private member_ `bool bWaitForSyncEvent;` — Option from MediaOutput
- L89 _private member_ `bool bLogDropFrame;`
- L92 _private member_ `EBlackmagicMediaOutputPixelFormat BlackmagicMediaOutputPixelFormat;` — MediaOutput cached value
- L95 _private member_ `bool bSavedIgnoreTextureAlpha;` — Saved IgnoreTextureAlpha flag from viewport
- L96 _private member_ `bool bIgnoreTextureAlphaChanged;`
- L99 _private member_ `FFrameRate FrameRate;` — Selected FrameRate of this output
- L102 _private member_ `FCriticalSection CopyingCriticalSection;` — Critical section for synchronizing access to the OutputChannel
- L105 _private member_ `FEvent* WakeUpEvent;` — Event to wakeup When waiting for sync
- L108 _private member_ `uint64 LastFrameDropCount_BlackmagicThread;` — Last frame drop count to detect count
- L111 _private member_ `TSharedPtr<class FMediaIOAudioOutput> AudioOutput;` — Holds an audio output that will receive samples from the media io core subsystem.
- L113 _private member_ `EBlackmagicMediaOutputAudioBitDepth AudioBitDepth = EBlackmagicMediaOutputAudioBitDepth::Signed_16Bits;`
- L115 _private member_ `uint32 NumAudioSamplesPerFrame = 0;`
- L117 _private member_ `bool bOutputAudio = false;`
- L119 _private member_ `uint8 NumOutputChannels = 0;`
- L122 _private member_ `TArray<FTextureRHIRef> TexturesToRelease;` — Textures to release when the capture has stopped. Must be released after GPUTextureTransfer textures have been unregistered.
- L125 _private member_ `double OutputAudioTimestamp;` — The last time OutputAudio was called. Used to adjust the number of audio samples to grab on each frame depending on the frame time.
- L127 _private member_ `TSharedPtr<UE::GPUTextureTransfer::ITextureTransfer> TextureTransfer;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace BlackmagicMediaCaptureHelpers`
- L20 _namespace_ `namespace BlackmagicDesign`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicMediaOutput/Public/BlackmagicMediaOutput.h` (Public)


#### enum `EBlackmagicMediaOutputPixelFormat`  
`enum class EBlackmagicMediaOutputPixelFormat : uint8`  
_L16-20_
- reflection: `UENUM()`
- desc: Native data format.
- L18 _public enumerator_ `PF_8BIT_YUV UMETA(DisplayName = "8bit YUV")`
- L19 _public enumerator_ `PF_10BIT_YUV UMETA(DisplayName = "10bit YUV")`

#### enum `EBlackmagicMediaOutputAudioSampleRate`  
`enum class EBlackmagicMediaOutputAudioSampleRate : uint32`  
_L23-26_
- reflection: `UENUM()`
- L25 _public enumerator_ `SR_48k = 48000 UMETA(DisplayName = "48 kHz")`

#### enum `EBlackmagicMediaAudioOutputChannelCount`  
`enum class EBlackmagicMediaAudioOutputChannelCount : uint8`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `CH_2 = 2 UMETA(DisplayName = "2")`
- L32 _public enumerator_ `CH_8 = 8 UMETA(DisplayName = "8")`
- L33 _public enumerator_ `CH_16 = 16 UMETA(DisplayName = "16")`

#### enum `EBlackmagicMediaOutputAudioBitDepth`  
`enum class EBlackmagicMediaOutputAudioBitDepth : uint8`  
_L37-41_
- reflection: `UENUM()`
- L39 _public enumerator_ `Signed_16Bits = 16 UMETA(DisplayName = "16 bits signed")`
- L40 _public enumerator_ `Signed_32Bits = 32 UMETA(DisplayName = "32 bits signed")`

#### class `UBlackmagicMediaOutput`  
`class UBlackmagicMediaOutput : public UMediaOutput`  
_L49-170_
- reflection: `UCLASS(BlueprintType, PrioritizeCategories=(Blackmagic, Output, Synchronization, Debug), meta = (MediaIOCustomLayout = "Blackmagic"))`
- inherits: `UMediaOutput`
- desc: Output information for a MediaCapture. @note	'Frame Buffer Pixel Format' must be set to at least 8 bits of alpha to enabled the Key. @note	'Enable alpha channel support in post-processing' must be set to 'Allow through tonemapper' to enabled the Key.
- L56 _public member_ `FMediaIOOutputConfiguration OutputConfiguration;` — `UPROPERTY(EditAnywhere, Category = "Blackmagic", meta = (DisplayName = "Configuration"))` — The device, port and video settings that correspond to the output.
- L61 _public member_ `int32 AudioBufferSize = 5*1024;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Size of the buffer that holds rendered audio samples, a bigger buffer will produce an output of greater quality but will introduce more delay.
- L65 _public member_ `EBlackmagicMediaOutputAudioSampleRate AudioSampleRate = EBlackmagicMediaOutputAudioSampleRate::SR_48k;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Sample rate of the audio output.
- L69 _public member_ `EBlackmagicMediaAudioOutputChannelCount OutputChannelCount = EBlackmagicMediaAudioOutputChannelCount::CH_2;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Number of audio channels to output.
- L73 _public member_ `EBlackmagicMediaOutputAudioBitDepth AudioBitDepth = EBlackmagicMediaOutputAudioBitDepth::Signed_16Bits;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Bit depth of each audio sample.
- L77 _public member_ `EMediaIOTimecodeFormat TimecodeFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Whether to embed the Engine's timecode to the output frame.
- L81 _public member_ `EBlackmagicMediaOutputPixelFormat PixelFormat;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Native data format internally used by the device before being converted to SDI/HDMI signal.
- L85 _public member_ `bool bInvertKeyOutput;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — Invert Key Output
- L89 _public member_ `bool bOutputAudio;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Output")` — Whether to capture and output audio from the engine.
- L97 _public member_ `int32 NumberOfBlackmagicBuffers;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output", meta = (UIMin = 3, UIMax = 4, ClampMin = 3, ClampMax = 4))` — Number of frame used to transfer from the system memory to the Blackmagic card. A smaller number is most likely to cause missed frame. A bigger number is most likely to increase latency.
- L105 _public member_ `bool bInterlacedFieldsTimecodeNeedToMatch;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — Only make sense in interlaced mode. When creating a new Frame the 2 fields need to have the same timecode value. The Engine's need a TimecodeProvider (or the default system clock) that is in sync with the generated fields.
- L111 _public member_ `bool bOutputInterlaceAsProgressive = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — If this is enabled when outputting media in interlace format, frames will be treated as progressive and will be outputted as-is. (Experimental)
- L118 _public member_ `bool bOutputInterlaceOnEvenFrames = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Output")` — Whether to only schedule interlace frames if we land on an even timecode. Useful when you have an interlace input and want to ensure that we interlace the original frames. (Experimental)
- L124 _public member_ `FBlackmagicMediaHDROptions HDROptions;` — `UPROPERTY(EditAnywhere, Category = "Output", DisplayName="HDR")` — HDR Metadata of the video signal.
- L130 _public member_ `bool bUseMultithreadedScheduling = false;` — `UPROPERTY(BlueprintReadWrite, AdvancedDisplay, EditAnywhere, Category = "Output")` — Whether to use multi threaded scheduling which should improve performance when outputting 4k and 8k content. (Experimental)
- L134 _public member_ `bool bWaitForSyncEvent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Synchronization")` — Try to maintain a the engine "Genlock" with the VSync signal.
- L140 _public member_ `bool bLogDropFrame;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Log a warning when there's a drop frame.
- L144 _public member_ `bool bEncodeTimecodeInTexel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug", meta = (DisplayName = "Burn Frame Timecode"))` — Burn Frame Timecode on the output without any frame number clipping.
- L147 _public prototype_ `bool Validate(FString& FailureReason) const;`
- L149 _public prototype_ `FFrameRate GetRequestedFrameRate() const;`
- L150 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L151 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L152 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L155 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L156 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L160 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L165 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L166 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
