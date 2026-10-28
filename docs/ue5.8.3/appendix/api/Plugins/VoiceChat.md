# Plugins / VoiceChat

- module root: `Plugins/Online/VoiceChat/VoiceChat/Source`
- headers: 3; symbols: 255
- symbol kinds: class=2, delegate=29, enum=4, enumerator=25, function=57, macro=1, member=16, namespace=2, prototype=115, struct=4
- PublicDependencyModuleNames: Core

### `Plugins/Online/VoiceChat/VoiceChat/Source/Public/VoiceChat.h` (Public)


#### enum `EVoiceChatChannelType`  
`enum class EVoiceChatChannelType`  
_L11-19_
- L14 _public enumerator_ `NonPositional` — Non positional/2d audio channel
- L16 _public enumerator_ `Positional` — Positional/3d audio channel
- L18 _public enumerator_ `Echo` — Echo channel. Will only ever have one player and will echo anything you say

#### enum `EVoiceChatAttenuationModel`  
`enum class EVoiceChatAttenuationModel`  
_L23-33_
- L26 _public enumerator_ `None` — No attenuation is applied. The audio will drop to 0 at MaxDistance
- L28 _public enumerator_ `InverseByDistance` — The attenuation increases in inverse proportion to the distance. The Rolloff is the inverse of the slope of the attenuation curve.
- L30 _public enumerator_ `LinearByDistance` — The attenuation increases in linear proportion to the distance. The Rolloff is the negative slope of the attenuation curve.
- L32 _public enumerator_ `ExponentialByDistance` — The attenuation increases in inverse proportion to the distance raised to the power of the Rolloff.

#### struct `FVoiceChatChannel3dProperties`  
`struct FVoiceChatChannel3dProperties`  
_L37-47_
- L40 _public member_ `EVoiceChatAttenuationModel AttenuationModel;` — The model used to determine how loud audio is at different distances
- L42 _public member_ `float MinDistance;` — The distance at which the sound will start to attenuate
- L44 _public member_ `float MaxDistance;` — The distance at which sound will no longer be audible
- L46 _public member_ `float Rolloff;` — How fast the sound attenuates with distance

#### enum `EVoiceChatTransmitMode`  
`enum class EVoiceChatTransmitMode`  
_L49-57_
- L52 _public enumerator_ `None` — Transmit to none of the channels you are in
- L54 _public enumerator_ `All` — Transmit to all of the channels you are in
- L56 _public enumerator_ `SpecificChannels` — Transmit to specific channel(s)

#### struct `FVoiceChatCallStats`  
`struct FVoiceChatCallStats`  
_L61-75_
- L64 _public member_ `double CallLength;` — Call length in seconds
- L66 _public member_ `double LatencyMinMeasuredSeconds;` — Minimum measured network latency in seconds. Zero if no measurements made
- L68 _public member_ `double LatencyMaxMeasuredSeconds;` — Maximum measured network latency in seconds. Zero if no measurements made
- L70 _public member_ `double LatencyAverageMeasuredSeconds;` — Average measured network latency in seconds. Zero if no measurements made
- L72 _public member_ `int PacketsNumTotal;` — Total number of packets, both received and lost
- L74 _public member_ `int PacketsNumLost;` — Total number of lost packets

#### struct `FVoiceChatDeviceInfo`  
`struct FVoiceChatDeviceInfo`  
_L77-88_
- L80 _public member_ `FString DisplayName;` — The display name for the device
- L82 _public member_ `FString Id;` — The unique id for the device
- L84 _public function_ `inline bool operator==(const FVoiceChatDeviceInfo& Other) const`
- L85 _public function_ `inline bool operator!=(const FVoiceChatDeviceInfo& Other) const`
- L87 _public function_ `FString ToDebugString() const`

