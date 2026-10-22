# Plugins / MediaStream

- module root: `Plugins/Experimental/MediaStream/Source/MediaStream`
- headers: 26; symbols: 383
- symbol kinds: class=24, delegate=4, enum=3, enumerator=8, function=15, member=62, namespace=3, prototype=257, struct=7
- PrivateDependencyModuleNames: CoreUObject, DesktopWidgets, LevelSequence, MediaCompositing, MediaUtils, MovieScene, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, Engine, MediaAssets

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/MediaStreamUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MediaStream` (scope `UE`)
- L10 _namespace_ `namespace Utils` (scope `UE::MediaStream`)
- L13 _prototype_ `FMediaPlayerOptions MakePlayerOptions(const UMediaStream* InMediaStream);` (scope `UE::MediaStream::Utils`) — Build player options from the stream's config; injects a ViewMediaTexture entry pointing at the stream's media texture when available.
- L20 _prototype_ `void BindMediaTextureToPlayer(const UMediaStream* InMediaStream, UMediaPlayer* InMediaPlayer);` (scope `UE::MediaStream::Utils`) — Assign the media player to the current media stream's media texture. @param InMediaStream Media stream to get the media texture from. @param InMediaPlayer Media player to bind to the media texture.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/ObjectHandlers/MediaStreamMediaPlaylistHandler.h` (Private)


#### class `FMediaStreamMediaPlaylistHandler`  
`class FMediaStreamMediaPlaylistHandler : public IMediaStreamObjectHandler`  
_L7-15_
- inherits: `IMediaStreamObjectHandler`
- L10 _public prototype_ `static UClass* GetClass();`
- L13 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) override;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/ObjectHandlers/MediaStreamMediaSourceHandler.h` (Private)


#### class `FMediaStreamMediaSourceHandler`  
`class FMediaStreamMediaSourceHandler : public IMediaStreamObjectHandler`  
_L7-15_
- inherits: `IMediaStreamObjectHandler`
- L10 _public prototype_ `static UClass* GetClass();`
- L13 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) override;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/ObjectHandlers/MediaStreamMediaStreamHandler.h` (Private)


