# Runtime / EngineSettings

- module root: `Source/Runtime/EngineSettings`
- headers: 8; symbols: 125
- symbol kinds: class=7, enum=5, enumerator=14, function=6, member=76, namespace=2, prototype=12, struct=3
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject

### `Source/Runtime/EngineSettings/Classes/ConsoleSettings.h` (Public)


#### struct `FAutoCompleteCommand`  
`struct FAutoCompleteCommand`  
_L15-53_
- reflection: `USTRUCT()`
- desc: Structure for auto-complete commands and their descriptions.
- L20 _public member_ `FString Command;` — `UPROPERTY(config, EditAnywhere, Category=Command)`
- L23 _public member_ `FString Desc;` — `UPROPERTY(config, EditAnywhere, Category=Command)`
- L25 _public member_ `FColor Color = FColor(180, 180, 180);`
- L27 _public function_ `bool operator<(const FAutoCompleteCommand& rhs) const`
- L33 _public function_ `const FString& GetLeft() const` — for game console
- L39 _public function_ `const FString& GetRight() const` — for game console
- L45 _public function_ `bool IsHistory() const` — @return true:history, false: autocompletion
- L49 _public function_ `void SetHistory()`

#### class `UConsoleSettings`  
`class UConsoleSettings : public UObject`  
_L60-111_
- reflection: `UCLASS(config=Input, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- desc: Implements the settings for the UConsole class.
- L67 _private member_ `int32 MaxScrollbackSize;` — `UPROPERTY(globalconfig, EditAnywhere, Category=General)` — The maximum number of lines the console keeps in its output history.
- L71 _private member_ `TArray<struct FAutoCompleteCommand> ManualAutoCompleteList;` — `UPROPERTY(config, EditAnywhere, Category=AutoComplete)` — Manual list of auto-complete commands and info specified in BaseInput.ini
- L75 _private member_ `TArray<FString> AutoCompleteMapPaths;` — `UPROPERTY(config, EditAnywhere, Category=AutoComplete)` — List of relative paths (e.g. Content/Maps) to search for map names for auto-complete usage. Specified in BaseInput.ini.
- L79 _private member_ `float BackgroundOpacityPercentage;` — `UPROPERTY(config, EditAnywhere, Category=Colors, meta=(UIMin="0", UIMax="100", ClampMin="0", ClampMax="100"))` — Amount of transparency of the console background.
- L83 _private member_ `bool bOrderTopToBottom;` — `UPROPERTY(config, EditAnywhere, Category = AutoComplete)` — Whether we legacy bottom-to-top ordering or regular top-to-bottom ordering
- L87 _private member_ `bool bDisplayHelpInAutoComplete = true;` — `UPROPERTY(config, EditAnywhere, Category = AutoComplete)` — Display the first line of any available help text in the auto-complete window, if a description isn't available
- L91 _private member_ `FColor InputColor;` — `UPROPERTY(config, EditAnywhere, Category=Colors)` — The color used for text input.
- L95 _private member_ `FColor HistoryColor;` — `UPROPERTY(config, EditAnywhere, Category=Colors)` — The color used for the previously typed commands history.
- L99 _private member_ `FColor AutoCompleteCommandColor;` — `UPROPERTY(config, EditAnywhere, Category=Colors)` — The autocomplete color used for executable commands.
- L103 _private member_ `FColor AutoCompleteCVarColor;` — `UPROPERTY(config, EditAnywhere, Category=Colors)` — The autocomplete color used for mutable CVars.
- L107 _private member_ `FColor AutoCompleteFadedColor;` — `UPROPERTY(config, EditAnywhere, Category=Colors)` — The autocomplete color used for command descriptions and read-only CVars.
- L110 _private prototype_ `TArray<FString> GetFilteredManualAutoCompleteCommands(FStringView Substring) const;` — Returns an array with the auto-complete command names that match all the words in the substring.

### `Source/Runtime/EngineSettings/Classes/GameMapsSettings.h` (Public)


#### enum `ETwoPlayerSplitScreenType::Type`  
`enum Type : int`  
_L15-19_
- L17 _public enumerator_ `Horizontal`
- L18 _public enumerator_ `Vertical`

#### enum `EThreePlayerSplitScreenType::Type`  
`enum Type : int`  
_L27-33_
- L29 _public enumerator_ `FavorTop`
- L30 _public enumerator_ `FavorBottom`
- L31 _public enumerator_ `Vertical`
- L32 _public enumerator_ `Horizontal`

#### enum `EFourPlayerSplitScreenType`  
`enum class EFourPlayerSplitScreenType : uint8`  
_L37-42_
- reflection: `UENUM()`
- L39 _public enumerator_ `Grid`
- L40 _public enumerator_ `Vertical`
- L41 _public enumerator_ `Horizontal`

#### struct `FGameModeName`  
`struct FGameModeName`  
_L46-57_
- reflection: `USTRUCT()`
- desc: Helper structure, used to associate GameModes with shortcut names.
- L52 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = DefaultModes, meta = (MetaClass = "/Script/Engine.GameModeBase"))` — Abbreviation/prefix that can be used as an alias for the class name
- L56 _public member_ `FSoftClassPath GameMode;` — `UPROPERTY(EditAnywhere, Category = DefaultModes, meta = (MetaClass = "/Script/Engine.GameModeBase"))` — GameMode class to load

