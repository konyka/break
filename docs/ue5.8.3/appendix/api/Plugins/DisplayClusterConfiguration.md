# Plugins / DisplayClusterConfiguration

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration`
- headers: 36; symbols: 1393
- symbol kinds: class=25, delegate=4, enum=28, enumerator=81, function=130, member=678, namespace=28, prototype=199, struct=161, variable=59
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Json, JsonUtilities
- PublicDependencyModuleNames: ActorLayerUtilities, CinematicCamera, MediaAssets, MediaIOCore, OpenColorIO
- PublicIncludePathModuleNames: DisplayCluster, DisplayClusterProjection, DisplayClusterShaders

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/DisplayClusterConfigurationLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterConfiguration, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterConfiguration, Log, All);` — Module-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/DisplayClusterConfigurationMgr.h` (Private)


#### class `FDisplayClusterConfigurationMgr`  
`class FDisplayClusterConfigurationMgr`  
_L14-30_
- desc: Display Cluster configuration manager
- L17 _protected prototype_ `FDisplayClusterConfigurationMgr() = default;`
- L18 _protected prototype_ `~FDisplayClusterConfigurationMgr() = default;`
- L22 _public prototype_ `static FDisplayClusterConfigurationMgr& Get();` — Singletone getter
- L25 _public prototype_ `EDisplayClusterConfigurationVersion GetConfigVersion(const FString& FilePath);`
- L26 _public prototype_ `UDisplayClusterConfigurationData* LoadConfig(const FString& FilePath, UObject* Owner = nullptr);`
- L27 _public prototype_ `bool SaveConfig(const UDisplayClusterConfigurationData* Config, const FString& FilePath);`
- L28 _public prototype_ `bool ConfigAsString(const UDisplayClusterConfigurationData* Config, FString& OutString);`
- L29 _public prototype_ `UDisplayClusterConfigurationData* CreateDefaultStandaloneConfigData();`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/DisplayClusterConfigurationModule.h` (Private)


#### class `FDisplayClusterConfigurationModule`  
`class FDisplayClusterConfigurationModule : public IDisplayClusterConfiguration`  
_L13-31_
- inherits: `IDisplayClusterConfiguration`
- desc: Display Cluster configuration module
- L21 _public prototype_ `virtual void SetIsSnapshotTransacting(bool bIsSnapshot) override;`
- L22 _public prototype_ `virtual bool IsTransactingSnapshot() const override;`
- L23 _public prototype_ `virtual EDisplayClusterConfigurationVersion GetConfigVersion(const FString& FilePath) override;`
- L24 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadConfig(const FString& FilePath, UObject* Owner = nullptr) override;`
- L25 _public prototype_ `virtual bool SaveConfig(const UDisplayClusterConfigurationData* Config, const FString& FilePath) override;`
- L26 _public prototype_ `virtual bool ConfigAsString(const UDisplayClusterConfigurationData* Config, FString& OutString) const override;`
- L30 _private member_ `bool bIsSnapshot = false;` — Snapshot state

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/DisplayClusterConfigurationUtils.h` (Private)


#### class `FDisplayClusterConfigurationUtils`  
`class FDisplayClusterConfigurationUtils`  
_L14-37_
- desc: Utility functions
- L17 _private prototype_ `FDisplayClusterConfigurationUtils() = default;`
- L21 _public prototype_ `static bool IsSerializingTemplate(const FArchive& Ar);` — Returns true if we're serializing a template or archetype. False otherwise.
- L29 _public prototype_ `static void UpdateToLatest(UDisplayClusterConfigurationData* Config);` — Updates the config data container to the latest version. It's called internally after loading the configuration from an external source. @param Config - Configuration data container
- L36 _public prototype_ `static void RedirectSimpleToMeshPolicy(UDisplayClusterConfigurationViewport* ViewportCfg);` — Migrates 'simple' to 'mesh' projection policy @param ViewportCfg - Viewport configuration to modify

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/IDisplayClusterConfigurationDataParser.h` (Private)


#### class `IDisplayClusterConfigurationDataParser`  
`class IDisplayClusterConfigurationDataParser`  
_L10-24_
- L13 _public prototype_ `virtual ~IDisplayClusterConfigurationDataParser() = default;`
- L17 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadData(const FString& FilePath, UObject* Owner = nullptr) = 0;` — Load data from a specified file
- L20 _public prototype_ `virtual bool SaveData(const UDisplayClusterConfigurationData* ConfigData, const FString& FilePath) = 0;` — Save data to a specified file
- L23 _public prototype_ `virtual bool AsString(const UDisplayClusterConfigurationData* ConfigData, FString& OutString) = 0;` — Convert configuration to string

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON426/DisplayClusterConfigurationJsonHelpers_426.h` (Private)


#### class `JSON426::DisplayClusterConfigurationJsonHelpers`  
`class DisplayClusterConfigurationJsonHelpers`  
_L15-29_
- desc: Auxiliary class with different type conversion functions
- L22 _public prototype_ `template <typename ConvertFrom> static FString ToString(const ConvertFrom& From);`
- L28 _public prototype_ `template <typename ConvertTo> static ConvertTo FromString(const FString& From);`
- L34 _function_ `template <> inline FString DisplayClusterConfigurationJsonHelpers::ToString<>(const EDisplayClusterConfigurationEyeStereoOffset& From)` — EDisplayClusterConfigurationEyeStereoOffset
- L56 _function_ `template <> inline EDisplayClusterConfigurationEyeStereoOffset DisplayClusterConfigurationJsonHelpers::FromString<>(const FString& From)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace JSON426`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON426/DisplayClusterConfigurationJsonParser_426.h` (Private)


#### class `JSON426::FDisplayClusterConfigurationJsonParser`  
`class FDisplayClusterConfigurationJsonParser : public IDisplayClusterConfigurationDataParser`  
_L17-47_
- inherits: `IDisplayClusterConfigurationDataParser`
- desc: Config parser for JSON based config files
- L21 _public prototype_ `FDisplayClusterConfigurationJsonParser() = default;`
- L22 _public prototype_ `~FDisplayClusterConfigurationJsonParser() = default;`
- L26 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadData(const FString& FilePath, UObject* Owner = nullptr) override;` — Load data from a specified file
- L29 _public prototype_ `virtual bool SaveData(const UDisplayClusterConfigurationData* ConfigData, const FString& FilePath) override;` — Save data to a specified file
- L32 _public prototype_ `virtual bool AsString(const UDisplayClusterConfigurationData* ConfigData, FString& OutString) override;` — Convert configuration to string
- L36 _protected prototype_ `UDisplayClusterConfigurationData* ConvertDataToInternalTypes();` — [import data] Fill generic data container with parsed information
- L38 _protected prototype_ `bool ConvertDataToExternalTypes(const UDisplayClusterConfigurationData* InData);` — [export data] Extract data from generic container to specific containers
- L42 _private member_ `FDisplayClusterConfigurationJsonContainer_426 JsonData;` — Intermediate temporary data (Json types)
- L44 _private member_ `FString ConfigFile;` — Source file
- L46 _private member_ `UObject* ConfigDataOwner = nullptr;` — Owner for config data UObject we'll create on success

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace JSON426`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON426/DisplayClusterConfigurationJsonTypes_426.h` (Private)


#### struct `FDisplayClusterConfigurationJsonRectangle_426`  
`struct FDisplayClusterConfigurationJsonRectangle_426`  
_L11-36_
- reflection: `USTRUCT()`
- L16 _public function_ `FDisplayClusterConfigurationJsonRectangle_426() : X(0), Y(0), W(0), H(0)`
- L20 _public function_ `FDisplayClusterConfigurationJsonRectangle_426(int32 _X, int32 _Y, int32 _W, int32 _H) : X(_X), Y(_Y), W(_W), H(_H)`
- L26 _public member_ `int32 X;` — `UPROPERTY()`
- L29 _public member_ `int32 Y;` — `UPROPERTY()`
- L32 _public member_ `int32 W;` — `UPROPERTY()`
- L35 _public member_ `int32 H;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonVector_426`  
`struct FDisplayClusterConfigurationJsonVector_426`  
_L40-77_
- reflection: `USTRUCT()`
- L45 _public function_ `FDisplayClusterConfigurationJsonVector_426() : FDisplayClusterConfigurationJsonVector_426(0.f, 0.f, 0.f)`
- L49 _public function_ `FDisplayClusterConfigurationJsonVector_426(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z)`
- L53 _public function_ `FDisplayClusterConfigurationJsonVector_426(const FVector& Vector) : FDisplayClusterConfigurationJsonVector_426(Vector.X, Vector.Y, Vector.Z)`
- L59 _public member_ `float X;` — `UPROPERTY()`
- L62 _public member_ `float Y;` — `UPROPERTY()`
- L65 _public member_ `float Z;` — `UPROPERTY()`
- L68 _public function_ `static FVector ToVector(const FDisplayClusterConfigurationJsonVector_426& Data)`
- L73 _public function_ `static FDisplayClusterConfigurationJsonVector_426 FromVector(const FVector& Vector)`

#### struct `FDisplayClusterConfigurationJsonRotator_426`  
`struct FDisplayClusterConfigurationJsonRotator_426`  
_L81-118_
- reflection: `USTRUCT()`
- L86 _public function_ `FDisplayClusterConfigurationJsonRotator_426() : FDisplayClusterConfigurationJsonRotator_426(0.f, 0.f, 0.f)`
- L90 _public function_ `FDisplayClusterConfigurationJsonRotator_426(float P, float Y, float R) : Pitch(P), Yaw(Y), Roll(R)`
- L94 _public function_ `FDisplayClusterConfigurationJsonRotator_426(const FRotator& Rotator) : FDisplayClusterConfigurationJsonRotator_426(Rotator.Pitch, Rotator.Yaw, Rotator.Roll)`
- L100 _public member_ `float Pitch;` — `UPROPERTY()`
- L103 _public member_ `float Yaw;` — `UPROPERTY()`
- L106 _public member_ `float Roll;` — `UPROPERTY()`
- L109 _public function_ `static FRotator ToRotator(const FDisplayClusterConfigurationJsonRotator_426& Data)`
- L114 _public function_ `static FDisplayClusterConfigurationJsonRotator_426 FromRotator(const FRotator& Rotator)`

#### struct `FDisplayClusterConfigurationJsonSizeInt_426`  
`struct FDisplayClusterConfigurationJsonSizeInt_426`  
_L122-152_
- reflection: `USTRUCT()`
- L127 _public function_ `FDisplayClusterConfigurationJsonSizeInt_426() : FDisplayClusterConfigurationJsonSizeInt_426(0, 0)`
- L131 _public function_ `FDisplayClusterConfigurationJsonSizeInt_426(int W, int H) : Width(W), Height(H)`
- L137 _public member_ `int Width;` — `UPROPERTY()`
- L140 _public member_ `int Height;` — `UPROPERTY()`
- L143 _public function_ `static FIntPoint ToPoint(const FDisplayClusterConfigurationJsonSizeInt_426& Data)`
- L148 _public function_ `static FDisplayClusterConfigurationJsonSizeInt_426 FromPoint(const FIntPoint& Point)`

#### struct `FDisplayClusterConfigurationJsonSizeFloat_426`  
`struct FDisplayClusterConfigurationJsonSizeFloat_426`  
_L156-190_
- reflection: `USTRUCT()`
- L161 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_426() : FDisplayClusterConfigurationJsonSizeFloat_426(0.f, 0.f)`
- L165 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_426(float W, float H) : Width(W), Height(H)`
- L169 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_426(const FVector2D& Vector) : FDisplayClusterConfigurationJsonSizeFloat_426(Vector.X, Vector.Y)`
- L175 _public member_ `float Width;` — `UPROPERTY()`
- L178 _public member_ `float Height;` — `UPROPERTY()`
- L181 _public function_ `static FVector2D ToVector(const FDisplayClusterConfigurationJsonSizeFloat_426& Data)`
- L186 _public function_ `static FDisplayClusterConfigurationJsonSizeFloat_426 FromVector(const FVector2D& Vector)`

#### struct `FDisplayClusterConfigurationJsonPolymorphicEntity_426`  
`struct FDisplayClusterConfigurationJsonPolymorphicEntity_426`  
_L194-204_
- reflection: `USTRUCT()`
- L200 _public member_ `FString Type;` — `UPROPERTY()`
- L203 _public member_ `TMap<FString, FString> Parameters;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponent_426`  
`struct FDisplayClusterConfigurationJsonSceneComponent_426`  
_L208-211_
- reflection: `USTRUCT()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentXform_426`  
`struct FDisplayClusterConfigurationJsonSceneComponentXform_426 : public FDisplayClusterConfigurationJsonSceneComponent_426`  
_L214-239_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponent_426`
- L220 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_426() : FDisplayClusterConfigurationJsonSceneComponentXform_426(FString(), FVector::ZeroVector, FRotator::ZeroRotator)`
- L224 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_426(const FString& InParent, const FVector& InLocation, const FRotator& InRotation) : Parent(InParent) , Location(InLocation) , Rotation(InRotation)`
- L232 _public member_ `FString Parent;` — `UPROPERTY()`
- L235 _public member_ `FDisplayClusterConfigurationJsonVector_426 Location;` — `UPROPERTY()`
- L238 _public member_ `FDisplayClusterConfigurationJsonRotator_426 Rotation;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentCamera_426`  
`struct FDisplayClusterConfigurationJsonSceneComponentCamera_426 : public FDisplayClusterConfigurationJsonSceneComponentXform_426`  
_L242-268_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_426`
- L248 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_426() : FDisplayClusterConfigurationJsonSceneComponentCamera_426(FString(), FVector::ZeroVector, FRotator::ZeroRotator, 0.064f, false, DisplayClusterConfigurationStrings::config::scene::camera::CameraStereoOffsetNone)`
- L252 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_426(const FString& InParent, const FVector& InLocation, const FRotator& InRotation, float InInterpupillaryDistance, bool bInSwapEyes, FString InStereoOffset) : FDisplayClusterConfigurationJsonSceneComponentXform_426(InParent, InLocation, InRotation) , InterpupillaryDistance(InInterpupillaryDistance) , SwapEyes(bInSwapEyes) , StereoOffset(InStereoOffset)`
- L261 _public member_ `float InterpupillaryDistance;` — `UPROPERTY()`
- L264 _public member_ `bool SwapEyes;` — `UPROPERTY()`
- L267 _public member_ `FString StereoOffset;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentScreen_426`  
`struct FDisplayClusterConfigurationJsonSceneComponentScreen_426 : public FDisplayClusterConfigurationJsonSceneComponentXform_426`  
_L271-289_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_426`
- L277 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_426() : FDisplayClusterConfigurationJsonSceneComponentScreen_426(FString(), FVector::ZeroVector, FRotator::ZeroRotator, FVector2D::ZeroVector)`
- L281 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_426(const FString& InParent, const FVector& InLocation, const FRotator& InRotation, const FVector2D& InSize) : FDisplayClusterConfigurationJsonSceneComponentXform_426(InParent, InLocation, InRotation) , Size(InSize)`
- L288 _public member_ `FDisplayClusterConfigurationJsonSizeFloat_426 Size;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonScene_426`  
`struct FDisplayClusterConfigurationJsonScene_426`  
_L292-305_
- reflection: `USTRUCT()`
- L298 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentXform_426> Xforms;` — `UPROPERTY()`
- L301 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentCamera_426> Cameras;` — `UPROPERTY()`
- L304 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentScreen_426> Screens;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonPrimaryNode_426`  
`struct FDisplayClusterConfigurationJsonPrimaryNode_426`  
_L308-318_
- reflection: `USTRUCT()`
- L314 _public member_ `FString Id;` — `UPROPERTY()`
- L317 _public member_ `TMap<FString, uint16> Ports;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterSyncPolicy_426`  
`struct FDisplayClusterConfigurationJsonClusterSyncPolicy_426 : public FDisplayClusterConfigurationJsonPolymorphicEntity_426`  
_L321-325_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_426`

#### struct `FDisplayClusterConfigurationJsonClusterSync_426`  
`struct FDisplayClusterConfigurationJsonClusterSync_426`  
_L328-338_
- reflection: `USTRUCT()`
- L334 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_426 RenderSyncPolicy;` — `UPROPERTY()`
- L337 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_426 InputSyncPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonPostprocess_426`  
`struct FDisplayClusterConfigurationJsonPostprocess_426 : public FDisplayClusterConfigurationJsonPolymorphicEntity_426`  
_L341-345_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_426`

#### struct `FDisplayClusterConfigurationJsonProjectionPolicy_426`  
`struct FDisplayClusterConfigurationJsonProjectionPolicy_426 : public FDisplayClusterConfigurationJsonPolymorphicEntity_426`  
_L348-352_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_426`

#### struct `FDisplayClusterConfigurationJsonViewport_426`  
`struct FDisplayClusterConfigurationJsonViewport_426`  
_L355-380_
- reflection: `USTRUCT()`
- L361 _public member_ `FString Camera;` — `UPROPERTY()`
- L364 _public member_ `float BufferRatio = 1.0f;` — `UPROPERTY()`
- L367 _public member_ `int32 GPUIndex = 0;` — `UPROPERTY()`
- L370 _public member_ `bool AllowCrossGPUTransfer = false;` — `UPROPERTY()`
- L373 _public member_ `bool IsShared = false;` — `UPROPERTY()`
- L376 _public member_ `FDisplayClusterConfigurationJsonRectangle_426 Region;` — `UPROPERTY()`
- L379 _public member_ `FDisplayClusterConfigurationJsonProjectionPolicy_426 ProjectionPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterNode_426`  
`struct FDisplayClusterConfigurationJsonClusterNode_426`  
_L383-405_
- reflection: `USTRUCT()`
- L389 _public member_ `FString Host;` — `UPROPERTY()`
- L392 _public member_ `bool Sound = true;` — `UPROPERTY()`
- L395 _public member_ `bool FullScreen = false;` — `UPROPERTY()`
- L398 _public member_ `FDisplayClusterConfigurationJsonRectangle_426 Window;` — `UPROPERTY()`
- L401 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonPostprocess_426> Postprocess;` — `UPROPERTY()`
- L404 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonViewport_426> Viewports;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonCluster_426`  
`struct FDisplayClusterConfigurationJsonCluster_426`  
_L408-424_
- reflection: `USTRUCT()`
- L414 _public member_ `FDisplayClusterConfigurationJsonPrimaryNode_426 MasterNode;` — `UPROPERTY()`
- L417 _public member_ `FDisplayClusterConfigurationJsonClusterSync_426 Sync;` — `UPROPERTY()`
- L420 _public member_ `TMap<FString, FString> Network;` — `UPROPERTY()`
- L423 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonClusterNode_426> Nodes;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonDiagnostics_426`  
`struct FDisplayClusterConfigurationJsonDiagnostics_426`  
_L427-440_
- reflection: `USTRUCT()`
- L433 _public member_ `bool SimulateLag = false;` — `UPROPERTY()`
- L436 _public member_ `float MinLagTime = 0.01f;` — `UPROPERTY()`
- L439 _public member_ `float MaxLagTime = 0.3f;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonNdisplay_426`  
`struct FDisplayClusterConfigurationJsonNdisplay_426`  
_L445-470_
- reflection: `USTRUCT()`
- desc: "nDisplay" category structure
- L451 _public member_ `FString Description;` — `UPROPERTY()`
- L454 _public member_ `FString Version;` — `UPROPERTY()`
- L457 _public member_ `FString AssetPath;` — `UPROPERTY()`
- L460 _public member_ `FDisplayClusterConfigurationJsonScene_426 Scene;` — `UPROPERTY()`
- L463 _public member_ `FDisplayClusterConfigurationJsonCluster_426 Cluster;` — `UPROPERTY()`
- L466 _public member_ `TMap<FString, FString> CustomParameters;` — `UPROPERTY()`
- L469 _public member_ `FDisplayClusterConfigurationJsonDiagnostics_426 Diagnostics;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonContainer_426`  
`struct FDisplayClusterConfigurationJsonContainer_426`  
_L474-481_
- reflection: `USTRUCT()`
- desc: The main nDisplay configuration structure. It's supposed to extract nDisplay related data from a collecting JSON file.
- L480 _public member_ `FDisplayClusterConfigurationJsonNdisplay_426 nDisplay;` — `UPROPERTY()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON427/DisplayClusterConfigurationJsonHelpers_427.h` (Private)


