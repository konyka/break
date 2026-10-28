# Plugins / RigVMEditor

- module root: `Plugins/Runtime/RigVM/Source/RigVMEditor`
- headers: 103; symbols: 4430
- symbol kinds: class=181, delegate=114, enum=19, enumerator=101, externvar=2, function=704, macro=74, member=1018, namespace=38, prototype=2095, struct=52, typedef=32
- PrivateDependencyModuleNames: ApplicationCore, FieldNotification, InputCore, Json, JsonUtilities, ToolWidgets, TraceLog, WorkspaceMenuStructure
- PublicDependencyModuleNames: AnimationCore, AnimationEditorWidgets, AnimationWidgets, AppFramework, ApplicationCore, BlueprintGraph, ContentBrowser, ContentBrowserData, Core, CoreUObject, EditorFramework, Engine, GameplayInsights, GraphEditor, InputCore, Kismet, KismetCompiler, KismetWidgets, MessageLog, PropertyEditor, PythonScriptPlugin, RHI, RenderCore, RewindDebuggerInterface, RigVM, RigVMDeveloper, Scribble, ScribbleEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, TraceAnalysis, TraceLog, TraceServices, UMG, UnrealEd, WidgetRegistration

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Internal/Editor/RigVMEdGraphNodeRegistry.h` (Internal)


#### class `UE::RigVMEditor::FRigVMEdGraphNodeRegistry`  
`class FRigVMEdGraphNodeRegistry : public TSharedFromThis<FRigVMEdGraphNodeRegistry>`  
_L23-97_
- inherits: `TSharedFromThis<FRigVMEdGraphNodeRegistry>`
- desc: Template to track existence of Rig VM Ed Graph Nodes for nodes of a specific Rig VM Node type in editor.
- L29 _public prototype_ `FRigVMEdGraphNodeRegistry() = default;`
- L32 _public prototype_ `FRigVMEdGraphNodeRegistry(const TScriptInterface<IRigVMEditorAssetInterface>& InRigVMAssetInterface, UClass* InRigVMNodeClass, FPrivateToken);` — Constructor, not ment to be used, instead use GetOrCreateRegistry to create instances.
- L44 _public prototype_ `static TSharedRef<FRigVMEdGraphNodeRegistry> GetOrCreateRegistry( const TScriptInterface<IRigVMEditorAssetInterface>& InRigVMAssetInterface, UClass* InRigVMNodeClass, const bool bForceUpdate = false);` — Creates a registry instance. Note, The registry will be destroyed when the all references are released. @param InRigVMAssetInterface			The Asset for which this registry is constructed @param InRigVMNodeClass				The Rig VM Node Class for which Ed Graph nodes are held @param bForceUpdate					(Optional) If set to true, the registry instantly updates. @return								The registry instance
- L50 _public function_ `const TArray<TWeakObjectPtr<URigVMEdGraphNode>>& GetConnectedEdGrapNodes() const` — Returns the currently registered ed graph nodes which correspond to the node type and have connected pins
- L53 _public function_ `const TArray<TWeakObjectPtr<URigVMEdGraphNode>>& GetDisconnectedEdGrapNodes() const` — Returns the currently registered ed graph nodes which correspond to the node type and do not have any connected pins
- L56 _public member_ `FSimpleMulticastDelegate OnPostRegistryUpdated;` — Delegate broadcasted when the registry was updated
- L59 _public function_ `const UClass* GetType() const` — Returns the node type this registry is tracking
- L63 _private prototype_ `void Initialize();` — Initializes the registry
- L66 _private prototype_ `void RequestUpdate();` — Requests to Update the registry
- L72 _private prototype_ `void ForceUpdate();` — Forces the registry to update. Mind the registry tracks changes and notifies via OnPostRegistryUpdated. ForceUpdate only needs to be called where handling changes via OnPostRegistryUpdated is not adequate.
- L75 _private prototype_ `void PostGraphModified(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);` — Called after a graph was modified
- L78 _private prototype_ `bool IsNodeConnected(const URigVMEdGraphNode& EdGraphNode, const bool bOnlyConsiderExecPin) const;` — Returns true if the node is considered connected
- L81 _private member_ `TArray<TWeakObjectPtr<URigVMEdGraphNode>> WeakConnectedEdGraphNodes;` — The currently registered nodes that have any pin connected
- L84 _private member_ `TArray<TWeakObjectPtr<URigVMEdGraphNode>> WeakDisconnectedEdGraphNodes;` — The currently registered nodes that do not have any pin connected
- L87 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakAssetInterface;` — The asset interface this registry refers to
- L90 _private member_ `UClass* RigVMNodeClass = nullptr;` — The Rig VM Node type that is tracked in this registry
- L93 _private member_ `FTimerHandle RequestUpdateTimerHandle;` — Timer handle to notify when the registry was fully updated
- L96 _private member_ `static TMap<FName, TWeakPtr<FRigVMEdGraphNodeRegistry>> TypeIDToRegistryMap;` — Map of registry IDs with their unique registry, useful to reuse registries of same type and asset

#### struct `UE::RigVMEditor::FRigVMEdGraphNodeRegistry::FPrivateToken`  
`struct FPrivateToken`  
_L26-26_
- L26 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMBlueprintAssetHandler.h` (Private)


#### class `IRigVMBlueprintAssetHandler`  
`class IRigVMBlueprintAssetHandler`  
_L23-44_
- desc: Interface used to define how to interact with a blueprint within an asset
- L26 _public prototype_ `virtual ~IRigVMBlueprintAssetHandler() = default;`
- L34 _public prototype_ `virtual UBlueprint* RetrieveBlueprint(UObject* InAsset) const = 0;` — Retrieve the blueprint from the specified asset object @param InAsset         The asset object to retrieve the blueprint from @return The blueprint contained within the specified asset, or nullptr if non exists
- L43 _public prototype_ `virtual bool AssetContainsBlueprint(const FAssetData& InAssetData) const = 0;` — Check whether the specified asset registry data contains a blueprint @param InAssetData     The asset object to retrieve the blueprint from @return True if the asset contains a blueprint, false otherwise

#### class `FRigVMBlueprintAssetHandler`  
`class FRigVMBlueprintAssetHandler`  
_L50-111_
- desc: Singleton class that marshals different blueprint asset handlers for different asset class types
- L57 _public prototype_ `static FRigVMBlueprintAssetHandler& Get();` — Retrieve the singleton instance of this class
- L63 _public function_ `TArrayView<const FTopLevelAssetPath> GetRegisteredClassNames() const` — Get all the currently registered class names
- L76 _public function_ `template<typename HandlerType> void RegisterHandler(FTopLevelAssetPath ClassPathName)` — Register an asset for the specified class name @note: Any assets whose class is a child of the specified class will use this handler (unless there is a more specific handler registered) @param ClassName      The name of the class this handler relates to.
- L89 _public prototype_ `void RegisterHandler(FTopLevelAssetPath ClassPathName, TUniquePtr<IRigVMBlueprintAssetHandler>&& InHandler);` — Register an asset for the specified class name @note: Any assets whose class is a child of the specified class will use this handler (unless there is a more specific handler registered) @param ClassPathName  The path name of the class this handler relates to. @param InHandler      The implementation of the handler to use
- L98 _public prototype_ `const IRigVMBlueprintAssetHandler* FindHandler(const UClass* InClass) const;` — Find a handler that applies to the specified class @param InClass        The class to find a handler for @return A valid asset handler, or nullptr if none exists for this class
- L104 _private prototype_ `FRigVMBlueprintAssetHandler();` — Private constructor - use singleton accessor (::Get)
- L107 _private member_ `TArray<FTopLevelAssetPath> ClassNames;` — Unsorted array of class names, one per-handler below
- L110 _private member_ `TArray<TUniquePtr<IRigVMBlueprintAssetHandler>> Handlers;` — Array of handlers that relate to the class names above

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMBlueprintCompilationManager.h` (Private)


#### struct `FRigVMBPCompileRequest`  
`struct FRigVMBPCompileRequest`  
_L23-36_
- L25 _public prototype_ `explicit FRigVMBPCompileRequest(UBlueprint* InBPToCompile, EBlueprintCompileOptions InCompileOptions, FCompilerResultsLog* InClientResultsLog);`
- L28 _public member_ `TObjectPtr<UBlueprint> BPToCompile;` — BP that needs to be compiled:
- L31 _public member_ `EBlueprintCompileOptions CompileOptions;` — Legacy options for blueprint compilation:
- L35 _public member_ `FCompilerResultsLog* ClientResultsLog;` — Clients can give us a results log if they want to parse or display it themselves, otherwise we will use a transient one:

#### struct `FRigVMBlueprintCompilationManager`  
`struct FRigVMBlueprintCompilationManager`  
_L38-100_
- L40 _public prototype_ `static void Initialize();`
- L41 _public prototype_ `static void Shutdown();`
- L50 _public prototype_ `static void FlushCompilationQueue(FUObjectSerializeContext* InLoadContext);` — Compiles all blueprints that have been placed in the compilation queue. ObjLoaded is a list of objects that need to be PostLoaded by the linker, when changing CDOs we will replace objects in this list. It is not a list of objects the compilation manager has loaded. The compilation manager will not load data while processing the compilation queue)
- L55 _public prototype_ `static void FlushCompilationQueueAndReinstance();` — Flushes the compilation queue and finishes reinstancing
- L62 _public prototype_ `static void CompileSynchronously(const FRigVMBPCompileRequest& Request);` — Immediately compiles the blueprint, no expectation that related blueprints be subsequently compiled. It will be significantly more efficient to queue blueprints and then flush the compilation queue if there are several blueprints that require compilation (e.g. typical case on PIE):
- L67 _public prototype_ `static void NotifyBlueprintLoaded(UBlueprint* BPLoaded);` — Adds a newly loaded blueprint to the compilation queue
- L72 _public prototype_ `static void QueueForCompilation(UBlueprint* BP);` — Adds a blueprint to the compilation queue - useful for batch compilation
- L75 _public prototype_ `static bool IsGeneratedClassLayoutReady();` — Returns true when UBlueprint::GeneratedClass members are up to date
- L82 _public prototype_ `static bool GetDefaultValue(const UClass* ForClass, const FProperty* Property, FString& OutDefaultValueAsString);` — Returns the Default Value associated with ForClass::Property, if ForClass is currently being compiled this function can look at the old version of the CDO and read the default value from there
- L89 _public prototype_ `static void ReparentHierarchies(const TMap<UClass*, UClass*>& OldClassToNewClass);` — Safely reparents all child classes of every Key in OldClassToNewClass to the class in the corresponding Value. Typically this means every child type will be reinstanced - although reinstancing could be avoided when layouts match.
- L97 _public prototype_ `static void RegisterCompilerExtension(TSubclassOf<UBlueprint> BlueprintType, URigVMBlueprintCompilerExtension* Extension);` — Registers a blueprint compiler extension - anytime a blueprint of the provided type is compiled the extension will be activated. Note that because editor initialization may require blueprint compilation there may be blueprints compiled before the extension is registed unless special care has been taken.
- L99 _private prototype_ `FRigVMBlueprintCompilationManager();`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMBlueprintCompilerExtension.h` (Private)


#### struct `FRigVMBlueprintCompiledData`  
`struct FRigVMBlueprintCompiledData`  
_L19-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TArray<TObjectPtr<UEdGraph>> IntermediateGraphs;` — `UPROPERTY()`

#### class `URigVMBlueprintCompilerExtension`  
`class URigVMBlueprintCompilerExtension : public UObject`  
_L28-45_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L33 _public prototype_ `URigVMBlueprintCompilerExtension(const FObjectInitializer& ObjectInitializer);`
- L36 _public prototype_ `void BlueprintCompiled(const FKismetCompilerContext& CompilationContext, const FRigVMBlueprintCompiledData& Data);`
- L43 _protected function_ `virtual void ProcessBlueprintCompiled(const FKismetCompilerContext& CompilationContext, const FRigVMBlueprintCompiledData& Data)` — Override this if you're interested in running logic after class layout has been generated, but before bytecode and member variables have been

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMFiBSearchInstance.h` (Private)


#### class `FFindInBlueprintExpressionEvaluator`  
`class FFindInBlueprintExpressionEvaluator : public FTextFilterExpressionEvaluator`  
_L26-64_
- inherits: `FTextFilterExpressionEvaluator`
- desc: Evaluates the expression the user submitted to be searched for
- L30 _public function_ `FFindInBlueprintExpressionEvaluator(const ETextFilterExpressionEvaluatorMode InMode, FRigVMFiBSearchInstance* InSearchInstance) : FTextFilterExpressionEvaluator(InMode) , SearchInstance(InSearchInstance)` — Construction and assignment
- L38 _public function_ `void SetDefaultFunctionHandler(FTokenDefaultFunctionHandler InFunctionHandler)` — Sets the default function handler, which supports generic functions which are categories or other object based on FRigVMImaginaryFiBData
- L45 _protected prototype_ `virtual void ConstructExpressionParser() override final;` — FTextFilterExpressionEvaluator Interface
- L46 _protected prototype_ `virtual bool EvaluateCompiledExpression(const ExpressionParser::CompileResultType& InCompiledResult, const ITextFilterExpressionContext& InContext, FText* OutErrorText) const override;`
- L50 _protected prototype_ `void MapBasicJumps();` — Helper function to make a mapping of all basic jump operations
- L53 _protected prototype_ `void MapOrBinaryJumps();` — Helper function to make a mapping of all "Or" binary jump operations
- L56 _protected prototype_ `void MapAndBinaryJumps();` — Helper function to make a mapping of all "And" binary jump operations
- L60 _protected member_ `FRigVMFiBSearchInstance* SearchInstance;` — Referenced SearchInstance that is powering this search
- L63 _protected member_ `FTokenDefaultFunctionHandler DefaultFunctionHandler;` — Fallback for all functions, Find-in-Blueprints filters into any sub-data using functions

#### class `FRigVMFiBSearchInstance`  
`class FRigVMFiBSearchInstance`  
_L67-155_
- desc: Used to manage searches through imaginary Blueprints
- L77 _public prototype_ `FRigVMSearchResult StartSearchQuery(const FString& InSearchString, FRigVMImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Starts a search query given a string and an imaginary Blueprint @param InSearchString				The string to search using @param InImaginaryBlueprintRoot		The imaginary Blueprint to search through @return								Search result shared pointer, can be used for display in the search results window
- L85 _public prototype_ `void MakeSearchQuery(const FString& InSearchString, FRigVMImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Starts a search query given a string and an imaginary Blueprint @param InSearchString				The string to search using @param InImaginaryBlueprintRoot		The imaginary Blueprint to search through
- L94 _public prototype_ `bool DoSearchQuery(const FString& InSearchString, bool bInComplete = true);` — Runs a search query on any pending imaginary data @param InSearchString		The string to search using @param bInComplete			TRUE if a complete search of all child items should also be done, this should be FALSE when you only want to compare the string against the immediate items and not their children @return						TRUE if the search was successful.
- L103 _public prototype_ `void BuildFunctionTargets(FRigVMImaginaryFiBDataSharedPtr InRootData, ERigVMSearchQueryFilter InSearchQueryFilter, TArray<FRigVMImaginaryFiBDataWeakPtr>& OutTargetPendingSearchables);` — Builds a list of imaginary items that can be targeted by a function @param InRootData						Item to find the child imaginary data that can have be sub-searched for the function @param InSearchQueryFilter				A filter to decide if the imaginary item is compatible with the function @param OutTargetPendingSearchables		List of pending imaginary items that will be sub-searched, this gets filled out by the function
- L112 _public prototype_ `void BuildFunctionTargetsByName(FRigVMImaginaryFiBDataSharedPtr InRootData, FString InTagName, TArray<FRigVMImaginaryFiBDataWeakPtr>& OutTargetPendingSearchables);` — Builds a list of imaginary items, using their names, that can be targeted by a function @param InRootData						Item to find the child imaginary data that can have be sub-searched for the function @param InTagName							The name of objects to find @param OutTargetPendingSearchables		List of pending imaginary items that will be sub-searched, this gets filled out by the function
- L121 _public prototype_ `bool OnFilterFunction(const FTextFilterString& A, ERigVMSearchQueryFilter InSearchQueryFilter);` — Callback when a function is called by the evaluator @param InParameterString		The parameter string to sub-search using @param InSearchQueryFilter	Effectively this is the function being called, the filter is used to determine if the current item can have the function called on it and whether it's sub items can have it called on them @return						TRUE if the function was successful at finding valid results
- L130 _public prototype_ `bool OnFilterDefaultFunction(const FTextFilterString& InFunctionName, const FTextFilterString& InFunctionParams);` — Callback when a default/generic function is called by the evaluator @param InFunctionName		The function name to call, will query for sub-objects with this name to do a sub-search on @param InFunctionParams		The parameter string to sub-search using @return						TRUE if the function was successful at finding valid results
- L133 _public prototype_ `void CreateFilteredResultsListFromTree(ERigVMSearchQueryFilter InSearchQueryFilter, TArray<FRigVMImaginaryFiBDataSharedPtr>& InOutValidSearchResults);` — Builds a list of search results in their imaginary data form, filtered by an object type
- L136 _public prototype_ `FRigVMSearchResult GetSearchResults(FRigVMImaginaryFiBDataSharedPtr InImaginaryBlueprintRoot);` — Helper function to return search results given an imaginary Blueprint root
- L139 _public member_ `FRigVMImaginaryFiBDataWeakPtr CurrentSearchable;` — Current item being searched in the Imaginary Blueprint. Must be declared as thread-safe because this is a shared object.
- L142 _public member_ `TArray< const FRigVMImaginaryFiBData* > MatchesSearchQuery;` — A going list of all imaginary items that match the search query
- L145 _public member_ `TMultiMap< const FRigVMImaginaryFiBData*, FRigVMComponentUniqueDisplay > MatchingSearchComponents;` — A mapping of items and their components that match the search query
- L148 _public member_ `TArray<FRigVMImaginaryFiBDataWeakPtr> PendingSearchables;` — A list of imaginary items that still need to be searched. Must be declared as thread-safe because it points to a shared object.
- L151 _public member_ `TArray< const FRigVMImaginaryFiBData* > LastFunctionResultMatchesSearchQuery;` — When a function returns on an item, this is the list of items that matched the sub-search query
- L154 _public member_ `TMultiMap< const FRigVMImaginaryFiBData*, FRigVMComponentUniqueDisplay > LastFunctionMatchingSearchComponents;` — When a function returns on an item, this is the mapping of imaginary items to components that matched the sub-search query

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTokenDefaultFunctionHandler, const FTextFilterString&, const FTextFilterString&);`
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTokenDefaultFunctionHandler, const FTextFilterString&, const FTextFilterString&);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMFindInBlueprintManager.h` (Private)


#### struct `FRigVMFindInBlueprintSearchTags`  
`struct FRigVMFindInBlueprintSearchTags`  
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

#### enum `ERigVMFiBVersion`  
`enum ERigVMFiBVersion : int`  
_L156-168_
- reflection: `UENUM()`
- desc: FiB data versioning
- L158 _public enumerator_ `RIGVM_FIB_VER_NONE = -1` — Unknown version (not set)
- L160 _public enumerator_ `RIGVM_FIB_VER_BASE = 0` — All Blueprints prior to versioning will automatically be assumed to be at 0 if they have FiB data collected
- L161 _public enumerator_ `RIGVM_FIB_VER_VARIABLE_REFERENCE` — Variable references (FMemberReference) is collected in FiB
- L162 _public enumerator_ `RIGVM_FIB_VER_INTERFACE_GRAPHS` — Implemented Interface Graphs is collected in FiB
- L163 _public enumerator_ `RIGVM_FIB_VER_FUNC_CALL_SITES` — Hidden target pins and function origin class are collected in FiB for improved function call site searchability
- L166 _public enumerator_ `RIGVM_FIB_VER_PLUS_ONE` — -----<new versions can be added before this line>-------------------------------------------------
- L167 _public enumerator_ `RIGVM_FIB_VER_LATEST = RIGVM_FIB_VER_PLUS_ONE - 1` — Always the last version, we want Blueprints to be at latest

#### struct `FRigVMSearchDataVersionInfo`  
`struct FRigVMSearchDataVersionInfo`  
_L173-183_
- desc: Consolidated version info for a Blueprint search data entry
- L176 _public member_ `int32 FiBDataVersion = ERigVMFiBVersion::RIGVM_FIB_VER_NONE;` — FiB asset registry tag data version
- L179 _public member_ `int32 EditorObjectVersion = -1;` — Editor object version used to serialize values in the JSON string lookup table
- L182 _public member_ `static FRigVMSearchDataVersionInfo Current;` — Current version info

#### enum `ERigVMSearchDataStateFlags`  
`enum class ERigVMSearchDataStateFlags : uint8`  
_L186-193_
- desc: State flags for search database entries
- L188 _public enumerator_ `None = 0`
- L190 _public enumerator_ `IsIndexed = 1 << 0` — Set when this search database entry has been fully indexed, which is completed asynchronously
- L192 _public enumerator_ `WasRemoved = 1 << 1` — Cached to determine if the Blueprint is seen as no longer valid, allows it to be cleared out next save to disk

#### struct `FRigVMSearchData`  
`struct FRigVMSearchData`  
_L198-261_
- desc: Tracks data relevant to a Blueprint for searches
- L201 _public member_ `TWeakObjectPtr<UBlueprint> Blueprint;` — The Blueprint this search data points to, if available
- L204 _public member_ `FSoftObjectPath AssetPath;` — The full asset path this search data is associated with of the form /Game/Path/To/Package.Package
- L207 _public member_ `FString Value;` — Encoded search data block for the Blueprint, this will not always be set if it's already been parsed
- L210 _public member_ `FName AssetKeyForValue;` — Key to use to look up the encoded search data from an FAssetData, if this is set Value will probably be empty
- L213 _public member_ `FString ParentClass;` — Parent Class
- L216 _public member_ `TArray<FString> Interfaces;` — Interfaces implemented by the Blueprint
- L219 _public member_ `FRigVMImaginaryFiBDataSharedPtr ImaginaryBlueprint;` — Cached ImaginaryBlueprint data for the searchable content, prevents having to re-parse every search
- L222 _public member_ `FRigVMSearchDataVersionInfo VersionInfo;` — Data versioning
- L225 _public member_ `ERigVMSearchDataStateFlags StateFlags;` — State flags (see enum)
- L227 _public function_ `FRigVMSearchData() : Blueprint(nullptr) , StateFlags(ERigVMSearchDataStateFlags::None)`
- L234 _public function_ `bool IsValid() const` — True if this represents a valid asset
- L240 _public function_ `bool HasEncodedValue() const` — True if this has an encoded value that has yet to be parsed
- L246 _public function_ `void ClearEncodedValue()` — Clear the encoded value after parsing or getting new data
- L252 _public function_ `bool IsIndexingCompleted() const`
- L257 _public function_ `bool IsMarkedForDeletion() const`

#### enum `ERigVMSearchQueryFilter`  
`enum ERigVMSearchQueryFilter`  
_L264-277_
- desc: Filters are used by functions for searching to decide whether items can call certain functions or match the requirements of a function
- L266 _public enumerator_ `RigVMBlueprintFilter = 0`
- L267 _public enumerator_ `RigVMGraphsFilter`
- L268 _public enumerator_ `RigVMUberGraphsFilter`
- L269 _public enumerator_ `RigVMFunctionsFilter`
- L270 _public enumerator_ `RigVMMacrosFilter`
- L271 _public enumerator_ `RigVMNodesFilter`
- L272 _public enumerator_ `RigVMPinsFilter`
- L273 _public enumerator_ `RigVMPropertiesFilter`
- L274 _public enumerator_ `RigVMVariablesFilter`
- L275 _public enumerator_ `RigVMComponentsFilter`
- L276 _public enumerator_ `RigVMAllFilter` — Will search all items, when used inside of another filter it will search all sub-items of that filter

#### struct `FRigVMFiBMD`  
`struct FRigVMFiBMD`  
_L291-298_
- L293 _public member_ `static const FString FiBSearchableMD;`
- L294 _public member_ `static const FString FiBSearchableShallowMD;`
- L295 _public member_ `static const FString FiBSearchableExplicitMD;`
- L296 _public member_ `static const FString FiBSearchableHiddenExplicitMD;`
- L297 _public member_ `static const FString FiBSearchableFormatVersionMD;`

#### enum `ERigVMFiBCacheOpType`  
`enum class ERigVMFiBCacheOpType`  
_L301-305_
- desc: Which assets to index for caching
- L303 _public enumerator_ `CachePendingAssets`
- L304 _public enumerator_ `CacheUnindexedAssets`

#### enum `ERigVMFiBCacheOpFlags`  
`enum class ERigVMFiBCacheOpFlags`  
_L308-333_
- desc: Flags to control the UX while caching
- L310 _public enumerator_ `None = 0`
- L312 _public enumerator_ `ShowProgress = 1 << 0` — Whether to show progress
- L314 _public enumerator_ `HideNotifications = 1 << 1` — Whether to hide toast popups
- L316 _public enumerator_ `AllowUserCancel = 1 << 2` — Whether to allow users to cancel
- L318 _public enumerator_ `CheckOutAndSave = 1 << 3` — Set if the user wants to check out and save (applies to unindexed caching only)
- L320 _public enumerator_ `HideProgressBars = 1 << 4` — Whether to hide progress bar widgets
- L322 _public enumerator_ `AllowUserCloseProgress = 1 << 5` — Whether to allow users to hide/close progress
- L324 _public enumerator_ `IsCachingDiscoveredAssets = 1 << 6` — Set if we are caching assets from the discovery stage
- L326 _public enumerator_ `KeepProgressVisibleOnCompletion = 1 << 7` — Whether to keep progress visible on completion
- L328 _public enumerator_ `ExecuteOnMainThread = 1 << 8` — Index deferred assets on the main thread only (used for debugging)
- L330 _public enumerator_ `ExecuteOnSingleThread = 1 << 9` — Don't index multiple assets in parallel (used to assist with profiling)
- L332 _public enumerator_ `ExecuteGatherPhaseOnly = 1 << 10` — Only execute the gather phase (used to help minimize memory usage on editor/tab open)

#### struct `FRigVMFindInBlueprintCachingOptions`  
`struct FRigVMFindInBlueprintCachingOptions`  
_L338-351_
- desc: Options to configure the bulk caching task
- L341 _public member_ `ERigVMFiBCacheOpType OpType = ERigVMFiBCacheOpType::CachePendingAssets;` — Type of caching operation
- L344 _public member_ `ERigVMFiBCacheOpFlags OpFlags = ERigVMFiBCacheOpFlags::None;` — Initial set of control flags
- L347 _public member_ `FSimpleDelegate OnFinished;` — Callback for when caching is finished
- L350 _public member_ `ERigVMFiBVersion MinimiumVersionRequirement = ERigVMFiBVersion::RIGVM_FIB_VER_LATEST;` — Minimum version requirement for caching, any Blueprints below this version will be re-indexed

#### enum `ERigVMAddOrUpdateBlueprintSearchMetadataFlags`  
`enum class ERigVMAddOrUpdateBlueprintSearchMetadataFlags`  
_L354-361_
- desc: Options for FRigVMFindInBlueprintSearchManager::AddOrUpdateBlueprintSearchMetadata()
- L356 _public enumerator_ `None = 0`
- L358 _public enumerator_ `ForceRecache = 1 << 0` — Forces the Blueprint to be recache'd, regardless of what data it believes exists
- L360 _public enumerator_ `ClearCachedValue = 1 << 1` — Clear any cached data value for this Blueprint

#### class `FRigVMFindInBlueprintsResult`  
`class FRigVMFindInBlueprintsResult : public TSharedFromThis< FRigVMFindInBlueprintsResult >`  
_L369-424_
- inherits: `TSharedFromThis<FRigVMFindInBlueprintsResult>`
- desc: Item that matched the search results
- L372 _public prototype_ `FRigVMFindInBlueprintsResult() = default;`
- L373 _public prototype_ `virtual ~FRigVMFindInBlueprintsResult() = default;`
- L376 _public prototype_ `explicit FRigVMFindInBlueprintsResult(const FText& InDisplayText);` — Create a root
- L379 _public prototype_ `virtual FReply OnClick();` — Called when user clicks on the search item
- L382 _public prototype_ `virtual FText GetCategory() const;` — Get Category for this search result
- L385 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L388 _public function_ `virtual void FinalizeSearchData()` — Finalizes any content for the search data that was unsafe to do on a separate thread
- L391 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L394 _public prototype_ `UBlueprint* GetParentBlueprint() const;` — gets the blueprint housing all these search results
- L404 _public function_ `virtual void ParseSearchInfo(FText InKey, FText InValue)` — Parses search info for specific data important for displaying the search result in an easy to understand format @param	InTokens		The search tokens to check results against @param	InKey			This is the tag for the data, describing what it is so special handling can occur if needed @param	InValue			Compared against search query to see if it passes the filter, sometimes data is rejected because it is deemed unsearchable @param	InParent		The parent search result
- L407 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const;` — Returns the Object represented by this search information give the Blueprint it can be found in
- L410 _public prototype_ `FText GetDisplayString() const;` — Returns the display string for the row
- L414 _public member_ `TArray< TSharedPtr<FRigVMFindInBlueprintsResult> > Children;` — Any children listed under this category
- L417 _public member_ `TWeakPtr<FRigVMFindInBlueprintsResult> Parent;` — If it exists it is the blueprint
- L420 _public member_ `FText DisplayText;` — The display text for this item
- L423 _public member_ `FString CommentText;` — Display text for comment information

#### struct `FRigVMStreamSearchOptions`  
`struct FRigVMStreamSearchOptions`  
_L431-445_
- L434 _public member_ `enum ERigVMSearchQueryFilter ImaginaryDataFilter;` — Filter to limit the FilteredImaginaryResults to
- L437 _public member_ `ERigVMFiBVersion MinimiumVersionRequirement;` — When searching, any Blueprint below this version will be considered out-of-date
- L440 _public function_ `FRigVMStreamSearchOptions() :ImaginaryDataFilter(ERigVMSearchQueryFilter::RigVMAllFilter) ,MinimiumVersionRequirement(ERigVMFiBVersion::RIGVM_FIB_VER_LATEST)` — Default constructor.

#### class `FRigVMStreamSearch`  
`class FRigVMStreamSearch : public FRunnable`  
_L450-525_
- inherits: `FRunnable`
- desc: Async task for searching Blueprints
- L454 _public prototype_ `FRigVMStreamSearch(const FString& InSearchValue, const FRigVMStreamSearchOptions& InSearchOptions = FRigVMStreamSearchOptions());` — Constructor
- L457 _public prototype_ `virtual bool Init() override;` — Begin FRunnable Interface
- L459 _public prototype_ `virtual uint32 Run() override;`
- L461 _public prototype_ `virtual void Stop() override;`
- L463 _public prototype_ `virtual void Exit() override;`
- L467 _public prototype_ `void EnsureCompletion();` — Brings the thread to a safe stop before continuing.
- L470 _public prototype_ `bool IsComplete() const;` — Returns TRUE if the thread is done with it's work.
- L473 _public prototype_ `bool WasStopped() const;` — Returns TRUE if Stop() was called while work is still pending.
- L480 _public prototype_ `void GetFilteredItems(TArray<TSharedPtr<class FRigVMFindInBlueprintsResult>>& OutItemsFound);` — Appends the items filtered through the search filter to the passed array @param OutItemsFound		All the items found since last queried
- L483 _public prototype_ `float GetPercentComplete() const;` — Helper function to query the percent complete this search is
- L486 _public function_ `int32 GetOutOfDateCount() const` — Returns the Out-of-Date Blueprint count
- L492 _public prototype_ `void GetFilteredImaginaryResults(TArray<FRigVMImaginaryFiBDataSharedPtr>& OutFilteredImaginaryResults);` — Returns the FilteredImaginaryResults from the search query, these results have been filtered by the ImaginaryDataFilter.
- L496 _public member_ `TUniquePtr<FRunnableThread> Thread;` — Thread to run the cleanup FRunnable on
- L499 _public member_ `TArray<TSharedPtr<class FRigVMFindInBlueprintsResult>> ItemsFound;` — A list of items found, cleared whenever the main thread pulls them to display to screen
- L502 _public member_ `FString SearchValue;` — The search value to filter results by
- L505 _public member_ `FRigVMStreamSearchOptions SearchOptions;` — Options for setting up the search
- L508 _public member_ `FCriticalSection SearchCriticalSection;` — Prevents searching while other threads are pulling search results
- L511 _public member_ `TArray<FRigVMImaginaryFiBDataSharedPtr> FilteredImaginaryResults;` — Filtered (ImaginaryDataFilter) list of imaginary data results that met the search requirements. Must be declared as thread-safe since imaginary data is a shared resource.
- L514 _public member_ `int32 BlueprintCountBelowVersion;` — A going count of all Blueprints below the MinimiumVersionRequirement
- L517 _public member_ `bool bThreadCompleted;` — Whether the thread has finished running
- L521 _private member_ `int32 SearchId;` — Unique identifier for this search (used with benchmarking)
- L524 _private member_ `FThreadSafeCounter StopTaskCounter;` — > 0 if we've been asked to abort work in progress at the next opportunity

#### class `FRigVMFindInBlueprintSearchManager`  
`class FRigVMFindInBlueprintSearchManager : public FTickableEditorObject`  
_L531-914_
- inherits: `FTickableEditorObject`
- desc: Singleton manager for handling all Blueprint searches, helps to manage the going progress of Blueprints, and is thread-safe.
- L534 _public member_ `static FRigVMFindInBlueprintSearchManager* Instance;`
- L535 _public prototype_ `static FRigVMFindInBlueprintSearchManager& Get();`
- L537 _public prototype_ `FRigVMFindInBlueprintSearchManager();`
- L538 _public prototype_ `~FRigVMFindInBlueprintSearchManager();`
- L541 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L542 _public prototype_ `virtual bool IsTickable() const override;`
- L543 _public prototype_ `virtual TStatId GetStatId() const override;`
- L552 _public prototype_ `void ApplySearchDataToDatabase(FRigVMSearchData InSearchData, bool bAllowNewEntry = false);` — Applies the given search data to a matching entry in the database. Optionally adds a new entry if a match is not found. @param InSearchData		Search data to be applied @param bAllowNewEntry	Whether to allow a new entry to be added if a match is not found
- L560 _public prototype_ `FRigVMSearchData GetSearchDataForAssetPath(const FSoftObjectPath& InAssetPath);` — Given an asset path, locate and return a copy of its matching search data in the index cache. @param InAssetPath				Asset path (search index key). @return							Matching search data from the index cache. Will return invalid (empty) search data if a matching entry was not found.
- L569 _public prototype_ `void AddOrUpdateBlueprintSearchMetadata(UBlueprint* InBlueprint, ERigVMAddOrUpdateBlueprintSearchMetadataFlags InFlags = ERigVMAddOrUpdateBlueprintSearchMetadataFlags::None, ERigVMFiBVersion InVersion = ERigVMFiBVersion::RIGVM_FIB_VER_NONE);` — Gathers the Blueprint's search metadata and adds or updates it in the cache @param InBlueprint		Blueprint to cache the searchable data for @param InFlags			Flags to assist with controlling this function's behavior @param InVersion			Allows the caller to override the format version to use for caching
- L576 _public prototype_ `void BeginSearchQuery(const class FRigVMStreamSearch* InSearchOriginator);` — Starts a search query, the FiB manager handles where the thread is at in the search query at all times so that post-save of the cache to disk it can correct the index @param InSearchOriginator		Pointer to the thread object that the query originates from
- L585 _public prototype_ `bool ContinueSearchQuery(const class FRigVMStreamSearch* InSearchOriginator, FRigVMSearchData& OutSearchData);` — Continues a search query, returning a single piece of search data @param InSearchOriginator		Pointer to the thread object that the query originates from @param OutSearchData				Result of the search, if there is any Blueprint search data still available to query @return							TRUE if the search was successful, FALSE if the search is complete
- L593 _public prototype_ `void EnsureSearchQueryEnds(const class FRigVMStreamSearch* InSearchOriginator);` — This function ensures that the passed in search query ends in a safe manner. The search will no longer be valid to this manager, though it does not destroy any objects. Use this whenever the search is finished or canceled. @param InSearchOriginator	Identifying search stream to be stopped
- L601 _public prototype_ `float GetPercentComplete(const class FRigVMStreamSearch* InSearchOriginator) const;` — Query how far along a search thread is @param OutSearchData				Result of the search, if there is any Blueprint search data still available to query @return							Percent along the search thread is
- L610 _public prototype_ `FRigVMSearchData QuerySingleBlueprint(UBlueprint* InBlueprint, bool bInRebuildSearchData);` — Query for a single, specific Blueprint's search data. @param InBlueprint				The Blueprint to search for @param bInRebuildSearchData		When TRUE the search data will be freshly collected @return							The search data, or invalid (empty) search data if not found
- L613 _public prototype_ `bool ProcessEncodedValueForUnloadedBlueprint(FRigVMSearchData& SearchData);` — Processes the encoded string value in the SearchData into the intermediate format, return true if string and version were valid
- L616 _public prototype_ `int32 GetNumberUnindexedAssets() const;` — Returns the number of unindexed Blueprints, either due to not having been indexed before, or AR data being out-of-date
- L619 _public prototype_ `int32 GetNumberUncachedAssets() const;` — Returns the number of uncached assets during an active indexing operation
- L627 _public prototype_ `void CacheAllAssets(TWeakPtr< class SRigVMFindInBlueprints > InSourceWidget, const FRigVMFindInBlueprintCachingOptions& InCachingOptions);` — Starts a task to cache Blueprints at a rate of 1 per tick @param InSourceWidget				The source RigVMFindInBlueprints widget, this widget will be informed when caching is complete @param InCachingOptions				Options to configure the caching task
- L632 _public prototype_ `void ExportOutdatedAssetList();` — Exports a list of all unindexed assets to Saved/RigVMFindInBlueprints_OutdatedAssetList.txt
- L640 _public prototype_ `void OnCacheAllUnindexedAssets(bool bInSourceControlActive, bool bInCheckoutAndSave);` — Starts the actual caching process @param bInSourceControlActive		TRUE if source control is active @param bInCheckoutAndSave			TRUE if the system should checkout and save all assets that need to be reindexed
- L643 _public prototype_ `void CancelCacheAll(SRigVMFindInBlueprints* InFindInBlueprintWidget);` — Stops the caching process where it currently is at, the rest can be continued later
- L646 _public prototype_ `int32 GetCurrentCacheIndex() const;` — Returns the current index in the caching
- L649 _public prototype_ `FSoftObjectPath GetCurrentCacheBlueprintPath() const;` — Returns the path of the current Blueprint being cached
- L652 _public prototype_ `float GetCacheProgress() const;` — Returns the progress complete on the caching
- L655 _public function_ `TSet<FSoftObjectPath> GetFailedToCachePathList() const` — Returns the list of Blueprint paths that failed to cache
- L658 _public function_ `int32 GetFailedToCacheCount() const` — Returns the number of Blueprints that failed to cache
- L661 _public function_ `bool HasCachingFailed() const` — Returns TRUE if caching failed
- L664 _public prototype_ `void StartedCachingBlueprints(ERigVMFiBCacheOpType InCacheOpType, ERigVMFiBCacheOpFlags InCacheOpFlags);` — Callback to note that Blueprint caching is started
- L671 _public prototype_ `void FinishedCachingBlueprints(ERigVMFiBCacheOpType InCacheOpType, ERigVMFiBCacheOpFlags InCacheOpFlags, int32 InNumberCached, TSet<FSoftObjectPath>& InFailedToCacheList);` — Callback to note that Blueprint caching is complete @param InNumberCached		The number of Blueprints cached, to be chopped off the existing array so the rest (if any) can be finished later
- L674 _public prototype_ `bool IsCacheInProgress() const;` — Returns TRUE if Blueprints are being cached.
- L677 _public prototype_ `bool IsUnindexedCacheInProgress() const;` — Returns TRUE if unindexed Blueprints are being cached (since this can block the UI)
- L680 _public prototype_ `bool IsAssetDiscoveryInProgress() const;` — Returns TRUE if we're still inside the initial asset discovery and registration stage
- L683 _public prototype_ `bool IsAsyncSearchQueryInProgress() const;` — Returns TRUE if there are one or more active asynchronous search queries
- L686 _public function_ `TWeakPtr<SRigVMFindInBlueprints> GetSourceCachingWidget() const` — Returns a weak reference to the widget that initiated the current caching operation
- L688 _public function_ `void EnableGatheringData(bool bInEnableGatheringData)`
- L690 _public function_ `bool IsGatheringDataEnabled() const`
- L693 _public function_ `bool ShouldEnableDeveloperMenuTools() const` — If TRUE, the developer menu tool commands will be shown in the 'Developer' section of the Blueprint Editor's menu bar
- L696 _public function_ `bool ShouldEnableSearchResultTemplates() const` — If TRUE, search result meta will be gathered once and stored in a template. Avoids doing this work redundantly at search time.
- L699 _public prototype_ `TSharedPtr<SRigVMFindInBlueprints> GetGlobalFindResults();` — Find or create the global find results widget
- L702 _public prototype_ `void EnableGlobalFindResults(bool bEnable);` — Enable or disable the global find results tab feature
- L705 _public prototype_ `void CloseOrphanedGlobalFindResultsTabs(TSharedPtr<class FTabManager> TabManager);` — Close any orphaned global find results tabs for a particular tab manager
- L708 _public function_ `bool IsGlobalFindResultsOpen() const` — Returns true if a global find results tab is currently open
- L710 _public prototype_ `void GlobalFindResultsClosed(const TSharedRef<SRigVMFindInBlueprints>& FindResults);`
- L713 _public prototype_ `void DumpCache(FArchive& Ar);` — Dumps the full index cache to the given stream (for debugging purposes)
- L716 _public prototype_ `void DoRandomIndexCacheRebuild();` — Randomly initiates a partial rebuild of the index cache (for debugging purposes)
- L720 _public prototype_ `static FText ConvertHexStringToFText(FString InHexString);` — Converts a string of hex characters, previously converted by ConvertFTextToHexString, to an FText.
- L723 _public prototype_ `static FString ConvertFTextToHexString(FText InValue);` — Serializes an FText to memory and converts the memory into a string of hex characters
- L726 _public prototype_ `static TSharedPtr< class FJsonObject > ConvertJsonStringToObject(FRigVMSearchDataVersionInfo InVersionInfo, const FString& InJsonString, TMap<int32, FText>& OutFTextLookupTable);` — Given a fully constructed Find-in-Blueprint FString of searchable data, will parse and construct a JsonObject
- L729 _public prototype_ `static FString GenerateSearchIndexForDebugging(UBlueprint* InBlueprint);` — Generates a human-readable search index for the given Blueprint (for debugging purposes)
- L733 _private prototype_ `void Initialize();` — Initializes the FiB manager
- L736 _private prototype_ `void PauseFindInBlueprintSearch();` — Callback hook during pre-garbage collection, pauses all processing searches so that the GC can do it's job
- L739 _private prototype_ `void UnpauseFindInBlueprintSearch();` — Callback hook during post-garbage collection, saves the cache to disk and unpauses all processing searches
- L742 _private prototype_ `void OnAssetAdded(const struct FAssetData& InAssetData);` — Callback hook from the Asset Registry when an asset is added
- L745 _private prototype_ `void OnAssetRemoved(const struct FAssetData& InAssetData);` — Callback hook from the Asset Registry, marks the asset for deletion from the cache
- L748 _private prototype_ `void OnAssetRenamed(const struct FAssetData& InAssetData, const FString& InOldName);` — Callback hook from the Asset Registry, marks the asset for deletion from the cache
- L751 _private prototype_ `void OnAssetRegistryFilesLoaded();` — Callback hook from the Asset Registry, signals that the initial asset discovery stage has been completed
- L754 _private prototype_ `void OnAssetLoaded(class UObject* InAsset);` — Callback hook from the Asset Registry when an asset is loaded
- L757 _private prototype_ `void OnBlueprintUnloaded(class UBlueprint* InBlueprint);` — Callback from Kismet when a Blueprint is unloaded
- L760 _private prototype_ `void OnReloadComplete(EReloadCompleteReason Reason);` — Callback hook from the Reload manager that indicates that a module has been reloaded
- L763 _private prototype_ `FRigVMSearchData GetSearchDataForIndex(int32 CacheIndex);` — Returns a copy of the search data that's cached at the given index. Will return invalid (empty) search data if the index is out of range
- L766 _private prototype_ `void CleanCache();` — Cleans the cache of any excess data from Blueprints that have been moved, renamed, or deleted. Occurs during post-garbage collection
- L769 _private prototype_ `void BuildCache();` — Builds the cache from all available Blueprint assets that the asset registry has discovered at the time of this function. Occurs on startup
- L777 _private prototype_ `int32 AddSearchDataToDatabase(FRigVMSearchData InSearchData);` — Helper to properly add a Blueprint's SearchData to the database @param InSearchData		Data to add to the database @return					Index into the SearchArray for looking up the added item
- L780 _private prototype_ `void RemoveBlueprintByPath(const FSoftObjectPath& InPath);` — Removes a Blueprint from being managed by the FiB system by passing in the UBlueprint's path
- L783 _private prototype_ `void AddUnloadedBlueprintSearchMetadata(const FAssetData& InAssetData);` — Adds a new search database entry for unloaded asset data
- L786 _private prototype_ `void ExtractUnloadedFiBData(const FAssetData& InAssetData, FString* InFiBData, FName InKeyForFiBData, ERigVMFiBVersion InFiBDataVersion);` — Begins the process of extracting FiB data from an unloaded asset
- L789 _private prototype_ `FText GetGlobalFindResultsTabLabel(int32 TabIdx);` — Determines the global find results tab label
- L792 _private prototype_ `TSharedRef<SDockTab> SpawnGlobalFindResultsTab(const FSpawnTabArgs& SpawnTabArgs, int32 TabIdx);` — Handler for a request to spawn a new global find results tab
- L795 _private prototype_ `TSharedPtr<SRigVMFindInBlueprints> OpenGlobalFindResultsTab();` — Creates and opens a new global find results tab
- L815 _protected typedef_ `typedef TSharedPtr<FActiveSearchQuery, ESPMode::ThreadSafe> FActiveSearchQueryPtr;`
- L818 _protected prototype_ `FActiveSearchQueryPtr FindSearchQuery(const class FRigVMStreamSearch* InSearchOriginator) const;` — Thread-safe access to the active search query that's mapped to the given stream search
- L821 _protected prototype_ `FRigVMSearchData GetNextSearchDataForQuery(const FRigVMStreamSearch* InSearchOriginator, FActiveSearchQueryPtr InSearchQueryPtr, bool bCheckDeferredList);` — Returns the next pending search data for the given query and advances the index to the next entry
- L824 _protected prototype_ `void BlockSearchQueryIfPaused();` — If searches are paused, blocks the calling thread until searching is resumed
- L828 _private member_ `TMap<FSoftObjectPath, int32> SearchMap;` — Maps the Blueprint paths to their index in the SearchArray
- L831 _private member_ `TArray<FRigVMSearchData> SearchArray;` — Stores the Blueprint search data and is used to iterate over in small chunks
- L834 _private member_ `FThreadSafeCounter ActiveSearchCounter;` — Counter of active searches
- L840 _private member_ `mutable FCriticalSection SafeQueryModifyCriticalSection;` — Critical section to safely add, remove, and find data in ActiveSearchQueries
- L843 _private member_ `FCriticalSection PauseThreadsCriticalSection;` — Critical section to lock threads during the pausing procedure
- L846 _private member_ `FCriticalSection SafeModifyCacheCriticalSection;` — Critical section to safely modify cached data
- L849 _private member_ `class FAssetRegistryModule* AssetRegistryModule;` — Because we are unable to query for the module on another thread, cache it for use later
- L852 _private member_ `TWeakPtr<SRigVMFindInBlueprints> SourceCachingWidget;` — RigVMFindInBlueprints widget that started the cache process
- L855 _private member_ `TSet<FSoftObjectPath> PendingAssets;` — Asset paths that were discovered, loaded or modified and now require indexing (or re-indexing)
- L858 _private member_ `TSet<FSoftObjectPath> UnindexedAssets;` — Asset paths that have not been cached for searching due to lack of FiB data, this means that they are either older Blueprints, or the DDC cannot find the data
- L861 _private member_ `TSet<FSoftObjectPath> FailedToCachePaths;` — List of paths for Blueprints that failed to cache
- L864 _private member_ `TSet<FSoftObjectPath> AssetsToIndexOnFirstSearch;` — List of paths that require a full index pass during the first global search
- L867 _private member_ `TUniquePtr<class FCacheAllBlueprintsTickableObject> CachingObject;` — Tickable object that does the caching of uncached Blueprints at a rate of once per tick
- L870 _private member_ `ERigVMFiBCacheOpType CurrentCacheOpType;` — Stores the type of caching operation that's currently in progress
- L873 _private member_ `TMap<FTopLevelAssetPath, TWeakObjectPtr<const UClass>> CachedAssetClasses;` — Mapping between a class name and its UClass instance - used for faster look up in FRigVMFindInBlueprintSearchManager::OnAssetAdded
- L876 _private member_ `FName GlobalFindResultsTabIDs[MAX_GLOBAL_FIND_RESULTS];` — The tab identifier/instance name for global find results
- L879 _private member_ `TArray<TWeakPtr<SRigVMFindInBlueprints>> GlobalFindResults;` — Array of open global find results widgets
- L882 _private member_ `TSharedPtr<class FWorkspaceItem> GlobalFindResultsMenuItem;` — Global Find Results workspace menu item
- L885 _private member_ `int32 AsyncTaskBatchSize;` — Size of a single async indexing task batch; zero or negative means that a caching operation will consist of a single batch
- L888 _private member_ `TAtomic<bool> bIsPausing;` — TRUE when the the FiB manager wants to pause all searches, helps manage the pausing procedure
- L891 _private member_ `TAtomic<bool> bHasFirstSearchOccurred;` — Currently used to delay the full indexing pass until the first search in order to control memory usage
- L894 _private member_ `bool bEnableGatheringData;` — Tells if gathering data is currently allowed
- L897 _private member_ `bool bDisableDeferredIndexing;` — If true, search metadata will be regenerated for loaded assets on the main thread immediately at discovery or load time. By default, this work is deferred to avoid hitching.
- L901 _private member_ `bool bDisableThreadedIndexing;` — If true, and if deferred indexing is not disabled, search metadata will be regenerated for loaded assets on the main thread at a rate of one asset per tick. Additional indexing work will be deferred to the search thread. By default, all indexing work is deferred to a background thread and both loaded and unloaded assets are fully indexed asynchronously.
- L904 _private member_ `bool bEnableCSVStatsProfiling;` — Whether CSV profiling has been enabled (default=false)
- L907 _private member_ `bool bEnableDeveloperMenuTools;` — Whether to enable Blueprint editor developer menu tools
- L910 _private member_ `bool bDisableSearchResultTemplates;` — Disable the use of search result templates. Setting this to TRUE will slightly decrease overall memory usage, but will also increase global search times
- L913 _private member_ `bool bDisableImmediateAssetDiscovery;` — Defers the cost to extract metadata for each discovered asset during the initial asset registry scan into a single pass over the full asset registry once the scan is complete.

#### struct `FRigVMFindInBlueprintSearchManager::FActiveSearchQuery`  
`struct FActiveSearchQuery`  
_L799-813_
- desc: Contains info about an active search query
- L802 _public member_ `TAtomic<int32> NextIndex;` — Current search array index
- L804 _public member_ `TAtomic<int32> SearchCount;` — Current count of assets searched
- L806 _public member_ `TQueue<FSoftObjectPath> DeferredAssetPaths;` — Asset paths for which searching was deferred due to being indexed
- L808 _public function_ `FActiveSearchQuery() :NextIndex(0) ,SearchCount(0)`

#### struct `FRigVMDisableGatheringDataOnScope`  
`struct FRigVMDisableGatheringDataOnScope`  
_L916-927_
- L918 _public member_ `bool bOriginallyEnabled;`
- L919 _public function_ `FRigVMDisableGatheringDataOnScope() : bOriginallyEnabled(FRigVMFindInBlueprintSearchManager::Get().IsGatheringDataEnabled())`
- L923 _public function_ `~FRigVMDisableGatheringDataOnScope()`

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMFindInBlueprint, Warning, All);`
- L52 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMFindInBlueprint, Warning, All);`
- L55 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(RigVMFindInBlueprint);` — CSV stats profiling category
- L65 _typedef_ `typedef TWeakPtr<FRigVMImaginaryFiBData, ESPMode::ThreadSafe> FRigVMImaginaryFiBDataWeakPtr;` — Shared pointers to cached imaginary data (must be declared as thread-safe).
- L66 _typedef_ `typedef TSharedPtr<FRigVMImaginaryFiBData, ESPMode::ThreadSafe> FRigVMImaginaryFiBDataSharedPtr;`
- L68 _macro_ `#define MAX_GLOBAL_FIND_RESULTS 4`
- L195 _prototype_ `ENUM_CLASS_FLAGS(ERigVMSearchDataStateFlags);`
- L335 _prototype_ `ENUM_CLASS_FLAGS(ERigVMFiBCacheOpFlags);`
- L363 _prototype_ `ENUM_CLASS_FLAGS(ERigVMAddOrUpdateBlueprintSearchMetadataFlags);`
- L426 _typedef_ `typedef TSharedPtr<FRigVMFindInBlueprintsResult> FRigVMSearchResult;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMFindInBlueprints.h` (Private)


#### struct `RigVMFindInBlueprintsHelpers::FSimpleFTextKeyStorage`  
`struct FSimpleFTextKeyStorage`  
_L69-83_
- desc: Stores an FText as if it were an FString, does zero advanced comparisons needed for true FText comparisons
- L71 _public member_ `FText Text;`
- L73 _public function_ `FSimpleFTextKeyStorage(FText InText) : Text(InText)`
- L79 _public function_ `bool operator==(const FSimpleFTextKeyStorage& InObject) const`

#### class `FRigVMFindInBlueprintsNoResult`  
`class FRigVMFindInBlueprintsNoResult : public FRigVMFindInBlueprintsResult`  
_L130-145_
- inherits: `FRigVMFindInBlueprintsResult`
- desc: Class used to denote an empty search result
- L133 _public function_ `FRigVMFindInBlueprintsNoResult(const FText& InDisplayText) :FRigVMFindInBlueprintsResult(InDisplayText)`
- L139 _public function_ `virtual FReply OnClick() override` — FRigVMFindInBlueprintsResult Interface

#### class `FRigVMFindInBlueprintsGraphNode`  
`class FRigVMFindInBlueprintsGraphNode : public FRigVMFindInBlueprintsResult`  
_L148-178_
- inherits: `FRigVMFindInBlueprintsResult`
- desc: Graph nodes use this class to store their data
- L151 _public prototype_ `FRigVMFindInBlueprintsGraphNode();`
- L152 _public prototype_ `virtual ~FRigVMFindInBlueprintsGraphNode() = default;`
- L155 _public prototype_ `virtual FReply OnClick() override;` — FRigVMFindInBlueprintsResult Interface
- L156 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L157 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L158 _public prototype_ `virtual FText GetCategory() const override;`
- L159 _public prototype_ `virtual void FinalizeSearchData() override;`
- L160 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const override;`
- L165 _private member_ `FGuid NodeGuid;` — The Node Guid to find when jumping to the node
- L168 _private member_ `FSlateIcon Glyph;` — The glyph brush for this node
- L171 _private member_ `FLinearColor GlyphColor;` — The glyph color for this node
- L174 _private member_ `UClass* Class;` — The class this item refers to
- L177 _private member_ `FString ClassName;` — The class name this item refers to

#### class `FRigVMFindInBlueprintsPin`  
`class FRigVMFindInBlueprintsPin : public FRigVMFindInBlueprintsResult`  
_L181-203_
- inherits: `FRigVMFindInBlueprintsResult`
- desc: Pins use this class to store their data
- L184 _public prototype_ `FRigVMFindInBlueprintsPin(FString InSchemaName);`
- L185 _public prototype_ `virtual ~FRigVMFindInBlueprintsPin() = default;`
- L188 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;` — FRigVMFindInBlueprintsResult Interface
- L189 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L190 _public prototype_ `virtual FText GetCategory() const override;`
- L191 _public prototype_ `virtual void FinalizeSearchData() override;`
- L196 _private member_ `FString SchemaName;` — The name of the schema this pin exists under
- L199 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L202 _private member_ `FSlateColor IconColor;` — Pin's icon color

#### class `FRigVMFindInBlueprintsProperty`  
`class FRigVMFindInBlueprintsProperty : public FRigVMFindInBlueprintsResult`  
_L206-229_
- inherits: `FRigVMFindInBlueprintsResult`
- desc: Property data is stored here
- L209 _public prototype_ `FRigVMFindInBlueprintsProperty();`
- L210 _public prototype_ `virtual ~FRigVMFindInBlueprintsProperty() = default;`
- L213 _public prototype_ `virtual FReply OnClick() override;` — FRigVMFindInBlueprintsResult Interface
- L214 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L215 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L216 _public prototype_ `virtual FText GetCategory() const override;`
- L217 _public prototype_ `virtual void FinalizeSearchData() override;`
- L222 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L225 _private member_ `FString DefaultValue;` — The default value of a property as a string
- L228 _private member_ `bool bIsSCSComponent;` — TRUE if the property is an SCS_Component

#### class `FRigVMFindInBlueprintsGraph`  
`class FRigVMFindInBlueprintsGraph : public FRigVMFindInBlueprintsResult`  
_L232-248_
- inherits: `FRigVMFindInBlueprintsResult`
- desc: Graphs, such as functions and macros, are stored here
- L235 _public prototype_ `FRigVMFindInBlueprintsGraph(EGraphType InGraphType);`
- L236 _public prototype_ `virtual ~FRigVMFindInBlueprintsGraph() = default;`
- L239 _public prototype_ `virtual FReply OnClick() override;` — FRigVMFindInBlueprintsResult Interface
- L240 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L241 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L242 _public prototype_ `virtual FText GetCategory() const override;`
- L247 _private member_ `EGraphType GraphType;` — The type of graph this represents

#### enum `ERigVMFiBCacheBarWidget`  
`enum class ERigVMFiBCacheBarWidget`  
_L251-261_
- desc: Cache bar widgets.
- L253 _public enumerator_ `ProgressBar`
- L254 _public enumerator_ `CloseButton`
- L255 _public enumerator_ `CancelButton`
- L256 _public enumerator_ `CacheAllUnindexedButton`
- L257 _public enumerator_ `CurrentAssetNameText`
- L258 _public enumerator_ `UnresponsiveEditorWarningText`
- L259 _public enumerator_ `ShowCacheFailuresButton`
- L260 _public enumerator_ `ShowCacheStatusText`

#### enum `ERigVMFiBSearchBarWidget`  
`enum class ERigVMFiBSearchBarWidget`  
_L264-269_
- desc: Search bar widgets.
- L266 _public enumerator_ `StatusText`
- L267 _public enumerator_ `Throbber`
- L268 _public enumerator_ `ProgressBar`

#### enum `ERigVMFiBIndexAllPermission`  
`enum class ERigVMFiBIndexAllPermission`  
_L275-283_
- reflection: `UENUM()`
- desc: Whether the Find-in-Blueprints window allows the user to load and resave all assets with out-of-date Blueprint search metadata
- L278 _public enumerator_ `None` — Users may not automatically load all Blueprints with out-of-date search metadata
- L280 _public enumerator_ `LoadOnly` — Users may automatically load all Blueprints with out-of-date search metadata, but not resave
- L282 _public enumerator_ `CheckoutAndResave` — Users may automatically checkout, load and resave all Blueprints with out-of-date search metadata

#### class `SRigVMFindInBlueprints`  
`class SRigVMFindInBlueprints: public SCompoundWidget`  
_L288-522_
- inherits: `SCompoundWidget`
- desc: Widget for searching for (functions/events) across all blueprints or just a single blueprint
- L291 _public function_ `SLATE_BEGIN_ARGS( SRigVMFindInBlueprints ) : _bIsSearchWindow(true) , _bHideSearchBar(false) , _bHideFindGlobalButton(false) , _ContainingTab()`
- L297 _public prototype_ `SLATE_ARGUMENT(bool, bIsSearchWindow) SLATE_ARGUMENT(bool, bHideSearchBar) SLATE_ARGUMENT(bool, bHideFindGlobalButton) SLATE_ARGUMENT(TSharedPtr<SDockTab>, ContainingTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FRigVMEditorBase> InBlueprintEditor = nullptr);`
- L304 _public prototype_ `~SRigVMFindInBlueprints();`
- L307 _public prototype_ `void FocusForUse(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false);` — Focuses this widget's search box, and changes the mode as well, and optionally the search terms
- L317 _public prototype_ `void MakeSearchQuery(FString InSearchString, bool bInIsFindWithinBlueprint, const FRigVMStreamSearchOptions& InSearchOptions = FRigVMStreamSearchOptions(), FRigVMOnSearchComplete InOnSearchComplete = FRigVMOnSearchComplete());` — Submits a search query @param InSearchString						String to search using @param bInIsFindWithinBlueprint				TRUE if searching within the current Blueprint only @param InSearchOptions						Optional search parameters. @param InOnSearchComplete					Callback when the search is complete, passing the filtered imaginary data (if any).
- L320 _public prototype_ `void OnCacheStarted(ERigVMFiBCacheOpType InOpType, ERigVMFiBCacheOpFlags InOpFlags);` — Called when caching Blueprints is started
- L323 _public prototype_ `void OnCacheComplete(ERigVMFiBCacheOpType InOpType, ERigVMFiBCacheOpFlags InOpFlags);` — Called when caching Blueprints is complete
- L330 _public prototype_ `void CacheAllBlueprints(const FRigVMFindInBlueprintCachingOptions& InOptions);` — Asynchronously caches all Blueprints below a specified version. @param InOptions								Options to configure the caching task
- L333 _public prototype_ `FName GetHostTabId() const;` — If this is a global find results widget, returns the host tab's unique ID. Otherwise, returns NAME_None.
- L336 _public prototype_ `void CloseHostTab();` — If this is a global find results widget, ask the host tab to close
- L339 _public function_ `bool IsLocked() const` — Determines if this context does not accept syncing from an external source
- L345 _public prototype_ `bool IsSearchInProgress() const;` — Determines whether a search query is actively in progress
- L348 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget overrides
- L351 _public prototype_ `void ClearResults();` — Clears the currently visible results
- L355 _private prototype_ `EActiveTimerReturnType UpdateSearchResults( double InCurrentTime, float InDeltaTime );` — Processes results of the ongoing async stream search
- L358 _private prototype_ `void RegisterCommands();` — Register any Find-in-Blueprint commands
- L361 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L364 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L367 _private prototype_ `void OnGetChildren( FRigVMSearchResult InItem, TArray< FRigVMSearchResult >& OutChildren );` — Get the children of a row
- L370 _private prototype_ `void OnTreeSelectionDoubleClicked( FRigVMSearchResult Item );` — Called when user double clicks on a new result
- L373 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FRigVMSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L376 _private prototype_ `void LaunchStreamThread(const FString& InSearchValue, const FRigVMStreamSearchOptions& InSearchOptions = FRigVMStreamSearchOptions(), FRigVMOnSearchComplete InOnSearchComplete = FRigVMOnSearchComplete());` — Launches a thread for streaming more content into the results widget
- L379 _private prototype_ `TOptional<float> GetPercentCompleteSearch() const;` — Returns the percent complete on the search for the progress bar
- L382 _private prototype_ `EVisibility GetSearchBarWidgetVisiblity(ERigVMFiBSearchBarWidget InSearchBarWidget) const;` — Returns the search bar visiblity for the given widget
- L385 _private prototype_ `void ConditionallyAddCacheBar();` — Adds the "cache" bar at the bottom of the Find-in-Blueprints widget, to notify the user that the search is incomplete
- L388 _private prototype_ `FReply OnRemoveCacheBar();` — Callback to remove the "cache" bar when a button is pressed
- L391 _private prototype_ `FText GetCacheBarStatusText() const;` — Callback to return the cache bar's display text, informing the user of the situation
- L394 _private prototype_ `FText GetCacheBarCurrentAssetName() const;` — Callback to return the current asset name during a cache operation
- L397 _private prototype_ `bool CanCacheAllUnindexedBlueprints() const;` — Whether user is allowed to initiate loading and indexing all blueprints with out-of-date metadata
- L400 _private prototype_ `FReply OnCacheAllUnindexedBlueprints();` — Callback to cache all unindexed Blueprints
- L403 _private prototype_ `FReply OnExportUnindexedAssetList();` — Callback to export a list of all blueprints that need reindexing
- L406 _private prototype_ `FReply OnCacheAllBlueprints(const FRigVMFindInBlueprintCachingOptions& InOptions);` — Callback to cache all Blueprints according to the given options
- L409 _private prototype_ `FReply OnCancelCacheAll();` — Callback to cancel the caching process
- L412 _private prototype_ `int32 GetCurrentCacheIndex() const;` — Retrieves the current index of the Blueprint caching process
- L415 _private prototype_ `TOptional<float> GetPercentCompleteCache() const;` — Gets the percent complete of the caching process
- L418 _private prototype_ `EVisibility GetCacheBarVisibility() const;` — Returns the caching bar's visibility, it goes invisible when there is nothing to be cached. The next search will remove this bar or make it visible again
- L421 _private prototype_ `EVisibility GetCacheBarWidgetVisibility(ERigVMFiBCacheBarWidget InCacheBarWidget) const;` — Returns the cache bar visibility for the given widget
- L424 _private prototype_ `bool IsCacheInProgress() const;` — Returns TRUE if Blueprint caching is in progress
- L427 _private prototype_ `const FSlateBrush* GetCacheBarImage() const;` — Returns the BG image used for the cache bar
- L430 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Callback to build the context menu when right clicking in the tree
- L433 _private prototype_ `void SelectAllItemsHelper(FRigVMSearchResult InItemToSelect);` — Helper function to select all items
- L436 _private prototype_ `void OnSelectAllAction();` — Callback when user attempts to select all items in the search results
- L439 _private prototype_ `void OnCopyAction();` — Callback when user attempts to copy their selection in the Find-in-Blueprints
- L442 _private prototype_ `FReply OnOpenGlobalFindResults();` — Called when the user clicks the global find results button
- L445 _private prototype_ `void OnHostTabClosed(TSharedRef<SDockTab> DockTab);` — Called when the host tab is closed (if valid)
- L448 _private prototype_ `FReply OnLockButtonClicked();` — Called when the lock button is clicked in a global find results tab
- L451 _private prototype_ `const FSlateBrush* OnGetLockButtonImage() const;` — Returns the image used for the lock button in a global find results tab
- L455 _private member_ `TWeakPtr<class FRigVMEditorBase> EditorPtr;` — Pointer back to the blueprint editor that owns us
- L458 _private member_ `TSharedPtr<SRigVMTreeViewType> TreeView;` — The tree view displays the results
- L461 _private member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L464 _private member_ `TArray<FRigVMSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L467 _private member_ `FRigVMSearchResult RootSearchResult;` — In Find Within Blueprint mode, we need to keep a handle on the root result, because it won't show up in the tree
- L470 _private member_ `FText HighlightText;` — The string to highlight in the results
- L473 _private member_ `FString SearchValue;` — The string to search for
- L476 _private member_ `TSharedPtr< class FRigVMStreamSearch> StreamSearch;` — Thread object that searches through Blueprint data on a separate thread
- L479 _private member_ `TWeakPtr< SVerticalBox > MainVerticalBox;` — Vertical box, used to add and remove widgets dynamically
- L482 _private member_ `TWeakPtr< SWidget > CacheBarSlot;` — Weak pointer to the cache bar slot, so it can be removed
- L485 _private member_ `FRigVMOnSearchComplete OnSearchComplete;` — Callback when search is complete
- L488 _private member_ `int32 OutOfDateWithLastSearchBPCount;` — Cached count of out of date Blueprints from last search.
- L491 _private member_ `ERigVMFiBVersion LastSearchedFiBVersion;` — Cached version that was last searched
- L494 _private member_ `TSharedPtr< FUICommandList > CommandList;` — Commands handled by this widget
- L497 _private member_ `TWeakPtr<SDockTab> HostTab;` — Tab hosting this widget. May be invalid.
- L500 _private member_ `mutable FSoftObjectPath LastCachedAssetPath;` — Last cached asset path (used during continuous cache operations).
- L503 _private member_ `bool bIsInFindWithinBlueprintMode;` — Should we search within the current blueprint only (rather than all blueprints)
- L506 _private member_ `bool bIsLocked;` — True if current search should not be changed by an external source
- L509 _private member_ `bool bHideProgressBars;` — True if progress bar widgets should be hidden
- L512 _private member_ `bool bShowCacheBarCloseButton;` — True if users should be allowed to close the cache bar while caching
- L515 _private member_ `bool bShowCacheBarCancelButton;` — True if users should be allowed to cancel the active caching operation
- L518 _private member_ `bool bShowCacheBarUnresponsiveEditorWarningText;` — True if the unresponsive warning text should be visible in the cache bar
- L521 _private member_ `bool bKeepCacheBarProgressVisible;` — True if cache bar should remain visible after a caching operation has ended

#### Free symbols / members of external scopes

- L61 _typedef_ `typedef STreeView<FRigVMSearchResult> SRigVMTreeViewType;`
- L63 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMOnSearchComplete, TArray<FRigVMImaginaryFiBDataSharedPtr>&);`
- L63 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMOnSearchComplete, TArray<FRigVMImaginaryFiBDataSharedPtr>&);`
- L66 _namespace_ `namespace RigVMFindInBlueprintsHelpers`
- L86 _prototype_ `UClass* GetFunctionOriginClass(const UFunction* Function);` (scope `RigVMFindInBlueprintsHelpers`) — Utility function to find the ancestor class or interface from which a function is inherited.
- L89 _prototype_ `bool ConstructSearchTermFromFunction(const UFunction* Function, FString& SearchTerm);` (scope `RigVMFindInBlueprintsHelpers`) — Constructs a search term for a function using Find-in-Blueprints search syntax
- L91 _function_ `static uint32 GetTypeHash(const RigVMFindInBlueprintsHelpers::FSimpleFTextKeyStorage& InObject)` (scope `RigVMFindInBlueprintsHelpers`)
- L97 _prototype_ `FText AsFText(TSharedPtr< FJsonValue > InJsonValue, const TMap<int32, FText>& InLookupTable);` (scope `RigVMFindInBlueprintsHelpers`) — Looks up a JsonValue's FText from the passed lookup table
- L100 _prototype_ `FText AsFText(int32 InValue, const TMap<int32, FText>& InLookupTable);` (scope `RigVMFindInBlueprintsHelpers`) — Looks up a JsonValue's FText from the passed lookup table
- L102 _prototype_ `bool IsTextEqualToString(const FText& InText, const FString& InString);` (scope `RigVMFindInBlueprintsHelpers`)
- L111 _prototype_ `FString GetPinTypeAsString(const FEdGraphPinType& InPinType);` (scope `RigVMFindInBlueprintsHelpers`) — Retrieves the pin type as a string value @param InPinType		The pin type to look at @return				The pin type as a string in format [category]'[sub-category object]'
- L121 _prototype_ `bool ParsePinType(FText InKey, FText InValue, FEdGraphPinType& InOutPinType);` (scope `RigVMFindInBlueprintsHelpers`) — Parses a pin type from passed in key names and values @param InKey					The key name for what the data should be translated as @param InValue				Value to be be translated @param InOutPinType			Modifies the PinType based on the passed parameters, building it up over multiple calls @return						TRUE when the parsing is successful
- L126 _prototype_ `void ExpandAllChildren(FRigVMSearchResult InTreeNode, TSharedPtr<STreeView<TSharedPtr<FRigVMFindInBlueprintsResult>>> InTreeView);` (scope `RigVMFindInBlueprintsHelpers`) — Iterates through all the given tree node's children and tells the tree view to expand them

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/Kismet/RigVMImaginaryBlueprintData.h` (Private)


#### enum `ERigVMSearchableValueStatus`  
`enum ERigVMSearchableValueStatus`  
_L30-42_
- L32 _public enumerator_ `RigVMNotSearchable = 0x00000000` — Cannot search this value, it is used for display purposes only
- L33 _public enumerator_ `RigVMSearchable = 0x00000001` — Generically searchable, value will appear as a sub-item and has no sub-data
- L34 _public enumerator_ `RigVMHidden = 0x00000002` — Item will not be shown
- L35 _public enumerator_ `RigVMExplicit = 0x00000004` — Item must be explicitly requested via the tag
- L38 _public enumerator_ `RigVMCoreDisplayItem = RigVMHidden | RigVMSearchable` — Core display items are searchable but should not display as sub-items because their data is presented in another fashion.
- L39 _public enumerator_ `RigVMExplicitySearchable = RigVMExplicit | RigVMSearchable` — Will only be allowed to be found if searching using a tag
- L40 _public enumerator_ `RigVMExplicitySearchableHidden = RigVMExplicit | RigVMSearchable | RigVMHidden` — Will only be allowed to be found if searching using a tag but will not display the tag in the results (because it is a CoreDisplayItem)
- L41 _public enumerator_ `RigVMAllSearchable = RigVMCoreDisplayItem | RigVMExplicitySearchable` — Covers all searchability methods

#### class `FRigVMSearchableValueInfo`  
`class FRigVMSearchableValueInfo`  
_L44-113_
- L47 _public function_ `FRigVMSearchableValueInfo() : SearchableValueStatus(ERigVMSearchableValueStatus::RigVMNotSearchable) , LookupTableKey(-1)`
- L53 _public function_ `FRigVMSearchableValueInfo(FText InDisplayKey, int32 InLookUpTableKey) : SearchableValueStatus(ERigVMSearchableValueStatus::RigVMSearchable) , DisplayKey(InDisplayKey) , LookupTableKey(InLookUpTableKey)`
- L60 _public function_ `FRigVMSearchableValueInfo(FText InDisplayKey, FText InDisplayText) : SearchableValueStatus(ERigVMSearchableValueStatus::RigVMSearchable) , DisplayKey(InDisplayKey) , LookupTableKey(-1) , DisplayText(InDisplayText)`
- L68 _public function_ `FRigVMSearchableValueInfo(FText InDisplayKey, int32 InLookUpTableKey, ERigVMSearchableValueStatus InSearchableValueStatus) : SearchableValueStatus(InSearchableValueStatus) , DisplayKey(InDisplayKey) , LookupTableKey(InLookUpTableKey)`
- L75 _public function_ `FRigVMSearchableValueInfo(FText InDisplayKey, FText InDisplayText, ERigVMSearchableValueStatus InSearchableValueStatus) : SearchableValueStatus(InSearchableValueStatus) , DisplayKey(InDisplayKey) , LookupTableKey(-1) , DisplayText(InDisplayText)`
- L84 _public function_ `bool IsSearchable() const` — Returns TRUE if the data is searchable
- L87 _public function_ `bool IsCoreDisplay() const` — Returns TRUE if the item should be treated as a CoreDisplayItem, which is searchable but not displayed
- L90 _public function_ `bool IsExplicitSearchable() const` — Returns TRUE if the item should only be searchable if explicitly searched for using the tag
- L93 _public prototype_ `FText GetDisplayText(const TMap<int32, FText>& InLookupTable) const;` — Returns the display text to use for this item
- L96 _public function_ `FText GetDisplayKey() const` — Returns the display key for this item
- L103 _protected member_ `ERigVMSearchableValueStatus SearchableValueStatus;` — The searchability status of this item
- L106 _protected member_ `FText DisplayKey;` — Key that this item is associated with, used for display purposes
- L109 _protected member_ `int32 LookupTableKey;` — Key to use to lookup into a table if DisplayText does not override
- L112 _protected member_ `FText DisplayText;` — Text value to use instead of a lookup into the table

#### struct `FRigVMComponentUniqueDisplay`  
`struct FRigVMComponentUniqueDisplay`  
_L116-126_
- desc: Struct to contain search results and help compare them for uniqueness.
- L118 _public function_ `FRigVMComponentUniqueDisplay( FRigVMSearchResult InSearchResult ) : SearchResult(InSearchResult)`
- L122 _public prototype_ `bool operator==(const FRigVMComponentUniqueDisplay& Other);`
- L125 _public member_ `FRigVMSearchResult SearchResult;` — Search result contained and used for comparing of uniqueness

#### class `FRigVMImaginaryFiBData`  
`class FRigVMImaginaryFiBData : public ITextFilterExpressionContext, public TSharedFromThis<FRigVMImaginaryFiBData, ESPMode::ThreadSafe>`  
_L128-262_
- inherits: `ITextFilterExpressionContext,TSharedFromThis<FRigVMImaginaryFiBData,ESPMode::ThreadSafe>`
- L131 _public prototype_ `FRigVMImaginaryFiBData(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject = TSharedPtr<FJsonObject>(), TMap<int32, FText>* InLookupTablePtr = nullptr);`
- L135 _public function_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override` — We don't actually use these overrides, see FFiBContextHelper for how we call the alternate functions. These will assert if they are accidentally called.
- L136 _public function_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override`
- L140 _public function_ `virtual bool IsCategory() const` — Returns TRUE if this item is a category type, which helps to organize child data
- L143 _public function_ `virtual bool IsTagAndValueCategory() const` — Returns TRUE if this item is considered a Tag and Value category, where it's contents should be considered no different than the parent owner
- L146 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const;` — Checks if the filter is compatible with the current object, returns TRUE by default
- L149 _public prototype_ `virtual bool CanCallFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const;` — Checks if the filter can call functions for the passed filter, returns FALSE by default if the filter is not the AllFilter
- L152 _public prototype_ `void ParseAllChildData(ERigVMSearchableValueStatus InSearchabilityOverride = ERigVMSearchableValueStatus::RigVMSearchable);` — Parses, in a thread-safe manner, all child data, non-recursively, so children will be left in an unparsed Json state
- L155 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode, TMultiMap< const FRigVMImaginaryFiBData*, FRigVMComponentUniqueDisplay >& InOutMatchingSearchComponents) const;` — Test the given value against the strings extracted from the current item. Will return the matching search components if any (can return TRUE without having any if the search components are hidden)
- L158 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode, TMultiMap< const FRigVMImaginaryFiBData*, FRigVMComponentUniqueDisplay >& InOutMatchingSearchComponents) const;` — Perform a complex expression test for the current item. Will return the matching search components if any (can return TRUE without having any if the search components are hidden)
- L161 _public prototype_ `virtual UObject* GetObject(UBlueprint* InBlueprint) const;` — Returns the UObject represented by this Imaginary data give the UBlueprint owner.
- L164 _public function_ `virtual UBlueprint* GetBlueprint() const` — This will return and force load the UBlueprint that owns this object data.
- L174 _public prototype_ `FRigVMSearchResult CreateSearchResult(FRigVMSearchResult InParent) const;` — Requests internal creation of the search result and properly initializes the visual representation of the result
- L177 _public function_ `const TArray<FRigVMImaginaryFiBDataSharedPtr>& GetAllParsedChildData() const` — Accessor for the parsed child data for this item
- L183 _public function_ `void AddKeyValuePair(FText InKey, FRigVMSearchableValueInfo& InValue)` — Adds a KeyValue pair to the ParsedTagAndValues map
- L189 _public function_ `FRigVMImaginaryFiBDataWeakPtr GetOuter() const` — Returns the Outer of this Imaginary data that directly owns it
- L195 _public function_ `void EnableInterlockedParsing()` — Called to enable interlocked parsing (only allow one thread at a time). In place to support backwards-compatibility with non-deferred indexing, may be removed later.
- L201 _public prototype_ `void DumpParsedObject(FArchive& Ar, int32 InTreeLevel = 0) const;` — Dumps the parsed object (including all children) to the given archive
- L204 _public prototype_ `static FRigVMSearchResult CreateSearchTree(FRigVMSearchResult InParentSearchResult, FRigVMImaginaryFiBDataWeakPtr InCurrentPointer, TArray< const FRigVMImaginaryFiBData* >& InValidSearchResults, TMultiMap< const FRigVMImaginaryFiBData*, FRigVMComponentUniqueDisplay >& InMatchingSearchComponents);` — Builds a SearchTree ready to be displayed in the Find-in-Blueprints window
- L214 _protected function_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue)` — Checks if the Key has any special handling to be done, such as making a Pin out of it @param InKey			Key that the JsonValue was stored under @param InJsonValue	JsonValue to be specially parsed @return				TRUE if the JsonValue was specially handled, will not be further handled
- L217 _protected function_ `virtual ERigVMSearchableValueStatus GetSearchabilityStatus(FString InKey)` — Returns the searchability status of a passed in Key, all Keys are searchable by default
- L220 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const = 0;` — Protected internal function which builds the search result for this item
- L223 _protected prototype_ `FText CreateSearchComponentDisplayText(FText InKey, FText InValue) const;` — Creates a display string for this item in search results
- L226 _protected prototype_ `void ParseJsonValue(FText InKey, FText InDisplayKey, TSharedPtr< FJsonValue > InJsonValue, TArray<FRigVMSearchableValueInfo>& OutParsedValues, bool bIsInArray = false, ERigVMSearchableValueStatus InSearchabilityOverride = ERigVMSearchableValueStatus::RigVMSearchable);` — Helper function for parsing Json values into usable properties
- L229 _protected prototype_ `virtual void ParseAllChildData_Internal(ERigVMSearchableValueStatus InSearchabilityOverride = ERigVMSearchableValueStatus::RigVMSearchable);` — Internal version of the ParseAllChildData function, handles the bulk of the work
- L232 _protected function_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const` — Internal helper function for dumping parsed object info
- L236 _protected member_ `TSharedPtr< FJsonObject > UnparsedJsonObject;` — The unparsed Json object representing this item. Auto-cleared after parsing. Does not need to be declared as thread-safe because it's only accessed when parsing and that is already a critical section.
- L239 _protected member_ `TArray<FRigVMImaginaryFiBDataSharedPtr> ParsedChildData;` — All parsed child data for this item. Must be declared as thread-safe because it may be accessed on different threads.
- L242 _protected member_ `TMultiMap< RigVMFindInBlueprintsHelpers::FSimpleFTextKeyStorage, FRigVMSearchableValueInfo > ParsedTagsAndValues;` — A mapping of tags to their values and searchability status
- L245 _protected member_ `TMap<int32, FText>* LookupTablePtr;` — Pointer to the lookup table to decompressed the Json strings back into fully formed FTexts
- L248 _protected member_ `FRigVMImaginaryFiBDataWeakPtr Outer;` — Outer of this object that owns it, used for climbing up the hierarchy. Must be declared as thread-safe because it may be accessed on different threads.
- L251 _protected member_ `TAtomic<bool> bHasParsedJsonObject;` — Set after the JSON object has been parsed.
- L254 _protected member_ `bool bRequiresInterlockedParsing;` — Set if this instance requires interlocked parsing.
- L257 _protected member_ `static FCriticalSection ParseChildDataCriticalSection;` — Allows for thread-safe parsing of the imaginary data. Only a single Imaginary data can be parsed at a time.
- L261 _private member_ `FRigVMSearchResult SearchResultTemplate;` — If display meta is present, this will cache those values and is then used as a basis when constructing a search result tree

#### class `FRigVMFiBMetaData`  
`class FRigVMFiBMetaData : public FRigVMImaginaryFiBData`  
_L264-298_
- inherits: `FRigVMImaginaryFiBData`
- L267 _public prototype_ `FRigVMFiBMetaData(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L270 _public function_ `bool IsHidden() const` — Returns TRUE if the metadata is informing that the FProperty and children should be hidden
- L278 _public function_ `bool IsExplicit() const` — Returns TRUE if the metadata is informing that the FProperty and children should be explicit
- L285 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FRigVMImaginaryFiBData Interface
- L286 _protected function_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override`
- L294 _private member_ `bool bIsHidden;` — TRUE if the FProperty this metadata represents is hidden
- L297 _private member_ `bool bIsExplicit;` — TRUE if the FProperty this metadata represents is explicit, should always be true if bIsHidden is true

#### class `FRigVMCategorySectionHelper`  
`class FRigVMCategorySectionHelper : public FRigVMImaginaryFiBData`  
_L300-338_
- inherits: `FRigVMImaginaryFiBData`
- L304 _public prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMCategorySectionHelperCallback, TSharedPtr< FJsonObject >, TArray<FRigVMImaginaryFiBDataSharedPtr>&);` — Callback declaration for handling special parsing of the items in the category
- L306 _public prototype_ `FRigVMCategorySectionHelper(FRigVMImaginaryFiBDataWeakPtr InOuter, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory);`
- L307 _public prototype_ `FRigVMCategorySectionHelper(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory);`
- L308 _public prototype_ `FRigVMCategorySectionHelper(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FText InCategoryName, bool bInTagAndValueCategory, FRigVMCategorySectionHelperCallback InSpecialHandlingCallback);`
- L311 _public function_ `virtual bool IsCategory() const override` — FRigVMImaginaryFiBData Interface
- L312 _public function_ `virtual bool IsTagAndValueCategory() const override`
- L313 _public prototype_ `virtual bool CanCallFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;`
- L317 _public function_ `FString GetCategoryFunctionName() const` — Returns the category name prepared for checking as a function
- L324 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;` — FRigVMImaginaryFiBData Interface
- L325 _protected prototype_ `virtual void ParseAllChildData_Internal(ERigVMSearchableValueStatus InSearchabilityOverride ) override;`
- L326 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L331 _protected member_ `FRigVMCategorySectionHelperCallback SpecialHandlingCallback;` — Callback to specially handle parsing of the Json Object instead of using generic handling
- L334 _protected member_ `FText CategoryName;` — The display text for this item in the search results
- L337 _protected member_ `bool bIsTagAndValue;` — TRUE if this category should be considered no different than a normal Tag and Value in it's parent

#### class `FRigVMImaginaryBlueprint`  
`class FRigVMImaginaryBlueprint : public FRigVMImaginaryFiBData`  
_L341-374_
- inherits: `FRigVMImaginaryFiBData`
- desc: An "imaginary" representation of a UBlueprint, featuring raw strings or other imaginary objects in the place of more structured substances
- L344 _public prototype_ `FRigVMImaginaryBlueprint(const FString& InBlueprintName, const FString& InBlueprintPath, const FString& InBlueprintParentClass, const TArray<FString>& InInterfaces, const FString& InUnparsedStringData, FRigVMSearchDataVersionInfo InVersionInfo);`
- L347 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface
- L348 _public prototype_ `virtual bool CanCallFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;`
- L349 _public prototype_ `virtual UBlueprint* GetBlueprint() const override;`
- L354 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FRigVMImaginaryFiBData Interface
- L355 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;`
- L356 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L360 _protected prototype_ `void ParseGraph( TSharedPtr< FJsonValue > InJsonValue, FString InCategoryTitle, EGraphType InGraphType );` — Helper function to parse an array of Json Object representing graphs
- L363 _protected prototype_ `void ParseComponents(TSharedPtr< FJsonObject > InJsonObject, TArray<FRigVMImaginaryFiBDataSharedPtr>& OutParsedChildData);` — Callback to specially parse an array of Json Objects representing components
- L366 _protected prototype_ `void ParseToJson(FRigVMSearchDataVersionInfo InVersionInfoconst, const FString& UnparsedStringData);` — Parses a raw string of Json to a Json object hierarchy
- L370 _protected member_ `FString BlueprintPath;` — The path for this Blueprint
- L373 _protected member_ `TMap<int32, FText> LookupTable;` — Lookup table used as a compression tool for the FTexts stored in the Json object

#### class `FRigVMImaginaryGraph`  
`class FRigVMImaginaryGraph : public FRigVMImaginaryFiBData`  
_L377-398_
- inherits: `FRigVMImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraph, featuring raw strings or other imaginary objects in the place of more structured substances
- L380 _public prototype_ `FRigVMImaginaryGraph(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, EGraphType InGraphType);`
- L383 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface
- L384 _public prototype_ `virtual bool CanCallFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;`
- L389 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FRigVMImaginaryFiBData Interface
- L390 _protected prototype_ `virtual ERigVMSearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L391 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;`
- L392 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L397 _protected member_ `EGraphType GraphType;` — The graph type being represented

#### class `FRigVMImaginaryGraphNode`  
`class FRigVMImaginaryGraphNode : public FRigVMImaginaryFiBData`  
_L401-423_
- inherits: `FRigVMImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraphNode, featuring raw strings or other imaginary objects in the place of more structured substances
- L404 _public prototype_ `FRigVMImaginaryGraphNode(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L407 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface
- L408 _public prototype_ `virtual bool CanCallFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;`
- L413 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue) override;` — FRigVMImaginaryFiBData Interface
- L414 _protected prototype_ `virtual ERigVMSearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L415 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;`
- L416 _protected prototype_ `virtual void ParseAllChildData_Internal(ERigVMSearchableValueStatus InSearchabilityOverride ) override;`
- L417 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L422 _private member_ `FString SchemaName;` — Schema name that manages this node

#### class `FRigVMImaginaryProperty`  
`class FRigVMImaginaryProperty : public FRigVMImaginaryFiBData`  
_L426-441_
- inherits: `FRigVMImaginaryFiBData`
- desc: An "imaginary" representation of a FProperty, featuring raw strings or other imaginary objects in the place of more structured substances
- L429 _public prototype_ `FRigVMImaginaryProperty(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L432 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface
- L437 _protected prototype_ `virtual ERigVMSearchableValueStatus GetSearchabilityStatus(FString InKey) override;` — FRigVMImaginaryFiBData Interface
- L438 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;`
- L439 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`

#### class `FRigVMImaginaryComponent`  
`class FRigVMImaginaryComponent : public FRigVMImaginaryProperty`  
_L444-452_
- inherits: `FRigVMImaginaryProperty`
- desc: An "imaginary" representation of a FProperty of an instanced component, featuring raw strings or other imaginary objects in the place of more structured substances
- L447 _public prototype_ `FRigVMImaginaryComponent(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr);`
- L450 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface

#### class `FRigVMImaginaryPin`  
`class FRigVMImaginaryPin : public FRigVMImaginaryFiBData`  
_L455-475_
- inherits: `FRigVMImaginaryFiBData`
- desc: An "imaginary" representation of a UEdGraphPin, featuring raw strings or other imaginary objects in the place of more structured substances
- L458 _public prototype_ `FRigVMImaginaryPin(FRigVMImaginaryFiBDataWeakPtr InOuter, TSharedPtr< FJsonObject > InUnparsedJsonObject, TMap<int32, FText>* InLookupTablePtr, FString InSchemaName);`
- L461 _public prototype_ `virtual bool IsCompatibleWithFilter(ERigVMSearchQueryFilter InSearchQueryFilter) const override;` — FRigVMImaginaryFiBData Interface
- L466 _protected prototype_ `virtual bool TrySpecialHandleJsonValue(FText InKey, TSharedPtr< FJsonValue > InJsonValue);` — FRigVMImaginaryFiBData Interface
- L467 _protected prototype_ `virtual ERigVMSearchableValueStatus GetSearchabilityStatus(FString InKey) override;`
- L468 _protected prototype_ `virtual FRigVMSearchResult CreateSearchResult_Internal(FRigVMSearchResult InTemplate) const override;`
- L469 _protected prototype_ `virtual void DumpParsedObject_Internal(FArchive& Ar) const override;`
- L474 _private member_ `FString SchemaName;` — Schema name that manages this pin

#### Free symbols / members of external scopes

- L304 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMCategorySectionHelperCallback, TSharedPtr< FJsonObject >, TArray<FRigVMImaginaryFiBDataSharedPtr>&);` — Callback declaration for handling special parsing of the items in the category

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/RemoveUnusedMembers/RigVMEditorRemoveUnusedMembers.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::RigVMEditor`)
- L30 _prototype_ `template <typename TRigVMNode> requires ConceptTypeSupportsRemoveUnusedMembers<TRigVMNode> FText GetDialogTitle();` (scope `UE::RigVMEditor::Private`) — Returns a type specific dialog title
- L34 _prototype_ `template <typename TRigVMNode> requires ConceptTypeSupportsRemoveUnusedMembers<TRigVMNode> void FindUnusedMemberNames( const TScriptInterface<IRigVMEditorAssetInterface>& InAsset, const TSharedRef<FRigVMEdGraphNodeRegistry>& InEdGraphNodeRegistry, TMap<FRigVMUnusedMemberCategory, TArray<FName>>& OutCategoryToUnusedMemberNamesMap);` (scope `UE::RigVMEditor::Private`) — Finds unused member names. Considers members with disconnected nodes as unused
- L41 _prototype_ `template <typename TRigVMNode> requires ConceptTypeSupportsRemoveUnusedMembers<TRigVMNode> void RemoveDisconnectedNodes( URigVMController& Controller, const TSharedRef<FRigVMEdGraphNodeRegistry>& EdGraphNodeRegistry, const TArray<FName>& MemberNamesToRemove);` (scope `UE::RigVMEditor::Private`) — Removes disconnected nodes
- L48 _prototype_ `template <typename TRigVMNode> requires ConceptTypeSupportsRemoveUnusedMembers<TRigVMNode> void RemoveMembers( const TScriptInterface<IRigVMEditorAssetInterface>& Asset, const TArray<FName>& MemberNamesToRemove);` (scope `UE::RigVMEditor::Private`) — Removes members
- L61 _function_ `template <typename TRigVMNode> requires ConceptTypeSupportsRemoveUnusedMembers<TRigVMNode> void RemoveUnusedMembersFromAsset( const TScriptInterface<IRigVMEditorAssetInterface>& Asset, const FText& TransactionText = FText::GetEmpty(), const FText& AllMembersReferencedMessage = FText::GetEmpty())` (scope `UE::RigVMEditor`) — Utility to remove unused members from a Rig VM asset. @param Asset							The Asset for which the nodes are removed @param TransactionText				(Optional) The transaction text used when nodes are being removed. If empty or already transacting, no transaction is created. @param AllMembersReferencedMessage	(Optional) The notification message displayed if all members are referenced and none was removed. If empty, no message is displayed.

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/RemoveUnusedMembers/RigVMEditorRemoveUnusedMembersCategory.h` (Private)


#### struct `UE::RigVMEditor::FRigVMUnusedMemberCategory`  
`struct FRigVMUnusedMemberCategory`  
_L15-48_
- desc: A category for related unused members
- L17 _public prototype_ `FRigVMUnusedMemberCategory() = default;`
- L19 _public function_ `FRigVMUnusedMemberCategory(const FName InID, const FText& InCategoryNameText, const bool bInSafeToRemove) : ID(InID) , CategoryNameText(InCategoryNameText) , bSafeToRemove(bInSafeToRemove)`
- L26 _public member_ `FName ID;` — The category ID
- L29 _public member_ `FText CategoryNameText;` — The text for this category
- L32 _public member_ `bool bSafeToRemove = false;` — If true, the members in this category can be safely removed from the Rig
- L34 _public function_ `bool operator==(const FRigVMUnusedMemberCategory& Other) const`
- L39 _public function_ `bool operator!=(const FRigVMUnusedMemberCategory& Other) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L44 _function_ `friend uint32 GetTypeHash(const FRigVMUnusedMemberCategory& Category)` (scope `UE::RigVMEditor`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/RemoveUnusedMembers/RigVMEditorRemoveUnusedMembersDialog.h` (Private)


#### struct `UE::RigVMEditor::FRigVMEditorRemoveUnusedMembersDialog`  
`struct FRigVMEditorRemoveUnusedMembersDialog`  
_L16-39_
- desc: Displays a dialog to remove unsued members when opened
- L36 _public prototype_ `static FResult Open( const FText& DialogTitle, const TMap<FRigVMUnusedMemberCategory, TArray<FName>>& CategoryToUnusedMemberNamesMap);` — Opens the dialog. @param DialogTitle						The tile of the dialog @param CategoryToUnusedMemberNamesMap	A map of categories with their unused member names @return									The Result of the dialog.

#### struct `UE::RigVMEditor::FRigVMEditorRemoveUnusedMembersDialog::FResult`  
`struct FResult`  
_L19-26_
- desc: The result of the dialog
- L22 _public member_ `EAppReturnType::Type AppReturnType = EAppReturnType::Cancel;` — The return type picked by the user
- L25 _public member_ `TArray<FName> MemberNames;` — The array of member names selected to be removed

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/RigVMEditorCommands.h` (Private)


#### class `FRigVMEditorCommands`  
`class FRigVMEditorCommands : public TCommands<FRigVMEditorCommands>`  
_L11-92_
- inherits: `TCommands<FRigVMEditorCommands>`
- L14 _public function_ `FRigVMEditorCommands() : TCommands<FRigVMEditorCommands> ( "RigVMAsset", NSLOCTEXT("Contexts", "RigVM", "RigVM Asset"), NAME_None,`
- L23 _public prototype_ `static TSharedPtr<const FRigVMEditorCommands> GetSharedPtr();`
- L26 _public member_ `TSharedPtr<FUICommandInfo> Compile;` — Compile the blueprint
- L27 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Never;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_SuccessOnly;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Always;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> JumpToErrorNode;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> ToggleFadeUnrelated;` — Edit global options
- L34 _public member_ `TSharedPtr<FUICommandInfo> EditGlobalOptions;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> EditClassDefaults;`
- L38 _public member_ `TSharedPtr< FUICommandInfo > DeleteItem;` — Deletes the selected items and removes their nodes from the graph.
- L41 _public member_ `TSharedPtr< FUICommandInfo > ExecuteGraph;` — Toggle Execute the Graph
- L44 _public member_ `TSharedPtr< FUICommandInfo > AutoCompileGraph;` — Toggle Auto Compilation in the Graph
- L47 _public member_ `TSharedPtr< FUICommandInfo > LockGraph;` — Toggle Locking of the Graph
- L50 _public member_ `TSharedPtr< FUICommandInfo > ToggleEventQueue;` — Toggle between this and the last event queue
- L53 _public member_ `TSharedPtr< FUICommandInfo > RunGraphOnce;` — Run the graph once or continuously
- L56 _public member_ `TSharedPtr< FUICommandInfo > FrameSelection;` — Frames the selected nodes
- L59 _public member_ `TSharedPtr< FUICommandInfo > SwapFunctionWithinAsset;` — Swap Function (Asset)
- L62 _public member_ `TSharedPtr< FUICommandInfo > SwapFunctionAcrossProject;` — Swap Function (Project)
- L65 _public member_ `TSharedPtr< FUICommandInfo > SwapAssetReferences;` — Swap Asset References
- L68 _public member_ `TSharedPtr<FUICommandInfo> ToggleProfiling;` — Toggle heatmap profiling for the graph
- L71 _public member_ `TSharedPtr< FUICommandInfo > TogglePreviewHere;` — Toggle the preview here state of the selected node
- L74 _public member_ `TSharedPtr< FUICommandInfo > PreviewHereStepForward;` — Step to next node during preview
- L77 _public member_ `TSharedPtr< FUICommandInfo > FindReferences;` — Find references for non-functions and variables
- L80 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByNameLocal;` — Find local references for functions and variables by name
- L83 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByNameGlobal;` — Find member references for functions and variables by name
- L88 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L91 _public prototype_ `static void BuildFindReferencesMenu(FMenuBuilder& MenuBuilder);` — Build "Find References" submenu when a context allows for it

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/RigVMPythonLogDetails.h` (Private)


#### class `SRigVMPythonLogDetails`  
`class SRigVMPythonLogDetails : public SCompoundWidget`  
_L11-24_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SRigVMPythonLogDetails)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FRigVMEditorAssetInterfacePtr InAsset);`
- L20 _protected prototype_ `FReply OnCopyPythonScriptClicked() const;`
- L21 _protected prototype_ `FReply OnRunPythonContextClicked() const;`
- L23 _protected member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized;`

#### class `FRigVMPythonLogDetails`  
`class FRigVMPythonLogDetails : public IPropertyTypeCustomization`  
_L26-41_
- inherits: `IPropertyTypeCustomization`
- L30 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L36 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L37 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L40 _private member_ `UObject* BlueprintBeingCustomized = nullptr;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Editor/SRigVMGraphTitleBar.h` (Private)


#### class `SRigVMGraphTitleBar`  
`class SRigVMGraphTitleBar : public SCompoundWidget`  
_L24-80_
- inherits: `SCompoundWidget`
- L26 _private prototype_ `DECLARE_DELEGATE_OneParam( FEdGraphEvent, class UEdGraph* );`
- L29 _public function_ `SLATE_BEGIN_ARGS( SRigVMGraphTitleBar ) : _EdGraphObj(nullptr) , _Editor()`
- L34 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, EdGraphObj ) SLATE_ARGUMENT( TWeakPtr<FRigVMNewEditor>, Editor ) SLATE_ARGUMENT( TSharedPtr<SWidget>, HistoryNavigationWidget ) SLATE_END_ARGS() ~SRigVMGraphTitleBar();`
- L42 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `void Refresh();` — Refresh the toolbar
- L49 _protected member_ `TWeakPtr<FRigVMNewEditor> EditorWeak;` — Owning Kismet 2
- L52 _protected member_ `TObjectPtr<UEdGraph> EdGraphObj = nullptr;` — Edited graph
- L54 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;`
- L57 _protected member_ `TSharedPtr< SBreadcrumbTrail<UEdGraph*> > BreadcrumbTrail;` — Breadcrumb trail widget
- L60 _protected member_ `FText BlueprintTitle;` — Blueprint title being displayed for toolbar
- L64 _protected prototype_ `const FSlateBrush* GetTypeGlyph() const;` — Get the icon to use
- L67 _protected prototype_ `FText GetTitleExtra() const;` — Get the extra title text
- L71 _protected prototype_ `void RebuildBreadcrumbTrail();`
- L73 _protected prototype_ `static FText GetTitleForOneCrumb(const UEdGraph* Graph);`
- L76 _protected prototype_ `UEdGraph* GetOuterGraph( UObject* Obj );` — Function to fetch outer class which is of type UEGraph.
- L79 _protected prototype_ `FText GetBlueprintTitle() const;` — Helper method used to show blueprint title in breadcrumbs

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_OneParam( FEdGraphEvent, class UEdGraph* );`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/RigVMEditorAssetActions.h` (Private)


#### class `FRigVMEditorAssetActions`  
`class FRigVMEditorAssetActions : public FAssetTypeActions_Base`  
_L13-23_
- inherits: `FAssetTypeActions_Base`
- desc: Asset type actions for URigVMEditorAsset that redirects to the runtime asset. When users try to open an EditorAsset directly, we redirect them to open the RuntimeAsset instead, which is the outer object that contains the editor data.
- L17 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L18 _public function_ `virtual FColor GetTypeColor() const override`
- L19 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L21 _public function_ `virtual uint32 GetCategories() override`
- L22 _public function_ `virtual bool CanFilter() override`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Trace/RigVMTraceAnalyzer.h` (Private)


#### class `FRigVMTraceAnalyzer`  
`class FRigVMTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L17-35_
- inherits: `UE::Trace::IAnalyzer`
- desc: The analyzer is used to turn unstructured data from an analytics session into useful bits that can be send to the corresponding provider class.
- L20 _public prototype_ `FRigVMTraceAnalyzer(TraceServices::IAnalysisSession& InSession, FRigVMTraceProvider& InProvider);`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public function_ `virtual void OnAnalysisEnd() override`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L33 _private member_ `TraceServices::IAnalysisSession& Session;`
- L34 _private member_ `FRigVMTraceProvider& Provider;`

#### enum `FRigVMTraceAnalyzer::(anonymous)`  
``  
_L28-31_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L29 _enumerator_ `RouteId_RigVMLiterals` (scope `FRigVMTraceAnalyzer::__anon1716fc210103`)
- L30 _enumerator_ `RouteId_RigVMExecute` (scope `FRigVMTraceAnalyzer::__anon1716fc210103`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Trace/RigVMTraceProvider.h` (Private)


#### class `FRigVMTraceProvider`  
`class FRigVMTraceProvider : public TraceServices::IProvider`  
_L22-50_
- inherits: `TraceServices::IProvider`
- desc: The provider is used to provide data to the world given a corresponding analyzer. The analyzer receives unstructured data from the session and forwards the data to the provider. The provider can then provide the data to the target RigVMHost during playback.
- L25 _public typedef_ `typedef TraceServices::ITimeline<FRigVMTraceExecuteData> ExecuteTimeline;`
- L27 _public member_ `static FName ProviderName;`
- L29 _public prototype_ `FRigVMTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L31 _public prototype_ `bool HasConstantData(uint64 InObjectId) const;`
- L32 _public prototype_ `bool ReadConstantData(uint64 InObjectId, TFunctionRef<void(const FRigVMTraceConstantData&)> Callback) const;`
- L33 _public prototype_ `void EnumerateConstantData(TFunctionRef<void(uint64 OwnerId, const FRigVMTraceConstantData&)> Callback) const;`
- L35 _public prototype_ `bool ReadExecuteTimeline(uint64 InObjectId, TFunctionRef<void(const ExecuteTimeline&)> Callback) const;`
- L36 _public prototype_ `void EnumerateExecuteTimelines(TFunctionRef<void(uint64 OwnerId, const ExecuteTimeline&)> Callback) const;`
- L38 _public prototype_ `void AppendLiterals(const FRigVMTraceConstantData& InConstantData);`
- L39 _public prototype_ `void AppendExecute(const FRigVMTraceExecuteData& InExecuteData);`
- L42 _private prototype_ `uint32 GetExecuteTimelineIndex(uint64 ObjectId);`
- L44 _private member_ `TraceServices::IAnalysisSession& Session;`
- L46 _private member_ `TMap<uint64, uint32> ObjectIdToConstantData;`
- L47 _private member_ `TraceServices::TPagedArray<FRigVMTraceConstantData> ConstantData;`
- L48 _private member_ `TMap<uint64, uint32> ObjectIdToExecuteTimelines;`
- L49 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FRigVMTraceExecuteData>>> ExecuteTimelines;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace TraceServices`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Widgets/RemoveUnusedMembers/RigVMEditorRemoveUnusedMembersColumnID.h` (Private)


#### struct `UE::RigVMEditor::FRigVMEditorRemoveUnusedMembersColumnID`  
`struct FRigVMEditorRemoveUnusedMembersColumnID`  
_L9-16_
- L12 _public member_ `static const FName LabelRow;` — The column to display the member name label
- L15 _public member_ `static const FName SelectedCheckBox;` — The column to display a checkbox to chose if the member should be removed

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Widgets/RemoveUnusedMembers/RigVMEditorRemoveUnusedMembersListItem.h` (Private)


#### struct `UE::RigVMEditor::FRigVMEditorRemoveUnusedMembersListItem`  
`struct FRigVMEditorRemoveUnusedMembersListItem`  
_L10-30_
- desc: An item in the unused members list
- L12 _public prototype_ `FRigVMEditorRemoveUnusedMembersListItem() = default;`
- L13 _public prototype_ `FRigVMEditorRemoveUnusedMembersListItem(const FName& InMemberName, const bool bInInitiallySelected);`
- L16 _public function_ `const FName& GetMemberName() const` — Returns the member name this item stands for
- L19 _public function_ `bool IsSelected() const` — Returns true if the item is selected
- L22 _public function_ `void SetSelected(const bool bInSelected)` — Sets the itetm selected
- L26 _private member_ `FName MemberName;` — The member name this item stands for
- L29 _private member_ `bool bSelected = false;` — If true the item is selected

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Widgets/RemoveUnusedMembers/SRigVMEditorRemoveUnusedMembersDialog.h` (Private)


#### class `UE::RigVMEditor::SRigVMEditorRemoveUnusedMembersDialog`  
`class SRigVMEditorRemoveUnusedMembersDialog : public SCompoundWidget`  
_L21-64_
- inherits: `SCompoundWidget`
- desc: The dialog displayed when removing unused members
- L25 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorRemoveUnusedMembersDialog)`
- L29 _public prototype_ `SLATE_EVENT(FRigVMEditorOnRemoveUnusedMembersDialogEnded, OnDialogEnded) SLATE_END_ARGS() virtual ~SRigVMEditorRemoveUnusedMembersDialog();` — Delegate executed when the dialog is closing
- L36 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<SWindow>& InOwningWindow, const TMap<FRigVMUnusedMemberCategory, TArray<FName>>& CategoryToUnusedMemberNamesMap);` — Constructs this widget
- L43 _private prototype_ `TSharedRef<SWidget> CreateCategory( const FRigVMUnusedMemberCategory& Category, const TArray<FName>& UnusedMemberNames);` — Creates a category with its unused members
- L48 _private prototype_ `TSharedRef<SWidget> CreateDialogButtons();` — Creates the widget that displays the dialog buttons
- L51 _private prototype_ `FReply OnOkClicked();` — Called when the ok button was clicked
- L54 _private prototype_ `FReply OnCancelClicked();` — Called when the cancel button was clicked
- L57 _private member_ `TWeakPtr<SWindow> WeakOwningWindow;` — The widget that owns this dialog
- L60 _private member_ `TArray<TSharedPtr<SRigVMEditorRemoveUnusedMembersList>> UnusedMembersListViews;` — The list views of unused members displayed in this dialog
- L63 _private member_ `FRigVMEditorOnRemoveUnusedMembersDialogEnded OnDialogEndedDelegate;` — Delegate executed when this dialog ended

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMEditorOnRemoveUnusedMembersDialogEnded, const EAppReturnType::Type , const TArray<FName>& );`
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMEditorOnRemoveUnusedMembersDialogEnded, const EAppReturnType::Type , const TArray<FName>& );` (scope `UE::RigVMEditor`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Widgets/RemoveUnusedMembers/SRigVMEditorRemoveUnusedMembersList.h` (Private)


#### class `UE::RigVMEditor::SRigVMEditorRemoveUnusedMembersList`  
`class SRigVMEditorRemoveUnusedMembersList : public SCompoundWidget`  
_L20-77_
- inherits: `SCompoundWidget`
- desc: A list displaying unused members along with an option to remove each item in the list
- L24 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorRemoveUnusedMembersList)`
- L28 _public prototype_ `SLATE_ARGUMENT(FRigVMUnusedMemberCategory, Category) SLATE_ARGUMENT(TArray<FName>, MemberNames) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The category to display in the header
- L39 _public prototype_ `TArray<FName> GetSelectedMemberNames() const;` — Returns the selected member names in this list
- L43 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Generates the header row for the list
- L46 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the list
- L49 _private prototype_ `TSharedRef<SWidget> GenerateHeaderRowLabel() const;` — Generates the header row label
- L52 _private prototype_ `ECheckBoxState IsHeaderRowChecked() const;` — Returns true if the checkbox in the header row is checked
- L55 _private prototype_ `void OnHeaderRowCheckStateChanged(ECheckBoxState NewState);` — Called when the check state of the checkbox in the header row changed
- L58 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnID) const;` — Returns the sort mode for the column
- L61 _private prototype_ `void SortByColumnID(const EColumnSortPriority::Type SortPriority, const FName& ColumnID, const EColumnSortMode::Type InSortMode);` — Sorts the list by column ID
- L64 _private member_ `FRigVMUnusedMemberCategory Category;` — The category to display in the header
- L67 _private member_ `TSharedPtr<SListView<TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem>>> ListView;` — The actual list view
- L70 _private member_ `TArray<TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem>> Items;` — The member names in this list
- L73 _private member_ `FName SortedByColumnID;` — The collumn ID by which this list is sorted
- L76 _private member_ `EColumnSortMode::Type ColumnSortMode = EColumnSortMode::None;` — The sort mode by which sorted by column ID is currently sorted

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Private/Widgets/RemoveUnusedMembers/SRigVMEditorRemoveUnusedMembersRow.h` (Private)


#### class `UE::RigVMEditor::SRigVMEditorRemoveUnusedMembersRow`  
`class SRigVMEditorRemoveUnusedMembersRow : public SMultiColumnTableRow<TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem>>`  
_L15-42_
- inherits: `SMultiColumnTableRow<TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem>>`
- desc: A row displaying a member along with a checkbox to select if it should be removed
- L19 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorRemoveUnusedMembersRow)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedPtr<FRigVMEditorRemoveUnusedMembersListItem>& InItem, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L32 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnID) override;` — Generates a widget for this column ID
- L35 _private prototype_ `ECheckBoxState IsChecked() const;` — Returns true if the checkbox in this row is checked
- L38 _private prototype_ `void OnCheckStateChanged(ECheckBoxState NewState);` — Called when the check state of the checkbox in this row changed
- L41 _private member_ `TWeakPtr<FRigVMEditorRemoveUnusedMembersListItem> WeakItem;` — The item this row displays

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphEnumNodeSpawner.h` (Public)


#### class `URigVMEdGraphEnumNodeSpawner`  
`class URigVMEdGraphEnumNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L12-34_
- inherits: `URigVMEdGraphNodeSpawner`
- L16 _public function_ `virtual ~URigVMEdGraphEnumNodeSpawner()`
- L23 _public prototype_ `URigVMEdGraphEnumNodeSpawner(UEnum* InEnum, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);` — Creates a new URigVMEdGraphEnumNodeSpawner @return A newly allocated instance of this class.
- L26 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L27 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const override;`
- L32 _private member_ `UEnum* Enum;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphFunctionRefNodeSpawner.h` (Public)


#### class `URigVMEdGraphFunctionRefNodeSpawner`  
`class URigVMEdGraphFunctionRefNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L22-75_
- inherits: `URigVMEdGraphNodeSpawner`
- L27 _public function_ `virtual ~URigVMEdGraphFunctionRefNodeSpawner()`
- L35 _public function_ `static URigVMEdGraphFunctionRefNodeSpawner* CreateFromFunction(URigVMLibraryNode* InFunction)` — `UE_DEPRECATED(5.7, "Plase use URigVMEdGraphFunctionRefNodeSpawner(URigVMLibraryNode* InFunction)")` — Creates a new URigVMEdGraphFunctionRefNodeSpawner, charged with spawning a function reference @return A newly allocated instance of this class.
- L36 _public prototype_ `URigVMEdGraphFunctionRefNodeSpawner(URigVMLibraryNode* InFunction);`
- L44 _public function_ `static URigVMEdGraphFunctionRefNodeSpawner* CreateFromAssetData(const FAssetData& InAssetData, const FRigVMGraphFunctionHeader& InPublicFunction)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphFunctionRefNodeSpawner(const FAssetData& InAssetData, const FRigVMGraphFunctionHeader& InPublicFunction)")` — Creates a new URigVMEdGraphFunctionRefNodeSpawner, charged with spawning a function reference @return A newly allocated instance of this class.
- L46 _public function_ `static URigVMEdGraphFunctionRefNodeSpawner* CreateFromAssetData(const FAssetData& InAssetData, const FRigVMOldPublicFunctionData& InPublicFunction)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphFunctionRefNodeSpawner(const FAssetData& InAssetData, const FRigVMOldPublicFunctionData& InPublicFunction)")`
- L47 _public prototype_ `URigVMEdGraphFunctionRefNodeSpawner(const FAssetData& InAssetData, const FRigVMGraphFunctionHeader& InPublicFunction);`
- L48 _public prototype_ `URigVMEdGraphFunctionRefNodeSpawner(const FAssetData& InAssetData, const FRigVMOldPublicFunctionData& InPublicFunction);`
- L51 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L52 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const override;`
- L53 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(TArray<UObject*>& InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins) const override;`
- L60 _private prototype_ `FSoftObjectPath GetResolvedAssetPath() const;` — Returns a resolved asset path. This is directly from the asset data if CreateFromAssetData was used to create the spawner, or if CreateFromFunction, the resolved function path.
- L63 _private member_ `mutable FRigVMGraphFunctionHeader ReferencedPublicFunctionHeader;` — The public function definition we will spawn from [optional]
- L66 _private member_ `bool bIsLocalFunction;` — Marked as true for local function definitions
- L68 _private member_ `mutable FSoftObjectPath AssetPath;`
- L69 _private member_ `mutable FString FunctionPath;`
- L71 _private prototype_ `static URigVMEdGraphNode* SpawnNode(UEdGraph* ParentGraph, FRigVMEditorAssetInterfacePtr Blueprint, FRigVMGraphFunctionHeader& InFunction, FVector2D const Location);`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphInvokeEntryNodeSpawner.h` (Public)


#### class `URigVMEdGraphInvokeEntryNodeSpawner`  
`class URigVMEdGraphInvokeEntryNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L13-36_
- inherits: `URigVMEdGraphNodeSpawner`
- L16 _public function_ `virtual ~URigVMEdGraphInvokeEntryNodeSpawner()`
- L19 _public function_ `static URigVMEdGraphInvokeEntryNodeSpawner* CreateForEntry(URigVMBlueprint* InBlueprint, const FName& InEntryName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)` — `UE_DEPRECATED(5.7, "Plase use URigVMEdGraphInvokeEntryNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, const FName& InEntryName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)")`
- L20 _public prototype_ `URigVMEdGraphInvokeEntryNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, const FName& InEntryName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);`
- L23 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L24 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const override;`
- L25 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(TArray<UObject*>& InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins) const override;`
- L31 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> Blueprint;` — The pin type we will spawn
- L32 _private member_ `TWeakObjectPtr<URigVMGraph> GraphOwner;`
- L33 _private member_ `FName EntryName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphNodeSpawner.h` (Public)


#### class `URigVMEdGraphNodeSpawner`  
`class URigVMEdGraphNodeSpawner : public TSharedFromThis<URigVMEdGraphNodeSpawner>`  
_L16-73_
- inherits: `TSharedFromThis<URigVMEdGraphNodeSpawner>`
- L19 _public function_ `virtual ~URigVMEdGraphNodeSpawner()`
- L22 _public function_ `void SetRelatedBlueprintClass(TSubclassOf<URigVMBlueprint> InClass)` — `UE_DEPRECATED(5.7, "Plase use SetRelatedBlueprintClass(UClass* InClass)")`
- L23 _public prototype_ `void SetRelatedBlueprintClass(UClass* InClass);`
- L47 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(TArray<UObject*>& InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins) const;`
- L48 _public function_ `virtual FString GetSpawnerSignature() const`
- L49 _public function_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const`
- L50 _public prototype_ `static URigVMEdGraphNode* SpawnTemplateNode(URigVMEdGraph* InParentGraph, const TArray<FPinInfo>& InPins, const FName& InNodeName = NAME_None);`
- L52 _public function_ `FText GetMenuName() const`
- L53 _public function_ `FText GetMenuTooltip() const`
- L54 _public function_ `FText GetMenuCategory() const`
- L55 _public function_ `FText GetMenuKeywords() const`
- L56 _public function_ `FSlateIcon GetMenuIcon() const`
- L57 _public function_ `FLinearColor GetMenuColor() const`
- L61 _protected member_ `UClass* RelatedBlueprintClass;`
- L62 _protected member_ `UClass* NodeClass;`
- L65 _protected member_ `FText MenuName;` — Menu signature
- L66 _protected member_ `FText MenuTooltip;`
- L67 _protected member_ `FText MenuCategory;`
- L68 _protected member_ `FText MenuKeywords;`
- L69 _protected member_ `FSlateIcon MenuIcon;`
- L70 _protected member_ `FLinearColor MenuIconTint = FLinearColor::White;`

#### struct `URigVMEdGraphNodeSpawner::FPinInfo`  
`struct FPinInfo`  
_L25-45_
- L27 _public member_ `FName Name;`
- L28 _public member_ `ERigVMPinDirection Direction;`
- L29 _public member_ `FName CPPType;`
- L30 _public member_ `UObject* CPPTypeObject;`
- L32 _public function_ `FPinInfo() : Name(NAME_None) , Direction(ERigVMPinDirection::Invalid) , CPPType(NAME_None) , CPPTypeObject(nullptr)`
- L39 _public function_ `FPinInfo(const FName& InName, ERigVMPinDirection InDirection, const FName& InCPPType, UObject* InCPPTypeObject) : Name(InName) , Direction(InDirection) , CPPType(InCPPType) , CPPTypeObject(InCPPTypeObject)`

#### class `URigVMEdGraphNodeBlueprintSpawner`  
`class URigVMEdGraphNodeBlueprintSpawner : public UBlueprintNodeSpawner`  
_L76-107_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBlueprintNodeSpawner`
- L82 _public function_ `static URigVMEdGraphNodeBlueprintSpawner* CreateFromRigVMSpawner(TSharedPtr<URigVMEdGraphNodeSpawner> InNodeSpawner)`
- L97 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(FBlueprintActionFilter const& Filter) const override;` — UBlueprintNodeSpawner interface
- L98 _public prototype_ `virtual void Prime() override;`
- L99 _public prototype_ `virtual FBlueprintNodeSignature GetSpawnerSignature() const override;`
- L100 _public prototype_ `virtual FBlueprintActionUiSpec GetUiSpec(FBlueprintActionContext const& Context, FBindingSet const& Bindings) const override;`
- L101 _public prototype_ `virtual UEdGraphNode* Invoke(UEdGraph* ParentGraph, FBindingSet const& Bindings, FVector2D const Location) const override;`
- L106 _private member_ `TSharedPtr<URigVMEdGraphNodeSpawner> RigVMSpawner;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphTemplateNodeSpawner.h` (Public)


#### class `URigVMEdGraphTemplateNodeSpawner`  
`class URigVMEdGraphTemplateNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L21-53_
- inherits: `URigVMEdGraphNodeSpawner`
- L25 _public function_ `virtual ~URigVMEdGraphTemplateNodeSpawner()`
- L33 _public function_ `static URigVMEdGraphTemplateNodeSpawner* CreateFromNotation(const FName& InNotation, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphTemplateNodeSpawner(const FName& InNotation, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)")` — Creates a new URigVMEdGraphVariableNodeSpawner, charged with spawning a new member-variable node @return A newly allocated instance of this class.
- L34 _public prototype_ `URigVMEdGraphTemplateNodeSpawner(const FName& InNotation, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);`
- L37 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L38 _public prototype_ `bool IsTemplateNodeFilteredOut(TArray<UObject*>& InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins) const override;`
- L39 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const override;`
- L45 _private member_ `FName TemplateNotation;` — `UPROPERTY(Transient)` — The unit type we will spawn
- L47 _private member_ `const FRigVMTemplate* Template = nullptr;`
- L49 _private prototype_ `static URigVMEdGraphNode* SpawnNode(URigVMEdGraph* ParentGraph, FRigVMEditorAssetInterfacePtr Blueprint, const FRigVMTemplate* Template, FVector2D const Location);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphUnitNodeSpawner.h` (Public)


#### class `URigVMEdGraphUnitNodeSpawner`  
`class URigVMEdGraphUnitNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L22-56_
- inherits: `URigVMEdGraphNodeSpawner`
- L26 _public function_ `virtual ~URigVMEdGraphUnitNodeSpawner()`
- L35 _public function_ `static URigVMEdGraphUnitNodeSpawner* CreateFromStruct(UScriptStruct* InStruct, const FName& InMethodName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphUnitNodeSpawner(UScriptStruct* InStruct, const FName& InMethodName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)")` — Creates a new URigVMEdGraphVariableNodeSpawner, charged with spawning a new unit node @return A newly allocated instance of this class.
- L36 _public prototype_ `URigVMEdGraphUnitNodeSpawner(UScriptStruct* InStruct, const FName& InMethodName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);`
- L39 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L40 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D const Location) const override;`
- L43 _public prototype_ `static void HookupMutableNode(URigVMNode* InModelNode, FRigVMEditorAssetInterfacePtr InRigBlueprint);`
- L47 _private member_ `TObjectPtr<UScriptStruct> StructTemplate;` — The unit type we will spawn
- L49 _private member_ `FName MethodName;`
- L51 _private prototype_ `static URigVMEdGraphNode* SpawnNode(URigVMEdGraph* ParentGraph, FRigVMEditorAssetInterfacePtr Blueprint, UScriptStruct* StructTemplate, const FName& InMethodName, FVector2D Location);`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/NodeSpawners/RigVMEdGraphVariableNodeSpawner.h` (Public)


#### class `URigVMEdGraphVariableNodeSpawner`  
`class URigVMEdGraphVariableNodeSpawner : public URigVMEdGraphNodeSpawner`  
_L20-57_
- inherits: `URigVMEdGraphNodeSpawner`
- L25 _public function_ `virtual ~URigVMEdGraphVariableNodeSpawner()`
- L34 _public function_ `static URigVMEdGraphVariableNodeSpawner* CreateFromExternalVariable(URigVMBlueprint* InBlueprint, const FRigVMExternalVariable& InExternalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphVariableNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, const FRigVMExternalVariable& InExternalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)")` — Creates a new URigVMEdGraphVariableNodeSpawner, charged with spawning a new member-variable node @return A newly allocated instance of this class.
- L36 _public function_ `static URigVMEdGraphVariableNodeSpawner* CreateFromLocalVariable(URigVMBlueprint* InBlueprint, URigVMGraph* InGraphOwner, const FRigVMGraphVariableDescription& InLocalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)` — `UE_DEPRECATED(5.7, "Please use URigVMEdGraphVariableNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, URigVMGraph* InGraphOwner, const FRigVMGraphVariableDescription& InLocalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)")`
- L38 _public prototype_ `URigVMEdGraphVariableNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, const FRigVMExternalVariable& InExternalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);`
- L39 _public prototype_ `URigVMEdGraphVariableNodeSpawner(FRigVMEditorAssetInterfacePtr InBlueprint, URigVMGraph* InGraphOwner, const FRigVMGraphVariableDescription& InLocalVariable, bool bInIsGetter, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip);`
- L42 _public prototype_ `virtual FString GetSpawnerSignature() const override;` — URigVMEdGraphNodeSpawner interface
- L43 _public prototype_ `virtual URigVMEdGraphNode* Invoke(URigVMEdGraph* ParentGraph, FVector2D Location) const override;`
- L44 _public prototype_ `virtual bool IsTemplateNodeFilteredOut(TArray<UObject*>& InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins) const override;`
- L50 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> Blueprint;` — The pin type we will spawn
- L51 _private member_ `TWeakObjectPtr<URigVMGraph> GraphOwner;`
- L52 _private member_ `FRigVMExternalVariable ExternalVariable;`
- L53 _private member_ `bool bIsGetter;`
- L54 _private member_ `bool bIsLocalVariable;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/RigVMEdGraphConnectionDrawingPolicy.h` (Public)


#### class `FRigVMEdGraphConnectionDrawingPolicy`  
`class FRigVMEdGraphConnectionDrawingPolicy : public FKismetConnectionDrawingPolicy`  
_L11-49_
- inherits: `FKismetConnectionDrawingPolicy`
- L14 _public function_ `FRigVMEdGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) : FKismetConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj)`
- L24 _public prototype_ `virtual void SetIncompatiblePinDrawState(const TSharedPtr<SGraphPin>& StartPin, const TSet< TSharedRef<SWidget> >& VisiblePins) override;`
- L25 _public prototype_ `virtual void ResetIncompatiblePinDrawState(const TSet< TSharedRef<SWidget> >& VisiblePins) override;`
- L26 _public prototype_ `virtual void BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries) override;`
- L27 _public prototype_ `virtual void DrawPinGeometries(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L28 _public prototype_ `virtual void DetermineLinkGeometry( FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry) override;`
- L35 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`
- L36 _public function_ `virtual bool UseDrawStateCaching() const override`
- L40 _private member_ `TMap<URigVMEdGraphNode*, bool> RerouteNodeToReversedDirectionMap;` — Each time a reroute node is encountered, input geometry is compared to output geometry to see if the pins on the reroute node need to be reversed
- L42 _private function_ `bool UseLowDetailConnections() const`
- L44 _private prototype_ `bool ShouldChangeTangentForReouteControlPoint(URigVMEdGraphNode* Node);`
- L46 _private prototype_ `bool GetAverageConnectedPositionForPin(UEdGraphPin* InPin, FVector2f& OutPos) const;` — Average of the positions of all pins connected to InPin
- L48 _private member_ `const FSlateBrush* CastImage;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/RigVMEdGraphPanelNodeFactory.h` (Public)


#### class `FRigVMEdGraphPanelNodeFactory`  
`class FRigVMEdGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L9-15_
- inherits: `FGraphPanelNodeFactory`
- L12 _public prototype_ `virtual FName GetFactoryName() const;`
- L14 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/EdGraph/RigVMEdGraphPanelPinFactory.h` (Public)


#### class `FRigVMEdGraphPanelPinFactory`  
`class FRigVMEdGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L10-20_
- inherits: `FGraphPanelPinFactory`
- L13 _public prototype_ `virtual FName GetFactoryName() const;`
- L16 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface
- L19 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin_Internal(class UEdGraphPin* InPin) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMActionMenuBuilder.h` (Public)


#### struct `FRigVMActionMenuBuilder`  
`struct FRigVMActionMenuBuilder : public FGraphActionListBuilderBase`  
_L34-113_
- inherits: `FGraphActionListBuilderBase`
- desc: Responsible for constructing a list of viable blueprint actions. Runs the blueprint actions database through a filter and spawns a series of FRigVMActionMenuItems for actions that pass. Takes care of generating the each menu item's category/name/etc.
- L56 _public prototype_ `FRigVMActionMenuBuilder(EConfigFlags Flags = EConfigFlags::DefaultConfig);` — Default constructor. @param Flags	- Optional configuration flags.
- L59 _public prototype_ `virtual void Empty() override;` — FGraphActionListBuilderBase interface
- L74 _public prototype_ `void AddMenuSection(FBlueprintActionFilter const& Filter, FText const& Heading = FText::GetEmpty());` — Some action menus require multiple sections. One option is to create multiple FRigVMActionMenuBuilders and append them together, but that can be unperformant (each builder will run through the entire database separately)... This method provides an alternative, where you can specify a separate filter/heading/ordering for a sub-section of the menu. @param  Filter	 The filter you want applied to this section of the menu. @param  Heading	 The root category for this section of the menu (can be left blank). @param  MenuOrder The sort order to assign this section of the menu (higher numbers come first). @param  Flags	 Set of ESectionFlags to customize this menu section.
- L81 _public prototype_ `void RebuildActionList();` — Regenerates the entire menu list from the cached menu sections. Filters and adds action items from the blueprint action database (as defined by the MenuSections list).
- L84 _public prototype_ `int32 GetNumPendingActions() const;` — Returns the current number of actions that are still pending
- L87 _public prototype_ `bool ProcessPendingActions();` — Processes any actions that may be added asynchronously or across multiple frames. Returns true if one or more actions were added into the list.
- L90 _public prototype_ `float GetPendingActionsProgress() const;` — Returns the normalized completion state when processing pending actions (e.g. for a status indicator)
- L94 _protected prototype_ `void MakeMenuItems(FBlueprintActionInfo& InAction);` — Adds menu items for the given database action.
- L103 _private member_ `TArray< TSharedRef<FRigVMActionMenuBuilderImpl::FMenuSectionDefinition> > MenuSections;` — Defines all the separate sections of the menu (filter, sort order, etc.). Defined as a TSharedRef<> so as to hide the implementation details (keep this API clean).
- L109 _private member_ `TSharedPtr<FRigVMActionMenuBuilderImpl::FMenuItemListAddHelper> MenuItemListAddHelper;` — Defines a utility that assists with building the list of action menu items for each menu section based on a set of action descriptor records.
- L112 _private member_ `bool bUsePendingActionList;` — If enabled, actions will be added to the pending list rather than processed immediately.

#### enum `FRigVMActionMenuBuilder::EConfigFlags`  
`enum EConfigFlags : uint8`  
_L38-47_
- desc: Flags used to configure the builder.
- L43 _public enumerator_ `UseTimeSlicing = (1<<0)` — If set, the builder will be configured to process the registered action set over time, rather than process the entire set in a single blocking frame.
- L46 _public enumerator_ `DefaultConfig = 0` — The default configuration for this builder type.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`
- L17 _namespace_ `namespace FRigVMActionMenuBuilderImpl`
- L115 _prototype_ `ENUM_CLASS_FLAGS(FRigVMActionMenuBuilder::EConfigFlags);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMActionMenuItem.h` (Public)


#### struct `FRigVMActionMenuItem`  
`struct FRigVMActionMenuItem : public FEdGraphSchemaAction`  
_L39-79_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Wrapper around a UBlueprintNodeSpawner, which takes care of specialized node spawning. This class should not be sub-classed, any special handling should be done inside a UBlueprintNodeSpawner subclass, which will be invoked from this class (separated to divide ui and node-spawning).
- L42 _public function_ `static FName StaticGetTypeId()`
- L46 _public function_ `FRigVMActionMenuItem(UBlueprintNodeSpawner const* NodeSpawner = nullptr) : Action(NodeSpawner), IconTint(FLinearColor::White), IconBrush(nullptr)` — Constructors
- L47 _public prototype_ `FRigVMActionMenuItem(UBlueprintNodeSpawner const* NodeSpawner, FBlueprintActionUiSpec const& UiDef, IBlueprintNodeBinder::FBindingSet const& Bindings = IBlueprintNodeBinder::FBindingSet(), FText InNodeCategory = FText(), int32 InGrouping = 0);`
- L50 _public function_ `virtual FName GetTypeId() const final` — FEdGraphSchemaAction interface
- L51 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) final;`
- L52 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) final;`
- L53 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) final;`
- L57 _public prototype_ `UBlueprintNodeSpawner const* GetRawAction() const;` — @return
- L66 _public prototype_ `FSlateBrush const* GetMenuIcon(FSlateColor& ColorOut);` — Retrieves the icon brush for this menu entry (to be displayed alongside in the menu). @param  ColorOut	An output parameter that's filled in with the color to tint the brush with. @return An slate brush to be used for this menu item in the action menu.
- L72 _private member_ `TObjectPtr<const UBlueprintNodeSpawner> Action;` — Specialized node-spawner, that comprises the action portion of this menu entry.
- L74 _private member_ `FSlateColor IconTint;` — Tint to return along with the icon brush.
- L76 _private member_ `FSlateBrush const* IconBrush;` — Brush that should be used for the icon on this menu item.
- L78 _private member_ `IBlueprintNodeBinder::FBindingSet Bindings;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMActionMenuUtils.h` (Public)


#### struct `FRigVMActionMenuUtils`  
`struct FRigVMActionMenuUtils`  
_L19-44_
- L32 _public prototype_ `static void MakeContextMenu(FBlueprintActionContext const& Context, bool bIsContextSensitive, uint32 ClassTargetMask, FRigVMActionMenuBuilder& MenuOut);` — A centralized utility function for constructing blueprint context menus. Rolls the supplied Context and SelectedProperties into a series of filters that're used to construct the menu. @param  Context				Contains the blueprint/graph/pin that the menu is for. @param  bIsContextSensitive @param  ClassTargetMask @param  MenuOut				The structure that will be populated with context menu items.
- L42 _public prototype_ `static const UK2Node* ExtractNodeTemplateFromAction(const FEdGraphSchemaAction& PaletteAction);` — A number of different palette actions hold onto node-templates in different ways. This handles most of those cases and looks to extract said node- template from the specified action. @param  PaletteAction	The action you want a node-template for. @return A pointer to the extracted node (NULL if the action doesn't have one, or we don't support the specific action type yet)
- L43 _public prototype_ `static const UK2Node* ExtractNodeTemplateFromAction(const TSharedPtr<FEdGraphSchemaAction>& PaletteAction);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMClassSettingsDetailCustomization.h` (Public)


#### class `FRigVMClassSettingsDetailCustomization`  
`class FRigVMClassSettingsDetailCustomization : public IDetailCustomization`  
_L14-39_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<IRigVMEditor> InEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `FRigVMClassSettingsDetailCustomization(TSharedPtr<IRigVMEditor> InEditor, FRigVMEditorAssetInterfacePtr Asset);`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L25 _public prototype_ `void CustomizeSettings(IDetailLayoutBuilder& DetailLayout, TSharedPtr<IRigVMEditor> Editor, FRigVMEditorAssetInterfacePtr Asset);`
- L26 _public prototype_ `void CustomizeDefaults(IDetailLayoutBuilder& DetailLayout, TSharedPtr<IRigVMEditor> Editor, FRigVMEditorAssetInterfacePtr Asset);`
- L29 _private prototype_ `void OnFinishedChangingSettings(const FPropertyChangedEvent& PropertyChangedEvent);`
- L33 _private member_ `TWeakPtr<IRigVMEditor> EditorPtr;` — The Blueprint editor we are embedded in
- L36 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> AssetPtr;` — The blueprint we are editing

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMCommentNodeDetailCustomization.h` (Public)


#### class `FRigVMCommentNodeDetailCustomization`  
`class FRigVMCommentNodeDetailCustomization : public IDetailCustomization`  
_L18-66_
- inherits: `IDetailCustomization`
- L20 _private function_ `FRigVMCommentNodeDetailCustomization() : BlueprintBeingCustomized(nullptr)`
- L28 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L38 _private member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized;`
- L39 _private member_ `mutable TArray<TWeakObjectPtr<URigVMCommentNode>> ObjectsBeingCustomized;`
- L41 _private prototype_ `void CleanupInvalidObjects() const;`
- L43 _private prototype_ `void GetValuesFromNode(TWeakObjectPtr<URigVMCommentNode> Node);`
- L44 _private prototype_ `void SetValues(TWeakObjectPtr<URigVMCommentNode> Node);`
- L46 _private prototype_ `FText GetText() const;`
- L47 _private prototype_ `void SetText(const FText& InNewText, ETextCommit::Type InCommitType);`
- L49 _private prototype_ `FLinearColor GetColor() const;`
- L50 _private prototype_ `FReply OnChooseColor(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L51 _private prototype_ `void OnColorPicked(FLinearColor LinearColor);`
- L53 _private prototype_ `ECheckBoxState IsShowingBubbleEnabled() const;`
- L54 _private prototype_ `void OnShowingBubbleStateChanged(ECheckBoxState InValue);`
- L56 _private prototype_ `ECheckBoxState IsColorBubbleEnabled() const;`
- L57 _private prototype_ `void OnColorBubbleStateChanged(ECheckBoxState InValue);`
- L59 _private prototype_ `TOptional<int> GetFontSize() const;`
- L60 _private prototype_ `void OnFontSizeChanged(int32 InValue, ETextCommit::Type Arg);`
- L62 _private member_ `FString CommentText;`
- L63 _private member_ `bool bShowingBubble;`
- L64 _private member_ `bool bBubbleColorEnabled;`
- L65 _private member_ `int32 FontSize;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMCompilerResultsTabSummoner.h` (Public)


#### struct `FRigVMCompilerResultsTabSummoner`  
`struct FRigVMCompilerResultsTabSummoner : public FWorkflowTabFactory`  
_L17-32_
- inherits: `FWorkflowTabFactory`
- L22 _public function_ `static const FName TabID()`
- L24 _public prototype_ `FRigVMCompilerResultsTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L26 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L28 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "RigVMEditor"`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMDetailsInspectorTabSummoner.h` (Public)


#### struct `FRigVMDetailsInspectorTabSummoner`  
`struct FRigVMDetailsInspectorTabSummoner : public FWorkflowTabFactory`  
_L12-26_
- inherits: `FWorkflowTabFactory`
- L16 _public function_ `static const FName TabID()`
- L19 _public prototype_ `FRigVMDetailsInspectorTabSummoner(const TSharedRef<FRigVMNewEditor>& InRigVMEditor);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L22 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L25 _protected member_ `TWeakPtr<FRigVMNewEditor> RigVMEditor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMDetailsViewWrapperObject.h` (Public)


#### class `URigVMDetailsViewWrapperObject`  
`class URigVMDetailsViewWrapperObject : public UObject`  
_L17-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L22 _public prototype_ `URigVMDetailsViewWrapperObject();`
- L25 _public prototype_ `virtual UClass* GetClassForStruct(UScriptStruct* InStruct, bool bCreateIfNeeded = true) const;` — Creating wrappers from a given struct
- L26 _public prototype_ `static URigVMDetailsViewWrapperObject* MakeInstance(UClass* InWrapperObjectClass, UObject* InOuter, UScriptStruct* InStruct, uint8* InStructMemory, UObject* InSubject = nullptr);`
- L27 _public prototype_ `UScriptStruct* GetWrappedStruct() const;`
- L30 _public prototype_ `virtual UClass* GetClassForNodes(TArray<URigVMNode*> InNodes, bool bCreateIfNeeded = true) const;` — Creating wrappers from a RigVMNode
- L31 _public prototype_ `static URigVMDetailsViewWrapperObject* MakeInstance(UClass* InWrapperObjectClass, UObject* InOuter, TArray<URigVMNode*> InNodes, URigVMNode* InSubject);`
- L33 _public prototype_ `static void MarkOutdatedClass(UClass* InClass);`
- L34 _public prototype_ `static bool IsValidClass(UClass* InClass);`
- L35 _public prototype_ `bool IsActive() const;`
- L37 _public prototype_ `static URigVMDetailsViewWrapperObject* GetOrCreateNewInstance(const UClass* InWrapperObjectClass, UObject* InOuter);`
- L40 _public prototype_ `static void ReturnToPool(URigVMDetailsViewWrapperObject* InInstance);` — Return an instance to the pool for reuse
- L43 _public prototype_ `static void ClearClassPool(UClass* InClass);` — Clear pooled instance of a certain class
- L46 _public prototype_ `static void ClearAllClassPools();` — Clear all pooled instances (call on module shutdown)
- L48 _public prototype_ `FString GetWrappedNodeNotation() const;`
- L50 _public function_ `bool IsChildOf(const UStruct* InStruct) const`
- L57 _public function_ `template<typename T> bool IsChildOf() const`
- L62 _public prototype_ `virtual void SetContent(const uint8* InStructMemory, const UStruct* InStruct);`
- L63 _public prototype_ `virtual void GetContent(uint8* OutStructMemory, const UStruct* InStruct) const;`
- L64 _public prototype_ `void SetContent(URigVMNode* InNode);`
- L67 _public function_ `template<typename T> T GetContent() const`
- L77 _public function_ `template<typename T> void SetContent(const T& InValue)`
- L84 _public prototype_ `UObject* GetSubject() const;`
- L85 _public prototype_ `void SetSubject(UObject* InSubject);`
- L87 _public function_ `FWrappedPropertyChangedChainEvent& GetWrappedPropertyChangedChainEvent()`
- L88 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L93 _private prototype_ `void ResetForReuse();` — Reset instance state for reuse
- L95 _private prototype_ `static void CopyPropertiesForUnrelatedStructs(uint8* InTargetMemory, const UStruct* InTargetStruct, const uint8* InSourceMemory, const UStruct* InSourceStruct);`
- L96 _private prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L97 _private prototype_ `void SetContentForPin(URigVMPin* InPin);`
- L119 _private function_ `friend uint32 GetTypeHash(const FPerClassInfo& Info)`
- L135 _private member_ `static TMap<FPerClassInfo, UClass*> InfoToClass;`
- L136 _private member_ `static TMap<UClass*, FPerClassInfo> ClassToInfo;`
- L137 _private member_ `static TSet<UClass*> OutdatedClassToRecreate;`
- L140 _private member_ `static TMap<UClass*, TArray<URigVMDetailsViewWrapperObject*>> InstancePool;` — Pool of available wrapper objects per class
- L143 _private member_ `static constexpr int32 MaxPoolSizePerClass = 32;` — Maximum pool size per class (prevents unbounded growth)
- L145 _private member_ `bool bIsSettingValue;`
- L148 _private member_ `TWeakObjectPtr<UObject> SubjectPtr;` — `UPROPERTY()`
- L150 _private member_ `FWrappedPropertyChangedChainEvent WrappedPropertyChangedChainEvent;`

#### struct `URigVMDetailsViewWrapperObject::FPerClassInfo`  
`struct FPerClassInfo`  
_L99-133_
- L101 _public member_ `FString Notation;`
- L102 _public member_ `UScriptStruct* ScriptStruct;`
- L104 _public function_ `FPerClassInfo() : Notation() , ScriptStruct(nullptr)`
- L109 _public function_ `FPerClassInfo(UScriptStruct* InScriptStruct) : Notation() , ScriptStruct(InScriptStruct)`
- L114 _public function_ `FPerClassInfo(const FString& InNotation) : Notation(InNotation) , ScriptStruct(nullptr)`
- L124 _public function_ `bool operator ==(const FPerClassInfo& Other) const`
- L129 _public function_ `bool operator !=(const FPerClassInfo& Other) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`
- L14 _delegate_ `DECLARE_EVENT_ThreeParams(URigVMDetailsViewWrapperObject, FWrappedPropertyChangedChainEvent, URigVMDetailsViewWrapperObject*, const FString&, FPropertyChangedChainEvent&);`
- L14 _prototype_ `DECLARE_EVENT_ThreeParams(URigVMDetailsViewWrapperObject, FWrappedPropertyChangedChainEvent, URigVMDetailsViewWrapperObject*, const FString&, FPropertyChangedChainEvent&);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMEditor.h` (Public)


#### enum `RigVMNodeSectionID::Type`  
`enum Type`  
_L49-56_
- desc: Keep the values as they are defined in NodeSectionID, which is defined in BlueprintEditor.h TODO: Once there is no need for FRigVMLegacyEditor, improve the definition of this enum, including a uint8 definition
- L51 _public enumerator_ `NONE = 0`
- L52 _public enumerator_ `GRAPH = 1` — Graph
- L53 _public enumerator_ `FUNCTION = 4` — Functions
- L54 _public enumerator_ `VARIABLE = 8` — Variables
- L55 _public enumerator_ `LOCAL_VARIABLE = 12` — Local variables

#### struct `FRigVMEditorModes`  
`struct FRigVMEditorModes`  
_L59-79_
- L62 _public member_ `static inline const FLazyName RigVMEditorMode = FLazyName(TEXT("RigV` — Mode constants
- L63 _public function_ `static FText GetLocalizedMode(const FName InMode)`
- L78 _private function_ `FRigVMEditorModes()`

#### struct `FRigVMCustomDebugObject`  
`struct FRigVMCustomDebugObject`  
_L81-101_
- L85 _public member_ `UObject* Object;` — Custom object to include, regardless of the current debugging World
- L88 _public member_ `FString NameOverride;` — Override for the object name (if not empty)
- L91 _public function_ `FRigVMCustomDebugObject() : Object(nullptr)`
- L96 _public function_ `FRigVMCustomDebugObject(UObject* InObject, const FString& InLabel) : Object(InObject) , NameOverride(InLabel)`

#### class `IRigVMEditor`  
`class IRigVMEditor`  
_L103-263_
- L107 _public prototype_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() = 0;`
- L109 _public function_ `virtual URigVMBlueprint* GetRigVMBlueprint() const` — `UE_DEPRECATED(5.7, "Plase use GetRigVMAsset")`
- L110 _public prototype_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const = 0;`
- L111 _public prototype_ `virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const = 0;`
- L112 _public prototype_ `virtual URigVMHost* GetRigVMHost() const = 0;`
- L114 _public prototype_ `virtual TSharedPtr<FTabManager> GetTabManager() = 0;`
- L115 _public prototype_ `virtual FName GetGraphExplorerWidgetID() = 0;`
- L116 _public prototype_ `virtual TSharedPtr<class SRigVMDetailsInspector> GetRigVMInspector() const = 0;`
- L117 _public prototype_ `virtual TSharedPtr<SRigVMEditorGraphExplorer> GetGraphExplorerWidget() = 0;`
- L119 _public prototype_ `virtual TSharedPtr<class SKismetInspector> GetKismetInspector() const = 0;`
- L122 _public prototype_ `virtual bool GetIsContextSensitive() = 0;`
- L123 _public prototype_ `virtual void SetIsContextSensitive(const bool bIsContextSensitive) = 0;`
- L125 _public prototype_ `virtual void SetGraphExplorerWidget(TSharedPtr<SRigVMEditorGraphExplorer> InWidget) = 0;`
- L127 _public prototype_ `virtual void GetPinTypeSelectorFilters(TArray<TSharedPtr<class IPinTypeSelectorFilter>>& OutFilters) const = 0;`
- L129 _public prototype_ `DECLARE_EVENT(IRigVMEditor, FOnRefreshEvent);`
- L130 _public prototype_ `virtual FOnRefreshEvent OnRefresh() = 0;`
- L131 _public prototype_ `virtual void ForceEditorRefresh(ERefreshRigVMEditorReason::Type Reason = ERefreshRigVMEditorReason::UnknownReason) = 0;`
- L133 _public prototype_ `DECLARE_EVENT_OneParam(IRigVMEditor, FPreviewHostUpdated, IRigVMEditor*);`
- L134 _public prototype_ `virtual FPreviewHostUpdated& OnPreviewHostUpdated() = 0;`
- L136 _public prototype_ `virtual FRigVMEditorClosed& OnEditorClosed() = 0;`
- L137 _public prototype_ `virtual FRigVMEditorKeyDownDelegate& GetKeyDownDelegate() = 0;`
- L138 _public prototype_ `virtual UEdGraph* GetFocusedGraph() const = 0;`
- L139 _public prototype_ `virtual URigVMGraph* GetFocusedModel() const = 0;`
- L140 _public prototype_ `virtual FNotifyHook* GetNotifyHook() = 0;`
- L141 _public prototype_ `virtual TWeakPtr<class SGraphEditor> GetFocusedGraphEditor() = 0;`
- L143 _public prototype_ `virtual bool InEditingMode() const = 0;`
- L144 _public prototype_ `virtual bool IsEditable(UEdGraph* InGraph) const = 0;`
- L146 _public prototype_ `virtual void OnGraphNodeDropToPerform(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) = 0;`
- L147 _public prototype_ `virtual TSharedRef<FUICommandList> GetToolkitCommands() = 0;`
- L149 _public prototype_ `virtual bool SelectLocalVariable(const UEdGraph* Graph, const FName& VariableName) = 0;`
- L150 _public prototype_ `virtual bool SelectVariable(const FName& VariableName) = 0;`
- L151 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename = false) = 0;`
- L152 _public prototype_ `virtual void OnAddNewLocalVariable() = 0;`
- L153 _public prototype_ `virtual bool CanAddNewLocalVariable() const = 0;`
- L154 _public prototype_ `virtual void OnAddNewVariable() = 0;`
- L155 _public prototype_ `virtual void OnPasteNewLocalVariable(const FBPVariableDescription& VariableDescription) = 0;`
- L156 _public prototype_ `virtual void AddNewFunctionVariant(const UEdGraph* InOriginalFunction) = 0;`
- L157 _public prototype_ `virtual TSharedPtr<SDockTab> OpenDocument(const UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause) = 0;`
- L169 _public prototype_ `virtual void OnNewDocumentClicked(ECreatedDocumentType GraphType) = 0;`
- L170 _public prototype_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false) = 0;`
- L172 _public prototype_ `virtual void GetDebugObjects(TArray<FRigVMCustomDebugObject>& DebugList) const = 0;`
- L173 _public prototype_ `virtual bool OnlyShowCustomDebugObjects() const = 0;`
- L174 _public prototype_ `virtual FString GetCustomDebugObjectLabel(UObject* ObjectBeingDebugged) const = 0;`
- L176 _public prototype_ `virtual TSharedPtr<SGraphEditor> OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus = true) = 0;`
- L177 _public prototype_ `virtual void ZoomToSelection_Clicked() = 0;`
- L179 _public prototype_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) = 0;`
- L180 _public prototype_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) = 0;`
- L181 _public prototype_ `virtual FPreviewScene* GetPreviewScene() = 0;`
- L183 _public prototype_ `virtual bool IsRunGraphOnceOn() const = 0;`
- L184 _public prototype_ `virtual bool CanRunGraphOnce() const = 0;`
- L186 _public prototype_ `virtual bool IsDetailsPanelEditingGlobalOptions() const = 0;`
- L187 _public prototype_ `virtual bool IsDetailsPanelEditingClassDefaults() const = 0;`
- L191 _protected prototype_ `virtual TSharedRef<IRigVMEditor> SharedRef() = 0;`
- L192 _protected prototype_ `virtual TSharedRef<const IRigVMEditor> SharedRef() const = 0;`
- L195 _protected prototype_ `virtual const TSharedPtr<FAssetEditorToolkit> GetHostingApp() const = 0;`
- L196 _protected prototype_ `virtual void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const FName AppIdentifier, const TSharedRef<FTabManager::FLayout>& StandaloneDefaultLayout, const bool bCreateDefaultStandaloneMenu, const bool bCreateDefaultToolbar, const TArray<UObject*>& ObjectsToEdit, const bool bInIsToolbarFocusable = false, const bool bInUseSmallToolbarIcons = false, const TOptional<EAssetOpenMethod>& InOpenMethod = TOptional<EAssetOpenMethod>()) = 0;`
- L197 _protected prototype_ `virtual void CreateEditorToolbar() = 0;`
- L198 _protected prototype_ `virtual void CommonInitialization(const TArray<FRigVMEditorAssetInterfacePtr>& InitBlueprints, bool bShouldOpenInDefaultsMode) = 0;`
- L199 _protected prototype_ `virtual TSharedPtr<FDocumentTracker> GetDocumentManager() const = 0;`
- L200 _protected prototype_ `virtual void AddApplicationMode(FName ModeName, TSharedRef<FApplicationMode> Mode) = 0;`
- L201 _protected prototype_ `virtual void RegenerateMenusAndToolbars() = 0;`
- L202 _protected prototype_ `virtual void SetCurrentMode(FName NewMode) = 0;`
- L203 _protected prototype_ `virtual FEditorModeTools& GetToolkitEditorModeManager() const = 0;`
- L204 _protected prototype_ `virtual void PostLayoutBlueprintEditorInitialization() = 0;`
- L205 _protected prototype_ `virtual bool FindOpenTabsContainingDocument(const UObject* DocumentID, TArray< TSharedPtr<SDockTab> >& Results) = 0;`
- L206 _protected prototype_ `virtual void CloseDocumentTab(const UObject* DocumentID) = 0;`
- L207 _protected prototype_ `virtual TSharedPtr<FApplicationMode> CreateEditorMode() = 0;`
- L208 _protected prototype_ `virtual const FName GetEditorAppName() const = 0;`
- L209 _protected prototype_ `virtual const TArray< UObject* >& GetEditingBlueprints() const = 0;`
- L210 _protected prototype_ `virtual const TSharedRef<IToolkitHost> GetToolkitHost() const = 0;`
- L211 _protected prototype_ `virtual bool IsHosted() const = 0;`
- L212 _protected prototype_ `virtual void BringToolkitToFrontImpl() = 0;`
- L213 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) = 0;`
- L214 _protected prototype_ `virtual TWeakPtr<FDocumentTabFactory> GetGraphEditorTabFactory() const = 0;`
- L215 _protected prototype_ `virtual bool TransactionObjectAffectsBlueprint(UObject* InTransactedObject) = 0;`
- L216 _protected prototype_ `virtual FEdGraphPinType GetLastPinTypeUsed() = 0;`
- L217 _protected prototype_ `virtual void LogSimpleMessage(const FText& MessageText) = 0;`
- L218 _protected prototype_ `virtual void RenameNewlyAddedAction(FName InActionName) = 0;`
- L219 _protected prototype_ `virtual FGraphPanelSelectionSet GetSelectedNodes() const = 0;`
- L220 _protected prototype_ `virtual void SetUISelectionState(FName SelectionOwner) = 0;`
- L221 _protected prototype_ `virtual void AnalyticsTrackNodeEvent(IRigVMEditorAssetInterface* Blueprint, UEdGraphNode *GraphNode, bool bNodeDelete = false) const = 0;`
- L222 _protected prototype_ `virtual void PostUndo(bool bSuccess) = 0;`
- L223 _protected prototype_ `virtual void PostRedo(bool bSuccess) = 0;`
- L224 _protected prototype_ `virtual UEdGraphPin* GetCurrentlySelectedPin() const = 0;`
- L225 _protected prototype_ `virtual void CreateDefaultCommands() = 0;`
- L226 _protected prototype_ `virtual TSharedRef<SGraphEditor> CreateGraphEditorWidget(TSharedRef<class FTabInfo> InTabInfo, class UEdGraph* InGraph) = 0;`
- L227 _protected prototype_ `virtual void CompileImpl() = 0;`
- L228 _protected prototype_ `virtual void SaveAsset_Execute_Impl() = 0;`
- L229 _protected prototype_ `virtual void SaveAssetAs_Execute_Impl() = 0;`
- L230 _protected prototype_ `virtual bool IsGraphInCurrentBlueprint(const UEdGraph* InGraph) const = 0;`
- L231 _protected prototype_ `virtual bool IsEditableImpl(UEdGraph* InGraph) const = 0;`
- L232 _protected prototype_ `virtual void JumpToNode(const class UEdGraphNode* Node, bool bRequestRename = false) = 0;`
- L233 _protected prototype_ `virtual void JumpToPin(const class UEdGraphPin* Pin) = 0;`
- L234 _protected prototype_ `virtual void AddToolbarExtender(TSharedPtr<FExtender> Extender) = 0;`
- L235 _protected prototype_ `virtual void RemoveToolbarExtender(TSharedPtr<FExtender> Extender) = 0;`
- L236 _protected prototype_ `virtual void AddMenuExtender(TSharedPtr<FExtender> Extender) = 0;`
- L237 _protected prototype_ `virtual void RemoveMenuExtender(TSharedPtr<FExtender> Extender) = 0;`
- L238 _protected prototype_ `virtual TSharedPtr<class IMessageLogListing> GetCompilerResultsListing() = 0;`
- L239 _protected prototype_ `virtual void OnBlueprintChangedInnerImpl(IRigVMEditorAssetInterface* InBlueprint, bool bIsJustBeingCompiled = false) = 0;`
- L240 _protected prototype_ `virtual void RefreshEditorsImpl(ERefreshRigVMEditorReason::Type Reason = ERefreshRigVMEditorReason::UnknownReason) = 0;`
- L241 _protected prototype_ `virtual void SetupGraphEditorEventsImpl(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents) = 0;`
- L242 _protected prototype_ `virtual FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed) = 0;`
- L243 _protected prototype_ `virtual void AddReferencedObjectsImpl(FReferenceCollector& Collector) = 0;`
- L244 _protected prototype_ `virtual FGraphAppearanceInfo GetGraphAppearanceImpl(class UEdGraph* InGraph) const = 0;`
- L245 _protected prototype_ `virtual void NotifyPreChangeImpl( FProperty* PropertyAboutToChange ) = 0;`
- L246 _protected prototype_ `virtual void NotifyPostChangeImpl( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) = 0;`
- L247 _protected prototype_ `virtual FName GetSelectedVariableName() = 0;`
- L248 _protected prototype_ `virtual bool IsNodeTitleVisible(const UEdGraphNode* Node, bool bRequestRename) = 0;`
- L249 _protected prototype_ `virtual void EditClassDefaults_Clicked() = 0;`
- L250 _protected prototype_ `virtual void EditGlobalOptions_Clicked() = 0;`
- L251 _protected prototype_ `virtual void TryInvokingDetailsTab(bool bFlash = true) = 0;`
- L252 _protected prototype_ `virtual void RefreshInspector() = 0;`
- L253 _protected prototype_ `virtual void RefreshStandAloneDefaultsEditor() = 0;`
- L254 _protected prototype_ `virtual void RestoreEditedObjectState() = 0;`
- L255 _protected prototype_ `virtual void SetupViewForBlueprintEditingMode() = 0;`
- L256 _protected prototype_ `virtual void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager) = 0;`
- L257 _protected prototype_ `virtual void AddCompileWidget(FToolBarBuilder& ToolbarBuilder) = 0;`
- L258 _protected prototype_ `virtual void AddSettingsAndDefaultWidget(FToolBarBuilder& ToolbarBuilder) = 0;`
- L259 _protected prototype_ `virtual void AddFindWidget(FToolBarBuilder& ToolbarBuilder) = 0;`
- L260 _protected prototype_ `virtual void AddSelectedDebugObjectWidget(FToolBarBuilder& ToolbarBuilder) = 0;`
- L261 _protected prototype_ `virtual void AddAutoCompileWidget(FToolBarBuilder& ToolbarBuilder) = 0;`
- L262 _protected prototype_ `virtual void AddRunOnceWidget(FToolBarBuilder& ToolbarBuilder) = 0;`

#### enum `IRigVMEditor::ECreatedDocumentType`  
`enum ECreatedDocumentType`  
_L160-168_
- desc: Type of new document/graph being created by a menu item
- L162 _public enumerator_ `CGT_NewVariable`
- L163 _public enumerator_ `CGT_NewFunctionGraph`
- L164 _public enumerator_ `CGT_NewMacroGraph`
- L165 _public enumerator_ `CGT_NewAnimationLayer`
- L166 _public enumerator_ `CGT_NewEventGraph`
- L167 _public enumerator_ `CGT_NewLocalVariable`

#### class `FRigVMEditorBase`  
`class FRigVMEditorBase : public IRigVMEditor`  
_L265-636_
- inherits: `IRigVMEditor`
- L276 _public prototype_ `virtual void InitRigVMEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint);` — Edits the specified asset(s) @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InRigVMBlueprint	The blueprint object to start editing.
- L278 _public prototype_ `static FRigVMEditorBase* GetFromAssetEditorInstance(IAssetEditorInstance* Instance);`
- L281 _public prototype_ `virtual URigVMBlueprint* GetRigVMBlueprint() const override;` — `UE_DEPRECATED(5.7, "Please use GetRigVMAsset")` — returns the blueprint being edited
- L282 _public prototype_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const override;`
- L284 _public prototype_ `void HandleJumpToHyperlink(const UObject* InSubject);`
- L286 _public prototype_ `void Compile();`
- L287 _public prototype_ `bool IsCompilingEnabled() const;`
- L289 _public prototype_ `void DeleteSelectedNodes();`
- L290 _public prototype_ `bool CanDeleteNodes() const;`
- L291 _public prototype_ `void CopySelectedNodes();`
- L292 _public prototype_ `bool CanCopyNodes() const;`
- L293 _public prototype_ `void PasteNodes();`
- L294 _public prototype_ `bool CanPasteNodes() const;`
- L295 _public prototype_ `void CutSelectedNodes();`
- L296 _public prototype_ `bool CanCutNodes() const;`
- L297 _public prototype_ `void DuplicateNodes();`
- L298 _public prototype_ `bool CanDuplicateNodes() const;`
- L300 _public prototype_ `void OnStartWatchingPin();`
- L301 _public prototype_ `bool CanStartWatchingPin() const;`
- L302 _public prototype_ `void OnStopWatchingPin();`
- L303 _public prototype_ `bool CanStopWatchingPin() const;`
- L305 _public function_ `virtual FOnRefreshEvent OnRefresh() override`
- L307 _public prototype_ `FText GetGraphDecorationString(UEdGraph* InGraph) const;`
- L308 _public prototype_ `virtual bool IsEditable(UEdGraph* InGraph) const override;`
- L310 _public prototype_ `virtual void OnGraphNodeDropToPerform(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) override;`
- L321 _public prototype_ `static FSlateBrush const* GetVarIconAndColorFromProperty(const FProperty* Property, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut);` — Util for finding a glyph and color for a variable. @param Property       The variable's property @param IconColorOut      The resulting color for the glyph @param SecondaryBrushOut The resulting secondary glyph brush (used for Map types) @param SecondaryColorOut The resulting secondary color for the glyph (used for Map types) @return					The resulting glyph brush
- L332 _public prototype_ `static FSlateBrush const* GetVarIconAndColorFromPinType(const FEdGraphPinType& PinType, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut);` — Util for finding a glyph and color for a variable. @param PinType       The variable's pin type @param IconColorOut      The resulting color for the glyph @param SecondaryBrushOut The resulting secondary glyph brush (used for Map types) @param SecondaryColorOut The resulting secondary color for the glyph (used for Map types) @return					The resulting glyph brush
- L336 _protected prototype_ `FRigVMEditorBase();`
- L337 _protected prototype_ `virtual ~FRigVMEditorBase()= default;`
- L339 _protected prototype_ `void UnbindEditor();`
- L342 _protected prototype_ `void HandleAssetRequestedOpen(UObject* InObject);`
- L343 _protected prototype_ `void HandleAssetRequestClose(UObject* InObject, EAssetEditorCloseReason InReason);`
- L344 _protected member_ `bool bRequestedReopen = false;`
- L346 _protected prototype_ `virtual const FName GetEditorModeName() const;`
- L349 _protected prototype_ `virtual bool InEditingMode() const override;` — FBlueprintEditor interface
- L350 _protected prototype_ `TSubclassOf<UEdGraphSchema> GetDefaultSchemaClass() const;`
- L351 _protected prototype_ `void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);`
- L354 _protected prototype_ `void Tick(float DeltaTime);` — FTickableEditorObject Interface
- L357 _protected prototype_ `void BringToolkitToFront();` — IToolkit Interface
- L358 _protected prototype_ `FName GetToolkitFName() const;`
- L359 _protected prototype_ `FName GetToolkitContextFName() const;`
- L360 _protected prototype_ `FText GetBaseToolkitName() const;`
- L361 _protected prototype_ `FText GetToolkitToolTipText() const;`
- L362 _protected prototype_ `FString GetWorldCentricTabPrefix() const;`
- L363 _protected prototype_ `FLinearColor GetWorldCentricTabColorScale() const;`
- L364 _protected prototype_ `void InitToolMenuContextImpl(FToolMenuContext& MenuContext);`
- L367 _protected prototype_ `bool TransactionObjectAffectsBlueprintImpl(UObject* InTransactedObject);` — BlueprintEditor interface
- L368 _protected prototype_ `virtual bool CanAddNewLocalVariable() const override;`
- L369 _protected prototype_ `virtual void OnAddNewLocalVariable() override;`
- L370 _protected prototype_ `virtual void OnPasteNewLocalVariable(const FBPVariableDescription& VariableDescription) override;`
- L373 _protected function_ `bool IsNativeParentClassCodeLinkEnabled() const`
- L374 _protected function_ `bool ReparentBlueprint_IsVisible() const`
- L375 _protected prototype_ `FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph);`
- L376 _protected function_ `bool ShouldLoadBPLibrariesFromAssetRegistry()`
- L377 _protected prototype_ `bool JumpToHyperlinkImpl(const UObject* ObjectReference, bool bRequestRename = false);`
- L378 _protected function_ `virtual bool ShouldOpenGraphByDefault() const`
- L379 _protected prototype_ `virtual void AddNewFunctionVariant(const UEdGraph* InOriginalFunction) override;`
- L382 _protected prototype_ `void PostUndoImpl(bool bSuccess);` — FEditorUndoClient Interface
- L383 _protected prototype_ `void PostRedoImpl(bool bSuccess);`
- L385 _protected prototype_ `virtual void PostTransaction(bool bSuccess, const FTransaction* Transaction, bool bIsRedo);`
- L388 _protected prototype_ `TStatId GetStatId() const;` — FTickableEditorObject Interface
- L391 _protected prototype_ `virtual URigVMHost* GetRigVMHost() const override;` — returns the currently debugged / viewed host
- L393 _protected prototype_ `virtual UObject* GetOuterForHost() const;`
- L396 _protected prototype_ `virtual UClass* GetDetailWrapperClass() const;` — returns the class to use for detail wrapper objects (UI shim layer)
- L399 _protected function_ `virtual void CreateEmptyGraphContent(URigVMController* InController)` — allows the editor to fill an empty graph
- L401 _protected function_ `virtual FPreviewHostUpdated& OnPreviewHostUpdated() override`
- L403 _protected function_ `virtual FRigVMEditorClosed& OnEditorClosed() override`
- L404 _protected function_ `virtual FRigVMEditorKeyDownDelegate& GetKeyDownDelegate() override`
- L406 _protected prototype_ `virtual bool SelectLocalVariable(const UEdGraph* Graph, const FName& VariableName) override;`
- L407 _protected prototype_ `virtual bool SelectVariable(const FName& VariableName) override;`
- L410 _protected prototype_ `void CreateDefaultCommandsImpl();` — FBlueprintEditor Interface
- L411 _protected prototype_ `void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList);`
- L413 _protected prototype_ `void SaveAsset_Execute();`
- L414 _protected prototype_ `void SaveAssetAs_Execute();`
- L415 _protected function_ `bool IsInAScriptingMode() const`
- L416 _protected prototype_ `virtual void OnNewDocumentClicked(ECreatedDocumentType GraphType) override;`
- L417 _protected prototype_ `bool IsSectionVisibleImpl(RigVMNodeSectionID::Type InSectionID) const;`
- L418 _protected prototype_ `bool NewDocument_IsVisibleForTypeImpl(ECreatedDocumentType GraphType) const;`
- L419 _protected prototype_ `FGraphAppearanceInfo GetGraphAppearance(class UEdGraph* InGraph) const;`
- L420 _protected prototype_ `void OnActiveTabChanged( TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated );`
- L421 _protected prototype_ `void OnSelectedNodesChangedImpl(const TSet<class UObject*>& NewSelection);`
- L422 _protected prototype_ `void OnBlueprintChangedImpl(IRigVMEditorAssetInterface* InBlueprint, bool bIsJustBeingCompiled);`
- L423 _protected prototype_ `virtual void ForceEditorRefresh(ERefreshRigVMEditorReason::Type Reason = ERefreshRigVMEditorReason::UnknownReason) override;`
- L424 _protected prototype_ `void SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents);`
- L425 _protected prototype_ `void FocusInspectorOnGraphSelection(const TSet<class UObject*>& NewSelection, bool bForceRefresh = false);`
- L427 _protected function_ `virtual TSharedPtr<SKismetInspector> GetKismetInspector() const override`
- L430 _protected prototype_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override;`
- L431 _protected prototype_ `virtual void HandleVMCompiledEvent(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext);`
- L432 _protected prototype_ `virtual void HandleVMExecutedEvent(URigVMHost* InHost, const FName& InEventName);`
- L435 _protected prototype_ `void NotifyPreChange(FProperty* PropertyAboutToChange);` — FNotifyHook Interface
- L436 _protected prototype_ `void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged);`
- L438 _protected prototype_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override;` — delegate for changing property
- L439 _protected prototype_ `void OnPropertyChanged(UObject* InObject, FPropertyChangedEvent& InEvent);`
- L440 _protected prototype_ `virtual void OnWrappedPropertyChangedChainEvent(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent);`
- L441 _protected prototype_ `void OnRequestLocalizeFunctionDialog(FRigVMGraphFunctionIdentifier& InFunction, URigVMController* InTargetController, IRigVMGraphFunctionHost* InTargetFunctionHost, bool bForce);`
- L442 _protected prototype_ `FRigVMController_BulkEditResult OnRequestBulkEditDialog(FRigVMEditorAssetInterfacePtr InBlueprint, URigVMController* InController, URigVMLibraryNode* InFunction, ERigVMControllerBulkEditType InEditType);`
- L443 _protected prototype_ `bool OnRequestBreakLinksDialog(TArray<URigVMLink*> InLinks);`
- L444 _protected prototype_ `TRigVMTypeIndex OnRequestPinTypeSelectionDialog(const TArray<TRigVMTypeIndex>& InTypes);`
- L446 _protected prototype_ `bool UpdateDefaultValueForVariable(FRigVMGraphVariableDescription& InVariable, bool bUseDebuggedObject);`
- L448 _protected member_ `URigVMController* ActiveController;`
- L451 _protected prototype_ `virtual void UpdateRigVMHost();` — Push a newly compiled/opened host to the editor
- L452 _protected function_ `virtual void UpdateRigVMHost_PreClearOldHost(URigVMHost* InPreviousHost)`
- L455 _protected prototype_ `virtual void CacheNameLists();` — Update the name lists for use in name combo boxes
- L458 _protected prototype_ `void AddReferencedObjects( FReferenceCollector& Collector );` — FGCObject Interface
- L460 _protected prototype_ `virtual void BindCommands();`
- L461 _protected prototype_ `virtual void UnbindCommands();`
- L463 _protected prototype_ `void ToggleAutoCompileGraph();`
- L464 _protected prototype_ `bool IsAutoCompileGraphOn() const;`
- L465 _protected function_ `bool CanAutoCompileGraph() const`
- L466 _protected prototype_ `void ToggleLockGraph();`
- L467 _protected prototype_ `bool IsLockGraphOn() const;`
- L468 _protected prototype_ `bool CanLockGraph() const;`
- L469 _protected prototype_ `void ToggleEventQueue();`
- L470 _protected prototype_ `void ToggleRunGraphOnce();`
- L471 _protected prototype_ `void SetRunGraphOnce(bool InRunGraphOnceEnabled);`
- L472 _protected prototype_ `virtual bool IsRunGraphOnceOn() const override;`
- L473 _protected function_ `virtual bool CanRunGraphOnce() const override`
- L474 _protected function_ `virtual void OnRunGraphOnceToggled(bool bRunGraphOnceEnabled)`
- L475 _protected prototype_ `TSharedRef<SWidget> GenerateEventQueueMenuContent();`
- L476 _protected prototype_ `virtual FMenuBuilder GenerateBulkEditMenu();`
- L477 _protected prototype_ `TSharedRef<SWidget> GenerateBulkEditMenuContent();`
- L478 _protected prototype_ `virtual void GenerateEventQueueMenuContent(FMenuBuilder& MenuBuilder);`
- L481 _protected prototype_ `FActionMenuContent HandleCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Wraps the normal blueprint editor's action menu creation callback
- L482 _protected prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L485 _protected prototype_ `void UndoAction();` — Undo Action
- L488 _protected prototype_ `void RedoAction();` — Redo Action
- L490 _protected prototype_ `void OnCreateComment();`
- L492 _protected function_ `bool IsDetailsPanelRefreshSuspended() const`
- L493 _protected function_ `bool& GetSuspendDetailsPanelRefreshFlag()`
- L494 _protected prototype_ `TArray<TWeakObjectPtr<UObject>> GetSelectedObjects() const;`
- L495 _protected prototype_ `virtual void SetDetailObjects(const TArray<UObject*>& InObjects);`
- L496 _protected prototype_ `virtual void SetDetailObjects(const TArray<UObject*>& InObjects, bool bChangeUISelectionState);`
- L497 _protected prototype_ `virtual void SetDetailObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InObjectFilter);`
- L498 _protected prototype_ `void SetMemoryStorageDetails(const TArray<FRigVMMemoryStorageStruct*>& InStructs);`
- L499 _protected prototype_ `void SetDetailViewForGraph(URigVMGraph* InGraph);`
- L500 _protected prototype_ `void SetDetailViewForFocusedGraph();`
- L501 _protected prototype_ `void SetDetailViewForLocalVariable();`
- L502 _protected prototype_ `void SetDetailViewForVariable();`
- L503 _protected prototype_ `virtual void RefreshDetailView();`
- L504 _protected prototype_ `bool DetailViewShowsAnyRigUnit() const;`
- L505 _protected prototype_ `bool DetailViewShowsLocalVariable() const;`
- L506 _protected prototype_ `bool DetailViewShowsVariable() const;`
- L507 _protected prototype_ `bool DetailViewShowsStruct(UScriptStruct* InStruct) const;`
- L508 _protected prototype_ `void ClearDetailObject(bool bChangeUISelectionState = true);`
- L509 _protected prototype_ `void ClearDetailsViewWrapperObjects();`
- L510 _protected function_ `const TArray<TStrongObjectPtr<URigVMDetailsViewWrapperObject>>& GetWrapperObjects() const`
- L512 _protected prototype_ `void SetHost(URigVMHost* InHost);`
- L514 _protected prototype_ `virtual URigVMGraph* GetFocusedModel() const override;`
- L515 _protected prototype_ `URigVMController* GetFocusedController() const;`
- L516 _protected prototype_ `TSharedPtr<SGraphEditor> GetGraphEditor(UEdGraph* InEdGraph) const;`
- L519 _protected prototype_ `void ExtendMenu();` — Extend menu
- L522 _protected prototype_ `void ExtendToolbar();` — Extend toolbar
- L525 _protected prototype_ `virtual void FillToolbar(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true);` — Fill the toolbar with content
- L526 _protected prototype_ `virtual void AddLockEditingWidget(FToolBarBuilder& ToolbarBuilder);`
- L528 _protected prototype_ `virtual TArray<FName> GetDefaultEventQueue() const;`
- L529 _protected prototype_ `TArray<FName> GetEventQueue() const;`
- L530 _protected prototype_ `void SetEventQueue(TArray<FName> InEventQueue);`
- L531 _protected prototype_ `virtual void SetEventQueue(TArray<FName> InEventQueue, bool bCompile);`
- L532 _protected function_ `virtual int32 GetEventQueueComboValue() const`
- L533 _protected function_ `virtual FText GetEventQueueLabel() const`
- L534 _protected prototype_ `virtual FSlateIcon GetEventQueueIcon(const TArray<FName>& InEventQueue) const;`
- L535 _protected prototype_ `FSlateIcon GetEventQueueIcon() const;`
- L537 _protected prototype_ `virtual void GetDebugObjects(TArray<FRigVMCustomDebugObject>& DebugList) const override;`
- L538 _protected function_ `virtual bool OnlyShowCustomDebugObjects() const override`
- L539 _protected prototype_ `void HandleSetObjectBeingDebugged(UObject* InObject);`
- L540 _protected prototype_ `virtual FString GetCustomDebugObjectLabel(UObject* ObjectBeingDebugged) const override;`
- L543 _protected prototype_ `void UpdateStaleWatchedPins();` — Update stale watch pins
- L545 _protected prototype_ `virtual void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L546 _protected prototype_ `void HandleVariableDroppedFromBlueprint(UObject* InSubject, FProperty* InVariableToDrop, const FVector2D& InDropPosition, const FVector2D& InScreenPosition);`
- L547 _protected prototype_ `void OnGraphNodeClicked(URigVMEdGraphNode* InNode, const FGeometry& InNodeGeometry, const FPointerEvent& InMouseEvent);`
- L548 _protected prototype_ `void OnNodeDoubleClicked(FRigVMEditorAssetInterfacePtr InBlueprint, URigVMNode* InNode);`
- L549 _protected prototype_ `void OnGraphImported(UEdGraph* InEdGraph);`
- L550 _protected prototype_ `bool OnActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;`
- L551 _protected prototype_ `void FrameSelection();`
- L552 _protected prototype_ `void SwapFunctionWithinAsset();`
- L553 _protected prototype_ `void SwapFunctionAcrossProject();`
- L554 _protected prototype_ `void SwapFunctionForAssets(const TArray<FAssetData>& InAssets, bool bSetupUndo);`
- L555 _protected prototype_ `void SwapAssetReferences();`
- L558 _protected prototype_ `void ToggleProfiling();` — Enables or disables heat map profiling for the graph
- L560 _protected prototype_ `void OnOpenSelectedNodesInNewTab();`
- L561 _protected prototype_ `bool CanOpenSelectedNodesInNewTab() const;`
- L564 _protected prototype_ `void UpdateGraphCompilerErrors();` — Once the log is collected update the graph
- L567 _protected prototype_ `static bool IsPIERunning();` — Returns true if PIE is currently running
- L569 _protected prototype_ `void OnPIEStopped(bool bSimulation);`
- L571 _protected prototype_ `virtual void ToggleFadeOutUnrelateNodes();`
- L572 _protected prototype_ `virtual bool IsToggleFadeOutUnrelatedNodesChecked() const;`
- L574 _protected prototype_ `virtual void AddRunOnceWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L577 _public prototype_ `void OnGraphEditorTick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime, TSharedRef<SGraphEditor> InGraphEditor, URigVMEdGraph* InGraph);`
- L584 _protected member_ `FPreviewHostUpdated PreviewHostUpdated;`
- L586 _protected member_ `TSharedPtr<SRigVMEditorGraphExplorer> GraphExplorerWidget;`
- L588 _protected member_ `FRigVMEditorClosed RigVMEditorClosedDelegate;`
- L589 _protected member_ `FRigVMEditorKeyDownDelegate OnKeyDownDelegate;`
- L591 _protected prototype_ `virtual void SetGraphExplorerWidget(TSharedPtr<SRigVMEditorGraphExplorer> InWidget) override;`
- L592 _protected function_ `virtual TSharedPtr<SRigVMEditorGraphExplorer> GetGraphExplorerWidget() override`
- L594 _protected prototype_ `bool IsEditingSingleBlueprint() const;`
- L597 _protected member_ `bool bAnyErrorsLeft;`
- L598 _protected member_ `TMap<FString, FString> KnownInstructionLimitWarnings;`
- L599 _protected member_ `FString LastDebuggedHost;`
- L601 _protected member_ `bool bSuspendDetailsPanelRefresh;`
- L602 _protected member_ `bool bDetailsPanelRequiresClear;`
- L603 _protected member_ `bool bAllowBulkEdits;`
- L604 _protected member_ `bool bIsSettingObjectBeingDebugged;`
- L606 _protected member_ `bool bRigVMEditorInitialized;`
- L609 _protected member_ `bool bIsCompilingThroughUI;` — Are we currently compiling through the user interface
- L611 _protected member_ `TArray<TStrongObjectPtr<URigVMDetailsViewWrapperObject>> WrapperObjects;`
- L614 _protected member_ `FRigVMLog RigVMLog;` — The log to use for errors resulting from the init phase of the units
- L616 _protected member_ `TArray<FName> LastEventQueue;`
- L619 _protected member_ `TSharedPtr<FExtender> MenuExtender;` — The extender to pass to the level editor to extend it's window menu
- L622 _protected member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender
- L624 _protected member_ `FDelegateHandle PropertyChangedHandle;`
- L626 _protected member_ `FOnRefreshEvent OnRefreshEvent;`
- L628 _protected member_ `bool bRunGraphOnce;`
- L635 _private prototype_ `void OnRequestFindNodeReferences(const UE::RigVMEditor::FRigVMEditorFindNodeReferencesParams Params);` — Called when the editor module requests finding nodes

#### struct `FRigVMEditorZoomLevelsContainer`  
`struct FRigVMEditorZoomLevelsContainer : public FZoomLevelsContainer`  
_L638-725_
- inherits: `FZoomLevelsContainer`
- L656 _public function_ `FRigVMEditorZoomLevelsContainer()`
- L683 _public function_ `float GetZoomAmount(int32 InZoomLevel) const override`
- L689 _public function_ `int32 GetNearestZoomLevel(float InZoomAmount) const override`
- L702 _public function_ `FText GetZoomText(int32 InZoomLevel) const override`
- L708 _public function_ `int32 GetNumZoomLevels() const override`
- L713 _public function_ `int32 GetDefaultZoomLevel() const override`
- L718 _public function_ `EGraphRenderingLOD::Type GetLOD(int32 InZoomLevel) const override`
- L724 _public member_ `TArray<FRigVMEditorZoomLevelEntry> ZoomLevels;`

#### struct `FRigVMEditorZoomLevelsContainer::FRigVMEditorZoomLevelEntry`  
`struct FRigVMEditorZoomLevelEntry`  
_L640-654_
- L643 _public function_ `FRigVMEditorZoomLevelEntry(float InZoomAmount, const FText& InDisplayText, EGraphRenderingLOD::Type InLOD) : DisplayText(FText::Format(NSLOCTEXT("GraphEditor", "Zoom", "Zoom {0}"), InDisplayText)) , ZoomAmount(InZoomAmount) , LOD(InLOD)`
- L651 _public member_ `FText DisplayText;`
- L652 _public member_ `float ZoomAmount;`
- L653 _public member_ `EGraphRenderingLOD::Type LOD;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API RIGVMEDITOR_API`
- L26 _macro_ `#define LOCTEXT_NAMESPACE "RigVMEditor"`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRigVMEditorClosed, const IRigVMEditor*, FRigVMEditorAssetInterfacePtr);`
- L40 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRigVMEditorClosed, const IRigVMEditor*, FRigVMEditorAssetInterfacePtr);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FRigVMEditorKeyDownDelegate, const FGeometry&, const FKeyEvent&);`
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FRigVMEditorKeyDownDelegate, const FGeometry&, const FKeyEvent&);`
- L45 _namespace_ `namespace RigVMNodeSectionID`
- L129 _delegate_ `DECLARE_EVENT(IRigVMEditor, FOnRefreshEvent);`
- L133 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditor, FPreviewHostUpdated, IRigVMEditor*);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMEditorGraphExplorerTabSummoner.h` (Public)


#### struct `FRigVMEditorGraphExplorerTabSummoner`  
`struct FRigVMEditorGraphExplorerTabSummoner : public FWorkflowTabFactory`  
_L12-25_
- inherits: `FWorkflowTabFactory`
- L16 _public function_ `static const FName TabID()`
- L19 _public prototype_ `FRigVMEditorGraphExplorerTabSummoner(const TSharedRef<IRigVMEditor>& InRigVMEditor);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `TWeakPtr<IRigVMEditor> RigVMEditor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMEditorMenuContext.h` (Public)


#### struct `FRigVMEditorGraphMenuContext`  
`struct FRigVMEditorGraphMenuContext`  
_L20-49_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public function_ `FRigVMEditorGraphMenuContext() : Graph(nullptr) , Node(nullptr) , Pin(nullptr)`
- L31 _public function_ `FRigVMEditorGraphMenuContext(TObjectPtr<const URigVMGraph> InGraph, TObjectPtr<const URigVMNode> InNode, TObjectPtr<const URigVMPin> InPin) : Graph(InGraph) , Node(InNode) , Pin(InPin)`
- L40 _public member_ `TObjectPtr<const URigVMGraph> Graph;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMEditor)` — The graph associated with this context.
- L44 _public member_ `TObjectPtr<const URigVMNode> Node;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMEditor)` — The node associated with this context.
- L48 _public member_ `TObjectPtr<const URigVMPin> Pin;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMEditor)` — The pin associated with this context; may be NULL when over a node.

#### class `URigVMEditorMenuContext`  
`class URigVMEditorMenuContext : public UObject`  
_L52-89_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L62 _public prototype_ `void Init(TWeakPtr<IRigVMEditor> InRigVMEditor, const FRigVMEditorGraphMenuContext& InGraphMenuContext = FRigVMEditorGraphMenuContext());` — Initialize the Context @param InRigVMEditor 	    The RigVM Editor hosting the menus @param InGraphMenuContext 	Additional context for specific menus
- L66 _public prototype_ `URigVMBlueprint* GetRigVMBlueprint() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEditor, meta=(DeprecatedFunction, DeprecationMessage="GetRigVMBlueprint is deprecated. Please use GetRigVMAssetInterface instead." ))` — Get the rigvm blueprint that we are editing
- L69 _public prototype_ `TScriptInterface<IRigVMEditorAssetInterface> GetRigVMAssetInterface() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEditor)`
- L73 _public prototype_ `URigVMHost* GetRigVMHost() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEditor)` — Get the active rigvm host instance in the viewport
- L77 _public prototype_ `bool IsAltDown() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEditor)` — Returns true if either alt key is down
- L81 _public prototype_ `FRigVMEditorGraphMenuContext GetGraphMenuContext();` — `UFUNCTION(BlueprintCallable, Category = RigVMEditor)` — Returns context for graph node context menu
- L83 _public prototype_ `IRigVMEditor* GetRigVMEditor() const;`
- L86 _private member_ `TWeakPtr<IRigVMEditor> WeakRigVMEditor;`
- L88 _private member_ `FRigVMEditorGraphMenuContext GraphMenuContext;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMEditorStyle.h` (Public)


#### class `FRigVMEditorStyle`  
`class FRigVMEditorStyle final : public FSlateStyleSet`  
_L13-129_
- inherits: `FSlateStyleSet`
- L35 _private function_ `FRigVMEditorStyle() : FSlateStyleSet("RigVMEditorStyle")`
- L114 _public function_ `static FRigVMEditorStyle& Get()`
- L120 _public function_ `static void Register()`
- L125 _public function_ `static void Unregister()`

#### class `FRigVMEditorStyle::FContentRootBracket`  
`class FContentRootBracket`  
_L16-33_
- L19 _public function_ `FContentRootBracket(FRigVMEditorStyle* InStyle, const FString& NewContentRoot) : Style(InStyle) , PreviousContentRoot(InStyle->GetContentRootDir())`
- L26 _public function_ `~FContentRootBracket()`
- L31 _private member_ `FRigVMEditorStyle* Style;`
- L32 _private member_ `FString PreviousContentRoot;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMEditorTools.h` (Public)


#### class `UE::RigVM::Editor::Tools::FFilterByAssetTag`  
`class FFilterByAssetTag : public FFrontendFilter`  
_L46-61_
- inherits: `FFrontendFilter`
- L49 _public prototype_ `FFilterByAssetTag(TSharedPtr<FFrontendFilterCategory> InCategory, const FRigVMTag& InTag);`
- L51 _public function_ `FString GetName() const override`
- L52 _public function_ `FText GetDisplayName() const override`
- L53 _public function_ `FText GetToolTipText() const override`
- L54 _public function_ `FLinearColor GetColor() const override`
- L56 _public prototype_ `bool PassesFilter(const FContentBrowserItem& InItem) const override;`
- L57 _public function_ `bool ShouldBeMarkedAsInvalid() const`
- L60 _private member_ `FRigVMTag Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RigVM` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::RigVM`)
- L18 _namespace_ `namespace Tools` (scope `UE::RigVM::Editor`)
- L21 _prototype_ `bool PasteNodes(const FVector2D& PasteLocation , const FString& TextToImport , URigVMController* InFocusedController , URigVMGraph* InFocusedModel , URigVMFunctionLibrary* InLocalFunctionLibrary , IRigVMGraphFunctionHost* InGraphFunctionHost , bool bSetupUndoRedo = true , bool bPrintPythonCommands = false);` (scope `UE::RigVM::Editor::Tools`)
- L30 _prototype_ `TArray<FName> ImportNodesFromText(const FVector2D& PasteLocation , const FString& TextToImport , URigVMController* InFocusedController , URigVMGraph* InFocusedModel , URigVMFunctionLibrary* InLocalFunctionLibrary , IRigVMGraphFunctionHost* InGraphFunctionHost , bool bSetupUndoRedo = true , bool bPrintPythonCommands = false);` (scope `UE::RigVM::Editor::Tools`)
- L39 _prototype_ `void OnRequestLocalizeFunctionDialog(FRigVMGraphFunctionIdentifier& InFunction , URigVMController* InTargetController , IRigVMGraphFunctionHost* InTargetFunctionHost , bool bForce);` (scope `UE::RigVM::Editor::Tools`)
- L44 _prototype_ `FAssetData FindAssetFromAnyPath(const FString& InPartialOrFullPath, bool bConvertToRootPath);` (scope `UE::RigVM::Editor::Tools`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMExecutionStackCommands.h` (Public)


#### class `FRigVMExecutionStackCommands`  
`class FRigVMExecutionStackCommands : public TCommands<FRigVMExecutionStackCommands>`  
_L8-39_
- inherits: `TCommands<FRigVMExecutionStackCommands>`
- L11 _public function_ `FRigVMExecutionStackCommands() : TCommands<FRigVMExecutionStackCommands> ( "RigVMExecutionStack", NSLOCTEXT("Contexts", "RigStack", "Execution Stack"), NAME_None,`
- L21 _public member_ `TSharedPtr< FUICommandInfo > FocusOnSelection;` — Focuses on a selected operator's node
- L24 _public member_ `TSharedPtr< FUICommandInfo > GoToInstruction;` — Looks for a specific instruction by index and brings it into focus
- L27 _public member_ `TSharedPtr< FUICommandInfo > SelectTargetInstructions;` — Selects the target instruction(s) of an instruction
- L30 _public member_ `TSharedPtr< FUICommandInfo > ToggleEarlyExitInstruction;` — Sets or unsets the preview here early exit instruction
- L33 _public member_ `TSharedPtr< FUICommandInfo > StepEarlyExitInstruction;` — Steps to the next early exist instruction
- L38 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMExecutionStackTabSummoner.h` (Public)


#### struct `FRigVMExecutionStackTabSummoner`  
`struct FRigVMExecutionStackTabSummoner : public FWorkflowTabFactory`  
_L12-25_
- inherits: `FWorkflowTabFactory`
- L16 _public member_ `static inline const FLazyName TabID = FLazyName(TEXT("Exec`
- L19 _public prototype_ `FRigVMExecutionStackTabSummoner(const TSharedRef<IRigVMEditor>& InRigVMEditor);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `TWeakPtr<IRigVMEditor> RigVMEditor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMFindReferences.h` (Public)


#### class `FRigVMFindResult`  
`class FRigVMFindResult : public TSharedFromThis< FRigVMFindResult >`  
_L23-81_
- inherits: `TSharedFromThis<FRigVMFindResult>`
- L26 _public prototype_ `FRigVMFindResult() = default;`
- L27 _public prototype_ `virtual ~FRigVMFindResult() = default;`
- L31 _public prototype_ `explicit FRigVMFindResult(TWeakObjectPtr<URigVMBlueprint> InBlueprint);` — `UE_DEPRECATED(5.7, "Please use FRigVMFindResult(FRigVMEditorAssetInterfacePtr InBlueprint)")` — Create a root
- L33 _public prototype_ `explicit FRigVMFindResult(TWeakObjectPtr<URigVMBlueprint> InBlueprint, const FText& InDisplayText);` — `UE_DEPRECATED(5.7, "Please use FRigVMFindResult(FRigVMEditorAssetInterfacePtr InBlueprint, const FText& InDisplayText)")`
- L34 _public prototype_ `explicit FRigVMFindResult(TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint);`
- L35 _public prototype_ `explicit FRigVMFindResult(TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint, const FText& InDisplayText);`
- L38 _public prototype_ `virtual FReply OnClick();` — Called when user clicks on the search item
- L41 _public prototype_ `virtual FText GetCategory() const;` — Get Category for this search result
- L44 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L47 _public function_ `virtual void FinalizeSearchData()` — Finalizes any content for the search data that was unsafe to do on a separate thread
- L51 _public prototype_ `URigVMBlueprint* GetBlueprint() const;` — `UE_DEPRECATED(5.7, "Please use FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface()")` — gets the blueprint housing all these search results
- L52 _public prototype_ `FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface();`
- L53 _public prototype_ `const FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const;`
- L61 _public function_ `virtual void ParseSearchInfo(FText InKey, FText InValue)` — Parses search info for specific data important for displaying the search result in an easy to understand format @param	InKey			This is the tag for the data, describing what it is so special handling can occur if needed @param	InValue			Compared against search query to see if it passes the filter, sometimes data is rejected because it is deemed unsearchable
- L64 _public prototype_ `virtual UObject* GetObject(FRigVMEditorAssetInterfacePtr InBlueprint) const;` — Returns the Object represented by this search information give the Blueprint it can be found in
- L67 _public prototype_ `FText GetDisplayString() const;` — Returns the display string for the row
- L71 _public member_ `TArray< TSharedPtr<FRigVMFindResult> > Children;` — Any children listed under this category
- L74 _public member_ `TWeakPtr<FRigVMFindResult> Parent;` — If it exists it is the blueprint
- L77 _public member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakBlueprint;` — If it exists it is the blueprint
- L80 _public member_ `FText DisplayText;` — The display text for this item

#### class `FRigVMFindReferencesGraphNode`  
`class FRigVMFindReferencesGraphNode : public FRigVMFindResult`  
_L115-147_
- inherits: `FRigVMFindResult`
- desc: Graph nodes use this class to store their data
- L119 _public prototype_ `FRigVMFindReferencesGraphNode(TWeakObjectPtr<URigVMBlueprint> InBlueprint);` — `UE_DEPRECATED(5.7, "Please use FRigVMFindReferencesGraphNode(FRigVMEditorAssetInterfacePtr InBlueprint)")`
- L120 _public prototype_ `FRigVMFindReferencesGraphNode(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L121 _public prototype_ `virtual ~FRigVMFindReferencesGraphNode() = default;`
- L124 _public prototype_ `virtual FReply OnClick() override;` — FRigVMFindResult Interface
- L125 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L126 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L127 _public prototype_ `virtual void FinalizeSearchData() override;`
- L128 _public prototype_ `virtual UObject* GetObject(FRigVMEditorAssetInterfacePtr InBlueprint) const override;`
- L129 _public prototype_ `virtual FText GetCategory() const override;`
- L134 _private member_ `FGuid NodeGuid;` — The Node Guid to find when jumping to the node
- L137 _private member_ `FSlateIcon Glyph;` — The glyph brush for this node
- L140 _private member_ `FLinearColor GlyphColor;` — The glyph color for this node
- L143 _private member_ `UClass* Class;` — The class this item refers to
- L146 _private member_ `FString ClassName;` — The class name this item refers to

#### class `FRigVMFindReferencesPin`  
`class FRigVMFindReferencesPin : public FRigVMFindResult`  
_L150-174_
- inherits: `FRigVMFindResult`
- desc: Pins use this class to store their data
- L154 _public prototype_ `FRigVMFindReferencesPin(TWeakObjectPtr<URigVMBlueprint> InBlueprint, FString InSchemaName);` — `UE_DEPRECATED(5.7, "Plase use FRigVMFindReferencesPin(FRigVMEditorAssetInterfacePtr InBlueprint, FString InSchemaName)")`
- L155 _public prototype_ `FRigVMFindReferencesPin(FRigVMEditorAssetInterfacePtr InBlueprint, FString InSchemaName);`
- L156 _public prototype_ `virtual ~FRigVMFindReferencesPin() = default;`
- L159 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;` — FRigVMFindResult Interface
- L160 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L161 _public prototype_ `virtual FText GetCategory() const override;`
- L162 _public prototype_ `virtual void FinalizeSearchData() override;`
- L167 _private member_ `FString SchemaName;` — The name of the schema this pin exists under
- L170 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L173 _private member_ `FSlateColor IconColor;` — Pin's icon color

#### class `FRigVMFindReferencesVariable`  
`class FRigVMFindReferencesVariable : public FRigVMFindResult`  
_L177-198_
- inherits: `FRigVMFindResult`
- desc: Property data is stored here
- L181 _public prototype_ `FRigVMFindReferencesVariable(TWeakObjectPtr<URigVMBlueprint> InBlueprint);` — `UE_DEPRECATED(5.7, "Plase use FRigVMFindReferencesVariable(FRigVMEditorAssetInterfacePtr InBlueprint)")`
- L182 _public prototype_ `FRigVMFindReferencesVariable(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L183 _public prototype_ `virtual ~FRigVMFindReferencesVariable() = default;`
- L186 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;` — FRigVMFindResult Interface
- L187 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L188 _public prototype_ `virtual FText GetCategory() const override;`
- L189 _public prototype_ `virtual void FinalizeSearchData() override;`
- L194 _private member_ `FEdGraphPinType PinType;` — The pin that this search result refers to
- L197 _private member_ `FString DefaultValue;` — The default value of a property as a string

#### class `FRigVMFindReferencesGraph`  
`class FRigVMFindReferencesGraph : public FRigVMFindResult`  
_L201-219_
- inherits: `FRigVMFindResult`
- desc: Graphs, such as functions and macros, are stored here
- L205 _public prototype_ `FRigVMFindReferencesGraph(TWeakObjectPtr<URigVMBlueprint> InBlueprint, EGraphType InGraphType);` — `UE_DEPRECATED(5.7, "Please use FRigVMFindReferencesGraph(FRigVMEditorAssetInterfacePtr InBlueprint, EGraphType InGraphType)")`
- L206 _public prototype_ `FRigVMFindReferencesGraph(FRigVMEditorAssetInterfacePtr InBlueprint, EGraphType InGraphType);`
- L207 _public prototype_ `virtual ~FRigVMFindReferencesGraph() = default;`
- L210 _public prototype_ `virtual FReply OnClick() override;` — FRigVMFindResult Interface
- L211 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const override;`
- L212 _public prototype_ `virtual void ParseSearchInfo(FText InKey, FText InValue) override;`
- L213 _public prototype_ `virtual FText GetCategory() const override;`
- L218 _private member_ `EGraphType GraphType;` — The type of graph this represents

#### class `SRigVMFindReferences`  
`class SRigVMFindReferences: public SCompoundWidget`  
_L222-296_
- inherits: `SCompoundWidget`
- desc: Widget for searching for (functions/events) across all blueprints or just a single blueprint
- L225 _public function_ `SLATE_BEGIN_ARGS( SRigVMFindReferences )`
- L227 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FRigVMEditorBase> InBlueprintEditor = nullptr);`
- L232 _public prototype_ `void FocusForUse(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false);` — Focuses this widget's search box, and changes the mode as well, and optionally the search terms
- L235 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget overrides
- L240 _private prototype_ `void FindReferences(const FString& SearchTerms);` — The main function that will find references and build the tree
- L243 _private prototype_ `void RegisterCommands();` — Register any Find-in-Blueprint commands
- L246 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L249 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L252 _private prototype_ `void OnGetChildren( FRigVMFindResultPtr InItem, TArray< FRigVMFindResultPtr >& OutChildren );` — Get the children of a row
- L255 _private prototype_ `void OnTreeSelectionDoubleClicked( FRigVMFindResultPtr Item );` — Called when user double clicks on a new result
- L258 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FRigVMFindResultPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L261 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Callback to build the context menu when right clicking in the tree
- L264 _private prototype_ `void SelectAllItemsHelper(FRigVMFindResultPtr InItemToSelect);` — Helper function to select all items
- L267 _private prototype_ `void OnSelectAllAction();` — Callback when user attempts to select all items in the search results
- L270 _private prototype_ `void OnCopyAction();` — Callback when user attempts to copy their selection in the Find-in-Blueprints
- L274 _private member_ `TWeakPtr<class FRigVMEditorBase> EditorPtr;` — Pointer back to the blueprint editor that owns us
- L277 _private member_ `TSharedPtr<SRigVMFindResultTreeViewType> TreeView;` — The tree view displays the results
- L280 _private member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L283 _private member_ `TArray<FRigVMFindResultPtr> ItemsFound;` — This buffer stores the currently displayed results
- L286 _private member_ `TMap<uint32, FRigVMFindResultPtr> ElementHashToResult;` — Map relationship between element hash and its result
- L289 _private member_ `FText HighlightText;` — The string to highlight in the results
- L292 _private member_ `FString SearchValue;` — The string to search for
- L295 _private member_ `TSharedPtr< FUICommandList > CommandList;` — Commands handled by this widget

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L83 _typedef_ `typedef TSharedPtr<FRigVMFindResult> FRigVMFindResultPtr;`
- L84 _typedef_ `typedef STreeView<FRigVMFindResultPtr> SRigVMFindResultTreeViewType;`
- L87 _namespace_ `namespace RigVMFindReferencesHelpers`
- L96 _prototype_ `FString GetPinTypeAsString(const FEdGraphPinType& InPinType);` (scope `RigVMFindReferencesHelpers`) — Retrieves the pin type as a string value @param InPinType		The pin type to look at @return				The pin type as a string in format [category]'[sub-category object]'
- L106 _prototype_ `bool ParsePinType(FText InKey, FText InValue, FEdGraphPinType& InOutPinType);` (scope `RigVMFindReferencesHelpers`) — Parses a pin type from passed in key names and values @param InKey					The key name for what the data should be translated as @param InValue				Value to be be translated @param InOutPinType			Modifies the PinType based on the passed parameters, building it up over multiple calls @return						TRUE when the parsing is successful
- L111 _prototype_ `void ExpandAllChildren(FRigVMFindResultPtr InTreeNode, TSharedPtr<STreeView<FRigVMFindResultPtr>> InTreeView);` (scope `RigVMFindReferencesHelpers`) — Iterates through all the given tree node's children and tells the tree view to expand them

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMFindReferencesTabSummoner.h` (Public)


#### struct `FRigVMFindReferencesTabSummoner`  
`struct FRigVMFindReferencesTabSummoner : public FWorkflowTabFactory`  
_L17-32_
- inherits: `FWorkflowTabFactory`
- L22 _public function_ `static const FName TabID()`
- L24 _public prototype_ `FRigVMFindReferencesTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L26 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L28 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "RigVMEditor"`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMGraphDetailCustomization.h` (Public)


#### class `FRigVMFunctionArgumentReorderDragDropOp`  
`class FRigVMFunctionArgumentReorderDragDropOp : public FDecoratedDragDropOp`  
_L31-48_
- inherits: `FDecoratedDragDropOp`
- L34 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigVMFunctionArgumentReorderDragDropOp, FDecoratedDragDropOp) FRigVMFunctionArgumentReorderDragDropOp(const TWeakObjectPtr<URigVMPin>& InPinPtr);`
- L39 _public prototype_ `void Init();` — Inits the tooltip, needs to be called after constructing
- L42 _public prototype_ `void SetValidTarget(bool IsValidTarget);` — Update the drag tool tip indicating whether the current drop target is valid
- L44 _public prototype_ `const URigVMPin* GetPin() const;`
- L47 _private member_ `TWeakObjectPtr<URigVMPin> PinPtr;`

#### class `FRigVMFunctionArgumentReorderDragDropHandler`  
`class FRigVMFunctionArgumentReorderDragDropHandler : public IDetailDragDropHandler`  
_L50-76_
- inherits: `IDetailDragDropHandler`
- L53 _public function_ `FRigVMFunctionArgumentReorderDragDropHandler( const TWeakObjectPtr<URigVMPin>& InPinPtr, const TWeakObjectPtr<URigVMGraph>& InGraphPtr, const TWeakInterfacePtr<IRigVMClientHost>& InWeakRigVMClientHost ) : PinPtr(InPinPtr) , GraphPtr(InGraphPtr) , WeakRigVMClientHost(InWeakRigVMClientHost)`
- L64 _public prototype_ `virtual ~FRigVMFunctionArgumentReorderDragDropHandler() override = default;`
- L66 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;`
- L67 _public prototype_ `virtual bool AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L68 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L70 _public prototype_ `const URigVMPin* GetPin() const;`
- L73 _private member_ `TWeakObjectPtr<URigVMPin> PinPtr;`
- L74 _private member_ `TWeakObjectPtr<URigVMGraph> GraphPtr;`
- L75 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;`

#### class `FRigVMFunctionArgumentGroupLayout`  
`class FRigVMFunctionArgumentGroupLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FRigVMFunctionArgumentGroupLayout>`  
_L78-107_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FRigVMFunctionArgumentGroupLayout>`
- L81 _public prototype_ `FRigVMFunctionArgumentGroupLayout( const TWeakObjectPtr<URigVMGraph>& InGraph, const TWeakInterfacePtr<IRigVMClientHost>& InRigVMClientHost, const TWeakPtr<IRigVMEditor>& InEditor, bool bInputs);`
- L86 _public prototype_ `virtual ~FRigVMFunctionArgumentGroupLayout();`
- L90 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L91 _private function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override`
- L92 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L93 _private function_ `virtual void Tick(float DeltaTime) override`
- L94 _private function_ `virtual bool RequiresTick() const override`
- L95 _private function_ `virtual FName GetName() const override`
- L96 _private function_ `virtual bool InitiallyCollapsed() const override`
- L100 _private prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L102 _private member_ `TWeakObjectPtr<URigVMGraph> GraphPtr;`
- L103 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;`
- L104 _private member_ `TWeakPtr<IRigVMEditor> RigVMEditorPtr;`
- L105 _private member_ `bool bIsInputGroup;`
- L106 _private member_ `FSimpleDelegate OnRebuildChildren;`

#### class `FRigVMFunctionArgumentLayout`  
`class FRigVMFunctionArgumentLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FRigVMFunctionArgumentLayout>`  
_L109-189_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FRigVMFunctionArgumentLayout>`
- L113 _public function_ `FRigVMFunctionArgumentLayout( const TWeakObjectPtr<URigVMPin>& InPin, const TWeakObjectPtr<URigVMGraph>& InGraph, const TWeakInterfacePtr<IRigVMClientHost>& InRigVMClientHost, const TWeakPtr<IRigVMEditor>& InEditor) : PinPtr(InPin) , GraphPtr(InGraph) , WeakRigVMClientHost(InRigVMClientHost) , RigVMEditorPtr(InEditor) , NameValidator((const FRigVMEditorAssetInterfacePtr)nullptr, InGraph.Get(), InPin->GetFName())`
- L128 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;` — IDetailCustomNodeBuilder Interface
- L129 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L130 _private function_ `virtual void Tick(float DeltaTime) override`
- L131 _private function_ `virtual bool RequiresTick() const override`
- L132 _private function_ `virtual FName GetName() const override`
- L133 _private function_ `virtual bool InitiallyCollapsed() const override`
- L137 _private typedef_ `typedef TTuple<EPinContainerType, bool, FText, FText, const FSlateBrush*> TContainerType;`
- L140 _private prototype_ `bool ShouldPinBeReadOnly(bool bIsEditingPinType = false) const;` — Determines if this pin should not be editable
- L143 _private prototype_ `bool IsPinEditingReadOnly(bool bIsEditingPinType = false) const;` — Determines if editing the pins on the node should be read only
- L146 _private prototype_ `void OnRemoveClicked();` — Callbacks for all the functionality for modifying arguments
- L148 _private prototype_ `int32 OnGetArgumentIndex() const;`
- L149 _private prototype_ `FText OnGetArgNameText() const;`
- L150 _private prototype_ `FText OnGetArgToolTipText() const;`
- L151 _private prototype_ `void OnArgNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L153 _private prototype_ `FEdGraphPinType OnGetPinInfo() const;`
- L154 _private prototype_ `void PinInfoChanged(const FEdGraphPinType& PinType);`
- L155 _private prototype_ `void OnPrePinInfoChange(const FEdGraphPinType& PinType);`
- L157 _private prototype_ `const TArray<TSharedPtr<TContainerType>> GetContainerTypes() const;`
- L158 _private prototype_ `bool CanChangeContainerType() const;`
- L159 _private prototype_ `TSharedRef<SWidget> GetContainerTypeMenuContent();`
- L160 _private prototype_ `const FSlateBrush* GetContainerTypeIconImage() const;`
- L161 _private prototype_ `FSlateColor GetContainerTypeIconColor() const;`
- L162 _private prototype_ `void OnContainerTypeSelectionChanged(TSharedPtr<TContainerType> InContainerType);`
- L167 _private member_ `TWeakObjectPtr<URigVMPin> PinPtr;` — The argument pin that this layout reflects
- L170 _private member_ `TWeakObjectPtr<URigVMGraph> GraphPtr;` — The target graph that this argument is on
- L173 _private member_ `mutable TWeakObjectPtr<URigVMEdGraphSchema> EdGraphSchemaPtr;` — The ed graph schema that this is using
- L176 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;` — The asset host we are editing
- L179 _private member_ `TWeakPtr<IRigVMEditor> RigVMEditorPtr;` — The editor we are editing
- L182 _private member_ `TWeakPtr<SEditableTextBox> ArgumentNameWidget;` — Holds a weak pointer to the argument name widget, used for error notifications
- L185 _private member_ `FRigVMLocalVariableNameValidator NameValidator;` — The validator to check if a name for an argument is valid
- L187 _private member_ `const FSlateBrush* CachedImg_Pin_Disconnected = nullptr;`
- L188 _private member_ `const FSlateBrush* CachedImg_RefPin_Disconnected = nullptr;`

#### class `FRigVMFunctionArgumentDefaultNode`  
`class FRigVMFunctionArgumentDefaultNode : public IDetailCustomNodeBuilder, public TSharedFromThis<FRigVMFunctionArgumentDefaultNode>`  
_L191-223_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FRigVMFunctionArgumentDefaultNode>`
- L194 _public prototype_ `FRigVMFunctionArgumentDefaultNode( const TWeakObjectPtr<URigVMGraph>& InGraph, const TWeakInterfacePtr<IRigVMClientHost>& InClientHost );`
- L198 _public prototype_ `virtual ~FRigVMFunctionArgumentDefaultNode();`
- L202 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L203 _private function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override`
- L204 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L205 _private function_ `virtual void Tick(float DeltaTime) override`
- L206 _private function_ `virtual bool RequiresTick() const override`
- L207 _private function_ `virtual FName GetName() const override`
- L208 _private function_ `virtual bool InitiallyCollapsed() const override`
- L212 _private prototype_ `void OnGraphChanged(const FEdGraphEditAction& InAction);`
- L213 _private prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject, bool bFromTargetToSource);`
- L215 _private member_ `TWeakObjectPtr<URigVMGraph> GraphPtr;`
- L216 _private member_ `TWeakObjectPtr<URigVMEdGraph> EdGraphOuterPtr;`
- L217 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;`
- L218 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L219 _private member_ `TSharedPtr<SRigVMNodePreviewWidget> PreviewWidget;`
- L220 _private member_ `FDelegateHandle GraphChangedDelegateHandle;`
- L221 _private member_ `TSharedPtr<FRigVMMinimalEnvironment> MinimalEnvironment;`
- L222 _private member_ `bool bIsHandlingModifiedEvent;`

#### class `FRigVMGraphDetailCustomization`  
`class FRigVMGraphDetailCustomization : public IDetailCustomization`  
_L226-252_
- inherits: `IDetailCustomization`
- desc: Customization for editing rig vm graphs
- L230 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<IRigVMEditor> InBlueprintEditor, const UClass* InExpectedBlueprintClass);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L231 _public prototype_ `FRigVMGraphDetailCustomization(TSharedPtr<IRigVMEditor> RigVMigEditor, FRigVMEditorAssetInterfacePtr RigVMBlueprint);`
- L233 _public prototype_ `static TSharedPtr<IDetailCustomization> MakeLegacyInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor, const UClass* InExpectedBlueprintClass);`
- L234 _public prototype_ `FRigVMGraphDetailCustomization(TSharedPtr<IBlueprintEditor> RigVMigEditor, FRigVMEditorAssetInterfacePtr RigVMBlueprint);`
- L239 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L243 _private member_ `TWeakPtr<IRigVMEditor> RigVMEditorPtr;` — The editor we are embedded in
- L246 _private member_ `TWeakObjectPtr<URigVMEdGraph> GraphPtr;` — The graph we are editing
- L249 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> RigVMBlueprintPtr;` — The blueprint we are editing
- L251 _private member_ `TSharedPtr<FRigVMGraphDetailCustomizationImpl> RigVMGraphDetailCustomizationImpl;`

#### class `FRigVMGraphDetailCustomizationImpl`  
`class FRigVMGraphDetailCustomizationImpl : public TSharedFromThis<FRigVMGraphDetailCustomizationImpl>`  
_L254-341_
- inherits: `TSharedFromThis<FRigVMGraphDetailCustomizationImpl>`
- L257 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout, URigVMGraph* Model, URigVMController* Controller, IRigVMClientHost* InRigVMClientHost, TWeakPtr<IRigVMEditor> InEditor);`
- L265 _private prototype_ `bool IsAddNewInputOutputEnabled() const;`
- L266 _private prototype_ `EVisibility GetAddNewInputOutputVisibility() const;`
- L267 _private prototype_ `FReply OnAddNewInputClicked();`
- L268 _private prototype_ `FReply OnAddNewOutputClicked();`
- L269 _private prototype_ `FText GetNodeCategory() const;`
- L270 _private prototype_ `void SetNodeCategory(const FText& InNewText, ETextCommit::Type InCommitType);`
- L271 _private prototype_ `FText GetNodeKeywords() const;`
- L272 _private prototype_ `void SetNodeKeywords(const FText& InNewText, ETextCommit::Type InCommitType);`
- L273 _private prototype_ `FText GetNodeDescription() const;`
- L274 _private prototype_ `void SetNodeDescription(const FText& InNewText, ETextCommit::Type InCommitType);`
- L275 _private prototype_ `FLinearColor GetNodeColor() const;`
- L276 _private prototype_ `void SetNodeColor(FLinearColor InColor, bool bSetupUndoRedo);`
- L277 _private prototype_ `void OnNodeColorBegin();`
- L278 _private prototype_ `void OnNodeColorEnd();`
- L279 _private prototype_ `void OnNodeColorCancelled(FLinearColor OriginalColor);`
- L280 _private prototype_ `FReply OnNodeColorClicked();`
- L281 _private prototype_ `FText GetCurrentAccessSpecifierName() const;`
- L282 _private prototype_ `void OnAccessSpecifierSelected( TSharedPtr<FRigVMStringWithTag> SpecifierName, ESelectInfo::Type SelectInfo );`
- L283 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRowAccessSpecifier( TSharedPtr<FRigVMStringWithTag> SpecifierName, const TSharedRef<STableViewBase>& OwnerTable );`
- L284 _private prototype_ `ECheckBoxState GetFunctionPureCheckState() const;`
- L285 _private prototype_ `void OnFunctionPureCheckStateChanged(ECheckBoxState NewState);`
- L286 _private prototype_ `bool IsValidFunction() const;`
- L287 _private prototype_ `FRigVMVariant GetVariant() const;`
- L288 _private prototype_ `FRigVMVariantRef GetSubjectVariantRef() const;`
- L289 _private prototype_ `TArray<FRigVMVariantRef> GetVariantRefs() const;`
- L293 _private prototype_ `void OnVariantChanged(const FRigVMVariant& InVariant);`
- L294 _private prototype_ `void OnBrowseVariantRef(const FRigVMVariantRef& InVariantRef);`
- L295 _private prototype_ `TArray<FRigVMTag> OnGetAssignedTags() const;`
- L296 _private prototype_ `void OnAddAssignedTag(const FName& InTagName);`
- L297 _private prototype_ `void OnRemoveAssignedTag(const FName& InTagName);`
- L299 _private prototype_ `URigVMLibraryNode* GetLibraryNode() const;`
- L300 _private prototype_ `URigVMNode* GetNodeForLayout() const;`
- L301 _private prototype_ `const FRigVMNodeLayout* GetNodeLayout() const;`
- L302 _private prototype_ `TArray<FString> GetUncategorizedPins() const;`
- L303 _private prototype_ `TArray<FRigVMPinCategory> GetPinCategories() const;`
- L304 _private prototype_ `FString GetPinCategory(FString InPinPath) const;`
- L305 _private prototype_ `int32 GetPinIndexInCategory(FString InPinPath) const;`
- L306 _private prototype_ `FString GetPinLabel(FString InPinPath) const;`
- L307 _private prototype_ `FLinearColor GetPinColor(FString InPinPath) const;`
- L308 _private prototype_ `const FSlateBrush* GetPinIcon(FString InPinPath) const;`
- L309 _private prototype_ `void HandleCategoryAdded(FString InCategory);`
- L310 _private prototype_ `void HandleCategoryRemoved(FString InCategory);`
- L311 _private prototype_ `void HandleCategoryRenamed(FString InOldCategory, FString InNewCategory);`
- L312 _private prototype_ `void HandlePinCategoryChanged(FString InPinPath, FString InCategory);`
- L313 _private prototype_ `void HandlePinLabelChanged(FString InPinPath, FString InNewLabel);`
- L314 _private prototype_ `void HandlePinIndexInCategoryChanged(FString InPinPath, int32 InIndexInCategory);`
- L315 _private prototype_ `static bool ValidateName(FString InNewName, FText& OutErrorMessage);`
- L316 _private prototype_ `bool HandleValidateCategoryName(FString InCategoryPath, FString InNewName, FText& OutErrorMessage);`
- L317 _private prototype_ `bool HandleValidatePinDisplayName(FString InPinPath, FString InNewName, FText& OutErrorMessage);`
- L319 _private prototype_ `uint32 GetNodeLayoutHash() const;`
- L322 _private member_ `TWeakObjectPtr<URigVMGraph> WeakModel;` — The graph we are editing
- L325 _private member_ `TWeakObjectPtr<URigVMController> WeakController;` — The graph controller we are editing
- L328 _private member_ `TWeakPtr<IRigVMEditor> RigVMEditorPtr;` — The editor we are embedded in
- L331 _private member_ `TWeakInterfacePtr<IRigVMClientHost> RigVMClientHost;` — The asset host we are editing
- L334 _private member_ `TSharedPtr<SColorBlock> ColorBlock;` — The color block widget
- L337 _private member_ `bool bIsPickingColor;` — Set to true if the UI is currently picking a color
- L339 _private member_ `static TArray<TSharedPtr<FRigVMStringWithTag>> AccessSpecifierStrings;`
- L340 _private member_ `mutable TOptional<FRigVMNodeLayout> CachedNodeLayout;`

#### class `FRigVMWrappedNodeDetailCustomization`  
`class FRigVMWrappedNodeDetailCustomization : public IDetailCustomization`  
_L344-368_
- inherits: `IDetailCustomization`
- desc: Customization for editing a rig vm node
- L348 _public prototype_ `FRigVMWrappedNodeDetailCustomization();`
- L351 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L354 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L356 _public prototype_ `TSharedRef<SWidget> MakeNameListItemWidget(TSharedPtr<FRigVMStringWithTag> InItem);`
- L357 _public prototype_ `FText GetNameListText(const FNameProperty* InProperty) const;`
- L358 _public prototype_ `TSharedPtr<FRigVMStringWithTag> GetCurrentlySelectedItem(const FNameProperty* InProperty, const TArray<TSharedPtr<FRigVMStringWithTag>>* InNameList) const;`
- L359 _public prototype_ `void SetNameListText(const FText& NewTypeInValue, ETextCommit::Type, const FNameProperty* InProperty, TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L360 _public prototype_ `void OnNameListChanged(TSharedPtr<FRigVMStringWithTag> NewSelection, ESelectInfo::Type SelectInfo, const FNameProperty* InProperty, TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L361 _public prototype_ `void OnNameListComboBox(const FNameProperty* InProperty, const TArray<TSharedPtr<FRigVMStringWithTag>>* InNameList);`
- L362 _public prototype_ `void CustomizeLiveValues(IDetailLayoutBuilder& DetailLayout);`
- L364 _public member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized;`
- L365 _public member_ `TArray<TWeakObjectPtr<URigVMDetailsViewWrapperObject>> ObjectsBeingCustomized;`
- L366 _public member_ `TArray<TWeakObjectPtr<URigVMNode>> NodesBeingCustomized;`
- L367 _public member_ `TMap<FName, TSharedPtr<SRigVMGraphPinNameListValueWidget>> NameListWidgets;`

#### class `FRigVMGraphEnumDetailCustomization`  
`class FRigVMGraphEnumDetailCustomization : public IPropertyTypeCustomization`  
_L371-497_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for editing a rig vm integer control enum class
- L375 _public prototype_ `FRigVMGraphEnumDetailCustomization();`
- L377 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L383 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L384 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L388 _protected function_ `TArray<uint8*> GetMemoryBeingCustomized()`
- L412 _protected function_ `bool GetPropertyChain(TSharedRef<class IPropertyHandle> InPropertyHandle, FEditPropertyChain& OutPropertyChain, TArray<int32> &OutPropertyArrayIndices, bool& bOutEnabled)`
- L447 _protected function_ `static UEnum** ContainerMemoryBlockToEnumPtr(uint8* InMemoryBlock, FEditPropertyChain& InPropertyChain, TArray<int32> &InPropertyArrayIndices)` — extracts the value for a nested property from an outer owner
- L491 _protected prototype_ `void HandleControlEnumChanged(TSharedPtr<FString> InEnumPath, ESelectInfo::Type InSelectType, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L493 _protected member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized;`
- L494 _protected member_ `URigVMGraph* GraphBeingCustomized;`
- L495 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L496 _protected member_ `TArray<TSharedPtr<FStructOnScope>> StructsBeingCustomized;`

#### class `FRigVMGraphMathTypeDetailCustomization`  
`class FRigVMGraphMathTypeDetailCustomization : public IPropertyTypeCustomization`  
_L500-756_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for editing a rig vm node
- L504 _public prototype_ `FRigVMGraphMathTypeDetailCustomization();`
- L506 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L512 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L513 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L517 _protected function_ `bool GetPropertyChain(TSharedRef<class IPropertyHandle> InPropertyHandle, FEditPropertyChain& OutPropertyChain, TArray<int32> &OutPropertyArrayIndices, bool& bOutEnabled)`
- L550 _protected function_ `template<typename ValueType> static ValueType& ContainerMemoryBlockToValueRef(uint8* InMemoryBlock, ValueType& InDefault, FEditPropertyChain& InPropertyChain, TArray<int32> &InPropertyArrayIndices)` — extracts the value for a nested property (for Example Settings.WorldTransform) from an outer owner
- L596 _protected function_ `template<typename ValueType> static bool IsQuaternionBasedRotation()` — specializations for FEulerTransform and FRotator at the end of this file
- L600 _protected function_ `template<typename VectorType, typename NumericType> TOptional<NumericType> GetVectorComponent(TSharedRef<class IPropertyHandle> InPropertyHandle, int32 InComponent)` — returns the numeric value of a vector component (or empty optional for varying values)
- L628 _protected function_ `template<typename VectorType, typename NumericType> void OnVectorComponentChanged(TSharedRef<class IPropertyHandle> InPropertyHandle, int32 InComponent, NumericType InValue, bool bIsCommit, ETextCommit::Type InCommitType = ETextCommit::Default)` — called when a numeric value of a vector component is changed
- L656 _protected function_ `template<typename VectorType> void ExtendVectorArgs(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)` — specializations for FVector and FVector4 at the end of this file
- L659 _protected prototype_ `template<typename VectorType, int32 NumberOfComponents> void MakeVectorHeaderRow(TSharedRef<class IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils);`
- L662 _protected prototype_ `template<typename RotationType> void MakeRotationHeaderRow(TSharedRef<class IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils);`
- L665 _protected prototype_ `template<typename TransformType> void ConfigureTransformWidgetArgs(TSharedRef<class IPropertyHandle> InPropertyHandle, typename SAdvancedTransformInputBox<TransformType>::FArguments& WidgetArgs, TConstArrayView<FName> ComponentNames);`
- L668 _protected prototype_ `template<typename TransformType> void MakeTransformHeaderRow(TSharedRef<class IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils, TConstArrayView<FName> ComponentNames);`
- L671 _protected prototype_ `template<typename TransformType> void MakeTransformChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils, TConstArrayView<FName> ComponentNames);`
- L675 _protected function_ `template<typename RotationType> TOptional<RotationType> GetRotation(TSharedRef<class IPropertyHandle> InPropertyHandle)` — returns the rotation for rotator or quaternions (or empty optional for varying values)
- L700 _protected function_ `template<typename RotationType> void OnRotationChanged(TSharedRef<class IPropertyHandle> InPropertyHandle, RotationType InValue, bool bIsCommit, ETextCommit::Type InCommitType = ETextCommit::Default)` — called when a rotation value is changed / committed
- L734 _protected function_ `template<typename RotationType> void ExtendRotationArgs(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)` — specializations for FRotator and FQuat at the end of this file
- L737 _protected function_ `template<typename TransformType> static FName GetTranslationPropertyName()`
- L743 _protected function_ `template<typename TransformType> static FName GetRotationPropertyName()`
- L749 _protected function_ `template<typename TransformType> static FName GetScalePropertyName()`
- L754 _protected member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> BlueprintBeingCustomized;`
- L755 _protected member_ `TWeakObjectPtr<URigVMGraph> GraphBeingCustomized;`
- L759 _function_ `template<> inline bool FRigVMGraphMathTypeDetailCustomization::IsQuaternionBasedRotation<FEulerTransform>()`
- L762 _function_ `template<> inline bool FRigVMGraphMathTypeDetailCustomization::IsQuaternionBasedRotation<FRotator>()`
- L765 _function_ `template<> inline void FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs<FVector>(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)`
- L788 _function_ `template<> inline void FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs<FVector4>(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)`
- L823 _function_ `template<> inline void FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs<FQuat>(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)`
- L847 _function_ `template<> inline void FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs<FRotator>(TSharedRef<class IPropertyHandle> InPropertyHandle, void* ArgumentsPtr)`
- L871 _function_ `template<> inline FName FRigVMGraphMathTypeDetailCustomization::GetTranslationPropertyName<FEulerTransform>()`
- L877 _function_ `template<> inline FName FRigVMGraphMathTypeDetailCustomization::GetScalePropertyName<FEulerTransform>()`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API RIGVMEDITOR_API`
- L767 _typedef_ `using VectorType = FVector;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L768 _typedef_ `typedef typename VectorType::FReal NumericType;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L769 _typedef_ `typedef SNumericVectorInputBox<NumericType, VectorType, 3> SLocalVectorInputBox;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L774 _function_ `` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L790 _typedef_ `using VectorType = FVector4;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L792 _typedef_ `typedef SNumericVectorInputBox<NumericType, VectorType, 4> SLocalVectorInputBox;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendVectorArgs`)
- L825 _typedef_ `using RotationType = FQuat;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs`)
- L826 _typedef_ `typedef typename RotationType::FReal NumericType;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs`)
- L827 _typedef_ `typedef SAdvancedRotationInputBox<NumericType> SLocalRotationInputBox;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs`)
- L831 _function_ `` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs`)
- L849 _typedef_ `using RotationType = FRotator;` (scope `FRigVMGraphMathTypeDetailCustomization::ExtendRotationArgs`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMGraphEditorTabSummoner.h` (Public)


#### struct `FRigVMLocalKismetCallbacks`  
`struct FRigVMLocalKismetCallbacks`  
_L17-20_
- L19 _public prototype_ `static FText GetGraphDisplayName(const UEdGraph* Graph);`

#### struct `FRigVMGraphEditorTabSummoner`  
`struct FRigVMGraphEditorTabSummoner : public FDocumentTabFactoryForObjects<UEdGraph>`  
_L22-50_
- inherits: `FDocumentTabFactoryForObjects<UEdGraph>`
- L24 _public function_ `static const FName TabID()`
- L27 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`
- L29 _public prototype_ `FRigVMGraphEditorTabSummoner(const TSharedRef<FRigVMNewEditor>& InRigVMEditor, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L31 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L33 _public prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> Tab) const override;`
- L35 _public prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L38 _protected function_ `virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override`
- L43 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L45 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L48 _protected member_ `TWeakPtr<class FRigVMNewEditor> BlueprintEditorPtr;`
- L49 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`
- L10 _macro_ `#define LOCTEXT_NAMESPACE "RigVMGraphEditorTabSummoner"`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UEdGraph*);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMLegacyEditor.h` (Public)


#### class `FRigVMLegacyEditor`  
`class FRigVMLegacyEditor : public FBlueprintEditor, public FRigVMEditorBase`  
_L21-211_
- inherits: `FBlueprintEditor,FRigVMEditorBase`
- L25 _public prototype_ `FRigVMLegacyEditor();`
- L27 _public function_ `virtual TSharedRef<IRigVMEditor> SharedRef() override`
- L28 _public function_ `virtual TSharedRef<const IRigVMEditor> SharedRef() const override`
- L33 _protected function_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() override` — IRigVMEditor overrides
- L34 _protected function_ `virtual const TSharedPtr<FAssetEditorToolkit> GetHostingApp() const override`
- L35 _protected prototype_ `virtual void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const FName AppIdentifier, const TSharedRef<FTabManager::FLayout>& StandaloneDefaultLayout, const bool bCreateDefaultStandaloneMenu, const bool bCreateDefaultToolbar, const TArray<UObject*>& ObjectsToEdit, const bool bInIsToolbarFocusable, const bool bInUseSmallToolbarIcons, const TOptional<EAssetOpenMethod>& InOpenMethod) override;`
- L36 _protected prototype_ `virtual void CreateEditorToolbar() override;`
- L37 _protected prototype_ `virtual void CommonInitialization(const TArray<FRigVMEditorAssetInterfacePtr>& InitBlueprints, bool bShouldOpenInDefaultsMode) override;`
- L38 _protected function_ `virtual TSharedPtr<FDocumentTracker> GetDocumentManager() const override`
- L39 _protected function_ `virtual void AddApplicationMode(FName ModeName, TSharedRef<FApplicationMode> Mode) override`
- L40 _protected function_ `virtual void RegenerateMenusAndToolbars() override`
- L41 _protected function_ `virtual void SetCurrentMode(FName NewMode) override`
- L42 _protected function_ `virtual FEditorModeTools& GetToolkitEditorModeManager() const override`
- L43 _protected function_ `virtual void PostLayoutBlueprintEditorInitialization() override`
- L44 _protected function_ `virtual TSharedPtr<SGraphEditor> OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus) override`
- L45 _protected function_ `virtual bool FindOpenTabsContainingDocument(const UObject* DocumentID, TArray<TSharedPtr<SDockTab>>& Results) override`
- L46 _protected function_ `virtual TSharedPtr<SDockTab> OpenDocument(const UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause) override`
- L47 _protected function_ `virtual void CloseDocumentTab(const UObject* DocumentID) override`
- L48 _protected function_ `virtual TSharedPtr<FTabManager> GetTabManager() override`
- L50 _protected function_ `virtual TSharedPtr<SKismetInspector> GetKismetInspector() const override`
- L52 _protected function_ `virtual TSharedPtr<SRigVMDetailsInspector> GetRigVMInspector() const override`
- L53 _protected prototype_ `virtual TSharedPtr<FApplicationMode> CreateEditorMode() override;`
- L54 _protected prototype_ `virtual const FName GetEditorAppName() const override;`
- L55 _protected function_ `virtual const TArray< UObject* >& GetEditingBlueprints() const override`
- L56 _protected prototype_ `virtual void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor) override;`
- L57 _protected function_ `virtual const TSharedRef<IToolkitHost> GetToolkitHost() const override`
- L58 _protected function_ `virtual bool IsHosted() const override`
- L59 _protected function_ `virtual void BringToolkitToFrontImpl() override`
- L60 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L61 _protected function_ `virtual TWeakPtr<SGraphEditor> GetFocusedGraphEditor() override`
- L62 _protected function_ `virtual TWeakPtr<FDocumentTabFactory> GetGraphEditorTabFactory() const override`
- L63 _protected prototype_ `virtual bool TransactionObjectAffectsBlueprint(UObject* InTransactedObject) override;`
- L64 _protected prototype_ `virtual FEdGraphPinType GetLastPinTypeUsed() override;`
- L65 _protected function_ `virtual void LogSimpleMessage(const FText& MessageText) override`
- L66 _protected function_ `virtual void RenameNewlyAddedAction(FName InActionName) override`
- L67 _protected function_ `virtual FGraphPanelSelectionSet GetSelectedNodes() const override`
- L68 _protected function_ `virtual void SetUISelectionState(FName SelectionOwner) override`
- L69 _protected function_ `virtual void AnalyticsTrackNodeEvent(UBlueprint* Blueprint, UEdGraphNode* GraphNode, bool bNodeDelete) const override`
- L70 _protected function_ `virtual void AnalyticsTrackNodeEvent(IRigVMEditorAssetInterface* Blueprint, UEdGraphNode* GraphNode, bool bNodeDelete) const override`
- L71 _protected prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename) override;`
- L72 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L73 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L74 _protected function_ `virtual UEdGraphPin* GetCurrentlySelectedPin() const override`
- L75 _protected prototype_ `virtual void CreateDefaultCommands() override;`
- L76 _protected prototype_ `virtual TSharedRef<SGraphEditor> CreateGraphEditorWidget(TSharedRef<FTabInfo> InTabInfo, UEdGraph* InGraph) override;`
- L77 _protected function_ `virtual void CompileImpl() override`
- L78 _protected function_ `virtual void SaveAsset_Execute_Impl() override`
- L79 _protected function_ `virtual void SaveAssetAs_Execute_Impl() override`
- L80 _protected function_ `virtual bool IsGraphInCurrentBlueprint(const UEdGraph* InGraph) const override`
- L81 _protected function_ `virtual bool IsEditableImpl(UEdGraph* InGraph) const override`
- L82 _protected function_ `virtual UEdGraph* GetFocusedGraph() const override`
- L83 _protected function_ `virtual void JumpToNode(const UEdGraphNode* Node, bool bRequestRename) override`
- L84 _protected function_ `virtual void JumpToPin(const UEdGraphPin* Pin) override`
- L85 _protected function_ `virtual void AddToolbarExtender(TSharedPtr<FExtender> Extender) override`
- L86 _protected function_ `virtual void RemoveToolbarExtender(TSharedPtr<FExtender> Extender) override`
- L87 _protected function_ `virtual void AddMenuExtender(TSharedPtr<FExtender> Extender) override`
- L88 _protected function_ `virtual void RemoveMenuExtender(TSharedPtr<FExtender> Extender) override`
- L89 _protected function_ `virtual TSharedPtr<IMessageLogListing> GetCompilerResultsListing() override`
- L90 _protected function_ `virtual void OnBlueprintChangedInnerImpl(IRigVMEditorAssetInterface* InBlueprint, bool bIsJustBeingCompiled) override`
- L91 _protected prototype_ `virtual void RefreshEditorsImpl(ERefreshRigVMEditorReason::Type Reason) override;`
- L92 _protected function_ `virtual void SetupGraphEditorEvents(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents) override`
- L93 _protected function_ `virtual void SetupGraphEditorEventsImpl(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents) override`
- L94 _protected function_ `virtual FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed) override`
- L95 _protected function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L96 _protected function_ `virtual void AddReferencedObjectsImpl(FReferenceCollector& Collector) override`
- L97 _protected prototype_ `virtual bool NewDocument_IsVisibleForType(FBlueprintEditor::ECreatedDocumentType GraphType) const override;`
- L98 _protected prototype_ `virtual bool IsSectionVisible(NodeSectionID::Type InSectionID) const override;`
- L99 _protected function_ `virtual FGraphAppearanceInfo GetGraphAppearanceImpl(UEdGraph* InGraph) const override`
- L100 _protected function_ `virtual void NotifyPreChangeImpl(FProperty* PropertyAboutToChange) override`
- L101 _protected function_ `virtual void NotifyPostChangeImpl(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override`
- L102 _protected prototype_ `virtual FName GetSelectedVariableName() override;`
- L103 _protected function_ `virtual bool IsNodeTitleVisible(const UEdGraphNode* Node, bool bRequestRename) override`
- L104 _protected function_ `virtual void EditClassDefaults_Clicked() override`
- L105 _protected function_ `virtual void EditGlobalOptions_Clicked() override`
- L106 _protected function_ `virtual bool IsDetailsPanelEditingClassDefaults() const override`
- L107 _protected function_ `virtual bool IsDetailsPanelEditingGlobalOptions() const override`
- L108 _protected function_ `virtual void TryInvokingDetailsTab(bool bFlash) override`
- L109 _protected function_ `virtual FName GetGraphExplorerWidgetID() override`
- L110 _protected function_ `virtual void RefreshInspector() override`
- L111 _protected function_ `virtual void RefreshStandAloneDefaultsEditor() override`
- L112 _protected function_ `virtual void GetPinTypeSelectorFilters(TArray<TSharedPtr<IPinTypeSelectorFilter>>& OutFilters) const override`
- L113 _protected function_ `virtual void OnAddNewVariable() override`
- L114 _protected function_ `virtual void ZoomToSelection_Clicked() override`
- L115 _protected function_ `virtual void RestoreEditedObjectState() override`
- L116 _protected function_ `virtual void SetupViewForBlueprintEditingMode() override`
- L117 _protected function_ `virtual bool GetIsContextSensitive() override`
- L118 _protected function_ `virtual void SetIsContextSensitive(const bool bIsContextSensitive) override`
- L119 _protected function_ `virtual void RegisterToolbarTab(const TSharedRef<FTabManager>& InTabManager) override`
- L120 _protected function_ `virtual const TArray<UObject*>* GetObjectsCurrentlyBeingEdited() const override`
- L121 _protected prototype_ `virtual void AddCompileWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L122 _protected function_ `virtual void AddSettingsAndDefaultWidget(FToolBarBuilder& ToolbarBuilder) override`
- L123 _protected function_ `virtual void AddFindWidget(FToolBarBuilder& ToolbarBuilder) override`
- L124 _protected prototype_ `virtual void AddSelectedDebugObjectWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L125 _protected prototype_ `virtual void AddAutoCompileWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L126 _protected function_ `virtual FString GetCustomDebugObjectLabel(UObject* ObjectBeingDebugged) const override`
- L128 _public function_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms, bool bSelectFirstResult) override`
- L129 _public function_ `virtual TSharedRef<FUICommandList> GetToolkitCommands() override`
- L130 _public prototype_ `virtual void OnClose() override;`
- L131 _public function_ `virtual FPreviewScene* GetPreviewScene() override`
- L133 _public function_ `virtual void ToggleHideUnrelatedNodes() override`
- L138 _public function_ `virtual bool IsToggleHideUnrelatedNodesChecked() const override`
- L144 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L149 _protected function_ `virtual UBlueprint* GetBlueprintObj() const override` — FBlueprintEditor overrides
- L150 _protected function_ `virtual TSubclassOf<UEdGraphSchema> GetDefaultSchemaClass() const override`
- L151 _protected function_ `virtual bool InEditingMode() const override`
- L152 _protected function_ `virtual bool CanAddNewLocalVariable() const override`
- L153 _protected function_ `virtual void OnAddNewLocalVariable() override`
- L154 _protected function_ `virtual void OnPasteNewLocalVariable(const FBPVariableDescription& VariableDescription) override`
- L155 _protected function_ `virtual void DeleteSelectedNodes() override`
- L156 _protected function_ `virtual bool CanDeleteNodes() const override`
- L157 _protected function_ `virtual void CopySelectedNodes() override`
- L158 _protected function_ `virtual bool CanCopyNodes() const override`
- L159 _protected function_ `virtual void PasteNodes() override`
- L160 _protected function_ `virtual bool CanPasteNodes() const override`
- L161 _protected function_ `virtual bool IsNativeParentClassCodeLinkEnabled() const override`
- L162 _protected function_ `virtual bool ReparentBlueprint_IsVisible() const override`
- L163 _protected function_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) override`
- L164 _protected function_ `virtual bool ShouldLoadBPLibrariesFromAssetRegistry() override`
- L165 _protected function_ `virtual bool ShouldOpenGraphByDefault() const`
- L166 _protected function_ `virtual void AddNewFunctionVariant(const UEdGraph* InOriginalFunction) override`
- L167 _protected function_ `virtual bool SelectLocalVariable(const UEdGraph* Graph, const FName& VariableName) override`
- L168 _protected function_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList)`
- L169 _protected function_ `virtual void Compile() override`
- L170 _protected function_ `virtual void SaveAsset_Execute() override`
- L171 _protected function_ `virtual void SaveAssetAs_Execute() override`
- L172 _protected function_ `virtual bool IsInAScriptingMode() const override`
- L173 _protected function_ `virtual void NewDocument_OnClicked(FBlueprintEditor::ECreatedDocumentType GraphType) override`
- L174 _protected function_ `virtual bool AreEventGraphsAllowed() const override`
- L175 _protected function_ `virtual bool AreMacrosAllowed() const override`
- L176 _protected function_ `virtual bool AreDelegatesAllowed() const override`
- L177 _protected function_ `virtual FGraphAppearanceInfo GetGraphAppearance(class UEdGraph* InGraph) const override`
- L178 _protected function_ `virtual bool IsEditable(UEdGraph* InGraph) const override`
- L179 _protected function_ `virtual bool IsCompilingEnabled() const override`
- L180 _protected function_ `virtual FText GetGraphDecorationString(UEdGraph* InGraph) const override`
- L181 _protected function_ `virtual void OnActiveTabChanged( TSharedPtr<SDockTab> PreviouslyActive, TSharedPtr<SDockTab> NewlyActivated ) override`
- L182 _protected function_ `virtual void OnSelectedNodesChangedImpl(const TSet<class UObject*>& NewSelection) override`
- L183 _protected function_ `virtual void OnBlueprintChangedImpl(UBlueprint* InBlueprint, bool bIsJustBeingCompiled) override`
- L184 _protected function_ `virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type Reason = ERefreshBlueprintEditorReason::UnknownReason) override`
- L185 _protected function_ `virtual void FocusInspectorOnGraphSelection(const TSet<class UObject*>& NewSelection, bool bForceRefresh = false) override`
- L186 _protected function_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override`
- L187 _protected function_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override`
- L188 _protected function_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L189 _protected function_ `virtual TStatId GetStatId() const override`
- L190 _protected function_ `virtual FName GetToolkitFName() const override`
- L191 _protected function_ `virtual FName GetToolkitContextFName() const override`
- L192 _protected function_ `virtual FText GetBaseToolkitName() const override`
- L193 _protected function_ `virtual FText GetToolkitToolTipText() const override`
- L194 _protected function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L195 _protected function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L196 _protected function_ `virtual void OnStartWatchingPin() override`
- L197 _protected function_ `virtual bool CanStartWatchingPin() const override`
- L198 _protected function_ `virtual void OnStopWatchingPin() override`
- L199 _protected function_ `virtual bool CanStopWatchingPin() const override`
- L200 _protected function_ `virtual void OnCreateComment() override`
- L201 _protected prototype_ `virtual void GetCustomDebugObjects(TArray<FCustomDebugObject>& DebugList) const override;`
- L202 _protected function_ `virtual bool OnlyShowCustomDebugObjects() const override`
- L203 _protected function_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject) override`
- L204 _protected function_ `virtual bool OnActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const override`
- L207 _protected function_ `virtual void BringToolkitToFront() override` — IToolkit Interface
- L209 _protected function_ `virtual FNotifyHook* GetNotifyHook() override`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMLegacyEditorMode.h` (Public)


#### class `FRigVMLegacyEditorMode`  
`class FRigVMLegacyEditorMode : public FBlueprintEditorApplicationMode`  
_L15-29_
- inherits: `FBlueprintEditorApplicationMode`
- L18 _public prototype_ `FRigVMLegacyEditorMode(const TSharedRef<FRigVMLegacyEditor>& InRigVMEditor);`
- L21 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L25 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs
- L28 _private member_ `TWeakObjectPtr<URigVMBlueprint> RigVMBlueprintPtr;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMLocalVariableDetailCustomization.h` (Public)


#### class `FRigVMLocalVariableDetailCustomization`  
`class FRigVMLocalVariableDetailCustomization : public IDetailCustomization`  
_L22-67_
- inherits: `IDetailCustomization`
- L24 _private function_ `FRigVMLocalVariableDetailCustomization() : GraphBeingCustomized(nullptr) , BlueprintBeingCustomized(nullptr) , NameValidator((const FRigVMEditorAssetInterfacePtr)nullptr, nullptr, NAME_None)`
- L34 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L40 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L44 _private member_ `URigVMGraph* GraphBeingCustomized;`
- L45 _private member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized;`
- L46 _private member_ `FRigVMGraphVariableDescription VariableDescription;`
- L47 _private member_ `TArray<TWeakObjectPtr<URigVMDetailsViewWrapperObject>> ObjectsBeingCustomized;`
- L49 _private member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> TypeHandle;`
- L51 _private member_ `TSharedPtr<IPropertyHandle> TypeObjectHandle;`
- L52 _private member_ `TSharedPtr<IPropertyHandle> DefaultValueHandle;`
- L53 _private member_ `TSharedPtr<FRigVMMemoryStorageStruct> MemoryStorage;`
- L55 _private member_ `FRigVMLocalVariableNameValidator NameValidator;`
- L56 _private member_ `TArray<TSharedPtr<FString>> EnumOptions;`
- L58 _private prototype_ `FText GetName() const;`
- L59 _private prototype_ `void SetName(const FText& InNewText, ETextCommit::Type InCommitType);`
- L60 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L62 _private prototype_ `FEdGraphPinType OnGetPinInfo() const;`
- L63 _private prototype_ `void HandlePinInfoChanged(const FEdGraphPinType& PinType);`
- L65 _private prototype_ `ECheckBoxState HandleBoolDefaultValueIsChecked( ) const;`
- L66 _private prototype_ `void OnBoolDefaultValueChanged(ECheckBoxState InCheckBoxState);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMMinimalEnvironment.h` (Public)


#### class `FRigVMMinimalEnvironment`  
`class FRigVMMinimalEnvironment : public TSharedFromThis<FRigVMMinimalEnvironment>`  
_L15-54_
- inherits: `TSharedFromThis<FRigVMMinimalEnvironment>`
- L18 _public prototype_ `FRigVMMinimalEnvironment(const IRigVMAssetInterface* InAssetInterface = nullptr);`
- L19 _public prototype_ `FRigVMMinimalEnvironment(IRigVMClientHost* InRigVMClientHost, UObject* InAssetObject);`
- L21 _public prototype_ `URigVMGraph* GetModel() const;`
- L22 _public prototype_ `URigVMController* GetController() const;`
- L23 _public prototype_ `URigVMNode* GetNode() const;`
- L24 _public prototype_ `URigVMEdGraph* GetEdGraph() const;`
- L25 _public prototype_ `URigVMEdGraphNode* GetEdGraphNode() const;`
- L27 _public prototype_ `void SetSchemata(const IRigVMAssetInterface* InAssetInterface);`
- L28 _public prototype_ `void SetSchemata(const IRigVMClientHost* InRigVMClientHost, const UObject* InAssetObject);`
- L29 _public prototype_ `void SetNode(URigVMNode* InModelNode);`
- L30 _public prototype_ `URigVMNode* SetFunctionReference(URigVMLibraryNode* InFunctionDefinition, const FString& InNodeName);`
- L31 _public prototype_ `URigVMNode* SetEmptyCollapseNode(URigVMCollapseNode* InSourceCollapseNode, const FString& InNodeName);`
- L32 _public prototype_ `void SetFunctionNode(const FRigVMGraphFunctionIdentifier& InIdentifier);`
- L34 _public prototype_ `FSimpleDelegate& OnChanged();`
- L35 _public prototype_ `void Tick_GameThead(float InDeltaTime);`
- L37 _public prototype_ `void SynchronizeCollapseNode(URigVMCollapseNode* InSource);`
- L40 _private prototype_ `void HandleModified(ERigVMGraphNotifType InNotification, URigVMGraph* InGraph, UObject* InSubject);`
- L41 _private prototype_ `void InitGraphData(UObject* InOuter);`
- L43 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakRigVMClientHost;`
- L44 _private member_ `TStrongObjectPtr<URigVMGraph> ModelGraph;`
- L45 _private member_ `TStrongObjectPtr<URigVMController> ModelController;`
- L46 _private member_ `UClass* EdGraphClass;`
- L47 _private member_ `UClass* EdGraphNodeClass;`
- L48 _private member_ `TStrongObjectPtr<URigVMEdGraph> EdGraph;`
- L49 _private member_ `TWeakObjectPtr<URigVMNode> ModelNode;`
- L50 _private member_ `TWeakObjectPtr<URigVMEdGraphNode> EdGraphNode;`
- L51 _private member_ `std::atomic<int32> NumModifications;`
- L52 _private member_ `FSimpleDelegate ChangedDelegate;`
- L53 _private member_ `FDelegateHandle ModelHandle;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMNewEditor.h` (Public)


#### struct `FRigVMNewEditorTabs`  
`struct FRigVMNewEditorTabs`  
_L15-19_
- L18 _public prototype_ `static const FName CompilerResultsID();` — Tab identifiers

#### class `FRigVMNewEditor`  
`class FRigVMNewEditor : public FWorkflowCentricApplication, public FRigVMEditorBase, public FGCObject, public FNotifyHook, public FTickableEditorObject, public FEditorUndoClient, public FNoncopyable`  
_L21-256_
- inherits: `FWorkflowCentricApplication,FRigVMEditorBase,FGCObject,FNotifyHook,FTickableEditorObject,FEditorUndoClient,FNoncopyable`
- L24 _public prototype_ `FRigVMNewEditor();`
- L25 _public prototype_ `virtual void OnClose() override;`
- L27 _public function_ `virtual TSharedRef<IRigVMEditor> SharedRef() override`
- L28 _public function_ `virtual TSharedRef<const IRigVMEditor> SharedRef() const override`
- L30 _public function_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() override`
- L31 _public function_ `virtual const TSharedPtr<FAssetEditorToolkit> GetHostingApp() const override`
- L34 _protected prototype_ `virtual void InitAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const FName AppIdentifier, const TSharedRef<FTabManager::FLayout>& StandaloneDefaultLayout, const bool bCreateDefaultStandaloneMenu, const bool bCreateDefaultToolbar, const TArray<UObject*>& ObjectsToEdit, const bool bInIsToolbarFocusable, const bool bInUseSmallToolbarIcons, const TOptional<EAssetOpenMethod>& InOpenMethod) override;`
- L35 _protected function_ `virtual void CreateEditorToolbar() override`
- L36 _protected prototype_ `virtual void CommonInitialization(const TArray<FRigVMEditorAssetInterfacePtr>& InitBlueprints, bool bShouldOpenInDefaultsMode) override;`
- L37 _protected prototype_ `void OnBlueprintChanged(UObject* InBlueprint);`
- L38 _protected function_ `virtual TSharedPtr<FDocumentTracker> GetDocumentManager() const override`
- L39 _protected function_ `virtual void AddApplicationMode(FName ModeName, TSharedRef<FApplicationMode> Mode) override`
- L40 _protected function_ `virtual void RegenerateMenusAndToolbars() override`
- L41 _protected prototype_ `virtual void SetCurrentMode(FName NewMode) override;`
- L42 _protected function_ `virtual FEditorModeTools& GetToolkitEditorModeManager() const override`
- L43 _protected prototype_ `virtual void PostLayoutBlueprintEditorInitialization() override;`
- L44 _protected prototype_ `virtual TSharedPtr<SGraphEditor> OpenGraphAndBringToFront(UEdGraph* Graph, bool bSetFocus = true) override;`
- L45 _protected prototype_ `virtual bool FindOpenTabsContainingDocument(const UObject* DocumentID, TArray< TSharedPtr<SDockTab> >& Results) override;`
- L46 _protected prototype_ `virtual TSharedPtr<SDockTab> OpenDocument(const UObject* DocumentID, FDocumentTracker::EOpenDocumentCause Cause) override;`
- L47 _protected prototype_ `virtual void CloseDocumentTab(const UObject* DocumentID) override;`
- L48 _protected function_ `virtual TSharedPtr<FTabManager> GetTabManager() override`
- L50 _public function_ `virtual TSharedPtr<SRigVMDetailsInspector> GetRigVMInspector() const override`
- L51 _public function_ `virtual void SetInspector(TSharedPtr<SRigVMDetailsInspector> InWidget)`
- L53 _public prototype_ `TSharedRef<SWidget> GetCompilerResults() const;`
- L54 _public function_ `TSharedRef<SRigVMFindReferences> GetFindResults() const`
- L55 _public prototype_ `virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename) override;`
- L57 _protected function_ `virtual TSharedPtr<IMessageLogListing> GetCompilerResultsListing() override`
- L58 _protected prototype_ `virtual TSharedPtr<FApplicationMode> CreateEditorMode() override;`
- L59 _protected prototype_ `virtual const FName GetEditorAppName() const override;`
- L60 _protected prototype_ `virtual FText GetToolkitName() const override;`
- L61 _protected prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L62 _protected function_ `virtual const TArray< UObject* >& GetEditingBlueprints() const override`
- L63 _protected function_ `virtual const TSharedRef<IToolkitHost> GetToolkitHost() const override`
- L64 _protected function_ `virtual bool IsHosted() const override`
- L65 _protected function_ `virtual void BringToolkitToFrontImpl() override`
- L66 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L67 _protected function_ `virtual TSharedRef<FUICommandList> GetToolkitCommands() override`
- L68 _protected function_ `virtual TWeakPtr<SGraphEditor> GetFocusedGraphEditor() override`
- L69 _protected function_ `virtual TWeakPtr<FDocumentTabFactory> GetGraphEditorTabFactory() const override`
- L70 _protected prototype_ `virtual bool TransactionObjectAffectsBlueprint(UObject* InTransactedObject) override;`
- L71 _protected prototype_ `virtual FEdGraphPinType GetLastPinTypeUsed() override;`
- L72 _protected prototype_ `virtual void LogSimpleMessage(const FText& MessageText) override;`
- L73 _protected prototype_ `virtual void RenameNewlyAddedAction(FName InActionName) override;`
- L74 _protected prototype_ `virtual FGraphPanelSelectionSet GetSelectedNodes() const override;`
- L75 _protected prototype_ `virtual void SetUISelectionState(FName SelectionOwner) override;`
- L76 _protected prototype_ `virtual void AnalyticsTrackNodeEvent(IRigVMEditorAssetInterface* Blueprint, UEdGraphNode* GraphNode, bool bNodeDelete) const override;`
- L77 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L78 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L79 _protected prototype_ `virtual UEdGraphPin* GetCurrentlySelectedPin() const override;`
- L80 _protected prototype_ `virtual void CreateDefaultCommands() override;`
- L81 _protected prototype_ `virtual TSharedRef<SGraphEditor> CreateGraphEditorWidget(TSharedRef<FTabInfo> InTabInfo, UEdGraph* InGraph) override;`
- L82 _protected prototype_ `virtual void CompileImpl() override;`
- L83 _protected function_ `virtual void SaveAsset_Execute_Impl() override`
- L84 _protected function_ `virtual void SaveAssetAs_Execute_Impl() override`
- L85 _protected prototype_ `virtual bool IsGraphInCurrentBlueprint(const UEdGraph* InGraph) const override;`
- L86 _protected prototype_ `virtual bool IsEditableImpl(UEdGraph* InGraph) const override;`
- L87 _protected prototype_ `virtual UEdGraph* GetFocusedGraph() const override;`
- L88 _protected prototype_ `virtual void JumpToNode(const UEdGraphNode* Node, bool bRequestRename) override;`
- L89 _protected prototype_ `virtual void JumpToPin(const UEdGraphPin* Pin) override;`
- L90 _protected function_ `virtual void AddToolbarExtender(TSharedPtr<FExtender> Extender) override`
- L91 _protected function_ `virtual void RemoveToolbarExtender(TSharedPtr<FExtender> Extender) override`
- L92 _protected function_ `virtual void AddMenuExtender(TSharedPtr<FExtender> Extender) override`
- L93 _protected function_ `virtual void RemoveMenuExtender(TSharedPtr<FExtender> Extender) override`
- L94 _protected prototype_ `virtual void OnBlueprintChangedInnerImpl(IRigVMEditorAssetInterface* InBlueprint, bool bIsJustBeingCompiled) override;`
- L95 _protected prototype_ `virtual void RefreshEditorsImpl(ERefreshRigVMEditorReason::Type Reason) override;`
- L96 _protected prototype_ `virtual void SetupGraphEditorEventsImpl(UEdGraph* InGraph, SGraphEditor::FGraphEditorEvents& InEvents) override;`
- L99 _protected prototype_ `void HandleGraphCanvasDoubleClicked(UEdGraph* InGraph);` — Called when the graph canvas was double clicked
- L100 _protected prototype_ `void OnClosedActionMenu(UEdGraph* InEdGraph) const;`
- L101 _protected prototype_ `virtual FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed) override;`
- L102 _protected prototype_ `virtual void AddReferencedObjectsImpl(FReferenceCollector& Collector) override;`
- L103 _protected prototype_ `virtual bool IsSectionVisible(RigVMNodeSectionID::Type InSectionID) const;`
- L104 _protected prototype_ `virtual bool NewDocument_IsVisibleForType(ECreatedDocumentType GraphType) const;`
- L105 _protected prototype_ `virtual FGraphAppearanceInfo GetGraphAppearanceImpl(UEdGraph* InGraph) const override;`
- L106 _protected prototype_ `virtual void NotifyPreChangeImpl(FProperty* PropertyAboutToChange) override;`
- L107 _protected prototype_ `virtual void NotifyPostChangeImpl(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L108 _protected prototype_ `virtual FName GetSelectedVariableName() override;`
- L109 _protected prototype_ `virtual bool IsNodeTitleVisible(const UEdGraphNode* Node, bool bRequestRename) override;`
- L110 _protected prototype_ `virtual void EditClassDefaults_Clicked() override;`
- L111 _protected prototype_ `virtual void EditGlobalOptions_Clicked() override;`
- L112 _protected prototype_ `virtual bool IsDetailsPanelEditingGlobalOptions() const override;`
- L113 _protected prototype_ `virtual bool IsDetailsPanelEditingClassDefaults() const override;`
- L114 _protected prototype_ `virtual void TryInvokingDetailsTab(bool bFlash = true) override;`
- L115 _protected function_ `virtual FName GetGraphExplorerWidgetID() override`
- L116 _protected prototype_ `virtual void RefreshInspector() override;`
- L117 _protected prototype_ `virtual void RefreshStandAloneDefaultsEditor() override;`
- L118 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L119 _protected prototype_ `virtual void GetPinTypeSelectorFilters(TArray<TSharedPtr<IPinTypeSelectorFilter>>& OutFilters) const override;`
- L120 _protected prototype_ `virtual void OnAddNewVariable() override;`
- L121 _protected prototype_ `virtual void ZoomToSelection_Clicked() override;`
- L122 _protected prototype_ `void FindInBlueprint_Clicked();`
- L124 _public prototype_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms, bool bSelectFirstResult) override;`
- L125 _public prototype_ `void SaveEditedObjectState();`
- L126 _public prototype_ `virtual void RestoreEditedObjectState() override;`
- L127 _public prototype_ `virtual void SetupViewForBlueprintEditingMode() override;`
- L128 _public prototype_ `virtual void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);`
- L129 _public prototype_ `virtual void OnGraphEditorBackgrounded(const TSharedRef<SGraphEditor>& InGraphEditor);`
- L130 _public function_ `virtual bool GetIsContextSensitive() override`
- L131 _public function_ `virtual void SetIsContextSensitive(const bool bIsContextSensitive) override`
- L132 _public function_ `virtual void RegisterToolbarTab(const TSharedRef<FTabManager>& InTabManager) override`
- L133 _public function_ `virtual const TArray<UObject*>* GetObjectsCurrentlyBeingEdited() const override`
- L134 _public prototype_ `virtual void AddCompileWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L135 _public prototype_ `virtual void AddSettingsAndDefaultWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L136 _public prototype_ `virtual void AddFindWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L137 _public prototype_ `virtual void AddSelectedDebugObjectWidget(FToolBarBuilder& ToolbarBuilder) override;`
- L138 _public function_ `virtual void AddAutoCompileWidget(FToolBarBuilder& ToolbarBuilder) override`
- L139 _public function_ `virtual void Compile()`
- L140 _public function_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList)`
- L141 _public function_ `virtual bool ShouldOpenGraphByDefault() const`
- L142 _public function_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)`
- L143 _public function_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject)`
- L144 _public function_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph)`
- L145 _public function_ `virtual FPreviewScene* GetPreviewScene() override`
- L148 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L152 _public function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L153 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L154 _public function_ `virtual FString GetReferencerName() const override`
- L155 _public function_ `virtual TStatId GetStatId() const override`
- L156 _public prototype_ `virtual void StartEditingDefaults(bool bAutoFocus = true, bool bForceRefresh = false);`
- L158 _public prototype_ `float GetInstructionTextOpacity(UEdGraph* InGraph) const;`
- L159 _public prototype_ `virtual void ClearSelectionStateFor(FName SelectionOwner);`
- L161 _protected prototype_ `void OnLogTokenClicked(const TSharedRef<IMessageToken>& MessageToken);`
- L164 _protected prototype_ `void DumpMessagesToCompilerLog(const TArray<TSharedRef<class FTokenizedMessage>>& Messages, bool bForceMessageDisplay);` — Dumps messages to the compiler log, with an option to force it to display/come to front
- L167 _public function_ `void CreateDefaultTabContents(const TArray<UBlueprint*> InBlueprints)` — `UE_DEPRECATED(5.7, "Please use void CreateDefaultTabContents(const TArray<FRigVMEditorAssetInterfacePtr> InBlueprints)")`
- L168 _public prototype_ `void CreateDefaultTabContents(const TArray<FRigVMEditorAssetInterfacePtr> InBlueprints);`
- L170 _public prototype_ `TSharedRef<SWidget> GenerateCompileOptionsMenu();`
- L171 _public prototype_ `void MakeSaveOnCompileSubMenu(FMenuBuilder& InMenu);`
- L172 _public prototype_ `void SetSaveOnCompileSetting(ERigVMSaveOnCompile NewSetting);`
- L173 _public prototype_ `bool IsSaveOnCompileOptionSet(ERigVMSaveOnCompile Option);`
- L174 _public prototype_ `void ToggleJumpToErrorNodeSetting();`
- L175 _public prototype_ `bool IsJumpToErrorNodeOptionSet();`
- L176 _public prototype_ `UEdGraphNode* FindNodeWithError(UBlueprint* Blueprint, EMessageSeverity::Type Severity);`
- L177 _public prototype_ `UEdGraphNode* FindNodeWithError(FCompilerResultsLog const& ErrorLog, EMessageSeverity::Type Severity);`
- L178 _public prototype_ `FText GetCompileStatusTooltip() const;`
- L179 _public prototype_ `FSlateIcon GetCompileStatusImage() const;`
- L182 _public prototype_ `static const FSlateBrush* GetGlyphForGraph(const UEdGraph* Graph, bool bInLargeIcon);`
- L184 _public prototype_ `static const FName SelectionState_GraphExplorer();`
- L185 _public prototype_ `static const FName SelectionState_Graph();`
- L186 _public prototype_ `static const FName SelectionState_ClassSettings();`
- L187 _public prototype_ `static const FName SelectionState_ClassDefaults();`
- L189 _public function_ `virtual FNotifyHook* GetNotifyHook() override`
- L191 _public prototype_ `void OnSelectedNodesChanged(const FGraphPanelSelectionSet& NewSelection);`
- L193 _public prototype_ `void OnAlignTop();`
- L194 _public prototype_ `void OnAlignMiddle();`
- L195 _public prototype_ `void OnAlignBottom();`
- L196 _public prototype_ `void OnAlignLeft();`
- L197 _public prototype_ `void OnAlignCenter();`
- L198 _public prototype_ `void OnAlignRight();`
- L199 _public prototype_ `void OnStraightenConnections();`
- L200 _public prototype_ `void OnDistributeNodesH();`
- L201 _public prototype_ `void OnDistributeNodesV();`
- L202 _public prototype_ `void SelectAllNodes();`
- L203 _public prototype_ `bool CanSelectAllNodes() const;`
- L207 _protected member_ `TSharedPtr<FDocumentTracker> DocumentManager;`
- L210 _protected member_ `TSharedPtr<class SRigVMDetailsInspector> Inspector;` — Node inspector widget
- L213 _protected member_ `TWeakPtr<class SGraphEditor> FocusedGraphEdPtr;` — Currently focused graph editor
- L216 _protected member_ `TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;` — Factory that spawns graph editors; used to look up all tabs spawned by it.
- L219 _protected member_ `FName CurrentUISelection;` — The current UI selection state of this editor
- L222 _protected member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for the graph editor
- L225 _protected member_ `TSharedPtr<class SWidget> CompilerResults;` — Compiler results log, with the log listing that it reflects
- L226 _protected member_ `TSharedPtr<class IMessageLogListing> CompilerResultsListing;`
- L229 _protected member_ `TSharedPtr<class SRigVMFindReferences> FindResults;` — Find results log as well as the search filter
- L232 _protected member_ `UEdGraph* HasOpenActionMenu;` — When set, flags which graph has a action menu currently open (if null, no graphs do).
- L235 _protected member_ `float InstructionsFadeCountdown;` — Used to nicely fade instruction text, when the context menu is opened.
- L238 _protected member_ `TSharedPtr<class SRigVMDetailsInspector> DefaultEditor;` — defaults inspector widget
- L241 _protected member_ `bool bWasOpenedInDefaultsMode;` — True if the editor was opened in defaults mode
- L244 _protected member_ `bool bBlueprintModifiedOnOpen;` — Did we update the blueprint when it opened
- L247 _protected member_ `bool bIsActionMenuContextSensitive;` — Whether the graph action menu should be sensitive to the pins dragged off of
- L249 _protected member_ `FName ElementInDetailsPanel = NAME_None;`
- L252 _protected member_ `uint64 LastDoubleClickFrame = TNumericLimits<uint64>::Max();` — Last frame in which the graph was double clicked. Useful to filter excess double clicks in a single frame
- L254 _protected prototype_ `void HandlePreVariablesChanged(FName InName);`
- L255 _protected prototype_ `void HandlePostVariablesChanged(FName InName);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMNewEditorMode.h` (Public)


#### struct `FRigVMNewEditorApplicationModes`  
`struct FRigVMNewEditorApplicationModes`  
_L13-21_
- L16 _public prototype_ `static const FName StandardRigVMEditorMode();` — Mode identifiers
- L17 _public prototype_ `static const FName RigVMDefaultsMode();`
- L20 _private function_ `FRigVMNewEditorApplicationModes()`

#### class `FRigVMNewEditorMode`  
`class FRigVMNewEditorMode : public FApplicationMode`  
_L23-41_
- inherits: `FApplicationMode`
- L26 _public prototype_ `FRigVMNewEditorMode(const TSharedRef<FRigVMNewEditor>& InRigVMEditor);`
- L29 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L31 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);`
- L33 _public prototype_ `virtual void PostActivateMode() override;`
- L34 _public prototype_ `virtual void PreDeactivateMode() override;`
- L38 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs
- L40 _protected member_ `TWeakPtr<FRigVMNewEditor> Editor;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMVariableDetailCustomization.h` (Public)


#### class `FRigVMVariableDetailCustomization`  
`class FRigVMVariableDetailCustomization : public IDetailCustomization`  
_L29-112_
- inherits: `IDetailCustomization`
- L33 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<IRigVMEditor> InEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public prototype_ `FRigVMVariableDetailCustomization(TSharedPtr<IRigVMEditor> InEditor, FRigVMEditorAssetInterfacePtr Blueprint);`
- L37 _public prototype_ `static TSharedPtr<IDetailCustomization> MakeLegacyInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);`
- L38 _public prototype_ `FRigVMVariableDetailCustomization(TSharedPtr<IBlueprintEditor> RigVMigEditor, UBlueprint* Blueprint);`
- L42 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L45 _private prototype_ `void PopulateCategories();`
- L46 _private prototype_ `void OnFinishedChangingVariable(const FPropertyChangedEvent& PropertyChangedEvent);`
- L50 _private prototype_ `FName GetVariableName() const;` — Accessors passed to parent
- L51 _private prototype_ `FText OnGetVariableName() const;`
- L52 _private prototype_ `void OnVarNameCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L55 _private prototype_ `FEdGraphPinType OnGetVarType() const;` — Callbacks for uproperty details customization
- L56 _private prototype_ `void OnVarTypeChanged(const FEdGraphPinType& NewPinType);`
- L58 _private prototype_ `void OnBrowseToVarType() const;`
- L59 _private prototype_ `bool CanBrowseToVarType() const;`
- L62 _private prototype_ `FText OnGetTooltipText() const;`
- L63 _private prototype_ `void OnTooltipTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L64 _private prototype_ `EVisibility IsToolTipVisible() const;`
- L66 _private prototype_ `FText OnGetCategoryText() const;`
- L67 _private prototype_ `void OnCategoryTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName VarName);`
- L68 _private prototype_ `TSharedRef< ITableRow > MakeCategoryViewWidget( TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable );`
- L69 _private prototype_ `void OnCategorySelectionChanged( TSharedPtr<FText> ProposedSelection, ESelectInfo::Type );`
- L72 _private prototype_ `ECheckBoxState OnGetExposedToSpawnCheckboxState() const;`
- L73 _private prototype_ `void OnExposedToSpawnChanged(ECheckBoxState InNewState);`
- L75 _private prototype_ `ECheckBoxState OnGetPublicCheckboxState() const;`
- L76 _private prototype_ `void OnPublicChanged(ECheckBoxState InNewState);`
- L78 _private prototype_ `ECheckBoxState OnGetExposedToCinematicsCheckboxState() const;`
- L79 _private prototype_ `void OnExposedToCinematicsChanged(ECheckBoxState InNewState);`
- L82 _private prototype_ `FText OnGetMetaKeyValue(FName Key) const;`
- L83 _private prototype_ `void OnMetaKeyValueChanged(const FText& NewMinValue, ETextCommit::Type CommitInfo, FName Key);`
- L84 _private prototype_ `EVisibility RangeVisibility() const;`
- L89 _private prototype_ `void OnPostEditorRefresh();` — Refreshes cached data that changes after a Blueprint recompile
- L93 _private member_ `TWeakPtr<IRigVMEditor> EditorPtr;` — The Blueprint editor we are embedded in
- L96 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> BlueprintPtr;` — The blueprint we are editing
- L99 _private member_ `TSharedPtr<SEditableTextBox> VarNameEditableTextBox;` — The widget used when in variable name editing mode
- L102 _private member_ `TArray<TSharedPtr<FText>> CategorySource;` — A list of all category names to choose from
- L104 _private member_ `TWeakPtr<SComboButton> CategoryComboButton;` — Widgets for the categories
- L105 _private member_ `TWeakPtr<SListView<TSharedPtr<FText>>> CategoryListView;`
- L108 _private member_ `TWeakFieldPtr<const FProperty> CachedVariableProperty;` — Cached property for the variable we are affecting
- L111 _private member_ `mutable FName CachedVariableName;` — Cached name for the variable we are affecting

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/RigVMVariantDetailCustomization.h` (Public)


#### class `FRigVMVariantDetailCustomization`  
`class FRigVMVariantDetailCustomization : public IPropertyTypeCustomization`  
_L13-42_
- inherits: `IPropertyTypeCustomization`
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _public prototype_ `FRigVMVariant GetVariant() const;`
- L27 _public prototype_ `FRigVMVariantRef GetSubjectVariantRef() const;`
- L28 _public prototype_ `TArray<FRigVMVariantRef> GetVariantRefs() const;`
- L32 _protected prototype_ `void OnVariantChanged(const FRigVMVariant& InNewVariant);`
- L33 _protected prototype_ `void OnBrowseVariantRef(const FRigVMVariantRef& InVariantRef);`
- L34 _protected prototype_ `TArray<FRigVMTag> OnGetTags() const;`
- L35 _protected prototype_ `void OnAddTag(const FName& InTagName);`
- L36 _protected prototype_ `void OnRemoveTag(const FName& InTagName);`
- L38 _protected member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized = nullptr;`
- L41 _protected member_ `TSharedPtr<SRigVMLogWidget> VariantLog;` — The log widget used for function variants

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/SRigVMActionMenu.h` (Public)


#### struct `FRigVMGraphSchemaAction_NewNode`  
`struct FRigVMGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L18-32_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a new RigVM node to the graph
- L25 _public member_ `TSharedPtr<URigVMEdGraphNodeSpawner> NodeSpawner;`
- L27 _public function_ `static FName StaticGetTypeId()`
- L28 _public function_ `FName GetTypeId() const override`
- L31 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### class `SRigVMActionMenu`  
`class SRigVMActionMenu : public SBorder`  
_L38-94_
- inherits: `SBorder`
- L42 _public function_ `SLATE_BEGIN_ARGS( SRigVMActionMenu ) : _GraphObj( nullptr ) , _NewNodePosition( FVector2f::ZeroVector )`
- L47 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FDeprecateSlateVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedPtr<IRigVMEditor> InEditor );`
- L55 _public prototype_ `~SRigVMActionMenu();`
- L57 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L60 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L65 _protected prototype_ `FText GetSearchContextDesc() const;` — UI Callback functions
- L66 _protected prototype_ `void OnContextToggleChanged(ECheckBoxState CheckState);`
- L67 _protected prototype_ `ECheckBoxState ContextToggleIsChecked() const;`
- L69 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType );`
- L71 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L74 _protected prototype_ `TSharedRef<FGraphActionListBuilderBase> OnGetActionList();` — Callback used to populate all actions list in SGraphActionMenu
- L77 _protected prototype_ `void ConstructActionContext(FBlueprintActionContext& ContextDescOut);`
- L80 _protected prototype_ `void TryInsertPromoteToVariable(FBlueprintActionContext const& Context, FGraphActionListBuilderBase& OutAllActions);` — Function to try to insert a promote to variable entry if it is possible to do so.
- L84 _private member_ `TObjectPtr<UEdGraph> GraphObj = nullptr;`
- L85 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L86 _private member_ `FDeprecateSlateVector2D NewNodePosition;`
- L87 _private member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L89 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L90 _private member_ `TWeakPtr<IRigVMEditor> EditorPtr;`
- L91 _private member_ `TSharedPtr<FRigVMActionMenuBuilder> ContextMenuBuilder;`
- L93 _private member_ `bool bActionExecuted = false;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Editor/SRigVMDetailsInspector.h` (Public)


#### class `SRigVMDetailsInspector`  
`class SRigVMDetailsInspector : public SCompoundWidget, public FGCObject`  
_L47-225_
- inherits: `SCompoundWidget,FGCObject`
- desc: Widget that shows properties and tools related to the selected node(s)
- L50 _public function_ `SLATE_BEGIN_ARGS( SRigVMDetailsInspector ) : _ShowPublicViewControl(false) , _HideNameArea(true) , _SetNotifyHook(true) , _ShowTitleArea(false) , _ShowLocalVariables(false) , _ScrollbarAlignment(HAlign_Right) , _ShowSectionSelector(false)`
- L60 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IRigVMEditor>, Editor) SLATE_ARGUMENT(TWeakPtr<SRigVMEditorGraphExplorer>, GraphExplorerWidget) SLATE_ATTRIBUTE( bool, ShowPublicViewControl ) SLATE_ARGUMENT( bool, HideNameArea ) SLATE_ARGUMENT( FIsPropertyEditingEnabled, IsPropertyEditingEnabledDelegate ) SLATE_ARGUMENT( FOnFinishedChangingProperties::FDelegate, OnFinishedChangingProperties ) SLATE_ARGUMENT( FName, ViewIdentifier) SLATE_ARGUMENT( bool, SetNotifyHook) SLATE_ARGUMENT( bool, ShowTitleArea) SLATE_ARGUMENT( bool, ShowLocalVariables) SLATE_ARGUMENT( TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_ARGUMENT( EHorizontalAlignment, ScrollbarAlignment) SLATE_ARGUMENT( bool, ShowSectionSelector) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L101 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L105 _public prototype_ `void ShowDetailsForSingleObject(UObject* Object, const FShowDetailsOptions& Options = FShowDetailsOptions());` — Update the inspector window to show information on the supplied object
- L108 _public prototype_ `void ShowDetailsForObjects(const TArray<UObject*>& PropertyObjects, const FShowDetailsOptions& Options = FShowDetailsOptions());` — Update the inspector window to show information on the supplied objects
- L111 _public prototype_ `void ShowSingleStruct(TSharedPtr<FStructOnScope> InStructToDisplay);` — Update the inspector window to show single struct. This invalidates ShowDetailsForObjects
- L114 _public prototype_ `bool IsPropertyVisible( const struct FPropertyAndParent& PropertyAndParent ) const;` — Used to control visibility of a property in the property window
- L117 _public function_ `TSharedPtr<class IDetailsView> GetPropertyView() const`
- L119 _public prototype_ `TSharedPtr<SDockTab> GetOwnerTab() const;`
- L120 _public prototype_ `void SetOwnerTab(TSharedRef<SDockTab> Tab);`
- L124 _public prototype_ `const TArray< TWeakObjectPtr<UObject> >& GetSelectedObjects() const;` — returns the list of selected objects
- L126 _public prototype_ `void OnEditorClose(const IRigVMEditor* RigVMEditorBase, FRigVMEditorAssetInterfacePtr RigVMBlueprint);`
- L128 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L129 _public prototype_ `virtual FString GetReferencerName() const override;`
- L133 _protected prototype_ `void UpdateFromObjects(const TArray<UObject*>& PropertyObjects, TArray<UObject*>& SelectionInfo, const FShowDetailsOptions& Options);` — Update the inspector window to show information on the supplied objects
- L136 _protected prototype_ `void AddPropertiesRecursive(FProperty* Property);` — Add this property and all its child properties to SelectedObjectProperties
- L139 _protected member_ `TWeakPtr<IRigVMEditor> WeakEditor;` — Pointer back to the kismet 2 tool that owns us
- L142 _protected member_ `TWeakPtr<SDockTab> OwnerTab;` — The tab that owns this details view.
- L145 _protected member_ `FText PropertyViewTitle;` — String used as the title above the property window
- L148 _protected member_ `bool bShowInspectorPropertyView;` — Should we currently show the property view
- L151 _protected member_ `ECheckBoxState PublicViewState;` — State of CheckBox representing whether to show only the public variables
- L154 _protected member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L157 _protected member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Selected objects for this detail view
- L160 _protected member_ `TSharedPtr<SBorder> ContextualEditingBorderWidget;` — Border widget that wraps a dynamic context-sensitive widget for editing objects that the property window is displaying
- L163 _protected member_ `TAttribute<bool> bShowPublicView;` — If true show the public view control
- L166 _protected member_ `bool bShowTitleArea;` — If true show the kismet inspector title widget
- L169 _protected member_ `TSet< TWeakFieldPtr<FProperty> > SelectedObjectProperties;` — Set of object properties that should be visible
- L172 _protected member_ `FIsPropertyEditingEnabled IsPropertyEditingEnabledDelegate;` — User defined delegate for IsPropertyEditingEnabled:
- L175 _protected member_ `FOnFinishedChangingProperties::FDelegate UserOnFinishedChangingProperties;` — User defined delegate for OnFinishedChangingProperties
- L178 _protected member_ `bool bRefreshOnTick;` — When TRUE, the Kismet inspector needs to refresh the details view on Tick
- L181 _protected member_ `TArray<TObjectPtr<UObject>> RefreshPropertyObjects;` — Holds the property objects that need to be displayed by the inspector starting on the next tick
- L184 _protected member_ `FShowDetailsOptions RefreshOptions;` — Details options that are used by the inspector on the next refresh.
- L187 _protected member_ `TSharedPtr<FStructOnScope> StructToDisplay;` — Struct to preview
- L190 _protected member_ `TSharedPtr<class IStructureDetailsView> StructureDetailsView;` — Sturct Detail View
- L193 _protected prototype_ `void UpdateFromSingleStruct(const TSharedPtr<FStructOnScope>& InStructToDisplay);` — Update the inspector window to show information on the single struct
- L196 _protected prototype_ `bool IsStructViewPropertyReadOnly(const struct FPropertyAndParent& PropertyAndParent) const;` — Is struct view property read only
- L201 _protected prototype_ `EVisibility GetPropertyViewVisibility() const;` — Returns whether the property view be visible
- L204 _protected prototype_ `bool IsPropertyEditingEnabled() const;` — Returns whether the properties in the view should be editable
- L210 _protected prototype_ `TSharedRef<SWidget> MakeContextualEditingWidget(TArray<UObject*>& SelectionInfo, const FShowDetailsOptions& Options);` — Generates a widget that is used to edit the specified object array contextually.  This widget will be displayed along with a property view in the level editor
- L215 _protected prototype_ `FText GetContextualEditingWidgetTitle() const;` — Generates the text for the title in the contextual editing widget
- L217 _protected prototype_ `ECheckBoxState GetPublicViewCheckboxState() const;`
- L218 _protected prototype_ `void SetPublicViewCheckboxState(ECheckBoxState InIsChecked);`
- L220 _protected prototype_ `bool IsAnyParentOrContainerSelected(const FPropertyAndParent& PropertyAndParent) const;`
- L223 _protected prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);` — Callback invoked after a value change on the selected object(s)

#### struct `SRigVMDetailsInspector::FShowDetailsOptions`  
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

- L26 _macro_ `#define UE_API RIGVMEDITOR_API`
- L41 _typedef_ `typedef TSet<class UObject*> FInspectorSelectionSet;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/RigVMEditorBlueprintLibrary.h` (Public)


#### enum `ERigVMBlueprintLoadLogSeverity`  
`enum ERigVMBlueprintLoadLogSeverity : uint8`  
_L18-23_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Display`
- L21 _public enumerator_ `Warning`
- L22 _public enumerator_ `Error`

#### struct `FRigVMBlueprintLoadLogEntry`  
`struct FRigVMBlueprintLoadLogEntry`  
_L26-49_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public function_ `FRigVMBlueprintLoadLogEntry() : Severity(ERigVMBlueprintLoadLogSeverity::Display) , Subject(nullptr)`
- L35 _public function_ `FRigVMBlueprintLoadLogEntry(ERigVMBlueprintLoadLogSeverity InSeverity, UObject* InSubject, const FString& InMessage) : Severity(InSeverity) , Subject(InSubject) , Message(InMessage)`
- L42 _public member_ `TEnumAsByte<ERigVMBlueprintLoadLogSeverity> Severity;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=Log)`
- L45 _public member_ `TObjectPtr<UObject> Subject;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=Log)`
- L48 _public member_ `FString Message;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category=Log)`

#### class `URigVMEditorBlueprintLibrary`  
`class URigVMEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L59-144_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(ScriptName="RigVMBlueprintLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L66 _public prototype_ `static void RecompileVM(URigVMBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L69 _public prototype_ `static void RecompileVMIfRequired(URigVMBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L72 _public prototype_ `static void RequestAutoVMRecompilation(URigVMBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L75 _public prototype_ `static URigVMGraph* GetModel(URigVMBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RigVM Blueprint")`
- L78 _public prototype_ `static URigVMController* GetController(URigVMBlueprint* InBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RigVM Blueprint")`
- L81 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssets();` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L84 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsByClass(TSubclassOf<URigVMBlueprint> InClass);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L87 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithBlueprintFilter_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMBlueprintFilterDynamic InBlueprintFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "LoadAssetsWithBlueprintFilter", ScriptName = "LoadAssetsWithBlueprintFilter"))`
- L92 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithAssetDataFilter_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilterDynamic InAssetDataFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "LoadAssetsWithAssetDataFilter", ScriptName = "LoadAssetsWithAssetDataFilter"))`
- L97 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithNodeFilter_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMNodeFilterDynamic InNodeFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "LoadAssetsWithNodeFilter", ScriptName = "LoadAssetsWithNodeFilter"))`
- L101 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithNodeFilter( TSubclassOf<URigVMBlueprint> InClass, FRigVMNodeFilter InNodeFilter);`
- L106 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithAssetDataAndBlueprintFilters_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilterDynamic InAssetDataFilter, FRigVMBlueprintFilterDynamic InBlueprintFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "LoadAssetsWithAssetDataAndBlueprintFilters", ScriptName = "LoadAssetsWithAssetDataAndBlueprintFilters"))`
- L111 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithAssetDataAndBlueprintFilters( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilter InAssetDataFilter, FRigVMBlueprintFilter InBlueprintFilter);`
- L117 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithAssetDataAndNodeFilters_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilterDynamic InAssetDataFilter, FRigVMNodeFilterDynamic InNodeFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "LoadAssetsWithAssetDataAndNodeFilters", ScriptName = "LoadAssetsWithAssetDataAndNodeFilters"))`
- L122 _public prototype_ `static TArray<URigVMBlueprint*> LoadAssetsWithAssetDataAndNodeFilters( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilter InAssetDataFilter, FRigVMNodeFilter InNodeFilter);`
- L128 _public prototype_ `static TArray<FAssetData> GetAssetsWithFilter_ForBlueprint( TSubclassOf<URigVMBlueprint> InClass, FRigVMAssetDataFilterDynamic InAssetDataFilter);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint", meta = (DisplayName = "GetAssetsWithFilter", ScriptName = "GetAssetsWithFilter"))`
- L132 _public prototype_ `static TArray<FAssetData> GetAssetsWithFilter( UClass* InClass, FRigVMAssetDataFilter InAssetDataFilter);`
- L137 _public prototype_ `static bool RenderRigVMSubjectToPNG(UObject* InUnitOrDispatchStructOrLibraryNode, const FString& OutFileName);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L140 _public prototype_ `static bool RenderRigVMTemplateToPNG(FName InTemplateNotation, const FString& OutFileName);` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L142 _public prototype_ `static bool RenderModelNodeToPNG(URigVMEditorAsset* EditorAsset, URigVMNode* InModelNode, const FString& OutFileName);`
- L143 _public prototype_ `static UObject* MakeRigVMAssetForSubject(UObject* InUnitOrDispatchStructOrLibraryNode, const URigVMSchema *& OutSchema);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`
- L51 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMAssetDataFilter, const FAssetData&);`
- L51 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMAssetDataFilter, const FAssetData&);`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMBlueprintFilter, const URigVMBlueprint*, const TArray<FRigVMBlueprintLoadLogEntry>&);`
- L52 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMBlueprintFilter, const URigVMBlueprint*, const TArray<FRigVMBlueprintLoadLogEntry>&);`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMNodeFilter, const URigVMBlueprint*, const URigVMNode*);`
- L53 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMNodeFilter, const URigVMBlueprint*, const URigVMNode*);`
- L54 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FRigVMAssetDataFilterDynamic, FAssetData, AssetData);`
- L54 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FRigVMAssetDataFilterDynamic, FAssetData, AssetData);`
- L55 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMBlueprintFilterDynamic, const URigVMBlueprint*, Blueprint, TArray<FRigVMBlueprintLoadLogEntry>, LogDuringLoad);`
- L55 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMBlueprintFilterDynamic, const URigVMBlueprint*, Blueprint, TArray<FRigVMBlueprintLoadLogEntry>, LogDuringLoad);`
- L56 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMNodeFilterDynamic, const URigVMBlueprint*, Blueprint, const URigVMNode*, Node);`
- L56 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FRigVMNodeFilterDynamic, const URigVMBlueprint*, Blueprint, const URigVMNode*, Node);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/RigVMEditorModule.h` (Public)


#### enum `ERefreshRigVMEditorReason::Type`  
`enum Type`  
_L49-54_
- L51 _public enumerator_ `BlueprintCompiled`
- L52 _public enumerator_ `PostUndo`
- L53 _public enumerator_ `UnknownReason`

#### struct `UE::RigVMEditor::FRigVMEditorFindNodeReferencesParams`  
`struct FRigVMEditorFindNodeReferencesParams`  
_L60-79_
- desc: Params when finding references for a node
- L62 _public function_ `FRigVMEditorFindNodeReferencesParams( const TWeakInterfacePtr<IRigVMEditorAssetInterface> InRigVMAsset, const TWeakObjectPtr<const URigVMEdGraphNode> InEdGraphNode, const bool bInSearchInAllBlueprints) : WeakRigVMAsset(InRigVMAsset) , WeakEdGraphNode(InEdGraphNode) , bSearchInAllBlueprints(bInSearchInAllBlueprints)`
- L72 _public member_ `const TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakRigVMAsset;` — The asset that contains the node
- L75 _public member_ `const TWeakObjectPtr<const URigVMEdGraphNode> WeakEdGraphNode;` — The ed graph node
- L78 _public member_ `const bool bSearchInAllBlueprints;` — If true, searches in all blueprints

#### class `IRigVMEditorModule`  
`class IRigVMEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility, public FStructureEditorUtils::INotifyOnStructChanged`  
_L85-103_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility,FStructureEditorUtils::INotifyOnStructChanged`
- desc: shallow interface declaration for use within RigVMDeveloper
- L89 _public function_ `static IRigVMEditorModule& Get()`
- L94 _public prototype_ `virtual void GetContextMenuActions(const URigVMEdGraphSchema* Schema, class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const = 0;`
- L95 _public prototype_ `virtual void GetTypeActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) = 0;`
- L96 _public prototype_ `virtual void GetTypeActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, TArray<TSharedRef<URigVMEdGraphNodeSpawner>>& OutGraphNodeSpawners) = 0;`
- L97 _public prototype_ `virtual void GetInstanceActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) = 0;`
- L98 _public prototype_ `virtual void GetInstanceActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, TArray<TSharedRef<URigVMEdGraphNodeSpawner>>& OutGraphNodeSpawners) = 0;`
- L99 _public prototype_ `virtual void GetNodeContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, class UToolMenu* Menu) const = 0;`
- L100 _public prototype_ `virtual void GetPinContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, class UToolMenu* Menu) const = 0;`
- L101 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const = 0;`
- L102 _public prototype_ `virtual bool AssetsPublicFunctionsAllowed(const FAssetData& InAssetData) const = 0;`

#### class `FRigVMEditorModule`  
`class FRigVMEditorModule : public IRigVMEditorModule`  
_L105-228_
- inherits: `IRigVMEditorModule`
- L109 _public prototype_ `static FRigVMEditorModule& Get();`
- L112 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L113 _public prototype_ `virtual void ShutdownModule() override;`
- L115 _public prototype_ `void StartupModuleCommon();`
- L116 _public prototype_ `void ShutdownModuleCommon();`
- L120 _public function_ `virtual UClass* GetRigVMBlueprintClass() const` — `UE_DEPRECATED(5.7, "Please update your code")` — RigVMEditorModule interface
- L122 _public function_ `const URigVMBlueprint* GetRigVMBlueprintCDO() const` — `UE_DEPRECATED(5.7, "Please update your code")`
- L123 _public prototype_ `virtual void GetTypeActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) override;`
- L124 _public prototype_ `virtual void GetTypeActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, TArray<TSharedRef<URigVMEdGraphNodeSpawner>>& OutGraphNodeSpawners) override;`
- L125 _public prototype_ `virtual void GetInstanceActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, FBlueprintActionDatabaseRegistrar& ActionRegistrar) override;`
- L126 _public prototype_ `virtual void GetInstanceActions(FRigVMEditorAssetInterfacePtr RigVMBlueprint, TArray<TSharedRef<URigVMEdGraphNodeSpawner>>& OutGraphNodeSpawners) override;`
- L127 _public prototype_ `virtual void GetNodeContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, class UToolMenu* Menu) const override;`
- L128 _public prototype_ `virtual void GetPinContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, class UToolMenu* Menu) const override;`
- L129 _public function_ `virtual bool AssetsPublicFunctionsAllowed(const FAssetData& InAssetData) const override`
- L132 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — IHasMenuExtensibility interface
- L135 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override` — IHasToolBarExtensibility interface
- L138 _public prototype_ `virtual void PreChange(const UUserDefinedStruct* Changed, FStructureEditorUtils::EStructureEditorChangeInfo ChangedType) override;` — FStructureEditorUtils::INotifyOnStructChanged Interface, used to respond to changes to user defined structs
- L139 _public prototype_ `virtual void PostChange(const UUserDefinedStruct* Changed, FStructureEditorUtils::EStructureEditorChangeInfo ChangedType) override;`
- L142 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FRigVMEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<FRigVMEditorBase> );` — Get all toolbar extenders
- L143 _public prototype_ `virtual TArray<FRigVMEditorToolbarExtender>& GetAllRigVMEditorToolbarExtenders();`
- L145 _public prototype_ `virtual void GetContextMenuActions(const URigVMEdGraphSchema* Schema, class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L148 _public prototype_ `void CreateRootGraphIfRequired(FRigVMEditorAssetInterfacePtr InBlueprint) const;` — Make sure to create the root graph for a given blueprint
- L150 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;`
- L153 _public function_ `static UE::RigVMEditor::FRigVMEditorOnRequestFindNodeReferencesDelegate& GetOnRequestFindNodeReferences()` — Returns an event broadcast when finding references for a node is requested
- L157 _protected prototype_ `bool IsRigVMEditorModuleBase() const;`
- L158 _protected function_ `virtual UClass* GetRigVMLegacyBlueprintClass() const`
- L159 _protected function_ `virtual UClass* GetRigVMAssetClass() const`
- L160 _protected function_ `virtual UClass* GetRigVMEdGraphSchemaClass() const`
- L161 _protected function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const`
- L164 _protected prototype_ `virtual void GetNodeActionsContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;` — Specific section callbacks for the context menu
- L165 _protected prototype_ `virtual void GetNodeWorkflowContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L166 _protected prototype_ `virtual void GetNodeEventsContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L167 _protected prototype_ `virtual void GetNodeDefaultValueContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L168 _protected prototype_ `virtual void GetNodeConversionContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L169 _protected prototype_ `virtual void GetNodeDebugContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L170 _protected prototype_ `virtual void GetNodeVariablesContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L171 _protected prototype_ `virtual void GetNodeTemplatesContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L172 _protected prototype_ `virtual void GetNodeOrganizationContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L173 _protected prototype_ `virtual void GetNodeVariantContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L174 _protected prototype_ `virtual void GetNodeTestContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L175 _protected prototype_ `virtual void GetNodeDisplayContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const;`
- L176 _protected prototype_ `virtual void GetExposedPinContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L177 _protected prototype_ `virtual void GetPinWorkflowContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L178 _protected prototype_ `virtual void GetPinDebugContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L179 _protected prototype_ `virtual void GetPinArrayContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L180 _protected prototype_ `virtual void GetPinSequenceContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L181 _protected prototype_ `virtual void GetPinAggregateContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L182 _protected prototype_ `virtual void GetPinTemplateContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L183 _protected prototype_ `virtual void GetPinConversionContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L184 _protected prototype_ `virtual void GetPinVariableContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L185 _protected prototype_ `virtual void GetPinResetDefaultContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L186 _protected prototype_ `virtual void GetPinInjectedNodesContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L189 _protected member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;` — Extensibility managers
- L190 _protected member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L191 _protected member_ `TArray<FRigVMEditorToolbarExtender> RigVMEditorToolbarExtenders;`
- L194 _protected member_ `TSharedPtr<FRigVMEdGraphPanelNodeFactory> EdGraphPanelNodeFactory;` — Node factory for the rigvm graph
- L197 _protected member_ `TSharedPtr<FRigVMEdGraphPanelPinFactory> EdGraphPanelPinFactory;` — Pin factory for the rigvm graph
- L200 _protected member_ `FDelegateHandle RefreshAllNodesDelegateHandle;` — Delegate handles for blueprint utils
- L201 _protected member_ `FDelegateHandle ReconstructAllNodesDelegateHandle;`
- L202 _protected member_ `FDelegateHandle BlueprintVariableCustomizationHandle;`
- L205 _protected member_ `FRewindDebuggerForRigVM RewindDebuggerForRigVM;`
- L206 _protected member_ `FRigVMTraceModule RigVMTraceModule;`
- L212 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;` — StaticStruct is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L215 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;` — Registered asset type actions
- L217 _private prototype_ `void HandleNewBlueprintCreated(UBlueprint* InBlueprint);`
- L219 _private prototype_ `bool ShowWorkflowOptionsDialog(URigVMUserWorkflowOptions* InOptions) const;`
- L222 _private member_ `static UE::RigVMEditor::FRigVMEditorOnRequestFindNodeReferencesDelegate OnRequestFindNodeReferences;` — Event broadcast when finding references for a node is requested
- L224 _private member_ `FDelegateHandle AssetsPreDeleteDelegate;`
- L225 _private prototype_ `static void HandleAssetsPreDelete(const TArray<UObject*>& InAssetsToDelete);`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API RIGVMEDITOR_API`
- L41 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMEditor, Log, All);`
- L41 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMEditor, Log, All);`
- L43 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMUseNewEditor;`
- L44 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMBlueprintIndependentAssets;`
- L47 _namespace_ `namespace ERefreshRigVMEditorReason`
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L81 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorModule, FRigVMEditorOnRequestFindNodeReferencesDelegate, FRigVMEditorFindNodeReferencesParams );`
- L81 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorModule, FRigVMEditorOnRequestFindNodeReferencesDelegate, FRigVMEditorFindNodeReferencesParams );` (scope `UE::RigVMEditor`)
- L142 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FRigVMEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<FRigVMEditorBase> );` — Get all toolbar extenders

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Trace/RigVMTraceModule.h` (Public)


#### class `FRigVMTraceModule`  
`class FRigVMTraceModule : public TraceServices::IModule`  
_L23-37_
- inherits: `TraceServices::IModule`
- desc: The trace module implements the rewind debugger extension to record traces
- L26 _public prototype_ `virtual ~FRigVMTraceModule() = default;`
- L29 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L30 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L31 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L32 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L33 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L36 _private member_ `static FName ModuleName;`

#### class `FRewindDebuggerForRigVM`  
`class FRewindDebuggerForRigVM : public IRewindDebuggerExtension`  
_L39-53_
- inherits: `IRewindDebuggerExtension`
- L42 _public function_ `FRewindDebuggerForRigVM()`
- L43 _public prototype_ `virtual ~FRewindDebuggerForRigVM() = default;`
- L45 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L46 _public function_ `virtual FString GetName() override`
- L50 _private member_ `double LastTraceTime = 0.0;`
- L51 _private member_ `double LastLogTime = 0.0;`
- L52 _private member_ `TMap<uint64,TWeakObjectPtr<URigVMHost>> AffectedHosts;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Trace/RigVMTraceTrack.h` (Public)


#### class `FRewindDebuggerRigVMExecuteTrack`  
`class FRewindDebuggerRigVMExecuteTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L21-59_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: The execute track advertises the relevant data per frame for a given RigVM host.
- L24 _public prototype_ `FRewindDebuggerRigVMExecuteTrack(uint64 InHostId);`
- L28 _private prototype_ `virtual bool UpdateInternal() override;`
- L29 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L30 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L32 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L37 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L42 _private function_ `virtual FName GetNameInternal() const override`
- L43 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L45 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L47 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L48 _private member_ `mutable int EventUpdateRequested = 0;`
- L50 _private member_ `uint64 HostId;`
- L51 _private member_ `FSlateIcon Icon;`
- L52 _private member_ `FText TrackName;`
- L54 _private member_ `double PreviousScrubTime = 0.0f;`
- L55 _private member_ `double AbsoluteTime = 0.0;`
- L56 _private member_ `double DeltaTime = 0.0;`
- L58 _private member_ `TSharedPtr<SVerticalBox> DetailsVerticalBox;`

#### class `FRewindDebuggerRigVMTrack`  
`class FRewindDebuggerRigVMTrack : public RewindDebugger::FRewindDebuggerTrack`  
_L66-84_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: The RigVM rewind debugger track is the main track / parent track for all other RigVM related tracks
- L69 _public prototype_ `FRewindDebuggerRigVMTrack(uint64 InObjectId);`
- L71 _private prototype_ `virtual bool UpdateInternal() override;`
- L72 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L74 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L75 _private function_ `virtual FName GetNameInternal() const override`
- L76 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L77 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L78 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L80 _private member_ `FSlateIcon Icon;`
- L81 _private member_ `uint64 HostId;`
- L83 _private member_ `TArray<TSharedPtr<FRewindDebuggerTrack>> Children;`

#### class `FRewindDebuggerRigVMTrackCreator`  
`class FRewindDebuggerRigVMTrackCreator : public RewindDebugger::IRewindDebuggerTrackCreator`  
_L90-98_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- desc: Factory class to create RigVM rewind debugger tracks
- L93 _private prototype_ `virtual FName GetTargetTypeNameInternal() const;`
- L94 _private prototype_ `virtual FName GetNameInternal() const override;`
- L95 _private prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L96 _private prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L97 _private prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/RigVMTreeToolkitContext.h` (Public)


#### class `FRigVMTreeContext`  
`class FRigVMTreeContext : public FRigVMTreeElement`  
_L18-45_
- inherits: `FRigVMTreeElement`
- desc: The context is the top level object passed to anything that has to interact with the tree, like visible node traversal, task execution etc.
- L21 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeContext, FRigVMTreeElement) virtual uint32 GetVisibleChildrenHash() const;`
- L24 _public prototype_ `bool FiltersNode(TSharedRef<FRigVMTreeNode> InNode) const;`
- L26 _public member_ `TArray<TSharedRef<FRigVMTreeFilter>> Filters;`
- L28 _public prototype_ `static FAssetData FindAssetFromAnyPath(const FString& InPartialOrFullPath, bool bUseRootPath);`
- L30 _public prototype_ `DECLARE_EVENT_OneParam(FRigVMTreeContext, FLogTokenizedMessage, const TSharedRef<FTokenizedMessage>&) void LogMessage(const TSharedRef<FTokenizedMessage>& InMessage) const;`
- L32 _public prototype_ `void LogMessage(const FText& InText) const;`
- L33 _public prototype_ `void LogMessage(const FString& InString) const;`
- L34 _public prototype_ `void LogWarning(const FText& InText) const;`
- L35 _public prototype_ `void LogWarning(const FString& InString) const;`
- L36 _public prototype_ `void LogError(const FText& InText) const;`
- L37 _public prototype_ `void LogError(const FString& InString) const;`
- L40 _private member_ `uint32 HashOffset = 0;`
- L41 _private member_ `FLogTokenizedMessage OnLogTokenizedMessage;`

#### class `FRigVMTreePhase`  
`class FRigVMTreePhase : public FRigVMTreeElement`  
_L53-186_
- inherits: `FRigVMTreeElement`
- desc: The Phase describes a phase of performing a UI wizard, like picking a set of inputs, or performing tasks. This can be also seen as the steps a wizard goes through when performing a UI process.
- L56 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreePhase, FRigVMTreeElement) DECLARE_DELEGATE_RetVal(FReply, FReplyDelegate) DECLARE_DELEGATE_OneParam(FQueueTasksDelegate, const TArray<TSharedRef<FRigVMTreeTask>>&) FRigVMTreePhase(int32 InID, const FString& InName, const TSharedRef<FRigVMTreeContext>& InContext);`
- L63 _public function_ `int32 GetID() const`
- L68 _public function_ `const FString& GetName() const`
- L73 _public function_ `bool IsActive() const`
- L78 _public function_ `virtual bool AllowsMultiSelection() const`
- L83 _public function_ `void SetAllowsMultiSelection(bool InAllowsMultiSelection)`
- L88 _public function_ `TAttribute<bool>& IsCancelButtonVisible()`
- L93 _public function_ `TAttribute<bool>& IsCancelButtonEnabled()`
- L98 _public function_ `FReplyDelegate& OnCancel()`
- L103 _public function_ `FReply Cancel() const`
- L112 _public function_ `TAttribute<bool>& IsPrimaryButtonVisible()`
- L117 _public function_ `TAttribute<bool>& IsPrimaryButtonEnabled()`
- L122 _public function_ `TAttribute<FText>& PrimaryButtonText()`
- L127 _public function_ `FReplyDelegate& OnPrimaryAction()`
- L132 _public function_ `FReply PrimaryAction() const`
- L141 _public function_ `TSharedRef<FRigVMTreeContext> GetContext() const`
- L146 _public prototype_ `void IncrementContextHash();`
- L148 _public prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetAllNodes() const;`
- L150 _public prototype_ `const TArray<TSharedRef<FRigVMTreeNode>>& GetVisibleNodes() const;`
- L152 _public prototype_ `TSharedPtr<FRigVMTreeNode> FindVisibleNode(const FString& InPath) const;`
- L154 _public prototype_ `void AddNode(const TSharedRef<FRigVMTreeNode>& InNode);`
- L155 _public prototype_ `void RemoveNode(const TSharedRef<FRigVMTreeNode>& InNode);`
- L156 _public prototype_ `void SetNodes(const TArray<TSharedRef<FRigVMTreeNode>>& InNodes);`
- L158 _public function_ `FQueueTasksDelegate& OnQueueTasks()`
- L163 _public function_ `void QueueTasks(const TArray<TSharedRef<FRigVMTreeTask>>& InTasks) const`
- L170 _private member_ `int32 ID;`
- L171 _private member_ `FString Name;`
- L172 _private member_ `bool bIsActive;`
- L173 _private member_ `bool bAllowsMultiSelection;`
- L174 _private member_ `TSharedRef<FRigVMTreeContext> Context;`
- L175 _private member_ `TSharedRef<FRigVMTreeRootNode> RootNode;`
- L176 _private member_ `TAttribute<bool> IsCancelButtonVisibleAttribute;`
- L177 _private member_ `TAttribute<bool> IsCancelButtonEnabledAttribute;`
- L178 _private member_ `FReplyDelegate OnCancelDelegate;`
- L179 _private member_ `TAttribute<bool> IsPrimaryButtonVisibleAttribute;`
- L180 _private member_ `TAttribute<bool> IsPrimaryButtonEnabledAttribute;`
- L181 _private member_ `TAttribute<FText> PrimaryButtonTextAttribute;`
- L182 _private member_ `FReplyDelegate OnPrimaryActionDelegate;`
- L183 _private member_ `FQueueTasksDelegate QueueTasksDelegate;`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_EVENT_OneParam(FRigVMTreeContext, FLogTokenizedMessage, const TSharedRef<FTokenizedMessage>&) void LogMessage(const TSharedRef<FTokenizedMessage>& InMessage) const;`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FReplyDelegate) DECLARE_DELEGATE_OneParam(FQueueTasksDelegate, const TArray<TSharedRef<FRigVMTreeTask>>&) FRigVMTreePhase(int32 InID, const FString& InName, const TSharedRef<FRigVMTreeContext>& InContext);`
- L59 _delegate_ `DECLARE_DELEGATE_OneParam(FQueueTasksDelegate, const TArray<TSharedRef<FRigVMTreeTask>>&) FRigVMTreePhase(int32 InID, const FString& InName, const TSharedRef<FRigVMTreeContext>& InContext);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/RigVMTreeToolkitDefines.h` (Public)


#### class `FRigVMTreeElement`  
`class FRigVMTreeElement : public TSharedFromThis<FRigVMTreeElement>`  
_L59-89_
- inherits: `TSharedFromThis<FRigVMTreeElement>`
- desc: The Tree Element is the base class for anything within a tree and manages the lifetime as well as type checking
- L62 _public member_ `static inline const FLazyName Type = FLazyName(TEXT("FRig`
- L63 _public function_ `virtual FName GetType() const`
- L68 _public function_ `virtual bool IsOfType(const FName& InType) const`
- L74 _public function_ `template<typename T> bool IsA() const`
- L79 _public prototype_ `virtual ~FRigVMTreeElement() = default;`
- L81 _public function_ `virtual void Initialize()`
- L86 _protected function_ `FRigVMTreeElement()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define DEFINE_RIGVMTREETOOLKIT_QUOTE(str) #str`
- L8 _macro_ `#define DEFINE_RIGVMTREETOOLKIT_ELEMENT(TypeName, SuperTypeName) \`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/RigVMTreeToolkitFilter.h` (Public)


#### class `FRigVMTreeFilter`  
`class FRigVMTreeFilter : public FRigVMTreeElement`  
_L15-56_
- inherits: `FRigVMTreeElement`
- desc: A Filter is used to hide elements from a tree. Filters can be used to filter by folder, filter by tags or anything else.
- L18 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFilter, FRigVMTreeElement) virtual bool CanBeToggledInUI() const`
- L25 _public function_ `virtual bool IsInvertedInUI() const`
- L30 _public function_ `virtual FText GetLabel() const`
- L35 _public function_ `virtual FText GetToolTip() const`
- L40 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext);`
- L42 _public prototype_ `virtual uint32 GetVisibleChildrenHash() const;`
- L44 _public function_ `bool IsEnabled() const`
- L49 _public function_ `void SetEnabled(bool InEnabled)`
- L55 _private member_ `bool bEnabled = true;`

#### class `FRigVMTreePathFilter`  
`class FRigVMTreePathFilter : public FRigVMTreeFilter`  
_L62-82_
- inherits: `FRigVMTreeFilter`
- desc: The Path filter is used to include elements only if they match a user provided path.
- L65 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreePathFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`
- L69 _public prototype_ `virtual uint32 GetVisibleChildrenHash() const override;`
- L71 _public function_ `const FString& GetFilterText() const`
- L75 _public function_ `void SetFilterText(const FString& InFilterText)`
- L81 _private member_ `FString FilterText;`

#### class `FRigVMTreeEngineContentFilter`  
`class FRigVMTreeEngineContentFilter : public FRigVMTreeFilter`  
_L88-106_
- inherits: `FRigVMTreeFilter`
- desc: The Engine Content Filter can be used to hide elements which reside on the engine content path.
- L91 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeEngineContentFilter, FRigVMTreeFilter) virtual bool CanBeToggledInUI() const override`
- L98 _public function_ `virtual bool IsInvertedInUI() const override`
- L103 _public prototype_ `virtual FText GetLabel() const override;`
- L105 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeDeveloperContentFilter`  
`class FRigVMTreeDeveloperContentFilter : public FRigVMTreeFilter`  
_L112-130_
- inherits: `FRigVMTreeFilter`
- desc: The Developer Content Filter can be used to hide items which reside on a developer content path.
- L115 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeDeveloperContentFilter, FRigVMTreeFilter) virtual bool CanBeToggledInUI() const override`
- L122 _public function_ `virtual bool IsInvertedInUI() const override`
- L127 _public prototype_ `virtual FText GetLabel() const override;`
- L129 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/RigVMTreeToolkitNode.h` (Public)


#### class `FRigVMTreeNode`  
`class FRigVMTreeNode : public FRigVMTreeElement`  
_L17-137_
- inherits: `FRigVMTreeElement`
- desc: A Node is the base element for anything that is shown within the tree.
- L20 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeNode, FRigVMTreeElement) FRigVMTreeNode(const FString& InPath) : Path(InPath)`
- L27 _public function_ `virtual const FString& GetPath() const`
- L32 _public prototype_ `virtual FAssetData GetAssetData() const;`
- L34 _public function_ `virtual URigVMBlueprint* GetBlueprint() const` — `UE_DEPRECATED(5.7, "Please use IRigVMEditorAssetInterface* GetAsset() const")`
- L35 _public prototype_ `virtual IRigVMEditorAssetInterface* GetAsset() const;`
- L37 _public prototype_ `virtual FText GetLabel() const;`
- L39 _public function_ `virtual void GetContextMenu(FMenuBuilder& InMenuBuilder)`
- L43 _public function_ `virtual bool IsCheckable() const`
- L48 _public prototype_ `ECheckBoxState GetCheckState() const;`
- L50 _public prototype_ `void SetCheckState(ECheckBoxState InNewState);`
- L51 _public prototype_ `void ResetCheckState();`
- L53 _public function_ `virtual bool ShouldExpandByDefault() const`
- L58 _public function_ `virtual const TArray<FRigVMTag>& GetTags() const`
- L63 _public prototype_ `int32 GetDepth() const;`
- L65 _public function_ `TSharedPtr<FRigVMTreeNode> GetParent() const`
- L74 _public prototype_ `TSharedRef<FRigVMTreeNode> GetRoot() const;`
- L76 _public function_ `const TArray<TSharedRef<FRigVMTreeNode>>& GetVisibleChildren(const TSharedRef<FRigVMTreeContext>& InContext) const`
- L82 _public function_ `TArray<TSharedRef<FRigVMTreeNode>> GetChildren(const TSharedRef<FRigVMTreeContext>& InContext) const`
- L88 _public function_ `virtual bool HasVisibleChildren() const`
- L93 _public prototype_ `TSharedPtr<FRigVMTreeNode> FindVisibleChild(const FString& InFullPath, const TSharedRef<FRigVMTreeContext>& InContext) const;`
- L95 _public prototype_ `virtual void DirtyChildren();`
- L96 _public prototype_ `virtual void DirtyVisibleChildren();`
- L97 _public prototype_ `void RequestRefresh(bool bForce = false);`
- L99 _public function_ `virtual const FSlateBrush* GetIconAndTint(FLinearColor& OutColor) const`
- L103 _public prototype_ `virtual const FSlateBrush* GetBackgroundImage(bool bIsHovered, bool bIsSelected) const;`
- L104 _public prototype_ `virtual FSlateColor GetBackgroundColor(bool bIsHovered, bool bIsSelected) const;`
- L106 _public prototype_ `virtual bool IsLoaded() const;`
- L109 _protected function_ `virtual TArray<TSharedRef<FRigVMTreeNode>> GetChildrenImpl(const TSharedRef<FRigVMTreeContext>& InContext) const`
- L113 _protected prototype_ `void AddChildImpl(const TSharedRef<FRigVMTreeNode>& InChild) const;`
- L114 _protected prototype_ `void UpdateChildren(const TSharedRef<FRigVMTreeContext>& InContext) const;`
- L115 _protected prototype_ `void UpdateVisibleChildren(const TSharedRef<FRigVMTreeContext>& InContext) const;`
- L116 _protected prototype_ `void DirtyVisibleParent() const;`
- L117 _protected prototype_ `bool ContainsAnyVisibleCheckedNode() const;`
- L119 _protected prototype_ `static TSharedPtr<FRigVMTreeNode> FindVisibleNodeInSet(const TArray<TSharedRef<FRigVMTreeNode>>& InNodes, const FString& InPath, const TSharedRef<FRigVMTreeContext>& InContext);`
- L121 _protected member_ `FString Path;`
- L122 _protected member_ `const FRigVMTreeNode* Parent = nullptr;`
- L123 _protected member_ `mutable TOptional<TArray<TSharedRef<FRigVMTreeNode>>> Children;`
- L124 _protected member_ `mutable uint32 VisibleChildrenHash = UINT32_MAX;`
- L125 _protected member_ `mutable TArray<TSharedRef<FRigVMTreeNode>> VisibleChildren;`
- L126 _protected member_ `mutable bool bIsDirtyingParent = false;`
- L127 _protected member_ `TOptional<ECheckBoxState> CheckState;`
- L128 _protected member_ `mutable TArray<FRigVMTag> Tags;`
- L130 _protected prototype_ `DECLARE_DELEGATE_OneParam(FRefreshDelegate, bool) FRefreshDelegate RefreshDelegate;`

#### class `FRigVMTreeRootNode`  
`class FRigVMTreeRootNode : public FRigVMTreeNode`  
_L143-154_
- inherits: `FRigVMTreeNode`
- desc: A Root Node is a node which can be placed only at the root of the tree.
- L147 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeRootNode, FRigVMTreeNode) FRigVMTreeRootNode();`
- L151 _public prototype_ `void AddChild(const TSharedRef<FRigVMTreeNode>& InNode);`
- L152 _public prototype_ `void RemoveChild(const TSharedRef<FRigVMTreeNode>& InNode);`
- L153 _public prototype_ `void SetChildren(const TArray<TSharedRef<FRigVMTreeNode>>& InNodes);`

#### class `FRigVMTreeCategoryNode`  
`class FRigVMTreeCategoryNode : public FRigVMTreeNode`  
_L160-172_
- inherits: `FRigVMTreeNode`
- desc: A Category Node is a node which presents itself as a category, providing a collapsed UI header.
- L163 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeCategoryNode, FRigVMTreeNode) FRigVMTreeCategoryNode(const FString& InPath) : FRigVMTreeNode(InPath)`
- L170 _public prototype_ `virtual const FSlateBrush* GetBackgroundImage(bool bIsHovered, bool bIsSelected) const override;`
- L171 _public prototype_ `virtual FSlateColor GetBackgroundColor(bool bIsHovered, bool bIsSelected) const override;`

#### class `FRigVMTreePackageNode`  
`class FRigVMTreePackageNode : public FRigVMTreeCategoryNode`  
_L178-202_
- inherits: `FRigVMTreeCategoryNode`
- desc: A Package Node is a special Category Node which reacts to the package being loaded and offers to update its content.
- L181 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreePackageNode, FRigVMTreeCategoryNode) FRigVMTreePackageNode(const FAssetData& InAssetData);`
- L185 _public prototype_ `virtual const FSlateBrush* GetIconAndTint(FLinearColor& OutColor) const override;`
- L186 _public prototype_ `virtual void Initialize() override;`
- L188 _public prototype_ `virtual FText GetLabel() const override;`
- L189 _public prototype_ `virtual bool IsLoaded() const override;`
- L190 _public prototype_ `virtual const TArray<FRigVMTag>& GetTags() const override;`
- L192 _public function_ `const FSoftObjectPath& GetPackagePath() const`
- L195 _protected prototype_ `void HandleAssetLoaded(UObject* InAsset);`
- L197 _protected member_ `mutable TOptional<bool> bIsLoaded;`
- L198 _protected member_ `FSoftObjectPath SoftObjectPath;`
- L199 _protected member_ `mutable FSlateIcon Icon;`
- L200 _protected member_ `mutable TOptional<const FSlateBrush*> IconBrush;`
- L201 _protected member_ `mutable bool bRetrievedTags;`

#### Free symbols / members of external scopes

- L130 _delegate_ `DECLARE_DELEGATE_OneParam(FRefreshDelegate, bool) FRefreshDelegate RefreshDelegate;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/RigVMTreeToolkitTask.h` (Public)


#### class `FRigVMTreeTask`  
`class FRigVMTreeTask : public FRigVMTreeElement`  
_L16-64_
- inherits: `FRigVMTreeElement`
- desc: A Task is a small piece of work that needs to be performed.
- L19 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeTask, FRigVMTreeElement) virtual bool Execute(const TSharedRef<FRigVMTreePhase>& InPhase)`
- L27 _public function_ `virtual URigVMBlueprint* GetBlueprint(const TSharedRef<FRigVMTreePhase>& InPhase) const` — `UE_DEPRECATED(5.7, "Please use FRigVMEditorAssetInterfacePtr GetRigVMAsset(const TSharedRef<FRigVMTreePhase>& InPhase) const")`
- L32 _public function_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAsset(const TSharedRef<FRigVMTreePhase>& InPhase) const`
- L37 _public function_ `virtual bool RequiresRefresh() const`
- L42 _public function_ `virtual bool RequiresUndo() const`
- L47 _public function_ `virtual TArray<FString> GetAffectedNodes() const`
- L52 _public function_ `void SetEnableUndo(bool bEnabled)`
- L57 _public function_ `bool IsUndoEnabled() const`
- L63 _private member_ `bool bEnableUndo = false;`

#### class `FRigVMTreeLoadPackageForNodeTask`  
`class FRigVMTreeLoadPackageForNodeTask : public FRigVMTreeTask`  
_L70-86_
- inherits: `FRigVMTreeTask`
- desc: The Load Package For Node Task will load a package related to a node given the node's path.
- L73 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeLoadPackageForNodeTask, FRigVMTreeTask) FRigVMTreeLoadPackageForNodeTask(const TSharedRef<FRigVMTreeNode>& InNode);`
- L77 _public prototype_ `virtual bool Execute(const TSharedRef<FRigVMTreePhase>& InPhase) override;`
- L79 _public function_ `virtual bool RequiresRefresh() const override`
- L85 _private member_ `FAssetData AssetData;`

#### class `FRigVMCompileBlueprintTask`  
`class FRigVMCompileBlueprintTask : public FRigVMTreeTask`  
_L92-109_
- inherits: `FRigVMTreeTask`
- desc: The Compile Blueprint Task is used to compile a blueprint related to a node in the tree (based on the node's path).
- L95 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMCompileBlueprintTask, FRigVMTreeTask) FRigVMCompileBlueprintTask(const TSharedRef<FRigVMTreeNode>& InNode);`
- L99 _public prototype_ `virtual bool Execute(const TSharedRef<FRigVMTreePhase>& InPhase) override;`
- L101 _public function_ `virtual bool RequiresRefresh() const override`
- L108 _private member_ `FSoftObjectPath ObjectPath;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMBulkEditDialog.h` (Public)


#### class `SRigVMBulkEditDialog`  
`template<typename InWidgetType = SRigVMBulkEditWidget> class SRigVMBulkEditDialog : public SWindow`  
_L11-89_
- inherits: `SWindow`
- L15 _public function_ `SLATE_BEGIN_ARGS(SRigVMBulkEditDialog) : _WindowSize(1200.0f, 1000.0f)`
- L18 _public prototype_ `SLATE_ARGUMENT(FVector2D, WindowSize) SLATE_ARGUMENT(typename InWidgetType::FArguments, WidgetArgs);`
- L20 _public function_ `SLATE_END_ARGS() TSharedRef<SRigVMBulkEditWidget> GetBulkEditWidget() const`
- L27 _public function_ `void Construct(const FArguments& InArgs)`
- L57 _public function_ `FText GetDialogTitle() const`
- L62 _public function_ `void ShowNormal()`
- L88 _private member_ `TSharedPtr<InWidgetType> Widget;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMBulkEditWidget.h` (Public)


#### class `SRigVMBulkEditWidget`  
`class SRigVMBulkEditWidget : public SCompoundWidget`  
_L17-122_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRigVMBulkEditWidget) : _EnableUndo(false) , _CloseOnSuccess(false) , _PhaseToActivate(INDEX_NONE) , _BulkEditConfirmIniField(TEXT("BulkEdit_Warning"))`
- L26 _public prototype_ `SLATE_ARGUMENT(bool, EnableUndo) SLATE_ARGUMENT(bool, CloseOnSuccess) SLATE_ARGUMENT(TArray<TSharedRef<FRigVMTreePhase>>, Phases) SLATE_ARGUMENT(int32, PhaseToActivate) SLATE_EVENT(FOnRigVMTreeNodeSelected, OnNodeSelected) SLATE_EVENT(FOnRigVMTreeNodeDoubleClicked, OnNodeDoubleClicked) SLATE_EVENT(FOnPhaseActivated, OnPhaseActivated) SLATE_ARGUMENT(TSharedPtr<SWidget>, HeaderWidget) SLATE_ARGUMENT(TSharedPtr<SWidget>, FooterWidget) SLATE_ARGUMENT(TSharedPtr<SWidget>, LeftWidget) SLATE_ARGUMENT(TSharedPtr<SWidget>, RightWidget) SLATE_ATTRIBUTE(FText, BulkEditTitle) SLATE_ATTRIBUTE(FText, BulkEditConfirmMessage) SLATE_ATTRIBUTE(FString, BulkEditConfirmIniField) SLATE_END_ARGS() virtual ~SRigVMBulkEditWidget() override;`
- L44 _public prototype_ `void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L48 _public prototype_ `FText GetDialogTitle() const;`
- L50 _public prototype_ `void QueueTasks(const TArray<TSharedRef<FRigVMTreeTask>>& InTasks);`
- L51 _public prototype_ `void CancelTasks();`
- L53 _public function_ `TSharedRef<SRigVMBulkEditWidget> GetBulkEditWidget()`
- L58 _public function_ `TSharedPtr<SRigVMChangesTreeView> GetTreeView()`
- L63 _public function_ `TSharedPtr<SRigVMLogWidget> GetLogWidget()`
- L68 _public prototype_ `TSharedPtr<FRigVMTreePhase> GetActivePhasePtr() const;`
- L69 _public prototype_ `TSharedRef<FRigVMTreePhase> GetActivePhase() const;`
- L70 _public prototype_ `TSharedPtr<FRigVMTreePhase> FindPhase(int32 InID) const;`
- L71 _public prototype_ `bool ActivatePhase(int32 InID);`
- L72 _public prototype_ `TSharedRef<FRigVMTreeContext> GetContext() const;`
- L74 _public prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetSelectedNodes() const;`
- L75 _public prototype_ `bool HasAnyVisibleCheckedNode() const;`
- L76 _public prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetCheckedNodes() const;`
- L78 _public prototype_ `FReply OnBackButtonClicked();`
- L79 _public prototype_ `FReply OnCancelButtonClicked();`
- L80 _public prototype_ `FReply OnPrimaryButtonClicked();`
- L82 _public prototype_ `void CloseDialog();`
- L86 _private member_ `TArray<TSharedRef<FRigVMTreePhase>> Phases;`
- L87 _private member_ `TArray<int32> ActivatedPhaseIDs;`
- L89 _private member_ `TSharedPtr<SRigVMChangesTreeView> TreeView;`
- L90 _private member_ `TSharedPtr<SRigVMLogWidget> BulkEditLogWidget;`
- L92 _private member_ `FOnPhaseActivated OnPhaseActivated;`
- L94 _private member_ `TAttribute<FText> BulkEditTitle;`
- L95 _private member_ `TAttribute<FText> BulkEditConfirmMessage;`
- L96 _private member_ `TAttribute<FString> BulkEditConfirmIniField;`
- L98 _private prototype_ `bool AreTasksInProgress() const;`
- L99 _private prototype_ `EVisibility GetTasksProgressVisibility() const;`
- L100 _private prototype_ `TOptional<float> GetTasksProgressPercentage() const;`
- L102 _private prototype_ `void OnLogMessage(const TSharedRef<FTokenizedMessage>& InMessage) const;`
- L103 _private prototype_ `void OnScriptException(ELogVerbosity::Type InVerbosity, const TCHAR* InMessage, const TCHAR* InStackMessage);`
- L105 _private member_ `mutable FCriticalSection TasksCriticalSection;`
- L106 _private member_ `TArray<TSharedRef<FRigVMTreeTask>> RemainingTasks;`
- L107 _private member_ `TArray<TSharedRef<FRigVMTreeTask>> CompletedTasks;`
- L108 _private member_ `bool bTasksSucceeded = false;`
- L109 _private member_ `bool bShowLog = false;`
- L110 _private member_ `bool bEnableUndo = false;`
- L111 _private member_ `bool bCloseOnSuccess = false;`
- L112 _private member_ `TSharedPtr<FScopedTransaction> Transaction;`
- L114 _private prototype_ `EVisibility GetBackButtonVisibility() const;`
- L115 _private prototype_ `bool IsBackButtonEnabled() const;`
- L116 _private prototype_ `EVisibility GetCancelButtonVisibility() const;`
- L117 _private prototype_ `bool IsCancelButtonEnabled() const;`
- L118 _private prototype_ `EVisibility GetPrimaryButtonVisibility() const;`
- L119 _private prototype_ `bool IsPrimaryButtonEnabled() const;`
- L120 _private prototype_ `FText GetPrimaryButtonText() const;`
- L121 _private prototype_ `bool IsReadyToClose() const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPhaseActivated, TSharedRef<FRigVMTreePhase>);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPhaseActivated, TSharedRef<FRigVMTreePhase>);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMChangesTreeView.h` (Public)


#### class `SRigVMChangesTreeRow`  
`class SRigVMChangesTreeRow : public STableRow<TSharedRef<FRigVMTreeNode>>`  
_L17-51_
- inherits: `STableRow<TSharedRef<FRigVMTreeNode>>`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRigVMChangesTreeRow)`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FRigVMTreeNode>, Node) SLATE_ARGUMENT(TSharedPtr<SRigVMChangesTreeView>, OwningWidget) SLATE_END_ARGS() virtual ~SRigVMChangesTreeRow() override;`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L33 _private prototype_ `EVisibility GetCheckBoxVisibility() const;`
- L34 _private prototype_ `ECheckBoxState GetCheckBoxState() const;`
- L35 _private prototype_ `void OnCheckBoxStateChanged(ECheckBoxState InNewState);`
- L36 _private prototype_ `const FSlateBrush* GetBackgroundImage() const;`
- L37 _private prototype_ `FSlateColor GetBackgroundColor() const;`
- L38 _private prototype_ `FOptionalSize GetIndentWidth() const;`
- L39 _private prototype_ `FSlateColor GetTextColor() const;`
- L40 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L41 _private prototype_ `FSlateColor GetIconColor() const;`
- L42 _private prototype_ `const FSlateBrush* GetExpanderImage() const;`
- L43 _private prototype_ `FReply OnExpanderMouseButtonDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);`
- L44 _private prototype_ `EVisibility GetExpanderVisibility() const;`
- L45 _private prototype_ `TArray<FRigVMTag> GetVariantTags() const;`
- L46 _private prototype_ `void RequestRefresh(bool bForce);`
- L48 _private member_ `TSharedPtr<FRigVMTreeNode> Node;`
- L49 _private member_ `SRigVMChangesTreeView* OwningWidget = nullptr;`
- L50 _private member_ `mutable TOptional<TArray<FRigVMTag>> Tags;`

#### class `SRigVMChangesTreeView`  
`class SRigVMChangesTreeView : public SCompoundWidget`  
_L56-127_
- inherits: `SCompoundWidget`
- L59 _public function_ `SLATE_BEGIN_ARGS(SRigVMChangesTreeView)`
- L61 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FRigVMTreePhase>, Phase) SLATE_EVENT(FOnRigVMTreeNodeSelected, OnNodeSelected) SLATE_EVENT(FOnRigVMTreeNodeDoubleClicked, OnNodeDoubleClicked) SLATE_END_ARGS() virtual ~SRigVMChangesTreeView() override;`
- L68 _public prototype_ `void Construct(const FArguments& InArgs);`
- L70 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L72 _public prototype_ `EVisibility GetPathFilterVisibility() const;`
- L73 _public prototype_ `void OnPathFilterTextChanged(const FText& SearchText);`
- L74 _public prototype_ `void OnPathFilterTextCommitted(const FText& SearchText, ETextCommit::Type CommitInfo);`
- L76 _public prototype_ `void RequestRefresh_AnyThread(bool bForce = false);`
- L77 _public prototype_ `void RefreshFilteredNodes(bool bForce = false);`
- L78 _public prototype_ `void RefreshFilteredNodesIfRequired();`
- L80 _public prototype_ `void OnPhaseChanged();`
- L81 _public prototype_ `void SetSelection(const TSharedPtr<FRigVMTreeNode>& InNode, bool bRequestScrollIntoView = false);`
- L83 _public function_ `TSharedPtr<STreeView<TSharedRef<FRigVMTreeNode>>> GetTreeView()`
- L88 _public prototype_ `TSharedRef<FRigVMTreePhase> GetPhase() const;`
- L89 _public prototype_ `TSharedRef<FRigVMTreeContext> GetContext() const;`
- L90 _public prototype_ `TSharedPtr<FRigVMTreePathFilter> GetPathFilter() const;`
- L92 _public prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetSelectedNodes() const;`
- L93 _public prototype_ `bool HasAnyVisibleCheckedNode() const;`
- L94 _public prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetCheckedNodes() const;`
- L98 _private member_ `TAttribute<TSharedPtr<FRigVMTreePhase>> PhaseAttribute;`
- L99 _private member_ `TArray<TSharedRef<FRigVMTreeNode>> FilteredNodes;`
- L101 _private prototype_ `FText GetPathFilterText();`
- L102 _private member_ `TSharedPtr<SSearchBox> PathFilterBox;`
- L104 _private member_ `TSharedPtr<STreeView<TSharedRef<FRigVMTreeNode>>> TreeView;`
- L106 _private member_ `FOnRigVMTreeNodeSelected OnNodeSelected;`
- L107 _private member_ `FOnRigVMTreeNodeDoubleClicked OnNodeDoubleClicked;`
- L109 _private member_ `TAttribute<FText> BulkEditTitle;`
- L110 _private member_ `TAttribute<FText> BulkEditConfirmMessage;`
- L111 _private member_ `TAttribute<FString> BulkEditConfirmIniField;`
- L113 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(TSharedRef<FRigVMTreeNode> InNode, const TSharedRef<STableViewBase>& OwnerTable);`
- L115 _private prototype_ `void GetChildrenForNode(TSharedRef<FRigVMTreeNode> InNode, TArray<TSharedRef<FRigVMTreeNode>>& OutChildren);`
- L116 _private prototype_ `void OnSelectionChanged(TSharedPtr<FRigVMTreeNode> Selection, ESelectInfo::Type SelectInfo);`
- L117 _private prototype_ `void OnTreeElementDoubleClicked(TSharedRef<FRigVMTreeNode> InNode);`
- L118 _private prototype_ `ESelectionMode::Type GetSelectionMode() const;`
- L120 _private prototype_ `TSharedPtr<SWidget> OnGetNodeContextMenuContent();`
- L122 _private prototype_ `EVisibility GetSettingsButtonVisibility() const;`
- L123 _private prototype_ `FReply OnSettingsButtonClicked();`
- L125 _private member_ `std::atomic<int32> RequestRefreshCount;`
- L126 _private member_ `std::atomic<int32> RequestRefreshForceCount;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply,FOnRigVMTreeNodeSelected,TSharedRef<FRigVMTreeNode>);`
- L53 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply,FOnRigVMTreeNodeSelected,TSharedRef<FRigVMTreeNode>);`
- L54 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply,FOnRigVMTreeNodeDoubleClicked,TSharedRef<FRigVMTreeNode>);`
- L54 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply,FOnRigVMTreeNodeDoubleClicked,TSharedRef<FRigVMTreeNode>);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMEditorGraphExplorer.h` (Public)


#### class `FRigVMGraphExplorerDragDropOp`  
`class FRigVMGraphExplorerDragDropOp : public FGraphEditorDragDropAction`  
_L33-67_
- inherits: `FGraphEditorDragDropAction`
- L36 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigVMExplorerDragDropOp, FGraphEditorDragDropAction) UE_DEPRECATED(5.7, "Please use New(const FRigVMExplorerElementKey& InElement, FRigVMEditorAssetInterfacePtr InBlueprint);") static TSharedRef<FRigVMGraphExplorerDragDropOp> New(const FRigVMExplorerElementKey& InElement, TObjectPtr<URigVMBlueprint> InBlueprint);`
- L40 _public prototype_ `static TSharedRef<FRigVMGraphExplorerDragDropOp> New(const FRigVMExplorerElementKey& InElement, FRigVMEditorAssetInterfacePtr InBlueprint);`
- L42 _public function_ `const FRigVMExplorerElementKey& GetElement() const`
- L48 _public function_ `TObjectPtr<URigVMBlueprint> GetBlueprint() const` — `UE_DEPRECATED(5.7, "Please use FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const")`
- L53 _public function_ `FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const`
- L58 _public prototype_ `virtual void Construct() override;`
- L60 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef<SWidget>& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L61 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L65 _private member_ `FRigVMExplorerElementKey Element;`
- L66 _private member_ `FRigVMEditorAssetInterfacePtr SourceBlueprint;`

#### class `FRigVMEditorGraphExplorerCommands`  
`class FRigVMEditorGraphExplorerCommands : public TCommands<FRigVMEditorGraphExplorerCommands>`  
_L69-89_
- inherits: `TCommands<FRigVMEditorGraphExplorerCommands>`
- L72 _public prototype_ `FRigVMEditorGraphExplorerCommands();`
- L74 _public member_ `TSharedPtr<FUICommandInfo> OpenGraph;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> OpenGraphInNewTab;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> CreateGraph;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> CreateFunction;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> CreateVariable;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> CreateLocalVariable;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> AddFunctionVariant;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> PasteFunction;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> PasteVariable;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> PasteLocalVariable;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> RemoveUnusedFunctions;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> RemoveUnusedVariables;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> FindReferences;`
- L88 _public prototype_ `void RegisterCommands() override;`

#### class `SRigVMEditorGraphExplorer`  
`class SRigVMEditorGraphExplorer : public SCompoundWidget`  
_L91-248_
- inherits: `SCompoundWidget`
- L94 _private typedef_ `using FRigVMEdGraphNodeRegistry = UE::RigVMEditor::FRigVMEdGraphNodeRegistry;`
- L97 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorGraphExplorer)`
- L98 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<IRigVMEditor> InRigVMEditor);`
- L103 _public prototype_ `void Refresh();` — Refresh the graph action menu.
- L106 _public prototype_ `void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget overrides
- L107 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L109 _public function_ `void SetLastPinTypeUsed(const FEdGraphPinType& InType)`
- L110 _public function_ `FEdGraphPinType GetLastPinTypeUsed() const`
- L112 _public prototype_ `FName GetSelectedVariableName() const;`
- L113 _public prototype_ `ERigVMExplorerElementType::Type GetSelectedType() const;`
- L115 _public prototype_ `void ClearSelection();`
- L118 _public function_ `const TSharedPtr<FRigVMEdGraphNodeRegistry>& GetEdGraphNodeFunctionRegistry() const` — Returns a registry for Ed Graph Nodes that hold RigVMFunctionReferenceNodes
- L121 _public function_ `const TSharedPtr<FRigVMEdGraphNodeRegistry>& GetEdGraphNodeVariableRegistry() const` — Returns a registry for Ed Graph Nodes that hold RigVMVariableNodes
- L123 _public prototype_ `void HandleGraphModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L126 _private member_ `bool bNeedsRefresh = true;`
- L128 _private member_ `FEdGraphPinType LastPinType;`
- L131 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Command list for widget-level keyboard shortcuts
- L133 _private prototype_ `void RegisterCommands();`
- L134 _private prototype_ `void CreateWidgets();`
- L137 _private prototype_ `TSharedRef<SWidget> CreateAddNewMenuWidget();` — Add new menu
- L138 _private prototype_ `void BuildAddNewMenu(FMenuBuilder& MenuBuilder);`
- L140 _private prototype_ `TArray<const URigVMGraph*> GetRootGraphs() const;`
- L141 _private prototype_ `TArray<const URigVMGraph*> GetChildrenGraphs(const FString& InParentGraphPath) const;`
- L142 _private prototype_ `TArray<URigVMNode*> GetEventNodesInGraph(const FString& InParentGraphPath) const;`
- L143 _private prototype_ `TArray<URigVMLibraryNode*> GetFunctions() const;`
- L144 _private prototype_ `TArray<FRigVMGraphVariableDescription> GetVariables() const;`
- L145 _private prototype_ `TArray<FRigVMGraphVariableDescription> GetLocalVariables() const;`
- L146 _private prototype_ `FText GetGraphDisplayName(const FString& InGraphPath) const;`
- L147 _private prototype_ `FText GetEventDisplayName(const FString& InNodePath) const;`
- L148 _private prototype_ `const FSlateBrush* GetGraphIcon(const FString& InGraphPath) const;`
- L149 _private prototype_ `FText GetGraphTooltip(const FString& InGraphPath) const;`
- L150 _private prototype_ `void OnGraphClicked(const FString& InGraphPath);`
- L151 _private prototype_ `void OnEventClicked(const FString& InEventPath);`
- L152 _private prototype_ `void OnFunctionClicked(const FString& InFunctionPath);`
- L153 _private prototype_ `void OnVariableClicked(const FRigVMExplorerElementKey& InVariable);`
- L154 _private prototype_ `void OnGraphDoubleClicked(const FString& InGraphPath);`
- L155 _private prototype_ `void OnEventDoubleClicked(const FString& InEventPath);`
- L156 _private prototype_ `void OnFunctionDoubleClicked(const FString& InFunctionPath);`
- L157 _private prototype_ `bool OnSetFunctionCategory(const FString& InFunctionPath, const FString& InCategory);`
- L158 _private prototype_ `FString OnGetFunctionCategory(const FString& InPath) const;`
- L159 _private prototype_ `FText OnGetFunctionTooltip(const FString& InFunctionPath) const;`
- L160 _private prototype_ `FText OnGetVariableTooltip(const FString& InVariable) const;`
- L161 _private prototype_ `bool OnSetVariableCategory(const FString& InVariable, const FString& InCategory);`
- L162 _private prototype_ `FString OnGetVariableCategory(const FString& InVariable) const;`
- L163 _private prototype_ `FEdGraphPinType OnGetVariablePinType(const FRigVMExplorerElementKey& InVariable);`
- L164 _private prototype_ `bool OnSetVariablePinType(const FRigVMExplorerElementKey& InVariable, const FEdGraphPinType& InType);`
- L165 _private prototype_ `bool OnIsVariablePublic(const FString& InVariableName) const;`
- L166 _private prototype_ `bool OnToggleVariablePublic(const FString& InVariableName) const;`
- L167 _private prototype_ `bool IsFunctionFocused() const;`
- L168 _private prototype_ `TArray<TSharedPtr<IPinTypeSelectorFilter>> GetCustomPinFilters() const;`
- L170 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L171 _private prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L173 _private prototype_ `void OnCopy();`
- L174 _private prototype_ `bool CanCopy() const;`
- L175 _private prototype_ `void OnCut();`
- L176 _private prototype_ `bool CanCut() const;`
- L177 _private prototype_ `void OnDuplicate();`
- L178 _private prototype_ `bool CanDuplicate() const;`
- L179 _private prototype_ `void OnPasteGeneric();`
- L180 _private prototype_ `bool CanPasteGeneric() const;`
- L181 _private prototype_ `void OnPasteFunction();`
- L182 _private prototype_ `bool CanPasteFunction() const;`
- L183 _private prototype_ `void OnPasteVariable();`
- L184 _private prototype_ `bool CanPasteVariable() const;`
- L185 _private prototype_ `void OnPasteLocalVariable();`
- L186 _private prototype_ `bool CanPasteLocalVariable() const;`
- L191 _private prototype_ `void OnToggleShowEmptySections();` — Support functions for view options for Show Empty Sections
- L192 _private prototype_ `bool IsShowingEmptySections() const;`
- L195 _private prototype_ `void OnOpenGraph(bool bOnNewTab = false);` — Command functions
- L196 _private prototype_ `bool CanOpenGraph() const;`
- L198 _private prototype_ `void OnCreateGraph();`
- L199 _private prototype_ `bool CanCreateGraph() const;`
- L201 _private prototype_ `void OnCreateFunction();`
- L202 _private prototype_ `bool CanCreateFunction() const;`
- L204 _private prototype_ `void OnCreateVariable();`
- L205 _private prototype_ `bool CanCreateVariable() const;`
- L207 _private prototype_ `void OnCreateLocalVariable();`
- L208 _private prototype_ `bool CanCreateLocalVariable() const;`
- L210 _private prototype_ `void OnAddFunctionVariant();`
- L211 _private prototype_ `bool CanAddFunctionVariant() const;`
- L213 _private prototype_ `void OnDeleteEntry();`
- L214 _private prototype_ `bool CanDeleteEntry() const;`
- L216 _private prototype_ `void OnRenameEntry();`
- L217 _private prototype_ `bool CanRenameEntry() const;`
- L218 _private prototype_ `bool OnRenameGraph(const FString& InOldPath, const FString& InNewPath);`
- L219 _private prototype_ `bool OnCanRenameGraph(const FString& InOldPath, const FString& InNewPath, FText& OutErrorMessage) const;`
- L220 _private prototype_ `bool OnRenameFunction(const FString& InOldPath, const FString& InNewPath);`
- L221 _private prototype_ `bool OnCanRenameFunction(const FString& InOldPath, const FString& InNewPath, FText& OutErrorMessage) const;`
- L222 _private prototype_ `bool OnRenameVariable(const FRigVMExplorerElementKey& InOldKey, const FString& InNewName);`
- L223 _private prototype_ `bool OnCanRenameVariable(const FRigVMExplorerElementKey& InOldKey, const FString& InNewName, FText& OutErrorMessage) const;`
- L224 _private prototype_ `bool OnReorderVariable(const FRigVMExplorerElementKey& InVariable, int32 NewIndex);`
- L225 _private prototype_ `bool OnReorderLocalVariable(const FRigVMExplorerElementKey& InVariable, int32 NewIndex);`
- L227 _private prototype_ `void OnFindReferences(const bool bSearchAllBlueprints);`
- L228 _private prototype_ `bool CanFindReferences() const;`
- L230 _private prototype_ `void OnRemoveUnusedFunctions();`
- L231 _private prototype_ `bool CanRemoveUnusedFunctions() const;`
- L232 _private prototype_ `void OnRemoveUnusedVariables();`
- L233 _private prototype_ `bool CanRemoveUnusedVariables() const;`
- L235 _private member_ `TWeakPtr<IRigVMEditor> RigVMEditor;`
- L237 _private member_ `TSharedPtr<SRigVMEditorGraphExplorerTreeView> TreeView;`
- L239 _private member_ `TSharedPtr<SSearchBox> FilterBox;`
- L242 _private member_ `TSharedPtr<FRigVMEdGraphNodeRegistry> EdGraphNodeFunctionRegistry;` — A registry for Ed Graph Nodes that hold URigVMFunctionReferenceNode
- L245 _private member_ `TSharedPtr<FRigVMEdGraphNodeRegistry> EdGraphNodeVariableRegistry;` — A registry for Ed Graph Nodes that hold RigVMVariableNodes
- L247 _private member_ `bool bShowEmptySections = true;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RigVMEditor` (scope `UE`)

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMEditorGraphExplorerTreeView.h` (Public)


#### enum `ERigVMExplorerElementType::Type`  
`enum Type`  
_L22-33_
- L24 _public enumerator_ `Invalid`
- L25 _public enumerator_ `Section`
- L26 _public enumerator_ `FunctionCategory`
- L27 _public enumerator_ `VariableCategory`
- L28 _public enumerator_ `Graph`
- L29 _public enumerator_ `Event`
- L30 _public enumerator_ `Function`
- L31 _public enumerator_ `Variable`
- L32 _public enumerator_ `LocalVariable`

#### enum `ERigVMGraphExplorerSectionType`  
`enum class ERigVMGraphExplorerSectionType : uint8`  
_L37-44_
- desc: The type of section in the graph explorer
- L39 _public enumerator_ `None`
- L40 _public enumerator_ `Graphs`
- L41 _public enumerator_ `Functions`
- L42 _public enumerator_ `Variables`
- L43 _public enumerator_ `LocalVariables`

#### struct `FRigVMExplorerElementKey`  
`struct FRigVMExplorerElementKey`  
_L46-67_
- L49 _public function_ `FRigVMExplorerElementKey() : Type(ERigVMExplorerElementType::Invalid), Name(FString())`
- L52 _public function_ `FRigVMExplorerElementKey(const ERigVMExplorerElementType::Type& InType, const FString& InName) : Type(InType), Name(InName)`
- L55 _public member_ `ERigVMExplorerElementType::Type Type;`
- L56 _public member_ `FString Name;`

#### struct `FRigVMEditorGraphExplorerTreeDelegates`  
`struct FRigVMEditorGraphExplorerTreeDelegates`  
_L112-524_
- L115 _public member_ `FRigVMGraphExplorer_OnGetRootGraphs OnGetRootGraphs;`
- L116 _public member_ `FRigVMGraphExplorer_OnGetChildrenGraphs OnGetChildrenGraphs;`
- L117 _public member_ `FRigVMGraphExplorer_OnGetEventNodesInGraph OnGetEventNodesInGraph;`
- L118 _public member_ `FRigVMGraphExplorer_OnGetFunctions OnGetFunctions;`
- L119 _public member_ `FRigVMGraphExplorer_OnGetVariables OnGetVariables;`
- L120 _public member_ `FRigVMGraphExplorer_OnGetVariables OnGetLocalVariables;`
- L121 _public member_ `FRigVMGraphExplorer_OnIsFunctionFocused OnIsFunctionFocused;`
- L122 _public member_ `FRigVMGraphExplorer_OnGetGraphDisplayName OnGetGraphDisplayName;`
- L123 _public member_ `FRigVMGraphExplorer_OnGetGraphDisplayName OnGetEventDisplayName;`
- L124 _public member_ `FRigVMGraphExplorer_OnGetGraphTooltip OnGetGraphTooltip;`
- L125 _public member_ `FRigVMGraphExplorer_OnGetGraphIcon OnGetGraphIcon;`
- L126 _public member_ `FRigVMGraphExplorer_OnGraphClicked OnGraphClicked;`
- L127 _public member_ `FRigVMGraphExplorer_OnEventClicked OnEventClicked;`
- L128 _public member_ `FRigVMGraphExplorer_OnFunctionClicked OnFunctionClicked;`
- L129 _public member_ `FRigVMGraphExplorer_OnVariableClicked OnVariableClicked;`
- L130 _public member_ `FRigVMGraphExplorer_OnGraphDoubleClicked OnGraphDoubleClicked;`
- L131 _public member_ `FRigVMGraphExplorer_OnEventDoubleClicked OnEventDoubleClicked;`
- L132 _public member_ `FRigVMGraphExplorer_OnFunctionDoubleClicked OnFunctionDoubleClicked;`
- L133 _public member_ `FRigVMGraphExplorer_OnCreateGraph OnCreateGraph;`
- L134 _public member_ `FRigVMGraphExplorer_OnCreateFunction OnCreateFunction;`
- L135 _public member_ `FRigVMGraphExplorer_OnCreateVariable OnCreateVariable;`
- L136 _public member_ `FRigVMGraphExplorer_OnCreateVariable OnCreateLocalVariable;`
- L137 _public member_ `FRigVMGraphExplorer_OnRenameGraph OnRenameGraph;`
- L138 _public member_ `FRigVMGraphExplorer_OnCanRenameGraph OnCanRenameGraph;`
- L139 _public member_ `FRigVMGraphExplorer_OnRenameFunction OnRenameFunction;`
- L140 _public member_ `FRigVMGraphExplorer_OnCanRenameFunction OnCanRenameFunction;`
- L141 _public member_ `FRigVMGraphExplorer_OnRenameVariable OnRenameVariable;`
- L142 _public member_ `FRigVMGraphExplorer_OnCanRenameVariable OnCanRenameVariable;`
- L143 _public member_ `FRigVMGraphExplorer_OnSetFunctionCategory OnSetFunctionCategory;`
- L144 _public member_ `FRigVMGraphExplorer_OnGetFunctionCategory OnGetFunctionCategory;`
- L145 _public member_ `FRigVMGraphExplorer_OnGetFunctionTooltip OnGetFunctionTooltip;`
- L146 _public member_ `FRigVMGraphExplorer_OnGetVariableTooltip OnGetVariableTooltip;`
- L147 _public member_ `FRigVMGraphExplorer_OnSetVariableCategory OnSetVariableCategory;`
- L148 _public member_ `FRigVMGraphExplorer_OnGetVariableCategory OnGetVariableCategory;`
- L149 _public member_ `FRigVMGraphExplorer_OnGetVariablePinType OnGetVariablePinType;`
- L150 _public member_ `FRigVMGraphExplorer_OnSetVariablePinType OnSetVariablePinType;`
- L151 _public member_ `FRigVMGraphExplorer_OnIsVariablePublic OnIsVariablePublic;`
- L152 _public member_ `FRigVMGraphExplorer_OnToggleVariablePublic OnToggleVariablePublic;`
- L153 _public member_ `FRigVMGraphExplorer_OnGetCustomPinFilters OnGetCustomPinFilters;`
- L154 _public member_ `FRigVMGraphExplorer_OnReorderVariable OnReorderVariable;`
- L155 _public member_ `FRigVMGraphExplorer_OnReorderVariable OnReorderLocalVariable;`
- L157 _public member_ `FRigVMGraphExplorer_OnSelectionChanged OnSelectionChanged;`
- L158 _public member_ `FRigVMGraphExplorer_OnRequestContextMenu OnRequestContextMenu;`
- L159 _public member_ `FOnDragDetected OnDragDetected;`
- L161 _public function_ `FRigVMEditorGraphExplorerTreeDelegates()`
- L165 _public function_ `TArray<const URigVMGraph*> GetRootGraphs() const`
- L174 _public function_ `TArray<const URigVMGraph*> GetChildrenGraphs(const FString& InParentPath) const`
- L183 _public function_ `TArray<URigVMNode*> GetEventNodesInGraph(const FString& InParentPath) const`
- L192 _public function_ `TArray<URigVMLibraryNode*> GetFunctions() const`
- L201 _public function_ `TArray<FRigVMGraphVariableDescription> GetVariables() const`
- L210 _public function_ `TArray<FRigVMGraphVariableDescription> GetLocalVariables() const`
- L219 _public function_ `bool IsFunctionFocused() const`
- L228 _public function_ `FText GetGraphDisplayName(const FString& InPath) const`
- L237 _public function_ `FText GetEventDisplayName(const FString& InPath) const`
- L246 _public function_ `FText GetGraphTooltip(const FString& InPath) const`
- L255 _public function_ `const FSlateBrush* GetGraphIcon(const FString& InPath) const`
- L264 _public function_ `void GraphClicked(const FString& InPath) const`
- L272 _public function_ `void EventClicked(const FString& InPath) const`
- L280 _public function_ `void FunctionClicked(const FString& InPath) const`
- L288 _public function_ `void VariableClicked(const FRigVMExplorerElementKey& InVariable) const`
- L296 _public function_ `void GraphDoubleClicked(const FString& InPath) const`
- L304 _public function_ `void EventDoubleClicked(const FString& InPath) const`
- L312 _public function_ `void FunctionDoubleClicked(const FString& InPath) const`
- L320 _public function_ `void CreateGraph() const`
- L328 _public function_ `void CreateFunction() const`
- L336 _public function_ `void CreateVariable() const`
- L344 _public function_ `void CreateLocalVariable() const`
- L352 _public function_ `void RenameGraph(const FString& InOldPath, const FString& InNewPath) const`
- L360 _public function_ `bool CanRenameGraph(const FString& InOldPath, const FString& InNewPath, FText& OutErrorMessage) const`
- L369 _public function_ `void RenameFunction(const FString& InOldPath, const FString& InNewPath) const`
- L377 _public function_ `bool CanRenameFunction(const FString& InOldPath, const FString& InNewPath, FText& OutErrorMessage) const`
- L386 _public function_ `void RenameVariable(const FRigVMExplorerElementKey& InOldKey, const FString& InNewName) const`
- L394 _public function_ `bool CanRenameVariable(const FRigVMExplorerElementKey& InOldKey, const FString& InNewName, FText& OutErrorMessage) const`
- L403 _public function_ `void SetFunctionCategory(const FString& InPath, const FString& InCategory) const`
- L411 _public function_ `FString GetFunctionCategory(const FString& InPath) const`
- L420 _public function_ `FText GetFunctionTooltip(const FString& InPath) const`
- L429 _public function_ `FText GetVariableTooltip(const FString& InPath) const`
- L438 _public function_ `void SetVariableCategory(const FString& InPath, const FString& InCategory) const`
- L446 _public function_ `FString GetVariableCategory(const FString& InPath) const`
- L455 _public function_ `void HandleSelectionChanged(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> Selection, ESelectInfo::Type SelectInfo)`
- L465 _public function_ `TSharedPtr<SWidget> RequestContextMenu()`
- L474 _public function_ `FEdGraphPinType GetVariablePinType(const FRigVMExplorerElementKey& InVariableKey)`
- L483 _public function_ `bool SetVariablePinType(const FRigVMExplorerElementKey& InVariableKey, const FEdGraphPinType& InType)`
- L492 _public function_ `bool IsVariablePublic(const FString& InVariable)`
- L501 _public function_ `bool ToggleVariablePublic(const FString& InVariable)`
- L510 _public function_ `TArray<TSharedPtr<IPinTypeSelectorFilter>> GetCustomPinFilters()`
- L521 _private member_ `bool bSuspendSelectionDelegate = false;`

#### class `SRigVMEditorGraphExplorerItem`  
`class SRigVMEditorGraphExplorerItem : public STableRow<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>`  
_L526-571_
- inherits: `STableRow<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>`
- L528 _private prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnAddClickedOnSection, const FRigVMExplorerElementKey&);`
- L530 _private typedef_ `using FRigVMEdGraphNodeRegistry = UE::RigVMEditor::FRigVMEdGraphNodeRegistry;`
- L533 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorGraphExplorerItem)`
- L535 _public prototype_ `SLATE_EVENT( FOnAddClickedOnSection, OnAddClickedOnSection ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRigVMEditorGraphExplorerTreeElement> InElement, TSharedPtr<SRigVMEditorGraphExplorerTreeView> InTreeView);`
- L543 _public prototype_ `TSharedRef<SWidget> CreateIconWidget(const FRigVMExplorerElementKey& Key);`
- L544 _public prototype_ `TSharedRef<SWidget> CreateTextSlotWidget(const FRigVMExplorerElementKey& Key, const FText& InHighlightText);`
- L545 _public prototype_ `FText GetDisplayText() const;`
- L546 _public prototype_ `FText GetItemTooltip() const;`
- L547 _public prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L548 _public prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;`
- L549 _public prototype_ `FReply OnAddButtonClickedOnSection(TSharedRef<FRigVMEditorGraphExplorerTreeElement> InElement);`
- L552 _public prototype_ `virtual TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRigVMEditorGraphExplorerTreeElement> TargetItem);` — Drag and drop support for reordering
- L553 _public prototype_ `virtual FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRigVMEditorGraphExplorerTreeElement> TargetItem);`
- L557 _private prototype_ `void UpdateIsUsedInGraph();` — Updates OptionalIsUsedInGraph
- L560 _private prototype_ `TSharedPtr<FRigVMEdGraphNodeRegistry> GetEdGraphNodeRegistry() const;` — Returns a registry for ed graph nodes this item uses, or nullptr if no registry exists
- L562 _private member_ `TWeakPtr<FRigVMEditorGraphExplorerTreeElement> WeakExplorerElement;`
- L563 _private member_ `TWeakPtr<SRigVMEditorGraphExplorerTreeView> WeakTreeView;`
- L564 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineRenameWidget;`
- L565 _private member_ `FRigVMEditorGraphExplorerTreeDelegates Delegates;`
- L568 _private member_ `TOptional<bool> OptionalIsUsedInGraph;` — If set and true, there are occurences in the graph. Only set for supported types (functions and variables as of 5.7)
- L570 _private member_ `FOnAddClickedOnSection OnAddClickedOnSection;`

#### class `FRigVMEditorGraphExplorerTreeElement`  
`class FRigVMEditorGraphExplorerTreeElement : public TSharedFromThis<FRigVMEditorGraphExplorerTreeElement>`  
_L575-592_
- inherits: `TSharedFromThis<FRigVMEditorGraphExplorerTreeElement>`
- desc: An item in the tree
- L578 _public function_ `FRigVMEditorGraphExplorerTreeElement(const FRigVMExplorerElementKey& InKey, TWeakPtr<SRigVMEditorGraphExplorerTreeView> InTreeView) : Key(InKey)`
- L581 _public member_ `FRigVMExplorerElementKey Key;`
- L582 _public member_ `TArray<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>> Children;`
- L584 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRigVMEditorGraphExplorerTreeElement> InRigTreeElement, TSharedPtr<SRigVMEditorGraphExplorerTreeView> InTreeView);`
- L586 _public prototype_ `void RequestRename();`
- L589 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L590 _public member_ `FOnRenameRequested OnRenameRequested;`

#### class `SRigVMEditorGraphExplorerTreeView`  
`class SRigVMEditorGraphExplorerTreeView : public STreeView<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>`  
_L594-683_
- inherits: `STreeView<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>`
- L596 _private typedef_ `using FRigVMEdGraphNodeRegistry = UE::RigVMEditor::FRigVMEdGraphNodeRegistry;`
- L600 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorGraphExplorerTreeView)`
- L602 _public prototype_ `SLATE_ARGUMENT(FRigVMEditorGraphExplorerTreeDelegates, RigTreeDelegates) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRigVMEditorGraphExplorer>& InGraphExplorer);`
- L606 _public prototype_ `virtual ~SRigVMEditorGraphExplorerTreeView() = default;`
- L609 _public function_ `void SaveAndClearSparseItemInfos()` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L620 _public function_ `void RestoreSparseItemInfos(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> ItemPtr)` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L633 _public prototype_ `void RefreshTreeView(bool bRebuildContent = true);`
- L634 _public prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L635 _public prototype_ `TSharedPtr< SWidget > CreateContextMenu();`
- L636 _public prototype_ `void SetExpansionRecursive(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L637 _public prototype_ `void HandleGetChildrenForTree(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> InItem, TArray<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>& OutChildren);`
- L638 _public prototype_ `TArray<FRigVMExplorerElementKey> GetKeys() const;`
- L639 _public prototype_ `TArray<FRigVMExplorerElementKey> GetSelectedKeys() const;`
- L640 _public prototype_ `void SetSelection(TArray<FRigVMExplorerElementKey>& InSelectedKeys);`
- L641 _public prototype_ `TSharedPtr<FRigVMEditorGraphExplorerTreeElement> FindElement(const FRigVMExplorerElementKey& Key);`
- L643 _public function_ `const TArray<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>& GetRootElements() const`
- L644 _public function_ `FRigVMEditorGraphExplorerTreeDelegates& GetRigTreeDelegates()`
- L645 _public prototype_ `void OnItemClicked(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> InElement);`
- L646 _public prototype_ `void OnItemDoubleClicked(TSharedPtr<FRigVMEditorGraphExplorerTreeElement> InElement);`
- L647 _public prototype_ `FReply OnAddButtonClickedOnSection(const FRigVMExplorerElementKey& InSectionKey);`
- L650 _public prototype_ `ERigVMGraphExplorerSectionType GetSectionType(const FRigVMExplorerElementKey& Key) const;` — Returns the type of section the key references, or ERigVMGraphExplorerSectionType::None if the key doesn't reference a section.
- L653 _public prototype_ `TSharedPtr<SRigVMEditorGraphExplorer> GetGraphExplorer() const;` — Returns the outer graph explorer or nullptr if there is no valid outer graph explorer
- L658 _private prototype_ `bool IsVariableElementUsedInGraph(const TSharedRef<FRigVMEditorGraphExplorerTreeElement>& Element) const;` — Returns true if the eleemnt refers to a variable used in the graph. The element's key type has to correspond to a variable (ensured)
- L661 _private member_ `TSparseItemMap OldSparseItemInfos;` — A temporary snapshot of the SparseItemInfos in STreeView, used during RefreshTreeView()
- L664 _private member_ `TArray<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>> RootElements;` — Backing array for tree view
- L667 _private member_ `TMap<FRigVMExplorerElementKey, TSharedPtr<FRigVMEditorGraphExplorerTreeElement>> ElementMap;` — A map for looking up items based on their key
- L670 _private member_ `TMap<FRigVMExplorerElementKey, FRigVMExplorerElementKey> ParentMap;` — A map for looking up a parent based on their key
- L672 _private member_ `FRigVMEditorGraphExplorerTreeDelegates Delegates;`
- L674 _private member_ `FText FilterText;`
- L677 _private member_ `TWeakPtr<SRigVMEditorGraphExplorer> WeakGraphExplorer;` — The outer graph explorer widget
- L679 _private member_ `bool bWasAddNewItemClicked = false;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L20 _namespace_ `namespace ERigVMExplorerElementType`
- L58 _function_ `friend bool operator==(const FRigVMExplorerElementKey& A, const FRigVMExplorerElementKey& B)`
- L63 _function_ `friend uint32 GetTypeHash(const FRigVMExplorerElementKey& Key)`
- L70 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<const URigVMGraph*>, FRigVMGraphExplorer_OnGetRootGraphs);`
- L70 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<const URigVMGraph*>, FRigVMGraphExplorer_OnGetRootGraphs);`
- L71 _delegate_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateGraph);`
- L71 _prototype_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateGraph);`
- L72 _delegate_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateFunction);`
- L72 _prototype_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateFunction);`
- L73 _delegate_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateVariable);`
- L73 _prototype_ `DECLARE_DELEGATE( FRigVMGraphExplorer_OnCreateVariable);`
- L74 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<const URigVMGraph*>, FRigVMGraphExplorer_OnGetChildrenGraphs, const FString&);`
- L74 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<const URigVMGraph*>, FRigVMGraphExplorer_OnGetChildrenGraphs, const FString&);`
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<URigVMNode*>, FRigVMGraphExplorer_OnGetEventNodesInGraph, const FString&);`
- L75 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<URigVMNode*>, FRigVMGraphExplorer_OnGetEventNodesInGraph, const FString&);`
- L76 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<URigVMLibraryNode*>, FRigVMGraphExplorer_OnGetFunctions);`
- L76 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<URigVMLibraryNode*>, FRigVMGraphExplorer_OnGetFunctions);`
- L77 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMGraphVariableDescription>, FRigVMGraphExplorer_OnGetVariables);`
- L77 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMGraphVariableDescription>, FRigVMGraphExplorer_OnGetVariables);`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FRigVMGraphExplorer_OnIsFunctionFocused);`
- L78 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FRigVMGraphExplorer_OnIsFunctionFocused);`
- L79 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetGraphDisplayName, const FString&);`
- L79 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetGraphDisplayName, const FString&);`
- L80 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetEventDisplayName, const FString&);`
- L80 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetEventDisplayName, const FString&);`
- L81 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetGraphTooltip, const FString&);`
- L81 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetGraphTooltip, const FString&);`
- L82 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FRigVMGraphExplorer_OnGetGraphIcon, const FString&);`
- L82 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FRigVMGraphExplorer_OnGetGraphIcon, const FString&);`
- L83 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnGraphClicked, const FString&);`
- L83 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnGraphClicked, const FString&);`
- L84 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnEventClicked, const FString&);`
- L84 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnEventClicked, const FString&);`
- L85 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnFunctionClicked, const FString&);`
- L85 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnFunctionClicked, const FString&);`
- L86 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnVariableClicked, const FRigVMExplorerElementKey&);`
- L86 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnVariableClicked, const FRigVMExplorerElementKey&);`
- L87 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnGraphDoubleClicked, const FString&);`
- L87 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnGraphDoubleClicked, const FString&);`
- L88 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnEventDoubleClicked, const FString&);`
- L88 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnEventDoubleClicked, const FString&);`
- L89 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnFunctionDoubleClicked, const FString&);`
- L89 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMGraphExplorer_OnFunctionDoubleClicked, const FString&);`
- L90 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameGraph, const FString&, const FString&);`
- L90 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameGraph, const FString&, const FString&);`
- L91 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameFunction, const FString&, const FString&);`
- L91 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameFunction, const FString&, const FString&);`
- L92 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameVariable, const FRigVMExplorerElementKey&, const FString&);`
- L92 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnRenameVariable, const FRigVMExplorerElementKey&, const FString&);`
- L93 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameGraph, const FString&, const FString&, FText&);`
- L93 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameGraph, const FString&, const FString&, FText&);`
- L94 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameFunction, const FString&, const FString&, FText&);`
- L94 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameFunction, const FString&, const FString&, FText&);`
- L95 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameVariable, const FRigVMExplorerElementKey&, const FString&, FText&);`
- L95 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMGraphExplorer_OnCanRenameVariable, const FRigVMExplorerElementKey&, const FString&, FText&);`
- L96 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetFunctionCategory, const FString&, const FString&);`
- L96 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetFunctionCategory, const FString&, const FString&);`
- L97 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMGraphExplorer_OnGetFunctionCategory, const FString&);`
- L97 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMGraphExplorer_OnGetFunctionCategory, const FString&);`
- L98 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetFunctionTooltip, const FString&);`
- L98 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetFunctionTooltip, const FString&);`
- L99 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetVariableTooltip, const FString&);`
- L99 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FRigVMGraphExplorer_OnGetVariableTooltip, const FString&);`
- L100 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetVariableCategory, const FString&, const FString&);`
- L100 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetVariableCategory, const FString&, const FString&);`
- L101 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMGraphExplorer_OnGetVariableCategory, const FString&);`
- L101 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMGraphExplorer_OnGetVariableCategory, const FString&);`
- L102 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FRigVMGraphExplorer_OnRequestContextMenu);`
- L102 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FRigVMGraphExplorer_OnRequestContextMenu);`
- L103 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FEdGraphPinType, FRigVMGraphExplorer_OnGetVariablePinType, const FRigVMExplorerElementKey&);`
- L103 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FEdGraphPinType, FRigVMGraphExplorer_OnGetVariablePinType, const FRigVMExplorerElementKey&);`
- L104 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetVariablePinType, const FRigVMExplorerElementKey&, const FEdGraphPinType&);`
- L104 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnSetVariablePinType, const FRigVMExplorerElementKey&, const FEdGraphPinType&);`
- L105 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMGraphExplorer_OnIsVariablePublic, const FString&);`
- L105 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMGraphExplorer_OnIsVariablePublic, const FString&);`
- L106 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMGraphExplorer_OnToggleVariablePublic, const FString&);`
- L106 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMGraphExplorer_OnToggleVariablePublic, const FString&);`
- L107 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<TSharedPtr<IPinTypeSelectorFilter>>, FRigVMGraphExplorer_OnGetCustomPinFilters);`
- L107 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<TSharedPtr<IPinTypeSelectorFilter>>, FRigVMGraphExplorer_OnGetCustomPinFilters);`
- L108 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnReorderVariable, const FRigVMExplorerElementKey&, int32 );`
- L108 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMGraphExplorer_OnReorderVariable, const FRigVMExplorerElementKey&, int32 );`
- L110 _typedef_ `typedef STreeView<TSharedPtr<FRigVMEditorGraphExplorerTreeElement>>::FOnSelectionChanged FRigVMGraphExplorer_OnSelectionChanged;`
- L528 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnAddClickedOnSection, const FRigVMExplorerElementKey&);`
- L589 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMEditorSelectedDebugObjectWidget.h` (Public)


#### struct `FRigVMDebugObjectInstance`  
`struct FRigVMDebugObjectInstance`  
_L10-47_
- L13 _public member_ `TWeakObjectPtr<UObject> ObjectPtr;` — Actual object to debug, can be null
- L16 _public member_ `FString ObjectLabel;` — Friendly label for object to debug
- L19 _public member_ `FString ObjectPath;` — Raw object path of spawned PIE object, this is not a SoftObjectPath because we don't want it to get fixed up
- L22 _public member_ `FString EditorObjectPath;` — Object path to object in the editor, will only be set for static objects
- L24 _public function_ `FRigVMDebugObjectInstance(TWeakObjectPtr<UObject> InPtr, const FString& InLabel) : ObjectPtr(InPtr) , ObjectLabel(InLabel)`
- L31 _public function_ `bool IsEmptyObject() const` — Returns true if this is the special entry for no specific object
- L37 _public function_ `bool IsSpawnedObject() const` — If this has no editor path, it was spawned
- L43 _public function_ `bool IsEditorObject() const` — If editor and object path are the same length because there's no prefix, this is the editor object

#### class `SRigVMEditorSelectedDebugObjectWidget`  
`class SRigVMEditorSelectedDebugObjectWidget : public SCompoundWidget`  
_L49-129_
- inherits: `SCompoundWidget`
- L52 _public function_ `SLATE_BEGIN_ARGS(SRigVMEditorSelectedDebugObjectWidget)`
- L53 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IRigVMEditor> InEditor);`
- L58 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L62 _public prototype_ `void AddDebugObject(UObject* TestObject, const FString& TestObjectName = FString());` — Adds an object to the list of debug choices
- L65 _private prototype_ `FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const;`
- L68 _private prototype_ `void GenerateDebugObjectInstances(bool bRestoreSelection);` — Creates a list of all debug objects
- L71 _private prototype_ `void GenerateDebugWorldNames(bool bRestoreSelection);` — Generate list of active PIE worlds to debug
- L74 _private prototype_ `void OnRefresh();` — Refresh the widget.
- L77 _private prototype_ `TSharedPtr<FRigVMDebugObjectInstance> GetDebugObjectInstance() const;` — Returns the entry for the current debug actor
- L80 _private prototype_ `TSharedPtr<FString> GetDebugWorldName() const;` — Returns the name of the current debug actor
- L83 _private prototype_ `void DebugObjectSelectionChanged(TSharedPtr<FRigVMDebugObjectInstance> NewSelection, ESelectInfo::Type SelectInfo);` — Handles the selection changed event for the debug actor combo box
- L85 _private prototype_ `void DebugWorldSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L88 _private prototype_ `void SelectedDebugObject_OnClicked();` — Called when user clicks button to select the current object being debugged
- L91 _private prototype_ `bool IsDebugObjectSelected() const;` — Returns true if a debug actor is currently selected
- L93 _private prototype_ `EVisibility IsDebugWorldComboVisible() const;`
- L96 _private prototype_ `const FString& GetNoDebugString() const;` — Returns the string to indicate no debug object is selected
- L98 _private prototype_ `const FString& GetDebugAllWorldsString() const;`
- L101 _private prototype_ `FString MakeDebugObjectLabel(UObject* TestObject, bool bAddContextIfSelectedInEditor, bool bAddSpawnedContext) const;` — Helper method to construct a debug object label string
- L104 _private prototype_ `void FillDebugObjectInstance(TSharedPtr<FRigVMDebugObjectInstance> Instance);` — Fills in data for a specific instance
- L107 _private prototype_ `TSharedRef<SWidget> CreateDebugObjectItemWidget(TSharedPtr<FRigVMDebugObjectInstance> InItem);` — Called to create a widget for each debug object item
- L110 _private prototype_ `FText GetSelectedDebugObjectTextLabel() const;` — Returns the combo button label to use for the currently-selected debug object item
- L114 _private member_ `TWeakPtr<IRigVMEditor> Editor;` — Pointer back to the rigvm editor tool that owns us
- L117 _private member_ `TArray<TSharedPtr<FRigVMDebugObjectInstance>> DebugObjects;` — Lists of actors of a given blueprint type and their names
- L120 _private member_ `TArray< TWeakObjectPtr<UWorld> > DebugWorlds;` — PIE worlds that we can debug
- L121 _private member_ `TArray< TSharedPtr<FString> > DebugWorldNames;`
- L124 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FRigVMDebugObjectInstance>>> DebugObjectsComboBox;` — Widget containing the names of all possible debug actors. This is a "generic" SComboBox rather than an STextComboBox so that we can customize the label on the combo button widget.
- L126 _private member_ `TSharedPtr<STextComboBox> DebugWorldsComboBox;`
- L128 _private member_ `TWeakObjectPtr<UObject> LastObjectObserved;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMExecutionStackView.h` (Public)


#### enum `ERigStackEntry::Type`  
`enum Type`  
_L22-30_
- L24 _public enumerator_ `Error`
- L25 _public enumerator_ `Warning`
- L26 _public enumerator_ `Info`
- L27 _public enumerator_ `Callable`
- L28 _public enumerator_ `Instruction`
- L29 _public enumerator_ `Block`

#### class `FRigStackEntry`  
`class FRigStackEntry : public TSharedFromThis<FRigStackEntry>`  
_L34-71_
- inherits: `TSharedFromThis<FRigStackEntry>`
- desc: An item in the stack
- L37 _public prototype_ `FRigStackEntry(int32 InEntryIndex, ERigStackEntry::Type InEntryType, int32 InSubjectIndex, ERigVMOpCode InOpCode, const FString& InLabel, const FRigVMASTProxy& InProxy);`
- L40 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRigStackEntry> InEntry, TSharedRef<FUICommandList> InCommandList, TSharedPtr<SRigVMExecutionStackView> InStackView, TWeakObjectPtr<UObject> InBlueprint);` — `UE_DEPRECATED(5.7, "Use TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRigStackEntry> InEntry, TSharedRef<FUICommandList> InCommandList, TSharedPtr<SRigVMExecutionStackView> InStackView, TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint); instead")`
- L54 _public prototype_ `void FilterChildren(const FString& InSearchText);`
- L55 _public prototype_ `bool MatchesFilter(const FString& InSearchText);`
- L57 _public member_ `int32 EntryIndex;`
- L58 _public member_ `ERigStackEntry::Type EntryType;`
- L59 _public member_ `int32 SubjectIndex;`
- L60 _public member_ `FString CallPath;`
- L61 _public member_ `FRigVMCallstack Callstack;`
- L62 _public member_ `ERigVMOpCode OpCode;`
- L63 _public member_ `FString Label;`
- L64 _public member_ `TArray<TSharedPtr<FRigStackEntry>> Children;`
- L65 _public member_ `TOptional<TArray<TSharedPtr<FRigStackEntry>>> FilteredChildren;`
- L66 _public member_ `mutable TOptional<bool> ShowAsFadedOut;`
- L67 _public member_ `mutable TOptional<FText> VisitedCountText;`
- L68 _public member_ `mutable TOptional<FText> DurationText;`
- L69 _public member_ `mutable double MicroSeconds;`
- L70 _public member_ `mutable TArray<double> MicroSecondsFrames;`

#### class `SRigStackItem`  
`class SRigStackItem : public STableRow<TSharedPtr<FRigStackEntry>>`  
_L73-91_
- inherits: `STableRow<TSharedPtr<FRigStackEntry>>`
- L75 _private function_ `SLATE_BEGIN_ARGS(SRigStackItem)`
- L76 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FRigStackEntry> InStackEntry, TSharedRef<FUICommandList> InCommandList, TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint);`
- L81 _private member_ `TWeakPtr<FRigStackEntry> WeakStackEntry;`
- L82 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakBlueprint;`
- L83 _private member_ `TWeakPtr<FUICommandList> WeakCommandList;`
- L85 _private prototype_ `FText GetIndexText() const;`
- L86 _private prototype_ `FText GetLabelText() const;`
- L87 _private prototype_ `FSlateColor GetLabelColorAndOpacity() const;`
- L88 _private prototype_ `FText GetTooltip() const;`
- L89 _private prototype_ `FText GetVisitedCountText() const;`
- L90 _private prototype_ `FText GetDurationText() const;`

#### class `SRigVMExecutionStackTreeView`  
`class SRigVMExecutionStackTreeView : public STreeView<TSharedPtr<FRigStackEntry>>`  
_L93-137_
- inherits: `STreeView<TSharedPtr<FRigStackEntry>>`
- L95 _private typedef_ `typedef STreeView<TSharedPtr<FRigStackEntry>> BaseView;`
- L100 _public function_ `void SaveAndClearSparseItemInfos()` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L119 _public function_ `void RestoreSparseItemInfos(TSharedPtr<FRigStackEntry> EntryPtr)` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L135 _private member_ `TSparseItemMap OldSparseItemInfos;`
- L136 _private member_ `TMap<uint32, FSparseItemInfo> OldSparseItemInfosByHash;`

#### class `SRigVMExecutionStackView`  
`class SRigVMExecutionStackView : public SCompoundWidget`  
_L139-241_
- inherits: `SCompoundWidget`
- L142 _public function_ `SLATE_BEGIN_ARGS(SRigVMExecutionStackView)`
- L145 _public prototype_ `~SRigVMExecutionStackView();`
- L147 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IRigVMEditor> InRigVMEditor);`
- L150 _public prototype_ `void OnSelectionChanged(TSharedPtr<FRigStackEntry> Selection, ESelectInfo::Type SelectInfo);` — Set Selection Changed
- L152 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L154 _public prototype_ `TSharedPtr< SWidget > CreateContextMenu();`
- L159 _protected prototype_ `void RefreshTreeView(URigVM* InVM, FRigVMExtendedExecuteContext* InVMContext, bool bRebuildEntries);` — Rebuild the tree view
- L164 _private prototype_ `void BindCommands();` — Bind commands that this widget handles
- L167 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FRigStackEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable, TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint);` — Make a row widget for the table
- L170 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FRigStackEntry> InItem, TArray<TSharedPtr<FRigStackEntry>>& OutChildren);` — Get children for the tree
- L173 _private prototype_ `void HandleFocusOnSelectedGraphNode();` — Focus on the selected operator in the graph
- L176 _private prototype_ `void HandleGoToInstruction();` — Offers a dialog to move to a specific instruction
- L179 _private prototype_ `void HandleSelectTargetInstructions();` — Selects the target instructions for the current selection
- L182 _private prototype_ `void HandleToggleEarlyExitInstruction();` — Sets or unsets the preview here early exit instruction
- L185 _private prototype_ `void HandleStepEarlyExitInstruction();` — Steps to the next early exist instruction
- L187 _private prototype_ `TArray<TSharedPtr<FRigStackEntry>> GetTargetItems(const TArray<TSharedPtr<FRigStackEntry>>& InItems) const;`
- L189 _private prototype_ `void UpdateTargetItemHighlighting();`
- L191 _private prototype_ `void OnVMCompiled(UObject* InCompiledObject, URigVM* InCompiledVM, FRigVMExtendedExecuteContext& InVMContext);`
- L192 _private prototype_ `void OnObjectBeingDebuggedChanged(UObject* InObjectBeingDebugged);`
- L195 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Search box widget
- L196 _private member_ `FText FilterText;`
- L197 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L200 _private member_ `bool bSuspendModelNotifications;`
- L201 _private member_ `bool bSuspendControllerSelection;`
- L202 _private prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L203 _private prototype_ `void HandleHostInitializedEvent(URigVMHost* InHost, const FName& InEventName);`
- L204 _private prototype_ `void HandleHostExecutedEvent(URigVMHost* InHost, const FName& InEventName);`
- L205 _private prototype_ `void HandlePreviewHostUpdated(IRigVMEditor* InEditor);`
- L206 _private prototype_ `void HandleItemMouseDoubleClick(TSharedPtr<FRigStackEntry> InItem);`
- L209 _private prototype_ `void PopulateStackView(URigVM* InVM, FRigVMExtendedExecuteContext* InVMContext);` — Populate the execution stack with descriptive names for each instruction
- L211 _private prototype_ `void BindHostDelegates();`
- L212 _private prototype_ `void BindHostDelegates(UObject* InObjectBeingDebugged);`
- L213 _private prototype_ `void UnbindHostDelegates();`
- L214 _private prototype_ `void UnbindAssetDelegates();`
- L216 _private prototype_ `TSharedPtr<FRigStackEntry> MakeEntry(ERigStackEntry::Type InEntryType, int32 InSubjectIndex, ERigVMOpCode InOpCode, const FString& InLabel, const FRigVMASTProxy& InProxy);`
- L218 _private member_ `TSharedPtr<SRigVMExecutionStackTreeView> TreeView;`
- L221 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list we bind to
- L223 _private member_ `TWeakPtr<IRigVMEditor> WeakEditor;`
- L224 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakRigVMBlueprint;`
- L226 _private member_ `TArray<TSharedPtr<FRigStackEntry>> RootEntries;`
- L227 _private member_ `TArray<TSharedPtr<FRigStackEntry>> FilteredRootEntries;`
- L228 _private member_ `TArray<TSharedPtr<FRigStackEntry>> AllEntries;`
- L229 _private member_ `TMap<int32, TSharedPtr<FRigStackEntry>> InstructionToEntry;`
- L230 _private member_ `TMap<int32, TSharedPtr<FRigStackEntry>> CallableToEntry;`
- L231 _private member_ `TArray<TTuple<int32,int32>> Blocks;`
- L232 _private member_ `TMap<TTuple<int32,int32>, TSharedPtr<FRigStackEntry>> BlockToEntry;`
- L234 _private member_ `FDelegateHandle OnModelModified;`
- L235 _private member_ `FDelegateHandle OnHostInitializedHandle;`
- L236 _private member_ `FDelegateHandle OnHostExecutedHandle;`
- L237 _private member_ `FDelegateHandle OnVMCompiledHandle;`
- L238 _private member_ `FDelegateHandle OnPreviewHostUpdatedHandle;`
- L239 _private member_ `FDelegateHandle OnObjectBeingDebuggedChangedHandle;`
- L240 _private member_ `TWeakObjectPtr<URigVMHost> PreviouslyDebuggedHost;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L20 _namespace_ `namespace ERigStackEntry`
- L44 _function_ `friend uint32 GetTypeHash(const FRigStackEntry& InEntry)`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphBreakLinksWidget.h` (Public)


#### class `SRigVMGraphBreakLinksWidget`  
`class SRigVMGraphBreakLinksWidget : public SCompoundWidget`  
_L17-39_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphBreakLinksWidget)`
- L21 _public prototype_ `SLATE_ARGUMENT(FRigVMOnFocusOnLinkRequestedDelegate, OnFocusOnLink) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArray<URigVMLink*> InLinks);`
- L29 _private prototype_ `void OnLinkDoubleClicked(const URigVMLink* InLink, EAssetTypeActivationMethod::Type ActivationMethod);` — Handler for when the user double clicks, presses enter, or presses space on an asset
- L31 _private prototype_ `TSharedRef<ITableRow> GenerateItemRow(URigVMLink* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L33 _private member_ `TArray<URigVMLink*> Links;`
- L34 _private member_ `FRigVMOnFocusOnLinkRequestedDelegate OnFocusOnLink;`
- L36 _private prototype_ `void HandleItemMouseDoubleClick(URigVMLink* InItem);`

#### class `SRigVMGraphBreakLinksDialog`  
`class SRigVMGraphBreakLinksDialog : public SWindow`  
_L41-64_
- inherits: `SWindow`
- L45 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphBreakLinksDialog)`
- L49 _public prototype_ `SLATE_ARGUMENT(TArray<URigVMLink*>, Links) SLATE_ARGUMENT(FRigVMOnFocusOnLinkRequestedDelegate, OnFocusOnLink) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L55 _public prototype_ `EAppReturnType::Type ShowModal();`
- L59 _protected member_ `TSharedPtr<SRigVMGraphBreakLinksWidget> BreakLinksWidget;`
- L61 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L62 _protected prototype_ `bool IsOkButtonEnabled() const;`
- L63 _protected member_ `EAppReturnType::Type UserResponse;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMOnFocusOnLinkRequestedDelegate, URigVMLink*);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMOnFocusOnLinkRequestedDelegate, URigVMLink*);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphChangePinType.h` (Public)


#### class `SRigVMGraphChangePinType`  
`class SRigVMGraphChangePinType : public SCompoundWidget`  
_L17-49_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphChangePinType) : _Types() , _OnTypeSelected(nullptr)`
- L26 _public prototype_ `SLATE_ARGUMENT(TArray<TRigVMTypeIndex>, Types) SLATE_EVENT(FOnTypeSelected, OnTypeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _protected prototype_ `static FText GetBindingText(const FRigVMTemplateArgumentType& InType);`
- L36 _protected prototype_ `FText GetBindingText(URigVMPin* ModelPin) const;`
- L37 _protected prototype_ `FText GetBindingText() const;`
- L38 _protected prototype_ `const FSlateBrush* GetBindingImage() const;`
- L39 _protected prototype_ `FLinearColor GetBindingColor() const;`
- L40 _protected prototype_ `bool OnCanBindProperty(FProperty* InProperty) const;`
- L41 _protected prototype_ `bool OnCanBindToClass(UClass* InClass) const;`
- L42 _protected prototype_ `void OnAddBinding(FName InPropertyName, const TArray<FBindingChainElement>& InBindingChain);`
- L43 _protected prototype_ `void FillPinTypeMenu( FMenuBuilder& MenuBuilder );`
- L44 _protected prototype_ `void HandlePinTypeChanged(FRigVMTemplateArgumentType InType);`
- L46 _protected member_ `TArray<TRigVMTypeIndex> Types;`
- L47 _protected member_ `FOnTypeSelected OnTypeSelected;`
- L48 _protected member_ `FPropertyBindingWidgetArgs BindingArgs;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTypeSelected, TRigVMTypeIndex);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTypeSelected, TRigVMTypeIndex);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphFunctionBulkEditWidget.h` (Public)


#### class `SRigVMGraphFunctionBulkEditWidget`  
`class SRigVMGraphFunctionBulkEditWidget : public SCompoundWidget`  
_L15-42_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphFunctionBulkEditWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FRigVMEditorAssetInterfacePtr InBlueprint, URigVMController* InController, URigVMLibraryNode* InFunction, ERigVMControllerBulkEditType InEditType);`
- L26 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu( const TArray<FAssetData>& SelectedAssets );` — Handler for when an asset context menu has been requested.
- L29 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& ActivatedAssets, EAssetTypeActivationMethod::Type ActivationMethod);` — Handler for when the user double clicks, presses enter, or presses space on an asset
- L32 _private prototype_ `void LoadAffectedAssets();` — Show a progress bar and load all of the assets
- L34 _private member_ `FRigVMEditorAssetInterfacePtr Blueprint;`
- L35 _private member_ `URigVMController* Controller;`
- L36 _private member_ `URigVMLibraryNode* Function;`
- L37 _private member_ `ERigVMControllerBulkEditType EditType;`
- L39 _private prototype_ `TSharedRef<SWidget> MakeAssetViewForReferencedAssets();`

#### class `SRigVMGraphFunctionBulkEditDialog`  
`class SRigVMGraphFunctionBulkEditDialog : public SWindow`  
_L44-69_
- inherits: `SWindow`
- L48 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphFunctionBulkEditDialog)`
- L52 _public prototype_ `SLATE_ARGUMENT(FRigVMEditorAssetInterfacePtr, Blueprint) SLATE_ARGUMENT(URigVMController*, Controller) SLATE_ARGUMENT(URigVMLibraryNode*, Function) SLATE_ARGUMENT(ERigVMControllerBulkEditType, EditType) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `EAppReturnType::Type ShowModal();`
- L64 _protected member_ `TSharedPtr<SRigVMGraphFunctionBulkEditWidget> BulkEditWidget;`
- L66 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L67 _protected prototype_ `bool IsOkButtonEnabled() const;`
- L68 _protected member_ `EAppReturnType::Type UserResponse;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphFunctionLocalizationWidget.h` (Public)


#### class `SRigVMGraphFunctionLocalizationItem`  
`class SRigVMGraphFunctionLocalizationItem : public TSharedFromThis<SRigVMGraphFunctionLocalizationItem>`  
_L15-23_
- inherits: `TSharedFromThis<SRigVMGraphFunctionLocalizationItem>`
- L18 _public prototype_ `SRigVMGraphFunctionLocalizationItem(const FRigVMGraphFunctionIdentifier& InFunction);`
- L20 _public member_ `FText DisplayText;`
- L21 _public member_ `FText ToolTipText;`
- L22 _public member_ `const FRigVMGraphFunctionIdentifier Function;`

#### class `SRigVMGraphFunctionLocalizationTableRow`  
`class SRigVMGraphFunctionLocalizationTableRow : public STableRow<TSharedPtr<SRigVMGraphFunctionLocalizationItem>>`  
_L25-31_
- inherits: `STableRow<TSharedPtr<SRigVMGraphFunctionLocalizationItem>>`
- L27 _private function_ `SLATE_BEGIN_ARGS(SRigVMGraphFunctionLocalizationTableRow)`
- L28 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, SRigVMGraphFunctionLocalizationWidget* InLocalizationWidget, TSharedRef<SRigVMGraphFunctionLocalizationItem> InFunctionItem);`

#### class `SRigVMGraphFunctionLocalizationWidget`  
`class SRigVMGraphFunctionLocalizationWidget : public SCompoundWidget`  
_L33-54_
- inherits: `SCompoundWidget`
- L36 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphFunctionLocalizationWidget)`
- L37 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FRigVMGraphFunctionIdentifier& InFunctionToLocalize, IRigVMGraphFunctionHost* InTargetFunctionHost);`
- L41 _public prototype_ `TSharedRef<ITableRow> GenerateFunctionListRow(TSharedPtr<SRigVMGraphFunctionLocalizationItem> InItem, const TSharedRef<STableViewBase>& InOwningTable);`
- L42 _public prototype_ `ECheckBoxState IsFunctionEnabled(const FRigVMGraphFunctionIdentifier InFunction) const;`
- L43 _public prototype_ `void SetFunctionEnabled(ECheckBoxState NewState, const FRigVMGraphFunctionIdentifier InFunction);`
- L44 _public prototype_ `bool IsFunctionPublic(const FRigVMGraphFunctionIdentifier InFunction) const;`
- L48 _private member_ `TArray<FRigVMGraphFunctionIdentifier> FunctionsToLocalize;`
- L49 _private member_ `TArray<TSharedPtr<SRigVMGraphFunctionLocalizationItem>> FunctionItems;`
- L50 _private member_ `TMap<FRigVMGraphFunctionIdentifier, TSharedRef<SRigVMGraphFunctionLocalizationTableRow>> TableRows;`

#### class `SRigVMGraphFunctionLocalizationDialog`  
`class SRigVMGraphFunctionLocalizationDialog : public SWindow`  
_L56-80_
- inherits: `SWindow`
- L60 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphFunctionLocalizationDialog)`
- L64 _public prototype_ `SLATE_ARGUMENT(FRigVMGraphFunctionIdentifier, Function) SLATE_ARGUMENT(IRigVMGraphFunctionHost*, GraphFunctionHost) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L70 _public prototype_ `EAppReturnType::Type ShowModal();`
- L71 _public prototype_ `TArray<FRigVMGraphFunctionIdentifier>& GetFunctionsToLocalize();`
- L75 _protected member_ `TSharedPtr<SRigVMGraphFunctionLocalizationWidget> FunctionsWidget;`
- L77 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L78 _protected prototype_ `bool IsOkButtonEnabled() const;`
- L79 _protected member_ `EAppReturnType::Type UserResponse;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphNode.h` (Public)


#### class `SRigVMGraphPinReorderHandle`  
`class SRigVMGraphPinReorderHandle : public SCompoundWidget`  
_L24-68_
- inherits: `SCompoundWidget`
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FCanReorderDelegate, const URigVMPin* , const URigVMPin* , EItemDropZone);`
- L29 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FReorderDelegate, const URigVMPin* , const URigVMPin* , EItemDropZone);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinReorderHandle) : _bIsInput(true) , _Width(50.f) , _Height(24.f) , _LineExtension(0.f)`
- L37 _public prototype_ `SLATE_ARGUMENT(bool, bIsInput) SLATE_ARGUMENT(float, Width) SLATE_ARGUMENT(float, Height) SLATE_ARGUMENT(TWeakObjectPtr<URigVMPin>, Pin) SLATE_ATTRIBUTE(float, LineExtension) SLATE_EVENT(FCanReorderDelegate, CanReorder) SLATE_EVENT(FReorderDelegate, OnReorder) SLATE_ARGUMENT(TWeakInterfacePtr<IRigVMClientHost>, WeakClientHost) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L49 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L52 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L53 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L55 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L59 _private member_ `bool bIsInput = true;`
- L60 _private member_ `TWeakObjectPtr<URigVMPin> Pin;`
- L61 _private member_ `TAttribute<float> LineExtension;`
- L62 _private member_ `FCanReorderDelegate CanReorderDelegate;`
- L63 _private member_ `FReorderDelegate ReorderDelegate;`
- L64 _private member_ `TOptional<EItemDropZone> DropZone;`
- L65 _private member_ `TWeakInterfacePtr<IRigVMClientHost> WeakClientHost;`

#### class `SRigVMGraphNode`  
`class SRigVMGraphNode : public SGraphNode`  
_L70-239_
- inherits: `SGraphNode`
- L73 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphNode) : _GraphNodeObj(nullptr) , _Enabled(true) , _PinDragDropEnabled(true)`
- L79 _public prototype_ `SLATE_ARGUMENT(URigVMEdGraphNode*, GraphNodeObj) SLATE_ATTRIBUTE(bool, Enabled) SLATE_ATTRIBUTE(bool, PinDragDropEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L88 _public prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> InNodeTitle) override;` — SGraphNode interface
- L90 _public prototype_ `virtual void EndUserInteraction() const override;`
- L91 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L92 _public prototype_ `virtual void AddPin( const TSharedRef<SGraphPin>& PinToAdd ) override;`
- L93 _public prototype_ `virtual void CreateStandardPinWidget(UEdGraphPin* CurPin) override;`
- L94 _public function_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override`
- L98 _public prototype_ `virtual const FSlateBrush * GetNodeBodyBrush() const override;`
- L99 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L100 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L102 _public prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L103 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;`
- L104 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L105 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L107 _public prototype_ `virtual void RefreshErrorInfo() override;`
- L108 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L109 _public function_ `virtual bool IsHidingPinWidgets() const override`
- L110 _public prototype_ `virtual bool UseLowDetailPinNames() const override;`
- L111 _public prototype_ `virtual void UpdateGraphNode() override;`
- L112 _public prototype_ `void UpdateStandardNode();`
- L113 _public prototype_ `void UpdateCompactNode();`
- L114 _public prototype_ `virtual TOptional<FSlateColor> GetPinTextColor(const SGraphPin* InGraphPin) const override;`
- L115 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L117 _public prototype_ `void CreateAddPinButton();`
- L119 _public prototype_ `void CreateWorkflowWidgets();`
- L122 _public prototype_ `virtual FReply OnAddPin() override;` — Callback function executed when Add pin button is clicked
- L126 _protected prototype_ `bool UseLowDetailNodeContent() const;`
- L128 _protected prototype_ `FVector2D GetLowDetailDesiredSize() const;`
- L130 _protected prototype_ `EVisibility GetTitleVisibility() const;`
- L131 _protected prototype_ `EVisibility GetArrayPlusButtonVisibility(URigVMPin* InModelPin) const;`
- L133 _protected prototype_ `FText GetPinLabel(TWeakPtr<SGraphPin> GraphPin) const;`
- L135 _protected prototype_ `virtual TOptional<FSlateColor> GetHighlightColor(const SGraphPin* InGraphPin) const override;`
- L136 _protected prototype_ `FSlateColor GetVariableLabelTextColor(TWeakObjectPtr<URigVMFunctionReferenceNode> FunctionReferenceNode, FName InVariableName) const;`
- L137 _protected prototype_ `FText GetVariableLabelTooltipText(TWeakInterfacePtr<IRigVMEditorAssetInterface> InBlueprint, FName InVariableName) const;`
- L139 _protected prototype_ `FReply HandleAddArrayElement(FString InModelPinPath);`
- L141 _protected prototype_ `void HandleNodeTitleDirtied();`
- L142 _protected prototype_ `void HandleNodePinsChanged();`
- L143 _protected prototype_ `void HandleNodeBeginRemoval();`
- L145 _protected prototype_ `FText GetInstructionCountText() const;`
- L146 _protected prototype_ `FText GetInstructionDurationText() const;`
- L148 _protected prototype_ `TSharedRef<SWidget> OnOverrideWidgetMenu() const;`
- L152 _protected prototype_ `int32 GetNodeTopologyVersion() const;`
- L153 _protected prototype_ `EVisibility GetPinVisibility(int32 InPinInfoIndex, bool bAskingForSubPin) const;`
- L154 _protected prototype_ `const FSlateBrush * GetExpanderImage(int32 InPinInfoIndex, bool bLeft, bool bHovered) const;`
- L155 _protected prototype_ `FReply OnExpanderArrowClicked(int32 InPinInfoIndex);`
- L156 _protected prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L157 _protected prototype_ `virtual void UpdatePinTreeView();`
- L158 _protected prototype_ `ERigVMNodeDefaultValueOverrideState::Type GetPinDefaultValueOverrideState() const;`
- L159 _protected prototype_ `bool IsCategoryPin(const SGraphPin* InGraphPin) const;`
- L160 _protected prototype_ `EOverrideWidgetStatus::Type GetOverrideStatus() const;`
- L161 _protected prototype_ `FSlateColor GetPreviewHereColor() const;`
- L163 _protected prototype_ `int32 CanReorderExposedPin(const URigVMPin* InPinToReorder, const URigVMPin* InTargetPin, EItemDropZone InDropZone);`
- L164 _protected prototype_ `void OnReorderExposedPin(const URigVMPin* InPinToReorder, const URigVMPin* InTargetPin, EItemDropZone InDropZone);`
- L167 _protected member_ `TSharedPtr<SOverlay> TitleAreaWidget;` — Cached widget title area
- L169 _protected member_ `int32 NodeErrorType;`
- L171 _protected member_ `TSharedPtr<SButton> PreviewHereIndicatorWidget;`
- L172 _protected member_ `bool bPreviewHereIndicatorHovered;`
- L173 _protected member_ `TSharedPtr<SImage> VisualDebugIndicatorWidget;`
- L174 _protected member_ `TSharedPtr<STextBlock> InstructionCountTextBlockWidget;`
- L175 _protected member_ `TSharedPtr<STextBlock> InstructionDurationTextBlockWidget;`
- L176 _protected member_ `TSharedPtr<SOverrideStatusWidget> OverrideStatusWidget;`
- L178 _protected member_ `static const FSlateBrush* CachedImg_CR_Pin_Connected;`
- L179 _protected member_ `static const FSlateBrush* CachedImg_CR_Pin_Disconnected;`
- L182 _protected member_ `TSharedPtr<SNodeTitle> NodeTitle;` — Cache the node title so we can invalidate it
- L184 _protected member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> Blueprint;`
- L186 _protected member_ `FVector2D LastHighDetailSize;`
- L226 _protected member_ `TArray<FPinInfo> PinInfos;`
- L227 _protected member_ `TWeakObjectPtr<URigVMNode> ModelNode;`
- L231 _protected member_ `TMap<const UEdGraphPin *, TSharedRef<SGraphPin>> PinsToKeep;` — Pins to keep after calling HandleNodePinsChanged. We recycle these pins in CreateStandardPinWidget.
- L236 _protected member_ `TSet<UEdGraphPin *> PinsToDelete;` — Delayed pin deletion. To deal with the fact that pin deletion cannot occur until we have re-generated the pin list. SRigVMGraphNode has already relinquished them but we still have a pointer to them in our pin widget.
- L238 _protected member_ `TAttribute<bool> PinDragDropEnabledAttribute;`

#### struct `SRigVMGraphNode::FPinInfo`  
`struct FPinInfo`  
_L188-204_
- L190 _public member_ `int32 Index;`
- L191 _public member_ `int32 ParentIndex;`
- L192 _public member_ `bool bIsCategoryPin;`
- L193 _public member_ `bool bHasChildren;`
- L194 _public member_ `bool bHideInputWidget;`
- L195 _public member_ `bool bIsContainer;`
- L196 _public member_ `bool bIsInputVariable;`
- L197 _public member_ `int32 Depth;`
- L198 _public member_ `FString Identifier;`
- L199 _public member_ `TSharedPtr<SGraphPin> InputPinWidget;`
- L200 _public member_ `TSharedPtr<SGraphPin> OutputPinWidget;`
- L201 _public member_ `bool bExpanded;`
- L202 _public member_ `bool bAutoHeight;`
- L203 _public member_ `bool bShowOnlySubPins;`

#### class `SRigVMGraphNode::FPinInfoMetaData`  
`class FPinInfoMetaData : public ISlateMetaData`  
_L210-224_
- inherits: `ISlateMetaData`
- desc: Simple tagging metadata
- L213 _public function_ `SLATE_METADATA_TYPE(FPinInfoMetaData, ISlateMetaData) FPinInfoMetaData(const FString& InCPPType, const FString& InBoundVariableName, bool InIsInputVariable) : CPPType(InCPPType) , BoundVariableName(InBoundVariableName) , bIsInputVariable(InIsInputVariable)`
- L221 _public member_ `FString CPPType;`
- L222 _public member_ `FString BoundVariableName;`
- L223 _public member_ `bool bIsInputVariable;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMEDITOR_API`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FCanReorderDelegate, const URigVMPin* , const URigVMPin* , EItemDropZone);`
- L29 _delegate_ `DECLARE_DELEGATE_ThreeParams(FReorderDelegate, const URigVMPin* , const URigVMPin* , EItemDropZone);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphNodeComment.h` (Public)


#### class `SRigVMGraphNodeComment`  
`class SRigVMGraphNodeComment : public SGraphNodeComment`  
_L12-35_
- inherits: `SGraphNodeComment`
- L16 _public prototype_ `SRigVMGraphNodeComment();`
- L18 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L19 _public prototype_ `virtual void EndUserInteraction() const override;`
- L20 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L21 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L25 _protected prototype_ `virtual bool IsNodeUnderComment(UEdGraphNode_Comment* InCommentNode, const TSharedRef<SGraphNode> InNodeWidget) const override;`
- L26 _protected prototype_ `bool IsNodeUnderComment(UEdGraphNode* InNode) const;`
- L27 _protected prototype_ `bool IsNodeUnderComment(const FVector2f& InNodePosition) const;`
- L28 _protected prototype_ `bool IsNodeUnderComment(const FVector2f& InCommentPosition, const FVector2f& InNodePosition) const;`
- L32 _private member_ `FLinearColor CachedNodeCommentColor;`
- L34 _private member_ `int8 CachedColorBubble;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphNodeKnot.h` (Public)


#### class `SRigVMGraphNodeKnot`  
`class SRigVMGraphNodeKnot : public SGraphNodeKnot`  
_L11-25_
- inherits: `SGraphNodeKnot`
- L13 _private function_ `SLATE_BEGIN_ARGS(SRigVMGraphNodeKnot)`
- L14 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode* InKnot);`
- L19 _private prototype_ `virtual void EndUserInteraction() const override;` — SGraphNode interface
- L20 _private prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L21 _private prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L23 _private prototype_ `void HandleNodeBeginRemoval();`
- L24 _private prototype_ `void UpdateGraphNode() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinCategory.h` (Public)


#### class `SRigVMGraphPinCategory`  
`class SRigVMGraphPinCategory : public SGraphPin`  
_L12-29_
- inherits: `SGraphPin`
- L15 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinCategory)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L21 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L27 _protected function_ `virtual const FSlateBrush* GetPinIcon() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinCurveFloat.h` (Public)


#### class `SRigVMGraphPinCurveFloat`  
`class SRigVMGraphPinCurveFloat : public SGraphPin, public FCurveOwnerInterface`  
_L14-45_
- inherits: `SGraphPin,FCurveOwnerInterface`
- L17 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinCurveFloat)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L24 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — FCurveOwnerInterface interface
- L26 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L27 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L28 _public prototype_ `virtual void ModifyOwner() override;`
- L29 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L30 _public prototype_ `virtual void MakeTransactional() override;`
- L31 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L32 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L38 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L41 _protected prototype_ `FRuntimeFloatCurve& UpdateAndGetCurve();`
- L43 _protected member_ `TSharedPtr<SCurveEditor> CurveEditor;`
- L44 _protected member_ `FRuntimeFloatCurve Curve;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinEditableNameValueWidget.h` (Public)


#### class `SRigVMGraphPinEditableNameValueWidget`  
`class SRigVMGraphPinEditableNameValueWidget : public SComboButton`  
_L18-134_
- inherits: `SComboButton`
- desc: A searchable text combo box
- L22 _public typedef_ `typedef SListView< TSharedPtr<FString> > SComboListType;` — Type of list used for showing menu options.
- L24 _public typedef_ `typedef typename TSlateDelegates< TSharedPtr<FString> >::FOnGenerateWidget FOnGenerateWidget;` — Delegate type used to generate widgets that represent Options
- L25 _public typedef_ `typedef typename TSlateDelegates< TSharedPtr<FString> >::FOnSelectionChanged FOnSelectionChanged;`
- L27 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinEditableNameValueWidget) : _Content() , _ContentPadding(FMargin(3.0, 3.0)) , _OptionsSource() , _OnSelectionChanged() , _OnGenerateWidget() , _InitiallySelectedItem(nullptr) , _Method() , _MaxListHeight(450.0f) , _HasDownArrow(true)`
- L40 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ARGUMENT(const TArray< TSharedPtr<FString> >*, OptionsSource) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar) SLATE_ARGUMENT(TSharedPtr<FString>, InitiallySelectedItem) SLATE_ARGUMENT(TOptional<EPopupMethod>, Method) SLATE_ARGUMENT(float, MaxListHeight) SLATE_ARGUMENT(bool, HasDownArrow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this button's content (optional)
- L77 _public prototype_ `void ClearSelection();`
- L79 _public prototype_ `void SetSelectedItem(TSharedPtr<FString> InSelectedItem);`
- L82 _public prototype_ `TSharedPtr<FString> GetSelectedItem();` — @return the item currently selected by the combo box.
- L89 _public prototype_ `void RefreshOptions();` — Requests a list refresh after updating options Call SetSelectedItem to update the selected item if required @see SetSelectedItem
- L94 _private prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget
- L97 _private prototype_ `void OnMenuOpenChanged(bool bOpen);` — /  Called if the menu is closed
- L100 _private prototype_ `void OnSelectionChanged_Internal(TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo);` — Invoked when the selection in the list changes
- L103 _private prototype_ `void OnSearchTextChanged(const FText& ChangedText);` — Invoked when the search text changes
- L106 _private prototype_ `void OnSearchTextCommitted(const FText& ChangedText, ETextCommit::Type CommitType);` — Invoked when the search is committed
- L109 _private prototype_ `virtual FReply OnButtonClicked() override;` — Handle clicking on the content menu
- L112 _private member_ `const FTableRowStyle* ItemStyle;` — The item style to use.
- L116 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate that is invoked when the selected item in the combo box changes
- L118 _private member_ `TSharedPtr<FString> SelectedItem;` — The item currently selected in the combo box
- L120 _private member_ `TSharedPtr< SEditableTextBox > SearchField;` — The search field used for the combox box's contents
- L122 _private member_ `TSharedPtr< SComboListType > ComboListView;` — The ListView that we pop up; visualized the available options.
- L124 _private member_ `TSharedPtr< SScrollBar > CustomScrollbar;` — The Scrollbar used in the ListView.
- L126 _private member_ `FOnComboBoxOpening OnComboBoxOpening;` — Delegate to invoke before the combo box is opening.
- L128 _private member_ `FOnGenerateWidget OnGenerateWidget;` — Delegate to invoke when we need to visualize an option as a widget.
- L130 _private member_ `const TArray< TSharedPtr<FString> >* OptionsSource;`
- L133 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);` — Used to focus the name box immediately following construction

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinEnumPicker.h` (Public)


#### class `SRigVMEnumPicker`  
`class SRigVMEnumPicker : public SCompoundWidget`  
_L14-53_
- inherits: `SCompoundWidget`
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal(TObjectPtr<UEnum>, FGetCurrentEnum);`
- L19 _public function_ `SLATE_BEGIN_ARGS(SRigVMEnumPicker)`
- L20 _public prototype_ `SLATE_EVENT(SSearchableComboBox::FOnSelectionChanged, OnEnumChanged) SLATE_EVENT(FGetCurrentEnum, GetCurrentEnum) SLATE_ARGUMENT(bool, IsEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _protected function_ `void HandleControlEnumChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo)`
- L37 _protected function_ `UEnum* GetCurrentEnum()`
- L46 _protected prototype_ `TSharedRef<SWidget> OnGetEnumNameWidget(TSharedPtr<FString> InItem);`
- L47 _protected prototype_ `void PopulateEnumOptions();`
- L49 _protected member_ `TArray<TSharedPtr<FString>> EnumOptions;`
- L50 _protected member_ `SSearchableComboBox::FOnSelectionChanged OnEnumChangedDelegate;`
- L51 _protected member_ `FGetCurrentEnum GetCurrentEnumDelegate;`
- L52 _protected member_ `bool bIsEnabled;`

#### class `SRigVMGraphPinEnumPicker`  
`class SRigVMGraphPinEnumPicker : public SGraphPin`  
_L55-74_
- inherits: `SGraphPin`
- L58 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinEnumPicker) : _ModelPin(nullptr)`
- L60 _public prototype_ `SLATE_ARGUMENT(URigVMPin*, ModelPin) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L67 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L70 _protected prototype_ `void HandleControlEnumChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo);`
- L72 _protected member_ `URigVMPin* ModelPin;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(TObjectPtr<UEnum>, FGetCurrentEnum);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinNameList.h` (Public)


#### class `SRigVMGraphPinNameList`  
`class SRigVMGraphPinNameList : public SGraphPin`  
_L16-82_
- inherits: `SGraphPin`
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( const TArray<TSharedPtr<FRigVMStringWithTag>>*, FOnGetNameListContent, URigVMPin*);`
- L21 _public prototype_ `DECLARE_DELEGATE_RetVal( const TArray<TSharedPtr<FRigVMStringWithTag>>, FOnGetNameFromSelection);`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnGetSelectedClicked, URigVMEdGraph*, URigVMPin*, FString);`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnBrowseClicked, URigVMEdGraph*, URigVMPin*, FString);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinNameList) : _MarkupInvalidItems(true) , _EnableNameListCache(true) , _SearchHintText(NSLOCTEXT("SRigVMGraphPinNameList", "Search", "Search")) , _AllowUserProvidedText(false)`
- L32 _public prototype_ `SLATE_ARGUMENT(URigVMPin*, ModelPin) SLATE_EVENT(FOnGetNameListContent, OnGetNameListContent) SLATE_EVENT(FOnGetNameListContent, OnGetNameListContentForValidation) SLATE_EVENT(FOnGetNameFromSelection, OnGetNameFromSelection) SLATE_EVENT(FOnGetSelectedClicked, OnGetSelectedClicked) SLATE_EVENT(FOnBrowseClicked, OnBrowseClicked) SLATE_ARGUMENT(bool, MarkupInvalidItems) SLATE_ARGUMENT(bool, EnableNameListCache) SLATE_ARGUMENT(FText, SearchHintText) SLATE_ARGUMENT(bool, AllowUserProvidedText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L49 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L52 _protected prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetNameList(bool bForContent = true) const;`
- L53 _protected prototype_ `FText GetNameListText() const;`
- L54 _protected prototype_ `FSlateColor GetNameColor() const;`
- L55 _protected prototype_ `virtual void SetNameListText(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L56 _protected prototype_ `void UpdateNameLists(bool bUpdateCurrent = true, bool bUpdateValidation = true);`
- L58 _protected prototype_ `TSharedRef<SWidget> MakeNameListItemWidget(TSharedPtr<FRigVMStringWithTag> InItem);`
- L59 _protected prototype_ `void OnNameListChanged(TSharedPtr<FRigVMStringWithTag> NewSelection, ESelectInfo::Type SelectInfo);`
- L60 _protected prototype_ `void OnNameListComboBox();`
- L62 _protected member_ `FOnGetNameListContent OnGetNameListContent;`
- L63 _protected member_ `FOnGetNameListContent OnGetNameListContentForValidation;`
- L64 _protected member_ `URigVMPin* ModelPin;`
- L65 _protected member_ `TSharedPtr<SRigVMGraphPinNameListValueWidget> NameListComboBox;`
- L66 _protected member_ `TArray<TSharedPtr<FRigVMStringWithTag>> EmptyList;`
- L67 _protected member_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* CurrentList;`
- L68 _protected member_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* ValidationList;`
- L69 _protected member_ `bool bMarkupInvalidItems;`
- L70 _protected member_ `bool EnableNameListCache;`
- L71 _protected member_ `FText SearchHintText;`
- L72 _protected member_ `bool AllowUserProvidedText;`
- L75 _protected prototype_ `FSlateColor OnGetWidgetForeground() const;` — Helper buttons.
- L76 _protected prototype_ `FSlateColor OnGetWidgetBackground() const;`
- L77 _protected prototype_ `FReply HandleGetSelectedClicked();`
- L78 _protected prototype_ `FReply HandleBrowseClicked();`
- L79 _protected member_ `FOnGetNameFromSelection OnGetNameFromSelection;`
- L80 _protected member_ `FOnGetSelectedClicked OnGetSelectedClicked;`
- L81 _protected member_ `FOnBrowseClicked OnBrowseClicked;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( const TArray<TSharedPtr<FRigVMStringWithTag>>*, FOnGetNameListContent, URigVMPin*);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal( const TArray<TSharedPtr<FRigVMStringWithTag>>, FOnGetNameFromSelection);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnGetSelectedClicked, URigVMEdGraph*, URigVMPin*, FString);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams( FReply, FOnBrowseClicked, URigVMEdGraph*, URigVMPin*, FString);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinNameListValueWidget.h` (Public)


#### class `SRigVMGraphPinNameListValueWidget`  
`class SRigVMGraphPinNameListValueWidget : public SComboButton`  
_L19-155_
- inherits: `SComboButton`
- desc: A searchable text combo box
- L23 _public typedef_ `typedef SListView< TSharedPtr<FRigVMStringWithTag> > SComboListType;` — Type of list used for showing menu options.
- L25 _public typedef_ `typedef typename TSlateDelegates< TSharedPtr<FRigVMStringWithTag> >::FOnGenerateWidget FOnGenerateWidget;` — Delegate type used to generate widgets that represent Options
- L26 _public typedef_ `typedef typename TSlateDelegates< TSharedPtr<FRigVMStringWithTag> >::FOnSelectionChanged FOnSelectionChanged;`
- L28 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinNameListValueWidget) : _Content() , _ContentPadding(FMargin(3.0, 3.0)) , _OptionsSource() , _OnSelectionChanged() , _OnGenerateWidget() , _InitiallySelectedItem(nullptr) , _Method() , _MaxListHeight(450.0f) , _HasDownArrow(true) , _SearchHintText(NSLOCTEXT("SRigVMGraphPinNameListValueWidget", "Search", "Search")) , _AllowUserProvidedText(false)`
- L43 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ARGUMENT(const TArray< TSharedPtr<FRigVMStringWithTag> >*, OptionsSource) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnComboBoxOpening, OnComboBoxOpening) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, CustomScrollbar) SLATE_ARGUMENT(TSharedPtr<FRigVMStringWithTag>, InitiallySelectedItem) SLATE_ARGUMENT(TOptional<EPopupMethod>, Method) SLATE_ARGUMENT(float, MaxListHeight) SLATE_ARGUMENT(bool, HasDownArrow) SLATE_ARGUMENT(FText, SearchHintText) SLATE_ARGUMENT(bool, AllowUserProvidedText) SLATE_END_ARGS()` — Slot for this button's content (optional)
- L90 _public prototype_ `void ClearSelection();`
- L92 _public prototype_ `void SetSelectedItem(TSharedPtr<FRigVMStringWithTag> InSelectedItem);`
- L93 _public prototype_ `void SetOptionsSource(const TArray< TSharedPtr<FRigVMStringWithTag> >* InOptionsSource);`
- L96 _public prototype_ `TSharedPtr<FRigVMStringWithTag> GetSelectedItem();` — @return the item currently selected by the combo box.
- L103 _public prototype_ `void RefreshOptions();` — Requests a list refresh after updating options Call SetSelectedItem to update the selected item if required @see SetSelectedItem
- L108 _private prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FRigVMStringWithTag> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for the InItem in the combo box's list (passed in as OwnerTable). Do this by calling the user-specified OnGenerateWidget
- L111 _private prototype_ `void OnMenuOpenChanged(bool bOpen);` — /  Called if the menu is closed
- L114 _private prototype_ `void OnSelectionChanged_Internal(TSharedPtr<FRigVMStringWithTag> ProposedSelection, ESelectInfo::Type SelectInfo, bool bForce = false);` — Invoked when the selection in the list changes
- L117 _private prototype_ `void OnSearchTextChanged(const FText& ChangedText);` — Invoked when the search text changes
- L120 _private prototype_ `void OnSearchTextCommitted(const FText& ChangedText, ETextCommit::Type CommitType);` — Invoked when the search is committed
- L123 _private prototype_ `FReply OnSearchTextKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Special case handling for search box key commands
- L126 _private prototype_ `FReply OnComboListKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Special case handling for combo list key commands
- L129 _private prototype_ `virtual FReply OnButtonClicked() override;` — Handle clicking on the content menu
- L132 _private member_ `const FTableRowStyle* ItemStyle;` — The item style to use.
- L136 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate that is invoked when the selected item in the combo box changes
- L138 _private member_ `TSharedPtr<FRigVMStringWithTag> SelectedItem;` — The item currently selected in the combo box
- L140 _private member_ `TSharedPtr< SEditableTextBox > SearchField;` — The search field used for the combox box's contents
- L142 _private member_ `TSharedPtr< SComboListType > ComboListView;` — The ListView that we pop up; visualized the available options.
- L144 _private member_ `TSharedPtr< SScrollBar > CustomScrollbar;` — The Scrollbar used in the ListView.
- L146 _private member_ `FOnComboBoxOpening OnComboBoxOpening;` — Delegate to invoke before the combo box is opening.
- L148 _private member_ `FOnGenerateWidget OnGenerateWidget;` — Delegate to invoke when we need to visualize an option as a widget.
- L150 _private member_ `const TArray< TSharedPtr<FRigVMStringWithTag> >* OptionsSource = nullptr;`
- L151 _private member_ `bool AllowUserProvidedText;`
- L154 _private prototype_ `EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);` — Used to focus the name box immediately following construction

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinQuat.h` (Public)


#### class `SRigVMGraphPinQuat`  
`class SRigVMGraphPinQuat : public SGraphPin`  
_L14-39_
- inherits: `SGraphPin`
- L17 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinQuat) : _ModelPin(nullptr)`
- L20 _public prototype_ `SLATE_ARGUMENT(URigVMPin*, ModelPin) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L32 _protected prototype_ `TOptional<FRotator> GetRotator() const;`
- L33 _protected prototype_ `void OnRotatorCommitted(FRotator InRotator, ETextCommit::Type InCommitType, bool bUndoRedo);`
- L34 _protected prototype_ `TOptional<float> GetRotatorComponent(int32 InComponent) const;`
- L35 _protected prototype_ `void OnRotatorComponentChanged(float InValue, int32 InComponent);`
- L36 _protected prototype_ `void OnRotatorComponentCommitted(float InValue, ETextCommit::Type InCommitType, int32 InComponent, bool bUndoRedo);`
- L38 _protected member_ `URigVMPin* ModelPin;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinUserDataNameSpace.h` (Public)


#### class `SRigVMGraphPinUserDataNameSpace`  
`class SRigVMGraphPinUserDataNameSpace : public SGraphPin`  
_L13-37_
- inherits: `SGraphPin`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinUserDataNameSpace)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L23 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L26 _protected prototype_ `FText GetNameSpaceText() const;`
- L27 _protected prototype_ `virtual void SetNameSpaceText(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L29 _protected prototype_ `TSharedRef<SWidget> MakeNameSpaceItemWidget(TSharedPtr<FString> InItem);`
- L30 _protected prototype_ `void OnNameSpaceChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L31 _protected prototype_ `void OnNameSpaceComboBox();`
- L32 _protected prototype_ `TArray<TSharedPtr<FString>>& GetNameSpaces();`
- L34 _protected member_ `TArray<TSharedPtr<FString>> NameSpaces;`
- L35 _protected member_ `TSharedPtr<SRigVMGraphPinEditableNameValueWidget> NameComboBox;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinUserDataPath.h` (Public)


#### class `SRigVMUserDataPath`  
`class SRigVMUserDataPath : public SCompoundWidget`  
_L18-54_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRigVMUserDataPath) : _ModelPins()`
- L26 _public prototype_ `SLATE_ARGUMENT(TArray<URigVMPin*>, ModelPins) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _protected prototype_ `FString GetUserDataPath(URigVMPin* ModelPin) const;`
- L35 _protected prototype_ `FString GetUserDataPath() const;`
- L36 _protected function_ `FText GetUserDataPathText() const`
- L37 _protected prototype_ `const FSlateBrush* GetUserDataIcon() const;`
- L38 _protected prototype_ `FLinearColor GetUserDataColor() const;`
- L39 _protected prototype_ `const FSlateBrush* GetUserDataIcon(const UNameSpacedUserData::FUserData* InUserData) const;`
- L40 _protected prototype_ `FLinearColor GetUserDataColor(const UNameSpacedUserData::FUserData* InUserData) const;`
- L41 _protected prototype_ `TSharedRef<SWidget> GetTopLevelMenuContent();`
- L42 _protected prototype_ `void FillUserDataPathMenu( FMenuBuilder& InMenuBuilder, FString InParentPath );`
- L43 _protected prototype_ `void HandleSetUserDataPath(FString InUserDataPath);`
- L45 _protected prototype_ `FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const;`
- L46 _protected prototype_ `FString GetUserDataNameSpace(URigVMPin* ModelPin) const;`
- L47 _protected prototype_ `FString GetUserDataNameSpace() const;`
- L48 _protected prototype_ `const UNameSpacedUserData* GetUserDataObject() const;`
- L49 _protected prototype_ `const UNameSpacedUserData::FUserData* GetUserData() const;`
- L51 _protected member_ `TArray<URigVMPin*> ModelPins;`
- L52 _protected member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L53 _protected member_ `bool bAllowUObjects = false;`

#### class `SRigVMGraphPinUserDataPath`  
`class SRigVMGraphPinUserDataPath : public SGraphPin`  
_L56-75_
- inherits: `SGraphPin`
- L60 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinUserDataPath)`
- L62 _public prototype_ `SLATE_ARGUMENT(TArray<URigVMPin*>, ModelPins) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L71 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L74 _protected member_ `TArray<URigVMPin*> ModelPins;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinVariableBinding.h` (Public)


#### class `SRigVMGraphVariableBinding`  
`class SRigVMGraphVariableBinding : public SCompoundWidget`  
_L16-55_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphVariableBinding) : _ModelPins() , _Asset(nullptr) , _Blueprint(nullptr) , _CanRemoveBinding(true)`
- L27 _public prototype_ `SLATE_ARGUMENT(TArray<URigVMPin*>, ModelPins) SLATE_ARGUMENT(FName, InnerVariableName) SLATE_ARGUMENT(FRigVMEditorAssetInterfacePtr, Asset) SLATE_ARGUMENT_DEPRECATED(URigVMBlueprint*, Blueprint, 5.7, "Please use Asset instead") SLATE_ARGUMENT(bool, CanRemoveBinding) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _protected prototype_ `FText GetBindingText(URigVMPin* ModelPin) const;`
- L40 _protected prototype_ `FText GetBindingText() const;`
- L41 _protected prototype_ `const FSlateBrush* GetBindingImage() const;`
- L42 _protected prototype_ `FLinearColor GetBindingColor() const;`
- L43 _protected prototype_ `bool OnCanBindProperty(FProperty* InProperty) const;`
- L44 _protected prototype_ `bool OnCanBindToClass(UClass* InClass) const;`
- L45 _protected prototype_ `void OnAddBinding(FName InPropertyName, const TArray<FBindingChainElement>& InBindingChain);`
- L46 _protected prototype_ `bool OnCanRemoveBinding(FName InPropertyName);`
- L47 _protected prototype_ `void OnRemoveBinding(FName InPropertyName);`
- L48 _protected prototype_ `void FillLocalVariableMenu( FMenuBuilder& MenuBuilder );`
- L49 _protected prototype_ `void HandleBindToLocalVariable(FRigVMGraphVariableDescription InLocalVariable);`
- L51 _protected member_ `TArray<URigVMPin*> ModelPins;`
- L52 _protected member_ `FRigVMEditorAssetInterfacePtr Blueprint;`
- L53 _protected member_ `FPropertyBindingWidgetArgs BindingArgs;`
- L54 _protected member_ `bool bCanRemoveBinding;`

#### class `SRigVMGraphPinVariableBinding`  
`class SRigVMGraphPinVariableBinding : public SGraphPin`  
_L57-79_
- inherits: `SGraphPin`
- L61 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinVariableBinding)`
- L63 _public prototype_ `SLATE_ARGUMENT(TArray<URigVMPin*>, ModelPins) SLATE_ARGUMENT_DEPRECATED(URigVMBlueprint*, Blueprint, 5.7, "Please use Asset instead") SLATE_ARGUMENT(FRigVMEditorAssetInterfacePtr, Asset) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L74 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L77 _protected member_ `TArray<URigVMPin*> ModelPins;`
- L78 _protected member_ `FRigVMEditorAssetInterfacePtr Blueprint;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMGraphPinVariableName.h` (Public)


#### class `SRigVMGraphPinVariableName`  
`class SRigVMGraphPinVariableName : public SGraphPin`  
_L13-37_
- inherits: `SGraphPin`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRigVMGraphPinVariableName)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L23 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L26 _protected prototype_ `FText GetVariableNameText() const;`
- L27 _protected prototype_ `virtual void SetVariableNameText(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L29 _protected prototype_ `TSharedRef<SWidget> MakeVariableNameItemWidget(TSharedPtr<FString> InItem);`
- L30 _protected prototype_ `void OnVariableNameChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L31 _protected prototype_ `void OnVariableNameComboBox();`
- L32 _protected prototype_ `TArray<TSharedPtr<FString>>& GetVariableNames();`
- L34 _protected member_ `TArray<TSharedPtr<FString>> VariableNames;`
- L35 _protected member_ `TSharedPtr<SRigVMGraphPinEditableNameValueWidget> NameComboBox;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMLogWidget.h` (Public)


#### class `SRigVMLogWidget`  
`class SRigVMLogWidget : public SBox`  
_L12-77_
- inherits: `SBox`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRigVMLogWidget) : _LogName(TEXT("RigVMLog")) , _LogLabel(NSLOCTEXT("SRigVMLogWidget", "RigVMLog", "RigVM Log")) , _ShowFilters(true) , _AllowClear(true) , _DiscardDuplicates(false) , _ScrollToBottom(true)`
- L25 _public prototype_ `SLATE_ATTRIBUTE(FOptionalSize, HeightOverride) SLATE_ARGUMENT(FName, LogName) SLATE_ARGUMENT(FText, LogLabel) SLATE_ARGUMENT(bool, ShowFilters);`
- L29 _public prototype_ `SLATE_ARGUMENT(bool, AllowClear);`
- L30 _public prototype_ `SLATE_ARGUMENT(bool, DiscardDuplicates);`
- L31 _public prototype_ `SLATE_ARGUMENT(bool, ScrollToBottom);`
- L34 _public prototype_ `SRigVMLogWidget();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `void BindLog(const FName& InLogName);`
- L40 _public prototype_ `void UnbindLog(const FName& InLogName);`
- L41 _public prototype_ `void BindLog(TSharedPtr<IMessageLogListing> InListing);`
- L42 _public prototype_ `void UnbindLog(TSharedPtr<IMessageLogListing> InListing);`
- L43 _public prototype_ `void BindLog(const FRigVMEditorAssetInterfacePtr InRigVMBlueprint);`
- L44 _public prototype_ `void UnbindLog(const FRigVMEditorAssetInterfacePtr InRigVMBlueprint);`
- L46 _public function_ `TSharedRef<FMessageLogListingModel> GetListing() const`
- L51 _public function_ `TSharedRef<FMessageLogListingModel> GetListing()`
- L58 _private prototype_ `void OnBoundListingChanged(TWeakPtr<IMessageLogListing> InWeakListing);`
- L60 _private member_ `TSharedPtr<FMessageLogListingModel> ListingModel;`
- L61 _private member_ `TSharedPtr<FMessageLogListingViewModel> ListingView;`
- L62 _private member_ `TArray<TWeakPtr<IMessageLogListing>> BoundListings;`
- L76 _private member_ `TMap<FName, FBoundListingInfo> ListingInfo;`

#### struct `SRigVMLogWidget::FBoundListingInfo`  
`struct FBoundListingInfo`  
_L64-74_
- L66 _public function_ `FBoundListingInfo() : NumMessages(0)`
- L71 _public prototype_ `FBoundListingInfo(const IMessageLogListing& InListing);`
- L73 _public member_ `int32 NumMessages;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMNodeLayoutWidget.h` (Public)


#### class `SRigVMNodeLayoutWidget`  
`class SRigVMNodeLayoutWidget : public SCompoundWidget`  
_L29-229_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS(SRigVMNodeLayoutWidget) : _MaxScrollBoxSize(300.f)`
- L37 _public prototype_ `SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetUncategorizedPins, OnGetUncategorizedPins) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetCategories, OnGetCategories) SLATE_EVENT(FRigVMNodeLayoutWidget_OnCategoryAdded, OnCategoryAdded) SLATE_EVENT(FRigVMNodeLayoutWidget_OnCategoryRemoved, OnCategoryRemoved) SLATE_EVENT(FRigVMNodeLayoutWidget_OnCategoryRenamed, OnCategoryRenamed) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetElementLabel, OnGetElementLabel) SLATE_EVENT(FRigVMNodeLayoutWidget_OnElementLabelChanged, OnElementLabelChanged) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetElementCategory, OnGetElementCategory) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetElementIndexInCategory, OnGetElementIndexInCategory) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetElementColor, OnGetElementColor) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetElementIcon, OnGetElementIcon) SLATE_EVENT(FRigVMNodeLayoutWidget_OnElementIndexInCategoryChanged, OnElementIndexInCategoryChanged) SLATE_EVENT(FRigVMNodeLayoutWidget_OnElementCategoryChanged, OnElementCategoryChanged) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetStructuralHash, OnGetStructuralHash) SLATE_EVENT(FRigVMNodeLayoutWidget_ValidateName, OnValidateCategoryName) SLATE_EVENT(FRigVMNodeLayoutWidget_ValidateName, OnValidateElementName) SLATE_ATTRIBUTE(FOptionalSize, MaxScrollBoxSize) SLATE_END_ARGS() SRigVMNodeLayoutWidget();`
- L59 _public prototype_ `void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `void Refresh();`
- L61 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L62 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L66 _private member_ `FRigVMNodeLayoutWidget_OnGetUncategorizedPins OnGetUncategorizedPins;`
- L67 _private member_ `FRigVMNodeLayoutWidget_OnGetCategories OnGetCategories;`
- L68 _private member_ `FRigVMNodeLayoutWidget_OnCategoryAdded OnCategoryAdded;`
- L69 _private member_ `FRigVMNodeLayoutWidget_OnCategoryRemoved OnCategoryRemoved;`
- L70 _private member_ `FRigVMNodeLayoutWidget_OnCategoryRenamed OnCategoryRenamed;`
- L71 _private member_ `FRigVMNodeLayoutWidget_OnGetElementLabel OnGetElementLabel;`
- L72 _private member_ `FRigVMNodeLayoutWidget_OnElementLabelChanged OnElementLabelChanged;`
- L73 _private member_ `FRigVMNodeLayoutWidget_OnGetElementCategory OnGetElementCategory;`
- L74 _private member_ `FRigVMNodeLayoutWidget_OnGetElementIndexInCategory OnGetElementIndexInCategory;`
- L75 _private member_ `FRigVMNodeLayoutWidget_OnGetElementColor OnGetElementColor;`
- L76 _private member_ `FRigVMNodeLayoutWidget_OnGetElementIcon OnGetElementIcon;`
- L77 _private member_ `FRigVMNodeLayoutWidget_OnElementIndexInCategoryChanged OnElementIndexInCategoryChanged;`
- L78 _private member_ `FRigVMNodeLayoutWidget_OnElementCategoryChanged OnElementCategoryChanged;`
- L79 _private member_ `FRigVMNodeLayoutWidget_OnGetStructuralHash OnGetStructuralHash;`
- L80 _private member_ `FRigVMNodeLayoutWidget_ValidateName OnValidateCategoryName;`
- L81 _private member_ `FRigVMNodeLayoutWidget_ValidateName OnValidateElementName;`
- L141 _private prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<EItemDropZone>, FRigVMNodeLayoutWidget_OnElementCanDrop, TSharedPtr<FNodeLayoutRow>, TSharedPtr<FNodeLayoutRow>, EItemDropZone);`
- L142 _private prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FRigVMNodeLayoutWidget_OnElementAcceptDrop, TSharedPtr<FNodeLayoutRow>, TSharedPtr<FNodeLayoutRow>, EItemDropZone);`
- L192 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FNodeLayoutRow> InRow, const TSharedRef<STableViewBase>& OwnerTable);`
- L193 _private prototype_ `void GetChildrenForRow(TSharedPtr<FNodeLayoutRow> InRow, TArray<TSharedPtr<FNodeLayoutRow>>& OutChildren);`
- L194 _private prototype_ `void OnItemExpansionChanged(TSharedPtr<FNodeLayoutRow> InRow, bool bExpanded);`
- L195 _private prototype_ `void OnItemSelectionChanged(TSharedPtr<FNodeLayoutRow> InRow, ESelectInfo::Type InSelectInfo);`
- L196 _private prototype_ `bool IsNodeLayoutEditable() const;`
- L197 _private prototype_ `FReply HandleAddCategory();`
- L221 _private prototype_ `FReply OnDragDetectedForRow(TSharedPtr<FNodeLayoutRow> InSourceRow);`
- L222 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, TSharedPtr<FNodeLayoutRow> InTargetRow, EItemDropZone InDropZone);`
- L223 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, TSharedPtr<FNodeLayoutRow> InTargetRow, EItemDropZone InDropZone);`
- L224 _private prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L226 _private member_ `TArray<TSharedPtr<FNodeLayoutRow>> NodeLayoutRows;`
- L227 _private member_ `TSharedPtr<STreeView<TSharedPtr<FNodeLayoutRow>>> TreeView;`
- L228 _private member_ `TOptional<uint32> LastStructuralHash;`

#### struct `SRigVMNodeLayoutWidget::FNodeLayoutRow`  
`struct FNodeLayoutRow`  
_L83-139_
- L85 _public function_ `FNodeLayoutRow() : bIsCategory(true) , bIsUncategorized(false) , Color(FLinearColor::White) , Icon(nullptr)`
- L105 _public member_ `bool bIsCategory;`
- L106 _public member_ `bool bIsUncategorized;`
- L107 _public member_ `FString Path;`
- L108 _public member_ `FString Label;`
- L109 _public member_ `FLinearColor Color;`
- L110 _public member_ `const FSlateBrush* Icon;`
- L111 _public member_ `FState State;`
- L112 _public member_ `TArray<TSharedPtr<FNodeLayoutRow>> ChildRows;`
- L113 _public member_ `FSimpleDelegate OnRequestRename;`
- L115 _public function_ `bool IsCategory() const`
- L120 _public function_ `bool IsPin() const`
- L125 _public function_ `bool IsUncategorizedPin() const`
- L130 _public function_ `bool IsCategorizedPin() const`
- L135 _public function_ `void RequestRename()`

#### struct `SRigVMNodeLayoutWidget::FNodeLayoutRow::FState`  
`struct FState`  
_L93-103_
- L95 _public function_ `FState() : bExpanded(false) , bSelected(false)`
- L101 _public member_ `bool bExpanded;`
- L102 _public member_ `bool bSelected;`

#### class `SRigVMNodeLayoutWidget::SRigVMNowLayoutRow`  
`class SRigVMNowLayoutRow : public STableRow<TSharedPtr<FNodeLayoutRow>>`  
_L144-190_
- inherits: `STableRow<TSharedPtr<FNodeLayoutRow>>`
- L149 _public function_ `SLATE_BEGIN_ARGS(SRigVMNowLayoutRow)`
- L151 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FNodeLayoutRow>, NodeLayoutRow) SLATE_EVENT(FRigVMNodeLayoutWidget_OnGetCategories, OnGetCategories) SLATE_EVENT(FRigVMNodeLayoutWidget_OnCategoryRenamed, OnCategoryRenamed) SLATE_EVENT(FRigVMNodeLayoutWidget_OnElementLabelChanged, OnElementLabelChanged) SLATE_EVENT(FRigVMNodeLayoutWidget_OnElementCategoryChanged, OnElementCategoryChanged) SLATE_EVENT(FRigVMNodeLayoutWidget_OnCategoryRemoved, OnCategoryRemoved) SLATE_EVENT(FRigVMNodeLayoutWidget_ValidateName, OnValidateCategoryName) SLATE_EVENT(FRigVMNodeLayoutWidget_ValidateName, OnValidateElementName) SLATE_EVENT( FOnCanAcceptDrop, OnCanAcceptDrop ) SLATE_EVENT( FOnAcceptDrop, OnAcceptDrop ) SLATE_EVENT( FOnPaintDropIndicator, OnPaintDropIndicator ) SLATE_EVENT( FOnDragDetected, OnDragDetected ) SLATE_EVENT( FOnTableRowDragEnter, OnDragEnter ) SLATE_EVENT( FOnTableRowDragLeave, OnDragLeave ) SLATE_EVENT( FOnTableRowDrop, OnDrop ) SLATE_END_ARGS() virtual ~SRigVMNowLayoutRow() override;`
- L171 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L172 _public prototype_ `static TSharedPtr<SInlineEditableTextBlock> ConstructLabel(TSharedPtr<FNodeLayoutRow> InNodeLayoutRow, TSharedRef<SHorizontalBox> OutHorizontalBox, SRigVMNowLayoutRow* InRow);`
- L174 _public function_ `TSharedPtr<FNodeLayoutRow> GetNodeLayoutRow() const`
- L175 _public prototype_ `void OnLabelCommitted(const FText& InText, ETextCommit::Type InCommitType) const;`
- L176 _public prototype_ `bool OnVerifyLabelChanged(const FText& InText, FText& OutErrorMessage);`
- L177 _public prototype_ `bool IsSelected() const;`
- L180 _private member_ `TSharedPtr<FNodeLayoutRow> NodeLayoutRow;`
- L181 _private member_ `FRigVMNodeLayoutWidget_OnGetCategories OnGetCategories;`
- L182 _private member_ `FRigVMNodeLayoutWidget_OnCategoryRenamed OnCategoryRenamed;`
- L183 _private member_ `FRigVMNodeLayoutWidget_OnElementLabelChanged OnElementLabelChanged;`
- L184 _private member_ `FRigVMNodeLayoutWidget_OnElementCategoryChanged OnElementCategoryChanged;`
- L185 _private member_ `FRigVMNodeLayoutWidget_OnCategoryRemoved OnCategoryRemoved;`
- L186 _private member_ `FRigVMNodeLayoutWidget_ValidateName OnValidateCategoryName;`
- L187 _private member_ `FRigVMNodeLayoutWidget_ValidateName OnValidateElementName;`
- L189 _private member_ `TSharedPtr<SInlineEditableTextBlock> LabelEditWidget;`

#### class `SRigVMNodeLayoutWidget::FRigVMNodeLayoutDragDropOp`  
`class FRigVMNodeLayoutDragDropOp : public FDragDropOperation`  
_L199-219_
- inherits: `FDragDropOperation`
- L202 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigVMNodeLayoutDragDropOp, FDragDropOperation) static TSharedRef<FRigVMNodeLayoutDragDropOp> New(const TArray<TSharedPtr<FNodeLayoutRow>>& InNodeLayoutRows);`
- L206 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L207 _public prototype_ `virtual FVector2D GetDecoratorPosition() const override;`
- L208 _public function_ `virtual bool IsWindowlessOperation() const override`
- L210 _public function_ `const TArray<TSharedPtr<FNodeLayoutRow>>& GetNodeLayoutRows() const`
- L218 _private member_ `TArray<TSharedPtr<FNodeLayoutRow>> NodeLayoutRows;` — Data for the property paths this item represents

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FString> , FRigVMNodeLayoutWidget_OnGetUncategorizedPins);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<FString> , FRigVMNodeLayoutWidget_OnGetUncategorizedPins);`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMPinCategory> , FRigVMNodeLayoutWidget_OnGetCategories);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMPinCategory> , FRigVMNodeLayoutWidget_OnGetCategories);`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMNodeLayoutWidget_OnCategoryAdded, FString );`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMNodeLayoutWidget_OnCategoryAdded, FString );`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMNodeLayoutWidget_OnCategoryRemoved, FString );`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMNodeLayoutWidget_OnCategoryRemoved, FString );`
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnCategoryRenamed, FString , FString );`
- L17 _prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnCategoryRenamed, FString , FString );`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMNodeLayoutWidget_OnGetElementLabel, FString );`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMNodeLayoutWidget_OnGetElementLabel, FString );`
- L19 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementLabelChanged, FString , FString );`
- L19 _prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementLabelChanged, FString , FString );`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMNodeLayoutWidget_OnGetElementCategory, FString );`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FRigVMNodeLayoutWidget_OnGetElementCategory, FString );`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FRigVMNodeLayoutWidget_OnGetElementIndexInCategory, FString );`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FRigVMNodeLayoutWidget_OnGetElementIndexInCategory, FString );`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRigVMNodeLayoutWidget_OnGetElementColor, FString );`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FRigVMNodeLayoutWidget_OnGetElementColor, FString );`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FRigVMNodeLayoutWidget_OnGetElementIcon, FString );`
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FRigVMNodeLayoutWidget_OnGetElementIcon, FString );`
- L24 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementIndexInCategoryChanged, FString , int32 );`
- L24 _prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementIndexInCategoryChanged, FString , int32 );`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementCategoryChanged, FString , FString );`
- L25 _prototype_ `DECLARE_DELEGATE_TwoParams(FRigVMNodeLayoutWidget_OnElementCategoryChanged, FString , FString );`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(uint32, FRigVMNodeLayoutWidget_OnGetStructuralHash);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal(uint32, FRigVMNodeLayoutWidget_OnGetStructuralHash);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMNodeLayoutWidget_ValidateName, FString , FString , FText& );`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRigVMNodeLayoutWidget_ValidateName, FString , FString , FText& );`
- L141 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TOptional<EItemDropZone>, FRigVMNodeLayoutWidget_OnElementCanDrop, TSharedPtr<FNodeLayoutRow>, TSharedPtr<FNodeLayoutRow>, EItemDropZone);`
- L142 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FRigVMNodeLayoutWidget_OnElementAcceptDrop, TSharedPtr<FNodeLayoutRow>, TSharedPtr<FNodeLayoutRow>, EItemDropZone);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMNodePreviewWidget.h` (Public)


#### class `SRigVMNodePreviewWidget`  
`class SRigVMNodePreviewWidget : public SCompoundWidget`  
_L11-36_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SRigVMNodePreviewWidget) : _Padding(16.f) , _NodeEnabled(false) , _PinDragAndDropEnabled(false)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(FMargin, Padding) SLATE_ARGUMENT(TSharedPtr<FRigVMMinimalEnvironment>, Environment) SLATE_ATTRIBUTE(bool, NodeEnabled) SLATE_ATTRIBUTE(bool, PinDragAndDropEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L31 _private prototype_ `void UpdateNodeWidget();`
- L33 _private member_ `TSharedPtr<FRigVMMinimalEnvironment> Environment;`
- L34 _private member_ `TAttribute<bool> NodeEnabledAttribute;`
- L35 _private member_ `TAttribute<bool> PinDragAndDropEnabledAttribute;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMSwapAssetReferencesWidget.h` (Public)


#### class `FRigVMSwapAssetReferencesContext`  
`class FRigVMSwapAssetReferencesContext : public FRigVMTreeContext`  
_L14-60_
- inherits: `FRigVMTreeContext`
- L17 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMSwapAssetReferencesContext, FRigVMTreeContext) const FAssetData& GetSourceAsset()`
- L24 _public function_ `void SetSourceAsset(const FAssetData& InAsset)`
- L29 _public function_ `const FAssetData& GetTargetAsset()`
- L34 _public function_ `void SetTargetAsset(const FAssetData& InAsset)`
- L39 _public function_ `const TArray<FSoftObjectPath>& GetReferences()`
- L44 _public function_ `void SetReferences(const TArray<FSoftObjectPath>& InReferences)`
- L49 _public function_ `void ClearReferences()`
- L54 _public prototype_ `virtual uint32 GetVisibleChildrenHash() const override;`
- L57 _private member_ `FAssetData SourceAsset;`
- L58 _private member_ `FAssetData TargetAsset;`
- L59 _private member_ `TArray<FSoftObjectPath> References;`

#### class `FRigVMTreeReferenceNode`  
`class FRigVMTreeReferenceNode : public FRigVMTreeNode`  
_L63-87_
- inherits: `FRigVMTreeNode`
- desc: A single reference node
- L66 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeReferenceNode, FRigVMTreeNode) FRigVMTreeReferenceNode(const FSoftObjectPath& InModulePath) : FRigVMTreeNode(InModulePath.GetSubPathString()) , ModulePath(InModulePath)`
- L75 _public function_ `virtual bool IsCheckable() const override`
- L80 _public function_ `const FSoftObjectPath& GetReferencePath() const`
- L86 _private member_ `FSoftObjectPath ModulePath;`

#### class `FRigVMTreeAssetRefAssetNode`  
`class FRigVMTreeAssetRefAssetNode : public FRigVMTreePackageNode`  
_L90-110_
- inherits: `FRigVMTreePackageNode`
- desc: The asset node which contains multiple reference nodes
- L93 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeAssetRefAssetNode, FRigVMTreePackageNode) FRigVMTreeAssetRefAssetNode(const FAssetData& InAssetData) : FRigVMTreePackageNode(InAssetData)`
- L101 _public function_ `virtual bool IsCheckable() const override`
- L107 _protected prototype_ `virtual TArray<TSharedRef<FRigVMTreeNode>> GetChildrenImpl(const TSharedRef<FRigVMTreeContext>& InContext) const override;`
- L109 _protected member_ `mutable TArray<TSharedRef<FRigVMTreeNode>> AssetRefNodes;`

#### class `FRigVMTreeTargetAssetFilter`  
`class FRigVMTreeTargetAssetFilter : public FRigVMTreeFilter`  
_L113-118_
- inherits: `FRigVMTreeFilter`
- desc: Filters the source asset from the target asset list
- L116 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeTargetAssetFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeAssetVariantFilter`  
`class FRigVMTreeAssetVariantFilter : public FRigVMTreeFilter`  
_L121-139_
- inherits: `FRigVMTreeFilter`
- desc: Filters target assets to show only variants of the source asset
- L124 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeAssetVariantFilter, FRigVMTreeFilter);`
- L125 _public function_ `virtual bool CanBeToggledInUI() const override`
- L129 _public function_ `virtual bool IsInvertedInUI() const override`
- L133 _public prototype_ `virtual FText GetLabel() const override;`
- L135 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`
- L138 _private member_ `mutable TMap<FString, TArray<FRigVMVariantRef>> SourceVariants;`

#### class `FRigVMSwapAssetReferenceTask`  
`class FRigVMSwapAssetReferenceTask : public FRigVMTreeTask`  
_L141-170_
- inherits: `FRigVMTreeTask`
- L144 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMSwapAssetReferenceTask, FRigVMTreeTask) FRigVMSwapAssetReferenceTask(const FSoftObjectPath InReferencePath, const FAssetData& InNewAsset, const FOnSwapReference& InSwapFunction) : ReferencePath(InReferencePath) , NewAsset(InNewAsset) , SwapFunction(InSwapFunction)`
- L153 _public prototype_ `virtual bool Execute(const TSharedRef<FRigVMTreePhase>& InPhase) override;`
- L155 _public function_ `virtual bool RequiresRefresh() const override`
- L160 _public function_ `virtual bool RequiresUndo() const override`
- L167 _private member_ `FSoftObjectPath ReferencePath;`
- L168 _private member_ `FAssetData NewAsset;`
- L169 _private member_ `FOnSwapReference SwapFunction;`

#### class `SRigVMSwapAssetReferencesWidget`  
`class SRigVMSwapAssetReferencesWidget : public SCompoundWidget`  
_L172-223_
- inherits: `SCompoundWidget`
- L176 _public function_ `SLATE_BEGIN_ARGS(SRigVMSwapAssetReferencesWidget) : _SkipPickingRefs(false) , _EnableUndo(false) , _CloseOnSuccess(false)`
- L181 _public prototype_ `SLATE_ARGUMENT(FAssetData, Source) SLATE_ARGUMENT(FAssetData, Target) SLATE_ARGUMENT(TArray<FSoftObjectPath>, ReferencePaths) SLATE_ARGUMENT(bool, SkipPickingRefs) SLATE_ARGUMENT(bool, EnableUndo) SLATE_ARGUMENT(bool, CloseOnSuccess) SLATE_ARGUMENT(TArray<FRigVMAssetDataFilter>, SourceAssetFilters) SLATE_ARGUMENT(TArray<FRigVMAssetDataFilter>, TargetAssetFilters) SLATE_EVENT(FOnGetReferences, OnGetReferences) SLATE_EVENT(FOnSwapReference, OnSwapReference) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L195 _public function_ `TSharedRef<SRigVMBulkEditWidget> GetBulkEditWidget()`
- L202 _private member_ `TSharedPtr<SRigVMBulkEditWidget> BulkEditWidget;`
- L203 _private member_ `TSharedPtr<FRigVMSwapAssetReferencesContext> PickTargetContext;`
- L204 _private member_ `TSharedPtr<FRigVMSwapAssetReferencesContext> PickAssetRefsContext;`
- L205 _private member_ `bool bSkipPickingRefs = false;`
- L207 _private member_ `TArray<FRigVMAssetDataFilter> SourceAssetFilters;`
- L208 _private member_ `TArray<FRigVMAssetDataFilter> TargetAssetFilters;`
- L210 _private member_ `FOnGetReferences OnGetReferences;`
- L211 _private member_ `FOnSwapReference OnSwapReference;`
- L213 _private prototype_ `TArray<TSharedRef<FRigVMTreeNode>> GetAssetNodes(const FArguments& InArgs, const int32& InPhase);`
- L214 _private prototype_ `void OnPhaseActivated(TSharedRef<FRigVMTreePhase> Phase);`
- L215 _private prototype_ `FReply OnNodeSelected(TSharedRef<FRigVMTreeNode> Node);`
- L216 _private prototype_ `FReply OnNodeDoubleClicked(TSharedRef<FRigVMTreeNode> Node);`
- L217 _private prototype_ `void SetSourceAsset(const FAssetData& InAsset);`
- L218 _private prototype_ `void SetTargetAsset(const FAssetData& InAsset);`
- L220 _private member_ `static constexpr int32 PHASE_PICKSOURCE = 0;`
- L221 _private member_ `static constexpr int32 PHASE_PICKTARGET = 1;`
- L222 _private member_ `static constexpr int32 PHASE_PICKASSETREFS = 2;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMEDITOR_API`
- L11 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FSoftObjectPath>, FOnGetReferences, FAssetData);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FSoftObjectPath>, FOnGetReferences, FAssetData);`
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSwapReference, FSoftObjectPath, FAssetData);`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSwapReference, FSoftObjectPath, FAssetData);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMSwapFunctionsWidget.h` (Public)


#### class `FRigVMSwapFunctionContext`  
`class FRigVMSwapFunctionContext : public FRigVMTreeContext`  
_L16-46_
- inherits: `FRigVMTreeContext`
- L19 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMSwapFunctionContext, FRigVMTreeContext) const FRigVMGraphFunctionIdentifier& GetSourceIdentifier()`
- L26 _public function_ `void SetSourceIdentifier(const FRigVMGraphFunctionIdentifier& InIdentifier)`
- L31 _public function_ `const FRigVMGraphFunctionIdentifier& GetTargetIdentifier()`
- L36 _public function_ `void SetTargetIdentifier(const FRigVMGraphFunctionIdentifier& InIdentifier)`
- L41 _public prototype_ `virtual uint32 GetVisibleChildrenHash() const override;`
- L44 _private member_ `FRigVMGraphFunctionIdentifier SourceIdentifier;`
- L45 _private member_ `FRigVMGraphFunctionIdentifier TargetIdentifier;`

#### class `FRigVMTreeFunctionRefNode`  
`class FRigVMTreeFunctionRefNode : public FRigVMTreeNode`  
_L48-79_
- inherits: `FRigVMTreeNode`
- L51 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionRefNode, FRigVMTreeNode) FRigVMTreeFunctionRefNode(const URigVMFunctionReferenceNode* InFunctionReferenceNode) : FRigVMTreeNode(InFunctionReferenceNode->GetPathName()) , Identifier(InFunctionReferenceNode->GetFunctionIdentifier())`
- L59 _public function_ `FRigVMTreeFunctionRefNode(const FRigVMReferenceNodeData& InRefNodeData) : FRigVMTreeNode(InRefNodeData.ReferenceNodePath) , Identifier(InRefNodeData.ReferencedFunctionIdentifier)`
- L65 _public function_ `virtual bool IsCheckable() const override`
- L70 _public function_ `const FRigVMGraphFunctionIdentifier& GetIdentifier() const`
- L75 _public prototype_ `virtual const FSlateBrush* GetIconAndTint(FLinearColor& OutColor) const override;`
- L78 _private member_ `FRigVMGraphFunctionIdentifier Identifier;`

#### class `FRigVMTreeFunctionRefGraphNode`  
`class FRigVMTreeFunctionRefGraphNode : public FRigVMTreeNode`  
_L81-106_
- inherits: `FRigVMTreeNode`
- L84 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionRefGraphNode, FRigVMTreeNode) FRigVMTreeFunctionRefGraphNode(const URigVMGraph* InFunctionGraph);`
- L88 _public prototype_ `virtual FText GetLabel() const override;`
- L90 _public prototype_ `virtual const FSlateBrush* GetIconAndTint(FLinearColor& OutColor) const override;`
- L92 _public function_ `virtual bool IsCheckable() const override`
- L97 _public prototype_ `virtual void DirtyChildren() override;`
- L98 _public prototype_ `bool ContainsFunctionReference(const TSharedRef<FRigVMTreeContext>& InContext) const;`
- L101 _protected prototype_ `virtual TArray<TSharedRef<FRigVMTreeNode>> GetChildrenImpl(const TSharedRef<FRigVMTreeContext>& InContext) const override;`
- L103 _protected member_ `TWeakObjectPtr<const URigVMGraph> WeakGraph;`
- L104 _protected member_ `TOptional<FText> OptionalLabel;`
- L105 _protected member_ `mutable TArray<TSharedRef<FRigVMTreeNode>> FunctionRefNodes;`

#### class `FRigVMTreeFunctionRefAssetNode`  
`class FRigVMTreeFunctionRefAssetNode : public FRigVMTreePackageNode`  
_L108-131_
- inherits: `FRigVMTreePackageNode`
- L111 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionRefAssetNode, FRigVMTreePackageNode) FRigVMTreeFunctionRefAssetNode(const FAssetData& InAssetData);`
- L115 _public function_ `virtual bool IsCheckable() const override`
- L120 _public prototype_ `virtual void DirtyChildren() override;`
- L123 _protected prototype_ `virtual TArray<TSharedRef<FRigVMTreeNode>> GetChildrenImpl(const TSharedRef<FRigVMTreeContext>& InContext) const override;`
- L125 _protected member_ `mutable TArray<TSharedRef<FRigVMTreeNode>> LoadedGraphNodes;`
- L126 _protected member_ `mutable TArray<TSharedRef<FRigVMTreeNode>> MetaDataBasedNodes;`
- L127 _protected member_ `mutable TArray<FRigVMReferenceNodeData> ReferenceNodeDatas;`

#### class `FRigVMTreeFunctionIdentifierNode`  
`class FRigVMTreeFunctionIdentifierNode : public FRigVMTreeNode`  
_L133-156_
- inherits: `FRigVMTreeNode`
- L136 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionIdentifierNode, FRigVMTreeNode) FRigVMTreeFunctionIdentifierNode(const FRigVMGraphFunctionIdentifier& InIdentifier) : FRigVMTreeNode(InIdentifier.GetLibraryNodePath()) , Identifier(InIdentifier)`
- L144 _public prototype_ `virtual FText GetLabel() const override;`
- L145 _public function_ `virtual bool IsCheckable() const override`
- L146 _public prototype_ `virtual const FSlateBrush* GetIconAndTint(FLinearColor& OutColor) const override;`
- L147 _public prototype_ `virtual const TArray<FRigVMTag>& GetTags() const override;`
- L149 _public function_ `const FRigVMGraphFunctionIdentifier& GetIdentifier() const`
- L155 _private member_ `FRigVMGraphFunctionIdentifier Identifier;`

#### class `FRigVMTreeFunctionIdentifierAssetNode`  
`class FRigVMTreeFunctionIdentifierAssetNode : public FRigVMTreePackageNode`  
_L158-176_
- inherits: `FRigVMTreePackageNode`
- L161 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionIdentifierAssetNode, FRigVMTreePackageNode) FRigVMTreeFunctionIdentifierAssetNode(const FAssetData& InAssetData) : FRigVMTreePackageNode(InAssetData)`
- L168 _public function_ `virtual bool ShouldExpandByDefault() const override`
- L173 _public function_ `virtual bool IsCheckable() const override`
- L174 _public prototype_ `void AddChildNode(const TSharedRef<FRigVMTreeNode>& InNode);`
- L175 _public prototype_ `virtual void DirtyChildren() override;`

#### class `FRigVMTreeEmptyFunctionRefGraphFilter`  
`class FRigVMTreeEmptyFunctionRefGraphFilter : public FRigVMTreeFilter`  
_L178-183_
- inherits: `FRigVMTreeFilter`
- L181 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeEmptyFunctionRefGraphFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeEmptyFunctionRefAssetFilter`  
`class FRigVMTreeEmptyFunctionRefAssetFilter : public FRigVMTreeFilter`  
_L185-190_
- inherits: `FRigVMTreeFilter`
- L188 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeEmptyFunctionRefAssetFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeFunctionWithNoRefsFilter`  
`class FRigVMTreeFunctionWithNoRefsFilter : public FRigVMTreeFilter`  
_L192-206_
- inherits: `FRigVMTreeFilter`
- L195 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionWithNoRefsFilter, FRigVMTreeFilter);`
- L196 _public function_ `virtual bool CanBeToggledInUI() const override`
- L200 _public function_ `virtual bool IsInvertedInUI() const override`
- L204 _public prototype_ `virtual FText GetLabel() const override;`
- L205 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeSourceFunctionFilter`  
`class FRigVMTreeSourceFunctionFilter : public FRigVMTreeFilter`  
_L208-213_
- inherits: `FRigVMTreeFilter`
- L211 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeSourceFunctionFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeTargetFunctionFilter`  
`class FRigVMTreeTargetFunctionFilter : public FRigVMTreeFilter`  
_L215-220_
- inherits: `FRigVMTreeFilter`
- L218 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeTargetFunctionFilter, FRigVMTreeFilter) virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`

#### class `FRigVMTreeFunctionVariantFilter`  
`class FRigVMTreeFunctionVariantFilter : public FRigVMTreeFilter`  
_L222-242_
- inherits: `FRigVMTreeFilter`
- L225 _public prototype_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMTreeFunctionVariantFilter, FRigVMTreeFilter);`
- L226 _public function_ `virtual bool CanBeToggledInUI() const override`
- L230 _public function_ `virtual bool IsInvertedInUI() const override`
- L234 _public prototype_ `virtual FText GetLabel() const override;`
- L235 _public prototype_ `virtual bool Filters(TSharedRef<FRigVMTreeNode>& InNode, const TSharedRef<FRigVMTreeContext>& InContext) override;`
- L238 _private prototype_ `bool IsFunctionVariant(const FRigVMGraphFunctionIdentifier& InIdentifier) const;`
- L239 _private prototype_ `bool IsFunctionVariantOf(const FRigVMGraphFunctionIdentifier& InIdentifier, const FRigVMGraphFunctionIdentifier& InSourceIdentifier) const;`
- L240 _private member_ `mutable TMap<FString,bool> LibraryNodePathToIsVariant;`
- L241 _private member_ `mutable TMap<FString,TArray<FRigVMGraphFunctionIdentifier>> LibraryNodePathToVariants;`

#### class `FRigVMSwapFunctionTask`  
`class FRigVMSwapFunctionTask : public FRigVMTreeTask`  
_L244-279_
- inherits: `FRigVMTreeTask`
- L247 _public function_ `DEFINE_RIGVMTREETOOLKIT_ELEMENT(FRigVMSwapFunctionTask, FRigVMTreeTask) FRigVMSwapFunctionTask(const FString InObjectPath, const FRigVMGraphFunctionIdentifier& InIdentifier) : ObjectPath(InObjectPath) , Identifier(InIdentifier)`
- L255 _public prototype_ `virtual bool Execute(const TSharedRef<FRigVMTreePhase>& InPhase) override;`
- L257 _public function_ `virtual bool RequiresRefresh() const override`
- L262 _public function_ `virtual bool RequiresUndo() const override`
- L267 _public function_ `virtual TArray<FString> GetAffectedNodes() const override`
- L274 _private prototype_ `URigVMFunctionReferenceNode* GetReferenceNode(const TSharedRef<FRigVMTreePhase>& InPhase) const;`
- L275 _private prototype_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAsset(const TSharedRef<FRigVMTreePhase>& InPhase) const override;`
- L277 _private member_ `FString ObjectPath;`
- L278 _private member_ `FRigVMGraphFunctionIdentifier Identifier;`

#### class `SRigVMSwapFunctionsWidget`  
`class SRigVMSwapFunctionsWidget : public SCompoundWidget`  
_L281-327_
- inherits: `SCompoundWidget`
- L285 _public function_ `SLATE_BEGIN_ARGS(SRigVMSwapFunctionsWidget) : _SkipPickingFunctionRefs(false) , _EnableUndo(false) , _CloseOnSuccess(false)`
- L290 _public prototype_ `SLATE_ARGUMENT(FRigVMGraphFunctionIdentifier, Source) SLATE_ARGUMENT(FRigVMGraphFunctionIdentifier, Target) SLATE_ARGUMENT(TArray<URigVMFunctionReferenceNode*>, FunctionReferenceNodes) SLATE_ARGUMENT(TArray<URigVMGraph*>, Graphs) SLATE_ARGUMENT(TArray<FAssetData>, Assets) SLATE_ARGUMENT(bool, SkipPickingFunctionRefs) SLATE_ARGUMENT(bool, EnableUndo) SLATE_ARGUMENT(bool, CloseOnSuccess) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L302 _public function_ `TSharedRef<SRigVMBulkEditWidget> GetBulkEditWidget()`
- L309 _private member_ `TSharedPtr<SRigVMBulkEditWidget> BulkEditWidget;`
- L310 _private member_ `TSharedPtr<FRigVMSwapFunctionContext> PickTargetContext;`
- L311 _private member_ `TSharedPtr<FRigVMSwapFunctionContext> PickFunctionRefsContext;`
- L312 _private member_ `TSharedPtr<FRigVMMinimalEnvironment> SourcePreviewEnvironment;`
- L313 _private member_ `TSharedPtr<FRigVMMinimalEnvironment> TargetPreviewEnvironment;`
- L314 _private member_ `bool bSkipPickingFunctionRefs = false;`
- L316 _private prototype_ `static TArray<TSharedRef<FRigVMTreeNode>> GetFunctionIdentifierNodes(const FArguments& InArgs);`
- L317 _private prototype_ `static TArray<TSharedRef<FRigVMTreeNode>> GetFunctionRefNodes(const FArguments& InArgs);`
- L318 _private prototype_ `void OnPhaseActivated(TSharedRef<FRigVMTreePhase> Phase);`
- L319 _private prototype_ `FReply OnNodeSelected(TSharedRef<FRigVMTreeNode> Node);`
- L320 _private prototype_ `FReply OnNodeDoubleClicked(TSharedRef<FRigVMTreeNode> Node);`
- L321 _private prototype_ `void SetSourceFunction(const FRigVMGraphFunctionIdentifier& InIdentifier);`
- L322 _private prototype_ `void SetTargetFunction(const FRigVMGraphFunctionIdentifier& InIdentifier);`
- L324 _private member_ `static constexpr int32 PHASE_PICKSOURCE = 0;`
- L325 _private member_ `static constexpr int32 PHASE_PICKTARGET = 1;`
- L326 _private member_ `static constexpr int32 PHASE_PICKFUNCTIONREFS = 2;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMEDITOR_API`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMVariableMappingWidget.h` (Public)


#### struct `FRigVMVariableMappingInfo`  
`struct FRigVMVariableMappingInfo`  
_L18-60_
- L23 _public member_ `FName PropertyName;` — This is the property that is the most shallow type It will be Transform.Translation.X
- L25 _public member_ `FString DisplayName;` — Display Name
- L30 _public member_ `TArray<TSharedPtr<FRigVMVariableMappingInfo>> Children;` — List of Children in theory, this actually shouldn't be active if you have children but it represent each raw nonetheless this is to map curve which is always float
- L33 _public function_ `static TSharedRef<FRigVMVariableMappingInfo> Make(const FName InPathName)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L38 _public function_ `FName GetPathName() const`
- L43 _public function_ `FString GetDisplayName() const`
- L50 _protected function_ `FRigVMVariableMappingInfo(const FName InPathName) : PropertyName(InPathName)` — Hidden constructor, always use Make above
- L59 _protected function_ `FRigVMVariableMappingInfo()` — Hidden constructor, always use Make above

#### class `SRigVMVariableMappingTreeRow`  
`class SRigVMVariableMappingTreeRow : public STableRow< TSharedPtr<FRigVMVariableMappingInfoPtr> >`  
_L82-135_
- inherits: `STableRow<TSharedPtr<FRigVMVariableMappingInfoPtr>>`
- L87 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariableMappingTreeRow)`
- L90 _public prototype_ `SLATE_ARGUMENT(FRigVMVariableMappingInfoPtr, Item) SLATE_EVENT(FOnRigVMVariableMappingChanged, OnVariableMappingChanged) SLATE_EVENT(FOnRigVMGetVariableMapping, OnGetVariableMapping) SLATE_EVENT(FOnRigVMGetAvailableMapping, OnGetAvailableMapping) SLATE_EVENT(FOnRigVMGetFilteredText, OnGetFilteredText) SLATE_EVENT(FOnRigVMVarOptionAvailable, OnVariableOptionAvailable);` — The item for this row
- L96 _public prototype_ `SLATE_EVENT(FOnRigVMPinCheckStateChanged, OnPinCheckStateChanged) SLATE_EVENT(FOnRigVMPinGetCheckState, OnPinGetCheckState) SLATE_EVENT(FOnRigVMPinIsCheckEnabled, OnPinIsEnabledCheckState) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L106 _private member_ `TSharedPtr<SSearchableComboBox> VarOptionComboBox;` — Widget used to display the list of variable option list
- L107 _private member_ `TArray< TSharedPtr< FString > > VariableOptionList;`
- L110 _private member_ `FRigVMVariableMappingInfoPtr Item;` — The name and weight of the variable option
- L113 _private prototype_ `FReply OnClearButtonClicked();` — Curve combo box options
- L114 _private prototype_ `FText GetFilterText() const;`
- L116 _private prototype_ `TSharedRef<SWidget> MakeVarOptionComboWidget(TSharedPtr<FString> InItem);`
- L117 _private prototype_ `void OnVarOptionSourceChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L118 _private prototype_ `FText GetVarOptionComboBoxContent() const;`
- L119 _private prototype_ `FText GetVarOptionComboBoxToolTip() const;`
- L120 _private prototype_ `void OnVarOptionComboOpening();`
- L121 _private prototype_ `bool IsVarOptionEnabled() const;`
- L123 _private prototype_ `ECheckBoxState IsPinChecked() const;`
- L124 _private prototype_ `void OnPinCheckStatusChanged(ECheckBoxState NewState);`
- L125 _private prototype_ `bool IsPinEnabled() const;`
- L127 _private member_ `FOnRigVMVariableMappingChanged OnVariableMappingChanged;`
- L128 _private member_ `FOnRigVMGetVariableMapping OnGetVariableMapping;`
- L129 _private member_ `FOnRigVMGetAvailableMapping OnGetAvailableMapping;`
- L130 _private member_ `FOnRigVMGetFilteredText OnGetFilteredText;`
- L131 _private member_ `FOnRigVMVarOptionAvailable OnVariableOptionAvailable;`
- L132 _private member_ `FOnRigVMPinCheckStateChanged OnPinCheckStateChanged;`
- L133 _private member_ `FOnRigVMPinGetCheckState OnPinGetCheckState;`
- L134 _private member_ `FOnRigVMPinIsCheckEnabled OnPinIsEnabledCheckState;`

#### class `SRigVMVariableMappingWidget`  
`class SRigVMVariableMappingWidget : public SCompoundWidget`  
_L139-235_
- inherits: `SCompoundWidget`
- L142 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariableMappingWidget)`
- L145 _public prototype_ `SLATE_EVENT(FOnRigVMVariableMappingChanged, OnVariableMappingChanged) SLATE_EVENT(FOnRigVMGetVariableMapping, OnGetVariableMapping) SLATE_EVENT(FOnRigVMGetAvailableMapping, OnGetAvailableMapping) SLATE_EVENT(FOnRigVMCreateVariableMapping, OnCreateVariableMapping) SLATE_EVENT(FOnRigVMGetFilteredText, OnGetFilteredText) SLATE_EVENT(FOnRigVMVarOptionAvailable, OnVariableOptionAvailable);`
- L151 _public prototype_ `SLATE_EVENT(FOnRigVMPinCheckStateChanged, OnPinCheckStateChanged) SLATE_EVENT(FOnRigVMPinGetCheckState, OnPinGetCheckState) SLATE_EVENT(FOnRigVMPinIsCheckEnabled, OnPinIsEnabledCheckState) SLATE_END_ARGS() void Construct(const FArguments& InArgs );`
- L170 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L180 _public prototype_ `void OnFilterTextCommitted(const FText& SearchText, ETextCommit::Type CommitInfo);` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L190 _public prototype_ `TSharedRef<ITableRow> GenerateVariableMappingRow(TSharedPtr<FRigVMVariableMappingInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L195 _public prototype_ `void RefreshVariableMappingList();` — Handler for the delete of retarget source
- L203 _private function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L206 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L209 _private member_ `TSharedPtr<SRigVMVariableMappingTreeView> VariableMappingTreeView;` — Widget used to display the list of retarget sources
- L212 _private member_ `TArray< TSharedPtr<FRigVMVariableMappingInfo> > VariableMappingList;` — A list of variable mapping list. Used by the VariableMappingListView.
- L215 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L218 _private prototype_ `void PostUndo();` — Delegate for undo/redo transaction
- L221 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(TSharedPtr<FRigVMVariableMappingInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Make a single tree row widget
- L224 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FRigVMVariableMappingInfo> InInfo, TArray< TSharedPtr<FRigVMVariableMappingInfo> >& OutChildren);` — Get the children for the provided bone info
- L226 _private member_ `FOnRigVMGetAvailableMapping OnGetAvailableMappingDelegate;`
- L227 _private member_ `FOnRigVMVariableMappingChanged OnVariableMappingChangedDelegate;`
- L228 _private member_ `FOnRigVMGetVariableMapping OnGetVariableMappingDelegate;`
- L229 _private member_ `FOnRigVMCreateVariableMapping OnCreateVariableMappingDelegate;`
- L230 _private member_ `FOnRigVMVarOptionAvailable OnVariableOptionAvailableDelegate;`
- L231 _private member_ `FOnRigVMPinCheckStateChanged OnPinCheckStateChangedDelegate;`
- L232 _private member_ `FOnRigVMPinGetCheckState OnPinGetCheckStateDelegate;`
- L233 _private member_ `FOnRigVMPinIsCheckEnabled OnPinIsEnabledCheckStateDelegate;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMEDITOR_API`
- L65 _typedef_ `typedef TSharedPtr< FRigVMVariableMappingInfo > FRigVMVariableMappingInfoPtr;`
- L67 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRigVMVariableMappingChanged, const FName& , const FName& ) DECLARE_DELEGATE_RetVal_OneParam(FName, FOnRigVMGetVariableMapping, const FName& )`
- L67 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRigVMVariableMappingChanged, const FName& , const FName& ) DECLARE_DELEGATE_RetVal_OneParam(FName, FOnRigVMGetVariableMapping, const FName& )`
- L68 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnRigVMGetVariableMapping, const FName& )`
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRigVMGetAvailableMapping, const FName& , TArray<FName>& )` — type verified, and make sure it's not double booked
- L72 _delegate_ `DECLARE_DELEGATE_RetVal(FText&, FOnRigVMGetFilteredText)` — to highlight item
- L74 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRigVMCreateVariableMapping, const FString&, TArray< TSharedPtr<FRigVMVariableMappingInfo> >&) DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigVMVarOptionAvailable, const FName& );` — caller to create list
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigVMVarOptionAvailable, const FName& );`
- L78 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRigVMPinCheckStateChanged, ECheckBoxState, FName );` — pin exposure option
- L78 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRigVMPinCheckStateChanged, ECheckBoxState, FName );` — pin exposure option
- L79 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FOnRigVMPinGetCheckState, FName );`
- L79 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FOnRigVMPinGetCheckState, FName );`
- L80 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigVMPinIsCheckEnabled, FName );`
- L80 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigVMPinIsCheckEnabled, FName );`
- L137 _typedef_ `typedef STreeView< TSharedPtr<FRigVMVariableMappingInfo> > SRigVMVariableMappingTreeView;`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMVariantTagWidget.h` (Public)


#### class `SRigVMVariantCapsule`  
`class SRigVMVariantCapsule : public SButton`  
_L17-58_
- inherits: `SButton`
- L21 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantCapsule) : _Padding(0.f) , _EnableContextMenu(false) , _MinDesiredLabelWidth(0.f) , _CapsuleTagBorder(FRigVMEditorStyle::Get().GetBrush("RigVM.TagCapsule"))`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FName, Name) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_ATTRIBUTE(FSlateColor, Color) SLATE_EVENT(FOnClicked, OnClicked) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_EVENT(FRigVMVariant_OnRemoveTag, OnRemoveTag) SLATE_ATTRIBUTE(bool, EnableContextMenu) SLATE_ARGUMENT(float, MinDesiredLabelWidth) SLATE_ATTRIBUTE(const FSlateBrush*, CapsuleTagBorder) SLATE_END_ARGS() SRigVMVariantCapsule();`
- L43 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `FSlateColor GetColor() const;`
- L46 _public prototype_ `FSlateColor GetLabelColor() const;`
- L48 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L52 _private prototype_ `void HandleRemoveTag();`
- L54 _private member_ `TAttribute<FName> NameAttribute;`
- L55 _private member_ `TAttribute<FSlateColor> ColorAttribute;`
- L56 _private member_ `FRigVMVariant_OnRemoveTag OnRemoveTag;`
- L57 _private member_ `TAttribute<bool> EnableContextMenu;`

#### class `SRigVMVariantTagWidget`  
`class SRigVMVariantTagWidget : public SBox`  
_L60-109_
- inherits: `SBox`
- L64 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantTagWidget) : _Orientation(EOrientation::Orient_Vertical) , _CanAddTags(false) , _EnableContextMenu(false) , _MinDesiredLabelWidth(0.f) , _EnableTick(true) , _CapsuleTagBorder(FRigVMEditorStyle::Get().GetBrush("RigVM.TagCapsule"))`
- L73 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ATTRIBUTE(bool, CanAddTags) SLATE_ATTRIBUTE(bool, EnableContextMenu) SLATE_EVENT(FRigVMVariant_OnGetTags, OnGetTags) SLATE_EVENT(FRigVMVariant_OnAddTag, OnAddTag) SLATE_EVENT(FRigVMVariant_OnRemoveTag, OnRemoveTag) SLATE_ARGUMENT(float, MinDesiredLabelWidth) SLATE_ARGUMENT(bool, EnableTick) SLATE_ATTRIBUTE(const FSlateBrush*, CapsuleTagBorder) SLATE_END_ARGS() SRigVMVariantTagWidget();`
- L87 _public prototype_ `void Construct(const FArguments& InArgs);`
- L89 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L93 _private prototype_ `void UpdateCapsules();`
- L94 _private prototype_ `FReply OnAddTagClicked(const FName& InTagName) const;`
- L95 _private prototype_ `TSharedRef<SWidget> OnBuildAddTagMenuContent() const;`
- L97 _private member_ `TSharedPtr<SVerticalBox> VerticalCapsuleBox;`
- L98 _private member_ `TSharedPtr<SHorizontalBox> HorizontalCapsuleBox;`
- L99 _private member_ `mutable TWeakPtr<SWidget> WeakAddTagMenuWidget;`
- L101 _private member_ `FRigVMVariant_OnGetTags OnGetTags;`
- L102 _private member_ `FRigVMVariant_OnAddTag OnAddTag;`
- L103 _private member_ `FRigVMVariant_OnRemoveTag OnRemoveTag;`
- L104 _private member_ `TAttribute<bool> CanAddTags;`
- L105 _private member_ `TAttribute<bool> EnableContextMenu;`
- L106 _private member_ `TAttribute<const FSlateBrush*> CapsuleTagBorder;`
- L107 _private member_ `uint32 LastTagHash;`
- L108 _private member_ `float MinDesiredLabelWidth;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMEDITOR_API`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMTag>, FRigVMVariant_OnGetTags);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal(TArray<FRigVMTag>, FRigVMVariant_OnGetTags);`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMVariant_OnAddTag, const FName&);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMVariant_OnAddTag, const FName&);`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMVariant_OnRemoveTag, const FName&);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMVariant_OnRemoveTag, const FName&);`

### `Plugins/Runtime/RigVM/Source/RigVMEditor/Public/Widgets/SRigVMVariantWidget.h` (Public)


#### struct `FRigVMVariantWidgetContext`  
`struct FRigVMVariantWidgetContext`  
_L21-30_
- L23 _public function_ `FRigVMVariantWidgetContext() : ParentPath()`
- L29 _public member_ `FString ParentPath;` — the path the current context is in

#### class `SRigVMVariantToolTipWithTags`  
`class SRigVMVariantToolTipWithTags : public SToolTip`  
_L32-50_
- inherits: `SToolTip`
- L35 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantToolTipWithTags)`
- L36 _public prototype_ `SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_EVENT(FRigVMVariant_OnGetTags, OnGetTags) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `virtual bool IsEmpty() const override;` — IToolTip interface
- L44 _public prototype_ `virtual void OnOpening() override;`
- L45 _public prototype_ `virtual void OnClosed() override;`
- L48 _private member_ `FRigVMVariant_OnGetTags GetTagsDelegate;`
- L49 _private member_ `SToolTip::FArguments SuperClassArgs;`

#### class `SRigVMVariantGuidWidget`  
`class SRigVMVariantGuidWidget : public SBox`  
_L52-67_
- inherits: `SBox`
- L55 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantGuidWidget)`
- L56 _public prototype_ `SLATE_ATTRIBUTE(FGuid, Guid) SLATE_EVENT(FRigVMVariantWidget_OnContextMenu, OnContextMenu) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L62 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _private member_ `FRigVMVariantWidget_OnContextMenu OnContextMenu;`

#### class `SRigVMVariantWidget`  
`class SRigVMVariantWidget : public SBox`  
_L69-153_
- inherits: `SBox`
- L73 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantWidget) : _Context(FRigVMVariantWidgetContext()) , _MaxVariantRefListHeight(200.f) , _CanAddTags(false) , _EnableTagContextMenu(false)`
- L80 _public prototype_ `SLATE_ATTRIBUTE(FRigVMVariant, Variant) SLATE_ATTRIBUTE(FRigVMVariantRef, SubjectVariantRef) SLATE_ATTRIBUTE(TArray<FRigVMVariantRef>, VariantRefs) SLATE_ATTRIBUTE(FRigVMVariantWidgetContext, Context) SLATE_EVENT(FRigVMVariantWidget_OnVariantChanged, OnVariantChanged) SLATE_EVENT(FRigVMVariantWidget_OnCreateVariantRefRow, OnCreateVariantRefRow);`
- L86 _public prototype_ `SLATE_EVENT(FRigVMVariantWidget_OnBrowseVariantRef, OnBrowseVariantRef) SLATE_EVENT(FRigVMVariantWidget_OnVariantRefContextMenu, OnVariantRefContextMenu) SLATE_ATTRIBUTE(float, MaxVariantRefListHeight) SLATE_EVENT(FRigVMVariant_OnGetTags, OnGetTags) SLATE_EVENT(FRigVMVariant_OnAddTag, OnAddTag) SLATE_EVENT(FRigVMVariant_OnRemoveTag, OnRemoveTag) SLATE_ATTRIBUTE(bool, CanAddTags) SLATE_ATTRIBUTE(bool, EnableTagContextMenu) SLATE_END_ARGS() SRigVMVariantWidget();`
- L99 _public prototype_ `void Construct(const FArguments& InArgs);`
- L101 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L127 _private prototype_ `const FRigVMVariantWidgetContext& GetVariantContext() const;`
- L128 _private prototype_ `EVisibility GetVariantRefListVisibility() const;`
- L129 _private prototype_ `TSharedRef<ITableRow> GenerateVariantTreeRow(TSharedPtr<FVariantTreeRowInfo> InRowInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L130 _private prototype_ `void GetChildrenForVariantInfo(TSharedPtr<FVariantTreeRowInfo> InInfo, TArray<TSharedPtr<FVariantTreeRowInfo>>& OutChildren);`
- L131 _private prototype_ `TSharedPtr<SWidget> CreateDefaultVariantRefRow(const FRigVMVariantRef& InVariantRef) const;`
- L132 _private prototype_ `void RebuildVariantRefList();`
- L133 _private prototype_ `const FSlateBrush* GetThumbnailBorder(TSharedRef<SBorder> InThumbnailBorder) const;`
- L134 _private prototype_ `TSharedPtr<SWidget> OnVariantRefTreeContextMenu();`
- L135 _private prototype_ `TSharedPtr<SWidget> CreateDefaultVariantRefContextMenu(const FRigVMVariantRef& InVariantRef);`
- L137 _private member_ `TAttribute<FRigVMVariant> VariantAttribute;`
- L138 _private member_ `TAttribute<FRigVMVariantRef> SubjectVariantRefAttribute;`
- L139 _private member_ `FRigVMVariantWidget_OnVariantChanged OnVariantChanged;`
- L141 _private member_ `TSharedPtr<SRigVMVariantTagWidget> TagWidget;`
- L143 _private member_ `TAttribute<TArray<FRigVMVariantRef>> VariantRefsAttribute;`
- L144 _private member_ `FRigVMVariantWidget_OnCreateVariantRefRow OnCreateVariantRefRow;`
- L145 _private member_ `FRigVMVariantWidget_OnBrowseVariantRef OnBrowseVariantRef;`
- L146 _private member_ `FRigVMVariantWidget_OnVariantRefContextMenu OnVariantRefContextMenu;`
- L147 _private member_ `TArray<FRigVMVariantRef> VariantRefs;`
- L148 _private member_ `TArray<TSharedPtr<FVariantTreeRowInfo>> VariantTreeRowInfos;`
- L149 _private member_ `uint32 VariantRefHash;`
- L150 _private member_ `TSharedPtr<SVerticalBox> VariantRefListBox;`
- L151 _private member_ `TSharedPtr<STreeView<TSharedPtr<FVariantTreeRowInfo>>> VariantRefTreeView;`
- L152 _private member_ `TAttribute<FRigVMVariantWidgetContext> ContextAttribute;`

#### struct `SRigVMVariantWidget::FVariantTreeRowInfo`  
`struct FVariantTreeRowInfo`  
_L105-110_
- L107 _public member_ `FRigVMVariantRef VariantRef;`
- L108 _public member_ `TArray<TSharedPtr<FVariantTreeRowInfo>> NestedInfos;`
- L109 _public member_ `TWeakPtr<ITableRow> RowWidget;`

#### class `SRigVMVariantWidget::SRigVMVariantRefTreeRow`  
`class SRigVMVariantRefTreeRow : public STableRow<TSharedPtr<FVariantTreeRowInfo>>`  
_L112-125_
- inherits: `STableRow<TSharedPtr<FVariantTreeRowInfo>>`
- L117 _public function_ `SLATE_BEGIN_ARGS(SRigVMVariantRefTreeRow)`
- L119 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, Content) SLATE_EVENT(FRigVMVariantWidget_OnVariantRefContextMenu, OnVariantRefContextMenu) SLATE_END_ARGS() virtual ~SRigVMVariantRefTreeRow() override;`
- L124 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMVariantWidget_OnVariantChanged, const FRigVMVariant&);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMVariantWidget_OnVariantChanged, const FRigVMVariant&);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FRigVMVariantWidget_OnCreateVariantRefRow, const FRigVMVariantRef&);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FRigVMVariantWidget_OnCreateVariantRefRow, const FRigVMVariantRef&);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMVariantWidget_OnBrowseVariantRef, const FRigVMVariantRef&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMVariantWidget_OnBrowseVariantRef, const FRigVMVariantRef&);`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FRigVMVariantWidget_OnVariantRefContextMenu, const FRigVMVariantRef&);`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SWidget>, FRigVMVariantWidget_OnVariantRefContextMenu, const FRigVMVariantRef&);`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FRigVMVariantWidget_OnContextMenu);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<SWidget>, FRigVMVariantWidget_OnContextMenu);`
