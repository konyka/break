# Plugins / NiagaraEditorWidgets

- module root: `Plugins/FX/Niagara/Source/NiagaraEditorWidgets`
- headers: 63; symbols: 1406
- symbol kinds: class=76, delegate=5, enum=5, enumerator=12, function=61, macro=3, member=303, namespace=3, prototype=927, struct=4, typedef=7
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, Core, CoreUObject, CurveEditor, DataHierarchyEditor, DesktopPlatform, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, KismetWidgets, Niagara, NiagaraBlueprintNodes, NiagaraCore, NiagaraEditor, Projects, PropertyEditor, Sequencer, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, UserAssetTagsEditor
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: 
- PublicIncludePathModuleNames: 

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataChannelDetails.h` (Private)


#### class `FNiagaraDataChannelIslandsDetails`  
`class FNiagaraDataChannelIslandsDetails : public IDetailCustomization`  
_L16-25_
- inherits: `IDetailCustomization`
- desc: Details customization for Niagara data channels.
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _private member_ `TWeakObjectPtr<UNiagaraDataChannel_Islands> DataChannel;`

#### class `FNiagaraDataInterfaceDataChannelReadDetails`  
`class FNiagaraDataInterfaceDataChannelReadDetails : public FNiagaraDataInterfaceDetailsBase`  
_L29-39_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara data channel read data interface.
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L37 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceDataChannelRead> ReadDataInterfaceWeak;`
- L38 _private member_ `TWeakObjectPtr<UNiagaraSystem> NiagaraSystemWeak;`

#### class `FNiagaraDataChannelBPNodeDetails`  
`class FNiagaraDataChannelBPNodeDetails : public IDetailCustomization`  
_L43-48_
- inherits: `IDetailCustomization`
- desc: Details customization for Blueprint nodes.
- L46 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L47 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceCurveDetails.h` (Private)


#### class `FNiagaraDataInterfaceCurveDetailsBase`  
`class FNiagaraDataInterfaceCurveDetailsBase : public FNiagaraDataInterfaceDetailsBase`  
_L20-49_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Base details customization for curve data interfaces.
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const = 0;`
- L27 _protected function_ `virtual bool GetIsColorCurve() const`
- L28 _protected function_ `virtual float GetDefaultHeight() const`
- L29 _protected prototype_ `virtual UCurveBase* GetUsedCurveAsset(UNiagaraDataInterfaceCurveBase* CurveDI) const;`
- L31 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const = 0;`
- L32 _protected prototype_ `virtual void ImportSelectedAsset(UObject* SelectedAsset);`
- L33 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const = 0;`
- L36 _protected member_ `IDetailLayoutBuilder* CustomDetailBuilder = nullptr;`
- L39 _private prototype_ `virtual TSharedRef<SWidget> GetCurveToCopyMenu();`
- L40 _private prototype_ `void SetGradientVisibility(bool bInShowGradient);`
- L41 _private prototype_ `int32 GetGradientCurvesSwitcherIndex() const;`
- L42 _private prototype_ `bool IsGradientVisible() const;`
- L43 _private prototype_ `void OnShowInCurveEditor() const;`
- L44 _private prototype_ `void CurveToCopySelected(const FAssetData& AssetData);`
- L45 _private prototype_ `FReply CurveTemplateSelected(TWeakObjectPtr<UCurveFloat> WeakCurveAsset, TSharedPtr<class FCurveEditor> CurveEditor);`
- L46 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceCurveBase> CurveDataInterfaceWeak;`
- L47 _private member_ `TWeakPtr<FNiagaraStackCurveEditorOptions> StackCurveEditorOptionsWeak;`
- L48 _private member_ `bool bCopyAssetData = true;`

#### class `FNiagaraDataInterfaceCurveDetails`  
`class FNiagaraDataInterfaceCurveDetails : public FNiagaraDataInterfaceCurveDetailsBase`  
_L52-62_
- inherits: `FNiagaraDataInterfaceCurveDetailsBase`
- desc: Details customization for curve data interfaces.
- L55 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L58 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const override;`
- L59 _protected function_ `virtual float GetDefaultHeight() const override`
- L60 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const override;`
- L61 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const override;`

#### class `FNiagaraDataInterfaceVector2DCurveDetails`  
`class FNiagaraDataInterfaceVector2DCurveDetails : public FNiagaraDataInterfaceCurveDetailsBase`  
_L66-75_
- inherits: `FNiagaraDataInterfaceCurveDetailsBase`
- desc: Details customization for vector 2d curve data interfaces.
- L69 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L72 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const override;`
- L73 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const override;`
- L74 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const override;`

#### class `FNiagaraDataInterfaceVectorCurveDetails`  
`class FNiagaraDataInterfaceVectorCurveDetails : public FNiagaraDataInterfaceCurveDetailsBase`  
_L78-87_
- inherits: `FNiagaraDataInterfaceCurveDetailsBase`
- desc: Details customization for vector curve data interfaces.
- L81 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L84 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const override;`
- L85 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const override;`
- L86 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const override;`

#### class `FNiagaraDataInterfaceVector4CurveDetails`  
`class FNiagaraDataInterfaceVector4CurveDetails : public FNiagaraDataInterfaceCurveDetailsBase`  
_L90-99_
- inherits: `FNiagaraDataInterfaceCurveDetailsBase`
- desc: Details customization for vector 4 curve data interfaces.
- L93 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L96 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const override;`
- L97 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const override;`
- L98 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const override;`

#### class `FNiagaraDataInterfaceColorCurveDetails`  
`class FNiagaraDataInterfaceColorCurveDetails : public FNiagaraDataInterfaceCurveDetailsBase`  
_L102-112_
- inherits: `FNiagaraDataInterfaceCurveDetailsBase`
- desc: Details customization for color curve data interfaces.
- L105 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L108 _protected prototype_ `virtual void GetCurveProperties(IDetailLayoutBuilder& DetailBuilder, TArray<TSharedRef<IPropertyHandle>>& OutCurveProperties) const override;`
- L109 _protected function_ `virtual bool GetIsColorCurve() const override`
- L110 _protected prototype_ `virtual FTopLevelAssetPath GetSupportedAssetClassName() const override;`
- L111 _protected prototype_ `virtual void GetFloatCurvesFromAsset(UObject* SelectedAsset, TArray<FRichCurve>& FloatCurves) const override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceDetails.h` (Private)


#### class `FNiagaraDataInterfaceDetailsBase`  
`class FNiagaraDataInterfaceDetailsBase : public IDetailCustomization`  
_L16-33_
- inherits: `IDetailCustomization`
- desc: Base details customization for Niagara data interfaces.
- L19 _public prototype_ `~FNiagaraDataInterfaceDetailsBase();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L25 _private prototype_ `void OnErrorsRefreshed();`
- L28 _private member_ `TWeakObjectPtr<UNiagaraDataInterface> DataInterface;`
- L29 _private member_ `TSharedPtr<FNiagaraDataInterfaceCustomNodeBuilder> CustomBuilder;`
- L30 _private member_ `IDetailCategoryBuilder* ErrorsCategoryBuilder;`
- L31 _private member_ `TWeakPtr<IDetailLayoutBuilder> Builder;`
- L32 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilitiesWeak;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceGrid2DCollectionDetails.h` (Private)


#### class `FNiagaraDataInterfaceGrid2DCollectionDetails`  
`class FNiagaraDataInterfaceGrid2DCollectionDetails : public FNiagaraDataInterfaceDetailsBase`  
_L20-39_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara Grid2D Collection data interface.
- L23 _public prototype_ `~FNiagaraDataInterfaceGrid2DCollectionDetails();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _private prototype_ `void OnInterfaceChanged();`
- L29 _private prototype_ `void OnDataChanged();`
- L30 _private prototype_ `void GeneratePreviewAttributes(TArray<TSharedPtr<FName>>& SourceArray);`
- L32 _private prototype_ `EVisibility IsOverideFormatVisibile() const;`
- L33 _private prototype_ `EVisibility IsOverideFormatInvisibile() const;`
- L34 _private prototype_ `FText GetDefaultFormatText() const;`
- L37 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceGrid2DCollection> Grid2DInterfacePtr;`
- L38 _private member_ `TSharedPtr<SNiagaraNamePropertySelector> PreviewAttributesBuilder;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceGrid3DCollectionDetails.h` (Private)


#### class `FNiagaraDataInterfaceGrid3DCollectionDetails`  
`class FNiagaraDataInterfaceGrid3DCollectionDetails : public FNiagaraDataInterfaceDetailsBase`  
_L20-39_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara Grid3D Collection data interface.
- L23 _public prototype_ `~FNiagaraDataInterfaceGrid3DCollectionDetails();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _private prototype_ `void OnInterfaceChanged();`
- L29 _private prototype_ `void OnDataChanged();`
- L30 _private prototype_ `void GeneratePreviewAttributes(TArray<TSharedPtr<FName>>& SourceArray);`
- L32 _private prototype_ `EVisibility IsOverideFormatVisibile() const;`
- L33 _private prototype_ `EVisibility IsOverideFormatInvisibile() const;`
- L34 _private prototype_ `FText GetDefaultFormatText() const;`
- L37 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceGrid3DCollection> Grid3DInterfacePtr;`
- L38 _private member_ `TSharedPtr<SNiagaraNamePropertySelector> PreviewAttributesBuilder;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceMeshRendererInfoDetails.h` (Private)


#### class `FNiagaraDataInterfaceMeshRendererInfoDetails`  
`class FNiagaraDataInterfaceMeshRendererInfoDetails : public FNiagaraDataInterfaceDetailsBase`  
_L16-47_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara mesh renderer info data interface.
- L19 _public prototype_ `~FNiagaraDataInterfaceMeshRendererInfoDetails();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _private typedef_ `using TRendererPtr = TWeakObjectPtr<UNiagaraMeshRendererProperties>;`
- L25 _private typedef_ `using SMeshRendererComboBox = SComboBox<TRendererPtr>;`
- L27 _private prototype_ `void OnInterfaceChanged();`
- L28 _private prototype_ `void GenerateRendererList();`
- L29 _private prototype_ `UNiagaraMeshRendererProperties* GetSelectedRenderer() const;`
- L30 _private prototype_ `void SetSelectedRenderer(TRendererPtr Selection, ESelectInfo::Type SelectInfo);`
- L31 _private prototype_ `FText GetRendererTextLabel(TRendererPtr Renderer) const;`
- L32 _private function_ `FText GetSelectedRendererTextLabel() const`
- L33 _private prototype_ `TSharedRef<SWidget> CreateRendererItemWidget(TRendererPtr Item);`
- L35 _private prototype_ `static FText CreateRendererTextLabel(const UNiagaraMeshRendererProperties* Properties);`
- L39 _private member_ `TSharedPtr<SMeshRendererComboBox> MeshRendererWidget;`
- L40 _private member_ `TArray<TRendererPtr> RendererList;`
- L41 _private member_ `TArray<FText> RendererLabels;`
- L42 _private member_ `IDetailLayoutBuilder* LayoutBuilder = nullptr;`
- L43 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceMeshRendererInfo> DataInterface;`
- L44 _private member_ `IDetailCategoryBuilder* SourceCategory = nullptr;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> MeshRendererProperty;`
- L46 _private member_ `bool bSettingSelection = false;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceSkeletalMeshDetails.h` (Private)


#### class `FNiagaraDataInterfaceSkeletalMeshDetails`  
`class FNiagaraDataInterfaceSkeletalMeshDetails : public FNiagaraDataInterfaceDetailsBase`  
_L21-47_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara skeletal mesh data interface.
- L24 _public prototype_ `~FNiagaraDataInterfaceSkeletalMeshDetails();`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L29 _private prototype_ `void OnInterfaceChanged();`
- L30 _private prototype_ `void OnDataChanged();`
- L31 _private prototype_ `void GenerateRegionsArray(TArray<TSharedPtr<FName>>& SourceArray);`
- L32 _private prototype_ `void GenerateBonesArray(TArray<TSharedPtr<FName>>& SourceArray);`
- L33 _private prototype_ `void GenerateSocketsArray(TArray<TSharedPtr<FName>>& SourceArray);`
- L36 _private member_ `TSharedPtr<FNiagaraDetailSourcedArrayBuilder> RegionsBuilder;`
- L37 _private member_ `TSharedPtr<FNiagaraDetailSourcedArrayBuilder> BonesBuilder;`
- L38 _private member_ `TSharedPtr<FNiagaraDetailSourcedArrayBuilder> SocketsBuilder;`
- L39 _private member_ `TSharedPtr<SNiagaraNamePropertySelector> ExcludeBoneWidget;`
- L40 _private member_ `IDetailLayoutBuilder* LayoutBuilder;`
- L41 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceSkeletalMesh> MeshInterface;`
- L42 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMeshObject;`
- L43 _private member_ `TWeakObjectPtr<USkinnedAsset> SkinnedMeshObject;`
- L45 _private member_ `IDetailCategoryBuilder* MeshCategory;`
- L46 _private member_ `IDetailCategoryBuilder* SkelCategory;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceSocketReaderDetails.h` (Private)


#### class `FNiagaraDataInterfaceSocketReaderDetails`  
`class FNiagaraDataInterfaceSocketReaderDetails : public IDetailCustomization`  
_L11-26_
- inherits: `IDetailCustomization`
- desc: FNiagaraDataInterfaceDetailsBase
- L14 _public prototype_ `~FNiagaraDataInterfaceSocketReaderDetails();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _private prototype_ `void OnDataChanged();`
- L21 _private prototype_ `TArray<TSharedPtr<FName>> GetSocketNames() const;`
- L24 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceSocketReader> WeakDataInterface;`
- L25 _private member_ `TSharedPtr<FNiagaraDetailSourcedArrayBuilder> SocketArrayBuilder;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceSpriteRendererInfoDetails.h` (Private)


#### class `FNiagaraDataInterfaceSpriteRendererInfoDetails`  
`class FNiagaraDataInterfaceSpriteRendererInfoDetails : public FNiagaraDataInterfaceDetailsBase`  
_L16-47_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara Sprite renderer info data interface.
- L19 _public prototype_ `virtual ~FNiagaraDataInterfaceSpriteRendererInfoDetails();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _private typedef_ `using TRendererPtr = TWeakObjectPtr<UNiagaraSpriteRendererProperties>;`
- L25 _private typedef_ `using SSpriteRendererComboBox = SComboBox<TRendererPtr>;`
- L27 _private prototype_ `void OnInterfaceChanged();`
- L28 _private prototype_ `void GenerateRendererList();`
- L29 _private prototype_ `UNiagaraSpriteRendererProperties* GetSelectedRenderer() const;`
- L30 _private prototype_ `void SetSelectedRenderer(TRendererPtr Selection, ESelectInfo::Type SelectInfo);`
- L31 _private prototype_ `FText GetRendererTextLabel(TRendererPtr Renderer) const;`
- L32 _private function_ `FText GetSelectedRendererTextLabel() const`
- L33 _private prototype_ `TSharedRef<SWidget> CreateRendererItemWidget(TRendererPtr Item);`
- L35 _private prototype_ `static FText CreateRendererTextLabel(const UNiagaraSpriteRendererProperties* Properties);`
- L39 _private member_ `TSharedPtr<SSpriteRendererComboBox> SpriteRendererWidget;`
- L40 _private member_ `TArray<TRendererPtr> RendererList;`
- L41 _private member_ `TArray<FText> RendererLabels;`
- L42 _private member_ `IDetailLayoutBuilder* LayoutBuilder = nullptr;`
- L43 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceSpriteRendererInfo> DataInterface;`
- L44 _private member_ `IDetailCategoryBuilder* SourceCategory = nullptr;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> SpriteRendererProperty;`
- L46 _private member_ `bool bSettingSelection = false;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDataInterfaceStaticMeshDetails.h` (Private)


#### class `FNiagaraDataInterfaceStaticMeshDetails`  
`class FNiagaraDataInterfaceStaticMeshDetails : public FNiagaraDataInterfaceDetailsBase`  
_L20-40_
- inherits: `FNiagaraDataInterfaceDetailsBase`
- desc: Details customization for Niagara static mesh data interface.
- L23 _public prototype_ `~FNiagaraDataInterfaceStaticMeshDetails();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _private prototype_ `void OnInterfaceChanged();`
- L29 _private prototype_ `void OnDataChanged();`
- L31 _private prototype_ `void GenerateSocketsArray(TArray<TSharedPtr<FName>>& SourceArray);`
- L34 _private member_ `TSharedPtr<FNiagaraDetailSourcedArrayBuilder> SocketsBuilder;`
- L35 _private member_ `IDetailLayoutBuilder* LayoutBuilder;`
- L36 _private member_ `TWeakObjectPtr<UNiagaraDataInterfaceStaticMesh> MeshInterface;`
- L37 _private member_ `TWeakObjectPtr<UStaticMesh> MeshObject;`
- L39 _private member_ `IDetailCategoryBuilder* MeshCategory;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDecalRendererDetails.h` (Private)


#### class `FNiagaraDecalRendererDetails`  
`class FNiagaraDecalRendererDetails : public FNiagaraRendererDetails`  
_L9-15_
- inherits: `FNiagaraRendererDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraDetailSourcedArrayBuilder.h` (Private)


