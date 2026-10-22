# Developer / ToolMenus

- module root: `Source/Developer/ToolMenus`
- headers: 14; symbols: 688
- symbol kinds: class=13, delegate=23, enum=5, enumerator=18, function=73, macro=8, member=198, namespace=8, prototype=311, struct=28, typedef=2, union=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, InputCore, Slate, SlateCore

### `Source/Developer/ToolMenus/Private/ToolMenusBlueprintLibrary.h` (Private)


#### class `UToolMenuContextExtensions`  
`class UToolMenuContextExtensions : public UObject`  
_L18-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- L25 _public prototype_ `static UObject* FindByClass(const FToolMenuContext& Context, TSubclassOf<UObject> InClass);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod, DeterminesOutputType = "InClass"))`
- L28 _public prototype_ `static void DebugLogContextObjectClasses(const FToolMenuContext& Context);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`

#### class `UToolMenuEntryExtensions`  
`class UToolMenuEntryExtensions : public UObject`  
_L32-76_
- reflection: `UCLASS()`
- inherits: `UObject`
- L39 _public prototype_ `static FScriptSlateIcon MakeScriptSlateIcon(const FName StyleSetName, const FName StyleName, const FName SmallStyleName = NAME_None);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (Keywords = "construct build", NativeMakeFunc))`
- L42 _public prototype_ `static void BreakScriptSlateIcon(const FScriptSlateIcon& InValue, FName& StyleSetName, FName& StyleName, FName& SmallStyleName);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (NativeBreakFunc))`
- L45 _public prototype_ `static FToolMenuStringCommand MakeStringCommand(EToolMenuStringCommandType Type, FName CustomType, const FString& String);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (Keywords = "construct build", NativeMakeFunc))`
- L48 _public prototype_ `static void BreakStringCommand(const FToolMenuStringCommand& InValue, EToolMenuStringCommandType& Type, FName& CustomType, FString& String);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (NativeBreakFunc))`
- L51 _public prototype_ `static FToolMenuOwner MakeToolMenuOwner(FName Name);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (Keywords = "construct build", NativeMakeFunc))`
- L54 _public prototype_ `static void BreakToolMenuOwner(const FToolMenuOwner& InValue, FName& Name);` — `UFUNCTION(BlueprintPure, Category = "Tool Menus", meta = (NativeBreakFunc))`
- L57 _public prototype_ `static void SetLabel(UPARAM(ref) FToolMenuEntry& Target, const FText& Label);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L60 _public prototype_ `static FText GetLabel(const FToolMenuEntry& Target);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L63 _public prototype_ `static void SetToolTip(UPARAM(ref) FToolMenuEntry& Target, const FText& ToolTip);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L66 _public prototype_ `static FText GetToolTip(const FToolMenuEntry& Target);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L69 _public prototype_ `static void SetIcon(UPARAM(ref) FToolMenuEntry& Target, const FName StyleSetName, const FName StyleName = NAME_None, const FName SmallStyleName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L72 _public prototype_ `static void SetStringCommand(UPARAM(ref) FToolMenuEntry& Target, const EToolMenuStringCommandType Type, const FName CustomType, const FString& String);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L75 _public prototype_ `static FToolMenuEntry InitMenuEntry(const FName InOwner, const FName InName, const FText& InLabel, const FText& InToolTip, const EToolMenuStringCommandType CommandType, const FName CustomCommandType, const FString& CommandString);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`

#### class `UToolMenuSectionExtensions`  
`class UToolMenuSectionExtensions : public UObject`  
_L79-96_
- reflection: `UCLASS()`
- inherits: `UObject`
- L86 _public prototype_ `static void SetLabel(UPARAM(ref) FToolMenuSection& Section, const FText& Label);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L89 _public prototype_ `static FText GetLabel(const FToolMenuSection& Section);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L92 _public prototype_ `static void AddEntry(UPARAM(ref) FToolMenuSection& Section, const FToolMenuEntry& Args);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`
- L95 _public prototype_ `static void AddEntryObject(UPARAM(ref) FToolMenuSection& Section, UToolMenuEntryScript* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = (ScriptMethod))`

### `Source/Developer/ToolMenus/Public/IToolMenusModule.h` (Public)


