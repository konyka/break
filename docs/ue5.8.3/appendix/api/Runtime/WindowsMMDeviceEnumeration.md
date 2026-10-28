# Runtime / WindowsMMDeviceEnumeration

- module root: `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration`
- headers: 7; symbols: 143
- symbol kinds: class=3, enum=1, enumerator=3, function=11, macro=1, member=32, namespace=6, prototype=81, struct=5
- PrivateDependencyModuleNames: Core, Engine
- PrivateIncludePathModuleNames: TargetPlatform

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Private/ConversionHelpers.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Audio`
- L19 _function_ `static inline EAudioDeviceState ConvertWordToDeviceState(DWORD InWord)` (scope `Audio`)
- L34 _function_ `static inline IAudioMixerDeviceChangedListener::EDisconnectReason AudioSessionDisconnectToEDisconnectReason(AudioSessionDisconnectReason InDisconnectReason)` (scope `Audio`)

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Private/WindowsMMCvarUtils.h` (Private)


#### class `Audio::WindowsMMCvarUtils`  
`class WindowsMMCvarUtils`  
_L8-19_
- L12 _public prototype_ `static bool ShouldIgnoreDeviceSwaps();` — Called by FWindowsMMNotificationClient to bypass notifications for audio device changes:
- L15 _public prototype_ `static bool ShouldLogDeviceSwaps();` — Called by FWindowsMMNotificationClient to toggle logging for audio device changes:
- L18 _public prototype_ `static bool IsAggregateDeviceSupportCVarEnabled();` — Called by FWindowsMMNotificationClient to determine if Wasapi aggregate device support is enabled.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Private/WindowsMMDeviceEnumerationLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioEnumeration, Log, All);`

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Public/ScopedCom.h` (Public)


#### struct `Audio::FScopeComString`  
`struct FScopeComString final`  
_L16-43_
- L18 _public member_ `LPTSTR StringPtr = nullptr;`
- L22 _public function_ `const LPTSTR Get() const`
- L27 _public function_ `explicit operator bool() const`
- L32 _public function_ `FScopeComString(LPTSTR InStringPtr = nullptr) : StringPtr(InStringPtr)`
- L36 _public function_ `~FScopeComString()`

