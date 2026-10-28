# Plugins / EOSVoiceChat

- module root: `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat`
- headers: 15; symbols: 501
- symbol kinds: class=11, delegate=9, enum=4, enumerator=16, function=28, macro=4, member=128, prototype=276, struct=12, typedef=13
- PrivateDependencyModuleNames: ApplicationCore, Core, EOSSDK, EOSShared, Projects
- PublicDependencyModuleNames: Json, VoiceChat

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/Android/AndroidEOSVoiceChat.h` (Private)


#### class `FAndroidEOSVoiceChat`  
`class FAndroidEOSVoiceChat : public FEOSVoiceChat`  
_L9-18_
- inherits: `FEOSVoiceChat`
- L12 _public prototype_ `FAndroidEOSVoiceChat(IEOSSDKManager& InSDKManager);`
- L13 _public prototype_ `virtual ~FAndroidEOSVoiceChat() = default;`
- L16 _public prototype_ `virtual IVoiceChatUser* CreateUser() override;`

#### Free symbols / members of external scopes

- L20 _typedef_ `using FPlatformEOSVoiceChat = FAndroidEOSVoiceChat;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/Android/AndroidEOSVoiceChatUser.h` (Private)


#### class `FAndroidEOSVoiceChatUser`  
`class FAndroidEOSVoiceChatUser : public FEOSVoiceChatUser`  
_L9-22_
- inherits: `FEOSVoiceChatUser`
- L12 _public function_ `FAndroidEOSVoiceChatUser(FEOSVoiceChat& InEOSVoiceChat) : FEOSVoiceChatUser(InEOSVoiceChat)`
- L13 _public prototype_ `virtual ~FAndroidEOSVoiceChatUser() = default;`
- L16 _public prototype_ `virtual void SetSetting(const FString& Name, const FString& Value) override;`
- L17 _public prototype_ `virtual FString GetSetting(const FString& Name) override;`
- L21 _private member_ `bool bEnableBluetoothMicrophone = false;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/EOSAudioDevicePool.h` (Private)


#### class `FEOSAudioDevicePool`  
`class FEOSAudioDevicePool final : public TSharedFromThis<FEOSAudioDevicePool>`  
_L9-39_
- inherits: `TSharedFromThis<FEOSAudioDevicePool>`
- L12 _public prototype_ `explicit FEOSAudioDevicePool(EOS_HRTC& InEosRtcInterface);`
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioDevicesCompleteDelegate, const FVoiceChatResult& );` — forward refreshing both input and output devices
- L16 _public prototype_ `void RefreshAudioDevices(const FOnAudioDevicePoolRefreshAudioDevicesCompleteDelegate& Delegate);`
- L18 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioInputDevicesCompleteDelegate, const FVoiceChatResult& );`
- L19 _public prototype_ `void RefreshAudioInputDevices(const FOnAudioDevicePoolRefreshAudioInputDevicesCompleteDelegate& Delegate);`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioOutputDevicesCompleteDelegate, const FVoiceChatResult& );`
- L22 _public prototype_ `void RefreshAudioOutputDevices(const FOnAudioDevicePoolRefreshAudioOutputDevicesCompleteDelegate& Delegate);`
- L24 _public prototype_ `const TArray<FVoiceChatDeviceInfo>& GetCachedInputDeviceInfos() const;`
- L25 _public prototype_ `const TArray<FVoiceChatDeviceInfo>& GetCachedOutputDeviceInfos() const;`
- L27 _public prototype_ `int32 GetDefaultInputDeviceInfoIdx() const;`
- L28 _public prototype_ `int32 GetDefaultOutputDeviceInfoIdx() const;`
- L30 _private prototype_ `TArray<FVoiceChatDeviceInfo> GetRtcInputDeviceInfos(int32& OutDefaultDeviceIdx) const;`
- L31 _private prototype_ `TArray<FVoiceChatDeviceInfo> GetRtcOutputDeviceInfos(int32& OutDefaultDeviceIdx) const;`
- L33 _private member_ `EOS_HRTC& EosRtcInterface;`
- L35 _private member_ `int32 DefaultInputDeviceInfoIdx = -1;`
- L36 _private member_ `int32 DefaultOutputDeviceInfoIdx = -1;`
- L37 _private member_ `TArray<FVoiceChatDeviceInfo> CachedInputDeviceInfos;`
- L38 _private member_ `TArray<FVoiceChatDeviceInfo> CachedOutputDeviceInfos;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioDevicesCompleteDelegate, const FVoiceChatResult& );` — forward refreshing both input and output devices
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioInputDevicesCompleteDelegate, const FVoiceChatResult& );`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAudioDevicePoolRefreshAudioOutputDevicesCompleteDelegate, const FVoiceChatResult& );`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/EOSVoiceChatErrors.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define EOSVOICECHAT_ERROR(...) FVoiceChatResult::CreateError(TEXT("errors.com.epicgames.voicechat.eos"), __VA_ARGS__)`
- L14 _prototype_ `FVoiceChatResult ResultFromEOSResult(const EOS_EResult EosResult);`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/EOSVoiceChatModule.h` (Private)


#### class `FEOSVoiceChatModule`  
`class FEOSVoiceChatModule : public IModuleInterface`  
_L11-26_
- inherits: `IModuleInterface`
- L14 _public prototype_ `FEOSVoiceChatModule() = default;`
- L15 _public prototype_ `~FEOSVoiceChatModule() = default;`
- L19 _private prototype_ `virtual void StartupModule() override;`
- L20 _private prototype_ `virtual void ShutdownModule() override;`
- L24 _private member_ `FEOSVoiceChatFactoryPtr EOSFactory;` — Singleton EOS object
- L25 _private member_ `IVoiceChatPtr EOSObj;`

#### Free symbols / members of external scopes

- L8 _typedef_ `using IVoiceChatPtr = TSharedPtr<class IVoiceChat, ESPMode::ThreadSafe>;`
- L9 _typedef_ `typedef TSharedPtr<class FEOSVoiceChatFactory, ESPMode::ThreadSafe> FEOSVoiceChatFactoryPtr;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/IOS/IOSEOSVoiceChat.h` (Private)


#### class `FIOSEOSVoiceChat`  
`class FIOSEOSVoiceChat : public FEOSVoiceChat`  
_L9-49_
- inherits: `FEOSVoiceChat`
- L12 _public prototype_ `FIOSEOSVoiceChat(IEOSSDKManager& InSDKManager);`
- L13 _public prototype_ `virtual ~FIOSEOSVoiceChat() = default;`
- L16 _public prototype_ `virtual void Initialize(const FOnVoiceChatInitializeCompleteDelegate& Delegate) override;`
- L17 _public prototype_ `virtual void Uninitialize(const FOnVoiceChatUninitializeCompleteDelegate& Delegate) override;`
- L18 _public prototype_ `virtual IVoiceChatUser* CreateUser() override;`
- L21 _public prototype_ `bool IsHardwareAECEnabled() const;`
- L22 _public prototype_ `void SetHardwareAECEnabled(bool bEnabled);`
- L23 _public prototype_ `bool IsBluetoothMicrophoneEnabled() const;`
- L24 _public prototype_ `void SetBluetoothMicrophoneEnabled(bool bEnabled);`
- L25 _public prototype_ `void EnableVoiceChat(bool bEnable);`
- L28 _private member_ `uint VoiceChatEnableCount = 0;`
- L30 _private member_ `bool bEnableHardwareAEC = false;`
- L31 _private member_ `TOptional<bool> OverrideEnableHardwareAEC;`
- L32 _private member_ `bool bVoiceChatModeEnabled = false;`
- L34 _private member_ `bool bEnableBluetoothMicrophone = false;`
- L35 _private member_ `TOptional<bool> OverrideEnableBluetoothMicrophone;`
- L36 _private member_ `bool bBluetoothMicrophoneFeatureEnabled = false;`
- L38 _private member_ `FDelegateHandle ApplicationWillEnterBackgroundHandle;`
- L39 _private member_ `FDelegateHandle ApplicationDidEnterForegroundHandle;`
- L40 _private member_ `FDelegateHandle AudioRouteChangedHandle;`
- L42 _private prototype_ `void HandleApplicationHasEnteredForeground();`
- L43 _private prototype_ `void HandleAudioRouteChanged(bool);`
- L45 _private prototype_ `void UpdateVoiceChatSettings();`
- L46 _private prototype_ `bool IsUsingBuiltInSpeaker();`
- L47 _private prototype_ `void SendAECSettingToUsers(bool bEnableAEC);`

