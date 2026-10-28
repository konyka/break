# Plugins / HierarchyTableAnimationEditor

- module root: `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor`
- headers: 8; symbols: 71
- symbol kinds: class=9, function=8, macro=2, member=10, prototype=41, struct=1

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/BlendProfileStandaloneAssetDefinition.h` (Private)


#### class `UAssetDefinition_BlendProfileStandalone`  
`class UAssetDefinition_BlendProfileStandalone : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/BlendProfileStandaloneEditorToolkit.h` (Private)


#### class `FBlendProfileStandaloneEditorToolkit`  
`class FBlendProfileStandaloneEditorToolkit : public FAssetEditorToolkit`  
_L12-37_
- inherits: `FAssetEditorToolkit`
- L15 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L18 _public prototype_ `void OnClose() override;`
- L20 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L21 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L23 _public function_ `FName GetToolkitFName() const override`
- L24 _public function_ `FText GetBaseToolkitName() const override`
- L25 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L26 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L30 _private prototype_ `void OnSkeletonHierarchyChanged();`
- L32 _private prototype_ `void ExtendToolbar();`
- L34 _private member_ `TObjectPtr<UBlendProfileStandalone> BlendProfile;`
- L36 _private member_ `TSharedPtr<IHierarchyTable> HierarchyTableWidgetInterface;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/BlendProfileStandaloneFactory.h` (Private)


#### class `UBlendProfileStandaloneFactory`  
`class UBlendProfileStandaloneFactory : public UFactory`  
_L16-40_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L21 _public prototype_ `UBlendProfileStandaloneFactory();`
- L24 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L25 _public prototype_ `virtual bool ConfigureProperties() override;`
- L28 _private prototype_ `bool ConfigureBlendProfileType();`
- L30 _private prototype_ `bool ConfigureBlendProfileHierarchy();`
- L32 _private member_ `EBlendProfileStandaloneType BlendProfileType;`
- L34 _private member_ `TSharedPtr<SWindow> PickerWindow;`
- L36 _private member_ `FInstancedStruct TableMetadata;`
- L39 _private member_ `TObjectPtr<UHierarchyTable_TableTypeHandler> TableHandler;` — `UPROPERTY()`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/BlendProfileStandaloneProvider.h` (Private)


#### class `UBlendProfileStandaloneProvider`  
`class UBlendProfileStandaloneProvider : public UObject, public IBlendProfileProviderInterface`  
_L19-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IBlendProfileProviderInterface`
- desc: Class responsible for actually creating new blend profiles from custom data
- L25 _public prototype_ `void Initialize(TObjectPtr<UBlendProfileStandalone> InBlendProfile);` — IBlendProfileProviderInterface
- L26 _public prototype_ `void ConstructBlendProfile(const TObjectPtr<UBlendProfile> OutBlendProfile) const override;`
- L29 _public member_ `TObjectPtr<UBlendProfileStandalone> BlendProfile;` — `UPROPERTY()`

#### class `FBlendProfileStandalonePickerExtender`  
`class FBlendProfileStandalonePickerExtender : public IBlendProfilePickerExtender`  
_L35-60_
- inherits: `IBlendProfilePickerExtender`
- desc: Class responsible for adding a new blend profile provider in the editor for FBlendProfileInterfaceWrapper
- L38 _public prototype_ `static FName StaticGetId();`
- L41 _public prototype_ `FName GetId() const override;` — IBlendProfilePickerExtender
- L42 _public prototype_ `FText GetDisplayName() const override;`
- L43 _public prototype_ `TSharedRef<SWidget> ConstructPickerWidget(const FPickerWidgetArgs& InWidgetArgs) const override;`
- L44 _public prototype_ `bool OwnsBlendProfileProvider(const TObjectPtr<const UObject> InObject) const override;`

#### class `FBlendProfileStandalonePickerExtender::SPicker`  
`class SPicker : public SCompoundWidget`  
_L47-59_
- inherits: `SCompoundWidget`
- L50 _public function_ `SLATE_BEGIN_ARGS(SPicker)`
- L53 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, IBlendProfilePickerExtender::FPickerWidgetArgs InPickerArgs);`
- L58 _private member_ `FAssetData SelectedAsset;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HIERARCHYTABLEANIMATIONEDITOR_API`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/MaskProfile/MaskProfileColumn.h` (Private)


#### struct `FHierarchyTableColumn_Mask`  
`struct FHierarchyTableColumn_Mask : public IHierarchyTableColumn`  
_L9-18_
- inherits: `IHierarchyTableColumn`
- L12 _public function_ `virtual FName GetColumnId() const override`
- L13 _public function_ `virtual FText GetColumnLabel() const override`
- L14 _public function_ `virtual float GetColumnSize() const override`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateEntryWidget(TObjectPtr<UHierarchyTable> HierarchyTable, int32 EntryIndex);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateHeaderWidget();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "HierarchyTableColumn_Mask"`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/SkeletonHierarchyTableTypeDetailsCustomization.h` (Private)


#### class `FHierarchyTableSkeletonTableTypeDetailsCustomization`  
`class FHierarchyTableSkeletonTableTypeDetailsCustomization : public IPropertyTypeCustomization`  
_L9-17_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Private/SkeletonHierarchyTableTypeHandler.h` (Private)


#### class `UHierarchyTable_TableTypeHandler_Skeleton`  
`class UHierarchyTable_TableTypeHandler_Skeleton final : public UHierarchyTable_TableTypeHandler`  
_L10-35_
- reflection: `UCLASS()`
- inherits: `UHierarchyTable_TableTypeHandler`
- L15 _public prototype_ `virtual void ConstructHierarchy();`
- L17 _public prototype_ `virtual bool FactoryConfigureProperties(FInstancedStruct& TableType) const override;`
- L19 _public prototype_ `virtual void ExtendToolbar(UToolMenu* ToolMenu, IHierarchyTable& HierarchyTableView) const override;`
- L21 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& MenuBuilder, IHierarchyTable& HierarchyTableView) const override;`
- L23 _public prototype_ `virtual FSlateIcon GetEntryIcon(const int32 EntryIndex) const override;`
- L25 _public prototype_ `virtual FSlateColor GetEntryIconColor(const int32 EntryIndex) const override;`
- L27 _public prototype_ `virtual bool CanRenameEntry(const int32 EntryIndex) const override;`
- L29 _public prototype_ `virtual bool CanRemoveEntry(const int32 EntryIndex) const override;`
- L32 _private prototype_ `void AddCurve(const int32 ParentIndex, const FName Identifier) const;`
- L34 _private prototype_ `void AddAttribute(const int32 ParentIndex, const FName Identifier) const;`

### `Plugins/Experimental/Animation/HierarchyTableAnimation/Source/Editor/Public/HierarchyTableAnimationEditorModule.h` (Public)


#### class `FHierarchyTableAnimationEditorModule`  
`class FHierarchyTableAnimationEditorModule : public IModuleInterface`  
_L8-18_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `TArray<TWeakObjectPtr<UScriptStruct>> BuiltinTableTypes;`
- L17 _private member_ `TArray<TWeakObjectPtr<UScriptStruct>> BuiltinElementTypes;`
