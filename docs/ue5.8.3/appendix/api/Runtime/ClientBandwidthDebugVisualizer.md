# Runtime / ClientBandwidthDebugVisualizer

- module root: `Source/Runtime/Online/Experimental/ClientBandwidthDebugVisualizer`
- headers: 1; symbols: 31
- symbol kinds: class=1, function=3, macro=1, member=14, namespace=2, prototype=9, struct=1
- PrivateDependencyModuleNames: BandwidthDebugDelegates, CoreUObject, Engine, EngineSettings
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/Experimental/ClientBandwidthDebugVisualizer/Public/ClientBandwidthDebugVisualizer.h` (Public)


#### struct `UE::ClientBandwidthDebug::FDebugTextInformation`  
`struct FDebugTextInformation`  
_L24-48_
- L26 _public function_ `FDebugTextInformation()`
- L28 _public function_ `FDebugTextInformation(const FDebugTextInformation& Copy) :Scale(Copy.Scale), TextColor(Copy.TextColor), bIsSubHeader(Copy.bIsSubHeader)`
- L36 _public function_ `bool operator==(const FDebugTextInformation& Compare) const`
- L44 _public member_ `FString Text;`
- L45 _public member_ `float Scale = 1.0f;`
- L46 _public member_ `FColor TextColor;`
- L47 _public member_ `bool bIsSubHeader = false;`

#### class `UClientBandwidthDebugVisualizer`  
`class UClientBandwidthDebugVisualizer : public UObject`  
_L52-97_
- reflection: `UCLASS(MinimalApi)`
- inherits: `UObject`
- L58 _public prototype_ `static UClientBandwidthDebugVisualizer& Get();` — --- Static Functions ---
- L61 _public prototype_ `void Initialize();` — --- Lifecycle (called by module) ---
- L62 _public prototype_ `void Shutdown();`
- L65 _public prototype_ `void DisplayDebugInformation(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);` — Displays Categorized Information to Debug HUD
- L68 _public prototype_ `void AddDebugMessageToVisualizer(FStringView CategoryName, FStringView TextToPrint, float Scale, FColor Color, bool bIsSubHeader);` — Adds the supplied message to the Debug Text that is displayed, if category name does not exist it will be added
- L71 _public prototype_ `void CycleToNextCategory(const FString& JumpCategory);` — Cycles to the next category/page of text to display
- L75 _private prototype_ `void ClientPlayerControllerCollection(bool bHasBegun);` — Function to set trackable player controller and HUD bindings
- L78 _private prototype_ `void ClearCategory(const FStringView& CategoryName);` — Clears Category for debug entries
- L81 _private member_ `static TStrongObjectPtr<UClientBandwidthDebugVisualizer> Instance;` — Singleton instance pointer
- L83 _private member_ `TMap<FString, TArray<UE::ClientBandwidthDebug::FDebugTextInformation>> DebugPrintText;`
- L85 _private member_ `FStringView CurrentCategory;`
- L87 _private member_ `TWeakObjectPtr<APlayerController> ClientPlayerController;`
- L89 _private member_ `FDelegateHandle OnActorSpawnedHandle;`
- L91 _private member_ `TWeakObjectPtr<UWorld> CurrentWorld;`
- L93 _private member_ `FDelegateHandle AddDebugTextHandle;`
- L94 _private member_ `FDelegateHandle ClearDebugTextHandle;`
- L95 _private member_ `FDelegateHandle WorldActorInitialization;`
- L96 _private member_ `FDelegateHandle ConsoleAutocomplete;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CLIENTBANDWIDTHDEBUGVISUALIZER_API`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBandwidthDebugger, Log, All);`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ClientBandwidthDebug` (scope `UE`)