#### class `JSON427::DisplayClusterConfigurationJsonHelpers`  
`class DisplayClusterConfigurationJsonHelpers`  
_L32-46_
- desc: Auxiliary class with different type conversion functions
- L39 _public prototype_ `template <typename ConvertFrom> static FString ToString(const ConvertFrom& From);`
- L45 _public prototype_ `template <typename ConvertTo> static ConvertTo FromString(const FString& From);`
- L51 _function_ `template <> inline FString DisplayClusterConfigurationJsonHelpers::ToString<>(const EDisplayClusterConfigurationEyeStereoOffset& From)` — EDisplayClusterConfigurationEyeStereoOffset
- L73 _function_ `template <> inline EDisplayClusterConfigurationEyeStereoOffset DisplayClusterConfigurationJsonHelpers::FromString<>(const FString& From)`
- L95 _function_ `template <> inline FString DisplayClusterConfigurationJsonHelpers::ToString<>(const EDisplayClusterConfigurationViewportOverscanMode& InOverscanMode)` — EDisplayClusterConfigurationViewportOverscanMode
- L114 _function_ `template <> inline EDisplayClusterConfigurationViewportOverscanMode DisplayClusterConfigurationJsonHelpers::FromString<>(const FString& InOverscanModeString)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace JSON427`
- L13 _namespace_ `namespace config` (scope `JSON427`)
- L15 _namespace_ `namespace node` (scope `JSON427::config`)
- L17 _namespace_ `namespace viewport` (scope `JSON427::config::node`)
- L19 _namespace_ `namespace overscan` (scope `JSON427::config::node::viewport`)
- L21 _variable_ `static constexpr const TCHAR* OverscanNone = TEXT("non` (scope `JSON427::config::node::viewport::overscan`)
- L22 _variable_ `static constexpr const TCHAR* OverscanPixels = TEXT("pix` (scope `JSON427::config::node::viewport::overscan`)
- L23 _variable_ `static constexpr const TCHAR* OverscanPercent = TEXT("per` (scope `JSON427::config::node::viewport::overscan`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON427/DisplayClusterConfigurationJsonParser_427.h` (Private)


#### class `JSON427::FDisplayClusterConfigurationJsonParser`  
`class FDisplayClusterConfigurationJsonParser : public IDisplayClusterConfigurationDataParser`  
_L17-47_
- inherits: `IDisplayClusterConfigurationDataParser`
- desc: Config parser for JSON based config files
- L21 _public prototype_ `FDisplayClusterConfigurationJsonParser() = default;`
- L22 _public prototype_ `~FDisplayClusterConfigurationJsonParser() = default;`
- L26 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadData(const FString& FilePath, UObject* Owner = nullptr) override;` — Load data from a specified file
- L29 _public prototype_ `virtual bool SaveData(const UDisplayClusterConfigurationData* ConfigData, const FString& FilePath) override;` — Save data to a specified file
- L32 _public prototype_ `virtual bool AsString(const UDisplayClusterConfigurationData* ConfigData, FString& OutString) override;` — Convert configuration to string
- L36 _protected prototype_ `UDisplayClusterConfigurationData* ConvertDataToInternalTypes();` — [import data] Fill generic data container with parsed information
- L38 _protected prototype_ `bool ConvertDataToExternalTypes(const UDisplayClusterConfigurationData* InData);` — [export data] Extract data from generic container to specific containers
- L42 _private member_ `FDisplayClusterConfigurationJsonContainer_427 JsonData;` — Intermediate temporary data (Json types)
- L44 _private member_ `FString ConfigFile;` — Source file
- L46 _private member_ `UObject* ConfigDataOwner = nullptr;` — Owner for config data UObject we'll create on success

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace JSON427`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON427/DisplayClusterConfigurationJsonTypes_427.h` (Private)


#### struct `FDisplayClusterConfigurationJsonRectangle_427`  
`struct FDisplayClusterConfigurationJsonRectangle_427`  
_L11-36_
- reflection: `USTRUCT()`
- L16 _public function_ `FDisplayClusterConfigurationJsonRectangle_427() : X(0), Y(0), W(0), H(0)`
- L20 _public function_ `FDisplayClusterConfigurationJsonRectangle_427(int32 _X, int32 _Y, int32 _W, int32 _H) : X(_X), Y(_Y), W(_W), H(_H)`
- L26 _public member_ `int32 X;` — `UPROPERTY()`
- L29 _public member_ `int32 Y;` — `UPROPERTY()`
- L32 _public member_ `int32 W;` — `UPROPERTY()`
- L35 _public member_ `int32 H;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonVector_427`  
`struct FDisplayClusterConfigurationJsonVector_427`  
_L40-77_
- reflection: `USTRUCT()`
- L45 _public function_ `FDisplayClusterConfigurationJsonVector_427() : FDisplayClusterConfigurationJsonVector_427(0.f, 0.f, 0.f)`
- L49 _public function_ `FDisplayClusterConfigurationJsonVector_427(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z)`
- L53 _public function_ `FDisplayClusterConfigurationJsonVector_427(const FVector& Vector) : FDisplayClusterConfigurationJsonVector_427(Vector.X, Vector.Y, Vector.Z)`
- L59 _public member_ `float X;` — `UPROPERTY()`
- L62 _public member_ `float Y;` — `UPROPERTY()`
- L65 _public member_ `float Z;` — `UPROPERTY()`
- L68 _public function_ `static FVector ToVector(const FDisplayClusterConfigurationJsonVector_427& Data)`
- L73 _public function_ `static FDisplayClusterConfigurationJsonVector_427 FromVector(const FVector& Vector)`

#### struct `FDisplayClusterConfigurationJsonRotator_427`  
`struct FDisplayClusterConfigurationJsonRotator_427`  
_L81-118_
- reflection: `USTRUCT()`
- L86 _public function_ `FDisplayClusterConfigurationJsonRotator_427() : FDisplayClusterConfigurationJsonRotator_427(0.f, 0.f, 0.f)`
- L90 _public function_ `FDisplayClusterConfigurationJsonRotator_427(float P, float Y, float R) : Pitch(P), Yaw(Y), Roll(R)`
- L94 _public function_ `FDisplayClusterConfigurationJsonRotator_427(const FRotator& Rotator) : FDisplayClusterConfigurationJsonRotator_427(Rotator.Pitch, Rotator.Yaw, Rotator.Roll)`
- L100 _public member_ `float Pitch;` — `UPROPERTY()`
- L103 _public member_ `float Yaw;` — `UPROPERTY()`
- L106 _public member_ `float Roll;` — `UPROPERTY()`
- L109 _public function_ `static FRotator ToRotator(const FDisplayClusterConfigurationJsonRotator_427& Data)`
- L114 _public function_ `static FDisplayClusterConfigurationJsonRotator_427 FromRotator(const FRotator& Rotator)`

#### struct `FDisplayClusterConfigurationJsonSizeInt_427`  
`struct FDisplayClusterConfigurationJsonSizeInt_427`  
_L122-152_
- reflection: `USTRUCT()`
- L127 _public function_ `FDisplayClusterConfigurationJsonSizeInt_427() : FDisplayClusterConfigurationJsonSizeInt_427(0, 0)`
- L131 _public function_ `FDisplayClusterConfigurationJsonSizeInt_427(int W, int H) : Width(W), Height(H)`
- L137 _public member_ `int Width;` — `UPROPERTY()`
- L140 _public member_ `int Height;` — `UPROPERTY()`
- L143 _public function_ `static FIntPoint ToPoint(const FDisplayClusterConfigurationJsonSizeInt_427& Data)`
- L148 _public function_ `static FDisplayClusterConfigurationJsonSizeInt_427 FromPoint(const FIntPoint& Point)`

#### struct `FDisplayClusterConfigurationJsonSizeFloat_427`  
`struct FDisplayClusterConfigurationJsonSizeFloat_427`  
_L156-190_
- reflection: `USTRUCT()`
- L161 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_427() : FDisplayClusterConfigurationJsonSizeFloat_427(0.f, 0.f)`
- L165 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_427(float W, float H) : Width(W), Height(H)`
- L169 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_427(const FVector2D& Vector) : FDisplayClusterConfigurationJsonSizeFloat_427(Vector.X, Vector.Y)`
- L175 _public member_ `float Width;` — `UPROPERTY()`
- L178 _public member_ `float Height;` — `UPROPERTY()`
- L181 _public function_ `static FVector2D ToVector(const FDisplayClusterConfigurationJsonSizeFloat_427& Data)`
- L186 _public function_ `static FDisplayClusterConfigurationJsonSizeFloat_427 FromVector(const FVector2D& Vector)`

#### struct `FDisplayClusterConfigurationJsonPolymorphicEntity_427`  
`struct FDisplayClusterConfigurationJsonPolymorphicEntity_427`  
_L194-204_
- reflection: `USTRUCT()`
- L200 _public member_ `FString Type;` — `UPROPERTY()`
- L203 _public member_ `TMap<FString, FString> Parameters;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonMisc_427`  
`struct FDisplayClusterConfigurationJsonMisc_427`  
_L208-224_
- reflection: `USTRUCT()`
- L213 _public function_ `FDisplayClusterConfigurationJsonMisc_427() : bFollowLocalPlayerCamera(false) , bExitOnEsc(true)`
- L220 _public member_ `bool bFollowLocalPlayerCamera;` — `UPROPERTY()`
- L223 _public member_ `bool bExitOnEsc;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponent_427`  
`struct FDisplayClusterConfigurationJsonSceneComponent_427`  
_L228-231_
- reflection: `USTRUCT()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentXform_427`  
`struct FDisplayClusterConfigurationJsonSceneComponentXform_427 : public FDisplayClusterConfigurationJsonSceneComponent_427`  
_L235-260_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponent_427`
- L241 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_427() : FDisplayClusterConfigurationJsonSceneComponentXform_427(FString(), FVector::ZeroVector, FRotator::ZeroRotator)`
- L245 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_427(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation) : ParentId(InParentId) , Location(InLocation) , Rotation(InRotation)`
- L253 _public member_ `FString ParentId;` — `UPROPERTY()`
- L256 _public member_ `FDisplayClusterConfigurationJsonVector_427 Location;` — `UPROPERTY()`
- L259 _public member_ `FDisplayClusterConfigurationJsonRotator_427 Rotation;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentCamera_427`  
`struct FDisplayClusterConfigurationJsonSceneComponentCamera_427 : public FDisplayClusterConfigurationJsonSceneComponentXform_427`  
_L264-290_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_427`
- L270 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_427() : FDisplayClusterConfigurationJsonSceneComponentCamera_427(FString(), FVector::ZeroVector, FRotator::ZeroRotator, 6.4f, false, DisplayClusterConfigurationStrings::config::scene::camera::CameraStereoOffsetNone)`
- L274 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_427(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, float InInterpupillaryDistance, bool bInSwapEyes, const FString& InStereoOffset) : FDisplayClusterConfigurationJsonSceneComponentXform_427(InParentId, InLocation, InRotation) , InterpupillaryDistance(InInterpupillaryDistance) , SwapEyes(bInSwapEyes) , StereoOffset(InStereoOffset)`
- L283 _public member_ `float InterpupillaryDistance;` — `UPROPERTY()`
- L286 _public member_ `bool SwapEyes;` — `UPROPERTY()`
- L289 _public member_ `FString StereoOffset;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentScreen_427`  
`struct FDisplayClusterConfigurationJsonSceneComponentScreen_427 : public FDisplayClusterConfigurationJsonSceneComponentXform_427`  
_L294-312_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_427`
- L300 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_427() : FDisplayClusterConfigurationJsonSceneComponentScreen_427(FString(), FVector::ZeroVector, FRotator::ZeroRotator, FVector2D(1.f, 1.f))`
- L304 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_427(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, const FVector2D& InSize) : FDisplayClusterConfigurationJsonSceneComponentXform_427(InParentId, InLocation, InRotation) , Size(InSize)`
- L311 _public member_ `FDisplayClusterConfigurationJsonSizeFloat_427 Size;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonScene_427`  
`struct FDisplayClusterConfigurationJsonScene_427`  
_L316-329_
- reflection: `USTRUCT()`
- L322 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentXform_427> Xforms;` — `UPROPERTY()`
- L325 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentCamera_427> Cameras;` — `UPROPERTY()`
- L328 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentScreen_427> Screens;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonPrimaryNode_427`  
`struct FDisplayClusterConfigurationJsonPrimaryNode_427`  
_L333-343_
- reflection: `USTRUCT()`
- L339 _public member_ `FString Id;` — `UPROPERTY()`
- L342 _public member_ `TMap<FString, uint16> Ports;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterSyncPolicy_427`  
`struct FDisplayClusterConfigurationJsonClusterSyncPolicy_427 : public FDisplayClusterConfigurationJsonPolymorphicEntity_427`  
_L346-350_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_427`

#### struct `FDisplayClusterConfigurationJsonClusterSync_427`  
`struct FDisplayClusterConfigurationJsonClusterSync_427`  
_L353-363_
- reflection: `USTRUCT()`
- L359 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_427 RenderSyncPolicy;` — `UPROPERTY()`
- L362 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_427 InputSyncPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonPostprocess_427`  
`struct FDisplayClusterConfigurationJsonPostprocess_427 : public FDisplayClusterConfigurationJsonPolymorphicEntity_427`  
_L366-370_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_427`

#### struct `FDisplayClusterConfigurationJsonProjectionPolicy_427`  
`struct FDisplayClusterConfigurationJsonProjectionPolicy_427 : public FDisplayClusterConfigurationJsonPolymorphicEntity_427`  
_L373-377_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_427`

#### struct `FDisplayClusterConfigurationJsonOverscan_427`  
`struct FDisplayClusterConfigurationJsonOverscan_427`  
_L380-405_
- reflection: `USTRUCT()`
- L386 _public member_ `bool bEnabled = false;` — `UPROPERTY()`
- L389 _public member_ `FString Mode = "";` — `UPROPERTY()`
- L392 _public member_ `int32 Left = 0;` — `UPROPERTY()`
- L395 _public member_ `int32 Right = 0;` — `UPROPERTY()`
- L398 _public member_ `int32 Top = 0;` — `UPROPERTY()`
- L401 _public member_ `int32 Bottom = 0;` — `UPROPERTY()`
- L404 _public member_ `bool Oversize = 0;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonViewport_427`  
`struct FDisplayClusterConfigurationJsonViewport_427`  
_L408-436_
- reflection: `USTRUCT()`
- L414 _public member_ `FString Camera;` — `UPROPERTY()`
- L417 _public member_ `float BufferRatio = 1.0f;` — `UPROPERTY()`
- L420 _public member_ `int32 GPUIndex = 0;` — `UPROPERTY()`
- L423 _public member_ `bool AllowCrossGPUTransfer = false;` — `UPROPERTY()`
- L426 _public member_ `bool IsShared = false;` — `UPROPERTY()`
- L429 _public member_ `FDisplayClusterConfigurationJsonOverscan_427 Overscan;` — `UPROPERTY()`
- L432 _public member_ `FDisplayClusterConfigurationJsonRectangle_427 Region;` — `UPROPERTY()`
- L435 _public member_ `FDisplayClusterConfigurationJsonProjectionPolicy_427 ProjectionPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationFramePostProcess_OutputRemap_427`  
`struct FDisplayClusterConfigurationFramePostProcess_OutputRemap_427`  
_L439-455_
- reflection: `USTRUCT()`
- L445 _public member_ `bool bEnable = false;` — `UPROPERTY()`
- L448 _public member_ `FString DataSource;` — `UPROPERTY()`
- L451 _public member_ `FString StaticMeshAsset;` — `UPROPERTY()`
- L454 _public member_ `FString ExternalFile;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterNode_427`  
`struct FDisplayClusterConfigurationJsonClusterNode_427`  
_L458-483_
- reflection: `USTRUCT()`
- L464 _public member_ `FString Host;` — `UPROPERTY()`
- L467 _public member_ `bool Sound = true;` — `UPROPERTY()`
- L470 _public member_ `bool FullScreen = false;` — `UPROPERTY()`
- L473 _public member_ `FDisplayClusterConfigurationJsonRectangle_427 Window;` — `UPROPERTY()`
- L476 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonPostprocess_427> Postprocess;` — `UPROPERTY()`
- L479 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonViewport_427> Viewports;` — `UPROPERTY()`
- L482 _public member_ `FDisplayClusterConfigurationFramePostProcess_OutputRemap_427 OutputRemap;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonCluster_427`  
`struct FDisplayClusterConfigurationJsonCluster_427`  
_L486-502_
- reflection: `USTRUCT()`
- L492 _public member_ `FDisplayClusterConfigurationJsonPrimaryNode_427 MasterNode;` — `UPROPERTY()`
- L495 _public member_ `FDisplayClusterConfigurationJsonClusterSync_427 Sync;` — `UPROPERTY()`
- L498 _public member_ `TMap<FString, FString> Network;` — `UPROPERTY()`
- L501 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonClusterNode_427> Nodes;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonDiagnostics_427`  
`struct FDisplayClusterConfigurationJsonDiagnostics_427`  
_L505-518_
- reflection: `USTRUCT()`
- L511 _public member_ `bool SimulateLag = false;` — `UPROPERTY()`
- L514 _public member_ `float MinLagTime = 0.01f;` — `UPROPERTY()`
- L517 _public member_ `float MaxLagTime = 0.3f;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonNdisplay_427`  
`struct FDisplayClusterConfigurationJsonNdisplay_427`  
_L523-551_
- reflection: `USTRUCT()`
- desc: "nDisplay" category structure
- L529 _public member_ `FString Description;` — `UPROPERTY()`
- L532 _public member_ `FString Version;` — `UPROPERTY()`
- L535 _public member_ `FString AssetPath;` — `UPROPERTY()`
- L538 _public member_ `FDisplayClusterConfigurationJsonMisc_427 Misc;` — `UPROPERTY()`
- L541 _public member_ `FDisplayClusterConfigurationJsonScene_427 Scene;` — `UPROPERTY()`
- L544 _public member_ `FDisplayClusterConfigurationJsonCluster_427 Cluster;` — `UPROPERTY()`
- L547 _public member_ `TMap<FString, FString> CustomParameters;` — `UPROPERTY()`
- L550 _public member_ `FDisplayClusterConfigurationJsonDiagnostics_427 Diagnostics;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonContainer_427`  
`struct FDisplayClusterConfigurationJsonContainer_427`  
_L555-562_
- reflection: `USTRUCT()`
- desc: The main nDisplay configuration structure. It's supposed to extract nDisplay related data from a collecting JSON file.
- L561 _public member_ `FDisplayClusterConfigurationJsonNdisplay_427 nDisplay;` — `UPROPERTY()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON500/DisplayClusterConfigurationJsonHelpers_500.h` (Private)


#### class `JSON500::DisplayClusterConfigurationJsonHelpers`  
`class DisplayClusterConfigurationJsonHelpers`  
_L32-46_
- desc: Auxiliary class with different type conversion functions
- L39 _public prototype_ `template <typename ConvertFrom> static FString ToString(const ConvertFrom& From);`
- L45 _public prototype_ `template <typename ConvertTo> static ConvertTo FromString(const FString& From);`
- L51 _function_ `template <> inline FString DisplayClusterConfigurationJsonHelpers::ToString<>(const EDisplayClusterConfigurationEyeStereoOffset& From)` — EDisplayClusterConfigurationEyeStereoOffset
- L73 _function_ `template <> inline EDisplayClusterConfigurationEyeStereoOffset DisplayClusterConfigurationJsonHelpers::FromString<>(const FString& From)`
- L95 _function_ `template <> inline FString DisplayClusterConfigurationJsonHelpers::ToString<>(const EDisplayClusterConfigurationViewportOverscanMode& InOverscanMode)` — EDisplayClusterConfigurationViewportOverscanMode
- L114 _function_ `template <> inline EDisplayClusterConfigurationViewportOverscanMode DisplayClusterConfigurationJsonHelpers::FromString<>(const FString& InOverscanModeString)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace JSON500`
- L13 _namespace_ `namespace config` (scope `JSON500`)
- L15 _namespace_ `namespace node` (scope `JSON500::config`)
- L17 _namespace_ `namespace viewport` (scope `JSON500::config::node`)
- L19 _namespace_ `namespace overscan` (scope `JSON500::config::node::viewport`)
- L21 _variable_ `static constexpr const TCHAR* OverscanNone = TEXT("non` (scope `JSON500::config::node::viewport::overscan`)
- L22 _variable_ `static constexpr const TCHAR* OverscanPixels = TEXT("pix` (scope `JSON500::config::node::viewport::overscan`)
- L23 _variable_ `static constexpr const TCHAR* OverscanPercent = TEXT("per` (scope `JSON500::config::node::viewport::overscan`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON500/DisplayClusterConfigurationJsonParser_500.h` (Private)


#### class `JSON500::FDisplayClusterConfigurationJsonParser`  
`class FDisplayClusterConfigurationJsonParser : public IDisplayClusterConfigurationDataParser`  
_L17-47_
- inherits: `IDisplayClusterConfigurationDataParser`
- desc: Config parser for JSON based config files
- L21 _public prototype_ `FDisplayClusterConfigurationJsonParser() = default;`
- L22 _public prototype_ `~FDisplayClusterConfigurationJsonParser() = default;`
- L26 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadData(const FString& FilePath, UObject* Owner = nullptr) override;` — Load data from a specified file
- L29 _public prototype_ `virtual bool SaveData(const UDisplayClusterConfigurationData* ConfigData, const FString& FilePath) override;` — Save data to a specified file
- L32 _public prototype_ `virtual bool AsString(const UDisplayClusterConfigurationData* ConfigData, FString& OutString) override;` — Convert configuration to string
- L36 _protected prototype_ `UDisplayClusterConfigurationData* ConvertDataToInternalTypes();` — [import data] Fill generic data container with parsed information
- L38 _protected prototype_ `bool ConvertDataToExternalTypes(const UDisplayClusterConfigurationData* InData);` — [export data] Extract data from generic container to specific containers
- L42 _private member_ `FDisplayClusterConfigurationJsonContainer_500 JsonData;` — Intermediate temporary data (Json types)
- L44 _private member_ `FString ConfigFile;` — Source file
- L46 _private member_ `UObject* ConfigDataOwner = nullptr;` — Owner for config data UObject we'll create on success

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace JSON500`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/Formats/JSON500/DisplayClusterConfigurationJsonTypes_500.h` (Private)


#### struct `FDisplayClusterConfigurationJsonRectangle_500`  
`struct FDisplayClusterConfigurationJsonRectangle_500`  
_L12-37_
- reflection: `USTRUCT()`
- L17 _public function_ `FDisplayClusterConfigurationJsonRectangle_500() : X(0), Y(0), W(0), H(0)`
- L21 _public function_ `FDisplayClusterConfigurationJsonRectangle_500(int32 _X, int32 _Y, int32 _W, int32 _H) : X(_X), Y(_Y), W(_W), H(_H)`
- L27 _public member_ `int32 X;` — `UPROPERTY()`
- L30 _public member_ `int32 Y;` — `UPROPERTY()`
- L33 _public member_ `int32 W;` — `UPROPERTY()`
- L36 _public member_ `int32 H;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonVector_500`  
`struct FDisplayClusterConfigurationJsonVector_500`  
_L41-78_
- reflection: `USTRUCT()`
- L46 _public function_ `FDisplayClusterConfigurationJsonVector_500() : FDisplayClusterConfigurationJsonVector_500(0.f, 0.f, 0.f)`
- L50 _public function_ `FDisplayClusterConfigurationJsonVector_500(float _X, float _Y, float _Z) : X(_X), Y(_Y), Z(_Z)`
- L54 _public function_ `FDisplayClusterConfigurationJsonVector_500(const FVector& Vector) : FDisplayClusterConfigurationJsonVector_500(Vector.X, Vector.Y, Vector.Z)`
- L60 _public member_ `float X;` — `UPROPERTY()`
- L63 _public member_ `float Y;` — `UPROPERTY()`
- L66 _public member_ `float Z;` — `UPROPERTY()`
- L69 _public function_ `static FVector ToVector(const FDisplayClusterConfigurationJsonVector_500& Data)`
- L74 _public function_ `static FDisplayClusterConfigurationJsonVector_500 FromVector(const FVector& Vector)`

#### struct `FDisplayClusterConfigurationJsonRotator_500`  
`struct FDisplayClusterConfigurationJsonRotator_500`  
_L82-119_
- reflection: `USTRUCT()`
- L87 _public function_ `FDisplayClusterConfigurationJsonRotator_500() : FDisplayClusterConfigurationJsonRotator_500(0.f, 0.f, 0.f)`
- L91 _public function_ `FDisplayClusterConfigurationJsonRotator_500(float P, float Y, float R) : Pitch(P), Yaw(Y), Roll(R)`
- L95 _public function_ `FDisplayClusterConfigurationJsonRotator_500(const FRotator& Rotator) : FDisplayClusterConfigurationJsonRotator_500(Rotator.Pitch, Rotator.Yaw, Rotator.Roll)`
- L101 _public member_ `float Pitch;` — `UPROPERTY()`
- L104 _public member_ `float Yaw;` — `UPROPERTY()`
- L107 _public member_ `float Roll;` — `UPROPERTY()`
- L110 _public function_ `static FRotator ToRotator(const FDisplayClusterConfigurationJsonRotator_500& Data)`
- L115 _public function_ `static FDisplayClusterConfigurationJsonRotator_500 FromRotator(const FRotator& Rotator)`

#### struct `FDisplayClusterConfigurationJsonSizeInt_500`  
`struct FDisplayClusterConfigurationJsonSizeInt_500`  
_L123-153_
- reflection: `USTRUCT()`
- L128 _public function_ `FDisplayClusterConfigurationJsonSizeInt_500() : FDisplayClusterConfigurationJsonSizeInt_500(0, 0)`
- L132 _public function_ `FDisplayClusterConfigurationJsonSizeInt_500(int W, int H) : Width(W), Height(H)`
- L138 _public member_ `int Width;` — `UPROPERTY()`
- L141 _public member_ `int Height;` — `UPROPERTY()`
- L144 _public function_ `static FIntPoint ToPoint(const FDisplayClusterConfigurationJsonSizeInt_500& Data)`
- L149 _public function_ `static FDisplayClusterConfigurationJsonSizeInt_500 FromPoint(const FIntPoint& Point)`

#### struct `FDisplayClusterConfigurationJsonSizeFloat_500`  
`struct FDisplayClusterConfigurationJsonSizeFloat_500`  
_L157-191_
- reflection: `USTRUCT()`
- L162 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_500() : FDisplayClusterConfigurationJsonSizeFloat_500(0.f, 0.f)`
- L166 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_500(float W, float H) : Width(W), Height(H)`
- L170 _public function_ `FDisplayClusterConfigurationJsonSizeFloat_500(const FVector2D& Vector) : FDisplayClusterConfigurationJsonSizeFloat_500(Vector.X, Vector.Y)`
- L176 _public member_ `float Width;` — `UPROPERTY()`
- L179 _public member_ `float Height;` — `UPROPERTY()`
- L182 _public function_ `static FVector2D ToVector(const FDisplayClusterConfigurationJsonSizeFloat_500& Data)`
- L187 _public function_ `static FDisplayClusterConfigurationJsonSizeFloat_500 FromVector(const FVector2D& Vector)`

#### struct `FDisplayClusterConfigurationJsonPolymorphicEntity_500`  
`struct FDisplayClusterConfigurationJsonPolymorphicEntity_500`  
_L195-205_
- reflection: `USTRUCT()`
- L201 _public member_ `FString Type;` — `UPROPERTY()`
- L204 _public member_ `TMap<FString, FString> Parameters;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonMisc_500`  
`struct FDisplayClusterConfigurationJsonMisc_500`  
_L209-237_
- reflection: `USTRUCT()`
- L214 _public function_ `FDisplayClusterConfigurationJsonMisc_500() : bFollowLocalPlayerCamera(false) , bExitOnEsc(true) , bOverrideViewportsFromExternalConfig(false) , bOverrideTransformsFromExternalConfig(false) , ClusterOuterViewportsBufferRatio(0.66f)`
- L224 _public member_ `bool bFollowLocalPlayerCamera;` — `UPROPERTY()`
- L227 _public member_ `bool bExitOnEsc;` — `UPROPERTY()`
- L230 _public member_ `bool bOverrideViewportsFromExternalConfig;` — `UPROPERTY()`
- L233 _public member_ `bool bOverrideTransformsFromExternalConfig;` — `UPROPERTY()`
- L236 _public member_ `float ClusterOuterViewportsBufferRatio;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponent_500`  
`struct FDisplayClusterConfigurationJsonSceneComponent_500`  
_L241-244_
- reflection: `USTRUCT()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentXform_500`  
`struct FDisplayClusterConfigurationJsonSceneComponentXform_500 : public FDisplayClusterConfigurationJsonSceneComponent_500`  
_L248-273_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponent_500`
- L254 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_500() : FDisplayClusterConfigurationJsonSceneComponentXform_500(FString(), FVector::ZeroVector, FRotator::ZeroRotator)`
- L258 _public function_ `FDisplayClusterConfigurationJsonSceneComponentXform_500(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation) : ParentId(InParentId) , Location(InLocation) , Rotation(InRotation)`
- L266 _public member_ `FString ParentId;` — `UPROPERTY()`
- L269 _public member_ `FDisplayClusterConfigurationJsonVector_500 Location;` — `UPROPERTY()`
- L272 _public member_ `FDisplayClusterConfigurationJsonRotator_500 Rotation;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentCamera_500`  
`struct FDisplayClusterConfigurationJsonSceneComponentCamera_500 : public FDisplayClusterConfigurationJsonSceneComponentXform_500`  
_L277-303_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_500`
- L283 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_500() : FDisplayClusterConfigurationJsonSceneComponentCamera_500(FString(), FVector::ZeroVector, FRotator::ZeroRotator, 6.4f, false, DisplayClusterConfigurationStrings::config::scene::camera::CameraStereoOffsetNone)`
- L287 _public function_ `FDisplayClusterConfigurationJsonSceneComponentCamera_500(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, float InInterpupillaryDistance, bool bInSwapEyes, const FString& InStereoOffset) : FDisplayClusterConfigurationJsonSceneComponentXform_500(InParentId, InLocation, InRotation) , InterpupillaryDistance(InInterpupillaryDistance) , SwapEyes(bInSwapEyes) , StereoOffset(InStereoOffset)`
- L296 _public member_ `float InterpupillaryDistance;` — `UPROPERTY()`
- L299 _public member_ `bool SwapEyes;` — `UPROPERTY()`
- L302 _public member_ `FString StereoOffset;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonSceneComponentScreen_500`  
`struct FDisplayClusterConfigurationJsonSceneComponentScreen_500 : public FDisplayClusterConfigurationJsonSceneComponentXform_500`  
_L307-325_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonSceneComponentXform_500`
- L313 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_500() : FDisplayClusterConfigurationJsonSceneComponentScreen_500(FString(), FVector::ZeroVector, FRotator::ZeroRotator, FVector2D(1.f, 1.f))`
- L317 _public function_ `FDisplayClusterConfigurationJsonSceneComponentScreen_500(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, const FVector2D& InSize) : FDisplayClusterConfigurationJsonSceneComponentXform_500(InParentId, InLocation, InRotation) , Size(InSize)`
- L324 _public member_ `FDisplayClusterConfigurationJsonSizeFloat_500 Size;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonScene_500`  
`struct FDisplayClusterConfigurationJsonScene_500`  
_L329-342_
- reflection: `USTRUCT()`
- L335 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentXform_500> Xforms;` — `UPROPERTY()`
- L338 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentCamera_500> Cameras;` — `UPROPERTY()`
- L341 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonSceneComponentScreen_500> Screens;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonPrimaryNode_500`  
`struct FDisplayClusterConfigurationJsonPrimaryNode_500`  
_L346-356_
- reflection: `USTRUCT()`
- L352 _public member_ `FString Id;` — `UPROPERTY()`
- L355 _public member_ `TMap<FString, uint16> Ports;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterSyncPolicy_500`  
`struct FDisplayClusterConfigurationJsonClusterSyncPolicy_500 : public FDisplayClusterConfigurationJsonPolymorphicEntity_500`  
_L360-364_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_500`

#### struct `FDisplayClusterConfigurationJsonClusterSync_500`  
`struct FDisplayClusterConfigurationJsonClusterSync_500`  
_L368-378_
- reflection: `USTRUCT()`
- L374 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_500 RenderSyncPolicy;` — `UPROPERTY()`
- L377 _public member_ `FDisplayClusterConfigurationJsonClusterSyncPolicy_500 InputSyncPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationFailoverSettings_500`  
`struct FDisplayClusterConfigurationFailoverSettings_500`  
_L382-399_
- reflection: `USTRUCT()`
- L390 _public member_ `bool bEnabled = false;` — `UPROPERTY()` — Enable/disable failover subsystem
- L394 _public member_ `TArray<FString> PrimaryBackups;` — `UPROPERTY()` — Prioritized nodes for primary node replacement. Used in the same order as listed.
- L398 _public member_ `TArray<FString> CriticalNodes;` — `UPROPERTY()` — Critical nodes not allowed to fail.

#### struct `FDisplayClusterConfigurationJsonPostprocess_500`  
`struct FDisplayClusterConfigurationJsonPostprocess_500 : public FDisplayClusterConfigurationJsonPolymorphicEntity_500`  
_L403-407_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_500`

#### struct `FDisplayClusterConfigurationJsonProjectionPolicy_500`  
`struct FDisplayClusterConfigurationJsonProjectionPolicy_500 : public FDisplayClusterConfigurationJsonPolymorphicEntity_500`  
_L411-415_
- reflection: `USTRUCT()`
- inherits: `FDisplayClusterConfigurationJsonPolymorphicEntity_500`

#### struct `FDisplayClusterConfigurationJsonOverscan_500`  
`struct FDisplayClusterConfigurationJsonOverscan_500`  
_L419-444_
- reflection: `USTRUCT()`
- L425 _public member_ `bool bEnabled = false;` — `UPROPERTY()`
- L428 _public member_ `FString Mode = "";` — `UPROPERTY()`
- L431 _public member_ `int32 Left = 0;` — `UPROPERTY()`
- L434 _public member_ `int32 Right = 0;` — `UPROPERTY()`
- L437 _public member_ `int32 Top = 0;` — `UPROPERTY()`
- L440 _public member_ `int32 Bottom = 0;` — `UPROPERTY()`
- L443 _public member_ `bool Oversize = 0;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonViewport_500`  
`struct FDisplayClusterConfigurationJsonViewport_500`  
_L448-476_
- reflection: `USTRUCT()`
- L454 _public member_ `FString Camera;` — `UPROPERTY()`
- L457 _public member_ `float BufferRatio = 1.0f;` — `UPROPERTY()`
- L460 _public member_ `int32 GPUIndex = 0;` — `UPROPERTY()`
- L463 _public member_ `bool AllowCrossGPUTransfer = false;` — `UPROPERTY()`
- L466 _public member_ `bool IsShared = false;` — `UPROPERTY()`
- L469 _public member_ `FDisplayClusterConfigurationJsonOverscan_500 Overscan;` — `UPROPERTY()`
- L472 _public member_ `FDisplayClusterConfigurationJsonRectangle_500 Region;` — `UPROPERTY()`
- L475 _public member_ `FDisplayClusterConfigurationJsonProjectionPolicy_500 ProjectionPolicy;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationFramePostProcess_OutputRemap_500`  
`struct FDisplayClusterConfigurationFramePostProcess_OutputRemap_500`  
_L480-496_
- reflection: `USTRUCT()`
- L486 _public member_ `bool bEnable = false;` — `UPROPERTY()`
- L489 _public member_ `FString DataSource;` — `UPROPERTY()`
- L492 _public member_ `FString StaticMeshAsset;` — `UPROPERTY()`
- L495 _public member_ `FString ExternalFile;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonClusterNode_500`  
`struct FDisplayClusterConfigurationJsonClusterNode_500`  
_L500-534_
- reflection: `USTRUCT()`
- L506 _public member_ `FString Host;` — `UPROPERTY()`
- L509 _public member_ `bool Sound = true;` — `UPROPERTY()`
- L512 _public member_ `bool FullScreen = false;` — `UPROPERTY()`
- L515 _public member_ `bool RenderHeadless = false;` — `UPROPERTY()`
- L518 _public member_ `int32 GraphicsAdapter = -1;` — `UPROPERTY()`
- L521 _public member_ `bool TextureShare = false;` — `UPROPERTY()`
- L524 _public member_ `FDisplayClusterConfigurationJsonRectangle_500 Window;` — `UPROPERTY()`
- L527 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonPostprocess_500> Postprocess;` — `UPROPERTY()`
- L530 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonViewport_500> Viewports;` — `UPROPERTY()`
- L533 _public member_ `FDisplayClusterConfigurationFramePostProcess_OutputRemap_500 OutputRemap;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonCluster_500`  
`struct FDisplayClusterConfigurationJsonCluster_500`  
_L538-557_
- reflection: `USTRUCT()`
- L544 _public member_ `FDisplayClusterConfigurationJsonPrimaryNode_500 PrimaryNode;` — `UPROPERTY()`
- L547 _public member_ `FDisplayClusterConfigurationJsonClusterSync_500 Sync;` — `UPROPERTY()`
- L550 _public member_ `TMap<FString, FString> Network;` — `UPROPERTY()`
- L553 _public member_ `FDisplayClusterConfigurationFailoverSettings_500 Failover;` — `UPROPERTY()`
- L556 _public member_ `TMap<FString, FDisplayClusterConfigurationJsonClusterNode_500> Nodes;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonDiagnostics_500`  
`struct FDisplayClusterConfigurationJsonDiagnostics_500`  
_L561-574_
- reflection: `USTRUCT()`
- L567 _public member_ `bool SimulateLag = false;` — `UPROPERTY()`
- L570 _public member_ `float MinLagTime = 0.01f;` — `UPROPERTY()`
- L573 _public member_ `float MaxLagTime = 0.3f;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonNdisplay_500`  
`struct FDisplayClusterConfigurationJsonNdisplay_500`  
_L579-607_
- reflection: `USTRUCT()`
- desc: "nDisplay" category structure
- L585 _public member_ `FString Description;` — `UPROPERTY()`
- L588 _public member_ `FString Version;` — `UPROPERTY()`
- L591 _public member_ `FString AssetPath;` — `UPROPERTY()`
- L594 _public member_ `FDisplayClusterConfigurationJsonMisc_500 Misc;` — `UPROPERTY()`
- L597 _public member_ `FDisplayClusterConfigurationJsonScene_500 Scene;` — `UPROPERTY()`
- L600 _public member_ `FDisplayClusterConfigurationJsonCluster_500 Cluster;` — `UPROPERTY()`
- L603 _public member_ `TMap<FString, FString> CustomParameters;` — `UPROPERTY()`
- L606 _public member_ `FDisplayClusterConfigurationJsonDiagnostics_500 Diagnostics;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationJsonContainer_500`  
`struct FDisplayClusterConfigurationJsonContainer_500`  
_L612-619_
- reflection: `USTRUCT()`
- desc: The main nDisplay configuration structure. It's supposed to extract nDisplay related data from a collecting JSON file.
- L618 _public member_ `FDisplayClusterConfigurationJsonNdisplay_500 nDisplay;` — `UPROPERTY()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/VersionChecker/DisplayClusterConfigurationVersionChecker.h` (Private)


#### class `FDisplayClusterConfigurationVersionChecker`  
`class FDisplayClusterConfigurationVersionChecker`  
_L12-34_
- desc: Version checker for nDisplay config files
- L15 _public prototype_ `FDisplayClusterConfigurationVersionChecker() = default;`
- L16 _public prototype_ `~FDisplayClusterConfigurationVersionChecker() = default;`
- L20 _public prototype_ `EDisplayClusterConfigurationVersion GetConfigVersion(const FString& FilePath) const;` — Returns version of a specified config file
- L24 _protected prototype_ `EDisplayClusterConfigurationVersion GetConfigVersionJson(const FString& FilePath) const;` — Helper function to deal with JSON files that might be of different version
- L33 _protected prototype_ `EConfigFileType GetConfigFileType(const FString& InConfigPath) const;`

#### enum `FDisplayClusterConfigurationVersionChecker::EConfigFileType`  
`enum class EConfigFileType`  
_L27-31_
- L29 _public enumerator_ `Unknown`
- L30 _public enumerator_ `Json`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Private/VersionChecker/DisplayClusterConfigurationVersionCheckerTypes.h` (Private)


#### struct `FDisplayClusterConfigurationVersion`  
`struct FDisplayClusterConfigurationVersion`  
_L11-18_
- reflection: `USTRUCT()`
- desc: "Version" property
- L17 _public member_ `FString Version;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationVersionContainer`  
`struct FDisplayClusterConfigurationVersionContainer`  
_L22-29_
- reflection: `USTRUCT()`
- desc: The main JSON container
- L28 _public member_ `FDisplayClusterConfigurationVersion nDisplay;` — `UPROPERTY()`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationStrings.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace DisplayClusterConfigurationStrings`
- L10 _namespace_ `namespace gui` (scope `DisplayClusterConfigurationStrings`)
- L12 _namespace_ `namespace preview` (scope `DisplayClusterConfigurationStrings::gui`)
- L14 _variable_ `static constexpr const TCHAR* PreviewNodeNone = TEXT("Non` (scope `DisplayClusterConfigurationStrings::gui::preview`)
- L19 _namespace_ `namespace categories` (scope `DisplayClusterConfigurationStrings`)
- L21 _variable_ `static constexpr const TCHAR* DefaultCategory = TEXT("NDi` (scope `DisplayClusterConfigurationStrings::categories`)
- L23 _variable_ `static constexpr const TCHAR* ClusterCategory = TEXT("NDi` (scope `DisplayClusterConfigurationStrings::categories`)
- L24 _variable_ `static constexpr const TCHAR* ClusterConfigurationCategory = TEXT("NDi` (scope `DisplayClusterConfigurationStrings::categories`)
- L25 _variable_ `static constexpr const TCHAR* ClusterPostprocessCategory = TEXT("Pos` (scope `DisplayClusterConfigurationStrings::categories`)
- L26 _variable_ `static constexpr const TCHAR* ColorGradingCategory = TEXT("Col` (scope `DisplayClusterConfigurationStrings::categories`)
- L27 _variable_ `static constexpr const TCHAR* CameraColorGradingCategoryOrig = TEXT("Inn` (scope `DisplayClusterConfigurationStrings::categories`)
- L28 _variable_ `static constexpr const TCHAR* CameraColorGradingCategory = TEXT("Col` (scope `DisplayClusterConfigurationStrings::categories`)
- L29 _variable_ `static constexpr const TCHAR* ChromaKeyCategory = TEXT("Chr` (scope `DisplayClusterConfigurationStrings::categories`)
- L30 _variable_ `static constexpr const TCHAR* LightcardCategory = TEXT("Lig` (scope `DisplayClusterConfigurationStrings::categories`)
- L31 _variable_ `static constexpr const TCHAR* OCIOCategory = TEXT("OCI` (scope `DisplayClusterConfigurationStrings::categories`)
- L32 _variable_ `static constexpr const TCHAR* ExposureCategory = TEXT("Exp` (scope `DisplayClusterConfigurationStrings::categories`)
- L33 _variable_ `static constexpr const TCHAR* MediaCategory = TEXT("Med` (scope `DisplayClusterConfigurationStrings::categories`)
- L34 _variable_ `static constexpr const TCHAR* TileCategory = TEXT("Til` (scope `DisplayClusterConfigurationStrings::categories`)
- L35 _variable_ `static constexpr const TCHAR* OverrideCategory = TEXT("Tex` (scope `DisplayClusterConfigurationStrings::categories`)
- L36 _variable_ `static constexpr const TCHAR* ViewportsCategory = TEXT("Vie` (scope `DisplayClusterConfigurationStrings::categories`)
- L38 _variable_ `static constexpr const TCHAR* InCameraVFXCategory = TEXT("In` (scope `DisplayClusterConfigurationStrings::categories`)
- L39 _variable_ `static constexpr const TCHAR* InnerFrustumCategory = TEXT("Inn` (scope `DisplayClusterConfigurationStrings::categories`)
- L41 _variable_ `static constexpr const TCHAR* ICVFXCameraCategoryOrig = TEXT("ICV` (scope `DisplayClusterConfigurationStrings::categories`)
- L42 _variable_ `static constexpr const TCHAR* ICVFXCameraCategory = TEXT("Cam` (scope `DisplayClusterConfigurationStrings::categories`)
- L44 _variable_ `static constexpr const TCHAR* ConfigurationCategory = TEXT("Con` (scope `DisplayClusterConfigurationStrings::categories`)
- L45 _variable_ `static constexpr const TCHAR* PreviewCategory = TEXT("Pre` (scope `DisplayClusterConfigurationStrings::categories`)
- L46 _variable_ `static constexpr const TCHAR* AdvancedCategory = TEXT("Adv` (scope `DisplayClusterConfigurationStrings::categories`)
- L47 _variable_ `static constexpr const TCHAR* TextureShareCategory = TEXT("Tex` (scope `DisplayClusterConfigurationStrings::categories`)
- L48 _variable_ `static constexpr const TCHAR* NetworkCategory = TEXT("Net` (scope `DisplayClusterConfigurationStrings::categories`)
- L49 _variable_ `static constexpr const TCHAR* RenderingCategory = TEXT("Ren` (scope `DisplayClusterConfigurationStrings::categories`)
- L50 _variable_ `static constexpr const TCHAR* StereoCategory = TEXT("Ste` (scope `DisplayClusterConfigurationStrings::categories`)
- L52 _variable_ `static constexpr const TCHAR* ViewPointStereoCategory = TEXT("Ste` (scope `DisplayClusterConfigurationStrings::categories`)
- L53 _variable_ `static constexpr const TCHAR* ViewPointCameraPostProcessCategory = TEXT("Cam` (scope `DisplayClusterConfigurationStrings::categories`)
- L54 _variable_ `static constexpr const TCHAR* ViewPointInFrustumProjectionCategory = TEXT("Fru` (scope `DisplayClusterConfigurationStrings::categories`)
- L58 _namespace_ `namespace file` (scope `DisplayClusterConfigurationStrings`)
- L60 _variable_ `static constexpr const TCHAR* FileExtJson = TEXT("ndi` (scope `DisplayClusterConfigurationStrings::file`)
- L63 _namespace_ `namespace config` (scope `DisplayClusterConfigurationStrings`)
- L65 _namespace_ `namespace cluster` (scope `DisplayClusterConfigurationStrings::config`)
- L67 _namespace_ `namespace ports` (scope `DisplayClusterConfigurationStrings::config::cluster`)
- L69 _variable_ `static constexpr const TCHAR* PortClusterSync = TEXT("Clu` (scope `DisplayClusterConfigurationStrings::config::cluster::ports`)
- L70 _variable_ `static constexpr const TCHAR* PortClusterEventsJson = TEXT("Clu` (scope `DisplayClusterConfigurationStrings::config::cluster::ports`)
- L71 _variable_ `static constexpr const TCHAR* PortClusterEventsBinary = TEXT("Clu` (scope `DisplayClusterConfigurationStrings::config::cluster::ports`)
- L74 _namespace_ `namespace network` (scope `DisplayClusterConfigurationStrings::config::cluster`)
- L76 _variable_ `static constexpr const TCHAR* NetConnectRetriesAmount = TEXT("Con` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L77 _variable_ `static constexpr const TCHAR* NetConnectRetryDelay = TEXT("Con` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L78 _variable_ `static constexpr const TCHAR* NetGameStartBarrierTimeout = TEXT("Gam` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L79 _variable_ `static constexpr const TCHAR* NetFrameStartBarrierTimeout = TEXT("Fra` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L80 _variable_ `static constexpr const TCHAR* NetFrameEndBarrierTimeout = TEXT("Fra` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L81 _variable_ `static constexpr const TCHAR* NetRenderSyncBarrierTimeout = TEXT("Ren` (scope `DisplayClusterConfigurationStrings::config::cluster::network`)
- L84 _namespace_ `namespace input_sync` (scope `DisplayClusterConfigurationStrings::config::cluster`)
- L86 _variable_ `static constexpr const TCHAR* InputSyncPolicyNone = TEXT("Non` (scope `DisplayClusterConfigurationStrings::config::cluster::input_sync`)
- L87 _variable_ `static constexpr const TCHAR* InputSyncPolicyReplicatePrimary = TEXT("Rep` (scope `DisplayClusterConfigurationStrings::config::cluster::input_sync`)
- L90 _namespace_ `namespace render_sync` (scope `DisplayClusterConfigurationStrings::config::cluster`)
- L92 _variable_ `static constexpr const TCHAR* None = TEXT("non` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`)
- L93 _variable_ `static constexpr const TCHAR* Ethernet = TEXT("eth` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`)
- L94 _variable_ `static constexpr const TCHAR* EthernetBarrier = TEXT("eth` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`)
- L97 _variable_ `static constexpr const TCHAR* Nvidia = TEXT("nvi` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`) — NVIDIA Swap Barrier (old)
- L98 _variable_ `static constexpr const TCHAR* NvidiaSwapBarrier = TEXT("swa` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`)
- L99 _variable_ `static constexpr const TCHAR* NvidiaSwapGroup = TEXT("swa` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`)
- L102 _variable_ `static constexpr const TCHAR* NvidiaPresentBarrier = TEXT("nvi` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`) — NVIDIA Present Barrier (new)
- L105 _variable_ `static constexpr const TCHAR* HeadlessRenderingSyncPolicy = None;` (scope `DisplayClusterConfigurationStrings::config::cluster::render_sync`) — Always use 'none' for headless rendering
- L109 _namespace_ `namespace scene` (scope `DisplayClusterConfigurationStrings::config`)
- L111 _namespace_ `namespace camera` (scope `DisplayClusterConfigurationStrings::config::scene`)
- L113 _variable_ `static constexpr const TCHAR* CameraStereoOffsetNone = TEXT("non` (scope `DisplayClusterConfigurationStrings::config::scene::camera`)
- L114 _variable_ `static constexpr const TCHAR* CameraStereoOffsetLeft = TEXT("lef` (scope `DisplayClusterConfigurationStrings::config::scene::camera`)
- L115 _variable_ `static constexpr const TCHAR* CameraStereoOffsetRight = TEXT("rig` (scope `DisplayClusterConfigurationStrings::config::scene::camera`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes.h` (Public)


#### struct `FDisplayClusterConfigurationInfo`  
`struct FDisplayClusterConfigurationInfo`  
_L25-43_
- reflection: `USTRUCT(Blueprintable)`
- L30 _public function_ `FDisplayClusterConfigurationInfo() : Version(DisplayClusterConfiguration::GetCurrentConfigurationSchemeMarker())`
- L36 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`
- L39 _public member_ `FString Version;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NDisplay)`
- L42 _public member_ `FString AssetPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NDisplay)`

#### class `UDisplayClusterConfigurationSceneComponent`  
`class UDisplayClusterConfigurationSceneComponent : public UDisplayClusterConfigurationData_Base`  
_L47-72_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfigurationData_Base`
- desc: Scene hierarchy
- L53 _public function_ `UDisplayClusterConfigurationSceneComponent() : UDisplayClusterConfigurationSceneComponent(FString(), FVector::ZeroVector, FRotator::ZeroRotator)`
- L57 _public function_ `UDisplayClusterConfigurationSceneComponent(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation) : ParentId(InParentId) , Location(InLocation) , Rotation(InRotation)`
- L65 _public member_ `FString ParentId;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L68 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L71 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`

#### class `UDisplayClusterConfigurationSceneComponentXform`  
`class UDisplayClusterConfigurationSceneComponentXform : public UDisplayClusterConfigurationSceneComponent`  
_L75-88_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfigurationSceneComponent`
- L81 _public function_ `UDisplayClusterConfigurationSceneComponentXform() : UDisplayClusterConfigurationSceneComponentXform(FString(), FVector::ZeroVector, FRotator::ZeroRotator)`
- L85 _public function_ `UDisplayClusterConfigurationSceneComponentXform(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation) : UDisplayClusterConfigurationSceneComponent(InParentId , InLocation, InRotation)`

#### class `UDisplayClusterConfigurationSceneComponentScreen`  
`class UDisplayClusterConfigurationSceneComponentScreen : public UDisplayClusterConfigurationSceneComponent`  
_L91-109_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfigurationSceneComponent`
- L97 _public function_ `UDisplayClusterConfigurationSceneComponentScreen() : UDisplayClusterConfigurationSceneComponentScreen(FString(), FVector::ZeroVector, FRotator::ZeroRotator, FVector2D(100.f, 100.f))`
- L101 _public function_ `UDisplayClusterConfigurationSceneComponentScreen(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, const FVector2D& InSize) : UDisplayClusterConfigurationSceneComponent(InParentId, InLocation, InRotation) , Size(InSize)`
- L108 _public member_ `FVector2D Size;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`

#### class `UDisplayClusterConfigurationSceneComponentCamera`  
`class UDisplayClusterConfigurationSceneComponentCamera : public UDisplayClusterConfigurationSceneComponent`  
_L112-139_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfigurationSceneComponent`
- L118 _public function_ `UDisplayClusterConfigurationSceneComponentCamera() : UDisplayClusterConfigurationSceneComponentCamera(FString(), FVector::ZeroVector, FRotator::ZeroRotator, 6.4f, false, EDisplayClusterConfigurationEyeStereoOffset::None)`
- L122 _public function_ `UDisplayClusterConfigurationSceneComponentCamera(const FString& InParentId, const FVector& InLocation, const FRotator& InRotation, float InInterpupillaryDistance, bool bInSwapEyes, EDisplayClusterConfigurationEyeStereoOffset InStereoOffset) : UDisplayClusterConfigurationSceneComponent(InParentId, InLocation, InRotation) , InterpupillaryDistance(InInterpupillaryDistance) , bSwapEyes(bInSwapEyes) , StereoOffset(InStereoOffset)`
- L132 _public member_ `float InterpupillaryDistance;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L135 _public member_ `bool bSwapEyes;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L138 _public member_ `EDisplayClusterConfigurationEyeStereoOffset StereoOffset;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`

#### class `UDisplayClusterConfigurationScene`  
`class UDisplayClusterConfigurationScene : public UDisplayClusterConfigurationData_Base`  
_L142-160_
- reflection: `UCLASS()`
- inherits: `UDisplayClusterConfigurationData_Base`
- L149 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationSceneComponentXform>> Xforms;` — `UPROPERTY()`
- L152 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationSceneComponentScreen>> Screens;` — `UPROPERTY()`
- L155 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationSceneComponentCamera>> Cameras;` — `UPROPERTY()`
- L158 _protected prototype_ `virtual void GetObjectsToExport(TArray<UObject*>& OutObjects) override;`

#### struct `FDisplayClusterConfigurationPrimaryNodePorts`  
`struct FDisplayClusterConfigurationPrimaryNodePorts`  
_L166-185_
- reflection: `USTRUCT(Blueprintable)`
- desc: Cluster
- L171 _public prototype_ `FDisplayClusterConfigurationPrimaryNodePorts();`
- L176 _public member_ `uint16 ClusterSync;` — `UPROPERTY(EditAnywhere, Category = NDisplay, meta = (ClampMin = "1024", ClampMax = "65535", UIMin = "1024", UIMax = "65535"))` — Advanced: TCP port for nDisplay internal services
- L180 _public member_ `uint16 ClusterEventsJson;` — `UPROPERTY(EditAnywhere, Category = NDisplay, meta = (ClampMin = "1024", ClampMax = "65535", UIMin = "1024", UIMax = "65535"))` — Advanced: network port for Json Cluster Events
- L184 _public member_ `uint16 ClusterEventsBinary;` — `UPROPERTY(EditAnywhere, Category = NDisplay, meta = (ClampMin = "1024", ClampMax = "65535", UIMin = "1024", UIMax = "65535"))` — Advanced: network port for Binary Cluster Events

#### struct `FDisplayClusterConfigurationPrimaryNode`  
`struct FDisplayClusterConfigurationPrimaryNode`  
_L188-198_
- reflection: `USTRUCT(Blueprintable)`
- L194 _public member_ `FString Id;` — `UPROPERTY(BlueprintReadOnly, Category = NDisplay)`
- L197 _public member_ `FDisplayClusterConfigurationPrimaryNodePorts Ports;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (DisplayName = "Primary Node Ports"))`

#### struct `FDisplayClusterConfigurationRenderSyncPolicy`  
`struct FDisplayClusterConfigurationRenderSyncPolicy : public FDisplayClusterConfigurationPolymorphicEntity`  
_L201-205_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationPolymorphicEntity`

#### struct `FDisplayClusterConfigurationInputSyncPolicy`  
`struct FDisplayClusterConfigurationInputSyncPolicy : public FDisplayClusterConfigurationPolymorphicEntity`  
_L208-212_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationPolymorphicEntity`

#### struct `FDisplayClusterConfigurationClusterSync`  
`struct FDisplayClusterConfigurationClusterSync`  
_L215-228_
- reflection: `USTRUCT(Blueprintable)`
- L220 _public prototype_ `FDisplayClusterConfigurationClusterSync();`
- L224 _public member_ `FDisplayClusterConfigurationRenderSyncPolicy RenderSyncPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)`
- L227 _public member_ `FDisplayClusterConfigurationInputSyncPolicy InputSyncPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Configuration)`

#### struct `FDisplayClusterConfigurationNetworkSettings`  
`struct FDisplayClusterConfigurationNetworkSettings`  
_L232-264_
- reflection: `USTRUCT(Blueprintable)`
- L238 _public prototype_ `FDisplayClusterConfigurationNetworkSettings();`
- L243 _public member_ `int32 ConnectRetriesAmount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "1", ClampMax = "500", UIMin = "1", UIMax = "500"))` — Advanced: amount of times nDisplay tries to reconnect before dropping
- L247 _public member_ `int32 ConnectRetryDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "1", ClampMax = "5000", UIMin = "1", UIMax = "5000"))` — Advanced: delay in between connection retries
- L251 _public member_ `int32 GameStartBarrierTimeout;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "5000", UIMin = "5000"))` — Advanced: timeout for Game Thread Barrier
- L255 _public member_ `int32 FrameStartBarrierTimeout;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "1", UIMin = "1"))` — Advanced: timeout value for Start Frame Barrier
- L259 _public member_ `int32 FrameEndBarrierTimeout;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "1", UIMin = "1"))` — Advanced: timeout value for End Frame Barrier
- L263 _public member_ `int32 RenderSyncBarrierTimeout;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "1", UIMin = "1"))` — Advanced: timeout value for Render Sync

#### struct `FDisplayClusterConfigurationFailoverSettings`  
`struct FDisplayClusterConfigurationFailoverSettings`  
_L268-297_
- reflection: `USTRUCT(Blueprintable)`
- L274 _public prototype_ `FDisplayClusterConfigurationFailoverSettings();`
- L280 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Failover, meta = (DisplayName = "Enable Failover"))` — Enable/disable failover subsystem
- L284 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList PrimaryBackups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Failover, meta = (DisplayName = "Prioritized Primary Backups", EditCondition = "bEnabled", ClusterItemType = ClusterNodes))` — Prioritized nodes for primary node replacement. Used in the same order as listed.
- L288 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList CriticalNodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Failover, meta = (DisplayName = "Critical Nodes", EditCondition = "bEnabled", ClusterItemType = ClusterNodes))` — Critical cluster nodes. None of these are allowed to fail. If even one fails, the cluster will self-terminate.
- L295 _public member_ `EDisplayClusterConfigurationFailoverPolicy FailoverPolicy = EDisplayClusterConfigurationFailoverPolicy::Disabled;` — `UE_DEPRECATED(5.6, "This property has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated."))`

