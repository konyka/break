# Plugins / HairStrandsEditor

- module root: `Plugins/Runtime/HairStrands/Source/HairStrandsEditor`
- headers: 32; symbols: 586
- symbol kinds: class=35, enum=2, enumerator=26, function=62, macro=7, member=137, namespace=2, prototype=309, struct=6
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetDefinition, AssetTools, CommonMenuExtensions, ContentBrowser, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, EditorFramework, EditorInteractiveToolsFramework, Engine, GeometryCache, HairCardGeneratorFramework, HairStrandsCore, InputCore, Json, JsonUtilities, LevelSequence, MainFrame, MovieScene, MovieSceneTools, Projects, PropertyEditor, RHI, RenderCore, Renderer, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: Analytics

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomAssetDetails.h` (Private)


#### enum `EMaterialPanelType`  
`enum class EMaterialPanelType`  
_L24-34_
- L26 _public enumerator_ `Strands`
- L27 _public enumerator_ `Cards`
- L28 _public enumerator_ `Meshes`
- L29 _public enumerator_ `Interpolation`
- L30 _public enumerator_ `LODs`
- L31 _public enumerator_ `Physics`
- L32 _public enumerator_ `Bindings`
- L33 _public enumerator_ `Dataflow`

#### class `FGroomRenderingDetails`  
`class FGroomRenderingDetails : public IDetailCustomization`  
_L36-120_
- inherits: `IDetailCustomization`
- L38 _private member_ `UGroomAsset* GroomAsset = nullptr;`
- L39 _private member_ `UGroomBindingAssetList* GroomBindingAssetList = nullptr;`
- L40 _private member_ `IGroomCustomAssetEditorToolkit* Toolkit = nullptr;`
- L43 _public prototype_ `FGroomRenderingDetails(IGroomCustomAssetEditorToolkit* InToolkit, EMaterialPanelType Type);`
- L44 _public prototype_ `~FGroomRenderingDetails();`
- L47 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(IGroomCustomAssetEditorToolkit* InToolkit, EMaterialPanelType Type);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L50 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L54 _private prototype_ `FName& GetMaterialSlotName(int32 GroupIndex);`
- L55 _private prototype_ `const FName& GetMaterialSlotName(int32 GroupIndex) const;`
- L56 _private prototype_ `int32 GetGroupCount() const;`
- L58 _private prototype_ `void AddNewGroupButton(IDetailCategoryBuilder& StrandsGroupFilesCategory, FProperty* Property, const FText& HeaderText);`
- L60 _private prototype_ `void ApplyChanges();`
- L61 _private prototype_ `void SetMaterialSlot(int32 GroupIndex, int32 MaterialIndex);`
- L62 _private prototype_ `TSharedRef<SWidget> OnGenerateStrandsMaterialMenuPicker(int32 GroupIndex);`
- L63 _private prototype_ `FText GetStrandsMaterialName(int32 GroupIndex) const;`
- L64 _private prototype_ `TSharedRef<SWidget> OnGenerateStrandsMaterialPicker(int32 GroupIndex, IDetailLayoutBuilder* DetailLayoutBuilder);`
- L65 _private prototype_ `bool IsStrandsMaterialPickerEnabled(int32 GroupIndex) const;`
- L68 _private prototype_ `void CustomizeStrandsGroupProperties(IDetailLayoutBuilder& DetailLayout, IDetailCategoryBuilder& StrandsGroupFilesCategory);` — Custom widget for material slot
- L69 _private prototype_ `void OnGenerateElementForHairGroup(TSharedRef<IPropertyHandle> StructProperty, int32 GroupIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L70 _private prototype_ `void OnGenerateElementForLODs(TSharedRef<IPropertyHandle> StructProperty, int32 LODIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout, int32 GroupIndex);`
- L71 _private prototype_ `void OnGenerateElementForBindingAsset(TSharedRef<IPropertyHandle> StructProperty, int32 BindingIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L74 _private prototype_ `void OnSetObject(const FAssetData& AssetData);` — Display custom thumbnail for material
- L75 _private prototype_ `FString OnGetObjectPath(int32 GroupIndex) const;`
- L76 _private prototype_ `bool GetReplaceVisibility(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L77 _private prototype_ `void OnResetToBaseClicked(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L78 _private prototype_ `TSharedRef<SWidget> CreateMaterialSwatch(const TSharedPtr<FAssetThumbnailPool>& ThumbnailPool, int32 GroupIndex);`
- L80 _private prototype_ `TSharedRef<SWidget> MakeGroupNameCustomization(int32 GroupIndex, const FLinearColor& GroupColor);`
- L81 _private prototype_ `TSharedRef<SWidget> MakeGroupNameButtonCustomization(int32 GroupIndex, FProperty* Property);`
- L83 _private prototype_ `FReply OnRemoveLODClicked(int32 GroupIndex, int32 LODIndex, FProperty* Property);`
- L84 _private prototype_ `FReply OnAddLODClicked(int32 GroupIndex, FProperty* Property);`
- L85 _private prototype_ `FReply OnRemoveGroupClicked(int32 GroupIndex, FProperty* Property);`
- L86 _private prototype_ `FReply OnAddGroup(FProperty* Property);`
- L87 _private prototype_ `FReply OnRefreshCards(int32 GroupIndex, FProperty* Property);`
- L88 _private prototype_ `FReply OnSaveCards(int32 GroupIndex, FProperty* Property);`
- L89 _private prototype_ `FReply OnGenerateCardDataUsingPlugin(int32 GroupIndex);`
- L90 _private prototype_ `FReply OnSelectBinding(int32 BindingIndex, FProperty* Property);`
- L91 _private prototype_ `void OnGroomLODTypeChanged();`
- L92 _private prototype_ `void OnGroomTextureLayoutChanged();`
- L94 _private prototype_ `void AddPropertySeparator(FName PropertyName, IDetailChildrenBuilder& ChildrenBuilder);`
- L95 _private prototype_ `void ExpandStructForLOD(TSharedRef<IPropertyHandle>& PropertyHandle, IDetailChildrenBuilder& ChildrenBuilder, int32 GroupIndex, int32 LODIndex, bool bOverrideReset);`
- L96 _private prototype_ `void ExpandStruct(TSharedPtr<IPropertyHandle>& PropertyHandle, IDetailChildrenBuilder& ChildrenBuilder, int32 GroupIndex, int32 LODIndex, bool bOverrideReset);`
- L97 _private prototype_ `void ExpandStruct(TSharedRef<IPropertyHandle>& PropertyHandle, IDetailChildrenBuilder& ChildrenBuilder, int32 GroupIndex, int32 LODIndex, bool bOverrideReset);`
- L98 _private prototype_ `IDetailPropertyRow& AddPropertyWithCustomReset(TSharedPtr<IPropertyHandle>& PropertyHandle, IDetailChildrenBuilder& Builder, int32 GroupIndex, int32 LODIndex);`
- L100 _private prototype_ `bool CommonResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex, int32 LODIndex, bool bSetValue);`
- L101 _private prototype_ `bool ShouldResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex, int32 LODInex);`
- L102 _private prototype_ `void ResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex, int32 LODIndex);`
- L105 _private member_ `IDetailLayoutBuilder* GroomDetailLayout = nullptr;`
- L106 _private member_ `EMaterialPanelType PanelType = EMaterialPanelType::Strands;`
- L107 _private member_ `bool bDeleteWarningConsumed;` — This prevent showing the delete material slot warning dialog more then once per editor session
- L110 _private prototype_ `void OnCopyGroupItem(int32 CurrentSlot, EMaterialPanelType InType);` — Copy/Paste group
- L111 _private prototype_ `bool OnCanCopyGroupItem(int32 CurrentSlot, EMaterialPanelType InType) const;`
- L112 _private prototype_ `void OnPasteGroupItem(int32 CurrentSlot, EMaterialPanelType InType);`
- L115 _private prototype_ `void OnCopyLODItem(int32 CurrentSlot, int32 InLODIndex);` — Copy/Paste LOD
- L116 _private prototype_ `bool OnCanCopyLODItem(int32 CurrentSlot, int32 InLODIndex) const;`
- L117 _private prototype_ `void OnPasteLODItem(int32 CurrentSlot, int32 InLODIndex);`
- L119 _private prototype_ `void CallPostEditChange(FProperty* PropertyChanged=nullptr);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomAssetThumbnailRenderer.h` (Private)


#### class `UGroomAssetThumbnailRenderer`  
`class UGroomAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L13-28_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L19 _public prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L20 _public prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L24 _public prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L27 _private member_ `TUniquePtr<FGroomAssetThumbnailScene> ThumbnailScene;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomAssetThumbnailScene.h` (Private)