#### class `IToolMenusModule`  
`class IToolMenusModule : public IModuleInterface`  
_L8-29_
- inherits: `IModuleInterface`
- L15 _public function_ `static inline IToolMenusModule& Get()` — Retrieve the module instance.
- L25 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Developer/ToolMenus/Public/ToolMenu.h` (Public)


#### class `UToolMenu`  
`class UToolMenu : public UToolMenuBase`  
_L24-255_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UToolMenuBase`
- desc: Represents a menu in the ToolMenus system. An instance of this class is returned by basic APIs such as UToolMenus::RegisterMenu and UToolMenus::ExtendMenu.
- L30 _public prototype_ `UToolMenu();`
- L33 _public prototype_ `void InitMenu(const FToolMenuOwner Owner, FName Name, FName Parent = NAME_None, EMultiBoxType Type = EMultiBoxType::Menu);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`
- L36 _public prototype_ `void AddSectionScript( const FName SectionName, const FText& Label = FText(), const FName InsertName = NAME_None, const EToolMenuInsertType InsertType = EToolMenuInsertType::Default, const EToolMenuSectionAlign Alignment = EToolMenuSectionAlign::Default );` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = ( ScriptName = "AddSection", DisplayName = "Add Section", AutoCreateRefTerm = "Label", AdvancedDisplay = "InsertName,InsertType" ))`
- L45 _public prototype_ `void AddDynamicSectionScript(const FName SectionName, UToolMenuSectionDynamic* Object);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = ( ScriptName = "AddDynamicSection", DisplayName = "Add Dynamic Section" ))`
- L48 _public prototype_ `void AddMenuEntry(const FName SectionName, const FToolMenuEntry& Args);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`
- L51 _public prototype_ `void AddMenuEntryObject(UToolMenuEntryScript* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`
- L54 _public prototype_ `void RemoveMenuEntryObject(UToolMenuEntryScript* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`
- L57 _public prototype_ `UToolMenu* AddSubMenuScript(const FName Owner, const FName SectionName, const FName Name, const FText& Label, const FText& ToolTip = FText());` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus", meta = ( ScriptName = "AddSubMenu", AutoCreateRefTerm = "Label,ToolTip" ))`
- L59 _public prototype_ `UToolMenu* AddSubMenu(const FToolMenuOwner Owner, const FName SectionName, const FName Name, const FText& Label, const FText& ToolTip = FText());`
- L61 _public prototype_ `void RemoveSection(const FName SectionName);`
- L73 _public prototype_ `FToolMenuSection& AddSection(const FName SectionName, const TAttribute< FText >& InLabel = TAttribute<FText>(), const FToolMenuInsert InPosition = FToolMenuInsert());` — Add a section to the menu. When adding sections while registering a menu with UToolMenus::Get()->RegisterMenu(), always use this function. This will ensure that sections have the right label and are presented in the intended order regardless of when menu extensions are performed. @param SectionName The name of the section. @param InLabel The label to set on the section. @param InPosition The position of the section within its parent menu. @return A reference to the created section.
- L85 _public prototype_ `FToolMenuSection& AddDynamicSection(const FName SectionName, const FNewSectionConstructChoice& InConstruct, const FToolMenuInsert InPosition = FToolMenuInsert());` — Build a section in a callback. The callback is passed a sandboxed empty menu to add as many sections as desired. Sections are merged into the final menu afterwards. @param SectionName The FName of the section the callback will build. @param InConstruct The callback that will be run to build the menu as the user opens it. @param InPosition The position of the section within its parent menu. @return A reference to the created section.
- L93 _public prototype_ `FToolMenuSection* FindSection(const FName SectionName);` — Finds an existing section using the provided FName. @param SectionName The section name to find. Provide NAME_None to access the unnamed section of this menu. @return A pointer to the found section or nullptr if none was found.
- L101 _public prototype_ `FToolMenuSection& FindOrAddSection(const FName SectionName);` — Finds an existing section using the provided FName or, if not found, creates a new one and assigns it that FName. @param SectionName The section name to find or add. Provide NAME_None to access the unnamed section of this menu. @return A reference to the found or newly created section.
- L114 _public prototype_ `FToolMenuSection& FindOrAddSection(const FName SectionName, const TAttribute< FText >& InLabel, const FToolMenuInsert InPosition = FToolMenuInsert());` — Finds an existing section using the provided FName or, if not found, creates a new one and assigns it that FName. In case the the section did not exist and a new one was created, then the provided label and optional position is also set on the newly created section. @param SectionName The section name to find or add. Provide NAME_None to access the unnamed section of this menu. @param InLabel The label to set on the section if a new one is created. If an existing section is returned this label is ignored. @param InPosition The position to set on the section if a new one is created. If an existing section is returned this position is ignored. @return A reference to the found or newly created section.
- L116 _public function_ `FName GetMenuName() const`
- L118 _public function_ `bool IsRegistered() const`
- L121 _public prototype_ `TArray<const UToolMenu*> GetSubMenuChain() const;` — returns array [Menu, Menu.SubMenuA, Menu.SubMenuB] for Menu.SubMenuB.SubMenuB
- L124 _public prototype_ `FString GetSubMenuNamePath() const;` — returns "SubMenuC.SubMenuD" for menu "ModuleA.MenuB.SubMenuC.SubMenuD"
- L127 _public prototype_ `void SetExtendersEnabled(bool bEnabled);` — Set support for extenders
- L130 _public prototype_ `virtual bool IsEditing() const override;`
- L131 _public prototype_ `virtual FName GetSectionName(const FName InEntryName) const override;`
- L132 _public prototype_ `virtual bool ContainsSection(const FName InName) const override;`
- L133 _public prototype_ `virtual bool ContainsEntry(const FName InName) const override;`
- L134 _public prototype_ `virtual FCustomizedToolMenu* FindMenuCustomization() const override;`
- L135 _public prototype_ `virtual FCustomizedToolMenu* AddMenuCustomization() const override;`
- L136 _public prototype_ `virtual FCustomizedToolMenuHierarchy GetMenuCustomizationHierarchy() const override;`
- L137 _public prototype_ `virtual FToolMenuProfile* FindMenuProfile(const FName& ProfileName) const override;`
- L138 _public prototype_ `virtual FToolMenuProfile* AddMenuProfile(const FName& ProfileName) const override;`
- L139 _public prototype_ `virtual FToolMenuProfileHierarchy GetMenuProfileHierarchy(const FName& ProfileName) const override;`
- L140 _public prototype_ `virtual void UpdateMenuCustomizationFromMultibox(const TSharedRef<const FMultiBox>& InMultiBox) override;`
- L141 _public prototype_ `virtual void OnMenuDestroyed() override;`
- L144 _public prototype_ `TArray<FName> GetMenuHierarchyNames(bool bIncludeSubMenuRoot) const;`
- L145 _public function_ `void SetMaxHeight(uint32 InMaxHeight)`
- L151 _public function_ `template <typename TContextType> TContextType* FindContext() const`
- L157 _public prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L159 _public prototype_ `const ISlateStyle* GetStyleSet() const;`
- L160 _public prototype_ `void SetStyleSet(const ISlateStyle* InStyleSet);`
- L166 _private prototype_ `void InitGeneratedCopy(const UToolMenu* Source, const FName InMenuName, const FToolMenuContext* InContext = nullptr);`
- L168 _private prototype_ `bool FindEntry(const FName EntryName, int32& SectionIndex, int32& EntryIndex) const;`
- L170 _private prototype_ `FToolMenuEntry* FindEntry(const FName EntryName);`
- L172 _private prototype_ `const FToolMenuEntry* FindEntry(const FName EntryName) const;`
- L174 _private prototype_ `int32 IndexOfSection(const FName SectionName) const;`
- L176 _private prototype_ `int32 FindInsertIndex(const FToolMenuSection& InSection) const;`
- L178 _private prototype_ `bool IsRegistering() const;`
- L180 _private prototype_ `void Empty();`
- L185 _public member_ `FName MenuName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L188 _public member_ `FName MenuParent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L191 _public member_ `FName StyleName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L194 _public member_ `FName TutorialHighlightName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L197 _public member_ `EMultiBoxType MenuType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L200 _public member_ `bool bShouldCleanupContextOnDestroy;` — `UPROPERTY(Transient)`
- L203 _public member_ `bool bShouldCloseWindowAfterMenuSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L206 _public member_ `bool bCloseSelfOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L209 _public member_ `bool bSearchable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L212 _public member_ `bool bToolBarIsFocusable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")`
- L216 _public member_ `bool bSeparateSections = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")` — Whether different sections should have separators automatically added between them.
- L220 _public member_ `TOptional<bool> bAllowToolBarWrapButton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")` — Whether to (ever) allow the wrap button/overflow menu. Defauls to the style.
- L223 _public member_ `bool bToolBarForceSmallIcons;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")`
- L227 _public member_ `bool bPreventCustomization;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")` — Prevent menu from being customized
- L230 _public member_ `FToolMenuOwner MenuOwner;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L233 _public member_ `FToolMenuContext Context;` — `UPROPERTY()`
- L236 _public member_ `TArray<FToolMenuSection> Sections;` — `UPROPERTY()`
- L239 _public member_ `TObjectPtr<const UToolMenu> SubMenuParent;` — `UPROPERTY()`
- L242 _public member_ `FName SubMenuSourceEntryName;` — `UPROPERTY()`
- L244 _public member_ `FMultiBox::FOnModifyBlockWidgetAfterMake ModifyBlockWidgetAfterMake;`
- L248 _private member_ `bool bRegistered;`
- L249 _private member_ `bool bIsRegistering;`
- L250 _private member_ `bool bExtendersEnabled;`
- L252 _private member_ `FName StyleSetName;`
- L254 _private member_ `uint32 MaxHeight;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TOOLMENUS_API`

### `Source/Developer/ToolMenus/Public/ToolMenuContext.h` (Public)


#### class `UToolMenuContextBase`  
`class UToolMenuContextBase : public UObject`  
_L19-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UObject`

#### class `USlateTabManagerContext`  
`class USlateTabManagerContext : public UToolMenuContextBase`  
_L25-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolMenuContextBase`
- L30 _public member_ `TWeakPtr<FTabManager> TabManager;`

#### struct `FToolMenuContext`  
`struct FToolMenuContext`  
_L34-106_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public typedef_ `using FContextObjectCleanup = TFunction<void(UObject*)>;`
- L40 _public typedef_ `using FContextCleanup = TFunction<void()>;`
- L42 _public prototype_ `FToolMenuContext() = default;`
- L43 _public prototype_ `FToolMenuContext(UObject* InContext);`
- L44 _public prototype_ `FToolMenuContext(UObject* InContext, FContextObjectCleanup&& InCleanup);`
- L45 _public prototype_ `FToolMenuContext(TSharedPtr<FUICommandList> InCommandList, TSharedPtr<FExtender> InExtender = TSharedPtr<FExtender>(), UObject* InContext = nullptr);`
- L48 _public function_ `template <typename TContextType> TContextType* FindContext() const`
- L61 _public prototype_ `UObject* FindByClass(UClass* InClass) const;`
- L63 _public prototype_ `void AppendCommandList(const TSharedRef<FUICommandList>& InCommandList);`
- L64 _public prototype_ `void AppendCommandList(const TSharedPtr<FUICommandList>& InCommandList);`
- L65 _public prototype_ `const FUIAction* GetActionForCommand(TSharedPtr<const FUICommandInfo> Command, TSharedPtr<const FUICommandList>& OutCommandList) const;`
- L66 _public prototype_ `const FUIAction* GetActionForCommand(TSharedPtr<const FUICommandInfo> Command) const;`
- L68 _public prototype_ `void AddExtender(const TSharedPtr<FExtender>& InExtender);`
- L69 _public prototype_ `TSharedPtr<FExtender> GetAllExtenders() const;`
- L70 _public prototype_ `void ResetExtenders();`
- L72 _public prototype_ `void AppendObjects(const TArray<UObject*>& InObjects);`
- L73 _public prototype_ `void AddObject(UObject* InObject);`
- L74 _public prototype_ `void AddObject(UObject* InObject, FContextObjectCleanup&& InCleanup);`
- L76 _public prototype_ `void AddCleanup(FContextCleanup&& InCleanup);`
- L78 _public prototype_ `void CleanupObjects();`
- L85 _public function_ `bool IsEditing() const`
- L86 _public function_ `void SetIsEditing(bool InIsEditing)`
- L90 _private prototype_ `void Empty();`
- L92 _private member_ `bool bIsEditing = false;`
- L95 _private member_ `TArray<TObjectPtr<UObject>> ContextObjects;` — `UPROPERTY()`
- L97 _private member_ `TSortedMap<TObjectPtr<UObject>, FContextObjectCleanup> ContextObjectCleanupFuncs;`
- L99 _private member_ `TArray<FContextCleanup> ContextCleanupFuncs;`
- L101 _private member_ `TArray<TSharedPtr<FUICommandList>> CommandLists;`
- L103 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L105 _private member_ `TArray<TSharedPtr<FExtender>> Extenders;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLMENUS_API`

### `Source/Developer/ToolMenus/Public/ToolMenuDelegates.h` (Public)


#### struct `FToolUIAction`  
`struct FToolUIAction`  
_L46-65_
- L48 _public function_ `FToolUIAction()`
- L49 _public function_ `FToolUIAction(const FToolMenuExecuteAction& InExecuteAction) : ExecuteAction(InExecuteAction)`
- L50 _public function_ `FToolUIAction(const FToolMenuExecuteAction& InExecuteAction, const FToolMenuCanExecuteAction& InCanExecuteAction, const FToolMenuGetActionCheckState& InGetActionCheckState) : ExecuteAction(InExecuteAction) , CanExecuteAction(InCanExecuteAction) , GetActionCheckState(InGetActionCheckState)`
- L56 _public function_ `FToolUIAction(const FToolMenuExecuteAction& InExecuteAction, const FToolMenuGetActionCheckState& InGetActionCheckState) : ExecuteAction(InExecuteAction) , GetActionCheckState(InGetActionCheckState)`
- L61 _public member_ `FToolMenuExecuteAction ExecuteAction;`
- L62 _public member_ `FToolMenuCanExecuteAction CanExecuteAction;`
- L63 _public member_ `FToolMenuGetActionCheckState GetActionCheckState;`
- L64 _public member_ `FToolMenuIsActionButtonVisible IsActionVisibleDelegate;`

#### struct `FToolDynamicUIAction`  
`struct FToolDynamicUIAction`  
_L68-85_
- reflection: `USTRUCT(BlueprintType)`
- L72 _public function_ `FToolDynamicUIAction()`
- L75 _public member_ `FToolMenuDynamicExecuteAction ExecuteAction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L78 _public member_ `FToolMenuDynamicCanExecuteAction CanExecuteAction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L81 _public member_ `FToolMenuDynamicGetActionCheckState GetActionCheckState;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L84 _public member_ `FToolMenuDynamicIsActionButtonVisible IsActionVisibleDelegate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`

#### struct `FNewToolMenuChoice`  
`struct FNewToolMenuChoice`  
_L87-99_
- L89 _public function_ `FNewToolMenuChoice()`
- L90 _public function_ `FNewToolMenuChoice(const FOnGetContent& InOnGetContent) : OnGetContent(InOnGetContent)`
- L91 _public function_ `FNewToolMenuChoice(const FNewToolMenuWidget& InNewToolMenuWidget) : NewToolMenuWidget(InNewToolMenuWidget)`
- L92 _public function_ `FNewToolMenuChoice(const FNewToolMenuDelegate& InNewToolMenu) : NewToolMenu(InNewToolMenu)`
- L93 _public function_ `FNewToolMenuChoice(const FNewMenuDelegate& InNewMenuLegacy) : NewMenuLegacy(InNewMenuLegacy)`
- L95 _public member_ `FOnGetContent OnGetContent;`
- L96 _public member_ `FNewToolMenuWidget NewToolMenuWidget;`
- L97 _public member_ `FNewToolMenuDelegate NewToolMenu;`
- L98 _public member_ `FNewMenuDelegate NewMenuLegacy;`

#### struct `FToolUIActionChoice`  
`struct FToolUIActionChoice`  
_L101-131_
- L104 _public function_ `FToolUIActionChoice()`
- L105 _public function_ `FToolUIActionChoice(const FUIAction& InAction) : Action(InAction)`
- L106 _public function_ `FToolUIActionChoice(const FExecuteAction& InExecuteAction) : Action(InExecuteAction)`
- L107 _public function_ `FToolUIActionChoice(const FToolUIAction& InAction) : ToolAction(InAction)`
- L108 _public function_ `FToolUIActionChoice(const FToolDynamicUIAction& InAction) : DynamicToolAction(InAction)`
- L109 _public function_ `FToolUIActionChoice(const FToolMenuExecuteAction& InExecuteAction) : ToolAction(InExecuteAction)`
- L110 _public prototype_ `FToolUIActionChoice(const TSharedPtr< const FUICommandInfo >& InCommand, const FUICommandList& InCommandList);`
- L112 _public function_ `const FUIAction* GetUIAction() const`
- L117 _public function_ `const FToolUIAction* GetToolUIAction() const`
- L122 _public function_ `const FToolDynamicUIAction* GetToolDynamicUIAction() const`
- L128 _private member_ `TOptional<FUIAction> Action;`
- L129 _private member_ `TOptional<FToolUIAction> ToolAction;`
- L130 _private member_ `TOptional<FToolDynamicUIAction> DynamicToolAction;`

#### struct `FNewSectionConstructChoice`  
`struct FNewSectionConstructChoice`  
_L133-145_
- L135 _public function_ `FNewSectionConstructChoice()`
- L136 _public function_ `FNewSectionConstructChoice(const FNewToolMenuDelegate& InNewToolMenuDelegate) : NewToolMenuDelegate(InNewToolMenuDelegate)`
- L137 _public function_ `FNewSectionConstructChoice(const FNewToolMenuDelegateLegacy& InNewToolMenuDelegateLegacy) : NewToolMenuDelegateLegacy(InNewToolMenuDelegateLegacy)`
- L138 _public function_ `FNewSectionConstructChoice(const FNewToolBarDelegateLegacy& InNewToolBarDelegateLegacy) : NewToolBarDelegateLegacy(InNewToolBarDelegateLegacy)`
- L140 _public member_ `FNewToolMenuDelegate NewToolMenuDelegate;`
- L141 _public member_ `FNewToolMenuDelegateLegacy NewToolMenuDelegateLegacy;`
- L142 _public member_ `FNewToolBarDelegateLegacy NewToolBarDelegateLegacy;`
- L144 _public function_ `bool IsBound() const`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TOOLMENUS_API`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FNewToolMenuSectionDelegate, FToolMenuSection&);`
- L23 _prototype_ `DECLARE_DELEGATE_OneParam(FNewToolMenuSectionDelegate, FToolMenuSection&);`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FNewToolMenuDelegate, UToolMenu*);`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FNewToolMenuDelegate, UToolMenu*);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FNewToolMenuDelegateLegacy, class FMenuBuilder&, UToolMenu*);`
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FNewToolMenuDelegateLegacy, class FMenuBuilder&, UToolMenu*);`
- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FNewToolBarDelegateLegacy, class FToolBarBuilder&, UToolMenu*);`
- L26 _prototype_ `DECLARE_DELEGATE_TwoParams(FNewToolBarDelegateLegacy, class FToolBarBuilder&, UToolMenu*);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FNewToolMenuWidget, const FToolMenuContext&);`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FNewToolMenuWidget, const FToolMenuContext&);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FNewToolMenuCustomWidget, const FToolMenuContext&, const FToolMenuCustomWidgetContext&);`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FNewToolMenuCustomWidget, const FToolMenuContext&, const FToolMenuCustomWidgetContext&);`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FToolMenuExecuteAction, const FToolMenuContext&);`
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FToolMenuExecuteAction, const FToolMenuContext&);`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuCanExecuteAction, const FToolMenuContext&);`
- L31 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuCanExecuteAction, const FToolMenuContext&);`
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuIsActionChecked, const FToolMenuContext&);`
- L32 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuIsActionChecked, const FToolMenuContext&);`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FToolMenuGetActionCheckState, const FToolMenuContext&);`
- L33 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FToolMenuGetActionCheckState, const FToolMenuContext&);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuIsActionButtonVisible, const FToolMenuContext&);`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuIsActionButtonVisible, const FToolMenuContext&);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FToolMenuSectionSorter, const FToolMenuEntry&, const FToolMenuEntry&, const FToolMenuContext&);`
- L36 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FToolMenuSectionSorter, const FToolMenuEntry&, const FToolMenuEntry&, const FToolMenuContext&);`
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams(FToolMenuExecuteString, const FString&, const FToolMenuContext&);`
- L38 _prototype_ `DECLARE_DELEGATE_TwoParams(FToolMenuExecuteString, const FString&, const FToolMenuContext&);`
- L40 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FToolMenuDynamicExecuteAction, const FToolMenuContext&, Context);`
- L40 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FToolMenuDynamicExecuteAction, const FToolMenuContext&, Context);`
- L41 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicCanExecuteAction, const FToolMenuContext&, Context);`
- L41 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicCanExecuteAction, const FToolMenuContext&, Context);`
- L42 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicIsActionChecked, const FToolMenuContext&, Context);`
- L42 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicIsActionChecked, const FToolMenuContext&, Context);`
- L43 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(ECheckBoxState, FToolMenuDynamicGetActionCheckState, const FToolMenuContext&, Context);`
- L43 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(ECheckBoxState, FToolMenuDynamicGetActionCheckState, const FToolMenuContext&, Context);`
- L44 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicIsActionButtonVisible, const FToolMenuContext&, Context);`
- L44 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FToolMenuDynamicIsActionButtonVisible, const FToolMenuContext&, Context);`

### `Source/Developer/ToolMenus/Public/ToolMenuEntry.h` (Public)


#### struct `FToolMenuEntryStyle`  
`struct FToolMenuEntryStyle`  
_L23-30_
- desc: A StyleSet, StyleName pair
- L29 _public member_ `TOptional<FName> StyleName;` — The name of the style (within the StyleSet) to use to create the calling widget. Default is auto-calculated or derived from elsewhere

#### struct `FToolMenuEntrySubMenuData`  
`struct FToolMenuEntrySubMenuData`  
_L32-50_
- L35 _public function_ `FToolMenuEntrySubMenuData() : bIsSubMenu(false), bOpenSubMenuOnClick(false), bAutoCollapse(false)`
- L42 _public member_ `bool bIsSubMenu;`
- L43 _public member_ `bool bOpenSubMenuOnClick;`
- L45 _public member_ `bool bAutoCollapse;` — Entry placed into the parent's menu when there is only one entry
- L46 _public member_ `FNewToolMenuChoice ConstructMenu;`
- L49 _public member_ `FToolMenuEntryStyle Style;` — Optionally specify to override the default styling

#### struct `FToolMenuEntryOptionsDropdownData`  
`struct FToolMenuEntryOptionsDropdownData`  
_L52-57_
- L54 _public member_ `FNewToolMenuChoice MenuContentGenerator;`
- L55 _public member_ `TAttribute<FText> ToolTip;`
- L56 _public member_ `FUIAction Action;`

#### struct `FToolMenuEntryToolBarData`  
`struct FToolMenuEntryToolBarData`  
_L59-95_
- L63 _public member_ `TAttribute<FText> LabelOverride;` — Optional override label to use when the entry appears in a toolbar.
- L66 _public member_ `FName StyleNameOverride = NAME_None;` — Optional style override used when this entry appears in a toolbar.
- L69 _public member_ `FName BlockGroupName = NAME_None;` — When set, entries with the same name will be grouped together.
- L72 _public member_ `FNewToolMenuChoice ComboButtonContextMenuGenerator;` — Delegate that generates a widget for this combo button's menu content. Called when the menu is summoned.
- L75 _public member_ `FNewToolBarDelegateLegacy ConstructLegacy;` — Legacy delegate that generates a widget for this combo button's menu content. Called when the menu is summoned.
- L77 _public member_ `TSharedPtr<FToolMenuEntryOptionsDropdownData> OptionsDropdownData;`
- L79 _public member_ `bool bSimpleComboBox = false;`
- L82 _public member_ `bool bIsFocusable = false;` — Whether ToolBar will have Focusable buttons.
- L85 _public member_ `bool bForceSmallIcons = false;` — Whether this toolbar should always use small icons, regardless of the current settings.
- L88 _public member_ `TAttribute<EMenuPlacement> PlacementOverride;` — Optional override placement to customize menu placement once opened via e.g. a toolbar menu button
- L91 _public member_ `FMenuEntryResizeParams ResizeParams;` — Various Resize parameters and overrides, will take precedent over those stored in FToolMenuEntryWidgetData for ToolBar entries.
- L94 _public member_ `TOptional<FToolUIAction> ActionOverride;` — Optional action override to use when the entry appears in a toolbar

#### struct `FToolMenuEntryWidgetData`  
`struct FToolMenuEntryWidgetData`  
_L98-122_
- L101 _public function_ `FToolMenuEntryWidgetData() : bNoIndent(false), bSearchable(false), bNoPadding(false)`
- L109 _public member_ `bool bNoIndent;` — Remove the padding from the left of the widget that lines it up with other menu items
- L112 _public member_ `bool bSearchable;` — If true, widget will be searchable
- L115 _public member_ `bool bNoPadding;` — If true, no padding will be added
- L118 _public member_ `FMenuEntryStyleParams StyleParams;` — Various Style parameters and overrides
- L121 _public member_ `FMenuEntryResizeParams ResizeParams;` — Various Resize parameters and overrides

#### struct `FToolMenuCustomWidgetContext`  
`struct FToolMenuCustomWidgetContext`  
_L124-131_
- L127 _public member_ `const class ISlateStyle* StyleSet = nullptr;` — The style used by the menu creating the widget
- L130 _public member_ `FName StyleName;` — The name of the style used by the menu creating the widget

#### struct `FToolMenuVisibilityChoice`  
`struct FToolMenuVisibilityChoice`  
_L138-157_
- desc: A convenience wrapper for multiple ways of delivering a visibility value. Use by setting directly to TAttribute<EVisibility>, TAttribute<bool>, or FIsActionButtonVisible. Can also assign directly to a lambda, e.g `Choice = []{ return TrueOrFalse(); };`
- L140 _public prototype_ `FToolMenuVisibilityChoice();`
- L141 _public prototype_ `FToolMenuVisibilityChoice(const FToolMenuVisibilityChoice& Other);`
- L142 _public prototype_ `FToolMenuVisibilityChoice(const TAttribute<EVisibility>& InVisibility);`
- L143 _public prototype_ `FToolMenuVisibilityChoice(const TAttribute<bool>& InIsVisible);`
- L144 _public prototype_ `FToolMenuVisibilityChoice(const FIsActionButtonVisible& InIsActionButtonVisible);`
- L146 _public prototype_ `TAttribute<EVisibility> ToVisibilityAttribute() const;`
- L147 _public function_ `operator TAttribute<EVisibility>() const`
- L149 _public prototype_ `FToolMenuVisibilityChoice& operator=(TFunction<EVisibility()> VisibilityFunc);`
- L150 _public prototype_ `FToolMenuVisibilityChoice& operator=(TFunction<bool()> IsVisibleFunc);`
- L152 _public prototype_ `bool IsSet() const;`
- L153 _public prototype_ `EVisibility Get() const;`
- L156 _private member_ `TVariant<TAttribute<EVisibility>, TAttribute<bool>, FIsActionButtonVisible> Value;`

#### struct `FToolMenuEntry`  
`struct FToolMenuEntry`  
_L165-312_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents entries in menus such as buttons, checkboxes, and sub-menus. Many entries are created for you via the methods of FToolMenuSection, such as FToolMenuSection::AddMenuEntry.
- L169 _public prototype_ `FToolMenuEntry();`
- L170 _public prototype_ `FToolMenuEntry(const FToolMenuOwner InOwner, const FName InName, EMultiBlockType InType);`
- L172 _public prototype_ `FToolMenuEntry(const FToolMenuEntry&);`
- L173 _public prototype_ `FToolMenuEntry(FToolMenuEntry&&);`
- L175 _public prototype_ `FToolMenuEntry& operator=(const FToolMenuEntry&);`
- L176 _public prototype_ `FToolMenuEntry& operator=(FToolMenuEntry&&);`
- L178 _public prototype_ `static FToolMenuEntry InitMenuEntry(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const TAttribute<FSlateIcon>& InIcon, const FToolUIActionChoice& InAction, const EUserInterfaceActionType UserInterfaceActionType = EUserInterfaceActionType::Button, const FName InTutorialHighlightName = NAME_None, const TOptional<FText>& InInputBindingOverride = TOptional<FText>());`
- L179 _public prototype_ `static FToolMenuEntry InitMenuEntry(const TSharedPtr< const FUICommandInfo >& InCommand, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None, const TOptional<FName> InNameOverride = TOptional<FName>());`
- L180 _public prototype_ `static FToolMenuEntry InitMenuEntry(const FName InNameOverride, const TSharedPtr< const FUICommandInfo >& InCommand, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None);`
- L181 _public prototype_ `static FToolMenuEntry InitMenuEntryWithCommandList(const TSharedPtr<const FUICommandInfo>& InCommand, const TSharedPtr<const FUICommandList>& InCommandList, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None, const TOptional<FName> InNameOverride = TOptional<FName>());`
- L182 _public prototype_ `static FToolMenuEntry InitMenuEntry(const FName InName, const FToolUIActionChoice& InAction, const TSharedRef<SWidget>& Widget);`
- L183 _public prototype_ `static FToolMenuEntry InitDynamicEntry(const FName InName, const FNewToolMenuSectionDelegate& InConstruct);`
- L185 _public prototype_ `static FToolMenuEntry InitSubMenu(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const FNewToolMenuChoice& InMakeMenu, const FToolUIActionChoice& InAction, const EUserInterfaceActionType InUserInterfaceActionType, bool bInOpenSubMenuOnClick = false, const TAttribute<FSlateIcon>& InIcon = TAttribute<FSlateIcon>(), const bool bShouldCloseWindowAfterMenuSelection = true);`
- L186 _public prototype_ `static FToolMenuEntry InitSubMenu(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const FNewToolMenuChoice& InMakeMenu, bool bInOpenSubMenuOnClick = false, const TAttribute<FSlateIcon>& InIcon = TAttribute<FSlateIcon>(), const bool bShouldCloseWindowAfterMenuSelection = true, const FName InTutorialHighlightName = NAME_None);`
- L187 _public prototype_ `static FToolMenuEntry InitSubMenu(const FName InName, const FToolUIActionChoice& InAction, const TSharedRef<SWidget>& InWidget, const FNewToolMenuChoice& InMakeMenu, bool bShouldCloseWindowAfterMenuSelection = true);`
- L189 _public prototype_ `static FToolMenuEntry InitToolBarButton(const FName InName, const FToolUIActionChoice& InAction, const TAttribute<FText>& InLabel = TAttribute<FText>(), const TAttribute<FText>& InToolTip = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIcon = TAttribute<FSlateIcon>(), const EUserInterfaceActionType UserInterfaceActionType = EUserInterfaceActionType::Button, FName InTutorialHighlightName = NAME_None);`
- L190 _public prototype_ `static FToolMenuEntry InitToolBarButton(const TSharedPtr< const FUICommandInfo >& InCommand, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), FName InTutorialHighlightName = NAME_None, const TOptional<FName> InNameOverride = TOptional<FName>());`
- L191 _public prototype_ `static FToolMenuEntry InitComboButton(const FName InName, const FToolUIActionChoice& InAction, const FNewToolMenuChoice& InMenuContentGenerator, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), bool bInSimpleComboBox = false, FName InTutorialHighlightName = NAME_None);`
- L193 _public prototype_ `static FToolMenuEntry InitSeparator(const FName InName);`
- L195 _public prototype_ `static FToolMenuEntry InitWidget(const FName InName, const TSharedRef<SWidget>& InWidget, const FText& Label, bool bNoIndent = false, bool bSearchable = true, bool bNoPadding = false, const FText& InToolTipText = FText());`
- L197 _public function_ `bool IsSubMenu() const`
- L199 _public function_ `bool IsConstructLegacy() const`
- L205 _public prototype_ `ECheckBoxState GetCheckState(const FToolMenuContext& InContext) const;` — Get the checked state of this entry by calling underlying commands and delegates. @return: the checked state of this entry.
- L207 _public prototype_ `const FUIAction* GetActionForCommand(const FToolMenuContext& InContext, TSharedPtr<const FUICommandList>& OutCommandList) const;`
- L209 _public prototype_ `void SetCommandList(const TSharedPtr<const FUICommandList>& InCommandList);`
- L211 _public prototype_ `void AddKeybindFromCommand(const TSharedPtr< const FUICommandInfo >& InCommand);`
- L213 _public prototype_ `bool IsCommandKeybindOnly() const;`
- L214 _public prototype_ `bool CommandAcceptsInput(const FKeyEvent& InKeyEvent) const;`
- L215 _public prototype_ `bool TryExecuteToolUIAction(const FToolMenuContext& InContext);`
- L233 _public prototype_ `void SetShowInToolbarTopLevel(TAttribute<bool> InTopLevel);` — Show this menu entry in the top-level toolbar section of a toolbar. Entries of a toolbar submenu can be raised to the top-level of the toolbar. Such top-level entries appear in the toolbar to the right of the submenu they belong to. This flag only effects entries within submenus of toolbar-type ToolMenus. THIS AFFECTS STYLING. When an entry is raised to the top level of a toolbar, the ".Raised" suffix is added to the style name that would otherwise have been applied. @param InTopLevel True shows the entry in the top-level next to its submenu, false (default) only displays it in the submenu itself. Pass a delegate to drive the top-level state from code.
- L237 _private prototype_ `void SetCommand(const TSharedPtr< const FUICommandInfo >& InCommand, TOptional<FName> InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const TAttribute<FSlateIcon>& InIcon);`
- L239 _private prototype_ `void ResetActions();`
- L241 _private prototype_ `bool IsScriptObjectDynamicConstruct() const;`
- L243 _private prototype_ `bool IsNonLegacyDynamicConstruct() const;`
- L248 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L251 _public member_ `FToolMenuOwner Owner;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L254 _public member_ `EMultiBlockType Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L257 _public member_ `EUserInterfaceActionType UserInterfaceActionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L260 _public member_ `FName TutorialHighlightName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L263 _public member_ `FToolMenuInsert InsertPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L266 _public member_ `bool bShouldCloseWindowAfterMenuSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L269 _public member_ `TObjectPtr<UToolMenuEntryScript> ScriptObject;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L272 _public member_ `FName StyleNameOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L274 _public member_ `FToolMenuEntrySubMenuData SubMenuData;`
- L276 _public member_ `FToolMenuEntryToolBarData ToolBarData;`
- L278 _public member_ `FToolMenuEntryWidgetData WidgetData;`
- L281 _public member_ `FNewToolMenuCustomWidget MakeCustomWidget;` — Optional delegate that returns a widget to use as this menu entry
- L283 _public member_ `TAttribute<FText> Label;`
- L284 _public member_ `TAttribute<FText> ToolTip;`
- L285 _public member_ `TAttribute<FSlateIcon> Icon;`
- L286 _public member_ `TAttribute<FText> InputBindingLabel;`
- L288 _public member_ `FToolMenuVisibilityChoice Visibility;`
- L296 _private member_ `FToolUIActionChoice Action;`
- L298 _private member_ `FToolMenuStringCommand StringExecuteAction;`
- L300 _private member_ `TSharedPtr< const FUICommandInfo > Command;`
- L301 _private member_ `TSharedPtr< const FUICommandList > CommandList;`
- L303 _private member_ `FNewToolMenuSectionDelegate Construct;`
- L304 _private member_ `FNewToolMenuDelegateLegacy ConstructLegacy;`
- L306 _private member_ `bool bAddedDuringRegister;`
- L309 _private member_ `bool bCommandIsKeybindOnly;` — `UPROPERTY()`
- L311 _private member_ `TAttribute<bool> ShowInToolbarTopLevel;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API TOOLMENUS_API`

### `Source/Developer/ToolMenus/Public/ToolMenuEntryScript.h` (Public)


#### struct `FScriptSlateIcon`  
`struct FScriptSlateIcon`  
_L27-48_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/ToolMenus.ToolMenuEntryExtensions.BreakScriptSlateIcon", HasNativeMake="/Script/ToolMenus.ToolMenuEntryExtensions.MakeScriptSlateIcon"))`
- L32 _public prototype_ `FScriptSlateIcon();`
- L33 _public prototype_ `FScriptSlateIcon(const FName InStyleSetName, const FName InStyleName);`
- L34 _public prototype_ `FScriptSlateIcon(const FName InStyleSetName, const FName InStyleName, const FName InSmallStyleName);`
- L37 _public member_ `FName StyleSetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L40 _public member_ `FName StyleName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L43 _public member_ `FName SmallStyleName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L45 _public function_ `operator FSlateIcon() const`
- L47 _public prototype_ `FSlateIcon GetSlateIcon() const;`

#### struct `FToolMenuEntryScriptDataAdvanced`  
`struct FToolMenuEntryScriptDataAdvanced`  
_L51-82_
- reflection: `USTRUCT(BlueprintType)`
- L57 _public prototype_ `FToolMenuEntryScriptDataAdvanced();`
- L60 _public member_ `FName TutorialHighlight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`
- L63 _public member_ `EMultiBlockType EntryType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`
- L66 _public member_ `EUserInterfaceActionType UserInterfaceActionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`
- L69 _public member_ `FName StyleNameOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`
- L72 _public member_ `bool bIsSubMenu;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubMenu")`
- L75 _public member_ `bool bOpenSubMenuOnClick;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubMenu")`
- L78 _public member_ `bool bShouldCloseWindowAfterMenuSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`
- L81 _public member_ `bool bSimpleComboBox;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToolBar")`