#### Free symbols / members of external scopes

- L51 _typedef_ `using FPlatformEOSVoiceChat = FIOSEOSVoiceChat;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/IOS/IOSEOSVoiceChatUser.h` (Private)


#### class `FIOSEOSVoiceChatUser`  
`class FIOSEOSVoiceChatUser : public FEOSVoiceChatUser`  
_L11-27_
- inherits: `FEOSVoiceChatUser`
- L14 _public prototype_ `FIOSEOSVoiceChatUser(FEOSVoiceChat& InEOSVoiceChat);`
- L15 _public prototype_ `virtual ~FIOSEOSVoiceChatUser() = default;`
- L18 _public prototype_ `virtual void SetSetting(const FString& Name, const FString& Value) override;`
- L19 _public prototype_ `virtual void JoinChannel(const FString& ChannelName, const FString& ChannelCredentials, EVoiceChatChannelType ChannelType, const FOnVoiceChatChannelJoinCompleteDelegate& Delegate, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties) override;`
- L22 _public prototype_ `FIOSEOSVoiceChat& GetIOSVoiceChat();`
- L26 _private prototype_ `void HandleVoiceChatChannelExited(const FString& ChannelName, const FVoiceChatResult& Reason);`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/Linux/LinuxEOSVoiceChat.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSVoiceChat = FEOSVoiceChat;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/Mac/MacEOSVoiceChat.h` (Private)


#### Free symbols / members of external scopes

- L9 _typedef_ `using FPlatformEOSVoiceChat = FEOSVoiceChat;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Private/Windows/WindowsEOSVoiceChat.h` (Private)


#### class `FWindowsEOSVoiceChat`  
`class FWindowsEOSVoiceChat : public FEOSVoiceChat`  
_L9-17_
- inherits: `FEOSVoiceChat`
- L12 _public prototype_ `FWindowsEOSVoiceChat(IEOSSDKManager& InSDKManager);`
- L13 _public prototype_ `virtual ~FWindowsEOSVoiceChat() = default;`
- L16 _protected prototype_ `virtual IEOSPlatformHandlePtr EOSPlatformCreate(EOS_Platform_Options& PlatformOptions) override;`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FPlatformEOSVoiceChat = FWindowsEOSVoiceChat;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Public/EOSVoiceChat.h` (Public)


#### struct `FVoiceChatMetadataItem`  
`struct FVoiceChatMetadataItem`  
_L21-25_
- L23 _public member_ `FString Key;`
- L24 _public member_ `FString Value;`

