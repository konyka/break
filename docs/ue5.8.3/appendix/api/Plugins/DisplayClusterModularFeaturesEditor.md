# Plugins / DisplayClusterModularFeaturesEditor

- module root: `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterModularFeaturesEditor`
- headers: 1; symbols: 24
- symbol kinds: class=1, enum=2, enumerator=8, member=5, prototype=7, struct=1
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterModularFeaturesEditor/Public/IDisplayClusterModularFeatureMediaInitializer.h` (Public)


#### struct `FMediaObjectOwnerInfo`  
`struct FMediaObjectOwnerInfo`  
_L11-40_
- desc: Container to carry the info about media object's owner
- L25 _public member_ `FString OwnerName;` — Owner name (ICVFX camera component name, viewport or node name)
- L28 _public member_ `EMediaObjectOwnerType OwnerType;` — Owner type (ICVFX camera component name, viewport or node name)
- L31 _public member_ `TOptional<uint8> ClusterNodeUniqueIdx;` — Optional unique index of the cluster node holding the owner object
- L39 _public member_ `uint8 OwnerUniqueIdx = 0;` — Unique index of the owner Camera     - within a config Viewport   - within a cluster node Backbuffer - within a config

#### enum `FMediaObjectOwnerInfo::EMediaObjectOwnerType`  
`enum class EMediaObjectOwnerType : uint8`  
_L16-21_
- desc: Type of the media object's owner
- L18 _public enumerator_ `ICVFXCamera = 0`
- L19 _public enumerator_ `Viewport`
- L20 _public enumerator_ `Backbuffer`

#### enum `EMediaStreamPropagationType`  
`enum class EMediaStreamPropagationType : uint8`  
_L45-52_
- desc: Media stream propagation types
- L47 _public enumerator_ `None = 0`
- L48 _public enumerator_ `LocalUnicast = 1 << 0` — Single sender and single receiver within the same host
- L49 _public enumerator_ `LocalMulticast = 1 << 1` — Single sender and multiple receivers within the same host
- L50 _public enumerator_ `Unicast = 1 << 2` — Single sender and single receiver on different hosts
- L51 _public enumerator_ `Multicast = 1 << 3` — Single sender and multiple receivers on different hosts

#### class `IDisplayClusterModularFeatureMediaInitializer`  
`class IDisplayClusterModularFeatureMediaInitializer : public IModularFeature`  
_L59-115_
- inherits: `IModularFeature`
- desc: Base class for nDisplay media initializer implementations.
- L64 _public member_ `static const FName ModularFeatureName;` — Public feature name
- L68 _public prototype_ `virtual ~IDisplayClusterModularFeatureMediaInitializer() = default;`
- L78 _public prototype_ `virtual bool IsMediaObjectSupported(const UObject* MediaObject) = 0;` — Checks if media object is supported by the initializer @param MediaObject - UMediaSource or UMediaOutput instance @return true if media object supported
- L87 _public prototype_ `virtual bool AreMediaObjectsCompatible(const UObject* MediaSource, const UObject* MediaOutput) = 0;` — Checks if media source and output are compatible and can be paired @param MediaSource - UMediaSource instance @param MediaOutput - UMediaOutput instance @return true if media objects are compatible with each other
- L97 _public prototype_ `virtual bool GetSupportedMediaPropagationTypes(const UObject* MediaSource, const UObject* MediaOutput, EMediaStreamPropagationType& OutPropagationTypes) = 0;` — Provides stream supported media propagation types (local/global, unicast/multicast, etc.) @param MediaSource - UMediaSource instance @param MediaOutput - UMediaOutput instance @param OutPropagationTypes - [out] supported types mask @return false if media objects are invalid, incompatible or not supported
- L106 _public prototype_ `virtual void InitializeMediaObjectForTile(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo, const FIntPoint& TilePos) = 0;` — Performs initialization of a media object for tiled input/output @param MediaObject - UMediaSource or UMediaOutput instance @param OwnerInfo   - Additional information about the object holding the media object @param TilePos     - Tile XY-position
- L114 _public prototype_ `virtual void InitializeMediaObjectForFullFrame(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo) = 0;` — Performs initialization of a media object for full frame input/output @param MediaObject - UMediaSource or UMediaOutput instance @param OwnerInfo   - Additional information about the object holding the media object

#### Free symbols / members of external scopes

- L53 _prototype_ `ENUM_CLASS_FLAGS(EMediaStreamPropagationType);`