#### class `FGroomAssetThumbnailScene`  
`class FGroomAssetThumbnailScene : public FThumbnailPreviewScene`  
_L9-27_
- inherits: `FThumbnailPreviewScene`
- L13 _public prototype_ `FGroomAssetThumbnailScene();` — Constructor
- L16 _public prototype_ `void SetGroomAsset(UGroomAsset* GroomAsset);` — Sets the groom asset to use in the next CreateView()
- L19 _public prototype_ `void CleanupSceneAfterThumbnailRender();`
- L22 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L26 _private member_ `TObjectPtr<AGroomActor> PreviewActor;` — The static mesh actor used to display all static mesh thumbnails

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomBindingAssetThumbnailRenderer.h` (Private)


#### class `UGroomBindingAssetThumbnailRenderer`  
`class UGroomBindingAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L14-30_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L20 _public prototype_ `virtual bool CanVisualizeAsset(UObject* Object);`
- L22 _public prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L26 _public prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L29 _private member_ `TUniquePtr<FGroomBindingAssetThumbnailScene> ThumbnailScene;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomBindingAssetThumbnailScene.h` (Private)


#### class `FGroomBindingAssetThumbnailScene`  
`class FGroomBindingAssetThumbnailScene : public FThumbnailPreviewScene`  
_L14-46_
- inherits: `FThumbnailPreviewScene`
- L18 _public prototype_ `FGroomBindingAssetThumbnailScene();` — Constructor
- L21 _public prototype_ `void SetGroomBindingAsset(UGroomBindingAsset* GroomBindingAsset);` — Sets the groom binding to use in the next CreateView()
- L24 _public prototype_ `void CleanupSceneAfterThumbnailRender();` — Sets the groom binding to use in the next CreateView()
- L28 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L30 _protected prototype_ `virtual bool ShouldClampOrbitZoom() const override;`
- L34 _private member_ `TObjectPtr<AGroomActor> PreviewGroomActor;` — The groom actor used to display all groom asset thumbnails
- L37 _private member_ `TObjectPtr<ASkeletalMeshActor> PreviewSkeletalMeshActor;` — The skeletal mesh actor for which the binding is created that will be previewed
- L40 _private member_ `TObjectPtr<AGeometryCacheActor> PreviewGeometryCacheActor;` — The geometry cache actor for which the binding is created that will be previewed
- L43 _private member_ `TObjectPtr<AActor> PreviewRootActor = nullptr;` — Actor used as the root of the scene for thumbnail
- L45 _private member_ `TWeakObjectPtr<UGroomBindingAsset> CachedBindingAsset;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomBindingDetailsCustomization.h` (Private)


#### struct `FGroomBindingAttributeSelection`  
`struct FGroomBindingAttributeSelection`  
_L11-15_
- L13 _public member_ `int32 SelectedBindingAttribute = INDEX_NONE;`
- L14 _public member_ `TArray<FName> BindingAttributeNames;`

#### class `FGroomBindingDetailsCustomization`  
`class FGroomBindingDetailsCustomization : public IDetailCustomization`  
_L17-25_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — End IDetailCustomization interface
- L24 _public member_ `FGroomBindingAttributeSelection BindingAttributeSelection;`

#### class `FGroomCreateBindingDetailsCustomization`  
`class FGroomCreateBindingDetailsCustomization : public IDetailCustomization`  
_L27-35_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L33 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — End IDetailCustomization interface
- L34 _public member_ `FGroomBindingAttributeSelection BindingAttributeSelection;`

#### class `FGroomHairGroomRemappingDetailsCustomization`  
`class FGroomHairGroomRemappingDetailsCustomization : public IDetailCustomization`  
_L37-45_
- inherits: `IDetailCustomization`
- L41 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L42 _public prototype_ `void OnGenerateElementForBindingAsset(TSharedRef<IPropertyHandle> StructProperty, int32 InIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout, UGroomHairGroupsMapping* InMapping);`
- L44 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — End IDetailCustomization interface

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomCacheImportSettingsCustomization.h` (Private)


#### class `FGroomCacheImportSettingsCustomization`  
`class FGroomCacheImportSettingsCustomization : public IPropertyTypeCustomization`  
_L8-24_
- inherits: `IPropertyTypeCustomization`
- L11 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L13 _public function_ `FGroomCacheImportSettingsCustomization() : Settings(nullptr)`
- L16 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — Begin IPropertyTypeCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _protected prototype_ `EVisibility ArePropertiesVisible(const int32 VisibleType) const;`
- L23 _protected member_ `struct FGroomCacheImportSettings* Settings;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomCacheTrackEditor.h` (Private)


#### class `FGroomCacheTrackEditor`  
`class FGroomCacheTrackEditor : public FMovieSceneTrackEditor`  
_L13-51_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for Geometry Cache tracks
- L21 _public prototype_ `FGroomCacheTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L24 _public prototype_ `virtual ~FGroomCacheTrackEditor() = default;` — Virtual destructor.
- L32 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L37 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L38 _public prototype_ `virtual void BuildObjectBindingTrackMenu(class FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L39 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L40 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L41 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L42 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L43 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L47 _private prototype_ `void BuildGroomCacheTrack(TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track);`
- L50 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, class UGroomComponent* GroomComp, UMovieSceneTrack* Track);` — Delegate for AnimatablePropertyChanged in AddKey