#### class `FEOSVoiceChatDelegates`  
`class FEOSVoiceChatDelegates`  
_L27-39_
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioInputDeviceStatusChanged, FString , EOS_ERTCAudioInputStatus );` — Delegate called when the status of the audio device has changed.
- L32 _public member_ `static FOnAudioInputDeviceStatusChanged OnAudioInputDeviceStatusChanged;`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatPlayerAddedMetadataDelegate, const FString& , const FString& , const FString& , const TArray<FVoiceChatMetadataItem>& );` — Delegate called when ParticipantMetadata is included in the player joined event
- L35 _public member_ `static FOnVoiceChatPlayerAddedMetadataDelegate OnVoiceChatPlayerAddedMetadata;`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAudioStatusChanged, const FString& , const FString& , const FString& , const EOS_ERTCAudioStatus );` — Delegate called when the audio status has changed
- L38 _public member_ `static FOnAudioStatusChanged OnAudioStatusChanged;`

#### class `FEOSVoiceChat`  
`class FEOSVoiceChat : public TSharedFromThis<FEOSVoiceChat, ESPMode::ThreadSafe>, public IVoiceChat`  
_L50-251_
- inherits: `TSharedFromThis<FEOSVoiceChat,ESPMode::ThreadSafe>,IVoiceChat`
- L53 _public prototype_ `FEOSVoiceChat(IEOSSDKManager& InSDKManager);`
- L56 _public prototype_ `FEOSVoiceChat(IEOSSDKManager& InSDKManager, const IEOSPlatformHandlePtr& PlatformHandle);` — `UE_DEPRECATED(5.8, "Use FEOSVoiceChat(IEOSSDKManager&) and call SetPlatformHandle() instead")`
- L58 _public prototype_ `virtual ~FEOSVoiceChat();`
- L61 _public prototype_ `virtual bool Initialize() override;`
- L62 _public prototype_ `virtual void Initialize(const FOnVoiceChatInitializeCompleteDelegate& Delegate) override;`
- L63 _public prototype_ `virtual bool Uninitialize() override;`
- L64 _public prototype_ `virtual void Uninitialize(const FOnVoiceChatUninitializeCompleteDelegate& Delegate) override;`
- L65 _public prototype_ `virtual bool IsInitialized() const override;`
- L66 _public prototype_ `virtual void Connect(const FOnVoiceChatConnectCompleteDelegate& Delegate) override;`
- L67 _public prototype_ `virtual void Disconnect(const FOnVoiceChatDisconnectCompleteDelegate& Delegate) override;`
- L68 _public prototype_ `virtual bool IsConnecting() const override;`
- L69 _public prototype_ `virtual bool IsConnected() const override;`
- L70 _public function_ `virtual FOnVoiceChatConnectedDelegate& OnVoiceChatConnected() override`
- L71 _public function_ `virtual FOnVoiceChatDisconnectedDelegate& OnVoiceChatDisconnected() override`
- L72 _public function_ `virtual FOnVoiceChatReconnectedDelegate& OnVoiceChatReconnected() override`
- L73 _public prototype_ `virtual IVoiceChatUser* CreateUser() override;`
- L74 _public prototype_ `virtual void ReleaseUser(IVoiceChatUser* VoiceChatUser) override;`
- L78 _public function_ `void SetPlatformConfigName(const FString& PlatformConfigName)` — Set the platform config name to use during Initialize(). Only used if no platform handle is set.
- L82 _public function_ `void SetPlatformHandle(const IEOSPlatformHandlePtr& PlatformHandle)` — Set an existing platform handle to use during Initialize(). If set, Initialize() will use this handle instead of creating one via named config or inline credentials
- L85 _public prototype_ `virtual void SetSetting(const FString& Name, const FString& Value) override;`
- L86 _public prototype_ `virtual FString GetSetting(const FString& Name) override;`
- L87 _public prototype_ `virtual void SetAudioInputVolume(float Volume) override;`
- L88 _public prototype_ `virtual void SetAudioOutputVolume(float Volume) override;`
- L89 _public prototype_ `virtual float GetAudioInputVolume() const override;`
- L90 _public prototype_ `virtual float GetAudioOutputVolume() const override;`
- L91 _public prototype_ `virtual void SetAudioInputDeviceMuted(bool bIsMuted) override;`
- L92 _public prototype_ `virtual void SetAudioOutputDeviceMuted(bool bIsMuted) override;`
- L93 _public prototype_ `virtual bool GetAudioInputDeviceMuted() const override;`
- L94 _public prototype_ `virtual bool GetAudioOutputDeviceMuted() const override;`
- L95 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableInputDeviceInfos() const override;`
- L96 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableOutputDeviceInfos() const override;`
- L97 _public prototype_ `virtual FOnVoiceChatAvailableAudioDevicesChangedDelegate& OnVoiceChatAvailableAudioDevicesChanged() override;`
- L98 _public prototype_ `virtual void SetInputDeviceId(const FString& InputDeviceId) override;`
- L99 _public prototype_ `virtual void SetOutputDeviceId(const FString& OutputDeviceId) override;`
- L100 _public prototype_ `virtual FVoiceChatDeviceInfo GetInputDeviceInfo() const override;`
- L101 _public prototype_ `virtual FVoiceChatDeviceInfo GetOutputDeviceInfo() const override;`
- L102 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultInputDeviceInfo() const override;`
- L103 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultOutputDeviceInfo() const override;`
- L104 _public prototype_ `virtual void Login(FPlatformUserId PlatformId, const FString& PlayerName, const FString& Credentials, const FOnVoiceChatLoginCompleteDelegate& Delegate) override;`
- L105 _public prototype_ `virtual void Logout(const FOnVoiceChatLogoutCompleteDelegate& Delegate) override;`
- L106 _public prototype_ `virtual bool IsLoggingIn() const override;`
- L107 _public prototype_ `virtual bool IsLoggedIn() const override;`
- L108 _public prototype_ `virtual FOnVoiceChatLoggedInDelegate& OnVoiceChatLoggedIn() override;`
- L109 _public prototype_ `virtual FOnVoiceChatLoggedOutDelegate& OnVoiceChatLoggedOut() override;`
- L110 _public prototype_ `virtual FString GetLoggedInPlayerName() const override;`
- L111 _public prototype_ `virtual void BlockPlayers(const TArray<FString>& PlayerNames) override;`
- L112 _public prototype_ `virtual void UnblockPlayers(const TArray<FString>& PlayerNames) override;`
- L113 _public prototype_ `virtual void JoinChannel(const FString& ChannelName, const FString& ChannelCredentials, EVoiceChatChannelType ChannelType, const FOnVoiceChatChannelJoinCompleteDelegate& Delegate, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) override;`
- L114 _public prototype_ `virtual void LeaveChannel(const FString& Channel, const FOnVoiceChatChannelLeaveCompleteDelegate& Delegate) override;`
- L115 _public prototype_ `virtual FOnVoiceChatChannelJoinedDelegate& OnVoiceChatChannelJoined() override;`
- L116 _public prototype_ `virtual FOnVoiceChatChannelExitedDelegate& OnVoiceChatChannelExited() override;`
- L118 _public prototype_ `virtual FOnVoiceChatCallStatsUpdatedDelegate& OnVoiceChatCallStatsUpdated() override;` — `UE_DEPRECATED(5.8, "Please use OnVoiceChatCallStatsUpdated2 which adds the ChannelName param")`
- L119 _public prototype_ `virtual FOnVoiceChatCallStatsUpdatedDelegate2& OnVoiceChatCallStatsUpdated2() override;`
- L120 _public prototype_ `virtual TOptional<FVoiceChatCallStats> GetChannelCallStats(const FString& ChannelName) const override;`
- L121 _public prototype_ `virtual void Set3DPosition(const FString& ChannelName, const FVector& Position) override;`
- L122 _public prototype_ `virtual TArray<FString> GetChannels() const override;`
- L123 _public prototype_ `virtual TArray<FString> GetPlayersInChannel(const FString& ChannelName) const override;`
- L124 _public prototype_ `virtual EVoiceChatChannelType GetChannelType(const FString& ChannelName) const override;`
- L125 _public prototype_ `virtual FOnVoiceChatPlayerAddedDelegate& OnVoiceChatPlayerAdded() override;`
- L126 _public prototype_ `virtual FOnVoiceChatPlayerRemovedDelegate& OnVoiceChatPlayerRemoved() override;`
- L127 _public prototype_ `virtual bool IsPlayerTalking(const FString& PlayerName) const override;`
- L128 _public prototype_ `virtual FOnVoiceChatPlayerTalkingUpdatedDelegate& OnVoiceChatPlayerTalkingUpdated() override;`
- L129 _public prototype_ `virtual void SetPlayerMuted(const FString& PlayerName, bool bMuted) override;`
- L130 _public prototype_ `virtual bool IsPlayerMuted(const FString& PlayerName) const override;`
- L131 _public prototype_ `virtual void SetChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName, bool bMuted) override;`
- L132 _public prototype_ `virtual bool IsChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName) const override;`
- L133 _public prototype_ `virtual FOnVoiceChatPlayerMuteUpdatedDelegate& OnVoiceChatPlayerMuteUpdated() override;`
- L134 _public prototype_ `virtual void SetPlayerVolume(const FString& PlayerName, float Volume) override;`
- L135 _public prototype_ `virtual float GetPlayerVolume(const FString& PlayerName) const override;`
- L136 _public prototype_ `virtual FOnVoiceChatPlayerVolumeUpdatedDelegate& OnVoiceChatPlayerVolumeUpdated() override;`
- L137 _public prototype_ `virtual void TransmitToAllChannels() override;`
- L138 _public prototype_ `virtual void TransmitToNoChannels() override;`
- L139 _public prototype_ `virtual void TransmitToSpecificChannels(const TSet<FString>& ChannelNames) override;`
- L140 _public prototype_ `virtual EVoiceChatTransmitMode GetTransmitMode() const override;`
- L141 _public prototype_ `virtual TSet<FString> GetTransmitChannels() const override;`
- L142 _public prototype_ `virtual FDelegateHandle StartRecording(const FOnVoiceChatRecordSamplesAvailableDelegate::FDelegate& Delegate) override;`
- L143 _public prototype_ `virtual void StopRecording(FDelegateHandle Handle) override;`
- L144 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatAfterCaptureAudioReadDelegate(const FOnVoiceChatAfterCaptureAudioReadDelegate2::FDelegate& Delegate) override;`
- L145 _public prototype_ `virtual void UnregisterOnVoiceChatAfterCaptureAudioReadDelegate(FDelegateHandle Handle) override;`
- L146 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeCaptureAudioSentDelegate(const FOnVoiceChatBeforeCaptureAudioSentDelegate2::FDelegate& Delegate) override;`
- L147 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeCaptureAudioSentDelegate(FDelegateHandle Handle) override;`
- L148 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) override;`
- L149 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(FDelegateHandle Handle) override;`
- L150 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) override;`
- L151 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(FDelegateHandle Handle) override;`
- L152 _public prototype_ `virtual FString InsecureGetLoginToken(const FString& PlayerName) override;`
- L153 _public prototype_ `virtual FString InsecureGetJoinToken(const FString& ChannelName, EVoiceChatChannelType ChannelType, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) override;`
- L156 _public function_ `IEOSPlatformHandlePtr GetPlatformHandle() const`
- L157 _public function_ `EOS_HRTC GetRtcInterface() const`
- L158 _public function_ `EOS_HLobby GetLobbyInterface() const`
- L161 _protected function_ `virtual void PostInitialize()`
- L162 _protected function_ `virtual void PreUninitialize()`
- L197 _protected member_ `FInitSession InitSession;`
- L199 _protected prototype_ `void BindInitCallbacks();`
- L200 _protected prototype_ `void UnbindInitCallbacks();`
- L201 _protected prototype_ `static void EOS_CALL OnAudioDevicesChangedStatic(const EOS_RTCAudio_AudioDevicesChangedCallbackInfo* CallbackInfo);`
- L202 _protected prototype_ `void OnAudioDevicesChanged();`
- L204 _protected prototype_ `void OnConfigSectionsChanged(const FString& IniFilename, const TSet<FString>& SectionNames);`
- L205 _protected prototype_ `void LoadConfig();`
- L215 _protected member_ `EConnectionState ConnectionState = EConnectionState::Disconnected;`
- L218 _protected member_ `FOnVoiceChatConnectedDelegate OnVoiceChatConnectedDelegate;` — IVoiceChat Delegates
- L219 _protected member_ `FOnVoiceChatDisconnectedDelegate OnVoiceChatDisconnectedDelegate;`
- L220 _protected member_ `FOnVoiceChatReconnectedDelegate OnVoiceChatReconnectedDelegate;`
- L222 _protected member_ `FOnVoiceChatAvailableAudioDevicesChangedDelegate OnVoiceChatAvailableAudioDevicesChangedDelegate;` — IVoiceChatUser Delegates
- L224 _protected member_ `TArray<FEOSVoiceChatUserRef> VoiceChatUsers;`
- L225 _protected member_ `TArray<FEOSVoiceChatUserRef> ReleasedVoiceChatUsers;`
- L226 _protected prototype_ `void ScheduleReleaseUser(IVoiceChatUser* User);`
- L228 _protected prototype_ `FEOSVoiceChatUser& GetVoiceChatUser();`
- L229 _protected prototype_ `FEOSVoiceChatUser& GetVoiceChatUser() const;`
- L230 _protected member_ `FEOSVoiceChatUser* SingleUserVoiceChatUser = nullptr;`
- L233 _protected prototype_ `bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L235 _protected member_ `TArray<IVoiceChatUser*> UsersCreatedByConsoleCommand;`
- L237 _protected member_ `IEOSSDKManager& SDKManager;`
- L238 _protected member_ `IEOSPlatformHandlePtr EosPlatformHandle = nullptr;`
- L239 _protected prototype_ `virtual IEOSPlatformHandlePtr EOSPlatformCreate(EOS_Platform_Options& PlatformOptions);`
- L241 _protected member_ `TOptional<FString> OverridePlatformConfigName;` — Override for platform config name, set via SetPlatformConfigName(). If set, Initialize() uses this instead of reading from config file
- L244 _protected member_ `uint8 InitializationPath = 0;`
- L247 _protected member_ `static int64 StaticInstanceIdCount;`
- L248 _protected member_ `int64 InstanceId = StaticInstanceIdCount++;`

#### enum `FEOSVoiceChat::EInitializationState`  
`enum class EInitializationState`  
_L168-174_
- desc: When initialized, contains the state for this initialize session. Reset during Uninitialize.
- L170 _public enumerator_ `Uninitialized`
- L171 _public enumerator_ `Uninitializing`
- L172 _public enumerator_ `Initializing`
- L173 _public enumerator_ `Initialized`

#### struct `FEOSVoiceChat::FInitSession`  
`struct FInitSession`  
_L176-196_
- L178 _public prototype_ `FInitSession();`
- L184 _public prototype_ `void Reset();` — reverts fields to their default state
- L186 _public member_ `EInitializationState State = EInitializationState::Uninitialized;`
- L188 _public member_ `TArray<FOnVoiceChatUninitializeCompleteDelegate> UninitializeCompleteDelegates;`
- L190 _public member_ `EOS_HRTC EosRtcInterface = nullptr;`
- L191 _public member_ `EOS_HLobby EosLobbyInterface = nullptr;`
- L193 _public member_ `EOS_NotificationId OnAudioDevicesChangedNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L195 _public member_ `TSharedRef<FEOSAudioDevicePool> EosAudioDevicePool;`