#### struct `FToolMenuEntryScriptData`  
`struct FToolMenuEntryScriptData`  
_L85-118_
- reflection: `USTRUCT(BlueprintType)`
- L92 _public member_ `FName Menu;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")`
- L95 _public member_ `FName Section;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")`
- L98 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")`
- L101 _public member_ `FText Label;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L104 _public member_ `FText ToolTip;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L107 _public member_ `FScriptSlateIcon Icon;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L111 _public member_ `FName OwnerName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")` — Optional identifier used for unregistering a group of menu items
- L114 _public member_ `FToolMenuInsert InsertPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")`
- L117 _public member_ `FToolMenuEntryScriptDataAdvanced Advanced;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced")`

#### class `UToolMenuEntryScript`  
`class UToolMenuEntryScript : public UObject`  
_L121-204_
- reflection: `UCLASS(MinimalAPI, Blueprintable, abstract)`
- inherits: `UObject`
- L128 _public prototype_ `void Execute(const FToolMenuContext& Context);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Action")`
- L131 _public prototype_ `bool CanExecute(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L132 _public function_ `virtual bool CanExecute_Implementation(const FToolMenuContext& Context) const`
- L135 _public prototype_ `ECheckBoxState GetCheckState(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L136 _public function_ `virtual ECheckBoxState GetCheckState_Implementation(const FToolMenuContext& Context) const`
- L139 _public prototype_ `bool IsVisible(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L140 _public function_ `virtual bool IsVisible_Implementation(const FToolMenuContext& Context) const`
- L143 _public prototype_ `FText GetLabel(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L144 _public function_ `virtual FText GetLabel_Implementation(const FToolMenuContext& Context) const`
- L147 _public prototype_ `FText GetToolTip(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L148 _public function_ `virtual FText GetToolTip_Implementation(const FToolMenuContext& Context) const`
- L151 _public prototype_ `FScriptSlateIcon GetIcon(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L152 _public function_ `virtual FScriptSlateIcon GetIcon_Implementation(const FToolMenuContext& Context) const`
- L155 _public prototype_ `void ConstructMenuEntry(UToolMenu* Menu, const FName SectionName, const FToolMenuContext& Context);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Advanced")`
- L158 _public prototype_ `void RegisterMenuEntry();` — `UFUNCTION(BlueprintCallable, Category = "Advanced")`
- L161 _public prototype_ `void UnregisterMenuEntry();` — `UFUNCTION(BlueprintCallable, Category = "Advanced")`
- L164 _public prototype_ `void InitEntry(const FName OwnerName, const FName Menu, const FName Section, const FName Name, const FText& Label = FText(), const FText& ToolTip = FText());` — `UFUNCTION(BlueprintCallable, Category = "Advanced")`
- L167 _public prototype_ `bool ShowInToolbarTopLevel(const FToolMenuContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Advanced")`
- L168 _public function_ `virtual bool ShowInToolbarTopLevel_Implementation(const FToolMenuContext& Context) const`
- L173 _public function_ `FORCEINLINE bool CanSafelyRouteCall()`
- L175 _public prototype_ `static UToolMenuEntryScript* GetIfCanSafelyRouteCall(const TWeakObjectPtr<UToolMenuEntryScript>& InWeak);`
- L183 _private prototype_ `TAttribute<FText> CreateLabelAttribute(FToolMenuContext& Context);`
- L185 _private prototype_ `TAttribute<FText> CreateToolTipAttribute(FToolMenuContext& Context);`
- L187 _private prototype_ `TAttribute<FSlateIcon> CreateIconAttribute(FToolMenuContext& Context);`
- L189 _private prototype_ `TAttribute<bool> CreateShowInToolbarTopLevelAttribute(FToolMenuContext& Context);`
- L191 _private prototype_ `void ToMenuEntry(FToolMenuEntry& Output);`
- L193 _private prototype_ `bool IsDynamicConstruct() const;`
- L195 _private prototype_ `FSlateIcon GetSlateIcon(const FToolMenuContext& Context) const;`
- L200 _public member_ `FToolMenuEntryScriptData Data;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")`
- L203 _public member_ `bool bHasRegisteredMenuEntry = false;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API TOOLMENUS_API`

### `Source/Developer/ToolMenus/Public/ToolMenuIteration.h` (Public)


#### struct `UE::ToolMenus::FToolMenuIterationInfo`  
`struct FToolMenuIterationInfo`  
_L16-23_
- L18 _public prototype_ `FToolMenuIterationInfo(const UToolMenu& InMenu, const FToolMenuSection& InSection, const FToolMenuEntry& InEntry);`
- L20 _public member_ `const UToolMenu& Menu;`
- L21 _public member_ `const FToolMenuSection& Section;`
- L22 _public member_ `const FToolMenuEntry& Entry;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ToolMenus` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuVisitor, const FToolMenuIterationInfo& IterationInfo);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FToolMenuVisitor, const FToolMenuIterationInfo& IterationInfo);` (scope `UE::ToolMenus`)
- L27 _prototype_ `void VisitMenuEntries( UToolMenus* InToolMenus, const FName InMenuName, const FToolMenuContext& InContext, const FToolMenuVisitor& InVisitor );` (scope `UE::ToolMenus`)

### `Source/Developer/ToolMenus/Public/ToolMenuMisc.h` (Public)


#### enum `EToolMenuStringCommandType`  
`enum class EToolMenuStringCommandType : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Command`
- L18 _public enumerator_ `Python`
- L19 _public enumerator_ `Custom`

#### struct `FToolMenuStringCommand`  
`struct FToolMenuStringCommand`  
_L23-57_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/ToolMenus.ToolMenuEntryExtensions.BreakStringCommand", HasNativeMake="/Script/ToolMenus.ToolMenuEntryExtensions.MakeStringCommand"))`
- L27 _public function_ `FToolMenuStringCommand() : Type(EToolMenuStringCommandType::Command)`
- L29 _public function_ `FToolMenuStringCommand(EToolMenuStringCommandType InType, FName InCustomType, const FString& InString) : Type(InType), CustomType(InCustomType), String(InString)`
- L38 _public member_ `EToolMenuStringCommandType Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — Which command handler to use
- L42 _public member_ `FName CustomType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — Which command handler to use when type is custom
- L46 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — String to pass to command handler
- L52 _private function_ `bool IsBound() const`
- L54 _private prototype_ `FExecuteAction ToExecuteAction(FName MenuName, const FToolMenuContext& Context) const;`
- L56 _private prototype_ `FName GetTypeName() const;`

#### enum `EToolMenuInsertType`  
`enum class EToolMenuInsertType : uint8`  
_L60-67_
- reflection: `UENUM(BlueprintType)`
- L62 _public enumerator_ `Default`
- L63 _public enumerator_ `Before`
- L64 _public enumerator_ `After`
- L65 _public enumerator_ `First`
- L66 _public enumerator_ `Last`

#### enum `EToolMenuInsertFallback`  
`enum class EToolMenuInsertFallback : uint8`  
_L70-77_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))`
- L72 _public enumerator_ `None = 0 UMETA(Hidden)`
- L74 _public enumerator_ `Insert = 1 << 0` — Insert the item even when the target is not found
- L76 _public enumerator_ `Log = 1 << 1` — Log a warning if the target is not found

#### struct `FToolMenuInsert`  
`struct FToolMenuInsert`  
_L81-119_
- reflection: `USTRUCT(BlueprintType)`
- L85 _public function_ `FToolMenuInsert() : Position(EToolMenuInsertType::Default)`
- L86 _public function_ `FToolMenuInsert(FName InName, EToolMenuInsertType InPosition) : Name(InName), Position(InPosition)`
- L90 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — Where to insert
- L94 _public member_ `EToolMenuInsertType Position;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — How to insert
- L98 _public member_ `EToolMenuInsertFallback Fallback = EToolMenuInsertFallback::Insert | EToolMenuInsertFallback::Log;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")` — How to handle an item when the target insertion position is not found. Defaults to inserting the item while logging that the target was not found.
- L100 _public function_ `FORCEINLINE bool operator==(const FToolMenuInsert& Other) const`
- L105 _public function_ `FORCEINLINE bool operator!=(const FToolMenuInsert& Other) const`
- L110 _public function_ `bool IsDefault() const`
- L115 _public function_ `bool IsBeforeOrAfter() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TOOLMENUS_API`
- L78 _prototype_ `ENUM_CLASS_FLAGS(EToolMenuInsertFallback);`