#### enum `ESubLevelStripMode`  
`enum class ESubLevelStripMode : uint8`  
_L60-67_
- reflection: `UENUM()`
- L63 _public enumerator_ `ExactClass` — The class of the sub level actor must be exactly this class
- L66 _public enumerator_ `IsChildOf` — Any child class of this class will be stripped, this is more expensive than ExactClass

#### struct `FTemplateMapInfoOverride`  
`struct FTemplateMapInfoOverride`  
_L72-91_
- reflection: `USTRUCT()`
- desc: Used by new level dialog.
- L78 _public member_ `FSoftObjectPath Thumbnail;` — `UPROPERTY(config, EditAnywhere, Category = DefaultMaps, meta = (AllowedClasses = "/Script/Engine.Texture2D"))` — The thumbnail to display in the new level dialog
- L82 _public member_ `FSoftObjectPath Map;` — `UPROPERTY(config, EditAnywhere, Category = DefaultMaps, meta = (AllowedClasses = "/Script/Engine.World"))` — The path to the template map
- L86 _public member_ `FText DisplayName;` — `UPROPERTY(config, EditAnywhere, Category = DefaultMaps)` — The display name of the map template in the level dialog. If this is empty the thumbnail name will be used
- L88 _public function_ `FTemplateMapInfoOverride()`

#### enum `EDefaultMapRequestType`  
`enum class EDefaultMapRequestType : uint8`  
_L93-98_
- L95 _public enumerator_ `Default`
- L96 _public enumerator_ `Client`
- L97 _public enumerator_ `Server`

