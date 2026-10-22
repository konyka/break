# Plugins / UAFLayeringUncookedOnly

- module root: `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly`
- headers: 17; symbols: 236
- symbol kinds: class=11, delegate=2, enum=4, enumerator=10, function=18, macro=2, member=48, namespace=29, prototype=103, struct=9
- PrivateDependencyModuleNames: EditorInteractiveToolsFramework, EditorWidgets, InteractiveToolsFramework, RigVM, RigVMDeveloper, UAFAnimGraph, UAFLayering, UnrealEd
- PrivateIncludePathModuleNames: UAFLayeringEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchyTableAnimationRuntime, HierarchyTableRuntime, InputCore, PropertyEditor, Slate, SlateCore, UAF, UAFAnimGraphUncookedOnly, UAFUncookedOnly, WorkspaceEditor

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFBaseLayer.h` (Internal)


#### class `UUAFBaseLayer`  
`class UUAFBaseLayer : public UUAFLayer`  
_L11-18_
- reflection: `UCLASS(editinlinenew, meta =(Hidden))`
- inherits: `UUAFLayer`
- desc: The editor representation of a base layer in a layer stack
- L16 _public prototype_ `UUAFBaseLayer();`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateLayerWidget() override;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFLayer.h` (Internal)


#### class `UUAFLayer`  
`class UUAFLayer : public UObject`  
_L20-84_
- reflection: `UCLASS(editinlinenew)`
- inherits: `UObject`
- desc: The editor representation of a layer in a layer stack
- L25 _public prototype_ `UUAFLayer();`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateLayerWidget();` — Creates the widget to represent this layer within the layer stack
- L33 _public prototype_ `virtual URigVMPin* CreateLayerGraphContentTraits(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext);` — Responsible for creating all traits that describe this layer Per default this will request the LayerContentProvider and LayerBlendProvider to specify the exact implementation @return Returns the output pin of the created layer. This can be nullptr if the creation failed.
- L36 _public prototype_ `void TogglePreviewVisibility();` — Toggles the preview state of this layer
- L39 _public prototype_ `FName GetLayerName() const;` — Gets the current layer name
- L42 _public prototype_ `void RenameLayer(const FName NewName);` — Renames this layer
- L45 _public prototype_ `bool IsLayerNameValid(const FName NewName) const;` — Checks if the passed in name is a valid name for this layer
- L47 _public prototype_ `EUAFLayerState GetLayerState() const;`
- L48 _public prototype_ `void SetLayerState(const EUAFLayerState InLayerState);`
- L50 _public prototype_ `bool IsLayerBlendProviderValid() const;`
- L51 _public prototype_ `TInstancedStruct<FUAFLayerBlendProviderBase>& GetLayerBlendProvider();`
- L52 _public prototype_ `void SetLayerBlendProvider(const TInstancedStruct<FUAFLayerBlendProviderBase>& InLayerBlendProvider);`
- L54 _public prototype_ `bool IsLayerContentProviderValid() const;`
- L55 _public prototype_ `TInstancedStruct<FUAFLayerContentProviderBase>& GetLayerContentProvider();`
- L56 _public prototype_ `void SetLayerContentProvider(const TInstancedStruct<FUAFLayerContentProviderBase>& InLayerContentProvider);`
- L58 _public prototype_ `void BroadcastModified(EAnimNextEditorDataNotifType InType, bool bNotifyLayerLayoutChanges = false) const;`
- L61 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L62 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L63 _public prototype_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const;`
- L69 _protected member_ `EUAFLayerState LayerState = EUAFLayerState::Enabled;` — `UPROPERTY(EditAnywhere, Category = "Layer")` — The current state of the layer.
- L73 _protected member_ `FName LayerName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer")` — The name of this layer. It has to be unique within one layer stack asset.
- L76 _protected member_ `TInstancedStruct<FUAFLayerContentProviderBase> LayerContentProvider;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (ExcludeBaseStruct))`
- L79 _protected member_ `TInstancedStruct<FUAFLayerBlendProviderBase> LayerBlendProvider;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta = (ExcludeBaseStruct))`
- L81 _protected member_ `FName CachedLayerOutputPoseName = NAME_None;`
- L83 _protected member_ `FName PreRenameLayerName = NAME_None;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFLayerAssetProvider.h` (Internal)


