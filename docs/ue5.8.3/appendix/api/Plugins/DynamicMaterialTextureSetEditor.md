# Plugins / DynamicMaterialTextureSetEditor

- module root: `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor`
- headers: 15; symbols: 133
- symbol kinds: class=14, delegate=2, function=5, member=29, prototype=81, struct=2
- PrivateDependencyModuleNames: AssetDefinition, Core, DeveloperSettings, DynamicMaterialTextureSet, EditorWidgets, Engine, InputCore, PropertyEditor, Slate, SlateCore
- PublicDependencyModuleNames: CoreUObject, UnrealEd

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/AssetDefinition_DMTextureSet.h` (Private)


#### class `UAssetDefinition_DMTextureSet`  
`class UAssetDefinition_DMTextureSet : public UAssetDefinitionDefault`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetAssetDisplayName(const FAssetData& InAssetData) const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DMTextureSetContentBrowserIntegrationPrivate.h` (Private)


#### class `FDMTextureSetContentBrowserIntegrationPrivate`  
`class FDMTextureSetContentBrowserIntegrationPrivate : public FDMTextureSetContentBrowserIntegration`  
_L16-33_
- inherits: `FDMTextureSetContentBrowserIntegration`
- L19 _public prototype_ `static void Integrate();`
- L21 _public prototype_ `static void Disintegrate();`
- L24 _protected prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`
- L26 _protected prototype_ `static void CreateMenu(FMenuBuilder& InMenuBuilder, TArray<FAssetData> InSelectedAssets);`
- L28 _protected prototype_ `static void CreateTextureSet(TArray<FAssetData> InSelectedAssets);`
- L30 _protected prototype_ `static void OnCreateTextureSetComplete(UDMTextureSet* InTextureSet, bool bInAccepted, FString InPath);`
- L32 _protected member_ `static FDelegateHandle ContentBrowserHandle;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DMTextureSetFilter.h` (Private)


#### struct `FDMTextureSetFilter`  
`struct FDMTextureSetFilter`  
_L12-38_
- reflection: `USTRUCT()`
- L16 _public prototype_ `FDMTextureSetFilter();`
- L24 _public member_ `TArray<FString> FilterStrings;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")` — Portion of the name of the Texture asset to search for. For instance _Normal or _ORB. Will match any of the given strings. Filters starting with _ will only match if they are at the end of an asset name.
- L30 _public member_ `TMap<EDMTextureSetMaterialProperty, EDMTextureChannelMask> MaterialProperties;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")` — Where the matched Texture assets should be placed into the Texture Set. Links to the channel for the given asset.
- L37 _public prototype_ `bool MatchesFilter(const FString& InAssetName) const;` — Checks the given asset name against the filter strings. @param InAssetName The name of the asset @return True if any filter string was matched.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DMTextureSetSettings.h` (Private)


#### class `UDMTextureSetSettings`  
`class UDMTextureSetSettings : public UDeveloperSettings`  
_L15-30_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "Material Designer Texture Set"))`
- inherits: `UDeveloperSettings`
- desc: DM Texture Set Settings
- L20 _public prototype_ `UDMTextureSetSettings();`
- L21 _public prototype_ `virtual ~UDMTextureSetSettings() override = default;`
- L23 _public prototype_ `static UDMTextureSetSettings* Get();`
- L26 _public member_ `bool bOnlyMatchEndOfAssetName = false;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")`
- L29 _public member_ `TArray<FDMTextureSetFilter> Filters;` — `UPROPERTY(EditAnywhere, Category = "Material Designer", meta = (TitleProperty=FilterStrings))`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DMTextureSetStyle.h` (Private)


#### class `FDMTextureSetStyle`  
`class FDMTextureSetStyle final : public FSlateStyleSet`  
_L8-16_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static const ISlateStyle& Get();`
- L13 _public prototype_ `FDMTextureSetStyle();`
- L15 _public prototype_ `virtual ~FDMTextureSetStyle() override = default;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DynamicMaterialTextureSetEditorModule.h` (Private)


