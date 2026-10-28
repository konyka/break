# Editor / AudioEditor

- module root: `Source/Editor/AudioEditor`
- headers: 71; symbols: 1022
- symbol kinds: class=99, delegate=2, enum=2, enumerator=6, externvar=1, function=159, macro=12, member=160, namespace=6, prototype=547, struct=16, typedef=4, variable=8
- PrivateDependencyModuleNames: AudioExtensions, AudioLinkEngine, DeveloperSettings, EditorSubsystem, GameProjectGeneration, ToolMenus, ToolWidgets, UMG, UMGEditor
- PrivateIncludePathModuleNames: AssetTools, WorkspaceMenuStructure
- PublicDependencyModuleNames: ApplicationCore, AssetDefinition, AudioMixer, ClassViewer, ContentBrowser, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, GraphEditor, InputCore, Kismet, Landscape, LevelEditor, PropertyEditor, RenderCore, SignalProcessing, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: UELibSampleRate

### `Source/Editor/AudioEditor/Classes/AudioEditorPerProjectUserSettings.h` (Public)


#### enum `EUseTemplateSoundWaveDuringAssetImport`  
`enum class EUseTemplateSoundWaveDuringAssetImport : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `AlwaysPrompt = 0`
- L13 _public enumerator_ `AlwaysUse = 1`
- L14 _public enumerator_ `NeverUse = 2`

#### class `UAudioEditorPerProjectUserSettings`  
`class UAudioEditorPerProjectUserSettings : public UDeveloperSettings`  
_L18-31_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings, meta = (DisplayName = "Audio Editor Per Project Settings"))`
- inherits: `UDeveloperSettings`
- L25 _public member_ `EUseTemplateSoundWaveDuringAssetImport UseTemplateSoundWaveDuringAssetImport = EUseTemplateSoundWaveDuringAssetImport::NeverUse;` — `UPROPERTY(EditAnywhere, config, Category = AssetImport)` — Whether to use the selected Sound Wave in the Content Browser as a template for sound(s) being imported.
- L28 _public function_ `virtual FName GetCategoryName() const override`

### `Source/Editor/AudioEditor/Classes/AudioEditorSettings.h` (Public)


#### struct `FAudioPlatform`  
`struct FAudioPlatform`  
_L30-51_
- reflection: `USTRUCT()`
- L35 _public member_ `FString DisplayName;` — `UPROPERTY(config)`
- L38 _public member_ `FString ModuleName;` — `UPROPERTY(config)`
- L40 _public prototype_ `FAudioPlatform() = default;`
- L42 _public function_ `FAudioPlatform(const FString& InDisplayName, const FString& InModuleName) : DisplayName(InDisplayName) , ModuleName(InModuleName)`
- L47 _public function_ `bool operator<(const FAudioPlatform& Other) const`

#### class `UAudioEditorSettings`  
`class UAudioEditorSettings : public UDeveloperSettings`  
_L54-132_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings, meta = (DisplayName = "Audio"))`
- inherits: `UDeveloperSettings`
- L62 _protected member_ `bool bUseAudioAttenuation = true;` — `UPROPERTY(EditAnywhere, config, Category = NonGameWorld)` — Whether or not should Audio Attenuation be used by default, for Non-Game Worlds
- L67 _public member_ `bool bPinSoundCueInAssetMenu = true;` — `UPROPERTY(EditAnywhere, config, Category = AssetMenu, meta = (ConfigRestartRequired = true))` — Whether to pin the Sound Cue asset type when creating new assets. Requires editor restart to take effect.
- L71 _public member_ `bool bPinSoundCueTemplateInAssetMenu = false;` — `UPROPERTY(EditAnywhere, config, Category = AssetMenu, meta = (ConfigRestartRequired = true))` — Whether to pin the Sound Cue Template asset type when creating new assets. Requires editor restart to take effect.
- L75 _public member_ `bool bPinSoundAttenuationInAssetMenu = true;` — `UPROPERTY(EditAnywhere, config, Category = AssetMenu, meta = (ConfigRestartRequired = true))` — Whether to pin the Sound Attenuation asset type when creating new assets. Requires editor restart to take effect.
- L79 _public member_ `bool bPinSoundConcurrencyInAssetMenu = true;` — `UPROPERTY(EditAnywhere, config, Category = AssetMenu, meta = (ConfigRestartRequired = true))` — Whether to pin the Sound Concurrency asset type when creating new assets. Requires editor restart to take effect.
- L83 _public member_ `FString AudioMixerModuleName;` — `UPROPERTY(EditAnywhere, config, Category = AudioOutputDevice, DisplayName = "Platform Audio API", meta = (ConfigRestartRequired = true))` — The device id of the currently selected audio output device. Requires editor restart to take effect
- L87 _public member_ `bool bUseSystemDevice = true;` — `UPROPERTY(EditAnywhere, config, Category = AudioOutputDevice, DisplayName = "Use System Default Audio Device")` — Use current audio playback device selected in the operating system.
- L91 _public member_ `FString AudioOutputDeviceId;` — `UPROPERTY(EditAnywhere, config, Category = AudioOutputDevice)` — The device id of the currently selected audio output device.
- L95 _public member_ `TArray<FAudioPlatform> AudioMixerPlatforms;` — `UPROPERTY(config)` — Array of available audio platforms.
- L99 _public member_ `bool bUseSubmixesForPreviewSound = true;` — `UPROPERTY(EditAnywhere, config, Category = EditorPlaybackOptions, DisplayName = "Use Submixes When Previewing Sounds")` — Use the submix tree when playing preview sounds
- L103 _public member_ `FName MenuPosition = "La` — `UPROPERTY(EditAnywhere, config, Category = AssetActionMenu, meta = (GetOptions = "AudioEditor.AudioEditorSettings.GetAllowedMenuPositions"))` — Specify placement of sound menus when right-clicking on sound asset types in Content Browser (ex. 'Last' will sort to bottom, 'First' to top).
- L106 _public prototype_ `void SetUseAudioAttenuation(bool bInUseAudioAttenuation);` — Set and apply, whether audio attenuation is used for non-game worlds
- L109 _public function_ `bool IsUsingAudioAttenuation() const` — Is audio attenuation used for non-game worlds
- L112 _public function_ `virtual FName GetCategoryName() const override`
- L116 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L117 _public prototype_ `virtual void PostInitProperties() override;`
- L120 _public prototype_ `void RebuildSoundContextMenuSections() const;`
- L123 _public prototype_ `static TArray<FName> GetAllowedMenuPositions();` — `UFUNCTION()`
- L128 _private prototype_ `void ApplyAttenuationForAllAudioDevices();` — Apply non-game world attenuation setting for all AudioDevices.
- L131 _private prototype_ `void ApplyAttenuationForAudioDevice(Audio::FDeviceId InDeviceID);` — Apply non-game world attenuation setting for AudioDevice with given ID.

#### class `FAudioOutputDeviceCustomization`  
`class FAudioOutputDeviceCustomization : public IDetailCustomization`  
_L134-176_
- inherits: `IDetailCustomization`
- L137 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L139 _public prototype_ `FAudioOutputDeviceCustomization();`
- L143 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L146 _public prototype_ `static bool IsDeviceSettingsEnabled();`
- L149 _private member_ `TSharedPtr<IPropertyHandle> AudioPlatformPropertyHandle;`
- L150 _private member_ `TSharedPtr<IPropertyHandle> UseSystemDevicePropertyHandle;`
- L151 _private member_ `TSharedPtr<IPropertyHandle> AudioDeviceIdPropertyHandle;`
- L152 _private member_ `TSharedPtr<SWidget> DeviceListComboButton;`
- L153 _private member_ `FString CurrentDeviceName;`
- L154 _private member_ `TWeakPtr<FActiveTimerHandle> DeviceMenuActiveTimer;`
- L155 _private member_ `FTickerDelegate TickDelegate;`
- L156 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;`
- L157 _private member_ `TArray<FAudioPlatform> AudioMixerPlatforms;`
- L158 _private member_ `TArray<TSharedPtr<FString>> AudioBackends;`
- L159 _private member_ `TSharedPtr<FString> CurrentBackendName;`
- L161 _private prototype_ `static TArray<Audio::FAudioPlatformDeviceInfo> GetAvailableAudioOutputDevices();`
- L162 _private prototype_ `static Audio::FAudioPlatformDeviceInfo GetDeviceInfo(const FString& InDeviceId);`
- L163 _private prototype_ `static TOptional<Audio::FAudioPlatformDeviceInfo> FindDefaultOutputDevice();`
- L164 _private prototype_ `static FString GetDeviceNameForDeviceId(const FString& InDeviceId);`
- L165 _private prototype_ `static FString GetCurrentAudioMixerDeviceName();`
- L166 _private prototype_ `static void SetIsListeningForDeviceEvents(bool bInListeningForDeviceEvents);`
- L167 _private prototype_ `static void RequestDeviceSwap(const FString& InDeviceId);`
- L168 _private prototype_ `static bool IsAggregateHardwareDeviceId(const FString& InDeviceId);`
- L170 _private prototype_ `void AddPlatformRow(IDetailCategoryBuilder& Category, const IDetailLayoutBuilder& DetailLayout);`
- L171 _private prototype_ `TSharedRef<SWidget> OnGenerateDeviceMenu();`
- L172 _private prototype_ `void MenuItemDeviceSelected(Audio::FAudioPlatformDeviceInfo InDeviceInfo);`
- L173 _private prototype_ `bool Tick(float DeltaTime);`
- L174 _private prototype_ `TSharedPtr<FString> GetCurrentBackendName() const;`
- L175 _private prototype_ `void SetCurrentBackendName(const FString& InBackendName);`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API AUDIOEDITOR_API`
- L21 _namespace_ `namespace Audio`

### `Source/Editor/AudioEditor/Classes/Factories/AudioBusFactory.h` (Public)


#### class `UAudioBusFactory`  
`class UAudioBusFactory : public UFactory`  
_L20-28_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L26 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Source/Editor/AudioEditor/Classes/Factories/DialogueVoiceFactory.h` (Public)


#### class `UDialogueVoiceFactory`  
`class UDialogueVoiceFactory : public UFactory`  
_L22-29_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/DialogueWaveFactory.h` (Public)


#### class `UDialogueWaveFactory`  
`class UDialogueWaveFactory : public UFactory`  
_L25-48_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L30 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L35 _private member_ `TObjectPtr<class USoundWave> InitialSoundWave;` — `UPROPERTY()` — An initial sound wave to place in the newly created dialogue wave
- L39 _private member_ `TObjectPtr<class UDialogueVoice> InitialSpeakerVoice;` — `UPROPERTY()` — An initial speaking dialogue voice to place in the newly created dialogue wave
- L43 _private member_ `bool HasSetInitialTargetVoice;` — `UPROPERTY()` — Whether an initial target dialogue voice should be set
- L47 _private member_ `TArray<TObjectPtr<UDialogueVoice>> InitialTargetVoices;` — `UPROPERTY()` — An initial target dialogue voices to place in the newly created dialogue wave

### `Source/Editor/AudioEditor/Classes/Factories/ReimportSoundFactory.h` (Public)


#### class `UReimportSoundFactory`  
`class UReimportSoundFactory : public USoundFactory, public FReimportHandler`  
_L23-39_
- reflection: `UCLASS(hidecategories=Object, collapsecategories)`
- inherits: `USoundFactory,FReimportHandler`
- L28 _private prototype_ `virtual bool CanReimport( UObject* Obj, TArray<FString>& OutFilenames ) override;`
- L29 _private prototype_ `virtual void SetReimportPaths( UObject* Obj, const TArray<FString>& NewReimportPaths ) override;`
- L30 _private prototype_ `virtual EReimportResult::Type Reimport( UObject* Obj ) override;`
- L31 _private prototype_ `virtual int32 GetPriority() const override;`
- L35 _private prototype_ `virtual void CleanUp() override;`
- L38 _private member_ `int8 OverwriteOtherAssetTypes;`

### `Source/Editor/AudioEditor/Classes/Factories/ReverbEffectFactory.h` (Public)


#### class `UReverbEffectFactory`  
`class UReverbEffectFactory : public UFactory`  
_L22-29_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundAttenuationFactory.h` (Public)


#### class `USoundAttenuationFactory`  
`class USoundAttenuationFactory : public UFactory`  
_L22-29_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundClassFactory.h` (Public)


#### class `USoundClassFactory`  
`class USoundClassFactory : public UFactory`  
_L22-30_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L28 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundConcurrencyFactory.h` (Public)


#### class `USoundConcurrencyFactory`  
`class USoundConcurrencyFactory : public UFactory`  
_L22-29_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundCueFactoryNew.h` (Public)


