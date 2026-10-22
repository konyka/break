# Developer / WidgetRegistration

- module root: `Source/Developer/WidgetRegistration`
- headers: 29; symbols: 494
- symbol kinds: class=38, delegate=4, enum=3, enumerator=9, function=18, macro=8, member=165, namespace=12, prototype=225, struct=12
- PublicDependencyModuleNames: Core, CoreUObject, EditorConfig, Engine, Slate, SlateCore, ToolMenus
- PublicIncludePathModuleNames: ToolMenus

### `Source/Developer/WidgetRegistration/Private/DataVisualization/ZeroStateBuilder.h` (Private)


#### class `FZeroStateBuilder`  
`class FZeroStateBuilder : public FSlateBuilder`  
_L15-45_
- inherits: `FSlateBuilder`
- desc: A builder which builds a view of a "Zero State" which can be displayed when no objects are available for that view. It has an icon which shows some indication of the missing data, and some text which explains the state.
- L23 _public prototype_ `explicit FZeroStateBuilder( UE::DisplayBuilders::FLabelAndIconArgs LabelAndIconArgs = UE::DisplayBuilders::FLabelAndIconArgs{ LOCTEXT("ZeroStateBuilderDefaultLabel", "No items available." ) , FBuilderIconKeys::Get().ZeroStateDefaultMedium().GetSlateIcon() } );` — The constructor which takes a FLabelAndIconArgs to initialize the Zero state @param LabelAndIconArgs a parameter object to provide the label and icon information
- L30 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Build the Zero state SWidget and return it
- L36 _private prototype_ `virtual void UpdateWidget() override;` — Keeping UpdateWidget private until/unless there is a need for it
- L41 _private prototype_ `virtual void ResetWidget() override;` — Keeping ResetWidget private until/unless there is a need for it
- L43 _private member_ `FSlateIcon Icon;`
- L44 _private member_ `FText Label;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "ZeroStateBuilder"`

### `Source/Developer/WidgetRegistration/Private/DataVisualization/ZeroStateBuilderTemplates.h` (Private)


#### class `FZeroStateBuilderTemplates`  
`class FZeroStateBuilderTemplates`  
_L10-28_
- desc: FZeroStateBuilderTemplates provides some templates for Zero State Builders.
- L13 _public prototype_ `static const FZeroStateBuilderTemplates& Get();`
- L20 _public prototype_ `TSharedRef<FZeroStateBuilder> GetDefault( FText DefaultText = FText::GetEmpty() ) const;` — A default Zero state builder which gives a general default icon and text for unavailable items @param DefaultText the text shown below the icon in the zero state view
- L27 _public prototype_ `TSharedRef<FZeroStateBuilder> GetFavorites( FText NoFavoritesAvailableText = FText::GetEmpty() ) const;` — A Zero state builder which gives an icon and text for no favorites items available @param NoFavoritesAvailableText the text shown below the icon in the zero state view

### `Source/Developer/WidgetRegistration/Private/Inputs/BuilderCommandCreationManager.h` (Private)


#### class `FBuilderCommandCreationManager`  
`class FBuilderCommandCreationManager : public TCommands<FBuilderCommandCreationManager>`  
_L17-43_
- inherits: `TCommands<FBuilderCommandCreationManager>`
- desc: FBuilderCommandCreationManager creates dynamic FUICommandInfos that can be used with toolbars, menus, and other command-centric objects and fills out the associated information in FBuilderInputs
- L22 _public prototype_ `FBuilderCommandCreationManager();` — default constructor
- L27 _public prototype_ `virtual void RegisterCommands() override;` — Creates the current commands specified in FUICommandInfoArray
- L35 _public prototype_ `void RegisterCommandForBuilder( UE::DisplayBuilders::FBuilderInput& OutBuilderInput ) const;` — Given a FBuilderInput, registers a TSharedPtr<FUICommandInfo> which can be used to create Slate toolbars, menus, and other command-centric objects and initializes the Command information for the FBuilderInput @param OutBuilderInput the FBuilderInput for which to register and initialize the related TSharedPtr<FUICommandInfo>
- L42 _public prototype_ `void UnregisterCommandForBuilder( UE::DisplayBuilders::FBuilderInput& OutBuilderInput ) const;` — Given a FBuilderInput, unregisters and tears down the related TSharedPtr<FUICommandInfo> @param OutBuilderInput the FBuilderInput for which to unregister and tear down TSharedPtr<FUICommandInfo>

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DisplayBuilders` (scope `UE`)

### `Source/Developer/WidgetRegistration/Private/Inputs/BuilderInputManager.h` (Private)


#### class `FBuilderInputManager`  
`class FBuilderInputManager`  
_L17-40_
- desc: BuilderInputManager provides access to utilities and information regarding user input.
- L24 _public prototype_ `static FBuilderInputManager& Get();` — Gets the singleton instance of FBuilderInputManager
- L29 _public prototype_ `static void Initialize();` — Registers and initializes the Command binding context.
- L34 _public prototype_ `static void Shutdown();` — Unregisters the Command context.
- L39 _public prototype_ `const FBuilderCommandCreationManager& GetCommandManager();` — @return the Command manager for Builders

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DisplayBuilders` (scope `UE`)

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/ColumnWrappingContainer.h` (Private)


#### class `FColumnWrappingContainerArgs`  
`class FColumnWrappingContainerArgs : public FWidgetContainerArgs`  
_L12-35_
- inherits: `FWidgetContainerArgs`
- desc: A struct that provides arguments for FColumnWrappingContainers
- L24 _public prototype_ `FColumnWrappingContainerArgs( float InCellHeight = TNumericLimits<float>::Min() , int32 InNumColumnsOverride = TNumericLimits<float>::Min() , FName InIdentifier = "FCol` — A constructor that initializes the arguments @param InCellHeight the height of the cells in this container @param InNumColumnsOverride the number of columns in the container. If not provided, the number of columns is dynamic, based on the container width and the width of the text of the buttons @param InIdentifier the identifier for this container
- L31 _public member_ `int32 NumColumns;` — the number of columns in the container. If not provided, the number of columns is dynamic, based on the container width and the width of the text of the buttons
- L34 _public member_ `float CellHeight;` — the height of the cells in this container

#### class `FColumnWrappingContainer`  
`class FColumnWrappingContainer : public FWidgetContainer`  
_L41-99_
- inherits: `FWidgetContainer`
- desc: A container that will provide best fit wrapping for columns, which you can override if needed.
- L49 _public prototype_ `explicit FColumnWrappingContainer( FColumnWrappingContainerArgs&& Args );` — Constructs the FColumnWrappingContainer @param Args the parameter object to initialize this container
- L56 _public prototype_ `explicit FColumnWrappingContainer( const FColumnWrappingContainerArgs& Args = {} );` — Constructs the FColumnWrappingContainer @param Args the parameter object to initialize this container
- L64 _public prototype_ `FColumnWrappingContainer& SetNumColumns( const int32& InNumColumns );` — Sets the number of columns to the int32 InNumColumns, and returns a reference to this to support chaining @param InNumColumns the number of columns to have in the container @return a reference to this to support chaining
- L69 _public prototype_ `virtual void Empty() override;` — Clear the container and any widget content within it
- L77 _protected prototype_ `virtual void CreateAndPositionWidgetAtIndex(int32 Index) override;` — Creates and positions within this container the Widget generated by the Builder at index "Index" in ChildBuilderArray @param Index the index of the builder in ChildBuilderArray to create and position the widget
- L83 _private prototype_ `void Initialize();` — Initializes this container
- L86 _private member_ `TSharedPtr<SBorder> MainContentSBorder;` — The SBorder that provides the look and feel for this container
- L91 _private member_ `TSharedPtr<SUniformWrapPanel> UniformWrapPanel;` — The SUniformWrapPanel that provides the layout for this container
- L95 _private member_ `int32 NumColumns;` — the number of columns in the container. If not provided, the number of columns is dynamic, based on the container width and the width of the text of the buttons
- L98 _private member_ `float CellHeight;` — the height of the cells in this container

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/ColumnWrappingContainerTemplates.h` (Private)


#### struct `FColumnWrappingContainerTemplates`  
`struct FColumnWrappingContainerTemplates`  
_L9-20_
- desc: Provides templates for
- L14 _public prototype_ `static FColumnWrappingContainerTemplates& Get();` — Gets the singleton instance of FColumnWrappingContainerTemplates
- L19 _public prototype_ `TSharedRef<FColumnWrappingContainer> GetBestFitColumnsWithSmallCells();` — Creates a TSharedRef<FColumnWrappingContainer> that will create columns on a best fit for size basis

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/HeaderAndBodyContainer.h` (Private)


#### class `FHeaderAndBodyContainerArgs`  
`class FHeaderAndBodyContainerArgs`  
_L15-43_
- desc: The parameter objects for a FHeaderAndBodyContainer.
- L18 _public prototype_ `FHeaderAndBodyContainerArgs( const FName& InIdentifier = "FHeaderAndBodyContainer", const TSharedRef<FSlateBuilder>& InHeader = MakeShared<FSlateBuilder>(), const TSharedRef<FSlateBuilder>& InBody = MakeShared<FSlateBuilder>(), const bool bInHasToggleButtonToCollapseBody = false, const bool bIsBodyHidden = false, const bool bIsHeaderHiddenOnCreate = false );`
- L27 _public member_ `FName Identifier;` — the identifier for the FHeaderAndBodyContainer
- L30 _public member_ `TSharedRef<FSlateBuilder> HeaderBuilder;` — the FSlateBuilder that builds the header of this container
- L33 _public member_ `TSharedRef<FSlateBuilder> BodyBuilder;` — the FSlateBuilder that builds the body of this container
- L36 _public member_ `bool bHasToggleButtonToCollapseBody;` — whether or not this container has a button to toggle the body open and closed
- L39 _public member_ `bool bIsBodyHidden;` — if true, the body is initially hidden
- L42 _public member_ `bool bIsHeaderHiddenOnCreate;` — if true, the header is initially hidden

#### class `FHeaderAndBodyContainer`  
`class FHeaderAndBodyContainer : public FSlateBuilder`  
_L48-164_
- inherits: `FSlateBuilder`
- desc: A container which provides a header and a body, both of which can be any SWidget.
- L62 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnBodyAddedOrRemoved, EBodyLifeCycleEventType LifeCycleEventType );`
- L67 _public prototype_ `void SetHeader( const TSharedRef<FSlateBuilder>& InHeaderBuilder );` — Sets the FSlateBuilder InHeaderBuilder to build the widget for the header of this container
- L72 _public prototype_ `void SetHeader( const TSharedRef<SWidget>& HeaderWidget );` — Converts the SWidget HeaderWidget to an FSlateBuilder which will build the widget for the header of this container
- L77 _public prototype_ `void SetBody( const TSharedRef<FSlateBuilder>& InBodyBuilder );` — Sets the FSlateBuilder InBodyBuilder to build the widget for the body of this container
- L82 _public prototype_ `void SetBody( const TSharedRef<SWidget>& BodyWidget );` — Converts the SWidget BodyWidget to an FSlateBuilder which will build the widget for the body of this container
- L89 _public prototype_ `FHeaderAndBodyContainer( const FHeaderAndBodyContainerArgs& Args = FHeaderAndBodyContainerArgs() );` — Constructs this container. @param Args the FHeaderAndBodyContainerArgs which will initialize this FHeaderAndBodyContainer
- L91 _public member_ `FOnBodyAddedOrRemoved OnBodyAddedOrRemoved;`
- L96 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Generates the widget for this header and body container and returns it
- L99 _public prototype_ `virtual void UpdateWidget() override;` — Updates/reloads this widget. This should be called after a consumer has changed any Data in this
- L106 _public prototype_ `void SetHeaderHidden(bool bInIsHeaderHidden );` — Sets the header content to be hidden @param bInIsHeaderHidden if true the header is hidden, else it is false
- L109 _public function_ `bool IsBodyEmpty()` — @return true if the body is empty, else returns false
- L118 _private prototype_ `FReply ToggleBodyExpansionState();` — called when the user toggles the expansion of the body
- L121 _private prototype_ `void UpdateToBodyAddedState();` — Makes the body visible by adding it
- L124 _private prototype_ `void UpdateToBodyRemovedState();` — Makes the body invisible by removing it
- L127 _private prototype_ `void UpdateToHeaderRemovedState();` — Makes the header invisible by removing it
- L130 _private prototype_ `void UpdateToHeaderAddedState();` — Makes the header visible by adding it
- L133 _private prototype_ `virtual void ResetWidget() override;` — overriding to hide the method, as it is not needed
- L136 _private member_ `TSharedRef<FSlateBuilder> HeaderBuilder;` — builds the header for this container
- L139 _private member_ `TSharedPtr<SBox> HeaderContentSBox;` — the SBox containing the header
- L142 _private member_ `TSharedPtr<SBorder> HeaderContentSBorder;` — the SBorder containing the header
- L145 _private member_ `TSharedRef<FSlateBuilder> BodyBuilder;` — builds the body for this container
- L148 _private member_ `TSharedPtr<SBox> BodyContentSBox;` — the SBox containing the body
- L151 _private member_ `TSharedPtr<SScrollBox> BodyContentSScrollBox;` — the scrollbox for the body
- L154 _private member_ `TSharedPtr<SImage> ToggleExpansionImage;` — the image for the toggle body button
- L157 _private member_ `bool bHasToggleButtonToCollapseBody;` — if true, this container has a toggle button to hide and show the body
- L160 _private member_ `bool bIsBodyHidden;` — if true, the body will not be viewable
- L163 _private member_ `bool bIsHeaderHidden;` — if true, the header will not be viewable

#### enum `FHeaderAndBodyContainer::EBodyLifeCycleEventType`  
`enum class EBodyLifeCycleEventType`  
_L56-60_
- desc: an enum to tell whether the body has been added or removed
- L58 _public enumerator_ `Added`
- L59 _public enumerator_ `Removed`

#### Free symbols / members of external scopes

- L62 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBodyAddedOrRemoved, EBodyLifeCycleEventType LifeCycleEventType );`

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/SimpleTitleContainer.h` (Private)


#### class `FSimpleTitleContainerArgs`  
`class FSimpleTitleContainerArgs : public FHeaderAndBodyContainerArgs`  
_L9-24_
- inherits: `FHeaderAndBodyContainerArgs`
- desc: a struct to provide arguments to the FSimpleTitleContainer
- L12 _public function_ `FSimpleTitleContainerArgs( FText InTitle = FText::GetEmpty(), const FName& InIdentifier = "FSimpleTitleContainer", const TSharedRef<FSlateBuilder>& InHeader = MakeShared<FSlateBuilder>(), const TSharedRef<FSlateBuilder>& InBody = MakeShared<FSlateBuilder>(), const bool bIsExpanded = false ) : FHeaderAndBodyContainerArgs(InIdentifier , InHeader, InBody, bIsExpanded ) , Title( InTitle )`
- L23 _public member_ `FText Title;`

#### class `FSimpleTitleContainer`  
`class FSimpleTitleContainer : public FHeaderAndBodyContainer`  
_L29-45_
- inherits: `FHeaderAndBodyContainer`
- desc: A container providing a simple FText title and a customizable body
- L35 _public prototype_ `FSimpleTitleContainer( const FSimpleTitleContainerArgs& Args );` — A constructor taking const FSimpleTitleContainerArgs& to initialize it
- L40 _public prototype_ `FSimpleTitleContainer( FSimpleTitleContainerArgs&& Args );` — A constructor taking const FSimpleTitleContainerArgs& to initialize it
- L44 _private member_ `FText Title;` — the title of the container, it will be set in the header

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/SlateBuilder.h` (Private)