#### class `FNiagaraDetailSourcedArrayBuilder`  
`class FNiagaraDetailSourcedArrayBuilder : public FDetailArrayBuilder , public TSharedFromThis<FNiagaraDetailSourcedArrayBuilder>`  
_L15-38_
- inherits: `FDetailArrayBuilder,TSharedFromThis<FNiagaraDetailSourcedArrayBuilder>`
- desc: Details customization for arrays composed of FName properties (or wrappers). The array contents are selected from a predetermined source list.
- L19 _public prototype_ `FNiagaraDetailSourcedArrayBuilder(TSharedRef<IPropertyHandle> InBaseProperty, const TArray<TSharedPtr<FName>>& InOptionsSource, const FName InFNameSubproperty = NAME_None, bool InGenerateHeader = true, bool InDisplayResetToDefault = true, bool InDisplayElementNum = true, bool InAllowAutoFill = true);`
- L21 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L22 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L24 _public prototype_ `void SetSourceArray(const TArray<TSharedPtr<FName>>& InOptionsSource);`
- L27 _private prototype_ `void OnGenerateEntry(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder);`
- L30 _private member_ `TArray<TSharedPtr<FName>> OptionsSourceList;`
- L33 _private member_ `TSharedPtr<IPropertyHandleArray> ArrayProperty;`
- L35 _private member_ `FName FNameSubproperty;` — Subproperty of type FName that needs to be edited - in case of FName wrappers
- L37 _private member_ `bool bAllowAutoFill;` — Whether or not to add a context menu option to reset the array to the list of all possible options

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraLightRendererDetails.h` (Private)


#### class `FNiagaraLightRendererDetails`  
`class FNiagaraLightRendererDetails : public FNiagaraRendererDetails`  
_L9-15_
- inherits: `FNiagaraRendererDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraMeshRendererDetails.h` (Private)


#### class `FNiagaraMeshRendererDetails`  
`class FNiagaraMeshRendererDetails : public FNiagaraRendererDetails`  
_L11-27_
- inherits: `FNiagaraRendererDetails`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L19 _private prototype_ `void OnInvalidateDetails();`
- L20 _private prototype_ `void OnGenerateMeshWidget(TSharedRef<IPropertyHandle> Property, int32 Index, IDetailChildrenBuilder& ChildrenBuilder);`
- L22 _private prototype_ `void OnGenerateMaterialOverrideWidget(TSharedRef<IPropertyHandle> Property, int32 Index, IDetailChildrenBuilder& ChildrenBuilder);`
- L24 _private member_ `IDetailLayoutBuilder* LayoutBuilder = nullptr;`
- L25 _private member_ `bool bEnableMeshFlipbook = false;`
- L26 _private member_ `bool bEnableMaterialOverrides = false;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraRendererDetails.h` (Private)


#### class `FNiagaraRendererDetails`  
`class FNiagaraRendererDetails : public IDetailCustomization`  
_L9-13_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `void SetupCategories(IDetailLayoutBuilder& DetailBuilder, TConstArrayView<FName> CategoryOrder, TConstArrayView<FName> CollapsedCategories);`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraRibbonRendererDetails.h` (Private)


#### class `FNiagaraRibbonRendererDetails`  
`class FNiagaraRibbonRendererDetails : public FNiagaraRendererDetails`  
_L9-15_
- inherits: `FNiagaraRendererDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/NiagaraSpriteRendererDetails.h` (Private)


#### class `FNiagaraSpriteRendererDetails`  
`class FNiagaraSpriteRendererDetails : public FNiagaraRendererDetails`  
_L9-15_
- inherits: `FNiagaraRendererDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/DetailCustomizations/SNiagaraNamePropertySelector.h` (Private)


#### class `SNiagaraNamePropertySelector`  
`class SNiagaraNamePropertySelector : public SCompoundWidget`  
_L15-61_
- inherits: `SCompoundWidget`
- desc: Details customization for arrays composed of FName properties (or wrappers). The array contents are selected from a predetermined source list.
- L18 _public function_ `SLATE_BEGIN_ARGS(SNiagaraNamePropertySelector)`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IPropertyHandle> InBaseProperty, const TArray<TSharedPtr<FName>>& InOptionsSource);`
- L23 _public prototype_ `void SetSourceArray(TArray<TSharedPtr<FName>>& InOptionsSource);`
- L26 _private prototype_ `void OnComboOpening();`
- L28 _private prototype_ `void OnSelectionChanged(TSharedPtr<FName> InNewSelection, ESelectInfo::Type);`
- L30 _private prototype_ `TSharedRef<SWidget> MakeSelectionWidget(TSharedPtr<FName> InItem);`
- L32 _private prototype_ `FText GetComboText() const;`
- L34 _private prototype_ `void OnSearchBoxTextChanged(const FText& InSearchText);`
- L36 _private prototype_ `void OnSearchBoxTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L38 _private prototype_ `TSharedRef<ITableRow> GenerateAddElementRow(TSharedPtr<FName> Entry, const TSharedRef<STableViewBase> &OwnerTable) const;`
- L40 _private prototype_ `void GenerateFilteredElementList(const FString& InSearchText);`
- L42 _private function_ `FText GetCurrentSearchString() const`
- L45 _private member_ `TArray<TSharedPtr<FName>> OptionsSourceList;`
- L47 _private member_ `TArray<TSharedPtr<FName>> FilteredSourceList;` — List of component class names, filtered by the current search string
- L49 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The current array property being edited
- L52 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box control - part of the combo drop down
- L55 _private member_ `TSharedPtr< SListView<TSharedPtr<FName>> > ElementsListView;` — The component list control - part of the combo drop down
- L58 _private member_ `FText CurrentSearchString;` — The current search string
- L60 _private member_ `TSharedPtr<SComboButton> ElementButton;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Misc/CurveEditorIntegrationUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NiagaraEditorWidgets` (scope `UE`)
- L19 _prototype_ `TUniquePtr<FCurveModel> ResolveNiagaraCurveModel(const CurveEditor::FCurveModelLookUpArgs& InArgs);` (scope `UE::NiagaraEditorWidgets`) — Tries to create a FCurveModel that was previously in the FCurveEditor but has since been removed. This is needed for Curve Editor's command based undo system. The user may make a change to curve X, then click on curve Y, and then undo; FCurveEditor::CurveData only contains the visible curves, so it will ask us to temporarily recreate the curve for X, which we try to match based off of the metadata it had when it existed.

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/NiagaraEditorWidgetsStyle.h` (Private)


#### class `FNiagaraEditorWidgetsStyle`  
`class FNiagaraEditorWidgetsStyle : public FSlateStyleSet`  
_L8-41_
- inherits: `FSlateStyleSet`
- desc: Manages the style which provides resources for niagara editor widgets.
- L12 _public prototype_ `static void Register();`
- L13 _public prototype_ `static void Unregister();`
- L14 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L20 _public prototype_ `static const FNiagaraEditorWidgetsStyle& Get();` — @return The Slate style set for niagara editor widgets
- L22 _public prototype_ `static void ReinitializeStyle();`
- L24 _private prototype_ `FNiagaraEditorWidgetsStyle();`
- L25 _private prototype_ `void InitColors();`
- L26 _private prototype_ `void InitTextStyles();`
- L27 _private prototype_ `void InitRowStyles();`
- L28 _private prototype_ `void InitButtonStyles();`
- L29 _private prototype_ `void InitInlineDynamicInputBrushes();`
- L30 _private prototype_ `void InitSystemOverviewMisc();`
- L31 _private prototype_ `void InitIcons();`
- L32 _private prototype_ `void InitSizes();`
- L33 _private prototype_ `void InitStackDropTarget();`
- L34 _private prototype_ `void InitMisc();`
- L36 _private prototype_ `void InitSystemOverviewColors();`
- L37 _private prototype_ `void InitScopeColors();`
- L38 _private prototype_ `void InitStackTextStyles();`
- L40 _private member_ `static TSharedPtr<FNiagaraEditorWidgetsStyle> NiagaraEditorWidgetsStyle;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/NiagaraEditorWidgetsUtilities.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace FNiagaraStackEditorWidgetsUtilities`
- L20 _prototype_ `FName GetColorNameForExecutionCategory(FName ExecutionCategoryName);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L22 _prototype_ `FName GetIconNameForExecutionSubcategory(FName ExecutionSubcategoryName, bool bIsHighlighted);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L24 _prototype_ `FName GetIconColorNameForExecutionCategory(FName ExecutionCategoryName);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L26 _prototype_ `FName GetAddItemButtonStyleNameForExecutionCategory(FName ExecutionCategoryName);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L28 _prototype_ `FText GetIconTextForInputMode(UNiagaraStackFunctionInput::EValueMode InputValueMode);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L30 _prototype_ `FText GetIconToolTipForInputMode(UNiagaraStackFunctionInput::EValueMode InputValueMode);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L32 _prototype_ `FName GetIconColorNameForInputMode(UNiagaraStackFunctionInput::EValueMode InputValueMode);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L34 _prototype_ `bool AddStackEntryAssetContextMenuActions(FMenuBuilder& MenuBuilder, UNiagaraStackEntry& StackEntry);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L36 _prototype_ `bool AddStackItemContextMenuActions(FMenuBuilder& MenuBuilder, UNiagaraStackItem& StackItem);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L38 _prototype_ `bool AddStackModuleItemContextMenuActions(FMenuBuilder& MenuBuilder, UNiagaraStackModuleItem& StackItem, TSharedRef<SWidget> TargetWidget);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L40 _prototype_ `void AddStackSimulationStageGroupContextMenuActions(FMenuBuilder& MenuBuilder, UNiagaraStackSimulationStageGroup* SimulationStageGroup, TSharedRef<SWidget> TagetWidget);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L42 _prototype_ `bool AddStackNoteContextMenuActions(FMenuBuilder& MenuBuilder, UNiagaraStackEntry& StackEntry);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L44 _prototype_ `TSharedRef<FDragDropOperation> ConstructDragDropOperationForStackEntries(const TArray<UNiagaraStackEntry*>& DraggedEntries);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L46 _prototype_ `void HandleDragLeave(const FDragDropEvent& InDragDropEvent);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L48 _prototype_ `TOptional<EItemDropZone> RequestDropForStackEntry(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry, UNiagaraStackEntry::EDropOptions DropOptions);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L50 _prototype_ `bool HandleDropForStackEntry(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry, UNiagaraStackEntry::EDropOptions DropOptions);` (scope `FNiagaraStackEditorWidgetsUtilities`)
- L52 _prototype_ `FString StackEntryToStringForListDebug(UNiagaraStackEntry* StackEntry);` (scope `FNiagaraStackEditorWidgetsUtilities`)

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/NiagaraOverviewGraphNodeFactory.h` (Private)


#### class `FNiagaraOverviewGraphNodeFactory`  
`class FNiagaraOverviewGraphNodeFactory : public FGraphNodeFactory`  
_L10-14_
- inherits: `FGraphNodeFactory`
- L13 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNodeWidget(UEdGraphNode* InNode) override;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/NiagaraScratchPadCommandContext.h` (Private)


#### class `FNiagaraScratchPadCommandContext`  
`class FNiagaraScratchPadCommandContext : public TSharedFromThis<FNiagaraScratchPadCommandContext>`  
_L12-80_
- inherits: `TSharedFromThis<FNiagaraScratchPadCommandContext>`
- L15 _public prototype_ `FNiagaraScratchPadCommandContext(UNiagaraScratchPadViewModel* InScratchPadViewModel);`
- L17 _public prototype_ `TSharedRef<FUICommandList> GetCommands();`
- L19 _public prototype_ `bool ProcessCommandBindings(const FKeyEvent& InKeyEvent);`
- L21 _public prototype_ `void AddMenuItems(FMenuBuilder& MenuBuilder);`
- L24 _private prototype_ `void SetupCommands();`
- L26 _private prototype_ `void RenameSelectedScript() const;`
- L28 _private prototype_ `bool CanRenameSelectedScript() const;`
- L30 _private prototype_ `FText GetCanRenameSelectedScriptToolTip() const;`
- L32 _private prototype_ `bool CanCutSelectedScripts() const;`
- L34 _private prototype_ `FText GetCanCutSelectedScriptsToolTip() const;`
- L36 _private prototype_ `void CutSelectedScripts() const;`
- L38 _private prototype_ `bool CanCopySelectedScripts() const;`
- L40 _private prototype_ `FText GetCanCopySelectedScriptsToolTip() const;`
- L42 _private prototype_ `void CopySelectedScripts() const;`
- L44 _private prototype_ `bool CanPasteSelectedScripts() const;`
- L46 _private prototype_ `FText GetCanPasteSelectedScriptsToolTip() const;`
- L48 _private prototype_ `void PasteSelectedScripts() const;`
- L50 _private prototype_ `bool CanDeleteSelectedScripts() const;`
- L52 _private prototype_ `FText GetCanDeleteSelectedScriptsToolTip() const;`
- L54 _private prototype_ `void DeleteSelectedScripts() const;`
- L56 _private prototype_ `bool CanApplyChangesToSelectedScripts() const;`
- L58 _private prototype_ `void ApplyChangesToSelectedScripts() const;`
- L60 _private prototype_ `bool CanDiscardChangesFromSelectedScripts() const;`
- L62 _private prototype_ `void DiscardChangesFromSelectedScripts() const;`
- L64 _private prototype_ `bool CanSelectNextUsageForSelectedScript() const;`
- L66 _private prototype_ `void SelectNextUsageForSelectedScript() const;`
- L68 _private prototype_ `bool CanCreateAssetFromSelectedScript() const;`
- L70 _private prototype_ `void CreateAssetFromSelectedScript() const;`
- L73 _private member_ `TSharedRef<FUICommandList> Commands;`
- L75 _private member_ `bool bCommandsAreSetup;`
- L77 _private member_ `bool bProcessingCommandBindings;`
- L79 _private member_ `UNiagaraScratchPadViewModel* ScratchPadViewModel;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/NiagaraStackCommandContext.h` (Private)


#### class `FNiagaraStackCommandContext`  
`class FNiagaraStackCommandContext : public TSharedFromThis<FNiagaraStackCommandContext>`  
_L12-66_
- inherits: `TSharedFromThis<FNiagaraStackCommandContext>`
- L15 _public prototype_ `FNiagaraStackCommandContext();`
- L17 _public prototype_ `void SetSelectedEntries(const TArray<UNiagaraStackEntry*> InSelectedEntries);`
- L19 _public prototype_ `TSharedRef<FUICommandList> GetCommands();`
- L21 _public prototype_ `bool ProcessCommandBindings(const FKeyEvent& InKeyEvent);`
- L23 _public prototype_ `bool AddEditMenuItems(FMenuBuilder& MenuBuilder);`
- L26 _private prototype_ `void SetupCommands();`
- L28 _private prototype_ `bool CanCutSelectedEntries() const;`
- L30 _private prototype_ `FText GetCanCutSelectedEntriesToolTip() const;`
- L32 _private prototype_ `void CutSelectedEntries() const;`
- L34 _private prototype_ `bool CanCopySelectedEntries() const;`
- L36 _private prototype_ `FText GetCanCopySelectedEntriesToolTip() const;`
- L38 _private prototype_ `void CopySelectedEntries() const;`
- L40 _private prototype_ `bool CanPasteSelectedEntries() const;`
- L42 _private prototype_ `FText GetCanPasteSelectedEntriesToolTip() const;`
- L44 _private prototype_ `void PasteSelectedEntries() const;`
- L46 _private prototype_ `bool CanDeleteSelectedEntries() const;`
- L48 _private prototype_ `FText GetCanDeleteSelectedEntriesToolTip() const;`
- L50 _private prototype_ `void DeleteSelectedEntries() const;`
- L52 _private prototype_ `FText GetCanRenameSelectedEntriesToolTip() const;`
- L54 _private prototype_ `bool CanRenameSelectedEntries() const;`
- L56 _private prototype_ `void RenameSelectedEntries();`
- L59 _private member_ `TSharedRef<FUICommandList> Commands;`
- L61 _private member_ `bool bCommandsAreSetup;`
- L63 _private member_ `bool bProcessingCommandBindings;`
- L65 _private member_ `TArray<UNiagaraStackEntry*> SelectedEntries;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraCurveKeySelector.h` (Private)