#### class `FDynamicMaterialTextureSetEditorModule`  
`class FDynamicMaterialTextureSetEditorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/DMTextureSetBuilderDragDropOperation.h` (Private)


#### class `FDMTextureSetBuilderDragDropOperation`  
`class FDMTextureSetBuilderDragDropOperation : public FAssetDragDropOp`  
_L7-27_
- inherits: `FAssetDragDropOp`
- L10 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMTextureSetBuilderDragDropOperation, FAssetDragDropOp) static TSharedRef<FDMTextureSetBuilderDragDropOperation> New(const FAssetData& InAssetData, int32 InIndex, bool bInIsMaterialProperty);`
- L14 _public prototype_ `virtual ~FDMTextureSetBuilderDragDropOperation() override = default;`
- L16 _public prototype_ `int32 GetIndex() const;`
- L18 _public prototype_ `bool IsMaterialProperty() const;`
- L21 _public prototype_ `virtual FCursorReply OnCursorQuery();`
- L25 _protected member_ `int32 Index = -1;`
- L26 _protected member_ `bool bIsMaterialProperty = false;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/DMTextureSetBuilderEntry.h` (Private)


#### struct `FDMTextureSetBuilderEntry`  
`struct FDMTextureSetBuilderEntry`  
_L17-33_
- reflection: `USTRUCT()`
- L21 _public prototype_ `FDMTextureSetBuilderEntry();`
- L23 _public prototype_ `FDMTextureSetBuilderEntry(EDMTextureSetMaterialProperty InMaterialProperty, UTexture* InTexture, EDMTextureChannelMask InMask);`
- L26 _public member_ `EDMTextureSetMaterialProperty MaterialProperty = EDMTextureSetMaterialProperty::BaseColor;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")`
- L29 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")`
- L32 _public member_ `EDMTextureChannelMask ChannelMask = EDMTextureChannelMask::RGBA;` — `UPROPERTY(EditAnywhere, Category = "Material Designer")`

#### class `FDMTextureSetBuilderEntryProvider`  
`class FDMTextureSetBuilderEntryProvider : public IStructureDataProvider`  
_L35-51_
- inherits: `IStructureDataProvider`
- L38 _public prototype_ `explicit FDMTextureSetBuilderEntryProvider(const TSharedRef<FDMTextureSetBuilderEntry>& InEntry);`
- L40 _public prototype_ `virtual ~FDMTextureSetBuilderEntryProvider() override = default;`
- L43 _public prototype_ `virtual bool IsValid() const override;`
- L44 _public prototype_ `virtual const UStruct* GetBaseStructure() const override;`
- L45 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override;`
- L46 _public prototype_ `virtual bool IsPropertyIndirection() const override;`
- L50 _protected member_ `TSharedRef<FDMTextureSetBuilderEntry> Entry;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/SDMTextureSetBuilder.h` (Private)


#### class `SDMTextureSetBuilder`  
`class SDMTextureSetBuilder : public SCompoundWidget`  
_L19-67_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SDMTextureSetBuilder)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, UDMTextureSet* InTextureSet, const TArray<FAssetData>& InAssets, FDMTextureSetBuilderOnComplete InOnComplete);`
- L27 _public function_ `bool WasAccepted() const`
- L29 _public prototype_ `void SwapTexture(int32 InFromIndex, bool bInIsFromMaterialProperty, int32 InToIndex, bool bInIsToMaterialProperty);`
- L31 _public prototype_ `void SetTexture(int32 InIndex, bool bInIsMaterialProperty, UTexture* InTexture);`
- L34 _protected member_ `TStrongObjectPtr<UDMTextureSet> TextureSet;`
- L35 _protected member_ `TArray<FAssetData> Assets;`
- L36 _protected member_ `TArray<TSharedRef<FDMTextureSetBuilderEntry>> MaterialProperties;`
- L37 _protected member_ `TArray<UTexture*> UnassignedTextures;`
- L38 _protected member_ `bool bAccepted = false;`
- L39 _protected member_ `FDMTextureSetBuilderOnComplete OnComplete;`
- L41 _protected member_ `TSharedPtr<SGridPanel> MaterialPropertyGrid;`
- L42 _protected member_ `TSharedPtr<SGridPanel> UnassignedTextureGrid;`
- L44 _protected prototype_ `TSharedRef<SWidget> GenerateMaterialPropertyCell(const TSharedRef<FDMTextureSetBuilderEntry>& InListItem, int32 InIndex);`
- L46 _protected prototype_ `TSharedRef<SWidget> GenerateUnusedTextureCell(UTexture* InTexture, int32 InIndex);`
- L48 _protected prototype_ `FReply OnAcceptClicked();`
- L50 _protected prototype_ `FReply OnCancelClicked();`
- L52 _protected prototype_ `void Close();`
- L54 _protected prototype_ `void CreateUnassignedTextureSlots();`
- L56 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets);`
- L58 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets);`
- L60 _protected prototype_ `TSharedPtr<SDMTextureSetBuilderCellBase> GetCell(int32 InIndex, bool bInIsMaterialProperty) const;`
- L62 _protected prototype_ `UTexture* GetTexture(int32 InIndex, bool bInIsMaterialProperty) const;`
- L64 _protected prototype_ `void SetTexture(int32 InIndex, bool bInIsMaterialProperty, UTexture* InTexture) const;`
- L66 _protected prototype_ `bool IsTextureAssignedToMaterialProperty(UTexture* InTexture) const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/SDMTextureSetBuilderCellBase.h` (Private)