#### class `FSlateBuilderArgs`  
`class FSlateBuilderArgs`  
_L10-37_
- desc: An argument object to instantiate the FSlateBuilder
- L21 _public prototype_ `FSlateBuilderArgs( const FName& InName = "SlateBuilder", const TSharedPtr<SWidget> InContent = SNullWidget::NullWidget.ToSh` — Creates the slate builder parameter object. @param InName the name of the builder @param InContent the shared pointer to the SWidget that provides the content for this slate builder. If this is nullptr or it is not provided, this builder will show a NullWidget
- L30 _public prototype_ `FSlateBuilderArgs( const UE::DisplayBuilders::FBuilderKey& InBuilderKey = UE::DisplayBuilders::FBuilderKeys::Get().None(), const TSharedPtr<SWidget> InContent = nullptr );` — Creates the slate builder parameter object. @param InBuilderKey the FBuilderKey for this builder @param InContent the shared pointer to the SWidget that provides the content for this slate builder. If this is nullptr or it is not provided, this builder will show a NullWidget
- L33 _public member_ `const UE::DisplayBuilders::FBuilderKey BuilderKey;` — the BuilderKey for the arguments
- L36 _public member_ `const TSharedPtr<SWidget> Content;` — the shared pointer to the SWidget that provides the content for this slate builder

#### class `FSlateBuilder`  
`class FSlateBuilder : public FToolElementRegistrationArgs`  
_L44-93_
- inherits: `FToolElementRegistrationArgs`
- desc: A builder which can build raw Slate. This is mostly used for adding raw Slate to Builder Containers, but can be used to build any Slate. It allows raw slate to be used in the context of builder containers, and provides backward compatibility so that Slate and builders can be used in the same context.
- L54 _public prototype_ `explicit FSlateBuilder( TSharedPtr<SWidget> InContent = nullptr, FName InIdentifier = "FSla` — A constructor which takes the TSharedPtr<SWidget> that provides the content for this builder, and the identifier for the builder @param InContent the TSharedPtr<SWidget> that provides the content for this builder @param InIdentifier the identifier for this container
- L61 _public prototype_ `explicit FSlateBuilder( FName InIdentifier );` — A constructor providing the identifier for the builder @param InIdentifier the identifier for this container
- L68 _public prototype_ `FSlateBuilder( UE::DisplayBuilders::FBuilderKey InBuilderKey );` — A constructor providing an FBuilderKey for the builder @param InBuilderKey the FBuilderKey for this FSlateBuilder
- L73 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — @return the TSharedPtr<SWidget> specified as the content for this FSlateBuilder
- L78 _public prototype_ `bool IsEmpty();` — @return true if the content of this is equivalent to an SNullWidget
- L83 _public prototype_ `virtual void Empty();` — Empties the content
- L87 _protected member_ `TSharedPtr<SWidget> SlateContent;` — The TSharedPtr<SWidget> that is the content for this FSlateBuilder
- L92 _private member_ `TSharedPtr<FSlateBuilder> SlateBuilder;` — The FSlateBuilder that provides the content for this FSlateBuilder

### `Source/Developer/WidgetRegistration/Private/Layout/Containers/WidgetContainer.h` (Private)


#### class `FWidgetContainerArgs`  
`class FWidgetContainerArgs`  
_L11-24_
- desc: A struct to provide the arguments for an FWidgetContainer
- L19 _public prototype_ `FWidgetContainerArgs( FName InIdentifier = "FWid` — The constructor for the widget arguments @param InIdentifier the identifier for this container
- L23 _public member_ `FName Identifier;` — the identifier for this container

#### class `FWidgetContainer`  
`class FWidgetContainer : public FSlateBuilder`  
_L29-102_
- inherits: `FSlateBuilder`
- desc: A Widget Container that contains an array of FSlateBuilders
- L38 _public prototype_ `explicit FWidgetContainer( const FWidgetContainerArgs Args );` — A constructor with const Args which can be used with Presets of extending containers @param Args the arugments to initializes this container
- L43 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Generates the container and its children.
- L48 _public prototype_ `virtual void UpdateWidget() override;` — Updates the container and its children.
- L56 _public prototype_ `FWidgetContainer& SetBuilders( TArray<TSharedRef<FSlateBuilder>> Builders );` — Sets the FSlateBuilders in Builders as the children of this container to provide the contents of this container. If there were previously any builders in this container, they will be cleared and these Builders will provide the entire content of this container @param Widgets the SWidgets that will provide the contents of this container
- L63 _public prototype_ `FWidgetContainer& AddBuilder( TSharedRef<SWidget> Widget);` — Converts "Widget" to an FSlateBuilder and adds it to the existing FSlateBuilders in this container @param Widget the widget to add to this container
- L70 _public prototype_ `FWidgetContainer& AddBuilder( const TSharedRef<FSlateBuilder>& Builder );` — Adds Builder to the contents @param Builder the shared pointer to the FSlateBuilder to add to this container
- L75 _public prototype_ `virtual void Empty() override;` — Clear the container and any widget content within it
- L81 _protected member_ `TSharedPtr<SWidget> MainContentWidget;` — The SWidget which holds the main content of this container
- L88 _protected prototype_ `TSharedPtr<FSlateBuilder> GetBuilderAtIndex( int32 Index );` — @return the Builder at index "Index" in ChildBuilderArray @param Index the index of the builder in ChildBuilderArray to return
- L95 _protected prototype_ `virtual void CreateAndPositionWidgetAtIndex( int32 Index ) = 0;` — Positions the Builder at index "Index" in ChildBuilderArray within this container @param Index the index of the builder in ChildBuilderArray to position
- L101 _private member_ `TArray<TSharedRef<FSlateBuilder>> ChildBuilderArray;` — The array of FSlateBuilders that will be converted to widgets by this container