#### class `SNiagaraCurveKeySelector`  
`class SNiagaraCurveKeySelector : public SCompoundWidget`  
_L16-60_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SNiagaraCurveKeySelector)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FCurveEditor> InCurveEditor, const TArray<FCurveEditorTreeItemID>& InCurveTreeItemIds, TSharedPtr<SCurveEditorTree> InCurveEditorTree);`
- L25 _private prototype_ `void GetActiveCurveModelAndSelectedKeys(TOptional<FCurveModelID>& OutActiveCurveModelId, TArray<FKeyHandle>& OutSelectedKeyHandles);`
- L33 _private prototype_ `void GetSortedKeyHandlessAndPositionsForModel(FCurveModel& InCurveModel, TArray<FKeyHandlePositionPair>& OutSortedKeyHandlesAndPositions);`
- L34 _private prototype_ `void GetOrderedActiveCurveModelIds(TArray<FCurveModelID>& OutOrderedActiveCurveModelIds);`
- L42 _private prototype_ `void NavigateToAdjacentCurve(ENavigateDirection Direction);`
- L43 _private prototype_ `void NavigateToAdjacentKey(ENavigateDirection Direction);`
- L45 _private prototype_ `FReply ZoomToFitClicked();`
- L46 _private prototype_ `FReply PreviousCurveClicked();`
- L47 _private prototype_ `FReply NextCurveClicked();`
- L48 _private prototype_ `FReply PreviousKeyClicked();`
- L49 _private prototype_ `FReply NextKeyClicked();`
- L51 _private prototype_ `EVisibility GetNextPreviousCurveButtonVisibility() const;`
- L53 _private prototype_ `FReply AddKeyClicked();`
- L54 _private prototype_ `FReply DeleteKeyClicked();`
- L57 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L58 _private member_ `TArray<FCurveEditorTreeItemID> OrderedCurveTreeItemIds;`
- L59 _private member_ `TSharedPtr<SCurveEditorTree> CurveEditorTree;`

#### struct `SNiagaraCurveKeySelector::FKeyHandlePositionPair`  
`struct FKeyHandlePositionPair`  
_L27-31_
- L29 _public member_ `FKeyHandle Handle;`
- L30 _public member_ `FKeyPosition Position;`

#### enum `SNiagaraCurveKeySelector::ENavigateDirection`  
`enum class ENavigateDirection`  
_L36-40_
- L38 _public enumerator_ `Previous`
- L39 _public enumerator_ `Next`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraCurveOverview.h` (Private)


#### class `SNiagaraCurveOverview`  
`class SNiagaraCurveOverview : public SCompoundWidget`  
_L16-44_
- inherits: `SCompoundWidget`
- desc: A curve editor control for curves in a niagara System.
- L19 _public function_ `SLATE_BEGIN_ARGS(SNiagaraCurveOverview)`
- L20 _public prototype_ `SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs, TSharedRef<FNiagaraSystemViewModel> InSystemViewModel);`
- L24 _public prototype_ `~SNiagaraCurveOverview();`
- L27 _private prototype_ `void CreateCurveEditorTreeItemsRecursive(FCurveEditorTreeItemID ParentTreeItemID, const TArray<TSharedRef<FNiagaraCurveSelectionTreeNode>>& CurveSelectionTreeNodes, TArray<FGuid>& LastCurveSelectionTreeNodeIds);`
- L29 _private prototype_ `void RefreshCurveEditorTreeItems();`
- L31 _private prototype_ `void CurveSelectionViewModelRefreshed();`
- L33 _private prototype_ `void CurveSelectionViewModelRequestSelectNode(FGuid NodeIdToSelect);`
- L35 _private prototype_ `void CurveTreeItemDoubleClicked(FCurveEditorTreeItemID TreeItemId);`
- L38 _private member_ `TSharedPtr<FNiagaraSystemViewModel> SystemViewModel;`
- L40 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L41 _private member_ `TSharedPtr<SCurveEditorPanel> CurveEditorPanel;`
- L42 _private member_ `TSharedPtr<SCurveEditorTree> CurveEditorTree;`
- L43 _private member_ `TMap<FGuid, FCurveEditorTreeItemID> CurveTreeNodeIdToTreeItemIdMap;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraCurveThumbnail.h` (Private)


#### class `SNiagaraCurveThumbnail`  
`class SNiagaraCurveThumbnail : public SLeafWidget`  
_L14-33_
- inherits: `SLeafWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(SNiagaraCurveThumbnail) : _Width(16) , _Height(8)`
- L21 _private prototype_ `SLATE_ARGUMENT(float, Width) SLATE_ARGUMENT(float, Height) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FRichCurve& CurveToDisplay);`
- L27 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L28 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L30 _private member_ `TArray<FVector2D> CurvePoints;`
- L31 _private member_ `float Width;`
- L32 _private member_ `float Height;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraEmitterRendererThumbnails.h` (Private)


#### struct `FNiagaraRendererStackEntryObserver`  
`struct FNiagaraRendererStackEntryObserver : public TSharedFromThis<FNiagaraRendererStackEntryObserver>`  
_L14-33_
- inherits: `TSharedFromThis<FNiagaraRendererStackEntryObserver>`
- L17 _public prototype_ `FNiagaraRendererStackEntryObserver();`
- L18 _public prototype_ `~FNiagaraRendererStackEntryObserver();`
- L20 _public prototype_ `void Initialize(TSharedRef<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRendererGroupStructureChanged);`
- L24 _public member_ `FOnRendererGroupStructureChanged OnRenderersChanged;`
- L27 _private prototype_ `void OnRenderGroupStructureChanged(ENiagaraStructureChangedFlags NiagaraStructureChangedFlags) const;`
- L28 _private prototype_ `void OnMaterialCompiled(class UMaterialInterface* MaterialInterface) const;`
- L29 _private prototype_ `void OnStackDataObjectChanged(TArray<UObject*> ChangedObjects, ENiagaraDataObjectChange NiagaraDataObjectChange) const;`
- L32 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModelWeak;`

#### class `SNiagaraEmitterRendererThumbnails`  
`class SNiagaraEmitterRendererThumbnails : public SCompoundWidget`  
_L38-61_
- inherits: `SCompoundWidget`
- L41 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnRendererThumbnailClicked, UNiagaraStackRendererItem* StackRendererItem);`
- L43 _public function_ `SLATE_BEGIN_ARGS(SNiagaraEmitterRendererThumbnails)`
- L45 _public prototype_ `SLATE_EVENT(FOnRendererThumbnailClicked, OnRendererThumbnailClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L51 _private prototype_ `void RefreshThumbnails();`
- L53 _private prototype_ `static void SetupRendererThumbnailTooltip(TSharedPtr<SWidget> InWidget, TSharedPtr<SWidget> InTooltipWidget);`
- L54 _private prototype_ `FReply OnRendererThumbnailClicked(UNiagaraStackRendererItem* StackRendererItem) const;`
- L57 _private member_ `TSharedPtr<SBox> Content;`
- L58 _private member_ `TSharedPtr<FNiagaraRendererStackEntryObserver> RendererObserver;`
- L59 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModelWeak;`
- L60 _private member_ `FOnRendererThumbnailClicked OnRendererThumbnailClickedDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NIAGARAEDITORWIDGETS_API`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRendererGroupStructureChanged);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnRendererThumbnailClicked, UNiagaraStackRendererItem* StackRendererItem);`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraOverviewGraph.h` (Private)


#### class `SNiagaraOverviewGraph`  
`class SNiagaraOverviewGraph : public SCompoundWidget`  
_L15-74_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SNiagaraOverviewGraph)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FNiagaraOverviewGraphViewModel> InViewModel, const FAssetData& InEditedAsset);`
- L23 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L26 _private prototype_ `void ViewModelSelectionChanged();`
- L28 _private prototype_ `void GraphSelectionChanged(const TSet<UObject*>& SelectedNodes);`
- L30 _private prototype_ `void PreClose();`
- L32 _private prototype_ `void OpenAddEmitterMenu();`
- L33 _private prototype_ `bool CanAddEmitters() const;`
- L36 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L38 _private prototype_ `void OnCreateEmptyEmitter();`
- L39 _private prototype_ `bool CanCreateStatelessEmitter() const;`
- L40 _private prototype_ `FText GetCreateStatelessEmitterTooltip() const;`
- L41 _private prototype_ `void OnCreateStatelessEmitter();`
- L42 _private prototype_ `void OnCreateComment();`
- L43 _private prototype_ `void OnClearIsolated();`
- L45 _private prototype_ `bool OnVerifyNodeTitle(const FText& NewText, UEdGraphNode* Node, FText& OutErrorMessage) const;`
- L46 _private prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L49 _private prototype_ `void NodesPasted(const TSet<UEdGraphNode*>& PastedNodes);` — Called when nodes are pasted in the System Overview View Model.
- L52 _private prototype_ `void OnNodesCreated(const FEdGraphEditAction& Action);` — A callback function to position nodes after they've been created
- L55 _private prototype_ `void PositionPastedNodes(const TSet<UEdGraphNode*>& PastedNodes);` — Sets the position on a group of newly pasted nodes.
- L57 _private prototype_ `void ZoomToFit();`
- L58 _private prototype_ `void ZoomToFitAll();`
- L60 _private prototype_ `void OnAlignTop();`
- L61 _private prototype_ `void OnAlignMiddle();`
- L62 _private prototype_ `void OnAlignBottom();`
- L64 _private prototype_ `void OnDistributeNodesH();`
- L65 _private prototype_ `void OnDistributeNodesV();`
- L67 _private member_ `TSharedPtr<FNiagaraOverviewGraphViewModel> ViewModel;`
- L68 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L70 _private member_ `bool bUpdatingViewModelSelectionFromGraph;`
- L71 _private member_ `bool bUpdatingGraphSelectionFromViewModel;`
- L73 _private member_ `int32 ZoomToFitFrameDelay;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraOverviewGraphTitleBar.h` (Private)


#### class `SNiagaraOverviewGraphTitleBar`  
`class SNiagaraOverviewGraphTitleBar : public SCompoundWidget`  
_L17-63_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_BEGIN_ARGS(SNiagaraOverviewGraphTitleBar) : _OverviewGraph(nullptr)`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FNiagaraSystemViewModel> InSystemViewModel, const FAssetData& InEditedAsset);`
- L29 _public prototype_ `void RebuildWidget();`
- L32 _private member_ `TWeakPtr<FNiagaraSystemViewModel> SystemViewModel;`
- L33 _private member_ `bool bScalabilityModeActive = false;`
- L34 _private member_ `TSharedPtr<SVerticalBox> ContainerWidget;`
- L35 _private member_ `TWeakPtr<SNiagaraOverviewGraph> OverviewGraph;`
- L37 _private prototype_ `void OnUpdateScalabilityMode(bool bActive);`
- L39 _private prototype_ `FText GetEmitterSubheaderText() const;`
- L40 _private prototype_ `EVisibility GetEmitterSubheaderVisibility() const;`
- L41 _private prototype_ `FLinearColor GetEmitterSubheaderColor() const;`
- L43 _private prototype_ `FText GetSystemSubheaderText() const;`
- L44 _private prototype_ `EVisibility GetSystemSubheaderVisibility() const;`
- L45 _private prototype_ `FLinearColor GetSystemSubheaderColor() const;`
- L47 _private prototype_ `EVisibility GetSystemCompileModeHeaderVisibility() const;`
- L48 _private prototype_ `FText GetSystemCompileModeHeaderText() const;`
- L49 _private prototype_ `FLinearColor GetSystemCompileModeHeaderColor() const;`
- L51 _private prototype_ `FLinearColor GetStatelessInfoHeaderColor() const;`
- L52 _private prototype_ `EVisibility GetStatelessInfoVisibility() const;`
- L53 _private prototype_ `FText GetStatelessInfoText() const;`
- L55 _private prototype_ `int32 GetEmitterAffectedAssets() const;`
- L56 _private prototype_ `bool IsUsingDeprecatedEmitter() const;`
- L57 _private prototype_ `void ResetAssetCount(const FAssetData& InAssetData);`
- L58 _private prototype_ `void AddAssetListeners();`
- L59 _private prototype_ `void ClearListeners();`
- L61 _private member_ `mutable TOptional<int32> EmitterAffectedAssets;`
- L62 _private member_ `FAssetData EditedAsset;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraOverviewInlineParameterBox.h` (Private)


#### class `SNiagaraOverviewInlineParameterBox`  
`class SNiagaraOverviewInlineParameterBox : public SCompoundWidget`  
_L20-63_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SNiagaraOverviewInlineParameterBox)`
- L28 _public prototype_ `SLATE_END_ARGS();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackModuleItem& InStackModuleItem);`
- L36 _private prototype_ `FReply NavigateToStack(TWeakObjectPtr<UNiagaraStackFunctionInput> FunctionInput);` — Selects the module item in the stack and searches for the function input
- L37 _private prototype_ `void ConstructChildren();`
- L38 _private prototype_ `TArray<TSharedRef<SWidget>> GenerateParameterWidgets();`
- L39 _private prototype_ `TSharedRef<SWidget> GenerateParameterWidgetFromLocalValue(UNiagaraStackFunctionInput* FunctionInput);`
- L40 _private prototype_ `TSharedRef<SWidget> GenerateParameterWidgetFromDynamicInput(UNiagaraStackFunctionInput* FunctionInput);`
- L41 _private prototype_ `TSharedRef<SWidget> GenerateParameterWidgetFromDataInterface(UNiagaraStackFunctionInput* FunctionInput);`
- L44 _private prototype_ `TWeakObjectPtr<UNiagaraStackFunctionInput> FindSubstituteEntry(const UNiagaraStackFunctionInput* Input);` — We build a substitute map of entries that we want to
- L46 _private prototype_ `void OnModuleItemStructureChanged(ENiagaraStructureChangedFlags);`
- L49 _private prototype_ `FLinearColor GetTypeColor(UNiagaraStackFunctionInput* FunctionInput) const;` — Gets the color based on type.
- L52 _private prototype_ `FLinearColor DetermineBackgroundColor(UNiagaraStackFunctionInput* FunctionInput) const;` — Determines the color for a function input. This is usually based on type, but can be overridden and handles special cases.
- L55 _private member_ `TWeakObjectPtr<UNiagaraStackModuleItem> ModuleItem;` — The module item whose parameters this box is representing
- L57 _private member_ `TSharedPtr<SScrollBox> Container;`
- L60 _private member_ `TArray<TWeakObjectPtr<UNiagaraStackFunctionInput>> BoundFunctionInputs;` — We keep track of the function inputs we are observing through this parameter box so we can unbind the delegates later
- L62 _private member_ `TArray<FSlateImageBrush> ImageBrushes;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraOverviewStack.h` (Private)


