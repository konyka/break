# Plugins / GeForceNOWWrapper

- module root: `Plugins/Runtime/Nvidia/GeForceNOWWrapper/Source`
- headers: 4; symbols: 71
- symbol kinds: class=4, delegate=2, function=3, member=10, prototype=52
- PrivateDependencyModuleNames: Core, SlateCore
- PublicDependencyModuleNames: GeForceNOW, Slate

### `Plugins/Runtime/Nvidia/GeForceNOWWrapper/Source/Private/GeForceNOWWrapperPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeForceNow, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeForceNow, Log, All);`

### `Plugins/Runtime/Nvidia/GeForceNOWWrapper/Source/Public/GeForceNOWActionZoneProcessor.h` (Public)


#### class `FWidgetGFNActionZone`  
`class FWidgetGFNActionZone`  
_L20-54_
- desc: Representation of a GeForce NOW action zone.
- L24 _public prototype_ `FWidgetGFNActionZone(const SWidget* InWidget);`
- L27 _public prototype_ `void UpdateActionZone(TArray<TSharedRef<SWindow>>& SlateWindows);` — Updates the action zone's values and notify the GeForce NOW API if the rect of the action zone changed or removes the action zone if it is no longer interactable.
- L29 _public prototype_ `void ClearActionZone();` — Tells the GeForce NOW API to remove this action zone.
- L32 _public prototype_ `unsigned int GetID() const;` — Returns the ID of this action zone.
- L36 _private member_ `const SWidget* Widget;`
- L37 _private member_ `FSlateRect ActionZoneRect;`
- L39 _private member_ `bool bWasInteractable = false;`
- L40 _private member_ `bool bHasActionZone = false;`
- L44 _public function_ `inline bool operator==(const FWidgetGFNActionZone& OtherWidgetGFNActionZone) const`
- L49 _public function_ `inline bool operator==(const SWidget* OtherWidget) const`

#### class `GeForceNOWActionZoneProcessor`  
`class GeForceNOWActionZoneProcessor : public TSharedFromThis<GeForceNOWActionZoneProcessor>`  
_L60-91_
- inherits: `TSharedFromThis<GeForceNOWActionZoneProcessor>`
- desc: Singleton that manages the Action Zones for GeForce NOW. Action Zones are rects that overlay the game stream on the user's end that when pressed can trigger various GeForce NOW features like the Native Virtual Keyboard.
- L67 _public prototype_ `bool Initialize();` — Initializes the Action Zone Processor by hooking onto the Slate Widget Tracker and requesting the tracked widgets we are interested in. Return true if initialization was successful.
- L69 _public prototype_ `void Terminate();` — Terminates the action Zone Processor by unhooking from the Slate Widget Tracker and clearing all action zones.
- L74 _private prototype_ `void HandleTrackedWidgetChanges(const SWidget* Widget, const FName& Tag, ETrackedSlateWidgetOperations Operation);` — Handles what happens when a widget is added or removed.
- L77 _private prototype_ `void HandleEditableTextWidgetRegistered(const SWidget* Widget);` — Creates an action zone when a widget is added.
- L79 _private prototype_ `void HandleEditableTextWidgetUnregistered(const SWidget* Widget);` — Removes the action zone of the removed widget.
- L82 _private prototype_ `bool ProcessGFNWidgetActionZones(float DeltaTime);` — Calls an update on all the action zones the processor has.
- L84 _private prototype_ `void StartProcess();` — Creates a ticker that calls ProcessGFNWidgetActionZones at an interval using GFNWidgetActionZonesProcessDelay.
- L86 _private prototype_ `void StopProcess();` — Removes the ticker that calls ProcessGFNWidgetActionZones.
- L88 _private member_ `TArray<FWidgetGFNActionZone> GFNWidgetActionZones;`
- L90 _private member_ `FTSTicker::FDelegateHandle ProcessDelegateHandle;`

### `Plugins/Runtime/Nvidia/GeForceNOWWrapper/Source/Public/GeForceNOWWrapper.h` (Public)