#### struct `FUAFLayerAssetProvider`  
`struct FUAFLayerAssetProvider : public FUAFLayerContentProviderBase`  
_L17-66_
- reflection: `USTRUCT()`
- inherits: `FUAFLayerContentProviderBase`
- desc: Layer content provider to support any pose outputting asset
- L25 _public prototype_ `FUAFLayerAssetProvider() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables this is a requirement for clang to compile without warnings.
- L26 _public prototype_ `virtual ~FUAFLayerAssetProvider() override = default;`
- L27 _public prototype_ `FUAFLayerAssetProvider(const FUAFLayerAssetProvider&) = default;`
- L28 _public prototype_ `FUAFLayerAssetProvider(FUAFLayerAssetProvider&&) = default;`
- L29 _public prototype_ `FUAFLayerAssetProvider& operator=(const FUAFLayerAssetProvider&) = default;`
- L30 _public prototype_ `FUAFLayerAssetProvider& operator=(FUAFLayerAssetProvider&&) = default;`
- L33 _public prototype_ `virtual URigVMPin* CreateLayerContentTrait(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext) override;`
- L34 _public prototype_ `virtual TSharedRef<SWidget> CreateLayerContentWidget(UUAFLayer* InLayer) override;`
- L36 _public prototype_ `void SetLayerAsset(const UObject* InNewAsset);`
- L39 _public prototype_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override;`
- L43 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L47 _private prototype_ `void OnLayerAssetSelectionChanged(const FAssetData& InAssetData);`
- L51 _private member_ `TInstancedStruct<FUAFGraphFactoryAsset> AssetData;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")`
- L54 _private member_ `TWeakObjectPtr<UUAFLayer> OuterLayer = nullptr;` — `UPROPERTY()`
- L59 _private member_ `FAnimNextFactoryParams Parameters_DEPRECATED;` — `UE_DEPRECATED(5.8, "Factory Parameters are not used directly anymore, instead it uses FUAFAssetData internally")` — `UPROPERTY()`
- L63 _private member_ `TObjectPtr<UObject> LayerAsset_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.8, "Using UObject based assets directly is deprecated, use AssetData instead")` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFLayerAssetProvider> : public TStructOpsTypeTraitsBase2<FUAFLayerAssetProvider>`  
_L69-77_
- inherits: `TStructOpsTypeTraitsBase2<FUAFLayerAssetProvider>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L73-75_

#### Free symbols / members of external scopes

- L74 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon274c549a0103`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFLayerBlendProviderBase.h` (Internal)


#### struct `FUAFLayerBlendProviderBase`  
`struct FUAFLayerBlendProviderBase`  
_L16-46_
- reflection: `USTRUCT(meta=(Hidden))`
- L21 _public prototype_ `FUAFLayerBlendProviderBase() = default;`
- L22 _public prototype_ `virtual ~FUAFLayerBlendProviderBase() = default;`
- L26 _public function_ `virtual URigVMPin* CreateBlendGraphTrait(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext)` — Responsible for creating traits to represent this blend and link inputs to the relevant traits. @return The final output pin of this layer blend which can be linked as input by other layers or be linked to the result of the graph
- L29 _public function_ `virtual TSharedRef<SWidget> CreateLayerBlendWidget(UUAFLayer* OuterLayer)` — Creates the widget to represent this blend in the layer stack editor
- L32 _public function_ `virtual const FSlateBrush* GetOverrideLayerBackground() const` — Optional override of the containing layers background brush
- L35 _public function_ `virtual bool GetOverrideIndicatorColor(FSlateColor& OutSlateColor) const` — Optional override of the containing layers indicator color
- L37 _public function_ `void SetAlwaysUpdateChildren(bool bInAlwaysUpdate)`
- L38 _public function_ `bool GetAlwaysUpdateChildren() const`
- L41 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const`
- L45 _private member_ `bool bAlwaysUpdateChildren = false;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFLayerContentProviderBase.h` (Internal)


#### struct `FUAFLayerContentProviderBase`  
`struct FUAFLayerContentProviderBase`  
_L15-33_
- reflection: `USTRUCT(meta=(Hidden))`
- L19 _public prototype_ `FUAFLayerContentProviderBase() = default;`
- L20 _public prototype_ `virtual ~FUAFLayerContentProviderBase() = default;`
- L24 _public function_ `virtual URigVMPin* CreateLayerContentTrait(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext)` — Responsible for creating the traits to play the content of this layer @return The output pin of this layers content trait stack which can be linked to the blend trait stack of this layer
- L27 _public function_ `virtual TSharedRef<SWidget> CreateLayerContentWidget(UUAFLayer* InLayer)` — Responsible for creating the widget to represent this layers content in the layer stack editor
- L30 _public function_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFLayerDefaultBlendProvider.h` (Internal)


