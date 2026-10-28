# Developer / SlateFontDialog

- module root: `Source/Developer/SlateFontDialog`
- headers: 3; symbols: 26
- symbol kinds: class=3, function=1, macro=1, member=14, prototype=7
- PrivateDependencyModuleNames: AppFramework, Core, CoreUObject, InputCore, Slate, SlateCore
- PrivateIncludePathModuleNames: TargetPlatform
- PublicIncludePathModuleNames: DesktopPlatform

### `Source/Developer/SlateFontDialog/Private/SlateFontDlgWindow.h` (Private)


#### class `FSlateFontDlgWindow`  
`class FSlateFontDlgWindow`  
_L15-49_
- L18 _private member_ `TSharedPtr<SWindow> Window;`
- L20 _private member_ `TSharedPtr<FString> SelectedFont;`
- L21 _private member_ `TArray<TSharedPtr<FString>> FontList;`
- L23 _private member_ `TSharedPtr<FString> SelectedTypeface;`
- L24 _private member_ `TArray<TSharedPtr<FString>> SelectedTypefaceList;`
- L25 _private member_ `TMap<FString, TArray<TSharedPtr<FString>>> TypefaceList;`
- L27 _private member_ `TSharedPtr<STextComboBox> TypefaceDropdown;`
- L28 _private member_ `TSharedPtr<STextBlock> SampleTextBlock;`
- L29 _private member_ `TSharedPtr<STextBlock> ColorIconText;`
- L31 _private member_ `FTextBlockStyle SampleTextStyle;`
- L32 _private member_ `const uint8 SampleTextSize = 36;`
- L34 _private member_ `uint8 FontSize = SampleTextSize;`
- L35 _private member_ `FLinearColor FontColor = FLinearColor::White;`
- L37 _private member_ `FcFontSet* FontSet;`
- L39 _private prototype_ `FSlateFontInfo GetSampleFont() const;`
- L41 _private prototype_ `void LoadFonts();`
- L43 _private prototype_ `FReply OpenColorPicker();`
- L46 _public prototype_ `FSlateFontDlgWindow(bool& OutSuccess);`
- L48 _public prototype_ `void OpenFontWindow(FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags, bool& OutSuccess);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "SlateFontDialogNamespace"`

### `Source/Developer/SlateFontDialog/Public/ISlateFontDialogModule.h` (Public)


#### class `ISlateFontDialogModule`  
`class ISlateFontDialogModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual ~ISlateFontDialogModule() = default;`
- L16 _public function_ `virtual bool OpenFontDialog(FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags)`

### `Source/Developer/SlateFontDialog/Public/SlateFontDialogModule.h` (Public)


#### class `FSlateFontDialogModule`  
`class FSlateFontDialogModule : public ISlateFontDialogModule`  
_L7-11_
- inherits: `ISlateFontDialogModule`
- L10 _public prototype_ `bool OpenFontDialog(FString& OutFontName, float& OutHeight, EFontImportFlags& OutFlags);`