#### enum `FEOSVoiceChat::EConnectionState`  
`enum class EConnectionState`  
_L208-214_
- desc: The current state of the connection.
- L210 _public enumerator_ `Disconnected`
- L211 _public enumerator_ `Disconnecting`
- L212 _public enumerator_ `Connecting`
- L213 _public enumerator_ `Connected`

#### Free symbols / members of external scopes

- L8 _macro_ `#define WITH_EOSVOICECHAT WITH_EOS_RTC`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioInputDeviceStatusChanged, FString , EOS_ERTCAudioInputStatus );` — Delegate called when the status of the audio device has changed.
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatPlayerAddedMetadataDelegate, const FString& , const FString& , const FString& , const TArray<FVoiceChatMetadataItem>& );` — Delegate called when ParticipantMetadata is included in the player joined event
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnAudioStatusChanged, const FString& , const FString& , const FString& , const EOS_ERTCAudioStatus );` — Delegate called when the audio status has changed
- L44 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle, ESPMode::ThreadSafe>;`
- L46 _typedef_ `typedef TSharedPtr<class FEOSVoiceChat, ESPMode::ThreadSafe> FEOSVoiceChatPtr;`
- L47 _typedef_ `typedef TSharedPtr<class FEOSVoiceChatUser, ESPMode::ThreadSafe> FEOSVoiceChatUserPtr;`
- L48 _typedef_ `typedef TSharedRef<class FEOSVoiceChatUser, ESPMode::ThreadSafe> FEOSVoiceChatUserRef;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Public/EOSVoiceChatFactory.h` (Public)


#### class `FEOSVoiceChatFactory`  
`class FEOSVoiceChatFactory : public IModularFeature, public FSelfRegisteringExec`  
_L17-51_
- inherits: `IModularFeature,FSelfRegisteringExec`
- L20 _public function_ `static FEOSVoiceChatFactory* Get()`
- L29 _public function_ `static FName GetModularFeatureName()`
- L35 _public prototype_ `virtual ~FEOSVoiceChatFactory() = default;`
- L38 _public prototype_ `IVoiceChatPtr CreateInstance();` — Create an instance with its own EOS platform.
- L40 _public prototype_ `IVoiceChatPtr CreateInstanceWithPlatform(const IEOSPlatformHandlePtr& PlatformHandle);` — Create an instance sharing an existing EOS platform. Used to enable interaction with e.g. lobby voice channels via an IVoiceChat interface.
- L42 _public prototype_ `IVoiceChatPtr CreateInstanceWithPlatformConfig(const FString& PlatformConfigName);` — Create an instance using a specific named platform config. Used to enable interaction with e.g. lobby voice channels via an IVoiceChat interface.
- L45 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L50 _private member_ `TArray<IVoiceChatWeakPtr> Instances;`