#### class `SNiagaraOverviewStack`  
`class SNiagaraOverviewStack : public SCompoundWidget`  
_L21-108_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SNiagaraOverviewStack) : _AllowedClasses({UNiagaraStackItem::StaticClass(), UNiagaraStackItemGroup::StaticClass()})`
- L27 _public prototype_ `SLATE_ARGUMENT(TArray<UClass*>, AllowedClasses) SLATE_END_ARGS();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackViewModel& InStackViewModel, UNiagaraSystemSelectionViewModel& InOverviewSelectionViewModel);`
- L34 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L36 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L38 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L40 _public prototype_ `static EVisibility GetIssueIconVisibility(UNiagaraStackEntry* StackEntry);`
- L41 _public prototype_ `static EVisibility GetUsageIconVisibility(UNiagaraStackEntry* StackEntry);`
- L42 _public prototype_ `static const FSlateBrush* GetUsageIcon(UNiagaraStackEntry* StackEntry);`
- L43 _public prototype_ `static int32 GetUsageIconWidth(UNiagaraStackEntry* StackEntry);`
- L44 _public prototype_ `static int32 GetUsageIconHeight(UNiagaraStackEntry* StackEntry);`
- L45 _public prototype_ `static FText GetUsageTooltip(UNiagaraStackEntry* StackEntry);`
- L48 _private prototype_ `void AddEntriesRecursive(UNiagaraStackEntry& EntryToAdd, TArray<UNiagaraStackEntry*>& EntryList, const TArray<UClass*>& AcceptableClasses, TArray<UNiagaraStackEntry*> ParentChain);`
- L50 _private prototype_ `void RefreshEntryList();`
- L52 _private prototype_ `void EntryExpansionChanged();`
- L53 _private prototype_ `void EntryExpansionInOverviewChanged();`
- L54 _private prototype_ `void EntryStructureChanged(ENiagaraStructureChangedFlags Flags);`
- L56 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForEntry(UNiagaraStackEntry* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L58 _private prototype_ `EVisibility GetEnabledCheckBoxVisibility(UNiagaraStackItem* Item) const;`
- L60 _private prototype_ `EVisibility GetShouldDebugDrawStatusVisibility(UNiagaraStackItem* Item) const;`
- L62 _private prototype_ `bool IsModuleDebugDrawEnabled(UNiagaraStackItem* Item) const;`
- L64 _private prototype_ `const FSlateBrush* GetDebugIconBrush(UNiagaraStackItem* Item) const;`
- L66 _private prototype_ `FReply ToggleModuleDebugDraw(UNiagaraStackItem* Item);`
- L68 _private prototype_ `void OnSelectionChanged(UNiagaraStackEntry* InNewSelection, ESelectInfo::Type SelectInfo);`
- L70 _private prototype_ `void SystemSelectionChanged();`
- L72 _private prototype_ `void UpdateCommandContextSelection();`
- L74 _private prototype_ `FReply OnRowDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, TWeakObjectPtr<UNiagaraStackEntry> InStackEntryWeak);`
- L76 _private prototype_ `void OnRowDragLeave(const FDragDropEvent& InDragDropEvent);`
- L78 _private prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry);`
- L80 _private prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry);`
- L82 _private prototype_ `void OnItemGroupEnabledStateChanged(ECheckBoxState InCheckState, UNiagaraStackItemGroup* Group);`
- L83 _private prototype_ `ECheckBoxState ItemGroupCheckEnabledStatus(UNiagaraStackItemGroup* Group) const;`
- L84 _private prototype_ `bool GetItemGroupEnabledCheckboxEnabled(UNiagaraStackItemGroup* Group) const;`
- L86 _private prototype_ `FText GetItemGroupDeleteButtonToolTip(UNiagaraStackItemGroup* Group) const;`
- L87 _private prototype_ `bool GetItemGroupDeleteButtonIsEnabled(UNiagaraStackItemGroup* Group) const;`
- L88 _private prototype_ `EVisibility GetItemGroupDeleteButtonVisibility(UNiagaraStackItemGroup* Group) const;`
- L89 _private prototype_ `FReply OnItemGroupDeleteClicked(UNiagaraStackItemGroup* Group);`
- L92 _private member_ `UNiagaraStackViewModel* StackViewModel;`
- L93 _private member_ `UNiagaraSystemSelectionViewModel* OverviewSelectionViewModel;`
- L95 _private member_ `TArray<UNiagaraStackEntry*> FlattenedEntryList;`
- L96 _private member_ `TMap<FObjectKey, TArray<UNiagaraStackEntry*>> EntryObjectKeyToParentChain;`
- L97 _private member_ `TSharedPtr<SListView<UNiagaraStackEntry*>> EntryListView;`
- L99 _private member_ `TArray<TWeakObjectPtr<UNiagaraStackEntry>> PreviousSelection;`
- L101 _private member_ `TSharedPtr<FNiagaraStackCommandContext> StackCommandContext;`
- L103 _private member_ `TArray<UClass*> AllowedClasses;`
- L105 _private member_ `bool bRefreshEntryListPending;`
- L106 _private member_ `bool bUpdatingOverviewSelectionFromStackSelection;`
- L107 _private member_ `bool bUpdatingStackSelectionFromOverviewSelection;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraOverviewStackNode.h` (Private)


#### class `SNiagaraOverviewStackNode`  
`class SNiagaraOverviewStackNode : public SGraphNode`  
_L18-148_
- inherits: `SGraphNode`
- L27 _public function_ `SLATE_BEGIN_ARGS(SNiagaraOverviewStackNode)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraOverviewNode* InNode);`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L33 _public function_ `virtual bool ShouldAllowCulling() const override`
- L37 _protected prototype_ `void BindEditorDataDelegates();`
- L38 _protected prototype_ `void UnbindEditorDataDelegates() const;`
- L40 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;`
- L41 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L42 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L43 _protected prototype_ `TSharedRef<SWidget> CreateTopContentBar();`
- L45 _protected prototype_ `TSharedRef<SWidget> CreateTitleWidget_Default(TSharedPtr<SNodeTitle> NodeTitle);`
- L46 _protected prototype_ `TSharedRef<SWidget> CreateTitleRightWidget_Default();`
- L47 _protected prototype_ `TSharedRef<SWidget> CreateNodeContentArea_Default();`
- L48 _protected prototype_ `TSharedRef<SWidget> CreateTopContentBar_Default();`
- L50 _protected prototype_ `TSharedRef<SWidget> CreateTitleWidget_Summary(TSharedPtr<SNodeTitle> NodeTitle);`
- L51 _protected prototype_ `TSharedRef<SWidget> CreateTitleRightWidget_Summary();`
- L52 _protected prototype_ `TSharedRef<SWidget> CreateNodeContentArea_Summary();`
- L53 _protected prototype_ `TSharedRef<SWidget> CreateTopContentBar_Summary();`
- L55 _protected function_ `virtual bool IsHidingPinWidgets() const override`
- L57 _protected prototype_ `bool UseLowDetailNodeContent() const;`
- L58 _protected prototype_ `FVector2D GetLowDetailDesiredSize() const;`
- L59 _protected prototype_ `FOptionalSize GetLowDetailDesiredWidth() const;`
- L60 _protected prototype_ `FOptionalSize GetLowDetailDesiredHeight() const;`
- L61 _protected prototype_ `FText GetLowDetailNodeTitle() const;`
- L63 _protected prototype_ `TSharedRef<SWidget> CreateEnabledCheckbox();`
- L64 _protected prototype_ `TSharedRef<SButton> CreateIsolateButton();`
- L65 _protected prototype_ `TSharedRef<SButton> CreateBoundsButton();`
- L66 _protected prototype_ `TSharedRef<SWidget> CreateEmitterThumbnail();`
- L67 _protected prototype_ `TSharedRef<SWidget> CreateEmitterRendererThumbnails();`
- L68 _protected prototype_ `TSharedRef<SWidget> CreateSummaryViewToggle();`
- L69 _protected prototype_ `TSharedRef<SWidget> CreateLocalSpaceToggle();`
- L70 _protected prototype_ `TSharedRef<SButton> CreateCaptureThumbnailButton();`
- L71 _protected prototype_ `TSharedRef<SWidget> CreateOpenParentButton();`
- L72 _protected prototype_ `TSharedRef<SWidget> CreateVersionSelectorButton();`
- L73 _protected prototype_ `TSharedRef<SWidget> CreateScalabilityControls();`
- L74 _protected prototype_ `TSharedRef<SWidget> CreateSimTargetToggle();`
- L75 _protected prototype_ `TSharedRef<SWidget> CreateDeterminismToggle();`
- L76 _protected prototype_ `TSharedRef<SWidget> CreatePropertiesButton();`
- L78 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L80 _private prototype_ `void RefreshEmitterThumbnailPreview();`
- L82 _private prototype_ `virtual TOptional<ETextOverflowPolicy> GetNameOverflowPolicy() const override;`
- L83 _private prototype_ `EVisibility GetIssueIconVisibility() const;`
- L85 _private prototype_ `EVisibility GetEnabledCheckBoxVisibility() const;`
- L86 _private prototype_ `ECheckBoxState GetEnabledCheckState() const;`
- L87 _private prototype_ `const FSlateBrush* GetEnabledImage() const;`
- L88 _private prototype_ `void OnEnabledCheckStateChanged(ECheckBoxState InCheckState);`
- L89 _private prototype_ `EVisibility GetShouldShowSummaryControls() const;`
- L90 _private prototype_ `FReply OnCaptureThumbnailButtonClicked();`
- L91 _private prototype_ `FReply OnRendererThumbnailClicked(class UNiagaraStackRendererItem* StackRendererItem);`
- L92 _private prototype_ `FReply OnPropertiesButtonClicked() const;`
- L94 _private prototype_ `FText GetToggleIsolateToolTip() const;`
- L95 _private prototype_ `FReply OnToggleIsolateButtonClicked();`
- L96 _private prototype_ `EVisibility GetToggleIsolateVisibility() const;`
- L97 _private prototype_ `const FSlateBrush* GetToggleIsolateImage() const;`
- L98 _private prototype_ `FSlateColor GetToggleIsolateImageColor() const;`
- L100 _private prototype_ `FText GetToggleBoundsToolTip() const;`
- L101 _private prototype_ `FReply OnToggleBoundsButtonClicked();`
- L102 _private prototype_ `EVisibility GetToggleBoundsVisibility() const;`
- L103 _private prototype_ `const FSlateBrush* GetToggleBoundsImage() const;`
- L104 _private prototype_ `FSlateColor GetToggleBoundsImageColor() const;`
- L106 _private prototype_ `EVisibility GetScalabilityIndicatorVisibility() const;`
- L107 _private prototype_ `FSlateColor GetScalabilityTintAlpha() const;`
- L108 _private prototype_ `void OnScalabilityModeChanged(bool bActive);`
- L109 _private prototype_ `EVisibility ShowExcludedOverlay() const;`
- L110 _private prototype_ `float GetGraphZoomDistanceAlphaMultiplier() const;`
- L112 _private prototype_ `FText GetSpawnCountScaleText() const;`
- L113 _private prototype_ `FText GetSpawnCountScaleTooltip() const;`
- L114 _private prototype_ `EVisibility GetSpawnCountScaleTextVisibility() const;`
- L115 _private prototype_ `ECheckBoxState IsScalabilityModeActive() const;`
- L116 _private prototype_ `void OnScalabilityModeStateChanged(ECheckBoxState CheckBoxState);`
- L118 _private prototype_ `FReply OnCycleThroughIssues();`
- L119 _private prototype_ `FReply OpenParentEmitter();`
- L120 _private prototype_ `FText OpenParentEmitterTooltip() const;`
- L121 _private prototype_ `EVisibility GetOpenParentEmitterVisibility() const;`
- L122 _private prototype_ `EVisibility GetVersionSelectorVisibility() const;`
- L123 _private prototype_ `FSlateColor GetVersionSelectorColor() const;`
- L124 _private prototype_ `TSharedRef<SWidget> GetVersionSelectorDropdownMenu();`
- L125 _private prototype_ `void SwitchToVersion(FNiagaraAssetVersion Version);`
- L127 _private member_ `UNiagaraOverviewNode* OverviewStackNode = nullptr;`
- L128 _private member_ `UNiagaraStackViewModel* StackViewModel = nullptr;`
- L129 _private member_ `UNiagaraSystemSelectionViewModel* OverviewSelectionViewModel = nullptr;`
- L130 _private member_ `TWeakObjectPtr<UNiagaraSystemScalabilityViewModel> ScalabilityViewModel;`
- L131 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModelWeak;`
- L132 _private member_ `TSharedPtr<SOverlay> ScalabilityWrapper;`
- L133 _private member_ `TSharedPtr<SInvalidationPanel> ContentAreaWidget;`
- L135 _private member_ `TArray<UNiagaraStackEntry*> RendererPreviewStackEntries;`
- L136 _private member_ `int32 CurrentIssueIndex = 0;`
- L137 _private member_ `bool bScalabilityModeActive = false;`
- L139 _private member_ `EDisplayMode DisplayMode = EDisplayMode::Default;`
- L142 _private member_ `FVector2D LastHighDetailSize = FVector2D::ZeroVector;` — Cached size from when we last drew at high detail
- L143 _private member_ `int32 GeometryTickForSize = 3;`
- L144 _private member_ `mutable TPair<FString, FText> LowDetailTitleCache;`
- L146 _private member_ `TSharedPtr<SBox> ThumbnailContainer;`
- L147 _private member_ `TSharedPtr<FAssetThumbnail> PreviewThumbnail;`

#### enum `SNiagaraOverviewStackNode::EDisplayMode`  
`enum class EDisplayMode : uint8`  
_L21-25_
- L23 _public enumerator_ `Default`
- L24 _public enumerator_ `Summary`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraParameterDropTarget.h` (Private)


#### class `SNiagaraParameterDropTarget`  
`class SNiagaraParameterDropTarget : public SDropTarget`  
_L18-41_
- inherits: `SDropTarget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNiagaraParameterDropTarget) : _DropTargetArgs(SDropTarget::FArguments()) , _TargetParameter(TOptional<FNiagaraVariable>()) , _TypeToTestAgainst(TOptional<FNiagaraTypeDefinition>()) , _ExecutionCategory(TOptional<FName>())`
- L27 _public prototype_ `SLATE_ARGUMENT(SDropTarget::FArguments, DropTargetArgs) SLATE_ARGUMENT(TOptional<FNiagaraVariable>, TargetParameter) SLATE_ARGUMENT(TOptional<FNiagaraTypeDefinition>, TypeToTestAgainst) SLATE_ARGUMENT(TOptional<FName>, ExecutionCategory) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L36 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L38 _private member_ `TOptional<FName> ExecutionCategory;`
- L39 _private member_ `TOptional<FNiagaraVariable> TargetParameter;`
- L40 _private member_ `TOptional<FNiagaraTypeDefinition> TypeToTestAgainst;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API NIAGARAEDITORWIDGETS_API`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraScalabilityPreviewSettings.h` (Private)


#### class `SNiagaraScalabilityPreviewSettings`  
`class SNiagaraScalabilityPreviewSettings : public SCompoundWidget`  
_L15-52_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SNiagaraScalabilityPreviewSettings)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraSystemScalabilityViewModel& InScalabilityViewModel);`
- L26 _private prototype_ `TSharedRef<SWidget> CreatePreviewQualityLevelWidgets();`
- L27 _private prototype_ `TSharedRef<SWidget> CreatePreviewPlatformWidgets();`
- L29 _private prototype_ `ECheckBoxState IsQLChecked(int32 QualityLevel) const;`
- L30 _private prototype_ `void QLCheckStateChanged(ECheckBoxState CheckState, int32 QualityLevel);`
- L31 _private prototype_ `FSlateColor GetQualityLevelButtonTextColor(int32 QualityLevel) const;`
- L32 _private prototype_ `const FSlateBrush* GetActivePreviewPlatformImage() const;`
- L33 _private prototype_ `FText GetActivePreviewPlatformName() const;`
- L34 _private prototype_ `FText GetQualityButtonTooltip(int32 QualityLevel) const;`
- L36 _private prototype_ `void CreateDeviceProfileTree();`
- L37 _private prototype_ `TSharedRef<SWidget> GenerateDeviceProfileTreeWidget();`
- L38 _private prototype_ `TSharedRef<ITableRow> OnGenerateDeviceProfileTreeRow(TSharedPtr<FNiagaraDeviceProfileViewModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L39 _private prototype_ `void OnGetDeviceProfileTreeChildren(TSharedPtr<FNiagaraDeviceProfileViewModel> InItem, TArray< TSharedPtr<FNiagaraDeviceProfileViewModel> >& OutChildren);`
- L40 _private prototype_ `FReply TogglePlatformMenuOpen();`
- L42 _private prototype_ `FReply OnProfileMenuButtonClicked(TSharedPtr<FNiagaraDeviceProfileViewModel> InItem);`
- L43 _private prototype_ `FReply OnResetPreviewPlatformClicked();`
- L45 _private member_ `TArray<TSharedPtr<FNiagaraDeviceProfileViewModel>> FullDeviceProfileTree;`
- L46 _private member_ `TArray<TArray<TSharedPtr<FNiagaraDeviceProfileViewModel>>> FilteredDeviceProfileTrees;`
- L47 _private member_ `TSharedPtr<STreeView<TSharedPtr<FNiagaraDeviceProfileViewModel>>> DeviceProfileTreeWidget;`
- L50 _private member_ `TWeakObjectPtr<UNiagaraSystemScalabilityViewModel> ScalabilityViewModel;`
- L51 _private member_ `TSharedPtr<SMenuAnchor> PlatformMenuAnchor;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraScratchPadScriptManager.h` (Private)


#### class `SNiagaraScratchPadScriptManager`  
`class SNiagaraScratchPadScriptManager : public SCompoundWidget`  
_L15-51_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SNiagaraScratchPadScriptManager)`
- L18 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraScratchPadViewModel* InViewModel);`
- L23 _private prototype_ `void ObjectSelectionChanged();`
- L25 _private prototype_ `TSharedRef<SWidget> ConstructScriptSelector();`
- L27 _private prototype_ `TSharedRef<SWidget> ConstructParameterPanel();`
- L29 _private prototype_ `TSharedRef<SWidget> ConstructScriptEditor();`
- L31 _private prototype_ `TSharedRef<SWidget> ConstructSelectionEditor();`
- L33 _private prototype_ `EVisibility GetObjectSelectionSubHeaderTextVisibility() const;`
- L35 _private prototype_ `FText GetObjectSelectionSubHeaderText() const;`
- L37 _private prototype_ `EVisibility GetObjectSelectionNoSelectionTextVisibility() const;`
- L38 _private member_ `static FName ScriptSelectorName;`
- L39 _private member_ `static FName ScriptParameterPanelName;`
- L40 _private member_ `static FName ScriptEditorName;`
- L41 _private member_ `static FName SelectionEditorName;`
- L42 _private member_ `static FName WideLayoutName;`
- L43 _private member_ `static FName NarrowLayoutName;`
- L45 _private member_ `FText ObjectSelectionSubHeaderText;`
- L47 _private member_ `TWeakObjectPtr<UNiagaraScratchPadViewModel> ViewModel;`
- L49 _private member_ `TSharedPtr<FNiagaraScratchPadCommandContext> CommandContext;`

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef SItemSelector<ENiagaraScriptUsage, TSharedRef<FNiagaraScratchPadScriptViewModel>> SNiagaraScriptViewModelSelector;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraStack.h` (Private)


#### class `SNiagaraStack`  
`class SNiagaraStack : public SCompoundWidget`  
_L21-145_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStack)`
- L27 _public prototype_ `SLATE_END_ARGS();`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackViewModel* InStackViewModel);`
- L31 _public prototype_ `TSharedPtr<SWidget> GenerateStackMenu(TWeakPtr<UNiagaraStackViewModel::FTopLevelViewModel> TopLevelViewModelWeak);`
- L51 _private prototype_ `void SynchronizeTreeExpansion();`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForStackItem(UNiagaraStackEntry* Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L55 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForTopLevelObject(TSharedRef<UNiagaraStackViewModel::FTopLevelViewModel> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L59 _private prototype_ `TSharedRef<SNiagaraStackTableRow> ConstructContainerForItem(UNiagaraStackEntry* Item);`
- L61 _private prototype_ `FRowWidgets ConstructNameAndValueWidgetsForItem(UNiagaraStackEntry* Item, TSharedRef<SNiagaraStackTableRow> Container);`
- L63 _private prototype_ `void ReconstructNameAndValueWidgetsForItem(UNiagaraStackEntry* Item);`
- L65 _private prototype_ `void OnGetChildren(UNiagaraStackEntry* Item, TArray<UNiagaraStackEntry*>& Children);`
- L67 _private prototype_ `void StackTreeScrolled(double ScrollValue);`
- L69 _private prototype_ `void StackTreeSelectionChanged(UNiagaraStackEntry* InNewSelection, ESelectInfo::Type SelectInfo);`
- L71 _private prototype_ `float GetNameColumnWidth() const;`
- L72 _private prototype_ `float GetContentColumnWidth() const;`
- L74 _private prototype_ `void OnNameColumnWidthChanged(float Width);`
- L75 _private prototype_ `void OnContentColumnWidthChanged(float Width);`
- L77 _private prototype_ `void OnStackExpansionChanged();`
- L78 _private prototype_ `void StackStructureChanged(ENiagaraStructureChangedFlags Info);`
- L80 _private prototype_ `EVisibility GetVisibilityForItem(UNiagaraStackEntry* Item) const;`
- L83 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L84 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L86 _private prototype_ `TSharedRef<SWidget> ConstructHeaderWidget();`
- L89 _private prototype_ `void UpdateSearchTextFromExternal(FText NewSearchText);`
- L90 _private prototype_ `void OnSearchTextChanged(const FText& SearchText);`
- L91 _private prototype_ `FReply ScrollToNextMatch();`
- L92 _private prototype_ `FReply ScrollToPreviousMatch();`
- L93 _private prototype_ `TOptional<SSearchBox::FSearchResultData> GetSearchResultData() const;`
- L94 _private prototype_ `bool GetIsSearching() const;`
- L95 _private prototype_ `void OnSearchBoxTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L96 _private prototype_ `void OnSearchBoxSearch(SSearchBox::SearchDirection Direction);`
- L97 _private prototype_ `FSlateColor GetTextColorForItem(UNiagaraStackEntry* Item) const;`
- L98 _private prototype_ `void ScrollFocusedEntryIntoView();`
- L99 _private prototype_ `void AddSearchScrollOffset(int NumberOfSteps);`
- L100 _private prototype_ `void OnStackSearchComplete(const FNiagaraStackSearchConfig& SearchConfig);`
- L101 _private prototype_ `void ExpandSearchResults();`
- L102 _private prototype_ `bool IsEntryFocusedInSearch(UNiagaraStackEntry* Entry) const;`
- L104 _private prototype_ `void SelectStackEntry(UNiagaraStackEntry* StackEntry, FNiagaraStackEntrySelectionConfig Config);`
- L107 _private prototype_ `void ShowEmitterInContentBrowser(TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModelWeak);` — Inline menu commands
- L108 _private prototype_ `void NavigateTo(UNiagaraStackEntry* Item);`
- L109 _private prototype_ `void CollapseAll();`
- L111 _private prototype_ `TSharedRef<SWidget> GetViewOptionsMenu() const;`
- L114 _private prototype_ `FReply OnRowDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, UNiagaraStackEntry* InStackEntry);` — Drag/Drop
- L116 _private prototype_ `void OnRowDragLeave(FDragDropEvent const& InDragDropEvent);`
- L118 _private prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry);`
- L120 _private prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UNiagaraStackEntry* InTargetEntry);`
- L122 _private prototype_ `EVisibility GetIssueIconVisibility() const;`
- L124 _private prototype_ `FReply OnCycleThroughSystemIssues(TSharedPtr<FNiagaraSystemViewModel> SystemViewModel);`
- L125 _private prototype_ `void OnCycleThroughIssues();`
- L127 _private prototype_ `const FSlateBrush* GetViewOptionsBadgeIcon() const;`
- L129 _private member_ `UNiagaraStackViewModel* StackViewModel;`
- L131 _private member_ `TSharedPtr<STreeView<UNiagaraStackEntry*>> StackTree;`
- L133 _private member_ `TSharedPtr<SListView<TSharedRef<UNiagaraStackViewModel::FTopLevelViewModel>>> HeaderList;`
- L135 _private member_ `float NameColumnWidth;`
- L137 _private member_ `float ContentColumnWidth;`
- L140 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L142 _private member_ `TSharedPtr<FNiagaraStackCommandContext> StackCommandContext;`
- L144 _private member_ `bool bSynchronizeExpansionPending;`