#### class `FMediaStreamMediaStreamHandler`  
`class FMediaStreamMediaStreamHandler : public IMediaStreamObjectHandler`  
_L7-15_
- inherits: `IMediaStreamObjectHandler`
- L10 _public prototype_ `static UClass* GetClass();`
- L13 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) override;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/Players/MediaStreamLocalPlayer.h` (Private)


#### class `UMediaStreamLocalPlayer`  
`class UMediaStreamLocalPlayer : public UObject, public IMediaStreamPlayer`  
_L19-203_
- reflection: `UCLASS(BlueprintType, Blueprintable, ClassGroup = "Media Stream", DefaultToInstanced)`
- inherits: `UObject,IMediaStreamPlayer`
- desc: Media Stream Local Player. Plays a media source using a UMediaPlayer.
- L24 _public prototype_ `UMediaStreamLocalPlayer() = default;`
- L28 _public function_ `void BP_SetRequestedSeekTime(float InSeekTime)` — `UFUNCTION(BlueprintCallable, DisplayName = "Set Requested Seek Time", Category = "Media Stream|Player")`
- L34 _public function_ `void BP_SetRequestedSeekFrame(int32 InSeekFrame)` — `UFUNCTION(BlueprintCallable, DisplayName = "Set Requested Seek Frame", Category = "Media Stream|Player")`
- L40 _public function_ `void BP_SetPlaybackState(EMediaStreamPlaybackState InState)` — `UFUNCTION(BlueprintCallable, DisplayName = "Set Playback State", Category = "Media Stream|Player")`
- L46 _public function_ `void BP_SetPlaylistIndex(int32 InIndex)` — `UFUNCTION(BlueprintCallable, DisplayName = "Set Playlist Index", Category = "Media Stream|Player")`
- L52 _public prototype_ `virtual UMediaStream* GetMediaStream() const override;`
- L53 _public prototype_ `virtual bool IsReadOnly() const override;`
- L54 _public prototype_ `virtual void OnCreated() override;`
- L55 _public prototype_ `virtual void OnSourceChanged(const FMediaStreamSource& InSource) override;`
- L56 _public prototype_ `virtual UMediaTexture* GetMediaTexture() const override;`
- L57 _public prototype_ `virtual const FMediaStreamTextureConfig& GetTextureConfig() const override;`
- L58 _public prototype_ `virtual void SetTextureConfig(const FMediaStreamTextureConfig& InTextureConfig) override;`
- L59 _public prototype_ `virtual void ApplyTextureConfig() override;`
- L60 _public prototype_ `virtual UMediaPlayer* GetPlayer() const override;`
- L61 _public prototype_ `virtual bool HasValidPlayer() const override;`
- L62 _public prototype_ `virtual const FMediaStreamPlayerConfig& GetPlayerConfig() const override;`
- L63 _public prototype_ `virtual void SetPlayerConfig(const FMediaStreamPlayerConfig& InPlayerConfig) override;`
- L64 _public prototype_ `virtual void ApplyPlayerConfig() override;`
- L65 _public prototype_ `virtual bool SetPlaylistIndex(int32 InIndex) override;`
- L66 _public prototype_ `virtual float GetRequestedSeekTime() const override;`
- L67 _public prototype_ `virtual bool SetRequestedSeekTime(float InTime) override;`
- L68 _public prototype_ `virtual int32 GetRequestedSeekFrame() const override;`
- L69 _public prototype_ `virtual bool SetRequestedSeekFrame(int32 InFrame) override;`
- L70 _public prototype_ `virtual EMediaStreamPlaybackState GetPlaybackState() const override;`
- L71 _public prototype_ `virtual bool SetPlaybackState(EMediaStreamPlaybackState InState) override;`
- L72 _public prototype_ `virtual int32 GetPlaylistIndex() const override;`
- L73 _public prototype_ `virtual int32 GetPlaylistNum() const override;`
- L74 _public prototype_ `virtual UMediaStream* GetSourceStream() const override;`
- L75 _public prototype_ `virtual bool OpenSource() override;`
- L76 _public prototype_ `virtual bool Play() override;`
- L77 _public prototype_ `virtual bool Pause() override;`
- L78 _public prototype_ `virtual bool Rewind() override;`
- L79 _public prototype_ `virtual bool FastForward() override;`
- L80 _public prototype_ `virtual bool Previous() override;`
- L81 _public prototype_ `virtual bool Next() override;`
- L82 _public prototype_ `virtual bool Close() override;`
- L83 _public prototype_ `virtual void Deinitialize() override;`
- L88 _public prototype_ `virtual void PreEditUndo() override;`
- L89 _public prototype_ `virtual void PostEditUndo() override;`
- L90 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L93 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L94 _public prototype_ `virtual void PostEditImport() override;`
- L95 _public prototype_ `virtual void PostLoad() override;`
- L96 _public prototype_ `virtual void PostNetReceive() override;`
- L97 _public prototype_ `virtual void BeginDestroy() override;`
- L102 _protected member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Media Stream|Texture", meta = (AllowPrivateAccess = true))`
- L105 _protected member_ `FMediaStreamTextureConfig TextureConfig;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Stream|Texture", meta = (AllowPrivateAccess = true))`
- L109 _protected member_ `TObjectPtr<UMediaPlayer> Player = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Media Stream|Player", Transient, DuplicateTransient, TextExportTransient, meta = (AllowPrivateAccess = true))`
- L112 _protected member_ `FMediaStreamPlayerConfig PlayerConfig;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Stream|Player", meta = (AllowPrivateAccess = true))`
- L117 _protected member_ `int32 RequestedSeekFrame = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = BP_SetRequestedSeekFrame, Getter, BlueprintSetter = BP_SetRequestedSeekFrame, Category = "Media Stream|Player", Interp, meta = (AllowPrivateAccess = true))` — Attempts to seek to this frame. Any value below 0 is ignored.
- L121 _protected member_ `EMediaStreamPlaybackState PlaybackState = EMediaStreamPlaybackState::Pause;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = BP_SetPlaybackState, Getter, BlueprintSetter = BP_SetPlaybackState, Category = "Media Stream|Player", Interp, meta = (AllowPrivateAccess = true))`
- L126 _protected member_ `int32 PlaylistIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = BP_SetPlaylistIndex, Getter, BlueprintSetter = BP_SetPlaylistIndex, Category = "Media Stream|Player", Interp, meta = (AllowPrivateAccess = true))` — The index playing in the playlist. -1 to ignore.
- L128 _protected member_ `FMediaStreamTextureConfig TextureConfig_PreUndo;`
- L129 _protected member_ `FMediaStreamPlayerConfig PlayerConfig_PreUndo;`
- L131 _protected member_ `bool bPlayerNeedsUpdate = false;`
- L136 _protected member_ `bool bAllowOpenSource = true;` — Determines whether local players can create or update media players when opening a source.
- L142 _protected member_ `bool bIsPIE = false;` — Whether this object was duplicated into a PIE level.
- L150 _protected member_ `TSharedPtr<FMediaStreamLocalPlayerClockSink> ClockSink;` — Holds our clock sink if available.
- L155 _protected prototype_ `void Initialize();` — Initializes all of the components of the Media Stream.
- L160 _protected prototype_ `void InitTexture();` — Initializes the Media Texture
- L165 _protected prototype_ `void DeinitTexture();` — Deinitializes the Media Texture
- L170 _protected prototype_ `void InitPlayer();` — Initializes the Media Player.
- L175 _protected prototype_ `void DeinitPlayer();` — Deinitializes the Media Player and clears the object.
- L181 _protected prototype_ `bool ApplyRequestedSeekFrame();` — Attempts to set the seek time on the currently active Media Player. @return True if successful.
- L188 _protected prototype_ `bool ApplyPlaybackState();` — Will either set the current Rate from the player config or 0 for paused. The player will be checked for valid rate values. The nearest possible rate will be chosen. @return True if successful.
- L194 _protected prototype_ `bool ApplyPlaylistIndex();` — Attempts to set the playlist index on the Media Player. @return True if successful.
- L200 _protected prototype_ `void OnMediaOpened(FString InOpenedUrl);` — `UFUNCTION()` — Called when the player's media has opened.
- L202 _protected prototype_ `void UpdateSequencesWithCurrentPlayer();`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/Players/MediaStreamProxyPlayer.h` (Private)


#### class `UMediaStreamProxyPlayer`  
`class UMediaStreamProxyPlayer : public UObject, public IMediaStreamPlayer`  
_L14-80_
- reflection: `UCLASS(BlueprintType, Blueprintable, ClassGroup = "Media Stream", DefaultToInstanced)`
- inherits: `UObject,IMediaStreamPlayer`
- desc: Media Stream Proxy Player. Forwards the player and texture from another Media Stream.
- L22 _public prototype_ `TSoftObjectPtr<UMediaStream> GetProxyStreamSoft() const;` — `UFUNCTION(Category = "Media Stream|Player")`
- L25 _public prototype_ `void SetReadOnly(bool bInReadOnly);` — `UFUNCTION(Category = "Media Stream|Texture")`
- L28 _public prototype_ `virtual UMediaStream* GetMediaStream() const override;`
- L29 _public prototype_ `virtual bool IsReadOnly() const override;`
- L30 _public prototype_ `virtual void OnCreated() override;`
- L31 _public prototype_ `virtual void OnSourceChanged(const FMediaStreamSource& InSource) override;`
- L32 _public prototype_ `virtual UMediaTexture* GetMediaTexture() const override;`
- L33 _public prototype_ `virtual const FMediaStreamTextureConfig& GetTextureConfig() const override;`
- L34 _public prototype_ `virtual void SetTextureConfig(const FMediaStreamTextureConfig& InTextureConfig) override;`
- L35 _public prototype_ `virtual void ApplyTextureConfig() override;`
- L36 _public prototype_ `virtual UMediaPlayer* GetPlayer() const override;`
- L37 _public prototype_ `virtual bool HasValidPlayer() const override;`
- L38 _public prototype_ `virtual const FMediaStreamPlayerConfig& GetPlayerConfig() const override;`
- L39 _public prototype_ `virtual void SetPlayerConfig(const FMediaStreamPlayerConfig& InPlayerConfig) override;`
- L40 _public prototype_ `virtual void ApplyPlayerConfig() override;`
- L41 _public prototype_ `virtual bool SetPlaylistIndex(int32 InIndex) override;`
- L42 _public prototype_ `virtual float GetRequestedSeekTime() const override;`
- L43 _public prototype_ `virtual bool SetRequestedSeekTime(float InTime) override;`
- L44 _public prototype_ `virtual int32 GetRequestedSeekFrame() const override;`
- L45 _public prototype_ `virtual bool SetRequestedSeekFrame(int32 InFrame) override;`
- L46 _public prototype_ `virtual EMediaStreamPlaybackState GetPlaybackState() const override;`
- L47 _public prototype_ `virtual bool SetPlaybackState(EMediaStreamPlaybackState InState) override;`
- L48 _public prototype_ `virtual int32 GetPlaylistIndex() const override;`
- L49 _public prototype_ `virtual int32 GetPlaylistNum() const override;`
- L50 _public prototype_ `virtual UMediaStream* GetSourceStream() const override;`
- L51 _public prototype_ `virtual bool OpenSource() override;`
- L52 _public prototype_ `virtual bool Play() override;`
- L53 _public prototype_ `virtual bool Pause() override;`
- L54 _public prototype_ `virtual bool Rewind() override;`
- L55 _public prototype_ `virtual bool FastForward() override;`
- L56 _public prototype_ `virtual bool Previous() override;`
- L57 _public prototype_ `virtual bool Next() override;`
- L58 _public prototype_ `virtual bool Close() override;`
- L59 _public prototype_ `virtual void Deinitialize() override;`
- L64 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L71 _protected member_ `TSoftObjectPtr<UMediaStream> ProxyStreamSoft;` — `UPROPERTY()` — Soft pointer to the proxied stream.
- L75 _protected member_ `mutable TObjectPtr<UMediaStream> ProxyStream;` — `UPROPERTY(Transient)` — Hard reference to the proxied stream.
- L79 _protected member_ `bool bReadOnly = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Stream|Player")` — If true, the proxied stream won't receive set calls.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/SchemeHandlers/MediaStreamAssetSchemeHandler.h` (Private)