### `Source/Developer/WidgetRegistration/Private/Styles/BuilderIconKeys.h` (Private)


#### class `FBuilderIconKey`  
`class FBuilderIconKey`  
_L16-71_
- desc: Provides keys for display builder Icons
- L21 _public function_ `void InitializeIcon()` — initializes the slate icon. This must be called after the the icon is registered by the Builder Style
- L29 _public member_ `const FString RelativePathToContainingFolder;` — The FString providing the relative path to the icon
- L34 _public member_ `const FName Name;` — The name of the Icon
- L39 _public member_ `const FBuilderIconSizeKey& SizeKey;` — The FBuilderIconSizeKey that provides the size of the Icon
- L44 _public member_ `const FName FileNameWithoutExtension;` — The name of the Icon file, not including relative path or extension
- L50 _public member_ `const FString RelativePathToFileWithoutExtension;` — the relative path to the file for the icon. This includes both the relative path of directories and the name of the file for the icon, but not the file extension
- L56 _public prototype_ `FSlateIcon GetSlateIcon() const;` — @return the FSlateIcon for this FBuilderIconKey
- L62 _private member_ `FSlateIcon SlateIcon;`
- L70 _private prototype_ `FBuilderIconKey( const FString InRelativePathToContainingFolder, const FName InName, const FBuilderIconSizeKey& InSizeKey );` — The constructor which takes an FName which provides the identifier for this BuilderIconKey @param InName the FName which provides the identifier for this BuilderIconKey @param InRelativePathToContainingFolder the relative path to the containing folder @param InSizeKey the icon size key for this

#### class `FBuilderIconKeys`  
`class FBuilderIconKeys`  
_L77-94_
- desc: Keys for builder icons
- L83 _public prototype_ `static const FBuilderIconKeys& Get();` — Gets the FBuilderIconKeys singleton
- L86 _public prototype_ `const FBuilderIconKey& ZeroStateDefaultMedium() const;` — An Icon for the default Zero State view. This shows a default icon that denotes that there are no items available
- L89 _public prototype_ `const FBuilderIconKey& ZeroStateFavoritesMedium() const;` — An Icon for the favorites Zero State view. This shows a zero state favorites icon that denotes that there are no favorites available
- L93 _private prototype_ `FBuilderIconKeys();` — private constructor as these keys should map to icons that we include with builder content

### `Source/Developer/WidgetRegistration/Private/Styles/BuilderIconSizeKeys.h` (Private)


#### class `FBuilderIconSizeKey`  
`class FBuilderIconSizeKey`  
_L14-48_
- desc: Provides identifiers and values for icon sizes
- L20 _public prototype_ `explicit FBuilderIconSizeKey( FString RelativePathToContainingFolder );` — default constructor that initializes the key
- L25 _public member_ `const FName Name;` — The name of the Icon
- L30 _public member_ `const FVector2D Size;` — The Size of the Icon
- L43 _private function_ `FBuilderIconSizeKey( const FName InName, const FVector2D InSize ) : Name( InName ) , Size( InSize )` — The constructor which takes an FName which provides the identifier for this BuilderIconSizeKey @param InName the FName which provides the identifier for this BuilderIconSizeKey @param InSize the FVector2D size of the icon

#### class `FBuilderIconSizeKeys`  
`class FBuilderIconSizeKeys`  
_L53-78_
- desc: FBuilderIconSizeKeys provides sizes for builder icons
- L56 _public prototype_ `static const FBuilderIconSizeKeys& Get();`
- L58 _public function_ `const FBuilderIconSizeKey& ExtraSmall() const`
- L64 _public function_ `const FBuilderIconSizeKey& Small() const`
- L70 _public function_ `const FBuilderIconSizeKey& Medium() const`
- L77 _private prototype_ `FBuilderIconSizeKeys();`
- L80 _function_ `inline const FBuilderIconSizeKeys& FBuilderIconSizeKeys::Get()`
- L86 _function_ `inline FBuilderIconSizeKeys::FBuilderIconSizeKeys()`

### `Source/Developer/WidgetRegistration/Private/Styles/BuilderStyleManager.h` (Private)


#### class `FBuilderStyleManager`  
`class FBuilderStyleManager final : public FSlateStyleSet`  
_L12-31_
- inherits: `FSlateStyleSet`
- desc: Provides styling utilities and information for builders.
- L15 _public function_ `static FBuilderStyleManager& Get()`
- L26 _public prototype_ `void RegisterSlateIcon( const FBuilderIconKey Key );` — Given Key, registers the FSlateIcon for it @param Key the FBuilderIconKey to register the FSlateIcon for
- L28 _public prototype_ `FBuilderStyleManager();`

### `Source/Developer/WidgetRegistration/Public/BuilderKey.h` (Public)


#### class `UE::DisplayBuilders::FBuilderKey`  
`class FBuilderKey`  
_L14-57_
- desc: Provides identifiers for display builders and some methods for using them. These are also used as the keys into persistent storage for builders.
- L20 _public prototype_ `explicit FBuilderKey();` — default constructor that initializes the key
- L25 _public prototype_ `FName ToName() const;` — converts the BuilderKey to its FName
- L32 _public prototype_ `FString GetKeyWithSuffix( const FName Suffix ) const;` — @return a combined key with Suffix @param Suffix the FName that will provide the Suffix for the combined Key
- L37 _public prototype_ `bool IsNone() const;` — @return true if this builder is set to None, meaning that it has not been initialized
- L46 _private member_ `const FName Key;` — The FName providing the identifier
- L53 _private function_ `FBuilderKey( const FName InKey ) : Key( InKey )` — The constructor which takes an FName which provides the identifier for this BuilderKey @param InKey the FName which provides the identifier for this BuilderKey

#### class `UE::DisplayBuilders::FBuilderKeys`  
`class FBuilderKeys`  
_L62-81_
- desc: FBuilderKeys provides keys registered for specific builders.
- L68 _public prototype_ `static const FBuilderKeys& Get();` — Get the singleton FBuilderKeys
- L71 _public prototype_ `const FBuilderKey& PlaceActors() const;` — The FBuilderKey for the Place Actors FCategoryDrivenContentBuilder. This provides the key into the favorites storage for place actors.
- L74 _public prototype_ `const FBuilderKey& None() const;` — A "None" key to provide a null state when needed.
- L80 _private prototype_ `FBuilderKeys();` — The constructor is kept private because these are for UE supported builders.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DisplayBuilders` (scope `UE`)

### `Source/Developer/WidgetRegistration/Public/Common/BuilderTypes.h` (Public)


#### class `UE::DisplayBuilders::FLabelAndIconArgs`  
`class FLabelAndIconArgs`  
_L13-20_
- desc: A class which provides a parameter object for builders consisting of an FText Label and a FSlateIcon icon
- L16 _public prototype_ `explicit FLabelAndIconArgs( FText InLabel = FText::GetEmpty(), FSlateIcon InIcon = FSlateIcon() );`
- L18 _public member_ `FText Label;`
- L19 _public member_ `FSlateIcon Icon;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DisplayBuilders` (scope `UE`)

### `Source/Developer/WidgetRegistration/Public/FToolkitWidgetStyle.h` (Public)


#### struct `FToolkitWidgetStyle`  
`struct FToolkitWidgetStyle : public FSlateWidgetStyle`  
_L19-64_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: FToolkitWidgetStyle is the FSlateWidgetStyle that defines the styling of a ToolkitWidget
- L23 _public function_ `FToolkitWidgetStyle() : TitleBackgroundBrush(FSlateNoResource()), ToolDetailsBackgroundBrush(FSlateNoResource()), TitleForegroundColor(FStyleColors::Panel)`
- L31 _public member_ `static const FName TypeName;`
- L32 _public function_ `virtual const FName GetTypeName() const override`
- L34 _public prototype_ `static const FToolkitWidgetStyle& GetDefault();`
- L35 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L38 _public member_ `FSlateBrush TitleBackgroundBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L39 _public prototype_ `FToolkitWidgetStyle& SetTitleBackgroundBrush(const FSlateBrush& InPaletteTitleBackgroundBrush);`
- L42 _public member_ `FSlateBrush ToolDetailsBackgroundBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L43 _public prototype_ `FToolkitWidgetStyle& SetToolDetailsBackgroundBrush(const FSlateBrush& InToolDetailsBackgroundBrush);`
- L46 _public member_ `FSlateColor TitleForegroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L47 _public prototype_ `FToolkitWidgetStyle& SetTitleForegroundColor(const FSlateColor& InTitleForegroundColor);`
- L50 _public member_ `FMargin TitlePadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L51 _public prototype_ `FToolkitWidgetStyle& SetTitlePadding(const FMargin& InTitlePadding);`
- L54 _public member_ `FMargin ActiveToolTitleBorderPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L55 _public prototype_ `FToolkitWidgetStyle& SetActiveToolTitleBorderPadding(const FMargin& InActiveToolTitleBorderPadding);`
- L58 _public member_ `FMargin ToolContextTextBlockPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L59 _public prototype_ `FToolkitWidgetStyle& SetToolContextTextBlockPadding(const FMargin& InToolContextTextBlockPadding);`
- L62 _public member_ `FSlateFontInfo TitleFont;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L63 _public prototype_ `FToolkitWidgetStyle& SetTitleFont(const FSlateFontInfo& InTitleFont);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/Inputs/BuilderInput.h` (Public)


