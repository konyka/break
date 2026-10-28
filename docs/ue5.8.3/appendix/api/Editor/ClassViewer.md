# Editor / ClassViewer

- module root: `Source/Editor/ClassViewer`
- headers: 7; symbols: 251
- symbol kinds: class=13, delegate=3, enum=4, enumerator=11, function=13, macro=1, member=78, namespace=3, prototype=124, struct=1
- DynamicallyLoadedModuleNames: AssetTools, EditorWidgets, GameProjectGeneration
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowserData, Core, CoreUObject, EditorFramework, Engine, InputCore, PropertyEditor, Settings, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools, EditorWidgets, GameProjectGeneration, WorkspaceMenuStructure

### `Source/Editor/ClassViewer/Private/ClassViewerNode.h` (Private)


#### class `FClassViewerNode`  
`class FClassViewerNode : public TSharedFromThis<FClassViewerNode>`  
_L16-118_
- inherits: `TSharedFromThis<FClassViewerNode>`
- L19 _public prototype_ `FClassViewerNode(UClass* Class);`
- L28 _public prototype_ `FClassViewerNode( const FString& InClassName, const FString& InClassDisplayName );` — Creates a node for the widget's tree. @param	InClassName						The name of the class this node represents. @param	InClassDisplayName				The display name of the class this node represents @param	bInIsPlaceable					true if the class is a placeable class.
- L30 _public prototype_ `FClassViewerNode( const FClassViewerNode& InCopyObject);`
- L37 _public prototype_ `void AddChild( TSharedPtr<FClassViewerNode> Child );` — Adds the specified child to the node. @param	Child							The child to be added to this node for the tree.
- L43 _public function_ `TSharedPtr<FString> GetClassName(bool bUseDisplayName = false) const` — Retrieves the class name this node is associated with. This is not the literal UClass name as it is missing the _C for blueprints @param	bUseDisplayName	Whether to use the display name or class name
- L52 _public prototype_ `TSharedPtr<FString> GetClassName(EClassViewerNameTypeToDisplay NameType) const;` — Retrieves the class name this node is associated with. This is not the literal UClass name as it is missing the _C for blueprints @param	NameType	Whether to use the display name or class name
- L55 _public function_ `TArray<TSharedPtr<FClassViewerNode>>& GetChildrenList()` — Retrieves the children list.
- L61 _public prototype_ `bool IsClassPlaceable() const;` — Checks if the class is placeable.
- L64 _public prototype_ `bool IsBlueprintClass() const;` — Checks if this is a blueprint
- L67 _public prototype_ `bool IsEditorOnlyClass() const;` — Checks if this is an editor module class
- L70 _public prototype_ `bool IsRestricted() const;` — Rather this class is not allowed for the specific context
- L73 _public prototype_ `TSharedPtr< FClassViewerNode > GetParentNode() const;` — Get the parent node for this node.
- L77 _private member_ `TSharedPtr<FString> ClassName;` — The nontranslated internal name for this class. This is not necessarily the UClass's name, as that may have _C for blueprints
- L80 _private member_ `TSharedPtr<FString> ClassDisplayName;` — The translated display name for this class
- L83 _private member_ `TArray<TSharedPtr<FClassViewerNode>> ChildrenList;` — List of children.
- L86 _private member_ `TWeakPtr< FClassViewerNode > ParentNode;` — Pointer to the parent to this object.
- L90 _public member_ `TWeakObjectPtr<UClass> Class;` — The class this node is associated with.
- L93 _public member_ `TWeakObjectPtr<UBlueprint> Blueprint;` — The blueprint this node is associated with.
- L96 _public member_ `FTopLevelAssetPath ClassPath;` — Full object path to the class including _C, set for both blueprint and native
- L99 _public member_ `FTopLevelAssetPath ParentClassPath;` — Full object path to the parent class, may be blueprint or native
- L102 _public member_ `FSoftObjectPath BlueprintAssetPath;` — Full path to the Blueprint that this class is loaded from, none for native classes
- L105 _public member_ `bool bPassesFilter;` — true if the class passed the filter.
- L111 _public member_ `bool bPassesFilterRegardlessTextFilter;` — true if the class passed all the sub-filters of the filter (regardless of the TextFilter one). This could be useful to verify e.g., that the parent class of a IsNodeAllowed() object is also valid (even though that parent will not likely pass the TextFilter).
- L114 _public member_ `TSharedPtr< class IUnloadedBlueprintData > UnloadedBlueprintData;` — Data for unloaded blueprints, only valid if the class is unloaded.
- L117 _public member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — The property this node will be working on.

### `Source/Editor/ClassViewer/Private/UnloadedBlueprintData.h` (Private)