#### struct `SNiagaraStack::FRowWidgets`  
`struct FRowWidgets`  
_L34-49_
- L36 _public function_ `FRowWidgets(TSharedRef<SWidget> InNameWidget, TSharedRef<SWidget> InValueWidget) : NameWidget(InNameWidget) , ValueWidget(InValueWidget)`
- L42 _public function_ `FRowWidgets(TSharedRef<SWidget> InWholeRowWidget) : NameWidget(InWholeRowWidget)`
- L47 _public member_ `TSharedRef<SWidget> NameWidget;`
- L48 _public member_ `TSharedPtr<SWidget> ValueWidget;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraStackEntryWidget.h` (Private)


#### class `SNiagaraStackEntryWidget`  
`class SNiagaraStackEntryWidget : public SCompoundWidget`  
_L17-30_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `FReply ExpandEntry();`
- L22 _public prototype_ `FSlateColor GetTextColorForSearch(FSlateColor DefaultColor) const;`
- L25 _protected prototype_ `bool IsCurrentSearchMatch() const;`
- L28 _protected member_ `UNiagaraStackViewModel* StackViewModel;`
- L29 _protected member_ `UNiagaraStackEntry* StackEntryItem;`

#### class `SNiagaraStackDisplayName`  
`class SNiagaraStackDisplayName : public SNiagaraStackEntryWidget`  
_L32-87_
- inherits: `SNiagaraStackEntryWidget`
- L35 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackDisplayName) : _NameStyle(&FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText")) , _EditableNameStyle(&FAppStyle::Get().GetWidgetStyle<FInlineEditableTextBlockStyle>("InlineEditableTextBlockStyle")) , _OriginalNameStyle(&FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))`
- L42 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, NameStyle) SLATE_STYLE_ARGUMENT(FInlineEditableTextBlockStyle, EditableNameStyle) SLATE_STYLE_ARGUMENT(FTextBlockStyle, OriginalNameStyle) SLATE_END_ARGS();`
- L47 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackEntry& InStackEntry, UNiagaraStackViewModel& InStackViewModel);`
- L49 _public prototype_ `~SNiagaraStackDisplayName();`
- L51 _public prototype_ `void StartRename();`
- L54 _private prototype_ `void OnEndRename();`
- L56 _private prototype_ `TSharedRef<SWidget> ConstructChildren();`
- L58 _private prototype_ `FText GetTopLevelDisplayName(TWeakPtr<UNiagaraStackViewModel::FTopLevelViewModel> TopLevelViewModelWeak) const;`
- L60 _private prototype_ `void StackViewModelStructureChanged(ENiagaraStructureChangedFlags Flags);`
- L62 _private prototype_ `void StackEntryItemAlternateNameChanged();`
- L64 _private prototype_ `FText GetEntryDisplayName() const;`
- L66 _private prototype_ `FText GetOriginalName() const;`
- L68 _private prototype_ `FText GetEntryToolTipText() const;`
- L70 _private prototype_ `bool GetEntryIsEnabled() const;`
- L72 _private prototype_ `void EntryNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L75 _private member_ `const FTextBlockStyle* NameStyle;`
- L76 _private member_ `const FInlineEditableTextBlockStyle* EditableNameStyle;`
- L77 _private member_ `const FTextBlockStyle* OriginalNameStyle;`
- L79 _private member_ `TSharedPtr<SBox> Container;`
- L81 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextBlock;`
- L82 _private member_ `FOnTextCommitted OnRenameCommitted;`
- L84 _private member_ `mutable FText TopLevelDisplayNameCache;`
- L85 _private member_ `mutable FText TopLevelDisplayNameFormattedCache;`
- L86 _private member_ `int32 TopLevelViewModelCountAtLastConstruction;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraStackNote.h` (Private)


#### class `SNiagaraStackInlineNote`  
`class SNiagaraStackInlineNote : public SCompoundWidget`  
_L14-37_
- inherits: `SCompoundWidget`
- desc: A possibly interactable widget showing a note. On hover, summons the note as a tooltip. On clicked, toggles between inline & full display
- L17 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackInlineNote) : _bInteractable(true)`
- L22 _public prototype_ `SLATE_ARGUMENT(bool, bInteractable) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackEntry* InStackEntry);` — If true, a button will be added. If false, it will be a simple image.
- L27 _public prototype_ `void UpdateTooltip();`
- L29 _private prototype_ `FReply OnClicked() const;`
- L31 _private prototype_ `FSlateColor GetStackNoteColor() const;`
- L33 _private prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L35 _private member_ `TWeakObjectPtr<UNiagaraStackEntry> StackEntry;`
- L36 _private member_ `bool bInteractable = true;`

#### class `SNiagaraStackNote`  
`class SNiagaraStackNote : public SCompoundWidget`  
_L40-96_
- inherits: `SCompoundWidget`
- desc: The full stack note widget displayed in the stack. Features editable title, message & toggle inline display button.
- L43 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackNote) : _bShowEditTextButtons(true)`
- L46 _public prototype_ `SLATE_ATTRIBUTE(bool, bShowEditTextButtons) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackNote& StackNote);`
- L52 _public prototype_ `void Rebuild();`
- L54 _public prototype_ `void FillRowContextMenu(FMenuBuilder& MenuBuilder);`
- L56 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L58 _private prototype_ `TOptional<FNiagaraStackNoteData> GetStackNoteData() const;`
- L60 _private prototype_ `void EditHeaderText() const;`
- L61 _private prototype_ `void EditBodyText() const;`
- L63 _private prototype_ `void CommitStackNoteHeaderUpdate(const FText& Text, ETextCommit::Type Arg);`
- L64 _private prototype_ `void CommitStackNoteBodyUpdate(const FText& Text, ETextCommit::Type Arg);`
- L66 _private prototype_ `void ToggleInlineDisplay() const;`
- L67 _private prototype_ `void DeleteStackNote() const;`
- L69 _private prototype_ `FText GetStackNoteHeader() const;`
- L70 _private prototype_ `FText GetStackNoteBody() const;`
- L71 _private prototype_ `FLinearColor GetStackNoteColor() const;`
- L72 _private prototype_ `FSlateColor GetSlateStackNoteColor() const;`
- L75 _private prototype_ `FReply OnToggleInlineDisplayClicked() const;`
- L77 _private prototype_ `FReply OnEditHeaderButtonClicked();`
- L78 _private prototype_ `FReply OnEditBodyButtonClicked();`
- L80 _private prototype_ `FReply SummonColorPicker(const FGeometry& Geometry, const FPointerEvent& PointerEvent) const;`
- L81 _private prototype_ `void OnColorPickedCommitted(FLinearColor LinearColor) const;`
- L82 _private prototype_ `void OnColorPickerCancelled(FLinearColor LinearColor) const;`
- L83 _private prototype_ `void OnColorPickerClosed(const TSharedRef<SWindow>& Window) const;`
- L85 _private prototype_ `EVisibility GetEditNoteHeaderButtonVisibility() const;`
- L86 _private prototype_ `EVisibility GetEditNoteBodyButtonVisibility() const;`
- L89 _private member_ `TWeakObjectPtr<UNiagaraStackNote> StackNote;`
- L91 _private member_ `TSharedPtr<SExpandableArea> ExpandableArea;`
- L92 _private member_ `TSharedPtr<SInlineEditableTextBlock> HeaderText;`
- L93 _private member_ `TSharedPtr<SInlineEditableTextBlock> BodyText;`
- L95 _private member_ `TAttribute<bool> ShowEditTextButtons;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NIAGARAEDITORWIDGETS_API`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/SNiagaraSystemEffectTypeBar.h` (Private)


#### class `SNiagaraSystemEffectTypeBar`  
`class SNiagaraSystemEffectTypeBar : public SCompoundWidget`  
_L12-35_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNiagaraSystemEffectTypeBar)`
- L19 _public prototype_ `virtual ~SNiagaraSystemEffectTypeBar();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraSystem& InSystem);`
- L22 _public prototype_ `void UpdateEffectTypeWidgets();`
- L24 _private prototype_ `TSharedPtr<SWidget> CreatePropertyValueWidget(FProperty* Property);`
- L27 _private prototype_ `FText GetObjectName(UObject* Object) const;`
- L28 _private prototype_ `FText GetClassDisplayName(UObject* Object) const;`
- L29 _private prototype_ `int32 GetActiveDetailsWidgetIndex() const;`
- L30 _private prototype_ `void UpdateEffectType();`
- L32 _private member_ `TWeakObjectPtr<UNiagaraEffectType> EffectType;`
- L33 _private member_ `TWeakObjectPtr<UNiagaraSystem> System;`
- L34 _private member_ `TSharedPtr<SWrapBox> EffectTypeValuesBox;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/NiagaraStackPropertyRowUtilities.h` (Private)


#### class `FNiagaraStackPropertyRowUtilities`  
`class FNiagaraStackPropertyRowUtilities`  
_L12-19_
- L15 _public prototype_ `static SNiagaraStackTableRow::FOnFillRowContextMenu CreateOnFillRowContextMenu(UNiagaraStackPropertyRow& PropertyRow, const FNodeWidgetActions& GeneratedPropertyNodeWidgetActions);`
- L18 _private prototype_ `static void OnFillPropertyRowContextMenu(FMenuBuilder& MenuBuilder, TWeakObjectPtr<UNiagaraStackPropertyRow> PropertyRowWeak, FNodeWidgetActions PropertyNodeWidgetActions);`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraDeterminismToggle.h` (Private)


#### class `SNiagaraDeterminismToggle`  
`class SNiagaraDeterminismToggle: public SCompoundWidget`  
_L9-31_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SNiagaraDeterminismToggle)`
- L13 _public prototype_ `SLATE_END_ARGS();`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L18 _private prototype_ `void ToggleDeterminism() const;`
- L19 _private prototype_ `FReply ToggleDeterminismInUI() const;`
- L21 _private prototype_ `FText GetDeterminismButtonText() const;`
- L22 _private prototype_ `const FSlateBrush* GetDeterminismImage() const;`
- L23 _private prototype_ `FText GetDeterminismToggleTooltip() const;`
- L26 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModel;`
- L27 _private member_ `FText PropertyDescription;`
- L29 _private member_ `static FSlateBrush* DeterminismBrush;`
- L30 _private member_ `static FSlateBrush* NonDeterminismBrush;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraLocalSpaceToggle.h` (Private)


#### class `SNiagaraLocalSpaceToggle`  
`class SNiagaraLocalSpaceToggle: public SCompoundWidget`  
_L9-27_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SNiagaraLocalSpaceToggle)`
- L13 _public prototype_ `SLATE_END_ARGS();`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L18 _private prototype_ `void ToggleLocalSpace() const;`
- L19 _private prototype_ `FReply ToggleLocalSpaceForUI() const;`
- L21 _private prototype_ `const FSlateBrush* GetLocalSpaceToggleImage() const;`
- L22 _private prototype_ `FText GetLocalSpaceToggleTooltip() const;`
- L25 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModel;`
- L26 _private member_ `FText PropertyDescription;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraSimTargetToggle.h` (Private)


#### class `SNiagaraSimTargetToggle`  
`class SNiagaraSimTargetToggle: public SCompoundWidget`  
_L9-28_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SNiagaraSimTargetToggle)`
- L13 _public prototype_ `SLATE_END_ARGS();`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L18 _private prototype_ `void ToggleSimTarget() const;`
- L19 _private prototype_ `FReply ToggleSimTargetInUI() const;`
- L21 _private prototype_ `const FSlateBrush* GetSimTargetImage() const;`
- L22 _private prototype_ `FText GetSimTargetToggleTooltip() const;`
- L24 _private prototype_ `FNiagaraEmitterHandle* GetEmitterHandle() const;`
- L27 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> WeakEmitterHandleViewModel;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackErrorItem.h` (Private)


#### class `SNiagaraStackErrorItem`  
`class SNiagaraStackErrorItem: public SNiagaraStackEntryWidget`  
_L12-22_
- inherits: `SNiagaraStackEntryWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackErrorItem)`
- L16 _public prototype_ `SLATE_END_ARGS();`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackErrorItem* InErrorItem, UNiagaraStackViewModel* InStackViewModel);`
- L21 _private member_ `UNiagaraStackErrorItem* ErrorItem;`

