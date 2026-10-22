# Plugins / PixelStreaming2Core

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core`
- headers: 9; symbols: 111
- symbol kinds: class=15, delegate=6, enum=1, enumerator=2, function=13, macro=1, member=2, namespace=4, prototype=67
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject, PixelCapture, RHI, WebRTC

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Core, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Core, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Private/Streamer.h` (Private)


#### class `UE::PixelStreaming2::FDummyStreamerFactory`  
`class FDummyStreamerFactory : public IPixelStreaming2StreamerFactory`  
_L7-12_
- inherits: `IPixelStreaming2StreamerFactory`
- L10 _public prototype_ `virtual FString GetStreamType() override;`
- L11 _public prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> CreateNewStreamer(const FString& StreamerId) override;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace PixelStreaming2` (scope `UE`)

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2AudioConsumer.h` (Public)


#### class `UPixelStreaming2AudioConsumer`  
`class UPixelStreaming2AudioConsumer : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2AudioConsumer`  
`class IPixelStreaming2AudioConsumer`  
_L19-48_
- desc: An "Audio Consumer" is an object that is responsible for outputting the audio received from a peer. For example, by passing the audio into a UE submix.
- L31 _public prototype_ `virtual void ConsumeRawPCM(const int16_t* AudioData, int SampleRate, size_t NumChannels, size_t NumFrames) = 0;` — @brief Consume raw audio data. @param AudioData Pointer to the audio data. @param SampleRate Audio sample rate in samples per second. @param NumChannels Number of audio channels. For example 2 for stero audio. @param NumFrames Number of Audio frames in a single channel.
- L36 _public prototype_ `virtual void OnAudioConsumerAdded() = 0;` — @brief Called when a audio consumer is added.
- L39 _public function_ `virtual void OnConsumerAdded()` — `UE_DEPRECATED(5.7, "OnConsumerAdded has been deprecated. Please use OnAudioConsumerAdded instead.")`
- L44 _public prototype_ `virtual void OnAudioConsumerRemoved() = 0;` — @brief Called when a audio consumer is removed.
- L47 _public function_ `virtual void OnConsumerRemoved()` — `UE_DEPRECATED(5.7, "OnConsumerRemoved has been deprecated. Please use OnAudioConsumerRemoved instead.")`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2AudioProducer.h` (Public)


#### class `UPixelStreaming2AudioProducer`  
`class UPixelStreaming2AudioProducer : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2AudioProducer`  
`class IPixelStreaming2AudioProducer`  
_L24-47_
- desc: A "Audio Producer" is an object that you use to push audio frames into the Pixel Streaming system. Example usage: (1) Each new frame you want to push you call `MyAudioProducer->PushFrame(Buffer, NumSamples, NumChannels, SampleRate)` Note: Any audio you push in with `PushAudio` will be mixed with other audio producers before being streamed
- L36 _public function_ `virtual void PushAudio(const float* InBuffer, int32 NumSamples, int32 NumChannels, int32 SampleRate) final` — @brief Pushes audio into the PS2 audio pipeline which will mix with other audio producers before broadcasting. @param InBuffer Pointer to the audio data. @param NumSamples Number of Audio frames in a single channel. @param NumChannels Number of audio channels. For example 2 for stero audio. @param SampleRate Audio sample rate in samples per second.
- L45 _public prototype_ `DECLARE_EVENT_FourParams(IPixelStreaming2AudioProducer, FOnAudioPushed, const float* , int32 , int32 , int32 );` — Event triggered when a frame is pushed to the audio producer. You can use this to hook into the frame stream. Currently, streamers will listen to this event to know when a new frame is available for encoding.
- L46 _public member_ `FOnAudioPushed OnAudioPushed;`

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_EVENT_FourParams(IPixelStreaming2AudioProducer, FOnAudioPushed, const float* , int32 , int32 , int32 );` — Event triggered when a frame is pushed to the audio producer. You can use this to hook into the frame stream. Currently, streamers will listen to this event to know when a new frame is available for encoding.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2AudioSink.h` (Public)


#### class `UPixelStreaming2AudioSink`  
`class UPixelStreaming2AudioSink : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2AudioSink`  
`class IPixelStreaming2AudioSink`  
_L21-43_
- desc: An "Audio Sink" is an object that receives audio from a singular peer. From here, you can add multiple consumers to output the received audio.
- L31 _public function_ `virtual void AddAudioConsumer(IPixelStreaming2AudioConsumer* AudioConsumer)` — `UE_DEPRECATED(5.6, "AddAudioConsumer(IPixelStreaming2AudioConsumer*) has been deprecated. Please use AddAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>&) instead.")` — @brief Add an audio consumer to the sink. @param AudioConsumer The Audio consumer to add to the sink.
- L33 _public prototype_ `virtual void AddAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>& AudioConsumer) = 0;`
- L40 _public function_ `virtual void RemoveAudioConsumer(IPixelStreaming2AudioConsumer* AudioConsumer)` — `UE_DEPRECATED(5.6, "RemoveAudioConsumer(IPixelStreaming2AudioConsumer*) has been deprecated. Please use RemoveAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>&) instead.")` — @brief Remove an audio consumer to remove from the sink. @param AudioConsumer The Audio consumer to remove from the sink.
- L42 _public prototype_ `virtual void RemoveAudioConsumer(const TWeakPtrVariant<IPixelStreaming2AudioConsumer>& AudioConsumer) = 0;`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2Streamer.h` (Public)