#### class `Audio::FScopedCoInitialize`  
`class FScopedCoInitialize final`  
_L45-66_
- L48 _public function_ `FScopedCoInitialize()`
- L55 _public function_ `~FScopedCoInitialize()`
- L65 _private member_ `bool bCoInitialized = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Audio`

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Public/WindowsMMDeviceInfoCache.h` (Public)


#### struct `Audio::FWindowsMMDeviceCache`  
`struct FWindowsMMDeviceCache : IAudioMixerDeviceChangedListener, IAudioPlatformDeviceInfoCache`  
_L27-167_
- inherits: `IAudioMixerDeviceChangedListener,IAudioPlatformDeviceInfoCache`
- L58 _public member_ `TComPtr<IMMDeviceEnumerator> DeviceEnumerator;`
- L60 _public member_ `mutable FRWLock CacheMutationLock;` — R/W lock protects map and default arrays.
- L61 _public member_ `TMap<FName, FCacheEntry> Cache;` — DeviceID GUID -> Info.
- L62 _public member_ `FName DefaultCaptureId[(int32)EAudioDeviceRole::COUNT];` — Role -> DeviceID GUID
- L63 _public member_ `FName DefaultRenderId[(int32)EAudioDeviceRole::COUNT];` — Role -> DeviceID GUID
- L65 _public prototype_ `FWindowsMMDeviceCache();`
- L66 _public prototype_ `explicit FWindowsMMDeviceCache(bool bInEnableAggregateDeviceSupport);`
- L67 _public prototype_ `virtual ~FWindowsMMDeviceCache() = default;`
- L69 _public prototype_ `bool EnumerateChannelMask(uint32 InMask, FCacheEntry& OutInfo);`
- L71 _public prototype_ `bool EnumerateChannelFormat(const WAVEFORMATEX* InFormat, FCacheEntry& OutInfo);`
- L73 _public prototype_ `EDeviceEndpointType QueryDeviceDataFlow(const TComPtr<IMMDevice>& InDevice) const;`
- L75 _public prototype_ `bool EnumerateDeviceProps(const TComPtr<IMMDevice>& InDevice, FCacheEntry& OutInfo);`
- L77 _public prototype_ `bool EnumerateHardwareTopology(const TComPtr<IMMDevice>& InDevice, FCacheEntry& OutInfo);`
- L80 _public prototype_ `void EnumerateEndpoints();` — `UE_DEPRECATED(5.8, "EnumerateEndpoints is no longer publicly callable; use Refresh() to rebuild the cache atomically.")`
- L83 _public prototype_ `void EnumerateDefaults();` — `UE_DEPRECATED(5.8, "EnumerateDefaults is no longer publicly callable; use Refresh() to rebuild the cache atomically.")`
- L85 _public prototype_ `void OnDefaultCaptureDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L87 _public prototype_ `void OnDefaultRenderDeviceChanged(const EAudioDeviceRole InAudioDeviceRole, const FString& DeviceId) override;`
- L89 _public prototype_ `void OnDeviceAdded(const FString& DeviceId, bool bIsRender) override;`
- L91 _public prototype_ `void OnDeviceRemoved(const FString& DeviceId, bool) override;`
- L93 _public prototype_ `TOptional<FCacheEntry> BuildCacheEntry(const FString& DeviceId);`
- L95 _public prototype_ `FString GetFriendlyName(FName InDeviceId) const;`
- L97 _public prototype_ `void OnDeviceStateChanged(const FString& DeviceId, const EAudioDeviceState InState, bool) override;`
- L99 _public prototype_ `void OnFormatChanged(const FString& InDeviceId, const FFormatChangedData& InFormat) override;`
- L101 _public prototype_ `void MakeDeviceInfo(const FCacheEntry& InEntry, FName InDefaultDevice, FAudioPlatformDeviceInfo& OutInfo) const;`
- L103 _public prototype_ `virtual TArray<FAudioPlatformDeviceInfo> GetAllActiveOutputDevices() const override;`
- L105 _public prototype_ `virtual bool IsAggregateHardwareDeviceId(const FName InDeviceID) const override;`
- L107 _public prototype_ `virtual TOptional<FAudioPlatformDeviceInfo> GetAggregateHardwareDeviceInfo(const FName InHardwareId, const EDeviceEndpointType InEndpointType) const;`
- L109 _public prototype_ `virtual TArray<FAudioPlatformDeviceInfo> GetLogicalAggregateDevices(const FName InHardwareId, const EDeviceEndpointType InEndpointType) const override;`
- L111 _public prototype_ `virtual TArray<FAudioPlatformDeviceInfo> SynthesizeAggregateDeviceList(const EDeviceEndpointType InType) const;`
- L113 _public prototype_ `virtual void Refresh() override;`
- L115 _public prototype_ `virtual void InvalidateDevice(FName InDeviceId) override;`
- L117 _public prototype_ `virtual FName GetDefaultOutputDevice(EAudioDeviceRole InRole) const override;`
- L119 _public prototype_ `FName GetDefaultOutputDevice_NoLock() const;`
- L121 _public prototype_ `TOptional<FAudioPlatformDeviceInfo> FindDefaultOutputDevice() const override;`
- L123 _public prototype_ `TOptional<FAudioPlatformDeviceInfo> FindActiveOutputDevice(FName InDeviceID) const override;`
- L125 _public prototype_ `bool IsAggregateDeviceSupportEnabled() const;`
- L127 _public prototype_ `static FString ExtractAggregateDeviceName(const FString& InName);`
- L131 _private prototype_ `void EnumerateEndpoints_NoLock();` — Re-enumerates all endpoints into the cache. Caller MUST hold CacheMutationLock for write.
- L134 _private prototype_ `void EnumerateDefaults_NoLock();` — Re-reads default render/capture device IDs. Caller MUST hold CacheMutationLock for write.
- L160 _private member_ `bool bIsAggregateDeviceSupportEnabled = false;`
- L162 _private prototype_ `void GetHardwareInfo(TSet<FCacheEntry, FCacheKeyFuncs>& OutUniqueHardwareIds, TMap<FName, FDeviceChannelInfo>& OutDeviceChannelInfos, EDeviceEndpointType InType) const;`
- L164 _private prototype_ `static FAudioPlatformDeviceInfo CreateAggregateDeviceInfo(const FCacheEntry& InCacheEntry, const FDeviceChannelInfo& InDeviceChannelInfo);`
- L166 _private prototype_ `static int32 ExtractAggregateChannelNumber(const FString& InName);`

