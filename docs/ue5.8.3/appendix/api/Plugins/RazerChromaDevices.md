# Plugins / RazerChromaDevices

- module root: `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices`
- headers: 9; symbols: 159
- symbol kinds: class=6, enum=1, enumerator=8, macro=4, member=51, prototype=59, struct=3, typedef=27
- PrivateDependencyModuleNames: RazerChromaSDK
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, InputCore, InputDevice, Projects

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Private/RazerChromaDevicesModule.h` (Private)


#### class `FRazerChromaDeviceModule`  
`class FRazerChromaDeviceModule : public IInputDeviceModule`  
_L14-90_
- inherits: `IInputDeviceModule`
- desc: Input Device module that will create the Razer Chroma input device module.
- L17 _public prototype_ `static FRazerChromaDeviceModule* Get();`
- L19 _public prototype_ `static FName GetModularFeatureName();`
- L26 _public prototype_ `static const FString RazerErrorToString(const int64 ErrorCode);` — Returns a string representing the given Razer Error code @see RzErrors.h
- L31 _protected prototype_ `virtual void StartupModule() override;`
- L32 _protected prototype_ `virtual void ShutdownModule() override;`
- L33 _protected prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L41 _protected prototype_ `bool IsChromaAvailable() const;` — Returns true if the Chroma DLL has been successfully loaded
- L46 _protected prototype_ `void CleanupSDK();` — Cleans up the SDK and all currently playing animations.
- L49 _protected member_ `void* RazerChromaEditorDLLHandle = nullptr;` — Handle to the Razer Chroma dynamic DLL
- L52 _protected member_ `bool bLoadedDynamicAPISuccessfully = false;` — True if the dynamic API was successfully loaded from the DLL handle.
- L58 _protected member_ `TMap<FString, int32> LoadedAnimationIdMap;` — A map of animation names (URazerChromaAnimationAsset::AnimationName) to their Animation ID loaded in from Razer Chroma.
- L67 _public prototype_ `void ForceReinitalize();` — This will call the Unit and Init functions over again. This can be useful if you need to completely reset the state of your razer devices as if the application has been closed and re-opened again
- L72 _public prototype_ `static bool IsChromaRuntimeAvailable();` — Returns true if the Razer Chroma runtime is available (the DLL has been successfully loaded and all of the functions we request have been found)
- L79 _public prototype_ `const int32 FindOrLoadAnimationData(const URazerChromaAnimationAsset* AnimAsset);` — Attempts to load the given animation property. Returns the int ID of the animation. -1 is invalid and means it failed to load.
- L86 _public prototype_ `const int32 FindOrLoadAnimationData(const FString& AnimName, const uint8* AnimByteBuffer);` — Attempts to load the given animation property. Returns the int ID of the animation. -1 is invalid and means it failed to load.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RAZERCHROMADEVICES_API`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Private/RazerChromaDynamicAPI.h` (Private)


#### struct `FRazerChromaEditorDynamicAPI`  
`struct FRazerChromaEditorDynamicAPI`  
_L20-150_
- desc: The Razer Chroma Editor Dynamic API, which should be loaded via the CChromaEditorLibrary64.dll. To see a full list of exported functions from this DLL, you can use the Microsoft Visual Studio command prompt and run the DUMPBIN command: dumpbin /EXPORTS CChromaEditorLibrary.dll See https://assets.razerzone.com/dev_portal/C%2B%2B/en/index.html#c_interface for details
- L27 _public prototype_ `[[nodiscard]] static bool LoadAPI(void* RazerChromaEditorDLLHandle);` — Loads the Razer Chroma API, returns true if successful. This will FATAL ERROR if RazerChromaDLLHandle is null.
- L30 _public typedef_ `typedef RZRESULT(*INIT)(void);` — Declare some function pointer types that are the signature of the function we need
- L33 _public typedef_ `typedef RZRESULT(*INITSDK)(ChromaSDK::APPINFOTYPE* AppInfo);` — Initalize the Razer Chroma app with some specific settings
- L35 _public typedef_ `typedef RZRESULT(*UNINIT)(void);`
- L37 _public typedef_ `typedef void (*PLAYANIMATIONNAME)(const wchar_t* path, bool loop);`
- L39 _public typedef_ `typedef int32 (*PLAYANIMATION)(int32 animationId, bool bLoop);`
- L41 _public typedef_ `typedef int32 (*OPENANIMATIONFROMMEMORY)(const BYTE* data, const wchar_t* name);`
- L43 _public typedef_ `typedef int32 (*STOPANIMATION)(int32 AnimationId);`
- L45 _public typedef_ `typedef RZRESULT(*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L47 _public typedef_ `typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L49 _public typedef_ `typedef RZRESULT(*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L51 _public typedef_ `typedef RZRESULT(*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L53 _public typedef_ `typedef RZRESULT(*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L55 _public typedef_ `typedef RZRESULT(*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L57 _public typedef_ `typedef RZRESULT(*CREATECHROMALINKEFFECT)(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);`
- L59 _public typedef_ `typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);`
- L61 _public typedef_ `typedef RZRESULT(*DELETEEFFECT)(RZEFFECTID EffectId);`
- L63 _public typedef_ `typedef void (*SETIDLEANIMATION)(int32 animationId);`
- L65 _public typedef_ `typedef void (*USEIDLEANIMATIONS)(bool bUseIdleAnimation);`
- L67 _public typedef_ `typedef void (*STOPALLANIMATIONS)();`
- L69 _public typedef_ `typedef void (*CLOSEALL)();`
- L71 _public typedef_ `typedef void (*PAUSEANIMATION)(int32 animationId);`
- L73 _public typedef_ `typedef void (*RESUMEANIMATION)(int32 animationId, bool loop);`
- L75 _public typedef_ `typedef bool (*ISANIMATIONPLAYING)(int32 animationId);`
- L77 _public typedef_ `typedef bool (*ISANIMATIONPAUSED)(int32 animationId);`
- L79 _public typedef_ `typedef float(*GETTOTALDURATION)(int32 animationId);`
- L81 _public typedef_ `typedef RZRESULT(*SETEVENTNAME)(LPCTSTR name);`
- L83 _public typedef_ `typedef void(*USEFORWARDCHROMAEVENTS)(bool toggle);`
- L89 _public member_ `static INIT Init;` — Initialize the razer chroma editor library
- L92 _public member_ `static INITSDK InitSDK;` — Initialize the razer chroma editor library with some additional description info about it
- L95 _public member_ `static UNINIT UnInit;` — Uninitialize the razer chroma editor library
- L98 _public member_ `static PLAYANIMATIONNAME PlayAnimationName;` — Plays an animation via its file path
- L101 _public member_ `static PLAYANIMATION PlayAnimationWithId;` — Plays an animation via the animation ID
- L104 _public member_ `static OPENANIMATIONFROMMEMORY OpenAnimationFromMemory;` — Opens an animation from a byte buffer, returning the int32 animation id
- L106 _public member_ `static STOPANIMATION StopAnimation;`
- L107 _public member_ `static CREATEEFFECT CreateEffect;`
- L108 _public member_ `static CREATEKEYBOARDEFFECT CreateKeyboardEffect;`
- L109 _public member_ `static CREATEHEADSETEFFECT CreateHeadsetEffect;`
- L110 _public member_ `static CREATEMOUSEPADEFFECT CreateMousepadEffect;`
- L111 _public member_ `static CREATEMOUSEEFFECT CreateMouseEffect;`
- L112 _public member_ `static CREATEKEYPADEFFECT CreateKeypadEffect;`
- L113 _public member_ `static CREATECHROMALINKEFFECT CreateChromaLinkEffect;`
- L114 _public member_ `static SETEFFECT SetEffect;`
- L115 _public member_ `static DELETEEFFECT DeleteEffect;`
- L118 _public member_ `static SETIDLEANIMATION SetIdleAnimation;` — Sets the idle animation of the application
- L121 _public member_ `static USEIDLEANIMATIONS SetUseIdleAnimations;` — Sets if we should use the current idle animation at all
- L124 _public member_ `static STOPALLANIMATIONS StopAllAnimations;` — Stops all animations that are currently playing
- L128 _public member_ `static CLOSEALL CloseAll;` — Closes all open animations so they can be reloaded from disk. You should call this on application shutdown
- L131 _public member_ `static PAUSEANIMATION PauseAnimation;` — Pauses the animation with the given int32 id
- L134 _public member_ `static RESUMEANIMATION ResumeAnimation;` — Resume the animation with the given int32 id
- L137 _public member_ `static ISANIMATIONPLAYING IsAnimationPlaying;` — Returns true if the given animation ID is currently playing.
- L140 _public member_ `static ISANIMATIONPAUSED IsAnimationPaused;` — Returns true if the given anim ID is currently paused
- L143 _public member_ `static GETTOTALDURATION GetTotalDuration;` — Returns the duration in seconds with the given animation ID
- L146 _public member_ `static SETEVENTNAME SetEventName;` — Returns zero if Chroma event can be named
- L149 _public member_ `static USEFORWARDCHROMAEVENTS UseForwardChromaEvents;` — Sets if PlayAnimation should send event name to SetEventName

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Private/RazerChromaInputDevice.h` (Private)


#### class `FRazerChromaInputDevice`  
`class FRazerChromaInputDevice : public IInputDevice`  
_L19-51_
- inherits: `IInputDevice`
- desc: This input device will handle the setting of device properties on Razer Chroma. It will not actually send any input events to the message handler, just set device properties like lights and other effects. TODO: Can we refactor SetDeviceProperty out into some other interface function so that we don't need all the other virtual functions?
- L22 _public prototype_ `explicit FRazerChromaInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);`
- L28 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L29 _protected prototype_ `virtual void SendControllerEvents() override;`
- L30 _protected prototype_ `virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L31 _protected prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L32 _protected prototype_ `virtual void SetChannelValue (int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;`
- L33 _protected prototype_ `virtual void SetChannelValues (int32 ControllerId, const FForceFeedbackValues &values) override;`
- L34 _protected prototype_ `virtual bool SupportsForceFeedback(int32 ControllerId) override;`
- L35 _protected prototype_ `virtual void SetLightColor(int32 ControllerId, FColor Color) override;`
- L36 _protected prototype_ `virtual void ResetLightColor(int32 ControllerId) override;`
- L37 _protected prototype_ `virtual void SetDeviceProperty(int32 ControllerId, const FInputDeviceProperty* Property) override;`
- L41 _protected member_ `TSharedRef<FGenericApplicationMessageHandler> MessageHandler;` — Message handler that we can use to tell the engine about input events
- L46 _protected member_ `void* RazerChromaDLLHandle;` — Pointer to the Razer Chroma DLL handle that has been loaded by the module.
- L48 _protected prototype_ `void HandlePropertySetLightColor(const FInputDeviceLightColorProperty& LightProperty);`
- L50 _protected prototype_ `void HandlePlayAnimationFile(const FRazerChromaPlayAnimationFile& Property);`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaAnimationAsset.h` (Public)


#### class `URazerChromaAnimationAsset`  
`class URazerChromaAnimationAsset : public UObject`  
_L17-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories = (Object), Meta = (DisplayName = "Razer Chroma Asset"))`
- inherits: `UObject`
- desc: Represents a single ".chroma" Razer animation file that can be played.
- L32 _public prototype_ `bool ImportFromFile(const FString& InFileName, const uint8*& Buffer, const uint8* BufferEnd);` — Imports the data for this razer chroma asset from the given binary file buffer. @param InFileName	The name of the file that this is being imported from. @param Buffer		Pointer to the byte buffer of chroma animation data @param BufferEnd		Pointer to the end of the animation byte buffer @return				True if successfully imported, false otherwise.
- L42 _public prototype_ `const FString& GetAnimationName() const;` — The name of this animation that Razer Chroma should consider. This is automatically set based on the .chroma animation file when imported, but you can rename it if you desire. @see URazerChromaAnimationAsset::AnimationName
- L49 _public prototype_ `const uint8* GetAnimByteBuffer() const;` — The raw byte data imported from the asset factory when reading a .chroma file. @see URazerChromaAnimationAsset::RawData
- L54 _protected prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`
- L65 _protected member_ `FString AnimationName;` — `UPROPERTY(EditAnywhere, NoClear, Category="Razer")` — The name of this animation that Razer Chroma should consider. This is automatically set based on the .chroma animation file when imported, but you can rename it if you desire.
- L71 _protected member_ `TArray<uint8> RawData;` — `UPROPERTY()` — The raw byte data imported from the asset factory when reading a .chroma file.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RAZERCHROMADEVICES_API`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaDeviceLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRazerChroma, Log, All);`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaDeviceProperties.h` (Public)


#### struct `FRazerChromaPlayAnimationFile`  
`struct FRazerChromaPlayAnimationFile : public FInputDeviceProperty`  
_L15-30_
- inherits: `FInputDeviceProperty`
- desc: Plays a Razer Chroma animation file (*.chroma files)
- L17 _public prototype_ `FRazerChromaPlayAnimationFile();`
- L19 _public prototype_ `static FName PropertyName();`
- L22 _public member_ `FString AnimName;` — The name of this animation that Razer Chroma should load
- L24 _public member_ `const uint8* AnimationByteBuffer = nullptr;`
- L29 _public member_ `bool bLooping = false;` — If true, then this animation should loop when played

#### class `URazerChromaPlayAnimationFile`  
`class URazerChromaPlayAnimationFile : public UInputDeviceProperty`  
_L33-53_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "Razer Chroma Play Animation File"))`
- inherits: `UInputDeviceProperty`
- L39 _protected prototype_ `virtual void EvaluateDeviceProperty_Implementation(const FPlatformUserId PlatformUser, const FInputDeviceId DeviceId, const float DeltaTime, const float Duration) override;`
- L40 _protected prototype_ `virtual FInputDeviceProperty* GetInternalDeviceProperty() override;`
- L44 _protected member_ `TObjectPtr<URazerChromaAnimationAsset> AnimAsset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Razer")` — The chroma animation to play
- L50 _protected member_ `bool bLooping = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Razer")` — If true, then this animation should loop when played
- L52 _protected member_ `FRazerChromaPlayAnimationFile InternalProperty = {};`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaDevicesDeveloperSettings.h` (Public)


#### enum `ERazerChromaDeviceTypes`  
`enum class ERazerChromaDeviceTypes : int32`  
_L17-27_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Bitmask options for Razer Chroma device types.
- L19 _public enumerator_ `None = 0x0000 UMETA(Hidden)`
- L20 _public enumerator_ `Keyboards = 0x0001`
- L21 _public enumerator_ `Mice = 0x0002`
- L22 _public enumerator_ `Headset = 0x0004`
- L23 _public enumerator_ `Mousepads = 0x0008`
- L24 _public enumerator_ `Keypads = 0x0010`
- L25 _public enumerator_ `ChromaLink = 0x0020`
- L26 _public enumerator_ `All = (Keyboards | Mice | Headset | Mousepads | Keypads | ChromaLink) UMETA(Hidden)`

#### struct `FRazerChromaAppInfo`  
`struct FRazerChromaAppInfo`  
_L34-103_
- reflection: `USTRUCT()`
- desc: This information will be used to populate data in Razer Synapse.
- L58 _public member_ `FString ApplicationTitle = TEXT("You` — `UPROPERTY(EditAnywhere, Category="Razer Chroma App Config", NoClear, meta=(MaxLength=236))` — The name of your application to report to Razer Synapse. In non-shipping builds, this will have the build target and type appended to it, which will make it show up as : "ApplicationTitle_<BuildType>_<BuildTarget>" in Razer Synapse. This is expected, and in a shipping build it will be displayed as only: "ApplicationTitle" This is necessary because if you register multiple executable names (i.e. <YourGame>.exe, <YourGame>-Win64-Shipping.exe, and <YourGame>-Win64-Test.exe) then Razer Synapse will only use the _first_ executable that you ran with this configuration. Appending the target names makes them unique in Synapse and easier to test. Cannot be empty. Char limit of 236.
- L68 _public member_ `FString ApplicationDescription = TEXT("Des` — `UPROPERTY(EditAnywhere, Category = "Razer Chroma App Config", NoClear, meta = (MaxLength = 1024))` — The description of your application to report to Razer Synapse. Cannot be empty. Char limit of 1024.
- L78 _public member_ `FString AuthorName = TEXT("Ent` — `UPROPERTY(EditAnywhere, Category = "Razer Chroma App Config", NoClear, meta = (MaxLength = 256))` — Name of the author of this application (company name) Cannot be empty. Char limit of 256.
- L88 _public member_ `FString AuthorContact = TEXT("Ent` — `UPROPERTY(EditAnywhere, Category = "Razer Chroma App Config", NoClear, meta = (MaxLength = 256))` — Contact info for the author of this application (normally a support email or something) Cannot be empty. Char limit of 256.
- L94 _public member_ `int32 SupportedDeviceTypes = static_cast<int32>(ERazerChromaDeviceTypes::All);` — `UPROPERTY(EditAnywhere, Category = "Razer Chroma App Config", meta = (Bitmask, BitmaskEnum = "/Script/RazerChromaDevices.ERazerChromaDeviceTypes"))` — A bitmask of the supported Razer Chroma devices for this project.
- L102 _public member_ `int32 Category = 2;` — `UPROPERTY(VisibleAnywhere, Category = "Razer Chroma App Config")` — The category of this application in Razer Synapse. Default: 2

#### class `URazerChromaDevicesDeveloperSettings`  
`class URazerChromaDevicesDeveloperSettings : public UDeveloperSettings`  
_L109-206_
- reflection: `UCLASS(MinimalAPI, Config=Game, DefaultConfig, meta=(DisplayName="Razer Chroma Settings"))`
- inherits: `UDeveloperSettings`
- desc: Project settings for the Razer Chroma API in Unreal.
- L119 _public prototype_ `const bool ShouldUseChromaAppInfoForInit() const;` — If true then on module startup with should use the Razer App Info to populate info about this application in Razer Synapse
- L126 _public prototype_ `const FRazerChromaAppInfo& GetRazerAppInfo() const;` — Returns the razer chroma app info @see URazerChromaDevicesDeveloperSettings::AppInfo
- L133 _public prototype_ `const bool IsRazerChromaEnabled() const;` — If true, Razer Chroma will be enabled. @see URazerChromaDevicesDeveloperSettings::bIsRazerChromaEnabled
- L140 _public prototype_ `const bool ShouldCreateRazerInputDevice() const;` — If true, then a IInputDevice will be created for Razer Chroma. @see URazerChromaDevicesDeveloperSettings::bCreateRazerChromaInputDevice
- L146 _public prototype_ `const URazerChromaAnimationAsset* GetIdleAnimation() const;` — This is the chroma animation file that should play when there are no other animations playing.
- L151 _protected prototype_ `virtual FName GetCategoryName() const override;`
- L162 _protected member_ `bool bIsRazerChromaEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category="Razer Chroma", meta = (ConfigRestartRequired = true))` — If true, Razer Chroma will be enabled. Useful for if you need to "hot fix" Chroma off in case something goes wrong. If this is false, we won't even load the Razer Chroma.dll file at all or attempt to open any animation files associated with Razer Chroma.
- L177 _protected member_ `bool bCreateRazerChromaInputDevice = false;` — `UPROPERTY(Config, EditAnywhere, Category="Razer Chroma", meta = (ConfigRestartRequired = true, EditCondition = "bIsRazerChromaEnabled"))` — If true, then a IInputDevice will be created for Razer Chroma. This Input Device will allow for Razer Chroma to support Input Device Properties such as setting the light color. This is desirable if you would like Razer Chroma to "just work" with any previous implementations of setting a device's light color that you may have in your project. If you set this to false, the Razer Chroma function library will still work, but any Input Device Properties will not. @see FRazerChromaInputDevice::SetDeviceProperty
- L186 _protected member_ `TObjectPtr<URazerChromaAnimationAsset> IdleAnimationAsset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Razer Chroma")` — This is the chroma animation file that should play when there are no other animations playing. If this is null then no idle animation will be set on boot
- L197 _protected member_ `bool bUseChromaAppInfoForInit = true;` — `UPROPERTY(Config, EditAnywhere, Category="Razer Chroma", meta = (ConfigRestartRequired = true))` — If true, then the razer app will be initialized using the additional "App Data" properties specified below. If this is false, the chroma SDK will be initialized without any additional information like what the name of the application is or what device types it supports. You very likely will want to fill this out for your game.
- L205 _protected member_ `FRazerChromaAppInfo AppInfo = {};` — `UPROPERTY(Config, EditAnywhere, Category = "App Configuration", meta = (ConfigRestartRequired = true, EditCondition="bUseChromaAppInfoForInit"))` — Some definitions about your app that is used to initialize Razer Chroma. This info will be used to populate Razer Synapse.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RAZERCHROMADEVICES_API`
- L28 _prototype_ `ENUM_CLASS_FLAGS(ERazerChromaDeviceTypes);`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaFunctionLibrary.h` (Public)


#### class `URazerChromaFunctionLibrary`  
`class URazerChromaFunctionLibrary final : public UBlueprintFunctionLibrary`  
_L21-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library for Razer Chroma devices. This function library is the main way that your gameplay code will likley interact with the Razer Chroma API to play animations or set any custom effects
- L34 _public prototype_ `static bool IsChromaRuntimeAvailable();` — `UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic, Category = "Razer Chroma")` — Returns true if the Razer Chroma runtime libraries are currently available. This will be false on any machines that do not have Razer Chroma installed on them, and thus cannot set any Razer Chroma effects.
- L47 _public prototype_ `static bool PlayChromaAnimation(const URazerChromaAnimationAsset* AnimToPlay, const bool bLooping = false);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma", meta = (ReturnDisplayName = "Was Successful"))` — Attempts to play the given Chroma animation file. If the Chroma Runtime is not available, nothing will happen. @param AnimToPlay		The Razer Chroma animation asset. @param bLooping		If true, this animation will loop (start re-playing after it finishes) @return	True if successfully played, false otherwise.
- L53 _public prototype_ `static bool IsAnimationPlaying(const URazerChromaAnimationAsset* Anim);` — `UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic, Category = "Razer Chroma", meta = (ReturnDisplayName = "Is Playing"))` — Returns true if the given animation is currently playing.
- L59 _public prototype_ `static void StopChromaAnimation(const URazerChromaAnimationAsset* AnimToStop);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Stops the given Chroma Animation if it is currently playing.
- L65 _public prototype_ `static void PauseChromaAnimation(const URazerChromaAnimationAsset* AnimToPause);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Pauses the given animation if it is currently playing
- L71 _public prototype_ `static bool IsChromaAnimationPaused(const URazerChromaAnimationAsset* Anim);` — `UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic, Category = "Razer Chroma")` — Returns true if the given animation is currently paused.
- L80 _public prototype_ `static void ResumeChromaAnimation(const URazerChromaAnimationAsset* AnimToResume, const bool bLoop);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Resumes the given animation if it has been paused. @param AnimToResume	The animation to resume. @param bLoop			If true, this animation will loop (start re-playing after it finishes)
- L86 _public prototype_ `static void StopAllChromaAnimations();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Stops all currently active Chroma animations
- L95 _public prototype_ `static void SetIdleAnimation(const URazerChromaAnimationAsset* NewIdleAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Sets the idle animation for this application. This animation will play if no other animations are playing at the moment. By default, the idle animation is set via the project settings, but it can be changed at runtime.
- L101 _public prototype_ `static void SetUseIdleAnimation(const bool bUseIdleAnimation);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Sets whether or not we should use an idle currently an animation
- L107 _public prototype_ `static float GetTotalDuration(const URazerChromaAnimationAsset* Anim);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintCosmetic, Category = "Razer Chroma")` — Returns the duration in seconds of the specified animation.
- L115 _public prototype_ `static void SetAllDevicesStaticColor(const FColor& ColorToSet, const ERazerChromaDeviceTypes DeviceTypes = ERazerChromaDeviceTypes::All);` — Sets the color of every connected Razer Chroma Device to this static color @param ColorToSet		The color to set the devices to @param DeviceTypes		Which types of razer devices you would like to set the color on if they are available
- L124 _public prototype_ `static void SetAllDevicesStaticColor(const FColor& ColorToSet, UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/RazerChromaDevices.ER` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma", meta=(AutoCreateRefTerm="ColorToSet"))` — Sets the color of every connected Razer Chroma Device to this static color @param ColorToSet		The color to set the devices to (the alpha channel is not used) @param DeviceTypes	Which types of razer devices you would like to set the color on if they are available
- L129 _public prototype_ `static FString LexToString(const ERazerChromaDeviceTypes DeviceTypes);` — Converts ERazerChromaDeviceTypes enum to FString.
- L133 _public prototype_ `static FString Conv_RazerChromaDeviceTypesToString(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/RazerChromaDevices.ER` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (ERazerChromaDeviceTypes)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a ERazerChromaDeviceTypes enum to string.
- L142 _public prototype_ `static int32 SetEventName(const FString& name);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — Name the Chroma event to add extras like haptics to supplement the event @param name			Empty string will stop haptic playback Name specifies an identifier that adds extras to game events like haptics
- L152 _public prototype_ `static void UseForwardChromaEvents(const bool bToggle);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Razer Chroma")` — On by default, `UseForwardChromaEvents` sends the animation name to `SetEventName` automatically when `PlayAnimationName` is called. @param bToggle		If true, PlayAnimation calls will pass the animation note to SetEventName. If false, PlayAnimation will not invoke SetEventName.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RAZERCHROMADEVICES_API`

### `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaSDKIncludes.h` (Public)
_(no declarations extracted)_