#### class `IPixelStreaming2Streamer`  
`class IPixelStreaming2Streamer`  
_L25-293_
- desc: The IPixelStreaming2Streamer interface provides functionality for managing a Pixel Streaming session. This class manages the core operations of streaming, such as setting the framerate, handling video input, and interacting with the signalling server. It also allows for control over connected players and sending data to them.
- L28 _public prototype_ `virtual ~IPixelStreaming2Streamer() = default;`
- L34 _public prototype_ `virtual void Initialize() = 0;` — Called just after streamer creation. Use this method to initialize any methods that need a shared pointer to the streamer by using AsShared() inside the method.
- L40 _public prototype_ `virtual void SetStreamFPS(int32 InFramesPerSecond) = 0;` — @brief Set the Stream FPS. @param InFramesPerSecond The number of frames per second the streamer will stream at.
- L46 _public prototype_ `virtual int32 GetStreamFPS() = 0;` — @brief Get the Stream FPS. @return - The number of frames per second the streamer will stream at.
- L54 _public prototype_ `virtual void SetCoupleFramerate(bool bCouple) = 0;` — Setting this to true will cause the streamer to ignore the FPS value and instead push out frames as they are submitted from the video input. If the encode process takes longer than the time between frames, frames will be dropped. @param bCouple true to couple the streamer framerate to that of the video input.
- L60 _public prototype_ `virtual void SetVideoProducer(TSharedPtr<IPixelStreaming2VideoProducer> Input) = 0;` — @brief Set the Video Input object. @param Input The IPixelStreaming2VideoProducer that this streamer will stream.
- L66 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoProducer> GetVideoProducer() = 0;` — @brief Get the Video Input object. @return The IPixelStreaming2VideoProducer that this streamer will stream.
- L72 _public prototype_ `virtual void AddAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer) = 0;` — @brief Add an audio producer to the streamer. @param AudioProducer An IPixelStreaming2AudioProducer that this streamer will mix with engine audio before streaming.
- L78 _public prototype_ `virtual void RemoveAudioProducer(TSharedPtr<IPixelStreaming2AudioProducer> AudioProducer) = 0;` — @brief Remove an audio producer from the streamer. @param AudioProducer The IPixelStreaming2AudioProducer to remove.
- L84 _public prototype_ `virtual TArray<TWeakPtr<IPixelStreaming2AudioProducer>> GetAudioProducers() = 0;` — @brief Get the audio producers currently added to this streamer. @return An array of weak pointers to the IPixelStreaming2AudioProducers currently added to this streamer.
- L90 _public prototype_ `virtual void SetConnectionURL(const FString& InConnectionURL) = 0;` — @brief Set the URL this streamer will connect to. @param InConnectionURL.
- L97 _public function_ `virtual void SetSignallingServerURL(const FString& InSignallingServerURL)` — `UE_DEPRECATED(5.6, "SetSignallingServerURL has been deprecated. Please use SetConnectionURL instead.")` — @brief Set the Signalling Server URL. @param InSignallingServerURL.
- L103 _public prototype_ `virtual FString GetConnectionURL() = 0;` — @brief Get the URL this streamer will connect to. @return The connection URL.
- L110 _public function_ `virtual FString GetSignallingServerURL()` — `UE_DEPRECATED(5.6, "GetSignallingServerURL has been deprecated. Please use GetConnectionURL instead.")` — @brief Get the Signalling Server URL. @return The Signalling Server URL.
- L116 _public prototype_ `virtual FString GetId() = 0;` — @brief Get this streamer's ID. @return The streamer's ID.
- L122 _public prototype_ `virtual bool IsConnected() = 0;` — @brief Check if this streamer is currently connected to the connection URL. @return True if the streamer is connected.
- L129 _public function_ `virtual bool IsSignallingConnected()` — `UE_DEPRECATED(5.6, "IsSignallingConnected has been deprecated. Please use IsConnected instead.")` — @brief Check if this streamer is currently connected to the signalling mechanism (e.g. websocket for signalling server). @return True if the streamer is connected to the signalling mechanism.
- L134 _public prototype_ `virtual void StartStreaming() = 0;` — @brief Start streaming this streamer
- L139 _public prototype_ `virtual void StopStreaming() = 0;` — @brief Stop this streamer from streaming
- L145 _public prototype_ `virtual bool IsStreaming() const = 0;` — @brief Get the current state of this streamer @return True if streaming, false otherwise.
- L150 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FPreConnectionEvent, IPixelStreaming2Streamer*);` — @brief Event fired just before the streamer begins connecting to signalling.
- L156 _public prototype_ `virtual FPreConnectionEvent& OnPreConnection() = 0;` — @brief A getter for the OnPreConnection event. Intent is for users to call IPixelStreaming2Module::Get().FindStreamer(ID)->OnPreConnection().AddXXX. @return - The bindable OnPreConnection event.
- L161 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FStreamingStartedEvent, IPixelStreaming2Streamer*);` — @brief Event fired when the streamer has connected to a signalling server and is ready for peers.
- L167 _public prototype_ `virtual FStreamingStartedEvent& OnStreamingStarted() = 0;` — @brief A getter for the OnStreamingStarted event. Intent is for users to call IPixelStreaming2Module::Get().FindStreamer(ID)->OnStreamingStarted().AddXXX. @return - The bindable OnStreamingStarted event.
- L172 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FStreamingStoppedEvent, IPixelStreaming2Streamer*);` — @brief Event fired when the streamer has disconnected from a signalling server and has stopped streaming.
- L178 _public prototype_ `virtual FStreamingStoppedEvent& OnStreamingStopped() = 0;` — @brief A getter for the OnStreamingStopped event. Intent is for users to call IPixelStreaming2Module::Get().FindStreamer(ID)->OnStreamingStopped().AddXXX. @return - The bindable OnStreamingStopped event.
- L183 _public prototype_ `virtual void ForceKeyFrame() = 0;` — @brief Force a key frame to be sent.
- L189 _public prototype_ `virtual void FreezeStream(UTexture2D* Texture) = 0;` — @brief Freeze Pixel Streaming. @param Texture 		- The freeze frame to display. If null then the back buffer is captured.
- L194 _public prototype_ `virtual void UnfreezeStream() = 0;` — @brief Unfreeze Pixel Streaming.
- L201 _public prototype_ `virtual void SendAllPlayersMessage(FString MessageType, const FString& Descriptor) = 0;` — @brief Send all players connected to this streamer a message. @param MessageType The message type to be sent to the player. @param Descriptor The contents of the message.
- L208 _public prototype_ `virtual void SendPlayerMessage(FString PlayerId, FString MessageType, const FString& Descriptor) = 0;` — @brief Send all players connected to this streamer a message. @param MessageType The message type to be sent to the player. @param Descriptor The contents of the message.
- L216 _public prototype_ `virtual void SendFileData(const TArray64<uint8>& ByteData, FString& MimeType, FString& FileExtension) = 0;` — @brief Send a file to the browser where we are sending video. @param ByteData	 	- The raw byte data of the file. @param MimeType	 	- The files Mime type. Used for reconstruction on the front end. @param FileExtension - The files extension. Used for reconstruction on the front end.
- L222 _public prototype_ `virtual void KickPlayer(FString PlayerId) = 0;` — @brief Kick a player by player id. @param PlayerId		- The ID of the player to kick
- L228 _public prototype_ `virtual TArray<FString> GetConnectedPlayers() = 0;` — @brief Get the ids of the connected players. @return TArray<FString> The ids of the connected players.
- L234 _public prototype_ `virtual TWeakPtr<class IPixelStreaming2InputHandler> GetInputHandler() = 0;` — @brief Get the streamer's input handler @return The streamer's input handler
- L240 _public prototype_ `virtual void SetInputHandler(TSharedPtr<class IPixelStreaming2InputHandler> Handler) = 0;` — @brief Set the streamer's input handler @param Handler The streamer's input handler
- L247 _public prototype_ `virtual TWeakPtr<IPixelStreaming2AudioSink> GetPeerAudioSink(FString PlayerId) = 0;` — @brief Get the audio sink associated with a specific peer/player. @param PlayerId The player id of the audio sink to retrieve. @return The PeerAudioSink.
- L253 _public prototype_ `virtual TWeakPtr<IPixelStreaming2AudioSink> GetUnlistenedAudioSink() = 0;` — @brief Get an audio sink that has no peers/players listening to it. @return The unlistened PeerAudioSink.
- L259 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoSink> GetPeerVideoSink(FString PlayerId) = 0;` — @brief Get the video sink associated with a specific peer/player. @return The PeerVideoSink.
- L265 _public prototype_ `virtual TWeakPtr<IPixelStreaming2VideoSink> GetUnwatchedVideoSink() = 0;` — @brief Get a video sink that has no peers/players watching it. @return The unwatched PeerVideoSink.
- L272 _public prototype_ `virtual void SetConfigOption(const FName& OptionName, const FString& Value) = 0;` — @brief Allows sending arbitrary configuration options during initial connection. @param OptionName The name of the option to set. @param Value Setting a value to an empty string clears it from the mapping and prevents it being sent.
- L279 _public prototype_ `virtual bool GetConfigOption(const FName& OptionName, FString& OutValue) = 0;` — @brief Get the configuration value for a specific option. @param OptionName The name of the config option to get. @param Value The value of the config option retrieved.
- L287 _public prototype_ `virtual void PlayerRequestsBitrate(FString PlayerId, int MinBitrate, int MaxBitrate) = 0;` — @brief Set the minimum and maximum bitrate for the streamer. @param PlayerId Currently unused. For setting the bitrate for a individual player id. @param MinBitrate minimum bitrate for the streamer. @param MaxBitrate maximum bitrate for the streamer.
- L292 _public prototype_ `virtual void RefreshStreamBitrate() = 0;` — @brief Refresh connection with minimum and maximum bitrate.

#### class `IPixelStreaming2StreamerFactory`  
`class IPixelStreaming2StreamerFactory : public IModularFeature`  
_L299-319_
- inherits: `IModularFeature`
- desc: The IPixelStreaming2StreamerFactory interface provides functionality for creating custom streamers based on an identifier.
- L302 _public prototype_ `IPixelStreaming2StreamerFactory();`
- L303 _public prototype_ `virtual ~IPixelStreaming2StreamerFactory();`
- L305 _public prototype_ `virtual FString GetStreamType() = 0;`
- L307 _public prototype_ `static void RegisterStreamerFactory(IPixelStreaming2StreamerFactory* InFactory);`
- L309 _public prototype_ `static void UnregisterStreamerFactory(IPixelStreaming2StreamerFactory* InFactory);`
- L311 _public prototype_ `static IPixelStreaming2StreamerFactory* Get(const FString& InType);`
- L313 _public prototype_ `static TArray<FString> GetAvailableFactoryTypes();`
- L318 _private prototype_ `virtual TSharedPtr<IPixelStreaming2Streamer> CreateNewStreamer(const FString& StreamerId) = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIXELSTREAMING2CORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L150 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FPreConnectionEvent, IPixelStreaming2Streamer*);` — @brief Event fired just before the streamer begins connecting to signalling.
- L161 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FStreamingStartedEvent, IPixelStreaming2Streamer*);` — @brief Event fired when the streamer has connected to a signalling server and is ready for peers.
- L172 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2Streamer, FStreamingStoppedEvent, IPixelStreaming2Streamer*);` — @brief Event fired when the streamer has disconnected from a signalling server and has stopped streaming.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2VideoConsumer.h` (Public)


