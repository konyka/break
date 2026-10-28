# Plugins / WaveFunctionCollapse

- module root: `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse`
- headers: 5; symbols: 113
- symbol kinds: class=5, enum=1, enumerator=6, function=10, member=33, prototype=51, struct=7
- PrivateDependencyModuleNames: CoreUObject, Engine, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: AssetTools, Blutility, Core, EditorFramework, EditorStyle, EditorSubsystem, LevelEditor, PropertyEditor, UMG, UMGEditor, UnrealEd

### `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse/Private/WaveFunctionCollapseEditorCommands.h` (Private)


#### class `FWaveFunctionCollapseEditorCommands`  
`class FWaveFunctionCollapseEditorCommands : public TCommands<FWaveFunctionCollapseEditorCommands>`  
_L8-27_
- inherits: `TCommands<FWaveFunctionCollapseEditorCommands>`
- L12 _public function_ `FWaveFunctionCollapseEditorCommands() : TCommands<FWaveFunctionCollapseEditorCommands> ( TEXT("WaveFunctionCollapse"), NSLOCTEXT("Contexts", "WaveFunctionCollapse", "WaveFunctionCollapse Plugin"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> WaveFunctionCollapseWidget;`

### `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse/Public/WaveFunctionCollapse.h` (Public)


#### class `FWaveFunctionCollapseModule`  
`class FWaveFunctionCollapseModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `void AddMenuEntry(FMenuBuilder& MenuBuilder);`
- L21 _private prototype_ `void WaveFunctionCollapseUI();`
- L23 _private member_ `TSharedPtr<class FUICommandList> PluginCommands;`

### `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse/Public/WaveFunctionCollapseBPLibrary.h` (Public)


#### struct `FWaveFunctionCollapseNeighbor`  
`struct FWaveFunctionCollapseNeighbor`  
_L10-22_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `EWaveFunctionCollapseAdjacency Adjacency = EWaveFunctionCollapseAdjacency::Front;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L18 _public member_ `int32 Step = 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L21 _public member_ `FSoftObjectPath NeighborObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.Blueprint"))`

