# Developer / DesktopWidgets

- module root: `Source/Developer/DesktopWidgets`
- headers: 2; symbols: 37
- symbol kinds: class=2, delegate=3, function=3, macro=2, member=12, prototype=15
- PrivateDependencyModuleNames: DesktopPlatform, InputCore
- PublicDependencyModuleNames: Core, CoreUObject, Slate, SlateCore

### `Source/Developer/DesktopWidgets/Public/Widgets/Input/SDirectoryPicker.h` (Public)


#### class `SDirectoryPicker`  
`class SDirectoryPicker : public SCompoundWidget`  
_L18-70_
- inherits: `SCompoundWidget`
- desc: A directory path box, with a button for picking a new path.
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDirectoryChanged, const FString& );`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDirectoryPicker) : _IsEnabled(true)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `FString GetFilePath() const;`
- L42 _public function_ `FString GetDirectory() const`
- L49 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDirectoryPicked, const FString& );` — Declares a delegate that is executed when a file was picked in the SFilePathPicker widget. The first parameter will contain the path to the picked file.
- L52 _private prototype_ `void OnDirectoryTextChanged(const FText& InDirectoryPath);`
- L53 _private prototype_ `void OnDirectoryTextCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L55 _private prototype_ `FText GetFilePathText() const;`
- L57 _private prototype_ `bool OpenPlatformDirectoryPicker(FString& OutDirectory, const FString& DefaultPath);`
- L59 _private prototype_ `FReply BrowseForDirectory();`
- L62 _private member_ `FString File;`
- L63 _private member_ `FString Directory;`
- L64 _private member_ `FText Message;`
- L67 _private member_ `FOnDirectoryChanged OnDirectoryChanged;` — Holds a delegate that is executed when a file was picked.
- L69 _private member_ `TSharedPtr<SEditableTextBox> EditableTextBox;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DESKTOPWIDGETS_API`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDirectoryChanged, const FString& );`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDirectoryPicked, const FString& );` — Declares a delegate that is executed when a file was picked in the SFilePathPicker widget. The first parameter will contain the path to the picked file.

### `Source/Developer/DesktopWidgets/Public/Widgets/Input/SFilePathPicker.h` (Public)


#### class `SFilePathPicker`  
`class SFilePathPicker : public SCompoundWidget`  
_L30-123_
- inherits: `SCompoundWidget`
- desc: Implements an editable text box with a browse button.
- L35 _public function_ `SLATE_BEGIN_ARGS(SFilePathPicker) : _BrowseButtonToolTip(NSLOCTEXT("SFilePathPicker", "BrowseButtonToolTip", "Choose a file from this computer")) , _FileTypeFilter(TEXT("All files (*.*)|*.*")) , _Font() , _IsReadOnly(false) , _DialogReturnsFullPath(false)`
- L44 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, BrowseButtonImage) SLATE_STYLE_ARGUMENT(FButtonStyle, BrowseButtonStyle) SLATE_ATTRIBUTE(FText, BrowseButtonToolTip) SLATE_ATTRIBUTE(FString, BrowseDirectory) SLATE_ATTRIBUTE(FText, BrowseTitle) SLATE_ATTRIBUTE(FString, FilePath) SLATE_ATTRIBUTE(FString, FileTypeFilter) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_ATTRIBUTE(bool, DialogReturnsFullPath) SLATE_EVENT(FOnPathPicked, OnPathPicked) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Browse button image resource.
- L86 _public prototype_ `void SimulateTextInput(const FText& NewText);` — Method which simulates the text input in the path text box.
- L91 _private prototype_ `FReply HandleBrowseButtonClicked( );` — Callback for clicking the browse button.
- L94 _private prototype_ `FText HandleTextBoxText( ) const;` — Callback for getting the text in the path text box.
- L97 _private prototype_ `void HandleTextBoxTextCommitted( const FText& NewText, ETextCommit::Type );` — Callback for committing the text in the path text box.
- L102 _private member_ `TAttribute<FString> BrowseDirectory;` — Holds the directory path to browse by default.
- L105 _private member_ `TAttribute<FText> BrowseTitle;` — Holds the title for the browse dialog window.
- L108 _private member_ `TAttribute<FString> FilePath;` — Holds the currently selected file path.
- L111 _private member_ `TAttribute<FString> FileTypeFilter;` — Holds the file type filter string.
- L114 _private member_ `TSharedPtr<SEditableTextBox> TextBox;` — Holds the editable text box.
- L117 _private member_ `TAttribute<bool> DialogReturnsFullPath;` — Holds the option for the dialog to return full path instead of relative.
- L122 _private member_ `FOnPathPicked OnPathPicked;` — Holds a delegate that is executed when a file was picked.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API DESKTOPWIDGETS_API`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPathPicked, const FString& );` — Declares a delegate that is executed when a file was picked in the SFilePathPicker widget. The first parameter will contain the path to the picked file.
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPathPicked, const FString& );` — Declares a delegate that is executed when a file was picked in the SFilePathPicker widget. The first parameter will contain the path to the picked file.
