# Plugins / UnifiedFavorites

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/UnifiedFavorites`
- headers: 3; symbols: 41
- symbol kinds: class=3, function=1, member=6, namespace=3, prototype=25, struct=3
- PrivateDependencyModuleNames: ApplicationCore, ContentBrowser, InputCore, LevelEditor, LevelInstanceEditor, TedsActorCompatibility, TedsAssetData, TedsOperations, TedsOutliner, TedsQueryStack, TedsTableViewer, ToolMenus, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, SceneOutliner, Slate, SlateCore, TypedElementFramework, TypedElementRuntime

### `Plugins/Experimental/EditorDataStorageFeatures/Source/UnifiedFavorites/Private/Widgets/UnifiedFavoritesOutlinerWidget.h` (Private)


#### struct `FOutlinerFavoriteHeaderConstructor`  
`struct FOutlinerFavoriteHeaderConstructor : public FSimpleWidgetConstructor`  
_L12-26_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Outliner-specific header override
- L17 _public prototype_ `FOutlinerFavoriteHeaderConstructor();`
- L18 _public prototype_ `~FOutlinerFavoriteHeaderConstructor() override = default;`
- L20 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UUnifiedFavoritesOutlinerFactory`  
`class UUnifiedFavoritesOutlinerFactory : public UEditorDataStorageFactory`  
_L30-40_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Factory — registers only the Outliner header override
- L35 _public prototype_ `~UUnifiedFavoritesOutlinerFactory() override = default;`
- L37 _public prototype_ `virtual void RegisterWidgetConstructors( UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/UnifiedFavorites/Private/Widgets/UnifiedFavoritesTableWidget.h` (Private)


#### struct `FTableFavoriteWidgetConstructor`  
`struct FTableFavoriteWidgetConstructor : public FSimpleWidgetConstructor`  
_L15-32_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L20 _public prototype_ `FTableFavoriteWidgetConstructor();`
- L21 _public prototype_ `~FTableFavoriteWidgetConstructor() override = default;`
- L23 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L29 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FTableFavoriteHeaderConstructor`  
`struct FTableFavoriteHeaderConstructor : public FSimpleWidgetConstructor`  
_L35-49_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L40 _public prototype_ `FTableFavoriteHeaderConstructor();`
- L41 _public prototype_ `~FTableFavoriteHeaderConstructor() override = default;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### class `UUnifiedFavoritesTableFactory`  
`class UUnifiedFavoritesTableFactory : public UEditorDataStorageFactory`  
_L56-64_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L61 _public prototype_ `~UUnifiedFavoritesTableFactory() override = default;`
- L63 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/UnifiedFavorites/Private/Widgets/UnifiedFavoritesWidget.h` (Private)


#### class `UE::Editor::DataStorage::SUnifiedFavoritesWidget`  
`class SUnifiedFavoritesWidget final : public SImage`  
_L12-60_
- inherits: `SImage`
- desc: Widget responsible for managing the favorite state of a TEDS row handle
- L15 _public function_ `SLATE_BEGIN_ARGS(SUnifiedFavoritesWidget) : _ActiveColor(FAppStyle::Get().GetSlateColor("Colors.Foreground")), _NotActiveColor(FAppStyle::Get().GetSlateColor("Colors.Transparent"))`
- L20 _public prototype_ `SLATE_ARGUMENT(FSlateColor, ActiveColor) SLATE_ARGUMENT(FSlateColor, NotActiveColor) SLATE_ARGUMENT(UE::Editor::DataStorage::RowHandle, RowHandle) SLATE_END_ARGS() void Construct(const FArguments& InArgs, ICoreProvider* InDataStorage);`
- L28 _public prototype_ `virtual bool IsInteractable() const override;`
- L31 _public prototype_ `void SetTargetRow(RowHandle InTargetRow);` — Directly sets the resolved target row (called by the mapping resolution processor).
- L34 _private prototype_ `bool IsFavorite() const;`
- L36 _private prototype_ `void ToggleFavorite() const;`
- L38 _private prototype_ `FReply HandleClick() const;`
- L40 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L42 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L44 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _private prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L48 _private prototype_ `const FSlateBrush* GetBrush() const;`
- L51 _private member_ `ICoreProvider* DataStorage;`
- L53 _private member_ `RowHandle TargetRow = InvalidRowHandle;`
- L55 _private member_ `FSlateColor ActiveColor;`
- L56 _private member_ `FSlateColor NotActiveColor;`
- L58 _private member_ `const FSlateBrush* FavoriteBrush;`
- L59 _private member_ `const FSlateBrush* NotFavoriteBrush;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