#### class `FMediaStreamAssetSchemeHandler`  
`class FMediaStreamAssetSchemeHandler : public IMediaStreamSchemeHandler`  
_L14-38_
- inherits: `IMediaStreamSchemeHandler`
- L17 _public member_ `static const FLazyName Scheme;`
- L20 _public prototype_ `virtual FMediaStreamSource CreateSource(UObject* InOuter, const FString& InPath) override;`
- L21 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) override;`
- L24 _public prototype_ `virtual void CreatePropertyCustomization(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets) override;`
- L29 _protected prototype_ `UObject* ResolveAsset(const FString& InPath);`
- L32 _protected prototype_ `void AddAssetSelector(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets);`
- L34 _protected prototype_ `EVisibility GetAssetSelectorVisibility(TWeakObjectPtr<UMediaStream> InMediaStreamWeak) const;`
- L36 _protected prototype_ `void OnAssetSelected(const FAssetData& InAssetData, TWeakObjectPtr<UMediaStream> InMediaStreamWeak);`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/SchemeHandlers/MediaStreamFileSchemeHandler.h` (Private)


#### class `FMediaStreamFileSchemeHandler`  
`class FMediaStreamFileSchemeHandler : public IMediaStreamSchemeHandler`  
_L10-36_
- inherits: `IMediaStreamSchemeHandler`
- L13 _public member_ `static const FLazyName Scheme;`
- L16 _public prototype_ `virtual FMediaStreamSource CreateSource(UObject* InOuter, const FString& InPath) override;`
- L17 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) override;`
- L20 _public prototype_ `virtual void CreatePropertyCustomization(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets) override;`
- L25 _protected prototype_ `FString ResolveFilePath(const FString& InPath);`
- L27 _protected prototype_ `UMediaSource* CreateMediaSource(UObject* InOuter, const FString& InPath);`
- L30 _protected prototype_ `void AddFileSelector(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets);`
- L32 _protected prototype_ `EVisibility GetFileSelectorVisibility(TWeakObjectPtr<UMediaStream> InMediaStreamWeak) const;`
- L34 _protected prototype_ `void OnFilePicked(const FString& InFilePath, TWeakObjectPtr<UMediaStream> InMediaStreamWeak);`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/SchemeHandlers/MediaStreamManagedSchemeHandler.h` (Private)