#### class `SNiagaraStackErrorItemFix`  
`class SNiagaraStackErrorItemFix : public SNiagaraStackEntryWidget`  
_L24-37_
- inherits: `SNiagaraStackEntryWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackErrorItemFix)`
- L28 _public prototype_ `SLATE_END_ARGS();`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackErrorItemFix* InErrorItem, UNiagaraStackViewModel* InStackViewModel);`
- L33 _private prototype_ `void LinkNavigate();`
- L36 _private member_ `UNiagaraStackErrorItemFix* ErrorItem;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackFunctionInputName.h` (Private)


#### class `SNiagaraStackFunctionInputName`  
`class SNiagaraStackFunctionInputName: public SNiagaraStackEntryWidget`  
_L14-90_
- inherits: `SNiagaraStackEntryWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackFunctionInputName)`
- L18 _public prototype_ `SLATE_ATTRIBUTE(bool, IsSelected);`
- L19 _public prototype_ `SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackFunctionInput* InFunctionInput, UNiagaraStackViewModel* InStackViewModel);`
- L23 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L25 _public prototype_ `void FillRowContextMenu(class FMenuBuilder& MenuBuilder);`
- L27 _public prototype_ `FSimpleMulticastDelegate& OnRequestReconstructRow();`
- L30 _private prototype_ `EVisibility GetEditConditionCheckBoxVisibility() const;`
- L32 _private prototype_ `ECheckBoxState GetEditConditionCheckState() const;`
- L34 _private prototype_ `void OnEditConditionCheckStateChanged(ECheckBoxState InCheckState);`
- L36 _private prototype_ `bool GetIsNameReadOnly() const;`
- L38 _private prototype_ `bool GetIsNameWidgetSelected() const;`
- L40 _private prototype_ `bool GetIsEnabled() const;`
- L42 _private prototype_ `FText GetToolTipText() const;`
- L44 _private prototype_ `void OnNameTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L46 _private prototype_ `void GetChangeNamespaceSubMenu(FMenuBuilder& MenuBuilder);`
- L47 _private prototype_ `void OnChangeNamespace(FNiagaraNamespaceMetadata Metadata);`
- L49 _private prototype_ `void GetChangeNamespaceModifierSubMenu(FMenuBuilder& MenuBuilder);`
- L51 _private prototype_ `FText GetSetNamespaceModifierToolTip(FName InNamespaceModifier) const;`
- L52 _private prototype_ `bool CanSetNamespaceModifier(FName InNamespaceModifier) const;`
- L53 _private prototype_ `void OnSetNamespaceModifier(FName InNamespaceModifier);`
- L55 _private prototype_ `FText GetSetCustomNamespaceModifierToolTip() const;`
- L56 _private prototype_ `bool CanSetCustomNamespaceModifier() const;`
- L57 _private prototype_ `void OnSetCustomNamespaceModifier();`
- L59 _private prototype_ `FText GetCopyParameterReferenceToolTip() const;`
- L60 _private prototype_ `bool CanCopyParameterReference() const;`
- L61 _private prototype_ `void OnCopyParameterReference();`
- L63 _private prototype_ `ECheckBoxState GetUseDefaultDisplayCheckboxState() const;`
- L64 _private prototype_ `void OnSetUseDefaultDisplay();`
- L66 _private prototype_ `ECheckBoxState GetUseInlineExpressionDisplayCheckboxState() const;`
- L67 _private prototype_ `void OnSetUseInlineExpressionDisplay();`
- L69 _private prototype_ `ECheckBoxState GetUseInlineHorizontalGraphDisplayCheckboxState() const;`
- L70 _private prototype_ `void OnSetUseInlineHorizontalGraphDisplay();`
- L72 _private prototype_ `ECheckBoxState GetUseInlineVerticalGraphDisplayCheckboxState() const;`
- L73 _private prototype_ `void OnSetUseInlineVerticalGraphDisplay();`
- L75 _private prototype_ `ECheckBoxState GetUseInlineHybridGraphDisplayCheckboxState() const;`
- L76 _private prototype_ `void OnSetUseInlineHybridGraphDisplay();`
- L78 _private prototype_ `void InputStructureChanged(ENiagaraStructureChangedFlags Flags);`
- L81 _private member_ `UNiagaraStackFunctionInput* FunctionInput;`
- L83 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameTextBlock;`
- L85 _private member_ `TSharedPtr<SNiagaraParameterNameTextBlock> ParameterTextBlock;`
- L87 _private member_ `TAttribute<bool> IsSelected;`
- L89 _private member_ `FSimpleMulticastDelegate OnRequestReconstructRowDelegate;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackFunctionInputValue.h` (Private)


#### class `SNiagaraStackFunctionInputValue`  
`class SNiagaraStackFunctionInputValue: public SCompoundWidget`  
_L27-224_
- inherits: `SCompoundWidget`
- L41 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackFunctionInputValue) : _LayoutMode(ELayoutMode::FullRow) , _CompactActionMenuButtonVisibility(EVisibility::Visible)`
- L45 _public prototype_ `SLATE_ARGUMENT(ELayoutMode, LayoutMode) SLATE_ATTRIBUTE(EVisibility, CompactActionMenuButtonVisibility) SLATE_NAMED_SLOT(FArguments, ValueDecorator) SLATE_END_ARGS();`
- L50 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackFunctionInput* InFunctionInput);`
- L52 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _private prototype_ `TSharedRef<SWidget> ConstructValueWidgets();`
- L57 _private prototype_ `bool GetInputEnabled() const;`
- L59 _private prototype_ `bool GetEntryEnabled() const;`
- L61 _private prototype_ `void ConstructTextValueWidgets(TSharedRef<SHorizontalBox>& ValueBox, TAttribute<FText> GetText);`
- L63 _private prototype_ `void ConstructLocalValueStructWidgets(TSharedRef<SHorizontalBox>& ValueBox);`
- L65 _private prototype_ `void ConstructLinkedValueWidgets(TSharedRef<SHorizontalBox>& ValueBox);`
- L67 _private prototype_ `void ConstructLinkedSharedValueWidgets(TSharedRef<SHorizontalBox>& ValueBox);`
- L69 _private prototype_ `void ConstructDynamicValueWidgets(TSharedRef<SHorizontalBox>& ValueBox);`
- L71 _private prototype_ `void OnInputValueChanged();`
- L73 _private prototype_ `void ParameterBeginValueChange();`
- L75 _private prototype_ `void ParameterEndValueChange();`
- L77 _private prototype_ `void ParameterValueChanged(TWeakPtr<SNiagaraParameterEditor> ParameterEditor);`
- L79 _private prototype_ `void ParameterPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L81 _private prototype_ `FName GetLinkedValueHandleName() const;`
- L83 _private prototype_ `FText GetDataValueText() const;`
- L85 _private prototype_ `FText GetObjectAssetValueText() const;`
- L87 _private prototype_ `FText GetDynamicValueText() const;`
- L89 _private prototype_ `FText GetDefaultFunctionText() const;`
- L91 _private prototype_ `void OnExpressionTextCommitted(const FText& Name, ETextCommit::Type CommitInfo);`
- L93 _private prototype_ `FReply DynamicInputTextDoubleClicked(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);`
- L94 _private prototype_ `FReply OnLinkedInputDoubleClicked(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);`
- L131 _private prototype_ `static TSharedRef<SExpanderArrow> CreateCustomNiagaraFunctionInputActionExpander(const FCustomExpanderData& ActionMenuData);`
- L133 _private prototype_ `TSharedRef<SWidget> OnGetAvailableHandleMenu();`
- L135 _private prototype_ `TSharedRef<SWidget> OnGetCompactActionMenu();`
- L137 _private prototype_ `void OnFillAssignSubMenu(FMenuBuilder& MenuBuilder);`
- L139 _private prototype_ `TSharedRef<SWidget> GetVersionSelectorDropdownMenu();`
- L140 _private prototype_ `void SwitchToVersion(FNiagaraAssetVersion Version);`
- L141 _private prototype_ `FSlateColor GetVersionSelectorColor() const;`
- L143 _private prototype_ `void SetToLocalValue();`
- L145 _private prototype_ `void DynamicInputScriptSelected(UNiagaraScript* DynamicInputScript);`
- L147 _private prototype_ `void CustomExpressionSelected();`
- L149 _private prototype_ `void CreateScratchSelected();`
- L151 _private prototype_ `void ParameterSelected(FNiagaraVariableBase Parameter);`
- L152 _private prototype_ `void ParameterWithConversionSelected(FNiagaraVariableBase Parameter, UNiagaraScript* ConversionScript);`
- L154 _private prototype_ `EVisibility GetResetButtonVisibility() const;`
- L156 _private prototype_ `EVisibility GetDropdownButtonVisibility() const;`
- L158 _private prototype_ `FReply ResetButtonPressed() const;`
- L160 _private prototype_ `EVisibility GetResetToBaseButtonVisibility() const;`
- L162 _private prototype_ `FReply ResetToBaseButtonPressed() const;`
- L164 _private prototype_ `FReply OnFunctionInputDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L166 _private prototype_ `bool OnFunctionInputAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation);`
- L168 _private prototype_ `TArray<TSharedPtr<FNiagaraMenuAction_Generic>> CollectDynamicInputActionsForReassign() const;`
- L170 _private prototype_ `void ShowReassignDynamicInputScriptMenu();`
- L172 _private prototype_ `bool GetLibraryOnly() const;`
- L174 _private prototype_ `void SetLibraryOnly(bool bInIsLibraryOnly);`
- L176 _private prototype_ `FReply ScratchButtonPressed() const;`
- L178 _private prototype_ `EVisibility GetVisibilityForHoverOnlyWidgets() const;`
- L181 _private member_ `UNiagaraStackFunctionInput* FunctionInput;`
- L183 _private member_ `ELayoutMode LayoutMode;`
- L185 _private member_ `TSharedPtr<SBox> ValueContainer;`
- L186 _private member_ `UNiagaraStackFunctionInput::EValueMode ValueModeForGeneratedWidgets = UNiagaraStackFunctionInput::EValueMode::None;`
- L188 _private member_ `TSharedPtr<FStructOnScope> DisplayedLocalValueStruct;`
- L189 _private member_ `TSharedPtr<SNiagaraParameterEditor> LocalValueStructParameterEditor;`
- L190 _private member_ `TSharedPtr<IStructureDetailsView> LocalValueStructDetailsView;`
- L192 _private member_ `TSharedPtr<SNiagaraMenuActionSelector> ActionSelector;`
- L193 _private member_ `TSharedPtr<SNiagaraFilterBox> FilterBox;`
- L194 _private member_ `TSharedPtr<SComboButton> SetFunctionInputButton;`
- L195 _private member_ `TSharedPtr<FNiagaraHLSLSyntaxHighlighter> SyntaxHighlighter;`
- L197 _private member_ `TAttribute<EVisibility> CompactActionMenuButtonVisibilityAttribute;`
- L198 _private member_ `TSharedPtr<FNiagaraStackCommandContext> StackCommandContext;`
- L200 _private member_ `static bool bLibraryOnly;`
- L202 _private member_ `static FName FavoriteActionsProfile;`
- L205 _private prototype_ `TArray<TSharedPtr<FNiagaraMenuAction_Generic>> CollectActions();`
- L206 _private prototype_ `TArray<FString> OnGetCategoriesForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L207 _private prototype_ `TArray<ENiagaraMenuSections> OnGetSectionsForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L208 _private prototype_ `bool OnCompareSectionsForEquality(const ENiagaraMenuSections& SectionA, const ENiagaraMenuSections& SectionB);`
- L209 _private prototype_ `bool OnCompareSectionsForSorting(const ENiagaraMenuSections& SectionA, const ENiagaraMenuSections& SectionB);`
- L210 _private prototype_ `bool OnCompareCategoriesForEquality(const FString& CategoryA, const FString& CategoryB);`
- L211 _private prototype_ `bool OnCompareCategoriesForSorting(const FString& CategoryA, const FString& CategoryB);`
- L212 _private prototype_ `bool OnCompareItemsForEquality(const TSharedPtr<FNiagaraMenuAction_Generic>& ItemA, const TSharedPtr<FNiagaraMenuAction_Generic>& ItemB);`
- L213 _private prototype_ `bool OnCompareItemsForSorting(const TSharedPtr<FNiagaraMenuAction_Generic>& ItemA, const TSharedPtr<FNiagaraMenuAction_Generic>& ItemB);`
- L214 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForSection(const ENiagaraMenuSections& Section);`
- L215 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForCategory(const FString& Category);`
- L216 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L217 _private prototype_ `bool DoesItemPassCustomFilter(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L218 _private prototype_ `void OnItemActivated(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L219 _private prototype_ `void OnActionRowHoverEvent(const TSharedPtr<FNiagaraMenuAction_Generic>& ActionNode, bool bIsHovered);`
- L221 _private prototype_ `void TriggerRefresh(const TMap<EScriptSource, bool>& SourceState);`
- L223 _private function_ `FText GetFilterText() const`

#### enum `SNiagaraStackFunctionInputValue::ELayoutMode`  
`enum class ELayoutMode`  
_L32-38_
- L34 _public enumerator_ `FullRow`
- L35 _public enumerator_ `CompactInline`
- L36 _public enumerator_ `LinkedInline`
- L37 _public enumerator_ `EditDropDownOnly`

#### class `SNiagaraStackFunctionInputValue::SNiagaraFunctionInputActionMenuExpander`  
`class SNiagaraFunctionInputActionMenuExpander: public SExpanderArrow`  
_L96-129_
- inherits: `SExpanderArrow`
- L98 _private function_ `SLATE_BEGIN_ARGS(SNiagaraFunctionInputActionMenuExpander)`
- L103 _public function_ `void Construct(const FArguments& InArgs, const FCustomExpanderData& ActionMenuData)`
- L125 _private function_ `FMargin GetCustomIndentPadding() const`

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef SItemSelector<FString, TSharedPtr<FNiagaraMenuAction_Generic>, ENiagaraMenuSections> SNiagaraMenuActionSelector;`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColumnWidthChanged, float) enum class ELayoutMode { FullRow, CompactInline, LinkedInline, EditDropDownOnly };`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackIndent.h` (Private)


#### enum `ENiagaraStackIndentMode`  
`enum class ENiagaraStackIndentMode`  
_L11-15_
- L13 _public enumerator_ `Name`
- L14 _public enumerator_ `Value`

#### class `SNiagaraStackIndent`  
`class SNiagaraStackIndent : public SCompoundWidget`  
_L17-34_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackIndent)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackEntry* InStackEntry, ENiagaraStackIndentMode InMode);`
- L26 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L27 _private prototype_ `FOptionalSize GetIndentWidth() const;`
- L28 _private prototype_ `FSlateColor GetRowBackgroundColor(int32 IndentLevel) const;`
- L31 _private member_ `UNiagaraStackEntry* StackEntry;`
- L32 _private member_ `ENiagaraStackIndentMode Mode;`
- L33 _private member_ `float SingleIndentWidth;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackInheritanceIcon.h` (Private)


#### class `SNiagaraStackInheritanceIcon`  
`class SNiagaraStackInheritanceIcon : public SCompoundWidget`  
_L10-23_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackInheritanceIcon)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackEntry* InStackEntry);`
- L19 _private prototype_ `EVisibility IsVisible() const;`
- L22 _private member_ `UNiagaraStackEntry* StackEntry;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackInlineDynamicInput.h` (Private)