#### class `USoundCueFactoryNew`  
`class USoundCueFactoryNew : public UFactory`  
_L31-59_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L36 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L41 _private member_ `TObjectPtr<USoundWave> InitialSoundWave;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Array InitialSoundWaves instead."))` — Initial sound wave to place in the newly created cue
- L45 _private member_ `TArray<TWeakObjectPtr<USoundWave>> InitialSoundWaves;` — `UPROPERTY(EditAnywhere, Category = Audio)` — Initial sound wave(s) to place in the newly created cue(s)
- L49 _private member_ `TObjectPtr<UDialogueWave> InitialDialogueWave;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Array InitialDialogueWaves instead."))` — An initial dialogue wave to place in the newly created cue
- L53 _private member_ `TArray<TWeakObjectPtr<UDialogueWave>> InitialDialogueWaves;` — `UPROPERTY(EditAnywhere, Category = Audio)` — Initial dialogue wave(s) to place in the newly created cue(s)
- L57 _protected prototype_ `static USoundNodeRandom* InsertRandomNode(USoundCue* SoundCue, int32 NodePosX, int32 NodePosY);`
- L58 _protected prototype_ `static USoundNode* CreateSoundPlayerNode(USoundCue* SoundCue, UObject* SoundObject, int32 NodePosX, int32 NodePosY);`

### `Source/Editor/AudioEditor/Classes/Factories/SoundFactory.h` (Public)


#### class `USoundFactory`  
`class USoundFactory : public UFactory`  
_L26-81_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L32 _private member_ `uint32 bAutoCreateCue:1;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="If enabled, a sound cue will automatically be created for the sound"))` — If enabled, a sound cue will automatically be created for the sound
- L36 _private member_ `uint32 bIncludeAttenuationNode:1;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="If enabled, the created sound cue will include a attenuation node"))` — If enabled, the created sound cue will include a attenuation node
- L40 _private member_ `uint32 bIncludeLoopingNode:1;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="If enabled, the created sound cue will include a looping node"))` — If enabled, the created sound cue will include a looping node
- L44 _private member_ `uint32 bIncludeModulatorNode:1;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="If enabled, the created sound cue will include a modulator node"))` — If enabled, the created sound cue will include a modulator node
- L48 _private member_ `float CueVolume;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="The volume of the created sound cue"))` — The volume of the created sound cue
- L52 _private member_ `FString CuePackageSuffix;` — `UPROPERTY(EditAnywhere, Category=SoundFactory, meta=(ToolTip="If not empty, generated SoundCues will be placed in PackageCuePackageSuffix, but only if bAutoCreateCue is true"))` — If not empty, imported waves will be placed in PackageCuePackageSuffix, but only if bAutoCreateCue is true.
- L55 _private prototype_ `virtual UObject* FactoryCreateBinary( UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* FileType, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn ) override;`
- L58 _private member_ `uint8 SuppressImportDialogOptions;`
- L62 _public prototype_ `void SuppressImportDialogs();` — Suppresses all dialogs pertaining to importing using factory
- L64 _public prototype_ `virtual void CleanUp() override;`
- L75 _private prototype_ `void UpdateTemplate();`
- L77 _private member_ `TWeakObjectPtr<USoundWave> TemplateSoundWave;`
- L80 _private prototype_ `UObject* CreateObject(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* FileType, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn);`

#### enum `USoundFactory::ESuppressImportDialog`  
`enum ESuppressImportDialog`  
_L67-72_
- L69 _public enumerator_ `None = 0`
- L70 _public enumerator_ `Overwrite = 1 << 0`
- L71 _public enumerator_ `UseTemplate = 1 << 1`

### `Source/Editor/AudioEditor/Classes/Factories/SoundMixFactory.h` (Public)


#### class `USoundMixFactory`  
`class USoundMixFactory : public UFactory`  
_L18-26_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L24 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundSourceBusFactory.h` (Public)


#### class `USoundSourceBusFactory`  
`class USoundSourceBusFactory : public UFactory`  
_L20-28_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L26 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundSourceEffectFactory.h` (Public)


#### class `USoundSourceEffectFactory`  
`class USoundSourceEffectFactory : public UFactory`  
_L20-33_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L26 _private member_ `TSubclassOf<USoundEffectSourcePreset> SoundEffectSourcepresetClass;` — `UPROPERTY(EditAnywhere, Category = CurveFactory)` — The type of sound source effect preset that will be created
- L29 _private prototype_ `virtual bool ConfigureProperties() override;`
- L30 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L31 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `USoundSourceEffectChainFactory`  
`class USoundSourceEffectChainFactory : public UFactory`  
_L36-44_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L41 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L42 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundSubmixEffectFactory.h` (Public)


#### class `USoundSubmixEffectFactory`  
`class USoundSubmixEffectFactory : public UFactory`  
_L20-33_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L26 _private member_ `TSubclassOf<USoundEffectSubmixPreset> SoundEffectSubmixPresetClass;` — `UPROPERTY(EditAnywhere, Category = CurveFactory)` — The type of sound source effect preset that will be created
- L29 _private prototype_ `virtual bool ConfigureProperties() override;`
- L30 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context, FFeedbackContext* Warn) override;`
- L31 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Source/Editor/AudioEditor/Classes/Factories/SoundSubmixFactory.h` (Public)


#### class `USoundSubmixFactory`  
`class USoundSubmixFactory : public UFactory`  
_L22-30_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`
- L28 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `USoundfieldSubmixFactory`  
`class USoundfieldSubmixFactory: public UFactory`  
_L33-41_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L38 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L39 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `UEndpointSubmixFactory`  
`class UEndpointSubmixFactory : public UFactory`  
_L44-52_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L49 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L50 _private prototype_ `virtual bool CanCreateNew() const override;`

#### class `USoundfieldEndpointSubmixFactory`  
`class USoundfieldEndpointSubmixFactory : public UFactory`  
_L55-63_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L60 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L61 _private prototype_ `virtual bool CanCreateNew() const override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Classes/SoundClassGraph/SoundClassGraph.h` (Public)