#### struct `FUAFDefaultBlendProvider`  
`struct FUAFDefaultBlendProvider : public FUAFLayerBlendProviderBase`  
_L22-85_
- reflection: `USTRUCT()`
- inherits: `FUAFLayerBlendProviderBase`
- L28 _public prototype_ `virtual URigVMPin* CreateBlendGraphTrait(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext) override;`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateLayerBlendWidget(UUAFLayer* InLayer) override;`
- L32 _public prototype_ `virtual const FSlateBrush* GetOverrideLayerBackground() const override;` — TODO: We can abstract this out to some layer override struct or to delegates we can pass into the widget
- L33 _public prototype_ `virtual bool GetOverrideIndicatorColor(FSlateColor& OutSlateColor) const override;`
- L40 _public member_ `bool bLayerEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings")` — TODO: This should be a binding If the layer is currently enabled at all
- L44 _public member_ `EUAFLayerBlendMode BlendMode = EUAFLayerBlendMode::Blend;` — `UPROPERTY(EditAnywhere, Category = "Layer")` — The blend mode this layer uses to blend its result with the pose result of the previous layer
- L48 _public member_ `EAlphaBlendOption BlendOption = EAlphaBlendOption::Linear;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings", meta = (EditCondition = "BlendCurve == nullptr", EditConditionHides))` — If not custom curve is used, which easing method should be used when this layer is blending in or out
- L53 _public member_ `float LayerWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta=(ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", Delta=0.1))` — TODO: This should be a binding The weight to use when blending this layer in. 0 == this layer won't get blended in at all, 1 == 100% of the layer gets blended in
- L58 _public member_ `float LayerBlendInTime = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings", meta=(Delta=0.1))` — TODO: This should be a binding How long it should take to blend this layer in if it has been disabled previously
- L63 _public member_ `float LayerBlendOutTime = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings", meta=(Delta=0.1))` — TODO: This should be a binding How long it should take to blend this layer out
- L68 _public member_ `TObjectPtr<UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Layer")` — TODO: This should be a binding An optional blend mask to apply when blending this layers pose result with the previous layer result
- L73 _public member_ `TObjectPtr<class UCurveFloat> BlendCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings")` — TODO: This should be a binding The custom blend curve to use when blending this layer in or out
- L79 _public member_ `TObjectPtr<UUAFBlendProfile> BlendProfile = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Layer|BlendSettings")` — TODO: This should be a binding The blend profile to use to add more fine grain control over how certain bones should blend in or out This can be used additionally to the blend mask that is used to apply this layer
- L84 _public member_ `FName SetName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer", meta=(EditCondition="BlendMask != nullptr"))` — TODO: In the future we should be able to read this out of the blend mask If a blend mask is applied, this is the named set for abstract hierarchies that mask relates to

#### class `UE::UAF::Layering::FDefaultLayerBlendStructureDataProvider`  
`class FDefaultLayerBlendStructureDataProvider : public IStructureDataProvider`  
_L89-102_
- inherits: `IStructureDataProvider`
- L92 _public function_ `FDefaultLayerBlendStructureDataProvider(TInstancedStruct<FUAFLayerBlendProviderBase>* InBlendProvider) : BlendProvider(InBlendProvider)`
- L96 _public prototype_ `virtual bool IsValid() const override;`
- L97 _public prototype_ `virtual const UStruct* GetBaseStructure() const override;`
- L98 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override;`
- L101 _protected member_ `TInstancedStruct<FUAFLayerBlendProviderBase>* BlendProvider = nullptr;`

#### Free symbols / members of external scopes

- L87 _namespace_ `namespace UE`
- L87 _namespace_ `namespace UAF` (scope `UE`)
- L87 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Layers/UAFMontageProvider.h` (Internal)