#### class `FMediaStreamManagedSchemeHandler`  
`class FMediaStreamManagedSchemeHandler : public IMediaStreamSchemeHandler`  
_L7-20_
- inherits: `IMediaStreamSchemeHandler`
- L10 _public member_ `static const FLazyName Scheme;`
- L13 _public prototype_ `virtual FMediaStreamSource CreateSource(UObject* InOuter, const FString& InPath) override;`
- L14 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) override;`
- L17 _public prototype_ `virtual void CreatePropertyCustomization(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets) override;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Private/SchemeHandlers/MediaStreamSubobjectSchemeHandler.h` (Private)


#### class `FMediaStreamSubobjectSchemeHandler`  
`class FMediaStreamSubobjectSchemeHandler : public IMediaStreamSchemeHandler`  
_L9-25_
- inherits: `IMediaStreamSchemeHandler`
- L12 _public member_ `static const FLazyName Scheme;`
- L15 _public prototype_ `virtual FMediaStreamSource CreateSource(UObject* InOuter, const FString& InPath) override;`
- L16 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) override;`
- L19 _public prototype_ `virtual void CreatePropertyCustomization(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets) override;`
- L24 _protected prototype_ `UObject* ResolveSubobjectPath(UObject* InOuter, const FString& InPath);`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/IMediaStreamObjectHandler.h` (Public)


#### struct `FMediaStreamObjectHandlerCreatePlayerParams`  
`struct FMediaStreamObjectHandlerCreatePlayerParams`  
_L14-41_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `TObjectPtr<UMediaStream> MediaStream;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — The container for the player.
- L24 _public member_ `TObjectPtr<UObject> Source;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — The media source for the player.
- L32 _public member_ `TObjectPtr<UMediaPlayer> CurrentPlayer;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — The current player to update or null. If a player is provided, it will be re-used to open the source, if it can be. If no player is provided, a new player will be created (if allowed).
- L40 _public member_ `bool bCanOpenSource = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — Whether the new player can open the source or not. If this is false, it may mean that a new player is not created or an existing player is not updated.

#### class `IMediaStreamObjectHandler`  
`class IMediaStreamObjectHandler : public TSharedFromThis<IMediaStreamObjectHandler>`  
_L47-58_
- inherits: `TSharedFromThis<IMediaStreamObjectHandler>`
- desc: Implement this interface to add a new object handler. If the derived class has a static UClass* Class then it can be added without specifying it.
- L50 _public prototype_ `virtual ~IMediaStreamObjectHandler() = default;`
- L57 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) = 0;` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/IMediaStreamPlayer.h` (Public)


#### class `UMediaStreamPlayer`  
`class UMediaStreamPlayer : public UInterface`  
_L24-27_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, Category = "Media Stream", meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for Media Stream Players. Should only be used within a Media Stream object.

#### class `IMediaStreamPlayer`  
`class IMediaStreamPlayer`  
_L32-238_
- desc: Interface for Media Stream Players. Should only be used within a Media Stream object.
- L38 _public prototype_ `virtual UMediaStream* GetMediaStream() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")`
- L42 _public prototype_ `virtual bool IsReadOnly() const = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Returns whether this player's controls can do anything.
- L45 _public prototype_ `virtual void OnCreated() = 0;` — `UFUNCTION(Category = "Media Stream|Player")`
- L50 _public prototype_ `virtual void OnSourceChanged(const FMediaStreamSource& InSource) = 0;` — Called by the owning Media Stream when the source changes so that the player can update.
- L56 _public prototype_ `virtual UMediaTexture* GetMediaTexture() const = 0;` — `UFUNCTION(Category = "Media Stream|Texture")` — @return Gets the media texture subobject.
- L62 _public prototype_ `virtual const FMediaStreamTextureConfig& GetTextureConfig() const = 0;` — `UFUNCTION(Category = "Media Stream|Texture")` — @return The current texture config.
- L69 _public prototype_ `virtual void SetTextureConfig(const FMediaStreamTextureConfig& InTextureConfig) = 0;` — `UFUNCTION(Category = "Media Stream|Texture")` — Update the current texture's (and any newly set texture's) config. @param InTextureConfig The new config.
- L76 _public prototype_ `virtual void ApplyTextureConfig() = 0;` — `UFUNCTION(Category = "Media Stream|Texture")` — Applies the current texture config to the current media texture. This is generally automatic.
- L82 _public prototype_ `virtual UMediaPlayer* GetPlayer() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @returns The active player, if there is one and it is valid.
- L88 _public prototype_ `virtual bool HasValidPlayer() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return True if there is an active and valid player.
- L94 _public prototype_ `virtual const FMediaStreamPlayerConfig& GetPlayerConfig() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return The current player config.
- L101 _public prototype_ `virtual void SetPlayerConfig(const FMediaStreamPlayerConfig& InPlayerConfig) = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Update the current player's (and any newly set player's) config. @param InPlayerConfig The new config.
- L108 _public prototype_ `virtual void ApplyPlayerConfig() = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Applies the current player config to the current media player. This is generally automatic.
- L116 _public prototype_ `virtual bool SetPlaylistIndex(int32 InIndex) = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Setter for events. @param InIndex The index to start playing. @return True on success. False on failure or invalid player.
- L122 _public prototype_ `virtual float GetRequestedSeekTime() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return The time offset in the media that has been requested.
- L130 _public prototype_ `virtual bool SetRequestedSeekTime(float InTime) = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Sets the time in the currently playing player, if possible. @param InTime The time offset in the media to request. @return True on success. False on failure or invalid player.
- L136 _public prototype_ `virtual int32 GetRequestedSeekFrame() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return The frame offset in the media that has been requested.
- L144 _public prototype_ `virtual bool SetRequestedSeekFrame(int32 InFrame) = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Sets the frame in the currently playing player, if possible. @param InFrame The frame offset in the media to request. @return True on success. False on failure or invalid player.
- L150 _public prototype_ `virtual EMediaStreamPlaybackState GetPlaybackState() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return Gets the media player playback state.
- L158 _public prototype_ `virtual bool SetPlaybackState(EMediaStreamPlaybackState InState) = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — Sets the media player playback state. @param InState The state to change to. @return True on success. False on failure or invalid player.
- L164 _public prototype_ `virtual int32 GetPlaylistIndex() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return Gets the active playlist index. May not match the actual player. -1 on error.
- L170 _public prototype_ `virtual int32 GetPlaylistNum() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return The size of the current playlist. -1 on error.
- L176 _public prototype_ `virtual UMediaStream* GetSourceStream() const = 0;` — `UFUNCTION(Category = "Media Stream|Player")` — @return For proxy streams, returns the stream this is getting data from.
- L183 _public prototype_ `virtual bool OpenSource() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Opens the source if it is not already opened. @return True if successful.
- L190 _public prototype_ `virtual bool Play() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Continues play of the current media. @return True if successful.
- L197 _public prototype_ `virtual bool Pause() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Pauses playback of the current media. @return True if successful.
- L204 _public prototype_ `virtual bool Rewind() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Seeks to the start of the current media. @return True if successful.
- L211 _public prototype_ `virtual bool FastForward() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Seeks to the end of the current media. @return True if successful.
- L218 _public prototype_ `virtual bool Previous() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Goes to the previous item in the playlist. Only possible with playlist sources. @return True if successful.
- L225 _public prototype_ `virtual bool Next() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Goes to the next item in the playlist. Only possible with playlist sources. @return True if successful.
- L232 _public prototype_ `virtual bool Close() = 0;` — `UFUNCTION(CallInEditor, Category = "Media Stream|Player")` — Closes the current media player. @return True if successful.
- L237 _public prototype_ `virtual void Deinitialize() = 0;` — Called by the Media Stream when it is done with this Media Stream Player.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/IMediaStreamSchemeHandler.h` (Public)


#### struct `FMediaStreamSchemeHandlerCreatePlayerParams`  
`struct FMediaStreamSchemeHandlerCreatePlayerParams`  
_L24-49_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `TObjectPtr<UMediaStream> MediaStream;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — The container for the player.
- L38 _public member_ `TObjectPtr<UMediaPlayer> CurrentPlayer;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — The current player to update or null. If a player is provided, it will be re-used to open the source, if it can be. If no player is provided, a new player will be created (if allowed).
- L46 _public member_ `bool bCanOpenSource = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Media Stream")` — Whether the new player can open the source or not. If this is false, it may mean that a new player is not created or an existing player is not updated.
- L48 _public prototype_ `FMediaStreamObjectHandlerCreatePlayerParams operator<<(UObject* InMediaSource) const;`

#### class `IMediaStreamSchemeHandler`  
`class IMediaStreamSchemeHandler : public TSharedFromThis<IMediaStreamSchemeHandler>`  
_L55-92_
- inherits: `TSharedFromThis<IMediaStreamSchemeHandler>`
- desc: Implement this interface to add a new scheme handler. If the derived class has a static TCHAR Scheme[] then it can be added without specifying it.
- L58 _public prototype_ `virtual ~IMediaStreamSchemeHandler() = default;`
- L66 _public prototype_ `virtual FMediaStreamSource CreateSource(UObject* InOuter, const FString& InPath) = 0;` — Passes a path to produce a stream source. @param InOuter The container of the source. @param InPath The path representing the source. @return A valid stream source object or none if it was not a valid path.
- L73 _public prototype_ `virtual UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) = 0;` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.
- L90 _public prototype_ `virtual void CreatePropertyCustomization(UMediaStream* InMediaStream, IMediaStreamSchemeHandler::FCustomWidgets& InOutCustomWidgets) = 0;`

#### struct `IMediaStreamSchemeHandler::FWidgetRow`  
`struct FWidgetRow`  
_L76-83_
- L78 _public member_ `FText Name;`
- L79 _public member_ `TSharedRef<SWidget> Widget;`
- L80 _public member_ `TAttribute<bool> Enabled = true;`
- L81 _public member_ `TAttribute<EVisibility> Visibility = EVisibility::Visible;`
- L82 _public member_ `FProperty* SourceProperty = nullptr;`

