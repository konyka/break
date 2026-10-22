# Plugins / PixelStreaming2Settings

- module root: `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Settings`
- headers: 3; symbols: 230
- symbol kinds: class=1, delegate=14, enum=3, enumerator=19, externvar=1, function=3, macro=1, member=151, namespace=2, prototype=34, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, EngineSettings, PixelStreaming2Core, UnrealEd
- PublicDependencyModuleNames: AVCodecsCore, EpicRtc, Slate

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Settings/Internal/PixelStreaming2PluginSettings.h` (Internal)


#### enum `EPortAllocatorFlags`  
`enum class EPortAllocatorFlags : uint32`  
_L52-69_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L54 _public enumerator_ `None = static_cast<uint32>(EpicRtcPortAllocatorOptions::None) UMETA(Hidden)`
- L55 _public enumerator_ `DisableUdp = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableUdp)`
- L56 _public enumerator_ `DisableStun = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableStun)`
- L57 _public enumerator_ `DisableRelay = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableRelay)`
- L58 _public enumerator_ `DisableTcp = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableTcp)`
- L59 _public enumerator_ `EnableIPV6 = static_cast<uint32>(EpicRtcPortAllocatorOptions::EnableIPV6)`
- L60 _public enumerator_ `EnableSharedSocket = static_cast<uint32>(EpicRtcPortAllocatorOptions::EnableSharedSocket)`
- L61 _public enumerator_ `EnableStunRetransmitAttribute = static_cast<uint32>(EpicRtcPortAllocatorOptions::EnableStunRetransmitAttribute)`
- L62 _public enumerator_ `DisableAdapterEnumeration = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableAdapterEnumeration)`
- L63 _public enumerator_ `DisableDefaultLocalCandidate = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableDefaultLocalCandidate)`
- L64 _public enumerator_ `DisableUdpRelay = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableUdpRelay)`
- L65 _public enumerator_ `DisableCostlyNetworks = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableCostlyNetworks)`
- L66 _public enumerator_ `EnableIPV6OnWifi = static_cast<uint32>(EpicRtcPortAllocatorOptions::EnableIPV6OnWifi)`
- L67 _public enumerator_ `EnableAnyAddressPort = static_cast<uint32>(EpicRtcPortAllocatorOptions::EnableAnyAddressPort)`
- L68 _public enumerator_ `DisableLinkLocalNetworks = static_cast<uint32>(EpicRtcPortAllocatorOptions::DisableLinkLocalNetworks)`

#### enum `EInputControllerMode`  
`enum class EInputControllerMode : uint8`  
_L74-78_
- reflection: `UENUM()`
- desc: Pixel Streaming can limit who can send input (keyboard, mouse, etc).
- L76 _public enumerator_ `Any` — Any peer can control input.
- L77 _public enumerator_ `Host` — Only the "host" peer can control input.

#### class `UPixelStreaming2PluginSettings`  
`class UPixelStreaming2PluginSettings : public UDeveloperSettings`  
_L83-707_
- reflection: `UCLASS(MinimalAPI, config = Game, defaultconfig, meta = (DisplayName = "PixelStreaming2"))`
- inherits: `UDeveloperSettings`
- desc: Config loaded/saved to an .ini file. It is also exposed through the plugin settings page in editor.
- L87 _private prototype_ `virtual ~UPixelStreaming2PluginSettings();`
- L96 _public member_ `bool EnablePixelStreamingToolbar = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( ConfigRestartRequired = true, DisplayName = "Enable Pixel Streaming 2 Toolbar", ToolTip = "Adds the Pixel Streaming 2 toolbar to the main viewport toolbar." ))` — clang-format off
- L98 _public member_ `static TAutoConsoleVariable<bool> CVarLogStats;`
- L103 _public member_ `bool LogStats = false;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Log Pixel Streaming Stats", ToolTip = "Whether to show PixelStreaming stats in the log (default: false)." ))`
- L105 _public member_ `static TAutoConsoleVariable<FString> CVarEpicRtcLogFilter;`
- L110 _public member_ `FString EpicRtcLogFilter = "";` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Log messages from EpicRtc to filter", ToolTip = "Double forward slash (\"//\") separated list of regex patterns to filter from the EpicRtc logs (default: \"\")." ))`
- L112 _public member_ `static TAutoConsoleVariable<bool> CVarDisableLatencyTester;`
- L117 _public member_ `bool DisableLatencyTester = false;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Disable Latency Tester", ToolTip = "If true disables latency tester being triggerable." ))`
- L119 _public member_ `static TAutoConsoleVariable<FString> CVarInputController;`
- L124 _public member_ `EInputControllerMode InputController = EInputControllerMode::Any;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Input Controller Mode", ToolTip = "If true disables latency tester being triggerable." ))`
- L126 _public member_ `static TAutoConsoleVariable<bool> CVarDecoupleFramerate;`
- L131 _public member_ `bool DecoupleFramerate = false;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Decouple Frame Rate", ToolTip = "Whether we should only stream as fast as we render or at some fixed interval. Coupled means only stream what we render." ))`
- L133 _public member_ `static TAutoConsoleVariable<float> CVarDecoupleWaitFactor;`
- L138 _public member_ `float DecoupleWaitFactor = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Decouple Wait Factor", ToolTip = "Frame rate factor to wait for a captured frame when streaming in decoupled mode. Higher factor waits longer but may also result in higher latency." ))`
- L140 _public member_ `static TAutoConsoleVariable<float> CVarSignalingReconnectInterval;`
- L145 _public member_ `float SignalingReconnectInterval = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Signaling Reconnect Interval", ToolTip = "Changes the number of seconds between attempted reconnects to the signaling server. This is useful for reducing the log spam produced from attempted reconnects. A value <= 0 results in no reconnect. Default: 2.0s" ))`
- L147 _public member_ `static TAutoConsoleVariable<float> CVarSignalingMaxReconnectAttempts;`
- L152 _public member_ `int32 SignalingMaxReconnectAttempts = -1;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Signaling Max Reconnect Attempts", ToolTip = "Changes the number of attempts that will be made to reconnect to the signalling server. This is useful for triggering application shutdowns if this value is exceeded. A value of < 0 results in unlimited attempts. Default: -1" ))`
- L154 _public member_ `static TAutoConsoleVariable<float> CVarSignalingKeepAliveInterval;`
- L159 _public member_ `float SignalingKeepAliveInterval = 30.0f;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Signaling Reconnect Interval", ToolTip = "Frame rate factor to wait for a captured frame when streaming in decoupled mode. Higher factor waits longer but may also result in higher latency." ))`
- L161 _public member_ `static TAutoConsoleVariable<bool> CVarUseMediaCapture;`
- L166 _public member_ `bool UseMediaCapture = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Use Media Capture", ToolTip = "Use Media Capture from MediaIOFramework to capture frames rather than Pixel Streamings internal backbuffer sources." ))`
- L168 _public member_ `static TAutoConsoleVariable<bool> CVarInitializeDefaultStreamer;`
- L173 _public member_ `bool InitializeDefaultStreamer = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Initialize Default Streamer", ToolTip = "If the default Pixel Streaming 2 streamer should be initialized. You may wish to set this to false if you only plan on receiving streams. Default: true" ))`
- L175 _public member_ `static TAutoConsoleVariable<FString> CVarDefaultStreamerID;`
- L181 _public member_ `FString DefaultStreamerID = TEXT("Def` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Default Streamer ID", ToolTip = "Default Streamer ID to be used when not specified elsewhere.", EditCondition="InitializeDefaultStreamer" ))`
- L183 _public member_ `static TAutoConsoleVariable<FString> CVarDefaultStreamerType;`
- L190 _public member_ `FString DefaultStreamerType = TEXT("Def` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Default Streamer Type", ToolTip = "Default Streamer Type to be used when not specified elsewhere. This value should match a type registered by an IPixelStreaming2StreamerFactory", GetOptions = "GetDefaultStreamerTypeOptions", EditCondition="InitializeDefaultStreamer" ))`
- L192 _public member_ `static TAutoConsoleVariable<bool> CVarAutoStartStream;`
- L198 _public member_ `bool AutoStartStream = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Automatically Start Streaming", ToolTip = "Configure the PixelStreaming2 plugin to automatically start streaming once loaded (if not in editor). You may wish to set this value to false and manually call StartStreaming at a later point from your c++ code. Default: true", EditCondition="InitializeDefaultStreamer" ))`
- L200 _public member_ `static TAutoConsoleVariable<FString> CVarConnectionURL;`
- L205 _public member_ `FString ConnectionURL;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Default Connection URL", ToolTip = "Default URL to connect to. This can be a URL to a signalling server or some other endpoint with the format (protocol)://(host):(port)" ))`
- L207 _public member_ `static FAutoConsoleVariableDeprecated CVarSignallingURL;`
- L209 _public member_ `static TAutoConsoleVariable<bool> CVarCaptureUseFence;`
- L214 _public member_ `bool CaptureUseFence = true;` — `UPROPERTY(config, EditAnywhere, Category = "PixelStreaming", meta = ( DisplayName = "Capture Using Fence", ToolTip = "Whether the texture copy we do during image capture should use a fence or not (non-fenced is faster but less safe)." ))`
- L216 _public member_ `static TAutoConsoleVariable<bool> CVarDebugDumpAudio;`
- L225 _public member_ `FSoftClassPath DefaultCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = "Cursor")` — Pixel streaming always requires various software cursors so they will be visible in the video stream sent to the browser to allow the user to click and interact with UI elements.
- L227 _public member_ `FSoftClassPath TextEditBeamCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = "Cursor")`
- L236 _public member_ `FSoftClassPath HiddenCursorClassName;` — `UPROPERTY(config, EditAnywhere, Category = "Cursor")` — Pixel Streaming can have a server-side cursor (where the cursor itself is shown as part of the video), or a client-side cursor (where the cursor is shown by the browser). In the latter case we need to turn the UE4 cursor invisible.
- L239 _public member_ `static TAutoConsoleVariable<int32> CVarEncoderTargetBitrate;`
- L244 _public member_ `int32 EncoderTargetBitrate = -1;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Target Bitrate", ToolTip = "Target bitrate (bps). Ignore the bitrate WebRTC wants (not recommended). Set to -1 to disable. Default -1.", ClampMin = -1))`
- L246 _public member_ `static TAutoConsoleVariable<int32> CVarEncoderMinQuality;`
- L251 _public member_ `int32 EncoderMinQuality = 0;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Encoder Minimum Quality", ToolTip = "0-100, Higher values result in a better minimum quality but higher average bitrates. Default 0 - i.e. no limit on a minimum Quality.", ClampMin = 0, ClampMax = 100))`
- L253 _public member_ `static TAutoConsoleVariable<int32> CVarEncoderMaxQuality;`
- L258 _public member_ `int32 EncoderMaxQuality = 100;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Encoder Maximum Quality", ToolTip = "0-100, Lower values result in lower average bitrates but reduces maximum quality. Default 100 - i.e. no limit on a maximum QP.", ClampMin = 0, ClampMax = 100))`
- L261 _public member_ `static TAutoConsoleVariable<FString> CVarEncoderQualityPreset;` — not directly connected to cvar due to string to enum conversion
- L266 _public member_ `EAVPreset QualityPreset = EAVPreset::Default;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Default Encoding Quality Profile", ToolTip = "PixelStreaming Encoder presets that affecting Quality vs Bitrate. Supported modes are 'ULTRA_LOW_QUALITY', 'LOW_QUALITY', 'DEFAULT', 'HIGH_QUALITY', 'LOSSLESS'" ))`
- L269 _public member_ `static TAutoConsoleVariable<FString> CVarEncoderLatencyMode;` — not directly connected to cvar due to string to enum conversion
- L274 _public member_ `EAVLatencyMode LatencyMode = EAVLatencyMode::UltraLowLatency;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Default Encoding Quality Profile", ToolTip = "PixelStreaming Encoder presets that affecting Quality vs Latency. Supported modes are 'ULTRA_LOW_LATENCY', 'LOW_LATENCY', 'DEFAULT'" ))`
- L276 _public member_ `static TAutoConsoleVariable<int32> CVarEncoderKeyframeInterval;`
- L281 _public member_ `int32 KeyframeInterval = -1;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Default Keyframe Interval", ToolTip = "How many frames before a key frame is sent. Default: -1 which disables the sending of periodic key frames. Note: NVENC reqires a reinitialization when this changes." ))`
- L283 _public member_ `static TAutoConsoleVariable<int32> CVarEncoderMaxSessions;`
- L288 _public member_ `int32 MaxSessions = -1;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Default Max Number of Encoding Session", ToolTip = "-1 implies no limit. Maximum number of concurrent hardware encoder sessions for Pixel Streaming. Note: Geforce gpus only support 8 concurrent sessions and will rollover to software encoding when that number is exceeded." ))`
- L290 _public member_ `static TAutoConsoleVariable<bool> CVarEncoderEnableSimulcast;`
- L297 _public member_ `bool EnableSimulcast = false;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Enable Simulcast", ToolTip = "Enables simulcast. When enabled, the encoder will encode at full resolution, 1/2 resolution and 1/4 resolution simultaneously. Note: Simulcast is only supported with 'H264' and 'VP8' and you must use the SFU from the infrastructure to fully utilise this functionality.", EditCondition="!WebRTCNegotiateCodecs", EditConditionHides ))`
- L299 _public member_ `static TAutoConsoleVariable<FString> CVarEncoderCodec;`
- L307 _public member_ `FString Codec = UE::PixelStreaming2::GetCVarStringFromEnum(EVideoCodec::H264);` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Preferred Encoder Codec", ToolTip = "Preferred encoder codec signalled during connection establishment.", GetOptions = "GetVideoCodecOptions", EditCondition="!WebRTCNegotiateCodecs", EditConditionHides ))`
- L309 _public member_ `static TAutoConsoleVariable<FString> CVarEncoderScalabilityMode;`
- L317 _public member_ `FString ScalabilityMode = UE::PixelStreaming2::GetCVarStringFromEnum(EScalabilityMode::L1T1);` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings", meta = ( DisplayName = "Default Scalability Mode", ToolTip = "Indicates number of spatial and temporal layers used, default: L1T1. For a full list of values refer to https://www.w3.org/TR/webrtc-svc/#scalabilitymodes*", GetOptions = "GetScalabilityModeOptions", EditCondition="!WebRTCNegotiateCodecs", EditConditionHides ))`
- L319 _public member_ `static TAutoConsoleVariable<FString> CVarEncoderH264Profile;`
- L325 _public member_ `EH264Profile H264Profile = EH264Profile::Baseline;` — `UPROPERTY(config, EditAnywhere, Category = "EncoderSettings|H264", meta = ( DisplayName = "Default H264 profile", ToolTip = "PixelStreaming Encoder profile. Supported modes are 'AUTO', 'BASELINE', 'MAIN', 'HIGH', 'HIGH444', 'PROGRESSIVE_HIGH' or 'CONSTRAINED_HIGH'", ValidEnumValues = "Auto, Baseline, Main, High, High444, ProgressiveHigh, ConstrainedHigh" ))`
- L327 _public member_ `static TAutoConsoleVariable<bool> CVarEncoderDebugDumpFrame;`
- L331 _public member_ `static TAutoConsoleVariable<int32> CVarWebRTCFps;`
- L336 _public member_ `int32 WebRTCFps = 60;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc FPS", ToolTip = "Framerate for WebRTC encoding. Default: 60" ))`
- L338 _public member_ `static TAutoConsoleVariable<int32> CVarWebRTCStartBitrate;`
- L343 _public member_ `int32 WebRTCStartBitrate = 1000000;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc Start Bitrate", ToolTip = "FStart bitrate (bps) that WebRTC will try begin the stream with. Must be between Min/Max bitrates. Default: 1000000" ))`
- L345 _public member_ `static TAutoConsoleVariable<int32> CVarWebRTCMinBitrate;`
- L350 _public member_ `int32 WebRTCMinBitrate = 100000;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc Minimum Bitrate", ToolTip = "Min bitrate (bps) that WebRTC will not request below. Careful not to set too high otherwise WebRTC will just drop frames. Default: 100000" ))`
- L352 _public member_ `static TAutoConsoleVariable<int32> CVarWebRTCMaxBitrate;`
- L357 _public member_ `int32 WebRTCMaxBitrate = 40000000;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc Maximum Bitrate", ToolTip = "Max bitrate (bps) that WebRTC will not request above. Default: 40000000 aka 40 megabits/per second." ))`
- L359 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableReceiveAudio;`
- L364 _public member_ `bool WebRTCDisableReceiveAudio = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable receiving audio by default", ToolTip = "Disables receiving audio from the browser into UE." ))`
- L366 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableReceiveVideo;`
- L371 _public member_ `bool WebRTCDisableReceiveVideo = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable receiving video by default", ToolTip = "Disables receiving video from the browser into UE." ))`
- L373 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableTransmitAudio;`
- L378 _public member_ `bool WebRTCDisableTransmitAudio = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable transmiting audio by default", ToolTip = "Disables transmiting audio to the browser." ))`
- L380 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableTransmitVideo;`
- L385 _public member_ `bool WebRTCDisableTransmitVideo = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable transmiting video by default", ToolTip = "Disables transmiting video to the browser." ))`
- L387 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableAudioSync;`
- L392 _public member_ `bool WebRTCDisableAudioSync = true;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable Audio/Video track sychronisation", ToolTip = "Disables the synchronization of audio and video tracks in WebRTC. This can be useful in low latency usecases where synchronization is not required." ))`
- L394 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCEnableFlexFec;`
- L399 _public member_ `bool WebRTCEnableFlexFec = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Enable Flexible Forward Error Correction", ToolTip = "Signals support for Flexible Forward Error Correction to WebRTC. This can cause a reduction in quality if total bitrate is low." ))`
- L401 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableStats;`
- L406 _public member_ `bool WebRTCDisableStats = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Disable WebRtc Stats", ToolTip = "Disables the collection of WebRTC stats." ))`
- L408 _public member_ `static TAutoConsoleVariable<float> CVarWebRTCStatsInterval;`
- L413 _public member_ `float WebRTCStatsInterval = 1.f;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Stats Interval", ToolTip = "Configures how often WebRTC stats are collected." ))`
- L415 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCNegotiateCodecs;`
- L420 _public member_ `bool WebRTCNegotiateCodecs = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "WebRtc Negotiate Codecs", ToolTip = "Whether PixelStreaming should send all its codecs during sdp handshake so peers can negotiate or just send a single selected codec." ))`
- L422 _public member_ `static TAutoConsoleVariable<FString> CVarWebRTCCodecPreferences;`
- L431 _public member_ `TArray<FString> WebRTCCodecPreferences = { UE::PixelStreaming2::GetCVarStringFromEnum(EVideoCodec::AV1), UE::PixelStreaming2::GetCVarStringFromEnum(EVideoCodec::H264), UE::PixelStreaming2::GetCVarStringFromEnum(EVideoCodec::VP9), UE::PixelStreaming2::GetCVarStringFromEnum(EVideoCodec::VP8) };` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "WebRtc Codec Preferences", ToolTip = "The preference order PixelStreaming will specify during sdp handshake", EditFixedSize, EditCondition="WebRTCNegotiateCodecs", EditConditionHides, GetOptions = "GetWebRTCCodecPreferencesOptions" ))`
- L438 _public prototype_ `static TArray<EVideoCodec> GetCodecPreferences();`
- L440 _public member_ `static TAutoConsoleVariable<float> CVarWebRTCAudioGain;`
- L445 _public member_ `float WebRTCAudioGain = 1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default Audio Gain", ToolTip = "Sets the amount of gain to apply to audio. Default: 1.0" ))`
- L447 _public member_ `static TAutoConsoleVariable<FString> CVarWebRTCPortAllocatorFlags;`
- L454 _public member_ `int32 WebRTCPortAllocatorFlags = 0;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( Bitmask, BitmaskEnum = "/Script/PixelStreaming2Settings.EPortAllocatorFlags", DisplayName = "WebRtc port allocation flags", ToolTip = "Sets the WebRTC port allocator flags. See " ))`
- L456 _public prototype_ `static EPortAllocatorFlags GetPortAllocationFlags();`
- L458 _public member_ `static TAutoConsoleVariable<int> CVarWebRTCMinPort;`
- L463 _public member_ `int WebRTCMinPort = 49152;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc Min Port", ToolTip = "Sets the minimum usable port for the WebRTC port allocator. Default: 49152" ))`
- L465 _public member_ `static TAutoConsoleVariable<int> CVarWebRTCMaxPort;`
- L470 _public member_ `int WebRTCMaxPort = 65535;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings", meta = ( DisplayName = "Default WebRtc Max Port", ToolTip = "Sets the maximum usable port for the WebRTC port allocator. Default: 65535" ))`
- L472 _public member_ `static TAutoConsoleVariable<FString> CVarWebRTCFieldTrials;`
- L477 _public member_ `FString WebRTCFieldTrials;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings|Field Trials", meta = ( DisplayName = "Manually defined WebRtc Field Trials", ToolTip = "Sets the WebRTC field trials string. Format:\"TRIAL1/VALUE1/TRIAL2/VALUE2/\" see https://webrtc.googlesource.com/src/+/HEAD/g3doc/field-trials.md" ))`
- L479 _public member_ `static TAutoConsoleVariable<bool> CVarWebRTCDisableFrameDropper;`
- L484 _public member_ `bool WebRTCDisableFrameDropper = false;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings|Field Trials", meta = ( DisplayName = "Disable Frame Dropper", ToolTip = "Disables the WebRTC internal frame dropper using the field trial WebRTC-FrameDropper/Disabled/" ))`
- L486 _public member_ `static TAutoConsoleVariable<float> CVarWebRTCVideoPacingMaxDelay;`
- L491 _public member_ `float WebRTCVideoPacingMaxDelay = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings|Field Trials", meta = ( DisplayName = "Video Pacing Max Delay", ToolTip = "Enables the WebRTC-Video-Pacing field trial and sets the max delay (ms) parameter. Default: -1.0f (values below zero are discarded.)" ))`
- L493 _public member_ `static TAutoConsoleVariable<float> CVarWebRTCVideoPacingFactor;`
- L498 _public member_ `float WebRTCVideoPacingFactor = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "WebRtcSettings|Field Trials", meta = ( DisplayName = "Video Pacing Factor", ToolTip = "Enables the WebRTC-Video-Pacing field trial and sets the video pacing factor parameter. Larger values are more lenient on larger bitrates. Default: -1.0f (values below zero are discarded.)" ))`
- L503 _public member_ `static TAutoConsoleVariable<bool> CVarEditorUseRemoteSignallingServer;`
- L508 _public member_ `bool EditorUseRemoteSignallingServer = false;` — `UPROPERTY(config, EditAnywhere, Category = "EditorStreaming", meta = ( DisplayName = "Use Remote Signalling Server", ToolTip = "Enables the use of a remote signalling server. Default: false" ))`
- L510 _public member_ `static TAutoConsoleVariable<bool> CVarAutoStreamPIE;`
- L515 _public member_ `bool AutoStreamPlayInEditor = true;` — `UPROPERTY(config, EditAnywhere, Category = "EditorStreaming", meta = ( DisplayName = "Auto Stream Play In Editor", ToolTip = "Automatically start streaming when playing in the editor. Default: true" ))`
- L517 _public member_ `static TAutoConsoleVariable<bool> CVarEditorStartOnLaunch;`
- L522 _public member_ `bool EditorStartOnLaunch = false;` — `UPROPERTY(config, EditAnywhere, Category = "EditorStreaming", meta = ( DisplayName = "Start Editor Streamer On Launch", ToolTip = "Start Editor Streaming as soon as the Unreal Editor is launched. Default: false" ))`
- L524 _public member_ `static TAutoConsoleVariable<FString> CVarEditorSource;`
- L529 _public member_ `EPixelStreaming2EditorStreamTypes EditorSource = EPixelStreaming2EditorStreamTypes::Editor;` — `UPROPERTY(config, EditAnywhere, Category = "EditorStreaming", meta = ( DisplayName = "Editor Streamer Source", ToolTip = "Editor PixelStreaming source. Supported values are 'Editor', 'LevelEditorViewport'. Default: Editor" ))`
- L533 _public member_ `static TAutoConsoleVariable<bool> CVarHMDEnable;`
- L538 _public member_ `bool HMDEnable = false;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Enable HMD", ToolTip = "Enables HMD specific functionality for Pixel Streaming. Namely input handling and stereoscopic rendering. Default: false" ))`
- L540 _public member_ `static TAutoConsoleVariable<bool> CVarHMDMatchAspectRatio;`
- L545 _public member_ `bool HMDMatchAspectRatio = true;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Match Aspect Ratio", ToolTip = "If true automatically resize the rendering resolution to match the aspect ratio determined by the HFoV and VFoV. Default: true" ))`
- L547 _public member_ `static TAutoConsoleVariable<bool> CVarHMDApplyEyePosition;`
- L552 _public member_ `bool HMDAppleEyePosition = true;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Apply Eye Position", ToolTip = "If true automatically position each eye's rendering by whatever amount WebXR reports for each left-right XRView. If false do no eye positioning. Default: true" ))`
- L554 _public member_ `static TAutoConsoleVariable<bool> CVarHMDApplyEyeRotation;`
- L559 _public member_ `bool HMDApplyEyeRotation = true;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Apply Eye Position", ToolTip = "If true automatically rotate each eye's rendering by whatever amount WebXR reports for each left-right XRView. If false do no eye rotation. Default: true" ))`
- L561 _public member_ `static TAutoConsoleVariable<float> CVarHMDHFOV;`
- L566 _public member_ `float HMDHFOV = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Horizontal FOV Override", ToolTip = "Overrides the horizontal field of view for HMD rendering, values are in degrees and values less than 0.0f disable the override. Default: -1.0f" ))`
- L568 _public member_ `static TAutoConsoleVariable<float> CVarHMDVFOV;`
- L573 _public member_ `float HMDVFOV = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Vertical FOV Override", ToolTip = "Overrides the vertical field of view for HMD rendering, values are in degrees and values less than 0.0f disable the override. Default: -1.0f" ))`
- L575 _public member_ `static TAutoConsoleVariable<float> CVarHMDIPD;`
- L580 _public member_ `float HMDIPD = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Interpupillary Distance Override", ToolTip = "Overrides the HMD IPD (interpupillary distance), values are in centimeters and values less than 0.0f disable the override. Default: -1.0f" ))`
- L582 _public member_ `static TAutoConsoleVariable<float> CVarHMDProjectionOffsetX;`
- L587 _public member_ `float HMDProjectionOffsetX = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Horizontal Projection Offset Override", ToolTip = "Overrides the left/right eye projection matrix x-offset, values are in clip space and values less than 0.0f disable the override. Default: -1.0f" ))`
- L589 _public member_ `static TAutoConsoleVariable<float> CVarHMDProjectionOffsetY;`
- L594 _public member_ `float HMDProjectionOffsetY = -1.0f;` — `UPROPERTY(config, EditAnywhere, Category = "XR Streaming", meta = ( DisplayName = "Vertical Projection Offset Override", ToolTip = "Overrides the left-right eye projection matrix y-offset, values are in clip space and values less than 0.0f disable the override. Default: -1.0f" ))`
- L598 _public member_ `static TAutoConsoleVariable<bool> CVarInputAllowConsoleCommands;`
- L603 _public member_ `bool InputAllowConsoleCommands = false;` — `UPROPERTY(config, EditAnywhere, Category = "Input", meta = ( DisplayName = "Allow Commands", ToolTip = "If true browser can send consoleCommand payloads that execute in UE's console. Default: false" ))`
- L605 _public member_ `static TAutoConsoleVariable<FString> CVarInputKeyFilter;`
- L610 _public member_ `FString InputKeyFilter = TEXT("");` — `UPROPERTY(config, EditAnywhere, Category = "Input", meta = ( DisplayName = "Key Filter", ToolTip = "Comma separated list of keys to ignore from streaming clients. Default: \"\"" ))`
- L615 _public member_ `static TAutoConsoleVariable<FString> CVarAllowedOrigins;`
- L620 _public member_ `FString AllowedOrigins = TEXT("htt` — `UPROPERTY(config, EditAnywhere, Category = "SignallingServer", meta = ( DisplayName = "Allowed Origins", ToolTip = "Comma-separated list of allowed origins for WebSocket connection filtering. Supports wildcards (*). Use '*' to allow all origins. Leave empty to disable filtering. Examples: \"*\" or \"https://example.com,http://192.168.0.*:8080\". Default: \"http://127.0.0.1,https://127.0.0.1\"" ))` — 127.0.0.1,https://127.0.0.1");
- L626 _public prototype_ `virtual FName GetCategoryName() const override;`
- L629 _public prototype_ `virtual FText GetSectionText() const override;`
- L631 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L633 _public prototype_ `void VerifyVideoSettings();`
- L638 _public prototype_ `virtual void PostInitProperties() override;`
- L683 _public prototype_ `static FDelegates* Delegates();`
- L686 _private prototype_ `void SetCVarAndPropertyFromValue(const FString& CVarName, FProperty* Property, const FString& Value);`
- L687 _private prototype_ `void SetCVarFromProperty(const FString& CVarName, FProperty* Property);`
- L689 _private prototype_ `void InitializeCVarsFromProperties();`
- L690 _private prototype_ `void ValidateCommandLineArgs();`
- L691 _private prototype_ `void ParseCommandlineArgs();`
- L692 _private prototype_ `void ParseLegacyCommandlineArgs();`
- L694 _private member_ `static FDelegates* DelegateSingleton;`
- L697 _private prototype_ `TArray<FString> GetVideoCodecOptions() const;` — `UFUNCTION()`
- L700 _private prototype_ `TArray<FString> GetScalabilityModeOptions() const;` — `UFUNCTION()`
- L703 _private prototype_ `TArray<FString> GetWebRTCCodecPreferencesOptions() const;` — `UFUNCTION()`
- L706 _private prototype_ `TArray<FString> GetDefaultStreamerTypeOptions() const;` — `UFUNCTION()`

