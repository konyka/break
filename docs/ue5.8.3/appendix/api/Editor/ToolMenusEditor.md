# Editor / ToolMenusEditor

- module root: `Source/Editor/ToolMenusEditor`
- headers: 3; symbols: 61
- symbol kinds: class=7, enum=1, enumerator=4, function=4, member=16, prototype=29
- DynamicallyLoadedModuleNames: AssetRegistry
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, InputCore, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry
- PublicDependencyModuleNames: ToolMenus

### `Source/Editor/ToolMenusEditor/Private/SEditToolMenuDialog.h` (Private)


#### class `SEditToolMenuDialog`  
`class SEditToolMenuDialog : public SCompoundWidget`  
_L26-84_
- inherits: `SCompoundWidget`
- desc: A dialog to customize a menu
- L29 _public function_ `SLATE_BEGIN_ARGS( SEditToolMenuDialog )`
- L33 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(UToolMenu*, SourceMenu) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — A reference to the parent window
- L42 _public prototype_ `void OnToggleVisibleClicked(TSharedRef<const FMultiBlock> InBlock, TWeakPtr<SMultiBoxWidget> BaseWidget);`
- L45 _public prototype_ `void CloseContainingWindow();` — Closes the window that contains this widget
- L47 _public prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& Window);`
- L51 _private prototype_ `TSharedRef<SWidget> ModifyBlockWidgetAfterMake(const TSharedRef<SMultiBoxWidget>& InMultiBoxWidget, const FMultiBlock& InBlock, const TSharedRef<SWidget>& InBlockWidget);`
- L53 _private prototype_ `void BuildWidget();`
- L54 _private prototype_ `void HandleOnLiveCodingPatchComplete();`
- L56 _private prototype_ `void InitMenu(UToolMenu* InMenu);`
- L58 _private prototype_ `FReply Refresh();`
- L59 _private prototype_ `FReply HandleResetClicked();`
- L60 _private prototype_ `FReply HandleResetAllClicked();`
- L61 _private prototype_ `FReply UndoAllChanges();`
- L63 _private prototype_ `void LoadSelectedObjectState();`
- L64 _private prototype_ `void SaveSettingsToDisk();`
- L66 _private prototype_ `TSharedRef<SWidget> BuildMenuPropertiesWidget();`
- L67 _private prototype_ `TSharedRef<SWidget> MakeMenuNameComboEntryWidget(TSharedPtr<FName> InEntry);`
- L68 _private prototype_ `void OnMenuNamesSelectionChanged(TSharedPtr<FName> InEntry, ESelectInfo::Type SelectInfo);`
- L70 _private prototype_ `void OnSelectedEntryChanged(TSharedRef<const FMultiBlock> InBlock);`
- L72 _private prototype_ `void SetSelectedItem(const FName InName, ESelectedEditMenuEntryType InType);`
- L74 _private member_ `TWeakObjectPtr<UToolMenu> MenuDialogOpenedWith;`
- L75 _private member_ `TWeakObjectPtr<UToolMenu> CurrentGeneratedMenu;`
- L77 _private member_ `TArray<FName> MenuNames;`
- L78 _private member_ `TArray<TSharedPtr<FName>> MenuNameComboData;`
- L80 _private member_ `TSharedPtr<class IDetailsView> PropertiesWidget;`
- L81 _private member_ `TStrongObjectPtr<UToolMenuEditorDialogObject> SelectedObject;`
- L83 _private member_ `TArray<FCustomizedToolMenu> OriginalSettings;`

### `Source/Editor/ToolMenusEditor/Public/IToolMenusEditorModule.h` (Public)


#### class `IToolMenusEditorModule`  
`class IToolMenusEditorModule : public IModuleInterface`  
_L10-43_
- inherits: `IModuleInterface`
- L17 _public function_ `static inline IToolMenusEditorModule& Get()` — Retrieve the module instance.
- L27 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L37 _public prototype_ `virtual void OpenEditToolMenuDialog(class UToolMenu* ToolMenu) const = 0;` — Open editor for the given ToolMenu @param ToolMenu The menu top edit
- L42 _public prototype_ `virtual void RegisterShowEditMenusModeCheckbox() const = 0;` — Adds menu entry to toggle adding an entry to each menu and toolbar to open a menu editor

#### Free symbols / members of external scopes

- L8 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogToolMenusEditor, Log, All);`

### `Source/Editor/ToolMenusEditor/Public/ToolMenusEditor.h` (Public)


#### enum `ESelectedEditMenuEntryType`  
`enum class ESelectedEditMenuEntryType : uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Entry`
- L17 _public enumerator_ `Section`
- L18 _public enumerator_ `Menu`

#### class `UToolMenuEditorDialogObject`  
`class UToolMenuEditorDialogObject : public UObject`  
_L22-29_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L28 _public function_ `virtual void LoadState()`

#### class `UToolMenuEditorDialogMenu`  
`class UToolMenuEditorDialogMenu : public UToolMenuEditorDialogObject`  
_L32-45_
- reflection: `UCLASS()`
- inherits: `UToolMenuEditorDialogObject`
- L38 _public prototype_ `void Init(class UToolMenu* InMenu, const FName InName);`
- L41 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L44 _public member_ `TObjectPtr<UToolMenu> Menu;` — `UPROPERTY()`

#### class `UToolMenuEditorDialogBlock`  
`class UToolMenuEditorDialogBlock : public UToolMenuEditorDialogObject`  
_L48-74_
- reflection: `UCLASS()`
- inherits: `UToolMenuEditorDialogObject`
- L55 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L58 _public member_ `ESelectedEditMenuEntryType Type;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L61 _public member_ `ECustomizedToolMenuVisibility Visibility;` — `UPROPERTY(EditAnywhere, Category = Misc)`
- L64 _public member_ `FString OwnerName;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L67 _public member_ `FString ScriptObject;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L70 _public member_ `FString ScriptObjectClass;` — `UPROPERTY(VisibleAnywhere, Category = Misc)`
- L73 _public member_ `TObjectPtr<UToolMenu> Menu;` — `UPROPERTY()`

#### class `UToolMenuEditorDialogSection`  
`class UToolMenuEditorDialogSection : public UToolMenuEditorDialogBlock`  
_L77-88_
- reflection: `UCLASS()`
- inherits: `UToolMenuEditorDialogBlock`
- L83 _public prototype_ `void Init(class UToolMenu* InMenu, const FName InName);`
- L85 _public prototype_ `virtual void LoadState() override;`
- L87 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UToolMenuEditorDialogEntry`  
`class UToolMenuEditorDialogEntry : public UToolMenuEditorDialogBlock`  
_L91-102_
- reflection: `UCLASS()`
- inherits: `UToolMenuEditorDialogBlock`
- L97 _public prototype_ `void Init(class UToolMenu* InMenu, const FName InName);`
- L99 _public prototype_ `virtual void LoadState() override;`
- L101 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
