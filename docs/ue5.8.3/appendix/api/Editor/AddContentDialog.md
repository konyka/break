# Editor / AddContentDialog

- module root: `Source/Editor/AddContentDialog`
- headers: 12; symbols: 255
- symbol kinds: class=15, delegate=5, enum=2, enumerator=9, function=22, macro=1, member=78, prototype=118, struct=4, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, DirectoryWatcher, EditorFramework, Engine, ImageWrapper, InputCore, Json, PakFile, Slate, SlateCore, ToolWidgets, UnrealEd, WidgetCarousel
- PrivateIncludePathModuleNames: AssetTools, ContentBrowser

### `Source/Editor/AddContentDialog/Private/ContentSourceDragDropOp.h` (Private)


#### class `FContentSourceDragDropOp`  
`class FContentSourceDragDropOp : public FDecoratedDragDropOp`  
_L14-34_
- inherits: `FDecoratedDragDropOp`
- desc: A drag drop operation for dragging and dropping FContentSourceViewModels.
- L17 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FContentSourceDragDropOp, FDecoratedDragDropOp) static TSharedRef<FContentSourceDragDropOp> CreateShared(TSharedPtr<FContentSourceViewModel> InContentSource);`
- L23 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L26 _public prototype_ `TSharedPtr<FContentSourceViewModel> GetContentSource();` — Gets the view model for the content source being dragged and dropped.
- L29 _private prototype_ `FContentSourceDragDropOp(TSharedPtr<FContentSourceViewModel> InContentSource);`
- L33 _private member_ `TSharedPtr<FContentSourceViewModel> ContentSource;` — The view model for the content source being dragged and dropped.

### `Source/Editor/AddContentDialog/Private/ContentSourceProviderManager.h` (Private)


#### class `FContentSourceProviderManager`  
`class FContentSourceProviderManager`  
_L11-23_
- desc: Provides methods for registering and getting registered content source providers.
- L15 _public prototype_ `void RegisterContentSourceProvider(TSharedRef<IContentSourceProvider> ContentSourceProvider);` — Registers a content source provider.
- L18 _public prototype_ `const TArray<TSharedRef<IContentSourceProvider>>* GetContentSourceProviders();` — Gets and array of the currently registered content source providers.
- L22 _private member_ `TArray<TSharedRef<IContentSourceProvider>> ContentSourceProviders;` — The registered content source providers.

### `Source/Editor/AddContentDialog/Private/ContentSourceProviders/FeaturePack/FeaturePackContentSourceProvider.h` (Private)


#### class `FFeaturePackContentSourceProvider`  
`class FFeaturePackContentSourceProvider : public IContentSourceProvider`  
_L15-66_
- inherits: `IContentSourceProvider`
- desc: A content source provider for available content upacks.
- L18 _public prototype_ `FFeaturePackContentSourceProvider();`
- L19 _public prototype_ `virtual const TArray<TSharedRef<IContentSource>>& GetContentSources() const override;`
- L20 _public prototype_ `virtual void SetContentSourcesChanged(FOnContentSourcesChanged OnContentSourcesChangedIn) override;`
- L22 _public prototype_ `virtual ~FFeaturePackContentSourceProvider();`
- L26 _private prototype_ `void StartUpDirectoryWatcher();` — Starts the directory watcher for the feature pack directory.
- L29 _private prototype_ `void ShutDownDirectoryWatcher();` — Shuts down the directory watcher for the feature pack directory.
- L32 _private prototype_ `void OnFeaturePackDirectoryChanged( const TArray<FFileChangeData>& FileChanges );` — Delegate to handle whenever the feature pack directory changes on disk.
- L35 _private prototype_ `void RefreshFeaturePacks();` — Rebuilds the feature pack array and calls the change notification delegate.
- L38 _private member_ `FString FeaturePackPath;` — The path on disk to the directory containing the feature packs.
- L41 _private member_ `FString EnterpriseFeaturePackPath;` — The path on disk to the directory containing the enterprise feature packs.
- L44 _private member_ `FString TemplatePath;` — The path on disk to the directory containing the templates folder.
- L47 _private member_ `FString EnterpriseTemplatePath;` — The path on disk to the directory containing the enterprise templates folder.
- L51 _private member_ `IDirectoryWatcher::FDirectoryChanged DirectoryChangedDelegate;` — The delegate which gets called when the feature pack directory changes. This reference is kept so that it can be unregistered correctly.
- L54 _private member_ `FOnContentSourcesChanged OnContentSourcesChanged;` — A delegate which gets called whenever the array of content sources changes.
- L57 _private member_ `TArray<TSharedRef<IContentSource>> ContentSources;` — An array of the available content sources.
- L60 _private member_ `TArray<TSharedRef<IContentSource>> EnterpiseContentSources;` — An array of the available Enterprise content sources.
- L63 _private member_ `mutable bool bAreContentSourcesUpToDate = false;` — Are the cached content sources up to date
- L65 _private member_ `FDelegateHandle DirectoryChangedDelegateHandle;`

### `Source/Editor/AddContentDialog/Private/IContentSource.h` (Private)


#### enum `EContentSourceCategory`  
`enum class EContentSourceCategory:uint8`  
_L11-20_
- reflection: `UENUM()`
- desc: Defines categories for content sources.
- L13 _public enumerator_ `BlueprintFeature`
- L14 _public enumerator_ `CodeFeature`
- L15 _public enumerator_ `EnterpriseFeature`
- L16 _public enumerator_ `Content`
- L17 _public enumerator_ `EnterpriseContent`
- L18 _public enumerator_ `SharedPack`
- L19 _public enumerator_ `Unknown`

#### class `FImageData`  
`class FImageData`  
_L24-51_
- desc: Represents raw binary image data in png format.
- L30 _public function_ `FImageData(FString InName, TSharedPtr <TArray<uint8>> InData)` — Creates a new FImageData @param InName - The name which identifies the image represented by this object @param InData - The raw binary image data in png format
- L37 _public function_ `const FString GetName() const` — Gets the name which identifies the image represented by this object.
- L43 _public function_ `const TSharedPtr<TArray<uint8>>& GetData() const` — Gets the raw binary image data in PNG format.
- L49 _private member_ `FString Name;`
- L50 _private member_ `TSharedPtr<TArray<uint8>> Data;`

#### class `FLocalizedText`  
`class FLocalizedText`  
_L54-85_
- desc: Represents a pieces of localized text.
- L57 _public function_ `FLocalizedText()`
- L64 _public function_ `FLocalizedText(FString InTwoLetterLanguage, FText InText)` — Creates a new FLocalizedText @param InTwoLetterLanguage - The iso 2-letter language specifier. @param InText - The text in the language specified
- L71 _public function_ `const FString& GetTwoLetterLanguage() const` — Gets the iso 2-letter language specifier for this text.
- L77 _public function_ `FText GetText() const` — Gets the text in the language specified.
- L83 _private member_ `FString TwoLetterLanguage;`
- L84 _private member_ `FText Text;`

#### class `IContentSource`  
`class IContentSource`  
_L88-127_
- desc: Defines a source of content to be used with the FAddContentDialog
- L91 _public prototype_ `virtual ~IContentSource() = default;`
- L94 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedNames() const = 0;` — Gets the name of the content source as an array of localized strings.
- L97 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedDescriptions() const = 0;` — Gets the description of the content source as an array or localized strings.
- L100 _public prototype_ `virtual const TArray<EContentSourceCategory>& GetCategories() const = 0;` — Gets the category for the content source.
- L103 _public prototype_ `virtual TSharedPtr<FImageData> GetIconData() const = 0;` — Gets the image data for the icon which should represent the content source in the UI.
- L106 _public prototype_ `virtual const TArray<TSharedPtr<FImageData>>& GetScreenshotData() const = 0;` — Gets an array or image data for screenshots for the content source.
- L109 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedAssetTypes() const = 0;` — Gets the asset types used in this pack.
- L112 _public prototype_ `virtual const FString& GetClassTypesUsed() const = 0;` — Gets the class types used in this pack.
- L115 _public prototype_ `virtual const FString& GetSortKey() const = 0;` — Gets the category for the content source.
- L120 _public prototype_ `virtual bool InstallToProject(FString InstallPath) = 0;` — Installs the content in the content source to the specific path. @returns true if install succeeded
- L123 _public prototype_ `virtual bool IsDataValid() const = 0;` — Is the data in this content valid.
- L126 _public prototype_ `virtual const FString& GetIdent() const = 0;` — Gets the identity of the content.