#### Free symbols / members of external scopes

- L14 _typedef_ `using IVoiceChatPtr = TSharedPtr<class IVoiceChat, ESPMode::ThreadSafe>;`
- L15 _typedef_ `using IVoiceChatWeakPtr = TWeakPtr<class IVoiceChat, ESPMode::ThreadSafe>;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Public/EOSVoiceChatLog.h` (Public)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSVoiceChat, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEOSVoiceChat, Log, All);`
- L13 _macro_ `#define EOSVOICECHATUSER_LOG(EOSVoiceChatLogLevel, EOSVoiceChatFormatStr, ...) \`
- L18 _macro_ `#define EOSVOICECHATUSER_CLOG(Condition, EOSVoiceChatLogLevel, EOSVoiceChatFormatStr, ...) \`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Public/EOSVoiceChatTypes.h` (Public)


#### struct `FEOSVoiceChatChannelCredentials`  
`struct FEOSVoiceChatChannelCredentials : public FJsonSerializable`  
_L10-22_
- inherits: `FJsonSerializable`
- desc: Passed in the ChannelCredentials parameter of EOSVoiceChatUser::JoinChannel calls.
- L13 _public member_ `FString OverrideUserId;`
- L14 _public member_ `FString ClientBaseUrl;`
- L15 _public member_ `FString ParticipantToken;`

### `Plugins/Online/VoiceChat/EOSVoiceChat/Source/EOSVoiceChat/Public/EOSVoiceChatUser.h` (Public)