#### class `SNiagaraStackInlineDynamicInput`  
`class SNiagaraStackInlineDynamicInput : public SCompoundWidget`  
_L13-124_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackInlineDynamicInput)`
- L17 _public prototype_ `SLATE_END_ARGS();`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackFunctionInput* InFunctionInput);`
- L55 _private prototype_ `static FInputDisplayEntries CollectInputDisplayEntriesRecursive(UNiagaraStackFunctionInput* Input);`
- L57 _private prototype_ `void RootFunctionInputStructureChanged(ENiagaraStructureChangedFlags Flags);`
- L59 _private prototype_ `void RootFunctionInputValueChanged();`
- L61 _private prototype_ `static bool TryMatchFormatInputs( const TArray<FInputDisplayEntries>& ChildInputs, const TArray<FNiagaraInlineDynamicInputFormatToken>& InlineFormat, TArray<TPair<FNiagaraInlineDynamicInputFormatToken, FInputDisplayEntries>>& OutMatchedFormatInputs);`
- L66 _private prototype_ `void ConstructChildren();`
- L68 _private prototype_ `void ConstructWrappedExpressionInputWidgets(TSharedRef<SWrapBox> ExpressionWrapBox, TSharedRef<SVerticalBox> DataInterfaceVerticalBox, const FInputDisplayEntries& InputDisplayEntries, FGuid InputId, bool bIsRootInput);`
- L70 _private prototype_ `void ConstructWrappedExpressionDynamicInputWidgets(TSharedRef<SWrapBox> ExpressionWrapBox, TSharedRef<SVerticalBox> DataInterfaceVerticalBox, const FInputDisplayEntries& InputDisplayEntries, FGuid InputId, bool bIsRootInput);`
- L72 _private prototype_ `TSharedRef<SWidget> ConstructGraphInputWidgetForFormatTokenInputPair( const TPair<FNiagaraInlineDynamicInputFormatToken, FInputDisplayEntries>& FormatTokenInputPair, const UNiagaraStackFunctionInput* OwningInput, FGuid InputId);`
- L77 _private prototype_ `void GenerateFormattedGroups( const TArray<FInputDisplayEntries>& InputDisplayEntries, const TArray<FNiagaraInlineDynamicInputFormatToken>& InlineFormat, bool bIgnoreLinebreaks, bool bTreatInputsWithoutChildrenLikeDecorators, bool& bOutFormatMatched, TArray<TArray<TPair<FNiagaraInlineDynamicInputFormatToken, FInputDisplayEntries>>>& OutFormattedGroups);`
- L85 _private prototype_ `TSharedRef<SWidget> ConstructHorizontalGraphInputWidgets( const TArray<FInputDisplayEntries>& InputDisplayEntries, const UNiagaraStackFunctionInput* OwningInput, TSharedRef<SVerticalBox> DataInterfaceVerticalBox, TSharedPtr<FWidthSynchronize> InputWidthSynchronizer);`
- L91 _private prototype_ `TSharedRef<SWidget> ConstructVerticalGraphInputWidgets( const TArray<FInputDisplayEntries>& InputDisplayEntries, const UNiagaraStackFunctionInput* OwningInput, TSharedRef<SVerticalBox> DataInterfaceVerticalBox);`
- L96 _private prototype_ `TSharedRef<SWidget> ConstructHybridGraphInputWidgets( const TArray<FInputDisplayEntries>& InputDisplayEntries, const UNiagaraStackFunctionInput* OwningInput, TSharedRef<SVerticalBox> DataInterfaceVerticalBox);`
- L101 _private prototype_ `void ConstructDataInterfaceWidgets(TSharedRef<SVerticalBox> DataInterfaceVerticalBox, const FInputDisplayEntries& InputDisplayEntries, FGuid InputId);`
- L103 _private prototype_ `FGuid GetHoveredInputId() const;`
- L105 _private prototype_ `void OnFormatTokenOutlineHoveredChanged(FGuid InputId, bool bIsHovered);`
- L107 _private prototype_ `EVisibility GetEditConditionCheckBoxVisibility(UNiagaraStackFunctionInput* FunctionInput) const;`
- L109 _private prototype_ `ECheckBoxState GetEditConditionCheckState(UNiagaraStackFunctionInput* FunctionInput) const;`
- L111 _private prototype_ `void OnEditConditionCheckStateChanged(ECheckBoxState InCheckState, UNiagaraStackFunctionInput* FunctionInput);`
- L113 _private prototype_ `EVisibility GetCompactActionMenuButtonVisibility(FGuid InputId) const;`
- L116 _private member_ `UNiagaraStackFunctionInput* RootFunctionInput;`
- L117 _private member_ `FInputDisplayEntries RootInputDisplayEntries;`
- L118 _private member_ `TArray<TSharedPtr<FWidthSynchronize>> WidthSynchronizers;`
- L120 _private member_ `bool bSingleValueMode;`
- L121 _private member_ `FGuid HoveredInputId;`
- L123 _private member_ `static const float TextIconSize;`

#### struct `SNiagaraStackInlineDynamicInput::FInputDisplayEntries`  
`struct FInputDisplayEntries`  
_L22-43_
- L24 _public function_ `FInputDisplayEntries() : InputEntry(nullptr) , ChildObjectEntry(nullptr)`
- L30 _public function_ `FORCEINLINE bool operator ==(const FInputDisplayEntries& Other) const`
- L38 _public function_ `FORCEINLINE bool operator !=(const FInputDisplayEntries& Other) const`
- L40 _public member_ `UNiagaraStackFunctionInput* InputEntry;`
- L41 _public member_ `TArray<FInputDisplayEntries> ChildInputDisplayEntries;`
- L42 _public member_ `UNiagaraStackObject* ChildObjectEntry;`

#### class `SNiagaraStackInlineDynamicInput::FWidthSynchronize`  
`class FWidthSynchronize`  
_L45-52_
- L48 _public prototype_ `void AddWidget(TSharedRef<SWidget> InWidget);`
- L49 _public prototype_ `FOptionalSize GetMaxDesiredWidth() const;`
- L51 _private member_ `TArray<TWeakPtr<SWidget>> WeakWidgets;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackIssueIcon.h` (Private)


#### class `SNiagaraStackIssueIcon`  
`class SNiagaraStackIssueIcon : public SCompoundWidget`  
_L14-57_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackIssueIcon) : _IconMode(EIconMode::Normal)`
- L27 _public prototype_ `SLATE_ARGUMENT(EIconMode, IconMode) SLATE_EVENT(FOnClicked, OnClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackViewModel* InStackViewModel, UNiagaraStackEntry* InStackEntry);`
- L33 _public prototype_ `~SNiagaraStackIssueIcon();`
- L36 _private prototype_ `bool GetIconIsEnabled() const;`
- L38 _private prototype_ `const FSlateBrush* GetIconBrush() const;`
- L39 _private prototype_ `FText GetIconToolTip() const;`
- L40 _private prototype_ `FOptionalSize GetIconHeight() const;`
- L41 _private prototype_ `EVisibility GetCompactIconBorderVisibility() const;`
- L43 _private prototype_ `void UpdateFromEntry(ENiagaraStructureChangedFlags Flags);`
- L46 _private member_ `const FSlateBrush* IconBrush;`
- L47 _private member_ `float IconHeight;`
- L49 _private member_ `mutable TOptional<FText> IconToolTipCache;`
- L51 _private member_ `UNiagaraStackViewModel* StackViewModel;`
- L52 _private member_ `TWeakObjectPtr<UNiagaraStackEntry> StackEntry;`
- L53 _private member_ `EIconMode IconMode;`
- L55 _private member_ `static const float NormalSize;`
- L56 _private member_ `static const float CompactSize;`

#### enum `SNiagaraStackIssueIcon::EIconMode`  
`enum class EIconMode`  
_L17-21_
- L19 _public enumerator_ `Normal`
- L20 _public enumerator_ `Compact`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackItem.h` (Private)


#### class `SNiagaraStackItem`  
`class SNiagaraStackItem: public SNiagaraStackEntryWidget`  
_L12-57_
- inherits: `SNiagaraStackEntryWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackItem)`
- L16 _public prototype_ `SLATE_END_ARGS();`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackItem& InItem, UNiagaraStackViewModel* InStackViewModel);`
- L20 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L23 _protected function_ `virtual void AddCustomRowWidgets(TSharedRef<SHorizontalBox> HorizontalBox)`
- L25 _protected prototype_ `virtual TSharedRef<SWidget> AddContainerForRowWidgets(TSharedRef<SWidget> RowWidgets);`
- L28 _private prototype_ `void ConstructHeaderValues(TSharedRef<SHorizontalBox> HorizontalBox);`
- L30 _private prototype_ `FReply EditModeButtonClicked();`
- L31 _private prototype_ `EVisibility IsEditButtonVisible() const;`
- L32 _private prototype_ `FText GetEditModeButtonToolTipText() const;`
- L34 _private prototype_ `EVisibility GetResetToBaseButtonVisibility() const;`
- L36 _private prototype_ `FText GetResetToBaseButtonToolTipText() const;`
- L38 _private prototype_ `FReply ResetToBaseButtonClicked();`
- L40 _private prototype_ `FText GetDeleteButtonToolTipText() const;`
- L42 _private prototype_ `EVisibility GetDeleteButtonVisibility() const;`
- L44 _private prototype_ `FReply DeleteClicked();`
- L46 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InCheckState);`
- L48 _private prototype_ `ECheckBoxState CheckEnabledStatus() const;`
- L50 _private prototype_ `bool GetEnabledCheckBoxEnabled() const;`
- L52 _private prototype_ `bool GetEntryIsEnabled() const;`
- L55 _private member_ `UNiagaraStackItem* Item;`
- L56 _private member_ `TSharedPtr<SNiagaraStackDisplayName> DisplayNameWidget;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackItemFooter.h` (Private)


#### class `SNiagaraStackItemFooter`  
`class SNiagaraStackItemFooter: public SCompoundWidget`  
_L10-33_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackItemFooter)`
- L14 _public prototype_ `SLATE_END_ARGS();`
- L16 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackItemFooter& InItemFooter);`
- L19 _private prototype_ `EVisibility GetExpandButtonVisibility() const;`
- L21 _private prototype_ `EVisibility GetOverrideIconVisibility() const;`
- L23 _private prototype_ `const struct FSlateBrush* GetButtonBrush() const;`
- L25 _private prototype_ `FText GetToolTipText() const;`
- L27 _private prototype_ `FReply ExpandButtonClicked();`
- L30 _private member_ `UNiagaraStackItemFooter* ItemFooter;`
- L31 _private member_ `FText ExpandedToolTipText;`
- L32 _private member_ `FText CollapsedToolTipText;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackItemGroup.h` (Private)


#### class `SNiagaraStackItemGroup`  
`class SNiagaraStackItemGroup : public SNiagaraStackEntryWidget`  
_L11-34_
- inherits: `SNiagaraStackEntryWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackItemGroup)`
- L15 _public prototype_ `SLATE_END_ARGS();`
- L17 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackItemGroup& InGroup, UNiagaraStackViewModel* InStackViewModel);`
- L20 _private prototype_ `TSharedRef<SWidget> ConstructAddButton();`
- L22 _private prototype_ `FText GetDeleteButtonToolTip() const;`
- L24 _private prototype_ `EVisibility GetDeleteButtonVisibility() const;`
- L26 _private prototype_ `FReply DeleteClicked();`
- L28 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InCheckState);`
- L29 _private prototype_ `ECheckBoxState CheckEnabledStatus() const;`
- L30 _private prototype_ `bool GetEnabledCheckBoxEnabled() const;`
- L33 _private member_ `UNiagaraStackItemGroup* Group;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackItemGroupAddButton.h` (Private)


#### class `SNiagaraStackItemGroupAddButton`  
`class SNiagaraStackItemGroupAddButton : public SCompoundWidget`  
_L12-33_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackItemGroupAddButton) :_Width(TextIconSize * 2)`
- L18 _public prototype_ `SLATE_ARGUMENT(float, Width) SLATE_END_ARGS();`
- L21 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackEntry* InSourceEntry, INiagaraStackItemGroupAddUtilities* InAddUtilities);`
- L24 _private prototype_ `TSharedRef<SWidget> GetAddMenu();`
- L26 _private prototype_ `FReply AddDirectlyButtonClicked();`
- L29 _private member_ `TWeakObjectPtr<UNiagaraStackEntry> SourceEntryWeak;`
- L30 _private member_ `INiagaraStackItemGroupAddUtilities* AddUtilities;`
- L31 _private member_ `TSharedPtr<SComboButton> AddActionButton;`
- L32 _private member_ `static const float TextIconSize;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackItemGroupAddMenu.h` (Private)


#### class `SNiagaraStackItemGroupAddMenu`  
`class SNiagaraStackItemGroupAddMenu : public SCompoundWidget`  
_L18-65_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackItemGroupAddMenu)`
- L22 _public prototype_ `SLATE_END_ARGS();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackEntry* InSourceEntry, INiagaraStackItemGroupAddUtilities* InAddUtilities, int32 InInsertIndex);`
- L26 _public prototype_ `TSharedPtr<SWidget> GetFilterTextBox();`
- L29 _private prototype_ `bool GetLibraryOnly() const;`
- L31 _private prototype_ `void SetLibraryOnly(bool bInLibraryOnly);`
- L34 _private member_ `INiagaraStackItemGroupAddUtilities* AddUtilities;`
- L35 _private member_ `TWeakObjectPtr<UNiagaraStackEntry> SourceEntry;`
- L36 _private member_ `int32 InsertIndex;`
- L38 _private member_ `TSharedPtr<SNiagaraStackAddSelector> ActionSelector;`
- L39 _private member_ `TSharedPtr<SNiagaraFilterBox> FilterBox;`
- L41 _private member_ `bool bSetFocusOnNextTick;`
- L43 _private member_ `static bool bLibraryOnly;`
- L46 _private prototype_ `TArray<TSharedPtr<FNiagaraMenuAction_Generic>> CollectActions();`
- L47 _private prototype_ `TArray<FString> OnGetCategoriesForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L48 _private prototype_ `TArray<ENiagaraMenuSections> OnGetSectionsForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L49 _private prototype_ `bool OnCompareSectionsForEquality(const ENiagaraMenuSections& SectionA, const ENiagaraMenuSections& SectionB);`
- L50 _private prototype_ `bool OnCompareSectionsForSorting(const ENiagaraMenuSections& SectionA, const ENiagaraMenuSections& SectionB);`
- L51 _private prototype_ `bool OnCompareCategoriesForEquality(const FString& CategoryA, const FString& CategoryB);`
- L52 _private prototype_ `bool OnCompareCategoriesForSorting(const FString& CategoryA, const FString& CategoryB);`
- L53 _private prototype_ `bool OnCompareItemsForEquality(const TSharedPtr<FNiagaraMenuAction_Generic>& ItemA, const TSharedPtr<FNiagaraMenuAction_Generic>& ItemB);`
- L54 _private prototype_ `bool OnCompareItemsForSorting(const TSharedPtr<FNiagaraMenuAction_Generic>& ItemA, const TSharedPtr<FNiagaraMenuAction_Generic>& ItemB);`
- L55 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForSection(const ENiagaraMenuSections& Section);`
- L56 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForCategory(const FString& Category);`
- L57 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForItem(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L58 _private prototype_ `bool DoesItemPassCustomFilter(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L59 _private prototype_ `void OnItemActivated(const TSharedPtr<FNiagaraMenuAction_Generic>& Item);`
- L60 _private prototype_ `void OnItemRowHoverEvent(const TSharedPtr<FNiagaraMenuAction_Generic>& Item, bool bHover) const;`
- L62 _private prototype_ `void TriggerRefresh(const TMap<EScriptSource, bool>& SourceState);`
- L64 _private function_ `FText GetFilterText() const`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef SItemSelector<FString, TSharedPtr<FNiagaraMenuAction_Generic>, ENiagaraMenuSections> SNiagaraStackAddSelector;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackModuleItem.h` (Private)


#### class `SNiagaraStackModuleItem`  
`class SNiagaraStackModuleItem : public SNiagaraStackItem`  
_L17-82_
- inherits: `SNiagaraStackItem`
- L20 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackModuleItem)`
- L21 _public prototype_ `SLATE_END_ARGS();`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackModuleItem& InModuleItem, UNiagaraStackViewModel* InStackViewModel);`
- L25 _public prototype_ `void FillRowContextMenu(class FMenuBuilder& MenuBuilder);`
- L28 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L29 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _protected prototype_ `virtual void AddCustomRowWidgets(TSharedRef<SHorizontalBox> HorizontalBox) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> AddContainerForRowWidgets(TSharedRef<SWidget> RowWidgets) override;`
- L37 _private prototype_ `bool GetButtonsEnabled() const;`
- L39 _private prototype_ `EVisibility GetRaiseActionMenuVisibility() const;`
- L41 _private prototype_ `EVisibility GetRefreshVisibility() const;`
- L43 _private prototype_ `EVisibility GetVersionSelectionMenuVisibility() const;`
- L44 _private prototype_ `bool GetVersionSelectionMenuEnabled() const;`
- L45 _private prototype_ `FText GetVersionSelectionMenuTooltip() const;`
- L47 _private prototype_ `FReply ScratchButtonPressed() const;`
- L49 _private prototype_ `TSharedRef<SWidget> RaiseActionMenuClicked();`
- L51 _private prototype_ `TSharedRef<SWidget> GetVersionSelectorDropdownMenu();`
- L53 _private prototype_ `bool CanRaiseActionMenu() const;`
- L55 _private prototype_ `static TSharedRef<SExpanderArrow> CreateCustomActionExpander(const struct FCustomExpanderData& ActionMenuData);`
- L57 _private prototype_ `FReply RefreshClicked();`
- L59 _private prototype_ `FReply OnModuleItemDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L61 _private prototype_ `FSlateColor GetVersionSelectorColor() const;`
- L63 _private prototype_ `bool OnModuleItemAllowDrop(TSharedPtr<class FDragDropOperation> DragDropOperation);`
- L65 _private prototype_ `void CollectModuleActions(FGraphActionListBuilderBase& ModuleActions);`
- L67 _private prototype_ `void ShowReassignModuleScriptMenu();`
- L69 _private prototype_ `bool GetLibraryOnly() const;`
- L71 _private prototype_ `void SetLibraryOnly(bool bInLibraryOnly);`
- L73 _private prototype_ `void SwitchToVersion(FNiagaraAssetVersion Version);`
- L76 _private member_ `UNiagaraStackModuleItem* ModuleItem;`
- L78 _private member_ `TSharedPtr<SComboButton> AddButton;`
- L80 _private member_ `static bool bLibraryOnly;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackRowPerfWidget.h` (Private)