#### struct `FWaveFunctionCollapseNeighborRule`  
`struct FWaveFunctionCollapseNeighborRule`  
_L25-46_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `FSoftObjectPath KeyObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.Blueprint"))`
- L33 _public member_ `TArray<FWaveFunctionCollapseNeighbor> Neighbors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L36 _public member_ `TArray<FSoftObjectPath> SpawnObjects;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.Blueprint"))`
- L39 _public member_ `FTransform SpawnRelativeTransform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L45 _public member_ `float SpawnChance = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (ClampMin = "0", ClampMax = "1"))` — SpawnChance 1 = 100 % chance to spawn, SpawnChance 0 = 0 % chance to spawn

#### class `UWaveFunctionCollapseBPLibrary`  
`class UWaveFunctionCollapseBPLibrary : public UBlueprintFunctionLibrary`  
_L49-193_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L59 _private prototype_ `static float CalculateShannonEntropy(const TArray<FWaveFunctionCollapseOption>& Options, UWaveFunctionCollapseModel* WFCModel);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Calculates Shannon Entropy from an array of options and a given model @param Options Array of options @param WFCModel WaveFunctionCollapseModel that stores weights for options
- L68 _private prototype_ `static int32 PositionAsIndex(FIntVector Position, FIntVector Resolution);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Convert 3D grid position to 2D array index @param Position 3D grid position @param Resolution Grid resolution @return 2D array index
- L77 _private prototype_ `static FIntVector IndexAsPosition(int32 Index, FIntVector Resolution);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Convert 2D array index to 3D grid position @param Index 2D array index @param Resolution @return 3D grid position
- L84 _private prototype_ `static FWaveFunctionCollapseTile BuildInitialTile(UWaveFunctionCollapseModel* WFCModel);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse", meta = (ScriptMethod))` — Builds the initial tile which adds every unique option in a model to its RemainingOptions array and calculates its entropy @param WFCModel WaveFunctionCollapseModel
- L93 _private prototype_ `static TMap<int32, EWaveFunctionCollapseAdjacency> GetAdjacentIndices(int32 Index, FIntVector Resolution);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get adjacent indices of a given index and its adjacency @param Index 2D array index @param Resolution @return Map of valid adjacent indices and its adjacency in relation to the given index
- L102 _private prototype_ `static TMap<FIntVector, EWaveFunctionCollapseAdjacency> GetAdjacentPositions(FIntVector Position, FIntVector Resolution);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get adjacent positions of a given position and its adjacency @param Position 3D grid position @param Resolution Grid resolution @return Map of valid adjacent positions and its adjacency in relation to the given position
- L110 _private prototype_ `static bool IsOptionContained(const FWaveFunctionCollapseOption& Option, const TArray<FWaveFunctionCollapseOption>& Options);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Is the option contained in the given options array @param Option Option to check for @param Options Array of options
- L117 _private prototype_ `static EWaveFunctionCollapseAdjacency GetOppositeAdjacency(EWaveFunctionCollapseAdjacency Adjacency);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Get the opposite adjacency for a given adjacency.  For example GetOppositeAdjacency(Front) will return Back. @param Adjacency Adjacency direction
- L126 _private prototype_ `static EWaveFunctionCollapseAdjacency GetNextZAxisClockwiseAdjacency(EWaveFunctionCollapseAdjacency Adjacency);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Get the next adjacency in clockwise direction on a Z-axis for a given adjacency. For example GetNextZAxisClockwiseAdjacency(Front) will return Right. Up or Down will return the original adjacency. @param Adjacency Adjacency direction
- L132 _private prototype_ `static void AddToAdjacencyToOptionsMap(UPARAM(ref) FWaveFunctionCollapseAdjacencyToOptionsMap& AdjacencyToOptionsMap, EWaveFunctionCollapseAdjacency Adjacency, FWaveFunctionCollapseOption Option);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Add an entry to an AdjacencyToOptionsMap
- L135 _private prototype_ `static bool IsSoftObjPathEqual(const FSoftObjectPath& SoftObjectPathA, const FSoftObjectPath& SoftObjectPathB);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")`
- L141 _private prototype_ `static FRotator SanitizeRotator(FRotator Rotator);` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Converts Rotator to Matrix and back to sanitize multiple representations of the same rotation to a common Rotator value
- L155 _private prototype_ `static void DeriveModelFromActors(UPARAM(ref) const TArray<AActor*>& Actors, UWaveFunctionCollapseModel* WFCModel, float TileSize, bool bIsBorderEmptyOption, bool bIsMinZFloorOption, bool bUseUniformWeightDistribution, bool bAutoDeriveZAxisRotationConstraints, const TArray<FSoftObjectPath>& SpawnExclusionAssets, const TArray<FSoftObjectPath>& IgnoreRotationAssets);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Derive constraints from a given layout of actors and append them to a model @param Actors array of actors to evaluate @param WFCModel to add constraints to @param TileSize distance between tiles @param bIsBorderEmptyOption should the border be considered EmptyOption @param bIsMinZFloorOption should the minimum Z actors be considered floor options (nothing can go below it) @param bAutoDeriveZAxisRotationConstraints should it auto derive z-axis rotational variants @param SpawnExclusionAssets assets to exclude when spawning @param IgnoreRotationAssets assets to ignore rotation variants
- L174 _private prototype_ `static bool GetPositionToOptionMapFromActor(AActor* Actor, float TileSize, UPARAM(ref) TMap<FIntVector, FWaveFunctionCollapseOption>& PositionToOptionMap);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get PositionToOptionsMap from a given actor that has ISM components. This is useful when you want to derive neighboring tile data from a WFC-solved actor to be used for post processing. This will only evaluate ISM components. @param Actor Actor with ISM components @param TileSize distance between tiles @param PositionToOptionMap
- L180 _private prototype_ `static FWaveFunctionCollapseOption MakeEmptyOption();` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Make FWaveFunctionCollapseOption of type: EmptyOption
- L186 _private prototype_ `static FWaveFunctionCollapseOption MakeBorderOption();` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Make FWaveFunctionCollapseOption of type: BorderOption
- L192 _private prototype_ `static FWaveFunctionCollapseOption MakeVoidOption();` — `UFUNCTION(BlueprintPure, Category = "WaveFunctionCollapse")` — Make FWaveFunctionCollapseOption of type: VoidOption

### `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse/Public/WaveFunctionCollapseModel.h` (Public)