#### class `UPixelStreaming2VideoConsumer`  
`class UPixelStreaming2VideoConsumer : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2VideoConsumer`  
`class IPixelStreaming2VideoConsumer`  
_L20-46_
- desc: An "Video Consumer" is an object that is responsible for outputting the video received from a peer. For example, by rendering to a render target.
- L29 _public prototype_ `virtual void ConsumeFrame(FTextureRHIRef Frame) = 0;` — @brief Consume a texture as a video frame. @param Frame The Frame to consume.
- L34 _public prototype_ `virtual void OnVideoConsumerAdded() = 0;` — @brief Called when a video consumer is added.
- L37 _public function_ `virtual void OnConsumerAdded()` — `UE_DEPRECATED(5.7, "OnConsumerAdded has been deprecated. Please use OnVideoConsumerAdded instead.")`
- L42 _public prototype_ `virtual void OnVideoConsumerRemoved() = 0;` — @brief Called when a video consumer is removed.
- L45 _public function_ `virtual void OnConsumerRemoved()` — `UE_DEPRECATED(5.7, "OnConsumerRemoved has been deprecated. Please use OnVideoConsumerRemoved instead.")`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2VideoProducer.h` (Public)


#### class `UPixelStreaming2VideoProducer`  
`class UPixelStreaming2VideoProducer : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### enum `EVideoProducerCapabilities`  
`enum class EVideoProducerCapabilities : uint8`  
_L16-20_
- L18 _public enumerator_ `Default = 0`
- L19 _public enumerator_ `ProducesPreprocessedFrames = 1 << 0` — Frames pushed into this producer are preprocessed (e.g. resized, format converted) and ready for encoding.

