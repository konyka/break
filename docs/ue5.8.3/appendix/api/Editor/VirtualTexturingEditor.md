# Editor / VirtualTexturingEditor

- module root: `Source/Editor/VirtualTexturingEditor`
- headers: 15; symbols: 156
- symbol kinds: class=15, enum=1, enumerator=2, function=17, member=44, namespace=2, prototype=70, struct=5
- PrivateDependencyModuleNames: AppFramework, AssetDefinition, AssetRegistry, ContentBrowser, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore, Landscape, MaterialEditor, PlacementMode, PropertyEditor, RHI, RenderCore, Renderer, Slate, SlateCore, ToolMenus, UnrealEd

### `Source/Editor/VirtualTexturingEditor/Classes/MaterialCacheVirtualTextureTagFactory.h` (Public)


#### class `UMaterialCacheVirtualTextureTagFactory`  
`class UMaterialCacheVirtualTextureTagFactory : public UFactory`  
_L13-18_
- reflection: `UCLASS(hidecategories = (Object))`
- inherits: `UFactory`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/VirtualTexturingEditor/Classes/RuntimeVirtualTextureDetailsCustomization.h` (Public)


#### class `FRuntimeVirtualTextureDetailsCustomization`  
`class FRuntimeVirtualTextureDetailsCustomization : public IDetailCustomization`  
_L16-49_
- inherits: `IDetailCustomization`
- desc: UI customization for URuntimeVirtualTexture
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L22 _protected prototype_ `FRuntimeVirtualTextureDetailsCustomization();`
- L25 _protected prototype_ `void RefreshMaterialTypes();` — Refresh array of supported material types.
- L28 _protected prototype_ `void RefreshTextDetails();` — Callback for updating text values after an edit.
- L30 _protected prototype_ `void RefreshDetailsView();` — Callback for full update of details view after an edit.
- L33 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L37 _private member_ `TWeakObjectPtr<URuntimeVirtualTexture> VirtualTexture;`
- L39 _private member_ `TArray<int32> SupportedMaterialTypes;`
- L41 _private member_ `IDetailLayoutBuilder* CachedDetailBuilder = nullptr;`
- L43 _private member_ `TSharedPtr<STextBlock> TileCountText;`
- L44 _private member_ `TSharedPtr<STextBlock> TileSizeText;`
- L45 _private member_ `TSharedPtr<STextBlock> TileBorderSizeText;`
- L47 _private member_ `TSharedPtr<STextBlock> SizeText;`
- L48 _private member_ `TSharedPtr<STextBlock> PageTableSizeText;`

#### class `FRuntimeVirtualTextureComponentDetailsCustomization`  
`class FRuntimeVirtualTextureComponentDetailsCustomization : public IDetailCustomization`  
_L53-83_
- inherits: `IDetailCustomization`
- desc: UI customization for URuntimeVirtualTextureComponent
- L56 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L59 _protected prototype_ `FRuntimeVirtualTextureComponentDetailsCustomization();`
- L62 _protected prototype_ `bool IsSetBoundsEnabled() const;` — Returns true if SetBounds button is enabled
- L64 _protected prototype_ `FReply SetBounds();` — Callback for Set Bounds button
- L67 _protected prototype_ `bool IsBuildStreamedMipsEnabled() const;` — Returns true if BuildStreamedMips button is enabled
- L69 _protected prototype_ `EVisibility GetBuildAllStreamedMipsVisible() const;` — Returns the visibility of the BuildAllStreamedMips button
- L71 _protected prototype_ `bool IsStreamingTextureSet() const;` — Returns true if the streaming texture is setup
- L73 _protected prototype_ `bool IsStreamingTextureValid(FText& OutReason) const;` — Returns true if the streaming texture is up to date
- L75 _protected prototype_ `FReply BuildStreamedMips(bool bBuildAll);` — Callback for Build button
- L78 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L82 _private member_ `TWeakObjectPtr<URuntimeVirtualTextureComponent> RuntimeVirtualTextureComponent;`

### `Source/Editor/VirtualTexturingEditor/Classes/RuntimeVirtualTextureFactory.h` (Public)


#### class `URuntimeVirtualTextureFactory`  
`class URuntimeVirtualTextureFactory : public UFactory`  
_L17-24_
- reflection: `UCLASS(hidecategories = (Object))`
- inherits: `UFactory`
- desc: Factory for URuntimeVirtualTexture
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/VirtualTexturingEditor/Classes/VirtualTextureBuilderFactory.h` (Public)


