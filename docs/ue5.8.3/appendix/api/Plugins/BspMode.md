# Plugins / BspMode

- module root: `Plugins/Editor/GeometryMode/Source/BspMode`
- headers: 6; symbols: 42
- symbol kinds: class=6, function=4, macro=1, member=12, prototype=18, struct=1
- DynamicallyLoadedModuleNames: PlacementMode, PropertyEditor
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: PlacementMode

### `Plugins/Editor/GeometryMode/Source/BspMode/Private/BspDragHandler.h` (Private)


#### class `FBspDragHandler`  
`class FBspDragHandler : public FPlaceableItem::FDragHandler`  
_L9-15_
- inherits: `FPlaceableItem::FDragHandler`
- L13 _public prototype_ `FBspDragHandler();`
- L14 _public prototype_ `void Initialize( TSharedRef<FBspBuilderType> InBspBuilder );`

### `Plugins/Editor/GeometryMode/Source/BspMode/Private/BspMode.h` (Private)


#### class `FBspMode`  
`class FBspMode : public FEdMode`  
_L9-16_
- inherits: `FEdMode`
- desc: Mode Toolkit for the Bsp
- L13 _public function_ `virtual bool UsesToolkits() const override`
- L15 _public function_ `virtual bool UsesPropertyWidgets() const override`

### `Plugins/Editor/GeometryMode/Source/BspMode/Private/BspModeModule.h` (Private)


#### struct `FBspBuilderType`  
`struct FBspBuilderType`  
_L17-41_
- L19 _public prototype_ `FBspBuilderType(class UClass* InBuilderClass, const FText& InText, const FText& InToolTipText, const FSlateBrush* InIcon);`
- L22 _public member_ `TWeakObjectPtr<UClass> BuilderClass;` — The class of the builder brush
- L25 _public member_ `FName BuilderClassName;` — The class name of the builder brush
- L28 _public member_ `FText Text;` — The name to be displayed for this builder
- L31 _public member_ `FText ToolTipText;` — The name to be displayed for this builder
- L34 _public member_ `const FSlateBrush* Icon;` — The icon to be displayed for this builder
- L37 _public member_ `TSharedPtr<FPlaceableItem> PlaceableItem;` — the placeable item that will provide the information for the draggable  for this BSP builder
- L40 _public member_ `TOptional<FPlacementModeID> PlacementModeID;` — TOptional<FPlacementModeID>for deletion

#### class `FBspModeModule`  
`class FBspModeModule : public IBspModeModule`  
_L43-64_
- inherits: `IBspModeModule`
- L48 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L49 _public prototype_ `virtual void ShutdownModule() override;`
- L52 _public prototype_ `virtual void RegisterBspBuilderType( class UClass* InBuilderClass, const FText& InBuilderName, const FText& InBuilderTooltip, const FSlateBrush* InBuilderIcon ) override;` — IBspModeModule interface
- L53 _public prototype_ `virtual void UnregisterBspBuilderType( class FName InBuilderClassName ) override;`
- L55 _public prototype_ `const TArray< TSharedPtr<FBspBuilderType> >& GetBspBuilderTypes();`
- L56 _public prototype_ `TSharedPtr<FBspBuilderType> FindBspBuilderType(UClass* InBuilderClass) const;`
- L60 _private member_ `TArray< TSharedPtr<FBspBuilderType> > BspBuilderTypes;`
- L61 _private member_ `FName CategoryName;`
- L63 _private member_ `TArray<FName> BspBuilderTypesToUnregisterOnShutdown;`

### `Plugins/Editor/GeometryMode/Source/BspMode/Private/SBspPalette.h` (Private)


#### class `SBspPalette`  
`class SBspPalette : public SCompoundWidget, public FNotifyHook`  
_L16-33_
- inherits: `SCompoundWidget,FNotifyHook`
- L19 _public function_ `SLATE_BEGIN_ARGS( SBspPalette )`
- L20 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct( const FArguments& InArgs );`
- L27 _private prototype_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<struct FBspBuilderType> BspBuilder, const TSharedRef<STableViewBase>& OwnerTable);` — Make a widget for the list view display
- L31 _private member_ `TSharedPtr<class SBspBuilderListView> ListViewWidget;` — List View for the BSP Builder Types

### `Plugins/Editor/GeometryMode/Source/BspMode/Public/BspModeStyle.h` (Public)


#### class `FBspModeStyle`  
`class FBspModeStyle`  
_L13-28_
- desc: BSP mode slate style
- L17 _public prototype_ `static void Initialize();`
- L18 _public prototype_ `static void Shutdown();`
- L20 _public prototype_ `static const ISlateStyle& Get();`
- L22 _public prototype_ `static const FName& GetStyleSetName();`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;` — Singleton instances of this style.

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API BSPMODE_API`

### `Plugins/Editor/GeometryMode/Source/BspMode/Public/IBspModeModule.h` (Public)


#### class `IBspModeModule`  
`class IBspModeModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void RegisterBspBuilderType( class UClass* InBuilderClass, const FText& InBuilderName, const FText& InBuilderTooltip, const FSlateBrush* InBuilderIcon ) = 0;`
- L16 _public function_ `virtual void UnregisterBspBuilderType( class UClass* InBuilderClass )` — `UE_DEPRECATED(5.8, "Use the FName variant of UnregisterBspBuilderType")`
- L17 _public prototype_ `virtual void UnregisterBspBuilderType( FName InBuilderClassName ) = 0;`