#### class `FGroomCacheSection`  
`class FGroomCacheSection : public ISequencerSection , public TSharedFromThis<FGroomCacheSection>`  
_L55-95_
- inherits: `ISequencerSection,TSharedFromThis<FGroomCacheSection>`
- desc: Class for animation sections
- L62 _public prototype_ `FGroomCacheSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L65 _public prototype_ `virtual ~FGroomCacheSection() = default;` — Virtual destructor.
- L71 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L72 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L73 _public prototype_ `virtual float GetSectionHeight() const override;`
- L74 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L75 _public prototype_ `virtual void BeginResizeSection() override;`
- L76 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L77 _public prototype_ `virtual void BeginSlipSection() override;`
- L78 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L79 _public prototype_ `virtual void BeginDilateSection() override;`
- L80 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L85 _private member_ `class UMovieSceneGroomCacheSection& Section;` — The section we are visualizing
- L88 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L91 _private member_ `FFrameNumber InitialFirstLoopStartOffsetDuringResize;` — Cached first loop start offset value valid only during resize
- L94 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomComponentDetailsCustomization.h` (Private)


#### class `FGroomComponentDetailsCustomization`  
`class FGroomComponentDetailsCustomization : public IDetailCustomization`  
_L19-41_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L30 _private member_ `TWeakObjectPtr<class UGroomComponent> GroomComponentPtr;`
- L31 _private member_ `IDetailLayoutBuilder* MyDetailLayout;`
- L33 _private prototype_ `void CustomizeDescGroupProperties(IDetailLayoutBuilder& DetailLayout, IDetailCategoryBuilder& StrandsGroupFilesCategory);`
- L34 _private prototype_ `void OnGenerateElementForHairGroup(TSharedRef<IPropertyHandle> StructProperty, int32 GroupIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L36 _private prototype_ `bool CommonResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex, bool bSetValue);`
- L37 _private prototype_ `bool ShouldResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex);`
- L38 _private prototype_ `void ResetToDefault(TSharedPtr<IPropertyHandle> ChildHandle, int32 GroupIndex);`
- L39 _private prototype_ `void AddPropertyWithCustomReset(TSharedPtr<IPropertyHandle>& PropertyHandle, IDetailChildrenBuilder& Builder, int32 GroupIndex);`
- L40 _private prototype_ `void OnGroomAssetChanged(IDetailLayoutBuilder* LayoutBuilder);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomCreateBindingOptionsWindow.h` (Private)


#### class `SGroomCreateBindingOptionsWindow`  
`class SGroomCreateBindingOptionsWindow : public SCompoundWidget`  
_L15-87_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SGroomCreateBindingOptionsWindow) : _BindingOptions(nullptr) , _WidgetWindow() , _FullPath() , _ButtonLabel()`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public prototype_ `static TSharedPtr<SGroomCreateBindingOptionsWindow> DisplayCreateBindingOptions(UGroomCreateBindingOptions* BindingOptions);`
- L37 _public function_ `FReply OnCreateBinding()`
- L47 _public function_ `FReply OnCancel()`
- L57 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L67 _public function_ `bool ShouldCreate() const`
- L72 _public function_ `SGroomCreateBindingOptionsWindow() : BindingOptions(nullptr) , bShouldCreate(false)`
- L79 _private prototype_ `bool CanCreateBinding() const;`
- L82 _private member_ `UGroomCreateBindingOptions* BindingOptions;`
- L83 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L84 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L85 _private member_ `TSharedPtr<SButton> ImportButton;`
- L86 _private member_ `bool bShouldCreate;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomCreateFollicleMaskOptionsWindow.h` (Private)


#### class `SGroomCreateFollicleMaskOptionsWindow`  
`class SGroomCreateFollicleMaskOptionsWindow : public SCompoundWidget`  
_L15-87_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SGroomCreateFollicleMaskOptionsWindow) : _FollicleMaskOptions(nullptr) , _WidgetWindow() , _FullPath() , _ButtonLabel()`
- L32 _public prototype_ `void Construct(const FArguments& InArgs);`
- L33 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L35 _public prototype_ `static TSharedPtr<SGroomCreateFollicleMaskOptionsWindow> DisplayCreateFollicleMaskOptions(UGroomCreateFollicleMaskOptions* FollicleMaskOptions);`
- L37 _public function_ `FReply OnCreateFollicleMask()`
- L47 _public function_ `FReply OnCancel()`
- L57 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L67 _public function_ `bool ShouldCreate() const`
- L72 _public function_ `SGroomCreateFollicleMaskOptionsWindow() : FollicleMaskOptions(nullptr) , bShouldCreate(false)`
- L79 _private prototype_ `bool CanCreateFollicleMask() const;`
- L82 _private member_ `UGroomCreateFollicleMaskOptions* FollicleMaskOptions;`
- L83 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L84 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L85 _private member_ `TSharedPtr<SButton> ImportButton;`
- L86 _private member_ `bool bShouldCreate;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomCreateStrandsTexturesOptionsWindow.h` (Private)


#### class `SGroomCreateStrandsTexturesOptionsWindow`  
`class SGroomCreateStrandsTexturesOptionsWindow : public SCompoundWidget`  
_L16-88_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SGroomCreateStrandsTexturesOptionsWindow) : _StrandsTexturesOptions(nullptr) , _WidgetWindow() , _FullPath() , _ButtonLabel()`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L36 _public prototype_ `static TSharedPtr<SGroomCreateStrandsTexturesOptionsWindow> DisplayCreateStrandsTexturesOptions(UGroomCreateStrandsTexturesOptions* StrandsTexturesOptions);`
- L38 _public function_ `FReply OnCreateStrandsTextures()`
- L48 _public function_ `FReply OnCancel()`
- L58 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L68 _public function_ `bool ShouldCreate() const`
- L73 _public function_ `SGroomCreateStrandsTexturesOptionsWindow() : StrandsTexturesOptions(nullptr) , bShouldCreate(false)`
- L80 _private prototype_ `bool CanCreateStrandsTextures() const;`
- L83 _private member_ `UGroomCreateStrandsTexturesOptions* StrandsTexturesOptions;`
- L84 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L85 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L86 _private member_ `TSharedPtr<SButton> ImportButton;`
- L87 _private member_ `bool bShouldCreate;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomImportOptionsWindow.h` (Private)


#### enum `EHairDescriptionStatus`  
`enum class EHairDescriptionStatus : uint32`  
_L22-43_
- reflection: `UENUM()`
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `GroomValid = 1u<<1`
- L26 _public enumerator_ `NoGroup = 1u<<2`
- L27 _public enumerator_ `NoCurve = 1u<<3`
- L28 _public enumerator_ `GroomCache = 1u<<4` — groom cache with unspecified groom asset
- L29 _public enumerator_ `GroomCacheCompatible = 1u<<5`
- L30 _public enumerator_ `GroomCacheIncompatible = 1u<<6`
- L31 _public enumerator_ `GuidesOnly = 1u<<7` — guides-only with unspecified groom asset
- L32 _public enumerator_ `GuidesOnlyCompatible = 1u<<8`
- L33 _public enumerator_ `GuidesOnlyIncompatible = 1u<<9`
- L34 _public enumerator_ `PointLimit = 1u<<10`
- L35 _public enumerator_ `CurveLimit = 1u<<11`
- L36 _public enumerator_ `InvalidPoint = 1u<<12`
- L37 _public enumerator_ `InvalidGroupMapping = 1u<<13`
- L38 _public enumerator_ `Unknown = 1u<<14`
- L40 _public enumerator_ `Warning = CurveLimit | PointLimit | InvalidPoint | InvalidGroupMapping`
- L41 _public enumerator_ `Error = NoCurve | NoGroup | GroomCacheIncompatible | GuidesOnlyIncompatible | GroomCache | GuidesOnly | Unknown`
- L42 _public enumerator_ `Valid = GroomValid | GroomCacheCompatible | GuidesOnlyCompatible`