#### class `UGameMapsSettings`  
`class UGameMapsSettings : public UObject`  
_L101-251_
- reflection: `UCLASS(config=Engine, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- L113 _private prototype_ `static FString GetGameDefaultMap(EDefaultMapRequestType RequestType = EDefaultMapRequestType::Default);` — Get the default map specified in the settings. Makes a choice based on running as listen server/client vs dedicated server if RequestType is Default @param RequestType If default, it will return the map for your currently running configuration, otherwise you can request the client or server map specifically @return the default map specified in the settings
- L121 _private prototype_ `static FString GetGlobalDefaultGameMode( );` — Get the global default game type specified in the configuration Makes a choice based on running as listen server/client vs dedicated server @return the proper global default game type
- L128 _private prototype_ `static FString GetGameModeForName( const FString& GameModeName );` — Searches the GameModeClassAliases list for a named game mode, if not found will return passed in string @return the proper game type class path to load
- L135 _private prototype_ `static FString GetGameModeForMapName( const FString& MapName );` — Searches the GameModeMapPrefixes list for a named game mode, if not found will return passed in string @return the proper game type class path to load, or empty if not found
- L142 _private prototype_ `static void SetGameDefaultMap( const FString& NewMap );` — Set the default map to use (see GameDefaultMap below) @param NewMap name of valid map to use
- L149 _private prototype_ `static void SetGlobalDefaultGameMode( const FString& NewGameMode );` — Set the default game type (see GlobalDefaultGameMode below) @param NewGameMode name of valid map to use
- L151 _private prototype_ `virtual void PostInitProperties() override;`
- L152 _private prototype_ `virtual void PostReloadConfig( class FProperty* PropertyThatWasLoaded ) override;`
- L159 _public member_ `FSoftObjectPath EditorStartupMap;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, meta=(AllowedClasses="/Script/Engine.World"))` — If set, this map will be loaded when the Editor starts up.
- L163 _public member_ `TArray<FTemplateMapInfoOverride> EditorTemplateMapOverrides;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, meta=(ConfigRestartRequired=true))` — Map templates that should show up in the new level dialog. This will completely override the default maps chosen by the default editor
- L168 _public member_ `FString LocalMapOptions;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, AdvancedDisplay)` — The default options that will be appended to a map being loaded.
- L172 _public member_ `FSoftObjectPath TransitionMap;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, AdvancedDisplay, meta=(AllowedClasses="/Script/Engine.World"))` — The map loaded when transition from one map to another.
- L176 _public member_ `bool bUseSplitscreen;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer)` — Whether the screen should be split or not when multiple local players are present
- L180 _public member_ `TEnumAsByte<ETwoPlayerSplitScreenType::Type> TwoPlayerSplitscreenLayout;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer, meta=(editcondition="bUseSplitScreen"))` — The viewport layout to use if the screen should be split and there are two local players
- L184 _public member_ `TEnumAsByte<EThreePlayerSplitScreenType::Type> ThreePlayerSplitscreenLayout;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer, meta=(editcondition="bUseSplitScreen"))` — The viewport layout to use if the screen should be split and there are three local players
- L188 _public member_ `EFourPlayerSplitScreenType FourPlayerSplitscreenLayout;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer, meta=(editcondition="bUseSplitScreen"))` — The viewport layout to use if the screen should be split and there are three local players
- L192 _public member_ `bool bShowAllPlayerWidgetsWhenSplitscreenDisabled;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer)` — Determines whether all player widget layers should be displayed in the main viewport when splitscreen is disabled. If unchecked, only Player 1 widget will be visible
- L199 _public member_ `bool bOffsetPlayerGamepadIds;` — `UPROPERTY(config, EditAnywhere, Category=LocalMultiplayer, meta=(DisplayName="Skip Assigning Gamepad to Player 1"))` — If enabled, this will make so that gamepads start being assigned to the second controller ID in local multiplayer games. In PIE sessions with multiple windows, this has the same effect as enabling "Route 1st Gamepad to 2nd Client"
- L203 _public member_ `FSoftClassPath GameInstanceClass;` — `UPROPERTY(config, noclear, EditAnywhere, Category=GameInstance, meta=(MetaClass="/Script/Engine.GameInstance"))` — The class to use when instantiating the transient GameInstance class
- L209 _private member_ `FSoftObjectPath GameDefaultMap;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, meta=(AllowedClasses="/Script/Engine.World"))` — The map that will be loaded by default when no other map is loaded.
- L213 _private member_ `FSoftObjectPath ServerDefaultMap;` — `UPROPERTY(config, EditAnywhere, Category=DefaultMaps, AdvancedDisplay, meta=(AllowedClasses="/Script/Engine.World"))` — The map that will be loaded by default when no other map is loaded (DEDICATED SERVER).
- L217 _private member_ `FSoftClassPath GlobalDefaultGameMode;` — `UPROPERTY(config, noclear, EditAnywhere, Category=DefaultModes, meta=(MetaClass="/Script/Engine.GameModeBase", DisplayName="Default GameMode"))` — GameMode to use if not specified in any other way. (e.g. per-map DefaultGameMode or on the URL).
- L224 _private member_ `FSoftClassPath GlobalDefaultServerGameMode;` — `UPROPERTY(config, EditAnywhere, Category=DefaultModes, meta=(MetaClass="/Script/Engine.GameModeBase"), AdvancedDisplay)` — GameMode to use if not specified in any other way. (e.g. per-map DefaultGameMode or on the URL) (DEDICATED SERVERS) If not set, the GlobalDefaultGameMode value will be used.
- L228 _private member_ `TArray<FGameModeName> GameModeMapPrefixes;` — `UPROPERTY(config, EditAnywhere, Category = DefaultModes, AdvancedDisplay)` — Overrides the GameMode to use when loading a map that starts with a specific prefix
- L232 _private member_ `TArray<FGameModeName> GameModeClassAliases;` — `UPROPERTY(config, EditAnywhere, Category = DefaultModes, AdvancedDisplay)` — List of GameModes to load when game= is specified in the URL (e.g. "DM" could be an alias for "MyProject.MyGameModeMP_DM")
- L238 _public prototype_ `static UGameMapsSettings* GetGameMapsSettings();` — `UFUNCTION(BlueprintPure, Category = Settings, meta=(DisplayName="Get Game Maps and Modes Settings"))` — Returns the game local maps settings
- L246 _public prototype_ `void SetSkipAssigningGamepadToPlayer1(bool bSkipFirstPlayer = true);` — `UFUNCTION(BlueprintCallable, Category = "Utilities")` — Modify "Skip Assigning Gamepad to Player 1" GameMapsSettings option @param bSkipFirstPlayer		If set connected game pads will only be assigned to the second and subsequent players @note This value is saved to local config when changed.
- L249 _public prototype_ `bool GetSkipAssigningGamepadToPlayer1() const;` — `UFUNCTION(BlueprintPure, Category = "Utilities")`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ETwoPlayerSplitScreenType`
- L25 _namespace_ `namespace EThreePlayerSplitScreenType`