#### class `USoundClassGraph`  
`class USoundClassGraph : public UEdGraph`  
_L20-126_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L27 _private prototype_ `void SetRootSoundClass(class USoundClass* InSoundClass);` — Set the SoundClass which forms the root of this graph
- L31 _private prototype_ `class USoundClass* GetRootSoundClass() const;` — Get the SoundClass which forms the root of this graph
- L35 _private prototype_ `void RebuildGraph();` — Completely rebuild the graph from the root, removing all old nodes
- L43 _private prototype_ `void AddDroppedSoundClasses(const TArray<class USoundClass*>& SoundClasses, int32 NodePosX, int32 NodePosY);` — Display SoundClasses (and all of their children) that have been dragged onto the editor @param	SoundClasses	SoundClasses not already represented on the graph @param	NodePosX		X coordinate classes were dropped at @param	NodePosY		Y coordinate classes were dropped at
- L54 _private prototype_ `void AddNewSoundClass(UEdGraphPin* FromPin, class USoundClass* SoundClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Display a new SoundClass that has just been created using the editor @param	FromPin		The Pin that was dragged from to create the SoundClass (may be NULL) @param	SoundClass	The newly created SoundClass @param	NodePosX	X coordinate new class was created at @param	NodePosY	Y coordinate new class was created at @param bSelectNewNode	Whether or not to select the new node being created
- L58 _private prototype_ `bool IsClassDisplayed(class USoundClass* SoundClass) const;` — Checks whether a SoundClass is already represented on this graph
- L62 _private prototype_ `void LinkSoundClasses();` — Use this graph to re-link all of the SoundClasses it represents after a change in linkage
- L66 _private prototype_ `void RefreshGraphLinks();` — Re-link all of the nodes in this graph after a change to SoundClass linkage
- L70 _private prototype_ `void RecursivelyRemoveNodes(const TSet<class UObject*> NodesToRemove);` — Recursively remove a set of nodes from this graph and re-link SoundClasses afterwards
- L82 _private prototype_ `int32 ConstructNodes(class USoundClass* SoundClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Construct Nodes to represent a SoundClass and all of its children @param	SoundClass	The SoundClass to represent @param	NodePosX	X coordinate to place first node at @param	NodePosY	Y coordinate to place first node at @param bSelectNewNode	Whether or not to select the new node being created @return	Total height of all constructed nodes (used to arrange multiple new nodes)
- L90 _private prototype_ `int32 RecursivelyGatherChildCounts(class USoundClass* ParentClass, TMap<class USoundClass*, int32>& OutChildCounts);` — Recursively build a map of child counts for each SoundClass to arrange them correctly @param	ParentClass		The class we are getting child counts for @param	OutChildCounts	Map of child counts @return	Total child count for ParentClass
- L99 _private prototype_ `int32 RecursivelyConstructChildNodes(class USoundClassGraphNode* ParentNode, const TMap<class USoundClass*, int32>& InChildCounts, bool bSelectNewNode = true);` — Recursively Construct Nodes to represent the children of a SoundClass @param	ParentNode		The Node we are constructing children for @param	InChildCounts	Map of child counts @param bSelectNewNode	Whether or not to select the new node being created @return	Total height of constructed nodes (used to arrange next new node)
- L103 _private prototype_ `void RecursivelyRemoveNode(class USoundClassGraphNode* ParentNode);` — Recursively remove a node and its children from the graph
- L107 _private prototype_ `void RemoveAllNodes();` — Remove all Nodes from the graph
- L117 _private prototype_ `class USoundClassGraphNode* CreateNode(class USoundClass* SoundClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Create a new node to represent a SoundClass @param	SoundClass	The SoundClass to represent @param	NodePosX	X coordinate to place node at @param	NodePosY	Y coordinate to place node at @param bSelectNewNode	Whether or not to select the new node being created @return	Either a new node or an existing node representing the class
- L121 _private prototype_ `class USoundClassGraphNode* FindExistingNode(class USoundClass* SoundClass) const;` — Find an existing node that represents a given SoundClass
- L125 _private member_ `class USoundClass* RootSoundClass;` — SoundClass which forms the root of this graph

### `Source/Editor/AudioEditor/Classes/SoundClassGraph/SoundClassGraphNode.h` (Public)


#### class `USoundClassGraphNode`  
`class USoundClassGraphNode : public UEdGraphNode`  
_L21-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L27 _private member_ `TObjectPtr<USoundClass> SoundClass;` — `UPROPERTY(VisibleAnywhere, instanced, Category=Sound)` — The SoundNode this represents
- L30 _private function_ `UEdGraphPin* GetChildPin() const` — Get the Pin that connects to all children
- L32 _private function_ `UEdGraphPin* GetParentPin() const` — Get the Pin that connects to its parent
- L34 _private prototype_ `bool CheckRepresentsSoundClass();` — Check whether the children of this node match the SoundClass it is representing
- L37 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L38 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L39 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L40 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L41 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L47 _private member_ `UEdGraphPin* ChildPin;` — Pin that connects to all children
- L49 _private member_ `UEdGraphPin* ParentPin;` — Pin that connects to its parent

### `Source/Editor/AudioEditor/Classes/SoundClassGraph/SoundClassGraphSchema.h` (Public)


#### struct `FSoundClassGraphSchemaAction_NewNode`  
`struct FSoundClassGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L31-55_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L36 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L38 _public function_ `FSoundClassGraphSchemaAction_NewNode() : FEdGraphSchemaAction() , NewSoundClassName(TEXT("ClassName"))`
- L43 _public function_ `FSoundClassGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NewSoundClassName(TEXT("ClassName"))`
- L49 _public function_ `virtual FName GetTypeId() const override`
- L50 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L54 _public member_ `FString NewSoundClassName;` — Name for the new SoundClass

#### class `USoundClassGraphSchema`  
`class USoundClassGraphSchema : public UEdGraphSchema`  
_L58-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L63 _private prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Check whether connecting these pins would cause a loop
- L66 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L67 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L68 _private function_ `virtual FName GetParentContextMenuName() const override`
- L69 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;`
- L70 _private prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L71 _private prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L72 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L73 _private prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L74 _private prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L75 _private prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L76 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L77 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Classes/SoundCueGraph/SoundCueGraph.h` (Public)


#### class `USoundCueGraph`  
`class USoundCueGraph : public UEdGraph`  
_L15-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L20 _private prototype_ `class USoundCue* GetSoundCue() const;` — Returns the SoundCue that contains this graph

### `Source/Editor/AudioEditor/Classes/SoundCueGraph/SoundCueGraphNode.h` (Public)


#### class `USoundCueGraphNode`  
`class USoundCueGraphNode : public USoundCueGraphNode_Base`  
_L22-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundCueGraphNode_Base`
- L28 _private member_ `TObjectPtr<USoundNode> SoundNode;` — `UPROPERTY(VisibleAnywhere, instanced, Category=Sound)` — The SoundNode this represents
- L31 _private prototype_ `void SetSoundNode(USoundNode* InSoundNode);` — Set the SoundNode this represents (also assigns this to the SoundNode in Editor)
- L33 _private prototype_ `void PostCopyNode();` — Fix up the node's owner after being copied
- L35 _private prototype_ `void CreateInputPin();` — Create a new input pin for this node
- L37 _private prototype_ `void AddInputPin();` — Add an input pin to this node and recompile the SoundCue
- L39 _private prototype_ `void RemoveInputPin(UEdGraphPin* InGraphPin);` — Remove a specific input pin from this node and recompile the SoundCue
- L41 _private prototype_ `int32 EstimateNodeWidth() const;` — Estimate the width of this Node from the length of its title
- L43 _private prototype_ `bool CanAddInputPin() const;` — Checks whether an input can be added to this node
- L47 _private prototype_ `virtual void CreateInputPins() override;` — USoundCueGraphNode_Base interface
- L51 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L52 _private prototype_ `virtual void PrepareForCopying() override;`
- L53 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L54 _private prototype_ `virtual FText GetTooltipText() const override;`
- L55 _private prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L59 _private prototype_ `virtual void PostLoad() override;` — UObject interface
- L60 _private prototype_ `virtual void PostEditImport() override;`
- L61 _private prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L66 _private prototype_ `void ResetSoundNodeOwner();` — Make sure the soundnode is owned by the SoundCue

### `Source/Editor/AudioEditor/Classes/SoundCueGraph/SoundCueGraphNode_Base.h` (Public)


#### class `USoundCueGraphNode_Base`  
`class USoundCueGraphNode_Base : public UEdGraphNode`  
_L21-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L26 _private function_ `virtual void CreateInputPins()` — Create all of the input pins required
- L28 _private function_ `virtual bool IsRootNode() const` — Is this the undeletable root node
- L31 _private prototype_ `class UEdGraphPin* GetOutputPin();` — Get the Output Pin (should only ever be one)
- L33 _private prototype_ `void GetInputPins(TArray<class UEdGraphPin*>& OutInputPins);` — Get all of the Input Pins
- L35 _private prototype_ `class UEdGraphPin* GetInputPin(int32 InputIndex);` — Get a single Input Pin via its index
- L37 _private prototype_ `int32 GetInputCount() const;` — Get the current Input Pin count
- L46 _private prototype_ `void InsertNewNode(UEdGraphPin* FromPin, UEdGraphPin* NewLinkPin, TSet<UEdGraphNode*>& OutNodeList);` — Handles inserting the node between the FromPin and what the FromPin was original connected to @param FromPin			The pin this node is being spawned from @param NewLinkPin		The new pin the FromPin will connect to @param OutNodeList		Any nodes that are modified will get added to this list for notification purposes
- L49 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L50 _private prototype_ `virtual void ReconstructNode() override;`
- L51 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L52 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L53 _private prototype_ `virtual FString GetDocumentationLink() const override;`

### `Source/Editor/AudioEditor/Classes/SoundCueGraph/SoundCueGraphNode_Root.h` (Public)


#### class `USoundCueGraphNode_Root`  
`class USoundCueGraphNode_Root : public USoundCueGraphNode_Base`  
_L18-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundCueGraphNode_Base`
- L23 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L24 _private prototype_ `virtual FText GetTooltipText() const override;`
- L25 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _private function_ `virtual bool CanUserDeleteNode() const override`
- L27 _private function_ `virtual bool CanDuplicateNode() const override`
- L28 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L32 _private prototype_ `virtual void CreateInputPins() override;` — USoundCueGraphNode_Base interface
- L33 _private function_ `virtual bool IsRootNode() const override`

### `Source/Editor/AudioEditor/Classes/SoundCueGraph/SoundCueGraphSchema.h` (Public)


#### struct `FSoundCueGraphSchemaAction_NewNode`  
`struct FSoundCueGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L33-60_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L39 _public member_ `TSubclassOf<USoundNode> SoundNodeClass;` — `UPROPERTY()` — Class of node we want to create
- L42 _public function_ `FSoundCueGraphSchemaAction_NewNode() : FEdGraphSchemaAction() , SoundNodeClass(NULL)`
- L47 _public function_ `FSoundCueGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , SoundNodeClass(NULL)`
- L54 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L59 _private prototype_ `void ConnectToSelectedNodes(USoundNode* NewNodeclass, UEdGraph* ParentGraph) const;` — Connects new node to output of selected nodes

#### struct `FSoundCueGraphSchemaAction_NewFromSelected`  
`struct FSoundCueGraphSchemaAction_NewFromSelected : public FSoundCueGraphSchemaAction_NewNode`  
_L64-80_
- reflection: `USTRUCT()`
- inherits: `FSoundCueGraphSchemaAction_NewNode`
- desc: Action to add nodes to the graph based on selected objects
- L68 _public function_ `FSoundCueGraphSchemaAction_NewFromSelected() : FSoundCueGraphSchemaAction_NewNode()`
- L72 _public function_ `FSoundCueGraphSchemaAction_NewFromSelected(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FSoundCueGraphSchemaAction_NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L78 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FSoundCueGraphSchemaAction_NewComment`  
`struct FSoundCueGraphSchemaAction_NewComment : public FEdGraphSchemaAction`  
_L84-100_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to create new comment
- L88 _public function_ `FSoundCueGraphSchemaAction_NewComment() : FEdGraphSchemaAction()`
- L92 _public function_ `FSoundCueGraphSchemaAction_NewComment(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L98 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FSoundCueGraphSchemaAction_Paste`  
`struct FSoundCueGraphSchemaAction_Paste : public FEdGraphSchemaAction`  
_L104-120_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to paste clipboard contents into the graph
- L108 _public function_ `FSoundCueGraphSchemaAction_Paste() : FEdGraphSchemaAction()`
- L112 _public function_ `FSoundCueGraphSchemaAction_Paste(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L118 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `USoundCueGraphSchema`  
`class USoundCueGraphSchema : public UEdGraphSchema`  
_L123-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L128 _private prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Check whether connecting these pins would cause a loop
- L131 _private prototype_ `void GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder) const;` — Helper method to add items valid to the palette list
- L134 _private prototype_ `void TryConnectNodes(const TArray<USoundNode*>& OutputNodes, USoundNode* InputNode) const;` — Attempts to connect the output of multiple nodes to the inputs of a single one
- L137 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L138 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L139 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L140 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L141 _private prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L142 _private prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L143 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L144 _private prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L145 _private prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L146 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L147 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L148 _private prototype_ `virtual void DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L149 _private prototype_ `virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;`
- L150 _private prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L154 _private prototype_ `void UpdateSoundNodeList(const SSoundCuePalette::FSoundNodeFilterData&);` — Update list of component classes
- L158 _private prototype_ `void GetAllSoundNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder, bool bShowSelectedActions) const;` — Adds actions for creating every type of SoundNode
- L160 _private prototype_ `void GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph = NULL) const;` — Adds action for creating a comment
- L162 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`
- L165 _private member_ `TArray<TSubclassOf<USoundNode>> AllowedSoundNodes;` — Soundnodes that can be selected in this graph

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Classes/SoundSubmixGraph/SoundSubmixGraph.h` (Public)


#### class `USoundSubmixGraph`  
`class USoundSubmixGraph : public UEdGraph`  
_L23-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L31 _public prototype_ `void SetRootSoundSubmix(USoundSubmixBase* InSoundSubmix);` — Set the SoundSubmix which forms the root of this graph
- L36 _public prototype_ `USoundSubmixBase* GetRootSoundSubmix() const;` — Get the SoundSubmix which forms the root of this graph
- L41 _public prototype_ `void RebuildGraph();` — Completely rebuild the graph from the root, removing all old nodes
- L50 _public prototype_ `void AddDroppedSoundSubmixes(const TSet<USoundSubmixBase*>& SoundSubmixes, int32 NodePosX, int32 NodePosY);` — Display SoundSubmixes (and all of their children) that have been dragged onto the editor @param	SoundSubmixes	SoundSubmixes not already represented on the graph @param	NodePosX		X coordinate submix(es) were dropped at @param	NodePosY		Y coordinate submix(es) were dropped at
- L61 _public prototype_ `void AddNewSoundSubmix(UEdGraphPin* FromPin, USoundSubmixBase* SoundSubmix, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Display a new SoundSubmix that has just been created using the editor @param	FromPin		The Pin that was dragged from to create the SoundSubmix (may be NULL) @param	SoundClass	The newly created SoundSubmix @param	NodePosX	X coordinate new submix was created at @param	NodePosY	Y coordinate new submix was created at @param bSelectNewNode	Whether or not to select the new node being created
- L66 _public prototype_ `bool IsSubmixDisplayed(USoundSubmixBase* SoundSubmix) const;` — Checks whether a SoundSubmix is already represented on this graph
- L71 _public prototype_ `void LinkSoundSubmixes();` — Use this graph to re-link all of the SoundSubmixes it represents after a change in linkage
- L76 _public prototype_ `void RefreshGraphLinks();` — Re-link all of the nodes in this graph after a change to SoundSubmix linkage
- L81 _public prototype_ `void RecursivelyRemoveNodes(const TSet<UObject*> NodesToRemove);` — Recursively remove a set of nodes from this graph and re-link SoundSubmixes afterwards
- L86 _public prototype_ `USoundSubmixGraphNode* FindExistingNode(USoundSubmixBase* SoundSubmix) const;` — Find an existing node that represents a given SoundSubmix
- L98 _private prototype_ `int32 ConstructNodes(USoundSubmixBase* SoundSubmix, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Construct Nodes to represent a SoundSubmix and all of its children @param	SoundSubmix	The SoundSubmix to represent @param	NodePosX	X coordinate to place first node at @param	NodePosY	Y coordinate to place first node at @param bSelectNewNode	Whether or not to select the new node being created @return	Total height of all constructed nodes (used to arrange multiple new nodes)
- L106 _private prototype_ `int32 RecursivelyGatherChildCounts(USoundSubmixBase* ParentSubmix, TMap<USoundSubmixBase*, int32>& OutChildCounts);` — Recursively build a map of child counts for each SoundSubmix to arrange them correctly @param	ParentClass		The class we are getting child counts for @param	OutChildCounts	Map of child counts @return	Total child count for ParentClass
- L115 _private prototype_ `int32 RecursivelyConstructChildNodes(USoundSubmixGraphNode* ParentNode, const TMap<USoundSubmixBase*, int32>& InChildCounts, bool bSelectNewNode = true);` — Recursively Construct Nodes to represent the children of a SoundSubmix @param	ParentNode		The Node we are constructing children for @param	InChildCounts	Map of child counts @param bSelectNewNode	Whether or not to select the new node being created @return	Total height of constructed nodes (used to arrange next new node)
- L119 _private prototype_ `void RecursivelyRemoveNode(USoundSubmixGraphNode* ParentNode);` — Recursively remove a node and its children from the graph
- L123 _private prototype_ `void RemoveAllNodes();` — Remove all Nodes from the graph
- L133 _private prototype_ `USoundSubmixGraphNode* CreateNode(USoundSubmixBase* SoundSubmix, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true);` — Create a new node to represent a SoundSubmix @param	SoundSubmix	The SoundSubmix to represent @param	NodePosX	X coordinate to place node at @param	NodePosY	Y coordinate to place node at @param bSelectNewNode	Whether or not to select the new node being created @return	Either a new node or an existing node representing the class
- L138 _private member_ `TObjectPtr<USoundSubmixBase> RootSoundSubmix = nullptr;` — `UPROPERTY(Transient)` — SoundSubmix which forms the root of this graph
- L141 _private member_ `TArray<TObjectPtr<USoundSubmixBase>> StaleRoots;` — `UPROPERTY(Transient)`

### `Source/Editor/AudioEditor/Classes/SoundSubmixGraph/SoundSubmixGraphNode.h` (Public)


#### class `SSubmixGraphNode`  
`class SSubmixGraphNode : public SGraphNode`  
_L37-54_
- inherits: `SGraphNode`
- L40 _public function_ `SLATE_BEGIN_ARGS(SSubmixGraphNode)`
- L42 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<USoundSubmixBase>, SubmixBase) SLATE_ARGUMENT(TWeakObjectPtr<UUserWidget>, SubmixNodeUserWidget) SLATE_END_ARGS();`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphNode* InGraphNode);`
- L49 _public prototype_ `TSharedRef<SWidget> CreateNodeContentArea() override;`
- L52 _private member_ `TWeakObjectPtr<USoundSubmixBase> SubmixBase;`
- L53 _private member_ `TWeakObjectPtr<UUserWidget> SubmixNodeUserWidget;`

#### class `USoundSubmixGraphNode`  
`class USoundSubmixGraphNode : public UEdGraphNode`  
_L57-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L63 _private member_ `TObjectPtr<USoundSubmixBase> SoundSubmix;` — `UPROPERTY(VisibleAnywhere, instanced, Category=Sound)` — The SoundSubmix this represents
- L67 _private member_ `TObjectPtr<UUserWidget> SubmixNodeUserWidget;` — `UPROPERTY(Transient)` — A user widget to use to represent the graph node
- L70 _private function_ `UEdGraphPin* GetChildPin() const` — Get the Pin that connects to all children
- L73 _private function_ `UEdGraphPin* GetParentPin() const` — Get the Pin that connects to its parent
- L76 _private prototype_ `bool CheckRepresentsSoundSubmix();` — Check whether the children of this node match the SoundSubmix it is representing
- L79 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L80 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L81 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L82 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L83 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L84 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L85 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget();`
- L90 _private member_ `UEdGraphPin* ChildPin;` — Pin that connects to all children
- L93 _private member_ `UEdGraphPin* ParentPin;` — Pin that connects to its parent

### `Source/Editor/AudioEditor/Classes/SoundSubmixGraph/SoundSubmixGraphSchema.h` (Public)


#### struct `FSoundSubmixGraphConnectionDrawingPolicyFactory`  
`struct FSoundSubmixGraphConnectionDrawingPolicyFactory : public FGraphPanelPinConnectionFactory`  
_L37-52_
- inherits: `FGraphPanelPinConnectionFactory`
- L40 _public prototype_ `virtual ~FSoundSubmixGraphConnectionDrawingPolicyFactory() = default;`
- L43 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionPolicy( const UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;` — FGraphPanelPinConnectionFactory

#### class `FSoundSubmixGraphConnectionDrawingPolicy`  
`class FSoundSubmixGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L56-89_
- inherits: `FConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph using a SoundCue schema
- L73 _protected typedef_ `typedef TMap<UEdGraphNode*, FTimePair> FExecPairingMap;` — Map of pairings
- L76 _protected member_ `TMap<UEdGraphNode*, FExecPairingMap> PredecessorNodes;` — Map of nodes that preceded before a given node in the execution sequence (one entry for each pairing)
- L78 _protected member_ `UEdGraph* GraphObj;`
- L80 _protected member_ `float ActiveWireThickness;`
- L81 _protected member_ `float InactiveWireThickness;`
- L84 _public prototype_ `FSoundSubmixGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L87 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface

#### struct `FSoundSubmixGraphConnectionDrawingPolicy::FTimePair`  
`struct FTimePair`  
_L60-70_
- desc: Times for one execution pair within the current graph
- L62 _public member_ `double PredExecTime;`
- L63 _public member_ `double ThisExecTime;`
- L65 _public function_ `FTimePair() : PredExecTime(0.0) , ThisExecTime(0.0)`

#### struct `FSoundSubmixGraphSchemaAction_NewNode`  
`struct FSoundSubmixGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L94-118_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L99 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L101 _public function_ `FSoundSubmixGraphSchemaAction_NewNode() : FEdGraphSchemaAction() , NewSoundSubmixName(TEXT("SubmixName"))`
- L106 _public function_ `FSoundSubmixGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NewSoundSubmixName(TEXT("SubmixName"))`
- L112 _public function_ `virtual FName GetTypeId() const override`
- L113 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L117 _public member_ `FString NewSoundSubmixName;` — Name for the new SoundSubmix

#### class `USoundSubmixGraphSchema`  
`class USoundSubmixGraphSchema : public UEdGraphSchema`  
_L121-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L126 _private prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Check whether connecting these pins would cause a loop
- L129 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L130 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L131 _private function_ `virtual FName GetParentContextMenuName() const override`
- L132 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;`
- L133 _private prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L134 _private prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L135 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L136 _private prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L137 _private prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L138 _private prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L139 _private prototype_ `virtual void DroppedAssetsOnGraph(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L140 _private prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_AudioBus.h` (Private)


#### class `UAssetDefinition_AudioBus`  
`class UAssetDefinition_AudioBus : public UAssetDefinitionDefault_AudioDiffable`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_DialogueVoice.h` (Private)


#### class `UAssetDefinition_DialogueVoice`  
`class UAssetDefinition_DialogueVoice : public UAssetDefinitionDefault_AudioDiffable`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_DialogueWave.h` (Private)


#### class `UAssetDefinition_DialogueWave`  
`class UAssetDefinition_DialogueWave : public UAssetDefinitionDefault_AudioDiffable`  
_L9-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_ReverbEffect.h` (Private)


#### class `UAssetDefinition_ReverbEffect`  
`class UAssetDefinition_ReverbEffect : public UAssetDefinitionDefault_AudioDiffable`  
_L12-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundAttenuation.h` (Private)


#### class `UAssetDefinition_SoundAttenuation`  
`class UAssetDefinition_SoundAttenuation : public UAssetDefinitionDefault_AudioDiffable`  
_L13-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundClass.h` (Private)


#### class `UAssetDefinition_SoundClass`  
`class UAssetDefinition_SoundClass : public UAssetDefinitionDefault_AudioDiffable`  
_L9-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundConcurrency.h` (Private)


#### class `UAssetDefinition_SoundConcurrency`  
`class UAssetDefinition_SoundConcurrency : public UAssetDefinitionDefault_AudioDiffable`  
_L13-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundCue.h` (Private)


#### class `UAssetDefinition_SoundCue`  
`class UAssetDefinition_SoundCue : public UAssetDefinition_SoundBase`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundBase`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundEffectPreset.h` (Private)


#### class `UAssetDefinition_SoundEffectSubmixPreset`  
`class UAssetDefinition_SoundEffectSubmixPreset : public UAssetDefinitionDefault_AudioDiffable`  
_L10-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundEffectSourcePreset`  
`class UAssetDefinition_SoundEffectSourcePreset : public UAssetDefinitionDefault_AudioDiffable`  
_L33-53_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L38 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L39 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L40 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L41 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundEffectSourcePresetChain`  
`class UAssetDefinition_SoundEffectSourcePresetChain : public UAssetDefinitionDefault_AudioDiffable`  
_L56-76_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L61 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L62 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L63 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L64 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundEffectPresetDynamic`  
`class UAssetDefinition_SoundEffectPresetDynamic : public UAssetDefinitionDefault_AudioDiffable`  
_L79-96_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L84 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L85 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L86 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L87 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L88 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L89 _public function_ `virtual bool CanRegisterStatically() const override`
- L92 _public prototype_ `void Initialize(TSubclassOf<USoundEffectPreset> InClass);`
- L95 _private member_ `TStrongObjectPtr<USoundEffectPreset> EffectPresetCDO;`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundMix.h` (Private)


#### class `UAssetDefinition_SoundMix`  
`class UAssetDefinition_SoundMix : public UAssetDefinitionDefault_AudioDiffable`  
_L12-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundSourceBus.h` (Private)


#### class `UAssetDefinition_SoundSourceBus`  
`class UAssetDefinition_SoundSourceBus : public UAssetDefinition_SoundBase`  
_L12-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundBase`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L31 _public function_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const override`
- L32 _public function_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override`

### `Source/Editor/AudioEditor/Private/AssetTypeActions/AssetDefinition_SoundSubmix.h` (Private)


#### class `UAssetDefinition_SoundSubmix`  
`class UAssetDefinition_SoundSubmix : public UAssetDefinitionDefault_AudioDiffable`  
_L9-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L29 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### class `UAssetDefinition_SoundfieldSubmix`  
`class UAssetDefinition_SoundfieldSubmix : public UAssetDefinition_SoundSubmix`  
_L34-48_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundSubmix`
- L39 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L40 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L41 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L42 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_EndpointSubmix`  
`class UAssetDefinition_EndpointSubmix : public UAssetDefinition_SoundSubmix`  
_L51-65_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundSubmix`
- L56 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L57 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L58 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L59 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundfieldEndpointSubmix`  
`class UAssetDefinition_SoundfieldEndpointSubmix : public UAssetDefinition_SoundSubmix`  
_L68-82_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundSubmix`
- L73 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L74 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L75 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L76 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundfieldEncodingSettings`  
`class UAssetDefinition_SoundfieldEncodingSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L85-99_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L90 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L91 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L92 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L93 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundfieldEffectSettings`  
`class UAssetDefinition_SoundfieldEffectSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L102-116_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L107 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L108 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L109 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L110 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundfieldEffect`  
`class UAssetDefinition_SoundfieldEffect : public UAssetDefinitionDefault_AudioDiffable`  
_L119-133_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L124 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L125 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L126 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L127 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_AudioEndpointSettings`  
`class UAssetDefinition_AudioEndpointSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L136-150_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L141 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L142 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L143 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L144 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_SoundfieldEndpointSettings`  
`class UAssetDefinition_SoundfieldEndpointSettings : public UAssetDefinitionDefault_AudioDiffable`  
_L153-167_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L158 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L159 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L160 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L161 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/AudioEditor/Private/Editors/SoundEffectPresetEditor.h` (Private)


#### class `FSoundEffectPresetEditor`  
`class FSoundEffectPresetEditor : public FAssetEditorToolkit, public FNotifyHook, public FEditorUndoClient`  
_L30-80_
- inherits: `FAssetEditorToolkit,FNotifyHook,FEditorUndoClient`
- L33 _public prototype_ `FSoundEffectPresetEditor();`
- L34 _public prototype_ `virtual ~FSoundEffectPresetEditor() = default;`
- L36 _public prototype_ `void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, USoundEffectPreset* PresetToEdit, const TArray<UUserWidget*>& InWidgetBlueprints);`
- L39 _public prototype_ `virtual bool CloseWindow(EAssetEditorCloseReason InCloseReason) override;` — FAssetEditorToolkit interface
- L40 _public prototype_ `virtual FName GetEditorName() const override;`
- L41 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L42 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L43 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L44 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L45 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L46 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L49 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L50 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L52 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L53 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L57 _private prototype_ `void InitPresetWidgets(const TArray<UUserWidget*>& InWidgets);` — Initializes all preset user widgets.
- L60 _private prototype_ `TSharedRef<SDockTab> SpawnTab_UserWidgetEditor(const FSpawnTabArgs& Args, int32 WidgetIndex);` — Spawns the tab allowing for editing/viewing the blueprint widget for the associated SoundEffectPreset
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the tab allowing for editing/viewing details panel
- L66 _private prototype_ `EOrientation GetSnapLabelOrientation() const;` — Get the orientation for the snap value controls.
- L69 _private member_ `TSharedPtr<IDetailsView> PropertiesView;` — Properties tab
- L72 _private member_ `static const FName AppIdentifier;` — Settings Editor App Identifier
- L74 _private member_ `TStrongObjectPtr<USoundEffectPreset> SoundEffectPreset;`
- L75 _private member_ `TArray<TStrongObjectPtr<UUserWidget>> UserWidgets;`
- L78 _private member_ `static const FName PropertiesTabId;` — Tab Ids
- L79 _private member_ `static const FName UserWidgetTabId;`

### `Source/Editor/AudioEditor/Private/Factories/SoundFactoryUtility.h` (Private)


#### class `FAssetClassParentFilter`  
`class FAssetClassParentFilter : public IClassViewerFilter`  
_L9-29_
- inherits: `IClassViewerFilter`
- L13 _public member_ `TSet< const UClass* > AllowedChildrenOfClasses;` — All children of these classes will be included unless filtered out by another setting.
- L16 _public member_ `EClassFlags DisallowedClassFlags;` — Disallowed class flags.
- L18 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`
- L24 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override`

### `Source/Editor/AudioEditor/Private/SFindInSoundClassGraph.h` (Private)


#### class `SFindInSoundClassGraph`  
`class SFindInSoundClassGraph final : public SCompoundWidget`  
_L13-80_
- inherits: `SCompoundWidget`
- L16 _public function_ `DECLARE_DELEGATE_OneParam(FOnResultActivated, USoundClassGraphNode*) SLATE_BEGIN_ARGS(SFindInSoundClassGraph)`
- L19 _public prototype_ `SLATE_EVENT(FOnResultActivated, OnSearchResultActivated) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SGraphEditor> InGraphEditor);`
- L25 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L27 _public prototype_ `void FocusForUse(const FString& NewSearchTerms);` — Focuses this widget's search box, and Initiates a search with given SearchTerms
- L30 _private typedef_ `typedef TWeakObjectPtr<USoundClassGraphNode> FSearchResult;`
- L31 _private typedef_ `typedef SListView<FSearchResult> SListViewType;`
- L34 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L37 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L40 _private prototype_ `void OnSelectionDoubleClick(FSearchResult Item);` — Called when user double-clicks on a new result
- L43 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerList);` — Called when a new row is being generated
- L46 _private prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L49 _private prototype_ `void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L52 _private prototype_ `void MatchTokensInGraph(const UEdGraph* Graph, const TArray<FString>& Tokens);` — Find any results that contain all of the tokens in provided graph
- L55 _private prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L58 _private member_ `TWeakPtr<SGraphEditor> GraphEditorPtr;` — Pointer back to the Graph Editor of the Sound Class editor that owns us
- L61 _private member_ `TSharedPtr<SListViewType> ListView;` — The list view displays the results
- L64 _private member_ `TSharedPtr<SSearchBox> SearchTextField;` — The search text box
- L67 _private member_ `FOnResultActivated OnResultActivated;` — The callback to execute when a search result is activated by the user (provides the node corresponding to the result)
- L70 _private member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L73 _private member_ `FText HighlightText;` — The string to highlight in the results
- L76 _private member_ `FString SearchValue;` — The string to search for
- L79 _private member_ `uint32 FoundNodeCount = 0;` — Counters for number of results

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResultActivated, USoundClassGraphNode*) SLATE_BEGIN_ARGS(SFindInSoundClassGraph) {} SLATE_EVENT(FOnResultActivated, OnSearchResultActivated) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SGraphEditor> InGraphEditor);`

### `Source/Editor/AudioEditor/Private/SGraphNodeSoundBase.h` (Private)


#### class `SGraphNodeSoundBase`  
`class SGraphNodeSoundBase : public SGraphNode`  
_L14-30_
- inherits: `SGraphNode`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSoundBase)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class USoundCueGraphNode* InNode);`
- L24 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;` — SGraphNode Interface
- L25 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L26 _protected prototype_ `virtual FReply OnAddPin() override;`
- L29 _private member_ `USoundCueGraphNode* SoundNode;`