### `Source/Developer/ToolMenus/Public/ToolMenuOwner.h` (Public)


#### struct `FToolMenuOwner`  
`struct FToolMenuOwner`  
_L16-93_
- reflection: `USTRUCT(BlueprintType, meta=(HasNativeBreak="/Script/ToolMenus.ToolMenuEntryExtensions.BreakToolMenuOwner", HasNativeMake="/Script/ToolMenus.ToolMenuEntryExtensions.MakeToolMenuOwner"))`
- desc: Represents the owner of a menu. Can be used when registering menus to later unregistering all menus created by a specified owner. See UToolMenus::UnregisterOwnerByName and FToolMenuOwnerScoped which relate to this.
- L35 _public function_ `FORCEINLINE FToolMenuOwner() : ValueInt64(0), ValueType(EValueType::None)`
- L36 _public function_ `FORCEINLINE FToolMenuOwner(void* InPointer) : ValueInt64(reinterpret_cast<int64>(InPointer)), ValueType(EValueType::Pointer)`
- L38 _public function_ `FToolMenuOwner(const WIDECHAR* InValue) : FToolMenuOwner(FName(InValue))`
- L39 _public function_ `FToolMenuOwner(const ANSICHAR* InValue) : FToolMenuOwner(FName(InValue))`
- L41 _public function_ `FToolMenuOwner(const FName InValue)`
- L56 _public function_ `FORCEINLINE bool operator==(const FToolMenuOwner& Other) const`
- L61 _public function_ `FORCEINLINE bool operator!=(const FToolMenuOwner& Other) const`
- L71 _public function_ `FORCEINLINE bool IsSet() const`
- L73 _public function_ `FName TryGetName() const`
- L92 _private member_ `EValueType ValueType;`

