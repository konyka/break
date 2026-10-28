# Plugins / PixelStreamingPlayer

- module root: `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer`
- headers: 8; symbols: 104
- symbol kinds: class=6, delegate=2, function=7, member=31, prototype=55, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MediaAssets, PixelStreaming, RHI, RenderCore, WebSockets
- PublicDependencyModuleNames: WebRTC

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Private/AsyncActionGetStreamers.h` (Private)


#### class `UAsyncAction_GetStreamers`  
`class UAsyncAction_GetStreamers : public UBlueprintAsyncActionBase`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase`
- L16 _public prototype_ `virtual void Activate() override;`
- L19 _public prototype_ `static UAsyncAction_GetStreamers* GetStreamerIdList(UPixelStreamingSignallingComponent* SignallingComponent);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "PixelStreaming"))`
- L22 _public member_ `FOnStreamerListCompleted Completed;` — `UPROPERTY(BlueprintAssignable)`
- L24 _public member_ `UPixelStreamingSignallingComponent* SignallingConnectionComponent;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStreamerListCompleted, const TArray<FString>&, StreamerList);`
- L8 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStreamerListCompleted, const TArray<FString>&, StreamerList);`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Private/PixelStreamingMediaTextureResource.h` (Private)


#### class `FPixelStreamingMediaTextureResource`  
`class FPixelStreamingMediaTextureResource : public FTextureResource`  
_L12-27_
- inherits: `FTextureResource`
- desc: The actual texture resource for a FPixelStreamingMediaTexture. Contains the RHI Texture and Sampler information.
- L15 _public prototype_ `FPixelStreamingMediaTextureResource(UPixelStreamingMediaTexture* Owner);`
- L16 _public function_ `virtual ~FPixelStreamingMediaTextureResource() override`
- L18 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L19 _public prototype_ `virtual void ReleaseRHI() override;`
- L20 _public prototype_ `virtual uint32 GetSizeX() const override;`
- L21 _public prototype_ `virtual uint32 GetSizeY() const override;`
- L23 _public prototype_ `SIZE_T GetResourceSize();`
- L26 _private member_ `UPixelStreamingMediaTexture* MediaTexture = nullptr;`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Private/PixelStreamingPlayerPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingPlayer, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreamingPlayer, Log, All);`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Private/WebRTCIncludes.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Public/PixelStreamingMediaTexture.h` (Public)


