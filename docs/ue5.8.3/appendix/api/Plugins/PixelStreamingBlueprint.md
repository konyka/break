# Plugins / PixelStreamingBlueprint

- module root: `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint`
- headers: 6; symbols: 46
- symbol kinds: class=5, delegate=4, function=1, member=13, prototype=23
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, PixelStreaming
- PublicDependencyModuleNames: 

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Internal/PixelStreamingStreamerVideoInput.h` (Internal)


#### class `UPixelStreamingStreamerVideoInput`  
`class UPixelStreamingStreamerVideoInput : public UObject`  
_L10-19_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, Category = "PixelStreaming", META = (DisplayName = "Video Input"))`
- inherits: `UObject`
- L15 _public function_ `virtual TSharedPtr<FPixelStreamingVideoInput> GetVideoInput()`
- L18 _protected member_ `TSharedPtr<FPixelStreamingVideoInput> VideoInput;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Internal/PixelStreamingStreamerVideoInputBackBuffer.h` (Internal)


#### class `UPixelStreamingStreamerVideoInputBackBuffer`  
`class UPixelStreamingStreamerVideoInputBackBuffer : public UPixelStreamingStreamerVideoInput`  
_L9-15_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, Category = "PixelStreaming", META = (DisplayName = "Back Buffer Streamer Video Input"))`
- inherits: `UPixelStreamingStreamerVideoInput`
- L14 _public prototype_ `virtual TSharedPtr<FPixelStreamingVideoInput> GetVideoInput() override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Internal/PixelStreamingStreamerVideoInputMediaCapture.h` (Internal)


#### class `UPixelStreamingStreamerVideoInputMediaCapture`  
`class UPixelStreamingStreamerVideoInputMediaCapture : public UPixelStreamingStreamerVideoInput`  
_L10-16_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, Category = "PixelStreaming", META = (DisplayName = "Media Capture Streamer Video Input"))`
- inherits: `UPixelStreamingStreamerVideoInput`
- desc: Equivalent to UPixelStreamingStreamerVideoInputBackBuffer but uses the MediaIO Framework to capture the frame rather than Pixel Capture
- L15 _public prototype_ `virtual TSharedPtr<FPixelStreamingVideoInput> GetVideoInput() override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Internal/PixelStreamingStreamerVideoInputRenderTarget.h` (Internal)


#### class `UPixelStreamingStreamerVideoInputRenderTarget`  
`class UPixelStreamingStreamerVideoInputRenderTarget : public UPixelStreamingStreamerVideoInput`  
_L10-19_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, Category = "PixelStreaming", META = (DisplayName = "Render Target Streamer Video Input"))`
- inherits: `UPixelStreamingStreamerVideoInput`
- L16 _public member_ `TObjectPtr<UTextureRenderTarget2D> Target;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Video, AssetRegistrySearchable)`
- L18 _public prototype_ `virtual TSharedPtr<FPixelStreamingVideoInput> GetVideoInput() override;`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Private/PixelStreamingBlueprintPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingBlueprint, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingBlueprint, Log, All);`

### `Plugins/Media/PixelStreaming/Source/PixelStreamingBlueprint/Private/PixelStreamingStreamerComponent.h` (Private)


#### class `UPixelStreamingStreamerComponent`  
`class UPixelStreamingStreamerComponent : public UActorComponent`  
_L12-84_
- reflection: `UCLASS(BlueprintType, Blueprintable, Category = "PixelStreaming", META = (DisplayName = "Streamer Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L17 _public prototype_ `virtual ~UPixelStreamingStreamerComponent();`
- L20 _public prototype_ `FString GetId();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L23 _public prototype_ `bool IsSignallingConnected();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L26 _public prototype_ `void StartStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L29 _public prototype_ `void StopStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L32 _public prototype_ `bool IsStreaming();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L34 _public prototype_ `DECLARE_EVENT(UPixelStreamingStreamerComponent, FStreamingStartedEvent);`
- L35 _public member_ `FStreamingStartedEvent OnStreamingStarted;`
- L37 _public prototype_ `DECLARE_EVENT(UPixelStreamingStreamerComponent, FStreamingStoppedEvent);`
- L38 _public member_ `FStreamingStoppedEvent OnStreamingStopped;`
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FPixelStreamingPlayerId, uint8, TArray<uint8>);`
- L41 _public member_ `FOnInputReceived OnInputReceived;`
- L44 _public prototype_ `void ForceKeyFrame();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L47 _public prototype_ `void FreezeStream(UTexture2D* Texture);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L50 _public prototype_ `void UnfreezeStream();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L53 _public prototype_ `void SendPlayerMessage(uint8 Type, const FString& Descriptor);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")`
- L56 _public member_ `FString StreamerId = "St` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")`
- L59 _public member_ `FString SignallingServerURL = "ws` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")` — 127.0.0.1:8888";
- L62 _public member_ `bool UsePixelStreamingURL = false;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")`
- L65 _public member_ `int32 StreamFPS = 60;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")`
- L68 _public member_ `bool CoupleFramerate = false;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")`
- L71 _public member_ `TObjectPtr<UPixelStreamingStreamerVideoInput> VideoInput = nullptr;` — `UPROPERTY(EditAnywhere, Category = "PixelStreaming")`
- L74 _private member_ `TSharedPtr<IPixelStreamingStreamer> Streamer;`
- L75 _private member_ `bool bEngineStarted = false;`
- L77 _private prototype_ `void OnPostEngineInit();`
- L78 _private prototype_ `void CreateStreamer();`
- L79 _private prototype_ `void SetupStreamerInput();`
- L81 _private prototype_ `void StreamingStarted(IPixelStreamingStreamer*);`
- L82 _private prototype_ `void StreamingStopped(IPixelStreamingStreamer*);`
- L83 _private prototype_ `void StreamingInput(FPixelStreamingPlayerId PlayerId, uint8 Type, TArray<uint8> Data);`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_EVENT(UPixelStreamingStreamerComponent, FStreamingStartedEvent);`
- L37 _delegate_ `DECLARE_EVENT(UPixelStreamingStreamerComponent, FStreamingStoppedEvent);`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInputReceived, FPixelStreamingPlayerId, uint8, TArray<uint8>);`