#### struct `FToolMenuOwner::FStoreName`  
`struct FStoreName`  
_L21-25_
- L23 _public member_ `int32 Index;`
- L24 _public member_ `int32 Number;`

#### enum `FToolMenuOwner::EValueType`  
`enum class EValueType : uint8`  
_L27-32_
- L29 _public enumerator_ `None`
- L30 _public enumerator_ `Pointer`
- L31 _public enumerator_ `Name`

#### union `FToolMenuOwner::(anonymous)`  
``  
_L87-90_

#### Free symbols / members of external scopes

- L66 _function_ `friend uint32 GetTypeHash(const FToolMenuOwner& Key)`
- L88 _member_ `int64 ValueInt64;` (scope `FToolMenuOwner::__anon5a006222010a`)
- L89 _member_ `FStoreName ValueName;` (scope `FToolMenuOwner::__anon5a006222010a`)

### `Source/Developer/ToolMenus/Public/ToolMenuSection.h` (Public)


#### class `UToolMenuSectionDynamic`  
`class UToolMenuSectionDynamic : public UObject`  
_L16-24_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L23 _public prototype_ `void ConstructSections(UToolMenu* Menu, const FToolMenuContext& Context);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Tool Menus")`

#### enum `EToolMenuSectionAlign`  
`enum class EToolMenuSectionAlign : uint8`  
_L27-33_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Default`
- L30 _public enumerator_ `First`
- L31 _public enumerator_ `Middle`
- L32 _public enumerator_ `Last`

#### struct `FToolMenuSection`  
`struct FToolMenuSection`  
_L36-155_
- reflection: `USTRUCT(BlueprintType)`
- L42 _public prototype_ `FToolMenuSection();`
- L44 _public prototype_ `void InitSection(const FName InName, const TAttribute< FText >& InLabel, const FToolMenuInsert InPosition);`
- L46 _public prototype_ `FToolMenuEntry& AddEntryObject(UToolMenuEntryScript* InObject);`
- L47 _public prototype_ `FToolMenuEntry& AddEntry(const FToolMenuEntry& Args);`
- L62 _public prototype_ `FToolMenuEntry& AddMenuEntry(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const TAttribute<FSlateIcon>& InIcon, const FToolUIActionChoice& InAction, const EUserInterfaceActionType UserInterfaceActionType = EUserInterfaceActionType::Button, const FName InTutorialHighlightName = NAME_None, const TOptional<FText>& InInputBindingOverride = TOptional<FText>());` — Add a menu entry to this section. @param InName The FName of the added entry used to identify it. @param InLabel The user-visible label of this entry. @param InToolTip The user-visible tooltip of this entry. @param InIcon The user-visible icon of this entry. @param InAction The delegates to call to make this entry interactive. Supports more than just on-click delegates. See FToolUIActionChoice for more information. @param UserInterfaceActionType The type of user interface element (such as a checkbox) to use for this entry. See EUserInterfaceActionType for more options. @param InTutorialHighlightName The tutorial highlight key @param InInputBindingOverride The key-binding reminder @return A reference to the added menu entry.
- L63 _public prototype_ `FToolMenuEntry& AddMenuEntry(const TSharedPtr< const FUICommandInfo >& InCommand, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None, const TOptional<FName> InNameOverride = TOptional<FName>());`
- L64 _public prototype_ `FToolMenuEntry& AddMenuEntry(const FName InNameOverride, const TSharedPtr< const FUICommandInfo >& InCommand, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None);`
- L65 _public prototype_ `FToolMenuEntry& AddMenuEntryWithCommandList(const TSharedPtr<const FUICommandInfo>& InCommand, const TSharedPtr<const FUICommandList>& InCommandList, const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), const TAttribute<FSlateIcon>& InIconOverride = TAttribute<FSlateIcon>(), const FName InTutorialHighlightName = NAME_None, const TOptional<FName> InNameOverride = TOptional<FName>());`
- L67 _public prototype_ `FToolMenuEntry& AddDynamicEntry(const FName InName, const FNewToolMenuSectionDelegate& InConstruct);`
- L68 _public prototype_ `FToolMenuEntry& AddDynamicEntry(const FName InName, const FNewToolMenuDelegateLegacy& InConstruct);`
- L70 _public prototype_ `FToolMenuEntry& AddSeparator(const FName InName);`
- L86 _public prototype_ `FToolMenuEntry& AddSubMenu(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const FNewToolMenuChoice& InMakeMenu, const FToolUIActionChoice& InAction, const EUserInterfaceActionType InUserInterfaceActionType, bool bInOpenSubMenuOnClick = false, const TAttribute<FSlateIcon>& InIcon = TAttribute<FSlateIcon>(), const bool bShouldCloseWindowAfterMenuSelection = true);` — Add a sub-menu to this section. @param InName The FName to use for identifying this sub-menu. Must be unique within the section. @param InLabel The user-visible label to use for this sub-menu. @param InToolTip The user-visible tooltip to use for this sub-menu. @param InMakeMenu The delegate to call to construct the sub-menu. This delegate is called when the user clicks the sub-menu entry. @param InAction The delegates to use to make this menu entry interactive. @param InUserInterfaceActionType The type of user interface element (such as a checkbox) to use for this entry. @param bInOpenSubMenuOnClick Whether or not the sub-menu entry opens when it is hovered or only when clicked. @param InIcon The user-visible icon to use for this sub-menu. @param bShouldCloseWindowAfterMenuSelection Whether or not the sub-menu should close after one of its entries is clicked. @return A reference to the menu entry for the added sub-menu.
- L87 _public prototype_ `FToolMenuEntry& AddSubMenu(const FName InName, const TAttribute<FText>& InLabel, const TAttribute<FText>& InToolTip, const FNewToolMenuChoice& InMakeMenu, bool bInOpenSubMenuOnClick = false, const TAttribute<FSlateIcon>& InIcon = TAttribute<FSlateIcon>(), const bool bShouldCloseWindowAfterMenuSelection = true, const FName InTutorialHighlightName = NAME_None);`
- L88 _public prototype_ `FToolMenuEntry& AddSubMenu(const FName InName, const FToolUIActionChoice& InAction, const TSharedRef<SWidget>& InWidget, const FNewToolMenuChoice& InMakeMenu, bool bShouldCloseWindowAfterMenuSelection = true);`
- L91 _public function_ `template <typename TContextType> TContextType* FindContext() const`
- L96 _public prototype_ `FToolMenuEntry* FindEntry(const FName InName);`
- L97 _public prototype_ `const FToolMenuEntry* FindEntry(const FName InName) const;`
- L101 _private prototype_ `void InitGeneratedSectionCopy(const FToolMenuSection& Source, FToolMenuContext& InContext);`
- L103 _private prototype_ `int32 RemoveEntry(const FName InName);`
- L104 _private prototype_ `int32 RemoveEntryObject(const UToolMenuEntryScript* InObject);`
- L105 _private prototype_ `int32 RemoveEntriesByOwner(const FToolMenuOwner InOwner);`
- L107 _private prototype_ `int32 IndexOfBlock(const FName InName) const;`
- L108 _private prototype_ `int32 FindBlockInsertIndex(const FToolMenuEntry& InBlock) const;`
- L110 _private prototype_ `bool IsNonLegacyDynamic() const;`
- L112 _private prototype_ `bool IsRegistering() const;`
- L121 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L124 _public member_ `FToolMenuOwner Owner;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L127 _public member_ `TArray<FToolMenuEntry> Blocks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L130 _public member_ `FToolMenuInsert InsertPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L133 _public member_ `FToolMenuContext Context;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L136 _public member_ `TObjectPtr<UToolMenuSectionDynamic> ToolMenuSectionDynamic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Menus")`
- L138 _public member_ `TAttribute<FText> Label;`
- L139 _public member_ `FToolMenuVisibilityChoice Visibility;`
- L141 _public member_ `FNewSectionConstructChoice Construct;`
- L143 _public member_ `EToolMenuSectionAlign Alignment;`
- L146 _public member_ `FMenuEntryResizeParams ResizeParams;` — Section-level resize parameters.
- L149 _public member_ `FToolMenuSectionSorter Sorter;` — A sorting function for blocks within this section. Blocks are sorted after all entries have been added.
- L153 _private member_ `bool bIsRegistering;`
- L154 _private member_ `bool bAddedDuringRegister;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TOOLMENUS_API`