#### class `UPixelStreamingMediaTexture`  
`class UPixelStreamingMediaTexture : public UTexture2DDynamic, public FPixelStreamingVideoSink`  
_L16-44_
- reflection: `UCLASS(NotBlueprintType, NotBlueprintable, HideDropdown, HideCategories = (ImportSettings, Compression, Texture, Adjustments, Compositing, LevelOfDetail, Object), META = (DisplayName = "PixelStreaming Media Texture"))`
- inherits: `UTexture2DDynamic,FPixelStreamingVideoSink`
- desc: A Texture Object that can be used in materials etc. that takes updates from webrtc frames.
- L22 _protected prototype_ `virtual void BeginDestroy() override;` — UObject overrides.
- L23 _protected prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L26 _protected prototype_ `virtual FTextureResource* CreateResource() override;` — UTexture implementation
- L29 _protected prototype_ `virtual void OnFrame(FTextureRHIRef Frame) override;` — FPixelStreamingVideoSink implementation
- L32 _private prototype_ `void InitializeResources();`
- L35 _private prototype_ `void UpdateTextureReference(FRHICommandList& RHICmdList, FTextureRHIRef Reference);` — updates the internal texture resource after each frame.
- L37 _private member_ `TArray<uint8_t> Buffer;`
- L39 _private member_ `FCriticalSection RenderSyncContext;`
- L40 _private member_ `FTextureRHIRef SourceTexture;`
- L41 _private member_ `FPooledRenderTargetDesc RenderTargetDescriptor;`
- L42 _private member_ `TRefCountPtr<IPooledRenderTarget> RenderTarget;`
- L43 _private member_ `FPixelStreamingMediaTextureResource* CurrentResource;`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Public/PixelStreamingPeerComponent.h` (Public)


#### class `UPixelStreamingPeerComponent`  
`class UPixelStreamingPeerComponent : public UActorComponent`  
_L20-89_
- reflection: `UCLASS(BlueprintType, Blueprintable, Category = "PixelStreaming", META = (DisplayName = "PixelStreaming Peer Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: A blueprint representation of a Pixel Streaming Peer Connection. Should communicate with a Pixel Streaming Signalling Connection and will accept video sinks to receive video data.
- L30 _public prototype_ `void SetConfig(const FPixelStreamingRTCConfigWrapper& Config);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Sets the RTC Configuration for this Peer Connection. @param Config The RTC configuration for this Peer Connection. Obtained from the signalling server On Config event.
- L37 _public prototype_ `FPixelStreamingSessionDescriptionWrapper CreateOffer();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Creates an offer. @return The offer object generated. Send this to the signalling server to initiate negotiation.
- L45 _public prototype_ `FPixelStreamingSessionDescriptionWrapper CreateAnswer(const FString& Offer);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Creates an answer to the given offer objet that was provided. @param Offer The offer SDP string to create an answer for. Should be obtained from the signalling server On Offer event. @return The answer object generated. Send this to the signalling server to complete negotiation.
- L52 _public prototype_ `void ReceiveAnswer(const FString& Offer);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Receives an answer from a streamer after we've sent an offer to receive. @param Offer The answer SDP. Should be obtained from the signalling server On Answer event.
- L59 _public prototype_ `void ReceiveIceCandidate(const FPixelStreamingIceCandidateWrapper& Candidate);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Notify the peer connection of an ICE candidate sent by the singalling connection. @param Candidate Provided by the singalling connection.
- L65 _public member_ `FPixelStreamingOnIceCandidate OnIceCandidate;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Once negotiation is completed the Peer Connection can generate Ice Candidate objects. These need to be sent to a signalling server to allow proper connection.
- L71 _public member_ `FPixelStreamingOnIceConnection OnIceConnection;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Once a connection has been connected and streaming should be available.
- L77 _public member_ `FPixelStreamingOnIceDisconnection OnIceDisconnection;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — When an ice connection is lost.
- L83 _public member_ `TObjectPtr<UPixelStreamingMediaTexture> VideoSink = nullptr;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", META = (DisplayName = "Pixel Streaming Video Sink", AllowPrivateAccess = true))` — A sink for the video data received once this connection has finished negotiating.
- L86 _private member_ `TUniquePtr<FPixelStreamingPeerConnection> PeerConnection;`
- L88 _private prototype_ `void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState);`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingOnIceCandidate, UPixelStreamingPeerComponent, OnIceCandidate, FPixelStreamingIceCandidateWrapper, Candidate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingOnIceConnection, UPixelStreamingPeerComponent, OnIceConnection, int, Number);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPixelStreamingOnIceDisconnection, UPixelStreamingPeerComponent, OnIceDisconnection);`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Public/PixelStreamingSignallingComponent.h` (Public)


