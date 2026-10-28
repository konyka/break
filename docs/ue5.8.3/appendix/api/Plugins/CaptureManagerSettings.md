# Plugins / CaptureManagerSettings

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings`
- headers: 4; symbols: 50
- symbol kinds: class=4, member=19, namespace=3, prototype=19, struct=1, variable=4
- PrivateDependencyModuleNames: CaptureDataConverter, CaptureUtils, Engine, NamingTokens, PropertyEditor, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings/Private/CaptureManagerSettingsModule.h` (Private)


#### class `FCaptureManagerSettingsModule`  
`class FCaptureManagerSettingsModule : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private prototype_ `void PostEngineInit();`
- L16 _private prototype_ `void EnginePreExit();`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings/Private/Settings/CaptureManagerSettingsCustomization.h` (Private)


#### class `FCaptureManagerSettingsCustomization`  
`class FCaptureManagerSettingsCustomization : public IDetailCustomization`  
_L13-21_
- inherits: `IDetailCustomization`
- desc: Customization for the capture manager settings.
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L20 _private prototype_ `FText GetDisplayTokenText(FNamingTokenFilterArgs InArgs) const;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings/Public/Settings/CaptureManagerSettings.h` (Public)


#### class `UCaptureManagerSettings`  
`class UCaptureManagerSettings : public UObject`  
_L17-112_
- reflection: `UCLASS(config = Editor, defaultconfig)`
- inherits: `UObject`
- L22 _public prototype_ `UCaptureManagerSettings(const FObjectInitializer& InObjectInitializer);`
- L25 _public prototype_ `TObjectPtr<UCaptureManagerGeneralTokens> GetGeneralNamingTokens() const;` — Get the general naming tokens for Capture Manager.
- L28 _public prototype_ `TObjectPtr<UCaptureManagerVideoEncoderTokens> GetVideoEncoderNamingTokens() const;` — Get the video encoder naming tokens for Capture Manager.
- L31 _public prototype_ `TObjectPtr<UCaptureManagerAudioEncoderTokens> GetAudioEncoderNamingTokens() const;` — Get the audio encoder naming tokens for Capture Manager.
- L35 _public member_ `FDirectoryPath DefaultWorkingDirectory;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion")` — Default location to where the converted data will be stored. It can be overriden when configuring the Ingest Job.
- L39 _public member_ `bool bShouldCleanWorkingDirectory = true;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion")` — Option to clean the converted data after the Ingest process.
- L43 _public member_ `FDirectoryPath DownloadDirectory;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion")` — Location where the take data downloaded from the device will be stored.
- L47 _public member_ `bool bEnableThirdPartyEncoder = false;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (DisplayName = "Use Third Party Encoder"))` — Option to enable a third party encoder instead of the engine media readers and writers.
- L52 _public member_ `FFilePath ThirdPartyEncoder;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (DisplayName = "Third Party Encoder Path", EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Path to the third party encoder executable.
- L59 _public member_ `FString CustomVideoCommandArguments;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Custom video command arguments to be used for executing the third party encoder. NOTE: Leave empty to use the arguments generated from the Job settings.
- L64 _public member_ `FText VideoCommandTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Tokens compatible with video command properties.
- L71 _public member_ `FString CustomAudioCommandArguments;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Custom audio command arguments to be used for executing the third party encoder. NOTE: Leave empty to use the arguments generated from the Job settings.
- L76 _public member_ `FText AudioCommandTokens;` — `UPROPERTY(config, EditAnywhere, Category = "Conversion", meta = (EditCondition = "bEnableThirdPartyEncoder", EditConditionHides))` — Tokens compatible with audio command properties.
- L80 _public member_ `FText GeneralTokens;` — `UPROPERTY(VisibleAnywhere, Category = "Templates")` — General tokens
- L84 _public member_ `FString DefaultUploadHostName;` — `UPROPERTY(config, EditAnywhere, Category = "Upload")` — The default host to target when uploading to an Unreal client (defaults to the local host if left empty)
- L88 _public member_ `int32 NumIngestExecutors = 2;` — `UPROPERTY(config, EditAnywhere, Category = "General", meta = (DisplayName = "Parallel Jobs", UIMin = 1, ClampMin = 1, UIMax = 8, ClampMax = 8))` — The number of jobs to run in parallel. Requires a restart of Live Link Hub (Warning: Setting this too high could cause issues)
- L92 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L93 _private prototype_ `virtual void PostInitProperties() override;`
- L95 _private prototype_ `void InitializeValuesIfNotSet();`
- L102 _private member_ `TObjectPtr<UCaptureManagerGeneralTokens> GeneralNamingTokens;` — `UPROPERTY(Instanced, Transient)` — Naming tokens for Capture Manager, instantiated each load based on the naming tokens class. This isn't serialized to the config file, and exists here for singleton-like access.
- L105 _private member_ `TObjectPtr<UCaptureManagerVideoEncoderTokens> VideoEncoderNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L108 _private member_ `TObjectPtr<UCaptureManagerAudioEncoderTokens> AudioEncoderNamingTokens;` — `UPROPERTY(Instanced, Transient)`
- L110 _private member_ `FString LocalHostName;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings/Public/Settings/CaptureManagerTemplateTokens.h` (Public)


#### struct `UE::CaptureManager::FArchiveToken`  
`struct FArchiveToken`  
_L11-15_
- L13 _public member_ `FString Name;`
- L14 _public member_ `FText Description;`

#### class `UCaptureManagerGeneralTokens`  
`class UCaptureManagerGeneralTokens final : public UNamingTokens`  
_L28-46_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UNamingTokens`
- L33 _public prototype_ `UCaptureManagerGeneralTokens();`
- L35 _public prototype_ `UE::CaptureManager::FArchiveToken GetToken(const FString& InKey) const;`
- L39 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& OutTokens) override;`
- L40 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L41 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L45 _private member_ `TMap<FString, UE::CaptureManager::FArchiveToken> GeneralTokens;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L17 _namespace_ `namespace GeneralTokens` (scope `UE::CaptureManager`)
- L19 _variable_ `static constexpr FStringView IdKey = TEXTVIEW("id"` (scope `UE::CaptureManager::GeneralTokens`)
- L20 _variable_ `static constexpr FStringView DeviceKey = TEXTVIEW("dev` (scope `UE::CaptureManager::GeneralTokens`)
- L21 _variable_ `static constexpr FStringView SlateKey = TEXTVIEW("sla` (scope `UE::CaptureManager::GeneralTokens`)
- L22 _variable_ `static constexpr FStringView TakeKey = TEXTVIEW("tak` (scope `UE::CaptureManager::GeneralTokens`)