#### class `FEOSVoiceChatUser`  
`class FEOSVoiceChatUser : public TSharedFromThis<FEOSVoiceChatUser, ESPMode::ThreadSafe>, public IVoiceChatUser`  
_L14-378_
- inherits: `TSharedFromThis<FEOSVoiceChatUser,ESPMode::ThreadSafe>,IVoiceChatUser`
- L17 _public prototype_ `FEOSVoiceChatUser(FEOSVoiceChat& InEOSVoiceChat);`
- L18 _public prototype_ `virtual ~FEOSVoiceChatUser();`
- L20 _public prototype_ `FEOSVoiceChatUser(const FEOSVoiceChatUser&) = delete;`
- L23 _public prototype_ `virtual void SetSetting(const FString& Name, const FString& Value) override;`
- L24 _public prototype_ `virtual FString GetSetting(const FString& Name) override;`
- L25 _public prototype_ `virtual void SetAudioInputVolume(float Volume) override;`
- L26 _public prototype_ `virtual void SetAudioOutputVolume(float Volume) override;`
- L27 _public prototype_ `virtual float GetAudioInputVolume() const override;`
- L28 _public prototype_ `virtual float GetAudioOutputVolume() const override;`
- L29 _public prototype_ `virtual void SetAudioInputDeviceMuted(bool bIsMuted) override;`
- L30 _public prototype_ `virtual void SetAudioOutputDeviceMuted(bool bIsMuted) override;`
- L31 _public prototype_ `virtual bool GetAudioInputDeviceMuted() const override;`
- L32 _public prototype_ `virtual bool GetAudioOutputDeviceMuted() const override;`
- L33 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableInputDeviceInfos() const override;`
- L34 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableOutputDeviceInfos() const override;`
- L35 _public function_ `virtual FOnVoiceChatAvailableAudioDevicesChangedDelegate& OnVoiceChatAvailableAudioDevicesChanged() override`
- L36 _public prototype_ `virtual void SetInputDeviceId(const FString& InputDeviceId) override;`
- L37 _public prototype_ `virtual void SetOutputDeviceId(const FString& OutputDeviceId) override;`
- L38 _public prototype_ `virtual FVoiceChatDeviceInfo GetInputDeviceInfo() const override;`
- L39 _public prototype_ `virtual FVoiceChatDeviceInfo GetOutputDeviceInfo() const override;`
- L40 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultInputDeviceInfo() const override;`
- L41 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultOutputDeviceInfo() const override;`
- L42 _public prototype_ `virtual void Login(FPlatformUserId PlatformId, const FString& PlayerName, const FString& Credentials, const FOnVoiceChatLoginCompleteDelegate& Delegate) override;`
- L43 _public prototype_ `virtual void Logout(const FOnVoiceChatLogoutCompleteDelegate& Delegate) override;`
- L44 _public prototype_ `virtual bool IsLoggingIn() const override;`
- L45 _public prototype_ `virtual bool IsLoggedIn() const override;`
- L46 _public function_ `virtual FOnVoiceChatLoggedInDelegate& OnVoiceChatLoggedIn() override`
- L47 _public function_ `virtual FOnVoiceChatLoggedOutDelegate& OnVoiceChatLoggedOut() override`
- L48 _public prototype_ `virtual FString GetLoggedInPlayerName() const override;`
- L49 _public prototype_ `virtual void BlockPlayers(const TArray<FString>& PlayerNames) override;`
- L50 _public prototype_ `virtual void UnblockPlayers(const TArray<FString>& PlayerNames) override;`
- L51 _public prototype_ `virtual void JoinChannel(const FString& ChannelName, const FString& ChannelCredentials, EVoiceChatChannelType ChannelType, const FOnVoiceChatChannelJoinCompleteDelegate& Delegate, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) override;`
- L52 _public prototype_ `virtual void LeaveChannel(const FString& Channel, const FOnVoiceChatChannelLeaveCompleteDelegate& Delegate) override;`
- L53 _public function_ `virtual FOnVoiceChatChannelJoinedDelegate& OnVoiceChatChannelJoined() override`
- L54 _public function_ `virtual FOnVoiceChatChannelExitedDelegate& OnVoiceChatChannelExited() override`
- L56 _public function_ `virtual FOnVoiceChatCallStatsUpdatedDelegate& OnVoiceChatCallStatsUpdated() override`
- L58 _public function_ `virtual FOnVoiceChatCallStatsUpdatedDelegate2& OnVoiceChatCallStatsUpdated2() override`
- L59 _public function_ `virtual TOptional<FVoiceChatCallStats> GetChannelCallStats(const FString& ChannelName) const override`
- L60 _public prototype_ `virtual void Set3DPosition(const FString& ChannelName, const FVector& Position) override;`
- L61 _public prototype_ `virtual TArray<FString> GetChannels() const override;`
- L62 _public prototype_ `virtual TArray<FString> GetPlayersInChannel(const FString& ChannelName) const override;`
- L63 _public prototype_ `virtual EVoiceChatChannelType GetChannelType(const FString& ChannelName) const override;`
- L64 _public function_ `virtual FOnVoiceChatPlayerAddedDelegate& OnVoiceChatPlayerAdded() override`
- L65 _public function_ `virtual FOnVoiceChatPlayerRemovedDelegate& OnVoiceChatPlayerRemoved() override`
- L66 _public prototype_ `virtual bool IsPlayerTalking(const FString& PlayerName) const override;`
- L67 _public function_ `virtual FOnVoiceChatPlayerTalkingUpdatedDelegate& OnVoiceChatPlayerTalkingUpdated() override`
- L68 _public prototype_ `virtual void SetPlayerMuted(const FString& PlayerName, bool bAudioMuted) override;`
- L69 _public prototype_ `virtual bool IsPlayerMuted(const FString& PlayerName) const override;`
- L70 _public prototype_ `virtual void SetChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName, bool bAudioMuted) override;`
- L71 _public prototype_ `virtual bool IsChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName) const override;`
- L72 _public function_ `virtual FOnVoiceChatPlayerMuteUpdatedDelegate& OnVoiceChatPlayerMuteUpdated() override`
- L73 _public prototype_ `virtual void SetPlayerVolume(const FString& PlayerName, float Volume) override;`
- L74 _public prototype_ `virtual float GetPlayerVolume(const FString& PlayerName) const override;`
- L75 _public function_ `virtual FOnVoiceChatPlayerVolumeUpdatedDelegate& OnVoiceChatPlayerVolumeUpdated() override`
- L76 _public prototype_ `virtual void TransmitToAllChannels() override;`
- L77 _public prototype_ `virtual void TransmitToNoChannels() override;`
- L78 _public prototype_ `virtual void TransmitToSpecificChannels(const TSet<FString>& ChannelNames) override;`
- L79 _public prototype_ `virtual EVoiceChatTransmitMode GetTransmitMode() const override;`
- L80 _public prototype_ `virtual TSet<FString> GetTransmitChannels() const override;`
- L81 _public prototype_ `virtual FDelegateHandle StartRecording(const FOnVoiceChatRecordSamplesAvailableDelegate::FDelegate& Delegate) override;`
- L82 _public prototype_ `virtual void StopRecording(FDelegateHandle Handle) override;`
- L83 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatAfterCaptureAudioReadDelegate(const FOnVoiceChatAfterCaptureAudioReadDelegate2::FDelegate& Delegate) override;`
- L84 _public prototype_ `virtual void UnregisterOnVoiceChatAfterCaptureAudioReadDelegate(FDelegateHandle Handle) override;`
- L85 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeCaptureAudioSentDelegate(const FOnVoiceChatBeforeCaptureAudioSentDelegate2::FDelegate& Delegate) override;`
- L86 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeCaptureAudioSentDelegate(FDelegateHandle Handle) override;`
- L87 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) override;`
- L88 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(FDelegateHandle Handle) override;`
- L89 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) override;`
- L90 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(FDelegateHandle Handle) override;`
- L91 _public prototype_ `virtual FString InsecureGetLoginToken(const FString& PlayerName) override;`
- L92 _public prototype_ `virtual FString InsecureGetJoinToken(const FString& ChannelName, EVoiceChatChannelType ChannelType, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) override;`
- L95 _public prototype_ `bool AddLobbyRoom(const FString& LobbyId);`
- L96 _public prototype_ `bool RemoveLobbyRoom(const FString& LobbyId);`
- L250 _protected member_ `FLoginSession LoginSession;`
- L259 _protected member_ `FAudioOutputOptions AudioOutputOptions;`
- L269 _protected member_ `FAudioInputOptions AudioInputOptions;`
- L276 _protected member_ `FTransmitState TransmitState;`
- L279 _protected member_ `FOnVoiceChatLoggedInDelegate OnVoiceChatLoggedInDelegate;` — IVoiceChatUser Delegates
- L280 _protected member_ `FOnVoiceChatLoggedOutDelegate OnVoiceChatLoggedOutDelegate;`
- L281 _protected member_ `FOnVoiceChatChannelJoinedDelegate OnVoiceChatChannelJoinedDelegate;`
- L282 _protected member_ `FOnVoiceChatChannelExitedDelegate OnVoiceChatChannelExitedDelegate;`
- L283 _protected member_ `FOnVoiceChatPlayerAddedDelegate OnVoiceChatPlayerAddedDelegate;`
- L284 _protected member_ `FOnVoiceChatPlayerTalkingUpdatedDelegate OnVoiceChatPlayerTalkingUpdatedDelegate;`
- L285 _protected member_ `FOnVoiceChatPlayerMuteUpdatedDelegate OnVoiceChatPlayerMuteUpdatedDelegate;`
- L286 _protected member_ `FOnVoiceChatPlayerVolumeUpdatedDelegate OnVoiceChatPlayerVolumeUpdatedDelegate;`
- L287 _protected member_ `FOnVoiceChatPlayerRemovedDelegate OnVoiceChatPlayerRemovedDelegate;`
- L288 _protected member_ `FOnVoiceChatCallStatsUpdatedDelegate OnVoiceChatCallStatsUpdatedDelegate;`
- L289 _protected member_ `FOnVoiceChatCallStatsUpdatedDelegate2 OnVoiceChatCallStatsUpdatedDelegate2;`
- L292 _protected member_ `FCriticalSection AudioRecordLock;`
- L293 _protected member_ `FOnVoiceChatRecordSamplesAvailableDelegate OnVoiceChatRecordSamplesAvailableDelegate;`
- L296 _protected member_ `FCriticalSection BeforeCaptureAudioSentLock;` — Note BeforeCaptureAudioSentLock is used for CaptureAudioRead too as they fire together
- L297 _protected member_ `FOnVoiceChatAfterCaptureAudioReadDelegate2 OnVoiceChatAfterCaptureAudioReadDelegate;`
- L298 _protected member_ `FOnVoiceChatBeforeCaptureAudioSentDelegate2 OnVoiceChatBeforeCaptureAudioSentDelegate;`
- L300 _protected member_ `FCriticalSection BeforeRecvMixedAudioRenderedLock;`
- L301 _protected member_ `FOnVoiceChatBeforeRecvAudioRenderedDelegate OnVoiceChatBeforeRecvMixedAudioRenderedDelegate;`
- L302 _protected member_ `FCriticalSection BeforeRecvUnmixedAudioRenderedLock;`
- L303 _protected member_ `FOnVoiceChatBeforeRecvAudioRenderedDelegate OnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate;`
- L306 _protected member_ `FEOSVoiceChat& EOSVoiceChat;`
- L308 _protected member_ `bool bFakeAudioInput = false;`
- L309 _protected member_ `bool bInDestructor = false;`
- L312 _protected prototype_ `bool IsInitialized();` — Helper methods
- L313 _protected prototype_ `bool IsConnected();`
- L314 _protected function_ `EOS_HRTC GetRtcInterface() const`
- L315 _protected function_ `EOS_HLobby GetLobbyInterface() const`
- L316 _protected prototype_ `FGlobalParticipant& GetGlobalParticipant(const FString& PlayerName);`
- L317 _protected prototype_ `const FGlobalParticipant& GetGlobalParticipant(const FString& PlayerName) const;`
- L318 _protected prototype_ `FChannelSession& GetChannelSession(const FString& ChannelName);`
- L319 _protected prototype_ `const FChannelSession& GetChannelSession(const FString& ChannelName) const;`
- L320 _protected prototype_ `void RemoveChannelSession(const FString& ChannelName);`
- L321 _protected prototype_ `void ApplyAudioInputOptions();`
- L322 _protected prototype_ `void ApplyAudioOutputOptions();`
- L323 _protected prototype_ `void ApplyPlayerBlock(const FGlobalParticipant& GlobalParticipant, const FChannelSession& ChannelSession, FChannelParticipant& ChannelParticipant);`
- L324 _protected prototype_ `void ApplyReceivingOptions(const FChannelSession& ChannelSession);`
- L325 _protected prototype_ `void ApplyPlayerReceivingOptions(const FString& PlayerName);`
- L326 _protected prototype_ `void ApplyPlayerReceivingOptions(const FGlobalParticipant& GlobalParticipant, const FChannelSession& ChannelSession, FChannelParticipant& ChannelParticipant);`
- L327 _protected prototype_ `void ApplySendingOptions();`
- L328 _protected prototype_ `void ApplySendingOptions(FChannelSession& ChannelSession);`
- L329 _protected prototype_ `void BindLoginCallbacks();`
- L330 _protected prototype_ `void UnbindLoginCallbacks();`
- L331 _protected prototype_ `void BindChannelCallbacks(FChannelSession& ChannelSession);`
- L332 _protected prototype_ `void UnbindChannelCallbacks(FChannelSession& ChannelSession);`
- L333 _protected prototype_ `void LeaveChannelInternal(const FString& ChannelName, const FOnVoiceChatChannelLeaveCompleteDelegate& Delegate);`
- L334 _protected prototype_ `void LogoutInternal(const FOnVoiceChatLogoutCompleteDelegate& Delegate);`
- L335 _protected prototype_ `void ClearLoginSession();`
- L337 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUserRtcRegisterUserCompleteDelegate, const EOS_EResult );`
- L338 _protected prototype_ `void RtcRegisterUser(const FString& UserId, const FOnVoiceChatUserRtcRegisterUserCompleteDelegate& Delegate);`
- L339 _protected prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUserRtcUnregisterUserCompleteDelegate, const EOS_EResult );`
- L340 _protected prototype_ `void RtcUnregisterUser(const FString& UserId, const FOnVoiceChatUserRtcUnregisterUserCompleteDelegate& Delegate);`
- L342 _protected prototype_ `void SetHardwareAECEnabled(bool bEnabled);`
- L345 _protected prototype_ `static void EOS_CALL OnJoinRoomStatic(const EOS_RTC_JoinRoomCallbackInfo* CallbackInfo);` — EOS operation callbacks
- L346 _protected prototype_ `void OnJoinRoom(const EOS_RTC_JoinRoomCallbackInfo* CallbackInfo);`
- L347 _protected prototype_ `static void EOS_CALL OnLeaveRoomStatic(const EOS_RTC_LeaveRoomCallbackInfo* CallbackInfo);`
- L348 _protected prototype_ `void OnLeaveRoom(const EOS_RTC_LeaveRoomCallbackInfo* CallbackInfo);`
- L349 _protected prototype_ `static void EOS_CALL OnBlockParticipantStatic(const EOS_RTC_BlockParticipantCallbackInfo* CallbackInfo);`
- L350 _protected prototype_ `void OnBlockParticipant(const EOS_RTC_BlockParticipantCallbackInfo* CallbackInfo);`
- L351 _protected prototype_ `static void EOS_CALL OnUpdateParticipantVolumeStatic(const EOS_RTCAudio_UpdateParticipantVolumeCallbackInfo* CallbackInfo);`
- L352 _protected prototype_ `void OnUpdateParticipantVolume(const EOS_RTCAudio_UpdateParticipantVolumeCallbackInfo* CallbackInfo);`
- L353 _protected prototype_ `static void EOS_CALL OnUpdateReceivingAudioStatic(const EOS_RTCAudio_UpdateReceivingCallbackInfo* CallbackInfo);`
- L354 _protected prototype_ `void OnUpdateReceivingAudio(const EOS_RTCAudio_UpdateReceivingCallbackInfo* CallbackInfo);`
- L355 _protected prototype_ `void OnUpdateSendingAudio(const EOS_RTCAudio_UpdateSendingCallbackInfo* CallbackInfo);`
- L358 _protected prototype_ `static void EOS_CALL OnChannelDisconnectedStatic(const EOS_RTC_DisconnectedCallbackInfo* CallbackInfo);` — EOS notification callbacks
- L359 _protected prototype_ `void OnChannelDisconnected(const EOS_RTC_DisconnectedCallbackInfo* CallbackInfo);`
- L360 _protected prototype_ `static void EOS_CALL OnLobbyChannelConnectionChangedStatic(const EOS_Lobby_RTCRoomConnectionChangedCallbackInfo* CallbackInfo);`
- L361 _protected prototype_ `void OnLobbyChannelConnectionChanged(const EOS_Lobby_RTCRoomConnectionChangedCallbackInfo* CallbackInfo);`
- L362 _protected prototype_ `static void EOS_CALL OnChannelParticipantStatusChangedStatic(const EOS_RTC_ParticipantStatusChangedCallbackInfo* CallbackInfo);`
- L363 _protected prototype_ `void OnChannelParticipantStatusChanged(const EOS_RTC_ParticipantStatusChangedCallbackInfo* CallbackInfo);`
- L364 _protected prototype_ `static void EOS_CALL OnChannelParticipantAudioUpdatedStatic(const EOS_RTCAudio_ParticipantUpdatedCallbackInfo* CallbackInfo);`
- L365 _protected prototype_ `void OnChannelParticipantAudioUpdated(const EOS_RTCAudio_ParticipantUpdatedCallbackInfo* CallbackInfo);`
- L366 _protected prototype_ `void OnChannelAudioBeforeSend(const EOS_RTCAudio_AudioBeforeSendCallbackInfo* CallbackInfo);`
- L367 _protected prototype_ `static void EOS_CALL OnChannelMixedAudioBeforeRenderStatic(const EOS_RTCAudio_AudioBeforeRenderCallbackInfo* CallbackInfo);`
- L368 _protected prototype_ `void OnChannelMixedAudioBeforeRender(const EOS_RTCAudio_AudioBeforeRenderCallbackInfo* CallbackInfo);`
- L369 _protected prototype_ `static void EOS_CALL OnChannelUnmixedAudioBeforeRenderStatic(const EOS_RTCAudio_AudioBeforeRenderCallbackInfo* CallbackInfo);`
- L370 _protected prototype_ `void OnChannelUnmixedAudioBeforeRender(const EOS_RTCAudio_AudioBeforeRenderCallbackInfo* CallbackInfo);`
- L371 _protected prototype_ `static void EOS_CALL OnChannelAudioInputStateStatic(const EOS_RTCAudio_AudioInputStateCallbackInfo* CallbackInfo);`
- L372 _protected prototype_ `virtual void OnChannelAudioInputState(const EOS_RTCAudio_AudioInputStateCallbackInfo* CallbackInfo);`
- L374 _protected prototype_ `bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`

#### struct `FEOSVoiceChatUser::FGlobalParticipant`  
`struct FGlobalParticipant`  
_L102-114_
- desc: Global state for a given user.
- L105 _public member_ `FString PlayerName;` — The player id
- L107 _public member_ `bool bTalking = false;` — Current talking state (we cache this on the global participant in addition to the channel one)
- L109 _public member_ `bool bBlocked = false;` — Desired block state
- L111 _public member_ `bool bAudioMuted = false;` — Desired mute state
- L113 _public member_ `float Volume = 1.f;` — Desired Volume

#### struct `FEOSVoiceChatUser::FChannelParticipant`  
`struct FChannelParticipant`  
_L123-135_
- desc: Current state of a user in a channel
- L126 _public member_ `FString PlayerName;` — The player id
- L128 _public member_ `bool bTalking = false;` — Current talking state
- L130 _public member_ `bool bAudioDisabled = false;` — Combined audio mute and isListening state
- L132 _public member_ `bool bMutedInChannel = false;` — Desired channel mute state
- L134 _public member_ `TOptional<EOS_ERTCAudioStatus> AudioStatus;` — Current audio status

#### enum `FEOSVoiceChatUser::EChannelJoinState`  
`enum class EChannelJoinState`  
_L137-143_
- L139 _public enumerator_ `NotJoined`
- L140 _public enumerator_ `Leaving`
- L141 _public enumerator_ `Joining`
- L142 _public enumerator_ `Joined`

#### struct `FEOSVoiceChatUser::FSendingState`  
`struct FSendingState`  
_L146-150_
- desc: Sending options passed to/received from UpdateSending and its completion callback
- L149 _public member_ `bool bAudioEnabled = true;` — Microphone input

#### struct `FEOSVoiceChatUser::FChannelSession`  
`struct FChannelSession`  
_L153-202_
- desc: Representation of a particular channel
- L155 _public prototype_ `FChannelSession() = default;`
- L156 _public prototype_ `FChannelSession(FChannelSession&&) = default;`
- L157 _public prototype_ `~FChannelSession();`
- L159 _public prototype_ `FChannelSession(const FChannelSession&) = delete;`
- L161 _public prototype_ `bool IsLocalUser(const FChannelParticipant& Participant);`
- L162 _public prototype_ `bool IsLobbySession() const;`
- L165 _public member_ `FString ChannelName;` — The channel name
- L167 _public member_ `EVoiceChatChannelType ChannelType = EVoiceChatChannelType::NonPositional;` — The channel type
- L169 _public member_ `EChannelJoinState JoinState = EChannelJoinState::NotJoined;` — Current join state of the channel
- L171 _public member_ `FString PlayerName;` — Name of the local player in the channel (can differ from LoginSession.PlayerName if an override ID was provided to JoinChannel)
- L173 _public member_ `TMap<FString, FChannelParticipant> Participants;` — Current participants in the channel, and the current blocked/muted state
- L175 _public member_ `bool bIsNotListening = false;` — Did the user toggle "off" this channel
- L178 _public member_ `FString LobbyId;` — Lobby Id, only relevant for lobby rooms
- L180 _public member_ `bool bLobbyChannelConnected = false;` — Lobby channel connection state, only relevant for lobby rooms
- L183 _public member_ `FSendingState DesiredSendingState;` — Desired sending state
- L185 _public member_ `FSendingState ActiveSendingState;` — Active sending state
- L188 _public member_ `FOnVoiceChatChannelJoinCompleteDelegate JoinDelegate;` — Set by JoinChannel and fired on success/failure
- L190 _public member_ `TArray<FOnVoiceChatChannelLeaveCompleteDelegate> LeaveDelegates;` — Set by LeaveChannel and fired on success/failure
- L193 _public member_ `EOS_NotificationId OnChannelDisconnectedNotificationId = EOS_INVALID_NOTIFICATIONID;` — Handles for channel callbacks
- L194 _public member_ `EOS_NotificationId OnParticipantStatusChangedNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L195 _public member_ `EOS_NotificationId OnParticipantAudioUpdatedNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L196 _public member_ `EOS_NotificationId OnAudioBeforeSendNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L197 _public member_ `EOS_NotificationId OnMixedAudioBeforeRenderNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L198 _public member_ `EOS_NotificationId OnUnmixedAudioBeforeRenderNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L199 _public member_ `EOS_NotificationId OnAudioInputStateNotificationId = EOS_INVALID_NOTIFICATIONID;`
- L201 _public member_ `TUniquePtr<class FCallbackBase> AudioBeforeSendCallback;`