#### class `UE::DisplayBuilders::FBuilderInput`  
`class FBuilderInput : public FLabelAndIconArgs`  
_L21-92_
- inherits: `FLabelAndIconArgs`
- desc: BuilderInput is the input representation for Builders and provides conversions to the various Slate types for inputs.
- L25 _public prototype_ `explicit FBuilderInput( FName InName = FName(), FText InLabel = FText::GetEmpty(), FSlateIcon InIcon = FSlateIcon(), EUserInterfaceActionType InUserInterfaceType = EUserInterfaceActionType::Button, FText InToolTip = FText::GetEmpty(), FText InDescription = FText::GetEmpty(), TArray<TSharedRef<FInputChord>> InActiveChords = {}, FInputChord InDefaultChords = FInputChord(), FName InUiStyle = NAME_None, FName InBindingContext = NAME_None, FName InBundle = NAME_None );`
- L41 _public prototype_ `~FBuilderInput();` — The destructor, destroys any command related information
- L44 _public member_ `FName Name;` — Name of the Input
- L47 _public member_ `EUserInterfaceActionType UserInterfaceType;` — The type of user interface to associated with this action
- L50 _public member_ `FText Description;` — Localized help text for the UI command
- L53 _public member_ `TArray<TSharedRef<FInputChord>> ActiveChords;` — Input commands that executes this action
- L56 _public member_ `FInputChord DefaultChords;` — The default input chords for the UI command (can be invalid)
- L59 _public member_ `FName UIStyle;` — Brush name for icon to use in tool bars and menu items to represent the UI command in its toggled on (checked) state
- L62 _public member_ `FName BindingContext;` — The context in which the UI command is active
- L65 _public member_ `FName Bundle;` — The bundle to group the UI command into. The bundle must have been added to the BindingContext first.
- L68 _public member_ `int32 Index;` — the index of the BuilderInput in whatever container it is in
- L71 _public member_ `FText Tooltip;` — the tooltip for the input
- L74 _public member_ `TSharedPtr<FUICommandInfo> UICommandInfo;` — FUICommandInfo, the basic Slate Class for defining user-facing commands, including their appearance and behavior in the UI
- L77 _public member_ `FButtonArgs ButtonArgs;` — FButtonArgs, a type which can be used to create buttons with FToolbarBuilder
- L80 _public member_ `static FBuilderInput NullInput;` — For use when we need a null state
- L85 _public prototype_ `bool IsNameNone() const;` — @return true if the input name is equivalent to Name_NONE
- L91 _private prototype_ `void InitializeCommandInfo();` — Initializes the related FUICommandInfo

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DisplayBuilders` (scope `UE`)

### `Source/Developer/WidgetRegistration/Public/Layout/CategoryDrivenContentBuilder.h` (Public)


#### class `FCategoryDrivenContentBuilder`  
`class FCategoryDrivenContentBuilder : public FCategoryDrivenContentBuilderBase`  
_L23-189_
- inherits: `FCategoryDrivenContentBuilderBase`
- desc: A builder which creates a widget that has a vertical toolbar category picker on the left hand side which populates the content on the right side.
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SWidget>, FProvideSelectedCategoryContent, const FName&) FProvideSelectedCategoryContent ProvideSelectedCategoryContentDelegate;`
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams( FUpdateContentForCategoryDelegate, FName, FText);`
- L36 _public prototype_ `const TArray<FName>& GetFavorites() const;` — @return the TArray<FName> of Favorites for this
- L44 _public prototype_ `TSharedRef<SWidget> CreateFavoritesContextMenu( FString FavoritesItemName );` — @return the context menu containing an item to add or remove a favorite. If FavoritesItemName is a current favorite it will return a context menu with the proper item to add or remove the favorite @param FavoritesItemName the name of the Favorites item that would be toggled with the menu
- L51 _public prototype_ `TSharedRef<SWidget> CreateShowCategoryLabelsContextMenu();` — Returns the context menu containing an item to show or hide category labels. @param bInShowCategoryLabelsItemName the name of the Show Category Labels item that would be toggled with the menu
- L57 _public member_ `FUpdateContentForCategoryDelegate UpdateContentForCategoryDelegate;` — A delegate which provides the const FName& Command name as a parameter to indicates which category was clicked. The bound method should update this FCategoryDrivenContentBuilder's content based on the category that was chosen.
- L64 _public prototype_ `explicit FCategoryDrivenContentBuilder(FCategoryDrivenContentBuilderArgs& Args);` — initializes this FCategoryDrivenContentBuilder with the given FCategoryDrivenContentBuilderArgs @param Args the parameter object which provides the information to initialize this FCategoryDrivenContentBuilder
- L69 _public prototype_ `~FCategoryDrivenContentBuilder();` — destroys the FCategoryDrivenContentBuilder and frees any resources
- L74 _public prototype_ `virtual void InitializeCategoryToolbar() override;` — Initializes the data necessary to build the category toolbar
- L79 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Generate the widget built by this builder and return a shared pointer to it.
- L84 _public prototype_ `virtual void UpdateWidget() override;` — Refreshes the existing widget.
- L92 _public prototype_ `void SetShowNoCategorySelection( bool bInShowNoCategorySelection );` — Sets whether we should show that no category selected. If true, the category picker shows no selection and there is no category title. @param bInShowNoCategorySelection if true, the category picker will show no selection and the category title is not shown
- L99 _public prototype_ `void InitializeCategoryButtons(TArray<UE::DisplayBuilders::FBuilderInput> InBuilderInputArray);` — Initializes the category buttons with the given FBuilderInputs @param InBuilderInputArray the array of FBuilderInput instances that will initialize the Category buttons
- L104 _public prototype_ `void InitializeCategoryButtons();` — Initializes the category buttons with the given FBuilderInputs
- L111 _public prototype_ `void AddBuilder( TSharedRef<SWidget> Widget );` — Converts the SWidget Widget to a FSlateBuilder and adds it to the main content for the currently selected category @param Widget the SWidget to convert to an FSlateBuilder and add to the content for the current category
- L118 _public prototype_ `void FillWithBuilder( TSharedRef<SWidget> Widget );` — Converts the SWidget Widget to a FSlateBuilder and sets it as the entire main content for the currently selected category @param Widget the SWidget to convert to an FSlateBuilder and set as the content for the current category
- L123 _public prototype_ `void ClearCategoryContent();` — Clears the content for the currently selected category
- L129 _public prototype_ `void AddFavorite( FName InFavoriteCommandName );` — Adds the favorites with the name InFavoriteCommandName to the favorites list. If InFavoriteCommandName is already in the Favorites list, this is a no-op
- L137 _private prototype_ `virtual void UpdateContentForCategory( FName ActiveCategoryName = NAME_None, FText InActiveCategoryText = FText::GetEmpty() ) override;` — Given the active category name, return an SWidget to provide the content @param ActiveCategoryName the name of the Category that will be loaded, which will be the title in the header of the returned content
- L144 _private member_ `TMap<FName, UE::DisplayBuilders::FBuilderInput> CategoryNameToBuilderInputMap;` — A map of the Category FName to the TSharedRef<FBuilderInput> providing the information to instantiate the category buttons
- L149 _private member_ `TArray<FName> Favorites;` — The TArray of FNames which have been set as favorites
- L154 _private member_ `FName FavoritesCategoryName;` — the FName of the favorites Category
- L159 _private prototype_ `void ToggleFavorite( FName InFavoriteCommandName );` — Toggles the favorite with the name InFavoriteCommandName
- L164 _private prototype_ `void ToggleShowLabels();` — Toggles the visibility of the categories names
- L169 _private member_ `TArray<UE::DisplayBuilders::FBuilderInput> BuilderInputArray;` — The array of BuilderInputs, in the correct display order
- L172 _private member_ `TArray<TSharedRef<FSlateBuilder>> ChildBuilderArray;` — The array of FSlateBuilders that will build the content for the currently selected category
- L175 _private member_ `FText CategoryLabel;` — the FText label of the currently selected category
- L179 _private member_ `TSharedPtr<FSimpleTitleContainer> TitleContainer;` — the simple title container that has a header with the currently selected category name, and an empty body that will contain the category content
- L182 _private member_ `TSharedPtr<FColumnWrappingContainer> ColumnWrappingContainer;` — the column wrapping container that provides the body of the category content
- L185 _private member_ `bool bIsFilledWithWidget;` — if true, the content for the category should have a single widget fill the content
- L188 _private member_ `bool bShowNoCategorySelection;` — if true, we need to show no selection on the category picker and no category title, else we should show both

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DisplayBuilders` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SWidget>, FProvideSelectedCategoryContent, const FName&) FProvideSelectedCategoryContent ProvideSelectedCategoryContentDelegate;`
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams( FUpdateContentForCategoryDelegate, FName, FText);`

### `Source/Developer/WidgetRegistration/Public/Layout/CategoryDrivenContentBuilderBase.h` (Public)