#### struct `FGroomImportStatus`  
`struct FGroomImportStatus`  
_L46-52_
- L48 _public member_ `EHairDescriptionStatus Status;`
- L49 _public member_ `FSoftObjectPath GroomAsset;`
- L50 _public member_ `bool bImportGroomAssetState = false;`
- L51 _public member_ `bool bImportGroomCacheState = false;`

#### class `SGroomImportOptionsWindow`  
`class SGroomImportOptionsWindow : public SCompoundWidget`  
_L57-184_
- inherits: `SCompoundWidget`
- L60 _public function_ `SLATE_BEGIN_ARGS(SGroomImportOptionsWindow) : _ImportOptions(nullptr) , _GroomCacheImportOptions(nullptr) , _GroupsPreview(nullptr) , _GroupsMapping(nullptr) , _WidgetWindow() , _FullPath() , _ButtonLabel() , _bShowImportAllButton(false)`
- L82 _public prototype_ `void Construct(const FArguments& InArgs);`
- L83 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L85 _public prototype_ `static TSharedPtr<SGroomImportOptionsWindow> DisplayImportOptions( UGroomImportOptions* ImportOptions, UGroomCacheImportOptions* GroomCacheImportOptions, UGroomHairGroupsPreview* GroupsPreview, UGroomHairGroupsMapping* GroupsMapping, const FString& FilePath, bool bShowImportAllButton);`
- L93 _public prototype_ `static TSharedPtr<SGroomImportOptionsWindow> DisplayRebuildOptions( UGroomImportOptions* ImportOptions, UGroomHairGroupsPreview* GroupsPreview, UGroomHairGroupsMapping* GroupsMapping, const FString& FilePath);`
- L99 _public function_ `FReply OnImport()`
- L110 _public function_ `FReply OnImportAll()`
- L121 _public function_ `FReply OnCancel()`
- L132 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L142 _public function_ `bool ShouldImport() const`
- L147 _public function_ `bool ShouldImportAll() const`
- L152 _public function_ `SGroomImportOptionsWindow() : ImportOptions(nullptr) , GroomCacheImportOptions(nullptr) , GroupsPreview(nullptr) , GroupsMapping(nullptr)`
- L161 _private prototype_ `bool CanImport() const;`
- L162 _private prototype_ `void UpdateStatus(UGroomHairGroupsPreview* Description) const;`
- L163 _private prototype_ `FText GetStatusText() const;`
- L164 _private prototype_ `FSlateColor GetStatusColor() const;`
- L165 _private prototype_ `TSharedRef<SWidget> AddImportButtons(FText InMainButtonLabel, bool bShowImportAllButton);`
- L168 _private member_ `mutable FGroomImportStatus ImportStatus;` — Properties that are monitored for changes
- L171 _private member_ `UGroomImportOptions* ImportOptions;`
- L172 _private member_ `UGroomCacheImportOptions* GroomCacheImportOptions;`
- L173 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L174 _private member_ `TSharedPtr<class IDetailsView> GroomCacheDetailsView;`
- L175 _private member_ `TSharedPtr<class IDetailsView> DetailsView2;`
- L176 _private member_ `TSharedPtr<class IDetailsView> DetailsView3;`
- L177 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L178 _private member_ `TSharedPtr<SButton> ImportButton;`
- L179 _private member_ `bool bShouldImport = false;`
- L180 _private member_ `bool bShouldImportAll = false;`
- L182 _public member_ `UGroomHairGroupsPreview* GroupsPreview;`
- L183 _public member_ `UGroomHairGroupsMapping* GroupsMapping;`

#### Free symbols / members of external scopes

