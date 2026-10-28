# Plugins / MoverCVDEditor

- module root: `Plugins/Experimental/Mover/Source/MoverCVDEditor`
- headers: 7; symbols: 64
- symbol kinds: class=7, enum=1, enumerator=2, function=1, member=21, prototype=31, struct=1
- PrivateDependencyModuleNames: ApplicationCore, ChaosVD, ChaosVDData, ChaosVDRuntime, CoreUObject, EditorWidgets, Engine, Mover, MoverCVDData, Projects, Slate, SlateCore, ToolMenus, TraceServices, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDExtension.h` (Private)


#### class `FMoverCVDExtension`  
`class FMoverCVDExtension final : public FChaosVDExtension`  
_L14-29_
- inherits: `FChaosVDExtension`
- desc: MoverCVDExtension is where we register MoverCVDTab as a displayable tab, register MoverCVDSimDataProcessor and give access to the MoverSimDataComponent
- L18 _public prototype_ `FMoverCVDExtension();`
- L21 _public prototype_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider) override;`
- L22 _public prototype_ `virtual TConstArrayView<TSubclassOf<UActorComponent>> GetSolverDataComponentsClasses() override;`
- L25 _public prototype_ `virtual void RegisterCustomTabSpawners(const TSharedRef<SChaosVDMainTab>& InParentTabWidget) override;` — Registers all available Tab Spawner instances in this extension, if any
- L28 _private member_ `TArray<TSubclassOf<UActorComponent>> DataComponentsClasses;`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDSimDataComponent.h` (Private)


#### struct `FDeserializedMoverStates`  
`struct FDeserializedMoverStates`  
_L13-18_
- L15 _public member_ `TSharedPtr<FMoverSyncState> SyncState;`
- L16 _public member_ `TSharedPtr<FMoverInputCmdContext> InputCommand;`
- L17 _public member_ `TArray<TPair<FName, TSharedPtr<FMoverDataCollection>>> LocalSimDataSections;`

#### class `UMoverCVDSimDataComponent`  
`class UMoverCVDSimDataComponent : public UChaosVDSolverDataComponent`  
_L22-53_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- desc: Component holding Mover data for the current visualized frame
- L31 _public prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;` — That we chose to implement this function and not UpdateFromNewGameFrameData or UpdateFromNewSolverStageData is tied to the implementation of FMoverCVDSimDataProcessor, which currently add ths information to FChaosVDTraceProvider::GetCurrentSolverFrame() Eventually we will record information at different stages of a solver frame and will be using UpdateFromNewSolverStageData instead, to show the state of the sync state at the beginning of the frame, then at the end
- L33 _public prototype_ `virtual void ClearData() override;`
- L35 _public function_ `TConstArrayView<TSharedPtr<FMoverCVDSimDataWrapper>> GetFrameSimDataArray() const`
- L40 _public prototype_ `bool FindAndUnwrapSimDataForParticle( uint32 ParticleID, TSharedPtr<FMoverCVDSimDataWrapper>& OutSimDataWrapper, TSharedPtr<FMoverSyncState>& OutSyncState, TSharedPtr<FMoverInputCmdContext>& OutInputCmd, TArray<TPair<FName, TSharedPtr<FMoverDataCollection>>>& OutLocalSimDataSections);`
- L50 _private member_ `TArray<TSharedPtr<FMoverCVDSimDataWrapper>> FrameSimDataArray;` — This is the array of FMoverCVDSimDataWrapper for the current frame (as it is updated in UpdateFromNewGameFrameData) and corresponding to this DataComponent's SolverID
- L52 _private member_ `TMap<FMoverCVDSimDataWrapper*, TSharedPtr<FDeserializedMoverStates>> DeserializedStates;`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDSimDataProcessor.h` (Private)


#### class `FMoverCVDSimDataProcessor`  
`class FMoverCVDSimDataProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Mover data
- L13 _public prototype_ `explicit FMoverCVDSimDataProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDSimDataSettings.h` (Private)


#### enum `EMoverCVDSimDataVisualizationFlags`  
`enum class EMoverCVDSimDataVisualizationFlags : uint32`  
_L10-14_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Set of visualization flags options for Mover Sim Data
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L13 _public enumerator_ `EnableDraw = 1 << 0`

#### class `UMoverCVDSimDataSettings`  
`class UMoverCVDSimDataSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L18-46_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L26 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — If true, any debug draw text available will be drawn
- L30 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L34 _public member_ `float BaseThickness = 2.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — Thickness to apply to any debug draw shape controlled by this setting.
- L36 _public prototype_ `static void SetDataVisualizationFlags(EMoverCVDSimDataVisualizationFlags NewFlags);`
- L37 _public prototype_ `static EMoverCVDSimDataVisualizationFlags GetDataVisualizationFlags();`
- L39 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L45 _private member_ `uint32 DebugDrawFlags = static_cast<uint32>(EMoverCVDSimDataVisualizationFlags::None);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/MoverCVDEditor.EMoverCVDSimDataVisualizationFlags"))` — Set of flags to enable/disable visualization of debug draw data shapes

