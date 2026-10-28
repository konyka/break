# Editor / DerivedDataWidgets

- module root: `Source/Editor/DerivedDataWidgets`
- headers: 2; symbols: 43
- symbol kinds: class=4, enum=1, enumerator=4, function=7, macro=2, member=9, prototype=16
- DynamicallyLoadedModuleNames: MainFrame
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, EditorFramework, EditorSubsystem, Engine, InputCore, MessageLog, OutputLog, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: 

### `Source/Editor/DerivedDataWidgets/Public/DerivedDataInformation.h` (Public)


#### enum `ERemoteCacheState`  
`enum class ERemoteCacheState : uint8`  
_L10-16_
- L12 _public enumerator_ `Idle`
- L13 _public enumerator_ `Busy`
- L14 _public enumerator_ `Unavailable`
- L15 _public enumerator_ `Warning`

#### class `FDerivedDataInformation`  
`class FDerivedDataInformation`  
_L18-43_
- L22 _public prototype_ `static double GetCacheActivityTimeSeconds(bool bGet, bool bLocal);`
- L23 _public prototype_ `static double GetCacheActivitySizeBytes(bool bGet, bool bLocal);`
- L24 _public prototype_ `static bool GetHasRemoteCache();`
- L25 _public prototype_ `static bool GetHasZenCache();`
- L26 _public prototype_ `static bool GetHasUnrealCloudCache();`
- L27 _public function_ `static ERemoteCacheState GetRemoteCacheState()`
- L28 _public prototype_ `static FText GetRemoteCacheStateAsText();`
- L29 _public function_ `static FText GetRemoteCacheWarningMessage()`
- L30 _public prototype_ `static void UpdateRemoteCacheState();`
- L31 _public function_ `static bool IsUploading()`
- L32 _public function_ `static bool IsDownloading()`
- L36 _private member_ `static ERemoteCacheState RemoteCacheState;`
- L37 _private member_ `static FText RemoteCacheWarningMessage;`
- L38 _private member_ `static double LastGetTime;`
- L39 _private member_ `static double LastPutTime;`
- L40 _private member_ `static bool bIsUploading;`
- L41 _private member_ `static bool bIsDownloading;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DERIVEDDATAWIDGETS_API`

### `Source/Editor/DerivedDataWidgets/Public/SDerivedDataDialogs.h` (Public)


#### class `SDerivedDataRemoteStoreDialog`  
`class SDerivedDataRemoteStoreDialog : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SDerivedDataRemoteStoreDialog)`
- L18 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L26 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L28 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`

#### class `SDerivedDataCacheStatisticsDialog`  
`class SDerivedDataCacheStatisticsDialog : public SCompoundWidget`  
_L31-45_
- inherits: `SCompoundWidget`
- L33 _private function_ `SLATE_BEGIN_ARGS(SDerivedDataCacheStatisticsDialog)`
- L34 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L42 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L44 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`

#### class `SDerivedDataResourceUsageDialog`  
`class SDerivedDataResourceUsageDialog : public SCompoundWidget`  
_L47-61_
- inherits: `SCompoundWidget`
- L49 _private function_ `SLATE_BEGIN_ARGS(SDerivedDataResourceUsageDialog)`
- L50 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L56 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L58 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L60 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DERIVEDDATAWIDGETS_API`
