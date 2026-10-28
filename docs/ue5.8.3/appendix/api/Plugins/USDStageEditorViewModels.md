# Plugins / USDStageEditorViewModels

- module root: `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels`
- headers: 8; symbols: 160
- symbol kinds: class=13, delegate=1, enum=1, enumerator=4, function=6, macro=7, member=54, namespace=1, prototype=68, typedef=2, variable=3
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopWidgets, EditorFramework, Engine, InputCore, LevelEditor, Slate, SlateCore, USDClasses, USDStage, USDStageImporter, USDUtilities, UnrealEd, UnrealUSDWrapper, WorkspaceMenuStructure

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDIntegrationsViewModel.h` (Public)


#### class `FUsdIntegrationsViewModel`  
`class FUsdIntegrationsViewModel`  
_L13-23_
- L16 _public prototype_ `void UpdateAttributes(const UE::FUsdStageWeak& UsdStage, const TCHAR* PrimPath);`
- L19 _public member_ `TArray<TSharedPtr<UE::FUsdAttribute>> Attributes;`
- L21 _public member_ `FString PrimPath;`
- L22 _public member_ `UE::FUsdStageWeak UsdStage;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDLayersViewModel.h` (Public)


#### class `FUsdLayerModel`  
`class FUsdLayerModel : public TSharedFromThis<FUsdLayerModel>`  
_L13-21_
- inherits: `TSharedFromThis<FUsdLayerModel>`
- L16 _public member_ `FString DisplayName;`
- L17 _public member_ `bool bIsEditTarget = false;`
- L18 _public member_ `bool bIsMuted = false;`
- L19 _public member_ `bool bIsDirty = false;`
- L20 _public member_ `bool bIsInIsolatedStage = true;`

#### class `FUsdLayerViewModel`  
`class FUsdLayerViewModel : public IUsdTreeViewItem`  
_L23-71_
- inherits: `IUsdTreeViewItem`
- L26 _public prototype_ `explicit FUsdLayerViewModel( FUsdLayerViewModel* InParentItem, const UE::FUsdStageWeak& InUsdStage, const UE::FUsdStageWeak& InIsolatedStage, const FString& InLayerIdentifier );`
- L33 _public prototype_ `bool IsValid() const;`
- L35 _public prototype_ `TArray<TSharedRef<FUsdLayerViewModel>> GetChildren();`
- L37 _public prototype_ `void FillChildren();`
- L39 _public prototype_ `void RefreshData();`
- L41 _public prototype_ `UE::FSdfLayer GetLayer() const;`
- L42 _public prototype_ `FText GetDisplayName() const;`
- L44 _public prototype_ `bool IsLayerMuted() const;`
- L45 _public prototype_ `bool CanMuteLayer() const;`
- L46 _public prototype_ `void ToggleMuteLayer();`
- L48 _public prototype_ `bool IsEditTarget() const;`
- L49 _public prototype_ `bool CanEditLayer() const;`
- L50 _public prototype_ `bool EditLayer();`
- L52 _public prototype_ `bool IsInIsolatedStage() const;`
- L54 _public prototype_ `void AddSubLayer(const TCHAR* SubLayerIdentifier);`
- L55 _public prototype_ `void NewSubLayer(const TCHAR* SubLayerIdentifier);`
- L56 _public prototype_ `bool RemoveSubLayer(int32 SubLayerIndex);`
- L58 _public prototype_ `bool IsLayerDirty() const;`
- L60 _public prototype_ `bool CanReload() const;`
- L61 _public prototype_ `void Reload();`
- L64 _public member_ `TSharedRef<FUsdLayerModel> LayerModel;`
- L65 _public member_ `FUsdLayerViewModel* ParentItem;`
- L66 _public member_ `TArray<TSharedRef<FUsdLayerViewModel>> Children;`
- L68 _public member_ `UE::FUsdStageWeak UsdStage;`
- L69 _public member_ `UE::FUsdStageWeak IsolatedStage;`
- L70 _public member_ `FString LayerIdentifier;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDObjectFieldViewModel.h` (Public)


#### enum `EObjectFieldType`  
`enum class EObjectFieldType : int32`  
_L16-22_
- L18 _public enumerator_ `Metadata = 0`
- L19 _public enumerator_ `Attribute = 1`
- L20 _public enumerator_ `Relationship = 2`
- L21 _public enumerator_ `MAX = 3`

#### class `FUsdObjectFieldViewModel`  
`class FUsdObjectFieldViewModel : public TSharedFromThis<FUsdObjectFieldViewModel>`  
_L31-49_
- inherits: `TSharedFromThis<FUsdObjectFieldViewModel>`
- L34 _public prototype_ `explicit FUsdObjectFieldViewModel(FUsdObjectFieldsViewModel* InOwner);`
- L37 _public prototype_ `TArray<TSharedPtr<FString>> GetDropdownOptions() const;` — This member function is necessary because the no-RTTI slate module can't query USD for the available token options
- L38 _public prototype_ `void SetAttributeValue(const UsdUtils::FConvertedVtValue& InValue);`
- L41 _public member_ `EObjectFieldType Type;`
- L42 _public member_ `FString Label;`
- L43 _public member_ `UsdUtils::FConvertedVtValue Value;`
- L44 _public member_ `FString ValueRole;`
- L45 _public member_ `bool bReadOnly = false;`
- L48 _private member_ `FUsdObjectFieldsViewModel* Owner;`

#### class `FUsdObjectFieldsViewModel`  
`class FUsdObjectFieldsViewModel`  
_L51-81_
- L55 _public prototype_ `template<typename T> void CreateField( EObjectFieldType Type, const FString& FieldName, const T& Value, UsdUtils::EUsdBasicDataTypes UsdType, const FString& ValueRole = FString(), bool bReadOnly = false );`
- L63 _public prototype_ `void CreateField(EObjectFieldType Type, const FString& FieldName, const UsdUtils::FConvertedVtValue& Value, bool bReadOnly = false);`
- L65 _public prototype_ `void SetFieldValue(const FString& FieldName, const UsdUtils::FConvertedVtValue& Value);`
- L67 _public prototype_ `void Refresh(const UE::FUsdStageWeak& UsdStage, const TCHAR* ObjectPath, float TimeCode);`
- L68 _public prototype_ `void Sort();`
- L70 _public prototype_ `UE::FUsdStageWeak GetUsdStage() const;`
- L71 _public prototype_ `FString GetObjectPath() const;`
- L74 _public member_ `EColumnSortMode::Type CurrentSortMode = EColumnSortMode::Ascending;`
- L75 _public member_ `FName CurrentSortColumn = ObjectFieldColumnIds::TypeColumn;`
- L76 _public member_ `TArray<TSharedPtr<FUsdObjectFieldViewModel>> Fields;`
- L79 _private member_ `UE::FUsdStageWeak UsdStage;`
- L80 _private member_ `FString ObjectPath;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`
- L24 _namespace_ `namespace ObjectFieldColumnIds`
- L26 _variable_ `inline const FName TypeColumn = TEXT("Fie` (scope `ObjectFieldColumnIds`)
- L27 _variable_ `inline const FName NameColumn = TEXT("Fie` (scope `ObjectFieldColumnIds`)
- L28 _variable_ `inline const FName ValueColumn = TEXT("Fie` (scope `ObjectFieldColumnIds`)

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDPrimViewModel.h` (Public)


#### class `FUsdPrimModel`  
`class FUsdPrimModel : public TSharedFromThis<FUsdPrimModel>`  
_L19-53_
- inherits: `TSharedFromThis<FUsdPrimModel>`
- L22 _public function_ `FText GetName() const`
- L26 _public function_ `FText GetType() const`
- L30 _public function_ `bool HasPayload() const`
- L34 _public function_ `bool IsLoaded() const`
- L38 _public function_ `bool HasCompositionArcs() const`
- L42 _public function_ `bool IsVisible() const`
- L47 _public member_ `FText Name;`
- L48 _public member_ `FText Type;`
- L49 _public member_ `bool bHasPayload = false;`
- L50 _public member_ `bool bIsLoaded = false;`
- L51 _public member_ `bool bHasCompositionArcs = false;`
- L52 _public member_ `bool bIsVisible = true;`

#### class `FUsdPrimViewModel`  
`class FUsdPrimViewModel : public IUsdTreeViewItem`  
_L55-107_
- inherits: `IUsdTreeViewItem`
- L58 _public prototype_ `FUsdPrimViewModel(FUsdPrimViewModel* InParentItem, const UE::FUsdStageWeak& InUsdStage, const UE::FUsdPrim& InPrim = {});`
- L60 _public prototype_ `TArray<FUsdPrimViewModelRef>& UpdateChildren();`
- L62 _public prototype_ `void SetIsExpanded(bool bNewIsExpanded);`
- L63 _public prototype_ `bool ShouldGenerateChildren() const;`
- L64 _public prototype_ `void FillChildren();`
- L66 _public prototype_ `void RefreshData(bool bRefreshChildren);`
- L68 _public prototype_ `bool HasVisibilityAttribute() const;`
- L69 _public prototype_ `void ToggleVisibility();`
- L70 _public prototype_ `void TogglePayload();`
- L72 _public prototype_ `void ApplySchema(FName SchemaName);`
- L73 _public prototype_ `bool CanApplySchema(FName SchemaName) const;`
- L74 _public prototype_ `void RemoveSchema(FName SchemaName);`
- L75 _public prototype_ `bool CanRemoveSchema(FName SchemaName) const;`
- L78 _public prototype_ `bool HasSpecsOnLocalLayer() const;` — Returns true if this prim has at least one spec on the stage's local layer stack
- L79 _public prototype_ `bool HasReferencesOnLocalLayer() const;`
- L80 _public prototype_ `bool HasPayloadsOnLocalLayer() const;`
- L82 _public prototype_ `void DefinePrim(const TCHAR* PrimName);`
- L85 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequest);` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L88 _public member_ `FOnRenameRequest RenameRequestEvent;` — Broadcasts whenever a rename is requested
- L91 _public prototype_ `void ClearReferences();`
- L92 _public prototype_ `void ClearPayloads();`
- L95 _public member_ `UE::FUsdStageWeak UsdStage;`
- L96 _public member_ `UE::FUsdPrim UsdPrim;`
- L98 _public member_ `FUsdPrimViewModel* ParentItem;`
- L99 _public member_ `TArray<FUsdPrimViewModelRef> Children;`
- L101 _public member_ `TSharedRef<FUsdPrimModel> RowData;` — Data model
- L103 _public member_ `bool bIsRenamingExistingPrim = false;`
- L106 _private member_ `bool bIsExpanded = false;` — Set by our parent tree, controls whether we generate grandchildren or not

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`
- L16 _typedef_ `using FUsdPrimViewModelRef = TSharedRef<class FUsdPrimViewModel>;`
- L17 _typedef_ `using FUsdPrimViewModelPtr = TSharedPtr<class FUsdPrimViewModel>;`
- L85 _delegate_ `DECLARE_DELEGATE(FOnRenameRequest);` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDReferencesViewModel.h` (Public)


#### class `FUsdReference`  
`class FUsdReference : public TSharedFromThis<FUsdReference>`  
_L13-20_
- inherits: `TSharedFromThis<FUsdReference>`
- L16 _public member_ `FString AssetPath;`
- L17 _public member_ `FString PrimPath;`
- L18 _public member_ `bool bIntroducedInLocalLayerStack = true;`
- L19 _public member_ `bool bIsPayload = false;`

#### class `FUsdReferencesViewModel`  
`class FUsdReferencesViewModel`  
_L22-33_
- L25 _public prototype_ `void UpdateReferences(const UE::FUsdStageWeak& UsdStage, const TCHAR* PrimPath);`
- L26 _public prototype_ `void RemoveReference(const TSharedPtr<FUsdReference>& Reference);`
- L27 _public prototype_ `void ReloadReference(const TSharedPtr<FUsdReference>& Reference);`
- L30 _public member_ `UE::FUsdStageWeak UsdStage;`
- L31 _public member_ `UE::FSdfPath PrimPath;`
- L32 _public member_ `TArray<TSharedPtr<FUsdReference>> References;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDStageEditorViewModelsModule.h` (Public)


#### class `IUsdStageEditorViewModelsModule`  
`class IUsdStageEditorViewModelsModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDStageViewModel.h` (Public)


#### class `FUsdStageViewModel`  
`class FUsdStageViewModel`  
_L14-35_
- L17 _public prototype_ `void NewStage();`
- L18 _public prototype_ `void OpenStage(const TCHAR* FilePath);`
- L19 _public prototype_ `void SetLoadAllRule();`
- L20 _public prototype_ `void SetLoadNoneRule();`
- L24 _public prototype_ `bool HasDefaultLoadRule();` — Returns false if we have a payload in the current stage that has been manually loaded or unloaded. Returns true otherwise. The intent is to get the LoadAll/LoadNone buttons to *both* show as unchecked in case the user manually toggled any, to indicate that picking either LoadAll or LoadNone would trigger some change.
- L25 _public prototype_ `void ReloadStage();`
- L26 _public prototype_ `void ResetStage();`
- L27 _public prototype_ `void CloseStage();`
- L28 _public prototype_ `void SaveStage();`
- L30 _public prototype_ `void SaveStageAs(const TCHAR* FilePath);` — Temporary until SaveAs feature is properly implemented, may be removed in a future release
- L31 _public prototype_ `void ImportStage(const TCHAR* TargetContentFolder = nullptr, UUsdStageImportOptions* Options = nullptr);`
- L34 _public member_ `TWeakObjectPtr<AUsdStageActor> UsdStageActor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`

### `Plugins/Importers/USDImporter/Source/USDStageEditorViewModels/Public/USDVariantSetsViewModel.h` (Public)


#### class `FUsdVariantSetViewModel`  
`class FUsdVariantSetViewModel : public TSharedFromThis<FUsdVariantSetViewModel>`  
_L13-27_
- inherits: `TSharedFromThis<FUsdVariantSetViewModel>`
- L16 _public prototype_ `explicit FUsdVariantSetViewModel(FUsdVariantSetsViewModel* InOwner);`
- L18 _public prototype_ `void SetVariantSelection(const TSharedPtr<FString>& InVariantSelection);`
- L21 _public member_ `FString SetName;`
- L22 _public member_ `TSharedPtr<FString> VariantSelection;`
- L23 _public member_ `TArray<TSharedPtr<FString>> Variants;`
- L26 _private member_ `FUsdVariantSetsViewModel* Owner;`

#### class `FUsdVariantSetsViewModel`  
`class FUsdVariantSetsViewModel`  
_L29-39_
- L32 _public prototype_ `void UpdateVariantSets(const UE::FUsdStageWeak& InUsdStage, const TCHAR* PrimPath);`
- L35 _public member_ `UE::FUsdStageWeak UsdStage;`
- L36 _public member_ `FString PrimPath;`
- L38 _public member_ `TArray<TSharedPtr<FUsdVariantSetViewModel>> VariantSets;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API USDSTAGEEDITORVIEWMODELS_API`