#### struct `IMediaStreamSchemeHandler::FCustomWidgets`  
`struct FCustomWidgets`  
_L85-88_
- L87 _public member_ `TArray<FWidgetRow> CustomRows;`

#### class `FMediaStreamSchemeHandlerLibrary`  
`class FMediaStreamSchemeHandlerLibrary`  
_L95-111_
- L98 _public prototype_ `static FMediaStreamSource* GetStreamSourcePtr(TWeakPtr<IPropertyHandle> InPropertyHandleWeak);`
- L100 _public prototype_ `static FName GetScheme(TWeakPtr<IPropertyHandle> InPropertyHandleWeak);`
- L101 _public prototype_ `static FName GetScheme(UMediaStream* InMediaStream);`
- L102 _public prototype_ `static FName GetScheme(TWeakObjectPtr<UMediaStream> InMediaStreamWeak);`
- L104 _public prototype_ `static FString GetPath(TWeakPtr<IPropertyHandle> InPropertyHandleWeak);`
- L105 _public prototype_ `static FString GetPath(UMediaStream* InMediaStream);`
- L106 _public prototype_ `static FString GetPath(TWeakObjectPtr<UMediaStream> InMediaStreamWeak);`
- L108 _public prototype_ `static void SetSource(TSharedRef<IPropertyHandle> InPropertyHandle, const FName& InScheme, const FString& InPath);`
- L109 _public prototype_ `static void SetSource(UMediaStream* InMediaStream, const FName& InScheme, const FString& InPath);`
- L110 _public prototype_ `static void SetSource(TWeakObjectPtr<UMediaStream> InMediaStreamWeak, const FName& InScheme, const FString& InPath);`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStream.h` (Public)


#### class `UMediaStream`  
`class UMediaStream : public UObject, public IMediaPlayerProxyInterface`  
_L21-151_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, ClassGroup = "Media Stream", DefaultToInstanced, PrioritizeCategories = (MediaStream, MediaControls, MediaSource, MediaDetails, MediaTexture, MediaCache, MediaPlayer))`
- inherits: `UObject,IMediaPlayerProxyInterface`
- desc: Media Stream. Provides an agnostic interface between controllers and players.
- L26 _public prototype_ `static FName GetSourcePropertyName();`
- L27 _public prototype_ `static FName GetPlayerPropertyName();`
- L29 _public prototype_ `virtual ~UMediaStream() override = default;`
- L35 _public prototype_ `bool HasValidSource() const;` — `UFUNCTION(Category = "Media Stream")` — @return True if the media source scheme is not empty. Does not guarantee the source is correct, only valid.
- L41 _public prototype_ `const FMediaStreamSource& GetSource() const;` — `UFUNCTION(Category = "Media Stream")` — @return The current Media Stream Source. Does not guaranteed that it is valid.
- L48 _public prototype_ `const FMediaStreamSource& ResolveSource() const;` — `UFUNCTION(Category = "Media Stream")` — @return The source at the end of the chain of proxy players, or the local one if it is local. If the chain is interrupted, the last link in the chain's source will be returned.
- L56 _public prototype_ `bool SetSource(const FMediaStreamSource& InSource);` — `UFUNCTION(Category = "Media Stream")` — Sets a new Media Stream Source and inits the Player. It should be ready to use if this returns true. @param InSource The new source. @return True if the source was successfully applied.
- L62 _public prototype_ `TScriptInterface<IMediaStreamPlayer> GetPlayer() const;` — `UFUNCTION(Category = "Media Stream")` — @return Gets the active Media Stream Player.
- L70 _public prototype_ `bool EnsurePlayer(bool bInForceRecreatePlayer = false);` — `UFUNCTION(Category = "Media Stream")` — Creates a player if it doesn't exist. @param  bInForceRecreatePlayer Will remove and recreate the player. @return True if a valid player exists.
- L75 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSourceChanged, UMediaStream*, InMediaStream);` — Called when the Media Stream Source changes.
- L76 _public prototype_ `FOnSourceChanged& GetOnSourceChanged();`
- L81 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerChanged, UMediaStream*, InMediaStream);` — Called when the Media Stream Player or its Settings change.
- L82 _public prototype_ `FOnPlayerChanged& GetOnPlayerChanged();`
- L89 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreSourceChange, UMediaStream* );` — Fires after the player has been created (so GetPlayer()->GetMediaTexture() is valid) but before its IMediaStreamPlayer::OnSourceChanged runs. Skipped when the new source is invalid. Handlers must not re-enter SetSource synchronously.
- L90 _public prototype_ `FOnPreSourceChange& GetOnPreSourceChange();`
- L95 _public prototype_ `void Close();` — Stops the media stream and unloads any resources.
- L99 _public prototype_ `virtual void PreEditUndo() override;`
- L100 _public prototype_ `virtual void PostEditUndo() override;`
- L101 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L103 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L104 _public prototype_ `virtual void PostEditImport() override;`
- L105 _public prototype_ `virtual void PostNetReceive() override;`
- L106 _public prototype_ `virtual void BeginDestroy() override;`
- L110 _public prototype_ `virtual float GetProxyRate() const override;`
- L111 _public prototype_ `virtual bool SetProxyRate(float Rate) override;`
- L112 _public prototype_ `virtual bool IsExternalControlAllowed() override;`
- L113 _public prototype_ `virtual const FMediaSourceCacheSettings& GetCacheSettings() const override;`
- L114 _public prototype_ `virtual UMediaSource* ProxyGetMediaSourceFromIndex(int32 Index) const override;`
- L115 _public prototype_ `virtual UMediaTexture* ProxyGetMediaTexture(int32 LayerIndex, int32 TextureIndex) override;`
- L116 _public prototype_ `virtual void ProxyReleaseMediaTexture(int32 LayerIndex, int32 TextureIndex) override;`
- L117 _public prototype_ `virtual bool ProxySetAspectRatio(UMediaPlayer* InMediaPlayer) override;`
- L118 _public prototype_ `virtual void ProxySetTextureBlend(int32 LayerIndex, int32 TextureIndex, float Blend) override;`
- L123 _protected member_ `FMediaStreamSource Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media Source")`
- L130 _protected member_ `TObjectPtr<UObject> PlayerObject = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, DisplayName = "Player", Category = "Media Stream")` — The player instance is automatically created based on the type of source. Where possible, the player is re-used when opening new media.
- L133 _protected member_ `FOnSourceChanged OnSourceChanged;` — `UPROPERTY(BlueprintAssignable)`
- L136 _protected member_ `FOnPlayerChanged OnPlayerChanged;` — `UPROPERTY(BlueprintAssignable)`
- L139 _protected member_ `FOnPreSourceChange OnPreSourceChange;` — Fired by ApplySource between player creation and IMediaStreamPlayer::OnSourceChanged. See GetOnPreSourceChange.
- L142 _protected member_ `bool bIsApplyingSource = false;` — True while ApplySource is in progress; blocks recursive SetSource calls from delegate handlers.
- L144 _protected member_ `FMediaStreamSource Source_PreUndo;`
- L150 _protected prototype_ `bool ApplySource();` — Applies the current source settings to this Media Stream, potentially changing the Media Stream Player. @return True if it was successful.