#### class `IVoiceChatUser`  
`class IVoiceChatUser`  
_L128-699_
- L131 _public prototype_ `virtual ~IVoiceChatUser() = default;`
- L139 _public prototype_ `virtual void SetSetting(const FString& Name, const FString& Value) = 0;` — Set an implementation specific setting @param Name Name of the config setting to set @param Value Value for the setting
- L148 _public prototype_ `virtual FString GetSetting(const FString& Name) = 0;` — Get an implementation specific setting @param Name Name of the config setting to get @return Current value for the setting
- L155 _public prototype_ `virtual void SetAudioInputVolume(float Volume) = 0;` — Set record volume @param Volume Value between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L162 _public prototype_ `virtual void SetAudioOutputVolume(float Volume) = 0;` — Set playback volume @param Volume Value between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L169 _public prototype_ `virtual float GetAudioInputVolume() const = 0;` — Get volume of audio input device @return Audio input device volume between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L176 _public prototype_ `virtual float GetAudioOutputVolume() const = 0;` — Get volume of audio output device @return Audio output device volume between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L183 _public prototype_ `virtual void SetAudioInputDeviceMuted(bool bIsMuted) = 0;` — Mute or unmute the audio input device @param bIsMuted set to true to mute the device or false to unmute
- L190 _public prototype_ `virtual void SetAudioOutputDeviceMuted(bool bIsMuted) = 0;` — Mute or unmute the audio output device @param bIsMuted set to true to mute the device or false to unmute
- L197 _public prototype_ `virtual bool GetAudioInputDeviceMuted() const = 0;` — Is the input device muted? @return true if the input device is muted
- L204 _public prototype_ `virtual bool GetAudioOutputDeviceMuted() const = 0;` — Is the output device muted? @return true if the input device is muted
- L212 _public function_ `TArray<FString> GetAvailableInputDevices() const` — `UE_DEPRECATED(4.26, "GetAvailableInputDevices is deprecated. Please use GetAvailableInputDeviceInfos instead!")` — Get a list of available audio input device names @return Array of audio input devices names
- L227 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableInputDeviceInfos() const = 0;` — Get a list of available audio input devices @return Array of audio input devices
- L235 _public function_ `TArray<FString> GetAvailableOutputDevices() const` — `UE_DEPRECATED(4.26, "GetAvailableOutputDevices is deprecated. Please use GetAvailableOutputDeviceInfos instead!")` — Get a list of available audio output device names @return Array of audio output device names
- L250 _public prototype_ `virtual TArray<FVoiceChatDeviceInfo> GetAvailableOutputDeviceInfos() const = 0;` — Get a list of available audio output devices @return Array of audio output devices
- L255 _public prototype_ `virtual FOnVoiceChatAvailableAudioDevicesChangedDelegate& OnVoiceChatAvailableAudioDevicesChanged() = 0;` — Delegate broadcast whenever the available audio devices change. Any cached values from GetAvailableInputDevices or GetAvailableOutputDevices should be discarded and requeried
- L263 _public function_ `void SetInputDevice(const FString& InputDeviceName)` — `UE_DEPRECATED(4.26, "SetInputDevice is deprecated. Please use SetInputDeviceId instead!")` — Set the audio input device to use @param InputDevice String from GetAvailableInputDevice. If empty, will use the default input device
- L282 _public prototype_ `virtual void SetInputDeviceId(const FString& InputDeviceId) = 0;` — Set the audio input device to use @param InputDeviceId Device Id from GetAvailableInputDeviceInfos. If empty, will use the default input device
- L290 _public function_ `void SetOutputDevice(const FString& OutputDeviceName)` — `UE_DEPRECATED(4.26, "SetOutputDevice is deprecated. Please use SetOutputDeviceId instead!")` — Set the audio output device to use @param OutputDevice String from GetAvailableOutputDevice. If empty, will use the default output device
- L309 _public prototype_ `virtual void SetOutputDeviceId(const FString& OutputDeviceId) = 0;` — Set the audio output device to use @param OutputDeviceId Device Id from GetAvailableOutputDeviceInfos. If empty, will use the default output device
- L315 _public function_ `FString GetInputDevice() const` — `UE_DEPRECATED(4.26, "GetInputDevice is deprecated. Please use GetInputDeviceInfo instead!")` — Get the display name of the audio input device that is being used
- L323 _public prototype_ `virtual FVoiceChatDeviceInfo GetInputDeviceInfo() const = 0;` — Get the device info of the audio input device that is being used
- L329 _public function_ `FString GetOutputDevice() const` — `UE_DEPRECATED(4.26, "GetOutputDevice is deprecated. Please use GetOutputDeviceInfo instead!")` — Get the display name of the audio output device that is being used
- L337 _public prototype_ `virtual FVoiceChatDeviceInfo GetOutputDeviceInfo() const = 0;` — Get the device info of the audio output device that is being used
- L343 _public function_ `FString GetDefaultInputDevice() const` — `UE_DEPRECATED(4.26, "GetDefaultInputDevice is deprecated. Please use GetDefaultInputDeviceInfo instead!")` — Get the display name of the default audio input device
- L351 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultInputDeviceInfo() const = 0;` — Get the device info of the default audio input device
- L357 _public function_ `FString GetDefaultOutputDevice() const` — `UE_DEPRECATED(4.26, "GetDefaultOutputDevice is deprecated. Please use GetDefaultOutputDeviceInfo instead!")` — Get the display name of the default audio output device
- L365 _public prototype_ `virtual FVoiceChatDeviceInfo GetDefaultOutputDeviceInfo() const = 0;` — Get the device info of the default audio output device
- L375 _public prototype_ `virtual void Login(FPlatformUserId PlatformId, const FString& PlayerName, const FString& Credentials, const FOnVoiceChatLoginCompleteDelegate& Delegate) = 0;` — Login to the connected voice server @param PlatformId Platform user Id for the player logging in @param PlayerName Name of the account to login to @param Credentials Token or password @param Delegate delegate called once login completes
- L382 _public prototype_ `virtual void Logout(const FOnVoiceChatLogoutCompleteDelegate& Delegate) = 0;` — Logout from the connected voice server @param Delegate delegate called once logout completes
- L389 _public prototype_ `virtual bool IsLoggingIn() const = 0;` — Are we logging in? @return true if we are logging in to the voice server
- L396 _public prototype_ `virtual bool IsLoggedIn() const = 0;` — Are we logged in? @return true if we are logged in to the voice server
- L401 _public prototype_ `virtual FOnVoiceChatLoggedInDelegate& OnVoiceChatLoggedIn() = 0;` — Delegate triggered when we are logged in to voice chat
- L406 _public prototype_ `virtual FOnVoiceChatLoggedOutDelegate& OnVoiceChatLoggedOut() = 0;` — Delegate triggered when we are logged out from voice chat
- L413 _public prototype_ `virtual FString GetLoggedInPlayerName() const = 0;` — Get the player name used to log in @return player name used to log in
- L425 _public prototype_ `virtual void BlockPlayers(const TArray<FString>& PlayerNames) = 0;` — Block communication with players Adds the PlayerNames to the block list, muting them in all current and subsequently joined channels. A block for a player persists until either: - The local user logs out (e.g. by calling Logout/Disconnect/Uninitialize, or receiving equivalent events) - A subsequent call to UnblockPlayers is made with that PlayerName. @param PlayerNames List of players to block communication with
- L432 _public prototype_ `virtual void UnblockPlayers(const TArray<FString>& PlayerNames) = 0;` — Unblock communication with players @param PlayerNames List of players to unblock communication with
- L443 _public prototype_ `virtual void JoinChannel(const FString& ChannelName, const FString& ChannelCredentials, EVoiceChatChannelType ChannelType, const FOnVoiceChatChannelJoinCompleteDelegate& Delegate, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) = 0;` — Join a voice channel @param ChannelName Channel to join @param ChannelCredentials password or token @param ChannelType NonPositional, Positional, or Echo @param Delegate delegate called once join completes @param Channel3dProperties Optional parameter to set 3d/Positional channel properties
- L451 _public prototype_ `virtual void LeaveChannel(const FString& ChannelName, const FOnVoiceChatChannelLeaveCompleteDelegate& Delegate) = 0;` — Leave a voice channel @param ChannelName Channel to leave @param Delegate delegate called once leave completes
- L456 _public prototype_ `virtual FOnVoiceChatChannelJoinedDelegate& OnVoiceChatChannelJoined() = 0;` — Delegate triggered when we join a voice channel
- L461 _public prototype_ `virtual FOnVoiceChatChannelExitedDelegate& OnVoiceChatChannelExited() = 0;` — Delegate triggered when we leave a voice channel
- L467 _public prototype_ `virtual FOnVoiceChatCallStatsUpdatedDelegate& OnVoiceChatCallStatsUpdated() = 0;` — `UE_DEPRECATED(5.8, "Please use OnVoiceChatCallStatsUpdated2 which adds the ChannelName param")` — Delegate triggered when a call is ended, providing the stats for the call.
- L474 _public prototype_ `virtual FOnVoiceChatCallStatsUpdatedDelegate2& OnVoiceChatCallStatsUpdated2() = 0;` — Delegate triggered when a call ends on a specific channel, providing the cumulative stats for the call. Replaces OnVoiceChatCallStatsUpdated to allow per-channel routing in implementations that may have multiple concurrent voice rooms.
- L481 _public prototype_ `virtual TOptional<FVoiceChatCallStats> GetChannelCallStats(const FString& ChannelName) const = 0;` — Returns the current cumulative call-quality stats for the named channel, if available, or an empty optional if the channel is not currently joined or if the implementation does not produce stats. The values are running totals since the channel was joined.
- L489 _public prototype_ `virtual void Set3DPosition(const FString& ChannelName, const FVector& Position) = 0;` — Set the 3d position of the player @param ChannelName @param Position
- L496 _public prototype_ `virtual TArray<FString> GetChannels() const = 0;` — Get an array of channels the user is in @return Array of connected channel names
- L504 _public prototype_ `virtual TArray<FString> GetPlayersInChannel(const FString& ChannelName) const = 0;` — Get an array of players in a channel @param ChannelName Channel to get the list of players for @return Array of names of players in Channel
- L512 _public prototype_ `virtual EVoiceChatChannelType GetChannelType(const FString& ChannelName) const = 0;` — Get an array of players in a channel @param ChannelName Channel to get the type of @return Channel type
- L517 _public prototype_ `virtual FOnVoiceChatPlayerAddedDelegate& OnVoiceChatPlayerAdded() = 0;` — Delegate triggered when a player is added to a channel
- L522 _public prototype_ `virtual FOnVoiceChatPlayerRemovedDelegate& OnVoiceChatPlayerRemoved() = 0;` — Delegate triggered when a player is removed from a channel
- L528 _public prototype_ `virtual bool IsPlayerTalking(const FString& PlayerName) const = 0;` — @param PlayerName Player to get the talking state of @return true if player is talking
- L533 _public prototype_ `virtual FOnVoiceChatPlayerTalkingUpdatedDelegate& OnVoiceChatPlayerTalkingUpdated() = 0;` — Delegate triggered when a player's talking state is updated
- L541 _public prototype_ `virtual void SetPlayerMuted(const FString& PlayerName, bool bMuted) = 0;` — Mute or unmute a player @param PlayerName Player to mute @param bMuted true if the player should be muted
- L547 _public prototype_ `virtual bool IsPlayerMuted(const FString& PlayerName) const = 0;` — @param PlayerName Player to get the mute state of @return true if player is muted
- L558 _public prototype_ `virtual void SetChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName, bool bAudioMuted) = 0;` — Mute or unmute a player in a given channel. Only has effect if the player is currently in the channel, and only until you/they leave the channel. i.e. this is expected to be [re]called by OnVoiceChatPlayerAdded delegates. @param ChannelName Channel in which to mute the player @param PlayerName Player to mute in channel @param bMuted true if the player should be muted in the specified channel
- L565 _public prototype_ `virtual bool IsChannelPlayerMuted(const FString& ChannelName, const FString& PlayerName) const = 0;` — @param ChannelName Channel in which the mute state will be checked @param PlayerName Player to get the mute state of in channel @return true if player is muted
- L570 _public prototype_ `virtual FOnVoiceChatPlayerMuteUpdatedDelegate& OnVoiceChatPlayerMuteUpdated() = 0;` — Delegate triggered when a player's muted state is updated, usually as a result of calling SetPlayerMuted
- L578 _public prototype_ `virtual void SetPlayerVolume(const FString& PlayerName, float Volume) = 0;` — Set player volume @param PlayerName Player to adjust the volume for @param Volume Value between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L584 _public prototype_ `virtual float GetPlayerVolume(const FString& PlayerName) const = 0;` — @param PlayerName Player to get the volume of @return Volume Value between 0.0 and 2.0. 1.0 leaves the source volume unchanged.
- L589 _public prototype_ `virtual FOnVoiceChatPlayerVolumeUpdatedDelegate& OnVoiceChatPlayerVolumeUpdated() = 0;` — Delegate triggered when a player's volume is updated, usually as a result of calling SetPlayerVolume
- L594 _public prototype_ `virtual void TransmitToAllChannels() = 0;` — Transmit to all channels that you are currently in
- L599 _public prototype_ `virtual void TransmitToNoChannels() = 0;` — Stop transmitting to all channels that you are currently in. This does not apply to channels you will join.
- L605 _public prototype_ `virtual void TransmitToSpecificChannels(const TSet<FString>& ChannelNames) = 0;` — Transmit to Specified set of channels @param ChannelNames Channels to transmit to
- L611 _public function_ `virtual void AddSpecificChannelsToTransmit(const TSet<FString>& ChannelNames)` — Add specific channels to transmit @param ChannelNames New channels to add to the current transmit set
- L617 _public function_ `virtual void RemoveSpecificChannelsFromTransmit(const TSet<FString>& ChannelNames)` — Remove specific channels from transmit @param ChannelNames Channels to remove from the current transmit set
- L624 _public prototype_ `virtual EVoiceChatTransmitMode GetTransmitMode() const = 0;` — Get the current transmit mode @return Transmit mode. If it is EVoiceChatTransmitMode::SpecificChannels, the current channels can be retrieved using GetTransmitChannels()
- L631 _public prototype_ `virtual TSet<FString> GetTransmitChannels() const = 0;` — Get all channels we are transmitting to @return Channels	 we are transmitting to. Will be empty if GetTransmissionMode() returned a value other than EVoiceChatTransmitMode::SpecificChannels
- L640 _public prototype_ `virtual FDelegateHandle StartRecording(const FOnVoiceChatRecordSamplesAvailableDelegate::FDelegate& Delegate) = 0;` — Start recording @param Delegate This will be called from audio thread. @return Delegate handle to pass to stop recording
- L647 _public prototype_ `virtual void StopRecording(FDelegateHandle Handle) = 0;` — Stop recording @param Handle Delegate handle returned from a StartRecording call
- L652 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatAfterCaptureAudioReadDelegate(const FOnVoiceChatAfterCaptureAudioReadDelegate2::FDelegate& Delegate) = 0;` — Delegates called from audio thread.
- L653 _public prototype_ `virtual void UnregisterOnVoiceChatAfterCaptureAudioReadDelegate(FDelegateHandle Handle) = 0;`
- L655 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeCaptureAudioSentDelegate(const FOnVoiceChatBeforeCaptureAudioSentDelegate2::FDelegate& Delegate) = 0;`
- L656 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeCaptureAudioSentDelegate(FDelegateHandle Handle) = 0;`
- L658 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) = 0;`
- L659 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate(FDelegateHandle Handle) = 0;`
- L661 _public prototype_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) = 0;`
- L662 _public prototype_ `virtual void UnregisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate(FDelegateHandle Handle) = 0;`
- L665 _public function_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeRecvAudioRenderedDelegate(const FOnVoiceChatBeforeRecvAudioRenderedDelegate::FDelegate& Delegate) final` — `UE_DEPRECATED(5.7, "Please use RegisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate instead. Also now possible to use RegisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate for receiving unmixed audio")`
- L670 _public function_ `virtual void UnregisterOnVoiceChatBeforeRecvAudioRenderedDelegate(FDelegateHandle Handle) final` — `UE_DEPRECATED(5.7, "Please use UnregisterOnVoiceChatBeforeRecvMixedAudioRenderedDelegate instead. Also now possible to use UnregisterOnVoiceChatBeforeRecvUnmixedAudioRenderedDelegate for unmixed audio")`
- L676 _public function_ `virtual FDelegateHandle RegisterOnVoiceChatAfterCaptureAudioReadDelegate(const FOnVoiceChatAfterCaptureAudioReadDelegate::FDelegate& Delegate) final` — `UE_DEPRECATED(5.6, "Please pass a FOnVoiceChatBeforeCaptureAudioSentDelegate2, which adds the ChannelName param")`
- L685 _public function_ `virtual FDelegateHandle RegisterOnVoiceChatBeforeCaptureAudioSentDelegate(const FOnVoiceChatBeforeCaptureAudioSentDelegate::FDelegate& Delegate) final` — `UE_DEPRECATED(5.6, "Please pass a FOnVoiceChatBeforeCaptureAudioSentDelegate2, which adds the ChannelName param")`
- L696 _public prototype_ `virtual FString InsecureGetLoginToken(const FString& PlayerName) = 0;` — Generate Login/Join tokens. Should be used for development purposes only
- L697 _public prototype_ `virtual FString InsecureGetJoinToken(const FString& ChannelName, EVoiceChatChannelType ChannelType, TOptional<FVoiceChatChannel3dProperties> Channel3dProperties = TOptional<FVoiceChatChannel3dProperties>()) = 0;`

#### class `IVoiceChat`  
`class IVoiceChat : public IVoiceChatUser, public IModularFeature`  
_L701-807_
- inherits: `IVoiceChatUser,IModularFeature`
- L707 _public function_ `static IVoiceChat* Get()` — Get the IVoiceChat modular feature instance
- L716 _public function_ `static FName GetModularFeatureName()`
- L725 _public prototype_ `virtual bool Initialize() = 0;` — Initialize VoiceChat synchronously
- L730 _public prototype_ `virtual void Initialize(const FOnVoiceChatInitializeCompleteDelegate& Delegate) = 0;` — Initialize VoiceChat asynchronously
- L735 _public prototype_ `virtual bool Uninitialize() = 0;` — Uninitialize VoiceChat synchronously
- L740 _public prototype_ `virtual void Uninitialize(const FOnVoiceChatUninitializeCompleteDelegate& Delegate) = 0;` — Uninitialize VoiceChat asynchronously
- L747 _public prototype_ `virtual bool IsInitialized() const = 0;` — Is voice chat initialized? @return true if voice chat is initialized
- L754 _public prototype_ `virtual void Connect(const FOnVoiceChatConnectCompleteDelegate& Delegate) = 0;` — Connect to a voice server @param Delegate delegate called once connect completes
- L761 _public prototype_ `virtual void Disconnect(const FOnVoiceChatDisconnectCompleteDelegate& Delegate) = 0;` — Disconnect from a voice server @param Delegate delegate called once disconnect completes
- L768 _public prototype_ `virtual bool IsConnecting() const = 0;` — Are we connecting to the voice server? @return true if we are connecting to the voice server
- L775 _public prototype_ `virtual bool IsConnected() const = 0;` — Are we connected to the voice server? @return true if we are connected to the voice server
- L780 _public prototype_ `virtual FOnVoiceChatConnectedDelegate& OnVoiceChatConnected() = 0;` — Delegate triggered when we are connected to voice chat
- L785 _public prototype_ `virtual FOnVoiceChatDisconnectedDelegate& OnVoiceChatDisconnected() = 0;` — Delegate triggered when we are disconnected from voice chat
- L792 _public prototype_ `virtual FOnVoiceChatReconnectedDelegate& OnVoiceChatReconnected() = 0;` — Delegate triggered when we are reconnected to voice chat in cases where the underlying implementation disconnected and then reconnected. This is most commonly seen when an application resumes after being suspended. If the disconnect is unexpected, OnVoiceChatDisconnected will be called instead.
- L799 _public prototype_ `virtual IVoiceChatUser* CreateUser() = 0;` — Allocate an interface for an additional user. The interface must be released with ReleaseUser. @return new instance of IVoiceChatUser, or nullptr if implementation does not support multiple users
- L806 _public prototype_ `virtual void ReleaseUser(IVoiceChatUser* VoiceChatUser) = 0;` — Release an interface for an additional user. @param VoiceChatUser the user interface to release.

#### Free symbols / members of external scopes

- L21 _prototype_ `const TCHAR* LexToString(const EVoiceChatChannelType Value);`
- L35 _prototype_ `const TCHAR* LexToString(const EVoiceChatAttenuationModel Value);`
- L59 _prototype_ `const TCHAR* LexToString(const EVoiceChatTransmitMode Value);`
- L90 _function_ `inline FString LexToString(const FVoiceChatDeviceInfo& DeviceInfo)`
- L95 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatInitializeCompleteDelegate, const FVoiceChatResult& );`
- L95 _prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatInitializeCompleteDelegate, const FVoiceChatResult& );`
- L96 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUninitializeCompleteDelegate, const FVoiceChatResult& );`
- L96 _prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatUninitializeCompleteDelegate, const FVoiceChatResult& );`
- L97 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatConnectCompleteDelegate, const FVoiceChatResult& );`
- L97 _prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatConnectCompleteDelegate, const FVoiceChatResult& );`
- L98 _delegate_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatDisconnectCompleteDelegate, const FVoiceChatResult& );`
- L98 _prototype_ `DECLARE_DELEGATE_OneParam(FOnVoiceChatDisconnectCompleteDelegate, const FVoiceChatResult& );`
- L99 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatLoginCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L99 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatLoginCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L100 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatLogoutCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L100 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatLogoutCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L101 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatChannelJoinCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L101 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatChannelJoinCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L102 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatChannelLeaveCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L102 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVoiceChatChannelLeaveCompleteDelegate, const FString& , const FVoiceChatResult& );`
- L104 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatAvailableAudioDevicesChangedDelegate);`
- L104 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatAvailableAudioDevicesChangedDelegate);`
- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatReconnectedDelegate);`
- L105 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatReconnectedDelegate);`
- L106 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatConnectedDelegate);`
- L106 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVoiceChatConnectedDelegate);`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatDisconnectedDelegate, const FVoiceChatResult& );`
- L107 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatDisconnectedDelegate, const FVoiceChatResult& );`
- L108 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatLoggedInDelegate, const FString& );`
- L108 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatLoggedInDelegate, const FString& );`
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatLoggedOutDelegate, const FString& );`
- L109 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatLoggedOutDelegate, const FString& );`
- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatCallStatsUpdatedDelegate, const FVoiceChatCallStats& );`
- L110 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatCallStatsUpdatedDelegate, const FVoiceChatCallStats& );`
- L111 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatCallStatsUpdatedDelegate2, const FString& , const FVoiceChatCallStats& );`
- L111 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatCallStatsUpdatedDelegate2, const FString& , const FVoiceChatCallStats& );`
- L112 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatChannelJoinedDelegate, const FString& );`
- L112 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoiceChatChannelJoinedDelegate, const FString& );`
- L113 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatChannelExitedDelegate, const FString& , const FVoiceChatResult& );`
- L113 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatChannelExitedDelegate, const FString& , const FVoiceChatResult& );`
- L114 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatPlayerAddedDelegate, const FString& , const FString& );`
- L114 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatPlayerAddedDelegate, const FString& , const FString& );`
- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatPlayerRemovedDelegate, const FString& , const FString& );`
- L115 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVoiceChatPlayerRemovedDelegate, const FString& , const FString& );`
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerTalkingUpdatedDelegate, const FString& , const FString& , bool );`
- L116 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerTalkingUpdatedDelegate, const FString& , const FString& , bool );`
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerMuteUpdatedDelegate, const FString& , const FString& , bool );`
- L117 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerMuteUpdatedDelegate, const FString& , const FString& , bool );`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerVolumeUpdatedDelegate, const FString& , const FString& , float );`
- L118 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatPlayerVolumeUpdatedDelegate, const FString& , const FString& , float );`
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatRecordSamplesAvailableDelegate, TArrayView<const int16> , int , int );`
- L120 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatRecordSamplesAvailableDelegate, TArrayView<const int16> , int , int );`
- L121 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatAfterCaptureAudioReadDelegate2, const FString& , TArrayView<int16> , int , int );`
- L121 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatAfterCaptureAudioReadDelegate2, const FString& , TArrayView<int16> , int , int );`
- L122 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnVoiceChatBeforeCaptureAudioSentDelegate2, const FString& , TArrayView<const int16> , int , int , bool );`
- L122 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FOnVoiceChatBeforeCaptureAudioSentDelegate2, const FString& , TArrayView<const int16> , int , int , bool );`
- L123 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnVoiceChatBeforeRecvAudioRenderedDelegate, TArrayView<int16> , int , int , bool , const FString& , const FString& );`
- L123 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FOnVoiceChatBeforeRecvAudioRenderedDelegate, TArrayView<int16> , int , int , bool , const FString& , const FString& );`
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatAfterCaptureAudioReadDelegate, TArrayView<int16> , int , int );`
- L125 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnVoiceChatAfterCaptureAudioReadDelegate, TArrayView<int16> , int , int );`
- L126 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatBeforeCaptureAudioSentDelegate, TArrayView<const int16> , int , int , bool );`
- L126 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnVoiceChatBeforeCaptureAudioSentDelegate, TArrayView<const int16> , int , int , bool );`
- L679 _function_ `` (scope `IVoiceChatUser::RegisterOnVoiceChatAfterCaptureAudioReadDelegate`)
- L688 _function_ `` (scope `IVoiceChatUser::RegisterOnVoiceChatBeforeCaptureAudioSentDelegate`)

### `Plugins/Online/VoiceChat/VoiceChat/Source/Public/VoiceChatErrors.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define VOICECHAT_ERROR(...) FVoiceChatResult::CreateError(TEXT("errors.com.epicgames.voicechat"), __VA_ARGS__)`
- L8 _namespace_ `namespace VoiceChat`
- L10 _namespace_ `namespace Errors` (scope `VoiceChat`)
- L12 _function_ `inline FVoiceChatResult NotEnabled()` (scope `VoiceChat::Errors`)
- L13 _function_ `inline FVoiceChatResult NotInitialized()` (scope `VoiceChat::Errors`)
- L14 _function_ `inline FVoiceChatResult NotConnected()` (scope `VoiceChat::Errors`)
- L15 _function_ `inline FVoiceChatResult NotLoggedIn()` (scope `VoiceChat::Errors`)
- L17 _function_ `inline FVoiceChatResult NotPermitted()` (scope `VoiceChat::Errors`)
- L18 _function_ `inline FVoiceChatResult Throttled()` (scope `VoiceChat::Errors`)
- L20 _function_ `inline FVoiceChatResult InvalidState()` (scope `VoiceChat::Errors`)
- L21 _function_ `inline FVoiceChatResult MissingConfig()` (scope `VoiceChat::Errors`)
- L22 _function_ `inline FVoiceChatResult AlreadyInProgress()` (scope `VoiceChat::Errors`)
- L23 _function_ `inline FVoiceChatResult DisconnectInProgress()` (scope `VoiceChat::Errors`)
- L24 _function_ `inline FVoiceChatResult OtherUserLoggedIn()` (scope `VoiceChat::Errors`)
- L25 _function_ `inline FVoiceChatResult NotInChannel()` (scope `VoiceChat::Errors`)
- L26 _function_ `inline FVoiceChatResult ChannelJoinInProgress()` (scope `VoiceChat::Errors`)
- L27 _function_ `inline FVoiceChatResult ChannelLeaveInProgress()` (scope `VoiceChat::Errors`)
- L28 _function_ `inline FVoiceChatResult PlatformPartyChatActive()` (scope `VoiceChat::Errors`)
- L30 _function_ `inline FVoiceChatResult InvalidArgument(const FString& ErrorDesc = FString())` (scope `VoiceChat::Errors`)
- L31 _function_ `inline FVoiceChatResult CredentialsInvalid(const FString& ErrorDesc = FString())` (scope `VoiceChat::Errors`)
- L32 _function_ `inline FVoiceChatResult CredentialsExpired()` (scope `VoiceChat::Errors`)
- L34 _function_ `inline FVoiceChatResult ClientTimeout()` (scope `VoiceChat::Errors`)
- L35 _function_ `inline FVoiceChatResult ServerTimeout()` (scope `VoiceChat::Errors`)
- L36 _function_ `inline FVoiceChatResult DnsFailure()` (scope `VoiceChat::Errors`)
- L37 _function_ `inline FVoiceChatResult ConnectionFailure()` (scope `VoiceChat::Errors`)

### `Plugins/Online/VoiceChat/VoiceChat/Source/Public/VoiceChatResult.h` (Public)


#### enum `EVoiceChatResult`  
`enum class EVoiceChatResult`  
_L6-32_
- L9 _public enumerator_ `Success = 0` — The operation succeeded
- L12 _public enumerator_ `InvalidState` — Common state errors
- L13 _public enumerator_ `NotInitialized`
- L14 _public enumerator_ `NotConnected`
- L15 _public enumerator_ `NotLoggedIn`
- L16 _public enumerator_ `NotPermitted`
- L17 _public enumerator_ `Throttled`
- L20 _public enumerator_ `InvalidArgument` — Common argument errors
- L21 _public enumerator_ `CredentialsInvalid`
- L22 _public enumerator_ `CredentialsExpired`
- L25 _public enumerator_ `ClientTimeout` — Common connection errors
- L26 _public enumerator_ `ServerTimeout`
- L27 _public enumerator_ `DnsFailure`
- L28 _public enumerator_ `ConnectionFailure`
- L31 _public enumerator_ `ImplementationError` — Error does not map to any common categories

#### struct `FVoiceChatResult`  
`struct FVoiceChatResult`  
_L34-87_
- L37 _public member_ `EVoiceChatResult ResultCode;` — Success, or an error category
- L39 _public member_ `FString ErrorCode;` — If we failed, the code for the error
- L41 _public member_ `int ErrorNum = 0;` — If we failed, a numeric error from the implementation
- L43 _public member_ `FString ErrorDesc;` — If we failed, more details about the error condition
- L45 _public function_ `bool IsSuccess() const`
- L47 _public function_ `bool operator==(const FVoiceChatResult& Other) const`
- L52 _public function_ `bool operator!=(const FVoiceChatResult& Other) const`
- L57 _public function_ `FVoiceChatResult(EVoiceChatResult ResultCode) : ResultCode(ResultCode)`
- L58 _public function_ `FVoiceChatResult(EVoiceChatResult ResultCode, const FString& ErrorCode) : ResultCode(ResultCode), ErrorCode(ErrorCode)`
- L59 _public function_ `FVoiceChatResult(EVoiceChatResult ResultCode, const FString& ErrorCode, const FString& ErrorDesc) : ResultCode(ResultCode), ErrorCode(ErrorCode), ErrorDesc(ErrorDesc)`
- L60 _public function_ `FVoiceChatResult(EVoiceChatResult ResultCode, const FString& ErrorCode, int ErrorNum) : ResultCode(ResultCode), ErrorCode(ErrorCode), ErrorNum(ErrorNum)`
- L61 _public function_ `FVoiceChatResult(EVoiceChatResult ResultCode, const FString& ErrorCode, int ErrorNum, const FString& ErrorDesc) : ResultCode(ResultCode), ErrorCode(ErrorCode), ErrorDesc(ErrorDesc)`
- L63 _public function_ `static FVoiceChatResult CreateSuccess()`
- L66 _public function_ `static FVoiceChatResult CreateError(const FString& ErrorNamespace, EVoiceChatResult ResultCode, const FString& ErrorCode, const FString& ErrorDesc = FString())` — Create factory for proper namespacing
- L81 _public function_ `static FVoiceChatResult CreateError(const FString& ErrorNamespace, EVoiceChatResult ResultCode, const FString& ErrorCode, int ErrorNum, const FString& ErrorDesc = FString())` — Create factory for proper namespacing

#### Free symbols / members of external scopes

- L89 _function_ `inline FString LexToString(const EVoiceChatResult Result)`
- L118 _function_ `inline FString LexToString(const FVoiceChatResult& Result)`
