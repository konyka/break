# Plugins / SoundFields

- module root: `Plugins/Runtime/SoundFields/Source/SoundFields`
- headers: 2; symbols: 22
- symbol kinds: class=3, macro=1, member=2, prototype=16
- PrivateDependencyModuleNames: AudioExtensions, CoreUObject, Engine, SignalProcessing, SoundFieldRendering
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/SoundFields/Source/SoundFields/Public/SoundFields.h` (Public)


#### class `UAmbisonicsEncodingSettings`  
`class UAmbisonicsEncodingSettings : public USoundfieldEncodingSettingsBase`  
_L11-24_
- reflection: `UCLASS(MinimalAPI, config = Engine, editinlinenew, BlueprintType)`
- inherits: `USoundfieldEncodingSettingsBase`
- L19 _protected member_ `int32 AmbisonicsOrder;` — `UPROPERTY(EditAnywhere, Category = EncodingSettings, meta=(ClampMin="1", ClampMax="5", UIMin="1", UIMax="5"))`
- L21 _protected prototype_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> GetProxy() const override;`

#### class `FAmbisonicsSoundfieldFormat`  
`class FAmbisonicsSoundfieldFormat : public ISoundfieldFactory`  
_L27-48_
- inherits: `ISoundfieldFactory`
- desc: This is the default format for Ambisonics in the Unreal Audio Engine.
- L30 _public prototype_ `FAmbisonicsSoundfieldFormat();`
- L33 _public prototype_ `virtual ~FAmbisonicsSoundfieldFormat();` — dtor
- L36 _public prototype_ `virtual FName GetSoundfieldFormatName() override;`
- L37 _public prototype_ `virtual TUniquePtr<ISoundfieldEncoderStream> CreateEncoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L38 _public prototype_ `virtual TUniquePtr<ISoundfieldDecoderStream> CreateDecoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L39 _public prototype_ `virtual TUniquePtr<ISoundfieldTranscodeStream> CreateTranscoderStream(const FName SourceFormat, const ISoundfieldEncodingSettingsProxy& InitialSourceSettings, const FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& InitialDestinationSettings, const FAudioPluginInitializationParams& InitInfo) override;`
- L40 _public prototype_ `virtual TUniquePtr<ISoundfieldMixerStream> CreateMixerStream(const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L41 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> CreateEmptyPacket() override;`
- L42 _public prototype_ `virtual bool IsTranscodeRequiredBetweenSettings(const ISoundfieldEncodingSettingsProxy& SourceSettings, const ISoundfieldEncodingSettingsProxy& DestinationSettings) override;`
- L43 _public prototype_ `virtual bool CanTranscodeFromSoundfieldFormat(FName InputFormat, const ISoundfieldEncodingSettingsProxy& InputEncodingSettings) override;`
- L44 _public prototype_ `virtual UClass* GetCustomEncodingSettingsClass() const override;`
- L45 _public prototype_ `virtual USoundfieldEncodingSettingsBase* GetDefaultEncodingSettings() override;`
- L46 _public prototype_ `virtual bool CanTranscodeToSoundfieldFormat(FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& DestinationEncodingSettings) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SOUNDFIELDS_API`

### `Plugins/Runtime/SoundFields/Source/SoundFields/Public/SoundFieldsModule.h` (Public)


#### class `FSoundFieldsModule`  
`class FSoundFieldsModule : public IModuleInterface`  
_L8-17_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `FAmbisonicsSoundfieldFormat SFFactory;`