#### enum `FEOSVoiceChatUser::ELoginState`  
`enum class ELoginState`  
_L204-210_
- L206 _public enumerator_ `LoggedOut`
- L207 _public enumerator_ `LoggingOut`
- L208 _public enumerator_ `LoggingIn`
- L209 _public enumerator_ `LoggedIn`

#### struct `FEOSVoiceChatUser::FLoginSession`  
`struct FLoginSession`  
_L213-249_
- desc: When logged in, contains the state for the current login session. Reset by Logout
- L215 _public prototype_ `FLoginSession() = default;`
- L216 _public prototype_ `FLoginSession& operator=(FLoginSession&&) = default;`
- L217 _public prototype_ `~FLoginSession();`
- L219 _public prototype_ `FLoginSession(const FLoginSession&) = delete;`
- L222 _public member_ `FPlatformUserId PlatformId = PLATFORMUSERID_NONE;` — The numeric platform id for the local user
- L224 _public member_ `FString PlayerName;` — Name of the local player
- L226 _public member_ `EOS_ProductUserId LocalUserProductUserId;` — EpicAccountId of the local player, converted from PlayerName
- L228 _public member_ `ELoginState State = ELoginState::LoggedOut;` — Current login state
- L230 _public member_ `TMap<FString, FChannelSession> ChannelSessions;` — Set of channels the user is interacting with
- L232 _public member_ `TMap<FString, FGlobalParticipant> Participants;` — Contains participants from all channels and the desired blocked/muted state
- L235 _public member_ `TMap<FString, FString> LobbyIdToChannelName;` — Maps LobbyId to RTC ChannelName, only relevant when VoiceChatFlowMode == Lobby
- L245 _public member_ `TOptional<FLogoutState> LogoutState;`
- L248 _public member_ `EOS_NotificationId OnLobbyChannelConnectionChangedNotificationId = EOS_INVALID_NOTIFICATIONID;` — Handles for callbacks