#### class `SNiagaraStackRowPerfWidget`  
`class SNiagaraStackRowPerfWidget: public SCompoundWidget`  
_L13-64_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackRowPerfWidget)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UNiagaraStackEntry* InStackEntry, ENiagaraPerformanceStateScopeMode InStatScopeMode);`
- L21 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L24 _private prototype_ `float GetFullBarWidth() const;`
- L25 _private prototype_ `EVisibility GetPerfBarVisibility() const;`
- L26 _private prototype_ `FOptionalSize GetVisualizationBrushWidth() const;`
- L27 _private prototype_ `FOptionalSize GetPlaceholderBrushWidth() const;`
- L28 _private prototype_ `FLinearColor GetVisualizationBrushColor() const;`
- L29 _private prototype_ `FLinearColor GetPlaceholderBrushColor() const;`
- L30 _private prototype_ `bool HasPerformanceData() const;`
- L31 _private prototype_ `bool IsSystemStack() const;`
- L32 _private prototype_ `bool IsEmitterStack() const;`
- L33 _private prototype_ `bool IsParticleStack() const;`
- L34 _private prototype_ `EVisibility IsVisible() const;`
- L35 _private prototype_ `FText GetPerformanceDisplayText() const;`
- L36 _private prototype_ `FText GetEvalTypeDisplayText() const;`
- L37 _private prototype_ `FSlateColor GetPerformanceDisplayTextColor() const;`
- L38 _private prototype_ `FSlateFontInfo GetPerformanceDisplayTextFont() const;`
- L39 _private prototype_ `FText CreateTooltipText() const;`
- L41 _private prototype_ `bool IsGroupHeaderEntry() const;`
- L42 _private prototype_ `bool IsModuleEntry() const;`
- L43 _private prototype_ `bool IsEntrySelected() const;`
- L44 _private prototype_ `FVersionedNiagaraEmitter GetEmitter() const;`
- L45 _private prototype_ `ENiagaraScriptUsage GetUsage() const;`
- L46 _private prototype_ `ENiagaraStatEvaluationType GetEvaluationType() const;`
- L47 _private prototype_ `ENiagaraStatDisplayMode GetDisplayMode() const;`
- L48 _private prototype_ `bool IsInterpolatedSpawnEnabled() const;`
- L49 _private prototype_ `bool IsGpuEmitter() const;`
- L50 _private prototype_ `bool IsFinalized() const;`
- L52 _private prototype_ `float CalculateGroupOverallTime(FString StatScopeName) const;`
- L53 _private prototype_ `float CalculateStackEntryTime() const;`
- L55 _private member_ `mutable TOptional<FText> IconToolTipCache;`
- L56 _private member_ `TWeakObjectPtr<UNiagaraStackEntry> StackEntry;`
- L57 _private member_ `static IConsoleVariable* StatEnabledVar;`
- L58 _private member_ `ENiagaraPerformanceStateScopeMode StatScopeMode;`
- L60 _private member_ `float GroupOverallTime = 0;`
- L61 _private member_ `float StackEntryTime = 0;`
- L62 _private member_ `float UpdateInSpawnTime = 0;`
- L63 _private member_ `float EmitterTimeTotal = 0;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackScriptHierarchyRoot.h` (Private)


#### class `SNiagaraStackHierarchySection`  
`class SNiagaraStackHierarchySection : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackHierarchySection)`
- L16 _public prototype_ `SLATE_EVENT(FOnCheckStateChanged, OnCheckStateChanged) SLATE_ATTRIBUTE(ECheckBoxState, IsChecked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UHierarchySection* InSection);`
- L23 _private prototype_ `FText GetSectionNameAsText() const;`
- L24 _private prototype_ `FText GetTooltipText() const;`
- L26 _private member_ `TWeakObjectPtr<const UHierarchySection> Section;`

#### class `SNiagaraStackScriptHierarchyRoot`  
`class SNiagaraStackScriptHierarchyRoot : public SCompoundWidget`  
_L29-51_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackScriptHierarchyRoot)`
- L33 _public prototype_ `SLATE_END_ARGS();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackScriptHierarchyRoot* InModuleHierarchyRoot);`
- L38 _private prototype_ `void ConstructSectionButtons();`
- L40 _private prototype_ `EVisibility GetLabelVisibility() const;`
- L42 _private prototype_ `ECheckBoxState IsSectionChecked(const UHierarchySection* NiagaraHierarchySection) const;`
- L43 _private prototype_ `void OnCheckStateChanged(ECheckBoxState CheckBoxState, const UHierarchySection* NiagaraHierarchySection);`
- L45 _private prototype_ `void HierarchyStructureChanged(ENiagaraStructureChangedFlags StructureChangedFlags);`
- L48 _private member_ `TWeakObjectPtr<UNiagaraStackScriptHierarchyRoot> ModuleHierarchyRoot;`
- L50 _private member_ `TSharedPtr<SWrapBox> SectionSelectorBox;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackTableRow.h` (Private)


#### class `SNiagaraStackTableRow`  
`class SNiagaraStackTableRow: public STableRow<UNiagaraStackEntry*>`  
_L19-153_
- inherits: `STableRow<UNiagaraStackEntry*>`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnColumnWidthChanged, float);`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnFillRowContextMenu, FMenuBuilder&);`
- L26 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackTableRow) : _ContentPadding(FMargin(2, 0, 2, 0)) , _IsCategoryIconHighlighted(false) , _ShowExecutionCategoryIcon(false)`
- L31 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_ARGUMENT(FMargin, ContentPadding) SLATE_ARGUMENT(TOptional<FSlateColor>, IndicatorColor) SLATE_ARGUMENT(bool, IsCategoryIconHighlighted) SLATE_ARGUMENT(bool, ShowExecutionCategoryIcon) SLATE_ATTRIBUTE(float, NameColumnWidth) SLATE_ATTRIBUTE(float, ValueColumnWidth) SLATE_ATTRIBUTE(EVisibility, IssueIconVisibility) SLATE_EVENT(FOnColumnWidthChanged, OnNameColumnWidthChanged) SLATE_EVENT(FOnColumnWidthChanged, OnValueColumnWidthChanged) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_EVENT(FOnTableRowDragLeave, OnDragLeave) SLATE_EVENT(FOnCanAcceptDrop, OnCanAcceptDrop) SLATE_EVENT(FOnAcceptDrop, OnAcceptDrop);`
- L45 _public prototype_ `SLATE_END_ARGS();`
- L49 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackViewModel* InStackViewModel, UNiagaraStackEntry* InStackEntry, TSharedRef<FNiagaraStackCommandContext> InStackCommandContext, const TSharedRef<STreeView<UNiagaraStackEntry*>>& InOwnerTree);`
- L51 _public prototype_ `void Reset();`
- L53 _public prototype_ `void SetOverrideNameWidth(TOptional<float> InMinWidth, TOptional<float> InMaxWidth);`
- L55 _public prototype_ `void SetOverrideNameAlignment(EHorizontalAlignment InHAlign, EVerticalAlignment InVAlign);`
- L57 _public prototype_ `void SetOverrideValueWidth(TOptional<float> InMinWidth, TOptional<float> InMaxWidth);`
- L59 _public prototype_ `void SetOverrideValueAlignment(EHorizontalAlignment InHAlign, EVerticalAlignment InVAlign);`
- L61 _public prototype_ `FMargin GetContentPadding() const;`
- L63 _public prototype_ `void SetContentPadding(FMargin InContentPadding);`
- L65 _public prototype_ `void SetNameAndValueContent(TSharedRef<SWidget> InNameWidget, TSharedPtr<SWidget> InValueWidget);`
- L67 _public prototype_ `void AddFillRowContextMenuHandler(FOnFillRowContextMenu FillRowContextMenuHandler);`
- L69 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L71 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L73 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L75 _private prototype_ `void Pulse();`
- L77 _private prototype_ `void CollapseChildren();`
- L78 _private prototype_ `void ExpandChildren();`
- L80 _private prototype_ `EVisibility GetRowVisibility() const;`
- L82 _private prototype_ `EVisibility GetExecutionCategoryIconVisibility() const;`
- L84 _private prototype_ `EVisibility GetExpanderVisibility() const;`
- L86 _private prototype_ `EVisibility GetInlineNoteVisibility() const;`
- L88 _private prototype_ `FReply ExpandButtonClicked();`
- L90 _private prototype_ `const FSlateBrush* GetExpandButtonImage() const;`
- L92 _private prototype_ `void OnNameColumnWidthChanged(float Width);`
- L94 _private prototype_ `void OnValueColumnWidthChanged(float Width);`
- L96 _private prototype_ `EVisibility GetSearchResultBorderVisibility() const;`
- L98 _private prototype_ `FSlateColor GetInnerBackgroundColor() const;`
- L100 _private prototype_ `void NavigateTo(UNiagaraStackEntry* Item);`
- L102 _private prototype_ `void ToggleShowInSummaryView() const;`
- L103 _private prototype_ `bool IsStackEntryInSummary() const;`
- L104 _private prototype_ `bool CanToggleShowInSummary() const;`
- L105 _private prototype_ `FText GetToggleShowSummaryActionTooltip() const;`
- L106 _private prototype_ `bool DoesItemExistInParentSummary() const;`
- L108 _private prototype_ `void NavigateToSummaryView() const;`
- L110 _private prototype_ `TSubclassOf<UHierarchyElement> DetermineHierarchyClassForSummaryView() const;`
- L112 _private member_ `UNiagaraStackViewModel* StackViewModel;`
- L113 _private member_ `UNiagaraStackEntry* StackEntry;`
- L114 _private member_ `TSharedPtr<STreeView<UNiagaraStackEntry*>> OwnerTree;`
- L116 _private member_ `TAttribute<float> NameColumnWidth;`
- L117 _private member_ `TAttribute<float> ValueColumnWidth;`
- L118 _private member_ `FOnColumnWidthChanged NameColumnWidthChanged;`
- L119 _private member_ `FOnColumnWidthChanged ValueColumnWidthChanged;`
- L121 _private member_ `TAttribute<EVisibility> IssueIconVisibility;`
- L123 _private member_ `const FSlateBrush* ExpandedImage;`
- L124 _private member_ `const FSlateBrush* CollapsedImage;`
- L126 _private member_ `TOptional<FSlateColor> IndicatorColor;`
- L128 _private member_ `FText ExecutionCategoryToolTipText;`
- L130 _private member_ `FMargin DefaultContentPadding;`
- L131 _private member_ `FMargin ContentPadding;`
- L133 _private member_ `EHorizontalAlignment NameHorizontalAlignment;`
- L134 _private member_ `EVerticalAlignment NameVerticalAlignment;`
- L136 _private member_ `TOptional<float> NameMinWidth;`
- L137 _private member_ `TOptional<float> NameMaxWidth;`
- L139 _private member_ `EHorizontalAlignment ValueHorizontalAlignment;`
- L140 _private member_ `EVerticalAlignment ValueVerticalAlignment;`
- L142 _private member_ `TOptional<float> ValueMinWidth;`
- L143 _private member_ `TOptional<float> ValueMaxWidth;`
- L145 _private member_ `bool bIsCategoryIconHighlighted;`
- L146 _private member_ `bool bShowExecutionCategoryIcon;`
- L148 _private member_ `TArray<FOnFillRowContextMenu> OnFillRowContextMenuHanders;`
- L150 _private member_ `TSharedPtr<FNiagaraStackCommandContext> StackCommandContext;`
- L152 _private member_ `FCurveSequence PulseAnimation;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnColumnWidthChanged, float);`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFillRowContextMenu, FMenuBuilder&);`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraStackValueCollection.h` (Private)


#### class `SNiagaraStackValueCollection`  
`class SNiagaraStackValueCollection : public SCompoundWidget`  
_L14-39_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNiagaraStackValueCollection)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L20 _public prototype_ `void Construct(const FArguments& InArgs, UNiagaraStackValueCollection* PropertyCollectionBase);`
- L23 _private prototype_ `EVisibility GetLabelVisibility() const;`
- L25 _private prototype_ `void ConstructSectionButtons();`
- L27 _private prototype_ `void InputCollectionStructureChanged(ENiagaraStructureChangedFlags StructureChangedFlags);`
- L29 _private prototype_ `ECheckBoxState GetSectionCheckState(FText Section) const;`
- L31 _private prototype_ `void OnSectionChecked(ECheckBoxState CheckState, FText Section);`
- L33 _private prototype_ `FText GetTooltipText(FText Section) const;`
- L36 _private member_ `UNiagaraStackValueCollection* PropertyCollection = nullptr;`
- L38 _private member_ `TSharedPtr<SWrapBox> SectionSelectorBox;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Private/Stack/SNiagaraSummaryViewToggle.h` (Private)


#### class `SNiagaraSummaryViewToggle`  
`class SNiagaraSummaryViewToggle: public SCompoundWidget`  
_L9-26_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SNiagaraSummaryViewToggle)`
- L13 _public prototype_ `SLATE_END_ARGS();`
- L15 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FNiagaraEmitterHandleViewModel> InEmitterHandleViewModel);`
- L18 _private prototype_ `void ToggleShowSummary() const;`
- L19 _private prototype_ `FReply ToggleShowSummaryForUI() const;`
- L21 _private prototype_ `const FSlateBrush* GetSummaryToggleImage() const;`
- L22 _private prototype_ `FText GetSummaryToggleTooltip() const;`
- L25 _private member_ `TWeakPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModel;`

### `Plugins/FX/Niagara/Source/NiagaraEditorWidgets/Public/NiagaraEditorWidgetsModule.h` (Public)


#### class `FNiagaraStackCurveEditorOptions`  
`class FNiagaraStackCurveEditorOptions`  
_L16-48_
- L19 _public prototype_ `FNiagaraStackCurveEditorOptions();`
- L21 _public prototype_ `bool GetNeedsInitializeView() const;`
- L22 _public prototype_ `void InitializeView(float InViewMinInput, float InViewMaxInput, float InViewMinOutput, float InViewMaxOutput);`
- L24 _public prototype_ `float GetViewMinInput() const;`
- L25 _public prototype_ `float GetViewMaxInput() const;`
- L26 _public prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);`
- L28 _public prototype_ `float GetViewMinOutput() const;`
- L29 _public prototype_ `float GetViewMaxOutput() const;`
- L30 _public prototype_ `void SetOutputViewRange(float InViewMinOutput, float InViewMaxOutput);`
- L32 _public prototype_ `bool GetIsGradientVisible() const;`
- L33 _public prototype_ `void SetIsGradientVisible(bool bInIsGradientVisible);`
- L35 _public prototype_ `float GetTimelineLength() const;`
- L37 _public prototype_ `float GetHeight() const;`
- L38 _public prototype_ `void SetHeight(float InHeight);`
- L41 _private member_ `float ViewMinInput;`
- L42 _private member_ `float ViewMaxInput;`
- L43 _private member_ `float ViewMinOutput;`
- L44 _private member_ `float ViewMaxOutput;`
- L45 _private member_ `bool bIsGradientVisible;`
- L46 _private member_ `bool bNeedsInitializeView;`
- L47 _private member_ `float Height;`

#### class `FNiagaraEditorWidgetsModule`  
`class FNiagaraEditorWidgetsModule : public IModuleInterface`  
_L51-85_
- inherits: `IModuleInterface`
- desc: A module containing widgets for editing niagara data.
- L69 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L70 _public prototype_ `virtual void ShutdownModule() override;`
- L72 _public prototype_ `static FNiagaraEditorWidgetsModule& Get();`
- L74 _public prototype_ `TSharedRef<FNiagaraStackCurveEditorOptions> GetOrCreateStackCurveEditorOptionsForObject(UObject* Object, float DefaultHeight);`
- L77 _private prototype_ `void ReinitializeStyle();`
- L80 _private member_ `TMap<FObjectKey, TSharedRef<FNiagaraStackCurveEditorOptions>> ObjectToStackCurveEditorOptionsMap;`
- L82 _private member_ `TSharedPtr<FNiagaraEditorWidgetProvider> WidgetProvider;`
- L84 _private member_ `IConsoleCommand* ReinitializeStyleCommand;`

#### class `FNiagaraEditorWidgetsModule::FNiagaraEditorWidgetProvider`  
`class FNiagaraEditorWidgetProvider : public INiagaraEditorWidgetProvider`  
_L54-65_
- inherits: `INiagaraEditorWidgetProvider`
- L57 _public prototype_ `virtual TSharedRef<SWidget> CreateStackView(UNiagaraStackViewModel& StackViewModel) const override;`
- L58 _public prototype_ `virtual TSharedRef<SWidget> CreateSystemOverview(TSharedRef<FNiagaraSystemViewModel> SystemViewModel, const FAssetData& EditedAsset) const override;`
- L59 _public prototype_ `virtual TSharedRef<SWidget> CreateStackIssueIcon(UNiagaraStackViewModel& StackViewModel, UNiagaraStackEntry& StackEntry) const override;`
- L60 _public prototype_ `virtual TSharedRef<SWidget> CreateScriptScratchPadManager(UNiagaraScratchPadViewModel& ScriptScratchPadViewModel) const override;`
- L61 _public prototype_ `virtual TSharedRef<SWidget> CreateCurveOverview(TSharedRef<FNiagaraSystemViewModel> SystemViewModel) const override;`
- L62 _public prototype_ `virtual TSharedRef<SWidget> CreateCurveKeySelector(TSharedPtr<FCurveEditor> InCurveEditor, const TArray<FCurveEditorTreeItemID>& InCurveTreeItemIds, TSharedPtr<SCurveEditorTree> InCurveEditorTree) const override;`
- L63 _public prototype_ `virtual TSharedRef<SWidget> CreateCurveThumbnail(const FRichCurve& Curve) const override;`
- L64 _public prototype_ `virtual FLinearColor GetColorForExecutionCategory(FName ExecutionCategory) const override;`