#### struct `FDisplayClusterConfigurationExternalImage`  
`struct FDisplayClusterConfigurationExternalImage`  
_L301-307_
- reflection: `USTRUCT()`
- L306 _public member_ `FString ImagePath;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`

#### class `UDisplayClusterConfigurationClusterNode`  
`class UDisplayClusterConfigurationClusterNode : public UDisplayClusterConfigurationData_Base`  
_L310-414_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UDisplayClusterConfigurationData_Base`
- L316 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`
- L318 _public member_ `FOnPostEditChangeChainProperty OnPostEditChangeChainProperty;`
- L321 _public prototype_ `UDisplayClusterConfigurationClusterNode();`
- L324 _public prototype_ `void GetViewportIds(TArray<FString>& OutViewportIds) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")`
- L327 _public prototype_ `UDisplayClusterConfigurationViewport* GetViewport(const FString& ViewportId) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")`
- L331 _public prototype_ `void GetReferencedMeshNames(TArray<FString>& OutMeshNames) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Return all references to meshes from policy, and other
- L335 _public prototype_ `virtual void PostLoad() override;`
- L336 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L339 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L346 _public member_ `FString Host;` — `UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Network", meta = (DisplayName = "Host IP Address"))` — IP address of this specific cluster Node
- L350 _public member_ `bool bIsSoundEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Enable Sound"))` — Enables or disables sound on nDisplay primary Node
- L354 _public member_ `bool bIsFullscreen;` — `UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Configuration", meta = (DisplayName = "Fullscreen"))` — Enables application window native fullscreen support
- L358 _public member_ `FDisplayClusterConfigurationRectangle WindowRect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Window", DisplayMode = "Compound", FixedAspectRatioProperty = "bFixedAspectRatio"))` — Defines the application window size in pixels
- L362 _public member_ `FDisplayClusterConfigurationFramePostProcess_OutputRemap OutputRemap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Output Remapping"))` — Output remapping settings for the selected cluster node
- L366 _public member_ `bool bRenderHeadless = false;` — `UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Configuration", meta = (DisplayName = "Headless Rendering"))` — Activates headless rendering for this cluster node
- L370 _public member_ `int32 GraphicsAdapter = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Configuration", meta = (DisplayName = "Graphics Adapter"))` — Hint for setting the r.GraphicsAdapter CVar when launching this cluster node. Note that this is distinct from the GPU Node Indices assigned to viewports.
- L374 _public member_ `bool bEnableTextureShare = false;` — `UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Configuration", meta = (DisplayName = "Enable Texture Share"))` — Enables texture sharing for this cluster node
- L379 _public member_ `bool bFixedAspectRatio;` — `UPROPERTY(EditAnywhere, Category = "Configuration", meta = (HideProperty))` — Locks the application window aspect ratio for easier resizing
- L383 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationViewport>> Viewports;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, EditFixedSize, Instanced, Category = "Configuration", meta = (DisplayThumbnail = false))`
- L386 _public member_ `TMap<FString, FDisplayClusterConfigurationPostprocess> Postprocess;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration", meta = (DisplayName = "Custom Output Settings", DisplayThumbnail = false, ShowInnerProperties))`
- L390 _public member_ `FDisplayClusterConfigurationMediaNodeBackbuffer MediaSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media", ShowOnlyInnerProperties))` — Media settings
- L394 _public member_ `bool bIsVisible;` — `UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (HideProperty))`
- L397 _public member_ `bool bIsUnlocked;` — `UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (HideProperty))`
- L401 _public member_ `FDisplayClusterConfigurationExternalImage PreviewImage;` — `UPROPERTY(EditDefaultsOnly, Category = "Configuration")` — Binds a background preview image for easier output mapping
- L409 _public member_ `FDisplayClusterConfigurationMediaViewport Media;` — `UE_DEPRECATED(5.4, "This property has been deprecated. Please use 'MediaSettings'.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated. Please use 'MediaSettings'."))`
- L413 _protected prototype_ `virtual void GetObjectsToExport(TArray<UObject*>& OutObjects) override;`

