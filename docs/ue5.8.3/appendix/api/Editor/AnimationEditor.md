# Editor / AnimationEditor

- module root: `Source/Editor/AnimationEditor`
- headers: 6; symbols: 130
- symbol kinds: class=6, delegate=3, enum=1, enumerator=3, externvar=13, function=10, member=30, namespace=2, prototype=61, struct=1
- DynamicallyLoadedModuleNames: PropertyEditor, SequenceRecorder
- PrivateDependencyModuleNames: AnimGraph, Core, CoreUObject, EditorFramework, Engine, InputCore, Kismet, Persona, SkeletonEditor, Slate, SlateCore, ToolMenus, TypedElementRuntime, UnrealEd
- PrivateIncludePathModuleNames: PropertyEditor, SequenceRecorder
- PublicIncludePathModuleNames: Persona

### `Source/Editor/AnimationEditor/Private/AnimationEditor.h` (Private)


#### class `FAnimationEditor`  
`class FAnimationEditor : public IAnimationEditor, public FGCObject, public FTickableEditorObject`  
_L63-228_
- inherits: `IAnimationEditor,FGCObject,FTickableEditorObject`
- L66 _public prototype_ `virtual ~FAnimationEditor();`
- L69 _public prototype_ `void InitAnimationEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class UAnimationAsset* InAnimationAsset);` — Edits the specified Skeleton object
- L72 _public prototype_ `virtual void SetAnimationAsset(UAnimationAsset* AnimAsset) override;` — IAnimationEditor interface
- L73 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const override;`
- L74 _public prototype_ `virtual void EditCurves(UAnimSequenceBase* InAnimSequence, const TArray<FCurveEditInfo>& InCurveInfo, const TSharedPtr<ITimeSliderController>& InExternalTimeSliderController) override;`
- L75 _public prototype_ `virtual void StopEditingCurves(const TArray<FCurveEditInfo>& InCurveInfo) override;`
- L76 _public function_ `virtual FOnAnimationEditorObjectsSelected& OnAnimationEditorObjectsSelected() override`
- L79 _public function_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L82 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L83 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L84 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L85 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L86 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L87 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L88 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L91 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject Interface
- L92 _public prototype_ `virtual TStatId GetStatId() const override;`
- L93 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L96 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L102 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L103 _public function_ `virtual FString GetReferencerName() const override`
- L109 _public function_ `TSharedRef<class ISkeletonTree> GetSkeletonTree() const` — Get the skeleton tree widget
- L111 _public prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L113 _public prototype_ `UObject* HandleGetAsset();`
- L115 _public prototype_ `void HandleOpenNewAsset(UObject* InNewAsset);`
- L117 _public prototype_ `void HandleAnimationSequenceBrowserCreated(const TSharedRef<class IAnimationSequenceBrowser>& InSequenceBrowser);`
- L119 _public prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L121 _public prototype_ `void HandleObjectSelected(UObject* InObject);`
- L123 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L126 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE) override;` — FAssetEditorToolkit interface
- L127 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget) override;`
- L139 _private prototype_ `void HandleSectionsChanged();`
- L141 _private prototype_ `bool HasValidAnimationSequence() const;`
- L143 _private prototype_ `bool CanSetKey() const;`
- L145 _private prototype_ `void OnSetKey();`
- L147 _private prototype_ `void OnReimportAnimation(bool bWithDialog);`
- L149 _private prototype_ `void OnApplyCompression();`
- L151 _private prototype_ `void OnExportToFBX(const EExportSourceOption Option);`
- L153 _private prototype_ `bool ExportToFBX(const TArray<UObject*> NewAssets, bool bRecordAnimation);` — Return true mean the asset was exported, false it was cancel or it fail
- L155 _private prototype_ `void OnAddLoopingInterpolation();`
- L156 _private prototype_ `void OnRemoveBoneTrack();`
- L158 _private prototype_ `TSharedRef< SWidget > GenerateExportAssetMenu() const;`
- L160 _private prototype_ `void FillExportAssetMenu(FMenuBuilder& MenuBuilder) const;`
- L162 _private prototype_ `void CopyCurveToSoundWave(const FAssetData& SoundWaveAssetData) const;`
- L164 _private prototype_ `void ConditionalRefreshEditor(UObject* InObject);`
- L166 _private prototype_ `void HandlePostReimport(UObject* InObject, bool bSuccess);`
- L168 _private prototype_ `void HandlePostImport(class UFactory* InFactory, UObject* InObject);`
- L171 _private prototype_ `void ExtendMenu();`
- L173 _private prototype_ `void ExtendToolbar();`
- L175 _private prototype_ `void BindCommands();`
- L177 _private prototype_ `TSharedPtr<SDockTab> OpenNewAnimationDocumentTab(UAnimationAsset* InAnimAsset);`
- L179 _private prototype_ `bool RecordMeshToAnimation(USkeletalMeshComponent* PreviewComponent, UAnimSequence* NewAsset) const;`
- L181 _private prototype_ `static TSharedPtr<FAnimationEditor> GetAnimationEditor(const FToolMenuContext& InMenuContext);`
- L183 _private prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder) const;`
- L187 _public member_ `FSimpleMulticastDelegate OnLODChanged;` — Multicast delegate fired on global undo/redo
- L190 _public member_ `FSimpleMulticastDelegate OnSectionsChanged;` — Multicast delegate fired on sections changing
- L193 _public member_ `FOnAnimationEditorObjectsSelected OnAnimationEditorObjectsSelectedDelegate;` — Multicast delegate fired on selecting objects
- L197 _private member_ `TObjectPtr<UAnimationAsset> AnimationAsset;` — The animation asset we are editing
- L200 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender
- L203 _private member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender
- L206 _private member_ `TSharedPtr<class IPersonaToolkit> PersonaToolkit;` — Persona toolkit
- L209 _private member_ `TSharedPtr<class ISkeletonTree> SkeletonTree;` — Skeleton tree
- L212 _private member_ `TSharedPtr<class IPersonaViewport> Viewport;` — Viewport
- L215 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Details panel
- L218 _private member_ `TWeakPtr<SDockTab> SharedAnimDocumentTab;` — The animation document currently being edited
- L221 _private member_ `TWeakPtr<SDockTab> AnimCurveDocumentTab;` — The animation document's curves that are currently being edited
- L224 _private member_ `TWeakPtr<class IAnimationSequenceBrowser> SequenceBrowser;` — Sequence Browser
- L227 _private member_ `TWeakPtr<IAnimSequenceCurveEditor> CurveEditor;` — The anim sequence curve editor