#### enum `EWaveFunctionCollapseAdjacency`  
`enum class EWaveFunctionCollapseAdjacency : uint8`  
_L10-18_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Front UMETA(DisplayName = "X+ Front")`
- L13 _public enumerator_ `Back UMETA(DisplayName = "X- Back")`
- L14 _public enumerator_ `Right UMETA(DisplayName = "Y+ Right")`
- L15 _public enumerator_ `Left UMETA(DisplayName = "Y- Left")`
- L16 _public enumerator_ `Up UMETA(DisplayName = "Z+ Up")`
- L17 _public enumerator_ `Down UMETA(DisplayName = "Z- Down")`

#### struct `FWaveFunctionCollapseOption`  
`struct FWaveFunctionCollapseOption`  
_L24-77_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base Option Struct which holds an object, its orientation and scale
- L29 _public member_ `FSoftObjectPath BaseObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.Blueprint"))`
- L32 _public member_ `FRotator BaseRotator = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L35 _public member_ `FVector BaseScale3D = FVector::OneVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L37 _public prototype_ `FWaveFunctionCollapseOption() = default;`
- L39 _public function_ `FWaveFunctionCollapseOption(FString Object, FRotator Rotator, FVector Scale3d)`
- L46 _public function_ `FWaveFunctionCollapseOption(FString Object)`
- L51 _public member_ `static const FWaveFunctionCollapseOption EmptyOption;`
- L52 _public member_ `static const FWaveFunctionCollapseOption BorderOption;`
- L53 _public member_ `static const FWaveFunctionCollapseOption VoidOption;`
- L63 _public function_ `bool operator==(const FWaveFunctionCollapseOption& Rhs) const`
- L68 _public function_ `bool operator!=(const FWaveFunctionCollapseOption& Rhs) const`
- L73 _public function_ `bool IsBaseObject(FString ObjectPath)`

#### struct `FWaveFunctionCollapseOptions`  
`struct FWaveFunctionCollapseOptions`  
_L83-89_
- reflection: `USTRUCT(BlueprintType)`
- desc: Container struct for array of Options
- L88 _public member_ `TArray<FWaveFunctionCollapseOption> Options;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`

#### struct `FWaveFunctionCollapseAdjacencyToOptionsMap`  
`struct FWaveFunctionCollapseAdjacencyToOptionsMap`  
_L96-115_
- reflection: `USTRUCT(BlueprintType)`
- desc: Container struct for AdjacencyToOptionsMap Stores the weight and contribution of an option
- L105 _public member_ `int32 Contribution = 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (ClampMin = "0"))` — The amount of times an option is present when deriving a model. This value is used to calculate its weight.
- L111 _public member_ `float Weight;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (ClampMin = "0", ClampMax = "1"))` — The weight of an option calculated by dividing this Contribution by the sum of all contributions of all options.
- L114 _public member_ `TMap<EWaveFunctionCollapseAdjacency, FWaveFunctionCollapseOptions> AdjacencyToOptionsMap;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`

#### class `UWaveFunctionCollapseModel`  
`class UWaveFunctionCollapseModel : public UDataAsset`  
_L122-204_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDataAsset`
- desc: A Model of WFC constraints. This data asset should contain all necessary data to allow for a WFC solve of an arbitrary grid size.
- L131 _public member_ `float TileSize;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")` — Grid Tile Size in cm^3
- L134 _public member_ `TMap<FWaveFunctionCollapseOption, FWaveFunctionCollapseAdjacencyToOptionsMap> Constraints;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L137 _public member_ `TArray<FSoftObjectPath> SpawnExclusion;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse", meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.Blueprint"))`
- L146 _public prototype_ `void AddConstraint(const FWaveFunctionCollapseOption& KeyOption, EWaveFunctionCollapseAdjacency Adjacency, const FWaveFunctionCollapseOption& AdjacentOption);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Create a constraint @param KeyOption Key option @param Adjacency Adjacency from KeyOption to AdjacentOption @param AdjacentOption Adjacent option
- L154 _public prototype_ `FWaveFunctionCollapseOptions GetOptions(const FWaveFunctionCollapseOption& KeyOption, EWaveFunctionCollapseAdjacency Adjacency) const;` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get all options for a given key option in a given adjacency @param KeyOption Key option @param Adjacency Adjacency from KeyOption to AdjacentOption
- L160 _public prototype_ `void SetWeightsFromContributions();` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Set the weights of key objects based on their contribution values
- L166 _public prototype_ `void SetAllWeights(float Weight);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Set the weights of key objects to a given value
- L172 _public prototype_ `void SetAllContributions(int32 Contribution);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Set the contribution values of key objects to a given value
- L178 _public prototype_ `void SetOptionContribution(const FWaveFunctionCollapseOption& Option, int32 Contribution);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Set the contribution value of a key object to a given value
- L184 _public prototype_ `float GetOptionWeight(const FWaveFunctionCollapseOption& Option) const;` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get the weight value of an option
- L190 _public prototype_ `int32 GetOptionContribution(const FWaveFunctionCollapseOption& Option) const;` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get the contribution value of an option
- L196 _public prototype_ `int32 GetConstraintCount() const;` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Get the total count of constraints in this model
- L203 _public prototype_ `void SwapMeshes(TMap<UStaticMesh*, UStaticMesh*> SourceToTargetMeshMap);` — `UFUNCTION(BlueprintCallable, Category = "WaveFunctionCollapse")` — Swap meshes in the model with other meshes based on a map. This is useful when working with template meshes that need to be swapped.

#### struct `FWaveFunctionCollapseTile`  
`struct FWaveFunctionCollapseTile`  
_L210-234_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base Tile Struct which holds an array of remaining Options and its Shannon Entropy value
- L215 _public member_ `float ShannonEntropy;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L218 _public member_ `TArray<FWaveFunctionCollapseOption> RemainingOptions;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L220 _public prototype_ `FWaveFunctionCollapseTile() = default;`
- L222 _public function_ `FWaveFunctionCollapseTile(const TArray<FWaveFunctionCollapseOption>& Options, float Entropy)`
- L229 _public function_ `FWaveFunctionCollapseTile(const FWaveFunctionCollapseOption& Option, float Entropy)` — constructor with only one option

#### struct `FWaveFunctionCollapseQueueElement`  
`struct FWaveFunctionCollapseQueueElement`  
_L240-257_
- reflection: `USTRUCT(BlueprintType)`
- desc: A helper struct used for queuing during Observation and Propagation phases
- L245 _public member_ `int32 CenterObjectIndex;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L248 _public member_ `EWaveFunctionCollapseAdjacency Adjacency = EWaveFunctionCollapseAdjacency::Front;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveFunctionCollapse")`
- L250 _public prototype_ `FWaveFunctionCollapseQueueElement() = default;`
- L252 _public function_ `FWaveFunctionCollapseQueueElement(int32 CenterObjectIndexInput, EWaveFunctionCollapseAdjacency AdjacencyInput)`