### `Source/Editor/AddContentDialog/Private/IContentSourceProvider.h` (Private)


#### class `IContentSourceProvider`  
`class IContentSourceProvider`  
_L9-22_
- desc: Defines methods for an object which provides IContentSource objects for use with the SAddContentDialog.
- L12 _public prototype_ `DECLARE_DELEGATE(FOnContentSourcesChanged);`
- L16 _public prototype_ `virtual const TArray<TSharedRef<IContentSource>>& GetContentSources() const = 0;` — Gets the available content sources.
- L19 _public prototype_ `virtual void SetContentSourcesChanged(FOnContentSourcesChanged OnContentSourcesChangedIn) = 0;` — Sets the delegate which will be executed when the avaialble content sources change
- L21 _public prototype_ `virtual ~IContentSourceProvider() = default;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE(FOnContentSourcesChanged);`

### `Source/Editor/AddContentDialog/Private/SAddContentDialog.h` (Private)


#### class `SAddContentDialog`  
`class SAddContentDialog : public SWindow`  
_L9-22_
- inherits: `SWindow`
- desc: A window which allows the user to select additional content to add to the currently loaded project.
- L12 _public function_ `SLATE_BEGIN_ARGS(SWindow)`
- L17 _public prototype_ `~SAddContentDialog();`
- L19 _public prototype_ `void Construct(const FArguments& InArgs);`