### `Source/Editor/AudioEditor/Private/SGraphNodeSoundResult.h` (Private)


#### class `SGraphNodeSoundResult`  
`class SGraphNodeSoundResult : public SGraphNode`  
_L11-23_
- inherits: `SGraphNode`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSoundResult)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class USoundCueGraphNode_Base* InNode);`
- L21 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;` — SGraphNode interface

### `Source/Editor/AudioEditor/Private/SSoundClassActionMenu.h` (Private)


#### class `SSoundClassActionMenuItem`  
`class SSoundClassActionMenuItem : public SCompoundWidget`  
_L27-49_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single item
- L30 _public function_ `SLATE_BEGIN_ARGS( SSoundClassActionMenuItem )`
- L33 _public prototype_ `SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FEdGraphSchemaAction> InAction, TWeakPtr<class SSoundClassActionMenu> InOwner);`
- L40 _private prototype_ `TSharedRef<SWidget> CreateNewSoundClassWidget( const FText& DisplayText, const FText& ToolTip, const FSlateFontInfo& NameFont, TSharedPtr<FEdGraphSchemaAction>& InAction );` — Create the new sound class widget
- L43 _private prototype_ `void OnNewSoundClassNameEntered(const FText& NewText, ETextCommit::Type CommitInfo, TSharedPtr<FEdGraphSchemaAction> InAction );` — Called when confirming name for new sound class
- L46 _private prototype_ `void OnNewSoundClassNameChanged(const FText& NewText, TSharedPtr<FEdGraphSchemaAction> InAction );` — Called when text is changed for a new sound class name
- L48 _private member_ `TWeakPtr<class SSoundClassActionMenu> Owner;`

