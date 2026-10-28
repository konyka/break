# Plugins / CaptureManagerEditorSettings

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings`
- headers: 4; symbols: 127
- symbol kinds: class=8, delegate=1, macro=2, member=47, namespace=7, prototype=52, struct=1, variable=9
- PrivateDependencyModuleNames: CaptureDataConverter, CaptureManagerStyle, ContentBrowser, ContentBrowserData, DeveloperSettings, LiveLinkHubCaptureMessaging, LiveLinkHubExportServer, LiveLinkHubMessaging, LiveLinkInterface, NamingTokens, PropertyEditor, Settings, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: CaptureUtils, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings/Private/CaptureManagerEditorSettingsModule.h` (Private)


#### class `FCaptureManagerEditorSettingsModule`  
`class FCaptureManagerEditorSettingsModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void PostEngineInit();`
- L18 _private prototype_ `void EnginePreExit();`
- L20 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings/Private/Settings/CaptureManagerEditorSettingsCustomization.h` (Private)


#### class `FCaptureManagerEditorSettingsCustomization`  
`class FCaptureManagerEditorSettingsCustomization : public IDetailCustomization`  
_L13-21_
- inherits: `IDetailCustomization`
- desc: Customization for the capture manager editor settings.
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L20 _private prototype_ `FText GetDisplayTokenText(FNamingTokenFilterArgs InArgs) const;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings/Public/Settings/CaptureManagerEditorSettings.h` (Public)


#### class `UCaptureManagerEditorSettings`  
`class UCaptureManagerEditorSettings : public UDeveloperSettings`  
_L23-253_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings, meta = (DisplayName = "Capture Manager"), defaultconfig)`
- inherits: `UDeveloperSettings`
- L28 _public prototype_ `void Initialize();`
- L31 _public prototype_ `TObjectPtr<const UCaptureManagerIngestNamingTokens> GetGeneralNamingTokens() const;` — Get the import naming tokens for Capture Manager Editor.
- L34 _public prototype_ `TObjectPtr<const UCaptureManagerVideoNamingTokens> GetVideoNamingTokens() const;` — Get the video naming tokens for Capture Manager Editor.
- L37 _public prototype_ `TObjectPtr<const UCaptureManagerAudioNamingTokens> GetAudioNamingTokens() const;` — Get the audio naming tokens for Capture Manager Editor.
- L40 _public prototype_ `TObjectPtr<const UCaptureManagerCalibrationNamingTokens> GetCalibrationNamingTokens() const;` — Get the calibration naming tokens for Capture Manager Editor.
- L43 _public prototype_ `TObjectPtr<const UCaptureManagerLensFileNamingTokens> GetLensFileNamingTokens() const;` — Get the calibration lens file naming tokens for Capture Manager Editor.
- L46 _public prototype_ `TObjectPtr<const UCaptureManagerVideoEncoderTokens> GetVideoEncoderNamingTokens() const;` — Get the video encoder naming tokens for Capture Manager Editor.
- L49 _public prototype_ `TObjectPtr<const UCaptureManagerAudioEncoderTokens> GetAudioEncoderNamingTokens() const;` — Get the audio encoder naming tokens for Capture Manager Editor.
- L56 _public prototype_ `static UCaptureManagerEditorSettings* GetCaptureManagerEditorSettings();` — `UFUNCTION(BlueprintPure, Category = "Capture Manager|Settings")` — Get the Capture Manager Editor settings uobject @return Settings Object.
- L62 _public prototype_ `void SetMediaDirectory(const FDirectoryPath& InMediaDirectory);` — `UFUNCTION(BlueprintCallable, Category = "Capture Manager|Settings", meta = (DisplayName = "Set Media Directory"))` — Set the Media Directory in Capture Manager Editor Settings
- L70 _public prototype_ `void SetImportDirectory(const FDirectoryPath& InImportDirectory);` — `UFUNCTION(BlueprintCallable, Category = "Capture Manager|Settings", meta = (DisplayName = "Set Import Directory", ToolTip = "Sets the Content Browser location where imported assets will be created. Must be within the project's Content folder (e.g. /Game/CaptureManager/Imports)."))` — Set the Import Directory in Capture Manager Editor Settings. Must be a valid UE package path not in a read-only content root (e.g. /Engine, /Script, /Temp). Plugin content roots and UEFN roots such as /VerseDevices are accepted.
- L76 _public member_ `FDirectoryPath MediaDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Import")` — Location to store ingested media data.
- L82 _public member_ `FDirectoryPath ImportDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Import", meta = (ContentDir, RelativeToGameContentDir, ToolTip = "Content Browser location where assets will be created. Must point to a directory within the project's Content folder (e.g. /Game/CaptureManager/Imports)."))` — Content Browser location where assets will be created.
- L86 _public member_ `bool bAutoSaveAssets = true;` — `UPROPERTY(config, EditAnywhere, Category = "Import")` — Option to automatically save the assets after the ingest process.
- L90 _public member_ `FString CaptureDataAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import")` — Name for created Capture Data assets.
- L94 _public member_ `FString ImageSequenceAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Video")` — Name for created Image Media Source video assets.
- L98 _public member_ `FString DepthSequenceAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Video")` — Name for created Image Media Source depth assets.
- L102 _public member_ `FText VideoTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Video")` — Tokens compatible with video properties.
- L106 _public member_ `FString SoundwaveAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Audio")` — Name for created Soundwave assets.
- L110 _public member_ `FText AudioTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Audio")` — Tokens compatible with audio properties.
- L114 _public member_ `FString CalibrationAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Calibration")` — Name for created Camera Calibration assets.
- L118 _public member_ `FText CalibrationTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Calibration")` — Tokens compatible with calibration properties.
- L122 _public member_ `FString LensFileAssetName;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Calibration")` — Name for created Lens File assets.
- L126 _public member_ `FText LensFileTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Import|Calibration")` — Tokens compatible with calibration properties.
- L133 _public member_ `int32 MaxConcurrentIngests = 2;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (DisplayName = "Max Concurrent Ingests", UIMin = 1, ClampMin = 1, UIMax = 8, ClampMax = 8))` — Maximum number of ingest jobs allowed to run concurrently from Blueprint/script. Higher values increase throughput on fast storage but raise CPU and disk I/O pressure. If using a third-party encoder, each slot may spawn a separate encoder process.
- L137 _public member_ `bool bEnableThirdPartyEncoder = false;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (DisplayName = "Use Third Party Encoder"))` — Option to enable a third party encoder instead of the engine media readers and writers.
- L142 _public member_ `FFilePath ThirdPartyEncoder;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (DisplayName = "Third Party Encoder Path", EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Location to the third party encoder executable.
- L147 _public member_ `FString CustomVideoCommandArguments;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Custom video command arguments for the third party encoder. Leave empty to use the default arguments.
- L152 _public member_ `FString CustomAudioCommandArguments;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Custom audio command arguments for the third party encoder. Leave empty to use the default arguments.
- L157 _public member_ `FText VideoCommandTokens;` — `UPROPERTY(VisibleAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Tokens compatible with video command arguments.
- L162 _public member_ `FText AudioCommandTokens;` — `UPROPERTY(VisibleAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Tokens compatible with audio command arguments.
- L166 _public member_ `bool bLaunchIngestServerOnLiveLinkHubConnection = true;` — `UPROPERTY(config, EditAnywhere, Category = "Ingest Server")` — Option to launch the Ingest Server when a Live Link Hub connection is made.
- L170 _public member_ `uint16 IngestServerPort = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Ingest Server")` — Option to choose a listening port for the Ingest Server. Leave 0 for automatic selection of the port.
- L174 _public member_ `FText ImportTokens;` — `UPROPERTY(VisibleAnywhere, Category = "Import")` — Tokens compatible with import properties
- L178 _public member_ `FText GlobalTokens;` — `UPROPERTY(VisibleAnywhere, Category = "Templates")` — Global tokens.
- L181 _public prototype_ `FString GetVerifiedImportDirectory();` — Returns verified import directory. Avoid accessing Import Directory property directly.
- L185 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCaptureManagerEditorSettingsChanged);`
- L189 _public member_ `FOnCaptureManagerEditorSettingsChanged OnCaptureManagerEditorSettingsChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Capture Manager|Settings")` — Multicast delegate called whenever Capture Manager Editor settings are modified.
- L194 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L196 _private prototype_ `FString GetBaseImportDirectory() const;`
- L197 _private prototype_ `void ResetImportDirectory();`
- L198 _private prototype_ `void InitializeValuesIfNotSet();`
- L201 _private prototype_ `void OnHubConnectionEstablished(FGuid SourceId);` — Handler used to update the connection state and source id when a connection with a hub instance is established.
- L204 _private prototype_ `void CheckHubConnection();` — Check whether the hub connection is still active.
- L207 _private prototype_ `bool StartIngestServer();` — Start the ingest server
- L214 _private member_ `TObjectPtr<UCaptureManagerIngestNamingTokens> GeneralNamingTokens;` — `UPROPERTY(Instanced, Transient)` — Naming tokens for Capture Manager Editor, instantiated each load based on the naming tokens class. This isn't serialized to the config file, and exists here for singleton-like access.
- L217 _private member_ `TObjectPtr<UCaptureManagerVideoNamingTokens> VideoNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L220 _private member_ `TObjectPtr<UCaptureManagerAudioNamingTokens> AudioNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L223 _private member_ `TObjectPtr<UCaptureManagerCalibrationNamingTokens> CalibrationNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L226 _private member_ `TObjectPtr<UCaptureManagerLensFileNamingTokens> LensFileNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L229 _private member_ `TObjectPtr<UCaptureManagerVideoEncoderTokens> VideoEncoderNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L232 _private member_ `TObjectPtr<UCaptureManagerAudioEncoderTokens> AudioEncoderNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L234 _private member_ `class ILiveLinkHubMessagingModule* HubMessagingModule;`
- L237 _private member_ `class ILiveLinkClient* LiveLinkClient = nullptr;` — LiveLink client used to retrieve the status of the hub connection.
- L240 _private member_ `TArray<FGuid> DetectedHubsArray;` — Cached list of detected LLH instance ids.
- L243 _private member_ `FTimerHandle TimerHandle;` — Handle to the timer responsible for triggering CheckHubConnection.
- L246 _private member_ `static constexpr float CheckConnectionIntervalSeconds = 1.0f;` — Interval of the timer to check for connection validity.
- L249 _private member_ `FString CachedBaseImportDirectory;` — Cached base of the import directory. The base directory differs when used in UE or UEFN
- L252 _private member_ `bool bInProgrammaticSetter = false;` — Flag when properties are being set programmatically

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREMANAGEREDITORSETTINGS_API`
- L185 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCaptureManagerEditorSettingsChanged);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings/Public/Settings/CaptureManagerEditorTemplateTokens.h` (Public)