#### class `UVirtualTextureBuilderFactory`  
`class UVirtualTextureBuilderFactory : public UFactory`  
_L12-22_
- reflection: `UCLASS(hidecategories = (Object))`
- inherits: `UFactory`
- desc: Factory for UVirtualTextureBuilder
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L18 _private prototype_ `virtual FText GetDisplayName() const override;`
- L19 _private prototype_ `virtual FText GetToolTip() const override;`
- L20 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Source/Editor/VirtualTexturingEditor/Private/AssetDefinition_MaterialCacheVirtualTextureTag.h` (Private)


#### class `UAssetDefinition_MaterialCacheVirtualTextureTag`  
`class UAssetDefinition_MaterialCacheVirtualTextureTag : public UAssetDefinitionDefault`  
_L9-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/VirtualTexturingEditor/Private/AssetDefinition_RuntimeVirtualTexture.h` (Private)


#### class `UAssetDefinition_RuntimeVirtualTexture`  
`class UAssetDefinition_RuntimeVirtualTexture : public UAssetDefinitionDefault`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/VirtualTexturingEditor/Private/AssetDefinition_VirtualTextureBuilder.h` (Private)


#### class `UAssetDefinition_VirtualTextureBuilder`  
`class UAssetDefinition_VirtualTextureBuilder : public UAssetDefinitionDefault`  
_L9-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/VirtualTexturingEditor/Private/MeshPaintVirtualTextureThumbnailRenderer.h` (Private)


#### class `UMeshPaintVirtualTextureThumbnailRenderer`  
`class UMeshPaintVirtualTextureThumbnailRenderer : public UTextureThumbnailRenderer`  
_L9-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTextureThumbnailRenderer`
- L14 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L15 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`

### `Source/Editor/VirtualTexturingEditor/Private/RuntimeVirtualTextureBuildStreamingMips.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace RuntimeVirtualTexture`
- L16 _prototype_ `bool HasStreamedMips(EShadingPath ShadingPath, URuntimeVirtualTextureComponent* InComponent);` (scope `RuntimeVirtualTexture`) — Returns true if the component describes a runtime virtual texture that has streaming mips.
- L19 _prototype_ `bool BuildStreamedMips(EShadingPath ShadingPath, URuntimeVirtualTextureComponent* InComponent);` (scope `RuntimeVirtualTexture`) — Build the streaming mips texture.
- L21 _prototype_ `FBuildAllStreamedMipsResult BuildAllStreamedMips(const FBuildAllStreamedMipsParams& InParams);` (scope `RuntimeVirtualTexture`)

### `Source/Editor/VirtualTexturingEditor/Private/RuntimeVirtualTextureThumbnailRenderer.h` (Private)