#### Free symbols / members of external scopes

- L75 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSourceChanged, UMediaStream*, InMediaStream);` — Called when the Media Stream Source changes.
- L81 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerChanged, UMediaStream*, InMediaStream);` — Called when the Media Stream Player or its Settings change.
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreSourceChange, UMediaStream* );` — Fires after the player has been created (so GetPlayer()->GetMediaTexture() is valid) but before its IMediaStreamPlayer::OnSourceChanged runs. Skipped when the new source is invalid. Handlers must not re-enter SetSource synchronously.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamActor.h` (Public)


#### class `AMediaStreamActor`  
`class AMediaStreamActor : public AActor`  
_L13-23_
- reflection: `UCLASS(BlueprintType, MinimalAPI, ComponentWrapperClass, NotPlaceable, PrioritizeCategories = (MediaStream, MediaControls, MediaSource, MediaDetails, MediaTexture, MediaCache, MediaPlayer))`
- inherits: `AActor`
- L18 _public prototype_ `AMediaStreamActor();`
- L22 _protected member_ `TObjectPtr<UMediaStreamComponent> MediaStreamComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media Stream")`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamComponent.h` (Public)


#### class `UMediaStreamComponent`  
`class UMediaStreamComponent : public UStaticMeshComponent`  
_L14-38_
- reflection: `UCLASS(BlueprintType, MinimalAPI, PrioritizeCategories = (MediaStream, MediaControls, MediaSource, MediaDetails, MediaTexture, MediaCache, MediaPlayer))`
- inherits: `UStaticMeshComponent`
- L19 _public prototype_ `UMediaStreamComponent();`
- L22 _public prototype_ `virtual void PostInitProperties() override;`
- L23 _public prototype_ `virtual void PostLoad() override;`
- L24 _public prototype_ `virtual void PostNetReceive() override;`
- L29 _protected member_ `TObjectPtr<UMediaStream> MediaStream;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media Stream")`
- L32 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstance;` — `UPROPERTY(BlueprintReadOnly, Transient, DuplicateTransient, TextExportTransient, Category = "Media Stream")`
- L35 _protected prototype_ `void OnSourceChanged(UMediaStream* InMediaStream);` — `UFUNCTION()`
- L37 _protected prototype_ `void InitPlayer();`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamEnums.h` (Public)


#### enum `EMediaStreamPlaybackState`  
`enum class EMediaStreamPlaybackState : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Play`
- L13 _public enumerator_ `Pause`

#### enum `EMediaStreamPlaybackDirection`  
`enum class EMediaStreamPlaybackDirection : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Forward`
- L20 _public enumerator_ `Backward`

