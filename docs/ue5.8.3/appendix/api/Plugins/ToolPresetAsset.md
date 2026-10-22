# Plugins / ToolPresetAsset

- module root: `Plugins/Experimental/ToolPresets/Source/ToolPresetAsset`
- headers: 3; symbols: 36
- symbol kinds: class=4, function=10, macro=3, member=9, prototype=8, struct=2
- PrivateDependencyModuleNames: AssetDefinition, CoreUObject, EditorConfig, EditorSubsystem, Engine, Json, JsonUtilities, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ToolPresets/Source/ToolPresetAsset/Private/AssetDefinition_ToolPresetAsset.h` (Private)


#### class `UAssetDefinition_InteractiveToolsPresetCollectionAsset`  
`class UAssetDefinition_InteractiveToolsPresetCollectionAsset : public UAssetDefinitionDefault`  
_L15-34_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L21 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L22 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L23 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L24 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L32 _public function_ `virtual FText GetObjectDisplayNameText(UObject* Object) const override`

### `Plugins/Experimental/ToolPresets/Source/ToolPresetAsset/Public/ToolPresetAsset.h` (Public)


#### struct `FInteractiveToolPresetDefinition`  
`struct FInteractiveToolPresetDefinition`  
_L19-35_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `FString StoredProperties;` — `UPROPERTY(VisibleAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L27 _public member_ `FString Label;` — `UPROPERTY(EditAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L30 _public member_ `FString Tooltip;` — `UPROPERTY(EditAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L32 _public prototype_ `bool IsValid() const;`
- L33 _public prototype_ `void SetStoredPropertyData(TArray<UObject*>& Properties);`
- L34 _public prototype_ `void LoadStoredPropertyData(TArray<UObject*>& Properties);`

#### struct `FInteractiveToolPresetStore`  
`struct FInteractiveToolPresetStore`  
_L38-50_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `TArray<FInteractiveToolPresetDefinition> NamedPresets;` — `UPROPERTY(EditAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L46 _public member_ `FText ToolLabel;` — `UPROPERTY(VisibleAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L49 _public member_ `FSlateBrush ToolIcon;` — `UPROPERTY(VisibleAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`

#### class `UInteractiveToolsPresetCollectionAsset`  
`class UInteractiveToolsPresetCollectionAsset : public UEditorConfigBase`  
_L56-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories=(Object), EditorConfig = "UInteractiveToolsPresetCollectionAsset_DefaultCollection")`
- inherits: `UEditorConfigBase`
- desc: Implements an asset that can be used to store tool settings as a named preset
- L71 _public member_ `TMap<FString, FInteractiveToolPresetStore > PerToolPresets;` — `UPROPERTY(VisibleAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`
- L74 _public member_ `FText CollectionLabel;` — `UPROPERTY(EditAnywhere, Category = "ToolPresetAsset", meta = (EditorConfig))`

#### class `UInteractiveToolsPresetCollectionAssetFactory`  
`class UInteractiveToolsPresetCollectionAssetFactory : public UFactory`  
_L79-116_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L85 _public function_ `UInteractiveToolsPresetCollectionAssetFactory()`
- L93 _public function_ `virtual FText GetToolTip() const override`
- L98 _public function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L110 _public function_ `virtual FString GetDefaultNewAssetName() const override`
- L115 _public function_ `virtual bool ShouldShowInNewMenu() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TOOLPRESETASSET_API`
- L16 _macro_ `#define LOCTEXT_NAMESPACE "ToolPresetAsset"`

### `Plugins/Experimental/ToolPresets/Source/ToolPresetAsset/Public/ToolPresetAssetSubsystem.h` (Public)


#### class `UToolPresetAssetSubsystem`  
`class UToolPresetAssetSubsystem : public UEditorSubsystem`  
_L18-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Using an editor subsystem allows us to make sure that we have a default preset asset whenever the editor exists (and to avoid accidentally trying to make one when it doesn't, such as when running cooking scripts).
- L23 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L24 _public prototype_ `virtual void Deinitialize() override;`
- L26 _public prototype_ `UInteractiveToolsPresetCollectionAsset* GetDefaultCollection();`
- L27 _public prototype_ `bool SaveDefaultCollection();`
- L31 _protected prototype_ `void InitializeDefaultCollection();`
- L34 _protected member_ `TObjectPtr<UInteractiveToolsPresetCollectionAsset> DefaultCollection;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TOOLPRESETASSET_API`