#### struct `FEOSVoiceChatUser::FLoginSession::FLogoutState`  
`struct FLogoutState`  
_L238-244_
- desc: State while handling a logout request
- L240 _public member_ `FVoiceChatResult Result = FVoiceChatResult::CreateSuccess();`
- L241 _public member_ `TSet<FString> ChannelNamesExpectingCallback;`
- L243 _public member_ `TArray<FOnVoiceChatLogoutCompleteDelegate> CompletionDelegates;` — Delegates to fire when Logout completes

#### struct `FEOSVoiceChatUser::FAudioOutputOptions`  
`struct FAudioOutputOptions`  
_L253-258_
- desc: Audio Output state
- L255 _public member_ `bool bMuted = false;`
- L256 _public member_ `float Volume = 1.0f;`
- L257 _public member_ `TOptional<FVoiceChatDeviceInfo> SpecificDeviceInfo;`

#### struct `FEOSVoiceChatUser::FAudioInputOptions`  
`struct FAudioInputOptions`  
_L262-268_
- desc: Audio Input state
- L264 _public member_ `bool bMuted = false;`
- L265 _public member_ `bool bPlatformAEC = false;`
- L266 _public member_ `float Volume = 1.0f;`
- L267 _public member_ `TOptional<FVoiceChatDeviceInfo> SpecificDeviceInfo;`

#### struct `FEOSVoiceChatUser::FTransmitState`  
`struct FTransmitState`  
_L271-275_
- L273 _public member_ `EVoiceChatTransmitMode Mode = EVoiceChatTransmitMode::All;`
- L274 _public member_ `TSet<FString> SpecificChannels;`

#### Free symbols / members of external scopes

- L337 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUserRtcRegisterUserCompleteDelegate, const EOS_EResult );`
- L339 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUserRtcUnregisterUserCompleteDelegate, const EOS_EResult );`