#### enum `EMediaStreamPlaybackSeek`  
`enum class EMediaStreamPlaybackSeek : uint8`  
_L24-30_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `Previous`
- L27 _public enumerator_ `Start`
- L28 _public enumerator_ `End`
- L29 _public enumerator_ `Next`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamModule.h` (Public)


#### class `FMediaStreamModule`  
`class FMediaStreamModule : public IModuleInterface`  
_L21-43_
- inherits: `IModuleInterface`
- desc: Media Stream - Content/type agnostic chainable media proxy with media player integration.
- L24 _public prototype_ `static FMediaStreamModule& Get();`
- L26 _public prototype_ `bool CanOpenSourceOnLoad();`
- L28 _public prototype_ `bool CanAutoplay() const;`
- L31 _public prototype_ `virtual void StartupModule() override;`
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _protected member_ `bool bIsMapLoading;`
- L39 _protected prototype_ `void OnMapLoad(const FString& InFilename, FCanLoadMap& OutCanLoadMap);`
- L41 _protected prototype_ `void OnMapOpened(const FString& InFilename, bool bInTemplate);`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaStream, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaStream, Log, All);`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamObjectHandlerManager.h` (Public)


#### class `FMediaStreamObjectHandlerManager`  
`class FMediaStreamObjectHandlerManager`  
_L20-196_
- desc: Handles the registration and operation of object handlers. Will fall back to using the Media Assets module if no handler is found.
- L28 _public prototype_ `static FMediaStreamObjectHandlerManager& Get();` — @return Gets the instance of this manager.
- L35 _public prototype_ `bool CanHandleObject(const UClass* InClass) const;` — Checks whether the given class has a class handler. Checks each super class too. @param InClass The class to check. @return True if any handler can handle the class.
- L44 _public function_ `bool CanHandleObject() const`
- L54 _public prototype_ `bool CanHandleObject(const UObject* InObject) const;` — Checks whether the given object's class has a class handler. Checks each super class too. @param InObject The object whose class is to be checked. @return True if any handler can handle the object's class.
- L61 _public prototype_ `bool HasObjectHandler(const UClass* InClass) const;` — Checks whether a class has a handler registered. @param InClass The class to check. Must be an exact match. @return True if the handler is registered.
- L68 _public prototype_ `bool HasObjectHandler(const UObject* InObject) const;` — Checks whether an object's class has a handler registered. @param InObject The object whose class to check. Must be an exact match. @return True if the handler is registered.
- L77 _public function_ `bool HasObjectHandler() const`
- L87 _public prototype_ `TSharedPtr<IMediaStreamObjectHandler> GetHandler(const UClass* InClass) const;` — Does an hierarchical search for a handler that can handle the given class. @param InClass A validity checked UObject class. @return The handler for the class, if found.
- L96 _public prototype_ `bool RegisterObjectHandler(const UClass* InClass, const TSharedRef<IMediaStreamObjectHandler>& InHandler);` — Registers a Object handler that creates a media player for the given object class. Holds a strong reference. Does not replace an already registered handler. @param InClass The class of the object handled. @param InHandler The handle which creates the media player. @return True if the handler was registered.
- L106 _public function_ `bool RegisterObjectHandler(const TSharedRef<IMediaStreamObjectHandler>& InHandler)`
- L121 _public function_ `bool RegisterObjectHandler(const UClass* InClass, InArgsType&&... InArgs)`
- L137 _public function_ `bool RegisterObjectHandler(InArgsType&&... InArgs)`
- L161 _public prototype_ `TSharedPtr<IMediaStreamObjectHandler> UnregisterObjectHandler(const UClass* InClass);` — Unregisters a Object handler. @param InClass The class to unregister. @return The removed Object handler, if found.
- L170 _public function_ `TSharedPtr<IMediaStreamObjectHandler> UnregisterObjectHandler()`
- L182 _public function_ `TSharedPtr<InHandlerClass> UnregisterObjectHandler()`
- L192 _public prototype_ `UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) const;` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.
- L195 _private member_ `TMap<FName, TSharedRef<IMediaStreamObjectHandler>> Handlers;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamObjectHandlerSubsystem.h` (Public)


#### class `UMediaStreamObjectHandlerSubsystem`  
`class UMediaStreamObjectHandlerSubsystem : public UEngineSubsystem`  
_L17-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Media Stream")`
- inherits: `UEngineSubsystem`
- desc: Subsystem for blueprint-style interaction with the Object Handler Manager.
- L26 _public prototype_ `static UMediaStreamObjectHandlerSubsystem* Get();` — `UFUNCTION(Category = "Media Stream|Object")` — @return Gets the instance of this subsystem.
- L34 _public prototype_ `bool CanHandleObject(const UClass* InClass) const;` — `UFUNCTION(Category = "Media Stream|Object")` — Checks whether the given class has a class handler. Checks each super class too. @param InClass The class to check. @return True if any handler can handle the class.
- L42 _public prototype_ `bool HasObjectHandler(const UClass* InClass) const;` — `UFUNCTION(Category = "Media Stream|Object")` — Checks whether a class has a handler registered. @param InClass The class to check. Must be an exact match. @return True if the handler is registered.
- L50 _public prototype_ `UMediaPlayer* CreateMediaPlayer(const FMediaStreamObjectHandlerCreatePlayerParams& InParams) const;` — `UFUNCTION(Category = "Media Stream|Object")` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamPlayerConfig.h` (Public)


#### struct `FMediaStreamPlayerConfig`  
`struct FMediaStreamPlayerConfig`  
_L12-67_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `bool bPlayOnOpen = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")`
- L20 _public member_ `FMediaPlayerTrackOptions TrackOptions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", EditFixedSize, meta = (EditFixedOrder))`
- L23 _public member_ `bool bLooping = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")`
- L26 _public member_ `float Volume = 1.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L29 _public member_ `TOptional<FFloatInterval> PlaybackTimeRange;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")`
- L32 _public member_ `float Rate = 1.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")`
- L35 _public member_ `float TimeDelay = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", meta = (Units = "s"))`
- L39 _public member_ `bool bShuffle = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")` — Only applicable to play lists.
- L43 _public member_ `float CacheAhead = 0.2f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", meta = (Units = "s", UIMin = 0.1, ClampMin = 0.01, UIMax = 5, ClampMax = 60))`
- L47 _public member_ `float CacheBehind = 3.0f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", meta = (Units = "s", UIMin = 0.1, ClampMin = 0.01, UIMax = 5, ClampMax = 60))`
- L51 _public member_ `float CacheBehindGame = 0.1f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player", meta = (Units = "s", UIMin = 0.1, ClampMin = 0.01, UIMax = 5, ClampMax = 60))`
- L58 _public member_ `bool bUseLocalCache = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Player")` — Enables a per-player local sample cache override instead of the default global cache settings. Currently maps to the ImgMediaPlayer smart cache, with CacheAhead reused as the look-ahead time.
- L60 _public prototype_ `bool operator==(const FMediaStreamPlayerConfig& InOther) const;`
- L62 _public prototype_ `FMediaPlayerOptions CreateOptions(const FTimespan& InStartTime, const TMap<FName, FVariant>& InCustomOptions = {}) const;`
- L64 _public prototype_ `void ApplyConfig(UMediaPlayer& InMediaPlayer) const;`
- L66 _public prototype_ `bool ApplyRate(UMediaPlayer& InMediaPlayer) const;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamSchemeHandlerManager.h` (Public)


#### class `FMediaStreamSchemeHandlerManager`  
`class FMediaStreamSchemeHandlerManager`  
_L19-121_
- desc: Handles the registration and operation of Scheme Handlers.
- L25 _public prototype_ `static FMediaStreamSchemeHandlerManager& Get();` — @return Gets the instance of this manager.
- L32 _public prototype_ `bool HasSchemeHandler(FName InScheme) const;` — Checks whether a scheme has a handler registered. @param InScheme The scheme to check. @return True if the handler is registered.
- L37 _public prototype_ `TArray<FName> GetSchemeHandlerNames() const;` — @return Gets the list of registered scheme handlers.
- L46 _public prototype_ `bool RegisterSchemeHandler(FName InScheme, const TSharedRef<IMediaStreamSchemeHandler>& InHandler);` — Registers a Scheme handler. Holds a strong reference. Does not replace an already registered handler. @param InScheme The scheme name. @param InHandler The handler which converts the path to a stream source. @return True if the handler was registered.
- L58 _public function_ `bool RegisterSchemeHandler(FName InScheme, InArgsType&&... InArgs)`
- L72 _public function_ `bool RegisterSchemeHandler(InArgsType&&... InArgs)`
- L82 _public prototype_ `TSharedPtr<IMediaStreamSchemeHandler> UnregisterSchemeHandler(FName InScheme);` — Unregisters a Scheme handler. @param InScheme The scheme to unregister. @return The removed Scheme handler, if found.
- L91 _public function_ `TSharedPtr<IMediaStreamSchemeHandler> UnregisterSchemeHandler()`
- L101 _public prototype_ `TSharedPtr<IMediaStreamSchemeHandler> GetHandlerTypeForScheme(FName InScheme) const;` — Finds the handler which is used for the given scheme. @param InScheme The scheme to check. @return The found handler or nullptr.
- L110 _public prototype_ `FMediaStreamSource CreateSource(UObject* InOuter, FName InScheme, const FString& InPath) const;` — Create a Media Stream Source from a scheme and path. Must have a registered handler. @param InOuter The container of the source. @param InScheme The scheme used to resolve the path. @param InPath The path to the media source. This should not be Url encoded. @return A valid stream source object or none if it was not a valid Url.
- L117 _public prototype_ `UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) const;` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.
- L120 _private member_ `TMap<FName, TSharedRef<IMediaStreamSchemeHandler>> Handlers;`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamSchemeHandlerSubsystem.h` (Public)


#### class `UMediaStreamSchemeHandlerSubsystem`  
`class UMediaStreamSchemeHandlerSubsystem : public UEngineSubsystem`  
_L21-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Media Stream")`
- inherits: `UEngineSubsystem`
- desc: Subsystem for blueprint-style interaction with the Scheme Handler Manager.
- L30 _public prototype_ `static UMediaStreamSchemeHandlerSubsystem* Get();` — `UFUNCTION(Category = "Media Stream|Scheme")` — @return Gets the instance of this subsystem.
- L38 _public prototype_ `bool HasSchemeHandler(FName InScheme) const;` — `UFUNCTION(Category = "Media Stream|Scheme")` — Checks whether a scheme has a handler registered. @param InScheme The scheme to check. @return True if the handler is registered.
- L44 _public prototype_ `TArray<FName> GetSchemeHandlerNames() const;` — `UFUNCTION(Category = "Media Stream|Scheme")` — @return Gets the list of registered scheme handlers.
- L54 _public prototype_ `FMediaStreamSource CreateSource(UObject* InOuter, FName InScheme, const FString& InPath) const;` — `UFUNCTION(Category = "Media Stream|Scheme")` — Create a Media Stream Source from a scheme and path. Must have a registered handler. @param InOuter The container of the source. @param InScheme The scheme used to resolve the path. @param InPath The path to the media source. This should not be Url encoded. @return A valid stream source object or none if it was not a valid Url.
- L62 _public prototype_ `UMediaPlayer* CreateOrUpdatePlayer(const FMediaStreamSchemeHandlerCreatePlayerParams& InParams) const;` — `UFUNCTION(Category = "Media Stream|Scheme")` — Create or update a UMediaPlayer for the provided source. Note: This usually means loading the media source. @see bCanLoadSource. @return A player or nullptr.

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamSource.h` (Public)


#### struct `FMediaStreamSource`  
`struct FMediaStreamSource`  
_L24-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents the source of a Media Stream. This uses the idea of a "scheme" and "path" to reference an asset. This nomenclature was chosen so that it would be easy to relate url schemes to this system, such as file://path or http://path.
- L34 _public member_ `FName Scheme = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media Stream|Source", meta = (GetOptions = "/Script/MediaStream.MediaStreamSourceBlueprintFunctionLibrary:GetSchemeTypes"))` — Used by the handler subsystem to identifer the scheme used. A value of NAME_None identifies a null or invalid source.
- L41 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media Stream|Source")` — Path to the referenced source, such as a file/asset path or a managed source name. A path must be provided to have a valid scheme.
- L48 _public member_ `TObjectPtr<UObject> Object = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media Stream|Source", meta = (AllowedClasses="/Script/MediaStream.MediaStream,/Script/MediaAssets.MediaSource,/Script/MediaAssets.MediaPlaylist"))` — Source of the Media. Either a UMediaStream, UMediaSource or a UMediaPlaylist
- L50 _public prototype_ `bool operator==(const FMediaStreamSource& InOther) const;`