#### class `FCategoryDrivenContentBuilderBase`  
`class FCategoryDrivenContentBuilderBase : public FToolElementRegistrationArgs`  
_L22-165_
- inherits: `FToolElementRegistrationArgs`
- desc: The FToolElementRegistrationArgs which is specified for Toolkits
- L44 _public prototype_ `explicit FCategoryDrivenContentBuilderBase( FName InBuilderName = "FCat` — A constructor for the FCategoryDrivenContentBuilderBase which defines the builder name @param InBuilderName the name for the builder
- L51 _public prototype_ `explicit FCategoryDrivenContentBuilderBase( FCategoryDrivenContentBuilderArgs& Args );` — A constructor for the FCategoryDrivenContentBuilderBase which takes a FCategoryDrivenContentBuilderArgs to initialize this @param Args the FCategoryDrivenContentBuilderArgs used to initialize this FCategoryDrivenContentBuilderBase
- L58 _public prototype_ `virtual void InitializeCategoryToolbar() = 0;` — Initializes the data necessary to build the category toolbar
- L65 _public prototype_ `void InitCategoryToolbarContainerWidget();` — Initializes the category toolbar container VBox, and the children inside it. On any repeat calls, the SVerticalBox created on the first pass will be emptied and the children repopulated.
- L74 _public prototype_ `void SetCategoryButtonLabelVisibility(EVisibility Visibility);` — Sets category button label visibility to Visibility. It also reinitializes the category toolbar data, as the toolbar's LabelVisibility member is now stale. @param Visibility If Visibility == EVisibility::Collapsed, the category button labels will be shown, else they will not be shown.
- L83 _public prototype_ `void SetCategoryButtonLabelVisibility(bool bIsCategoryButtonLabelVisible);` — Sets category button label visibility to Visibility. It also reinitializes the category toolbar data, as the toolbar's LabelVisibility member is now stale. @param bIsCategoryButtonLabelVisible If bIsCategoryButtonLabelVisible == true, the category button labels will be shown, else they will not be shown.
- L88 _public prototype_ `void RefreshCategoryToolbarWidget( bool bShouldReinitialize = false );` — refreshes the UI display of the category toolbar
- L91 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Implements the generation of the TSharedPtr<SWidget>
- L94 _public prototype_ `TSharedRef<SWidget> CreateToolbarWidget() const;` — Creates the Toolbar for the widget with the FUICommandInfos that load the Palettes
- L97 _public prototype_ `TSharedPtr<FToolBarBuilder> GetLoadPaletteToolbar();` — @return a TSharedPointer to the FToolbarBuilder with the FUICommandInfos that load the Palettes
- L100 _public member_ `TSharedPtr<FToolElement> VerticalToolbarElement;` — a TSharedPointer to the FToolElement for the vertical toolbar
- L103 _public member_ `FSimpleMulticastDelegate OnActivePaletteChanged;` — OnActivePaletteChanged is broadcast when the active palette changes to a different palette
- L106 _public member_ `FGetDecoratedButtonDelegate GetDecoratedButtonDelegate;` — Delegate that takes the default toolbar button created by this as a parameter, adds any decorator needed and returns the new widget
- L111 _private member_ `TSharedPtr<SWidget> ToolkitWidget;` — The SWidget that is the whole Toolkit
- L115 _private member_ `TSharedPtr<SVerticalBox> CategoryToolbarVBox;` — The SVerticalBox which contains the category toolbar
- L118 _private member_ `TSharedPtr<SVerticalBox> ToolkitWidgetContainerVBox;` — The SVerticalBox which holds the entire Toolkit
- L125 _protected prototype_ `void CreateWidget();` — Creates the SWidget
- L127 _protected prototype_ `FName GetCategoryToolBarStyleName() const;`
- L129 _protected prototype_ `virtual void UpdateContentForCategory( FName ActiveCategoryName = NAME_None, FText InActiveCategoryText = FText::GetEmpty() ) = 0;`
- L132 _protected member_ `TSharedPtr<SVerticalBox> MainContentVerticalBox;` — The SVerticalBox which holds the main content ~ -all but the Category chooser
- L135 _protected member_ `static FToolElementRegistry ToolRegistry;` — the tool element registry this class will use to register UI tool elements
- L138 _protected member_ `ECategoryReclickBehavior CategoryReclickBehavior = ECategoryReclickBehavior::NoEffect;` — Specifies what happens if you click the category button of an already-active category
- L141 _protected member_ `FToolkitWidgetStyle Style;` — The current FToolkitWidgetStyle
- L145 _protected member_ `EVisibility CategoryButtonLabelVisibility;` — If CategoryButtonLabelVisibility == EVisibility::Visible, the category button labels are visible, else they are not displayed. By default the selected category button labels are Visible
- L150 _protected member_ `EVisibility CategoryToolbarVisibility = EVisibility::Visible;` — Is the Category toolbar visible?
- L153 _protected member_ `TSharedPtr<FUICommandList> LoadToolPaletteCommandList;` — A TSharedPointer to the FUICommandList for the FUICommandInfos which load a tool palette
- L156 _protected member_ `TSharedPtr<FToolBarBuilder> LoadPaletteToolBarBuilder;` — The toolbar builder for the toolbar which has the FUICommandInfos which load the various palettes
- L159 _protected member_ `FName BuilderName;` — Name of this builder
- L164 _protected member_ `FName ActiveCategoryName;` — the name of the currently selected/active category

#### enum `FCategoryDrivenContentBuilderBase::ECategoryReclickBehavior`  
`enum class ECategoryReclickBehavior : uint8`  
_L27-38_
- desc: Used to specify what happens when you click the category button of a category that is already active.
- L30 _public enumerator_ `NoEffect` — Do nothing if the same category button is clicked.
- L33 _public enumerator_ `ToggleOff` — Toggle the active category off, so no category is active.
- L37 _public enumerator_ `TreatAsChanged` — Do the same thing that would be done if we were switching from a different category. Note that this will trigger OnActivePaletteChanged.

#### class `FCategoryDrivenContentBuilderArgs`  
`class FCategoryDrivenContentBuilderArgs`  
_L170-206_
- desc: A struct to provide arguments for a FCategoryDrivenContentBuilderBase
- L179 _public prototype_ `FCategoryDrivenContentBuilderArgs( FName InBuilderName, const UE::DisplayBuilders:: FBuilderKey& InKey = UE::DisplayBuilders::FBuilderKeys::Get().None() );` — Constructor taking the builder name and the FBuilderKey @param InBuilderName the name of the builder @param InKey the FBuilderKey for this
- L183 _public member_ `UE::DisplayBuilders::FBuilderKey Key;` — the FBuilderKey for this
- L186 _public member_ `FName BuilderName;` — Name of this builder
- L190 _public member_ `bool bShowCategoryButtonLabels;` — If bShowCategoryButtonLabels == true, the category button labels should be visible, else they are not displayed
- L193 _public member_ `FCategoryDrivenContentBuilderBase::ECategoryReclickBehavior CategoryReclickBehavior;` — Specifies what happens if you click the category button of an already-active category
- L196 _public member_ `FName FavoritesCommandName;` — The FName of the favorites Category, if one exists
- L199 _public member_ `FText CategoryLabel;` — The label/title of the initially selected category
- L202 _public member_ `FName ActiveCategoryName;` — The name of the initially selected category
- L205 _public member_ `FGetDecoratedButtonDelegate GetDecoratedButtonDelegate;` — Delegate that takes the default toolbar button created by this as a parameter, adds any decorator needed and returns the new widget

### `Source/Developer/WidgetRegistration/Public/Layout/SeparatorBuilder.h` (Public)


#### class `FSeparatorSize`  
`class FSeparatorSize`  
_L13-40_
- desc: Provides a type that will hold the size for a FSeparatorBuilder
- L18 _private member_ `float Magnitude;` — The magnitude of the size ~ the greater the Magnitude the larger the Separator.
- L25 _private function_ `FSeparatorSize(float InMagnitude): Magnitude(InMagnitude)` — Constructs the Separator Size with a Magnitude o InMagnitude @param InMagnitude
- L34 _public function_ `float ToFloat() const` — Converts the Size to a float value

#### struct `FSeparatorSizes`  
`struct FSeparatorSizes`  
_L45-61_
- desc: A struct to contain the possible sizes for a Separator
- L48 _public member_ `static inline const FSeparatorSize XSmall{1.0f};` — the size of an extra small (1 slate unit) Separator
- L51 _public member_ `static inline const FSeparatorSize Small{2.0f};` — the size of a small (2 slate unit) Separator
- L54 _public member_ `static inline const FSeparatorSize Medium{4.0f};` — the size of a medium (4 slate unit) Separator
- L57 _public member_ `static inline const FSeparatorSize Large{8.0f};` — the size of a large (8 slate unit) Separator
- L60 _public member_ `static inline const FSeparatorSize XLarge{16.0f};` — the size of an extra large (16 slate unit) Separator

#### class `FSeparatorBuilder`  
`class FSeparatorBuilder final : public FToolElementRegistrationArgs`  
_L66-165_
- inherits: `FToolElementRegistrationArgs`
- desc: FSeparatorBuilder instances will build a TSharedRef<SSeparator>
- L73 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Implements the generation of the TSharedPtr<SWidget>
- L80 _public prototype_ `TSharedRef<SSeparator> ToSSeparatorSharedRef();` — Generates the SSeparator and returns the TSharedRef<SSeparator> as a reference to it @return the TSharedRef<SSeparator> as a reference to the generated SSeparator
- L89 _public prototype_ `TSharedRef<SSeparator> operator*();` — Generates the SSeparator and returns the TSharedRef<SSeparator> as a reference to it. This provides some convenience syntax to generate the widget and get a reference to it in a concise way. @return the TSharedRef<SSeparator> as a reference to the generated SSeparator
- L98 _public prototype_ `FSeparatorBuilder& InitializeSize(const FSeparatorSize& NewSize);` — Initializes the size of the separator. If called after the widget creation (that is, a call to GenerateWidget) this call will have no effect. @param NewSize the FSeparatorSize& that will provide the size for the Separator @return this FSeparatorBuilder to enable cascading.
- L108 _public prototype_ `FSeparatorBuilder& SetColor(const EStyleColor& NewColor);` — Sets the color of the Separator. This will update the color of the Separator even after widget creation. @param NewColor the EStyleColor to set the color of the SSeparator. Note that the EStyleColor is a key into the color table, so providing an EStyleColor such as EStyleColor::Panel will honor updates to changes in themes for that EStyleColor immediately. @return this FSeparatorBuilder to enable cascading.
- L116 _public function_ `FSeparatorBuilder& BindVisibility(TAttribute<EVisibility> NewVisibility)` — Binds the Visibility of the Separator to a TAttribute for continuous update. @param NewVisibility the TAttribute<EVisibility> to bind for the SSeparator. @return this FSeparatorBuilder to enable cascading.
- L135 _private prototype_ `FSeparatorBuilder(EStyleColor InColor = EStyleColor::Background, EOrientation InOrientation = Orient_Horizontal, FSeparatorSize InSize = FSeparatorSizes::Small, const FSlateBrush* InImage = FAppStyle::GetBrush("Thin` — Constructs the FSeparatorBuilder. This is private to keep the end user API simple. By starting with a template callers should not have a need to construct an FSeparatorBuilder. @param InColor the EStyleColor to provide the color for this Separator @param InOrientation the EOrientation that sets the orientation for this Separator @param InSize the FSeparatorSize that sets the size for this Separator @param InImage the const FSlateBrush* which specifies the FSlateBrush to use for this Separator
- L143 _private member_ `const FSlateBrush* Image = FAppStyle::GetBrush("Thi` — The const FSlateBrush* for the SSeparator
- L148 _private member_ `EOrientation Orientation = Orient_Horizontal;` — The EOrientation that specifies whether this is a horizontal or vertical Separator
- L153 _private member_ `TAttribute<FSlateColor> SlateColor = EStyleColor::Background;` — The FSlateColor that specifies the Color for this Separator.
- L158 _private member_ `float Size = FSeparatorSizes::Small.ToFloat();` — The FSeparatorSize that specifies the Size for this Separator.
- L163 _private member_ `TAttribute<EVisibility> Visibility = EVisibility::Visible;` — The TAttribute<EVisibility> which will provide the Visibility for the Separator

### `Source/Developer/WidgetRegistration/Public/Layout/SeparatorTemplates.h` (Public)