#### class `SSoundClassActionMenu`  
`class SSoundClassActionMenu : public SBorder`  
_L53-91_
- inherits: `SBorder`
- L56 _public function_ `SLATE_BEGIN_ARGS( SSoundClassActionMenu ) : _GraphObj( static_cast<UEdGraph*>(NULL) ) , _NewNodePosition( FVector2D::ZeroVector ) , _AutoExpandActionMenu( true )`
- L62 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L71 _public prototype_ `~SSoundClassActionMenu();`
- L74 _protected member_ `UEdGraph* GraphObj;`
- L75 _protected member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L76 _protected member_ `FDeprecateSlateVector2D NewNodePosition;`
- L77 _protected member_ `bool bAutoExpandActionMenu;`
- L79 _protected member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L81 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L83 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedActions, ESelectInfo::Type InSelectionType );`
- L85 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L88 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu

### `Source/Editor/AudioEditor/Private/SSoundCuePalette.h` (Private)


#### class `SSoundCuePalette`  
`class SSoundCuePalette : public SGraphPalette`  
_L16-41_
- inherits: `SGraphPalette`
- L19 _public function_ `SLATE_BEGIN_ARGS( SSoundCuePalette )`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;` — Callback used to populate all actions list in SGraphActionMenu
- L38 _protected prototype_ `void OnGlobalClassViewerFilterModified();` — Callback when the class viewer filter has been modified
- L40 _protected member_ `FSoundNodeFilterData FilterData;`

#### struct `SSoundCuePalette::FSoundNodeFilterData`  
`struct FSoundNodeFilterData`  
_L26-31_
- desc: Internal data used to facilitate sound node filtering
- L28 _public member_ `TSharedPtr<FClassViewerInitializationOptions> InitOptions;`
- L29 _public member_ `TSharedPtr<IClassViewerFilter> ClassFilter;`
- L30 _public member_ `TSharedPtr<FClassViewerFilterFuncs> FilterFuncs;`

### `Source/Editor/AudioEditor/Private/SSoundSubmixActionMenu.h` (Private)


#### class `SSoundSubmixActionMenuItem`  
`class SSoundSubmixActionMenuItem : public SCompoundWidget`  
_L27-49_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single item
- L30 _public function_ `SLATE_BEGIN_ARGS( SSoundSubmixActionMenuItem )`
- L33 _public prototype_ `SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FEdGraphSchemaAction> InAction, TWeakPtr<class SSoundSubmixActionMenu> InOwner);`
- L40 _private prototype_ `TSharedRef<SWidget> CreateNewSoundSubmixWidget( const FText& DisplayText, const FText& ToolTip, const FSlateFontInfo& NameFont, TSharedPtr<FEdGraphSchemaAction>& InAction );` — Create the new sound submix widget
- L43 _private prototype_ `void OnNewSoundSubmixNameEntered(const FText& NewText, ETextCommit::Type CommitInfo, TSharedPtr<FEdGraphSchemaAction> InAction );` — Called when confirming name for new sound submix
- L46 _private prototype_ `void OnNewSoundSubmixNameChanged(const FText& NewText, TSharedPtr<FEdGraphSchemaAction> InAction );` — Called when text is changed for a new sound submix name
- L48 _private member_ `TWeakPtr<class SSoundSubmixActionMenu> Owner;`

#### class `SSoundSubmixActionMenu`  
`class SSoundSubmixActionMenu : public SBorder`  
_L53-91_
- inherits: `SBorder`
- L56 _public function_ `SLATE_BEGIN_ARGS( SSoundSubmixActionMenu ) : _GraphObj( static_cast<UEdGraph*>(NULL) ) , _NewNodePosition( FVector2D::ZeroVector ) , _AutoExpandActionMenu( true )`
- L62 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L71 _public prototype_ `~SSoundSubmixActionMenu();`
- L74 _protected member_ `UEdGraph* GraphObj;`
- L75 _protected member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L76 _protected member_ `FDeprecateSlateVector2D NewNodePosition;`
- L77 _protected member_ `bool bAutoExpandActionMenu;`
- L79 _protected member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L81 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L83 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedActions, ESelectInfo::Type InSelectionType );`
- L85 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L88 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu

### `Source/Editor/AudioEditor/Private/SoundClassEditor.h` (Private)


#### class `FSoundClassEditor`  
`class FSoundClassEditor : public ISoundClassEditor, public FGCObject, public FEditorUndoClient`  
_L28-157_
- inherits: `ISoundClassEditor,FGCObject,FEditorUndoClient`
- L31 _public function_ `SLATE_BEGIN_ARGS( FSoundClassEditor )`
- L35 _public prototype_ `SLATE_END_ARGS() virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L38 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L47 _public prototype_ `void InitSoundClassEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit );` — Edits the specified sound class object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The sound class to edit
- L49 _public prototype_ `FSoundClassEditor();`
- L50 _public prototype_ `virtual ~FSoundClassEditor();`
- L53 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L54 _public function_ `virtual FString GetReferencerName() const override`
- L60 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L61 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L62 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L65 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L68 _public prototype_ `virtual void CreateSoundClass(class UEdGraphPin* FromPin, const FVector2D& Location, const FString& Name) override;` — ISoundClassEditor interface
- L71 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L72 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L75 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);`
- L76 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L77 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Find(const FSpawnTabArgs& Args);`
- L81 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L84 _private prototype_ `TSharedRef<SGraphEditor> CreateGraphEditorWidget();` — Create new graph editor widget
- L87 _private prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L90 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L93 _private prototype_ `void SelectAllNodes();` — Select every node in the graph
- L95 _private prototype_ `bool CanSelectAllNodes() const;` — Whether we can select every node
- L98 _private prototype_ `void RemoveSelectedNodes();` — Remove the currently selected nodes from editor view
- L100 _private prototype_ `bool CanRemoveNodes() const;` — Whether we are able to remove the currently selected nodes
- L103 _private prototype_ `void UndoGraphAction();` — Called to undo the last action
- L105 _private prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L108 _private prototype_ `void ToggleSolo();` — Toggle solo (Soloing means we just hear this)
- L109 _private prototype_ `bool CanExcuteToggleSolo() const;`
- L110 _private prototype_ `bool IsSoloToggled() const;`
- L113 _private prototype_ `void ToggleMute();` — Toggle mute (Muting means this will be explicitly silenced)
- L114 _private prototype_ `bool CanExcuteToggleMute() const;`
- L115 _private prototype_ `bool IsMuteToggled() const;`
- L117 _private prototype_ `virtual void FindInContentBrowser_Execute() override;`
- L118 _private prototype_ `void OnLaunchReferenceViewer() const;`
- L121 _private prototype_ `void ShowFindInSoundClassGraph();` — Show and focus the Find in Sound Class Graph tab.
- L125 _private member_ `TObjectPtr<USoundClass> SoundClass;` — The SoundClass asset being inspected
- L128 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;` — Graph Editor
- L131 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View
- L134 _private member_ `TSharedPtr<SFindInSoundClassGraph> FindWidget;` — Find in Sound Class Graph widget.
- L137 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L141 _private member_ `Audio::FAudioDebugger* Debugger;` — Cache the audio debugger instance
- L145 _private member_ `static const FName GraphCanvasTabId;` — The tab ids for all the tabs used
- L146 _private member_ `static const FName PropertiesTabId;`
- L147 _private member_ `static const FName FindInSoundClassGraphTabId;`
- L150 _private prototype_ `void BindCommands();` — Bind to commands.
- L153 _private prototype_ `void ExtendToolbar();` — Helper function to grow the toolbar and add custom buttons
- L156 _private prototype_ `void OnSearchResultActivated(USoundClassGraphNode* Node);` — Select & zoom to result

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Audio`

### `Source/Editor/AudioEditor/Private/SoundClassTemplates.h` (Private)


#### class `USoundEffectSourcePresetClassTemplate`  
`class USoundEffectSourcePresetClassTemplate : public UClassTemplate`  
_L16-25_
- reflection: `UCLASS()`
- inherits: `UClassTemplate`
- L21 _public function_ `FString GetFilename() const override`

#### class `USoundEffectSubmixPresetClassTemplate`  
`class USoundEffectSubmixPresetClassTemplate : public UClassTemplate`  
_L28-37_
- reflection: `UCLASS()`
- inherits: `UClassTemplate`
- L33 _public function_ `FString GetFilename() const override`

#### class `USynthComponentClassTemplate`  
`class USynthComponentClassTemplate : public UClassTemplate`  
_L40-49_
- reflection: `UCLASS()`
- inherits: `UClassTemplate`
- L45 _public function_ `FString GetFilename() const override`