#### class `URuntimeVirtualTextureThumbnailRenderer`  
`class URuntimeVirtualTextureThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L16-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L21 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object);`
- L22 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`

### `Source/Editor/VirtualTexturingEditor/Private/SConvertToVirtualTexture.h` (Private)


#### struct `FConversionStatus`  
`struct FConversionStatus`  
_L23-29_
- L25 _public member_ `bool UserSelected = true;` — Originally selected by the user
- L26 _public member_ `bool UnderSized = false;` — Too small to convert according to user settings
- L27 _public member_ `bool NonPowerOf2 = false;` — Not a power of 2, can't convert
- L28 _public member_ `bool InvalidMaterialUsage = false;`

#### class `FConvertToVTDlg`  
`class FConvertToVTDlg`  
_L37-54_
- desc: FConvertToVTDlg Wrapper class for SConvertToVTDlg. This class creates and launches a dialog then awaits the result to return to the user.
- L46 _public prototype_ `FConvertToVTDlg(const TArray<UTexture2D*>& Textures, bool bBackwards);`
- L49 _public prototype_ `EResult ShowModal();` — Shows the dialog box and waits for the user to respond.
- L52 _private member_ `TSharedPtr<SWindow> DialogWindow;`
- L53 _private member_ `TSharedPtr<class SConvertToVirtualTexture> DialogWidget;`

#### enum `FConvertToVTDlg::EResult`  
`enum EResult`  
_L40-44_
- L42 _public enumerator_ `Cancel = 0` — No/Cancel, normal usage would stop the current action
- L43 _public enumerator_ `Confirm = 1` — Yes/Ok/Etc, normal usage would continue with action

#### struct `FMaterialItem`  
`struct FMaterialItem`  
_L56-59_
- L58 _public member_ `FName Name;`

#### class `SConvertToVirtualTexture`  
`class SConvertToVirtualTexture : public SCompoundWidget`  
_L61-147_
- inherits: `SCompoundWidget`
- L64 _public prototype_ `static void ConvertVTTexture(TArray<UTexture2D*> Objects, bool backwards);`
- L68 _public function_ `SLATE_BEGIN_ARGS(SConvertToVirtualTexture)`
- L71 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bBackwards);` — Window in which this widget resides
- L76 _public prototype_ `void SetBackwards(bool bSetBackwards);`
- L78 _public prototype_ `void SetUserTextures(const TArray<UTexture2D *> &Textures);`
- L80 _public prototype_ `FConvertToVTDlg::EResult GetUserResponse() const;`
- L87 _private prototype_ `TSharedRef<SWidget> CreateAssetLine(int index, const FAssetData &Asset, const FConversionStatus &Status);` — Creates a single line showing an asset and it's status related to VT conversion
- L89 _private prototype_ `TSharedRef<SWidget> GetAuditTrailText(const FAssetData &Asset, int32 index);`
- L91 _private prototype_ `void UpdateList();`
- L93 _private prototype_ `FReply OnButtonClick(FConvertToVTDlg::EResult ButtonID);`
- L95 _private prototype_ `void OnThresholdChanged(TSharedPtr<int32> InSelectedItem, ESelectInfo::Type SelectInfo);`
- L97 _private prototype_ `FText GetThresholdText() const;`
- L99 _private prototype_ `TSharedRef<SWidget> OnGenerateThresholdWidget(TSharedPtr<int32> InItem);`
- L101 _private prototype_ `bool GetFilterButtonEnabled() const;`
- L103 _private prototype_ `FReply OnFilterButtonClicked();`
- L105 _private prototype_ `FReply OnExpanderClicked(int index);`
- L107 _private prototype_ `bool GetOkButtonEnabled() const;`
- L109 _private prototype_ `EVisibility GetDetailVisibility(int index) const;`
- L111 _private prototype_ `const FSlateBrush* GetExpanderImage(int index) const;`
- L113 _private prototype_ `EVisibility GetIntroMessageVisibility() const;`
- L115 _private prototype_ `EVisibility GetErrorMessageVisibility() const;`
- L117 _private prototype_ `EVisibility GetThresholdVisibility() const;`
- L119 _private prototype_ `FText GetIntroMessage() const;`
- L121 _private prototype_ `FText GetErrorMessage() const;`
- L123 _private member_ `TArray<int> ExpandedIndexes;`
- L125 _private member_ `bool bBackwards;`
- L126 _private member_ `FText IntroMessage;`
- L127 _private member_ `FText ErrorMessage;`
- L128 _private member_ `FConvertToVTDlg::EResult UserResponse;`
- L130 _private member_ `TSharedPtr<SVerticalBox> AssetListContainer;`
- L137 _private member_ `TSharedPtr<SWindow> ParentWindow;` — Pointer to the window which holds this Widget, required for modal control
- L139 _private member_ `FVirtualTextureConversionWorker Worker;`
- L140 _private member_ `TArray<FAssetData> AssetList;`
- L141 _private member_ `TArray<FConversionStatus> AssetStatus;`
- L143 _private member_ `int ThresholdValue;`
- L144 _private member_ `bool bThresholdVisible;`
- L146 _private member_ `TArray<TSharedPtr<int32>> TextureSizes;`