#### enum `FAnimationEditor::EExportSourceOption`  
`enum class EExportSourceOption : uint8`  
_L132-137_
- desc: Options for asset export
- L134 _public enumerator_ `CurrentAnimation_AnimData`
- L135 _public enumerator_ `CurrentAnimation_PreviewMesh`
- L136 _public enumerator_ `Max`

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace AnimationEditorModes`
- L43 _externvar_ `extern const FName AnimationEditorMode;` (scope `AnimationEditorModes`) — Mode identifiers
- L46 _namespace_ `namespace AnimationEditorTabs`
- L49 _externvar_ `extern const FName DetailsTab;` (scope `AnimationEditorTabs`) — Tab identifiers
- L50 _externvar_ `extern const FName SkeletonTreeTab;` (scope `AnimationEditorTabs`)
- L51 _externvar_ `extern const FName ViewportTab;` (scope `AnimationEditorTabs`)
- L52 _externvar_ `extern const FName AdvancedPreviewTab;` (scope `AnimationEditorTabs`)
- L53 _externvar_ `extern const FName DocumentTab;` (scope `AnimationEditorTabs`)
- L54 _externvar_ `extern const FName CurveEditorTab;` (scope `AnimationEditorTabs`)
- L55 _externvar_ `extern const FName AssetBrowserTab;` (scope `AnimationEditorTabs`)
- L56 _externvar_ `extern const FName AssetDetailsTab;` (scope `AnimationEditorTabs`)
- L57 _externvar_ `extern const FName CurveNamesTab;` (scope `AnimationEditorTabs`)
- L58 _externvar_ `extern const FName SlotNamesTab;` (scope `AnimationEditorTabs`)
- L59 _externvar_ `extern const FName AnimMontageSectionsTab;` (scope `AnimationEditorTabs`)
- L60 _externvar_ `extern const FName FindReplaceTab;` (scope `AnimationEditorTabs`)

### `Source/Editor/AnimationEditor/Private/AnimationEditorCommands.h` (Private)


#### class `FAnimationEditorCommands`  
`class FAnimationEditorCommands : public TCommands<FAnimationEditorCommands>`  
_L15-43_
- inherits: `TCommands<FAnimationEditorCommands>`
- L18 _public function_ `FAnimationEditorCommands() : TCommands<FAnimationEditorCommands>(TEXT("AnimationEditor"), NSLOCTEXT("Contexts", "AnimationEditor", "Animation Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ImportAnimation;` — import animation
- L29 _public member_ `TSharedPtr<FUICommandInfo> ReimportAnimation;` — reimport animation
- L30 _public member_ `TSharedPtr<FUICommandInfo> ReimportAnimationWithDialog;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ApplyCompression;` — apply compression
- L34 _public member_ `TSharedPtr<FUICommandInfo> ExportToFBX_AnimData;` — export to FBX
- L36 _public member_ `TSharedPtr<FUICommandInfo> ExportToFBX_PreviewMesh;` — export to FBX
- L38 _public member_ `TSharedPtr<FUICommandInfo> AddLoopingInterpolation;` — Add looping interpolation
- L40 _public member_ `TSharedPtr<FUICommandInfo> SetKey;` — set key for bone track
- L42 _public member_ `TSharedPtr<FUICommandInfo> RemoveBoneTracks;` — Remove bone tracks

### `Source/Editor/AnimationEditor/Private/AnimationEditorMode.h` (Private)


#### class `FAnimationEditorMode`  
`class FAnimationEditorMode : public FApplicationMode`  
_L12-19_
- inherits: `FApplicationMode`
- L15 _public prototype_ `FAnimationEditorMode(TSharedRef<class FWorkflowCentricApplication> InHostingApp, TSharedRef<class ISkeletonTree> InSkeletonTree);`
- L18 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface

### `Source/Editor/AnimationEditor/Public/AnimationToolMenuContext.h` (Public)


#### class `UAnimationToolMenuContext`  
`class UAnimationToolMenuContext : public UObject`  
_L12-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public member_ `TWeakPtr<IAnimationEditor> AnimationEditor;`

### `Source/Editor/AnimationEditor/Public/IAnimationEditor.h` (Public)


#### class `IAnimationEditor`  
`class IAnimationEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit`  
_L18-66_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit`
- L22 _public prototype_ `virtual void SetAnimationAsset(UAnimationAsset* AnimAsset) = 0;` — Set the animation asset of the editor.
- L25 _public prototype_ `virtual IAnimationSequenceBrowser* GetAssetBrowser() const = 0;` — Get the asset browser we host
- L59 _public prototype_ `virtual void EditCurves(UAnimSequenceBase* InAnimSequence, const TArray<FCurveEditInfo>& InCurveInfo, const TSharedPtr<ITimeSliderController>& InExternalTimeSliderController) = 0;` — Edit the specified curves on the specified sequence
- L62 _public prototype_ `virtual void StopEditingCurves(const TArray<FCurveEditInfo>& InCurveInfo) = 0;` — Stop editing the specified curves
- L65 _public prototype_ `virtual FOnAnimationEditorObjectsSelected& OnAnimationEditorObjectsSelected() = 0;` — Multicast delegate fired on selecting objects

#### struct `IAnimationEditor::FCurveEditInfo`  
`struct FCurveEditInfo`  
_L28-56_
- desc: Support structure for EditCurves
- L30 _public function_ `FCurveEditInfo(const FText& InCurveDisplayName, const FLinearColor& InCurveColor, const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex, FSimpleDelegate OnCurveModified = FSimpleDelegate()) : CurveDisplayName(InCurveDisplayName) , CurveColor(InCurveColor) , CurveName(InName) , Type(InType) , CurveIndex(InCurveIndex) , OnCurveModified(OnCurveModified)`
- L39 _public function_ `FCurveEditInfo(const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex) : CurveName(InName) , Type(InType) , CurveIndex(InCurveIndex)`
- L45 _public function_ `bool operator==(const FCurveEditInfo& InCurveEditInfo) const`
- L50 _public member_ `FText CurveDisplayName;`
- L51 _public member_ `FLinearColor CurveColor;`
- L52 _public member_ `FName CurveName;`
- L53 _public member_ `ERawCurveTrackTypes Type;`
- L54 _public member_ `int32 CurveIndex;`
- L55 _public member_ `FSimpleDelegate OnCurveModified;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationEditorObjectsSelected, const TArray<UObject*>& );`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationEditorObjectsSelected, const TArray<UObject*>& );`

### `Source/Editor/AnimationEditor/Public/IAnimationEditorModule.h` (Public)


#### class `IAnimationEditorModule`  
`class IAnimationEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L14-23_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L18 _public prototype_ `virtual TSharedRef<IAnimationEditor> CreateAnimationEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class UAnimationAsset* InAnimationAsset) = 0;` — Creates a new skeleton editor instance
- L21 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FAnimationEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<IAnimationEditor> );` — Get all toolbar extenders
- L22 _public prototype_ `virtual TArray<FAnimationEditorToolbarExtender>& GetAllAnimationEditorToolbarExtenders() = 0;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationEditor, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationEditor, Log, All);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FAnimationEditorToolbarExtender, const TSharedRef<FUICommandList> , TSharedRef<IAnimationEditor> );` — Get all toolbar extenders