### `Source/Editor/AudioEditor/Private/SoundCueEditor.h` (Private)


#### class `FSoundCueEditor`  
`class FSoundCueEditor : public ISoundCueEditor, public FGCObject, public FNotifyHook, public FEditorUndoClient`  
_L30-228_
- inherits: `ISoundCueEditor,FGCObject,FNotifyHook,FEditorUndoClient`
- L33 _public prototype_ `FSoundCueEditor();`
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L39 _public prototype_ `virtual ~FSoundCueEditor();` — Destructor
- L42 _public prototype_ `void InitSoundCueEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified SoundCue object
- L45 _public prototype_ `virtual USoundCue* GetSoundCue() const override;` — ISoundCueEditor interface
- L46 _public prototype_ `virtual void SetSelection(TArray<UObject*> SelectedObjects) override;`
- L47 _public prototype_ `virtual bool GetBoundsForSelectedNodes(class FSlateRect& Rect, float Padding) override;`
- L48 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const override;`
- L49 _public prototype_ `virtual TSet<UObject*> GetSelectedNodes() const override;`
- L52 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L53 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L54 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L55 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L57 _public function_ `virtual FString GetDocumentationLink() const override`
- L63 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L64 _public function_ `virtual FString GetReferencerName() const override`
- L70 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L71 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L75 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);`
- L76 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L77 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args);`
- L81 _protected prototype_ `void OnPreviewTextChanged(const FString& Text);` — Called when the preview text changes
- L84 _protected prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L93 _protected prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename @param	NewText				New title text @param	CommitInfo			How text was committed @param	NodeBeingChanged	The node being changed
- L96 _protected prototype_ `void SelectAllNodes();` — Select every node in the graph
- L98 _protected prototype_ `bool CanSelectAllNodes() const;` — Whether we can select every node
- L101 _protected prototype_ `void DeleteSelectedNodes();` — Delete the currently selected nodes
- L103 _protected prototype_ `bool CanDeleteNodes() const;` — Whether we are able to delete the currently selected nodes
- L105 _protected prototype_ `void DeleteSelectedDuplicatableNodes();` — Delete only the currently selected nodes that can be duplicated
- L108 _protected prototype_ `void CutSelectedNodes();` — Cut the currently selected nodes
- L110 _protected prototype_ `bool CanCutNodes() const;` — Whether we are able to cut the currently selected nodes
- L113 _protected prototype_ `void CopySelectedNodes();` — Copy the currently selected nodes
- L115 _protected prototype_ `bool CanCopyNodes() const;` — Whether we are able to copy the currently selected nodes
- L118 _protected prototype_ `void PasteNodes();` — Paste the contents of the clipboard
- L120 _protected prototype_ `virtual void PasteNodesHere(const FVector2D& Location) override;` — Paste the contents of the clipboard at a specific location
- L122 _protected prototype_ `virtual bool CanPasteNodes() const override;` — Whether we are able to paste the contents of the clipboard
- L125 _protected prototype_ `void DuplicateNodes();` — Duplicate the currently selected nodes
- L127 _protected prototype_ `bool CanDuplicateNodes() const;` — Whether we are able to duplicate the currently selected nodes
- L130 _protected prototype_ `void UndoGraphAction();` — Called to undo the last action
- L133 _protected prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L135 _protected prototype_ `void OnAlignTop();`
- L136 _protected prototype_ `void OnAlignMiddle();`
- L137 _protected prototype_ `void OnAlignBottom();`
- L138 _protected prototype_ `void OnAlignLeft();`
- L139 _protected prototype_ `void OnAlignCenter();`
- L140 _protected prototype_ `void OnAlignRight();`
- L142 _protected prototype_ `void OnStraightenConnections();`
- L144 _protected prototype_ `void OnDistributeNodesH();`
- L145 _protected prototype_ `void OnDistributeNodesV();`
- L149 _private prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L152 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L155 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the SoundCue editor
- L158 _private prototype_ `void BindGraphCommands();` — Binds new graph commands to delegates
- L161 _private prototype_ `void PlayCue();` — Toolbar command methods
- L162 _private prototype_ `void PlayNode();`
- L164 _private prototype_ `bool CanPlayNode() const;` — Whether we can play the current selection of nodes
- L165 _private prototype_ `void Stop();`
- L167 _private prototype_ `void TogglePlayback();` — Either play the cue or stop currently playing sound
- L170 _private prototype_ `void ToggleSolo();` — Toggle solo explain soloing
- L171 _private prototype_ `bool CanExcuteToggleSolo() const;`
- L172 _private prototype_ `bool IsSoloToggled() const;`
- L175 _private prototype_ `void ToggleMute();` — Toggle mute
- L176 _private prototype_ `bool CanExcuteToggleMute() const;`
- L177 _private prototype_ `bool IsMuteToggled() const;`
- L180 _private prototype_ `void PlaySingleNode(UEdGraphNode* Node);` — Plays a single specified node
- L183 _private prototype_ `void SyncInBrowser();` — Sync the content browser to the current selection of nodes
- L185 _private prototype_ `bool CanSyncInBrowser() const;` — Whether we can sync the content browser to the current selection of nodes
- L188 _private prototype_ `void AddInput();` — Add an input to the currently selected node
- L190 _private prototype_ `bool CanAddInput() const;` — Whether we can add an input to the currently selected node
- L193 _private prototype_ `void DeleteInput();` — Delete an input from the currently selected node
- L195 _private prototype_ `bool CanDeleteInput() const;` — Whether we can delete an input from the currently selected node
- L198 _private prototype_ `void OnCreateComment();` — Create comment node on graph
- L201 _private prototype_ `TSharedRef<SGraphEditor> CreateGraphEditorWidget();` — Create new graph editor widget
- L205 _private member_ `TObjectPtr<USoundCue> SoundCue;` — The SoundCue asset being inspected
- L208 _private member_ `TSharedPtr<SGraphEditor> SoundCueGraphEditor;` — New Graph Editor
- L211 _private member_ `TSharedPtr<class IDetailsView> SoundCueProperties;` — Properties tab
- L214 _private member_ `TSharedPtr<class SSoundCuePalette> Palette;` — Palette of Sound Node types
- L217 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L221 _private member_ `Audio::FAudioDebugger* Debugger;` — Cache of the Audio debugger instance
- L225 _private member_ `static const FName GraphCanvasTabId;` — The tab ids for all the tabs used
- L226 _private member_ `static const FName PropertiesTabId;`
- L227 _private member_ `static const FName PaletteTabId;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Audio`

### `Source/Editor/AudioEditor/Private/SoundCueGraphConnectionDrawingPolicy.h` (Private)


#### struct `FSoundCueGraphConnectionDrawingPolicyFactory`  
`struct FSoundCueGraphConnectionDrawingPolicyFactory : public FGraphPanelPinConnectionFactory`  
_L22-31_
- inherits: `FGraphPanelPinConnectionFactory`
- L25 _public prototype_ `virtual ~FSoundCueGraphConnectionDrawingPolicyFactory() = default;`
- L28 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionPolicy(const class UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const class FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;` — FGraphPanelPinConnectionFactory

#### class `FSoundCueGraphConnectionDrawingPolicy`  
`class FSoundCueGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L38-77_
- inherits: `FConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph using a SoundCue schema
- L55 _protected typedef_ `typedef TMap<UEdGraphNode*, FTimePair> FExecPairingMap;` — Map of pairings
- L58 _protected member_ `TMap<UEdGraphNode*, FExecPairingMap> PredecessorNodes;` — Map of nodes that preceeded before a given node in the execution sequence (one entry for each pairing)
- L60 _protected member_ `UEdGraph* GraphObj;`
- L62 _protected member_ `FLinearColor ActiveColor;`
- L63 _protected member_ `FLinearColor InactiveColor;`
- L65 _protected member_ `float ActiveWireThickness;`
- L66 _protected member_ `float InactiveWireThickness;`
- L69 _public prototype_ `FSoundCueGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L71 _public prototype_ `void BuildAudioFlowRoadmap();`
- L74 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L75 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;`

#### struct `FSoundCueGraphConnectionDrawingPolicy::FTimePair`  
`struct FTimePair`  
_L42-52_
- desc: Times for one execution pair within the current graph
- L44 _public member_ `double PredExecTime;`
- L45 _public member_ `double ThisExecTime;`
- L47 _public function_ `FTimePair() : PredExecTime(0.0) , ThisExecTime(0.0)`

### `Source/Editor/AudioEditor/Private/SoundCueGraphNodeFactory.h` (Private)


#### class `FSoundCueGraphNodeFactory`  
`class FSoundCueGraphNodeFactory : public FGraphPanelNodeFactory`  
_L16-33_
- inherits: `FGraphPanelNodeFactory`
- L18 _private function_ `virtual TSharedPtr<class SGraphNode> CreateNode(class UEdGraphNode* InNode) const override`

### `Source/Editor/AudioEditor/Private/SoundModulationDestinationLayout.h` (Private)


#### class `FSoundModulationDestinationLayoutCustomization`  
`class FSoundModulationDestinationLayoutCustomization : public IPropertyTypeCustomization`  
_L11-23_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FSoundModulationDefaultSettingsLayoutCustomization`  
`class FSoundModulationDefaultSettingsLayoutCustomization : public IPropertyTypeCustomization`  
_L25-37_
- inherits: `IPropertyTypeCustomization`
- L28 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L35 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FSoundModulationDefaultRoutingSettingsLayoutCustomization`  
`class FSoundModulationDefaultRoutingSettingsLayoutCustomization : public IPropertyTypeCustomization`  
_L39-51_
- inherits: `IPropertyTypeCustomization`
- L42 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L48 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L49 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/AudioEditor/Private/SoundSubmixEditor.h` (Private)


#### class `FSoundSubmixEditor`  
`class FSoundSubmixEditor : public ISoundSubmixEditor, public FGCObject, public FEditorUndoClient, public FNotifyHook`  
_L33-140_
- inherits: `ISoundSubmixEditor,FGCObject,FEditorUndoClient,FNotifyHook`
- L36 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L37 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L46 _public prototype_ `void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified sound submix object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The sound submix to edit
- L48 _public prototype_ `virtual ~FSoundSubmixEditor();`
- L51 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L52 _public function_ `virtual FString GetReferencerName() const override`
- L58 _public prototype_ `virtual FText GetBaseToolkitName() const override;` — FAssetEditorToolkit interface
- L59 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L60 _public prototype_ `virtual FText GetToolkitName() const override;`
- L61 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L62 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L63 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L66 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L69 _public prototype_ `void CreateSoundSubmix(UEdGraphPin* FromPin, FVector2D Location, const FString& Name) override;`
- L73 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;` — FNotifyHook Interface
- L76 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L77 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L79 _public prototype_ `void AddMissingEditableSubmixes();`
- L82 _public prototype_ `void RefreshDetails();` — Forces the details panel to re-evaluate property metadata (e.g. EditConditions) after a graph topology change
- L85 _public prototype_ `void SelectSubmixes(TSet<USoundSubmixBase*>& InSubmixes);` — Select node associated with the provided submix
- L88 _public prototype_ `UEdGraph* GetGraph();` — Returns current graph handled by editor
- L91 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);`
- L92 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L95 _private prototype_ `void CreateInternalWidgets(USoundSubmixBase* InSoundSubmix);` — Creates all internal widgets for the tabs to point at
- L98 _private prototype_ `TSharedRef<SGraphEditor> CreateGraphEditorWidget(USoundSubmixBase* InSoundSubmix);` — Create new graph editor widget
- L101 _private prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L104 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L107 _private prototype_ `void AddEditableSubmixChildren(USoundSubmixBase* ParentSubmix);` — Adds all children of provided parent submix as editable
- L110 _private prototype_ `void SelectAllNodes();` — Select every node in the graph
- L113 _private prototype_ `bool CanSelectAllNodes() const;` — Whether we can select every node
- L116 _private prototype_ `void RemoveSelectedNodes();` — Remove the currently selected nodes from editor view
- L119 _private prototype_ `bool CanRemoveNodes() const;` — Whether we are able to remove the currently selected nodes
- L122 _private prototype_ `void UndoGraphAction();` — Called to undo the last action
- L125 _private prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L129 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;` — Graph Editor
- L132 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Property View
- L135 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L138 _private member_ `static const FName GraphCanvasTabId;` — The tab ids for all the tabs used
- L139 _private member_ `static const FName PropertiesTabId;`

### `Source/Editor/AudioEditor/Public/AssetTypeActions/AssetDefinitionDefault_AudioDiffable.h` (Public)