#### class `FUnloadedBlueprintData`  
`class FUnloadedBlueprintData : public IUnloadedBlueprintData`  
_L16-65_
- inherits: `IUnloadedBlueprintData`
- L19 _public prototype_ `FUnloadedBlueprintData(TWeakPtr<FClassViewerNode> InClassViewerNode);`
- L21 _public prototype_ `virtual ~FUnloadedBlueprintData() = default;`
- L23 _public prototype_ `virtual bool HasAnyClassFlags(uint32 InFlagsToCheck) const override;`
- L25 _public prototype_ `virtual bool HasAllClassFlags(uint32 InFlagsToCheck) const override;`
- L27 _public prototype_ `virtual void SetClassFlags(uint32 InFlags) override;`
- L29 _public prototype_ `virtual bool ImplementsInterface(const UClass* InInterface) const override;`
- L31 _public prototype_ `virtual bool IsChildOf(const UClass* InClass) const override;`
- L33 _public prototype_ `virtual bool IsA(const UClass* InClass) const override;`
- L35 _public function_ `virtual void SetNormalBlueprintType(bool bInNormalBPType) override`
- L37 _public function_ `virtual bool IsNormalBlueprintType() const override`
- L39 _public prototype_ `virtual TSharedPtr<FString> GetClassName() const override;`
- L41 _public prototype_ `virtual FTopLevelAssetPath GetClassPathName() const override;`
- L43 _public prototype_ `virtual const UClass* GetClassWithin() const override;`
- L45 _public prototype_ `virtual const UClass* GetNativeParent() const override;`
- L48 _public prototype_ `const TWeakPtr<FClassViewerNode>& GetClassViewerNode() const;` — Retrieves the Class Viewer node this data is associated with.
- L51 _public prototype_ `void AddImplementedInterface(const FString& InterfacePath);` — Adds the path of an interface that this blueprint implements directly.
- L55 _private member_ `uint32 ClassFlags = CLASS_None;` — Flags for the class.
- L58 _private member_ `bool bNormalBlueprintType;` — Is this a normal blueprint type?
- L61 _private member_ `TArray<FString> ImplementedInterfaces;` — The full paths for all directly implemented interfaces for this class.
- L64 _private member_ `TWeakPtr<FClassViewerNode> ClassViewerNode;` — The node this class is contained in, used to gather hierarchical data as needed.

### `Source/Editor/ClassViewer/Public/ClassViewerFilter.h` (Public)


#### class `FClassViewerFilterOption`  
`class FClassViewerFilterOption`  
_L37-51_
- desc: Used to define a custom class viewer filter option.
- L41 _public member_ `bool bEnabled = true;` — Whether or not the option is currently enabled (default = true).
- L44 _public member_ `TAttribute<FText> LabelText;` — Localized label text to use for the option in the class viewer's filter menu.
- L47 _public member_ `TAttribute<FText> ToolTipText;` — Localized tooltip text to use for the option in the class viewer's filter menu.
- L50 _public member_ `FOnClassViewerFilterOptionChanged OnOptionChanged;` — Optional external delegate that will be invoked when this filter option is changed.