#### class `UDisplayClusterConfigurationHostDisplayData`  
`class UDisplayClusterConfigurationHostDisplayData : public UObject`  
_L417-470_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- L422 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`
- L424 _public member_ `FOnPostEditChangeChainProperty OnPostEditChangeChainProperty;`
- L427 _public prototype_ `UDisplayClusterConfigurationHostDisplayData();`
- L432 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;` — UObject interface
- L439 _public member_ `FText HostName;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Custom name for the Host PC. No effect on nDisplay
- L443 _public member_ `FVector2D Position;` — `UPROPERTY(EditAnywhere, Category = "Configuration", meta = (EditCondition = "bAllowManualPlacement"))` — Arbitrary position of the Host PC in 2D workspace. No effect on nDisplay
- L447 _public member_ `bool bAllowManualPlacement;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Disables the automatic placement of Host PCs
- L451 _public member_ `FVector2D HostResolution;` — `UPROPERTY(EditAnywhere, Category = "Configuration", meta = (EditCondition = "bAllowManualSizing", AllowPreserveRatio))` — Resolution of Host PC in pixels
- L455 _public member_ `bool bAllowManualSizing;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Allows to manually resize the Host PC resolution
- L459 _public member_ `FVector2D Origin;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Specify coordinates of the Host PC origin in relation to OS configuration
- L463 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = "Configuration")` — Specify custom and arbitrary color for a given Host PC
- L466 _public member_ `bool bIsVisible;` — `UPROPERTY()`
- L469 _public member_ `bool bIsUnlocked;` — `UPROPERTY()`

#### class `UDisplayClusterConfigurationCluster`  
`class UDisplayClusterConfigurationCluster : public UDisplayClusterConfigurationData_Base`  
_L473-519_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UDisplayClusterConfigurationData_Base`
- L480 _public member_ `FDisplayClusterConfigurationPrimaryNode PrimaryNode;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration", meta = (ShowOnlyInnerProperties))`
- L483 _public member_ `FDisplayClusterConfigurationClusterSync Sync;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration", meta = (ShowOnlyInnerProperties))`
- L486 _public member_ `FDisplayClusterConfigurationNetworkSettings Network;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")`
- L489 _public member_ `FDisplayClusterConfigurationFailoverSettings Failover;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")`
- L492 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationClusterNode>> Nodes;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, EditFixedSize, Instanced, Category = NDisplay, meta = (DisplayThumbnail = false, HideProperty))`
- L496 _public member_ `TMap<FString, TObjectPtr<UDisplayClusterConfigurationHostDisplayData>> HostDisplayData;` — `UPROPERTY(Instanced)`
- L502 _public prototype_ `virtual void PostLoad() override;`
- L506 _protected prototype_ `virtual void GetObjectsToExport(TArray<UObject*>& OutObjects) override;`
- L511 _public prototype_ `void GetReferencedMeshNames(TArray<FString>& OutMeshNames) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Return all references to meshes from policy, and other
- L515 _public prototype_ `void GetNodeIds(TArray<FString>& OutNodeIds) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Nodes API
- L518 _public prototype_ `UDisplayClusterConfigurationClusterNode* GetNode(const FString& NodeId) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")`

#### struct `FDisplayClusterConfigurationDiagnostics`  
`struct FDisplayClusterConfigurationDiagnostics`  
_L522-535_
- reflection: `USTRUCT(Blueprintable)`
- L528 _public member_ `bool bSimulateLag = false;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L531 _public member_ `float MinLagTime = 0.01f;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`
- L534 _public member_ `float MaxLagTime = 0.3f;` — `UPROPERTY(EditAnywhere, Category = NDisplay)`

#### struct `FDisplayClusterConfigurationDataMetaInfo`  
`struct FDisplayClusterConfigurationDataMetaInfo`  
_L537-541_
- L539 _public member_ `EDisplayClusterConfigurationDataSource ImportDataSource;`
- L540 _public member_ `FString ImportFilePath;`

#### class `UDisplayClusterConfigurationData`  
`class UDisplayClusterConfigurationData : public UDisplayClusterConfigurationData_Base`  
_L546-677_
- reflection: `UCLASS(Blueprintable, BlueprintType, PerObjectConfig, config = EditorPerProjectUserSettings)`
- inherits: `UDisplayClusterConfigurationData_Base`
- desc: Main configuration data container
- L552 _public prototype_ `UDisplayClusterConfigurationData();`
- L558 _public prototype_ `UDisplayClusterConfigurationClusterNode* GetPrimaryNode() const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Returns primary node configuration. Otherwise nullptr.
- L562 _public prototype_ `UDisplayClusterConfigurationClusterNode* GetNode(const FString& NodeId) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Returns specific node configuration. Otherwise nullptr.
- L566 _public prototype_ `UDisplayClusterConfigurationViewport* GetViewport(const FString& NodeId, const FString& ViewportId) const;` — `UFUNCTION(BlueprintPure, Category = "NDisplay|Configuration")` — Viewports API
- L569 _public prototype_ `void ForEachViewport(const TFunction<void(const TObjectPtr<UDisplayClusterConfigurationViewport>&)>& Function) const;` — Execute a function on each viewport in each cluster node
- L582 _public prototype_ `bool AssignPostprocess(const FString& NodeId, const FString& PostprocessId, const FString& Type, TMap<FString, FString> Parameters, int32 Order = -1);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Configuration")` — Update\Create node postprocess @param PostprocessId - Unique postprocess name @param Type          - Postprocess type id @param Parameters    - Postprocess parameters @param Order         - Control the rendering order of post-processing. Larger value is displayed last @return - true, if success
- L585 _public prototype_ `bool RemovePostprocess(const FString& NodeId, const FString& PostprocessId);` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Configuration")`
- L588 _public prototype_ `bool GetPostprocess(const FString& NodeId, const FString& PostprocessId, FDisplayClusterConfigurationPostprocess& OutPostprocess) const;` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Configuration")`
- L591 _public prototype_ `bool GetProjectionPolicy(const FString& NodeId, const FString& ViewportId, FDisplayClusterConfigurationProjection& OutProjection) const;` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Configuration")`
- L595 _public prototype_ `void GetReferencedMeshNames(TArray<FString>& OutMeshNames) const;` — `UFUNCTION(BlueprintCallable, Category = "NDisplay|Configuration")` — Return all references to meshes from policy, and other
- L599 _public prototype_ `uint32 GetNumberOfClusterNodes() const;` — Returns number of nodes in current cluster
- L602 _public prototype_ `FString GetPrimaryNodeAddress() const;` — Returns primary node IP address of current cluster
- L605 _public member_ `FDisplayClusterConfigurationDataMetaInfo Meta;`
- L608 _public member_ `FDisplayClusterConfigurationInfo Info;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayAfter = "RenderFrameSettings"))`
- L611 _public member_ `TObjectPtr<UDisplayClusterConfigurationScene> Scene;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = NDisplay, meta = (HideProperty))`
- L614 _public member_ `TObjectPtr<UDisplayClusterConfigurationCluster> Cluster;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = NDisplay)`
- L617 _public member_ `TMap<FString, FString> CustomParameters;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayAfter = "Diagnostics"))`
- L620 _public member_ `FDisplayClusterConfigurationDiagnostics Diagnostics;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayAfter = "Info"))`
- L623 _public member_ `FDisplayClusterConfigurationRenderFrame RenderFrameSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Configuration, meta = (HidePropertyInstanceOnly, DisplayAfter = "DefaultFrameSizeRef"))`
- L626 _public member_ `FDisplayClusterConfigurationICVFX_StageSettings StageSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (HideProperty))`
- L629 _public member_ `bool bFollowLocalPlayerCamera = false;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Follow Local Player Camera", DisplayAfter = "CustomParameters"))`
- L632 _public member_ `bool bExitOnEsc = true;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Exit When ESC Pressed", DisplayAfter = "bFollowLocalPlayerCamera"))`
- L635 _public member_ `bool bOverrideViewportsFromExternalConfig = false;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Override Viewports From .ndisplay", DisplayAfter = "bExitOnEsc"))`
- L638 _public member_ `bool bOverrideTransformsFromExternalConfig = false;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Override Transforms From .ndisplay", DisplayAfter = "bOverrideViewportsFromExternalConfig"))`
- L641 _public member_ `FDisplayClusterConfigurationGlobalMediaSettings MediaSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Global Media Settings"))`
- L644 _public prototype_ `static UDisplayClusterConfigurationData* CreateNewConfigData(UObject* Owner = nullptr, EObjectFlags ObjectFlags = RF_NoFlags);` — Create empty config data.
- L649 _public member_ `FString PathToConfig;` — `UPROPERTY(config)`
- L653 _public member_ `FString ImportedPath;` — `UPROPERTY()` — The path used when originally importing.
- L656 _public member_ `const static TSet<FString> RenderSyncPolicies;`
- L658 _public member_ `const static TSet<FString> InputSyncPolicies;`
- L660 _public member_ `const static TSet<FString> ProjectionPolicies;`
- L667 _private member_ `FDisplayClusterEditorPropertyReference DefaultFrameSizeRef;` — `UPROPERTY(EditDefaultsOnly, Transient, Category = Configuration, meta = (PropertyPath = "StageSettings.DefaultFrameSize"))`
- L674 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;` — UObject interface

#### Free symbols / members of external scopes

- L316 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`
- L422 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_AutoExposure.h` (Public)


#### struct `FDisplayClusterConfiguration_AutoExposureMeteringSettings`  
`struct FDisplayClusterConfiguration_AutoExposureMeteringSettings`  
_L15-40_
- reflection: `USTRUCT(Blueprintable)`
- L25 _public member_ `TArray<FString> Viewports;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Viewports"))` — List of allowed outer viewports for auto-exposure metering when the override is enabled. If no viewports are specified, all outer viewports are used for metering.
- L32 _public member_ `TArray<FString> ICVFXCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "ICVFX Cameras"))` — List of allowed ICVFX cameras for auto-exposure metering when the override is enabled. If no ICVFX cameras are specified, all ICVFX cameras are used for metering.
- L39 _public member_ `TArray<FString> Nodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Nodes"))` — List of allowed cluster nodes for auto-exposure metering when the override is enabled. If no nodes are specified, all cluster nodes can be used for metering.

#### struct `FDisplayClusterConfiguration_AutoExposureExcludeSettings`  
`struct FDisplayClusterConfiguration_AutoExposureExcludeSettings`  
_L43-59_
- reflection: `USTRUCT(Blueprintable)`
- L50 _public member_ `TArray<FString> Viewports;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Viewports"))` — Outer viewports excluded from nDisplay auto-exposure (they use the default exposure behavior).
- L54 _public member_ `TArray<FString> ICVFXCameras;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "ICVFX Cameras"))` — ICVFX cameras excluded from nDisplay auto-exposure (they use the default exposure behavior).
- L58 _public member_ `TArray<FString> Nodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Nodes"))` — Cluster nodes excluded from nDisplay auto-exposure (they use the default exposure behavior).

#### struct `FDisplayClusterConfiguration_AutoExposureSettings`  
`struct FDisplayClusterConfiguration_AutoExposureSettings`  
_L62-82_
- reflection: `USTRUCT(Blueprintable)`
- L69 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Enable Auto Exposure Override"))` — Enable/disable AutoExposure override.
- L75 _public member_ `FDisplayClusterConfiguration_AutoExposureMeteringSettings MeteringSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Meter Auto Exposure on Items"))` — Metering settings for auto-exposure metering when the override is enabled.
- L81 _public member_ `FDisplayClusterConfiguration_AutoExposureExcludeSettings ExcludeSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Exclude Items from Auto Exposure"))` — Exclude settings for auto-exposure.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Base.h` (Public)


#### struct `FTextureCropOrigin`  
`struct FTextureCropOrigin`  
_L16-28_
- reflection: `USTRUCT(Blueprintable)`
- desc: Texture Replace Crop Origin parameter container
- L23 _public member_ `int32 X = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "X"))` — Replace texture origin X location, in pixels
- L27 _public member_ `int32 Y = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Y"))` — Replace texture origin Y position, in pixels

#### struct `FTextureCropSize`  
`struct FTextureCropSize`  
_L34-46_
- reflection: `USTRUCT(Blueprintable)`
- desc: Texture Replace Crop Size parameter container
- L41 _public member_ `int32 W = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "W"))` — Replace texture crop width, in pixels
- L45 _public member_ `int32 H = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "H"))` — Replace texture crop height, in pixels

#### struct `FDisplayClusterReplaceTextureCropRectangle`  
`struct FDisplayClusterReplaceTextureCropRectangle`  
_L52-67_
- reflection: `USTRUCT(Blueprintable)`
- desc: Texture Replace Crop parameters container
- L57 _public prototype_ `FIntRect ToRect() const;`
- L62 _public member_ `FTextureCropOrigin Origin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Texture Crop Origin"))` — Texture Crop Origin
- L66 _public member_ `FTextureCropSize Size;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Texture Crop Size"))` — Texture Crop Size

#### struct `FDisplayClusterConfigurationRectangle`  
`struct FDisplayClusterConfigurationRectangle`  
_L73-100_
- reflection: `USTRUCT(Blueprintable)`
- desc: All configuration UObjects should inherit from this class.
- L78 _public function_ `FDisplayClusterConfigurationRectangle() : X(0), Y(0), W(0), H(0)`
- L82 _public function_ `FDisplayClusterConfigurationRectangle(int32 _X, int32 _Y, int32 _W, int32 _H) : X(_X), Y(_Y), W(_W), H(_H)`
- L86 _public prototype_ `FIntRect ToRect() const;`
- L90 _public member_ `int32 X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`
- L93 _public member_ `int32 Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`
- L96 _public member_ `int32 W;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`
- L99 _public member_ `int32 H;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`

#### class `UDisplayClusterConfigurationData_Base`  
`class UDisplayClusterConfigurationData_Base : public UObject`  
_L106-137_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: All configuration UObjects should inherit from this class.
- L113 _public function_ `static FName GetExportedObjectsMemberName()`
- L119 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L127 _protected function_ `virtual void OnPreCompile(class FCompilerResultsLog& MessageLog)` — Called by nDisplay compiler prior to compilation.
- L132 _protected function_ `virtual void GetObjectsToExport(TArray<UObject*>& OutObjects)` — Called before saving to collect objects which should be exported as a sub object block.
- L136 _private member_ `TArray<TObjectPtr<UObject>> ExportedObjects;` — `UPROPERTY(Export)`

#### struct `FDisplayClusterConfigurationPolymorphicEntity`  
`struct FDisplayClusterConfigurationPolymorphicEntity`  
_L140-166_
- reflection: `USTRUCT(Blueprintable)`
- L147 _public member_ `FString Type;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NDisplay)` — Polymorphic entity type
- L151 _public member_ `TMap<FString, FString> Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NDisplay)` — Generic parameters map
- L164 _public member_ `bool bIsCustom = false;` — `UPROPERTY(EditAnywhere, Category = NDisplay)` — When a custom policy is selected from the details panel. This is needed in the event a custom policy is selected but the custom type is a default policy. This allows users to further customize default policies if necessary. EditAnywhere is required so we can manipulate the property through a handle. Details will hide it from showing.

#### struct `FDisplayClusterConfigurationProjection`  
`struct FDisplayClusterConfigurationProjection : public FDisplayClusterConfigurationPolymorphicEntity`  
_L169-181_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationPolymorphicEntity`
- L175 _public prototype_ `FDisplayClusterConfigurationProjection();`
- L180 _public prototype_ `bool ShouldDisplayICVFXCategory() const;` — The ICVFX properties of the viewport will only be displayed in the UI if this function returns true.

#### struct `FDisplayClusterConfigurationPostprocess`  
`struct FDisplayClusterConfigurationPostprocess : public FDisplayClusterConfigurationPolymorphicEntity`  
_L184-193_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationPolymorphicEntity`
- L192 _public member_ `int32 Order = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NDisplay)` — Control postprocess rendering order. Bigger value rendered last

#### struct `FDisplayClusterConfigurationClusterItemReferenceList`  
`struct FDisplayClusterConfigurationClusterItemReferenceList`  
_L196-203_
- reflection: `USTRUCT(BlueprintType)`
- L202 _public member_ `TArray<FString> ItemNames;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NDisplay)`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Enums.h` (Public)


#### enum `EDisplayClusterConfigurationDataSource`  
`enum class EDisplayClusterConfigurationDataSource : uint8`  
_L14-18_
- reflection: `UENUM()`
- L16 _public enumerator_ `Text UMETA(DisplayName = "Text file")`
- L17 _public enumerator_ `Json UMETA(DisplayName = "JSON file")`

#### enum `EDisplayClusterConfigurationFailoverPolicy`  
`enum class UE_DEPRECATED(5.6, "Removed as unnecessary in the new failover implementation") EDisplayClusterConfigurationFailoverPolicy : uint8`  
_L21-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled")` — No failover operations performed. The whole cluster gets terminated in case of any error
- L28 _public enumerator_ `DropSecondaryNodesOnly UMETA(DisplayName = "Drop S-node on fail")` — This policy allows to drop any secondary node out of cluster in case it's failed, and let the others continue working. However, the whole cluster will be terminated if primary node fails.

#### enum `EDisplayClusterConfigurationEyeStereoOffset`  
`enum class EDisplayClusterConfigurationEyeStereoOffset : uint8`  
_L32-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `None UMETA(DisplayName = "No offset")`
- L35 _public enumerator_ `Left UMETA(DisplayName = "Left eye of a stereo pair")`
- L36 _public enumerator_ `Right UMETA(DisplayName = "Right eye of a stereo pair")`

#### enum `EDisplayClusterConfiguration_PostRenderBlur`  
`enum class EDisplayClusterConfiguration_PostRenderBlur : uint8`  
_L40-50_
- reflection: `UENUM()`
- L43 _public enumerator_ `None UMETA(DisplayName = "None")` — Not use blur postprocess
- L46 _public enumerator_ `Gaussian UMETA(DisplayName = "Gaussian")` — Blur viewport using Gaussian method
- L49 _public enumerator_ `Dilate UMETA(DisplayName = "Dilate")` — Blur viewport using Dilate method

#### enum `EDisplayClusterConfigurationICVFX_ChromakeyType`  
`enum class EDisplayClusterConfigurationICVFX_ChromakeyType : uint8`  
_L54-68_
- reflection: `UENUM()`
- desc: Indicates the type of chromakey that is used within an ICVFX camera's inner frustum
- L57 _public enumerator_ `InnerFrustum UMETA(DisplayName = "Inner Frustum")` — The entire inner frustum is rendered as chromakey
- L60 _public enumerator_ `CustomChromakey UMETA(DisplayName = "Custom Chromakey")` — Only actors specified in the custom chromakey actor list are rendered as chromakey
- L67 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled")` — Disable chromakey. This value can be overridden by the viewport ICVFX settings, by changing the ‘Override Chromakey Type’ property.

#### enum `EDisplayClusterConfigurationICVFX_ChromakeySettingsSource`  
`enum class EDisplayClusterConfigurationICVFX_ChromakeySettingsSource : uint8`  
_L72-79_
- reflection: `UENUM()`
- desc: Indicates the source of the chromakey settings when an ICVFX camera's inner frustum is rendered as chromakey
- L75 _public enumerator_ `Viewport UMETA(DisplayName = "Use nDisplay Viewport Chromakey")` — The nDisplay stage actor's chromakey settings are used
- L78 _public enumerator_ `ICVFXCamera UMETA(DisplayName = "Use ICVFX Camera Chromakey")` — The ICVFX camera's chromakey settings are used

#### enum `EDisplayClusterConfigurationICVFX_ChromakeySource`  
`enum class EDisplayClusterConfigurationICVFX_ChromakeySource : uint8`  
_L82-92_
- reflection: `UENUM()`
- L85 _public enumerator_ `None UMETA(DisplayName = "None")` — Disable chromakey rendering
- L88 _public enumerator_ `FrameColor UMETA(DisplayName = "Chromakey Color")` — Fill whole camera frame with chromakey color
- L91 _public enumerator_ `ChromakeyRenderTexture UMETA(DisplayName = "Chromakey Render Texture")` — Capture to texture RTT from scene layers

#### enum `EDisplayClusterConfigurationICVFX_LightcardRenderMode`  
`enum class EDisplayClusterConfigurationICVFX_LightcardRenderMode : uint8`  
_L96-103_
- reflection: `UENUM()`
- desc: How to render Light Cards in relation to the inner frustum.
- L99 _public enumerator_ `Over UMETA(DisplayName = "Lightcard Over Frustum")` — Render Light Cards over the inner frustum.  Light Cards can be directly visible in camera.
- L102 _public enumerator_ `Under UMETA(DisplayName = "Lightcard Under Frustum")` — Render Light Cards under the inner frustum. Light Cards will not be directly visible in camera.

#### enum `EDisplayClusterConfigurationICVFX_PerLightcardRenderMode`  
`enum class EDisplayClusterConfigurationICVFX_PerLightcardRenderMode : uint8`  
_L107-117_
- reflection: `UENUM()`
- desc: How to render a Light Card Actor in relation to the inner frustum.
- L110 _public enumerator_ `Default UMETA(DisplayName = "Default")` — It is determined by nDisplay settings.
- L113 _public enumerator_ `Over UMETA(DisplayName = "Lightcard Over Frustum")` — Render Light Card Actor over the inner frustum.  Light Card Actor can be directly visible in camera.
- L116 _public enumerator_ `Under UMETA(DisplayName = "Lightcard Under Frustum")` — Render Light Card Actor under the inner frustum. Light Card Actor will not be directly visible in camera.

#### enum `EDisplayClusterConfigurationICVFX_OverrideLightcardRenderMode`  
`enum class EDisplayClusterConfigurationICVFX_OverrideLightcardRenderMode : uint8`  
_L121-134_
- reflection: `UENUM()`
- desc: Override the lightcard rendering order for the viewport.
- L124 _public enumerator_ `Default UMETA(DisplayName = "Default")` — Use global lightcard mode from StageSettings for this viewport
- L127 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled")` — Disable lightcard rendering for this viewport
- L130 _public enumerator_ `Over UMETA(DisplayName = "Lightcard Over Frustum")` — Always render the In-Camera frame over lightcards for this viewport.
- L133 _public enumerator_ `Under UMETA(DisplayName = "Lightcard Under Frustum")` — Always render the In-Camera frame under lightcards for this viewport.

#### enum `EDisplayClusterConfigurationICVFX_OverrideChromakeyType`  
`enum class EDisplayClusterConfigurationICVFX_OverrideChromakeyType : uint8`  
_L138-151_
- reflection: `UENUM()`
- desc: Override the chromakey type for the viewport.
- L141 _public enumerator_ `Default UMETA(DisplayName = "Default")` — Use the chromakey type from ICVFX camera
- L144 _public enumerator_ `InnerFrustum UMETA(DisplayName = "Inner Frustum")` — The entire inner frustum is rendered as chromakey for this viewport
- L147 _public enumerator_ `CustomChromakey UMETA(DisplayName = "Custom Chromakey")` — Only actors specified in the custom chromakey actor list are rendered as chromakey
- L150 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled Chromakey")` — Disable chromakey