#### class `SDMTextureSetBuilderCellBase`  
`class SDMTextureSetBuilderCellBase : public SCompoundWidget`  
_L14-51_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SDMTextureSetBuilderCellBase)`
- L20 _public prototype_ `SDMTextureSetBuilderCellBase();`
- L22 _public prototype_ `virtual ~SDMTextureSetBuilderCellBase() override = default;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMTextureSetBuilder>& InTextureSetBuilder, UTexture* InTexture, int32 InIndex, bool bInIsMaterialProperty);`
- L27 _public prototype_ `UTexture* GetTexture() const;`
- L29 _public prototype_ `virtual void SetTexture(UTexture* InTexture);`
- L32 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L37 _protected member_ `TWeakPtr<SDMTextureSetBuilder> TextureSetBuilderWeak;`
- L38 _protected member_ `TStrongObjectPtr<UTexture> Texture;`
- L39 _protected member_ `int32 Index;`
- L40 _protected member_ `bool bIsMaterialProperty;`
- L42 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets);`
- L44 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent& InDragDropEvent, TArrayView<FAssetData> InAssets);`
- L46 _protected prototype_ `EVisibility GetImageVisibility() const;`
- L48 _protected prototype_ `FText GetToolTipText() const;`
- L50 _protected prototype_ `FText GetTextureName() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/SDMTextureSetBuilderMaterialPropertyCell.h` (Private)


#### class `SDMTextureSetBuilderMaterialPropertyCell`  
`class SDMTextureSetBuilderMaterialPropertyCell : public SDMTextureSetBuilderCellBase, public FNotifyHook`  
_L16-48_
- inherits: `SDMTextureSetBuilderCellBase,FNotifyHook`
- L18 _private function_ `SLATE_BEGIN_ARGS(SDMTextureSetBuilderMaterialPropertyCell)`
- L22 _public prototype_ `SDMTextureSetBuilderMaterialPropertyCell();`
- L24 _public prototype_ `virtual ~SDMTextureSetBuilderMaterialPropertyCell() override = default;`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMTextureSetBuilder>& InTextureSetBuilder, const TSharedRef<FDMTextureSetBuilderEntry>& InEntry, int32 InIndex);`
- L30 _public prototype_ `virtual void SetTexture(UTexture* InTexture) override;`
- L34 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L38 _protected member_ `TSharedPtr<FDMTextureSetBuilderEntry> Entry;`
- L39 _protected member_ `TSharedPtr<FDMTextureSetBuilderEntryProvider> EntryProvider;`
- L40 _protected member_ `TStrongObjectPtr<UMaterialInstanceDynamic> MID;`
- L41 _protected member_ `FSlateMaterialBrush MaterialBrush;`
- L43 _protected prototype_ `bool GetPropertyEnabled() const;`
- L45 _protected prototype_ `void SetMaterialForChannelMask();`
- L47 _protected prototype_ `EVisibility GetTextureNameVisibility() const;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/Widgets/SDMTextureSetBuilderUnassignedTextureCell.h` (Private)