- L44 _prototype_ `ENUM_CLASS_FLAGS(EHairDescriptionStatus);`
- L54 _prototype_ `FGroomImportStatus GetGroomImportStatus(UGroomHairGroupsPreview* InDescription, UGroomCacheImportOptions* InGroomCacheImportOptions, UGroomHairGroupsMapping* InGroupMapping);`
- L55 _prototype_ `FText GetGroomImportStatusText(FGroomImportStatus In, bool bAddPrefix);`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomMaterialDetails.h` (Private)


#### class `FGroomMaterialDetails`  
`class FGroomMaterialDetails : public IDetailCustomization`  
_L20-176_
- inherits: `IDetailCustomization`
- L22 _private member_ `UGroomAsset* GroomAsset = nullptr;`
- L25 _public prototype_ `FGroomMaterialDetails(IGroomCustomAssetEditorToolkit* InToolkit);`
- L26 _public prototype_ `~FGroomMaterialDetails();`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(IGroomCustomAssetEditorToolkit* InToolkit);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L36 _private prototype_ `FReply AddMaterialSlot();`
- L38 _private prototype_ `FText GetMaterialArrayText() const;`
- L39 _private prototype_ `bool IsMaterialValid(int32 MaterialIndex) const;`
- L46 _private prototype_ `void OnGetMaterialsForArray(class IMaterialListBuilder& OutMaterials, int32 LODIndex);` — Called by the material list widget when we need to get new materials for the list @param OutMaterials	Handle to a material list builder that materials should be added to
- L56 _private prototype_ `void OnMaterialArrayChanged(UMaterialInterface* NewMaterial, UMaterialInterface* PrevMaterial, int32 SlotIndex, bool bReplaceAll, int32 LODIndex);` — Called when a user drags a new material over a list item to replace it @param NewMaterial	The material that should replace the existing material @param PrevMaterial	The material that should be replaced @param SlotIndex		The index of the slot on the component where materials should be replaces @param bReplaceAll	If true all materials in the slot should be replaced not just ones using PrevMaterial
- L64 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomNameWidgetsForSection(int32 LodIndex, int32 SectionIndex);` — Called by the material list widget on generating each name widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L72 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomSectionWidgetsForSection(int32 LODIndex, int32 SectionIndex);` — Called by the material list widget on generating each thumbnail widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L74 _private prototype_ `EVisibility ShowEnabledSectionDetail(int32 LodIndex, int32 SectionIndex) const;`
- L75 _private prototype_ `EVisibility ShowDisabledSectionDetail(int32 LodIndex, int32 SectionIndex) const;`
- L77 _private prototype_ `FText GetMaterialNameText(int32 MaterialIndex)const;`
- L78 _private prototype_ `void OnMaterialNameCommitted(const FText& InValue, ETextCommit::Type CommitType, int32 MaterialIndex);`
- L86 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomNameWidgetsForMaterialArray(UMaterialInterface* Material, int32 MaterialIndex);` — Called by the material list widget on generating name side content @param Material		The material that is being displayed @param MaterialIndex	The index of the material slot
- L94 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomMaterialWidgetsForMaterialArray(UMaterialInterface* Material, int32 MaterialIndex, int32 LODIndex);` — Called by the material list widget on generating each thumbnail widget @param Material		The material that is being displayed @param MaterialIndex	The index of the material slot
- L97 _private prototype_ `bool OnMaterialListDirty();` — If the material list is dirty this function will return true
- L99 _private prototype_ `bool CanDeleteMaterialSlot(int32 MaterialIndex) const;`
- L101 _private prototype_ `void OnDeleteMaterialSlot(int32 MaterialIndex);`
- L108 _private prototype_ `void OnMaterialSelectedChanged(ECheckBoxState NewState, int32 MaterialIndex);` — Handler for changing highlight status on a material @param MaterialIndex	The material index that is being selected
- L115 _private prototype_ `ECheckBoxState IsIsolateMaterialEnabled(int32 MaterialIndex) const;` — Handler for check box display based on whether the material is isolated @param MaterialIndex	The material index that is being isolate
- L122 _private prototype_ `void OnMaterialIsolatedChanged(ECheckBoxState NewState, int32 MaterialIndex);` — Handler for changing isolated status on a material @param MaterialIndex	The material index that is being isolate
- L130 _private prototype_ `ECheckBoxState IsSectionSelected(int32 SectionIndex) const;` — Handler for check box display based on whether the material is highlighted @param SectionIndex	The material section that is being tested
- L137 _private prototype_ `void OnSectionSelectedChanged(ECheckBoxState NewState, int32 SectionIndex);` — Handler for changing highlight status on a material @param SectionIndex	The material section that is being tested
- L144 _private prototype_ `ECheckBoxState IsIsolateSectionEnabled(int32 SectionIndex) const;` — Handler for check box display based on whether the material is isolated @param SectionIndex	The material section that is being tested
- L151 _private prototype_ `void OnSectionIsolatedChanged(ECheckBoxState NewState, int32 SectionIndex);` — Handler for changing isolated status on a material @param SectionIndex	The material section that is being tested
- L154 _private prototype_ `void AddMaterials(IDetailLayoutBuilder& DetailLayout);` — Creates the UI for Current LOD panel
- L156 _private prototype_ `FText GetMaterialSlotNameText(int32 MaterialIndex) const;`
- L158 _private prototype_ `void OnCopyMaterialList();`
- L159 _private prototype_ `bool OnCanCopyMaterialList() const;`
- L160 _private prototype_ `void OnPasteMaterialList();`
- L162 _private prototype_ `void OnCopyMaterialItem(int32 CurrentSlot);`
- L163 _private prototype_ `bool OnCanCopyMaterialItem(int32 CurrentSlot) const;`
- L164 _private prototype_ `void OnPasteMaterialItem(int32 CurrentSlot);`
- L166 _public prototype_ `void ApplyChanges();`
- L169 _private prototype_ `void CallPostEditChange(FProperty* PropertyChanged=nullptr);`
- L171 _private member_ `IDetailLayoutBuilder* GroomDetailLayout;`
- L175 _private member_ `bool bDeleteWarningConsumed;` — This prevent showing the delete material slot warning dialog more then once per editor session

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomActions.h` (Public)


#### class `UAssetDefinition_GroomAsset`  
`class UAssetDefinition_GroomAsset : public UAssetDefinitionDefault`  
_L12-50_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L23 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L25 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L30 _public function_ `virtual bool CanImport() const override`
- L35 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L44 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L46 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L49 _public prototype_ `void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomActorFactory.h` (Public)


#### class `UGroomActorFactory`  
`class UGroomActorFactory : public UActorFactory`  
_L15-25_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L20 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L21 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor) override;`
- L22 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L23 _private prototype_ `virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomBindingActions.h` (Public)


#### class `UAssetDefinition_GroomBindingAsset`  
`class UAssetDefinition_GroomBindingAsset : public UAssetDefinitionDefault`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomBindingFactory.h` (Public)


#### class `UGroomBindingFactory`  
`class UGroomBindingFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L17 _public prototype_ `UGroomBindingFactory();`
- L20 _public function_ `virtual bool ShouldShowInNewMenu() const` — Not shown in the Menu, only exposed for code/python access.
- L21 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomCacheActions.h` (Public)


#### class `UAssetDefinition_GroomCacheAsset`  
`class UAssetDefinition_GroomCacheAsset : public UAssetDefinitionDefault`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual bool CanImport() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L29 _public prototype_ `void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomCacheImporter.h` (Public)


#### struct `FGroomCacheImporter`  
`struct FGroomCacheImporter`  
_L18-24_
- L20 _public prototype_ `static TArray<UGroomCache*> ImportGroomCache(const FString& SourceFilename, TSharedPtr<IGroomTranslator> Translator, const FGroomAnimationInfo& InAnimInfo, FHairImportContext& HairImportContext, UGroomAsset* GroomAssetForCache, EGroomCacheImportType ImportType);`
- L21 _public prototype_ `static void SetupImportSettings(struct FGroomCacheImportSettings& ImportSettings, const FGroomAnimationInfo& AnimInfo);`
- L22 _public prototype_ `static void ApplyImportSettings(struct FGroomCacheImportSettings& ImportSettings, FGroomAnimationInfo& AnimInfo);`
- L23 _public prototype_ `static UGroomCache* ProcessToGroomCache(FGroomCacheProcessor& Processor, const FGroomAnimationInfo& AnimInfo, FHairImportContext& ImportContext, const FString& ObjectNameSuffix);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HAIRSTRANDSEDITOR_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomCustomAssetEditorToolkit.h` (Public)


#### class `IGroomCustomAssetEditorToolkit`  
`class IGroomCustomAssetEditorToolkit : public FAssetEditorToolkit`  
_L30-45_
- inherits: `FAssetEditorToolkit`
- L34 _public prototype_ `virtual UGroomAsset* GetCustomAsset() const = 0;` — Retrieves the current custom asset.
- L37 _public prototype_ `virtual void SetCustomAsset(UGroomAsset* InCustomAsset) = 0;` — Set the current custom asset.
- L40 _public prototype_ `virtual void PreviewBinding(int32 BindingIndex) = 0;` — Set preview of a particular binding.
- L42 _public prototype_ `virtual int32 GetActiveBindingIndex() const =0;`
- L44 _public function_ `virtual FGroomEditorStyle* GetSlateStyle() const`