#### class `UPixelStreamingSignallingComponent`  
`class UPixelStreamingSignallingComponent : public UActorComponent`  
_L26-164_
- reflection: `UCLASS(BlueprintType, Blueprintable, Category = "PixelStreaming", META = (DisplayName = "PixelStreaming Signalling Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: A blueprint class representing a Pixel Streaming Signalling connection. Used to communicate with the signalling server and should route information to the peer connection.
- L36 _public prototype_ `void Connect(const FString& Url);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Attempt to connect to a specified signalling server. @param Url The url of the signalling server. Ignored if this component has a MediaSource. In that case the URL on the media source will be used instead.
- L42 _public prototype_ `void Disconnect();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Disconnect from the signalling server. No action if no connection exists.
- L49 _public prototype_ `void Subscribe(const FString& StreamerId);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Send a subscribe message to the signalling server to subscribe to a specific streamer. @param StreamerId The name of the streamer to subscribe to.
- L55 _public prototype_ `void Unsubscribe();` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Send an unsubscribe message to the signalling server to unsubscribe from a streamer.
- L62 _public prototype_ `void SendOffer(const FPixelStreamingSessionDescriptionWrapper& Offer);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Send an offer created from a Peer Connection to the signalling server. @param Offer The answer object created from calling CreateAnswer on a Peer Connection.
- L69 _public prototype_ `void SendAnswer(const FPixelStreamingSessionDescriptionWrapper& Answer);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Send an answer created from a Peer Connection to the signalling server. @param Answer The answer object created from calling CreateAnswer on a Peer Connection.
- L76 _public prototype_ `void SendIceCandidate(const FPixelStreamingIceCandidateWrapper& CandidateWrapper);` — `UFUNCTION(BlueprintCallable, Category = "PixelStreaming")` — Send an Ice Candidate to the signalling server that is generated from a Peer Connection. @param Candidate The Ice Candidate object generated from a Peer Connection.
- L82 _public member_ `FPixelStreamingSignallingComponentConnected OnConnected;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the signalling connection is successfully established.
- L88 _public member_ `FPixelStreamingSignallingComponentConnectionError OnConnectionError;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired if the connection failed or an error occurs during the connection. If this is fired at any point the connection should be considered closed.
- L94 _public member_ `FPixelStreamingSignallingComponentDisconnected OnDisconnected;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the connection successfully closes.
- L100 _public member_ `FPixelStreamingSignallingComponentConfig OnConfig;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the connection receives a config message from the server. This is the earliest place where the peer connection can be initialized.
- L106 _public member_ `FPixelStreamingSignallingComponentOffer OnOffer;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the connection receives an offer from the server. This means there is media being offered up to this connection. Forward to the peer connection.
- L112 _public member_ `FPixelStreamingSignallingComponentAnswer OnAnswer;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the connection receives an answer from the server. The streamer is answering a previously sent offer by us. Forward to the peer connection.
- L118 _public member_ `FPixelStreamingSignallingComponentIceCandidate OnIceCandidate;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Activation")` — Fired when the server sends through an ice candidate. Forward this information on to the peer connection.
- L124 _public member_ `TObjectPtr<UStreamMediaSource> MediaSource;` — `UPROPERTY(EditDefaultsOnly, Category = "Properties", META = (DisplayName = "Stream Media Source", AllowPrivateAccess = true))` — If this media source is set we will use its supplied URL instead of the Url parameter on the connect call.
- L127 _public prototype_ `void AsyncRequestStreamerList(const TFunction<void(const TArray<FString>&)>& Callback);` — Used by the async bp node
- L159 _protected member_ `TFunction<void(const TArray<FString>&)> OnStreamerListCallback;`
- L162 _private member_ `TUniquePtr<IPixelStreamingSignallingConnection> SignallingConnection;`
- L163 _private member_ `TSharedPtr<IPixelStreamingSignallingConnectionObserver> SignallingServerConnectionObserver;`