#### struct `Audio::FWindowsMMDeviceCache::FCacheEntry`  
`struct FCacheEntry`  
_L29-56_
- L33 _public member_ `FName DeviceId;` — Key
- L34 _public member_ `FString FriendlyName;`
- L35 _public member_ `FString DeviceFriendlyName;`
- L36 _public member_ `EAudioDeviceState State = EAudioDeviceState::NotPresent;`
- L37 _public member_ `int32 NumChannels = 0;`
- L38 _public member_ `int32 SampleRate = 0;`
- L39 _public member_ `EDeviceEndpointType Type = EDeviceEndpointType::Unknown;`
- L40 _public member_ `uint32 ChannelBitmask = 0;` — Bitfield used to build output channels, for easy comparison.
- L41 _public member_ `FName HardwareId;` — Unique string of the physical hardware device this MMDevice belongs to
- L42 _public member_ `FString FilterId;` — Unique identifier for this device containing product id (pid), vendor id (vid), etc.
- L44 _public member_ `TArray<EAudioMixerChannel::Type> OutputChannels;` — TODO. Generate this from the ChannelNum and bitmask when we are asked for it.
- L45 _public member_ `mutable FRWLock MutationLock;`
- L47 _public prototype_ `FCacheEntry& operator=(const FCacheEntry& InOther);`
- L49 _public prototype_ `FCacheEntry& operator=(FCacheEntry&& InOther);`
- L51 _public prototype_ `FCacheEntry(const FCacheEntry& InOther);`
- L53 _public prototype_ `FCacheEntry(FCacheEntry&& InOther);`
- L55 _public prototype_ `FCacheEntry(const FString& InDeviceId);`

#### enum `Audio::FWindowsMMDeviceCache::FCacheEntry::EEndpointType`  
`enum class UE_DEPRECATED(5.6, "EEndpointType is`  
_L31-31_
- L31 _public enumerator_ `enum class UE_DEPRECATED(5.6, "EEndpointType is deprecated. Please use EDeviceEndpointType instead.") EEndpointType { Unknown, Render, Capture }; FName DeviceId; FString FriendlyName; FString DeviceFriendlyName; EAudioDeviceState State = EAudioDeviceState::NotPresent; int32 NumChannels = 0; int32 SampleRate = 0;`
- L31 _public enumerator_ `enum class UE_DEPRECATED(5.6, "EEndpointType is deprecated. Please use EDeviceEndpointType instead.") EEndpointType { Unknown, Render, Capture }; FName DeviceId; FString FriendlyName; FString DeviceFriendlyName; EAudioDeviceState State = EAudioDeviceState::NotPresent; int32 NumChannels = 0; int32 SampleRate = 0;`
- L31 _public enumerator_ `enum class UE_DEPRECATED(5.6, "EEndpointType is deprecated. Please use EDeviceEndpointType instead.") EEndpointType { Unknown, Render, Capture }; FName DeviceId; FString FriendlyName; FString DeviceFriendlyName; EAudioDeviceState State = EAudioDeviceState::NotPresent; int32 NumChannels = 0; int32 SampleRate = 0;`

#### struct `Audio::FWindowsMMDeviceCache::FCacheKeyFuncs`  
`struct FCacheKeyFuncs : BaseKeyFuncs<FWindowsMMDeviceCache::FCacheEntry, FName>`  
_L136-152_
- inherits: `BaseKeyFuncs<FWindowsMMDeviceCache::FCacheEntry,FName>`
- L138 _public function_ `static KeyInitType GetSetKey(ElementInitType Element)`
- L143 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L148 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`

#### struct `Audio::FWindowsMMDeviceCache::FDeviceChannelInfo`  
`struct FDeviceChannelInfo`  
_L154-158_
- L156 _public member_ `uint32 LogicDeviceChannelCount = 0;`
- L157 _public member_ `uint32 TotalChannelCount = 0;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API WINDOWSMMDEVICEENUMERATION_API`
- L25 _namespace_ `namespace Audio`

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Public/WindowsMMNotificationClient.h` (Public)