#### class `FGroomCustomAssetEditorToolkit`  
`class FGroomCustomAssetEditorToolkit : public IGroomCustomAssetEditorToolkit`  
_L47-204_
- inherits: `IGroomCustomAssetEditorToolkit`
- L51 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L52 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L61 _public prototype_ `void InitCustomAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UGroomAsset* InCustomAsset);` — Edits the specified asset object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	InCustomAsset			The Custom Asset to Edit
- L63 _public prototype_ `FGroomCustomAssetEditorToolkit();`
- L66 _public prototype_ `virtual ~FGroomCustomAssetEditorToolkit();` — Destructor
- L69 _public prototype_ `virtual FName GetToolkitFName() const override;` — Begin IToolkit interface
- L70 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L71 _public prototype_ `virtual FText GetToolkitName() const override;`
- L72 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L73 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L74 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L75 _public function_ `virtual bool IsPrimaryEditor() const override`
- L76 _public prototype_ `virtual void OnClose() override;`
- L80 _public prototype_ `virtual UGroomAsset* GetCustomAsset() const override;` — Retrieves the current custom asset.
- L83 _public prototype_ `virtual void SetCustomAsset(UGroomAsset* InCustomAsset) override;` — Set the current custom asset.
- L86 _public prototype_ `virtual void PreviewBinding(int32 BindingIndex) override;` — Set preview of a particular binding.
- L89 _public prototype_ `virtual int32 GetActiveBindingIndex() const override;` — Return the index of the active binding.
- L92 _public prototype_ `FGroomEditorStyle* GetSlateStyle() const override;` — Return groom editor style.
- L97 _private prototype_ `void OnPlaySimulation();` — called when The Play simulation button is pressed
- L98 _private prototype_ `bool CanPlaySimulation() const;`
- L101 _private prototype_ `void OnPauseSimulation();` — Called when the pause simulation button is pressed
- L102 _private prototype_ `bool CanPauseSimulation() const;`
- L105 _private prototype_ `void OnResetSimulation();` — Called when the reset simulation button is pressed
- L106 _private prototype_ `bool CanResetSimulation() const;`
- L109 _private prototype_ `void OnPlayAnimation();` — Called when the play animation button is pressed
- L110 _private prototype_ `bool CanPlayAnimation() const;`
- L113 _private prototype_ `void OnStopAnimation();` — Called when the stop animation button is pressed
- L114 _private prototype_ `bool CanStopAnimation() const;`
- L117 _private prototype_ `void ExtendToolbar();` — Add buttons to to the toolbar
- L120 _private prototype_ `void DocPropChanged(UObject *, FPropertyChangedEvent &);` — THis should be called when the properties of the Document are changed
- L123 _private prototype_ `void OnSkeletalGroomTargetChanged(USkeletalMesh *NewTarget);` — THis is called when the groom target object changes and needs updating
- L126 _private prototype_ `bool OnShouldFilterAnimAsset(const FAssetData& AssetData);` — Return true if the animation asset should be filtered out (not compatible with the preview skel. mesh)
- L127 _private prototype_ `void OnObjectChangedAnimAsset(const FAssetData& AssetData);`
- L128 _private prototype_ `bool OnIsEnabledAnimAsset();`
- L129 _private prototype_ `FString GetCurrentAnimAssetPath() const;`
- L132 _private prototype_ `void InitPreviewComponents();` — create the custom components we need
- L135 _private prototype_ `void InitializeBindingAssetTabContent();` — Initialized the content of the binding tab
- L138 _private prototype_ `UGroomComponent* GetPreview_GroomComponent() const;` — return a pointer to the groom preview component
- L139 _private prototype_ `USkeletalMeshComponent* GetPreview_SkeletalMeshComponent() const;`
- L141 _private prototype_ `TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& Args);`
- L143 _private prototype_ `TSharedRef<SDockTab> SpawnTab_LODProperties(const FSpawnTabArgs& Args);`
- L144 _private prototype_ `TSharedRef<SDockTab> SpawnTab_InterpolationProperties(const FSpawnTabArgs& Args);`
- L145 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RenderingProperties(const FSpawnTabArgs& Args);`
- L146 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CardsProperties(const FSpawnTabArgs& Args);`
- L147 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MeshesProperties(const FSpawnTabArgs& Args);`
- L148 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MaterialProperties(const FSpawnTabArgs& Args);`
- L149 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PhysicsProperties(const FSpawnTabArgs& Args);`
- L150 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewGroomComponent(const FSpawnTabArgs& Args);`
- L151 _private prototype_ `TSharedRef<SDockTab> SpawnTab_BindingProperties(const FSpawnTabArgs& Args);`
- L152 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L153 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DataflowProperties(const FSpawnTabArgs& Args);`
- L158 _private member_ `TSharedPtr< SDockableTab > PropertiesTab;` — Dockable tab for properties
- L159 _private member_ `TSharedPtr< SGroomEditorViewport > ViewportTab;`
- L161 _private member_ `TSharedPtr<class IDetailsView> DetailView_LODProperties;`
- L162 _private member_ `TSharedPtr<class IDetailsView> DetailView_InterpolationProperties;`
- L163 _private member_ `TSharedPtr<class IDetailsView> DetailView_RenderingProperties;`
- L164 _private member_ `TSharedPtr<class IDetailsView> DetailView_CardsProperties;`
- L165 _private member_ `TSharedPtr<class IDetailsView> DetailView_MeshesProperties;`
- L166 _private member_ `TSharedPtr<class IDetailsView> DetailView_MaterialProperties;`
- L167 _private member_ `TSharedPtr<class IDetailsView> DetailView_PhysicsProperties;`
- L168 _private member_ `TSharedPtr<class IDetailsView> DetailView_PreviewGroomComponent;`
- L169 _private member_ `TSharedPtr<class IDetailsView> DetailView_BindingProperties;`
- L170 _private member_ `TSharedPtr<class IDetailsView> DetailView_PreviewSceneProperties;`
- L171 _private member_ `TSharedPtr<class IDetailsView> DetailView_DataflowProperties;`
- L173 _private member_ `static const FName ToolkitFName;`
- L174 _private member_ `static const FName TabId_Viewport;`
- L176 _private member_ `static const FName TabId_LODProperties;`
- L177 _private member_ `static const FName TabId_InterpolationProperties;`
- L178 _private member_ `static const FName TabId_RenderingProperties;`
- L179 _private member_ `static const FName TabId_CardsProperties;`
- L180 _private member_ `static const FName TabId_MeshesProperties;`
- L181 _private member_ `static const FName TabId_MaterialProperties;`
- L182 _private member_ `static const FName TabId_PhysicsProperties;`
- L183 _private member_ `static const FName TabId_PreviewGroomComponent;`
- L184 _private member_ `static const FName TabId_BindingProperties;`
- L185 _private member_ `static const FName TabId_PreviewSceneProperties;`
- L186 _private member_ `static const FName TabId_DataflowProperties;`
- L189 _private member_ `bool bIsTabManagerInitialized = false;`
- L190 _private member_ `int32 ActiveGroomBindingIndex = -1;`
- L191 _private member_ `TArray<FDelegateHandle> PropertyListenDelegatesAssetChanged;`
- L192 _private member_ `TArray<FDelegateHandle> PropertyListenDelegatesResourceChanged;`
- L193 _private member_ `TWeakObjectPtr<UGroomAsset> GroomAsset;`
- L194 _private member_ `TWeakObjectPtr<UGroomBindingAsset> GroomBindingAsset;`
- L195 _private member_ `TWeakObjectPtr<UGroomBindingAssetList> GroomBindingAssetList;`
- L197 _private member_ `TWeakObjectPtr<UGroomComponent> PreviewGroomComponent;`
- L198 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> PreviewSkeletalMeshComponent;`
- L199 _private member_ `TWeakObjectPtr<UAnimationAsset> PreviewSkeletalAnimationAsset;`
- L201 _private member_ `TSharedPtr<FAssetThumbnailPool> ThumbnailPool;`
- L203 _private member_ `TSharedPtr<FGroomEditorStyle> GroomEditorStyle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HAIRSTRANDSEDITOR_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomEditorCommands.h` (Public)