#### Free symbols / members of external scopes

- L55 _function_ `friend uint32 GetTypeHash(FWaveFunctionCollapseOption Output)`

### `Plugins/Experimental/WaveFunctionCollapse/Source/WaveFunctionCollapse/Public/WaveFunctionCollapseSubsystem.h` (Public)


#### class `UWaveFunctionCollapseSubsystem`  
`class UWaveFunctionCollapseSubsystem : public UEditorSubsystem`  
_L13-175_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L20 _public member_ `TObjectPtr<UWaveFunctionCollapseModel> WFCModel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L23 _public member_ `FIntVector Resolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L26 _public member_ `FVector OriginLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L29 _public member_ `FRotator Orientation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L32 _public member_ `bool bUseEmptyBorder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L35 _public member_ `TMap<FIntVector, FWaveFunctionCollapseOption> StarterOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WFCSettings")`
- L43 _public prototype_ `AActor* Collapse(int32 TryCount = 1, int32 RandomSeed = 0);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Solve a grid using a WFC model.  If successful, spawn an actor. @param TryCount Amount of times to attempt a successful solve @param RandomSeed Seed for deterministic results.  When this value is 0 the seed will be generated. Seed value will be logged during the solve.
- L52 _public prototype_ `void InitializeWFC(TArray<FWaveFunctionCollapseTile>& Tiles, TArray<int32>& RemainingTiles);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Initialize WFC process which sets up Tiles and RemainingTiles arrays Pre-populates Tiles with StarterOptions, BorderOptions and InitialTiles @param Tiles Array of tiles (by ref) @param RemainingTiles Array of remaining tile indices.  Semi-sorted: Min Entropy tiles at the front, the rest remains unsorted (by ref)
- L63 _public prototype_ `bool Observe(TArray<FWaveFunctionCollapseTile>& Tiles, TArray<int32>& RemainingTiles, TMap<int32, FWaveFunctionCollapseQueueElement>& ObservationQueue, int32 RandomSeed);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Observation phase: This process randomly selects one tile from minimum entropy tiles then randomly selects a valid option for that tile @param Tiles Array of tiles (by ref) @param RemainingTiles Array of remaining tile indices.  Semi-sorted: Min Entropy tiles at the front, the rest remains unsorted (by ref) @param ObservationQueue Array to store tiles that need to be checked whether remaining options are affected during propagation phase (by ref)
- L80 _public prototype_ `bool Propagate(TArray<FWaveFunctionCollapseTile>& Tiles, TArray<int32>& RemainingTiles, TMap<int32, FWaveFunctionCollapseQueueElement>& ObservationQueue, int32& PropagationCount);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Propagation phase: This process checks if the selection made during the observation is valid by checking constraint validity with neighboring tiles. Neighboring tiles may reduce their remaining options to include only valid options. If the remaining options of a tile were modified, the neighboring tiles of the modified tile will be added to a queue. During this process, if any contradiction (a tile with zero remaining options) is encountered, the current solve will fail. @param Tiles Array of tiles (by ref) @param RemainingTiles Array of remaining tile indices.  Semi-sorted: Min Entropy tiles at the front, the rest remains unsorted (by ref) @param ObservationQueue Array to store tiles that need to be checked whether remaining options are affected (by ref) @param PropagationCount Counter for propagation passes
- L92 _public prototype_ `bool ObservationPropagation(TArray<FWaveFunctionCollapseTile>& Tiles, TArray<int32>& RemainingTiles, TMap<int32, FWaveFunctionCollapseQueueElement>& ObservationQueue, int32 RandomSeed);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Recursive Observation and Propagation cycle @param Tiles Array of tiles (by ref) @param RemainingTiles Array of remaining tile indices (by ref) @param ObservationQueue Array to store tiles that need to be checked whether remaining options are affected (by ref)
- L106 _public prototype_ `void DeriveGridFromTransformBounds(const TArray<FTransform>& Transforms);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Derive grid from the bounds of an array of transforms Assumptions: -Transforms can only represent a single grid -Sets empty starter option if there is a valid grid position with no transform -Orientation is determined by the yaw of the first transform in the array @param Transforms Array of transforms (by ref)
- L117 _public prototype_ `void DeriveGridFromTransforms(const TArray<FTransform>& Transforms);` — `UFUNCTION(BlueprintCallable, Category = "WFCFunctions")` — Derive grid from an array of transforms Assumptions: -Every transform represents the center point of a tile position -Sets empty starter option if there is a valid grid position with no transform -Orientation is determined by the yaw of the first transform in the array @param Transforms Array of transforms (by ref)
- L125 _private prototype_ `bool BuildInitialTile(FWaveFunctionCollapseTile& InitialTile);` — Builds the Initial Tile which is a tile containing all possible options @param InitialTile The Initial Tile (by ref)
- L132 _private prototype_ `TArray<FWaveFunctionCollapseOption> GetInnerBorderOptions(FIntVector Position, const TArray<FWaveFunctionCollapseOption>& InitialOptions);` — Get valid options for a border tile @param Position Position of border tile @param TmpInitialOptions Initial options which should contain all possible options
- L140 _private prototype_ `void GatherInnerBorderOptionsToRemove(EWaveFunctionCollapseAdjacency Adjacency, const TArray<FWaveFunctionCollapseOption>& InitialOptions, TArray<FWaveFunctionCollapseOption>& OutBorderOptionsToRemove);` — Used in GetBorderOptions to gather invalid options for border tiles that should be removed from the InitialOptions set @param Adjacency Direction from Exterior Border to Inner Border @param InInitialOptions This should be the InitialOptions @param OutBorderOptionsToRemove Array containing gathered options to remove
- L146 _private prototype_ `bool IsPositionInnerBorder(FIntVector Position);` — Checks if a position is an inner border @param Position
- L154 _private prototype_ `void AddAdjacentIndicesToQueue(int32 CenterIndex, const TArray<int32>& RemainingTiles, TMap<int32,FWaveFunctionCollapseQueueElement>& OutQueue);` — Used in Observe and Propagate to add adjacent indices to a queue @param CenterIndex Index of the center object @param RemainingTiles Used to check if index still remains in RemainingTiles @param OutQueue Queue to add indices to
- L162 _private prototype_ `UActorComponent* AddNamedInstanceComponent(AActor* Actor, TSubclassOf<UActorComponent> ComponentClass, FName ComponentName);` — Add an Instance Component with a given name @param Actor Actor to add component to @param ComponentClass @param ComponentName
- L168 _private prototype_ `AActor* SpawnActorFromTiles(const TArray<FWaveFunctionCollapseTile>& Tiles);` — Spawn an actor given an array of successfully solved tiles @param Tiles Successfully solved array of tiles
- L174 _private prototype_ `bool AreAllTilesNonSpawnable(const TArray<FWaveFunctionCollapseTile>& Tiles);` — Returns true if no remaining options in given tiles are an empty/void option or included in the SpawnExclusion list @param Tiles Successfully solved array of tiles

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWFC, Log, All);`