#### class `UMediaStreamSourceBlueprintFunctionLibrary`  
`class UMediaStreamSourceBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L54-61_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L60 _public prototype_ `static TArray<FName> GetSchemeTypes();` — `UFUNCTION()`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamSourceBlueprintLibrary.h` (Public)


#### class `UMediaStreamSourceBlueprintLibrary`  
`class UMediaStreamSourceBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-126_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Media Stream")`
- inherits: `UBlueprintFunctionLibrary`
- desc: Deals with creating new Media Stream Sources.
- L30 _public prototype_ `static bool IsValidMediaSource(const FMediaStreamSource& InSource);` — `UFUNCTION(Category = "Media Stream|Source")` — Checks the media stream to see if its source type is none or set to something valid. And that the path is not empty. @param InSource The source to check. @return True if the source is valid. Does not guarantee it is correct, only valid.
- L38 _public prototype_ `static bool IsAssetValid(const TSoftObjectPtr<UObject>& InAsset);` — `UFUNCTION(Category = "Media Stream|Source")` — Checks the Asset pointer to see if it's a valid asset for a Media Stream Source. @param InAsset The asset to check. @return True if the asset is valid.
- L46 _public prototype_ `static bool IsAssetPathValid(const FString& InPath);` — `UFUNCTION(Category = "Media Stream|Source")` — Checks the Asset path to see if it's a valid asset for a Media Stream Source. @param InPath The asset path to check. @return True if the asset is valid.
- L54 _public prototype_ `static bool IsAssetSoftPathValid(const FSoftObjectPath& InPath);` — `UFUNCTION(Category = "Media Stream|Source")` — Checks the Asset soft path to see if it's a valid asset for a Media Stream Source. @param InPath The asset soft path to check. @return True if the asset is valid.
- L64 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromSchemePath(UMediaStream* InMediaStream, FName InScheme, const FString& InPath);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source from an Asset. Must have a registered handler. @param InMediaStream The owning Media Stream @param InScheme The scheme of the source. @param InPath The path to the source. @return A valid stream source object or none if it was not a valid object.
- L73 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromAsset(UMediaStream* InMediaStream, const TSoftObjectPtr<UObject>& InAsset);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source from an Asset. Must have a registered handler. @param InMediaStream The owning Media Stream @param InObject The playable object. @return A valid stream source object or none if it was not a valid object.
- L82 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromStreamName(UMediaStream* InMediaStream, FName InStreamName);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source from a stream name. Must be set up via the Media Source Manager. @param InMediaStream The owning Media Stream @param InStreamName The name of the registered stream. @return A valid stream source object or none if it was not a valid stream or the stream was not found.
- L91 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromFile(UMediaStream* InMediaStream, const FString& InFileName);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source from a file name. @param InMediaStream The owning Media Stream @param InFileName The path to the file name. Should be a full path or relative to the project or engine root. @return A valid stream source object or none if the file was not found.
- L101 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromSubobject(UMediaStream* InMediaStream, UObject* InObject);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source from an object. @param InMediaStream The owning Media Stream @param InRootObject Root of the relative path. @param InObject The playable object. Should share a common ancestor with the Media Stream, but this is not enforced. @return A valid stream source object or none if the file was not found.
- L111 _public prototype_ `static FMediaStreamSource MakeMediaSourceFromSubobjectClass(UMediaStream* InMediaStream, const UClass* InClass);` — `UFUNCTION(Category = "Media Stream|Source")` — Create a Media Stream Source by instantiating the given class. @param InMediaStream The owning Media Stream @param InClass The class of a playable object. @param InOuter The outer of the new object. Defaults to the media stream object. @return A valid stream source object or none if the file was not found.
- L122 _public function_ `static FMediaStreamSource MakeMediaSourceFromSubobject(UMediaStream* InMediaStream)`

### `Plugins/Experimental/MediaStream/Source/MediaStream/Public/MediaStreamTextureConfig.h` (Public)


#### struct `FMediaStreamTextureConfig`  
`struct FMediaStreamTextureConfig`  
_L12-22_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `bool bEnableMipGen = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Media Stream|Texture", DisplayName = "Enable Real Time Mips")`
- L19 _public prototype_ `bool operator==(const FMediaStreamTextureConfig& InOther) const;`
- L21 _public prototype_ `void ApplyConfig(UMediaTexture& InMediaTexture) const;`