### `Source/Developer/ToolMenus/Public/ToolMenuWidgetCollectionContext.h` (Public)


#### class `UToolMenuWidgetCollectionContext`  
`class UToolMenuWidgetCollectionContext : public UToolMenuContextBase`  
_L16-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolMenuContextBase`
- desc: Context class containing a collection of widgets that can be added for later retrieval. @see FToolMenuContext
- L27 _public prototype_ `[[nodiscard]] static UToolMenuWidgetCollectionContext* Get(FToolMenuContext& Context, bool bCreateIfNeeded = true);` — Get the widget collection context object from the parameter context. @param Context The tool menu context to retrieve the context object from. @param bCreateIfNeeded If true (default) then the context object is created if one wasn't found. @return The context object, or null if one wasn't found and bCreateIfNeeded was false.
- L34 _public prototype_ `void AddWidget(const TSharedRef<SWidget>& Widget);` — Add a widget to this context for later retrieval. @param Widget The widget to add to the context. @see FindContextWidget
- L45 _public function_ `template <typename WidgetType> [[nodiscard]] TSharedPtr<WidgetType> FindWidget() const` — Find a previously added widget. Uses the widget's type via WidgetType::StaticWidgetClass. @tparam WidgetType The type of widget to find. @return The widget, if found. A null pointer otherwise. @note This requires that the widget implements SLATE_DECLARE_WIDGET in its class definition. @note This function performs an exact match on the widget type - there is no inheritance checking. @see AddWidget
- L55 _public prototype_ `void EnumerateWidgets(const TFunctionRef<bool(const TSharedPtr<SWidget>& Widget)>& Callback) const;` — Enumerate all the previously added widgets. @param InCallback Callback invoked for each wdget; return true to continue enumeration, or false to stop.
- L58 _private prototype_ `[[nodiscard]] TSharedPtr<SWidget> FindWidgetByClassType(const FName& WidgetClassType) const;`
- L60 _private member_ `TArray<TWeakPtr<SWidget>> Widgets;`

### `Source/Developer/ToolMenus/Public/ToolMenus.h` (Public)


#### struct `FGeneratedToolMenuWidget`  
`struct FGeneratedToolMenuWidget`  
_L41-51_
- L44 _public member_ `TObjectPtr<UToolMenu> GeneratedMenu;` — A copy of the menu so we can refresh menus not in the database
- L47 _public member_ `TWeakPtr<SWidget> Widget;` — The actual widget for the menu
- L50 _public member_ `TWeakObjectPtr<UToolMenu> OriginalMenu;` — Weak ptr to the original menu that owns the widget

#### struct `FGeneratedToolMenuWidgets`  
`struct FGeneratedToolMenuWidgets`  
_L53-56_
- L55 _public member_ `TArray<TSharedPtr<FGeneratedToolMenuWidget>> Instances;`

#### struct `UE::ToolMenus::FSubBlockReference`  
`struct FSubBlockReference`  
_L63-72_
- desc: A handle to a particular entry. Used when elevating child elements to a parent toolbar.
- L65 _public prototype_ `FSubBlockReference();`
- L66 _public prototype_ `FSubBlockReference(const FSubBlockReference& Other);`
- L67 _public prototype_ `FSubBlockReference(UToolMenu* InParent, FToolMenuSection* InSection, FToolMenuEntry* InEntry);`
- L69 _public member_ `UToolMenu* ParentMenu;`
- L70 _public member_ `FToolMenuSection* Section;`
- L71 _public member_ `FToolMenuEntry* Entry;`

#### class `UToolMenuProfileContext`  
`class UToolMenuProfileContext : public UToolMenuContextBase`  
_L79-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolMenuContextBase`
- desc: A global context that any menu can add/modify to specify which profiles are currently active
- L84 _public member_ `TArray<FName> ActiveProfiles;`

#### struct `FToolMenuProfileMap`  
`struct FToolMenuProfileMap`  
_L91-97_
- reflection: `USTRUCT()`
- desc: Struct to store all the profiles for a menu for serialization
- L96 _public member_ `TMap<FName , FToolMenuProfile> MenuProfiles;` — `UPROPERTY()`