#### class `UPixelStreamingSignallingComponent::FSignallingObserver`  
`class FSignallingObserver : public IPixelStreamingSignallingConnectionObserver`  
_L130-157_
- inherits: `IPixelStreamingSignallingConnectionObserver`
- L133 _public function_ `FSignallingObserver(UPixelStreamingSignallingComponent* InParent) : Parent(InParent)`
- L139 _public prototype_ `virtual void OnSignallingConnected() override;` — ISignallingServerConnectionObserver implementation.
- L140 _public prototype_ `virtual void OnSignallingDisconnected(int32 StatusCode, const FString& Reason, bool bWasClean) override;`
- L141 _public prototype_ `virtual void OnSignallingError(const FString& ErrorMsg) override;`
- L142 _public prototype_ `virtual void OnSignallingConfig(const webrtc::PeerConnectionInterface::RTCConfiguration& Config) override;`
- L143 _public prototype_ `virtual void OnSignallingSessionDescription(webrtc::SdpType Type, const FString& Sdp) override;`
- L144 _public prototype_ `virtual void OnSignallingRemoteIceCandidate(const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) override;`
- L145 _public prototype_ `virtual void OnSignallingPeerDataChannels(int32 SendStreamId, int32 RecvStreamId) override;`
- L146 _public prototype_ `virtual void OnSignallingPlayerCount(uint32 Count) override;`
- L147 _public prototype_ `virtual void OnSignallingPlayerConnected(FPixelStreamingPlayerId PlayerId, const FPixelStreamingPlayerConfig& PlayerConfig, bool bSendOffer) override;`
- L148 _public prototype_ `virtual void OnSignallingPlayerDisconnected(FPixelStreamingPlayerId PlayerId) override;`
- L149 _public prototype_ `virtual void OnSignallingSFUPeerDataChannels(FPixelStreamingPlayerId SFUId, FPixelStreamingPlayerId PlayerId, int32 SendStreamId, int32 RecvStreamId) override;`
- L150 _public function_ `virtual void OnSignallingSessionDescription(FPixelStreamingPlayerId PlayerId, webrtc::SdpType Type, const FString& Sdp) override`
- L151 _public function_ `virtual void OnSignallingRemoteIceCandidate(FPixelStreamingPlayerId PlayerId, const FString& SdpMid, int SdpMLineIndex, const FString& Sdp) override`
- L152 _public prototype_ `virtual void OnSignallingStreamerList(const TArray<FString>& StreamerList) override;`
- L153 _public prototype_ `virtual void OnPlayerRequestsBitrate(FPixelStreamingPlayerId PlayerId, int MinBitrate, int MaxBitrate) override;`
- L156 _private member_ `TObjectPtr<UPixelStreamingSignallingComponent> Parent;`

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPixelStreamingSignallingComponentConnected, UPixelStreamingSignallingComponent, OnConnected);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingSignallingComponentConnectionError, UPixelStreamingSignallingComponent, OnConnectionError, const FString&, ErrorMsg);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_ThreeParams(FPixelStreamingSignallingComponentDisconnected, UPixelStreamingSignallingComponent, OnDisconnected, int32, StatusCode, const FString&, Reason, bool, bWasClean);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingSignallingComponentConfig, UPixelStreamingSignallingComponent, OnConfig, FPixelStreamingRTCConfigWrapper, Config);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingSignallingComponentOffer, UPixelStreamingSignallingComponent, OnOffer, const FString&, Offer);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingSignallingComponentAnswer, UPixelStreamingSignallingComponent, OnAnswer, const FString&, Answer);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FPixelStreamingSignallingComponentIceCandidate, UPixelStreamingSignallingComponent, OnIceCandidate, FPixelStreamingIceCandidateWrapper, Candidate);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FPixelStreamingSignallingComponentDataChannels, UPixelStreamingSignallingComponent, OnDataChannels, int32, SendStreamId, int32, RecvStreamId);`

### `Plugins/Experimental/PixelStreamingPlayer/Source/PixelStreamingPlayer/Public/PixelStreamingWebRTCWrappers.h` (Public)


#### struct `FPixelStreamingRTCConfigWrapper`  
`struct FPixelStreamingRTCConfigWrapper`  
_L12-16_
- reflection: `USTRUCT(BlueprintType, Category = "PixelStreaming")`
- desc: A blueprint wrapper for an RTCConfiguration from webrtc so it can be passed around in blueprints.
- L15 _public member_ `webrtc::PeerConnectionInterface::RTCConfiguration Config;`

#### struct `FPixelStreamingSessionDescriptionWrapper`  
`struct FPixelStreamingSessionDescriptionWrapper`  
_L22-26_
- reflection: `USTRUCT(BlueprintType, Category = "PixelStreaming")`
- desc: A blueprint wrapper for an SessionDescriptionInterface from webrtc so it can be passed around in blueprints.
- L25 _public member_ `const webrtc::SessionDescriptionInterface* SDP = nullptr;`

#### struct `FPixelStreamingIceCandidateWrapper`  
`struct FPixelStreamingIceCandidateWrapper`  
_L32-65_
- reflection: `USTRUCT(BlueprintType, Category = "PixelStreaming")`
- desc: A blueprint wrapper for an IceCandidateInterface from webrtc so it can be passed around in blueprints.
- L36 _public prototype_ `FPixelStreamingIceCandidateWrapper() = default;`
- L38 _public function_ `explicit FPixelStreamingIceCandidateWrapper(const webrtc::IceCandidateInterface& Candidate)`
- L47 _public function_ `FPixelStreamingIceCandidateWrapper(const FString& SdpMid, int SdpMLineIndex, const FString& Sdp)`
- L54 _public function_ `TUniquePtr<webrtc::IceCandidateInterface> ToWebRTC() const`
- L62 _public member_ `FString Mid;`
- L63 _public member_ `int MLineIndex = -1;`
- L64 _public member_ `FString SDP;`