#### enum `EDisplayClusterConfigurationICVFX_OverrideCameraRenderMode`  
`enum class EDisplayClusterConfigurationICVFX_OverrideCameraRenderMode : uint8`  
_L154-167_
- reflection: `UENUM()`
- L157 _public enumerator_ `Default UMETA(DisplayName = "Default")` — Use default rendering rules
- L160 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled")` — Disable camera frame render for this viewport
- L163 _public enumerator_ `DisableChromakey UMETA(DisplayName = "Disabled Chromakey")` — Disable chromakey render for this viewport
- L166 _public enumerator_ `DisableChromakeyMarkers UMETA(DisplayName = "Disabled Markers")` — Disable chromakey markers render for this viewport

#### enum `EDisplayClusterConfigurationViewport_StereoMode`  
`enum class EDisplayClusterConfigurationViewport_StereoMode : uint8`  
_L170-177_
- reflection: `UENUM()`
- L173 _public enumerator_ `Default UMETA(DisplayName = "Default")` — Render incamera frame over lightcard
- L176 _public enumerator_ `ForceMono UMETA(DisplayName = "Force Mono")` — Force monoscopic render mode for this viewport (performance)

#### enum `EDisplayClusterConfigurationRenderFamilyMode`  
`enum class EDisplayClusterConfigurationRenderFamilyMode : uint8`  
_L180-193_
- reflection: `UENUM()`
- L183 _public enumerator_ `None UMETA(DisplayName = "Disabled")` — Render all viewports to unique RenderTargets
- L186 _public enumerator_ `AllowMergeForGroups UMETA(DisplayName = "Groups")` — Merge views by ViewFamilyGroupNum
- L189 _public enumerator_ `AllowMergeForGroupsAndStereo UMETA(DisplayName = "GroupsAndStereo")` — Merge views by ViewFamilyGroupNum and stereo
- L192 _public enumerator_ `MergeAnyPossible UMETA(DisplayName = "AnyPossible")` — Use rules to merge views to minimal num of families (separate by: buffer_ratio, viewExtension, max RTT size)

#### enum `EDisplayClusterConfigurationCameraMotionBlurMode`  
`enum class EDisplayClusterConfigurationCameraMotionBlurMode : uint8`  
_L196-206_
- reflection: `UENUM()`
- L199 _public enumerator_ `Off UMETA(DisplayName = "All Camera Blur Off")` — Subtract blur due to all global motion of the ICVFX camera, but preserve blur from object motion.
- L202 _public enumerator_ `On UMETA(DisplayName = "ICVFX Camera Blur On")` — Allow blur from camera motion. This option should not normally be used for shooting, but may be useful for diagnostic purposes.
- L205 _public enumerator_ `Override UMETA(DisplayName = "ICVFX Camera Blur Off")` — Subtract blur due to motion of the ICVFX camera relative to the nDisplay root, but preserve blur from both object motion and movement of the nDisplay root, which can be animated to represent vehicular motion through an environment.

#### enum `EDisplayClusterConfigurationViewportOverscanMode`  
`enum class EDisplayClusterConfigurationViewportOverscanMode : uint8`  
_L209-213_
- reflection: `UENUM()`
- L211 _public enumerator_ `Pixels UMETA(DisplayName = "Pixels")`
- L212 _public enumerator_ `Percent UMETA(DisplayName = "Percent")`

#### enum `EDisplayClusterConfigurationViewportOverscanBlendMode`  
`enum class EDisplayClusterConfigurationViewportOverscanBlendMode : uint8`  
_L221-234_
- reflection: `UENUM()`
- desc: Defines how the overscan blend width is interpreted. Allows blending between tiles to be specified in a percentage of the overscan size, or disabled entirely.
- L224 _public enumerator_ `Disable UMETA(DisplayName = "Disable")` — Disable blending across overscan region
- L227 _public enumerator_ `Percent25 UMETA(DisplayName = "25%")` — Blend width defined as 25% of the overscan size
- L230 _public enumerator_ `Percent50 UMETA(DisplayName = "50%")` — Blend width defined as 50% of the overscan size
- L233 _public enumerator_ `Percent75 UMETA(DisplayName = "75%")` — Blend width defined as 75% of the overscan size

#### enum `EDisplayClusterConfigurationRenderMode`  
`enum class EDisplayClusterConfigurationRenderMode : uint8`  
_L238-243_
- reflection: `UENUM()`
- L240 _public enumerator_ `Mono UMETA(DisplayName = "Mono")`
- L241 _public enumerator_ `SideBySide UMETA(DisplayName = "Stereo: Side By Side")`
- L242 _public enumerator_ `TopBottom UMETA(DisplayName = "Stereo: Top Bottom")`

#### enum `EDisplayClusterConfigurationViewportCustomFrustumMode`  
`enum class EDisplayClusterConfigurationViewportCustomFrustumMode : uint8`  
_L246-250_
- reflection: `UENUM()`
- L248 _public enumerator_ `Percent UMETA(DisplayName = "Percentage")`
- L249 _public enumerator_ `Pixels UMETA(DisplayName = "Pixels")`

#### enum `EDisplayClusterConfigurationViewportLightcardOCIOMode`  
`enum class EDisplayClusterConfigurationViewportLightcardOCIOMode : uint8`  
_L253-263_
- reflection: `UENUM()`
- L256 _public enumerator_ `nDisplay UMETA(DisplayName = "Use nDisplay Viewport OCIO")` — Use nDisplay Viewport OCIO.
- L259 _public enumerator_ `Custom UMETA(DisplayName = "Use Custom Light Cards OCIO")` — Use Custom Light Cards OCIO.
- L262 _public enumerator_ `None UMETA(DisplayName = "None")` — None.

#### enum `EDisplayClusterConfigurationRootActorPreviewSettingsSource`  
`enum class EDisplayClusterConfigurationRootActorPreviewSettingsSource : uint8`  
_L267-275_
- reflection: `UENUM()`
- desc: Determines where the data for RootActor GetPreviewSettings() will come from:
- L270 _public enumerator_ `RootActor` — The preview settings will be obtained from the RootActor properties.
- L274 _public enumerator_ `Configuration` — The preview settings will be retrieved from DC ViewportManagerConfiguration. This option is used when the preview settings need to be customized in a different way, but not to change the RootActor properties.

#### enum `EDisplayClusterConfigurationUpscalingMethod`  
`enum class EDisplayClusterConfigurationUpscalingMethod : uint8`  
_L282-301_
- reflection: `UENUM()`
- desc: Determines Upscaling method. Not used as an enum in the UI. Used in the FDisplayClusterConfigurationUpscalerSettingsDetailCustomization.
- L285 _public enumerator_ `Default = 0 UMETA(DisplayName = "Default")` — Use configuration project settings.
- L288 _public enumerator_ `Disable UMETA(DisplayName = "Disable")` — No Antialiasing.
- L291 _public enumerator_ `FXAA UMETA(DisplayName = "Fast Approximate Anti-Aliasing (FXAA)")` — Fast Approximate Anti-Aliasing.
- L294 _public enumerator_ `MSAA UMETA(DisplayName = "Multisample Anti-Aliasing (MSAA)")` — Multisample Anti-Aliasing. (Only supported with forward shading.)
- L297 _public enumerator_ `TAA UMETA(DisplayName = "Temporal Anti-Aliasing (TAA)")` — Temporal Anti-Aliasing.
- L300 _public enumerator_ `TSR UMETA(DisplayName = "Temporal Super-Resolution (TSR)")` — Temporal Super-Resolution. Use TSR upscaler with built-in AntiAliasing.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_ICVFX.h` (Public)


#### struct `FDisplayClusterConfigurationICVFX_LightcardCustomOCIO`  
`struct FDisplayClusterConfigurationICVFX_LightcardCustomOCIO`  
_L31-47_
- reflection: `USTRUCT(Blueprintable)`
- L37 _public prototype_ `const FOpenColorIOColorConversionSettings* FindOCIOConfiguration(const FString& InViewportId) const;` — Return LightCard OCIO configuration for the specified viewport. Return nullptr if no OCIO.
- L42 _public member_ `FDisplayClusterConfigurationOCIOConfiguration AllViewportsOCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Card", meta = (DisplayName = "All Viewports Color Configuration", ConfigurationMode = "Viewports"))` — Apply this OpenColorIO configuration to all viewports.
- L46 _public member_ `TArray<FDisplayClusterConfigurationOCIOProfile> PerViewportOCIOProfiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Card", meta = (DisplayName = "Per-Viewport OCIO Overrides", ConfigurationMode = "Viewports"))` — Apply an OpenColorIO configuration on a per-viewport or group-of-viewports basis.

#### struct `FDisplayClusterConfigurationICVFX_ViewportOCIO`  
`struct FDisplayClusterConfigurationICVFX_ViewportOCIO`  
_L50-66_
- reflection: `USTRUCT(Blueprintable)`
- L56 _public prototype_ `const FOpenColorIOColorConversionSettings* FindOCIOConfiguration(const FString& InViewportId) const;` — Return OCIO configuration for the specified viewport. Return nullptr if no OCIO.
- L61 _public member_ `FDisplayClusterConfigurationOCIOConfiguration AllViewportsOCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "All Viewports Color Configuration", ConfigurationMode = "Viewports"))` — Apply this OpenColorIO configuration to all viewports.
- L65 _public member_ `TArray<FDisplayClusterConfigurationOCIOProfile> PerViewportOCIOProfiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "Per-Viewport OCIO Overrides", ConfigurationMode = "Viewports"))` — Apply an OpenColorIO configuration on a per-viewport or group-of-viewports basis.

#### struct `FDisplayClusterConfigurationICVFX_CameraOCIO`  
`struct FDisplayClusterConfigurationICVFX_CameraOCIO`  
_L69-91_
- reflection: `USTRUCT(Blueprintable)`
- L75 _public prototype_ `const FOpenColorIOColorConversionSettings* FindOCIOConfiguration(const FString& InClusterNodeId) const;` — Return InCamera OCIO configuration for the specified cluster node. Return nullptr if no OCIO.
- L78 _public prototype_ `bool IsInnerFrustumViewportSettingsEqual(const FString& InClusterNodeId1, const FString& InClusterNodeId2) const;` — Returns true if the InCamera OCIO configuration is the same for the input nodes.
- L81 _public prototype_ `bool IsChromakeyViewportSettingsEqual(const FString& InClusterNodeId1, const FString& InClusterNodeId2) const;` — Returns true if the Chromakey OCIO configuration is the same for the input nodes.
- L86 _public member_ `FDisplayClusterConfigurationOCIOConfiguration AllNodesOCIOConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "All Nodes Color Configuration", ConfigurationMode = "ClusterNodes"))` — OCIO Display look configuration for all nodes
- L90 _public member_ `TArray<FDisplayClusterConfigurationOCIOProfile> PerNodeOCIOProfiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "Per-Node OCIO Overrides", ConfigurationMode = "ClusterNodes"))` — Apply an OpenColorIO configuration on a per-node or group-of-nodes basis.

#### struct `FDisplayClusterConfigurationICVFX_LightcardOCIO`  
`struct FDisplayClusterConfigurationICVFX_LightcardOCIO`  
_L94-110_
- reflection: `USTRUCT(Blueprintable)`
- L100 _public prototype_ `const FOpenColorIOColorConversionSettings* FindOCIOConfiguration(const FString& InViewportId, const FDisplayClusterConfigurationICVFX_ViewportOCIO& InViewportOCIO) const;` — Return LightCard OCIO configuration for the specified viewport. Return nullptr if no OCIO.
- L105 _public member_ `EDisplayClusterConfigurationViewportLightcardOCIOMode LightcardOCIOMode = EDisplayClusterConfigurationViewportLightcardOCIOMode::nDisplay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Card|OCIO", meta = (DisplayName = "Light Cards OCIO"))` — Light Cards OCIO mode.
- L109 _public member_ `FDisplayClusterConfigurationICVFX_LightcardCustomOCIO CustomOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Card|OCIO", meta = (DisplayName = "Custom Light Cards OCIO"))` — Custom OpenColorIO configuration for Light Cards.

#### struct `FDisplayClusterConfigurationICVFX_VisibilityList`  
`struct FDisplayClusterConfigurationICVFX_VisibilityList`  
_L113-138_
- reflection: `USTRUCT(Blueprintable, meta = (DefaultSubstitutions = "LayersTooltip = Actor Layers, ActorsTooltip = Actor references"))`
- L119 _public prototype_ `bool IsVisibilityListValid() const;` — returns true if there is at least one valid value in the visibility list.
- L126 _public member_ `TArray<FActorLayer> ActorLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Layers"))` — Actor layers. Warning: This option has a very expensive performance cost, especially on big projects.
- L130 _public member_ `TArray<TSoftObjectPtr<AActor>> Actors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ToolTip = "{ActorsTooltip}"))` — Actor references
- L134 _public member_ `TArray<FString> RootActorComponentNames;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NDisplay)` — Reference to RootActor components by names
- L137 _public member_ `TArray<TSoftObjectPtr<AActor>> AutoAddedActors;` — Actors added automatically during a session

#### struct `FDisplayClusterConfigurationICVFX_CustomSize`  
`struct FDisplayClusterConfigurationICVFX_CustomSize`  
_L142-168_
- reflection: `USTRUCT(Blueprintable)`
- desc: Custom resolution settings for ICVFX.
- L149 _public member_ `bool bUseCustomSize = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Use Custom Resolution"))` — Enabling this option will allow these custom settings to be used instead of the default settings.
- L153 _public member_ `int CustomWidth = 2560;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Custom Width", ClampMin = "32", UIMin = "32", EditCondition = "bUseCustomSize"))` — Custom Width, in pixels.
- L157 _public member_ `int CustomHeight = 1440;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Custom Height", ClampMin = "32", UIMin = "32", EditCondition = "bUseCustomSize"))` — Custom Height, in pixels.
- L167 _public member_ `bool bAdaptSize = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Adapt Resolution to Match Filmback Aspect Ratio", EditCondition = "bUseCustomSize"))` — Automatically adapts resolution to be proportional to the filmback aspect ratio for the ICVFX Camera while continuing to render the same total amount of pixels as specified by the size. Enabling this can help avoid visual artifacts without affecting the performance budget.

#### struct `FDisplayClusterConfigurationICVFX_Size`  
`struct FDisplayClusterConfigurationICVFX_Size`  
_L172-194_
- reflection: `USTRUCT(Blueprintable)`
- desc: Default resolution settings for ICVFX.
- L179 _public member_ `int Width = 2560;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Default Width", ClampMin = "32", UIMin = "32"))` — The default width of In-Cameras, in pixels.
- L183 _public member_ `int Height = 1440;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Default Height", ClampMin = "32", UIMin = "32"))` — The default height of In-Cameras, in pixels.
- L193 _public member_ `bool bAdaptSize = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Adapt Resolution to Match Filmback Aspect Ratio"))` — Automatically adapts the default frame resolution to be proportional to the filmback aspect ratio for the ICVFX Camera while continuing to render the same total amount of pixels as specified by the size. Enabling this can help avoid visual artifacts without affecting the performance budget.

#### struct `FDisplayClusterConfigurationICVFX_OverlayAdvancedRenderSettings`  
`struct FDisplayClusterConfigurationICVFX_OverlayAdvancedRenderSettings`  
_L197-236_
- reflection: `USTRUCT(Blueprintable)`
- L204 _public member_ `float BufferRatio = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.05", UIMin = "0.05", ClampMax = "10.0", UIMax = "10.0"))` — Allow ScreenPercentage
- L208 _public member_ `float RenderTargetRatio = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.01", UIMin = "0.01", ClampMax = "1.0", UIMax = "1.0"))` — Performance: Render to scale RTT, resolved with shader to viewport (Custom value)
- L218 _public member_ `int GPUIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the ICVFX viewport (LC or CK). A value of '-1' means using the same GPU index as defined in the base viewport: - The In-Camera viewport is used as the base viewport for the Chromakey (CK) viewport. - An outer viewport is used as the base viewport for the Light Card (LC) viewport. Used to improve rendering performance by spreading the load across multiple GPUs.
- L226 _public member_ `int StereoGPUIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Stereo GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the ICVFX viewport (LC or CK) in stereo rendering for the second eye. A value of '-1' means to use the value from the GPU Index parameter. (the same value is used for both eyes). Used to improve rendering performance by spreading the load across multiple GPUs.
- L230 _public member_ `EDisplayClusterConfigurationViewport_StereoMode StereoMode = EDisplayClusterConfigurationViewport_StereoMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Performance: force monoscopic render, resolved to stereo viewport
- L235 _public member_ `int RenderFamilyGroup = -1;` — `UPROPERTY()` — Experimental: Support special frame builder mode - merge viewports to single viewfamily by group num [not implemented yet]

#### struct `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings`  
`struct FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings`  
_L239-295_
- reflection: `USTRUCT(Blueprintable)`
- L246 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L247 _public prototype_ `~FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings() = default;`
- L248 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings(const FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings&) = default;`
- L249 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings(FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings&&) = default;`
- L250 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings& operator=(const FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings&) = default;`
- L251 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings& operator=(FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings&&) = default;`
- L256 _public prototype_ `bool ShouldUseChromakeyViewport(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — true if chromakey viewport is used in  ICVFX.
- L262 _public member_ `bool bEnable_DEPRECATED = false;` — `UE_DEPRECATED(5.3, "Use the ChromakeyType enum in FDisplayClusterConfigurationICVFX_ChromakeySettings instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the Chromakey Type enum in the chromakey settings instead"))` — Set to True to use custom chromakey content.
- L266 _public member_ `bool bReplaceCameraViewport = false;` — `UPROPERTY(BlueprintReadWrite,Category = NDisplay)` — Replace the texture of the camera viewport from this chromakey RTT
- L271 _public member_ `FDisplayClusterConfigurationICVFX_CustomSize CustomSize_DEPRECATED;` — `UE_DEPRECATED(5.5, "Use the 'ChromakeySizeMult' instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the 'Chromakey Resolution Multiplier' instead"))` — Custom resolution of the chromakey RTT. If it is not used, the Default Frame Resolution value is used by default.
- L275 _public member_ `float ChromakeySizeMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Chromakey Resolution Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "1.0", UIMax = "1.0"))` — Resolution multiplier for RTT chromakey. The default is the ICVFX camera frame resolution.
- L279 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList ShowOnlyList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Custom Chromakey Content"))` — Content specified here will be overridden to use the chromakey color specified and include chromakey markers if enabled.
- L283 _public member_ `FDisplayClusterConfigurationPostRender_Override Replace;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay)` — Replace viewport render from source texture
- L287 _public member_ `FDisplayClusterConfigurationPostRender_BlurPostprocess PostprocessBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Post Process Blur"))` — Apply blur to the Custom Chromakey content.
- L290 _public member_ `FDisplayClusterConfigurationPostRender_GenerateMips GenerateMips;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay)`
- L294 _public member_ `FDisplayClusterConfigurationICVFX_OverlayAdvancedRenderSettings AdvancedRenderSettings;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay)` — Advanced render settings

#### struct `FDisplayClusterConfigurationICVFX_ChromakeyMarkers`  
`struct FDisplayClusterConfigurationICVFX_ChromakeyMarkers`  
_L298-329_
- reflection: `USTRUCT(Blueprintable)`
- L303 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyMarkers();`
- L308 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Enable Chromakey Markers"))` — True to display Chromakey Markers within the inner frustum.
- L312 _public member_ `FLinearColor MarkerColor = { 0.f, 0.25f, 0.f, 1.f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Marker Color
- L316 _public member_ `TObjectPtr<UTexture> MarkerTileRGBA = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Texture to use as the chromakey marker tile.
- L320 _public member_ `float MarkerSizeScale = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0", UIMin = "0", DisplayName = "Marker Scale"))` — Scale value for the size of each chromakey marker tile.
- L324 _public member_ `float MarkerTileDistance = 1.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0", UIMin = "0"))` — Distance value between each chromakey marker tile.
- L328 _public member_ `FVector2D MarkerTileOffset = { 0, 0 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Offset value for the chromakey marker tiles, normalized to the tile distance.  Adjust placement of the chromakey markers within the composition of the camera framing.  Whole numbers will offset chromakey markers by a cyclical amount and have no visual change.

#### struct `FDisplayClusterConfigurationICVFX_ChromakeySettings`  
`struct FDisplayClusterConfigurationICVFX_ChromakeySettings`  
_L332-400_
- reflection: `USTRUCT(Blueprintable)`
- L337 _public function_ `FDisplayClusterConfigurationICVFX_ChromakeySettings()`
- L344 _public prototype_ `EDisplayClusterShaderParametersICVFX_ChromakeySource GetChromakeyType(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get Type of Chromakey: disabled, filling all internal frustum or rendering Chromakey actors.
- L349 _public prototype_ `const FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings* GetChromakeyRenderSettings(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the Chromakey render settings Return nullptr if Chromakey: is disabled or its type does not use rendering
- L354 _public prototype_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings* GetWritableChromakeyRenderSettings(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings);` — Get the writable Chromakey render settings Return nullptr if Chromakey: is disabled or its type does not use rendering
- L357 _public prototype_ `const FLinearColor& GetChromakeyColor(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the Chromakey color value
- L360 _public prototype_ `const FLinearColor& GetOverlapChromakeyColor(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the Chromakey overlap color value
- L365 _public prototype_ `const FDisplayClusterConfigurationICVFX_ChromakeyMarkers* GetChromakeyMarkers(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the Chromakey markers settings Return nullptr if Chromakey markers is :disabled
- L370 _public prototype_ `const FDisplayClusterConfigurationICVFX_ChromakeyMarkers* GetOverlapChromakeyMarkers(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the Chromakey overlap markers settings Return nullptr if Chromakey overlap markers is disabled
- L374 _private prototype_ `const FDisplayClusterConfigurationICVFX_ChromakeyMarkers* ImplGetChromakeyMarkers(const FDisplayClusterConfigurationICVFX_ChromakeyMarkers* InValue) const;` — Checks the input parameter and returns it or nullptr if it cannot be used.
- L379 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Enable Inner Frustum Chromakey"))` — Set to True to fill the inner frustum with the specified Chromakey Color.
- L383 _public member_ `EDisplayClusterConfigurationICVFX_ChromakeyType ChromakeyType = EDisplayClusterConfigurationICVFX_ChromakeyType::InnerFrustum;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — The type of chromakey to use
- L387 _public member_ `EDisplayClusterConfigurationICVFX_ChromakeySettingsSource ChromakeySettingsSource = EDisplayClusterConfigurationICVFX_ChromakeySettingsSource::Viewport;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "ICVFX Camera Chromakey"))` — The source of the chromakey settings, either the settings on the ICVFX camera or the global settings on the root actor
- L391 _public member_ `FLinearColor ChromakeyColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Chromakey Color
- L395 _public member_ `FDisplayClusterConfigurationICVFX_ChromakeyRenderSettings ChromakeyRenderTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Custom Chromakey"))` — Configure a custom chromakey based on content that will appear in the inner frustum, rather than the entire inner frustum.
- L399 _public member_ `FDisplayClusterConfigurationICVFX_ChromakeyMarkers ChromakeyMarkers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Display Chromakey Markers to facilitate camera tracking in post production.

#### struct `FDisplayClusterConfigurationICVFX_GlobalChromakeySettings`  
`struct FDisplayClusterConfigurationICVFX_GlobalChromakeySettings`  
_L404-422_
- reflection: `USTRUCT(Blueprintable)`
- desc: Chromakey settings that are global for all ICVFX cameras in a root actor
- L409 _public function_ `FDisplayClusterConfigurationICVFX_GlobalChromakeySettings()`
- L417 _public member_ `FLinearColor ChromakeyColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Chromakey Color
- L421 _public member_ `FDisplayClusterConfigurationICVFX_ChromakeyMarkers ChromakeyMarkers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Display Chromakey Markers to facilitate camera tracking in post production.

#### struct `FDisplayClusterConfigurationICVFX_LightcardRenderSettings`  
`struct FDisplayClusterConfigurationICVFX_LightcardRenderSettings`  
_L425-447_
- reflection: `USTRUCT(Blueprintable)`
- L432 _public member_ `bool bReplaceViewport = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — override the texture of the target viewport from this lightcard RTT
- L436 _public member_ `FDisplayClusterConfigurationPostRender_Override Replace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Override viewport render from source texture
- L439 _public member_ `FDisplayClusterConfigurationPostRender_BlurPostprocess PostprocessBlur;` — `UPROPERTY()`
- L442 _public member_ `FDisplayClusterConfigurationPostRender_GenerateMips GenerateMips;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)`
- L446 _public member_ `FDisplayClusterConfigurationICVFX_OverlayAdvancedRenderSettings AdvancedRenderSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Advanced render settings

#### struct `FDisplayClusterConfigurationICVFX_LightcardSettings`  
`struct FDisplayClusterConfigurationICVFX_LightcardSettings`  
_L450-495_
- reflection: `USTRUCT(Blueprintable)`
- L456 _public prototype_ `bool ShouldUseLightCard(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Returns true if the use of the LightCard is allowed
- L459 _public prototype_ `bool ShouldUseUVLightCard(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Returns true if the use of the UVLightCard is allowed
- L462 _public prototype_ `EDisplayClusterShaderParametersICVFX_LightCardRenderMode GetLightCardRenderMode(const EDisplayClusterConfigurationICVFX_PerLightcardRenderMode InPerLightcardRenderMode, const UDisplayClusterConfigurationViewport* InViewportConfiguration = nullptr) const;` — Get lightcard render mode.
- L465 _public prototype_ `EDisplayClusterShaderParametersICVFX_LightCardRenderMode GetLightCardRenderModeOverride(const UDisplayClusterConfigurationViewport* InViewportConfiguration) const;` — Get LC render mode override.
- L470 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Cards", meta = (DisplayName = "Enable Light Cards"))` — Enable Light Cards
- L474 _public member_ `bool bIgnoreOuterViewportsFreezingForLightcards = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Cards", meta = (DisplayName = "Ignore Freezing of Outer Viewports for Lightcards"))` — Enable\Disable freeze rendering for lightcards when outer viewports rendering also freezed. This will impact performance.
- L478 _public member_ `EDisplayClusterConfigurationICVFX_LightcardRenderMode Blendingmode = EDisplayClusterConfigurationICVFX_LightcardRenderMode::Under;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Cards", meta = (DisplayName = "Blending Mode"))` — Specify how to render Light Cards in relation to the inner frustum.
- L482 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList ShowOnlyList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Cards", meta = (DisplayName = "Light Cards Content", ToolTip = "Content specified here will be treated as a Light Card and adhere to the Blending Mode setting", Substitutions = "LayersTooltip = Layers containing Light Cards, ActorsTooltip = Light Card Actors"))` — Render actors from this layers to lightcard textures
- L486 _public member_ `FDisplayClusterConfigurationICVFX_LightcardRenderSettings RenderSettings;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay)` — Configure global render settings for this viewport
- L490 _public member_ `FDisplayClusterConfigurationICVFX_LightcardOCIO LightcardOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "Lightcard OCIO"))` — OpenColorIO configuration for the lightcards.
- L494 _public member_ `bool bEnableOuterViewportColorGrading = false;` — `UPROPERTY()` — Enable using outer viewport Color Grading from DCRA for lightcard rendering

#### struct `FDisplayClusterConfigurationICVFX_CameraAdvancedRenderSettings`  
`struct FDisplayClusterConfigurationICVFX_CameraAdvancedRenderSettings`  
_L498-531_
- reflection: `USTRUCT(Blueprintable)`
- L505 _public member_ `float RenderTargetRatio = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.01", UIMin = "0.01", ClampMax = "1.0", UIMax = "1.0"))` — Performance: Render to scale RTT, resolved with shader to viewport (Custom value)
- L513 _public member_ `int GPUIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the ICVFX camera viewport. Value '-1' means do not use multi-GPU Used to improve rendering performance by spreading the load across multiple GPUs.
- L521 _public member_ `int StereoGPUIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Stereo GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the ICVFX camera viewport in stereo rendering for the second eye. A value of '-1' means to use the value from the GPU Index parameter. (the same value is used for both eyes). Used to improve rendering performance by spreading the load across multiple GPUs.
- L525 _public member_ `EDisplayClusterConfigurationViewport_StereoMode StereoMode = EDisplayClusterConfigurationViewport_StereoMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Performance: force monoscopic render, resolved to stereo viewport
- L530 _public member_ `int RenderFamilyGroup = -1;` — `UPROPERTY()` — Experimental: Support special frame builder mode - merge viewports to single viewfamily by group num [not implemented yet]

#### struct `FDisplayClusterConfigurationICVFX_CameraRenderSettings`  
`struct FDisplayClusterConfigurationICVFX_CameraRenderSettings`  
_L534-579_
- reflection: `USTRUCT(BlueprintType)`
- L539 _public prototype_ `FDisplayClusterConfigurationICVFX_CameraRenderSettings();`
- L544 _public member_ `FDisplayClusterConfigurationICVFX_CustomSize CustomFrameSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Custom Frame Resolution"))` — Custom resolution of the ICVFX Camera. If it is not used, the Default Frame Resolution value is used by default.
- L548 _public member_ `int RenderOrder = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Camera render order, bigger value is over
- L551 _public member_ `FDisplayClusterConfigurationViewport_CustomPostprocess CustomPostprocess;` — `UPROPERTY()`
- L555 _public member_ `bool bUseCameraComponentPostprocess = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Use postprocess settings from camera component
- L559 _public member_ `FDisplayClusterConfigurationPostRender_Override Replace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Replace Output With a Texture"))` — Replace viewport render from source texture
- L563 _public member_ `FDisplayClusterConfigurationMediaICVFX Media;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Media", ShowOnlyInnerProperties))` — Media settings
- L566 _public member_ `FDisplayClusterConfigurationPostRender_BlurPostprocess PostprocessBlur;` — `UPROPERTY()`
- L570 _public member_ `FDisplayClusterConfigurationPostRender_GenerateMips GenerateMips;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Mipmapping", Simplified))` — Mipmapping can help avoid visual artifacts when the inner frustum is rendered at a lower resolution than specified in the configuration and is smaller on screen than the available pixels on the display device.
- L574 _public member_ `FDisplayClusterConfigurationICVFX_CameraAdvancedRenderSettings AdvancedRenderSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Advanced render settings
- L578 _public prototype_ `void SetupViewInfo(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, FMinimalViewInfo& InOutViewInfo) const;` — Propagates general render related settings to the view info.

#### struct `FDisplayClusterConfigurationICVFX_CameraMotionBlurOverridePPS`  
`struct FDisplayClusterConfigurationICVFX_CameraMotionBlurOverridePPS`  
_L583-603_
- reflection: `USTRUCT(BlueprintType)`
- L590 _public member_ `bool bReplaceEnable = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay, meta = (DisplayName = "Enable Settings Override"))` — If enabled, override the overall motion blur settings that would otherwise come from the current post-process volume or Cine Camera.
- L594 _public member_ `float MotionBlurAmount = 1;` — `UPROPERTY(interp, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Intensity"))` — Strength of motion blur, 0:off.
- L598 _public member_ `float MotionBlurMax = 50;` — `UPROPERTY(interp, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.0", ClampMax = "100.0", DisplayName = "Max"))` — Max distortion caused by motion blur in percent of the screen width, 0:off
- L602 _public member_ `float MotionBlurPerObjectSize = 4;` — `UPROPERTY(interp, BlueprintReadWrite, Category = NDisplay, meta = (ClampMin = "0.0", UIMax = "100.0", DisplayName = "Per Object Size"))` — The minimum projected screen radius for a primitive to be drawn in the velocity pass.Percentage of screen width, smaller numbers cause more draw calls, default: 4 %

#### struct `FDisplayClusterConfigurationICVFX_CameraMotionBlur`  
`struct FDisplayClusterConfigurationICVFX_CameraMotionBlur`  
_L606-626_
- reflection: `USTRUCT(BlueprintType)`
- L613 _public member_ `EDisplayClusterConfigurationCameraMotionBlurMode MotionBlurMode = EDisplayClusterConfigurationCameraMotionBlurMode::Override;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Specify the motion blur mode for the inner frustum, correcting for the motion of the camera. Blur due to camera motion will be incorrectly doubled in the physically exposed image if there is already camera blur applied to the inner frustum.
- L617 _public member_ `float TranslationScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Translation Scale
- L621 _public member_ `FDisplayClusterConfigurationICVFX_CameraMotionBlurOverridePPS MotionBlurPPS;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Motion Blur Settings Override"))` — Motion Blur Settings Override
- L625 _public prototype_ `void SetupViewInfo(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, FMinimalViewInfo& InOutViewInfo) const;` — Propagates Motion Blur related settings to the view info.

#### struct `FDisplayClusterConfigurationICVFX_CameraDepthOfField`  
`struct FDisplayClusterConfigurationICVFX_CameraDepthOfField`  
_L629-672_
- reflection: `USTRUCT(BlueprintType)`
- L638 _public prototype_ `UTexture2D* GetCompensationLUT(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get the CompensationLUT texture corresponding to the current settings. @param InStageSettings - it can be used for global LUT settings.
- L643 _public member_ `bool bEnableDepthOfFieldCompensation = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay)` — Enables depth of field correction on the wall, which dynamically adjusts the size of the defocus circle of confusion to compensate for the real-world camera blur when shooting the wall
- L647 _public member_ `bool bAutomaticallySetDistanceToWall = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay)` — Allows the ICVFX camera to automatically compute its distance from the stage walls using ray casting every tick
- L651 _public member_ `float DistanceToWall = 0.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay, meta=(EditCondition="!bAutomaticallySetDistanceToWall"))` — The distance from the ICVFX camera to the wall it is pointing at
- L655 _public member_ `float DistanceToWallOffset = 0.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay)` — An offset applied to DistanceToWall (applied regardless of whether DistanceToWall is automatically set)
- L659 _public member_ `float DepthOfFieldGain = 1.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay, meta = (UIMin=0.0, UIMax=10.0, ClampMin=0.0, ClampMax=10.0))` — A gain factor that scales the amount of depth of field blur rendered on the wall
- L663 _public member_ `TSoftObjectPtr<UTexture2D> CompensationLUT = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/nDis` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = NDisplay)` — Look-up texture that encodes the specific amount of compensation used for each combination of wall distance and object distance
- L667 _public member_ `TObjectPtr<UTexture2D> DynamicCompensationLUT = nullptr;` — `UPROPERTY(Transient)` — Actual LUT to use with the depth of field pipeline, copied and modified from CompensationLUT
- L671 _public prototype_ `void UpdateDynamicCompensationLUT();` — Processes the compensation LUT by adding any needed DoF gain and writes the result to the dynamic compensation LUT texture