#### class `IPixelStreaming2VideoProducer`  
`class IPixelStreaming2VideoProducer`  
_L33-65_
- desc: A "Video Producer" is an object that you use to push video frames into the Pixel Streaming system. Example usage: (1) Each new frame you want to push you call `MyVideoProducer->PushFrame(MyFrame)` Note: Your frame is likely a `FPixelCaptureInputFrameRHI` if the frame is a GPU texture or a `FPixelCaptureInputFrameI420` or `FPixelCaptureInputFrameNV12` if your frame is from the CPU.
- L42 _public function_ `virtual void PushFrame(const IPixelCaptureInputFrame& InputFrame) final` — Pushes a raw video frame into the Pixel Streaming system. @param InputFrame The raw input frame, which may be a GPU texture or a CPU texture based on the underlying type of frame pushed.
- L51 _public prototype_ `DECLARE_EVENT_OneParam(IPixelStreaming2VideoProducer, FOnFramePushed, const IPixelCaptureInputFrame&);` — Event triggered when a frame is pushed to the video producer. You can use this to hook into the frame stream. Currently, streamers will listen to this event to know when a new frame is available for encoding.
- L52 _public member_ `FOnFramePushed OnFramePushed;`
- L58 _public prototype_ `virtual EVideoProducerCapabilities GetCapabilities() = 0;` — Returns the capabilities of the video producer. @return The capabilities of the video producer.
- L64 _public prototype_ `virtual FString ToString() = 0;` — A human readable identifier used when displaying what the streamer is streaming in the toolbar @return A string containing the display name.

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_CLASS_FLAGS(EVideoProducerCapabilities);`
- L51 _delegate_ `DECLARE_EVENT_OneParam(IPixelStreaming2VideoProducer, FOnFramePushed, const IPixelCaptureInputFrame&);` — Event triggered when a frame is pushed to the video producer. You can use this to hook into the frame stream. Currently, streamers will listen to this event to know when a new frame is available for encoding.

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Core/Public/IPixelStreaming2VideoSink.h` (Public)