#### class `SDMTextureSetBuilderUnassignedTextureCell`  
`class SDMTextureSetBuilderUnassignedTextureCell : public SDMTextureSetBuilderCellBase`  
_L12-31_
- inherits: `SDMTextureSetBuilderCellBase`
- L14 _private function_ `SLATE_BEGIN_ARGS(SDMTextureSetBuilderUnassignedTextureCell)`
- L18 _public prototype_ `SDMTextureSetBuilderUnassignedTextureCell();`
- L20 _public prototype_ `virtual ~SDMTextureSetBuilderUnassignedTextureCell() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDMTextureSetBuilder>& InTextureSetBuilder, UTexture* InTexture, int32 InIndex);`
- L26 _public prototype_ `virtual void SetTexture(UTexture* InTexture) override;`
- L30 _protected member_ `FSlateImageBrush TextureBrush;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Public/DMTextureSetBlueprintFunctionLibrary.h` (Public)


#### class `UDMTextureSetBlueprintFunctionLibrary`  
`class UDMTextureSetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-39_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material Designer Texture Set Blueprint Function Library
- L30 _public prototype_ `static UDMTextureSet* CreateTextureSetFromAssets(const TArray<FAssetData>& InAssets);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Uses the filters from the Texture Set Settings to create a Texture Set based on the given assets. @param InAssets The texture assets to assign to the texture slot. @return A new texture set or nullptr if no textures were filtered.
- L38 _public prototype_ `static void CreateTextureSetFromAssetsInteractive(const TArray<FAssetData>& InAssets, FDMTextureSetBuilderOnComplete InOnComplete);` — Uses the filters from the Texture Set Settings to create a Texture Set based on the given assets and presents the user with a UI to confirm slot assignments. @param InAssets The texture assets to assign to the texture slot. @param InOnComplete Called when the interactive panel is closed, successful or not.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FDMTextureSetBuilderOnComplete, UDMTextureSet*, bool);`
- L13 _prototype_ `DECLARE_DELEGATE_TwoParams(FDMTextureSetBuilderOnComplete, UDMTextureSet*, bool);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Public/DMTextureSetContentBrowserIntegration.h` (Public)


#### class `FDMTextureSetContentBrowserIntegration`  
`class FDMTextureSetContentBrowserIntegration`  
_L13-23_
- L16 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPopulateMenu, FMenuBuilder& InMenuBuilder, const TArray<FAssetData>& InSelectedAssets) static FOnPopulateMenu::RegistrationType& GetPopulateExtenderDelegate();`
- L22 _protected member_ `static FOnPopulateMenu PopulateMenuDelegate;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPopulateMenu, FMenuBuilder& InMenuBuilder, const TArray<FAssetData>& InSelectedAssets) static FOnPopulateMenu::RegistrationType& GetPopulateExtenderDelegate();`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Public/DMTextureSetFactory.h` (Public)


#### class `UDMTextureSetFactory`  
`class UDMTextureSetFactory : public UFactory`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UDMTextureSetFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual FText GetToolTip() const override;`