#### struct `FDisplayClusterConfigurationICVFX_CameraSoftEdge`  
`struct FDisplayClusterConfigurationICVFX_CameraSoftEdge`  
_L675-690_
- reflection: `USTRUCT(BlueprintType)`
- L681 _public member_ `float Vertical = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Top and Bottom", ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Adjust blur amount to the top and bottom edges of the inner frustum.
- L685 _public member_ `float Horizontal = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Sides", ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Adjust blur amount to the left and right side edges of the inner frustum.
- L689 _public member_ `float Feather = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Feather", ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Feather.

#### struct `FDisplayClusterConfigurationICVFX_CameraBorder`  
`struct FDisplayClusterConfigurationICVFX_CameraBorder`  
_L693-708_
- reflection: `USTRUCT(BlueprintType)`
- L699 _public member_ `bool Enable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Enable Inner Frustum Border"))` — Enable Inner Frustum Border.
- L703 _public member_ `float Thickness = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Border Width", ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Adjust border width to the top and bottom edges of the inner frustum.
- L707 _public member_ `FLinearColor Color = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Border Color"))` — Adjust color of the border edges of the inner frustum.

#### struct `FDisplayClusterConfigurationICVFX_CameraCustomFrustum`  
`struct FDisplayClusterConfigurationICVFX_CameraCustomFrustum`  
_L711-769_
- reflection: `USTRUCT(Blueprintable)`
- L717 _public member_ `FIntPoint EstimatedOverscanResolution = { 2560, 1440 };` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NDisplay)` — Expected ICVFX camera resolution when both 'Adapt Resolution' and 'Enable Inner Frustum Overscan' are enabled.
- L721 _public member_ `FIntPoint InnerFrustumResolution = { 2560, 1440 };` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = NDisplay)` — Real ICVFX camera resolution for current settings.
- L725 _public member_ `float OverscanPixelsIncrease = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = NDisplay, meta = (HideInDetailPanel))` — This value shows the ratio of "Overscan Estimated Resolution" pixels to "Frustum Internal Resolution" pixels.
- L729 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Enable Inner Frustum Overscan"))` — Enable Custom Frustum.
- L733 _public member_ `bool bAdaptResolution = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Adapt Resolution"))` — Enable adaptive resolution.
- L737 _public member_ `float FieldOfViewMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Overscan Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "5.0", UIMax = "5.0"))` — Multiply the field of view for the ICVFX camera by this value.  This can increase the overall size of the inner frustum to help provide a buffer against latency when moving the camera.
- L741 _public member_ `EDisplayClusterConfigurationViewportCustomFrustumMode Mode = EDisplayClusterConfigurationViewportCustomFrustumMode::Percent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Overscan Units"))` — Enable/disable inner camera custom frustum and specify units as percent or pixel values.
- L745 _public member_ `float Left = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Left", ClampMin = "-500.0", UIMin = "-500.0", ClampMax = "500.0", UIMax = "500.0"))` — Pixel/Percent value to alter the frustum to the left side
- L749 _public member_ `float Right = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Right", ClampMin = "-500.0", UIMin = "-500.0", ClampMax = "500.0", UIMax = "500.0"))` — Pixel/Percent value to alter the frustum to the right side
- L753 _public member_ `float Top = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Top", ClampMin = "-500.0", UIMin = "-500.0", ClampMax = "500.0", UIMax = "500.0"))` — Pixel/Percent value to alter the frustum to the top
- L757 _public member_ `float Bottom = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Bottom", ClampMin = "-500.0", UIMin = "-500.0", ClampMax = "500.0", UIMax = "500.0"))` — Pixel/Percent value to alter the frustum to the bottom
- L761 _public prototype_ `void SetupViewInfo(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings, FMinimalViewInfo& InOutViewInfo) const;` — Propagates Custom Frustum related settings to the view info.
- L764 _public prototype_ `float GetCameraFieldOfViewMultiplier(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get camera FOV multiplier.
- L767 _public prototype_ `float GetCameraAdaptResolutionRatio(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get camera adapt resolution ratio.

#### struct `FDisplayClusterConfigurationICVFX_CameraSettings`  
`struct FDisplayClusterConfigurationICVFX_CameraSettings`  
_L772-907_
- reflection: `USTRUCT(BlueprintType)`
- L784 _public prototype_ `bool IsICVFXEnabled(const class UDisplayClusterConfigurationData& InConfigurationData, const FString& InClusterNodeId) const;` — Returns true if this camera is active @param InConfigurationData - cluster configuration data @param InClusterNodeId     - current cluster node name @return - true if this camera can be used
- L787 _public prototype_ `ACineCameraActor* GetExternalCineCameraActor() const;` — Returns the CineCameraActor from the 'ExternalCameraActor' parameter.
- L790 _public prototype_ `UCineCameraComponent* GetExternalCineCameraComponent() const;` — Returns the CineCameraComponent from the 'ExternalCameraActor' parameter.
- L793 _public prototype_ `FDisplayClusterConfigurationICVFX_CameraSettings();`
- L796 _public prototype_ `const FOpenColorIOColorConversionSettings* FindInnerFrustumOCIOConfiguration(const FString& InClusterNodeId) const;` — Return InCamera OCIO configuration for the specified cluster node. Return nullptr if no OCIO.
- L799 _public prototype_ `const FOpenColorIOColorConversionSettings* FindChromakeyOCIOConfiguration(const FString& InClusterNodeId) const;` — Return Chromakey OCIO configuration for the specified cluster node. Return nullptr if no OCIO.
- L801 _public prototype_ `bool IsInnerFrustumViewportSettingsEqual(const FString& InClusterNodeId1, const FString& InClusterNodeId2) const;`
- L802 _public prototype_ `bool IsChromakeyViewportSettingsEqual(const FString& InClusterNodeId1, const FString& InClusterNodeId2) const;`
- L806 _public function_ `FVector4 GetCameraSoftEdge(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const UCineCameraComponent& InCineCameraComponent) const` — `UE_DEPRECATED(5.5, "Use the UDisplayClusterICVFXCameraComponent::GetICVFXCameraShaderParameters() instead")` — Return calculated soft edges values.
- L809 _public prototype_ `float GetCameraBufferRatio(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get camera buffer ratio.
- L812 _public prototype_ `void GetCameraUpscalerSettings(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, FDisplayClusterUpscalerSettings& OutUpscalerSettings) const;` — Get camera upscale settings.
- L816 _public function_ `FIntPoint GetCameraFrameSize(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const UCineCameraComponent& InCineCameraComponent) const` — `UE_DEPRECATED(5.5, "Use the UDisplayClusterICVFXCameraComponent::GetICVFXCameraFrameSize() instead")` — Get camera frame resolution.
- L820 _public function_ `float GetCameraFrameAspectRatio(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const UCineCameraComponent& InCineCameraComponent) const` — `UE_DEPRECATED(5.5, "Use the UDisplayClusterICVFXCameraComponent::GetICVFXCameraFrameSize() instead")` — Get camera frame aspect ratio.
- L824 _public function_ `bool GetCameraBorder(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, FLinearColor& OutBorderColor, float& OutBorderThickness) const` — `UE_DEPRECATED(5.5, "Use the UDisplayClusterICVFXCameraComponent::GetICVFXCameraShaderParameters() instead")` — Get camera border settings.
- L827 _public prototype_ `void SetupViewInfo(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, FMinimalViewInfo& InOutViewInfo);` — Sets up view info for each relevant setting such as render, custom frustrum and motion blur settings.
- L832 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Enable Inner Frustum"))` — Render the inner frustum for this ICVFX camera.
- L836 _public member_ `TSoftObjectPtr<ACineCameraActor> ExternalCameraActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In Camera VFX", meta = (DisplayName = "Cine Camera Actor"))` — Specify a Cine Camera Actor for this ICVFX camera to use instead of the default nDisplay camera.
- L840 _public member_ `float BufferRatio = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Screen Percentage", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10.0", UIMax = "1.0"))` — Adjust resolution scaling for the inner frustum.
- L844 _public member_ `FDisplayClusterConfigurationUpscalerSettings UpscalerSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Upscaler Settings"))` — Upscaler settings for the inner frustum.
- L848 _public member_ `FDisplayClusterConfigurationICVFX_CameraCustomFrustum CustomFrustum;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Overscan"))` — Render a larger or smaller inner frame
- L852 _public member_ `FDisplayClusterConfigurationICVFX_CameraSoftEdge SoftEdge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Soften the edges of the inner frustum to help avoid hard lines in reflections seen by the live-action camera.
- L856 _public member_ `FRotator FrustumRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Rotation"))` — Rotate the inner frustum.
- L860 _public member_ `FVector FrustumOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Offset"))` — Specify an offset on the inner frustum.
- L864 _public member_ `FVector2D OffCenterProjectionOffset = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Projection Offset"))` — Off-axis / off-center projection offset as proportion of screen dimensions.
- L868 _public member_ `FDisplayClusterConfigurationICVFX_CameraBorder Border;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Inner Frustum Border"))` — Border for the inner frustum.
- L872 _public member_ `FDisplayClusterConfigurationICVFX_CameraMotionBlur CameraMotionBlur;` — `UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, EditAnywhere, Category = "In Camera VFX")` — Render motion blur more accurately by subtracting blur from camera motion and avoiding amplification of blur by the physical camera.
- L876 _public member_ `FDisplayClusterConfigurationICVFX_CameraDepthOfField CameraDepthOfField;` — `UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, EditAnywhere, Category = "In Camera VFX")` — Settings that control the depth of field blur applied to the ICVFX image
- L880 _public member_ `FDisplayClusterConfigurationICVFX_CameraRenderSettings RenderSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay)` — Configure global render settings for this viewport
- L883 _public member_ `FDisplayClusterConfigurationICVFX_ChromakeySettings Chromakey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chromakey)`
- L886 _public member_ `FDisplayClusterConfigurationICVFX_CameraOCIO CameraOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OCIO)`
- L890 _public member_ `bool EnableInnerFrustumColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inner Frustum Color Grading", meta = (DisplayName = "Enable Inner Frustum Color Grading"))` — Entire Cluster Color Grading
- L894 _public member_ `FDisplayClusterConfigurationViewport_AllNodesColorGrading AllNodesColorGrading;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inner Frustum Color Grading", meta = (DisplayName = "All Nodes Color Grading"))` — All Nodes Color Grading
- L898 _public member_ `TArray<FDisplayClusterConfigurationViewport_PerNodeColorGrading> PerNodeColorGrading;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inner Frustum Color Grading", meta = (DisplayName = "Per-Node Color Grading", ConfigurationMode = "ClusterNodes"))` — Perform advanced color grading operations for the inner frustum on a per-node or group-of-nodes basis.
- L902 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList CameraHideList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Content Hidden from Inner Frustum", Substitutions = "LayersTooltip = Layers hidden from the inner frustum, ActorsTooltip = Actors hidden from the inner frustum"))` — Content specified here will not appear in the inner frustum, but can appear in the nDisplay viewports.
- L906 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList HiddenICVFXViewports;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (ClusterItemType = Viewports, DisplayName = "Inner Frustum Hidden in Viewports"))` — A list of viewports that the inner frustum is not rendered to.

#### struct `FDisplayClusterConfigurationICVFX_StageSettings`  
`struct FDisplayClusterConfigurationICVFX_StageSettings`  
_L910-984_
- reflection: `USTRUCT(Blueprintable)`
- L916 _public prototype_ `const FOpenColorIOColorConversionSettings* FindViewportOCIOConfiguration(const FString& InViewportId) const;` — Return OCIO configuration for the specified viewport. Return nullptr if no OCIO.
- L919 _public prototype_ `const FOpenColorIOColorConversionSettings* FindLightcardOCIOConfiguration(const FString& InViewportId) const;` — Return LightCard OCIO configuration for the specified viewport. Return nullptr if no OCIO.
- L922 _public prototype_ `EDisplayClusterShaderParametersICVFX_CameraOverlappingRenderMode GetCameraOverlappingRenderMode() const;` — Get camera overlapping rendering mode.
- L927 _public member_ `bool bEnableInnerFrustums = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Enable Inner Frustum"))` — Enable/disable the inner frustum on all ICVFX cameras.
- L931 _public member_ `bool bEnableInnerFrustumChromakeyOverlap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Enable Inner Frustum Chromakey Overlap"))` — Render the chromakey where the inner frustum overlaps.
- L935 _public member_ `FDisplayClusterConfigurationUpscalerSettings GlobalInnerFrustumUpscalerSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (DisplayName = "Default Upscaler Settings"))` — Global upscaler settings that all ICVFX camera components can opt to use.
- L939 _public member_ `FDisplayClusterConfigurationICVFX_Size DefaultFrameSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Configuration, meta = (DisplayName = "Default Frame Resolution"))` — Default In-Cameras texture resolution.
- L942 _public member_ `FDisplayClusterConfigurationICVFX_LightcardSettings Lightcard;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Cards", meta = (ExpandProperties))`
- L946 _public member_ `bool bFreezeRenderOuterViewports = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Viewports, meta = (DisplayName = "Freeze Viewports"))` — Freeze rendering for viewports. This improves performance.
- L950 _public member_ `FDisplayClusterConfigurationUpscalerSettings OuterViewportUpscalerSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Viewports, meta = (DisplayName = "Default Upscaler Settings"))` — Global upscaler settings for Outer viewports.
- L955 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList HideList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Viewports, meta = (DisplayName = "Content Hidden from Entire Cluster", ToolTip = "Content specified here will not appear anywhere in the nDisplay cluster", Substitutions = "LayersTooltip = Layers hidden from the entire nDisplay cluster, ActorsTooltip = Actors hidden from the entire nDisplay cluster"))` — Hide list for all icvfx viewports (outer, inner, cameras, etc) (This allow to hide all actors from layers for icvfx render logic)
- L959 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList OuterViewportHideList;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Viewports, meta = (DisplayName = "Content Hidden from All Viewports", ToolTip = "Content specified here will not appear in the nDisplay viewports, but can appear in the inner frustum.", Substitutions = "LayersTooltip = Layers hidden from the nDisplay viewports, ActorsTooltip = Actors hidden from the nDisplay viewports"))` — Special hide list for Outer viewports
- L963 _public member_ `bool EnableColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Enable Color Grading"))` — Viewport Color Grading
- L967 _public member_ `FDisplayClusterConfigurationViewport_EntireClusterColorGrading EntireClusterColorGrading;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Entire Cluster"))` — Entire Cluster Color Grading
- L971 _public member_ `TArray<FDisplayClusterConfigurationViewport_PerViewportColorGrading> PerViewportColorGrading;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Per-Viewport Color Grading", ConfigurationMode = "Viewports"))` — Perform advanced color grading operations on a per-viewport or group-of-viewports basis.
- L975 _public member_ `FDisplayClusterConfigurationICVFX_ViewportOCIO ViewportOCIO;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO", meta = (DisplayName = "Outer Viewports OCIO"))` — OpenColorIO configuration for the Outer viewports.
- L979 _public member_ `FDisplayClusterConfiguration_AutoExposureSettings AutoExposureSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposure", meta = (DisplayName = "Auto Exposure Settings"))` — Entire cluster Auto Exposure settings.
- L983 _public member_ `FDisplayClusterConfigurationICVFX_GlobalChromakeySettings GlobalChromakey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chromakey")` — Global chromakey settings that all ICVFX camera components can opt to use

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Media.h` (Public)


#### enum `EDisplayClusterConfigurationMediaSplitType`  
`enum class EDisplayClusterConfigurationMediaSplitType : uint8`  
_L25-29_
- reflection: `UENUM(BlueprintType)`
- desc: Media frame split types
- L27 _public enumerator_ `FullFrame UMETA(DisplayName = "Full Frame")`
- L28 _public enumerator_ `UniformTiles UMETA(DisplayName = "Tiled")`

#### struct `FDisplayClusterConfigurationMediaInput`  
`struct FDisplayClusterConfigurationMediaInput`  
_L36-44_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media input item
- L43 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media source to use

#### struct `FDisplayClusterConfigurationMediaOutput`  
`struct FDisplayClusterConfigurationMediaOutput`  
_L51-63_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media output item
- L58 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media output to use
- L62 _public member_ `TObjectPtr<UDisplayClusterMediaOutputSynchronizationPolicy> OutputSyncPolicy;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Capture Synchronization"))` — Media output synchronization policy

#### struct `FDisplayClusterConfigurationMediaInputGroup`  
`struct FDisplayClusterConfigurationMediaInputGroup : public FDisplayClusterConfigurationMediaInput`  
_L70-79_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationMediaInput`
- desc: Media input group (ICVFX, Full frame)
- L78 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList ClusterNodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Media, meta = (ClusterItemType = ClusterNodes))` — Cluster nodes that use media source below

#### struct `FDisplayClusterConfigurationMediaOutputGroup`  
`struct FDisplayClusterConfigurationMediaOutputGroup : public FDisplayClusterConfigurationMediaOutput`  
_L86-95_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FDisplayClusterConfigurationMediaOutput`
- desc: Media output group (ICVFX, Full Frame)
- L94 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList ClusterNodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Media, meta = (ClusterItemType = ClusterNodes))` — Cluster nodes that export media via MediaOutput below

#### struct `FDisplayClusterConfigurationMediaUniformTileInput`  
`struct FDisplayClusterConfigurationMediaUniformTileInput`  
_L102-114_
- reflection: `USTRUCT(BlueprintType)`
- desc: Uniform tile media input item. Maps a tile to a media source.
- L109 _public member_ `FIntPoint Position = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media", meta = (ClampMin = 0, ClampMax = 3))` — Tile position
- L113 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media source to use

#### struct `FDisplayClusterConfigurationMediaUniformTileOutput`  
`struct FDisplayClusterConfigurationMediaUniformTileOutput`  
_L121-137_
- reflection: `USTRUCT(BlueprintType)`
- desc: Uniform tile media output item. Maps a tile to a media output.
- L128 _public member_ `FIntPoint Position = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Media", meta = (ClampMin = 0, ClampMax = 3))` — Tile position
- L132 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media output to use
- L136 _public member_ `TObjectPtr<UDisplayClusterMediaOutputSynchronizationPolicy> OutputSyncPolicy;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Capture Synchronization"))` — Media output synchronization policy

#### struct `FDisplayClusterConfigurationMediaTiledInputGroup`  
`struct FDisplayClusterConfigurationMediaTiledInputGroup`  
_L144-156_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media input group (ICVFX, Tiled)
- L151 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList ClusterNodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ClusterItemType = ClusterNodes))` — Cluster nodes that use media source below
- L155 _public member_ `TArray<FDisplayClusterConfigurationMediaUniformTileInput> Tiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Tile mapping. Maps tiles to media sources.