#### struct `FSeparatorTemplates`  
`struct FSeparatorTemplates`  
_L11-39_
- desc: A struct which holds methods that provide templates for FSeparatorBuilders. The provided FSeparatorBuilders can be updated as needed with the FSeparatorBuilder API.
- L20 _public prototype_ `static FSeparatorBuilder SmallVerticalBackgroundNoBorder();` — Creates and returns a small (2 Slate Unit), vertical FSeparatorBuilder with the color of the theme specified color for Background @return a small (2 Slate Unit), vertical FSeparatorBuilder with the color of the theme specified color for Background
- L29 _public prototype_ `static FSeparatorBuilder SmallHorizontalBackgroundNoBorder();` — Creates and returns a small (2 Slate Unit), horizontal FSeparatorBuilder set to the color of the theme specified color for Background @return a small (2 Slate Unit), horizontal FSeparatorBuilder with the color of the theme specified color for Background
- L38 _public prototype_ `static FSeparatorBuilder SmallHorizontalPanelNoBorder();` — Creates and returns a small (2 Slate Unit), horizontal FSeparatorBuilder set to the color of the theme specified color for Panels. @return a small (2 Slate Unit), horizontal FSeparatorBuilder with the color of the theme specified color for Panels.

### `Source/Developer/WidgetRegistration/Public/Persistence/BuilderPersistenceManager.h` (Public)


#### struct `FPersistedNameArray`  
`struct FPersistedNameArray`  
_L18-25_
- reflection: `USTRUCT()`
- desc: Manages an array of FNames to persist
- L24 _public member_ `TArray<FName> ArrayOfNamesToPersist;` — `UPROPERTY()`

#### struct `FPersistedBool`  
`struct FPersistedBool`  
_L31-38_
- reflection: `USTRUCT()`
- desc: Manages a Bool to persist
- L37 _public member_ `bool PersistedBool = false;` — `UPROPERTY()`

#### class `UBuilderPersistenceManager`  
`class UBuilderPersistenceManager : public UEditorConfigBase`  
_L45-143_
- reflection: `UCLASS(MinimalAPI, EditorConfig="BuilderPersistenceManager")`
- inherits: `UEditorConfigBase`
- desc: The Builder Persistence Manager handles persistence for Builders through use of FBuilderKeys
- L55 _public prototype_ `TArray<FName> GetFavoritesNames( const UE::DisplayBuilders::FBuilderKey& Key );` — @return the default named favorites array for the Builder with FBuilderKey Key, if one exists, else an empty array is returned @param Key the FBuilderKey to retrieve the favorites for
- L63 _public prototype_ `void PersistFavoritesNames( const UE::DisplayBuilders::FBuilderKey& Key, TArray<FName>& Favorites );` — Sets the default named favorites array for the Builder with FBuilderKey Key @param Key the FBuilderKey to retrieve the favorites for @param Favorites the array of FNames for the favorites to persist
- L71 _public prototype_ `void PersistShowButtonLabels( const UE::DisplayBuilders::FBuilderKey& Key, bool bValue );` — Sets the default button label EVisisbility for the Builder with FBuilderKey Key @param Key the FBuilderKey to retrieve the button label Bool for @param Bool the bool for the button labels to persist
- L79 _public prototype_ `bool GetShowButtonLabels( const UE::DisplayBuilders::FBuilderKey& Key, bool bDefaultValue );` — @return the bool or the buttons labels for the Builder with FBuilderKey Key, if one exists, else an empty array is returned @param Key the FBuilderKey to retrieve the button label bool @param PersistedBoolIfNoneFound the Bool to set as the new persistence value, if one is not found
- L84 _public prototype_ `static void Initialize();` — Initialize the Persistence manager
- L89 _public prototype_ `static void ShutDown();` — Shuts down the Persistence manager
- L94 _public function_ `static UBuilderPersistenceManager* Get()` — Gets the singleton for the Builder Persistence Manager
- L103 _private member_ `TMap<FString, FPersistedNameArray> SavedNameToPersistedFNameArrayMap;` — `UPROPERTY(meta=(EditorConfig))`
- L106 _private member_ `TMap<FString, FPersistedBool> SavedNameToPersistedBoolMap;` — `UPROPERTY(meta=(EditorConfig))`
- L108 _private member_ `static TObjectPtr<UBuilderPersistenceManager> Instance;`
- L117 _private prototype_ `TArray<FName> GetPersistedArrayOfNames( const UE::DisplayBuilders::FBuilderKey& Key, FName PersistenceKeySuffix );` — @return the an array for the Builder with FBuilderKey Key and the suffix that the array was persisted with, if one exists, else an empty array is returned @param Key the FBuilderKey to retrieve the FNames array for @param PersistenceKeySuffix the suffix to add to the FBuilderKey to persist the array of FNames with
- L125 _private prototype_ `void PersistArrayOfNames( const UE::DisplayBuilders::FBuilderKey& Key, FName PersistenceKeySuffix, TArray<FName>& ArrayOfNamesToPersist );` — Persists the array of FNames the Builder with FBuilderKey Key and suffix PersistenceKeySuffix @param Key the FBuilderKey to retrieve the favorites for @param PersistenceKeySuffix the suffix added to the FBuilderKey to persist the array of FNames with
- L134 _private prototype_ `bool GetPersistedBool( const UE::DisplayBuilders::FBuilderKey& Key, FName PersistenceKeySuffix, bool bDefaultValue );` — Returns the bool for the Builder with FBuilderKey Key and the suffix that the array was persisted with, if one exists, else an empty array is returned @param Key the FBuilderKey to retrieve the bool @param PersistenceKeySuffix the suffix to add to the FBuilderKey to get the bool with @param bDefaultValue the Bool to set as the new persistence value, if one is not found
- L142 _private prototype_ `void PersistBool( const UE::DisplayBuilders::FBuilderKey& Key, FName PersistenceKeySuffix, bool bInPersistedBool );` — Persists the Bool the Builder with FBuilderKey Key and suffix PersistenceKeySuffix @param Key the FBuilderKey to retrieve the favorites for @param PersistenceKeySuffix the suffix added to the FBuilderKey to persist the Bool with

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/Styles/SlateBrushTemplates.h` (Public)


#### struct `FSlateBrushTemplates`  
`struct UE_DEPRECATED(5.8, "This struct is deprecated. You should use FAppStyle instead") FSlateBrushTemplates`  
_L12-46_
- desc: A const FSlateBrush* Factory
- L16 _public prototype_ `static const FSlateBrush* DragHandle();` — Images UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush("VerticalBoxDragIndicatorShort") instead
- L18 _public prototype_ `static const FSlateBrush* ThinLineHorizontal();` — UE_DEPRECATED 5.8 : "Use FAppStyle::GetBrush("ThinLine.Horizontal") instead
- L22 _public prototype_ `static const FSlateBrush* Dropdown();` — Colors UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush("Brushes.Dropdown") instead
- L24 _public prototype_ `static const FSlateBrush* Transparent();` — UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush("Brushes.Transparent") instead
- L26 _public prototype_ `static const FSlateBrush* Panel();` — UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush("Brushes.Panel") instead
- L28 _public prototype_ `static const FSlateBrush* Recessed();` — UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush("Brushes.Recessed") instead
- L36 _public prototype_ `const FSlateBrush* GetBrushWithColor(EStyleColor Color);` — UE_DEPRECATED 5.8 : Use FAppStyle::GetBrush() with a predefined brush name in StyleSheets instead
- L42 _public prototype_ `static FSlateBrushTemplates& Get();` — UE_DEPRECATED 5.8: This struct is deprecated. You should use FAppStyle instead
- L45 _public member_ `TMap<EStyleColor, TUniquePtr<FSlateColorBrush>> EStyleColorToSlateBrushMap;` — the map of EStyleColor to const FSlateColorBrush UniquePtr

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/ToolElementRegistry.h` (Public)


#### enum `EToolElement`  
`enum class EToolElement : uint32`  
_L13-19_
- desc: An enum to provide the type of Tool Element
- L15 _public enumerator_ `Toolbar = 0`
- L16 _public enumerator_ `Toolkit`
- L17 _public enumerator_ `Separator`
- L18 _public enumerator_ `Section`