### `Source/Editor/VirtualTexturingEditor/Private/VirtualTextureBuilderThumbnailRenderer.h` (Private)


#### class `UVirtualTextureBuilderThumbnailRenderer`  
`class UVirtualTextureBuilderThumbnailRenderer : public UTextureThumbnailRenderer`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTextureThumbnailRenderer`
- L15 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L16 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`

### `Source/Editor/VirtualTexturingEditor/Private/VirtualTextureConversionWorker.h` (Private)


#### class `FVirtualTextureConversionWorker`  
`class FVirtualTextureConversionWorker : public FGCObject`  
_L17-65_
- inherits: `FGCObject`
- L20 _public function_ `FVirtualTextureConversionWorker(bool bInConvertBackward = false) : bConvertBackward(bInConvertBackward)`
- L22 _public member_ `bool bConvertBackward;`
- L25 _public member_ `TArray<TObjectPtr<UTexture2D>> UserTextures;` — Fill this array intially with some textures you want to see converted to vt
- L28 _public member_ `TArray<TObjectPtr<UTexture2D>> Textures;` — These will be filled by calling FilterList
- L29 _public member_ `TArray<TObjectPtr<UMaterial >>Materials;`
- L30 _public member_ `TArray<TObjectPtr<UMaterialFunctionInterface >> Functions;`
- L31 _public member_ `TArray<TObjectPtr<UTexture2D>> SizeRejectedTextures;` — The original selection of the user filtered by textures that match the threshold size
- L32 _public member_ `TSet<TObjectPtr<UTexture2D>> MaterialRejectedTextures;` — Textures that could not be converted due to their usage in materials (connected to unsupported property)
- L41 _public member_ `TMap<TObjectPtr<UObject>, FAuditTrail> AuditTrail;`
- L43 _public function_ `void SetConversionDirection(bool bInConvertBackward)`
- L45 _public prototype_ `void FilterList(int32 SizeThreshold);`
- L48 _public prototype_ `void DoConvert();` — Based on the filtered lists do the actual VT conversion
- L50 _public prototype_ `void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L51 _public function_ `virtual FString GetReferencerName() const override`
- L57 _private prototype_ `void FindAllTexturesAndMaterials_Iteration(TSet<UMaterial*>& InAffectedMaterials, TSet<UMaterialFunctionInterface*>& InAffectedFunctions, TSet<UTexture2D*>& InAffectedTextures, TSet<TObjectPtr<UTexture2D>>& InInvalidTextures, FScopedSlowTask& Task);`
- L63 _private prototype_ `void FindAllTexturesAndMaterials(TArray<TObjectPtr<UMaterial >> &OutAffectedMaterials, TArray<TObjectPtr<UMaterialFunctionInterface >> &OutAffectedFunctions, TArray<TObjectPtr<UTexture2D >> &OutAffectedTextures);`

#### struct `FVirtualTextureConversionWorker::FAuditTrail`  
`struct FAuditTrail`  
_L34-39_
- L36 _public function_ `FAuditTrail(UObject *SetObject, const FString &SetString) : Destination(SetObject), PathDescription(SetString)`
- L37 _public member_ `UObject *Destination;` — Next object in the trail
- L38 _public member_ `FString PathDescription;` — Description on how we go there

### `Source/Editor/VirtualTexturingEditor/Public/RuntimeVirtualTextureSetBounds.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace RuntimeVirtualTexture`
- L12 _prototype_ `void SetBounds(URuntimeVirtualTextureComponent* InComponent);` (scope `RuntimeVirtualTexture`) — Set the transform on a URuntimeVirtualTextureComponent so that it includes the bounds of all associated primitives in the current world.

### `Source/Editor/VirtualTexturingEditor/Public/VirtualTexturingEditorModule.h` (Public)


#### struct `FBuildAllStreamedMipsResult`  
`struct FBuildAllStreamedMipsResult`  
_L13-17_
- L15 _public member_ `bool bSuccess = true;`
- L16 _public member_ `TSet<UPackage*> ModifiedPackages;`

#### struct `FBuildAllStreamedMipsParams`  
`struct FBuildAllStreamedMipsParams`  
_L19-27_
- L22 _public member_ `UWorld* World = nullptr;` — World for which to build the streamed mips
- L24 _public member_ `TConstArrayView<URuntimeVirtualTextureComponent*> Components;` — RVT components for which to build the streamed mips. The components should belong to the World and be properly registered
- L26 _public member_ `bool bRestoreFeatureLevelAfterBuilding = true;` — If the feature level has been changed because we needed to build the SVT for multiple feature levels, defines whether it should be restored afterwards

#### class `IVirtualTexturingEditorModule`  
`class IVirtualTexturingEditorModule : public IModuleInterface`  
_L30-70_
- inherits: `IModuleInterface`
- desc: Module for virtual texturing editor extensions.
- L34 _public prototype_ `virtual bool HasStreamedMips(URuntimeVirtualTextureComponent* InComponent) const PURE_VIRTUAL(IVirtualTexturingEditorModule::HasStreamedMips, return false;);` — `UE_DEPRECATED(5.6, "Use the version that takes a EShadingPath (previously was : EShadingPath::Deferred)")`
- L39 _public prototype_ `virtual bool HasStreamedMips(EShadingPath ShadingPath, URuntimeVirtualTextureComponent* InComponent) const PURE_VIRTUAL(IVirtualTexturingEditorModule::HasStreamedMips, return false;);` — Returns true if the component describes a runtime virtual texture that has streaming low mips for the specified shading path
- L42 _public prototype_ `virtual bool BuildStreamedMips(URuntimeVirtualTextureComponent* InComponent) const PURE_VIRTUAL(IVirtualTexturingEditorModule::BuildStreamedMips, return false;);` — `UE_DEPRECATED(5.6, "Use the version that takes a EShadingPath (previously was : EShadingPath::Deferred)")`
- L51 _public prototype_ `virtual bool BuildStreamedMips(EShadingPath ShadingPath, URuntimeVirtualTextureComponent* InComponent) const PURE_VIRTUAL(IVirtualTexturingEditorModule::BuildStreamedMips, return false;);` — Build the contents of the streaming low mips for a single component and a single shading path. @param ShadingPath shading path for which to build the SVT (note: EShadingPath::Mobile only if enabled) @param InComponent RVT component to build the SVT for. It's expected that this component is registered @return true in case of success
- L61 _public prototype_ `virtual FBuildAllStreamedMipsResult BuildAllStreamedMips(const FBuildAllStreamedMipsParams& InParams) const PURE_VIRTUAL(IVirtualTexturingEditorModule::BuildAllStreamedMips, return {};);` — Build the contents of the streaming low mips for several components for all supported shading paths (e.g. deferred and mobile, if enabled) This is the preferred method for ensuring the SVT is up-to-date across all platforms but is slower because of the potential multiple shading paths @param InWorld world to whom belong the RVT components to bake @param InComponents components to build the SVT for. It's expected that these components are registered @return a struct containing the details about the whole operation
- L63 _public prototype_ `virtual void ConvertVirtualTextures(const TArray<UTexture2D *>& Textures, bool bConvertBackToNonVirtual, const TArray<UMaterial *>* RelatedMaterials ) const PURE_VIRTUAL(IVirtualTexturingEditorModule::ConvertVirtualTextures, );`
- L64 _public prototype_ `virtual void ConvertVirtualTexturesWithDialog(const TArray<UTexture2D*>& Textures, bool bConvertBackToNonVirtual) const PURE_VIRTUAL(IVirtualTexturingEditorModule::ConvertVirtualTexturesWithDialog, );`
- L69 _public prototype_ `virtual TArray<URuntimeVirtualTextureComponent*> GatherRuntimeVirtualTextureComponents(UWorld* InWorld) const PURE_VIRTUAL(IVirtualTexturingEditorModule::GatherRuntimeVirtualTextureComponents, return {};);` — @return the list of valid RVT components for this world