#### class `UPixelStreaming2VideoSink`  
`class UPixelStreaming2VideoSink : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPixelStreaming2VideoSink`  
`class IPixelStreaming2VideoSink`  
_L22-52_
- desc: Interface for a sink that collects video coming in from the browser and passes into into UE.
- L32 _public function_ `virtual void AddVideoConsumer(IPixelStreaming2VideoConsumer* VideoConsumer)` — `UE_DEPRECATED(5.6, "AddVideoConsumer(IPixelStreaming2VideoConsumer*) has been deprecated. Please use AddVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>&) instead.")` — @brief Add a video consumer to the sink. @param VideoConsumer The video consumer to add to the sink.
- L38 _public prototype_ `virtual void AddVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>& VideoConsumer) = 0;` — @brief Add a video consumer to the sink. @param VideoConsumer The video consumer to add to the sink.
- L45 _public function_ `virtual void RemoveVideoConsumer(IPixelStreaming2VideoConsumer* VideoConsumer)` — `UE_DEPRECATED(5.6, "RemoveVideoConsumer(IPixelStreaming2VideoConsumer*) has been deprecated. Please use RemoveVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>&) instead.")` — @brief Remove a video consumer to remove from the sink. @param VideoConsumer The video consumer to remove from the sink.
- L51 _public prototype_ `virtual void RemoveVideoConsumer(const TWeakPtrVariant<IPixelStreaming2VideoConsumer>& VideoConsumer) = 0;` — @brief Remove a video consumer to remove from the sink. @param VideoConsumer The video consumer to remove from the sink.