#### class `FGroomEditorCommands`  
`class FGroomEditorCommands : public TCommands<FGroomEditorCommands>`  
_L9-27_
- inherits: `TCommands<FGroomEditorCommands>`
- L13 _public prototype_ `FGroomEditorCommands();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> BeginHairPlaceTool;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> ResetSimulation;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> PauseSimulation;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> PlaySimulation;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> PlayAnimation;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> StopAnimation;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> Simulate;`
- L26 _public prototype_ `virtual void RegisterCommands() override;`

#### class `FGroomViewportLODCommands`  
`class FGroomViewportLODCommands : public TCommands<FGroomViewportLODCommands>`  
_L30-39_
- inherits: `TCommands<FGroomViewportLODCommands>`
- L33 _public prototype_ `FGroomViewportLODCommands();`
- L35 _public member_ `TSharedPtr< FUICommandInfo > LODAuto;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > LOD0;`
- L38 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomEditorMode.h` (Public)


#### class `UGroomEditorMode`  
`class UGroomEditorMode : public UBaseLegacyWidgetEdMode`  
_L10-47_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseLegacyWidgetEdMode`
- L15 _public member_ `const static FEditorModeID EM_GroomEditorModeId;`
- L17 _public prototype_ `UGroomEditorMode();`
- L25 _public prototype_ `virtual bool AllowWidgetMove() override;` — these disable the standard gizmo, which is probably want we want in these tools as we can't hit-test the standard gizmo...
- L27 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L34 _public prototype_ `virtual void Enter() override;` — called when we "start" this editor mode (ie switch to this tab)
- L37 _public prototype_ `virtual void Exit() override;` — called when we "end" this editor mode (ie switch to another tab)
- L45 _public member_ `class UViewportWorldInteraction* ViewportWorldInteraction;` — Cached pointer to the viewport world interaction object we're using to interact with mesh elements

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomEditorStyle.h` (Public)


#### class `FGroomEditorStyle`  
`class FGroomEditorStyle final : public FSlateStyleSet`  
_L16-57_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the Groom asset editor UI.
- L21 _public function_ `FGroomEditorStyle() : FSlateStyleSet(GetStyleName())` — Default constructor.
- L46 _public function_ `static FName GetStyleName()` — Return the name of this style
- L53 _public function_ `~FGroomEditorStyle()` — Destructor.

#### Free symbols / members of external scopes

- L10 _macro_ `#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)`
- L11 _macro_ `#define IMAGE_BRUSH_SVG( RelativePath, ... ) FSlateVectorImageBrush( RootToContentDir( RelativePath, TEXT(".svg") ), __VA_ARGS__ )`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomFactory.h` (Public)


#### class `UGroomFactory`  
`class UGroomFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L17 _public prototype_ `UGroomFactory();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L21 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/HairStrandsEditor.h` (Public)


