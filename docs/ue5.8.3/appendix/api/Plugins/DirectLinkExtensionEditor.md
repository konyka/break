# Plugins / DirectLinkExtensionEditor

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor`
- headers: 7; symbols: 81
- symbol kinds: class=8, function=18, macro=2, member=15, namespace=12, prototype=26
- PrivateDependencyModuleNames: ContentBrowserData, EditorStyle, EditorWidgets, Engine, InputCore, MainFrame, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: ContentBrowser, Core, CoreUObject, DirectLink, DirectLinkExtension, ExternalSource

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Private/DirectLinkExtensionStyle.h` (Private)


#### class `UE::DatasmithImporter::FDirectLinkExtensionStyle`  
`class FDirectLinkExtensionStyle`  
_L14-29_
- L17 _public prototype_ `static void Initialize();`
- L19 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static const ISlateStyle& Get();`
- L23 _public prototype_ `static FName GetStyleSetName();`
- L25 _private prototype_ `static FString InContent(const FString& RelativePath, const TCHAR* Extension);`
- L28 _private member_ `static TUniquePtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Private/DirectLinkExtensionUI.h` (Private)


#### class `UE::DatasmithImporter::FDirectLinkExtensionUI`  
`class FDirectLinkExtensionUI`  
_L18-65_
- L21 _public function_ `FDirectLinkExtensionUI()`
- L34 _public function_ `~FDirectLinkExtensionUI()`
- L49 _private function_ `TSharedRef<SWidget> OnGenerateAssetViewLockStateIcons(const FAssetData& AssetData)`
- L55 _private function_ `TSharedRef<SWidget> OnGenerateAssetViewLockStateTooltip(const FAssetData& AssetData)`
- L62 _private member_ `FDelegateHandle AssetViewExtraStateGeneratorHandle;` — Delegate handle for asset direct link connection state indicator extensions.
- L64 _private member_ `TWeakPtr<SWindow> DirectLinkWindow;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "DirectLinkExtensionUI"`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Private/DirectLinkUriResolverInEditor.h` (Private)


#### class `UE::DatasmithImporter::FDirectLinkUriResolverInEditor`  
`class FDirectLinkUriResolverInEditor : public FDirectLinkUriResolver`  
_L12-21_
- inherits: `FDirectLinkUriResolver`
- L16 _public function_ `virtual TSharedPtr<FExternalSource> BrowseExternalSource(const FSourceUri& DefaultSourceUri) const override` — IUriResolver interface begin

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Private/SDirectLinkAssetThumbnailIndicator.h` (Private)


#### class `UE::DatasmithImporter::SDirectLinkAssetThumbnailIndicator`  
`class SDirectLinkAssetThumbnailIndicator : public SCompoundWidget`  
_L17-47_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDirectLinkAssetThumbnailIndicator)`
- L21 _public prototype_ `SLATE_ARGUMENT(FAssetData, AssetData) SLATE_END_ARGS();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs);`
- L26 _public prototype_ `virtual ~SDirectLinkAssetThumbnailIndicator();`
- L29 _private prototype_ `EVisibility GetVisibility() const;`
- L31 _private prototype_ `const FSlateBrush* GetImageBrush() const;`
- L33 _private prototype_ `void OnObjectPropertyChanged(UObject* ModifiedObject, struct FPropertyChangedEvent&);`
- L35 _private prototype_ `static void CacheBrushes();`
- L38 _private member_ `static const FSlateBrush* NotAvailableBrush;` — Brushes used to render DirectLink icons.
- L39 _private member_ `static const FSlateBrush* OutOfSyncBrush;`
- L40 _private member_ `static const FSlateBrush* UpToDateBrush;`
- L41 _private member_ `static const FSlateBrush* AutoReimportBrush;`
- L44 _private member_ `FAssetData AssetData;` — Asset path for this indicator widget.
- L46 _private member_ `FDelegateHandle ObjectPropertyChangedHandle;`

#### class `UE::DatasmithImporter::SDirectLinkAssetThumbnailTooltip`  
`class SDirectLinkAssetThumbnailTooltip : public SCompoundWidget`  
_L49-68_
- inherits: `SCompoundWidget`
- L52 _public function_ `SLATE_BEGIN_ARGS(SDirectLinkAssetThumbnailTooltip)`
- L53 _public prototype_ `SLATE_ARGUMENT(FAssetData, AssetData) SLATE_END_ARGS();`
- L60 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget. @param InArgs Slate arguments
- L63 _private prototype_ `EVisibility GetTooltipVisibility() const;`
- L65 _private prototype_ `FText GetTooltipText() const;`
- L67 _private member_ `mutable FAssetData AssetData;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Private/SDirectLinkAvailableSource.h` (Private)