#### class `GeForceNOWWrapper`  
`class GeForceNOWWrapper`  
_L24-138_
- desc: Singleton wrapper to manage the GeForceNow SDK
- L28 _public prototype_ `static GfnRuntimeError Initialize();` — Load and Initialize the GeforceNOW SDK dll.
- L31 _public prototype_ `static GfnRuntimeError Shutdown();` — Unload the GeforceNOW SDK dlls.
- L38 _public prototype_ `static bool OpenURLOnClient(const TCHAR* URL, int32& OutErrorCode);` — Use to request that the client application open a URL link in their local web browser Returns true if the client successfully opened the URL If the client fails to open the URL an error code is provided
- L40 _public prototype_ `static GeForceNOWWrapper& Get();`
- L42 _public prototype_ `static const FString GetGfnOsTypeString(GfnOsType OsType);`
- L45 _public prototype_ `static bool IsRunningInGFN();` — Returns true if the GeForceNow SDK is initialized and running in cloud.
- L48 _public prototype_ `static bool IsRunningMockGFN();` — Returns true for mock, but this can be used to differentiate between real and mock.
- L51 _public prototype_ `bool InitializeActionZoneProcessor();` — Initializes the Action Zone Processor.Returns true if the initialization was a success.
- L54 _public prototype_ `static bool IsRunningInCloud();` — Determines if application is running in GeforceNOW environment  and without requiring process elevation.
- L57 _public prototype_ `GfnRuntimeError SetupTitle(const FString& InPlatformAppId) const;` — Notify GeforceNOW that an application should be readied for launch.
- L60 _public prototype_ `GfnRuntimeError NotifyAppReady(bool bSuccess, const FString& InStatus) const;` — Notify GeForceNOW that an application is ready to be displayed.
- L62 _public prototype_ `GfnRuntimeError NotifyTitleExited(const FString& InPlatformId, const FString& InPlatformAppId) const;` — Notify GeforceNOW that an application has exited.
- L65 _public prototype_ `GfnRuntimeError StartStream(StartStreamInput& InStartStreamInput, StartStreamResponse& OutResponse) const;` — Request GeforceNOW client to start a streaming session of an application in a synchronous (blocking) fashion.
- L67 _public prototype_ `GfnRuntimeError StartStreamAsync(const StartStreamInput& InStartStreamInput, StartStreamCallbackSig StartStreamCallback, void* Context, uint32 TimeoutMs) const;` — Request GeforceNOW client to start a streaming session of an application in an asynchronous fashion.
- L70 _public prototype_ `GfnRuntimeError StopStream() const;` — Request GeforceNOW client to stop a streaming session of an application in a synchronous (blocking) fashion.
- L72 _public prototype_ `GfnRuntimeError StopStreamAsync(StopStreamCallbackSig StopStreamCallback, void* Context, unsigned int TimeoutMs) const;` — Request GeforceNOW client to stop a streaming session of an application in an asynchronous fashion.
- L75 _public prototype_ `GfnRuntimeError SetActionZone(GfnActionType ActionType, unsigned int Id, GfnRect* Zone);` — Use to invoke special events on the client from the GFN cloud environment
- L78 _public prototype_ `GfnRuntimeError RegisterStreamStatusCallback(StreamStatusCallbackSig StreamStatusCallback, void* Context) const;` — Registers a callback that gets called on the user's PC when the streaming session state changes.
- L80 _public prototype_ `GfnRuntimeError RegisterExitCallback(ExitCallbackSig ExitCallback, void* Context) const;` — Registers an application function to call when GeforceNOW needs to exit the game.
- L82 _public prototype_ `GfnRuntimeError RegisterPauseCallback(PauseCallbackSig PauseCallback, void* Context) const;` — Registers an application callback with GeforceNOW to be called when GeforceNOW needs to pause the game on the user's behalf.
- L84 _public prototype_ `GfnRuntimeError RegisterInstallCallback(InstallCallbackSig InstallCallback, void* Context) const;` — Registers an application callback with GeforceNOW to be called after a successful call to SetupTitle.
- L86 _public prototype_ `GfnRuntimeError RegisterSaveCallback(SaveCallbackSig SaveCallback, void* Context) const;` — Registers an application callback with GeforceNOW to be called when GeforceNOW needs the application to save user progress.
- L88 _public prototype_ `GfnRuntimeError RegisterSessionInitCallback(SessionInitCallbackSig SessionInitCallback, void* Context) const;` — Registers an application callback to be called when a GeforceNOW user has connected to the game seat.
- L90 _public prototype_ `GfnRuntimeError RegisterClientInfoCallback(ClientInfoCallbackSig ClientInfoCallback, void* Context) const;` — Registers an application callback with GFN to be called when client info changes.
- L93 _public prototype_ `GfnRuntimeError GetClientIpV4(FString& OutIpv4) const;` — Gets user client's IP address.
- L95 _public prototype_ `GfnRuntimeError GetClientLanguageCode(FString& OutLanguageCode) const;` — Gets user's client language code in the form "<lang>-<country>" using a standard ISO 639-1 language code and ISO 3166-1 Alpha-2 country code.
- L97 _public prototype_ `GfnRuntimeError GetClientCountryCode(FString& OutCountryCode) const;` — Gets user’s client country code using ISO 3166-1 Alpha-2 country code.
- L99 _public prototype_ `GfnRuntimeError GetClientInfo(GfnClientInfo& OutClientInfo) const;` — Gets user's client data.
- L101 _public prototype_ `GfnRuntimeError GetSessionInfo(GfnSessionInfo& OutSessionInfo) const;` — Gets user's session data.
- L103 _public prototype_ `GfnRuntimeError GetPartnerData(FString& OutPartnerData) const;` — Retrieves secure partner data that is either a) passed by the client in the gfnStartStream call or b) sent in response to Deep Link nonce validation.
- L105 _public prototype_ `GfnRuntimeError GetPartnerSecureData(FString& OutPartnerSecureData) const;` — Use during cloud session to retrieve secure partner data.
- L107 _public prototype_ `GfnRuntimeError GetTitlesAvailable(FString& OutAvailableTitles) const;` — Retrieves all titles that can be launched in the current game streaming session.
- L110 _public prototype_ `GfnRuntimeError IsRunningInCloudSecure(GfnIsRunningInCloudAssurance& OutAssurance) const;` — Determines if calling application is running in GeforceNOW environment, and what level of security assurance that the result is valid.
- L112 _public prototype_ `GfnRuntimeError IsTitleAvailable(const FString& InTitleID, bool& OutbIsAvailable) const;` — Determines if a specific title is available to launch in current streaming session.
- L115 _public function_ `static bool IsSdkInitialized()` — Returns true is the GeforceNOW SDK dll was loaded and initialized.
- L120 _private prototype_ `GeForceNOWWrapper() = default;` — Singleton access only.
- L121 _private prototype_ `~GeForceNOWWrapper() = default;`
- L123 _private prototype_ `void HandleLaunchURL(const TCHAR* URL);`
- L126 _private prototype_ `GfnRuntimeError Free(const char** data) const;` — Free memory allocated by gfnGetTitlesAvailable and the likes.
- L129 _private member_ `static bool bIsSdkInitialized;` — Is the DLL loaded and GfnInitializeSdk was called and succeeded.
- L132 _private member_ `static TOptional<bool> bIsRunningInCloud;` — Is the DLL running in the GeForce Now environment.
- L135 _private member_ `TSharedPtr<GeForceNOWActionZoneProcessor> ActionZoneProcessor;` — Keeps track of actions zones for GeForce NOW. Action Zones are used for things like keyboard invocation within the GeForce NOW app.
- L137 _private member_ `static GeForceNOWWrapper* Singleton;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGFNWrapper, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGFNWrapper, Log, All);`

### `Plugins/Runtime/Nvidia/GeForceNOWWrapper/Source/Public/IGeForceNOWWrapperModule.h` (Public)


#### class `IGeForceNOWWrapperModule`  
`class IGeForceNOWWrapperModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`
- desc: Interface for the GeForceNOW Module.
