# Runtime / IOSPlatformFeatures

- module root: `Source/Runtime/IOS/IOSPlatformFeatures`
- headers: 2; symbols: 32
- symbol kinds: class=2, delegate=3, function=3, member=7, prototype=16, struct=1
- PrivateDependencyModuleNames: Core, Engine

### `Source/Runtime/IOS/IOSPlatformFeatures/Public/IOSGamepadUtils.h` (Public)


#### class `FIOSGamepadUtils`  
`class FIOSGamepadUtils`  
_L12-29_
- L22 _public prototype_ `FIOSGamepadUtils();`
- L23 _public prototype_ `virtual ~FIOSGamepadUtils();`
- L25 _public prototype_ `UTexture2D* GetGamepadButtonGlyph(const FGamepadKeyNames::Type& ButtonKey, uint32 ControllerIndex);`
- L28 _private member_ `TArray<GamepadGlyph> GlyphsArray;`

#### struct `FIOSGamepadUtils::GamepadGlyph`  
`struct GamepadGlyph`  
_L16-21_
- L18 _public member_ `ControllerType ControllerType;`
- L19 _public member_ `FGamepadKeyNames::Type ButtonName;`
- L20 _public member_ `UTexture2D* ButtonTexture;`

### `Source/Runtime/IOS/IOSPlatformFeatures/Public/IOSSaveGameSystem.h` (Public)


#### class `FIOSSaveGameSystem`  
`class FIOSSaveGameSystem : public ISaveGameSystem`  
_L7-69_
- inherits: `ISaveGameSystem`
- L10 _public prototype_ `FIOSSaveGameSystem();`
- L11 _public prototype_ `virtual ~FIOSSaveGameSystem();`
- L14 _public function_ `virtual bool PlatformHasNativeUI() override` — ISaveGameSystem interface
- L19 _public function_ `virtual bool DoesSaveSystemSupportMultipleUsers() override`
- L24 _public prototype_ `virtual bool GetSaveGameNames(TArray<FString>& FoundSaves, const int32 UserIndex) override;`
- L26 _public function_ `virtual bool DoesSaveGameExist(const TCHAR* Name, const int32 UserIndex) override`
- L31 _public prototype_ `virtual ESaveExistsResult DoesSaveGameExistWithResult(const TCHAR* Name, const int32 UserIndex) override;`
- L33 _public prototype_ `virtual bool SaveGame(bool bAttemptToUseUI, const TCHAR* Name, const int32 UserIndex, const TArray<uint8>& Data) override;`
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpdateCloudDataFromLocalSave, const FString&);` — We call this to notify any listening Cloud subsystem that we have updated a save file.
- L38 _public member_ `FUpdateCloudDataFromLocalSave OnUpdateCloudDataFromLocalSave;`
- L40 _public prototype_ `virtual bool LoadGame(bool bAttemptToUseUI, const TCHAR* Name, const int32 UserIndex, TArray<uint8>& Data) override;`
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpdateLocalSaveFileFromCloud, const FString&);` — We call this to refresh a save file from a listening Cloud subsystem, before we open it.
- L45 _public member_ `FUpdateLocalSaveFileFromCloud OnUpdateLocalSaveFileFromCloud;`
- L47 _public prototype_ `virtual bool DeleteGame(bool bAttemptToUseUI, const TCHAR* Name, const int32 UserIndex) override;`
- L51 _public prototype_ `DECLARE_DELEGATE_OneParam(FDeleteCloudData, const FString&);` — We call this to delete a save file from a listening Cloud subsystem.
- L52 _public member_ `FDeleteCloudData OnDeleteCloudData;`
- L58 _private prototype_ `void Initialize();` — Initializes the SaveData library then loads and initializes the SaveDialog library
- L63 _private prototype_ `void Shutdown();` — Terminates and unloads the SaveDialog library then terminates the SaveData library
- L68 _private prototype_ `virtual FString GetSaveGamePath(const TCHAR* Name);` — Get the path to save game file for the given name

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpdateCloudDataFromLocalSave, const FString&);` — We call this to notify any listening Cloud subsystem that we have updated a save file.
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpdateLocalSaveFileFromCloud, const FString&);` — We call this to refresh a save file from a listening Cloud subsystem, before we open it.
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FDeleteCloudData, const FString&);` — We call this to delete a save file from a listening Cloud subsystem.