#### class `UAssetDefinitionDefault_AudioDiffable`  
`class UAssetDefinitionDefault_AudioDiffable : public UAssetDefinitionDefault`  
_L9-18_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Source/Editor/AudioEditor/Public/AssetTypeActions/AssetDefinition_SoundBase.h` (Public)


#### class `UAssetDefinition_SoundAssetBase`  
`class UAssetDefinition_SoundAssetBase : public UAssetDefinitionDefault_AudioDiffable`  
_L26-36_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L33 _public prototype_ `virtual TArray<FToolMenuSection*> RebuildSoundContextMenuSections() const;` — Enables asset types used for audio to customize and register a given menu section for use in the ContentBrowser right-click menu and organize it accordingly.
- L35 _public prototype_ `FToolMenuSection* FindSoundContextMenuSection(FName SectionName) const;`

#### class `UAssetDefinition_SoundBase`  
`class UAssetDefinition_SoundBase : public UAssetDefinition_SoundAssetBase`  
_L39-76_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_SoundAssetBase`
- L45 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L46 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L47 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L48 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L49 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const override;`
- L50 _public prototype_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override;`
- L51 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L52 _public prototype_ `virtual void GetAssetActionButtonExtensions(const FAssetData& InAssetData, TArray<FAssetButtonActionExtension>& OutExtensions) const override;`
- L55 _public prototype_ `virtual TArray<FToolMenuSection*> RebuildSoundContextMenuSections() const override;`
- L58 _public prototype_ `static void ExecutePlaySound(const FToolMenuContext& InContext);` — Menu Extension statics
- L59 _public prototype_ `static void ExecuteStopSound(const FToolMenuContext& InContext);`
- L60 _public prototype_ `static bool CanExecutePlayCommand(const FToolMenuContext& InContext);`
- L61 _public prototype_ `static ECheckBoxState IsActionCheckedMute(const FToolMenuContext& InContext);`
- L62 _public prototype_ `static ECheckBoxState IsActionCheckedSolo(const FToolMenuContext& InContext);`
- L63 _public prototype_ `static void ExecuteMuteSound(const FToolMenuContext& InContext);`
- L64 _public prototype_ `static void ExecuteSoloSound(const FToolMenuContext& InContext);`
- L65 _public prototype_ `static void ExecuteClearMutesAndSolos(const FToolMenuContext& InContext);`
- L66 _public prototype_ `static bool CanExecuteMuteCommand(const FToolMenuContext& InContext);`
- L67 _public prototype_ `static bool CanExecuteSoloCommand(const FToolMenuContext& InContext);`
- L68 _public prototype_ `static bool CanExecuteClearMutesAndSolos(const FToolMenuContext& InContext);`
- L69 _public prototype_ `static bool IsPlayingContextAsset(const FToolMenuContext& InContext, bool bMustMatchContext);`
- L70 _public prototype_ `static const USoundBase* GetPlayingSound();`
- L73 _public prototype_ `static TSharedPtr<SWidget> GetSoundBaseThumbnailOverlay(const FAssetData& InAssetData, TFunction<FReply()>&& OnClicked);` — Asset definition static utilities
- L74 _public prototype_ `static void GetSoundBaseAssetActionButtonExtensions(const FAssetData& InAssetData, TArray<FAssetButtonActionExtension>& OutExtensions);`
- L75 _public prototype_ `static EAssetCommandResult ActivateSoundBase(const FAssetActivateArgs& ActivateArgs);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AudioEditor` (scope `UE`)
- L17 _prototype_ `void StopSound();` (scope `UE::AudioEditor`)
- L19 _prototype_ `void PlaySound(USoundBase* Sound);` (scope `UE::AudioEditor`)
- L21 _prototype_ `bool IsSoundPlaying(USoundBase* Sound);` (scope `UE::AudioEditor`)
- L22 _prototype_ `bool IsSoundPlaying(const FAssetData& AssetData);` (scope `UE::AudioEditor`)

### `Source/Editor/AudioEditor/Public/AssetTypeActions/AssetDefinition_SoundWave.h` (Public)