### `Source/Runtime/EngineSettings/Classes/GameNetworkManagerSettings.h` (Public)


#### class `UGameNetworkManagerSettings`  
`class UGameNetworkManagerSettings : public UObject`  
_L15-63_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `UObject`
- desc: Holds the settings for the AGameNetworkManager class.
- L22 _private member_ `int32 MinDynamicBandwidth;` — `UPROPERTY(globalconfig, EditAnywhere, Category=Bandwidth)` — Minimum bandwidth dynamically set per connection.
- L26 _private member_ `int32 MaxDynamicBandwidth;` — `UPROPERTY(globalconfig, EditAnywhere, Category=Bandwidth)` — Maximum bandwidth dynamically set per connection.
- L30 _private member_ `int32 TotalNetBandwidth;` — `UPROPERTY(globalconfig, EditAnywhere, Category=Bandwidth)` — Total available bandwidth for listen server, split dynamically across net connections.
- L34 _private member_ `int32 BadPingThreshold;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The point we determine the server is either delaying packets or has bad upstream.
- L38 _private member_ `uint32 bIsStandbyCheckingEnabled:1;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — Used to determine if checking for standby cheats should occur.
- L42 _private member_ `float StandbyRxCheatTime;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The amount of time without packets before triggering the cheat code.
- L46 _private member_ `float StandbyTxCheatTime;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The amount of time without packets before triggering the cheat code.
- L50 _private member_ `float PercentMissingForRxStandby;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The percentage of clients missing RX data before triggering the standby code.
- L54 _private member_ `float PercentMissingForTxStandby;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The percentage of clients missing TX data before triggering the standby code.
- L58 _private member_ `float PercentForBadPing;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The percentage of clients with bad ping before triggering the standby code.
- L62 _private member_ `float JoinInProgressStandbyWaitTime;` — `UPROPERTY(config, EditAnywhere, Category=StandbyCheats)` — The amount of time to wait before checking a connection for standby issues.

### `Source/Runtime/EngineSettings/Classes/GameSessionSettings.h` (Public)


#### class `UGameSessionSettings`  
`class UGameSessionSettings : public UObject`  
_L12-28_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `UObject`
- L19 _private member_ `int32 MaxSpectators;` — `UPROPERTY(globalconfig, EditAnywhere, Category=GameSessionSettings)` — Maximum number of spectators allowed by this server.
- L23 _private member_ `int32 MaxPlayers;` — `UPROPERTY(globalconfig, EditAnywhere, Category=GameSessionSettings)` — Maximum number of players allowed by this server.
- L27 _private member_ `uint32 bRequiresPushToTalk:1;` — `UPROPERTY(globalconfig, EditAnywhere, Category=GameSessionSettings)` — Is voice enabled always or via a push to talk key binding.

### `Source/Runtime/EngineSettings/Classes/GeneralEngineSettings.h` (Public)


#### class `UGeneralEngineSettings`  
`class UGeneralEngineSettings : public UObject`  
_L12-17_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UObject`

### `Source/Runtime/EngineSettings/Classes/GeneralProjectSettings.h` (Public)


