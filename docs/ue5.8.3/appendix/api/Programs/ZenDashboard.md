# Programs / ZenDashboard

- module root: `Source/Programs/ZenDashboard`
- headers: 4; symbols: 15
- symbol kinds: class=1, delegate=1, macro=6, member=1, prototype=6
- PrivateDependencyModuleNames: ApplicationCore, Core, HTTP, Json, Projects, SSL, Slate, SlateCore, StandaloneRenderer, StorageServerWidgets, UnixCommonStartup, Zen
- PublicDependencyModuleNames: XCurl
- PublicIncludePathModuleNames: Launch

### `Source/Programs/ZenDashboard/Private/SMessageDialog.h` (Private)


#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMsgDlgResult, const TSharedRef<SWindow>&, EAppReturnType::Type);`
- L14 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMsgDlgResult, const TSharedRef<SWindow>&, EAppReturnType::Type);`
- L16 _prototype_ `EAppReturnType::Type OpenModalMessageDialog_Internal(EAppMsgCategory InMessageCategory, EAppMsgType::Type InMessageType, const FText& InMessage, const FText& InTitle, const TSharedPtr<const SWidget>& ModalParent);`

### `Source/Programs/ZenDashboard/Private/Version.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define ZEN_DASHBOARD_VERSION_MAJOR 1`
- L8 _macro_ `#define ZEN_DASHBOARD_VERSION_MINOR 0`
- L9 _macro_ `#define ZEN_DASHBOARD_VERSION_PATCH 0`
- L11 _macro_ `#define ZEN_DASHBOARD_VERSION_STRING "1.00"`
- L14 _macro_ `#define ZEN_DASHBOARD_VERSION_STRING_EX "v" ZEN_DASHBOARD_VERSION_STRING "-" ZEN_DASHBOARD_VERSION_ID_STRING`
- L16 _macro_ `#define ZEN_DASHBOARD_VERSION_STRING_EX "v" ZEN_DASHBOARD_VERSION_STRING`

### `Source/Programs/ZenDashboard/Private/ZenDashboard.h` (Private)
_(no declarations extracted)_

### `Source/Programs/ZenDashboard/Private/ZenDashboardStyle.h` (Private)


#### class `FZenDashboardStyle`  
`class FZenDashboardStyle`  
_L8-31_
- L14 _public prototype_ `static void Initialize();` — Set up specific styles for the zen dashboard app
- L19 _public prototype_ `static void Shutdown();` — Tidy up on shut-down
- L24 _public prototype_ `static const ISlateStyle& Get();` — Access to singleton style object
- L27 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L30 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Singleton style object