#### class `UE::DatasmithImporter::SDirectLinkAvailableSource`  
`class SDirectLinkAvailableSource : public SCompoundWidget`  
_L18-93_
- inherits: `SCompoundWidget`
- desc: Dialog used to make a selection of one available FDirectLinkExternalSource.
- L22 _public function_ `SLATE_BEGIN_ARGS(SDirectLinkAvailableSource)`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_ARGUMENT(FText, ProceedButtonLabel) SLATE_ARGUMENT(FText, ProceedButtonTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `virtual ~SDirectLinkAvailableSource() = default;`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L45 _public function_ `bool GetShouldProceed() const`
- L47 _public function_ `TSharedPtr<FDirectLinkExternalSource> GetSelectedSource() const`
- L51 _private prototype_ `void GenerateDirectLinkExternalSourceInfos();`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedRef<struct FDirectLinkExternalSourceInfo> Item, const TSharedRef<STableViewBase>& Owner) const;`
- L55 _private prototype_ `void OnSelectionChanged(TSharedPtr<struct FDirectLinkExternalSourceInfo>, ESelectInfo::Type);`
- L57 _private function_ `FReply OnCancel()`
- L67 _private function_ `FReply OnProceed()`
- L78 _private prototype_ `float GetNoConnectionHintFillHeight() const;`
- L80 _private prototype_ `::EVisibility GetNoConnectionHintVisibility() const;`
- L82 _private prototype_ `::EVisibility GetConnectionViewVisibility() const;`
- L84 _private member_ `bool bShouldProceed = false;`
- L86 _private member_ `TWeakPtr< SWindow > Window;`
- L88 _private member_ `TSharedPtr<FDirectLinkExternalSource> SelectedSource;`
- L90 _private member_ `TSharedPtr<SListView<TSharedRef<struct FDirectLinkExternalSourceInfo>>> SourceListView;`
- L92 _private member_ `TArray<TSharedRef<struct FDirectLinkExternalSourceInfo>> DirectLinkExternalSourceInfos;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Public/DirectLinkExtensionEditorModule.h` (Public)


#### class `IDirectLinkExtensionEditorModule`  
`class IDirectLinkExtensionEditorModule : public IDirectLinkExtensionModule`  
_L14-53_
- inherits: `IDirectLinkExtensionModule`
- L22 _public function_ `static inline IDirectLinkExtensionEditorModule& Get()` — Singleton-like access to IDirectLinkExtensionEditorModule @return Returns IDirectLinkExtensionEditorModule singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. @return True if the module is loaded and ready to use
- L37 _public function_ `virtual void OverwriteUriResolver(const TSharedRef<UE::DatasmithImporter::IUriResolver>& UriResolver)`
- L42 _public function_ `virtual UE::DatasmithImporter::IDirectLinkManager& GetManager() const override`
- L52 _public prototype_ `virtual TSharedPtr<UE::DatasmithImporter::FDirectLinkExternalSource> DisplayDirectLinkSourcesDialog() = 0;` — Spawn a dialog window prompting the user to select one available FDirectLinkExternalSource. The list of displayed DirectLink source can be filtered. @return The selected DirectLinkExternalSource, nullptr is returned if the dialog was canceled.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L12 _macro_ `#define DIRECTLINKEXTENSIONEDITOR_MODULE_NAME TEXT("DirectLinkExtensionEditor")`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtensionEditor/Public/DirectLinkSourceSearchFilter.h` (Public)


#### class `UDirectLinkSourceSearchFilter`  
`class UDirectLinkSourceSearchFilter : public UContentBrowserFrontEndFilterExtension`  
_L18-26_
- reflection: `UCLASS()`
- inherits: `UContentBrowserFrontEndFilterExtension`
- desc: Content Browser filter used to isolate assets imported via a Direct Link source.
- L24 _public prototype_ `virtual void AddFrontEndFilterExtensions(TSharedPtr<FFrontendFilterCategory> DefaultCategory, TArray< TSharedRef<FFrontendFilter> >& InOutFilterList) const override;` — UContentBrowserFrontEndFilterExtension interface