#### Free symbols / members of external scopes

- L15 _prototype_ `ENUM_CLASS_FLAGS(EMoverCVDSimDataVisualizationFlags);`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDStyle.h` (Private)


#### class `FMoverCVDStyle`  
`class FMoverCVDStyle`  
_L11-30_
- L15 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L19 _public prototype_ `static void ReloadTextures();`
- L21 _public prototype_ `static const ISlateStyle& Get();`
- L23 _public prototype_ `static FName GetStyleSetName();`
- L27 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L29 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDTab.h` (Private)


#### class `FMoverCVDTab`  
`class FMoverCVDTab : public FChaosVDObjectDetailsTab`  
_L22-60_
- inherits: `FChaosVDObjectDetailsTab`
- desc: This tab is an additional details tab displaying mover info corresponding to the selected particles if they are moved by a Mover component
- L26 _public prototype_ `FMoverCVDTab(const FName& InTabID, TSharedPtr<FTabManager> InTabManager, TWeakPtr<SChaosVDMainTab> InOwningTabWidget);`
- L27 _public prototype_ `virtual ~FMoverCVDTab();`
- L30 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;` — Implementation of FChaosVDObjectDetailsTab
- L31 _public prototype_ `virtual void HandlePostSelectionChange(const UTypedElementSelectionSet* ChangedSelectionSet) override;`
- L33 _public prototype_ `virtual void HandleSolverDataSelectionChange(const TSharedPtr<FChaosVDSolverDataSelectionHandle>& SelectionHandle) override;`
- L36 _public prototype_ `void HandleSceneUpdated();` — Scene callbacks
- L39 _private prototype_ `void DisplaySingleParticleInfo(int32 SelectedSolverID, int32 SelectedParticleID);`
- L40 _private prototype_ `void DisplayMoverInfoForSelectedElements(const TArray<FTypedElementHandle>& SelectedElementHandles);`
- L43 _private prototype_ `void RetrieveAllSolversMoverDataComponents();` — This function retrieves and caches all the mover data components for all solvers, populating SolverToSimDataComponentMap
- L45 _private prototype_ `TWeakObjectPtr<UMoverCVDSimDataComponent>* FindMoverDataComponentForSolver(int32 SolverID);`
- L47 _private member_ `TWeakPtr<FChaosVDScene> SceneWeakPtr;`
- L49 _private member_ `TMap<int32, TWeakObjectPtr<UMoverCVDSimDataComponent>> SolverToSimDataComponentMap;`
- L51 _private member_ `int32 CurrentlyDisplayedParticleID = INDEX_NONE;`
- L52 _private member_ `int32 CurrentlyDisplayedSolverID = INDEX_NONE;`
- L54 _private member_ `FChaosVDSelectionMultipleView MultiViewWrapper;`
- L56 _private member_ `TSharedPtr<FMoverCVDSimDataWrapper> MoverSimDataWrapper;`
- L57 _private member_ `TSharedPtr<FMoverSyncState> MoverSyncState;`
- L58 _private member_ `TSharedPtr<FMoverInputCmdContext> MoverInputCmd;`
- L59 _private member_ `TArray<TPair<FName, TSharedPtr<FMoverDataCollection>>> MoverLocalSimDataSections;`

### `Plugins/Experimental/Mover/Source/MoverCVDEditor/Public/MoverCVDEditor.h` (Public)


#### class `FMoverCVDEditorModule`  
`class FMoverCVDEditorModule : public IModuleInterface`  
_L18-27_
- inherits: `IModuleInterface`
- desc: This module contains the Editor side of the Mover support in Chaos Visual Debugger (CVD) Mover is a module responsible for the movement of actors and its replication, for instance the input controlled movement of characters This module allows the display and recording specific data in CVD that makes it easier to understand and debug Mover MoverCVDTab is the tab in CVD where that information is displayed MoverCVDSimDataProcessor is the receiving and processing end of the Mover data trace ("Sim Data") that the game sends to CVD MoverSimDataComponent is a component holding Mover data for the current visualized frame MoverCVDExtension is where we register MoverCVDTab as a displayable tab, register MoverCVDSimDataProcessor and give access to the MoverSimDataComponent
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private member_ `TArray<TWeakPtr<FChaosVDExtension>> AvailableExtensions;`