#### class `Audio::FWindowsMMNotificationClient`  
`class FWindowsMMNotificationClient final : public IMMNotificationClient #if PLATFORM_WINDOWS , public IAudioSessionEvents #endif`  
_L28-115_
- inherits: `IMMNotificationClient,IAudioSessionEvents`
- L34 _public prototype_ `FWindowsMMNotificationClient();`
- L35 _public prototype_ `~FWindowsMMNotificationClient();`
- L38 _public prototype_ `bool IsRenderDevice(const FString& InDeviceId) const;` — TODO: Ideally we'd use the cache instead of ask for this.
- L40 _public prototype_ `FString GetFriendlyName(const FString InDeviceID);`
- L41 _public prototype_ `FString GetFriendlyName(const TComPtr<IMMDevice>& InDevice);`
- L43 _public prototype_ `TComPtr<IMMDevice> GetDevice(const FString InDeviceID) const;`
- L44 _public prototype_ `uint32 ReleaseClient();`
- L46 _public prototype_ `void RegisterDeviceChangedListener(Audio::IAudioMixerDeviceChangedListener* DeviceChangedListener);`
- L47 _public prototype_ `void UnRegisterDeviceDeviceChangedListener(Audio::IAudioMixerDeviceChangedListener* DeviceChangedListener);`
- L50 _public prototype_ `HRESULT STDMETHODCALLTYPE QueryInterface(const IID& IId, void** UnknownPtrPtr) override;`
- L51 _public prototype_ `ULONG STDMETHODCALLTYPE AddRef() override;`
- L52 _public prototype_ `ULONG STDMETHODCALLTYPE Release() override;`
- L56 _public prototype_ `HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow InFlow, ERole InRole, LPCWSTR pwstrDeviceId) override;`
- L57 _public prototype_ `HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId) override;`
- L58 _public prototype_ `HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId) override;`
- L59 _public prototype_ `HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) override;`
- L60 _public prototype_ `HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key);`
- L64 _public prototype_ `bool RegisterForSessionNotifications(const TComPtr<IMMDevice>& InDevice);`
- L65 _public prototype_ `bool RegisterForSessionNotifications(const FString& InDeviceId);`
- L66 _public prototype_ `void UnregisterForSessionNotifications();`
- L69 _public prototype_ `HRESULT STDMETHODCALLTYPE OnDisplayNameChanged( LPCWSTR NewDisplayName, LPCGUID EventContext) override;`
- L73 _public prototype_ `HRESULT STDMETHODCALLTYPE OnIconPathChanged( LPCWSTR NewIconPath, LPCGUID EventContext) override;`
- L77 _public prototype_ `HRESULT STDMETHODCALLTYPE OnSimpleVolumeChanged( float NewVolume, BOOL NewMute, LPCGUID EventContext) override;`
- L82 _public prototype_ `HRESULT STDMETHODCALLTYPE OnChannelVolumeChanged( DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext) override;`
- L88 _public prototype_ `HRESULT STDMETHODCALLTYPE OnGroupingParamChanged( LPCGUID NewGroupingParam, LPCGUID EventContext) override;`
- L92 _public prototype_ `HRESULT STDMETHODCALLTYPE OnStateChanged( AudioSessionState NewState) override;`
- L95 _public prototype_ `HRESULT STDMETHODCALLTYPE OnSessionDisconnected( AudioSessionDisconnectReason InDisconnectReason);`
- L100 _private member_ `FCriticalSection SessionRegistrationCS;`
- L101 _private member_ `TComPtr<IAudioSessionManager> SessionManager;`
- L102 _private member_ `TComPtr<IAudioSessionControl> SessionControls;`
- L103 _private member_ `TComPtr<IMMDevice> DeviceListeningToSessionEvents;`
- L105 _private member_ `bool bComInitialized = false;`
- L106 _private member_ `std::atomic<bool> bHasDisconnectSessionHappened = false;`
- L111 _private member_ `LONG Ref = 1;` — Start with self-reference
- L112 _private member_ `TSet<Audio::IAudioMixerDeviceChangedListener*> Listeners;`
- L113 _private member_ `FRWLock ListenersSetRwLock;`
- L114 _private member_ `TComPtr<IMMDeviceEnumerator> DeviceEnumerator = nullptr;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace Audio`

### `Source/Runtime/AudioDeviceEnumeration/Windows/WindowsMMDeviceEnumeration/Public/WindowsMMStringUtils.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Audio`
- L20 _prototype_ `const TCHAR* ToString(AudioSessionDisconnectReason InDisconnectReason);` (scope `Audio`)
- L21 _prototype_ `const TCHAR* ToString(ERole InRole);` (scope `Audio`)
- L22 _prototype_ `const TCHAR* ToString(EDataFlow InFlow);` (scope `Audio`)
- L23 _prototype_ `FString ToFString(const PROPERTYKEY Key);` (scope `Audio`)
- L25 _prototype_ `FString ToFString(const TArray<EAudioMixerChannel::Type>& InChannels);` (scope `Audio`)
- L27 _prototype_ `const TCHAR* ToString(EAudioDeviceRole InRole);` (scope `Audio`)
- L28 _prototype_ `const TCHAR* ToString(EAudioDeviceState InState);` (scope `Audio`)
- L29 _prototype_ `FString AudioClientErrorToFString(HRESULT InResult);` (scope `Audio`)