#### struct `FUAFMontageProvider`  
`struct FUAFMontageProvider : public FUAFLayerContentProviderBase`  
_L15-45_
- reflection: `USTRUCT(DisplayName="Montage Layer")`
- inherits: `FUAFLayerContentProviderBase`
- desc: Layer content provider to support legacy montages
- L20 _public prototype_ `virtual URigVMPin* CreateLayerContentTrait(UE::UAF::Layering::FLayerCreationContext& LayerCreationContext) override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateLayerContentWidget(UUAFLayer* InLayer) override;`
- L26 _private member_ `FName SlotName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")` — The name of this slot
- L30 _private member_ `bool bAlwaysUpdateSource = false;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")` — If true it will always update the source input, even when montages are fully blended in
- L34 _private member_ `bool bDisableSynchronization = false;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")` — Disables synchronization for this slot even if the playing montage has a sync group setup
- L39 _private member_ `bool bAutoEnableLayerWithMontage = false;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")` — If true, automatically disables and enables the layer based on if a montage in the given slot is active This will cause the content of this layer to always update even if the weight is 0 to auto enable itself
- L43 _private member_ `bool bAutoSetBlendTimesFromMontage = false;` — `UPROPERTY(EditAnywhere, Category = "Layer|Content")` — If true, automatically sets the layer blend in and blend out time based on the montage playing

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/UAFLayerStack_EditorData.h` (Internal)


#### enum `UE::UAF::Layering::EBaseLayerInclusion`  
`enum class EBaseLayerInclusion`  
_L21-27_
- L24 _public enumerator_ `Include` — Includes the base layer when indexing in the layer stack
- L26 _public enumerator_ `Exclude` — Excludes the base layer when indexing in the layer stack

#### class `UUAFLayerStack_EditorData`  
`class UUAFLayerStack_EditorData : public UUAFAnimGraph_EditorData, public FEditorUndoClient`  
_L31-133_
- reflection: `UCLASS()`
- inherits: `UUAFAnimGraph_EditorData,FEditorUndoClient`
- L36 _public prototype_ `UUAFLayerStack_EditorData();`
- L40 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L41 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L46 _public prototype_ `int32 GetNumLayers(const UE::UAF::Layering::EBaseLayerInclusion IncludeBaseLayer = UE::UAF::Layering::EBaseLayerInclusion::Include) const;` — Gets the number of total layers Per default, this also includes the base layer
- L49 _public prototype_ `int32 GetIndexForLayer(const TObjectPtr<UUAFLayer> InLayer, const UE::UAF::Layering::EBaseLayerInclusion IncludeBaseLayer = UE::UAF::Layering::EBaseLayerInclusion::Include) const;` — Gets the index for the given layer, either including the base layer or excluding it
- L52 _public prototype_ `TArray<TObjectPtr<UUAFLayer>> GetAllLayers() const;` — Gets all layers including the base layer
- L55 _public prototype_ `bool IsBaseLayer(const TObjectPtr<UUAFLayer> InLayer) const;` — Checks if the given layer is the base layer of this layer stack
- L58 _public prototype_ `bool IsLastLayer(const TObjectPtr<UUAFLayer> InLayer) const;` — Checks if the given layer is the last layer in this layer stack
- L63 _public prototype_ `void MoveLayerToIndex(const TObjectPtr<UUAFLayer> LayerToMove, int32 NewLayerIndex);` — Moves the given layer to a specific index in the layer stack Does not affect the base layer of the stack NewLayerIndex == 0 is equivalent to the first layer under the base layer
- L68 _public prototype_ `void MoveLayerUp(const TObjectPtr<UUAFLayer> LayerToMove);` — Decreases the index of the given layer within the layers array of this layer stack and moves it visually up in the stack If index == 0, this layer will be the next layer under the base layer Does not affect the base layer of the stack
- L72 _public prototype_ `void MoveLayerDown(const TObjectPtr<UUAFLayer> LayerToMove);` — Increases the index of the given layer within the layers array of this layer stack and moves it visually down in the stack Does not affect the base layer of the stack
- L75 _public prototype_ `void RemoveLayer(const TObjectPtr<UUAFLayer> LayerToDelete);` — Removes the given layer from the layer stack
- L78 _public prototype_ `bool IsLayerNameValid(const TObjectPtr<const UUAFLayer> InLayer, const FName NewLayerName) const;` — Checks if NewLayerName is a valid name for the given layer
- L82 _public prototype_ `FName GetUniqueNameForLayer(const TObjectPtr<UUAFLayer> InLayer) const;` — Generates a unique name for the given layer in the current layer stack Unless the layer name is already valid, then it will return that
- L85 _public prototype_ `void SetLayerState(const TObjectPtr<UUAFLayer> Layer, EUAFLayerState LayerState);` — Set the state of the given layer
- L88 _public prototype_ `void SelectLayer(const TObjectPtr<UUAFLayer> Layer) const;` — Selects the given layer within the layer stack
- L91 _public prototype_ `void ClearSelectedLayer() const;` — Clears the current selection of the layer stack
- L94 _public prototype_ `TObjectPtr<UUAFLayer> AddDefaultAssetBasedLayer(const FAssetData& InAsset);` — Creates a new layer with a default asset and blend provider and adds it on top of the stack
- L98 _protected prototype_ `virtual void Initialize(bool bRecompileVM) override;`
- L99 _protected prototype_ `virtual TSubclassOf<UAssetUserData> GetAssetUserDataClass() const override;`
- L100 _protected prototype_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const override;`
- L101 _protected prototype_ `virtual void OnPreCompileGetProgrammaticGraphs(const FRigVMCompileSettings& InSettings, FAnimNextGetGraphCompileContext& OutCompileContext) override;`
- L105 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L110 _private prototype_ `void BroadcastLayerStackChanged(EAnimNextEditorDataNotifType InType, bool bRefreshUI = false);` — Broadcasts if anything has changed in the current layer stack, with the option to refresh the layering UI
- L113 _private prototype_ `void NotifyLayerLayoutChanged() const;` — Notify the layering UI to refresh its state
- L115 _private prototype_ `void OnLayerAdded(const TObjectPtr<UUAFLayer> NewLayer);`
- L119 _public member_ `TWeakObjectPtr<URigVMGraph> CreatedGraph = nullptr;` — `UPROPERTY(Transient)`
- L121 _public member_ `FLayerLayoutChangedDelegate OnLayerLayoutChanged;`
- L122 _public member_ `FLayerSelectionChangedDelegate OnLayerSelectionChanged;`
- L126 _private member_ `TObjectPtr<UUAFBaseLayer> BaseLayer;` — `UPROPERTY(Instanced, VisibleAnywhere, Category = "LayerStack")`
- L129 _private member_ `TArray<TObjectPtr<UUAFLayer>> Layers;` — `UPROPERTY(Instanced, EditAnywhere, Category = "LayerStack")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UAFLAYERINGUNCOOKEDONLY_API`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FLayerLayoutChangedDelegate);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FLayerLayoutChangedDelegate);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLayerSelectionChangedDelegate, const TWeakObjectPtr<UUAFLayer>);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLayerSelectionChangedDelegate, const TWeakObjectPtr<UUAFLayer>);`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/UAFLayeringStyle.h` (Internal)