#### class `IClassViewerFilter`  
`class IClassViewerFilter`  
_L54-118_
- desc: Interface class for creating filters for the Class Viewer.
- L57 _public prototype_ `virtual ~IClassViewerFilter() = default;`
- L66 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs ) = 0;` — Checks if a class is allowed by this filter. @param InInitOptions				The Class Viewer/Picker options. @param InClass					The class to be tested. @param InFilterFuncs				Useful functions for filtering.
- L75 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const class IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs) = 0;` — Checks if a class is allowed by this filter. @param InInitOptions				The Class Viewer/Picker options. @param InUnloadedClassData		The information for the unloaded class to be tested. @param InFilterFuncs				Useful functions for filtering.
- L117 _public function_ `virtual void GetFilterOptions(TArray<TSharedRef<FClassViewerFilterOption>>& OutFilterOptions)` — Can be optionally implemented to gather additional filter flags. If present, these will be added into the View Options menu where they can be toggled on/off by the user. Example: In the following case, we define a custom filter option to allow the user to toggle the entire filter on/off. This is synced with a global config setting (MyFilterConfigSettings->bIsCustomFilterEnabled) that is checked at filtering time. void FMyCustomClassFilter::GetFilterOptions(TArray<TSharedRef<FClassViewerFilterOption>>& OutFilterOptions) { TSharedRef<FClassViewerFilterOption> MyFilterOption = MakeShared<FClassViewerFilterOption>(); MyFilterOption->bEnabled = MyFilterConfigSettings->bIsCustomFilterEnabled; MyFilterOption->LabelText = LOCTEXT("MyCustomFilterOptionLabel", "My Custom Filter"); MyFilterOption->ToolTipText = LOCTEXT("MyCustomFilterOptionToolTip", "Enable or disable my custom class filter."); MyFilterOption->OnOptionChanged = FOnClassViewerFilterOptionChanged::CreateSP(this, &FMyCustomClassFilter::OnOptionChanged); OutFilterOptions.Add(MyFilterOption); } void FMyCustomClassFilter::OnOptionChanged(bool bIsEnabled) { // Updates the filter's config setting whenever the user changes the option. MyFilterConfigSettings->bIsCustomFilterEnabled = bIsEnabled; } bool FMyCustomClassFilter::IsClassAllowed(...) { if(!MyFilterConfigSettings->bIsCustomFilterEnabled) { // Filter is disabled; always allow the class. return true; } // ... } @param OutFilterOptions		On output, contains the set of option

#### class `FClassViewerFilter`  
`class FClassViewerFilter : public IClassViewerFilter`  
_L121-147_
- inherits: `IClassViewerFilter`
- desc: Filter class that performs many common checks.
- L124 _public prototype_ `FClassViewerFilter(const FClassViewerInitializationOptions& InInitOptions);`
- L133 _public prototype_ `virtual bool IsNodeAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<FClassViewerNode>& Node, const bool bCheckTextFilter);` — This function checks whether a node passes the filter defined by IsClassAllowed/IsUnloadedClassAllowed. @param InInitOptions				The Class Viewer/Picker options. @param Node						The Node to check. @param bCheckTextFilter			Whether to check the TextFilter. Disabling it could be useful e.g., to verify that the parent class of a IsNodeAllowed() object is also valid (regardless of the TextFilter, which will likely fail to pass).
- L135 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs ) override;`
- L136 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs, const bool bCheckTextFilter);`
- L137 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const class IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< class FClassViewerFilterFuncs > InFilterFuncs) override;`
- L140 _public member_ `TArray<UClass*> InternalClasses;`
- L141 _public member_ `TArray<FDirectoryPath> InternalPaths;`
- L142 _public member_ `FOnShouldFilterClass FilterDelegate;`
- L143 _public member_ `TSharedRef<FTextFilterExpressionEvaluator> TextFilter;`
- L144 _public member_ `TSharedRef<FClassViewerFilterFuncs> FilterFunctions;`
- L145 _public member_ `TSharedPtr<IAssetReferenceFilter> AssetReferenceFilter;`
- L146 _public member_ `const IAssetRegistry& AssetRegistry;`

#### enum `EFilterReturn::Type`  
`enum Type`  
_L151-151_
- L151 _public enumerator_ `enum Type{ Failed = 0, Passed, NoItems };`
- L151 _public enumerator_ `enum Type{ Failed = 0, Passed, NoItems };`
- L151 _public enumerator_ `enum Type{ Failed = 0, Passed, NoItems };`

#### class `FClassViewerFilterFuncs`  
`class FClassViewerFilterFuncs`  
_L153-278_
- L157 _public prototype_ `virtual ~FClassViewerFilterFuncs() = default;`
- L167 _public prototype_ `virtual EFilterReturn::Type IfInChildOfClassesSet(TSet< const UClass* >& InSet, const UClass* InClass);` — Checks if the given Class is a child-of any of the classes in a set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if it is a child-of a class in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L177 _public prototype_ `virtual EFilterReturn::Type IfInChildOfClassesSet(TSet< const UClass* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if the given Class is a child-of any of the classes in a set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if it is a child-of a class in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L187 _public prototype_ `virtual EFilterReturn::Type IfMatchesAllInChildOfClassesSet(TSet< const UClass* >& InSet, const UClass* InClass);` — Checks if the given Class is a child-of ALL of the classes in a set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if it is a child-of ALL the classes in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L197 _public prototype_ `virtual EFilterReturn::Type IfMatchesAllInChildOfClassesSet(TSet< const UClass* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if the given Class is a child-of ALL of the classes in a set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if it is a child-of ALL the classes in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L207 _public prototype_ `virtual EFilterReturn::Type IfMatchesAll_ObjectsSetIsAClass(TSet< const UObject* >& InSet, const UClass* InClass);` — Checks if ALL the Objects has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if ALL the Objects set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L217 _public prototype_ `virtual EFilterReturn::Type IfMatchesAll_ObjectsSetIsAClass(TSet< const UObject* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if ALL the Objects has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if ALL the Objects set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L227 _public prototype_ `virtual EFilterReturn::Type IfMatchesAll_ClassesSetIsAClass(TSet< const UClass* >& InSet, const UClass* InClass);` — Checks if ALL the Classes set has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if ALL the Classes set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L237 _public prototype_ `virtual EFilterReturn::Type IfMatchesAll_ClassesSetIsAClass(TSet< const UClass* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if ALL the Classes set has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if ALL the Classes set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L247 _public prototype_ `virtual EFilterReturn::Type IfMatches_ClassesSetIsAClass(TSet< const UClass* >& InSet, const UClass* InClass);` — Checks if any in the Classes set has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if the Classes set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L257 _public prototype_ `virtual EFilterReturn::Type IfMatches_ClassesSetIsAClass(TSet< const UClass* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if any in the Classes set has a Is-A relationship with the passed in class. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if the Classes set IsA the passed class, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L267 _public prototype_ `virtual EFilterReturn::Type IfInClassesSet(TSet< const UClass* >& InSet, const UClass* InClass);` — Checks if the Class is in the Classes set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if the Class is in the Classes set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L277 _public prototype_ `virtual EFilterReturn::Type IfInClassesSet(TSet< const UClass* >& InSet, const TSharedPtr< const class IUnloadedBlueprintData > InClass);` — Checks if the Class is in the Classes set. @param InSet				The set to test against. @param InClass			The class to test against. @return					EFilterReturn::Passed if the Class is in the Classes set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.

#### class `IUnloadedBlueprintData`  
`class IUnloadedBlueprintData`  
_L280-367_
- L292 _public prototype_ `virtual bool HasAnyClassFlags( uint32 InFlagsToCheck ) const = 0;` — Used to safely check whether the passed in flag is set. @param	InFlagsToCheck		Class flag to check for @return	true if the passed in flag is set, false otherwise (including no flag passed in, unless the FlagsToCheck is CLASS_AllFlags)
- L300 _public prototype_ `virtual bool HasAllClassFlags( uint32 InFlagsToCheck ) const = 0;` — Used to safely check whether all of the passed in flags are set. @param InFlagsToCheck	Class flags to check for @return true if all of the passed in flags are set (including no flags passed in), false otherwise
- L307 _public prototype_ `virtual void SetClassFlags(uint32 InFlags) = 0;` — Sets the flags for this class. @param InFlags		The flags to be set to.
- L314 _public prototype_ `virtual bool ImplementsInterface(const UClass* InInterface) const = 0;` — This will return whether or not this class implements the passed in class / interface @param InInterface - the interface to check and see if this class implements it
- L323 _public prototype_ `virtual bool IsChildOf(const UClass* InClass) const = 0;` — Checks whether or not the class is a child-of the passed in class. @param InClass		The class to check against. @return				true if it is a child-of the passed in class.
- L332 _public prototype_ `virtual bool IsA(const UClass* InClass) const = 0;` — Checks whether or not the class has an Is-A relationship with the passed in class. @param InClass		The class to check against. @return				true if it has an Is-A relationship to the passed in class.
- L339 _public prototype_ `virtual const UClass* GetClassWithin() const = 0;` — Attempts to get the ClassWithin property for this class. @return ClassWithin of the child most Native class in the hierarchy.
- L346 _public prototype_ `virtual const UClass* GetNativeParent() const = 0;` — Attempts to get the child-most Native class in the hierarchy. @return The child-most Native class in the hierarchy.
- L351 _public prototype_ `virtual void SetNormalBlueprintType(bool bInNormalBPType) = 0;` — Set whether or not this blueprint is a normal blueprint.
- L356 _public prototype_ `virtual bool IsNormalBlueprintType() const = 0;` — Get whether or not this blueprint is a normal blueprint.
- L361 _public prototype_ `virtual TSharedPtr<FString> GetClassName() const = 0;` — Get the generated class name of this blueprint.
- L366 _public prototype_ `virtual FTopLevelAssetPath GetClassPathName() const = 0;` — Get the class path of this blueprint.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CLASSVIEWER_API`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnClassViewerFilterOptionChanged, bool);` — Delegate used to respond to a filter option change. The argument will indicate whether the option was enabled or disabled.
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnClassViewerFilterOptionChanged, bool);` — Delegate used to respond to a filter option change. The argument will indicate whether the option was enabled or disabled.
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterClass, const UClass* );` — Called to check if a class should be filtered out by external code. Return true to exclude the class from the view.
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnShouldFilterClass, const UClass* );` — Called to check if a class should be filtered out by external code. Return true to exclude the class from the view.
- L149 _namespace_ `namespace EFilterReturn`

### `Source/Editor/ClassViewer/Public/ClassViewerModule.h` (Public)


#### enum `EClassViewerMode::Type`  
`enum Type`  
_L29-36_
- L32 _public enumerator_ `ClassBrowsing` — Allows all classes to be browsed and selected; syncs selection with the editor; drag and drop attachment, etc.
- L35 _public enumerator_ `ClassPicker` — Sets the class viewer to operate as a class 'picker'.

#### enum `EClassViewerDisplayMode::Type`  
`enum Type`  
_L41-51_
- L44 _public enumerator_ `DefaultView` — Default will choose what view mode based on if in Viewer or Picker mode.
- L47 _public enumerator_ `TreeView` — Displays all classes as a tree.
- L50 _public enumerator_ `ListView` — Displays all classes as a list.

#### enum `EClassViewerNameTypeToDisplay`  
`enum class EClassViewerNameTypeToDisplay : uint8`  
_L54-64_
- L57 _public enumerator_ `Dynamic` — Display both the display name and class name if they're available and different.
- L60 _public enumerator_ `DisplayName` — Always use the display name
- L63 _public enumerator_ `ClassName` — Always use the class name

#### struct `FClassViewerSortElementInfo`  
`struct FClassViewerSortElementInfo`  
_L66-77_
- L68 _public function_ `FClassViewerSortElementInfo(TWeakObjectPtr<UClass> InClass, TSharedPtr<FString> InName, TSharedPtr<FString> InDisplayName) : Class(InClass), Name(InName), DisplayName(InDisplayName)`
- L72 _public member_ `TWeakObjectPtr<UClass> Class;`
- L74 _public member_ `TSharedPtr<FString> Name;`
- L76 _public member_ `TSharedPtr<FString> DisplayName;`

#### class `FClassViewerInitializationOptions`  
`class FClassViewerInitializationOptions`  
_L83-182_
- desc: Settings for the Class Viewer set by the programmer before spawning an instance of the widget.  This is used to modify the class viewer's behavior in various ways, such as filtering in or out specific classes.
- L88 _public member_ `TArray<TSharedRef<IClassViewerFilter>> ClassFilters;` — The filter(s) to use on classes in this instance.
- L91 _public member_ `TFunction<bool(const FClassViewerSortElementInfo&, const FClassViewerSortElementInfo&)> ClassViewerSortPredicate;` — Predicate used to sort the class list
- L94 _public member_ `EClassViewerMode::Type Mode;` — Mode to operate in
- L97 _public member_ `EClassViewerDisplayMode::Type DisplayMode;` — Mode to display the classes using.
- L100 _public member_ `bool bIsActorsOnly;` — Filters so only actors will be displayed.
- L103 _public member_ `bool bIsPlaceableOnly;` — Filters so only placeable actors will be displayed. Forces bIsActorsOnly to true.
- L106 _public member_ `bool bIsBlueprintBaseOnly;` — Filters so only base blueprints will be displayed.
- L109 _public member_ `bool bShowUnloadedBlueprints;` — Shows unloaded blueprints. Will not be filtered out based on non-bool filter options.
- L112 _public member_ `bool bShowNoneOption;` — Shows a "None" option, only available in Picker mode.
- L115 _public member_ `bool bShowObjectRootClass;` — true will show the UObject root class.
- L118 _public member_ `bool bExpandRootNodes;` — If true, root nodes will be expanded by default.
- L121 _public member_ `bool bExpandAllNodes;` — If true, all nodes will be expanded by default.
- L124 _public member_ `bool bEnableClassDynamicLoading;` — true allows class dynamic loading on selection
- L127 _public member_ `EClassViewerNameTypeToDisplay NameTypeToDisplay;` — Controls what name is shown for classes
- L130 _public member_ `FText ViewerTitleString;` — the title string of the class viewer if required.
- L133 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property this class viewer be working on.
- L136 _public member_ `TArray<FAssetData> AdditionalReferencingAssets;` — The passed in property handle will be used to gather referencing assets. If additional referencing assets should be reported, supply them here.
- L139 _public member_ `bool bAllowViewOptions;` — true (the default) shows the view options at the bottom of the class picker
- L142 _public member_ `bool bShowBackgroundBorder = true;` — true (the default) shows a background border behind the class viewer widget.
- L145 _public member_ `TArray<UClass*> ExtraPickerCommonClasses;` — Defines additional classes you want listed in the "Common Classes" section for the picker.
- L148 _public member_ `bool bEditorClassesOnly;` — false by default, restricts the class picker to only showing editor module classes
- L151 _public member_ `UClass* InitiallySelectedClass;` — Will set the initially selected row, if possible, to this class when the viewer is created
- L154 _public member_ `bool bShowDefaultClasses;` — (true) Will show the default classes if they exist.
- L157 _public member_ `bool bShowClassesViewer;` — (true) Will show the classes viewer.
- L162 _public function_ `FClassViewerInitializationOptions() : Mode( EClassViewerMode::ClassPicker ) , DisplayMode(EClassViewerDisplayMode::DefaultView) , bIsActorsOnly(false) , bIsPlaceableOnly(false) , bIsBlueprintBaseOnly(false) , bShowUnloadedBlueprints(true) , bShowNoneOption(false) , bShowObjectRootClass(false) , bExpandRootNodes(true) , bExpandAllNodes(false) , bEnableClassDynamicLoading(true) , NameTypeToDisplay(EClassViewerNameTypeToDisplay::ClassName) , bAllowViewOptions(true) , bEditorClassesOnly(false) , InitiallySelectedClass(nullptr) , bShowDefaultClasses(true) , bShowClassesViewer(true)` — Constructor

#### class `FClassViewerModule`  
`class FClassViewerModule : public IModuleInterface`  
_L187-232_
- inherits: `IModuleInterface`
- desc: Class Viewer module
- L195 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L200 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L210 _public prototype_ `virtual TSharedRef<SWidget> CreateClassViewer(const FClassViewerInitializationOptions& InitOptions, const FOnClassPicked& OnClassPickedDelegate );` — Creates a class viewer widget @param	InitOptions						Programmer-driven configuration for this widget instance @param	OnClassPickedDelegate			Optional callback when a class is selected in 'class picking' mode @return	New class viewer widget
- L215 _public prototype_ `virtual TSharedRef<IClassViewerFilter> CreateClassFilter(const FClassViewerInitializationOptions& InitOptions);` — Create a new class filter from the given initialization options.
- L217 _public prototype_ `virtual TSharedRef<FClassViewerFilterFuncs> CreateFilterFuncs();`
- L220 _public prototype_ `virtual void RegisterGlobalClassViewerFilter(const TSharedRef<IClassViewerFilter>& Filter);` — Registers a global filter that affects all class viewer instances (gets combined any local filter)
- L223 _public prototype_ `virtual const TSharedPtr<IClassViewerFilter>& GetGlobalClassViewerFilter();` — Returns the global filter that affects all class viewer instances
- L225 _public function_ `FSimpleMulticastDelegate& GetOnGlobalClassViewerFilterModified()`
- L229 _private member_ `TSharedPtr<IClassViewerFilter> GlobalClassViewerFilter;`
- L231 _private member_ `FSimpleMulticastDelegate OnGlobalClassViewerFilterModified;`

#### Free symbols / members of external scopes

- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorClassViewer, Log, All);`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam( FOnClassPicked, UClass* );` — Delegate used with the Class Viewer in 'class picking' mode.  You'll bind a delegate when the class viewer widget is created, which will be fired off when a class is selected in the list
- L25 _prototype_ `DECLARE_DELEGATE_OneParam( FOnClassPicked, UClass* );` — Delegate used with the Class Viewer in 'class picking' mode.  You'll bind a delegate when the class viewer widget is created, which will be fired off when a class is selected in the list
- L27 _namespace_ `namespace EClassViewerMode`
- L39 _namespace_ `namespace EClassViewerDisplayMode`

### `Source/Editor/ClassViewer/Public/ClassViewerProjectSettings.h` (Public)


#### class `UClassViewerProjectSettings`  
`class UClassViewerProjectSettings : public UObject`  
_L24-37_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Class Viewer Project Settings
- L31 _private member_ `TArray<FDirectoryPath> InternalOnlyPaths;` — `UPROPERTY(EditAnywhere, config, Category = ClassVisibilityManagement, meta = (DisplayName = "List of directories to consider Internal Only.", ContentDir, LongPackageName))` — The base directories to be considered Internal Only for the class picker.
- L35 _private member_ `TArray<FSoftClassPath> InternalOnlyClasses;` — `UPROPERTY(EditAnywhere, config, Category = ClassVisibilityManagement, meta = (MetaClass = "/Script/CoreUObject.Object", DisplayName = "List of base classes to consider Internal Only.", AllowAbstract = "true", ShowTreeView, HideViewOptions))` — The base classes to be considered Internal Only for the class picker.

### `Source/Editor/ClassViewer/Public/SClassViewer.h` (Public)


#### class `SClassViewer`  
`class SClassViewer : public SCompoundWidget`  
_L57-317_
- inherits: `SCompoundWidget`
- L60 _public function_ `SLATE_BEGIN_ARGS( SClassViewer )`
- L64 _public prototype_ `SLATE_ARGUMENT( FOnClassPicked, OnClassPickedDelegate ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FClassViewerInitializationOptions& InInitOptions);`
- L77 _public prototype_ `virtual TSharedRef<SWidget> GetContent();` — Gets the widget contents of the app
- L79 _public prototype_ `virtual ~SClassViewer();`
- L82 _public prototype_ `virtual void ClearSelection();` — Empty the selection set.
- L85 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L86 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L87 _public prototype_ `virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;`
- L88 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L91 _public prototype_ `virtual bool IsClassAllowed(const UClass* InClass) const;` — Test to see whether the given class would be allowed by this class viewer
- L94 _public prototype_ `void Refresh();` — Sends a requests to the Class Viewer to refresh itself the next chance it gets
- L97 _public prototype_ `static void RequestPopulateClassHierarchy();` — Requests a repopulation of the internal Class Hierarchy database
- L100 _public prototype_ `static void DestroyClassHierarchy();` — Destroys the internal Class Hierarchy database
- L107 _private prototype_ `void OnGetChildrenForClassViewerTree( TSharedPtr<FClassViewerNode> InParent, TArray< TSharedPtr< FClassViewerNode > >& OutChildren );` — Retrieves the children for the input node. @param InParent				The parent node to retrieve the children from. @param OutChildren			List of children for the parent node.
- L110 _private prototype_ `TSharedRef< ITableRow > OnGenerateRowForClassViewer( TSharedPtr<FClassViewerNode> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Creates the row widget when called by Slate when an item appears on the tree.
- L113 _private prototype_ `FReply OnDragDetected( const FGeometry& Geometry, const FPointerEvent& PointerEvent ) override;` — Invoked when the user attempts to drag an item out of the class browser
- L116 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called by Slate when the filter box changes text.
- L119 _private prototype_ `void OnFilterTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Called when enter is hit in search box
- L122 _private prototype_ `void OnClassViewerSelectionChanged( TSharedPtr<FClassViewerNode> Item, ESelectInfo::Type SelectInfo );` — Called by Slate when an item is selected from the tree/list.
- L125 _private prototype_ `void OnClassViewerExpansionChanged(TSharedPtr<FClassViewerNode> Item, bool bExpanded);` — Called by Slate when an item is expanded/collapsed from the tree/list.
- L128 _private prototype_ `bool Menu_CanExecute() const;` — A simple function for the filters to keep them enabled.
- L131 _private prototype_ `void MenuActorsOnly_Execute();` — Toggles "Actors Only" true/false.
- L134 _private prototype_ `bool MenuActorsOnly_IsChecked() const;` — Returns the state of "Actors Only".
- L137 _private prototype_ `void MenuPlaceableOnly_Execute();` — Toggles "Placeable Only" true/false.
- L140 _private prototype_ `bool MenuPlaceableOnly_IsChecked() const;` — Returns the state of "Placeable Only".
- L143 _private prototype_ `void MenuBlueprintBasesOnly_Execute();` — Toggles "Blueprint Bases Only" true/false.
- L146 _private prototype_ `bool MenuBlueprintBasesOnly_IsChecked() const;` — Returns the state of "Blueprint Bases Only".
- L149 _private prototype_ `TSharedRef<SWidget> FillFilterEntries();` — Fills in the filter menu.
- L156 _private prototype_ `void SetAllExpansionStates(bool bInExpansionState);` — Sets all expansion states in the tree. @param bInExpansionState			The expansion state to set the tree to.
- L164 _private prototype_ `void SetAllExpansionStates_Helper(TSharedPtr< FClassViewerNode > InNode, bool bInExpansionState);` — A helper function to recursively set the tree. @param	InNode						The current node in the tree. @param	bInExpansionState			The expansion state to set the tree to.
- L171 _private prototype_ `void ToggleExpansionState_Helper(TSharedPtr< FClassViewerNode > InNode);` — A helper function to toggle expansion state of a single node @param	InNode						The node to toggle expansion.
- L174 _private prototype_ `TSharedPtr< SWidget > BuildMenuWidget();` — Builds the right click menu widget for the selected node.
- L177 _private prototype_ `void OnOpenBlueprintTool();` — Menu context option to open the currently selected Blueprint in the editor.
- L180 _private prototype_ `void FindInContentBrowser();` — Menu context option to find the selected object in the content browser.
- L187 _private prototype_ `bool ExpandFilteredInNodes(TSharedPtr<FClassViewerNode> InNode);` — Recursive function to expand nodes not filtered out of the tree @param	InNode				The current node to inspect for expansion. @return bool				true if the child expanded, thus the parent should.
- L192 _private prototype_ `void MapExpansionStatesInTree( TSharedPtr<FClassViewerNode> InItem );` — Recursive function to map the expansion states of items in the tree. @param InItem		The current item to examine the expansion state of.
- L197 _private prototype_ `void SetExpansionStatesInTree( TSharedPtr<FClassViewerNode> InItem );` — Recursive function to set the expansion states of items in the tree. @param InItem		The current item to set the expansion state of.
- L200 _private prototype_ `void Populate();` — Populates the tree with items based on the current filter.
- L203 _private prototype_ `TSharedPtr<FClassViewerNode> CreateNoneOption();` — Creates a "None" option for the tree/list.
- L206 _private prototype_ `const TArray< TSharedPtr< FClassViewerNode > > GetSelectedItems() const;` — Returns an array of the currently selected ClassViewerNodes
- L209 _private prototype_ `virtual void ExpandRootNodes();` — Expands all of the root nodes
- L214 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent();` — Handler for when the view combo button is clicked
- L217 _private prototype_ `FText GetClassCountText() const;` — Gets the text for the class count label
- L220 _private prototype_ `void SetCurrentDeveloperViewType(EClassViewerDeveloperType NewType);` — Sets the view type and updates lists accordingly
- L223 _private prototype_ `void CreateCurrentDeveloperView();` — Clears the reference to the current view and creates a new one, based on CurrentViewType
- L226 _private prototype_ `EClassViewerDeveloperType GetCurrentDeveloperViewType() const;` — Gets the current view type (list or tile)
- L229 _private prototype_ `bool IsCurrentDeveloperViewType(EClassViewerDeveloperType ViewType) const;` — Returns true if ViewType is the current view type
- L232 _private prototype_ `void ToggleShowInternalClasses();` — Toggle whether internal use classes should be shown or not
- L235 _private prototype_ `bool IsShowingInternalClasses() const;` — Whether or not it's possible to show internal use classes
- L238 _private prototype_ `bool IsToggleShowInternalClassesAllowed() const;` — Whether or not it's possible to show internal use classes
- L241 _private prototype_ `void ToggleCustomFilterOption(TSharedRef<FClassViewerFilterOption> FilterOption);` — Toggle whether a custom class filter option is enabled
- L244 _private prototype_ `bool IsCustomFilterOptionEnabled(TSharedRef<FClassViewerFilterOption> FilterOption) const;` — Returns whether a custom class filter option is currently enabled
- L247 _private prototype_ `const int GetNumItems() const;` — Get the total number of classes passing the current filters.
- L250 _private prototype_ `int32 CountTreeItems(FClassViewerNode* Node);` — Count the number of tree items in the specified hierarchy
- L253 _private prototype_ `void HandleSettingChanged(FName PropertyName);` — Handle the settings for ClassViewer changing.
- L256 _private prototype_ `void GetInternalOnlyClasses(TArray<FSoftClassPath>& Classes);` — Accessor for the classnames that have been marked as internal only in settings
- L259 _private prototype_ `void GetInternalOnlyPaths(TArray<FDirectoryPath>& Paths);` — Accessor for the class paths that have been marked as internal only in settings
- L262 _private member_ `FClassViewerInitializationOptions InitOptions;` — Init options, cached
- L265 _private member_ `TSharedPtr<FClassViewerFilter> ClassFilter;` — Filter to use to determine what classes are valid.
- L268 _private member_ `TArray< TSharedPtr< FClassViewerNode > > RootTreeItems;` — The items to be displayed in the tree.
- L271 _private member_ `TSharedPtr<STreeView<TSharedPtr< FClassViewerNode > >> ClassTree;` — Holds the Slate Tree widget which holds the classes for the Class Viewer.
- L274 _private member_ `TSharedPtr<SListView<TSharedPtr< FClassViewerNode > >> ClassList;` — Holds the Slate List widget which holds the classes for the Class Viewer.
- L277 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The Class Search Box, used for filtering the classes visible.
- L280 _private member_ `bool bEnableClassDynamicLoading;` — true to allow class dynamic loading.
- L283 _private member_ `FOnClassPicked OnClassPicked;` — Callback that's fired when a class is selected while in 'class picking' mode
- L286 _private member_ `UClass* RightClickClass;` — The class currently right clicked on.
- L289 _private member_ `UBlueprint* RightClickBlueprint;` — The blueprint currently right clicked on.
- L292 _private member_ `int32 RightClickClassIndex;` — The index of the class currently right clicked on.
- L295 _private member_ `bool bSaveExpansionStates;` — true if expansions states should be saved when compiling.
- L298 _private member_ `TMap< FString, bool > ExpansionStateMap;` — The map holding the expansion state map for the tree.
- L301 _private member_ `bool bNeedsRefresh;` — True if the Class Viewer needs to be repopulated at the next appropriate opportunity, occurs whenever classes are added, removed, renamed, etc.
- L304 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L307 _private member_ `bool bPendingSetExpansionStates;` — True if we need to set the tree expansion states according to our local copy next tick
- L310 _private member_ `TSharedPtr<SComboButton> ViewOptionsComboButton;` — The button that displays view options
- L313 _private member_ `int NumClasses;` — Number of classes that passed the filter
- L316 _private member_ `TArray<TSharedRef<FClassViewerFilterOption>> CustomClassFilterOptions;` — Custom filter options for the View Options menu

### `Source/Editor/ClassViewer/Public/VerseClassConstraintFilters.h` (Public)


#### class `FVerseConcreteClassFilter`  
`class FVerseConcreteClassFilter : public IClassViewerFilter`  
_L7-20_
- inherits: `IClassViewerFilter`
- L11 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override`
- L16 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const class IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<class FClassViewerFilterFuncs> InFilterFuncs) override`

#### class `FVerseCastableClassFilter`  
`class FVerseCastableClassFilter : public IClassViewerFilter`  
_L22-35_
- inherits: `IClassViewerFilter`
- L26 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override`
- L31 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const class IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<class FClassViewerFilterFuncs> InFilterFuncs) override`