#### class `UToolMenus`  
`class UToolMenus : public UObject`  
_L100-525_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L106 _public prototype_ `UToolMenus();`
- L109 _public prototype_ `static UToolMenus* Get();` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")`
- L112 _public function_ `static inline UToolMenus* TryGet()` — Try to get UToolMenus without forcing ToolMenus module to load.
- L123 _public function_ `static inline void UnregisterOwner(FToolMenuOwner Owner)` — Unregister everything associated with the given owner without forcing ToolMenus module to load.
- L137 _public prototype_ `static bool IsToolMenuUIEnabled();` — Returns true if slate initialized and editor GUI is being used. The application should have been initialized before this method is called. @return	True if slate initialized and editor GUI is being used.
- L145 _public prototype_ `static FDelegateHandle RegisterStartupCallback(const FSimpleMulticastDelegate::FDelegate& InDelegate);` — Delays menu registration until safe and ready Will not trigger if Slate does not end up being enabled after loading Will not trigger when running commandlet, game, dedicated server or client only
- L148 _public prototype_ `static void UnRegisterStartupCallback(FDelegateUserObjectConst UserPointer);` — Unregister a startup callback delegate by pointer
- L151 _public prototype_ `static void UnRegisterStartupCallback(FDelegateHandle InHandle);` — Unregister a startup callback delegate by handle
- L161 _public prototype_ `UToolMenu* RegisterMenu(FName Name, const FName Parent = NAME_None, EMultiBoxType Type = EMultiBoxType::Menu, bool bWarnIfAlreadyRegistered = true);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Registers a menu by name @param	Parent	Optional name of a menu to layer on top of. @param	Type	Type of menu that will be generated such as: ToolBar, VerticalToolBar, etc.. @param	bWarnIfAlreadyRegistered	Display warning if already registered @return	ToolMenu	Menu object
- L169 _public prototype_ `UToolMenu* ExtendMenu(const FName Name);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Extends a menu without registering the menu or claiming ownership of it. Ok to call even if menu does not exist yet. @param	Name	Name of the menu to extend @return	ToolMenu	Menu object
- L177 _public prototype_ `TSharedRef<SWidget> GenerateWidget(const FName Name, const FToolMenuContext& InMenuContext);` — Generate widget from a registered menu. Most common function used to generate new menu widgets. @param	Name	Registered menu's name that widget will be generated from @param	Context	Additional information specific to the menu being generated @return	Widget to display
- L185 _public prototype_ `UToolMenu* FindMenu(const FName Name);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Finds an existing menu that has been registered or extended. @param	Name	Name of the menu to find. @return	ToolMenu	Menu object. Returns null if not found.
- L193 _public prototype_ `bool IsMenuRegistered(const FName Name) const;` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Determines if a menu has already been registered. @param	Name	Name of the menu to find. @return	bool	True if menu has already been registered.
- L197 _public prototype_ `bool RefreshMenuWidget(const FName Name);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Rebuilds all widgets generated from a specific menu.
- L201 _public prototype_ `void RefreshAllWidgets();` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Rebuilds all currently generated widgets next tick.
- L205 _public prototype_ `static bool AddMenuEntryObject(UToolMenuEntryScript* MenuEntryObject);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Registers menu entry object from blueprint/script
- L209 _public prototype_ `static bool RemoveMenuEntryObject(UToolMenuEntryScript* MenuEntryObject);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Unregisters menu entry object from blueprint/script
- L213 _public prototype_ `void UnregisterOwnerByName(FName InOwnerName);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Removes all entries that were registered under a specific owner name
- L217 _public prototype_ `void SetSectionLabel(const FName MenuName, const FName SectionName, const FText Label);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Sets a section's displayed label text.
- L221 _public prototype_ `void SetSectionPosition(const FName MenuName, const FName SectionName, const FName OtherSectionName, const EToolMenuInsertType PositionType);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Sets where to insert a section into a menu when generating relative to other section names.
- L224 _public prototype_ `void AddSection(const FName MenuName, const FName SectionName, const TAttribute< FText >& InLabel, const FToolMenuInsert InPosition = FToolMenuInsert());` — Registers a section for a menu
- L227 _public prototype_ `void AddEntry(const FName MenuName, const FName SectionName, const FToolMenuEntry& Entry);` — Registers an entry for a menu's section
- L231 _public prototype_ `void RemoveEntry(const FName MenuName, const FName Section, const FName Name);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Removes a menu entry from a given menu and section
- L235 _public prototype_ `void RemoveSection(const FName MenuName, const FName Section);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Removes a section from a given menu
- L239 _public prototype_ `void RemoveMenu(const FName MenuName);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Unregisters a menu by name
- L243 _public prototype_ `static UObject* FindContext(const FToolMenuContext& InContext, UClass* InClass);` — `UFUNCTION(BlueprintCallable, Category = "Tool Menus")` — Finds a context object of a given class if it exists
- L251 _public prototype_ `TSharedRef<SWidget> GenerateWidget(const TArray<UToolMenu*>& Hierarchy, const FToolMenuContext& InMenuContext);` — Generate widget from a hierarchy of menus. For advanced specialized use cases. @param	Hierarchy	Array of menus to combine into a final widget @param	Context	Additional information specific to the menu being generated @return	Widget to display
- L258 _public prototype_ `TSharedRef<SWidget> GenerateWidget(UToolMenu* GeneratedMenu);` — Generate widget from a final collapsed menu. For advanced specialized use cases. @param	GeneratedMenu	Combined final menu to generate final widget from @return	Widget to display
- L261 _public prototype_ `UToolMenu* GenerateMenu(const FName Name, const FToolMenuContext& InMenuContext);` — Create a finalized menu that combines all parents used to generate a widget. Advanced special use cases only.
- L264 _public prototype_ `UToolMenu* GenerateMenuAsBuilder(const UToolMenu* InMenu, const FToolMenuContext& InMenuContext);` — Create a finalized menu based on a custom crafted menu. Advanced special use cases only.
- L267 _public prototype_ `UToolMenu* GenerateMenuOrSubMenuForEdit(const UToolMenu* InMenu);` — Generate either a menu or submenu ready for editing
- L270 _public prototype_ `void AssembleMenuHierarchy(UToolMenu* GeneratedMenu, const TArray<UToolMenu*>& Hierarchy);` — Bake final menu including calls to construction delegates, sorting, and customization
- L273 _public prototype_ `TArray<UToolMenu*> CollectHierarchy(const FName Name);` — Returns list of menus starting with root parent
- L276 _public prototype_ `FToolMenuOwner CurrentOwner() const;` — For advanced use cases
- L279 _public prototype_ `void RegisterStringCommandHandler(const FName InName, const FToolMenuExecuteString& InDelegate);` — Registers a new type of string based command handler.
- L282 _public prototype_ `void UnregisterStringCommandHandler(const FName InName);` — Removes a string based command handler.
- L284 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStringCommandExecuted, FName MenuName, FName TypeName);`
- L286 _public member_ `FOnStringCommandExecuted OnStringCommandExecuted;` — Called when we execute a string command. Useful for analytics
- L289 _public prototype_ `void AssignSetTimerForNextTickDelegate(const FSimpleDelegate& InDelegate);` — Sets delegate to setup timer for deferred one off ticks
- L292 _public prototype_ `void HandleNextTick();` — Timer function used to consolidate multiple duplicate requests into a single frame.
- L295 _public prototype_ `void RemoveCustomization(const FName InName);` — Remove customization for a menu
- L298 _public prototype_ `void RemoveAllCustomizations();` — Remove all menu customizations for all menus
- L301 _public prototype_ `void SaveCustomizations();` — Save menu customizations to ini files
- L304 _public prototype_ `FCustomizedToolMenu* FindMenuCustomization(const FName InName);` — Find customization settings for a menu
- L307 _public prototype_ `FCustomizedToolMenu* AddMenuCustomization(const FName InName);` — Find or add customization settings for a menu
- L310 _public prototype_ `int32 FindMenuCustomizationIndex(const FName InName);` — Find index of customization settings for a menu
- L313 _public prototype_ `FCustomizedToolMenu* FindRuntimeMenuCustomization(const FName InName);` — Find runtime customization settings for a menu
- L316 _public prototype_ `FCustomizedToolMenu* AddRuntimeMenuCustomization(const FName InName);` — Find or add runtime customization settings for a menu
- L319 _public prototype_ `FToolMenuProfile* FindMenuProfile(const FName InMenuName, const FName InProfileName);` — Find a specific profile for a menu
- L322 _public prototype_ `FToolMenuProfile* AddMenuProfile(const FName InMenuName, const FName InProfileName);` — Find or add a specific profile for a menu
- L325 _public prototype_ `FToolMenuProfile* FindRuntimeMenuProfile(const FName InMenuName, const FName InProfileName);` — Find a specific runtime only profile for a menu
- L328 _public prototype_ `FToolMenuProfile* AddRuntimeMenuProfile(const FName InMenuName, const FName InProfileName);` — Find or add a specific runtime only profile for a menu
- L331 _public prototype_ `void UnregisterRuntimeMenuCustomizationOwner(const FName InOwnerName);` — Unregister runtime customization settings for a specific owner name
- L334 _public prototype_ `void UnregisterRuntimeMenuProfileOwner(const FName InOwnerName);` — Unregister runtime profile settings for a specific owner name
- L337 _public prototype_ `UToolMenu* GenerateSubMenu(const UToolMenu* InGeneratedParent, const FName InBlockName);` — Generates sub menu by entry name in the given generated menu parent
- L340 _public prototype_ `bool GetEditMenusMode() const;` — When true, adds command to open edit menu dialog to each menu
- L343 _public prototype_ `void SetEditMenusMode(bool bEnable);` — Enables adding command to open edit menu dialog to each menu
- L346 _public prototype_ `void AddMenuSubstitutionDuringGenerate(const FName OriginalMenu, const FName NewMenu);` — Substitute one menu for another during generate but not during find or extend
- L349 _public prototype_ `void RemoveSubstitutionDuringGenerate(const FName InMenu);` — Remove substitute one menu for another during generate
- L352 _public prototype_ `void CleanupStaleWidgetsNextTick(bool bGarbageCollect = false);` — Release references to UObjects of widgets that have been deleted. Combines multiple requests in one frame together for improved performance.
- L355 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FShouldDisplayExtensionPoints);` — Displaying extension points is for debugging menus
- L356 _public member_ `FShouldDisplayExtensionPoints ShouldDisplayExtensionPoints;`
- L359 _public prototype_ `DECLARE_DELEGATE_OneParam(FEditMenuDelegate, class UToolMenu*);` — Delegate that opens a menu editor
- L360 _public member_ `FEditMenuDelegate EditMenuDelegate;`
- L362 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FGenerateWidgetEvent, const FName InName, const FToolMenuContext& InMenuContext);`
- L364 _public member_ `FGenerateWidgetEvent OnPreGenerateWidget;` — Called before we generate a menu widget.
- L366 _public member_ `FGenerateWidgetEvent OnPostGenerateWidget;` — Called after we generate a menu widget.
- L369 _public member_ `FSlateIcon EditMenuIcon;` — Icon to display in menus for command to open menu editor
- L372 _public member_ `FSlateIcon EditToolbarIcon;` — Icon to display in toolbars for command to open menu editor
- L375 _public prototype_ `static FName JoinMenuPaths(const FName Base, const FName Child);` — Join two paths together
- L378 _public prototype_ `static bool SplitMenuPath(const FName MenuPath, FName& OutLeft, FName& OutRight);` — Break apart a menu path into components
- L381 _public prototype_ `static bool CanSafelyRouteCall();` — Returns true if safe to call into script
- L387 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L388 _public prototype_ `virtual void BeginDestroy() override;`
- L395 _private prototype_ `UToolMenu* GenerateMenuFromHierarchy(const TArray<UToolMenu*>& Hierarchy, const FToolMenuContext& InMenuContext);` — Create a finalized menu that combines given hierarchy array that will generate a widget. Advanced special use cases only.
- L398 _private prototype_ `void SetNextTickTimer();` — Sets a timer to be called next engine tick so that multiple repeated actions can be combined together.
- L401 _private prototype_ `void CleanupStaleWidgets();` — Release references to UObjects of widgets that have been deleted
- L404 _private prototype_ `bool RefreshMenuWidget(const FName Name, FGeneratedToolMenuWidget& GeneratedMenuWidget);` — Re-creates widget that is active
- L407 _private prototype_ `void PushOwner(const FToolMenuOwner InOwner);` — Sets the current temporary menu owner to avoid needing to supply owner for each menu entry being registered. Used by FToolMenuEntryScoped
- L410 _private prototype_ `void PopOwner(const FToolMenuOwner InOwner);` — Sets the current temporary menu owner. Used by FToolMenuEntryScoped
- L412 _private prototype_ `static void PrivateStartupCallback();`
- L413 _private prototype_ `static void UnregisterPrivateStartupCallback();`
- L415 _private prototype_ `UToolMenu* FindSubMenuToGenerateWith(const FName InParentName, const FName InChildName);`
- L417 _private prototype_ `void PopulateMenuBuilder(FMenuBuilder& MenuBuilder, UToolMenu* MenuData);`
- L418 _private prototype_ `void PopulateMenuBarBuilder(FMenuBarBuilder& MenuBarBuilder, UToolMenu* MenuData);`
- L420 _private prototype_ `void ExtractChildBlocksFromSubMenu(UToolMenu* ParentMenu, FToolMenuEntry& InBlock, TArray<UE::ToolMenus::FSubBlockReference>& SubMenuBlocks);`
- L421 _private prototype_ `void PopulateToolBarBuilderWithTopLevelChildren(FToolBarBuilder& ToolBarBuilder, UToolMenu* ParentMenu, FToolMenuEntry& InBlock, bool bAddSpaceAfterRaisedChildren);`
- L422 _private prototype_ `void PopulateToolBarBuilderWithEntry( FToolBarBuilder& ToolBarBuilder, UToolMenu* MenuData, FToolMenuSection& Section, FToolMenuEntry& Entry, bool bIsRaisingToTopLevel = false, bool bIsLastBlockOfLastSection = false );`
- L430 _private prototype_ `void PopulateToolBarBuilder(FToolBarBuilder& ToolBarBuilder, UToolMenu* MenuData);`
- L432 _private prototype_ `TSharedRef<SWidget> GenerateToolbarComboButtonMenu(TWeakObjectPtr<UToolMenu> InParent, const FName InBlockName);`
- L434 _private prototype_ `FOnGetContent ConvertWidgetChoice(const FNewToolMenuChoice& Choice, const FToolMenuContext& Context, const FToolMenuEntry& Block) const;`
- L437 _private prototype_ `static FUIAction ConvertUIAction(const FToolMenuEntry& Block, const FToolMenuContext& Context);` — Converts a string command to a FUIAction
- L438 _private prototype_ `static FUIAction ConvertUIAction(const FToolUIActionChoice& Choice, const FToolMenuContext& Context);`
- L439 _private prototype_ `static FUIAction ConvertUIAction(const FToolUIAction& Actions, const FToolMenuContext& Context);`
- L440 _private prototype_ `static FUIAction ConvertUIAction(const FToolDynamicUIAction& Actions, const FToolMenuContext& Context);`
- L441 _private prototype_ `static FUIAction ConvertScriptObjectToUIAction(UToolMenuEntryScript* ScriptObject, const FToolMenuContext& Context);`
- L443 _private prototype_ `static TAttribute<EVisibility> CalculateToolbarVisibility( UToolMenu* Menu, FToolMenuSection& Section, FToolMenuEntry& Entry, bool bIsRaisingToTopLevel, bool bEmbedActionOrCommand );`
- L451 _private prototype_ `static void ExecuteStringCommand(const FToolMenuStringCommand StringCommand, FName MenuName, const FToolMenuContext Context);`
- L453 _private prototype_ `void PopulateSubMenu(FMenuBuilder& Builder, TWeakObjectPtr<UToolMenu> InParent, const FToolMenuEntry InEntry, const FName InBlockName);`
- L454 _private prototype_ `void PopulateSubMenuWithoutName(FMenuBuilder& MenuBuilder, TWeakObjectPtr<UToolMenu> InParent, const FToolMenuEntry InEntry);`
- L455 _private prototype_ `TArray<UToolMenu*> CollectHierarchy(const FName Name, const TMap<FName, FName>& UnregisteredParentNames);`
- L458 _private prototype_ `void ApplyStyleToBuilder(FMenuBuilder& InBuilder, const FToolMenuEntryStyle& InStyle);` — Applies the style to the given Builder, as specified by the provided Style.
- L460 _private prototype_ `void ListAllParents(const FName Name, TArray<FName>& AllParents);`
- L462 _private prototype_ `void AssembleMenu(UToolMenu* GeneratedMenu, const UToolMenu* Other);`
- L463 _private prototype_ `void AssembleMenuSection(UToolMenu* GeneratedMenu, const UToolMenu* Other, FToolMenuSection* DestSection, const FToolMenuSection& OtherSection);`
- L465 _private prototype_ `void CopyMenuSettings(UToolMenu* GeneratedMenu, const UToolMenu* Other);`
- L467 _private prototype_ `void AddReferencedContextObjects(const TSharedRef<FMultiBox>& InMultiBox, const UToolMenu* InMenu);`
- L469 _private prototype_ `void ApplyCustomizationAndProfiles(UToolMenu* GeneratedMenu);`
- L470 _private prototype_ `void ApplyProfile(UToolMenu* GeneratedMenu, const FToolMenuProfile& Profile);`
- L471 _private prototype_ `void ApplyCustomization(UToolMenu* GeneratedMenu, const FCustomizedToolMenu& Profile);`
- L473 _private prototype_ `void UnregisterOwnerInternal(FToolMenuOwner Owner);`
- L475 _private prototype_ `bool GetDisplayUIExtensionPoints() const;`
- L477 _private prototype_ `static void ModifyEntryForEditDialog(FToolMenuEntry& Entry);`
- L479 _private prototype_ `UToolMenu* NewToolMenuObject(const FName NewBaseName, const FName InMenuName);`
- L484 _private member_ `TArray<FCustomizedToolMenu> CustomizedMenus;` — `UPROPERTY(EditAnywhere, Category = Misc)`
- L488 _private member_ `TMap<FName, FName> MenuSubstitutionsDuringGenerate;` — `UPROPERTY(EditAnywhere, Category = Misc)` — Allow substituting one menu for another during generate but not during find or extend
- L491 _private member_ `TMap<FName, TObjectPtr<UToolMenu>> Menus;` — `UPROPERTY()`
- L493 _private member_ `TMap<FName, TSharedPtr<FGeneratedToolMenuWidgets>> GeneratedMenuWidgets;`
- L495 _private member_ `TMap<TWeakPtr<FMultiBox>, TArray<TObjectPtr<const UObject>>> WidgetObjectReferences;`
- L497 _private member_ `TArray<FToolMenuOwner> OwnerStack;`
- L499 _private member_ `TMap<FName, FToolMenuExecuteString> StringCommandHandlers;`
- L502 _private member_ `TArray<FCustomizedToolMenu> RuntimeCustomizedMenus;` — Transient customizations made during runtime that will not be saved
- L505 _private member_ `TMap<FName , FToolMenuProfileMap> MenuProfiles;` — `UPROPERTY(EditAnywhere, Category = Misc)`
- L508 _private member_ `TMap<FName , FToolMenuProfileMap> RuntimeMenuProfiles;` — Transient profiles made during runtime that will not be saved
- L510 _private member_ `FSimpleDelegate SetTimerForNextTickDelegate;`
- L512 _private member_ `bool bNextTickTimerIsSet;`
- L513 _private member_ `bool bRefreshWidgetsNextTick;`
- L514 _private member_ `bool bCleanupStaleWidgetsNextTick;`
- L515 _private member_ `bool bCleanupStaleWidgetsNextTickGC;`
- L516 _private member_ `bool bEditMenusMode;`
- L517 _private member_ `bool bSuppressRefreshWidgetsRequests = false;`
- L519 _private member_ `static UToolMenus* Singleton;`
- L520 _private member_ `static bool bHasShutDown;`
- L521 _private member_ `static FSimpleMulticastDelegate StartupCallbacks;`
- L522 _private member_ `static TOptional<FDelegateHandle> InternalStartupCallbackHandle;`

#### struct `FToolMenuOwnerScoped`  
`struct FToolMenuOwnerScoped`  
_L531-548_
- desc: Sets the owner for all menus created until the end of the current scope (with support for nested scopes). Combines well with UToolMenus::UnregisterOwnerByName.
- L533 _public function_ `FToolMenuOwnerScoped(const FToolMenuOwner InOwner) : Owner(InOwner)`
- L538 _public function_ `~FToolMenuOwnerScoped()`
- L543 _public function_ `FToolMenuOwner GetOwner() const`
- L547 _private member_ `FToolMenuOwner Owner;`

#### class `UE::ToolMenus::FToolMenuTestInstanceScoped`  
`class FToolMenuTestInstanceScoped`  
_L557-566_
- desc: Creates a new instance of UToolMenus and sets the UToolMenus singleton to point at this new instance. When the scope instance is destructed, the previous UToolMenus singleton is reinstated.
- L560 _public prototype_ `FToolMenuTestInstanceScoped();`
- L561 _public prototype_ `~FToolMenuTestInstanceScoped();`
- L564 _private member_ `UToolMenus* PreviousInstance;`
- L565 _private member_ `UToolMenus* ScopedInstance;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API TOOLMENUS_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace ToolMenus` (scope `UE`)
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace ToolMenus` (scope `UE`)
- L284 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStringCommandExecuted, FName MenuName, FName TypeName);`
- L355 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FShouldDisplayExtensionPoints);` — Displaying extension points is for debugging menus
- L359 _delegate_ `DECLARE_DELEGATE_OneParam(FEditMenuDelegate, class UToolMenu*);` — Delegate that opens a menu editor
- L362 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FGenerateWidgetEvent, const FName InName, const FToolMenuContext& InMenuContext);`
- L550 _namespace_ `namespace UE`
- L550 _namespace_ `namespace ToolMenus` (scope `UE`)

### `Source/Developer/ToolMenus/Public/ToolMenusLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogToolMenus, Log, All);`