#### struct `UE::CaptureManager::FIngestToken`  
`struct FIngestToken`  
_L14-18_
- L16 _public member_ `FString Name;`
- L17 _public member_ `FText Description;`

#### class `UCaptureManagerIngestNamingTokens`  
`class UCaptureManagerIngestNamingTokens final : public UNamingTokens`  
_L51-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- L56 _public prototype_ `UCaptureManagerIngestNamingTokens();`
- L58 _public prototype_ `UE::CaptureManager::FIngestToken GetToken(const FString& InKey) const;`
- L62 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L63 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L64 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L68 _private member_ `TMap<FString, UE::CaptureManager::FIngestToken> IngestGeneralTokens;`

#### class `UCaptureManagerVideoNamingTokens`  
`class UCaptureManagerVideoNamingTokens final : public UNamingTokens`  
_L72-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- L77 _public prototype_ `UCaptureManagerVideoNamingTokens();`
- L79 _public prototype_ `UE::CaptureManager::FIngestToken GetToken(const FString& InKey) const;`
- L83 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L84 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L85 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L89 _private member_ `TMap<FString, UE::CaptureManager::FIngestToken> IngestVideoTokens;`

#### class `UCaptureManagerAudioNamingTokens`  
`class UCaptureManagerAudioNamingTokens final : public UNamingTokens`  
_L93-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- L98 _public prototype_ `UCaptureManagerAudioNamingTokens();`
- L100 _public prototype_ `UE::CaptureManager::FIngestToken GetToken(const FString& InKey) const;`
- L104 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L105 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L106 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L110 _private member_ `TMap<FString, UE::CaptureManager::FIngestToken> IngestAudioTokens;`