### `Source/Editor/AddContentDialog/Private/SAddContentWidget.h` (Private)


#### class `SAddContentWidget`  
`class SAddContentWidget : public SCompoundWidget`  
_L33-114_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to select multiple options from content which is available to be added to the project.
- L36 _public prototype_ `DECLARE_DELEGATE(FOnAddListChanged);`
- L38 _public function_ `SLATE_BEGIN_ARGS(SAddContentWidget)`
- L43 _public prototype_ `~SAddContentWidget();`
- L45 _public prototype_ `void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `const TArray<TSharedPtr<IContentSource>>* GetContentSourcesToAdd();` — Gets the content sources which have been selected by the user for addition to the project
- L52 _private prototype_ `TSharedRef<SWidget> CreateCategoryTabs();` — Creates a strip of tabs which display and allow selecting categories.
- L55 _private prototype_ `TSharedRef<SWidget> CreateContentSourceTileView();` — Creates a tile view which displays the content sources in the selected category.
- L58 _private prototype_ `TSharedRef<ITableRow> CreateContentSourceIconTile(TSharedPtr<FContentSourceViewModel> ContentSource, const TSharedRef<STableViewBase>& OwnerTable);` — Creates the widget which represents each content source in the content source tile view.
- L61 _private prototype_ `TSharedRef<SWidget> CreateContentSourceDetail(TSharedPtr<FContentSourceViewModel> ContentSource);` — Creates a widget representing detailed information about a single content source.
- L64 _private prototype_ `TSharedRef<SWidget> CreateScreenshotCarousel(TSharedPtr<FContentSourceViewModel> ContentSource);` — Creates a widget carousel for displaying the set of screenshots for a specific content source.
- L67 _private prototype_ `TSharedRef<SWidget> CreateScreenshotWidget(TSharedPtr<FSlateBrush> ScreenshotBrush);` — Creates the widget the displays a screenshot in the screenshot carousel.
- L70 _private prototype_ `void SearchTextChanged(const FText& SearchText);` — Handles the text in the search box changing.
- L73 _private prototype_ `void ContentSourceTileViewSelectionChanged(TSharedPtr<FContentSourceViewModel> SelectedContentSource, ESelectInfo::Type SelectInfo);` — Handles the selection in the content source tile view changing
- L76 _private prototype_ `FReply AddButtonClicked();` — Handles the add content to project button being clicked.
- L79 _private prototype_ `FReply CancelButtonClicked();` — Handles the close button being clicked.
- L82 _private prototype_ `void OnSelectedCategoryChanged(FCategoryViewModel SelectedCategory);` — Handles selected category changing in the UI
- L85 _private prototype_ `FCategoryViewModel GetSelectedCategory() const;` — Gets the curerently selected category
- L88 _private prototype_ `void CategoriesChanged();` — Handles the available categories changing on the view model.
- L91 _private prototype_ `void ContentSourcesChanged();` — Handles the available content sources changing on the view model.
- L94 _private prototype_ `void SelectedContentSourceChanged();` — Handles the selected content source changing on the view model.
- L98 _private member_ `TSharedPtr<FAddContentWidgetViewModel> ViewModel;` — The view model which represents the current data of the UI.
- L101 _private member_ `TSharedPtr<STileView<TSharedPtr<FContentSourceViewModel>>> ContentSourceTileView;` — The tile view which displays the content sources in the currently selected category.
- L104 _private member_ `TSharedPtr<SBox> CategoryTabsContainer;` — The placeholder widget which holds the category tab strip.
- L107 _private member_ `TSharedPtr<SBox> ContentSourceDetailContainer;` — The placeholder widget which holds the detail view for the currently selected content source.
- L110 _private member_ `TArray<TSharedPtr<IContentSource>> ContentSourcesToAdd;` — The content sources which the user has selected for addition to the project.
- L113 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — The search box

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_DELEGATE(FOnAddListChanged);`

