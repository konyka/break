# Runtime / MacMenu

- module root: `Source/Runtime/Apple/MacMenu`
- headers: 1; symbols: 14
- symbol kinds: class=1, prototype=13
- PrivateDependencyModuleNames: CoreUObject, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: ApplicationCore, Core

### `Source/Runtime/Apple/MacMenu/Private/MacMenu.h` (Private)


#### class `FSlateMacMenu`  
`class FSlateMacMenu`  
_L14-33_
- L17 _public prototype_ `static void PostInitStartup();`
- L18 _public prototype_ `static void CleanupOnShutdown();`
- L19 _public prototype_ `static void UpdateWithMultiBox(const TSharedPtr<FMultiBox> MultiBox);`
- L20 _public prototype_ `static void UpdateMenu(FMacMenu* Menu);`
- L21 _public prototype_ `static void UpdateCachedState();`
- L22 _public prototype_ `static void ExecuteMenuItemAction(const TSharedRef<const FMenuEntryBlock>& Block);`
- L23 _public prototype_ `static void UpdateApplicationMenu(bool bMacApplicationModalMode);`
- L24 _public prototype_ `static void UpdateWindowMenu(bool bMacApplicationModalMode);`
- L25 _public prototype_ `static void LanguageChanged();`
- L29 _private prototype_ `static NSString* GetMenuItemTitle(const TSharedRef< const FMenuEntryBlock >& Block);`
- L30 _private prototype_ `static NSImage* GetMenuItemIcon(const TSharedRef<const FMenuEntryBlock>& Block);`
- L31 _private prototype_ `static bool IsMenuItemEnabled(const TSharedRef<const FMenuEntryBlock>& Block);`
- L32 _private prototype_ `static int32 GetMenuItemState(const TSharedRef<const FMenuEntryBlock>& Block);`