#### class `FGroomEditor`  
`class FGroomEditor : public IModuleInterface`  
_L22-70_
- inherits: `IModuleInterface`
- desc: Implements the HairStrands module
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public function_ `virtual bool SupportsDynamicReloading() override`
- L32 _public prototype_ `void OnPostEngineInit();`
- L33 _public prototype_ `void OnPreviewPlatformChanged(EShaderPlatform NewShaderPlatform);`
- L34 _public prototype_ `void OnPreExit();`
- L36 _public function_ `static inline FGroomEditor& Get()`
- L44 _public function_ `template <typename TranslatorType> void RegisterHairTranslator()` — Register HairStrandsTranslator to add support for import by the HairStandsFactory
- L53 _public prototype_ `TArray<TSharedPtr<IGroomTranslator>> GetHairTranslators();` — Get new instances of HairStrandsTranslators
- L56 _private prototype_ `void RegisterMenus();`
- L58 _private member_ `TArray<TFunction<TSharedPtr<IGroomTranslator>()>> TranslatorSpawners;`
- L60 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`
- L62 _private member_ `FDelegateHandle TrackEditorBindingHandle;`
- L63 _private member_ `FDelegateHandle PreviewPlatformChangedHandle;`
- L64 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;`
- L65 _private member_ `FDelegateHandle DataflowMenusHandle;`
- L69 _public member_ `static FName GroomEditorAppIdentifier;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HAIRSTRANDSEDITOR_API`
- L15 _macro_ `#define HAIRSTRANDSEDITOR_MODULE_NAME TEXT("HairStrandsEditor")`
- L47 _function_ `` (scope `FGroomEditor::RegisterHairTranslator`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/HairStrandsFactory.h` (Public)


#### struct `UE::Groom::FGroomDataflowTemplateData`  
`struct FGroomDataflowTemplateData`  
_L16-32_
- L19 _public member_ `FString TemplateName;` — Dataflow template name
- L22 _public member_ `FString TemplateTitle;` — Dataflow template title
- L25 _public member_ `FString TemplateTooltip;` — Dataflow template tooltip
- L28 _public member_ `FString TemplatePath;` — Dataflow template asset path
- L31 _public member_ `bool bIsPrimaryTemplate = false;` — Template primary flag

#### class `UHairStrandsFactory`  
`class UHairStrandsFactory : public UFactory`  
_L57-84_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for UHairStrands objects.
- L63 _public prototype_ `UHairStrandsFactory(const FObjectInitializer& ObjectInitializer);`
- L66 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L68 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L69 _public prototype_ `virtual void GetSupportedFileExtensions(TArray<FString>& OutExtensions) const override;`
- L70 _public prototype_ `virtual void CleanUp() override;`
- L74 _protected prototype_ `void InitTranslators();`
- L76 _protected prototype_ `TSharedPtr<IGroomTranslator> GetTranslator(const FString& Filename);`
- L78 _protected member_ `class UGroomImportOptions* ImportOptions;`
- L79 _protected member_ `class UGroomCacheImportOptions* GroomCacheImportOptions;`
- L82 _private member_ `TArray<TSharedPtr<IGroomTranslator>> Translators;`
- L83 _private member_ `bool bImportAll = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Groom` (scope `UE`)
- L35 _prototype_ `TArray<SMessageDialog::FButton> BuildGroomDataflowTemplateButtons(TFunction<void(FString)> OnButtonClicked);` (scope `UE::Groom`) — Build dataflow template buttons
- L38 _prototype_ `void RegisterGroomDataflowTemplate(const FGroomDataflowTemplateData& DataflowTemplate);` (scope `UE::Groom`) — Register dataflow template to the manager
- L41 _prototype_ `void UnregisterGroomDataflowTemplate(const FString& TemplateName);` (scope `UE::Groom`) — Unregister dataflow template to the manager
- L44 _prototype_ `void RegisterGroomDataflowTemplatePath(const FString& DataflowTemplatePath);` (scope `UE::Groom`) — Register a dataflow template path to the manager. this will be used to dynamically load template from it whenever the list of templates is requested
- L47 _prototype_ `void UnregisterGroomDataflowTemplatePath(const FString& DataflowTemplatePath);` (scope `UE::Groom`) — Unregister a dataflow template path from the manager
- L50 _prototype_ `bool BuildGroomDataflowAsset(UGroomAsset* GroomAsset);` (scope `UE::Groom`) — Build groom dataflow asset from templates

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/HairStrandsImporter.h` (Public)


#### struct `FHairImportContext`  
`struct FHairImportContext`  
_L15-24_
- L17 _public prototype_ `FHairImportContext(UGroomImportOptions* InImportOptions, UObject* InParent = nullptr, UClass* InClass = nullptr, FName InName = FName(), EObjectFlags InFlags = EObjectFlags::RF_NoFlags);`
- L19 _public member_ `UGroomImportOptions* ImportOptions;`
- L20 _public member_ `UObject* Parent;`
- L21 _public member_ `UClass* Class;`
- L22 _public member_ `FName Name;`
- L23 _public member_ `EObjectFlags Flags;`

#### struct `FHairStrandsImporter`  
`struct FHairStrandsImporter`  
_L26-29_
- L28 _public prototype_ `static UGroomAsset* ImportHair(const FHairImportContext& ImportContext, FHairDescription& HairDescription, UGroomAsset* ExistingHair = nullptr, const UGroomHairGroupsMapping* GroupsMapping=nullptr);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HAIRSTRANDSEDITOR_API`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/HairStrandsTranslator.h` (Public)


#### class `IGroomTranslator`  
`class IGroomTranslator`  
_L7-42_
- L10 _public prototype_ `virtual ~IGroomTranslator() = default;`
- L13 _public prototype_ `virtual bool Translate(const FString& FilePath, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings) = 0;` — Translate a given file into a HairDescription; return true if successful
- L16 _public prototype_ `virtual bool CanTranslate(const FString& FilePath) = 0;` — Return true if a given file can be translated (by checking its content if necessary)
- L19 _public prototype_ `virtual bool IsFileExtensionSupported(const FString& FileExtension) const = 0;` — Return true if a given file extension is supported by the translator
- L22 _public prototype_ `virtual FString GetSupportedFormat() const = 0;` — Return the file format supported by the translator in the form "ext;file format description"
- L25 _public function_ `virtual bool Translate(const FString& FilePath, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings, struct FGroomAnimationInfo* OutAnimInfo)` — Translate a given file into a HairDescription with info about Groom animation if OutAnimInfo is not null; return true if successful
- L31 _public function_ `virtual bool BeginTranslation(const FString& FilePath)` — Open a file for multiple translations at different frame indices
- L35 _public function_ `virtual bool Translate(uint32 FrameIndex, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings)` — `UE_DEPRECATED(5.0, "Translate by frame index is deprecated. Use Translate by frame time instead.")` — Translate a given file into a HairDescription at the requested frame index; return true if successful
- L38 _public function_ `virtual bool Translate(float FrameTime, FHairDescription& OutHairDescription, const struct FGroomConversionSettings& ConversionSettings)` — Translate a given file into a HairDescription at the requested frame time (in seconds); return true if successful
- L41 _public function_ `virtual void EndTranslation()` — Clean up after finishing translations

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/ReimportGroomCacheFactory.h` (Public)


#### class `UReimportGroomCacheFactory`  
`class UReimportGroomCacheFactory : public UHairStrandsFactory, public FReimportHandler`  
_L11-25_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UHairStrandsFactory,FReimportHandler`
- L17 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L21 _public prototype_ `virtual int32 GetPriority() const override;`
- L22 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L23 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L24 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/ReimportHairStrandsFactory.h` (Public)


#### class `UReimportHairStrandsFactory`  
`class UReimportHairStrandsFactory : public UHairStrandsFactory, public FReimportHandler`  
_L11-25_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UHairStrandsFactory,FReimportHandler`
- L17 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L21 _public prototype_ `virtual int32 GetPriority() const override;`
- L22 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L23 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L24 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/Widgets/SGroomEditorViewport.h` (Public)


#### class `SGroomEditorViewport`  
`class SGroomEditorViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider, public IPreviewLODController`  
_L25-102_
- inherits: `SEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider,IPreviewLODController`
- desc: Material Editor Preview viewport widget
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L32 _public function_ `virtual FString GetReferencerName() const override`
- L37 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L40 _public prototype_ `void TogglePreviewGrid();` — Event handlers
- L41 _public prototype_ `bool IsTogglePreviewGridChecked() const;`
- L44 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L45 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L46 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L50 _public prototype_ `void SetGroomComponent(UGroomComponent* GroomComponent);` — Set the component to preview
- L53 _public prototype_ `void SetStaticMeshComponent(UStaticMeshComponent *StaticGroomTarget);` — set the mesh on which we are grooming
- L56 _public prototype_ `void SetSkeletalMeshComponent(USkeletalMeshComponent *SkeletalGroomTarget);` — set the mesh on which we are grooming
- L59 _public prototype_ `virtual int32 GetCurrentLOD() const override;` — IPreviewLODController interface
- L60 _public prototype_ `virtual int32 GetLODCount() const override;`
- L61 _public prototype_ `virtual bool IsLODSelected(int32 LODIndex) const override;`
- L62 _public prototype_ `virtual void SetLODLevel(int32 LODIndex) override;`
- L63 _public prototype_ `virtual void FillLODCommands(TArray<TSharedPtr<FUICommandInfo>>& Commands) override;`
- L64 _public function_ `virtual int32 GetAutoLODStartingIndex() const override`
- L67 _public function_ `TSharedPtr<class FAdvancedPreviewScene> GetAdvancedPreviewScene()`
- L72 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L73 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L74 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L75 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L76 _protected prototype_ `virtual void BindCommands() override;`
- L77 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L81 _private prototype_ `bool IsVisible() const override;`
- L83 _private prototype_ `void RefreshViewport();`
- L87 _private member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L90 _private member_ `TSharedPtr<class FGroomEditorViewportClient> SystemViewportClient;` — Level viewport client
- L93 _private member_ `TSharedPtr<class FAdvancedPreviewScene> AdvancedPreviewScene;` — Preview Scene - uses advanced preview settings
- L95 _private member_ `TObjectPtr<class UGroomComponent> GroomComponent;`
- L96 _private member_ `TObjectPtr<class UStaticMeshComponent> StaticGroomTarget;`
- L97 _private member_ `class USkeletalMeshComponent *SkeletalGroomTarget;`
- L100 _private member_ `bool bShowGrid;` — If true, render grid the preview scene.