#### struct `FDisplayClusterConfigurationMediaTiledOutputGroup`  
`struct FDisplayClusterConfigurationMediaTiledOutputGroup`  
_L165-185_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media output group (ICVFX, Tiled)
- L172 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList ClusterNodes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ClusterItemType = ClusterNodes))` — Cluster nodes that export media via MediaOutput below
- L176 _public member_ `TArray<FDisplayClusterConfigurationMediaUniformTileOutput> Tiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Tile mapping. Maps tiles to media outputs.
- L183 _public member_ `TObjectPtr<UDisplayClusterMediaOutputSynchronizationPolicy> OutputSyncPolicy;` — `UE_DEPRECATED(5.6, "This property has been deprecated. Please refer new MediaOutputs property.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated. Synchronization policy is bound to the actual media outputs."))` — Media output synchronization policy

#### struct `FDisplayClusterConfigurationMediaNodeBackbuffer`  
`struct FDisplayClusterConfigurationMediaNodeBackbuffer`  
_L194-219_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media settings for node backbuffer
- L201 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Enable Media"))` — Enable/Disable Media
- L205 _public member_ `TArray<FDisplayClusterConfigurationMediaOutput> MediaOutputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Full-Frame Media Outputs
- L209 _public member_ `FIntPoint TiledSplitLayout = { 1, 1 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ClampMin = 1, ClampMax = 4))` — Split layout
- L213 _public member_ `TArray<FDisplayClusterConfigurationMediaUniformTileOutput> TiledMediaOutputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Tile mapping. Maps tiles to media outputs.
- L218 _public prototype_ `bool IsMediaOutputAssigned() const;` — Returns true if at least one media output assigned

#### struct `FDisplayClusterConfigurationMediaViewport`  
`struct FDisplayClusterConfigurationMediaViewport`  
_L228-272_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media settings for viewports
- L235 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Enable Media"))` — Enable/disable media
- L239 _public member_ `FDisplayClusterConfigurationMediaInput MediaInput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media source to use
- L243 _public member_ `TArray<FDisplayClusterConfigurationMediaOutput> MediaOutputs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Media outputs to use
- L247 _public prototype_ `bool IsMediaInputAssigned() const;` — Returns true if a media source assigned
- L250 _public prototype_ `bool IsMediaOutputAssigned() const;` — Returns true if at least one media output assigned
- L256 _protected member_ `FString MediaSharingNode_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated"))`
- L261 _public member_ `TObjectPtr<UMediaSource> MediaSource;` — `UE_DEPRECATED(5.3, "This property has been deprecated. Please refer new MediaInput property.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated. Please refer new MediaInput property."))`
- L265 _public member_ `TObjectPtr<UMediaOutput> MediaOutput;` — `UE_DEPRECATED(5.3, "This property has been deprecated. Please refer new MediaOutputs property.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated. Please refer new MediaOutputs property."))`
- L269 _public member_ `TObjectPtr<UDisplayClusterMediaOutputSynchronizationPolicy> OutputSyncPolicy;` — `UE_DEPRECATED(5.3, "This property has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been deprecated."))`

#### struct `FDisplayClusterConfigurationMediaICVFX`  
`struct FDisplayClusterConfigurationMediaICVFX`  
_L281-406_
- reflection: `USTRUCT(Blueprintable)`
- desc: Media settings for ICVFX cameras
- L288 _public prototype_ `FDisplayClusterConfigurationMediaICVFX() = default;`
- L289 _public prototype_ `~FDisplayClusterConfigurationMediaICVFX() = default;`
- L290 _public prototype_ `FDisplayClusterConfigurationMediaICVFX(const FDisplayClusterConfigurationMediaICVFX&) = default;`
- L291 _public prototype_ `FDisplayClusterConfigurationMediaICVFX(FDisplayClusterConfigurationMediaICVFX&&) = default;`
- L292 _public prototype_ `FDisplayClusterConfigurationMediaICVFX& operator=(const FDisplayClusterConfigurationMediaICVFX&) = default;`
- L293 _public prototype_ `FDisplayClusterConfigurationMediaICVFX& operator=(FDisplayClusterConfigurationMediaICVFX&&) = default;`
- L299 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Enable Media"))` — Enable/disable media
- L303 _public member_ `EDisplayClusterConfigurationMediaSplitType SplitType = EDisplayClusterConfigurationMediaSplitType::FullFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Inner Frustum Type"))` — Media frame split type
- L309 _public member_ `TArray<FDisplayClusterConfigurationMediaInputGroup> MediaInputGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media Input Groups"))` — Media input mapping (Full frame)
- L313 _public member_ `TArray<FDisplayClusterConfigurationMediaOutputGroup> MediaOutputGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media Output Groups"))` — Media output mapping (Full frame)
- L319 _public member_ `FIntPoint TiledSplitLayout = { 1, 1 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Tiled Split Layout", ClampMin = 1, ClampMax = 4))` — Split layout
- L323 _public member_ `FDisplayClusterConfigurationTile_Overscan TileOverscan;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")` — Overscan settings for tile.
- L327 _public member_ `FDisplayClusterConfigurationClusterItemReferenceList ClusterNodesToRenderUnboundTiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ClusterItemType = ClusterNodes, DisplayName = "Nodes To Render Unbound Tiles", ToolTip = "Choose nodes that should render camera tiles that don't have any media assigned"))` — Cluster nodes that should render unbound tiles. Unbound tiles are the tiles that don't have any media assigned
- L331 _public member_ `TArray<FDisplayClusterConfigurationMediaTiledInputGroup> TiledMediaInputGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media Input Groups"))` — Media input mapping (Tiled)
- L335 _public member_ `TArray<FDisplayClusterConfigurationMediaTiledOutputGroup> TiledMediaOutputGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media Output Groups"))` — Media output mapping (Tiled)
- L339 _public member_ `bool bLateOCIOPass_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "This property has been depreacted. Late OCIO is automatically detected in runtime.")` — `UPROPERTY(meta = (DeprecatedProperty))`
- L343 _public member_ `bool bTransferPQ_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "This property has been depreacted. PQ is allways used now.")` — `UPROPERTY(meta = (DeprecatedProperty))`
- L347 _public prototype_ `bool ShouldMediaICVFXSplitIntoTiles() const;` — Returns true if these media settings can be used for tiling.
- L350 _public prototype_ `EDisplayClusterViewportTileFlags GetMediaICVFXTileFlags(const FString& NodeId) const;` — Returns additional tile settings for the cluster node.
- L353 _public prototype_ `bool HasAnyMediaInputAssigned(const FString& NodeId, EDisplayClusterConfigurationMediaSplitType SplitType) const;` — Returns true if any media source of specified split-type is bound
- L356 _public prototype_ `bool HasAnyMediaOutputAssigned(const FString& NodeId, EDisplayClusterConfigurationMediaSplitType SplitType) const;` — Returns true if any media output of specified split-type is bound
- L359 _public prototype_ `UMediaSource* GetMediaSource(const FString& NodeId) const;` — [FullFrame] Returns media source bound to a specific cluster node if configured for full-frame media
- L362 _public prototype_ `TArray<FDisplayClusterConfigurationMediaOutputGroup> GetMediaOutputGroups(const FString& NodeId) const;` — [FullFrame] Returns media outputs bound to a specific cluster node if configured for full-frame media
- L365 _public prototype_ `bool GetMediaInputTiles(const FString& NodeId, TArray<FDisplayClusterConfigurationMediaUniformTileInput>& OutTiles) const;` — [UniformTiles] Returns all the tiles bound to a specific cluster node.
- L368 _public prototype_ `bool GetMediaOutputTiles(const FString& NodeId, TArray<FDisplayClusterConfigurationMediaUniformTileOutput>& OutTiles) const;` — [UniformTiles] Returns all the tiles bound to a specific cluster node.
- L372 _public function_ `TArray<UMediaOutput*> GetMediaOutputs(const FString& NodeId) const` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use GetMediaOutputGroups.")`
- L378 _public function_ `UDisplayClusterMediaOutputSynchronizationPolicy* GetOutputSyncPolicy(const FString& NodeId) const` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use GetMediaOutputGroups.")`
- L384 _public function_ `UMediaOutput* GetMediaOutput(const FString& NodeId) const` — `UE_DEPRECATED(5.3, "This function has been deprecated. Please use GetMediaOutputGroups.")`
- L390 _public function_ `bool IsMediaSharingNode(const FString& InNodeId) const` — `UE_DEPRECATED(5.2, "This function has been deprecated.")`
- L396 _public function_ `bool IsMediaInputAssigned(const FString& NodeId) const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'HasAnyMediaInputAssigned'.")`
- L402 _public function_ `bool IsMediaOutputAssigned(const FString& NodeId) const` — `UE_DEPRECATED(5.4, "This function has been deprecated. Please use 'HasAnyMediaOutputAssigned'.")`

#### struct `FDisplayClusterConfigurationGlobalMediaSettings`  
`struct FDisplayClusterConfigurationGlobalMediaSettings`  
_L413-421_
- reflection: `USTRUCT(Blueprintable)`
- desc: Global media settings
- L420 _public member_ `int32 Latency = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (ClampMin = "0", ClampMax = "9", UIMin = "0", UIMax = "9"))` — Media latency

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_MediaSync.h` (Public)


#### class `IDisplayClusterMediaOutputSynchronizationPolicyHandler`  
`class IDisplayClusterMediaOutputSynchronizationPolicyHandler : public TSharedFromThis<IDisplayClusterMediaOutputSynchronizationPolicyHandler>`  
_L16-37_
- inherits: `TSharedFromThis<IDisplayClusterMediaOutputSynchronizationPolicyHandler>`
- desc: Media output sync policy handler interface. All sync logic is handled in a derived native class to avoid UObject interaction from other threads.
- L21 _public prototype_ `virtual ~IDisplayClusterMediaOutputSynchronizationPolicyHandler() = default;` — Destructor
- L24 _public prototype_ `virtual bool IsCaptureTypeSupported(UMediaCapture* MediaCapture) const = 0;` — Returns true if specified media capture type can be synchonized by the policy implementation
- L27 _public prototype_ `virtual bool StartSynchronization(UMediaCapture* MediaCapture, const FString& MediaId) = 0;` — Starts synchronization of specific output stream (capture device). Returns false if failed.
- L30 _public prototype_ `virtual void StopSynchronization() = 0;` — Stops synchronization of specific output stream (capture device).
- L33 _public prototype_ `virtual bool IsRunning() = 0;` — Returns true if currently synchronizing a media output.
- L36 _public prototype_ `virtual TSubclassOf<UDisplayClusterMediaOutputSynchronizationPolicy> GetPolicyClass() const = 0;` — Returns the policy config class used to create this policy handler.

#### class `UDisplayClusterMediaOutputSynchronizationPolicy`  
`class UDisplayClusterMediaOutputSynchronizationPolicy : public UObject`  
_L43-52_
- reflection: `UCLASS(Abstract, editinlinenew, BlueprintType, hidecategories = (Object))`
- inherits: `UObject`
- desc: Base media output synchronization policy class settings
- L51 _public prototype_ `virtual TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> GetHandler() PURE_VIRTUAL(UDisplayClusterMediaOutputSynchronizationPolicy::GetHandler, return nullptr;);` — Returns the handler associated with this policy config object

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_OCIO.h` (Public)


#### struct `FDisplayClusterConfigurationOCIOConfiguration`  
`struct FDisplayClusterConfigurationOCIOConfiguration`  
_L16-36_
- reflection: `USTRUCT(Blueprintable)`
- desc: OCIO configuration structure.
- L22 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO")` — Enable the application of an OpenColorIO configuration to all viewports.
- L26 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the ColorConfiguration property instead"))` — "This property has been deprecated.
- L30 _public member_ `FOpenColorIOColorConversionSettings ColorConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO")` — Conversion to apply when this display is enabled
- L34 _public prototype_ `bool Serialize(FArchive& Ar);`
- L35 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDisplayClusterConfigurationOCIOConfiguration> : public TStructOpsTypeTraitsBase2<FDisplayClusterConfigurationOCIOConfiguration>`  
_L38-45_
- inherits: `TStructOpsTypeTraitsBase2<FDisplayClusterConfigurationOCIOConfiguration>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L41-44_

#### struct `FDisplayClusterConfigurationOCIOProfile`  
`struct FDisplayClusterConfigurationOCIOProfile`  
_L53-80_
- reflection: `USTRUCT(Blueprintable)`
- desc: OCIO profile structure. Can be configured for viewports or cluster nodes. To enable viewport configuration when using as a UPROPERTY set meta = (ConfigurationMode = "Viewports") To enable cluster node configuration when using as a UPROPERTY set meta = (ConfigurationMode = "ClusterNodes")
- L59 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO")` — Enable the application of an OpenColorIO configuration for the viewport(s) specified.
- L63 _public member_ `FOpenColorIODisplayConfiguration OCIOConfiguration_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the ColorConfiguration property instead"))` — "This property has been deprecated.
- L67 _public member_ `TArray<FString> ApplyOCIOToObjects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OCIO")` — Specify the viewports to apply this OpenColorIO configuration.
- L71 _public member_ `FOpenColorIOColorConversionSettings ColorConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OCIO")` — Conversion to apply when this display is enabled
- L75 _public prototype_ `bool Serialize(FArchive& Ar);`
- L76 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L79 _public prototype_ `bool IsEnabledForObject(const FString& InObjectId) const;` — Return true if the configuration is valid for the input object

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDisplayClusterConfigurationOCIOProfile> : public TStructOpsTypeTraitsBase2<FDisplayClusterConfigurationOCIOProfile>`  
_L82-89_
- inherits: `TStructOpsTypeTraitsBase2<FDisplayClusterConfigurationOCIOProfile>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L85-88_

#### Free symbols / members of external scopes

- L42 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonacfbbede0103`)
- L43 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonacfbbede0103`)
- L86 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonacfbbede0203`)
- L87 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonacfbbede0203`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_OutputRemap.h` (Public)


#### enum `EDisplayClusterConfigurationFramePostProcess_OutputRemapSource`  
`enum class EDisplayClusterConfigurationFramePostProcess_OutputRemapSource : uint8`  
_L16-26_
- reflection: `UENUM()`
- desc: Source types of the output remapping
- L19 _public enumerator_ `StaticMesh UMETA(DisplayName = "Static Mesh")` — Use a Static Mesh reference for output remapping when the Data Source is set to Mesh
- L22 _public enumerator_ `ExternalFile UMETA(DisplayName = "External File")` — Use an external .obj file for output remapping when the Data Source is set to File
- L25 _public enumerator_ `MeshComponent UMETA(DisplayName = "Mesh Component")` — Use a Mesh component reference for output remapping (ProceduralMeshComponent or StaticMeshComponent)

#### struct `FDisplayClusterConfigurationFramePostProcess_OutputRemap`  
`struct FDisplayClusterConfigurationFramePostProcess_OutputRemap`  
_L30-54_
- reflection: `USTRUCT(Blueprintable)`
- desc: Screen space remapping of the final backbuffer output. Applied at the whole window
- L37 _public member_ `bool bEnable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay OutputRemap", meta = (DisplayName = "Enable Output Remapping"))` — Enables or disables output remapping
- L41 _public member_ `EDisplayClusterConfigurationFramePostProcess_OutputRemapSource DataSource = EDisplayClusterConfigurationFramePostProcess_OutputRemapSource::StaticMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay OutputRemap")` — Selects either the Static Mesh or External File setting as the source for output remapping
- L45 _public member_ `TObjectPtr<class UStaticMesh> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NDisplay OutputRemap", meta = (EditCondition = "DataSource == EDisplayClusterConfigurationFramePostProcess_OutputRemapSource::StaticMesh"))` — The Static Mesh reference to use for output remapping when the Data Source is set to Static Mesh
- L49 _public member_ `FString MeshComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NDisplay OutputRemap", meta = (EditCondition = "DataSource == EDisplayClusterConfigurationFramePostProcess_OutputRemapSource::MeshComponent"))` — The MeshComponent reference (ProceduralMeshComponent or StaticMeshComponent) to use for output remapping when the Data Source is set to Mesh Component
- L53 _public member_ `FString ExternalFile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay OutputRemap", meta = (EditCondition = "DataSource == EDisplayClusterConfigurationFramePostProcess_OutputRemapSource::ExternalFile"))` — The external .obj file to use for output remapping when the Data Source is set to File

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_PostRender.h` (Public)


#### struct `FDisplayClusterConfigurationPostRender_Override`  
`struct FDisplayClusterConfigurationPostRender_Override`  
_L19-39_
- reflection: `USTRUCT(Blueprintable)`
- L26 _public member_ `bool bAllowReplace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render", meta = (DisplayName = "Enable Viewport Texture Replacement"))` — Disable default render, and resolve SourceTexture to viewport
- L30 _public member_ `TObjectPtr<UTexture> SourceTexture = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render")` — Texture to use in place of the inner frustum.
- L34 _public member_ `bool bShouldUseTextureRegion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render", meta = (DisplayName = "Use Texture Crop"))` — Set to True to crop the texture for the inner frustum as specified below.
- L38 _public member_ `FDisplayClusterReplaceTextureCropRectangle TextureRegion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render", meta = (DisplayName = "Texture Crop"))` — Texture Crop

#### struct `FDisplayClusterConfigurationPostRender_BlurPostprocess`  
`struct FDisplayClusterConfigurationPostRender_BlurPostprocess`  
_L42-58_
- reflection: `USTRUCT(Blueprintable)`
- L49 _public member_ `EDisplayClusterConfiguration_PostRenderBlur Mode = EDisplayClusterConfiguration_PostRenderBlur::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render")` — Enable/disable Post Process Blur and specify method.
- L53 _public member_ `int KernelRadius = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render", meta = (EditCondition = "Mode != EDisplayClusterConfiguration_PostRenderBlur::None"))` — Kernel Radius
- L57 _public member_ `float KernelScale = 20;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render", meta = (EditCondition = "Mode != EDisplayClusterConfiguration_PostRenderBlur::None"))` — Kernel Scale

#### struct `FDisplayClusterConfigurationPostRender_GenerateMips`  
`struct FDisplayClusterConfigurationPostRender_GenerateMips`  
_L61-88_
- reflection: `USTRUCT(Blueprintable)`
- L67 _public member_ `bool bAutoGenerateMips = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Render")` — Generate and use mipmaps for the inner frustum.  Disabling this can improve performance but result in visual artifacts on the inner frustum.
- L83 _public member_ `bool bEnabledMaxNumMips = false;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NDisplay Render", meta = (DisplayName = "Enable Maximum Number of Mips"))` — Performance: Allows a limited number of MIPs for high resolution.
- L87 _public member_ `int MaxNumMips = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NDisplay Render", meta = (DisplayName = "Maximum Number of Mips"))` — Performance: Use this value as the maximum number of MIPs for high resolution.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Postprocess.h` (Public)


#### struct `FDisplayClusterConfigurationViewport_CustomPostprocessSettings`  
`struct FDisplayClusterConfigurationViewport_CustomPostprocessSettings`  
_L17-37_
- reflection: `USTRUCT(Blueprintable)`
- L24 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Viewport")` — Enable custom postprocess
- L28 _public member_ `bool bIsOneFrame = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Viewport")` — Apply postprocess for one frame
- L32 _public member_ `FPostProcessSettings PostProcessSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Viewport")` — Custom postprocess settings
- L36 _public member_ `float BlendWeight = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NDisplay Viewport")` — Override blend weight

#### struct `FDisplayClusterConfigurationViewport_CustomPostprocess`  
`struct FDisplayClusterConfigurationViewport_CustomPostprocess`  
_L40-53_
- reflection: `USTRUCT()`
- L46 _public member_ `FDisplayClusterConfigurationViewport_CustomPostprocessSettings Start;` — `UPROPERTY()`
- L49 _public member_ `FDisplayClusterConfigurationViewport_CustomPostprocessSettings Override;` — `UPROPERTY()`
- L52 _public member_ `FDisplayClusterConfigurationViewport_CustomPostprocessSettings Final;` — `UPROPERTY()`

#### struct `FDisplayClusterConfigurationViewport_ColorGradingSettings`  
`struct FDisplayClusterConfigurationViewport_ColorGradingSettings`  
_L56-98_
- reflection: `USTRUCT(Blueprintable)`
- L60 _public function_ `FDisplayClusterConfigurationViewport_ColorGradingSettings() : bOverride_Saturation(false) , bOverride_Contrast(false) , bOverride_Gamma(false) , bOverride_Gain(false) , bOverride_Offset(false)`
- L69 _public member_ `uint8 bOverride_Saturation : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L71 _public member_ `uint8 bOverride_Contrast : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L73 _public member_ `uint8 bOverride_Gamma : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L75 _public member_ `uint8 bOverride_Gain : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L77 _public member_ `uint8 bOverride_Offset : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L81 _public member_ `FVector4 Saturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Grading", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", EditCondition = "bOverride_Saturation", ColorGradingMode = "saturation"))` — Saturation
- L85 _public member_ `FVector4 Contrast = FVector4(1.0f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Grading", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", EditCondition = "bOverride_Contrast", ColorGradingMode = "contrast"))` — Contrast
- L89 _public member_ `FVector4 Gamma = FVector4(1.0f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Grading", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", EditCondition = "bOverride_Gamma", ColorGradingMode = "gamma"))` — Gamma
- L93 _public member_ `FVector4 Gain = FVector4(1.0f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Grading", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", EditCondition = "bOverride_Gain", ColorGradingMode = "gain"))` — Gain
- L97 _public member_ `FVector4 Offset = FVector4(0.0f, 0.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Grading", meta = (UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", EditCondition = "bOverride_Offset", ColorGradingMode = "offset"))` — Offset

#### struct `FDisplayClusterConfigurationViewport_ColorGradingWhiteBalanceSettings`  
`struct FDisplayClusterConfigurationViewport_ColorGradingWhiteBalanceSettings`  
_L101-133_
- reflection: `USTRUCT(BlueprintType)`
- L105 _public function_ `FDisplayClusterConfigurationViewport_ColorGradingWhiteBalanceSettings() : bOverride_TemperatureType(0) , bOverride_WhiteTemp(0) , bOverride_WhiteTint(0)`
- L112 _public member_ `uint8 bOverride_TemperatureType:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L114 _public member_ `uint8 bOverride_WhiteTemp:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L116 _public member_ `uint8 bOverride_WhiteTint:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L128 _public member_ `float WhiteTemp = 6500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "White Balance", meta = (UIMin = "1500.0", UIMax = "15000.0", EditCondition = "bOverride_WhiteTemp", DisplayName = "Temp"))` — White temperature
- L132 _public member_ `float WhiteTint = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "White Balance", meta = (UIMin = "-1.0", UIMax = "1.0", EditCondition = "bOverride_WhiteTint", DisplayName = "Tint"))` — White tint

#### struct `FDisplayClusterConfigurationViewport_ColorGradingMiscSettings`  
`struct FDisplayClusterConfigurationViewport_ColorGradingMiscSettings`  
_L136-168_
- reflection: `USTRUCT(BlueprintType)`
- L140 _public function_ `FDisplayClusterConfigurationViewport_ColorGradingMiscSettings() : bOverride_BlueCorrection(0) , bOverride_ExpandGamut(0) , bOverride_SceneColorTint(0) , BlueCorrection(0) , ExpandGamut(0) , SceneColorTint(ForceInitToZero)`
- L151 _public member_ `uint8 bOverride_BlueCorrection:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L153 _public member_ `uint8 bOverride_ExpandGamut:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L155 _public member_ `uint8 bOverride_SceneColorTint:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L159 _public member_ `float BlueCorrection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverride_BlueCorrection"))` — Correct for artifacts with "electric" blues due to the ACEScg color space. Bright blue desaturates instead of going to violet.
- L163 _public member_ `float ExpandGamut;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", meta = (ClampMin = "0.0", UIMax = "1.0", EditCondition = "bOverride_ExpandGamut"))` — Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering.
- L167 _public member_ `FLinearColor SceneColorTint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Misc", meta = (EditCondition = "bOverride_SceneColorTint", HideAlphaChannel))` — Scene tint color

#### struct `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings`  
`struct FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings`  
_L171-239_
- reflection: `USTRUCT(BlueprintType)`
- L175 _public function_ `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings() : bOverride_AutoExposureBias(0) , bOverride_ColorCorrectionHighlightsMin(0) , bOverride_ColorCorrectionHighlightsMax(0) , bOverride_ColorCorrectionShadowsMax(0) , Global() , Shadows() , ColorCorrectionShadowsMax(0) , Midtones() , Highlights() , ColorCorrectionHighlightsMin(0) , ColorCorrectionHighlightsMax(1)`
- L191 _public member_ `uint8 bOverride_AutoExposureBias:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L193 _public member_ `uint8 bOverride_ColorCorrectionHighlightsMin:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L195 _public member_ `uint8 bOverride_ColorCorrectionHighlightsMax:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L197 _public member_ `uint8 bOverride_ColorCorrectionShadowsMax:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L201 _public member_ `float BlendWeight = 1.0f;` — `UPROPERTY()` — Not Implemented: Blend weight
- L205 _public member_ `float AutoExposureBias = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (UIMin = "-15.0", UIMax = "15.0", EditCondition = "bOverride_AutoExposureBias", DisplayName = "Exposure Compensation"))` — Exposure compensation
- L209 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingWhiteBalanceSettings WhiteBalance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — White balance
- L213 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingSettings Global;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — Global color grading
- L217 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingSettings Shadows;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — Shadows color grading
- L220 _public member_ `float ColorCorrectionShadowsMax;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (UIMin = "-1.0", UIMax = "1.0", EditCondition = "bOverride_ColorCorrectionShadowsMax", DisplayName = "ShadowsMax"))`
- L224 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingSettings Midtones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — Midtones color grading
- L228 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingSettings Highlights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — Highlights color grading
- L231 _public member_ `float ColorCorrectionHighlightsMin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (UIMin = "-1.0", UIMax = "1.0", EditCondition = "bOverride_ColorCorrectionHighlightsMin", DisplayName = "HighlightsMin"))`
- L234 _public member_ `float ColorCorrectionHighlightsMax;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (UIMin = "1.0", UIMax = "10.0", EditCondition = "bOverride_ColorCorrectionHighlightsMax", DisplayName = "HighlightsMax"))`
- L238 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingMiscSettings Misc;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")` — Highlights color grading misc settings