#### class `UCaptureManagerCalibrationNamingTokens`  
`class UCaptureManagerCalibrationNamingTokens final : public UNamingTokens`  
_L114-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- L119 _public prototype_ `UCaptureManagerCalibrationNamingTokens();`
- L121 _public prototype_ `UE::CaptureManager::FIngestToken GetToken(const FString& InKey) const;`
- L125 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L126 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L127 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L131 _private member_ `TMap<FString, UE::CaptureManager::FIngestToken> IngestCalibTokens;`

#### class `UCaptureManagerLensFileNamingTokens`  
`class UCaptureManagerLensFileNamingTokens final : public UNamingTokens`  
_L135-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNamingTokens`
- L140 _public prototype_ `UCaptureManagerLensFileNamingTokens();`
- L142 _public prototype_ `UE::CaptureManager::FIngestToken GetToken(const FString& InKey) const;`
- L146 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L147 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L148 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L152 _private member_ `TMap<FString, UE::CaptureManager::FIngestToken> IngestLensFileTokens;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGEREDITORSETTINGS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)
- L20 _namespace_ `namespace GeneralTokens` (scope `UE::CaptureManager`)
- L22 _variable_ `static constexpr FStringView IdKey = TEXTVIEW("id"` (scope `UE::CaptureManager::GeneralTokens`)
- L23 _variable_ `static constexpr FStringView DeviceKey = TEXTVIEW("dev` (scope `UE::CaptureManager::GeneralTokens`)
- L24 _variable_ `static constexpr FStringView SlateKey = TEXTVIEW("sla` (scope `UE::CaptureManager::GeneralTokens`)
- L25 _variable_ `static constexpr FStringView TakeKey = TEXTVIEW("tak` (scope `UE::CaptureManager::GeneralTokens`)
- L28 _namespace_ `namespace VideoTokens` (scope `UE::CaptureManager`)
- L30 _variable_ `static constexpr FStringView NameKey = TEXTVIEW("nam` (scope `UE::CaptureManager::VideoTokens`)
- L31 _variable_ `static constexpr FStringView FrameRateKey = TEXTVIEW("fra` (scope `UE::CaptureManager::VideoTokens`)
- L34 _namespace_ `namespace AudioTokens` (scope `UE::CaptureManager`)
- L36 _variable_ `static constexpr FStringView NameKey = TEXTVIEW("nam` (scope `UE::CaptureManager::AudioTokens`)
- L39 _namespace_ `namespace CalibTokens` (scope `UE::CaptureManager`)
- L41 _variable_ `static constexpr FStringView NameKey = TEXTVIEW("nam` (scope `UE::CaptureManager::CalibTokens`)
- L44 _namespace_ `namespace LensFileTokens` (scope `UE::CaptureManager`)
- L46 _variable_ `static constexpr FStringView CameraNameKey = TEXTVIEW("cam` (scope `UE::CaptureManager::LensFileTokens`)