#### class `UAssetDefinition_SoundWave`  
`class UAssetDefinition_SoundWave : public UAssetDefinition_SoundBase`  
_L14-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinition_SoundBase`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L25 _public prototype_ `virtual bool CanImport() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Public/AssetTypeActions/AssetTypeActions_AudioDiffable.h` (Public)


#### class `FAssetTypeActions_AudioDiffable`  
`class FAssetTypeActions_AudioDiffable : public FAssetTypeActions_Base`  
_L6-12_
- inherits: `FAssetTypeActions_Base`
- L10 _public prototype_ `virtual void PerformAssetDiff(UObject* OldAsset, UObject* NewAsset, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`

### `Source/Editor/AudioEditor/Public/AssetTypeActions/AssetTypeActions_SoundBase.h` (Public)


#### class `FAssetTypeActions_SoundBase`  
`FAssetTypeActions_SoundBase : public FAssetTypeActions_AudioDiffable`  
_L28-80_
- inherits: `FAssetTypeActions_AudioDiffable`
- L32 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L33 _public function_ `virtual FColor GetTypeColor() const override`
- L34 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L35 _public prototype_ `virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;`
- L36 _public function_ `virtual uint32 GetCategories() override`
- L37 _public function_ `virtual bool CanFilter() override`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L42 _protected prototype_ `void PlaySound(USoundBase* Sound) const;` — Plays the specified sound wave
- L45 _protected prototype_ `void StopSound() const;` — Stops any currently playing sounds
- L48 _protected prototype_ `bool IsSoundPlaying(USoundBase* Sound) const;` — Return true if the specified sound is playing
- L51 _protected prototype_ `bool IsSoundPlaying(const FAssetData& AssetData) const;` — Return true if the specified asset's sound is playing
- L55 _private prototype_ `void ExecutePlaySound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Handler for when PlaySound is selected
- L58 _private prototype_ `void ExecuteStopSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Handler for when StopSound is selected
- L61 _private prototype_ `bool CanExecutePlayCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Returns true if only one sound is selected to play
- L64 _private prototype_ `void ExecuteMuteSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Handler for Mute is selected
- L67 _private prototype_ `void ExecuteSoloSound(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Handler for Solo is selected
- L70 _private prototype_ `bool IsActionCheckedMute(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Returns true if the mute state is set.
- L73 _private prototype_ `bool IsActionCheckedSolo(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Returns true if the solo state is set.
- L76 _private prototype_ `bool CanExecuteMuteCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Returns true if its possible to mute a sound
- L79 _private prototype_ `bool CanExecuteSoloCommand(TArray<TWeakObjectPtr<USoundBase>> Objects) const;` — Returns true if its possible to solo a sound

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Public/AudioEditorModule.h` (Public)


#### class `FAudioComponentBroker`  
`class FAudioComponentBroker : public IComponentAssetBroker`  
_L38-44_
- inherits: `IComponentAssetBroker`
- L41 _public prototype_ `UClass* GetSupportedAssetClass() override;`
- L42 _public prototype_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override;`
- L43 _public prototype_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override;`

#### struct `FAudioEditorDeviceSettings`  
`struct FAudioEditorDeviceSettings`  
_L46-50_
- L48 _public member_ `bool bUseSystemDevice = true;`
- L49 _public member_ `FString DeviceId;`

#### class `IAudioEditorModule`  
`class IAudioEditorModule : public IModuleInterface`  
_L53-113_
- inherits: `IModuleInterface`
- desc: Sound class editor module interface
- L58 _public prototype_ `virtual void RegisterAssetActions() = 0;` — `UE_DEPRECATED(5.8, "Asset action where converted to asset definition, there is no need to register them manually anymore")` — Registers audio editor asset actions.
- L62 _public prototype_ `virtual void RegisterAudioMixerAssetActions() = 0;` — `UE_DEPRECATED(5.8, "Asset action where converted to asset definition, there is no need to register them manually anymore")` — Registers audio editor asset actions specific to audio mixer functionality.
- L65 _public prototype_ `virtual void RegisterEffectPresetAssetActions() = 0;` — Registers effect preset asset actions.
- L68 _public prototype_ `virtual TSharedRef<FAssetEditorToolkit> CreateSoundClassEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, USoundClass* InSoundClass ) = 0;` — Creates a new sound class editor for a sound class object.
- L71 _public prototype_ `virtual TSharedRef<FAssetEditorToolkit> CreateSoundSubmixEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, USoundSubmixBase* InSoundSubmix) = 0;` — Creates a new sound submix editor for a sound submix object.
- L74 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundClassMenuExtensibilityManager() = 0;` — Returns the menu extensibility manager for the given audio editor type.
- L77 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundClassToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the given audio editor type.
- L80 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundSubmixMenuExtensibilityManager() = 0;` — Returns the menu extensibility manager for the given audio editor type.
- L83 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundSubmixToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the given audio editor type.
- L86 _public prototype_ `virtual TSharedRef<ISoundCueEditor> CreateSoundCueEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, USoundCue* SoundCue) = 0;` — Creates a new material editor, either for a material or a material function.
- L89 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundCueMenuExtensibilityManager() = 0;` — Returns the menu extensibility manager for the given audio editor type.
- L92 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSoundCueToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the given audio editor type.
- L95 _public prototype_ `virtual void ReplaceSoundNodesInGraph(USoundCue* SoundCue, UDialogueWave* DialogueWave, TArray<USoundNode*>& NodesToReplace, const FDialogueContextMapping& ContextMapping) = 0;` — Replaces sound cue nodes in the graph.
- L98 _public prototype_ `virtual USoundWave* ImportSoundWave(UPackage* const SoundWavePackage, const FString& InSoundWaveAssetName, const FString& InWavFilename) = 0;` — Imports a sound wave from the given package.
- L101 _public prototype_ `virtual bool IsRestrictedMode() const = 0;` — Queries if the Audio editor is in "restricted mode"
- L104 _public prototype_ `virtual void SetRestrictedMode(bool bInRestricted) = 0;` — Sets if the Audio editor is in "restricted mode" (certain asset actions may be disabled)
- L107 _public prototype_ `virtual TOptional<FAudioEditorDeviceSettings> GetAudioEditorDeviceSettings() const = 0;` — Returns the default audio editor device settings
- L110 _public prototype_ `DECLARE_DELEGATE_OneParam(SoundWaveEditorOpenDelegate, TArray<USoundWave*>);` — Allows systems to register to open soundwave files with custom editor
- L112 _public member_ `SoundWaveEditorOpenDelegate SoundWaveEditorOpen;`

#### Free symbols / members of external scopes

- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioEditor, Log, All);`
- L36 _externvar_ `extern const FName AudioEditorAppIdentifier;`
- L110 _delegate_ `DECLARE_DELEGATE_OneParam(SoundWaveEditorOpenDelegate, TArray<USoundWave*>);` — Allows systems to register to open soundwave files with custom editor

### `Source/Editor/AudioEditor/Public/ISoundClassEditor.h` (Public)


#### class `ISoundClassEditor`  
`class ISoundClassEditor : public FAssetEditorToolkit`  
_L8-19_
- inherits: `FAssetEditorToolkit`
- L18 _public prototype_ `virtual void CreateSoundClass(class UEdGraphPin* FromPin, const FVector2D& Location, const FString& Name) = 0;` — Creates a new sound class @param	FromPin		Pin that was dragged to create sound class @param	Location	Location for new sound class @param	Name		Name of the new sound class

### `Source/Editor/AudioEditor/Public/ISoundCueEditor.h` (Public)


#### class `ISoundCueEditor`  
`class ISoundCueEditor : public FAssetEditorToolkit`  
_L11-39_
- inherits: `FAssetEditorToolkit`
- L15 _public prototype_ `virtual USoundCue* GetSoundCue() const = 0;` — Returns the SoundCue asset inspected by the editor
- L18 _public prototype_ `virtual void SetSelection(TArray<UObject*> SelectedObjects) = 0;` — Assigns the currently selected nodes to the property control
- L21 _public prototype_ `virtual bool CanPasteNodes() const = 0;` — Checks whether nodes can currently be pasted
- L24 _public prototype_ `virtual void PasteNodesHere(const FVector2D& Location) = 0;` — Paste nodes at a specific location
- L32 _public prototype_ `virtual bool GetBoundsForSelectedNodes(class FSlateRect& Rect, float Padding) = 0;` — Get the bounding area for the currently selected nodes @param Rect Final output bounding area, including padding @param Padding An amount of padding to add to all sides of the bounds @return false if nothing is selected
- L35 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const = 0;` — Gets the number of nodes that are currently selected
- L38 _public prototype_ `virtual TSet<UObject*> GetSelectedNodes() const = 0;` — Get the currently selected set of nodes

### `Source/Editor/AudioEditor/Public/ISoundSubmixEditor.h` (Public)


#### class `ISoundSubmixEditor`  
`class ISoundSubmixEditor : public FAssetEditorToolkit`  
_L10-21_
- inherits: `FAssetEditorToolkit`
- L20 _public prototype_ `virtual void CreateSoundSubmix(UEdGraphPin* FromPin, FVector2D Location, const FString& Name) = 0;` — Creates a new sound submix @param	FromPin		Pin that was dragged to create sound class @param	Location	Location for new sound class @param	Name		Name of the new sound class

### `Source/Editor/AudioEditor/Public/SoundClassEditorCommands.h` (Public)


#### class `FSoundClassEditorCommands`  
`class FSoundClassEditorCommands : public TCommands<FSoundClassEditorCommands>`  
_L19-42_
- inherits: `TCommands<FSoundClassEditorCommands>`
- L23 _public function_ `FSoundClassEditorCommands() : TCommands<FSoundClassEditorCommands>("SoundClassEditor", NSLOCTEXT("Contexts", "SoundClassEditor", "SoundClass Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L29 _public member_ `TSharedPtr<FUICommandInfo> ToggleSolo;` — Plays the SoundCue or stops the currently playing cue/node
- L32 _public member_ `TSharedPtr<FUICommandInfo> ToggleMute;` — Plays the SoundCue or stops the currently playing cue/node
- L35 _public member_ `TSharedPtr<FUICommandInfo> ViewReferences;` — Shows the reference viewer for the selected assets
- L38 _public member_ `TSharedPtr<FUICommandInfo> FindInSoundClassGraph;` — Show the Find in Sound Class Graph window.
- L41 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/AudioEditor/Public/SoundClassEditorUtilities.h` (Public)


#### class `FSoundClassEditorUtilities`  
`class FSoundClassEditorUtilities`  
_L12-27_
- L23 _public prototype_ `static void CreateSoundClass(const class UEdGraph* Graph, class UEdGraphPin* FromPin, const FVector2D& Location, FString Name);` — Create a new SoundClass @param	Graph		Graph representing sound classes @param	FromPin		Pin that was dragged to create sound class @param	Location	Location for new sound class
- L26 _private function_ `FSoundClassEditorUtilities()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Public/SoundCueEditorUtilities.h` (Public)


#### class `FSoundCueEditorUtilities`  
`class FSoundCueEditorUtilities`  
_L23-72_
- L28 _public prototype_ `static bool CanPasteNodes(const class UEdGraph* Graph);` — Can we paste to this graph?
- L31 _public prototype_ `static void PasteNodesHere(class UEdGraph* Graph, const FVector2D& Location);` — Perform paste on graph, at location
- L40 _public prototype_ `static void CreateWaveContainers(TArray<class USoundWave*>& SelectedWaves, class USoundCue* SoundCue, TArray<class USoundNode*>& OutPlayers, FVector2D Location);` — Adds SoundNodeWavePlayer nodes based on selected objects @param SelectedWaves List of selected SoundWaves to create player nodes for @param SoundCue The SoundCue that the nodes will be part of @param OutPlayers Stores all created nodes @param Location Position of first created node
- L49 _public prototype_ `static void CreateDialogueContainers(TArray<class UDialogueWave*>& SelectedDialogues, USoundCue* SoundCue, TArray<class USoundNode*>& OutPlayers, FVector2D Location);` — Adds USoundNodeDialoguePlayer nodes based on selected objects @param SelectedDialogues List of selected DialogueWaves to create player nodes for @param SoundCue The SoundCue that the nodes will be part of @param OutPlayers Stores all created nodes @param Location Position of first created node
- L59 _public prototype_ `static bool GetBoundsForSelectedNodes(const UEdGraph* Graph, class FSlateRect& Rect, float Padding = 0.0f);` — Get the bounding area for the currently selected nodes @param Graph The Graph we are finding bounds for @param Rect Final output bounding area, including padding @param Padding An amount of padding to add to all sides of the bounds @return false if nothing is selected
- L62 _public prototype_ `static int32 GetNumberOfSelectedNodes(const UEdGraph* Graph);` — Gets the number of nodes that are currently selected
- L65 _public prototype_ `static TSet<UObject*> GetSelectedNodes(const UEdGraph* Graph);` — Get the currently selected set of nodes
- L69 _private prototype_ `static TSharedPtr<class ISoundCueEditor> GetISoundCueEditorForObject(const UObject* ObjectToFocusOn);` — Get ISoundCueEditor for given object, if it exists
- L71 _private function_ `FSoundCueEditorUtilities()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Public/SoundCueGraphEditorCommands.h` (Public)


#### class `FSoundCueGraphEditorCommands`  
`class FSoundCueGraphEditorCommands : public TCommands<FSoundCueGraphEditorCommands>`  
_L19-60_
- inherits: `TCommands<FSoundCueGraphEditorCommands>`
- L23 _public function_ `FSoundCueGraphEditorCommands() : TCommands<FSoundCueGraphEditorCommands>("SoundCueGraphEditor", NSLOCTEXT("Contexts", "SoundCueGraphEditor", "SoundCue Graph Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L29 _public member_ `TSharedPtr<FUICommandInfo> PlayCue;` — Plays the SoundCue
- L32 _public member_ `TSharedPtr<FUICommandInfo> StopCueNode;` — Stops the currently playing cue/node
- L35 _public member_ `TSharedPtr<FUICommandInfo> PlayNode;` — Plays the selected node
- L38 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayback;` — Plays the SoundCue or stops the currently playing cue/node
- L41 _public member_ `TSharedPtr<FUICommandInfo> BrowserSync;` — Selects the SoundWave in the content browser
- L44 _public member_ `TSharedPtr<FUICommandInfo> BreakLink;` — Breaks the node input/output link
- L47 _public member_ `TSharedPtr<FUICommandInfo> AddInput;` — Adds an input to the node
- L50 _public member_ `TSharedPtr<FUICommandInfo> DeleteInput;` — Removes an input from the node
- L53 _public member_ `TSharedPtr<FUICommandInfo> ToggleSolo;` — Plays the SoundCue or stops the currently playing cue/node
- L56 _public member_ `TSharedPtr<FUICommandInfo> ToggleMute;` — Plays the SoundCue or stops the currently playing cue/node
- L59 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/AudioEditor/Public/SoundSubmixDefaultColorPalette.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L23 _variable_ `const FColor DefaultSubmixColor = FColor(143, 190, 0);` (scope `Audio`)
- L24 _variable_ `const FColor SoundfieldDefaultSubmixColor = FColor(0, 168, 198);` (scope `Audio`)
- L25 _variable_ `const FColor EndpointDefaultSubmixColor = FColor(249, 242, 231);` (scope `Audio`)
- L26 _variable_ `const FColor SoundfieldEndpointDefaultSubmixColor = FColor(64, 192, 203);` (scope `Audio`)
- L29 _variable_ `const FName SoundSubmixName = TEXT("Sou` (scope `Audio`) — These names are used to identify pins by their owning node.
- L30 _variable_ `const FName SoundfieldSubmixName = TEXT("Sou` (scope `Audio`)
- L31 _variable_ `const FName EndpointSubmixName = TEXT("End` (scope `Audio`)
- L32 _variable_ `const FName SoundfieldEndpointSubmixName = TEXT("Sou` (scope `Audio`)
- L35 _prototype_ `FName GetNameForSubmixType(const USoundSubmixBase* InSubmix);` (scope `Audio`) — These utility functions are used
- L36 _prototype_ `FColor GetColorForSubmixType(const USoundSubmixBase* InSubmix);` (scope `Audio`)
- L37 _prototype_ `FColor GetColorForSubmixType(const FName& InSubmixName);` (scope `Audio`)
- L38 _prototype_ `const bool IsConnectionPerformingSoundfieldConversion(const USoundSubmixBase* InputSubmix, const USoundSubmixBase* OutputSubmix);` (scope `Audio`)

### `Source/Editor/AudioEditor/Public/SoundSubmixEditorUtilities.h` (Public)


#### class `FSoundSubmixEditorUtilities`  
`class FSoundSubmixEditorUtilities`  
_L14-29_
- L25 _public prototype_ `static void CreateSoundSubmix(const UEdGraph* Graph, UEdGraphPin* FromPin, FVector2D Location, const FString& Name);` — Create a new SoundSubmix @param	Graph		Graph representing sound classes @param	FromPin		Pin that was dragged to create sound class @param	Location	Location for new sound class
- L28 _private function_ `FSoundSubmixEditorUtilities()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOEDITOR_API`

### `Source/Editor/AudioEditor/Public/SubmixDetailsCustomization.h` (Public)


#### class `FNameSelectorGenerator`  
`class FNameSelectorGenerator`  
_L26-61_
- desc: Utility class to build combo boxes out of arrays of names.
- L32 _public prototype_ `FNameSelectorGenerator(FProtectedToken);`
- L42 _public prototype_ `TSharedRef<SWidget> MakeNameSelectorWidget(TArray<FName>& InNameArray, FNameSelectorCallbacks&& InCallbacks);` — Use this to generate a combo box widget.
- L45 _public prototype_ `static TSharedRef<FNameSelectorGenerator> MakeInstance();` — Makes a new instance of the name selector generator class
- L49 _protected prototype_ `void SetWeakThis(TWeakPtr<FNameSelectorGenerator>&& InWeakThis);` — This needs to be called after construction and after it has been bound to a TSharedPtr
- L51 _protected prototype_ `void OnSelectionChanged(TSharedPtr<FName> NameItem, ESelectInfo::Type SelectInfo);`
- L52 _protected prototype_ `TSharedRef<SWidget> HandleResponseComboBoxGenerateWidget(TSharedPtr<FName> StringItem);`
- L53 _protected prototype_ `FText GetComboBoxToolTip() const;`
- L54 _protected prototype_ `FText GetComboBoxContent() const;`
- L56 _protected member_ `TArray<TSharedPtr<FName>> CachedNameArray;`
- L57 _protected member_ `FNameSelectorCallbacks CachedCallbacks;`
- L60 _private member_ `TWeakPtr<FNameSelectorGenerator> WeakThis;`

#### struct `FNameSelectorGenerator::FProtectedToken`  
`struct FProtectedToken`  
_L29-29_
- L29 _public prototype_ `struct FProtectedToken`

#### struct `FNameSelectorGenerator::FNameSelectorCallbacks`  
`struct FNameSelectorCallbacks`  
_L34-39_
- L36 _public member_ `TUniqueFunction<void(FName)> OnNewNameSelected;`
- L37 _public member_ `TUniqueFunction<FName()> GetCurrentlySelectedName;`
- L38 _public member_ `TUniqueFunction<FString()> GetTooltipText;`

#### class `FSoundfieldSubmixDetailsCustomization`  
`class FSoundfieldSubmixDetailsCustomization : public IDetailCustomization`  
_L63-80_
- inherits: `IDetailCustomization`
- L69 _public prototype_ `FSoundfieldSubmixDetailsCustomization(FPrivateToken);`
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class
- L75 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L79 _private member_ `TSharedPtr<FNameSelectorGenerator> SoundfieldFormatNameSelectorGenerator;`

#### struct `FSoundfieldSubmixDetailsCustomization::FPrivateToken`  
`struct FPrivateToken`  
_L66-66_
- L66 _public prototype_ `struct FPrivateToken`

#### class `FEndpointSubmixDetailsCustomization`  
`class FEndpointSubmixDetailsCustomization : public IDetailCustomization, public FNameSelectorGenerator`  
_L82-96_
- inherits: `IDetailCustomization,FNameSelectorGenerator`
- L85 _public prototype_ `FEndpointSubmixDetailsCustomization(FProtectedToken);`
- L88 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class
- L91 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L95 _private member_ `TSharedPtr<FNameSelectorGenerator> EndpointTypeNameSelectorGenerator;`

#### class `FSoundfieldEndpointSubmixDetailsCustomization`  
`class FSoundfieldEndpointSubmixDetailsCustomization : public IDetailCustomization, public FNameSelectorGenerator`  
_L98-112_
- inherits: `IDetailCustomization,FNameSelectorGenerator`
- L101 _public prototype_ `FSoundfieldEndpointSubmixDetailsCustomization(FProtectedToken);`
- L104 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class
- L107 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L111 _private member_ `TSharedPtr<FNameSelectorGenerator> EndpointTypeNameSelectorGenerator;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API AUDIOEDITOR_API`