#### struct `FDisplayClusterConfigurationViewport_EntireClusterColorGrading`  
`struct FDisplayClusterConfigurationViewport_EntireClusterColorGrading`  
_L243-254_
- reflection: `USTRUCT(Blueprintable)`
- L249 _public member_ `bool bEnableEntireClusterColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Enable Entire Cluster Color Grading"))` — Enable the color grading settings for the entire cluster and add them to nDisplay's color grading stack.  This will affect both the viewports and inner frustum.
- L253 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings ColorGradingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Color Grading"))` — Entire Cluster Color Grading

#### struct `FDisplayClusterConfigurationViewport_PerViewportColorGrading`  
`struct FDisplayClusterConfigurationViewport_PerViewportColorGrading`  
_L257-281_
- reflection: `USTRUCT(Blueprintable)`
- L263 _public member_ `FText Name = FText::GetEmpty();` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L268 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Enable Per-Viewport Color Grading"))` — Enable the color grading settings for the viewport(s) specified and add them to nDisplay's color grading stack.  This will not affect the inner frustum.
- L272 _public member_ `bool bIsEntireClusterEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Include Entire Cluster Color Grading"))` — Optionally include the Entire Cluster Color Grading settings specified above in nDisplay's color grading stack for these viewports.
- L276 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings ColorGradingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Color Grading"))` — Color Grading
- L280 _public member_ `TArray<FString> ApplyPostProcessToObjects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Viewport Settings", meta = (DisplayName = "Apply Color Grading to Viewports"))` — Specify the viewports to apply these color grading settings.

#### struct `FDisplayClusterConfigurationViewport_AllNodesColorGrading`  
`struct FDisplayClusterConfigurationViewport_AllNodesColorGrading`  
_L284-299_
- reflection: `USTRUCT(Blueprintable)`
- L290 _public member_ `bool bEnableInnerFrustumAllNodesColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Enable All Nodes Color Grading"))` — Enable the color grading settings on the inner frustum for the all nodes and add them to nDisplay's color grading stack.
- L294 _public member_ `bool bEnableEntireClusterColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Color Grading", meta = (DisplayName = "Include Entire Cluster Color Grading"))` — Optionally include Entire Cluster Color Grading settings specified on the root actor in nDisplay's color grading stack for the inner frustum.
- L298 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings ColorGradingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Color Grading"))` — Color Grading

#### struct `FDisplayClusterConfigurationViewport_PerNodeColorGrading`  
`struct FDisplayClusterConfigurationViewport_PerNodeColorGrading`  
_L302-330_
- reflection: `USTRUCT(Blueprintable)`
- L308 _public member_ `FText Name = FText::GetEmpty();` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L313 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Enable Per-Node Color Grading"))` — Enable the color grading settings for the node(s) specified and add them to nDisplay's color grading stack.
- L317 _public member_ `bool bEntireClusterColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Include Entire Cluster Color Grading"))` — Optionally include Entire Cluster Color Grading settings specified on the root actor in nDisplay's color grading stack for these nodes.
- L321 _public member_ `bool bAllNodesColorGrading = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Include All Nodes Color Grading"))` — Optionally include the All Nodes Color Grading settings specified above in nDisplay's color grading stack for these nodes.
- L325 _public member_ `FDisplayClusterConfigurationViewport_ColorGradingRenderingSettings ColorGradingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings", meta = (DisplayName = "Color Grading"))` — Color Grading
- L329 _public member_ `TArray<FString> ApplyPostProcessToObjects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Viewport Settings", meta = (DisplayName = "Apply Color Grading to Nodes"))` — Specify the nodes to apply these color grading settings.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Tile.h` (Public)


#### struct `FDisplayClusterConfigurationTile_Settings`  
`struct FDisplayClusterConfigurationTile_Settings`  
_L16-35_
- reflection: `USTRUCT(Blueprintable)`
- desc: Tile rendering
- L22 _public prototype_ `bool IsEnabled(const struct FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Return true if tile rendering can be used.
- L25 _public prototype_ `static bool IsValid(const FIntPoint& InTilesLayout);` — Layout validation.
- L30 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Rendering")` — Enable tile rendering.
- L34 _public member_ `FIntPoint Layout = { 1, 1 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Rendering", meta = (ClampMin = "1", ClampMax = "4"))` — Tiling layout (X by Y tiles amount).

#### struct `FDisplayClusterConfigurationTile_Overscan`  
`struct FDisplayClusterConfigurationTile_Overscan`  
_L38-71_
- reflection: `USTRUCT(Blueprintable)`
- L45 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "Enable Tile Overscan"))` — Enable/disable Viewport Overscan and specify units as percent or pixel values.
- L49 _public member_ `bool bOversize = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "Adapt Resolution", EditCondition = "bEnabled == true"))` — Set to True to render at the overscan resolution, set to false to render at the resolution in the configuration and scale for overscan.
- L54 _public member_ `bool bOptimizeTileOverscan = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "No Overscan For Edges", EditCondition = "bEnabled == true"))` — Optimize overscan values on boundary tiles. When enabled, tile sides not in contact with other tiles will use zero overscan.
- L58 _public member_ `EDisplayClusterConfigurationViewportOverscanMode Mode = EDisplayClusterConfigurationViewportOverscanMode::Percent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "Overscan Units", EditCondition = "bEnabled == true"))` — Enable/disable Viewport Overscan and specify units as percent or pixel values.
- L62 _public member_ `float AllSides = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "Overscan Value", EditCondition = "bEnabled == true"))` — Overscan value for all sides.
- L70 _public member_ `EDisplayClusterConfigurationViewportOverscanBlendMode OverscanBlendMode = EDisplayClusterConfigurationViewportOverscanBlendMode::Percent50;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Overscan", meta = (DisplayName = "Blend Mode", EditCondition = "bEnabled == true"))` — Defines how the overscan blend width is interpreted. Allows blending between tiles to be specified in a percentage of the overscan size, or disabled entirely.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Upscaler.h` (Public)


#### struct `FDisplayClusterConfigurationUpscalerSettings`  
`struct FDisplayClusterConfigurationUpscalerSettings`  
_L29-55_
- reflection: `USTRUCT(BlueprintType)`
- desc: Upscaler settings. MethodName  - refers to one of the available methods EditingData - Editable data for selected Method. FInstancedPropertyBag is an abstract container and is not handled on the nDisplay side. MethodName is customized as a drop-down list where items are taken from: - EDisplayClusterConfigurationUpscalingMethod enum elements - Upscalers exposed in the IUpscalerModularFeature interface. Data logic are implemented in the FDisplayClusterConfigurationUpscalerSettingsDetailCustomization. The initial structure FInstancedPropertyBag is derived by the IUpscalerModularFeature::GetSettings().
- L35 _public prototype_ `bool GetUpscalerSettings( const FDisplayClusterConfigurationUpscalerSettings* InDefaultUpscalerSettings, FDisplayClusterUpscalerSettings& OutUpscalerSettings) const;` — Get upscaler settings.
- L42 _public member_ `FName MethodName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upscaler", meta = (DisplayName = "Upscaling Method"))` — Override the Upscaling method.
- L46 _public member_ `FInstancedPropertyBag EditingData;` — `UPROPERTY(EditAnywhere, Category = "Upscaler", meta = (DisplayName = "Upscaling Settings"))` — Upscaling method settings.
- L54 _public member_ `TArray<FGuid> ParameterOverrideGuids;` — `UPROPERTY()` — In cases where these upscaler settings are overriding global upscaler settings, this list stores the IDs of the properties that will override the global settings. These are exposed and utilized when the owner of the UpscalerSettings struct uses the WithOverrides metadata specifier

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_Viewport.h` (Public)


#### struct `FDisplayClusterConfigurationViewport_ICVFX`  
`struct FDisplayClusterConfigurationViewport_ICVFX`  
_L37-94_
- reflection: `USTRUCT(BlueprintType)`
- desc: Unique ICVFX customisation for each viewport. Must be processed in UDisplayClusterConfigurationViewport::GetViewportICVFXFlags(). This will result in some EDisplayClusterViewportICVFXFlags being raised.
- L44 _public function_ `EDisplayClusterShaderParametersICVFX_LightCardRenderMode GetLightCardRenderMode(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const` — `UE_DEPRECATED(5.5, "This function has been moved to FDisplayClusterConfigurationICVFX_LightcardSettings.")` — Get lightcard render mode for this viewport.
- L51 _public function_ `EDisplayClusterViewportICVFXFlags GetViewportICVFXFlags(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const` — `UE_DEPRECATED(5.5, "This function has been moved to UDisplayClusterConfigurationViewport.")` — Get ICVFX settings flags for viewport
- L56 _public prototype_ `EDisplayClusterConfigurationICVFX_OverrideChromakeyType GetOverrideChromakeyType(const FString& CameraId) const;`
- L61 _public member_ `bool bAllowICVFX = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Enable in-camera VFX for this Viewport (works only with supported Projection Policies)
- L65 _public member_ `bool bAllowInnerFrustum = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Allow the inner frustum to appear on this Viewport
- L69 _public member_ `EDisplayClusterConfigurationICVFX_OverrideCameraRenderMode CameraRenderMode = EDisplayClusterConfigurationICVFX_OverrideCameraRenderMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Disable incamera render to this viewport
- L73 _public member_ `EDisplayClusterConfigurationICVFX_OverrideLightcardRenderMode LightcardRenderMode = EDisplayClusterConfigurationICVFX_OverrideLightcardRenderMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Use unique lightcard mode for this viewport
- L77 _public member_ `EDisplayClusterConfigurationICVFX_OverrideChromakeyType OverrideChromakeyType = EDisplayClusterConfigurationICVFX_OverrideChromakeyType::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Use unique chromakey type for this viewport
- L81 _public member_ `TMap<FString, EDisplayClusterConfigurationICVFX_OverrideChromakeyType> PerCameraOverrideChromakeyType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Determines the chromakey override per-camera in this viewport.
- L89 _public member_ `TArray<FString> EnforcedCameraOrder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — Enforced rendering order for ICVFX cameras on this viewport. Cameras listed here will be rendered in this order (index 0 is composed on top). Cameras not in this list will be composed below, in their default order based on RenderOrder property. If empty, all cameras use default render order.
- L93 _public member_ `bool bReverseCameraPriority = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX")` — The order in which the ICVFX cameras are composited over is reversed. Useful for time-multiplexed displays.

#### struct `FDisplayClusterConfigurationViewport_RenderSettings`  
`struct FDisplayClusterConfigurationViewport_RenderSettings`  
_L97-166_
- reflection: `USTRUCT(Blueprintable)`
- L108 _public member_ `bool bEnableCrossGPUTransfer = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Enable Cross-GPU Transfer"))` — Enable cross-GPU transfer for this viewport. It may be disabled in some configurations. For example, when using offscreen rendering with TextureShare, cross-gpu transfer can be disabled for this viewport to improve performance, because when transfer is called, it freezes the GPUs until synchronization is reached. (TextureShare uses its own implementation of the crossGPU transfer for the shared textures.)
- L116 _public member_ `int StereoGPUIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Stereo", meta = (DisplayName = "Stereo GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the nDisplay viewport in stereo rendering for the second eye. A value of '-1' means to use the value from the GPU Index parameter. (the same value is used for both eyes). Used to improve rendering performance by spreading the load across multiple GPUs.
- L120 _public member_ `EDisplayClusterConfigurationViewport_StereoMode StereoMode = EDisplayClusterConfigurationViewport_StereoMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo")` — Enables and sets Stereo mode
- L124 _public member_ `FDisplayClusterConfigurationUpscalerSettings UpscalerSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Upscaler Settings", NoResetToDefault, WithOverrides))` — Upscaler settings for the viewport.
- L128 _public member_ `float BufferRatio = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "Screen Percentage", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10.0", UIMax = "1.0"))` — Adjust resolution scaling for an individual viewport.  Viewport Screen Percentage Multiplier is applied to this value.
- L132 _public member_ `float RenderTargetRatio = 1.f;` — `UPROPERTY()` — Adjust resolution scaling for an individual viewport.  Viewport Screen Percentage Multiplier is applied to this value.
- L135 _public member_ `FDisplayClusterConfigurationViewport_CustomPostprocess CustomPostprocess;` — `UPROPERTY()`
- L139 _public member_ `FDisplayClusterConfigurationPostRender_Override Replace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Replacement")` — Override viewport render from source texture
- L143 _public member_ `FDisplayClusterConfigurationPostRender_BlurPostprocess PostprocessBlur;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", AdvancedDisplay)` — Add postprocess blur to viewport
- L147 _public member_ `FDisplayClusterConfigurationPostRender_GenerateMips GenerateMips;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", AdvancedDisplay)` — Generate Mips texture for this viewport (used, only if projection policy supports this feature)
- L151 _public member_ `FDisplayClusterConfigurationViewport_Overscan Overscan;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — Render a larger frame than specified in the configuration to achieve continuity across displays when using post-processing effects.
- L155 _public member_ `FDisplayClusterConfigurationICVFX_VisibilityList HiddenContent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — Override actor visibility for this viewport.
- L159 _public member_ `FDisplayClusterConfigurationMediaViewport Media;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media", meta = (DisplayName = "Media", ShowOnlyInnerProperties))` — Media settings
- L164 _public member_ `int RenderFamilyGroup = -1;` — `UPROPERTY()` — Experimental: Support special frame builder mode - merge viewports to single viewfamily by group num [not implemented yet]

#### class `UDisplayClusterConfigurationViewport`  
`class UDisplayClusterConfigurationViewport : public UDisplayClusterConfigurationData_Base`  
_L170-298_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UDisplayClusterConfigurationData_Base`
- L176 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`
- L178 _public member_ `FOnPostEditChangeChainProperty OnPostEditChangeChainProperty;`
- L181 _public prototype_ `UDisplayClusterConfigurationViewport();`
- L185 _public prototype_ `virtual void PostLoad() override;`
- L188 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L189 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L194 _public prototype_ `void GetReferencedMeshNames(TArray<FString>& OutMeshNames) const;`
- L197 _public function_ `bool IsViewportEnabled() const` — The viewport object will only be created or updated if this function returns true.
- L203 _public prototype_ `EDisplayClusterViewportICVFXFlags GetViewportICVFXFlags(const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings) const;` — Get ICVFX settings flags for viewport
- L206 _public prototype_ `EDisplayClusterShaderParametersICVFX_ChromakeySource GetViewportChromakeyType( const FDisplayClusterConfigurationICVFX_StageSettings& InStageSettings, const FString& InCameraId, const struct FDisplayClusterConfigurationICVFX_CameraSettings& InCameraSettings) const;` — Returns the chromakey type for this viewport used by the specified ICVFX camera.
- L213 _public prototype_ `void EnablePreviewTexture();` — Enable the preview texture. Only should be called by the object managing the preview texture state.
- L219 _public prototype_ `bool DisablePreviewTexture();` — Signal that the preview texture should be disabled. @return True if the preview texture was disabled. False if it was already disabled.
- L222 _public function_ `bool IsPreviewTextureAllowed() const` — If this viewport is allowed to render a preview texture. Used with resizing viewports.
- L225 _protected prototype_ `virtual void OnPreCompile(class FCompilerResultsLog& MessageLog) override;`
- L229 _private member_ `bool bAllowPreviewTexture = true;` — If this viewport is allowed to render a preview texture.
- L232 _private member_ `bool bIsManagingPreviewTexture = false;` — If this object is managing the preview texture state.
- L238 _public member_ `bool bAllowRendering = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Enable Viewport"))` — Enables or disables rendering of this specific Viewport
- L242 _public member_ `FString Camera;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "View Point"))` — Reference to the nDisplay View Point
- L246 _public member_ `FDisplayClusterConfigurationProjection ProjectionPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Configuration")` — Specify your Projection Policy Settings
- L250 _public member_ `FString DisplayDeviceName;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (DisplayName = "Display Device"))` — Select a display device to use during preview. An empty string will use the default display device
- L253 _public member_ `bool bAllowPreviewFrustumRendering = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview", meta = (DisplayName = "Preview Frustum"))`
- L257 _public member_ `FDisplayClusterConfigurationRectangle Region;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayMode = "Compound", FixedAspectRatioProperty = "bFixedAspectRatio"))` — Define the Viewport 2D coordinates
- L261 _public member_ `FDisplayClusterConfigurationViewport_Remap ViewportRemap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Remapping"))` — Define the Viewport Remap settings
- L265 _public member_ `int OverlapOrder = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Allows Viewports to overlap and sets Viewport overlapping order priority
- L273 _public member_ `int GPUIndex = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (DisplayName = "GPU Index", ClampMin = "-1", UIMin = "-1", ClampMax = "8", UIMax = "8"))` — Specifies the GPU index for the nDisplay viewport. Value '-1' means do not use multi-GPU Used to improve rendering performance by spreading the load across multiple GPUs.
- L277 _public member_ `FDisplayClusterConfigurationViewport_RenderSettings RenderSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (ShowOnlyInnerProperties))` — Configure render for this viewport
- L281 _public member_ `FDisplayClusterConfigurationViewport_ICVFX ICVFX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "In Camera VFX", meta = (ShowOnlyInnerProperties))` — Configure ICVFX for this viewport
- L286 _public member_ `bool bFixedAspectRatio;` — `UPROPERTY(EditAnywhere, Category = "Configuration", meta = (HideProperty))` — Locks the Viewport aspect ratio for easier resizing
- L289 _public member_ `bool bIsUnlocked = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (HideProperty))`
- L292 _public member_ `bool bIsVisible = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (HideProperty))`
- L296 _public member_ `static const float ViewportMinimumSize;`
- L297 _public member_ `static const float ViewportMaximumSize;`

#### struct `FDisplayClusterConfigurationRenderFrame`  
`struct FDisplayClusterConfigurationRenderFrame`  
_L302-352_
- reflection: `USTRUCT(Blueprintable)`
- desc: This struct now stored in UDisplayClusterConfigurationData, and replicated with MultiUser
- L310 _public member_ `bool bAllowRenderTargetAtlasing = false;` — `UPROPERTY()` — Performance: Allow merge multiple viewports on single RTT with atlasing (required for bAllowViewFamilyMergeOptimization) [not implemented yet] Experimental
- L315 _public member_ `EDisplayClusterConfigurationRenderFamilyMode ViewFamilyMode = EDisplayClusterConfigurationRenderFamilyMode::None;` — `UPROPERTY()` — Performance: Allow viewfamily merge optimization (render multiple viewports contexts within single family) [not implemented yet] Experimental
- L321 _public member_ `bool bShouldUseParentViewportRenderFamily = false;` — `UPROPERTY()` — Performance: Allow to use parent ViewFamily from parent viewport (icvfx has child viewports: lightcard and chromakey with prj_view matrices copied from parent viewport. May sense to use same viewfamily?) [not implemented yet] Experimental
- L325 _public member_ `float ClusterRenderTargetRatioMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Global RTT Size Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "10"))` — Multiplies the RTT size of all viewports within nDisplay by this value.
- L329 _public member_ `float ClusterICVFXInnerViewportRenderTargetRatioMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Inner Frustum RTT Size Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "10"))` — Multiplies the RTT size of the ICVFX Inner Frustum viewports by this value.
- L334 _public member_ `float ClusterICVFXOuterViewportRenderTargetRatioMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Viewports RTT Size Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "10"))` — Multiplies the RTT size of the viewports by this value. (Excluding ICVFX internal viewports such as Inner frustum, LightCards, Chromakey, etc.)
- L338 _public member_ `float ClusterBufferRatioMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Global Screen Percentage Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "10"))` — Multiplies all screen percentages within nDisplay by this value.
- L342 _public member_ `float ClusterICVFXInnerFrustumBufferRatioMult = 1.f;` — `UPROPERTY(BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Inner Frustum Screen Percentage Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "10"))` — Multiplies the screen percentage for all ICVFX Inner Frustum viewports by this value.
- L347 _public member_ `float ClusterICVFXOuterViewportBufferRatioMult = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NDisplay, meta = (DisplayName = "Viewports Screen Percentage Multiplier", ClampMin = "0.05", UIMin = "0.05", ClampMax = "10", UIMax = "1"))` — Multiplies the screen percentage for viewports by this value. (Excluding ICVFX internal viewports such as Inner Frustum, LightCards and Chromakey.)
- L351 _public member_ `bool bAllowWarpBlend = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — Allow warpblend render

#### Free symbols / members of external scopes

- L176 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostEditChangeChainProperty, const FPropertyChangedChainEvent&);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_ViewportOverscan.h` (Public)


#### struct `FDisplayClusterConfigurationViewport_Overscan`  
`struct FDisplayClusterConfigurationViewport_Overscan`  
_L15-47_
- reflection: `USTRUCT(Blueprintable)`
- L22 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan", meta = (DisplayName = "Enable"))` — Enable/disable Viewport Overscan and specify units as percent or pixel values.
- L26 _public member_ `EDisplayClusterConfigurationViewportOverscanMode Mode = EDisplayClusterConfigurationViewportOverscanMode::Percent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan")` — Enable/disable Viewport Overscan and specify units as percent or pixel values.
- L30 _public member_ `float Left = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan")` — Left
- L34 _public member_ `float Right = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan")` — Right
- L38 _public member_ `float Top = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan")` — Top
- L42 _public member_ `float Bottom = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan")` — Bottom
- L46 _public member_ `bool bOversize = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overscan", meta = (DisplayName = "Adapt Resolution", DisplayAfter = "Mode"))` — Set to True to render at the overscan resolution, set to false to render at the resolution in the configuration and scale for overscan.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes_ViewportRemap.h` (Public)


#### struct `FDisplayClusterConfigurationViewport_RemapData`  
`struct FDisplayClusterConfigurationViewport_RemapData`  
_L19-53_
- reflection: `USTRUCT(Blueprintable)`
- desc: Remapping configuration for a single remapped region, which can be any subregion of a viewport, and can be remapped to any part of the screen, and can be rotated or flipped
- L26 _public member_ `FDisplayClusterConfigurationRectangle ViewportRegion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — The subregion of the viewport to remap; (0,0) x (W, H) will remap the entire viewport
- L30 _public member_ `FDisplayClusterConfigurationRectangle OutputRegion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — The region in screen space to output the remapped region to
- L34 _public member_ `float Angle = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — The angle in degrees to rotate the remapped region by; rotation is performed around the center of the output region
- L38 _public member_ `bool bFlipH = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — Flips the remapped region horizontally
- L42 _public member_ `bool bFlipV = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")` — Flips the remapped region vertically
- L46 _public prototype_ `bool IsValid() const;` — Determines if the remap has non-trivial transformations to apply to a viewport
- L49 _public prototype_ `bool IsRotating() const;` — Determines if the remap has a non-trivial rotation to apply to the viewport
- L52 _public prototype_ `bool IsFlipping() const;` — Determines if the remap is applying a flip to the viewport

#### struct `FDisplayClusterConfigurationViewport_Remap`  
`struct FDisplayClusterConfigurationViewport_Remap`  
_L57-73_
- reflection: `USTRUCT(Blueprintable)`
- desc: Configuration for all remapping to apply to a single viewport
- L64 _public member_ `bool bEnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Enable Output Remapping"))` — Enables or disables viweport output remapping
- L68 _public member_ `FDisplayClusterConfigurationViewport_RemapData BaseRemap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (NoHeader, Simplified, AngleInterval = "90"))` — The base remap to apply to the entire viewport, used to apply flipping and rotation to the viewport
- L72 _public member_ `TArray<FDisplayClusterConfigurationViewport_RemapData> RemapRegions;` — `UPROPERTY()` — Additional remaps to apply to the viewport, can be used to subdivide the viewport into multiple outputs. Experimental, not exposed to users at this time

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationVersion.h` (Public)


#### enum `EDisplayClusterConfigurationVersion`  
`enum class EDisplayClusterConfigurationVersion : uint8`  
_L7-13_
- L9 _public enumerator_ `Unknown` — Unknown version or not a config file
- L10 _public enumerator_ `Version_426` — 4.26 JSON based config format
- L11 _public enumerator_ `Version_427` — 4.27 JSON based config format
- L12 _public enumerator_ `Version_500` — 5.00 JSON based config format

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DisplayClusterConfiguration`
- L17 _function_ `static constexpr const TCHAR* GetCurrentConfigurationSchemeMarker()` (scope `DisplayClusterConfiguration`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterEditorPropertyReference.h` (Public)


#### struct `FDisplayClusterEditorPropertyReference`  
`struct FDisplayClusterEditorPropertyReference`  
_L26-29_
- reflection: `USTRUCT()`
- desc: A dummy structure used to reference properties of subobjects to be displayed at the root level in a details panel. When placed within an Unreal class or struct, the property reference is replaced with the referenced property in the type's details panel. The display name, tooltip, category, and accessiblity of the property reference will be applied to the referenced property when provided, overwriting the property's own specifiers. If the property path contains lists (arrays, maps, or sets), then each element of the list will be iterated over, and all properties within that list will be displayed together in a group. Use the PropertyPath metadata specifier to specify the path to the referenced property, relative to the object that owns the property reference. Additionally, this type supports using property paths within its EditCondition specifier, allowing the edit condition of the referenced property within a details panel to depend on other referenced properties. The && operator is supported, allowing multiple property paths to be used to construct the edit condition.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/IDisplayClusterConfiguration.h` (Public)


#### class `IDisplayClusterConfiguration`  
`class IDisplayClusterConfiguration : public IModuleInterface`  
_L17-97_
- inherits: `IModuleInterface`
- desc: Display Cluster configuration module interface
- L20 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L23 _public prototype_ `virtual ~IDisplayClusterConfiguration() = default;`
- L32 _public function_ `static inline IDisplayClusterConfiguration& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L52 _public prototype_ `virtual void SetIsSnapshotTransacting(bool bIsSnapshot) = 0;` — Sets the transaction flags so that we don't necessarily re-run the construction scripts all the time.
- L57 _public prototype_ `virtual bool IsTransactingSnapshot() const = 0;` — Gets the current transaction snapshot status.
- L66 _public prototype_ `virtual EDisplayClusterConfigurationVersion GetConfigVersion(const FString& FilePath) = 0;` — Returns version of a specified config file @param FilePath   - Config file path @return Config version if succeeded, otherwise nulltpr
- L76 _public prototype_ `virtual UDisplayClusterConfigurationData* LoadConfig(const FString& FilePath, UObject* Owner = nullptr) = 0;` — Load configuration data from specified file @param FilePath   - Config file path @param Owner      - UObject owner for the configuration data object @return Configuration data if succeeded, otherwise nulltpr
- L86 _public prototype_ `virtual bool SaveConfig(const UDisplayClusterConfigurationData* Config, const FString& FilePath) = 0;` — Save configuration data to a specified file @param Config - Configuration data @param FilePath - File to save @return true if succeeded
- L96 _public prototype_ `virtual bool ConfigAsString(const UDisplayClusterConfigurationData* Config, FString& OutString) const = 0;` — Converts configuration data to string @param Config - Configuration data @param OutString - String to contain the configuration data @return true if succeeded