#### class `UGeneralProjectSettings`  
`class UGeneralProjectSettings : public UObject`  
_L13-117_
- reflection: `UCLASS(config=Game, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- L20 _private member_ `FString CompanyName;` — `UPROPERTY(config, EditAnywhere, Category=Publisher)` — The name of the company (author, provider) that created the project.
- L24 _private member_ `FString CompanyDistinguishedName;` — `UPROPERTY(config, EditAnywhere, Category=Publisher)` — The Distinguished Name of the company (author, provider) that created the project, which is used by publishing tools on some platforms.
- L28 _private member_ `FString CopyrightNotice;` — `UPROPERTY(config, EditAnywhere, Category=Legal)` — The project's copyright and/or trademark notices.
- L32 _private member_ `FString Description;` — `UPROPERTY(config, EditAnywhere, Category=About)` — The project's description text.
- L36 _private member_ `FString Homepage;` — `UPROPERTY(config, EditAnywhere, Category=Publisher)` — The project's homepage URL.
- L40 _private member_ `FString LicensingTerms;` — `UPROPERTY(config, EditAnywhere, Category=Legal)` — The project's licensing terms.
- L44 _private member_ `FString PrivacyPolicy;` — `UPROPERTY(config, EditAnywhere, Category=Legal)` — The project's privacy policy.
- L48 _private member_ `FGuid ProjectID;` — `UPROPERTY(config, EditAnywhere, Category=About)` — The project's unique identifier.
- L52 _private member_ `FString ProjectName;` — `UPROPERTY(config, EditAnywhere, Category=About)` — The project's non-localized name.
- L56 _private member_ `FString ProjectVersion;` — `UPROPERTY(config, EditAnywhere, Category=About)` — The project's version number.
- L60 _private member_ `FString SupportContact;` — `UPROPERTY(config, EditAnywhere, Category=Publisher)` — The project's support contact information.
- L64 _private member_ `FText ProjectDisplayedTitle;` — `UPROPERTY(config, EditAnywhere, Category=Displayed)` — The project's title as displayed on the window title bar (can include the tokens {GameName}, {PlatformArchitecture}, {BuildConfiguration} or {RHIName}, which will be replaced with the specified text)
- L68 _private member_ `FText ProjectDebugTitleInfo;` — `UPROPERTY(config, EditAnywhere, Category=Displayed)` — Additional data to be displayed on the window title bar in non-shipping configurations (can include the tokens {GameName}, {PlatformArchitecture}, {BuildConfiguration} or {RHIName}, which will be replaced with the specified text)
- L72 _private member_ `bool bShouldWindowPreserveAspectRatio;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should the game's window preserve its aspect ratio when resized by user.
- L76 _private member_ `bool bUseBorderlessWindow;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should the game use a borderless Slate window instead of a window with system title bar and border
- L80 _private member_ `bool bStartInVR;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should the game attempt to start in VR, regardless of whether -vr was set on the commandline
- L84 _private member_ `bool bAllowWindowResize;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should the user be allowed to resize the window used by the game, when not using full screen
- L88 _private member_ `bool bAllowClose;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should a close button be shown for the game's window, when not using full screen
- L92 _private member_ `bool bAllowMaximize;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should a maximize button be shown for the game's window, when not using full screen
- L96 _private member_ `bool bAllowMinimize;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Should a minimize button be shown for the game's window, when not using full screen
- L100 _private member_ `float EyeOffsetForFakeStereoRenderingDevice;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Determines the Eye offset of the virtual stereo device created when " -emulatestereo" command line arg is detected
- L104 _private member_ `float FOVForFakeStereoRenderingDevice;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Determines the Field Of View of the virtual stereo device created when " -emulatestereo" command line arg is detected
- L110 _private member_ `float TopFOVRatioForFakeStereoRenderingDevice;` — `UPROPERTY(config, EditAnywhere, Category = Settings, meta = ( ClampMin = "0.01", ClampMax = "0.99"))` — Determines how much of -emulatestereo FOV is above the horizontal plane (0-1) - usually helmets have a larger FOV down than up, so this value is less than 0.5.
- L116 _private member_ `float DifferenceBetweenEyesForFakeStereoRenderingDevice;` — `UPROPERTY(config, EditAnywhere, Category = Settings, meta=( ClampMin="-0.99", ClampMax="0.99"))` — Determines difference between left and eyes horizontal -emulatestereo FOVs. If 0, they are the same (their FOVs are symmetric), the closer to 1, the more each eye is looking towards its side. Reasonable values are in 0 - 0.4 range.

### `Source/Runtime/EngineSettings/Classes/HudSettings.h` (Public)


#### class `UHudSettings`  
`class UHudSettings : public UObject`  
_L12-24_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `UObject`
- L19 _private member_ `uint32 bShowHUD:1;` — `UPROPERTY(config, EditAnywhere, Category=HudSettings)` — Whether the HUD is visible at all.
- L23 _private member_ `TArray<FName> DebugDisplay;` — `UPROPERTY(globalconfig, EditAnywhere, Category=HudSettings)` — Collection of names specifying what debug info to display for ViewTarget actor.

### `Source/Runtime/EngineSettings/Public/EngineSettings.h` (Public)
_(no declarations extracted)_