#### class `FUAFLayeringStyle`  
`class FUAFLayeringStyle final : public FSlateStyleSet`  
_L7-15_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FUAFLayeringStyle& Get();`
- L13 _private prototype_ `FUAFLayeringStyle();`
- L14 _private prototype_ `~FUAFLayeringStyle();`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Widgets/SDefaultBlendProvider.h` (Internal)


#### class `UE::UAF::Layering::SDefaultBlendProvider`  
`class SDefaultBlendProvider : public SCompoundWidget, public FNotifyHook`  
_L20-35_
- inherits: `SCompoundWidget,FNotifyHook`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDefaultBlendProvider)`
- L24 _public prototype_ `SLATE_ARGUMENT(UUAFLayer*, Layer) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `virtual void NotifyPreChange( class FEditPropertyChain* PropertyAboutToChange ) override;`
- L31 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged ) override;`
- L34 _private member_ `TWeakObjectPtr<UUAFLayer> WeakLayer = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Layering` (scope `UE::UAF`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L18 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Widgets/SLayer.h` (Internal)


#### class `UE::UAF::Layering::SLayer`  
`class SLayer : public SCompoundWidget`  
_L12-36_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SLayer)`
- L16 _public prototype_ `SLATE_ARGUMENT(UUAFLayer*, Layer) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _private prototype_ `const FSlateBrush* GetVisibilityBrushForLayer() const;`
- L23 _private prototype_ `const FSlateBrush* GetAdvancedSettingBrushForLayer() const;`
- L24 _private prototype_ `const FSlateBrush* GetBackgroundBrush() const;`
- L25 _private prototype_ `const FSlateBrush* GetBackgroundOverlayBrush() const;`
- L27 _private prototype_ `FSlateColor GetIndicatorColor() const;`
- L28 _private prototype_ `FText GetLayerName() const;`
- L29 _private prototype_ `bool IsSelected() const;`
- L30 _private prototype_ `bool VerifyLayerName(const FText& Text, FText& OutErrorMessage) const;`
- L31 _private prototype_ `void OnLayerNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo) const;`
- L34 _private member_ `TWeakObjectPtr<UUAFLayer> Layer = nullptr;`
- L35 _private member_ `bool bAdvancedSettingsExpanded = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Widgets/SLayerStack.h` (Internal)


