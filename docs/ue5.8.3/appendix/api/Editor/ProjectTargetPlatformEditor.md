# Editor / ProjectTargetPlatformEditor

- module root: `Source/Editor/ProjectTargetPlatformEditor`
- headers: 3; symbols: 17
- symbol kinds: class=2, function=1, member=1, namespace=2, prototype=11
- DynamicallyLoadedModuleNames: GameProjectGeneration
- PrivateDependencyModuleNames: DesktopPlatform, Projects, Settings, UnrealEd
- PrivateIncludePathModuleNames: GameProjectGeneration
- PublicDependencyModuleNames: Core, Slate, SlateCore

### `Source/Editor/ProjectTargetPlatformEditor/Private/Widgets/SProjectTargetPlatformSettings.h` (Private)


#### class `SProjectTargetPlatformSettings`  
`class SProjectTargetPlatformSettings : public SCompoundWidget`  
_L19-43_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SProjectTargetPlatformSettings)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `TSharedRef<SWidget> MakePlatformRow(const FText& DisplayName, const FName PlatformName, const FSlateBrush* Icon) const;` — Generate an entry for the given platform information
- L34 _private prototype_ `ECheckBoxState HandlePlatformCheckBoxIsChecked(const FName PlatformName) const;` — Check to see if the "enabled" checkbox should be checked for this platform
- L37 _private prototype_ `bool HandlePlatformCheckBoxIsEnabled(const FName PlatformName) const;` — Check to see if the "enabled" checkbox should be enabled for this platform
- L40 _private prototype_ `void HandlePlatformCheckBoxStateChanged(ECheckBoxState InState, const FName PlatformName) const;` — Handle the "enabled" checkbox state being changed for this platform
- L42 _private member_ `TArray<const PlatformInfo::FTargetPlatformInfo*> AvailablePlatforms;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace PlatformInfo`

### `Source/Editor/ProjectTargetPlatformEditor/Public/Interfaces/IProjectTargetPlatformEditorModule.h` (Public)


#### class `IProjectTargetPlatformEditorModule`  
`class IProjectTargetPlatformEditorModule : public IModuleInterface`  
_L20-69_
- inherits: `IModuleInterface`
- desc: Interface for the platform target platform editor module
- L29 _public prototype_ `virtual TWeakPtr<SWidget> CreateProjectTargetPlatformEditorPanel() = 0;` — Creates an project target platform editor panel widget. @return The created widget.
- L36 _public prototype_ `virtual void DestroyProjectTargetPlatformEditorPanel(const TWeakPtr<SWidget>& Panel) = 0;` — Destroys a previously created editor panel widget. @param Panel - The panel to destroy.
- L43 _public prototype_ `virtual void AddOpenProjectTargetPlatformEditorMenuItem(FMenuBuilder& MenuBuilder) const = 0;` — Adds a menu item to open the target platform editor panel in the project settings. @param MenuBuilder - The menu builder to add the item to.
- L52 _public prototype_ `virtual TSharedRef<SWidget> MakePlatformMenuItemWidget(const PlatformInfo::FTargetPlatformInfo& PlatformInfo, const bool bForCheckBox = false, const FText& DisplayNameOverride = FText()) const = 0;` — Creates the widget to use for a platform entry within a FMenuBuilder. @param PlatformInfo - The target platform info to build the widget for @param bForCheckBox - true if the widget is for a checkbox menu item, false if it's for any other menu item (this affects the padding) @param DisplayNameOverride - An alternate name to use for the platform, otherwise Platform->DisplayName() will be used
- L61 _public prototype_ `virtual bool ShowUnsupportedTargetWarning(const FName PlatformName) const = 0;` — Check to see if the given platform is on the list of supported targets, and show a warning message if it's not, allowing the user to continue or cancel @param PlatformName - The name of the platform to test. @return true if the platform is supported, or the warning was accepted with "continue".
- L68 _public prototype_ `virtual ~IProjectTargetPlatformEditorModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PlatformInfo`

### `Source/Editor/ProjectTargetPlatformEditor/Public/ProjectTargetPlatformEditor.h` (Public)
_(no declarations extracted)_