### `Source/Editor/AddContentDialog/Private/ViewModels/AddContentWidgetViewModel.h` (Private)


#### class `FAddContentWidgetViewModel`  
`class FAddContentWidgetViewModel : public TSharedFromThis<FAddContentWidgetViewModel>`  
_L18-120_
- inherits: `TSharedFromThis<FAddContentWidgetViewModel>`
- desc: The view model for the SAddContentWidget.
- L22 _public prototype_ `DECLARE_DELEGATE(FOnContentSourcesChanged);`
- L23 _public prototype_ `DECLARE_DELEGATE(FOnSelectedContentSourceChanged);`
- L25 _public typedef_ `typedef TTextFilter<TSharedPtr<FContentSourceViewModel>> ContentSourceTextFilter;`
- L28 _public prototype_ `static TSharedRef<FAddContentWidgetViewModel> CreateShared();` — Creates a shared reference to a new view model.
- L31 _public prototype_ `const TArray<FCategoryViewModel>& GetCategories() const;` — Gets the view models for the current set of content source categories.
- L34 _public prototype_ `void SetOnCategoriesChanged(FOnCategoriesChanged OnCategoriesChangedIn);` — Sets the delegate which should be executed when the set of categories changes.
- L38 _public prototype_ `FCategoryViewModel GetSelectedCategory();` — Gets the view model for the currently selected category.  Only content sources which match the selected category will be returned by GetContentSources().
- L42 _public prototype_ `void SetSelectedCategory(FCategoryViewModel SelectedCategoryIn);` — Sets the currently selected category view model. Only content sources which match the selected category will be returned by GetContentSources().
- L45 _public prototype_ `void SetSearchText(FText SearchTextIn);` — Sets search text which should be used to filter the content sources.
- L48 _public prototype_ `FText GetSearchErrorText() const;` — Get any error information that was reported the last time SetSearchText was called.
- L52 _public prototype_ `const TArray<TSharedPtr<FContentSourceViewModel>>* GetContentSources();` — Gets a filtered array of content sources which match both the selected category and the search text if it has been set.
- L56 _public prototype_ `void SetOnContentSourcesChanged(FOnContentSourcesChanged OnContentSourcesChangedIn);` — Sets the delegate which should be executed when the current set of content sources returned by GetContentSources changes.
- L59 _public prototype_ `TSharedPtr<FContentSourceViewModel> GetSelectedContentSource();` — Gets the currently selected content source.
- L62 _public prototype_ `void SetSelectedContentSource(TSharedPtr<FContentSourceViewModel> SelectedContentSourceIn);` — Sets the currently selected content source.
- L65 _public prototype_ `void SetOnSelectedContentSourceChanged(FOnSelectedContentSourceChanged OnSelectedContentSourceChangedIn);` — Sets the delegate which should be executed when the selected content source changes.
- L68 _private prototype_ `FAddContentWidgetViewModel();`
- L69 _private prototype_ `void Initialize();`
- L72 _private prototype_ `void BuildContentSourceViewModels();` — Builds view models for all available content sources.
- L76 _private prototype_ `void UpdateFilteredContentSourcesAndSelection(bool bAllowEmptySelection);` — Filters the current set of content sources based on the selected category and the search text, and updates the selection. @param bAllowEmptySelection Determines whether or not to select the first available item after filtering if the selected item is null, or not in the filtered set.
- L79 _private prototype_ `void TransformContentSourceToStrings(TSharedPtr<FContentSourceViewModel> Item, OUT TArray< FString >& Array);` — Converts a content source item to an array of strings for processing by the TTextFilter.
- L82 _private prototype_ `void ContentSourcesChanged();` — Handles notification from the content source providers when their content source arrays change.
- L86 _private member_ `TArray<TSharedPtr<IContentSourceProvider>> ContentSourceProviders;` — The array of content source providers who's content sources are being displayed.
- L89 _private member_ `TArray<FCategoryViewModel> Categories;` — The view models for the available categories.
- L92 _private member_ `TArray<TSharedPtr<FContentSourceViewModel>> ContentSourceViewModels;` — A combined array of all content sources from all content source providers.
- L95 _private member_ `TArray<TSharedPtr<FContentSourceViewModel>> FilteredContentSourceViewModels;` — A filtered array of content sources based on the currently selected category and the search text.
- L98 _private member_ `TMap<FCategoryViewModel, TSharedPtr<FContentSourceViewModel>> CategoryToSelectedContentSourceMap;` — A map which keeps track of the currently selected content source for each category.
- L101 _private member_ `FCategoryViewModel SelectedCategory;` — The view model for the currently selected category.
- L104 _private member_ `FText SearchText;` — The current search text.
- L107 _private member_ `bool bBuildingContentSourceViewModels = false;` — True while building context source view models.
- L110 _private member_ `FOnCategoriesChanged OnCategoriesChanged;` — The delegate which is executed when the available categories change.
- L113 _private member_ `FOnContentSourcesChanged OnContentSourcesChanged;` — The delegate which is executed when the filtered content sources change.
- L116 _private member_ `FOnSelectedContentSourceChanged OnSelectedContentSourceChanged;` — The delegate which is executed when the currently selected content source changes.
- L119 _private member_ `TSharedPtr<ContentSourceTextFilter> ContentSourceFilter;` — The filter which is used to filter the content sources based on the search text.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE(FOnCategoriesChanged) DECLARE_DELEGATE(FOnContentSourcesChanged);`
- L22 _delegate_ `DECLARE_DELEGATE(FOnContentSourcesChanged);`
- L23 _delegate_ `DECLARE_DELEGATE(FOnSelectedContentSourceChanged);`

### `Source/Editor/AddContentDialog/Private/ViewModels/CategoryViewModel.h` (Private)


#### class `FCategoryViewModel`  
`class FCategoryViewModel`  
_L12-41_
- desc: A view model for displaying a content source category in the UI.
- L15 _public prototype_ `FCategoryViewModel();`
- L17 _public prototype_ `FCategoryViewModel(EContentSourceCategory InCategory);`
- L20 _public function_ `const FText& GetText() const` — Gets the display name of the category.
- L22 _public function_ `inline bool operator==(const FCategoryViewModel& Other) const`
- L27 _public function_ `bool operator<(FCategoryViewModel const& Other) const`
- L32 _public function_ `uint32 GetTypeHash() const`
- L35 _private prototype_ `void Initialize();`
- L38 _private member_ `EContentSourceCategory Category;`
- L39 _private member_ `FText Text;`
- L40 _private member_ `int SortID;`

#### Free symbols / members of external scopes

- L43 _function_ `inline uint32 GetTypeHash(const FCategoryViewModel& CategoryViewModel)`

### `Source/Editor/AddContentDialog/Private/ViewModels/ContentSourceViewModel.h` (Private)


#### class `FContentSourceViewModel`  
`class FContentSourceViewModel : public TSharedFromThis<FContentSourceViewModel>`  
_L19-91_
- inherits: `TSharedFromThis<FContentSourceViewModel>`
- desc: A view model for displaying and interacting with an IContentSource in the FAddContentDialog.
- L23 _public prototype_ `FContentSourceViewModel(TSharedPtr<IContentSource> ContentSourceIn);` — Creates a view model for a supplied content source.
- L26 _public prototype_ `const TSharedPtr<IContentSource>& GetContentSource() const;` — Gets the content source represented by this view model.
- L29 _public prototype_ `const FText& GetName() const;` — Gets the display name for this content source.
- L32 _public prototype_ `const FText& GetDescription() const;` — Gets the description of this content source.
- L35 _public prototype_ `const FText& GetAssetTypes() const;` — Gets the asset types used in this content source.
- L38 _public prototype_ `FStringView GetClassTypes() const;` — Gets the class types used in this content source.
- L41 _public prototype_ `const TArray<FCategoryViewModel>& GetCategories() const;` — Gets the view models for the categories for this content source.
- L44 _public prototype_ `const TSharedPtr<FSlateBrush>& GetIconBrush() const;` — Gets the brush which should be used to draw the icon representation of this content source.
- L47 _public prototype_ `const TArray<TSharedPtr<FSlateBrush>>& GetScreenshotBrushes() const;` — Gets an array or brushes which should be used to display screenshots for this content source.
- L51 _private prototype_ `void SetupBrushes();` — Sets up brushes from the images data supplied by the IContentSource.
- L54 _private prototype_ `TSharedPtr<FSlateDynamicImageBrush> CreateBrushFromRawData(const FString& ResourceNamePrefix, const TArray<uint8>& RawData) const;` — Creates a slate brush from raw binary PNG formatted image data and the supplied prefix.
- L57 _private prototype_ `FText ChooseLocalizedText(const TArray<FLocalizedText>& Choices, const FString& InCurrentLanguage) const;` — Selects the text from an array which matches the given language.
- L67 _private member_ `TSharedPtr<IContentSource> ContentSource;` — The content source represented by this view model.
- L70 _private member_ `TSharedPtr<FSlateBrush> IconBrush;` — The brush which should be used to draw the icon representation of this content source.
- L73 _private member_ `TArray<TSharedPtr<FSlateBrush>> ScreenshotBrushes;` — An array or brushes which should be used to display screenshots for this content source.
- L76 _private member_ `TArray<FCategoryViewModel> Categories;` — The view models for the categories for this content source.
- L79 _private member_ `mutable FCachedContentText CachedNameText;` — The information used/returned the last time the name of the content source was requested.
- L82 _private member_ `mutable FCachedContentText CachedDescriptionText;` — The information used/returned the last time the description of the content source was requested.
- L85 _private member_ `mutable FCachedContentText CachedAssetTypeText;` — The information used/returned the last time the asset types of the content source was requested.
- L90 _private member_ `static uint32 ImageID;` — Keeps track of a unique increasing id which is appended to each brush name.  This avoids an issue where two brushes are created with the same name, and then both brushes texture data gets deleted when either brush is destructed.

#### struct `FContentSourceViewModel::FCachedContentText`  
`struct FCachedContentText`  
_L60-64_
- L62 _public member_ `FString Language;`
- L63 _public member_ `FText Text;`

### `Source/Editor/AddContentDialog/Public/FeaturePackContentSource.h` (Public)


#### struct `FPackData`  
`struct FPackData`  
_L26-32_
- L28 _public member_ `FString PackSource;`
- L29 _public member_ `FString PackName;`
- L30 _public member_ `FString PackMap;`
- L31 _public member_ `TArray<UObject*> ImportedObjects;`

#### class `FLocalizedTextArray`  
`class FLocalizedTextArray`  
_L34-70_
- L37 _public function_ `FLocalizedTextArray()`
- L44 _public function_ `FLocalizedTextArray(FString InTwoLetterLanguage, FString InText)` — Creates a new FLocalizedText @param InTwoLetterLanguage - The iso 2-letter language specifier. @param InText - The text in the language specified
- L56 _public function_ `const FString& GetTwoLetterLanguage() const` — Gets the iso 2-letter language specifier for this text.
- L62 _public function_ `const TArray<FText>& GetTags() const` — Gets the array of tags in the language specified.
- L68 _private member_ `FString TwoLetterLanguage;`
- L69 _private member_ `TArray<FText> Tags;`

#### enum `EFeaturePackDetailLevel`  
`enum class EFeaturePackDetailLevel :uint8`  
_L75-79_
- reflection: `UENUM()`
- desc: Defines categories for shared template resource levels.
- L77 _public enumerator_ `Standard`
- L78 _public enumerator_ `High`

#### struct `FFeaturePackLevelSet`  
`struct FFeaturePackLevelSet`  
_L83-124_
- reflection: `USTRUCT()`
- desc: Structure that defines a shared feature pack resource.
- L87 _public function_ `FFeaturePackLevelSet()`
- L92 _public function_ `FFeaturePackLevelSet(FString InMountName, TArray<EFeaturePackDetailLevel> InDetailLevels)` — Creates a new FFeaturePackLevelSet @param InMountName - Name of the pack/folder to insert to @param InDetailLevels - The levels available for this pack
- L100 _public member_ `TArray<EFeaturePackDetailLevel> DetailLevels;` — `UPROPERTY()` — List of shared resource levels for this shared resource.
- L104 _public member_ `FString MountName;` — `UPROPERTY()` — Mount name for the shared resource - this is the folder the resource will be copied to on project generation as well as the name of the folder that will appear in the content browser.
- L106 _public function_ `FString GetFeaturePackNameForLevel(EFeaturePackDetailLevel InLevel, bool bLevelRequired = false)`

#### struct `FFeatureAdditionalFiles`  
`struct FFeatureAdditionalFiles`  
_L128-141_
- reflection: `USTRUCT()`
- desc: Structure that defines a shared feature pack resource.
- L132 _public function_ `FFeatureAdditionalFiles()`
- L136 _public member_ `FString DestinationFilesFolder;` — `UPROPERTY()` — Name of the folder to insert the files to
- L140 _public member_ `TArray<FString> AdditionalFilesList;` — `UPROPERTY()` — List of files to insert

#### class `FFeaturePackContentSource`  
`class FFeaturePackContentSource : public IContentSource`  
_L147-285_
- inherits: `IContentSource`
- desc: A content source which represents a content upack.
- L150 _public prototype_ `FFeaturePackContentSource();`
- L151 _public prototype_ `FFeaturePackContentSource(FString InFeaturePackPath);`
- L153 _public prototype_ `virtual ~FFeaturePackContentSource();`
- L155 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedNames() const override;`
- L156 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedDescriptions() const override;`
- L158 _public prototype_ `virtual const TArray<EContentSourceCategory>& GetCategories() const override;`
- L159 _public prototype_ `virtual const TArray<FLocalizedText>& GetLocalizedAssetTypes() const override;`
- L160 _public prototype_ `virtual const FString& GetSortKey() const override;`
- L161 _public prototype_ `virtual const FString& GetClassTypesUsed() const override;`
- L162 _public prototype_ `virtual const FString& GetIdent() const override;`
- L163 _public prototype_ `virtual TSharedPtr<FImageData> GetIconData() const override;`
- L164 _public prototype_ `virtual const TArray<TSharedPtr<FImageData>>& GetScreenshotData() const override;`
- L165 _public prototype_ `const FString& GetFocusAssetName() const;`
- L167 _public prototype_ `virtual bool InstallToProject(FString InstallPath) override;`
- L169 _public prototype_ `void InsertAdditionalFeaturePacks();`
- L170 _public prototype_ `bool InsertAdditionalResources(TArray<FFeaturePackLevelSet> InAdditionalFeaturePacks,EFeaturePackDetailLevel RequiredLevel, const FString& InDestinationFolder,TArray<FString>& InFilesCopied);`
- L172 _public prototype_ `virtual bool IsDataValid() const override;`
- L182 _public prototype_ `void CopyAdditionalFilesToFolder( const FString& DestinationFolder, TArray<FString>& FilesCopied, bool &bHasSourceFiles, FString InGameFolder = FString() );` — Copies the list of files specified in 'AdditionFilesToInclude' section in the config.ini of the feature pack. @param DestinationFolder	Destination folder for the files @param FilesCopied		List of files copied @param bContainsSource 	Set to true if the file list contains any source files @returns true if config file was read and parsed successfully
- L191 _public prototype_ `bool GetAdditionalFilesForPack(TArray<FString>& FileList, bool& bContainsSource);` — Returns a list of additional files (including the path) as specified in the config file if one exists in the pack file. @param FileList		  array to receive list of files @param bContainsSource did the file list contain any source files @returns true if config file was read and parsed successfully
- L193 _public prototype_ `static void ImportPendingPacks();`
- L196 _public member_ `TArray<FString> ParseErrors;` — Errors found when parsing manifest (if any)
- L198 _public prototype_ `void BuildListOfAdditionalFiles(TArray<FString>& AdditionalFileSourceList,TArray<FString>& FileList, bool& bContainsSourceFiles);`
- L201 _private prototype_ `static void ParseAndImportPacks();`
- L202 _private prototype_ `bool LoadPakFileToBuffer(FPakPlatformFile& PakPlatformFile, FString Path, TArray<uint8>& Buffer);`
- L212 _private prototype_ `bool ExtractListOfAdditionalFiles(const FString& ConfigFile, TArray<FString>& FileList,bool& bContainsSource);` — Extract the list of additional files defined in config file to an array @param ConfigFile	  config file as a string @param FileList		  array to receive list of files @param bContainsSource did the file list contain any source files
- L214 _private prototype_ `void RecordAndLogError(const FString& ErrorString);`
- L217 _private prototype_ `bool LoadFeaturePackImageData();` — Load the images for the icon and screen shots directly from disk
- L220 _private prototype_ `bool LoadFeaturePackImageDataFromPackFile(FPakPlatformFile& PakPlatformFile);` — extract the images for the icon and screen shots from a pak file
- L223 _private prototype_ `bool ParseManifestString(const FString& ManifestString);` — Parse the manifest string describing this pack file
- L226 _private prototype_ `FLocalizedTextArray ChooseLocalizedTextArray(TArray<FLocalizedTextArray> Choices, FString LanguageCode);` — Selects an FLocalizedText from an array which matches either the supplied language code, or the default language code.
- L227 _private prototype_ `FLocalizedText ChooseLocalizedText(TArray<FLocalizedText> Choices, FString LanguageCode);`
- L230 _private member_ `FString FeaturePackPath;` — The path of the file we used to create this feature pack instance
- L233 _private member_ `TArray<FLocalizedText> LocalizedNames;` — Array of localised names
- L236 _private member_ `TArray<FLocalizedText> LocalizedDescriptions;` — Array of localised descriptions
- L239 _private member_ `TArray<EContentSourceCategory> Categories;` — Defines the type(s) of feature pack this is
- L242 _private member_ `FString IconFilename;` — Filename of the icon
- L245 _private member_ `TSharedPtr<FImageData> IconData;` — Image data for the icon
- L248 _private member_ `TArray<TSharedPtr<FJsonValue>> ScreenshotFilenameArray;` — Filenames of the preview screenshots
- L251 _private member_ `TArray<TSharedPtr<FImageData>> ScreenshotData;` — Image data of the preview screenshots
- L254 _private member_ `TArray<FLocalizedText> LocalizedAssetTypesList;` — Array of localised assset type names
- L257 _private member_ `FString ClassTypes;` — Comma delimited string listing the class types
- L260 _private member_ `bool bPackValid;` — true if the pack is valid
- L263 _private member_ `FString FocusAssetIdent;` — Asset to focus after loading the pack
- L266 _private member_ `FString SortKey;` — Key used when sorting in the add dialog
- L269 _private member_ `TArray<FLocalizedTextArray> LocalizedSearchTags;` — Tags searched when typing in the super search box
- L272 _private member_ `TArray<FFeaturePackLevelSet> AdditionalFeaturePacks;` — Other feature packs this pack needs (shared assets)
- L275 _private member_ `FFeatureAdditionalFiles AdditionalFilesForPack;` — Additional files to copy when installing this pack
- L278 _private member_ `bool bContentsInPakFile;` — Are the contents in a pack file or did we just read a manifest for the pack
- L281 _private member_ `FString MountPoint;` — Feature pack mount point
- L283 _private member_ `FString Identity;`
- L284 _private member_ `FString VersionNumber;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API ADDCONTENTDIALOG_API`

### `Source/Editor/AddContentDialog/Public/IAddContentDialogModule.h` (Public)


#### class `IAddContentDialogModule`  
`class IAddContentDialogModule : public IModuleInterface`  
_L12-21_
- inherits: `IModuleInterface`
- desc: Defines methods for interacting with the Add Content Dialog.
- L17 _public prototype_ `virtual TSharedRef<FContentSourceProviderManager> GetContentSourceProviderManager() = 0;` — Gets the object responsible for managing content source providers.
- L20 _public prototype_ `virtual void ShowDialog(TSharedRef<SWindow> ParentWindow) = 0;` — Creates a dialog for adding existing content to a project.