#### class `UE::UAF::Layering::SLayerStack`  
`class SLayerStack : public SCompoundWidget`  
_L21-47_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SLayerStack)`
- L25 _public prototype_ `SLATE_ARGUMENT(UUAFLayerStack*, LayerStack) SLATE_ARGUMENT(TSharedPtr<UE::Workspace::IWorkspaceEditor>, WorkspaceEditor) SLATE_EVENT(FSimpleDelegate, OnSelectedLayerChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `TSharedRef<ITableRow> GenerateLayerRow(TWeakObjectPtr<UUAFLayer> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L35 _private prototype_ `void OnListSelectionChanged(TWeakObjectPtr<UUAFLayer> SelectedItem, ESelectInfo::Type SelectInfo) const;`
- L36 _private prototype_ `TSharedPtr<SWidget> OnConstructContextMenu() const;`
- L37 _private prototype_ `void OnLayerLayoutChanged();`
- L38 _private prototype_ `void OnLayerSelectionChanged(const TWeakObjectPtr<UUAFLayer> SelectedLayer) const;`
- L39 _private prototype_ `void CacheLayersForList();`
- L41 _private member_ `TSharedPtr<SListView<TWeakObjectPtr<UUAFLayer>>> LayerListView = nullptr;`
- L42 _private member_ `TArray<TWeakObjectPtr<UUAFLayer>> CachedLayerPointers;`
- L44 _private member_ `TSharedPtr<FUICommandList> CommandList = nullptr;`
- L45 _private member_ `TWeakObjectPtr<UUAFLayerStack> LayerStack = nullptr;`
- L46 _private member_ `TWeakPtr<UE::Workspace::IWorkspaceEditor> WeakWorkspaceEditor = nullptr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Workspace` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UAF` (scope `UE`)
- L19 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Workspace/UAFLayerStackWorkspaceAssetUserData.h` (Internal)


#### class `UUAFLayerStackWorkspaceAssetUserData`  
`class UUAFLayerStackWorkspaceAssetUserData : public UAnimNextAnimGraphWorkspaceAssetUserData`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAnimNextAnimGraphWorkspaceAssetUserData`
- L16 _protected prototype_ `virtual void GetRootAssetExport(FAssetRegistryTagsContext Context) const override;`
- L17 _protected prototype_ `virtual void GetWorkspaceAssetExports(FAssetRegistryTagsContext Context) const override;`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Internal/Workspace/UAFLayerStackWorkspaceOutlinerData.h` (Internal)


#### struct `FUAFLayerStackWorkspaceOutlinerData`  
`struct FUAFLayerStackWorkspaceOutlinerData : public FAnimNextRigVMAssetOutlinerData`  
_L10-15_
- reflection: `USTRUCT()`
- inherits: `FAnimNextRigVMAssetOutlinerData`
- L14 _public prototype_ `FUAFLayerStackWorkspaceOutlinerData() = default;`

#### struct `FUAFLayerStackLayerOutlinerData`  
`struct FUAFLayerStackLayerOutlinerData : public FWorkspaceOutlinerItemData`  
_L18-26_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L22 _public prototype_ `FUAFLayerStackLayerOutlinerData() = default;`
- L25 _public member_ `FName LayerName = NAME_None;` — `UPROPERTY()`

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Private/UAFLayeringUncookedOnlyModule.h` (Private)


#### class `UE::UAF::Layering::FUAFLayeringUncookedOnlyModule`  
`class FUAFLayeringUncookedOnlyModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace Layering` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Private/Widgets/LayerDragDropOp.h` (Private)


#### class `UE::UAF::Layering::FLayerDragDropOp`  
`class FLayerDragDropOp : public FDecoratedDragDropOp`  
_L17-63_
- inherits: `FDecoratedDragDropOp`
- L20 _public function_ `DRAG_DROP_OPERATOR_TYPE(FLayerDragDropOp, FDecoratedDragDropOp) static TSharedRef<FLayerDragDropOp> New(const TWeakObjectPtr<UUAFLayer> InLayer)`
- L32 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L62 _public member_ `TWeakObjectPtr<UUAFLayer> DraggedLayer = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "FLayerDragDropOp"`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L15 _namespace_ `namespace Layering` (scope `UE::UAF`)
- L53 _function_ `` (scope `UE::UAF::Layering::FLayerDragDropOp::GetDefaultDecorator`)

### `Plugins/Experimental/UAF/UAFLayering/Source/UAFLayeringUncookedOnly/Public/LayeringUncookedOnlyTypes.h` (Public)


#### enum `EUAFLayerBlendMode`  
`enum class EUAFLayerBlendMode : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Blend UMETA(DisplayName= "Blend", ToolTip = "Behaves like a regular blend and will blend together based on layer weight. Weight 0 == Full Source Value, 1 == Full Layer Value")`
- L16 _public enumerator_ `Additive UMETA(DisplayName = "Additive", ToolTip = "The layer will get applied as a additive with the weight of the layer")`
- L17 _public enumerator_ `CacheOnly UMETA(DisplayName = "Cache Only", ToolTip = "The layer will not get applied at all, but will produce a cached output pose if bound")`
- L18 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EUAFLayerState`  
`enum class EUAFLayerState : uint8`  
_L22-27_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `Enabled UMETA(DisplayName="Enabled", ToolTip = "This layer is enabled during preview and runtime.")`
- L25 _public enumerator_ `PreviewDisabled UMETA(DisplayName="Preview Disabled", ToolTip = "This layer is disabled during preview but will execute during runtime.")`
- L26 _public enumerator_ `Disabled UMETA(DisplayName="Disabled", ToolTip = "This layer is disabled during preview and runtime.")`

#### struct `UE::UAF::Layering::FLayerCreationContext`  
`struct FLayerCreationContext`  
_L31-59_
- L33 _public function_ `FLayerCreationContext(const FRigVMCompileSettings& InCompileSettings) : CompileSettings(InCompileSettings)`
- L40 _public member_ `const FRigVMCompileSettings& CompileSettings;` — The compile setting, can be used to report errors
- L43 _public member_ `TObjectPtr<UUAFLayerStack> LayerStack = nullptr;` — The stack this layer creation takes place in
- L46 _public member_ `TObjectPtr<UUAFLayer> Layer = nullptr;` — The layer currently being generated
- L49 _public member_ `TObjectPtr<UAnimNextController> GraphController = nullptr;` — The UAF Controller controlling the underlying graph of this layer stack
- L54 _public member_ `TArray<URigVMPin*> LayerInputs;` — Input Pins 0 == Last layers output 1 == This layers content output
- L58 _public member_ `FVector2D LastNodeLocation = FVector2D::ZeroVector;` — The location of the last created node Used to build a readable graph under the hood with correct node placement

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace UAF` (scope `UE`)
- L29 _namespace_ `namespace Layering` (scope `UE::UAF`)
