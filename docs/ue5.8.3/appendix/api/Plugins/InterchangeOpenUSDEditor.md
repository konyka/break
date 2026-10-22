# Plugins / InterchangeOpenUSDEditor

- module root: `Plugins/Interchange/Extensions/OpenUSD/Source/Editor`
- headers: 4; symbols: 32
- symbol kinds: class=4, function=1, macro=1, member=8, prototype=18
- PrivateDependencyModuleNames: InputCore, InterchangeEditor, InterchangeEngine, InterchangeOpenUSDImport, Slate, SlateCore, USDClasses, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Interchange/Extensions/OpenUSD/Source/Editor/Private/InterchangeUsdHandlerOrderWindow.h` (Private)


#### class `SInterchangeUsdHandlerOrderWindow`  
`class SInterchangeUsdHandlerOrderWindow : public SCompoundWidget`  
_L15-45_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SInterchangeUsdHandlerOrderWindow)`
- L24 _public prototype_ `static bool ShowWindow(UInterchangeUsdTranslatorSettings* Settings);`
- L26 _public prototype_ `void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `TSharedRef<ITableRow> OnGenerateListRow(TSharedPtr<FSchemaHandlerEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L29 _public prototype_ `FReply OnAccept();`
- L30 _public prototype_ `FReply OnCancel();`
- L31 _public prototype_ `FReply OnReset();`
- L32 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L34 _public prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, TSharedPtr<FSchemaHandlerEntry> Item);`
- L35 _public prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& Event, EItemDropZone Zone, TSharedPtr<FSchemaHandlerEntry> Item);`
- L36 _public prototype_ `FReply OnRowDragDetected(const FGeometry& Geometry, const FPointerEvent& PointerEvent);`
- L37 _public prototype_ `void OnRowDragLeave(const FDragDropEvent& Event);`
- L40 _private member_ `bool bNeedNewTranslation = false;`
- L41 _private member_ `UInterchangeUsdTranslatorSettings* Settings;`
- L42 _private member_ `TArray<TSharedPtr<FSchemaHandlerEntry>> Entries;`
- L43 _private member_ `TWeakPtr<SWindow> WeakWindow;`
- L44 _private member_ `TSharedPtr<SListView<TSharedPtr<FSchemaHandlerEntry>>> ListView;`

### `Plugins/Interchange/Extensions/OpenUSD/Source/Editor/Private/InterchangeUsdTranslatorSettingsCustomization.h` (Private)


#### class `FInterchangeUsdTranslatorSettingsCustomization`  
`class FInterchangeUsdTranslatorSettingsCustomization : public IDetailCustomization`  
_L13-30_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `FInterchangeUsdTranslatorSettingsCustomization();`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L21 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L25 _private member_ `UInterchangeUsdTranslatorSettings* CurrentOptions;`
- L27 _private member_ `TArray<TSharedPtr<FString>> RenderContextComboBoxItems;`
- L29 _private member_ `TArray<TSharedPtr<FString>> MaterialPurposeComboBoxItems;`

### `Plugins/Interchange/Extensions/OpenUSD/Source/Editor/Public/InterchangeOpenUSDEditorModule.h` (Public)


#### class `FInterchangeOpenUSDEditorModule`  
`class FInterchangeOpenUSDEditorModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Interchange/Extensions/OpenUSD/Source/Editor/Public/InterchangeUsdTranslatorBlueprintLibrary.h` (Public)


#### class `UInterchangeUsdTranslatorBlueprintLibrary`  
`class UInterchangeUsdTranslatorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L15-29_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "InterchangeUsdTranslatorLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L28 _public prototype_ `static TArray<FSchemaHandlerEntry> GetDefaultSchemaHandlerEntries();` — `UFUNCTION(BlueprintCallable, Category = "USD Translator")` — Returns the default list of schema handlers entries registered via C++, i.e. FSchemaHandlerRegistry::RegisteredHandlerEntries. The main use case here is to retrieve this list, modify it as needed, and to set it as the CustomHandlerEntries property on the UInterchangeUsdTranslatorSettings class default object, which will be used by any Interchange USD translations after that point

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEOPENUSDEDITOR_API`