#### struct `UPixelStreaming2PluginSettings::FDelegates`  
`struct FDelegates`  
_L641-681_
- L643 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnScalabilityModeChanged, IConsoleVariable*);`
- L644 _public member_ `FOnScalabilityModeChanged OnScalabilityModeChanged;`
- L646 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSimulcastEnabledChanged, IConsoleVariable*);`
- L647 _public member_ `FOnSimulcastEnabledChanged OnSimulcastEnabledChanged;`
- L649 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnCaptureUseFenceChanged, IConsoleVariable*);`
- L650 _public member_ `FOnCaptureUseFenceChanged OnCaptureUseFenceChanged;`
- L652 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnUseMediaCaptureChanged, IConsoleVariable*);`
- L653 _public member_ `FOnUseMediaCaptureChanged OnUseMediaCaptureChanged;`
- L655 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCFpsChanged, IConsoleVariable*);`
- L656 _public member_ `FOnWebRTCFpsChanged OnWebRTCFpsChanged;`
- L658 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCBitrateChanged, IConsoleVariable*);`
- L659 _public member_ `FOnWebRTCBitrateChanged OnWebRTCBitrateChanged;`
- L661 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCDisableStatsChanged, IConsoleVariable*);`
- L662 _public member_ `FOnWebRTCDisableStatsChanged OnWebRTCDisableStatsChanged;`
- L664 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLogStatsChanged, IConsoleVariable*);`
- L665 _public member_ `FOnLogStatsChanged OnLogStatsChanged;`
- L667 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnInputKeyFilterChanged, IConsoleVariable*);`
- L668 _public member_ `FOnInputKeyFilterChanged OnInputKeyFilterChanged;`
- L670 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEncoderDebugDumpFrameChanged, IConsoleVariable*);`
- L671 _public member_ `FOnEncoderDebugDumpFrameChanged OnEncoderDebugDumpFrameChanged;`
- L673 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnDebugDumpAudioChanged, IConsoleVariable*);`
- L674 _public member_ `FOnDebugDumpAudioChanged OnDebugDumpAudioChanged;`
- L676 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnDecoupleFramerateChanged, IConsoleVariable*);`
- L677 _public member_ `FOnDecoupleFramerateChanged OnDecoupleFramerateChanged;`
- L679 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEpicRtcLogFilterChanged, IConsoleVariable*);`
- L680 _public member_ `FOnEpicRtcLogFilterChanged OnEpicRtcLogFilterChanged;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API PIXELSTREAMING2SETTINGS_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace PixelStreaming2` (scope `UE`)
- L26 _externvar_ `extern FString GSelectedCodec;` (scope `UE::PixelStreaming2`) — This variable exists to back CVarEncoderCodec and should only be used by the FEpicRtcVideo(Encoder/Decoder)Initializer. When doing software fallback, the encoder initializer will set post an async task to set the CVarEncoderCodec. However, we cannot be certain that this task will execute before the decoder initializer reads the cvar again. By having both use this variable, we can be certain that there will be no race conditions between them.
- L29 _function_ `template <typename TEnumType> TEnumType GetEnumFromCVar(const TAutoConsoleVariable<FString>& CVar)` (scope `UE::PixelStreaming2`)
- L37 _function_ `template <typename TEnumType> TEnumType GetEnumFromString(const FString& EnumString)` (scope `UE::PixelStreaming2`)
- L45 _function_ `template <typename TEnumType> FString GetCVarStringFromEnum(TEnumType Value)` (scope `UE::PixelStreaming2`)
- L70 _prototype_ `ENUM_CLASS_FLAGS(EPortAllocatorFlags);`
- L643 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnScalabilityModeChanged, IConsoleVariable*);`
- L646 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSimulcastEnabledChanged, IConsoleVariable*);`
- L649 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnCaptureUseFenceChanged, IConsoleVariable*);`
- L652 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnUseMediaCaptureChanged, IConsoleVariable*);`
- L655 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCFpsChanged, IConsoleVariable*);`
- L658 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCBitrateChanged, IConsoleVariable*);`
- L661 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnWebRTCDisableStatsChanged, IConsoleVariable*);`
- L664 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLogStatsChanged, IConsoleVariable*);`
- L667 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnInputKeyFilterChanged, IConsoleVariable*);`
- L670 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEncoderDebugDumpFrameChanged, IConsoleVariable*);`
- L673 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnDebugDumpAudioChanged, IConsoleVariable*);`
- L676 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnDecoupleFramerateChanged, IConsoleVariable*);`
- L679 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnEpicRtcLogFilterChanged, IConsoleVariable*);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Settings/Private/Logging.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Settings, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelStreaming2Settings, Log, All);`

### `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Settings/Public/PixelStreaming2SettingsEnums.h` (Public)


#### enum `EPixelStreaming2EditorStreamTypes`  
`enum class EPixelStreaming2EditorStreamTypes : uint8`  
_L12-18_
- reflection: `UENUM()`
- desc: @brief The possible stream types Editor Streaming supports.
- L15 _public enumerator_ `LevelEditorViewport = 0` — `LevelEditorViewport` will stream just the level editor
- L17 _public enumerator_ `Editor = 1` — `Editor` will stream the full editor and any of its child windows
