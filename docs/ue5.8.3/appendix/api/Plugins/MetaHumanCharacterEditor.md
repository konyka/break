# Plugins / MetaHumanCharacterEditor

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor`
- headers: 109; symbols: 3999
- symbol kinds: class=194, delegate=63, enum=37, enumerator=140, function=205, macro=4, member=1205, namespace=37, prototype=2046, struct=58, typedef=5, variable=5
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ChaosClothAssetEngine, ChaosOutfitAssetEngine, ClassViewer, CommonMenuExtensions, ContentBrowser, ContentBrowserData, ControlRig, ControlRigDeveloper, ControlRigEditor, Core, CoreUObject, DNACalibModule, DataflowEngine, DerivedDataCache, DesktopWidgets, DeveloperSettings, DirectoryWatcher, EditorFramework, EditorInteractiveToolsFramework, EditorScriptingUtilities, EditorSubsystem, EditorWidgets, Engine, EngineSettings, FileUtilities, GeometryCore, GeometryFramework, GeometryScriptingCore, GeometryScriptingEditor, HTTP, HairStrandsCore, IKRig, ImageCore, InputCore, InterchangeDNA, Json, JsonUtilities, Kismet, KismetWidgets, LauncherPlatform, LevelSequence, LevelSequenceEditor, LiveLinkInterface, MeshConversion, MeshDescription, MessageLog, MetaHumanCharacterPalette, MetaHumanCharacterPaletteEditor, MetaHumanConfig, MetaHumanCore, MetaHumanDefaultPipeline, MetaHumanFaceContourTracker, MetaHumanIdentity, MetaHumanImageViewer, MetaHumanImageViewerEditor, MetaHumanPipeline, MetaHumanPipelineCore, MetaHumanSDKEditor, MetaHumanSDKRuntime, ModelingComponents, ModelingComponentsEditorOnly, PerformanceCaptureCore, PhysicsCore, Projects, PropertyEditor, RHI, RenderCore, RigLogicLib, RigVM, RigVMDeveloper, RigVMEditor, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, SlateCore, SourceControl, StaticMeshDescription, StatusBar, StructUtilsEditor, TargetPlatform, TextureGraph, TextureUtilitiesCommon, ToolMenus, ToolWidgets, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: InteractiveToolsFramework, MetaHumanCharacter, MetaHumanCoreTech, MetaHumanCoreTechLib, MetaHumanSDKEditor, RigLogicModule, ScriptableToolsFramework

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanCharacter.h` (Private)


#### class `UAssetDefinition_MetaHumanCharacter`  
`class UAssetDefinition_MetaHumanCharacter : public UAssetDefinitionDefault`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/DCC/MetaHumanCharacterDCCExport.h` (Private)


#### struct `FMetaHumanExportDCCManifestDna`  
`struct FMetaHumanExportDCCManifestDna`  
_L13-22_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Head;` — `UPROPERTY()`
- L21 _public member_ `FString Body;` — `UPROPERTY()`

#### struct `FMetaHumanExportDCCManifestFolders`  
`struct FMetaHumanExportDCCManifestFolders`  
_L25-34_
- reflection: `USTRUCT()`
- L30 _public member_ `FString Maps;` — `UPROPERTY()`
- L33 _public member_ `FString Masks;` — `UPROPERTY()`

#### struct `FMetaHumanExportDCCManifestFiles`  
`struct FMetaHumanExportDCCManifestFiles`  
_L37-46_
- reflection: `USTRUCT()`
- L42 _public member_ `TArray<FString> Maps;` — `UPROPERTY()`
- L45 _public member_ `TArray<FString> Masks;` — `UPROPERTY()`

#### struct `FMetaHumanExportDCCManifest`  
`struct FMetaHumanExportDCCManifest`  
_L52-79_
- reflection: `USTRUCT()`
- desc: Information about the exported MetaHuman.
- L57 _public member_ `FString MetaHumanName;` — `UPROPERTY()`
- L60 _public member_ `FString ExportPluginVersion;` — `UPROPERTY()`
- L63 _public member_ `FString ExportEngineVersion;` — `UPROPERTY()`
- L66 _public member_ `FDateTime ExportedAt;` — `UPROPERTY()`
- L69 _public member_ `FMetaHumanExportDCCManifestDna Dna;` — `UPROPERTY()`
- L72 _public member_ `FString Thumbnail;` — `UPROPERTY()`
- L75 _public member_ `FMetaHumanExportDCCManifestFolders Folders;` — `UPROPERTY()`
- L78 _public member_ `FMetaHumanExportDCCManifestFiles Files;` — `UPROPERTY()`

#### struct `FMetaHumanCharacterEditorDCCExportParameters`  
`struct FMetaHumanCharacterEditorDCCExportParameters`  
_L81-102_
- L86 _public member_ `FString OutputFolderPath;` — Output folder on disk to store the DCC data. It should not be empty.
- L91 _public member_ `bool bBakeFaceMakeup = true;` — Whether or not to bake makeup in the face textures
- L96 _public member_ `bool bExportZipFile = false;` — Whether or not to export files in ZIP archive
- L101 _public member_ `FString ArchiveName;` — File name on disk to store the archive with the DCC data. If empty, character name will be used.

#### struct `FMetaHumanCharacterEditorDCCExport`  
`struct FMetaHumanCharacterEditorDCCExport`  
_L104-112_
- L109 _public prototype_ `static void ExportCharacterForDCC( TNotNull<class UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterEditorDCCExportParameters& InExportParams);` — Generate an archive containing the MetaHuman assets for consumption in DCC tools.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterAnalytics.h` (Private)


#### enum `UE::MetaHuman::Analytics::EConformOperation`  
`enum class EConformOperation : uint8`  
_L36-41_
- desc: The user-facing operation that triggered the conform event. Describes the button the user clicked, NOT the per-part code path taken internally. (e.g. Template `ImportMesh` button does "assign-as-is" for body and a real conform for head, both are reported as Operation=ImportMesh because that's what the user clicked.) Note: ImportJoints is NOT a value here, it has its own event family (see RecordImportJointsEvent / FImportJointsEventExtras).
- L38 _public enumerator_ `Conform` — "Conform" button (DNA, Template)
- L39 _public enumerator_ `ImportMesh` — "Import Mesh" button (DNA, Identity, Template)
- L40 _public enumerator_ `ImportWholeRig` — "Import Whole Rig" button (DNA only)

#### enum `UE::MetaHuman::Analytics::EConformParts`  
`enum class EConformParts : uint8`  
_L46-51_
- desc: Which mesh parts the user's click conformed.
- L48 _public enumerator_ `Head` — head conform only
- L49 _public enumerator_ `Body` — body conform only
- L50 _public enumerator_ `HeadAndBody` — head AND body conformed in the same click

#### struct `UE::MetaHuman::Analytics::FConformEventExtras`  
`struct FConformEventExtras`  
_L68-99_
- desc: Extra attributes for the Conform analytics event. The wire event is always `Editor.MetaHumanCharacter.ToolActivate.Conform` regardless of source; the source is encoded by the choice of recorder (`RecordConformFromDnaEvent` / `RecordConformFromIdentityEvent` / `RecordConformFromTemplateEvent`). Emission rules (see RecordConformEvent in the .cpp): - Operation, Parts always emitted. - bHeadSuccess emitted iff Parts is Head or HeadAndBody. - bBodySuccess emitted iff Parts is Body or HeadAndBody. - bImportEyes / bImportTeeth emitted only when explicitly set (Template path). - ExtraAttributes appended verbatim use for non-universal additions
- L71 _public member_ `EConformOperation Operation = EConformOperation::Conform;` — Which user-facing button triggered this event.
- L74 _public member_ `EConformParts Parts = EConformParts::Head;` — Which parts of the mesh the click conformed.
- L81 _public member_ `TOptional<bool> bHeadSuccess;` — Whether the head/face conform succeeded. Set iff `Parts` is Head or HeadAndBody. Default is unset, defensive, since a forgotten field should NOT silently report success.
- L87 _public member_ `TOptional<bool> bBodySuccess;` — Whether the body conform succeeded. Set iff `Parts` is Body or HeadAndBody. Default is unset.
- L90 _public member_ `TOptional<bool> bImportEyes;` — Template-only: whether eye meshes were imported as part of this conform.
- L93 _public member_ `TOptional<bool> bImportTeeth;` — Template-only: whether the teeth mesh was imported as part of this conform.
- L98 _public member_ `TArray<FAnalyticsEventAttribute> ExtraAttributes;` — Future-extension bag — non-universal attributes appended verbatim.

#### struct `UE::MetaHuman::Analytics::FImportJointsEventExtras`  
`struct FImportJointsEventExtras`  
_L108-114_
- desc: Optional extra attributes for the ImportJoints analytics event. ImportJoints patches joint transforms only it does not run the conform solver so it has its own event family separate from Conform. This keeps conform success-rate dashboards honest.
- L111 _public member_ `FString Source = TEXT("DNA` — Source label: "DNA" or "Template".
- L113 _public member_ `bool bSuccess = false;`

#### struct `UE::MetaHuman::Analytics::FMeshConformEventExtras`  
`struct FMeshConformEventExtras`  
_L129-150_
- desc: Optional extra attributes for the MeshConform (M2MH / "From Custom Mesh") events. The MeshImport tool's three click paths (AutoSolve, Face Solve Step, Body Solve Step) all funnel through `StartMeshConform`, then `ConformTargetMeshesAsync` (worker thread). This event family is separate from `ToolActivate.Conform` because: - Different solver path (M2MH ICP / NRR fitting, not the Import-From-X conform). - Different user gesture (provide an arbitrary input mesh, not a DNA/Identity/Template). `bSuccess` here means "the async conform task was queued successfully", NOT "the conform converged". Convergence isn't observable from the click site. A future revision could hook the task-completion delegate for a real success bit.
- L137 _public member_ `FString Step = TEXT("Aut` — Which of the three buttons fired this event: "Auto" "FaceOnly" "BodyOnly"
- L144 _public member_ `FString TargetPartsType = TEXT("Com` — The user's target-parts selection on the MeshImport tool: "Combined" | "BodyOnly" | "HeadOnly" | "HeadAndBody" (Mirror of `ETargetPartsType`.)
- L146 _public member_ `bool bSuccess = false;`
- L149 _public member_ `bool bHasKeyPoints = false;` — Whether the user populated any keypoint correspondences before clicking.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MetaHuman` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MetaHuman` (scope `UE`)
- L23 _namespace_ `namespace Analytics` (scope `UE::MetaHuman`)
- L152 _prototype_ `void RecordNewCharacterEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L153 _prototype_ `void RecordOpenCharacterEditorEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L154 _prototype_ `void RecordCloseCharacterEditorEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L155 _prototype_ `void RecordBuildPipelineCharacterEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const TSubclassOf<UMetaHumanCharacterPipeline> InMaybePipeline);` (scope `UE::MetaHuman::Analytics`)
- L156 _prototype_ `void RecordRequestAutorigEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, ERigType RigType);` (scope `UE::MetaHuman::Analytics`)
- L157 _prototype_ `void RecordRemoveFaceRigEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L158 _prototype_ `void RecordRequestHighResolutionTexturesEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, ERequestTextureResolution RequestTextureResolution);` (scope `UE::MetaHuman::Analytics`)
- L159 _prototype_ `void RecordSaveFaceDNAEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L160 _prototype_ `void RecordSaveBodyDNAEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L161 _prototype_ `void RecordSaveHighResolutionTexturesEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L162 _prototype_ `void RecordCreateMeshFromDNAEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L163 _prototype_ `void RecordWardrobeItemPreparedEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FName& ItemSlotName, const FName& ItemAssetName);` (scope `UE::MetaHuman::Analytics`)
- L164 _prototype_ `void RecordWardrobeItemWornEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FName& ItemSlotName, const FName& ItemAssetName);` (scope `UE::MetaHuman::Analytics`)
- L165 _prototype_ `void RecordImportFaceDNAEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L166 _prototype_ `void RecordImportBodyDNAEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter);` (scope `UE::MetaHuman::Analytics`)
- L167 _prototype_ `void RecordOnToolStartEvent(UMetaHumanCharacterEditorMode* MetaHumanCharacterEditorMode, FToolkitBuilder* ToolkitBuilder, const FString& ToolName);` (scope `UE::MetaHuman::Analytics`)
- L175 _prototype_ `void RecordConformFromDnaEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FConformEventExtras& InExtras = {});` (scope `UE::MetaHuman::Analytics`) — Recorders for the unified Conform event family. Each call emits exactly one `Editor.MetaHumanCharacter.ToolActivate.Conform` row, carrying `Source` (encoded by the recorder), `Operation`, `Parts`, per-part success bits, and any template-only/extra attrs.
- L176 _prototype_ `void RecordConformFromIdentityEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FConformEventExtras& InExtras = {});` (scope `UE::MetaHuman::Analytics`)
- L177 _prototype_ `void RecordConformFromTemplateEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FConformEventExtras& InExtras = {});` (scope `UE::MetaHuman::Analytics`)
- L179 _prototype_ `void RecordImportJointsEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FImportJointsEventExtras& InExtras = {});` (scope `UE::MetaHuman::Analytics`)
- L180 _prototype_ `void RecordMeshConformEvent(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter, const FMeshConformEventExtras& InExtras = {});` (scope `UE::MetaHuman::Analytics`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterAnimInstance.h` (Private)


#### class `UMetaHumanCharacterAnimInstance`  
`class UMetaHumanCharacterAnimInstance : public UAnimInstance`  
_L8-60_
- reflection: `UCLASS()`
- inherits: `UAnimInstance`
- L15 _public member_ `bool bIsPaused;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L18 _public member_ `bool bIsScrubbing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L21 _public member_ `float PlayRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L24 _public member_ `TObjectPtr<class UAnimSequence> PrimaryAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L27 _public member_ `TObjectPtr<class UAnimSequence> SecondaryAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L30 _public member_ `bool bIsAnimationPlaying;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L33 _public member_ `float CurrentPlayTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L36 _public member_ `int32 NumberOfKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHumanCharacter|Animation")`
- L38 _public prototype_ `void PlayAnimation();`
- L39 _public prototype_ `void PlayReverseAnimation();`
- L40 _public prototype_ `void StopAnimation();`
- L41 _public prototype_ `void PauseAnimation();`
- L42 _public prototype_ `void BeginScrubbingAnimation();`
- L43 _public prototype_ `void ScrubAnimation(float InScrubValue);`
- L44 _public prototype_ `void EndScrubbingAnimation();`
- L45 _public prototype_ `void SetAnimationPlayRate(float InNewPlayRate);`
- L46 _public prototype_ `float GetAnimationLenght() const;`
- L47 _public prototype_ `float GetCurrentPlayTime() const;`
- L48 _public prototype_ `int32 GetNumberOfKeys() const;`
- L50 _public prototype_ `void SetAnimation(UAnimSequence* FaceAnimation, UAnimSequence* BodyAnimation);`
- L55 _private prototype_ `virtual void NativeInitializeAnimation() override;` — UAnimInstance interface begin
- L56 _private prototype_ `virtual void NativeUpdateAnimation(float DeltaSeconds) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterAssetEditor.h` (Private)


#### class `UMetaHumanCharacterAssetEditor`  
`class UMetaHumanCharacterAssetEditor : public UAssetEditor`  
_L10-37_
- reflection: `UCLASS()`
- inherits: `UAssetEditor`
- L15 _public prototype_ `UMetaHumanCharacterAssetEditor();`
- L17 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjectsToEdit) override;`
- L18 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L21 _public prototype_ `class UMetaHumanCharacter* GetObjectToEdit() const;`
- L22 _public prototype_ `void SetObjectToEdit(class UMetaHumanCharacter* InObject);`
- L26 _public function_ `FGuid GetSessionGuid()` — returns unique editor session ID for analytics tracking the GUID is created each time an asset editor is opened
- L34 _private member_ `TObjectPtr<class UMetaHumanCharacter> ObjectToEdit;` — `UPROPERTY()`
- L36 _private member_ `FGuid EditorSessionGuid;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterAssetEditorContext.h` (Private)


#### class `UMetaHumanCharacterAssetEditorContext`  
`class UMetaHumanCharacterAssetEditorContext : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<FMetaHumanCharacterEditorToolkit> MetaHumanCharacterAssetEditor;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterAssetObserver.h` (Private)


#### struct `FMetaHumanObserverChanges`  
`struct FMetaHumanObserverChanges`  
_L10-21_
- L19 _public member_ `TMap<EChangeType, TArray<TSoftObjectPtr<UObject>>> Changes;`
- L20 _public member_ `FName Dir;`

#### enum `FMetaHumanObserverChanges::EChangeType`  
`enum class EChangeType : uint8`  
_L12-17_
- L14 _public enumerator_ `Added`
- L15 _public enumerator_ `Removed`
- L16 _public enumerator_ `Modified`

#### class `FMetaHumanCharacterAssetObserver`  
`class FMetaHumanCharacterAssetObserver`  
_L32-110_
- desc: Can be used to put a directory on a watch - whenever the content of the directory changes, the callback is triggered.
- L36 _public prototype_ `~FMetaHumanCharacterAssetObserver();`
- L38 _public prototype_ `static FMetaHumanCharacterAssetObserver& Get();`
- L43 _public prototype_ `bool IsDirectoryObserved(const FName& InDir) const;` — Checks if we're already watching a directory
- L50 _public prototype_ `bool StartObserving(const FName& InDir);` — Starts watching the given directory. Param InDir must be long package name.
- L57 _public prototype_ `bool StopObserving(const FName& InDir);` — Removes a directory from the watchlist. Param InDir must be long package name.
- L62 _public prototype_ `void StopObserving();` — Removes all observers.
- L67 _public prototype_ `FDelegateHandle SubscribeToObserver(const FName& InDir, const FOnObservedDirectoryChanged& InCallback);` — Adds subscribed to the observer.
- L72 _public prototype_ `bool UnsubscribeFromObserver(const FName& InDir, const FOnObservedDirectoryChanged& InCallback);` — Removes a subscriber for a directory from a given callback.
- L77 _public prototype_ `bool UnsubscribeFromObserver(const FName& InDir, const FDelegateHandle& InHandle);` — Removes a subscriber for a directory from a given handle.
- L82 _public prototype_ `bool GetAssets( const FName& InDir, const TSet<TSubclassOf<UObject>>& InClassesToFilter, TArray<FAssetData>& OutAssets);` — Queries assets on the given directory.
- L90 _public prototype_ `bool GetWardrobeAssets( const FName& InDir, const TSet<TSubclassOf<UObject>>& InClassesToFilter, TArray<FAssetData>& OutAssets);` — Queries wardrobe assets on the given directory, filering by principal item classes.
- L96 _private prototype_ `FMetaHumanCharacterAssetObserver() = default;`
- L98 _private prototype_ `void OnDirectoryChanged(const TArray<FFileChangeData>& InChanges, const FName InDir);`
- L109 _private member_ `TMap<FName, FObserverData> ObserverData;`

#### struct `FMetaHumanCharacterAssetObserver::FObserverData`  
`struct FObserverData`  
_L100-107_
- L102 _public member_ `FDelegateHandle DirWatcherHandle;`
- L103 _public member_ `FString AbsDir;`
- L105 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObservedDirectoryChangedDelegate, const FMetaHumanObserverChanges& );`
- L106 _public member_ `FOnObservedDirectoryChangedDelegate Callback;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObservedDirectoryChanged, const FMetaHumanObserverChanges& );`
- L23 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObservedDirectoryChanged, const FMetaHumanObserverChanges& );`
- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObservedDirectoryChangedDelegate, const FMetaHumanObserverChanges& );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorCommands.h` (Private)


#### class `FMetaHumanCharacterEditorCommands`  
`class FMetaHumanCharacterEditorCommands : public TCommands<FMetaHumanCharacterEditorCommands>`  
_L8-24_
- inherits: `TCommands<FMetaHumanCharacterEditorCommands>`
- L12 _public prototype_ `FMetaHumanCharacterEditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> SaveThumbnail;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> AutoRigFaceBlendShapes;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> AutoRigFaceJointsOnly;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> RemoveFaceRig;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> DownloadTextureSources;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> RefreshPreview;`

#### class `FMetaHumanCharacterEditorDebugCommands`  
`class FMetaHumanCharacterEditorDebugCommands : public TCommands<FMetaHumanCharacterEditorDebugCommands>`  
_L26-43_
- inherits: `TCommands<FMetaHumanCharacterEditorDebugCommands>`
- L30 _public prototype_ `FMetaHumanCharacterEditorDebugCommands();`
- L32 _public prototype_ `virtual void RegisterCommands() override;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SaveFaceState;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> SaveFaceStateToDNA;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> DumpFaceStateDataForAR;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> SaveBodyState;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SaveFaceTextures;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> SaveEyePreset;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> TakeHighResScreenshot;`

#### class `FMetaHumanCharacterEditorToolCommands`  
`class FMetaHumanCharacterEditorToolCommands : public TInteractiveToolCommands<FMetaHumanCharacterEditorToolCommands>`  
_L45-115_
- inherits: `TInteractiveToolCommands<FMetaHumanCharacterEditorToolCommands>`
- L49 _public prototype_ `FMetaHumanCharacterEditorToolCommands();`
- L51 _public prototype_ `virtual void RegisterCommands() override;`
- L53 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& OutToolCDOs) override;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> LoadPresetsTools;` — Preset tools
- L62 _public member_ `TSharedPtr<FUICommandInfo> BeginPresetsTool;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> PresetProperties;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> ApplyPreset;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> LoadMeshImportTools;` — Import tools
- L68 _public member_ `TSharedPtr<FUICommandInfo> BeginImportFromDNATool;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> BeginImportFromIdentityTool;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> BeginImportFromTemplateTool;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> BeginImportFromCustomMeshTool;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> LoadHeadAndBodyTools;` — Head and Body tools
- L75 _public member_ `TSharedPtr<FUICommandInfo> BeginBodyModelTool;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> BeginBodyModelParametricTool;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> BeginBodyFixedCompatibilityTool;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadAndBodyBlendTool;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadModelTools;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadModelEyelashesTool;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadModelTeethTool;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadMaterialsTools;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadMaterialsTeethTool;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> BeginHeadMaterialsEyelashesTool;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> BeginFaceMoveTool;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> BeginFaceSculptTool;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> LoadMaterialsTools;` — Materials tools
- L90 _public member_ `TSharedPtr<FUICommandInfo> BeginSkinTool;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> BeginEyesTool;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> BeginMakeupTool;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> BeginTextureMaterialOverrideTool;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> LoadHairAndClothingTools;` — Hair & Clothing tools
- L97 _public member_ `TSharedPtr<FUICommandInfo> BeginWardrobeSelectionTool;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> BeginCostumeDetailsTool;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> PrepareAccessory;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> UnprepareAccessory;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> WearAcceessory;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> RemoveAccessory;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> AccessoryProperties;`
- L106 _public member_ `TSharedPtr<FUICommandInfo> LoadPipelineTools;` — Pipeline tools
- L107 _public member_ `TSharedPtr<FUICommandInfo> BeginPipelineTool;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> LoadExportTools;` — Export tools
- L111 _public member_ `TSharedPtr<FUICommandInfo> BeginDCCExportTool;`
- L112 _public member_ `TSharedPtr<FUICommandInfo> BeginDNAExportTool;`
- L113 _public member_ `TSharedPtr<FUICommandInfo> BeginGeometryExportTool;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> BeginMaterialsExportTool;`

#### class `FMetaHumanCharacterEditorViewportToolbarCommands`  
`class FMetaHumanCharacterEditorViewportToolbarCommands : public TCommands<FMetaHumanCharacterEditorViewportToolbarCommands>`  
_L117-141_
- inherits: `TCommands<FMetaHumanCharacterEditorViewportToolbarCommands>`
- L120 _public prototype_ `FMetaHumanCharacterEditorViewportToolbarCommands();`
- L122 _public prototype_ `virtual void RegisterCommands() override;`
- L124 _public member_ `TSharedPtr<FUICommandInfo> PerspectiveProjection;`
- L125 _public member_ `TSharedPtr<FUICommandInfo> OrthographicProjection;`
- L127 _public member_ `TSharedPtr<FUICommandInfo> FocusFace;`
- L128 _public member_ `TSharedPtr<FUICommandInfo> FocusBody;`
- L129 _public member_ `TSharedPtr<FUICommandInfo> FocusFar;`
- L130 _public member_ `TSharedPtr<FUICommandInfo> FocusHands;`
- L131 _public member_ `TSharedPtr<FUICommandInfo> FocusFeet;`
- L133 _public member_ `TSharedPtr<FUICommandInfo> OrthoTop;`
- L134 _public member_ `TSharedPtr<FUICommandInfo> OrthoBottom;`
- L135 _public member_ `TSharedPtr<FUICommandInfo> OrthoLeft;`
- L136 _public member_ `TSharedPtr<FUICommandInfo> OrthoRight;`
- L137 _public member_ `TSharedPtr<FUICommandInfo> OrthoFront;`
- L138 _public member_ `TSharedPtr<FUICommandInfo> OrthoBack;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorLandmarkTracker.h` (Private)


#### class `UMetaHumanCharacterEditorLandmarkTracker`  
`class UMetaHumanCharacterEditorLandmarkTracker : public UObject`  
_L15-41_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _public prototype_ `virtual void PostInitProperties() override;`
- L22 _public prototype_ `void LoadTrackers();`
- L23 _public prototype_ `void InitializeContourData(int32 InWidth, int32 InHeight);`
- L25 _public prototype_ `FFrameTrackingContourData TrackImage(const TArray<FColor>& InImageData, int32 InWidth, int32 InHeight);`
- L27 _public prototype_ `TMap<FString, TArray<FVector2D>> GetTrackingContours(const FFrameTrackingContourData& TrackingContourData) const;`
- L29 _public function_ `TSharedPtr<FMetaHumanCurveDataController> GetCurveDataController() const`
- L33 _private member_ `TObjectPtr<UMetaHumanFaceContourTrackerAsset> FaceContourTracker;` — `UPROPERTY()`
- L36 _private member_ `TObjectPtr<UMetaHumanContourData> ContourData;` — `UPROPERTY()`
- L38 _private member_ `TSharedPtr<FMetaHumanCurveDataController> CurveDataController;`
- L39 _private member_ `TUniquePtr<UE::MetaHuman::Pipeline::FPipeline> TrackPipeline;`
- L40 _private member_ `FVector2D TrackingImageSize = FVector2D::ZeroVector;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterEditor, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorMeshImportTaskRunner.h` (Private)


#### class `FMeshImportTaskRunner`  
`class FMeshImportTaskRunner : public TSharedFromThis<FMeshImportTaskRunner, ESPMode::ThreadSafe>`  
_L13-87_
- inherits: `TSharedFromThis<FMeshImportTaskRunner,ESPMode::ThreadSafe>`
- L31 _public prototype_ `FOnMeshImportIteration& OnMeshImportIteration();`
- L32 _public prototype_ `FOnMeshImportFinish& OnMeshImportFinish();`
- L34 _public function_ `static TSharedRef<FMeshImportTaskRunner> Create()`
- L39 _public prototype_ `FMeshImportTaskRunner() = default;`
- L40 _public prototype_ `~FMeshImportTaskRunner();`
- L42 _public prototype_ `FMeshImportTaskRunner(const FMeshImportTaskRunner&) = delete;`
- L43 _public prototype_ `FMeshImportTaskRunner& operator=(const FMeshImportTaskRunner&) = delete;`
- L44 _public prototype_ `FMeshImportTaskRunner(FMeshImportTaskRunner&&) = delete;`
- L45 _public prototype_ `FMeshImportTaskRunner& operator=(FMeshImportTaskRunner&&) = delete;`
- L47 _public prototype_ `void StartConform(const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& InBodyState, const TSharedRef<FMetaHumanCharacterIdentity::FState>& InFaceState, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams);`
- L52 _public prototype_ `void StartAlignToTargetMesh(const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& InBodyState, const TSharedRef<FMetaHumanCharacterIdentity::FState>& InFaceState, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams);`
- L57 _public prototype_ `void StartRefineVertices(const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& InBodyState, const TSharedRef<FMetaHumanCharacterIdentity::FState>& InFaceState, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FRefinementTargetParams& InRefinementTargetParams);`
- L62 _public prototype_ `void CancelUpdates();`
- L65 _private prototype_ `bool OnIterationUpdate(const FMetaHumanRigEvaluatedState& InBodyVerticesAndNormals, const TArray<FMatrix44f>& InBindPoseMatrices, int32 InIterationCount, ESolveStepType InSolveStepType);`
- L66 _private prototype_ `static void OnProcessComplete(const TWeakPtr<FMeshImportTaskRunner>& TaskRunnerWeakPtr);`
- L69 _private member_ `FOnMeshImportIteration MeshImportIterationDelegate;`
- L70 _private member_ `FOnMeshImportFinish MeshImportFinishDelegate;`
- L73 _private member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> BodyState;`
- L74 _private member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> FaceState;`
- L75 _private member_ `FMetaHumanCharacterTargetMeshKey TargetMeshKey;`
- L77 _private member_ `int32 IterationCount = 0;`
- L78 _private member_ `bool bSuccess = true;`
- L79 _private member_ `bool bCancelled = false;`
- L81 _private member_ `FCriticalSection UpdateVerticesMutex;`
- L82 _private member_ `FMetaHumanRigEvaluatedState IterationBodyVerticesAndNormals;`
- L83 _private member_ `FMetaHumanRigEvaluatedState IterationFaceVerticesAndNormals;`
- L84 _private member_ `TArray<FVector3f> IterationLocalJointPositions;`
- L85 _private member_ `TArray<FRotator3f> IterationLocalJointRotations;`
- L86 _private member_ `FText IterationSolveMessage;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_SixParams(FOnMeshImportIteration, float , const FMetaHumanRigEvaluatedState& , const FMetaHumanRigEvaluatedState& , const TArray<FVector3f>& , const TArray<FRotator3f>& , const FText& ) DECLARE_DELEGATE_FiveParams(FOnMeshImportFinish, bool , bool , const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& , const TSharedRef<FMetaHumanCharacterIdentity::FState>& , const FMetaHumanCharacterTargetMeshKey& ) public: FOnMeshImportIteration& OnMeshImportIteration();`
- L23 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnMeshImportFinish, bool , bool , const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& , const TSharedRef<FMetaHumanCharacterIdentity::FState>& , const FMetaHumanCharacterTargetMeshKey& ) public: FOnMeshImportIteration& OnMeshImportIteration();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorMode.h` (Private)


#### class `UMetaHumanCharacterEditorMode`  
`class UMetaHumanCharacterEditorMode : public UEdMode`  
_L15-78_
- reflection: `UCLASS(Transient)`
- inherits: `UEdMode`
- L20 _public member_ `const static FEditorModeID EM_MetaHumanCharacterEditorModeId;`
- L22 _public prototype_ `UMetaHumanCharacterEditorMode();`
- L25 _public prototype_ `virtual void Enter() override;`
- L26 _public prototype_ `virtual void Exit() override;`
- L27 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L28 _public prototype_ `virtual void RegisterTool(TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder, EToolsContextScope ToolScope = EToolsContextScope::Default) override;`
- L32 _public prototype_ `void SetCharacter(TNotNull<UMetaHumanCharacter*> InCharacter);` — Set the Character which we are editing
- L34 _public prototype_ `TObjectPtr<UMetaHumanCharacter> GetCharacter() const;` — Get the Character which we are editing
- L42 _public prototype_ `void RestartCurrentlyActiveTool();` — @brief Restarts the current active tool. If there is an active tool, sends EToolShutdownType::Completed to is and reactivate it. This is useful in cases where tool changes must be committed, such as when saving the asset
- L47 _protected prototype_ `virtual void CreateToolkit() override;`
- L48 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L49 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L54 _private prototype_ `void RegisterModeTools();` — Register the tools used by this mode (see ToolTarget.h for more info on tools)
- L57 _private prototype_ `void RegisterModeToolTargetFactories();` — Register the tool target factories (see ToolTarget.h for more info tool targets)
- L60 _private member_ `TObjectPtr<UMetaHumanCharacter> Character;` — the character being edited
- L63 _private member_ `FDelegateHandle CharacterRiggingStateChanged;` — a delegate handle for a delegate called when the character rigging state changes
- L65 _private prototype_ `void OnRiggingStateChanged();` — the function which gets called
- L68 _private member_ `FDelegateHandle DownloadingTexturesStateChanged;` — Delegate handle for when the subsystem downloading textures state changes
- L70 _private prototype_ `void OnDownloadingTexturesStateChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Called when change in downloading textures state
- L73 _private prototype_ `void UpdateWarningText() const;` — Calls FMetaHumanCharacterEditorModeToolkit::UpdateWarningText to update warning text dependent on rigging state and if downloading textures
- L77 _private member_ `TObjectPtr<UMetaHumanCharacterEditorMeshImportContextObject> MeshImportContextObject;` — `UPROPERTY()` — Context object registered in the tools context store so the mesh import tool can cache and re-use built dynamic meshes across restarts.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorModeToolkit.h` (Private)


#### class `FMetaHumanCharacterEditorModeToolkit`  
`class FMetaHumanCharacterEditorModeToolkit : public FModeToolkit`  
_L18-164_
- inherits: `FModeToolkit`
- desc: The Mode toolkit is responsible for the panel on the side in the asset editor that shows mode and tool properties. Tool buttons would go in Init(). It also builds the toolbar used in the asset editor
- L22 _public prototype_ `FMetaHumanCharacterEditorModeToolkit();` — Constructor.
- L25 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L28 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L29 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L30 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L31 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* InManager, UInteractiveTool* InTool) override;`
- L35 _public prototype_ `virtual void PostNotification(const FText& InMessage);` — Set/Clear notification messages displayed in the status bar.
- L36 _public prototype_ `virtual void ClearNotification();`
- L39 _public prototype_ `virtual void PostWarning(const FText& InMessage);` — Set/Clear warnings messages.
- L40 _public prototype_ `virtual void ClearWarning();`
- L43 _public prototype_ `void UpdateWarningText();` — Updates warning text dependent on rigging state and if downloading textures
- L48 _private prototype_ `TSharedPtr<SEditorViewport> GetEditorViewport() const;` — Getters
- L49 _private prototype_ `EVisibility GetCustomWarningVisibility() const;`
- L50 _private prototype_ `bool IsViewportModeVisible() const;`
- L51 _private prototype_ `FText GetCustomWarning() const;`
- L54 _private prototype_ `TSharedRef<SWidget> CreateSubToolsToolbar(TNotNull<UInteractiveTool*> Tool, bool bUseLabel = true) const;` — Creates the toolbar widget used to display the subtools of the given tool.
- L57 _private prototype_ `TSharedRef<SWidget> CreateToolView(UInteractiveTool* Tool);` — Creates the view used to display the current active tool.
- L60 _private prototype_ `TSharedRef<IDetailsView> CreateToolDetailsView(UInteractiveTool* Tool) const;` — Creates a details view used to display the current active tool.
- L63 _private prototype_ `TSharedRef<SWidget> MakeActiveToolViewWidget();` — Creates the widget used to contain the active tool view.
- L66 _private prototype_ `TSharedRef<SWidget> MakeCustomWarningsWidget();` — Creates the widget used to display custom warnings.
- L69 _private prototype_ `void RegisterPalettes();` — Creates the tool palettes and register them in the FToolkitBuilder.
- L72 _private prototype_ `void InitializeViewport();` — Initializes the viewport widget.
- L75 _private prototype_ `void UpdateViewport(UInteractiveTool* Tool, bool bOnToolEnded = false);` — Updates the viewport according to the active tool.
- L78 _private prototype_ `void UpdateActiveToolViewWidget();` — Updates the active tool view widget according to the active tool.
- L81 _private prototype_ `void UpdateSubToolsToolbar();` — Updates the subtools toolbar according to the active tool.
- L84 _private prototype_ `void UpdateActiveToolViewStatus();` — Updates the active tool view status according to the active tool.
- L87 _private prototype_ `void UpdateTrackerImageViewer();` — Updates the tracker image viewer in the viewport overlay.
- L90 _private prototype_ `void HandleAutoActivatingTools();` — Handles the activation of auto-activating tools.
- L93 _private prototype_ `void HandleLastToolActivation(UInteractiveTool* Tool);` — Handles the recovery of the last tool activation.
- L96 _private prototype_ `void HandleToolShutdown();` — Handles the shutdown of a tool.
- L99 _private prototype_ `bool CanActivateToolAfterBodyStateCheck();` — Checks if a tool can be activated after checking the body state.
- L102 _private prototype_ `void OnActivePaletteChanged();` — Called when the active palette has been changed.
- L105 _private prototype_ `void OnSubToolPropertySetsModified(UInteractiveTool* Tool, const FName ToolName);` — Called when the property set of a tool with subtools gets modified.
- L108 _private prototype_ `void OnViewportResized(FVector2D InSize);` — Called when the editor viewport widget is resized
- L111 _private prototype_ `void OnTrackerImageVisibilityChanged(bool bIsVisible);` — Called when the visibility of the tracker image viewer changes.
- L114 _private prototype_ `FVector2D GetTrackerViewerImageSize() const;` — Returns the size of the tracker image viewer in the viewport overlay.
- L117 _private prototype_ `bool ShouldDrawTrackingPointsOnViewport() const;` — Returns true if the viewport should display the tracking points of the active tool.
- L121 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;` — Widget used to display warning messages raised by tools
- L124 _private member_ `FText ActiveToolName;` — The name of the active tool
- L127 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;` — The icon of the active tool, used in the Accept/Cancel widget
- L130 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;` — Handle of the message being displayed in the toolkit status bar
- L133 _private member_ `TSharedPtr<SWidget> SubToolsToolbarWidget;` — Contains the widget container for the SubTools Toolbar
- L136 _private member_ `TSharedPtr<SWidget> ActiveToolViewWidget;` — Contains the widget container for the Active Tool view
- L139 _private member_ `TSharedPtr<SWidget> ActiveToolView;` — Contains the Active Tool view
- L142 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;` — Contains the overlay for the viewport
- L145 _private member_ `TMap<FName, FName> ModeNameToLastActiveToolNameMap;` — The map used for remembering the last active tool of a mode
- L148 _private member_ `TMap<FName, FName> ToolNameToLastActiveSubToolNameMap;` — The map used for remembering the last active subtool of a tool
- L151 _private member_ `TMap<FName, float> ToolNameToLastScrollOffsetMap;` — The map used for remembering the last scroll offset tool of a tool
- L154 _private member_ `TMap<FName, FMetaHumanCharacterAssetViewsPanelStatus> ToolViewNameToStatusMap;` — The map used for remembering the status of the asset views panels in the tool views
- L157 _private member_ `TMap<FName, TArray<FMetaHumanCharacterAssetViewStatus>> ToolViewNameToStatusArrayMap;` — The map used for remembering the status of the asset views in the tool views
- L160 _private member_ `FText CustomWarning;` — Custom warning
- L163 _private member_ `bool bHasToolView = false;` — True if the toolkit is displaying a tool view widget

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorPreviewMaterialState.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MetaHuman` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::MetaHuman`)
- L8 _variable_ `inline bool bFacePreviewMaterialsFailed = false;` (scope `UE::MetaHuman::Private`) — Set by FMetaHumanCharacterSkinMaterials::GetHeadPreviewMaterialInstance.
- L11 _variable_ `inline bool bBodyPreviewMaterialsFailed = false;` (scope `UE::MetaHuman::Private`) — Set by FMetaHumanCharacterSkinMaterials::GetBodyPreviewMaterialInstance.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorStyle.h` (Private)


#### class `FMetaHumanCharacterEditorStyle`  
`class FMetaHumanCharacterEditorStyle : public FSlateStyleSet`  
_L10-31_
- inherits: `FSlateStyleSet`
- desc: Slate style set for the MetaHuman Character Editor
- L14 _public prototype_ `static const FMetaHumanCharacterEditorStyle& Get();`
- L16 _public prototype_ `static void Register();`
- L17 _public prototype_ `static void Unregister();`
- L20 _private prototype_ `FMetaHumanCharacterEditorStyle();`
- L30 _private prototype_ `void SetSkinAccentRegionStyle(const FSkinAccentRegionStyleParams& InParams);` — Helper function to set the style of a skin accent region

#### struct `FMetaHumanCharacterEditorStyle::FSkinAccentRegionStyleParams`  
`struct FSkinAccentRegionStyleParams`  
_L22-27_
- L24 _public member_ `FName Property;`
- L25 _public member_ `FVector2D BrushSize;`
- L26 _public member_ `FName Image;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorToolkit.h` (Private)


#### class `FMetaHumanCharacterEditorToolkit`  
`class FMetaHumanCharacterEditorToolkit : public FBaseAssetToolkit`  
_L13-193_
- inherits: `FBaseAssetToolkit`
- L17 _public prototype_ `FMetaHumanCharacterEditorToolkit(class UMetaHumanCharacterAssetEditor* InOwningAssetEditor);`
- L18 _public prototype_ `virtual ~FMetaHumanCharacterEditorToolkit();`
- L21 _public prototype_ `virtual FName GetToolkitFName() const;`
- L22 _public prototype_ `virtual FText GetBaseToolkitName() const;`
- L23 _public prototype_ `virtual void CreateEditorModeManager() override;`
- L24 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L25 _public prototype_ `virtual void InitToolMenuContext(struct FToolMenuContext& InMenuContext) override;`
- L26 _public prototype_ `virtual void OnClose() override;`
- L32 _protected prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L33 _protected prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L34 _protected prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L35 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L36 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L37 _protected prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& InToolkit) override;`
- L38 _protected prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& InToolkit) override;`
- L44 _private member_ `static const FName MetaHumanCharacterPreviewTabID;` — /
- L45 _private member_ `static const FName MetaHumanCharcterAnimationPanelID;`
- L48 _private prototype_ `TNotNull<class UMetaHumanCharacterEditorMode*> GetMetaHumanCharacterEditorMode() const;` — Utility to get the MetaHumanCharacterEditorMode
- L51 _private prototype_ `bool HasActiveTool() const;` — Returns false if there is a current active tool
- L54 _private prototype_ `FText GetDownloadTextureSourcesLabel() const;` — Returns the label for the Download Texture Sources
- L57 _private prototype_ `FText GetDownloadTextureSourcesTooltip() const;` — Returns the tooltip to display for the Download Texture Sources command
- L60 _private prototype_ `bool CanRequestTextureSources() const;` — Returns true if the Character can request texture sources from the service
- L63 _private prototype_ `void RequestTextureSources();` — Start a service request to downloaded texture sources
- L66 _private prototype_ `bool CanAutoRigFace() const;` — Returns true if it's safe to call AutoRigFace
- L69 _private prototype_ `void AutoRigFace(EMetaHumanRigType InRigType);` — Function which triggers the call to AutoRigService
- L72 _private prototype_ `bool CanRemoveFaceRig() const;` — Returns true if the is a rig to remove
- L75 _private prototype_ `void RemoveFaceRig();` — Function which triggers removal of the face rig
- L78 _private prototype_ `class ULevelStreaming* LoadLevelInWorld(const FSoftObjectPath& LevelPath, const FTransform& LevelTransform = FTransform::Identity);` — Generic function for loading a level as streaming, optionally at a specific transform
- L81 _private prototype_ `void LoadLevelInstanceSubLevelsInWorldRecursive(const TNotNull<ULevel*> InLoadedLevel);` — Recursively stream LevelInstance sublevels found in the streamed level
- L82 _private prototype_ `void LoadLevelInstanceSubLevelsInWorldRecursive(const TNotNull<ULevel*> InLoadedLevel, const FTransform& InParentTransform, TArray<AActor*>& OutActorsToDestroy);`
- L85 _private prototype_ `void LoadLightingScenariosInWorld(const TArray<FSoftObjectPath>& LevelPaths);` — This function is called on PostInitEditor when we need to load all of the lighting scenarios that we use in viewport
- L88 _private prototype_ `void LoadPostProcessScenariosInWorld(const FSoftObjectPath& BaseLevelPath);` — This function is called on PostInitEditor when we need to load all of the PostProcess scenarios that we use in viewport
- L90 _private prototype_ `void LoadCustomLightingEnvironment(const FSoftObjectPath& EnvironmentPath);`
- L92 _private prototype_ `void UnloadCustomLightingEnvironment();`
- L97 _private prototype_ `bool EnsureValidLightingEnvIsSelected() const;` — Ensures that a valid lighting environment is selected if selected CustomLightPreset is updated or became invalid @return True if environment needs update, else false
- L101 _private prototype_ `void OnLightingStudioEnvironmentChanged(const EMetaHumanCharacterEnvironment NewStudioEnvironment);` — `UE_DEPRECATED(5.7, "Deprecated! Please use OnEnvironmentChanged.")` — Changes lighting environment by streaming lighting scenario in the world
- L105 _private prototype_ `void OnTonemapperEnvironmentChanged(const bool InTonemapperEnabled);` — Called when PostProcess volume option changes
- L108 _private prototype_ `void OnEnvironmentChanged();` — Changes lighting environment by streaming lighting scenario in the world
- L111 _private prototype_ `void SetLightRigParentRotation(const FRotator& InRotation);` — Applies a rotation to the current light rig's parent actor, if one exists.
- L114 _private prototype_ `void OnLightRotationChanged(float InRotation);` — Called when the light rotation changes so the world can be updated
- L117 _private prototype_ `void RefreshEnvironmentCapabilityState();` — Scans the preview world for actors implementing IMetaHumanCharacterEnvironmentLightRig and IMetaHumanCharacterEnvironmentBackground, pushes the results into the viewport client, and emits Message Log warnings for each missing capability.
- L120 _private prototype_ `void WarnIfWorldPartitionEnvironment(const FSoftObjectPath& InEnvironmentPath, const class UWorld* InLoadedWorld) const;` — Logs a Message Log warning if the loaded custom environment world uses World Partition.
- L123 _private prototype_ `void OnBackgroundColorChanged(const FLinearColor& InBackgroundColor);` — Called when the background color changes
- L125 _private prototype_ `void OnRenderingQualityProfileUpdate(const int32 InActiveProfileIndex);`
- L128 _private prototype_ `void RefreshPreview();` — Re-runs the preview build pipeline to regenerate the content used by the preview actor
- L131 _private prototype_ `void ExtendToolbar();` — Extend the editor's toolbar with custom entries
- L134 _private prototype_ `void ExtendMenu();` — Extend the editor's main menu with custom entries
- L136 _private prototype_ `void BindCommands();`
- L141 _private prototype_ `bool CanSaveStates() const;` — Returns true if the character has body or face state
- L142 _private prototype_ `bool CanSaveTextures() const;` — Returns true if the character has synthesized textures
- L143 _private prototype_ `bool CanSaveEyePreset() const;`
- L145 _private prototype_ `void SaveFaceState();` — Save the identity state of the face to a file
- L146 _private prototype_ `void SaveFaceStateToDNA();` — Save the face state as part of a DNA, uses either the MH asset DNA or the preview one
- L147 _private prototype_ `void DumpFaceStateDataForAR();` — Save the face state debug data to a folder
- L148 _private prototype_ `void SaveBodyState();` — Save the identity state of the body to a file
- L149 _private prototype_ `void SaveFaceTextures();` — Save all synthesized textures of the edited character as images files
- L150 _private prototype_ `void SaveEyePreset();` — Save the current eye as a preset
- L151 _private prototype_ `void TakeHighResScreenshot();` — Take a high resolution screenshot of the asset editor
- L157 _private member_ `TUniquePtr<class FPreviewScene> PreviewScene;` — The preview scene displayed in the viewport of the asset editor. It holds the world and all the components that operate on the world The advanced preview scene is used because of the post processing settings needed in editor
- L160 _private member_ `TScriptInterface<class IMetaHumanCharacterEditorActorInterface> PreviewActor;` — The actor spawned in the world of the preview scene. It is used to hold any components required to render the MetaHuman in the preview world
- L163 _private member_ `TSharedPtr<class FMetaHumanCharacterEditorModeUILayer> ModeUILayer;` — Handles the hosting of mode toolkits. Builds the UI from the toolkit being hosted
- L166 _private member_ `TSharedPtr<FWorkspaceItem> MetaHumanCharacterEditorMenuCategory;` — This is set in ModeUILayer to be the menu category where new tabs are registered to be enabled by the user
- L169 _private member_ `TStrongObjectPtr<class UMetaHumanCharacterEditorPreviewSceneDescription> PreviewSceneDescription;` — Description where all of the preview scene details specific to the MetaHuman Character are stored
- L172 _private member_ `TArray<class ULevelStreaming*> PostProcessLevels;` — Base and Tonemapper post process levels
- L175 _private member_ `TOptional<FRotator> CurrentLightRigParentRotation;` — Rotation of the light rig's parent actor, captured before an environment swap so it can be restored on the new level's rig.
- L178 _private member_ `TSharedPtr<SWidget> PreviewSettingsWidget;` — The preview settings widget where different options for preview can be adjusted and the tab where it's docked
- L180 _private member_ `TSharedPtr<SMetaHumanCharacterEditorRenderingQualityView> RenderingQualityWidget;`
- L182 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AnimationBar(const FSpawnTabArgs& Args);`
- L184 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneDetails(const FSpawnTabArgs& Args);`
- L186 _private prototype_ `void InitPreviewSceneDetails();`
- L188 _private prototype_ `class UMetaHumanCharacterEditorPreviewSceneDescription* GetPreviewSceneDescription();`
- L191 _private member_ `TSet<FSoftObjectPath> ResidentLevelPaths;` — Protected levels that should never be unloaded during unloading of custom lighting environment
- L192 _private member_ `TArray<TWeakObjectPtr<ULevelStreaming>> SelectedCustomLightingEnvStreamingLevels;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorToolkitBuilder.h` (Private)


#### struct `FMetaHumanCharacterEditorToolkitSections`  
`struct FMetaHumanCharacterEditorToolkitSections : FToolkitSections`  
_L7-11_
- inherits: `FToolkitSections`
- L9 _public member_ `TSharedPtr<SWidget> ToolCustomWarningsArea = nullptr;`
- L10 _public member_ `TSharedPtr<SWidget> ToolViewArea = nullptr;`

#### class `FMetaHumanCharacterEditorToolkitBuilder`  
`class FMetaHumanCharacterEditorToolkitBuilder : public FToolkitBuilder`  
_L14-66_
- inherits: `FToolkitBuilder`
- desc: A customized Toolkit Builder used for the MetaHuman Character editor implementation
- L24 _public prototype_ `explicit FMetaHumanCharacterEditorToolkitBuilder( FName ToolbarCustomizationName, TSharedPtr<FUICommandList> InToolkitCommandList, TSharedPtr<FToolkitSections> InToolkitSections);` — Constructor @param ToolbarCustomizationName the name of the  customization fr the category toolbar @param InToolkitCommandList  the toolkit FUICommandList @param InToolkitSections The FToolkitSections for this toolkit builder
- L30 _public prototype_ `explicit FMetaHumanCharacterEditorToolkitBuilder(FToolkitBuilderArgs& Args);` — default constructor
- L38 _public prototype_ `void AddPaletteCustom(TSharedPtr<FToolPalette> Palette);` — Adds a palette and tracks its display order locally for the custom category column. Required because base FToolkitBuilder::LoadCommandArray is private; we need the ordered list to build the wrapping-label category buttons. Use this instead of FToolkitBuilder::AddPalette when constructing the MetaHuman editor.
- L39 _public prototype_ `void AddPaletteCustom(TSharedPtr<FEditablePalette> Palette);`
- L43 _protected prototype_ `virtual TSharedPtr<SWidget> GenerateWidget() override;`
- L47 _protected prototype_ `TSharedRef<SWidget> BuildCategoryColumnWidget();` — Builds the custom left-hand category column with wrapping text labels.
- L51 _private member_ `TSharedPtr<SWidget> ToolCustomWarningsArea;` — Reference to the custom Tool Warnings section
- L54 _private member_ `TSharedPtr<SWidget> ToolViewArea;` — Reference to the Tool View area section
- L57 _private member_ `TArray<FName> OrderedLoadCommandNames;` — Ordered list of category command names, in the order palettes were added.
- L65 _private member_ `TSharedPtr<SWidget> CachedRootWidget;` — Cached root SSplitter wrapping the inherited MainContentVerticalBox. Built once on the first GenerateWidget() call and reused on subsequent calls so that MainContentVerticalBox is never re-parented into a freshly-created SSplitter (which would trigger Slate's single-parent assertion).

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorUILayer.h` (Private)


#### class `UMetaHumanCharacterEditorUISubsystem`  
`class UMetaHumanCharacterEditorUISubsystem : public UAssetEditorUISubsystem`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- desc: Interchange layer to manage built in tab locations within the editor's layout.
- L18 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L19 _public prototype_ `virtual void Deinitialize() override;`
- L20 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& InExtender) override;`

#### class `FMetaHumanCharacterEditorModeUILayer`  
`class FMetaHumanCharacterEditorModeUILayer : public FAssetEditorModeUILayer`  
_L25-42_
- inherits: `FAssetEditorModeUILayer`
- desc: Handles the hosting of additional toolkits, such as the mode toolkit, within the MetaHumanCharacterEditor's toolkit.
- L28 _public prototype_ `FMetaHumanCharacterEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L31 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& InToolkit) override;`
- L32 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& InToolkit) override;`
- L33 _public prototype_ `TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L36 _public prototype_ `void SetModeMenuCategory(TSharedPtr<FWorkspaceItem> InMenuCategory);`
- L41 _protected member_ `TSharedPtr<FWorkspaceItem> MetaHumanCharacterEditorMenuCategory;` — The Menu Category to be used to add new entries for MetaHuman tabs

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEditorViewportClient.h` (Private)


#### class `FMetaHumanCharacterViewportClient`  
`class FMetaHumanCharacterViewportClient : public FEditorViewportClient`  
_L23-212_
- inherits: `FEditorViewportClient`
- L26 _public prototype_ `FMetaHumanCharacterViewportClient( FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, TWeakInterfacePtr<IMetaHumanCharacterEditorActorInterface> InEditingActor, TWeakObjectPtr<UMetaHumanCharacter> InCharacter);`
- L33 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L34 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& InEventArgs) override;`
- L35 _public prototype_ `virtual void OverridePostProcessSettings(FSceneView& View) override;`
- L36 _public prototype_ `virtual void SetupViewForRendering(FSceneViewFamily& InViewFamily, FSceneView& InOutView) override;`
- L37 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L38 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L39 _public prototype_ `virtual bool ShouldScaleCameraSpeedByDistance() const override;`
- L40 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* InCanvas) override;`
- L41 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L42 _public prototype_ `virtual void MouseMove(FViewport* InViewport, int32 X, int32 Y) override;`
- L43 _public prototype_ `virtual void CapturedMouseMove(FViewport* InViewport, int32 X, int32 Y) override;`
- L44 _public prototype_ `virtual void ProcessAccumulatedPointerInput(FViewport* InViewport) override;`
- L47 _public member_ `TWeakInterfacePtr<IMetaHumanCharacterEditorActorInterface> WeakCharacterActor;`
- L48 _public member_ `TWeakObjectPtr<UMetaHumanCharacter> WeakCharacter;`
- L50 _public prototype_ `void FocusOnSelectedFrame(EMetaHumanCharacterCameraFrame SelectedFrame, bool bInRotate, bool bInInstant = false);`
- L51 _public prototype_ `void SetAutoFocusToSelectedFrame(EMetaHumanCharacterCameraFrame SelectedFrame, bool bInRotate);`
- L52 _public prototype_ `void RescheduleFocus();`
- L54 _public prototype_ `void UpdateRenderingQuality(const int32 InActiveProfileIndex);`
- L56 _public prototype_ `void SetViewportWidget(const TWeakPtr<SEditorViewport>& InEditorViewportWidget);`
- L58 _public prototype_ `void ClearShortcuts();`
- L59 _public prototype_ `void SetShortcuts(const TArray<TPair<FText, FText>>& InShortcuts);`
- L61 _public prototype_ `void ShowFaceBonesOnCharacter(const bool InDrawFaceBones);`
- L63 _public prototype_ `void ShowBodyBonesOnCharacter(const bool InDrawBodyBones);`
- L65 _public prototype_ `void DrawDebugBones(const USkeletalMeshComponent* MetaHumanSkeletalMeshComponent, bool bIsFaceComponent, FPrimitiveDrawInterface* PDI);`
- L67 _public prototype_ `void ShowFaceNormalsOnCharacter(const bool InShowFaceNormals);`
- L68 _public prototype_ `void ShowBodyNormalsOnCharacter(const bool InShowBodyNormals);`
- L70 _public prototype_ `void ShowFaceTangentsOnCharacter(const bool InShowFaceTangents);`
- L71 _public prototype_ `void ShowBodyTangentsOnCharacter(const bool InShowBodyTangents);`
- L73 _public prototype_ `void ShowFaceBinormalsOnCharacter(const bool InShowFaceBinormals);`
- L74 _public prototype_ `void ShowBodyBinormalsOnCharacter(const bool InShowBodyBinormals);`
- L76 _public prototype_ `void HandleCameraFocusRequest(UMetaHumanCharacter* InCharacter, EMetaHumanCharacterCameraFrame InFrameToFocus);`
- L79 _public prototype_ `void SetSelectedPoint(const FVector& InPoint);` — Sets the selected point for the SelectedPoint camera frame. Does not start orbit.
- L82 _public member_ `TFunction<bool(const FRay&, FVector&)> SelectPointHitProvider;` — Called on Ctrl+Alt+LMB to find the orbit focus point. Return true and set OutPoint if hit. If unset, defaults to the MetaHuman mesh.
- L85 _public member_ `FSimpleMulticastDelegate OnSelectPointOrbitStarted;` — Fired when Ctrl+Alt+LMB successfully finds a selection point and orbit begins
- L88 _public function_ `void SetEnvironmentHasLightRig(bool bInHasLightRig)` — Set by the toolkit after each environment swap. False when the loaded environment has no actor implementing IMetaHumanCharacterEnvironmentLightRig.
- L91 _public function_ `bool DoesEnvironmentHaveLightRig() const` — True if the loaded environment exposes a light rig. Drives whether the Light Rig Rotation slider is interactive.
- L94 _public function_ `void SetEnvironmentHasBackground(bool bInHasBackground)` — Set by the toolkit after each environment swap. False when the loaded environment has no actor implementing IMetaHumanCharacterEnvironmentBackground.
- L97 _public function_ `bool DoesEnvironmentHaveBackground() const` — True if the loaded environment exposes a background actor. Drives whether the Background Color picker is interactive.
- L101 _private prototype_ `void FocusOnFace(float InDistanceScale, const FVector& InOffset, bool bInInstant);`
- L103 _private prototype_ `void FocusOnBody(float InDistanceScale, const FVector& InOffset, bool bInInstant);`
- L105 _private prototype_ `void FocusOnBodyPartPair(const FName InBodyPartNameR, const FName InBodyPartNameL, const float InDistanceScale, const FVector& InOffset, const bool bInInstant);`
- L107 _private prototype_ `void FocusOnHands(float InDistanceScale, const FVector& InOffset, const bool bInInstant);`
- L109 _private prototype_ `void FocusOnFeet(float InDistanceScale, const FVector& InOffset, const bool bInInstant);`
- L111 _private member_ `struct FPostProcessSettings PostProcessSettings;`
- L113 _private prototype_ `void SetTransmissionForAllLights(bool bTransmissionEnabled);`
- L125 _private prototype_ `void DrawInfos(FCanvas* InCanvas, const FText& Title, const TArray<TPair<FText, FText>>& Infos, const FDrawInfoOptions& InDrawInfoOptions) const;`
- L128 _private prototype_ `void ForceTicks(uint32 NumberOfTicks);` — This function is used to force ViewportClient to tick becease when enabling Normals/Tangents/Binormals we need more than 1 tick for these to show on MH
- L140 _private prototype_ `void UpdateLightRigParentRotation(bool bJustFramedThisTick);` — Updates the light rig parent actor's yaw so the rig stays camera-relative, while respecting any externally applied rotation (level default, environment swap restore). Called from Tick. @param bJustFramedThisTick True if the viewport-framing first-focus ran on this same tick. In that case we skip tracking for this tick because FocusOnSelectedFrame's ToggleOrbitCamera calls rebase the camera rotation through ComputeOrbitMatrix's internal 90-degree offset, producing a transient yaw reading.
- L144 _private member_ `bool bIsViewportFramed;` — Flag whether an initial viewport camera framing has been performed.
- L154 _private member_ `TWeakObjectPtr<AActor> WeakLightRigParent;` — State for applying per-tick world-space camera-yaw deltas to the light rig's parent actor, keeping the light direction camera-relative as the user orbits. Each tick we read the mode-aware world-space camera yaw and add the shortest-arc delta to the parent's yaw. External writes to the parent (toolkit environment-swap restore, level defaults) are respected: the first observation of a new parent adopts its current yaw as baseline without writing.
- L155 _private member_ `double LastCameraYaw = 0.0;`
- L156 _private member_ `bool bHasPrevCameraYaw = false;`
- L159 _private member_ `bool bDrawFaceBones = false;` — Flag for showing Face bones in Draw function
- L162 _private member_ `bool bDrawBodyBones = false;` — Flag for showing Body bones in Draw function
- L165 _private member_ `EMetaHumanCharacterCameraFrame AutoSelectedFrame;` — Camera framing for auto framing mode.
- L168 _private member_ `EMetaHumanCharacterCameraFrame LastSelectedFrame;` — Last selected camera framing in viewport.
- L171 _private member_ `FText ViewportMessage;` — Viewport message.
- L174 _private member_ `TArray<TPair<FText, FText>> Shortcuts;` — Shortcuts
- L177 _private member_ `TOptional<FInt32Point> PreviousMousePosition;` — Previous mouse position
- L178 _private member_ `TOptional<FInt32Point> NextMousePosition;`
- L181 _private member_ `TOptional<FVector> SelectedPointFocusTarget;` — Target point for the SelectedPoint camera frame, set via SetSelectedPoint
- L184 _private member_ `TOptional<EMetaHumanCharacterCameraFrame> OverrideNextFocusFrame;` — When set, the next F press focuses on this frame instead of following the normal cycle, then resets to empty
- L196 _private member_ `TOptional<FCameraBookmark> CameraBookmarks[4];` — Camera bookmarks saved with Ctrl+1..4, recalled with 1..4
- L199 _private member_ `bool bEnvironmentHasLightRig = true;` — True when the loaded environment contains a light rig. See SetEnvironmentHasLightRig.
- L202 _private member_ `bool bEnvironmentHasBackground = true;` — True when the loaded environment contains a background actor. See SetEnvironmentHasBackground.
- L205 _private member_ `TArray<FTransform> FaceBonesWorldTransforms;` — Bone drawing information
- L206 _private member_ `TArray<FTransform> BodyBonesWorldTransforms;`
- L208 _private member_ `TArray<FLinearColor> FaceBoneColors;`
- L209 _private member_ `TArray<FLinearColor> BodyBoneColors;`
- L211 _private member_ `TArray<TRefCountPtr<HHitProxy>> HitProxies;`

#### struct `FMetaHumanCharacterViewportClient::FDrawInfoOptions`  
`struct FDrawInfoOptions`  
_L115-123_
- L117 _public member_ `FIntPoint TopCenter;`
- L118 _public member_ `bool bTitleLeft = true;`
- L119 _public member_ `int32 Padding = 2;`
- L120 _public member_ `FLinearColor TitleColor = FLinearColor::White;`
- L121 _public member_ `FLinearColor KeyTextColor = FLinearColor::White;`
- L122 _public member_ `FLinearColor ValueTextColor = FLinearColor::White;`

#### struct `FMetaHumanCharacterViewportClient::FCameraBookmark`  
`struct FCameraBookmark`  
_L187-193_
- desc: Saved camera state for a numbered bookmark slot
- L189 _public member_ `FVector Location;`
- L190 _public member_ `FVector LookAt;`
- L191 _public member_ `FRotator Rotation;`
- L192 _public member_ `float FOV;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace ViewportDefaults` (scope `UE::MetaHuman`)
- L15 _variable_ `constexpr float DefaultFOV = 18.001738f;` (scope `UE::MetaHuman::ViewportDefaults`) — Same FoV used in MetaHuman Creator
- L19 _variable_ `constexpr float DefaultNearClippingPlane = 1.0f;` (scope `UE::MetaHuman::ViewportDefaults`) — Default Perpective Clipping plane distances A value of 0 for the Far Clipping plane means infinity
- L20 _variable_ `constexpr float DefaultFarClippingPlane = 0.0f;` (scope `UE::MetaHuman::ViewportDefaults`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterEnvironmentLightRig.h` (Private)


#### class `UMetaHumanCharacterEnvironmentLightRig`  
`class UMetaHumanCharacterEnvironmentLightRig : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `UInterface`

#### class `IMetaHumanCharacterEnvironmentLightRig`  
`class IMetaHumanCharacterEnvironmentLightRig`  
_L19-30_
- desc: Interface implemented by actors that provide light rig functionality in the lighting environments of the Character editor
- L29 _public prototype_ `void SetRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MetaHuman|Lighting")` — Sets the rotation of the light rig

#### class `UMetaHumanCharacterEnvironmentBackground`  
`class UMetaHumanCharacterEnvironmentBackground : public UInterface`  
_L33-36_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `UInterface`

#### class `IMetaHumanCharacterEnvironmentBackground`  
`class IMetaHumanCharacterEnvironmentBackground`  
_L38-46_
- L45 _public prototype_ `void SetBackgroundColor(const FLinearColor& BackgroundColor);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MetaHuman|Background")`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterSkelMeshUtils.h` (Private)


#### enum `EVertexPositionsAndNormals`  
`enum class EVertexPositionsAndNormals : uint8`  
_L25-30_
- L27 _public enumerator_ `PositionOnly` — vertex positions only
- L28 _public enumerator_ `NormalsOnly` — vertex normals only
- L29 _public enumerator_ `Both` — both vertex positions and normals

#### struct `FMetaHumanCharacterSkelMeshUtils`  
`struct FMetaHumanCharacterSkelMeshUtils`  
_L33-214_
- desc: Helper with utility functions to modify Skeletal Mesh assets
- L45 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EUpdateFlags);`
- L55 _public prototype_ `static void UpdateSkelMeshFromDNA( TSharedRef<IDNAReader> InDNAReader, EUpdateFlags InUpdateFlags, TSharedRef<FDNAToSkelMeshMap>& InOutDNAToSkelMeshMap, EMetaHumanCharacterOrientation InCharacterOrientation, TNotNull<USkeletalMesh*> OutSkeletalMesh);` — Updates the input Skeleta Mesh with the DNA data pass by the reader. The update flags specifies which DNA info need to be updated, the rest are ignored. Note that the Skeletal Mesh will be re-build and the DNAToSkelMeshMap is updated to match the latest render data InOutDNAToSkelMeshMap should be a valid map for the current input DNA reader and skel mesh, see USkelMeshDNAUtils::CreateMapForUpdatingNeutralMesh()
- L65 _public prototype_ `static void UpdateMeshDescriptionFromLODModel(TNotNull<USkeletalMesh*> InSkeletalMesh);` — Updates and commits the Mesh Description of the input Skeletal Mesh for Import Model LODs of the mesh
- L75 _public prototype_ `static void UpdateMeshDescriptionFromLODModelVerticesNormalsAndTangents(TNotNull<USkeletalMesh*> InSkeletalMesh);` — Updates the vertex, normal, and tangent positions of the input mesh descriptions based on the input Skeletal Mesh Import Model LODs The method uses a subset of void FSkeletalMeshLODModel::GetMeshDescription(const USkeletalMesh *InSkeletalMesh, const int32 InLODIndex, FMeshDescription& OutMeshDescription) const where instead of recreating the mesh description from scratch, vertices, normals, and tangents are updated. If the mesh description does not match the LOD model, then it falls back to a full MeshDescription update using GetMeshDescription()
- L80 _public prototype_ `static bool CompareDnaToSkelMeshVertices( TSharedPtr<const IDNAReader> InDNAReader, TNotNull<const USkeletalMesh*> InSkeletalMesh, const FDNAToSkelMeshMap& InDNAToSkelMeshMap, float Tolerance = UE_KINDA_SMALL_NUMBER);` — Compares the vertex positions of each LOD in the input DNA and the Skeletal Mesh
- L92 _public prototype_ `static bool CompareDnaToStateVerticesAndNormals( TSharedPtr<const IDNAReader> InDNAReader, const TArray<FVector3f>& InStateVertices, const TArray<FVector3f>& InStateNormals, TSharedPtr<const FMetaHumanCharacterIdentity::FState> InState, float Tolerance = UE_KINDA_SMALL_NUMBER, TConstArrayView<int32> InMeshIndicesToCheck = {});` — Compares the vertex positions and normals of each LOD in the input DNA and the Skeletal Mesh Note that the face state is evaluated internally. @param InMeshIndicesToCheck Optional DNA mesh indices to check. When empty, every mesh in the DNA is checked.
- L106 _public prototype_ `static bool CompareDnaToStateVertices( TSharedPtr<const IDNAReader> InDNAReader, const TArray<FVector3f>& InStateVertices, TSharedPtr<const FMetaHumanCharacterIdentity::FState> InState, float Tolerance = UE_KINDA_SMALL_NUMBER, TConstArrayView<int32> InMeshIndicesToCheck = {});` — Compares the vertex positions of each LOD in the input DNA and the Skeletal Mesh Note that the face state is evaluated internally. @param InMeshIndicesToCheck Optional DNA mesh indices to check. When empty, every mesh in the DNA is checked.
- L114 _public prototype_ `static bool CheckDNACompatibility(IDNAReader* InDnaReaderA, IDNAReader* InDnaReaderB);` — Copy from the FDNAUtilities::CheckDNACompatibility in MetaHuman plugin
- L120 _public prototype_ `static void UpdateLODModelVertexPositions( TNotNull<USkeletalMesh*> InSkelMesh, const FMetaHumanRigEvaluatedState& InVerticesAndNormals, const FMetaHumanCharacterIdentity::FState& InState, const FDNAToSkelMeshMap& InDNAToSkelMeshMap, ELodUpdateOption InUpdateOption, EVertexPositionsAndNormals InVertexUpdateOption, TObjectPtr<USkeletalMesh> InMergedHeadAndBody = nullptr, const UE::MetaHuman::FMergedMeshMapping* InMergedMeshMapping = nullptr, bool bInUpdateMergedMeshNormals = false);` — Function overloads for body & face states to update the vertex positions of the Import Model in the input Skeletal Mesh based on the input (evaluated) vertices of the state. If a merged head and body mesh is provided, this will also be updated.
- L131 _public prototype_ `static void UpdateLODModelVertexPositions( TNotNull<USkeletalMesh*> InSkelMesh, const FMetaHumanRigEvaluatedState& InVerticesAndNormals, const FMetaHumanCharacterBodyIdentity::FState& InState, const FDNAToSkelMeshMap& InDNAToSkelMeshMap, ELodUpdateOption InUpdateOption, EVertexPositionsAndNormals InVertexUpdateOption, TObjectPtr<USkeletalMesh> InMergedHeadAndBody = nullptr, const UE::MetaHuman::FMergedMeshMapping* InMergedMeshMapping = nullptr, bool bInUpdateMergedMeshNormals = false);`
- L143 _public prototype_ `static TArray<FTransform> GetUECoordinateComponentTransforms(USkeletalMesh* InSkelMesh, const TSharedPtr<IDNAReader>& InArchetypeDNAReader, const TArray<FVector3f>& InJointPositions, const TArray<FRotator3f>& InJointRotations, FDNAToSkelMeshMap* InDNAToSkelMeshMap, EMetaHumanCharacterOrientation InCharacterOrientation);` — Converts component joint positions and rotations in DNA space and converts them to UE coordinates
- L151 _public prototype_ `static void UpdateBindPoseFromSource(TNotNull<USkeletalMesh*> InSourceSkelMesh, TNotNull<USkeletalMesh*> InTargetSkelMesh);` — Checks for shared joints between source and target meshes and updates target ref pose shared joints from the source ref pose
- L153 _public prototype_ `static void PopulateSkelMeshData(TNotNull<USkeletalMesh*> InSkelMesh, TSharedPtr<IDNAReader> InDNAReader, bool bIsFaceMesh);`
- L155 _public prototype_ `static void EnableRecomputeTangents(TNotNull<USkeletalMesh*> InSkelMesh);`
- L157 _public prototype_ `static TArray<FVector3f> GetComponentSpaceJointTranslations(TNotNull<USkeletalMesh*> InSkelMesh);`
- L160 _public prototype_ `static bool GetStaticMeshVertices(const TNotNull<UStaticMesh*> InTemplateStaticMesh, int32 InLodIndex, TArray<FVector3f>& OutVertices);` — Get vertices from template static mesh in vertex order of the mesh description
- L163 _public prototype_ `static bool GetSkeletalMeshVertices( const TNotNull<USkeletalMesh*> InTemplateSkeletalMesh, int32 InLodIndex, const TNotNull<FDNAToSkelMeshMap*> InDNAToSkelMeshMap, int32 InDNAMeshIndex, TArray<FVector3f>& OutVertices);` — Get vertices from template skeletal mesh, using DNAToSkelMeshMap to map vertex order from source model
- L175 _public prototype_ `static bool GetUVCorrespondingStaticMeshVertices( const TNotNull<UStaticMesh*> InTemplateStaticMesh, int32 InLodIndex, const TSharedPtr<IDNAReader>& InArchetypeDNAReader, int32 InDNAMeshIndex, TArray<FVector3f>& OutVertices);` — Gets corresponding vertices from template static mesh in the vertex order of the DNA archetype. Finds corresponding vertices by matching UVs. UV map of template mesh and DNA archetype should match and should have non-overlapping UVs with each part of the mesh its unique UV space.
- L187 _public prototype_ `static bool GetUVCorrespondingSkeletalMeshVertices( const TNotNull<USkeletalMesh*> InTemplateSkelMesh, int32 InLodIndex, const TNotNull<FDNAToSkelMeshMap*> InDNAToSkelMeshMap, const TSharedPtr<IDNAReader>& InArchetypeDNAReader, int32 InDNAMeshIndex, TArray<FVector3f>& OutVertices);` — Gets corresponding vertices from template skeletal mesh in the vertex order of the DNA archetype. Finds corresponding vertices by matching UVs. UV map of template mesh and DNA archetype should match and should have non-overlapping UVs with each part of the mesh its unique UV space.
- L199 _public prototype_ `static USkeletalMesh* GetSkeletalMeshAssetFromDNA(const TSharedPtr<IDNAReader>& InDNAReader, const FString& InAssetPath, const FString& InAssetName, const EMetaHumanImportDNAType InImportDNAType);` — Create a USkeletalMesh asset with provided path using the dna interchange system for a given dna data and name. The Skeletal mesh is created of a specified type and corresponding Skeleton is selected
- L201 _public prototype_ `static USkeletalMesh* CreateArchetypeSkelMeshFromDNA(const EMetaHumanImportDNAType InImportDNAType, TSharedPtr<IDNAReader>& OutArchetypeDnaReader);`
- L203 _public prototype_ `static UDNA* GetArchetypeDNAAsset(const EMetaHumanImportDNAType InImportDNAType, UObject* InOuter);`
- L205 _public prototype_ `static FString GetTransientArchetypeMeshAssetName(const EMetaHumanImportDNAType InImportDNAType);`
- L207 _public prototype_ `static class UPhysicsAsset* GetFaceArchetypePhysicsAsset(EMetaHumanCharacterTemplateType InTemplateType);`
- L208 _public prototype_ `static class USkeletalMeshLODSettings* GetFaceArchetypeLODSettings(EMetaHumanCharacterTemplateType InTemplateType);`
- L209 _public prototype_ `static TSoftObjectPtr<UObject> GetFaceArchetypeDefaultAnimatingRig(EMetaHumanCharacterTemplateType InTemplateType);`
- L211 _public prototype_ `static class UPhysicsAsset* GetBodyArchetypePhysicsAsset(EMetaHumanCharacterTemplateType InTemplateType);`
- L212 _public prototype_ `static class USkeletalMeshLODSettings* GetBodyArchetypeLODSettings(EMetaHumanCharacterTemplateType InTemplateType);`
- L213 _public prototype_ `static TSoftObjectPtr<UObject> GetBodyArchetypeDefaultAnimatingRig(EMetaHumanCharacterTemplateType InTemplateType);`

#### enum `FMetaHumanCharacterSkelMeshUtils::EUpdateFlags`  
`enum class EUpdateFlags : uint32`  
_L35-44_
- L37 _public enumerator_ `None = 0`
- L38 _public enumerator_ `BaseMesh = 1 << 0`
- L39 _public enumerator_ `Joints = 1 << 1`
- L40 _public enumerator_ `SkinWeights = 1 << 2`
- L41 _public enumerator_ `DNA = 1 << 3`
- L43 _public enumerator_ `All = MAX_uint32` — MorphTargets = 1 << 6, // TODO

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MetaHuman` (scope `UE`)
- L216 _prototype_ `ENUM_CLASS_FLAGS(FMetaHumanCharacterSkelMeshUtils::EUpdateFlags);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/MetaHumanCharacterTextureSynthesis.h` (Private)


#### class `FMetaHumanCharacterTextureSynthesis`  
`class FMetaHumanCharacterTextureSynthesis`  
_L17-123_
- desc: Helper class providing stateless static functions that implement the functionality for synthesizing and updating textures It provides for creating and updating synthesized images and textures
- L27 _public prototype_ `static UTexture2D* CreateFaceTextureFromSource(EFaceTextureType InTextureType, FImageView InTextureImage, bool bInMakeVirtualIfSupported);` — Creates a texture from the input image so that it can be used with the MetaHuman face materials. Sets the image data to the texture source and waits for the texture to be compiled. NOTE: This texture object cannot be used with the texture synthesize APIs below
- L38 _public prototype_ `static void InitFaceTextureSynthesizer(FMetaHumanFaceTextureSynthesizer& OutFaceTextureSynthesizer);` — Load the Texture Synthesis model and initialize all data needed for the OutFaceTextureSynthesizer
- L43 _public prototype_ `static void InitSynthesizedFaceData(const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, const TMap<EFaceTextureType, FMetaHumanCharacterTextureInfo>& InTextureInfo, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures, TMap<EFaceTextureType, FImage>& OutSynthesizedFaceImages);` — Initialize the necessary Texture Synthesis data, will not do anything if data have been already populated
- L52 _public prototype_ `static UTexture2D* CreateFaceTextureEditable(EFaceTextureType InTextureType, int32 InSizeX, int32 InSizeY);` — Create a texture of the given face type that is backed with an uncompressed buffer in main memory. This texture can be used with the Texture Generation API functions.
- L58 _public prototype_ `static void CreateSynthesizedFaceTextures(int32 InResolution, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures);` — Create the array of Textures required by the MH Character Face material OutSynthesizedFaceTextures should be empty
- L61 _public prototype_ `static bool AreTexturesAndImagesSuitableForSynthesis( const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, const TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& InSynthesizedFaceTextures, const TMap<EFaceTextureType, FImage>& InSynthesizedFaceImages);` — Returns true if the given textures and images are the correct size and format to accept the output of texture synthesis
- L67 _public prototype_ `static FMetaHumanFaceTextureSynthesizer::FTextureSynthesisParams SkinPropertiesToSynthesizerParams( const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer);` — Returns the parameters for the FaceTextureSynthesizer that correspond to the input Character Skin Properties
- L81 _public prototype_ `static bool SynthesizeFaceTextures( const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, TMap<EFaceTextureType, FImage>& OutCachedImages);` — Synthesize any face textures based on the input UV parameters and output the results to the OutCachedImages Only valid images in OutCachedImages are updated
- L93 _public prototype_ `static bool SynthesizeFaceAlbedoWithHFMap(EFaceTextureType InTextureType, const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, const TStaticArray<TArray<uint8>, 4>& InHFMaps, FImageView OutImage);` — Synthesize an albedo face texture using a specific HFMap (i.e. overrides the Texture property by using the input HF Map) InTextureType needs to be one of the base color enum values (Basecolor or Basecolor_Animated_CM1/2/3) InHFMaps contains the BGR buffer of (Resolution, Resolution, 3) in a flattened layout where Resolution is the OutImage width & height In the case of the neutral (base) map, then InHFMaps only needs to contain a valid buffer for the first entry in the array In the case where the texture type is an animated map, then InHFMaps needs to contain a valid buffer for the first entry in the array AND the animated map index
- L103 _public prototype_ `static bool SelectFaceTextures( const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, TMap<EFaceTextureType, FImage>& OutCachedImages);` — Select any face textures based on the High Frequency index and output the results to the OutCachedImages Only valid images in OutCachedImages are updated
- L111 _public prototype_ `static void UpdateTexture(TConstArrayView<uint8> InRawData, TNotNull<UTexture2D*> InOutTexture);` — Updates a single texture using data from the InRawData. It assumes the texture has enough space to allocated for the data
- L120 _public prototype_ `static bool UpdateFaceTextures( const TMap<EFaceTextureType, FImage>& InCachedImages, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures);` — Copies the synthesized cached image data to the output Texture Objects Copy from the respective cached image for each output texture type, or the neutral map if there is no image @param InCachedImages should contain at least the neutral maps for Basecolor, Normal & Cavity @param OutSynthesizedFaceTextures should contain a valid texture object for all supported EFaceTextureType types

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/SMetaHumanCharacterEditorPreviewSettingsView.h` (Private)


#### enum `EMetaHumanPreviewAssemblyVisibility`  
`enum class EMetaHumanPreviewAssemblyVisibility : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `Visible`
- L28 _public enumerator_ `Hidden`

#### enum `EMetaHumanCharacterAnimationController`  
`enum class EMetaHumanCharacterAnimationController : uint8`  
_L32-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `None UMETA(DisplayName = "None")`
- L35 _public enumerator_ `AnimSequence UMETA(DisplayName = "AnimSequence")`
- L36 _public enumerator_ `LiveLink UMETA(DisplayName = "LiveLink")`

#### enum `EMetaHumanAnimationType`  
`enum class EMetaHumanAnimationType : uint8`  
_L40-44_
- reflection: `UENUM()`
- L42 _public enumerator_ `SpecificAnimation`
- L43 _public enumerator_ `TemplateAnimation`

#### struct `FMetaHumanTemplateAnimationRow`  
`struct FMetaHumanTemplateAnimationRow : public FTableRowBase`  
_L47-58_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L54 _public member_ `TSoftObjectPtr<UAnimSequence> FaceAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TemplateAnimation")`
- L57 _public member_ `TSoftObjectPtr<UAnimSequence> BodyAnimation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TemplateAnimation")`

#### class `UMetaHumanCharacterEditorPreviewSceneDescription`  
`class UMetaHumanCharacterEditorPreviewSceneDescription : public UObject`  
_L62-148_
- reflection: `UCLASS()`
- inherits: `UObject`
- L67 _public prototype_ `UMetaHumanCharacterEditorPreviewSceneDescription();`
- L70 _public member_ `FOnMetaHumanCharacterAnimationChanged OnAnimationChanged;` — Have just one delegate and figure our what changed separately?
- L71 _public member_ `FOnMetaHumanCharacterPlayRateChanged OnPlayRateChanged;`
- L72 _public member_ `FOnMetaHumanCharacterLiveLinkSubjectChanged OnLiveLinkSubjectChanged;`
- L73 _public member_ `FOnMetaHumanCharacterAnimationControllerChanged OnAnimationControllerChanged;`
- L74 _public member_ `FOnMetaHumanPreviewModeChanged OnPreviewModeChanged;`
- L75 _public member_ `FOnMetaHumanCharacterGroomHiddenChanged OnGroomHiddenChanged;`
- L76 _public member_ `FOnMetaHumanCharacterClothingHiddenChanged OnClothingHiddenChanged;`
- L79 _public member_ `bool bAnimationControllerEnabled = true;` — `UPROPERTY(Transient)`
- L82 _public member_ `EMetaHumanCharacterAnimationController AnimationController = EMetaHumanCharacterAnimationController::AnimSequence;` — `UPROPERTY(EditAnywhere, DisplayName = "Animation Controller", Category = "Animation")`
- L86 _public member_ `EMetaHumanAnimationType FaceAnimationType = EMetaHumanAnimationType::SpecificAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "FaceAnimation", meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence", EditConditionHides))` — Anim sequence Face Animation options
- L89 _public member_ `TObjectPtr<UAnimSequence> FaceSpecificAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "FaceAnimation",meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence && FaceAnimationType == EMetaHumanAnimationType::SpecificAnimation", EditConditionHides))`
- L92 _public member_ `FName FaceTemplateAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "FaceAnimation", meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence && FaceAnimationType == EMetaHumanAnimationType::TemplateAnimation", EditConditionHides, GetOptions="GetTemplateAnimationOptions"))`
- L96 _public member_ `EMetaHumanAnimationType BodyAnimationType = EMetaHumanAnimationType::SpecificAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "BodyAnimation", meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence", EditConditionHides))` — Anim sequence Body Animation options
- L99 _public member_ `TObjectPtr<UAnimSequence> BodySpecificAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "BodyAnimation",meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence && BodyAnimationType == EMetaHumanAnimationType::SpecificAnimation", EditConditionHides))`
- L102 _public member_ `FName BodyTemplateAnimation;` — `UPROPERTY(EditAnywhere, Transient, Category = "BodyAnimation",meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence && BodyAnimationType == EMetaHumanAnimationType::TemplateAnimation", EditConditionHides, GetOptions = "GetTemplateAnimationOptions"))`
- L105 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Transient, Category = "Animation", meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::AnimSequence", EditConditionHides, ClampMin = "0.05", ClampMax = "10.0"))`
- L108 _public member_ `FLiveLinkSubjectName LiveLinkSubjectName;` — `UPROPERTY(EditAnywhere, Transient, Category = "Animation", meta = (EditCondition = "AnimationController == EMetaHumanCharacterAnimationController::LiveLink", EditConditionHides))`
- L111 _public member_ `EMetaHumanPreviewAssemblyVisibility PreviewAssemblyGrooms = EMetaHumanPreviewAssemblyVisibility::Visible;` — `UPROPERTY(EditAnywhere, Transient, DisplayName = "Preview", Category = "Grooms")`
- L114 _public member_ `EMetaHumanPreviewAssemblyVisibility PreviewAssemblyClothing = EMetaHumanPreviewAssemblyVisibility::Visible;` — `UPROPERTY(EditAnywhere, Transient, DisplayName = "Preview", Category = "Outfit Clothing")`
- L117 _public member_ `TObjectPtr<UDataTable> TemplateAnimationDataTable;` — `UPROPERTY(Transient)`
- L119 _public member_ `FName DefaultBodyTemplateAnimationName;`
- L120 _public member_ `FName DefaultFaceTemplateAnimationName;`
- L125 _public prototype_ `void AddTemplateAnimationsFromDataTable(const FSoftObjectPath& DataTableObjectPath);` — Add template animations from the given data table asset to the list of available template animations for previewing.
- L127 _public prototype_ `void OnRiggingStateChanged(TNotNull<UMetaHumanCharacter*> Character);`
- L129 _public prototype_ `void SetAnimationController(EMetaHumanCharacterAnimationController InAnimationController);`
- L131 _public prototype_ `void SceneDescriptionPropertyChanged(const FName& PropertyName);`
- L133 _public prototype_ `void RefreshAnimationData();`
- L136 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L137 _private prototype_ `FName GetFirstLiveLinkSubject() const;`
- L140 _private prototype_ `TArray<FName> GetTemplateAnimationOptions() const;` — `UFUNCTION()`
- L143 _public prototype_ `UAnimSequence* GetTemplateAnimation(const bool bIsFaceAnimation, const FName& AnimationName);`
- L147 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `SMetaHumanCharacterEditorPreviewSettingsView`  
`class SMetaHumanCharacterEditorPreviewSettingsView : public SCompoundWidget`  
_L150-164_
- inherits: `SCompoundWidget`
- L154 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorPreviewSettingsView)`
- L155 _public prototype_ `SLATE_ARGUMENT(UMetaHumanCharacterEditorPreviewSceneDescription*, SettingsObject) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L162 _private member_ `TWeakObjectPtr<UMetaHumanCharacterEditorPreviewSceneDescription> PreviewSceneDescription;`
- L163 _private member_ `TSharedPtr<class IDetailsView> SettingsDetailsView;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMetaHumanCharacterAnimationChanged, UAnimSequence*, UAnimSequence*) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterPlayRateChanged, float) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterLiveLinkSubjectChanged, FLiveLinkSubjectName) DECLARE_DELEGATE_ThreeParams(FOnMetaHumanCharacterAnimationControllerChanged, EMetaHumanCharacterAnimationController, UAnimSequence*, UAnimSequence*) DECLARE_DELEGATE_OneParam(FOnMetaHumanPreviewModeChanged, EMetaHumanCharacterSkinPreviewMaterial) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterPlayRateChanged, float) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterLiveLinkSubjectChanged, FLiveLinkSubjectName) DECLARE_DELEGATE_ThreeParams(FOnMetaHumanCharacterAnimationControllerChanged, EMetaHumanCharacterAnimationController, UAnimSequence*, UAnimSequence*) DECLARE_DELEGATE_OneParam(FOnMetaHumanPreviewModeChanged, EMetaHumanCharacterSkinPreviewMaterial) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterLiveLinkSubjectChanged, FLiveLinkSubjectName) DECLARE_DELEGATE_ThreeParams(FOnMetaHumanCharacterAnimationControllerChanged, EMetaHumanCharacterAnimationController, UAnimSequence*, UAnimSequence*) DECLARE_DELEGATE_OneParam(FOnMetaHumanPreviewModeChanged, EMetaHumanCharacterSkinPreviewMaterial) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L19 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMetaHumanCharacterAnimationControllerChanged, EMetaHumanCharacterAnimationController, UAnimSequence*, UAnimSequence*) DECLARE_DELEGATE_OneParam(FOnMetaHumanPreviewModeChanged, EMetaHumanCharacterSkinPreviewMaterial) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanPreviewModeChanged, EMetaHumanCharacterSkinPreviewMaterial) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterGroomHiddenChanged, EMetaHumanPreviewAssemblyVisibility) DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterClothingHiddenChanged, EMetaHumanPreviewAssemblyVisibility) UENUM() enum class EMetaHumanPreviewAssemblyVisibility : uint8 { Visible, Hidden };`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/SMetaHumanPreviewSceneDetailCustomization.h` (Private)


#### class `FMetaHumanPreviewSceneCustomization`  
`class FMetaHumanPreviewSceneCustomization : public IDetailCustomization`  
_L7-12_
- inherits: `IDetailCustomization`
- L10 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L11 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/Customizations/MetaHumanCharacterEditorCostumeItemDetailCustomization.h` (Private)


#### class `FCostumeParametersOverridesDetails`  
`class FCostumeParametersOverridesDetails : public FPropertyBagInstanceDataDetails`  
_L10-59_
- inherits: `FPropertyBagInstanceDataDetails`
- desc: A detail customization for the costume tool property bag parameters overrides
- L13 _public function_ `FCostumeParametersOverridesDetails(const TSharedPtr<IPropertyHandle> InVariableStructProperty, const TSharedPtr<IPropertyUtilities>& InPropUtils, UMetaHumanCharacterEditorCostumeItem* InItem) : FPropertyBagInstanceDataDetails(InVariableStructProperty, InPropUtils, false) , Item(InItem)`
- L21 _protected prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L25 _protected prototype_ `TSharedRef<SWidget> MakeHighlightsVariationWidget(const TSharedRef<IPropertyHandle> PropertyHandle) const;` — Makes the widget use to correctly display the highlights variation property
- L28 _protected prototype_ `void HandleUVColorPickerProperties(const TSharedRef<IPropertyHandle> PropertyHandle, IDetailPropertyRow& ChildRow);` — Handles the customization of the properties which require a color picker
- L31 _protected prototype_ `void TryMakeUVColorPicker(TNotNull<UTexture2D*> ColorPickerTexture);` — Tries to make the UV color picker for gathering melanin and redness properties
- L34 _protected prototype_ `FVector2f GetPropertyUV(FName PropertyName, const void* PropertyBagContainerAddress) const;` — Gets the UV coordinates values for the property with the given name
- L37 _protected prototype_ `void OnPropertyUVChanged(const FVector2f& InUV, bool bIsDragging, FName PropertyName, void* PropertyBagContainerAddress);` — Called when the UV coordinates of the property with the given name have been changed
- L40 _protected member_ `FName UVPropertyName = NAME_None;` — The property name of the current UV property being customized
- L43 _protected member_ `TMap<FName, TTuple<TSharedPtr<IPropertyHandle>, TSharedPtr<IPropertyHandle>>> UVPropertyNameToHandlesMap;` — A map that that relates the UV properties handle to its matching property name
- L46 _protected member_ `TSharedPtr<IPropertyHandle> UPropertyHandle;` — The U property handle used for customizing UV properties
- L49 _protected member_ `TSharedPtr<IPropertyHandle> VPropertyHandle;` — The V property handle used for customizing UV properties
- L52 _protected member_ `IDetailPropertyRow* UPropertyRow = nullptr;` — The detail row for the U property
- L55 _protected member_ `IDetailPropertyRow* VPropertyRow = nullptr;` — The detail row for the V property
- L58 _protected member_ `TWeakObjectPtr<UMetaHumanCharacterEditorCostumeItem> Item;` — The item which holds the reference to the property bag this customization is based on

#### class `FMetaHumanCharacterEditorCostumeItemDetailCustomization`  
`class FMetaHumanCharacterEditorCostumeItemDetailCustomization : public IDetailCustomization`  
_L65-76_
- inherits: `IDetailCustomization`
- desc: Detail Customization for the UMetaHumanCharacterEditorCostumeItem class, which is used for editing the costume tool properties
- L68 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L74 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/Customizations/MetaHumanCharacterEditorPipelineToolPropertiesCustomization.h` (Private)


#### class `FMetaHumanCharacterEditorPipelineToolPropertiesCustomization`  
`class FMetaHumanCharacterEditorPipelineToolPropertiesCustomization : public IDetailCustomization`  
_L23-41_
- inherits: `IDetailCustomization`
- desc: Detail Customization for the UMetaHumanCharacterEditorPipelineToolProperties class, which is used for selecting a build pipeline
- L26 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;` — IDetailCustomization interface
- L33 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L38 _private prototype_ `void RebuildDetailsView();`
- L40 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorBodyEditingTools.h` (Private)


#### enum `EMetaHumanCharacterBodyEditingTool`  
`enum class EMetaHumanCharacterBodyEditingTool : uint8`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `Model`
- L20 _public enumerator_ `Blend`

#### class `UMetaHumanCharacterEditorBodyToolBuilder`  
`class UMetaHumanCharacterEditorBodyToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L24-37_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L32 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L36 _public member_ `EMetaHumanCharacterBodyEditingTool ToolType = EMetaHumanCharacterBodyEditingTool::Blend;` — `UPROPERTY()`

#### class `FMetaHumanCharacterClothVisibilityBase`  
`class FMetaHumanCharacterClothVisibilityBase`  
_L39-50_
- L43 _protected member_ `TOptional<EMetaHumanCharacterSkinPreviewMaterial> SavedPreviewMaterial;` — Storage for the last preview material set
- L46 _protected member_ `TOptional<EMetaHumanClothingVisibilityState> SavedClothingVisibilityState;` — Storage for the last preview material set
- L49 _protected prototype_ `void UpdateClothVisibility(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, bool bStartBodyModeling, bool bUpdateMaterialHiddenFaces = true);` — Helper to update the visibility of the input character if needed

#### class `UMetaHumanCharacterBodyModelSubToolBase`  
`class UMetaHumanCharacterBodyModelSubToolBase : public UInteractiveToolPropertySet`  
_L53-65_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveToolPropertySet`
- L58 _public function_ `virtual void SetEnabled(bool bInIsEnabled)`
- L64 _public member_ `bool bSubToolActive = true;` — `UPROPERTY(Transient)`

#### struct `FMetaHumanCharacterBodyConstraintItem`  
`struct FMetaHumanCharacterBodyConstraintItem`  
_L68-76_
- L70 _public member_ `FName Name;`
- L71 _public member_ `bool bIsActive = false;`
- L72 _public member_ `float TargetMeasurement = 100.0f;`
- L73 _public member_ `float ActualMeasurement = 100.0f;`
- L74 _public member_ `float MinMeasurement = 0.0f;`
- L75 _public member_ `float MaxMeasurement = 200.0f;`

#### class `UMetaHumanCharacterParametricBodyProperties`  
`class UMetaHumanCharacterParametricBodyProperties : public UMetaHumanCharacterBodyModelSubToolBase, public FMetaHumanCharacterClothVisibilityBase`  
_L82-127_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterBodyModelSubToolBase,FMetaHumanCharacterClothVisibilityBase`
- L88 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L91 _public prototype_ `bool IsFixedBodyType() const;`
- L93 _public prototype_ `void OnBeginConstraintEditing();`
- L94 _public prototype_ `void OnConstraintItemsChanged(bool bInCommitChange);`
- L95 _public prototype_ `void ResetConstraints();`
- L96 _public prototype_ `void PerformParametricFit();`
- L98 _public prototype_ `TArray<FMetaHumanCharacterBodyConstraintItemPtr> GetConstraintItems(const TArray<FName>& ConstraintNames);`
- L99 _public prototype_ `void OnBodyStateChanged();`
- L106 _public prototype_ `void UpdateMeasurements(bool bUpdateRanges = true);` — Refreshes BodyConstraintItems' ActualMeasurement (and optionally MinMeasurement / MaxMeasurement) plus ActiveContours from the current body state. @param bUpdateRanges  When true, also recomputes Min/MaxMeasurement via BodyState->GetBodyConstraints()
- L110 _public member_ `float ParametersRangeMultiplier = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Parametric Body", meta = (UIMin = "1.0", UIMax = "5.0", ClampMin = "1.0", ClampMax = "5.0"))` — Multiplier applied to the measurement ranges defined in the body model to expand or contract the range of the sliders for each constraint. This does not affect the actual constraints in the model, just the UI representation of them.
- L114 _public member_ `bool bShowMeasurements = true;` — `UPROPERTY(EditAnywhere, Category = "Parametric Body")` — Show debug lines for active measurements in viewport
- L118 _public member_ `bool bScaleRangesByHeight = true;` — `UPROPERTY(EditAnywhere, Category = "Parametric Body")` — Scale the measurement ranges by height to help stay within realistic model proportions
- L122 _public member_ `bool bUnlockBodyRanges = false;` — `UPROPERTY(EditAnywhere, Category = "Parametric Body")` — Unlock the measurement ranges to allow for more flexible body proportions
- L124 _public member_ `TArray<FMetaHumanCharacterBodyConstraintItemPtr> BodyConstraintItems;`
- L125 _public member_ `TArray<TArray<FVector>> ActiveContours;`
- L126 _public member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> PreviousBodyState;`

#### enum `EMetaHumanCharacterFixedBodyToolHeight`  
`enum class EMetaHumanCharacterFixedBodyToolHeight : uint8`  
_L130-135_
- reflection: `UENUM()`
- L132 _public enumerator_ `Short`
- L133 _public enumerator_ `Average`
- L134 _public enumerator_ `Tall`

#### class `UMetaHumanCharacterFixedCompatibilityBodyProperties`  
`class UMetaHumanCharacterFixedCompatibilityBodyProperties : public UMetaHumanCharacterBodyModelSubToolBase`  
_L138-155_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterBodyModelSubToolBase`
- L145 _public member_ `EMetaHumanCharacterFixedBodyToolHeight Height = EMetaHumanCharacterFixedBodyToolHeight::Average;` — `UPROPERTY(EditAnywhere, Category = "Body")`
- L148 _public member_ `EMetaHumanBodyType MetaHumanBodyType = EMetaHumanBodyType::BlendableBody;` — `UPROPERTY(EditAnywhere, Category = "Body")`
- L150 _public function_ `int32 GetHeightIndex() const`
- L151 _public prototype_ `void UpdateHeightFromBodyType();`
- L153 _public prototype_ `void OnBodyStateChanged();`
- L154 _public prototype_ `void OnMetaHumanBodyTypeChanged();`

#### class `UMetaHumanCharacterEditorBodyModelTool`  
`class UMetaHumanCharacterEditorBodyModelTool : public UMetaHumanCharacterEditorToolWithSubTools`  
_L158-182_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithSubTools`
- L164 _public prototype_ `virtual void Setup() override;`
- L165 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L167 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L170 _public prototype_ `void SetEnabledSubTool(UMetaHumanCharacterBodyModelSubToolBase* InSubTool, bool bInEnabled);`
- L173 _public member_ `TObjectPtr<UMetaHumanCharacterParametricBodyProperties> ParametricBodyProperties;` — `UPROPERTY()`
- L176 _public member_ `TObjectPtr<UMetaHumanCharacterFixedCompatibilityBodyProperties> FixedCompatibilityBodyProperties;` — `UPROPERTY()`
- L179 _public member_ `TObjectPtr<UMetaHumanCharacterEditorHeadAndBodyParameterProperties> BodyParameterProperties;` — `UPROPERTY()`
- L181 _public member_ `bool bNeedsFullUpdate = false;`

#### class `UBodyStateChangeTransactor`  
`class UBodyStateChangeTransactor : public UObject, public IMeshStateChangeTransactorInterface, public FMetaHumanCharacterClothVisibilityBase`  
_L186-204_
- reflection: `UCLASS()`
- inherits: `UObject,IMeshStateChangeTransactorInterface,FMetaHumanCharacterClothVisibilityBase`
- L191 _public prototype_ `virtual FSimpleMulticastDelegate& GetStateChangedDelegate(UMetaHumanCharacter* InMetaHumanCharacter) override;`
- L193 _public prototype_ `virtual void CommitShutdownState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, EToolShutdownType InShutdownType, const FText& InCommandChangeDescription) override;`
- L195 _public prototype_ `virtual void StoreBeginDragState(UMetaHumanCharacter* InMetaHumanCharacter) override;`
- L196 _public prototype_ `virtual void CommitEndDragState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, const FText& InCommandChangeDescription) override;`
- L198 _public prototype_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> GetBeginDragState() const;`
- L203 _protected member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> BeginDragState;` — Hold the state of the character when a dragging operation begins so it can be undone while the tool is active

#### class `UDualStateChangeTransactor`  
`class UDualStateChangeTransactor : public UObject, public IMeshStateChangeTransactorInterface, public FMetaHumanCharacterClothVisibilityBase`  
_L207-236_
- reflection: `UCLASS()`
- inherits: `UObject,IMeshStateChangeTransactorInterface,FMetaHumanCharacterClothVisibilityBase`
- L212 _public function_ `bool IsBodyManipulator(int32 InIndex) const`
- L213 _public function_ `void SetActiveManipulatorIndex(int32 InIndex)`
- L214 _public function_ `void SetBlendBothTypes()`
- L215 _public function_ `void SetNumBodyManipulators(int32 InNum)`
- L217 _public function_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> GetBodyBeginDragState() const`
- L218 _public function_ `TSharedRef<FMetaHumanCharacterIdentity::FState> GetFaceBeginDragState() const`
- L221 _public prototype_ `virtual FSimpleMulticastDelegate& GetStateChangedDelegate(UMetaHumanCharacter* InMetaHumanCharacter) override;` — IMeshStateChangeTransactorInterface
- L222 _public prototype_ `virtual void CommitShutdownState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, EToolShutdownType InShutdownType, const FText& InCommandChangeDescription) override;`
- L223 _public prototype_ `virtual void StoreBeginDragState(UMetaHumanCharacter* InMetaHumanCharacter) override;`
- L224 _public prototype_ `virtual void CommitEndDragState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, const FText& InCommandChangeDescription) override;`
- L227 _protected member_ `int32 NumBodyManipulators = 0;`
- L228 _protected member_ `int32 ActiveManipulatorIndex = INDEX_NONE;`
- L229 _protected member_ `bool bBlendBothTypes = false;`
- L230 _protected member_ `bool bDelegatesBound = false;`
- L232 _protected member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> BodyBeginDragState;`
- L233 _protected member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> FaceBeginDragState;`
- L235 _protected member_ `FSimpleMulticastDelegate CombinedStateChangedDelegate;`

#### class `UMetaHumanCharacterEditorHeadAndBodyBlendToolProperties`  
`class UMetaHumanCharacterEditorHeadAndBodyBlendToolProperties : public UMetaHumanCharacterEditorMeshBlendToolProperties`  
_L239-263_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorMeshBlendToolProperties`
- L244 _public prototype_ `bool IsFixedBodyType() const;`
- L246 _public prototype_ `void PerformParametricFit() const;`
- L250 _public member_ `EBlendOptions FaceBlendOptions = EBlendOptions::Both;` — `UPROPERTY(EditAnywhere, DisplayName = "Blend Space", Category = "BlendTool", meta = (ShowOnlyInnerProperties))` — Blend facial features, proportions, or both
- L254 _public member_ `EBodyBlendOptions BodyBlendOptions = EBodyBlendOptions::Both;` — `UPROPERTY(EditAnywhere, DisplayName = "Blend Type", Category = "BlendTool")` — Blend shape, skeleton, or both
- L258 _public member_ `bool bShowManipulators = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Show Manipulators", Category = "BlendTool")` — Show or hide all manipulator gizmos
- L262 _public member_ `TArray<TSoftObjectPtr<UMetaHumanCharacter>> PresetCharacters;` — `UPROPERTY()` — Soft references to the preset characters assigned to each thumbnail slot.

#### class `UMetaHumanCharacterEditorHeadAndBodyBlendTool`  
`class UMetaHumanCharacterEditorHeadAndBodyBlendTool : public UMetaHumanCharacterEditorMeshBlendTool`  
_L266-309_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorMeshBlendTool`
- L272 _public prototype_ `virtual void Setup() override;`
- L273 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L274 _public prototype_ `virtual void AddMetaHumanCharacterPreset(class UMetaHumanCharacter* InCharacterPreset, int32 InItemIndex) override;`
- L275 _public prototype_ `virtual void RemoveMetaHumanCharacterPreset(int32 InItemIndex) override;`
- L276 _public prototype_ `virtual void BlendToMetaHumanCharacterPreset(UMetaHumanCharacter* InCharacterPreset) override;`
- L277 _public prototype_ `virtual void BlendToMetaHumanCharacterPresetHeadOnly(UMetaHumanCharacter* InCharacterPreset) override;`
- L278 _public prototype_ `virtual void BlendToMetaHumanCharacterPresetBodyOnly(UMetaHumanCharacter* InCharacterPreset) override;`
- L283 _protected prototype_ `virtual void InitStateChangeTransactor() override;`
- L284 _protected prototype_ `virtual const FText GetDescription() const override;`
- L285 _protected prototype_ `virtual const FText GetCommandChangeDescription() const override;`
- L286 _protected prototype_ `virtual const FText GetCommandChangeIntermediateDescription() const override;`
- L287 _protected prototype_ `virtual float GetManipulatorScale() const override;`
- L288 _protected prototype_ `virtual TArray<FVector3f> GetManipulatorPositions() const override;`
- L292 _protected prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L296 _protected prototype_ `virtual TArray<FVector3f> BlendPresets(int32 InManipulatorIndex, const TArray<float>& Weights) override;`
- L297 _protected prototype_ `virtual float GetAncestryCircleRadius() const override;`
- L302 _private member_ `mutable int32 NumBodyManipulators = 0;` — Cached number of body manipulators for index routing.
- L305 _private member_ `TArray<TSharedPtr<const FMetaHumanCharacterIdentity::FState>> FacePresetStates;` — Holds the face states of the presets.
- L308 _private member_ `TArray<TSharedPtr<const FMetaHumanCharacterBodyIdentity::FState>> BodyPresetStates;` — Holds the body states of the presets.

#### Free symbols / members of external scopes

- L78 _typedef_ `using FMetaHumanCharacterBodyConstraintItemPtr = TSharedPtr<FMetaHumanCharacterBodyConstraintItem>;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorCostumeTools.h` (Private)


#### enum `EMetaHumanCharacterCostumeEditingTool`  
`enum class EMetaHumanCharacterCostumeEditingTool : uint8`  
_L19-22_
- reflection: `UENUM()`
- L21 _public enumerator_ `Costume`

#### enum `EMetaHumanCharacterEditorHighlightsVariation`  
`enum class EMetaHumanCharacterEditorHighlightsVariation : uint8`  
_L26-32_
- reflection: `UENUM()`
- desc: Enum for displaying grooms highlights variations in the Costume Tool
- L28 _public enumerator_ `Bold`
- L29 _public enumerator_ `Blended`
- L30 _public enumerator_ `Traditional`
- L31 _public enumerator_ `Thin`

#### class `UMetaHumanCharacterEditorCostumeToolBuilder`  
`class UMetaHumanCharacterEditorCostumeToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L35-53_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L42 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L43 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L47 _public member_ `EMetaHumanCharacterCostumeEditingTool ToolType = EMetaHumanCharacterCostumeEditingTool::Costume;` — `UPROPERTY()`
- L51 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMetaHumanCharacterEditorCostumeItem`  
`class UMetaHumanCharacterEditorCostumeItem : public UObject`  
_L56-75_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L62 _public member_ `FName SlotName;` — `UPROPERTY()`
- L65 _public member_ `FMetaHumanPaletteItemPath ItemPath;` — `UPROPERTY()`
- L68 _public member_ `TWeakObjectPtr<UMetaHumanWardrobeItem> WardrobeItem;` — `UPROPERTY()`
- L71 _public member_ `FInstancedPropertyBag InstanceParameters;` — `UPROPERTY(EditAnywhere, Category = "Overrides", meta = (FixedLayout, ShowOnlyInnerProperties))`
- L74 _public member_ `FInstancedPropertyBag DefaultValues;` — `UPROPERTY()`

#### class `UMetaHumanCharacterEditorCostumeToolProperties`  
`class UMetaHumanCharacterEditorCostumeToolProperties : public UInteractiveToolPropertySet`  
_L81-95_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: The Detail Customization for this class contains the costume editing UI
- L87 _public member_ `TObjectPtr<UMetaHumanCharacter> Character;` — `UPROPERTY()`
- L90 _public member_ `TObjectPtr<UMetaHumanCollection> Collection;` — `UPROPERTY()`
- L94 _public member_ `TArray<TObjectPtr<UMetaHumanCharacterEditorCostumeItem>> CostumeItems;` — `UPROPERTY(EditAnywhere, Category = "Costume", meta = (ShowOnlyInnerProperties))` — The array of costume items containing costume parameters

#### class `UMetaHumanCharacterEditorCostumeTool`  
`class UMetaHumanCharacterEditorCostumeTool : public USingleTargetWithSelectionTool`  
_L101-122_
- reflection: `UCLASS()`
- inherits: `USingleTargetWithSelectionTool`
- desc: The Costume Tool allows the user to add, remove and apply adornments, such as hair and clothing
- L107 _public function_ `UMetaHumanCharacterEditorCostumeToolProperties* GetCostumeToolProperties() const` — Get the Costume Tool properties.
- L110 _public prototype_ `virtual void Setup() override;`
- L112 _public function_ `virtual bool HasCancel() const override`
- L113 _public function_ `virtual bool HasAccept() const override`
- L114 _public function_ `virtual bool CanAccept() const override`
- L117 _public prototype_ `void UpdateCostumeItems();`
- L121 _private member_ `TObjectPtr<UMetaHumanCharacterEditorCostumeToolProperties> PropertyObject;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorExportToolBase.h` (Private)


#### class `UMetaHumanCharacterEditorExportToolBuilder`  
`class UMetaHumanCharacterEditorExportToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L17-34_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- desc: Shared builder for all Export tools. Set ToolClass to the specific export tool subclass to create.
- L24 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L28 _public member_ `TSubclassOf<class UMetaHumanCharacterEditorExportToolBase> ToolClass;` — `UPROPERTY()`
- L33 _private member_ `mutable TStrongObjectPtr<UInteractiveToolPropertySet> PersistentProperties;` — Long-lived property set, lazily created on the first BuildTool call.

#### class `UMetaHumanCharacterEditorExportToolBase`  
`class UMetaHumanCharacterEditorExportToolBase : public USingleSelectionTool`  
_L41-85_
- reflection: `UCLASS(Abstract)`
- inherits: `USingleSelectionTool`
- desc: Abstract base class for all Export tools. Subclasses provide the concrete property set class via GetExportPropertiesClass and override CanExport / Export / GetExportButtonText.
- L48 _public prototype_ `virtual void Setup() override;`
- L49 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L51 _public function_ `virtual bool HasCancel() const override`
- L52 _public function_ `virtual bool HasAccept() const override`
- L53 _public function_ `virtual bool CanAccept() const override`
- L57 _public function_ `UInteractiveToolPropertySet* GetExportProperties() const` — Returns the active export property set.
- L60 _public function_ `void InitializeExportProperties(UInteractiveToolPropertySet* InExportProperties)` — Called by the builder to inject the property set this tool will display.
- L66 _public prototype_ `virtual UClass* GetExportPropertiesClass() const PURE_VIRTUAL(UMetaHumanCharacterEditorExportToolBase::GetExportPropertiesClass, return nullptr;);` — Returns the concrete UInteractiveToolPropertySet subclass this tool wants.
- L69 _public prototype_ `virtual bool CanExport(FText& OutErrorMsg) const;` — Returns true if the export can proceed.
- L72 _public prototype_ `virtual void Export() const;` — Performs the export.
- L75 _public prototype_ `virtual FText GetExportButtonText() const;` — Returns the text to display on the Export button.
- L80 _protected prototype_ `virtual FText GetExportToolDisplayName() const PURE_VIRTUAL(UMetaHumanCharacterEditorExportToolBase::GetExportToolDisplayName, return FText::GetEmpty(););` — Returns the display name for this export tool.
- L84 _protected member_ `TObjectPtr<UInteractiveToolPropertySet> ExportProperties;` — `UPROPERTY()` — The property set displayed in this tool's details panel. Owned by the builder.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorExportTools.h` (Private)


#### class `UMetaHumanCharacterEditorDCCExportProperties`  
`class UMetaHumanCharacterEditorDCCExportProperties : public UInteractiveToolPropertySet`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L19 _public member_ `FDirectoryPath ExternalPath;` — `UPROPERTY(EditAnywhere, Category = "DCC Export Options")`
- L22 _public member_ `bool bBakeMakeUp = false;` — `UPROPERTY(EditAnywhere, Category = "DCC Export Options")`
- L25 _public member_ `bool bCompressInZipFile = false;` — `UPROPERTY(EditAnywhere, Category = "DCC Export Options")`
- L28 _public member_ `FString ArchiveName;` — `UPROPERTY(EditAnywhere, Category = "DCC Export Options", meta = (EditCondition = "bCompressInZipFile", EditConditionHides))`

#### class `UMetaHumanCharacterEditorDCCExportTool`  
`class UMetaHumanCharacterEditorDCCExportTool : public UMetaHumanCharacterEditorExportToolBase`  
_L32-48_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorExportToolBase`
- L38 _protected prototype_ `virtual UClass* GetExportPropertiesClass() const override;`
- L39 _protected prototype_ `virtual FText GetExportToolDisplayName() const override;`
- L44 _public prototype_ `virtual FText GetExportButtonText() const override;`
- L45 _public prototype_ `virtual bool CanExport(FText& OutErrorMsg) const override;`
- L46 _public prototype_ `virtual void Export() const override;`

#### class `UMetaHumanCharacterEditorDNAExportProperties`  
`class UMetaHumanCharacterEditorDNAExportProperties : public UInteractiveToolPropertySet`  
_L53-67_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L60 _public member_ `FDirectoryPath ExternalPath;` — `UPROPERTY(EditAnywhere, Category = "DNA File Export Options")`
- L63 _public member_ `bool bDNAHead = true;` — `UPROPERTY(EditAnywhere, Category = "DNA File Export Options", DisplayName = "DNA Head")`
- L66 _public member_ `bool bDNABody = true;` — `UPROPERTY(EditAnywhere, Category = "DNA File Export Options", DisplayName = "DNA Body")`

#### class `UMetaHumanCharacterEditorDNAExportTool`  
`class UMetaHumanCharacterEditorDNAExportTool : public UMetaHumanCharacterEditorExportToolBase`  
_L70-87_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorExportToolBase`
- L77 _protected prototype_ `virtual UClass* GetExportPropertiesClass() const override;`
- L78 _protected prototype_ `virtual FText GetExportToolDisplayName() const override;`
- L79 _protected prototype_ `virtual FText GetExportButtonText() const override;`
- L84 _public prototype_ `virtual bool CanExport(FText& OutErrorMsg) const override;`
- L85 _public prototype_ `virtual void Export() const override;`

#### class `UMetaHumanCharacterEditorGeometryExportProperties`  
`class UMetaHumanCharacterEditorGeometryExportProperties : public UInteractiveToolPropertySet`  
_L92-113_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L99 _public member_ `FDirectoryPath ProjectPath{ TEXT("/Game` — `UPROPERTY(EditAnywhere, Category = "Geometry Export Options", meta = (ContentDir))`
- L102 _public member_ `bool bHeadSkeletalMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Meshes")`
- L105 _public member_ `bool bBodySkeletalMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Meshes")`
- L108 _public member_ `bool bFullBodySkeletalMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Meshes")`
- L112 _public member_ `bool bOverwriteExistingAssets = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Meshes", AdvancedDisplay)` — Overwrites onto the existing assets, if false will create new unique asset names for exported assets.

#### class `UMetaHumanCharacterEditorGeometryExportTool`  
`class UMetaHumanCharacterEditorGeometryExportTool : public UMetaHumanCharacterEditorExportToolBase`  
_L116-132_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorExportToolBase`
- L122 _protected prototype_ `virtual UClass* GetExportPropertiesClass() const override;`
- L123 _protected prototype_ `virtual FText GetExportToolDisplayName() const override;`
- L128 _public prototype_ `virtual FText GetExportButtonText() const override;`
- L129 _public prototype_ `virtual bool CanExport(FText& OutErrorMsg) const override;`
- L130 _public prototype_ `virtual void Export() const override;`

#### class `UMetaHumanCharacterEditorMaterialsExportProperties`  
`class UMetaHumanCharacterEditorMaterialsExportProperties : public UInteractiveToolPropertySet`  
_L137-149_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L144 _public member_ `FDirectoryPath ProjectPath{ TEXT("/Game` — `UPROPERTY(EditAnywhere, Category = "Materials Export Options", meta = (ContentDir))`
- L148 _public member_ `bool bMaterialsApplyAsOverrides = true;` — `UPROPERTY(EditAnywhere, Category = "Materials", DisplayName = "Apply as Overrides")` — If true the exported materials will be applied as override materials on MetaHumanCharacter asset

#### class `UMetaHumanCharacterEditorMaterialsExportTool`  
`class UMetaHumanCharacterEditorMaterialsExportTool : public UMetaHumanCharacterEditorExportToolBase`  
_L152-168_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorExportToolBase`
- L158 _protected prototype_ `virtual UClass* GetExportPropertiesClass() const override;`
- L159 _protected prototype_ `virtual FText GetExportToolDisplayName() const override;`
- L160 _protected prototype_ `virtual FText GetExportButtonText() const override;`
- L165 _public prototype_ `virtual bool CanExport(FText& OutErrorMsg) const override;`
- L166 _public prototype_ `virtual void Export() const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorEyesTool.h` (Private)


#### struct `FMetaHumanCharacterEyePreset`  
`struct FMetaHumanCharacterEyePreset`  
_L16-28_
- reflection: `USTRUCT()`
- desc: Data that represents an eye preset that can be displayed in the eye tool
- L21 _public member_ `FName PresetName;` — `UPROPERTY(EditAnywhere, Category = "Preset")`
- L24 _public member_ `FMetaHumanCharacterEyesSettings EyesSettings;` — `UPROPERTY(EditAnywhere, Category = "Eye Settings")`
- L27 _public member_ `TSoftObjectPtr<class UTexture> Thumbnail;` — `UPROPERTY(EditAnywhere, Category = "Thumbnail")`

#### class `UMetaHumanCharacterEyePresets`  
`class UMetaHumanCharacterEyePresets : public UDataAsset`  
_L34-48_
- reflection: `UCLASS()`
- inherits: `UDataAsset`
- desc: Data Asset definition for eye presets
- L41 _public prototype_ `static TNotNull<UMetaHumanCharacterEyePresets*> Get();` — Returns the default data asset used for eye presets
- L47 _public member_ `TArray<FMetaHumanCharacterEyePreset> Presets;` — `UPROPERTY(EditAnywhere, Category = "Presets")` — The list of eye presets the user can select

#### enum `EMetaHumanCharacterEyeEditSelection`  
`enum class EMetaHumanCharacterEyeEditSelection : uint8`  
_L51-58_
- reflection: `UENUM()`
- L53 _public enumerator_ `Both`
- L54 _public enumerator_ `Left`
- L55 _public enumerator_ `Right`
- L57 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanCharacterEditorEyesToolBuilder`  
`class UMetaHumanCharacterEditorEyesToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L62-78_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L69 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L70 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L76 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMetaHumanCharacterEditorEyesToolProperties`  
`class UMetaHumanCharacterEditorEyesToolProperties : public UInteractiveToolPropertySet`  
_L81-97_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L87 _public prototype_ `void CopyFrom(const FMetaHumanCharacterEyesSettings& InEyesSettings);`
- L88 _public prototype_ `void CopyTo(FMetaHumanCharacterEyesSettings& OutEyesSettings) const;`
- L93 _public member_ `EMetaHumanCharacterEyeEditSelection EyeSelection = EMetaHumanCharacterEyeEditSelection::Both;` — `UPROPERTY(EditAnywhere, Category = "Selection")`
- L96 _public member_ `FMetaHumanCharacterEyeProperties Eye;` — `UPROPERTY(EditAnywhere, Category = "Eye", meta = (ShowOnlyInnerProperties), Transient)`

#### class `UMetaHumanCharacterEditorEyesTool`  
`class UMetaHumanCharacterEditorEyesTool : public USingleSelectionTool`  
_L100-133_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- L106 _public prototype_ `virtual void Setup();`
- L107 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType);`
- L109 _public function_ `virtual bool HasCancel() const`
- L110 _public function_ `virtual bool HasAccept() const`
- L111 _public function_ `virtual bool CanAccept() const`
- L113 _public prototype_ `virtual void OnPropertyModified(UObject* InPropertySet, FProperty* InProperty) override;`
- L117 _public prototype_ `UMetaHumanCharacterEditorEyesToolProperties* GetEyesToolProperties() const;` — Get the Eyes Tool properties.
- L119 _public prototype_ `void SetEyeSelection(EMetaHumanCharacterEyeEditSelection InSelection);`
- L121 _public prototype_ `void SetEyesFromPreset(const FMetaHumanCharacterEyesSettings& InPreset);`
- L129 _private member_ `TObjectPtr<UMetaHumanCharacterEditorEyesToolProperties> EyesProperties;` — `UPROPERTY()` — Properties of the Eyes Tool. These are displayed in the details panel when the tool is activated.
- L132 _private member_ `FMetaHumanCharacterEyesSettings PreviousEyeSettings;` — Keep track of previously set eyes settings

#### Free symbols / members of external scopes

- L59 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterEyeEditSelection, EMetaHumanCharacterEyeEditSelection::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorFaceEditingTools.h` (Private)


#### enum `EMetaHumanCharacterFaceEditingTool`  
`enum class EMetaHumanCharacterFaceEditingTool : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `Move`
- L18 _public enumerator_ `Sculpt`

#### class `UMetaHumanCharacterEditorFaceEditingToolBuilder`  
`class UMetaHumanCharacterEditorFaceEditingToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L22-35_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L30 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L34 _public member_ `EMetaHumanCharacterFaceEditingTool ToolType = EMetaHumanCharacterFaceEditingTool::Move;` — `UPROPERTY()`

#### class `UFaceStateChangeTransactor`  
`class UFaceStateChangeTransactor : public UObject, public IMeshStateChangeTransactorInterface`  
_L39-59_
- reflection: `UCLASS()`
- inherits: `UObject,IMeshStateChangeTransactorInterface`
- L44 _public prototype_ `virtual FSimpleMulticastDelegate& GetStateChangedDelegate(UMetaHumanCharacter* InMetaHumanCharacter) override;`
- L46 _public prototype_ `virtual void CommitShutdownState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, EToolShutdownType InShutdownType, const FText& InCommandChangeDescription) override;`
- L48 _public prototype_ `virtual void StoreBeginDragState(UMetaHumanCharacter* InMetaHumanCharacter) override;`
- L49 _public prototype_ `virtual void CommitEndDragState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, const FText& InCommandChangeDescription) override;`
- L51 _public prototype_ `TSharedRef<FMetaHumanCharacterIdentity::FState> GetBeginDragState() const;`
- L53 _public prototype_ `bool IsDragStateValid() const;`
- L58 _protected member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> BeginDragState;` — Hold the state of the character when a dragging operation begins so it can be undone while the tool is active

#### enum `EMetaHumanCharacterMoveToolManipulationGizmos`  
`enum class EMetaHumanCharacterMoveToolManipulationGizmos : uint8`  
_L63-70_
- reflection: `UENUM()`
- L65 _public enumerator_ `ScreenSpace`
- L66 _public enumerator_ `Translate`
- L67 _public enumerator_ `Rotate`
- L68 _public enumerator_ `UniformScale`
- L69 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanCharacterEditorFaceMoveToolProperties`  
`class UMetaHumanCharacterEditorFaceMoveToolProperties : public UInteractiveToolPropertySet`  
_L74-92_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L80 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L87 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertyValueSetDelegate, const FPropertyChangedEvent&);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated
- L88 _public member_ `FOnPropertyValueSetDelegate OnPropertyValueSetDelegate;`
- L91 _public member_ `EMetaHumanCharacterMoveToolManipulationGizmos GizmoType = EMetaHumanCharacterMoveToolManipulationGizmos::ScreenSpace;` — `UPROPERTY(EditAnywhere, Category = "Manipulators")`

#### struct `FGizmoBoundaryConstraintFunctions`  
`struct FGizmoBoundaryConstraintFunctions`  
_L94-113_
- L96 _public member_ `FVector3f BeginDragGizmoPosition;`
- L97 _public member_ `FVector3f MinGizmoPosition;`
- L98 _public member_ `FVector3f MaxGizmoPosition;`
- L99 _public member_ `const float BBoxReduction = 0.2f;`
- L100 _public member_ `const bool bExpandToCurrent = true;`
- L101 _public member_ `const float BBoxSoftBound = 0.2f;`
- L103 _public member_ `FVector3f BeginDragGizmoRotation;`
- L104 _public member_ `FVector3f MinGizmoRotation;`
- L105 _public member_ `FVector3f MaxGizmoRotation;`
- L107 _public member_ `float BeginDragGizmoScale;`
- L108 _public member_ `float MinGizmoScale;`
- L109 _public member_ `float MaxGizmoScale;`
- L111 _public prototype_ `FVector3f GizmoTranslationFunction(const FVector3f& Delta) const;`
- L112 _public prototype_ `FVector3f GizmoRotationFunction(const FVector3f& Delta) const;`

#### class `UMetaHumanCharacterEditorFaceMoveTool`  
`class UMetaHumanCharacterEditorFaceMoveTool : public UMetaHumanCharacterEditorFaceTool`  
_L116-176_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorFaceTool`
- L121 _public function_ `UMetaHumanCharacterEditorFaceMoveToolProperties* GetFaceMoveToolProperties() const`
- L123 _public prototype_ `void SetGizmoType(EMetaHumanCharacterMoveToolManipulationGizmos InSelection);`
- L127 _protected prototype_ `virtual void Setup() override;`
- L128 _protected prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L129 _protected prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L130 _protected prototype_ `virtual void OnClickPress(const FInputDeviceRay& InClickPos) override;`
- L131 _protected prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L132 _protected prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L133 _protected prototype_ `virtual void OnUpdateDrag(const FRay& InRay) override;`
- L134 _protected prototype_ `virtual void OnEndDrag(const FRay& InRay) override;`
- L135 _protected prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L139 _protected prototype_ `virtual void InitStateChangeTransactor() override;`
- L140 _protected prototype_ `virtual const FText GetDescription() const override;`
- L141 _protected prototype_ `virtual const FText GetCommandChangeDescription() const override;`
- L142 _protected prototype_ `virtual const FText GetCommandChangeIntermediateDescription() const override;`
- L143 _protected prototype_ `virtual UStaticMesh* GetManipulatorMesh() const override;`
- L144 _protected prototype_ `virtual UMaterialInterface* GetManipulatorMaterial() const override;`
- L145 _protected prototype_ `virtual float GetManipulatorScale() const override;`
- L146 _protected prototype_ `virtual TArray<FVector3f> GetManipulatorPositions() const override;`
- L147 _protected prototype_ `virtual TArray<FVector3f> TranslateManipulator(int32 InManipulatorIndex, const FVector3f& InDelta) override;`
- L152 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorFaceMoveToolProperties> MoveProperties;` — `UPROPERTY()` — Properties of the Move Tool. These are displayed in the details panel when the tool is activated.
- L157 _private member_ `TObjectPtr<class UTransformProxy> TransformProxy;` — `UPROPERTY()` — Gizmo and it's proxy used for UE like manipulations
- L160 _private member_ `TObjectPtr<class UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L163 _private member_ `int32 SelectedGizmoManipulator = INDEX_NONE;` — Index of the manipulator that the gizmo is assigned to
- L166 _private member_ `TOptional<FTransform> BeginDragTransform;` — Transform at the start of the drag
- L169 _private member_ `TOptional<FTransform> CurrentDragTransform;` — Current drag transform
- L172 _private member_ `FGizmoBoundaryConstraintFunctions GizmoConstraints;` — Gizmo contraints data
- L175 _private member_ `ETransformGizmoSubElements DraggedGizmoElements;` — Records which elements have been modified during drag

#### class `UMetaHumanCharacterEditorFaceSculptTool`  
`class UMetaHumanCharacterEditorFaceSculptTool : public UMetaHumanCharacterEditorFaceTool`  
_L179-219_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorFaceTool`
- L185 _protected prototype_ `virtual void InitStateChangeTransactor() override;`
- L186 _protected prototype_ `virtual const FText GetDescription() const override;`
- L187 _protected prototype_ `virtual const FText GetCommandChangeDescription() const override;`
- L188 _protected prototype_ `virtual const FText GetCommandChangeIntermediateDescription() const override;`
- L189 _protected prototype_ `virtual UStaticMesh* GetManipulatorMesh() const override;`
- L190 _protected prototype_ `virtual UMaterialInterface* GetManipulatorMaterial() const override;`
- L191 _protected prototype_ `virtual float GetManipulatorScale() const override;`
- L192 _protected prototype_ `virtual TArray<FVector3f> GetManipulatorPositions() const override;`
- L193 _protected prototype_ `virtual TArray<FVector3f> TranslateManipulator(int32 InManipulatorIndex, const FVector3f& InDelta) override;`
- L194 _protected prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L195 _protected prototype_ `virtual bool HitTest(const FRay& InRay, FHitResult& OutHit) override;`
- L196 _protected prototype_ `virtual void Setup() override;`
- L197 _protected prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L198 _protected prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L199 _protected prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L200 _protected prototype_ `virtual void OnUpdateDrag(const FRay& InRay) override;`
- L201 _protected prototype_ `virtual void OnEndDrag(const FRay& InRay) override;`
- L202 _protected prototype_ `virtual void OnCancelDrag() override;`
- L207 _private member_ `int32 HitVertexID = -1;` — Saves the current hit if a ray intersects the base mesh
- L208 _private member_ `FVector HitVertex;`
- L209 _private member_ `FVector HitNormal;`
- L213 _private member_ `bool CtrlToggledOnBeginDrag;` — Flag whether Ctrl was pressed during when a dragging operation started This is used to enter the add/remove landmark mode
- L215 _private member_ `TArray<FVector3f> DebugVertices;`
- L218 _private member_ `FMetaHumanCharacterFaceEvaluationSettings PreviousFaceEvaluationSettings;` — Keep track of previously set face evaluation settings

#### Free symbols / members of external scopes

- L71 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterMoveToolManipulationGizmos, EMetaHumanCharacterMoveToolManipulationGizmos::Count);`
- L87 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyValueSetDelegate, const FPropertyChangedEvent&);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorHeadModelTool.h` (Private)


#### enum `EMetaHumanCharacterHeadModelTool`  
`enum class EMetaHumanCharacterHeadModelTool : uint8`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `Model`
- L15 _public enumerator_ `Materials`
- L16 _public enumerator_ `Grooms`

#### class `UMetaHumanCharacterEditorHeadModelToolBuilder`  
`class UMetaHumanCharacterEditorHeadModelToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L20-33_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L27 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L28 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L32 _public member_ `EMetaHumanCharacterHeadModelTool ToolType = EMetaHumanCharacterHeadModelTool::Model;` — `UPROPERTY()`

#### class `UMetaHumanCharacterHeadModelSubToolBase`  
`class UMetaHumanCharacterHeadModelSubToolBase : public UInteractiveToolPropertySet`  
_L36-47_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveToolPropertySet`
- L43 _public prototype_ `virtual void CopyTo(FMetaHumanCharacterHeadModelSettings& OutHeadModelSettings) PURE_VIRTUAL(UMetaHumanCharacterHeadModelSubToolBase::CopyTo(), {});` — Utility functions for copying to & from MetaHuman Character Head Model Settings and Head Model Tool Properties
- L44 _public prototype_ `virtual void CopyFrom(const FMetaHumanCharacterHeadModelSettings& InHeadModelSettings) PURE_VIRTUAL(UMetaHumanCharacterHeadModelSubToolBase::CopyFrom(), {});`
- L46 _public function_ `virtual void SetEnabled(bool bInIsEnabled)`

#### class `UMetaHumanCharacterHeadModelEyelashesProperties`  
`class UMetaHumanCharacterHeadModelEyelashesProperties : public UMetaHumanCharacterHeadModelSubToolBase`  
_L50-74_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterHeadModelSubToolBase`
- L56 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _public prototype_ `virtual void CopyTo(FMetaHumanCharacterHeadModelSettings& OutHeadModelSettings) override;`
- L61 _public prototype_ `virtual void CopyFrom(const FMetaHumanCharacterHeadModelSettings& InHeadModelSettings) override;`
- L68 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnEyelashesPropertyValueSetDelegate, bool);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated
- L69 _public member_ `FOnEyelashesPropertyValueSetDelegate OnEyelashesPropertyValueSetDelegate;`
- L73 _public member_ `FMetaHumanCharacterEyelashesProperties Eyelashes;` — `UPROPERTY(EditAnywhere, Category = "Eyelashes", meta = (ShowOnlyInnerProperties))`

#### enum `EMetaHumanCharacterTeethPropertyType`  
`enum class EMetaHumanCharacterTeethPropertyType : uint8`  
_L77-89_
- reflection: `UENUM()`
- L79 _public enumerator_ `ToothLength`
- L80 _public enumerator_ `ToothSpacing`
- L81 _public enumerator_ `UpperShift`
- L82 _public enumerator_ `LowerShift`
- L83 _public enumerator_ `Overbite`
- L84 _public enumerator_ `Overjet`
- L85 _public enumerator_ `WornDown`
- L86 _public enumerator_ `Polycanine`
- L87 _public enumerator_ `RecedingGums`
- L88 _public enumerator_ `Narrowness`

#### class `UMetaHumanCharacterHeadModelTeethProperties`  
`class UMetaHumanCharacterHeadModelTeethProperties : public UMetaHumanCharacterHeadModelSubToolBase`  
_L92-122_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterHeadModelSubToolBase`
- L98 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L102 _public prototype_ `virtual void CopyTo(FMetaHumanCharacterHeadModelSettings& OutHeadModelSettings) override;`
- L103 _public prototype_ `virtual void CopyFrom(const FMetaHumanCharacterHeadModelSettings& InHeadModelSettings) override;`
- L106 _public prototype_ `virtual void SetEnabled(bool bInIsEnabled) override;`
- L113 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTeethPropertyValueSetDelegate, bool);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated
- L114 _public member_ `FOnTeethPropertyValueSetDelegate OnTeethPropertyValueSetDelegate;`
- L118 _public member_ `EMetaHumanCharacterTeethPropertyType EditableProperty = EMetaHumanCharacterTeethPropertyType::ToothLength;` — `UPROPERTY(EditAnywhere, Category = "Teeth")`
- L121 _public member_ `FMetaHumanCharacterTeethProperties Teeth;` — `UPROPERTY(EditAnywhere, Category = "Teeth", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanCharacterEditorHeadModelTool`  
`class UMetaHumanCharacterEditorHeadModelTool : public UMetaHumanCharacterEditorToolWithSubTools`  
_L125-170_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithSubTools`
- L131 _public prototype_ `virtual void Setup() override;`
- L132 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L133 _public prototype_ `virtual void OnTick(float InDeltaTime);`
- L136 _public prototype_ `void SetEnabledSubTool(UMetaHumanCharacterHeadModelSubToolBase* InSubTool, bool bInEnabled);`
- L140 _protected prototype_ `virtual void RegisterSubTools();`
- L141 _protected prototype_ `virtual const FText GetDescription() const;`
- L145 _protected member_ `TObjectPtr<UMetaHumanCharacterHeadModelEyelashesProperties> EyelashesProperties;` — `UPROPERTY()` — Properties of the Head Model Tool. These are displayed in the details panel when the tool is activated.
- L148 _protected member_ `TObjectPtr<UMetaHumanCharacterHeadModelTeethProperties> TeethProperties;` — `UPROPERTY()`
- L154 _private member_ `FMetaHumanCharacterHeadModelSettings PreviousHeadModelSettings;` — Keep track of previously set head model settings
- L155 _private member_ `FMetaHumanCharacterHeadModelSettings OriginalHeadModelSettings;`
- L158 _private member_ `bool bEyelashesVariantWasModified = false;` — Keep track of whether the tool applied any changes
- L159 _private member_ `bool bTeethVariantWasModified = false;`
- L160 _private member_ `bool bTeethVariantWasCommitted = false;`
- L166 _private member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> FaceState;` — The face state of the actor when the tool was activated This is needed because Eyelashes and Teeth Type changes face geometry through FaceState.
- L168 _private prototype_ `void UpdateHeadModelState(bool bInCommitChange) const;`
- L169 _private prototype_ `void ProcessPending();`

#### class `UMetaHumanCharacterEditorHeadMaterialsTool`  
`class UMetaHumanCharacterEditorHeadMaterialsTool : public UMetaHumanCharacterEditorHeadModelTool`  
_L173-188_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorHeadModelTool`
- L179 _public prototype_ `virtual void Setup() override;`
- L180 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L181 _public prototype_ `virtual void OnTick(float InDeltaTime);`
- L185 _protected prototype_ `virtual void RegisterSubTools() override;`
- L186 _protected prototype_ `virtual const FText GetDescription() const override;`

#### Free symbols / members of external scopes

- L68 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEyelashesPropertyValueSetDelegate, bool);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated
- L113 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTeethPropertyValueSetDelegate, bool);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorImportTools.h` (Private)


#### enum `EMetaHumanImportToolMode`  
`enum class EMetaHumanImportToolMode : uint8`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `MeshFit`
- L15 _public enumerator_ `Replace`
- L16 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanCharacterEditorImportFromDNAToolBuilder`  
`class UMetaHumanCharacterEditorImportFromDNAToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L21-31_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L28 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L29 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorImportFromIdentityToolBuilder`  
`class UMetaHumanCharacterEditorImportFromIdentityToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L34-44_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L41 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L42 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorImportFromTemplateToolBuilder`  
`class UMetaHumanCharacterEditorImportFromTemplateToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L47-57_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L54 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L55 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterImportSubToolBase`  
`class UMetaHumanCharacterImportSubToolBase : public UInteractiveToolPropertySet`  
_L60-79_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveToolPropertySet`
- L65 _public prototype_ `virtual bool CanConform() const PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::CanConform(), { return false; });`
- L66 _public prototype_ `virtual void Conform() PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::Conform(), {});`
- L68 _public prototype_ `virtual bool CanImportMesh() const PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::CanImportMesh(), { return false; });`
- L69 _public prototype_ `virtual void ImportMesh() PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::ImportMesh(), {});`
- L71 _public prototype_ `virtual bool CanImportJoints() const PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::CanImportJoints(), { return false; });`
- L72 _public prototype_ `virtual void ImportJoints() PURE_VIRTUAL(UMetaHumanCharacterImportSubToolBase::ImportJoints(), {});`
- L75 _public prototype_ `virtual void DisplayConformError(const FText& ErrorMessageText) const;` — Display a conform error message
- L78 _public member_ `EMetaHumanImportToolMode Mode = EMetaHumanImportToolMode::MeshFit;` — `UPROPERTY()`

#### class `UMetaHumanCharacterImportFromDNAProperties`  
`class UMetaHumanCharacterImportFromDNAProperties : public UMetaHumanCharacterImportSubToolBase`  
_L82-138_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterImportSubToolBase`
- L89 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L94 _public member_ `FFilePath DNAHead;` — `UPROPERTY(EditAnywhere, Category = "Load DNA Assets", DisplayName = "DNA Head", meta = (FilePathFilter = "DNA file (*.dna)|*.dna"))` — File path to the .dna file containing the head rig data to import.
- L98 _public member_ `FFilePath DNABody;` — `UPROPERTY(EditAnywhere, Category = "Load DNA Assets", DisplayName = "DNA Body", meta = (FilePathFilter = "DNA file (*.dna)|*.dna"))` — File path to the .dna file containing the body rig data to import.
- L101 _public member_ `FImportFromDNAParams ImportOptions;` — `UPROPERTY(EditAnywhere, Category = "Head Options", meta = (ShowOnlyInnerProperties))`
- L104 _public member_ `FConformBodyParams BodyParams;` — `UPROPERTY(EditAnywhere, Category = "Body Options", meta = (ShowOnlyInnerProperties))`
- L108 _public member_ `bool bReplaceMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Body Options")` — When enabled, the MetaHuman's body surface mesh is replaced with the geometry stored in the DNA file. Disable if you only want to update joints without changing the visible mesh.
- L112 _public member_ `bool bReplaceBodyJoints = true;` — `UPROPERTY(EditAnywhere, Category = "Body Options")` — When enabled, the MetaHuman's body joint positions and orientations are replaced with those from the body DNA. Disable if you only want to update the surface mesh without affecting the skeleton.
- L115 _public member_ `bool bAlignScale = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L118 _public member_ `bool bAlignRotation = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L121 _public member_ `bool bAlignTranslation = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L125 _public prototype_ `virtual bool CanImportMesh() const override;`
- L126 _public prototype_ `virtual void ImportMesh() override;`
- L127 _public prototype_ `virtual bool CanConform() const override;`
- L128 _public prototype_ `virtual void Conform() override;`
- L129 _public prototype_ `virtual bool CanImportJoints() const override;`
- L130 _public prototype_ `virtual void ImportJoints() override;`
- L133 _public prototype_ `bool CanImportWholeRig() const;`
- L134 _public prototype_ `void ImportWholeRig();`
- L137 _private prototype_ `bool GetErrorMessageText(EImportErrorCode InErrorCode, FText& OutErrorMessage) const;`

#### class `UMetaHumanCharacterImportFromIdentityProperties`  
`class UMetaHumanCharacterImportFromIdentityProperties : public UMetaHumanCharacterImportSubToolBase`  
_L141-163_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterImportSubToolBase`
- L148 _public member_ `TSoftObjectPtr<class UMetaHumanIdentity> MetaHumanIdentity;` — `UPROPERTY(EditAnywhere, Category = "Asset")`
- L151 _public member_ `FImportFromIdentityParams ImportOptions;` — `UPROPERTY(EditAnywhere, Category = "Import Identity Options", meta = (ShowOnlyInnerProperties))`
- L156 _public prototype_ `virtual bool CanImportMesh() const override;`
- L157 _public prototype_ `virtual void ImportMesh() override;`
- L158 _public function_ `virtual bool CanConform() const override`
- L159 _public function_ `virtual void Conform() override`
- L160 _public function_ `virtual bool CanImportJoints() const override`
- L161 _public function_ `virtual void ImportJoints() override`

#### class `UMetaHumanCharacterImportFromTemplateProperties`  
`class UMetaHumanCharacterImportFromTemplateProperties : public UMetaHumanCharacterImportSubToolBase`  
_L166-232_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterImportSubToolBase`
- L173 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L177 _public member_ `TSoftObjectPtr<UObject> HeadMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L180 _public member_ `TSoftObjectPtr<UObject> BodyMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L183 _public member_ `TSoftObjectPtr<UObject> LeftEyeMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`
- L186 _public member_ `TSoftObjectPtr<UObject> RightEyeMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`
- L189 _public member_ `TSoftObjectPtr<UObject> TeethMesh;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`
- L193 _public member_ `bool bMatchVerticesByUVs = true;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — When enabled, vertices are matched to the MetaHuman template by comparing UV coordinates instead of vertex order. Use this when the template mesh has the same UV layout as the MetaHuman standard but a different vertex ordering.
- L196 _public member_ `FImportFromTemplateParams ImportOptions;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ShowOnlyInnerProperties))`
- L199 _public member_ `FConformBodyParams BodyParams;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ShowOnlyInnerProperties))`
- L203 _public member_ `bool bReplaceMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Options")` — When enabled, the MetaHuman's body surface mesh is replaced with the geometry from the template mesh. Disable if you only want to update joints without changing the visible mesh.
- L207 _public member_ `bool bReplaceBodyJoints = true;` — `UPROPERTY(EditAnywhere, Category = "Options")` — When enabled, the MetaHuman's body joint positions and orientations are replaced with those from the template mesh. Disable if you only want to update the surface mesh without affecting the skeleton.
- L210 _public member_ `bool bAlignScale = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L213 _public member_ `bool bAlignRotation = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L216 _public member_ `bool bAlignTranslation = true;` — `UPROPERTY(EditAnywhere, Category = "Options")`
- L221 _public prototype_ `virtual bool CanImportMesh() const override;`
- L222 _public prototype_ `virtual void ImportMesh() override;`
- L223 _public prototype_ `virtual bool CanConform() const override;`
- L224 _public prototype_ `virtual void Conform() override;`
- L225 _public prototype_ `virtual bool CanImportJoints() const override;`
- L226 _public prototype_ `virtual void ImportJoints() override;`
- L231 _private prototype_ `bool GetErrorMessageText(EImportErrorCode InErrorCode, FText& OutErrorMessage) const;`

#### class `UMetaHumanCharacterEditorImportTool`  
`class UMetaHumanCharacterEditorImportTool : public USingleSelectionTool`  
_L235-271_
- reflection: `UCLASS(Abstract)`
- inherits: `USingleSelectionTool`
- L241 _public function_ `UMetaHumanCharacterImportSubToolBase* GetImportToolProperties() const` — Get the Import Tool properties.
- L244 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L247 _public prototype_ `void UpdateOriginalState();`
- L248 _public prototype_ `void UpdateOriginalDNABuffer();`
- L250 _public prototype_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> GetOriginalFaceState() const;`
- L251 _public prototype_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> GetOriginalBodyState() const;`
- L252 _public prototype_ `const TArray<uint8>& GetOriginalFaceDNABuffer() const;`
- L253 _public prototype_ `const TArray<uint8>& GetOriginalBodyDNABuffer() const;`
- L258 _protected member_ `TObjectPtr<UMetaHumanCharacterImportSubToolBase> ImportProperties;` — `UPROPERTY()`
- L261 _protected member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> OriginalFaceState;` — Hold the original face state of the character, used to undo changes on cancel
- L264 _protected member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> OriginalBodyState;` — Hold the original body state of the character, used to undo changes on cancel
- L267 _protected member_ `TArray<uint8> OriginalFaceDNABuffer;` — Hold the original Face DNA buffer of the character, used to undo changes on cancel
- L270 _protected member_ `TArray<uint8> OriginalBodyDNABuffer;` — Hold the original Body DNA buffer of the character, used to undo changes on cancel

#### class `UMetaHumanCharacterEditorImportFromDNATool`  
`class UMetaHumanCharacterEditorImportFromDNATool : public UMetaHumanCharacterEditorImportTool`  
_L274-284_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorImportTool`
- L281 _public prototype_ `virtual void Setup() override;`

#### class `UMetaHumanCharacterEditorImportFromIdentityTool`  
`class UMetaHumanCharacterEditorImportFromIdentityTool : public UMetaHumanCharacterEditorImportTool`  
_L287-297_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorImportTool`
- L294 _public prototype_ `virtual void Setup() override;`

#### class `UMetaHumanCharacterEditorImportFromTemplateTool`  
`class UMetaHumanCharacterEditorImportFromTemplateTool : public UMetaHumanCharacterEditorImportTool`  
_L300-310_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorImportTool`
- L307 _public prototype_ `virtual void Setup() override;`

#### Free symbols / members of external scopes

- L18 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanImportToolMode, EMetaHumanImportToolMode::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMakeupTool.h` (Private)


#### class `UMetaHumanCharacterEditorMakeupToolBuilder`  
`class UMetaHumanCharacterEditorMakeupToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L20 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorMakeupToolProperties`  
`class UMetaHumanCharacterEditorMakeupToolProperties : public UInteractiveToolPropertySet`  
_L25-48_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L31 _public prototype_ `void CopyFrom(const FMetaHumanCharacterMakeupSettings& InMakeupSettings);`
- L32 _public prototype_ `void CopyTo(FMetaHumanCharacterMakeupSettings& OutMakeupSettings);`
- L37 _public member_ `FMetaHumanCharacterFoundationMakeupProperties Foundation;` — `UPROPERTY(EditAnywhere, Category = "Foundation", meta = (ShowOnlyInnerProperties))`
- L40 _public member_ `FMetaHumanCharacterEyeMakeupProperties Eyes;` — `UPROPERTY(EditAnywhere, Category = "Eyes", meta = (ShowOnlyInnerProperties))`
- L43 _public member_ `FMetaHumanCharacterBlushMakeupProperties Blush;` — `UPROPERTY(EditAnywhere, Category = "Blush", meta = (ShowOnlyInnerProperties))`
- L46 _public member_ `FMetaHumanCharacterLipsMakeupProperties Lips;` — `UPROPERTY(EditAnywhere, Category = "Lips", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanCharacterEditorMakeupTool`  
`class UMetaHumanCharacterEditorMakeupTool : public USingleSelectionTool`  
_L51-87_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- L57 _public function_ `UMetaHumanCharacterEditorMakeupToolProperties* GetMakeupToolProperties() const` — Get the Makeup Tool properties.
- L60 _public prototype_ `virtual void Setup();`
- L61 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType);`
- L63 _public function_ `virtual bool HasCancel() const`
- L64 _public function_ `virtual bool HasAccept() const`
- L65 _public function_ `virtual bool CanAccept() const`
- L67 _public prototype_ `virtual void OnPropertyModified(UObject* InPropertySet, FProperty* InProperty) override;`
- L72 _private prototype_ `void UpdateMakeupSettings();`
- L80 _private member_ `TObjectPtr<UMetaHumanCharacterEditorMakeupToolProperties> MakeupProperties;` — `UPROPERTY()` — Properties of the Makeup Tool. These are displayed in the details panel when the tool is activated.
- L83 _private member_ `FMetaHumanCharacterMakeupSettings PreviousMakeupSettings;` — Keep track of previously set makeup settings
- L86 _private member_ `bool bActorWasModified = false;` — Keep track of whether the tool applied any changes

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshEditingTools.h` (Private)


#### class `UMeshStateChangeTransactorInterface`  
`class UMeshStateChangeTransactorInterface : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshStateChangeTransactorInterface`  
`class IMeshStateChangeTransactorInterface`  
_L25-36_
- L30 _public prototype_ `virtual FSimpleMulticastDelegate& GetStateChangedDelegate(UMetaHumanCharacter* InMetaHumanCharacter) = 0;`
- L32 _public prototype_ `virtual void CommitShutdownState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, EToolShutdownType InShutdownType, const FText& InCommandChangeDescription) = 0;`
- L34 _public prototype_ `virtual void StoreBeginDragState(UMetaHumanCharacter* InMetaHumanCharacter) = 0;`
- L35 _public prototype_ `virtual void CommitEndDragState(UInteractiveToolManager* InToolManager, UMetaHumanCharacter* InMetaHumanCharacter, const FText& InCommandChangeDescription) = 0;`

#### class `FMetaHumanCharacterEditorFaceToolCommandChange`  
`class FMetaHumanCharacterEditorFaceToolCommandChange : public FMetaHumanCharacterEditorToolCommandChange`  
_L41-57_
- inherits: `FMetaHumanCharacterEditorToolCommandChange`
- desc: Face Tool Command change for undo/redo transactions.
- L44 _public prototype_ `FMetaHumanCharacterEditorFaceToolCommandChange( TSharedRef<const FMetaHumanCharacterIdentity::FState> InOldState, TNotNull<UMetaHumanCharacter*> InCharacter, TNotNull<UInteractiveToolManager*> InToolManager);`
- L50 _public prototype_ `virtual void Apply(UObject* InObject) override;`
- L51 _public prototype_ `virtual void Revert(UObject* InObject) override;`
- L55 _private member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> OldState;`
- L56 _private member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> NewState;`

#### class `UMetaHumanCharacterEditorMeshEditingToolProperties`  
`class UMetaHumanCharacterEditorMeshEditingToolProperties : public UInteractiveToolPropertySet`  
_L60-81_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L68 _public member_ `float Size = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Manipulators", meta = (UIMin = "0", UIMax = "5", ClampMin = "0", ClampMax = "5"))` — Scales the size of the on-screen blend handle in the viewport. Useful on high-DPI displays or when precision clicking is difficult.
- L72 _public member_ `float Speed = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Manipulators", meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))` — Mouse interaction speed of manipulator
- L76 _public member_ `bool bHideWhileDragging = true;` — `UPROPERTY(EditAnywhere, Category = "Manipulators")` — Hide other manipulators while dragging
- L80 _public member_ `bool bSymmetricModeling = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Symmetric Manipulation", Category = "Manipulators")` — When enabled, any edits made to one side of the face are automatically mirrored to the other.. Disable to sculpt asymmetric features.

#### class `UMetaHumanCharacterEditorMeshEditingTool`  
`class UMetaHumanCharacterEditorMeshEditingTool : public UMeshSurfacePointTool`  
_L84-193_
- reflection: `UCLASS(Abstract)`
- inherits: `UMeshSurfacePointTool`
- L90 _public prototype_ `virtual bool HitTest(const FRay& InRay, FHitResult& OutHit) override;`
- L91 _public prototype_ `virtual void Setup() override;`
- L92 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L93 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L94 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InClickPos) override;`
- L95 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L96 _public prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L97 _public prototype_ `virtual void OnUpdateDrag(const FRay& InRay) override;`
- L98 _public prototype_ `virtual void OnEndDrag(const FRay& InRay) override;`
- L99 _public function_ `virtual bool HasCancel() const override`
- L100 _public function_ `virtual bool HasAccept() const override`
- L101 _public function_ `virtual bool CanAccept() const override`
- L104 _public function_ `UMetaHumanCharacterEditorMeshEditingToolProperties* GetMeshEditingToolProperties() const`
- L107 _protected prototype_ `virtual void SetManipulatorDragState(int32 InManipulatorIndex, bool bInIsDragging);`
- L108 _protected prototype_ `virtual void SetManipulatorHoverState(int32 InManipulatorIndex, bool bInIsHovering);`
- L109 _protected prototype_ `virtual void SetManipulatorMarkedState(int32 InManipulatorIndex, bool bInIsMarked);`
- L110 _protected prototype_ `virtual void UpdateManipulatorsScale();`
- L111 _protected prototype_ `virtual const FText GetDescription() const;`
- L112 _protected prototype_ `virtual const FText GetCommandChangeDescription() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetCommandChangeDescription, return FText(););`
- L113 _protected prototype_ `virtual const FText GetCommandChangeIntermediateDescription() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetCommandChangeIntermediateDescription, return FText(););`
- L114 _protected prototype_ `virtual class UStaticMesh* GetManipulatorMesh() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetManipulatorMesh, return {};);`
- L115 _protected prototype_ `virtual class UMaterialInterface* GetManipulatorMaterial() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetManipulatorMaterial, return {};);`
- L116 _protected prototype_ `virtual float GetManipulatorScale() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetManipulatorScale, return 0.0f;) virtual TArray<FVector3f> GetManipulatorPositions() const PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::GetManipulatorPositions, return TArray<FVector3f>(););`
- L118 _protected prototype_ `virtual TArray<FVector3f> TranslateManipulator(int32 InManipulatorIndex, const FVector3f& InDelta) PURE_VIRTUAL(UMetaHumanCharacterEditorFaceEditingTool::TranslateManipulator, return TArray<FVector3f>(););`
- L120 _protected prototype_ `virtual void InitStateChangeTransactor() PURE_VIRTUAL(UMetaHumanCharacterEditorMeshEditingTool::InitStateChangeTransactor,);`
- L125 _protected prototype_ `virtual UStaticMeshComponent* CreateManipulator(const FVector3f& InPosition);` — Create new manipulator in the given position and stores it to be referenced later
- L130 _protected prototype_ `void RecreateManipulators(const TArray<FVector3f>& InManipulatorPositions);` — Recreates manipulators actor and components based on positions array.
- L135 _protected prototype_ `void UpdateManipulatorPositions(const TArray<FVector3f>& InPositions);` — Updates the positions of the manipulator components
- L140 _protected prototype_ `void UpdateManipulatorPositions();` — Updates the positions of the manipulator components by calling GetManipulatorPositions()
- L149 _protected prototype_ `void WithSceneView(TFunction<void(class FSceneView*)> InCallback) const;` — Utility function to get a scene view of the current viewport The lifetime of FSceneViews objects is tied to the view family content in which it is created and are deleted when the view family goes out of scope so the scene view can only be used in the scoped of the given callback function
- L154 _protected prototype_ `bool IsManipulatorOccluded(const FRay& InRay) const;` — Checks if the manipulator is occluded by the mesh in ray direction
- L159 _protected member_ `TObjectPtr<class UMetaHumanCharacter> MetaHumanCharacter;` — `UPROPERTY()` — Reference to the MetaHumanCharacter being edited
- L163 _protected member_ `TObjectPtr<class UMetaHumanCharacterEditorMeshEditingToolProperties> MeshEditingToolProperties;` — `UPROPERTY()` — Mesh editing property set
- L167 _protected member_ `TArray<TObjectPtr<UStaticMeshComponent>> ManipulatorComponents;` — `UPROPERTY()` — An array of static mesh components that represents the manipulators in the viewport
- L171 _protected member_ `TObjectPtr<class AInternalToolFrameworkActor> ManipulatorsActor = nullptr;` — `UPROPERTY()` — An actor used to hold the manipulator components that the user can interact with
- L174 _protected member_ `TScriptInterface<IMeshStateChangeTransactorInterface> MeshStateChangeTransactor;` — `UPROPERTY()`
- L177 _protected member_ `FVector2D OldPixelPos;` — The previous pixel position used to calculate the manipulator's movement delta
- L180 _protected member_ `FVector2D NewPixelPos;` — The current pixel position used to calculate the manipulator's movement delta
- L183 _protected member_ `int32 SelectedManipulator = INDEX_NONE;` — Index of the selected manipulator
- L186 _protected member_ `FVector3f PendingMoveDelta = FVector3f::ZeroVector;` — Holds the movement to be applied in the next tick
- L189 _protected member_ `FVector3f BeginDragMoveDelta = FVector3f::ZeroVector;` — Holds the movement starting from begin drag
- L192 _protected member_ `FDelegateHandle DelegateHandle;` — Delegate handle for the state change

#### class `UMetaHumanCharacterEditorHeadAndBodyParameterProperties`  
`class UMetaHumanCharacterEditorHeadAndBodyParameterProperties : public UInteractiveToolPropertySet`  
_L196-241_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L202 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L205 _public prototype_ `void OnPostEditChangeProperty(const FPropertyChangedEvent& PropertyChangedEvent);`
- L211 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPropertyValueSetDelegate, const FPropertyChangedEvent&);` — Delegate that executes on EPropertyChangeType::ValueSet property change event for face evaluation settings (FaceDelta, HeadScale). Mirrors the pattern from the former UMetaHumanCharacterEditorFaceEditingToolHeadParameterProperties.
- L212 _public member_ `FOnPropertyValueSetDelegate OnPropertyValueSetDelegate;`
- L214 _public member_ `FSimpleMulticastDelegate OnBodyParameterChangedDelegate;`
- L216 _public prototype_ `void OnBodyStateChanged();`
- L217 _public prototype_ `void ResetBody();`
- L219 _public prototype_ `void CopyFrom(const FMetaHumanCharacterFaceEvaluationSettings& InFaceEvaluationSettings);`
- L220 _public prototype_ `void CopyTo(FMetaHumanCharacterFaceEvaluationSettings& OutFaceEvaluationSettings) const;`
- L226 _public member_ `float BodyDelta = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Body Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — When fitting, the underlying body model won't perfectly match the input. The small difference, or 'vertex delta,' is stored and this slider controls its application to the body mesh.
- L228 _public member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity::FState> PreviousBodyState;`
- L234 _public member_ `float FaceDelta = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Head Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Global Delta"))` — When fitting, the underlying head model won't perfectly match the input. The small difference, or 'vertex delta,' is stored and this slider controls its application to the head mesh.
- L238 _public member_ `float HeadScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Head Parameters", meta = (UIMin = "0.8", UIMax = "1.3", ClampMin = "0.8", ClampMax = "1.3"))` — Changes the global scale of the head relative to the body.
- L240 _public member_ `FMetaHumanCharacterFaceEvaluationSettings PreviousFaceEvaluationSettings;`

#### class `UMetaHumanCharacterEditorFaceTool`  
`class UMetaHumanCharacterEditorFaceTool : public UMetaHumanCharacterEditorMeshEditingTool`  
_L244-266_
- reflection: `UCLASS(Abstract)`
- inherits: `UMetaHumanCharacterEditorMeshEditingTool`
- L249 _public function_ `UMetaHumanCharacterEditorHeadAndBodyParameterProperties* GetHeadAndBodyParameterProperties() const`
- L251 _public prototype_ `void ResetFace();`
- L253 _public prototype_ `void ResetFaceNeck();`
- L257 _protected prototype_ `virtual void Setup() override;`
- L258 _protected prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L263 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorHeadAndBodyParameterProperties> HeadAndBodyParameterProperties;` — `UPROPERTY()`
- L265 _protected prototype_ `void UpdateHeadAndBodyParameterProperties(TWeakObjectPtr<UInteractiveToolManager> ToolManager, const FMetaHumanCharacterFaceEvaluationSettings& FaceEvaluationSettings);`

#### class `UMetaHumanCharacterEditorMeshBlendToolProperties`  
`class UMetaHumanCharacterEditorMeshBlendToolProperties : public UInteractiveToolPropertySet`  
_L269-272_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`

#### class `UMetaHumanCharacterEditorMeshBlendTool`  
`class UMetaHumanCharacterEditorMeshBlendTool : public UMetaHumanCharacterEditorFaceTool`  
_L275-337_
- reflection: `UCLASS(Abstract)`
- inherits: `UMetaHumanCharacterEditorFaceTool`
- L281 _public function_ `UMetaHumanCharacterEditorMeshBlendToolProperties* GetBlendToolProperties() const` — Get the Blend Tool properties.
- L283 _public prototype_ `virtual void AddMetaHumanCharacterPreset(UMetaHumanCharacter* InCharacterPreset, int32 InItemIndex) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::AddMetaHumanCharacterPreset,);`
- L284 _public prototype_ `virtual void RemoveMetaHumanCharacterPreset(int32 InItemIndex) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::RemoveMetaHumanCharacterPreset, );`
- L285 _public prototype_ `virtual void BlendToMetaHumanCharacterPreset(UMetaHumanCharacter* InCharacterPreset) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::BlendToMetaHumanCharacterPreset);`
- L286 _public prototype_ `virtual void BlendToMetaHumanCharacterPresetHeadOnly(UMetaHumanCharacter* InCharacterPreset) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::BlendToMetaHumanCharacterPresetHeadOnly);`
- L287 _public prototype_ `virtual void BlendToMetaHumanCharacterPresetBodyOnly(UMetaHumanCharacter* InCharacterPreset) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::BlendToMetaHumanCharacterPresetBodyOnly);`
- L290 _public prototype_ `virtual void Setup() override;`
- L291 _public prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L292 _public prototype_ `virtual void OnEndDrag(const FRay& InRay) override;`
- L293 _public prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L294 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InClickPos) override;`
- L299 _public member_ `TObjectPtr<UMetaHumanCharacterEditorMeshBlendToolProperties> BlendProperties;` — `UPROPERTY()` — Properties of the Blend Tool. These are displayed in the details panel when the tool is activated.
- L303 _protected prototype_ `virtual class UStaticMesh* GetManipulatorMesh() const override;`
- L304 _protected prototype_ `virtual class UMaterialInterface* GetManipulatorMaterial() const override;`
- L305 _protected prototype_ `virtual float GetManipulatorScale() const override;`
- L306 _protected prototype_ `virtual TArray<FVector3f> TranslateManipulator(int32 InManipulatorIndex, const FVector3f& InDelta) override;`
- L309 _protected prototype_ `virtual TArray<FVector3f> BlendPresets(int32 InManipulatorIndex, const TArray<float>& Weights) PURE_VIRTUAL(UMetaHumanCharacterEditorMeshBlendTool::BlendPresets, return {};);`
- L312 _protected prototype_ `virtual float GetAncestryCircleRadius() const;` — Getting the radius of an ancestry circle
- L316 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> PresetItemComponents;` — An array of static mesh components that represents the preset widgets for every manipulator in the viewport.
- L319 _private member_ `TArray<FVector> PresetItemPositions;` — Positions of the active gizmo preset widgets
- L322 _private prototype_ `void CreatePresetItem(UStaticMesh* ManipulatorMesh, const float GizmoScale, const FVector WidgetPosition, UMaterialInterface* ManipulatorMaterial);` — Creates preset manipulator widget for the selected manipulator in the viewport.
- L325 _private prototype_ `static bool CalculateWeights(const FVector& InputPosition, const TArray<FVector>& Targets, TArray<float>& OutResult);` — Uses RBF function to calculate weights for presets on a given region.
- L328 _private prototype_ `UStaticMesh* GetManipulatorDragHandleMesh() const;` — Mesh used for Drag state of the tool
- L331 _private prototype_ `UMaterialInterface* GetManipulatorDragHandleMaterial() const;` — Material used for Drag state of the tool
- L334 _private prototype_ `void SetWeightOnPresetMaterials(const TArray<float>& Weights);` — Change material weight property based on handle position
- L336 _private member_ `TObjectPtr<UStaticMeshComponent> AncestryCircleComponent;`

#### Free symbols / members of external scopes

- L211 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyValueSetDelegate, const FPropertyChangedEvent&);` — Delegate that executes on EPropertyChangeType::ValueSet property change event for face evaluation settings (FaceDelta, HeadScale). Mirrors the pattern from the former UMetaHumanCharacterEditorFaceEditingToolHeadParameterProperties.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshImportContextObject.h` (Private)


#### class `UMetaHumanCharacterEditorMeshImportContextObject`  
`class UMetaHumanCharacterEditorMeshImportContextObject : public UObject`  
_L19-81_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Context object stored in the InteractiveToolsContext's ContextObjectStore by UMetaHumanCharacterEditorMode.  It caches the two dynamic meshes that were last built for a given target-mesh key so that UMetaHumanCharacterEditorMeshImportTool can re-use them without triggering another async asset load + conversion when the tool is restarted against the same target mesh.
- L25 _public member_ `FMetaHumanCharacterTargetMeshKey TargetMeshKey;` — Key that identifies which target mesh the cached dynamic meshes were built from.
- L31 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> BodyDynamicMesh;` — Cached body (or combined) dynamic mesh.  Valid when the key is non-empty and the last load succeeded.
- L37 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> HeadDynamicMesh;` — Cached head dynamic mesh.  Only populated when the tool was in "mesh parts" mode (bUseCharacterParts == true) and a head mesh was provided.
- L43 _public member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> BodyAABBTree;` — Cached AABB tree for the body (or combined) dynamic mesh.  Kept in sync with BodyDynamicMesh and valid whenever BodyDynamicMesh is valid.
- L49 _public member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> HeadAABBTree;` — Cached AABB tree for the head dynamic mesh.  Only populated alongside HeadDynamicMesh in "mesh parts" mode.
- L52 _public function_ `bool HasValidMeshesForKey(const FMetaHumanCharacterTargetMeshKey& InKey) const` — Returns true when the store holds meshes that match @p InKey.
- L58 _public function_ `void SetCachedMeshes( const FMetaHumanCharacterTargetMeshKey& InKey, TSharedPtr<UE::Geometry::FDynamicMesh3> InBodyDynamicMesh, TSharedPtr<UE::Geometry::FDynamicMesh3> InHeadDynamicMesh, TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> InBodyAABBTree, TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> InHeadAABBTree)` — Stores new dynamic meshes and their AABB trees for the given key, replacing any previously cached data.
- L73 _public function_ `void Invalidate()` — Clears any cached mesh data.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshImportTargetScene.h` (Private)


#### class `UMetaHumanCharacterEditorMeshImportTargetScene`  
`class UMetaHumanCharacterEditorMeshImportTargetScene : public UObject`  
_L19-101_
- reflection: `UCLASS()`
- inherits: `UObject`
- L24 _public prototype_ `void Initialize(TObjectPtr<UMetaHumanCharacter> InMetaHumanCharacter, UWorld* InWorld);`
- L25 _public prototype_ `void Shutdown();`
- L27 _public prototype_ `void BuildCharacterDynamicMeshes(const TArray<FVector3f>& InBodyVertices, const TArray<FVector3f>& InFaceVertices, bool bShowCharacterMesh);`
- L29 _public prototype_ `void ClearTargetMesh();` — Resets the target mesh components to an empty state, ready for a new mesh to be loaded.
- L31 _public prototype_ `bool ApplyBuiltDynamicMeshes( bool bInUseCharacterParts, const TSharedPtr<UE::Geometry::FDynamicMesh3>& InBodyDynamicMesh, const TSharedPtr<UE::Geometry::FDynamicMesh3>& InHeadDynamicMesh, UObject* InBodyMesh, UObject* InHeadMesh, UObject* InCombinedMesh, const FVector& InLocation, TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> InBodyAABBTree = nullptr, TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> InHeadAABBTree = nullptr);`
- L41 _public prototype_ `bool ApplyBuiltDynamicMeshesFromContextObject( const UMetaHumanCharacterEditorMeshImportContextObject& InContextObject, bool bInUseCharacterParts, UObject* InBodyMesh, UObject* InHeadMesh, UObject* InCombinedMesh, const FVector& InLocation);` — Convenience overload that applies the cached dynamic meshes and AABB trees stored in UMetaHumanCharacterEditorMeshImportContextObject
- L47 _public prototype_ `void SetTargetTranslucentMaterial();`
- L48 _public prototype_ `void SetMaterialTranslucency(float InTranslucency);`
- L49 _public prototype_ `void SetMaterialColor(FLinearColor InColor);`
- L50 _public prototype_ `void SetTargetMaterialFromMesh(UObject* InMesh);`
- L51 _public prototype_ `void SetTargetMaterialsFromMeshes(UObject* InBodyMesh, UObject* InHeadMesh);`
- L53 _public prototype_ `void SetMeshDepthOffset(float InDepthOffset);`
- L55 _public prototype_ `bool HitTestMesh(const FRay& InRay, bool bInTestTarget, bool bInTestCharacter, bool bSelectVertexId, FMetaHumanTargetHitResult& OutHitResult);`
- L57 _public prototype_ `void SetMeshLocation(const FVector& InLocation);`
- L58 _public prototype_ `void SetMeshTransform(const FTransform& InTransform);`
- L60 _public prototype_ `bool IsUsingCharacterParts() const;`
- L61 _public prototype_ `const FTransform& GetBodyComponentTransform() const;`
- L62 _public prototype_ `const FTransform& GetHeadComponentTransform() const;`
- L64 _public prototype_ `FBox GetTargetMeshBounds() const;`
- L65 _public function_ `UDynamicMeshComponent* GetHeadDynamicMeshComponent() const`
- L66 _public function_ `UDynamicMeshComponent* GetBodyDynamicMeshComponent() const`
- L67 _public function_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> GetTargetBodyMeshAABBTree() const`
- L68 _public function_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> GetTargetHeadMeshAABBTree() const`
- L71 _public member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor;` — `UPROPERTY()`
- L75 _public member_ `TObjectPtr<UMetaHumanCharacter> MetaHumanCharacter;` — `UPROPERTY()`
- L78 _public member_ `TObjectPtr<UMaterialInterface> ImportMeshFaceMaterial;` — `UPROPERTY()`
- L81 _public member_ `TObjectPtr<UMaterialInterface> ImportMeshBodyMaterial;` — `UPROPERTY()`
- L85 _private member_ `TObjectPtr<UDynamicMeshComponent> BodyDynamicMeshComponent;` — `UPROPERTY()`
- L88 _private member_ `TObjectPtr<UDynamicMeshComponent> HeadDynamicMeshComponent;` — `UPROPERTY()`
- L91 _private member_ `TObjectPtr<UDynamicMeshComponent> DebugBodyModelDynamicMeshComponent;` — `UPROPERTY()`
- L93 _private member_ `bool bUsingCharacterParts = false;`
- L94 _private member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> CharacterBodyDynamicMesh;`
- L95 _private member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> CharacterHeadDynamicMesh;`
- L97 _private member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> TargetBodyMeshAABBTree;`
- L98 _private member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3> TargetHeadMeshAABBTree;`
- L99 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> CharacterBodyAABBTree;`
- L100 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> CharacterHeadAABBTree;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshImportTool.h` (Private)


#### enum `EMetaHumanCharacterOverlay`  
`enum class EMetaHumanCharacterOverlay : uint8`  
_L28-34_
- reflection: `UENUM()`
- L30 _public enumerator_ `NoOverlay UMETA(ToolTip = "Removes Overlay")`
- L31 _public enumerator_ `OverlayMesh UMETA(ToolTip = "Places the target mesh on top of everything")`
- L32 _public enumerator_ `OverlayMetaHuman UMETA(DisplayName = "Overlay MetaHuman", ToolTip = "Places the MetaHuman mesh on top of everything")`
- L33 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanMeshImportMode`  
`enum class EMetaHumanMeshImportMode : uint8`  
_L38-43_
- reflection: `UENUM()`
- L40 _public enumerator_ `Single`
- L41 _public enumerator_ `MeshParts`
- L42 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanCharacterEditorMeshImportToolBuilder`  
`class UMetaHumanCharacterEditorMeshImportToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L47-57_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L54 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L55 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorMeshImportToolProperties`  
`class UMetaHumanCharacterEditorMeshImportToolProperties : public UInteractiveToolPropertySet, public FMetaHumanCharacterClothVisibilityBase`  
_L60-214_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet,FMetaHumanCharacterClothVisibilityBase`
- L66 _public member_ `bool bUseCharacterParts = false;` — `UPROPERTY(EditAnywhere, Category = "Import Meshes")`
- L70 _public member_ `TSoftObjectPtr<UObject> CombinedMesh;` — `UPROPERTY(EditAnywhere, Category = "Import Meshes", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))` — Assign your full body character mesh to this slot.
- L73 _public member_ `TSoftObjectPtr<UObject> HeadMesh;` — `UPROPERTY(EditAnywhere, Category = "Import Meshes", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L76 _public member_ `TSoftObjectPtr<UObject> BodyMesh;` — `UPROPERTY(EditAnywhere, Category = "Import Meshes", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))`
- L79 _public member_ `bool bShowKeyPoints = true;` — `UPROPERTY(EditAnywhere, Category = "Visualization")`
- L83 _public member_ `FVector MeshOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Custom Mesh")` — Manually nudges the custom mesh position along each axis. Click and drag in the input text field to quickly change the offset value.
- L87 _public member_ `bool bUseGrayMaterialOnMesh = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Matcap", Category = "Visualization | Custom Mesh")` — Toggles a matcap shader on the custom mesh in the viewport.
- L90 _public member_ `bool bShowFacialTracking = false;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Facial Tracking")`
- L93 _public member_ `bool bEditFacialCurves = true;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Facial Tracking")`
- L96 _public member_ `FLinearColor TrackingCurvesColor = FLinearColor::Green;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Facial Tracking")`
- L99 _public member_ `FLinearColor TrackingPointsColor = FLinearColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Facial Tracking")`
- L102 _public member_ `float TrackingPointsSize = 4.f;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Facial Tracking", meta = (UIMin = "0.1", UIMax = "10.0", ClampMin = "0.1", ClampMax = "10.0"))`
- L106 _public member_ `float MeshOpacity = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Custom Mesh", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Controls the transparency of the custom mesh overlay in the viewport. Lower values let you see the MetaHuman mesh through it, useful when checking alignment.
- L110 _public member_ `FLinearColor MeshColor = FLinearColor(0.3f, 0.4f, 1.0f, 1.f);` — `UPROPERTY(EditAnywhere, DisplayName = "Matcap Color", Category = "Visualization | Custom Mesh")` — Sets the colour of the matcap shader applied to the custom mesh.
- L114 _public member_ `float BodyDelta = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Body Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — When fitting, the underlying body model won't perfectly match the input. The small difference, or 'vertex delta', is stored and this slider controls its application to the body mesh.
- L118 _public member_ `float HeadDelta = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Head Parameters", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — When fitting, the underlying head model won't perfectly match the input. The small difference, or 'vertex delta', is stored and this slider controls its application to the head mesh.
- L121 _public member_ `FBodyConformSolveSettings BodySolveSettings;` — `UPROPERTY(EditAnywhere, Category = "Advanced")`
- L124 _public member_ `FRefinementSettings RefinementSettings;` — `UPROPERTY(EditAnywhere, Category = "Advanced", meta=(ShowInnerProperties))`
- L128 _public member_ `bool bUseGrayMaterialOnMetaHuman = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Matcap", Category = "Visualization | MetaHuman")` — Toggles a matcap shader on the MetaHuman mesh in the viewport.
- L132 _public member_ `bool bUseGuidesTextureOnMetaHuman = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Guides Texture", Category = "Visualization | MetaHuman")` — When enabled, overlays the MetaHuman topology guide texture onto the mesh
- L136 _public member_ `FLinearColor MetaHumanMeshColor = FLinearColor(1.f, 0.125f, 0.f, 1.f);` — `UPROPERTY(EditAnywhere, DisplayName = "Matcap Color", Category = "Visualization | MetaHuman")` — Sets the colour of the matcap shader on the MetaHuman mesh.
- L140 _public member_ `float MetaHumanOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "Opacity", Category = "Visualization | MetaHuman", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Controls the transparency of the MetaHuman mesh in the viewport.
- L143 _public member_ `EMetaHumanCharacterOverlay Overlay = EMetaHumanCharacterOverlay::NoOverlay;` — `UPROPERTY(EditAnywhere, Category = "Visualization | MetaHuman")`
- L146 _public member_ `bool bShowBodyModelMesh = false;` — `UPROPERTY(EditAnywhere, Category = "Visualization | Debug")`
- L149 _public member_ `bool bShowBodyModelAPose = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Show Body Model A Pose", Category = "Visualization | Debug")`
- L152 _public member_ `bool bShowMetaHumanAPose = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Show MetaHuman A Pose", Category = "Visualization | Debug")`
- L156 _public member_ `bool bShowCustomKeyPoints = true;` — `UPROPERTY(EditAnywhere, Category = "Key Points")` — Toggles visibility of any additional key points you have manually added.
- L160 _public member_ `bool bShowPresetKeyPoints = false;` — `UPROPERTY(EditAnywhere, Category = "Key Points")` — Toggles visibility of the default MetaHuman preset key points. These are the default landmarks used on the MetaHuman mesh to guide the solve.
- L164 _public member_ `FLinearColor CustomKeyPointsColor = FLinearColor(0.f, 0.2f, 1.f, 1.f);` — `UPROPERTY(EditAnywhere, DisplayName = "Custom Key Points Color", Category = "Key Points")` — Sets the display colour of the key points belonging to your imported custom mesh.
- L168 _public member_ `FLinearColor MHKeyPointsColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, DisplayName = "MH Key Points Color", Category = "Key Points")` — Sets the display colour of the key points belonging to the MetaHuman mesh.
- L172 _public member_ `float KeyPointsScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Key Points", meta = (UIMin = "0.0", UIMax = "5.0", ClampMin = "0.0", ClampMax = "5.0"))` — Scales the size of the key point markers displayed in the viewport.
- L176 _public member_ `bool bShowConnectionLines = true;` — `UPROPERTY(EditAnywhere, Category = "Key Points")` — When enabled, draws lines between corresponding MetaHuman and custom mesh key points
- L179 _public member_ `EMetaHumanMeshImportMode Mode = EMetaHumanMeshImportMode::Single;` — `UPROPERTY()`
- L183 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L186 _public prototype_ `void StartBodyStepMeshConform();`
- L187 _public prototype_ `void StartFaceStepMeshConform();`
- L188 _public prototype_ `void StartAutoMeshConform();`
- L189 _public prototype_ `void StartAlignHeadMeshConform();`
- L190 _public prototype_ `bool CanProcess() const;`
- L191 _public prototype_ `bool CanReset() const;`
- L193 _public prototype_ `void RefineVertices();`
- L195 _public prototype_ `void OnAsyncConformComplete(bool bInSuccess, bool bWasCancelled);`
- L197 _public prototype_ `TMap<int32, FVector3f> GetKeyPointCorrespondencesFromCharacter() const;`
- L198 _public prototype_ `FMetaHumanCharacterTargetTrackingResults GetFaceTrackingFromCharacter() const;`
- L200 _public prototype_ `FMetaHumanCharacterTargetMeshKey GetTargetMeshKey() const;`
- L202 _public prototype_ `void TrackFace();`
- L203 _public prototype_ `bool CanTrackFace() const;`
- L204 _public prototype_ `void ResetBody();`
- L205 _public prototype_ `void ResetHead();`
- L208 _public prototype_ `void UpdateKeyPointVisibility();`
- L211 _private prototype_ `bool GetErrorMessageText(EImportErrorCode InErrorCode, FText& OutErrorMessage) const;`
- L212 _private prototype_ `void StartMeshConform(bool bIsAutoSolve, bool bDisableBodySolve, bool bDisableFaceSolve);`
- L213 _private prototype_ `FConformTargetMesh GetConformTargetMesh() const;`

#### class `UMetaHumanCharacterEditorMeshImportTool`  
`class UMetaHumanCharacterEditorMeshImportTool : public UMeshSurfacePointTool`  
_L217-332_
- reflection: `UCLASS()`
- inherits: `UMeshSurfacePointTool`
- L223 _public prototype_ `DECLARE_DELEGATE_RetVal(FVector2D, OnGetTrackerImageSize);`
- L226 _public prototype_ `virtual void Setup() override;`
- L227 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L229 _public prototype_ `virtual bool HitTest(const FRay& InRay, FHitResult& OutHit) override;`
- L230 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L231 _public prototype_ `virtual void OnBeginDrag(const FRay& InRay) override;`
- L232 _public prototype_ `virtual void OnUpdateDrag(const FRay& InRay) override;`
- L233 _public prototype_ `virtual void OnEndDrag(const FRay& InRay) override;`
- L235 _public function_ `virtual bool HasCancel() const override`
- L236 _public function_ `virtual bool HasAccept() const override`
- L237 _public function_ `virtual bool CanAccept() const override`
- L240 _public prototype_ `virtual void OnPropertyModified(UObject* InPropertySet, FProperty* InProperty) override;`
- L242 _public function_ `UMetaHumanCharacterEditorMeshImportToolProperties* GetMeshImportProperties() const`
- L243 _public prototype_ `TSharedPtr<FMetaHumanCurveDataController> GetCurveDataController() const;`
- L244 _public prototype_ `UTexture* GetTrackingImageTexture() const;`
- L245 _public prototype_ `FIntPoint GetTrackingImageSize() const;`
- L246 _public prototype_ `void RemoveAllKeyPoints();`
- L247 _public prototype_ `void DeleteFaceCurves();`
- L248 _public prototype_ `bool HasFaceCurves() const;`
- L249 _public prototype_ `void DeselectAllKeyPoints();`
- L250 _public prototype_ `void SetViewportClient(const TSharedPtr<FMetaHumanCharacterViewportClient>& InViewportClient);`
- L252 _public prototype_ `void ExportStateToDNA();`
- L254 _public member_ `FSimpleMulticastDelegate OnUpdateFacialTrackingCurvesDelegate;`
- L256 _public member_ `OnGetTrackerImageSize OnGetTrackerImageSizeDelegate;`
- L259 _protected prototype_ `virtual void OnTick(float InDeltaTime) override;`
- L260 _protected prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L261 _protected prototype_ `virtual void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L266 _private prototype_ `void OnTargetMeshChange();`
- L267 _private prototype_ `void SetShowAPose(bool bSetToAPose);`
- L268 _private prototype_ `void OnTargetMeshLoaded();`
- L269 _private prototype_ `void UpdateTargetMeshMaterial();`
- L271 _private prototype_ `void ApplyOverlayState();`
- L272 _private prototype_ `void UpdateMeshLocationFromOffset() const;`
- L273 _private prototype_ `void Initialize3DKeyPoints();`
- L274 _private prototype_ `void UpdateSelectedPointFromMechanic();`
- L275 _private prototype_ `void SetBodyDelta(float InBodyDelta, bool bRebuildDynamicMeshes);`
- L276 _private prototype_ `void SetHeadDelta(float InHeadDelta, bool bRebuildDynamicMeshes);`
- L277 _private prototype_ `void SetNeedsFullUpdate(const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey);`
- L278 _private prototype_ `void OnCharacterStateChanged(bool bRebuildKeyPoints, bool bRebuildDynamicMeshes = true);`
- L279 _private prototype_ `void OnCharacterVerticesChanged(const TArray<FVector3f>& InBodyVertices, const TArray<FVector3f>& InFaceVertices, bool bRebuildKeyPoints, bool bRebuildDynamicMeshes = true);`
- L280 _private prototype_ `void DisplayError(const FText& InErrorMessage) const;`
- L282 _private member_ `TSharedPtr<class FMeshImportToolInputProcessor> InputProcessor;`
- L285 _private member_ `TObjectPtr<UMetaHumanCharacterEditorMeshImportToolProperties> MeshImportProperties;` — `UPROPERTY()`
- L288 _private member_ `TObjectPtr<UMeshTarget3DKeyPointMechanic> KeyPointsMechanic3D;` — `UPROPERTY()`
- L291 _private member_ `TObjectPtr<UMeshTargetContourMechanic> ContourMechanic;` — `UPROPERTY()`
- L294 _private member_ `TObjectPtr<UMetaHumanCharacterEditorMeshImportTargetScene> MeshTargetScene;` — `UPROPERTY()`
- L297 _private member_ `TObjectPtr<UMetaHumanCharacter> MetaHumanCharacter = nullptr;` — `UPROPERTY()`
- L299 _private member_ `FDelegateHandle OnAsyncConformIterationDelegateHandle;`
- L300 _private member_ `FDelegateHandle OnAsyncConformCompleteDelegateHandle;`
- L301 _private member_ `FDelegateHandle OnBodyStateChangedDelegateHandle;`
- L302 _private member_ `FDelegateHandle OnTargetMeshKeyPointsChangedDelegateHandle;`
- L303 _private member_ `FDelegateHandle OnPreviewMaterialChangedFromGrayDelagateHandle;`
- L306 _private member_ `bool bIsRebuildingKeyPoints = false;` — Re-entrancy guard for the OnTargetMeshKeyPointsChanged lambda — prevents a rebuild from recursively triggering another rebuild if any downstream path commits again.
- L308 _private member_ `TSharedPtr<const FMetaHumanCharacterBodyIdentity::FState> PreConformBodyState;`
- L309 _private member_ `TSharedPtr<const FMetaHumanCharacterIdentity::FState> PreConformFaceState;`
- L312 _private member_ `TSharedPtr<const FMetaHumanCharacterBodyIdentity::FState> SetupBodyState;` — Body and face states captured at Setup() — used to restore state on cancel/non-full-update shutdown.
- L313 _private member_ `TSharedPtr<const FMetaHumanCharacterIdentity::FState> SetupFaceState;`
- L315 _private member_ `FMetaHumanTargetHitResult LastHitResult;`
- L317 _private member_ `TOptional<EMetaHumanCharacterSkinPreviewMaterial> LastUsedPreviewMaterial;`
- L319 _private member_ `bool bHasBeenShutdown = false;`
- L320 _private member_ `bool bNeedsFullUpdate = false;`
- L321 _private member_ `FMetaHumanCharacterTargetMeshKey ConformedTargetMeshKey;`
- L322 _private member_ `bool bTargetMeshChangePending = false;`
- L323 _private member_ `bool bIsLoadingTargetMesh = false;`
- L324 _private member_ `TWeakPtr<SNotificationItem> TargetMeshLoadNotification;`
- L325 _private member_ `TSharedPtr<FStreamableHandle> TargetMeshStreamableHandle;`
- L327 _private member_ `bool bRightClickActive = false;`
- L329 _private member_ `TWeakPtr<FMetaHumanCharacterViewportClient> ViewportClient = nullptr;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)
- L35 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterOverlay, EMetaHumanCharacterOverlay::Count);`
- L44 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanMeshImportMode, EMetaHumanMeshImportMode::Count);`
- L223 _delegate_ `DECLARE_DELEGATE_RetVal(FVector2D, OnGetTrackerImageSize);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshTarget3DKeyPointMechanic.h` (Private)


#### struct `FKeyPointData`  
`struct FKeyPointData`  
_L17-60_
- reflection: `USTRUCT()`
- L22 _public member_ `FMetaHumanCharacterTargetKeyPoints TargetKeyPoints;` — `UPROPERTY()`
- L25 _public member_ `TArray<FName> ManipulatorIDToKeyPointName;` — `UPROPERTY()`
- L28 _public member_ `TArray<EHitMeshType> ManipulatorIDHitType;` — `UPROPERTY()`
- L31 _public member_ `TArray<FVector> ManipulatorPositions;` — `UPROPERTY()`
- L35 _public member_ `TMap<FName, EKeyPointType> KeyPointTypes;` — `UPROPERTY()` — Track type for each keypoint
- L37 _public prototype_ `void Initialize(const FMetaHumanCharacterTargetKeyPoints& InCharacterTargetKeyPoints);`
- L39 _public prototype_ `bool KeyPointIndexExists(const FName& InName) const;`
- L40 _public prototype_ `bool KeyPointTargetExists(const FName& InName) const;`
- L41 _public prototype_ `int32 GetCharacterManipulatorIndex(const FName& InName) const;`
- L42 _public prototype_ `int32 GetTargetManipulatorIndex(const FName& InName) const;`
- L43 _public prototype_ `int32 GetCorrespondingManipulatorIndex(int32 InManipulatorIndex) const;`
- L45 _public prototype_ `void AddTargetKeyPoint(const FName& InName, bool bInIsHead, const FVector& InTargetWorldPosition, const FTransform& InWorldToLocalTransform);`
- L46 _public prototype_ `void AddCharacterKeyPoint(const FName& InName, int32 InCharacterVertexID, bool bInIsHead, const FVector& InCharacterPointPosition);`
- L47 _public prototype_ `void RemoveKeyPoint(int32 InManipulatorIndex);`
- L48 _public prototype_ `void RemoveAllCustomKeyPoints();`
- L50 _public prototype_ `void CopyToKeyPointCorrespondences(TMap<int32, FVector3f>& OutKeyPointCorrespondences) const;`
- L51 _public prototype_ `bool GetKeyPointNameForManipulatorIndex(int32 InManipulatorIndex, FName& OutKeyPointName) const;`
- L52 _public prototype_ `TArray<FVector> RebuildManipulatorPositions(const FTransform& InBodyComponentTransform, const FTransform& InHeadComponentTransform, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState);`
- L57 _public prototype_ `void UpdateCharacterManipulatorPositions(const TArray<FVector3f>& InBodyVertices, const TArray<FVector3f>& InFaceVertices, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState);`

#### class `UMeshTarget3DKeyPointMechanic`  
`class UMeshTarget3DKeyPointMechanic : public UInteractionMechanic`  
_L63-180_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractionMechanic`
- L68 _public prototype_ `virtual void Setup(UInteractiveTool* InParentTool) override;`
- L69 _public prototype_ `virtual void Shutdown() override;`
- L71 _public prototype_ `void Initialize(TObjectPtr<UMetaHumanCharacter> InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState, TObjectPtr<UMetaHumanCharacterEditorMeshImportTargetScene> InMeshTargetScene);`
- L77 _public prototype_ `void RebuildKeyPointData(TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState);`
- L80 _public prototype_ `void RecreateManipulators();`
- L82 _public prototype_ `void Clear();`
- L83 _public prototype_ `void RemoveAllKeyPoints();`
- L84 _public prototype_ `void DeleteSelectedKeyPoint();`
- L85 _public prototype_ `void DeselectAll();`
- L87 _public prototype_ `void DrawHUD(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI);`
- L88 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L89 _public prototype_ `void SetCharacterManipulatorsColor(FLinearColor InColor);`
- L90 _public prototype_ `void SetTargetManipulatorsColor(FLinearColor InColor);`
- L91 _public prototype_ `void SetManipulatorsScale(float Scale);`
- L93 _public prototype_ `virtual bool HitTest(const FRay& InRay, FHitResult& OutHit);`
- L94 _public prototype_ `virtual void OnBeginDrag(bool bCtrlModifier, bool bIsRightClick, bool bShiftModifier);`
- L95 _public prototype_ `virtual bool OnEndDrag(const FMetaHumanTargetHitResult& InHitResult);`
- L97 _public prototype_ `bool IsDraggingManipulator() const;`
- L98 _public prototype_ `EHitMeshType GetDraggingManipulatorHitMeshType() const;`
- L99 _public prototype_ `void UpdateDraggingManipulatorPosition(const FMetaHumanTargetHitResult& InHitResult);`
- L100 _public prototype_ `bool GetSelectedManipulatorWorldPosition(FVector& OutPosition) const;`
- L101 _public function_ `int32 GetSelectedManipulator() const`
- L103 _public prototype_ `void UpdateComponentTransform();`
- L104 _public prototype_ `void UpdateCharacterManipulatorPositions(const TArray<FVector3f>& InBodyVertices, const TArray<FVector3f>& InFaceVertices, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState);`
- L109 _public prototype_ `void UpdateKeyPointManipulatorsVisibility();` — Visibility control
- L112 _public member_ `bool bShowCustomKeyPoints = true;` — Visibility flags
- L113 _public member_ `bool bShowPresetBodyKeyPoints = false;`
- L116 _public function_ `bool IsInitialized() const` — True between Initialize() and Clear()/Shutdown(). Used by observers to skip rebuilds issued before the mechanic is ready.
- L119 _protected prototype_ `bool ShouldShowKeyPoint(const FName& KeyPointName) const;`
- L121 _protected prototype_ `virtual void CreateManipulator(const FVector& InPosition, bool bInIsCharacter);`
- L122 _protected prototype_ `virtual UStaticMesh* GetManipulatorMesh(bool bInIsCharacterMesh) const;`
- L123 _protected prototype_ `virtual UMaterialInterface* GetManipulatorMaterial(bool bInIsCharacterMaterial) const;`
- L124 _protected prototype_ `virtual float GetManipulatorScale() const;`
- L126 _protected prototype_ `void SelectManipulator(int32 InManipulatorIndex);`
- L127 _protected prototype_ `void SetHoveredManipulator(int32 InManipulatorIndex);`
- L128 _protected prototype_ `void SetDraggingManipulator(int32 InManipulatorIndex);`
- L130 _protected prototype_ `void UpdateManipulatorPosition(const FMetaHumanTargetHitResult& InHitResult, int32 InManipulatorIndex);`
- L134 _protected member_ `TObjectPtr<UMetaHumanCharacter> MetaHumanCharacter;` — `UPROPERTY()`
- L137 _protected member_ `FMetaHumanCharacterTargetMeshKey TargetMeshKey;` — `UPROPERTY()`
- L140 _protected member_ `FKeyPointData KeyPointData;` — `UPROPERTY()`
- L143 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> ManipulatorsActor;` — `UPROPERTY()`
- L146 _protected member_ `TArray<TObjectPtr<UStaticMeshComponent>> ManipulatorComponents;` — `UPROPERTY()`
- L149 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorMeshImportTargetScene> MeshTargetScene;` — `UPROPERTY()`
- L152 _protected member_ `TObjectPtr<UWorld> TargetWorld;` — `UPROPERTY()`
- L156 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorMeshEditingToolProperties> MeshEditingToolProperties;` — `UPROPERTY()` — Mesh editing property set
- L158 _protected member_ `bool bIsInitialized = false;`
- L159 _protected member_ `bool bCtrlToggledOnBeginDrag = false;`
- L160 _protected member_ `bool bIsRightClick = false;`
- L161 _protected member_ `bool bShiftToggledOnBeginDrag = false;`
- L162 _protected member_ `bool bWasPresetKeyPointClick = false;`
- L164 _protected member_ `FMetaHumanCharacterTargetKeyPoints BeginDragTargetKeyPoints;`
- L165 _protected member_ `TMap<FName, EKeyPointType> BeginDragKeyPointTypes;`
- L168 _protected member_ `int32 HoveredManipulator = INDEX_NONE;` — Index of the manipulator hovering
- L171 _protected member_ `int32 DraggingManipulator = INDEX_NONE;` — Index of currently dragging manipulator
- L174 _protected member_ `int32 SelectedManipulator = INDEX_NONE;` — Index of currently selected manipulator
- L176 _protected member_ `FTransform TargetBodyComponentTransform;`
- L177 _protected member_ `FTransform TargetHeadComponentTransform;`
- L179 _protected member_ `float CurrentManipulatorScale = 1.f;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshTargetContourMechanic.h` (Private)


#### class `UMeshTargetContourMechanic`  
`class UMeshTargetContourMechanic : public UInteractionMechanic, public FEditorUndoClient`  
_L17-106_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractionMechanic,FEditorUndoClient`
- L22 _public prototype_ `virtual void Setup(UInteractiveTool* InParentTool) override;`
- L23 _public prototype_ `virtual void Shutdown() override;`
- L25 _public prototype_ `void Initialize(TObjectPtr<UMetaHumanCharacter> InMetaHumanCharacter, TObjectPtr<UMetaHumanCharacterEditorMeshImportTargetScene> InMeshTargetScene, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey);`
- L26 _public prototype_ `TSharedPtr<FMetaHumanCurveDataController> GetCurveDataController() const;`
- L27 _public prototype_ `UTexture* GetTrackingImageTexture() const;`
- L28 _public prototype_ `FIntPoint GetTrackingImageSize() const;`
- L30 _public prototype_ `bool TrackFaceInCurrentView(const FVector& InMeshOffset);`
- L31 _public prototype_ `bool TrackFaceWithAutoFraming(const FVector& InMeshOffset);`
- L33 _public prototype_ `bool HasTrackingResults() const;`
- L35 _public prototype_ `void DeleteFaceCurves();`
- L36 _public prototype_ `void Clear();`
- L38 _public prototype_ `void UpdateComponentTransform();`
- L40 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L43 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L44 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L45 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L48 _public prototype_ `virtual void BeginDestroy() override;`
- L51 _protected prototype_ `FIntPoint GetImageSize() const;`
- L52 _protected prototype_ `bool TrackFaceFromSceneComponent(const FVector& InMeshOffset);`
- L54 _protected member_ `bool bIsTracking = false;`
- L58 _protected member_ `bool bIsApplyingUndo = false;` — Guards OnCurveDataControllerUpdated from re-committing to the character asset while we are rebuilding derived state in response to an undo/redo.
- L60 _protected prototype_ `void ProjectTo3DPoints();`
- L61 _protected prototype_ `void OnCurveDataControllerUpdated();`
- L62 _protected prototype_ `void SubscribeToCurveDataController();`
- L66 _protected prototype_ `void RebuildAfterUndo();` — Rebuild mechanic-side derived state (controller draw data, TrackingContours map, 3D splines) after UE's transaction system has restored UMetaHumanContourData / UMetaHumanCharacter.
- L70 _protected member_ `TObjectPtr<UMetaHumanCharacter> MetaHumanCharacter;` — `UPROPERTY()`
- L73 _protected member_ `TObjectPtr<UWorld> TargetWorld;` — `UPROPERTY()`
- L76 _protected member_ `TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;` — `UPROPERTY()`
- L79 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorLandmarkTracker> LandmarkTracker;` — `UPROPERTY()`
- L82 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorMeshImportTargetScene> MeshTargetScene;` — `UPROPERTY()`
- L85 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> SplinesActor;` — `UPROPERTY()`
- L88 _protected member_ `TMap<FString, TObjectPtr<USplineComponent>> ContourSplines;` — `UPROPERTY()`
- L90 _protected member_ `FMinimalViewInfo CapturedViewInfo;`
- L91 _protected member_ `FVector CapturedMeshOffset;`
- L93 _protected member_ `int32 DefaultTrackingImageWidth = 2048;`
- L94 _protected member_ `int32 DefaultTrackingImageHeight = 2048;`
- L96 _protected member_ `FMetaHumanCharacterTargetMeshKey TargetMeshKey;`
- L97 _protected member_ `TMap<FString, TArray<FVector2D>> TrackingContours;`
- L98 _protected member_ `TMap<FString, TArray<FVector>> TrackingContours3D;`
- L99 _protected member_ `FTransform TargetComponentTransform;`
- L102 _protected member_ `TObjectPtr<UTexture2D> RestoredTrackerImage;` — `UPROPERTY()`
- L103 _protected member_ `FIntPoint RestoredTrackerImageSize;`
- L105 _protected prototype_ `FBox CalculateHeadBounds() const;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorMeshTargetHitResult.h` (Private)


#### enum `EHitMeshType`  
`enum class EHitMeshType : uint8`  
_L11-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `TargetBody`
- L15 _public enumerator_ `TargetHead`
- L16 _public enumerator_ `CharacterBody`
- L17 _public enumerator_ `CharacterHead`

#### struct `FMetaHumanTargetHitResult`  
`struct FMetaHumanTargetHitResult`  
_L21-33_
- reflection: `USTRUCT()`
- L26 _public member_ `FHitResult HitResult;` — `UPROPERTY()`
- L29 _public member_ `EHitMeshType HitMeshType = EHitMeshType::None;` — `UPROPERTY()`
- L32 _public member_ `int32 HitVertexID = INDEX_NONE;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorPipelineTools.h` (Private)


#### enum `EMetaHumanCharacterPipelineEditingTool`  
`enum class EMetaHumanCharacterPipelineEditingTool : uint8`  
_L21-24_
- reflection: `UENUM()`
- L23 _public enumerator_ `Pipeline`

#### class `UMetaHumanCharacterEditorPipelineToolBuilder`  
`class UMetaHumanCharacterEditorPipelineToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L27-39_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L34 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L38 _public member_ `EMetaHumanCharacterPipelineEditingTool ToolType = EMetaHumanCharacterPipelineEditingTool::Pipeline;` — `UPROPERTY()`

#### class `UMetaHumanCharacterEditorPipelineToolProperties`  
`class UMetaHumanCharacterEditorPipelineToolProperties : public UInteractiveToolPropertySet`  
_L46-120_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties used to customize the pipeline UI and generate the parameters for a pipeline assembly NOTE: this is transient and will reset when the tool closes, it is a temporary solution until we find a better solution
- L52 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _public prototype_ `void CopyFrom(const FMetaHumanCharacterAssemblySettings& InAssemblySettings);`
- L56 _public prototype_ `void CopyTo(FMetaHumanCharacterAssemblySettings& OutAssemblySettings);`
- L59 _public prototype_ `bool IsUEFN() const;`
- L63 _public member_ `EMetaHumanDefaultPipelineType PipelineType = EMetaHumanDefaultPipelineType::Cinematic;` — `UPROPERTY(EditAnywhere, Category = "Assembly Selection", meta = (DisplayName = "Assembly", EditCondition = InitializePipelineTypeVisibility, EditConditionHides))` — Selected type of pipeline to run the assembly
- L66 _public prototype_ `bool InitializePipelineTypeVisibility() const;` — `UFUNCTION()`
- L68 _public member_ `FName DefaultAnimationSystemNameAnimBP = TEXT("Ani`
- L72 _public member_ `FName AnimationSystemName = DefaultAnimationSystemNameAnimBP;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta = (DisplayName = "Animation System", GetOptions = GetAnimationSystemOptions, EditCondition = InitializeAnimationSystemNameVisibility, EditConditionHides))` — Target animation system to be used by the assembled MetaHuman.
- L76 _public prototype_ `TArray<FName> GetAnimationSystemOptions() const;` — `UFUNCTION()` — Get the list of available animation systems, including ones registered by external plugins.
- L84 _public prototype_ `bool InitializeAnimationSystemNameVisibility() const;` — `UFUNCTION()` — Controls visibility for the animation system combo box. The combo box will be visible if another plugin registers an animation system. Animation system selection currently is only possible for Cinematic and Optimized MetaHumans.
- L88 _public member_ `EMetaHumanQualityLevel PipelineQuality = EMetaHumanQualityLevel::High;` — `UPROPERTY(EditAnywhere, Category = "Assembly Selection", meta = (DisplayName = "Quality", InvalidEnumValues = "Cinematic", EditConditionHides, EditCondition = "PipelineType == EMetaHumanDefaultPipelineType::Optimized || PipelineType == EMetaHumanDefaultPipelineType::UEFN"))` — Quality setting for the pipeline
- L92 _public member_ `FDirectoryPath RootDirectory{ TEXT("/Game` — `UPROPERTY(EditAnywhere, Category = "Targets", meta = (ContentDir, PipelineDisplay = "Targets", EditConditionHides, EditCondition = "(PipelineType == EMetaHumanDefaultPipelineType::Cinematic || PipelineType == EMetaHumanDefaultPipelineType::Optimized)"))` — Path to the Root directory where the assembled assets will be placed so that the final structure is <RootDirectory>/<Name>
- L96 _public member_ `FDirectoryPath CommonDirectory{ TEXT("/Game` — `UPROPERTY(EditAnywhere, Category = "Advanced Options", meta = (ContentDir, PipelineDisplay = "Targets", EditConditionHides, EditCondition = "(PipelineType == EMetaHumanDefaultPipelineType::Cinematic || PipelineType == EMetaHumanDefaultPipelineType::Optimized)"))` — Path to a project directory where assets shared by assembled MetaHumans are place. If referenced assets are missing, they will be populated as needed.
- L99 _public member_ `FString DefaultName;` — Character default name, usually the name of the asset.
- L103 _public member_ `FString NameOverride;` — `UPROPERTY(EditAnywhere, Category = "Targets", meta = (DisplayName = "Name", EditConditionHides, EditCondition = "(PipelineType == EMetaHumanDefaultPipelineType::Cinematic || PipelineType == EMetaHumanDefaultPipelineType::Optimized || PipelineType == EMetaHumanDefaultPipelineType::UEFN)"))` — Character name to use for the generated assets.
- L106 _public member_ `FSimpleDelegate OnPipelineSelectionChanged;` — Trigger when either PipelineType or Quality are modified
- L109 _public prototype_ `[[nodiscard]] TSoftClassPtr<class UMetaHumanCollectionPipeline> GetSelectedPipelineClass() const;` — Returns the class of the currently selected pipeline
- L112 _public prototype_ `[[nodiscard]] TObjectPtr<class UMetaHumanCollectionPipeline> GetSelectedPipeline() const;` — Helpers to get an UObject pointer to the instance of the currently selected pipeline from the character data
- L113 _public prototype_ `[[nodiscard]] TObjectPtr<class UMetaHumanCollectionEditorPipeline> GetSelectedEditorPipeline() const;`
- L116 _public prototype_ `void UpdateSelectedPipeline();` — Updates the character data with the selected pipeline
- L119 _public prototype_ `[[nodiscard]] FMetaHumanCharacterEditorBuildParameters InitBuildParameters() const;` — Generates the Build params to set in the tool for passing to FMetaHumanCharacterEditorBuild::BuildMetaHumanCharacter()

#### class `UMetaHumanCharacterEditorPipelineTool`  
`class UMetaHumanCharacterEditorPipelineTool : public USingleTargetWithSelectionTool`  
_L126-161_
- reflection: `UCLASS()`
- inherits: `USingleTargetWithSelectionTool`
- desc: Tool for manipulating the build pipeline.
- L132 _public prototype_ `virtual void Setup() override;`
- L133 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L135 _public function_ `virtual bool HasCancel() const override`
- L136 _public function_ `virtual bool HasAccept() const override`
- L137 _public function_ `virtual bool CanAccept() const override`
- L139 _public prototype_ `virtual void OnPropertyModified(UObject* InPropertySet, FProperty* InProperty) override;`
- L142 _public function_ `UMetaHumanCharacterEditorPipelineToolProperties* GetPipelineProperty() const`
- L144 _public prototype_ `bool CanBuild(FText& OutErrorMsg) const;`
- L145 _public prototype_ `void Build() const;`
- L150 _protected prototype_ `void UpdateToolMessage();` — Refreshes informational messages displayed by the tool (e.g. Virtual Textures usage notice).
- L154 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorPipelineToolProperties> PropertyObject;` — `UPROPERTY()`
- L157 _protected member_ `FMetaHumanCharacterAssemblySettings PreviousAssemblySettings;` — Keep track of previously set assembly settings
- L160 _protected member_ `FDelegateHandle UseVirtualTexturesChangedHandle;` — Handle to the OnUseVirtualTexturesChanged delegate so it can be removed on Shutdown

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorPresetsTool.h` (Private)


#### class `UMetaHumanCharacterEditorPresetsToolBuilder`  
`class UMetaHumanCharacterEditorPresetsToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L18 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L19 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`

#### enum `EAssetThumbnailAcquisitionType`  
`enum class EAssetThumbnailAcquisitionType : uint8`  
_L24-30_
- reflection: `UENUM()`
- L26 _public enumerator_ `Camera UMETA(DisplayName = "Use Face Camera")`
- L27 _public enumerator_ `Custom UMETA(DisplayName = "Use Custom Image")`
- L29 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterPresetsManagementProperties`  
`struct FMetaHumanCharacterPresetsManagementProperties`  
_L34-52_
- reflection: `USTRUCT()`
- L39 _public member_ `FString Factory;` — `UPROPERTY(EditAnywhere, Category = "Tags")`
- L42 _public member_ `FString User;` — `UPROPERTY(EditAnywhere, Category = "Tags")`
- L45 _public member_ `bool bUseAssetThumbnail = false;` — `UPROPERTY(EditAnywhere, Category = "Thumbnail")`
- L48 _public member_ `EAssetThumbnailAcquisitionType AssetThumbnail = EAssetThumbnailAcquisitionType::Custom;` — `UPROPERTY(EditAnywhere, Category = "Thumbnail")`
- L51 _public member_ `FDirectoryPath ImagePath;` — `UPROPERTY(EditAnywhere, Category = "Thumbnail")`

#### struct `FMetaHumanCharacterPresetsLibraryProperties`  
`struct FMetaHumanCharacterPresetsLibraryProperties`  
_L55-64_
- reflection: `USTRUCT()`
- L60 _public member_ `FDirectoryPath Path;` — `UPROPERTY(EditAnywhere, Category = "Library Management")`
- L63 _public member_ `FDirectoryPath ProjectPath;` — `UPROPERTY(EditAnywhere, Category = "Library Management", meta = (ContentDir))`

#### class `UMetaHumanCharacterEditorPresetsToolProperties`  
`class UMetaHumanCharacterEditorPresetsToolProperties : public UInteractiveToolPropertySet`  
_L67-83_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L74 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L79 _public member_ `FMetaHumanCharacterPresetsManagementProperties PresetsManagement;` — `UPROPERTY(EditAnywhere, Category = "Presets Management")`
- L82 _public member_ `FMetaHumanCharacterPresetsLibraryProperties LibraryManagement;` — `UPROPERTY(EditAnywhere, Category = "Library Management")`

#### class `UMetaHumanCharacterEditorPresetsTool`  
`class UMetaHumanCharacterEditorPresetsTool : public USingleSelectionTool`  
_L86-113_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- L92 _public function_ `UMetaHumanCharacterEditorPresetsToolProperties* GetPresetsToolProperties() const` — Get the Presets Tool properties.
- L95 _public prototype_ `virtual void Setup();`
- L97 _public function_ `virtual bool HasCancel() const`
- L98 _public function_ `virtual bool HasAccept() const`
- L99 _public function_ `virtual bool CanAccept() const`
- L101 _public prototype_ `virtual void OnPropertyModified(UObject* InPropertySet, FProperty* InProperty) override;`
- L104 _public prototype_ `void ApplyPresetCharacter(TNotNull<class UMetaHumanCharacter*> InPresetCharacter);`
- L112 _private member_ `TObjectPtr<UMetaHumanCharacterEditorPresetsToolProperties> PresetsProperties;` — `UPROPERTY()` — Properties of the Presets Tool. These are displayed in the details panel when the tool is activated.

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_RANGE_BY_COUNT(EAssetThumbnailAcquisitionType, EAssetThumbnailAcquisitionType::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorSkinTool.h` (Private)


#### class `UMetaHumanCharacterEditorSkinToolBuilder`  
`class UMetaHumanCharacterEditorSkinToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L21-30_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L28 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorSkinToolProperties`  
`class UMetaHumanCharacterEditorSkinToolProperties : public UInteractiveToolPropertySet`  
_L38-115_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for the Skin tool. These are displayed in the details panel of the Skin Tool and are how the user can edit skin parameters and, for now, are the same as the ones stored in UMetaHumanCharacter
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L52 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSkinPropertyValueSetDelegate, const FPropertyChangedEvent& PropertyChangedEvent);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated
- L53 _public member_ `FOnSkinPropertyValueSetDelegate OnSkinPropertyValueSetDelegate;`
- L56 _public member_ `FSimpleMulticastDelegate OnSkinToolCommandChangeApplied;` — Fires after a transaction writes settings into the tool properties.
- L61 _public prototype_ `void CopyTo(FMetaHumanCharacterSkinSettings& OutSkinSettings);` — Utility functions for copying to & from MetaHuman Character Skin Settings and Skin Tool Properties
- L62 _public prototype_ `void CopyFrom(const FMetaHumanCharacterSkinSettings& InSkinSettings);`
- L67 _public prototype_ `void CopyTo(FMetaHumanCharacterFaceEvaluationSettings& OutFaceEvaluationSettings);` — Utility functions for copying to & from MetaHuman Character Evaluation Properties
- L68 _public prototype_ `void CopyFrom(const FMetaHumanCharacterFaceEvaluationSettings& InFaceEvaluationSettings);`
- L77 _public prototype_ `bool CanEditRigRestrictedProperties() const;` — Returns true when rig-restricted skin properties are editable (the character is not rigged or rig-pending). Rig-restricted properties are the ones that regenerate the synthesized skin texture in ways that affect the rig: face/body texture indices (including the texture-attribute filter controls that drive the face texture index) and the Texture Position Offset.
- L83 _public prototype_ `static bool IsRigRestrictedProperty(const FProperty* InProperty);` — Returns true if InProperty is one of the rig-restricted skin properties. See CanEditRigRestrictedProperties for the list of restricted properties.
- L88 _public member_ `FMetaHumanCharacterSkinProperties Skin;` — `UPROPERTY(EditAnywhere, Category = "Skin", meta = (ShowOnlyInnerProperties, TransientToolProperty))`
- L91 _public member_ `bool bIsSkinFilterEnabled;` — `UPROPERTY(EditAnywhere, DisplayName = "Use Texture Index Filters", Category = "Skin")`
- L94 _public member_ `TArray<int32> SkinFilterValues;` — `UPROPERTY(EditAnywhere, Category = "Skin")`
- L97 _public member_ `int32 SkinFilterIndex;` — `UPROPERTY(EditAnywhere, DisplayName = "Face Filter Index", Category = "Skin")`
- L100 _public member_ `FMetaHumanCharacterFaceEvaluationSettings FaceEvaluationSettings;` — `UPROPERTY(EditAnywhere, Category = "FaceEvaluation", meta = (ShowOnlyInnerProperties, TransientToolProperty))`
- L103 _public member_ `FMetaHumanCharacterFrecklesProperties Freckles;` — `UPROPERTY(EditAnywhere, Category = "Freckles", meta = (ShowOnlyInnerProperties, TransientToolProperty))`
- L106 _public member_ `FMetaHumanCharacterAccentRegions Accents;` — `UPROPERTY(EditAnywhere, Category = "Accents", meta = (ShowOnlyInnerProperties, TransientToolProperty))`
- L110 _public member_ `FMetaHumanCharacterTextureSourceResolutions DesiredTextureSourcesResolutions;` — `UPROPERTY(EditAnywhere, Category = "Textures Sources", AdvancedDisplay, meta = (TransientToolProperty))` — The desired resolutions to use when requesting to download texture sources
- L114 _public member_ `bool bShowHands = false;` — `UPROPERTY(EditAnywhere, Category = "Skin")` — When enabled, poses the character's hands with an open palm pose so the hand textures and materials can be inspected. The character must be rigged for the pose to take effect.

#### class `UMetaHumanCharacterEditorSkinTool`  
`class UMetaHumanCharacterEditorSkinTool : public USingleSelectionTool`  
_L121-230_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- desc: The Skin Tool allows the user to edit properties of the MetaHuman Skin
- L127 _public function_ `UMetaHumanCharacterEditorSkinToolProperties* GetSkinToolProperties() const` — Get the Skin Tool properties.
- L130 _public prototype_ `virtual void Setup();`
- L131 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType);`
- L133 _public function_ `virtual bool HasCancel() const`
- L134 _public function_ `virtual bool HasAccept() const`
- L135 _public function_ `virtual bool CanAccept() const`
- L139 _public prototype_ `bool IsFilteredFaceTextureIndicesValid() const;` — Returns true if the filter indices are valid.
- L142 _public prototype_ `void SetShowHandsPose(bool bShowHandsPose);` — Enables or disables the show hands pose on the character. Does not move the camera.
- L150 _private prototype_ `void OnShowHandsChanged(bool bInShowHands);` — Handler for changes to UMetaHumanCharacterEditorSkinToolProperties::bShowHands. Toggles the show-hands pose, manages the camera-focus ticker, and restores the pre-pose camera frame.
- L154 _protected prototype_ `void UpdateSkinState() const;`
- L158 _private prototype_ `const FText GetCommandChangeDescription() const;`
- L165 _private prototype_ `bool UpdateSkinSynthesizedTexture();` — Updates the Skin Texture. Called whenever one of the skin texture parameters changes Will prompt the user if the character currently has high resolution textures to avoid loss of data @return true if a change was applied to character and false otherwise.
- L167 _private prototype_ `void UpdateSkinToolProperties(TWeakObjectPtr<UInteractiveToolManager> InToolManager, const FMetaHumanCharacterFaceEvaluationSettings& InFaceEvaluationSettings);`
- L169 _private prototype_ `void UpdateFaceTextureFromFilterIndex();`
- L171 _private prototype_ `void SetEnableSkinFilter(bool bInEnableSkinFilter);`
- L177 _private prototype_ `void UpdateRiggedWarning();` — Posts a warning to the mode toolkit when the character is rigged (face/body texture selection is locked) and clears it otherwise.
- L186 _private member_ `TObjectPtr<UMetaHumanCharacterEditorSkinToolProperties> SkinToolProperties;` — `UPROPERTY()` — Properties of the Skin Tool. These are displayed in the details panel when the tool is activated.
- L189 _private member_ `FMetaHumanCharacterSkinSettings PreviousSkinSettings;` — Keep track of previously set skin settings
- L190 _private member_ `FMetaHumanCharacterFaceEvaluationSettings PreviousFaceEvaluationSettings;`
- L192 _private member_ `TSharedPtr<FMetaHumanFilteredFaceTextureIndices> FilteredFaceTextureIndices;`
- L195 _private member_ `bool bActorWasModified = false;` — Keep track of whether the tool applied any changes
- L196 _private member_ `bool bSkinTextureWasModified = false;`
- L199 _private member_ `TSharedPtr<FMetaHumanCharacterIdentity::FState> FaceState;` — The face state of the actor when the tool was activated
- L202 _private member_ `FDelegateHandle RiggingStateChangedHandle;` — Delegate handle for the character's rigging state changed event.
- L205 _private member_ `FDelegateHandle PackageSavedHandle;` — Delegate handle for re-applying the hands pose after the character package is saved.
- L212 _private member_ `EMetaHumanCharacterCameraFrame PreShowHandsCameraFrame = EMetaHumanCharacterCameraFrame::Auto;` — Camera frame the character was focused on immediately before the show-hands pose was last enabled. Seeded at Setup with the frame the character had on tool activation, so a Shutdown that follows a show-hands activation can return the viewport to where the user started.
- L215 _private member_ `bool bShowHandsPoseActivated = false;` — True if SetShowHandsPose(true) ran during the session. Triggers frame restore on Shutdown.
- L218 _private member_ `TOptional<FTSTicker::FDelegateHandle> ShowHandsPoseFocusTickerHandle;` — Handle to the ticker that waits for the show-hands pose animation to finish before focusing the camera.
- L225 _private member_ `TWeakObjectPtr<UAnimSequence> PreShowHandsFaceAnim;` — Face/body animations that were driving the character immediately before the show-hands pose was applied. Cached so toggling the pose off restores the previous animation instead of leaving the character with no animation.
- L226 _private member_ `TWeakObjectPtr<UAnimSequence> PreShowHandsBodyAnim;`
- L229 _private member_ `bool bHasPreShowHandsAnim = false;` — True while PreShowHandsFaceAnim/PreShowHandsBodyAnim hold a valid pre-pose snapshot.

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSkinPropertyValueSetDelegate, const FPropertyChangedEvent& PropertyChangedEvent);` — Delegate that executes on EPropertyChangeType::ValueSet property change event, i.e. when a property value has finished being updated

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorSubTools.h` (Private)


#### class `UMetaHumanCharacterEditorSubToolsProperties`  
`class UMetaHumanCharacterEditorSubToolsProperties : public UInteractiveToolPropertySet`  
_L22-53_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- desc: SubTools property set to be used for a tool that is divided into subtools. Each subtool is represented as an UInteractiveToolPropertySet in the tool UMetaHumanCharacterSubToolsPropertySet::RegisterSubTools is used by a tool to register a map of commands to property sets. The commands are mapped to actions that activate each subtool, which also determines the checked state of a tool, i.e., which one is active
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSubToolActivated, UInteractiveToolPropertySet*, bool);`
- L29 _public member_ `FOnSubToolActivated OnSetSubToolPropertySetEnabledDelegate;`
- L31 _public prototype_ `void RegisterSubTools(const TMap<TSharedPtr<FUICommandInfo>, TObjectPtr<UInteractiveToolPropertySet>>& InSubTools, const TSharedPtr<FUICommandInfo> InDefaultCommand = nullptr);`
- L33 _public prototype_ `TArray<UInteractiveToolPropertySet*> GetSubToolsPropertySets() const;`
- L35 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetSubToolCommands() const;`
- L37 _public function_ `FName GetActiveSubToolName() const`
- L39 _public prototype_ `TSharedPtr<FUICommandList> GetCommandList() const;`
- L41 _public function_ `TSharedPtr<FUICommandInfo> GetDefaultCommand() const`
- L46 _private member_ `FName ActiveSubToolName;` — `UPROPERTY()`
- L48 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L50 _private member_ `TSharedPtr<FUICommandInfo> DefaultCommand;`
- L52 _private member_ `TMap<TSharedPtr<FUICommandInfo>, TObjectPtr<UInteractiveToolPropertySet>> SubToolsCommands;`

#### class `UMetaHumanCharacterEditorToolWithSubTools`  
`class UMetaHumanCharacterEditorToolWithSubTools : public USingleSelectionTool`  
_L62-99_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- desc: Subclass this to allow a tool to be split into subtools. Setup/Shutdown will take care of initializing the subtools object and enabling/disabling which tool is currently active. At the end of the subclass Setup implementation, call SubTools->RegisterSubTools() to register all available subtools for this tool.
- L67 _public function_ `UMetaHumanCharacterEditorSubToolsProperties* GetSubTools() const`
- L70 _public prototype_ `virtual void Setup() override;`
- L71 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L73 _public function_ `virtual bool HasCancel() const override`
- L78 _public function_ `virtual bool HasAccept() const override`
- L83 _public function_ `virtual bool CanAccept() const override`
- L93 _protected member_ `TObjectPtr<class UMetaHumanCharacterEditorSubToolsProperties> SubTools;` — `UPROPERTY()`

#### class `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
`class UMetaHumanCharacterEditorToolWithToolTargetsBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L105-138_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- desc: Subclass which simply implements the CanBuildTool function which is common to all subclasses
- L112 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& InSceneState) const override;`
- L118 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`
- L125 _protected prototype_ `static class UMetaHumanCharacter* GetMetaHumanCharacter(const FToolBuilderState& InSceneState);` — Returns the MetaHuman Character being edited for the given scene state, or nullptr if the scene state has no component whose owner implements UMetaHumanCharacterEditorActorInterface.
- L131 _protected prototype_ `static bool IsCharacterRigged(const FToolBuilderState& InSceneState);` — Returns true if the character being edited is rigged or rig-pending. Returns false when there is no character in the scene state.
- L137 _protected prototype_ `static bool IsCharacterRequestingHighResTextures(const FToolBuilderState& InSceneState);` — Returns true if the character being edited is currently requesting high-resolution source textures. Returns false when there is no character in the scene state.

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSubToolActivated, UInteractiveToolPropertySet*, bool);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorTextureMaterialOverrideTool.h` (Private)


#### class `UMetaHumanCharacterEditorTextureMaterialOverrideToolBuilder`  
`class UMetaHumanCharacterEditorTextureMaterialOverrideToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L18 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`

#### class `UMetaHumanCharacterEditorTextureMaterialOverrideToolProperties`  
`class UMetaHumanCharacterEditorTextureMaterialOverrideToolProperties : public UInteractiveToolPropertySet`  
_L27-50_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties for the Texture & Material Overrides tool. Allows the user to override skin textures and material parameters.
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTextureMaterialOverridePropertyValueSetDelegate, const FPropertyChangedEvent& PropertyChangedEvent);`
- L37 _public member_ `FOnTextureMaterialOverridePropertyValueSetDelegate OnPropertyValueSetDelegate;`
- L40 _public prototype_ `void CopyTo(FMetaHumanCharacterSkinSettings& OutSkinSettings) const;` — Copies texture override fields into the given skin settings, leaving other fields untouched
- L43 _public prototype_ `void CopyFrom(const FMetaHumanCharacterSkinSettings& InSkinSettings);` — Reads texture override fields from the given skin settings
- L46 _public member_ `FMetaHumanCharacterTextureMaterialOverrides TextureMaterialOverrides;` — `UPROPERTY(EditAnywhere, Category = "Texture & Material Overrides", meta = (ShowOnlyInnerProperties))`
- L49 _public member_ `bool bShowTeeth = false;` — `UPROPERTY(Transient, EditAnywhere, Category = "Viewport")`

#### class `UMetaHumanCharacterEditorTextureMaterialOverrideTool`  
`class UMetaHumanCharacterEditorTextureMaterialOverrideTool : public USingleSelectionTool`  
_L57-85_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool`
- desc: The Texture & Material Overrides Tool allows the user to override skin textures and material parameters on the MetaHuman Character.
- L63 _public function_ `UMetaHumanCharacterEditorTextureMaterialOverrideToolProperties* GetTextureMaterialOverrideToolProperties() const` — Get the tool properties
- L66 _public prototype_ `virtual void Setup() override;`
- L67 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L69 _public function_ `virtual bool HasCancel() const override`
- L70 _public function_ `virtual bool HasAccept() const override`
- L71 _public function_ `virtual bool CanAccept() const override`
- L75 _protected prototype_ `void UpdateTextureMaterialOverrideState() const;`
- L76 _protected prototype_ `void UpdateShowTeethState() const;`
- L82 _private member_ `TObjectPtr<UMetaHumanCharacterEditorTextureMaterialOverrideToolProperties> ToolProperties;` — `UPROPERTY()`
- L84 _private member_ `FMetaHumanCharacterSkinSettings PreviousSkinSettings;`

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTextureMaterialOverridePropertyValueSetDelegate, const FPropertyChangedEvent& PropertyChangedEvent);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorToolCommandChange.h` (Private)


#### class `FMetaHumanCharacterEditorToolCommandChange`  
`class FMetaHumanCharacterEditorToolCommandChange : public FToolCommandChange`  
_L15-33_
- inherits: `FToolCommandChange`
- desc: Tool Command change for undo/redo transactions.
- L18 _public function_ `FMetaHumanCharacterEditorToolCommandChange(TNotNull<UInteractiveToolManager*> InToolManager) : ToolManager`
- L24 _public function_ `virtual bool HasExpired(UObject* InObject) const override`
- L32 _protected member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager;`

#### class `FMetaHumanCharacterEditorFaceEvaluationSettingsCommandChange`  
`class FMetaHumanCharacterEditorFaceEvaluationSettingsCommandChange : public FMetaHumanCharacterEditorToolCommandChange`  
_L41-66_
- inherits: `FMetaHumanCharacterEditorToolCommandChange`
- desc: Base class for MetaHuman Character command change for undo/redo transactions.
- L44 _public function_ `FMetaHumanCharacterEditorFaceEvaluationSettingsCommandChange( TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterFaceEvaluationSettings& InOldSettings, FOnSettingsUpdateDelegate InOnSettingsUpdateDelegate, TNotNull<UInteractiveToolManager*> InToolManager) : FMetaHumanCharacterEditorToolCommandChange(InToolManager) , OldSettings`
- L57 _public prototype_ `virtual void Apply(UObject* InObject) override;`
- L58 _public prototype_ `virtual void Revert(UObject* InObject) override;`
- L62 _private member_ `FMetaHumanCharacterFaceEvaluationSettings OldSettings;`
- L63 _private member_ `FMetaHumanCharacterFaceEvaluationSettings NewSettings;`
- L65 _private member_ `FOnSettingsUpdateDelegate OnSettingsUpdateDelegate;`

#### class `FMetaHumanCharacterEditorBodyToolCommandChange`  
`class FMetaHumanCharacterEditorBodyToolCommandChange : public FToolCommandChange`  
_L71-106_
- inherits: `FToolCommandChange`
- desc: Body Tool Command change for undo/redo transactions.
- L74 _public function_ `FMetaHumanCharacterEditorBodyToolCommandChange( TSharedRef<FMetaHumanCharacterBodyIdentity::FState> InOldState, TSharedRef<FMetaHumanCharacterBodyIdentity::FState> InNewState, TNotNull<UInteractiveToolManager*> InToolManager) : OldState(InOldState) , NewState(InNewState) , ToolManager(InToolManager)`
- L84 _public function_ `virtual void Apply(UObject* Object) override`
- L90 _public function_ `virtual void Revert(UObject* Object) override`
- L96 _public function_ `virtual bool HasExpired(UObject* InObject) const override`
- L102 _private member_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> OldState;`
- L103 _private member_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> NewState;`
- L105 _private member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager;`

#### class `FMetaHumanCharacterEditorStateCommandChange`  
`class FMetaHumanCharacterEditorStateCommandChange : public FMetaHumanCharacterEditorToolCommandChange`  
_L112-157_
- inherits: `FMetaHumanCharacterEditorToolCommandChange`
- desc: Combined body and face command change for undo/redo transactions. Used when both body and face states change together as a single undoable operation (e.g. mesh conform, blend both types).
- L115 _public function_ `FMetaHumanCharacterEditorStateCommandChange( TNotNull<UInteractiveToolManager*> InToolManager, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InOldBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InOldFaceState, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InNewBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InNewFaceState, FString InDescription) : FMetaHumanCharacterEditorToolCommandChange(InToolManager) , OldBodyState(InOldBodyState) , OldFaceState(InOldFaceState) , NewBodyState(InNewBodyState) , NewFaceState(InNewFaceState) , Description(InDescription)`
- L130 _public function_ `virtual void Apply(UObject* InObject) override`
- L135 _public function_ `virtual void Revert(UObject* InObject) override`
- L140 _public function_ `virtual FString ToString() const override`
- L143 _private function_ `void ApplyState(UObject* InObject, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState, TSharedRef<const FMetaHumanCharacterIdentity::FState> InFaceState)`
- L152 _private member_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> OldBodyState;`
- L153 _private member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> OldFaceState;`
- L154 _private member_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> NewBodyState;`
- L155 _private member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> NewFaceState;`
- L156 _private member_ `FString Description;`

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSettingsUpdateDelegate, TWeakObjectPtr<UInteractiveToolManager>, const FMetaHumanCharacterFaceEvaluationSettings&);`
- L36 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSettingsUpdateDelegate, TWeakObjectPtr<UInteractiveToolManager>, const FMetaHumanCharacterFaceEvaluationSettings&);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorToolTargetUtil.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ToolTarget` (scope `UE`)
- L18 _prototype_ `UMetaHumanCharacter* GetTargetMetaHumanCharacter(UToolTarget* InTarget);` (scope `UE::ToolTarget`) — Returns the MetaHuman Character asset backing a tool target, or nullptr if there is no such asset

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Tools/MetaHumanCharacterEditorWardrobeTools.h` (Private)


#### enum `EMetaHumanCharacterWardrobeEditingTool`  
`enum class EMetaHumanCharacterWardrobeEditingTool : uint8`  
_L17-20_
- reflection: `UENUM()`
- L19 _public enumerator_ `Wardrobe`

#### class `UMetaHumanCharacterEditorWardrobeToolBuilder`  
`class UMetaHumanCharacterEditorWardrobeToolBuilder : public UMetaHumanCharacterEditorToolWithToolTargetsBuilder`  
_L23-35_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterEditorToolWithToolTargetsBuilder`
- L30 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& InSceneState) const override;`
- L34 _public member_ `EMetaHumanCharacterWardrobeEditingTool ToolType = EMetaHumanCharacterWardrobeEditingTool::Wardrobe;` — `UPROPERTY()`

#### class `UMetaHumanCharacterEditorWardrobeToolProperties`  
`class UMetaHumanCharacterEditorWardrobeToolProperties : public UInteractiveToolPropertySet`  
_L41-51_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: The Detail Customization for this class contains the wardrobe editing UI
- L47 _public member_ `TObjectPtr<UMetaHumanCollection> Collection;` — `UPROPERTY()`
- L50 _public member_ `TObjectPtr<UMetaHumanCharacter> Character;` — `UPROPERTY()`

#### class `UMetaHumanCharacterEditorWardrobeTool`  
`class UMetaHumanCharacterEditorWardrobeTool : public USingleTargetWithSelectionTool`  
_L57-82_
- reflection: `UCLASS()`
- inherits: `USingleTargetWithSelectionTool`
- desc: The Wardrobe Tool allows the user to customize items selected in the Costume tab.
- L63 _public function_ `UMetaHumanCharacterEditorWardrobeToolProperties* GetWardrobeToolProperties() const` — Get the Wardrobe Tool properties.
- L66 _public prototype_ `virtual void Setup() override;`
- L67 _public prototype_ `virtual void Shutdown(EToolShutdownType InShutdownType) override;`
- L69 _public function_ `virtual bool HasCancel() const override`
- L70 _public function_ `virtual bool HasAccept() const override`
- L71 _public function_ `virtual bool CanAccept() const override`
- L75 _protected prototype_ `void OnWardrobePathsChanged();`
- L78 _protected member_ `TObjectPtr<UMetaHumanCharacterEditorWardrobeToolProperties> PropertyObject;` — `UPROPERTY()`
- L80 _protected member_ `FDelegateHandle WardrobePathChangedUserSettings;`
- L81 _protected member_ `FDelegateHandle WardrobePathChangedCharacter;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Viewport/SMetaHumanCharacterEditor2DViewportOverlay.h` (Private)


#### class `SMetaHumanCharacterEditor2DViewportOverlay`  
`class SMetaHumanCharacterEditor2DViewportOverlay : public SCompoundWidget`  
_L12-40_
- inherits: `SCompoundWidget`
- desc: Widget used as an overlay for the 2D viewport in MetaHuman Character Editor.
- L16 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditor2DViewportOverlay)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(const FSlateBrush*, ImageBrush) SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The text to be displayed as the label for the overlay.
- L36 _private prototype_ `const FSlateBrush* GetOverlayBorderImageBrush() const;` — Gets the border image brush used for the overlay.
- L39 _private member_ `TSharedPtr<SBorder> OverlayBorder;` — The border widget used to display the overlay image.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Viewport/SMetaHumanCharacterEditorViewport.h` (Private)


#### class `SMetaHumanCharacterEditorViewport`  
`class SMetaHumanCharacterEditorViewport : public SAssetEditorViewport, public FGCObject`  
_L17-145_
- inherits: `SAssetEditorViewport,FGCObject`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);` — Constructor
- L25 _public prototype_ `virtual ~SMetaHumanCharacterEditorViewport();` — Destructor - destroys the scene capture component so it doesn't outlive its world.
- L28 _public prototype_ `TSharedRef<class FMetaHumanCharacterViewportClient> GetMetaHumanCharacterEditorViewportClient() const;` — Returns a reference to the viewport client that controls this viewport
- L31 _public prototype_ `TSharedRef<SMetaHumanOverlayWidget<STrackerImageViewer>> GetTrackerImageViewer() const;` — Returns a reference to the STrackerImageViewer we are controlling
- L34 _public prototype_ `UTextureRenderTarget2D* GetOrCreateTrackingTexture(UObject* WorldContextObject, UTexture* SourceTexture, const FIntPoint& SourceSize, const FIntPoint& TargetSize);` — Gets or creates a render target texture to be used for tracking the viewport in the 2D View Overlay widget
- L37 _public prototype_ `void SetTrackerImageTexture(UTexture* InTexture, const FIntPoint& InImageSize);` — Sets the texture to be displayed in the tracker image viewer overlay
- L40 _public function_ `FGeometry GetCurrentViewportGeometry() const` — Returns the current geometry of the viewport widget
- L43 _public function_ `void SetViewportModeVisible(TAttribute<bool> IsVisible)` — Sets the visibility of the viewport mode toolbar buttons
- L46 _public prototype_ `bool IsViewportModeVisible() const;` — True if the viewport mode toolbar buttons are visible
- L49 _public function_ `void Toggle2DViewOverlay()` — Toggles the visibility state of the 2D View Overlay widget
- L52 _public function_ `bool Is2DViewOverlayEnabled() const` — Gets the visibility state of the 2D View Overlay widget
- L55 _public prototype_ `void Update2DViewportOverlay(bool bEnable2DView);` — Updates the 2D View Overlay widget based on the current state of the viewport
- L58 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L59 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> InOverlay) override;`
- L60 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L61 _public prototype_ `virtual void BindCommands() override;`
- L65 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L66 _public prototype_ `virtual FString GetReferencerName() const override;`
- L70 _public member_ `FOnSceneViewportResize OnViewportSizeChangedDelegate;` — Delegate used to trigger when the viewport size changes, which is used to update the tracker image viewer
- L73 _public member_ `FIsSelected OnShouldDrawTrackingPointsDelegate;` — Delegate used to determine whether or not to draw the tracking points overlay
- L76 _public member_ `FOnBooleanValueChanged OnTrackerImageVisibilityChangedDelegate;` — Delegate used to trigger when the visibility of the tracker image viewer changes, which is used to update the tracker image viewer
- L79 _public member_ `TSharedPtr<class SComboButton> CustomEnvironmentSelectionBox;` — A reference to the custom environment selection combo button in the viewport toolbar
- L84 _private prototype_ `void InitializeSceneCaptureComponent();` — Initializes the scene capture component used to track the viewport for the 2D View Overlay widget
- L87 _private prototype_ `void CaptureCurrentView();` — Captures the current view of the viewport
- L90 _private prototype_ `FBox2D ComputeTextureFitRect(const FIntPoint& SourceSize, const FIntPoint& TargetSize) const;` — Computes the rectangle to fit the source texture into the target size while maintaining aspect ratio
- L93 _private prototype_ `UInteractiveToolManager* GetToolManager() const;` — Returns a pointer to the InteractiveToolManager from the current ToolsContext, or nullptr if it is not available
- L96 _private prototype_ `void UpdateCurrentViewportImageBrush(UTexture* InTexture, const FIntPoint& InImageSize);` — Updates the brush used to draw the current viewport capture in the 2D View Overlay widget
- L99 _private prototype_ `void UpdateTrackerImageBrush(UTexture* InTexture, const FIntPoint& InImageSize);` — Updates the brush used to draw the tracker image viewer overlay with the given texture and image size
- L102 _private prototype_ `FText Get2DViewportModeOverlayLabelText() const;` — Gets the label text for the 2D View Overlay widget based on the current state of the viewport
- L105 _private prototype_ `const FSlateBrush* Get2DViewportModeOverlayImageBrush() const;` — Gets the brush used to draw the current viewport capture in the 2D View Overlay widget
- L108 _private prototype_ `EVisibility Get2DViewportModeOverlayVisibility() const;` — Gets the visibility of the 2D View Overlay widget
- L111 _private prototype_ `FReply On2DViewportModeOverlayClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the 2D View Overlay widget is clicked, toggles the visibility of the overlay
- L114 _private prototype_ `void FocusOnFrame(EMetaHumanCharacterCameraFrame FrameToFocus);` — Focuses the camera on the given frame
- L117 _private prototype_ `bool IsCameraFrameChecked(EMetaHumanCharacterCameraFrame Frame) const;` — Returns true if the given camera frame is currently selected in the viewport
- L120 _private prototype_ `bool ShouldDrawTrackingPoints() const;` — Returns true if the tracking points overlay should be drawn
- L123 _private member_ `TSharedPtr<SMetaHumanOverlayWidget<STrackerImageViewer>> TrackerImageViewer;` — A reference to the tracker image viewer overlay
- L126 _private member_ `TSharedPtr<FSlateBrush> CurrentViewportBrush;` — The brush used to draw the current viewport capture in the 2D View Overlay widget
- L129 _private member_ `TSharedPtr<FSlateBrush> TrackerImageViewerBrush;` — The brush used to draw the tracker image viewer overlay
- L132 _private member_ `TObjectPtr<class USceneCaptureComponent2D> SceneCaptureComponent;` — A pointer to the scene capture component used for tracking the viewport
- L135 _private member_ `TObjectPtr<class UTextureRenderTarget2D> TrackingRenderTarget;` — A pointer to the render target used to capture the viewport for the 2D View Overlay widget
- L138 _private member_ `TAttribute<bool> IsViewportModeVisibleAttribute;` — An attribute used to determine the visibility of the viewport mode toolbar buttons
- L141 _private member_ `FGeometry CurrentViewportGeometry;` — Holds the current geometry of the widget. Used to trigger the ViewportSizeChangedDelegate if the size changes
- L144 _private member_ `bool bIs2DViewOverlayEnabled = true;` — True if the 2D View Overlay widget is enabled

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Viewport/SMetaHumanCharacterEditorViewportAnimationBar.h` (Private)


#### class `SMetaHumanCharacterEditorViewportAnimationBar`  
`class SMetaHumanCharacterEditorViewportAnimationBar: public SCompoundWidget`  
_L7-41_
- inherits: `SCompoundWidget`
- L10 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorViewportAnimationBar)`
- L11 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FMetaHumanCharacterViewportClient>, AnimationBarViewportClient) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L16 _public prototype_ `TSharedRef<SWidget> MakeAnimationBarScrubber();`
- L18 _public member_ `TSharedPtr<class FMetaHumanCharacterViewportClient> ViewportClient;`
- L21 _private prototype_ `class AMetaHumanInvisibleDrivingActor* GetInvisibleDrivingActor() const;`
- L22 _private member_ `bool bAnimationPlaying;`
- L25 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;` — ScrubWidget
- L26 _private prototype_ `float GetScrubValue() const;`
- L27 _private prototype_ `uint32 GetNumberOfKeys() const;`
- L28 _private prototype_ `float GetSequenceLength() const;`
- L29 _private prototype_ `bool IsScrubWidgetEnabled() const;`
- L30 _private prototype_ `EVisibility WarningVisibility() const;`
- L32 _private prototype_ `void OnValueChanged(float NewValue);`
- L33 _private prototype_ `void OnBeginSliderMovement();`
- L34 _private prototype_ `void OnEndSliderMovement(float NewValue);`
- L37 _private prototype_ `FReply OnClick_Forward();` — Notifiers
- L38 _private prototype_ `FReply OnClick_Backward();`
- L40 _private prototype_ `TSharedRef<SWidget> OnCreateStopButtonWidget();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Viewport/SMetaHumanCharacterEditorViewportToolBar.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `FToolMenuEntry Create3DViewToggle();`
- L8 _prototype_ `FToolMenuEntry Create2DViewFacialTracingToggle();`
- L9 _prototype_ `FToolMenuEntry Create2DViewOverlayVisibilityToggle();`
- L10 _prototype_ `FToolMenuEntry CreateEnvironmentSubmenu();`
- L11 _prototype_ `FToolMenuEntry CreateCameraSelectionSubmenu();`
- L12 _prototype_ `FToolMenuEntry CreateLODSubmenu();`
- L13 _prototype_ `FToolMenuEntry CreateRenderingQualitySubmenu();`
- L14 _prototype_ `FToolMenuEntry CreatePreviewMaterialSubmenu();`
- L15 _prototype_ `FToolMenuEntry CreateViewportOverlayToggle();`
- L16 _prototype_ `FToolMenuEntry CreateDebugSubmenu();`
- L17 _prototype_ `FToolMenuEntry CreateViewModesSubmenu();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorBlendToolView.h` (Private)


#### class `SMetaHumanCharacterEditorBlendToolView`  
`class SMetaHumanCharacterEditorBlendToolView : public SMetaHumanCharacterEditorToolView`  
_L17-102_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: View for displaying the Blend Tool in the MetahHumanCharacter editor
- L24 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorBlendToolView)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorMeshBlendTool* InTool);`
- L33 _public prototype_ `virtual const FName& GetToolViewNameID() const override;`
- L34 _public prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L35 _public prototype_ `virtual void MakeToolView() override;`
- L36 _public prototype_ `virtual void OnPostEditChangeProperty(FProperty* Property, bool bIsInteractive) override;`
- L40 _public prototype_ `FMetaHumanCharacterAssetViewsPanelStatus GetAssetViewsPanelStatus() const;` — Gets the status parameters of the asset views panel.
- L43 _public prototype_ `void SetAssetViewsPanelStatus(const FMetaHumanCharacterAssetViewsPanelStatus& Status);` — Sets the status of the asset views panel according to the given parameters.
- L46 _public prototype_ `TArray<FMetaHumanCharacterAssetViewStatus> GetAssetViewsStatusArray() const;` — Gets an array with the status parameters of all the asset views in the panel.
- L49 _public prototype_ `void SetAssetViewsStatus(const TArray<FMetaHumanCharacterAssetViewStatus>& StatusArray);` — Sets the status of the asset views in the panel according to the given array.
- L52 _public prototype_ `void OnBlendToolItemContentSet(const FAssetData& InAssetData, int32 InItemIndex);` — Called when an item's content is set in the blend tool panel.
- L55 _public prototype_ `void OnBlendToolItemContentDeleted(int32 InItemIndex);` — Called when an item's content is deleted in the blend tool panel.
- L58 _public prototype_ `void OnBlendToolItemActivated(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when an item is double clicked in the presets of the blend tool panel.
- L61 _public prototype_ `void OnBlendToolItemApplyHeadOnly(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when "Apply Head Only" is selected from an item's context menu in the blend tool panel.
- L64 _public prototype_ `void OnBlendToolItemApplyBodyOnly(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when "Apply Body Only" is selected from an item's context menu in the blend tool panel.
- L68 _private prototype_ `TSharedRef<SWidget> CreateBlendToolViewBlendPanelSection();` — Creates the section widget for showing the Presets properties.
- L71 _private prototype_ `TSharedRef<SWidget> CreateParametersViewSection();` — Creates the parameters section (manipulator size).
- L74 _private prototype_ `TSharedRef<SWidget> CreateHeadParametersViewSection();` — Creates the section widget for showing the head blend settings.
- L77 _private prototype_ `TSharedRef<SWidget> CreateBodyParametersViewSection();` — Creates the section widget for showing the body blend settings.
- L80 _private prototype_ `bool OnFilterAddAssetDataToAssetView(const FAssetData& AssetData) const;` — Called to filter assets added to the asset view, e.g. to exclude fixed body types.
- L83 _private prototype_ `void OnOverrideItemThumbnailBrush(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — Called to override the item thumbnail brush.
- L86 _private prototype_ `EVisibility GetBlendSubToolVisibility() const;` — Gets the visibility for this tool.
- L89 _private prototype_ `EVisibility GetFixedBodyWarningVisibility() const;` — Gets the visibility for the fixed body warning.
- L92 _private prototype_ `FReply OnPerformParametricFitButtonClicked() const;` — Perform parameteric fit for fixed body types
- L95 _private prototype_ `FReply OnResetNeckButtonClicked() const;` — Revert the neck region of the head based on the body
- L98 _private member_ `TSharedPtr<SMetaHumanCharacterEditorBlendToolPanel> BlendToolPanel;` — Reference to the Blend Tool panel, used for handling preset blending.
- L101 _private member_ `static FName AssetsSlotName;` — Name identifier for the slot where virtual assets from the body blend tool are stored.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorBodyModelToolView.h` (Private)


#### class `SMetaHumanCharacterEditorBodyModelToolView`  
`class SMetaHumanCharacterEditorBodyModelToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L14-114_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Body Model Tool in the MetaHumanCharacter editor
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorToolView)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorToolWithSubTools* InTool);`
- L29 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L30 _protected prototype_ `virtual void MakeToolView() override;`
- L34 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L35 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L40 _private prototype_ `UInteractiveToolPropertySet* GetParametricProperties() const;` — Gets the body model parametric subtool properties.
- L43 _private prototype_ `UInteractiveToolPropertySet* GetFixedCompatibilityProperties() const ;` — Gets the body model fixed compatibility subtool properties.
- L46 _private prototype_ `void MakeParametricSubToolView();` — Makes the parametric subtool view.
- L49 _private prototype_ `void MakeParametricFixedWarningView();` — Makes the parametric subtool warning view.
- L52 _private prototype_ `void MakeFixedCompatibilitySubToolView();` — Makes the fixed compatibility subtool view.
- L55 _private prototype_ `void MakeFixedCompatibilityWarningView();` — Makes the fixed compatibility subtool warning view.
- L58 _private prototype_ `void OnPropertySetsModified();` — Called when the property set of this tool has been modified.
- L61 _private prototype_ `TSharedRef<SWidget> CreateParametricSubToolViewSection();` — Creates the section widget for showing the body parametric properties.
- L64 _private prototype_ `TSharedRef<SWidget> CreateParametricConstraintsPanel(const FText& Label, const TArray<FName>& ConstraintNames, bool bDiagnosticsView = false);` — Creates the panel widget for an array of constraint names.
- L71 _private prototype_ `void OnBeginConstraintEditing();` — Called when the user starts dragging a constraint slider. When they release the slider, OnParametricConstraintsChanged will be called with bInCommit = true.
- L74 _private prototype_ `void OnParametricConstraintsChanged(bool bInCommit);` — On parametric constraints changed
- L77 _private prototype_ `FReply OnResetButtonClicked() const;` — On reset parametric clicked
- L80 _private prototype_ `FReply OnPerformParametricFitButtonClicked() const;` — On perform parametric fit clicked
- L83 _private prototype_ `TSharedRef<SWidget> CreateFixedCompatibilitySubToolViewSection();` — Creates the section widget for showing the fixed compatibility properties.
- L86 _private prototype_ `EVisibility GetParametricSubToolViewVisibility() const;` — Gets the visibility for the parametric subtool view.
- L89 _private prototype_ `EVisibility GetParametricSubToolFixedWarningVisibility() const;` — Gets the visibility for the parametric fixed warning.
- L92 _private prototype_ `EVisibility GetFixedCompatibilitySubToolViewVisibility() const;` — Gets the visibility for the fixed compatibility subtool view.
- L95 _private prototype_ `EVisibility GetFixedCompatibilitySubToolWarningVisibility() const;` — Gets the visibility for the fixed compatibility warning about no optional content.
- L98 _private member_ `TSharedPtr<SVerticalBox> ParametricSubToolView;` — Reference to the parametric subtool view.
- L101 _private member_ `TSharedPtr<SVerticalBox> ParametricFixedWarningView;` — Reference to the parametric fixed warning view.
- L104 _private member_ `TSharedPtr<SVerticalBox> FixedCompatibilitySubToolView;` — Reference to the fixed compatibility subtool view.
- L107 _private member_ `TSharedPtr<SVerticalBox> FixedCompatibilityWarningView;` — Reference to the fixed compatibilit warning view.
- L110 _private member_ `TSharedPtr<SMetaHumanCharacterEditorFixedCompatibilityPanel> FixedCompatibilityPanel;` — Reference to the fixed compatibility panel.
- L113 _private member_ `bool bOptionalMetaHumanContentInstalled = false;` — Flag to store if optional content is installed

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorCostumeToolView.h` (Private)


#### class `SMetaHumanCharacterEditorCostumeToolView`  
`class SMetaHumanCharacterEditorCostumeToolView : public SMetaHumanCharacterEditorToolView , public FSelfRegisteringEditorUndoClient`  
_L13-89_
- inherits: `SMetaHumanCharacterEditorToolView,FSelfRegisteringEditorUndoClient`
- desc: View for displaying the Costume Tool in the MetahHumanCharacter editor
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorCostumeToolView)`
- L25 _public prototype_ `virtual ~SMetaHumanCharacterEditorCostumeToolView() override;` — Destructor
- L28 _public prototype_ `void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorCostumeTool* InTool);` — Constructs the widget
- L32 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L33 _protected prototype_ `virtual void MakeToolView() override;`
- L37 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L38 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _private prototype_ `TSharedRef<SWidget> CreateCostumeToolViewWarningSection();` — Creates the section widget for showing the Warning panel.
- L46 _private prototype_ `TSharedRef<SWidget> CreateCostumeToolViewGroomsSection();` — Creates the section widget for showing the Grooms properties.
- L49 _private prototype_ `TSharedRef<SWidget> CreateCostumeToolViewOutfitClothingSection();` — Creates the section widget for showing the Outfit Clothing properties.
- L52 _private prototype_ `TSharedRef<SWidget> CreateCostumeToolViewSkeletalMeshSection();` — Creates the section widget for showing the Skeletal Mesh properties.
- L55 _private prototype_ `void MakeCostumeItemsBoxes();` — Makes the costume item boxes content, based on the current wardrobe selection.
- L58 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Called when a costume item property has been changed.
- L61 _private prototype_ `EVisibility GetWarningVisibility() const;` — Gets the visibility of the warning panel
- L64 _private prototype_ `EVisibility GetGroomsBoxVisibility() const;` — Gets the visibility of the grooms container box.
- L67 _private prototype_ `EVisibility GetOutfitClothingBoxVisibility() const;` — Gets the visibility of the outfit clothing container box.
- L70 _private prototype_ `EVisibility GetSkeletalMeshBoxVisibility() const;` — Gets the visibility of the skeletal mesh container box.
- L73 _private prototype_ `bool IsNameEnumValue(UEnum* EnumPtr, const FName& NameToCheck) const;` — True if the given name is one of the given enum's values.
- L76 _private prototype_ `void Refresh();` — Refreshes the panel asset views widgets.
- L79 _private member_ `TUniquePtr<FScopedTransaction> PropertyChangeTransaction;` — Unique pointer to the property change transaction.
- L82 _private member_ `TSharedPtr<SVerticalBox> GroomsBox;` — Reference to the container box for grooms.
- L85 _private member_ `TSharedPtr<SVerticalBox> OutfitClothingBox;` — Reference to the container box for outfit clothing.
- L88 _private member_ `TSharedPtr<SVerticalBox> SkeletalMeshesBox;` — Reference to the container box for skeletal meshes.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorExportToolView.h` (Private)


#### class `SMetaHumanCharacterEditorExportToolView`  
`class SMetaHumanCharacterEditorExportToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L13-57_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: Generic view for all Export tools in the MetaHuman Character editor
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorExportToolView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorExportToolBase* InTool);`
- L26 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L27 _protected prototype_ `virtual void MakeToolView() override;`
- L31 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L32 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L38 _private prototype_ `TSharedRef<SWidget> CreateExportToolViewDetailsViewSection();` — Creates the details view section for the export properties.
- L41 _private prototype_ `TSharedRef<SWidget> CreateExportToolViewExportSection();` — Creates the section widget for showing the Export button.
- L44 _private prototype_ `bool IsExportButtonEnabled() const;` — True if the Export button is enabled.
- L47 _private prototype_ `FReply OnExportButtonClicked() const;` — Called when the Export button is clicked.
- L50 _private prototype_ `EVisibility GetWarningVisibility() const;` — Gets the warning message visibility.
- L53 _private member_ `mutable FText ExportErrorMsg;` — The optional error message displayed when export cannot proceed.
- L56 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Reference to the Details View that displays export properties.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorExternalImportToolView.h` (Private)


#### class `SMetaHumanCharacterEditorExternalImportToolView`  
`class SMetaHumanCharacterEditorExternalImportToolView : public SMetaHumanCharacterEditorImportToolView`  
_L17-41_
- inherits: `SMetaHumanCharacterEditorImportToolView`
- desc: Host wrapper widget for externally-contributed import tools. Derives from the abstract SMetaHumanCharacterEditorImportToolView so it participates in the standard import tool view hierarchy (scroll-offset save/restore, toolkit guards) without inheriting FNotifyHook or any internal import tool assumptions. Created by FMetaHumanCharacterEditorModeToolkit::CreateToolView() when it detects a tool contributed via IMetaHumanImportToolFeature.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorExternalImportToolView)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SWidget> InContent, UMetaHumanCharacterExternalImportTool* InExtTool);`
- L27 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L28 _protected prototype_ `virtual void MakeToolView() override;`
- L32 _protected prototype_ `virtual bool IsImportButtonEnabled() const override;`
- L33 _protected prototype_ `virtual FReply OnImportButtonClicked() override;`
- L34 _protected prototype_ `virtual FText GetWarningText() const override;`
- L39 _private member_ `TSharedPtr<SWidget> ExternalContent;`
- L40 _private member_ `TWeakObjectPtr<UMetaHumanCharacterExternalImportTool> ExtTool;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorEyesToolView.h` (Private)


#### class `SMetaHumanCharacterEditorEyesToolView`  
`class SMetaHumanCharacterEditorEyesToolView : public SMetaHumanCharacterEditorToolView`  
_L15-62_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: View for displaying the Eyes Tool in the MetahHumanCharacter editor
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorEyesToolView)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorEyesTool* InTool);`
- L29 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L30 _protected prototype_ `virtual void MakeToolView() override;`
- L35 _private prototype_ `TSharedRef<SWidget> CreateEyesToolViewPresetsSection();` — Creates the section widget for showing the Presets properties.
- L38 _private prototype_ `TSharedRef<SWidget> CreateEyeSelectionSection();` — Creates the section widget for showing the eye selction
- L41 _private prototype_ `TSharedRef<SWidget> CreateEyesToolViewIrisSection();` — Creates the section widget for showing the Iris properties.
- L44 _private prototype_ `TSharedRef<SWidget> CreateEyeToolViewPupilSection();` — Creates the section widget for showing the Pupil properties
- L47 _private prototype_ `TSharedRef<SWidget> CreateEyeCorneaViewSection();` — Creates the section widget for showing the Cornea properties
- L50 _private prototype_ `TSharedRef<SWidget> CreateEyesToolViewScleraSection();` — Creates the section widget for showing the Sclera properties.
- L53 _private prototype_ `const FSlateBrush* GetIrisSectionBrush(uint8 InItem);` — Gets the Iris section brush according to the given item value.
- L58 _private member_ `TArray<FEyePresetItemPtr> PresetItems;` — List of preset items to display in the Preset Tile View
- L61 _private member_ `TSharedPtr<SMetaHumanCharacterEditorTileView<EMetaHumanCharacterEyesIrisPattern>> IrisPatternTileView;` — Iris Pattern Tile View Widget.

#### Free symbols / members of external scopes

- L9 _typedef_ `using FEyePresetItemPtr = TSharedPtr<struct FEyePresetItem>;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorFaceToolView.h` (Private)


#### class `SMetaHumanCharacterEditorFaceToolView`  
`class SMetaHumanCharacterEditorFaceToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L14-51_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the face scult tool in the MetahHumanCharacter editor
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorFaceToolView)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorFaceSculptTool* InTool);`
- L29 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L33 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L34 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L39 _protected prototype_ `TSharedRef<SWidget> CreateManipulatorsViewSection();` — Creates the section widget for showing the manipulator properties.
- L42 _protected prototype_ `TSharedRef<SWidget> CreateHeadParametersViewSection();` — Creates the section widget for showing the head parameter properties.
- L47 _private prototype_ `FReply OnResetButtonClicked() const;` — On reset clicked
- L50 _private prototype_ `FReply OnResetNeckButtonClicked() const;` — On reset neck clicked

#### class `SMetaHumanCharacterEditorFaceSculptToolView`  
`class SMetaHumanCharacterEditorFaceSculptToolView : public SMetaHumanCharacterEditorFaceToolView`  
_L54-72_
- inherits: `SMetaHumanCharacterEditorFaceToolView`
- desc: View for displaying the face sculpt tool in the MetahHumanCharacter editor
- L58 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorFaceSculptToolView)`
- L61 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorFaceSculptTool* InTool);`
- L68 _protected prototype_ `virtual void MakeToolView() override;`

#### class `SMetaHumanCharacterEditorFaceMoveToolView`  
`class SMetaHumanCharacterEditorFaceMoveToolView : public SMetaHumanCharacterEditorFaceToolView`  
_L76-96_
- inherits: `SMetaHumanCharacterEditorFaceToolView`
- desc: View for displaying the face move tool in the MetahHumanCharacter editor
- L80 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorFaceMoveToolView)`
- L83 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorFaceMoveTool* InTool);`
- L90 _protected prototype_ `virtual void MakeToolView() override;`
- L94 _private prototype_ `TSharedRef<SWidget> CreateGizmoSelectionSection();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorHeadMaterialsToolView.h` (Private)


#### class `SMetaHumanCharacterEditorHeadMaterialsToolView`  
`class SMetaHumanCharacterEditorHeadMaterialsToolView : public SMetaHumanCharacterEditorToolView`  
_L14-71_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: View for displaying the HeadModel Tool in the MetahHumanCharacter editor
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorHeadMaterialsToolView)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorHeadMaterialsTool* InTool);`
- L28 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L29 _protected prototype_ `virtual void MakeToolView() override;`
- L34 _private prototype_ `UInteractiveToolPropertySet* GetEyelashesProperties() const;` — Gets the Head Model Eyelashes subtool properties.
- L37 _private prototype_ `UInteractiveToolPropertySet* GetTeethProperties() const ;` — Gets the Head Model Teeth subtool properties.
- L40 _private prototype_ `void MakeEyelashesSubToolView();` — Makes the Eyelashes subtool view.
- L43 _private prototype_ `void MakeTeethSubToolView();` — Makes the Teeth subtool view.
- L46 _private prototype_ `void OnPropertySetsModified();` — gets called when the subtool changes
- L49 _private prototype_ `TSharedRef<SWidget> CreateEyelashesSubToolViewMaterialSection();` — Creates the section widget for showing the Eyelashes material properties.
- L52 _private prototype_ `TSharedRef<SWidget> CreateTeethSubToolViewMaterialsSection();` — Creates the section widget for showing the Teeth material properties.
- L55 _private prototype_ `const FSlateBrush* GetEyelashesSectionBrush(uint8 InItem);` — Gets the Eyelashes section brush according to the given item value.
- L58 _private prototype_ `const FSlateBrush* GetTeethSectionBrush(uint8 InItem);` — Gets the Teeth section brush according to the given item value.
- L61 _private prototype_ `EVisibility GetEyelashesSubToolViewVisibility() const;` — Gets the visibility for the Eyelashes subtool view.
- L64 _private prototype_ `EVisibility GetTeethSubToolViewVisibility() const;` — Gets the visibility for the Teeth subtool view.
- L67 _private member_ `TSharedPtr<SVerticalBox> EyelashesSubToolView;` — Reference to the Eyelashes subtool view.
- L70 _private member_ `TSharedPtr<SVerticalBox> TeethSubToolView;` — Reference to the Teeth subtool view.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorHeadModelToolView.h` (Private)


#### class `SMetaHumanCharacterEditorHeadModelToolView`  
`class SMetaHumanCharacterEditorHeadModelToolView : public SMetaHumanCharacterEditorToolView`  
_L14-89_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: View for displaying the HeadModel Tool in the MetahHumanCharacter editor
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorHeadModelToolView)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorHeadModelTool* InTool);`
- L28 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L29 _protected prototype_ `virtual void MakeToolView() override;`
- L34 _private prototype_ `UInteractiveToolPropertySet* GetEyelashesProperties() const;` — Gets the Head Model Eyelashes subtool properties.
- L37 _private prototype_ `UInteractiveToolPropertySet* GetTeethProperties() const ;` — Gets the Head Model Teeth subtool properties.
- L40 _private prototype_ `void MakeEyelashesSubToolView();` — Makes the Eyelashes subtool view.
- L43 _private prototype_ `void MakeTeethSubToolView();` — Makes the Teeth subtool view.
- L46 _private prototype_ `void OnPropertySetsModified();` — gets called when the subtool changes
- L49 _private prototype_ `TSharedRef<SWidget> CreateEyelashesSubToolViewStyleSection();` — Creates the section widget for showing the Eyelashes style properties.
- L52 _private prototype_ `TSharedRef<SWidget> CreateEyelashesSubToolViewMaterialSection();` — Creates the section widget for showing the Eyelashes material properties.
- L55 _private prototype_ `TSharedRef<SWidget> CreateTeethSubToolViewParametersSection();` — Creates the section widget for showing the Teeth parameters properties.
- L58 _private prototype_ `void OnTeethSliderPropertyEdited(FProperty* Property);` — Called when a property is being edited on a teeth slider.
- L61 _private prototype_ `void OnTeethEditablePropertyValueChanged(uint8 Value, FProperty* Property, void* PropertyContainerPtr);` — Called when the teeth editable property has changed.
- L64 _private prototype_ `void OnTeethSliderValueChanged(const float Value, bool bIsInteractive, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a property has been changed on a teeth slider.
- L67 _private prototype_ `const FSlateBrush* GetEyelashesSectionBrush(uint8 InItem);` — Gets the Eyelashes section brush according to the given item value.
- L70 _private prototype_ `const FSlateBrush* GetTeethSectionBrush(uint8 InItem);` — Gets the Teeth section brush according to the given item value.
- L73 _private prototype_ `EVisibility GetEyelashesSubToolViewVisibility() const;` — Gets the visibility for the Eyelashes subtool view.
- L76 _private prototype_ `EVisibility GetTeethSubToolViewVisibility() const;` — Gets the visibility for the Teeth subtool view.
- L79 _private member_ `TSharedPtr<SVerticalBox> TeethEditablePropertyBox;` — Reference to the box container of the current teeth editable property.
- L82 _private member_ `TSharedPtr<SMetaHumanCharacterEditorComboBox<EMetaHumanCharacterTeethPropertyType>> TeethEditablePropertyComboBox;` — Reference to the box container of the current teeth editable property.
- L85 _private member_ `TSharedPtr<SVerticalBox> EyelashesSubToolView;` — Reference to the Eyelashes subtool view.
- L88 _private member_ `TSharedPtr<SVerticalBox> TeethSubToolView;` — Reference to the Teeth subtool view.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorImportToolView.h` (Private)


#### class `SMetaHumanCharacterEditorImportToolView`  
`class SMetaHumanCharacterEditorImportToolView : public SMetaHumanCharacterEditorToolView`  
_L23-47_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: Abstract base for import tool views in the MetaHuman Character editor. Provides shared layout helpers and the virtual button/warning interface. Does not assume anything about property sets or undo mechanics.
- L28 _protected prototype_ `TSharedRef<SWidget> CreateImportToolViewWarningSection();` — Creates the section widget for showing the Warning panel.
- L31 _protected prototype_ `TSharedRef<SWidget> CreateImportToolViewButtonSection();` — Creates the section widget for showing the Import button.
- L34 _protected prototype_ `virtual bool IsImportButtonEnabled() const = 0;` — True if the Import button is enabled.
- L37 _protected prototype_ `virtual FReply OnImportButtonClicked() = 0;` — Called when the Import button is clicked.
- L40 _protected prototype_ `virtual FText GetImportButtonText() const;` — Gets the displayed text of the Import button. Defaults to "Apply".
- L43 _protected prototype_ `virtual FText GetWarningText() const;` — Gets the text for the warning panel. Defaults to empty (hidden).
- L46 _protected prototype_ `EVisibility GetWarningVisibility() const;` — Gets the visibility of the warning panel

#### class `SMetaHumanCharacterEditorInternalImportToolView`  
`class SMetaHumanCharacterEditorInternalImportToolView : public SMetaHumanCharacterEditorImportToolView , public FNotifyHook`  
_L54-95_
- inherits: `SMetaHumanCharacterEditorImportToolView,FNotifyHook`
- desc: Intermediate base for the built-in import tool views. Adds FNotifyHook for property-change undo tracking and provides implementations driven by UMetaHumanCharacterEditorImportTool.
- L59 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorInternalImportToolView)`
- L62 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorImportTool* InTool);`
- L69 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L70 _protected prototype_ `virtual void MakeToolView() override;`
- L74 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L75 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L79 _protected prototype_ `TSharedRef<SWidget> CreateImportToolToolbarSection();` — Creates the section widget for showing the toolbar
- L82 _protected prototype_ `EMetaHumanImportToolMode GetImportToolMode() const;` — Gets the current import tool mode from the tool properties.
- L85 _protected prototype_ `void OnImportToolModeChanged(EMetaHumanImportToolMode Mode);` — Called when the import tool mode is changed by the user.
- L88 _protected prototype_ `EVisibility GetImportToolModeVisibility(EMetaHumanImportToolMode Mode) const;` — Gets the visibility of the Import Tool properties sections based on the current tool mode.
- L91 _protected prototype_ `virtual bool IsImportButtonEnabled() const override;`
- L92 _protected prototype_ `virtual FReply OnImportButtonClicked() override;`
- L93 _protected prototype_ `virtual FText GetWarningText() const override;`

#### class `SMetaHumanCharacterEditorImportFromDNAToolView`  
`class SMetaHumanCharacterEditorImportFromDNAToolView : public SMetaHumanCharacterEditorInternalImportToolView`  
_L97-139_
- inherits: `SMetaHumanCharacterEditorInternalImportToolView`
- L101 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorImportFromDNAToolView)`
- L105 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorImportTool* InTool);`
- L111 _public prototype_ `virtual void MakeToolView() override;`
- L114 _private prototype_ `virtual bool IsImportButtonEnabled() const override;`
- L115 _private prototype_ `virtual FReply OnImportButtonClicked() override;`
- L116 _private prototype_ `virtual FText GetWarningText() const override;`
- L120 _private prototype_ `TSharedRef<SWidget> CreateImportLoadDNAAssetsSection();` — Creates the section widget for showing the Load DNA Assets properties
- L123 _private prototype_ `TSharedRef<SWidget> CreateImportBodyMeshSection();` — Creates the section widget for showing the Body Mesh properties
- L126 _private prototype_ `TSharedRef<SWidget> CreateImportBodyJointsSection();` — Creates the section widget for showing the Body Joints properties
- L129 _private prototype_ `bool IsDNABodyEnabled() const;` — True if the DNA body property should be enabled (disabled when bIsolateHeadFromBody is set).
- L132 _private prototype_ `bool IsReplaceMeshEnabled() const;` — True if the replace mesh property should be enabled (disabled when bImportWholeRig is set).
- L135 _private prototype_ `bool IsAutoRigHelperJointsEnabled() const;` — True if the auto rig helper joints property should be enabled.
- L138 _private prototype_ `bool IsImportHelperJointsEnabled() const;` — True if the import helper joints property should be enabled.

#### class `SMetaHumanCharacterEditorImportFromIdentityToolView`  
`class SMetaHumanCharacterEditorImportFromIdentityToolView : public SMetaHumanCharacterEditorInternalImportToolView`  
_L141-166_
- inherits: `SMetaHumanCharacterEditorInternalImportToolView`
- L145 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorImportFromIdentityToolView)`
- L149 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorImportTool* InTool);`
- L155 _public prototype_ `virtual void MakeToolView() override;`
- L158 _private prototype_ `virtual FText GetWarningText() const override;`
- L162 _private prototype_ `TSharedRef<SWidget> CreateImportLoadIdentityAssetsSection();` — Creates the section widget for showing the Load Identity Assets properties
- L165 _private prototype_ `TSharedRef<SWidget> CreateImportViewOptionsSection();` — Creates the section widget for showing the View Options properties

#### class `SMetaHumanCharacterEditorImportFromTemplateToolView`  
`class SMetaHumanCharacterEditorImportFromTemplateToolView : public SMetaHumanCharacterEditorInternalImportToolView`  
_L168-217_
- inherits: `SMetaHumanCharacterEditorInternalImportToolView`
- L172 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorImportFromTemplateToolView)`
- L176 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorImportTool* InTool);`
- L182 _public prototype_ `virtual void MakeToolView() override;`
- L186 _private prototype_ `virtual bool IsImportButtonEnabled() const override;`
- L187 _private prototype_ `virtual FReply OnImportButtonClicked() override;`
- L188 _private prototype_ `virtual FText GetWarningText() const override;`
- L192 _private prototype_ `TSharedRef<SWidget> CreateImportLoadTemplateAssetsSection();` — Creates the section widget for showing the Load Template Assets properties
- L195 _private prototype_ `TSharedRef<SWidget> CreateImportHeadOptionsSection();` — Creates the section widget for showing the Head Options properties
- L198 _private prototype_ `TSharedRef<SWidget> CreateImportBodyOptionsSection();` — Creates the section widget for showing the Body Options properties
- L201 _private prototype_ `TSharedRef<SWidget> CreateImportBodyMeshSection();` — Creates the section widget for showing the Body Mesh properties
- L204 _private prototype_ `TSharedRef<SWidget> CreateImportBodyJointsSection();` — Creates the section widget for showing the Body Joints properties
- L207 _private prototype_ `bool IsBodyMeshEnabled() const;` — True if the body mesh property should be enabled (disabled when bIsolateHeadFromBody is set).
- L210 _private prototype_ `bool IsHeadMeshPropertyEnabledByClass(TSubclassOf<UStreamableRenderAsset> Class) const;` — True if the head mesh properties should be enabled.
- L213 _private prototype_ `bool IsAutoRigHelperJointsEnabled() const;` — True if the auto rig helper joints property should be enabled.
- L216 _private prototype_ `bool IsImportHelperJointsEnabled() const;` — True if the import helper joints property should be enabled.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorMakeupToolView.h` (Private)


#### class `SMetaHumanCharacterEditorMakeupToolView`  
`class SMetaHumanCharacterEditorMakeupToolView : public SMetaHumanCharacterEditorToolView`  
_L11-50_
- inherits: `SMetaHumanCharacterEditorToolView`
- desc: View for displaying the Makeup Tool in the MetahHumanCharacter editor
- L15 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorMakeupToolView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorMakeupTool* InTool);`
- L25 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L26 _protected prototype_ `virtual void MakeToolView() override;`
- L31 _private prototype_ `TSharedRef<SWidget> CreateMakeupToolViewFoundationSection();` — Creates the section widget for showing the Foundation properties.
- L34 _private prototype_ `TSharedRef<SWidget> CreateMakeupToolViewEyesSection();` — Creates the section widget for showing the Eyes properties.
- L37 _private prototype_ `TSharedRef<SWidget> CreateMakeupToolViewBlushSection();` — Creates the section widget for showing the Blush properties.
- L40 _private prototype_ `TSharedRef<SWidget> CreateMakeupToolViewLipsSection();` — Creates the section widget for showing the Lips properties.
- L43 _private prototype_ `const FSlateBrush* GetEyesSectionBrush(uint8 InItem);` — Gets the Eyes section brush according to the given item value.
- L46 _private prototype_ `const FSlateBrush* GetBlushSectionBrush(uint8 InItem);` — Gets the Blush section brush according to the given item value.
- L49 _private prototype_ `const FSlateBrush* GetLipsSectionBrush(uint8 InItem);` — Gets the Lips section brush according to the given item value.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorMeshImportToolView.h` (Private)


#### class `SMetaHumanCharacterEditorMeshImportToolView`  
`class SMetaHumanCharacterEditorMeshImportToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L16-164_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Mesh Import Tool in the MetaHumanCharacter editor
- L21 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorToolView)`
- L25 _public prototype_ `~SMetaHumanCharacterEditorMeshImportToolView();` — Destructor.
- L28 _public prototype_ `void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorMeshImportTool* InTool);` — Constructs the widget.
- L32 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L33 _protected prototype_ `virtual void MakeToolView() override;`
- L37 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L38 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L43 _private prototype_ `TSharedRef<SWidget> CreateMeshImportToolbarSection();` — Creates the section widget for showing the toolbar
- L46 _private prototype_ `TSharedRef<SWidget> CreateMeshImportWarningTextSection();` — Creates the section widget for showing the warning text
- L49 _private prototype_ `TSharedRef<SWidget> CreateMeshImportLoadCustomMeshSection();` — Creates the section widget for showing the Load Custom Mesh properties
- L52 _private prototype_ `TSharedRef<SWidget> CreateMeshImportLoadMeshPartsSection();` — Creates the section widget for showing the Load Mesh Parts properties
- L55 _private prototype_ `TSharedRef<SWidget> CreateMeshImportCustomMeshSection();` — Creates the section widget for showing the Custom Mesh properties
- L58 _private prototype_ `TSharedRef<SWidget> CreateMeshImportMetaHumanMeshSection();` — Creates the section widget for showing the MetaHuman Mesh properties
- L61 _private prototype_ `TSharedRef<SWidget> CreateMeshImportKeyPointsSection();` — Creates the section widget for showing the Key Points properties
- L64 _private prototype_ `TSharedRef<SWidget> CreateMeshImportFacialTrackingSection();` — Creates the section widget for showing the Facial Tracking properties
- L67 _private prototype_ `TSharedRef<SWidget> CreateMeshImportButtonSection();` — Creates the section widget for showing the Import button section.
- L70 _private prototype_ `TSharedRef<SWidget> CreateAdvancedPropertiesWindow();` — Creates the window content for showing the advanced parameters properties.
- L73 _private prototype_ `TSharedRef<SWidget> CreateMeshImportToolButton(const FText& ButtonText, const FText& ToolTipText, const FOnClicked& OnClickedHandler, TAttribute<bool> IsEnabled, const FSlateBrush* Icon = nullptr) const;` — Helper function to create a button for the mesh import tool.
- L76 _private prototype_ `void OnAdvancedFeaturesWindowClosed(const TSharedRef<SWindow>& Window);` — Called when the advanced features window is closed.
- L79 _private prototype_ `EMetaHumanMeshImportMode GetMeshImportMode() const;` — Gets the current mesh import mode from the tool properties.
- L82 _private prototype_ `void OnMeshImportModeChanged(EMetaHumanMeshImportMode Mode);` — Called when the mesh import mode is changed by the user.
- L85 _private prototype_ `FReply OnResetBodyButtonClicked();` — Called when the Reset Body button is clicked.
- L88 _private prototype_ `bool IsResetBodyButtonEnabled() const;` — True if the Reset Body button is enabled.
- L91 _private prototype_ `FReply OnResetHeadButtonClicked();` — Called when the Reset Head button is clicked.
- L94 _private prototype_ `bool IsResetHeadButtonEnabled() const;` — True if the Reset Head button is enabled.
- L97 _private prototype_ `FReply OnSavePoseButtonClicked();` — Called when the Save Pose button is clicked.
- L100 _private prototype_ `bool IsSavePoseButtonEnabled() const;` — True if the Save Pose button is enabled.
- L103 _private prototype_ `FReply OnDeleteKeyPointsButtonClicked();` — Called when the Delete Key Points button is clicked.
- L106 _private prototype_ `bool IsDeleteKeyPointsButtonEnabled() const;` — True if the Delete Key Points button is enabled.
- L109 _private prototype_ `bool IsTraceFacialFeaturesButtonEnabled() const;` — True if the Trace Facial Features button is enabled.
- L112 _private prototype_ `bool IsFacialCurvesEditingEnabled() const;` — True if the Facial Curves editing is enabled.
- L115 _private prototype_ `FReply OnTraceFacialFeaturesButtonClicked();` — Called when the Trace Facial Features button is clicked.
- L118 _private prototype_ `bool IsDeleteFaceCurvesButtonEnabled() const;` — True if the Delete Face Curves button is enabled.
- L121 _private prototype_ `FReply OnDeleteFaceCurvesButtonClicked();` — Called when the Delete Face Curves button is clicked.
- L124 _private prototype_ `bool IsAlignHeadButtonEnabled() const;` — True if the Align Head button is enabled.
- L127 _private prototype_ `FReply OnAlignHeadButtonClicked();` — Called when the Align Head button is clicked.
- L130 _private prototype_ `bool IsBodySolveStepButtonEnabled() const;` — True if the Body Solve Step button is enabled.
- L133 _private prototype_ `FReply OnBodySolveStepButtonClicked();` — Called when the Body Solve Step button is clicked.
- L136 _private prototype_ `bool IsFaceSolveStepButtonEnabled() const;` — True if the Face Solve Step button is enabled.
- L139 _private prototype_ `FReply OnFaceSolveStepButtonClicked();` — Called when the Face Solve Step button is clicked.
- L142 _private prototype_ `bool IsRefineVerticesButtonEnabled() const;` — True if the Refine Vertices button is enabled.
- L145 _private prototype_ `FReply OnRefineVerticesButtonClicked();` — Called when the Refine Vertices button is clicked.
- L148 _private prototype_ `bool IsImportButtonEnabled() const;` — True if the Import button is enabled.
- L151 _private prototype_ `FReply OnAdvancedFeaturesButtonClicked();` — Called when the Advanced Features button is clicked.
- L154 _private prototype_ `FReply OnImportButtonClicked();` — Called when the Import button is clicked.
- L157 _private prototype_ `FText GetWarningText() const;` — Gets the text for the warning panel
- L160 _private prototype_ `EVisibility GetMeshImportModeVisibility(EMetaHumanMeshImportMode Mode) const;` — Gets the visibility according to given the mesh import mode
- L163 _private member_ `TSharedPtr<SWindow> AdvancedFeaturesWindow;` — Reference to the window that displays the advanced parameters properties

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorPipelineToolView.h` (Private)


#### class `SMetaHumanCharacterEditorPipelineToolView`  
`class SMetaHumanCharacterEditorPipelineToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L13-58_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Pipeline Tool in the MetahHumanCharacter editor
- L18 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorToolView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorPipelineTool* InTool);`
- L25 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L26 _protected prototype_ `virtual void MakeToolView() override;`
- L30 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L31 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L36 _private prototype_ `TSharedRef<SWidget> CreatePipelineToolViewDetailsViewSection();` — Creates the section widget for showing the main Details View.
- L39 _private prototype_ `TSharedRef<SWidget> CreatePipelineToolViewAssembleSection();` — Creates the section widget for showing the Assemble button.
- L42 _private prototype_ `bool IsAssembleButtonEnabled() const;` — True if the Assemble button is enabled.
- L45 _private prototype_ `FReply OnAssembleButtonClicked();` — Called when the Assemble button is clicked.
- L48 _private prototype_ `FText GetAssembleButtonText() const;` — Gets the Assemble button label text.
- L51 _private prototype_ `EVisibility GetWarningVisibility() const;` — Gets the warning message visibility.
- L54 _private member_ `FText BuildErrorMsg;` — The optional error message displayed when building the pipeline.
- L57 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Reference to the Details View that displays pipeline properties.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorPresetsToolView.h` (Private)


#### class `SMetaHumanCharacterEditorPresetsToolView`  
`class SMetaHumanCharacterEditorPresetsToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L22-145_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Presets Tool in the MetahHumanCharacter editor
- L29 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorPresetsToolView)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorPresetsTool* InTool);`
- L38 _public prototype_ `FMetaHumanCharacterAssetViewsPanelStatus GetAssetViewsPanelStatus() const;` — Gets the status parameters of the asset views panel.
- L41 _public prototype_ `void SetAssetViewsPanelStatus(const FMetaHumanCharacterAssetViewsPanelStatus& Status);` — Sets the status of the asset views panel according to the given parameters.
- L44 _public prototype_ `TArray<FMetaHumanCharacterAssetViewStatus> GetAssetViewsStatusArray() const;` — Gets an array with the status parameters of all the asset views in the panel.
- L47 _public prototype_ `void SetAssetViewsStatus(const TArray<FMetaHumanCharacterAssetViewStatus>& StatusArray);` — Sets the status of the asset views in the panel according to the given array.
- L50 _public prototype_ `virtual const FName& GetToolViewNameID() const override;`
- L55 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L56 _protected prototype_ `virtual void MakeToolView() override;`
- L60 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L61 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L66 _private prototype_ `TSharedRef<SWidget> CreatePresetsToolViewPresetsViewSection();` — Creates the section widget for showing the Presets View.
- L69 _private prototype_ `TSharedRef<SWidget> CreatePresetsToolViewManagementSection();` — Creates the section widget for showing the Management properties.
- L72 _private prototype_ `TSharedRef<SWidget> CreatePresetsToolViewLibrarySection();` — Creates the section widget for showing the Library properties.
- L75 _private prototype_ `TSharedRef<SWidget> MakePresetPropertiesWindow();` — Creates the Preset Properties window content.
- L78 _private prototype_ `FReply OnAcceptPresetPropertiesClicked();` — Called when the Accept button in the Preset Properties window is clicked.
- L81 _private prototype_ `FReply OnCancelPresetPropertiesClicked();` — Called when the Cancel button in the Preset Properties window is clicked.
- L84 _private prototype_ `bool IsPropertiesEditingEnabled() const;` — True if properties editing is enabled.
- L87 _private prototype_ `bool IsInspectButtonEnabled() const;` — True when the Inspect button is enabled.
- L90 _private prototype_ `FReply OnInspectButtonClicked();` — Called when the Inspect button is clicked.
- L93 _private prototype_ `void OpenPresetPropertiesWindow();` — Opens the preset properties window.
- L96 _private prototype_ `void ApplyPreset();` — Applies the preset properties values.
- L99 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> GetCharacterIndividualAssets() const;` — Gets and array of items containing the stored Character individual assets.
- L102 _private prototype_ `TArray<FMetaHumanCharacterAssetsSection> GetAssetViewsSections() const;` — Gets the sections array for the wardrobe asset views panel.
- L105 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> OnPopulateAssetViewsItems(const FMetaHumanCharacterAssetsSection& InSection, const FMetaHumanObserverChanges& InChanges);` — Called when to populate asset views with items.
- L108 _private prototype_ `void OnProcessDroppedFolders(const TArray<FContentBrowserItem> Items, const FMetaHumanCharacterAssetsSection& InSection) const;` — Called to process an array of dropped folders in the asset views panel.
- L111 _private prototype_ `void OnPresetsToolItemActivated(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been activated.
- L114 _private prototype_ `void OnPresetsToolVirtualItemDeleted(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been deleted.
- L117 _private prototype_ `bool CanDeletePresetsToolVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True if the given item can be deleted.
- L120 _private prototype_ `void OnPresetsPathsFolderDeleted(const FMetaHumanCharacterAssetsSection& InSection);` — Called when the folder has been deleted.
- L123 _private prototype_ `bool CanDeletePresetsPathsFolder(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item, const FMetaHumanCharacterAssetsSection& InSection) const;` — True if the given folder can be deleted.
- L126 _private prototype_ `void OnHandlePresetsVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been moved in a virtual folder.
- L129 _private prototype_ `void OnOverrideItemThumbnailBrush(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — Called to override the item thumbnail brush.
- L132 _private prototype_ `void OnPresetsDirectoriesChanged();` — Called when the Project Settings selected directory paths have been changed.
- L135 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Reference to this view command list.
- L138 _private member_ `TSharedPtr<SMetaHumanCharacterEditorAssetViewsPanel> AssetViewsPanel;` — Reference to this Asset Views panel.
- L141 _private member_ `TSharedPtr<SWindow> PresetsPropertiesWindow;` — Reference to the window which displays the Presets properties.
- L144 _private member_ `static const FName PresetsLibraryAssetsSlotName;` — Name identifier for the slot where virtual assets from the presets library are stored.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorRenderingQualityView.h` (Private)


#### class `SMetaHumanCharacterEditorRenderingQualityView`  
`class SMetaHumanCharacterEditorRenderingQualityView : public SCompoundWidget, public FGCObject`  
_L14-51_
- inherits: `SCompoundWidget,FGCObject`
- desc: View for displaying meta human render quality
- L17 _public function_ `DECLARE_DELEGATE_OneParam(FOnRenderingQualityProfileUpdate, int32) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorRenderingQualityView)`
- L22 _public prototype_ `SLATE_EVENT(FOnRenderingQualityProfileUpdate, OnRenderingQualityProfileUpdate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const int32 InActiveProfileIndex);` — Called when render quality profile is updated.
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L30 _public prototype_ `virtual FString GetReferencerName() const override;`
- L33 _public prototype_ `void SetSelectedItem(const int32 InIndex) const;`
- L36 _private prototype_ `void CreateSettingsView();`
- L37 _private prototype_ `void RebuildProfileNames();`
- L38 _private prototype_ `void SwitchToProfile(const int32 InIndex) const;`
- L39 _private prototype_ `void SwitchToProfile(const int32 InIndex, const bool bBroadcastSwitch) const;`
- L41 _private prototype_ `FReply OnAddProfileClicked();`
- L42 _private prototype_ `FReply OnCloneProfileClicked();`
- L43 _private prototype_ `FReply OnRemoveOrResetProfileClicked();`
- L44 _private prototype_ `void CreateAndSelectNewProfile(FMetaHumanCharacterRenderingQualityProfile& InRenderingQuality);`
- L46 _private member_ `TSharedPtr<IDetailsView> SettingsView;`
- L47 _private member_ `TSharedPtr<SMetaHumanCharacterEditorTextComboBox> ProfileComboBox;`
- L48 _private member_ `TArray<TSharedPtr<FString>> ProfileNames;`
- L49 _private member_ `TObjectPtr<UMetaHumanCharacterRenderingQualityProfileProxy> Proxy;`
- L50 _private member_ `FOnRenderingQualityProfileUpdate OnRenderingQualityProfileUpdate;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRenderingQualityProfileUpdate, int32) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorRenderingQualityView) {} SLATE_EVENT(FOnRenderingQualityProfileUpdate, OnRenderingQualityProfileUpdate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const int32 InActiveProfileIndex);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorSkinToolView.h` (Private)


#### class `SMetaHumanCharacterEditorSkinToolView`  
`class SMetaHumanCharacterEditorSkinToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook`  
_L14-98_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Skin Tool in the MetahHumanCharacter editor
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorSkinToolView)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorSkinTool* InTool);`
- L29 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L30 _protected prototype_ `virtual void MakeToolView() override;`
- L34 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L35 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L40 _private prototype_ `TSharedRef<SWidget> CreateSkinToolViewSkinSection();` — Creates the section widget for showing the Skin properties.
- L43 _private prototype_ `TSharedRef<SWidget> CreateSkinToolViewHandsAndFeetSkinSubSection();` — Creates the subsection widget for showing the Hands & Feet Skin properties.
- L46 _private prototype_ `TSharedRef<SWidget> CreateSkinToolViewFrecklesSection();` — Creates the section widget for showing the Freckles properties.
- L49 _private prototype_ `TSharedRef<SWidget> CreateSkinToolViewAccentsSection();` — Creates the section widget for showing the Accents properties.
- L52 _private prototype_ `TSharedRef<SWidget> CreateTextureSourceSection();` — Creates the section widget for showing the Desired Texture Sources Resolution
- L55 _private prototype_ `TSharedRef<SWidget> CreateAccentRegionPropertySpinBoxWidget(const FText LabelText, FProperty* Property, const int32 FractionalDigits = 2);` — Creates a spin box widget for displaying accent region related Numeric Properties, if valid.
- L58 _private prototype_ `void* GetAccentRegionPropertyContainerFromSelection() const;` — Gets the specific accent region Property Container pointer from the current panel selection.
- L61 _private prototype_ `const void* GetAccentRegionDefaultPropertyContainerFromSelection() const;` — Gets the default accent region Property Container pointer from the current panel selection.
- L64 _private prototype_ `TOptional<float> GetAccentRegionFloatPropertyValue(FProperty* Property) const;` — Gets the value of the given accent region related Numeric Property, if valid.
- L67 _private prototype_ `void OnAccentRegionFloatPropertyValueChanged(const float Value, bool bIsDragging, FProperty* Property);` — Called when the value of an accent region related Numeric Property is changed, if valid.
- L70 _private prototype_ `FReply OnAccentRegionPropertyResetToDefaultClicked(FProperty* Property);` — Called when the reset to default button is clicked for an accent region related Property.
- L73 _private prototype_ `EVisibility GetAccentRegionPropertyResetVisibility(FProperty* Property) const;` — Gets the visibility of the reset to default button for an accent region related Property.
- L76 _private prototype_ `void OnSkinUVChanged(const FVector2f& UV, bool bIsDragging);` — Called when the Skin UV values have changed.
- L79 _private prototype_ `const FSlateBrush* GetFreckesSectionBrush(uint8 InItem);` — Gets the Freckles section brush according to the given item value.
- L82 _private prototype_ `bool IsEditEnabled() const;` — True if editing is enabled in this tool view.
- L85 _private prototype_ `bool IsSkinEditEnabled() const;` — True if skin editing is enabled in this tool view.
- L88 _private prototype_ `virtual EVisibility GetPropertyVisibility(FProperty* Property, void* PropertyContainerPtr) const override;` — Returns the visibility of a property.
- L91 _private prototype_ `virtual bool IsPropertyEnabled(FProperty* Property, void* PropertyContainerPtr) const override;` — Returns whether the property is enabled
- L94 _private member_ `TSharedPtr<SMetaHumanCharacterEditorAccentRegionsPanel> AccentRegionsPanel;` — Reference to the Accent Regions panel.
- L97 _private member_ `TArray<TArray<TSharedPtr<FString>>> AttributeValueNames;` — Attribute names.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorTextureMaterialOverrideToolView.h` (Private)


#### class `SMetaHumanCharacterEditorTextureMaterialOverrideToolView`  
`class SMetaHumanCharacterEditorTextureMaterialOverrideToolView : public SMetaHumanCharacterEditorToolView, public FNotifyHook`  
_L11-31_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook`
- desc: View for displaying the Texture & Material Overrides Tool in the MetaHuman Character editor
- L14 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTextureMaterialOverrideToolView)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorTextureMaterialOverrideTool* InTool);`
- L23 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L24 _protected prototype_ `virtual void MakeToolView() override;`
- L28 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L29 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorToolView.h` (Private)


#### class `SMetaHumanCharacterEditorToolView`  
`class SMetaHumanCharacterEditorToolView : public SCompoundWidget`  
_L27-302_
- inherits: `SCompoundWidget`
- desc: View for displaying an interactive tool in the MetaHumanCharacter editor
- L33 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorToolView)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UInteractiveTool* InTool);`
- L42 _public prototype_ `float GetScrollOffset() const;` — Gets the current scroll offset of the view.
- L45 _public prototype_ `void SetScrollOffset(float NewScrollOffset);` — Sets the scroll offset of the view.
- L48 _public prototype_ `virtual const FName& GetToolViewNameID() const;` — Gets the name identifier of the view.
- L51 _public prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;`
- L56 _protected function_ `virtual UInteractiveTool* GetTool() const` — Gets the Tool this view is based on.
- L59 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const = 0;` — Gets the properties of the Tool this view is based on. To implement in inherited classes.
- L62 _protected prototype_ `virtual void MakeToolView() = 0;` — Called in the default constructor. Contains the tool view specific implementation. To implement in inherited classes.
- L67 _protected prototype_ `TSharedRef<SWidget> CreatePropertyNumericEntry(FProperty* InProperty, void* PropertyContainerPtr, const FString& InLabelOverride = TEXT(""), const int32 FractionalDigits = 2);` — Creates a numeric entry widget for the given Numeric Property, if valid.
- L70 _protected prototype_ `TSharedRef<SWidget> CreatePropertyNumericEntryNormalized(FProperty* InProperty, void* InPropertyContainerPtr, float InMinValue, float InMaxValue, const FText& InLabelOverride = FText::GetEmpty());` — Creates a numeric entry widget for the given Numeric Property that displays the normalized range [InMinValue, InMaxValue]
- L73 _protected prototype_ `TSharedRef<SWidget> CreatePropertySpinBoxWidget(const FText& LabelText, FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr, const int32 FractionalDigits = 2);` — Creates a spin box widget for the given Numeric Property, if valid.
- L76 _protected prototype_ `TSharedRef<SWidget> CreatePropertySpinBoxWidgetNormalized(FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr, float InMinValue = -1.0f, float InMaxValue = -1.0f, const FText& InLabelOverride = FText::GetEmpty());` — Creates a spin box widget for the given Numeric Property showing the normalized value in the UI. When the value changes the value is converted to the range [InMinValue, InMaxValue] for storage
- L79 _protected prototype_ `TSharedRef<SWidget> CreatePropertyCheckBoxWidget(const FText& LabelText, FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr);` — Creates a check box widget for the given Bool Property, if valid.
- L83 _protected function_ `template<typename TEnum> TSharedRef<SWidget> CreatePropertyComboBoxWidget(const FText& LabelText, TEnum SelectedItem, FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr)` — Creates a combo box widget for the given Enum Property, if valid.
- L148 _protected prototype_ `TSharedRef<SWidget> CreatePropertyColorPickerWidget(const FText& LabelText, FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr);` — Creates a color picker widget for the given Color Property, if valid.
- L151 _protected prototype_ `TSharedRef<SWidget> CreatePropertyPalettePickerWidget(FProperty* ColorProperty, FProperty* ColorIndexProperty, void* PropertyContainerPtr, const void* DefaultContainerPtr, int32 NumPaletteColumns, int32 NumPaletteRows, const FText& LabelText, const FLinearColor& DefaultColor = FLinearColor::Transparent, UTexture2D* CustomPickerTexture = nullptr, const FText& ULabelOverride = FText::GetEmpty(), const FText& VLabelOverride = FText::GetEmpty());` — Creates a color palette picker widget for the given Color Property, if valid.
- L164 _protected prototype_ `TSharedRef<SWidget> CreatePropertyUVColorPickerWidget(FProperty* PropertyU, FProperty* PropertyV, void* PropertyContainerPtr, const void* DefaultContainerPtr, const FText& ColorPickerLabel, TNotNull<UTexture2D*> InColorPickerTexture, const FText& ULabelOverride = FText::GetEmpty(), const FText& VLabelOverride = FText::GetEmpty());` — Creates a color picker widget using the two properties that represent the UV values to sample a texture
- L175 _protected prototype_ `TSharedRef<SWidget> CreatePropertyDefaultWidget(const FText& LabelText, FProperty* Property, UObject* PropertyContainerObject, FNotifyHook* NotifyHook = nullptr);` — Creates the default widget for the given Property, if valid.
- L178 _protected prototype_ `TSharedRef<SWidget> CreatePropertyResetButton(FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr);` — Creates a reset to default button for the given Property, if valid.
- L181 _protected prototype_ `ECheckBoxState IsPropertyCheckBoxChecked(FProperty* Property, void* PropertyContainerPtr) const;` — Gets the check box state according to the given Bool Property, if valid.
- L184 _protected prototype_ `void OnPropertyCheckStateChanged(ECheckBoxState CheckState, FProperty* Property, void* PropertyContainerPtr);` — Called when the check box state changes according to the given Bool Property, if valid.
- L187 _protected prototype_ `FReply OnColorBlockMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, FProperty* Property, void* PropertyContainerPtr, const FString Label = TEXT(""));` — Called when the mouse button is pressed on the color block of a given Color Property, if valid.
- L190 _protected prototype_ `TOptional<int32> GetIntPropertyValue(FProperty* Property, void* PropertyContainerPtr) const;` — Gets the value of the given Numeric Property as an integer, if valid.
- L193 _protected prototype_ `TOptional<int32> GetIntPropertyMinValue(FProperty* Property) const;` — Gets the min value of the given Numeric Property as an integer, if valid.
- L196 _protected prototype_ `TOptional<int32> GetIntPropertyMaxValue(FProperty* Property) const;` — Gets the max value of the given Numeric Property as an integer, if valid.
- L199 _protected prototype_ `TOptional<float> GetFloatPropertyValue(FProperty* Property, void* PropertyContainerPtr) const;` — Gets the value of the given Numeric Property as a float, if valid.
- L202 _protected prototype_ `TOptional<float> GetFloatPropertyValueNormalized(FProperty* InProperty, void* InPropertyContainerPtr, float InMinValue, float InMaxValue) const;` — Gets the value of the given Numeric Property as a normalized float
- L205 _protected prototype_ `TOptional<float> GetFloatPropertyMinValue(FProperty* Property) const;` — Gets the min value of the given Numeric Property as a float, if valid.
- L208 _protected prototype_ `TOptional<float> GetFloatPropertyMaxValue(FProperty* Property) const;` — Gets the max value of the given Numeric Property as a float, if valid.
- L211 _protected prototype_ `bool GetBoolPropertyValue(FProperty* Property, void* PropertyContainerPtr) const;` — Gets the value of the given Bool Property, if valid.
- L215 _protected function_ `template<typename TEnum> TEnum GetEnumPropertyValue(FProperty* Property, void* PropertyContainerPtr) const` — Gets the value of the given Enum or Byte Property, if valid.
- L238 _protected prototype_ `FLinearColor GetColorPropertyValue(FProperty* Property, void* PropertyContainerPtr) const;` — Gets the value of the given Color Property, if valid.
- L241 _protected prototype_ `void OnPreEditChangeProperty(FProperty* Property, const FString Label = TEXT(""));` — Called before the value of a Property gets changed.
- L244 _protected prototype_ `virtual void OnPostEditChangeProperty(FProperty* Property, bool bIsInteractive);` — Called after the value of a Property has been changed.
- L247 _protected prototype_ `void OnIntPropertyValueChanged(int32 Value, bool bIsInteractive, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a Numeric Property is changed, if valid.
- L250 _protected prototype_ `void OnFloatPropertyValueChanged(const float Value, bool bIsInteractive, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a Numeric Property is changed, if valid.
- L253 _protected prototype_ `void OnIntPropertyValueCommitted(int32 Value, ETextCommit::Type Type, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of the Numeric Property is committed
- L256 _protected prototype_ `void OnFloatPropertyNormalizedValueChanged(float Value, float InMinValue, float InMaxValue, bool bIsInteractive, FProperty* InProperty, void* InPropertyContainerPtr);` — called when the value of a Normalized Numeric Property is changed
- L259 _protected prototype_ `void OnFloatPropertyValueCommited(const float Value, ETextCommit::Type Type, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a Numeric Property is committed, if valid.
- L262 _protected prototype_ `void OnFloatPropertyNormalizedValueCommited(float InValue, ETextCommit::Type InType, float InMinValue, float InMaxValue, FProperty* InProperty, void* InPropertyContainerPtr);` — Called when the value of a Normalized Numeric Property is committed
- L265 _protected prototype_ `void OnBoolPropertyValueChanged(const bool Value, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a Bool Property is changed, if valid.
- L268 _protected prototype_ `void OnEnumPropertyValueChanged(uint8 Value, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of an Enum Property is changed, if valid.
- L271 _protected prototype_ `void OnColorPropertyValueChanged(FLinearColor Color, bool bIsInteractive, FProperty* Property, void* PropertyContainerPtr);` — Called when the value of a Color Property is changed, if valid.
- L274 _protected prototype_ `FReply OnPropertyResetToDefaultClicked(FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr);` — Called when the reset to default button is clicked for a property.
- L277 _protected prototype_ `EVisibility GetPropertyResetVisibility(FProperty* Property, void* PropertyContainerPtr, const void* DefaultContainerPtr) const;` — Gets the visibility of the reset to default button for a property.
- L280 _protected prototype_ `virtual EVisibility GetPropertyVisibility(FProperty* Property, void* PropertyContainerPtr) const;` — Returns the visibility of a property.
- L283 _protected prototype_ `virtual bool IsPropertyEnabled(FProperty* Property, void* PropertyContainerPtr) const;` — Returns whether the property is enabled.
- L286 _protected prototype_ `void CancelOutstandingTransaction();` — Cancels any outstanding property change transaction.
- L289 _protected member_ `TUniquePtr<FScopedTransaction> PropertyChangeTransaction;` — Unique pointer to the property change transaction.
- L292 _protected member_ `TSharedPtr<SVerticalBox> ToolViewMainBox;` — Reference to the tool view main vertical box.
- L295 _protected member_ `TSharedPtr<SScrollBox> ToolViewScrollBox;` — Reference to the tool view scroll box.
- L298 _protected member_ `TWeakObjectPtr<UInteractiveTool> Tool;` — Weak reference to the Tool this view is based on.
- L301 _protected member_ `float ToolViewHeightRatio = 1.f;` — Desired Height ratio multiplier for adjusting the tool view size.

#### Free symbols / members of external scopes

- L123 _function_ `` (scope `SMetaHumanCharacterEditorToolView::CreatePropertyComboBoxWidget`)
- L218 _typedef_ `using UnderT = std::underlying_type_t<TEnum>;` (scope `SMetaHumanCharacterEditorToolView::GetEnumPropertyValue`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Views/SMetaHumanCharacterEditorWardrobeToolView.h` (Private)


#### class `SMetaHumanCharacterEditorWardrobeToolView`  
`class SMetaHumanCharacterEditorWardrobeToolView : public SMetaHumanCharacterEditorToolView , public FNotifyHook , public FSelfRegisteringEditorUndoClient`  
_L27-199_
- inherits: `SMetaHumanCharacterEditorToolView,FNotifyHook,FSelfRegisteringEditorUndoClient`
- desc: View for displaying the Wardrobe Tool in the MetahHumanCharacter editor
- L35 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorWardrobeToolView)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacterEditorWardrobeTool* InTool);`
- L44 _public prototype_ `FMetaHumanCharacterAssetViewsPanelStatus GetAssetViewsPanelStatus() const;` — Gets the status parameters of the asset views panel.
- L47 _public prototype_ `void SetAssetViewsPanelStatus(const FMetaHumanCharacterAssetViewsPanelStatus& Status);` — Sets the status of the asset views panel according to the given parameters.
- L50 _public prototype_ `TArray<FMetaHumanCharacterAssetViewStatus> GetAssetViewsStatusArray() const;` — Gets an array with the status parameters of all the asset views in the panel.
- L53 _public prototype_ `void SetAssetViewsStatus(const TArray<FMetaHumanCharacterAssetViewStatus>& StatusArray);` — Sets the status of the asset views in the panel according to the given array.
- L56 _public prototype_ `virtual const FName& GetToolViewNameID() const override;`
- L61 _protected prototype_ `virtual UInteractiveToolPropertySet* GetToolProperties() const override;`
- L62 _protected prototype_ `virtual void MakeToolView() override;`
- L66 _protected prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L67 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L71 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L72 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L77 _private prototype_ `TSharedRef<SWidget> CreateWardrobeToolViewAssetViewsPanelSection();` — Creates the section widget for showing the Asset Views panel.
- L80 _private prototype_ `TSharedRef<SWidget> CreateWardrobeToolViewToolbarSection();` — Creates the section widget for showing the main toolbar.
- L83 _private prototype_ `void CreateWardrobeItemsForCompatibleAssets(const FMetaHumanCharacterAssetsSection& Section);` — Creates Wardrobe items for all compatible assets in the given section.
- L86 _private prototype_ `void RegisterToolbarCommands();` — Registers the toolbar command actions.
- L89 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> GetWardrobeIndividualAssets(const FName& SlotName) const;` — Gets and array of items containing the stored Wardrobe individual assets.
- L92 _private prototype_ `TArray<FMetaHumanCharacterAssetsSection> GetWardrobeAssetViewsSections(const UMetaHumanCharacter* InCharacter, const UMetaHumanCharacterEditorPipelineSpecification* InSpec) const;` — Gets the sections array for the wardrobe asset views panel.
- L95 _private prototype_ `bool IsItemValid(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True if item is considered valid to be applied in the character
- L98 _private prototype_ `bool IsItemCompatible(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item, const FMetaHumanCharacterAssetsSection& Section) const;` — True is the item asset is compatible to the given section. Called when new items are dropped into the wardrobe panel
- L101 _private prototype_ `bool IsItemChecked(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True is the item asset is checked.
- L104 _private prototype_ `bool IsItemActive(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True is the item asset is active.
- L107 _private prototype_ `FName OnOverrideSlotName(const FName& SlotName);` — Called to override the given slot name.
- L110 _private prototype_ `FText OnOverrideItemThumbnailName(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — Called to override the name of the thumbnail
- L113 _private prototype_ `void OnOverrideItemThumbnailBrush(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — Called to override the item thumbnail brush.
- L116 _private prototype_ `UObject* OnProcessDroppedItem(const FAssetData& AssetData);` — Called to process a dropped item in the asset views panel.
- L119 _private prototype_ `void OnProcessDroppedFolders(const TArray<FContentBrowserItem> Items, const FMetaHumanCharacterAssetsSection& InSection) const;` — Called to process an array of dropped folders in the asset views panel.
- L122 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> OnPopulateAssetViewsItems(const FMetaHumanCharacterAssetsSection& InSection, const FMetaHumanObserverChanges& InChanges);` — Called when to populate asset views with items.
- L125 _private prototype_ `void OnWardrobeToolItemActivated(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been activated.
- L128 _private prototype_ `void OnWardrobeToolVirtualItemDeleted(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been deleted.
- L131 _private prototype_ `bool CanDeleteWardrobeToolVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True if the given item can be deleted.
- L134 _private prototype_ `void OnWardrobePathsFolderDeleted(const FMetaHumanCharacterAssetsSection& InSection);` — Called when the folder has been deleted.
- L137 _private prototype_ `bool CanDeleteWardrobePathsFolder(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item, const FMetaHumanCharacterAssetsSection& InSection) const;` — True if the given folder can be deleted.
- L140 _private prototype_ `void OnHandleWardrobeVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been moved in a virtual folder.
- L150 _private prototype_ `bool ApplyWearRequest(const TArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>>& Items, EWearRequest WearRequest);` — Tries to apply wear state to the given items. Returns true if collection was updated, false otherwise
- L153 _private prototype_ `void UpdateAdditionalCharacterSettings(const FName& SlotName, TSharedPtr<FMetaHumanCharacterAssetViewItem> Item, bool bUnwear = false);` — Updates character model settings
- L162 _private prototype_ `void OnCollectionModified();` — Must be called when the collection or its default instance have been modified. If the modifications are part of a transaction, this function must be called within the scope of the transaction, so that the edits to the Character's collection are also captured (not just the preview collection).
- L165 _private prototype_ `void RebuildPreviewCollection();` — Rebuild the preview collection to update the preview viewport
- L168 _private prototype_ `void PrepareAsset(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Prepares the asset in the given asset item, if valid.
- L171 _private prototype_ `void UnprepareAsset(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Unprepares the asset in the given asset item, if valid.
- L174 _private prototype_ `void OnWardrobePathsChanged();` — Called when the wardrobe paths array in the project settings has changed.
- L177 _private prototype_ `void OnPrepareAccessory();` — Called when an accessory is prepared.
- L180 _private prototype_ `void OnUnprepareAccessory();` — Called when an accessory is unprepared.
- L183 _private prototype_ `void OnWearAccessory();` — Called to wear an accessory.
- L186 _private prototype_ `void OnRemoveAccessory();` — Called when an accessory is removed.
- L189 _private prototype_ `void OnOpenAccessoryProperties();` — Called to open accessory properties.
- L192 _private prototype_ `void GetSlotSelectionItemForGivenItemPath(const FSoftObjectPath& ItemPath, const TArray<FMetaHumanPipelineSlotSelectionData>& InSlotSelectionData, FMetaHumanPipelineSlotSelection& InOutSlotSelectionItem) const;` — Extracts the SlotSelectionItem for a give ItemPath regardless of SlotName
- L195 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Reference to this view command list.
- L198 _private member_ `TSharedPtr<SMetaHumanCharacterEditorAssetViewsPanel> AssetViewsPanel;` — Reference to this Asset Views panel.

#### enum `SMetaHumanCharacterEditorWardrobeToolView::EWearRequest`  
`enum class EWearRequest`  
_L142-147_
- L144 _public enumerator_ `Wear`
- L145 _public enumerator_ `Unwear`
- L146 _public enumerator_ `Toggle`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/DNAImportDialogWidget.h` (Private)


#### class `SDNAImportDialogWidget`  
`class SDNAImportDialogWidget : public SWindow`  
_L14-48_
- inherits: `SWindow`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDNAImportDialogWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void OnBrowseButtonClicked() const;`
- L22 _public prototype_ `void OnMeshTypeChanged(TSharedPtr<FString> InNewSelection, ESelectInfo::Type);`
- L24 _public prototype_ `FReply OnImportClicked();`
- L26 _public prototype_ `FString GetFilePath() const;`
- L27 _public prototype_ `FString GetImportName() const;`
- L28 _public prototype_ `FString GetImportPath() const;`
- L29 _public prototype_ `FString GetMeshType() const;`
- L30 _public prototype_ `TSharedPtr<EMetaHumanCharacterSkinPreviewMaterial> GetSelectedMaterial();`
- L34 _private prototype_ `TSharedRef<SWidget> MakeComboWidget(TSharedPtr<FString> InItem);`
- L36 _private member_ `TSharedPtr<SEditableTextBox> FilePathBox;`
- L37 _private member_ `TSharedPtr<SEditableTextBox> NameBox;`
- L38 _private member_ `TSharedPtr<SEditableTextBox> PathBox;`
- L39 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> MeshTypeComboBox;`
- L40 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> TextureTypeComboBox;`
- L41 _private member_ `TSharedPtr<SComboBox<TSharedPtr<EMetaHumanCharacterSkinPreviewMaterial>>> TextureSelectionComboBox;`
- L43 _private member_ `TArray<TSharedPtr<EMetaHumanCharacterSkinPreviewMaterial>> TextureSelectionOptions;`
- L44 _private member_ `TArray<TSharedPtr<FString>> MeshTypeOptions;`
- L45 _private member_ `FString SelectedMeshType;`
- L46 _private member_ `TSharedPtr<EMetaHumanCharacterSkinPreviewMaterial> CurrentTextureSelection;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorAccentRegionsPanel.h` (Private)


#### struct `FMetaHumanCharacterEditorAccentRegionInfo`  
`struct FMetaHumanCharacterEditorAccentRegionInfo`  
_L14-21_
- desc: Struct used for holding informations of an Accent Region.
- L16 _public member_ `EMetaHumanCharacterAccentRegion Type;`
- L17 _public member_ `FName Name;`
- L18 _public member_ `FText Label;`
- L19 _public member_ `FVector2D Position;`
- L20 _public member_ `FVector2D Size;`

#### class `SMetaHumanCharacterEditorAccentRegionsPanel`  
`class SMetaHumanCharacterEditorAccentRegionsPanel : public SCompoundWidget`  
_L36-73_
- inherits: `SCompoundWidget`
- desc: Widget used to display the Skin Accent Regions. This widget is created from check boxes since they can display brushes for checked and hovered states The brushes for each check box are defined in the style class FMetaHumanCharacterEditorStyle so each region check box just need to reference the style and the correct images are going to be used. This widget is completely passive, meaning it doesn't hold any selection state. The selected region is defined by an attribute that each check box can use to compare if it should be in the checked state or not The widget has two main parts, the background Head image and the regions the user can click. The regions are built using an SCanvas, which is a widget that allows anchoring its child widgets as well set custom sizes for each
- L39 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorAccentRegionsPanel) : _SelectedRegion(EMetaHumanCharacterAccentRegion::Scalp)`
- L42 _public prototype_ `SLATE_ATTRIBUTE(EMetaHumanCharacterAccentRegion, SelectedRegion) SLATE_EVENT(FOnRegionClicked, OnRegionClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `EMetaHumanCharacterAccentRegion GetSelectedRegion() const;` — Gets the currently selected Accent Region.
- L54 _private prototype_ `void MakeAccentRegionsCanvas(const TArray<FMetaHumanCharacterEditorAccentRegionInfo> AccentRegionsInfos);` — Makes the Accent Regions main canvas widget.
- L57 _private prototype_ `TArray<FMetaHumanCharacterEditorAccentRegionInfo> CreateAccentRegionsInfoArray() const;` — Creates the array of Accent Regions info used to correctly create the widget.
- L60 _private prototype_ `ECheckBoxState IsRegionSelected(EMetaHumanCharacterAccentRegion InRegion) const;` — Gets the check box state which tells if a specific Accent Region is selected or not.
- L63 _private prototype_ `void OnRegionCheckedStateChanged(ECheckBoxState InState, EMetaHumanCharacterAccentRegion InRegion);` — Called when the check box state of a specific Accent Region has been changed.
- L66 _private member_ `FOnRegionClicked RegionClickedDelegate;` — Delegate executed when the user clicks on a region.
- L69 _private member_ `TSharedPtr<SCanvas> AccentRegionsCanvas;` — Reference to the Accent Regions canvas.
- L72 _private member_ `TAttribute<EMetaHumanCharacterAccentRegion> SelectedRegion;` — Attribute used to query the selected region.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRegionClicked, EMetaHumanCharacterAccentRegion) struct FMetaHumanCharacterEditorAccentRegionInfo { EMetaHumanCharacterAccentRegion Type; FName Name; FText Label; FVector2D Position; FVector2D Size; };`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorAssetViewsPanel.h` (Private)


#### struct `FMetaHumanCharacterAssetViewsPanelStatus`  
`struct FMetaHumanCharacterAssetViewsPanelStatus`  
_L27-32_
- desc: Struct used to store the asset views panel status parameters.
- L29 _public member_ `FName ToolViewName;`
- L30 _public member_ `FText FilterText;`
- L31 _public member_ `bool bShowFolders = false;`

#### struct `FMetaHumanCharacterAssetViewStatus`  
`struct FMetaHumanCharacterAssetViewStatus`  
_L35-45_
- desc: Struct used to store the asset view status.
- L37 _public prototype_ `FMetaHumanCharacterAssetViewStatus();`
- L39 _public member_ `FString Label;`
- L40 _public member_ `FString SlotLabel;`
- L41 _public member_ `float ScrollOffset = 0.f;`
- L42 _public member_ `bool bIsExpanded = true;`
- L43 _public member_ `bool bIsSlotExpanded = true;`
- L44 _public member_ `TArray<FSoftObjectPath> SelectedItemsPaths;`

#### struct `FMetaHumanCharacterAssetViewItem`  
`struct FMetaHumanCharacterAssetViewItem`  
_L48-64_
- desc: Struct used to represent an asset view item.
- L50 _public prototype_ `FMetaHumanCharacterAssetViewItem(const FAssetData& InAssetData, const FName& InSlotName, const FMetaHumanPaletteItemKey& InPaletteItemKey, TSharedPtr<FAssetThumbnailPool> InAssetThumbnailPool, bool bInIsValid);`
- L55 _public prototype_ `~FMetaHumanCharacterAssetViewItem();`
- L57 _public member_ `FAssetData AssetData;`
- L58 _public member_ `FName SlotName;`
- L59 _public member_ `FMetaHumanPaletteItemKey PaletteItemKey;`
- L60 _public member_ `TSharedPtr<FAssetThumbnail> Thumbnail;`
- L61 _public member_ `TSharedPtr<FDeferredCleanupSlateBrush> ThumbnailImageOverride;`
- L62 _public member_ `EMetaHumanCharacterThumbnailCameraPosition ThumbnailType = EMetaHumanCharacterThumbnailCameraPosition::Face;`
- L63 _public member_ `bool bIsValid = true;`

#### class `FMetaHumanCharacterAssetViewItemDragDropOp`  
`class FMetaHumanCharacterAssetViewItemDragDropOp : public FAssetDragDropOp`  
_L67-74_
- inherits: `FAssetDragDropOp`
- desc: Drag drop action whick allow to hold data about asset view items.
- L70 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMetaHumanCharacterAssetViewItemDragDropOp, FAssetDragDropOp) TSharedPtr<FMetaHumanCharacterAssetViewItem> AssetItem;`
- L73 _public prototype_ `static TSharedRef<FMetaHumanCharacterAssetViewItemDragDropOp> New(FAssetData AssetData, UActorFactory* ActorFactory, TSharedPtr<FMetaHumanCharacterAssetViewItem> AssetItem);`

#### class `SMetaHumanCharacterAssetViewItem`  
`class SMetaHumanCharacterAssetViewItem : public SCompoundWidget`  
_L97-283_
- inherits: `SCompoundWidget`
- desc: Widget that represents an asset view item in a tile view.
- L100 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterAssetViewItem) : _ShowThumbnailType(false)`
- L105 _public prototype_ `SLATE_ARGUMENT(bool, ShowThumbnailType) SLATE_ARGUMENT(TSharedPtr<FMetaHumanCharacterAssetViewItem>, AssetItem) SLATE_ARGUMENT(TSharedPtr<FAssetThumbnail>, AssetThumbnail) SLATE_ARGUMENT(FIsSelected, IsSelected) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsChecked) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsAvailable) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsActive) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnOverrideThumbnail) SLATE_EVENT(FMetaHumanCharacterOnOverrideThumbnailName, OnOverrideThumbnailName) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnDeleted) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, CanDelete) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnDeletedFolder) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, CanDeleteFolder) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnApplyHeadOnly)` — True if the thumbnail type toggle should be shown in the item.
- L155 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L156 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L157 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L158 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L159 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L160 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L165 _private prototype_ `TSharedRef<SWidget> GenerateThumbnailWidget();` — Generates the thumbnail widget for this item.
- L168 _private prototype_ `TSharedRef<SWidget> GenerateAssetItemContextMenu();` — Generates the context menu for this item.
- L171 _private prototype_ `void OnApplyHeadOnlyClicked();` — Executes the OnApplyHeadOnly delegate for this item.
- L174 _private prototype_ `void OnApplyBodyOnlyClicked();` — Executes the OnApplyBodyOnly delegate for this item.
- L177 _private function_ `FName GetContextMenuName() const` — Gets the context menu unique name.
- L180 _private prototype_ `const FSlateBrush* GetAssetAreaOverlayBackgroundImage() const;` — Gets the asset area overlay background brush.
- L183 _private prototype_ `const FSlateBrush* GetNameAreaBackgroundImage() const;` — Gets the name area background brush.
- L186 _private prototype_ `const FSlateBrush* GetThumbnailImageOverrideBrush() const;` — Gets the thumbnail image brush.
- L189 _private prototype_ `FSlateColor GetNameAreaTextColor() const;` — Gets the color for the name area text.
- L192 _private prototype_ `FText GetThumbnailName() const;` — Gets the thumbnail name for current item
- L195 _private prototype_ `bool IsItemDirty() const;` — True is the item asset is dirty.
- L198 _private prototype_ `bool IsItemChecked() const;` — True is the item asset is checked.
- L201 _private prototype_ `bool IsItemAvailable() const;` — True is the item asset is available.
- L204 _private prototype_ `bool IsItemActive() const;` — True is the item asset is active.
- L207 _private prototype_ `ECheckBoxState GetThumbnailTypeCheckState() const;` — Gets the thumbnail type check state.
- L210 _private prototype_ `void OnThumbnailTypeCheckStateChanged(ECheckBoxState NewState);` — Called when the thumbnail type check state is changed.
- L213 _private prototype_ `EVisibility GetAssetColorVisibility() const;` — Gets the visibility of the thumbnail chip border image.
- L216 _private prototype_ `EVisibility GetDirtyIconVisibility() const;` — Gets the visibility of the dirty state icon.
- L219 _private prototype_ `EVisibility GetCheckedIconVisibility() const;` — Gets the visibility of the checked state icon.
- L222 _private prototype_ `EVisibility GetAvailableIconVisibility() const;` — Gets the visibility of the available state icon.
- L225 _private prototype_ `EVisibility GetActiveIconVisibility() const;` — Gets the visibility of the active state icon.
- L228 _private prototype_ `EVisibility GetStatesOverlayBorderVisibility() const;` — Gets the visibility of the states overlay border.
- L231 _private prototype_ `EVisibility GetThumbnailTypeCheckBoxVisibility() const;` — Gets the visibility of the thumbnail type check box.
- L234 _private member_ `FIsSelected IsSelected;` — The delegate to execute to get wether the item is selected in the view.
- L237 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsChecked;` — The delegate to execute to get the item checked state.
- L240 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsAvailable;` — The delegate to execute to get the item available state.
- L243 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsActive;` — The delegate to execute to get the item active state.
- L246 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnOverrideThumbnailDelegate;` — The delegate to execute to get thumbnail brushes overrides.
- L249 _private member_ `FMetaHumanCharacterOnOverrideThumbnailName OnOverrideThumbnailNameDelegate;` — The delegate to execute to get thumbnail name overrides
- L252 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnDeletedDelegate;` — The delegate to execute when this item is deleted.
- L255 _private member_ `FMetaHumanCharacterEditorOnGetItemState CanDeleteDelegate;` — The delegate to execute to get wheter this item can be deleted.
- L258 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnDeletedFolderDelegate;` — The delegate to execute when the owner folder of this item is deleted.
- L261 _private member_ `FMetaHumanCharacterEditorOnGetItemState CanDeleteFolderDelegate;` — The delegate to execute to get wheter the owner folder of this item can be deleted.
- L264 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnApplyHeadOnlyDelegate;` — The delegate to execute when "Apply Head Only" is selected from the context menu.
- L267 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnApplyBodyOnlyDelegate;` — The delegate to execute when "Apply Body Only" is selected from the context menu.
- L270 _private member_ `TSharedPtr<SWidget> Thumbnail;` — Reference to the thumbnail widget.
- L273 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — Reference to the thumbnail that this item is rendering
- L276 _private member_ `TSharedPtr<FMetaHumanCharacterAssetViewItem> AssetItem;` — The asset view item this widget is based on
- L279 _private member_ `bool bDraggedOver = false;` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L282 _private member_ `bool bShowThumbnailType = false;` — True if the thumbnail type toggle should be shown in the item.

#### class `SMetaHumanCharacterEditorAssetsView`  
`class SMetaHumanCharacterEditorAssetsView : public SCompoundWidget`  
_L286-574_
- inherits: `SCompoundWidget`
- desc: Displays assets in the observed asset section as tile view.
- L289 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorAssetsView) : _SelectionMode(ESelectionMode::Single) , _SlotName(NAME_None) , _MaxHeight(320.f) , _AutoHeight(false) , _AllowDragging(true) , _AllowDropping(false) , _ShowThumbnailType(false) , _HasVirtualFolder(false)`
- L301 _public prototype_ `SLATE_ARGUMENT(TArray<FMetaHumanCharacterAssetsSection>, Sections) SLATE_ARGUMENT(TArray<TWeakObjectPtr<UObject>>, ExcludedObjects) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(FName, SlotName) SLATE_ARGUMENT(FString, Label) SLATE_ARGUMENT(float, MaxHeight) SLATE_ARGUMENT(bool, AutoHeight) SLATE_ARGUMENT(bool, AllowDragging) SLATE_ARGUMENT(bool, AllowDropping) SLATE_ARGUMENT(bool, ShowThumbnailType) SLATE_ARGUMENT(bool, HasVirtualFolder) SLATE_ARGUMENT(TSharedPtr<SWidget>, AssetViewToolPanel) SLATE_ARGUMENT(TSharedPtr<SWidget>, SlotToolPanel) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnOverrideThumbnail)` — The assets sections this view is based on.
- L376 _public prototype_ `SLATE_EVENT(FMetaHumanCharacterEditorOnGetSectionState, IsItemCompatible) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemChecked) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemAvailable) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemActive) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyHeadOnly) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyBodyOnly) SLATE_END_ARGS() SMetaHumanCharacterEditorAssetsView();` — Called to get whether the item is compatible with a section.
- L399 _public prototype_ `~SMetaHumanCharacterEditorAssetsView();` — Destructor.
- L402 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget.
- L405 _public prototype_ `TArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>> GetSelectedItems() const;` — Gets the array of selected items of the view.
- L408 _public prototype_ `TArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>> GetItems() const;` — Gets the array of items of the view.
- L411 _public function_ `FString GetLabel() const` — Gets the name label of the view.
- L414 _public function_ `FName GetSlotName() const` — Gets the slot name label of the view.
- L417 _public function_ `TSharedPtr<SWidget> GetAssetViewToolPanel() const` — Gets the tool panel that contains this asset view.
- L420 _public function_ `TSharedPtr<SWidget> GetSlotToolPanel() const` — Gets the slot tool panel that contains this asset view.
- L423 _public prototype_ `float GetScrollOffset() const;` — Gets the current scroll offset of the view.
- L426 _public prototype_ `void SetScrollOffset(float InScrollOffset);` — Sets the scroll offset of the view.
- L429 _public prototype_ `bool IsExpanded() const;` — Gets the current expansions state of this asset view.
- L432 _public prototype_ `void SetExpanded(bool bExpand);` — Sets the expansion state of the view.
- L435 _public prototype_ `bool IsSlotExpanded() const;` — Gets the current expansions state of the slot this asset view belongs.
- L438 _public prototype_ `void SetSlotExpanded(bool bExpand);` — Sets the expansion state of the slot this view belongs.
- L441 _public prototype_ `void PopulateListItems(const FMetaHumanObserverChanges& InChanges);` — Populates the list items array.
- L444 _public prototype_ `void SetFilter(const FText& InNewSearchText);` — Sets the text filter for the view.
- L447 _public prototype_ `void SetItemSelection(TSharedPtr<FMetaHumanCharacterAssetViewItem> InItem, bool bSelected, ESelectInfo::Type SelectInfo);` — Sets the given item as selected, if valid.
- L450 _public prototype_ `void ClearSelection();` — Clears the selection.
- L453 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L454 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L455 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L456 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L461 _private prototype_ `bool IsAssetFiltered(const TSharedPtr<FMetaHumanCharacterAssetViewItem>& InAssetItem) const;` — True if the given asset data needs to be filtered.
- L464 _private prototype_ `TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<FMetaHumanCharacterAssetViewItem> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;` — Called each time an asset view tile is generated.
- L467 _private prototype_ `void OnDeletedFolder(TSharedPtr<FMetaHumanCharacterAssetViewItem> InItem) const;` — Called when a folder has been deleted.
- L470 _private prototype_ `bool CanDeleteFolder(TSharedPtr<FMetaHumanCharacterAssetViewItem> InItem) const;` — Called to get whether a folder can be deleted or not.
- L473 _private prototype_ `FReply OnDraggingAssetItem(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;` — Called when an asset view item is being dragged.
- L476 _private prototype_ `EVisibility GetDroppingAreaVisibility() const;` — Gets the visibility of the dropping area widgets.
- L479 _private prototype_ `void HandleVirtualFolderAsset(const FAssetData& AssetData);` — Handles the assets in the VirtualFolderItems array.
- L482 _private prototype_ `UObject* SaveAssetToSectionFolder(const FAssetData& AssetData, const FString& FolderPath, bool bAllowMoving = false);` — Saves an asset in the given folder path, if valid.
- L485 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnOverrideThumbnailDelegate;` — The delegate to execute to get thumbnail brushes overrides.
- L488 _private member_ `FMetaHumanCharacterOnOverrideThumbnailName OnOverrideThumbnailNameDelegate;` — The delegate to execute to get thumbnail name overrides
- L491 _private member_ `FMetaHumanCharacterEditorOnProcessAssetData OnProcessDroppedItemDelegate;` — The delegate to execute to process a dropped item, before checking if it matches class requirements.
- L494 _private member_ `FMetaHumanCharacterEditorOnProcessFolders OnProcessDroppedFoldersDelegate;` — The delegate to execute to process an array of dropped folder.
- L497 _private member_ `FMetaHumanCharacterEditorOnPopulateItems OnPopulateItemsDelegate;` — The delegate to execute when asset views are populated.
- L500 _private member_ `FMetaHumanCharacterEditorOnItemSelectionChanged OnSelectionChangedDelegate;` — The delegate to execute when asset views selection has changed.
- L503 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemActivatedDelegate;` — The delegate to execute when an item is activated.
- L506 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemDeletedDelegate;` — The delegate to execute when an item is deleted.
- L509 _private member_ `FMetaHumanCharacterEditorOnGetItemState CanDeleteItemDelegate;` — The delegate to execute to get whether an item can be deleted.
- L512 _private member_ `FMetaHumanCharacterEditorAssetViewSectionDelegate OnFolderDeletedDelegate;` — The delegate to execute when a folder is deleted.
- L515 _private member_ `FMetaHumanCharacterEditorOnGetSectionState CanDeleteFolderDelegate;` — The delegate to execute to get whether a folder can be deleted.
- L518 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnHandleVirtualItemDelegate;` — The delegate to execute when an item is added to the virtual assets folder.
- L521 _private member_ `FMetaHumanCharacterEditorOnGetSectionState IsItemCompatible;` — The delegate to execute to get whether the item is compatible with a section.
- L524 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemChecked;` — The delegate to execute to get the item checked state.
- L527 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemAvailable;` — The delegate to execute to get the item available state.
- L530 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemActive;` — The delegate to execute to get the item active state.
- L533 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyHeadOnlyDelegate;` — The delegate to execute when "Apply Head Only" is selected from an item's context menu.
- L536 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyBodyOnlyDelegate;` — The delegate to execute when "Apply Body Only" is selected from an item's context menu.
- L539 _private member_ `FDelegateHandle SubscriberHandle;` — Keeps track of the subscriber handle to the directory observer.
- L542 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;` — Reference to the asset thumbnail pool used for creating item thumbnails.
- L545 _private member_ `TSharedRef<UE::Slate::Containers::TObservableArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>>> ListItems;` — The array of items displayed in the asset view.
- L548 _private member_ `TSharedPtr<STileView<TSharedPtr<FMetaHumanCharacterAssetViewItem>>> TileView;` — Reference to the displayed tile view.
- L551 _private member_ `TWeakPtr<SWidget> AssetViewToolPanel;` — Reference to the tool panel that contains this asset view.
- L554 _private member_ `TWeakPtr<SWidget> SlotToolPanel;` — Reference to the slot tool panel that contains this asset view.
- L557 _private member_ `FString SearchText;` — The text filter currently applied.
- L560 _private member_ `bool bDraggedOver = false;` — True when a drag is over this item with a drag operation that we know how to handle. The operation itself may not be valid to drop.
- L563 _private member_ `TArray<FMetaHumanCharacterAssetsSection> Sections;` — Slate Arguments.
- L564 _private member_ `TArray<TWeakObjectPtr<UObject>> ExcludedObjects;`
- L565 _private member_ `ESelectionMode::Type SelectionMode = ESelectionMode::Type::Single;`
- L566 _private member_ `FName SlotName;`
- L567 _private member_ `FString Label;`
- L568 _private member_ `float MaxHeight;`
- L569 _private member_ `bool bAutoHeight;`
- L570 _private member_ `bool bAllowDragging;`
- L571 _private member_ `bool bAllowDropping;`
- L572 _private member_ `bool bShowThumbnailType;`
- L573 _private member_ `bool bHasVirtualFolder;`

#### class `SMetaHumanCharacterEditorAssetViewsPanel`  
`class SMetaHumanCharacterEditorAssetViewsPanel : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L577-866_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Displays a selection of assets from specified folders into sorted into editor asset views.
- L582 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorAssetViewsPanel) : _AutoHeight(false) , _AllowDragging(true) , _AllowSlots(true) , _AllowMultiSelection(false) , _AllowSlotMultiSelection(true) , _ShowThumbnailType(false)`
- L592 _public prototype_ `SLATE_ATTRIBUTE(TArray<FMetaHumanCharacterAssetsSection>, AssetViewSections) SLATE_ARGUMENT(TArray<TWeakObjectPtr<UObject>>, ExcludedObjects) SLATE_ARGUMENT(TArray<TSubclassOf<UObject>>, VirtualFolderClassesToFilter) SLATE_ARGUMENT(bool, AutoHeight) SLATE_ARGUMENT(bool, AllowDragging) SLATE_ARGUMENT(bool, AllowSlots) SLATE_ARGUMENT(bool, AllowMultiSelection) SLATE_ARGUMENT(bool, AllowSlotMultiSelection) SLATE_ARGUMENT(bool, ShowThumbnailType) SLATE_EVENT(FNewToolMenuSectionDelegate, OnGetCustomMenuOptions) SLATE_EVENT(FMetaHumanCharacterEditorOnOverrideName, OnOverrideSlotName) SLATE_EVENT(FMetaHumanCharacterOnOverrideThumbnailName, OnOverrideThumbnailName) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnOverrideThumbnail) SLATE_EVENT(FMetaHumanCharacterEditorOnProcessAssetData, OnProcessDroppedItem)` — The array of sections used for creating asset views.
- L661 _public prototype_ `SLATE_EVENT(FMetaHumanCharacterEditorOnGetSectionState, IsItemCompatible) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemChecked) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemAvailable) SLATE_EVENT(FMetaHumanCharacterEditorOnGetItemState, IsItemActive) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyHeadOnly) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyBodyOnly) SLATE_END_ARGS() ~SMetaHumanCharacterEditorAssetViewsPanel();` — Called to get whether the item is compatible with a section.
- L684 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget.
- L687 _public prototype_ `TArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>> GetAllItems() const;` — Gets the array of all asset view items of this panel.
- L690 _public prototype_ `TArray<TSharedPtr<FMetaHumanCharacterAssetViewItem>> GetSelectedItems() const;` — Gets the array of selected asset view items of this panel.
- L693 _public prototype_ `TSharedPtr<SMetaHumanCharacterEditorAssetsView> GetOwnerAssetView(TSharedPtr<FMetaHumanCharacterAssetViewItem> InSelectedItem) const;` — Gets the owner asset view of the given item, if valid.
- L696 _public prototype_ `FMetaHumanCharacterAssetViewsPanelStatus GetAssetViewsPanelStatus() const;` — Gets the status parameters of this panel.
- L699 _public prototype_ `TArray<FMetaHumanCharacterAssetViewStatus> GetAssetViewsStatusArray() const;` — Gets an array of all the asset views status parameters.
- L702 _public prototype_ `void UpdateAssetViewsPanelStatus(const FMetaHumanCharacterAssetViewsPanelStatus& Status);` — Sets the status of the panel according to the given parameters.
- L705 _public prototype_ `void UpdateAssetViewsStatus(const TArray<FMetaHumanCharacterAssetViewStatus>& StatusArray);` — Sets the status of the asset views according to the given map.
- L708 _public prototype_ `void RequestRefresh();` — Requests the refreshing of the panel.
- L711 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L715 _public prototype_ `static UTexture2D* LoadThumbnailAsTextureFromAssetData(const FAssetData& InAssetData, EMetaHumanCharacterThumbnailCameraPosition InCameraPosition);` — Loads the thumbnail of an asset as a texture, using the given camera position.
- L719 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L720 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L725 _private prototype_ `void MakeAssetViewsPanel();` — Makes the asset views panel, using the stored parameters.
- L728 _private prototype_ `TSharedRef<SWidget> GenerateAssetViewsSlot(const FName& SlotName);` — Generates an asset view slot with the given slot name.
- L731 _private prototype_ `TSharedRef<SWidget> GenerateAssetView(const TArray<FMetaHumanCharacterAssetsSection>& Sections, const FName& SlotName, const TSharedPtr<SWidget>& AssetViewToolPanel = nullptr, const TSharedPtr<SWidget>& SlotToolPanel = nullptr, bool bHasVirtualFolder = false);` — Generates an asset view slot with the given slot name.
- L734 _private prototype_ `TSharedRef<SWidget> GenerateSectionToolbar() const;` — Generates the toolbar for an asset view section.
- L737 _private prototype_ `TSharedRef<SWidget> GenerateSettingsMenuWidget();` — Generates the settings menu widget for this panel.
- L740 _private prototype_ `FString GenerateAssetViewNameLabel(const TArray<FMetaHumanCharacterAssetsSection>& Sections, const FName& SlotName, bool bHasVirtualFolder = false) const;` — Generates an asset view name label using the given parameters.
- L743 _private prototype_ `void PopulateSlotNames();` — Populates the slot names array.
- L746 _private prototype_ `TArray<FMetaHumanCharacterAssetsSection> GetSectionsBySlotName(const FName& SlotName) const;` — Gets the owner section of the slot with the given slot name.
- L749 _private function_ `FName GetSettingsMenuName() const` — Gets the settings menu unique name.
- L752 _private prototype_ `void OnSearchBoxTextChanged(const FText& InText);` — Called when the search box text has changed.
- L755 _private prototype_ `void OnItemSelectionChanged(TSharedPtr<FMetaHumanCharacterAssetViewItem> InSelectedItem, ESelectInfo::Type InSelectInfo);` — Called when the item selection of and asset view has changed.
- L758 _private prototype_ `void OnThumbnailTypeChanged();` — Called when the thumbnail type has changed.
- L761 _private prototype_ `void OnSetCharacterThumbnailType(EMetaHumanCharacterThumbnailCameraPosition NewThumbnailType);` — Called when the user changes the thumbnail type to be displayed for the character.
- L764 _private prototype_ `ECheckBoxState IsCharacterThumbnailTypeChecked(EMetaHumanCharacterThumbnailCameraPosition ThumbnailType) const;` — Gets the check state of the given thumbnail type.
- L767 _private prototype_ `void OpenProjectSettings();` — Opens the project settings menu.
- L770 _private prototype_ `void ToggleShowFolders();` — Toggles the show folders option state.
- L773 _private prototype_ `void Refresh();` — Refreshes the panel asset views widgets.
- L776 _private prototype_ `static UTexture2D* ThumbnailToTexture(const class FObjectThumbnail* InThumbnailObject);` — Gets the thumbnail texture from a given thumbnail object.
- L779 _private member_ `FNewToolMenuSectionDelegate OnGetCustomMenuOptionsDelegate;` — The delegate to execute to add custom menu options.
- L782 _private member_ `FMetaHumanCharacterEditorOnOverrideName OnOverrideSlotNameDelegate;` — The delegate to execute to get slot names overrides.
- L785 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnOverrideThumbnailDelegate;` — The delegate to execute to get thumbnail brushes overrides.
- L788 _private member_ `FMetaHumanCharacterOnOverrideThumbnailName OnOverrideThumbnailNameDelegate;` — The delegate to execute to get thumbnail name overrides
- L791 _private member_ `FMetaHumanCharacterEditorOnProcessAssetData OnProcessDroppedItemDelegate;` — The delegate to execute to process a dropped item, before checking if it matches class requirements.
- L794 _private member_ `FMetaHumanCharacterEditorOnProcessFolders OnProcessDroppedFoldersDelegate;` — The delegate to execute to process an array of dropped folder.
- L797 _private member_ `FMetaHumanCharacterEditorOnPopulateItems OnPopulateAssetViewsItemsDelegate;` — The delegate to execute when asset views are populated.
- L800 _private member_ `FMetaHumanCharacterEditorOnItemSelectionChanged OnSelectionChangedDelegate;` — The delegate to execute when asset views selection has changed.
- L803 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemActivatedDelegate;` — The delegate to execute when an item is activated.
- L806 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemDeletedDelegate;` — The delegate to execute when an item is deleted.
- L809 _private member_ `FMetaHumanCharacterEditorOnGetItemState CanDeleteItemDelegate;` — The delegate to execute to get whether an item can be deleted.
- L812 _private member_ `FMetaHumanCharacterEditorAssetViewSectionDelegate OnFolderDeletedDelegate;` — The delegate to execute when a folder is deleted.
- L815 _private member_ `FMetaHumanCharacterEditorOnGetSectionState CanDeleteFolderDelegate;` — The delegate to execute to get whether a folder can be deleted.
- L818 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnHandleVirtualItemDelegate;` — The delegate to execute when an item is added to the virtual assets folder.
- L821 _private member_ `FMetaHumanCharacterEditorOnGetSectionState IsItemCompatible;` — The delegate to execute to get whether the item is compatible with a section.
- L824 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemChecked;` — The delegate to execute to get the item checked state.
- L827 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemAvailable;` — The delegate to execute to get the item available state.
- L830 _private member_ `FMetaHumanCharacterEditorOnGetItemState IsItemActive;` — The delegate to execute to get the item active state.
- L833 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyHeadOnlyDelegate;` — The delegate to execute when "Apply Head Only" is selected from an item's context menu.
- L836 _private member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyBodyOnlyDelegate;` — The delegate to execute when "Apply Body Only" is selected from an item's context menu.
- L839 _private member_ `FTimerHandle RefreshAssetViewsTimerHandle;` — Timer handle used when asset views refresh is requested.
- L842 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Reference to the search box used for filtering assets.
- L845 _private member_ `TSharedPtr<SVerticalBox> AssetViewSlotsBox;` — Reference to the box container widget for the asset views slots.
- L848 _private member_ `TArray<TSharedPtr<SMetaHumanCharacterEditorAssetsView>> AssetViews;` — The array of asset views displayed in the panel.
- L851 _private member_ `TArray<FName> AssetViewsSlotNames;` — The array of slot names used for creating slots.
- L854 _private member_ `bool bShowFolders = false;` — True to show sections as single folders.
- L857 _private member_ `TAttribute<TArray<FMetaHumanCharacterAssetsSection>> AssetViewSections;` — Slate arguments.
- L858 _private member_ `TArray<TWeakObjectPtr<UObject>> ExcludedObjects;`
- L859 _private member_ `TArray<TSubclassOf<UObject>> VirtualFolderClassesToFilter;`
- L860 _private member_ `bool bAutoHeight;`
- L861 _private member_ `bool bAllowDragging;`
- L862 _private member_ `bool bAllowSlots;`
- L863 _private member_ `bool bAllowMultiSelection;`
- L864 _private member_ `bool bAllowSlotMultiSelection;`
- L865 _private member_ `bool bShowThumbnailType;`

#### Free symbols / members of external scopes

- L76 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FMetaHumanCharacterEditorOnOverrideName, const FName&);`
- L76 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FMetaHumanCharacterEditorOnOverrideName, const FName&);`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FMetaHumanCharacterOnOverrideThumbnailName, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L78 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FMetaHumanCharacterOnOverrideThumbnailName, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L80 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TArray<FMetaHumanCharacterAssetViewItem>, FMetaHumanCharacterEditorOnPopulateItems, const FMetaHumanCharacterAssetsSection&, const FMetaHumanObserverChanges&);`
- L80 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TArray<FMetaHumanCharacterAssetViewItem>, FMetaHumanCharacterEditorOnPopulateItems, const FMetaHumanCharacterAssetsSection&, const FMetaHumanObserverChanges&);`
- L82 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UObject*, FMetaHumanCharacterEditorOnProcessAssetData, const FAssetData&);`
- L82 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UObject*, FMetaHumanCharacterEditorOnProcessAssetData, const FAssetData&);`
- L84 _delegate_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterEditorOnProcessFolders, const TArray<FContentBrowserItem>, const FMetaHumanCharacterAssetsSection&);`
- L84 _prototype_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterEditorOnProcessFolders, const TArray<FContentBrowserItem>, const FMetaHumanCharacterAssetsSection&);`
- L86 _delegate_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterEditorOnItemSelectionChanged, TSharedPtr<FMetaHumanCharacterAssetViewItem> , ESelectInfo::Type );`
- L86 _prototype_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterEditorOnItemSelectionChanged, TSharedPtr<FMetaHumanCharacterAssetViewItem> , ESelectInfo::Type );`
- L88 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterEditorAssetViewItemDelegate, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L88 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterEditorAssetViewItemDelegate, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L90 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterEditorAssetViewSectionDelegate, const FMetaHumanCharacterAssetsSection& );`
- L90 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterEditorAssetViewSectionDelegate, const FMetaHumanCharacterAssetsSection& );`
- L92 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FMetaHumanCharacterEditorOnGetItemState, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L92 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FMetaHumanCharacterEditorOnGetItemState, TSharedPtr<FMetaHumanCharacterAssetViewItem> );`
- L94 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FMetaHumanCharacterEditorOnGetSectionState, TSharedPtr<FMetaHumanCharacterAssetViewItem> , const FMetaHumanCharacterAssetsSection& );`
- L94 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FMetaHumanCharacterEditorOnGetSectionState, TSharedPtr<FMetaHumanCharacterAssetViewItem> , const FMetaHumanCharacterAssetsSection& );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorBlendToolPanel.h` (Private)


#### class `SMetaHumanCharacterEditorBlendToolThumbnail`  
`class SMetaHumanCharacterEditorBlendToolThumbnail : public SCompoundWidget`  
_L26-99_
- inherits: `SCompoundWidget`
- desc: Widget used to display asset thumbnails for the Blend Tool.
- L29 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorBlendToolThumbnail)`
- L33 _public prototype_ `SLATE_EVENT(FMetaHumanCharacterOnBlendToolThumbnailContentSet, OnItemContentSet) SLATE_EVENT(FMetaHumanCharacterOnBlendToolThumbnailContentDeleted, OnItemDeleted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, int32 InItemIndex);` — Called when an item's content is set in this widget.
- L44 _public prototype_ `FAssetData GetThumbnailAssetData() const;` — Gets the asset data displayed by this widget.
- L47 _public prototype_ `void SetContent(const TSharedPtr<FMetaHumanCharacterAssetViewItem>& InAssetItem);` — Sets the content of this thumbnail widget from the given asset item.
- L51 _protected prototype_ `virtual void OnDragEnter(const FGeometry & MyGeometry, const FDragDropEvent & DragDropEvent) override;`
- L52 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L53 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L59 _private prototype_ `TSharedRef<SWidget> GenerateThumbnailWidget(TSharedPtr<FMetaHumanCharacterAssetViewItem> AssetItem);` — Generates the thumbnail widget for this item.
- L62 _private prototype_ `FReply OnDeleteButtonClicked();` — Called when the delete button is clicked.
- L65 _private prototype_ `EVisibility GetDeleteButtonVisibility() const;` — Gets the visibility of the delete button.
- L68 _private prototype_ `const FSlateBrush* GetBorderBrush() const;` — Gets the border brush of this widget.
- L71 _private prototype_ `FText GetThumbnailNameAsText() const;` — Gets the thumbnail name label as a text.
- L74 _private member_ `FMetaHumanCharacterOnBlendToolThumbnailContentSet OnItemContentSetDelegate;` — The delegate to execute when an item's content is set in this widget.
- L77 _private member_ `FMetaHumanCharacterOnBlendToolThumbnailContentDeleted OnItemDeletedDelegate;` — The delegate to execute when an item is deleted in this widget.
- L80 _private member_ `const FSlateBrush* DefaultBrush;` — The default brush used by this widget.
- L83 _private member_ `const FSlateBrush* SelectedBrush;` — The brush used when this widget is selected.
- L86 _private member_ `bool bIsDragging = false;` — True if a drag and drop operation is on.
- L89 _private member_ `TSharedPtr<FAssetThumbnailPool> ThumbnailPool;` — Reference to the thumbnail pool used by this widget thumbnail.
- L92 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — Reference to the asset thumbnail displayed by this widget.
- L95 _private member_ `TSharedPtr<SBox> ThumbnailContainerBox;` — Reference to the thumbnail container box widget.
- L98 _private member_ `int32 ItemIndex;` — Index of the thumbnail within the thumbnail panel

#### class `SMetaHumanCharacterEditorBlendToolPanel`  
`class SMetaHumanCharacterEditorBlendToolPanel : public SCompoundWidget`  
_L102-218_
- inherits: `SCompoundWidget`
- desc: Widget used to display the Blend Tool and its properties widgets in the MetaHumanCharacter editor.
- L105 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorBlendToolPanel) : _VirtualFolderSlotName(NAME_None)`
- L110 _public prototype_ `SLATE_ARGUMENT(FName, VirtualFolderSlotName) SLATE_EVENT(FMetaHumanCharacterOnBlendToolThumbnailContentSet, OnItemContentSet) SLATE_EVENT(FMetaHumanCharacterOnBlendToolThumbnailContentDeleted, OnItemDeleted) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemActivated) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnOverrideItemThumbnail) SLATE_EVENT(FMetaHumanCharacterFilterAssetData, OnFilterAssetData) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyHeadOnly) SLATE_EVENT(FMetaHumanCharacterEditorAssetViewItemDelegate, OnItemApplyBodyOnly) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetaHumanCharacter* InCharacter, UMetaHumanCharacterEditorMeshBlendTool* InBlendTool);` — Name identifier used for handling operations with virtual assets.
- L139 _public function_ `TSharedPtr<SMetaHumanCharacterEditorAssetViewsPanel> GetAssetViewsPanel() const` — Gets a reference to the asset views panel.
- L142 _public prototype_ `TArray<FAssetData> GetBlendableItems() const;` — Gets the array of current blendable items displayed by this panel.
- L145 _public prototype_ `void RestorePresets(const TArray<TSoftObjectPtr<UMetaHumanCharacter>>& InPresets);` — Restores thumbnail content from saved soft object pointers.
- L148 _public member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemActivatedDelegate;` — The delegate to execute when an item is double clicked in this widget.
- L151 _public member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnOverrideItemThumbnailDelegate;` — The delegate to execute to override the item thumbnail brush.
- L154 _public member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyHeadOnlyDelegate;` — The delegate to execute when "Apply Head Only" is selected from an item's context menu.
- L157 _public member_ `FMetaHumanCharacterEditorAssetViewItemDelegate OnItemApplyBodyOnlyDelegate;` — The delegate to execute when "Apply Body Only" is selected from an item's context menu.
- L159 _public member_ `FMetaHumanCharacterFilterAssetData OnFilterAssetDataDelegate;`
- L163 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> GetCharacterIndividualAssets() const;` — Gets and array of items containing the stored Character individual assets.
- L166 _private prototype_ `TArray<FMetaHumanCharacterAssetsSection> GetAssetViewsSections() const;` — Gets the sections array for the wardrobe asset views panel.
- L169 _private prototype_ `TArray<FMetaHumanCharacterAssetViewItem> OnPopulateAssetViewsItems(const FMetaHumanCharacterAssetsSection& InSection, const FMetaHumanObserverChanges& InChanges);` — Called when to populate asset views with items.
- L172 _private prototype_ `void OnProcessDroppedFolders(const TArray<FContentBrowserItem> Items, const FMetaHumanCharacterAssetsSection& InSection) const;` — Called to process an array of dropped folders in the asset views panel.
- L175 _private prototype_ `void OnBlendToolVirtualItemDeleted(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been deleted.
- L178 _private prototype_ `bool CanDeleteBlendToolVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item) const;` — True if the given item can be deleted.
- L181 _private prototype_ `void OnPresetsPathsFolderDeleted(const FMetaHumanCharacterAssetsSection& InSection);` — Called when the folder has been deleted.
- L184 _private prototype_ `bool CanDeletePresetsPathsFolder(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item, const FMetaHumanCharacterAssetsSection& InSection) const;` — True if the given folder can be deleted.
- L187 _private prototype_ `void OnHandleBlendVirtualItem(TSharedPtr<FMetaHumanCharacterAssetViewItem> Item);` — Called when the given item has been moved in a virtual folder.
- L190 _private prototype_ `void OnPresetsDirectoriesChanged();` — Called when the Project Settings selected directory paths have been changed.
- L193 _private prototype_ `FReply OnCameraFocusButtonPressed(bool bShouldFocusFace);` — Called when the user presses the camera button to focus either face or body
- L196 _private prototype_ `FReply OnSavePresetButtonClicked();` — Called when the Save Preset button is clicked.
- L199 _private member_ `TArray<TSharedPtr<SMetaHumanCharacterEditorBlendToolThumbnail>> BlendToolThumbnails;` — The array of available thumbnails in this panel.
- L202 _private prototype_ `FReply OnResetHeadButtonClicked();` — Reset the head to its default state.
- L205 _private prototype_ `FReply OnResetBodyButtonClicked();` — Reset the body to its default state.
- L208 _private member_ `TSharedPtr<SMetaHumanCharacterEditorAssetViewsPanel> AssetViewsPanel;` — Reference to this Asset Views panel.
- L211 _private member_ `TWeakObjectPtr<UMetaHumanCharacter> CharacterWeakPtr;` — Reference to the Character this panel is based on.
- L214 _private member_ `TWeakObjectPtr<UMetaHumanCharacterEditorMeshBlendTool> BlendToolWeakPtr;` — Reference to the Blend Tool, used for reset operations.
- L217 _private member_ `FName VirtualFolderSlotName;` — Slate arguments.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterOnBlendToolThumbnailContentSet, const FAssetData&, int32);`
- L21 _prototype_ `DECLARE_DELEGATE_TwoParams(FMetaHumanCharacterOnBlendToolThumbnailContentSet, const FAssetData&, int32);`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterOnBlendToolThumbnailContentDeleted, int32);`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterOnBlendToolThumbnailContentDeleted, int32);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FMetaHumanCharacterFilterAssetData, const FAssetData&);`
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FMetaHumanCharacterFilterAssetData, const FAssetData&);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorColorPalettePicker.h` (Private)


#### enum `EColorPalettePickerMode`  
`enum class EColorPalettePickerMode : uint8`  
_L17-21_
- desc: The available color palette picker modes.
- L19 _public enumerator_ `Preset`
- L20 _public enumerator_ `Custom`

#### class `SMetaHumanCharacterEditorColorPaletteTile`  
`class SMetaHumanCharacterEditorColorPaletteTile : public SCompoundWidget`  
_L24-76_
- inherits: `SCompoundWidget`
- desc: Widget that displays a single color palette tile.
- L27 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorColorPaletteTile) : _Color(FLinearColor::Transparent) , _TileIndex(INDEX_NONE) , _UseSRGBInColorBlock(true) , _IsSelected(false)`
- L35 _public prototype_ `SLATE_ARGUMENT(FLinearColor, Color) SLATE_ARGUMENT(int32, TileIndex) SLATE_ARGUMENT(bool, UseSRGBInColorBlock) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FOnColorTileSelected, OnTileSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The color displayed by the tile.
- L55 _public function_ `const FLinearColor& GetColor() const` — Gets the tile color.
- L58 _public function_ `bool IsSelected() const` — True if this tile is selected.
- L62 _private prototype_ `FReply OnTileClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Called when this tile is clicked.
- L65 _private prototype_ `const FSlateBrush* GetTileBorderBrush() const;` — Gets the tile border brush according to its state.
- L68 _private prototype_ `FOptionalSize GetTileSize() const;` — Gets the tile size according to its state.
- L71 _private member_ `FOnColorTileSelected OnTileSelectedDelegate;` — Slate Arguments
- L72 _private member_ `FLinearColor Color;`
- L73 _private member_ `int32 TileIndex = INDEX_NONE;`
- L75 _private member_ `TAttribute<bool> bIsSelectedAttribute;`

#### class `SMetaHumanCharacterEditorColorPalette`  
`class SMetaHumanCharacterEditorColorPalette : public SCompoundWidget`  
_L82-141_
- inherits: `SCompoundWidget`
- desc: Widget that displays a color palette made of palette tiles. It allows selecting a color from the palette.
- L85 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorColorPalette) : _PaletteDefaultColor(FLinearColor::Transparent) , _SelectedColor(FLinearColor::Transparent) , _PaletteRows(5) , _PaletteColumns(7) , _UseSRGBInColorBlock(true)`
- L93 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, PaletteDefaultColor) SLATE_ATTRIBUTE(FLinearColor, SelectedColor) SLATE_ARGUMENT(uint32, PaletteRows) SLATE_ARGUMENT(uint32, PaletteColumns) SLATE_ARGUMENT(bool, UseSRGBInColorBlock) SLATE_EVENT(FOnColorTileSelected, OnPaletteTileSelected) SLATE_EVENT(FOnComputeVariantColor, OnComputeVariantColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The default color used for deriving the palette colors from.
- L120 _private prototype_ `void MakeColorPalette();` — Makes the color palette deriving the colors from the DefaultColor.
- L123 _private prototype_ `void OnColorSelectionChanged(FLinearColor InColor, int32 TileIndex = INDEX_NONE);` — Called when the selected color has changed.
- L126 _private member_ `TArray<TSharedPtr<SMetaHumanCharacterEditorColorPaletteTile>> PaletteTiles;` — The array of tiles of the palette.
- L129 _private member_ `TSharedPtr<SUniformGridPanel> GridPanel;` — The grid panel of the palette.
- L132 _private member_ `TAttribute<FLinearColor> DefaultColor;` — Slate Attributes
- L133 _private member_ `TAttribute<FLinearColor> SelectedColor;`
- L136 _private member_ `FOnColorTileSelected OnPaletteTileSelectedDelegate;` — Slate Arguments
- L137 _private member_ `FOnComputeVariantColor OnComputeVariantColorDelegate;`
- L138 _private member_ `uint32 PaletteRows;`
- L139 _private member_ `uint32 PaletteColumns;`
- L140 _private member_ `bool bUseSRGBInColorBlock;`

#### class `SMetaHumanCharacterEditorColorPalettePicker`  
`class SMetaHumanCharacterEditorColorPalettePicker : public SCompoundWidget`  
_L148-254_
- inherits: `SCompoundWidget`
- desc: Widget that displays a color block that when clicked creates a pop-up window that allows the user to select a color from a multi-modal widget.
- L151 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorColorPalettePicker) : _PaletteDefaultColor(FLinearColor::Transparent) , _SelectedColor(FLinearColor::Transparent) , _PaletteLabel(NSLOCTEXT("SMetaHumanCharacterEditorColorPalettePicker", "PalettePickerLabel", "Palette Picker")) , _PaletteColumns(7) , _PaletteRows(5) , _ColorPickerTexture`
- L162 _public prototype_ `SLATE_ATTRIBUTE(FLinearColor, PaletteDefaultColor) SLATE_ATTRIBUTE(FLinearColor, SelectedColor) SLATE_ATTRIBUTE(FText, PaletteLabel) SLATE_ARGUMENT(int32, PaletteColumns) SLATE_ARGUMENT(int32, PaletteRows) SLATE_ATTRIBUTE(FText, ULabelOverride) SLATE_ATTRIBUTE(FText, VLabelOverride) SLATE_ARGUMENT(class UTexture2D*, ColorPickerTexture) SLATE_ARGUMENT(bool, UseSRGBInColorBlock) SLATE_EVENT(FOnColorTileSelected, OnPaletteColorSelectionChanged) SLATE_EVENT(FOnComputeVariantColor, OnComputeVariantColor) SLATE_END_ARGS() virtual ~SMetaHumanCharacterEditorColorPalettePicker() override;` — The default color used for deriving the palette colors from.
- L198 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the widget.
- L202 _private prototype_ `TSharedRef<SWidget> GenerateCustomTextureUVPicker();` — Generates a texture UV picker, if the ColorPickerTexture is valid.
- L205 _private prototype_ `FReply OnColorBlockClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Called when the color block is clicked.
- L208 _private prototype_ `void OnPalettePickerModeChanged(EColorPalettePickerMode NewMode);` — Called when the mode of the palette picker has changed.
- L211 _private prototype_ `void OnPaletteColorSelectionChanged(FLinearColor InColor, int32 InTileIndex = INDEX_NONE);` — Called when the selected color of the palette picker has changed.
- L214 _private prototype_ `void OnTextureUVChanged(const FVector2f& InUV, bool bInIsDragging);` — Called when the texture's UV coordinates of the UV picker have changed.
- L217 _private prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& InWindow);` — Called when the picker window has been closed.
- L220 _private prototype_ `EVisibility GetColorPalettePickerModeVisibility(EColorPalettePickerMode InMode) const;` — Gets the visibility of the pickers, according to the given palette picker mode.
- L223 _private member_ `TAttribute<FVector2f> TextureUV;` — The current texture UV value.
- L226 _private member_ `FImage TextureImageData;` — The image data of the given ColorPickerTexture, if valid.
- L229 _private member_ `EColorPalettePickerMode Mode = EColorPalettePickerMode::Preset;` — The current palette picker mode.
- L232 _private member_ `TSharedPtr<class SCustomColorPicker> CustomColorPicker;` — The custom color picker widget
- L235 _private member_ `TSharedPtr<SMetaHumanCharacterEditorColorPalette> ColorPalette;` — The color palette widget.
- L238 _private member_ `TSharedPtr<SWindow> Window;` — The main window to display the color palette picker.
- L241 _private member_ `TAttribute<FLinearColor> DefaultColor;` — Slate Attributes
- L242 _private member_ `TAttribute<FLinearColor> SelectedColor;`
- L243 _private member_ `TAttribute<FText> Label;`
- L244 _private member_ `TAttribute<FText> ULabelOverride;`
- L245 _private member_ `TAttribute<FText> VLabelOverride;`
- L248 _private member_ `FOnColorTileSelected OnPaletteColorSelectionChangedDelegate;` — Slate Arguments
- L249 _private member_ `FOnComputeVariantColor OnComputeVariantColorDelegate;`
- L250 _private member_ `TStrongObjectPtr<UTexture2D> ColorPickerTexture;`
- L251 _private member_ `bool bUseSRGBInColorBlock;`
- L252 _private member_ `int32 NumPaletteColumns;`
- L253 _private member_ `int32 NumPaletteRows;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnColorTileSelected, FLinearColor Color, int32 TileIndex);`
- L13 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnColorTileSelected, FLinearColor Color, int32 TileIndex);`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_SixParams(FLinearColor, FOnComputeVariantColor, const FLinearColor& InColor, int32 InColorIndex, int32 InShowColumns, int32 InShowRows, float InSaturationShift, float InValueShift);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_SixParams(FLinearColor, FOnComputeVariantColor, const FLinearColor& InColor, int32 InColorIndex, int32 InShowColumns, int32 InShowRows, float InSaturationShift, float InValueShift);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorComboBox.h` (Private)


#### class `SMetaHumanCharacterEditorComboBox`  
`template<typename TEnum> class SMetaHumanCharacterEditorComboBox : public SCompoundWidget`  
_L12-227_
- inherits: `SCompoundWidget`
- desc: This class is used as a custom ComboBox for MetaHuman Character purposes Requirements for using it are having an Enum for options which the ComboBox will represent
- L15 _public typedef_ `using FEnumType = typename std::underlying_type<TEnum>::type;`
- L17 _public function_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorComboBox<TEnum>)`
- L24 _public function_ `SLATE_ATTRIBUTE(TEnum, CurrentValue) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorComboBox<TEnum>::FArguments& InArgs)` — The currently selected item of the Combo Box. Note: This will also be used as InitiallySelectedItem during Construct
- L77 _public function_ `void SetSelectedItem(TEnum InItem, const bool bExecuteOnSelectionChanged = true) const` — Sets the selected combo box item and executes selection change callback if bound and bExecuteOnSelectionChanged is true
- L110 _private function_ `FText GetEnumNameText(int64 EnumIndex) const` — Gets the Enum name by the given index.
- L117 _private function_ `FText GetEnumToolTipText(int64 EnumIndex) const` — Gets the Enum name by the given index.
- L124 _private function_ `FText GetSelectedEnumNameAsText() const` — Gets the name of the currently selected Enum as text.
- L137 _private function_ `FText GetSelectedEnumToolTipAsText() const` — Gets the name of the currently selected Enum as text.
- L150 _private function_ `TArray<TSharedPtr<TEnum>> GetEnumOptions()` — Gets the array of all Enum options from the given UEnum.
- L182 _private function_ `TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<TEnum>InItem)` — Generated the Combo Box widget for the given item.
- L198 _private function_ `void OnComboBoxSelectionChanged(TSharedPtr<TEnum> InItem, ESelectInfo::Type InSelectInfo)` — Called when the combo box selection has changed.
- L207 _private function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`
- L218 _private member_ `FOnSelectionChanged OnSelectionChanged;` — The delegate to execute when the selection of the Combo Box has changed.
- L220 _private member_ `TAttribute<TEnum> CurrentValue;`
- L223 _private member_ `TArray<TSharedPtr<TEnum>> ComboBoxOptions;` — The array of Combo Box options.
- L226 _private member_ `TSharedPtr<SComboBox<TSharedPtr<TEnum>>> ComboBox;` — Reference to the Combo Box widget.

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorComboBox<TEnum>) {} SLATE_ATTRIBUTE(TEnum, CurrentValue) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorComboBox<TEnum>::FArguments& InArgs) { OnSelectionChanged = InArgs._OnSelectionChanged; CurrentValue = InArgs._CurrentValue; ComboBoxOptions = GetEnumOptions(); check(CurrentValue.IsSet()); check(OnSelectionChanged.IsBound()); check(!ComboBoxOptions.IsEmpty()); TSharedPtr<TEnum> InitiallySelectedItem = nullptr; for (const TSharedPtr<TEnum>& ItemPtr : ComboBoxOptions) { if (!ItemPtr.IsValid()) { continue; } const TEnum Item = *ItemPtr.Get(); if (Item == CurrentValue.Get()) { InitiallySelectedItem = ItemPtr; break; } }`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorFixedCompatibilityPanel.h` (Private)


#### class `SMetaHumanCharacterEditorFixedCompatibilityPanel`  
`class SMetaHumanCharacterEditorFixedCompatibilityPanel : public SCompoundWidget`  
_L11-40_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorFixedCompatibilityPanel)`
- L20 _public prototype_ `SLATE_ARGUMENT(UMetaHumanCharacterFixedCompatibilityBodyProperties*, FixedCompatabilityProperties) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void UpdateItemListFromProperties();`
- L32 _private prototype_ `int32 GetHeightValue() const;`
- L33 _private prototype_ `void OnHeightValueChanged(int32 HeightValue);`
- L34 _private prototype_ `const FSlateBrush* GetFixedCompatabilityBodyBrush(uint8 InItem);`
- L36 _private member_ `TWeakObjectPtr<UMetaHumanCharacterFixedCompatibilityBodyProperties> FixedCompatabilityProperties;`
- L37 _private member_ `TSharedPtr<SMetaHumanCharacterEditorTileView<EMetaHumanBodyType>> TileView;`
- L39 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) public: SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorFixedCompatibilityPanel) {} SLATE_ARGUMENT(UMetaHumanCharacterFixedCompatibilityBodyProperties*, FixedCompatabilityProperties) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorParametricView.h` (Private)


#### class `SMetaHumanCharacterEditorParametricSpinBox`  
`template<typename NumericType> class SMetaHumanCharacterEditorParametricSpinBox : public SCompoundWidget`  
_L16-82_
- inherits: `SCompoundWidget`
- L20 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnValueChanged, NumericType , bool bCommit);` — Notification for numeric value change
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FText>, FOnGetDisplayValue, NumericType);` — Optional customization of the display value based on the current value.
- L26 _public function_ `SLATE_BEGIN_ARGS( SMetaHumanCharacterEditorParametricSpinBox<NumericType> ) : _MinValue(TNumericLimits<NumericType>::Lowest()) , _MaxValue(TNumericLimits<NumericType>::Max())`
- L32 _public prototype_ `SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_ATTRIBUTE(FText, ToolTip) SLATE_STYLE_ARGUMENT( FSpinBoxStyle, SpinBoxStyle ) SLATE_ARGUMENT( bool, IsEnabled ) SLATE_ATTRIBUTE( NumericType, Value ) SLATE_ATTRIBUTE( NumericType, MinValue ) SLATE_ATTRIBUTE( NumericType, MaxValue ) SLATE_EVENT( FOnValueChanged, OnValueChanged ) SLATE_EVENT( FSimpleDelegate, OnBeginSliderMovement ) SLATE_EVENT( FOnValueChanged, OnEndSliderMovement ) SLATE_EVENT(FOnGetDisplayValue, OnGetDisplayValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Font color and opacity
- L61 _private prototype_ `float GetSliderValue() const;`
- L62 _private prototype_ `void OnSliderValueChanged(float NewValue, bool bCommit) const;`
- L63 _private prototype_ `void OnSliderValueCommitted(float NewValue, ETextCommit::Type CommitType) const;`
- L64 _private prototype_ `FText GetOutputValueText() const;`
- L65 _private prototype_ `TOptional<FText> GetDisplayText(float Value) const;`
- L68 _private member_ `TAttribute<NumericType> ValueAttribute;` — Attribute for getting the value.
- L70 _private member_ `FOnValueChanged OnValueChanged;` — Delegate to call when the value changes
- L72 _private member_ `FOnGetDisplayValue OnGetDisplayValue;` — Delegate to get display text
- L74 _private member_ `const float SliderDistance = 100.f;`
- L75 _private member_ `const float SliderMinValue = 0.0f;`
- L76 _private member_ `const float SliderMaxValue = 100.f;`
- L77 _private member_ `TAttribute<NumericType> MinValue = 0.0;`
- L78 _private member_ `TAttribute<NumericType> MaxValue = 100.0;`
- L80 _private member_ `TSharedPtr<INumericTypeInterface<NumericType>> InterfaceAttr;`
- L81 _private member_ `TSharedPtr<SSpinBox<float>> SpinBox;`

#### class `SMetaHumanCharacterEditorParametricConstraintView`  
`class SMetaHumanCharacterEditorParametricConstraintView : public SCompoundWidget`  
_L85-139_
- inherits: `SCompoundWidget`
- desc: Displays a widget for a parametric constraint in body parametric tool
- L88 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnParametricConstraintChanged, float TargetMeasurement, bool bIsPinned, bool bCommit);`
- L91 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorParametricConstraintView) : _IsEnabled(true)`
- L95 _public prototype_ `SLATE_ATTRIBUTE(float, TargetMeasurement) SLATE_ATTRIBUTE(float, ActualMeasurement) SLATE_ATTRIBUTE(bool, IsPinned) SLATE_ARGUMENT(EVisibility, PinVisibility) SLATE_ARGUMENT(bool, IsEnabled) SLATE_ARGUMENT(FName, ConstraintName) SLATE_ATTRIBUTE(float, MinValue) SLATE_ATTRIBUTE(float, MaxValue) SLATE_EVENT(FSimpleDelegate, OnBeginConstraintEditing) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(FText, ToolTip) SLATE_EVENT(FOnParametricConstraintChanged, OnParametricConstraintChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L126 _private prototype_ `TOptional<FText> GetDisplayText(float TargetValue) const;`
- L127 _private prototype_ `float GetParametricValue() const;`
- L128 _private prototype_ `void OnBeginConstraintEditing() const;`
- L129 _private prototype_ `void OnConstraintTargetChanged(const float Value, bool bCommit) const;`
- L130 _private prototype_ `ECheckBoxState GetConstraintChecked() const;`
- L131 _private prototype_ `void OnConstraintPinnedChanged(ECheckBoxState CheckState) const;`
- L133 _private member_ `FName ConstraintName;`
- L134 _private member_ `TAttribute<float> TargetMeasurement;`
- L135 _private member_ `TAttribute<float> ActualMeasurement;`
- L136 _private member_ `TAttribute<bool> IsPinned;`
- L137 _private member_ `FSimpleDelegate OnBeginConstraintEditingDelegate;`
- L138 _private member_ `FOnParametricConstraintChanged OnParametricConstraintChangedDelegate;`

#### class `SMetaHumanCharacterEditorParametricConstraintsPanel`  
`class SMetaHumanCharacterEditorParametricConstraintsPanel : public SCompoundWidget`  
_L141-179_
- inherits: `SCompoundWidget`
- L144 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnConstraintChanged, bool );`
- L147 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorParametricConstraintsPanel) : _ListItemsSource(nullptr) , _Padding(FMargin(0.f))`
- L152 _public prototype_ `SLATE_ARGUMENT(const TArray<FMetaHumanCharacterBodyConstraintItemPtr>*, ListItemsSource) SLATE_ARGUMENT(bool, DiagnosticsView) SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_EVENT(FSimpleDelegate, OnBeginConstraintEditing) SLATE_EVENT(FOnConstraintChanged, OnConstraintsChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L168 _private prototype_ `TSharedRef<ITableRow> MakeConstraintRowWidget(FMetaHumanCharacterBodyConstraintItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L169 _private prototype_ `void OnGroupPinCheckStateChanged(ECheckBoxState CheckState);`
- L170 _private prototype_ `void OnBeginConstraintEditing();`
- L171 _private prototype_ `void OnConstraintChanged(bool bCommit);`
- L172 _private prototype_ `ECheckBoxState GetGroupPinCheckState() const;`
- L174 _private member_ `TSharedPtr<SListView<FMetaHumanCharacterBodyConstraintItemPtr>> ListView;`
- L175 _private member_ `TArray<FMetaHumanCharacterBodyConstraintItemPtr> ItemsSource;`
- L176 _private member_ `FSimpleDelegate OnBeginConstraintEditingDelegate;`
- L177 _private member_ `FOnConstraintChanged OnConstraintsChangedDelegate;`
- L178 _private member_ `bool DiagnosticView = false;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnValueChanged, NumericType , bool bCommit);` — Notification for numeric value change
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FText>, FOnGetDisplayValue, NumericType);` — Optional customization of the display value based on the current value.
- L88 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnParametricConstraintChanged, float TargetMeasurement, bool bIsPinned, bool bCommit);`
- L144 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConstraintChanged, bool );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorTeethSlidersPanel.h` (Private)


#### class `SMetaHumanCharacterEditorTeethSlider`  
`class SMetaHumanCharacterEditorTeethSlider : public SCompoundWidget`  
_L19-79_
- inherits: `SCompoundWidget`
- desc: Slider used for specifically handling the teeth properties value change.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTeethSlider) : _MinValue(0.f) , _MaxValue(1.f) , _Orientation(EOrientation::Orient_Horizontal)`
- L29 _public prototype_ `SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(float, MinValue) SLATE_ARGUMENT(float, MaxValue) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FOnTeethSliderValueChanged, OnValueChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A value that drives where the slider handle appears.
- L53 _private prototype_ `void OnValueChanged(float NewValue);` — Called when the value of the slider changes.
- L56 _private prototype_ `void OnMouseCaptureBegin();` — Called when mouse capture on the slider begins.
- L59 _private prototype_ `void OnMouseCaptureEnd();` — Called when mouse capture on the slider ends.
- L62 _private prototype_ `const FSlateBrush* GetElipseBrush() const;` — Gets the slider's elipse brush.
- L65 _private prototype_ `EVisibility GetArrowVisibility() const;` — Gets the visibility of slider's arrow.
- L68 _private member_ `TSharedPtr<SSlider> Slider;` — Reference to this widget's slider.
- L71 _private member_ `bool bIsDragging = false;` — True if the slider is being dragged.
- L74 _private member_ `FOnTeethSliderValueChanged OnValueChangedDelegate;` — Slate arguments.
- L75 _private member_ `FSimpleDelegate OnMouseCaptureBeginDelegate;`
- L76 _private member_ `EOrientation Orientation;`
- L77 _private member_ `float MinValue;`
- L78 _private member_ `float MaxValue;`

#### class `SMetaHumanCharacterEditorTeethSlidersPanel`  
`class SMetaHumanCharacterEditorTeethSlidersPanel : public SCompoundWidget`  
_L82-125_
- inherits: `SCompoundWidget`
- desc: Widget used to display the Teeth Sliders for the different editable properties.
- L85 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTeethSlidersPanel)`
- L89 _public prototype_ `SLATE_EVENT(FOnGetTeethSliderPropertyValue, OnGetTeethSliderValue) SLATE_EVENT(FOnTeethSliderPropertyValueChanged, OnTeethSliderValueChanged) SLATE_EVENT(FOnTeethSliderPropertyEdited, OnTeethSliderPropertyEdited) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Called to get the teeth slider value.
- L104 _private prototype_ `void MakeTeethSlidersCanvas();` — Makes the Teeth Slider main canvas widget.
- L107 _private prototype_ `TSharedRef<SWidget> CreateTeethPropertySlider(FProperty* Property, EOrientation Orientation);` — Creates the slider for showing the Teeth properties.
- L110 _private prototype_ `float GetTeethSliderValue(FProperty* Property) const;` — Gets the value of the teeth slider assigned to the given property.
- L113 _private prototype_ `void OnTeethSliderValueChanged(const float Value, bool bIsInteractive, FProperty* Property);` — Called when the value of a teeth slider has changed.
- L116 _private prototype_ `void OnTeethSliderMouseCaptureBegin(FProperty* Property);` — Called when the mouse capture of a teeth slider begins.
- L119 _private member_ `TSharedPtr<SConstraintCanvas> TeethSlidersCanvas;` — Reference to the canvas which contains all the Teeth Sliders.
- L122 _private member_ `FOnGetTeethSliderPropertyValue OnGetTeethSliderPropertyValueDelegate;` — Slate arguments.
- L123 _private member_ `FOnTeethSliderPropertyValueChanged OnTeethSliderValueChangedDelegate;`
- L124 _private member_ `FOnTeethSliderPropertyEdited OnTeethSliderPropertyEditedDelegate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<float>, FOnGetTeethSliderPropertyValue, FProperty*);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<float>, FOnGetTeethSliderPropertyValue, FProperty*);`
- L14 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnTeethSliderPropertyValueChanged, float InValue, bool bInIsInteractive, FProperty*);`
- L14 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnTeethSliderPropertyValueChanged, float InValue, bool bInIsInteractive, FProperty*);`
- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTeethSliderValueChanged, float InValue, bool bInIsInteractive);`
- L15 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnTeethSliderValueChanged, float InValue, bool bInIsInteractive);`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTeethSliderPropertyEdited, FProperty*);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTeethSliderPropertyEdited, FProperty*);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorTextComboBox.h` (Private)


#### class `SMetaHumanCharacterEditorTextComboBox`  
`class SMetaHumanCharacterEditorTextComboBox : public SCompoundWidget`  
_L10-64_
- inherits: `SCompoundWidget`
- desc: This class is used as a custom ComboBox containing texture labels for MetaHuman Character purposes
- L13 _public function_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, int32) DECLARE_DELEGATE_OneParam(FOnSelectionChangedItem, const FString&) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTextComboBox)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FText, PlaceholderText) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnSelectionChangedItem, OnSelectionChangedItem) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTextComboBox::FArguments& InArgs, const TArray<TSharedPtr<FString>>& InComboBoxOptions, const TSharedPtr<FString>& InInitiallySelectedItem);` — Placeholder text when no option is selected.
- L32 _public prototype_ `void SetSelectedItem(const int32 InIdx);`
- L34 _public prototype_ `void SetOptions(const TArray<TSharedPtr<FString>>& InComboBoxOptions);`
- L36 _public prototype_ `void ClearSelection() const;`
- L42 _private prototype_ `TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);` — Generated the Combo Box widget for the given item.
- L45 _private prototype_ `void OnComboBoxSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);` — Called when the combo box selection has changed.
- L48 _private prototype_ `FText GetSelectedItemAsText() const;` — Gets the name of the currently selected item as text.
- L51 _private member_ `FOnSelectionChanged OnSelectionChanged;` — The delegate to execute when the selection of the Combo Box has changed.
- L54 _private member_ `FOnSelectionChangedItem OnSelectionChangedItem;` — The delegate to execute when the selection of the Combo Box has changed.
- L57 _private member_ `TArray<TSharedPtr<FString>> ComboBoxOptions;` — The array of Combo Box options.
- L60 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;` — Reference to the Combo Box widget.
- L63 _private member_ `TAttribute<FText> PlaceholderText;` — Placeholder text when no option is selected.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, int32) DECLARE_DELEGATE_OneParam(FOnSelectionChangedItem, const FString&) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTextComboBox) {} SLATE_ATTRIBUTE(FText, PlaceholderText) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnSelectionChangedItem, OnSelectionChangedItem) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTextComboBox::FArguments& InArgs, const TArray<TSharedPtr<FString>>& InComboBoxOptions, const TSharedPtr<FString>& InInitiallySelectedItem);`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChangedItem, const FString&) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTextComboBox) {} SLATE_ATTRIBUTE(FText, PlaceholderText) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnSelectionChangedItem, OnSelectionChangedItem) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTextComboBox::FArguments& InArgs, const TArray<TSharedPtr<FString>>& InComboBoxOptions, const TSharedPtr<FString>& InInitiallySelectedItem);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorTileView.h` (Private)


#### class `SMetaHumanCharacterEditorTileView`  
`template<typename TEnum> class SMetaHumanCharacterEditorTileView : public SCompoundWidget`  
_L17-195_
- inherits: `SCompoundWidget`
- desc: This class is used as a custom TileView for MetaHuman Character purposes Requirements for using it are having an Enum for options which the TileView will represent and TileView needs to be inside of a DetailsView so that PropertyHandle can be passed
- L20 _public typedef_ `using FEnumType = std::underlying_type_t<TEnum>;`
- L22 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FOnGetSlateBrush, uint8) DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTileView<TEnum>) : _IsFocusable(true)`
- L30 _public function_ `SLATE_ATTRIBUTE(bool, IsFocusable) SLATE_ATTRIBUTE(TEnum, InitiallySelectedItem) SLATE_ARGUMENT(TArray<TEnum>, ExcludedItems) SLATE_EVENT(FOnGetSlateBrush, OnGetSlateBrush) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTileView<TEnum>::FArguments& InArgs)` — True when the list view supports keyboard focus
- L98 _public function_ `void SetItemsSource(const TArray<TEnum>& InEnumItems, TEnum SelectedItem)` — Sets custom item list
- L124 _public function_ `TSharedPtr<STileView<TSharedPtr<TEnum>>> GetTileView() const`
- L129 _public function_ `const TArray<TSharedPtr<TEnum>>& GetTileViewItems() const`
- L134 _public function_ `void ClearSelection()`
- L144 _private function_ `TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<TEnum>InItem, const TSharedRef<class STableViewBase>& InOwnerTable) const` — Called to generate the Tile View's tile widgets.
- L168 _private function_ `void OnTileSelectionChanged(TSharedPtr<TEnum> InItem, ESelectInfo::Type InSelectInfo)` — Called when the selection of the Tile View has changed.
- L182 _private member_ `FOnSelectionChanged OnSelectionChanged;` — The delegate to execute when the selection of the Tile View has changed.
- L185 _private member_ `FOnGetSlateBrush OnGetSlateBrush;` — The delegate to execute to get the brush to display for a specific Tile View item.
- L188 _private member_ `TArray<TSharedPtr<TEnum>> TileViewItems;` — The array of Tile View items.
- L191 _private member_ `TArray<TEnum> ExcludedItems;` — The array of items that should be exclueded from the Tile View.
- L194 _private member_ `TSharedPtr<STileView<TSharedPtr<TEnum>>> TileView;` — Reference to the Tile View widget.

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FSlateBrush*, FOnGetSlateBrush, uint8) DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTileView<TEnum>) : _IsFocusable(true) {} SLATE_ATTRIBUTE(bool, IsFocusable) SLATE_ATTRIBUTE(TEnum, InitiallySelectedItem) SLATE_ARGUMENT(TArray<TEnum>, ExcludedItems) SLATE_EVENT(FOnGetSlateBrush, OnGetSlateBrush) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTileView<TEnum>::FArguments& InArgs) { OnGetSlateBrush = InArgs._OnGetSlateBrush; OnSelectionChanged = InArgs._OnSelectionChanged; check(OnGetSlateBrush.IsBound()); check(OnSelectionChanged.IsBound()); ExcludedItems = InArgs._ExcludedItems; const TEnum InitiallySelectedItem = InArgs._InitiallySelectedItem.IsSet() ? InArgs._InitiallySelectedItem.Get() : static_cast<TEnum>(0); TSharedPtr<TEnum> InitialItem = nullptr; TileViewItems.Empty();`
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, uint8) SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorTileView<TEnum>) : _IsFocusable(true) {} SLATE_ATTRIBUTE(bool, IsFocusable) SLATE_ATTRIBUTE(TEnum, InitiallySelectedItem) SLATE_ARGUMENT(TArray<TEnum>, ExcludedItems) SLATE_EVENT(FOnGetSlateBrush, OnGetSlateBrush) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const typename SMetaHumanCharacterEditorTileView<TEnum>::FArguments& InArgs) { OnGetSlateBrush = InArgs._OnGetSlateBrush; OnSelectionChanged = InArgs._OnSelectionChanged; check(OnGetSlateBrush.IsBound()); check(OnSelectionChanged.IsBound()); ExcludedItems = InArgs._ExcludedItems; const TEnum InitiallySelectedItem = InArgs._InitiallySelectedItem.IsSet() ? InArgs._InitiallySelectedItem.Get() : static_cast<TEnum>(0); TSharedPtr<TEnum> InitialItem = nullptr; TileViewItems.Empty();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SMetaHumanCharacterEditorToolPanel.h` (Private)


#### enum `EMetaHumanCharacterEditorPanelHierarchyLevel`  
`enum class EMetaHumanCharacterEditorPanelHierarchyLevel : uint8`  
_L13-18_
- desc: Enum used to represent the tool panel hierarchy level.
- L15 _public enumerator_ `Top`
- L16 _public enumerator_ `Middle`
- L17 _public enumerator_ `Low`

#### class `SMetaHumanCharacterEditorArrowButton`  
`class SMetaHumanCharacterEditorArrowButton : public SCompoundWidget`  
_L21-54_
- inherits: `SCompoundWidget`
- desc: Button which allows to show an expanded/collapsed state.
- L24 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorArrowButton) : _IsExpanded(true)`
- L29 _public prototype_ `SLATE_ARGUMENT(bool, IsExpanded) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — True if this button is in expand state
- L37 _public function_ `bool IsExpanded() const` — Gets whether this button is in expanded state
- L40 _public function_ `void SetExpanded(bool bExpand)` — Sets the expansion state of this button
- L44 _private prototype_ `FReply OnArrowButtonClicked();` — Called when this button is clicked.
- L47 _private prototype_ `const FSlateBrush* GetArrowButtonImage() const;` — Gets the brush for this Button, according to the current state.
- L50 _private member_ `TSharedPtr<SButton> Button;` — Reference to the Button widget.
- L53 _private member_ `bool bIsExpanded = true;` — True if this button is in expand state

#### class `SMetaHumanCharacterEditorToolPanel`  
`class SMetaHumanCharacterEditorToolPanel : public SCompoundWidget`  
_L57-154_
- inherits: `SCompoundWidget`
- desc: Widget used to display tools and their properties widgets in the MetaHumanCharacter editor.
- L62 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCharacterEditorToolPanel) : _Content() , _HeaderContent() , _HierarchyLevel(EMetaHumanCharacterEditorPanelHierarchyLevel::Top) , _RoundedBorders(true) , _IsExpanded(true) , _Padding(FMargin(0.f))`
- L72 _public function_ `SLATE_ATTRIBUTE(FText, Label) SLATE_ATTRIBUTE(const FSlateBrush*, IconBrush) SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_NAMED_SLOT(FArguments, HeaderContent) SLATE_ARGUMENT(EMetaHumanCharacterEditorPanelHierarchyLevel, HierarchyLevel) SLATE_ARGUMENT(bool, RoundedBorders) SLATE_ARGUMENT(bool, IsExpanded) SLATE_ATTRIBUTE(FMargin, Padding) FArguments& Padding(float Uniform)` — The panel's top level text label.
- L101 _public function_ `FArguments& Padding(float Horizontal, float Vertical)`
- L107 _public function_ `FArguments& Padding(float Left, float Top, float Right, float Bottom)`
- L113 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L119 _public prototype_ `bool IsExpanded() const;` — Gets whether this panel is in expanded state
- L122 _public prototype_ `void SetExpanded(bool bExpand);` — Sets the expansion state of this panel
- L125 _public prototype_ `FText GetLabel() const;` — Gets the label text of this panel
- L128 _public prototype_ `void SetContent(const TSharedRef<SWidget>& InContent);` — Sets the content of this panel
- L132 _private prototype_ `const FSlateBrush* GetPanelBorderBrush() const;` — Gets the panel border brush, according to the RoundedBorders attribute.
- L135 _private prototype_ `EVisibility GetContentSlotVisibility() const;` — Gets the visibility of the content slot, according to the arrow button state.
- L138 _private member_ `TSharedPtr<SMetaHumanCharacterEditorArrowButton> ArrowButton;` — Reference to the Arrow Button of the panel.
- L141 _private member_ `TSharedPtr<SBox> ContentBox;` — The box container of this panel content.
- L144 _private member_ `EMetaHumanCharacterEditorPanelHierarchyLevel HierarchyLevel = EMetaHumanCharacterEditorPanelHierarchyLevel::Top;` — The hierarchy level of this panel.
- L147 _private member_ `TAttribute<FText> LabelAttribute;` — The panel's top level text label attribute.
- L150 _private member_ `TAttribute<const FSlateBrush*> IconBrushAttribute;` — The slate brush to draw for the ImageAttribute that we can invalidate.
- L153 _private member_ `bool bRoundedBorders = true;` — True if the panel should has rounded borders.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/UI/Widgets/SUVColorPicker.h` (Private)


#### class `SUVColorSwatch`  
`class SUVColorSwatch : public SCompoundWidget`  
_L15-68_
- inherits: `SCompoundWidget`
- desc: Widget that displays a texture used as a color swatch. It allows selecting a UV withing the swatch area
- L18 _public function_ `SLATE_BEGIN_ARGS(SUVColorSwatch)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(FVector2f, UV)` — The UV attribute used get the current UV value to display
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L36 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L37 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L38 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L39 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InWidgetClippingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L52 _private member_ `TAttribute<FVector2f> UV;` — Slate Attributes
- L55 _private member_ `FOnUVChanged OnUVChangedDelegate;` — Delegate to execute when the UV changes in the swatch area
- L58 _private member_ `FSlateBrush ColorPickerBrush;` — Brush drawn to be used as a color picker
- L61 _private member_ `TWeakObjectPtr<class UTexture2D> ColorPickerTexture;` — The texture used as the color swatch
- L64 _private member_ `bool bIsDragging = false;` — True if the user is selecting a color using the picker
- L67 _private member_ `const FSlateBrush* CrosshairBrush = nullptr;` — The brush used to draw the cross hair showing which color is selected

#### class `SUVColorPicker`  
`class SUVColorPicker : public SCompoundWidget`  
_L75-141_
- inherits: `SCompoundWidget`
- desc: Widget that displays a color block that when clicked creates a pop-up window that allows the user to select a color from a texture using UV coordinates
- L79 _public function_ `SLATE_BEGIN_ARGS(SUVColorPicker) : _bUseSRGBInColorBlock(true)`
- L84 _public prototype_ `SLATE_ATTRIBUTE(FVector2f, UV)` — The UV value currently displayed by the widget
- L108 _public prototype_ `void Construct(const FArguments& InArgs);`
- L113 _private prototype_ `FReply OnUVColorBlockClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Called the color block is clicked
- L116 _private prototype_ `FLinearColor SampleTexture() const;` — Samples the texture image data using the current UV values
- L121 _private member_ `TSharedPtr<class SWindow> Window;` — The window to display the color picker
- L124 _private member_ `FOnUVChanged OnUVChangedDelegate;` — Delegate called when the UV changes from the sliders
- L127 _private member_ `TAttribute<FText> ColorPickerLabel;` — Label to use for the color block and the color picker window
- L130 _private member_ `TAttribute<FText> ULabelOverride;` — Overrides for the UV labels displayed in the color picker window
- L131 _private member_ `TAttribute<FText> VLabelOverride;`
- L134 _private member_ `TAttribute<FVector2f> UV;` — Get the current UV value
- L137 _private member_ `TStrongObjectPtr<class UTexture2D> ColorPickerTexture;` — Color picker texture to be used in the color swatch window
- L140 _private member_ `FImage TextureImageData;` — Image data to be sampled by the color block

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnUVChanged, const FVector2f& InUV, bool bInIsDragging);`
- L9 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnUVChanged, const FVector2f& InUV, bool bInIsDragging);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Private/Verification/MetaHumanCharacterTypesVerification.h` (Private)


#### class `UMetaHumanCharacterTypesVerification`  
`class UMetaHumanCharacterTypesVerification : public UMetaHumanCharacterTypesVerificationExtensionBase`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterTypesVerificationExtensionBase`
- L18 _public prototype_ `virtual void VerifyGroomWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> GroomBindingAsset, UMetaHumanAssetReport* Report) override;`
- L19 _public prototype_ `virtual void VerifySkelMeshClothingWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> SkeletalMesh, UMetaHumanAssetReport* Report) override;`
- L20 _public prototype_ `virtual void VerifyOutfitWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> OutfitAsset, UMetaHumanAssetReport* Report) override;`
- L21 _public prototype_ `virtual void VerifyOutfitAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) override;`
- L22 _public prototype_ `virtual void VerifyMetaHumanCharacterAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) override;`
- L23 _public prototype_ `virtual FClothingAssetDetails GetDetailsForClothingAsset(TNotNull<const UObject*> Target) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorActor.h` (Public)


#### class `AMetaHumanCharacterEditorActor`  
`class AMetaHumanCharacterEditorActor : public AActor, public IMetaHumanCharacterEditorActorInterface`  
_L22-122_
- reflection: `UCLASS(Transient, NotPlaceable, Blueprintable)`
- inherits: `AActor,IMetaHumanCharacterEditorActorInterface`
- desc: A simple actor that represents a MetaHuman in the Character Editor Viewport. This is the default implementation of IMetaHumanCharacterEditorActorInterface, and will be used as a fallback if the implementation specified by the Character Pipeline is invalid. Since it's used as a fallback for any pipeline, it can't rely on any pipeline-specific data in the passed-in Instance.
- L28 _public prototype_ `AMetaHumanCharacterEditorActor();`
- L31 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L32 _public prototype_ `virtual void OnConstruction(const FTransform& InTransform) override;`
- L36 _public prototype_ `virtual void InitializeMetaHumanCharacterEditorActor( TNotNull<const UMetaHumanInstance*> InCharacterInstance, TNotNull<UMetaHumanCharacter*> InCharacter, TNotNull<USkeletalMesh*> InFaceMesh, TNotNull<USkeletalMesh*> InBodyMesh, int32 InNumLODs, const TArray<int32>& InFaceLODMapping, const TArray<int32>& InBodyLODMapping) override;`
- L45 _public prototype_ `virtual void SetForcedLOD(int32 InForcedLOD) override;`
- L47 _public prototype_ `virtual TNotNull<UMetaHumanCharacter*> GetCharacter() const override;`
- L48 _public prototype_ `virtual TNotNull<const USkeletalMeshComponent*> GetFaceComponent() const override;`
- L49 _public prototype_ `virtual TNotNull<const USkeletalMeshComponent*> GetBodyComponent() const override;`
- L50 _public prototype_ `virtual void OnFaceMeshUpdated() override;`
- L51 _public prototype_ `virtual void OnBodyMeshUpdated() override;`
- L52 _public prototype_ `virtual void SetActorDrivingAnimationMode(EMetaHumanActorDrivingAnimationMode InDrivingAnimationMode) override;`
- L53 _public prototype_ `virtual void SetDrivingSkeletalMesh(USkeletalMeshComponent* DrivingSkelMeshComponent) override;`
- L54 _public prototype_ `virtual void UpdateFaceComponentMesh(USkeletalMesh* InFaceMesh) override;`
- L55 _public prototype_ `virtual void UpdateBodyComponentMesh(USkeletalMesh* InBodyMesh) override;`
- L56 _public prototype_ `virtual void ReinitAnimation() override;`
- L57 _public prototype_ `virtual void ResetAnimation() override;`
- L58 _public prototype_ `virtual void SetHairVisibilityState(EMetaHumanHairVisibilityState State) override;`
- L59 _public prototype_ `virtual void SetClothingVisibilityState(EMetaHumanClothingVisibilityState State, UMaterialInterface* OverrideMaterial = nullptr) override;`
- L60 _public prototype_ `virtual void SetShowNormalsOnFace(const bool InShowNormals) override;`
- L61 _public prototype_ `virtual void SetShowNormalsOnBody(const bool InShowNormals) override;`
- L62 _public prototype_ `virtual void SetShowTangentsOnFace(const bool InShowTangents) override;`
- L63 _public prototype_ `virtual void SetShowTangentsOnBody(const bool InShowTangents) override;`
- L64 _public prototype_ `virtual void SetShowBinormalsOnFace(const bool InShowBinormals) override;`
- L65 _public prototype_ `virtual void SetShowBinormalsOnBody(const bool InShowBinormals) override;`
- L72 _protected prototype_ `void Blueprint_SetHairVisibilityState(EMetaHumanHairVisibilityState State);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaHuman|Character", meta = (DisplayName = "SetHairVisibilityState"))` — Any hair components should be set to the given visibility state
- L82 _protected prototype_ `void Blueprint_SetClothingVisibilityState(EMetaHumanClothingVisibilityState State, UMaterialInterface* OverrideMaterial);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaHuman|Character", meta = (DisplayName = "SetClothingVisibilityState"))` — Any clothing components should be set to the given visibility state. If the state is UseOverrideMaterial, the provided material should be applied. The original materials should be restored on the next time the state is changed.
- L87 _protected prototype_ `void OnRiggingStateChanged();` — Called when the character rigging state changes
- L93 _protected member_ `TObjectPtr<class UDebugSkelMeshComponent> BodyComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L96 _protected member_ `TObjectPtr<class UDebugSkelMeshComponent> FaceComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L99 _protected member_ `TObjectPtr<class ULODSyncComponent> LODSyncComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")`
- L103 _protected member_ `TObjectPtr<class URetargetComponent> RetargetComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Retargeting")` — Retarget component used to read poses from another actor's skeletal mesh to retarget it.
- L107 _protected member_ `TObjectPtr<class UIKRetargeter> IKRetargeter;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Retargeting")` — IK retargeter used by the retarget component.
- L111 _protected member_ `EMetaHumanActorDrivingAnimationMode ActorDrivingAnimationMode = EMetaHumanActorDrivingAnimationMode::Manual;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")` — How the actor should handle animation
- L121 _private member_ `TObjectPtr<class UMetaHumanCharacter> Character;` — `UPROPERTY()` — Pointer back to the Character this actor is based on. This is only here so it can be returned from GetCharacter. The actor shouldn't need to access the Character apart from that.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorModule.h` (Public)


#### class `FMetaHumanCharacterEditorModule`  
`class FMetaHumanCharacterEditorModule : public IModuleInterface`  
_L8-31_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static FMetaHumanCharacterEditorModule& GetChecked();`
- L15 _public prototype_ `static bool IsOptionalMetaHumanContentInstalled();` — Returns true if the optional MetaHuman Content has been installed with the Engine and is available to the plugin
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `DECLARE_EVENT_OneParam(FMetaHumanCharacterEditorModule, FOnRegisterLayoutExtensions, class FLayoutExtender&);`
- L23 _public function_ `FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L30 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_EVENT_OneParam(FMetaHumanCharacterEditorModule, FOnRegisterLayoutExtensions, class FLayoutExtender&);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorRenderingQualitySettings.h` (Public)


#### struct `FMetaHumanCharacterViewportRenderingFlags`  
`struct FMetaHumanCharacterViewportRenderingFlags`  
_L11-51_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `bool bTransmissionForAllLights = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L19 _public member_ `bool bTonemapper = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "RenderingQuality")`
- L22 _public member_ `bool bDepthOfField = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "RenderingQuality")`
- L25 _public member_ `bool bDynamicShadows = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "RenderingQuality")`
- L28 _public member_ `bool bSubsurfaceScattering = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L31 _public member_ `bool bGlobalIllumination = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L34 _public member_ `bool bTemporalAA = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L37 _public member_ `bool bLumenGlobalIllumination = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L40 _public member_ `bool bLumenReflections = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L43 _public member_ `bool bPreviewingScreenPercentage = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L46 _public member_ `int32 PreviewScreenPercentage = 50;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality", meta = (EditCondition = "bPreviewingScreenPercentage"))`
- L48 _public member_ `static FMetaHumanCharacterViewportRenderingFlags Epic;`
- L49 _public member_ `static FMetaHumanCharacterViewportRenderingFlags High;`
- L50 _public member_ `static FMetaHumanCharacterViewportRenderingFlags Medium;`

#### struct `FMetaHumanCharacterRenderingQualityProfile`  
`struct FMetaHumanCharacterRenderingQualityProfile`  
_L54-78_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public prototype_ `explicit FMetaHumanCharacterRenderingQualityProfile(const FString& InProfileName = TEXT(""));`
- L59 _public prototype_ `FMetaHumanCharacterRenderingQualityProfile(const FString& InProfileName, const bool bInMetaHumanCharacterDefault, const FMetaHumanCharacterViewportRenderingFlags& InViewportRenderingFlags);`
- L62 _public member_ `FString ProfileName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality", meta = (EditCondition = "!bMetaHumanCharacterDefault", HideEditConditionToggle))`
- L66 _public member_ `bool bMetaHumanCharacterDefault = false;` — `UPROPERTY()` — True if it's a not a user generated profile aka default profile Epic, High or Medium, else false. Default profiles are not serialized into config
- L69 _public member_ `FPostProcessSettings PostProcessSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L72 _public member_ `FMetaHumanCharacterViewportRenderingFlags ViewportRenderingFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderingQuality")`
- L74 _public member_ `static const FMetaHumanCharacterRenderingQualityProfile Invalid;`
- L75 _public member_ `static FMetaHumanCharacterRenderingQualityProfile Epic;`
- L76 _public member_ `static FMetaHumanCharacterRenderingQualityProfile High;`
- L77 _public member_ `static FMetaHumanCharacterRenderingQualityProfile Medium;`

#### class `UMetaHumanCharacterRenderingQualityProfileProxy`  
`class UMetaHumanCharacterRenderingQualityProfileProxy : public UObject`  
_L81-104_
- reflection: `UCLASS()`
- inherits: `UObject`
- L87 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L88 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L91 _public prototype_ `void SetActiveProfile(const FMetaHumanCharacterRenderingQualityProfile& InProfile);`
- L94 _public member_ `FMetaHumanCharacterRenderingQualityProfile RenderingQualityProfile;` — `UPROPERTY(EditAnywhere, Category = "RenderingQuality", meta = (ShowOnlyInnerProperties))`
- L96 _public member_ `int32 ActiveProfileIndex = INDEX_NONE;`
- L97 _public member_ `FString CachedProfileName;`
- L100 _public member_ `FSimpleMulticastDelegate OnProfileNameUpdated;` — The delegate executed when ProfileName is changed
- L103 _public member_ `FSimpleMulticastDelegate OnProfileUpdated;` — The delegate executed when PostProcessSettings or ViewportRenderingFlags is modified

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorSettings.h` (Public)


#### enum `EMetaHumanCharacterMigrationAction`  
`enum class EMetaHumanCharacterMigrationAction : uint8`  
_L17-30_
- reflection: `UENUM()`
- L20 _public enumerator_ `Prompt` — When adding a MetaHuman, prompt for the action to take
- L23 _public enumerator_ `Import` — Import the legacy MetaHuman to the project
- L26 _public enumerator_ `Migrate` — Migrate the MetaHuman to its new representation
- L29 _public enumerator_ `ImportAndMigrate` — Performs both an import and migrate operations

#### class `UMetaHumanCharacterEditorSettings`  
`class UMetaHumanCharacterEditorSettings : public UDeveloperSettings`  
_L36-271_
- reflection: `UCLASS(BlueprintType, config = MetaHumanCharacter, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Settings for the MetaHuman Character Editor plug-in.
- L43 _public prototype_ `UMetaHumanCharacterEditorSettings();` — Constructor
- L46 _public prototype_ `virtual void PostInitProperties() override;`
- L47 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L48 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L49 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L53 _public function_ `virtual FName GetContainerName() const override`
- L54 _public function_ `virtual FName GetCategoryName() const override`
- L55 _public function_ `virtual FName GetSectionName() const override`
- L57 _public prototype_ `virtual FText GetSectionText() const override;`
- L58 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L64 _public prototype_ `const bool ShouldUseVirtualTextures() const;` — @brief Whether or not we should use virtual textures in the MetaHuman Character Editor
- L67 _public function_ `FSimpleDelegate& GetOnPresetsDirectoriesChanged()` — Gets a reference to the OnPresetsDirectoriesChanged delegate
- L70 _public function_ `FSimpleMulticastDelegate& GetOnThumbnailTypeChanged()` — Gets a reference to the OnThumbnailTypeChanged delegate
- L72 _public prototype_ `static FString MakeUniqueKey(const FString& InDesiredKey, TFunctionRef<bool(const FString&)> KeyExists);`
- L74 _public prototype_ `void ShowInvalidOperationError(const FText& ErrorText);`
- L77 _public prototype_ `static bool IsReservedLightingEnvironmentName(const FString& InName);` — Returns true if the given name matches a built-in lighting environment name (e.g. Studio, Fireside, etc.)
- L87 _public prototype_ `void ResolveDefaultLightingEnvironment(EMetaHumanCharacterEnvironment& OutEnvironment, FString& OutCustomPresetKey, TSoftObjectPtr<UWorld>& OutCustomPresetWorld) const;` — Resolves DefaultLightingEnvironment into an environment enum and (when applicable) the matching custom preset. Falls back to Studio if the name is invalid or the matching preset is empty/null. Guarantees that when OutEnvironment == Custom, OutCustomPresetKey and OutCustomPresetWorld both refer to a valid (non-null) preset. @param OutEnvironment 		The resolved environment enum value @param OutCustomPresetKey 	If the resolved environment is Custom, the preset key; otherwise empty @param OutCustomPresetWorld 	If the resolved environment is Custom, the preset world asset; otherwise null
- L91 _private prototype_ `bool CustomLightPresetAssetsFilter(const FAssetData& AssetData);` — `UFUNCTION()`
- L94 _private prototype_ `TArray<FName> GetDefaultLightingEnvironmentOptions() const;` — `UFUNCTION()`
- L96 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L98 _private member_ `TWeakPtr<class SNotificationItem> InvalidOperationError;`
- L101 _private member_ `FSimpleDelegate OnPresetsDirectoriesChanged;` — The delegate executed when the presets directory paths have been changed
- L104 _private member_ `FSimpleMulticastDelegate OnThumbnailTypeChanged;` — The delegate executed when the ThumbnailType has changed
- L108 _private member_ `TArray<FMetaHumanCharacterRenderingQualityProfile> DefaultRenderingQualityProfiles;` — `UPROPERTY(Transient)` — Default rendering quality profiles (Epic, High, Medium). Populated in PostInitProperties and never serialized
- L112 _private member_ `TArray<FMetaHumanCharacterRenderingQualityProfile> UserRenderingQualityProfiles;` — `UPROPERTY(config, VisibleAnywhere, Category = "Lighting Environments")` — User-created rendering quality profiles. Serialized to config.
- L117 _public member_ `FDirectoryPath TextureSynthesisModelDir;` — `UPROPERTY(Config, EditAnywhere, Category = "Face Editing|Texture Synthesis", DisplayName = "Texture Synthesis Model Directory")`
- L120 _public member_ `int32 TextureSynthesisThreadCount = 0;` — `UPROPERTY(Config, EditAnywhere, Category = "Face Editing|Texture Synthesis")`
- L123 _public member_ `TSoftObjectPtr<class UStaticMesh> SculptManipulatorMesh;` — `UPROPERTY(Config, EditAnywhere, Category = "Face Editing|Manipulators")`
- L126 _public member_ `TSoftObjectPtr<class UStaticMesh> MoveManipulatorMesh;` — `UPROPERTY(Config, EditAnywhere, Category = "Face Editing|Manipulators")`
- L129 _public member_ `TSoftObjectPtr<class UStaticMesh> KeyPointCharacterManipulatorMesh;` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Import|Manipulators")`
- L132 _public member_ `TSoftObjectPtr<class UStaticMesh> KeyPointTargetManipulatorMesh;` — `UPROPERTY(Config, EditAnywhere, Category = "Mesh Import|Manipulators")`
- L135 _public member_ `bool bShowCompatibilityModeBodies = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Fixed Body Types")`
- L138 _public member_ `bool bEnableExperimentalWorkflows = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Pipeline")`
- L141 _public member_ `TMap<FName, TSoftObjectPtr<UMaterialInstanceConstant>> ScalableNormalsTypeMaterials;` — `UPROPERTY(Config, EditAnywhere, Category = "Pipeline")`
- L144 _public member_ `TArray<FSoftObjectPath> TemplateAnimationDataTableAssets;` — `UPROPERTY(Config, EditAnywhere, Category = "Animation")`
- L147 _public member_ `TSoftObjectPtr<class UAnimSequence> ShowHandsPose;` — `UPROPERTY(Config, EditAnywhere, Category = "Animation")`
- L151 _public member_ `TArray<FDirectoryPath> PresetsDirectories;` — `UPROPERTY(Config, EditAnywhere, Category = "Presets", DisplayName = "Presets Directories", meta = (ContentDir))` — Where MetaHuman Character presets are going to be searched
- L154 _public member_ `EMetaHumanCharacterThumbnailCameraPosition PresetsThumbnailType = EMetaHumanCharacterThumbnailCameraPosition::Face;` — `UPROPERTY(Config, EditAnywhere, Category = "Presets")`
- L158 _public member_ `EMetaHumanCharacterMigrationAction MigrationAction = EMetaHumanCharacterMigrationAction::Prompt;` — `UPROPERTY(Config, EditAnywhere, Category = "Migration")` — What happens when adding a MetaHuman from Bridge
- L162 _public member_ `FDirectoryPath MigratedPackagePath;` — `UPROPERTY(Config, EditAnywhere, Category = "Migration", meta = (ContentDir))` — Where new MetaHuman Character assets are going to be placed
- L166 _public member_ `FString MigratedNamePrefix;` — `UPROPERTY(Config, EditAnywhere, Category = "Migration")` — Prefix to be added to the name of the migrated MetaHuman Character asset
- L170 _public member_ `FString MigratedNameSuffix;` — `UPROPERTY(Config, EditAnywhere, Category = "Migration")` — Suffix to be added to the name of the migrated MetaHuman Character asset
- L174 _public member_ `int32 TextureStreamingBoost = 5;` — `UPROPERTY(Config, EditAnywhere, Category = "Viewport", meta = (ClampMin = "1", ClampMax = "5"))` — Boost factor to apply when streaming textures in the MetaHumanCharacter asset editor. A higher boost value will stream higher resolution textures in the viewport
- L178 _public member_ `FName DefaultLightingEnvironment = "St` — `UPROPERTY(Config, EditAnywhere, Category = "Lighting Environments", meta = (GetOptions = "GetDefaultLightingEnvironmentOptions"))` — The default lighting environment to use when opening a character. Can be any built-in environment name (Studio, Split, etc.) or a CustomLightPresets key
- L181 _public member_ `TMap<FString, TSoftObjectPtr<UWorld>> CustomLightPresets;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, Category = "Lighting Environments", meta = (GetAssetFilter="CustomLightPresetAssetsFilter"))`
- L185 _public member_ `bool bOpenCustomLightPresetInLevelEditor = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Lighting Environments")` — When enabled, automatically opens the duplicated Custom Light Preset level in the Level Editor after creation
- L189 _public member_ `bool bAutoSpawnPreviewActor = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Lighting Environments", meta = (EditCondition = "bOpenCustomLightPresetInLevelEditor"))` — When enabled, automatically spawns the MetaHuman preview actor when the Custom Light Preset level is opened
- L196 _public member_ `bool bValidateLightingEnvironments = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Lighting Environments")` — When enabled, the MetaHuman lighting environments are validated and MetaHuman Message Log shows validation warnings when a lighting environment uses World Partition or is missing the actors that drive the Light Rig Rotation and Background Color controls. Turn off to silence these messages.
- L199 _public member_ `int32 CameraSpeed_DEPRECATED = 2;` — `UPROPERTY(Config)`
- L202 _public member_ `FEditorViewportCameraSpeedSettings CameraSpeedSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Camera Options")`
- L205 _public member_ `float MouseSensitivityModifier = 0.4f;` — `UPROPERTY(Config, EditAnywhere, Category = "Camera Options", Meta = (ClampMin = "0.0", ClampMax = "1.0"))`
- L209 _public member_ `TArray<FMetaHumanCharacterAssetsSection> WardrobePaths;` — `UPROPERTY(config, EditAnywhere, Category = "Wardrobe", meta=(DisplayName="New Wardrobe Default Asset Paths"))` — User defined wardrobe paths
- L214 _public member_ `bool bEnableWardrobeItemValidation = true;` — `UPROPERTY(config, EditAnywhere, Category = "Wardrobe|Validation")` — Whether or not to run validation of wardrobe items. Disabling this will allow potentially incompatible items to be applied to a MetaHuman Character
- L218 _public member_ `bool bSuppressMessageLogWhenValidatingItems = false;` — `UPROPERTY(config, EditAnywhere, Category = "Wardrobe|Validation")` — If enabled, prevents the Message Log from automatically opening even if there are warnings or errors.
- L222 _public prototype_ `TArray<FMetaHumanCharacterRenderingQualityProfile> GetAllRenderingQualityProfiles() const;` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Returns all rendering quality profiles, with defaults first followed by user profiles
- L225 _public prototype_ `int32 GetAllRenderingQualityProfilesNum() const;` — `UFUNCTION(BlueprintCallable, Category = "Rendering")`
- L229 _public prototype_ `FMetaHumanCharacterRenderingQualityProfile GetRenderingQualityProfile(const int32 InIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Returns the rendering quality profile at the given combined index
- L233 _public prototype_ `void SetRenderingQualityProfile(const int32 InIndex, const FMetaHumanCharacterRenderingQualityProfile& InProfile);` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Sets the rendering quality profile at the given combined index, routing to default or user array based on bMetaHumanCharacterDefault
- L237 _public prototype_ `void AddUserRenderingQualityProfile(const FMetaHumanCharacterRenderingQualityProfile& InProfile);` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Adds a new user rendering quality profile
- L241 _public prototype_ `bool RemoveUserRenderingQualityProfile(const int32 InIndex);` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Removes the user rendering quality profile at the given index. Returns false if index is invalid
- L245 _public prototype_ `int32 GetUserRenderingQualityProfileIndex(const int32 InCombinedIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Converts a combined profile index to a user profile index. Returns INDEX_NONE if the index falls within the default profiles range
- L249 _public prototype_ `bool IsValidRenderingQualityProfileIndex(const int32 InIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Rendering")` — Returns true if the given combined index is valid across both default and user profiles
- L257 _public member_ `bool bUseVirtualTextures = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Rendering")` — Controls which type of materials are created when assembling a MetaHuman Character. When enabled, the assembled character will use materials that support Virtual Textures. This option is ignored if Virtual Textures are disabled in the Project Settings, or if Allow Static Lighting is enabled (r.AllowStaticLighting), as MetaHuman materials that have Virtual Texture support enabled will fail to compile if static lighting is enabled for the project.
- L260 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWardrobePathsChanged);` — Triggers when we change the wardrobe paths
- L261 _public member_ `FOnWardrobePathsChanged OnWardrobePathsChanged;`
- L264 _public member_ `FSimpleDelegate OnExperimentalAssemblyOptionsStateChanged;` — The delegate executed when the experimental assembly options enable state has changed
- L267 _public member_ `FSimpleMulticastDelegate OnCustomLightPresetsChanged;` — The delegate executed when the CustomLightPresets has changed
- L270 _public member_ `FSimpleMulticastDelegate OnUseVirtualTexturesChanged;` — The delegate executed when bUseVirtualTextures has changed

#### Free symbols / members of external scopes

- L260 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWardrobePathsChanged);` — Triggers when we change the wardrobe paths

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorSubsystem.h` (Public)


#### enum `EImportErrorCode`  
`enum class EImportErrorCode : uint8`  
_L38-54_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `FittingError`
- L41 _public enumerator_ `InvalidInputData`
- L42 _public enumerator_ `InvalidInputBones`
- L43 _public enumerator_ `InvalidHeadMesh`
- L44 _public enumerator_ `InvalidLeftEyeMesh`
- L45 _public enumerator_ `InvalidRightEyeMesh`
- L46 _public enumerator_ `InvalidTeethMesh`
- L47 _public enumerator_ `NoHeadMeshPresent`
- L48 _public enumerator_ `NoEyeMeshesPresent`
- L49 _public enumerator_ `NoTeethMeshPresent`
- L50 _public enumerator_ `IdentityNotConformed`
- L51 _public enumerator_ `GeneralError`
- L52 _public enumerator_ `CombinedBodyCannotBeImportedAsWholeRig`
- L53 _public enumerator_ `Success`

#### class `FRemoveRigCommandChange`  
`class FRemoveRigCommandChange : public FCommandChange`  
_L56-108_
- inherits: `FCommandChange`
- L60 _public prototype_ `FRemoveRigCommandChange( const TArray<uint8>& InOldDNABuffer, TSharedRef<const FMetaHumanCharacterIdentity::FState> InOldState, const TArray<uint8>& InOldBodyDNABuffer, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InOldBodyState, TNotNull<UMetaHumanCharacter*> InCharacter);`
- L68 _public function_ `virtual FString ToString() const override`
- L73 _public function_ `virtual void Apply(UObject* InObject) override`
- L78 _public function_ `virtual void Revert(UObject* InObject) override`
- L83 _public prototype_ `virtual bool HasExpired(UObject* InObject) const override;`
- L89 _protected prototype_ `void ApplyChange(UObject* InObject, const TArray<uint8>& InDNABuffer, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState, const TArray<uint8>& InBodyDNABuffer, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState);`
- L95 _protected member_ `TArray<uint8> OldDNABuffer;`
- L96 _protected member_ `TArray<uint8> NewDNABuffer;`
- L98 _protected member_ `TArray<uint8> OldBodyDNABuffer;`
- L99 _protected member_ `TArray<uint8> NewBodyDNABuffer;`
- L101 _protected member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> OldState;`
- L102 _protected member_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> NewState;`
- L104 _protected member_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> OldBodyState;`
- L105 _protected member_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> NewBodyState;`
- L107 _protected member_ `bool bFixedBodyType = false;`

#### class `FAutoRigCommandChange`  
`class FAutoRigCommandChange : public FRemoveRigCommandChange`  
_L111-127_
- inherits: `FRemoveRigCommandChange`
- desc: a specialization of the above with identical functionality but a different name so it appears correctly in the undo stack
- L115 _public prototype_ `FAutoRigCommandChange( const TArray<uint8>& InOldDNABuffer, TSharedRef<const FMetaHumanCharacterIdentity::FState> InOldState, const TArray<uint8>& InOldBodyDNABuffer, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InOldBodyState, TNotNull<UMetaHumanCharacter*> InCharacter);`
- L123 _public function_ `virtual FString ToString() const override`

#### enum `EMetaHumanRigType`  
`enum class EMetaHumanRigType : uint8`  
_L131-135_
- reflection: `UENUM()`
- desc: TODO: Merge this with the enum defined in MetaHumanARServiceRequest.h
- L133 _public enumerator_ `JointsOnly`
- L134 _public enumerator_ `JointsAndBlendShapes`

#### struct `FMetaHumanCharacterTextureRequestParams`  
`struct FMetaHumanCharacterTextureRequestParams`  
_L138-149_
- reflection: `USTRUCT(BlueprintType)`
- L144 _public member_ `bool bReportProgress = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Synthesis")` — Weather or not to report the progress of the request in the form of notification items
- L148 _public member_ `bool bBlocking = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Synthesis")` — Set to true to make it a blocking request

#### struct `FMetaHumanCharacterAutoRiggingRequestParams`  
`struct FMetaHumanCharacterAutoRiggingRequestParams`  
_L152-167_
- reflection: `USTRUCT(BlueprintType)`
- L158 _public member_ `EMetaHumanRigType RigType = EMetaHumanRigType::JointsOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto-Rigging")` — The type of rig to request
- L162 _public member_ `bool bReportProgress = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto-Rigging")` — Weather or not to report the progress of the request in the form of notification items
- L166 _public member_ `bool bBlocking = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto-Rigging")` — Set to true to make it a blocking request

#### struct `FMetaHumanCharacterFitToVerticesParams`  
`struct FMetaHumanCharacterFitToVerticesParams`  
_L170-188_
- reflection: `USTRUCT(BlueprintType)`
- L175 _public member_ `FFitToTargetOptions Options;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L178 _public member_ `TArray<FVector> HeadVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L181 _public member_ `TArray<FVector> LeftEyeVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L184 _public member_ `TArray<FVector> RightEyeVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`
- L187 _public member_ `TArray<FVector> TeethVertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conforming")`

#### struct `FMetaHumanCharacterEditorData`  
`struct FMetaHumanCharacterEditorData`  
_L207-359_
- reflection: `USTRUCT()`
- desc: Helper struct used to hold a data needed for each character being edited
- L211 _public function_ `FMetaHumanCharacterEditorData( TNotNull<USkeletalMesh*> InFaceMesh, TNotNull<USkeletalMesh*> InBodyMesh, TSharedRef<class FDNAToSkelMeshMap> InFaceDnaToSkelMeshMap, TSharedRef<class FDNAToSkelMeshMap> InBodyDnaToSkelMeshMap, TSharedRef<FMetaHumanCharacterIdentity::FState> InFaceState, TSharedRef<FMetaHumanCharacterBodyIdentity::FState> InBodyState) : FaceMesh(InFaceMesh) , BodyMesh(InBodyMesh) , FaceDnaToSkelMeshMap(InFaceDnaToSkelMeshMap) , BodyDnaToSkelMeshMap(InBodyDnaToSkelMeshMap) , FaceState(InFaceState) , BodyState(InBodyState)`
- L229 _public prototype_ `FMetaHumanCharacterEditorData();` — DO NOT USE. For Unreal internals only. Default-constructed instances are not considered valid.
- L232 _public member_ `TArray<TWeakInterfacePtr<class IMetaHumanCharacterEditorActorInterface>> CharacterActorList;` — List of editor actors for a particular characters
- L235 _public member_ `TMap<EFaceTextureType, FImage> CachedSynthesizedImages;` — Image objects used as temp storage for the texture synthesis output
- L238 _public member_ `TStaticArray<TArray<uint8>, 4> CachedHFAlbedoMaps;` — Temporary storage for HF albedo maps returned by the service, used for local texture synthesis
- L241 _public member_ `TSortedMap<EFaceTextureType, TSharedFuture<FSharedBuffer>> SynthesizedFaceTexturesFutures;` — Maps of futures used to do async loading of texture data
- L242 _public member_ `TSortedMap<EBodyTextureType, TSharedFuture<FSharedBuffer>> HighResBodyTexturesFutures;`
- L246 _public member_ `bool bFaceVirtualTextures = false;` — `UPROPERTY()` — Whether or not virtual textures are being used in the Face Material
- L250 _public member_ `bool bBodyVirtualTextures = false;` — `UPROPERTY()` — Whether or not virtual texture are being used in the Body Material
- L253 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L255 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L259 _public member_ `TObjectPtr<class AMetaHumanInvisibleDrivingActor> InvisibleDrivingActor;` — `UPROPERTY()` — Invisible actor driving the preview actor.
- L263 _public member_ `FMetaHumanCharacterFaceMaterialSet HeadMaterials;` — `UPROPERTY()` — All members of this will be UMaterialInstanceDynamics, so it's safe to cast them
- L265 _public member_ `TObjectPtr<class UMaterialInstanceDynamic> BodyMaterial;` — `UPROPERTY()`
- L268 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture HeadHiddenFaceMap;` — `UPROPERTY()`
- L270 _public member_ `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture BodyHiddenFaceMap;` — `UPROPERTY()`
- L274 _public member_ `TObjectPtr<UTexture2D> TempCombinedHeadHiddenFaceMap;` — `UPROPERTY()` — Temporary textures used to combine multiple hidden face maps into one for the character preview
- L276 _public member_ `TObjectPtr<UTexture2D> TempCombinedBodyHiddenFaceMap;` — `UPROPERTY()`
- L280 _public member_ `TObjectPtr<UMetaHumanCollection> PreviewCollection;` — `UPROPERTY()` — Mirrors the Character's internal Collection. Used to build the character shown in the preview viewport.
- L283 _public member_ `bool bClothingVisible = true;` — `UPROPERTY()`
- L286 _public member_ `TOptional<FMetaHumanCharacterSkinSettings> SkinSettings;` — The latest skin settings to be used for generating textures and setting material parameters
- L289 _public member_ `TOptional<FMetaHumanCharacterEyesSettings> EyesSettings;` — The latest eyes settings to be used when updating the preview materials
- L292 _public member_ `TOptional<FMetaHumanCharacterMakeupSettings> MakeupSettings;` — The latest makeup settings to be used when updating the preview materials
- L295 _public member_ `TOptional<FMetaHumanCharacterFaceEvaluationSettings> FaceEvaluationSettings;` — The latest face evaluation settings which include vertex delta scale
- L298 _public member_ `TOptional<FMetaHumanCharacterHeadModelSettings> HeadModelSettings;` — The latest head model settings which include eyelashes parameters and variants.
- L301 _public member_ `TSharedRef<class FDNAToSkelMeshMap> FaceDnaToSkelMeshMap;` — Reference to the mapping between face DNA and Face Skeletal Mesh
- L304 _public member_ `TSharedRef<class FDNAToSkelMeshMap> BodyDnaToSkelMeshMap;` — Reference to the mapping between body DNA and Body Skeletal Mesh
- L307 _public member_ `TSharedRef<FMetaHumanCharacterIdentity::FState> FaceState;` — Reference to the character identity creator
- L310 _public member_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> BodyState;` — Reference to the character body identity creator
- L314 _public member_ `bool bEvaluateBodyPose = false;` — `UPROPERTY()` — Sets if a pose other than MetaHuman A pose should be evaluated from the body state. Used during the import process.
- L318 _public member_ `TArray<FTransform> OverrideDebugBodyBoneTransforms;` — `UPROPERTY()` — Override transforms for drawing debug bones
- L326 _public member_ `TObjectPtr<USkeletalMesh> PreviewMergedHeadAndBody;` — `UPROPERTY()` — Merged head and body mesh used for fast outfit resizing while editing the face or body. Contains only LOD 0. May have other limitations.
- L329 _public member_ `UE::MetaHuman::FMergedMeshMapping PreviewMergedMeshMapping;` — Info about how the separate face and body mesh verts correspond to the verts in the merged mesh.
- L332 _public member_ `FSimpleMulticastDelegate OnFaceStateChangedDelegate;` — Delegate called when the Face State changes
- L335 _public member_ `FSimpleMulticastDelegate OnBodyStateChangedDelegate;` — Delegate called when the Body State changes
- L338 _public member_ `FSimpleMulticastDelegate OnTargetMeshKeyPointsChangedDelegate;` — Delegate called when the target-mesh keypoints collection for this character is modified
- L341 _public member_ `FOnAsyncMeshConformIteration OnAsyncMeshConformIterationDelegate;` — Delegate called on async mesh iteration
- L344 _public member_ `FOnAsyncMeshConformCompleted OnAsyncMeshConformCompletedDelegate;` — Delegate called when async mesh conform finishes
- L347 _public member_ `FOnNotifyLightingEnvironmentChanged NotifyLightingEnvironmentChangedDelegate;` — Delegate used for Environment Lighting studio update.
- L348 _public member_ `FOnStudioLightRotationChanged EnvironmentLightRotationChangedDelegate;`
- L349 _public member_ `FOnStudioBackgroundColorChanged EnvironmentBackgroundColorChangedDelegate;`
- L352 _public member_ `FSimpleMulticastDelegate OnPreviewMaterialChangedDelegate;` — Delegate used for preview material change used in Import Tool
- L355 _public member_ `FOnCameraFocusRequested CameraFocusRequestedDelegate;` — Delegate used for focusing camera on MH Character
- L358 _public member_ `FOnViewportToolbarRenderingQualityProfileChange OnViewportToolbarRenderingQualityProfileChange;` — Delegate used for rendering quality update from viewport toolbar.

#### struct `FMetaHumanCharacterPreviewAssets`  
`struct FMetaHumanCharacterPreviewAssets`  
_L368-383_
- reflection: `USTRUCT()`
- desc: The set of assets needed for the preview build. Importantly, these assets belong to the editor subsystem and must not be modified by the preview build.
- L373 _public member_ `TObjectPtr<USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L376 _public member_ `TObjectPtr<USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L379 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY()`
- L382 _public member_ `TMap<FString, float> BodyMeasurements;` — `UPROPERTY()`

#### struct `FMetaHumanCharacterPreviewAssetOptions`  
`struct FMetaHumanCharacterPreviewAssetOptions`  
_L385-389_
- L387 _public member_ `bool bGenerateMergedHeadAndBodyMesh = false;`
- L388 _public member_ `bool bGenerateBodyMeasurements = false;`

#### struct `FImportFromIdentityParams`  
`struct FImportFromIdentityParams`  
_L392-407_
- reflection: `USTRUCT(BlueprintType)`
- L398 _public member_ `bool bUseEyeMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Identity Options")` — Set to true to use the eye meshes to fit when importing a MetaHuman Identity asset; if false, they are not used
- L402 _public member_ `bool bUseTeethMesh = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Identity Options")` — Set to true to use the teeth mesh to fit when importing a MetaHuman Identity asset; if false, it is not used
- L406 _public member_ `bool bUseMetricScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Identity Options")` — Set to true to use the metric scale of the Identity head when importing a MetaHuman Identity asset; if false, the Identity head will be scaled to MetaHuman size

#### struct `FImportFromDNAParams`  
`struct FImportFromDNAParams`  
_L410-425_
- reflection: `USTRUCT(BlueprintType)`
- L416 _public member_ `bool bIsolateHeadFromBody = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import DNA Options")` — Separates the head from the body, preventing the head being updated by any body changes
- L420 _public member_ `bool bImportWholeRig = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import DNA Options")` — When enabled, the entire rig is replaced from the DNA file (mesh, joints, skin weights and RBFs), resulting in a fixed, non-editable body type. If unchecked, the head DNA file will only be used for neck alignment.
- L424 _public member_ `EAlignmentOptions AlignmentOptions = EAlignmentOptions::ScalingRotationTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import DNA Options", meta = (EditCondition = "!bImportWholeRig", EditConditionHides))` — Set the alignment options to use when importing a MetaHuman DNA head asset

#### struct `FImportBodyFromDNAParams`  
`struct FImportBodyFromDNAParams`  
_L428-439_
- reflection: `USTRUCT()`
- L434 _public member_ `bool bImportWholeRig = false;` — `UPROPERTY(EditAnywhere, Category = "Import Whole Rig")` — When enabled, imports mesh, joints, RBF, and skin weights from the DNA file, resulting in a fixed, non-editable body type. Must be body only, using MetaHuman topology. Disabling this option allows for generating a parametric body type using mesh and, optionally, skeleton from DNA.
- L438 _public member_ `FConformBodyParams ConformBodyParams;` — `UPROPERTY(EditAnywhere, Category = "Import DNA Options", meta = (ShowOnlyInnerProperties, EditCondition = "!bImportWholeRig"))` — Set the conform options to use when conforming a MetaHuman DNA body asset

#### struct `FImportFromTemplateParams`  
`struct FImportFromTemplateParams`  
_L442-465_
- reflection: `USTRUCT(BlueprintType)`
- L448 _public member_ `bool bIsolateHeadFromBody = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Template Options")` — Separates the head from the body, preventing the head being updated by any body changes
- L452 _public member_ `bool bMatchVerticesByUVs = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Template Options")` — Get corresponding vertices from template mesh by matching the template mesh's UVs to MH standard
- L456 _public member_ `bool bUseEyeMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Template Options")` — Set to true to use the eye meshes to fit when importing a SkelMesh; if false, they are not used
- L460 _public member_ `bool bUseTeethMesh = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Template Options")` — Set to true to use the teeth mesh to fit when importing a SkelMesh; if false, it is not used
- L464 _public member_ `EAlignmentOptions AlignmentOptions = EAlignmentOptions::ScalingRotationTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Template Options")` — Set the alignment options to use when importing a SkelMesh or Static Mesh head asset

#### struct `FEditorDataForCharacterCreationParams`  
`struct FEditorDataForCharacterCreationParams`  
_L468-481_
- L471 _public member_ `bool bBlockUntilComplete = false;` — A parameter to control if we should wait for any async tasks to complete
- L474 _public member_ `bool bCreateMeshFromDNA = false;` — A parameter to switch between Interchange import from DNA or content mesh duplication
- L477 _public member_ `TNotNull<UObject*> OuterForGeneratedAssets = GetTransientPackage();` — An outer package that should be used for created skeletal meshes
- L480 _public member_ `EMetaHumanCharacterSkinPreviewMaterial PreviewMaterial = EMetaHumanCharacterSkinPreviewMaterial::Default;` — The preview material type to be used

#### class `UMetaHumanCharacterEditorSubsystem`  
`class UMetaHumanCharacterEditorSubsystem : public UEditorSubsystem , public FTickableEditorObject`  
_L491-2216_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UEditorSubsystem,FTickableEditorObject`
- desc: Subsystem used to interface with the UMetaHumanCharacter asset. Any edits to a MetaHumanCharacter that may need to be exposed as an API should be done as part of this class, as UFUNCTIONs declared here are automatically exposed
- L500 _public prototype_ `virtual bool IsTickable() const override;`
- L501 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L502 _public prototype_ `virtual TStatId GetStatId() const override;`
- L510 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L516 _public prototype_ `static UMetaHumanCharacterEditorSubsystem* Get();` — Utility for obtaining a pointer to the global instance of this subsystem in the editor.
- L529 _public prototype_ `[[nodiscard]] bool TryAddObjectToEdit(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Initialization")` — Registers an object to be edited. The first object registered will also load the Texture Synthesis model to make it to be used Most functions taking a Character on this class require the Character to be registered for editing first. Call RemoveObjectToEdit when done editing. If TryAddObjectToEdit returns false, the Character is not registered, so there's no need to call RemoveObjectToEdit.
- L533 _public prototype_ `bool IsObjectAddedForEditing(const UMetaHumanCharacter* InCharacter) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MetaHuman|Initialization")` — Returns true if the object is registered for editing
- L541 _public prototype_ `void RemoveObjectToEdit(const UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Initialization")` — Tells the subsystem that a character is no longer being edited. Unloads the texture synthesis model when the last object being edited is removed from the subsystem
- L546 _public prototype_ `void ResetTextureSynthesis();` — Clears all internal model data for Texture Synthesis and re-loads the model using the path in the settings
- L559 _public prototype_ `UMetaHumanCollection* GetPreviewCollection(const UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")` — Returns the Collection used to build the Character's preview. If the Character is not being actively edited (i.e. TryAddObjectToEdit hasn't been called) this will return nullptr, otherwise it will always return a valid Collection. @param InCharacter	The character whose preview Collection is requested. @return				The preview Collection, or nullptr if InCharacter is null or has not been added for editing.
- L568 _public prototype_ `void OnEditPreviewCollection(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline")` — Any code that modifies the preview collection for a Character must call this function afterwards, in order to propagate the edits back to the Character asset. @param InCharacter	The character whose preview Collection was edited.
- L572 _public prototype_ `void RunCharacterEditorPipelineForPreview(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline", meta = (ScriptName="AssembleForPreview"))` — Runs the editor pipeline (Preview quality) for the given character. Use whenever changes are made that should be reflected in the preview
- L575 _public prototype_ `const TSharedRef<FMetaHumanCharacterEditorData>* GetMetaHumanCharacterEditorData(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Gets a readonly view on the character editor data
- L589 _private prototype_ `TSharedPtr<FMetaHumanCharacterEditorData> CreateEditorDataForCharacter( TNotNull<const UMetaHumanCharacter*> InCharacter, const FEditorDataForCharacterCreationParams& InParams, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures, TMap<EBodyTextureType, TObjectPtr<class UTexture2D>>& OutBodyTextures, UE::Tasks::FTask InFaceTextureSynthesizerLoadTask = {});` — Initializes the editing state for a Character without registering it. Textures are guaranteed to be created by this function, but not necessarily filled with correct image data yet unless bBlockUntilComplete is true. @param InCharacter The character to create the editor data for @param InParams The collection of input parameters that affect editor data creation @param OutSynthesizedFaceTextures will receive the set of textures for the Character. @param OutBodyTextures will receive the set of bodytextures for the Character. @param InFaceTextureSynthesizerLoadTask optional, task to track whether the FaceTextureSynthesizer has finished initialization
- L604 _private prototype_ `static bool UpdateCharacterFaceMeshFromDNA(TNotNull<UObject*> InGeneratedAssetsOuter, const TSharedPtr<IDNAReader>& InDNAReader, TSharedRef<FMetaHumanCharacterEditorData>& OutCharacterData);` — Updates character face by creating facial SkeletalMesh from DNA through DNA Interchange system and attaches it to CharacterData->FaceMesh. @param InGeneratedAssetsOuter Outer package for created facial skeletal mesh @param InDNAReader DNA to create skeletal mesh from @param OutCharacterData CharacterData to update face mesh for @return True if updated successfully, else false
- L609 _private prototype_ `static void UpdateCharacterBodyMeshFromDNA(TNotNull<UObject*> InGeneratedAssetsOuter, const TSharedPtr<IDNAReader>& InDNAReader, TSharedRef<FMetaHumanCharacterEditorData>& OutCharacterData);` — Creates body SkeletalMesh from DNA through DNA Interchange system and attaches it to CharacterData->BodyMesh.
- L612 _private prototype_ `bool InitializeIdentityStateForFaceAndBody(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedPtr<FMetaHumanCharacterIdentity::FState>& OutFaceState, TSharedPtr<FMetaHumanCharacterBodyIdentity::FState>& OutBodyState);` — /  Setting up and returning the Face and Body states for the character
- L616 _private prototype_ `static void GetFaceAndBodySkeletalMeshes(TNotNull<const UMetaHumanCharacter*> InCharacter, const FEditorDataForCharacterCreationParams& InParams, USkeletalMesh*& OutFaceMesh, USkeletalMesh*& OutBodyMesh);` — Creates Face and Body mesh either by duplicating content browser assets or Interchange system from stored or loaded DNA data
- L623 _private prototype_ `static void UpdatePendingSynthesizedTextures( TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures);` — Fills in textures with image data for any pending textures that are ready. This should be called repeatedly while textures are pending.
- L628 _private prototype_ `static void UpdatePendingHighResBodyTextures( TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TMap<EBodyTextureType, TObjectPtr<UTexture2D>>& OutBodyTextures);`
- L634 _private prototype_ `static void WaitForSynthesizedTextures( TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& OutSynthesizedFaceTextures, TMap<EBodyTextureType, TObjectPtr<UTexture2D>>& OutBodyTextures);` — Block until all textures are filled with image data
- L641 _private prototype_ `void SaveCharacterThumbnails(TNotNull<UMetaHumanCharacter*> InCharacter);` — Updates thumbnail assets for the given character.
- L644 _private prototype_ `[[nodiscard]] TSharedPtr<FMetaHumanCharacterEditorData> CreateEditorDataSKMsFromCharacter( TNotNull<const UMetaHumanCharacter*> InCharacter, const FEditorDataForCharacterCreationParams& InParams);` — Creates the MetaHumanCharacterEditorData generating the Face and Body SKMs as needed.
- L649 _private prototype_ `void SetupEditorDataSKMsFromCharacter(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<FMetaHumanCharacterEditorData> CharacterData);` — Updates the Face and Body SKMs from the input Character data and state
- L652 _private prototype_ `void GenerateCharacterTextures( TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<FMetaHumanCharacterEditorData> CharacterData, TMap<EFaceTextureType, TObjectPtr<class UTexture2D>>& OutSynthesizedFaceTextures, TMap<EBodyTextureType, TObjectPtr<class UTexture2D>>& OutBodyTextures);` — Generate the texture objects from the input Character properties
- L666 _public prototype_ `void InitializeMetaHumanCharacter(TNotNull<UMetaHumanCharacter*> InCharacter);` — Initializes all properties from the given MetaHumanCharacter that require loading data from various sources
- L676 _public prototype_ `TScriptInterface<IMetaHumanCharacterEditorActorInterface> CreateMetaHumanCharacterEditorActor(TNotNull<UMetaHumanCharacter*> InCharacter, TNotNull<class UWorld*> InWorld);` — Spawns and initializes an actor implementing IMetaHumanCharacterEditorActorInterface in the given world. The actor will have the all of its components initialized from the state stored in the MetaHumanCharacter Asset. This function will try to spawn the actor specified by the selected MetaHuman Character Pipeline, but falls back to a default actor type if that fails, so it's guaranteed to return a valid actor.
- L685 _public prototype_ `AActor* SpawnMetaHumanActor(UMetaHumanCharacter* InCharacter, bool bKeepTransient = false);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Actor")` — @brief Spawns a MetaHuman Editor Actor in the main editor level The spawned actor will reflect any changes made to the character while its added to the subsystem @param bKeepTransient If true, the spawned actor retains its RF_Transient flag and will not persist in the level
- L694 _public prototype_ `[[nodiscard]] bool TryGetMetaHumanCharacterEditorActorClass(TNotNull<const UMetaHumanCharacter*> InCharacter, TSubclassOf<AActor>& OutActorClass, FText& OutFailureReason) const;` — Gets the class of actor that will be spawned by CreateMetaHumanCharacterEditorActor if there are no errors. If CreateMetaHumanCharacterEditorActor would fall back to spawning a default actor type, this function will return false and OutActorClass will be set to null.
- L702 _public prototype_ `void CreateMetaHumanInvisibleDrivingActor(TNotNull<const UMetaHumanCharacter*> InCharacter, TScriptInterface<IMetaHumanCharacterEditorActorInterface> InEditorActorInterface, TNotNull<class UWorld*> InWorld);` — Create invisible driving actor. The invisible driving actor is used to play preview animations on the archetype skeletal meshes for which our animations have been recorded for. This is needed for retargeting. We use the invisible driving actor to drive the pose in the right proportions and then retarget it onto the preview MetaHuman. This avoids artefacts from inline retargeting while we can leave the MH Blueprint like it is. Curves will be propagated over as well.
- L707 _public prototype_ `TObjectPtr<class AMetaHumanInvisibleDrivingActor> GetInvisibleDrivingActor(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Get the invisible driving actor given the character.
- L714 _public prototype_ `bool RemoveTexturesAndRigs(TNotNull<UMetaHumanCharacter*> InCharacter);` — Removes all data that is not needed to be in the character to make it a preset. Removes any stored textures and rigs. The caller is responsible for making sure the character is not opened for edit, returns false if the conversion failed
- L733 _public prototype_ `[[nodiscard]] bool TryGenerateCharacterAssets( TNotNull<const UMetaHumanCharacter*> InCharacter, UObject* InOuterForGeneratedAssets, FMetaHumanCharacterGeneratedAssets& OutGeneratedAssets);` — Generates assets, such as meshes and textures, so that other code systems can render the Character. All generated objects must have the provided InOuterForGeneratedAssets as their Outer, and be added to the Metadata array on OutGeneratedAssets. If InOuterForGeneratedAssets is nullptr, the Transient Package will be used as an Outer. If asset generation fails, the function will return false and OutGeneratedAssets will be empty. Some assets may have been generated but they will not be referenced from OutGeneratedAssets.
- L738 _public prototype_ `[[nodiscard]] bool TryGenerateCharacterAssets( TNotNull<const UMetaHumanCharacter*> InCharacter, UObject* InOuterForGeneratedAssets, const FMetaHumanCharacterGeneratedAssetOptions& InOptions, FMetaHumanCharacterGeneratedAssets& OutGeneratedAssets);`
- L751 _public prototype_ `[[nodiscard]] bool TryGetCharacterPreviewAssets( TNotNull<const UMetaHumanCharacter*> InCharacter, FMetaHumanCharacterPreviewAssets& OutPreviewAssets);` — Fetches editor-owned assets needed for the preview build, such as the meshes being actively edited by the Character asset editor. These assets are still owned by the editor and must NOT be modified by callers of this function.
- L755 _public prototype_ `[[nodiscard]] bool TryGetCharacterPreviewAssets( TNotNull<const UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterPreviewAssetOptions& InOptions, FMetaHumanCharacterPreviewAssets& OutPreviewAssets);`
- L764 _public prototype_ `bool CanBuildMetaHuman(TNotNull<const UMetaHumanCharacter*> InCharacter, FText& OutErrorMessage);` — Checks if MetaHuman character is ready for building. If the character cannot be built, outputs the error message describing the reason why.
- L777 _public prototype_ `bool CanBuildMetaHuman(const UMetaHumanCharacter* InCharacter, bool bInLogError = false);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Assembly")` — @brief Checks if MetaHuman character is ready for assembly. If the character is not ready a message with the reason why can be printed in the logs using bInLogError. @param InCharacter The character to verify @param bInLogError Set to log an error message if the character can't be built @return true if the character can be built and false otherwise
- L788 _public prototype_ `void BuildMetaHuman(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterEditorBuildParameters& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Assembly")` — @brief Assemble a MetaHuman Character. Which type of assembly and configuration options can be set using InParams @param InCharacter The character to be assembled. The character must be opened for edit or the build will fail @param InParams Parameter that determine which type of build to make
- L791 _public prototype_ `class UMaterialInterface* GetTranslucentClothingMaterial() const;` — Returns the material to apply to clothing when it should be translucent
- L794 _public prototype_ `void SetClothingVisibilityState(TNotNull<UMetaHumanCharacter*> InCharacter, EMetaHumanClothingVisibilityState InState, bool bUpdateMaterialHiddenFaces);` — Sets the clothing visibility state on any character actor and optionally updates the body material with character data hidden face map
- L797 _public prototype_ `EMetaHumanClothingVisibilityState GetClothingVisibilityState(TNotNull<UMetaHumanCharacter*> InCharacter);` — Gets the clothing visibility state on any character actor
- L802 _public prototype_ `bool IsCharacterOutfitSelected(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns true when the input Character has an outfit applied in the currently active edit sesssion
- L807 _public prototype_ `static USkeletalMesh* GetFaceArchetypeMesh(EMetaHumanCharacterTemplateType InTemplateType, UObject* OuterForGeneratedAssets = GetTransientPackageAsObject());` — Returns the Face Archetype Mesh for the given template type
- L812 _public prototype_ `static USkeletalMesh* GetBodyArchetypeMesh(EMetaHumanCharacterTemplateType InTemplateType, UObject* OuterForGeneratedAssets = GetTransientPackageAsObject());` — Returns the Body Archetype Mesh for the given template type
- L819 _public prototype_ `USkeletalMesh* CreateCombinedFaceAndBodyMesh(TNotNull<const UMetaHumanCharacter*> InCharacter, const FString& InAssetPathAndName, const bool bOverwriteExisting = false);` — Returns combined face and body mesh for the given character. The requirement is that the character has both face and body DNAs.
- L829 _public prototype_ `bool IsTextureSynthesisEnabled() const;` — Returns if the subsystem is able synthesize textures
- L834 _public prototype_ `FLinearColor GetSkinTone(const FVector2f& UV) const;` — Gets the skin tone texture color as rgb value
- L840 _public prototype_ `TWeakObjectPtr<class UTexture2D> GetOrCreateSkinToneTexture();` — Get or create the skin tone texture suitable to be used in the skin tone picker UI The caller is responsible for keeping a reference to the returned texture or it may be GC'ed
- L847 _public prototype_ `FVector2f EstimateSkinTone(const FLinearColor& InSkinTone, const int HFIndex) const;` — Estimates the skin tone UI values from an sRGB colour. Note that the estimation will be done using the currently loaded texture synthesis model. @param InSkinTone is assumed to be in sRGB space
- L852 _public prototype_ `int32 GetMaxHighFrequencyIndex() const;` — Get the maximum value for the HF index the model supports
- L857 _public prototype_ `void ApplyFaceEvaluationSettings(TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterFaceEvaluationSettings& InFaceEvaluationSettings) const;` — Updates the face evaluation settings (vertex deltas and vertex geometry delta) of all the actors associated with the given character.
- L862 _public prototype_ `void CommitFaceEvaluationSettings(TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterFaceEvaluationSettings& InFaceEvaluationSettings);` — Set all the face evaluation settings to the character and apply the changes to all the registered actors.
- L867 _public prototype_ `const FMetaHumanFaceTextureAttributeMap& GetFaceTextureAttributeMap() const;` — Gets the texture attribute map associated with the face texture synthesizer.
- L873 _public prototype_ `void ApplyHeadModelSettings( TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterHeadModelSettings& InHeadModelSettings, bool bIgnoreGrooms = false);` — Updates the Head Model (Eyelashes) of all the actors associated with the given character. bIgnoreGrooms flag is used to skip groom toggling when the focus is only geometry and materials.
- L882 _public prototype_ `void CommitHeadModelSettings(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterHeadModelSettings& InHeadModelSettings);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Model")` — Set all the Head Model settings to the character and apply the changes to all the registered actors.
- L887 _public prototype_ `void ToggleEyelashesGrooms(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterEyelashesProperties& InEyelashesProperties);` — Applies or removes eyelashes grooms according to properties.
- L892 _public prototype_ `void ApplySkinSettings( TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterSkinSettings& InSkinSettings) const;` — Updates the Skin material of all the actors associated with the given character.
- L902 _public prototype_ `void CommitSkinSettings(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterSkinSettings& InSkinSettings);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Texture Synthesis")` — Set all the skin settings to the character and apply the changes to all registered actors. This will synthesize textures if needed based on skin settings. This will also discard any high resolution textures currently stored in the Character
- L906 _public prototype_ `void RequestHighResolutionTextures(TNotNull<UMetaHumanCharacter*> InCharacter, ERequestTextureResolution InResolution);` — `UE_DEPRECATED(5.7, "Please use RequestTextureSources")`
- L917 _public prototype_ `void RequestTextureSources(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterTextureRequestParams& InParams = FMetaHumanCharacterTextureRequestParams());` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Texture Synthesis")` — @brief Request high resolution textures for the given character. This function does nothing if there is already a pending request @param InCharacter The character to request the textures for @param InParams Parameters to control the request
- L922 _public prototype_ `bool IsRequestingHighResolutionTextures(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns true if there is pending request for high resolution textures
- L930 _public prototype_ `void UpdateCharacterPreviewMaterial(TNotNull<UMetaHumanCharacter*> InCharacter, EMetaHumanCharacterSkinPreviewMaterial InPreviewMaterial, bool bWritePersistentState = true) const;` — Update the currently active preview material for the character. @param bWritePersistentState  When true (default), the new preview material is written to UMetaHumanCharacter::PreviewMaterialType and the asset package is marked dirty. Pass false for transient/visualization-only.
- L935 _public prototype_ `void UpdateTranslucencyOnActor(TNotNull<UMetaHumanCharacter*> InCharacter, float InTranslucency);` — Update translucency on matcap material used in Import Tool, this won't work if character doesn't have matcap material applied
- L940 _public prototype_ `void UpdateMatcapMaterialColorOnActor(TNotNull<UMetaHumanCharacter*> InCharacter, FLinearColor InColor);` — Update color on matcap material used in Import Tool, this won't work if character doesn't have matcap material applied
- L945 _public prototype_ `void SetGuideTexturesOnActor(TNotNull<UMetaHumanCharacter*> InCharacter, bool bShowGuides);` — Set guide textures on matcap material used in Import Tool, this won't work if character doesn't have matcap material applied
- L953 _public prototype_ `static bool CompareFaceTextures(const UMetaHumanCharacter* InCharacter1, const UMetaHumanCharacter* InCharacter2, int32 InPixelTolerance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Testing")` — Compare the face textures for the two supplied characters Does NOT require the characters to have been added for edit Returns true if face textures are identical to within the specified tolerance for each channel of each pixel, false otherwise
- L957 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMetaHumanOnDownloadingTexturesStateChanged, TNotNull<const UMetaHumanCharacter*>);` — Callback when downloading textures state changes in editor
- L958 _public member_ `FMetaHumanOnDownloadingTexturesStateChanged OnDownloadingTexturesStateChanged;`
- L965 _private prototype_ `void StoreSynthesizedTextures(TNotNull<UMetaHumanCharacter*> InCharacter) const;` — Stores the synthesized textures in the character asset to be serialized
- L970 _private prototype_ `static void UpdateActorsSkinPreviewMaterial(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, EMetaHumanCharacterSkinPreviewMaterial InPreviewMaterialType, const FMetaHumanCharacterSkinSettings* InSkinSettings = nullptr);` — Update the preview material for the actors corresponding to the character data
- L984 _private prototype_ `void ApplySkinSettings( TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterSkinSettings& InSkinSettings, bool bInForceUseExistingTextures, const FMetaHumanCharacterSkinTextureSet& InFinalSkinTextureSet, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& InOutSynthesizedFaceTextures, bool& bOutTexturesHaveBeenRegenerated) const;` — Updates the editing state of the Character with the given skin settings. Compares the new skin settings to those in the Character Data to determine whether to re-synthesize textures, etc. If bInForceUseExistingTextures is true, this function will assume the current textures are up to date and will not re-synthesize them even if the new skin settings don't match the stored settings. bOutTexturesHaveBeenRegenerated will be set to true if textures were re-synthesized.
- L1003 _private prototype_ `void ApplySkinProperties( TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterSkinProperties& InSkinProperties, TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& InOutSynthesizedFaceTextures, const TMap<EBodyTextureType, TObjectPtr<UTexture2D>>& InBodyTextures) const;` — Synthesizes textures and updates face state with high frequency data. This function doesn't compare the new state to the existing state, so only call it if the textures and HF data need updating. @param InCharacterData the character data struct to apply the settings to @param InSkinProperties parameters for the texture synthesis model @param InOutSynthesizedFaceTextures synthesized textures to be updated @param InOutBodyTextures the set of body textures to update the body material with
- L1010 _private prototype_ `void UpdateSkinTextures(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanCharacterSkinTextureSet& InSkinTextureSet) const;` — Updates material parameters to set textures and skin tone. Needs to be called if new texture objects are being used.
- L1018 _private prototype_ `void OnHighResolutionTexturesRequestCompleted(TSharedPtr<UE::MetaHuman::FFaceHighFrequencyData> InResponse, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Handles a high resolution texture response. Stores the new textures in the character and update any live character actors
- L1023 _private prototype_ `void OnHighResolutionTexturesRequestFailed(EMetaHumanServiceRequestResult InResult, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Handles a high resolution texture request failure
- L1028 _private prototype_ `void OnHighResolutionTexturesProgressUpdated(float InPercentage, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Updates the progress of the texture download notification
- L1034 _private prototype_ `void OnHighResolutionBodyTexturesRequestCompleted(TSharedPtr<UE::MetaHuman::FBodyHighFrequencyData> InResponse, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Handles a high resolution body texture response. Stores the new textures in the character and update any live character actors
- L1039 _private prototype_ `void OnHighResolutionBodyTexturesRequestFailed(EMetaHumanServiceRequestResult InResult, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Handles a high resolution body texture request failure
- L1044 _private prototype_ `void OnHighResolutionBodyTexturesProgressUpdated(float InPercentage, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Updates the progress of the body texture download notification
- L1054 _public prototype_ `void ApplyEyesSettings(TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterEyesSettings& InEyesSettings) const;` — Updates the editing state of the Character with the given eyes settings
- L1063 _public prototype_ `void CommitEyesSettings(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterEyesSettings& InEyesSettings) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Eyes")` — @brief Commits the eyes settings to the character and updates the associated actors @param InCharacter The character in which the eyes settings are going to be committed @param InEyesSettings the eyes settings to commit to the character
- L1070 _private prototype_ `static void ApplyEyesSettings(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterEyesSettings& InEyesSettings);` — Utility function to apply the eyes settings in the character data and update the eyes material with the eyes settings
- L1080 _public prototype_ `void ApplyMakeupSettings(TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterMakeupSettings& InMakeupSettings) const;` — Updates the editing state of the Character with the given makeup settings
- L1089 _public prototype_ `void CommitMakeupSettings(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterMakeupSettings& InMakeupSettings) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Makeup")` — @brief Commits the makeup settings to the character and updates the associated actors @param InCharacter The character in which the makeup settings are going to be commited @param InMakeupSettings the makeup settings to commit to the character
- L1099 _private prototype_ `static void ApplyMakeupSettings(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterMakeupSettings& InMakeupSettings);` — @brief Utility function to apply the makeup settings in the character data and update the face material with the makeup settings @param InCharacterData Character Editor Data containing the materials to be updated @param InMakeupSettings The makeup settings to apply to the materials
- L1109 _public prototype_ `void ApplyFaceState(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState);` — Applies the given state in the MetaHuman Character Actors registered against the character.
- L1117 _public prototype_ `TSharedRef<const FMetaHumanCharacterIdentity::FState> GetFaceState(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Provides read-only access to the current face editing state. If edits have been made since the last call to CommitFaceState, this will be different from Character's stored face state.
- L1122 _public prototype_ `TSharedRef<const FDNAToSkelMeshMap> GetFaceDnaToSkelMeshMap(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Provides read-only access to the FDNAToSkelMeshMap for the current face editing state.
- L1129 _public prototype_ `[[nodiscard]] TSharedRef<FMetaHumanCharacterIdentity::FState> CopyFaceState(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Creates a copy of the current face editing state. Same as GetFaceState, but creates a copy owned by the caller for convenience.
- L1136 _public prototype_ `void CommitFaceState(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState);` — Commits the Face State into the Character asset in order to be serialized when the asset is saved. Also updates the face editing state.
- L1144 _public prototype_ `void CommitFaceState(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — Commits the Face State of the given Character to be serialized. This needs to be done after after using the sculpting or blending APIs to persist the changes Requires the character to be added for edit using TryAddObjectToEdit
- L1152 _public prototype_ `bool CompareFaceState(const UMetaHumanCharacter* InCharacter1, const UMetaHumanCharacter* InCharacter2, float InTolerance) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Testing")` — Evaluate the face state for each of the supplied characters, and compare the vertices and vertex normals Requires the characters to have been added for edit using TryAddObjectToEdit Returns true if all corresponding vertices and vertex normals are within InTolerance of each other in terms of vector norm
- L1160 _public prototype_ `FSimpleMulticastDelegate& OnFaceStateChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Returns a reference to a delegate that fires whenever the face editing state of the given character is modified. May only be called if the Character is registered using TryAddObjectToEdit.
- L1171 _public prototype_ `TSharedPtr<IDNAReader> AlignFaceDNAWithBody(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedPtr<IDNAReader> InFaceDNAReader, bool bUpdateDescendentFaceJoints = false);` — Adapts the given face DNA to fit the character's current body, returning the corrected DNA. Performs CopyBodyJointsToFace and UpdateFaceSkinWeightsFromBodyAndVertexNormals on the input DNA. @param InCharacter Character whose body the DNA is being aligned to @param InFaceDNAReader Face DNA to align @param bUpdateDescendentFaceJoints If true, descendent face joints are updated from body joints @return Aligned DNA, or the input DNA unchanged if alignment cannot be performed (no body or incompatible)
- L1181 _public prototype_ `bool ApplyFaceDNA(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedRef<IDNAReader> InFaceDNAReader, ELodUpdateOption InLodUpdateOption = ELodUpdateOption::All);` — Updates the face editing state and SkelMesh from the given DNA. Does NOT modify the DNA. @param InCharacter Character to update face DNA for @param InFaceDNAReader DNA to apply (must be non-null) @param InLodUpdateOption Chooses which LODs in the SkelMesh are updated @return true if the face mesh was successfully updated, false otherwise
- L1188 _public prototype_ `TSharedPtr<IDNAReader> ApplyFaceDNA(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedPtr<IDNAReader> InFaceDNAReader, bool& bOutUpdatedFaceMesh, ELodUpdateOption InLodUpdateOption = ELodUpdateOption::All);` — `UE_DEPRECATED(5.8, "Use AlignFaceDNAWithBody + ApplyFaceDNA(TSharedRef<IDNAReader>, LodOption) instead. The new ApplyFaceDNA does not modify the DNA.")` — @deprecated Body-aligns and applies the DNA. Use AlignFaceDNAWithBody + ApplyFaceDNA(TSharedRef, …) instead. The new ApplyFaceDNA does not modify the DNA, callers that need alignment should call AlignFaceDNAWithBody explicitly.
- L1195 _public prototype_ `TSharedPtr<IDNAReader> ApplyFaceDNA(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedPtr<IDNAReader> InFaceDNAReader, ELodUpdateOption InLodUpdateOption = ELodUpdateOption::All);` — `UE_DEPRECATED(5.8, "Use AlignFaceDNAWithBody + ApplyFaceDNA(..., TSharedRef<IDNAReader>, ...) instead. The new ApplyFaceDNA does not modify the DNA.")` — @deprecated Body-aligns and applies the DNA. Use AlignFaceDNAWithBody + ApplyFaceDNA(TSharedRef, …) instead. The new ApplyFaceDNA does not modify the DNA, callers that need alignment should call AlignFaceDNAWithBody explicitly.
- L1200 _public prototype_ `void ImportFaceDNA(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedPtr<IDNAReader> InFaceDNAReader);` — Create a face skeletal mesh from the imported DNA.
- L1207 _public prototype_ `void EnableSkeletalPostProcessing(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Enabling animation is now handled internally by the actors and this function is not needed anymore")` — Enable skeletal post-processing. This will enable running the face and body rig and correctives.
- L1214 _public prototype_ `void DisableSkeletalPostProcessing(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Disabling animation is now handled internally by the actors and this function is not needed anymore")` — Disable skeletal post-processing. This will enable running the face and body rig and correctives.
- L1221 _public prototype_ `void EnableAnimation(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Enabling animation is now handled internally by the actors and this function is not needed anymore")` — Enable animation. This will connect the preview character to the invisible driving actor.
- L1228 _public prototype_ `void DisableAnimation(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Disabling animation is now handled internally by the actors and this function is not needed anymore")` — Disable animation. This will disconnect the preview character from the invisible driving actor.
- L1233 _public prototype_ `void CommitFaceDNA(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TSharedRef<class IDNAReader> InFaceDNAReader);` — Commits the Face DNA into the Character asset in order to be serialized when the asset is saved.
- L1238 _public prototype_ `void ResetCharacterFace(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Reset character face.
- L1243 _public prototype_ `[[nodiscard]] TArray<FVector3f> GetFaceGizmos(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns the list of Face Gizmo positions from the Character's state
- L1249 _public prototype_ `[[nodiscard]] TArray<FVector3f> SetFaceGizmoPosition(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState, int32 InGizmoIndex, const FVector3f& InPosition, bool bInSymmetric, bool bInEnforceBounds);` — Sets the face gizmo to an exact position. This function updates the character's Face mesh and returns the list of updated gizmo positions
- L1255 _public prototype_ `[[nodiscard]] TArray<FVector3f> SetFaceGizmoRotation(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState, int32 InGizmoIndex, const FVector3f& InRotation, bool bInSymmetric, bool bInEnforceBounds);` — Sets the face gizmo to an exact rotation. This function updates the character's Face mesh and returns the list of updated gizmo positions
- L1261 _public prototype_ `[[nodiscard]] TArray<FVector3f> SetFaceGizmoScale(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState, int32 InGizmoIndex, float InScale, bool bInSymmetric, bool bInEnforceBounds);` — Scales the given gizmo. This function updates the character's Face mesh and returns the list of updated gizmo positions
- L1266 _public prototype_ `[[nodiscard]] TArray<FVector3f> GetFaceLandmarks(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns the list of Face Landmark positions from the Character's state
- L1277 _public prototype_ `void GetFaceLandmarks(const UMetaHumanCharacter* InCharacter, TArray<FVector>& OutFaceLandmarks) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MetaHuman|Sculpting")` — @brief Gets the positions of the face landmarks for a given character. Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to obtain the landmarks for @param OutFaceLandmarks the list with the face landmarks positions
- L1283 _public prototype_ `[[nodiscard]] TArray<FVector3f> TranslateFaceLandmark(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterIdentity::FState> InState, int32 InLandmarkIndex, const FVector3f& InDelta, bool bInTranslateSymmetrically);` — Translates the given landmark by a delta. This function updates the character's Face mesh and returns the list of updated landmark positions
- L1297 _public prototype_ `void TranslateFaceLandmarks(const UMetaHumanCharacter* InCharacter, const TArray<int32>& InLandmarkIndices, const TArray<FVector>& InDeltas);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — @brief Translates the face landmarks by the given deltas Requires the character to be added for edit using TryAddObjectToEdit The number of landmark indices and deltas must match @param InCharacter the character to translate the landmarks for @param InLandmarkIndices The index of each landmark to be translated @param InDeltas the list of translation deltas to apply to each landmark
- L1308 _public prototype_ `void GetFaceModelCoefficients(const UMetaHumanCharacter* InCharacter, TArray<float>& OutCoefficients) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MetaHuman|Sculpting")` — @brief Gets the coefficients of the underlying face model for the given character. Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to obtain the coefficients for @param OutCoefficients The coefficients array to fill
- L1319 _public prototype_ `void SetFaceModelCoefficients(const UMetaHumanCharacter* InCharacter, const TArray<float>& InCoefficients);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — @brief Sets the coefficients of the underlying face model for the given character. Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to update @param InCoefficients The coefficients to apply
- L1324 _public prototype_ `int32 SelectFaceVertex(TNotNull<const UMetaHumanCharacter*> InCharacter, const FRay& InRay, FVector& OutHitVertex, FVector& OutHitNormal);` — Selects a vertex on the face by intersecting the ray with the current face mesh.
- L1329 _public prototype_ `void AddFaceLandmark(TNotNull<const UMetaHumanCharacter*> InCharacter, int32 InMeshVertexIndex);` — Adds additional custom landmark manipulator on a given mesh surface point.
- L1334 _public prototype_ `void RemoveFaceLandmark(TNotNull<const UMetaHumanCharacter*> InCharacter, int32 InLandmarkIndex);` — Removes selected landmark manipulator.
- L1339 _public prototype_ `TArray<FVector3f> BlendFaceRegion(TNotNull<const UMetaHumanCharacter*> InCharacter, int32 InRegionIndex, const TSharedPtr<const FMetaHumanCharacterIdentity::FState>& InStartState, const TArray<TSharedPtr<const FMetaHumanCharacterIdentity::FState>>& InPresetStates, TConstArrayView<float> InPresetWeights, EBlendOptions InBlendOptions, bool bInBlendSymmetrically);` — Blends Face region though preset states.
- L1345 _public prototype_ `void AutoRigFace(TNotNull<UMetaHumanCharacter*> InCharacter, const UE::MetaHuman::ERigType InRigType);` — `UE_DEPRECATED(5.7, "Please use RequestAutoRigging")` — Method which handles calls to AutoRigService.
- L1356 _public prototype_ `void RequestAutoRigging(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterAutoRiggingRequestParams& InParams = FMetaHumanCharacterAutoRiggingRequestParams());` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Auto-Rigging")` — @brief Make a request to auto-rig a character Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to be auto-rigged @param InParams Parameters to control the auto-rigging process
- L1365 _public prototype_ `void RemoveFaceRig(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Auto-Rigging")` — Remove the face rig from InCharacter, reverting the face mesh back to the archetype DNA and unregistering any morph targets. @param InCharacter Character to remove the face rig from. No-op if null.
- L1370 _public prototype_ `void RemoveBodyRig(TNotNull<UMetaHumanCharacter*> InCharacter);` — Remove the body rig from InCharacter
- L1375 _public prototype_ `void UpdateEyelashesVariantFromProperties(TSharedRef<FMetaHumanCharacterIdentity::FState> InOutFaceState, const FMetaHumanCharacterEyelashesProperties& InEyelashesProperties) const;` — Utility function that sets the eyelashes variant to the input state based on the eyelashes type property
- L1381 _public prototype_ `void UpdateTeethVariantFromProperties(TSharedRef<FMetaHumanCharacterIdentity::FState> InOutFaceState, const FMetaHumanCharacterTeethProperties& InTeethProperties, bool bInUseExpressions = true) const;` — Utility function that sets the teeth variant to the input state based on the teeth type property Also allows the user to turn off the (teeth) expressions at the end of using the tool
- L1386 _public prototype_ `void UpdateHFVariantFromSkinProperties(TSharedRef<FMetaHumanCharacterIdentity::FState> InOutFaceState, const FMetaHumanCharacterSkinProperties& InSkinProperties) const;` — Utility function that sets the high frequency variant to the input state based on the skin texture property
- L1391 _public prototype_ `bool IsAutoRiggingFace(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns true if there is an active request to auto rig the face of the given character
- L1396 _public prototype_ `EMetaHumanCharacterRigState GetRiggingState(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Get the rigging state for the supplied character
- L1403 _public prototype_ `bool FitStateToTargetVertices(TNotNull<UMetaHumanCharacter*> InCharacter, const TMap<EHeadFitToTargetMeshes, TArray<FVector3f>>& InTargetVertices, const FFitToTargetOptions & InFitToTargetOptions);` — Fit the state to the supplied target vertices, which will use whatever part(s) the user has supplied to fit the model EHeadFitToTargetMeshes::Head vertices must always be supplied in the InTargetVertices, using the supplied fitting options. Returns true if successful, false otherwise
- L1415 _public prototype_ `bool FitStateToTargetVertices(UMetaHumanCharacter* InCharacter, const FMetaHumanCharacterFitToVerticesParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — @brief Fit the character to the supplied vertices. Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to be fitted @param InParams Parameters to control the fitting process as well as the meshes @return true if successful, false otherwise
- L1420 _public prototype_ `bool FitToFaceDna(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedRef<class IDNAReader> InFaceDna, const FFitToTargetOptions& InFitToTargetOptions);` — Fit the state to the supplied face DNA, using the supplied fitting options. Returns true if successful, false otherwise
- L1425 _public prototype_ `EImportErrorCode ImportFromIdentity(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TNotNull<const class UMetaHumanIdentity*> InMetaHumanIdentity, const FImportFromIdentityParams& InImportParams);` — Fits the Character face state to the conformed mesh of the input Identity asset
- L1437 _public prototype_ `EImportErrorCode ImportFromIdentity(UMetaHumanCharacter* InMetaHumanCharacter, const class UMetaHumanIdentity* InMetaHumanIdentity, const FImportFromIdentityParams& InImportParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Fits the Character face state to the conformed mesh of the input Identity asset. Suitable for use from Python and Blueprints. @param InMetaHumanCharacter  The character to import into @param InMetaHumanIdentity   The MetaHuman Identity asset to import from @param InImportParams        Options controlling the import @return EImportErrorCode::Success on success, otherwise an error code describing the failure
- L1442 _public prototype_ `EImportErrorCode ImportFromFaceDna(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TSharedRef<class IDNAReader> InFaceDna, const FImportFromDNAParams& InImportParams);` — Either fits the Character face state to the input face DNA, or imports the DNA as-is, depending on options
- L1455 _public prototype_ `EImportErrorCode ImportFromFaceDna(UMetaHumanCharacter* InCharacter, const FString& InDNAFilePath, const FImportFromDNAParams& InImportParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — @brief Either fits the Character face state to the input face DNA, or imports the DNA as-is, depending on options Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to import the DNA to @param InDNAFilePath Path to the DNA file to be imported @param InImportParams Options for how to perform the import operation @return code indicating success or failure
- L1474 _public prototype_ `EImportErrorCode ImportFromTemplate(UMetaHumanCharacter* InCharacter, UObject* InTemplateMesh, UObject* InTemplateLeftEyeMesh, UObject* InTemplateRightEyeMesh, UObject* InTemplateTeethMesh, const FImportFromTemplateParams& InImportParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — @brief Fits the Character face state to the conformed mesh of the input asset, which must be a SkelMesh or Static Mesh which has the correct number of vertices. In addition, the user can (optionally) in the case of a StaticMesh pass in up to three additional meshes for left eye, right eye and teeth, which if not null will be used in the fitting. Note that for the StaticMesh, if the extra meshes are present, they will be used and the flags in the import options will be ignored. Eye and Teeth meshes must contain the correct number of vertices for a MetaHuman. @param InCharacter The character to import the template mesh(es) to @param InTemplateMesh The head mesh (either StaticMesh or SkelMesh) which much match the topology of a MetaHuman head mesh @param InTemplateLeftEyeMesh If not nullptr, must be a StaticMesh for the left eye which much match the topology of a MetaHuman left eye mesh @param InTemplateRightEyeMesh If not nullptr, must be a StaticMesh for the right eye which much match the topology of a MetaHuman right eye mesh @param InTemplateTeethMesh If not nullptr, must be a StaticMesh for the teeth which much match the topology of a MetaHuman teeth mesh @param InImportParams the parameters used during the fitting process @return code indicating success or failure
- L1481 _public prototype_ `void InitializeFromPreset(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TNotNull<const UMetaHumanCharacter*> InPresetCharacter);` — Initializes metahuman character using selected preset character.
- L1487 _private prototype_ `void OnAutoRigFaceRequestCompleted(const UE::MetaHuman::FAutorigResponse& InResponse, TObjectKey<UMetaHumanCharacter> InCharacterKey, const UE::MetaHuman::ERigType InRigType);` — Called when an AutoRigging request completes
- L1492 _private prototype_ `void OnAutoRigFaceRequestFailed(EMetaHumanServiceRequestResult InResult, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Handles a high resolution texture request failure
- L1497 _private prototype_ `void OnAutoRigFaceProgressUpdated(float InPercentage, TObjectKey<UMetaHumanCharacter> InCharacterKey);` — Updates the progress of an AutoRigging request
- L1504 _private prototype_ `static void ApplyFaceState(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TSharedRef<FMetaHumanCharacterIdentity::FState> InState);` — Sets the given face state on the Character Data. Note that this function takes ownership of InState, unlike the public overload that takes a copy of it.
- L1507 _private prototype_ `void ApplySkinPropertiesToFaceState(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterSkinProperties& InSkinProperties) const;` — Updates the face editing state from the given skin properties
- L1510 _private prototype_ `void ApplyEyelashesAndTeethPropertiesToFaceState(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanCharacterEyelashesProperties& InEyelashesProperties, const FMetaHumanCharacterTeethProperties& InTeethProperties, bool bInUpdateEyelashes, bool bInUpdateTeeth, ELodUpdateOption InUpdateOption) const;` — Updates the face editing state from the given eyelashes and teeth properties
- L1518 _private prototype_ `static void UpdateFaceMeshInternal(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanRigEvaluatedState& InVerticesAndNormals, ELodUpdateOption InUpdateOption);` — Updates the Face Mesh of the Character using state stored in the actor and the given vertices and vertex normals This function does not evaluate the model and purely updates the skeletal mesh. It is the caller responsibility to call Evaluate and obtain the vertices and normals to pass to this function.
- L1523 _private prototype_ `void FitFaceStateFromBody(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const TArray<FVector3f>& InTeethVertices, const TArray<FVector3f>& InLeftEyeVertices, const TArray<FVector3f>& InRightEyeVertices);` — Core implementation shared by both FitFaceStateFromBody overloads. Drives the head from the body vertices, then fits any supplied teeth/eye vertex arrays into the bind frame and calls FitToTarget.
- L1531 _private prototype_ `EImportErrorCode GetDataForConforming(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TNotNull<UObject*> InTemplateMesh, UObject* InTemplateLeftEyeMesh, UObject* InTemplateRightEyeMesh, UObject* InTemplateTeethMesh, const FImportFromTemplateParams& InImportParams, TMap<EHeadFitToTargetMeshes, TArray<FVector3f>>& OutVertices);` — Get the data for performing import from template mesh
- L1552 _public prototype_ `void ApplyBodyState(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InState, EBodyMeshUpdateMode InUpdateMode);` — Applies the given custom body state to MetaHuman Character Actors registered against the character. Evaluates the state and updates the body mesh, updates the character's body mesh state using the state stored in the character The subsystem takes a copy of the passed-in state and uses the copy, so InState will not be modified.
- L1558 _public prototype_ `void CommitBodyState(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InState, EBodyMeshUpdateMode InUpdateMode = EBodyMeshUpdateMode::Full);` — Commits the Body State into the Character asset in order to be serialized when the asset is saved. If there are live Character actors registered against the subsystem, also update their face state.
- L1566 _public prototype_ `bool CompareBodyState(const UMetaHumanCharacter* InCharacter1, const UMetaHumanCharacter* InCharacter2, float InTolerance) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Testing")` — Evaluate the body state for each of the supplied characters, and compare the vertices and vertex normals Requires the characters to have been added for edit using TryAddObjectToEdit Returns true if all corresponding vertices and vertex normals are within InTolerance of each other in terms of vector norm
- L1574 _public prototype_ `void CommitBodyState(UMetaHumanCharacter* InCharacter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — Commits the Body State of the given Character to be serialized. This needs to be done after after using the sculpting or blending APIs to persist the changes Requires the character to be added for edit using TryAddObjectToEdit
- L1581 _public prototype_ `FSimpleMulticastDelegate& OnBodyStateChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Returns a reference to a delegate that fires whenever the body editing state of the given character is modified. May only be called if the Character is registered using TryAddObjectToEdit.
- L1589 _public prototype_ `FSimpleMulticastDelegate& OnTargetMeshKeyPointsChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Returns a reference to a delegate that fires whenever the target-mesh keypoints collection on the given character is modified including undo/redo of keypoint changes. May only be called if the Character is registered using TryAddObjectToEdit.
- L1597 _public prototype_ `TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> GetBodyState(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Provides read-only access to the current body editing state. If edits have been made since the last call to CommitBodyState, this will be different from Character's stored body state.
- L1604 _public prototype_ `TSharedRef<FMetaHumanCharacterBodyIdentity::FState> CopyBodyState(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Creates a copy of the current body editing state. Same as GetBodyState, but creates a copy owned by the caller for convenience.
- L1611 _public prototype_ `bool SetToTargetPosedState(TNotNull<UMetaHumanCharacter*> InCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey);` — Sets the character state to the character's posed state Used to restore a character's posed state if one has been stored during import for the target mesh key
- L1618 _public prototype_ `void SetBodyGlobalDeltaScale(TNotNull<UMetaHumanCharacter*> InCharacter, float InBodyGlobalDelta) const;` — Sets the body vertex and joint global delta scale
- L1623 _public prototype_ `float GetBodyGlobalDeltaScale(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Gets the body vertex and joint global delta scale
- L1628 _public prototype_ `TSharedPtr<IDNAReader> ApplyBodyDNA(TNotNull<const UMetaHumanCharacter*> InCharacter, TSharedRef<IDNAReader> InBodyDNAReader, bool bImportMesh = true);` — Updates the body editing state with the given DNA. Optionally importing the mesh from DNA via interchange
- L1634 _public prototype_ `void CommitBodyDNA(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TSharedRef<class IDNAReader> InBodyDNAReader, bool bFixedBodyType = true);` — Commits the Body DNA into the Character asset in order to be serialized when the asset is saved, Sets the Character as having a fixed body type with bFixedBodyType. Fixed types import the mesh from DNA via interchange
- L1639 _public prototype_ `bool ParametricFitToDnaBody(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter);` — Fits the Character body state to the fixed body DNA
- L1644 _public prototype_ `bool ParametricFitToCompatibilityBody(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter);` — Fits the Character body state to the current fixed compatibility body
- L1651 _public prototype_ `EImportErrorCode ImportFromBodyDna(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TSharedRef<class IDNAReader> InBodyDna, const FImportBodyFromDNAParams& InImportOptions);` — `UE_DEPRECATED(5.7, "ImportFromBodyDna option has been deprecated. Please use ConformBody, SetBodyJointTranslations, SetBodyMesh or ImportWholeRig.")` — Either fits the Character body state to the input body DNA, or imports the DNA as-is, depending on options
- L1662 _public prototype_ `EImportErrorCode ImportFromBodyTemplate(UMetaHumanCharacter* InMetaHumanCharacter, UObject* InTemplateMesh, EMetaHumanCharacterBodyFitOptions InBodyFitOptions);` — `UE_DEPRECATED(5.7, "ImportFromBodyTemplate option has been deprecatd. Please use ConformBody, SetBodyJointTranslations, SetBodyMesh or ImportWholeRig.")` — @brief Fits the Character body state to the conformed mesh of the input asset, which must be a SkelMesh or Static Mesh which has the correct number of vertices. @param InMetaHumanCharacter The character to import the body template mesh to @param InTemplateMesh The mesh (either StaticMesh or SkelMesh) which much match the topology of a MetaHuman body or combined head and body mesh @param InBodyFitOptions the fitting options used during the fitting process @return code indicating success or failure
- L1668 _public prototype_ `EImportErrorCode GetMeshForBodyConforming(UMetaHumanCharacter* InMetaHumanCharacter, UObject* InBodyTemplateMesh, UObject* InHeadTemplateMesh, bool bInMatchVerticesByUVs, TArray<FVector3f>& OutVertices);` — Get the mesh for performing import from body template
- L1682 _public prototype_ `EImportErrorCode GetMeshForBodyConforming(UMetaHumanCharacter* InMetaHumanCharacter, UObject* InBodyTemplateMesh, UObject* InHeadTemplateMesh, bool bInMatchVerticesByUVs, TArray<FVector>& OutVertices);` — `UE_DEPRECATED(5.8, "Use GetMeshForBodyConformingFromTemplate instead.")` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming", meta = (DeprecatedFunction, DeprecationMessage = "Use GetMeshForBodyConformingFromTemplate instead."))` — @brief Blueprint exposed version of the GetMeshForBodyConforming function @param InMetaHumanCharacter The character to import the body template mesh to @param InBodyTemplateMesh The mesh (either StaticMesh or SkelMesh) which much match the topology of a MetaHuman body or combined head and body mesh @param InHeadTemplateMesh The mesh (either StaticMesh or SkelMesh) which much match the topology of a MetaHuman head mesh @param bInMatchVerticesByUVs flag which if set to true uses UV matching to match the vertices, otherwise requires exactly matching SkelMesh @param OutVertices On completion contains the body mesh vertices @return code indicating success or failure
- L1685 _public prototype_ `EImportErrorCode GetMeshForBodyConformingFromTemplate(UMetaHumanCharacter* InMetaHumanCharacter, UObject* InBodyTemplateMesh, UObject* InHeadTemplateMesh, bool bInMatchVerticesByUVs, TArray<FVector3f>& OutVertices);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")`
- L1691 _public prototype_ `EImportErrorCode GetMeshForBodyConforming(UMetaHumanCharacter* InMetaHumanCharacter, TSharedRef<IDNAReader> BodyDNA, TSharedPtr<IDNAReader> HeadDNA, TArray<FVector3f>& OutVertices);` — Get the mesh for performing import from body template
- L1703 _public prototype_ `EImportErrorCode GetMeshForBodyConformingFromDNA(UMetaHumanCharacter* InMetaHumanCharacter, const FString& InBodyDnaFilePath, const FString& InHeadDnaFilePath, TArray<FVector3f>& OutVertices);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Get the body mesh vertices for conforming, from DNA file paths. @param InMetaHumanCharacter  The character to conform @param InBodyDnaFilePath     Absolute file path to the body DNA file @param InHeadDnaFilePath     Absolute file path to the head DNA file (optional, pass empty string to omit) @param OutVertices           On success, contains the body mesh vertices @return EImportErrorCode::Success on success, otherwise an error code describing the failure
- L1708 _public prototype_ `EImportErrorCode GetJointsForBodyConforming(USkeletalMesh* InTemplateMesh, TArray<FVector3f>& OutJointWorldTranslations, TArray<FVector3f>& OutJointRotations);` — Get the joints for performing import from body template
- L1720 _public prototype_ `EImportErrorCode GetJointsForBodyConforming(USkeletalMesh* InTemplateMesh, TArray<FVector>& OutJointWorldTranslations, TArray<FVector>& OutJointRotations);` — `UE_DEPRECATED(5.8, "Use GetJointsForBodyConformingFromTemplate instead.")` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming", meta = (DeprecatedFunction, DeprecationMessage = "Use GetJointsForBodyConformingFromTemplate instead."))` — @brief Blueprint exposed version of the GetJointsForBodyConforming function @param InTemplateMesh The mesh to be conformed which much match the topology of a MetaHuman body or combined head and body mesh @param OutJointWorldTranslations On completion contains the body joint world translations @param OutJointRotations On completion contains the body joint rotations @return code indicating success or failure
- L1723 _public prototype_ `EImportErrorCode GetJointsForBodyConformingFromTemplate(USkeletalMesh* InTemplateMesh, TArray<FVector3f>& OutJointWorldTranslations, TArray<FVector3f>& OutJointRotations);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")`
- L1729 _public prototype_ `EImportErrorCode GetJointsForBodyConforming(TSharedRef<IDNAReader> BodyDNA, TArray<FVector3f>& OutJointWorldTranslations, TArray<FVector3f>& OutJointRotations);` — Get the joints for performing import from body template
- L1741 _public prototype_ `EImportErrorCode GetJointsForBodyConformingFromDNA(const FString& InBodyDnaFilePath, TArray<FVector3f>& OutJointWorldTranslations, TArray<FVector3f>& OutJointRotations);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Get the body joint data for conforming, from a DNA file path. Suitable for use from Python and Blueprints. @param InBodyDnaFilePath             Absolute file path to the body DNA file @param OutJointWorldTranslations     On success, contains the body joint world translations @param OutJointRotations             On success, contains the body joint rotations @return EImportErrorCode::Success on success, otherwise an error code describing the failure
- L1744 _public prototype_ `bool ConformBody(UMetaHumanCharacter* InMetaHumanCharacter, const TArray<FVector3f>& InVertices, const TArray<FVector3f>& InJointRotations, bool bTargetIsInAPose, bool bEstimateJointsFromMesh);` — Conforms the body mesh to target parameters
- L1757 _public prototype_ `bool FitFaceStateFromBodyWithEyesTeethTemplate(UMetaHumanCharacter* InMetaHumanCharacter, UObject* InTeethMesh, UObject* InLeftEyeMesh, UObject* InRightEyeMesh, bool bInMatchVerticesByUVs);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Updates the face state to fit the current body state, and optionally re-fits teeth and/or eyes using vertices extracted from the supplied template mesh objects. Call this after ConformBody. @param InMetaHumanCharacter  The character whose face state will be updated. @param InTeethMesh           Optional static or skeletal mesh in MetaHuman teeth topology. Pass null to skip. @param InLeftEyeMesh         Optional static or skeletal mesh in MetaHuman left eye topology. Pass null to skip. @param InRightEyeMesh        Optional static or skeletal mesh in MetaHuman right eye topology. Pass null to skip. @param bInMatchVerticesByUVs When true, use UV correspondence to map template vertices to the DNA archetype order. @return true if the face state was successfully updated.
- L1772 _public prototype_ `bool FitFaceStateFromBodyWithEyesTeethDNA(UMetaHumanCharacter* InMetaHumanCharacter, TSharedRef<class IDNAReader> InFaceDna);` — Updates the face state to fit the current body state, then re-fits teeth and eyes using vertex positions read directly from a face DNA reader. The head shape is driven by the body, not the DNA — only teeth (mesh index 1), left eye (3), and right eye (4) are taken from the DNA. Call this after ConformBody. @param InMetaHumanCharacter  The character whose face state will be updated. @param InFaceDna             DNA reader to extract teeth and eye vertices from. @return true if the face state was successfully updated.
- L1784 _public prototype_ `bool FitFaceStateFromBodyWithEyesTeethDNA(UMetaHumanCharacter* InMetaHumanCharacter, const FString& InFaceDnaFilePath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Updates the face state to fit the current body state, then re-fits teeth and eyes using vertex positions read from a face DNA file. The head shape is driven by the body, not the DNA — only teeth (mesh index 1), left eye (3), and right eye (4) are taken from the DNA. Call this after ConformBody. @param InMetaHumanCharacter  The character whose face state will be updated. @param InFaceDnaFilePath     Path to the face DNA file to extract teeth and eye vertices from. @return true if the face state was successfully updated.
- L1787 _public prototype_ `bool ConformTargetMeshesAsync(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams, bool bBlocking = false);` — Conforms the body and head meshes to target meshes
- L1797 _public prototype_ `static bool GetMeshDataForConforming(UObject* InMesh, TArray<FVector3f>& OutVertices, TArray<int32>& OutTriangleIndices);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Extract topology vertices and triangle indices from a static or skeletal mesh. Uses the MeshDescription to return the same data that the interactive conform tool uses internally. @param InMesh The source mesh (UStaticMesh or USkeletalMesh) @param OutVertices Topology vertex positions @param OutTriangleIndices Triangle indices (3 per triangle, referencing OutVertices) @return true if extraction succeeded
- L1811 _public prototype_ `bool ConformToTargetMeshes(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Synchronously conforms the body and head meshes to target parameters. Python/Blueprint-friendly wrapper around ConformTargetMeshesAsync that runs with bBlocking=true and returns the solver result. @param InMetaHumanCharacter The character to conform. Must be open for editing. @param InTargetMeshKey Identifies which target mesh slot (body / head / combined) the conform applies to. Used as the per-mesh key for target-pose state storage so successive conforms against different meshes don't overwrite each other. @param InConformTargetParams Solver inputs: target mesh data, keypoints, face tracking, solver settings. @return true if the conform solver succeeded; false on invalid input or solve failure.
- L1825 _public prototype_ `bool TrackFaceLandmarksFromImage(const TArray<FColor>& InImageData, int32 InWidth, int32 InHeight, TMap<FString, FTrackingPoints>& OutCurveTrackingPoints);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Run face landmark detection on an image and return tracking contour curves. Use with a front-facing portrait of the target mesh — typically a SceneCapture2D render. The first call after editor start synchronously loads the face contour tracker NNE models (the default tracker asset), so it can take several seconds; subsequent calls hit the cached models and are fast. @param InImageData Raw pixel data (BGRA8); length must equal InWidth * InHeight. @param InWidth Image width in pixels. @param InHeight Image height in pixels. @param OutCurveTrackingPoints Named contour curves (2D points in image space). @return true if any landmarks were detected; false on invalid input, model load failure, or no face found.
- L1828 _public prototype_ `bool AlignToTargetMeshesAsync(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams, bool bBlocking = false);` — Rigidly aligns the character state to the target meshes
- L1833 _public prototype_ `void CommitPosedStateAsAPose(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — After conforming body state in pose, finalizes body and face states by evaluating solved body state in MetaHuman A Pose, and updating face state from it.
- L1839 _public prototype_ `bool AlignToTargetMeshes(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FConformTargetParams& InConformTargetParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Synchronously aligns tthe body and head meshes to target meshes Python/Blueprint-friendly wrapper that calls AlignToTargetMeshesAsync in blocking mode.
- L1842 _public prototype_ `bool IsAsyncConformPending(TNotNull<const UMetaHumanCharacter*> InMetaHumanCharacter) const;` — Returns if Async Conform process is pending
- L1845 _public prototype_ `bool IsBodyStateMatchingTargetPosedState(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey) const;` — Returns if the body state is currently matching the target posed state for the given target mesh key
- L1852 _public prototype_ `FOnAsyncMeshConformIteration& OnAsyncMeshConformIteration(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Returns a reference to a delegate that fires on each conform async iteration May only be called if the Character is registered using TryAddObjectToEdit.
- L1859 _public prototype_ `FOnAsyncMeshConformCompleted& OnAsyncMeshConformCompleted(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Returns a reference to a delegate that fires whenever the conform async is completed. May only be called if the Character is registered using TryAddObjectToEdit.
- L1862 _public prototype_ `bool RefineVerticesToTargeAsync(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FRefinementTargetParams& InRefinementTargetParams);` — Refines vertices to the target mesh
- L1865 _public prototype_ `void CancelMeshAsyncProcess(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter);` — Cancels any async mesh import process
- L1869 _public prototype_ `void CommitTargetMeshKeypoints(UMetaHumanCharacter* InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FMetaHumanCharacterTargetKeyPoints& InTargetMeshKeyPoints, const TMap<FName, EKeyPointType>& InKeyPointTypes);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Commit the target mesh keypoints to the character (filters out preset keypoints, only commits Custom)
- L1873 _public prototype_ `TMap<FName, int32> GetPresetBodyKeyPoints(const UMetaHumanCharacter* InCharacter) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Get preset keypoints from MetaHumanCreator API (body or head) without committing them
- L1876 _public prototype_ `void CommitTargetMeshTrackingResults(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FMetaHumanCharacterTargetTrackingResults& InTrackingResults);` — Commit the target mesh tracking results to the character
- L1890 _public prototype_ `bool ConformBody(UMetaHumanCharacter* InMetaHumanCharacter, const TArray<FVector>& InVertices, const TArray<FVector>& InJointRotations, bool bRepose, bool bEstimateJointsFromMesh);` — `UE_DEPRECATED(5.8, "Use ConformBodyToTarget instead.")` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming", meta = (DeprecatedFunction, DeprecationMessage = "Use ConformBodyToTarget instead."))` — @brief Blueprint exposed version of the ConformBody functions @param InMetaHumanCharacter The character to conform @param InVertices The body vertices, obtained by calling GetMeshForBodyConforming @param InJointRotations The body joint rotations, obtained by calling GetJointsForBodyConforming @param bRepose If set to true, repose the body to the A pose after conformation, if false, leave as-is @param bEstimateJointsFromMesh If set to true, estimate the hand and feet joints from the supplied mesh vertices; otherwise, leave alone. @return true if successful, false otherwise
- L1893 _public prototype_ `bool ConformBodyToTarget(UMetaHumanCharacter* InMetaHumanCharacter, const TArray<FVector3f>& InVertices, const TArray<FVector3f>& InJointRotations, bool bTargetIsInAPose, bool bEstimateJointsFromMesh);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")`
- L1897 _public prototype_ `bool SetBodyJoints(UMetaHumanCharacter* InMetaHumanCharacter, const TArray<FVector3f>& InComponentJointTranslations, const TArray<FVector3f>& InJointRotations, bool bImportHelperJoints);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Set custom body joints
- L1901 _public prototype_ `bool SetBodyMesh(UMetaHumanCharacter* InMetaHumanCharacter, const TArray<FVector3f>& InVertices, bool bRepositionHelperJoints);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Set custom body neutral mesh
- L1904 _public prototype_ `EImportErrorCode ImportBodyWholeRig(TNotNull<UMetaHumanCharacter*> InMetaHumanCharacter, TSharedRef<class IDNAReader> InBodyDna, TSharedPtr<IDNAReader> InHeadDna);` — Import body as a fully rigged Character  from DNA, sets character to a fixed body type
- L1908 _public prototype_ `EImportErrorCode ImportBodyWholeRig(UMetaHumanCharacter* InMetaHumanCharacter, const FString& InBodyDnaFilePath, const FString& InHeadDnaFilePath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Import body as a fully rigged Character from DNA file paths, sets character to a fixed body type
- L1914 _public prototype_ `bool FitToBodyDna(TNotNull<UMetaHumanCharacter*> InCharacter, TSharedRef<class IDNAReader> InBodyDna, EMetaHumanCharacterBodyFitOptions InBodyFitOptions);` — `UE_DEPRECATED(5.7, "FitToBodyDna option has been deprecatd. Please use ConformBodyFromDna with FConformBodyParams instead.")` — Fit the state to the supplied body DNA. Returns true if successful, false otherwise
- L1927 _public prototype_ `TArray<FMetaHumanCharacterBodyConstraint> GetBodyConstraints(const UMetaHumanCharacter* InCharacter, bool bScaleMeasurementRangesWithHeight = false) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — @brief Gets the list of body constrains from the underlying parametric body model Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter the character to retrieve the body constraints for @param bScaleMeasurementRangesWithHeight scale the measurement ranges by height to help stay within realistic model proportions @return the list of body constraints provided by the underlying parametric body model
- L1938 _public prototype_ `void SetBodyConstraints(const UMetaHumanCharacter* InCharacter, const TArray<FMetaHumanCharacterBodyConstraint>& InBodyConstraints);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Sculpting")` — @brief Set body constraints and evaluate the parametric body Requires the character to be added for edit using TryAddObjectToEdit @param InCharacter The character to update the constraints @param InBodyContrains The list of body constraints to apply to the character
- L1943 _public prototype_ `void ResetParametricBody(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Reset the parametric body
- L1948 _public prototype_ `void SetMetaHumanBodyType(TNotNull<const UMetaHumanCharacter*> InCharacter, EMetaHumanBodyType InBodyType, EBodyMeshUpdateMode InUpdateMode);` — Sets the MetaHuman body on the body editing state
- L1953 _public prototype_ `bool IsFixedBodyType(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Is the body a fixed body type, either imported from dna as a whole rig, or a fixed compatibility body
- L1958 _public prototype_ `int32 SelectBodyVertex(TNotNull<const UMetaHumanCharacter*> InCharacter, const FRay& InRay, FVector& OutHitVertex, FVector& OutHitNormal) const;` — Selects a vertex on the body by intersecting the ray with the current body mesh.
- L1963 _public prototype_ `[[nodiscard]] TArray<FVector3f> GetBodyGizmos(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns the list of body region gizmo positions from the character's state
- L1968 _public prototype_ `TArray<FVector3f> BlendBodyRegion(TNotNull<const UMetaHumanCharacter*> InCharacter, int32 InRegionIndex, EBodyBlendOptions InBodyBlendOptions, const TSharedPtr<const FMetaHumanCharacterBodyIdentity::FState>& InStartState, const TArray<TSharedPtr<const FMetaHumanCharacterBodyIdentity::FState>>& InPresetStates, TConstArrayView<float> InPresetWeights);` — Blends Face region though preset states.
- L1971 _public prototype_ `void SetEvaluateBodyPose(UMetaHumanCharacter* InMetaHumanCharacter, bool bEvaluateBodyPose);` — Sets to evaluate a pose other than MetaHuman A pose from the state
- L1974 _public prototype_ `TNotNull<const USkeletalMesh*> GetFaceEditMesh(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns the face editing mesh for the character.
- L1977 _public prototype_ `TNotNull<const USkeletalMesh*> GetBodyEditMesh(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Returns the body editing mesh for the character.
- L1981 _public prototype_ `TNotNull<const USkeletalMesh*> Debug_GetFaceEditMesh(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — `UE_DEPRECATED(5.8, "Debug_GetFaceEditMesh has been renamed to GetFaceEditMesh.")` — @deprecated Use GetFaceEditMesh instead.
- L1985 _public prototype_ `TNotNull<const USkeletalMesh*> Debug_GetBodyEditMesh(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — `UE_DEPRECATED(5.8, "Debug_GetBodyEditMesh has been renamed to GetBodyEditMesh.")` — @deprecated Use GetBodyEditMesh instead.
- L1989 _private prototype_ `static void UpdateBodyMeshInternal( TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, const FMetaHumanRigEvaluatedState& InVerticesAndNormals, ELodUpdateOption InUpdateOption, bool bInUpdateDnaState);`
- L1995 _private prototype_ `static void UpdateFaceFromBodyInternal( TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, ELodUpdateOption InUpdateOption, bool bInUpdateNeutral);`
- L2000 _private prototype_ `static void ApplyBodyState(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TSharedRef<FMetaHumanCharacterBodyIdentity::FState> InState, EBodyMeshUpdateMode InUpdateMode);`
- L2005 _private prototype_ `void UpdateCharacterIsFixedBodyType(TNotNull<UMetaHumanCharacter*> InCharacter, bool bIsFixedBody);` — Updates the character's fixed body type, fixed bodies are either imported from dna as a whole rig, or a fixed compatibility body
- L2010 _private prototype_ `static void ForEachCharacterActor(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TFunction<void(TScriptInterface<class IMetaHumanCharacterEditorActorInterface>)> InFunc);` — Utility function that invokes a callback for each valid MetaHuman Character Editor Actor registered against the given MetaHuman Character
- L2022 _private prototype_ `const FMetaHumanCharacterIdentityModels& GetOrCreateCharacterIdentity(EMetaHumanCharacterTemplateType InTemplateType);` — Returns the FMetaHumanCharacterIdentity of the given template type. If the Identity for the template doesn't exist it will be created and cached in CharacterIdentities
- L2027 _private prototype_ `static FString GetFaceIdentityTemplateModelPath(EMetaHumanCharacterTemplateType InTemplateType);` — Returns the path to where the face models for the given template type are stored
- L2032 _private prototype_ `static FString GetBodyIdentityModelPath();` — Returns the path to where the body model is stored
- L2037 _private prototype_ `static FString GetLegacyBodiesPath();` — Returns the path to where the legacy bodies are stored
- L2046 _private prototype_ `static TObjectPtr<UPhysicsAsset> CreatePhysicsAssetForCharacter(TNotNull<const UMetaHumanCharacter*> InCharacter, TNotNull<UObject*> InOuter, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState);` — Creates the physics asset using body state @param InCharacter the character to generate the physics asset for @param InOuter the object to use as the outer for the new physics asset @param InBodyState the body state used to generate the physics asset
- L2052 _private prototype_ `static void UpdatePhysicsAssetFromBodyState(TNotNull<UPhysicsAsset*> InPhysicsAsset, TSharedRef<const FMetaHumanCharacterBodyIdentity::FState> InBodyState);` — Updates a physics asset using body state
- L2057 _private prototype_ `void OnCharacterInstanceUpdated(TNotNull<const UMetaHumanCharacter*> InCharacter);` — Called on instance updated. Updates head and body hidden face maps and materials
- L2062 _private prototype_ `void UpdateCharacterPreviewMaterialHiddenFacesMask(TNotNull<const UMetaHumanCharacter*> InCharacter) const;` — Updates hidden faces map on body material
- L2067 _private prototype_ `TMap<FString, float> GetFaceAndBodyMeasurements(TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, bool bGetMeasuresFromDNA) const;` — Gets measurements from face and body, either from dna or from character state
- L2070 _private prototype_ `void OnMeshImportIterationUpdate(float InPercentage, const FMetaHumanRigEvaluatedState& InBodyVerticesAndNormals, const FMetaHumanRigEvaluatedState& InFaceVerticesAndNormals, const TArray<FVector3f>& InJointPositions, const TArray<FRotator3f>& InJointRotations, const FText& InSolveMessage, TNotNull<UMetaHumanCharacter*> InCharacter);` — Called on async conform iteration to update character render data in scene
- L2079 _private prototype_ `void OnMeshImportComplete(bool bSuccess, bool bWasCancelled, const TSharedRef<FMetaHumanCharacterBodyIdentity::FState>& InBodyState, const TSharedRef<FMetaHumanCharacterIdentity::FState>& InFaceState, const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, TNotNull<UMetaHumanCharacter*> InCharacter);` — Called on async conform completion to commit state
- L2087 _private prototype_ `void OnMeshImportFailedNotifications(TNotNull<UMetaHumanCharacter*> InCharacter);` — Called on async conform failure cases to set notifications
- L2090 _private prototype_ `static void UpdateDebugBoneTransformsFromState(const TSharedRef<FMetaHumanCharacterEditorData>& InCharacterData);` — Updates override debug bone transforms used to display body bones during conform
- L2094 _private prototype_ `static ELodUpdateOption GetUpdateOptionForEditing();`
- L2096 _private prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L2099 _private member_ `TMap<TObjectKey<UMetaHumanCharacter>, TSharedRef<FMetaHumanCharacterEditorData>> CharacterDataMap;` — Map a MetaHuman Character to the data it needs while being edited
- L2102 _private member_ `TMap<TObjectKey<UMetaHumanCharacter>, FMetaHumanCharacterEditorCloudRequests> CharacterCloudRequests;` — Map all the live cloud requests for a given MetaHuman Character
- L2105 _private member_ `TMap<TObjectKey<UMetaHumanCharacter>, FMetaHumanCharacterEditorMeshImportContext> CharacterMeshImportContexts;` — Map async mesh import contexts for each MetaHuman Character
- L2108 _private member_ `TSortedMap<EMetaHumanCharacterTemplateType, FMetaHumanCharacterIdentityModels> CharacterIdentities;` — Map with loaded Character Identity Models
- L2111 _private member_ `FMetaHumanFaceTextureSynthesizer FaceTextureSynthesizer;` — Face Synthesizer to be shared between all editable objects
- L2114 _private member_ `TWeakObjectPtr<class UTexture2D> SkinToneTexture;` — Skin Tone Texture created from FaceTextureSynthesizer used in UI skin tone picker
- L2117 _private member_ `FDelegateHandle CharacterInstanceUpdatedDelegateHandle;` — Delegate handle for instance update
- L2121 _private member_ `TObjectPtr<USkeletalMesh> MetaHumanFaceArchetypeMesh;` — `UPROPERTY()` — Cached archetype meshes imported from DNA
- L2123 _private member_ `TObjectPtr<USkeletalMesh> MetaHumanBodyArchetypeMesh;` — `UPROPERTY()`
- L2126 _private member_ `bool bIsAddingObjectToEdit = false;` — True if TryAddObjectToEdit is running
- L2132 _public prototype_ `void ForEachCharacterActor(TNotNull<const UMetaHumanCharacter*> InCharacter, TFunction<void(TScriptInterface<class IMetaHumanCharacterEditorActorInterface>)> InFunc);` — Utility function that invokes a callback for each valid MetaHuman Character Editor Actor registered against the given MetaHuman Character
- L2143 _public prototype_ `void DestroyMetaHumanCharacterEditorActor(TScriptInterface<class IMetaHumanCharacterEditorActorInterface> InCharacterActor);` — Destroys an editor actor previously created via CreateMetaHumanCharacterEditorActor and unregisters it from the character's actor list. RemoveObjectToEdit already destroys all actors registered for the character, so callers that paired Create with TryAddObjectToEdit / RemoveObjectToEdit do not need to invoke this directly. This is only required when CreateMetaHumanCharacterEditorActor was called without going through TryAddObjectToEdit (e.g. transient preview/thumbnail use cases) and the caller is responsible for tearing the actor down.
- L2149 _public prototype_ `FOnNotifyLightingEnvironmentChanged& OnLightTonemapperChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Please use OnNotifyLightingEnvironmentChanged function for getting a delegate for all level related changes.")` — Editing environment changes from toolbar options
- L2151 _public prototype_ `FOnNotifyLightingEnvironmentChanged& OnLightEnvironmentChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);` — `UE_DEPRECATED(5.7, "Please use OnNotifyLightingEnvironmentChanged function for getting a delegate for all level related changes.")`
- L2152 _public prototype_ `FOnNotifyLightingEnvironmentChanged& OnNotifyLightingEnvironmentChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2154 _public prototype_ `FOnStudioLightRotationChanged& OnLightRotationChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2156 _public prototype_ `FOnStudioBackgroundColorChanged& OnBackgroundColorChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2158 _public prototype_ `FSimpleMulticastDelegate& OnPreviewMaterialChanged(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2160 _public prototype_ `FOnCameraFocusRequested& OnCameraFocusRequested(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2162 _public prototype_ `FOnViewportToolbarRenderingQualityProfileChange& OnViewportToolbarRenderingQualityProfileChange(TNotNull<const UMetaHumanCharacter*> InCharacter);`
- L2173 _public prototype_ `void UpdateLightingEnvironment(TNotNull<UMetaHumanCharacter*> InCharacter, EMetaHumanCharacterEnvironment InLightingEnvironment) const;` — `UE_DEPRECATED(5.7, "Please use NotifyLightingEnvironmentChanged function for all level related changes.")` — !!!!DEPRECATED!!!! USE NotifyLightingEnvironmentChanged Updates the Environment Lighting studio. This function executes an EnvironmentUpdate delegate which has a bound function inside of an EditorToolkit. It is called when change happens inside a tile view which holds lighting studio options in toolbar menu or if tonemapper option changes, or if user decides to use custom lighting environment.
- L2183 _public prototype_ `void UpdateTonemapperOption(TNotNull<UMetaHumanCharacter*> InCharacter, bool bInToneMapperEnabled) const;` — `UE_DEPRECATED(5.7, "Please use NotifyLightingEnvironmentChanged function for all level related changes.")` — !!!!DEPRECATED!!!! USE NotifyLightingEnvironmentChanged Updates the Environment Lighting studio. This function executes an EnvironmentUpdate delegate which has a bound function inside of an EditorToolkit. It is called when change happens inside a tile view which holds lighting studio options in toolbar menu.
- L2189 _public prototype_ `void NotifyLightingEnvironmentChanged(TNotNull<UMetaHumanCharacter*> InCharacter) const;` — Used for lighting scenario levels updates, including custom levels and post process levels, signals an update to editor toolkit
- L2194 _public prototype_ `void UpdateLightRotation(TNotNull<UMetaHumanCharacter*> InCharacter, float InRotation) const;`
- L2199 _public prototype_ `void UpdateBackgroundColor(TNotNull<UMetaHumanCharacter*> InCharacter, const FLinearColor& InBackgroundColor) const;` — Updates the background color of the lighting environment
- L2204 _public prototype_ `void UpdateCharacterLOD(TNotNull<UMetaHumanCharacter*> InCharacter, const EMetaHumanCharacterLOD NewLODValue) const;` — Updates the Character Level of detail shown in Editor.
- L2209 _public prototype_ `void UpdateAlwaysUseHairCardsOption(TNotNull<UMetaHumanCharacter*> InCharacter, bool bInAlwaysUseHairCards);` — Updates character actor groom components to always use cards instead of strands.
- L2215 _public prototype_ `void NotifyViewportToolbarRenderingQualityProfileChange(TNotNull<UMetaHumanCharacter*> InCharacter, const int32 InIndex) const;` — Used for rendering quality profile update from viewport toolbar, signals an update to editor toolkit

#### enum `UMetaHumanCharacterEditorSubsystem::EBodyMeshUpdateMode`  
`enum class EBodyMeshUpdateMode : uint8`  
_L1538-1544_
- L1541 _public enumerator_ `Minimal` — A fast update to be used while dragging sliders, etc. Only the data needed for immediate rendering is updated.
- L1543 _public enumerator_ `Full` — The full update that takes longer. This must be done once the slider drag or other input is complete.

#### struct `UMetaHumanCharacterEditorSubsystem::FMetaHumanCharacterIdentityModels`  
`struct FMetaHumanCharacterIdentityModels`  
_L2012-2016_
- L2014 _public member_ `TSharedPtr<FMetaHumanCharacterIdentity> Face;`
- L2015 _public member_ `TSharedPtr<FMetaHumanCharacterBodyIdentity> Body;`

#### Free symbols / members of external scopes

- L190 _namespace_ `namespace UE`
- L190 _namespace_ `namespace MetaHuman` (scope `UE`)
- L195 _delegate_ `DECLARE_DELEGATE(FOnNotifyLightingEnvironmentChanged) DECLARE_DELEGATE_OneParam(FOnStudioLightRotationChanged, float InRotation);`
- L196 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStudioLightRotationChanged, float InRotation);`
- L196 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStudioLightRotationChanged, float InRotation);`
- L197 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStudioBackgroundColorChanged, const FLinearColor& InBackgroundColor) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncMeshConformIteration, const FMetaHumanRigEvaluatedState& , const FMetaHumanRigEvaluatedState& );`
- L197 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStudioBackgroundColorChanged, const FLinearColor& InBackgroundColor) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncMeshConformIteration, const FMetaHumanRigEvaluatedState& , const FMetaHumanRigEvaluatedState& );`
- L198 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncMeshConformIteration, const FMetaHumanRigEvaluatedState& , const FMetaHumanRigEvaluatedState& );`
- L199 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncMeshConformCompleted, bool bSuccess, bool bWasCancelled);`
- L199 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAsyncMeshConformCompleted, bool bSuccess, bool bWasCancelled);`
- L200 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCameraFocusRequested, UMetaHumanCharacter* , EMetaHumanCharacterCameraFrame );`
- L200 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnCameraFocusRequested, UMetaHumanCharacter* , EMetaHumanCharacterCameraFrame );`
- L201 _delegate_ `DECLARE_DELEGATE_OneParam(FOnViewportToolbarRenderingQualityProfileChange, int32);`
- L201 _prototype_ `DECLARE_DELEGATE_OneParam(FOnViewportToolbarRenderingQualityProfileChange, int32);`
- L957 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMetaHumanOnDownloadingTexturesStateChanged, TNotNull<const UMetaHumanCharacter*>);` — Callback when downloading textures state changes in editor

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorWardrobeSettings.h` (Public)


#### class `UMetaHumanCharacterEditorWardrobeSettings`  
`class UMetaHumanCharacterEditorWardrobeSettings : public UObject`  
_L17-39_
- reflection: `UCLASS(Config = Editor, DefaultConfig)`
- inherits: `UObject`
- desc: Predefined wardrobe settings.
- L24 _public member_ `TArray<FMetaHumanCharacterAssetsSection> WardrobeSections;` — `UPROPERTY(Config, EditAnywhere, Category = "Wardrobe")` — List of predefined sections to display assets from
- L28 _public member_ `TMap<FName, FText> SlotNameToCategoryNameMap;` — `UPROPERTY(Config, EditAnywhere, Category = "Wardrobe")` — Mapping between slot name (e.g. Hair, Beard) and the display name for the category
- L32 _public member_ `TMap<EMetaHumanCharacterEyelashesType, FSoftObjectPath> EyelashesTypeToAssetPath;` — `UPROPERTY(Config, EditAnywhere, Category = "Wardrobe")` — Mapping between Eyelashes type and corresponding groom wardrobe asset.
- L36 _public member_ `TArray<FDirectoryPath> PresetDirectories;` — `UPROPERTY(Config, EditAnywhere, Category = "Preset")` — List of predefined preset directories to show by default
- L38 _public prototype_ `FText SlotNameToCategoryName(const FName& InSlotName, const FText& InTextFallback = FText::GetEmpty()) const;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterExportBlueprintLibrary.h` (Public)


#### struct `FMetaHumanDCCExportParams`  
`struct FMetaHumanDCCExportParams`  
_L14-33_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for DCC export.
- L20 _public member_ `FString ExternalPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Output folder on disk. Must not be empty.
- L24 _public member_ `bool bBakeMakeUp = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Whether to bake makeup into the face textures.
- L28 _public member_ `bool bCompressInZipFile = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Whether to compress the output in a ZIP archive.
- L32 _public member_ `FString ArchiveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Archive name. If empty, the character name is used.

#### struct `FMetaHumanDNAExportParams`  
`struct FMetaHumanDNAExportParams`  
_L37-72_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for DNA export.
- L49 _public member_ `FString ProjectPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Project content path for the exported DNA assets (e.g. "/Game/MetaHumans"). Optional: if left empty, no project (in-editor) assets are created and only the external file export is performed. At least one of ProjectPath or ExternalPath must be set to a valid value; both may be set to export in parallel.
- L59 _public member_ `FString ExternalPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Output folder on disk for the exported .dna files. Optional: if left empty, no files are written to disk and only the project-path asset export is performed. At least one of ProjectPath or ExternalPath must be set to a valid value; both may be set to export in parallel.
- L63 _public member_ `bool bDNAHead = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Export head DNA.
- L67 _public member_ `bool bDNABody = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Export body DNA.
- L71 _public member_ `bool bOverwriteExistingAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Overwrites onto the existing DNA assets. Only applies to project path export. If false, creates new unique asset names.

#### struct `FMetaHumanGeometryExportParams`  
`struct FMetaHumanGeometryExportParams`  
_L76-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for geometry export.
- L82 _public member_ `FString ProjectPath = TEXT("/Ga` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Project content path for the exported skeletal mesh assets.
- L86 _public member_ `bool bHeadSkeletalMesh = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Export head skeletal mesh.
- L90 _public member_ `bool bBodySkeletalMesh = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Export body skeletal mesh.
- L94 _public member_ `bool bFullBodySkeletalMesh = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Export combined full-body skeletal mesh.
- L98 _public member_ `bool bOverwriteExistingAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Overwrites onto the existing assets, if false will create new unique asset names for exported assets.

#### struct `FMetaHumanPosedDNAExportParams`  
`struct FMetaHumanPosedDNAExportParams`  
_L108-153_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for posed-DNA export. Posed DNA is the combined head+body geometry produced by a previous ConformToTargetMeshes call, baked into a single DNA file with the body rig applied in posed-joints mode. It's the artifact downstream tools (e.g. material baking) consume after a conform.
- L122 _public member_ `FString ProjectPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Project content folder for the exported posed DNA asset (e.g. "/Game/MetaHumans"). The asset name within this folder is taken from AssetName, falling back to "<CharacterName>_Posed". Optional: if left empty, no project (in-editor) asset is created and only the external file export is performed. At least one of ProjectPath or ExternalPath must be set to a valid value; both may be set to export in parallel.
- L132 _public member_ `FString ExternalPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Output folder on disk for the exported .dna file. The filename within this folder is taken from AssetName (with .dna appended), falling back to "<CharacterName>_Posed.dna". Optional: if left empty, no file is written to disk and only the project-path asset export is performed. At least one of ProjectPath or ExternalPath must be set.
- L140 _public member_ `FMetaHumanCharacterTargetMeshKey TargetMeshKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Identifies the target mesh slot under which the conformed body posed state was stored during ConformToTargetMeshes / ConformTargetMeshesAsync. Must match the key used at conform time — otherwise no posed state is found and the export fails.
- L148 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Optional asset/file name (without extension) for the exported posed DNA. Used as both the UDNA asset name under ProjectPath and the .dna filename stem under ExternalPath. If left empty, defaults to "<CharacterName>_Posed".
- L152 _public member_ `bool bOverwriteExistingAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Overwrites onto the existing DNA asset at ProjectPath. If false, a unique name is generated.

#### struct `FMetaHumanMaterialsExportParams`  
`struct FMetaHumanMaterialsExportParams`  
_L157-168_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters for materials export.
- L163 _public member_ `FString ProjectPath = TEXT("/Ga` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — Project content path for the exported material assets.
- L167 _public member_ `bool bApplyAsOverrides = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaHuman|Export")` — If true, apply exported materials as overrides on the MetaHumanCharacter asset.

#### class `UMetaHumanCharacterExportBlueprintLibrary`  
`class UMetaHumanCharacterExportBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L184-241_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint/Python function library for MetaHuman Character export operations. Provides programmatic access to the same export functionality available through the interactive export tools in the MetaHuman Character Editor UI. Python usage: import unreal character = unreal.load_asset("/Game/MetaHumans/MyCharacter") params = unreal.MetaHumanDCCExportParams() params.external_path = "D:/Export/MyCharacter" unreal.MetaHumanCharacterExportBlueprintLibrary.export_dcc(character, params)
- L197 _public prototype_ `static void ExportDCC(UMetaHumanCharacter* InCharacter, const FMetaHumanDCCExportParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Export a MetaHuman character as a DCC package to an external folder on disk. Generate an archive/directory containing the MetaHuman assets for consumption in DCC tools. Character must be valid and rigged.
- L207 _public prototype_ `static void ExportDNA(UMetaHumanCharacter* InCharacter, const FMetaHumanDNAExportParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Export MetaHuman DNA assets (head and/or body) to project content. Creates standalone UDNA assets. Character must be valid. Head DNA export requires face DNA. At least one of bDNAHead/bDNABody must be true.
- L216 _public prototype_ `static void ExportGeometry(UMetaHumanCharacter* InCharacter, const FMetaHumanGeometryExportParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Export MetaHuman geometry (skeletal meshes) to project content. Creates standalone skeletal mesh assets with persistent topology materials. Character must be valid and open for editing. At least one mesh option in params must be true.
- L226 _public prototype_ `static void ExportMaterials(UMetaHumanCharacter* InCharacter, const FMetaHumanMaterialsExportParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Export MetaHuman materials as persistent MIC assets to project content. Generates character assets, persists textures, creates MICs for all face/body material slots, and optionally applies the exported materials as overrides on the character asset. Character must be valid and have high-resolution textures.
- L240 _public prototype_ `static void ExportPosedDNA(UMetaHumanCharacter* InCharacter, const FMetaHumanPosedDNAExportParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")` — Export the combined posed DNA produced by a previous ConformToTargetMeshes call. Reads the body posed state stored on the character under InParams.TargetMeshKey, converts it to a combined head+body DNA via FState::StateToDna(BaseDNA, bIsCombine=true, bUsePosedJoints=true), and writes it as a UDNA asset to ProjectPath and/or as a .dna file to ExternalPath. This is the headless equivalent of the editor's "Save Pose" button under the Mesh Import tool's manual solve actions. Character must be valid and ConformToTargetMeshes must have run with a matching TargetMeshKey.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterFactoryNew.h` (Public)


#### class `UMetaHumanCharacterFactoryNew`  
`class UMetaHumanCharacterFactoryNew : public UFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UMetaHumanCharacterFactoryNew();`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterThumbnailRenderer.h` (Public)


#### class `FMetaHumanCharacterThumbnailScene`  
`class FMetaHumanCharacterThumbnailScene : public FThumbnailPreviewScene`  
_L18-44_
- inherits: `FThumbnailPreviewScene`
- desc: Scene containing a MetaHumanCharacter actor.
- L22 _public prototype_ `FMetaHumanCharacterThumbnailScene();`
- L24 _public prototype_ `void CreatePreview(UMetaHumanCharacter* InCharacter, EMetaHumanCharacterThumbnailCameraPosition InCameraPosition);`
- L25 _public prototype_ `void DestroyPreview();`
- L30 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;`
- L31 _protected prototype_ `virtual float GetFOV() const override;`
- L37 _private member_ `TScriptInterface<class IMetaHumanCharacterEditorActorInterface> PreviewActor;` — The actor used to preview the character.
- L40 _private member_ `TWeakObjectPtr<UMetaHumanCharacter> Character;` — A reference to the Character asset which we need to generate the thumbnail for.
- L43 _private member_ `EMetaHumanCharacterThumbnailCameraPosition CameraPosition;` — Camera position for this scene

#### class `UMetaHumanCharacterThumbnailRenderer`  
`class UMetaHumanCharacterThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L51-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: Class that does the thumbnail rendering. It contains a reference to the MetaHumanCharacter scene which will be spawned for the thumbnail renderer.
- L57 _public prototype_ `UMetaHumanCharacterThumbnailRenderer();`
- L60 _public prototype_ `virtual void BeginDestroy() override;`
- L64 _public prototype_ `virtual bool CanVisualizeAsset(UObject* InObject) override;`
- L65 _public prototype_ `virtual void Draw(UObject* InObject, int32 InX, int32 InY, uint32 InWidth, uint32 InHeight, class FRenderTarget* InRenderTarget, class FCanvas* InCanvas, bool bInAdditionalViewFamily) override;`
- L66 _public prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L70 _public member_ `EMetaHumanCharacterThumbnailCameraPosition CameraPosition;` — Specifies the camera to be used for the next thumbnail capture
- L74 _private member_ `TUniquePtr<FMetaHumanCharacterThumbnailScene> ThumbnailScene;` — Scene that we're rendering

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanGeometryRemoval.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MetaHuman` (scope `UE`)
- L16 _namespace_ `namespace GeometryRemoval` (scope `UE::MetaHuman`)
- L27 _prototype_ `bool TryCombineHiddenFaceMaps(TConstArrayView<FHiddenFaceMapImage> SourceMaps, FHiddenFaceMapImage& OutDestinationMap, FText& OutFailureReason);` (scope `UE::MetaHuman::GeometryRemoval`) — Combines the source hidden face maps onto a provided destination map, so that multiple sets of hidden faces can be removed in one call. OutDestinationMap will be initialized by this function. Returns false if the inputs are invalid in some way (e.g. zero size source texture) and sets OutFailureReason to an explanation for the failure.
- L38 _prototype_ `bool TryConvertHiddenFaceMapTexturesToImages(TConstArrayView<FHiddenFaceMapTexture> SourceMaps, TArray<FHiddenFaceMapImage>& OutImages, FText& OutFailureReason);` (scope `UE::MetaHuman::GeometryRemoval`) — Converts the provided textures to images and copies the accompanying settings over. Any null textures will be skipped, in which case the resulting image array will be smaller than the provided texture array. Any failures in retrieving the image data from a non-null texture will cause this function to fail and return false. OutFailureReason will be set to an explanation for the failure.
- L46 _prototype_ `void UpdateHiddenFaceMapTextureFromImage(const FImage& Image, TNotNull<UTexture2D*> Texture);` (scope `UE::MetaHuman::GeometryRemoval`) — Copies the image contents into the given texture. Texture only needs to be a valid UTexture2D object. It doesn't need to be initialized in any particular way.
- L75 _prototype_ `bool RemoveAndShrinkGeometry( TNotNull<USkeletalMesh*> SkeletalMesh, int32 LODIndex, const FHiddenFaceMapImage& HiddenFaceMap, TConstArrayView<FName> MaterialSlotsToProcess = TConstArrayView<FName>());` (scope `UE::MetaHuman::GeometryRemoval`) — Removes and shrinks geometry in a skeletal mesh LOD according to the given HiddenFaceMap. This is used to remove geometry that will be hidden, e.g. geometry of a body that is hidden by the clothing being worn on the body. This is done to avoid wasting performance and memory on geometry that will never be seen, but also to stop unseen geometry from intersecting with the geometry in front of it, e.g. the body showing through the clothes due to Z-fighting or coarser geometry being used at lower LODs. At the edges of the hidden area, e.g. around the edges of the clothes, there will be geometry that is partially visible and therefore can't be removed, but could still intersect with geometry in front of it. For this reason, this function provides the ability to "shrink" geometry by moving it a small distance in the opposite direction of its normal. HiddenFaceMap is an image and some settings that control which geometry will be removed or shrunk. For each vertex that's processed, the vertex's UV will be used to look up the image to determine what modification to make to the vertex, if any. Note that for backwards compatibility with the previous geometry removal system, all three color channels are sampled and the highest of the three values is used. MaterialSlotsToProcess is an optional list of names of material slots (which correspond to mesh sections) to operate on. If the list is empty, all material slots will be processed. To understand how the hidden face map pixel values are u
- L91 _prototype_ `float SampleHiddenFaceMap(const FImage& Image, int32 PixelX, int32 PixelY);` (scope `UE::MetaHuman::GeometryRemoval`) — Samples a hidden face map image at the given pixel coordinates.
- L96 _prototype_ `FIntVector2 GetHiddenFaceMapPixelForUV(const FVector2f& UV, float ResX, float ResY);` (scope `UE::MetaHuman::GeometryRemoval`) — Converts a UV coordinate to pixel coordinates in a hidden face map image.
- L108 _prototype_ `bool ShouldHideTriangle( const FVector2f& UvA, const FVector2f& UvB, const FVector2f& UvC, const FImage& Image, float MaxCullValue);` (scope `UE::MetaHuman::GeometryRemoval`) — Returns true if the triangle (identified by its three UV coordinates) should be hidden (fully hidden) according to the hidden face map. A triangle is stripped only if every pixel that overlaps it has a value at or below MaxCullValue. Pixel-triangle overlap is tested precisely, not just by bounding box. UVs are wrapped to the 0-1 range internally. Triangles that cross an integer UV boundary will be handled incorrectly (known limitation).
- L122 _prototype_ `float ComputeShrinkWeight(float PixelValue, float MaxCullValue, float MinKeepValue);` (scope `UE::MetaHuman::GeometryRemoval`) — Computes the shrink weight for a pixel value. Returns 0 if the pixel is at or above MinKeepValue (unaffected), 1 if at or below MaxCullValue (fully hidden / max shrink), and linearly interpolates in between.
- L127 _function_ `inline bool IsPixelCulled(float PixelValue, float MaxCullValue)` (scope `UE::MetaHuman::GeometryRemoval`) — Returns true if the pixel value indicates the geometry should be culled (fully hidden).

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanInvisibleDrivingActor.h` (Public)


#### enum `EMetaHumanCharacterAnimationPlayState`  
`enum class EMetaHumanCharacterAnimationPlayState : uint8`  
_L9-14_
- L11 _public enumerator_ `PlayingForward = 0`
- L12 _public enumerator_ `PlayingBackwards`
- L13 _public enumerator_ `Paused`

#### class `AMetaHumanInvisibleDrivingActor`  
`class AMetaHumanInvisibleDrivingActor : public ASkeletalMeshActor`  
_L17-57_
- reflection: `UCLASS(Transient, NotPlaceable, Blueprintable)`
- inherits: `ASkeletalMeshActor`
- L22 _public prototype_ `AMetaHumanInvisibleDrivingActor();`
- L23 _public prototype_ `void SetBodySkeletalMesh(TNotNull<USkeletalMesh*> InBodyMesh) const;`
- L24 _public prototype_ `void SetDefaultBodySkeletalMesh();`
- L25 _public prototype_ `void ResetAnimInstance();`
- L26 _public prototype_ `void InitPreviewAnimInstance();`
- L27 _public prototype_ `void InitLiveLinkAnimInstance();`
- L29 _public prototype_ `void PlayAnimation() const;`
- L30 _public prototype_ `void PlayAnimationReverse() const;`
- L31 _public prototype_ `void PauseAnimation() const;`
- L32 _public prototype_ `void StopAnimation() const;`
- L33 _public prototype_ `void ScrubAnimation(float NormalizedTime) const;`
- L34 _public prototype_ `void BeginAnimationScrubbing() const;`
- L35 _public prototype_ `void EndAnimationScrubbing() const;`
- L36 _public prototype_ `void SetAnimationPlayRate(float NewPlayRate) const;`
- L37 _public prototype_ `float GetAnimationLength() const;`
- L38 _public prototype_ `EMetaHumanCharacterAnimationPlayState GetAnimationPlayState() const;`
- L39 _public prototype_ `float GetCurrentPlayTime() const;`
- L40 _public prototype_ `int32 GetNumberOfAnimationKeys() const;`
- L42 _public prototype_ `void SetAnimation(UAnimSequence* FaceAnimSequence, UAnimSequence* BodyAnimSequence) const;`
- L44 _public prototype_ `void SetLiveLinkSubjectNameChanged(FName InLiveLinkSubjectName, bool bInitAnimInstance = true);`
- L46 _public prototype_ `class UMetaHumanCharacterAnimInstance* GetPreviewAnimInstance() const;`
- L50 _private member_ `TSoftClassPtr<class UAnimInstance> PreviewAnimInstanceClass;` — `UPROPERTY()`
- L53 _private member_ `TSoftClassPtr<class UAnimInstance> LiveLinkAnimInstanceClass;` — `UPROPERTY()`
- L56 _private member_ `FName LiveLinkSubjectName;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanRigLogicUnpackLibrary.h` (Public)


#### class `UMetaHumanRigLogicUnpackLibrary`  
`class UMetaHumanRigLogicUnpackLibrary`  
_L13-30_
- L17 _public prototype_ `static bool UnpackRBFEvaluation(UAnimBlueprint* AnimBlueprint, USkeletalMesh* SkeletalMesh, TNotNull<UObject*> GeneratedAssetOuter, bool UnpackFingerRBFToHalfRotationControlRig, TArray<uint16>& HalfRotationSolvers, TArray<FMetaHumanBodyRigLogicGeneratedAsset>& OutGeneratedAssets);` — Unpack a DNA file's RBF logic to the specified animation blueprint
- L20 _public prototype_ `static TObjectPtr<UControlRigBlueprint> UnpackControlRigEvaluation(UAnimBlueprint* AnimBlueprint, USkeletalMesh* SkeletalMesh, TObjectPtr<UControlRigBlueprint> ControlRig, TNotNull<UObject*> GeneratedAssetOuter, bool UnpackSwingTwistEvaluation, TArray<uint16>& HalfRotationSolvers);` — Unpack a DNA file's SwingTwist logic to the specified animation blueprint
- L23 _public prototype_ `static UAnimGraphNode_PoseDriver* CreatePoseDriverNode(const UAnimBlueprint* AnimBlueprint, bool bAutoConnect = true);` — Create a new PoseDriver node inside the specified animation blueprint. If AutoConnect is true then the new node will be connected to the Result node in the anim graph.
- L26 _public prototype_ `static UAnimGraphNode_PoseDriver* GetPoseDriverWithDrivers(const TArray<FName>& DriverJointNames, const UAnimBlueprint* AnimBlueprint);` — Try to get a specific PoseDriver node from the animation blueprint that has the specified driver joint names.
- L29 _public prototype_ `static UAnimGraphNode_PoseDriver* GetPoseDriverWithTag(const FName& DriverTag, const UAnimBlueprint* AnimBlueprint);` — Try to get a PoseDriver node from the animation blueprint that has the specified tag applied.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanWardrobeItemThumbnailRenderer.h` (Public)


#### class `UMetaHumanWardrobeItemThumbnailRenderer`  
`class UMetaHumanWardrobeItemThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L14-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: Class that does the thumbnail rendering for MetaHuman Wardrobe Item
- L20 _public prototype_ `virtual bool CanVisualizeAsset(UObject* InObject) override;`
- L21 _public prototype_ `virtual void Draw(UObject* InObject, int32 InX, int32 InY, uint32 InWidth, uint32 InHeight, class FRenderTarget* InRenderTarget, class FCanvas* InCanvas, bool bInAdditionalViewFamily) override;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterBodyTextureUtils.h` (Public)


#### class `FMetaHumanCharacterBodyTextureUtils`  
`class FMetaHumanCharacterBodyTextureUtils`  
_L14-61_
- desc: Helper class providing stateless static functions for managing body textures
- L17 _public prototype_ `static int32 GetSkinToneIndex(const FMetaHumanCharacterSkinProperties& InSkinProperties);`
- L19 _public prototype_ `static int32 GetBodySurfaceMapId(const FMetaHumanCharacterSkinProperties& InSkinProperties);`
- L21 _public prototype_ `static void InitBodyTextureData(const FMetaHumanCharacterSkinProperties& InSkinProperties, const TMap<EBodyTextureType, FMetaHumanCharacterTextureInfo>& InTextureInfo, bool bInUseVirtualTextures, TMap<EBodyTextureType, TObjectPtr<UTexture2D>>& OutBodyTextures);`
- L26 _public prototype_ `static void UpdateBodyTextureSet(const TOptional<FMetaHumanCharacterSkinSettings>& InCharacterSkinSettings, const FMetaHumanCharacterSkinProperties& InSkinProperties, bool bInUseVirtualTextures, TMap<EBodyTextureType, FMetaHumanCharacterTextureInfo>& InOutTextureInfo, TMap<EBodyTextureType, TObjectPtr<class UTexture2D>>& InOutBodyTextures);`
- L32 _public prototype_ `static void UpdateBodySkinBiasGain(const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, FMetaHumanCharacterSkinProperties& InOutSkinProperties);`
- L37 _public prototype_ `static void GetSkinToneAndUpdateMaterials(const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, const TMap<EBodyTextureType, TObjectPtr<class UTexture2D>>& InBodyTextures, const struct FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<UMaterialInstanceDynamic*> InBodyMID);` — Get the skin tone and update the body material with rgb bias parameters and textures. Updates the rgb bias and textures for the chest in the face material to match
- L43 _public prototype_ `static void SetMaterialHiddenFacesTexture(TNotNull<UMaterialInstanceDynamic*> InBodyMID, const UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture& InHiddenFacesTexture);`
- L45 _public prototype_ `static void SetMaterialHiddenFacesTextureNoOp(TNotNull<UMaterialInstanceDynamic*> InBodyMID);`
- L48 _public prototype_ `static UTexture2D* CreateBodyTextureFromSource(EBodyTextureType InTextureType, FImageView InTextureImage, bool bInMakeVirtualIfSupported);` — See the similar functions in FMetaHumanCharacterTextureSynthesis
- L50 _public prototype_ `static void UpdateBodySkinTone( const FMetaHumanCharacterSkinProperties& InSkinProperties, const FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<UMaterialInstanceDynamic*> InBodyMID);`
- L56 _public prototype_ `static void UpdateBodyMaterialFromSkinProperties( const FMetaHumanCharacterSkinProperties& InSkinProperties, const TMap<EBodyTextureType, TObjectPtr<UTexture2D>>& InBodyTextures, const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<UMaterialInstanceDynamic*> InBodyMID);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCHARACTEREDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace GeometryRemoval` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterBuild.h` (Public)


#### struct `FMetaHumanCharacterEditorBuildParameters`  
`struct FMetaHumanCharacterEditorBuildParameters`  
_L25-85_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters to configure MetaHuman Character build.
- L33 _public member_ `EMetaHumanDefaultPipelineType PipelineType = EMetaHumanDefaultPipelineType::Cinematic;` — `UPROPERTY(BlueprintReadWrite, Category = "Build")` — Which type of build to perform.
- L40 _public member_ `EMetaHumanQualityLevel PipelineQuality = EMetaHumanQualityLevel::Cinematic;` — `UPROPERTY(BlueprintReadWrite, Category = "Build")` — The quality of build to perform. Only relevant when PipelineType is Optimized or UEFN
- L44 _public member_ `FName AnimationSystemName;` — `UPROPERTY(BlueprintReadWrite, Category = "Build")` — Target animation system name to be used by the assembled MetaHuman.
- L53 _public member_ `FString AbsoluteBuildPath;` — `UPROPERTY(BlueprintReadWrite, Category = "Build")` — Absolute location where the built assets will end up in. If empty, build will unpack assets in respect to the options set by the palette. Only relevant when Pipeline type is Cinematic, Optimized
- L60 _public member_ `FString NameOverride;` — `UPROPERTY(BlueprintReadWrite, Category = "Build")` — Optional string to be used instead of the character name for the final unpacking folder. Only relevant when Pipeline type is Cinematic, Optimized
- L67 _public member_ `FString CommonFolderPath;` — `UPROPERTY(BlueprintReadWrite, Category = "Build|Default")` — Optional path to a directory where Common MH assets should be shared or copied if needed. Only relevant when PipelineType is Cinematic or Optimized
- L75 _public member_ `bool bEnableWardrobeItemValidation = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Build|Validation")` — If disabled, won't run validation of wardrobe items, allowing potentially incompatible items to be present in the assembled MetaHuman. Setting this to false bEnableWardrobeItemValidation defined in the Project Settings.
- L84 _public member_ `TObjectPtr<class UMetaHumanCollectionPipeline> PipelineOverride;` — `UPROPERTY()` — Specifies the pipeline override to use to build the character. If none, build will fall back on using the pipeline defined on the MetaHumanCharacter, otherwise it will try to use the given pipeline class.

#### class `IMetaHumanCharacterBuildExtender`  
`class IMetaHumanCharacterBuildExtender : public IModularFeature`  
_L87-113_
- inherits: `IModularFeature`
- L90 _public prototype_ `virtual ~IMetaHumanCharacterBuildExtender();`
- L91 _public member_ `static const FName FeatureName;`
- L94 _public prototype_ `virtual TSet<FString> GetMountPoints() const;` — Additional mount points so assets get considered by assembly.
- L97 _public prototype_ `virtual TSet<FName> GetPackageRootsToCopyFrom() const;` — Additional package root path like a plugin path to copy assets into Common. Assets within that package will be copied over to the project common folder.
- L100 _public prototype_ `virtual TArray<FName> GetAnimationSystemOptions() const;` — Get the additional animation system names the extender will add.
- L102 _public prototype_ `virtual bool IsUEFN() const;`
- L103 _public prototype_ `virtual const TSoftClassPtr<UMetaHumanCollectionPipeline> GetOverwritePipeline(EMetaHumanDefaultPipelineType InPipelineType, EMetaHumanQualityLevel InQualityLevel);`
- L106 _public prototype_ `virtual void SetCommonPath(const FString& InCommonFolderPath);` — Inform the extender about the Common folder path.
- L109 _public prototype_ `virtual TArray<UObject*> GetRootObjects(const FMetaHumanCharacterEditorBuildParameters& BuildParameters) const;` — Manually copied, additional assets for cases where dependencies are created after duplication in the assembly process or there is no dependency from the actor blueprint at all.
- L112 _public prototype_ `virtual void PostDuplicateDependencies(const FString& AssetBuildPath, TNotNull<UMetaHumanInstance*> CharacterInstance);` — Called after dependencies are duplicated, allowing extenders to perform custom modifications.

#### struct `UE::MetaHuman::FMergedMeshMapping`  
`struct FMergedMeshMapping`  
_L122-147_
- desc: A mapping from vertices in the face and body meshes to the corresponding verts in the merged mesh. This allows the merged mesh to be quickly updated if the face or body has been changed in a way that doesn't affect topology, e.g. only vertex positions or normals have changed.
- L124 _public prototype_ `void InitFromBodyFaceLODPairing(TConstArrayView<TPair<int32, int32>> BodyFaceLODPairing, int32 NumOriginalBodyLODs, int32 NumOriginalFaceLODs);`
- L145 _public member_ `FVertexMap BodyVertexMap;`
- L146 _public member_ `FVertexMap FaceVertexMap;`

#### struct `UE::MetaHuman::FMergedMeshMapping::FLODVertexMap`  
`struct FLODVertexMap`  
_L126-138_
- L128 _public function_ `bool IsValid() const`
- L135 _public member_ `TArray<FVertexID> OriginalMeshToMergedMesh;` — For each vertex in the separate mesh (e.g. the face or body by itself), this contains the ID of the vertex in the merged mesh
- L137 _public member_ `int32 MergedMeshLODIndex = INDEX_NONE;`

#### struct `UE::MetaHuman::FMergedMeshMapping::FVertexMap`  
`struct FVertexMap`  
_L140-143_
- L142 _public member_ `TArray<FLODVertexMap> OriginalLODVertexMap;`

#### struct `FMetaHumanCharacterEditorBuild`  
`struct FMetaHumanCharacterEditorBuild`  
_L150-296_
- L158 _public prototype_ `static void BuildMetaHumanCharacter( TNotNull<class UMetaHumanCharacter*> InMetaHumanCharacter, const FMetaHumanCharacterEditorBuildParameters& InParams);` — For a given MetaHumanCharacter assembles the MetaHuman Blueprint along with other MetaHuman assets (palette and instance). @param InMetaHumanCharacter Character that we want to build @param InParams Parameters that control the build process
- L168 _public prototype_ `static void StripLODsFromMesh(TNotNull<class USkeletalMesh*> InSkeletalMesh, const TArray<int32>& InLODsToKeep);` — Remove LODs from a Skeletal Mesh and DNA if one is attached @param InLODsToKeep Which LODs to keep in the mesh. If InLODsToKeep is empty, any of the LOD indices in is invalid or if there are more values than the number of LODs in the skeletal mesh, this function does nothing.
- L173 _public prototype_ `static void DownsizeTexture(TNotNull<class UTexture*> InTexture, int32 InTargetResolution, TNotNull<const ITargetPlatform*> InTargetPlatform);` — Downsize a texture it is larger than the target resolution
- L181 _public prototype_ `static USkeletalMesh* MergeHeadAndBody_CreateAsset( TNotNull<class USkeletalMesh*> InFaceMesh, TNotNull<class USkeletalMesh*> InBodyMesh, const FString& InAssetPathAndName, ELodUpdateOption InLodUpdateOption = ELodUpdateOption::All, UE::MetaHuman::FMergedMeshMapping* OutMeshMapping = nullptr);` — Merges body and face skeletal meshes. Resulting mesh will have only joints from the body and skin weights from the face will be transferred to the body joints. Resulting mesh will be standalone asset.
- L194 _public prototype_ `static USkeletalMesh* MergeHeadAndBody_CreateTransient( TNotNull<USkeletalMesh*> InFaceMesh, TNotNull<USkeletalMesh*> InBodyMesh, UObject* InOuter, ELodUpdateOption InLodUpdateOption = ELodUpdateOption::All, UE::MetaHuman::FMergedMeshMapping* OutMeshMapping = nullptr);` — Merges body and face skeletal meshes. Resulting mesh will have only joints from the body and skin weights from the face will be transferred to the body joints. Resulting mesh will be transient object on the given outer.
- L210 _public prototype_ `static TSoftClassPtr<UMetaHumanCollectionPipeline> GetDefaultPipelineClass(EMetaHumanDefaultPipelineType InPipelineType, EMetaHumanQualityLevel InQualityLevel);` — @brief Gets the default pipeline class for the given pipeline type and quality. Default pipeline classes are defined in UMetaHumanCharacterPaletteProjectSettings @param InPipelineType the type of pipeline to search for @param InQualityLevel the quality level for the given pipeline type to search for @return UMetaHumanCollectionPipeline class or null if no class found
- L215 _public prototype_ `static void ReportMessageLogErrors( bool bWasSuccessful, const FText& InSuccessMessageText, const FText& FailureMessageText);` — Helper to report errors to the message log of the MetaHuman editor module.
- L231 _public prototype_ `static bool DuplicateDepedenciesToNewRoot( const TSet<UObject*>& InDependencies, const FString& InDependencyRootPath, TSet<UObject*>& InOutObjectsToReplaceWithin, TMap<UObject*, UObject*>& OutDuplicatedDependencies, TFunction<bool(const UObject*)> InIsAssetSupported);` — Duplicates the dependency objects to input root path and resolves any references as needed. If a dependency object already exists in the root folder then it is not duplicated. @param InDependencies set of all dependency objects to be duplicated @param InDependencyRootPath new root folder for the dependencies to be copied @param InOutObjectsToReplaceWithin set with all objects that reference the dependencies and need to resolve their references @param OutDuplicatedDependencies map for every dependency to its new referenced object @param InIsAssetSupported Callable to check if an asset should be duplicated @return true if all dependencies were duplicated successfully, false if a fatal conflict was detected
- L246 _public prototype_ `static void DeleteMaterialInstanceChildren(TNotNull<UMaterialInterface*> InParentMI, const TSet<UObject*>* InProtectedAssets = nullptr);` — Helper that deletes and MIDs & MICs that are children of the input MI. @param InParentMI         Parent material whose loaded child MIDs/MICs should be marked garbage. @param InProtectedAssets  Optional set of objects to skip even if they would otherwise match IsChildOf(InParentMI). Used by DuplicateDepedenciesToNewRoot to keep the canonical targets it just produced or reused alive across the sweep.
- L257 _public prototype_ `static void CollectDependencies(const TArray<UObject*>& InRootObjects, const TSet<FString>& InAllowedMountPoints, TSet<UObject*>& OutDependencies);` — Finds all the outer objects that are dependencies of the input root objects by walking recursively over all referenced objects It limits the tracking to the MetaHuman Character plugin and Game mount point by default Note that dependencies do not have to be saved on disk @param InRootObjects array of objects to look for their dependencies @param InAllowedMountPoints additional mount points that are allowed in tracking the references (on top for MHC and Game) @param OutDependencies set with all dependency objects
- L266 _public prototype_ `static void CollectUObjectReferencesFromStruct(const UStruct* StructType, const void* StructPtr, TArray<UObject*>& OutObjects);` — Populates an array with all the objects referenced by the input instanced struct @param StructType UStruct instance type @param StructPtr pointer to UStruct data @param OutObjects array of UObjects that are referenced by the struct
- L271 _public prototype_ `static UE::MetaHuman::FMetaHumanAssetVersion GetMetaHumanAssetVersion(TNotNull<const UObject*> InAsset);` — Helper returning the version stored in the metadata. Version of 0.0 is returned if metadata is not found
- L274 _public prototype_ `static UE::MetaHuman::FMetaHumanAssetVersion GetMetaHumanAssetVersion();` — `UE_DEPRECATED(5.7, "Please use GetCurrentMetaHumanAssetVersion")`
- L279 _public prototype_ `static UE::MetaHuman::FMetaHumanAssetVersion GetCurrentMetaHumanAssetVersion();` — Helper returning the Actor BP version used in the plugin as the current engine version
- L284 _public prototype_ `static UE::MetaHuman::FMetaHumanAssetVersion GetFirstMetaHumanCompatibleVersion();` — Helper returning the earliest compatible version of the engine for MetaHuman Character
- L289 _public prototype_ `static bool MetaHumanAssetMetadataVersionIsCompatible(TNotNull<const UObject*> InAsset);` — Helper to check if provided asset has matching or higher version in metadata.
- L294 _public prototype_ `static void SetMetaHumanVersionMetadata(TNotNull<UObject*> InObject);` — Helper to set the latest MetaHuman Asset Version used in the plugin

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METAHUMANCHARACTEREDITOR_API`
- L115 _namespace_ `namespace UE`
- L115 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterMeshImportContext.h` (Public)


#### struct `FMetaHumanCharacterEditorMeshImportContext`  
`struct FMetaHumanCharacterEditorMeshImportContext`  
_L13-36_
- desc: Struct holding data used for mesh import async tasks
- L16 _public member_ `TSharedPtr<FMeshImportTaskRunner> MeshImportTaskRunner;` — Task runner used to run mesh import process
- L19 _public member_ `double MeshImportStartTime = 0.0f;` — The start time of the mesh import process
- L22 _public member_ `FProgressNotificationHandle MeshImportProgressHandle;` — Handle used to update the progress on mesh import
- L25 _public member_ `TWeakPtr<SNotificationItem> MeshImportNotificationItem;` — Permanent notification item displayed while mesh importing
- L30 _public prototype_ `void MeshImportFinished();` — Marks the mesh import as finished and reset all of the state associated with it
- L35 _public prototype_ `bool HasActiveRequest() const;` — Returns true if there is an active mesh import process

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterService.h` (Public)


#### struct `FMetaHumanCharacterEditorCloudRequests`  
`struct FMetaHumanCharacterEditorCloudRequests`  
_L20-102_
- desc: Struct holding requests to the MetaHuman Cloud Services
- L23 _public member_ `TSharedPtr<UE::MetaHuman::FFaceTextureSynthesisServiceRequest> TextureSynthesis;` — A request to obtain high resolution textures
- L26 _public member_ `TSharedPtr<UE::MetaHuman::FBodyTextureSynthesisServiceRequest> BodyTextures;` — A request to obtain high resolution body textures
- L29 _public member_ `TSharedPtr<UE::MetaHuman::FAutoRigServiceRequest> AutoRig;` — A request to auto rig a character
- L32 _public member_ `double TextureSynthesisStartTime = 0.0f;` — The start time of the texture synthesis request
- L35 _public member_ `double BodyTextureStartTime = 0.0f;` — The start time of the body texture request
- L38 _public member_ `double AutoRiggingStartTime = 0.0f;` — The start time of the auto rig request
- L41 _public member_ `FProgressNotificationHandle TextureSynthesisProgressHandle;` — Handle used to update the progress on the texture download
- L44 _public member_ `FProgressNotificationHandle BodyTextureProgressHandle;` — Handle used to update the progress on the body texture download
- L47 _public member_ `FProgressNotificationHandle AutoRiggingProgressHandle;` — Handle used to update the progress of an auto rigging request
- L50 _public member_ `TWeakPtr<SNotificationItem> TextureSynthesisNotificationItem;` — Permanent notification item displayed while downloading high resolution textures
- L53 _public member_ `TWeakPtr<SNotificationItem> BodyTextureNotificationItem;` — Permanent notification item displayed while downloading high resolution body textures
- L56 _public member_ `TWeakPtr<SNotificationItem> AutoRiggingNotificationItem;` — Permanent notification item displayed while the auto rigging request is live
- L61 _public prototype_ `void TextureSynthesisRequestFinished();` — Marks the texture synthesis request as finished and reset all of the state associated with it
- L66 _public prototype_ `void BodyTextureRequestFinished();` — Marks the body texture request as finished and reset all of the state associated with it
- L71 _public prototype_ `void AutoRiggingRequestFinished();` — Marks the auto rigging request as finished and reset all of the state associated with it
- L76 _public prototype_ `bool HasActiveRequest() const;` — Returns true if there is an active texture synthesis or auto-rigging request
- L81 _public prototype_ `static void InitFaceAutoRigParams( const FMetaHumanCharacterIdentity::FState& InFaceState, TSharedRef<const IDNAReader> InFaceDNAReader, UE::MetaHuman::FTargetSolveParameters& OutAutoRigParameters);` — Initializes the passed FTargetSolveParameters from the input face data
- L92 _public prototype_ `static bool GenerateTexturesFromResponse( TSharedPtr<UE::MetaHuman::FFaceHighFrequencyData> InResponse, const class FMetaHumanFaceTextureSynthesizer& InFaceTextureSynthesizer, TSharedRef<struct FMetaHumanCharacterEditorData> InCharacterData, TNotNull<class UMetaHumanCharacter*> InMetaHumanCharacter);` — Generates the face textures from the data in the service respond. Normals and cavity are assigned directly, while albedos are synthesized using InFaceTextureSynthesizer. Returns true if the Character texture objects were updated
- L98 _public prototype_ `static bool GenerateBodyTexturesFromResponse( TSharedPtr<UE::MetaHuman::FBodyHighFrequencyData> InResponse, TSharedRef<FMetaHumanCharacterEditorData> InCharacterData, TNotNull<class UMetaHumanCharacter*> InMetaHumanCharacter);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterSkelmeshHelper.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCHARACTEREDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace Build` (scope `UE::MetaHuman`)
- L20 _prototype_ `USkeletalMesh* CreateNewIncompleteSkeletalIncludingMeshDescriptions( UObject* InOuter, TArray<UDynamicMesh*> FromDynamicMeshLODs, USkeleton* InSkeleton, FGeometryScriptCreateNewSkeletalMeshAssetOptions Options, EGeometryScriptOutcomePins& Outcome);` (scope `UE::MetaHuman::Build`) — Creates an incomplete transient skeletal mesh that only includes the skeleton and the updated mesh descriptions. Render data is not created or submitted. code is a stripped version of UGeometryScriptLibrary_CreateNewAssetFunctions::CreateNewSkeletalMeshAssetFromMeshLODs()

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Subsystem/MetaHumanCharacterSkinMaterials.h` (Public)


#### enum `EMetaHumanCharacterAccentRegion`  
`enum class EMetaHumanCharacterAccentRegion : uint8`  
_L19-31_
- reflection: `UENUM()`
- L21 _public enumerator_ `Scalp`
- L22 _public enumerator_ `Forehead`
- L23 _public enumerator_ `Nose`
- L24 _public enumerator_ `UnderEye`
- L25 _public enumerator_ `Cheeks`
- L26 _public enumerator_ `Lips`
- L27 _public enumerator_ `Chin`
- L28 _public enumerator_ `Ears`
- L30 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterAccentRegionParameter`  
`enum class EMetaHumanCharacterAccentRegionParameter : uint8`  
_L35-42_
- reflection: `UENUM()`
- L37 _public enumerator_ `Redness`
- L38 _public enumerator_ `Saturation`
- L39 _public enumerator_ `Lightness`
- L41 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterFrecklesParameter`  
`enum class EMetaHumanCharacterFrecklesParameter : uint8`  
_L46-55_
- reflection: `UENUM()`
- L48 _public enumerator_ `Mask`
- L49 _public enumerator_ `Density`
- L50 _public enumerator_ `Strength`
- L51 _public enumerator_ `Saturation`
- L52 _public enumerator_ `ToneShift`
- L54 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterPalmParameters`  
`enum class EMetaHumanCharacterPalmParameters : uint8`  
_L59-66_
- reflection: `UENUM()`
- L61 _public enumerator_ `Lightness`
- L62 _public enumerator_ `Tint`
- L63 _public enumerator_ `CavityDarkness`
- L65 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterNailParameters`  
`enum class EMetaHumanCharacterNailParameters : uint8`  
_L70-78_
- reflection: `UENUM()`
- L72 _public enumerator_ `TintColor`
- L73 _public enumerator_ `TintIntensity`
- L74 _public enumerator_ `Metallic`
- L75 _public enumerator_ `Roughness`
- L77 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterSkinMaterialOverrideRow`  
`struct FMetaHumanCharacterSkinMaterialOverrideRow : public FTableRowBase`  
_L82-88_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L87 _public member_ `TMap<FName, float> ScalarParameterValues;` — `UPROPERTY(EditAnywhere, Category = "Scalar Parameters")`

#### struct `FMetaHumanCharacterSkinMaterials`  
`struct FMetaHumanCharacterSkinMaterials`  
_L90-290_
- L95 _public prototype_ `static FName GetSkinMaterialSlotName(EMetaHumanCharacterSkinMaterialSlot InSlot);` — Returns the material slot names for the skin materials
- L103 _public prototype_ `static FName GetFaceTextureParameterName(EFaceTextureType InTextureType, bool bInWithVTSupport = false);` — @brief Returns the material parameter name for the a given synthesized texture type @param InTextureType the face texture type to get the parameter name for @param bInWithVTSupport Whether or not to return the virtual texture parameter name if supported
- L111 _public prototype_ `static FName GetBodyTextureParameterName(EBodyTextureType InTextureType, bool bInWithVTSupport = false);` — @brief Returns the material parameter name for the a given body texture type @param InTextureType the body texture type to get the parameter name for @param bInWithVTSupport Whether or not to return the virtual texture parameter name if supported
- L113 _public member_ `static const FName EyeLeftSlotName;`
- L114 _public member_ `static const FName EyeRightSlotName;`
- L115 _public member_ `static const FName SalivaSlotName;`
- L116 _public member_ `static const FName EyeShellSlotName;`
- L117 _public member_ `static const FName EyeEdgeSlotName;`
- L118 _public member_ `static const FName TeethSlotName;`
- L119 _public member_ `static const FName EyelashesSlotName;`
- L120 _public member_ `static const FName EyelashesHiLodSlotName;`
- L121 _public member_ `static const FName BodySlotName;`
- L122 _public member_ `static const FName UseCavityParamName;`
- L123 _public member_ `static const FName UseAnimatedMapsParamName;`
- L124 _public member_ `static const FName UseTextureOverrideParamName;`
- L125 _public member_ `static const FName RoughnessUIMultiplyParamName;`
- L127 _public prototype_ `static void ForEachFaceMaterialSlot(const FMetaHumanCharacterFaceMaterialSet& InMaterialSet, TFunction<void(FName, const class UMaterialInterface*)> InCallback);`
- L129 _public prototype_ `static void SetHeadMaterialsOnMesh(const FMetaHumanCharacterFaceMaterialSet& InMaterialSet, TNotNull<class USkeletalMesh*> InMesh);`
- L130 _public prototype_ `static void SetBodyMaterialOnMesh(TNotNull<class UMaterialInterface*> InBodyMaterial, TNotNull<class USkeletalMesh*> InMesh);`
- L135 _public prototype_ `static FMetaHumanCharacterFaceMaterialSet GetHeadMaterialsFromMesh(TNotNull<class USkeletalMesh*> InFaceMesh);` — Creates a Face Material set from the materials in the given face mesh
- L138 _public member_ `static constexpr int32 FoundationPaletteColumns = 7;` — Number of rows and columns to use when building the foundation color picker palette
- L139 _public member_ `static constexpr int32 FoundationPaletteRows = 5;`
- L140 _public member_ `static constexpr float FoundationSaturationShift = 0.1f;`
- L141 _public member_ `static constexpr float FoundationValueShift = 0.1f;`
- L147 _public prototype_ `static FLinearColor ShiftFoundationColor(const FLinearColor& InColor, int32 InColorIndex, int32 InShowColumns, int32 InShowRows, float InSaturationShift, float InValueShift);` — Shifts the input color based on the preset index to calculate the final foundation color to apply. If InColorIndex is INDEX_NONE returns InColor so that no shift happens.
- L149 _public prototype_ `static void ApplyTextureOverrideParameterToMaterials(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinSettings& InSkinSettings);`
- L156 _public prototype_ `static void ApplyMaterialOverrides( FMetaHumanCharacterFaceMaterialSet& InOutFaceMaterialSet, UMaterialInstanceDynamic*& InOutBodyMaterial, const FMetaHumanCharacterSkinSettings& InSkinSettings, EMetaHumanCharacterSkinPreviewMaterial InPreviewMaterialType);` — Replaces the default preview MIDs with new ones parented to override MICs. Skin and Body overrides only apply in Editable preview mode. Eye, teeth, and eyelash overrides apply in all preview modes.
- L165 _public prototype_ `static void ApplySkinParametersToMaterials(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<class UMaterialInstanceDynamic*> InBodyMID, const FMetaHumanCharacterSkinSettings& InSkinSettings);` — Apply skin material parameter overrides based on the face texture index for better visuals
- L170 _public prototype_ `static void ApplyRoughnessMultiplyToMaterials(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinSettings& InSkinSettings);` — Apply the Roughness UI Multiply to the skin materials
- L175 _public prototype_ `static void ApplyPalmParametersToMaterial(TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinProperties& InSkinProps);` — Apply skin palm parameters (Lightness, Tint, and Cavity Darkness) to the body material
- L180 _public prototype_ `static void ApplyNailParametersToMaterial(TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinProperties& InSkinProps, const FString& InNailPrefix);` — Apply skin nail parameters (TintColor, TintIntensity, Metallic, and Roughness) to the body material
- L185 _public prototype_ `static void ApplyFingernailParametersToMaterial(TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinProperties& InSkinProps);` — Apply skin fingernail parameters (TintColor, TintIntensity, Metallic, and Roughness) to the body material
- L190 _public prototype_ `static void ApplyToenailParametersToMaterial(TNotNull<class UMaterialInstanceDynamic*> InBodyMaterial, const FMetaHumanCharacterSkinProperties& InSkinProps);` — Apply skin toenail parameters (TintColor, TintIntensity, Metallic, and Roughness) to the body material
- L195 _public prototype_ `static void ApplySkinAccentParameterToMaterial( const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, EMetaHumanCharacterAccentRegion InRegion, EMetaHumanCharacterAccentRegionParameter InParameter, float InValue);` — Update the preview material parameter value of the given accent region.
- L204 _public prototype_ `static void ApplySkinAccentsToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterAccentRegions& InAccentProperties);` — Updates the accent region parameters in the given face material set
- L209 _public prototype_ `static void ApplyFrecklesMaskToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, EMetaHumanCharacterFrecklesMask InMask);` — Updates the freckles mask in the given face material set
- L214 _public prototype_ `static void ApplyFrecklesParameterToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, EMetaHumanCharacterFrecklesParameter InParam, float InValue);` — Updates one of the freckles material parameters in the given face material set
- L219 _public prototype_ `static void ApplyFrecklesToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterFrecklesProperties& InFrecklesProperties);` — Updates all freckle parameters in the given face material set
- L227 _public prototype_ `static void ApplyFoundationMakeupToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterFoundationMakeupProperties& InFoundationMakeupProperties, bool bInWithVTSupport);` — @brief Apply makeup settings to the given face material set @param InFaceMaterialSet the set of face materials to where the foundation properties are going to be applied @param bInWithVTSupport Whether or not apply textures to virtual texture slots when supported
- L228 _public prototype_ `static void ApplyEyeMakeupToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterEyeMakeupProperties& InEyeMakeupProperties, bool bInWithVTSupport);`
- L229 _public prototype_ `static void ApplyBlushMakeupToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterBlushMakeupProperties& InBlushMakeupProperties, bool bInWithVTSupport);`
- L230 _public prototype_ `static void ApplyLipsMakeupToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterLipsMakeupProperties& InLipsMakeupProperties, bool bInWithVTSupport);`
- L235 _public prototype_ `static void ApplySynthesizedTexturesToFaceMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const TMap<EFaceTextureType, TObjectPtr<UTexture2D>>& InSynthesizedFaceTextures);` — Helper to apply update the MH face material so that it references the (transient) synthesized textures
- L240 _public prototype_ `static void ApplyEyeSettingsToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterEyesSettings& InEyeSettings);` — Helper to apply all eye material settings to the given face material set
- L245 _public prototype_ `static FLinearColor GetScleraTintBasedOnSkinTone(const FMetaHumanCharacterSkinSettings& InSkinSettings);` — Compute the Sclera tint based on the current Skin Tone
- L250 _public prototype_ `static void GetDefaultEyeSettings(FMetaHumanCharacterEyesSettings& OutEyeSettings);` — Read the eye settings from the default eye material
- L255 _public prototype_ `static void ApplyEyelashesPropertiesToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterEyelashesProperties& InEyelashesProperties, const bool bAlwaysUseCards);` — Applies eyelashes material properties to given face material set
- L260 _public prototype_ `static void ToggleEyelashesMaterialOpacity(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, bool bEyelashesGroomEnabled, bool bAlwaysUseHairCards);` — Toggles opacity for eyelashes material set for lower LODs which can have both strands and cards.
- L265 _public prototype_ `static void ApplyTeethPropertiesToMaterial(const FMetaHumanCharacterFaceMaterialSet& InFaceMaterialSet, const FMetaHumanCharacterTeethProperties& InTeethProperties);` — Applies teeth material properties to given face material set
- L272 _public prototype_ `static FMetaHumanCharacterFaceMaterialSet GetHeadPreviewMaterialInstance(EMetaHumanCharacterSkinPreviewMaterial InPreviewMaterialType, bool bInWithVTSupport);` — @brief Returns a new material instance for the head for a given preview material type @param bInWithVTSupport Returns the materials that have support for virtual textures
- L279 _public prototype_ `static class UMaterialInstanceDynamic* GetBodyPreviewMaterialInstance(EMetaHumanCharacterSkinPreviewMaterial InPreviewMaterialType, bool bInWithVTSupport);` — Returns a new material instance for the body for a given preview material type @param bInWithVTSupport Returns the materials that have support for virtual texures
- L284 _public prototype_ `static void SetMaterialInstanceParent(TNotNull<class UMaterialInstanceConstant*> InMaterial, TNotNull<class UMaterialInterface*> InNewParent);` — Set the parent of InMaterial to InNewParent preserving overrides and static switches
- L289 _public prototype_ `static class UTexture2D* GetEyelashesMask(const FMetaHumanCharacterEyelashesProperties& InEyelashesProperties);` — Returns the active mask texture used for the eyelashes mesh given the input eyelashes properties

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METAHUMANCHARACTEREDITOR_API`
- L32 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterAccentRegion, EMetaHumanCharacterAccentRegion::Count);`
- L43 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterAccentRegionParameter, EMetaHumanCharacterAccentRegionParameter::Count);`
- L56 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterFrecklesParameter, EMetaHumanCharacterFrecklesParameter::Count);`
- L67 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterPalmParameters, EMetaHumanCharacterPalmParameters::Count);`
- L79 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterNailParameters, EMetaHumanCharacterNailParameters::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Tools/MetaHumanCharacterExternalImportTool.h` (Public)


#### class `UMetaHumanCharacterExternalImportTool`  
`class UMetaHumanCharacterExternalImportTool : public USingleSelectionTool`  
_L24-43_
- reflection: `UCLASS(Abstract, Transient)`
- inherits: `USingleSelectionTool`
- desc: Abstract base class for externally-contributed MetaHuman import tools. External plugins should: 1. Derive their tool UClass from UMetaHumanCharacterExternalImportTool. 2. Override CanApply() and Apply(). 3. Optionally override GetWarningText(). 4. Implement IMetaHumanImportToolFeature and register via IModularFeatures. The host framework calls these methods to drive the Apply button state and action. Use GetTargetMetaHumanCharacter() inside Apply() to obtain the MetaHuman Character being edited.
- L30 _public prototype_ `virtual bool CanApply() const PURE_VIRTUAL(UMetaHumanCharacterExternalImportTool::CanApply, return false;);` — Returns true when the Apply button should be enabled.
- L34 _public prototype_ `virtual void Apply() PURE_VIRTUAL(UMetaHumanCharacterExternalImportTool::Apply,);` — Called when the Apply button is clicked.
- L38 _public prototype_ `virtual FText GetWarningText() const;` — Warning text shown above the content area. Return empty to hide. Defaults to empty.
- L42 _protected prototype_ `UMetaHumanCharacter* GetTargetMetaHumanCharacter() const;` — Returns the MetaHuman Character asset that is currently being edited.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Tools/MetaHumanImportToolFeature.h` (Public)


#### class `IMetaHumanImportToolFeature`  
`class IMetaHumanImportToolFeature : public IModularFeature`  
_L28-65_
- inherits: `IModularFeature`
- desc: Modular feature interface implemented by external plugins to contribute an import tool to the MetaHuman Character Editor's Import palette. External plugins should: 1. Subclass IMetaHumanImportToolFeature and implement all pure virtual methods. 2. Declare a static instance of their subclass. 3. In StartupModule(), call: IModularFeatures::Get().RegisterModularFeature(IMetaHumanImportToolFeature::GetModularFeatureName(), &MyFeature); 4. In ShutdownModule(), call: IModularFeatures::Get().UnregisterModularFeature(IMetaHumanImportToolFeature::GetModularFeatureName(), &MyFeature);
- L32 _public function_ `static FName GetModularFeatureName()` — Feature name key used with IModularFeatures::Get().
- L39 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetCommand() const = 0;` — Command for the palette toggle button. Must be registered before the editor mode enters.
- L45 _public prototype_ `virtual UInteractiveToolBuilder* CreateBuilder(UObject* Outer) const = 0;` — Creates the tool builder. Outer is the EdMode (matching internal tool creation via NewObject<Builder>(this)).
- L51 _public prototype_ `virtual TSharedRef<SWidget> CreateContent(UMetaHumanCharacterExternalImportTool* Tool) const = 0;` — Creates the scrollable content widget shown in the tool's panel. Do NOT include an Apply button — it is provided by the host framework.
- L58 _public prototype_ `virtual TSubclassOf<UMetaHumanCharacterExternalImportTool> GetToolClass() const = 0;` — The concrete UClass of the tool. Used to match the active tool in CreateToolView() via Tool->IsA(GetToolClass()). Must be a subclass of UMetaHumanCharacterExternalImportTool.
- L64 _public function_ `virtual FSlateIcon GetIcon() const` — Optional icon shown on the palette toggle button. Return a default-constructed FSlateIcon() (IsSet() == false) to show no icon.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/Verification/MetaHumanCharacterValidation.h` (Public)


#### class `UMetaHumanCharacterValidationContext`  
`class UMetaHumanCharacterValidationContext : public UObject , public IMetaHumanValidationContext`  
_L18-118_
- reflection: `UCLASS()`
- inherits: `UObject,IMetaHumanValidationContext`
- desc: Validation context used to encapsulate the validation process of MetaHuman Character items
- L27 _public prototype_ `virtual bool ValidateWardrobeItem(const class UMetaHumanWardrobeItem* InWardrobeItem) override;`
- L44 _public prototype_ `static UMetaHumanCharacterValidationContext* BeginReport(const FBeginReportParams& InReportParams);` — @brief Begin a new report by constructing a validation context that can be used to validate items @param InReportParams parameters to configure the report
- L52 _public prototype_ `TSharedRef<FTokenizedMessage> AddMessage(EMessageSeverity::Type InSeverity);` — @brief Adds a new message to the report of the given severity @param InSeverity the severity of the message to be added @return Reference to the newly added message so more tokens can be added to it
- L57 _public prototype_ `const TArray<TSharedRef<FTokenizedMessage>>& GetMessages() const;` — @brief Return all the messages currently stored in the context
- L62 _public prototype_ `void CancelReport();` — @brief Cancel the current report meaning that when EndReport is called no messages are going to be displayed in the Message Log
- L67 _public prototype_ `void EndReport();` — @brief Ends the current report and displays the Message Log if there are errors or warnings collected in the report
- L106 _private member_ `TObjectPtr<UObject> ObjectBeingValidated;` — `UPROPERTY()` — The object being validated
- L110 _private member_ `bool bSilent = false;` — `UPROPERTY()` — Makes the internal report silent, meaning no messages are to be printed in the logs
- L114 _private member_ `bool bCancelled = false;` — `UPROPERTY()` — True if the report was cancelled
- L117 _private member_ `TArray<TSharedRef<FTokenizedMessage>> TokenizedMessages;` — Current list of messages the report contains

#### struct `UMetaHumanCharacterValidationContext::FBeginReportParams`  
`struct FBeginReportParams`  
_L30-37_
- L33 _public member_ `UObject* ObjectToValidate = nullptr;` — The object to be validated
- L36 _public member_ `bool bSilent = false;` — Prevents message from being logged in the Output Log

#### struct `UMetaHumanCharacterValidationContext::FScopedReport`  
`struct FScopedReport`  
_L74-99_
- desc: @brief Utility to scope a report making sure its closed on the end of a scope
- L76 _public function_ `FScopedReport(const UMetaHumanCharacterValidationContext::FBeginReportParams& InParams) : Context`
- L81 _public function_ `~FScopedReport()`
- L90 _public function_ `void Cancel() const`
- L98 _public member_ `TStrongObjectPtr<UMetaHumanCharacterValidationContext> Context;`