#### class `FToolElementRegistrationArgs`  
`class FToolElementRegistrationArgs : public TSharedFromThis<FToolElementRegistrationArgs>`  
_L25-70_
- inherits: `TSharedFromThis<FToolElementRegistrationArgs>`
- desc: A class which provides the data necessary to generate a widget. This class should be extended and used to hold whatever information is needed to generate or update the widgets that make up the tool, and implement the virtual widget methods
- L32 _public prototype_ `FToolElementRegistrationArgs(EToolElement InToolElementType);` — The constructor, which takes an EToolElement which will define the type of Tool Element
- L35 _public prototype_ `FToolElementRegistrationArgs(FName InStyleClassName);` — The constructor, which takes an EToolElement which will define the type of Tool Element
- L42 _public prototype_ `FToolElementRegistrationArgs( UE::DisplayBuilders::FBuilderKey InBuilderKey );` — The constructor, which takes an FBuilderKey which will define the type of Tool Element @param InBuilderKey the FBuilderKey that provides the Key for this builder
- L45 _public prototype_ `virtual ~FToolElementRegistrationArgs() = default;` — default destructor in case any subclasses need to provide a destructor
- L48 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget();` — Implements the generation of the TSharedPtr<SWidget>
- L51 _public prototype_ `TSharedRef<SWidget> GenerateWidgetSharedRef();` — Implements the generation of the TSharedRef<SWidget>
- L54 _public prototype_ `virtual void UpdateWidget();` — Updates/reloads this widget. This should be called after a consumer has changed any Data in this
- L57 _public prototype_ `virtual void ResetWidget();` — Resets the widget to its initial state
- L60 _public member_ `const EToolElement ToolElementType;` — The type of tool element this is Registration args for
- L63 _public member_ `const FName StyleClassName;` — The style class name
- L69 _public member_ `const UE::DisplayBuilders::FBuilderKey BuilderKey;` — the FBuilderKey for this. This provides a key into persistence, if any exists for the builder, along with other things.

#### class `FToolElementRegistrationKey`  
`class FToolElementRegistrationKey : public TSharedFromThis<FToolElementRegistrationKey>`  
_L73-95_
- inherits: `TSharedFromThis<FToolElementRegistrationKey>`
- desc: Serves as a key into the FToolElementRegistry of FToolElements
- L83 _public prototype_ `FToolElementRegistrationKey(FName InName, EToolElement InToolElementType );` — Constructor for FToolElementRegistrationKey. @param InName the FName that will be part of the compound key for the FToolElement this denotes @param InToolElementType the EToolElementType that will be part of the compound key for the FToolElement this denotes
- L86 _public member_ `FName Name;` — the FName that will be part of the compound key for the FToolElement this denotes
- L89 _public member_ `EToolElement ToolElementType;` — the EToolElementType that will be part of the compound key for the FToolElement this denotes
- L91 _public prototype_ `FString GetKeyString();`
- L94 _private member_ `FString KeyString;`

#### class `FToolElement`  
`class FToolElement : public FToolElementRegistrationKey`  
_L98-135_
- inherits: `FToolElementRegistrationKey`
- desc: Represents one Tool Element, and is responsible for displaying the UI for that element
- L112 _public prototype_ `FToolElement( const FName InName, TSharedRef<FToolElementRegistrationArgs> InBuilderArgs);` — FToolElement constructor @param InName the FName of the FToolElement @param InBuilderArgs the shared reference to the FToolElementRegistrationArgs. Need to have a shared reference here so that if the registered outlives the registrar, we maintain a copy
- L122 _public prototype_ `TSharedRef<SWidget> GenerateWidget();` — a convenience pass through method to the FToolElementRegistrationArgs GenerateWidget method which generates the TSharedRef<SWidget> @return the TSharedRef<SWidget> which makes up the UI for this tool element
- L129 _public prototype_ `void SetRegistrationArgs(TSharedRef<FToolElementRegistrationArgs> RegistrationArgs);` — Sets the FToolElementRegistrationArgs for the this tool element to RegistrationArgs @param RegistrationArgs the FToolElementRegistrationArgs for the this tool element
- L133 _private member_ `TSharedRef<FToolElementRegistrationArgs> RegistrationArgs;` — the FToolElementRegistrationArgs for the this tool element

#### class `FToolElementRegistry`  
`class FToolElementRegistry`  
_L138-185_
- desc: A Registry for FToolElements, where the FToolElements will generate the UI for a certain tool
- L147 _public prototype_ `TSharedPtr<FToolElement> GetToolElementSP( FToolElementRegistrationKey& ToolElementKey);` — Gets the TSharedPtr<FToolElement> for the given FToolElementRegistrationKey& tool element key @param ToolElementKey the given FToolElementRegistrationKey& tool element key for which to find the tool element
- L148 _public prototype_ `explicit FToolElementRegistry();`
- L150 _public prototype_ `static FToolElementRegistry& Get();`
- L165 _public prototype_ `TSharedRef< SWidget > GenerateWidget( TSharedRef<FToolElementRegistrationKey> ToolElementKeySR, TSharedPtr<FToolElementRegistrationArgs> RegistrationArgsSP = nullptr, bool bUpdateRegistrationArgs = false);` — Generates the widget for the tool element denoted by the FToolElementRegistrationKey, using the specified TSharedPtr<FToolElementRegistrationArgs> if provided (otherwise it will use the default registered registration arguments. If bUpdateRegistrationArgs is set to true and RegistrationArgsSP is not nullptr, the specified registration args will replace the existing ones for the tool element. @param ToolElementKeySR the TSharedRef<FToolElementRegistrationKey> which is the key to the tool element for which we want to generate the widget @param RegistrationArgsSP The SharedPtr to the FToolElementRegistrationArgs for the tool element for which which we want to generate the widget @param bUpdateRegistrationArgs a bool that indicates whether we store any provided FToolElementRegistrationArgs as the new FToolElementRegistrationArgs for this tool element
- L174 _public prototype_ `void RegisterElement(const TSharedRef<FToolElement> ToolElement);` — registers the FToolElement ToolElement @param ToolElement the FToolElement that is to be registered
- L180 _public prototype_ `void UnregisterElement(const TSharedRef<FToolElement> ToolElement);` — Unregisters the FToolElement ToolElement @param ToolElement the FToolElement that is to be registered
- L184 _private member_ `TMap<FString, TSharedPtr<FToolElement>> ToolElementKeyToToolElementMap;` — the Map of tool element Key to tool element

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/ToolbarRegistrationArgs.h` (Public)


#### class `FToolbarRegistrationArgs`  
`class FToolbarRegistrationArgs : public FToolElementRegistrationArgs`  
_L11-33_
- inherits: `FToolElementRegistrationArgs`
- desc: A class that provides the FToolbarRegistrationArgs for a UE toolbar
- L21 _public prototype_ `FToolbarRegistrationArgs(TSharedRef<FToolBarBuilder> InToolBarBuilder);` — the constructor for FToolbarRegistrationArgs @param InToolBarBuilder a TSharedRef to the FToolBarBuilder  which will be used by this to build up a toolbar SWidget
- L28 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;` — Generates the TSharedPtr<SWidget> for a toolbar @return the the TSharedPtr<SWidget> for a toolbar
- L31 _public member_ `TSharedRef<FToolBarBuilder> ToolBarBuilder;` — The FToolBarBuilder object used to build up a toolbar widget

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/ToolkitBuilder.h` (Public)


#### struct `FToolkitSections`  
`struct FToolkitSections`  
_L20-29_
- L22 _public member_ `TSharedPtr<STextBlock> ModeWarningArea = nullptr;`
- L23 _public member_ `TSharedPtr<STextBlock> ToolWarningArea = nullptr;`
- L24 _public member_ `TSharedPtr<SWidget> ToolPresetArea = nullptr;`
- L25 _public member_ `TSharedPtr<IDetailsView> DetailsView = nullptr;`
- L26 _public member_ `TSharedPtr<SWidget> ToolHeader = nullptr;`
- L27 _public member_ `TSharedPtr<SWidget> Header = nullptr;`
- L28 _public member_ `TSharedPtr<SWidget> Footer = nullptr;`

#### struct `FToolPalette`  
`struct FToolPalette : TSharedFromThis<FToolPalette>`  
_L32-54_
- inherits: `TSharedFromThis<FToolPalette>`
- desc: A struct that provides the data for a single tool Palette
- L34 _public function_ `FToolPalette(TSharedPtr<FUICommandInfo> InLoadToolPaletteAction, const TArray<TSharedPtr< FUICommandInfo >>& InPaletteActions) : LoadToolPaletteAction(InLoadToolPaletteAction)`
- L47 _public member_ `const TSharedPtr<FUICommandInfo> LoadToolPaletteAction;` — The FUICommandInfo button which loads a particular set of toads
- L50 _public member_ `TArray<TSharedRef<FButtonArgs>> PaletteActions;` — The ButtonArgs that has the data to initialize the buttons in the FToolPalette loaded by LoadToolPaletteAction
- L53 _public member_ `TSharedPtr<FUICommandList> PaletteActionsCommandList;` — The FUICommandList associated with this Palette

#### struct `FEditablePalette`  
`struct FEditablePalette : public FToolPalette`  
_L57-102_
- inherits: `FToolPalette`
- desc: An FToolPalette to which you can add and remove actions
- L59 _public prototype_ `FEditablePalette(TSharedPtr<FUICommandInfo> InLoadToolPaletteAction, TSharedPtr<FUICommandInfo> InAddToPaletteAction, TSharedPtr<FUICommandInfo> InRemoveFromPaletteAction, FName InEditablePaletteName = FName(), FGetEditableToolPaletteConfigManager InGetConfigManager = FGetEditableToolPaletteConfigManager());`
- L66 _public member_ `const TSharedPtr<FUICommandInfo> AddToPaletteAction;` — The FUICommandInfo which adds an action to this palette
- L69 _public member_ `const TSharedPtr<FUICommandInfo> RemoveFromPaletteAction;` — The FUICommandInfo which removes an action to this palette
- L72 _public member_ `FSimpleDelegate OnPaletteEdited;` — Delegate used by FToolkitBuilder that is called when an item is added/removed from the palette
- L79 _public prototype_ `bool IsInPalette(const FName CommandName) const;` — Given a reference to a FUICommandInfo, returns whether it is in the current Palette @param CommandName the name of the FUICommandInfo queried as to whether it is in the Palette
- L81 _public prototype_ `TArray<FString> GetPaletteCommandNames() const;`
- L83 _public prototype_ `void AddCommandToPalette(const FString CommandNameString);`
- L85 _public prototype_ `void RemoveCommandFromPalette(const FString CommandNameString);`
- L89 _protected prototype_ `void SaveToConfig();`
- L91 _protected prototype_ `void LoadFromConfig();`
- L95 _protected member_ `TArray<FString> PaletteCommandNameArray;` — The TArray of Command names that are the current FuiCommandInfo actions in this Palette
- L98 _protected member_ `FName EditablePaletteName;` — The (unique) name attached to this palette, enables saving the palette contents into config if provided
- L101 _protected member_ `FGetEditableToolPaletteConfigManager GetConfigManager;` — Delegate used to check if we have a config manager and get it

#### struct `FToolkitBuilderArgs`  
`struct FToolkitBuilderArgs : public FCategoryDrivenContentBuilderArgs`  
_L109-125_
- inherits: `FCategoryDrivenContentBuilderArgs`
- desc: A simple struct to carry initialization data for an FToolkitBuilder
- L111 _public prototype_ `FToolkitBuilderArgs(const FName InToolbarCustomizationName);`
- L114 _public member_ `FName ToolbarCustomizationName;` — Name of the toolbar this mode uses and can be used by external systems to customize that mode toolbar
- L117 _public member_ `TSharedPtr<FUICommandList> ToolkitCommandList;` — A TSharedPointer to the FUICommandList for the current mode
- L120 _public member_ `TSharedPtr<FToolkitSections> ToolkitSections;` — The FToolkitSections which holds the sections defined for this Toolkit
- L124 _public member_ `EVisibility SelectedCategoryTitleVisibility;` — If SelectedCategoryTitleVisibility == EVisibility::Visible, the selected category title is visible, else it is not displayed

