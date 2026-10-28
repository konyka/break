# Editor / Kismet

- module root: `Source/Editor/Kismet`
- headers: 94; symbols: 4622
- symbol kinds: class=153, delegate=43, enum=34, enumerator=161, function=453, macro=43, member=1117, namespace=31, prototype=2399, struct=131, typedef=56, variable=1
- DynamicallyLoadedModuleNames: BlueprintRuntime, ClassViewer, Documentation, GameProjectGeneration
- PrivateDependencyModuleNames: AnimGraph, AppFramework, ApplicationCore, BlueprintEditorLibrary, BlueprintGraph, Core, CoreUObject, DesktopPlatform, DeveloperSettings, EditorFramework, EditorStyle, EditorWidgets, Engine, EngineSettings, FieldNotification, GameplayTags, GraphEditor, HotReload, InputCore, InteractiveToolsFramework, Json, JsonObjectGraph, JsonUtilities, KismetCompiler, KismetWidgets, LiveCoding, Merge, MessageLog, Projects, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore, Sockets, SourceControl, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, TraceLog, TypedElementRuntime, UMG, UMGEditor, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: Analytics, AssetRegistry, AssetTools, BlueprintRuntime, ClassViewer, GameProjectGeneration, LevelEditor, SourceCodeAccess

### `Source/Editor/Kismet/Classes/BlueprintPaletteFavorites.h` (Public)


#### struct `FFavoritedBlueprintPaletteItem`  
`struct FFavoritedBlueprintPaletteItem`  
_L29-99_
- reflection: `USTRUCT()`
- L34 _public prototype_ `FFavoritedBlueprintPaletteItem();`
- L43 _public prototype_ `FFavoritedBlueprintPaletteItem(FString const& SerializedAction);` — Sometime favorites can be coming from user edited .ini files, so this converts that readable text into a favorite (since the strings are user generated, there could be some error, so sure to check its validity). @param  SerializedAction		A string representing a serialized favorite.
- L51 _public prototype_ `FFavoritedBlueprintPaletteItem(const FEdGraphSchemaAction& InPaletteAction);` — Constructs a favorite from the specified palette action (some palette actions cannot be favorited, so make sure to check its validity). @param  PaletteAction	The action you wish to favorite.
- L54 _public prototype_ `FFavoritedBlueprintPaletteItem(TSharedPtr<FEdGraphSchemaAction> PaletteAction);` — `UE_DEPRECATED(5.5, "Provide a dereferenced FEdGraphSchemaAction, after validating it in the caller")`
- L62 _public prototype_ `FFavoritedBlueprintPaletteItem(UBlueprintNodeSpawner const* BlueprintAction);` — @param  BlueprintAction @return
- L70 _public prototype_ `bool IsValid() const;` — Sometimes we're not able to construct favorites from specified actions, so this provides us a way to check this item's validity. @return True if this favorite is valid (refers to a specific node), false if not.
- L78 _public prototype_ `bool operator==(FFavoritedBlueprintPaletteItem const& Rhs) const;` — Checks to see if this favorite matches the specified one. @param  Rhs	The other favorite you want to compare with. @return True if this favorite matches the other one, false if not.
- L87 _public prototype_ `bool operator==(TSharedPtr<FEdGraphSchemaAction> PaletteAction) const;` — Checks to see if this favorite represents the supplied ed-graph action (so we can match them together, and construct a favorites list). @param  PaletteAction	The action you want to compare with. @return True if this favorite represents the specified action, false if not.
- L95 _public prototype_ `FString const& ToString() const;` — We want to be able to specify some of these in .ini files, so let we have to have a readable string representation for them. @return A string representation of this item.
- L98 _private member_ `FBlueprintNodeSignature ActionSignature;`

#### class `UBlueprintPaletteFavorites`  
`class UBlueprintPaletteFavorites : public UObject`  
_L106-275_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L112 _public prototype_ `virtual void PostInitProperties() override;`
- L113 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L123 _public prototype_ `bool CanBeFavorited(TSharedPtr<FEdGraphSchemaAction> PaletteAction) const;` — Not all palette actions can be turned into a favorite. This method is meant to catch those cases. @param  PaletteAction	The action you wish to check. @return True if the action can be turned into a favorite, false if not.
- L132 _public prototype_ `bool IsFavorited(TSharedPtr<FEdGraphSchemaAction> PaletteAction) const;` — This method can be used to see if a specified action is already favorited by the user. @param  PaletteAction	The action you wish to check. @return True if this action is already favorited, false if it not.
- L133 _public prototype_ `bool IsFavorited(const FEdGraphSchemaAction& InCurrentAction) const;`
- L141 _public prototype_ `bool IsFavorited(FBlueprintActionInfo& BlueprintAction) const;` — @param  BlueprintAction @return
- L149 _public prototype_ `bool IsFavorited(UBlueprintNodeSpawner const* BlueprintAction) const;` — @param  BlueprintAction @return
- L158 _public prototype_ `void AddFavorite(TSharedPtr<FEdGraphSchemaAction> PaletteAction);` — Adds the specified action to the current favorites list (fails if the action action can't be favorited, or if the favorite already exists). Will also convert the user's profile to a custom one (if it isn't already). @param  PaletteAction	The action you wish to add.
- L166 _public prototype_ `void AddFavorites(TArray< TSharedPtr<FEdGraphSchemaAction> > PaletteActions);` — Adds the specified actions to the current favorites list. Will also convert the user's profile to a custom one (if it isn't already). @param  PaletteActions	An array of action you wish to add.
- L175 _public prototype_ `void RemoveFavorite(TSharedPtr<FEdGraphSchemaAction> PaletteAction);` — Removes the specified action to the current favorites list (if it's there). Will also convert the user's profile to a custom one (if it isn't already). @param  PaletteAction	The action you wish to remove.
- L183 _public prototype_ `void RemoveFavorites(TArray< TSharedPtr<FEdGraphSchemaAction> > PaletteActions);` — Remove the specified actions from the current favorites list. Will also convert the user's profile to a custom one (if it isn't already). @param  PaletteActions	An array of action you wish to remove.
- L191 _public prototype_ `void LoadProfile(FString const& ProfileName);` — Throws out all current favorites and loads in ones for the specified profile (explicitly laid out in the editor .ini file). @param  ProfileName	The name of the profile you wish to load.
- L199 _public prototype_ `bool IsUsingCustomProfile() const;` — Provides any easy way to see if the user is currently using their own manual profile (one they set up through the tool). @return True if the user is using their own profile, false if it is a predefined one.
- L207 _public prototype_ `FString const& GetCurrentProfile() const;` — Gets the user's currently set profile. If the user hasn't manually set one themselves, then it'll return the default profile identifier. @return A string name, representing the currently set profile (defined in the editor .ini file)
- L213 _public prototype_ `void ClearAllFavorites();` — Removes every single favorite and sets the user's profile to a custom one (if it isn't already).
- L219 _public prototype_ `DECLARE_EVENT(UBlueprintPaletteFavorites, FBlueprintFavoritesUpdatedEvent);` — A event for users to hook into (specifically the UI), so they can be notified when a change to the favorites has been made.
- L220 _public member_ `FBlueprintFavoritesUpdatedEvent OnFavoritesUpdated;`
- L229 _private prototype_ `FString const& GetDefaultProfileId() const;` — Gets the default profile id specified by the user's .ini file (so we can easily change it without modifying code). @return A string name, representing the default profile (defined in the editor .ini file)
- L235 _private prototype_ `void LoadSetProfile();` — Throws out all current favorites and loads in ones for specified by CurrentProfile.
- L241 _private prototype_ `void LoadCustomFavorites();` — Fills the CurrentFavorites array with items that have been loaded into the CustomFavorites array.
- L249 _private prototype_ `void SetProfile(FString const& NewProfileName);` — Modifies the CurrentProfile member, but flags the property as edited so that it invokes a save of the config. @param  NewProfileName	The new profile that you want favorites saved with.
- L258 _public member_ `TArray<FString> CustomFavorites;` — `UPROPERTY(config)` — A list of strings that are used to identify specific palette actions. This is what gets saved out when the user has customized their own set, and is not updated until PreSave.
- L266 _public member_ `TArray<FFavoritedBlueprintPaletteItem> CurrentFavorites;` — `UPROPERTY(Transient)` — A list of favorites that is constructed in PostLoad() (either from a profile or the user's set of CustomFavorites). This list is up to date and maintained at runtime.
- L274 _public member_ `FString CurrentProfile;` — `UPROPERTY(config)` — Users could load pre-existing profiles (intended to share favorites, and hook into tutorials). If empty, the default profile will be loaded; if the user has customized a pre-existing profile, then this will be "CustomProfile".

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API KISMET_API`
- L219 _delegate_ `DECLARE_EVENT(UBlueprintPaletteFavorites, FBlueprintFavoritesUpdatedEvent);` — A event for users to hook into (specifically the UI), so they can be notified when a change to the favorites has been made.

### `Source/Editor/Kismet/Internal/Blueprints/BlueprintDependencies.h` (Internal)


#### enum `EBPDependencyType`  
`enum class EBPDependencyType`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Asset`
- L15 _public enumerator_ `Struct`
- L16 _public enumerator_ `Class`
- L17 _public enumerator_ `GameplayTag`

#### struct `FBlueprintDependency`  
`struct FBlueprintDependency`  
_L21-36_
- reflection: `USTRUCT()`
- L26 _public member_ `EBPDependencyType DependencyType = EBPDependencyType::Asset;` — `UPROPERTY()`
- L29 _public member_ `FName PackageName;` — `UPROPERTY()`
- L32 _public member_ `FName NativeObjectName;` — `UPROPERTY()`
- L35 _public member_ `FString Hash;` — `UPROPERTY()`

#### struct `FBlueprintDependencies`  
`struct FBlueprintDependencies`  
_L39-45_
- reflection: `USTRUCT()`
- L44 _public member_ `TArray<FBlueprintDependency> BlueprintDependencies;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCookBlueprint, Display, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCookBlueprint, Display, All);`
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace Private` (scope `UE`)
- L47 _namespace_ `namespace BlueprintDependencies` (scope `UE::Private`)
- L49 _prototype_ `UE::Cook::FCookDependency RecordCookDependencies(const UBlueprint* BP);` (scope `UE::Private::BlueprintDependencies`)

### `Source/Editor/Kismet/Internal/DiffControl.h` (Internal)


#### class `IDiffControl`  
`class IDiffControl`  
_L24-48_
- desc: Interface responsible for generating FBlueprintDifferenceTreeEntry's for visual diff tools
- L27 _public prototype_ `virtual ~IDiffControl() = default;`
- L29 _public function_ `virtual void Tick()`
- L32 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) = 0;` — Adds widgets to the tree of differences to show
- L34 _public member_ `static FText RightRevision;`
- L35 _public prototype_ `static TSharedRef<SWidget> GenerateSimpleDiffWidget(FText DiffText);`
- L36 _public prototype_ `static TSharedRef<SWidget> GenerateObjectDiffWidget(FSingleObjectDiffEntry DiffEntry, FText ObjectName);`
- L39 _public prototype_ `void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView, const UObject* OldObject, const UObject* NewObject);` — to support comment posting, set this to the tree view that contains the comments.
- L40 _public prototype_ `void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView, const TArray<const UObject*>& Objects);`
- L41 _public function_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView)`
- L45 _protected prototype_ `void GenerateCategoryCommentTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& , TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences, FString CategoryKey);` — to be called at the end of GenerateTreeEntries if you want this diff control to support review comments
- L47 _protected member_ `TSharedPtr<FReviewCommentsDiffControl> ReviewCommentsDiffControl;`

#### class `FMyBlueprintDiffControl`  
`class FMyBlueprintDiffControl : public TSharedFromThis<FMyBlueprintDiffControl>, public IDiffControl`  
_L51-65_
- inherits: `TSharedFromThis<FMyBlueprintDiffControl>,IDiffControl`
- desc: Shows all differences for the blueprint structure itself that aren't picked up elsewhere
- L54 _public prototype_ `FMyBlueprintDiffControl(const UBlueprint* InOldBlueprint, const UBlueprint* InNewBlueprint, FOnDiffEntryFocused InSelectionCallback);`
- L56 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`
- L59 _public prototype_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView) override;` — to support comment posting, set this to the tree view that contains the comments.
- L62 _private member_ `FOnDiffEntryFocused SelectionCallback;`
- L63 _private member_ `const UBlueprint* OldBlueprint;`
- L64 _private member_ `const UBlueprint* NewBlueprint;`

#### class `FSCSDiffControl`  
`class FSCSDiffControl : public TSharedFromThis<FSCSDiffControl>, public IDiffControl`  
_L71-90_
- inherits: `TSharedFromThis<FSCSDiffControl>,IDiffControl`
- desc: Each difference in the tree will either be a tree node that is added in one Blueprint or a tree node and an FName of a property that has been added or edited in one Blueprint
- L74 _public prototype_ `FSCSDiffControl(const UBlueprint* InOldBlueprint, const UBlueprint* InNewBlueprint, FOnDiffEntryFocused InSelectionCallback);`
- L76 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`
- L78 _public function_ `TSharedRef<SWidget> OldTreeWidget()`
- L79 _public function_ `TSharedRef<SWidget> NewTreeWidget()`
- L82 _public prototype_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView) override;` — to support comment posting, set this to the tree view that contains the comments.
- L85 _private member_ `FOnDiffEntryFocused SelectionCallback;`
- L86 _private member_ `FSCSDiffRoot DifferingProperties;`
- L88 _private member_ `FSCSDiff OldSCS;`
- L89 _private member_ `FSCSDiff NewSCS;`

#### class `FDetailsDiffControl`  
`class FDetailsDiffControl : public TSharedFromThis<FDetailsDiffControl>, public IDiffControl`  
_L93-148_
- inherits: `TSharedFromThis<FDetailsDiffControl>,IDiffControl`
- desc: Generic wrapper around a details view template parameter determines whether TreeEntries are populated
- L96 _public prototype_ `FDetailsDiffControl(const UObject* InOldObject, const UObject* InNewObject, FOnDiffEntryFocused InSelectionCallback, bool bPopulateOutTreeEntries);`
- L97 _public prototype_ `~FDetailsDiffControl();`
- L99 _public prototype_ `virtual void Tick() override;`
- L101 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`
- L102 _public prototype_ `void GenerateTreeEntriesWithoutComments(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences);`
- L104 _public prototype_ `TSharedRef<IDetailsView> InsertObject(const UObject* Object, bool bScrollbarOnLeft = false, int32 Index = INDEX_NONE);`
- L105 _public prototype_ `TSharedRef<IDetailsView> GetDetailsWidget(const UObject* Object) const;`
- L106 _public prototype_ `TSharedPtr<IDetailsView> TryGetDetailsWidget(const UObject* Object) const;`
- L107 _public prototype_ `TSharedPtr<FAsyncDetailViewDiff> GetDifferencesWithLeft(const UObject* Object) const;`
- L108 _public prototype_ `TSharedPtr<FAsyncDetailViewDiff> GetDifferencesWithRight(const UObject* Object) const;`
- L109 _public prototype_ `int32 IndexOfObject(const UObject* Object) const;`
- L112 _public prototype_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView) override;` — to support comment posting, set this to the tree view that contains the comments.
- L114 _public member_ `DiffUtils::FOnGenerateCustomDiffEntries GenerateCustomEntriesCallback;`
- L115 _public member_ `DiffUtils::FOnGenerateCustomDiffEntryWidget GenerateCustomEntryWidgetCallback;`
- L116 _public member_ `DiffUtils::FOnOrganizeDiffEntries OrganizeEntriesCallback;`
- L118 _protected prototype_ `virtual void OnSelectDiffEntry(FPropertySoftPath PropertyName);`
- L119 _protected prototype_ `TAttribute<TArray<FVector2f>> GetLinkedScrollRateAttribute(const TSharedRef<IDetailsView>& OldDetailsView, const TSharedRef<IDetailsView>& NewDetailsView);`
- L123 _protected prototype_ `TArray<FVector2f> GetLinkedScrollRate(TSharedRef<IDetailsView> LeftDetailsView, TSharedRef<IDetailsView> RightDetailsView) const;` — helper function that analyzes two details views and determines the rate they should scroll relative to one another to be in sync
- L125 _private prototype_ `void HandlePropertiesChanged();`
- L127 _private prototype_ `FDetailsDiffControl& operator=(const FDetailsDiffControl&) = delete;`
- L128 _private prototype_ `FDetailsDiffControl( const FDetailsDiffControl& ) = delete;`
- L129 _private prototype_ `FDetailsDiffControl& operator=(FDetailsDiffControl&&) = delete;`
- L130 _private prototype_ `FDetailsDiffControl( FDetailsDiffControl&& ) = delete;`
- L133 _protected member_ `FOnDiffEntryFocused SelectionCallback;`
- L135 _protected member_ `TMap<const UObject*,FDetailsDiff> DetailsDiffs;`
- L136 _protected member_ `TArray<const UObject*> ObjectDisplayOrder;`
- L142 _protected member_ `TMap<const UObject*, FPropertyTreeDiffPairs> PropertyTreeDifferences;`
- L144 _protected member_ `TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> > Children;`
- L145 _protected member_ `const bool bPopulateOutTreeEntries;`
- L147 _protected member_ `TSet<FPropertyPath> PropertyAllowList;`

#### struct `FDetailsDiffControl::FPropertyTreeDiffPairs`  
`struct FPropertyTreeDiffPairs`  
_L137-141_
- L139 _public member_ `TSharedPtr<FAsyncDetailViewDiff> Left;`
- L140 _public member_ `TSharedPtr<FAsyncDetailViewDiff> Right;`

#### class `FCDODiffControl`  
`class FCDODiffControl : public FDetailsDiffControl`  
_L151-157_
- inherits: `FDetailsDiffControl`
- desc: Override for CDO special case
- L154 _public prototype_ `FCDODiffControl(const UObject* InOldObject, const UObject* InNewObject, FOnDiffEntryFocused InSelectionCallback);`
- L156 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`

#### class `FClassSettingsDiffControl`  
`class FClassSettingsDiffControl : public FDetailsDiffControl`  
_L160-166_
- inherits: `FDetailsDiffControl`
- desc: Override for class class settings
- L163 _public prototype_ `FClassSettingsDiffControl(const UObject* InOldObject, const UObject* InNewObject, FOnDiffEntryFocused InSelectionCallback);`
- L165 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`

#### struct `FBlueprintTypeDiffControl`  
`struct FBlueprintTypeDiffControl : public TSharedFromThis<FBlueprintTypeDiffControl>, public IDiffControl`  
_L169-241_
- inherits: `TSharedFromThis<FBlueprintTypeDiffControl>,IDiffControl`
- desc: Diff control to handle finding type-specific differences
- L196 _public prototype_ `FBlueprintTypeDiffControl(const UBlueprint* InBlueprintOld, const UBlueprint* InBlueprintNew, FOnDiffEntryFocused InSelectionCallback);`
- L199 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;` — Generate difference tree widgets
- L202 _public prototype_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView) override;` — to support comment posting, set this to the tree view that contains the comments.
- L205 _public member_ `const UBlueprint* BlueprintOld;` — The old blueprint (left)
- L208 _public member_ `const UBlueprint* BlueprintNew;` — The new blueprint(right)
- L211 _public member_ `TSharedPtr<SBox> OldDetailsBox;` — Boxes that will display the details diffs
- L212 _public member_ `TSharedPtr<SBox> NewDetailsBox;`
- L216 _private prototype_ `TSharedRef<SWidget> GenerateCategoryWidget(bool bHasRealDiffs);` — Generate Widget for top category
- L219 _private prototype_ `void BuildDiffSourceArray();` — Build up the Diff Source Array
- L222 _private prototype_ `void OnSelectSubobjectDiff(FPropertySoftPath Identifier, TSharedPtr<FSubObjectDiff> SubObjectDiff);` — Handle selecting a diff
- L225 _private prototype_ `void OnSelectDiffCustomObject(TSharedPtr<IDiffCustomProperty> CustomProperty, TSharedPtr<FDiffCustomObject> DiffCustomObject);` — Handle selecting a custom object diff
- L228 _private member_ `TArray<TSharedPtr<FSubObjectDiff>> SubObjectDiffs;` — List of objects with differences
- L231 _private member_ `TArray<TSharedPtr<FDiffCustomObject>> DiffCustomObjects;` — List of custom object differences
- L234 _private member_ `TArray<TSharedPtr<FDiffResultItem>> DiffListSource;` — Source for list view
- L237 _private member_ `FOnDiffEntryFocused SelectionCallback;` — Selection callback
- L240 _private member_ `bool bDiffSucceeded;` — Did diff generation succeed?

#### struct `FBlueprintTypeDiffControl::FSubObjectDiff`  
`struct FSubObjectDiff`  
_L171-183_
- L173 _public member_ `FDiffSingleResult SourceResult;`
- L174 _public member_ `FDetailsDiff OldDetails;`
- L175 _public member_ `FDetailsDiff NewDetails;`
- L176 _public member_ `TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>> Diffs;`
- L178 _public function_ `FSubObjectDiff(const FDiffSingleResult& InSourceResult, const UObject* OldObject, const UObject* NewObject) : SourceResult(InSourceResult) , OldDetails(OldObject) , NewDetails(NewObject)`

#### struct `FBlueprintTypeDiffControl::FDiffCustomObject`  
`struct FDiffCustomObject`  
_L185-194_
- L187 _public member_ `FDiffSingleResult SourceResult;`
- L188 _public member_ `TSharedPtr<IDiffCustomObject> DiffWidget;`
- L189 _public member_ `TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>> Diffs;`
- L190 _public function_ `FDiffCustomObject(const FDiffSingleResult& InSourceResult, TSharedPtr<IDiffCustomObject> DiffWidget) : SourceResult(InSourceResult) , DiffWidget(DiffWidget)`

#### struct `FGraphToDiff`  
`struct FGraphToDiff : public TSharedFromThis<FGraphToDiff>, IDiffControl`  
_L245-296_
- inherits: `TSharedFromThis<FGraphToDiff>,IDiffControl`
- desc: Category list item for a graph
- L247 _public prototype_ `FGraphToDiff(SBlueprintDiff* DiffWidget, UEdGraph* GraphOld, UEdGraph* GraphNew, const FRevisionInfo& RevisionOld, const FRevisionInfo& RevisionNew);`
- L251 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;` — Add widgets to the differences tree
- L254 _public prototype_ `UEdGraph* GetGraphOld() const;` — Get old(left) graph
- L257 _public prototype_ `UEdGraph* GetGraphNew() const;` — Get new(right) graph
- L260 _public prototype_ `virtual void EnableComments(TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView) override;` — to support comment posting, set this to the tree view that contains the comments.
- L263 _public member_ `TArray<TSharedPtr<FDiffResultItem>> DiffListSource;` — Source for list view
- L264 _public member_ `TSharedPtr<TArray<FDiffSingleResult>> FoundDiffs;`
- L267 _public member_ `int32 RealDifferencesStartIndex = INDEX_NONE;` — Index of the first item in RealDifferences that was generated by this graph
- L271 _private prototype_ `FText GetToolTip();` — Get tooltip for category
- L274 _private prototype_ `TSharedRef<SWidget> GenerateCategoryWidget();` — Generate Widget for category list
- L277 _private prototype_ `void OnGraphChanged(const FEdGraphEditAction& Action);` — Called when the Newer Graph is modified
- L280 _private prototype_ `void BuildDiffSourceArray();` — Build up the Diff Source Array
- L283 _private member_ `class SBlueprintDiff* DiffWidget;` — Diff widget
- L286 _private member_ `UEdGraph* GraphOld;` — The old graph(left)
- L289 _private member_ `UEdGraph* GraphNew;` — The new graph(right)
- L292 _private member_ `FRevisionInfo RevisionOld, RevisionNew;` — Description of Old and new graph
- L292 _private member_ `FRevisionInfo RevisionOld, RevisionNew;` — Description of Old and new graph
- L295 _private member_ `FDelegateHandle OnGraphChangedDelegateHandle;` — Handle to the registered OnGraphChanged delegate.

#### class `FCommentTreeEntry`  
`class FCommentTreeEntry : public FBlueprintDifferenceTreeEntry, public TSharedFromThis<FCommentTreeEntry>`  
_L298-351_
- inherits: `FBlueprintDifferenceTreeEntry,TSharedFromThis<FCommentTreeEntry>`
- L301 _public prototype_ `FCommentTreeEntry(TWeakPtr<FReviewCommentsDiffControl> InCommentsControl, const FReviewComment& InComment, const TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& InChildren);`
- L303 _public prototype_ `static TSharedRef<FCommentTreeEntry> Make(TWeakPtr<FReviewCommentsDiffControl> CommentsControl, const FReviewComment& Comment, const TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& Children = {});`
- L305 _public prototype_ `int32 GetCommentIDChecked() const;`
- L306 _public prototype_ `void AwaitCommentPost();`
- L309 _private prototype_ `TSharedRef<SWidget> CreateWidget();` — FBlueprintDifferenceTreeEntry callbacks
- L312 _private prototype_ `bool IsCommentTextBoxReadonly() const;` — slate callbacks
- L313 _private prototype_ `FReply OnClickReply();`
- L314 _private prototype_ `FReply OnClickEdit();`
- L315 _private prototype_ `FReply OnLikeToggle();`
- L316 _private prototype_ `FText GetLikeTooltip() const;`
- L317 _private prototype_ `const FSlateBrush* GetLikeIcon() const;`
- L318 _private prototype_ `FSlateColor GetUsernameColor() const;`
- L319 _private prototype_ `FSlateColor GetLikeIconColor() const;`
- L320 _private prototype_ `EVisibility GetEditReplyButtonGroupVisibility() const;`
- L321 _private prototype_ `EVisibility GetEditButtonVisibility() const;`
- L322 _private prototype_ `EVisibility GetSubmitCancelButtonGroupVisibility() const;`
- L323 _private prototype_ `bool IsSubmitButtonEnabled() const;`
- L324 _private prototype_ `FReply OnEditSubmitClicked();`
- L325 _private prototype_ `FReply OnEditCancelClicked();`
- L328 _private prototype_ `void OnCommentPosted(const FReviewComment& Comment);` — comment api callbacks
- L330 _private prototype_ `FString GetCommentString() const;`
- L331 _private prototype_ `void SetCommentString(const FString& NewComment);`
- L334 _private prototype_ `bool HasCommentStringChanged() const;` — during a pending edit, returns whether the comment is different from the saved version
- L336 _private prototype_ `bool IsEditMode() const;`
- L337 _private prototype_ `void SetEditMode(bool bIsEditMode);`
- L339 _private member_ `FReviewComment Comment;`
- L341 _private member_ `TSharedPtr<SWidget> Content;`
- L342 _private member_ `TSharedPtr<SHorizontalBox> EditReplyButtonGroup;`
- L343 _private member_ `TSharedPtr<SHorizontalBox> SubmitCancelButtonGroup;`
- L344 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CommentTextBox;`
- L346 _private member_ `TWeakPtr<FReviewCommentsDiffControl> CommentsControl;`
- L347 _private member_ `FDelegateHandle OnCommentPostedHandle;`
- L350 _private member_ `bool bExpectedEditMode = false;` — prefer the use of IsEditMode().

#### class `FCommentDraftTreeEntry`  
`class FCommentDraftTreeEntry : public FBlueprintDifferenceTreeEntry, public TSharedFromThis<FCommentDraftTreeEntry>`  
_L353-385_
- inherits: `FBlueprintDifferenceTreeEntry,TSharedFromThis<FCommentDraftTreeEntry>`
- L356 _public prototype_ `FCommentDraftTreeEntry(TWeakPtr<FReviewCommentsDiffControl> InCommentsControl, TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>* InSiblings, int32 InReplyID = -1);`
- L357 _public prototype_ `static TSharedRef<FCommentDraftTreeEntry> MakeCommentDraft(TWeakPtr<FReviewCommentsDiffControl> CommentsControl, TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>* Siblings);`
- L358 _public prototype_ `static TSharedRef<FCommentDraftTreeEntry> MakeReplyDraft(TWeakPtr<FReviewCommentsDiffControl> CommentsControl, TSharedPtr<FCommentTreeEntry> InParent);`
- L360 _public prototype_ `void ReassignReplyParent(TSharedPtr<FCommentTreeEntry> InParent);`
- L362 _public function_ `TSharedPtr<SMultiLineEditableTextBox> GetCommentTextBox() const`
- L364 _public prototype_ `bool IsReply() const;`
- L367 _private prototype_ `TSharedRef<SWidget> CreateWidget();` — FBlueprintDifferenceTreeEntry callbacks
- L370 _private prototype_ `bool IsPostButtonEnabled() const;` — slate callbacks
- L371 _private prototype_ `FReply OnCommentPostClicked();`
- L373 _private prototype_ `void ReassignSiblings(TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>* InSiblings, int32 InReplyID);`
- L375 _private member_ `TSharedPtr<SWidget> Content;`
- L376 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CommentTextBox;`
- L377 _private member_ `TSharedPtr<SCheckBox> FlagAsTaskCheckBox;`
- L379 _private member_ `TWeakPtr<FReviewCommentsDiffControl> CommentsControl;`
- L381 _private member_ `TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>* Siblings;`
- L384 _private member_ `int32 ReplyID = -1;` — if this is a reply, store the comment id of it's parent

#### struct `FReviewCommentsDiffControl`  
`struct FReviewCommentsDiffControl : public TSharedFromThis<FReviewCommentsDiffControl>, IDiffControl`  
_L388-414_
- inherits: `TSharedFromThis<FReviewCommentsDiffControl>,IDiffControl`
- desc: Category list item for a graph
- L390 _public prototype_ `FReviewCommentsDiffControl(const FString& InCommentFilePath, TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> TreeView);`
- L392 _public prototype_ `virtual void GenerateTreeEntries(TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutTreeEntries, TArray< TSharedPtr<FBlueprintDifferenceTreeEntry> >& OutRealDifferences) override;`
- L394 _public prototype_ `void SetCategory(const FString& CategoryKey);`
- L396 _public prototype_ `void PostComment(FReviewComment& Comment);`
- L397 _public prototype_ `void DraftReply(TSharedPtr<FCommentTreeEntry> ParentComment);`
- L398 _public prototype_ `void RebuildListView() const;`
- L400 _public function_ `const FString& GetCommentFilePath()`
- L401 _public function_ `const FString& GetCommentCategory()`
- L404 _protected prototype_ `void GenerateCommentThreadRecursive(const FReviewComment& Comment, const TMap<int32, TArray<const FReviewComment*>>& CommentReplyMap, TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutTreeEntries);`
- L408 _protected member_ `FString CommentFilePath;`
- L409 _protected member_ `FString CommentCategory;`
- L410 _protected member_ `TWeakPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> CommentsTreeView;`
- L413 _protected member_ `static TWeakPtr<FCommentDraftTreeEntry> ReplyDraftEntry;` — we only want one reply draft widget in existence so we can use a static to track it

### `Source/Editor/Kismet/Internal/ProjectUtilities/BuildTargetSet.h` (Internal)


#### struct `UE::ProjectUtilities::FBuildTargetSet`  
`struct FBuildTargetSet`  
_L20-55_
- desc: FBuildTargetSet is a value type that represents a set of build targets, e.g. Server|Client|Editor or Client|Server. The underlying target types are meant to be abstracted away, instead the set can be constructed from a piece of reflection data (e.g. a UFunction to call or UClass to use)
- L31 _public prototype_ `static FBuildTargetSet GetCallerTargetsUnsupportedByCallee(const UClass* Caller, const UFunction* Callee);` — Returns a FBuildTargetSet representing the set of targets that the caller supports, that the callee does not. @param Caller	A class that intends to call the Callee @param Callee	The function being called @return			FBuildTargetSet representing the unsupported targets that a caller supports that the callee does not - useful for detecting a caller that may exist on some target (e.g. client) using a function that will not exist on said target.
- L34 _public prototype_ `FString LexToString() const;` — @return			A String representation of this, useful for messaging to a user
- L49 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EBuildTargetFlags) static FString LexToStringImpl(EBuildTargetFlags Flags);`
- L51 _private prototype_ `static EBuildTargetFlags GetSupportedTargetsForNativeClass(const UClass* NativeClass);`
- L52 _private prototype_ `static EBuildTargetFlags GetCallerTargetsUnsupportedByCalleeImpl(EBuildTargetFlags CallerTargets, EBuildTargetFlags CalleeTargets);`
- L54 _private member_ `EBuildTargetFlags BuildTargetFlags = EBuildTargetFlags::None;`

#### enum `UE::ProjectUtilities::FBuildTargetSet::EBuildTargetFlags`  
`enum class EBuildTargetFlags : uint32`  
_L42-48_
- desc: This internal state may become more restrictive as we add validations - e.g. for platforms or specialty programs that go beyond the server/client/editor paradigm:
- L44 _public enumerator_ `None = 0`
- L45 _public enumerator_ `Server = 1 << 0`
- L46 _public enumerator_ `Client = 1 << 1`
- L47 _public enumerator_ `Editor = 1 << 2`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EHostType`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ProjectUtilities` (scope `UE`)
- L56 _prototype_ `ENUM_CLASS_FLAGS(FBuildTargetSet::EBuildTargetFlags);` (scope `UE::ProjectUtilities`)
- L62 _prototype_ `const EHostType::Type FindModuleDescriptorHostType(const UPackage* ForNativePackage);` (scope `UE::ProjectUtilities`) — Given a native UPackage attempts to find the module descriptor host type, returning EHostType::Max if it cannot be determined.

### `Source/Editor/Kismet/Internal/Reflection/FunctionUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Reflection` (scope `UE`)
- L31 _function_ `template<typename T> bool DoesStaticFunctionSignatureMatch(const UFunction* TestFunction)` (scope `UE::Reflection`) — Template function for testing the signature of a UFuction, the template argument should be a function signature, similar to TFunctionRef or std::function. Returns true if the UFunction is notionally compatible with the function signature. For example, if you wish to identify functions have a return param of int32 that takes in two int32s you would write: using UE::Reflection; const bool bMatches = DoesStaticFunctionSignatureMatch<int(int, int)>(TestFunction); Reference types should be tested with their templated variant, e.g. TObjectPtr<UObject> instead of UObject*, and TSubclassOf<UObject> instead of UClass*. Current shortcomings: Any function with OutParams is not currently testable with this function, they will always return false. Some intrinsic structs (like FVector) are not currently testable Delegate parameters are implemented but untested

### `Source/Editor/Kismet/Internal/Reflection/FunctionUtilsPrivate.h` (Internal)


#### struct `UE::Private::TIsUHTUEnum`  
`template <typename T, typename = void> struct TIsUHTUEnum : std::false_type`  
_L17-17_
- inherits: `std::false_type`
- desc: These simple helpers aren't enough to truly detect all UEnums and UStructs, we would also need specializations for non-UHT generated UStructs,to make this edge case more obvious I have chosen these names:

#### struct `UE::Private::TIsUHTUEnum`  
`template <typename T> struct TIsUHTUEnum <T, std::void_t<decltype(&T::StaticEnum)>> : std::true_type`  
_L20-20_
- inherits: `std::true_type`

#### struct `UE::Private::TIsUHTUStruct`  
`template <typename T, typename = void> struct TIsUHTUStruct : std::false_type`  
_L23-23_
- inherits: `std::false_type`

#### struct `UE::Private::TIsUHTUStruct`  
`template <typename T> struct TIsUHTUStruct <T, std::void_t<decltype(&T::StaticStruct)>> : std::true_type`  
_L26-26_
- inherits: `std::true_type`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType`  
_L62-67_
- desc: FProperty <-> CPPType mappings, encoded in TCPPTypeToPropertyType: FInt8Property	<-> int8 FInt16Property	<-> int16 FIntProperty	<-> int32 FInt64Property	<-> int64 FByteProperty	<-> uint8 FUInt16Property	<-> uint16 FUInt32Property	<-> uint32 FUInt64Property	<-> uint64 FFloatProperty	<-> float FDoubleProperty	<-> double FBoolProperty	<-> bool FStrProperty	<-> FString FNameProperty	<-> FName FTextProperty	<-> FText FObjectProperty	<-> TObjectPtr FClassProperty	<-> TSubclassOf FSoftObjectProperty	<-> TSoftObjectPtr FSoftClassProperty	<-> TSoftClassPtr FWeakObjectProperty	<-> TWeakObjectPtr FLazyObjectProperty	<-> TLazyObjectPtr FSetProperty	<-> TSet FArrayProperty	<-> TArray FMapProperty	<-> TMap FOptionalProperty	<-> TOptional FInterfaceProperty	<-> TScriptInterface FMulticastInlineDelegateProperty	<-> TMulticastDelegate FMulticastSparseDelegateProperty	<-> TSparseDynamicDelegate FDelegateProperty	<-> TScriptDelegate FEnumProperty	<-> UEnum FStructProperty	<-> UStruct
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int8>`  
_L69-69_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int8>`  
_L70-70_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int8>`  
_L71-71_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int8>`  
_L72-72_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int16>`  
_L73-73_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int32>`  
_L74-74_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<int64>`  
_L75-75_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<uint8>`  
_L76-76_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<uint16>`  
_L77-77_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<uint32>`  
_L78-78_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<uint64>`  
_L79-79_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<float>`  
_L80-80_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<double>`  
_L81-81_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<bool>`  
_L82-82_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<FString>`  
_L83-83_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<FName>`  
_L84-84_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<> struct TCPPTypeToPropertyType<FText>`  
_L85-85_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>>`  
_L86-86_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>>`  
_L87-87_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>>`  
_L88-88_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>>`  
_L89-89_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>>`  
_L90-90_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>>`  
_L91-91_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TArray<T>>`  
_L92-92_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>>`  
_L93-93_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TOptional<T>>`  
_L94-94_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TCPPTypeToPropertyType`  
`template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>>`  
_L95-95_
- L64 _public typedef_ `using PropertyType = std::conditional< TIsUHTUStruct<T>::value, FStructProperty, std::conditional<TIsUHTUEnum<T>::value, FEnumProperty, std::false_type>>;`
- L69 _public typedef_ `template<> struct TCPPTypeToPropertyType<int8> { using PropertyType = FInt8Property; };`
- L73 _public typedef_ `template<> struct TCPPTypeToPropertyType<int16> { using PropertyType = FInt16Property; };`
- L74 _public typedef_ `template<> struct TCPPTypeToPropertyType<int32> { using PropertyType = FIntProperty; };`
- L75 _public typedef_ `template<> struct TCPPTypeToPropertyType<int64> { using PropertyType = FInt64Property; };`
- L76 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint8> { using PropertyType = FByteProperty; };`
- L77 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint16> { using PropertyType = FUInt16Property; };`
- L78 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint32> { using PropertyType = FUInt32Property; };`
- L79 _public typedef_ `template<> struct TCPPTypeToPropertyType<uint64> { using PropertyType = FUInt64Property; };`
- L80 _public typedef_ `template<> struct TCPPTypeToPropertyType<float> { using PropertyType = FFloatProperty; };`
- L81 _public typedef_ `template<> struct TCPPTypeToPropertyType<double> { using PropertyType = FDoubleProperty; };`
- L82 _public typedef_ `template<> struct TCPPTypeToPropertyType<bool> { using PropertyType = FBoolProperty; };`
- L83 _public typedef_ `template<> struct TCPPTypeToPropertyType<FString> { using PropertyType = FStrProperty; };`
- L84 _public typedef_ `template<> struct TCPPTypeToPropertyType<FName> { using PropertyType = FNameProperty; };`
- L85 _public typedef_ `template<> struct TCPPTypeToPropertyType<FText> { using PropertyType = FTextProperty; };`
- L86 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TObjectPtr<T>> { using PropertyType = FObjectProperty; };`
- L87 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSubclassOf<T>> { using PropertyType = FClassProperty; };`
- L88 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftObjectPtr<T>> { using PropertyType = FSoftObjectProperty; };`
- L89 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TSoftClassPtr<T>> { using PropertyType = FSoftClassProperty; };`
- L90 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TWeakObjectPtr<T>> { using PropertyType = FWeakObjectProperty; };`
- L91 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TLazyObjectPtr<T>> { using PropertyType = FLazyObjectProperty; };`
- L92 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TArray<T>> { using PropertyType = FArrayProperty; };`
- L93 _public typedef_ `template<typename K, typename V> struct TCPPTypeToPropertyType<TMap<K, V>> { using PropertyType = FMapProperty; };`
- L94 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TOptional<T>> { using PropertyType = FOptionalProperty; };`
- L95 _public typedef_ `template<typename T> struct TCPPTypeToPropertyType<TScriptInterface<T>> { using PropertyType = FInterfaceProperty; };`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename T> struct TDoesParamMatchImpl`  
_L99-119_
- desc: This implementation handles UStructs, UEnums, and all non-parameterized types, specializations below handle parameterized types
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<template <typename> typename T, typename ReferenceType> struct TDoesParamMatchImpl<T<ReferenceType>>`  
_L142-148_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename ContainedType> struct TDoesParamMatchImpl<TSet<ContainedType>>`  
_L151-159_
- desc: Container Types - we could make these more dense, but I found this easy to write:
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename ContainedType> struct TDoesParamMatchImpl<TArray<ContainedType>>`  
_L161-169_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename ContainedType> struct TDoesParamMatchImpl<TOptional<ContainedType>>`  
_L171-179_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename KeyType, typename ValueType> struct TDoesParamMatchImpl<TMap<KeyType, ValueType>>`  
_L181-190_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename SignatureType> struct TDoesParamMatchImpl<TMulticastDelegate<SignatureType>>`  
_L193-201_
- desc: delegate types:
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename SignatureType, typename OwningClass, typename InfoGetter> struct TDoesParamMatchImpl<TSparseDynamicDelegate<SignatureType, OwningClass, InfoGetter>>`  
_L203-211_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesParamMatchImpl`  
`template<typename SignatureType> struct TDoesParamMatchImpl<TScriptDelegate<SignatureType>>`  
_L213-221_
- L101 _public function_ `static bool DoesMatchProperty(const FProperty* Property)`
- L144 _public function_ `static bool DoesMatchProperty(const FProperty* P)`

#### struct `UE::Private::TDoesStaticFunctionSignatureMatchImpl`  
`template<typename... Args> struct TDoesStaticFunctionSignatureMatchImpl<void(Args...)>`  
_L262-274_
- desc: Two specializations, one for signatures and one for signatures with return types:
- L264 _public function_ `static bool DoesMatch(const UFunction* Fn)`

#### struct `UE::Private::TDoesStaticFunctionSignatureMatchImpl`  
`template<typename ReturnType, typename... Args> struct TDoesStaticFunctionSignatureMatchImpl<ReturnType(Args...)>`  
_L277-290_
- L264 _public function_ `static bool DoesMatch(const UFunction* Fn)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Private` (scope `UE`)
- L103 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<T>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L123 _function_ `template<typename T> bool DoesReferencePropertyMatch(const T* Property, UClass* Type)` (scope `UE::Private`) — This handles all reference types (TObjectPtr, TSubclassOf, TSoftObjectPtr, TSoftClassPtr, TWeakObjectPtr, TLazyObjectPtr:
- L129 _function_ `template<> inline bool DoesReferencePropertyMatch<FClassProperty>(const FClassProperty* Property, UClass* Type)` (scope `UE::Private`)
- L135 _function_ `template<> inline bool DoesReferencePropertyMatch<FSoftClassProperty>(const FSoftClassProperty* Property, UClass* Type)` (scope `UE::Private`)
- L155 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TSet<ContainedType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L165 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TArray<ContainedType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L175 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TOptional<ContainedType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L185 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TMap<KeyType, ValueType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L197 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TMulticastDelegate<SignatureType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L207 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TSparseDynamicDelegate<SignatureType, OwningClass, InfoGetter>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L217 _typedef_ `using PropertyType = typename TCPPTypeToPropertyType<TScriptDelegate<SignatureType>>::PropertyType;` (scope `UE::Private::TDoesParamMatchImpl::DoesMatchProperty`)
- L224 _function_ `template<typename Arg, typename... Args> bool DoesParamMatch(const FProperty* Param)` (scope `UE::Private`)

### `Source/Editor/Kismet/Private/BPDelegateDragDropAction.h` (Private)


#### class `FKismetDelegateDragDropAction`  
`class FKismetDelegateDragDropAction : public FKismetVariableDragDropAction`  
_L30-90_
- inherits: `FKismetVariableDragDropAction`
- desc: DragDropAction class for dropping a Variable onto a graph
- L33 _public function_ `DRAG_DROP_OPERATOR_TYPE(FKismetDelegateDragDropAction, FKismetVariableDragDropAction)`
- L38 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L40 _public prototype_ `virtual bool IsSupportedBySchema(const class UEdGraphSchema* Schema) const override;`
- L43 _public prototype_ `bool IsValid() const;`
- L45 _public function_ `static TSharedRef<FKismetDelegateDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InSourceAction, FName InVariableName, UStruct* InSource, FNodeCreationAnalytic AnalyticCallback)`
- L66 _public function_ `template<class TNode> static void MakeMCDelegateNode(FNodeConstructionParams Params)`
- L83 _public prototype_ `static void MakeEvent(FNodeConstructionParams Params);` — Create new custom event node from construction parameters
- L86 _public prototype_ `static void AssignEvent(FNodeConstructionParams Params);` — Assign new delegate node from construction parameters
- L89 _protected function_ `FKismetDelegateDragDropAction()`

#### struct `FKismetDelegateDragDropAction::FNodeConstructionParams`  
`struct FNodeConstructionParams`  
_L57-64_
- desc: Structure for required node construction parameters
- L59 _public member_ `FDeprecateSlateVector2D GraphPosition;`
- L60 _public member_ `UEdGraph* Graph;`
- L61 _public member_ `bool bSelfContext;`
- L62 _public member_ `const FProperty* Property;`
- L63 _public member_ `FNodeCreationAnalytic AnalyticCallback;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API KISMET_API`
- L75 _function_ `` (scope `FKismetDelegateDragDropAction::MakeMCDelegateNode`)

### `Source/Editor/Kismet/Private/BPFunctionDragDropAction.h` (Private)


#### class `FKismetDragDropAction`  
`class FKismetDragDropAction : public FMyBlueprintItemDragDropAction`  
_L29-56_
- inherits: `FMyBlueprintItemDragDropAction`
- L32 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FKismetDragDropAction, FMyBlueprintItemDragDropAction)`
- L36 _public prototype_ `virtual FReply DroppedOnPanel( const TSharedRef< class SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L39 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanBeDroppedDelegate, TSharedPtr<FEdGraphSchemaAction> , UEdGraph* , FText& );`
- L41 _public function_ `static TSharedRef<FKismetDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InActionNode, FNodeCreationAnalytic AnalyticCallback, FCanBeDroppedDelegate CanBeDroppedDelegate)`
- L52 _protected prototype_ `bool ActionWillShowExistingNode() const;`
- L55 _protected member_ `FCanBeDroppedDelegate CanBeDroppedDelegate;`

#### class `FKismetFunctionDragDropAction`  
`class FKismetFunctionDragDropAction : public FKismetDragDropAction`  
_L62-89_
- inherits: `FKismetDragDropAction`
- L65 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FKismetFunctionDragDropAction, FKismetDragDropAction) FKismetFunctionDragDropAction();`
- L70 _public prototype_ `virtual FReply DroppedOnPanel( const TSharedRef< class SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;` — FGraphEditorDragDropAction interface
- L71 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L74 _public prototype_ `static TSharedRef<FKismetFunctionDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InActionNode, FName InFunctionName, UClass* InOwningClass, const FMemberReference& InCallOnMember, FNodeCreationAnalytic AnalyticCallback, FCanBeDroppedDelegate CanBeDroppedDelegate = FCanBeDroppedDelegate());`
- L78 _protected member_ `FName FunctionName;` — Name of function being dragged
- L80 _protected member_ `UClass* OwningClass;` — Class that function belongs to
- L82 _protected member_ `FMemberReference CallOnMember;` — Call on member reference
- L85 _protected prototype_ `UFunction const* GetFunctionProperty() const;` — Looks up the functions field on OwningClass using FunctionName
- L88 _protected prototype_ `class UBlueprintFunctionNodeSpawner* GetDropAction(UEdGraph& Graph) const;` — Constructs an action to execute, placing a function call node for the associated function

#### class `FKismetMacroDragDropAction`  
`class FKismetMacroDragDropAction : public FKismetDragDropAction`  
_L95-123_
- inherits: `FKismetDragDropAction`
- L98 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FKismetMacroDragDropAction, FKismetDragDropAction) FKismetMacroDragDropAction();`
- L103 _public prototype_ `virtual FReply DroppedOnPanel( const TSharedRef< class SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;` — FGraphEditorDragDropAction interface
- L106 _public prototype_ `static TSharedRef<FKismetMacroDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InActionNode, FName InMacroName, UBlueprint* InBlueprint, UEdGraph* InMacro, FNodeCreationAnalytic AnalyticCallback);`
- L110 _protected function_ `virtual UBlueprint* GetSourceBlueprint() const override` — FMyBlueprintItemDragDropAction interface
- L118 _protected member_ `FName MacroName;` — Name of macro being dragged
- L120 _protected member_ `UEdGraph* Macro;` — Graph for the macro being dragged
- L122 _protected member_ `UBlueprint* Blueprint;` — Blueprint we are operating on

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API KISMET_API`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FCanBeDroppedDelegate, TSharedPtr<FEdGraphSchemaAction> , UEdGraph* , FText& );`

### `Source/Editor/Kismet/Private/BPGraphClipboardData.h` (Private)


#### struct `FBPGraphClipboardData`  
`struct FBPGraphClipboardData`  
_L22-77_
- reflection: `USTRUCT()`
- desc: A helper struct for copying a Blueprint Function to the clipboard
- L27 _public prototype_ `FBPGraphClipboardData();` — Default constructor
- L30 _public prototype_ `FBPGraphClipboardData(const UEdGraph* InFuncGraph);` — Constructs a FBPGraphClipboardData from a graph
- L33 _public prototype_ `bool IsValid() const;` — Checks if the data is valid for configuring a graph
- L36 _public prototype_ `bool IsFunction() const;` — Returns whether the graph represents a function
- L39 _public prototype_ `bool IsMacro() const;` — Returns whether the graph represents a macro
- L42 _public prototype_ `void SetFromGraph(const UEdGraph* InFuncGraph);` — Populates the struct based on a graph
- L44 _public function_ `UBlueprint* GetOriginalBlueprint() const`
- L55 _public prototype_ `UEdGraph* CreateAndPopulateGraph(UBlueprint* InBlueprint, UBlueprint* FromBP, FBlueprintEditor* InBlueprintEditor, const FText& InCategoryOverride = FText::GetEmpty());` — Creates and configures a new graph with data from this struct @param InBlueprint        The Blueprint to add the new graph to @param FromBP		The blueprint that this function is originally from @param InBlueprintEditor  Editor that is being pasted into @param InCategoryOverride Category to place the new graph into @return The new Graph, properly configured and populated if data is valid, or nullptr if data is invalid.
- L59 _private prototype_ `bool PopulateGraph(UEdGraph* InFuncGraph, UBlueprint* FromBP, FBlueprintEditor* InBlueprintEditor);` — Configures a graph with the nodes and settings, returns false if operation was aborted
- L64 _private member_ `FName GraphName;` — `UPROPERTY()` — Name of the Graph
- L68 _private member_ `TEnumAsByte<EGraphType> GraphType;` — `UPROPERTY()` — The type of graph
- L72 _private member_ `TWeakObjectPtr<UBlueprint> OriginalBlueprint;` — `UPROPERTY()` — The original Blueprint that this function was copied from. Used to determine if nodes need to be created as functions or custom events
- L76 _private member_ `FString NodesString;` — `UPROPERTY()` — A string containing the exported text for the nodes in this function

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessCoordinator.h` (Private)


#### enum `EBatchJobState`  
`enum class EBatchJobState`  
_L12-18_
- L14 _public enumerator_ `Pending`
- L15 _public enumerator_ `Scheduled`
- L16 _public enumerator_ `InProgress`
- L17 _public enumerator_ `Completed`

#### struct `FBatchJobResult`  
`struct FBatchJobResult`  
_L20-26_
- L22 _public member_ `EBatchJobState State = EBatchJobState::Pending;`
- L23 _public member_ `bool bEncounteredError = false;`
- L24 _public member_ `FString Output;` — log output captured by the worker during this job's function call
- L25 _public member_ `FString ArgumentSummary;` — compact JSON of the original argument, for diagnostic display

#### struct `FBatchProcessCoordinator`  
`struct FBatchProcessCoordinator`  
_L28-156_
- L30 _public prototype_ `FBatchProcessCoordinator(const FString* ClientAddress, int32 InNumWorkers = 1);`
- L31 _public prototype_ `~FBatchProcessCoordinator();`
- L38 _public prototype_ `void SubmitFile(const TCHAR* Filename);` — Parse a job description from a file or JSON string. The JSON must contain a "function" (UFunction path) and "arguments" (array of arg objects). Call Seal() once no more jobs will be added.
- L39 _public prototype_ `void Submit(const FUtf8String& JsonCommand);`
- L45 _public prototype_ `void AppendJob(TSharedPtr<FJsonValue> Argument);` — Append a single argument object to the pending job queue. May be called at any point before Seal(), including while Tick() is running.
- L51 _public prototype_ `void Seal();` — Signal that no more jobs will be appended. The coordinator will complete once all queued jobs finish.
- L54 _public prototype_ `void Abort();` — Cancel all in-flight work and shut down workers.
- L61 _public prototype_ `void RegisterPendingWorker();` — Registers a pre-existing worker slot without launching a process. The slot accepts an incoming connection via the normal handshake. Useful for in-process testing and the "dummy coordinator" debug mode.
- L64 _public prototype_ `bool Tick();` — @return true if still in progress, false when complete
- L66 _public prototype_ `bool HasAnyErrors() const;`
- L67 _public prototype_ `FString GetErrorString() const;`
- L68 _public prototype_ `int32 GetNumJobs() const;`
- L69 _public prototype_ `int32 GetNumWorkers() const;`
- L70 _public prototype_ `int32 GetNumLaunchingWorkers() const;`
- L72 _public prototype_ `int32 GetNumActiveWorkers() const;` — Returns the number of workers that are Starting, WaitingForWork, or Running.
- L73 _public prototype_ `const FBatchJobResult& GetJobResult(int32 Idx) const;`
- L74 _public prototype_ `const FString& GetFunctionAsString() const;`
- L77 _private prototype_ `void HandleCleanup();`
- L78 _private prototype_ `void HandleError(const FString& Error);`
- L79 _private prototype_ `void AcceptConnections();`
- L80 _private prototype_ `void ReceiveHandshakes();`
- L81 _private prototype_ `void LaunchNewWorkers();`
- L82 _private prototype_ `void UpdateActiveWorkers();`
- L83 _private prototype_ `void CheckCompletion();`
- L85 _private prototype_ `void FindCrashedWorkers();`
- L86 _private prototype_ `void FindStuckWorkers();`
- L87 _private prototype_ `void GiveWorkToWorkers();`
- L88 _private prototype_ `void ProcessResultsFromWorkers();`
- L89 _private prototype_ `void FailAllRemainingJobs();`
- L91 _private prototype_ `bool Recv(FSocket* FromSocket, TArray<uint8>& Bytes);`
- L92 _private prototype_ `static FString GetSocketReadableErrorCode();`
- L94 _private prototype_ `FBatchProcessCoordinator(const FBatchProcessCoordinator&) = delete;`
- L95 _private prototype_ `FBatchProcessCoordinator& operator=(const FBatchProcessCoordinator&) = delete;`
- L96 _private prototype_ `FBatchProcessCoordinator(FBatchProcessCoordinator&&) = delete;`
- L97 _private prototype_ `FBatchProcessCoordinator& operator=(FBatchProcessCoordinator&&) = delete;`
- L99 _private member_ `TArray<FBatchJobResult> JobResults;`
- L100 _private member_ `TArray<TSharedPtr<FJsonValue>> JobArguments;` — one entry per job
- L101 _private member_ `FString FunctionAsString;`
- L112 _private prototype_ `static bool IsErrorState(EWorkerState WorkerState);`
- L139 _private member_ `TArray<FSocket*> PendingWorkerSockets;`
- L140 _private member_ `TArray<FWorkerStateData> ActiveWorkers;`
- L141 _private member_ `FString ErrorRecord;`
- L143 _private member_ `int32 NumWorkers = 1;`
- L144 _private member_ `int32 NextJobToDispatch = 0;` — next sequential job index to send
- L145 _private member_ `int32 CompletionCounter = 0;`
- L146 _private member_ `TArray<int32> RetryQueue;` — jobs to re-attempt after worker crash/timeout
- L147 _private member_ `TArray<int8> JobRetryCount;` — per-job retry count (parallel to JobResults)
- L150 _private member_ `TSharedPtr<class FInternetAddr> ListenAddr;` — socket info:
- L151 _private member_ `FSocket* CoordinatorSocket;`
- L154 _private member_ `bool bIsCompleted;` — flags:
- L155 _private member_ `bool bIsSealed;` — true once no more jobs will be appended; enables completion detection

#### enum `FBatchProcessCoordinator::EWorkerState`  
`enum class EWorkerState`  
_L103-111_
- L105 _public enumerator_ `Starting`
- L106 _public enumerator_ `WaitingForWork`
- L107 _public enumerator_ `Running`
- L108 _public enumerator_ `ShuttingDown`
- L109 _public enumerator_ `FailedToStart`
- L110 _public enumerator_ `FailedToShutdown`

#### struct `FBatchProcessCoordinator::FWorkerStateData`  
`struct FWorkerStateData`  
_L113-137_
- L115 _public member_ `EWorkerState WorkerState = EWorkerState::Starting;`
- L116 _public member_ `FProcHandle Handle;`
- L117 _public member_ `double LastStateChangeTime = 0.0;`
- L118 _public member_ `FString LaunchString;`
- L119 _public member_ `FSocket* Socket = nullptr;`
- L123 _public member_ `int32 CurrentJobIndex = -1;` — The global job index this worker is currently executing; -1 when idle. Used for crash/timeout recovery: if the worker dies, this job is re-enqueued.
- L127 _public member_ `double LastResultTime = 0.0;` — Timestamp of the last result received from this worker. Used by FindStuckWorkers to detect Running workers that have gone silent.
- L133 _public member_ `TArray<uint8> RecvBuffer;` — Per-worker byte buffer for incoming socket data. The coordinator drains bytes non-blockingly into this buffer and parses complete framed messages from it, preventing a slow/large result from one worker from blocking reads of all other workers.
- L134 _public member_ `int32 RecvBufferReadOffset = 0;`
- L136 _public prototype_ `void ChangeState(EWorkerState NewState);`

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessLibrary.h` (Private)


#### class `UBatchProcessLibrary`  
`class UBatchProcessLibrary : public UBlueprintFunctionLibrary`  
_L92-109_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint/Python-callable wrapper around FBatchProcessCoordinator. RunBatch() lets you drive the batch processor from a single Python script: discover assets, build a job description, fan out to N workers, and get structured results back — all without leaving the current editor process. Example — stringify every Blueprint in the project with JsonObjectGraph note that for snapshot_asset to be reachable you must register it in init_unreal.py thusly: import snapshot_assets @code{.py} # Save in /Game/Content/Python/snapshot_assets.py import json import os import unreal # Declare a uclass with a function that we want to run, this simple function just # takes an asset path, loads it, stringifies it, and writes the string to a file: @unreal.uclass() class SnapshotAsset(unreal.Object): @unreal.ufunction(params=[str]) def snapshot_asset(self, asset_path: str) -> None: try: asset = unreal.load_asset(asset_path) except Exception as exc: unreal.log_error(f"FAIL: {asset_path}  (load exception: {exc})") return if asset is None: unreal.log_error(f"FAIL: {asset_path}  (asset not found)") return json_str = unreal.JsonObjectGraphFunctionLibrary.stringify( [asset.get_package()], unreal.JsonStringifyOptions(unreal.JsonStringifyFlags.FILTER_EDITOR_ONLY_DATA)) # Build a nested output path from the package path, stripping the leading '/'. # e.g. "/Game/Baz/Foo" -> "Game/Baz/Foo.json" and write to that file: relative = asset_path.lstrip("/") out_path = os.path.join( unreal.Paths.project_saved_dir(),
- L108 _public prototype_ `static FString RunBatch(const FString& JobJson, int32 NumWorkers = 0);` — `UFUNCTION(BlueprintCallable, Category = "BatchProcess")` — Run a batch of jobs across multiple worker processes and return structured results. @param JobJson    Full job description as a JSON string: {"Function": "<UFunction path>", "Arguments": [{...}, ...]} @param NumWorkers Number of worker processes to spawn. Pass 0 (default) to auto-select based on core count. @return           JSON array string — one object per job, in submission order: [{"Passed": bool, "Output": "...", "ArgumentSummary": "..."}, ...]

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBatchProcess, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBatchProcess, Log, All);`

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessRunner.h` (Private)


#### struct `UE::Private::FBatchRunOptions`  
`struct FBatchRunOptions`  
_L11-21_
- L14 _public member_ `int32 NumWorkers = 0;` — Number of workers to spawn. 0 = auto-select based on core count.
- L20 _public member_ `const FString* ClientAddress = nullptr;` — When non-null, launches the coordinator in listen mode so a single external client can connect for debugging (-launchforclient).

#### struct `UE::Private::FBatchRunResult`  
`struct FBatchRunResult`  
_L23-30_
- L25 _public member_ `TArray<FBatchJobResult> Jobs;` — one per submitted job, in submission order
- L26 _public member_ `FString FunctionPath;` — the UFUNCTION path parsed from the job JSON
- L27 _public member_ `FString TempFilePath;` — Saved/BatchProcess/last_run.json written by the runner
- L28 _public member_ `bool bHasCoordinatorErrors = false;`
- L29 _public member_ `FString CoordinatorErrorString;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Private` (scope `UE`)
- L42 _prototype_ `FBatchRunResult RunBatchFromJson(const FString& JobJson, const FBatchRunOptions& Options = FBatchRunOptions());` (scope `UE::Private`) — Core batch execution helper shared by BatchProcessCommandlet and BatchProcessLibrary. Given a raw JSON job description string this function: 1. Persists the JSON to Saved/BatchProcess/last_run.json and prints a rerun command. 2. Spins up an FBatchProcessCoordinator, submits all jobs, and runs the tick loop. 3. Displays a live progress bar in interactive consoles. 4. Prints the first 10 failures as errors, each with a -singlecommand reproduce line. 5. Returns all results for the caller to handle (results file, exit code, JSON, etc.).

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessSocketHelpers.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Private` (scope `UE`)
- L11 _namespace_ `namespace BatchProcessSocketHelpers` (scope `UE::Private`)
- L14 _variable_ `constexpr int32 DefaultPortNumber = 61579;` (scope `UE::Private::BatchProcessSocketHelpers`) — Port the coordinator listens on and workers connect to.
- L16 _prototype_ `bool SendUint32(FSocket& Socket, uint32 Arg);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L17 _prototype_ `bool RecvUint32(FSocket& Socket, uint32& Num);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L18 _prototype_ `bool RecvCharArray(FSocket& Socket, uint32 Num, TUniquePtr<char[]>& OutCharArray);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L19 _prototype_ `bool RecvString(FSocket& Socket, FString& OutString);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L20 _prototype_ `bool SendJsonValue(FSocket& Socket, const TSharedRef<FJsonObject>& Object);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L21 _prototype_ `bool RecvJsonValue(FSocket& Socket, TSharedPtr<FJsonValue>& Value);` (scope `UE::Private::BatchProcessSocketHelpers`)
- L22 _prototype_ `bool SendString(FSocket& Socket, const FString& String);` (scope `UE::Private::BatchProcessSocketHelpers`)

### `Source/Editor/Kismet/Private/BatchProcess/BatchProcessWorker.h` (Private)


#### struct `FBatchProcessWorker`  
`struct FBatchProcessWorker`  
_L11-49_
- L13 _public prototype_ `FBatchProcessWorker();`
- L14 _public prototype_ `~FBatchProcessWorker();`
- L16 _public prototype_ `bool LaunchLocalCoordinator(const FString& Command, FString& OutCoordinatorAddr, const FString& ExtraArgs = FString());`
- L17 _public prototype_ `bool PerformWork(const FString& CoordinatorAddrStr, int32 WorkerId, uint32 CoordinatorPid = 0);`
- L19 _public function_ `FProcHandle GetLocalCoordinatorHandle() const` — Returns the handle for the coordinator process started by LaunchLocalCoordinator, if any.
- L26 _public prototype_ `static bool RunSingleCommand(const FString& JobJson);` — Run a single job inline without connecting to a coordinator. JobJson must have the form: {"function":"<path>","arguments":[{...}]} Output flows to the normal log; returns false if any error was logged.
- L29 _private prototype_ `void HandleCleanup();`
- L30 _private prototype_ `bool Connect(const FString& CoordinatorAddrStr, int32 WorkerId);`
- L32 _private prototype_ `FBatchProcessWorker(const FBatchProcessWorker&) = delete;`
- L33 _private prototype_ `FBatchProcessWorker(FBatchProcessWorker&&) = delete;`
- L34 _private prototype_ `FBatchProcessWorker& operator=(const FBatchProcessWorker&) = delete;`
- L35 _private prototype_ `FBatchProcessWorker& operator=(FBatchProcessWorker&&) = delete;`
- L37 _private member_ `FSocket* ClientSocket = nullptr;`
- L38 _private member_ `FProcHandle LocalCoordinator;` — debug facility: client starts its own coordinator for testing
- L48 _private member_ `EClientState ClientState;`

#### enum `FBatchProcessWorker::EClientState`  
`enum class EClientState`  
_L40-47_
- L42 _public enumerator_ `Starting`
- L43 _public enumerator_ `Working`
- L44 _public enumerator_ `Idle`
- L45 _public enumerator_ `ShuttingDown`
- L46 _public enumerator_ `Error`

### `Source/Editor/Kismet/Private/BitmaskLiteralDetails.h` (Private)


#### class `FBitmaskLiteralDetails`  
`class FBitmaskLiteralDetails : public IDetailCustomization`  
_L19-49_
- inherits: `IDetailCustomization`
- desc: Details customization for the "Make Bitmask Literal" node
- L23 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public function_ `FBitmaskLiteralDetails() : TargetNode(NULL)`
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L37 _protected prototype_ `TSharedPtr<FString> GetBitmaskEnumTypeName() const;`
- L38 _protected prototype_ `void OnBitmaskEnumTypeChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`
- L42 _private member_ `UK2Node_BitmaskLiteral* TargetNode;` — The target node
- L45 _private member_ `TMap<FName, UEnum*> BitmaskEnumTypeMap;` — Map of enum types used as bitmasks
- L48 _private member_ `TArray<TSharedPtr<FString>> BitmaskEnumTypeNames;` — Array of enum type names used by the UI

### `Source/Editor/Kismet/Private/BlueprintDebugger.h` (Private)


#### struct `FBlueprintDebugger`  
`struct FBlueprintDebugger`  
_L9-28_
- L12 _public prototype_ `FBlueprintDebugger();` — Initializes the global state of the debugger (commands, tab spawners, etc):
- L15 _public prototype_ `~FBlueprintDebugger();` — Destructor declaration purely so that we can pimpl:
- L18 _public prototype_ `void SetDebuggedBlueprint(UBlueprint* InBlueprint);` — Sets the current debugged blueprint in the debugger
- L21 _private member_ `TUniquePtr< struct FBlueprintDebuggerImpl > Impl;`
- L24 _private prototype_ `FBlueprintDebugger(const FBlueprintDebugger&);` — prevent copying:
- L25 _private prototype_ `FBlueprintDebugger(FBlueprintDebugger&&);`
- L26 _private prototype_ `FBlueprintDebugger& operator=(FBlueprintDebugger const&);`
- L27 _private prototype_ `FBlueprintDebugger& operator=(FBlueprintDebugger&&);`

### `Source/Editor/Kismet/Private/BlueprintDetailsCustomization.h` (Private)


#### enum `EVariableReplication::Type`  
`enum Type`  
_L76-96_
- L81 _public enumerator_ `None` — Not replicated.
- L87 _public enumerator_ `Replicated` — Replicated from server to client. As values change on the server, client automatically receives new values, if Actor is set to replicate.
- L93 _public enumerator_ `RepNotify` — Replicated from server to client, with a notification function called on clients when a new value arrives. An event with the name "On Rep <VariableName>" is created.
- L95 _public enumerator_ `MAX`

#### class `FBlueprintDetails`  
`class FBlueprintDetails : public IDetailCustomization`  
_L99-132_
- inherits: `IDetailCustomization`
- L102 _public function_ `FBlueprintDetails(TWeakPtr<SMyBlueprint> InMyBlueprint) : Blueprint(InMyBlueprint.Pin()->GetBlueprintObj())`
- L107 _public function_ `FBlueprintDetails(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr) : Blueprint(InBlueprintEditorPtr.Pin()->GetBlueprintObj())`
- L114 _protected function_ `UBlueprint* GetBlueprintObj() const`
- L124 _protected prototype_ `void AddEventsCategory(IDetailLayoutBuilder& DetailBuilder, FName PropertyName, UClass* ComponentClass);` — Adds any FMulticastDelegateProperties on the given details builder with either a green "+" symbol to create a bound node, or a "view" option if it already exists. @param DetailBuilder		Details builder to add the events to @param PropertyName		Name of the selected property @param ComponentClass		The class to find any Multicast delegate properties on
- L126 _protected prototype_ `FReply HandleAddOrViewEventForVariable(const FName EventName, FName PropertyName, TWeakObjectPtr<UClass> PropertyClass);`
- L127 _protected prototype_ `int32 HandleAddOrViewIndexForButton(const FName EventName, FName PropertyName) const;`
- L131 _private member_ `TWeakObjectPtr<UBlueprint> Blueprint;` — Pointer back to my parent tab

#### class `FBlueprintVarActionDetails`  
`class FBlueprintVarActionDetails : public FBlueprintDetails`  
_L135-383_
- inherits: `FBlueprintDetails`
- desc: Details customization for variables selected in the MyBlueprint panel
- L139 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<SMyBlueprint> InMyBlueprint)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L144 _public function_ `FBlueprintVarActionDetails(TWeakPtr<SMyBlueprint> InMyBlueprint) : FBlueprintDetails(InMyBlueprint) , MyBlueprint(InMyBlueprint) , bIsVarNameInvalid(false)`
- L151 _public prototype_ `~FBlueprintVarActionDetails();`
- L154 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L156 _public prototype_ `static void PopulateCategories(SMyBlueprint* MyBlueprint, TArray<TSharedPtr<FText>>& CategorySource);`
- L160 _private prototype_ `UK2Node_Variable* EdGraphSelectionAsVar() const;` — Accessors passed to parent
- L161 _private prototype_ `FProperty* SelectionAsProperty() const;`
- L162 _private prototype_ `FName GetVariableName() const;`
- L165 _private prototype_ `bool IsAUserVariable(FProperty* VariableProperty) const;` — Commonly queried attributes about the schema action
- L166 _private prototype_ `bool IsASCSVariable(FProperty* VariableProperty) const;`
- L167 _private prototype_ `bool IsABlueprintVariable(FProperty* VariableProperty) const;`
- L168 _private prototype_ `bool IsALocalVariable(FProperty* VariableProperty) const;`
- L169 _private prototype_ `UStruct* GetLocalVariableScope(FProperty* VariableProperty) const;`
- L172 _private prototype_ `bool GetVariableNameChangeEnabled() const;` — Callbacks for uproperty details customization
- L173 _private prototype_ `FText OnGetVarName() const;`
- L174 _private prototype_ `void OnVarNameChanged(const FText& InNewText);`
- L175 _private prototype_ `void OnVarNameCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L176 _private prototype_ `bool GetVariableTypeChangeEnabled() const;`
- L177 _private prototype_ `FEdGraphPinType OnGetVarType() const;`
- L178 _private prototype_ `void OnVarTypeChanged(const FEdGraphPinType& NewPinType);`
- L179 _private prototype_ `EVisibility IsTooltipEditVisible() const;`
- L181 _private prototype_ `void OnBrowseToVarType() const;`
- L182 _private prototype_ `bool CanBrowseToVarType() const;`
- L189 _private prototype_ `void OnFinishedChangingVariable(const FPropertyChangedEvent& InPropertyChangedEvent);` — Callback when changing a variable property @param InPropertyChangedEvent	Information on the property changed
- L198 _private prototype_ `void OnFinishedChangingLocalVariable(const FPropertyChangedEvent& InPropertyChangedEvent, TSharedPtr<FStructOnScope> InStructData, TWeakObjectPtr<UK2Node_EditablePinBase> InEntryNode);` — Callback when changing a local variable property @param InPropertyChangedEvent	Information on the property changed @param InStructData				The struct data where the value of the properties are stored @param InEntryNode				Entry node where the default values of local variables are stored
- L206 _private prototype_ `void ImportNamespacesForPropertyValue(const FProperty* InProperty, const void* InContainer);` — Auto-import any namespaces associated with a variable's value into the current editor context @param InProperty				A reference to the variable property @param InContainer				A pointer to the data container (e.g. struct or object) where the property's value is stored
- L209 _private prototype_ `bool GetVariableCategoryChangeEnabled() const;` — Callback to decide if the category drop down menu should be enabled
- L211 _private prototype_ `FText OnGetTooltipText() const;`
- L212 _private prototype_ `void OnTooltipTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L214 _private prototype_ `FText OnGetCategoryText() const;`
- L215 _private prototype_ `void OnCategoryTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L216 _private prototype_ `TSharedRef< ITableRow > MakeCategoryViewWidget( TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable );`
- L217 _private prototype_ `void OnCategorySelectionChanged( TSharedPtr<FText> ProposedSelection, ESelectInfo::Type );`
- L219 _private prototype_ `EVisibility ShowEditableCheckboxVisibility() const;`
- L220 _private prototype_ `ECheckBoxState OnEditableCheckboxState() const;`
- L221 _private prototype_ `void OnEditableChanged(ECheckBoxState InNewState);`
- L223 _private prototype_ `EVisibility ShowReadOnlyCheckboxVisibility() const;`
- L224 _private prototype_ `ECheckBoxState OnReadyOnlyCheckboxState() const;`
- L225 _private prototype_ `void OnReadyOnlyChanged(ECheckBoxState InNewState);`
- L227 _private prototype_ `EVisibility GetVariableUnitsVisibility() const;`
- L228 _private prototype_ `TSharedPtr<FString> GetVariableUnits() const;`
- L229 _private prototype_ `void OnVariableUnitsChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`
- L231 _private prototype_ `ECheckBoxState OnFieldNotifyCheckboxState() const;`
- L232 _private prototype_ `void OnFieldNotifyChanged(ECheckBoxState InNewState);`
- L233 _private prototype_ `EVisibility GetFieldNotifyCheckboxListVisibility() const;`
- L235 _private prototype_ `ECheckBoxState OnCreateWidgetCheckboxState() const;`
- L236 _private prototype_ `void OnCreateWidgetChanged(ECheckBoxState InNewState);`
- L237 _private prototype_ `EVisibility Show3DWidgetVisibility() const;`
- L238 _private prototype_ `bool Is3DWidgetEnabled();`
- L240 _private prototype_ `ECheckBoxState OnGetExposedToSpawnCheckboxState() const;`
- L241 _private prototype_ `void OnExposedToSpawnChanged(ECheckBoxState InNewState);`
- L242 _private prototype_ `EVisibility ExposeOnSpawnVisibility() const;`
- L244 _private prototype_ `ECheckBoxState OnGetPrivateCheckboxState() const;`
- L245 _private prototype_ `void OnPrivateChanged(ECheckBoxState InNewState);`
- L246 _private prototype_ `EVisibility ExposePrivateVisibility() const;`
- L248 _private prototype_ `ECheckBoxState OnGetExposedToCinematicsCheckboxState() const;`
- L249 _private prototype_ `void OnExposedToCinematicsChanged(ECheckBoxState InNewState);`
- L250 _private prototype_ `EVisibility ExposeToCinematicsVisibility() const;`
- L252 _private prototype_ `ECheckBoxState OnGetConfigVariableCheckboxState() const;`
- L253 _private prototype_ `void OnSetConfigVariableState(ECheckBoxState InNewState);`
- L254 _private prototype_ `EVisibility ExposeConfigVisibility() const;`
- L255 _private prototype_ `bool IsConfigCheckBoxEnabled() const;`
- L257 _private prototype_ `FText OnGetMetaKeyValue(FName Key) const;`
- L258 _private prototype_ `void OnMetaKeyValueChanged(const FText& NewMinValue, ETextCommit::Type CommitInfo, FName Key);`
- L259 _private prototype_ `EVisibility RangeVisibility() const;`
- L261 _private prototype_ `ECheckBoxState OnBitmaskCheckboxState() const;`
- L262 _private prototype_ `EVisibility BitmaskVisibility() const;`
- L263 _private prototype_ `void OnBitmaskChanged(ECheckBoxState InNewState);`
- L265 _private prototype_ `TSharedPtr<FTopLevelAssetPath> GetBitmaskEnumTypePath() const;`
- L266 _private prototype_ `void OnBitmaskEnumTypeChanged(TSharedPtr<FTopLevelAssetPath> ItemSelected, ESelectInfo::Type SelectInfo);`
- L267 _private prototype_ `TSharedRef<SWidget> GenerateBitmaskEnumTypeWidget(TSharedPtr<FTopLevelAssetPath> Item);`
- L268 _private prototype_ `FText GetBitmaskEnumTypeName() const;`
- L270 _private prototype_ `TSharedPtr<FString> GetVariableReplicationType() const;`
- L271 _private prototype_ `void OnChangeReplication(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`
- L272 _private prototype_ `void ReplicationOnRepFuncChanged(const FString& NewOnRepFunc) const;`
- L273 _private prototype_ `EVisibility ReplicationVisibility() const;`
- L276 _private member_ `TArray<TSharedPtr<FString>> ReplicationConditionEnumTypeNames;` — Array of replication conditions for the combo text box
- L277 _private prototype_ `TSharedPtr<FString> GetVariableReplicationCondition() const;`
- L278 _private prototype_ `void OnChangeReplicationCondition(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);`
- L279 _private prototype_ `bool ReplicationConditionEnabled() const;`
- L280 _private prototype_ `bool ReplicationEnabled() const;`
- L281 _private prototype_ `FText ReplicationTooltip() const;`
- L283 _private prototype_ `EVisibility GetTransientVisibility() const;`
- L284 _private prototype_ `ECheckBoxState OnGetTransientCheckboxState() const;`
- L285 _private prototype_ `void OnTransientChanged(ECheckBoxState InNewState);`
- L287 _private prototype_ `EVisibility GetSaveGameVisibility() const;`
- L288 _private prototype_ `ECheckBoxState OnGetSaveGameCheckboxState() const;`
- L289 _private prototype_ `void OnSaveGameChanged(ECheckBoxState InNewState);`
- L291 _private prototype_ `EVisibility GetAdvancedDisplayVisibility() const;`
- L292 _private prototype_ `ECheckBoxState OnGetAdvancedDisplayCheckboxState() const;`
- L293 _private prototype_ `void OnAdvancedDisplayChanged(ECheckBoxState InNewState);`
- L295 _private prototype_ `EVisibility GetMultilineVisibility() const;`
- L296 _private prototype_ `ECheckBoxState OnGetMultilineCheckboxState() const;`
- L297 _private prototype_ `void OnMultilineChanged(ECheckBoxState InNewState);`
- L299 _private prototype_ `EVisibility GetDeprecatedVisibility() const;`
- L300 _private prototype_ `ECheckBoxState OnGetDeprecatedCheckboxState() const;`
- L301 _private prototype_ `void OnDeprecatedChanged(ECheckBoxState InNewState);`
- L303 _private prototype_ `EVisibility GetDropDownOptionsVisibility() const;`
- L304 _private prototype_ `void OnDropDownOptionSelectionChanged(TSharedPtr<FString> InString, ESelectInfo::Type);`
- L305 _private prototype_ `void OnDropDownOptionTextChanged(const FText& Text, ETextCommit::Type);`
- L306 _private prototype_ `TSharedRef<SWidget> GenerateDropDownOptionWidget(TSharedPtr<FString> InItem) const;`
- L307 _private prototype_ `void CollectDropDownOptions();`
- L308 _private prototype_ `FText GetDropDownOptionDisplayText() const;`
- L309 _private prototype_ `FString GetDropDownOptionsFunctionName() const;`
- L310 _private prototype_ `void SetDropDownOptionsFunctionName(const FString& InFunctionName);`
- L312 _private prototype_ `FText GetDeprecationMessageText() const;`
- L313 _private prototype_ `void OnDeprecationMessageTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L316 _private prototype_ `void RefreshPropertyFlags();` — Refresh the property flags list
- L319 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForPropertyList( TSharedPtr< FString > Item, const TSharedRef<STableViewBase>& OwnerTable );` — Generates the widget for the property flag list
- L322 _private prototype_ `TSharedRef<SWidget> BuildEventsMenuForVariable() const;` — Delegate to build variable events droplist menu
- L325 _private prototype_ `void OnPostEditorRefresh();` — Refreshes cached data that changes after a Blueprint recompile
- L328 _private function_ `UBlueprint* GetPropertyOwnerBlueprint() const` — Returns the Property's Blueprint
- L331 _private function_ `bool IsVariableInBlueprint() const` — Returns TRUE if the Variable is in the current Blueprint
- L334 _private prototype_ `bool IsVariableInheritedByBlueprint() const;` — Returns TRUE if the Variable is inherited by the current Blueprint
- L337 _private prototype_ `bool IsVariableDeprecated() const;` — Returns TRUE if the Variable is marked as deprecated
- L340 _private member_ `TWeakPtr<SMyBlueprint> MyBlueprint;` — Pointer back to my parent tab
- L343 _private member_ `TArray<TSharedPtr<FString>> ReplicationOptions;` — Array of replication options for our combo text box
- L346 _private member_ `TArray<TSharedPtr<FString>> DropDownFunctionOptions;` — Array of function names that can be used for GetOptions
- L349 _private member_ `TArray<TSharedPtr<FString>> UnitsOptions;` — Array of units options for our combo text box
- L352 _private member_ `TArray<TSharedPtr<FTopLevelAssetPath>> BitmaskEnumTypePaths;` — Array of enum type names for integers used as bitmasks
- L355 _private member_ `TSharedPtr<SEditableTextBox> VarNameEditableTextBox;` — The widget used when in variable name editing mode
- L358 _private member_ `bool bIsVarNameInvalid;` — Flag to indicate whether or not the variable name is invalid
- L361 _private member_ `TArray<TSharedPtr<FText>> CategorySource;` — A list of all category names to choose from
- L363 _private member_ `TWeakPtr<SComboButton> CategoryComboButton;` — Widgets for the categories
- L364 _private member_ `TWeakPtr<SListView<TSharedPtr<FText>>> CategoryListView;`
- L367 _private member_ `TArray< TSharedPtr< FString > > PropertyFlags;` — Array of names of property flags on the selected property
- L370 _private member_ `TWeakPtr< SListView< TSharedPtr< FString > > > PropertyFlagWidget;` — The listview widget for displaying property flags
- L373 _private member_ `TWeakFieldPtr<FProperty> CachedVariableProperty;` — Cached property for the variable we are affecting
- L376 _private member_ `FName CachedVariableName;` — Cached name for the variable we are affecting
- L379 _private member_ `TWeakObjectPtr<UBlueprint> PropertyOwnerBlueprint;` — Pointer back to the variable's Blueprint
- L382 _private member_ `TArray<TSharedPtr<IDetailCustomization>> ExternalDetailCustomizations;` — External detail customizations

#### class `FBaseBlueprintGraphActionDetails`  
`class FBaseBlueprintGraphActionDetails : public IDetailCustomization`  
_L385-455_
- inherits: `IDetailCustomization`
- L388 _public prototype_ `virtual ~FBaseBlueprintGraphActionDetails();`
- L390 _public function_ `FBaseBlueprintGraphActionDetails(TWeakPtr<SMyBlueprint> InMyBlueprint) : MyBlueprint(InMyBlueprint)`
- L396 _public function_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override` — IDetailCustomization interface
- L402 _public prototype_ `virtual UEdGraph* GetGraph() const;` — Gets the graph that we are currently editing
- L405 _public prototype_ `void OnParamsChanged(UK2Node_EditablePinBase* TargetNode, bool bForceRefresh = false);` — Refreshes the graph and ensures the target node is up to date
- L408 _public prototype_ `bool OnVerifyPinRename(UK2Node_EditablePinBase* InTargetNode, const FName InOldName, const FString& InNewName, FText& OutErrorMessage);` — Checks if the pin rename can occur
- L411 _public prototype_ `bool OnPinRenamed(UK2Node_EditablePinBase* TargetNode, const FName OldName, const FString& NewName);` — Refreshes the graph and ensures the target node is up to date
- L414 _public function_ `TWeakPtr<SMyBlueprint> GetMyBlueprint() const` — Gets the blueprint we're editing
- L417 _public function_ `TWeakObjectPtr<class UK2Node_EditablePinBase> GetFunctionEntryNode() const` — Gets the node for the function entry point
- L420 _public prototype_ `void SetRefreshDelegate(FSimpleDelegate RefreshDelegate, bool bForInputs);` — Sets the delegate to be called when refreshing our children
- L423 _public function_ `UBlueprint* GetBlueprintObj() const` — Accessors passed to parent
- L425 _public prototype_ `FReply OnAddNewInputClicked();`
- L428 _public prototype_ `void OnPostEditorRefresh();` — Called when blueprint changes
- L432 _protected prototype_ `bool AttemptToCreateResultNode();` — Tries to create the result node (if there are output args)
- L435 _protected member_ `TWeakPtr<SMyBlueprint> MyBlueprint;` — Pointer to the parent
- L438 _protected member_ `TWeakObjectPtr<class UK2Node_EditablePinBase> FunctionEntryNodePtr;` — The entry node in the graph
- L441 _protected member_ `TWeakObjectPtr<class UK2Node_EditablePinBase> FunctionResultNodePtr;` — The result node in the graph, if the function has any return or out params.  This can be the same as the entry point
- L444 _protected member_ `FSimpleDelegate RegenerateInputsChildrenDelegate;` — Delegates to regenerate the lists of children
- L445 _protected member_ `FSimpleDelegate RegenerateOutputsChildrenDelegate;`
- L448 _protected member_ `IDetailLayoutBuilder* DetailsLayoutPtr;` — Details layout builder we need to hold on to to refresh it at times
- L451 _protected member_ `FDelegateHandle BlueprintEditorRefreshDelegateHandle;` — Handle for graph refresh delegate
- L454 _protected member_ `TArray< TWeakObjectPtr<UObject> > ObjectsBeingEdited;` — Array of nodes were were constructed to represent

#### class `FBlueprintDelegateActionDetails`  
`class FBlueprintDelegateActionDetails : public FBaseBlueprintGraphActionDetails`  
_L457-491_
- inherits: `FBaseBlueprintGraphActionDetails`
- L461 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<SMyBlueprint> InMyBlueprint)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L466 _public function_ `FBlueprintDelegateActionDetails(TWeakPtr<SMyBlueprint> InMyBlueprint) : FBaseBlueprintGraphActionDetails(InMyBlueprint)`
- L472 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L475 _public prototype_ `virtual UEdGraph* GetGraph() const override;` — Gets the graph that we are currently editing
- L479 _private prototype_ `void SetEntryNode();`
- L481 _private prototype_ `FMulticastDelegateProperty* GetDelegateProperty() const;`
- L483 _private prototype_ `void CollectAvailibleSignatures();`
- L484 _private prototype_ `void OnFunctionSelected(TSharedPtr<FString> FunctionItemData, ESelectInfo::Type SelectInfo);`
- L485 _private prototype_ `bool IsBlueprintProperty() const;`
- L486 _private prototype_ `EVisibility OnGetSectionTextVisibility(TWeakPtr<SWidget> RowWidget) const;`
- L489 _private member_ `TArray<TSharedPtr<FString>> FunctionsToCopySignatureFrom;`
- L490 _private member_ `TSharedPtr<STextComboBox> CopySignatureComboButton;`

#### class `FBlueprintGraphArgumentGroupLayout`  
`class FBlueprintGraphArgumentGroupLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FBlueprintGraphArgumentGroupLayout>`  
_L494-517_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FBlueprintGraphArgumentGroupLayout>`
- desc: Custom struct for each group of arguments in the function editing details
- L497 _public function_ `FBlueprintGraphArgumentGroupLayout(TWeakPtr<class FBaseBlueprintGraphActionDetails> InGraphActionDetails, UK2Node_EditablePinBase* InTargetNode) : GraphActionDetailsPtr(InGraphActionDetails) , TargetNode(InTargetNode)`
- L503 _private prototype_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override;` — IDetailCustomNodeBuilder Interface
- L504 _private function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override`
- L505 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L506 _private function_ `virtual void Tick( float DeltaTime ) override`
- L507 _private function_ `virtual bool RequiresTick() const override`
- L508 _private function_ `virtual FName GetName() const override`
- L509 _private function_ `virtual bool InitiallyCollapsed() const override`
- L513 _private member_ `TWeakPtr<class FBaseBlueprintGraphActionDetails> GraphActionDetailsPtr;` — The parent graph action details customization
- L516 _private member_ `TWeakObjectPtr<UK2Node_EditablePinBase> TargetNode;` — The target node that this argument is on

#### class `FBlueprintGraphArgumentLayout`  
`class FBlueprintGraphArgumentLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FBlueprintGraphArgumentLayout>`  
_L520-600_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FBlueprintGraphArgumentLayout>`
- desc: Custom struct for each argument in the function editing details
- L523 _public function_ `FBlueprintGraphArgumentLayout(TWeakPtr<FUserPinInfo> PinInfo, UK2Node_EditablePinBase* InTargetNode, TWeakPtr<class FBaseBlueprintGraphActionDetails> InGraphActionDetails, FName InArgName, bool bInHasDefaultValue) : GraphActionDetailsPtr(InGraphActionDetails) , ParamItemPtr(PinInfo) , TargetNode(InTargetNode) , bHasDefaultValue(bInHasDefaultValue) , ArgumentName(InArgName)`
- L529 _public prototype_ `virtual ~FBlueprintGraphArgumentLayout();`
- L533 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L534 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L535 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L536 _private function_ `virtual void Tick( float DeltaTime ) override`
- L537 _private function_ `virtual bool RequiresTick() const override`
- L538 _private function_ `virtual FName GetName() const override`
- L539 _private function_ `virtual bool InitiallyCollapsed() const override`
- L543 _private prototype_ `bool ShouldPinBeReadOnly(bool bIsEditingPinType = false) const;` — Determines if this pin should not be editable
- L546 _private prototype_ `bool IsPinEditingReadOnly(bool bIsEditingPinType = false) const;` — Determines if editing the pins on the node should be read only
- L549 _private prototype_ `void OnRemoveClicked();` — Callbacks for all the functionality for modifying arguments
- L551 _private prototype_ `void OnArgumentGraphChanged(const FEdGraphEditAction& Action);`
- L553 _private prototype_ `FText OnGetArgNameText() const;`
- L554 _private prototype_ `FText OnGetArgToolTipText() const;`
- L555 _private prototype_ `void OnArgNameChange(const FText& InNewText);`
- L556 _private prototype_ `void OnArgNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L558 _private prototype_ `FEdGraphPinType OnGetPinInfo() const;`
- L559 _private prototype_ `void PinInfoChanged(const FEdGraphPinType& PinType);`
- L560 _private prototype_ `void OnPrePinInfoChange(const FEdGraphPinType& PinType);`
- L563 _private prototype_ `UEdGraphPin* GetPin() const;` — Returns the graph pin representing this variable
- L566 _private prototype_ `ECheckBoxState IsRefChecked() const;` — Returns whether the "Pass-by-Reference" checkbox is checked or not
- L567 _private prototype_ `ECheckBoxState IsConstChecked() const;`
- L570 _private prototype_ `void OnRefCheckStateChanged(ECheckBoxState InState);` — Handles toggling the "Pass-by-Reference" checkbox
- L572 _private prototype_ `void OnConstCheckStateChanged(ECheckBoxState InState);`
- L573 _private prototype_ `bool ShouldBeForceConst() const;`
- L574 _private prototype_ `bool CanChangeConst() const;`
- L578 _private member_ `TWeakPtr<class FBaseBlueprintGraphActionDetails> GraphActionDetailsPtr;` — The parent graph action details customization
- L581 _private member_ `TWeakPtr<FUserPinInfo> ParamItemPtr;` — The argument pin that this layout reflects
- L584 _private member_ `UK2Node_EditablePinBase* TargetNode;` — The target node that this argument is on
- L587 _private member_ `bool bHasDefaultValue;` — Whether or not this builder should have a default value edit control (input args only)
- L590 _private member_ `FName ArgumentName;` — The name of this argument for remembering expansion state
- L593 _private member_ `TWeakPtr<SEditableTextBox> ArgumentNameWidget;` — Holds a weak pointer to the argument name widget, used for error notifications
- L596 _private member_ `TSharedPtr<SGraphPin> DefaultValuePinWidget;` — The SGraphPin widget created to show/edit default value
- L599 _private member_ `FDelegateHandle GraphChangedHandler;` — Delegate handle for node changes

#### class `FBlueprintGraphLocalVariableGroupLayout`  
`class FBlueprintGraphLocalVariableGroupLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FBlueprintGraphLocalVariableGroupLayout>`  
_L607-644_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FBlueprintGraphLocalVariableGroupLayout>`
- desc: Custom struct for each group of local variables in the function editing details
- L610 _public function_ `FBlueprintGraphLocalVariableGroupLayout(TWeakPtr<class FBaseBlueprintGraphActionDetails> InGraphActionDetails, TWeakObjectPtr<UEdGraph> InTargetGraph, TWeakObjectPtr<UBlueprint> InBlueprintObj, TWeakObjectPtr<UFunction> InOwningFunction, TSharedPtr<IPropertyHandle> Property = nullptr) : GraphActionDetailsPtr(InGraphActionDetails) , TargetGraph(InTargetGraph) , BlueprintObj(InBlueprintObj) , PropertyHandle(Property) , OwningFunction(InOwningFunction)`
- L618 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override`
- L622 _private function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override` — IDetailCustomNodeBuilder Interface
- L623 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L624 _private function_ `virtual void Tick( float DeltaTime ) override`
- L625 _private function_ `virtual bool RequiresTick() const override`
- L626 _private function_ `virtual FName GetName() const override`
- L627 _private function_ `virtual bool InitiallyCollapsed() const override`
- L631 _private member_ `TWeakPtr<class FBaseBlueprintGraphActionDetails> GraphActionDetailsPtr;` — The parent graph action details customization
- L634 _private member_ `TWeakObjectPtr<UEdGraph> TargetGraph;` — The target graph that the local variable's are on
- L637 _private member_ `TWeakObjectPtr<UBlueprint> BlueprintObj;` — The blueprint object that the target graph is in
- L640 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — handle to property for array of FBPVariableDescription's
- L643 _private member_ `TWeakObjectPtr<UFunction> OwningFunction;` — function that owns the local variable's being displayed

#### class `FBlueprintGraphLocalVariableLayout`  
`class FBlueprintGraphLocalVariableLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FBlueprintGraphLocalVariableLayout>`  
_L647-712_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FBlueprintGraphLocalVariableLayout>`
- desc: Custom struct for each local variable in the function editing details
- L650 _public function_ `FBlueprintGraphLocalVariableLayout(TWeakObjectPtr<UFunction> InOwningFunction, const FBPVariableDescription& VariableDescription) : OwningFunction(InOwningFunction)`
- L656 _public function_ `FBlueprintGraphLocalVariableLayout(TWeakObjectPtr<UFunction> InOwningFunction, TSharedPtr<IPropertyHandle> Property = nullptr) : OwningFunction(InOwningFunction)`
- L662 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;`
- L664 _public prototype_ `const FBPVariableDescription& GetVariable() const;`
- L665 _public prototype_ `void SetVariable(const FBPVariableDescription&);`
- L669 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L670 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L671 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L672 _private function_ `virtual void Tick( float DeltaTime ) override`
- L673 _private function_ `virtual bool RequiresTick() const override`
- L674 _private function_ `virtual FName GetName() const override`
- L675 _private function_ `virtual bool InitiallyCollapsed() const override`
- L679 _private prototype_ `bool ShouldVarBeReadOnly(bool bIsEditingPinType = false) const;` — Determines if this pin should not be editable
- L682 _private prototype_ `bool IsVariableEditingReadOnly(bool bIsEditingPinType = false) const;` — Determines if editing the pins on the node should be read only
- L686 _private prototype_ `FText OnGetVarNameText() const;` — Callbacks for all the functionality for modifying local variables
- L687 _private prototype_ `FText OnGetVarToolTipText() const;`
- L688 _private prototype_ `FEdGraphPinType OnGetVariableType() const;`
- L692 _private prototype_ `void OnRemoveClicked();`
- L693 _private prototype_ `void OnVarNameChange(const FText& InNewText);`
- L694 _private prototype_ `void OnVarNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L695 _private prototype_ `void VariableTypeChanged(const FEdGraphPinType& PinType);`
- L696 _private prototype_ `void OnPreVariableTypeChange(const FEdGraphPinType& PinType);`
- L702 _private member_ `TWeakPtr<SEditableTextBox> VariableNameWidget;` — Holds a weak pointer to the argument name widget, used for error notifications
- L705 _private member_ `TSharedPtr<SGraphPin> DefaultValueWidget;` — The SGraphPin widget created to show/edit default value
- L708 _private member_ `TVariant<TSharedPtr<IPropertyHandle>, FBPVariableDescription> Data;` — either the read only copy of FBPVariableDescription or the property handle to the original variable description
- L711 _private member_ `TWeakObjectPtr<UFunction> OwningFunction;` — function that owns this local variable

#### class `FBlueprintGraphActionDetails`  
`class FBlueprintGraphActionDetails : public FBaseBlueprintGraphActionDetails`  
_L715-879_
- inherits: `FBaseBlueprintGraphActionDetails`
- desc: Details customization for functions and graphs selected in the MyBlueprint panel
- L719 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<SMyBlueprint> InMyBlueprint, bool bInShowLocalVariables = false)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L724 _public function_ `FBlueprintGraphActionDetails(TWeakPtr<SMyBlueprint> InMyBlueprint, bool bInShowLocalVariables = false) : FBaseBlueprintGraphActionDetails(InMyBlueprint) , bShowLocalVariables(bInShowLocalVariables)`
- L731 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L747 _private prototype_ `void SetEntryAndResultNodes();` — Setup for the nodes this details customizer needs to access
- L750 _private prototype_ `UK2Node_EditablePinBase* GetEditableNode() const;` — Gets the node we are currently editing if available
- L753 _private prototype_ `UFunction* FindFunction() const;` — Get function associated with the selected graph
- L756 _private prototype_ `FKismetUserDeclaredFunctionMetadata* GetMetadataBlock() const;` — Utility for editing metadata on the function
- L759 _private prototype_ `FText OnGetTooltipText() const;` — Callbacks for uproperty details customization
- L760 _private prototype_ `void OnTooltipTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L762 _private prototype_ `FText OnGetCategoryText() const;`
- L763 _private prototype_ `void OnCategoryTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L765 _private prototype_ `FText OnGetKeywordsText() const;`
- L766 _private prototype_ `void OnKeywordsTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L768 _private prototype_ `FText OnGetCompactNodeTitleText() const;`
- L769 _private prototype_ `void OnCompactNodeTitleTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L771 _private prototype_ `FText AccessSpecifierProperName( uint32 AccessSpecifierFlag ) const;`
- L772 _private prototype_ `bool IsAccessSpecifierVisible() const;`
- L773 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRowAccessSpecifier( TSharedPtr<FAccessSpecifierLabel> SpecifierName, const TSharedRef<STableViewBase>& OwnerTable );`
- L774 _private prototype_ `FText GetCurrentAccessSpecifierName() const;`
- L775 _private prototype_ `void OnAccessSpecifierSelected( TSharedPtr<FAccessSpecifierLabel> SpecifierName, ESelectInfo::Type SelectInfo );`
- L777 _private prototype_ `bool GetInstanceColorVisibility() const;`
- L778 _private prototype_ `FLinearColor GetNodeTitleColor() const;`
- L779 _private prototype_ `FReply ColorBlock_OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L781 _private prototype_ `bool IsCustomEvent() const;`
- L782 _private prototype_ `void OnIsReliableReplicationFunctionModified(const ECheckBoxState NewCheckedState);`
- L783 _private prototype_ `ECheckBoxState GetIsReliableReplicatedFunction() const;`
- L796 _private prototype_ `FText GetCurrentReplicatedEventString() const;`
- L797 _private prototype_ `FText ReplicationSpecifierProperName( uint32 ReplicationSpecifierFlag ) const;`
- L798 _private prototype_ `TSharedRef<ITableRow> OnGenerateReplicationComboWidget( TSharedPtr<FReplicationSpecifierLabel> InNetFlag, const TSharedRef<STableViewBase>& OwnerTable );`
- L800 _private prototype_ `bool IsPureFunctionVisible() const;`
- L801 _private prototype_ `void OnIsPureFunctionModified(const ECheckBoxState NewCheckedState);`
- L802 _private prototype_ `ECheckBoxState GetIsPureFunction() const;`
- L804 _private prototype_ `bool IsConstFunctionVisible() const;`
- L805 _private prototype_ `void OnIsConstFunctionModified(const ECheckBoxState NewCheckedState);`
- L806 _private prototype_ `ECheckBoxState GetIsConstFunction() const;`
- L808 _private prototype_ `bool IsExecFunctionVisible() const;`
- L809 _private prototype_ `void OnIsExecFunctionModified(const ECheckBoxState NewCheckedState);`
- L810 _private prototype_ `ECheckBoxState GetIsExecFunction() const;`
- L812 _private prototype_ `bool IsThreadSafeFunctionVisible() const;`
- L813 _private prototype_ `void OnIsThreadSafeFunctionModified(const ECheckBoxState NewCheckedState);`
- L814 _private prototype_ `ECheckBoxState GetIsThreadSafeFunction() const;`
- L816 _private prototype_ `bool IsUnsafeDuringActorConstructionVisible() const;`
- L817 _private prototype_ `void OnIsUnsafeDuringActorConstructionModified(const ECheckBoxState NewCheckedState);`
- L818 _private prototype_ `ECheckBoxState GetIsUnsafeDuringActorConstruction() const;`
- L820 _private prototype_ `bool IsFieldNotifyCheckVisible() const;`
- L821 _private prototype_ `bool GetIsFieldNotfyEnabled() const;`
- L822 _private prototype_ `ECheckBoxState OnFieldNotifyCheckboxState() const;`
- L823 _private prototype_ `void OnFieldNotifyChanged(ECheckBoxState InNewState);`
- L826 _private prototype_ `ECheckBoxState GetIsEditorCallableEvent() const;` — Determines if the selected event is identified as editor callable
- L829 _private prototype_ `void OnEditorCallableEventModified( const ECheckBoxState NewCheckedState ) const;` — Enables/Disables selected event as editor callable
- L831 _private prototype_ `bool IsFunctionDeprecated() const;`
- L832 _private prototype_ `ECheckBoxState OnGetDeprecatedCheckboxState() const;`
- L833 _private prototype_ `void OnDeprecatedChanged(ECheckBoxState InNewState);`
- L835 _private prototype_ `FText GetDeprecationMessageText() const;`
- L836 _private prototype_ `void OnDeprecationMessageTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L838 _private prototype_ `FReply OnAddNewOutputClicked();`
- L841 _private prototype_ `EVisibility GetAddNewInputOutputVisibility() const;` — Callback to determine if the "New" button for adding input/output pins is visible
- L844 _private prototype_ `bool IsAddNewInputOutputEnabled() const;` — Callback to determine if the "new" button for adding input/output pins is enabled
- L846 _private prototype_ `EVisibility OnGetSectionTextVisibility(TWeakPtr<SWidget> RowWidget) const;`
- L849 _private prototype_ `static void SetNetFlags( TWeakObjectPtr<UK2Node_EditablePinBase> FunctionEntryNode, uint32 NetFlags);` — Called to set the replication type from the details view combo
- L852 _private prototype_ `void OnCategorySelectionChanged( TSharedPtr<FText> ProposedSelection, ESelectInfo::Type );` — Callback when a graph category is changed
- L855 _private prototype_ `TSharedRef< ITableRow > MakeCategoryViewWidget( TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Callback to make category widgets
- L860 _private member_ `TArray<TSharedPtr<FAccessSpecifierLabel> > AccessSpecifierLabels;` — List of available localized access specifiers names
- L863 _private member_ `TSharedPtr< class SComboButton > AccessSpecifierComboButton;` — ComboButton with access specifiers
- L866 _private member_ `TSharedPtr<class SColorBlock> ColorBlock;` — Color block for parenting the color picker
- L869 _private member_ `TArray<TSharedPtr<FText>> CategorySource;` — A list of all category names to choose from
- L872 _private member_ `TWeakPtr<SComboButton> CategoryComboButton;` — Widgets for the categories
- L873 _private member_ `TWeakPtr<SListView<TSharedPtr<FText>>> CategoryListView;`
- L876 _private member_ `TArray<TSharedPtr<IDetailCustomization>> ExternalDetailCustomizations;` — External detail customizations
- L878 _private member_ `bool bShowLocalVariables = false;`

#### struct `FBlueprintGraphActionDetails::FAccessSpecifierLabel`  
`struct FAccessSpecifierLabel`  
_L734-742_
- L736 _public member_ `FText LocalizedName;`
- L737 _public member_ `EFunctionFlags SpecifierFlag;`
- L739 _public function_ `FAccessSpecifierLabel( FText InLocalizedName, EFunctionFlags InSpecifierFlag) : LocalizedName( InLocalizedName ), SpecifierFlag( InSpecifierFlag )`

#### struct `FBlueprintGraphActionDetails::FReplicationSpecifierLabel`  
`struct FReplicationSpecifierLabel`  
_L785-794_
- L787 _public member_ `FText LocalizedName;`
- L788 _public member_ `FText LocalizedToolTip;`
- L789 _public member_ `uint32 SpecifierFlag;`
- L791 _public function_ `FReplicationSpecifierLabel( FText InLocalizedName, uint32 InSpecifierFlag, FText InLocalizedToolTip ) : LocalizedName( InLocalizedName ), LocalizedToolTip( InLocalizedToolTip ), SpecifierFlag( InSpecifierFlag )`

#### class `FBlueprintGlobalOptionsManagedListDetails`  
`class FBlueprintGlobalOptionsManagedListDetails : public FBlueprintManagedListDetails`  
_L882-899_
- inherits: `FBlueprintManagedListDetails`
- desc: Blueprint global options - managed list details customization base
- L886 _public prototype_ `FBlueprintGlobalOptionsManagedListDetails(TWeakPtr<class FBlueprintGlobalOptionsDetails> InGlobalOptionsDetailsPtr);` — Constructor method
- L890 _protected prototype_ `UBlueprint* GetBlueprintObjectChecked() const;` — Access to external resources
- L891 _protected prototype_ `TSharedPtr<FBlueprintEditor> GetPinnedBlueprintEditorPtr() const;`
- L894 _protected prototype_ `void OnRefreshInDetailsView();` — Helper function to set the Blueprint back into the KismetInspector's details view
- L898 _private member_ `TWeakPtr<class FBlueprintGlobalOptionsDetails> GlobalOptionsDetailsPtr;` — The parent graph action details customization

#### class `FBlueprintImportsLayout`  
`class FBlueprintImportsLayout : public FBlueprintGlobalOptionsManagedListDetails, public TSharedFromThis<FBlueprintImportsLayout>`  
_L902-920_
- inherits: `FBlueprintGlobalOptionsManagedListDetails,TSharedFromThis<FBlueprintImportsLayout>`
- desc: Blueprint Imports List Details
- L905 _public prototype_ `FBlueprintImportsLayout(TWeakPtr<class FBlueprintGlobalOptionsDetails> InGlobalOptionsDetails, bool bInShowDefaultImports);`
- L909 _protected prototype_ `virtual TSharedPtr<SWidget> MakeAddItemWidget() override;` — FBlueprintManagedListDetails interface
- L910 _protected prototype_ `virtual void GetManagedListItems(TArray<FManagedListItem>& OutListItems) const override;`
- L911 _protected prototype_ `virtual void OnRemoveItem(const FManagedListItem& Item) override;`
- L914 _protected prototype_ `void OnNamespaceSelected(const FString& InNamespace);`
- L915 _protected prototype_ `void OnGetNamespacesToExclude(TSet<FString>& OutNamespacesToExclude) const;`
- L919 _private member_ `bool bShouldShowDefaultImports;` — Whether we should show default (i.e. global) imports versus custom (i.e. local) imports

#### class `FBlueprintInterfaceLayout`  
`class FBlueprintInterfaceLayout : public FBlueprintGlobalOptionsManagedListDetails, public TSharedFromThis<FBlueprintInterfaceLayout>`  
_L923-951_
- inherits: `FBlueprintGlobalOptionsManagedListDetails,TSharedFromThis<FBlueprintInterfaceLayout>`
- desc: Blueprint Interface List Details
- L926 _public prototype_ `FBlueprintInterfaceLayout(TWeakPtr<class FBlueprintGlobalOptionsDetails> InGlobalOptionsDetails, TSharedPtr<IPropertyHandle> InInterfacesProperty = nullptr);`
- L929 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override;` — IDetailCustomNodeBuilder interface
- L933 _protected prototype_ `virtual TSharedPtr<SWidget> MakeAddItemWidget() override;` — FBlueprintManagedListDetails interface
- L934 _protected prototype_ `virtual void GetManagedListItems(TArray<FManagedListItem>& OutListItems) const override;`
- L935 _protected prototype_ `virtual void OnRemoveItem(const FManagedListItem& Item) override;`
- L940 _private prototype_ `TSharedRef<SWidget> OnGetAddInterfaceMenuContent();` — Callbacks for details UI
- L943 _private prototype_ `void OnClassPicked(UClass* PickedClass);` — Callback function when an interface class is picked
- L947 _private member_ `TSharedPtr<SComboButton> AddInterfaceComboButton;` — The add interface combo button
- L950 _private member_ `TSharedPtr<IPropertyHandle> InterfacesProperty;` — Property that stores interfaces

#### class `FBlueprintGlobalOptionsDetails`  
`class FBlueprintGlobalOptionsDetails : public IDetailCustomization`  
_L954-1048_
- inherits: `IDetailCustomization`
- desc: Details customization for Blueprint settings
- L958 _public function_ `FBlueprintGlobalOptionsDetails(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr) :BlueprintEditorPtr(InBlueprintEditorPtr) ,BlueprintObjOverride(nullptr)` — Constructor
- L965 _public function_ `FBlueprintGlobalOptionsDetails(TWeakObjectPtr<UBlueprint> InBlueprintPtr) :BlueprintObjOverride(InBlueprintPtr)`
- L972 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L979 _public function_ `static TSharedRef<IDetailCustomization> MakeInstanceForDiff(TWeakObjectPtr<UBlueprint> InBlueprintPtr)` — Diff functionality doesn't need access to the FBlueprintEditor so this allows creation without editor access but with limited functionality
- L985 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L988 _public prototype_ `UBlueprint* GetBlueprintObj() const;` — Gets the Blueprint being edited
- L991 _public function_ `TWeakPtr<FBlueprintEditor> GetBlueprintEditorPtr() const` — Gets the Blueprint editor
- L995 _protected prototype_ `FText GetParentClassName() const;` — Gets the Blueprint parent class name text
- L998 _protected prototype_ `bool CanReparent() const;` — Determine whether or not we should be allowed to reparent (but still display the parent class regardless)
- L1001 _protected prototype_ `TSharedRef<SWidget> GetParentClassMenuContent();` — Gets the menu content that's displayed when the parent class combo box is clicked
- L1004 _protected prototype_ `void OnClassPicked(UClass* SelectedClass);` — Delegate called when a class is selected from the class picker
- L1007 _protected prototype_ `bool CanDeprecateBlueprint() const;` — Returns TRUE if the Blueprint can be deprecated
- L1010 _protected prototype_ `void OnDeprecateBlueprint(ECheckBoxState InCheckState);` — Callback when toggling the Deprecate checkbox, handles marking a Blueprint as deprecated
- L1013 _protected prototype_ `ECheckBoxState IsDeprecatedBlueprint() const;` — Callback for Deprecate checkbox, returns checked if the Blueprint is deprecated
- L1016 _protected prototype_ `FText GetDeprecatedTooltip() const;` — Returns the tooltip explaining deprecation
- L1019 _protected prototype_ `void OnNamespaceValueCommitted(const FString& InNamespace);` — Callback for when a new Blueprint namespace value is entered
- L1022 _protected prototype_ `bool ShouldShowNamespaceResetToDefault() const;` — Determine Blueprint namespace "reset to default" button visibility
- L1025 _protected prototype_ `void OnNamespaceResetToDefaultValue();` — Invoked when the Blueprint namespace "reset to default" button is clicked
- L1028 _protected prototype_ `void HandleNamespaceValueChange(const FString& InOldValue, const FString& InNewValue);` — Called when the assigned Blueprint namespace value is changed
- L1032 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the Blueprint editor
- L1035 _private member_ `TWeakObjectPtr<UBlueprint> BlueprintObjOverride;` — Weak reference to a Blueprint override - used to customize a blueprint that is displayed without an editor, e.g. for diff
- L1038 _private member_ `TSharedPtr<SComboButton> ParentClassComboButton;` — Combo button used to choose a parent class
- L1041 _private member_ `TSharedPtr<IPropertyHandle> NamespacePropertyHandle;` — Handle to the customized namespace property
- L1044 _private member_ `TSharedPtr<SBlueprintNamespaceEntry> NamespaceValueWidget;` — Widget used for namespace value customization
- L1047 _private member_ `static float NamespacePropertyValueCustomization_MinDesiredWidth;` — Desired width for namespace value customization

#### class `FBlueprintComponentDetails`  
`class FBlueprintComponentDetails : public FBlueprintDetails`  
_L1053-1117_
- inherits: `FBlueprintDetails`
- desc: Details customization for Blueprint Component settings
- L1057 _public function_ `FBlueprintComponentDetails(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr) : FBlueprintDetails(InBlueprintEditorPtr) , BlueprintEditorPtr(InBlueprintEditorPtr) , bIsVariableNameInvalid(false)` — Constructor
- L1066 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L1072 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L1076 _protected prototype_ `FText OnGetVariableText() const;` — Callbacks for widgets
- L1077 _protected prototype_ `void OnVariableTextChanged(const FText& InNewText);`
- L1078 _protected prototype_ `void OnVariableTextCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L1079 _protected prototype_ `FText OnGetTooltipText() const;`
- L1080 _protected prototype_ `void OnTooltipTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L1081 _protected prototype_ `bool OnVariableCategoryChangeEnabled() const;`
- L1082 _protected prototype_ `FText OnGetVariableCategoryText() const;`
- L1083 _protected prototype_ `void OnVariableCategoryTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L1084 _protected prototype_ `void OnVariableCategorySelectionChanged(TSharedPtr<FText> ProposedSelection, ESelectInfo::Type );`
- L1085 _protected prototype_ `TSharedRef<ITableRow> MakeVariableCategoryViewWidget(TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L1086 _protected prototype_ `const UClass* GetSelectedEntryClass() const;`
- L1087 _protected prototype_ `void HandleNewEntryClassSelected(const UClass* NewEntryClass) const;`
- L1089 _protected prototype_ `FText GetSocketName() const;`
- L1090 _protected prototype_ `bool CanChangeSocket() const;`
- L1091 _protected prototype_ `void OnBrowseSocket();`
- L1092 _protected prototype_ `void OnClearSocket();`
- L1094 _protected prototype_ `void OnSocketSelection( FName SocketName );`
- L1096 _protected prototype_ `void PopulateVariableCategories();`
- L1100 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the Blueprint editor
- L1103 _private member_ `TSharedPtr<FSubobjectEditorTreeNode> CachedNodePtr;` — The cached tree Node we're editing
- L1106 _private member_ `TSharedPtr<SEditableTextBox> VariableNameEditableTextBox;` — The widget used when in variable name editing mode
- L1109 _private member_ `bool bIsVariableNameInvalid;` — Flag to indicate whether or not the variable name is invalid
- L1112 _private member_ `TArray<TSharedPtr<FText>> VariableCategorySource;` — A list of all category names to choose from
- L1115 _private member_ `TSharedPtr<SComboButton> VariableCategoryComboButton;` — Widgets for the categories
- L1116 _private member_ `TSharedPtr<SListView<TSharedPtr<FText>>> VariableCategoryListView;`

#### class `FBlueprintGraphNodeDetails`  
`class FBlueprintGraphNodeDetails : public IDetailCustomization`  
_L1120-1164_
- inherits: `IDetailCustomization`
- desc: Details customization for All Graph Nodes
- L1124 _public function_ `FBlueprintGraphNodeDetails(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr) : GraphNodePtr(NULL) , BlueprintEditorPtr(InBlueprintEditorPtr)` — Constructor
- L1132 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L1138 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L1143 _protected prototype_ `UBlueprint* GetBlueprintObj() const;` — Returns the currently edited blueprint
- L1148 _private prototype_ `void SetNameError( const FText& Error );` — Set error to name textbox
- L1151 _private prototype_ `FText OnGetName() const;` — Callbacks for uproperty details customization
- L1152 _private prototype_ `bool IsNameReadOnly() const;`
- L1153 _private prototype_ `void OnNameChanged(const FText& InNewText);`
- L1154 _private prototype_ `void OnNameCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L1157 _private member_ `TSharedPtr<SEditableTextBox> NameEditableTextBox;` — The widget used when editing a singleline name
- L1159 _private member_ `TSharedPtr<SMultiLineEditableTextBox> MultiLineNameEditableTextBox;` — The widget used when editing a multiline name
- L1161 _private member_ `TWeakObjectPtr<UEdGraphNode> GraphNodePtr;` — The target GraphNode
- L1163 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the Blueprint editor

#### class `FChildActorComponentDetails`  
`class FChildActorComponentDetails : public IDetailCustomization`  
_L1167-1182_
- inherits: `IDetailCustomization`
- desc: Details customization for ChildActorComponents
- L1171 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FBlueprintEditor> BlueprintEditorPtr);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L1174 _public prototype_ `FChildActorComponentDetails(TWeakPtr<FBlueprintEditor> BlueprintEditorPtr);` — Constructor
- L1177 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L1181 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the Blueprint editor

#### class `FBlueprintDocumentationDetails`  
`class FBlueprintDocumentationDetails : public IDetailCustomization`  
_L1185-1248_
- inherits: `IDetailCustomization`
- desc: Details customization for Blueprint Documentation
- L1189 _public function_ `FBlueprintDocumentationDetails(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr) : BlueprintEditorPtr(InBlueprintEditorPtr)` — Constructor
- L1195 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TWeakPtr<FBlueprintEditor> InBlueprintEditorPtr)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L1201 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L1206 _protected function_ `UBlueprint* GetBlueprintObj() const` — Accessors passed to parent
- L1209 _protected prototype_ `TWeakObjectPtr<UEdGraphNode_Documentation> EdGraphSelectionAsDocumentNode();` — Get the currently selected node from the edgraph
- L1212 _protected prototype_ `FText OnGetDocumentationLink() const;` — Accessor for the current nodes documentation link
- L1215 _protected prototype_ `FText OnGetDocumentationExcerpt() const;` — Accessor for the nodes current documentation excerpt
- L1218 _protected prototype_ `bool OnExcerptChangeEnabled() const;` — Accessor to evaluate if the current excerpt can be modified
- L1221 _protected prototype_ `void OnDocumentationLinkCommitted( const FText& InNewName, ETextCommit::Type InTextCommit );` — Handler for the documentation link being committed
- L1224 _protected prototype_ `TSharedRef< ITableRow > MakeExcerptViewWidget( TSharedPtr<FString> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Generate table row for excerpt combo
- L1227 _protected prototype_ `void OnExcerptSelectionChanged( TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo );` — Apply selection changes from the excerpt combo
- L1230 _protected prototype_ `TSharedRef<SWidget> GenerateExcerptList();` — Generate excerpt list widget from documentation page
- L1236 _private member_ `FString DocumentationLink;` — Documentation Link
- L1238 _private member_ `FString DocumentationExcerpt;` — Current Excerpt
- L1240 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the Blueprint editor
- L1242 _private member_ `TWeakObjectPtr<UEdGraphNode_Documentation> DocumentationNodePtr;` — The editor node we're editing
- L1244 _private member_ `TSharedPtr<SComboButton> ExcerptComboButton;` — Excerpt combo widget
- L1246 _private member_ `TArray<TSharedPtr<FString>> ExcerptList;` — Excerpt List

#### Free symbols / members of external scopes

- L74 _namespace_ `namespace EVariableReplication`
- L604 _macro_ `#define UE_BP_LOCAL_VAR_LAYOUT_SETTERS_IMPLEMENTED false` — local variables in the details view only support read-only mode at the moment. the incomplete read/write functionality can be turned on by setting this to true but you'll have to write some more code to make it compile/work

### `Source/Editor/Kismet/Private/BlueprintEditorCommands.h` (Private)


#### class `FBlueprintEditorCommands`  
`class FBlueprintEditorCommands : public TCommands<FBlueprintEditorCommands>`  
_L24-90_
- inherits: `TCommands<FBlueprintEditorCommands>`
- desc: Set of kismet 2 wide commands
- L28 _public function_ `FBlueprintEditorCommands() : TCommands<FBlueprintEditorCommands>( TEXT("BlueprintEditor"), NSLOCTEXT("Contexts", "BlueprintEditor", "Blueprint Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L33 _public prototype_ `virtual void RegisterCommands() override;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > CompileBlueprint;` — File-ish commands
- L38 _public member_ `TSharedPtr< FUICommandInfo > RefreshAllNodes;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > DeleteUnusedVariables;`
- L40 _public member_ `TSharedPtr< FUICommandInfo > FindInBlueprints;`
- L42 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesFromClass;`
- L43 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesFromBlueprint;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > RepairCorruptedBlueprint;`
- L47 _public member_ `TSharedPtr< FUICommandInfo > FindInBlueprint;` — Edit commands
- L48 _public member_ `TSharedPtr< FUICommandInfo > ReparentBlueprint;`
- L51 _public member_ `TSharedPtr< FUICommandInfo > ZoomToWindow;` — View commands
- L52 _public member_ `TSharedPtr< FUICommandInfo > ZoomToSelection;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > NavigateToParent;`
- L54 _public member_ `TSharedPtr< FUICommandInfo > NavigateToParentBackspace;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > NavigateToChild;`
- L58 _public member_ `TSharedPtr< FUICommandInfo > ResetCamera;` — Preview commands
- L59 _public member_ `TSharedPtr< FUICommandInfo > EnableSimulation;`
- L60 _public member_ `TSharedPtr< FUICommandInfo > ShowFloor;`
- L61 _public member_ `TSharedPtr< FUICommandInfo > ShowGrid;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > EnableAllBreakpoints;` — Debugging commands
- L65 _public member_ `TSharedPtr< FUICommandInfo > DisableAllBreakpoints;`
- L66 _public member_ `TSharedPtr< FUICommandInfo > ClearAllBreakpoints;`
- L67 _public member_ `TSharedPtr< FUICommandInfo > ClearAllWatches;`
- L68 _public member_ `TSharedPtr< FUICommandInfo > OpenBlueprintDebugger;`
- L71 _public member_ `TSharedPtr< FUICommandInfo > AddNewVariable;` — New documents
- L72 _public member_ `TSharedPtr< FUICommandInfo > AddNewLocalVariable;`
- L73 _public member_ `TSharedPtr< FUICommandInfo > AddNewFunction;`
- L74 _public member_ `TSharedPtr< FUICommandInfo > AddNewMacroDeclaration;`
- L75 _public member_ `TSharedPtr< FUICommandInfo > AddNewAnimationLayer;`
- L76 _public member_ `TSharedPtr< FUICommandInfo > AddNewEventGraph;`
- L77 _public member_ `TSharedPtr< FUICommandInfo > AddNewDelegate;`
- L80 _public member_ `TSharedPtr< FUICommandInfo > SaveIntermediateBuildProducts;` — Development commands
- L81 _public member_ `TSharedPtr< FUICommandInfo > GenerateSearchIndex;`
- L82 _public member_ `TSharedPtr< FUICommandInfo > DumpCachedIndexData;`
- L83 _public member_ `TSharedPtr< FUICommandInfo > ShowActionMenuItemSignatures;`
- L86 _public member_ `TSharedPtr< FUICommandInfo > BeginBlueprintMerge;` — SSC commands
- L89 _public member_ `TSharedPtr< FUICommandInfo > ToggleHideUnrelatedNodes;` — Toggle focusing nodes which are related to the selected nodes

#### class `FBlueprintSpawnNodeCommands`  
`class FBlueprintSpawnNodeCommands : public TCommands<FBlueprintSpawnNodeCommands>`  
_L96-120_
- inherits: `TCommands<FBlueprintSpawnNodeCommands>`
- desc: Handles spawn node commands for the Blueprint Editor
- L100 _public function_ `FBlueprintSpawnNodeCommands() : TCommands<FBlueprintSpawnNodeCommands>(TEXT("BlueprintEditorSpawnNodes"), NSLOCTEXT("Contexts", "BlueprintEditor_SpawnNodes", "Blueprint Editor - Spawn Nodes by chord"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L105 _public prototype_ `virtual void RegisterCommands() override;`
- L115 _public prototype_ `void GetGraphActionByChord(FInputChord& InChord, UEdGraph* InDestGraph, FVector2D& InOutDestPosition, TArray<UEdGraphNode*>& OutNodes) const;` — Returns a graph action assigned to the passed in chord @param InChord					The chord to use for lookup @param InDestGraph				The graph to create the graph action for, used for validation purposes and to link any important node data to the graph @param InOutDestPosition			Position to start placing nodes, will be updated to be at the next safe position for node placement @param OutNodes					All nodes spawned by this operation
- L119 _private member_ `TArray< TSharedPtr< class FNodeSpawnInfo > > NodeCommands;` — An array of all the possible commands for spawning nodes

#### class `FSCSEditorViewportCommands`  
`class FSCSEditorViewportCommands : public TCommands<FSCSEditorViewportCommands>`  
_L125-136_
- inherits: `TCommands<FSCSEditorViewportCommands>`
- L129 _public function_ `FSCSEditorViewportCommands() : TCommands<FSCSEditorViewportCommands>(TEXT("SCSEditorViewport"), NSLOCTEXT("Contexts", "SCSEditorViewport", "SCS Editor Viewport"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L133 _public prototype_ `virtual void RegisterCommands() override;`
- L135 _public member_ `TSharedPtr< FUICommandInfo > DeleteComponent;`

### `Source/Editor/Kismet/Private/BlueprintEditorEdMode.h` (Private)


#### class `UBlueprintEditorEdMode`  
`class UBlueprintEditorEdMode : public UAssetEdModeDefault`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UAssetEdModeDefault`
- L15 _public member_ `static inline const FEditorModeID Id = TEXT("Blu`
- L17 _public prototype_ `UBlueprintEditorEdMode();`
- L19 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L20 _public prototype_ `virtual EEditAction::Type GetActionDragDuplicate() override;`

### `Source/Editor/Kismet/Private/BlueprintEditorSCSEditorUICustomization.h` (Private)


#### class `FFBlueprintEditorSCSEditorUICustomization`  
`class FFBlueprintEditorSCSEditorUICustomization : public ISCSEditorUICustomization`  
_L9-41_
- inherits: `ISCSEditorUICustomization`
- L12 _public prototype_ `static TSharedPtr<FFBlueprintEditorSCSEditorUICustomization> GetInstance();`
- L14 _public prototype_ `virtual ~FFBlueprintEditorSCSEditorUICustomization() override = default;`
- L16 _public prototype_ `virtual bool HideComponentsTree(TArrayView<UObject*> Context) const override;`
- L18 _public prototype_ `virtual bool HideComponentsFilterBox(TArrayView<UObject*> Context) const override;`
- L20 _public prototype_ `virtual bool HideAddComponentButton(TArrayView<UObject*> Context) const override;`
- L22 _public prototype_ `virtual bool HideBlueprintButtons(TArrayView<UObject*> Context) const override;`
- L24 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FSubobjectData&) const override;`
- L25 _public prototype_ `virtual TSharedPtr<SWidget> GetControlsWidget(TSharedRef<SSubobjectEditor>& SubobjectEditor, const FSubobjectData&) const override;`
- L27 _public prototype_ `virtual EChildActorComponentTreeViewVisualizationMode GetChildActorVisualizationMode() const override;`
- L29 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentTypeFilter(TArrayView<UObject*> Context) const override;`
- L31 _public prototype_ `void AddCustomization(TSharedPtr<ISCSEditorUICustomization> Customization);`
- L32 _public prototype_ `void RemoveCustomization(TSharedPtr<ISCSEditorUICustomization> Customization);`
- L34 _public prototype_ `virtual bool SortSubobjectData(TArray<FSubobjectDataHandle>& SubobjectData) override;`
- L37 _private prototype_ `FFBlueprintEditorSCSEditorUICustomization();`
- L39 _private member_ `static TSharedPtr<FFBlueprintEditorSCSEditorUICustomization> Instance;`
- L40 _private member_ `TArray<TSharedPtr<ISCSEditorUICustomization>> Customizations;`

#### class `FFBlueprintEditorDefaultSortUICustomization`  
`class FFBlueprintEditorDefaultSortUICustomization : public ISCSEditorUICustomization`  
_L43-54_
- inherits: `ISCSEditorUICustomization`
- L46 _public prototype_ `static TSharedPtr<FFBlueprintEditorDefaultSortUICustomization> GetInstance();`
- L48 _public prototype_ `virtual bool SortSubobjectData(TArray<FSubobjectDataHandle>& SubobjectData) override;`
- L51 _private prototype_ `FFBlueprintEditorDefaultSortUICustomization() = default;`
- L53 _private member_ `static TSharedPtr<FFBlueprintEditorDefaultSortUICustomization> Instance;`

### `Source/Editor/Kismet/Private/BlueprintEditorTabFactories.h` (Private)


#### struct `FLocalKismetCallbacks`  
`struct FLocalKismetCallbacks`  
_L34-63_
- L36 _public function_ `static FText GetObjectName(UObject* Object)`
- L41 _public function_ `static FText GetGraphDisplayName(const UEdGraph* Graph)`

#### struct `FDefaultsEditorSummoner`  
`struct FDefaultsEditorSummoner : public FWorkflowTabFactory`  
_L68-87_
- inherits: `FWorkflowTabFactory`
- L71 _public prototype_ `FDefaultsEditorSummoner(TSharedPtr<class FBlueprintEditor> InHostingApp);`
- L73 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L75 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`
- L81 _private prototype_ `TSharedRef<SWidget> CreateOptionalDataOnlyMessage() const;`
- L82 _private prototype_ `TSharedRef<SWidget> CreateOptionalEditableWarning() const;`
- L84 _private prototype_ `void OnChangeBlueprintToNotDataOnly();`
- L86 _private member_ `TWeakObjectPtr<UBlueprint> EditingBlueprint;`

#### struct `FGraphTabHistory`  
`struct FGraphTabHistory : public FGenericTabHistory`  
_L92-122_
- inherits: `FGenericTabHistory`
- L99 _public function_ `FGraphTabHistory(TSharedPtr<FDocumentTabFactory> InFactory, TSharedPtr<FTabPayload> InPayload) : FGenericTabHistory(InFactory, InPayload) , SavedLocation(FVector2f::ZeroVector) , SavedZoomAmount(INDEX_NONE)` — @param InFactory		The factory used to regenerate the content @param InPayload		The payload object used to regenerate the content
- L107 _public prototype_ `virtual void EvokeHistory(TSharedPtr<FTabInfo> InTabInfo, bool bPrevTabMatches) override;`
- L109 _public prototype_ `virtual void SaveHistory() override;`
- L111 _public prototype_ `virtual void RestoreHistory() override;`
- L115 _private member_ `TWeakPtr< class SGraphEditor > GraphEditor;` — The graph editor represented by this history node. While this node is inactive, the graph editor is invalid
- L117 _private member_ `FDeprecateSlateVector2D SavedLocation;` — Saved location the graph editor was at when this history node was last visited
- L119 _private member_ `float SavedZoomAmount;` — Saved zoom the graph editor was at when this history node was last visited
- L121 _private member_ `FGuid SavedBookmarkId;` — Saved bookmark ID the graph editor was at when this history node was last visited

#### struct `FGraphEditorSummoner`  
`struct FGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>`  
_L127-157_
- inherits: `FDocumentTabFactoryForObjects<UEdGraph>`
- L130 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`
- L132 _public prototype_ `FGraphEditorSummoner(TSharedPtr<class FBlueprintEditor> InBlueprintEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L134 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L136 _public prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> Tab) const override;`
- L138 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L140 _public prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L143 _protected function_ `virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override`
- L148 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L150 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L152 _protected prototype_ `virtual TSharedRef<FGenericTabHistory> CreateTabHistoryNode(TSharedPtr<FTabPayload> Payload) override;`
- L155 _protected member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;`
- L156 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### struct `FTimelineEditorSummoner`  
`struct FTimelineEditorSummoner : public FDocumentTabFactoryForObjects<UTimelineTemplate>`  
_L162-189_
- inherits: `FDocumentTabFactoryForObjects<UTimelineTemplate>`
- L165 _public prototype_ `FTimelineEditorSummoner(TSharedPtr<class FBlueprintEditor> InBlueprintEditorPtr);`
- L167 _protected prototype_ `virtual TAttribute<FText> ConstructTabNameForObject(UTimelineTemplate* DocumentID) const override;`
- L169 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UTimelineTemplate* DocumentID) const override;`
- L171 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UTimelineTemplate* DocumentID) const override;`
- L173 _protected prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L180 _protected prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L182 _protected function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`
- L188 _protected member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;`

#### struct `FConstructionScriptEditorSummoner`  
`struct FConstructionScriptEditorSummoner : public FWorkflowTabFactory`  
_L194-205_
- inherits: `FWorkflowTabFactory`
- L197 _public prototype_ `FConstructionScriptEditorSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L199 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L201 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FSCSViewportSummoner`  
`struct FSCSViewportSummoner : public FWorkflowTabFactory`  
_L210-217_
- inherits: `FWorkflowTabFactory`
- L213 _public prototype_ `FSCSViewportSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L215 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L216 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`

#### struct `FPaletteSummoner`  
`struct FPaletteSummoner : public FWorkflowTabFactory`  
_L222-233_
- inherits: `FWorkflowTabFactory`
- L225 _public prototype_ `FPaletteSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L227 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L229 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FBookmarksSummoner`  
`struct FBookmarksSummoner : public FWorkflowTabFactory`  
_L238-249_
- inherits: `FWorkflowTabFactory`
- L241 _public prototype_ `FBookmarksSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L243 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L245 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FMyBlueprintSummoner`  
`struct FMyBlueprintSummoner : public FWorkflowTabFactory`  
_L254-265_
- inherits: `FWorkflowTabFactory`
- L257 _public prototype_ `FMyBlueprintSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L259 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L261 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FReplaceNodeReferencesSummoner`  
`struct FReplaceNodeReferencesSummoner : public FWorkflowTabFactory`  
_L270-281_
- inherits: `FWorkflowTabFactory`
- L273 _public prototype_ `FReplaceNodeReferencesSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L275 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L277 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FFindResultsSummoner`  
`struct FFindResultsSummoner : public FWorkflowTabFactory`  
_L286-297_
- inherits: `FWorkflowTabFactory`
- L289 _public prototype_ `FFindResultsSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L291 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L293 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### Free symbols / members of external scopes

- L29 _macro_ `#define LOCTEXT_NAMESPACE "BlueprintEditor"`
- L130 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`

### `Source/Editor/Kismet/Private/BlueprintNamespacePathTree.h` (Private)


#### struct `FBlueprintNamespacePathTree`  
`struct FBlueprintNamespacePathTree`  
_L11-213_
- desc: Data type used to store and retrieve Blueprint namespace path components. Note: Namespace identifier strings are expected to be of the form: "X.Y.Z"
- L15 _public member_ `inline static const TCHAR PathSeparator[] = TEXT(".")` — Path separator; can be used for path parsing as well as path construction.
- L41 _public function_ `FBlueprintNamespacePathTree()`
- L47 _public function_ `TSharedRef<FNode> GetRootNode() const`
- L61 _public function_ `TSharedPtr<FNode> FindPathNode(const FString& InPath, bool bMatchFirstInclusivePath = false) const` — Attempts to locate an added path node that represents the given identifier string. @param InPath					A Blueprint namespace path identifier string (e.g. "X.Y.Z"). @param bMatchFirstInclusivePath	Whether to match on any prefix that represents an explicitly-added path (e.g. "X.Y.*"). @return A valid path node if the search was successful.
- L93 _public function_ `void AddPath(const FString& InPath)` — Adds the given namespace identifier string as an explicitly-added path. @param InPath	A Blueprint namespace path identifier string (e.g. "X.Y.Z").
- L112 _public function_ `void RemovePath(const FString& InPath)` — Removes the given namespace identifier string as an explicitly-added path. @param InPath	A Blueprint namespace path identifier string (e.g. "X.Y.Z").
- L182 _public typedef_ `typedef TFunctionRef<void(const TArray<FName>& , TSharedRef<const FBlueprintNamespacePathTree::FNode> )> FNodeVisitorFunc;` — Path node visitor function signature. @param CurrentPath	Current path (represented as a stack of names). @param Node			A read-only reference to the node at the current visitor level.
- L189 _public function_ `void ForeachNode(FNodeVisitorFunc VisitorFunc) const` — A utility method that will recursively visit all added nodes. @param VisitorFunc	A function that will be called for each visited node.
- L197 _protected function_ `void RecursiveNodeVisitor(TSharedPtr<FBlueprintNamespacePathTree::FNode> Node, TArray<FName>& CurrentPath, FNodeVisitorFunc VisitorFunc) const` — Helper method for recursively visiting all nodes.
- L212 _private member_ `TSharedPtr<FNode> RootNode;`

#### struct `FBlueprintNamespacePathTree::FNode`  
`struct FNode : TSharedFromThis<FNode>`  
_L18-39_
- inherits: `TSharedFromThis<FNode>`
- desc: Path tree node structure.
- L21 _public member_ `bool bIsAddedPath = false;` — If TRUE, this node marks the end of an explicitly-added path string. Allows for "wildcard" paths which are inclusive of all subtrees.
- L24 _public member_ `TMap<FName, TSharedPtr<struct FNode>> Children;` — Maps path component names to any added child nodes (subtrees).
- L27 _public function_ `TSharedRef<FNode> FindOrAddChild(const FName& InKey)` — Find or add the subtree associated with the given path component name as the key.

#### Free symbols / members of external scopes

- L117 _typedef_ `using FPathTraceNode = TTuple<FName, TSharedPtr<FNode>>;` (scope `FBlueprintNamespacePathTree::RemovePath`)

### `Source/Editor/Kismet/Private/BlueprintWarningsConfigurationPanel.h` (Private)


#### class `SBlueprintWarningsConfigurationPanel`  
`class SBlueprintWarningsConfigurationPanel : public SCompoundWidget`  
_L21-41_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SBlueprintWarningsConfigurationPanel)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `void UpdateSelectedWarningBehaviors(EBlueprintWarningBehavior NewBehavior, const FBlueprintWarningDeclaration& AlteredWarning );`
- L34 _private member_ `TArray<TSharedPtr<FBlueprintWarningDeclaration>> CachedBlueprintWarningData;` — SListView requires TArray<TSharedRef<FFoo>> so we cache off a list from core:
- L36 _private member_ `TArray<TSharedPtr<EBlueprintWarningBehavior>> CachedBlueprintWarningBehaviors;` — Again, SListView boilerplate:
- L38 _private member_ `TSharedPtr< FBlueprintWarningListView > ListView;` — Storing the listview, so we can apply updates to all selected entries:
- L40 _private member_ `TSharedPtr<SSettingsEditorCheckoutNotice> SettingsEditorCheckoutNotice;` — Stored so that we can only enable controls when the settings files is writable:

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TSharedPtr<FBlueprintWarningDeclaration> FBlueprintWarningListEntry;`
- L19 _typedef_ `typedef SListView<FBlueprintWarningListEntry> FBlueprintWarningListView;`

### `Source/Editor/Kismet/Private/Blueprints/BulkNewClassReinstancer.h` (Private)


#### struct `UE::Private::FBulkNewClassReinstancer`  
`struct FBulkNewClassReinstancer : public IClassReinstancer`  
_L17-32_
- inherits: `IClassReinstancer`
- L19 _public prototype_ `FBulkNewClassReinstancer(TArray<UClass*>& InOutClasses);`
- L20 _public prototype_ `virtual ~FBulkNewClassReinstancer();`
- L21 _public prototype_ `virtual void DoReinstance(const TMap<UClass*, UClass*>& OldClassToNewClass) override;`
- L23 _private prototype_ `static void ReparentHierarchiesFast(const TMap<UClass*, UClass*>& OldClassToNewClass);`
- L24 _private prototype_ `void MapIdenticalClasses(const TMap<UClass*, UClass*>& OldClassToNewClass, TMap<UClass*, UClass*>& OutOldToNewFastReinstancing);`
- L25 _private prototype_ `void StoreIdentities(TArrayView<UClass*> InClasses);`
- L26 _private prototype_ `FBlake3Hash CalculateClassIdentity(const UClass* ForClass);`
- L28 _private member_ `TMap<UClass*, FBlake3Hash> OriginalClassIdentities;`
- L31 _private member_ `TMap<FString, FUtf8String> DebugClassIdentity;` — This is typically not populated, and is only used when BP.bPrintFastReinstancingMismatches is set:

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Private` (scope `UE`)

### `Source/Editor/Kismet/Private/Blueprints/JsonObjectGraphFunctionLibrary.h` (Private)


#### class `UJsonObjectGraphFunctionLibrary`  
`class UJsonObjectGraphFunctionLibrary : public UBlueprintFunctionLibrary`  
_L11-64_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L36 _public prototype_ `static void Stringify(const TArray<UObject*>& RootObjects, FJsonStringifyOptions Options, FString& ResultString);` — `UFUNCTION(BlueprintCallable, Category = "Experimental|Json")` — ! EXPERIMENTAL ! Writes the provided objects to a string output, using the JsonObjectGraph format. Reachable nested objects will be included automatically. Objects not within a root should be included in RootObjects if they want to be deeply represented in the result string Examples of invocation from python: Print an object: print( unreal.JsonObjectGraphFunctionLibrary.stringify([object], tuple()) ) Print a list objects: print( unreal.JsonObjectGraphFunctionLibrary.stringify(objects, tuple()) ) Print an object's entire package: print( unreal.JsonObjectGraphFunctionLibrary.stringify([unreal.EditorAssetLibrary.get_package_for_object(object)], tuple()) ) @param	RootObjects		The objects to write at the root level @param	Options			Options controlling the written format @param	ResultString	The objects stringified
- L50 _public prototype_ `static void WritePackageToTempFile(const UObject* Object, const FString& Label, FJsonStringifyOptions Options, FString& OutFilename);` — `UFUNCTION(BlueprintCallable, Category = "Experimental|Json")` — ! EXPERIMENTAL ! Writes all objects in the provided object's package to a temporary file using the JsonObjectGraph format. @param	Object			The object whose package will be written to the file @param	Label			A label to disambiguate the temporary file @param	Options			Options controlling the written format @param	OutFilename		The filename written, empty if no file written
- L63 _public prototype_ `static void WriteBlueprintClassToTempFile(const UBlueprint* BP, const FString& Label, FJsonStringifyOptions Options, FString& OutFilename);` — `UFUNCTION(BlueprintCallable, Category = "Experimental|Json")` — ! EXPERIMENTAL ! Writes only the provided blueprint's Class and CDO to a temporary file using the JsonObjectGraph format. Always excludes editor only data. @param	BP				The blueprint to write to a file @param	Label			A label to disambiguate the temporary file @param	OutFilename		The filename written, empty if no file written

### `Source/Editor/Kismet/Private/Commandlets/BatchProcessCommandlet.h` (Private)


#### class `UBatchProcessCommandlet`  
`class UBatchProcessCommandlet : public UCommandlet`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- L15 _private prototype_ `UBatchProcessCommandlet(const FObjectInitializer& ObjectInitializer);`
- L18 _private prototype_ `virtual int32 Main(const FString& Params) override;`

### `Source/Editor/Kismet/Private/Commandlets/BatchWorkerCommandlet.h` (Private)


#### class `UBatchWorkerCommandlet`  
`class UBatchWorkerCommandlet : public UCommandlet`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- L15 _private prototype_ `UBatchWorkerCommandlet(const FObjectInitializer& ObjectInitializer);`
- L18 _private prototype_ `virtual int32 Main(const FString& Params) override;`

### `Source/Editor/Kismet/Private/Debugging/SKismetDebuggingView.h` (Private)


#### class `SKismetDebuggingView`  
`class SKismetDebuggingView : public SCompoundWidget`  
_L28-89_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS( SKismetDebuggingView ) : _BlueprintToWatch()`
- L38 _public prototype_ `void Construct( const FArguments& InArgs );`
- L41 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L45 _public member_ `static TWeakObjectPtr<const UObject> CurrentActiveObject;` — set to an object that's paused at a breakpoint and null otherwise
- L47 _public prototype_ `FText GetTabLabel() const;`
- L50 _public prototype_ `static void TryRegisterDebugToolbar();` — Registers the Kismet.DebuggingViewToolBar if it hasn't already been registered
- L52 _public prototype_ `void SetBlueprintToWatch(TWeakObjectPtr<UBlueprint> InBlueprintToWatch);`
- L54 _protected prototype_ `FText GetTopText() const;`
- L55 _protected prototype_ `bool CanToggleAllBreakpoints() const;`
- L56 _protected prototype_ `FText GetToggleAllBreakpointsText() const;`
- L57 _protected prototype_ `FReply OnToggleAllBreakpointsClicked();`
- L59 _protected prototype_ `void OnBlueprintClassPicked(UClass* PickedClass);`
- L60 _protected prototype_ `TSharedRef<SWidget> ConstructBlueprintClassPicker();`
- L62 _protected prototype_ `static TSharedRef<SHorizontalBox> GetDebugLineTypeToggle(FDebugLineItem::EDebugLineType Type, const FText& Text);`
- L65 _protected prototype_ `void OnSearchTextChanged(const FText& Text);` — called when SearchBox query is changed by user
- L67 _protected member_ `TSharedPtr<SKismetDebugTreeView> DebugTreeView;`
- L68 _protected member_ `TMap<UObject*, FDebugTreeItemPtr> ObjectToTreeItemMap;`
- L71 _protected member_ `TSharedPtr< SKismetDebugTreeView > OtherTreeView;` — includes items such as breakpoints and Exectution trace
- L74 _protected member_ `FDebugTreeItemPtr TraceStackItem;` — UI tree entries for stack trace and breakpoints
- L75 _protected member_ `FDebugTreeItemPtr BreakpointParentItem;`
- L78 _protected member_ `TSharedPtr<SComboButton> DebugClassComboButton;` — Combo button for selecting which blueprint is being watched
- L79 _protected member_ `TWeakObjectPtr<UBlueprint> BlueprintToWatchPtr;`
- L82 _protected member_ `TSharedPtr<SSearchBox> SearchBox;` — Search Box for tree
- L86 _protected member_ `static constexpr uint8 TreeUpdatesPerSecond = 2;` — updating the tree every tick is slow. use this to update less frequently
- L87 _protected member_ `static constexpr float UpdateInterval = 1.f / TreeUpdatesPerSecond;`
- L88 _protected member_ `float TreeUpdateTimer = UpdateInterval;`

### `Source/Editor/Kismet/Private/FiBSearchInstance.h` (Private)


#### class `FFindInBlueprintExpressionEvaluator`  
`class FFindInBlueprintExpressionEvaluator : public FTextFilterExpressionEvaluator`  
_L22-60_
- inherits: `FTextFilterExpressionEvaluator`
- desc: Evaluates the expression the user submitted to be searched for
- L26 _public function_ `FFindInBlueprintExpressionEvaluator(const ETextFilterExpressionEvaluatorMode InMode, FFiBSearchInstance* InSearchInstance) : FTextFilterExpressionEvaluator(InMode) , SearchInstance(InSearchInstance)` — Construction and assignment
- L34 _public function_ `void SetDefaultFunctionHandler(FTokenDefaultFunctionHandler InFunctionHandler)` — Sets the default function handler, which supports generic functions which are categories or other object based on FImaginaryFiBData
- L41 _protected prototype_ `virtual void ConstructExpressionParser() override final;` — FTextFilterExpressionEvaluator Interface
- L42 _protected prototype_ `virtual bool EvaluateCompiledExpression(const ExpressionParser::CompileResultType& InCompiledResult, const ITextFilterExpressionContext& InContext, FText* OutErrorText) const override;`
- L46 _protected prototype_ `void MapBasicJumps();` — Helper function to make a mapping of all basic jump operations
- L49 _protected prototype_ `void MapOrBinaryJumps();` — Helper function to make a mapping of all "Or" binary jump operations
- L52 _protected prototype_ `void MapAndBinaryJumps();` — Helper function to make a mapping of all "And" binary jump operations
- L56 _protected member_ `FFiBSearchInstance* SearchInstance;` — Referenced SearchInstance that is powering this search
- L59 _protected member_ `FTokenDefaultFunctionHandler DefaultFunctionHandler;` — Fallback for all functions, Find-in-Blueprints filters into any sub-data using functions

#### class `FFiBSearchInstance`  
`class FFiBSearchInstance`  
_L63-151_
- desc: Used to manage searches through imaginary Blueprints
- L73 _public prototype_ `FSearchResult StartSearchQuery(const FString& InSearchString, FImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Starts a search query given a string and an imaginary Blueprint @param InSearchString				The string to search using @param InImaginaryBlueprintRoot		The imaginary Blueprint to search through @return								Search result shared pointer, can be used for display in the search results window
- L81 _public prototype_ `void MakeSearchQuery(const FString& InSearchString, FImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Starts a search query given a string and an imaginary Blueprint @param InSearchString				The string to search using @param InImaginaryBlueprintRoot		The imaginary Blueprint to search through
- L90 _public prototype_ `bool DoSearchQuery(const FString& InSearchString, bool bInComplete = true);` — Runs a search query on any pending imaginary data @param InSearchString		The string to search using @param bInComplete			TRUE if a complete search of all child items should also be done, this should be FALSE when you only want to compare the string against the immediate items and not their children @return						TRUE if the search was successful.
- L99 _public prototype_ `void BuildFunctionTargets(FImaginaryFiBDataSharedPtr InRootData, ESearchQueryFilter InSearchQueryFilter, TArray<FImaginaryFiBDataWeakPtr>& OutTargetPendingSearchables);` — Builds a list of imaginary items that can be targeted by a function @param InRootData						Item to find the child imaginary data that can have be sub-searched for the function @param InSearchQueryFilter				A filter to decide if the imaginary item is compatible with the function @param OutTargetPendingSearchables		List of pending imaginary items that will be sub-searched, this gets filled out by the function
- L108 _public prototype_ `void BuildFunctionTargetsByName(FImaginaryFiBDataSharedPtr InRootData, FString InTagName, TArray<FImaginaryFiBDataWeakPtr>& OutTargetPendingSearchables);` — Builds a list of imaginary items, using their names, that can be targeted by a function @param InRootData						Item to find the child imaginary data that can have be sub-searched for the function @param InTagName							The name of objects to find @param OutTargetPendingSearchables		List of pending imaginary items that will be sub-searched, this gets filled out by the function
- L117 _public prototype_ `bool OnFilterFunction(const FTextFilterString& A, ESearchQueryFilter InSearchQueryFilter);` — Callback when a function is called by the evaluator @param InParameterString		The parameter string to sub-search using @param InSearchQueryFilter	Effectively this is the function being called, the filter is used to determine if the current item can have the function called on it and whether it's sub items can have it called on them @return						TRUE if the function was successful at finding valid results
- L126 _public prototype_ `bool OnFilterDefaultFunction(const FTextFilterString& InFunctionName, const FTextFilterString& InFunctionParams);` — Callback when a default/generic function is called by the evaluator @param InFunctionName		The function name to call, will query for sub-objects with this name to do a sub-search on @param InFunctionParams		The parameter string to sub-search using @return						TRUE if the function was successful at finding valid results
- L129 _public prototype_ `void CreateFilteredResultsListFromTree(ESearchQueryFilter InSearchQueryFilter, TArray<FImaginaryFiBDataSharedPtr>& InOutValidSearchResults);` — Builds a list of search results in their imaginary data form, filtered by an object type
- L132 _public prototype_ `FSearchResult GetSearchResults(FImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Helper function to return search results given an imaginary Blueprint root
- L135 _public member_ `FImaginaryFiBDataWeakPtr CurrentSearchable;` — Current item being searched in the Imaginary Blueprint. Must be declared as thread-safe because this is a shared object.
- L138 _public member_ `TArray< const FImaginaryFiBData* > MatchesSearchQuery;` — A going list of all imaginary items that match the search query
- L141 _public member_ `TMultiMap< const FImaginaryFiBData*, FComponentUniqueDisplay > MatchingSearchComponents;` — A mapping of items and their components that match the search query
- L144 _public member_ `TArray<FImaginaryFiBDataWeakPtr> PendingSearchables;` — A list of imaginary items that still need to be searched. Must be declared as thread-safe because it points to a shared object.
- L147 _public member_ `TArray< const FImaginaryFiBData* > LastFunctionResultMatchesSearchQuery;` — When a function returns on an item, this is the list of items that matched the sub-search query
- L150 _public member_ `TMultiMap< const FImaginaryFiBData*, FComponentUniqueDisplay > LastFunctionMatchingSearchComponents;` — When a function returns on an item, this is the mapping of imaginary items to components that matched the sub-search query

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTokenDefaultFunctionHandler, const FTextFilterString&, const FTextFilterString&);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTokenDefaultFunctionHandler, const FTextFilterString&, const FTextFilterString&);`

### `Source/Editor/Kismet/Private/FieldNotifyToggle.h` (Private)


#### class `SPaletteItemFunctionFieldNotifyToggle`  
`class SPaletteItemFunctionFieldNotifyToggle : public SCompoundWidget`  
_L21-71_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SPaletteItemFunctionFieldNotifyToggle)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FEdGraphSchemaAction> ActionPtrIn, TWeakPtr<FBlueprintEditor> InBlueprintEditor, UBlueprint* InBlueprint);`
- L37 _private prototype_ `bool GetFieldNotifyToggleEnabled() const;`
- L38 _private prototype_ `ECheckBoxState GetFieldNotifyToggleState() const;`
- L39 _private prototype_ `void OnFieldNotifyToggleFlipped(ECheckBoxState InNewState);`
- L40 _private prototype_ `const FSlateBrush* GetFieldNotifyIcon() const;`
- L41 _private prototype_ `FText GetFieldNotifyToggleToolTip() const;`
- L43 _private prototype_ `FKismetUserDeclaredFunctionMetadata* GetMetadataBlock() const;`
- L44 _private prototype_ `bool IsConstFunction() const;`
- L45 _private prototype_ `bool IsPureFunction() const;`
- L49 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The action that the owning palette entry represents
- L52 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns this, optional because of diff and merge views:
- L55 _private member_ `TWeakObjectPtr<UBlueprint> BlueprintObjPtr;` — Pointer back to the blueprint that is being displayed:
- L58 _private member_ `TWeakObjectPtr<UK2Node_FunctionEntry> FunctionEntryNodePtr;` — Pointer to the entry node of function
- L61 _private member_ `TWeakObjectPtr<UK2Node_FunctionResult> FunctionResultNodePtr;` — Pointer to a result node of function
- L64 _private member_ `TWeakObjectPtr<UFunction> FunctionPtr;` — Pointer to the function item
- L67 _private member_ `const FSlateBrush* FieldNotifyOnIcon;` — Pointer to the icon representing the active field notify state.
- L70 _private member_ `const FSlateBrush* FieldNotifyOffIcon;` — Pointer to the icon representing the inactive field notify state.

#### class `SPaletteItemVarFieldNotifyToggle`  
`class SPaletteItemVarFieldNotifyToggle : public SCompoundWidget`  
_L78-115_
- inherits: `SCompoundWidget`
- L81 _public function_ `SLATE_BEGIN_ARGS(SPaletteItemVarFieldNotifyToggle)`
- L82 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FEdGraphSchemaAction> ActionPtrIn, TWeakPtr<FBlueprintEditor> InBlueprintEditor, UBlueprint* InBlueprint);`
- L95 _private prototype_ `ECheckBoxState GetFieldNotifyToggleState() const;`
- L96 _private prototype_ `void OnFieldNotifyToggleFlipped(ECheckBoxState InNewState);`
- L97 _private prototype_ `const FSlateBrush* GetFieldNotifyIcon() const;`
- L98 _private prototype_ `FText GetFieldNotifyToggleToolTip() const;`
- L102 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The action that the owning palette entry represents
- L105 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns this, optional because of diff and merge views:
- L108 _private member_ `TWeakObjectPtr<UBlueprint> BlueprintObjPtr;` — Pointer back to the blueprint that is being displayed:
- L111 _private member_ `const FSlateBrush* FieldNotifyOnIcon;` — Pointer to the icon representing the active field notify state.
- L114 _private member_ `const FSlateBrush* FieldNotifyOffIcon;` — Pointer to the icon representing the inactive field notify state.

### `Source/Editor/Kismet/Private/FormatTextDetails.h` (Private)


#### class `FFormatTextDetails`  
`class FFormatTextDetails : public IDetailCustomization`  
_L25-59_
- inherits: `IDetailCustomization`
- desc: Details customization for the "Format Text" node
- L29 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public function_ `FFormatTextDetails() : TargetNode(NULL)`
- L39 _public prototype_ `~FFormatTextDetails();`
- L42 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L45 _public prototype_ `void OnForceRefresh();` — Forces a refresh on the details customization
- L49 _private prototype_ `FReply OnAddNewArgument();` — Handles new argument request
- L52 _private prototype_ `void OnEditorPackageModified(UPackage* Package);` — Callback whenever a package is marked dirty, will refresh the node being represented by this details customization
- L54 _private prototype_ `bool CanEditArguments() const;`
- L56 _private member_ `TSharedPtr<class FFormatTextLayout> Layout;`
- L58 _private member_ `UK2Node_FormatText* TargetNode;` — The target node that this argument is on

#### class `FFormatTextLayout`  
`class FFormatTextLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FFormatTextLayout>`  
_L62-93_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FFormatTextLayout>`
- desc: Custom struct for each group of arguments in the function editing details
- L65 _public function_ `FFormatTextLayout(UK2Node_FormatText* InTargetNode) : TargetNode(InTargetNode)`
- L69 _public function_ `void Refresh()`
- L74 _public prototype_ `bool CausedChange() const;`
- L78 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L79 _private function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override`
- L80 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L81 _private function_ `virtual void Tick( float DeltaTime ) override`
- L82 _private function_ `virtual bool RequiresTick() const override`
- L83 _private function_ `virtual FName GetName() const override`
- L84 _private function_ `virtual bool InitiallyCollapsed() const override`
- L87 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L90 _private member_ `UK2Node_FormatText* TargetNode;` — The target node that this argument is on
- L92 _private member_ `TArray<TWeakPtr<class FFormatTextArgumentLayout>> Children;`

#### class `FFormatTextArgumentLayout`  
`class FFormatTextArgumentLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FFormatTextArgumentLayout>`  
_L96-157_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FFormatTextArgumentLayout>`
- desc: Custom struct for each group of arguments in the function editing details
- L99 _public function_ `FFormatTextArgumentLayout(UK2Node_FormatText* InTargetNode, int32 InArgumentIndex) : TargetNode(InTargetNode) , ArgumentIndex(InArgumentIndex) , bCausedChange(false)`
- L105 _public function_ `bool CausedChange() const`
- L109 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L110 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L111 _private function_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override`
- L112 _private function_ `virtual void Tick( float DeltaTime ) override`
- L113 _private function_ `virtual bool RequiresTick() const override`
- L114 _private function_ `virtual FName GetName() const override`
- L115 _private function_ `virtual bool InitiallyCollapsed() const override`
- L119 _private prototype_ `FText GetArgumentName() const;` — Retrieves the argument's name
- L122 _private prototype_ `FReply OnMoveArgumentUp();` — Moves the argument up in the list
- L125 _private prototype_ `FReply OnMoveArgumentDown();` — Moves the argument down in the list
- L128 _private prototype_ `void OnArgumentRemove();` — Deletes the argument
- L131 _private prototype_ `void OnArgumentNameCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Callback when the argument's name is committed
- L134 _private prototype_ `void OnArgumentNameChanged(const FText& NewText);` — Callback when changing the argument's name to verify the name
- L143 _private prototype_ `bool IsValidArgumentName(const FText& InNewText) const;` — Helper function to validate the argument's name @param InNewText		The name to validate @return				Returns true if the name is valid
- L145 _private prototype_ `bool CanEditArguments() const;`
- L148 _private member_ `UK2Node_FormatText* TargetNode;` — The target node that this argument is on
- L151 _private member_ `int32 ArgumentIndex;` — Index of argument
- L154 _private member_ `TWeakPtr< SEditableTextBox > ArgumentNameWidget;` — The argument's name widget, used for setting a argument's name
- L156 _private member_ `bool bCausedChange;`

### `Source/Editor/Kismet/Private/InstancedStaticMeshSCSEditorCustomization.h` (Private)


#### class `FInstancedStaticMeshSCSEditorCustomization`  
`class FInstancedStaticMeshSCSEditorCustomization : public ISCSEditorCustomization`  
_L16-35_
- inherits: `ISCSEditorCustomization`
- L19 _public prototype_ `static TSharedRef<ISCSEditorCustomization> MakeInstance(TSharedRef< class IBlueprintEditor > InBlueprintEditor);`
- L23 _public prototype_ `virtual bool HandleViewportClick(const TSharedRef<FEditorViewportClient>& InViewportClient, class FSceneView& InView, class HHitProxy* InHitProxy, FKey InKey, EInputEvent InEvent, uint32 InHitX, uint32 InHitY) override;` — ISCSEditorCustomization interface
- L24 _public prototype_ `virtual bool HandleViewportDrag(const USceneComponent* InComponentScene, class USceneComponent* InComponentTemplate, const FVector& InDeltaTranslation, const FRotator& InDeltaRotation, const FVector& InDeltaScale, const FVector& InPivot) override;`
- L25 _public prototype_ `virtual bool HandleGetWidgetLocation(const USceneComponent* InSceneComponent, FVector& OutWidgetLocation) override;`
- L26 _public prototype_ `virtual bool HandleGetWidgetTransform(const USceneComponent* InSceneComponent, FMatrix& OutWidgetTransform) override;`
- L30 _protected prototype_ `void ValidateSelectedInstances(class UInstancedStaticMeshComponent* InComponent);` — Ensure that selection bits are in sync w/ the number of instances
- L34 _private member_ `TWeakPtr<class IBlueprintEditor> BlueprintEditorPtr;` — The blueprint editor we are bound to

### `Source/Editor/Kismet/Private/SBlueprintActionMenu.h` (Private)


#### class `SBlueprintActionMenu`  
`class SBlueprintActionMenu : public SBorder`  
_L41-113_
- inherits: `SBorder`
- L45 _public prototype_ `DECLARE_DELEGATE_ThreeParams( FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SBlueprintActionMenu closes
- L47 _public function_ `SLATE_BEGIN_ARGS( SBlueprintActionMenu ) : _GraphObj( static_cast<UEdGraph*>(NULL) ) , _NewNodePosition( FVector2D::ZeroVector ) , _AutoExpandActionMenu( false )`
- L53 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_EVENT( FClosedReason, OnCloseReason ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<FBlueprintEditor> InEditor );`
- L63 _public prototype_ `~SBlueprintActionMenu();`
- L65 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L68 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L73 _protected prototype_ `EVisibility GetTypeImageVisibility() const;` — UI Callback functions
- L74 _protected prototype_ `FText GetSearchContextDesc() const;`
- L75 _protected prototype_ `void OnContextToggleChanged(ECheckBoxState CheckState);`
- L76 _protected prototype_ `ECheckBoxState ContextToggleIsChecked() const;`
- L77 _protected prototype_ `void OnContextTargetsChanged(uint32 ContextTargetMask);`
- L79 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType );`
- L81 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L84 _protected prototype_ `TSharedRef<FGraphActionListBuilderBase> OnGetActionList();` — Callback used to populate all actions list in SGraphActionMenu
- L87 _protected prototype_ `void ConstructActionContext(FBlueprintActionContext& ContextDescOut);`
- L90 _protected prototype_ `void TryInsertPromoteToVariable(FBlueprintActionContext const& Context, FGraphActionListBuilderBase& OutAllActions);` — Function to try to insert a promote to variable entry if it is possible to do so.
- L93 _protected prototype_ `void OnNamespaceSelectedForImport(const FString& InNamespace);` — Invoked when an available namespace is selected for import.
- L96 _protected prototype_ `void OnGetNamespacesToExcludeFromImportMenu(TSet<FString>& OutNamespacesToExclude);` — Gathers the list of namespaces to exclude from the import menu.
- L99 _private member_ `UEdGraph* GraphObj;`
- L100 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L101 _private member_ `FDeprecateSlateVector2D NewNodePosition;`
- L102 _private member_ `bool bAutoExpandActionMenu;`
- L104 _private member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L105 _private member_ `FClosedReason OnCloseReasonCallback;`
- L107 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L108 _private member_ `TWeakPtr<FBlueprintEditor> EditorPtr;`
- L109 _private member_ `TSharedPtr<SBlueprintContextTargetMenu> ContextTargetSubMenu;`
- L110 _private member_ `TSharedPtr<FBlueprintActionMenuBuilder> ContextMenuBuilder;`
- L112 _private member_ `bool bActionExecuted;`

#### class `SBlueprintActionMenuExpander`  
`class SBlueprintActionMenuExpander : public SExpanderArrow`  
_L119-148_
- inherits: `SExpanderArrow`
- L121 _private function_ `SLATE_BEGIN_ARGS( SBlueprintActionMenuExpander )`
- L134 _public prototype_ `void Construct(const FArguments& InArgs, const FCustomExpanderData& ActionMenuData);` — Constructs a standard SExpanderArrow widget if the associated menu item is a category or separator, otherwise, for action items, it constructs a favoriting toggle (plus indent) in front of the action entry. @param  InArgs			A set of slate arguments for this widget type (defined above). @param  ActionMenuData	A set of useful data for detailing the specific action menu row this is for.
- L144 _private prototype_ `FMargin GetCustomIndentPadding() const;` — Action menu expanders are also responsible for properly indenting the menu entries, so this returns the proper margin padding for the menu row (based off its indent level). @return Padding to construct around this widget (so the menu entry is properly indented).
- L147 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The action associated with the menu row this belongs to

#### Free symbols / members of external scopes

- L45 _delegate_ `DECLARE_DELEGATE_ThreeParams( FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SBlueprintActionMenu closes

### `Source/Editor/Kismet/Private/SBlueprintBookmarks.h` (Private)


#### class `SBlueprintBookmarks`  
`class SBlueprintBookmarks : public SCompoundWidget`  
_L35-148_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS(SBlueprintBookmarks)`
- L40 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FBlueprintEditor>, EditorContext) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `void RefreshBookmarksTree();`
- L93 _protected typedef_ `typedef TSharedPtr<FTreeViewItem> FTreeViewItemPtr;`
- L114 _protected prototype_ `void OnFilterTextCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L116 _protected prototype_ `void OnDeleteSelectedTreeViewItems();`
- L117 _protected prototype_ `bool CanDeleteSelectedTreeViewItems() const;`
- L118 _protected prototype_ `void OnRenameSelectedTreeViewItems();`
- L119 _protected prototype_ `bool CanRenameSelectedTreeViewItem() const;`
- L121 _protected prototype_ `bool CanNavigateToSelection() const;`
- L122 _protected prototype_ `TSharedRef<ITableRow> OnGenerateTreeViewRow(FTreeViewItemPtr TreeItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L123 _protected prototype_ `void OnGetTreeViewChildren(FTreeViewItemPtr TreeItem, TArray<FTreeViewItemPtr>& OutChildren);`
- L124 _protected prototype_ `void OnTreeViewItemDoubleClick(FTreeViewItemPtr TreeItem);`
- L125 _protected prototype_ `TSharedPtr<SWidget> OnOpenTreeViewContextMenu();`
- L127 _protected prototype_ `bool IsShowCommentNodesChecked() const;`
- L128 _protected prototype_ `void OnToggleShowCommentNodes();`
- L130 _protected prototype_ `bool IsShowBookmarksForCurrentDocumentOnlyChecked() const;`
- L131 _protected prototype_ `void OnToggleShowBookmarksForCurrentDocumentOnly();`
- L134 _private member_ `TWeakPtr<FBlueprintEditor> EditorContext;`
- L136 _private member_ `FBPEditorBookmarkNode CommentsRootNode;`
- L137 _private member_ `FBPEditorBookmarkNode BookmarksRootNode;`
- L138 _private member_ `TArray<FBPEditorBookmarkNode> CommentNodes;`
- L139 _private member_ `TMap<FGuid, FEditedDocumentInfo> CommentNodeInfo;`
- L141 _private member_ `TArray<FTreeViewItemPtr> TreeViewRootItems;`
- L143 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L144 _private member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L145 _private member_ `TSharedPtr<STreeView<FTreeViewItemPtr> > TreeViewWidget;`
- L147 _private member_ `FText FilterText;`

#### enum `SBlueprintBookmarks::ETreeViewNodeType`  
`enum class ETreeViewNodeType`  
_L47-54_
- L49 _public enumerator_ `Root`
- L50 _public enumerator_ `Folder`
- L51 _public enumerator_ `Comment`
- L52 _public enumerator_ `LocalBookmark`
- L53 _public enumerator_ `SharedBookmark`

#### struct `SBlueprintBookmarks::FTreeViewItem`  
`struct FTreeViewItem : public TSharedFromThis<FTreeViewItem>`  
_L56-91_
- inherits: `TSharedFromThis<FTreeViewItem>`
- L58 _public prototype_ `DECLARE_DELEGATE(FOnRequestRename);`
- L60 _public member_ `ETreeViewNodeType NodeType;`
- L61 _public member_ `FBPEditorBookmarkNode& BookmarkNode;`
- L62 _public member_ `const FEditedDocumentInfo* DocumentInfo;`
- L63 _public member_ `TArray<TSharedPtr<FTreeViewItem>> Children;`
- L64 _public member_ `FOnRequestRename OnRequestRenameDelegate;`
- L66 _public function_ `FTreeViewItem(ETreeViewNodeType InNodeType, FBPEditorBookmarkNode& InBookmarkNode, const FEditedDocumentInfo* InDocumentInfo = nullptr) :NodeType(InNodeType) ,BookmarkNode(InBookmarkNode) ,DocumentInfo(InDocumentInfo)`
- L72 _public function_ `FORCEINLINE bool IsRootNode() const`
- L77 _public function_ `FORCEINLINE bool IsBookmarkNode() const`
- L82 _public function_ `FORCEINLINE bool IsCommentNode() const`
- L87 _public function_ `FORCEINLINE bool IsFolderNode() const`

#### class `SBlueprintBookmarks::STreeItemRow`  
`class STreeItemRow : public SMultiColumnTableRow<FTreeViewItemPtr>`  
_L95-112_
- inherits: `SMultiColumnTableRow<FTreeViewItemPtr>`
- L98 _public function_ `SLATE_BEGIN_ARGS(STreeItemRow)`
- L99 _public prototype_ `SLATE_ARGUMENT(FTreeViewItemPtr, ItemPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TWeakPtr<FBlueprintEditor> InEditorContext);`
- L103 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L106 _protected prototype_ `FText GetItemNameText() const;`
- L107 _protected prototype_ `void OnNameTextCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L110 _private member_ `FTreeViewItemPtr ItemPtr;`
- L111 _private member_ `TWeakPtr<FBlueprintEditor> EditorContext;`

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DELEGATE(FOnRequestRename);`

### `Source/Editor/Kismet/Private/SBlueprintContextTargetMenu.h` (Private)


#### struct `FContextMenuTargetProfile`  
`struct FContextMenuTargetProfile`  
_L21-41_
- desc: Used internally by SBlueprintContextTargetMenu, to track and save the user's context target settings
- L24 _public prototype_ `FContextMenuTargetProfile();`
- L25 _public prototype_ `FContextMenuTargetProfile(const FBlueprintActionContext& MenuContext);`
- L27 _public prototype_ `uint32 GetContextTargetMask() const;`
- L28 _public prototype_ `void SetContextTarget(EContextTargetFlags::Type Flag, bool bClear = false);`
- L29 _public prototype_ `uint32 GetIncompatibleTargetsMask() const;`
- L31 _public prototype_ `bool IsTargetEnabled(EContextTargetFlags::Type Flag) const;`
- L34 _private prototype_ `void SaveProfile() const;`
- L35 _private prototype_ `bool LoadProfile();`
- L37 _private member_ `FString ProfileSaveName;`
- L38 _private member_ `uint32 HasComponentsMask;`
- L39 _private member_ `uint32 IncompatibleTargetFlags;`
- L40 _private member_ `uint32 SavedTargetFlags;`

#### class `SBlueprintContextTargetMenu`  
`class SBlueprintContextTargetMenu : public SBorder`  
_L48-91_
- inherits: `SBorder`
- L50 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnTargetMaskChanged, uint32);`
- L53 _public function_ `SLATE_BEGIN_ARGS(SBlueprintContextTargetMenu)`
- L54 _public prototype_ `SLATE_EVENT(FOnTargetMaskChanged, OnTargetMaskChanged) SLATE_NAMED_SLOT(FArguments, CustomTargetContent) SLATE_END_ARGS()`
- L66 _public prototype_ `uint32 GetContextTargetMask() const;` — Returns a EContextTargetFlags::Type bitmask, defining which targets the user currently has enabled.
- L76 _private prototype_ `void OnTargetCheckStateChanged(const ECheckBoxState NewCheckedState, EContextTargetFlags::Type ContextTarget);` — Internal UI callback that handles when one of the context targets is checked/unchecked. @param  NewCheckedState	The checkbox's new state. @param  ContextTarget    A flag identifying which checkbox was altered.
- L85 _private prototype_ `ECheckBoxState GetTargetCheckedState(EContextTargetFlags::Type ContextTarget) const;` — Internal UI callback that determines the checkbox state for one of the context target options. @param  ContextTarget    A flag identifying which checkbox we want the state of. @return ECheckBoxState::Checked if the user has the flag set, otherwise ECheckBoxState::UnChecked
- L88 _private member_ `FContextMenuTargetProfile TargetProfile;` — Determines what flags are incompatible with the current context, and saves/loads the user's choice settings
- L90 _private member_ `FOnTargetMaskChanged OnTargetMaskChanged;` — Delegate for external users to hook into (so they can act when the menu's settings are changed).

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTargetMaskChanged, uint32);`

### `Source/Editor/Kismet/Private/SBlueprintFavoritesPalette.h` (Private)


#### class `SBlueprintFavoritesPalette`  
`class SBlueprintFavoritesPalette : public SBlueprintSubPalette`  
_L18-49_
- inherits: `SBlueprintSubPalette`
- L21 _public function_ `SLATE_BEGIN_ARGS(SBlueprintFavoritesPalette)`
- L25 _public prototype_ `virtual ~SBlueprintFavoritesPalette();` — Unsubscribes this from events before it is destroyed
- L35 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);` — Creates a sub-palette widget for the blueprint palette UI (this contains a subset of the library palette, specifically the user's favorites and most used nodes) @param  InArgs				A set of slate arguments, defined above. @param  InBlueprintEditor	A pointer to the blueprint editor that this palette belongs to.
- L39 _private prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;` — SGraphPalette Interface
- L43 _private prototype_ `virtual void BindCommands(TSharedPtr<FUICommandList> CommandListIn) const override;` — SBlueprintSubPalette Interface
- L44 _private prototype_ `virtual void GenerateContextMenuEntries(FMenuBuilder& MenuBuilder) const override;`
- L48 _private member_ `bool bShowFrequentlyUsed;` — Flags weather we should add the "frequently used" list to the user's favorites

### `Source/Editor/Kismet/Private/SBlueprintLibraryPalette.h` (Private)


#### class `SBlueprintLibraryPalette`  
`class SBlueprintLibraryPalette : public SBlueprintSubPalette`  
_L28-97_
- inherits: `SBlueprintSubPalette`
- L31 _public function_ `SLATE_BEGIN_ARGS( SBlueprintLibraryPalette ) : _UseLegacyLayout(false)`
- L34 _public prototype_ `SLATE_ATTRIBUTE(bool, UseLegacyLayout) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);`
- L49 _private prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;` — SGraphPalette Interface
- L53 _private prototype_ `virtual TSharedRef<SVerticalBox> ConstructHeadingWidget(FSlateBrush const* const Icon, FText const& TitleText, FText const& ToolTip) override;` — SBlueprintSubPalette Interface
- L54 _private prototype_ `virtual void BindCommands(TSharedPtr<FUICommandList> CommandListIn) const override;`
- L55 _private prototype_ `virtual void GenerateContextMenuEntries(FMenuBuilder& MenuBuilder) const override;`
- L64 _private prototype_ `TSharedRef<SWidget> ConstructClassFilterDropdownContent();` — Constructs a slate widget for the class drop-down menu, which is used to select a filter class. @return A pointer to the newly created menu widget.
- L72 _private prototype_ `FText GetFilterClassName() const;` — Retrieves the name of the currently selected class filter (or "All" if no class filter has been selected). @return A string representing the selected class filter.
- L80 _private prototype_ `FReply ClearClassFilter();` — Clears the current class filter (if one is set), and refreshes the displayed action list. @return FReply::Handled()
- L87 _private prototype_ `void OnClassPicked(UClass* PickedClass);` — Resets the current class filter and refreshes the displayed action list. @param  PickedClass	The new class to filter the library by.
- L90 _private member_ `bool bUseLegacyLayout;` — Used to help ease the transition for users who like the old format
- L93 _private member_ `TWeakObjectPtr<UClass> FilterClass;` — Class we want to see content of
- L96 _private member_ `TSharedPtr<SComboButton> FilterComboButton;` — Combo button used to choose class to filter

### `Source/Editor/Kismet/Private/SBlueprintPalette.h` (Private)


#### class `SBlueprintPaletteItem`  
`class SBlueprintPaletteItem : public SGraphPaletteItem`  
_L29-84_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a single item
- L32 _public function_ `SLATE_BEGIN_ARGS( SBlueprintPaletteItem ) : _ShowClassInTooltip(false)`
- L36 _public prototype_ `SLATE_ARGUMENT(bool, ShowClassInTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, TWeakPtr<FBlueprintEditor> InBlueprintEditor);`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, UBlueprint* InBlueprint);`
- L50 _private prototype_ `void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, UBlueprint* InBlueprint, TWeakPtr<FBlueprintEditor> InBlueprintEditor);`
- L53 _private prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget Interface
- L57 _private prototype_ `virtual TSharedRef<SWidget> CreateTextSlotWidget(FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly ) override;` — SGraphPaletteItem Interface
- L58 _private prototype_ `virtual FText GetDisplayText() const override;`
- L59 _private prototype_ `virtual bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage) override;`
- L60 _private prototype_ `virtual void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit) override;`
- L69 _private prototype_ `TSharedPtr<SToolTip> ConstructToolTipWidget() const;` — Creates a tooltip widget based off the specified action (attempts to mirror the tool-tip that would be found on the node once it's placed). @return A new slate widget to be used as the tool tip for this item's text element.
- L72 _private prototype_ `FText GetToolTipText() const;` — Returns the up-to-date tooltip for the item
- L75 _private member_ `bool bShowClassInTooltip;` — True if the class should be displayed in the tooltip
- L77 _private member_ `UBlueprint* Blueprint;`
- L80 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns this
- L83 _private member_ `FNodeTextCache MenuDescriptionCache;` — Cache for the MenuDescription to be displayed for this item

#### class `SBlueprintPalette`  
`class SBlueprintPalette : public SCompoundWidget`  
_L91-116_
- inherits: `SCompoundWidget`
- L94 _public function_ `SLATE_BEGIN_ARGS( SBlueprintPalette )`
- L95 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);`
- L111 _private prototype_ `void OnSplitterResized() const;` — Saves off the user's new sub-palette configuration (so as to not annoy them by reseting it every time they open the blueprint editor).
- L113 _private member_ `TSharedPtr<SWidget> FavoritesWrapper;`
- L114 _private member_ `TSharedPtr<SSplitter> PaletteSplitter;`
- L115 _private member_ `TSharedPtr<SWidget> LibraryWrapper;`

### `Source/Editor/Kismet/Private/SBlueprintSubPalette.h` (Private)


#### class `SBlueprintSubPalette`  
`class SBlueprintSubPalette : public SGraphPalette`  
_L32-138_
- inherits: `SGraphPalette`
- L35 _public function_ `SLATE_BEGIN_ARGS( SBlueprintSubPalette ) : _Title() , _Icon(FCoreStyle::Get().GetDefaultBrush()) , _ShowFavoriteToggles(false)`
- L41 _public prototype_ `SLATE_ATTRIBUTE(FText, Title) SLATE_ATTRIBUTE(FSlateBrush const*, Icon) SLATE_ATTRIBUTE(bool, ShowFavoriteToggles) SLATE_END_ARGS() virtual ~SBlueprintSubPalette();`
- L56 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);` — Creates a sub-palette widget for the blueprint palette UI (this serves as a base class for more specialized sub-palettes). @param  InArgs				A set of slate arguments, defined above. @param  InBlueprintEditor	A pointer to the blueprint editor that this palette belongs to.
- L64 _public prototype_ `UBlueprint* GetBlueprint() const;` — Retrieves, from the owning blueprint-editor, the blueprint currently being worked on. @return The blueprint currently being edited by this palette's blueprint-editor.
- L71 _public prototype_ `TSharedPtr<FEdGraphSchemaAction> GetSelectedAction() const;` — Retrieves the palette menu item currently selected by the user. @return A pointer to the palette's currently selected action (NULL if a category is selected, or nothing at all)
- L75 _protected prototype_ `virtual void RefreshActionsList(bool bPreserveExpansion) override;` — SGraphPalette Interface
- L76 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;`
- L77 _protected prototype_ `virtual FReply OnActionDragged(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions, const FPointerEvent& MouseEvent) override;`
- L86 _protected prototype_ `virtual void BindCommands(TSharedPtr<FUICommandList> CommandListIn) const;` — A place to bind all context menu actions for this sub-palette. Sub-classes can override this to bind their own specialized commands. @param  CommandListIn	The command list to map your actions with.
- L97 _protected prototype_ `virtual TSharedRef<SVerticalBox> ConstructHeadingWidget(FSlateBrush const* const Icon, FText const& TitleText, FText const& ToolTip);` — Constructs the slate header for the sub-palette. Inherited classes can override this to tack on their own headers. @param  Icon			The icon, identifying this specific sub-palette. @param  TitleText	A title identifying this sub-palette. @param  ToolTip		A tooltip you want displayed when the user hovers over the heading. @return A reference to the newly created vertical slate box containing the header.
- L106 _protected prototype_ `virtual void GenerateContextMenuEntries(FMenuBuilder& MenuBuilder) const;` — An overridable method, that fills out the provided menu-builder with actions for this sub-palette's right-click context menu (sub-classes can provide their own). @param  MenuBuilder	The menu builder you want the sub-palette's actions added to.
- L109 _protected prototype_ `void RequestRefreshActionsList();` — Delegate to call to request a refresh
- L111 _protected prototype_ `void OnDatabaseActionsUpdated(UObject* ActionsKey);` — Delegate handlers for when the blueprint database is updated (so we can release references and refresh the list)
- L112 _protected prototype_ `void OnDatabaseActionsRemoved(UObject* ActionsKey);`
- L114 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L117 _protected member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns us
- L121 _private prototype_ `void ForceRefreshActionList();` — Immediately calls RefreshActionsList(), doesn't not defer until Tick() like RequestRefreshActionsList() does.
- L130 _private prototype_ `TSharedPtr<SWidget> ConstructContextMenuWidget() const;` — Constructs a slate widget for the right-click context menu in this palette. While this isn't virtual, sub-classes can override GenerateContextMenuEntries() to provide their own specialized entries. @return A pointer to the newly created menu widget.
- L134 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Pointer to the command list created for this (so multiple sub-palettes can have their own bindings)
- L137 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer to refresh the actions list is currently registered

### `Source/Editor/Kismet/Private/SCSEditorViewportClient.h` (Private)


#### class `FSCSEditorViewportClient`  
`class FSCSEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FSCSEditorViewportClient>`  
_L34-194_
- inherits: `FEditorViewportClient,TSharedFromThis<FSCSEditorViewportClient>`
- desc: An editor viewport client subclass for the SCS editor viewport.
- L44 _public prototype_ `FSCSEditorViewportClient(TWeakPtr<class FBlueprintEditor>& InBlueprintEditorPtr, FPreviewScene* InPreviewScene, const TSharedRef<SSCSEditorViewport>& InSCSEditorViewport, FEditorModeTools* InModeTools = nullptr);` — Constructor. @param InBlueprintEditorPtr A weak reference to the Blueprint Editor context. @param InPreviewScene The preview scene to use. @param InModeTools Optional pre-configured mode tools (if nullptr, a new one will be created).
- L49 _public prototype_ `virtual ~FSCSEditorViewportClient();` — Destructor.
- L52 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface
- L53 _public prototype_ `virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;`
- L54 _public prototype_ `virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;`
- L55 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L56 _public prototype_ `virtual void MouseMove(FViewport* InViewport, int32 InX, int32 InY) override;`
- L57 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* InViewport, int32 InX, int32 InY) override;`
- L58 _public prototype_ `virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L59 _public prototype_ `virtual bool InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale ) override;`
- L60 _public prototype_ `virtual void TrackingStarted( const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge ) override;`
- L61 _public prototype_ `virtual void TrackingStopped() override;`
- L62 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L63 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L64 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L65 _public prototype_ `virtual void SetWidgetMode( UE::Widget::EWidgetMode NewMode ) override;`
- L66 _public prototype_ `virtual void SetWidgetCoordSystemSpace( ECoordSystem NewCoordSystem ) override;`
- L67 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L68 _public prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L69 _public function_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override`
- L70 _public prototype_ `virtual const FEditorViewportCameraSpeedSettings& GetCameraSpeedSettings() const override;`
- L71 _public prototype_ `virtual void SetCameraSpeedSettings(const FEditorViewportCameraSpeedSettings& NewCameraSpeedSettings) override;`
- L79 _public prototype_ `void InvalidatePreview(bool bResetCamera = true);` — Recreates the preview scene and invalidates the owning viewport. @param bResetCamera Whether or not to reset the camera after recreating the preview scene.
- L84 _public prototype_ `void ResetCamera();` — Resets the camera position
- L91 _public function_ `bool GetRealtimePreview() const` — Determines whether or not realtime preview is enabled. @return true if realtime preview is enabled, false otherwise.
- L99 _public prototype_ `void ToggleRealtimePreview();` — Toggles realtime preview on/off.
- L104 _public prototype_ `void FocusViewportToSelection();` — Focuses the viewport on the selected components
- L109 _public prototype_ `bool GetIsSimulateEnabled();` — Returns true if simulate is enabled in the viewport
- L114 _public prototype_ `void ToggleIsSimulateEnabled();` — Will toggle the simulation mode of the viewport
- L119 _public prototype_ `bool GetShowFloor();` — Returns true if the floor is currently visible in the viewport
- L124 _public prototype_ `void ToggleShowFloor();` — Will toggle the floor's visibility in the viewport
- L129 _public prototype_ `bool GetShowGrid();` — Returns true if the grid is currently visible in the viewport
- L134 _public prototype_ `void ToggleShowGrid();` — Will toggle the grid's visibility in the viewport
- L139 _public prototype_ `AActor* GetPreviewActor() const;` — Gets the current preview actor instance.
- L141 _public prototype_ `bool IsViewportSelectionLimited() const;`
- L144 _public prototype_ `bool IsObjectSelectableInViewport(UObject* const InObject) const;` — @return True if the specified object is selectable in the viewport and not made unselectable by the Sequencer selection limiting.
- L150 _protected prototype_ `void BeginTransaction(const FText& Description);` — Initiates a transaction.
- L155 _protected prototype_ `void EndTransaction();` — Ends the current transaction, if one exists.
- L160 _protected prototype_ `void RefreshPreviewBounds();` — Updates preview bounds and floor positioning
- L162 _protected prototype_ `void UpdateHoverFromHitProxy(HHitProxy* const InHitProxy);`
- L166 _private member_ `UE::Widget::EWidgetMode WidgetMode;`
- L167 _private member_ `ECoordSystem WidgetCoordSystem;`
- L170 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;` — Weak reference to the editor hosting the viewport
- L173 _private member_ `FBoxSphereBounds PreviewActorBounds;` — The full bounds of the preview scene (encompasses all visible components)
- L176 _private member_ `bool bIsManipulating;` — If true then we are manipulating a specific property or component
- L179 _private member_ `FScopedTransaction* ScopedTransaction;` — The current transaction for undo/redo
- L182 _private member_ `UStaticMeshComponent* EditorFloorComp;` — Floor static mesh component
- L185 _private member_ `bool bIsSimulateEnabled;` — If true, the physics simulation gets ticked
- L187 _private prototype_ `bool HandleBeginTransform();`
- L188 _private prototype_ `bool HandleEndTransform();`
- L191 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, TOptional<FColor>> HoveredPrimitiveComponents;` — Hovered primitives and their last overlay color before we apply the hover overlay
- L193 _private member_ `TOptional<EMouseCursor::Type> MouseCursor;`

### `Source/Editor/Kismet/Private/SFieldNotificationCheckList.h` (Private)


#### class `UE::FieldNotification::SFieldNotificationCheckList`  
`class SFieldNotificationCheckList : public SCompoundWidget`  
_L25-60_
- inherits: `SCompoundWidget`
- desc: A widget in details panel which allows the user to choose which field notify variables/functions will be notified when the selected property changes.
- L28 _public typedef_ `typedef SListView< TSharedPtr<FFieldNotificationId> > SComboListType;`
- L30 _public function_ `SLATE_BEGIN_ARGS(SFieldNotificationCheckList)`
- L32 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UBlueprint>, BlueprintPtr) SLATE_ARGUMENT(FName, FieldName) SLATE_ARGUMENT(bool, IsFieldFunction) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _private prototype_ `EVisibility GetFieldNotifyIconVisibility() const;`
- L43 _private prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FFieldNotificationId> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L44 _private prototype_ `void OnMenuOpenChanged(bool bOpen);`
- L46 _private prototype_ `bool IsCheckBoxEnabled(FName OtherName) const;`
- L47 _private prototype_ `ECheckBoxState OnVariableCheckboxState(FName OtherName) const;`
- L48 _private prototype_ `void OnVariableCheckBoxChanged(ECheckBoxState InNewState, FName OtherName);`
- L51 _private prototype_ `TArray<UK2Node_FunctionEntry*> GetFieldNotifyFunctionEntryNodesInBlueprint();` — Iterates through all graphs in the blueprint to find function graphs that are field notify and adds their entry node to OutArray.
- L55 _private member_ `TArray<TSharedPtr<FFieldNotificationId>> FieldNotificationIdsSource;` — Array of all field notify variables and functions in the owning blueprint.
- L56 _private member_ `TWeakObjectPtr<UBlueprint> BlueprintPtr;`
- L57 _private member_ `TSharedPtr< SComboListType > ComboListView;`
- L59 _private member_ `FName FieldName;` — The name of the selected field in the blueprint editor.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Source/Editor/Kismet/Private/SGraphTitleBar.h` (Private)


#### class `SGraphTitleBar`  
`class SGraphTitleBar : public SCompoundWidget`  
_L25-95_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS( SGraphTitleBar ) : _EdGraphObj(nullptr) , _Kismet2()`
- L33 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, EdGraphObj ) SLATE_ARGUMENT( TWeakPtr<FBlueprintEditor>, Kismet2 ) SLATE_EVENT( FEdGraphEvent, OnDifferentGraphCrumbClicked ) SLATE_ARGUMENT( TSharedPtr<SWidget>, HistoryNavigationWidget ) SLATE_END_ARGS() ~SGraphTitleBar();`
- L42 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `void Refresh();` — Refresh the toolbar
- L49 _protected member_ `TWeakPtr<FBlueprintEditor> Kismet2Ptr;` — Owning Kismet 2
- L52 _protected member_ `UEdGraph* EdGraphObj;` — Edited graph
- L55 _protected member_ `TWeakPtr<SFunctionEditor> FuncEditorPtr;` — Pointer to the function editor widget
- L57 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;`
- L60 _protected member_ `TSharedPtr< SBreadcrumbTrail<UEdGraph*> > BreadcrumbTrail;` — Breadcrumb trail widget
- L63 _protected member_ `FEdGraphEvent OnDifferentGraphCrumbClicked;` — Callback to call when the user wants to change the active graph via the breadcrumb trail
- L66 _protected member_ `bool bShowBlueprintTitle;` — Should we show graph's blueprint title
- L69 _protected member_ `FText BlueprintTitle;` — Blueprint title being displayed for toolbar
- L73 _protected prototype_ `const FSlateBrush* GetTypeGlyph() const;` — Get the icon to use
- L76 _protected prototype_ `FText GetTitleExtra() const;` — Get the extra title text
- L79 _protected prototype_ `EVisibility IsGraphBlueprintNameVisible() const;` — Helper methods
- L81 _protected prototype_ `void OnBreadcrumbClicked(UEdGraph* const & Item);`
- L83 _protected prototype_ `void RebuildBreadcrumbTrail();`
- L85 _protected prototype_ `static FText GetTitleForOneCrumb(const UEdGraph* Graph);`
- L88 _protected prototype_ `UEdGraph* GetOuterGraph( UObject* Obj );` — Function to fetch outer class which is of type UEGraph.
- L91 _protected prototype_ `FText GetBlueprintTitle() const;` — Helper method used to show blueprint title in breadcrumbs
- L94 _protected prototype_ `TSharedRef<SWidget> CreateBookmarkSelectionWidget();` — Helper method used to create the bookmark selector widget

### `Source/Editor/Kismet/Private/SGraphTitleBarAddNewBookmark.h` (Private)


#### class `SGraphTitleBarAddNewBookmark`  
`class SGraphTitleBarAddNewBookmark : public SComboButton`  
_L13-44_
- inherits: `SComboButton`
- L16 _public function_ `SLATE_BEGIN_ARGS(SGraphTitleBarAddNewBookmark) : _EditorPtr()`
- L20 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class FBlueprintEditor>, EditorPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _protected prototype_ `FText GetPopupTitleText() const;`
- L27 _protected prototype_ `FText GetDefaultNameText() const;`
- L28 _protected prototype_ `const FSlateBrush* GetAddButtonIcon() const;`
- L29 _protected prototype_ `FText GetAddButtonLabel() const;`
- L31 _protected prototype_ `void OnComboBoxOpened();`
- L32 _protected prototype_ `FReply OnAddButtonClicked();`
- L33 _protected prototype_ `bool IsAddButtonEnabled() const;`
- L34 _protected prototype_ `FReply OnRemoveButtonClicked();`
- L35 _protected prototype_ `void OnNameTextCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L38 _private member_ `TWeakPtr<class FBlueprintEditor> EditorContextPtr;`
- L39 _private member_ `TSharedPtr<class SEditableTextBox> NameEntryWidget;`
- L41 _private member_ `FText CurrentNameText;`
- L42 _private member_ `FText OriginalNameText;`
- L43 _private member_ `FGuid CurrentViewBookmarkId;`

### `Source/Editor/Kismet/Private/SReplaceNodeReferences.h` (Private)


#### class `FTargetReplaceReferences`  
`class FTargetReplaceReferences`  
_L40-77_
- L43 _public prototype_ `virtual ~FTargetReplaceReferences() = default;`
- L46 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget() const = 0;` — Returns a generated widget to represent this target item reference
- L54 _public prototype_ `virtual bool GetMemberReference(FMemberReference& OutVariableReference) const = 0;` — Retrieves the MemberReference represented by this item, if any @param OutVariableReference		The output MemberReference represented by this item @return							TRUE if successful at having a MemberReference
- L57 _public prototype_ `virtual FText GetDisplayTitle() const = 0;` — Returns the display title for this item
- L60 _public function_ `virtual bool IsCategory() const` — TRUE if this item is a category and nothing else
- L63 _public function_ `virtual const struct FSlateBrush* GetIcon() const` — Returns the Icon representing this reference
- L66 _public function_ `virtual FSlateColor GetIconColor() const` — Returns the Icon Color of this reference
- L69 _public function_ `virtual const struct FSlateBrush* GetSecondaryIcon() const` — Returns the Secondary Icon representing this reference
- L72 _public function_ `virtual FSlateColor GetSecondaryIconColor() const` — Returns the Secondary Icon Color of this reference
- L76 _public member_ `TArray< TSharedPtr<FTargetReplaceReferences> > Children;` — Children members to sub-list in the tree

#### class `SReplaceNodeReferences`  
`class SReplaceNodeReferences : public SCompoundWidget`  
_L79-262_
- inherits: `SCompoundWidget`
- L82 _protected typedef_ `typedef TSharedPtr< FTargetReplaceReferences > FTreeViewItem;`
- L83 _protected typedef_ `typedef STreeView<FTreeViewItem> SReplaceReferencesTreeViewType;`
- L85 _public function_ `SLATE_BEGIN_ARGS( SReplaceNodeReferences )`
- L88 _public function_ `SReplaceNodeReferences() : SourceProperty(nullptr)`
- L94 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<class FBlueprintEditor> InBlueprintEditor);`
- L95 _public prototype_ `~SReplaceNodeReferences();`
- L98 _public prototype_ `void Refresh();` — Forces a refresh on this widget when things in the Blueprint Editor have changed
- L101 _public prototype_ `void SetSourceVariable(FProperty* InProperty);` — Sets a source variable reference to replace
- L106 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FTreeViewItem InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L109 _protected prototype_ `void OnGetChildren( FTreeViewItem InItem, TArray< FTreeViewItem >& OutChildren );` — Get the children of a row
- L112 _protected prototype_ `TSharedRef<SWidget> GetTargetMenuContent();` — Returns the menu content for the Target Reference drop down section of the combo button
- L115 _protected prototype_ `TSharedRef<SWidget> GetSourceMenuContent();` — Returns the menu content for the Source Reference drop down section of the combo button
- L118 _protected prototype_ `void OnTargetSelectionChanged(FTreeViewItem Selection, ESelectInfo::Type SelectInfo);` — Callback when selection in the target combo button has changed
- L121 _protected prototype_ `void OnSourceSelectionChanged(FTreeViewItem Selection, ESelectInfo::Type SelectInfo);` — Callback when selection in the target combo button has changed
- L128 _protected prototype_ `void OnSubmitSearchQuery(bool bFindAndReplace);` — Submits a search query and potentially does a mass replace on results @param bInFindAndReplace		TRUE if it's a Find-and-Replace action, FALSE if it should do a search of items that will be replaced
- L131 _protected prototype_ `FReply OnFindAll();` — Callback for "Find All" button
- L134 _protected prototype_ `FReply OnFindAndReplaceAll();` — Callback for "Find and Replace All" button
- L137 _protected prototype_ `void FindAllReplacementsComplete(TArray<FImaginaryFiBDataSharedPtr>& InRawDataList);` — Callback when the search for "Find and Replace All" is complete so that the replacements can begin
- L145 _protected prototype_ `void GatherAllAvailableBlueprintVariables(UClass* InTargetClass, bool bForTarget);` — Gathers all Blueprint Variable references from the Target Class @param InTargetClass Class to gather variables from @param bForTarget    TRUE if we need to check that the type is the same as the source and recurse parent classes, FALSE if picking a new source
- L148 _protected prototype_ `FText GetTargetDisplayText() const;` — Returns the display text for the target reference
- L151 _protected prototype_ `const struct FSlateBrush* GetTargetIcon() const;` — Returns the icon for the target reference
- L154 _protected prototype_ `FSlateColor GetTargetIconColor() const;` — Returns the icon color for the target reference
- L157 _protected prototype_ `const struct FSlateBrush* GetSecondaryTargetIcon() const;` — Returns the icon for the target reference
- L160 _protected prototype_ `FSlateColor GetSecondaryTargetIconColor() const;` — Returns the icon color for the target reference
- L163 _protected prototype_ `FText GetSourceDisplayText() const;` — Returns the display text for the source reference
- L166 _protected prototype_ `const FSlateBrush* GetSourceReferenceIcon() const;` — Returns the icon for the source reference
- L169 _protected prototype_ `FSlateColor GetSourceReferenceIconColor() const;` — Returns the icon color for the source reference
- L172 _protected prototype_ `const FSlateBrush* GetSecondarySourceReferenceIcon() const;` — Returns the secondary icon for the source reference
- L175 _protected prototype_ `FSlateColor GetSecondarySourceReferenceIconColor() const;` — Returns the secondary icon color for the source reference
- L178 _protected prototype_ `FText GetFindAllButtonText() const;` — Returns the text for the Find All button
- L181 _protected prototype_ `FText GetFindAndReplaceAllButtonText() const;` — Returns the text for the Find and Replace All button
- L184 _protected prototype_ `FText GetFindAndReplaceToolTipText(bool bFindAndReplace) const;` — Returns tool tip text for the "Find All" and "Find And Replace All" buttons
- L187 _protected prototype_ `bool CanBeginSearch(bool bFindAndReplace) const;` — Returns whether or not a search can be initiated right now
- L190 _protected prototype_ `void OnLocalCheckBoxChanged(ECheckBoxState Checked);` — Callback for when the "Only Local Results" CheckBox is changed
- L193 _protected prototype_ `ECheckBoxState GetLocalCheckBoxState() const;` — Returns the current state of the "Only Local Results" CheckBox
- L196 _protected prototype_ `FText GetLocalCheckBoxLabelText() const;` — Returns the label text for the "OnlyLocalResults" CheckBox
- L199 _protected prototype_ `void OnShowReplacementsCheckBoxChanged(ECheckBoxState Checked);` — Callback for when the "Show When Finished" CheckBox is changed
- L202 _protected prototype_ `ECheckBoxState GetShowReplacementsCheckBoxState() const;` — Returns the current state of the "Show When Finished" CheckBox
- L205 _protected prototype_ `FText GetShowReplacementsCheckBoxLabelText() const;` — Returns the label text for the "Show When Finished" CheckBox
- L208 _protected prototype_ `FText GetStatusText() const;` — Returns the text to display in the bottom right corner of the window
- L211 _protected prototype_ `bool IsSearchInProgress() const;` — Determines whether a search is actively in progress
- L218 _protected prototype_ `FText GetTransactionTitle(const FMemberReference& TargetReference) const;` — Builds a title for the transaction of Replacing references @param TargetReference  The Target variable that will be replacing the source
- L222 _protected member_ `TSharedPtr< SComboButton > TargetReferencesComboBox;` — Combo box for selecting the target reference
- L225 _protected member_ `TSharedPtr< SReplaceReferencesTreeViewType > AvailableTargetReferencesTreeView;` — Tree view for displaying available target references
- L228 _protected member_ `TArray< FTreeViewItem > PossibleTargetVariableList;` — List of items used for the root of the target picker tree
- L231 _protected member_ `TSharedPtr< SComboButton > SourceReferencesComboBox;` — Combo box for selecting the source reference
- L234 _protected member_ `TSharedPtr< SReplaceReferencesTreeViewType > AvailableSourceReferencesTreeView;` — Tree view for displaying available source references
- L237 _protected member_ `TArray< FTreeViewItem > PossibleSourceVariableList;` — List of items used for the root of the source picker tree
- L240 _protected member_ `UClass* TargetClass;` — Target SKEL_ class that is being referenced by this window
- L243 _protected member_ `TWeakPtr< FBlueprintEditor > BlueprintEditor;` — Blueprint editor that owns this window
- L246 _protected member_ `FEdGraphPinType SourcePinType;` — Cached SourcePinType for the property the user wants to replace
- L249 _protected member_ `FProperty* SourceProperty;` — Cached SourceProperty that the user wants to replace
- L252 _protected member_ `TSharedPtr< SFindInBlueprints > FindInBlueprints;` — Find-in-Blueprints window used for making search queries and presenting results to the user
- L255 _protected member_ `FTreeViewItem SelectedTargetReferenceItem;` — Currently selected target reference
- L258 _protected member_ `bool bFindWithinBlueprint;` — Whether to search only within the currently open blueprint
- L261 _protected member_ `bool bShowReplacementsWhenFinished;` — Whether to show a FindResults tab for the replacements after completing action

#### class `FReplaceConfirmationListItem`  
`class FReplaceConfirmationListItem`  
_L265-294_
- desc: List item for the Confirmation Dialog
- L268 _public function_ `FReplaceConfirmationListItem(const UBlueprint* InBlueprint) : Blueprint(InBlueprint), bReplace(true)`
- L271 _public function_ `const UBlueprint* GetBlueprint() const` — Gets the blueprint this Item refers to
- L274 _public function_ `bool ShouldReplace() const` — Gets whether the references in this blueprint will be replace when the modal is closed
- L277 _public function_ `void SetShouldReplace(bool bInReplace)` — Sets whether the references in this blueprint will be replace when the modal is closed
- L280 _public prototype_ `TSharedRef<SWidget> CreateWidget();` — Sets whether the references in this blueprint will be replace when the modal is closed
- L283 _private prototype_ `void OnCheckStateChanged(ECheckBoxState State);` — Callback for Checkbox status changed
- L286 _private prototype_ `ECheckBoxState IsChecked() const;` — Callback for getting Checkbox State
- L290 _private member_ `const UBlueprint* Blueprint;` — The Blueprint this item represents
- L293 _private member_ `bool bReplace;` — Whether or not to replace references in this blueprint

#### class `SReplaceReferencesConfirmation`  
`class SReplaceReferencesConfirmation : public SCompoundWidget`  
_L297-339_
- inherits: `SCompoundWidget`
- desc: Widget for the ReplaceNodeReferences Confirmation Dialog
- L300 _private typedef_ `typedef TSharedPtr<FReplaceConfirmationListItem> FListViewItem;`
- L304 _public function_ `SLATE_BEGIN_ARGS(SReplaceReferencesConfirmation) : _FindResults(nullptr)`
- L308 _public prototype_ `SLATE_ARGUMENT(TArray< FImaginaryFiBDataSharedPtr >*, FindResults) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L319 _public prototype_ `static EDialogResponse CreateModal(TArray< FImaginaryFiBDataSharedPtr >* InFindResults);` — Creates a Confirmation Modal, this function will not return until the Dialog is closed @param InFindResults The Results to filter with this dialog @return A constructed Confirmation Widget
- L323 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FListViewItem Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generates a row for a List Item
- L326 _private prototype_ `FReply CloseWindow(EDialogResponse InResponse);` — Closes the window with the given response
- L329 _private member_ `TArray< FListViewItem > AffectedBlueprints;` — The list of unique blueprints that are affected
- L332 _private member_ `TArray< FImaginaryFiBDataSharedPtr >* RawFindData;` — The find results to modify
- L335 _private member_ `EDialogResponse Response;` — The User's response
- L338 _private member_ `TSharedPtr<SWindow> MyWindow;` — Window to close when dialog completed

#### enum `SReplaceReferencesConfirmation::EDialogResponse`  
`enum class EDialogResponse`  
_L302-302_
- L302 _public enumerator_ `enum class EDialogResponse { Confirm, Cancel }; SLATE_BEGIN_ARGS(SReplaceReferencesConfirmation) : _FindResults(nullptr) {} SLATE_ARGUMENT(TArray< FImaginaryFiBDataSharedPtr >*, FindResults) SLATE_END_ARGS()`
- L302 _public enumerator_ `enum class EDialogResponse { Confirm, Cancel }; SLATE_BEGIN_ARGS(SReplaceReferencesConfirmation) : _FindResults(nullptr) {} SLATE_ARGUMENT(TArray< FImaginaryFiBDataSharedPtr >*, FindResults) SLATE_END_ARGS()`

### `Source/Editor/Kismet/Private/SSCSEditorViewport.h` (Private)


#### class `SSCSEditorViewport`  
`class SSCSEditorViewport : public SEditorViewport`  
_L19-126_
- inherits: `SEditorViewport`
- desc: Implements the viewport widget that's hosted in the SCS editor tab.
- L22 _public function_ `SLATE_BEGIN_ARGS(SSCSEditorViewport)`
- L23 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class FBlueprintEditor>, BlueprintEditor) SLATE_ARGUMENT(TSharedPtr<class FEditorModeTools>, ModeTools) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `virtual ~SSCSEditorViewport();` — Destructor.
- L42 _public prototype_ `void Invalidate();` — Invalidates the viewport client
- L49 _public prototype_ `void EnablePreview(bool bEnable);` — Sets whether or not the preview should be enabled. @param bEnable Whether or not to enable the preview.
- L57 _public prototype_ `void RequestRefresh(bool bResetCamera = false, bool bRefreshNow = false);` — Request a refresh of the preview scene/world. Will recreate actors as needed. @param bResetCamera If true, the camera will be reset to its default position based on the preview. @param bRefreshNow If true, the preview will be refreshed immediately. Otherwise, it will be deferred until the next tick (default behavior).
- L60 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L66 _public prototype_ `void OnComponentSelectionChanged();` — Called when the selected component changes in the SCS editor.
- L71 _public prototype_ `virtual void OnFocusViewportToSelection() override;` — Focuses the viewport on the currently selected components
- L76 _public prototype_ `bool GetIsSimulateEnabled();` — Returns true if simulation is enabled for the viewport
- L78 _public prototype_ `void SetOwnerTab(TSharedRef<SDockTab> Tab);`
- L80 _public prototype_ `TSharedPtr<SDockTab> GetOwnerTab() const;`
- L88 _protected prototype_ `bool IsVisible() const override;` — Determines if the viewport widget is visible. @return true if the viewport is visible; false otherwise.
- L93 _protected prototype_ `bool ShouldShowViewportCommands() const;` — Returns true if the viewport commands should be shown
- L96 _protected prototype_ `void ToggleIsSimulateEnabled();` — Called when the simulation toggle command is fired
- L99 _protected prototype_ `virtual TSharedRef<class FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L100 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L101 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<class SOverlay> Overlay) override;`
- L102 _protected prototype_ `virtual void BindCommands() override;`
- L106 _private prototype_ `EActiveTimerReturnType DeferredUpdatePreview(double InCurrentTime, float InDeltaTime, bool bResetCamera);` — One-off active timer to update the preview
- L110 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to editor tool (owner)
- L113 _private member_ `TSharedPtr<class FSCSEditorViewportClient> ViewportClient;` — Viewport client
- L116 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer (for updating the preview) is registered
- L119 _private member_ `TWeakPtr<SDockTab> OwnerTab;` — The owner dock tab for this viewport.
- L122 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L125 _private member_ `TSharedPtr<class FEditorModeTools> ModeTools;` — Pre-configured mode tools for the viewport (optional)

### `Source/Editor/Kismet/Private/STimelineEditor.h` (Private)


#### class `FTimelineEdTrack`  
`class FTimelineEdTrack`  
_L49-75_
- desc: Represents a single track on the timeline
- L55 _public member_ `int32 DisplayIndex;` — The index of the curve (due to re-ordering)
- L58 _public member_ `FSimpleDelegate OnRenameRequest;` — Trigger when a rename is requested on the track
- L61 _public function_ `static TSharedRef<FTimelineEdTrack> Make(int32 DisplayIndex)`
- L68 _private function_ `FTimelineEdTrack(int32 InDisplayIndex) : DisplayIndex(InDisplayIndex)` — Hidden constructor, always use Make above
- L74 _private function_ `FTimelineEdTrack()` — Hidden constructor, always use Make above

#### class `STimelineEdTrack`  
`class STimelineEdTrack : public SCompoundWidget`  
_L81-201_
- inherits: `SCompoundWidget`
- desc: Widget for drawing a single track
- L84 _public function_ `SLATE_BEGIN_ARGS( STimelineEdTrack )`
- L85 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FTimelineEdTrack> InTrack, TSharedPtr<class STimelineEditor> InTimelineEd);`
- L90 _private member_ `TSharedPtr<FTimelineEdTrack> Track;` — Pointer to the underlying track information
- L93 _private member_ `TWeakPtr<class STimelineEditor> TimelineEdPtr;` — Pointer back to the timeline editor widget
- L96 _private member_ `TSharedPtr<class SCurveEditor> TrackWidget;` — Pointer to track widget for drawing keys
- L99 _private member_ `TSharedPtr<SWindow> AssetCreationWindow;` — Pointer to a window which prompts user to save internal curve as an external asset
- L102 _private member_ `UCurveBase* CurveBasePtr;` — Pointer to the curve
- L105 _private member_ `FString ExternalCurvePath;` — String to display external curve path as tooltip
- L108 _private member_ `float LocalInputMin;` — The local curve input min to use when the this tracks curve view isn't synchronized.
- L111 _private member_ `float LocalInputMax;` — The local curve input max to use when the this tracks curve view isn't synchronized.
- L114 _private member_ `float LocalOutputMin;` — The local curve output min to use when the this tracks curve view isn't synchronized.
- L117 _private member_ `float LocalOutputMax;` — The local curve output max to use when the this tracks curve view isn't synchronized.
- L120 _private prototype_ `void OnCloseCreateCurveWindow();` — Function to destroy popup window
- L123 _private prototype_ `UCurveBase* CreateCurveAsset();` — Function to create curve asset inside the user specified package
- L126 _private prototype_ `void OnCreateExternalCurve();` — Callback function to initiate the external curve asset creation process
- L129 _private prototype_ `FString CreateUniqueCurveAssetPathName();` — Creates default asset path
- L132 _private prototype_ `FString GetExternalCurvePath( ) const;` — Get the current external curve path
- L135 _private prototype_ `void SwitchToExternalCurve(UCurveBase* AssetCurvePtr);` — Function to replace internal curve with an external curve
- L138 _private prototype_ `void UseExternalCurve( UObject* AssetObj );` — Function to update track with external curve reference
- L141 _private prototype_ `void UseInternalCurve( );` — Function to convert external curve to an internal curve
- L144 _private prototype_ `FReply OnClickClear();` — Callback function to replace external curve with an internal curve
- L147 _private prototype_ `void ResetExternalCurveInfo( );` — Function to reset external curve info
- L150 _private prototype_ `static void CopyCurveData( const FRichCurve* SrcCurve, FRichCurve* DestCurve );` — Function to copy data from one curve to another
- L153 _private prototype_ `ECheckBoxState GetIsExpandedState() const;` — Gets whether this track is expanded.
- L155 _private prototype_ `void OnIsExpandedStateChanged(ECheckBoxState IsExpandedState);` — Callback for when the expanded state for this track changes.
- L158 _private prototype_ `EVisibility GetContentVisibility() const;` — Gets whether or not the content of this track should be visible, based on whether or not it's expanded.
- L161 _private prototype_ `ECheckBoxState GetIsCurveViewSynchronizedState() const;` — Gets a check box state representing whether or not this track's curve view is synchronized with other tracks.
- L163 _private prototype_ `void OnIsCurveViewSynchronizedStateChanged(ECheckBoxState IsCurveViewSynchronized);` — Callback for when the check box state representing whether or not this track's curve view is synchronized with other tracks changes.
- L166 _private prototype_ `FReply OnMoveUp();` — Moves selected track up in the track list
- L168 _private prototype_ `bool CanMoveUp() const;` — Checks if you can move the selected track up
- L171 _private prototype_ `FReply OnMoveDown();` — Moves selected track down in the track list
- L173 _private prototype_ `bool CanMoveDown() const;` — Checks if you can move the selected track down
- L175 _private prototype_ `void MoveTrack(int32 DirectionDelta);`
- L178 _private prototype_ `float GetMinInput() const;` — Get the minimum input for the curve view.
- L180 _private prototype_ `float GetMaxInput() const;` — Get the maximum input for the curve view.
- L183 _private prototype_ `float GetMinOutput() const;` — Get the minimum output for the curve view.
- L185 _private prototype_ `float GetMaxOutput() const;` — Get the maximum output for the curve view.
- L188 _private prototype_ `void OnSetInputViewRange(float Min, float Max);` — Callback to set the input view range for the curve editor.
- L190 _private prototype_ `void OnSetOutputViewRange(float Min, float Max);` — Callback to set the output view range for the curve editor.
- L192 _private prototype_ `void OnChooseCurve(const FAssetData& InObject);` — Callback when the user picks a curve from the asset picker for a track
- L195 _private prototype_ `FTTTrackBase* GetTrackBase();` — helper function to make getting expanded and synchronized state easier
- L196 _private prototype_ `const FTTTrackBase* GetTrackBase() const;`
- L200 _public member_ `TSharedPtr<SInlineEditableTextBlock> InlineNameBlock;` — Inline block for changing name of track

#### class `STimelineEditor`  
`class STimelineEditor : public SCompoundWidget`  
_L210-374_
- inherits: `SCompoundWidget`
- desc: Overall timeline editing widget
- L213 _public function_ `SLATE_BEGIN_ARGS( STimelineEditor )`
- L218 _private member_ `TSharedPtr<STimelineEdTrackListType> TrackListView;` — List widget used for showing tracks
- L221 _private member_ `TArray< TSharedPtr<FTimelineEdTrack> > TrackList;` — Underlying array of tracks, used by TrackListView
- L224 _private member_ `TWeakPtr<FBlueprintEditor> Kismet2Ptr;` — Pointer back to owning Kismet 2 tool
- L227 _private member_ `TSharedPtr<SEditableTextBox> TimelineLengthEdit;` — Text box for editing length of timeline
- L230 _private member_ `TSharedPtr<SCheckBox> LoopCheckBox;` — If we want the timeline to loop
- L233 _private member_ `TSharedPtr<SCheckBox> ReplicatedCheckBox;` — If we want the timeline to replicate
- L236 _private member_ `TSharedPtr<SCheckBox> PlayCheckBox;` — If we want the timeline to auto-play
- L239 _private member_ `TSharedPtr<SCheckBox> UseLastKeyframeCheckBox;` — If we want the timeline to play to the full specified length, or just to the last keyframe of its curves
- L242 _private member_ `TSharedPtr<SCheckBox> IgnoreTimeDilationCheckBox;` — If we want the timeline to replicate
- L245 _private member_ `UTimelineTemplate* TimelineObj;` — Pointer to the timeline object we are editing
- L248 _private member_ `float ViewMinInput;` — Minimum input shown for tracks
- L251 _private member_ `float ViewMaxInput;` — Maximum input shown for tracks
- L254 _private member_ `float ViewMinOutput;` — Minimum output shown for tracks
- L257 _private member_ `float ViewMaxOutput;` — Maximum output shown for tracks
- L260 _private member_ `FName NewTrackPendingRename;` — The default name of the last track created, used to identify which track needs to be renamed.
- L263 _private member_ `TSharedPtr< FUICommandList > CommandList;` — The commandlist for the Timeline editor.
- L266 _private member_ `FVector2f TimelineDesiredSize;` — The current desired size of the timeline
- L269 _private member_ `float NominalTimelineDesiredHeight;` — The nominal desired height of a single timeline track at 1.0x height
- L272 _public prototype_ `UTimelineTemplate* GetTimeline();` — Get the timeline object that we are currently editing
- L275 _public prototype_ `void OnTimelineChanged();` — Called when the timeline changes to get the editor to refresh its state
- L277 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FBlueprintEditor> InKismet2, UTimelineTemplate* InTimelineObj);`
- L279 _public prototype_ `float GetViewMinInput() const;`
- L280 _public prototype_ `float GetViewMaxInput() const;`
- L281 _public prototype_ `float GetViewMinOutput() const;`
- L282 _public prototype_ `float GetViewMaxOutput() const;`
- L285 _public prototype_ `float GetTimelineLength() const;` — Return length of timeline
- L287 _public prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);`
- L288 _public prototype_ `void SetOutputViewRange(float InViewMinOutput, float InViewMaxOutput);`
- L291 _public prototype_ `bool OnVerifyTrackNameCommit(const FText& TrackName, FText& OutErrorMessage, FTTTrackBase* TrackBase, STimelineEdTrack* Track );` — When user attempts to commit the name of a track
- L293 _public prototype_ `void OnTrackNameCommitted(const FText& Name, ETextCommit::Type CommitInfo, FTTTrackBase* TrackBase, STimelineEdTrack* Track );` — When user commits the name of a track
- L296 _public prototype_ `UCurveBase* CreateNewCurve(FTTTrackBase::ETrackType Type );` — Create curve object based on curve type
- L298 _public prototype_ `void OnReorderTracks(int32 DisplayIndex, int32 DirectionDelta);`
- L301 _public prototype_ `FVector2D GetTimelineDesiredSize() const;` — Gets the desired size for timelines
- L304 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget interface
- L308 _private prototype_ `TSharedRef<ITableRow> MakeTrackWidget( TSharedPtr<FTimelineEdTrack> Track, const TSharedRef<STableViewBase>& OwnerTable );` — Used by list view to create a track widget from the track item struct
- L310 _private prototype_ `void CreateNewTrack(FTTTrackBase::ETrackType Type );` — Add a new track to the timeline
- L313 _private prototype_ `bool CanDeleteSelectedTracks() const;` — Checks if the user can delete the selected tracks
- L315 _private prototype_ `void OnDeleteSelectedTracks();` — Deletes the currently selected tracks
- L318 _private prototype_ `FText GetTimelineName() const;` — Get the name of the timeline we are editing
- L321 _private prototype_ `ECheckBoxState IsAutoPlayChecked() const;` — Get state of autoplay box
- L323 _private prototype_ `void OnAutoPlayChanged(ECheckBoxState NewType);` — Handle play box being changed
- L326 _private prototype_ `ECheckBoxState IsLoopChecked() const;` — Get state of loop box
- L328 _private prototype_ `void OnLoopChanged(ECheckBoxState NewType);` — Handle loop box being changed
- L331 _private prototype_ `ECheckBoxState IsReplicatedChecked() const;` — Get state of replicated box
- L333 _private prototype_ `void OnReplicatedChanged(ECheckBoxState NewType);` — Handle loop box being changed
- L336 _private prototype_ `ECheckBoxState IsUseLastKeyframeChecked() const;` — Get state of the use last keyframe checkbox
- L338 _private prototype_ `void OnUseLastKeyframeChanged(ECheckBoxState NewType);` — Handle toggling between use last keyframe and use length
- L341 _private prototype_ `ECheckBoxState IsIgnoreTimeDilationChecked() const;` — Get state of replicated box
- L343 _private prototype_ `void OnIgnoreTimeDilationChanged(ECheckBoxState NewType);` — Handle loop box being changed
- L346 _private prototype_ `FText GetLengthString() const;` — Get current length of timeline as string
- L348 _private prototype_ `void OnLengthStringChanged(const FText& NewString, ETextCommit::Type CommitInfo);` — Handle length string being changed
- L351 _private prototype_ `bool IsCurveAssetSelected() const;` — Function to check whether a curve asset is selected in content browser in order to enable "Add Curve Asset" button
- L354 _private prototype_ `void CreateNewTrackFromAsset();` — Create new track from curve asset
- L357 _private prototype_ `void OnItemScrolledIntoView( TSharedPtr<FTimelineEdTrack> InTrackNode, const TSharedPtr<ITableRow>& InWidget );` — Callback when a track item is scrolled into view
- L360 _private prototype_ `void OnTimelineTickGroupChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Callback when the TimelineTickGroup is changed via Editor controls
- L363 _private prototype_ `bool CanRenameSelectedTrack() const;` — Checks if you can rename the selected track
- L365 _private prototype_ `void OnRequestTrackRename() const;` — Informs the selected track that the user wants to rename it
- L368 _private prototype_ `TSharedPtr< SWidget > MakeContextMenu() const;` — Creates the right click context menu for the track list
- L370 _private prototype_ `void SetSizeScaleValue(float NewValue);`
- L371 _private prototype_ `float GetSizeScaleValue() const;`
- L373 _private prototype_ `TSharedRef<SWidget> MakeAddButton();`

#### Free symbols / members of external scopes

- L207 _typedef_ `typedef SListView< TSharedPtr<FTimelineEdTrack> > STimelineEdTrackListType;` — Type used for list widget of tracks

### `Source/Editor/Kismet/Private/UserDefinedEnumEditor.h` (Private)


#### class `FUserDefinedEnumEditor`  
`class FUserDefinedEnumEditor : public IUserDefinedEnumEditor`  
_L37-83_
- inherits: `IUserDefinedEnumEditor`
- L40 _private member_ `static const FName UserDefinedEnumEditorAppIdentifier;` — App Identifier.
- L43 _private member_ `static const FName EnumeratorsTabId;` — The tab ids for all the tabs used
- L46 _private member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L56 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UUserDefinedEnum* EnumToEdit);` — Edits the specified enum @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	EnumToEdit				The user defined enum to edit
- L59 _public prototype_ `virtual ~FUserDefinedEnumEditor();` — Destructor
- L62 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L63 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L64 _public prototype_ `virtual FText GetToolkitName() const override;`
- L65 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L66 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L67 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L69 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L70 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L73 _protected prototype_ `TSharedRef<SDockTab> SpawnEnumeratorsTab(const FSpawnTabArgs& Args);`
- L76 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L79 _private prototype_ `FReply OnAddNewEnumerator();` — Handles new enum element request
- L82 _private member_ `TWeakObjectPtr<UUserDefinedEnum> TargetEnum;`

#### class `FEnumDetails`  
`class FEnumDetails : public IDetailCustomization, FEnumEditorUtils::INotifyOnEnumChanged, FEditorUndoClient`  
_L86-121_
- inherits: `IDetailCustomization,FEnumEditorUtils::INotifyOnEnumChanged,FEditorUndoClient`
- desc: Details customization for functions and graphs selected in the MyBlueprint panel
- L90 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L95 _public prototype_ `FEnumDetails();`
- L96 _public prototype_ `~FEnumDetails();`
- L99 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L102 _public prototype_ `void OnForceRefresh();` — Forces a refresh on the details customization
- L105 _public prototype_ `virtual void PreChange(const class UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;` — FEnumEditorUtils::INotifyOnEnumChanged
- L106 _public prototype_ `virtual void PostChange(const class UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;`
- L109 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L110 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L114 _private prototype_ `ECheckBoxState OnGetBitmaskFlagsAttributeState() const;` — Handles the optional bitmask flags attribute
- L115 _private prototype_ `void OnBitmaskFlagsAttributeStateChanged(ECheckBoxState InNewState);`
- L118 _private member_ `TSharedPtr<class FUserDefinedEnumLayout> Layout;`
- L120 _private member_ `TWeakObjectPtr<UUserDefinedEnum> TargetEnum;` — The target node that this argument is on

#### class `FUserDefinedEnumLayout`  
`class FUserDefinedEnumLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FUserDefinedEnumLayout>`  
_L124-154_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FUserDefinedEnumLayout>`
- desc: Custom struct for each group of arguments in the function editing details
- L127 _public function_ `FUserDefinedEnumLayout(UUserDefinedEnum* InTargetEnum) : TargetEnum(InTargetEnum)`
- L131 _public function_ `void Refresh()`
- L136 _public prototype_ `bool CausedChange() const;`
- L140 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L141 _private function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override`
- L142 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L143 _private function_ `virtual void Tick( float DeltaTime ) override`
- L144 _private function_ `virtual bool RequiresTick() const override`
- L145 _private function_ `virtual FName GetName() const override`
- L146 _private function_ `virtual bool InitiallyCollapsed() const override`
- L149 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L151 _private member_ `TWeakObjectPtr<UUserDefinedEnum> TargetEnum;` — The target node that this argument is on
- L153 _private member_ `TArray<TWeakPtr<class FUserDefinedEnumIndexLayout>> Children;`

#### class `FUserDefinedEnumIndexLayout`  
`class FUserDefinedEnumIndexLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FUserDefinedEnumIndexLayout>`  
_L157-193_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FUserDefinedEnumIndexLayout>`
- desc: Custom struct for each group of arguments in the function editing details
- L160 _public function_ `FUserDefinedEnumIndexLayout(UUserDefinedEnum* InTargetEnum, int32 InEnumeratorIndex) : TargetEnum(InTargetEnum) , EnumeratorIndex(InEnumeratorIndex)`
- L165 _public prototype_ `bool CausedChange() const;`
- L169 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L170 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L171 _private function_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override`
- L172 _private function_ `virtual void Tick( float DeltaTime ) override`
- L173 _private function_ `virtual bool RequiresTick() const override`
- L174 _private function_ `virtual FName GetName() const override`
- L175 _private function_ `virtual bool InitiallyCollapsed() const override`
- L179 _private prototype_ `void OnEnumeratorRemove();` — Deletes the enumerator
- L183 _private member_ `UUserDefinedEnum* TargetEnum;` — The target node that this argument is on
- L186 _private member_ `int32 EnumeratorIndex;` — Index of enumerator
- L189 _private member_ `TSharedPtr<FEditableTextUserDefinedEnum> DisplayNameEditor;` — The editable text interface for the display name data
- L192 _private member_ `TSharedPtr<FEditableTextUserDefinedEnumTooltip> TooltipEditor;` — The editable text interface for the tooltip data

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Private/UserDefinedStructureEditor.h` (Private)


#### class `FUserDefinedStructureEditor`  
`class FUserDefinedStructureEditor : public IUserDefinedStructureEditor`  
_L23-83_
- inherits: `IUserDefinedStructureEditor`
- L26 _private member_ `static const FName UserDefinedStructureEditorAppIdentifier;` — App Identifier.
- L29 _private member_ `static const FName MemberVariablesTabId;` — The tab ids for all the tabs used
- L30 _private member_ `static const FName DefaultValuesTabId;`
- L33 _private member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L34 _private member_ `TSharedPtr<class FStructureDefaultValueView> DefaultValueView;`
- L43 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UUserDefinedStruct* EnumToEdit);` — Edits the specified enum @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	EnumToEdit				The user defined enum to edit
- L46 _public prototype_ `void SetInitialPinType(FEdGraphPinType PinType);` — Sets the pin type for new struct members added via the Add Variable toolbar button
- L49 _public prototype_ `virtual ~FUserDefinedStructureEditor();` — Destructor
- L52 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L53 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L54 _public prototype_ `virtual FText GetToolkitName() const override;`
- L55 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L56 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L57 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L59 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L60 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L63 _protected prototype_ `TSharedRef<SDockTab> SpawnStructureTab(const FSpawnTabArgs& Args);`
- L64 _protected prototype_ `TSharedRef<SDockTab> SpawnStructureDefaultValuesTab(const FSpawnTabArgs& Args);`
- L67 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L70 _private prototype_ `FReply OnAddNewField();` — Handles adding a new member variable from the toolbar button
- L73 _private prototype_ `const FSlateBrush* OnGetStructureStatus() const;` — Returns the overlay image to indicate the compile status
- L76 _private prototype_ `FText OnGetStatusTooltip() const;` — Returns the tooltip describing the compile status
- L79 _private member_ `TWeakObjectPtr<UUserDefinedStruct> UserDefinedStruct;`
- L82 _private member_ `FEdGraphPinType InitialPinType;` — Cached value of the last pin type the user selected, used as the initial value for new struct members

### `Source/Editor/Kismet/Public/BPVariableDragDropAction.h` (Public)


#### class `FKismetVariableDragDropAction`  
`class FKismetVariableDragDropAction : public FMyBlueprintItemDragDropAction`  
_L33-127_
- inherits: `FMyBlueprintItemDragDropAction`
- desc: DragDropAction class for dropping a Variable onto a graph
- L36 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FKismetVariableDragDropAction, FMyBlueprintItemDragDropAction)`
- L40 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L41 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L42 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< class SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L45 _public function_ `static TSharedRef<FKismetVariableDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InAction, FName InVariableName, UStruct* InVariableSource, FNodeCreationAnalytic AnalyticCallback)`
- L56 _public function_ `FProperty* GetVariableProperty()`
- L67 _protected prototype_ `FKismetVariableDragDropAction();` — Construct a FKismetVariableDragDropAction
- L79 _protected prototype_ `virtual void GetDefaultStatusSymbol(const FSlateBrush*& PrimaryBrushOut, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut) const override;` — FGraphSchemaActionDragDropAction interface
- L83 _protected prototype_ `virtual UBlueprint* GetSourceBlueprint() const override;` — FMyBlueprintItemDragDropAction interface
- L87 _protected prototype_ `static void MakeGetter(FNodeConstructionParams InParams);` — Called when user selects to create a Getter for the variable
- L89 _protected prototype_ `static void MakeSetter(FNodeConstructionParams InParams);` — Called when user selects to create a Setter for the variable
- L91 _protected prototype_ `static bool CanExecuteMakeSetter(FNodeConstructionParams InParams, FProperty* InVariableProperty);` — Called too check if we can execute a setter on a given property
- L100 _protected prototype_ `void GetLinksThatWillBreak(UEdGraphNode* Node, FProperty* NewVariableProperty, TArray<class UEdGraphPin*>& OutBroken);` — Test new variable type against existing links for node and get any links that will break @param	Node						The node with existing links @param	NewVariableProperty			the property for the new variable type @param	OutBroken						All of the links which are NOT compatible with the new type
- L103 _protected function_ `bool WillBreakLinks( UEdGraphNode* Node, FProperty* NewVariableProperty )` — Indicates if replacing the variable node, with the new property will require any links to be broken
- L116 _protected prototype_ `bool CanVariableBeDropped(const FProperty* InVariableProperty, const UEdGraph& InGraph) const;` — Checks if the property can be dropped in a graph @param InVariableProperty		The variable property to check with @param InGraph					The graph to check against placing the variable
- L120 _protected prototype_ `UStruct* GetLocalVariableScope() const;` — Returns the local variable's scope, if any
- L124 _protected member_ `FName VariableName;` — Name of variable being dragged
- L126 _protected member_ `TWeakObjectPtr<UStruct> VariableSource;` — Scope this variable belongs to

#### struct `FKismetVariableDragDropAction::FNodeConstructionParams`  
`struct FNodeConstructionParams`  
_L70-76_
- desc: Structure for required node construction parameters
- L72 _public member_ `FDeprecateSlateVector2D GraphPosition;`
- L73 _public member_ `UEdGraph* Graph;`
- L74 _public member_ `FName VariableName;`
- L75 _public member_ `TWeakObjectPtr<UStruct> VariableSource;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintActionMenuBuilder.h` (Public)


#### struct `FBlueprintActionMenuBuilder`  
`struct FBlueprintActionMenuBuilder : public FGraphActionListBuilderBase`  
_L34-129_
- inherits: `FGraphActionListBuilderBase`
- desc: Responsible for constructing a list of viable blueprint actions. Runs the blueprint actions database through a filter and spawns a series of FBlueprintActionMenuItems for actions that pass. Takes care of generating the each menu item's category/name/etc.
- L70 _public prototype_ `FBlueprintActionMenuBuilder(EConfigFlags Flags = EConfigFlags::DefaultConfig);` — Default constructor. @param Flags	- Optional configuration flags.
- L73 _public prototype_ `virtual void Empty() override;` — FGraphActionListBuilderBase interface
- L88 _public prototype_ `void AddMenuSection(FBlueprintActionFilter const& Filter, FText const& Heading = FText::GetEmpty(), int32 MenuOrder = 0, uint32 const Flags = 0);` — Some action menus require multiple sections. One option is to create multiple FBlueprintActionMenuBuilders and append them together, but that can be unperformant (each builder will run through the entire database separately)... This method provides an alternative, where you can specify a separate filter/heading/ordering for a sub-section of the menu. @param  Filter	 The filter you want applied to this section of the menu. @param  Heading	 The root category for this section of the menu (can be left blank). @param  MenuOrder The sort order to assign this section of the menu (higher numbers come first). @param  Flags	 Set of ESectionFlags to customize this menu section.
- L95 _public prototype_ `void RebuildActionList();` — Regenerates the entire menu list from the cached menu sections. Filters and adds action items from the blueprint action database (as defined by the MenuSections list).
- L98 _public prototype_ `int32 GetNumPendingActions() const;` — Returns the current number of actions that are still pending
- L101 _public prototype_ `bool ProcessPendingActions();` — Processes any actions that may be added asynchronously or across multiple frames. Returns true if one or more actions were added into the list.
- L104 _public prototype_ `float GetPendingActionsProgress() const;` — Returns the normalized completion state when processing pending actions (e.g. for a status indicator)
- L108 _protected prototype_ `void MakeMenuItems(FBlueprintActionInfo& InAction);` — Adds menu items for the given database action.
- L111 _protected prototype_ `void BuildCompleted();` — Called when all menu items have been constructed.
- L119 _private member_ `TArray< TSharedRef<FBlueprintActionMenuBuilderImpl::FMenuSectionDefinition> > MenuSections;` — Defines all the separate sections of the menu (filter, sort order, etc.). Defined as a TSharedRef<> so as to hide the implementation details (keep this API clean).
- L125 _private member_ `TSharedPtr<FBlueprintActionMenuBuilderImpl::FMenuItemListAddHelper> MenuItemListAddHelper;` — Defines a utility that assists with building the list of action menu items for each menu section based on a set of Blueprint action descriptor records.
- L128 _private member_ `bool bUsePendingActionList;` — If enabled, actions will be added to the pending list rather than processed immediately.

#### enum `FBlueprintActionMenuBuilder::EConfigFlags`  
`enum EConfigFlags`  
_L38-47_
- desc: Flags used to configure the builder.
- L43 _public enumerator_ `UseTimeSlicing = (1<<0)` — If set, the builder will be configured to process the registered action set over time, rather than process the entire set in a single blocking frame.
- L46 _public enumerator_ `DefaultConfig = 0` — The default configuration for this builder type.

#### enum `FBlueprintActionMenuBuilder::ESectionFlag`  
`enum ESectionFlag`  
_L50-62_
- desc: Flags used to customize specific sections of the menu.
- L54 _public enumerator_ `ConsolidatePropertyActions = (1<<0)` — Rolls properties into a single menu item that will spawn a drag-drop menu for users to pick a node type from.
- L58 _public enumerator_ `ConsolidateBoundActions = (1<<1)` — Rolls bound node spawners into a single menu entry that will spawn multiple nodes, each bound to a single binding.
- L61 _public enumerator_ `FlattenCategoryHierarcy = (1<<2)` — Will clear all action categories (except the section's root)

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API KISMET_API`
- L17 _namespace_ `namespace FBlueprintActionMenuBuilderImpl`
- L131 _prototype_ `ENUM_CLASS_FLAGS(FBlueprintActionMenuBuilder::EConfigFlags);`

### `Source/Editor/Kismet/Public/BlueprintActionMenuItem.h` (Public)


#### struct `FBlueprintActionMenuItem`  
`struct FBlueprintActionMenuItem : public FEdGraphSchemaAction`  
_L39-93_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Wrapper around a UBlueprintNodeSpawner, which takes care of specialized node spawning. This class should not be sub-classed, any special handling should be done inside a UBlueprintNodeSpawner subclass, which will be invoked from this class (separated to divide ui and node-spawning).
- L42 _public function_ `static FName StaticGetTypeId()`
- L46 _public function_ `FBlueprintActionMenuItem(UBlueprintNodeSpawner const* NodeSpawner = nullptr) : Action(NodeSpawner), IconTint(FLinearColor::White), IconBrush(nullptr)` — Constructors
- L47 _public prototype_ `FBlueprintActionMenuItem(UBlueprintNodeSpawner const* NodeSpawner, FBlueprintActionUiSpec const& UiDef, IBlueprintNodeBinder::FBindingSet const& Bindings = IBlueprintNodeBinder::FBindingSet(), FText InNodeCategory = FText(), int32 InGrouping = 0);`
- L50 _public function_ `virtual FName GetTypeId() const final` — FEdGraphSchemaAction interface
- L52 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) final;`
- L53 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) final;`
- L54 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) final;`
- L58 _public prototype_ `UBlueprintNodeSpawner const* GetRawAction() const;` — @return
- L60 _public prototype_ `void AppendBindings(const FBlueprintActionContext& Context, IBlueprintNodeBinder::FBindingSet const& BindingSet);`
- L69 _public prototype_ `FSlateBrush const* GetMenuIcon(FSlateColor& ColorOut);` — Retrieves the icon brush for this menu entry (to be displayed alongside in the menu). @param  ColorOut	An output parameter that's filled in with the color to tint the brush with. @return An slate brush to be used for this menu item in the action menu.
- L80 _public prototype_ `const FDocExcerptRef& GetDocumentationExcerpt() const;`
- L84 _private member_ `TObjectPtr<const UBlueprintNodeSpawner> Action;` — Specialized node-spawner, that comprises the action portion of this menu entry.
- L86 _private member_ `FSlateColor IconTint;` — Tint to return along with the icon brush.
- L88 _private member_ `FSlateBrush const* IconBrush;` — Brush that should be used for the icon on this menu item.
- L90 _private member_ `IBlueprintNodeBinder::FBindingSet Bindings;`
- L92 _private member_ `FDocExcerptRef DocExcerptRef;` — References the documentation page/excerpt pertaining to the node this will spawn

#### struct `FBlueprintActionMenuItem::FDocExcerptRef`  
`struct FDocExcerptRef`  
_L72-78_
- desc: Utility struct for pairing documentation page names with excerpt names
- L74 _public prototype_ `bool IsValid() const;`
- L76 _public member_ `FString DocLink;`
- L77 _public member_ `FString DocExcerptName;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintActionMenuUtils.h` (Public)


#### enum `EContextTargetFlags::Type`  
`enum Type : int`  
_L23-35_
- L25 _public enumerator_ `TARGET_Blueprint = 0x00000001 UMETA(DisplayName="This Blueprint", ToolTip="Include functions and variables that belong to this Blueprint.")`
- L26 _public enumerator_ `TARGET_SubComponents = 0x00000002 UMETA(DisplayName="Components", ToolTip="Include functions that belong to components of this Blueprint and/or the other target classes.")`
- L27 _public enumerator_ `TARGET_NodeTarget = 0x00000004 UMETA(DisplayName="Node Target", ToolTip="Include functions and variables that belong to the same class that the pin's node does.")`
- L28 _public enumerator_ `TARGET_PinObject = 0x00000008 UMETA(DisplayName="Pin Type Class", ToolTip="Include functions and variables that belong to this pin type.")`
- L29 _public enumerator_ `TARGET_SiblingPinObjects = 0x00000010 UMETA(DisplayName="Other Object Outputs", ToolTip="Include functions and variables that belong to any of this node's output types.")`
- L30 _public enumerator_ `TARGET_BlueprintLibraries = 0x00000020 UMETA(DisplayName="Libraries", ToolTip="Include static functions that are globally accessible (belonging to function/macro libraries, etc.).")`
- L31 _public enumerator_ `TARGET_NonImportedTypes = 0x00000040 UMETA(DisplayName="Non-Imported Types", ToolTip="Include functions from loaded types that are not imported by this Blueprint.")`
- L34 _public enumerator_ `ContextTargetFlagsEnd UMETA(Hidden)` — +1 to the last flag (so we can easily iterate these flags)

#### struct `FBlueprintActionMenuUtils`  
`struct FBlueprintActionMenuUtils`  
_L38-83_
- L49 _public prototype_ `static void MakePaletteMenu(FBlueprintActionContext const& Context, UClass* FilterClass, FBlueprintActionMenuBuilder& MenuOut);` — A centralized utility function for constructing blueprint palette menus. Rolls the supplied Context and FilterClass into a filter that's used to construct the palette. @param  Context		Contains the blueprint that the palette is for. @param  FilterClass	If not null, then this specifies the class whose members we want listed (and nothing else). @param  MenuOut		The structure that will be populated with palette menu items.
- L61 _public prototype_ `static void MakeContextMenu(FBlueprintActionContext const& Context, bool bIsContextSensitive, uint32 ClassTargetMask, FBlueprintActionMenuBuilder& MenuOut);` — A centralized utility function for constructing blueprint context menus. Rolls the supplied Context and SelectedProperties into a series of filters that're used to construct the menu. @param  Context				Contains the blueprint/graph/pin that the menu is for. @param  bIsContextSensitive @param  ClassTargetMask @param  MenuOut				The structure that will be populated with context menu items.
- L71 _public prototype_ `static void MakeFavoritesMenu(FBlueprintActionContext const& Context, FBlueprintActionMenuBuilder& MenuOut);` — A centralized utility function for constructing the blueprint favorites menu. Takes the palette menu building code and folds in an additional "IsFavorited" filter check. @param  Context	Contains the blueprint that the palette is for. @param  MenuOut	The structure that will be populated with favorite menu items.
- L81 _public prototype_ `static const UK2Node* ExtractNodeTemplateFromAction(const FEdGraphSchemaAction& PaletteAction);` — A number of different palette actions hold onto node-templates in different ways. This handles most of those cases and looks to extract said node- template from the specified action. @param  PaletteAction	The action you want a node-template for. @return A pointer to the extracted node (NULL if the action doesn't have one, or we don't support the specific action type yet)
- L82 _public prototype_ `static const UK2Node* ExtractNodeTemplateFromAction(const TSharedPtr<FEdGraphSchemaAction>& PaletteAction);`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace EContextTargetFlags`

### `Source/Editor/Kismet/Public/BlueprintAssetHandler.h` (Public)


#### class `IBlueprintAssetHandler`  
`class IBlueprintAssetHandler`  
_L21-42_
- desc: Interface used to define how to interact with a blueprint within an asset
- L24 _public prototype_ `virtual ~IBlueprintAssetHandler() = default;`
- L32 _public prototype_ `virtual UBlueprint* RetrieveBlueprint(UObject* InAsset) const = 0;` — Retrieve the blueprint from the specified asset object @param InAsset         The asset object to retrieve the blueprint from @return The blueprint contained within the specified asset, or nullptr if non exists
- L41 _public prototype_ `virtual bool AssetContainsBlueprint(const FAssetData& InAssetData) const = 0;` — Check whether the specified asset registry data contains a blueprint @param InAssetData     The asset object to retrieve the blueprint from @return True if the asset contains a blueprint, false otherwise

#### class `FBlueprintAssetHandler`  
`class FBlueprintAssetHandler`  
_L48-109_
- desc: Singleton class that marshals different blueprint asset handlers for different asset class types
- L55 _public prototype_ `static FBlueprintAssetHandler& Get();` — Retrieve the singleton instance of this class
- L61 _public function_ `TArrayView<const FTopLevelAssetPath> GetRegisteredClassNames() const` — Get all the currently registered class names
- L74 _public function_ `template<typename HandlerType> void RegisterHandler(FTopLevelAssetPath ClassPathName)` — Register an asset for the specified class name @note: Any assets whose class is a child of the specified class will use this handler (unless there is a more specific handler registered) @param ClassName      The name of the class this handler relates to.
- L87 _public prototype_ `void RegisterHandler(FTopLevelAssetPath ClassPathName, TUniquePtr<IBlueprintAssetHandler>&& InHandler);` — Register an asset for the specified class name @note: Any assets whose class is a child of the specified class will use this handler (unless there is a more specific handler registered) @param ClassPathName  The path name of the class this handler relates to. @param InHandler      The implementation of the handler to use
- L96 _public prototype_ `const IBlueprintAssetHandler* FindHandler(const UClass* InClass) const;` — Find a handler that applies to the specified class @param InClass        The class to find a handler for @return A valid asset handler, or nullptr if none exists for this class
- L102 _private prototype_ `FBlueprintAssetHandler();` — Private constructor - use singleton accessor (::Get)
- L105 _private member_ `TArray<FTopLevelAssetPath> ClassNames;` — Unsorted array of class names, one per-handler below
- L108 _private member_ `TArray<TUniquePtr<IBlueprintAssetHandler>> Handlers;` — Array of handlers that relate to the class names above

### `Source/Editor/Kismet/Public/BlueprintCompilationManager.h` (Public)


#### struct `FBPCompileRequest`  
`struct FBPCompileRequest`  
_L23-36_
- L25 _public prototype_ `explicit FBPCompileRequest(UBlueprint* InBPToCompile, EBlueprintCompileOptions InCompileOptions, FCompilerResultsLog* InClientResultsLog);`
- L28 _public member_ `TObjectPtr<UBlueprint> BPToCompile;` — BP that needs to be compiled:
- L31 _public member_ `EBlueprintCompileOptions CompileOptions;` — Legacy options for blueprint compilation:
- L35 _public member_ `FCompilerResultsLog* ClientResultsLog;` — Clients can give us a results log if they want to parse or display it themselves, otherwise we will use a transient one:

#### struct `FBlueprintCompilationManager`  
`struct FBlueprintCompilationManager`  
_L38-103_
- L40 _public prototype_ `static void Initialize();`
- L41 _public prototype_ `static void Shutdown();`
- L50 _public prototype_ `static void FlushCompilationQueue(FUObjectSerializeContext* InLoadContext);` — Compiles all blueprints that have been placed in the compilation queue. ObjLoaded is a list of objects that need to be PostLoaded by the linker, when changing CDOs we will replace objects in this list. It is not a list of objects the compilation manager has loaded. The compilation manager will not load data while processing the compilation queue)
- L55 _public prototype_ `static void FlushCompilationQueueAndReinstance(const bool bFindAndReplaceCDOReferences = false);` — Flushes the compilation queue and finishes reinstancing
- L62 _public prototype_ `static void CompileSynchronously(const FBPCompileRequest& Request);` — Immediately compiles the blueprint, no expectation that related blueprints be subsequently compiled. It will be significantly more efficient to queue blueprints and then flush the compilation queue if there are several blueprints that require compilation (e.g. typical case on PIE):
- L67 _public prototype_ `static void NotifyBlueprintLoaded(UBlueprint* BPLoaded);` — Adds a newly loaded blueprint to the compilation queue
- L72 _public prototype_ `static void QueueForCompilation(UBlueprint* BP);` — Adds a blueprint to the compilation queue - useful for batch compilation
- L75 _public prototype_ `static bool IsGeneratedClassLayoutReady();` — Returns true when UBlueprint::GeneratedClass members are up to date
- L82 _public prototype_ `static bool GetDefaultValue(const UClass* ForClass, const FProperty* Property, FString& OutDefaultValueAsString);` — Returns the Default Value associated with ForClass::Property, if ForClass is currently being compiled this function can look at the old version of the CDO and read the default value from there
- L89 _public prototype_ `static void ReparentHierarchies(const TMap<UClass*, UClass*>& OldClassToNewClass);` — Safely reparents all child classes of every Key in OldClassToNewClass to the class in the corresponding Value. Typically this means every child type will be reinstanced - although reinstancing could be avoided when layouts match.
- L97 _public prototype_ `static void RegisterCompilerExtension(TSubclassOf<UBlueprint> BlueprintType, UBlueprintCompilerExtension* Extension);` — Registers a blueprint compiler extension - anytime a blueprint of the provided type is compiled the extension will be activated. Note that because editor initialization may require blueprint compilation there may be blueprints compiled before the extension is registed unless special care has been taken.
- L100 _public prototype_ `static void ReinstanceStruct(class UUserDefinedStruct* Struct);` — Safely updates all instances using the provided UUserDefinedStruct so that it can be mutated (inc. deletion)
- L102 _private prototype_ `FBlueprintCompilationManager();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintCompilerExtension.h` (Public)


#### struct `FBlueprintCompiledData`  
`struct FBlueprintCompiledData`  
_L19-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TArray<TObjectPtr<UEdGraph>> IntermediateGraphs;` — `UPROPERTY()`

#### class `UBlueprintCompilerExtension`  
`class UBlueprintCompilerExtension : public UObject`  
_L28-42_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L32 _public prototype_ `UBlueprintCompilerExtension(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `void BlueprintCompiled(const FKismetCompilerContext& CompilationContext, const FBlueprintCompiledData& Data);`
- L41 _protected function_ `virtual void ProcessBlueprintCompiled(const FKismetCompilerContext& CompilationContext, const FBlueprintCompiledData& Data)` — Override this if you're interested in running logic after class layout has been generated, but before bytecode and member variables have been

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintDragDropMenuItem.h` (Public)


#### struct `FBlueprintDragDropMenuItem`  
`struct FBlueprintDragDropMenuItem : public FEdGraphSchemaAction`  
_L47-102_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: At certain times we want a single menu entry that represents a set of UBlueprintNodeSpawners (generally when all those UBlueprintNodeSpawners wrap the same UField). We do this to keep the menu less jumbled, and instead use the drag/drop action to present a sub-menu to the user (so they can pick the the node type that they want). We do this with both delegates and variable nodes (where the user can pick a getter vs. a setter, etc.). This class represents those "consolidated" actions, and essentially serves as a FDragDropOperation spawner. It wraps a single UBlueprintNodeSpawner (any one of the set that it is supposed to represent), that it uses to determine the proper FDragDropOperation.
- L52 _public function_ `static FName StaticGetTypeId()`
- L54 _public function_ `FBlueprintDragDropMenuItem()` — `USTRUCT()`
- L63 _public prototype_ `FBlueprintDragDropMenuItem(FBlueprintActionContext const& Context, UBlueprintNodeSpawner const* SampleAction, int32 MenuGrouping, FText InNodeCategory, FText InMenuDesc, FText InToolTip );` — Sole constructor, which ensures that the RepresentativeAction member is set (and valid). @param  SampleAction	One of the node-spawners that this "consolidated" menu item represents (shouldn't matter which one). @param  MenuGrouping	Defines the order in which this entry is listed in the menu.
- L66 _public function_ `virtual FName GetTypeId() const final` — FEdGraphSchemaAction interface
- L67 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L68 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L69 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L79 _public prototype_ `FSlateBrush const* GetMenuIcon(FSlateColor& ColorOut);` — Retrieves the icon brush for this menu entry (to be displayed alongside in the menu). @param  ColorOut	An output parameter that's filled in with the color to tint the brush with. @return An slate brush to be used for this menu item in the action menu.
- L82 _public prototype_ `void AppendAction(UBlueprintNodeSpawner const* Action);`
- L85 _public prototype_ `UBlueprintNodeSpawner const* GetSampleAction() const;` — @return
- L88 _public prototype_ `TSet<UBlueprintNodeSpawner const*> const& GetActionSet() const;` — @return
- L97 _public prototype_ `TSharedPtr<FDragDropOperation> OnDragged(FNodeCreationAnalytic AnalyticsDelegate) const;` — Attempts to create a certain drag/drop action with respect to the set UBlueprintNodeSpawner. @param  AnalyticsDelegate	The analytics callback to assign the drag/drop operation. @return An empty TSharedPtr if we failed to determine the FDragDropOperation type to use, else a newly instantiated drag/drop op.
- L101 _private member_ `TSet<TObjectPtr<const UBlueprintNodeSpawner>> ActionSet;` — An arbitrary member of the node-spawner subset that this menu entry represents.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintEditor.h` (Public)


#### struct `FCustomDebugObject`  
`struct FCustomDebugObject`  
_L113-133_
- L117 _public member_ `UObject* Object;` — Custom object to include, regardless of the current debugging World
- L120 _public member_ `FString NameOverride;` — Override for the object name (if not empty)
- L123 _public function_ `FCustomDebugObject() : Object(nullptr)`
- L128 _public function_ `FCustomDebugObject(UObject* InObject, const FString& InLabel) : Object(InObject) , NameOverride(InLabel)`

#### struct `FSelectionDetailsSummoner`  
`struct FSelectionDetailsSummoner : public FWorkflowTabFactory`  
_L140-152_
- inherits: `FWorkflowTabFactory`
- L143 _public prototype_ `FSelectionDetailsSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L145 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L146 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L148 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### struct `FComponentEventConstructionData`  
`struct FComponentEventConstructionData`  
_L158-164_
- desc: The structure used to construct the "Add Event" menu entries
- L161 _public member_ `FName VariableName;` — The name of the event handler to create.
- L163 _public member_ `TWeakObjectPtr<UObject> Component;` — The template component that the handler applies to.

#### enum `ENodeCreateAction::Type`  
`enum Type`  
_L175-182_
- L177 _public enumerator_ `MyBlueprintDragPlacement`
- L178 _public enumerator_ `PaletteDragPlacement`
- L179 _public enumerator_ `GraphContext`
- L180 _public enumerator_ `PinContext`
- L181 _public enumerator_ `Keymap`

#### class `FBlueprintEditor`  
`class FBlueprintEditor : public IBlueprintEditor, public FGCObject, public FNotifyHook, public FTickableEditorObject, public FEditorUndoClient, public FNoncopyable`  
_L189-1614_
- inherits: `IBlueprintEditor,FGCObject,FNotifyHook,FTickableEditorObject,FEditorUndoClient,FNoncopyable`
- desc: Main Kismet asset editor
- L192 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetPinVisibility, SGraphEditor::EPinVisibility);`
- L211 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L214 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeSet, FName);`
- L215 _public function_ `FOnModeSet& OnModeSet()`
- L216 _public prototype_ `virtual void SetCurrentMode(FName NewMode) override;`
- L228 _public prototype_ `void InitBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost >& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, TSharedPtr<ISCSEditorUICustomization> InSCSEditorUICustomization = nullptr);` — Edits the specified blueprint @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InBlueprints			The blueprints to edit @param	bShouldOpenInDefaultsMode	If true, the editor will open in defaults editing mode @param	InSCSEditorUICustomization	UI customizations for the SCS editor inside the blueprint editor
- L232 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L233 _public prototype_ `virtual void OnClose() override;`
- L234 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override;`
- L235 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;`
- L236 _public prototype_ `virtual void CreateEditorModeManager() override;`
- L240 _public prototype_ `virtual FName GetToolkitContextFName() const override;`
- L241 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L242 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L243 _public prototype_ `virtual FText GetToolkitName() const override;`
- L244 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L245 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L246 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L247 _public prototype_ `virtual bool IsBlueprintEditor() const override;`
- L251 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L252 _public prototype_ `virtual FString GetReferencerName() const override;`
- L256 _public prototype_ `virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type Reason = ERefreshBlueprintEditorReason::UnknownReason) override;`
- L257 _public prototype_ `virtual void RefreshMyBlueprint();`
- L258 _public prototype_ `virtual void RefreshInspector();`
- L259 _public prototype_ `virtual void AddToSelection(UEdGraphNode* InNode) override;`
- L260 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename = false) override;`
- L261 _public prototype_ `virtual void JumpToPin(const class UEdGraphPin* Pin) override;`
- L262 _public prototype_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false) override;`
- L263 _public prototype_ `virtual void SummonFindAndReplaceUI() override;`
- L264 _public prototype_ `virtual UEdGraph* GetFocusedGraph() const override;`
- L265 _public prototype_ `virtual TSharedPtr<SGraphEditor> OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus = true) override;`
- L266 _public prototype_ `virtual TArray<TSharedPtr<FSubobjectEditorTreeNode>> GetSelectedSubobjectEditorTreeNodes() const override;`
- L267 _public prototype_ `virtual TSharedPtr<FSubobjectEditorTreeNode> FindAndSelectSubobjectEditorTreeNode(const UActorComponent* InComponent, bool IsCntrlDown) override;`
- L268 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const override;`
- L269 _public prototype_ `virtual void AnalyticsTrackNodeEvent(UBlueprint* Blueprint, UEdGraphNode *GraphNode, bool bNodeDelete = false) const override;`
- L270 _public prototype_ `void AnalyticsTrackCompileEvent(UBlueprint* Blueprint, int32 NumErrors, int32 NumWarnings) const;`
- L271 _public function_ `virtual TSharedPtr<class IClassViewerFilter> GetImportedClassViewerFilter() const override`
- L272 _public prototype_ `virtual void GetPinTypeSelectorFilters(TArray<TSharedPtr<class IPinTypeSelectorFilter>>& OutFilters) const override;`
- L273 _public prototype_ `virtual bool IsNonImportedObject(const UObject* InObject) const;`
- L274 _public prototype_ `virtual bool IsNonImportedObject(const FSoftObjectPath& InObject) const;`
- L278 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L279 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L280 _public prototype_ `virtual TStatId GetStatId() const override;`
- L284 _public prototype_ `FBlueprintEditor();`
- L286 _public prototype_ `virtual ~FBlueprintEditor();`
- L289 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;` — Add context objects for menus and toolbars
- L292 _public prototype_ `bool IsNodeTitleVisible(const UEdGraphNode* Node, bool bRequestRename);` — Check the Node Title is visible
- L295 _public prototype_ `void JumpToNode(const class UEdGraphNode* Node, bool bRequestRename = false);` — Pan the view to center on a particular node
- L298 _public prototype_ `virtual UBlueprint* GetBlueprintObj() const;` — Returns a pointer to the Blueprint object we are currently editing, as long as we are editing exactly one
- L301 _public prototype_ `bool IsEditingSingleBlueprint() const;` — Returns whether the editor is currently editing a single blueprint object
- L304 _public prototype_ `void SetKeyboardFocus();` — Ensures the blueprint has keyboard focus.
- L307 _public function_ `TSharedRef<SKismetInspector> GetInspector() const` — Getters for the various Kismet2 widgets
- L308 _public function_ `TSharedRef<SKismetInspector> GetDefaultEditor() const`
- L309 _public prototype_ `TSharedRef<SBlueprintPalette> GetPalette();`
- L310 _public function_ `TSharedRef<SBlueprintBookmarks> GetBookmarksWidget() const`
- L311 _public function_ `TSharedRef<SWidget> GetCompilerResults() const`
- L312 _public function_ `TSharedRef<SFindInBlueprints> GetFindResults() const`
- L315 _public function_ `TSharedPtr<SSubobjectEditor> GetSubobjectEditor() const` — Getters for the various optional Kismet2 widgets
- L316 _public function_ `TSharedPtr<SSCSEditorViewport> GetSubobjectViewport() const`
- L317 _public function_ `TSharedPtr<SMyBlueprint> GetMyBlueprintWidget() const`
- L318 _public function_ `TSharedPtr<SReplaceNodeReferences> GetReplaceReferencesWidget() const`
- L323 _public prototype_ `AActor* GetPreviewActor() const;` — Provides access to the preview actor.
- L328 _public function_ `FPreviewScene* GetPreviewScene()` — Provides access to the preview scene.
- L339 _public prototype_ `void UpdatePreviewActor(UBlueprint* InBlueprint, bool bInForceFullUpdate = false);` — Creates/updates the preview actor for the given blueprint. @param InBlueprint			The Blueprint to create or update the preview for. @param bInForceFullUpdate	Force a full update to respawn actors.
- L344 _public prototype_ `void DestroyPreview();` — Destroy the Blueprint preview.
- L346 _public function_ `TSharedPtr<class FBlueprintEditorToolbar> GetToolbarBuilder()`
- L349 _public prototype_ `virtual FString GetDocumentationLink() const override;` — @return the documentation location for this editor
- L352 _public prototype_ `bool CanAccessComponentsMode() const;` — Returns whether the edited blueprint has components
- L355 _public prototype_ `bool IsEditorClosing() const;` — Returns if we are currently closing the editor
- L358 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);` — @todo This is a hack for now until we reconcile the default toolbar with application modes
- L360 _public prototype_ `void LogSimpleMessage(const FText& MessageText);` — Throw a simple message into the log
- L363 _public prototype_ `void DumpMessagesToCompilerLog(const TArray<TSharedRef<class FTokenizedMessage>>& Messages, bool bForceMessageDisplay);` — Dumps messages to the compiler log, with an option to force it to display/come to front
- L366 _public prototype_ `bool IsPlayInEditorActive() const;` — Returns true if PIE is active
- L369 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;` — Get the currently selected set of nodes
- L372 _public prototype_ `UEdGraphNode* GetSingleSelectedNode() const;` — Returns the currently selected node if there is a single node selected (if there are multiple nodes selected or none selected, it will return nullptr)
- L375 _public prototype_ `void SaveEditedObjectState();` — Save the current set of edited objects in the LastEditedObjects array so it will be opened next time we open K2
- L378 _public prototype_ `void RestoreEditedObjectState();` — Create new tab for each element of LastEditedObjects array
- L382 _public prototype_ `void RequestSaveEditedObjectState();` — Request a save of the edited object state This is used to delay it by one frame when triggered by a tab being closed, so it can finish closing before remembering the new state
- L385 _public prototype_ `void GetBoundsForNode(const UEdGraphNode* InNode, class FSlateRect& OutRect, float InPadding) const;` — Get the visible bounds of the given graph node
- L388 _public prototype_ `void GetViewBookmark(FGuid& BookmarkId);` — Gets the focused graph current view bookmark ID
- L391 _public prototype_ `void GetViewLocation(FVector2D& Location, float& ZoomAmount);` — Gets the focused graph view location/zoom amount
- L394 _public prototype_ `void SetViewLocation(const FVector2D& Location, float ZoomAmount, const FGuid& BookmarkId = FGuid());` — Sets the focused graph view location/zoom amount
- L397 _public prototype_ `virtual bool IsEditable(UEdGraph* InGraph) const;` — Returns whether a graph is editable or not
- L399 _public prototype_ `bool IsGraphReadOnly(UEdGraph* InGraph) const;` — Determines if the graph is ReadOnly, this differs from editable in that it is never expected to be edited and is in a read-only state
- L402 _public prototype_ `float GetInstructionTextOpacity(UEdGraph* InGraph) const;` — Used to determine the visibility of the graph's instruction text.
- L405 _public prototype_ `virtual bool InEditingMode() const;` — Returns true if in editing mode
- L408 _public prototype_ `virtual bool IsCompilingEnabled() const;` — Returns true if able to compile
- L411 _public prototype_ `bool IsParentClassABlueprint() const;` — Returns true if the parent class of the Blueprint being edited is also a Blueprint
- L414 _public prototype_ `bool IsParentClassAnEditableBlueprint() const;` — Returns true if the parent class of the Blueprint being edited is an editable Blueprint
- L417 _public prototype_ `bool IsParentClassNative() const;` — Returns true if the parent class of the Blueprint being edited is native
- L420 _public prototype_ `virtual bool IsNativeParentClassCodeLinkEnabled() const;` — Returns true if the parent class is native and the link to it's header can be shown
- L423 _public prototype_ `void OnEditParentClassNativeCodeClicked();` — Handles opening the header file of native parent class
- L426 _public prototype_ `FText GetTextForNativeParentClassHeaderLink() const;` — Returns: "(<NativeParentClass>.h)"
- L429 _public prototype_ `EVisibility GetNativeParentClassButtonsVisibility() const;` — Determines visibility of the native parent class manipulation buttons on the menu bar overlay
- L432 _public prototype_ `EVisibility GetParentClassNameVisibility() const;` — Determines visibility of the standard parent class label on the menu bar overlay
- L435 _public prototype_ `FText GetPIEStatus() const;` — Returns our PIE Status - SIMULATING / SERVER / CLIENT
- L444 _public prototype_ `static const FSlateBrush* GetGlyphForGraph(const UEdGraph* Graph, bool bInLargeIcon = false);` — Util for finding a glyph for a graph @param Graph - The graph to evaluate @param bInLargeIcon - if true the icon returned is 22x22 pixels, else it is 16x16 @return An appropriate brush to use to represent the graph, if the graph is an unknown type the function will return the default "function" glyph
- L456 _public prototype_ `static FSlateBrush const* GetVarIconAndColor(const UStruct* VarScope, FName VarName, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut);` — Util for finding a glyph and color for a variable. @param VarScope			Scope to find the variable in @param VarName			Name of variable @param IconColorOut		The resulting color for the glyph @param SecondaryBrushOut The resulting secondary glyph brush (used for Map types) @param SecondaryColorOut The resulting secondary color for the glyph (used for Map types) @return					The resulting glyph brush
- L467 _public prototype_ `static FSlateBrush const* GetVarIconAndColorFromProperty(const FProperty* Property, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut);` — Util for finding a glyph and color for a variable. @param Property       The variable's property @param IconColorOut      The resulting color for the glyph @param SecondaryBrushOut The resulting secondary glyph brush (used for Map types) @param SecondaryColorOut The resulting secondary color for the glyph (used for Map types) @return					The resulting glyph brush
- L478 _public prototype_ `static FSlateBrush const* GetVarIconAndColorFromPinType(const FEdGraphPinType& PinType, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut);` — Util for finding a glyph and color for a variable. @param PinType       The variable's pin type @param IconColorOut      The resulting color for the glyph @param SecondaryBrushOut The resulting secondary glyph brush (used for Map types) @param SecondaryColorOut The resulting secondary color for the glyph (used for Map types) @return					The resulting glyph brush
- L481 _public prototype_ `virtual bool IsInAScriptingMode() const;` — Overridable function for determining if the current mode can script
- L484 _public prototype_ `virtual void Compile();` — Called when Compile button is clicked
- L487 _public prototype_ `bool IsSaveOnCompileEnabled() const;` — Helper functions used to construct/operate-on the "Save on Compile" command
- L490 _public prototype_ `virtual FReply Compile_OnClickWithReply();` — Calls the above function, but returns an FReply::Handled(). Used in SButtons
- L493 _public prototype_ `void RefreshAllNodes_OnClicked();` — Called when the refresh all nodes button is clicked
- L495 _public prototype_ `EVisibility IsDebuggerVisible() const;`
- L497 _public prototype_ `virtual void OnActiveTabChanged(TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated);`
- L500 _public prototype_ `void LogToken_OnClicked(const class IMessageToken& Token);` — Called when a token in a log message is clicked
- L502 _public prototype_ `virtual void FocusInspectorOnGraphSelection(const TSet<class UObject*>& NewSelection, bool bForceRefresh = false);`
- L505 _public prototype_ `void VariableListWasUpdated();` — Variable list window calls this after it is updated
- L508 _public prototype_ `virtual void StartEditingDefaults(bool bAutoFocus = true, bool bForceRefresh = false);` — Virtual override point for editing defaults; allowing more derived editors to edit something else
- L511 _public prototype_ `void SetupViewForBlueprintEditingMode();` — Called by the blueprint editing app mode to focus the appropriate tabs, etc...
- L514 _public prototype_ `void EnsureBlueprintIsUpToDate(UBlueprint* BlueprintObj);` — Ensures the blueprint is up to date
- L517 _public prototype_ `void CommonInitialization(const TArray<UBlueprint*>& InitBlueprints, bool bShouldOpenInDefaultsMode);` — Should be called when initializing any editor built off this foundation
- L520 _public function_ `virtual bool ShouldLoadBPLibrariesFromAssetRegistry()` — Other types of BP editors that don't use BP VM/function libs can choose to not load BP function libraries, for example: Control Rig Blueprints
- L523 _public prototype_ `void PostLayoutBlueprintEditorInitialization();` — Should be called when initializing an editor that has a blueprint, after layout (tab spawning) is done
- L526 _public prototype_ `virtual void OnGraphEditorFocused(const TSharedRef<class SGraphEditor>& InGraphEditor);` — Called when graph editor focus is changed
- L529 _public prototype_ `virtual void OnGraphEditorBackgrounded(const TSharedRef<SGraphEditor>& InGraphEditor);` — Called when the graph editor tab is backgrounded
- L532 _public prototype_ `void EnableSubobjectPreview(bool bEnable);` — Enable/disable the subobject editor preview viewport
- L535 _public prototype_ `void UpdateSubobjectPreview(bool bUpdateNow = false);` — Refresh the preview viewport to reflect changes in the subobject
- L540 _public prototype_ `UObject* GetSubobjectEditorObjectContext() const;` — Delegate invoked when the Subobject editor needs to obtain the object context for editing
- L543 _public prototype_ `virtual void OnSelectionUpdated(const TArray<TSharedPtr<class FSubobjectEditorTreeNode>>& SelectedNodes);` — Delegate invoked when the selection is changed in the subobject editor widget
- L546 _public prototype_ `virtual void OnComponentDoubleClicked(TSharedPtr<class FSubobjectEditorTreeNode> Node);` — Delegate invoked when an item is double clicked in the subobject editor widget
- L549 _public prototype_ `virtual void OnComponentAddedToBlueprint(const FSubobjectData& NewSubobjectData);` — Delegate invoked when a new subobject is added in the subobject editor widget
- L552 _public prototype_ `void SetPinVisibility(SGraphEditor::EPinVisibility Visibility);` — Pin visibility accessors
- L553 _public function_ `bool GetPinVisibility(SGraphEditor::EPinVisibility Visibility) const`
- L556 _public prototype_ `void ReparentBlueprint_Clicked();` — Reparent the current blueprint
- L557 _public prototype_ `virtual bool ReparentBlueprint_IsVisible() const;`
- L558 _public prototype_ `void ReparentBlueprint_NewParentChosen(UClass* ChosenClass);`
- L561 _public prototype_ `void RenameNewlyAddedAction(FName InActionName);` — Utility function to handle all steps required to rename a newly added action
- L564 _public prototype_ `void OnAddNewVariable();` — Adds a new variable to this blueprint
- L565 _public function_ `FReply OnAddNewVariable_OnClick()`
- L568 _public prototype_ `virtual bool CanAddNewLocalVariable() const;` — Checks if adding a local variable is allowed in the focused graph
- L571 _public prototype_ `virtual void OnAddNewLocalVariable();` — Adds a new local variable to the focused function graph
- L574 _public prototype_ `virtual void OnPasteNewLocalVariable(const FBPVariableDescription& VariableDescription);` — Pastes a new local variable to the focused function graph
- L577 _public function_ `virtual void AddNewFunctionVariant(const UEdGraph* InOriginalFunction)` — Create a variant for a function
- L591 _public prototype_ `virtual void NewDocument_OnClicked(ECreatedDocumentType GraphType);` — Called when New Function button is clicked
- L592 _public function_ `FReply NewDocument_OnClick(ECreatedDocumentType GraphType)`
- L595 _public prototype_ `void OnAddNewDelegate();` — Called when New Delegate button is clicked
- L596 _public prototype_ `bool AddNewDelegateIsVisible() const;`
- L599 _public function_ `virtual bool IsSectionVisible(NodeSectionID::Type InSectionID) const` — Called to see if the new document menu items is visible for this type
- L600 _public prototype_ `virtual bool NewDocument_IsVisibleForType(ECreatedDocumentType GraphType) const;`
- L601 _public function_ `EVisibility NewDocument_GetVisibilityForType(ECreatedDocumentType GraphType) const`
- L606 _public member_ `static FName SelectionState_MyBlueprint;`
- L607 _public member_ `static FName SelectionState_Components;`
- L608 _public member_ `static FName SelectionState_Graph;`
- L609 _public member_ `static FName SelectionState_ClassSettings;`
- L610 _public member_ `static FName SelectionState_ClassDefaults;`
- L613 _public function_ `bool& GetIsContextSensitive()` — Gets or sets the flag for context sensitivity in the graph action menu
- L616 _public function_ `FName GetUISelectionState() const` — Gets the UI selection state of this editor
- L617 _public prototype_ `void SetUISelectionState(FName SelectionOwner);`
- L619 _public prototype_ `virtual void ClearSelectionStateFor(FName SelectionOwner);`
- L623 _public prototype_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2D& InPosition, UEdGraph* InGraph) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Please use the version of the function accepting FVector2f.")` — Handles spawning a graph node in the current graph using the passed in chord
- L624 _public prototype_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph);`
- L635 _public prototype_ `void DoPromoteToVariable(UBlueprint* InBlueprint, UEdGraphPin* InTargetPin, bool bInToMemberVariable, const FVector2D* InOptionalLocation = nullptr);` — `UE_DEPRECATED(5.6, "Use the version of this function accepting a TOptional")` — Perform the actual promote to variable action on the given pin in the given blueprint. @param	InBlueprint				The blueprint in which to create the variable. @param	InTargetPin				The pin on which to base the variable. @param	bInToMemberVariable		TRUE if attempting to create a member variable, FALSE if the variable should be local @param   InOptionalLocation		Where the new node should be placed. If null, a fixed offset from the parent node will be used.
- L636 _public prototype_ `void DoPromoteToVariable2f(UBlueprint* InBlueprint, UEdGraphPin* InTargetPin, bool bInToMemberVariable, TOptional<FVector2f> InOptionalLocation = TOptional<FVector2f>());`
- L639 _public prototype_ `void OnNodeSpawnedByKeymap();` — Called when node is spawned by keymap
- L642 _public prototype_ `void UpdateNodeCreationStats(const ENodeCreateAction::Type CreateAction);` — Update Node Creation mechanisms for analytics
- L645 _public prototype_ `void SetDetailsCustomization(TSharedPtr<class FDetailsViewObjectFilter> DetailsObjectFilter, TSharedPtr<class IDetailRootObjectCustomization> DetailsRootCustomization);` — Sets customizations for the BP editor details panel.
- L648 _public prototype_ `void SetSubobjectEditorUICustomization(TSharedPtr<class ISCSEditorUICustomization> InSCSEditorUICustomization);` — Sets subobject editor UI customization
- L655 _public prototype_ `void RegisterSCSEditorCustomization(const FName& InComponentName, TSharedPtr<class ISCSEditorCustomization> InCustomization);` — Register a customization for interacting with the subobject editor @param	InComponentName			The name of the component to customize behavior for @param	InCustomization			The customization instance to use
- L661 _public prototype_ `void UnregisterSCSEditorCustomization(const FName& InComponentName);` — Unregister a previously registered customization for interacting with the subobject editor @param	InComponentName			The name of the component to customize behavior for
- L664 _public prototype_ `void CreateMergeToolTab();` — Forces the merge tool to be shown
- L665 _public prototype_ `void CreateMergeToolTab(const UBlueprint* BaseBlueprint, const UBlueprint* RemoteBlueprint, const FOnMergeResolved& ResolutionCallback);`
- L668 _public prototype_ `void CloseMergeTool();` — Closes the merge tool, rather than simply hiding it
- L671 _public prototype_ `void OnGenerateSearchIndexForDebugging();` — Dumps the current blueprint search index to a JSON file for debugging purposes
- L674 _public prototype_ `void OnDumpCachedIndexDataForBlueprint();` — Dumps the currently-cached index data for the blueprint to a file for debugging
- L681 _public prototype_ `TSharedPtr<class ISCSEditorCustomization> CustomizeSubobjectEditor(const USceneComponent* InComponentToCustomize) const;` — Check to see if we can customize the subobject editor for the passed-in scene component @param	InComponentToCustomize	The component to check to see if a customization exists @return an subobject editor customization instance, if one exists.
- L684 _public function_ `virtual void GetCustomDebugObjects(TArray<FCustomDebugObject>& DebugList) const` — Adds to a list of custom objects for debugging beyond what will automatically be found/used
- L687 _public function_ `virtual bool OnlyShowCustomDebugObjects() const` — If returns true only the custom debug list will be used
- L690 _public function_ `virtual FString GetCustomDebugObjectLabel(UObject* ObjectBeingDebugged) const` — Can be overloaded to customize the labels in the debug filter
- L693 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename
- L696 _public prototype_ `virtual FText GetGraphDecorationString(UEdGraph* InGraph) const;` — Called by a graph title bar to get any extra information the editor would like to display
- L699 _public prototype_ `static FText GetGraphDisplayName(const UEdGraph* Graph);` — Gets the display name of a graph
- L702 _public prototype_ `bool IsGraphInCurrentBlueprint(const UEdGraph* InGraph) const;` — Checks to see if the provided graph is contained within the current blueprint
- L705 _public prototype_ `static FName GetContextFromBlueprintType(EBlueprintType InType);` — Get the context to use from the Blueprint type
- L708 _public prototype_ `void SelectGraphActionItemByName(const FName& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct, int32 SectionId = INDEX_NONE, bool bIsCategory = false);` — Selects an item in "My Blueprint" by name.
- L711 _public function_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject)` — Handle when the debug object is changed in the UI
- L714 _public prototype_ `FBPEditorBookmarkNode* AddBookmark(const FText& DisplayName, const FEditedDocumentInfo& BookmarkInfo, bool bSharedBookmark = false);` — Adds a new bookmark node to the Blueprint that's being edited.
- L717 _public prototype_ `void RenameBookmark(const FGuid& BookmarkNodeId, const FText& NewName);` — Renames the bookmark node with the given ID.
- L720 _public prototype_ `void RemoveBookmark(const FGuid& BookmarkNodeId, bool bRefreshUI = true);` — Removes the bookmark node with the given ID.
- L723 _public function_ `TSubclassOf<UEdGraphSchema> GetDefaultSchema() const` — Gets the default schema for this editor
- L726 _public prototype_ `void ImportNamespace(const FString& InNamespace);` — Imports the given namespace into the editor. This may trigger a load event for additional macro and/or function library assets if not already loaded.
- L749 _public prototype_ `void ImportNamespaceEx(const FImportNamespaceExParameters& InParams);` — Imports a set of namespace(s) into the editor. This may trigger a load event for additional macro and/or function library assets if not already loaded.
- L752 _public prototype_ `void RemoveNamespace(const FString& InNamespace);` — Removes the given namespace from the editor's current import context. However, this will NOT unload any associated macro and/or function library assets.
- L755 _public function_ `virtual bool SelectLocalVariable(const UEdGraph* Graph, const FName& VariableName)` — Selects a local variable to load in the details panel.
- L758 _public prototype_ `void SelectAndDuplicateNode(UEdGraphNode* InNode);` — Duplicates an EdGraphNode using selection and copy / paste functionality
- L763 _protected prototype_ `virtual void InitalizeExtenders();` — Called during initialization of the blueprint editor to register commands and extenders.
- L766 _protected prototype_ `virtual void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false);` — Called during initialization of the blueprint editor to register any application modes.
- L769 _protected prototype_ `void RefreshStandAloneDefaultsEditor();` — Updates the selected object used by the stand lone defaults editor widget.
- L772 _protected prototype_ `void ZoomToWindow_Clicked();` — Zooming to fit the entire graph
- L773 _protected prototype_ `bool CanZoomToWindow() const;`
- L776 _protected prototype_ `void ZoomToSelection_Clicked();` — Zooming to fit the current selection
- L777 _protected prototype_ `bool CanZoomToSelection() const;`
- L780 _protected prototype_ `void NavigateToParentGraph();` — Navigating into/out of graphs
- L781 _protected prototype_ `void NavigateToParentGraphByDoubleClick();`
- L782 _protected prototype_ `bool CanNavigateToParentGraph() const;`
- L783 _protected prototype_ `void NavigateToChildGraph();`
- L784 _protected prototype_ `bool CanNavigateToChildGraph() const;`
- L787 _protected prototype_ `EVisibility GetFindParentClassVisibility() const;` — Determines visibility of the find parent class in content browser button on the menu bar overlay
- L790 _protected prototype_ `EVisibility GetEditParentClassVisibility() const;` — Determines visibility of the edit parent class button on the menu bar overlay
- L793 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;` — Recreates the overlay on the menu bar
- L796 _protected prototype_ `FText GetParentClassNameText() const;` — Returns the name of the Blueprint's parent class
- L799 _protected prototype_ `FText GetParentClassNativeNameText() const;` — Returns the native name of the Blueprint's parent class
- L802 _protected prototype_ `FReply OnFindParentClassInContentBrowserClicked();` — Handler for "Find parent class in CB" button
- L805 _protected prototype_ `FReply OnEditParentClassClicked();` — Handler for "Edit parent class" button
- L808 _protected prototype_ `void FindInBlueprint_Clicked();` — Called to start a quick find (focus the search box in the explorer tab)
- L811 _protected prototype_ `bool IsDetailsPanelEditingGlobalOptions() const;` — Is the main details panel currently showing 'Global options' (e.g., class metadata)?
- L814 _protected prototype_ `void EditGlobalOptions_Clicked();` — Edit the class settings aka Blueprint global options
- L817 _protected prototype_ `bool IsDetailsPanelEditingClassDefaults() const;` — Is the main details panel currently showing 'Class defaults' (Note: Has nothing to do with the standalone class defaults panel)?
- L820 _protected prototype_ `void EditClassDefaults_Clicked();` — Edit the class defaults
- L823 _protected prototype_ `void UndoGraphAction();` — Called to undo the last action
- L826 _protected prototype_ `bool CanUndoGraphAction() const;` — Whether or not we can perform an undo of the last transacted action
- L829 _protected prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L832 _protected prototype_ `bool CanRedoGraphAction() const;` — Whether or not we can redo an undone action
- L835 _protected prototype_ `virtual void OnSelectedNodesChangedImpl(const TSet<class UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L838 _protected function_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)` — Called when the selection changes in the GraphEditor
- L841 _protected prototype_ `void OnGraphEditorDropActor(const TArray< TWeakObjectPtr<AActor> >& Actors, UEdGraph* Graph, const FVector2f& DropLocation);` — Called when an actor is dropped onto the graph editor
- L844 _protected prototype_ `void OnGraphEditorDropStreamingLevel(const TArray< TWeakObjectPtr<ULevelStreaming> >& Levels, UEdGraph* Graph, const FVector2f& DropLocation);` — Called when a streaming level is dropped onto the graph editor
- L848 _protected prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2D& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — `UE_DEPRECATED(5.6, "Please use the version of the function taking FVector2f.")` — Called to create context menu when right-clicking on graph
- L849 _protected prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);`
- L852 _protected prototype_ `void OnGraphActionMenuClosed(bool bActionExecuted, bool bContextSensitiveChecked, bool bGraphPinContext);` — Called from graph context menus when they close to tell the editor why they closed
- L855 _protected prototype_ `virtual void OnBlueprintChangedImpl(UBlueprint* InBlueprint, bool bIsJustBeingCompiled = false);` — Called when the Blueprint we are editing has changed
- L858 _protected function_ `void OnBlueprintChanged(UBlueprint* InBlueprint)` — Called when the Blueprint we are editing has changed, forwards to impl
- L860 _protected prototype_ `void OnBlueprintCompiled(UBlueprint* InBlueprint);`
- L863 _protected prototype_ `void OnBlueprintUnloaded(UBlueprint* InBlueprint);` — Handles the unloading of Blueprints (by closing the editor, if it operating on the Blueprint being unloaded)
- L866 _protected prototype_ `void OnPreObjectPropertyChanged(UObject* InObject, const FEditPropertyChain& EditPropertyChain);` — Called when a property change is about to be propagated to instances of the Blueprint
- L869 _protected prototype_ `void OnPostObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& PropertyChangedEvent);` — Called after a property change has been propagated to instances of the Blueprint
- L874 _protected prototype_ `void ClearAllBreakpoints();` — Deletes all breakpoints for the blueprint being edited
- L877 _protected prototype_ `void DisableAllBreakpoints();` — Disables all breakpoints for the blueprint being edited
- L880 _protected prototype_ `void EnableAllBreakpoints();` — Enables all breakpoints for the blueprint being edited
- L883 _protected prototype_ `void ClearAllWatches();` — Clears all watches associated with the blueprint being edited
- L885 _protected prototype_ `bool HasAnyBreakpoints() const;`
- L886 _protected prototype_ `bool HasAnyEnabledBreakpoints() const;`
- L887 _protected prototype_ `bool HasAnyDisabledBreakpoints() const;`
- L888 _protected prototype_ `bool HasAnyWatches() const;`
- L891 _protected prototype_ `void OpenBlueprintDebugger();` — Spawns a new blueprint debugger tab
- L892 _protected prototype_ `bool CanOpenBlueprintDebugger() const;`
- L895 _protected prototype_ `UEdGraphPin* GetCurrentlySelectedPin() const;` — Utility helper to get the currently hovered pin in the currently visible graph, or nullptr if there isn't one
- L898 _protected prototype_ `void OnPromoteToVariable(bool bInToMemberVariable);` — UI Action functionality
- L899 _protected prototype_ `bool CanPromoteToVariable(bool bInToMemberVariable) const;`
- L901 _protected prototype_ `void OnSplitStructPin();`
- L902 _protected prototype_ `bool CanSplitStructPin() const;`
- L904 _protected prototype_ `void OnRecombineStructPin();`
- L905 _protected prototype_ `bool CanRecombineStructPin() const;`
- L907 _protected prototype_ `void OnAddExecutionPin();`
- L908 _protected prototype_ `bool CanAddExecutionPin() const;`
- L910 _protected prototype_ `void OnInsertExecutionPinBefore();`
- L911 _protected prototype_ `void OnInsertExecutionPinAfter();`
- L912 _protected prototype_ `void OnInsertExecutionPin(EPinInsertPosition Position);`
- L913 _protected prototype_ `bool CanInsertExecutionPin() const;`
- L915 _protected prototype_ `void OnRemoveExecutionPin();`
- L916 _protected prototype_ `bool CanRemoveExecutionPin() const;`
- L918 _protected prototype_ `void OnRemoveThisStructVarPin();`
- L919 _protected prototype_ `bool CanRemoveThisStructVarPin() const;`
- L921 _protected prototype_ `void OnRemoveOtherStructVarPins();`
- L922 _protected prototype_ `bool CanRemoveOtherStructVarPins() const;`
- L924 _protected prototype_ `void OnRestoreAllStructVarPins();`
- L925 _protected prototype_ `bool CanRestoreAllStructVarPins() const;`
- L927 _protected prototype_ `void OnResetPinToDefaultValue();`
- L928 _protected prototype_ `bool CanResetPinToDefaultValue() const;`
- L930 _protected prototype_ `void OnAddOptionPin();`
- L931 _protected prototype_ `bool CanAddOptionPin() const;`
- L933 _protected prototype_ `void OnRemoveOptionPin();`
- L934 _protected prototype_ `bool CanRemoveOptionPin() const;`
- L937 _protected prototype_ `FEdGraphPinType OnGetPinType(UEdGraphPin* SelectedPin) const;` — Functions for handling the changing of the pin's type (PinCategory, PinSubCategory, etc)
- L938 _protected prototype_ `void OnChangePinType();`
- L939 _protected prototype_ `void OnChangePinTypeFinished(const FEdGraphPinType& PinType, UEdGraphPin* SelectedPin);`
- L940 _protected prototype_ `bool CanChangePinType() const;`
- L942 _protected prototype_ `void OnAddParentNode();`
- L943 _protected prototype_ `bool CanAddParentNode() const;`
- L945 _protected prototype_ `void OnCreateMatchingFunction();`
- L946 _protected prototype_ `bool CanCreateMatchingFunction() const;`
- L948 _protected prototype_ `void OnEnableBreakpoint();`
- L949 _protected prototype_ `bool CanEnableBreakpoint() const;`
- L951 _protected prototype_ `void OnToggleBreakpoint();`
- L952 _protected prototype_ `bool CanToggleBreakpoint() const;`
- L954 _protected prototype_ `void OnDisableBreakpoint();`
- L955 _protected prototype_ `bool CanDisableBreakpoint() const;`
- L957 _protected prototype_ `void OnAddBreakpoint();`
- L958 _protected prototype_ `bool CanAddBreakpoint() const;`
- L960 _protected prototype_ `void OnRemoveBreakpoint();`
- L961 _protected prototype_ `bool CanRemoveBreakpoint() const;`
- L963 _protected prototype_ `void OnCollapseNodes();`
- L964 _protected prototype_ `bool CanCollapseNodes() const;`
- L966 _protected prototype_ `void OnCollapseSelectionToFunction();`
- L967 _protected prototype_ `bool CanCollapseSelectionToFunction() const;`
- L969 _protected prototype_ `void OnCollapseSelectionToMacro();`
- L970 _protected prototype_ `bool CanCollapseSelectionToMacro() const;`
- L972 _protected prototype_ `void OnPromoteSelectionToFunction();`
- L973 _protected prototype_ `bool CanPromoteSelectionToFunction() const;`
- L975 _protected prototype_ `void OnPromoteSelectionToMacro();`
- L976 _protected prototype_ `bool CanPromoteSelectionToMacro() const;`
- L978 _protected prototype_ `void OnExpandNodes();`
- L979 _protected prototype_ `bool CanExpandNodes() const;`
- L981 _protected prototype_ `void OnOpenSelectedNodesInNewTab();`
- L982 _protected prototype_ `bool CanOpenSelectedNodesInNewTab() const;`
- L991 _protected prototype_ `void MoveNodesToAveragePos(TSet<UEdGraphNode*>& AverageNodes, FVector2D SourcePos, bool bExpandedNodesNeedUniqueGuid = false) const;` — Move the given set of nodes to an average spot near the Source position @param AverageNodes					The nodes to move @param SourcePos						The source position used to average the nodes around @param bExpandedNodesNeedUniqueGuid	If true then a new Guid will be generated for each node in the set
- L993 _protected prototype_ `void OnConvertFunctionToEvent();`
- L997 _public prototype_ `bool ConvertFunctionIfValid(UK2Node_FunctionEntry* FuncEntryNode);` — Converts the given function entry node to an event if it passes validation
- L1000 _public prototype_ `bool ConvertEventIfValid(UK2Node_Event* EventToConv);` — Converts the given event node to a function graph on this blueprint if it passes validation
- L1007 _protected prototype_ `bool CanConvertFunctionToEvent() const;` — Callback function for the context menu on a node to determine if a function could possibly be converted to an event
- L1015 _protected prototype_ `void ConvertFunctionToEvent(UK2Node_FunctionEntry* SelectedCallFunctionNode);` — Given a function node, move all nodes from the function out of the function graph, create an event with the same function name, and connect nodes to that event. @param SelectedCallFunctionNode	The function node to convert to an event
- L1017 _protected prototype_ `void OnConvertEventToFunction();`
- L1018 _protected prototype_ `void ConvertEventToFunction(UK2Node_Event* SelectedEventNode);`
- L1019 _protected prototype_ `bool CanConvertEventToFunction() const;`
- L1027 _protected prototype_ `TArray<UEdGraphNode*> GetAllConnectedNodes(UEdGraphNode* const Node) const;` — Get all connected nodes and add them to a set of out nodes @param Node		The node to get all connects to @return	TArray of all connected nodes
- L1029 _protected prototype_ `void OnAlignTop();`
- L1030 _protected prototype_ `void OnAlignMiddle();`
- L1031 _protected prototype_ `void OnAlignBottom();`
- L1032 _protected prototype_ `void OnAlignLeft();`
- L1033 _protected prototype_ `void OnAlignCenter();`
- L1034 _protected prototype_ `void OnAlignRight();`
- L1036 _protected prototype_ `void OnStraightenConnections();`
- L1038 _protected prototype_ `void OnDistributeNodesH();`
- L1039 _protected prototype_ `void OnDistributeNodesV();`
- L1041 _protected prototype_ `void OnStackNodesH();`
- L1042 _protected prototype_ `void OnStackNodesV();`
- L1044 _protected prototype_ `void SelectAllNodes();`
- L1045 _protected prototype_ `bool CanSelectAllNodes() const;`
- L1047 _protected prototype_ `virtual void DeleteSelectedNodes();`
- L1048 _protected prototype_ `virtual bool CanDeleteNodes() const;`
- L1056 _protected prototype_ `void ReconnectExecPins(class UK2Node* Node);` — Given a node, make connections from anything connected to it's input pin to anything connected to it's "then" pins. Only works on impure nodes with single exec/then pins. @param Node	The node to reconnect
- L1058 _protected prototype_ `void DeleteSelectedDuplicatableNodes();`
- L1060 _protected prototype_ `virtual void CutSelectedNodes();`
- L1061 _protected prototype_ `virtual bool CanCutNodes() const;`
- L1063 _protected prototype_ `virtual void CopySelectedNodes();`
- L1064 _protected prototype_ `virtual bool CanCopyNodes() const;`
- L1067 _protected prototype_ `virtual void PasteNodesHere(class UEdGraph* DestinationGraph, const FVector2f& GraphLocation) override;` — Paste on graph at specific location
- L1070 _protected prototype_ `virtual void PasteGeneric();` — Paste Variable Definition or Nodes
- L1071 _protected prototype_ `virtual bool CanPasteGeneric() const;`
- L1073 _protected prototype_ `virtual void PasteNodes();`
- L1074 _protected prototype_ `virtual bool CanPasteNodes() const override;`
- L1076 _protected prototype_ `void DuplicateNodes();`
- L1077 _protected prototype_ `bool CanDuplicateNodes() const;`
- L1079 _protected prototype_ `void OnSelectReferenceInLevel();`
- L1080 _protected prototype_ `bool CanSelectReferenceInLevel() const;`
- L1082 _protected prototype_ `void OnAssignReferencedActor();`
- L1083 _protected prototype_ `bool CanAssignReferencedActor() const;`
- L1085 _protected prototype_ `virtual void OnStartWatchingPin();`
- L1086 _protected prototype_ `virtual bool CanStartWatchingPin() const;`
- L1088 _protected prototype_ `virtual void OnStopWatchingPin();`
- L1089 _protected prototype_ `virtual bool CanStopWatchingPin() const;`
- L1091 _protected prototype_ `void ToggleSaveIntermediateBuildProducts();`
- L1092 _protected prototype_ `bool GetSaveIntermediateBuildProducts() const;`
- L1094 _protected prototype_ `void OnListObjectsReferencedByClass();`
- L1095 _protected prototype_ `void OnListObjectsReferencedByBlueprint();`
- L1096 _protected prototype_ `void OnRepairCorruptedBlueprint();`
- L1098 _protected prototype_ `void OnNodeDoubleClicked(UEdGraphNode* Node);`
- L1100 _protected prototype_ `virtual void OnEditTabClosed(TSharedRef<SDockTab> Tab);`
- L1102 _protected prototype_ `virtual bool GetBoundsForSelectedNodes(class FSlateRect& Rect, float Padding) override;`
- L1113 _protected prototype_ `void ExtractEventTemplateForFunction(class UK2Node_CustomEvent* InCustomEvent, UEdGraphNode* InGatewayNode, class UK2Node_EditablePinBase* InEntryNode, class UK2Node_EditablePinBase* InResultNode, TSet<UEdGraphNode*>& InCollapsableNodes);` — Pulls out the pins to use as a template when collapsing a selection to a function with a custom event involved. @param InCustomEvent				The custom event used as a template @param InGatewayNode				The node replacing the selection of nodes @param InEntryNode				The entry node in the graph @param InResultNode				The result node in the graph @param InCollapsableNodes		The selection of nodes being collapsed
- L1125 _protected prototype_ `void CollapseNodesIntoGraph(UEdGraphNode* InGatewayNode, class UK2Node_EditablePinBase* InEntryNode, class UK2Node_EditablePinBase* InResultNode, UEdGraph* InSourceGraph, UEdGraph* InDestinationGraph, TSet<UEdGraphNode*>& InCollapsableNodes, bool bCanDiscardEmptyReturnNode, bool bCanHaveWeakObjPtrParam);` — Collapses a selection of nodes into a graph for composite, function, or macro nodes. @param InGatewayNode				The node replacing the selection of nodes @param InEntryNode				The entry node in the graph @param InResultNode				The result node in the graph @param InSourceGraph				The graph the selection is from @param InDestinationGraph		The destination graph to move the selected nodes to @param InCollapsableNodes		The selection of nodes being collapsed
- L1128 _protected prototype_ `void CollapseNodes(TSet<class UEdGraphNode*>& InCollapsableNodes);` — Called when a selection of nodes are being collapsed into a sub-graph
- L1131 _protected prototype_ `UEdGraph* CollapseSelectionToFunction(TSharedPtr<SGraphEditor> InRootGraph, TSet<class UEdGraphNode*>& InCollapsableNodes, UEdGraphNode*& OutFunctionNode);` — Called when a selection of nodes are being collapsed into a function
- L1134 _protected prototype_ `UEdGraph* CollapseSelectionToMacro(TSharedPtr<SGraphEditor> InRootGraph, TSet<class UEdGraphNode*>& InCollapsableNodes, UEdGraphNode*& OutMacroNode);` — Called when a selection of nodes are being collapsed into a macro
- L1143 _protected prototype_ `bool CanCollapseSelectionToFunction(TSet<class UEdGraphNode*>& InSelection) const;` — Called when a selection of nodes is being collapsed into a function @param InSelection		The selection to check @return					Returns TRUE if the selection can be promoted to a function
- L1152 _protected prototype_ `bool CanCollapseSelectionToMacro(TSet<class UEdGraphNode*>& InSelection) const;` — Called when a selection of nodes is being collapsed into a macro @param InSelection		The selection to check @return					Returns TRUE if the selection can be promoted to a macro
- L1156 _protected prototype_ `static void ExpandNode(UEdGraphNode* InNodeToExpand, UEdGraph* InSourceGraph, TSet<UEdGraphNode*>& OutExpandedNodes);` — Expands passed in node
- L1169 _protected prototype_ `static void MoveNodesToGraph(TArray<UEdGraphNode*>& SourceNodes, UEdGraph* DestinationGraph, TSet<UEdGraphNode*>& OutExpandedNodes, UEdGraphNode** OutEntry, UEdGraphNode** OutResult, const bool bIsCollapsedGraph = false);` — Move every node from the source graph to the destination graph. Add Each node that is moved to the OutExpandedNodes set. If the source graph is a function graph, keep track of the entry and result nodes in the given Out Parameters. @param SourceNodes		Nodes to move @param DestinationGraph	Graph to move nodes to @param OutExpandedNodes	Set of each node that was moved from the source to destination graph @param OutEntry			Pointer to the function entry node @param OutResult			Pointer to the function result node @param bIsCollapsedGraph	Whether or not the source graph is collapsed
- L1172 _protected prototype_ `void OnStartEditingDefaultsClicked();` — Start editing the defaults for this blueprint
- L1175 _protected prototype_ `virtual void CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints);` — Creates the widgets that go into the tabs (note: does not create the tabs themselves)
- L1178 _protected prototype_ `virtual void CreateDefaultCommands();` — Create Default Commands
- L1181 _protected prototype_ `void DeleteUnusedVariables_OnClicked();` — Called when DeleteUnusedVariables button is clicked
- L1184 _protected prototype_ `void FindInBlueprints_OnClicked();` — Called when Find In Blueprints menu is opened is clicked
- L1187 _protected prototype_ `virtual void NotifyPreChange( FProperty* PropertyAboutToChange ) override;`
- L1188 _protected prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L1192 _protected prototype_ `bool ShouldShowPublicViewControl() const;` — Callback to determine visibility of the public view checkbox in the Defaults editor
- L1195 _protected prototype_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Callback when properties have finished being handled
- L1198 _protected prototype_ `void OnRenameNode();` — On starting to rename node
- L1199 _protected prototype_ `bool CanRenameNodes() const;`
- L1202 _protected prototype_ `bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);` — Called when a node's title is being committed for a rename so it can be verified
- L1205 _protected prototype_ `void LoadLibrariesFromAssetRegistry();` — Load macro & function blueprint libraries from asset registry
- L1208 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L1209 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L1213 _protected prototype_ `virtual void SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents);` — Setup all the events that the graph editor can handle
- L1216 _protected prototype_ `FGraphAppearanceInfo GetCurrentGraphAppearance() const;` — Get the graph appearance of the currently focused graph
- L1219 _protected prototype_ `virtual FGraphAppearanceInfo GetGraphAppearance(class UEdGraph* InGraph) const;` — Get the graph appearance of a specific graph, GetCurrentGraphAppearance() uses the currently focused graph.
- L1222 _protected prototype_ `virtual TSubclassOf<UEdGraphSchema> GetDefaultSchemaClass() const;` — Whenever new graphs need to be created it will use this schema by default.
- L1225 _protected prototype_ `void TryInvokingDetailsTab(bool bFlash = true);` — Attempts to invoke the details tab if it's currently possible to.
- L1228 _protected prototype_ `void OnGraphEditorQuickJump(int32 BookmarkIndex);` — Handles activation of a graph editor "quick jump" command
- L1231 _protected prototype_ `void SetGraphEditorQuickJump(int32 BookmarkIndex);` — Binds a graph editor "quick jump" to the command at the given index
- L1234 _protected prototype_ `void ClearGraphEditorQuickJump(int32 BookmarkIndex);` — Unbinds a graph editor "quick jump" from the command at the given index
- L1237 _protected prototype_ `void ClearAllGraphEditorQuickJumps();` — Unbinds all graph editor "quick jump" commands
- L1240 _protected prototype_ `TSharedRef<SWidget> CreateGraphTitleBarWidget(TSharedRef<FTabInfo> InTabInfo, UEdGraph* InGraph);` — Create a graph title bar widget
- L1245 _private prototype_ `static bool CanRecompileModules();` — Returns true if modules can be recompiled
- L1248 _private prototype_ `void OnEditTunnel();` — User wants to edit tunnel via function editor
- L1253 _protected prototype_ `virtual void OnCreateComment();` — Create comment node on graph
- L1256 _protected prototype_ `virtual void OnCreateCustomEvent();` — Create custom event node on graph
- L1259 _protected prototype_ `virtual TSharedRef<SGraphEditor> CreateGraphEditorWidget(TSharedRef<class FTabInfo> InTabInfo, class UEdGraph* InGraph);` — Create new graph editor widget for the supplied document container
- L1264 _private prototype_ `void OnChangeBreadCrumbGraph( class UEdGraph* InGraph);` — Helper to move focused graph when clicking on graph breadcrumb
- L1267 _private prototype_ `static bool IsASubGraph( const class UEdGraph* GraphPtr );` — Function to check whether the give graph is a subgraph
- L1270 _private prototype_ `void CreateSubobjectEditors();` — Creates the Subobject Editor tree component view and the Subobject Viewport.
- L1273 _private prototype_ `void OnLogTokenClicked(const TSharedRef<class IMessageToken>& Token);` — Callback when a token is clicked on in the compiler results log
- L1276 _private prototype_ `void NavigateTab(FDocumentTracker::EOpenDocumentCause InCause);` — Helper function to navigate the current tab
- L1279 _private prototype_ `void OnFindReferences(bool bSearchAllBlueprints, const EGetFindReferenceSearchStringFlags Flags);` — Find all references of the selected node.
- L1282 _private prototype_ `bool CanFindReferences();` — Checks if we can currently find all references of the node selection.
- L1285 _private prototype_ `void OnDisallowedPinConnection(const class UEdGraphPin* PinA, const class UEdGraphPin* PinB);` — Called when the user generates a warning tooltip because a connection was invalid
- L1292 _private prototype_ `bool IsEditingAnimGraph() const;` — Checks to see if the focused Graph-Editor is focused on a animation graph or not. @return True if GraphEdPtr's current graph is an animation graph, false if not.
- L1295 _private prototype_ `bool IsFocusedGraphEditable() const;` — Returns whether the currently focused graph is editable or not
- L1298 _private prototype_ `void OnGoToDefinition();` — Called when the user wants to jump to a node's definition
- L1301 _private prototype_ `bool CanGoToDefinition() const;` — Checks to see if it is possible to jump to the selected node's definition.
- L1304 _private prototype_ `void OnGoToDocumentation();` — Open documentation for the selected node class
- L1307 _private prototype_ `bool CanGoToDocumentation();` — Can we open documentation for the selected node
- L1310 _private prototype_ `FString GetDocLinkForSelectedNode();` — Util to try and get doc link for the currently selected node
- L1313 _private prototype_ `FString GetDocLinkBaseUrlForSelectedNode();` — Util to try and get the base URL for the doc link for the currently selected node
- L1316 _private prototype_ `void OnSetEnabledStateForSelectedNodes(ENodeEnabledState NewState);` — Set the enabled state for currently-selected nodes
- L1319 _private prototype_ `ECheckBoxState GetEnabledCheckBoxStateForSelectedNodes();` — Returns the appropriate check box state representing whether or not the selected nodes are enabled
- L1324 _private prototype_ `virtual void LoadEditorSettings();` — Load editor settings from disk (docking state, window pos/size, option state, etc).
- L1329 _private prototype_ `virtual void SaveEditorSettings();` — Saves editor settings to disk (docking state, window pos/size, option state, etc).
- L1332 _private prototype_ `ECheckBoxState CheckEnabledStateForSelectedNodes(ENodeEnabledState CheckState);` — Attempt to match the given enabled state for currently-selected nodes
- L1335 _private prototype_ `void HandleUndoTransaction(const class FTransaction* Transaction);` — Handle undo/redo
- L1339 _public prototype_ `virtual bool TransactionObjectAffectsBlueprint(UObject* InTransactedObject);`
- L1341 _public member_ `TSharedPtr<FDocumentTracker> DocumentManager;`
- L1344 _public prototype_ `void UpdateNodesUnrelatedStatesAfterGraphChange();` — Update all nodes' unrelated states when the graph has changed
- L1347 _public prototype_ `virtual bool AreEventGraphsAllowed() const;` — Whether event graphs are allowed to be displayed/created in a blueprint
- L1350 _public prototype_ `virtual bool AreMacrosAllowed() const;` — Whether macros are allowed  to be displayed/created in a blueprint
- L1353 _public prototype_ `virtual bool AreDelegatesAllowed() const;` — Whether delegates are allowed  to be displayed/created in a blueprint
- L1355 _public prototype_ `FEditorViewportSelectabilityBridge* GetViewportSelectabilityBridge();`
- L1360 _protected member_ `bool bSaveIntermediateBuildProducts;` — Should intermediate build products be saved when recompiling?
- L1363 _protected member_ `bool bIsReparentingBlueprint;` — True if the current blueprint is in the process of being reparented
- L1366 _protected member_ `bool bPendingDeferredClose;` — Flags if this blueprint editor should close on its next tick.
- L1369 _protected member_ `TWeakPtr<class SGraphEditor> FocusedGraphEdPtr;` — Currently focused graph editor
- L1372 _protected member_ `TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;` — Factory that spawns graph editors; used to look up all tabs spawned by it.
- L1375 _protected member_ `TSet<TWeakObjectPtr<UUserDefinedEnum>> UserDefinedEnumerators;` — User-defined enumerators to keep loaded
- L1378 _protected member_ `TSet<TWeakObjectPtr<UUserDefinedStruct>> UserDefinedStructures;` — User-defined structures to keep loaded
- L1381 _protected member_ `TArray<TObjectPtr<UBlueprint>> StandardLibraries;` — Macro/function libraries to keep loaded
- L1384 _protected member_ `TSharedPtr<SSubobjectEditor> SubobjectEditor;` — Subobject Editor
- L1387 _protected member_ `TSharedPtr<SSCSEditorViewport> SubobjectViewport;` — Viewport widget
- L1390 _protected member_ `TSharedPtr<class SKismetInspector> Inspector;` — Node inspector widget
- L1393 _protected member_ `TSharedPtr<class SKismetInspector> DefaultEditor;` — defaults inspector widget
- L1396 _protected member_ `TSharedPtr<class SBlueprintPalette> Palette;` — Palette of all classes with funcs/vars
- L1399 _protected member_ `TSharedPtr<class SBlueprintBookmarks> BookmarksWidget;` — Blueprint bookmark editing widget
- L1402 _protected member_ `TSharedPtr<class SMyBlueprint> MyBlueprintWidget;` — All of this blueprints' functions and variables
- L1405 _protected member_ `TSharedPtr<class SReplaceNodeReferences> ReplaceReferencesWidget;` — Widget for replacing node references
- L1408 _protected member_ `TSharedPtr<class SWidget> CompilerResults;` — Compiler results log, with the log listing that it reflects
- L1409 _protected member_ `TSharedPtr<class IMessageLogListing> CompilerResultsListing;`
- L1412 _protected member_ `int32 CachedNumWarnings;` — Limited cache of last compile results
- L1413 _protected member_ `int32 CachedNumErrors;`
- L1416 _protected member_ `TSharedPtr<class SFindInBlueprints> FindResults;` — Find results log as well as the search filter
- L1419 _protected member_ `TWeakPtr<class SDockTab> MergeTool;` — Merge tool - WeakPtr because it's owned by the GlobalTabManager
- L1421 _protected member_ `FOnMergeResolved OnMergeResolved;` — Merge tool - Delegate to call when the merge tool is closed.
- L1424 _protected member_ `TWeakPtr<class SWindow> NameEntryPopupWindow;` — Reference to owner of the current popup
- L1427 _protected member_ `TSharedPtr<class INameValidatorInterface> NameEntryValidator;` — Reference to helper object to validate names in popup
- L1430 _protected member_ `TWeakPtr<class IMenu> PinTypeChangeMenu;` — Reference to owner of the pin type change popup
- L1433 _protected member_ `TSharedPtr<class FBlueprintEditorToolbar> Toolbar;` — The toolbar builder class
- L1436 _protected member_ `TSharedPtr<FBlueprintNamespaceHelper> ImportedNamespaceHelper;` — Imported namespace helper utility object
- L1439 _protected member_ `TSharedPtr<class IClassViewerFilter> ImportedClassViewerFilter;` — Filter used to restrict class viewer widgets in the editor context to imported namespaces only
- L1442 _protected member_ `TSharedPtr<class IPinTypeSelectorFilter> ImportedPinTypeSelectorFilter;` — Filter used to restrict pin type selector widgets in the editor context to imported namespaces only
- L1445 _protected member_ `TSharedPtr<class IPinTypeSelectorFilter> PermissionsPinTypeSelectorFilter;` — Filter used to restrict pin type selector widgets to those which permissions allow
- L1448 _protected member_ `TSharedPtr<class IPinTypeSelectorFilter> CompositePinTypeSelectorFilter;` — Filter used to compose multiple pin type filters together
- L1451 _protected member_ `TSet<FString> DeferredNamespaceImports;` — Pending set of namespaces to be auto-imported on the next tick
- L1453 _protected member_ `FOnSetPinVisibility OnSetPinVisibility;`
- L1456 _protected member_ `bool bRequestedSavingOpenDocumentState;` — Has someone requested a deferred update of the saved document state?
- L1459 _protected member_ `bool bBlueprintModifiedOnOpen;` — Did we update the blueprint when it opened
- L1462 _protected member_ `SGraphEditor::EPinVisibility PinVisibility;` — Whether to hide unused pins or not
- L1465 _protected member_ `bool bIsActionMenuContextSensitive;` — Whether the graph action menu should be sensitive to the pins dragged off of
- L1468 _protected member_ `FName CurrentUISelection;` — The current UI selection state of this editor
- L1471 _protected member_ `bool bEditorMarkedAsClosed;` — Whether we are already in the process of closing this editor
- L1474 _protected member_ `FPreviewScene PreviewScene;` — Blueprint preview scene
- L1477 _protected member_ `mutable TWeakObjectPtr<AActor> PreviewActorPtr;` — The preview actor representing the current preview
- L1480 _protected member_ `bool bHideUnrelatedNodes;` — If true, fade out nodes which are unrelated to the selected nodes automatically.
- L1483 _protected member_ `bool bLockNodeFadeState;` — Lock the current fade state of each node
- L1486 _protected member_ `bool bSelectRegularNode;` — If a regular node (not a comment node) has been selected
- L1489 _protected member_ `bool bWasOpenedInDefaultsMode;` — True if the editor was opened in defaults mode
- L1492 _protected prototype_ `void ResetAllNodesUnrelatedStates();` — Focus nodes which are related to the selected nodes
- L1493 _protected prototype_ `void CollectExecUpstreamNodes(UEdGraphNode* CurrentNode, TArray<UEdGraphNode*>& CollectedNodes);`
- L1494 _protected prototype_ `void CollectExecDownstreamNodes(UEdGraphNode* CurrentNode, TArray<UEdGraphNode*>& CollectedNodes);`
- L1495 _protected prototype_ `void CollectPureDownstreamNodes(UEdGraphNode* CurrentNode, TArray<UEdGraphNode*>& CollectedNodes);`
- L1496 _protected prototype_ `void CollectPureUpstreamNodes(UEdGraphNode* CurrentNode, TArray<UEdGraphNode*>& CollectedNodes);`
- L1497 _protected prototype_ `void HideUnrelatedNodes();`
- L1500 _protected prototype_ `void RegisterMenus();` — Register Menus
- L1504 _public prototype_ `virtual void ToggleHideUnrelatedNodes();` — Make nodes which are unrelated to the selected nodes fade out
- L1505 _public prototype_ `virtual bool IsToggleHideUnrelatedNodesChecked() const;`
- L1508 _public prototype_ `TSharedRef<SWidget> MakeHideUnrelatedNodesOptionsMenu();` — Make a drop down menu to control the opacity of unrelated nodes
- L1509 _public prototype_ `TOptional<float> HandleUnrelatedNodesOpacityBoxValue() const;`
- L1510 _public prototype_ `void HandleUnrelatedNodesOpacityBoxChanged(float NewOpacity);`
- L1511 _public prototype_ `void OnLockNodeStateCheckStateChanged(ECheckBoxState NewCheckedState);`
- L1516 _public prototype_ `TSharedPtr<SDockTab> OpenDocument(const UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause);` — @TODO: To be moved/merged
- L1519 _public prototype_ `void CloseDocumentTab(const UObject* DocumentID);` — Finds the tab associated with the specified asset, and closes if it is open
- L1522 _public prototype_ `bool FindOpenTabsContainingDocument(const UObject* DocumentID, TArray< TSharedPtr<SDockTab> >& Results);` — Finds any open tabs containing the specified document and adds them to the specified array; returns true if at least one is found
- L1526 _public prototype_ `DECLARE_EVENT ( FBlueprintEditor, FOnRefreshEvent );` — Broadcasts a notification whenever the editor needs associated controls to refresh
- L1527 _public function_ `FOnRefreshEvent& OnRefresh()`
- L1532 _public function_ `virtual bool OnActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const` — function used by the SMyBlueprint to determine if an action matches a name. This happens during selection of a custom action ( a graph, a variable etc )
- L1536 _private member_ `FOnRefreshEvent RefreshEvent;` — Notification used whenever the editor wants associated controls to refresh.
- L1539 _private function_ `void BroadcastRefresh()` — Broadcast notification for associated controls to update
- L1542 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for the graph editor
- L1572 _private member_ `FAnalyticsStatistics AnalyticsStats;` — analytics statistics for the Editor
- L1575 _private member_ `TSharedPtr<ISCSEditorUICustomization> SCSEditorUICustomization;` — UI customizations for the SCS editor inside the blueprint editor
- L1578 _private member_ `TMap<FName, TSharedPtr<ISCSEditorCustomization>> SubobjectEditorCustomizations;` — Customizations for the Subobject editor
- L1581 _private member_ `bool bCodeBasedProject;` — Whether the current project is C++ or blueprint based
- L1584 _private member_ `FOnModeSet OnModeSetData;` — Delegates that are fired when the blueprint editor changes modes
- L1587 _private member_ `UEdGraph* HasOpenActionMenu;` — When set, flags which graph has a action menu currently open (if null, no graphs do).
- L1589 _private member_ `float InstructionsFadeCountdown;` — Used to nicely fade instruction text, when the context menu is opened.
- L1592 _private member_ `FDelegateHandle OnActiveTabChangedDelegateHandle;` — Handle to the registered OnActiveTabChanged delegate
- L1595 _private member_ `FDelegateHandle BlueprintEditorSettingsChangedHandle;` — Delegate handle registered for when settings change
- L1596 _private member_ `FDelegateHandle BlueprintProjectSettingsChangedHandle;`
- L1605 _private member_ `mutable ESafeToModifyDuringPIEStatus ModifyDuringPIEStatus = ESafeToModifyDuringPIEStatus::Unknown;`
- L1608 _private function_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList)` — Allow derived editors to add command mappings
- L1610 _private prototype_ `virtual void OnBlueprintProjectSettingsChanged(UObject*, struct FPropertyChangedEvent&);`
- L1611 _private prototype_ `virtual void OnBlueprintEditorPreferencesChanged(UObject*, struct FPropertyChangedEvent&);`
- L1613 _private member_ `TUniquePtr<FEditorViewportSelectabilityBridge> ViewportSelectabilityBridge;`

#### struct `FBlueprintEditor::FDisallowedPinConnection`  
`struct FDisallowedPinConnection`  
_L195-207_
- desc: A record of a warning generated by a disallowed pin connection attempt
- L197 _public member_ `FName PinTypeCategoryA;`
- L198 _public member_ `FName PinTypeCategoryB;`
- L200 _public member_ `uint8 bPinIsArrayA:1;`
- L201 _public member_ `uint8 bPinIsReferenceA:1;`
- L202 _public member_ `uint8 bPinIsWeakPointerA:1;`
- L204 _public member_ `uint8 bPinIsArrayB:1;`
- L205 _public member_ `uint8 bPinIsReferenceB:1;`
- L206 _public member_ `uint8 bPinIsWeakPointerB:1;`

#### enum `FBlueprintEditor::ECreatedDocumentType`  
`enum ECreatedDocumentType`  
_L580-588_
- desc: Type of new document/graph being created by a menu item
- L582 _public enumerator_ `CGT_NewVariable`
- L583 _public enumerator_ `CGT_NewFunctionGraph`
- L584 _public enumerator_ `CGT_NewMacroGraph`
- L585 _public enumerator_ `CGT_NewAnimationLayer`
- L586 _public enumerator_ `CGT_NewEventGraph`
- L587 _public enumerator_ `CGT_NewLocalVariable`

#### struct `FBlueprintEditor::FImportNamespaceExParameters`  
`struct FImportNamespaceExParameters`  
_L729-746_
- desc: Parameters for the extended ImportNamespaceEx() method
- L732 _public member_ `bool bIsAutoImport;` — Whether this is an automatic or explicit (i.e. user-initiated) action.
- L735 _public member_ `FSimpleDelegate OnPostImportCallback;` — Callback to use for any post-import actions. Will not be invoked if nothing is imported.
- L738 _public member_ `TSet<FString> NamespacesToImport;` — One or more unique namespace identifiers to be imported as part of the single transaction.
- L741 _public function_ `FImportNamespaceExParameters()` — Default ctor (for initialization).

#### struct `FBlueprintEditor::FAnalyticsStatistics`  
`struct FAnalyticsStatistics`  
_L1545-1569_
- desc: Structure to contain editor usage analytics
- L1548 _public member_ `int32 GraphActionMenusNonCtxtSensitiveExecCount;` — Stats collected about graph action menu usage
- L1549 _public member_ `int32 GraphActionMenusCtxtSensitiveExecCount;`
- L1550 _public member_ `int32 GraphActionMenusCancelledCount;`
- L1553 _public member_ `int32 MyBlueprintNodeDragPlacementCount;` — Stats collection about user node creation actions
- L1554 _public member_ `int32 PaletteNodeDragPlacementCount;`
- L1555 _public member_ `int32 NodeGraphContextCreateCount;`
- L1556 _public member_ `int32 NodePinContextCreateCount;`
- L1557 _public member_ `int32 NodeKeymapCreateCount;`
- L1558 _public member_ `int32 NodePasteCreateCount;`
- L1568 _public member_ `TArray<FDisallowedPinConnection> GraphDisallowedPinConnections;` — Stats collected about warning tooltips

#### struct `FBlueprintEditor::FAnalyticsStatistics::FNodeDetails`  
`struct FNodeDetails`  
_L1561-1565_
- desc: New node instance information
- L1563 _public member_ `FName NodeClass;`
- L1564 _public member_ `int32 Instances;`

#### enum `FBlueprintEditor::ESafeToModifyDuringPIEStatus`  
`enum class ESafeToModifyDuringPIEStatus`  
_L1598-1603_
- L1600 _public enumerator_ `Unknown`
- L1601 _public enumerator_ `Safe`
- L1602 _public enumerator_ `NotSafe`

#### Free symbols / members of external scopes

- L59 _macro_ `#define UE_API KISMET_API`
- L138 _macro_ `#define LOCTEXT_NAMESPACE "BlueprintEditor"`
- L167 _delegate_ `DECLARE_DELEGATE_OneParam(FGetSelectedObjectsDelegate, TArray<FComponentEventConstructionData>&);` — The delegate that the caller must supply to BuildComponentActionsSubMenu that returns the currently selected items
- L167 _prototype_ `DECLARE_DELEGATE_OneParam(FGetSelectedObjectsDelegate, TArray<FComponentEventConstructionData>&);` — The delegate that the caller must supply to BuildComponentActionsSubMenu that returns the currently selected items
- L170 _delegate_ `DECLARE_DELEGATE(FNodeCreationAnalytic);` — Delegate for Node Creation Analytics
- L170 _prototype_ `DECLARE_DELEGATE(FNodeCreationAnalytic);` — Delegate for Node Creation Analytics
- L173 _namespace_ `namespace ENodeCreateAction`
- L192 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetPinVisibility, SGraphEditor::EPinVisibility);`
- L214 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeSet, FName);`
- L1526 _delegate_ `DECLARE_EVENT ( FBlueprintEditor, FOnRefreshEvent );` — Broadcasts a notification whenever the editor needs associated controls to refresh

### `Source/Editor/Kismet/Public/BlueprintEditorContext.h` (Public)


#### class `UBlueprintEditorToolMenuContext`  
`class UBlueprintEditorToolMenuContext : public UObject`  
_L15-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `UBlueprint* GetBlueprintObj() const;` — `UFUNCTION(BlueprintCallable, Category="Tool Menus")`
- L23 _public member_ `TWeakPtr<FBlueprintEditor> BlueprintEditor;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintEditorModes.h` (Public)


#### struct `FBlueprintEditorApplicationModes`  
`struct FBlueprintEditorApplicationModes`  
_L26-54_
- L29 _public member_ `static const FName StandardBlueprintEditorMode;` — Mode identifiers
- L30 _public member_ `static const FName BlueprintDefaultsMode;`
- L31 _public member_ `static const FName BlueprintComponentsMode;`
- L32 _public member_ `static const FName BlueprintInterfaceMode;`
- L33 _public member_ `static const FName BlueprintMacroMode;`
- L34 _public function_ `static FText GetLocalizedMode( const FName InMode )`
- L53 _private function_ `FBlueprintEditorApplicationModes()`

#### class `FBlueprintEditorApplicationMode`  
`class FBlueprintEditorApplicationMode : public FApplicationMode`  
_L58-79_
- inherits: `FApplicationMode`
- L61 _public prototype_ `FBlueprintEditorApplicationMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = true, const bool bRegisterDefaultsTab = true);`
- L63 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L64 _public prototype_ `virtual void PreDeactivateMode() override;`
- L65 _public prototype_ `virtual void PostActivateMode() override;`
- L69 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L72 _protected member_ `FWorkflowAllowedTabSet BlueprintEditorTabFactories;` — Set of spawnable tabs in blueprint editing mode
- L75 _protected member_ `FWorkflowAllowedTabSet CoreTabFactories;` — Set of spawnable tabs useful in derived classes, even without a blueprint
- L78 _protected member_ `FWorkflowAllowedTabSet BlueprintEditorOnlyTabFactories;` — Set of spawnable tabs only usable in blueprint editing mode (not useful in Persona, etc...)

#### class `FBlueprintDefaultsApplicationMode`  
`class FBlueprintDefaultsApplicationMode : public FApplicationMode`  
_L82-96_
- inherits: `FApplicationMode`
- L85 _public prototype_ `FBlueprintDefaultsApplicationMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor);`
- L87 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L88 _public prototype_ `virtual void PostActivateMode() override;`
- L92 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L95 _protected member_ `FWorkflowAllowedTabSet BlueprintDefaultsTabFactories;` — Set of spawnable tabs in Class Defaults mode

#### class `FBlueprintComponentsApplicationMode`  
`class FBlueprintComponentsApplicationMode : public FApplicationMode`  
_L99-117_
- inherits: `FApplicationMode`
- L102 _public prototype_ `FBlueprintComponentsApplicationMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor);`
- L104 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L105 _public prototype_ `virtual void PreDeactivateMode() override;`
- L106 _public prototype_ `virtual void PostActivateMode() override;`
- L108 _public function_ `TSharedPtr<FBlueprintEditor> GetBlueprintEditor() const`
- L109 _public prototype_ `AActor* GetPreviewActor() const;`
- L111 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L114 _protected member_ `FWorkflowAllowedTabSet BlueprintComponentsTabFactories;` — Set of spawnable tabs in this mode
- L116 _protected member_ `TArray<TWeakObjectPtr<const UActorComponent>> CachedComponentSelection;`

#### class `FBlueprintInterfaceApplicationMode`  
`class FBlueprintInterfaceApplicationMode : public FApplicationMode`  
_L119-134_
- inherits: `FApplicationMode`
- L122 _public prototype_ `FBlueprintInterfaceApplicationMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor, FName InModeName = FBlueprintEditorApplicationModes::BlueprintInterfaceMode, FText(*GetLocalizedMode)(const FName) = FBlueprintEditorApplicationModes::GetLocalizedMode);`
- L124 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L125 _public prototype_ `virtual void PreDeactivateMode() override;`
- L126 _public prototype_ `virtual void PostActivateMode() override;`
- L130 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L133 _protected member_ `FWorkflowAllowedTabSet BlueprintInterfaceTabFactories;` — Set of spawnable tabs in this mode

#### class `FBlueprintMacroApplicationMode`  
`class FBlueprintMacroApplicationMode : public FApplicationMode`  
_L136-151_
- inherits: `FApplicationMode`
- L139 _public prototype_ `FBlueprintMacroApplicationMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor);`
- L141 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L142 _public prototype_ `virtual void PreDeactivateMode() override;`
- L143 _public prototype_ `virtual void PostActivateMode() override;`
- L147 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L150 _protected member_ `FWorkflowAllowedTabSet BlueprintMacroTabFactories;` — Set of spawnable tabs in this mode

#### class `FBlueprintEditorUnifiedMode`  
`class FBlueprintEditorUnifiedMode : public FApplicationMode`  
_L153-174_
- inherits: `FApplicationMode`
- L156 _public prototype_ `FBlueprintEditorUnifiedMode(TSharedPtr<class FBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)( const FName ), const bool bRegisterViewport = true);`
- L158 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L159 _public prototype_ `virtual void PreDeactivateMode() override;`
- L160 _public prototype_ `virtual void PostActivateMode() override;`
- L164 _protected member_ `TWeakPtr<FBlueprintEditor> MyBlueprintEditor;`
- L167 _protected member_ `FWorkflowAllowedTabSet BlueprintEditorTabFactories;` — Set of spawnable tabs in blueprint editing mode
- L170 _protected member_ `FWorkflowAllowedTabSet CoreTabFactories;` — Set of spawnable tabs useful in derived classes, even without a blueprint
- L173 _protected member_ `FWorkflowAllowedTabSet BlueprintEditorOnlyTabFactories;` — Set of spawnable tabs only usable in blueprint editing mode (not useful in Persona, etc...)

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintEditorModule.h` (Public)


#### struct `UE::BlueprintEditor::FAdditionalCategory`  
`struct FAdditionalCategory`  
_L63-88_
- desc: Describes a Blueprint category that should always be visible, even when it contains no entries. Registered programmatically via FBlueprintEditorModule.
- L66 _public member_ `FText Category;` — Display name of the category.
- L72 _public member_ `TArray<FSoftClassPath> ClassFilters;` — Only apply this category for blueprints whose ParentClass is a child of one of these classes. If empty, applies to all blueprints.
- L87 _public member_ `TArray<FPlaceholder> Placeholders;` — Show placeholder row when the category is empty.

#### struct `UE::BlueprintEditor::FAdditionalCategory::FPlaceholder`  
`struct FPlaceholder`  
_L74-84_
- L77 _public member_ `FText MenuDescription;` — Display text of the placeholder entry.
- L80 _public member_ `FText Tooltip;` — Tooltip of the placeholder entry.
- L83 _public member_ `NodeSectionID::Type SectionID = NodeSectionID::NONE;` — Section of the placeholder entry.

#### enum `ERefreshBlueprintEditorReason::Type`  
`enum Type`  
_L107-112_
- L109 _public enumerator_ `BlueprintCompiled`
- L110 _public enumerator_ `PostUndo`
- L111 _public enumerator_ `UnknownReason`

#### class `IUserDefinedEnumEditor`  
`class IUserDefinedEnumEditor : public FAssetEditorToolkit`  
_L118-120_
- inherits: `FAssetEditorToolkit`
- desc: Enum editor public interface

#### class `IUserDefinedStructureEditor`  
`class IUserDefinedStructureEditor : public FAssetEditorToolkit`  
_L125-127_
- inherits: `FAssetEditorToolkit`
- desc: Enum editor public interface

#### class `IBlueprintEditor`  
`class IBlueprintEditor : public FWorkflowCentricApplication`  
_L132-189_
- inherits: `FWorkflowCentricApplication`
- desc: Blueprint editor public interface
- L135 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename) = 0;`
- L136 _public prototype_ `virtual void JumpToPin(const UEdGraphPin* PinToFocusOn) = 0;`
- L139 _public prototype_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false) = 0;` — Invokes the search UI and sets the mode and search terms optionally
- L142 _public prototype_ `virtual void SummonFindAndReplaceUI() = 0;` — Invokes the Find and Replace UI
- L145 _public prototype_ `virtual UEdGraph* GetFocusedGraph() const = 0;` — Returns the currently focused graph context, or NULL if no graph is available.
- L148 _public prototype_ `virtual TSharedPtr<class SGraphEditor> OpenGraphAndBringToFront(class UEdGraph* Graph, bool bSetFocus = true) = 0;` — Tries to open the specified graph and bring it's document to the front (note: this can return NULL)
- L150 _public prototype_ `virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type Reason = ERefreshBlueprintEditorReason::UnknownReason) = 0;`
- L152 _public prototype_ `virtual void RefreshMyBlueprint() = 0;`
- L154 _public prototype_ `virtual void RefreshInspector() = 0;`
- L156 _public prototype_ `virtual void AddToSelection(UEdGraphNode* InNode) = 0;`
- L158 _public prototype_ `virtual bool CanPasteNodes() const= 0;`
- L161 _public function_ `virtual void PasteNodesHere(class UEdGraph* Graph, const FVector2D& Location) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Slate positions are represented in FVector2f. Please update to use the function acceping FVector2f.")`
- L162 _public prototype_ `virtual void PasteNodesHere(class UEdGraph* Graph, const FVector2f& Location) = 0;`
- L164 _public prototype_ `virtual bool GetBoundsForSelectedNodes(class FSlateRect& Rect, float Padding ) = 0;`
- L167 _public prototype_ `virtual TArray<TSharedPtr<FSubobjectEditorTreeNode>> GetSelectedSubobjectEditorTreeNodes() const = 0;` — Util to get the currently selected Subobject editor tree Nodes
- L170 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const = 0;` — Get number of currently selected nodes in the SCS editor tree
- L173 _public prototype_ `virtual TSharedPtr<FSubobjectEditorTreeNode> FindAndSelectSubobjectEditorTreeNode(const class UActorComponent* InComponent, bool IsCntrlDown) = 0;` — Find and select a specific SCS editor tree node associated with the given component
- L176 _public prototype_ `virtual void AnalyticsTrackNodeEvent( UBlueprint* Blueprint, UEdGraphNode *GraphNode, bool bNodeDelete = false ) const = 0;` — Used to track node create/delete events for Analytics
- L179 _public function_ `virtual TSharedPtr<class IClassViewerFilter> GetImportedClassViewerFilter() const` — Return the class viewer filter associated with the current set of imported namespaces within this editor context. Default is NULL (no filter).
- L182 _public function_ `virtual void GetPinTypeSelectorFilters(TArray<TSharedPtr<class IPinTypeSelectorFilter>>& OutFilters) const` — Get all the the pin type selector filters within this editor context.
- L185 _public function_ `virtual bool IsNonImportedObject(const UObject* InObject) const` — Return whether the given object falls outside the scope of the current set of imported namespaces within this editor context. Default is FALSE (imported).
- L188 _public function_ `virtual bool IsNonImportedObject(const FSoftObjectPath& InObject) const` — Return whether the given object (referenced by path) falls outside the scope of the current set of imported namespaces within this editor context. Default is FALSE (imported).

#### class `FBlueprintEditorModule`  
`class FBlueprintEditorModule : public IModuleInterface, public IHasMenuExtensibility`  
_L196-477_
- inherits: `IModuleInterface,IHasMenuExtensibility`
- desc: The blueprint editor module provides the blueprint editor application.
- L201 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L202 _public prototype_ `virtual void ShutdownModule() override;`
- L219 _public prototype_ `virtual TSharedRef<IBlueprintEditor> CreateBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UBlueprint* Blueprint, bool bShouldOpenInDefaultsMode = false);` — Creates an instance of a Kismet editor object.  Only virtual so that it can be called across the DLL boundary. Note: This function should not be called directly, use one of the following instead: - FKismetEditorUtilities::BringKismetToFocusAttentionOnObject - GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Blueprint				The blueprint object to start editing @param	bShouldOpenInDefaultsMode	If true, the editor will open in defaults editing mode @return	Interface to the new Blueprint editor
- L220 _public prototype_ `virtual TSharedRef<IBlueprintEditor> CreateBlueprintEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray< UBlueprint* >& BlueprintsToEdit, bool bShouldOpenInDefaultsMode = true);`
- L223 _public prototype_ `virtual TArray<TSharedRef<IBlueprintEditor>> GetBlueprintEditors() const;` — Get all blueprint editor instances
- L234 _public prototype_ `virtual TSharedRef<IUserDefinedEnumEditor> CreateUserDefinedEnumEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UUserDefinedEnum* UDEnum);` — Creates an instance of a Enum editor object. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	UDEnum					The user-defined Enum to start editing @return	Interface to the new Enum editor
- L245 _public prototype_ `virtual TSharedRef<IUserDefinedStructureEditor> CreateUserDefinedStructEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UUserDefinedStruct* UDStruct);` — Creates an instance of a Structure editor object. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	UDEnum					The user-defined structure to start editing @return	Interface to the new Struct editor
- L248 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend blueprint editor's menus and toolbars
- L251 _public prototype_ `DECLARE_EVENT_TwoParams(FBlueprintEditorModule, FBlueprintMenuExtensionEvent, TSharedPtr<FExtender>, UBlueprint*);`
- L252 _public function_ `FBlueprintMenuExtensionEvent& OnGatherBlueprintMenuExtensions()`
- L254 _public prototype_ `DECLARE_EVENT_ThreeParams(IBlueprintEditor, FOnRegisterTabs, FWorkflowAllowedTabSet&, FName , TSharedPtr<FBlueprintEditor>);`
- L255 _public function_ `FOnRegisterTabs& OnRegisterTabsForEditor()`
- L257 _public prototype_ `DECLARE_EVENT_OneParam(IBlueprintEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L258 _public function_ `FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L261 _public prototype_ `virtual void SetDetailsCustomization(TSharedPtr<class FDetailsViewObjectFilter> InDetailsObjectFilter, TSharedPtr<class IDetailRootObjectCustomization> InDetailsRootCustomization);` — Sets customizations for the BP editor details panel.
- L265 _public prototype_ `virtual void SetSubobjectEditorUICustomization(TSharedPtr<ISCSEditorUICustomization> InSCSEditorUICustomization);` — `UE_DEPRECATED(5.7, "Please use AddCustomization instead.")` — Sets SCS editor UI customization
- L268 _public prototype_ `virtual void AddCustomization(TSharedPtr<ISCSEditorUICustomization> InSCSEditorUICustomization);` — Adds the SCS editor UI customization to the array of customizations to be invoked
- L271 _public prototype_ `virtual void RemoveCustomization(TSharedPtr<ISCSEditorUICustomization> InSCSEditorUICustomization);` — Removes the SCS editor UI customization from the array of customizations to be invoked
- L278 _public prototype_ `virtual void RegisterSCSEditorCustomization(const FName& InComponentName, FSCSEditorCustomizationBuilder InCustomizationBuilder);` — Register a customization for interacting with the SCS editor @param	InComponentName			The name of the component to customize behavior for @param	InCustomizationBuilder	The delegate used to create customization instances
- L284 _public prototype_ `virtual void UnregisterSCSEditorCustomization(const FName& InComponentName);` — Unregister a previously registered customization for interacting with the SCS editor @param	InComponentName			The name of the component to customize behavior for
- L291 _public prototype_ `virtual FDelegateHandle RegisterVariableCustomization(FFieldClass* InFieldClass, FOnGetVariableCustomizationInstance InOnGetVariableCustomization);` — Register a customization for for Blueprint variables @param	InStruct				The type of the variable to create the customization for @param	InOnGetDetailCustomization	The delegate used to create customization instances
- L298 _public prototype_ `virtual void UnregisterVariableCustomization(FFieldClass* InFieldClass, FDelegateHandle InHandle);` — Unregister a previously registered customization for BP variables @param	InStruct				The type to create the customization for @param	InHandle				The handle returned by RegisterVariableCustomization
- L305 _public prototype_ `virtual FDelegateHandle RegisterLocalVariableCustomization(FFieldClass* InFieldClass, FOnGetLocalVariableCustomizationInstance InOnGetLocalVariableCustomization);` — Register a customization for for Blueprint local variables @param	InFieldClass				The type of the variable to create the customization for @param	InOnGetLocalVariableCustomization	The delegate used to create customization instances
- L312 _public prototype_ `virtual void UnregisterLocalVariableCustomization(FFieldClass* InFieldClass, FDelegateHandle InHandle);` — Unregister a previously registered customization for BP local variables @param	InFieldClass				The type to create the customization for @param	InHandle				The handle returned by RegisterLocalVariableCustomization
- L319 _public prototype_ `virtual void RegisterGraphCustomization(const UEdGraphSchema* InGraphSchema, FOnGetGraphCustomizationInstance InOnGetGraphCustomization);` — Register a customization for for Blueprint graphs @param	InGraphSchema				The schema of the graph to create the customization for @param	InOnGetDetailCustomization	The delegate used to create customization instances
- L325 _public prototype_ `virtual void UnregisterGraphCustomization(const UEdGraphSchema* InGraphSchema);` — Unregister a previously registered customization for BP graphs @param	InGraphSchema				The schema of the graph to create the customization for
- L332 _public prototype_ `virtual FDelegateHandle RegisterFunctionCustomization(TSubclassOf<UK2Node_EditablePinBase> InFieldClass, FOnGetFunctionCustomizationInstance InOnGetFunctionCustomization);` — Register a customization for for Blueprint functions @param	InStruct				The type of the pin to create the customization for @param	InOnGetFunctionCustomization	The delegate used to create customization instances
- L339 _public prototype_ `virtual void UnregisterFunctionCustomization(TSubclassOf<UK2Node_EditablePinBase> InFieldClass, FDelegateHandle InHandle);` — Unregister a previously registered customization for BP functions @param	InStruct				The type to create the customization for @param	InHandle				The handle returned by UnregisterFunctionCustomization
- L347 _public prototype_ `virtual TArray<TSharedPtr<IDetailCustomization>> CustomizeVariable(FFieldClass* InFieldClass, TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Build a set of details customizations for the passed-in type, if possible. @param	InStruct				The type to create the customization for @param	InBlueprintEditor		The Blueprint Editor the customization will be created for
- L354 _public prototype_ `virtual TArray<TSharedPtr<IDetailCustomization>> CustomizeGraph(const UEdGraphSchema* InGraphSchema, TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Build a set of details customizations for graphs with the passed-in schema, if possible. @param	InGraphSchema			The schema to create the customization for @param	InBlueprintEditor		The Blueprint Editor the customization will be created for
- L361 _public prototype_ `virtual TArray<TSharedPtr<IDetailCustomization>> CustomizeFunction(TSubclassOf<UK2Node_EditablePinBase> InFunctionClass, TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Build a set of details customizations for function with the passed-in type, if possible. @param	InFunctionClass		The type to create the customization for @param	InBlueprintEditor		The Blueprint Editor the customization will be created for
- L364 _public prototype_ `DECLARE_EVENT_OneParam( FBlueprintEditorModule, FBlueprintEditorOpenedEvent, EBlueprintType );` — Delegate for binding functions to be called when the blueprint editor finishes getting created
- L365 _public function_ `FBlueprintEditorOpenedEvent& OnBlueprintEditorOpened()`
- L372 _public function_ `virtual const TSharedRef<FUICommandList> GetsSharedBlueprintEditorCommands() const` — Exposes a way for other modules to fold in their own Blueprint editor commands (folded in with other BP editor commands, when the editor is first opened).
- L375 _public function_ `const TUniquePtr<FBlueprintDebugger>& GetBlueprintDebugger() const` — Returns a reference to the Blueprint Debugger state object
- L404 _public prototype_ `FAdditionalCategoryHandle RegisterAdditionalBlueprintCategory(UE::BlueprintEditor::FAdditionalCategory InCategory);` — Register an additional category. Returns a handle for unregistration.
- L407 _public prototype_ `void UnregisterAdditionalBlueprintCategory(FAdditionalCategoryHandle Handle);` — Unregister a previously registered category by handle.
- L410 _public prototype_ `TArray<UE::BlueprintEditor::FAdditionalCategory> GetAdditionalBlueprintCategories() const;` — Returns all additional categories.
- L413 _public prototype_ `TArray<UE::BlueprintEditor::FAdditionalCategory> GetAdditionalBlueprintCategories(TNotNull<const UBlueprint*> Blueprint) const;` — Returns the additional categories for the Blueprint.
- L417 _private prototype_ `void PrepareAutoGeneratedDefaultEvents();` — Loads from ini a list of all events that should be auto created for Blueprints of a specific class
- L421 _private member_ `TArray<TWeakPtr<FBlueprintEditor>> BlueprintEditors;` — List of all blueprint editors that were created.
- L423 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L426 _private member_ `FBlueprintMenuExtensionEvent GatherBlueprintMenuExtensions;`
- L429 _private member_ `FOnRegisterTabs RegisterTabsForEditor;` — Event called to allow external clients to register additional tabs for the specified editor
- L430 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`
- L433 _private member_ `FBlueprintEditorOpenedEvent BlueprintEditorOpened;` — Event to be called when the blueprint editor is opened
- L436 _private member_ `TMap<FName, FSCSEditorCustomizationBuilder> SCSEditorCustomizations;` — Customizations for the SCS editor
- L439 _private member_ `TMultiMap<FFieldClass*, FOnGetVariableCustomizationInstance> VariableCustomizations;` — Customizations for Blueprint variables
- L442 _private member_ `TMultiMap<FFieldClass*, FOnGetLocalVariableCustomizationInstance> LocalVariableCustomizations;` — Customizations for Blueprint local variables
- L445 _private member_ `TMap<const UEdGraphSchema*, FOnGetGraphCustomizationInstance> GraphCustomizations;` — Customizations for Blueprint graphs
- L448 _private member_ `TMultiMap<TSubclassOf<UK2Node_EditablePinBase>, FOnGetFunctionCustomizationInstance> FunctionCustomizations;` — Customizations for Blueprint functions
- L451 _private member_ `TSharedPtr<class IDetailRootObjectCustomization> DetailsRootCustomization;` — Root customization for the BP editor details panel.
- L454 _private member_ `TSharedPtr<class FDetailsViewObjectFilter> DetailsObjectFilter;` — Filter used to determine the set of objects shown in the BP editor details panel.
- L457 _private member_ `TSharedPtr<FFBlueprintEditorSCSEditorUICustomization> SCSEditorUICustomization;` — UI customizations for the SCS editor inside the blueprint editor
- L463 _private member_ `TSharedPtr<FUICommandList> SharedBlueprintEditorCommands;` — A command list that can be passed around and isn't bound to an instance of the blueprint editor.
- L466 _private member_ `FDelegateHandle LevelViewportContextMenuBlueprintExtenderDelegateHandle;` — Handle to a registered LevelViewportContextMenuBlueprintExtender delegate
- L469 _private member_ `TSharedPtr<SWidget> ConfigurationPanel;` — Reference to keep our custom configuration panel alive
- L472 _private member_ `TUniquePtr<FBlueprintDebugger> BlueprintDebugger;` — Blueprint debugger state - refactor into SBlueprintDebugger if needed
- L475 _private member_ `TArray<TTuple<FAdditionalCategoryHandle, UE::BlueprintEditor::FAdditionalCategory>> RegisteredAdditionalCategories;` — Programmatically registered additional Blueprint categories.
- L476 _private member_ `uint32 NextAdditionalCategoryHandle = 0;`

#### struct `FBlueprintEditorModule::FAdditionalCategoryHandle`  
`struct FAdditionalCategoryHandle`  
_L378-401_
- desc: Opaque handle returned by RegisterAdditionalBlueprintCategory. Pass to Unregister to remove.
- L380 _public prototype_ `FAdditionalCategoryHandle() = default;`
- L382 _public function_ `bool IsValid() const`
- L387 _public function_ `bool operator==(const FAdditionalCategoryHandle& Other) const`
- L395 _private member_ `static constexpr uint32 InvalidValue = MAX_uint32;`
- L396 _private function_ `explicit FAdditionalCategoryHandle(uint32 InValue) : Value(InValue)`
- L400 _private member_ `uint32 Value = InvalidValue;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API KISMET_API`
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace BlueprintEditor` (scope `UE`)
- L93 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetVariableCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize variable display
- L93 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetVariableCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize variable display
- L96 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetLocalVariableCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize local variable display
- L96 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetLocalVariableCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize local variable display
- L99 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetFunctionCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize function display
- L99 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetFunctionCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize function display
- L102 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetGraphCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize graph display
- L102 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IDetailCustomization>, FOnGetGraphCustomizationInstance, TSharedPtr<IBlueprintEditor> );` — Delegate used to customize graph display
- L105 _namespace_ `namespace ERefreshBlueprintEditorReason`
- L191 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<class ISCSEditorCustomization>, FSCSEditorCustomizationBuilder, TSharedRef< IBlueprintEditor > );`
- L191 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<class ISCSEditorCustomization>, FSCSEditorCustomizationBuilder, TSharedRef< IBlueprintEditor > );`
- L251 _delegate_ `DECLARE_EVENT_TwoParams(FBlueprintEditorModule, FBlueprintMenuExtensionEvent, TSharedPtr<FExtender>, UBlueprint*);`
- L254 _delegate_ `DECLARE_EVENT_ThreeParams(IBlueprintEditor, FOnRegisterTabs, FWorkflowAllowedTabSet&, FName , TSharedPtr<FBlueprintEditor>);`
- L257 _delegate_ `DECLARE_EVENT_OneParam(IBlueprintEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L364 _delegate_ `DECLARE_EVENT_OneParam( FBlueprintEditorModule, FBlueprintEditorOpenedEvent, EBlueprintType );` — Delegate for binding functions to be called when the blueprint editor finishes getting created

### `Source/Editor/Kismet/Public/BlueprintEditorSharedTabFactories.h` (Public)


#### struct `FCompilerResultsSummoner`  
`struct FCompilerResultsSummoner : public FWorkflowTabFactory`  
_L17-28_
- inherits: `FWorkflowTabFactory`
- L20 _public prototype_ `FCompilerResultsSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API KISMET_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "BlueprintEditor"`

### `Source/Editor/Kismet/Public/BlueprintEditorTabs.h` (Public)


#### struct `FBlueprintEditorTabs`  
`struct FBlueprintEditorTabs`  
_L11-34_
- L14 _public member_ `static const FName DetailsID;` — Tab identifiers
- L15 _public member_ `static const FName DefaultEditorID;`
- L16 _public member_ `static const FName DebugID;`
- L17 _public member_ `static const FName PaletteID;`
- L18 _public member_ `static const FName BookmarksID;`
- L19 _public member_ `static const FName CompilerResultsID;`
- L20 _public member_ `static const FName FindResultsID;`
- L21 _public member_ `static const FName ConstructionScriptEditorID;`
- L22 _public member_ `static const FName SCSViewportID;`
- L23 _public member_ `static const FName MyBlueprintID;`
- L24 _public member_ `static const FName ReplaceNodeReferencesID;`
- L25 _public member_ `static const FName UserDefinedStructureID;`
- L26 _public member_ `static const FName BlueprintDebuggerID;`
- L29 _public member_ `static const FName GraphEditorID;` — Document tab identifiers
- L30 _public member_ `static const FName TimelineEditorID;`
- L33 _private function_ `FBlueprintEditorTabs()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintManagedListDetails.h` (Public)


#### class `FBlueprintManagedListDetails`  
`class FBlueprintManagedListDetails : public IDetailCustomNodeBuilder`  
_L26-79_
- inherits: `IDetailCustomNodeBuilder`
- desc: Blueprint managed list details
- L56 _protected member_ `FDisplayOptions DisplayOptions;` — Mutable display options
- L59 _protected prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& HeaderRow) override;` — IDetailCustomNodeBuilder interface
- L60 _protected prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L61 _protected function_ `virtual FName GetName() const override`
- L62 _protected function_ `virtual bool InitiallyCollapsed() const override`
- L63 _protected function_ `virtual void Tick(float DeltaTime) override`
- L64 _protected function_ `virtual bool RequiresTick() const override`
- L65 _protected function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override`
- L69 _protected function_ `virtual TSharedPtr<SWidget> MakeAddItemWidget()` — Overridable interface methods
- L70 _protected function_ `virtual void GetManagedListItems(TArray<FManagedListItem>& OutListItems) const`
- L71 _protected function_ `virtual void OnRemoveItem(const FManagedListItem& Item)`
- L74 _protected prototype_ `void RegenerateChildContent();` — Helper function to regenerate the details customization
- L78 _private member_ `FSimpleDelegate RegenerateChildrenDelegate;` — A delegate to regenerate this list of children

#### struct `FBlueprintManagedListDetails::FManagedListItem`  
`struct FManagedListItem`  
_L30-42_
- desc: List item node type
- L32 _public member_ `FString ItemName;`
- L33 _public member_ `FText DisplayName;`
- L34 _public member_ `TWeakObjectPtr<> AssetPtr;`
- L35 _public member_ `uint8 bIsRemovable : 1;`
- L36 _public member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyHandles;`
- L38 _public function_ `FManagedListItem() :bIsRemovable(false)`

#### struct `FBlueprintManagedListDetails::FDisplayOptions`  
`struct FDisplayOptions`  
_L45-53_
- desc: Customizable display options
- L47 _public member_ `FText TitleText;`
- L48 _public member_ `FText TitleTooltipText;`
- L49 _public member_ `FText NoItemsLabelText;`
- L50 _public member_ `FText BrowseButtonToolTipText;`
- L51 _public member_ `FText RemoveButtonToolTipText;`
- L52 _public member_ `TAttribute<bool> EditCondition;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintMemberReferenceCustomization.h` (Public)


#### class `FBlueprintMemberReferenceDetails`  
`class FBlueprintMemberReferenceDetails : public IPropertyTypeCustomization`  
_L17-42_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for FMemberReference
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<SMyBlueprint> InMyBlueprint)`
- L31 _private function_ `FBlueprintMemberReferenceDetails(TWeakPtr<SMyBlueprint> InMyBlueprint) : MyBlueprint(InMyBlueprint)`
- L37 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L38 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override`
- L41 _private member_ `TWeakPtr<SMyBlueprint> MyBlueprint;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintNamespaceHelper.h` (Public)


#### class `FBlueprintNamespaceHelper`  
`class FBlueprintNamespaceHelper`  
_L23-129_
- desc: A helper class for managing namespace info for a single Blueprint context.
- L27 _public prototype_ `FBlueprintNamespaceHelper();` — Default constructor.
- L30 _public prototype_ `virtual ~FBlueprintNamespaceHelper();` — Note: We explicitly declare/implement the dtor so that forward-declared types can be destroyed.
- L37 _public prototype_ `void AddBlueprint(const UBlueprint* InBlueprint);` — Add a new Blueprint into the current helper context. @param InBlueprint	A Blueprint object being edited.
- L44 _public prototype_ `void AddNamespace(const FString& Namespace);` — Add a namespace identifier into the Blueprint editor context that's managed by this instance. @param Namespace		The namespace identifier string to add. Should resemble "X.Y.Z" as the format.
- L52 _public function_ `template<typename ContainerType> void AddNamespaces(const ContainerType& NamespaceList)` — Add multiple namespace identifiers into the Blueprint editor context that's managed by this instance. @param NamespaceList	A container type containing one or more namespace identifier strings. Each entry should resemble "X.Y.Z" as the format.
- L65 _public prototype_ `void RemoveNamespace(const FString& Namespace);` — Remove a namespace identifier from the Blueprint editor context that's managed by this instance. @param Namespace		The namespace identifier string to remove. Should resemble "X.Y.Z" as the format.
- L73 _public prototype_ `bool IsIncludedInNamespaceList(const FString& TestNamespace) const;` — Tests a namespace identifier to see if it's been imported. @param TestNamespace	A namespace identifier string. Should resemble "X.Y.Z" as the format. @return TRUE if the namespace identifier exists within the Blueprint editor context that's managed by this instance.
- L81 _public prototype_ `bool IsImportedAsset(const FAssetData& InAssetData) const;` — Tests an asset's namespace to see if it's been imported. @param InAssetData	Asset data context. @return TRUE if the asset's underlying namespace was imported into the Blueprint editor context that's managed by this instance.
- L89 _public prototype_ `bool IsImportedObject(const UObject* InObject) const;` — Tests an object's namespace to see if it's been imported. @param InObject	Hard reference to a (loaded) object. @return TRUE if the object's underlying namespace was imported into the Blueprint editor context that's managed by this instance.
- L97 _public prototype_ `bool IsImportedObject(const FSoftObjectPath& InObjectPath) const;` — Tests an object's namespace to see if it's been imported. @param InObjectPath	Soft reference to an object. May be loaded or unloaded. @return TRUE if the object's underlying namespace was imported into the Blueprint editor context that's managed by this instance.
- L102 _public function_ `TSharedPtr<IClassViewerFilter> GetClassViewerFilter() const` — @return A class viewer filter that can be used with class picker widgets to filter out class types whose namespaces were not imported into the Blueprint editor context that's managed by this instance.
- L110 _public function_ `TSharedPtr<IPinTypeSelectorFilter> GetPinTypeSelectorFilter() const` — @return A pin type selection filter that can be used with pin type selector widgets to filter out pin types whose namespaces were not imported into the Blueprint editor context that's managed by this instance.
- L118 _public prototype_ `static void RefreshEditorFeatureConsoleFlags();` — Utility method used to keep console flags in sync with the current Blueprint editor settings environment.
- L122 _private member_ `TUniquePtr<FBlueprintNamespacePathTree> NamespacePathTree;` — Path tree that stores imported namespace identifiers for the associated Blueprint.
- L125 _private member_ `TSharedPtr<IClassViewerFilter> ClassViewerFilter;` — For use with the class viewer widget in order to filter class type items by namespace.
- L128 _private member_ `TSharedPtr<IPinTypeSelectorFilter> PinTypeSelectorFilter;` — For use with the pin type selector widget in order to filter pin type items by namespace.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintNamespaceRegistry.h` (Public)


#### class `FBlueprintNamespaceRegistry`  
`class FBlueprintNamespaceRegistry`  
_L24-121_
- desc: A shared utility class that keeps track of registered Blueprint namespace identifiers sourced from objects and assets in the editor.
- L27 _public prototype_ `~FBlueprintNamespaceRegistry();`
- L32 _public prototype_ `static FBlueprintNamespaceRegistry& Get();` — Provides public singleton access.
- L37 _public prototype_ `void Initialize();` — One-time initialization method; separated from the ctor so it can be called explicitly.
- L42 _public prototype_ `void Shutdown();` — One-time shutdown method; separated from the dtor so it can be called explicitly.
- L47 _public prototype_ `bool IsRegisteredPath(const FString& InPath) const;` — @return TRUE if the given path identifier is currently registered.
- L57 _public prototype_ `bool IsInclusivePath(const FString& InPath) const;` — @return TRUE if the given path identifier is inclusive of any registered paths. Example: If "MyProject.MyNamespace" is a registered path, then both "MyProject" and "MyProject.MyNamespace" are inclusive paths. Also note if a registered path is removed, inclusive paths may still be valid. For instance, if both "MyProject.MyNamespace" and "MyProject.MyNamespace_2" are registered paths, and "MyProject.MyNamespace_2" is removed, "MyProject" is still an inclusive path.
- L63 _public prototype_ `void GetNamesUnderPath(const FString& InPath, TArray<FName>& OutNames) const;` — @param InPath	Path identifier string (e.g. "X.Y" or "X.Y."). @param OutNames	On output, an array containing the set of names rooted to the given path (e.g. "Z" in "X.Y.Z").
- L68 _public prototype_ `void GetAllRegisteredPaths(TArray<FString>& OutPaths) const;` — @param OutPaths	On output, contains the full set of all currently-registered namespace identifier paths.
- L75 _public prototype_ `void RegisterNamespace(const FString& InPath);` — Adds an explicit namespace identifier to the registry if not already included. @param InPath	Path identifier string (e.g. "X.Y").
- L80 _public prototype_ `void Rebuild();` — Recreates the namespace registry.
- L83 _protected prototype_ `FBlueprintNamespaceRegistry();`
- L86 _protected prototype_ `void OnAssetAdded(const FAssetData& AssetData);` — Asset registry event handler methods.
- L87 _protected prototype_ `void OnAssetRemoved(const FAssetData& AssetData);`
- L88 _protected prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& InOldName);`
- L89 _protected prototype_ `void OnAssetRegistryFilesLoaded();`
- L92 _protected prototype_ `void FindAndRegisterAllNamespaces();` — Namespace identifier registration methods.
- L93 _protected prototype_ `void RegisterNamespace(const UObject* InObject);`
- L94 _protected prototype_ `void RegisterNamespace(const FAssetData& AssetData);`
- L97 _protected prototype_ `void ToggleDefaultNamespace();` — Console command implementations (debugging/testing).
- L98 _protected prototype_ `void DumpAllRegisteredPaths();`
- L99 _protected prototype_ `void OnDefaultNamespaceTypeChanged();`
- L102 _protected prototype_ `void OnReloadComplete(EReloadCompleteReason InReason);` — Handler for hot reload / live coding completion events.
- L106 _private member_ `bool bIsInitialized;` — Indicates whether the registry has been initialized.
- L109 _private member_ `FDelegateHandle OnAssetAddedDelegateHandle;` — Delegate handles to allow for deregistration on shutdown.
- L110 _private member_ `FDelegateHandle OnAssetRemovedDelegateHandle;`
- L111 _private member_ `FDelegateHandle OnAssetRenamedDelegateHandle;`
- L112 _private member_ `FDelegateHandle OnFilesLoadedDelegateHandle;`
- L113 _private member_ `FDelegateHandle OnReloadCompleteDelegateHandle;`
- L114 _private member_ `FDelegateHandle OnDefaultNamespaceTypeChangedDelegateHandle;`
- L117 _private member_ `TUniquePtr<FBlueprintNamespacePathTree> PathTree;` — Handles storage and retrieval for namespace path identifiers.
- L120 _private member_ `TSet<FSoftObjectPath> ExcludedObjectPaths;` — Internal set of objects to exclude during namespace registration.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/BlueprintNamespaceUtilities.h` (Public)


#### enum `EDefaultBlueprintNamespaceType`  
`enum class EDefaultBlueprintNamespaceType`  
_L21-28_
- desc: Default namespace type for objects/assets if one is not explicitly assigned.
- L24 _public enumerator_ `DefaultToGlobalNamespace` — All objects/assets belong to the global namespace by default.
- L27 _public enumerator_ `UsePackagePathAsDefaultNamespace` — All objects/assets base their default namespace on the underlying package path.

#### struct `FBlueprintNamespaceUtilities`  
`struct FBlueprintNamespaceUtilities`  
_L31-108_
- desc: A wrapper struct around various Blueprint namespace utility and support methods.
- L40 _public prototype_ `static FString GetAssetNamespace(const FAssetData& InAssetData);` — Analyzes the given asset to determine its explicitly-assigned namespace identifier, or otherwise returns its default namespace. @param InAssetData	Input asset data. @return The unique Blueprint namespace identifier associated with the given asset, or an empty string if the asset belongs to the global namespace (default).
- L48 _public prototype_ `static FString GetObjectNamespace(const UObject* InObject);` — Analyzes the given object to determine its explicitly-assigned namespace identifier, or otherwise returns its default namespace. @param InObject		A reference to the input object. @return The unique Blueprint namespace identifier associated with the given object, or an empty string if the object belongs to the global namespace (default).
- L56 _public prototype_ `static FString GetObjectNamespace(const FSoftObjectPath& InObjectPath);` — Analyzes the given object path to determine its explicitly-assigned namespace identifier, or otherwise returns its default namespace. @param InObjectPath	Path to the given object (may not be loaded yet). @return The unique Blueprint namespace identifier associated with the given object (even if unloaded), or an empty string if the object belongs to the global namespace (default).
- L65 _public prototype_ `static void GetPropertyValueNamespaces(const FProperty* InProperty, const void* InContainer, TSet<FString>& OutNamespaces);` — Analyzes a property value to determine explicitly-assigned namespace identifiers from any object references, or otherwise returns the default namespace for each occurrence (default). @param InProperty	The property for which we will analyze the value. @param InContainer	The source address of the struct/object containing the property's value. @param OutNamespaces	Zero or more unique namespace identifier(s) referenced by the property value. An entry with an empty string equates to the default global namespace.
- L72 _public prototype_ `static void GetSharedGlobalImports(TSet<FString>& OutNamespaces);` — Gathers the set of global namespaces that are implicitly imported by all Blueprint assets. @param OutNamespaces	Zero or more unique namespace identifier(s) representing the shared global namespace set.
- L80 _public prototype_ `static void GetDefaultImportsForObject(const UObject* InObject, TSet<FString>& OutNamespaces);` — Gathers the set of default namespaces that are implicitly imported by a given object's type. @param InObject		A reference to a loaded object or type. @param OutNamespaces	Zero or more unique namespace identifier(s) representing the type's default namespace set.
- L87 _public prototype_ `static void SetDefaultBlueprintNamespaceType(EDefaultBlueprintNamespaceType InType);` — Sets the default Blueprint namespace type that objects/assets should use when not explicitly assigned. @param InType		Default namespace type to use.
- L90 _public prototype_ `static EDefaultBlueprintNamespaceType GetDefaultBlueprintNamespaceType();` — @return The default Blueprint namespace type objects/assets should use. Currently used for debugging/testing.
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDefaultBlueprintNamespaceTypeChanged);` — Delegate invoked whenever the default Blueprint namespace type changes.
- L94 _public prototype_ `static FOnDefaultBlueprintNamespaceTypeChanged& OnDefaultBlueprintNamespaceTypeChanged();`
- L99 _public prototype_ `static void RefreshBlueprintEditorFeatures();` — Refresh the Blueprint editor environment to align with current namespace editor feature settings.
- L107 _public prototype_ `static void ConvertPackagePathToNamespacePath(const FString& InPackagePath, FString& OutNamespacePath);` — Helper method to convert a package path to a Blueprint namespace identifier string. @param InPackagePath		Package path input string. @param OutNamespacePath	The input string converted to namespace identifier format.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API KISMET_API`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDefaultBlueprintNamespaceTypeChanged);` — Delegate invoked whenever the default Blueprint namespace type changes.

### `Source/Editor/Kismet/Public/CallStackViewer.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace CallStackViewer`
- L15 _prototype_ `void UpdateDisplayedCallstack(TArrayView<const FFrame* const> ScriptStack);` (scope `CallStackViewer`)
- L16 _prototype_ `FName GetTabName();` (scope `CallStackViewer`)
- L17 _prototype_ `void RegisterTabSpawner(FTabManager& TabManager);` (scope `CallStackViewer`)

### `Source/Editor/Kismet/Public/Debugging/SKismetDebugTreeView.h` (Public)


#### class `FDebugLineItem`  
`class FDebugLineItem : public TSharedFromThis<FDebugLineItem>`  
_L56-184_
- inherits: `TSharedFromThis<FDebugLineItem>`
- desc: The base class for a line entry in the debugging tree view
- L81 _public prototype_ `virtual ~FDebugLineItem() = default;`
- L84 _public prototype_ `virtual TSharedRef<SWidget> GenerateNameWidget(TSharedPtr<FString> InSearchString);` — Create the widget for the name column
- L87 _public prototype_ `virtual TSharedRef<SWidget> GenerateValueWidget(TSharedPtr<FString> InSearchString);` — Create the widget for the value column
- L90 _public prototype_ `void MakeMenu(class FMenuBuilder& MenuBuilder, bool bInDebuggerTab);` — Add standard context menu items that can act on any node of the tree
- L93 _public prototype_ `virtual void ExtendContextMenu(class FMenuBuilder& MenuBuilder, bool bInDebuggerTab);` — Add context menu items that can act on this node of the tree
- L96 _public function_ `virtual void GatherChildrenBase(TArray<FDebugTreeItemPtr>& OutChildren, const FString& InSearchString, bool bRespectSearch = true)` — Gather all of the children
- L99 _public prototype_ `virtual bool HasChildren() const;` — returns whether this tree node has children (used by drop down arrows)
- L102 _public function_ `virtual bool CanHaveChildren()` — only line items inheriting from FLineItemWithChildren can have children
- L105 _public function_ `virtual UObject* GetParentObject() const` — @return The object that will act as a parent to more items in the tree, or nullptr if this is a leaf node
- L107 _public function_ `virtual EDebugLineType GetType() const`
- L113 _public prototype_ `virtual TSharedRef<SWidget> GetNameIcon();` — returns a widget that will go to the left of the Name Widget.
- L116 _public prototype_ `virtual TSharedRef<SWidget> GetValueIcon();` — returns a widget that will go to the left of the Value Widget.
- L119 _public prototype_ `FText GetHighlightText(const TSharedPtr<FString> InSearchString) const;` — returns current value of Search String
- L125 _public prototype_ `static UBlueprint* GetBlueprintForObject(UObject* ParentObject);` — Helper function to try to get the blueprint for a given object; Returns the blueprint that was used to create the instance if there was one Returns the object itself if it is already a blueprint Otherwise returns NULL
- L127 _public prototype_ `static UBlueprintGeneratedClass* GetClassForObject(UObject* ParentObject);`
- L129 _public prototype_ `static bool IsDebugLineTypeActive(EDebugLineType Type);`
- L130 _public prototype_ `static void OnDebugLineTypeActiveChanged(ECheckBoxState CheckState, EDebugLineType Type);`
- L132 _public prototype_ `static void SetBreakpointParentItemBlueprint(FDebugTreeItemPtr InBreakpointParentItem, TWeakObjectPtr<UBlueprint> InBlueprint);`
- L135 _public prototype_ `void UpdateSearch(const FString& InSearchString, ESearchFlags SearchFlags);` — updates bVisible and bParentsMatchSearch based on this node alone
- L137 _public prototype_ `bool IsVisible();`
- L138 _public prototype_ `bool DoParentsMatchSearch();`
- L141 _public prototype_ `virtual FText GetDescription() const;` — @return The text to display in the value column, unless GenerateValueWidget is overridden
- L145 _protected function_ `FDebugLineItem(EDebugLineType InType) : Type(InType)` — Cannot create an instance of this class, it's just for use as a base class
- L151 _protected prototype_ `virtual FDebugLineItem* Duplicate() const = 0;` — Duplicate this item
- L154 _protected prototype_ `virtual bool Compare(const FDebugLineItem* Other) const = 0;` — Compare this item to another of the same type
- L157 _protected prototype_ `virtual uint32 GetHash() const = 0;` — used for sets
- L161 _protected function_ `[[maybe_unused]] virtual void UpdateData(const FDebugLineItem& NewerData)` — Used to update the state of a line item rather than replace it. called after Compare returns true
- L164 _protected prototype_ `virtual FText GetName() const;` — @return The actual underlying name of the item, for search compatibility
- L167 _protected prototype_ `virtual FText GetDisplayName() const;` — @return The text to display in the name column, unless GenerateNameWidget is overridden
- L169 _protected prototype_ `bool HasName() const;`
- L170 _protected prototype_ `bool HasValue() const;`
- L171 _protected prototype_ `void CopyNameToClipboard() const;`
- L172 _protected prototype_ `void CopyValueToClipboard() const;`
- L176 _protected member_ `EDebugLineType Type;` — Type of action (a kind of RTTI for the tree, really only used to accelerate Compare checks)
- L178 _protected member_ `static uint16 ActiveTypeBitset;`
- L181 _protected member_ `bool bVisible = false;` — true if self or any recursive children match the search
- L183 _protected member_ `bool bParentsMatchSearch = false;` — true if self or any recursive parents match the search

#### enum `FDebugLineItem::EDebugLineType`  
`enum EDebugLineType`  
_L60-72_
- L62 _public enumerator_ `DLT_Message`
- L63 _public enumerator_ `DLT_TraceStackParent`
- L64 _public enumerator_ `DLT_TraceStackChild`
- L65 _public enumerator_ `DLT_Parent`
- L66 _public enumerator_ `DLT_SelfWatch`
- L67 _public enumerator_ `DLT_Watch`
- L68 _public enumerator_ `DLT_WatchChild`
- L69 _public enumerator_ `DLT_LatentAction`
- L70 _public enumerator_ `DLT_Breakpoint`
- L71 _public enumerator_ `DLT_BreakpointParent`

#### enum `FDebugLineItem::ESearchFlags`  
`enum ESearchFlags`  
_L74-79_
- L76 _public enumerator_ `SF_None = 0`
- L77 _public enumerator_ `SF_RootNode = 1 << 0`
- L78 _public enumerator_ `SF_ContainerElement = 1 << 1`

#### class `SKismetDebugTreeView`  
`class SKismetDebugTreeView : public SCompoundWidget`  
_L189-266_
- inherits: `SCompoundWidget`
- L192 _public function_ `SLATE_BEGIN_ARGS(SKismetDebugTreeView) : _SelectionMode(ESelectionMode::Single) , _OnExpansionChanged() , _InDebuggerTab(false)`
- L205 _public prototype_ `void Construct(const FArguments& InArgs);`
- L208 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L212 _public prototype_ `void AddTreeItemUnique(const FDebugTreeItemPtr& Item);` — Adds a root level TreeItem
- L215 _public prototype_ `bool RemoveTreeItem(const FDebugTreeItemPtr& Item);` — Removes a root level TreeItem
- L218 _public prototype_ `void ClearTreeItems();` — Clears all root level Tree Items
- L221 _public prototype_ `void SetSearchText(const FText& InSearchText);` — Updates search text and requests the Tree be updated
- L224 _public prototype_ `void RequestUpdateFilteredItems();` — Requests for an update of the tree at the next tick
- L227 _public prototype_ `const TArray<FDebugTreeItemPtr>& GetRootTreeItems() const;` — Returns the Array of Root Tree Items
- L230 _public prototype_ `int32 GetSelectedItems(TArray<FDebugTreeItemPtr>& OutItems);` — Passthrough functions to the TreeView
- L231 _public prototype_ `void ClearExpandedItems();`
- L232 _public prototype_ `bool IsScrolling() const;`
- L233 _public prototype_ `void SetItemExpansion(FDebugTreeItemPtr InItem, bool bInShouldExpandItem);`
- L236 _private prototype_ `void UpdateFilteredItems();` — Updates the Filtered Items based on current Root Tree Items
- L238 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FDebugTreeItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L239 _private prototype_ `void OnGetChildren(FDebugTreeItemPtr InParent, TArray<FDebugTreeItemPtr>& OutChildren);`
- L240 _private prototype_ `TSharedPtr<SWidget> OnMakeContextMenu() const;`
- L242 _private member_ `TSharedPtr< STreeView< FDebugTreeItemPtr > > TreeView;`
- L243 _private member_ `TArray<FDebugTreeItemPtr> FilteredTreeRoots;`
- L244 _private member_ `TArray<FDebugTreeItemPtr> RootTreeItems;`
- L246 _private member_ `TSharedPtr<FString> SearchString;`
- L248 _private member_ `bool bFilteredItemsDirty;`
- L251 _private member_ `FDebugTreeItemPtr SearchMessageItem;` — message to display when no entries in the tree match the search text
- L254 _private member_ `bool bInDebuggerTab;` — whether this tree is held within the blueprint debugger tab, used to hide context menu options
- L257 _public prototype_ `static FDebugTreeItemPtr MakeTraceStackParentItem();` — Accessible functions for creating tree items
- L258 _public prototype_ `static FDebugTreeItemPtr MakeBreakpointParentItem(TWeakObjectPtr<UBlueprint> InBlueprint);`
- L259 _public prototype_ `static FDebugTreeItemPtr MakeMessageItem(const FString& InMessage);`
- L260 _public prototype_ `static FDebugTreeItemPtr MakeParentItem(UObject* InObject);`
- L261 _public prototype_ `static FDebugTreeItemPtr MakeWatchLineItem(const UEdGraphPin* InPinRef, UObject* InDebugObject);`
- L264 _public member_ `static const FName ColumnId_Name;` — Column Id's for custom header rows
- L265 _public member_ `static const FName ColumnId_Value;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API KISMET_API`
- L53 _typedef_ `typedef TSharedPtr<class FDebugLineItem> FDebugTreeItemPtr;` — Shared pointer to a debugging tree line entry

### `Source/Editor/Kismet/Public/DetailsDiff.h` (Public)


#### class `FDetailsDiff`  
`class FDetailsDiff`  
_L20-60_
- desc: Struct to handle showing details for an object and provide an interface for listing all differences
- L23 _public prototype_ `FDetailsDiff( const UObject* InObject, bool bScrollbarOnLeft = false );`
- L26 _public prototype_ `DECLARE_DELEGATE( FOnDisplayedPropertiesChanged );` — `UE_DEPRECATED(5.6, "FOnDisplayedPropertiesChanged removed, interact with IDetailsView directly")`
- L30 _public prototype_ `FDetailsDiff( const UObject* InObject, FOnDisplayedPropertiesChanged InOnDisplayedPropertiesChanged, bool bScrollbarOnLeft = false );` — `UE_DEPRECATED(5.6, "InOnDisplayedPropertiesChanged, interact with IDetailsView directly")`
- L34 _public prototype_ `void HighlightProperty( const FPropertySoftPath& PropertyName );` — Attempt to highlight the property with the given path, may not always succeed
- L37 _public prototype_ `TSharedRef< IDetailsView > DetailsWidget() const;` — Returns actual widget that is used to display details
- L40 _public function_ `const UObject* GetDisplayedObject() const` — Returns object being displayed
- L43 _public prototype_ `TArray<FPropertySoftPath> GetDisplayedProperties() const;` — Returns a list of all properties that would be diffed
- L46 _public prototype_ `void DiffAgainst(const FDetailsDiff& Newer, TArray<FSingleObjectDiffEntry>& OutDifferences, bool bSortByDisplayOrder = false) const;` — Perform a diff against another view, ordering either by display order or by remove/add/change
- L49 _public prototype_ `static void LinkScrolling(FDetailsDiff& LeftPanel, FDetailsDiff& RightPanel, const TAttribute<TArray<FVector2f>>& ScrollRate);` — Link the two details panels so they scroll in sync with one another
- L51 _public prototype_ `static TSharedRef<IDetailsView> CreateDetailsView(const UObject* InObject, TSharedPtr<SScrollBar> ExternalScrollbar = nullptr, bool bScrollbarOnLeft = false);`
- L54 _private member_ `TArray< FPropertyPath > DisplayedProperties;`
- L55 _private member_ `const UObject* DisplayedObject;`
- L57 _private member_ `TSharedPtr< class IDetailsView > DetailsView;`
- L59 _private member_ `TSharedPtr<SLinkableScrollBar> ScrollBar;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API KISMET_API`
- L26 _delegate_ `DECLARE_DELEGATE( FOnDisplayedPropertiesChanged );`

### `Source/Editor/Kismet/Public/FindInBlueprintManager.h` (Public)


#### struct `FFindInBlueprintSearchTags`  
`struct FFindInBlueprintSearchTags`  
_L73-151_
- desc: Const values for Find-in-Blueprints to tag searchable data
- L76 _public member_ `static const FText FiB_Properties;` — Properties tag, for Blueprint variables
- L79 _public member_ `static const FText FiB_Components;` — Components tags
- L80 _public member_ `static const FText FiB_IsSCSComponent;`
- L84 _public member_ `static const FText FiB_Nodes;` — Nodes tag
- L87 _public member_ `static const FText FiB_SchemaName;` — Schema Name tag, to identify the schema that a graph uses
- L89 _public member_ `static const FText FiB_UberGraphs;` — Uber graphs tag
- L91 _public member_ `static const FText FiB_Functions;` — Function graph tag
- L93 _public member_ `static const FText FiB_Macros;` — Macro graph tag
- L95 _public member_ `static const FText FiB_SubGraphs;` — Sub graph tag, for any sub-graphs in a Blueprint
- L97 _public member_ `static const FText FiB_ExtensionGraphs;` — Extension graph tag, for any graphs in a Blueprint Extension
- L99 _public member_ `static const FText FiB_Extensions;` — Blueprint extension tag.
- L102 _public member_ `static const FText FiB_Name;` — Name tag
- L104 _public member_ `static const FText FiB_NativeName;` — Native Name tag
- L106 _public member_ `static const FText FiB_ClassName;` — Class Name tag
- L108 _public member_ `static const FText FiB_NodeGuid;` — NodeGuid tag
- L110 _public member_ `static const FText FiB_DefaultValue;` — Default value
- L112 _public member_ `static const FText FiB_Tooltip;` — Tooltip tag
- L114 _public member_ `static const FText FiB_Description;` — Description tag
- L116 _public member_ `static const FText FiB_Comment;` — Comment tag
- L118 _public member_ `static const FText FiB_Path;` — Path tag
- L120 _public member_ `static const FText FiB_ParentClass;` — Parent Class tag
- L122 _public member_ `static const FText FiB_Interfaces;` — Interfaces tag
- L124 _public member_ `static const FText FiB_FuncOriginClass;` — Class that originally defined the function tag
- L129 _public member_ `static const FText FiB_Pins;` — Pins tag
- L132 _public member_ `static const FText FiB_PinCategory;` — Pin Category tag
- L134 _public member_ `static const FText FiB_PinSubCategory;` — Pin Sub-Category tag
- L136 _public member_ `static const FText FiB_ObjectClass;` — Pin object class tag
- L138 _public member_ `static const FText FiB_IsArray;` — Pin IsArray tag
- L140 _public member_ `static const FText FiB_IsReference;` — Pin IsReference tag
- L142 _public member_ `static const FText FiB_Glyph;` — Glyph icon tag
- L144 _public member_ `static const FText FiB_GlyphStyleSet;` — Style set the glyph belongs to
- L146 _public member_ `static const FText FiB_GlyphColor;` — Glyph icon color tag
- L149 _public member_ `static const FText FiBMetaDataTag;` — Identifier for metadata storage, completely unsearchable tag

#### enum `EFiBVersion`  
`enum EFiBVersion : int`  
_L155-167_
- reflection: `UENUM()`
- desc: FiB data versioning
- L157 _public enumerator_ `FIB_VER_NONE = -1` — Unknown version (not set)
- L159 _public enumerator_ `FIB_VER_BASE = 0` — All Blueprints prior to versioning will automatically be assumed to be at 0 if they have FiB data collected
- L160 _public enumerator_ `FIB_VER_VARIABLE_REFERENCE` — Variable references (FMemberReference) is collected in FiB
- L161 _public enumerator_ `FIB_VER_INTERFACE_GRAPHS` — Implemented Interface Graphs is collected in FiB
- L162 _public enumerator_ `FIB_VER_FUNC_CALL_SITES` — Hidden target pins and function origin class are collected in FiB for improved function call site searchability
- L165 _public enumerator_ `FIB_VER_PLUS_ONE` — -----<new versions can be added before this line>-------------------------------------------------
- L166 _public enumerator_ `FIB_VER_LATEST = FIB_VER_PLUS_ONE - 1` — Always the last version, we want Blueprints to be at latest

#### struct `FSearchDataVersionInfo`  
`struct FSearchDataVersionInfo`  
_L170-180_
- desc: Consolidated version info for a Blueprint search data entry
- L173 _public member_ `int32 FiBDataVersion = EFiBVersion::FIB_VER_NONE;` — FiB asset registry tag data version
- L176 _public member_ `FCustomVersionContainer CustomVersions;` — Custom versions used to serialize values in the JSON string lookup table
- L179 _public prototype_ `static FSearchDataVersionInfo Current();` — Current version info

#### enum `ESearchDataStateFlags`  
`enum class ESearchDataStateFlags : uint8`  
_L183-190_
- desc: State flags for search database entries
- L185 _public enumerator_ `None = 0`
- L187 _public enumerator_ `IsIndexed = 1 << 0` — Set when this search database entry has been fully indexed, which is completed asynchronously
- L189 _public enumerator_ `WasRemoved = 1 << 1` — Cached to determine if the Blueprint is seen as no longer valid, allows it to be cleared out next save to disk

#### struct `FSearchData`  
`struct FSearchData`  
_L195-258_
- desc: Tracks data relevant to a Blueprint for searches
- L198 _public member_ `TWeakObjectPtr<UBlueprint> Blueprint;` — The Blueprint this search data points to, if available
- L201 _public member_ `FSoftObjectPath AssetPath;` — The full asset path this search data is associated with of the form /Game/Path/To/Package.Package
- L204 _public member_ `FString Value;` — Encoded search data block for the Blueprint, this will not always be set if it's already been parsed
- L207 _public member_ `FName AssetKeyForValue;` — Key to use to look up the encoded search data from an FAssetData, if this is set Value will probably be empty
- L210 _public member_ `FString ParentClass;` — Parent Class
- L213 _public member_ `TArray<FString> Interfaces;` — Interfaces implemented by the Blueprint
- L216 _public member_ `FImaginaryFiBDataSharedPtr ImaginaryBlueprint;` — Cached ImaginaryBlueprint data for the searchable content, prevents having to re-parse every search
- L219 _public member_ `FSearchDataVersionInfo VersionInfo;` — Data versioning
- L222 _public member_ `ESearchDataStateFlags StateFlags;` — State flags (see enum)
- L224 _public function_ `FSearchData() : Blueprint(nullptr) , StateFlags(ESearchDataStateFlags::None)`
- L231 _public function_ `bool IsValid() const` — True if this represents a valid asset
- L237 _public function_ `bool HasEncodedValue() const` — True if this has an encoded value that has yet to be parsed
- L243 _public function_ `void ClearEncodedValue()` — Clear the encoded value after parsing or getting new data
- L249 _public function_ `bool IsIndexingCompleted() const`
- L254 _public function_ `bool IsMarkedForDeletion() const`

#### enum `ESearchQueryFilter`  
`enum ESearchQueryFilter`  
_L261-274_
- desc: Filters are used by functions for searching to decide whether items can call certain functions or match the requirements of a function
- L263 _public enumerator_ `BlueprintFilter = 0`
- L264 _public enumerator_ `GraphsFilter`
- L265 _public enumerator_ `UberGraphsFilter`
- L266 _public enumerator_ `FunctionsFilter`
- L267 _public enumerator_ `MacrosFilter`
- L268 _public enumerator_ `NodesFilter`
- L269 _public enumerator_ `PinsFilter`
- L270 _public enumerator_ `PropertiesFilter`
- L271 _public enumerator_ `VariablesFilter`
- L272 _public enumerator_ `ComponentsFilter`
- L273 _public enumerator_ `AllFilter` — Will search all items, when used inside of another filter it will search all sub-items of that filter

#### struct `FSearchTagDataPair`  
`struct FSearchTagDataPair`  
_L277-286_
- desc: Used for external gather functions to add Key/Value pairs to be placed into Json
- L279 _public function_ `FSearchTagDataPair(FText InKey, FText InValue) : Key(InKey) , Value(InValue)`
- L284 _public member_ `FText Key;`
- L285 _public member_ `FText Value;`

#### struct `FFiBMD`  
`struct FFiBMD`  
_L288-295_
- L290 _public member_ `static const FString FiBSearchableMD;`
- L291 _public member_ `static const FString FiBSearchableShallowMD;`
- L292 _public member_ `static const FString FiBSearchableExplicitMD;`
- L293 _public member_ `static const FString FiBSearchableHiddenExplicitMD;`
- L294 _public member_ `static const FString FiBSearchableFormatVersionMD;`

#### enum `EFiBCacheOpType`  
`enum class EFiBCacheOpType`  
_L298-302_
- desc: Which assets to index for caching
- L300 _public enumerator_ `CachePendingAssets`
- L301 _public enumerator_ `CacheUnindexedAssets`

#### enum `EFiBCacheOpFlags`  
`enum class EFiBCacheOpFlags`  
_L305-330_
- desc: Flags to control the UX while caching
- L307 _public enumerator_ `None = 0`
- L309 _public enumerator_ `ShowProgress = 1 << 0` — Whether to show progress
- L311 _public enumerator_ `HideNotifications = 1 << 1` — Whether to hide toast popups
- L313 _public enumerator_ `AllowUserCancel = 1 << 2` — Whether to allow users to cancel
- L315 _public enumerator_ `CheckOutAndSave = 1 << 3` — Set if the user wants to check out and save (applies to unindexed caching only)
- L317 _public enumerator_ `HideProgressBars = 1 << 4` — Whether to hide progress bar widgets
- L319 _public enumerator_ `AllowUserCloseProgress = 1 << 5` — Whether to allow users to hide/close progress
- L321 _public enumerator_ `IsCachingDiscoveredAssets = 1 << 6` — Set if we are caching assets from the discovery stage
- L323 _public enumerator_ `KeepProgressVisibleOnCompletion = 1 << 7` — Whether to keep progress visible on completion
- L325 _public enumerator_ `ExecuteOnMainThread = 1 << 8` — Index deferred assets on the main thread only (used for debugging)
- L327 _public enumerator_ `ExecuteOnSingleThread = 1 << 9` — Don't index multiple assets in parallel (used to assist with profiling)
- L329 _public enumerator_ `ExecuteGatherPhaseOnly = 1 << 10` — Only execute the gather phase (used to help minimize memory usage on editor/tab open)

#### struct `FFindInBlueprintCachingOptions`  
`struct FFindInBlueprintCachingOptions`  
_L335-348_
- desc: Options to configure the bulk caching task
- L338 _public member_ `EFiBCacheOpType OpType = EFiBCacheOpType::CachePendingAssets;` — Type of caching operation
- L341 _public member_ `EFiBCacheOpFlags OpFlags = EFiBCacheOpFlags::None;` — Initial set of control flags
- L344 _public member_ `FSimpleDelegate OnFinished;` — Callback for when caching is finished
- L347 _public member_ `EFiBVersion MinimiumVersionRequirement = EFiBVersion::FIB_VER_LATEST;` — Minimum version requirement for caching, any Blueprints below this version will be re-indexed

#### enum `EAddOrUpdateBlueprintSearchMetadataFlags`  
`enum class EAddOrUpdateBlueprintSearchMetadataFlags`  
_L351-358_
- desc: Options for FFindInBlueprintSearchManager::AddOrUpdateBlueprintSearchMetadata()
- L353 _public enumerator_ `None = 0`
- L355 _public enumerator_ `ForceRecache = 1 << 0` — Forces the Blueprint to be recache'd, regardless of what data it believes exists
- L357 _public enumerator_ `ClearCachedValue = 1 << 1` — Clear any cached data value for this Blueprint

#### class `FFindInBlueprintsResult`  
`class FFindInBlueprintsResult : public TSharedFromThis< FFindInBlueprintsResult >`  
_L366-421_
- inherits: `TSharedFromThis<FFindInBlueprintsResult>`
- desc: Item that matched the search results
- L369 _public prototype_ `FFindInBlueprintsResult() = default;`
- L370 _public prototype_ `virtual ~FFindInBlueprintsResult() = default;`
- L373 _public prototype_ `explicit FFindInBlueprintsResult(const FText& InDisplayText);` — Create a root
- L376 _public prototype_ `virtual FReply OnClick();` — Called when user clicks on the search item
- L379 _public prototype_ `virtual FText GetCategory() const;` — Get Category for this search result
- L382 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L385 _public function_ `virtual void FinalizeSearchData()` — Finalizes any content for the search data that was unsafe to do on a separate thread
- L388 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L391 _public prototype_ `UBlueprint* GetParentBlueprint() const;` — gets the blueprint housing all these search results
- L401 _public function_ `virtual void ParseSearchInfo(FText InKey, FText InValue)` — Parses search info for specific data important for displaying the search result in an easy to understand format @param	InTokens		The search tokens to check results against @param	InKey			This is the tag for the data, describing what it is so special handling can occur if needed @param	InValue			Compared against search query to see if it passes the filter, sometimes data is rejected because it is deemed unsearchable @param	InParent		The parent search result
- L404 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const;` — Returns the Object represented by this search information give the Blueprint it can be found in
- L407 _public prototype_ `FText GetDisplayString() const;` — Returns the display string for the row
- L411 _public member_ `TArray< TSharedPtr<FFindInBlueprintsResult> > Children;` — Any children listed under this category
- L414 _public member_ `TWeakPtr<FFindInBlueprintsResult> Parent;` — If it exists it is the blueprint
- L417 _public member_ `FText DisplayText;` — The display text for this item
- L420 _public member_ `FString CommentText;` — Display text for comment information

#### struct `FStreamSearchOptions`  
`struct FStreamSearchOptions`  
_L428-442_
- L431 _public member_ `enum ESearchQueryFilter ImaginaryDataFilter;` — Filter to limit the FilteredImaginaryResults to
- L434 _public member_ `EFiBVersion MinimiumVersionRequirement;` — When searching, any Blueprint below this version will be considered out-of-date
- L437 _public function_ `FStreamSearchOptions() :ImaginaryDataFilter(ESearchQueryFilter::AllFilter) ,MinimiumVersionRequirement(EFiBVersion::FIB_VER_LATEST)` — Default constructor.

#### class `FStreamSearch`  
`class FStreamSearch : public FRunnable`  
_L447-522_
- inherits: `FRunnable`
- desc: Async task for searching Blueprints
- L451 _public prototype_ `FStreamSearch(const FString& InSearchValue, const FStreamSearchOptions& InSearchOptions = FStreamSearchOptions());` — Constructor
- L454 _public prototype_ `virtual bool Init() override;` — Begin FRunnable Interface
- L456 _public prototype_ `virtual uint32 Run() override;`
- L458 _public prototype_ `virtual void Stop() override;`
- L460 _public prototype_ `virtual void Exit() override;`
- L464 _public prototype_ `void EnsureCompletion();` — Brings the thread to a safe stop before continuing.
- L467 _public prototype_ `bool IsComplete() const;` — Returns TRUE if the thread is done with it's work.
- L470 _public prototype_ `bool WasStopped() const;` — Returns TRUE if Stop() was called while work is still pending.
- L477 _public prototype_ `void GetFilteredItems(TArray<TSharedPtr<class FFindInBlueprintsResult>>& OutItemsFound);` — Appends the items filtered through the search filter to the passed array @param OutItemsFound		All the items found since last queried
- L480 _public prototype_ `float GetPercentComplete() const;` — Helper function to query the percent complete this search is
- L483 _public function_ `int32 GetOutOfDateCount() const` — Returns the Out-of-Date Blueprint count
- L489 _public prototype_ `void GetFilteredImaginaryResults(TArray<FImaginaryFiBDataSharedPtr>& OutFilteredImaginaryResults);` — Returns the FilteredImaginaryResults from the search query, these results have been filtered by the ImaginaryDataFilter.
- L493 _public member_ `TUniquePtr<FRunnableThread> Thread;` — Thread to run the cleanup FRunnable on
- L496 _public member_ `TArray<TSharedPtr<class FFindInBlueprintsResult>> ItemsFound;` — A list of items found, cleared whenever the main thread pulls them to display to screen
- L499 _public member_ `FString SearchValue;` — The search value to filter results by
- L502 _public member_ `FStreamSearchOptions SearchOptions;` — Options for setting up the search
- L505 _public member_ `FCriticalSection SearchCriticalSection;` — Prevents searching while other threads are pulling search results
- L508 _public member_ `TArray<FImaginaryFiBDataSharedPtr> FilteredImaginaryResults;` — Filtered (ImaginaryDataFilter) list of imaginary data results that met the search requirements. Must be declared as thread-safe since imaginary data is a shared resource.
- L511 _public member_ `int32 BlueprintCountBelowVersion;` — A going count of all Blueprints below the MinimiumVersionRequirement
- L514 _public member_ `bool bThreadCompleted;` — Whether the thread has finished running
- L518 _private member_ `int32 SearchId;` — Unique identifier for this search (used with benchmarking)
- L521 _private member_ `FThreadSafeCounter StopTaskCounter;` — > 0 if we've been asked to abort work in progress at the next opportunity

#### class `FFindInBlueprintSearchManager`  
`class FFindInBlueprintSearchManager : public FTickableEditorObject`  
_L528-911_
- inherits: `FTickableEditorObject`
- desc: Singleton manager for handling all Blueprint searches, helps to manage the going progress of Blueprints, and is thread-safe.
- L531 _public member_ `static FFindInBlueprintSearchManager* Instance;`
- L532 _public prototype_ `static FFindInBlueprintSearchManager& Get();`
- L534 _public prototype_ `FFindInBlueprintSearchManager();`
- L535 _public prototype_ `~FFindInBlueprintSearchManager();`
- L538 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L539 _public prototype_ `virtual bool IsTickable() const override;`
- L540 _public prototype_ `virtual TStatId GetStatId() const override;`
- L549 _public prototype_ `void ApplySearchDataToDatabase(FSearchData InSearchData, bool bAllowNewEntry = false);` — Applies the given search data to a matching entry in the database. Optionally adds a new entry if a match is not found. @param InSearchData		Search data to be applied @param bAllowNewEntry	Whether to allow a new entry to be added if a match is not found
- L557 _public prototype_ `FSearchData GetSearchDataForAssetPath(const FSoftObjectPath& InAssetPath);` — Given an asset path, locate and return a copy of its matching search data in the index cache. @param InAssetPath				Asset path (search index key). @return							Matching search data from the index cache. Will return invalid (empty) search data if a matching entry was not found.
- L566 _public prototype_ `void AddOrUpdateBlueprintSearchMetadata(UBlueprint* InBlueprint, EAddOrUpdateBlueprintSearchMetadataFlags InFlags = EAddOrUpdateBlueprintSearchMetadataFlags::None, EFiBVersion InVersion = EFiBVersion::FIB_VER_NONE);` — Gathers the Blueprint's search metadata and adds or updates it in the cache @param InBlueprint		Blueprint to cache the searchable data for @param InFlags			Flags to assist with controlling this function's behavior @param InVersion			Allows the caller to override the format version to use for caching
- L573 _public prototype_ `void BeginSearchQuery(const class FStreamSearch* InSearchOriginator);` — Starts a search query, the FiB manager handles where the thread is at in the search query at all times so that post-save of the cache to disk it can correct the index @param InSearchOriginator		Pointer to the thread object that the query originates from
- L582 _public prototype_ `bool ContinueSearchQuery(const class FStreamSearch* InSearchOriginator, FSearchData& OutSearchData);` — Continues a search query, returning a single piece of search data @param InSearchOriginator		Pointer to the thread object that the query originates from @param OutSearchData				Result of the search, if there is any Blueprint search data still available to query @return							TRUE if the search was successful, FALSE if the search is complete
- L590 _public prototype_ `void EnsureSearchQueryEnds(const class FStreamSearch* InSearchOriginator);` — This function ensures that the passed in search query ends in a safe manner. The search will no longer be valid to this manager, though it does not destroy any objects. Use this whenever the search is finished or canceled. @param InSearchOriginator	Identifying search stream to be stopped
- L598 _public prototype_ `float GetPercentComplete(const class FStreamSearch* InSearchOriginator) const;` — Query how far along a search thread is @param OutSearchData				Result of the search, if there is any Blueprint search data still available to query @return							Percent along the search thread is
- L607 _public prototype_ `FSearchData QuerySingleBlueprint(UBlueprint* InBlueprint, bool bInRebuildSearchData);` — Query for a single, specific Blueprint's search data. @param InBlueprint				The Blueprint to search for @param bInRebuildSearchData		When TRUE the search data will be freshly collected @return							The search data, or invalid (empty) search data if not found
- L610 _public prototype_ `bool ProcessEncodedValueForUnloadedBlueprint(FSearchData& SearchData);` — Processes the encoded string value in the SearchData into the intermediate format, return true if string and version were valid
- L613 _public prototype_ `int32 GetNumberUnindexedAssets() const;` — Returns the number of unindexed Blueprints, either due to not having been indexed before, or AR data being out-of-date
- L616 _public prototype_ `int32 GetNumberUncachedAssets() const;` — Returns the number of uncached assets during an active indexing operation
- L624 _public prototype_ `void CacheAllAssets(TWeakPtr< class SFindInBlueprints > InSourceWidget, const FFindInBlueprintCachingOptions& InCachingOptions);` — Starts a task to cache Blueprints at a rate of 1 per tick @param InSourceWidget				The source FindInBlueprints widget, this widget will be informed when caching is complete @param InCachingOptions				Options to configure the caching task
- L629 _public prototype_ `void ExportOutdatedAssetList();` — Exports a list of all unindexed assets to Saved/FindInBlueprints_OutdatedAssetList.txt
- L637 _public prototype_ `void OnCacheAllUnindexedAssets(bool bInSourceControlActive, bool bInCheckoutAndSave);` — Starts the actual caching process @param bInSourceControlActive		TRUE if source control is active @param bInCheckoutAndSave			TRUE if the system should checkout and save all assets that need to be reindexed
- L640 _public prototype_ `void CancelCacheAll(SFindInBlueprints* InFindInBlueprintWidget);` — Stops the caching process where it currently is at, the rest can be continued later
- L643 _public prototype_ `int32 GetCurrentCacheIndex() const;` — Returns the current index in the caching
- L646 _public prototype_ `FSoftObjectPath GetCurrentCacheBlueprintPath() const;` — Returns the path of the current Blueprint being cached
- L649 _public prototype_ `float GetCacheProgress() const;` — Returns the progress complete on the caching
- L652 _public function_ `TSet<FSoftObjectPath> GetFailedToCachePathList() const` — Returns the list of Blueprint paths that failed to cache
- L655 _public function_ `int32 GetFailedToCacheCount() const` — Returns the number of Blueprints that failed to cache
- L658 _public function_ `bool HasCachingFailed() const` — Returns TRUE if caching failed
- L661 _public prototype_ `void StartedCachingBlueprints(EFiBCacheOpType InCacheOpType, EFiBCacheOpFlags InCacheOpFlags);` — Callback to note that Blueprint caching is started
- L668 _public prototype_ `void FinishedCachingBlueprints(EFiBCacheOpType InCacheOpType, EFiBCacheOpFlags InCacheOpFlags, int32 InNumberCached, TSet<FSoftObjectPath>& InFailedToCacheList);` — Callback to note that Blueprint caching is complete @param InNumberCached		The number of Blueprints cached, to be chopped off the existing array so the rest (if any) can be finished later
- L671 _public prototype_ `bool IsCacheInProgress() const;` — Returns TRUE if Blueprints are being cached.
- L674 _public prototype_ `bool IsUnindexedCacheInProgress() const;` — Returns TRUE if unindexed Blueprints are being cached (since this can block the UI)
- L677 _public prototype_ `bool IsAssetDiscoveryInProgress() const;` — Returns TRUE if we're still inside the initial asset discovery and registration stage
- L680 _public prototype_ `bool IsAsyncSearchQueryInProgress() const;` — Returns TRUE if there are one or more active asynchronous search queries
- L683 _public function_ `TWeakPtr<SFindInBlueprints> GetSourceCachingWidget() const` — Returns a weak reference to the widget that initiated the current caching operation
- L685 _public function_ `void EnableGatheringData(bool bInEnableGatheringData)`
- L687 _public function_ `bool IsGatheringDataEnabled() const`
- L690 _public function_ `bool ShouldEnableDeveloperMenuTools() const` — If TRUE, the developer menu tool commands will be shown in the 'Developer' section of the Blueprint Editor's menu bar
- L693 _public function_ `bool ShouldEnableSearchResultTemplates() const` — If TRUE, search result meta will be gathered once and stored in a template. Avoids doing this work redundantly at search time.
- L696 _public prototype_ `TSharedPtr<SFindInBlueprints> GetGlobalFindResults();` — Find or create the global find results widget
- L699 _public prototype_ `void EnableGlobalFindResults(bool bEnable);` — Enable or disable the global find results tab feature
- L702 _public prototype_ `void CloseOrphanedGlobalFindResultsTabs(TSharedPtr<class FTabManager> TabManager);` — Close any orphaned global find results tabs for a particular tab manager
- L705 _public function_ `bool IsGlobalFindResultsOpen() const` — Returns true if a global find results tab is currently open
- L707 _public prototype_ `void GlobalFindResultsClosed(const TSharedRef<SFindInBlueprints>& FindResults);`
- L710 _public prototype_ `void DumpCache(FArchive& Ar);` — Dumps the full index cache to the given stream (for debugging purposes)
- L713 _public prototype_ `void DoRandomIndexCacheRebuild();` — Randomly initiates a partial rebuild of the index cache (for debugging purposes)
- L717 _public prototype_ `static FText ConvertHexStringToFText(FString InHexString);` — Converts a string of hex characters, previously converted by ConvertFTextToHexString, to an FText.
- L720 _public prototype_ `static FString ConvertFTextToHexString(FText InValue);` — Serializes an FText to memory and converts the memory into a string of hex characters
- L723 _public prototype_ `static TSharedPtr< class FJsonObject > ConvertJsonStringToObject(FSearchDataVersionInfo InVersionInfo, const FString& InJsonString, TMap<int32, FText>& OutFTextLookupTable);` — Given a fully constructed Find-in-Blueprint FString of searchable data, will parse and construct a JsonObject
- L726 _public prototype_ `static FString GenerateSearchIndexForDebugging(UBlueprint* InBlueprint);` — Generates a human-readable search index for the given Blueprint (for debugging purposes)
- L730 _private prototype_ `void Initialize();` — Initializes the FiB manager
- L733 _private prototype_ `void PauseFindInBlueprintSearch();` — Callback hook during pre-garbage collection, pauses all processing searches so that the GC can do it's job
- L736 _private prototype_ `void UnpauseFindInBlueprintSearch();` — Callback hook during post-garbage collection, saves the cache to disk and unpauses all processing searches
- L739 _private prototype_ `void OnAssetAdded(const struct FAssetData& InAssetData);` — Callback hook from the Asset Registry when an asset is added
- L742 _private prototype_ `void OnAssetRemoved(const struct FAssetData& InAssetData);` — Callback hook from the Asset Registry, marks the asset for deletion from the cache
- L745 _private prototype_ `void OnAssetRenamed(const struct FAssetData& InAssetData, const FString& InOldName);` — Callback hook from the Asset Registry, marks the asset for deletion from the cache
- L748 _private prototype_ `void OnAssetRegistryFilesLoaded();` — Callback hook from the Asset Registry, signals that the initial asset discovery stage has been completed
- L751 _private prototype_ `void OnAssetLoaded(class UObject* InAsset);` — Callback hook from the Asset Registry when an asset is loaded
- L754 _private prototype_ `void OnBlueprintUnloaded(class UBlueprint* InBlueprint);` — Callback from Kismet when a Blueprint is unloaded
- L757 _private prototype_ `void OnReloadComplete(EReloadCompleteReason Reason);` — Callback hook from the Reload manager that indicates that a module has been reloaded
- L760 _private prototype_ `FSearchData GetSearchDataForIndex(int32 CacheIndex);` — Returns a copy of the search data that's cached at the given index. Will return invalid (empty) search data if the index is out of range
- L763 _private prototype_ `void CleanCache();` — Cleans the cache of any excess data from Blueprints that have been moved, renamed, or deleted. Occurs during post-garbage collection
- L766 _private prototype_ `void BuildCache();` — Builds the cache from all available Blueprint assets that the asset registry has discovered at the time of this function. Occurs on startup
- L774 _private prototype_ `int32 AddSearchDataToDatabase(FSearchData InSearchData);` — Helper to properly add a Blueprint's SearchData to the database @param InSearchData		Data to add to the database @return					Index into the SearchArray for looking up the added item
- L777 _private prototype_ `void RemoveBlueprintByPath(const FSoftObjectPath& InPath);` — Removes a Blueprint from being managed by the FiB system by passing in the UBlueprint's path
- L780 _private prototype_ `void AddUnloadedBlueprintSearchMetadata(const FAssetData& InAssetData);` — Adds a new search database entry for unloaded asset data
- L783 _private prototype_ `void ExtractUnloadedFiBData(const FAssetData& InAssetData, FString* InFiBData, FName InKeyForFiBData, EFiBVersion InFiBDataVersion);` — Begins the process of extracting FiB data from an unloaded asset
- L786 _private prototype_ `FText GetGlobalFindResultsTabLabel(int32 TabIdx);` — Determines the global find results tab label
- L789 _private prototype_ `TSharedRef<SDockTab> SpawnGlobalFindResultsTab(const FSpawnTabArgs& SpawnTabArgs, int32 TabIdx);` — Handler for a request to spawn a new global find results tab
- L792 _private prototype_ `TSharedPtr<SFindInBlueprints> OpenGlobalFindResultsTab();` — Creates and opens a new global find results tab
- L812 _protected typedef_ `typedef TSharedPtr<FActiveSearchQuery, ESPMode::ThreadSafe> FActiveSearchQueryPtr;`
- L815 _protected prototype_ `FActiveSearchQueryPtr FindSearchQuery(const class FStreamSearch* InSearchOriginator) const;` — Thread-safe access to the active search query that's mapped to the given stream search
- L818 _protected prototype_ `FSearchData GetNextSearchDataForQuery(const FStreamSearch* InSearchOriginator, FActiveSearchQueryPtr InSearchQueryPtr, bool bCheckDeferredList);` — Returns the next pending search data for the given query and advances the index to the next entry
- L821 _protected prototype_ `void BlockSearchQueryIfPaused();` — If searches are paused, blocks the calling thread until searching is resumed
- L825 _private member_ `TMap<FSoftObjectPath, int32> SearchMap;` — Maps the Blueprint paths to their index in the SearchArray
- L828 _private member_ `TArray<FSearchData> SearchArray;` — Stores the Blueprint search data and is used to iterate over in small chunks
- L831 _private member_ `FThreadSafeCounter ActiveSearchCounter;` — Counter of active searches
- L837 _private member_ `mutable FCriticalSection SafeQueryModifyCriticalSection;` — Critical section to safely add, remove, and find data in ActiveSearchQueries
- L840 _private member_ `FCriticalSection PauseThreadsCriticalSection;` — Critical section to lock threads during the pausing procedure
- L843 _private member_ `FCriticalSection SafeModifyCacheCriticalSection;` — Critical section to safely modify cached data
- L846 _private member_ `class FAssetRegistryModule* AssetRegistryModule;` — Because we are unable to query for the module on another thread, cache it for use later
- L849 _private member_ `TWeakPtr<SFindInBlueprints> SourceCachingWidget;` — FindInBlueprints widget that started the cache process
- L852 _private member_ `TSet<FSoftObjectPath> PendingAssets;` — Asset paths that were discovered, loaded or modified and now require indexing (or re-indexing)
- L855 _private member_ `TSet<FSoftObjectPath> UnindexedAssets;` — Asset paths that have not been cached for searching due to lack of FiB data, this means that they are either older Blueprints, or the DDC cannot find the data
- L858 _private member_ `TSet<FSoftObjectPath> FailedToCachePaths;` — List of paths for Blueprints that failed to cache
- L861 _private member_ `TSet<FSoftObjectPath> AssetsToIndexOnFirstSearch;` — List of paths that require a full index pass during the first global search
- L864 _private member_ `TUniquePtr<class FCacheAllBlueprintsTickableObject> CachingObject;` — Tickable object that does the caching of uncached Blueprints at a rate of once per tick
- L867 _private member_ `EFiBCacheOpType CurrentCacheOpType;` — Stores the type of caching operation that's currently in progress
- L870 _private member_ `TMap<FTopLevelAssetPath, TWeakObjectPtr<const UClass>> CachedAssetClasses;` — Mapping between a class name and its UClass instance - used for faster look up in FFindInBlueprintSearchManager::OnAssetAdded
- L873 _private member_ `FName GlobalFindResultsTabIDs[MAX_GLOBAL_FIND_RESULTS];` — The tab identifier/instance name for global find results
- L876 _private member_ `TArray<TWeakPtr<SFindInBlueprints>> GlobalFindResults;` — Array of open global find results widgets
- L879 _private member_ `TSharedPtr<class FWorkspaceItem> GlobalFindResultsMenuItem;` — Global Find Results workspace menu item
- L882 _private member_ `int32 AsyncTaskBatchSize;` — Size of a single async indexing task batch; zero or negative means that a caching operation will consist of a single batch
- L885 _private member_ `TAtomic<bool> bIsPausing;` — TRUE when the the FiB manager wants to pause all searches, helps manage the pausing procedure
- L888 _private member_ `TAtomic<bool> bHasFirstSearchOccurred;` — Currently used to delay the full indexing pass until the first search in order to control memory usage
- L891 _private member_ `bool bEnableGatheringData;` — Tells if gathering data is currently allowed
- L894 _private member_ `bool bDisableDeferredIndexing;` — If true, search metadata will be regenerated for loaded assets on the main thread immediately at discovery or load time. By default, this work is deferred to avoid hitching.
- L898 _private member_ `bool bDisableThreadedIndexing;` — If true, and if deferred indexing is not disabled, search metadata will be regenerated for loaded assets on the main thread at a rate of one asset per tick. Additional indexing work will be deferred to the search thread. By default, all indexing work is deferred to a background thread and both loaded and unloaded assets are fully indexed asynchronously.
- L901 _private member_ `bool bEnableCSVStatsProfiling;` — Whether CSV profiling has been enabled (default=false)
- L904 _private member_ `bool bEnableDeveloperMenuTools;` — Whether to enable Blueprint editor developer menu tools
- L907 _private member_ `bool bDisableSearchResultTemplates;` — Disable the use of search result templates. Setting this to TRUE will slightly decrease overall memory usage, but will also increase global search times
- L910 _private member_ `bool bDisableImmediateAssetDiscovery;` — Defers the cost to extract metadata for each discovered asset during the initial asset registry scan into a single pass over the full asset registry once the scan is complete.

#### struct `FFindInBlueprintSearchManager::FActiveSearchQuery`  
`struct FActiveSearchQuery`  
_L796-810_
- desc: Contains info about an active search query
- L799 _public member_ `TAtomic<int32> NextIndex;` — Current search array index
- L801 _public member_ `TAtomic<int32> SearchCount;` — Current count of assets searched
- L803 _public member_ `TQueue<FSoftObjectPath> DeferredAssetPaths;` — Asset paths for which searching was deferred due to being indexed
- L805 _public function_ `FActiveSearchQuery() :NextIndex(0) ,SearchCount(0)`

#### struct `FDisableGatheringDataOnScope`  
`struct FDisableGatheringDataOnScope`  
_L913-924_
- L915 _public member_ `bool bOriginallyEnabled;`
- L916 _public function_ `FDisableGatheringDataOnScope() : bOriginallyEnabled(FFindInBlueprintSearchManager::Get().IsGatheringDataEnabled())`
- L920 _public function_ `~FDisableGatheringDataOnScope()`

#### Free symbols / members of external scopes

- L42 _macro_ `#define UE_API KISMET_API`
- L52 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFindInBlueprint, Warning, All);`
- L52 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFindInBlueprint, Warning, All);`
- L55 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(FindInBlueprint);` — CSV stats profiling category
- L65 _typedef_ `typedef TWeakPtr<FImaginaryFiBData, ESPMode::ThreadSafe> FImaginaryFiBDataWeakPtr;` — Shared pointers to cached imaginary data (must be declared as thread-safe).
- L66 _typedef_ `typedef TSharedPtr<FImaginaryFiBData, ESPMode::ThreadSafe> FImaginaryFiBDataSharedPtr;`
- L68 _macro_ `#define MAX_GLOBAL_FIND_RESULTS 4`
- L192 _prototype_ `ENUM_CLASS_FLAGS(ESearchDataStateFlags);`
- L332 _prototype_ `ENUM_CLASS_FLAGS(EFiBCacheOpFlags);`
- L360 _prototype_ `ENUM_CLASS_FLAGS(EAddOrUpdateBlueprintSearchMetadataFlags);`
- L423 _typedef_ `typedef TSharedPtr<FFindInBlueprintsResult> FSearchResult;`

### `Source/Editor/Kismet/Public/FindInBlueprints.h` (Public)


#### struct `FindInBlueprintsHelpers::FSimpleFTextKeyStorage`  
`struct FSimpleFTextKeyStorage`  
_L65-79_
- desc: Stores an FText as if it were an FString, does zero advanced comparisons needed for true FText comparisons
- L67 _public member_ `FText Text;`
- L69 _public function_ `FSimpleFTextKeyStorage(FText InText) : Text(InText)`
- L75 _public function_ `bool operator==(const FSimpleFTextKeyStorage& InObject) const`

#### class `FFindInBlueprintsNoResult`  
`class FFindInBlueprintsNoResult : public FFindInBlueprintsResult`  
_L126-141_
- inherits: `FFindInBlueprintsResult`
- desc: Class used to denote an empty search result
- L129 _public function_ `FFindInBlueprintsNoResult(const FText& InDisplayText) :FFindInBlueprintsResult(InDisplayText)`
- L135 _public function_ `virtual FReply OnClick() override` — FFindInBlueprintsResult Interface

#### class `FFindInBlueprintsGraphNode`  
`class FFindInBlueprintsGraphNode : public FFindInBlueprintsResult`  
_L144-174_
- inherits: `FFindInBlueprintsResult`
- desc: Graph nodes use this class to store their data
- L147 _public prototype_ `FFindInBlueprintsGraphNode();`
- L148 _public prototype_ `virtual ~FFindInBlueprintsGraphNode() = default;`
- L151 _public prototype_ `virtual FReply OnClick() override;` — FFindInBlueprintsResult Interface
- L152 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L153 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L154 _public prototype_ `virtual FText GetCategory() const override;`
- L155 _public prototype_ `virtual void FinalizeSearchData() override;`
- L156 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const override;`
- L161 _private member_ `FGuid NodeGuid;` — The Node Guid to find when jumping to the node
- L164 _private member_ `FSlateIcon Glyph;` — The glyph brush for this node
- L167 _private member_ `FLinearColor GlyphColor;` — The glyph color for this node
- L170 _private member_ `UClass* Class;` — The class this item refers to
- L173 _private member_ `FString ClassName;` — The class name this item refers to

#### class `FFindInBlueprintsPin`  
`class FFindInBlueprintsPin : public FFindInBlueprintsResult`  
_L177-199_
- inherits: `FFindInBlueprintsResult`
- desc: Pins use this class to store their data
- L180 _public prototype_ `FFindInBlueprintsPin(FString InSchemaName);`
- L181 _public prototype_ `virtual ~FFindInBlueprintsPin() = default;`
- L184 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;` — FFindInBlueprintsResult Interface
- L185 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L186 _public prototype_ `virtual FText GetCategory() const override;`
- L187 _public prototype_ `virtual void FinalizeSearchData() override;`
- L192 _private member_ `FString SchemaName;` — The name of the schema this pin exists under
- L195 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L198 _private member_ `FSlateColor IconColor;` — Pin's icon color

#### class `FFindInBlueprintsProperty`  
`class FFindInBlueprintsProperty : public FFindInBlueprintsResult`  
_L202-225_
- inherits: `FFindInBlueprintsResult`
- desc: Property data is stored here
- L205 _public prototype_ `FFindInBlueprintsProperty();`
- L206 _public prototype_ `virtual ~FFindInBlueprintsProperty() = default;`
- L209 _public prototype_ `virtual FReply OnClick() override;` — FFindInBlueprintsResult Interface
- L210 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L211 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L212 _public prototype_ `virtual FText GetCategory() const override;`
- L213 _public prototype_ `virtual void FinalizeSearchData() override;`
- L218 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L221 _private member_ `FString DefaultValue;` — The default value of a property as a string
- L224 _private member_ `bool bIsSCSComponent;` — TRUE if the property is an SCS_Component

#### class `FFindInBlueprintsGraph`  
`class FFindInBlueprintsGraph : public FFindInBlueprintsResult`  
_L228-244_
- inherits: `FFindInBlueprintsResult`
- desc: Graphs, such as functions and macros, are stored here
- L231 _public prototype_ `FFindInBlueprintsGraph(EGraphType InGraphType);`
- L232 _public prototype_ `virtual ~FFindInBlueprintsGraph() = default;`
- L235 _public prototype_ `virtual FReply OnClick() override;` — FFindInBlueprintsResult Interface
- L236 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L237 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L238 _public prototype_ `virtual FText GetCategory() const override;`
- L243 _private member_ `EGraphType GraphType;` — The type of graph this represents

#### enum `EFiBCacheBarWidget`  
`enum class EFiBCacheBarWidget`  
_L247-257_
- desc: Cache bar widgets.
- L249 _public enumerator_ `ProgressBar`
- L250 _public enumerator_ `CloseButton`
- L251 _public enumerator_ `CancelButton`
- L252 _public enumerator_ `CacheAllUnindexedButton`
- L253 _public enumerator_ `CurrentAssetNameText`
- L254 _public enumerator_ `UnresponsiveEditorWarningText`
- L255 _public enumerator_ `ShowCacheFailuresButton`
- L256 _public enumerator_ `ShowCacheStatusText`

#### enum `EFiBSearchBarWidget`  
`enum class EFiBSearchBarWidget`  
_L260-265_
- desc: Search bar widgets.
- L262 _public enumerator_ `StatusText`
- L263 _public enumerator_ `Throbber`
- L264 _public enumerator_ `ProgressBar`

#### enum `EFiBIndexAllPermission`  
`enum class EFiBIndexAllPermission`  
_L269-277_
- reflection: `UENUM()`
- desc: Whether the Find-in-Blueprints window allows the user to load and resave all assets with out-of-date Blueprint search metadata
- L272 _public enumerator_ `None` — Users may not automatically load all Blueprints with out-of-date search metadata
- L274 _public enumerator_ `LoadOnly` — Users may automatically load all Blueprints with out-of-date search metadata, but not resave
- L276 _public enumerator_ `CheckoutAndResave` — Users may automatically checkout, load and resave all Blueprints with out-of-date search metadata

#### class `SFindInBlueprints`  
`class SFindInBlueprints: public SCompoundWidget`  
_L280-514_
- inherits: `SCompoundWidget`
- desc: Widget for searching for (functions/events) across all blueprints or just a single blueprint
- L283 _public function_ `SLATE_BEGIN_ARGS( SFindInBlueprints ) : _bIsSearchWindow(true) , _bHideSearchBar(false) , _bHideFindGlobalButton(false) , _ContainingTab()`
- L289 _public prototype_ `SLATE_ARGUMENT(bool, bIsSearchWindow) SLATE_ARGUMENT(bool, bHideSearchBar) SLATE_ARGUMENT(bool, bHideFindGlobalButton) SLATE_ARGUMENT(TSharedPtr<SDockTab>, ContainingTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FBlueprintEditor> InBlueprintEditor = nullptr);`
- L296 _public prototype_ `~SFindInBlueprints();`
- L299 _public prototype_ `void FocusForUse(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false);` — Focuses this widget's search box, and changes the mode as well, and optionally the search terms
- L309 _public prototype_ `void MakeSearchQuery(FString InSearchString, bool bInIsFindWithinBlueprint, const FStreamSearchOptions& InSearchOptions = FStreamSearchOptions(), FOnSearchComplete InOnSearchComplete = FOnSearchComplete());` — Submits a search query @param InSearchString						String to search using @param bInIsFindWithinBlueprint				TRUE if searching within the current Blueprint only @param InSearchOptions						Optional search parameters. @param InOnSearchComplete					Callback when the search is complete, passing the filtered imaginary data (if any).
- L312 _public prototype_ `void OnCacheStarted(EFiBCacheOpType InOpType, EFiBCacheOpFlags InOpFlags);` — Called when caching Blueprints is started
- L315 _public prototype_ `void OnCacheComplete(EFiBCacheOpType InOpType, EFiBCacheOpFlags InOpFlags);` — Called when caching Blueprints is complete
- L322 _public prototype_ `void CacheAllBlueprints(const FFindInBlueprintCachingOptions& InOptions);` — Asynchronously caches all Blueprints below a specified version. @param InOptions								Options to configure the caching task
- L325 _public prototype_ `FName GetHostTabId() const;` — If this is a global find results widget, returns the host tab's unique ID. Otherwise, returns NAME_None.
- L328 _public prototype_ `void CloseHostTab();` — If this is a global find results widget, ask the host tab to close
- L331 _public function_ `bool IsLocked() const` — Determines if this context does not accept syncing from an external source
- L337 _public prototype_ `bool IsSearchInProgress() const;` — Determines whether a search query is actively in progress
- L340 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget overrides
- L343 _public prototype_ `void ClearResults();` — Clears the currently visible results
- L347 _private prototype_ `EActiveTimerReturnType UpdateSearchResults( double InCurrentTime, float InDeltaTime );` — Processes results of the ongoing async stream search
- L350 _private prototype_ `void RegisterCommands();` — Register any Find-in-Blueprint commands
- L353 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L356 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L359 _private prototype_ `void OnGetChildren( FSearchResult InItem, TArray< FSearchResult >& OutChildren );` — Get the children of a row
- L362 _private prototype_ `void OnTreeSelectionDoubleClicked( FSearchResult Item );` — Called when user double clicks on a new result
- L365 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L368 _private prototype_ `void LaunchStreamThread(const FString& InSearchValue, const FStreamSearchOptions& InSearchOptions = FStreamSearchOptions(), FOnSearchComplete InOnSearchComplete = FOnSearchComplete());` — Launches a thread for streaming more content into the results widget
- L371 _private prototype_ `TOptional<float> GetPercentCompleteSearch() const;` — Returns the percent complete on the search for the progress bar
- L374 _private prototype_ `EVisibility GetSearchBarWidgetVisiblity(EFiBSearchBarWidget InSearchBarWidget) const;` — Returns the search bar visiblity for the given widget
- L377 _private prototype_ `void ConditionallyAddCacheBar();` — Adds the "cache" bar at the bottom of the Find-in-Blueprints widget, to notify the user that the search is incomplete
- L380 _private prototype_ `FReply OnRemoveCacheBar();` — Callback to remove the "cache" bar when a button is pressed
- L383 _private prototype_ `FText GetCacheBarStatusText() const;` — Callback to return the cache bar's display text, informing the user of the situation
- L386 _private prototype_ `FText GetCacheBarCurrentAssetName() const;` — Callback to return the current asset name during a cache operation
- L389 _private prototype_ `bool CanCacheAllUnindexedBlueprints() const;` — Whether user is allowed to initiate loading and indexing all blueprints with out-of-date metadata
- L392 _private prototype_ `FReply OnCacheAllUnindexedBlueprints();` — Callback to cache all unindexed Blueprints
- L395 _private prototype_ `FReply OnExportUnindexedAssetList();` — Callback to export a list of all blueprints that need reindexing
- L398 _private prototype_ `FReply OnCacheAllBlueprints(const FFindInBlueprintCachingOptions& InOptions);` — Callback to cache all Blueprints according to the given options
- L401 _private prototype_ `FReply OnCancelCacheAll();` — Callback to cancel the caching process
- L404 _private prototype_ `int32 GetCurrentCacheIndex() const;` — Retrieves the current index of the Blueprint caching process
- L407 _private prototype_ `TOptional<float> GetPercentCompleteCache() const;` — Gets the percent complete of the caching process
- L410 _private prototype_ `EVisibility GetCacheBarVisibility() const;` — Returns the caching bar's visibility, it goes invisible when there is nothing to be cached. The next search will remove this bar or make it visible again
- L413 _private prototype_ `EVisibility GetCacheBarWidgetVisibility(EFiBCacheBarWidget InCacheBarWidget) const;` — Returns the cache bar visibility for the given widget
- L416 _private prototype_ `bool IsCacheInProgress() const;` — Returns TRUE if Blueprint caching is in progress
- L419 _private prototype_ `const FSlateBrush* GetCacheBarImage() const;` — Returns the BG image used for the cache bar
- L422 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Callback to build the context menu when right clicking in the tree
- L425 _private prototype_ `void SelectAllItemsHelper(FSearchResult InItemToSelect);` — Helper function to select all items
- L428 _private prototype_ `void OnSelectAllAction();` — Callback when user attempts to select all items in the search results
- L431 _private prototype_ `void OnCopyAction();` — Callback when user attempts to copy their selection in the Find-in-Blueprints
- L434 _private prototype_ `FReply OnOpenGlobalFindResults();` — Called when the user clicks the global find results button
- L437 _private prototype_ `void OnHostTabClosed(TSharedRef<SDockTab> DockTab);` — Called when the host tab is closed (if valid)
- L440 _private prototype_ `FReply OnLockButtonClicked();` — Called when the lock button is clicked in a global find results tab
- L443 _private prototype_ `const FSlateBrush* OnGetLockButtonImage() const;` — Returns the image used for the lock button in a global find results tab
- L447 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns us
- L450 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L453 _private member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L456 _private member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L459 _private member_ `FSearchResult RootSearchResult;` — In Find Within Blueprint mode, we need to keep a handle on the root result, because it won't show up in the tree
- L462 _private member_ `FText HighlightText;` — The string to highlight in the results
- L465 _private member_ `FString SearchValue;` — The string to search for
- L468 _private member_ `TSharedPtr< class FStreamSearch> StreamSearch;` — Thread object that searches through Blueprint data on a separate thread
- L471 _private member_ `TWeakPtr< SVerticalBox > MainVerticalBox;` — Vertical box, used to add and remove widgets dynamically
- L474 _private member_ `TWeakPtr< SWidget > CacheBarSlot;` — Weak pointer to the cache bar slot, so it can be removed
- L477 _private member_ `FOnSearchComplete OnSearchComplete;` — Callback when search is complete
- L480 _private member_ `int32 OutOfDateWithLastSearchBPCount;` — Cached count of out of date Blueprints from last search.
- L483 _private member_ `EFiBVersion LastSearchedFiBVersion;` — Cached version that was last searched
- L486 _private member_ `TSharedPtr< FUICommandList > CommandList;` — Commands handled by this widget
- L489 _private member_ `TWeakPtr<SDockTab> HostTab;` — Tab hosting this widget. May be invalid.
- L492 _private member_ `mutable FSoftObjectPath LastCachedAssetPath;` — Last cached asset path (used during continuous cache operations).
- L495 _private member_ `bool bIsInFindWithinBlueprintMode;` — Should we search within the current blueprint only (rather than all blueprints)
- L498 _private member_ `bool bIsLocked;` — True if current search should not be changed by an external source
- L501 _private member_ `bool bHideProgressBars;` — True if progress bar widgets should be hidden
- L504 _private member_ `bool bShowCacheBarCloseButton;` — True if users should be allowed to close the cache bar while caching
- L507 _private member_ `bool bShowCacheBarCancelButton;` — True if users should be allowed to cancel the active caching operation
- L510 _private member_ `bool bShowCacheBarUnresponsiveEditorWarningText;` — True if the unresponsive warning text should be visible in the cache bar
- L513 _private member_ `bool bKeepCacheBarProgressVisible;` — True if cache bar should remain visible after a caching operation has ended

#### Free symbols / members of external scopes

- L40 _macro_ `#define UE_API KISMET_API`
- L57 _typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L59 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSearchComplete, TArray<FImaginaryFiBDataSharedPtr>&);`
- L59 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSearchComplete, TArray<FImaginaryFiBDataSharedPtr>&);`
- L62 _namespace_ `namespace FindInBlueprintsHelpers`
- L82 _prototype_ `UClass* GetFunctionOriginClass(const UFunction* Function);` (scope `FindInBlueprintsHelpers`) — Utility function to find the ancestor class or interface from which a function is inherited.
- L85 _prototype_ `bool ConstructSearchTermFromFunction(const UFunction* Function, FString& SearchTerm);` (scope `FindInBlueprintsHelpers`) — Constructs a search term for a function using Find-in-Blueprints search syntax
- L87 _function_ `static uint32 GetTypeHash(const FindInBlueprintsHelpers::FSimpleFTextKeyStorage& InObject)` (scope `FindInBlueprintsHelpers`)
- L93 _prototype_ `FText AsFText(TSharedPtr< FJsonValue > InJsonValue, const TMap<int32, FText>& InLookupTable);` (scope `FindInBlueprintsHelpers`) — Looks up a JsonValue's FText from the passed lookup table
- L96 _prototype_ `FText AsFText(int32 InValue, const TMap<int32, FText>& InLookupTable);` (scope `FindInBlueprintsHelpers`) — Looks up a JsonValue's FText from the passed lookup table
- L98 _prototype_ `bool IsTextEqualToString(const FText& InText, const FString& InString);` (scope `FindInBlueprintsHelpers`)
- L107 _prototype_ `FString GetPinTypeAsString(const FEdGraphPinType& InPinType);` (scope `FindInBlueprintsHelpers`) — Retrieves the pin type as a string value @param InPinType		The pin type to look at @return				The pin type as a string in format [category]'[sub-category object]'
- L117 _prototype_ `bool ParsePinType(FText InKey, FText InValue, FEdGraphPinType& InOutPinType);` (scope `FindInBlueprintsHelpers`) — Parses a pin type from passed in key names and values @param InKey					The key name for what the data should be translated as @param InValue				Value to be be translated @param InOutPinType			Modifies the PinType based on the passed parameters, building it up over multiple calls @return						TRUE when the parsing is successful
- L122 _prototype_ `void ExpandAllChildren(FSearchResult InTreeNode, TSharedPtr<STreeView<TSharedPtr<FFindInBlueprintsResult>>> InTreeView);` (scope `FindInBlueprintsHelpers`) — Iterates through all the given tree node's children and tells the tree view to expand them

### `Source/Editor/Kismet/Public/IBlueprintSelectionNotifier.h` (Public)


#### class `IBlueprintSelectionNotifier`  
`class UE_INTERNAL IBlueprintSelectionNotifier : public IModularFeature`  
_L16-32_
- inherits: `IModularFeature`
- desc: Modular feature interface for Blueprint Editor selection notifications Implemented by plugins that want to be notified when Blueprint Editor selection changes
- L19 _public function_ `static FName GetModularFeatureName()`
- L31 _public prototype_ `virtual void OnBlueprintSelectionUpdated(IAssetEditorInstance* AssetEditorInstance, UBlueprint* Blueprint, const TArray<FTypedElementHandle>& SelectedElements) = 0;` — Called when Blueprint Editor selection changes @param AssetEditorInstance The asset editor instance that triggered the selection change @param Blueprint The blueprint being edited @param SelectedElements The currently selected elements in the blueprint

### `Source/Editor/Kismet/Public/ISCSEditorCustomization.h` (Public)


#### class `ISCSEditorCustomization`  
`class ISCSEditorCustomization`  
_L14-59_
- desc: Customization class that allows per-component type handling of various SCS editor functionality.
- L17 _public prototype_ `virtual ~ISCSEditorCustomization() = default;`
- L30 _public prototype_ `virtual bool HandleViewportClick(const TSharedRef<FEditorViewportClient>& InViewportClient, class FSceneView& InView, class HHitProxy* InHitProxy, FKey InKey, EInputEvent InEvent, uint32 InHitX, uint32 InHitY) = 0;` — Process click in the viewport. @param	InViewportClient	The viewport client receiving the click @param	InView				The scene view receiving the click @param	InHitProxy			The hit proxy that was clicked @param	InKey				The key that was pressed @param	InEvent				The input event that occurred @param	InHitX				The X location of the click @param	InHitY				The Y location of the click @return true if the operation was handled.
- L42 _public prototype_ `virtual bool HandleViewportDrag(const USceneComponent* InSceneComponent, class USceneComponent* InComponentTemplate, const FVector& InDeltaTranslation, const FRotator& InDeltaRotation, const FVector& InDeltaScale, const FVector& InPivot) = 0;` — Handle drag in the viewport @param	InSceneComponent		The scene component being dragged @param	InComponentTemplate		The template corresponding to the scene component @param	InDeltaTranslation		The delta translation being applied @param	InDeltaRotation			The delta rotation being applied @param	InDeltaScale			The delta scale being applied @param	InPivot					The povot point for any transformations @return true if the operation was handled.
- L50 _public prototype_ `virtual bool HandleGetWidgetLocation(const USceneComponent* InSceneComponent, FVector& OutWidgetLocation) = 0;` — Get the widget location for this scene component @param	InSceneComponent		The scene component to get location for @param	OutWidgetLocation		The output widget location @return true if the operation was handled.
- L58 _public prototype_ `virtual bool HandleGetWidgetTransform(const USceneComponent* InSceneComponent, FMatrix& OutWidgetTransform) = 0;` — Get the widget transform for this scene component @param	InSceneComponent		The scene component to get transform for @param	OutWidgetLocation		The output widget transform @return true if the operation was handled.

### `Source/Editor/Kismet/Public/ISCSEditorUICustomization.h` (Public)


#### class `ISCSEditorUICustomization`  
`class ISCSEditorUICustomization`  
_L22-121_
- desc: SCSEditor UI customization
- L25 _public prototype_ `virtual ~ISCSEditorUICustomization() = default;`
- L28 _public function_ `virtual bool HideComponentsTree(TArrayView<UObject*> Context) const` — @return Whether to hide the components tree
- L31 _public function_ `virtual bool HideComponentsFilterBox(TArrayView<UObject*> Context) const` — @return Whether to hide the components filter box
- L34 _public function_ `virtual bool HideAddComponentButton(TArrayView<UObject*> Context) const` — @return Whether to hide the "Add Component" combo button
- L37 _public function_ `virtual bool HideBlueprintButtons(TArrayView<UObject*> Context) const` — @return Whether to hide the "Edit Blueprint" and "Blueprint/Add Script" buttons
- L44 _public function_ `virtual const FSlateBrush* GetIconBrush(const FSubobjectData&) const` — @return The icon that should be used for the given SubobjectData Implementations that return nullptr will lead to existing built-in functionality of the subobject editor being used to determine the Icon for the given FSubobjectData
- L55 _public function_ `virtual TSharedPtr<SWidget> GetControlsWidget(const FSubobjectData&) const` — `UE_DEPRECATED(5.8, "Use GetControlsWidget(TSharedRef<SSubobjectEditor>&, const FSubobjectData&")` — Allows customizer to inject a right-side justified widget on the subobject editor Typically these widgets would convey actions that can be taken and may optionally provide status information through their visualization. As an example, a subobject that is a non-native ActorComponent may provide a button via these widgets to open a code editor to the C++ version of that type. Returning nullptr will cause built-in behaviour to be used, indicating that the UICustomization does not customize this UI element. To override existing behaviour and actually show nothing, return a single null widget
- L65 _public function_ `virtual TSharedPtr<SWidget> GetControlsWidget(TSharedRef<SSubobjectEditor>& SubobjectEditor, const FSubobjectData& Data) const` — Allows customizer to inject a right-side justified widget on the subobject editor Typically these widgets would convey actions that can be taken and may optionally provide status information through their visualization. As an example, a subobject that is a non-native ActorComponent may provide a button via these widgets to open a code editor to the C++ version of that type. Returning nullptr will cause built-in behaviour to be used, indicating that the UICustomization does not customize this UI element. To override existing behaviour and actually show nothing, return a single null widget
- L79 _public function_ `virtual bool OverrideDesiredVisibility(const UE::Editor::FSubobjectEditorContext& Context, EVisibility& VisibilityOut) const` — When it returns true, overrides the value returned by SSubobjectEditor::GetDesiredVisibility(). Otherwise, it is ignored. @param VisibilityOut The visibility to return @return true if the customization wants VisibilityOut to be used.
- L85 _public function_ `virtual EChildActorComponentTreeViewVisualizationMode GetChildActorVisualizationMode() const` — @return An override for the default ChildActorComponentTreeViewVisualizationMode from the project settings, if different from UseDefault. @note Setting an override also forces child actor tree view expansion to be enabled.
- L88 _public function_ `virtual TSubclassOf<UActorComponent> GetComponentTypeFilter(TArrayView<UObject*> Context) const` — @return A component type that limits visible nodes when filtering the tree view
- L93 _public function_ `virtual bool FilterSubobjectData(TArray<FSubobjectDataHandle>& SubobjectData) const` — Optionally filter the given SubobjectDataHandles for the tree view as appropriate for this editor. @return Whether any edits were made
- L97 _public function_ `virtual bool SortSubobjectData(TArray<FSubobjectDataHandle>& SubobjectData)` — Optionally sorts the given SubobjectDataHandles for the tree view as appropriate for this editor. @return Whether any sorting was attempted
- L104 _public function_ `virtual void PrePotentialTargetChange(SSubobjectEditor& SubobjectEditor)` — Called before events that might change the targets of the subobject editor, particularly useful for gathering data to use in a subsequent SelectDefaultSubobject call.
- L112 _public function_ `virtual bool SelectDefaultSubobject(SSubobjectEditor& SubobjectEditor)` — Gives a customization the opportunity to control what the "default" subobject selection is. @return true if custom selection was performed, false if subobject editor should perform its own default selection (typically selecting root).
- L116 _public function_ `virtual bool SupportsTreeViewOverlay(const SSubobjectEditor& Editor) const` — Decides if this UI Customization provides an overlay for the tree view
- L120 _public function_ `virtual TSharedRef<class SWidget> ConstructTreeViewOverlay(TWeakPtr<class SSubobjectEditor> Editor) const` — Create an overlay for the tree view widget

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)

### `Source/Editor/Kismet/Public/ImaginaryBlueprintData.h` (Public)


#### enum `ESearchableValueStatus`  
`enum ESearchableValueStatus`  
_L28-40_
- L30 _public enumerator_ `NotSearchable = 0x00000000` — Cannot search this value, it is used for display purposes only
- L31 _public enumerator_ `Searchable = 0x00000001` — Generically searchable, value will appear as a sub-item and has no sub-data
- L32 _public enumerator_ `Hidden = 0x00000002` — Item will not be shown
- L33 _public enumerator_ `Explicit = 0x00000004` — Item must be explicitly requested via the tag
- L36 _public enumerator_ `CoreDisplayItem = Hidden | Searchable` — Core display items are searchable but should not display as sub-items because their data is presented in another fashion.
- L37 _public enumerator_ `ExplicitySearchable = Explicit | Searchable` — Will only be allowed to be found if searching using a tag
- L38 _public enumerator_ `ExplicitySearchableHidden = Explicit | Searchable | Hidden` — Will only be allowed to be found if searching using a tag but will not display the tag in the results (because it is a CoreDisplayItem)
- L39 _public enumerator_ `AllSearchable = CoreDisplayItem | ExplicitySearchable` — Covers all searchability methods

#### class `FSearchableValueInfo`  
`class FSearchableValueInfo`  
_L42-111_
- L45 _public function_ `FSearchableValueInfo() : SearchableValueStatus(ESearchableValueStatus::NotSearchable) , LookupTableKey(-1)`
- L51 _public function_ `FSearchableValueInfo(FText InDisplayKey, int32 InLookUpTableKey) : SearchableValueStatus(ESearchableValueStatus::Searchable) , DisplayKey(InDisplayKey) , LookupTableKey(InLookUpTableKey)`
- L58 _public function_ `FSearchableValueInfo(FText InDisplayKey, FText InDisplayText) : SearchableValueStatus(ESearchableValueStatus::Searchable) , DisplayKey(InDisplayKey) , LookupTableKey(-1) , DisplayText(InDisplayText)`
- L66 _public function_ `FSearchableValueInfo(FText InDisplayKey, int32 InLookUpTableKey, ESearchableValueStatus InSearchableValueStatus) : SearchableValueStatus(InSearchableValueStatus) , DisplayKey(InDisplayKey) , LookupTableKey(InLookUpTableKey)`
- L73 _public function_ `FSearchableValueInfo(FText InDisplayKey, FText InDisplayText, ESearchableValueStatus InSearchableValueStatus) : SearchableValueStatus(InSearchableValueStatus) , DisplayKey(InDisplayKey) , LookupTableKey(-1) , DisplayText(InDisplayText)`
- L82 _public function_ `bool IsSearchable() const` — Returns TRUE if the data is searchable
- L85 _public function_ `bool IsCoreDisplay() const` — Returns TRUE if the item should be treated as a CoreDisplayItem, which is searchable but not displayed
- L88 _public function_ `bool IsExplicitSearchable() const` — Returns TRUE if the item should only be searchable if explicitly searched for using the tag
- L91 _public prototype_ `FText GetDisplayText(const TMap<int32, FText>& InLookupTable) const;` — Returns the display text to use for this item
- L94 _public function_ `FText GetDisplayKey() const` — Returns the display key for this item
- L101 _protected member_ `ESearchableValueStatus SearchableValueStatus;` — The searchability status of this item
- L104 _protected member_ `FText DisplayKey;` — Key that this item is associated with, used for display purposes
- L107 _protected member_ `int32 LookupTableKey;` — Key to use to lookup into a table if DisplayText does not override
- L110 _protected member_ `FText DisplayText;` — Text value to use instead of a lookup into the table

#### struct `FComponentUniqueDisplay`  
`struct FComponentUniqueDisplay`  
_L114-124_
- desc: Struct to contain search results and help compare them for uniqueness.
- L116 _public function_ `FComponentUniqueDisplay( FSearchResult InSearchResult ) : SearchResult(InSearchResult)`
- L120 _public prototype_ `bool operator==(const FComponentUniqueDisplay& Other);`
- L123 _public member_ `FSearchResult SearchResult;` — Search result contained and used for comparing of uniqueness

#### class `FImaginaryFiBData`  
`class FImaginaryFiBData : public ITextFilterExpressionContext, public TSharedFromThis<FImaginaryFiBData, ESPMode::ThreadSafe>`  
_L126-266_
- inherits: `ITextFilterExpressionContext,TSharedFromThis<FImaginaryFiBData,ESPMode::ThreadSafe>`
- L129 _public prototype_ `FImaginaryFiBData(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject = TSharedPtr<FJsonObject>(), TMap<int32, FText>* InLookupTablePtr = nullptr);`
- L133 _public function_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override` — We don't actually use these overrides, see FFiBContextHelper for how we call the alternate functions. These will assert if they are accidentally called.
- L134 _public function_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override`
- L138 _public function_ `virtual bool IsCategory() const` — Returns TRUE if this item is a category type, which helps to organize child data
- L141 _public function_ `virtual bool IsTagAndValueCategory() const` — Returns TRUE if this item is considered a Tag and Value category, where it's contents should be considered no different than the parent owner
- L144 _public function_ `virtual bool ShouldSearchChildKeys(TSharedPtr<FJsonObject> ChildNode) const` — Returns TRUE if the child item's keys should be searchable.
- L147 _public function_ `virtual bool AreKeysSearchable() const` — Returns TRUE if this item's keys should be searchable. For example if they don't represent property names, but values. Introduced for TMap keys.
- L150 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const;` — Checks if the filter is compatible with the current object, returns TRUE by default
- L153 _public prototype_ `virtual bool CanCallFilter(ESearchQueryFilter InSearchQueryFilter) const;` — Checks if the filter can call functions for the passed filter, returns FALSE by default if the filter is not the AllFilter
- L156 _public prototype_ `void ParseAllChildData(ESearchableValueStatus InSearchabilityOverride = ESearchableValueStatus::Searchable);` — Parses, in a thread-safe manner, all child data, non-recursively, so children will be left in an unparsed Json state
- L159 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode, TMultiMap< const FImaginaryFiBData*, FComponentUniqueDisplay >& InOutMatchingSearchComponents) const;` — Test the given value against the strings extracted from the current item. Will return the matching search components if any (can return TRUE without having any if the search components are hidden)
- L162 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode, TMultiMap< const FImaginaryFiBData*, FComponentUniqueDisplay >& InOutMatchingSearchComponents) const;` — Perform a complex expression test for the current item. Will return the matching search components if any (can return TRUE without having any if the search components are hidden)
- L165 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const;` — Returns the UObject represented by this Imaginary data give the UBlueprint owner.
- L168 _public function_ `virtual UBlueprint* GetBlueprint() const` — This will return and force load the UBlueprint that owns this object data.
- L178 _public prototype_ `FSearchResult CreateSearchResult(FSearchResult InParent) const;` — Requests internal creation of the search result and properly initializes the visual representation of the result
- L181 _public function_ `const TArray<FImaginaryFiBDataSharedPtr>& GetAllParsedChildData() const` — Accessor for the parsed child data for this item
- L187 _public function_ `void AddKeyValuePair(FText InKey, FSearchableValueInfo& InValue)` — Adds a KeyValue pair to the ParsedTagAndValues map
- L193 _public function_ `FImaginaryFiBDataWeakPtr GetOuter() const` — Returns the Outer of this Imaginary data that directly owns it
- L199 _public function_ `void EnableInterlockedParsing()` — Called to enable interlocked parsing (only allow one thread at a time). In place to support backwards-compatibility with non-deferred indexing, may be removed later.
- L205 _public prototype_ `void DumpParsedObject(FArchive& Ar, int32 InTreeLevel = 0) const;` — Dumps the parsed object (including all children) to the given archive
- L208 _public prototype_ `static FSearchResult CreateSearchTree(FSearchResult InParentSearchResult, FImaginaryFiBDataWeakPtr InCurrentPointer, TArray< const FImaginaryFiBData* >& InValidSearchResults, TMultiMap< const FImaginaryFiBData*, FComponentUniqueDisplay >& InMatchingSearchComponents);` — Builds a SearchTree ready to be displayed in the Find-in-Blueprints window
- L218 _protected function_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue)` — Checks if the Key has any special handling to be done, such as making a Pin out of it @param InKey			Key that the JsonValue was stored under @param InJsonValue	JsonValue to be specially parsed @return				TRUE if the JsonValue was specially handled, will not be further handled
- L221 _protected function_ `virtual ESearchableValueStatus GetSearchabilityStatus(FString InKey)` — Returns the searchability status of a passed in Key, all Keys are searchable by default
- L224 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const = 0;` — Protected internal function which builds the search result for this item
- L227 _protected prototype_ `FText CreateSearchComponentDisplayText(FText InKey, FText InValue) const;` — Creates a display string for this item in search results
- L230 _protected prototype_ `void ParseJsonValue(FText InKey, FText InDisplayKey, TSharedPtr< FJsonValue > InJsonValue, TArray<FSearchableValueInfo>& OutParsedValues, bool bIsInArray = false, ESearchableValueStatus InSearchabilityOverride = ESearchableValueStatus::Searchable);` — Helper function for parsing Json values into usable properties
- L233 _protected prototype_ `virtual void ParseAllChildData_Internal(ESearchableValueStatus InSearchabilityOverride = ESearchableValueStatus::Searchable);` — Internal version of the ParseAllChildData function, handles the bulk of the work
- L236 _protected function_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const` — Internal helper function for dumping parsed object info
- L240 _protected member_ `TSharedPtr< FJsonObject > UnparsedJsonObject;` — The unparsed Json object representing this item. Auto-cleared after parsing. Does not need to be declared as thread-safe because it's only accessed when parsing and that is already a critical section.
- L243 _protected member_ `TArray<FImaginaryFiBDataSharedPtr> ParsedChildData;` — All parsed child data for this item. Must be declared as thread-safe because it may be accessed on different threads.
- L246 _protected member_ `TMultiMap< FindInBlueprintsHelpers::FSimpleFTextKeyStorage, FSearchableValueInfo > ParsedTagsAndValues;` — A mapping of tags to their values and searchability status
- L249 _protected member_ `TMap<int32, FText>* LookupTablePtr;` — Pointer to the lookup table to decompressed the Json strings back into fully formed FTexts
- L252 _protected member_ `FImaginaryFiBDataWeakPtr Outer;` — Outer of this object that owns it, used for climbing up the hierarchy. Must be declared as thread-safe because it may be accessed on different threads.
- L255 _protected member_ `TAtomic<bool> bHasParsedJsonObject;` — Set after the JSON object has been parsed.
- L258 _protected member_ `bool bRequiresInterlockedParsing;` — Set if this instance requires interlocked parsing.
- L261 _protected member_ `static FCriticalSection ParseChildDataCriticalSection;` — Allows for thread-safe parsing of the imaginary data. Only a single Imaginary data can be parsed at a time.
- L265 _private member_ `FSearchResult SearchResultTemplate;` — If display meta is present, this will cache those values and is then used as a basis when constructing a search result tree

#### class `FFiBMetaData`  
`class FFiBMetaData : public FImaginaryFiBData`  
_L268-302_
- inherits: `FImaginaryFiBData`
- L271 _public prototype_ `FFiBMetaData(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L274 _public function_ `bool IsHidden() const` — Returns TRUE if the metadata is informing that the FProperty and children should be hidden
- L282 _public function_ `bool IsExplicit() const` — Returns TRUE if the metadata is informing that the FProperty and children should be explicit
- L289 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FImaginaryFiBData Interface
- L290 _protected function_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override`
- L298 _private member_ `bool bIsHidden;` — TRUE if the FProperty this metadata represents is hidden
- L301 _private member_ `bool bIsExplicit;` — TRUE if the FProperty this metadata represents is explicit, should always be true if bIsHidden is true

#### enum `ECategorySectionHelperFlags`  
`enum class ECategorySectionHelperFlags : uint8`  
_L305-310_
- desc: Flags to control the UX while caching
- L307 _public enumerator_ `None = 0`
- L308 _public enumerator_ `IsTagAndValue = 1 << 0` — See bIsTagAndValue
- L309 _public enumerator_ `AreKeysSearchable = 1 << 1` — See bAreKeysSearchable

#### class `FCategorySectionHelper`  
`class FCategorySectionHelper : public FImaginaryFiBData`  
_L314-361_
- inherits: `FImaginaryFiBData`
- L318 _public prototype_ `DECLARE_DELEGATE_TwoParams(FCategorySectionHelperCallback, TSharedPtr< FJsonObject >, TArray<FImaginaryFiBDataSharedPtr>&);` — Callback declaration for handling special parsing of the items in the category
- L320 _public prototype_ `FCategorySectionHelper(FImaginaryFiBDataWeakPtr InOuter, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory);`
- L321 _public prototype_ `FCategorySectionHelper(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory);`
- L322 _public prototype_ `FCategorySectionHelper(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory, FCategorySectionHelperCallback InSpecialHandlingCallback);`
- L323 _public prototype_ `FCategorySectionHelper(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, ECategorySectionHelperFlags Flags);`
- L326 _public function_ `virtual bool IsCategory() const override` — FImaginaryFiBData Interface
- L327 _public function_ `virtual bool AreKeysSearchable() const`
- L328 _public function_ `virtual bool IsTagAndValueCategory() const override`
- L329 _public prototype_ `virtual bool CanCallFilter(ESearchQueryFilter InSearchQueryFilter) const override;`
- L333 _public function_ `FString GetCategoryFunctionName() const` — Returns the category name prepared for checking as a function
- L340 _public prototype_ `FString GetCategoryPath() const;` — Recursively visits outer categories and constructs a path name: Outermost.Outer.ThisCategoryName. Intended for debugging. Halts as soon as a non-category is visited.
- L344 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;` — FImaginaryFiBData Interface
- L345 _protected prototype_ `virtual void ParseAllChildData_Internal(ESearchableValueStatus InSearchabilityOverride ) override;`
- L346 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L351 _protected member_ `FCategorySectionHelperCallback SpecialHandlingCallback;` — Callback to specially handle parsing of the Json Object instead of using generic handling
- L354 _protected member_ `FText CategoryName;` — The display text for this item in the search results
- L357 _protected member_ `uint8 bIsTagAndValue:1;` — TRUE if this category should be considered no different than a normal Tag and Value in it's parent
- L360 _protected member_ `uint8 bAreKeysSearchable:1;` — TRUE if this category's keys should be searchable

#### class `FImaginaryBlueprint`  
`class FImaginaryBlueprint : public FImaginaryFiBData`  
_L364-397_
- inherits: `FImaginaryFiBData`
- desc: An "imaginary" representation of a UBlueprint, featuring raw strings or other imaginary objects in the place of more structured substances
- L367 _public prototype_ `FImaginaryBlueprint(const FString& InBlueprintName, const FString& InBlueprintPath, const FString& InBlueprintParentClass, const TArray<FString>& InInterfaces, const FString& InUnparsedStringData, FSearchDataVersionInfo InVersionInfo);`
- L370 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface
- L371 _public prototype_ `virtual bool CanCallFilter(ESearchQueryFilter InSearchQueryFilter) const override;`
- L372 _public prototype_ `virtual UBlueprint* GetBlueprint() const override;`
- L377 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FImaginaryFiBData Interface
- L378 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;`
- L379 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L383 _protected prototype_ `void ParseGraph( TSharedPtr< FJsonValue > InJsonValue, FString InCategoryTitle, EGraphType InGraphType );` — Helper function to parse an array of Json Object representing graphs
- L386 _protected prototype_ `void ParseComponents(TSharedPtr< FJsonObject > InJsonObject, TArray<FImaginaryFiBDataSharedPtr>& OutParsedChildData);` — Callback to specially parse an array of Json Objects representing components
- L389 _protected prototype_ `void ParseToJson(FSearchDataVersionInfo InVersionInfoconst, const FString& UnparsedStringData);` — Parses a raw string of Json to a Json object hierarchy
- L393 _protected member_ `FString BlueprintPath;` — The path for this Blueprint
- L396 _protected member_ `TMap<int32, FText> LookupTable;` — Lookup table used as a compression tool for the FTexts stored in the Json object

#### class `FImaginaryGraph`  
`class FImaginaryGraph : public FImaginaryFiBData`  
_L400-421_
- inherits: `FImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraph, featuring raw strings or other imaginary objects in the place of more structured substances
- L403 _public prototype_ `FImaginaryGraph(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, EGraphType InGraphType);`
- L406 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface
- L407 _public prototype_ `virtual bool CanCallFilter(ESearchQueryFilter InSearchQueryFilter) const override;`
- L412 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FImaginaryFiBData Interface
- L413 _protected prototype_ `virtual ESearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L414 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;`
- L415 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L420 _protected member_ `EGraphType GraphType;` — The graph type being represented

#### class `FImaginaryGraphNode`  
`class FImaginaryGraphNode : public FImaginaryFiBData`  
_L424-446_
- inherits: `FImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraphNode, featuring raw strings or other imaginary objects in the place of more structured substances
- L427 _public prototype_ `FImaginaryGraphNode(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L430 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface
- L431 _public prototype_ `virtual bool CanCallFilter(ESearchQueryFilter InSearchQueryFilter) const override;`
- L436 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FImaginaryFiBData Interface
- L437 _protected prototype_ `virtual ESearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L438 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;`
- L439 _protected prototype_ `virtual void ParseAllChildData_Internal(ESearchableValueStatus InSearchabilityOverride ) override;`
- L440 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L445 _private member_ `FString SchemaName;` — Schema name that manages this node

#### class `FImaginaryProperty`  
`class FImaginaryProperty : public FImaginaryFiBData`  
_L449-470_
- inherits: `FImaginaryFiBData`
- desc: An "imaginary" representation of a FProperty, featuring raw strings or other imaginary objects in the place of more structured substances
- L452 _public prototype_ `FImaginaryProperty(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L455 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface
- L456 _public prototype_ `virtual void ParseAllChildData_Internal(ESearchableValueStatus InSearchabilityOverride) override;`
- L457 _public prototype_ `virtual bool ShouldSearchChildKeys(TSharedPtr<FJsonObject> ChildNode) const override;`
- L462 _protected prototype_ `virtual ESearchableValueStatus GetSearchabilityStatus(FString InKey) override;` — FImaginaryFiBData Interface
- L463 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;`
- L464 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L469 _private member_ `uint8 bIsStructProperty:1;` — TRUE if this property's metadata's PinCategory was PC_Struct. If so, it can represent a struct, or a TMap whose key type is a struct.

#### class `FImaginaryComponent`  
`class FImaginaryComponent : public FImaginaryProperty`  
_L473-481_
- inherits: `FImaginaryProperty`
- desc: An "imaginary" representation of a FProperty of an instanced component, featuring raw strings or other imaginary objects in the place of more structured substances
- L476 _public prototype_ `FImaginaryComponent(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L479 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface

#### class `FImaginaryPin`  
`class FImaginaryPin : public FImaginaryFiBData`  
_L484-504_
- inherits: `FImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraphPin, featuring raw strings or other imaginary objects in the place of more structured substances
- L487 _public prototype_ `FImaginaryPin(FImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FString InSchemaName);`
- L490 _public prototype_ `virtual bool IsCompatibleWithFilter(ESearchQueryFilter InSearchQueryFilter) const override;` — FImaginaryFiBData Interface
- L495 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue);` — FImaginaryFiBData Interface
- L496 _protected prototype_ `virtual ESearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L497 _protected prototype_ `virtual FSearchResult CreateSearchResult_Internal(FSearchResult InTemplate) const override;`
- L498 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L503 _private member_ `FString SchemaName;` — Schema name that manages this pin

#### Free symbols / members of external scopes

- L312 _prototype_ `ENUM_CLASS_FLAGS(ECategorySectionHelperFlags);`
- L318 _delegate_ `DECLARE_DELEGATE_TwoParams(FCategorySectionHelperCallback, TSharedPtr< FJsonObject >, TArray<FImaginaryFiBDataSharedPtr>&);` — Callback declaration for handling special parsing of the items in the category

### `Source/Editor/Kismet/Public/MyBlueprintItemDragDropAction.h` (Public)


#### class `FMyBlueprintItemDragDropAction`  
`class FMyBlueprintItemDragDropAction : public FGraphSchemaActionDragDropAction`  
_L24-66_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: DragDropAction class for drag and dropping an item from the My Blueprints tree (e.g., variable or function)
- L27 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMyBlueprintItemDragDropAction, FGraphSchemaActionDragDropAction)`
- L31 _public prototype_ `virtual FReply DroppedOnCategory(FText Category) override;`
- L32 _public prototype_ `virtual void HoverTargetChanged() override;`
- L36 _public function_ `void SetAltDrag(bool InIsAltDrag)` — Set if operation is modified by alt
- L39 _public function_ `void SetCtrlDrag(bool InIsCtrlDrag)` — Set if operation is modified by the ctrl key
- L43 _protected prototype_ `FMyBlueprintItemDragDropAction();` — Constructor
- L45 _protected function_ `virtual UBlueprint* GetSourceBlueprint() const`
- L51 _protected function_ `bool IsFromBlueprint(UBlueprint* InBlueprint) const` — Helper method to see if we're dragging in the same blueprint
- L56 _protected prototype_ `void SetFeedbackMessageError(const FText& Message);`
- L57 _protected prototype_ `void SetFeedbackMessageOK(const FText& Message);`
- L61 _protected member_ `bool bControlDrag;` — Was ctrl held down at start of drag
- L63 _protected member_ `bool bAltDrag;` — Was alt held down at the start of drag
- L65 _protected member_ `FNodeCreationAnalytic AnalyticCallback;` — Analytic delegate to track node creation

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/ReplaceNodeReferencesHelper.h` (Public)


#### struct `FReplaceNodeReferencesHelper`  
`struct FReplaceNodeReferencesHelper : FTickableEditorObject`  
_L22-99_
- inherits: `FTickableEditorObject`
- desc: A helper class for Replacing Variable references in blueprints
- L25 _public prototype_ `FReplaceNodeReferencesHelper(const FMemberReference& Source, const FMemberReference& Replacement, UBlueprint* InBlueprint);` — Constructs a ReplaceNodeReferencesHelper with the specified Source and Replacement variables
- L28 _public prototype_ `FReplaceNodeReferencesHelper(FMemberReference&& Source, FMemberReference&& Replacement, UBlueprint* InBlueprint);` — Constructs a ReplaceNodeReference Helper with the specified Source and Replacement variables
- L30 _public prototype_ `virtual ~FReplaceNodeReferencesHelper();`
- L33 _public prototype_ `void BeginFindAndReplace(const FSimpleDelegate& InOnCompleted = FSimpleDelegate());` — Triggers a FindInBlueprints cache of all blueprints, and submits a search query when it is done, this could take a while
- L36 _public prototype_ `void ReplaceReferences(TArray<FImaginaryFiBDataSharedPtr>& InRawDataList);` — Callback to replace references when Search is completed
- L39 _public function_ `bool IsCompleted() const` — Returns true when the Find/Replace operation is finished
- L42 _public function_ `const FMemberReference& GetSource() const` — Returns the MemberReference for the Source
- L45 _public function_ `const FMemberReference& GetReplacement() const` — Returns the MemberReference for the Replacement
- L48 _public prototype_ `const void SetTransaction(TSharedPtr<FScopedTransaction> InTransaction);` — Keeps a scoped transaction alive while it does it's job (call with nullptr to reset if needed)
- L51 _public prototype_ `virtual bool IsTickable() const override;`
- L53 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L55 _public prototype_ `virtual TStatId GetStatId() const override;`
- L66 _public prototype_ `static void ReplaceReferences(const FMemberReference& InSource, const FMemberReference& InReplacement, UBlueprint* InBlueprint, TArray<FImaginaryFiBDataSharedPtr>& InRawDataList);` — Helper function to replace references @param InSource		Variable reference to replace @param InReplacement Variable reference to replace with @param InBlueprint   Blueprint that InReplacement belongs to @param InRawDataList Raw find in blueprints search results
- L71 _private prototype_ `void OnSubmitSearchQuery();` — Submits a search query and calls ReplaceReferences when complete
- L74 _private prototype_ `void UpdateSearchQuery();` — Updates the active search and ends it when complete
- L77 _private member_ `FMemberReference SourceReference;` — The source variable to be replaced
- L80 _private member_ `FMemberReference ReplacementReference;` — The variable to replace references to the source with
- L83 _private member_ `UBlueprint* Blueprint;` — The Class that owns the variables
- L86 _private member_ `FSimpleDelegate OnCompleted;` — Callback for when the FindAndReplace is completed
- L89 _private member_ `TUniquePtr<FScopedSlowTask> SlowTask;` — Used when starting a full find and replace task
- L92 _private member_ `TSharedPtr<FStreamSearch> StreamSearch;` — In Progress Search Object
- L95 _private member_ `TSharedPtr<FScopedTransaction> Transaction;` — Transaction if the user wants us to keep one alive
- L98 _private member_ `bool bCompleted;` — Whether a search has been started and finished

### `Source/Editor/Kismet/Public/ReviewComments.h` (Public)


#### enum `EReviewCommentTaskState`  
`enum class EReviewCommentTaskState : uint8`  
_L11-21_
- reflection: `UENUM()`
- L14 _public enumerator_ `Comment` — regular comment (not a task)
- L16 _public enumerator_ `Open` — unaddressed task
- L18 _public enumerator_ `Addressed` — completed task
- L20 _public enumerator_ `Verified` — verified completed task (documentation is limited so I'm not positive on this one)

#### enum `EReviewTopicType`  
`enum class EReviewTopicType : uint8`  
_L25-34_
- reflection: `UENUM()`
- desc: swarm stores shelved file reviews separately from comments on submitted CLs
- L28 _public enumerator_ `Review` — shelved for review
- L30 _public enumerator_ `Change` — change is already submitted
- L33 _public enumerator_ `Unrecognised` — this should never happen

#### struct `FReviewCommentContext`  
`struct FReviewCommentContext`  
_L36-60_
- L40 _public member_ `TOptional<FString> File;` — file being commented on
- L42 _public member_ `TOptional<int32> Version;` — what version of the file this comment is associated with
- L44 _public member_ `TOptional<TArray<FString>> Content;` — (text only) preview of text being commented on
- L46 _public member_ `TOptional<int32> LeftLine;` — (text only) line number on left panel of this comment
- L48 _public member_ `TOptional<int32> RightLine;` — (text only) line number on right panel of this comment
- L51 _public member_ `TOptional<int32> ReplyTo;` — id of the comment that this one is replying to
- L54 _public member_ `TOptional<FString> Category;` — category this comment will appear under in the diff results
- L56 _public prototype_ `FString ToJson() const;`
- L57 _public prototype_ `TSharedPtr<FJsonObject> ToJsonObject() const;`
- L58 _public prototype_ `static FReviewCommentContext FromJson(const FString& Json);`
- L59 _public prototype_ `static FReviewCommentContext FromJson(const TSharedPtr<FJsonObject>& JsonObject);`

#### struct `FReviewTopic`  
`struct FReviewTopic`  
_L62-75_
- L65 _public member_ `FString ChangelistNum;`
- L66 _public member_ `EReviewTopicType TopicType;`
- L69 _public prototype_ `FString ToString() const;` — returns topic in format "TopicType/ChangelistNum"
- L70 _public prototype_ `static FReviewTopic FromString(const FString& ReviewTopic);`
- L71 _public function_ `bool operator==(const FReviewTopic& Other) const`

#### struct `FReviewComment`  
`struct FReviewComment`  
_L82-117_
- L86 _public member_ `TOptional<FReviewTopic> Topic;` — info about CL being commented on
- L88 _public member_ `TOptional<int32> CommentID;` — unique id associated with this comment
- L90 _public member_ `TOptional<FString> Body;` — the comment text
- L93 _public member_ `TOptional<TSet<FString>> Likes;` — names of all users who have liked this comment
- L95 _public member_ `TOptional<TSet<FString>> ReadBy;` — names of all users who have marked the comment as read
- L97 _public member_ `TOptional<EReviewCommentTaskState> TaskState;` — signifies whether this is a task and if it's been addressed
- L99 _public member_ `TOptional<FString> User;` — comment author
- L101 _public member_ `TOptional<FDateTime> CreatedTime;` — when the comment was created
- L103 _public member_ `TOptional<FDateTime> EditedTime;` — when the comment was last edited
- L105 _public member_ `TOptional<FDateTime> UpdatedTime;` — when the comment was created
- L108 _public member_ `FReviewCommentContext Context;` — metadata about the comment
- L111 _public member_ `bool bIsClosed : 1 = false;` — flags
- L113 _public prototype_ `FString ToJson() const;`
- L114 _public prototype_ `TSharedPtr<FJsonObject> ToJsonObject() const;`
- L115 _public prototype_ `static FReviewComment FromJson(const FString& Json);`
- L116 _public prototype_ `static FReviewComment FromJson(const TSharedPtr<FJsonObject>& JsonObject);`

#### class `IReviewCommentAPI`  
`class IReviewCommentAPI : public TSharedFromThis<IReviewCommentAPI>`  
_L119-142_
- inherits: `TSharedFromThis<IReviewCommentAPI>`
- L122 _public prototype_ `DECLARE_DELEGATE_TwoParams(OnGetCommentsComplete, const TArray<FReviewComment>&, const FString& ) DECLARE_DELEGATE_TwoParams(OnPostCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnEditCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnGetReviewTopicForCLComplete, const FReviewTopic&, const FString& ) virtual ~IReviewCommentAPI() = default;`
- L130 _public prototype_ `virtual FString GetUsername() const = 0;` — returns the name of the user logged in
- L132 _public prototype_ `virtual void GetComments(const FReviewTopic& Topic, const OnGetCommentsComplete& OnComplete) const = 0;`
- L134 _public prototype_ `virtual void PostComment(FReviewComment& Comment, const OnPostCommentComplete& OnComplete, bool bSilenceNotification = false) const = 0;` — Body must be set; username will get set by PostComment
- L136 _public prototype_ `virtual void EditComment(const FReviewComment& Comment, const OnEditCommentComplete& OnComplete, bool bSilenceNotification = false) const = 0;` — all unset members will be left unchanged.
- L139 _public prototype_ `virtual void GetReviewTopicForCL(const FString &ChangelistNum, const OnGetReviewTopicForCLComplete& OnComplete) const = 0;` — retrieves the review associated with a CL.
- L141 _public prototype_ `virtual void GetOrCreateReviewTopicForCL(const FString &ChangelistNum, const OnGetReviewTopicForCLComplete& OnComplete) const = 0;` — retrieves the review associated with a CL. If there is none, it creates a new review and returns that.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API KISMET_API`
- L77 _function_ `inline uint32 GetTypeHash(const FReviewTopic& Topic)`
- L122 _delegate_ `DECLARE_DELEGATE_TwoParams(OnGetCommentsComplete, const TArray<FReviewComment>&, const FString& ) DECLARE_DELEGATE_TwoParams(OnPostCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnEditCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnGetReviewTopicForCLComplete, const FReviewTopic&, const FString& ) virtual ~IReviewCommentAPI() = default;`
- L123 _delegate_ `DECLARE_DELEGATE_TwoParams(OnPostCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnEditCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnGetReviewTopicForCLComplete, const FReviewTopic&, const FString& ) virtual ~IReviewCommentAPI() = default;`
- L124 _delegate_ `DECLARE_DELEGATE_TwoParams(OnEditCommentComplete, const FReviewComment&, const FString& ) DECLARE_DELEGATE_TwoParams(OnGetReviewTopicForCLComplete, const FReviewTopic&, const FString& ) virtual ~IReviewCommentAPI() = default;`
- L125 _delegate_ `DECLARE_DELEGATE_TwoParams(OnGetReviewTopicForCLComplete, const FReviewTopic&, const FString& ) virtual ~IReviewCommentAPI() = default;`

### `Source/Editor/Kismet/Public/SBlueprintDiff.h` (Public)


#### struct `FDiffResultItem`  
`struct FDiffResultItem : public TSharedFromThis<FDiffResultItem>`  
_L58-65_
- inherits: `TSharedFromThis<FDiffResultItem>`
- desc: Individual Diff item shown in the list of diffs
- L60 _public function_ `FDiffResultItem(FDiffSingleResult InResult) : Result(InResult)`
- L62 _public member_ `FDiffSingleResult Result;`
- L64 _public prototype_ `TSharedRef<SWidget> GenerateWidget() const;`

#### struct `FDiffPanel`  
`struct FDiffPanel`  
_L78-138_
- desc: Panel used to display the blueprint
- L80 _public prototype_ `FDiffPanel();`
- L83 _public prototype_ `void InitializeDiffPanel();` — Initializes the panel, can be moved into constructor if diff and merge clients are made more uniform:
- L86 _public prototype_ `void GeneratePanel(UEdGraph* NewGraph, UEdGraph* OldGraph);` — Generate a panel for NewGraph diffed against OldGraph
- L89 _public prototype_ `void GeneratePanel(UEdGraph* Graph, TSharedPtr<TArray<FDiffSingleResult>> DiffResults, TAttribute<int32> FocusedDiffResult);` — Generate a panel that displays the Graph and reflects the items in the DiffResults
- L92 _public prototype_ `TSharedRef<class SWidget> GenerateMyBlueprintWidget();` — Generate the 'MyBlueprint' widget, which is private to this module
- L95 _public prototype_ `void CopySelectedNodes();` — Called when user hits keyboard shortcut to copy nodes
- L98 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;` — Gets whatever nodes are selected in the Graph Editor
- L101 _public prototype_ `bool CanCopyNodes() const;` — Can user copy any of the selected nodes?
- L104 _public prototype_ `void FocusDiff(UEdGraphPin& Pin);` — Functions used to focus/find a particular change in a diff result
- L105 _public prototype_ `void FocusDiff(UEdGraphNode& Node);`
- L107 _public prototype_ `TSharedRef<SWidget> GetMyBlueprintWidget() const;`
- L108 _public prototype_ `TSharedRef<SWidget> GetDetailsWidget() const;`
- L111 _public member_ `const UBlueprint* Blueprint;` — The blueprint that owns the graph we are showing
- L114 _public member_ `TSharedPtr<SBox> GraphEditorBox;` — The box around the graph editor, used to change the content when new graphs are set
- L117 _public member_ `TSharedPtr<class SMyBlueprint> MyBlueprint;` — The actual my blueprint panel, used to regenerate the panel when the new graphs are set
- L120 _public member_ `TSharedPtr<class SKismetInspector> DetailsView;` — The details view associated with the graph editor
- L123 _public member_ `TWeakPtr<class SGraphEditor> GraphEditor;` — The graph editor which does the work of displaying the graph
- L126 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this blueprint
- L129 _public member_ `bool bShowAssetName;` — True if we should show a name identifying which asset this panel is displaying
- L132 _public member_ `TSharedPtr<SWidget> OverlayGraphRevisionInfo;` — The widget that contains the revision info in graph mode
- L134 _public member_ `TSharedPtr<SLinkableScrollBar> DetailScrollbar;`
- L137 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel

#### class `SBlueprintDiff`  
`class SBlueprintDiff: public SCompoundWidget`  
_L141-323_
- inherits: `SCompoundWidget`
- desc: Visual Diff between two Blueprints
- L144 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOpenInDefaults, const class UBlueprint* , const class UBlueprint* );`
- L146 _public function_ `SLATE_BEGIN_ARGS( SBlueprintDiff )`
- L147 _public prototype_ `SLATE_ARGUMENT( const class UBlueprint*, BlueprintOld ) SLATE_ARGUMENT( const class UBlueprint*, BlueprintNew ) SLATE_ARGUMENT( struct FRevisionInfo, OldRevision ) SLATE_ARGUMENT( struct FRevisionInfo, NewRevision ) SLATE_ARGUMENT( bool, ShowAssetNames ) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L156 _public prototype_ `virtual ~SBlueprintDiff();`
- L158 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L161 _public prototype_ `void OnGraphChanged(FGraphToDiff* Diff);` — Called when a new Graph is clicked on by user
- L164 _public prototype_ `void OnBlueprintChanged(UBlueprint* InBlueprint);` — Called when blueprint is modified
- L167 _public prototype_ `void OnGraphSelectionChanged(TSharedPtr<FGraphToDiff> Item, ESelectInfo::Type SelectionType);` — Called when user clicks on a new graph list item
- L170 _public prototype_ `void OnDiffListSelectionChanged(TSharedPtr<struct FDiffResultItem> TheDiff);` — Called when user clicks on an entry in the listview of differences
- L173 _public prototype_ `static TSharedRef<SWidget> DefaultEmptyPanel();` — Helper function for generating an empty widget
- L176 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(FText WindowTitle, const UBlueprint* OldBlueprint, const UBlueprint* NewBlueprint, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision);` — Helper function to create a window that holds a diff widget
- L179 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow(const UBlueprint* OldBlueprint, const UBlueprint* NewBlueprint, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision, const UClass* BlueprintClass);` — Helper function to create a window that holds a diff widget that defaults a window title
- L183 _protected prototype_ `void NextDiff();` — Called when user clicks button to go to next difference
- L186 _protected prototype_ `void PrevDiff();` — Called when user clicks button to go to prev difference
- L189 _protected prototype_ `bool HasNextDiff() const;` — Called to determine whether we have a list of differences to cycle through
- L190 _protected prototype_ `bool HasPrevDiff() const;`
- L193 _protected prototype_ `FGraphToDiff* FindGraphToDiffEntry(const FString& GraphPath);` — Find the FGraphToDiff that displays the graph with GraphPath relative path
- L196 _protected prototype_ `void FocusOnGraphRevisions(FGraphToDiff* Diff);` — Bring these revisions of graph into focus on main display
- L199 _protected prototype_ `void CreateGraphEntry(class UEdGraph* GraphOld, class UEdGraph* GraphNew);` — Create a list item entry graph that exists in at least one of the blueprints
- L202 _protected prototype_ `void DisablePinDiffFocus();` — Disable the focus on a particular pin
- L205 _protected prototype_ `void OnToggleLockView();` — User toggles the option to lock the views between the two blueprints
- L208 _protected prototype_ `void OnToggleSplitViewMode();` — User toggles the option to change the split view mode betwwen vertical and horizontal
- L211 _protected prototype_ `void ResetGraphEditors();` — Reset the graph editor, called when user switches graphs to display
- L214 _protected prototype_ `FSlateIcon GetLockViewImage() const;` — Get the image to show for the toggle lock option
- L217 _protected prototype_ `FSlateIcon GetSplitViewModeImage() const;` — Get the image to show for the toggle split view mode option
- L220 _protected member_ `TArray<TSharedPtr<FGraphToDiff>> Graphs;` — List of graphs to diff, are added to panel last
- L223 _protected prototype_ `FDiffPanel& GetDiffPanelForNode(UEdGraphNode& Node);` — Get Graph editor associated with this Graph
- L226 _protected prototype_ `void HandleGraphChanged(FGraphToDiff* Diff);` — Event handler that updates the graph view when user selects a new graph
- L229 _protected prototype_ `void GenerateDifferencesList();` — Function used to generate the list of differences and the widgets needed to calculate that list
- L232 _protected prototype_ `bool IsGraphDiffNeeded(class UEdGraph* InGraph) const;` — Checks if a graph is valid for diffing
- L235 _protected prototype_ `void OnCloseAssetEditor(UObject* Asset, EAssetEditorCloseReason CloseReason);` — Called when editor may need to be closed
- L249 _protected prototype_ `FDiffControl GenerateBlueprintTypePanel();`
- L250 _protected prototype_ `FDiffControl GenerateMyBlueprintPanel();`
- L251 _protected prototype_ `FDiffControl GenerateGraphPanel();`
- L252 _protected prototype_ `FDiffControl GenerateDefaultsPanel();`
- L253 _protected prototype_ `FDiffControl GenerateClassSettingsPanel();`
- L254 _protected prototype_ `FDiffControl GenerateComponentsPanel();`
- L255 _protected prototype_ `FDiffControl GenerateGeneralFileCommentEntries();`
- L257 _protected prototype_ `TSharedRef<SOverlay> GenerateGraphWidgetForPanel(FDiffPanel& OutDiffPanel) const;`
- L258 _protected prototype_ `TSharedRef<SBox> GenerateRevisionInfoWidgetForPanel(TSharedPtr<SWidget>& OutGeneratedWidget,const FText& InRevisionText) const;`
- L261 _protected prototype_ `void SetCurrentMode(FName NewMode);` — Accessor and event handler for toggling between diff view modes (defaults, components, graph view, interface, macro):
- L262 _protected function_ `FName GetCurrentMode() const`
- L263 _protected prototype_ `void OnModeChanged(const FName& InNewViewMode) const;`
- L265 _protected prototype_ `void UpdateTopSectionVisibility(const FName& InNewViewMode) const;`
- L267 _protected member_ `FName CurrentMode;`
- L270 _protected member_ `FDiffPanel PanelOld, PanelNew;` — The two panels used to show the old & new revision
- L270 _protected member_ `FDiffPanel PanelOld, PanelNew;` — The two panels used to show the old & new revision
- L273 _protected member_ `TSharedPtr<FAsyncDetailViewDiff> GraphDetailDiff;` — Diff info about the kismet panels in blueprint graph diff view
- L276 _protected member_ `bool bLockViews;` — If the two views should be locked
- L279 _protected member_ `bool bVerticalSplitGraphMode = true;` — If the view on Graph Mode should be divided vertically
- L282 _protected member_ `TSharedPtr<SBox> ModeContents;` — Contents widget that we swap when mode changes (defaults, components, etc)
- L284 _protected member_ `TSharedPtr<SSplitter> TopRevisionInfoWidget;`
- L286 _protected member_ `TSharedPtr<SSplitter> DiffGraphSplitter;`
- L288 _protected member_ `TSharedPtr<SSplitter> GraphToolBarWidget;`
- L293 _protected member_ `TSharedPtr<FTabManager> TabManager;` — We can't use the global tab manager because we need to instance the diff control, so we have our own tab manager:
- L296 _protected member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > PrimaryDifferencesList;` — Tree of differences collected across all panels:
- L299 _protected member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > RealDifferences;` — List of all differences, cached so that we can iterate only the differences and not labels, etc:
- L302 _protected member_ `TSharedPtr< STreeView< TSharedPtr< FBlueprintDifferenceTreeEntry > > > DifferencesTreeView;` — Tree view that displays the differences, cached for the buttons that iterate the differences:
- L305 _protected member_ `TMap<FName, FDiffControl> ModePanels;` — Stored references to widgets used to display various parts of a blueprint, from the mode name
- L308 _protected member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window holding this
- L310 _protected member_ `FDelegateHandle AssetEditorCloseDelegate;`
- L322 _protected member_ `} ScopedCategorySortChange;`

#### struct `SBlueprintDiff::FDiffControl`  
`struct FDiffControl`  
_L237-247_
- L239 _public function_ `FDiffControl() : Widget() , DiffControl(nullptr)`
- L245 _public member_ `TSharedPtr<SWidget> Widget;`
- L246 _public member_ `TSharedPtr< class IDiffControl > DiffControl;`

#### class `SBlueprintDiff::FScopedCategorySortChange`  
`class FScopedCategorySortChange`  
_L314-322_
- desc: To make diffing more accurate and friendly, UBlueprint::CategorySorting gets modified. this will revert to the old version when the window closes
- L317 _public prototype_ `~FScopedCategorySortChange();`
- L318 _public prototype_ `void SetBlueprint(UBlueprint* Blueprint);`
- L320 _private member_ `UBlueprint* Blueprint = nullptr;`
- L321 _private member_ `TArray<FName> Backup = {};`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API KISMET_API`
- L67 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMyBlueprintActionSelected, UObject*);`
- L67 _prototype_ `DECLARE_DELEGATE_OneParam(FOnMyBlueprintActionSelected, UObject*);`
- L69 _namespace_ `namespace DiffWidgetUtils`
- L71 _prototype_ `void SelectNextRow(SListView< TSharedPtr< struct FDiffSingleResult> >& ListView, const TArray< TSharedPtr< struct FDiffSingleResult > >& ListViewSource );` (scope `DiffWidgetUtils`)
- L72 _prototype_ `void SelectPrevRow(SListView< TSharedPtr< struct FDiffSingleResult> >& ListView, const TArray< TSharedPtr< struct FDiffSingleResult > >& ListViewSource );` (scope `DiffWidgetUtils`)
- L73 _prototype_ `bool HasNextDifference(SListView< TSharedPtr< struct FDiffSingleResult> >& ListView, const TArray< TSharedPtr< struct FDiffSingleResult > >& ListViewSource);` (scope `DiffWidgetUtils`)
- L74 _prototype_ `bool HasPrevDifference(SListView< TSharedPtr< struct FDiffSingleResult> >& ListView, const TArray< TSharedPtr< struct FDiffSingleResult > >& ListViewSource);` (scope `DiffWidgetUtils`)
- L144 _delegate_ `DECLARE_DELEGATE_TwoParams( FOpenInDefaults, const class UBlueprint* , const class UBlueprint* );`

### `Source/Editor/Kismet/Public/SBlueprintEditorSelectedDebugObjectWidget.h` (Public)


#### struct `FBlueprintDebugObjectInstance`  
`struct FBlueprintDebugObjectInstance`  
_L37-77_
- L40 _public member_ `TWeakObjectPtr<UObject> ObjectPtr;` — Actual object to debug, can be null
- L43 _public member_ `FString ObjectLabel;` — Friendly label for object to debug
- L46 _public member_ `FString ObjectPath;` — Raw object path of spawned PIE object, this is not a SoftObjectPath because we don't want it to get fixed up
- L49 _public member_ `FString EditorObjectPath;` — Object path to object in the editor, will only be set for static objects
- L51 _public member_ `bool bPinned;`
- L53 _public function_ `FBlueprintDebugObjectInstance(TWeakObjectPtr<UObject> InPtr, const FString& InLabel) : ObjectPtr(InPtr) , ObjectLabel(InLabel) , bPinned(false)`
- L61 _public function_ `bool IsEmptyObject() const` — Returns true if this is the special entry for no specific object
- L67 _public function_ `bool IsSpawnedObject() const` — If this has no editor path, it was spawned
- L73 _public function_ `bool IsEditorObject() const` — If editor and object path are the same length because there's no prefix, this is the editor object

#### class `SBlueprintEditorSelectedDebugObjectWidget`  
`class SBlueprintEditorSelectedDebugObjectWidget : public SCompoundWidget`  
_L79-180_
- inherits: `SCompoundWidget`
- L82 _public function_ `SLATE_BEGIN_ARGS(SBlueprintEditorSelectedDebugObjectWidget)`
- L85 _public prototype_ `virtual ~SBlueprintEditorSelectedDebugObjectWidget();`
- L87 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FBlueprintEditor> InBlueprintEditor);`
- L90 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L94 _public prototype_ `void AddDebugObject(UObject* TestObject, const FString& TestObjectName = FString());` — Adds an object to the list of debug choices
- L97 _private function_ `UBlueprint* GetBlueprintObj() const`
- L100 _private prototype_ `void GenerateDebugObjectInstances(bool bRestoreSelection);` — Creates a list of all debug objects
- L103 _private prototype_ `void GenerateDebugWorldNames(bool bRestoreSelection);` — Generate list of active PIE worlds to debug
- L106 _private prototype_ `void OnRefresh();` — Refresh the widget.
- L109 _private prototype_ `TSharedPtr<FBlueprintDebugObjectInstance> GetDebugObjectInstance() const;` — Returns the entry for the current debug actor
- L112 _private prototype_ `TSharedPtr<FString> GetDebugWorldName() const;` — Returns the name of the current debug actor
- L115 _private prototype_ `void DebugObjectSelectionChanged(TSharedPtr<FBlueprintDebugObjectInstance> NewSelection, ESelectInfo::Type SelectInfo);` — Handles the selection changed event for the debug actor combo box
- L117 _private prototype_ `void DebugWorldSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L120 _private prototype_ `void SelectedDebugObject_OnClicked();` — Called when user clicks button to select the current object being debugged
- L123 _private prototype_ `bool IsDebugObjectSelected() const;` — Returns true if a debug actor is currently selected
- L125 _private prototype_ `EVisibility IsDebugWorldComboVisible() const;`
- L128 _private prototype_ `static const FString& GetNoDebugString();` — Returns the string to indicate no debug object is selected
- L130 _private prototype_ `const FString& GetDebugAllWorldsString() const;`
- L132 _private prototype_ `TSharedRef<SWidget> OnGetActiveDetailSlotContent(bool bChangedToHighDetail);`
- L135 _private prototype_ `FString MakeDebugObjectLabel(UObject* TestObject, bool bAddContextIfSelectedInEditor, bool bAddSpawnedContext) const;` — Helper method to construct a debug object label string
- L138 _private prototype_ `void FillDebugObjectInstance(TSharedPtr<FBlueprintDebugObjectInstance> Instance);` — Fills in data for a specific instance
- L141 _private prototype_ `TSharedRef<SWidget> CreateDebugObjectItemWidget(TSharedPtr<FBlueprintDebugObjectInstance> InItem);` — Called to create a widget for each debug object item
- L144 _private prototype_ `FText GetSelectedDebugObjectTextLabel() const;` — Returns the combo button label to use for the currently-selected debug object item
- L147 _private prototype_ `void HandleOnDebugObjectAccess(UObject* InDebugObject);` — Handle selection of debug object through debug object access.
- L150 _private prototype_ `void SortDebugObjects();` — Sorts the debug objects based on pinned status.
- L153 _private prototype_ `const FSlateBrush* GetDebugObjectItemWidgetPinBrush(TWeakPtr<FBlueprintDebugObjectInstance> InInstanceWeak) const;` — Returns either a pinned or unpinned image based on object pin status.
- L156 _private prototype_ `EVisibility GetDebugObjectItemWidgetPinVisibility(TWeakPtr<FBlueprintDebugObjectInstance> InInstanceWeak, TWeakPtr<SWidget> InRowWidgetWeak) const;` — Returns Visible if the item is pinned or hovered.
- L159 _private prototype_ `FReply OnDebugObjectItemWidgetPinMouseDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, TWeakPtr<FBlueprintDebugObjectInstance> InInstanceWeak);` — Pins or unpins the debug object.
- L163 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditor;` — Pointer back to the blueprint editor tool that owns us
- L165 _private member_ `static TSharedRef<FBlueprintDebugObjectInstance> NoDebugInstance;`
- L168 _private member_ `TArray<TSharedPtr<FBlueprintDebugObjectInstance>> DebugObjects;` — Lists of actors of a given blueprint type and their names
- L171 _private member_ `TArray< TWeakObjectPtr<UWorld> > DebugWorlds;` — PIE worlds that we can debug
- L172 _private member_ `TArray< TSharedPtr<FString> > DebugWorldNames;`
- L175 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FBlueprintDebugObjectInstance>>> DebugObjectsComboBox;` — Widget containing the names of all possible debug actors. This is a "generic" SComboBox rather than an STextComboBox so that we can customize the label on the combo button widget.
- L177 _private member_ `TSharedPtr<STextComboBox> DebugWorldsComboBox;`
- L179 _private member_ `TWeakObjectPtr<UObject> LastObjectObserved;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/SBlueprintEditorToolbar.h` (Public)


#### class `FKismet2Menu`  
`class FKismet2Menu`  
_L34-49_
- desc: Kismet menu
- L37 _public prototype_ `static void SetupBlueprintEditorMenu(const FName MainMenuName);`
- L40 _protected prototype_ `static void FillFileMenuBlueprintSection(UToolMenu* Menu);`
- L42 _protected prototype_ `static void FillEditMenu(UToolMenu* Menu);`
- L44 _protected prototype_ `static void FillViewMenu(UToolMenu* Menu);`
- L46 _protected prototype_ `static void FillDebugMenu(UToolMenu* Menu);`
- L48 _protected prototype_ `static void FillDeveloperMenu(UToolMenu* Menu);`

#### class `FFullBlueprintEditorCommands`  
`class FFullBlueprintEditorCommands : public TCommands<FFullBlueprintEditorCommands>`  
_L52-79_
- inherits: `TCommands<FFullBlueprintEditorCommands>`
- L56 _public function_ `FFullBlueprintEditorCommands() : TCommands<FFullBlueprintEditorCommands>("FullBlueprintEditor", NSLOCTEXT("Contexts", "FullBlueprintEditor", "Full Blueprint Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L62 _public member_ `TSharedPtr<FUICommandInfo> Compile;` — Compile the blueprint
- L63 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Never;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_SuccessOnly;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Always;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> JumpToErrorNode;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> SwitchToScriptingMode;` — Switch between modes in the blueprint editor
- L70 _public member_ `TSharedPtr<FUICommandInfo> SwitchToBlueprintDefaultsMode;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> SwitchToComponentsMode;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> EditGlobalOptions;` — Edit Blueprint global options
- L75 _public member_ `TSharedPtr<FUICommandInfo> EditClassDefaults;`
- L78 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FBlueprintEditorToolbar`  
`class FBlueprintEditorToolbar : public TSharedFromThis<FBlueprintEditorToolbar>`  
_L83-109_
- inherits: `TSharedFromThis<FBlueprintEditorToolbar>`
- L86 _public function_ `FBlueprintEditorToolbar(TSharedPtr<FBlueprintEditor> InBlueprintEditor) : BlueprintEditor(InBlueprintEditor)`
- L89 _public prototype_ `void AddBlueprintGlobalOptionsToolbar(UToolMenu* InMenu, bool bRegisterViewport = false);`
- L90 _public prototype_ `void AddCompileToolbar(UToolMenu* InMenu);`
- L91 _public prototype_ `void AddNewToolbar(UToolMenu* InMenu);`
- L92 _public prototype_ `void AddScriptingToolbar(UToolMenu* InMenu);`
- L93 _public prototype_ `void AddDebuggingToolbar(UToolMenu* InMenu);`
- L96 _public prototype_ `FSlateIcon GetStatusImage() const;` — Returns the current status icon for the blueprint being edited
- L99 _public prototype_ `FText GetStatusTooltip() const;` — Returns the current status as text for the blueprint being edited
- L102 _public prototype_ `static void DiffAgainstRevision(class UBlueprint* Current, int32 OldRevision);` — Diff current blueprint against the specified revision
- L104 _public prototype_ `static TSharedRef<SWidget> MakeDiffMenu(const UBlueprintEditorToolMenuContext* InContext);`
- L108 _protected member_ `TWeakPtr<FBlueprintEditor> BlueprintEditor;` — Pointer back to the blueprint editor tool that owns us

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/SBlueprintNamespaceEntry.h` (Public)


#### class `SBlueprintNamespaceEntry`  
`class SBlueprintNamespaceEntry : public SCompoundWidget`  
_L40-123_
- inherits: `SCompoundWidget`
- desc: A custom widget class that provides support for Blueprint namespace entry and/or selection.
- L43 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnNamespaceSelected, const FString&);`
- L44 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGetNamespacesToExclude, TSet<FString>&);`
- L46 _public function_ `SLATE_BEGIN_ARGS(SBlueprintNamespaceEntry) : _Font(FCoreStyle::Get().GetFontStyle(TEXT("NormalFont"))) , _AllowTextEntry(true)`
- L51 _public prototype_ `SLATE_ARGUMENT(FString, CurrentNamespace) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ARGUMENT(bool, AllowTextEntry) SLATE_NAMED_SLOT(FArguments, ButtonContent) SLATE_EVENT(FOnNamespaceSelected, OnNamespaceSelected) SLATE_EVENT(FOnGetNamespacesToExclude, OnGetNamespacesToExclude) SLATE_ATTRIBUTE(FText, ExcludedNamespaceTooltipText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Current namespace value.
- L80 _public prototype_ `void SetCurrentNamespace(const FString& InNamespace);` — Set the current namespace to the given identifier. @param InNamespace	New namespace identifier. May be an empty string.
- L90 _protected prototype_ `void OnTextChanged(const FText& InText);`
- L91 _protected prototype_ `void OnTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L92 _protected prototype_ `void OnShowingSuggestions(const FString& InputText, TArray<FString>& OutSuggestions);`
- L93 _protected prototype_ `TSharedRef<SWidget> OnGetNamespaceTreeMenuContent();`
- L94 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRowForNamespaceTreeItem(TSharedPtr<FPathTreeNodeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L95 _protected prototype_ `void OnGetChildrenForNamespaceTreeItem(TSharedPtr<FPathTreeNodeItem> Item, TArray<TSharedPtr<FPathTreeNodeItem>>& OutChildren);`
- L96 _protected prototype_ `void OnNamespaceTreeFilterTextChanged(const FText& InText);`
- L97 _protected prototype_ `void OnNamespaceTreeSelectionChanged(TSharedPtr<FPathTreeNodeItem> Item, ESelectInfo::Type SelectInfo);`
- L98 _protected prototype_ `bool OnIsNamespaceTreeItemSelectable(TSharedPtr<FPathTreeNodeItem> Item) const;`
- L99 _protected prototype_ `FText GetCurrentNamespaceText() const;`
- L101 _protected prototype_ `void PopulateNamespaceTree();`
- L102 _protected prototype_ `void SelectNamespace(const FString& InNamespace);`
- L103 _protected prototype_ `void ExpandAllTreeViewItems(const TArray<TSharedPtr<FPathTreeNodeItem>>* NodeListPtr = nullptr);`
- L104 _protected prototype_ `const TSharedPtr<FPathTreeNodeItem>* FindTreeViewNode(const FString& NodePath, const TArray<TSharedPtr<FPathTreeNodeItem>>* NodeListPtr = nullptr) const;`
- L107 _private member_ `FString CurrentNamespace;`
- L108 _private member_ `TArray<FString> AllRegisteredPaths;`
- L109 _private member_ `TSet<FString> ExcludedTreeViewPaths;`
- L110 _private member_ `TArray<TSharedPtr<FPathTreeNodeItem>> RootNodes;`
- L112 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L113 _private member_ `TSharedPtr<SSuggestionTextBox> TextBox;`
- L114 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L115 _private member_ `TSharedPtr<STreeView<TSharedPtr<FPathTreeNodeItem>>> TreeView;`
- L117 _private member_ `FOnNamespaceSelected OnNamespaceSelected;`
- L118 _private member_ `FOnGetNamespacesToExclude OnGetNamespacesToExclude;`
- L119 _private member_ `TAttribute<FText> ExcludedNamespaceTooltipText;`
- L121 _private member_ `static float NamespaceListBorderPadding;`
- L122 _private member_ `static float NamespaceListMinDesiredWidth;`

#### struct `SBlueprintNamespaceEntry::FPathTreeNodeItem`  
`struct FPathTreeNodeItem`  
_L83-88_
- L85 _public member_ `FString NodePath;`
- L86 _public member_ `TArray<TSharedPtr<FPathTreeNodeItem>> ChildNodes;`
- L87 _public member_ `bool bIsSelectable = true;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define UE_API KISMET_API`
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNamespaceSelected, const FString&);`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetNamespacesToExclude, TSet<FString>&);`

### `Source/Editor/Kismet/Public/SBlueprintRevisionMenu.h` (Public)


#### class `SBlueprintRevisionMenu`  
`class SBlueprintRevisionMenu : public SCompoundWidget`  
_L25-64_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SBlueprintRevisionMenu) : _bIncludeLocalRevision(false)`
- L33 _public prototype_ `SLATE_ARGUMENT(bool, bIncludeLocalRevision) SLATE_EVENT(FOnRevisionSelected, OnRevisionSelected) SLATE_END_ARGS() ~SBlueprintRevisionMenu();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, UBlueprint const* Blueprint);`
- L43 _private prototype_ `EVisibility GetInProgressVisibility() const;` — Delegate used to determine the visibility 'in progress' widgets
- L45 _private prototype_ `EVisibility GetCancelButtonVisibility() const;` — Delegate used to determine the visibility of the cancel button
- L48 _private prototype_ `FReply OnCancelButtonClicked() const;` — Delegate used to cancel a source control operation in progress
- L50 _private prototype_ `void OnSourceControlQueryComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Callback for when the source control operation is complete
- L53 _private member_ `bool bIncludeLocalRevision;`
- L55 _private member_ `FOnRevisionSelected OnRevisionSelected;`
- L57 _private member_ `FString Filename;` — The name of the file we want revision info for
- L59 _private member_ `TSharedPtr<SVerticalBox> MenuBox;` — The box we are using to display our menu
- L61 _private member_ `TSharedPtr<FUpdateStatus, ESPMode::ThreadSafe> SourceControlQueryOp;` — The source control operation in progress
- L63 _private member_ `uint32 SourceControlQueryState;` — The state of the SCC query

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API KISMET_API`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRevisionSelected, FRevisionInfo const&) public: SLATE_BEGIN_ARGS(SBlueprintRevisionMenu) : _bIncludeLocalRevision(false) {} SLATE_ARGUMENT(bool, bIncludeLocalRevision) SLATE_EVENT(FOnRevisionSelected, OnRevisionSelected) SLATE_END_ARGS() ~SBlueprintRevisionMenu();`

### `Source/Editor/Kismet/Public/SCSDiff.h` (Public)


#### class `FSCSDiff`  
`class FSCSDiff`  
_L21-44_
- desc: Struct to support diffing the component tree for a blueprint
- L24 _public prototype_ `FSCSDiff(const class UBlueprint* InBlueprint);`
- L26 _public prototype_ `void HighlightProperty(FName VarName, FPropertySoftPath Property);`
- L27 _public prototype_ `TSharedRef< SWidget > TreeWidget();`
- L29 _public prototype_ `TArray< FSCSResolvedIdentifier > GetDisplayedHierarchy() const;`
- L31 _public function_ `const UBlueprint* GetBlueprint() const`
- L34 _protected prototype_ `void OnSCSEditorUpdateSelectionFromNodes(const TArray<TSharedPtr<FSubobjectEditorTreeNode>>& SelectedNodes);`
- L35 _protected prototype_ `void OnSCSEditorHighlightPropertyInDetailsView(const class FPropertyPath& InPropertyPath);`
- L38 _private member_ `TSharedPtr< class SWidget > ContainerWidget;`
- L39 _private member_ `TSharedPtr< class SSubobjectBlueprintEditor > SubobjectEditor;`
- L40 _private member_ `TSharedPtr< class SKismetInspector > Inspector;`
- L43 _private member_ `UBlueprint* Blueprint = nullptr;` — Blueprint we are inspecting

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/SDetailsDiff.h` (Public)


#### struct `FDetailsDiffPanel`  
`struct FDetailsDiffPanel`  
_L21-37_
- desc: Panel used to display the details
- L24 _public member_ `const UObject* Object = nullptr;` — The asset that owns the details view we are showing
- L27 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this asset
- L30 _public member_ `bool bShowAssetName = true;` — True if we should show a name identifying which asset this panel is displaying
- L33 _public member_ `TSharedPtr<SWidget> OverlayRevisionInfo;` — The widget that contains the revision info in graph mode
- L36 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel

#### class `SDetailsDiff`  
`class SDetailsDiff: public SCompoundWidget`  
_L40-185_
- inherits: `SCompoundWidget`
- desc: Visual Diff between two Assets
- L44 _public function_ `DECLARE_DELEGATE_OneParam(FOnCustomizeDetailsWidget, const TSharedRef<IDetailsView>&) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRowHighlightColor, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) SLATE_BEGIN_ARGS(SDetailsDiff)`
- L51 _public prototype_ `SLATE_ARGUMENT(const class UObject*, OldAsset) SLATE_ARGUMENT(const class UObject*, NewAsset) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TSharedPtr<IDetailPropertyExtensionHandler>, ExtensionHandler) SLATE_EVENT(FOnCustomizeDetailsWidget, OnCustomizeDetailsWidget) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntries, OnGenerateCustomDiffEntries) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntryWidget, OnGenerateCustomDiffEntryWidget) SLATE_EVENT(DiffUtils::FOnOrganizeDiffEntries, OnOrganizeDiffEntries) SLATE_EVENT(FShouldHighlightRow, ShouldHighlightRow) SLATE_EVENT(FRowHighlightColor, RowHighlightColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L68 _public prototype_ `virtual ~SDetailsDiff();`
- L70 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L73 _public prototype_ `void OnDiffListSelectionChanged(TSharedPtr<struct FDiffResultItem> TheDiff);` — Called when user clicks on an entry in the listview of differences
- L76 _public prototype_ `static TSharedRef<SWidget> DefaultEmptyPanel();` — Helper function for generating an empty widget
- L79 _public prototype_ `static TSharedRef<SDetailsDiff> CreateDiffWindow(FText WindowTitle, const UObject* OldObject, const UObject* NewObject, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision);` — Helper function to create a window that holds a diff widget
- L82 _public prototype_ `static TSharedRef<SDetailsDiff> CreateDiffWindow(const UObject* OldObject, const UObject* NewObject, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision, const UClass* ObjectClass);` — Helper function to create a window that holds a diff widget (default window title)
- L85 _public prototype_ `void SetOutputObject(UObject* OutputObject);` — Enables actions like "Choose Left" and "Choose Right" which will modify the OutputObject
- L88 _public prototype_ `UObject* GetOutputObject() const;` — Return a serialized buffer of change requests made by the user
- L91 _public prototype_ `bool IsOutputEnabled() const;` — Returns whether SetOutputObject was called with a valid object
- L93 _public prototype_ `void ReportMergeConflicts(const TMap<FString, TMap<FPropertySoftPath, ETreeDiffResult>>& Conflicts);`
- L95 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWindowClosedEvent, TSharedRef<SDetailsDiff>) FOnWindowClosedEvent OnWindowClosedEvent;`
- L99 _protected prototype_ `void NextDiff();` — Called when user clicks button to go to next difference
- L102 _protected prototype_ `void PrevDiff();` — Called when user clicks button to go to prev difference
- L105 _protected prototype_ `bool HasNextDiff() const;` — Called to determine whether we have a list of differences to cycle through
- L106 _protected prototype_ `bool HasPrevDiff() const;`
- L109 _protected prototype_ `void GenerateDifferencesList();` — Function used to generate the list of differences and the widgets needed to calculate that list
- L112 _protected prototype_ `void OnCloseAssetEditor(UObject* Asset, EAssetEditorCloseReason CloseReason);` — Called when editor may need to be closed
- L114 _protected prototype_ `void OnObjectReplaced(const FCoreUObjectDelegates::FReplacementObjectMap& Replacements);`
- L128 _protected prototype_ `FDiffControl GenerateDetailsPanel(const TFunction<const UObject*(const UObject*)>& Redirector = nullptr);`
- L130 _protected prototype_ `TSharedRef<SBox> GenerateRevisionInfoWidgetForPanel(TSharedPtr<SWidget>& OutGeneratedWidget,const FText& InRevisionText) const;`
- L133 _protected prototype_ `void SetCurrentMode(FName NewMode);` — Accessor and event handler for toggling between diff view modes (defaults, components, graph view, interface, macro):
- L134 _protected prototype_ `void RefreshCurrentModePanel();`
- L135 _protected function_ `FName GetCurrentMode() const`
- L136 _protected prototype_ `void OnModeChanged(const FName& InNewViewMode) const;`
- L138 _protected prototype_ `void UpdateTopSectionVisibility(const FName& InNewViewMode) const;`
- L140 _protected member_ `FName CurrentMode;`
- L143 _protected member_ `FDetailsDiffPanel PanelOld;` — The two panels used to show the old & new revision
- L144 _protected member_ `FDetailsDiffPanel PanelNew;`
- L147 _protected member_ `UObject* OutputObject = nullptr;` — If set, actions like "Choose Left" and "Choose Right" will be enabled and modify the OutputObject
- L149 _protected prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSetOutputObjectEvent) FOnSetOutputObjectEvent OnOutputObjectSetEvent;`
- L152 _protected member_ `FOnCustomizeDetailsWidget OnCustomizeDetailsWidget;`
- L153 _protected member_ `DiffUtils::FOnGenerateCustomDiffEntries OnGenerateCustomDiffEntries;`
- L154 _protected member_ `DiffUtils::FOnGenerateCustomDiffEntryWidget OnGenerateCustomDiffEntryWidget;`
- L155 _protected member_ `DiffUtils::FOnOrganizeDiffEntries OnOrganizeDiffEntries;`
- L156 _protected member_ `FShouldHighlightRow ShouldHighlightRow;`
- L157 _protected member_ `FRowHighlightColor RowHighlightColor;`
- L160 _protected member_ `TSharedPtr<SBox> ModeContents;` — Contents widget that we swap when mode changes (defaults, components, etc)
- L162 _protected member_ `TSharedPtr<SSplitter> TopRevisionInfoWidget;`
- L165 _protected member_ `TSharedPtr<FTabManager> TabManager;` — We can't use the global tab manager because we need to instance the diff control, so we have our own tab manager:
- L168 _protected member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > PrimaryDifferencesList;` — Tree of differences collected across all panels:
- L171 _protected member_ `TArray< TSharedPtr<class FBlueprintDifferenceTreeEntry> > RealDifferences;` — List of all differences, cached so that we can iterate only the differences and not labels, etc:
- L174 _protected member_ `TSharedPtr< STreeView< TSharedPtr< FBlueprintDifferenceTreeEntry > > > DifferencesTreeView;` — Tree view that displays the differences, cached for the buttons that iterate the differences:
- L177 _protected member_ `TMap<FName, FDiffControl> ModePanels;` — Stored references to widgets used to display various parts of an object, from the mode name
- L180 _protected member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window holding this
- L182 _protected member_ `FDelegateHandle AssetEditorCloseDelegate;`
- L184 _protected member_ `TMap<FString, TMap<FPropertySoftPath, ETreeDiffResult>> MergeConflicts;`

#### struct `SDetailsDiff::FDiffControl`  
`struct FDiffControl`  
_L116-126_
- L118 _public function_ `FDiffControl() : Widget() , DiffControl(nullptr)`
- L124 _public member_ `TSharedPtr<SWidget> Widget;`
- L125 _public member_ `TSharedPtr< class IDiffControl > DiffControl;`

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCustomizeDetailsWidget, const TSharedRef<IDetailsView>&) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRowHighlightColor, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) SLATE_BEGIN_ARGS(SDetailsDiff) {} SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetOld, 5.5, "Use OldAsset instead") SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetNew, 5.5, "Use NewAsset instead") SLATE_ARGUMENT(const class UObject*, OldAsset) SLATE_ARGUMENT(const class UObject*, NewAsset) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TSharedPtr<IDetailPropertyExtensionHandler>, ExtensionHandler) SLATE_EVENT(FOnCustomizeDetailsWidget, OnCustomizeDetailsWidget) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntries, OnGenerateCustomDiffEntries) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntryWidget, OnGenerateCustomDiffEntryWidget) SLATE_EVENT(DiffUtils::FOnOrganizeDiffEntries, OnOrganizeDiffEntries) SLATE_EVENT(FShouldHighlightRow, ShouldHighlightRow) SLATE_EVENT(FRowHighlightColor, RowHighlightColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L45 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRowHighlightColor, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) SLATE_BEGIN_ARGS(SDetailsDiff) {} SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetOld, 5.5, "Use OldAsset instead") SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetNew, 5.5, "Use NewAsset instead") SLATE_ARGUMENT(const class UObject*, OldAsset) SLATE_ARGUMENT(const class UObject*, NewAsset) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TSharedPtr<IDetailPropertyExtensionHandler>, ExtensionHandler) SLATE_EVENT(FOnCustomizeDetailsWidget, OnCustomizeDetailsWidget) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntries, OnGenerateCustomDiffEntries) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntryWidget, OnGenerateCustomDiffEntryWidget) SLATE_EVENT(DiffUtils::FOnOrganizeDiffEntries, OnOrganizeDiffEntries) SLATE_EVENT(FShouldHighlightRow, ShouldHighlightRow) SLATE_EVENT(FRowHighlightColor, RowHighlightColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldHighlightRow, const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>&) SLATE_BEGIN_ARGS(SDetailsDiff) {} SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetOld, 5.5, "Use OldAsset instead") SLATE_ARGUMENT_DEPRECATED(const class UObject*, AssetNew, 5.5, "Use NewAsset instead") SLATE_ARGUMENT(const class UObject*, OldAsset) SLATE_ARGUMENT(const class UObject*, NewAsset) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TSharedPtr<IDetailPropertyExtensionHandler>, ExtensionHandler) SLATE_EVENT(FOnCustomizeDetailsWidget, OnCustomizeDetailsWidget) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntries, OnGenerateCustomDiffEntries) SLATE_EVENT(DiffUtils::FOnGenerateCustomDiffEntryWidget, OnGenerateCustomDiffEntryWidget) SLATE_EVENT(DiffUtils::FOnOrganizeDiffEntries, OnOrganizeDiffEntries) SLATE_EVENT(FShouldHighlightRow, ShouldHighlightRow) SLATE_EVENT(FRowHighlightColor, RowHighlightColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L95 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWindowClosedEvent, TSharedRef<SDetailsDiff>) FOnWindowClosedEvent OnWindowClosedEvent;`
- L149 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSetOutputObjectEvent) FOnSetOutputObjectEvent OnOutputObjectSetEvent;`

### `Source/Editor/Kismet/Public/SFilterableObjectList.h` (Public)


#### class `SFilterableObjectList`  
`class SFilterableObjectList : public SCompoundWidget`  
_L40-101_
- inherits: `SCompoundWidget`
- L43 _public function_ `SLATE_BEGIN_ARGS( SFilterableObjectList )`
- L46 _public prototype_ `void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `void InternalConstruct();`
- L52 _protected prototype_ `virtual void RebuildObjectList();` — Interface for derived classes to implement
- L53 _protected prototype_ `virtual FString GetSearchableText(UObject* Object);`
- L71 _protected prototype_ `virtual FListRow GenerateRowForObject(UObject* Object);` — Make a table row for the list of filterable widgets
- L76 _protected prototype_ `void RefilterObjectList();`
- L78 _protected prototype_ `TSharedRef<ITableRow> OnGenerateTableRow(UObject* InData, const TSharedRef<STableViewBase>& OwnerTable);`
- L80 _protected prototype_ `FReply OnRefreshButtonClicked();`
- L82 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L84 _protected prototype_ `EVisibility GetFilterStatusVisibility() const;`
- L85 _protected prototype_ `FText GetFilterStatusText() const;`
- L87 _protected prototype_ `bool IsFilterActive() const;`
- L88 _protected prototype_ `void ReapplyFilter();`
- L91 _protected member_ `TSharedPtr< SListView<UObject*> > ObjectListWidget;` — Widget containing the object list
- L94 _protected member_ `TSharedPtr< SSearchBox > FilterTextBoxWidget;` — Widget containing the filtering text box
- L97 _protected member_ `TArray<UObject*> LoadedObjectList;` — List of objects that can be shown
- L100 _protected member_ `TArray<UObject*> FilteredObjectList;` — List of objects to show that have passed the keyword filtering

#### struct `SFilterableObjectList::FListRow`  
`struct FListRow`  
_L56-68_
- desc: Return value for GenerateRowForObject
- L58 _public function_ `FListRow( const TSharedRef<SWidget>& InWidget, const FOnDragDetected& OnDragDetected ) : Widget(InWidget) , OnDragDetected_Handler( OnDragDetected )`
- L65 _public member_ `TSharedRef<SWidget> Widget;` — The widget to place into the table row.
- L67 _public member_ `FOnDragDetected OnDragDetected_Handler;` — The Delegate to invoke when the user started dragging a row.

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/SFixupSelfContextDlg.h` (Public)


#### struct `FFixupSelfContextItem`  
`struct FFixupSelfContextItem`  
_L31-56_
- L43 _public function_ `FFixupSelfContextItem(FName Function) : FuncName(Function)` — Constructs a FixupSelfContextItem for a given function name
- L46 _public prototype_ `TSharedRef<SWidget> CreateWidget(TArray<TSharedPtr<FString>>& InFixupOptions);` — Callback to create a widget for the Item
- L49 _public member_ `FName FuncName;` — Function this item relates to
- L52 _public member_ `TArray<UK2Node_CallFunction*> Nodes;` — Nodes that reference this function
- L55 _public member_ `TSharedPtr<STextComboBox> ComboBox;` — Combo box for user to decide fixup strategy

#### enum `FFixupSelfContextItem::EFixupStrategy`  
`enum class EFixupStrategy`  
_L35-40_
- desc: Enum to describe how the node will be fixed up (or not)
- L37 _public enumerator_ `DoNothing`
- L38 _public enumerator_ `CreateNewFunction`
- L39 _public enumerator_ `RemoveNode`

#### class `SFixupSelfContextDialog`  
`class SFixupSelfContextDialog : public SCompoundWidget`  
_L59-125_
- inherits: `SCompoundWidget`
- desc: Widget to prompt the user to fixup self context on bad K2Node_CallFunction Pastes
- L62 _private typedef_ `typedef TSharedPtr<FFixupSelfContextItem> FListViewItem;`
- L64 _public function_ `SLATE_BEGIN_ARGS(SFixupSelfContextDialog)`
- L66 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<UK2Node_CallFunction*>& InNodesToFixup, UBlueprint* InFromBP, const FBlueprintEditor* InBlueprintEditorPtr, bool bInOtherPastedNodes);`
- L79 _public prototype_ `static bool CreateModal(const TArray<UK2Node_CallFunction*>& NodesToFixup, UBlueprint* InFromBP, const FBlueprintEditor* BlueprintEditorPtr, bool bOtherPastedNodes);` — Creates a Confirmation Modal, this function will not return until the Dialog is closed @param NodesToFixup Array of unresolved function nodes @param InFromBP	The blueprint that the function was copied from @param BlueprintEditorPtr the BlueprintEditor this modal was created by @param bOtherPastedNodes Whether other nodes were involved in this paste operation @returns True if the user confirmed the operation, False if it was canceled
- L83 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FListViewItem Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row for a List Item
- L86 _private prototype_ `EVisibility GetNoneWarningVisibility() const;` — Visibility callback for "Nothing pasted" warning
- L89 _private prototype_ `FReply CloseWindow(bool bConfirmed);` — Closes the window
- L97 _private prototype_ `void CreateMissingFunctions(FListViewItem FuncToFix);` — Creates the missing function or event in the blueprint we are copying to. If the FuncToFix came from a custom event, then create a matching one here. @param FuncToFix		The function that needs to be created that was on the old BP, but not this one
- L100 _private member_ `TArray<FListViewItem> FunctionsToFixup;` — The list of unique functions that need to be fixed
- L103 _private member_ `TArray<UK2Node_CallFunction*> NodesToFixup;` — The find results to modify
- L106 _private member_ `UBlueprint* Blueprint;` — The blueprint for the new context
- L109 _private member_ `const FBlueprintEditor* BlueprintEditor;` — The blueprint editor this modal was created by
- L112 _private member_ `UBlueprint* FromBP;` — The blueprint that the incoming function is coming from
- L115 _private member_ `TSharedPtr<SWindow> MyWindow;` — Window to close when dialog completed
- L118 _private member_ `TArray<TSharedPtr<FString>> Options;` — Options for fixup
- L121 _private member_ `bool bOtherNodes;` — Whether other nodes were involved in this paste operation
- L124 _private member_ `bool bOutConfirmed;` — Whether the user confirmed or canceled the action

### `Source/Editor/Kismet/Public/SKismetInspector.h` (Public)


#### class `SKismetInspector`  
`class SKismetInspector : public SCompoundWidget, public FGCObject`  
_L47-246_
- inherits: `SCompoundWidget,FGCObject`
- desc: Widget that shows properties and tools related to the selected node(s)
- L50 _public function_ `SLATE_BEGIN_ARGS( SKismetInspector ) : _ShowPublicViewControl(false) , _HideNameArea(true) , _SetNotifyHook(true) , _ShowTitleArea(false) , _ShowLocalVariables(false) , _ScrollbarAlignment(HAlign_Right) , _ShowSectionSelector(false)`
- L60 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FBlueprintEditor>, Kismet2) SLATE_ARGUMENT(TWeakPtr<SMyBlueprint>, MyBlueprintWidget) SLATE_ATTRIBUTE( bool, ShowPublicViewControl ) SLATE_ARGUMENT( bool, HideNameArea ) SLATE_ARGUMENT( FIsPropertyEditingEnabled, IsPropertyEditingEnabledDelegate ) SLATE_ARGUMENT( FOnFinishedChangingProperties::FDelegate, OnFinishedChangingProperties ) SLATE_ARGUMENT( FName, ViewIdentifier) SLATE_ARGUMENT( bool, SetNotifyHook) SLATE_ARGUMENT( bool, ShowTitleArea) SLATE_ARGUMENT( bool, ShowLocalVariables) SLATE_ARGUMENT( TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_ARGUMENT( EHorizontalAlignment, ScrollbarAlignment) SLATE_ARGUMENT( bool, ShowSectionSelector) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L101 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L105 _public prototype_ `void ShowDetailsForSingleObject(UObject* Object, const FShowDetailsOptions& Options = FShowDetailsOptions());` — Update the inspector window to show information on the supplied object
- L108 _public prototype_ `void ShowDetailsForObjects(const TArray<UObject*>& PropertyObjects, const FShowDetailsOptions& Options = FShowDetailsOptions());` — Update the inspector window to show information on the supplied objects
- L111 _public prototype_ `void ShowSingleStruct(TSharedPtr<FStructOnScope> InStructToDisplay);` — Update the inspector window to show single struct. This invalidates ShowDetailsForObjects
- L114 _public prototype_ `bool IsPropertyVisible( const struct FPropertyAndParent& PropertyAndParent ) const;` — Used to control visibility of a property in the property window
- L117 _public prototype_ `void EnableComponentDetailsCustomization(bool bEnable);` — Turns on or off details customization for components
- L119 _public function_ `TSharedPtr<class IDetailsView> GetPropertyView() const`
- L121 _public prototype_ `void SetOwnerTab(TSharedRef<SDockTab> Tab);`
- L122 _public prototype_ `TSharedPtr<SDockTab> GetOwnerTab() const;`
- L125 _public prototype_ `bool IsSelected(UObject* Object) const;` — @return true if the object is in the selection set.
- L128 _public prototype_ `const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const;` — returns the list of selected objects
- L130 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L131 _public prototype_ `virtual FString GetReferencerName() const override;`
- L135 _protected prototype_ `void UpdateFromObjects(const TArray<UObject*>& PropertyObjects, struct FKismetSelectionInfo& SelectionInfo, const FShowDetailsOptions& Options);` — Update the inspector window to show information on the supplied objects
- L138 _protected prototype_ `void AddPropertiesRecursive(FProperty* Property);` — Add this property and all its child properties to SelectedObjectProperties
- L141 _protected member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the kismet 2 tool that owns us
- L144 _protected member_ `TWeakPtr<SDockTab> OwnerTab;` — The tab that owns this details view.
- L147 _protected member_ `FText PropertyViewTitle;` — String used as the title above the property window
- L150 _protected member_ `bool bShowInspectorPropertyView;` — Should we currently show the property view
- L153 _protected member_ `bool bShowComponents;` — Should we currently show components
- L156 _protected member_ `ECheckBoxState PublicViewState;` — State of CheckBox representing whether to show only the public variables
- L159 _protected member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L162 _protected member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Selected objects for this detail view
- L165 _protected member_ `TSharedPtr<class SNameEditingWidget> EditNameWidget;` — The widget used to edit the names of properties
- L168 _protected member_ `TSharedPtr<SBorder> ContextualEditingBorderWidget;` — Border widget that wraps a dynamic context-sensitive widget for editing objects that the property window is displaying
- L171 _protected member_ `TAttribute<bool> bShowPublicView;` — If true show the public view control
- L174 _protected member_ `bool bShowTitleArea;` — If true show the kismet inspector title widget
- L177 _protected member_ `bool bComponenetDetailsCustomizationEnabled;` — Component details customization enabled.
- L180 _protected member_ `TSet< TWeakFieldPtr<FProperty> > SelectedObjectProperties;` — Set of object properties that should be visible
- L183 _protected member_ `FIsPropertyEditingEnabled IsPropertyEditingEnabledDelegate;` — User defined delegate for IsPropertyEditingEnabled:
- L186 _protected member_ `FOnFinishedChangingProperties::FDelegate UserOnFinishedChangingProperties;` — User defined delegate for OnFinishedChangingProperties
- L189 _protected member_ `bool bRefreshOnTick;` — When TRUE, the Kismet inspector needs to refresh the details view on Tick
- L192 _protected member_ `TArray<TObjectPtr<UObject>> RefreshPropertyObjects;` — Holds the property objects that need to be displayed by the inspector starting on the next tick
- L195 _protected member_ `FShowDetailsOptions RefreshOptions;` — Details options that are used by the inspector on the next refresh.
- L198 _protected member_ `TSharedPtr<FStructOnScope> StructToDisplay;` — Struct to preview
- L201 _protected member_ `TSharedPtr<class IStructureDetailsView> StructureDetailsView;` — Sturct Detail View
- L204 _protected prototype_ `void UpdateFromSingleStruct(const TSharedPtr<FStructOnScope>& InStructToDisplay);` — Update the inspector window to show information on the single struct
- L207 _protected prototype_ `bool IsStructViewPropertyReadOnly(const struct FPropertyAndParent& PropertyAndParent) const;` — Is struct view property read only
- L211 _protected prototype_ `void SetPropertyWindowContents(TArray<UObject*> Objects);` — Show properties of the selected object
- L214 _protected prototype_ `EVisibility GetPropertyViewVisibility() const;` — Returns whether the property view be visible
- L217 _protected prototype_ `bool IsPropertyEditingEnabled() const;` — Returns whether the properties in the view should be editable
- L220 _protected prototype_ `EVisibility GetInheritedBlueprintComponentWarningVisibility() const;` — Returns whether the warning about an inherited component not being editable should be visible
- L223 _protected prototype_ `void OnInheritedBlueprintComponentWarningHyperlinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata);` — Opens the parent blueprint when the hyperlink in the warning is clicked
- L229 _protected prototype_ `TSharedRef<SWidget> MakeContextualEditingWidget(struct FKismetSelectionInfo& SelectionInfo, const FShowDetailsOptions& Options);` — Generates a widget that is used to edit the specified object array contextually.  This widget will be displayed along with a property view in the level editor
- L234 _protected prototype_ `FText GetContextualEditingWidgetTitle() const;` — Generates the text for the title in the contextual editing widget
- L236 _protected prototype_ `ECheckBoxState GetPublicViewCheckboxState() const;`
- L237 _protected prototype_ `void SetPublicViewCheckboxState(ECheckBoxState InIsChecked);`
- L239 _protected prototype_ `bool IsAnyParentOrContainerSelected(const FPropertyAndParent& PropertyAndParent) const;`
- L242 _protected prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);` — Callback invoked after a value change on the selected object(s)
- L245 _protected prototype_ `void ImportNamespacesForPropertyValue(const FProperty* InProperty) const;` — Auto-import any namespaces associated with a property's value into the current editor context

#### struct `SKismetInspector::FShowDetailsOptions`  
`struct FShowDetailsOptions`  
_L78-98_
- desc: Options for ShowDetails
- L80 _public member_ `FText ForcedTitle;`
- L81 _public member_ `bool bForceRefresh;`
- L82 _public member_ `bool bShowComponents;`
- L83 _public member_ `bool bHideFilterArea;`
- L85 _public function_ `FShowDetailsOptions() :ForcedTitle() ,bForceRefresh(false) ,bShowComponents(true) ,bHideFilterArea(false)`
- L92 _public function_ `FShowDetailsOptions(const FText& InForcedTitle, bool bInForceRefresh = false) :ForcedTitle(InForcedTitle) ,bForceRefresh(bInForceRefresh) ,bShowComponents(true) ,bHideFilterArea(false)`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API KISMET_API`
- L41 _typedef_ `typedef TSet<class UObject*> FInspectorSelectionSet;`

### `Source/Editor/Kismet/Public/SMyBlueprint.h` (Public)


#### class `FMyBlueprintCommands`  
`class FMyBlueprintCommands : public TCommands<FMyBlueprintCommands>`  
_L58-85_
- inherits: `TCommands<FMyBlueprintCommands>`
- L62 _public function_ `FMyBlueprintCommands() : TCommands<FMyBlueprintCommands>(TEXT("MyBlueprint"), NSLOCTEXT("Contexts", "My Blueprint", "My Blueprint"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L68 _public member_ `TSharedPtr<FUICommandInfo> OpenGraph;` — Basic operations
- L69 _public member_ `TSharedPtr<FUICommandInfo> OpenGraphInNewTab;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> OpenExternalGraph;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> FocusNode;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> FocusNodeInNewTab;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> ImplementFunction;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> DeleteEntry;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> PasteVariable;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> PasteLocalVariable;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> PasteFunction;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> PasteMacro;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> GotoNativeVarDefinition;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> MoveVariableToParent;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> MoveFunctionToParent;`
- L84 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `SMyBlueprint`  
`class SMyBlueprint : public SCompoundWidget`  
_L87-382_
- inherits: `SCompoundWidget`
- L90 _public function_ `SLATE_BEGIN_ARGS( SMyBlueprint )`
- L91 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor, const UBlueprint* InBlueprint = nullptr);`
- L94 _public prototype_ `~SMyBlueprint();`
- L96 _public function_ `void SetInspector( TSharedPtr<SKismetInspector> InInspector )`
- L99 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);` — SWidget interface
- L100 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L103 _public prototype_ `void ResetLastPinType();` — Reset the last pin type settings to default.
- L106 _public prototype_ `void Refresh();` — Refreshes the graph action menu
- L107 _public function_ `void SetFocusedGraph(UEdGraph* InEdGraph)`
- L110 _public prototype_ `FEdGraphSchemaAction_K2Graph* SelectionAsGraph() const;` — Accessor for getting the current selection as a K2 graph
- L113 _public prototype_ `FEdGraphSchemaAction_K2Enum* SelectionAsEnum() const;` — Accessor for getting the current selection as a K2 enum
- L116 _public prototype_ `FEdGraphSchemaAction_K2Struct* SelectionAsStruct() const;` — Accessor for getting the current selection as a K2 enum
- L119 _public prototype_ `FEdGraphSchemaAction_K2Var* SelectionAsVar() const;` — Accessor for getting the current selection as a K2 var
- L122 _public prototype_ `FEdGraphSchemaAction_K2Delegate* SelectionAsDelegate() const;` — Accessor for getting the current selection as a K2 delegate
- L125 _public prototype_ `FEdGraphSchemaAction_K2Event* SelectionAsEvent() const;` — Accessor for getting the current selection as a K2 event
- L128 _public prototype_ `FEdGraphSchemaAction_K2InputAction* SelectionAsInputAction() const;` — Accessor for getting the current selection as a K2 Input Action
- L131 _public prototype_ `FEdGraphSchemaAction_K2LocalVar* SelectionAsLocalVar() const;` — Accessor for getting the current selection as a K2 local var
- L134 _public prototype_ `FEdGraphSchemaAction_BlueprintVariableBase* SelectionAsBlueprintVariable() const;` — Accessor for getting the current selection as a K2 blueprint base variable
- L137 _public prototype_ `bool SelectionIsCategory() const;` — Accessor for determining if the current selection is a category
- L139 _public prototype_ `void EnsureLastPinTypeValid();`
- L142 _public function_ `FEdGraphPinType& GetLastPinTypeUsed()` — Gets the last pin type selected by this widget, or by the function editor
- L143 _public function_ `FEdGraphPinType& GetLastFunctionPinTypeUsed()`
- L146 _public function_ `UBlueprint* GetBlueprintObj() const` — Accessor the blueprint object from the main editor
- L149 _public function_ `bool ShowUserVarsOnly() const` — Gets whether we are showing user variables only or not
- L152 _public function_ `TWeakPtr<FBlueprintEditor> GetBlueprintEditor()` — Gets our parent blueprint editor
- L158 _public prototype_ `void GetSelectedItemsForContextMenu(TArray<FComponentEventConstructionData>& OutSelectedItems) const;` — Fills the supplied array with the currently selected objects @param OutSelectedItems The array to fill.
- L161 _public prototype_ `void OnResetItemFilter();` — Called to reset the search filter
- L164 _public prototype_ `void SelectItemByName(const FName& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct, int32 SectionId = INDEX_NONE, bool bIsCategory = false);` — Selects an item by name in either the main graph action menu or the local one
- L167 _public prototype_ `void ClearGraphActionMenuSelection();` — Clears the selection in the graph action menus
- L170 _public prototype_ `void OnRequestRenameOnActionNode();` — Initiates a rename on the selected action node, if possible
- L173 _public prototype_ `void ExpandCategory(const FText& CategoryName);` — Expands any category with the associated name
- L176 _public prototype_ `bool MoveCategoryBeforeCategory( const FText& CategoryToMove, const FText& TargetCategory );` — Move the category before the target category
- L179 _public prototype_ `void OnPasteGeneric();` — Callbacks for Paste Commands
- L180 _public prototype_ `bool CanPasteGeneric();`
- L183 _private prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);` — Creates widgets for the graph schema actions
- L186 _private prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu
- L187 _private prototype_ `void CollectStaticSections(TArray<int32>& StaticSectionIDs);`
- L188 _private prototype_ `void AddEventForFunctionGraph(UEdGraph* EdGraph, int32 const SectionId, FGraphActionSort& SortList, const FText& ParentCategory = FText::GetEmpty(), bool bAddChildGraphs = true) const;`
- L189 _private prototype_ `void GetChildGraphs(UEdGraph* EdGraph, int32 const SectionId, FGraphActionSort& SortList, const FText& ParentCategory = FText::GetEmpty()) const;`
- L190 _private prototype_ `void GetChildEvents(UEdGraph const* EdGraph, int32 const SectionId, FGraphActionSort& SortList, const FText& ParentCategory = FText::GetEmpty(), bool bInAddChildGraphs = true) const;`
- L191 _private prototype_ `void GetLocalVariables(FGraphActionSort& SortList) const;`
- L194 _private prototype_ `EVisibility GetLocalActionsListVisibility() const;` — Handles the visibility of the local action list
- L197 _private prototype_ `FReply OnActionDragged(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions, const FPointerEvent& MouseEvent);` — Callbacks for the graph action menu
- L198 _private prototype_ `FReply OnCategoryDragged(const FText& InCategory, const FPointerEvent& MouseEvent);`
- L199 _private prototype_ `void OnActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions);`
- L200 _private prototype_ `void OnActionSelectedHelper(TSharedPtr<FEdGraphSchemaAction> InAction, TWeakPtr< FBlueprintEditor > InBlueprintEditor, UBlueprint* Blueprint, TSharedRef<SKismetInspector> Inspector);`
- L201 _private prototype_ `void OnGlobalActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions, ESelectInfo::Type InSelectionType);`
- L202 _private prototype_ `void OnActionDoubleClicked(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions);`
- L203 _private prototype_ `void ExecuteAction(TSharedPtr<FEdGraphSchemaAction> InAction);`
- L204 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L206 _private prototype_ `TSharedRef<SWidget> CreateAddNewMenuWidget();`
- L207 _private prototype_ `void BuildAddNewMenu(FMenuBuilder& MenuBuilder);`
- L208 _private prototype_ `TSharedRef<SWidget> CreateAddToSectionButton(int32 InSectionID, TWeakPtr<SWidget> WeakRowWidget, FText AddNewText, FName MetaDataTag);`
- L210 _private prototype_ `void OnCategoryNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit, TWeakPtr< struct FGraphActionNode > InAction );`
- L211 _private prototype_ `bool CanRequestRenameOnActionNode(TWeakPtr<struct FGraphActionNode> InSelectedNode) const;`
- L212 _private prototype_ `FText OnGetSectionTitle( int32 InSectionID );`
- L213 _private prototype_ `TSharedRef<SWidget> OnGetSectionWidget( TSharedRef<SWidget> RowWidget, int32 InSectionID );`
- L214 _private prototype_ `EVisibility OnGetSectionTextVisibility(TWeakPtr<SWidget> RowWidget, int32 InSectionID) const;`
- L215 _private prototype_ `TSharedRef<SWidget> OnGetFunctionListMenu();`
- L216 _private prototype_ `void BuildOverridableFunctionsMenu(FMenuBuilder& MenuBuilder);`
- L217 _private prototype_ `FReply OnAddButtonClickedOnSection(int32 InSectionID);`
- L218 _private prototype_ `bool CanAddNewElementToSection(int32 InSectionID) const;`
- L220 _private prototype_ `bool HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;`
- L223 _private prototype_ `bool IsShowingInheritedVariables() const;` — Support functions for checkbox to manage displaying user variables only
- L224 _private prototype_ `void OnToggleShowInheritedVariables();`
- L227 _private prototype_ `void OnToggleShowEmptySections();` — Support functions for view options for Show Empty Sections
- L228 _private prototype_ `bool IsShowingEmptySections() const;`
- L231 _private prototype_ `void OnToggleShowReplicatedVariablesOnly();` — Support functions for view options for Show Replicated Variables only
- L232 _private prototype_ `bool IsShowingReplicatedVariablesOnly() const;`
- L235 _private prototype_ `void OnToggleAlwaysShowInterfacesInOverrides();` — Support functions for view options for bAlwaysShowInterfacesInOverrides blueprint editor setting
- L236 _private prototype_ `bool GetAlwaysShowInterfacesInOverrides() const;`
- L239 _private prototype_ `void OnToggleShowParentClassInOverrides();` — Support functions for view options for bShowParentClassInOverrides blueprint editor setting
- L240 _private prototype_ `bool GetShowParentClassInOverrides() const;`
- L243 _private prototype_ `void OnToggleShowAccessSpecifier();` — Support functions for view options for bShowAccessSpecifier blueprint editor setting
- L244 _private prototype_ `bool GetShowAccessSpecifier() const;`
- L247 _private prototype_ `void OpenGraph(FDocumentTracker::EOpenDocumentCause InCause, bool bOpenExternalGraphInNewEditor = false);` — Helper function to open the selected graph
- L257 _private prototype_ `bool IsImplementationDesiredAsFunction(const UFunction* OverrideFunc) const;` — Check if the override of a given function is most likely desired as a blueprint function or as an event. @param OverrideFunc	Desired function to override @return	True if the function is desired as a function, false if desired as an event
- L260 _private prototype_ `void OnOpenGraph();` — Callbacks for commands
- L261 _private prototype_ `void OnOpenGraphInNewTab();`
- L262 _private prototype_ `void OnOpenExternalGraph();`
- L263 _private prototype_ `bool CanOpenGraph() const;`
- L264 _private prototype_ `bool CanOpenExternalGraph() const;`
- L265 _private prototype_ `bool CanFocusOnNode() const;`
- L266 _private prototype_ `void OnFocusNode();`
- L267 _private prototype_ `void OnFocusNodeInNewTab();`
- L268 _private prototype_ `void OnImplementFunction();`
- L269 _private prototype_ `void ImplementFunction(TSharedPtr<FEdGraphSchemaAction_K2Graph> GraphAction);`
- L270 _private prototype_ `void ImplementFunction(FEdGraphSchemaAction_K2Graph* GraphAction);`
- L271 _private prototype_ `bool CanImplementFunction() const;`
- L272 _private prototype_ `void OnFindReference(bool bSearchAllBlueprints, const EGetFindReferenceSearchStringFlags Flags);`
- L273 _private prototype_ `bool CanFindReference() const;`
- L274 _private prototype_ `void OnFindAndReplaceReference();`
- L275 _private prototype_ `bool CanFindAndReplaceReference() const;`
- L276 _private prototype_ `void OnDeleteEntry();`
- L277 _private prototype_ `bool CanDeleteEntry() const;`
- L278 _private prototype_ `FReply OnAddNewLocalVariable();`
- L279 _private prototype_ `bool CanRequestRenameOnActionNode() const;`
- L280 _private prototype_ `bool IsDuplicateActionVisible() const;`
- L281 _private prototype_ `bool CanDuplicateAction() const;`
- L282 _private prototype_ `void OnDuplicateAction();`
- L283 _private prototype_ `void GotoNativeCodeVarDefinition();`
- L284 _private prototype_ `bool IsNativeVariable() const;`
- L285 _private prototype_ `void OnMoveToParent();`
- L286 _private prototype_ `bool CanMoveVariableToParent() const;`
- L287 _private prototype_ `bool CanMoveFunctionToParent() const;`
- L288 _private prototype_ `void OnCopy();`
- L289 _private prototype_ `bool CanCopy() const;`
- L290 _private prototype_ `void OnCut();`
- L291 _private prototype_ `bool CanCut() const;`
- L292 _private prototype_ `void OnPasteVariable();`
- L293 _private prototype_ `void OnPasteLocalVariable();`
- L294 _private prototype_ `bool CanPasteVariable() const;`
- L295 _private prototype_ `bool CanPasteLocalVariable() const;`
- L296 _private prototype_ `void OnPasteFunction();`
- L297 _private prototype_ `bool CanPasteFunction() const;`
- L298 _private prototype_ `void OnPasteMacro();`
- L299 _private prototype_ `bool CanPasteMacro() const;`
- L302 _private prototype_ `FText GetPasteCategory() const;` — Gets the currently selected Category or returns default category name
- L305 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Callback when the filter is changed, forces the action tree(s) to filter
- L308 _private prototype_ `FText GetFilterText() const;` — Callback for the action trees to get the filter text
- L311 _private prototype_ `bool SelectionHasContextMenu() const;` — Checks if the selected action has context menu
- L314 _private prototype_ `void UpdateNodeCreation();` — Update Node Create Analytic
- L317 _private prototype_ `FText GetGraphCategory(UEdGraph* InGraph) const;` — Returns the displayed category, if any, of a graph
- L320 _private prototype_ `void OnDeleteGraph(UEdGraph* InGraph, EEdGraphSchemaAction_K2Graph::Type);` — Helper function to delete a graph in the MyBlueprint window
- L323 _private prototype_ `void OnDeleteDelegate(FEdGraphSchemaAction_K2Delegate* InDelegateAction);` — Helper function to delete a delegate in the MyBlueprint window
- L325 _private prototype_ `UEdGraph* GetFocusedGraph() const;`
- L328 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Delegate to hook us into non-structural Blueprint object post-change events
- L331 _private prototype_ `bool IsEditingMode() const;` — Helper function indicating whehter we're in editing mode, and can modify the target blueprint
- L334 _private prototype_ `static bool IsAnInterfaceEvent(FEdGraphSchemaAction_K2Graph* InAction);` — Determine whether an FEdGraphSchemaAction is associated with an event
- L338 _private member_ `TSharedPtr<FUICommandList> CommandList;` — List of UI Commands for this scope
- L341 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditorPtr;` — Pointer back to the blueprint editor that owns us
- L344 _private member_ `TSharedPtr<class SGraphActionMenu> GraphActionMenu;` — Graph Action Menu for displaying all our variables and functions
- L347 _private member_ `TSharedPtr<SComboButton> FunctionSectionButton;` — The +Function button in the function section
- L350 _private member_ `TArray< TSharedPtr<FEdGraphSchemaAction_K2Graph> > OverridableFunctionActions;` — When we rebuild the view of members, we cache (but don't display) any overridable functions for user in popup menus.
- L353 _private member_ `TSet<FName> ImplementedFunctionCache;` — When we refresh the list of functions we cache off the implemented ones to ask questions for overridable functions.
- L356 _private member_ `FEdGraphPinType LastPinType;` — The last pin type used (including the function editor last pin type)
- L357 _private member_ `FEdGraphPinType LastFunctionPinType;`
- L360 _private member_ `TArray<TWeakObjectPtr<UUserDefinedEnum>> EnumsAddedToBlueprint;` — Enums created from 'blueprint' level
- L363 _private member_ `TSharedPtr< SSearchBox > FilterBox;` — The filter box that handles filtering for both graph action menus.
- L366 _private member_ `TArray<TWeakObjectPtr<UUserDefinedStruct>> StructsAddedToBlueprint;` — Enums created from 'blueprint' level
- L369 _private member_ `UBlueprint* Blueprint;` — The blueprint being displayed:
- L372 _private member_ `UEdGraph* EdGraph;` — The Ed Graph being displayed:
- L375 _private member_ `TWeakPtr<SKismetInspector> Inspector;` — The Kismet Inspector used to display properties:
- L378 _private member_ `bool bNeedsRefresh;` — Flag to indicate whether or not we need to refresh the panel
- L381 _private member_ `bool bShowReplicatedVariablesOnly;` — If set we'll show only replicated variables (local to a particular blueprint view).

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API KISMET_API`

### `Source/Editor/Kismet/Public/SPinValueInspector.h` (Public)


#### class `SPinValueInspector`  
`class SPinValueInspector : public SCompoundWidget`  
_L29-83_
- inherits: `SCompoundWidget`
- desc: Inspects the referenced pin object's underlying property value and presents it within a tree view. Compound properties (e.g. structs/containers) will be broken down into a hierarchy of child nodes.
- L32 _public function_ `SLATE_BEGIN_ARGS(SPinValueInspector)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `bool ShouldShowSearchFilter() const;` — Whether the search filter UI should be visible.
- L42 _public prototype_ `const FEdGraphPinReference& GetPinRef() const;` — Gets the current watched pin reference
- L48 _protected prototype_ `virtual EVisibility GetSearchFilterVisibility() const;` — @return Visibility of the search box filter widget.
- L51 _protected prototype_ `virtual void OnSearchTextChanged(const FText& InSearchText);` — Passes SearchText through to tree view
- L54 _protected prototype_ `virtual void OnExpansionChanged(FDebugTreeItemPtr InItem, bool bItemIsExpanded);` — requests the constrained box be resized
- L57 _protected prototype_ `virtual void AddTreeItemUnique(const FDebugTreeItemPtr& Item);` — Adds a unique tree item to the TreeView.
- L60 _protected prototype_ `virtual void PopulateTreeView();` — Adds relevant pins to the tree view
- L63 _protected prototype_ `void AddPinToTreeView(const UEdGraphPin* Pin, UBlueprint* Blueprint);` — Adds a single pin to the tree view
- L66 _protected prototype_ `void RequestUpdateFilteredItems();` — Marks tree view for updating currently filtered items.
- L69 _protected prototype_ `void SetPinRef(const FEdGraphPinReference& InPinRef);` — Sets the current watched pin
- L73 _private member_ `FEdGraphPinReference PinRef;` — Holds a weak reference to the target pin.
- L76 _private member_ `TWeakObjectPtr<UObject> TargetObject;` — The instance that's currently selected as the debugging target.
- L79 _private member_ `TSharedPtr<SKismetDebugTreeView> TreeViewWidget;` — Presents a hierarchical display of the inspected value along with any sub-values as children.
- L82 _private member_ `TSharedPtr<class SPinValueInspector_ConstrainedBox> ConstrainedBox;` — The box that handles resizing of the Tree View

#### class `FPinValueInspectorTooltip`  
`class FPinValueInspectorTooltip`  
_L86-132_
- desc: class holding functions to spawn a pin value inspector tooltip
- L90 _public prototype_ `void MoveTooltip(const UE::Slate::FDeprecateVector2DParameter& InNewLocation);` — Moves the tooltip to the new location
- L98 _public prototype_ `void TryDismissTooltip(bool bForceDismiss = false);` — Dismisses the current tooltip, if it is not currently hovered NOTE: Pin a shared ptr before calling this function @param bForceDismiss	true to dismiss regardless of hover & tooltip ownership
- L101 _public prototype_ `bool TooltipCanClose() const;` — @returns whether or not the tooltip can close
- L104 _public prototype_ `bool TooltipHostsMenu() const;` — @returns whether this tooltip is the host for a context menu
- L108 _private prototype_ `void DismissTooltip();` — Dismisses the current tooltip (internal implementation)
- L112 _public prototype_ `static TWeakPtr<FPinValueInspectorTooltip> SummonTooltip(FEdGraphPinReference InPinRef, TSharedPtr<SPinValueInspector> InContentWidgetOverride = { });` — Summons a new tooltip in the shared window. If provided, uses a custom implementation of a pin value inspector widget.
- L115 _public prototype_ `static void ShutdownTooltip();` — Release the references to the static widget shared pointers
- L118 _public member_ `static TSharedPtr<SPinValueInspector> ValueInspectorWidget;` — Default inspector widget in the tooltip
- L122 _private prototype_ `static void CreatePinValueTooltipWindow();` — Handles Creating a custom tooltip window for all PinValueInspector tooltips
- L125 _private member_ `static TSharedPtr<class SWindow> TooltipWindow;` — A reusable tooltip window for PinValueInspector
- L128 _private member_ `static TSharedPtr<class SToolTip> TooltipWidget;` — Tooltip widget housed in the window
- L131 _private member_ `static TSharedPtr<FPinValueInspectorTooltip> Instance;` — The current "live" tooltip

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API KISMET_API`
- L23 _typedef_ `typedef TSharedPtr<struct FPinValueInspectorTreeViewNode> FPinValueInspectorTreeViewNodePtr;`

### `Source/Editor/Kismet/Public/SSCSEditor.h` (Public)


#### class `FSCSEditorTreeNode`  
`class FSCSEditorTreeNode : public TSharedFromThis<FSCSEditorTreeNode>`  
_L100-506_
- inherits: `TSharedFromThis<FSCSEditorTreeNode>`
- desc: FSCSEditorTreeNode Wrapper class for nodes displayed in the SCS (Simple Construction Script) editor tree widget. NOTE: Mostly deprecated, switch to FSubobjectEditorTreeNode
- L104 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L117 _public prototype_ `FSCSEditorTreeNode(FSCSEditorTreeNode::ENodeType InNodeType);` — Constructs an empty tree node.
- L122 _public prototype_ `virtual FName GetNodeID() const;` — @return The name to identify this node.
- L127 _public prototype_ `virtual FName GetVariableName() const;` — @return The name of the variable represented by this node.
- L131 _public prototype_ `virtual FString GetDisplayString() const;` — @return The string to be used in the tree display.
- L135 _public prototype_ `virtual FText GetDisplayName() const;` — @return The name of this node in text.
- L139 _public prototype_ `virtual class USCS_Node* GetSCSNode() const;` — @return The SCS node that is represented by this object, or NULL if there is no associated SCS node.
- L145 _public function_ `inline UActorComponent* GetOrCreateEditableComponentTemplate(UBlueprint* ActualEditedBlueprint) const` — @param ActualEditedBlueprint currently edited blueprint @note Derived classes should override GetOrCreateEditableObjectForBlueprint(). @return The component template that can be editable for actual class.
- L156 _public prototype_ `virtual UActorComponent* FindComponentInstanceInActor(const AActor* InActor) const;` — Finds the component instance represented by this node contained within a given Actor instance. @param InActor The Actor instance to use as the container object for finding the component instance. @return The component instance represented by this node and contained within the given Actor instance, or NULL if not found.
- L160 _public function_ `FSCSEditorTreeNodePtrType GetParent() const` — @return This object's parent node (or an invalid reference if no parent is assigned).
- L164 _public function_ `const TArray<FSCSEditorTreeNodePtrType>& GetChildren() const` — @return The set of nodes which are parented to this node (read-only).
- L168 _public function_ `FSCSEditorActorNodePtrType GetActorRootNode() const` — @return The root of the actor subtree to which this node belongs.
- L172 _public prototype_ `void SetActorRootNode(FSCSEditorActorNodePtrType InActorNode);` — Sets the actor root to the given node for this node along with any children.
- L176 _public prototype_ `ENodeType GetNodeType() const;` — @return Type of node
- L180 _public function_ `bool IsActorNode() const` — @return True if this represents an actor node type
- L187 _public function_ `bool IsComponentNode() const` — @return True if this represents a component node type
- L200 _public function_ `inline UActorComponent* GetComponentTemplate(bool bEvenIfPendingKill = false) const` — @param	bEvenIfPendingKill	If false, nullptr will be returned if the cached component template is pending kill. If true, it will be returned regardless (this is used for recaching the component template if the objects have been reinstanced following construction script execution). @note	Deliberately non-virtual, for performance reasons. @warning This will not return the right component for components overridden by the inherited component handler, you need to call GetOrCreateEditableComponentTemplate instead @return	The component template or instance represented by this node, if it's a component node.
- L214 _public function_ `template<class T> inline const T* GetObject(bool bEvenIfPendingKill = false) const` — @param	bEvenIfPendingKill	If false, nullptr will be returned if the cached object instance is pending kill. If true, it will be returned regardless (this is used for recaching the object if the objects have been reinstanced following construction script execution). @note	Deliberately non-virtual, for performance reasons. @return	A read-only reference to the object represented by this node.
- L225 _public function_ `template<class T> inline T* GetEditableObjectForBlueprint(UBlueprint* InBlueprint) const` — @param	InBlueprint			The Blueprint in which the object will be edited. @note	May not be the same as the value returned by GetObject(). @return	A reference to the object represented by this node that can be modified within the given Blueprint.
- L232 _public function_ `inline void SetObject(UObject* InObject)` — Sets the internal object instance represented by this node.
- L239 _public function_ `bool IsDirectlyAttachedTo(FSCSEditorTreeNodePtrType InNodePtr) const` — @return Whether or not this node is a direct child of the given node.
- L243 _public prototype_ `bool IsAttachedTo(FSCSEditorTreeNodePtrType InNodePtr) const;` — @return Whether or not this node is a child (direct or indirect) of the given node.
- L251 _public prototype_ `FSCSEditorTreeNodePtrType FindClosestParent(TArray<FSCSEditorTreeNodePtrType> InNodes);` — Finds the closest ancestor node in the given node set. @param InNodes The given node set. @return One of the nodes from the set, or an invalid node reference if the set does not contain any ancestor nodes.
- L258 _public prototype_ `virtual void AddChild(FSCSEditorTreeNodePtrType InChildNodePtr);` — Adds the given node as a child node. @param InChildNodePtr The node to add as a child node.
- L267 _public prototype_ `FSCSEditorTreeNodePtrType AddChild(USCS_Node* InSCSNode, bool bIsInheritedSCS);` — Adds a child node for the given SCS node. @param InSCSNode The SCS node to for which to create a child node. @param bIsInheritedSCS Whether or not the given SCS node is inherited from a parent. @return A reference to the new child node or the existing child node if a match is found.
- L275 _public prototype_ `FSCSEditorTreeNodePtrType AddChildFromComponent(UActorComponent* InComponentTemplate);` — Adds a child node for the given component template. @param InComponentTemplate The component template for which to create a child node. @return A reference to the new child node or the existing child node if a match is found.
- L285 _public prototype_ `FSCSEditorTreeNodePtrType FindChild(const USCS_Node* InSCSNode, bool bRecursiveSearch = false, uint32* OutDepth = NULL) const;` — Attempts to find a reference to the child node that matches the given SCS node. @param InSCSNode The SCS node to match. @param bRecursiveSearch Whether or not to recursively search child nodes (default == false). @param OutDepth If non-NULL, the depth of the child node will be returned in this parameter on success (default == NULL). @return The child node that matches the given SCS node, or an invalid node reference if no match was found.
- L295 _public prototype_ `FSCSEditorTreeNodePtrType FindChild(const UActorComponent* InComponentTemplate, bool bRecursiveSearch = false, uint32* OutDepth = NULL) const;` — Attempts to find a reference to the child node that matches the given component template. @param InComponentTemplate The component template instance to match. @param bRecursiveSearch Whether or not to recursively search child nodes (default == false). @param OutDepth If non-NULL, the depth of the child node will be returned in this parameter on success (default == NULL). @return The child node with a component template that matches the given component template instance, or an invalid node reference if no match was found.
- L305 _public prototype_ `FSCSEditorTreeNodePtrType FindChild(const FName& InVariableOrInstanceName, bool bRecursiveSearch = false, uint32* OutDepth = NULL) const;` — Attempts to find a reference to the child node that matches the given component variable or instance name. @param InVariableOrInstanceName The component variable or instance name to match. @param bRecursiveSearch Whether or not to recursively search child nodes (default == false). @param OutDepth If non-NULL, the depth of the child node will be returned in this parameter on success (default == NULL). @return The child node with a component variable or instance name that matches the given name, or an invalid node reference if no match was found.
- L312 _public prototype_ `virtual void RemoveChild(FSCSEditorTreeNodePtrType InChildNodePtr);` — Removes the given node from the list of child nodes. @param InChildNodePtr The child node to remove.
- L314 _public function_ `bool IsSceneComponent() const`
- L320 _public function_ `virtual FSCSEditorChildActorNodePtrType GetChildActorNode()` — Returns the associated child actor node if applicable to this node type.
- L323 _public prototype_ `static USCS_Node* FindSCSNodeForInstance(const UActorComponent* InstanceComponent, UClass* ClassToSearch);` — Tries to find a SCS node that was likely responsible for creating the specified instance component.  Note: This is not always possible to do!
- L328 _public prototype_ `static FSCSEditorTreeNodePtrType FactoryNodeFromComponent(UActorComponent* InComponent);` — Creates the correct type of node based on the component (instanced or not, etc...)
- L331 _public prototype_ `static FSlateColor GetColorTintForIcon(FSCSEditorTreeNodePtrType InNode);` — Returns a color to use for this type of node
- L334 _public prototype_ `virtual ~FSCSEditorTreeNode() = default;` — Destructor
- L341 _public prototype_ `void CloseOngoingCreateTransaction();` — Ends the 'Create + enter initial name' transaction of this node. The creation of a node is 'ongoing' as long as the initial name of the node is in edition mode. When the text is not in edit mode anymore, the ongoing create transaction ends and the node is considered fully created.
- L345 _protected function_ `virtual void RemoveMeAsChild()` — Called when this node is being removed via a RemoveChild call
- L349 _protected function_ `template<class T> inline T* GetMutableObject() const` — Provides derived classes with non-const access to the object represented by this node (e.g. for rename operations, etc.). This should not be made public.
- L355 _protected prototype_ `virtual UObject* GetOrCreateEditableObjectForBlueprint(UBlueprint* InBlueprint) const;` — Derived classes can override to create and/or return a reference to an alternate editable object.
- L361 _public prototype_ `virtual UBlueprint* GetBlueprint() const = 0;` — @return The Blueprint to which the object represented by this node belongs (requires implementation in subclass).
- L366 _public function_ `virtual bool IsNativeComponent() const` — @return Whether or not this object represents a "native" component template (i.e. one that is not found in the SCS tree).
- L371 _public function_ `virtual bool IsRootComponent() const` — @return Whether or not this object represents a root component.
- L376 _public function_ `virtual bool IsInheritedSCSNode() const` — @return Whether or not this object represents an inherited SCS node (one from a SCS node in a parent Blueprint).
- L381 _public function_ `virtual bool IsInheritedComponent() const` — @return Whether or not this object was declared in the current class (or instance).  Anything inherited cannot be reorganized (renamed, reparented, etc...).
- L389 _public function_ `virtual bool IsInstanced() const` — @return Whether or not this node represents an instanced object (i.e. not a template).
- L394 _public function_ `bool IsInstancedActor() const` — @return Whether or not this node represents an instanced actor object.
- L402 _public function_ `bool IsInstancedComponent() const` — @return Whether or not this node represents an instanced component object.
- L410 _public function_ `bool IsBlueprintComponent() const` — @return Whether or not this node represents a Blueprint (i.e. non-native) component object.
- L418 _public function_ `virtual bool IsUserInstancedComponent() const` — @return Whether or not this object represents a component instance that was created by the user and not by a native or Blueprint-generated class.
- L423 _public function_ `virtual bool IsDefaultSceneRoot() const` — @return Whether or not this object represents the default SCS scene root component.
- L428 _public function_ `virtual bool CanDelete() const` — @return Whether or not this object represents a node that can be deleted from the SCS tree.
- L433 _public function_ `virtual bool CanReparent() const` — @return Whether or not this object represents a node that can be reparented to other nodes based on its context.
- L438 _public function_ `virtual bool CanEdit() const` — @return Whether or not we can edit properties for the object represented by this node.
- L443 _public function_ `virtual bool CanRename() const` — @return Whether or not we can rename the object or variable represented by this node.
- L449 _public prototype_ `void OnRequestRename(TUniquePtr<FScopedTransaction> OngoingCreateTransaction);` — Requests a rename on the node. @param OngoingCreateTransaction The transaction scoping the node creation which will end once the node is named by the user or null if the rename is not part of a the creation process.
- L452 _public prototype_ `virtual void OnCompleteRename(const FText& InNewName);` — Renames the object or variable represented by this node
- L455 _public function_ `void SetRenameRequestedDelegate(FOnRenameRequested InRenameRequested)` — Sets up the delegate for a rename operation
- L458 _public function_ `virtual bool IsFlaggedForFiltration() const` — Query that determines if this item should be filtered out or not
- L465 _public prototype_ `virtual bool MatchesFilterType(const UClass* InFilterType) const;` — Returns whether the node will match the given type (for filtering)
- L468 _public prototype_ `virtual bool RefreshFilteredState(const UClass* InFilterType, const TArray<FString>& InFilterTerms, bool bRecursive);` — Refreshes this item's filtration state. Set bRecursive to 'true' to refresh any child nodes as well
- L472 _protected prototype_ `void SetCachedFilterState(bool bMatchesFilter, bool bUpdateParent);` — Sets this item's filtration state. Use bUpdateParent to make sure the parent's EFilteredState::ChildMatches flag is properly updated based off the new state
- L474 _protected prototype_ `void RefreshCachedChildFilterState(bool bUpdateParent);` — Updates the EFilteredState::ChildMatches flag, based off of children's current state
- L476 _protected prototype_ `void ApplyFilteredStateToParent();` — Used to update the EFilteredState::ChildMatches flag for parent nodes, when this item's filtration state has changed
- L479 _protected member_ `TUniquePtr<FScopedTransaction> OngoingCreateTransaction;` — Scope the creation of a node which ends when the initial 'name' is given/accepted by the user, which can be several frames after the node was actually created.
- L483 _private member_ `ENodeType NodeType;` — The type of tree node
- L486 _private member_ `TWeakObjectPtr<UObject> WeakObjectPtr;` — Weak ptr to the object instance represented by this node (e.g. component template)
- L489 _private member_ `FSCSEditorTreeNodePtrType ParentNodePtr;` — Actual tree structure
- L490 _private member_ `FSCSEditorActorNodePtrType ActorRootNodePtr;`
- L491 _private member_ `TArray<FSCSEditorTreeNodePtrType> Children;`
- L494 _private member_ `FOnRenameRequested RenameRequestedDelegate;` — Handles rename requests
- L505 _private member_ `uint8 FilterFlags;`

#### enum `FSCSEditorTreeNode::ENodeType`  
`enum ENodeType`  
_L106-112_
- L108 _public enumerator_ `ComponentNode`
- L109 _public enumerator_ `RootActorNode`
- L110 _public enumerator_ `SeparatorNode`
- L111 _public enumerator_ `ChildActorNode`

#### enum `FSCSEditorTreeNode::EFilteredState`  
`enum EFilteredState`  
_L496-504_
- L498 _public enumerator_ `FilteredOut = 0x00`
- L499 _public enumerator_ `MatchesFilter = (1 << 0)`
- L500 _public enumerator_ `ChildMatches = (1 << 1)`
- L502 _public enumerator_ `FilteredInMask = (MatchesFilter | ChildMatches)`
- L503 _public enumerator_ `Unknown = 0xFC` — ~FilteredInMask

#### class `FSCSEditorTreeNodeComponentBase`  
`class FSCSEditorTreeNodeComponentBase : public FSCSEditorTreeNode`  
_L511-534_
- inherits: `FSCSEditorTreeNode`
- L514 _protected function_ `FSCSEditorTreeNodeComponentBase() : FSCSEditorTreeNode(FSCSEditorTreeNode::ComponentNode)`
- L521 _public prototype_ `virtual FName GetVariableName() const override;` — FSCSEditorTreeNode interface
- L522 _public prototype_ `virtual FString GetDisplayString() const override;`
- L523 _public function_ `virtual bool CanRename() const override`
- L524 _public function_ `virtual bool CanDelete() const override`
- L525 _public prototype_ `virtual bool CanReparent() const override;`
- L526 _public prototype_ `virtual UBlueprint* GetBlueprint() const override;`
- L527 _public prototype_ `virtual FSCSEditorChildActorNodePtrType GetChildActorNode();`
- L528 _public prototype_ `virtual bool MatchesFilterType(const UClass* InFilterType) const override;`
- L533 _private member_ `FSCSEditorChildActorNodePtrType ChildActorNodePtr;` — Child actor node associated with this component node, if applicable.

#### class `FSCSEditorTreeNodeInstancedInheritedComponent`  
`class FSCSEditorTreeNodeInstancedInheritedComponent : public FSCSEditorTreeNodeComponentBase`  
_L540-563_
- inherits: `FSCSEditorTreeNodeComponentBase`
- L548 _public prototype_ `FSCSEditorTreeNodeInstancedInheritedComponent(AActor* Owner, UActorComponent* InComponentTemplate);` — Constructs a wrapper around a component template not contained within an SCS tree node (e.g. "native" components). @param InComponentTemplate The component template represented by this object.
- L551 _public prototype_ `virtual bool IsNativeComponent() const override;` — FSCSEditorTreeNode public interface
- L552 _public prototype_ `virtual bool IsRootComponent() const override;`
- L553 _public prototype_ `virtual bool IsInheritedSCSNode() const override;`
- L554 _public function_ `virtual bool IsInstanced() const override`
- L555 _public function_ `virtual bool IsInheritedComponent() const override`
- L556 _public prototype_ `virtual bool IsDefaultSceneRoot() const override;`
- L557 _public prototype_ `virtual bool CanEdit() const override;`
- L558 _public prototype_ `virtual FText GetDisplayName() const override;`
- L562 _private member_ `TWeakObjectPtr<AActor> InstancedComponentOwnerPtr;`

#### class `FSCSEditorTreeNodeInstanceAddedComponent`  
`class FSCSEditorTreeNodeInstanceAddedComponent : public FSCSEditorTreeNodeComponentBase`  
_L568-598_
- inherits: `FSCSEditorTreeNodeComponentBase`
- L576 _public prototype_ `FSCSEditorTreeNodeInstanceAddedComponent(AActor* Owner, UActorComponent* InComponentTemplate);` — Constructs a wrapper around a component template not contained within an SCS tree node (e.g. "native" components). @param InComponentTemplate The component template represented by this object.
- L579 _public prototype_ `virtual bool IsRootComponent() const override;` — FSCSEditorTreeNode public interface
- L580 _public function_ `virtual bool IsInstanced() const override`
- L581 _public function_ `virtual bool IsUserInstancedComponent() const override`
- L582 _public prototype_ `virtual bool IsDefaultSceneRoot() const override;`
- L583 _public function_ `virtual bool CanEdit() const override`
- L584 _public function_ `virtual FName GetVariableName() const override`
- L585 _public prototype_ `virtual FString GetDisplayString() const override;`
- L586 _public prototype_ `virtual FText GetDisplayName() const override;`
- L587 _public prototype_ `virtual void OnCompleteRename(const FText& InNewName) override;`
- L592 _protected prototype_ `virtual void RemoveMeAsChild() override;` — FSCSEditorTreeNode protected interface
- L596 _private member_ `FName InstancedComponentName;`
- L597 _private member_ `TWeakObjectPtr<AActor> InstancedComponentOwnerPtr;`

#### class `FSCSEditorTreeNodeComponent`  
`class FSCSEditorTreeNodeComponent : public FSCSEditorTreeNodeComponentBase`  
_L603-648_
- inherits: `FSCSEditorTreeNodeComponentBase`
- L612 _public prototype_ `FSCSEditorTreeNodeComponent(class USCS_Node* InSCSNode, bool bInIsInherited = false);` — Constructs a wrapper around a component template contained within an SCS tree node. @param InSCSNode The SCS tree node represented by this object. @param bInIsInherited Whether or not the SCS tree node is inherited from a parent Blueprint class.
- L619 _public prototype_ `FSCSEditorTreeNodeComponent(UActorComponent* InComponentTemplate);` — Constructs a wrapper around a component template not contained within an SCS tree node (e.g. "native" components). @param InComponentTemplate The component template represented by this object.
- L623 _public prototype_ `virtual bool IsNativeComponent() const override;` — FSCSEditorTreeNode public interface
- L624 _public prototype_ `virtual bool IsRootComponent() const override;`
- L625 _public prototype_ `virtual bool IsInheritedSCSNode() const override;`
- L626 _public prototype_ `virtual bool IsDefaultSceneRoot() const override;`
- L627 _public prototype_ `virtual bool CanEdit() const override;`
- L628 _public prototype_ `virtual FText GetDisplayName() const override;`
- L629 _public prototype_ `virtual class USCS_Node* GetSCSNode() const override;`
- L630 _public prototype_ `virtual void OnCompleteRename(const FText& InNewName) override;`
- L635 _protected prototype_ `virtual void RemoveMeAsChild() override;` — FSCSEditorTreeNode protected interface
- L636 _protected prototype_ `virtual UObject* GetOrCreateEditableObjectForBlueprint(UBlueprint* InBlueprint) const override;`
- L640 _protected prototype_ `UActorComponent* INTERNAL_GetOverridenComponentTemplate(UBlueprint* Blueprint) const;` — Get overridden template component, specialized in given blueprint
- L644 _private member_ `bool bIsInheritedSCS;` — Was this component inherited from a parent class or introduced in this class?
- L647 _private member_ `TWeakObjectPtr<class USCS_Node> SCSNodePtr;` — Is this the template coming from an SCS node?

#### class `FSCSEditorTreeNodeActorBase`  
`class FSCSEditorTreeNodeActorBase : public FSCSEditorTreeNode`  
_L650-687_
- inherits: `FSCSEditorTreeNode`
- L653 _public function_ `FSCSEditorTreeNodeActorBase(FSCSEditorTreeNode::ENodeType InNodeType, AActor* InActor) : FSCSEditorTreeNode(InNodeType)`
- L659 _public prototype_ `FSCSEditorTreeNodePtrType GetOwnerNode() const;`
- L660 _public prototype_ `void SetOwnerNode(FSCSEditorTreeNodePtrType NewOwnerNode);`
- L662 _public prototype_ `FSCSEditorTreeNodePtrType GetSceneRootNode() const;`
- L663 _public prototype_ `void SetSceneRootNode(FSCSEditorTreeNodePtrType NewSceneRootNode);`
- L666 _public prototype_ `const TArray<FSCSEditorTreeNodePtrType>& GetComponentNodes() const;` — Returns the set of root nodes
- L669 _public prototype_ `virtual FName GetNodeID() const override;` — FSCSEditorTreeNode public interface
- L670 _public prototype_ `virtual bool IsInstanced() const override;`
- L671 _public function_ `virtual bool CanEdit() const override`
- L672 _public prototype_ `virtual void AddChild(FSCSEditorTreeNodePtrType InChildNodePtr) override;`
- L673 _public prototype_ `virtual void RemoveChild(FSCSEditorTreeNodePtrType InChildNodePtr) override;`
- L674 _public prototype_ `virtual UBlueprint* GetBlueprint() const override;`
- L678 _protected typedef_ `using Super = FSCSEditorTreeNode;`
- L682 _private member_ `FSCSEditorTreeNodePtrType OwnerNodePtr;` — The actor's subtree owner (if valid)
- L684 _private member_ `FSCSEditorTreeNodePtrType SceneRootNodePtr;` — The actor's scene root node (if valid)
- L686 _private member_ `TArray<FSCSEditorTreeNodePtrType> ComponentNodes;` — Root set of components (contains the root scene component and any non-scene component nodes)

#### class `FSCSEditorTreeNodeRootActor`  
`class FSCSEditorTreeNodeRootActor : public FSCSEditorTreeNodeActorBase`  
_L689-713_
- inherits: `FSCSEditorTreeNodeActorBase`
- L692 _public function_ `FSCSEditorTreeNodeRootActor(AActor* InActor, bool bInAllowRename) : FSCSEditorTreeNodeActorBase(FSCSEditorTreeNode::RootActorNode, InActor) , bAllowRename(bInAllowRename) , CachedFilterType(nullptr)`
- L700 _public function_ `virtual bool CanRename() const override` — FSCSEditorTreeNode public interface
- L701 _public prototype_ `virtual void OnCompleteRename(const FText& InNewName) override;`
- L702 _public prototype_ `virtual void AddChild(FSCSEditorTreeNodePtrType InChildNodePtr) override;`
- L703 _public prototype_ `virtual void RemoveChild(FSCSEditorTreeNodePtrType InChildNodePtr) override;`
- L704 _public prototype_ `virtual bool RefreshFilteredState(const UClass* InFilterType, const TArray<FString>& InFilterTerms, bool bRecursive) override;`
- L708 _private member_ `bool bAllowRename;`
- L709 _private member_ `const UClass* CachedFilterType;`
- L710 _private member_ `TArray<FString> CachedFilterTerms;`
- L711 _private member_ `TWeakPtr<class FSCSEditorTreeNodeSeparator> SceneComponentSeparatorNodePtr;`
- L712 _private member_ `TWeakPtr<class FSCSEditorTreeNodeSeparator> NonSceneComponentSeparatorNodePtr;`

#### class `FSCSEditorTreeNodeChildActor`  
`class FSCSEditorTreeNodeChildActor : public FSCSEditorTreeNodeActorBase`  
_L715-728_
- inherits: `FSCSEditorTreeNodeActorBase`
- L718 _public function_ `FSCSEditorTreeNodeChildActor(AActor* InActor) : FSCSEditorTreeNodeActorBase(FSCSEditorTreeNode::ChildActorNode, InActor)`
- L724 _public prototype_ `virtual bool IsFlaggedForFiltration() const override;` — FSCSEditorTreeNode public interface
- L727 _public prototype_ `UChildActorComponent* GetChildActorComponent() const;`

#### class `FSCSEditorTreeNodeSeparator`  
`class FSCSEditorTreeNodeSeparator : public FSCSEditorTreeNode`  
_L730-748_
- inherits: `FSCSEditorTreeNode`
- L733 _public function_ `FSCSEditorTreeNodeSeparator() : FSCSEditorTreeNode(FSCSEditorTreeNode::SeparatorNode)`
- L739 _public function_ `virtual UBlueprint* GetBlueprint() const override` — FSCSEditorTreeNode public interface
- L740 _public prototype_ `virtual bool MatchesFilterType(const UClass* InFilterType) const override;`
- L744 _public prototype_ `void AddFilteredComponentType(const TSubclassOf<UActorComponent>& InFilteredType);` — If the given type matches the tree view filter, the separator will also be flagged for filtration.
- L747 _private member_ `TArray<const UClass*> FilteredTypes;`

#### class `SSCS_RowWidget`  
`class SSCS_RowWidget`  
_L752-759_
- L755 _private function_ `static FSlateColor GetColorTintForIcon(FSCSEditorTreeNodePtrType InNode)` — `UE_DEPRECATED(5.8, "Use FSCSEditorTreeNode::GetColorTintForIcon")`

#### Free symbols / members of external scopes

- L55 _macro_ `#define UE_API KISMET_API`
- L89 _typedef_ `using FSCSEditorTreeNodePtrType = TSharedPtr<class FSCSEditorTreeNode>;` — SCS editor tree node pointer types
- L90 _typedef_ `using FSCSEditorActorNodePtrType = TSharedPtr<class FSCSEditorTreeNodeActorBase>;`
- L91 _typedef_ `using FSCSEditorChildActorNodePtrType = TSharedPtr<class FSCSEditorTreeNodeChildActor>;`
- L104 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Source/Editor/Kismet/Public/SubobjectEditorExtensionContext.h` (Public)


#### class `USubobjectEditorExtensionContext`  
`class USubobjectEditorExtensionContext : public UObject`  
_L18-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L24 _public function_ `const TWeakPtr<SSubobjectEditor>& GetSubobjectEditor() const`
- L31 _private member_ `TWeakPtr<SSubobjectEditor> SubobjectEditor;`