#### class `FToolkitBuilder`  
`class FToolkitBuilder : public FCategoryDrivenContentBuilderBase`  
_L127-351_
- inherits: `FCategoryDrivenContentBuilderBase`
- L137 _public prototype_ `explicit FToolkitBuilder( FName ToolbarCustomizationName, TSharedPtr<FUICommandList> InToolkitCommandList, TSharedPtr<FToolkitSections> InToolkitSections);` — Constructor @param ToolbarCustomizationName the name of the  customization fr the category toolbar @param InToolkitCommandList  the toolkit FUICommandList @param InToolkitSections The FToolkitSections for this toolkit builder
- L143 _public prototype_ `explicit FToolkitBuilder(FToolkitBuilderArgs& Args);` — default constructor
- L147 _public prototype_ `void SetActivePaletteCommandsVisibility(EVisibility Visibility);`
- L152 _public prototype_ `EVisibility GetActivePaletteCommandsVisibility() const;` — @return the Visibility state of the active palette command buttons
- L159 _public prototype_ `void AddPalette(TSharedPtr<FToolPalette> Palette);` — Adds the FToolPalette Palette to this FToolkitBuilder @param Palette the FToolPalette being added to this FToolkitBuilder
- L166 _public prototype_ `void AddPalette(TSharedPtr<FEditablePalette> Palette);` — Adds the FEditablePalette Palette to this FToolkitBuilder @param Palette the FEditablePalette being added to this FToolkitBuilder
- L169 _public prototype_ `virtual void ResetWidget() override final;` — Cleans up any previously set data in this FToolkitBuilder and reset the members to their initial values
- L173 _public prototype_ `virtual void UpdateWidget() override;` — Updates the Toolkit. This should be called after any changes to the data of this FToolkitBuilder, and the UI will be regenerated to reflect it.
- L176 _public prototype_ `bool HasActivePalette() const;` — @return true is there is an active palette selected, else it returns false
- L183 _public prototype_ `void SetActivePaletteOnLoad(const FUICommandInfo* Command);` — Loads the palette for the FUICommandInfo Command on first visit to the mode. @param Command the FUICommandInfo which defines the palette that will be loaded on first visit to the mode.
- L191 _public prototype_ `ECheckBoxState IsActiveToolPalette(FName CommandName) const;` — @return true if the FUICommandInfo with the name CommandName is the active tool palette, else it returns false @param CommandName the name of the FUICommandInfo we are checking to see if it is the active tool palette
- L196 _public prototype_ `void InitializeCategoryToolbar() override;` — Initializes the data necessary to build the category toolbar
- L206 _public prototype_ `void InitializeCategoryToolbar(bool bInitLoadToolPaletteMap);` — Initializes the data necessary to build the category toolbar @param bInitLoadToolPaletteMap If true, the map which holds the load action names as keys and the ToolPalettes as value will be cleared and available to add new data when the method completes. Otherwise, the map will keep the load action name to ToolPalette mappings that it was initially set up with.
- L213 _public prototype_ `void SetCategoryToolbarVisibility(EVisibility Visibility);` — Sets the visibility of the category toolbar. Call RefreshCategoryToolbarWidget to apply changes in visibility. @param Visibility the visibility state to apply
- L220 _public prototype_ `void SetActiveToolDisplayName(FText InActiveToolDisplayName);` — Sets the display name for the active tool @param InActiveToolDisplayName an FText that holds the name of the currently active tool
- L225 _public prototype_ `FText GetActiveToolDisplayName() const;` — @returns the display name for the active tool
- L233 _public prototype_ `void GetCommandsForEditablePalette(TSharedRef<FEditablePalette> EditablePalette, TArray<TSharedPtr<const FUICommandInfo>>& OutCommands);` — Fills the OutCommands TArray with TSharedPtr<const FUICommandInfo> instances that are present in the FEditablePalette EditablePalette @param EditablePalette the FEditablePalette whose FUICommandInfo
- L238 _public prototype_ `FName GetActivePaletteName() const;` — @returns the name of the Active Palette if one is available, else it returns NAME_NONE
- L241 _public member_ `FName ToolbarCustomizationName;` — Name of the toolbar this mode uses and can be used by external systems to customize that mode toolbar
- L244 _public member_ `TMap<FString, TSharedPtr<FButtonArgs>> PaletteCommandNameToButtonArgsMap;` — The map of the command name to the ButtonArgs for it
- L247 _public member_ `TMap<FString, TSharedPtr<FToolPalette>> LoadCommandNameToToolPaletteMap;` — The map of the command name to the ButtonArgs for it
- L250 _public member_ `TMap<FString, TSharedPtr<const FUICommandInfo>> PaletteCommandInfos;` — Map of command name to the actual command for all commands belonging to this palette
- L253 _public member_ `TSharedPtr<FUICommandList> ToolkitCommandList;` — A TSharedPointer to the FUICommandList for the current mode
- L256 _public member_ `TArray<TSharedRef<FEditablePalette>> EditablePalettesArray;` — A TArray of FEditablePalettes, kept to update the commands which are on them
- L259 _public member_ `TSharedPtr<FToolPalette> ActivePalette;` — The tool palette which is currently loaded/active
- L262 _public member_ `TSharedPtr<SVerticalBox> ToolPaletteWidget;` — The SVerticalBox which holds the tool palette (the Buttons which load each tool)
- L265 _public member_ `TMap<FName, TSharedPtr<FToolBarBuilder>> LoadCommandNameToPaletteToolbarBuilderMap;` — the FName of each Load palette command to the FToolbarBuilder for the palette which it loads
- L268 _public prototype_ `void UpdateEditablePalette(TSharedRef<FEditablePalette> EditablePalette);` — Updates the Editable Palette with any commands that are on it
- L270 _public prototype_ `void OnEditablePaletteEdited(TSharedRef<FEditablePalette> EditablePalette);`
- L273 _public prototype_ `void ResetToolPaletteWidget();` — Resets the tool palette widget, on which the buttons for the currently chosen toolset are shown
- L277 _public member_ `TArray<TSharedRef<FToolElement>> ToolPaletteElementArray;` — The array of Tool Palettes on display. This array is used to keep a handle on all of the created FToolElements so that we can unregister them upon destruction
- L285 _private prototype_ `void CreatePalette(TSharedPtr<FToolPalette> Palette);` — Creates the UI for the Palette specified by the FToolPalette Palette @param Palette the FToolPalette for which this method will build the UI
- L293 _private prototype_ `void TogglePalette(TSharedPtr<FToolPalette> Palette);` — Creates the UI for the Palette specified by the FToolPalette Palette if it is not currently active, else it removes it. @param Palette the FToolPalette for which this method will build the UI
- L301 _private prototype_ `TSharedRef<SWidget> GetContextMenuContent(const FName CommandName);` — Retrieves the context menu content for the FUICommandInfo with the command name CommandName @param CommandName the command name of the FUICommandInfo to get the context menu widget for @return the TSharedRef<SWidget> which contains the context menu for the FUICommandInfo with the name CommandName
- L303 _private prototype_ `void CreatePaletteWidget(FToolPalette& Palette, FToolElement& Element);`
- L312 _private prototype_ `void ToggleCommandInPalette(TSharedRef<FEditablePalette> Palette, FString CommandNameString);` — Adds the FUICommandInfo with the command name CommandNameString to the FEditablePalette Palette if it is not on Palette, and removes the FUICommandInfo from Palette if it is on the Palette @param Palette the FEditablePalette to which the FUICommandInfo will be toggled on/off @param CommandNameString the name of the FUICommandInfo command which will be toggled on/off of Palette
- L315 _private prototype_ `bool HasSelectedToolSet() const;` — @return true if the Toolkit builder has some tools that are currently active/selected
- L322 _private prototype_ `virtual void UpdateContentForCategory( FName ActiveCategoryName = NAME_None, FText InActiveCategoryText = FText::GetEmpty() ) override;` — Given the active category name, update the toolkit content @param ActiveCategoryName
- L329 _private prototype_ `EVisibility GetActiveToolTitleVisibility() const;` — Gets the EVisibility of the active tool title. This should only be visible if a tool is currently chosen in the palette. @return the EVisibility of the active tool title
- L333 _private member_ `EVisibility SelectedCategoryTitleVisibility = EVisibility::Collapsed;` — If SelectedCategoryTitleVisibility == EVisibility::Visible, the selected category title is visible, else it is not displayed. By default the selected category title is Collapsed
- L336 _private member_ `FText ActiveToolDisplayName = FText::GetEmpty();` — The display name of the currently active tool
- L339 _private member_ `TArray<FName> LoadCommandArray;` — The array of Command names, in the correct display order
- L343 _protected prototype_ `TSharedRef<SWidget> GetToolPaletteWidget() const;` — @return a TSharedPointer to the FToolbarBuilder with the FUICommandInfos that load the Palettes
- L347 _protected member_ `EVisibility ActivePaletteButtonVisibility = EVisibility::Visible;` — If ActivePaletteButtonVisibility == EVisibility::Visible, the command buttons in the active palette are visible, otherwise they are not displayed. By default the state is Visible
- L350 _protected member_ `TSharedPtr<FToolkitSections> ToolkitSections;` — The FToolkitSections which holds the sections defined for this Toolkit

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/ToolkitBuilderConfig.h` (Public)


#### struct `FEditableToolPaletteSettings`  
`struct FEditableToolPaletteSettings`  
_L11-19_
- reflection: `USTRUCT()`
- desc: The actual struct that contains the properties saved for an FEditableToolPalette
- L18 _public member_ `TArray<FString> PaletteCommandNames;` — `UPROPERTY()`

#### class `IEditableToolPaletteConfigManager`  
`class IEditableToolPaletteConfigManager`  
_L22-30_
- desc: Interface class for FEditableToolPalette to interact with EditorConfig which is an Editor only module currently
- L26 _public prototype_ `virtual FEditableToolPaletteSettings* GetMutablePaletteConfig(const FName& InstanceName) = 0;`
- L27 _public prototype_ `virtual const FEditableToolPaletteSettings* GetConstPaletteConfig(const FName& InstanceName) = 0;`
- L28 _public prototype_ `virtual void SavePaletteConfig(const FName& InstanceName) = 0;`
- L29 _public prototype_ `virtual ~IEditableToolPaletteConfigManager() = default;`

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_DELEGATE_RetVal(IEditableToolPaletteConfigManager*, FGetEditableToolPaletteConfigManager)` — Delegate passed into FEditableToolPalette that is used to get the actual config manager instance

### `Source/Developer/WidgetRegistration/Public/ToolkitStyle.h` (Public)


#### class `FToolkitStyle`  
`class FToolkitStyle : public FSlateStyleSet`  
_L13-29_
- inherits: `FSlateStyleSet`
- desc: FToolkitStyle is the FSlateStyleSet that defines styles for FToolkitBuilders
- L18 _public member_ `static FName StyleName;`
- L19 _public prototype_ `FToolkitStyle();`
- L20 _public prototype_ `static void Initialize();`
- L21 _public prototype_ `static void Shutdown();`
- L22 _public prototype_ `static const ISlateStyle& Get();`
- L23 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L27 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L28 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WIDGETREGISTRATION_API`

### `Source/Developer/WidgetRegistration/Public/WidgetRegistrationModule.h` (Public)


#### class `FWidgetRegistrationModule`  
`class FWidgetRegistrationModule : public IModuleInterface`  
_L12-23_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
