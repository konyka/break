# Programs / UnrealLightmass

- module root: `Source/Programs/UnrealLightmass`
- headers: 45; symbols: 3064
- symbol kinds: class=150, delegate=1, enum=30, enumerator=81, externvar=8, function=602, macro=78, member=1419, namespace=43, prototype=430, struct=112, typedef=35, union=9, variable=66
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Messaging, Networking, Projects, Sockets, SwarmInterface, UdpMessaging, zlib
- PrivateIncludePathModuleNames: Messaging
- PublicDependencyModuleNames: Embree, IntelTBB
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealLightmass/Private/CPUSolver/CPUSolver.h` (Private)


#### struct `Lightmass::FThreadStatistics`  
`struct FThreadStatistics`  
_L21-52_
- desc: Helper struct that contain global statistics for the Lightmass thread execution.
- L23 _public function_ `FThreadStatistics() : TotalTime(0.0) , RequestTime(0.0) , ExportTime(0.0) , TextureMappingTime(0.0) , RequestTimeoutTime(0.0) , SwarmRequestTime(0.0) , NumTextureMappings(0)`
- L34 _public function_ `void operator+=( const FThreadStatistics& Other )`
- L45 _public member_ `double TotalTime;`
- L46 _public member_ `double RequestTime;`
- L47 _public member_ `double ExportTime;`
- L48 _public member_ `double TextureMappingTime;`
- L49 _public member_ `double RequestTimeoutTime;`
- L50 _public member_ `double SwarmRequestTime;`
- L51 _public member_ `int32 NumTextureMappings;`

#### struct `Lightmass::FGlobalStatistics`  
`struct FGlobalStatistics`  
_L55-93_
- desc: Helper struct that contain global statistics for the Lightmass execution.
- L57 _public function_ `FGlobalStatistics() : NumThreads(0) , NumThreadsFinished(0) , NumTotalMappings(0) , NumExportedMappings(0) , TotalTimeStart(0.0) , TotalTimeEnd(0.0) , ImportTimeStart(0.0) , ImportTimeEnd(0.0) , PhotonsStart(0.0) , PhotonsEnd(0.0) , WorkTimeStart(0.0) , WorkTimeEnd(0.0) , ExtraExportTime(0.0) , SendMessageTime(0.0) , SceneSetupTime(0.0)`
- L75 _public member_ `FThreadStatistics ThreadStatistics;`
- L76 _public member_ `int32 NumThreads;`
- L77 _public member_ `volatile int32 NumThreadsFinished;` — Incremented by each thread when they finish.
- L78 _public member_ `int32 NumTotalMappings;`
- L79 _public member_ `int32 NumExportedMappings;` — Only incremented while threads are still running.
- L80 _public member_ `double TotalTimeStart;`
- L81 _public member_ `double TotalTimeEnd;`
- L82 _public member_ `double ImportTimeStart;`
- L83 _public member_ `double ImportTimeEnd;`
- L84 _public member_ `double PhotonsStart;`
- L85 _public member_ `double PhotonsEnd;`
- L86 _public member_ `double WorkTimeStart;`
- L87 _public member_ `double WorkTimeEnd;`
- L88 _public member_ `double ExtraExportTime;`
- L90 _public member_ `double SendMessageTime;` — Time spent in SendMessage(), in seconds.
- L92 _public member_ `double SceneSetupTime;` — Time spent setting up the scene, in seconds.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Lightmass`
- L18 _prototype_ `void BuildStaticLighting(const FGuid& SceneGuid, int32 NumThreads, bool bDumpTextures);` (scope `Lightmass`) — Entry point for starting the static lighting process @param SceneGuid		Guid of the scene to process @param NumThreads	Number of concurrent threads to use for lighting building @param bDumpTextures	If true, 2d lightmaps will be dumped to
- L96 _externvar_ `extern FGlobalStatistics GStatistics;` (scope `Lightmass`) — Global statistics
- L99 _externvar_ `extern class FLightmassSwarm* GSwarm;` (scope `Lightmass`) — Global Swarm instance.
- L102 _externvar_ `extern bool GReportDetailedStats;` (scope `Lightmass`) — Whether we should report detailed stats back to Unreal.
- L108 _externvar_ `extern bool GDebugMode;` (scope `Lightmass`) — Whether Lightmass is running in debug mode (-debug), using a hardcoded job and not requesting tasks from Swarm. Warning!  This will only process mapping tasks and will skip other types of tasks.

### `Source/Programs/UnrealLightmass/Private/ImportExport/Exporter.h` (Private)


#### class `Lightmass::FLightmassSolverExporter`  
`class FLightmassSolverExporter`  
_L19-80_
- desc: @todo - need to pass to Serialization
- L28 _public prototype_ `FLightmassSolverExporter( class FLightmassSwarm* InSwarm, const FScene& InScene, bool bInDumpTextures );` — Constructor @param InSwarm Wrapper object around the Swarm interface @param bInDumpTextures If true, the 2d lightmap exporter will dump out textures
- L29 _public prototype_ `~FLightmassSolverExporter();`
- L31 _public prototype_ `class FLightmassSwarm* GetSwarm();`
- L38 _public prototype_ `void ExportResults(struct FTextureMappingStaticLightingData& LightingData, bool bUseUniqueChannel) const;` — Send complete lighting data to Unreal @param LightingData - Object containing the computed data
- L39 _public prototype_ `void ExportResults(const struct FPrecomputedVisibilityData& TaskData) const;`
- L40 _public prototype_ `void ExportResults(const struct FVolumetricLightmapTaskData& TaskData) const;`
- L45 _public prototype_ `int32 BeginExportResults(struct FTextureMappingStaticLightingData& LightingData, uint32 NumMappings) const;` — Used when exporting multiple mappings into a single file
- L46 _public prototype_ `void EndExportResults() const;`
- L49 _public prototype_ `void ExportVolumeLightingSamples( bool bExportVolumeLightingDebugOutput, const struct FVolumeLightingDebugOutput& DebugOutput, const FVector4f& VolumeCenter, const FVector4f& VolumeExtent, const TMap<FGuid,TArray<class FVolumeLightingSample> >& VolumeSamples) const;` — Exports volume lighting samples to Unreal.
- L57 _public prototype_ `void ExportStaticShadowDepthMap(const FGuid& LightGuid, const class FStaticShadowDepthMap& StaticShadowDepthMap) const;` — Exports dominant shadow information to Unreal.
- L63 _public prototype_ `void ExportMeshAreaLightData(const class TIndirectArray<FMeshAreaLight>& MeshAreaLights, float MeshAreaLightGeneratedDynamicLightSurfaceOffset) const;` — Exports information about mesh area lights back to Unreal, So that Unreal can create dynamic lights to approximate the mesh area light's influence on dynamic objects.
- L66 _public prototype_ `void ExportVolumeDistanceField(int32 VolumeSizeX, int32 VolumeSizeY, int32 VolumeSizeZ, float VolumeMaxDistance, const FBox3f& DistanceFieldVolumeBounds, const TArray<FColor>& VolumeDistanceField) const;` — Exports the volume distance field.
- L69 _private member_ `class FLightmassSwarm* Swarm;`
- L70 _private member_ `const class FScene& Scene;`
- L73 _private member_ `bool bDumpTextures;` — true if the exporter should dump out textures to disk for previewing
- L77 _private prototype_ `template<class T> void WriteArray(const TArray<T>& Array) const;` — Writes a TArray to the channel on the top of the Swarm stack.
- L79 _private prototype_ `void WriteDebugLightingOutput(const struct FDebugLightingOutput& DebugOutput) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/ImportExport/Importer.h` (Private)


#### class `Lightmass::FLightmassImporter`  
`class FLightmassImporter`  
_L15-131_
- desc: @todo - need to pass to Serialization
- L29 _protected prototype_ `template <class ObjType, class LookupMapType, class KeyType> ObjType* ConditionalImportObjectWithKey(const KeyType& Key, const int32 Version, const FSHAHash& LMExecutableHash, const TCHAR* Extension, int32 ChannelFlags, LookupMapType& LookupMap);` — Finds existing or imports new object by Guid @param Key Key of object @param Version Version of object to load @param LMExecutableHash Hash of Lightmass executable to avoid stale cache content @param Extension Type of object to load (@todo UE5: This could be removed if Version could imply extension) @return The object that was loaded or found, or NULL if the Guid failed
- L33 _public prototype_ `FLightmassImporter( class FLightmassSwarm* InSwarm );`
- L34 _public prototype_ `~FLightmassImporter();`
- L42 _public prototype_ `bool ImportScene( class FScene& Scene, const FGuid& SceneGuid );` — Imports a scene and all required dependent objects @param Scene Scene object to fill out @param SceneGuid Guid of the scene to load from a swarm channel
- L45 _public prototype_ `bool Read( void* Data, int32 NumBytes );` — Imports a buffer of raw data
- L49 _public prototype_ `template <class DataType> bool ImportData( DataType* Data );` — Imports one object
- L53 _public prototype_ `template <class ArrayType> bool ImportArray( ArrayType& Array, int32 Count );` — Imports a TArray of simple elements in one bulk read.
- L57 _public prototype_ `template <class ObjType, class LookupMapType> bool ImportObjectArray( TArray<ObjType>& Array, int32 Count, LookupMapType& LookupMap );` — Imports a TArray of objects, while also adding them to the specified LookupMap.
- L61 _public prototype_ `template <class ArrayType, class LookupMapType> bool ImportGuidArray( ArrayType& Array, int32 Count, const LookupMapType& LookupMap );` — Imports an array of GUIDs and stores the corresponding pointers into a TArray
- L72 _public function_ `template <class ObjType, class LookupMapType> ObjType* ConditionalImportObject(const FGuid& Guid, const int32 Version, const TCHAR* Extension, int32 ChannelFlags, LookupMapType& LookupMap)` — Finds existing or imports new object by Guid @param Guid Guid of object @param Version Version of object to load @param Extension Type of object to load (@todo UE5: This could be removed if Version could imply extension) @return The object that was loaded or found, or NULL if the Guid failed
- L86 _public function_ `template <class ObjType, class LookupMapType> ObjType* ConditionalImportObject(const FSHAHash& Hash, const int32 Version, const TCHAR* Extension, int32 ChannelFlags, LookupMapType& LookupMap)` — Finds existing or imports new object by Hash @param Hash Id of object @param Version Version of object to load @param Extension Type of object to load (@todo UE5: This could be removed if Version could imply extension) @return The object that was loaded or found, or NULL if the Guid failed
- L91 _public function_ `void SetLevelScale(float InScale)`
- L92 _public function_ `float GetLevelScale() const`
- L98 _public function_ `TMap<FGuid,class FLight*>& GetLights()`
- L99 _public function_ `TMap<FGuid,class FStaticMeshStaticLightingMesh*>& GetStaticMeshInstances()`
- L100 _public function_ `TMap<FGuid,class FFluidSurfaceStaticLightingMesh*>& GetFluidMeshInstances()`
- L101 _public function_ `TMap<FGuid,class FLandscapeStaticLightingMesh*>& GetLandscapeMeshInstances()`
- L102 _public function_ `TMap<FGuid,class FStaticMeshStaticLightingTextureMapping*>& GetTextureMappings()`
- L103 _public function_ `TMap<FGuid,class FBSPSurfaceStaticLighting*>& GetBSPMappings()`
- L104 _public function_ `TMap<FGuid,class FStaticMesh*>& GetStaticMeshes()`
- L105 _public function_ `TMap<FGuid,class FFluidSurfaceStaticLightingTextureMapping*>& GetFluidMappings()`
- L106 _public function_ `TMap<FGuid,class FLandscapeStaticLightingTextureMapping*>& GetLandscapeMappings()`
- L107 _public function_ `TMap<FGuid,class FStaticLightingGlobalVolumeMapping*>& GetVolumeMappings()`
- L108 _public function_ `TMap<FGuid,class FLandscapeStaticLightingGlobalVolumeMapping*>& GetLandscapeVolumeMappings()`
- L110 _public function_ `TMap<FSHAHash,class FMaterial*>& GetMaterials()`
- L114 _private member_ `class FLightmassSwarm* Swarm;`
- L115 _private member_ `FSHAHash LightmassExecutableHash;`
- L117 _private member_ `TMap<FGuid,class FLight*> Lights;`
- L118 _private member_ `TMap<FGuid,class FStaticMesh*> StaticMeshes;`
- L119 _private member_ `TMap<FGuid,class FStaticMeshStaticLightingMesh*> StaticMeshInstances;`
- L120 _private member_ `TMap<FGuid,class FFluidSurfaceStaticLightingMesh*> FluidMeshInstances;`
- L121 _private member_ `TMap<FGuid,class FLandscapeStaticLightingMesh*> LandscapeMeshInstances;`
- L122 _private member_ `TMap<FGuid,class FStaticMeshStaticLightingTextureMapping*> StaticMeshTextureMappings;`
- L123 _private member_ `TMap<FGuid,class FBSPSurfaceStaticLighting*> BSPTextureMappings;`
- L124 _private member_ `TMap<FGuid,class FFluidSurfaceStaticLightingTextureMapping*> FluidMappings;`
- L125 _private member_ `TMap<FGuid,class FLandscapeStaticLightingTextureMapping*> LandscapeMappings;`
- L126 _private member_ `TMap<FGuid,class FStaticLightingGlobalVolumeMapping*> VolumeMappings;`
- L127 _private member_ `TMap<FGuid,class FLandscapeStaticLightingGlobalVolumeMapping*> LandscapeVolumeMappings;`
- L128 _private member_ `TMap<FSHAHash,class FMaterial*> Materials;`
- L130 _private member_ `float LevelScale;`
- L135 _function_ `template <typename DataType> FORCEINLINE bool FLightmassImporter::ImportData( DataType* Data )`
- L143 _function_ `template <class ArrayType> bool FLightmassImporter::ImportArray( ArrayType& Array, int32 Count )` — Imports a TArray of simple elements in one bulk read.
- L153 _function_ `template <class ObjType, class LookupMapType> bool FLightmassImporter::ImportObjectArray( TArray<ObjType>& Array, int32 Count, LookupMapType& LookupMap )` — Imports a TArray of objects, while also adding them to the specified LookupMap.
- L168 _function_ `template <class ArrayType, class LookupMapType> bool FLightmassImporter::ImportGuidArray( ArrayType& Array, int32 Count, const LookupMapType& LookupMap )` — Imports an array of GUIDs and stores the corresponding pointers into a TArray
- L191 _function_ `template <class ObjType, class LookupMapType, class KeyType> ObjType* FLightmassImporter::ConditionalImportObjectWithKey(const KeyType& Key, const int32 Version, const FSHAHash& LMExecutableHash, const TCHAR* Extension, int32 ChannelFlags, LookupMapType& LookupMap)` — Finds existing or imports new object by Guid @param Key Key of object @param Version Version of object to load @param Extension Type of object to load (@todo UE5: This could be removed if Version could imply extension) @return The object that was loaded or found, or NULL if the Guid failed

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/ImportExport/LightmassScene.h` (Private)


#### class `Lightmass::FLightSurfaceSample`  
`class FLightSurfaceSample`  
_L29-49_
- desc: A sample of a light's surface.
- L33 _public member_ `FVector4f Position;` — World space position
- L35 _public member_ `FVector4f Normal;` — Normal of the light's surface at the sample point
- L37 _public member_ `FVector2f DiskPosition;` — Position on the disk for lights modelled by a disk
- L39 _public member_ `float PDF;` — The probability that a sample with this position was generated
- L41 _public function_ `FLightSurfaceSample()`
- L43 _public function_ `FLightSurfaceSample(const FVector4f& InPosition, const FVector4f& InNormal, const FVector2f& InDiskPosition, float InPDF) : Position(InPosition), Normal(InNormal), DiskPosition(InDiskPosition), PDF(InPDF)`

#### class `Lightmass::FIndirectPathRay`  
`class FIndirectPathRay`  
_L52-68_
- desc: A path that was found to result in at least one indirect photon being deposited.
- L55 _public member_ `FVector4f Start;`
- L56 _public member_ `FVector4f UnitDirection;`
- L57 _public member_ `FVector4f LightSourceNormal;`
- L58 _public member_ `FVector2f LightSurfacePosition;`
- L59 _public member_ `float Length;`
- L61 _public function_ `FIndirectPathRay(const FVector4f& InStart, const FVector4f& InUnitDirection, const FVector4f& InLightSourceNormal, const FVector2f& InLightSurfacePosition, const float& InLength) : Start(InStart), UnitDirection(InUnitDirection), LightSourceNormal(InLightSourceNormal), LightSurfacePosition(InLightSurfacePosition), Length(InLength)`

#### class `Lightmass::FIrradiancePhotonData`  
`class FIrradiancePhotonData`  
_L70-82_
- L74 _protected member_ `FVector4f PositionAndDirectContribution;` — XYZ stores world space position, W stores 1 if the photon has contribution from direct photons, and 0 otherwise.
- L81 _protected member_ `FVector4f SurfaceNormalAndIrradiance;` — XYZ stores the world space normal of the receiving surface. The irradiance photon caching pass stores 1 in W if the photon is actually used. This is overwritten with the photon's irradiance in RGBE in the irradiance photon calculating pass.

#### class `Lightmass::FLight`  
`class FLight : public FLightData`  
_L87-219_
- inherits: `FLightData`
- L90 _public function_ `virtual ~FLight()`
- L92 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L97 _public function_ `virtual const class FSkyLight* GetSkyLight() const` — @return 'this' if the light is a skylight, NULL otherwise
- L101 _public function_ `virtual class FSkyLight* GetSkyLight()`
- L106 _public function_ `virtual class FDirectionalLight* GetDirectionalLight()`
- L111 _public function_ `virtual const class FDirectionalLight* GetDirectionalLight() const`
- L116 _public function_ `virtual class FPointLight* GetPointLight()`
- L121 _public function_ `virtual const class FPointLight* GetPointLight() const`
- L126 _public function_ `virtual class FSpotLight* GetSpotLight()`
- L131 _public function_ `virtual const class FSpotLight* GetSpotLight() const`
- L136 _public function_ `virtual const class FMeshAreaLight* GetMeshAreaLight() const`
- L142 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const = 0;` — Returns the number of direct photons to gather required by this light.
- L149 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds3f& Bounds) const;` — Tests whether the light affects the given bounding volume. @param Bounds - The bounding volume to test. @return True if the light affects the bounding volume
- L151 _public prototype_ `virtual FSphere3f GetBoundingSphere() const;`
- L156 _public prototype_ `virtual FLinearColor GetDirectIntensity(const FVector4f& Point, bool bCalculateForIndirectLighting) const;` — Computes the intensity of the direct lighting from this light on a specific point.
- L159 _public function_ `virtual float CustomAttenuation(const FVector4f& Point, FLMRandomStream& RandomStream, bool bMaintainEvenDensity) const` — Returns an intensity scale based on the receiving point.
- L162 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, class FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const = 0;` — Generates a direction sample from the light's domain
- L165 _public function_ `virtual void CachePathRays(const TArray<FIndirectPathRay>& IndirectPathRays)` — Gives the light an opportunity to precalculate information about the indirect path rays that will be used to generate new directions.
- L168 _public prototype_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const = 0;` — Generates a direction sample from the light based on the given rays
- L176 _public prototype_ `virtual float Power() const = 0;` — Returns the light's radiant power.
- L179 _public prototype_ `virtual void CacheSurfaceSamples(int32 BounceIndex, int32 NumSamples, int32 NumPenumbraSamples, FLMRandomStream& RandomStream);` — Generates and caches samples on the light's surface.
- L182 _public prototype_ `const TArray<FLightSurfaceSample>& GetCachedSurfaceSamples(int32 BounceIndex, bool bPenumbra) const;` — Retrieves the array of cached light surface samples.
- L185 _public function_ `virtual void ValidateSurfaceSample(const FVector4f& Point, FLightSurfaceSample& Sample) const` — Validates a surface sample given the position that sample is affecting.  The sample is unaffected by default.
- L188 _public function_ `virtual FVector4f LightCenterPosition(const FVector4f& ReceivingPosition, const FVector4f& ReceivingNormal) const` — Gets a single position which represents the center of the area light source from the ReceivingPosition's point of view.
- L191 _public prototype_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const = 0;` — Returns true if all parts of the light are behind the surface being tested.
- L194 _public prototype_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const = 0;` — Gets a single direction to use for direct lighting that is representative of the whole area light.
- L201 _public function_ `bool UseStaticLighting() const` — Returns whether static lighting, aka lightmaps, is being used for primitive/ light interaction. @return true if lightmaps/ static lighting is being used, false otherwise
- L206 _public function_ `virtual FVector3f GetLightTangent() const`
- L210 _protected member_ `TArray<TArray<TArray<FLightSurfaceSample> > > CachedLightSurfaceSamples;` — Cached samples of the light's surface, indexed first by bounce number, then by whether the shadow ray is a penumbra ray, then by sample index.
- L213 _protected member_ `FLinearColor IndirectColor;` — Cached calculation of the light's indirect color, which is the base Color adjusted by the IndirectLightingScale and IndirectLightingSaturation
- L216 _protected prototype_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const = 0;` — Generates a sample on the light's surface.
- L218 _protected member_ `TArray< uint8 > LightTextureProfileData;`

#### class `Lightmass::FDirectionalLight`  
`class FDirectionalLight : public FLight, public FDirectionalLightData`  
_L225-326_
- inherits: `FLight,FDirectionalLightData`
- L229 _public member_ `float IndirectDiskRadius;`
- L231 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L233 _public function_ `virtual class FDirectionalLight* GetDirectionalLight()`
- L238 _public function_ `virtual const class FDirectionalLight* GetDirectionalLight() const`
- L243 _public prototype_ `void Initialize( const FBoxSphereBounds3f& InSceneBounds, bool bInEmitPhotonsOutsideImportanceVolume, const FBoxSphereBounds3f& InImportanceBounds, float InIndirectDiskRadius, int32 InGridSize, float InDirectPhotonDensity, float InOutsideImportanceVolumeDensity);`
- L253 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const;` — Returns the number of direct photons to gather required by this light.
- L256 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light's domain
- L259 _public prototype_ `virtual void CachePathRays(const TArray<FIndirectPathRay>& IndirectPathRays);` — Gives the light an opportunity to precalculate information about the indirect path rays that will be used to generate new directions.
- L262 _public prototype_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light based on the given rays
- L270 _public prototype_ `virtual float Power() const;` — Returns the light's radiant power.
- L273 _public prototype_ `virtual void ValidateSurfaceSample(const FVector4f& Point, FLightSurfaceSample& Sample) const;` — Validates a surface sample given the position that sample is affecting.
- L276 _public prototype_ `virtual FVector4f LightCenterPosition(const FVector4f& ReceivingPosition, const FVector4f& ReceivingNormal) const;` — Gets a single position which represents the center of the area light source from the ReceivingPosition's point of view.
- L279 _public prototype_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const;` — Returns true if all parts of the light are behind the surface being tested.
- L282 _public prototype_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const;` — Gets a single direction to use for direct lighting that is representative of the whole area light.
- L287 _protected member_ `float GridExtent;` — Extent of PathRayGrid in the [-1, 1] space of the directional light's disk.
- L290 _protected member_ `FVector2f GridCenter;` — Center of PathRayGrid in the [-1, 1] space of the directional light's disk.
- L293 _protected member_ `int32 GridSize;` — Size of PathRayGrid in each dimension.
- L296 _protected member_ `TArray<TArray<int32>> PathRayGrid;` — Grid of indices into IndirectPathRays that affect each cell.
- L299 _protected member_ `FBoxSphereBounds3f SceneBounds;` — Bounds of the scene that the directional light is affecting.
- L301 _protected member_ `bool bEmitPhotonsOutsideImportanceVolume;`
- L304 _protected member_ `FBoxSphereBounds3f ImportanceBounds;` — Bounds of the importance volume in the scene.  If the radius is 0, there was no importance volume.
- L307 _protected member_ `FVector2f ImportanceDiskOrigin;` — Center of the importance volume in the [-1,1] space of the directional light's disk
- L310 _protected member_ `float LightSpaceImportanceDiskRadius;` — Radius of the importance volume in the [-1,1] space of the directional light's disk
- L313 _protected member_ `float OutsideImportanceVolumeDensity;` — Density of photons to gather outside of the importance volume.
- L316 _protected member_ `float ImportanceBoundsSampleProbability;` — Probability of generating a sample inside the importance volume.
- L319 _protected member_ `FVector4f XAxis;` — X axis of the directional light, which is unit length and orthogonal to the direction and YAxis.
- L322 _protected member_ `FVector4f YAxis;` — Y axis of the directional light, which is unit length and orthogonal to the direction and XAxis.
- L325 _protected prototype_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const;` — Generates a sample on the light's surface.

#### class `Lightmass::FPointLight`  
`class FPointLight : public FLight, public FPointLightData`  
_L332-405_
- inherits: `FLight,FPointLightData`
- L335 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L337 _public function_ `virtual class FPointLight* GetPointLight()`
- L342 _public function_ `virtual const class FPointLight* GetPointLight() const`
- L347 _public prototype_ `void Initialize(float InIndirectPhotonEmitConeAngle);`
- L350 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const;` — Returns the number of direct photons to gather required by this light.
- L357 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds3f& Bounds) const;` — Tests whether the light affects the given bounding volume. @param Bounds - The bounding volume to test. @return True if the light affects the bounding volume
- L359 _public function_ `virtual FSphere3f GetBoundingSphere() const`
- L367 _public prototype_ `virtual FLinearColor GetDirectIntensity(const FVector4f& Point, bool bCalculateForIndirectLighting) const;` — Computes the intensity of the direct lighting from this light on a specific point.
- L370 _public prototype_ `virtual float CustomAttenuation(const FVector4f& Point, FLMRandomStream& RandomStream, bool bMaintainEvenDensity) const;` — Returns an intensity scale based on the receiving point.
- L373 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light's domain
- L376 _public prototype_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light based on the given rays
- L384 _public prototype_ `virtual void ValidateSurfaceSample(const FVector4f& Point, FLightSurfaceSample& Sample) const;` — Validates a surface sample given the position that sample is affecting.
- L387 _public prototype_ `virtual float Power() const;` — Returns the light's radiant power.
- L389 _public prototype_ `virtual FVector4f LightCenterPosition(const FVector4f& ReceivingPosition, const FVector4f& ReceivingNormal) const;`
- L392 _public prototype_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const;` — Returns true if all parts of the light are behind the surface being tested.
- L395 _public prototype_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const;` — Gets a single direction to use for direct lighting that is representative of the whole area light.
- L397 _public prototype_ `virtual FVector3f GetLightTangent() const override;`
- L401 _protected member_ `float CosIndirectPhotonEmitConeAngle;`
- L404 _protected prototype_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const;` — Generates a sample on the light's surface.

#### class `Lightmass::FSpotLight`  
`class FSpotLight : public FPointLight, public FSpotLightData`  
_L411-461_
- inherits: `FPointLight,FSpotLightData`
- L415 _public function_ `virtual class FSpotLight* GetSpotLight()`
- L420 _public function_ `virtual const class FSpotLight* GetSpotLight() const`
- L425 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L427 _public prototype_ `void Initialize(float InIndirectPhotonEmitConeAngle);`
- L434 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds3f& Bounds) const;` — Tests whether the light affects the given bounding volume. @param Bounds - The bounding volume to test. @return True if the light affects the bounding volume
- L436 _public prototype_ `virtual FSphere3f GetBoundingSphere() const;`
- L441 _public prototype_ `virtual FLinearColor GetDirectIntensity(const FVector4f& Point, bool bCalculateForIndirectLighting) const;` — Computes the intensity of the direct lighting from this light on a specific point.
- L444 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const;` — Returns the number of direct photons to gather required by this light.
- L447 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light's domain
- L450 _public prototype_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light based on the given rays
- L458 _protected member_ `float SinOuterConeAngle;`
- L459 _protected member_ `float CosOuterConeAngle;`
- L460 _protected member_ `float CosInnerConeAngle;`

#### class `Lightmass::FRectLight`  
`class FRectLight : public FPointLight, public FRectLightData`  
_L467-487_
- inherits: `FPointLight,FRectLightData`
- L470 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L472 _public prototype_ `virtual FLinearColor GetDirectIntensity(const FVector4f& Point, bool bCalculateForIndirectLighting) const override;`
- L473 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const override;`
- L474 _public prototype_ `virtual void ValidateSurfaceSample(const FVector4f& Point, FLightSurfaceSample& Sample) const override;`
- L475 _public prototype_ `virtual FVector4f LightCenterPosition(const FVector4f& ReceivingPosition, const FVector4f& ReceivingNormal) const override;`
- L476 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds3f& Bounds) const override;`
- L477 _public prototype_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const override;`
- L478 _public prototype_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const override;`
- L480 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const override;`
- L481 _public prototype_ `virtual void SampleDirection(const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const override;`
- L484 _protected prototype_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const override;`
- L486 _protected member_ `TArray< FFloat16Color > SourceTexture;`

#### class `Lightmass::FSkyLight`  
`class FSkyLight : public FLight, public FSkyLightData`  
_L493-558_
- inherits: `FLight,FSkyLightData`
- L496 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L501 _public function_ `virtual const class FSkyLight* GetSkyLight() const` — @return 'this' if the light is a skylight, NULL otherwise
- L505 _public function_ `virtual class FSkyLight* GetSkyLight()`
- L511 _public function_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const` — Returns the number of direct photons to gather required by this light.
- L515 _public function_ `virtual void SampleDirection(FLMRandomStream& RandomStream, class FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const` — Generates a direction sample from the light's domain
- L519 _public function_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const` — Generates a direction sample from the light based on the given rays
- L528 _public function_ `virtual float Power() const` — Returns the light's radiant power.
- L532 _public function_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const` — Returns true if all parts of the light are behind the surface being tested.
- L535 _public function_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const` — Gets a single direction to use for direct lighting that is representative of the whole area light.
- L538 _public prototype_ `FLinearColor GetPathLighting(const FVector4f& IncomingDirection, float PathSolidAngle, bool bCalculateForIndirectLighting) const;`
- L540 _public prototype_ `float GetPathVariance(const FVector4f& IncomingDirection, float PathSolidAngle) const;`
- L545 _protected function_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const` — Generates a sample on the light's surface.
- L548 _protected prototype_ `float GetMipIndexForSolidAngle(float SolidAngle) const;`
- L549 _protected prototype_ `FLinearColor SampleRadianceCubemap(float MipIndex, int32 CubeFaceIndex, FVector2f FaceUV) const;`
- L550 _protected prototype_ `float SampleVarianceCubemap(float MipIndex, int32 CubeFaceIndex, FVector2f FaceUV) const;`
- L552 _protected prototype_ `void ComputePrefilteredVariance();`
- L554 _protected member_ `int32 CubemapSize;`
- L555 _protected member_ `int32 NumMips;`
- L556 _protected member_ `TArray<TArray<FLinearColor>> PrefilteredRadiance;`
- L557 _protected member_ `TArray<TArray<float>> PrefilteredVariance;`

#### class `Lightmass::FMeshLightPrimitiveCorner`  
`class FMeshLightPrimitiveCorner`  
_L560-567_
- L564 _public member_ `FVector4f WorldPosition;` — World space corner position, not necessarily coplanar with the other corners.
- L566 _public member_ `FIntPoint FurthestCoordinates;` — Coordinate in texture space corresponding to the position this corner is storing.

#### class `Lightmass::FMeshLightPrimitive`  
`class FMeshLightPrimitive`  
_L570-585_
- desc: The atomic shape used to represent an area light's shape.
- L573 _public member_ `FMeshLightPrimitiveCorner Corners[NumTexelCorners];`
- L575 _public member_ `FVector4f SurfaceNormal;` — Average normal of the sub primitives making up this simplified primitive.
- L577 _public member_ `FLinearColor Power;` — Radiant flux of this primitive
- L579 _public member_ `float SurfaceArea;` — Surface area of this primitive
- L581 _public member_ `int32 NumSubPrimitives;` — Number of original primitives that were combined into this simplified primitive.
- L583 _public prototype_ `void AddSubPrimitive(const struct FTexelToCorners& TexelToCorners, const FIntPoint& Coordinates, const FLinearColor& InTexelPower, float NormalOffset);`
- L584 _public prototype_ `void Finalize();`

#### class `Lightmass::FMeshAreaLight`  
`class FMeshAreaLight : public FLight`  
_L590-719_
- inherits: `FLight`
- L594 _public function_ `FMeshAreaLight(EForceInit)`
- L602 _public function_ `virtual const class FMeshAreaLight* GetMeshAreaLight() const`
- L607 _public prototype_ `void Initialize(float InIndirectPhotonEmitConeAngle, const FBoxSphereBounds3f& InImportanceBounds);`
- L610 _public prototype_ `virtual int32 GetNumDirectPhotons(float DirectPhotonDensity) const;` — Returns the number of direct photons to gather required by this light.
- L613 _public prototype_ `void SetPrimitives( const TArray<FMeshLightPrimitive>& InPrimitives, float EmissiveLightFalloffExponent, float EmissiveLightExplicitInfluenceRadius, int32 InMeshAreaLightGridSize, FGuid InLevelGuid);` — Initializes the mesh area light with primitives
- L620 _public function_ `int32 GetNumPrimitives() const`
- L630 _public function_ `int32 GetNumSimplifiedPrimitives() const`
- L637 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds3f& Bounds) const;` — Tests whether the light affects the given bounding volume. @param Bounds - The bounding volume to test. @return True if the light affects the bounding volume
- L642 _public prototype_ `virtual FLinearColor GetDirectIntensity(const FVector4f& Point, bool bCalculateForIndirectLighting) const;` — Computes the intensity of the direct lighting from this light on a specific point.
- L645 _public prototype_ `virtual float CustomAttenuation(const FVector4f& Point, FLMRandomStream& RandomStream, bool bMaintainEvenDensity) const;` — Returns an intensity scale based on the receiving point.
- L648 _public prototype_ `virtual void SampleDirection(FLMRandomStream& RandomStream, FLightRay& SampleRay, FVector4f& LightSourceNormal, FVector2f& LightSurfacePosition, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light's domain
- L651 _public prototype_ `virtual void SampleDirection( const TArray<FIndirectPathRay>& IndirectPathRays, FLMRandomStream& RandomStream, FLightRay& SampleRay, float& RayPDF, FLinearColor& Power) const;` — Generates a direction sample from the light based on the given rays
- L659 _public prototype_ `void ValidateSurfaceSample(const FVector4f& Point, FLightSurfaceSample& Sample) const;` — Validates a surface sample given the position that sample is affecting.
- L662 _public prototype_ `virtual float Power() const;` — Returns the light's radiant power.
- L665 _public prototype_ `virtual bool BehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal) const;` — Returns true if all parts of the light are behind the surface being tested.
- L668 _public prototype_ `virtual FVector4f GetDirectLightingDirection(const FVector4f& Point, const FVector4f& PointNormal) const;` — Gets a single direction to use for direct lighting that is representative of the whole area light.
- L672 _protected member_ `FLinearColor TotalPower;` — Radiant flux of all the primitives
- L675 _protected member_ `float TotalSurfaceArea;` — Accumulated surface area of all primitives
- L678 _protected member_ `float InfluenceRadius;` — Generated radius of the light's influence
- L681 _protected member_ `FBoxSphereBounds3f SourceBounds;` — Bounds of the light's primitives
- L684 _protected member_ `float FalloffExponent;` — Falloff of the attenuation function
- L687 _protected member_ `float CosIndirectPhotonEmitConeAngle;` — Cosine of the angle about an indirect path in which to emit indirect photons
- L690 _protected member_ `TArray<FMeshLightPrimitive> Primitives;` — All the primitives that define this light's shape
- L693 _protected member_ `int32 MeshAreaLightGridSize;` — Size of the data stored in CachedPrimitiveNormals in each dimension.
- L695 _protected member_ `FGuid LevelGuid;`
- L698 _protected member_ `TArray<TArray<FVector4f> > CachedPrimitiveNormals;` — Grid of arrays of primitive normals, used to accelerate PDF calculation once a sample is generated.
- L701 _protected member_ `TArray<FIntPoint> OccupiedCachedPrimitiveNormalCells;` — Entries in CachedPrimitiveNormals that have one or more cached normals.
- L704 _protected member_ `FBoxSphereBounds3f ImportanceBounds;` — Bounds of the importance volume in the scene.  If the radius is 0, there was no importance volume.
- L707 _protected member_ `TArray<float> PrimitivePDFs;` — Probability of selecting each primitive when sampling.
- L710 _protected member_ `TArray<float> PrimitiveCDFs;` — Stores the cumulative distribution function of PrimitivePDFs
- L713 _protected member_ `float UnnormalizedIntegral;` — Stores the integral of PrimitivePDFs
- L716 _protected prototype_ `virtual void SampleLightSurface(FLMRandomStream& RandomStream, FLightSurfaceSample& Sample) const;` — Generates a sample on the light's surface.

#### class `Lightmass::FPrecomputedVisibilityVolume`  
`class FPrecomputedVisibilityVolume`  
_L722-727_
- desc: Volume that determines where to place visibility cells.
- L725 _public member_ `FBox3f Bounds;`
- L726 _public member_ `TArray<FPlane4f> Planes;`

#### class `Lightmass::FPrecomputedVisibilityOverrideVolume`  
`class FPrecomputedVisibilityOverrideVolume`  
_L730-736_
- desc: Volume that overrides visibility for a set of Ids.
- L733 _public member_ `FBox3f Bounds;`
- L734 _public member_ `TArray<int32> OverrideVisibilityIds;`
- L735 _public member_ `TArray<int32> OverrideInvisibilityIds;`

#### struct `Lightmass::FVolumetricLightmapDensityVolume`  
`struct FVolumetricLightmapDensityVolume : public FVolumetricLightmapDensityVolumeData`  
_L738-741_
- inherits: `FVolumetricLightmapDensityVolumeData`
- L740 _public member_ `TArray<FPlane4f> Planes;`

#### class `Lightmass::FScene`  
`class FScene : public FSceneFileHeader`  
_L746-812_
- inherits: `FSceneFileHeader`
- L749 _public prototype_ `FScene();`
- L750 _public prototype_ `virtual ~FScene();`
- L752 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L753 _public prototype_ `FBoxSphereBounds3f GetImportanceBounds() const;`
- L755 _public member_ `FBox3f ImportanceBoundingBox;`
- L756 _public member_ `TArray<FBox3f> ImportanceVolumes;`
- L757 _public member_ `TArray<FBox3f> CharacterIndirectDetailVolumes;`
- L758 _public member_ `TArray<FVolumetricLightmapDensityVolume> VolumetricLightmapDensityVolumes;`
- L759 _public member_ `TArray<FSphere3f> Portals;`
- L760 _public member_ `TArray<FPrecomputedVisibilityVolume> PrecomputedVisibilityVolumes;`
- L761 _public member_ `TArray<FPrecomputedVisibilityOverrideVolume> PrecomputedVisibilityOverrideVolumes;`
- L762 _public member_ `TArray<FVector4f> CameraTrackPositions;`
- L764 _public member_ `TArray<FDirectionalLight> DirectionalLights;`
- L765 _public member_ `TArray<FPointLight> PointLights;`
- L766 _public member_ `TArray<FSpotLight> SpotLights;`
- L767 _public member_ `TArray<FRectLight> RectLights;`
- L768 _public member_ `TArray<FSkyLight> SkyLights;`
- L770 _public member_ `TArray<FStaticMeshStaticLightingMesh> StaticMeshInstances;`
- L771 _public member_ `TArray<FFluidSurfaceStaticLightingMesh> FluidMeshInstances;`
- L772 _public member_ `TArray<FLandscapeStaticLightingMesh> LandscapeMeshInstances;`
- L773 _public member_ `TArray<FBSPSurfaceStaticLighting> BspMappings;`
- L774 _public member_ `TArray<FStaticMeshStaticLightingTextureMapping> TextureLightingMappings;`
- L775 _public member_ `TArray<FFluidSurfaceStaticLightingTextureMapping> FluidMappings;`
- L776 _public member_ `TArray<FLandscapeStaticLightingTextureMapping> LandscapeMappings;`
- L777 _public member_ `TArray<FStaticLightingGlobalVolumeMapping> VolumeMappings;`
- L778 _public member_ `TArray<FLandscapeStaticLightingGlobalVolumeMapping> LandscapeVolumeMappings;`
- L780 _public member_ `TArray<FGuid> VisibilityBucketGuids;`
- L781 _public member_ `TArray<FGuid> VolumetricLightmapTaskGuids;`
- L783 _public member_ `RTCDevice EmbreeDevice;`
- L784 _public member_ `bool bVerifyEmbree;`
- L787 _public member_ `const class FStaticLightingMapping* DebugMapping;` — The mapping whose texel is selected in Unreal and is being debugged.
- L789 _public prototype_ `const FLight* FindLightByGuid(const FGuid& Guid) const;`
- L792 _public prototype_ `bool IsPointInImportanceVolume(const FVector4f& Position, float Tolerance) const;` — Returns true if the specified position is inside any of the importance volumes.
- L794 _public prototype_ `bool IsBoxInImportanceVolume(const FBox3f& QueryBox) const;`
- L797 _public prototype_ `bool IsPointInVisibilityVolume(const FVector4f& Position) const;` — Returns true if the specified position is inside any of the visibility volumes.
- L799 _public prototype_ `bool DoesBoxIntersectVisibilityVolume(const FBox3f& TestBounds) const;`
- L802 _public prototype_ `FBox3f GetVisibilityVolumeBounds() const;` — Returns accumulated bounds from all the visibility volumes.
- L804 _public prototype_ `bool GetVolumetricLightmapAllowedMipRange(const FVector4f& Position, FIntPoint& OutRange) const;`
- L808 _private prototype_ `const FStaticLightingMapping* FindMappingByGuid(FGuid FindGuid) const;` — Searches through all mapping arrays for the mapping matching FindGuid.
- L811 _private prototype_ `void ApplyStaticLightingScale();` — Applies GeneralSettings.StaticLightingLevelScale to all scale dependent settings.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/ImportExport/LightmassSwarm.h` (Private)


#### class `Lightmass::FLightmassSwarm`  
`class FLightmassSwarm`  
_L49-360_
- L58 _public prototype_ `FLightmassSwarm( NSwarm::FSwarmInterface& SwarmInterface, const FGuid& JobGuid, int32 TaskQueueSize );` — Constructs the Swarm wrapper used by Lightmass. @param SwarmInterface	The global SwarmInterface to use @param JobGuid			Guid that identifies the job we're working on @param TaskQueueSize		Number of tasks we should try to keep in the queue
- L61 _public prototype_ `~FLightmassSwarm();` — Destructor
- L66 _public function_ `int32 GetChannel()` — @retrurn the currently active channel for reading
- L76 _public function_ `const FGuid& GetJobGuid()` — Returns the current job guid. @return	Current Swarm job guid
- L90 _public prototype_ `int32 OpenChannel( const TCHAR* ChannelName, int32 ChannelFlags, bool bPushChannel );` — Opens a new channel and optionally pushes it on to the channel stack @param ChannelName Name of the channel @param ChannelFlags Flags (read, write, etc) for the channel @param bPushChannel If true, this new channel will be auto-pushed onto the stack @return The channel that was opened
- L97 _public prototype_ `void CloseChannel( int32 Channel );` — Closes a channel previously opened with OpenSideChannel @param Channel The channel to close
- L104 _public prototype_ `void PushChannel(int32 Channel);` — Pushes a new channel on the stack as the current channel to read from @param Channel New channel to read from
- L111 _public prototype_ `void PopChannel(bool bCloseChannel);` — Pops the top channel @param bCloseChannel If true, the channel will be closed when it is popped off
- L116 _public function_ `void CloseCurrentChannel()` — Function that closes and pops current channel
- L129 _public function_ `int32 Read(void* Data, int32 Size)` — Reads data from the current channel @param Data Data to read from the channel @param Size Size of Data @return Amount read
- L151 _public function_ `int32 Write(const void* Data, int32 Size)` — Writes data to the current channel @param Data Data to write over the channel @param Size Size of Data @return Amount written
- L170 _public prototype_ `static void SwarmCallback( NSwarm::FMessage* CallbackMessage, void* CallbackData );` — The callback function used by Swarm to communicate to Lightmass. @param CallbackMessage	Message sent from Swarm @param UserParam			User-defined parameter (specified in OpenConnection). Type-casted FLightmassSwarm pointer.
- L176 _public function_ `bool ReceivedQuitRequest() const` — Whether Swarm wants us to quit. @return	true if Swarm has told us to quit.
- L185 _public function_ `bool IsDone() const` — Whether we've received all tasks already and there are no more tasks to work on. @return	true if there are no more tasks in the job to work on
- L194 _public prototype_ `void PrefetchTasks();` — Prefetch tasks into our work queue, which is where RequestTask gets its work items from.
- L206 _public prototype_ `bool RequestTask( FGuid& TaskGuid, uint32 WaitTime = uint32(-1) );` — Thread-safe blocking call to request a new task from the local task queue. It will block until there's a task in the local queue, or the timeout period has passed. If a task is returned, it will asynchronously request a new task from Swarm to keep the queue full. You must call AcceptTask() or RejectTask() if a task is returned. @param TaskGuid	[out] When successful, contains the FGuid for the new task @param WaitTime	Timeout period in milliseconds, or -1 for INFINITE @return			true if a Task Guid is returned, false if the timeout period has passed or IsDone()/ReceivedQuitRequest() is true
- L212 _public prototype_ `void AcceptTask( const FGuid& TaskGuid );` — Accepts a requested task. This will also notify UE5. @param TaskGuid	The task that is being accepted
- L218 _public prototype_ `void RejectTask( const FGuid& TaskGuid );` — Rejects a requested task. This will also notify UE5. @param TaskGuid	The task that is being rejected
- L224 _public prototype_ `void TaskCompleted( const FGuid& TaskGuid );` — Tells Swarm that the task is completed and all results have been fully exported. This will also notify UE5. @param TaskGuid	A guid that identifies the task that has been completed
- L230 _public prototype_ `void TaskFailed( const FGuid& TaskGuid );` — Tells Swarm that the task has failed. This will also notify UE5. @param TaskGuid	A guid that identifies the task that has failed
- L236 _public function_ `template <typename FmtType, typename... Types> void SendTextMessage(const FmtType& Fmt, Types... Args)` — Sends text information to Swarm, using printf-like parameters.
- L242 _private prototype_ `void SendTextMessageImpl(const TCHAR* Buffer);`
- L249 _public prototype_ `void ReportFile( const TCHAR* Filename );` — Report to Swarm by sending back a file. @param Filename	File to send back
- L255 _public prototype_ `void SendMessage( const NSwarm::FMessage& Message );` — Sends a message to Swarm. Thread-safe access. @param Message	Swarm message to send.
- L264 _public prototype_ `void SendAlertMessage( NSwarm::TAlertLevel AlertLevel, const FGuid& ObjectGuid, const int32 TypeId, const TCHAR* MessageText);` — Sends an alert message to Swarm. Thread-safe access. @param	AlertType		The type of alert. @param	ObjectGuid		The GUID of the object associated with the alert. @param	TypeId			The type of object. @param	MessageText		The text of the message.
- L272 _public function_ `uint64 GetTotalBytesRead()` — @return the total number of bytes that have been read from Swarm
- L280 _public function_ `uint64 GetTotalBytesWritten()` — @return the total number of bytes that have been read from Swarm
- L288 _public function_ `double GetTotalSecondsRead()` — @return the total number of seconds spent reading from Swarm
- L296 _public function_ `double GetTotalSecondsWritten()` — @return the total number of seconds spent writing to Swarm
- L304 _public function_ `uint32 GetTotalNumReads()` — @return the total number of reads from Swarm
- L312 _public function_ `uint32 GetTotalNumWrites()` — @return the total number of writes to Swarm
- L322 _private prototype_ `void TriggerAllThreads();` — Triggers the task queue enough times to release all blocked threads.
- L325 _private member_ `NSwarm::FSwarmInterface& API;` — The Swarm interface.
- L328 _private member_ `FGuid JobGuid;` — The job guid (the same as the scene guid)
- L331 _private member_ `FCriticalSection SwarmAccess;` — Critical section to synchronize any access to the Swarm API (sending messages, etc).
- L334 _private member_ `bool bIsDone;` — true if there are no more tasks in the job.
- L337 _private member_ `bool QuitRequest;` — Set to true when a QUIT message is received from Swarm.
- L340 _private member_ `TProducerConsumerQueue<FGuid> TaskQueue;` — Tasks that have been received from Swarm but not yet handed out to a worker thread.
- L343 _private member_ `volatile int32 NumRequestedTasks;` — Number of outstanding task requests.
- L346 _private member_ `TArray<int32> ChannelStack;` — Stack of used channels
- L349 _private member_ `uint64 TotalBytesRead;` — Total bytes read/written
- L350 _private member_ `uint64 TotalBytesWritten;`
- L353 _private member_ `double TotalSecondsRead;` — Total number of seconds spent reading from Swarm
- L355 _private member_ `double TotalSecondsWritten;` — Total number of seconds spent writing to Swarm
- L357 _private member_ `uint32 TotalNumReads;` — Total number of reads to Swarm
- L359 _private member_ `uint32 TotalNumWrites;` — Total number of writes to Swarm

#### struct `Lightmass::FTiming`  
`struct FTiming`  
_L369-444_
- desc: Helper struct for request-task/receive-task roundtrip timings
- L372 _public function_ `FTiming()` — Constructor that clears the timing.
- L377 _public function_ `void Clear()` — Clear the timing.
- L383 _public function_ `void Start( )` — Start the timing.
- L388 _public function_ `void Stop()` — Stop the timing.
- L393 _public member_ `double StartTime;` — Start time, as measured by an FPlatformTime::Seconds() timestamp.
- L395 _public member_ `double Duration;` — Duration of the timing, in seconds.
- L398 _public function_ `static FORCEINLINE void NotifyTaskRequested()` — Call when requesting a task.
- L412 _public function_ `static FORCEINLINE void NotifyTaskReceived()` — Call when receiving a task.
- L426 _public function_ `static double GetAverageTiming()` — Returns the average roundtrip time for the timings captured so far, in seconds.
- L439 _public member_ `static FTiming GTaskTimings[NUM_TASKTIMINGS];` — The first NUM_TASKTIMINGS roundtrip timings.
- L441 _public member_ `static volatile int32 GTaskRequestCounter;` — Number of tasks requested so far.
- L443 _public member_ `static volatile int32 GTaskReceiveCounter;` — Number of tasks received so far.

#### Free symbols / members of external scopes

- L6 _macro_ `#define SWARMINTERFACE_API`
- L20 _namespace_ `namespace Lightmass`
- L24 _macro_ `#define SWARM_ENABLE_CHANNEL_READS 1` — Whether to enable channel I/O via Swarm - disable for performance debugging
- L25 _macro_ `#define SWARM_ENABLE_CHANNEL_WRITES 1`
- L29 _variable_ `static const int32 LM_TEXTUREMAPPING_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`) — MUST PAIR APPROPRIATELY WITH THE SAME FLAGS IN UE5
- L30 _variable_ `static const int32 LM_VOLUMESAMPLES_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L31 _variable_ `static const int32 LM_PRECOMPUTEDVISIBILITY_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L32 _variable_ `static const int32 LM_VOLUMEDEBUGOUTPUT_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L33 _variable_ `static const int32 LM_DOMINANTSHADOW_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L34 _variable_ `static const int32 LM_MESHAREALIGHT_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L35 _variable_ `static const int32 LM_DEBUGOUTPUT_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_WRITE;` (scope `Lightmass`)
- L40 _variable_ `static const int32 LM_SCENE_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_READ | NSwarm::SWARM_CHANNEL_MISC_ENABLE_COMPRESSION;` (scope `Lightmass`)
- L41 _variable_ `static const int32 LM_STATICMESH_CHANNEL_FLAGS = NSwarm::SWARM_CHANNEL_READ | NSwarm::SWARM_CHANNEL_MISC_ENABLE_COMPRESSION;` (scope `Lightmass`)
- L42 _variable_ `static const int32 LM_MATERIAL_CHANNEL_FLAGS = NSwarm::SWARM_CHANNEL_READ | NSwarm::SWARM_CHANNEL_MISC_ENABLE_COMPRESSION;` (scope `Lightmass`)
- L44 _variable_ `static const int32 LM_SCENE_CHANNEL_FLAGS = NSwarm::SWARM_JOB_CHANNEL_READ;` (scope `Lightmass`)
- L45 _variable_ `static const int32 LM_STATICMESH_CHANNEL_FLAGS = NSwarm::SWARM_CHANNEL_READ;` (scope `Lightmass`)
- L46 _variable_ `static const int32 LM_MATERIAL_CHANNEL_FLAGS = NSwarm::SWARM_CHANNEL_READ;` (scope `Lightmass`)
- L363 _macro_ `#define TASKTIMING_FREQ 50` — Number of task-requests to skip before timing a roundtrip
- L366 _macro_ `#define NUM_TASKTIMINGS 100` — Number of roundtrip timings to capture

### `Source/Programs/UnrealLightmass/Private/ImportExport/Material.h` (Private)


#### class `Lightmass::FBaseMaterial`  
`class FBaseMaterial : public FBaseMaterialData`  
_L17-22_
- inherits: `FBaseMaterialData`
- L20 _public function_ `virtual ~FBaseMaterial()`
- L21 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`

#### class `Lightmass::FMaterial`  
`class FMaterial : public FBaseMaterial, public FMaterialData`  
_L28-64_
- inherits: `FBaseMaterial,FMaterialData`
- L31 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L34 _public function_ `inline void SampleEmissive(const FVector2f& UV, FLinearColor& Emissive, float& OutEmissiveBoost) const` — Sample the various properties of this material at the given UV
- L39 _public function_ `inline void SampleDiffuse(const FVector2f& UV, FLinearColor& Diffuse, float& OutDiffuseBoost) const`
- L44 _public function_ `inline FLinearColor SampleTransmission(const FVector2f& UV) const`
- L48 _public function_ `inline void SampleNormal(const FVector2f& UV, FVector4f& Normal) const`
- L60 _protected member_ `FTexture2D MaterialEmissive;`
- L61 _protected member_ `FTexture2D MaterialDiffuse;`
- L62 _protected member_ `FTexture2D MaterialTransmission;`
- L63 _protected member_ `FTexture2D MaterialNormal;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/ImportExport/Mesh.h` (Private)


#### class `Lightmass::FBaseMesh`  
`class FBaseMesh : public FBaseMeshData`  
_L22-27_
- inherits: `FBaseMeshData`
- L25 _public function_ `virtual ~FBaseMesh()`
- L26 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`

#### class `Lightmass::FStaticMesh`  
`class FStaticMesh : public FBaseMesh, public FStaticMeshData`  
_L34-52_
- inherits: `FBaseMesh,FStaticMeshData`
- L37 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L42 _public function_ `inline const FStaticMeshLOD& GetLOD(int32 Index) const` — @return the given LOD by index
- L47 _public member_ `class FDefaultAggregateMesh* VoxelizationMesh = nullptr;`
- L51 _protected member_ `TArray<FStaticMeshLOD> LODs;` — array of LODs (same number as FStaticMeshData.NumLODs)

#### class `Lightmass::FStaticMeshLOD`  
`class FStaticMeshLOD : public FStaticMeshLODData`  
_L59-97_
- inherits: `FStaticMeshLODData`
- L62 _public function_ `virtual ~FStaticMeshLOD()`
- L63 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L68 _public function_ `inline const FStaticMeshElement& GetElement(int32 Index) const` — @return the given element by index
- L76 _public function_ `inline const uint32 GetIndex(int32 Index) const` — @return the given vertex index by index
- L84 _public function_ `inline const FStaticMeshVertex& GetVertex(int32 Index) const` — @return the given vertex by index
- L90 _protected member_ `TArray<FStaticMeshElement> Elements;` — array of Elements for this LOD (same number as FStaticMeshLODData.NumElements)
- L93 _protected member_ `TArray<uint32> Indices;` — array of Indices for this LOD (same number as FStaticMeshLODData.NumIndices)
- L96 _protected member_ `TArray<FStaticMeshVertex> Vertices;` — array of vertices for this LOD (same number as FStaticMeshLODData.NumVertices)

#### class `Lightmass::FStaticMeshElement`  
`class FStaticMeshElement : public FStaticMeshElementData`  
_L104-108_
- inherits: `FStaticMeshElementData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Launch/UnitTest.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`
- L13 _prototype_ `void TestLightmass();` (scope `Lightmass`) — Run "unit tests" making use of LightmassCore and other functionality worth testing

### `Source/Programs/UnrealLightmass/Private/Launch/UnrealLightmass.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLightmass, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLightmass, Log, All);`

### `Source/Programs/UnrealLightmass/Private/Lighting/BSP.h` (Private)


#### class `Lightmass::FBSPSurfaceStaticLighting`  
`class FBSPSurfaceStaticLighting : public FStaticLightingMesh, public FBSPSurfaceStaticLightingData`  
_L13-41_
- inherits: `FStaticLightingMesh,FBSPSurfaceStaticLightingData`
- desc: Represents a BSP surface to the static lighting system.
- L17 _public function_ `FBSPSurfaceStaticLighting() : bComplete(false)`
- L22 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const;` — FStaticLightingMesh interface.
- L23 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L25 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L28 _public member_ `bool bComplete;` — true if the surface has complete static lighting.
- L31 _public member_ `FStaticLightingTextureMapping Mapping;` — Texture mapping for the BSP
- L34 _public member_ `TArray<FStaticLightingVertex> Vertices;` — The surface's vertices.
- L37 _public member_ `TArray<int32> TriangleVertexIndices;` — The vertex indices of the surface's triangles.
- L40 _public member_ `TArray<int32> TriangleLightmassSettings;` — Array for each triangle to the lightmass settings (boost, etc)

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/BuildOptions.h` (Private)


#### enum `Lightmass::ELightingSolverType`  
`enum ELightingSolverType`  
_L10-16_
- L13 _public enumerator_ `LightSolver_Direct=0` — Default direct lighting solver with no global/bounced lighting
- L15 _public enumerator_ `LightSolver_Bouncy` — GI solver type

#### class `Lightmass::FLightingBuildOptions`  
`class FLightingBuildOptions`  
_L21-34_
- desc: A set of parameters specifying how static lighting is rebuilt.
- L25 _public function_ `FLightingBuildOptions() : bPerformFullQualityBuild(true) , LightSolverType(LightSolver_Direct)`
- L31 _public member_ `bool bPerformFullQualityBuild;` — Whether to use fast or pretty lighting build.
- L33 _public member_ `ELightingSolverType LightSolverType;` — Current light solver type desired

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/Collision.h` (Private)


#### enum `Lightmass::ELightRayIntersectionFlags`  
`enum ELightRayIntersectionFlags`  
_L21-30_
- desc: Flags set on a FLightRay that control how the ray is intersected with the scene.
- L23 _public enumerator_ `LIGHTRAY_NONE = 1<<0`
- L25 _public enumerator_ `LIGHTRAY_SELFSHADOWDISABLE = 1<<1` — Whether the ray should intersect with triangles from the ray's mesh.
- L27 _public enumerator_ `LIGHTRAY_STATIC_AND_OPAQUEONLY = 1<<2` — Whether the ray should only intersect with static, opaque materials, and exlude masked and translucent materials.
- L29 _public enumerator_ `LIGHTRAY_FLIP_SIDEDNESS = 1<<3` — Whether to flip what is considered a backface.  This is useful for getting consistent backface culling regardless of which side of a ray the trace starts at.

#### class `Lightmass::FLightRay`  
`class FLightRay`  
_L33-77_
- desc: A line segment representing a direct light path through the scene.
- L37 _public member_ `FVector4f Start;`
- L38 _public member_ `FVector4f End;`
- L39 _public member_ `FVector4f Direction;`
- L40 _public member_ `float Length;`
- L43 _public member_ `const FStaticLightingMapping* Mapping;` — The mapping that the ray originated from, used for conditional intersections.
- L44 _public member_ `const FStaticLightingMesh* Mesh;`
- L45 _public member_ `const FLight* Light;`
- L47 _public member_ `uint32 TraceFlags;`
- L49 _public function_ `FLightRay()`
- L52 _public function_ `FLightRay(const FVector4f& InStart, const FVector4f& InEnd, const FStaticLightingMapping* InMapping, const FLight* InLight, uint32 InTraceFlags = LIGHTRAY_NONE) : Start(InStart) , End(InEnd) , Direction(InEnd - InStart) , Mapping(InMapping) , Mesh(InMapping ? InMapping->Mesh : NULL) , Light(InLight) , TraceFlags(InTraceFlags)` — Initialization constructor.
- L65 _public function_ `void ClipAgainstIntersectionFromStart(const FVector4f& IntersectionPoint)` — Clips the light ray from the original start to an intersection point.
- L72 _public function_ `void ClipAgainstIntersectionFromEnd(const FVector4f& IntersectionPoint)` — Clips the light ray from the original end to an intersection point.

#### struct `Lightmass::FStaticLightingMeshInfo`  
`struct FStaticLightingMeshInfo`  
_L82-94_
- desc: Information about a single mesh that got aggregated.
- L85 _public member_ `const int32 BaseIndex;` — First index of the mesh into FStaticLightingAggregateMesh::Vertices, UVs and LightmapUVs
- L86 _public member_ `const FStaticLightingMesh* Mesh;`
- L88 _public function_ `FStaticLightingMeshInfo(int32 InBaseIndex, const FStaticLightingMesh* InMesh) : BaseIndex(InBaseIndex), Mesh(InMesh)`

#### struct `Lightmass::FTriangleSOAPayload`  
`struct FTriangleSOAPayload`  
_L97-120_
- desc: Each FTriangleSOA in the kDOP references 4 of these, one for each triangle it represents.
- L100 _public function_ `FTriangleSOAPayload(const FStaticLightingMeshInfo* InMeshInfo, const FStaticLightingMapping* InMapping, int32 InElementIndex, int32 VertexIndex1, int32 VertexIndex2, int32 VertexIndex3 ) : MeshInfo(InMeshInfo) , Mapping(InMapping) , ElementIndex(InElementIndex)` — Constructor.
- L113 _public member_ `const FStaticLightingMeshInfo* MeshInfo;` — Information about the Mesh that uses the triangle.
- L115 _public member_ `const FStaticLightingMapping* Mapping;` — The Mapping that uses the triangle.
- L117 _public member_ `int32 ElementIndex;` — Mesh element index
- L119 _public member_ `int32 VertexIndex[3];` — Index into FStaticLightingAggregateMesh::Vertices, UVs and LightmapUVs, for each of the vertices of the triangle.

#### class `Lightmass::FStaticLightingAggregateMesh`  
`class FStaticLightingAggregateMesh`  
_L123-199_
- desc: The static lighting mesh.
- L128 _public prototype_ `FStaticLightingAggregateMesh(const FScene& InScene);` — Initialization constructor.
- L130 _public function_ `virtual ~FStaticLightingAggregateMesh()`
- L136 _public prototype_ `virtual void AddMesh(const FStaticLightingMesh* Mesh, const FStaticLightingMapping* Mapping) = 0;` — Merges a mesh into the shadow mesh. @param Mesh - The mesh the triangle comes from.
- L145 _public prototype_ `virtual void ReserveMemory( int32 NumMeshes, int32 NumVertices, int32 NumTriangles ) = 0;` — Pre-allocates memory ahead of time, before calling AddMesh() a bunch of times. @param NumMeshes		- Expected number of meshes which will be added @param NumVertices	- Expected number of vertices which will be added @param NumTriangles	- Expected number of triangles which will be added
- L148 _public prototype_ `virtual void PrepareForRaytracing() = 0;` — Prepares the mesh for raytracing.
- L150 _public prototype_ `virtual void DumpStats() const = 0;`
- L153 _public function_ `virtual void DumpCheckStats() const` — Used to dump additional stats about intersect checks that where done
- L155 _public function_ `virtual void DumpPostBuildStats() const`
- L170 _public prototype_ `virtual bool IntersectLightRay( const FLightRay& LightRay, bool bFindClosestIntersection, bool bCalculateTransmission, bool bDirectShadowingRay, class FCoherentRayCache& CoherentRayCache, FLightRayIntersection& Intersection) const = 0;` — Checks a light ray for intersection with the shadow mesh. @param LightRay - The line segment to check for intersection. @param bFindClosestIntersection - true if the intersection must return the closest intersection.  false if it may return any intersection. This can be used as an optimization for rays which only need to know if there was an intersection or not, but not any other information about the intersection. Note: bFindClosestIntersection == false currently does not handle masked materials correctly, it treats them as if they were opaque. However, bFindClosestIntersection == false does work correctly in conjunction with LIGHTRAY_STATIC_AND_OPAQUEONLY. @param bCalculateTransmission - Whether to keep track of transmission or not.  If this is true, bFindClosestIntersection must also be true. @param bDirectShadowingRay - Whether this ray is being used to calculate direct shadowing. @param CoherentRayCache - The calling thread's collision cache. @param [out] Intersection - The intersection of between the light ray and the mesh. @return true if there is an intersection, false otherwise
- L178 _public prototype_ `FBox3f GetBounds() const;`
- L181 _public function_ `float GetSurfaceArea() const` — The total surface area of everything in the aggregate mesh
- L183 _public function_ `float GetSurfaceAreaWithinImportanceVolume() const` — The total surface area of everything in the aggregate mesh within the importance volume, if there is one
- L187 _protected member_ `const FScene& Scene;`
- L190 _protected member_ `bool bHasShadowCastingPrimitives;` — True if some mesh where added to the scene.
- L193 _protected member_ `FBox3f SceneBounds;` — The bounding box of everything in the aggregate mesh.
- L196 _protected member_ `float SceneSurfaceArea;` — The total surface area of everything in the aggregate mesh
- L198 _protected member_ `float SceneSurfaceAreaWithinImportanceVolume;` — The total surface area of everything in the aggregate mesh within the importance volume, if there is one

#### class `Lightmass::FDefaultAggregateMesh`  
`class FDefaultAggregateMesh final : public FStaticLightingAggregateMesh`  
_L201-272_
- inherits: `FStaticLightingAggregateMesh`
- L206 _public function_ `FDefaultAggregateMesh(const FScene& InScene) : FStaticLightingAggregateMesh(InScene)` — Initialization constructor.
- L208 _public prototype_ `virtual ~FDefaultAggregateMesh();`
- L210 _public function_ `FORCEINLINE const FVector2f& GetUV(uint32 Index) const`
- L215 _public function_ `FORCEINLINE const FVector2f& GetLightmapUV(uint32 Index) const`
- L220 _public prototype_ `virtual void AddMesh(const FStaticLightingMesh* Mesh, const FStaticLightingMapping* Mapping) override;`
- L222 _public prototype_ `void AddMeshForVoxelization(const FStaticLightingMesh* Mesh, const FStaticLightingMapping* Mapping, bool bUseForInstancing = false);`
- L224 _public prototype_ `virtual void ReserveMemory( int32 NumMeshes, int32 NumVertices, int32 NumTriangles ) override;`
- L226 _public prototype_ `virtual void PrepareForRaytracing() override;`
- L228 _public prototype_ `virtual void DumpStats() const override;`
- L230 _public prototype_ `virtual void DumpPostBuildStats() const override;`
- L232 _public prototype_ `virtual bool IntersectLightRay( const FLightRay& LightRay, bool bFindClosestIntersection, bool bCalculateTransmission, bool bDirectShadowingRay, class FCoherentRayCache& CoherentRayCache, FLightRayIntersection& Intersection) const override;`
- L240 _public prototype_ `const FStaticLightingMesh* IntersectBox(const FBox3f Box) const;`
- L247 _private member_ `TkDOPTree<const FStaticLightingAggregateMeshDataProvider,uint32> kDopTree;` — The world-space kDOP which is used by the simple meshes in the world.
- L250 _private member_ `TArray<FkDOPBuildCollisionTriangle<uint32> > kDOPTriangles;` — The triangles used to build the kDOP, valid until PrepareForRaytracing is called.
- L253 _private member_ `TArray<FTriangleSOAPayload> TrianglePayloads;` — TriangleSOA payload. Each TriangleSOA in the kDOP references 4 of these (one for each of the 4 triangles in a TriangleSOA).
- L256 _private member_ `TArray<const FStaticLightingMeshInfo*> MeshInfos;` — Information about the meshes used in the kDOP tree.
- L262 _private member_ `TArray<FVector4f> Vertices;` — The vertices used by the kDOP. @todo - should all of these vertex attributes be stored in the same array? (ArrayOfStructures instead of SoA)
- L265 _private member_ `TArray<FVector2f> UVs;` — The texture coordinates used by the kDOP.
- L268 _private member_ `TArray<FVector2f> LightmapUVs;` — The lightmap coordinates used by the kDOP.

#### class `Lightmass::FCoherentRayCache`  
`class FCoherentRayCache`  
_L275-302_
- desc: Information which is cached while processing a group of coherent rays.
- L278 _public member_ `uint64 NumFirstHitRaysTraced;`
- L279 _public member_ `uint64 NumBooleanRaysTraced;`
- L280 _public member_ `float FirstHitRayTraceTime;`
- L281 _public member_ `float BooleanRayTraceTime;`
- L287 _public member_ `uint32 kDOPNodeIndex;` — Stores the index of the last hit kDOP node when doing a boolean visibility check. Used to optimize coherent boolean visibliity traces.
- L290 _public function_ `FCoherentRayCache() : NumFirstHitRaysTraced(0), NumBooleanRaysTraced(0), FirstHitRayTraceTime(0), BooleanRayTraceTime(0), kDOPNodeIndex(0xFFFFFFFF)` — Initialization constructor.
- L298 _public function_ `void Clear()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Lightmass`
- L18 _variable_ `const float TRIANGLE_AREA_THRESHOLD =0.00001f;` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/Lighting/Embree.h` (Private)


#### struct `Lightmass::FEmbreeTransmissionAccumulator`  
`struct FEmbreeTransmissionAccumulator`  
_L24-34_
- desc: Accumulates transmission color, and store the distance. This is required since Embree test collision in any order, possibly accumulating transmission that are being collision
- L26 _public member_ `TArray<FLinearColor, TInlineAllocator<64> > Colors;`
- L27 _public function_ `FORCEINLINE void Push(const FLinearColor& Color, float tFar)`
- L32 _public prototype_ `void Resolve(FLinearColor& FinalColor, float tCollide);`
- L33 _public prototype_ `void Resolve(FLinearColor& FinalColor);`

#### struct `Lightmass::FEmbreeContext`  
`struct FEmbreeContext : public RTCRayQueryContext #else struct FEmbreeContext : public RTCIntersectContext #endif`  
_L38-68_
- inherits: `RTCRayQueryContext`
- L43 _public prototype_ `FEmbreeContext( const FStaticLightingMesh* InShadowMesh, const FStaticLightingMesh* InMappingMesh, uint32 InTraceFlags, bool InFindClosestIntersection, bool InCalculateTransmission, bool InDirectShadowingRay );`
- L52 _public member_ `const FStaticLightingMesh* ShadowMesh;` — Controls self shadow behavior, such as only self shadow and no self shadow.
- L53 _public member_ `const FStaticLightingMesh* MappingMesh;` — Controls LOD behavior to control which mesh are allowed to cast shadows
- L54 _public member_ `uint32 TraceFlags;`
- L55 _public member_ `bool bFindClosestIntersection;`
- L56 _public member_ `bool bCalculateTransmission;`
- L57 _public member_ `bool bDirectShadowingRay;`
- L58 _public member_ `bool bStaticAndOpaqueOnly;`
- L59 _public member_ `bool bTwoSidedCollision;`
- L60 _public member_ `bool bFlipSidedness;`
- L64 _public member_ `int32 ElementIndex;` — Outputs Warning: EmbreeFilterFunc must only modify these!
- L65 _public member_ `FVector2f TextureCoordinates;` — Material Coordinates
- L66 _public member_ `FVector2f LightmapCoordinates;`
- L67 _public member_ `FEmbreeTransmissionAccumulator TransmissionAcc;`

#### struct `Lightmass::FEmbreeRay`  
`struct FEmbreeRay : public RTCRay`  
_L70-98_
- inherits: `RTCRay`
- L72 _public prototype_ `FEmbreeRay( const FStaticLightingMesh* InShadowMesh, const FStaticLightingMesh* InMappingMesh, uint32 InTraceFlags, bool InFindClosestIntersection, bool InCalculateTransmission, bool InDirectShadowingRay );`
- L82 _public member_ `const FStaticLightingMesh* ShadowMesh;` — Inputs required by filter functions
- L83 _public member_ `const FStaticLightingMesh* MappingMesh;` — Controls LOD behavior to control which mesh are allowed to cast shadows
- L84 _public member_ `uint32 TraceFlags;`
- L85 _public member_ `bool bFindClosestIntersection;`
- L86 _public member_ `bool bCalculateTransmission;`
- L87 _public member_ `bool bDirectShadowingRay;`
- L88 _public member_ `bool bStaticAndOpaqueOnly;`
- L89 _public member_ `bool bTwoSidedCollision;`
- L90 _public member_ `bool bFlipSidedness;`
- L94 _public member_ `int32 ElementIndex;` — Additional Outputs. Warning: EmbreeFilterFunc must only modify these!  Nothing else is copied back to FEmbreeRay4.
- L95 _public member_ `FVector2f TextureCoordinates;` — Material Coordinates
- L96 _public member_ `FVector2f LightmapCoordinates;`
- L97 _public member_ `FEmbreeTransmissionAccumulator TransmissionAcc;`

#### struct `Lightmass::FEmbreeRay4`  
`struct FEmbreeRay4 : public RTCRay4`  
_L101-182_
- inherits: `RTCRay4`
- L103 _public prototype_ `FEmbreeRay4( const FStaticLightingMesh* InShadowMesh, const FStaticLightingMesh* InMappingMesh, uint32 InTraceFlags, bool InFindClosestIntersection, bool InCalculateTransmission, bool InDirectShadowingRay );`
- L112 _public function_ `inline FEmbreeRay BuildSingleRay(int32 RayIndex)`
- L155 _public function_ `inline void SetFromSingleRay(FEmbreeRay SingleRay, int32 RayIndex)`
- L167 _public member_ `const FStaticLightingMesh* ShadowMesh;` — Inputs required by filter functions
- L168 _public member_ `const FStaticLightingMesh* MappingMesh;` — Controls LOD behavior to control which mesh are allowed to cast shadows
- L169 _public member_ `uint32 TraceFlags;`
- L170 _public member_ `bool bFindClosestIntersection;`
- L171 _public member_ `bool bCalculateTransmission;`
- L172 _public member_ `bool bDirectShadowingRay;`
- L173 _public member_ `bool bStaticAndOpaqueOnly;`
- L174 _public member_ `bool bTwoSidedCollision;`
- L175 _public member_ `bool bFlipSidedness;`
- L178 _public member_ `int32 ElementIndex[4];` — Additional Outputs.
- L179 _public member_ `FVector2f TextureCoordinates[4];` — Material Coordinates
- L180 _public member_ `FVector2f LightmapCoordinates[4];`
- L181 _public member_ `FEmbreeTransmissionAccumulator TransmissionAcc[4];`

#### struct `Lightmass::FEmbreeTriangleDesc`  
`struct FEmbreeTriangleDesc`  
_L185-196_
- L187 _public member_ `int16 ElementIndex;`
- L188 _public member_ `uint16 CastShadow : 1;`
- L189 _public member_ `uint16 StaticAndOpaqueMask : 1;`
- L190 _public member_ `uint16 TwoSidedMask: 1;`
- L191 _public member_ `uint16 Translucent : 1;`
- L192 _public member_ `uint16 SurfaceDomain : 1;`
- L193 _public member_ `uint16 IndirectlyShadowedOnly : 1;`
- L194 _public member_ `uint16 Masked : 1;`
- L195 _public member_ `uint16 CastShadowAsMasked : 1;`

#### struct `Lightmass::FEmbreeGeometry`  
`struct FEmbreeGeometry`  
_L199-224_
- desc: Mapping between Embree Geometry Id and Lightmass Mesh/LOD Id
- L201 _public prototype_ `FEmbreeGeometry( RTCDevice EmbreeDevice, RTCScene EmbreeScene, const FBoxSphereBounds3f& ImportanceBounds, const FStaticLightingMesh* InMesh, const FStaticLightingMapping* InMapping, bool bUseForInstancing );`
- L210 _public member_ `const FStaticLightingMesh* Mesh;`
- L211 _public member_ `const FStaticLightingMapping* Mapping;`
- L213 _public member_ `TArray<FEmbreeTriangleDesc> TriangleDescs;` — The material ID of each triangle.
- L214 _public member_ `TArray<FVector2f> UVs;`
- L215 _public member_ `TArray<FVector2f> LightmapUVs;`
- L217 _public member_ `uint32 GeomID;` — Embree ID for this mesh.
- L219 _public member_ `float SurfaceArea;`
- L220 _public member_ `float SurfaceAreaWithinImportanceVolume;`
- L221 _public member_ `bool bHasShadowCastingPrimitives;`
- L223 _public member_ `class FEmbreeAggregateMesh* ParentAggregateMesh;`

#### class `Lightmass::FEmbreeAggregateMesh`  
`class FEmbreeAggregateMesh final : public FStaticLightingAggregateMesh`  
_L226-275_
- inherits: `FStaticLightingAggregateMesh`
- L231 _public prototype_ `FEmbreeAggregateMesh(const FScene& InScene);` — Initialization constructor.
- L233 _public prototype_ `virtual ~FEmbreeAggregateMesh();`
- L235 _public prototype_ `virtual void AddMesh(const FStaticLightingMesh* Mesh, const FStaticLightingMapping* Mapping) override;`
- L237 _public function_ `virtual void ReserveMemory( int32 NumMeshes, int32 NumVertices, int32 NumTriangles ) override`
- L240 _public prototype_ `virtual void PrepareForRaytracing() override;` — Prepares the mesh for raytracing.
- L242 _public prototype_ `virtual void DumpStats() const override;`
- L244 _public prototype_ `virtual bool IntersectLightRay( const FLightRay& LightRay, bool bFindClosestIntersection, bool bCalculateTransmission, bool bDirectShadowingRay, class FCoherentRayCache& CoherentRayCache, FLightRayIntersection& Intersection) const override;`
- L252 _public member_ `TArray<const FStaticLightingMapping*> StaticMeshInstancesToMappings;`
- L257 _private member_ `TArray<const FEmbreeGeometry*> MeshInfos;` — Information about the meshes used in the kDOP tree.
- L264 _private member_ `TMap<const FStaticMeshLOD*, FEmbreeStaticMeshGeometry> StaticMeshGeometries;`
- L267 _private member_ `RTCDevice EmbreeDevice;` — Embree scene
- L268 _private member_ `RTCScene EmbreeScene;`
- L271 _private member_ `int32 TotalNumTriangles;` — Total number of triangles in the shadow mesh
- L274 _private member_ `int32 TotalNumTrianglesInstanced;` — Total number of instanced triangles in the shadow mesh

#### struct `Lightmass::FEmbreeAggregateMesh::FEmbreeStaticMeshGeometry`  
`struct FEmbreeStaticMeshGeometry`  
_L259-263_
- L261 _public member_ `RTCScene MeshScene;`
- L262 _public member_ `FEmbreeGeometry* Geo;`

#### class `Lightmass::FEmbreeVerifyAggregateMesh`  
`class FEmbreeVerifyAggregateMesh final : public FStaticLightingAggregateMesh`  
_L277-315_
- inherits: `FStaticLightingAggregateMesh`
- L279 _private typedef_ `typedef FStaticLightingAggregateMesh Super;`
- L283 _public prototype_ `FEmbreeVerifyAggregateMesh(const FScene& InScene);`
- L285 _public prototype_ `virtual void AddMesh(const FStaticLightingMesh* Mesh, const FStaticLightingMapping* Mapping) override;`
- L287 _public prototype_ `virtual void ReserveMemory( int32 NumMeshes, int32 NumVertices, int32 NumTriangles ) override;`
- L289 _public prototype_ `virtual void PrepareForRaytracing() override;`
- L291 _public prototype_ `virtual void DumpStats() const override;`
- L292 _public prototype_ `virtual void DumpCheckStats() const override;`
- L294 _public prototype_ `virtual bool IntersectLightRay( const FLightRay& LightRay, bool bFindClosestIntersection, bool bCalculateTransmission, bool bDirectShadowingRay, class FCoherentRayCache& CoherentRayCache, FLightRayIntersection& Intersection) const override;`
- L304 _private prototype_ `static bool VerifyTransmissions(const FLightRayIntersection& EmbreeIntersection, const FLightRayIntersection& ClosestIntersection);`
- L305 _private prototype_ `static bool VerifyChecks(const FLightRayIntersection& EmbreeIntersection, const FLightRayIntersection& ClosestIntersection, bool bFindClosestIntersection);`
- L307 _private member_ `FDefaultAggregateMesh DefaultAggregate;`
- L308 _private member_ `FEmbreeAggregateMesh EmbreeAggregate;`
- L310 _private member_ `mutable volatile int64 TransmissionMismatchCount;`
- L311 _private member_ `mutable volatile int64 TransmissionEqualCount;`
- L313 _private member_ `mutable volatile int64 CheckEqualCount;`
- L314 _private member_ `mutable volatile int64 CheckMismatchCount;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`
- L15 _prototype_ `void EmbreeFilterFunc(const RTCFilterFunctionNArguments* args);` (scope `Lightmass`)
- L17 _prototype_ `void EmbreeFilterFunc(void* UserPtr, RTCRay& InRay);` (scope `Lightmass`)
- L18 _prototype_ `void EmbreeFilterFunc4(const void* valid, void* UserPtr, RTCRay4& InRay);` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/Lighting/FluidSurface.h` (Private)


#### class `Lightmass::FFluidSurfaceStaticLightingMesh`  
`class FFluidSurfaceStaticLightingMesh : public FStaticLightingMesh, public FFluidSurfaceStaticLightingMeshData`  
_L13-21_
- inherits: `FStaticLightingMesh,FFluidSurfaceStaticLightingMeshData`
- desc: Represents the triangles of a fluid surface primitive to the static lighting system.
- L17 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const;` — FStaticLightingMesh interface.
- L18 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L20 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`

#### class `Lightmass::FFluidSurfaceStaticLightingTextureMapping`  
`class FFluidSurfaceStaticLightingTextureMapping : public FStaticLightingTextureMapping`  
_L24-28_
- inherits: `FStaticLightingTextureMapping`
- desc: Represents a fluid surface primitive with texture mapped static lighting.
- L27 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/GatheredLightingSample.h` (Private)


#### class `Lightmass::TGatheredLightSample`  
`template <int32 SHOrder> class TGatheredLightSample`  
_L17-89_
- desc: The light incident for a point on a surface, in the representation used when gathering lighting. This representation is additive, and allows for accumulating lighting contributions in-place.
- L22 _public member_ `TSHVectorRGB<SHOrder> SHVector;` — World space incident lighting.
- L25 _public member_ `FLinearColor IncidentLighting;` — Incident lighting including dot(N, L) where N is the smoothed vertex normal.
- L28 _public member_ `float SHCorrection;` — Correction factor to force SH as applied to a flat normal map to be 1 to get purely directional data.
- L31 _public member_ `FVector3f SkyOcclusion;` — Sky bent normal, points toward the most unoccluded direction, and the length is the visibility amount (0 = occluded, 1 = visible).
- L33 _public member_ `float AOMaterialMask;`
- L36 _public function_ `TGatheredLightSample()` — Initialization constructor.
- L44 _public function_ `TGatheredLightSample(EForceInit)`
- L57 _public prototype_ `void AddWeighted(const TGatheredLightSample& OtherSample, float Weight);` — Adds a weighted light sample to this light sample. @param OtherSample - The sample to add. @param Weight - The weight to multiply the other sample by before addition.
- L59 _public prototype_ `void ApplyOcclusion(float Occlusion);`
- L61 _public function_ `inline void SetSkyOcclusion(FVector3f InSkyOcclusion)`
- L66 _public prototype_ `bool AreFloatsValid() const;`
- L68 _public function_ `TGatheredLightSample operator*(float Scalar) const`
- L79 _public function_ `TGatheredLightSample operator+(const TGatheredLightSample& SampleB) const`

#### class `Lightmass::FGatheredLightSampleUtil`  
`class FGatheredLightSampleUtil`  
_L91-110_
- L101 _public prototype_ `template <int32 SHOrder> static TGatheredLightSample<SHOrder> AmbientLight(const FLinearColor& Color);` — Constructs a light sample representing an ambient light. Note: Lighting contributed through this method won't have the same final brightness as PointLightWorldSpace, because of the dot(N, L) @param Color - The color/intensity of the light at the sample point.
- L109 _public prototype_ `template <int32 SHOrder> static TGatheredLightSample<SHOrder> PointLightWorldSpace(const FLinearColor& Color, const FVector4f& TangentDirection, const FVector4f& WorldDirection);` — Constructs a light sample representing a point light. @param Color - The color/intensity of the light at the sample point. @param Direction - The direction toward the light at the sample point.

#### class `Lightmass::FGatheredLightMapSample`  
`class FGatheredLightMapSample`  
_L115-160_
- L118 _public member_ `FGatheredLightSample HighQuality;`
- L119 _public member_ `FGatheredLightSample LowQuality;`
- L122 _public member_ `bool bIsMapped;` — True if this sample maps to a valid point on a triangle.  This is only meaningful for texture lightmaps.
- L124 _public function_ `FGatheredLightMapSample() : bIsMapped(false)`
- L128 _public function_ `FGatheredLightMapSample(const FGatheredLightSample& Sample) : HighQuality(Sample) , LowQuality(Sample) , bIsMapped(false)`
- L134 _public function_ `FGatheredLightMapSample& operator=(const FGatheredLightSample& Sample)`
- L146 _public function_ `void AddWeighted(const FGatheredLightSample& OtherSample, float Weight)` — Adds a weighted light sample to this light sample. @param OtherSample - The sample to add. @param Weight - The weight to multiply the other sample by before addition.
- L152 _public function_ `void ApplyOcclusion(float Occlusion)`
- L159 _public prototype_ `FLightSample ConvertToLightSample(bool bDebugThisSample) const;` — Converts an FGatheredLightMapSample into a FLightSample.

#### class `Lightmass::TFinalGatherSample`  
`template <int32 SHOrder> class TFinalGatherSample : public TGatheredLightSample<SHOrder>`  
_L164-232_
- inherits: `TGatheredLightSample<SHOrder>`
- desc: The lighting information gathered for one final gather sample
- L169 _public member_ `float Occlusion;` — Occlusion factor of the sample, 0 is completely unoccluded, 1 is completely occluded.
- L174 _public member_ `TGatheredLightSample<SHOrder> StationarySkyLighting;` — A light sample for sky lighting.  This has to be stored separately to support stationary sky lights only contributing to low quality lightmaps.
- L177 _public function_ `TFinalGatherSample() : TGatheredLightSample<SHOrder>(), Occlusion(0.0f)` — Initialization constructor.
- L182 _public function_ `TFinalGatherSample(EForceInit) : TGatheredLightSample<SHOrder>(ForceInit), Occlusion(0.0f)`
- L192 _public prototype_ `void AddWeighted(const TFinalGatherSample& OtherSample, float Weight);` — Adds a weighted light sample to this light sample. @param OtherSample - The sample to add. @param Weight - The weight to multiply the other sample by before addition.
- L200 _public function_ `template<int32 OtherOrder> inline void AddWeighted(const TGatheredLightSample<OtherOrder>& OtherSample, float Weight)` — Adds a weighted light sample to this light sample. @param OtherSample - The sample to add. @param Weight - The weight to multiply the other sample by before addition.
- L205 _public function_ `inline void SetOcclusion(float InOcclusion)`
- L210 _public function_ `inline void AddIncomingRadiance(const FLinearColor& IncomingRadiance, float Weight, const FVector4f& TangentSpaceDirection, const FVector4f& WorldSpaceDirection)`
- L215 _public prototype_ `bool AreFloatsValid() const;`
- L217 _public function_ `TFinalGatherSample operator*(float Scalar) const`
- L225 _public function_ `TFinalGatherSample operator+(const TFinalGatherSample& SampleB) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`
- L112 _typedef_ `typedef TGatheredLightSample<2> FGatheredLightSample;` (scope `Lightmass`)
- L113 _typedef_ `typedef TGatheredLightSample<3> FGatheredLightSample3;` (scope `Lightmass`)
- L234 _typedef_ `typedef TFinalGatherSample<2> FFinalGatherSample;` (scope `Lightmass`)
- L235 _typedef_ `typedef TFinalGatherSample<3> FFinalGatherSample3;` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/Lighting/Landscape.h` (Private)


#### class `Lightmass::FLandscapeStaticLightingMesh`  
`class FLandscapeStaticLightingMesh : public FStaticLightingMesh, public FLandscapeStaticLightingMeshData`  
_L14-40_
- inherits: `FStaticLightingMesh,FLandscapeStaticLightingMeshData`
- desc: Represents the triangles of a Landscape primitive to the static lighting system.
- L17 _public prototype_ `FORCEINLINE void GetStaticLightingVertex(int32 VertexIndex, FStaticLightingVertex& OutVertex) const;`
- L19 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const;` — FStaticLightingMesh interface.
- L20 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L22 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L25 _public prototype_ `FORCEINLINE void VertexIndexToXY(int32 VertexIndex, int32& OutX, int32& OutY) const;` — Accessors from FLandscapeDataInterface
- L26 _public prototype_ `FORCEINLINE void QuadIndexToXY(int32 QuadIndex, int32& OutX, int32& OutY) const;`
- L27 _public prototype_ `FORCEINLINE const FColor* GetHeightData( int32 LocalX, int32 LocalY ) const;`
- L28 _public prototype_ `FORCEINLINE void GetTriangleIndices(int32 QuadIndex,int32 TriNum,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L31 _public function_ `virtual bool IsAlwaysOpaqueForVisibility() const override` — We always want to compute visibility for landscape meshes, regardless of material blend mode
- L34 _private member_ `TArray<FColor> HeightMap;`
- L36 _private member_ `int32 NumVertices;` — Cache
- L37 _private member_ `int32 NumQuads;`
- L38 _private member_ `float UVFactor;`
- L39 _private member_ `bool bReverseWinding;`

#### class `Lightmass::FLandscapeStaticLightingTextureMapping`  
`class FLandscapeStaticLightingTextureMapping : public FStaticLightingTextureMapping`  
_L43-47_
- inherits: `FStaticLightingTextureMapping`
- desc: Represents a landscape primitive with texture mapped static lighting.
- L46 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`

#### class `Lightmass::FLandscapeStaticLightingGlobalVolumeMapping`  
`class FLandscapeStaticLightingGlobalVolumeMapping : public FLandscapeStaticLightingTextureMapping`  
_L53-69_
- inherits: `FLandscapeStaticLightingTextureMapping`
- desc: A mapping that represents an object which is going to use the global volumetric lightmap. Hack: currently represented as a texture lightmap to Lightmass for the purposes of surface caching of light (radiosity + direct lighting).
- L57 _public function_ `FLandscapeStaticLightingGlobalVolumeMapping()`
- L60 _public function_ `virtual class FLandscapeStaticLightingGlobalVolumeMapping* GetLandscapeVolumeMapping() override`
- L65 _public function_ `virtual const FLandscapeStaticLightingGlobalVolumeMapping* GetLandscapeVolumeMapping() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LANDSCAPE_ZSCALE (1.0f/128.0f)`
- L11 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/Lighting.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define ALLOW_LIGHTMAP_SAMPLE_DEBUGGING 0` — Set to 1 to allow selecting lightmap texels by holding down T and left clicking in the editor, And having debug information about that texel tracked during subsequent lighting rebuilds. Have to enable 'r.TexelDebugging' in the editor as well.
- L27 _typedef_ `typedef void* RTCDevice;`
- L41 _namespace_ `namespace Lightmass`
- L44 _typedef_ `typedef FStaticLightingAggregateMesh FStaticLightingAggregateMeshType;` (scope `Lightmass`)
- L55 _namespace_ `namespace Lightmass`
- L57 _externvar_ `extern double GStartupTime;` (scope `Lightmass`)
- L61 _macro_ `#define WORLD_MAX 2097152.0 /* Maximum size of the world */` — LWC_TODO: Lightmass definition of WORLD_MAX is no longer in sync with EngineDefines.h. Is this acceptable?
- L62 _macro_ `#define HALF_WORLD_MAX ( WORLD_MAX*0.5f ) /* Half the maximum size of the world */` — #define WORLD_MAX			2097152.0			  Maximum size of the world

### `Source/Programs/UnrealLightmass/Private/Lighting/LightingCache.h` (Private)


#### class `Lightmass::FIrradianceCacheStats`  
`class FIrradianceCacheStats`  
_L12-33_
- L16 _public member_ `uint64 NumCacheLookups;`
- L17 _public member_ `uint64 NumRecords;`
- L18 _public member_ `uint64 NumInsideGeometry;`
- L20 _public function_ `FIrradianceCacheStats() : NumCacheLookups(0), NumRecords(0), NumInsideGeometry(0)`
- L26 _public function_ `FIrradianceCacheStats& operator+=(const FIrradianceCacheStats& B)`

#### class `Lightmass::FQuantizedHemisphereDirection`  
`class FQuantizedHemisphereDirection`  
_L46-81_
- L50 _public function_ `FQuantizedHemisphereDirection() : QuantizedTheta(0), QuantizedPhi(0)`
- L55 _public function_ `FQuantizedHemisphereDirection(const FVector4f& UnitTangentSpaceDirection)`
- L68 _public function_ `FVector4f GetDirection() const`
- L79 _private member_ `uint8 QuantizedTheta;`
- L80 _private member_ `uint8 QuantizedPhi;`

#### class `Lightmass::FFinalGatherHitPoint`  
`class FFinalGatherHitPoint`  
_L83-96_
- L87 _public function_ `FFinalGatherHitPoint() : MappingIndex(-1), MappingSurfaceCoordinate(-1), Weight(0.0f)`
- L93 _public member_ `int32 MappingIndex;`
- L94 _public member_ `int32 MappingSurfaceCoordinate;`
- L95 _public member_ `FFloat16 Weight;`

#### class `Lightmass::FLightingCacheGatherInfo`  
`class FLightingCacheGatherInfo`  
_L103-123_
- desc: The information needed by the lighting cache from a uniform sampled integration of the hemisphere in order to create a lighting record at that point.
- L106 _public member_ `float MinDistance;`
- L107 _public member_ `float BackfacingHitsFraction;`
- L109 _public member_ `TArray<FLinearColor> PreviousIncidentRadiances;` — Incident radiance and distance from each hemisphere sample.
- L110 _public member_ `TArray<float> PreviousDistances;`
- L111 _public member_ `class FGatherHitPoints* HitPointRecorder;`
- L113 _public function_ `FLightingCacheGatherInfo() : MinDistance(FLT_MAX), BackfacingHitsFraction(0), HitPointRecorder(NULL)`
- L119 _public function_ `inline void UpdateOnHit(float IntersectionDistance)`

#### class `Lightmass::FLightingCacheBase`  
`class FLightingCacheBase`  
_L125-143_
- L129 _public member_ `float InterpolationAngleNormalization;` — See FIrradianceCachingSettings for descriptions of these or the variables they are based on.
- L130 _public member_ `float InterpolationAngleNormalizationSmooth;`
- L131 _public member_ `const float MinCosPointBehindPlane;`
- L132 _public member_ `const float DistanceSmoothFactor;`
- L133 _public member_ `const bool bUseIrradianceGradients;`
- L134 _public member_ `const bool bShowGradientsOnly;`
- L135 _public member_ `const bool bVisualizeIrradianceSamples;`
- L136 _public member_ `const int32 BounceNumber;`
- L137 _public member_ `int32 NextRecordId;`
- L138 _public member_ `mutable FIrradianceCacheStats Stats;`
- L139 _public member_ `const class FStaticLightingSystem& System;`
- L142 _public prototype_ `FLightingCacheBase(const FStaticLightingSystem& InSystem, int32 InBounceNumber);` — Initialization constructor.

#### class `Lightmass::TLightingCache`  
`template<class SampleType> class TLightingCache : public FLightingCacheBase`  
_L147-297_
- inherits: `FLightingCacheBase`
- desc: A lighting cache.
- L208 _public typedef_ `typedef TOctree<FRecord<SampleType>,FRecordOctreeSemantics> LightingOctreeType;` — The type of lighting cache octree nodes.
- L228 _public function_ `TLightingCache(const FBox3f& InBoundingBox, const FStaticLightingSystem& System, int32 InBounceNumber) : FLightingCacheBase(System, InBounceNumber), Octree(InBoundingBox.GetCenter(),InBoundingBox.GetExtent().GetMax())`
- L234 _public function_ `void AddRecord(FRecord<SampleType>& Record, bool bInsideGeometry, bool bAddToStats)` — Adds a lighting record to the cache.
- L251 _public function_ `void GetAllRecords(TArray<FRecord<SampleType> >& Records) const`
- L274 _public function_ `LightingOctreeType& GetOctree()`
- L282 _public prototype_ `bool InterpolateLighting( const FFullStaticLightingVertex& Vertex, bool bFirstPass, bool bDebugThisSample, float SecondInterpolationSmoothnessReduction, SampleType& OutLighting, SampleType& OutSecondLighting, float& OutBackfacingHitsFraction, TArray<FDebugLightingCacheRecord>& DebugCacheRecords, class FInfluencingRecordCollector* RecordCollector = NULL) const;` — Interpolates nearby lighting records for a vertex. @param Vertex - The vertex to interpolate the lighting for. @param OutLighting - If true is returned, contains the blended lighting records that were found near the point. @return true if nearby records were found with enough relevance to interpolate this point's lighting.
- L296 _private member_ `LightingOctreeType Octree;` — The lighting cache octree.
- L360 _function_ `template<class SampleType> bool TLightingCache<SampleType>::InterpolateLighting( const FFullStaticLightingVertex& Vertex, bool bFirstPass, bool bDebugThisSample, float SecondInterpolationSmoothnessReduction, SampleType& OutLighting, SampleType& OutSecondLighting, float& OutBackfacingHitsFraction, TArray<FDebugLightingCacheRecord>& DebugCacheRecords, FInfluencingRecordCollector* RecordCollector) const` — Interpolates nearby lighting records for a vertex. @param Vertex - The vertex to interpolate the lighting for. @param OutLighting - If true is returned, contains the blended lighting records that were found near the point. @return true if nearby records were found with enough relevance to interpolate this point's lighting.

#### class `Lightmass::TLightingCache::FRecord`  
`template<class RecordSampleType> class FRecord`  
_L153-203_
- desc: The irradiance for a single static lighting vertex.
- L158 _public member_ `FFullStaticLightingVertex Vertex;` — The static lighting vertex the irradiance record was computed for.
- L160 _public member_ `int32 ElementIndex;`
- L163 _public member_ `float BoundingRadius;` — Largest radius that the sample will ever have, used for insertion into spatial data structures.
- L166 _public member_ `float Radius;` — Radius of this irradiance cache record in the cache pass.
- L169 _public member_ `float InterpolationRadius;` — Radius of this irradiance cache record in the interpolation pass.
- L172 _public member_ `RecordSampleType Lighting;` — The lighting incident on an infinitely small surface at WorldPosition facing along WorldNormal.
- L175 _public member_ `FVector4f RotationalGradient;` — The rotational gradient along the vector perpendicular to both the record normal and the normal of the vertex being interpolated to, used for higher order interpolation.
- L178 _public member_ `FVector4f TranslationalGradient;` — The translational gradient from the record to the point being interpolated to, used for higher order interpolation.
- L181 _public member_ `int32 Id;` — For debugging
- L183 _public member_ `float BackfacingHitsFraction;`
- L186 _public function_ `FRecord(const FFullStaticLightingVertex& InVertex,int32 InElementIndex,const FLightingCacheGatherInfo& GatherInfo,float SampleRadius,float InOverrideRadius,const FIrradianceCachingSettings& IrradianceCachingSettings,const FStaticLightingSettings& GeneralSettings,const RecordSampleType& InLighting, const FVector4f& InRotGradient, const FVector4f& InTransGradient): Vertex(InVertex), ElementIndex(InElementIndex), Lighting(InLighting), RotationalGradient(InRotGradient), TranslationalGradient(InTransGradient), Id(-1)` — Initialization constructor.

#### struct `Lightmass::TLightingCache::FRecordOctreeSemantics`  
`struct FRecordOctreeSemantics`  
_L211-226_
- desc: The octree semantics for irradiance records.
- L217 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf * 8> ElementAllocator;`
- L219 _public function_ `static FBoxCenterAndExtent GetBoundingBox(const FRecord<SampleType>& LightingRecord)`

#### enum `Lightmass::TLightingCache::FRecordOctreeSemantics::(anonymous)`  
`enum`  
_L213-213_

#### enum `Lightmass::TLightingCache::FRecordOctreeSemantics::(anonymous)`  
`enum`  
_L214-214_

#### enum `Lightmass::TLightingCache::FRecordOctreeSemantics::(anonymous)`  
`enum`  
_L215-215_

#### class `Lightmass::FInfluencingRecord`  
`class FInfluencingRecord`  
_L299-309_
- L302 _public member_ `int32 RecordIndex;`
- L303 _public member_ `FFloat16 RecordWeight;`
- L305 _public function_ `FInfluencingRecord(int32 InRecordIndex, FFloat16 InRecordWeight) : RecordIndex(InRecordIndex), RecordWeight(InRecordWeight)`

#### class `Lightmass::FArrayRange`  
`class FArrayRange`  
_L311-322_
- L315 _public function_ `FArrayRange(int32 InStartIndex) : StartIndex(InStartIndex), NumEntries(0)`
- L320 _public member_ `int32 StartIndex;`
- L321 _public member_ `int32 NumEntries;`

#### class `Lightmass::FInfluencingRecords`  
`class FInfluencingRecords`  
_L324-332_
- L328 _public member_ `TArray<FArrayRange> Ranges;`
- L329 _public member_ `TArray<FInfluencingRecord> Data;`
- L331 _public function_ `size_t GetAllocatedSize() const`

#### class `Lightmass::FInfluencingRecordCollector`  
`class FInfluencingRecordCollector`  
_L334-351_
- L338 _public function_ `FInfluencingRecordCollector(FInfluencingRecords& InInfluencingRecords, int32 InCurrentRangeIndex) : CurrentRangeIndex(InCurrentRangeIndex), InfluencingRecords(InInfluencingRecords)`
- L343 _public function_ `void AddInfluencingRecord(int32 RecordId, float Weight)`
- L349 _public member_ `int32 CurrentRangeIndex;`
- L350 _public member_ `FInfluencingRecords& InfluencingRecords;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`
- L38 _function_ `inline float acosFast(float inX)` (scope `Lightmass`) — max absolute error 9.0x10^-3 Eberly's polynomial degree 1 - respect bounds input [-1, 1] and output [0, PI]
- L213 _enumerator_ `enum { MaxElementsPerLeaf = 4 }; enum { MaxNodeDepth = 24 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf * 8> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FRecord<SampleType>& LightingRecord) {` (scope `Lightmass::TLightingCache::FRecordOctreeSemantics::__anon991077010103`)
- L214 _enumerator_ `enum { MaxNodeDepth = 24 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf * 8> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FRecord<SampleType>& LightingRecord) { return FBoxCenterAndExtent(` (scope `Lightmass::TLightingCache::FRecordOctreeSemantics::__anon991077010203`)
- L215 _enumerator_ `enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf * 8> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FRecord<SampleType>& LightingRecord) { return FBoxCenterAndExtent( LightingRecord.Vertex.WorldPosition,` (scope `Lightmass::TLightingCache::FRecordOctreeSemantics::__anon991077010303`)

### `Source/Programs/UnrealLightmass/Private/Lighting/LightingMesh.h` (Private)


#### struct `Lightmass::FStaticLightingVertex`  
`struct FStaticLightingVertex: public FStaticLightingVertexData`  
_L20-143_
- inherits: `FStaticLightingVertexData`
- desc: The vertex data used to build static lighting.
- L22 _public function_ `FStaticLightingVertex()`
- L24 _public function_ `FStaticLightingVertex(const FMinimalStaticLightingVertex& InVertex)`
- L38 _public function_ `inline FVector4f TransformWorldVectorToTangent(const FVector4f& WorldVector) const` — Transforms a world space vector into the tangent space of this vertex.
- L49 _public function_ `inline FVector4f TransformTangentVectorToWorld(const FVector4f& TangentVector) const` — Transforms a vector in the tangent space of this vertex into world space.
- L66 _public function_ `inline void GenerateVertexTangents()` — Generates WorldTangentX and WorldTangentY from WorldTangentZ such that the tangent basis is orthonormal.

#### struct `Lightmass::FFullStaticLightingVertex`  
`struct FFullStaticLightingVertex : public FStaticLightingVertex`  
_L149-219_
- inherits: `FStaticLightingVertex`
- desc: A vertex for static lighting that contains a tangent space around the triangle normal. This is useful for generating rays from a tangent space sample set, because the smoothed normal will produce samples that self-intersect even on a plane.
- L151 _public member_ `FVector4f TriangleTangentX;`
- L152 _public member_ `FVector4f TriangleTangentY;`
- L153 _public member_ `FVector4f TriangleNormal;`
- L156 _public function_ `inline FVector4f TransformWorldVectorToTriangleTangent(const FVector4f& WorldVector) const` — Transforms a world space vector into the tangent space of this triangle.
- L167 _public function_ `inline FVector4f TransformTriangleTangentVectorToWorld(const FVector4f& TriangleTangentVector) const` — Transforms a vector in the tangent space of this triangle into world space.
- L184 _public function_ `inline void GenerateTriangleTangents()` — Generates TriangleTangentX and TriangleTangentY from TriangleNormal such that the tangent basis is orthonormal.
- L203 _public prototype_ `void ApplyVertexModifications(int32 ElementIndex, bool bUseNormalMapsForLighting, const class FStaticLightingMesh* Mesh);`
- L205 _public function_ `inline void ComputePathDirections(const FVector4f& TriangleTangentPathDirection, FVector4f& WorldPathDirection, FVector4f& TangentPathDirection) const`

#### class `Lightmass::FLightRayIntersection`  
`class FLightRayIntersection`  
_L222-267_
- desc: The result of an intersection between a light ray and the scene.
- L227 _public member_ `uint32 bIntersects : 1;` — true if the light ray intersected opaque scene geometry.
- L230 _public member_ `FMinimalStaticLightingVertex IntersectionVertex;` — The differential geometry which the light ray intersected with, only valid if the ray intersected.
- L233 _public member_ `FLinearColor Transmission;` — Transmission of the ray, valid whether the ray intersected or not as long as Transmission was requested from FStaticLightingAggregateMesh::IntersectLightRay.
- L236 _public member_ `const class FStaticLightingMesh* Mesh;` — The mesh that was intersected by the ray, only valid if the ray intersected.
- L239 _public member_ `const class FStaticLightingMapping* Mapping;` — The mapping that was intersected by the ray, only valid if the ray intersected.
- L242 _public member_ `int32 ElementIndex;` — Primitive type specific element index associated with the triangle that was hit, only valid if the ray intersected.
- L245 _public function_ `FLightRayIntersection()` — Dummy constructor, not initializing any members.
- L249 _public function_ `FLightRayIntersection( bool bInIntersects, const FMinimalStaticLightingVertex& InIntersectionVertex, const FStaticLightingMesh* InMesh, const FStaticLightingMapping* InMapping, int32 InElementIndex) : bIntersects(bInIntersects), IntersectionVertex(InIntersectionVertex), Mesh(InMesh), Mapping(InMapping), ElementIndex(InElementIndex)` — Initialization constructor.
- L266 _public function_ `static FLightRayIntersection None()` — No intersection constructor.

#### class `Lightmass::FMaterialElement`  
`class FMaterialElement : public FMaterialElementData`  
_L270-300_
- inherits: `FMaterialElementData`
- desc: Stores information about an element of the mesh which can have its own material.
- L274 _public member_ `bool bTranslucent;` — Whether Material has transmission, cached here to avoid dereferencing Material.
- L276 _public member_ `bool bIsMasked;` — Whether Material is Masked, cached here to avoid dereferencing Material.
- L282 _public member_ `bool bIsTwoSided;` — Whether Material is TwoSided, cached here to avoid dereferencing Material. This is different from FMaterialElementData::bUseTwoSidedLighting, because a two sided material may still want to use one sided lighting for the most part. It just indicates whether backfaces will be visible, and therefore artifacts on backfaces should be avoided.
- L284 _public member_ `bool bIsThinSurface;` — Whether Material is a thin surface or not.
- L286 _public member_ `bool bCastShadowAsMasked;` — Whether Material wants to cast shadows as masked, cached here to avoid dereferencing Material.
- L287 _public member_ `bool bSurfaceDomain;`
- L289 _public member_ `FMaterial* Material;` — The material associated with this element.  After import, Material is always valid (non-null and points to an FMaterial).
- L291 _public function_ `FMaterialElement() : bTranslucent(false), bIsMasked(false), bIsTwoSided(false), bIsThinSurface(false), bCastShadowAsMasked(false), bSurfaceDomain(true), Material(NULL)`

#### class `Lightmass::FStaticLightingMesh`  
`class FStaticLightingMesh : public virtual FRefCountedObject, public FStaticLightingMeshInstanceData`  
_L303-579_
- inherits: `FRefCountedObject,FStaticLightingMeshInstanceData`
- desc: A mesh which is used for computing static lighting.
- L307 _public member_ `TArray<FLight*> RelevantLights;` — The lights which affect the mesh's primitive.
- L314 _public member_ `TArray<int32> VisibilityIds;` — Visibility Id's corresponding to this static lighting mesh. Has to be an array because BSP exports FStaticLightingMesh's per combined group of surfaces that should be lit together, Instead of per-component geometry that should be visibility culled together.
- L319 _protected member_ `bool bColorInvalidTexels;` — Whether to color texels whose lightmap UV's are invalid.
- L322 _protected member_ `bool bUseDebugMaterial;` — Indicates whether DebugDiffuse should override the materials associated with this mesh.
- L323 _protected member_ `FLinearColor DebugDiffuse;`
- L329 _protected member_ `TArray<FMaterialElement, TInlineAllocator<5>> MaterialElements;` — Materials used by the mesh, guaranteed to contain at least one. These are indexed by the primitive type specific ElementIndex.
- L335 _protected member_ `static TMap<FStaticLightingMesh*, int32> MeshToIndexMap;` — Map from FStaticLightingMesh to the index given to uniquely identify all instances of the same primitive component. This is used to give all LOD's of the same primitive component the same mesh index.
- L339 _public function_ `virtual FStaticMeshStaticLightingMesh* GetInstanceableStaticMesh()`
- L341 _public function_ `virtual const FStaticMeshStaticLightingMesh* GetInstanceableStaticMesh() const`
- L344 _public function_ `virtual ~FStaticLightingMesh()` — Virtual destructor.
- L347 _public function_ `inline bool IsTranslucent(int32 ElementIndex) const` — Returns whether the given element index is translucent.
- L349 _public function_ `inline bool IsMasked(int32 ElementIndex) const` — Returns whether the given element index is masked.
- L351 _public function_ `inline bool UsesTwoSidedLighting(int32 ElementIndex) const` — Whether samples using the given element accept lighting from both sides of the triangle.
- L353 _public function_ `inline bool IsTwoSided(int32 ElementIndex) const` — Whether samples using the given element are going to have backfaces visible, and therefore artifacts on backfaces should be avoided.
- L354 _public function_ `inline bool IsThinSurface(int32 ElementIndex) const`
- L355 _public function_ `inline bool IsCastingShadowsAsMasked(int32 ElementIndex) const`
- L356 _public function_ `inline bool IsSurfaceDomain(int32 ElementIndex) const`
- L357 _public function_ `inline bool IsCastingShadowAsTwoSided() const`
- L358 _public function_ `inline bool IsEmissive(int32 ElementIndex) const`
- L359 _public function_ `inline bool IsIndirectlyShadowedOnly(int32 ElementIndex) const`
- L360 _public function_ `inline float GetFullyOccludedSamplesFraction(int32 ElementIndex) const`
- L361 _public function_ `inline int32 GetNumElements() const`
- L362 _public function_ `inline bool ShouldColorInvalidTexels() const`
- L363 _public function_ `inline bool HasImportedNormal(int32 ElementIndex) const`
- L364 _public function_ `inline bool UseVertexNormalForHemisphereGather(int32 ElementIndex) const`
- L371 _public function_ `virtual FGuid GetObjectGuid() const` — Returns the Guid for the object associated with this lighting mesh. Ie, for a StaticMeshStaticLightingMesh, it would return the Guid of the source static mesh. The GetObjectType function should also be used to determine the TypeId of the source object.
- L376 _public function_ `virtual ESourceObjectType GetObjectType() const` — Returns the SourceObject type id.
- L386 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const = 0;` — Accesses a triangle for visibility testing. @param TriangleIndex - The triangle to access, valid range is [0, NumTriangles). @param OutV0 - Upon return, should contain the first vertex of the triangle. @param OutV1 - Upon return, should contain the second vertex of the triangle. @param OutV2 - Upon return, should contain the third vertex of the triangle. @param ElementIndex - Indicates the element index of the triangle.
- L396 _public function_ `virtual void GetShadingTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const` — Accesses a triangle for shading. @param TriangleIndex - The triangle to access, valid range is [0, NumShadingTriangles). @param OutV0 - Upon return, should contain the first vertex of the triangle. @param OutV1 - Upon return, should contain the second vertex of the triangle. @param OutV2 - Upon return, should contain the third vertex of the triangle. @param ElementIndex - Indicates the element index of the triangle.
- L410 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const = 0;` — Accesses a triangle's vertex indices for visibility testing. @param TriangleIndex - The triangle to access, valid range is [0, NumTriangles). @param OutI0 - Upon return, should contain the first vertex index of the triangle. @param OutI1 - Upon return, should contain the second vertex index of the triangle. @param OutI2 - Upon return, should contain the third vertex index of the triangle.
- L419 _public function_ `virtual void GetShadingTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const` — Accesses a triangle's vertex indices for shading. @param TriangleIndex - The triangle to access, valid range is [0, NumShadingTriangles). @param OutI0 - Upon return, should contain the first vertex index of the triangle. @param OutI1 - Upon return, should contain the second vertex index of the triangle. @param OutI2 - Upon return, should contain the third vertex index of the triangle.
- L426 _public function_ `virtual bool IsElementCastingShadow(int32 ElementIndex) const`
- L430 _public function_ `virtual uint32 GetLODIndices() const` — Returns the LOD of this instance.
- L431 _public function_ `virtual uint32 GetHLODRange() const`
- L432 _public prototype_ `bool DoesMeshBelongToLOD0() const;`
- L435 _public prototype_ `virtual void SetDebugMaterial(bool bUseDebugMaterial, FLinearColor Diffuse);` — For debugging
- L441 _public function_ `virtual bool IsAlwaysOpaqueForVisibility() const` — Whether mesh is always opaque for visibility calculations, otherwise opaque property will be checked for each triangle
- L444 _public prototype_ `FLinearColor EvaluateBRDF( const FStaticLightingVertex& Vertex, int32 ElementIndex, const FVector4f& IncomingDirection, const FVector4f& OutgoingDirection) const;` — Evaluates the mesh's Bidirectional Reflectance Distribution Function.
- L451 _public prototype_ `FLinearColor SampleBRDF( const FStaticLightingVertex& Vertex, int32 ElementIndex, const FVector4f& IncomingDirection, FVector4f& OutgoingDirection, float& DirectionPDF, FLMRandomStream& RandomStream ) const;` — Generates an outgoing direction sample and evaluates the BRDF for that direction.
- L461 _public function_ `inline FLinearColor EvaluateEmissive(const FVector2f& UVs, int32 ElementIndex) const` — Evaluates the mesh's emissive at the given UVs
- L479 _public function_ `inline FLinearColor EvaluateDiffuse(const FVector2f& UVs, int32 ElementIndex) const` — Evaluates the mesh's diffuse at the given UVs
- L504 _public function_ `inline FLinearColor EvaluateTransmission(const FVector2f& UVs, int32 ElementIndex) const` — Evaluates the mesh's transmission at the given UVs
- L515 _public function_ `inline bool EvaluateMaskedCollision(const FVector2f& UVs, int32 ElementIndex) const` — Evaluates the mesh's transmission at the given UVs
- L525 _public function_ `inline FVector4f EvaluateNormal(const FVector2f& UVs, int32 ElementIndex) const` — Evaluates the mesh's tangent space normal at the given UVs
- L541 _public function_ `inline FLinearColor EvaluateTotalReflectance(const FMinimalStaticLightingVertex& Vertex, int32 ElementIndex) const` — Returns the hemispherical-hemispherical reflectance, Which is the fraction of light that is reflected in any direction when the incident light is constant over all directions of the hemisphere. This value is used to calculate exitant radiance, which is 1 / PI * HemisphericalHemisphericalReflectance * Irradiance, disregarding directional variation.
- L546 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L549 _public prototype_ `void CreateMeshAreaLights(const class FStaticLightingSystem& LightingSystem, const FScene& Scene, TIndirectArray<FMeshAreaLight>& MeshAreaLights) const;` — Allows the mesh to create mesh area lights from its emissive contribution
- L554 _private prototype_ `void CalculateUniqueLayers(const TArray<FStaticLightingVertex>& MeshVertices, const TArray<int32>& ElementIndices, TArray<TArray<int32> >& LayeredGroupTriangles) const;` — Splits a mesh into layers with non-overlapping UVs, maintaining adjacency in world space and UVs.
- L557 _private prototype_ `void AddLightTexel( const class FTexelToCornersMap& TexelToCornersMap, int32 ElementIndex, TArray<int32>& LightIndices, int32 X, int32 Y, float EmissiveThreshold, TArray<FIntPoint>& Texels, int32 TexSizeX, int32 TexSizeY) const;` — Adds an entry to Texels if the given texel passes the emissive criteria.
- L568 _private prototype_ `void AddPrimitiveTexel( const FTexelToCornersMap& TexelToCornersMap, const struct FTexelToCorners& ComparisonTexel, int32 ComparisonTexelLightIndex, const FVector4f& PrimitiveOrigin, TArray<int32>& PrimitiveIndices, const TArray<int32>& LightIndices, int32 X, int32 Y, TArray<FIntPoint>& Texels, const FScene& Scene, float DistanceThreshold) const;` — Adds an entry to Texels if the given texel passes the primitive simplifying criteria.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Lightmass`
- L86 _function_ `friend FStaticLightingVertex operator+(const FStaticLightingVertex& A,const FStaticLightingVertex& B)` (scope `Lightmass`) — Operators used for linear combinations of static lighting vertices.
- L100 _function_ `friend FStaticLightingVertex operator-(const FStaticLightingVertex& A,const FStaticLightingVertex& B)` (scope `Lightmass`)
- L114 _function_ `friend FStaticLightingVertex operator*(const FStaticLightingVertex& A,float B)` (scope `Lightmass`)
- L128 _function_ `friend FStaticLightingVertex operator/(const FStaticLightingVertex& A,float B)` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/Lighting/LightingSystem.h` (Private)


#### class `Lightmass::FGatheredLightMapData2D`  
`class FGatheredLightMapData2D`  
_L38-83_
- desc: The raw data which is used to construct a 2D light-map.
- L43 _public member_ `uint32 SizeX;` — The width of the light-map.
- L45 _public member_ `uint32 SizeY;` — The height of the light-map.
- L48 _public member_ `TArray<const FLight*> Lights;` — The lights which this light-map stores.
- L50 _public member_ `bool bHasSkyShadowing;`
- L52 _public function_ `FGatheredLightMapData2D(uint32 InSizeX, uint32 InSizeY) : SizeX(InSizeX), SizeY(InSizeY), bHasSkyShadowing(false)`
- L62 _public function_ `const FGatheredLightMapSample& operator()(uint32 X,uint32 Y) const` — Accessors.
- L63 _public function_ `FGatheredLightMapSample& operator()(uint32 X,uint32 Y)`
- L64 _public function_ `uint32 GetSizeX() const`
- L65 _public function_ `uint32 GetSizeY() const`
- L67 _public function_ `void Empty()`
- L74 _public function_ `void AddLight(const FLight* NewLight)`
- L79 _public prototype_ `FLightMapData2D* ConvertToLightmap2D(bool bDebugThisMapping, int32 PaddedDebugX, int32 PaddedDebugY) const;`
- L82 _private member_ `TArray<FGatheredLightMapSample> Data;`

#### struct `Lightmass::FFinalGatherInfo`  
`struct FFinalGatherInfo`  
_L85-94_
- L87 _public function_ `FFinalGatherInfo() : NumBackfaceHits(0), NumSamplesOccluded(0)`
- L92 _public member_ `int32 NumBackfaceHits;`
- L93 _public member_ `float NumSamplesOccluded;`

#### struct `Lightmass::FTexelCorner`  
`struct FTexelCorner`  
_L96-99_
- L98 _public member_ `FVector4f WorldPosition;`

#### struct `Lightmass::FTexelToCorners`  
`struct FTexelToCorners`  
_L102-112_
- desc: Information about a texel's corners
- L105 _public member_ `FTexelCorner Corners[NumTexelCorners];` — The position of each corner
- L107 _public member_ `FVector4f WorldTangentX;` — The tangent basis of the last valid corner to be rasterized
- L108 _public member_ `FVector4f WorldTangentY;`
- L109 _public member_ `FVector4f WorldTangentZ;`
- L111 _public member_ `bool bValid[NumTexelCorners];` — Whether each corner lies on the mesh

#### class `Lightmass::FTexelToCornersMap`  
`class FTexelToCornersMap`  
_L115-154_
- desc: Map from texel to the corners of that texel.
- L120 _public function_ `FTexelToCornersMap(int32 InSizeX,int32 InSizeY): SizeX(InSizeX), SizeY(InSizeY)` — Initialization constructor.
- L129 _public function_ `FTexelToCorners& operator()(int32 X,int32 Y)` — Accessors.
- L134 _public function_ `const FTexelToCorners& operator()(int32 X,int32 Y) const`
- L140 _public function_ `int32 GetSizeX() const`
- L141 _public function_ `int32 GetSizeY() const`
- L142 _public function_ `void Empty()`
- L147 _private member_ `TArray<FTexelToCorners> Data;` — The mapping data.
- L150 _private member_ `int32 SizeX;` — The width of the mapping data.
- L153 _private member_ `int32 SizeY;` — The height of the mapping data.

#### class `Lightmass::FPhoton`  
`class FPhoton`  
_L157-213_
- desc: A particle representing the distribution of a light's radiant power.
- L162 _private member_ `FVector4f PositionAndId;` — Position that the photon was deposited at in XYZ, and Id in W for debugging.
- L165 _private member_ `FVector4f IncidentDirectionAndDistance;` — Direction the photon came from in XYZ, and distance that the photon traveled along its last path before being deposited in W.
- L168 _private member_ `FVector4f SurfaceNormalAndPower;` — Normal of the surface the photon was deposited on in XYZ, and fraction of the originating light's power that this photon represents in W.
- L172 _public function_ `FPhoton(int32 InId, const FVector4f& InPosition, float InDistance, const FVector4f& InIncidentDirection, const FVector4f& InSurfaceNormal, const FLinearColor& InPower)`
- L181 _public function_ `FORCEINLINE int32 GetId() const`
- L186 _public function_ `FORCEINLINE FVector4f GetPosition() const`
- L191 _public function_ `FORCEINLINE FVector4f GetIncidentDirection() const`
- L196 _public function_ `FORCEINLINE float GetDistance() const`
- L201 _public function_ `FORCEINLINE FVector4f GetSurfaceNormal() const`
- L206 _public function_ `FORCEINLINE FLinearColor GetPower() const`

#### struct `Lightmass::FPhotonElement`  
`struct FPhotonElement`  
_L216-225_
- desc: An octree element that contains a photon
- L219 _public member_ `const FPhoton Photon;` — Stores a photon by value so we can discard the original array and avoid a level of indirection
- L222 _public function_ `FPhotonElement(const FPhoton& InPhoton) : Photon(InPhoton)` — Initialization constructor.

#### struct `Lightmass::FPhotonMapOctreeSemantics`  
`struct FPhotonMapOctreeSemantics`  
_L230-244_
- desc: Octree semantic definitions.
- L238 _public typedef_ `typedef FDefaultAllocator ElementAllocator;` — Using the default heap allocator instead of an inline allocator to reduce memory usage
- L240 _public function_ `static FBoxCenterAndExtent GetBoundingBox(const FPhotonElement& PhotonElement)`

#### enum `Lightmass::FPhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L233-233_
- desc: @todo - evaluate different performance/memory tradeoffs with these

#### enum `Lightmass::FPhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L234-234_

#### enum `Lightmass::FPhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L235-235_

#### struct `Lightmass::FPhotonSegmentElement`  
`struct FPhotonSegmentElement`  
_L246-277_
- L248 _public member_ `const FPhoton* Photon;`
- L250 _public member_ `FVector3f SegmentCenter;`
- L251 _public member_ `FVector3f SegmentExtent;`
- L254 _public function_ `FPhotonSegmentElement(const FPhoton* InPhoton, float InStartOffset, float InSegmentLength) : Photon(InPhoton)` — Initialization constructor.
- L270 _public function_ `inline float ComputeSquaredDistanceToPoint(FVector3f InPoint) const`

#### struct `Lightmass::FPhotonSegmentMapOctreeSemantics`  
`struct FPhotonSegmentMapOctreeSemantics`  
_L280-293_
- desc: Octree semantic definitions.
- L287 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;`
- L289 _public function_ `static FBoxCenterAndExtent GetBoundingBox(const FPhotonSegmentElement& PhotonSegmentElement)`

#### enum `Lightmass::FPhotonSegmentMapOctreeSemantics::(anonymous)`  
`enum`  
_L283-283_
- desc: @todo - evaluate different performance/memory tradeoffs with these

#### enum `Lightmass::FPhotonSegmentMapOctreeSemantics::(anonymous)`  
`enum`  
_L284-284_

#### enum `Lightmass::FPhotonSegmentMapOctreeSemantics::(anonymous)`  
`enum`  
_L285-285_

#### class `Lightmass::FIrradiancePhoton`  
`class FIrradiancePhoton : public FIrradiancePhotonData`  
_L298-352_
- inherits: `FIrradiancePhotonData`
- desc: A photon which stores a precalculated irradiance estimate.
- L302 _public function_ `FIrradiancePhoton(const FVector4f& InPosition, const FVector4f& InSurfaceNormal, bool bInHasContributionFromDirectPhotons)`
- L308 _public function_ `FORCEINLINE bool HasDirectContribution() const`
- L313 _public function_ `FORCEINLINE void SetHasDirectContribution()`
- L318 _public function_ `FORCEINLINE void SetUsed()`
- L323 _public function_ `FORCEINLINE bool IsUsed() const`
- L328 _public function_ `FORCEINLINE void SetIrradiance(FLinearColor InIrradiance)`
- L335 _public function_ `FORCEINLINE FLinearColor GetIrradiance() const`
- L343 _public function_ `FORCEINLINE FVector4f GetPosition() const`
- L348 _public function_ `FORCEINLINE FVector4f GetSurfaceNormal() const`

#### struct `Lightmass::FIrradiancePhotonElement`  
`struct FIrradiancePhotonElement`  
_L355-370_
- desc: An octree element that contains an irradiance photon
- L359 _public function_ `FIrradiancePhotonElement(const int32 InPhotonIndex, TArray<FIrradiancePhoton>& InPhotonArray) : PhotonIndex(InPhotonIndex), PhotonArray(InPhotonArray)` — Initialization constructor.
- L364 _public function_ `FIrradiancePhoton& GetPhoton()`
- L365 _public function_ `const FIrradiancePhoton& GetPhoton() const`
- L368 _private member_ `int32 PhotonIndex;`
- L369 _private member_ `TArray<FIrradiancePhoton>& PhotonArray;`

#### struct `Lightmass::FIrradiancePhotonMapOctreeSemantics`  
`struct FIrradiancePhotonMapOctreeSemantics`  
_L375-388_
- desc: Octree semantic definitions.
- L382 _public typedef_ `typedef FDefaultAllocator ElementAllocator;`
- L384 _public function_ `static FBoxCenterAndExtent GetBoundingBox(const FIrradiancePhotonElement& PhotonElement)`

#### enum `Lightmass::FIrradiancePhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L378-378_
- desc: @todo - evaluate different performance/memory tradeoffs with these

#### enum `Lightmass::FIrradiancePhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L379-379_

#### enum `Lightmass::FIrradiancePhotonMapOctreeSemantics::(anonymous)`  
`enum`  
_L380-380_

#### class `Lightmass::FVolumeLightingSample`  
`class FVolumeLightingSample : public FVolumeLightingSampleData`  
_L391-420_
- inherits: `FVolumeLightingSampleData`
- desc: A lighting sample in world space storing incident radiance from a whole sphere of directions.
- L394 _public function_ `FVolumeLightingSample(const FVector4f& InPositionAndRadius)`
- L407 _public function_ `inline FVector4f GetPosition() const`
- L411 _public function_ `inline float GetRadius() const`
- L416 _public prototype_ `void SetFromSHVector(const FSHVectorRGB3& SHVector);`
- L419 _public prototype_ `void ToSHVector(FSHVectorRGB3& SHVector) const;` — Constructs an SH environment from this lighting sample.

#### struct `Lightmass::FVolumeSampleInterpolationElement`  
`struct FVolumeSampleInterpolationElement`  
_L422-432_
- L424 _public member_ `const int32 SampleIndex;`
- L425 _public member_ `const TArray<FVolumeLightingSample>& VolumeSamples;`
- L428 _public function_ `FVolumeSampleInterpolationElement(const int32 InSampleIndex, const TArray<FVolumeLightingSample>& InVolumeSamples) : SampleIndex(InSampleIndex), VolumeSamples(InVolumeSamples)` — Initialization constructor.

#### struct `Lightmass::FVolumeLightingInterpolationOctreeSemantics`  
`struct FVolumeLightingInterpolationOctreeSemantics`  
_L437-451_
- desc: Octree semantic definitions.
- L444 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;`
- L446 _public function_ `static FBoxCenterAndExtent GetBoundingBox(const FVolumeSampleInterpolationElement& Element)`

#### enum `Lightmass::FVolumeLightingInterpolationOctreeSemantics::(anonymous)`  
`enum`  
_L440-440_
- desc: @todo - evaluate different performance/memory tradeoffs with these

#### enum `Lightmass::FVolumeLightingInterpolationOctreeSemantics::(anonymous)`  
`enum`  
_L441-441_

#### enum `Lightmass::FVolumeLightingInterpolationOctreeSemantics::(anonymous)`  
`enum`  
_L442-442_

#### class `Lightmass::FPrecomputedVisibilityCell`  
`class FPrecomputedVisibilityCell`  
_L453-458_
- L456 _public member_ `FBox3f Bounds;`
- L457 _public member_ `TArray<uint8> VisibilityData;`

#### class `Lightmass::FStaticShadowDepthMapSample`  
`class FStaticShadowDepthMapSample : public FStaticShadowDepthMapSampleData`  
_L461-468_
- inherits: `FStaticShadowDepthMapSampleData`
- desc: Stores depth for a single cell of a shadow map for a stationary light.
- L464 _public function_ `FStaticShadowDepthMapSample(FFloat16 InDistance)`

#### class `Lightmass::FStaticShadowDepthMap`  
`class FStaticShadowDepthMap : public FStaticShadowDepthMapData`  
_L471-475_
- inherits: `FStaticShadowDepthMapData`
- desc: Stores information about how ShadowMap was generated.
- L474 _public member_ `TArray<FStaticShadowDepthMapSample> ShadowMap;`

#### class `Lightmass::FStaticLightingMappingStats`  
`class FStaticLightingMappingStats`  
_L483-834_
- desc: Stats for a single mapping.  All times are thread seconds if the stat was calculated during a multi threaded mapping process.
- L488 _public member_ `float TotalTextureMappingLightingThreadTime;` — Part of TotalLightingThreadTime that was spent on texture mappings.
- L491 _public member_ `float TotalVolumeSampleLightingThreadTime;` — Part of TotalLightingThreadTime that was spent on volume samples.
- L494 _public member_ `float TotalVolumetricLightmapLightingThreadTime;` — Part of TotalLightingThreadTime that was spent on volumetric lightmap work.
- L497 _public member_ `float TexelRasterizationTime;` — Time taken to generate the FTexelToVertexMap
- L500 _public member_ `float VertexSampleCreationTime;` — Time taken to create vertex samples.
- L503 _public member_ `int32 NumMappedTexels;` — Number of texels mapped to geometry in the scene.
- L506 _public member_ `int32 NumVertexSamples;` — Number of vertex light samples calculated.
- L509 _public member_ `float DirectLightingTime;` — Time taken to calculate direct lighting
- L512 _public member_ `float AreaShadowsThreadTime;` — Thread seconds spent calculating area shadows.
- L515 _public member_ `float AreaLightingThreadTime;` — Thread seconds spent calculating light attenuation and influence.
- L518 _public member_ `float AccumulatedSignedDistanceFieldUpsampleFactors;` — Accumulated signed distance field upsample factors for all mappings that used signed distance field shadows.
- L521 _public member_ `int32 NumSignedDistanceFieldCalculations;` — Number of mappings that used signed distance field shadows.
- L524 _public member_ `uint64 NumSignedDistanceFieldAdaptiveSourceRaysFirstPass;` — Number of rays traced during the sparse source data generation pass.
- L527 _public member_ `uint64 NumSignedDistanceFieldAdaptiveSourceRaysSecondPass;` — Number of rays traced during the refining source data generation pass.
- L530 _public member_ `float SignedDistanceFieldSourceFirstPassThreadTime;` — Thread seconds spend processing the sparse source data generation pass.
- L533 _public member_ `float SignedDistanceFieldSourceSecondPassThreadTime;` — Thread seconds spend processing the refining source data generation pass.
- L536 _public member_ `uint64 NumSignedDistanceFieldScatters;` — Number of transition distance scatters during the distance field search pass.
- L539 _public member_ `float SignedDistanceFieldSearchThreadTime;` — Thread seconds spent searching the source data for the closest transition distance.
- L542 _public member_ `uint64 NumPrecomputedVisibilityQueries;` — Number of cell - mesh queries processed.
- L545 _public member_ `uint64 NumQueriesVisibleByDistanceRatio;` — Number of cell - mesh queries considered visible because the mesh was very close to the cell.
- L548 _public member_ `uint64 NumQueriesVisibleExplicitSampling;` — Number of cell - mesh queries determined visible from explicitly sampling the mesh's bounds.
- L551 _public member_ `uint64 NumQueriesVisibleImportanceSampling;` — Number of cell - mesh queries determined visible from importance sampling.
- L554 _public member_ `uint64 NumPrecomputedVisibilityRayTraces;` — Number of rays traced for precomputed visibility.
- L557 _public member_ `int32 NumPrecomputedVisibilityCellsProcessed;` — Number of visibility cells processed on this agent.
- L560 _public member_ `float PrecomputedVisibilityThreadTime;` — Thread seconds processing visibility cells.
- L563 _public member_ `float PrecomputedVisibilitySampleSetupThreadTime;` — Thread seconds generating visibility sample positions.
- L566 _public member_ `float PrecomputedVisibilityRayTraceThreadTime;` — Thread seconds tracing visibility rays.
- L569 _public member_ `float PrecomputedVisibilityImportanceSampleThreadTime;` — Thread seconds importance sampling visibility queries.
- L572 _public member_ `uint64 NumPrecomputedVisibilityGroupQueries;` — Number of visibility queries on groups.
- L575 _public member_ `uint64 NumPrecomputedVisibilityMeshQueriesSkipped;` — Number of mesh queries that were trivially occluded because their group was already determined to be occluded.
- L578 _public member_ `float StaticShadowDepthMapThreadTime;` — Thread seconds calculating static shadow depth maps.
- L581 _public member_ `float MaxStaticShadowDepthMapThreadTime;` — Longest time spent on a single static shadow depth map.
- L584 _public member_ `float VolumeDistanceFieldThreadTime;` — Thread seconds calculating the volume distance field.
- L587 _public member_ `float BlockOnIndirectLightingCacheTasksTime;` — Amount of time the mapping processing threads spent either processing indirect lighting cache tasks, or waiting on another thread to finish its cache task.
- L590 _public member_ `float BlockOnIndirectLightingInterpolateTasksTime;` — Amount of time the mapping processing threads spent either processing indirect lighting interpolate tasks, or waiting on another thread to finish its interpolate task.
- L593 _public member_ `float IndirectLightingCacheTaskThreadTime;` — Time taken to calculate indirect lighting
- L595 _public member_ `float IndirectLightingCacheTaskThreadTimeSeparateTask;`
- L598 _public member_ `float ImportancePhotonGatherTime;` — Time taken to gather photons which are used for importance sampling the final gather
- L601 _public member_ `uint64 TotalFoundImportancePhotons;` — Number of importance photons found
- L604 _public member_ `float CalculateImportanceSampleTime;` — Time taken to generate a sample direction based on the importance photons, and then calculate the PDF for the generated sample direction.
- L607 _public member_ `uint64 NumImportancePDFCalculations;` — Number of elements contributing to the PDF times the number of samples
- L610 _public member_ `float CalculateExitantRadianceTime;` — Time taken to calculate the exitant radiance at the end of each final gather ray
- L613 _public member_ `uint64 NumFirstBounceRaysTraced;` — Number of final gather rays
- L616 _public member_ `float FirstBounceRayTraceTime;` — Time taken to trace final gather rays
- L619 _public member_ `uint64 NumDirectLightingShadowRays;` — Number of shadow rays traced for direct lighting.
- L622 _public member_ `uint64 NumIrradiancePhotonMapSearches;` — Number of times the nearest irradiance photon was searched for
- L625 _public member_ `int32 NumFoundIrradiancePhotons;` — Number of unique irradiance photons cached on surfaces.
- L628 _public member_ `uint64 NumCachedIrradianceSamples;` — Number of nearest irradiance photon samples that were cached on surfaces
- L631 _public member_ `float SecondPassIrradianceCacheInterpolationTime;` — Time taken for irradiance cache interpolation for the final shading pass
- L633 _public member_ `float SecondPassIrradianceCacheInterpolationTimeSeparateTask;`
- L636 _public member_ `uint64 NumIrradiancePhotonSearchRays;` — Number of rays traced to determine visibility of irradiance photons while caching them on surfaces
- L639 _public member_ `float IrradiancePhotonCachingThreadTime;` — Time spent caching irradiance photons on surfaces
- L641 _public member_ `float RadiositySetupThreadTime;`
- L642 _public member_ `float RadiosityIterationThreadTime;`
- L645 _public member_ `float IrradiancePhotonOctreeTraversalTime;` — Time taken traversing the irradiance photon octree
- L648 _public member_ `float IrradiancePhotonSearchRayTime;` — Time taken to trace rays determining the visibility of irradiance photons
- L651 _public member_ `uint64 NumBaseFinalGatherSamples;` — The number of final gather samples done at the base resolution.
- L654 _public member_ `uint64 NumRefiningFinalGatherSamples[MaxNumRefiningDepths];` — The number of final gather samples done at each refinement depth.
- L657 _public member_ `uint64 NumRefiningSamplesDueToBrightness;` — The number of final gather samples done due to brightness differences between neighbors.
- L660 _public member_ `uint64 NumRefiningSamplesDueToImportancePhotons;` — The number of final gather samples done due to intersecting importance photons.
- L662 _public member_ `uint64 NumRefiningSamplesOther;`
- L665 _public member_ `float BaseFinalGatherSampleTime;` — Amount of time spent computing base final gather samples.
- L668 _public member_ `float RefiningFinalGatherSampleTime;` — Amount of time spent computing refining final gather samples.
- L670 _public member_ `int32 NumVolumetricLightmapSamples;`
- L672 _public member_ `float VolumetricLightmapVoxelizationTime;`
- L674 _public member_ `float VolumetricLightmapGatherImportancePhotonsTime;`
- L676 _public member_ `float VolumetricLightmapDirectLightingTime;`
- L678 _public member_ `float VolumetricLightmapFinalGatherTime;`
- L680 _public function_ `FStaticLightingMappingStats() : TotalTextureMappingLightingThreadTime(0), TotalVolumeSampleLightingThreadTime(0), TotalVolumetricLightmapLightingThreadTime(0), TexelRasterizationTime(0), VertexSampleCreationTime(0), NumMappedTexels(0), NumVertexSamples(0), DirectLightingTime(0), AreaShadowsThreadTime(0), AreaLightingThreadTime(0), AccumulatedSignedDistanceFieldUpsampleFactors(0), NumSignedDistanceFieldCalculations(0), NumSignedDistanceFieldAdaptiveSourceRaysFirstPass(0), NumSignedDistanceFieldAdaptiveSourceRaysSecondPass(0), SignedDistanceFieldSourceFirstPassThreadTime(0), SignedDistanceFieldSourceSecondPassThreadTime(0), NumSignedDistanceFieldScatters(0), SignedDistanceFieldSearchThreadTime(0), NumPrecomputedVisibilityQueries(0), NumQueriesVisibleByDistanceRatio(0), NumQueriesVisibleExplicitSampling(0), NumQueriesVisibleImportanceSampling(0), NumPrecomputedVisibilityRayTraces(0), NumPrecomputedVisibilityCellsProcessed(0), PrecomputedVisibilityThreadTime(0), PrecomputedVisibilitySampleSetupThreadTime(0), PrecomputedVisibilityRayTraceThreadTime(0), PrecomputedVisibilityImportanceSampleThreadTime(0), NumPrecomputedVisibilityGroupQueries(0), NumPrecomputedVisibilityMeshQueriesSkipped(0), StaticShadowDepthMapThreadTime(0), MaxStaticShadowDepthMapThreadTime(0), VolumeDistanceFieldThreadTime(0), BlockOnIndirectLightingCacheTasksTime(0), BlockOnIndirectLightingInterpolateTasksTime(0), IndirectLightingCacheTaskThreadTime(0), IndirectLightingCacheTaskThreadTimeSeparateTask(0), Importa ...`
- L755 _public function_ `FStaticLightingMappingStats& operator+=(const FStaticLightingMappingStats& B)`

#### struct `Lightmass::FFindNearbyPhotonStats`  
`struct FFindNearbyPhotonStats`  
_L837-891_
- desc: Stats collected by FLightingSystem::FindNearbyPhotons*()
- L840 _public member_ `uint64 NumIterativePhotonMapSearches;` — Number of photon map searches using the iterative search process.
- L843 _public member_ `uint64 NumSearchIterations;` — Number of size-increasing photon map search iterations until enough photons were found.
- L846 _public member_ `float PushingOctreeChildrenThreadTime;` — Thread seconds spent traversing the photon map octree and pushing child nodes onto the traversal stack.
- L849 _public member_ `float ProcessingOctreeElementsThreadTime;` — Thread seconds spent processing photons found in the photon map.
- L852 _public member_ `float FindingFurthestPhotonThreadTime;` — Thread seconds spent finding the furthest found photon in order to replace it with the incoming one.
- L855 _public member_ `uint64 NumOctreeNodesTested;` — Number of octree nodes tested during all photon map searches.
- L858 _public member_ `uint64 NumOctreeNodesVisited;` — Number of octree nodes that passed testing and had their elements processed during all photon map searches.
- L861 _public member_ `uint64 NumElementsTested;` — Number of elements tested during all photon map searches.
- L864 _public member_ `uint64 NumElementsAccepted;` — Number of elements that passed testing during all photon map searches.
- L866 _public function_ `FFindNearbyPhotonStats() : NumIterativePhotonMapSearches(0), NumSearchIterations(0), PushingOctreeChildrenThreadTime(0), ProcessingOctreeElementsThreadTime(0), FindingFurthestPhotonThreadTime(0), NumOctreeNodesTested(0), NumOctreeNodesVisited(0), NumElementsTested(0), NumElementsAccepted(0)`
- L878 _public function_ `FFindNearbyPhotonStats& operator+=(const FFindNearbyPhotonStats& B)`

#### struct `Lightmass::FCalculateIrradiancePhotonStats`  
`struct FCalculateIrradiancePhotonStats : public FFindNearbyPhotonStats`  
_L894-910_
- inherits: `FFindNearbyPhotonStats`
- desc: Stats collected by FStaticLightingSystem::CalculateIrradiancePhotonsThreadLoop()
- L897 _public member_ `float CalculateIrradianceThreadTime;` — Thread seconds spent calculating irradiance once the relevant photons have been found.
- L899 _public function_ `FCalculateIrradiancePhotonStats() : FFindNearbyPhotonStats(), CalculateIrradianceThreadTime(0)`
- L904 _public function_ `FCalculateIrradiancePhotonStats& operator+=(const FCalculateIrradiancePhotonStats& B)`

#### class `Lightmass::FStaticLightingStats`  
`class FStaticLightingStats : public FStaticLightingMappingStats`  
_L913-1141_
- inherits: `FStaticLightingMappingStats`
- desc: Stats for the whole lighting system, which belong to the main thread.  Other threads must use synchronization to access them.
- L918 _public member_ `float SceneSetupTime;` — Main thread seconds setting up the scene
- L921 _public member_ `float MeshAreaLightSetupTime;` — Main thread seconds setting up mesh area lights
- L924 _public member_ `float TotalLightingThreadTime;` — Thread seconds spent processing mappings for the final lighting pass
- L927 _public member_ `float MainThreadLightingTime;` — Main thread seconds until the final lighting pass was complete
- L930 _public member_ `int32 NumMappings;` — Number of mappings processed
- L933 _public member_ `int32 NumTexelsProcessed;` — Number of texels processed
- L936 _public member_ `int32 NumLights;` — Number of lights in the scene.
- L939 _public member_ `int32 NumMeshAreaLightMeshes;` — Number of meshes that created mesh area lights.
- L942 _public member_ `int32 NumMeshAreaLights;` — Number of mesh area lights created from emissive areas in the scene.
- L945 _public member_ `uint64 NumMeshAreaLightPrimitives;` — Number of mesh area light primitives before simplification.
- L948 _public member_ `uint64 NumSimplifiedMeshAreaLightPrimitives;` — Number of simplified mesh area light primitives that are used for lighting.
- L951 _public member_ `int32 NumDynamicObjectSurfaceSamples;` — Number of volume lighting samples created off of surfaces.
- L954 _public member_ `int32 NumDynamicObjectVolumeSamples;` — Number of volume lighting samples created based on the importance volume.
- L957 _public member_ `float PrecomputedVisibilitySetupTime;` — Single threaded time setup up sPVS structures for parallel task processing.
- L960 _public member_ `int32 NumPrecomputedVisibilityCellsTotal;` — Total number of cells which visibility will be computed for.
- L963 _public member_ `int32 NumPrecomputedVisibilityCellsCamaraTracks;` — Number of visibility cells generated on camera tracks.
- L966 _public member_ `int32 NumPrecomputedVisibilityMeshes;` — Number of meshes with valid visibility Ids in the scene.
- L969 _public member_ `int32 NumPrecomputedVisibilityMeshesExcludedFromGroups;` — Number of meshes excluded from visibility groups due to their size.
- L972 _public member_ `SIZE_T PrecomputedVisibilityDataBytes;` — Size of the raw visibility data exported.
- L975 _public member_ `float EmitDirectPhotonsTime;` — Main thread time emitting direct photons
- L978 _public member_ `float EmitDirectPhotonsThreadTime;` — Thread time emitting direct photons.
- L981 _public member_ `float DirectPhotonsTracingThreadTime;` — Thread time tracing rays for direct photons.
- L984 _public member_ `float DirectPhotonsLightSamplingThreadTime;` — Thread time generating light samples for direct photons.
- L987 _public member_ `float DirectCustomAttenuationThreadTime;` — Thread time spent applying non-physical attenuation to direct photons.
- L990 _public member_ `float ProcessDirectPhotonsThreadTime;` — Thread seconds spent processing gathered direct photons and adding them to spatial data structures.
- L993 _public member_ `int32 NumDirectPhotonsGathered;` — Number of direct photons that were deposited on surfaces.
- L996 _public member_ `float CachingIndirectPhotonPathsTime;` — Main thread time letting lights cache information about the indirect photon paths.
- L999 _public member_ `float EmitIndirectPhotonsTime;` — Main thread time emitting indirect photons
- L1002 _public member_ `float EmitIndirectPhotonsThreadTime;` — Thread time emitting indirect photons.
- L1005 _public member_ `float ProcessIndirectPhotonsThreadTime;` — Thread seconds spent processing gathered indirect photons and adding them to spatial data structures.
- L1008 _public member_ `float LightSamplingThreadTime;` — Thread time sampling lights while emitting indirect photons.
- L1011 _public member_ `float IndirectCustomAttenuationThreadTime;` — Thread time spent applying non-physical attenuation to indirect photons.
- L1014 _public member_ `float IntersectLightRayThreadTime;` — Thread time tracing indirect photons from a light.
- L1017 _public member_ `float PhotonBounceTracingThreadTime;` — Thread time tracing photons bouncing off of surfaces in the scene.
- L1020 _public member_ `int32 NumIndirectPhotonsGathered;` — Number of indirect photons that were deposited on surfaces.
- L1023 _public member_ `float IrradiancePhotonMarkingTime;` — Main thread time marking photons as having direct lighting influence or not.
- L1026 _public member_ `float IrradiancePhotonMarkingThreadTime;` — Thread time marking photons.
- L1029 _public member_ `float IrradiancePhotonCalculatingTime;` — Main thread time calculating irradiance photons
- L1032 _public member_ `float IrradiancePhotonCalculatingThreadTime;` — Thread time calculating irradiance photons
- L1035 _public member_ `float CacheIrradiancePhotonsTime;` — Main thread time caching irradiance photons on surfaces
- L1038 _public member_ `int32 NumIrradiancePhotons;` — Number of irradiance photons
- L1041 _public member_ `int32 NumDirectIrradiancePhotons;` — Number of irradiance photons created off of direct photons.
- L1044 _public member_ `volatile int32 NumPhotonGathers;` — Number of times a photon map was searched, excluding irradiance photon searches
- L1047 _public member_ `uint64 NumFirstPassPhotonsEmitted;` — Number of photons emitted in the first pass
- L1050 _public member_ `uint64 NumFirstPassPhotonsRequested;` — Number of photons requested to be emitted in the first pass
- L1053 _public member_ `uint64 NumSecondPassPhotonsEmitted;` — Number of photons emitted in the second pass
- L1056 _public member_ `uint64 NumSecondPassPhotonsRequested;` — Number of photons requested to be emitted in the second pass
- L1059 _public member_ `uint64 NumFirstHitRaysTraced;` — Total number of first hit rays traced
- L1062 _public member_ `uint64 NumBooleanRaysTraced;` — Total number of boolean visibility rays traced
- L1065 _public member_ `float FirstHitRayTraceThreadTime;` — Thread seconds spent tracing first hit rays
- L1068 _public member_ `float BooleanRayTraceThreadTime;` — Thread seconds spent tracing shadow rays
- L1071 _public member_ `float VolumeSamplePlacementThreadTime;` — Thread seconds spent placing volume lighting samples and then calculating their lighting.
- L1074 _public member_ `FIrradianceCacheStats Cache[NumTrackedBounces];` — Irradiance cache stats
- L1077 _public member_ `FCalculateIrradiancePhotonStats CalculateIrradiancePhotonStats;` — Stats from irradiance photon calculations.
- L1080 _public member_ `FCriticalSection StatsSync;` — Critical section that worker threads must acquire before writing to members of this class
- L1082 _public function_ `FStaticLightingStats() : SceneSetupTime(0), MeshAreaLightSetupTime(0), TotalLightingThreadTime(0), MainThreadLightingTime(0), NumMappings(0), NumTexelsProcessed(0), NumLights(0), NumMeshAreaLightMeshes(0), NumMeshAreaLights(0), NumMeshAreaLightPrimitives(0), NumSimplifiedMeshAreaLightPrimitives(0), NumDynamicObjectSurfaceSamples(0), NumDynamicObjectVolumeSamples(0), PrecomputedVisibilitySetupTime(0), NumPrecomputedVisibilityCellsTotal(0), NumPrecomputedVisibilityCellsCamaraTracks(0), NumPrecomputedVisibilityMeshes(0), NumPrecomputedVisibilityMeshesExcludedFromGroups(0), PrecomputedVisibilityDataBytes(0), EmitDirectPhotonsTime(0), EmitDirectPhotonsThreadTime(0), DirectPhotonsTracingThreadTime(0), DirectPhotonsLightSamplingThreadTime(0), DirectCustomAttenuationThreadTime(0), ProcessDirectPhotonsThreadTime(0), NumDirectPhotonsGathered(0), CachingIndirectPhotonPathsTime(0), EmitIndirectPhotonsTime(0), EmitIndirectPhotonsThreadTime(0), ProcessIndirectPhotonsThreadTime(0), LightSamplingThreadTime(0), IndirectCustomAttenuationThreadTime(0), IntersectLightRayThreadTime(0), PhotonBounceTracingThreadTime(0), NumIndirectPhotonsGathered(0), IrradiancePhotonMarkingTime(0), IrradiancePhotonMarkingThreadTime(0), IrradiancePhotonCalculatingTime(0), IrradiancePhotonCalculatingThreadTime(0),`

#### class `Lightmass::FSimpleQuadTreeNode`  
`template<typename ElementType> class FSimpleQuadTreeNode`  
_L1144-1163_
- L1147 _public member_ `ElementType Element;`
- L1149 _public member_ `FSimpleQuadTreeNode* Children[4];`
- L1151 _public function_ `FSimpleQuadTreeNode()`
- L1159 _public function_ `void AddChild(int32 Index, FSimpleQuadTreeNode* Child)`

#### class `Lightmass::FSimpleQuadTree`  
`template<typename ElementType> class FSimpleQuadTree`  
_L1166-1224_
- L1170 _public function_ `const ElementType& GetLeafElement(float U, float V) const`
- L1196 _public member_ `FSimpleQuadTreeNode<ElementType> RootNode;`
- L1198 _public function_ `~FSimpleQuadTree()`
- L1202 _public function_ `void ReturnToFreeList(TArray<FSimpleQuadTreeNode<ElementType>*>& OutNodes)`
- L1209 _private function_ `void ReturnToFreeListRecursive(FSimpleQuadTreeNode<ElementType>* Node, TArray<FSimpleQuadTreeNode<ElementType>*>& OutNodes) const`

#### class `Lightmass::FLightingAndOcclusion`  
`class FLightingAndOcclusion`  
_L1227-1259_
- desc: Lighting payload used by the adaptive refinement in final gathering.
- L1231 _public member_ `FLinearColor Lighting;`
- L1232 _public member_ `FVector3f UnoccludedSkyVector;`
- L1233 _public member_ `FLinearColor StationarySkyLighting;`
- L1234 _public member_ `float NumSamplesOccluded;`
- L1236 _public function_ `FLightingAndOcclusion() : Lighting(ForceInit), UnoccludedSkyVector(FVector3f(0)), StationarySkyLighting(FLinearColor::Black), NumSamplesOccluded(0)`
- L1243 _public function_ `FLightingAndOcclusion(const FLinearColor& InLighting, FVector3f InUnoccludedSkyVector, const FLinearColor& InStationarySkyLighting, float InNumSamplesOccluded) : Lighting(InLighting), UnoccludedSkyVector(InUnoccludedSkyVector), StationarySkyLighting(InStationarySkyLighting), NumSamplesOccluded(InNumSamplesOccluded)`

#### class `Lightmass::FRefinementElement`  
`class FRefinementElement`  
_L1262-1279_
- desc: Data stored for a sample that may need to be refined.
- L1265 _public member_ `FLightingAndOcclusion Lighting;`
- L1266 _public member_ `FVector2f Uniforms;`
- L1267 _public member_ `int32 HitPointIndex;`
- L1269 _public function_ `FRefinementElement() : Uniforms(FVector2f(0, 0)), HitPointIndex(-1)`
- L1274 _public function_ `FRefinementElement(FLightingAndOcclusion InLighting, FVector2f InUniforms, int32 InHitPointIndex) : Lighting(InLighting), Uniforms(InUniforms), HitPointIndex(InHitPointIndex)`

#### class `Lightmass::FStaticLightingMappingContext`  
`class FStaticLightingMappingContext`  
_L1282-1305_
- desc: Local state for a mapping, accessed only by the owning thread.
- L1285 _public member_ `FStaticLightingMappingStats Stats;`
- L1288 _public member_ `TLightingCache<FFinalGatherSample> FirstBounceCache;` — Lighting caches for the mapping
- L1290 _public member_ `FCoherentRayCache RayCache;`
- L1292 _public member_ `TArray<FDebugLightingCacheRecord> DebugCacheRecords;`
- L1294 _public member_ `TArray<FSimpleQuadTreeNode<FRefinementElement>* > RefinementTreeFreePool;`
- L1296 _public member_ `class FStaticLightingSystem& System;`
- L1299 _public member_ `FDebugLightingOutput* DebugOutput;` — This mapping's debug output, if any.
- L1302 _public prototype_ `FStaticLightingMappingContext(const FStaticLightingMesh* InSubjectMesh, class FStaticLightingSystem& InSystem, FDebugLightingOutput* InDebugOutput = nullptr);`
- L1304 _public prototype_ `~FStaticLightingMappingContext();`

#### class `Lightmass::FSceneLightPowerDistribution`  
`class FSceneLightPowerDistribution`  
_L1308-1319_
- desc: Information about the power distribution of lights in the scene.
- L1312 _public member_ `TArray<float> LightPDFs;` — Stores an unnormalized step 1D probability distribution function of emitting a photon from a given light
- L1315 _public member_ `TArray<float> LightCDFs;` — Stores the cumulative distribution function of LightPDFs
- L1318 _public member_ `float UnnormalizedIntegral;` — Stores the integral of LightPDFs

#### struct `Lightmass::FTextureMappingStaticLightingData`  
`struct FTextureMappingStaticLightingData`  
_L1322-1332_
- desc: The static lighting data for a texture mapping.
- L1324 _public member_ `FStaticLightingTextureMapping* Mapping;`
- L1325 _public member_ `FLightMapData2D* LightMapData;`
- L1326 _public member_ `TMap<const FLight*,FShadowMapData2D*> ShadowMaps;`
- L1327 _public member_ `TMap<const FLight*,FSignedDistanceFieldShadowMapData2D*> SignedDistanceFieldShadowMaps;`
- L1328 _public member_ `FDebugLightingOutput DebugOutput;`
- L1331 _public member_ `double ExecutionTime;` — Stores the time this mapping took to process

#### struct `Lightmass::FPrecomputedVisibilityData`  
`struct FPrecomputedVisibilityData`  
_L1335-1340_
- desc: Visibility output data from a single visibility task.
- L1337 _public member_ `FGuid Guid;`
- L1338 _public member_ `TArray<FPrecomputedVisibilityCell> PrecomputedVisibilityCells;`
- L1339 _public member_ `TArray<FDebugStaticLightingRay> DebugVisibilityRays;`

#### struct `Lightmass::FIrradianceBrickData`  
`struct FIrradianceBrickData`  
_L1342-1362_
- L1344 _public member_ `FGuid IntersectingLevelGuid;`
- L1347 _public member_ `FIntVector IndirectionTexturePosition;` — Position in the global indirection texture.  Used for mapping brick positions back to world space.
- L1350 _public member_ `int32 TreeDepth;` — Depth in the refinement tree, where 0 is the root.
- L1352 _public member_ `float AverageClosestGeometryDistance;`
- L1354 _public member_ `TArray<FFloat3Packed> AmbientVector;`
- L1355 _public member_ `TArray<FColor> SHCoefficients[6];`
- L1356 _public member_ `TArray<FColor> SkyBentNormal;`
- L1357 _public member_ `TArray<uint8> DirectionalLightShadowing;`
- L1359 _public member_ `TArray<FIrradianceVoxelImportProcessingData> VoxelImportProcessingData;`
- L1361 _public prototype_ `void SetFromVolumeLightingSample(int32 Index, const FVolumeLightingSample& Sample, bool bInsideGeometry, float MinDistanceToSurface, bool bBorderVoxel);`

#### struct `Lightmass::FVolumetricLightmapTaskData`  
`struct FVolumetricLightmapTaskData`  
_L1365-1370_
- desc: Output data from a single volumetric lightmap task.
- L1367 _public member_ `FGuid Guid;`
- L1368 _public member_ `TArray<FIrradianceBrickData> BrickData;`
- L1369 _public member_ `FDebugLightingOutput DebugOutput;`

#### class `Lightmass::FStaticLightingThreadRunnable`  
`class FStaticLightingThreadRunnable : public FRunnable`  
_L1374-1414_
- inherits: `FRunnable`
- desc: A thread which processes static lighting mappings.
- L1378 _public member_ `FRunnableThread* Thread;`
- L1381 _public member_ `float ExecutionTime;` — Seconds that the thread spent in Run()
- L1383 _public member_ `float IdleTime;`
- L1386 _public member_ `double EndTime;` — Seconds since GStartupTime that the thread exited Run()
- L1388 _public member_ `int32 ThreadIndex;`
- L1390 _public member_ `FThreadStatistics ThreadStatistics;`
- L1393 _public function_ `FStaticLightingThreadRunnable(FStaticLightingSystem* InSystem, int32 InThreadIndex) : Thread(NULL), IdleTime(0), ThreadIndex(InThreadIndex), System(InSystem), bTerminatedByError(false)` — Initialization constructor.
- L1402 _public prototype_ `bool CheckHealth(bool bReportError = true) const;` — Checks the thread's health, and passes on any errors that have occurred.  Called by the main thread.
- L1404 _public prototype_ `void FixThreadGroupAffinity() const;`
- L1407 _protected member_ `FStaticLightingSystem* System;`
- L1410 _protected member_ `FString ErrorMessage;` — If the thread has been terminated by an unhandled exception, this contains the error message.
- L1413 _protected member_ `bool bTerminatedByError;` — true if the thread has been terminated by an unhandled exception.

#### class `Lightmass::FDirectPhotonEmittingInput`  
`class FDirectPhotonEmittingInput`  
_L1417-1430_
- desc: Input required to emit direct photons.
- L1420 _public member_ `const FBoxSphereBounds3f& ImportanceBounds;`
- L1421 _public member_ `const FSceneLightPowerDistribution& LightDistribution;`
- L1423 _public function_ `FDirectPhotonEmittingInput( const FBoxSphereBounds3f& InImportanceBounds, const FSceneLightPowerDistribution& InLightDistribution) : ImportanceBounds(InImportanceBounds), LightDistribution(InLightDistribution)`

#### class `Lightmass::FDirectPhotonEmittingWorkRange`  
`class FDirectPhotonEmittingWorkRange`  
_L1433-1449_
- desc: A work range for emitting direct photons, which is the smallest unit that can be parallelized.
- L1436 _public member_ `const int32 RangeIndex;`
- L1437 _public member_ `const int32 NumDirectPhotonsToEmit;`
- L1438 _public member_ `const int32 TargetNumIndirectPhotonPaths;`
- L1440 _public function_ `FDirectPhotonEmittingWorkRange( int32 InRangeIndex, int32 InNumDirectPhotonsToEmit, int32 InTargetNumIndirectPhotonPaths) : RangeIndex(InRangeIndex), NumDirectPhotonsToEmit(InNumDirectPhotonsToEmit), TargetNumIndirectPhotonPaths(InTargetNumIndirectPhotonPaths)`

#### class `Lightmass::FDirectPhotonEmittingOutput`  
`class FDirectPhotonEmittingOutput`  
_L1452-1478_
- desc: Direct photon emitting output for a single FDirectPhotonEmittingWorkRange.
- L1459 _public member_ `volatile int32 OutputComplete;` — A worker thread will increment this counter once the output is complete, so that the main thread can process it while the worker thread moves on.
- L1460 _public member_ `int32 NumPhotonsEmittedDirect;`
- L1461 _public member_ `TArray<FPhoton> DirectPhotons;`
- L1462 _public member_ `TArray<FIrradiancePhoton>* IrradiancePhotons;`
- L1463 _public member_ `TArray<TArray<FIndirectPathRay> > IndirectPathRays;`
- L1464 _public member_ `int32 NumPhotonsEmitted;`
- L1465 _public member_ `float DirectPhotonsTracingThreadTime;`
- L1466 _public member_ `float DirectPhotonsLightSamplingThreadTime;`
- L1467 _public member_ `float DirectCustomAttenuationThreadTime;`
- L1469 _public function_ `FDirectPhotonEmittingOutput(TArray<FIrradiancePhoton>* InIrradiancePhotons) : OutputComplete(0), NumPhotonsEmittedDirect(0), IrradiancePhotons(InIrradiancePhotons), NumPhotonsEmitted(0), DirectPhotonsTracingThreadTime(0), DirectPhotonsLightSamplingThreadTime(0), DirectCustomAttenuationThreadTime(0)`

#### class `Lightmass::FDirectPhotonEmittingThreadRunnable`  
`class FDirectPhotonEmittingThreadRunnable : public FStaticLightingThreadRunnable`  
_L1481-1503_
- inherits: `FStaticLightingThreadRunnable`
- desc: Thread used to parallelize indirect photon emitting.
- L1486 _public function_ `FDirectPhotonEmittingThreadRunnable( FStaticLightingSystem* InSystem, int32 InThreadIndex, const FDirectPhotonEmittingInput& InInput) : FStaticLightingThreadRunnable(InSystem, InThreadIndex), Input(InInput)` — Initialization constructor.
- L1496 _public function_ `virtual bool Init(void)` — FRunnable interface.
- L1497 _public function_ `virtual void Exit(void)`
- L1498 _public function_ `virtual void Stop(void)`
- L1499 _public prototype_ `virtual uint32 Run(void);`
- L1502 _protected member_ `const FDirectPhotonEmittingInput& Input;`

#### class `Lightmass::FIndirectPhotonEmittingInput`  
`class FIndirectPhotonEmittingInput`  
_L1506-1522_
- desc: Input required to emit indirect photons.
- L1509 _public member_ `const FBoxSphereBounds3f& ImportanceBounds;`
- L1510 _public member_ `const FSceneLightPowerDistribution& LightDistribution;`
- L1511 _public member_ `const TArray<TArray<FIndirectPathRay> >& IndirectPathRays;`
- L1513 _public function_ `FIndirectPhotonEmittingInput( const FBoxSphereBounds3f& InImportanceBounds, const FSceneLightPowerDistribution& InLightDistribution, const TArray<TArray<FIndirectPathRay> >& InIndirectPathRays) : ImportanceBounds(InImportanceBounds), LightDistribution(InLightDistribution), IndirectPathRays(InIndirectPathRays)`

#### class `Lightmass::FIndirectPhotonEmittingWorkRange`  
`class FIndirectPhotonEmittingWorkRange`  
_L1525-1538_
- desc: A work range for emitting indirect photons, which is the smallest unit that can be parallelized.
- L1528 _public member_ `const int32 RangeIndex;`
- L1529 _public member_ `const int32 NumIndirectPhotonsToEmit;`
- L1531 _public function_ `FIndirectPhotonEmittingWorkRange( int32 InRangeIndex, int32 InNumIndirectPhotonsToEmit) : RangeIndex(InRangeIndex), NumIndirectPhotonsToEmit(InNumIndirectPhotonsToEmit)`

#### class `Lightmass::FIndirectPhotonEmittingOutput`  
`class FIndirectPhotonEmittingOutput`  
_L1541-1572_
- desc: Indirect photon emitting output for a single FIndirectPhotonEmittingWorkRange.
- L1548 _public member_ `volatile int32 OutputComplete;` — A worker thread will increment this counter once the output is complete, so that the main thread can process it while the worker thread moves on.
- L1549 _public member_ `int32 NumPhotonsEmittedFirstBounce;`
- L1550 _public member_ `TArray<FPhoton> FirstBouncePhotons;`
- L1551 _public member_ `TArray<FPhoton> FirstBounceEscapedPhotons;`
- L1552 _public member_ `int32 NumPhotonsEmittedSecondBounce;`
- L1553 _public member_ `TArray<FPhoton> SecondBouncePhotons;`
- L1554 _public member_ `TArray<FIrradiancePhoton>* IrradiancePhotons;`
- L1555 _public member_ `int32 NumPhotonsEmitted;`
- L1556 _public member_ `float LightSamplingThreadTime;`
- L1557 _public member_ `float IndirectCustomAttenuationThreadTime;`
- L1558 _public member_ `float IntersectLightRayThreadTime;`
- L1559 _public member_ `float PhotonBounceTracingThreadTime;`
- L1561 _public function_ `FIndirectPhotonEmittingOutput(TArray<FIrradiancePhoton>* InIrradiancePhotons) : OutputComplete(0), NumPhotonsEmittedFirstBounce(0), NumPhotonsEmittedSecondBounce(0), IrradiancePhotons(InIrradiancePhotons), NumPhotonsEmitted(0), LightSamplingThreadTime(0), IndirectCustomAttenuationThreadTime(0), IntersectLightRayThreadTime(0), PhotonBounceTracingThreadTime(0)`

#### class `Lightmass::FIndirectPhotonEmittingThreadRunnable`  
`class FIndirectPhotonEmittingThreadRunnable : public FStaticLightingThreadRunnable`  
_L1575-1597_
- inherits: `FStaticLightingThreadRunnable`
- desc: Thread used to parallelize indirect photon emitting.
- L1580 _public function_ `FIndirectPhotonEmittingThreadRunnable( FStaticLightingSystem* InSystem, int32 InThreadIndex, const FIndirectPhotonEmittingInput& InInput) : FStaticLightingThreadRunnable(InSystem, InThreadIndex), Input(InInput)` — Initialization constructor.
- L1590 _public function_ `virtual bool Init(void)` — FRunnable interface.
- L1591 _public function_ `virtual void Exit(void)`
- L1592 _public function_ `virtual void Stop(void)`
- L1593 _public prototype_ `virtual uint32 Run(void);`
- L1596 _protected member_ `const FIndirectPhotonEmittingInput& Input;`

#### class `Lightmass::FIrradianceMarkingWorkRange`  
`class FIrradianceMarkingWorkRange`  
_L1600-1614_
- desc: Smallest unit of irradiance photon marking work that can be done in parallel.
- L1603 _public member_ `const int32 RangeIndex;`
- L1605 _public member_ `const int32 IrradiancePhotonArrayIndex;` — Index into IrradiancePhotons that should be processed for this work range.
- L1607 _public function_ `FIrradianceMarkingWorkRange( int32 InRangeIndex, int32 InIrradiancePhotonArrayIndex) : RangeIndex(InRangeIndex), IrradiancePhotonArrayIndex(InIrradiancePhotonArrayIndex)`

#### class `Lightmass::FIrradiancePhotonMarkingThreadRunnable`  
`class FIrradiancePhotonMarkingThreadRunnable : public FStaticLightingThreadRunnable`  
_L1616-1635_
- inherits: `FStaticLightingThreadRunnable`
- L1621 _public function_ `FIrradiancePhotonMarkingThreadRunnable(FStaticLightingSystem* InSystem, int32 InThreadIndex, TArray<TArray<FIrradiancePhoton>>& InIrradiancePhotons) : FStaticLightingThreadRunnable(InSystem, InThreadIndex), IrradiancePhotons(InIrradiancePhotons)` — Initialization constructor.
- L1627 _public function_ `virtual bool Init(void)` — FRunnable interface.
- L1628 _public function_ `virtual void Exit(void)`
- L1629 _public function_ `virtual void Stop(void)`
- L1630 _public prototype_ `virtual uint32 Run(void);`
- L1634 _private member_ `TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons;` — Irradiance photons to operate on

#### class `Lightmass::FIrradianceCalculatingWorkRange`  
`class FIrradianceCalculatingWorkRange`  
_L1638-1652_
- desc: Smallest unit of irradiance photon calculating work that can be done in parallel.
- L1641 _public member_ `const int32 RangeIndex;`
- L1643 _public member_ `const int32 IrradiancePhotonArrayIndex;` — Index into IrradiancePhotons that should be processed for this work range.
- L1645 _public function_ `FIrradianceCalculatingWorkRange( int32 InRangeIndex, int32 InIrradiancePhotonArrayIndex) : RangeIndex(InRangeIndex), IrradiancePhotonArrayIndex(InIrradiancePhotonArrayIndex)`

#### class `Lightmass::FIrradiancePhotonCalculatingThreadRunnable`  
`class FIrradiancePhotonCalculatingThreadRunnable : public FStaticLightingThreadRunnable`  
_L1654-1676_
- inherits: `FStaticLightingThreadRunnable`
- L1659 _public member_ `FCalculateIrradiancePhotonStats Stats;` — Stats for this thread's operations.
- L1662 _public function_ `FIrradiancePhotonCalculatingThreadRunnable(FStaticLightingSystem* InSystem, int32 InThreadIndex, TArray<TArray<FIrradiancePhoton>>& InIrradiancePhotons) : FStaticLightingThreadRunnable(InSystem, InThreadIndex), IrradiancePhotons(InIrradiancePhotons)` — Initialization constructor.
- L1668 _public function_ `virtual bool Init(void)` — FRunnable interface.
- L1669 _public function_ `virtual void Exit(void)`
- L1670 _public function_ `virtual void Stop(void)`
- L1671 _public prototype_ `virtual uint32 Run(void);`
- L1675 _private member_ `TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons;` — Irradiance photons to operate on

#### enum `Lightmass::EStaticLightingTaskType`  
`enum EStaticLightingTaskType`  
_L1679-1686_
- desc: Indicates which type of task a FMappingProcessingThreadRunnable should execute
- L1681 _public enumerator_ `StaticLightingTask_ProcessMappings`
- L1682 _public enumerator_ `StaticLightingTask_CacheIrradiancePhotons`
- L1683 _public enumerator_ `StaticLightingTask_RadiositySetup`
- L1684 _public enumerator_ `StaticLightingTask_RadiosityIterations`
- L1685 _public enumerator_ `StaticLightingTask_FinalizeSurfaceCache`

#### class `Lightmass::FMappingProcessingThreadRunnable`  
`class FMappingProcessingThreadRunnable : public FStaticLightingThreadRunnable`  
_L1689-1715_
- inherits: `FStaticLightingThreadRunnable`
- desc: A thread which processes static lighting mappings.
- L1692 _private member_ `FThreadSafeCounter FinishedCounter;` — > 0 this thread has finished working
- L1696 _public member_ `EStaticLightingTaskType TaskType;`
- L1699 _public function_ `FMappingProcessingThreadRunnable(FStaticLightingSystem* InSystem, int32 ThreadIndex, EStaticLightingTaskType InTaskType) : FStaticLightingThreadRunnable(InSystem, ThreadIndex), FinishedCounter(0), TaskType(InTaskType)` — Initialization constructor.
- L1706 _public function_ `virtual bool Init(void)` — FRunnable interface.
- L1707 _public function_ `virtual void Exit(void)`
- L1708 _public function_ `virtual void Stop(void)`
- L1709 _public prototype_ `virtual uint32 Run(void);`
- L1711 _public function_ `bool IsComplete()`

#### class `Lightmass::TCompleteStaticLightingList`  
`template<typename StaticLightingDataType> class TCompleteStaticLightingList`  
_L1719-1751_
- desc: Encapsulates a list of mappings which static lighting has been computed for, but not yet applied.
- L1724 _public function_ `TCompleteStaticLightingList(): FirstElement(NULL)` — Initialization constructor.
- L1729 _public function_ `void AddElement(TList<StaticLightingDataType>* Element)` — Adds an element to the list.
- L1746 _public prototype_ `void ApplyAndClear(FStaticLightingSystem& LightingSystem);` — Applies the static lighting to the mappings in the list, and clears the list. Also reports back to Unreal after each mapping has been exported. @param LightingSystem - Reference to the static lighting system
- L1750 _protected member_ `TList<StaticLightingDataType>* FirstElement;`

#### class `Lightmass::TCompleteTaskList`  
`template<typename DataType> class TCompleteTaskList : public TCompleteStaticLightingList<DataType>`  
_L1754-1758_
- inherits: `TCompleteStaticLightingList<DataType>`
- L1757 _public prototype_ `void ApplyAndClear(FStaticLightingSystem& LightingSystem);`

#### class `Lightmass::FBaseTextureTaskDescription`  
`class FBaseTextureTaskDescription`  
_L1761-1787_
- desc: Base class for a task that operates on a rectangle of a texture mapping.
- L1764 _public member_ `int32 StartX;`
- L1765 _public member_ `int32 StartY;`
- L1766 _public member_ `int32 SizeX;`
- L1767 _public member_ `int32 SizeY;`
- L1768 _public member_ `bool bDebugThisMapping;`
- L1769 _public member_ `FStaticLightingTextureMapping* TextureMapping;`
- L1770 _public member_ `FStaticLightingMappingContext MappingContext;`
- L1771 _public member_ `FGatheredLightMapData2D* LightMapData;`
- L1772 _public member_ `const class FTexelToVertexMap* TexelToVertexMap;`
- L1773 _public member_ `bool bProcessedOnMainThread;`
- L1775 _public function_ `FBaseTextureTaskDescription(const FStaticLightingMesh* InSubjectMesh, class FStaticLightingSystem& InSystem) : StartX(0), StartY(0), SizeX(0), SizeY(0), bDebugThisMapping(false), TextureMapping(NULL), MappingContext(InSubjectMesh, InSystem), LightMapData(NULL), TexelToVertexMap(NULL), bProcessedOnMainThread(false)`

#### class `Lightmass::FCacheIndirectTaskDescription`  
`class FCacheIndirectTaskDescription : public FBaseTextureTaskDescription`  
_L1790-1797_
- inherits: `FBaseTextureTaskDescription`
- desc: Class for a task that populates the irradiance cache for a texture mapping.
- L1794 _public function_ `FCacheIndirectTaskDescription(const FStaticLightingMesh* InSubjectMesh, class FStaticLightingSystem& InSystem) : FBaseTextureTaskDescription(InSubjectMesh, InSystem)`

#### class `Lightmass::FInterpolateIndirectTaskDescription`  
`class FInterpolateIndirectTaskDescription : public FBaseTextureTaskDescription`  
_L1800-1809_
- inherits: `FBaseTextureTaskDescription`
- desc: Class for a task that interpolates from the irradiance cache for a texture mapping.
- L1803 _public member_ `TLightingCache<FFinalGatherSample>* FirstBounceCache;`
- L1805 _public function_ `FInterpolateIndirectTaskDescription(const FStaticLightingMesh* InSubjectMesh, class FStaticLightingSystem& InSystem) : FBaseTextureTaskDescription(InSubjectMesh, InSystem), FirstBounceCache(NULL)`

#### class `Lightmass::FVolumeSamplesTaskDescription`  
`class FVolumeSamplesTaskDescription`  
_L1812-1824_
- L1815 _public member_ `FGuid LevelId;`
- L1816 _public member_ `int32 StartIndex;`
- L1817 _public member_ `int32 NumSamples;`
- L1819 _public function_ `FVolumeSamplesTaskDescription(FGuid InLevelId, int32 InStartIndex, int32 InNumSamples) : LevelId(InLevelId), StartIndex(InStartIndex), NumSamples(InNumSamples)`

#### class `Lightmass::FVisibilityMeshGroup`  
`class FVisibilityMeshGroup`  
_L1826-1833_
- L1829 _public member_ `FBox3f GroupBounds;`
- L1832 _public member_ `TArray<int32> VisibilityIds;` — Array of all the meshes contained in the group.  These entries index into VisibilityMeshes.

#### class `Lightmass::FVisibilityMesh`  
`class FVisibilityMesh`  
_L1835-1840_
- L1838 _public member_ `bool bInGroup;`
- L1839 _public member_ `TArray<FStaticLightingMesh*> Meshes;`

#### enum `Lightmass::EFinalGatherRayBiasMode`  
`enum EFinalGatherRayBiasMode`  
_L1842-1846_
- L1844 _public enumerator_ `RBM_ConstantNormalOffset`
- L1845 _public enumerator_ `RBM_ScaledNormalOffset`

#### class `Lightmass::FStaticLightingSystem`  
`class FStaticLightingSystem`  
_L1849-2805_
- desc: The state of the static lighting system.
- L1854 _public member_ `mutable FDebugLightingOutput StartupDebugOutput;` — Debug data generated by startup passes (photon mapping) to transfer back to Unreal.
- L1856 _public member_ `FVolumeLightingDebugOutput VolumeLightingDebugOutput;`
- L1859 _public member_ `mutable FCriticalSection DebugOutputSync;` — Threads must acquire this critical section before reading or writing to StartupDebugOutput or VolumeLightingDebugOutput, if contention is possible.
- L1868 _public prototype_ `FStaticLightingSystem( const FLightingBuildOptions& InOptions, class FScene& InScene, class FLightmassSolverExporter& InExporter, int32 InNumThreads );` — Initializes this static lighting system, and builds static lighting based on the provided options. @param InOptions		- The static lighting build options. @param InScene		- The scene containing all the lights and meshes @param InExporter	- The exporter used to send completed data back to Unreal @param InNumThreads	- Number of concurrent threads to use for lighting building
- L1870 _public prototype_ `~FStaticLightingSystem();`
- L1876 _public function_ `class FLightmassSolverExporter& GetExporter()` — Returns the Lightmass exporter (back to Unreal) @return	Lightmass exporter
- L1881 _public function_ `FGuid GetDebugGuid() const`
- L1888 _public function_ `bool IsDebugMode() const` — Whether the Lighting System is in debug mode or not. When in debug mode, Swarm is not completely hooked up and the system will process all mappings in the scene file on its own. @return	true if in debug mode
- L1893 _public function_ `bool HasSkyShadowing() const`
- L1910 _public prototype_ `void CalculateTexelCorners(const FStaticLightingMesh* Mesh, class FTexelToCornersMap& TexelToCornersMap, int32 UVIndex, bool bDebugThisMapping) const;` — Rasterizes Mesh into TexelToCornersMap
- L1913 _public prototype_ `void CalculateTexelCorners( const TArray<int32>& TriangleIndices, const TArray<FStaticLightingVertex>& Vertices, FTexelToCornersMap& TexelToCornersMap, const TArray<int32>& ElementIndices, int32 MaterialIndex, int32 UVIndex, bool bDebugThisMapping, FVector2f UVBias, FVector2f UVScale) const;` — Rasterizes Mesh into TexelToCornersMap, with extra parameters like which material index to rasterize and UV scale and bias.
- L1924 _public function_ `FStaticLightingAggregateMeshType& GetAggregateMesh()`
- L1932 _private prototype_ `void ExportNonMappingTasks();` — Exports tasks that are not mappings, if they are ready.
- L1935 _private prototype_ `int32 GetNumShadowRays(int32 BounceNumber, bool bPenumbra=false) const;` — Internal accessors
- L1936 _private prototype_ `int32 GetNumUniformHemisphereSamples(int32 BounceNumber) const;`
- L1937 _private prototype_ `int32 GetNumPhotonImportanceHemisphereSamples() const;`
- L1939 _private prototype_ `FBoxSphereBounds3f GetImportanceBounds(bool bClampToScene = true) const;`
- L1942 _private prototype_ `bool IsPointInImportanceVolume(const FVector4f& Position, float Tolerance = 0.0f) const;` — Returns true if the specified position is inside any of the importance volumes.
- L1945 _private prototype_ `void ValidateSettings(FScene& InScene);` — Changes the scene's settings if necessary so that only valid combinations are used
- L1948 _private prototype_ `void DumpStats(float TotalStaticLightingTime) const;` — Logs solver stats
- L1951 _private prototype_ `void LogSolverMessage(const FString& Message) const;` — Logs a solver message
- L1954 _private prototype_ `void UpdateInternalStatus(int32 OldNumTexelsCompleted) const;` — Logs a progress update message when appropriate
- L1957 _private prototype_ `void CacheSamples();` — Caches samples for any sampling distributions that are known ahead of time, which greatly reduces noise in those estimates.
- L1960 _private prototype_ `void InitializePhotonSettings();` — Sets up photon mapping settings.
- L1963 _private prototype_ `void EmitPhotons();` — Emits photons, builds data structures to accelerate photon map lookups, and does any other photon preprocessing required.
- L1966 _private prototype_ `void EmitDirectPhotons( const FBoxSphereBounds3f& ImportanceBounds, TArray<TArray<FIndirectPathRay> >& IndirectPathRays, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons);` — Gathers direct photons and generates indirect photon paths.
- L1972 _private prototype_ `void EmitDirectPhotonsThreadLoop(const FDirectPhotonEmittingInput& Input, int32 ThreadIndex);` — Entrypoint for all threads emitting direct photons.
- L1975 _private prototype_ `void EmitDirectPhotonsWorkRange( const FDirectPhotonEmittingInput& Input, FDirectPhotonEmittingWorkRange WorkRange, FDirectPhotonEmittingOutput& Output);` — Emits direct photons for a given work range.
- L1980 _private prototype_ `void BuildPhotonSegmentMap(const FPhotonOctree& SourcePhotonMap, FPhotonSegmentOctree& OutPhotonSegementMap, float AddToSegmentMapChance);`
- L1983 _private prototype_ `void EmitIndirectPhotons( const FBoxSphereBounds3f& ImportanceBounds, const TArray<TArray<FIndirectPathRay> >& IndirectPathRays, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons);` — Gathers indirect photons based on the indirect photon paths.
- L1989 _private prototype_ `void EmitIndirectPhotonsThreadLoop(const FIndirectPhotonEmittingInput& Input, int32 ThreadIndex);` — Entrypoint for all threads emitting indirect photons.
- L1992 _private prototype_ `void EmitIndirectPhotonsWorkRange( const FIndirectPhotonEmittingInput& Input, FIndirectPhotonEmittingWorkRange WorkRange, FIndirectPhotonEmittingOutput& Output);` — Emits indirect photons for a given work range.
- L1998 _private prototype_ `void MarkIrradiancePhotons(const FBoxSphereBounds3f& ImportanceBounds, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons);` — Iterates through all irradiance photons, searches for nearby direct photons, and marks the irradiance photon has having direct photon influence if necessary.
- L2001 _private prototype_ `void MarkIrradiancePhotonsThreadLoop( int32 ThreadIndex, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons);` — Entry point for all threads marking irradiance photons.
- L2006 _private prototype_ `void MarkIrradiancePhotonsWorkRange( TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons, FIrradianceMarkingWorkRange WorkRange);` — Marks irradiance photons specified by a single work range.
- L2011 _private prototype_ `void CalculateIrradiancePhotons(const FBoxSphereBounds3f& ImportanceBounds, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons);` — Calculates irradiance for photons randomly chosen to precalculate irradiance.
- L2014 _private prototype_ `void CalculateIrradiancePhotonsThreadLoop( int32 ThreadIndex, TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons, FCalculateIrradiancePhotonStats& Stats);` — Main loop that all threads access to calculate irradiance photons.
- L2020 _private prototype_ `void CalculateIrradiancePhotonsWorkRange( TArray<TArray<FIrradiancePhoton>>& IrradiancePhotons, FIrradianceCalculatingWorkRange WorkRange, FCalculateIrradiancePhotonStats& Stats);` — Calculates irradiance for the photons specified by a single work range.
- L2026 _private prototype_ `void CacheIrradiancePhotons();` — Cache irradiance photons on surfaces.
- L2029 _private prototype_ `void CacheIrradiancePhotonsThreadLoop(int32 ThreadIndex, bool bIsMainThread);` — Main loop that all threads access to cache irradiance photons.
- L2032 _private prototype_ `void CacheIrradiancePhotonsTextureMapping(FStaticLightingTextureMapping* TextureMapping);` — Caches irradiance photons on a single texture mapping.
- L2034 _private prototype_ `void SetupRadiosity();`
- L2035 _private prototype_ `void RadiositySetupThreadLoop(int32 ThreadIndex, bool bIsMainThread);`
- L2036 _private prototype_ `void RadiositySetupTextureMapping(FStaticLightingTextureMapping* TextureMapping);`
- L2037 _private prototype_ `void RunRadiosityIterations();`
- L2039 _private prototype_ `void RadiosityIterationThreadLoop(int32 ThreadIndex, bool bIsMainThread);`
- L2042 _private prototype_ `void FinalizeSurfaceCache();` — Cache irradiance photons on surfaces.
- L2045 _private prototype_ `void FinalizeSurfaceCacheThreadLoop(int32 ThreadIndex, bool bIsMainThread);` — Main loop that all threads access to cache irradiance photons.
- L2048 _private prototype_ `void FinalizeSurfaceCacheTextureMapping(FStaticLightingTextureMapping* TextureMapping);` — Caches irradiance photons on a single texture mapping.
- L2050 _private prototype_ `void RasterizeToSurfaceCacheTextureMapping(FStaticLightingTextureMapping* TextureMapping, bool bDebugThisMapping, FTexelToVertexMap& TexelToVertexMap);`
- L2052 _private prototype_ `void AdjustRepresentativeSurfelForTexelsTextureMapping(FStaticLightingTextureMapping* TextureMapping, FTexelToVertexMap& TexelToVertexMap, FTexelToCornersMap& TexelToCornersMap, FGatheredLightMapData2D* LightMapData, FStaticLightingMappingContext& MappingContext, bool bDebugThisMapping) const;`
- L2054 _private prototype_ `void RadiosityIterationTextureMapping(FStaticLightingTextureMapping* TextureMapping, int32 PassIndex);`
- L2056 _private prototype_ `void RadiosityIterationCachedHitpointsTextureMapping(const FTexelToVertexMap& TexelToVertexMap, FStaticLightingTextureMapping* TextureMapping, int32 PassIndex);`
- L2059 _private prototype_ `bool FindAnyNearbyPhoton( const FPhotonOctree& PhotonMap, const FVector4f& SearchPosition, float MaxPhotonSearchDistance, bool bDebugThisLookup) const;` — Returns true if a photon was found within MaxPhotonSearchDistance.
- L2072 _private prototype_ `float FindNearbyPhotonsIterative( const FPhotonOctree& PhotonMap, const FVector4f& SearchPosition, const FVector4f& SearchNormal, int32 NumPhotonsToFind, float StartPhotonSearchDistance, float MaxPhotonSearchDistance, bool bDebugSearchResults, bool bDebugSearchProcess, TArray<FPhoton>& FoundPhotons, FFindNearbyPhotonStats& SearchStats) const;` — Searches the given photon map for the nearest NumPhotonsToFind photons to SearchPosition using an iterative process, Unless the start and max search distances are the same, in which case all photons in that distance will be returned. The iterative search starts at StartPhotonSearchDistance and doubles the search distance until enough photons are found or the distance is greater than MaxPhotonSearchDistance. @return - the furthest found photon's distance squared from SearchPosition, unless the start and max search distances are the same, in which case FMath::Square(MaxPhotonSearchDistance) will be returned.
- L2084 _private prototype_ `float FindNearbyPhotonsInVolumeIterative( const FPhotonSegmentOctree& PhotonSegmentMap, const FVector4f& SearchPosition, int32 NumPhotonsToFind, float StartPhotonSearchDistance, float MaxPhotonSearchDistance, TArray<FPhotonSegmentElement>& FoundPhotonSegments, bool bDebugThisLookup) const;`
- L2097 _private prototype_ `float FindNearbyPhotonsSorted( const FPhotonOctree& PhotonMap, const FVector4f& SearchPosition, const FVector4f& SearchNormal, int32 NumPhotonsToFind, float MaxPhotonSearchDistance, bool bDebugSearchResults, bool bDebugSearchProcess, TArray<FPhoton>& FoundPhotons, FFindNearbyPhotonStats& SearchStats) const;` — Searches the given photon map for the nearest NumPhotonsToFind photons to SearchPosition by sorting octree nodes nearest to furthest. @return - the furthest found photon's distance squared from SearchPosition.
- L2109 _private prototype_ `FIrradiancePhoton* FindNearestIrradiancePhoton( const FMinimalStaticLightingVertex& Vertex, FStaticLightingMappingContext& MappingContext, TArray<FIrradiancePhoton*>& TempIrradiancePhotons, bool bVisibleOnly, bool bDebugThisLookup) const;` — Finds the nearest irradiance photon, if one exists.
- L2117 _private prototype_ `FLinearColor CalculatePhotonIrradiance( const FPhotonOctree& PhotonMap, int32 NumPhotonsEmitted, int32 NumPhotonsToFind, float SearchDistance, const FIrradiancePhoton& IrradiancePhoton, bool bDebugThisCalculation, TArray<FPhoton>& TempFoundPhotons, FCalculateIrradiancePhotonStats& Stats) const;` — Calculates the irradiance for an irradiance photon
- L2128 _private prototype_ `FGatheredLightSample CalculatePhotonIncidentRadiance( const FPhotonOctree& PhotonMap, int32 NumPhotonsEmitted, float SearchDistance, const FStaticLightingVertex& Vertex, bool bDebugThisDensityEstimation) const;` — Calculates incident radiance at a vertex from the given photon map.
- L2136 _private prototype_ `FLinearColor CalculatePhotonExitantRadiance( const FPhotonOctree& PhotonMap, int32 NumPhotonsEmitted, float SearchDistance, const FStaticLightingMesh* Mesh, const FMinimalStaticLightingVertex& Vertex, int32 ElementIndex, const FVector4f& OutgoingDirection, bool bDebugThisDensityEstimation) const;` — Calculates exitant radiance at a vertex from the given photon map.
- L2147 _private prototype_ `void BeginCalculateVolumeSamples();` — Places volume lighting samples and calculates lighting for them.
- L2153 _private prototype_ `FGatheredLightSample InterpolatePrecomputedVolumeIncidentRadiance( const FStaticLightingVertex& Vertex, float SampleRadius, FCoherentRayCache& RayCache, bool bDebugThisTexel) const;` — Interpolates lighting from the volume lighting samples to a vertex. This mirrors FPrecomputedLightVolume::InterpolateIncidentRadiance in Unreal, used for visualizing interpolation from the lighting volume on surfaces.
- L2164 _private prototype_ `template<int32 SHOrder> void CalculateApproximateDirectLighting( const FStaticLightingVertex& Vertex, float SampleRadius, const TArray<FVector3f, TInlineAllocator<1>>& VertexOffsets, float LightSampleFraction, bool bCompositeAllLights, bool bCalculateForIndirectLighting, bool bDebugThisSample, FStaticLightingMappingContext& MappingContext, TGatheredLightSample<SHOrder>& OutStaticDirectLighting, float& OutToggleableDirectionalLightShadowing) const;` — Computes direct lighting for a volume point. Caller is responsible for initializing the outputs to something valid.
- L2177 _private prototype_ `void GatherVolumeImportancePhotonDirections( const FVector3f WorldPosition, FVector3f FirstHemisphereNormal, FVector3f SecondHemisphereNormal, TArray<FVector4f>& FirstHemisphereImportancePhotonDirections, TArray<FVector4f>& SecondHemisphereImportancePhotonDirections, bool bDebugThisSample) const;`
- L2186 _private prototype_ `void CalculateVolumeSampleIncidentRadiance( const TArray<FVector4f>& UniformHemisphereSamples, const TArray<FVector2f>& UniformHemisphereSampleUniforms, float MaxUnoccludedLength, const TArray<FVector3f, TInlineAllocator<1>>& VertexOffsets, FVolumeLightingSample& LightingSample, float& OutBackfacingHitsFraction, float& OutMinDistanceToSurface, FLMRandomStream& RandomStream, FStaticLightingMappingContext& MappingContext, bool bDebugThisSample ) const;` — Calculates incident radiance for a given world space position.
- L2200 _private prototype_ `void SetupPrecomputedVisibility();` — Determines visibility cell placement, called once at startup.
- L2202 _private prototype_ `int32 GetGroupCellIndex(FVector3f BoxCenter) const;`
- L2205 _private prototype_ `void CalculatePrecomputedVisibility(int32 BucketIndex);` — Calculates visibility for a given group of cells, called from all threads.
- L2207 _private prototype_ `void RecursivelyBuildBrickTree( int32 StartCellIndex, int32 NumCells, FIntVector CellCoordinate, int32 TreeDepth, bool bCoveringDebugPosition, const FBox3f& TopLevelCellBounds, const TArray<FVector3f>& VoxelTestPositions, const FGuid& IntersectingLevelGuid, TArray<struct FIrradianceBrickBuildData>& OutBrickBuildData);`
- L2218 _private prototype_ `void ProcessVolumetricLightmapBrickTask(class FVolumetricLightmapBrickTaskDescription* Task);`
- L2220 _private prototype_ `bool ProcessVolumetricLightmapTaskIfAvailable();`
- L2222 _private prototype_ `void GenerateVoxelTestPositions(TArray<FVector3f>& VoxelTestPositions) const;`
- L2224 _private prototype_ `void CalculateAdaptiveVolumetricLightmap(int32 TaskIndex);`
- L2226 _private prototype_ `bool DoesVoxelIntersectSceneGeometry(const FBox3f& CellBounds, FGuid& OutIntersectingLevelGuid) const;`
- L2228 _private prototype_ `bool ShouldRefineVoxel(int32 TreeDepth, const FBox3f& AABB, const TArray<FVector3f>& VoxelTestPositions, bool bDebugThisVoxel, FGuid& OutIntersectingLevelGuid) const;`
- L2231 _private prototype_ `void CalculateStaticShadowDepthMap(FGuid LightGuid);` — Computes a shadow depth map for a stationary light.
- L2234 _private prototype_ `void BeginCalculateVolumeDistanceField();` — Prepares for multithreaded generation of VolumeDistanceField.
- L2237 _private prototype_ `void CalculateVolumeDistanceFieldWorkRange(int32 ZIndex);` — Generates a single z layer of VolumeDistanceField.
- L2247 _private prototype_ `bool CalculatePointShadowing( const FStaticLightingMapping* Mapping, const FVector4f& WorldSurfacePoint, const FLight* Light, FStaticLightingMappingContext& MappingContext, bool bDebugThisSample) const;` — Calculates shadowing for a given mapping surface point and light. @param Mapping - The mapping the point comes from. @param WorldSurfacePoint - The point to check shadowing at. @param Light - The light to check shadowing from. @param CacheGroup - The calling thread's collision cache. @return true if the surface point is shadowed from the light.
- L2255 _private prototype_ `FVector2f CalculatePointAreaShadowing( const FStaticLightingMapping* Mapping, const FStaticLightingVertex& Vertex, int32 ElementIndex, float SampleRadius, const FLight* Light, FStaticLightingMappingContext& MappingContext, FLMRandomStream& RandomStream, FLinearColor& UnnormalizedTransmission, const TArray<FLightSurfaceSample>& LightPositionSamples, bool bDebugThisSample ) const;` — Calculates area shadowing from a light for the given vertex.
- L2269 _private prototype_ `FGatheredLightSample CalculatePointLighting( const FStaticLightingMapping* Mapping, const FStaticLightingVertex& Vertex, int32 ElementIndex, const FLight* Light, const FLinearColor& InLightIntensity, const FLinearColor& InTransmission ) const;` — Calculates the lighting contribution of a light to a mapping vertex.
- L2279 _private prototype_ `FLinearColor EvaluateEnvironmentLighting(const FVector4f& IncomingDirection) const;` — Returns environment lighting for the given direction.
- L2282 _private prototype_ `void EvaluateSkyLighting(const FVector4f& IncomingDirection, float PathSolidAngle, bool bShadowed, bool bForDirectLighting, FLinearColor& OutStaticLighting, FLinearColor& OutStationaryLighting) const;` — Evaluates the incoming sky lighting from the scene.
- L2284 _private prototype_ `float EvaluateSkyVariance(const FVector4f& IncomingDirection, float PathSolidAngle) const;`
- L2287 _private prototype_ `FGatheredLightSample GetVisualizedMaterialAttribute(const FStaticLightingMapping* Mapping, const FLightRayIntersection& Intersection) const;` — Returns a light sample that represents the material attribute specified by MaterialSettings.ViewMaterialAttribute at the intersection.
- L2290 _private prototype_ `FLinearColor CalculateExitantRadiance( const FStaticLightingMapping* HitMapping, const FStaticLightingMesh* HitMesh, const FMinimalStaticLightingVertex& Vertex, int32 ElementIndex, const FVector4f& OutgoingDirection, int32 BounceNumber, EHemisphereGatherClassification GatherClassification, FStaticLightingMappingContext& MappingContext, bool bDebugThisTexel) const;` — Calculates exitant radiance at a vertex.
- L2301 _private prototype_ `void IntersectLightRay( const FStaticLightingMapping* Mapping, const FFullStaticLightingVertex& Vertex, float SampleRadius, const FVector4f& WorldPathDirection, const FVector4f& TangentPathDirection, EFinalGatherRayBiasMode RayBiasMode, FStaticLightingMappingContext& MappingContext, FLightRay& OutLightRay, FLightRayIntersection& OutLightRayIntersection) const;`
- L2313 _private prototype_ `FLinearColor FinalGatherSample( const FStaticLightingMapping* Mapping, const FFullStaticLightingVertex& Vertex, const FVector4f& WorldPathDirection, const FVector4f& TangentPathDirection, const FLightRay& PathRay, const FLightRayIntersection& RayIntersection, float PathSolidAngle, int32 BounceNumber, EHemisphereGatherClassification GatherClassification, bool bGatheringForCachedDirectLighting, bool bDebugThisTexel, FStaticLightingMappingContext& MappingContext, FLMRandomStream& RandomStream, FLightingCacheGatherInfo& GatherInfo, FFinalGatherInfo& FinalGatherInfo, FFinalGatherHitPoint& HitPoint, FVector3f& OutUnoccludedSkyVector, FLinearColor& OutStationarySkyLighting) const;` — Takes a final gather sample in the given tangent space direction.
- L2338 _private prototype_ `template<class SampleType> SampleType IncomingRadianceAdaptive( const FStaticLightingMapping* Mapping, const FFullStaticLightingVertex& Vertex, float SampleRadius, bool bIntersectingSurface, int32 ElementIndex, int32 BounceNumber, EFinalGatherRayBiasMode RayBiasMode, EHemisphereGatherClassification GatherClassification, int32 NumAdaptiveRefinementLevels, float BrightnessThresholdScale, const TArray<FVector4f>& UniformHemisphereSamples, const TArray<FVector2f>& UniformHemisphereSampleUniforms, float MaxUnoccludedLength, const TArray<FVector4f>& ImportancePhotonDirections, FStaticLightingMappingContext& MappingContext, FLMRandomStream& RandomStream, FLightingCacheGatherInfo& GatherInfo, bool bGatheringForCachedDirectLighting, bool bDebugThisTexel) const;` — Final gather using adaptive sampling to estimate the incident radiance function. Adaptive refinement is done on brightness differences and anywhere that a first bounce photon determined lighting was coming from.
- L2360 _private prototype_ `void CalculateIrradianceGradients( int32 BounceNumber, const FLightingCacheGatherInfo& GatherInfo, FVector4f& RotationalGradient, FVector4f& TranslationalGradient) const;` — Calculates irradiance gradients for a sample position that will be cached.
- L2370 _private prototype_ `FFinalGatherSample CachePointIncomingRadiance( const FStaticLightingMapping* Mapping, const FFullStaticLightingVertex& Vertex, int32 ElementIndex, float TexelRadius, float SampleRadius, bool bIntersectingSurface, FStaticLightingMappingContext& MappingContext, FLMRandomStream& RandomStream, bool bDebugThisTexel) const;` — Interpolates incoming radiance from the lighting cache if possible, otherwise estimates incoming radiance for this sample point and adds it to the cache.
- L2385 _private prototype_ `void ProcessTextureMapping(FStaticLightingTextureMapping* TextureMapping);` — Builds lighting for a texture mapping. @param TextureMapping - The mapping to build lighting for.
- L2388 _private prototype_ `void TraceToTexelCorner( const FVector4f& TexelCenterOffset, const FFullStaticLightingVertex& FullVertex, FVector2f CornerSigns, float TexelRadius, FStaticLightingMappingContext& MappingContext, FLightRayIntersection& Intersection, bool& bHitBackface, bool bDebugThisTexel) const;` — Traces a ray to the corner of a texel.
- L2399 _private prototype_ `void SetupTextureMapping( FStaticLightingTextureMapping* TextureMapping, FGatheredLightMapData2D& LightMapData, class FTexelToVertexMap& TexelToVertexMap, class FTexelToCornersMap& TexelToCornersMap, FStaticLightingMappingContext& MappingContext, bool bDebugThisMapping) const;` — Calculates TexelToVertexMap and initializes each texel's light sample as mapped or not.
- L2408 _private prototype_ `void CalculateDirectLightingTextureMappingFiltered( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, TMap<const FLight*, FShadowMapData2D*>& ShadowMaps, const FTexelToVertexMap& TexelToVertexMap, bool bDebugThisMapping, const FLight* Light) const;` — Calculates direct lighting as if all lights were non-area lights, then filters the results in texture space to create approximate soft shadows.
- L2421 _private prototype_ `void CalculateDirectAreaLightingTextureMapping( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, FShadowMapData2D*& ShadowMapData, const FTexelToVertexMap& TexelToVertexMap, bool bDebugThisMapping, const FLight* Light) const;` — Calculate lighting from area lights, no filtering in texture space. Shadow penumbras will be correctly shaped and will be softer for larger light sources and distant shadow casters.
- L2434 _private prototype_ `void CalculateDirectSignedDistanceFieldLightingTextureMappingTextureSpace( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, TMap<const FLight*, FSignedDistanceFieldShadowMapData2D*>& ShadowMaps, const FTexelToVertexMap& TexelToVertexMap, const FTexelToCornersMap& TexelToCornersMap, bool bDebugThisMapping, const FLight* Light) const;` — Calculate signed distance field shadowing from a single light, Based on the paper "Improved Alpha-Tested Magnification for Vector Textures and Special Effects" by Valve.
- L2445 _private prototype_ `void CalculateDirectSignedDistanceFieldLightingTextureMappingLightSpace( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, TMap<const FLight*, FSignedDistanceFieldShadowMapData2D*>& ShadowMaps, const FTexelToVertexMap& TexelToVertexMap, const FTexelToCornersMap& TexelToCornersMap, bool bDebugThisMapping, const FLight* Light) const;` — Experimental method that avoids artifacts due to lightmap seams.
- L2459 _private prototype_ `void CalculateDirectLightingTextureMappingPhotonMap( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, TMap<const FLight*, FShadowMapData2D*>& ShadowMaps, const FTexelToVertexMap& TexelToVertexMap, bool bDebugThisMapping) const;` — Estimate direct lighting using the direct photon map. This is only useful for debugging what the final gather rays see.
- L2471 _private prototype_ `void ProcessCacheIndirectLightingTask(FCacheIndirectTaskDescription* Task, bool bProcessedByMappingThread);` — Builds an irradiance cache for a given mapping task. This can be called from any thread, not just the thread that owns the mapping, so called code must be thread safe in that manner.
- L2477 _private prototype_ `void ProcessInterpolateTask(FInterpolateIndirectTaskDescription* Task, bool bProcessedByMappingThread);` — Interpolates from the irradiance cache for a given mapping task. This can be called from any thread, not just the thread that owns the mapping, so called code must be thread safe in that manner.
- L2479 _private prototype_ `void ProcessVolumeSamplesTask(const FVolumeSamplesTaskDescription& Task);`
- L2482 _private prototype_ `void CalculateIndirectLightingTextureMapping( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, const FTexelToVertexMap& TexelToVertexMap, bool bDebugThisMapping);` — Handles indirect lighting calculations for a single texture mapping.
- L2490 _private prototype_ `void ViewMaterialAttributesTextureMapping( FStaticLightingTextureMapping* TextureMapping, FStaticLightingMappingContext& MappingContext, FGatheredLightMapData2D& LightMapData, const FTexelToVertexMap& TexelToVertexMap, bool bDebugThisMapping) const;` — Overrides LightMapData with material attributes if MaterialSettings.ViewMaterialAttribute != VMA_None
- L2498 _private prototype_ `void ColorInvalidLightmapUVs( const FStaticLightingTextureMapping* TextureMapping, FGatheredLightMapData2D& LightMapData, bool bDebugThisMapping) const;` — Colors texels with invalid lightmap UVs to make it obvious that they are wrong.
- L2504 _private prototype_ `void PadTextureMapping( const FStaticLightingTextureMapping* TextureMapping, const FGatheredLightMapData2D& LightMapData, FGatheredLightMapData2D& PaddedLightMapData, TMap<const FLight*, FShadowMapData2D*>& ShadowMaps, TMap<const FLight*, FSignedDistanceFieldShadowMapData2D*>& SignedDistanceFieldShadowMaps) const;` — Adds a texel of padding around texture mappings and copies the nearest texel into the padding.
- L2517 _private prototype_ `FStaticLightingMapping* ThreadGetNextMapping( FThreadStatistics& ThreadStatistics, FGuid& TaskGuid, uint32 WaitTime, bool& bWaitTimedOut, bool& bDynamicObjectTask, int32& PrecomputedVisibilityTaskIndex, int32& VolumetricLightmapTaskIndex, bool& DominantShadowTask, bool& bMeshAreaLightDataTask, bool& bVolumeDataTask);` — Retrieves the next task from Swarm. Optionally blocking, thread-safe function call. Returns NULL when there are no more tasks. @param WaitTime The timeout period in milliseconds for the request @param bWaitTimedOut Output parameter; true if the request timed out, false if not @return	The next mapping task to process.
- L2535 _private prototype_ `void ThreadLoop(bool bIsMainThread, int32 ThreadIndex, FThreadStatistics& ThreadStatistics, float& IdleTime);` — The processing loop for a static lighting thread. @param bIsMainThread		- true if this is running in the main thread. @param ThreadStatistics	- [out] Various thread statistics
- L2540 _private prototype_ `void MultithreadProcess();` — Creates multiple worker threads and starts the process locally.
- L2543 _private member_ `TArray<FLight*> Lights;` — The lights in the world which the system is building, excluding sky lights.
- L2545 _private member_ `TArray<FSkyLight*> SkyLights;`
- L2548 _private member_ `TIndirectArray<FMeshAreaLight> MeshAreaLights;` — Mesh area lights in the world.
- L2551 _private member_ `const FLightingBuildOptions Options;` — The options the system is building lighting with.
- L2554 _private member_ `FCriticalSection CriticalSection;` — Critical section to synchronize the access to Mappings (used only when GDebugMode is true).
- L2557 _private member_ `FStaticLightingSettings& GeneralSettings;` — References to the scene's settings, for convenience
- L2558 _private member_ `FStaticLightingSceneConstants& SceneConstants;`
- L2559 _private member_ `FSceneMaterialSettings& MaterialSettings;`
- L2560 _private member_ `FMeshAreaLightSettings& MeshAreaLightSettings;`
- L2561 _private member_ `FDynamicObjectSettings& DynamicObjectSettings;`
- L2562 _private member_ `FVolumetricLightmapSettings& VolumetricLightmapSettings;`
- L2563 _private member_ `FPrecomputedVisibilitySettings& PrecomputedVisibilitySettings;`
- L2564 _private member_ `FVolumeDistanceFieldSettings& VolumeDistanceFieldSettings;`
- L2565 _private member_ `FAmbientOcclusionSettings& AmbientOcclusionSettings;`
- L2566 _private member_ `FStaticShadowSettings& ShadowSettings;`
- L2567 _private member_ `FImportanceTracingSettings& ImportanceTracingSettings;`
- L2568 _private member_ `FPhotonMappingSettings& PhotonMappingSettings;`
- L2569 _private member_ `FIrradianceCachingSettings& IrradianceCachingSettings;`
- L2572 _private member_ `mutable FStaticLightingStats Stats;` — Stats of the system
- L2578 _private member_ `volatile int32 TasksInProgressThatWillNeedHelp;` — Counts the number of mapping tasks that have begun, and might need help from other threads with tasks that they generate. This is used to keep completed mapping threads running so they can check for tasks.
- L2582 _private member_ `TLockFreePointerListLIFO<FCacheIndirectTaskDescription> CacheIndirectLightingTasks;` — consider changing this from FIFO to Unordered, which may be faster
- L2586 _private member_ `TLockFreePointerListLIFO<FInterpolateIndirectTaskDescription> InterpolateIndirectLightingTasks;` — consider changing this from FIFO to Unordered, which may be faster
- L2588 _private member_ `TLockFreePointerListLIFO<FVolumetricLightmapBrickTaskDescription> VolumetricLightmapBrickTasks;`
- L2590 _private member_ `TArray<FVolumeSamplesTaskDescription> VolumeSampleTasks;`
- L2592 _private member_ `volatile int32 bHasVolumeSampleTasks;`
- L2593 _private member_ `volatile int32 NextVolumeSampleTaskIndex;`
- L2594 _private member_ `volatile int32 NumVolumeSampleTasksOutstanding;`
- L2595 _private member_ `volatile int32 bShouldExportVolumeSampleData;`
- L2597 _private member_ `FBoxSphereBounds3f VolumeBounds;` — Bounds that VolumeLightingSamples were generated in.
- L2599 _private member_ `FVolumeLightingInterpolationOctree VolumeLightingInterpolationOctree;` — Octree used for interpolating the volume lighting samples if DynamicObjectSettings.bVisualizeVolumeLightInterpolation is true.
- L2601 _private member_ `TMap<FGuid,TArray<FVolumeLightingSample> > VolumeLightingSamples;` — Map from Level Guid to array of volume lighting samples generated.
- L2604 _private member_ `TArray<FPrecomputedVisibilityCell> AllPrecomputedVisibilityCells;` — All precomputed visibility cells in the scene.  Some of these may be processed on other agents.
- L2607 _private member_ `FCriticalSection CompletedStaticShadowDepthMapsSync;` — Threads must acquire this critical section before reading or writing to CompletedStaticShadowDepthMaps.
- L2610 _private member_ `TMap<const FLight*, FStaticShadowDepthMap*> CompletedStaticShadowDepthMaps;` — Static shadow depth maps ready to be exported by the main thread.
- L2613 _private member_ `volatile int32 bShouldExportMeshAreaLightData;` — Non-zero if the mesh area light data task should be exported.
- L2616 _private member_ `volatile int32 bShouldExportVolumeDistanceField;` — Non-zero if the volume distance field task should be exported.
- L2619 _private member_ `int32 NumDirectPhotonsToEmit;` — Number of direct photons to emit
- L2621 _private member_ `int32 NumPhotonsEmittedDirect;` — Number of photons that were emitted until enough direct photons were gathered
- L2623 _private member_ `FPhotonOctree DirectPhotonMap;` — Photon map for direct photons
- L2626 _private member_ `int32 NumIndirectPhotonPaths;` — The target number of indirect photon paths to gather.
- L2628 _private member_ `int32 NumIndirectPhotonsToEmit;` — Number of indirect photons to emit
- L2630 _private member_ `int32 NumPhotonsEmittedFirstBounce;` — Number of photons that were emitted until enough first bounce photons were gathered
- L2635 _private member_ `FPhotonOctree FirstBouncePhotonMap;` — Photon map for first bounce indirect photons. This is separate from other indirect photons so we can access just first bounce photons and use them for guiding the final gather.
- L2638 _private member_ `FPhotonOctree FirstBounceEscapedPhotonMap;` — Tracks first bounce photons that did not intersect a surface and escaped.  Used when lighting volumes.
- L2641 _private member_ `FPhotonSegmentOctree FirstBouncePhotonSegmentMap;` — Stores photon segments, which allows finding photons which travelled near a certain point in space.
- L2644 _private member_ `int32 NumPhotonsEmittedSecondBounce;` — Number of photons that were emitted until enough second bounce photons were gathered
- L2646 _private member_ `FPhotonOctree SecondBouncePhotonMap;` — Photon map for second and up bounce photons.
- L2649 _private member_ `float DirectIrradiancePhotonFraction;` — Fraction of direct photons deposited to calculate irradiance at.
- L2651 _private member_ `float IndirectIrradiancePhotonFraction;` — Fraction of indirect photons deposited to calculate irradiance at.
- L2653 _private member_ `FIrradiancePhotonOctree IrradiancePhotonMap;` — Photon map storing irradiance photons
- L2660 _private member_ `TArray<TArray<FIrradiancePhoton>> mIrradiancePhotons;` — Irradiance photons generated by photon emission. Each array was generated on a separate thread, so these are stored as an array of irradiance photon arrays, Which avoids copying to one large array, since that can take a while due to the large irradiance photon memory size.
- L2663 _private member_ `float MaxRayDistance;` — Maximum distance to trace a ray through the scene.
- L2666 _private member_ `TArray<FVector4f> CachedHemisphereSamples;` — Cached direction samples for hemisphere gathers.
- L2669 _private member_ `float CachedSamplesMaxUnoccludedLength;` — Length of all the hemisphere samples averaged, which is also the max length that a bent normal can be.
- L2671 _private member_ `TArray<FVector2f> CachedHemisphereSampleUniforms;`
- L2673 _private member_ `TArray<FVector4f> CachedHemisphereSamplesForRadiosity[3];`
- L2674 _private member_ `TArray<FVector2f> CachedHemisphereSamplesForRadiosityUniforms[3];`
- L2676 _private member_ `TArray<FVector4f> CachedVolumetricLightmapUniformHemisphereSamples;`
- L2677 _private member_ `TArray<FVector2f> CachedVolumetricLightmapUniformHemisphereSampleUniforms;`
- L2678 _private member_ `float CachedVolumetricLightmapMaxUnoccludedLength;`
- L2679 _private member_ `TArray<FVector3f, TInlineAllocator<1>> CachedVolumetricLightmapVertexOffsets;`
- L2682 _private member_ `FStaticLightingAggregateMeshType* AggregateMesh;` — The aggregate mesh used for raytracing.
- L2684 _private member_ `FDefaultAggregateMesh* VoxelizationSurfaceAggregateMesh;`
- L2685 _private member_ `FDefaultAggregateMesh* VoxelizationVolumeAggregateMesh;`
- L2686 _private member_ `FDefaultAggregateMesh* LandscapeCullingVoxelizationAggregateMesh;`
- L2689 _private member_ `const FScene& Scene;` — The input scene describing geometry, materials and lights.
- L2692 _private member_ `TArray< FStaticLightingMesh* > Meshes;` — All meshes in the system.
- L2695 _private member_ `TArray<FVisibilityMesh> VisibilityMeshes;` — All meshes involved in sPVS indexed by their visibility id, setup at scene setup time.
- L2698 _private member_ `TArray<FVisibilityMeshGroup> VisibilityGroups;` — Visibility groups which are clusters of meshes, generated at PVS startup time.
- L2701 _private member_ `int32 GroupVisibilityGridSizeXY;` — X and Y dimensions of GroupGrid.
- L2704 _private member_ `int32 GroupVisibilityGridSizeZ;` — Z dimension of GroupGrid.
- L2707 _private member_ `FBox3f VisibilityGridBounds;` — World space bounding box of GroupGrid.
- L2710 _private member_ `TArray<int32> GroupGrid;` — Grid of indices into VisibilityGroups.
- L2713 _private member_ `TArray< FStaticLightingMapping* > AllMappings;` — All mappings in the system.
- L2716 _private member_ `TMap< FGuid, FStaticLightingMapping* > Mappings;` — All mappings in the system for which lighting will be built.
- L2719 _private member_ `FThreadSafeCounter NextMappingToProcess;` — The next index into Mappings which processing hasn't started for yet.
- L2722 _private member_ `volatile int32 NumTexelsCompleted;` — Stats on how many texels and vertices have been completed, written and read by all threads.
- L2725 _private member_ `TCompleteStaticLightingList<FTextureMappingStaticLightingData> CompleteTextureMappingList;` — A list of the texture mappings which static lighting has been computed for, but not yet applied.  This is accessed by multiple threads and should be written to using interlocked functions.
- L2728 _private member_ `TCompleteTaskList<FPrecomputedVisibilityData> CompleteVisibilityTaskList;` — List of complete visibility task data.
- L2730 _private member_ `TCompleteTaskList<FVolumetricLightmapTaskData> CompleteVolumetricLightmapTaskList;`
- L2733 _private member_ `TArray< FStaticLightingMapping* > LandscapeMappings;` — Landscape mapping for Lighting Sample number estimation...
- L2735 _private member_ `int32 VolumeSizeX;`
- L2736 _private member_ `int32 VolumeSizeY;`
- L2737 _private member_ `int32 VolumeSizeZ;`
- L2738 _private member_ `FVector4f::FReal DistanceFieldVoxelSize;`
- L2739 _private member_ `FBox3f DistanceFieldVolumeBounds;`
- L2740 _private member_ `TArray<FColor> VolumeDistanceField;`
- L2743 _private member_ `volatile int32 NumOutstandingVolumeDataLayers;`
- L2745 _private member_ `volatile int32 OutstandingVolumeDataLayerIndex;`
- L2748 _private member_ `const int32 NumStaticLightingThreads;` — Number of threads to use for static lighting
- L2751 _private member_ `TIndirectArray<FMappingProcessingThreadRunnable> Threads;` — The threads spawned by the static lighting system for processing mappings.
- L2754 _private member_ `FThreadSafeCounter DirectPhotonEmittingWorkRangeIndex;` — Index of the next entry in DirectPhotonEmittingWorkRanges to process.
- L2755 _private member_ `TArray<FDirectPhotonEmittingWorkRange> DirectPhotonEmittingWorkRanges;`
- L2756 _private member_ `TArray<FDirectPhotonEmittingOutput> DirectPhotonEmittingOutputs;`
- L2759 _private member_ `FThreadSafeCounter IndirectPhotonEmittingWorkRangeIndex;` — Index of the next entry in IndirectPhotonEmittingWorkRanges to process.
- L2760 _private member_ `TArray<FIndirectPhotonEmittingWorkRange> IndirectPhotonEmittingWorkRanges;`
- L2761 _private member_ `TArray<FIndirectPhotonEmittingOutput> IndirectPhotonEmittingOutputs;`
- L2764 _private member_ `FThreadSafeCounter IrradianceMarkWorkRangeIndex;` — Index of the next entry in IrradianceMarkWorkRanges to process.
- L2765 _private member_ `TArray<FIrradianceMarkingWorkRange> IrradianceMarkWorkRanges;`
- L2768 _private member_ `FThreadSafeCounter IrradianceCalcWorkRangeIndex;` — Index of the next entry in IrradianceCalculationWorkRanges to process.
- L2769 _private member_ `TArray<FIrradianceCalculatingWorkRange> IrradianceCalculationWorkRanges;`
- L2772 _private member_ `FThreadSafeCounter NextMappingToCacheIrradiancePhotonsOn;` — Index of the next mapping in AllMappings to cache irradiance photons on
- L2774 _private member_ `int32 DebugIrradiancePhotonCalculationArrayIndex;` — Index into IrradiancePhotons of the array containing the photon being debugged, or INDEX_NONE if no photon is being debugged.
- L2776 _private member_ `int32 DebugIrradiancePhotonCalculationPhotonIndex;` — Index into IrradiancePhotons(DebugIrradiancePhotonCalculationArrayIndex) of the photon being debugged.
- L2778 _private member_ `TIndirectArray<FMappingProcessingThreadRunnable> IrradiancePhotonCachingThreads;`
- L2780 _private member_ `FThreadSafeCounter NextMappingToProcessRadiositySetup;`
- L2781 _private member_ `FThreadSafeCounter NextMappingToProcessRadiosityIterations;`
- L2782 _private member_ `TArray<FThreadSafeCounter> NumCompletedRadiosityIterationMappings;`
- L2784 _private member_ `FThreadSafeCounter NextMappingToFinalizeSurfaceCache;`
- L2786 _private member_ `TIndirectArray<FMappingProcessingThreadRunnable> RadiositySetupThreads;`
- L2787 _private member_ `TIndirectArray<FMappingProcessingThreadRunnable> RadiosityIterationThreads;`
- L2788 _private member_ `TIndirectArray<FMappingProcessingThreadRunnable> FinalizeSurfaceCacheThreads;`
- L2791 _private member_ `class FLightmassSolverExporter& Exporter;` — Lightmass exporter (back to Unreal)

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Lightmass`
- L21 _macro_ `#define ALLOW_STATIC_LIGHTING_STATS 1` — Whether to allow static lighting stats that may affect the system's performance.
- L27 _macro_ `#define LIGHTMASS_DO_PROCESSING 1` — When enabled, makes Lightmass do pretty much no processing at all (NOP). Useful when iterating on import / export
- L30 _macro_ `#define LIGHTINGSTAT(x) x`
- L227 _typedef_ `typedef TOctree<FPhotonElement,struct FPhotonMapOctreeSemantics> FPhotonOctree;` (scope `Lightmass`)
- L233 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonElement& PhotonElement)` (scope `Lightmass::FPhotonMapOctreeSemantics::__anondcdf0c520103`) — @todo - evaluate different performance/memory tradeoffs with these
- L234 _enumerator_ `enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonElement& PhotonElement) {` (scope `Lightmass::FPhotonMapOctreeSemantics::__anondcdf0c520203`)
- L235 _enumerator_ `enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonElement& PhotonElement) { return FBoxCenterAndExtent(PhotonElement.Photon.GetPosition(), FVector4f(0,0,0));` (scope `Lightmass::FPhotonMapOctreeSemantics::__anondcdf0c520303`)
- L283 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonSegmentElement& PhotonSegmentElement) {` (scope `Lightmass::FPhotonSegmentMapOctreeSemantics::__anondcdf0c520403`) — @todo - evaluate different performance/memory tradeoffs with these
- L284 _enumerator_ `enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonSegmentElement& PhotonSegmentElement) { return FBoxCenterAndExtent(PhotonSegmentElement.SegmentCenter, PhotonSegmentElement.SegmentExtent);` (scope `Lightmass::FPhotonSegmentMapOctreeSemantics::__anondcdf0c520503`)
- L285 _enumerator_ `enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FPhotonSegmentElement& PhotonSegmentElement) { return FBoxCenterAndExtent(PhotonSegmentElement.SegmentCenter, PhotonSegmentElement.SegmentExtent); }` (scope `Lightmass::FPhotonSegmentMapOctreeSemantics::__anondcdf0c520603`)
- L295 _typedef_ `typedef TOctree<FPhotonSegmentElement,struct FPhotonSegmentMapOctreeSemantics> FPhotonSegmentOctree;` (scope `Lightmass`)
- L372 _typedef_ `typedef TOctree<FIrradiancePhotonElement,struct FIrradiancePhotonMapOctreeSemantics> FIrradiancePhotonOctree;` (scope `Lightmass`)
- L378 _enumerator_ `enum { MaxElementsPerLeaf = 32 }; enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FIrradiancePhotonElement& PhotonElement) {` (scope `Lightmass::FIrradiancePhotonMapOctreeSemantics::__anondcdf0c520703`) — @todo - evaluate different performance/memory tradeoffs with these
- L379 _enumerator_ `enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FIrradiancePhotonElement& PhotonElement) { return FBoxCenterAndExtent(PhotonElement.GetPhoton().GetPosition(), FVector4f(0,0,0));` (scope `Lightmass::FIrradiancePhotonMapOctreeSemantics::__anondcdf0c520803`)
- L380 _enumerator_ `enum { LoosenessDenominator = 16 }; typedef FDefaultAllocator ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FIrradiancePhotonElement& PhotonElement) { return FBoxCenterAndExtent(PhotonElement.GetPhoton().GetPosition(), FVector4f(0,0,0)); }` (scope `Lightmass::FIrradiancePhotonMapOctreeSemantics::__anondcdf0c520903`)
- L434 _typedef_ `typedef TOctree<FVolumeSampleInterpolationElement,struct FVolumeLightingInterpolationOctreeSemantics> FVolumeLightingInterpolationOctree;` (scope `Lightmass`)
- L440 _enumerator_ `enum { MaxElementsPerLeaf = 4 }; enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FVolumeSampleInterpolationElement& Element) {` (scope `Lightmass::FVolumeLightingInterpolationOctreeSemantics::__anondcdf0c520a03`) — @todo - evaluate different performance/memory tradeoffs with these
- L441 _enumerator_ `enum { MaxNodeDepth = 12 }; enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FVolumeSampleInterpolationElement& Element) { const FVolumeLightingSample& Sample = Element.VolumeSamples[Element.SampleIndex];` (scope `Lightmass::FVolumeLightingInterpolationOctreeSemantics::__anondcdf0c520b03`)
- L442 _enumerator_ `enum { LoosenessDenominator = 16 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; static FBoxCenterAndExtent GetBoundingBox(const FVolumeSampleInterpolationElement& Element) { const FVolumeLightingSample& Sample = Element.VolumeSamples[Element.SampleIndex]; return FBoxCenterAndExtent(FVector4f(Sample.PositionAndRadius, 0.0f), FVector4f(Sample.PositionAndRadius.W, Sample.PositionAndRadius.W, Sample.PositionAndRadius.W));` (scope `Lightmass::FVolumeLightingInterpolationOctreeSemantics::__anondcdf0c520c03`)
- L478 _variable_ `static const int32 NumTrackedBounces = 1;` (scope `Lightmass`) — Number of light bounces that we are keeping track of stats for
- L480 _variable_ `static const int32 MaxNumRefiningDepths = 6;` (scope `Lightmass`)
- L1250 _function_ `friend inline FLightingAndOcclusion operator+ (const FLightingAndOcclusion& A, const FLightingAndOcclusion& B)` (scope `Lightmass`)
- L1255 _function_ `friend inline FLightingAndOcclusion operator/ (const FLightingAndOcclusion& A, float Divisor)` (scope `Lightmass`)
- L2814 _prototype_ `extern bool IsLightBehindSurface(const FVector4f& TrianglePoint, const FVector4f& TriangleNormal, const FLight* Light);` (scope `Lightmass`) — Checks if a light is behind a triangle. @param TrianglePoint - Any point on the triangle. @param TriangleNormal - The (not necessarily normalized) triangle surface normal. @param Light - The light to classify. @return true if the light is behind the triangle.
- L2824 _prototype_ `extern TBitArray<> CullBackfacingLights(bool bTwoSidedMaterial, const FVector4f& TrianglePoint, const FVector4f& TriangleNormal, const TArray<FLight*>& Lights);` (scope `Lightmass`) — Culls lights that are behind a triangle. @param bTwoSidedMaterial - true if the triangle has a two-sided material.  If so, lights behind the surface are not culled. @param TrianglePoint - Any point on the triangle. @param TriangleNormal - The (not necessarily normalized) triangle surface normal. @param Lights - The lights to cull. @return A map from Lights index to a boolean which is true if the light is in front of the triangle.

### `Source/Programs/UnrealLightmass/Private/Lighting/LightingSystem.inl` (Private)


#### Free symbols / members of external scopes

- L4 _function_ `template<int32 SHOrder> TGatheredLightSample<SHOrder> FGatheredLightSampleUtil::AmbientLight(const FLinearColor& Color)` (scope `FGatheredLightSampleUtil`)
- L23 _function_ `template<int32 SHOrder> TGatheredLightSample<SHOrder> FGatheredLightSampleUtil::PointLightWorldSpace(const FLinearColor& Color, const FVector4f& TangentDirection, const FVector4f& WorldDirection)` (scope `FGatheredLightSampleUtil`)
- L46 _function_ `template<int32 SHOrder> void TGatheredLightSample<SHOrder>::AddWeighted(const TGatheredLightSample<SHOrder>& OtherSample, float Weight)` (scope `TGatheredLightSample`)
- L55 _prototype_ `template void TGatheredLightSample<2>::AddWeighted(const TGatheredLightSample<2>& OtherSample, float Weight);` (scope `TGatheredLightSample`)
- L59 _function_ `template<int32 SHOrder> void TGatheredLightSample<SHOrder>::ApplyOcclusion(float Occlusion)` (scope `TGatheredLightSample`)
- L65 _prototype_ `template void TGatheredLightSample<2>::ApplyOcclusion(float Occlusion);` (scope `TGatheredLightSample`)
- L69 _function_ `template<int32 SHOrder> bool TGatheredLightSample<SHOrder>::AreFloatsValid() const` (scope `TGatheredLightSample`)
- L75 _prototype_ `template bool TGatheredLightSample<2>::AreFloatsValid() const;` (scope `TGatheredLightSample`)
- L79 _function_ `template<int32 SHOrder> void TFinalGatherSample<SHOrder>::AddWeighted(const TFinalGatherSample<SHOrder>& OtherSample, float Weight)` (scope `TFinalGatherSample`)
- L87 _function_ `template<int32 SHOrder> bool TFinalGatherSample<SHOrder>::AreFloatsValid() const` (scope `TFinalGatherSample`)
- L93 _function_ `template<int32 SHOrder> void FStaticLightingSystem::CalculateApproximateDirectLighting( const FStaticLightingVertex& Vertex, float SampleRadius, const TArray<FVector3f, TInlineAllocator<1>>& VertexOffsets, float LightSampleFraction, bool bCompositeAllLights, bool bCalculateForIndirectLighting, bool bDebugThisSample, FStaticLightingMappingContext& MappingContext, TGatheredLightSample<SHOrder>& OutStaticDirectLighting, float& OutToggleableDirectionalLightShadowing) const` (scope `FStaticLightingSystem`)

### `Source/Programs/UnrealLightmass/Private/Lighting/LightmapData.h` (Private)


#### class `Lightmass::FLightMapData2D`  
`class FLightMapData2D : public FLightMapData2DData`  
_L14-72_
- inherits: `FLightMapData2DData`
- desc: The raw data which is used to construct a 2D light-map.
- L19 _public member_ `TArray<const FLight*> Lights;` — The lights which this light-map stores.
- L21 _public function_ `FLightMapData2D(uint32 InSizeX,uint32 InSizeY) : FLightMapData2DData(InSizeX, InSizeY) , CompressedData(NULL)`
- L29 _public function_ `~FLightMapData2D()`
- L35 _public function_ `const FLightSample& operator()(uint32 X,uint32 Y) const` — Accessors.
- L36 _public function_ `FLightSample& operator()(uint32 X,uint32 Y)`
- L37 _public function_ `uint32 GetSizeX() const`
- L38 _public function_ `uint32 GetSizeY() const`
- L40 _public function_ `void AddLight(const FLight* NewLight)`
- L48 _public prototype_ `void Quantize(int32 DebugSampleIndex);` — Quantize the full-res FLightSamples into FQuantizedLightSampleDatas
- L50 _public function_ `const FLightSample* GetData()`
- L51 _public function_ `const FQuantizedLightSampleData* GetQuantizedData()`
- L56 _public prototype_ `void Compress(int32 DebugSampleIndex);` — Compresses the raw lightmap data to a buffer for writing over Swarm
- L61 _public function_ `uint8* GetCompressedData()` — @return the compressed data, or NULL if not compressed
- L67 _private member_ `TArray<FLightSample> Data;`
- L68 _private member_ `TArray<FQuantizedLightSampleData> QuantizedData;`
- L71 _private member_ `uint8* CompressedData;` — zlib compressed lightmap data

#### class `Lightmass::FShadowSample`  
`class FShadowSample : public FShadowSampleData`  
_L77-94_
- inherits: `FShadowSampleData`
- desc: A sample of the visibility factor between a light and a single point.
- L80 _public function_ `FShadowSample operator-(const FShadowSample& SampleB) const`
- L87 _public function_ `FShadowSample operator*(const float& Scalar) const`

#### class `Lightmass::FShadowMapData2D`  
`class FShadowMapData2D : public FShadowMapData2DData`  
_L99-133_
- inherits: `FShadowMapData2DData`
- desc: The raw data which is used to construct a 2D light-map.
- L102 _public function_ `FShadowMapData2D(uint32 InSizeX,uint32 InSizeY) : FShadowMapData2DData(InSizeX, InSizeY) , CompressedData(NULL)`
- L110 _public function_ `virtual ~FShadowMapData2D()`
- L113 _public function_ `const FShadowSample& operator()(uint32 X,uint32 Y) const` — Accessors.
- L114 _public function_ `FShadowSample& operator()(uint32 X,uint32 Y)`
- L115 _public function_ `uint32 GetSizeX() const`
- L116 _public function_ `uint32 GetSizeY() const`
- L118 _public prototype_ `void Quantize(int32 DebugSampleIndex);`
- L120 _public function_ `const FShadowSample* GetData()`
- L121 _public function_ `const FQuantizedShadowSampleData* GetQuantizedData()`
- L123 _public prototype_ `void Compress(int32 DebugSampleIndex);`
- L124 _public function_ `uint8* GetCompressedData()`
- L130 _private member_ `TArray<FShadowSample> Data;`
- L131 _private member_ `TArray<FQuantizedShadowSampleData> QuantizedData;`
- L132 _private member_ `uint8* CompressedData;`

#### class `Lightmass::FSignedDistanceFieldShadowSample`  
`class FSignedDistanceFieldShadowSample : public FSignedDistanceFieldShadowSampleData`  
_L135-154_
- inherits: `FSignedDistanceFieldShadowSampleData`
- L138 _public function_ `FSignedDistanceFieldShadowSample operator-(const FSignedDistanceFieldShadowSample& SampleB) const`
- L146 _public function_ `FSignedDistanceFieldShadowSample operator*(const float& Scalar) const`

#### class `Lightmass::FSignedDistanceFieldShadowMapData2D`  
`class FSignedDistanceFieldShadowMapData2D : public FSignedDistanceFieldShadowMapData2DData`  
_L159-193_
- inherits: `FSignedDistanceFieldShadowMapData2DData`
- desc: The raw data which is used to construct a 2D signed distance field shadow map.
- L162 _public function_ `FSignedDistanceFieldShadowMapData2D(uint32 InSizeX,uint32 InSizeY) : FSignedDistanceFieldShadowMapData2DData(InSizeX, InSizeY) , CompressedData(NULL)`
- L170 _public function_ `virtual ~FSignedDistanceFieldShadowMapData2D()`
- L173 _public function_ `const FSignedDistanceFieldShadowSample& operator()(uint32 X,uint32 Y) const` — Accessors.
- L174 _public function_ `FSignedDistanceFieldShadowSample& operator()(uint32 X,uint32 Y)`
- L175 _public function_ `uint32 GetSizeX() const`
- L176 _public function_ `uint32 GetSizeY() const`
- L178 _public prototype_ `void Quantize(int32 DebugSampleIndex);`
- L180 _public function_ `const FSignedDistanceFieldShadowSample* GetData()`
- L181 _public function_ `const FQuantizedSignedDistanceFieldShadowSampleData* GetQuantizedData()`
- L183 _public prototype_ `void Compress(int32 DebugSampleIndex);`
- L184 _public function_ `uint8* GetCompressedData()`
- L190 _private member_ `TArray<FSignedDistanceFieldShadowSample> Data;`
- L191 _private member_ `TArray<FQuantizedSignedDistanceFieldShadowSampleData> QuantizedData;`
- L192 _private member_ `uint8* CompressedData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/Mappings.h` (Private)


#### enum `Lightmass::EHemisphereGatherClassification`  
`enum EHemisphereGatherClassification`  
_L17-25_
- L19 _public enumerator_ `GLM_None = 0`
- L20 _public enumerator_ `GLM_GatherRadiosityBuffer0 = 1`
- L21 _public enumerator_ `GLM_GatherRadiosityBuffer1 = 2`
- L22 _public enumerator_ `GLM_GatherLightEmitted = 4`
- L23 _public enumerator_ `GLM_GatherLightFinalBounced = 8`
- L24 _public enumerator_ `GLM_FinalGather = GLM_GatherLightEmitted | GLM_GatherLightFinalBounced`

#### class `Lightmass::FCompressedGatherHitPoints`  
`class FCompressedGatherHitPoints`  
_L27-46_
- L31 _public function_ `FCompressedGatherHitPoints() : GatherHitPointRangesUncompressedSize(0), GatherHitPointDataUncompressedSize(0)`
- L36 _public member_ `uint32 GatherHitPointRangesUncompressedSize;`
- L37 _public member_ `TArray<uint8> GatherHitPointRanges;`
- L39 _public member_ `uint32 GatherHitPointDataUncompressedSize;`
- L40 _public member_ `TArray<uint8> GatherHitPointData;`
- L42 _public prototype_ `void Compress(const FGatherHitPoints& Source);`
- L43 _public prototype_ `void Decompress(FGatherHitPoints& Dest) const;`
- L45 _public function_ `size_t GetAllocatedSize() const`

#### class `Lightmass::FGatherHitPoints`  
`class FGatherHitPoints`  
_L48-56_
- L52 _public member_ `TArray<FArrayRange> GatherHitPointRanges;`
- L53 _public member_ `TArray<FFinalGatherHitPoint> GatherHitPointData;`
- L55 _public function_ `size_t GetAllocatedSize() const`

#### class `Lightmass::FCompressedInfluencingRecords`  
`class FCompressedInfluencingRecords`  
_L58-77_
- L62 _public function_ `FCompressedInfluencingRecords() : RangesUncompressedSize(0), DataUncompressedSize(0)`
- L67 _public member_ `uint32 RangesUncompressedSize;`
- L68 _public member_ `TArray<uint8> Ranges;`
- L70 _public member_ `uint32 DataUncompressedSize;`
- L71 _public member_ `TArray<uint8> Data;`
- L73 _public prototype_ `void Compress(const FInfluencingRecords& Source);`
- L74 _public prototype_ `void Decompress(FInfluencingRecords& Dest) const;`
- L76 _public function_ `size_t GetAllocatedSize() const`

#### class `Lightmass::FStaticLightingMapping`  
`class FStaticLightingMapping : public virtual FRefCountedObject, public FStaticLightingMappingData`  
_L80-185_
- inherits: `FRefCountedObject,FStaticLightingMappingData`
- desc: A mapping between world-space surfaces and a static lighting cache.
- L85 _public member_ `class FStaticLightingMesh* Mesh;` — The mesh associated with the mapping, guaranteed to be valid (non-NULL) after import.
- L88 _public member_ `volatile int32 bProcessed;` — Whether the mapping has been processed.
- L91 _public member_ `bool bPadded;` — If true, the mapping is being padded
- L94 _public member_ `static bool s_bShowLightmapBorders;` — A static indicating that debug borders should be used around padded mappings.
- L97 _public member_ `int32 SceneMappingIndex;` — Index of this mapping in FStaticLightingSystem::AllMappings
- L105 _protected member_ `TArray<FLinearColor> SurfaceCacheLighting;` — Approximate lighting cached on this mapping, used by final gather rays.
- L107 _protected member_ `TArray<FLinearColor> RadiositySurfaceCache[2];`
- L110 _protected member_ `FCompressedInfluencingRecords CompressedInfluencingRecords;` — Indexed by texel coordinate
- L111 _protected member_ `FInfluencingRecords InfluencingRecordsSurfaceCache;`
- L113 _protected member_ `FCompressedGatherHitPoints CompressedGatherHitPoints;`
- L114 _protected member_ `FGatherHitPoints UncompressedGatherHitPoints;`
- L119 _public function_ `FStaticLightingMapping() : bProcessed(false) , bPadded(false) , SceneMappingIndex(-1)` — Initialization constructor.
- L127 _public function_ `virtual ~FStaticLightingMapping()` — Virtual destructor.
- L132 _public function_ `virtual class FStaticLightingTextureMapping* GetTextureMapping()` — @return If the mapping is a texture mapping, returns a pointer to this mapping as a texture mapping.  Otherwise, returns NULL.
- L137 _public function_ `virtual const FStaticLightingTextureMapping* GetTextureMapping() const`
- L142 _public function_ `virtual class FStaticLightingGlobalVolumeMapping* GetVolumeMapping()`
- L147 _public function_ `virtual const FStaticLightingGlobalVolumeMapping* GetVolumeMapping() const`
- L152 _public function_ `virtual const class FLandscapeStaticLightingGlobalVolumeMapping* GetLandscapeVolumeMapping()`
- L157 _public function_ `virtual const class FLandscapeStaticLightingGlobalVolumeMapping* GetLandscapeVolumeMapping() const`
- L167 _public function_ `virtual float GetProcessingCost() const` — Returns the relative processing cost used to sort tasks from slowest to fastest. @return	relative processing cost or 0 if unknown
- L172 _public prototype_ `virtual FLinearColor GetSurfaceCacheLighting(const FMinimalStaticLightingVertex& Vertex) const = 0;`
- L174 _public prototype_ `virtual int32 GetSurfaceCacheIndex(const struct FMinimalStaticLightingVertex& Vertex) const = 0;`
- L175 _public prototype_ `FLinearColor GetCachedRadiosity(int32 RadiosityBufferIndex, int32 SurfaceCacheIndex) const;`
- L176 _public prototype_ `size_t FreeRadiosityTemporaries();`
- L178 _public function_ `uint32 GetIrradiancePhotonCacheBytes() const`
- L180 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L182 _public prototype_ `virtual void Initialize(FStaticLightingSystem& System) = 0;`

#### class `Lightmass::FStaticLightingTextureMapping`  
`class FStaticLightingTextureMapping : public FStaticLightingMapping, public FStaticLightingTextureMappingData`  
_L188-245_
- inherits: `FStaticLightingMapping,FStaticLightingTextureMappingData`
- desc: A mapping between world-space surfaces and static lighting cache textures.
- L192 _public function_ `FStaticLightingTextureMapping() : NumOutstandingCacheTasks(0), NumOutstandingInterpolationTasks(0)`
- L198 _public function_ `virtual FStaticLightingTextureMapping* GetTextureMapping() override` — FStaticLightingMapping interface.
- L203 _public function_ `virtual const FStaticLightingTextureMapping* GetTextureMapping() const override`
- L213 _public function_ `virtual float GetProcessingCost() const` — Returns the relative processing cost used to sort tasks from slowest to fastest. @return	relative processing cost or 0 if unknown
- L218 _public prototype_ `virtual FLinearColor GetSurfaceCacheLighting(const FMinimalStaticLightingVertex& Vertex) const override;`
- L220 _public prototype_ `virtual int32 GetSurfaceCacheIndex(const struct FMinimalStaticLightingVertex& Vertex) const;`
- L222 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L224 _public prototype_ `virtual void Initialize(FStaticLightingSystem& System);`
- L227 _public member_ `int32 CachedSizeX;` — The padded size of the mapping
- L228 _public member_ `int32 CachedSizeY;`
- L231 _public member_ `int32 SurfaceCacheSizeX;` — The sizes that CachedIrradiancePhotons were stored with
- L232 _public member_ `int32 SurfaceCacheSizeY;`
- L235 _public member_ `volatile int32 NumOutstandingCacheTasks;` — Counts how many cache tasks this mapping needs completed.
- L238 _public member_ `TLockFreePointerListLIFO<FCacheIndirectTaskDescription> CompletedCacheIndirectLightingTasks;` — List of completed cache tasks for this mapping.
- L241 _public member_ `volatile int32 NumOutstandingInterpolationTasks;` — Counts how many interpolation tasks this mapping needs completed.
- L244 _public member_ `TLockFreePointerListLIFO<FInterpolateIndirectTaskDescription> CompletedInterpolationTasks;` — List of completed interpolation tasks for this mapping.

#### class `Lightmass::FStaticLightingGlobalVolumeMapping`  
`class FStaticLightingGlobalVolumeMapping : public FStaticLightingTextureMapping`  
_L251-267_
- inherits: `FStaticLightingTextureMapping`
- desc: A mapping that represents an object which is going to use the global volumetric lightmap. Hack: currently represented as a texture lightmap to Lightmass for the purposes of surface caching of light (radiosity + direct lighting).
- L255 _public function_ `FStaticLightingGlobalVolumeMapping()`
- L258 _public function_ `virtual class FStaticLightingGlobalVolumeMapping* GetVolumeMapping() override`
- L263 _public function_ `virtual const FStaticLightingGlobalVolumeMapping* GetVolumeMapping() const override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/MonteCarlo.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Lightmass`
- L11 _prototype_ `void GenerateCoordinateSystem(const FVector4f& ZAxis, FVector4f& XAxis, FVector4f& YAxis);` (scope `Lightmass`) — Generates valid X and Y axes of a coordinate system, given the Z axis.
- L14 _prototype_ `FVector4f GetUnitVector(FLMRandomStream& RandomStream);` (scope `Lightmass`) — Generates a pseudo-random unit vector, uniformly distributed over all directions.
- L17 _prototype_ `FVector4f GetUnitPosition(FLMRandomStream& RandomStream);` (scope `Lightmass`) — Generates a pseudo-random position inside the unit sphere, uniformly distributed over the volume of the sphere.
- L23 _prototype_ `FVector4f GetUniformHemisphereVector(FLMRandomStream& RandomStream, float MaxTheta = (float)HALF_PI);` (scope `Lightmass`) — Generates a pseudo-random unit vector in the Z > 0 hemisphere whose PDF == 1 / (2 * PI) in solid angles, Or sin(theta) / (2 * PI) in hemispherical coordinates, which is a uniform distribution over the area of the hemisphere.
- L29 _prototype_ `FVector4f GetCosineHemisphereVector(FLMRandomStream& RandomStream, float MaxTheta = (float)HALF_PI);` (scope `Lightmass`) — Generates a pseudo-random unit vector in the Z > 0 hemisphere whose PDF == cos(theta) / PI in solid angles, Which is sin(theta)cos(theta) / PI in hemispherical coordinates.
- L36 _prototype_ `FVector4f GetModifiedPhongSpecularVector(FLMRandomStream& RandomStream, const FVector4f& TangentSpecularDirection, float SpecularPower);` (scope `Lightmass`) — Generates a pseudo-random unit vector in the Z > 0 hemisphere, Whose PDF == (SpecularPower + 1) / (2.0f * PI) * cos(Alpha) ^ SpecularPower in solid angles, Where Alpha is the angle between the perfect specular direction and the outgoing direction.
- L42 _prototype_ `FVector2f GetUniformUnitDiskPosition(FLMRandomStream& RandomStream);` (scope `Lightmass`) — Generates a pseudo-random position within a unit disk, Whose PDF == 1 / PI, which is a uniform distribution over the area of the disk.
- L48 _prototype_ `FVector4f UniformSampleCone(FLMRandomStream& RandomStream, float CosMaxConeTheta, const FVector4f& XAxis, const FVector4f& YAxis, const FVector4f& ZAxis);` (scope `Lightmass`) — Generates a pseudo-random direction within a cone, Whose PDF == 1 / (2 * PI * (1 - CosMaxConeTheta)), which is a uniform distribution over the directions in the cone.
- L50 _prototype_ `FVector4f UniformSampleCone(float CosMaxConeTheta, const FVector4f& XAxis, const FVector4f& YAxis, const FVector4f& ZAxis, float Uniform1, float Uniform2);` (scope `Lightmass`)
- L53 _prototype_ `float UniformConePDF(float CosMaxConeTheta);` (scope `Lightmass`) — Calculates the PDF for a sample generated by UniformSampleCone
- L55 _prototype_ `FVector4f UniformSampleHemisphere(float Uniform1, float Uniform2);` (scope `Lightmass`)
- L58 _prototype_ `void GenerateStratifiedUniformHemisphereSamples(int32 NumThetaSteps, int32 NumPhiSteps, FLMRandomStream& RandomStream, TArray<FVector4f>& Samples, TArray<FVector2f>& Uniforms);` (scope `Lightmass`) — Generates unit length, stratified and uniformly distributed direction samples in a hemisphere.
- L60 _prototype_ `void GenerateStratifiedCosineHemisphereSamples(int32 NumThetaSteps, int32 NumPhiSteps, FLMRandomStream& RandomStream, TArray<FVector4f>& Samples);` (scope `Lightmass`)
- L66 _prototype_ `float PowerHeuristic(int32 NumF, float fPDF, int32 NumG, float gPDF);` (scope `Lightmass`) — Multiple importance sampling power heuristic of two functions with a power of two. From Veach's PHD thesis titled "Robust Monte Carlo Methods for Light Transport Simulation", page 273.
- L69 _prototype_ `void CalculateStep1dCDF(const TArray<float>& PDF, TArray<float>& CDF, float& UnnormalizedIntegral);` (scope `Lightmass`) — Calculates the step 1D cumulative distribution function for the given unnormalized probability distribution function.
- L72 _prototype_ `void Sample1dCDF(const TArray<float>& PDFArray, const TArray<float>& CDFArray, float UnnormalizedIntegral, FLMRandomStream& RandomStream, float& PDF, float& Sample);` (scope `Lightmass`) — Generates a Sample from the given step 1D probability distribution function.

### `Source/Programs/UnrealLightmass/Private/Lighting/Raster.h` (Private)


#### class `Lightmass::FTriangleRasterizer`  
`template<class RasterPolicyType> class FTriangleRasterizer : public RasterPolicyType`  
_L20-141_
- inherits: `RasterPolicyType`
- L24 _public typedef_ `typedef typename RasterPolicyType::InterpolantType InterpolantType;`
- L26 _public function_ `void DrawTriangle(const InterpolantType& I0,const InterpolantType& I1,const InterpolantType& I2,const FVector2f& P0,const FVector2f& P1,const FVector2f& P2,bool BackFacing)`
- L93 _public function_ `FTriangleRasterizer(const RasterPolicyType& InRasterPolicy): RasterPolicyType(InRasterPolicy)`
- L97 _private function_ `void DrawTriangleTrapezoid( const InterpolantType& TopMinInterpolant, const InterpolantType& DeltaMinInterpolant, const InterpolantType& TopMaxInterpolant, const InterpolantType& DeltaMaxInterpolant, float TopMinX, float DeltaMinX, float TopMaxX, float DeltaMaxX, float MinY, float MaxY, bool BackFacing )`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/StaticMesh.h` (Private)


#### class `Lightmass::FStaticMeshStaticLightingMesh`  
`class FStaticMeshStaticLightingMesh : public FStaticLightingMesh, public FStaticMeshStaticLightingMeshData`  
_L13-77_
- inherits: `FStaticLightingMesh,FStaticMeshStaticLightingMeshData`
- desc: Represents the triangles of one LOD of a static mesh primitive to the static lighting system.
- L18 _public member_ `FStaticMesh* StaticMesh;` — The static mesh this mesh represents.
- L20 _public member_ `FStaticLightingMapping* Mapping;`
- L23 _public member_ `FMatrix44f WorldToLocal;` — World to local transform, for box intersection w/ instances.
- L25 _public function_ `virtual FStaticMeshStaticLightingMesh* GetInstanceableStaticMesh() override`
- L27 _public function_ `virtual const FStaticMeshStaticLightingMesh* GetInstanceableStaticMesh() const override`
- L35 _public function_ `virtual FGuid GetObjectGuid() const` — Returns the Guid for the object associated with this lighting mesh. Ie, for a StaticMeshStaticLightingMesh, it would return the Guid of the source static mesh. The GetObjectType function should also be used to determine the TypeId of the source object.
- L47 _public function_ `virtual ESourceObjectType GetObjectType() const` — Returns the SourceObject type id.
- L52 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const;`
- L53 _public prototype_ `virtual void GetNonTransformedTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2,int32& ElementIndex) const;`
- L54 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L55 _public prototype_ `virtual void GetNonTransformedTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L57 _public prototype_ `virtual bool IsElementCastingShadow(int32 ElementIndex) const;`
- L59 _public function_ `virtual uint32 GetLODIndices() const`
- L60 _public function_ `virtual uint32 GetHLODRange() const`
- L67 _public function_ `virtual uint32 GetMeshLODIndex() const` — @return the portion of the LOD index variable that is actually the mesh LOD level It strips off the MassiveLOD portion, which is in the high bytes. The MassiveLOD portion is needed for disallowing shadow casting between parents/children
- L68 _public function_ `virtual uint32 GetMeshHLODIndex() const`
- L70 _public function_ `virtual uint32 GetMeshHLODRangeStart() const`
- L71 _public function_ `virtual uint32 GetMeshHLODRangeEnd() const`
- L73 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L76 _public member_ `FMatrix44f LocalToWorldInverseTranspose;` — The inverse transpose of the primitive's local to world transform.

#### class `Lightmass::FStaticMeshStaticLightingTextureMapping`  
`class FStaticMeshStaticLightingTextureMapping : public FStaticLightingTextureMapping`  
_L80-90_
- inherits: `FStaticLightingTextureMapping`
- desc: Represents a static mesh primitive with texture mapped static lighting.
- L84 _public prototype_ `virtual void Import( class FLightmassImporter& Importer );`
- L89 _private member_ `int32 LODIndex;` — The LOD this mapping represents.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/Texture.h` (Private)


#### enum `Lightmass::ETexture2DFormats`  
`enum ETexture2DFormats`  
_L10-15_
- desc: Texture formats used by FTexture2D
- L12 _public enumerator_ `TF_UNKNOWN`
- L13 _public enumerator_ `TF_ARGB8`
- L14 _public enumerator_ `TF_ARGB16F`

#### class `Lightmass::FTexture2D`  
`class FTexture2D`  
_L18-129_
- desc: A 2D texture
- L22 _protected member_ `int32 SizeX;` — Texture dimensions
- L23 _protected member_ `int32 SizeY;`
- L25 _protected member_ `ETexture2DFormats Format;` — Format of texture which indicates how to interpret Data
- L27 _protected member_ `int32 ElementSize;` — The size of each element in the data array
- L29 _protected member_ `uint8* Data;` — Mip 0 texture data
- L32 _public function_ `FTexture2D() : SizeX(0) , SizeY(0) , Format(TF_UNKNOWN) , ElementSize(0) , Data(NULL)`
- L41 _public function_ `FTexture2D(ETexture2DFormats InFormat, int32 InSizeX, int32 InSizeY) : SizeX(InSizeX) , SizeY(InSizeY) , Format(InFormat) , ElementSize(0) , Data(NULL)`
- L51 _public function_ `virtual ~FTexture2D()`
- L57 _public function_ `int32 GetSizeX() const` — Accessors
- L58 _public function_ `int32 GetSizeY() const`
- L59 _public function_ `uint8* GetData()`
- L61 _public function_ `void Init(ETexture2DFormats InFormat, int32 InSizeX, int32 InSizeY)`
- L81 _public function_ `inline uint8* SampleRawPtr(const FVector2f& UV) const`
- L102 _public function_ `inline FLinearColor Sample(const FVector2f& UV) const`
- L118 _public function_ `inline FVector4f SampleNormal(const FVector2f& UV) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/Lighting/TextureMappingSetup.h` (Private)


#### struct `Lightmass::FTexelToVertex`  
`struct FTexelToVertex`  
_L14-65_
- desc: A map from a texel to the world-space surface point which maps the texel.
- L16 _public member_ `FVector4f WorldPosition;`
- L17 _public member_ `FVector4f WorldTangentX;`
- L18 _public member_ `FVector4f WorldTangentY;`
- L19 _public member_ `FVector4f WorldTangentZ;`
- L20 _public member_ `FVector4f TriangleNormal;`
- L23 _public member_ `float TotalSampleWeight;` — Weight used when combining super sampled attributes and determining if the texel has been mapped.
- L26 _public member_ `float MaxSampleWeight;` — Tracks the max sample weight encountered.
- L29 _public member_ `float TexelRadius;` — World space radius of the texel.
- L32 _public member_ `float SampleRadius;` — Final gathering sample radius, derived from texel radius by adjustment
- L35 _public member_ `uint32 bIntersectingSurface : 1;` — Whether this texel was determined to be intersecting another surface.
- L37 _public member_ `uint16 ElementIndex;`
- L40 _public member_ `FVector2f TextureCoordinates[MAX_TEXCOORDS];` — Texture coordinates
- L43 _public function_ `inline FStaticLightingVertex GetVertex() const` — Create a static lighting vertex to represent the texel.
- L57 _public function_ `inline FFullStaticLightingVertex GetFullVertex() const`

#### class `Lightmass::FTexelToVertexMap`  
`class FTexelToVertexMap`  
_L68-107_
- desc: A map from light-map texels to the world-space surface points which map the texels.
- L73 _public function_ `FTexelToVertexMap(int32 InSizeX,int32 InSizeY): SizeX(InSizeX), SizeY(InSizeY)` — Initialization constructor.
- L82 _public function_ `FTexelToVertex& operator()(int32 X,int32 Y)` — Accessors.
- L87 _public function_ `const FTexelToVertex& operator()(int32 X,int32 Y) const`
- L93 _public function_ `int32 GetSizeX() const`
- L94 _public function_ `int32 GetSizeY() const`
- L95 _public function_ `SIZE_T GetAllocatedSize() const`
- L100 _private member_ `TArray<FTexelToVertex> Data;` — The mapping data.
- L103 _private member_ `int32 SizeX;` — The width of the mapping data.
- L106 _private member_ `int32 SizeY;` — The height of the mapping data.

#### struct `Lightmass::FStaticLightingInterpolant`  
`struct FStaticLightingInterpolant`  
_L109-153_
- L111 _public member_ `FStaticLightingVertex Vertex;`
- L112 _public member_ `uint16 ElementIndex;`
- L114 _public function_ `FStaticLightingInterpolant()`
- L116 _public function_ `FStaticLightingInterpolant(const FStaticLightingVertex& InVertex, uint16 InElementIndex) : Vertex(InVertex), ElementIndex(InElementIndex)`

#### class `Lightmass::FStaticLightingRasterPolicy`  
`class FStaticLightingRasterPolicy`  
_L156-202_
- desc: Used to map static lighting texels to vertices.
- L160 _public typedef_ `typedef FStaticLightingInterpolant InterpolantType;`
- L163 _public function_ `FStaticLightingRasterPolicy( const FScene& InScene, FTexelToVertexMap& InTexelToVertexMap, float InSampleWeight, const FVector4f& InTriangleNormal, bool bInDebugThisMapping, bool bInUseMaxWeight ) : Scene(InScene), TexelToVertexMap(InTexelToVertexMap), SampleWeight(InSampleWeight), TriangleNormal(InTriangleNormal), bDebugThisMapping(bInDebugThisMapping), bUseMaxWeight(bInUseMaxWeight)` — Initialization constructor.
- L183 _protected function_ `int32 GetMinX() const`
- L184 _protected function_ `int32 GetMaxX() const`
- L185 _protected function_ `int32 GetMinY() const`
- L186 _protected function_ `int32 GetMaxY() const`
- L188 _protected prototype_ `void ProcessPixel(int32 X,int32 Y,const InterpolantType& Interpolant,bool BackFacing);`
- L192 _private member_ `const FScene& Scene;`
- L195 _private member_ `FTexelToVertexMap& TexelToVertexMap;` — The texel to vertex map which is being rasterized to.
- L198 _private member_ `const float SampleWeight;` — The weight of the current sample.
- L199 _private member_ `const FVector4f TriangleNormal;`
- L200 _private member_ `const bool bDebugThisMapping;`
- L201 _private member_ `const bool bUseMaxWeight;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Lightmass`
- L122 _function_ `friend FStaticLightingInterpolant operator+(const FStaticLightingInterpolant& A,const FStaticLightingInterpolant& B)` (scope `Lightmass`) — Operators used for linear combinations of static lighting interpolants.
- L130 _function_ `friend FStaticLightingInterpolant operator-(const FStaticLightingInterpolant& A,const FStaticLightingInterpolant& B)` (scope `Lightmass`)
- L138 _function_ `friend FStaticLightingInterpolant operator*(const FStaticLightingInterpolant& A,float B)` (scope `Lightmass`)
- L146 _function_ `friend FStaticLightingInterpolant operator/(const FStaticLightingInterpolant& A,float B)` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/LightmassCore/LMCore.h` (Private)
_(no declarations extracted)_

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Math/LMCollision.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`
- L10 _function_ `static bool ClipLineWithBox(const FBox3f& Box, const FVector4f& Start, const FVector4f& End, FVector4f& IntersectedStart, FVector4f& IntersectedEnd)` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Math/LMMath.h` (Private)


#### union `Lightmass::W128_T`  
`union W128_T`  
_L55-58_
- desc: 128-bit data structure
- L56 _public member_ `__m128i si;`
- L57 _public member_ `uint32_t u[4];`

#### struct `Lightmass::W128_T`  
`struct W128_T`  
_L65-67_
- desc: 128-bit data structure
- L56 _public member_ `__m128i si;`
- L57 _public member_ `uint32_t u[4];`

#### class `Lightmass::FLMRandomStream`  
`class FLMRandomStream`  
_L85-244_
- desc: Thread-safe Random Number Generator which wraps the SIMD-oriented Fast Mersenne Twister (SFMT).
- L89 _public function_ `FLMRandomStream(int32 InSeed) : initialized(0)`
- L101 _public function_ `inline float GetFraction()` — Generates a uniformly distributed pseudo-random float in the range [0,1). This is implemented with the Mersenne Twister and has excellent precision and distribution properties
- L146 _private member_ `w128_t sfmt[N];` — the 128-bit internal state array
- L148 _private member_ `uint32_t *psfmt32;` — the 32bit integer pointer to the 128-bit internal state array
- L151 _private member_ `uint64_t *psfmt64;` — the 64bit integer pointer to the 128-bit internal state array
- L154 _private member_ `int idx;` — index counter to the 32-bit internal state array
- L157 _private member_ `int initialized;` — a flag: it is 0 if and only if the internal state is not yet initialized.
- L159 _private prototype_ `uint32_t gen_rand32(void);`
- L160 _private prototype_ `uint64_t gen_rand64(void);`
- L161 _private prototype_ `void fill_array32(uint32_t *array, int size);`
- L162 _private prototype_ `void fill_array64(uint64_t *array, int size);`
- L163 _private prototype_ `void init_gen_rand(uint32_t seed);`
- L164 _private prototype_ `void init_by_array(uint32_t *init_key, int key_length);`
- L165 _private prototype_ `const char * get_idstring(void);`
- L166 _private prototype_ `int get_min_array_size32(void);`
- L167 _private prototype_ `int get_min_array_size64(void);`
- L168 _private prototype_ `void gen_rand_all(void);`
- L169 _private prototype_ `void gen_rand_array(w128_t *array, int size);`
- L170 _private prototype_ `void period_certification(void);`
- L174 _private function_ `inline double to_real1(uint32_t v)` — generates a random number on [0,1]-real-interval
- L181 _private function_ `inline double genrand_real1(void)` — generates a random number on [0,1]-real-interval
- L187 _private function_ `inline double to_real2(uint32_t v)` — generates a random number on [0,1)-real-interval
- L194 _private function_ `inline double genrand_real2(void)` — generates a random number on [0,1)-real-interval
- L200 _private function_ `inline double to_real3(uint32_t v)` — generates a random number on (0,1)-real-interval
- L207 _private function_ `inline double genrand_real3(void)` — generates a random number on (0,1)-real-interval
- L214 _private function_ `inline double to_res53(uint64_t v)` — generates a random number on [0,1) with 53-bit resolution
- L221 _private function_ `inline double to_res53_mix(uint32_t x, uint32_t y)` — generates a random number on [0,1) with 53-bit resolution from two 32 bit integers
- L228 _private function_ `inline double genrand_res53(void)` — generates a random number on [0,1) with 53-bit resolution
- L236 _private function_ `inline double genrand_res53_mix(void)` — generates a random number on [0,1) with 53-bit resolution using 32bit integer.

#### class `Lightmass::FFloat32`  
`class FFloat32`  
_L252-271_
- desc: 32 bit float components
- L268 _public function_ `FFloat32( float InValue=0.0f ) : FloatValue(InValue)`

#### union `Lightmass::FFloat32::(anonymous)`  
``  
_L256-266_

#### struct `Lightmass::FFloat32::__anond3308632010a::(anonymous)`  
``  
_L258-263_

#### class `Lightmass::FFloat16`  
`class FFloat16`  
_L290-401_
- desc: 16 bit float components and conversion IEEE float 16 Represented by 10-bit mantissa M, 5-bit exponent E, and 1-bit sign S Specials: E=0, M=0		== 0.0 E=0, M!=0		== Denormalized value (M / 2^10) * 2^-14 0<E<31, M=any	== (1 + M / 2^10) * 2^(E-15) E=31, M=0		== Infinity E=31, M!=0		== NAN
- L307 _public function_ `FFloat16( ) : Encoded(0)` — Default constructor
- L313 _public function_ `FFloat16( const FFloat16& FP16Value )` — Copy constructor.
- L319 _public function_ `FFloat16( float FP32Value )` — Conversion constructor. Convert from Fp32 to Fp16.
- L325 _public function_ `FFloat16& operator=( float FP32Value )` — Assignment operator. Convert from Fp32 to Fp16.
- L332 _public function_ `FFloat16& operator=( const FFloat16& FP16Value )` — Assignment operator. Copy Fp16 value.
- L339 _public function_ `operator float() const` — Convert from Fp16 to Fp32.
- L345 _public function_ `void Set( float FP32Value )` — Convert from Fp32 to Fp16.
- L375 _public function_ `FORCEINLINE float GetFloat() const` — Convert from Fp16 to Fp32.

#### union `Lightmass::FFloat16::(anonymous)`  
``  
_L294-304_

#### struct `Lightmass::FFloat16::__anond3308632030a::(anonymous)`  
``  
_L296-301_

#### struct `Lightmass::FLinearColorUtils`  
`struct FLinearColorUtils`  
_L403-440_
- L406 _public prototype_ `static FLinearColor LinearRGBToXYZ(const FLinearColor& InColor);` — Converts a linear space RGB color to linear space XYZ.
- L409 _public prototype_ `static FLinearColor XYZToLinearRGB(const FLinearColor& InColor);` — Converts a linear space XYZ color to linear space RGB.
- L412 _public prototype_ `static FLinearColor XYZToxyzY(const FLinearColor& InColor);` — Converts an XYZ color to xyzY, where xy and z are chrominance measures and Y is the brightness.
- L415 _public prototype_ `static FLinearColor xyzYToXYZ(const FLinearColor& InColor);` — Converts an xyzY color to XYZ.
- L418 _public prototype_ `static FLinearColor LinearRGBToHSV(const FLinearColor& InColor);` — Converts a linear space RGB color to an HSV color
- L421 _public prototype_ `static FLinearColor HSVToLinearRGB(const FLinearColor& InColor);` — Converts an HSV color to a linear space RGB color
- L432 _public prototype_ `static FLinearColor AdjustSaturation(const FLinearColor& InColor, float SaturationFactor);` — Returns a color with adjusted saturation levels, with valid input from 0.0 to 2.0 0.0 produces a fully desaturated color 1.0 produces no change to the saturation 2.0 produces a fully saturated color @param	SaturationFactor	Saturation factor in range [0..2] @return	Desaturated color
- L434 _public function_ `static bool AreFloatsValid(const FLinearColor& InColor)`

#### struct `Lightmass::FVectorUtils`  
`struct FVectorUtils`  
_L442-449_
- L445 _public function_ `FORCEINLINE static float PlaneDot( const FVector4f &V, const FVector4f &P )` — @return >0: point is in front of the plane, <0: behind, =0: on the plane

#### Free symbols / members of external scopes

- L7 _macro_ `#define USE_SSE2_FOR_MERSENNE_TWISTER 1`
- L12 _namespace_ `namespace Lightmass`
- L18 _prototype_ `bool GetBarycentricWeights( const FVector4f& Position0, const FVector4f& Position1, const FVector4f& Position2, const FVector4f& InterpolatePosition, float Tolerance, FVector4f& BarycentricWeights );` (scope `Lightmass`)
- L29 _typedef_ `typedef unsigned int uint32_t;` (scope `Lightmass`) — Types used by SFMT
- L31 _typedef_ `typedef unsigned __int64 uint64_t;` (scope `Lightmass`)
- L37 _variable_ `static const uint64_t MEXP = 19937;` (scope `Lightmass`) — Mersenne Exponent. The period of the sequence is a multiple of 2^MEXP-1. #define MEXP 19937
- L40 _variable_ `static const uint64_t N = (MEXP / 128 + 1);` (scope `Lightmass`) — SFMT generator has an internal state array of 128-bit integers, and N is its size.
- L43 _variable_ `static const uint64_t N32 = (N * 4);` (scope `Lightmass`) — N32 is the size of internal state array when regarded as an array of 32-bit integers.
- L46 _variable_ `static const uint64_t N64 = (N * 2);` (scope `Lightmass`) — N64 is the size of internal state array when regarded as an array of 64-bit integers.
- L60 _typedef_ `typedef union W128_T w128_t;` (scope `Lightmass`) — 128-bit data type
- L69 _typedef_ `typedef struct W128_T w128_t;` (scope `Lightmass`) — 128-bit data type
- L74 _variable_ `static const int32 appTruncErrorCode = 0x80000000;` (scope `Lightmass`) — Value returned by appTrunc if the converted result is larger than the maximum signed 32bit integer.
- L79 _function_ `inline int32 appTrunc( float F )` (scope `Lightmass`) — Converts float to int via truncation.
- L260 _member_ `uint32 Mantissa : 23;` (scope `Lightmass::FFloat32::__anond3308632010a::__anond33086320208`) — __INTEL_BYTE_ORDER__
- L261 _member_ `uint32 Exponent : 8;` (scope `Lightmass::FFloat32::__anond3308632010a::__anond33086320208`)
- L262 _member_ `uint32 Sign : 1;` (scope `Lightmass::FFloat32::__anond3308632010a::__anond33086320208`)
- L263 _member_ `} Components;` (scope `Lightmass::FFloat32::__anond3308632010a`)
- L265 _member_ `float FloatValue;` (scope `Lightmass::FFloat32::__anond3308632010a`)
- L298 _member_ `uint16 Mantissa : 10;` (scope `Lightmass::FFloat16::__anond3308632030a::__anond33086320408`) — __INTEL_BYTE_ORDER__
- L299 _member_ `uint16 Exponent : 5;` (scope `Lightmass::FFloat16::__anond3308632030a::__anond33086320408`)
- L300 _member_ `uint16 Sign : 1;` (scope `Lightmass::FFloat16::__anond3308632030a::__anond33086320408`)
- L301 _member_ `} Components;` (scope `Lightmass::FFloat16::__anond3308632030a`)
- L303 _member_ `uint16 Encoded;` (scope `Lightmass::FFloat16::__anond3308632030a`)
- L461 _function_ `FORCEINLINE uint32 appCountTrailingZeros(uint32 Value)` (scope `Lightmass`)
- L483 _function_ `FORCEINLINE FVector4f SphericalToUnitCartesian(const FVector2f& InHemispherical)` (scope `Lightmass`) — Converts spherical coordinates on the unit sphere into a cartesian unit length vector.

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Math/LMMathSSE.h` (Private)


#### union `LmMakeVectorRegister::(anonymous)`  
`union`  
_L35-35_

#### union `LmVectorStoreFloat3::(anonymous)`  
`union`  
_L201-201_

#### union `LmVectorPow::(anonymous)`  
`union`  
_L372-372_
- desc: @TODO: Optimize

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef __m128 LmVectorRegister;` — float4 vector register type, where the first float (X) is stored in the lowest 32 bits, and so on.
- L22 _macro_ `#define LMSHUFFLEMASK(A0,A1,B2,B3) ( (A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6) )` — @param A0	Selects which component (0-3) from 'A' into 1st slot in the result @param A1	Selects which component (0-3) from 'A' into 2nd slot in the result @param B2	Selects which component (0-3) from 'B' into 3rd slot in the result @param B3	Selects which component (0-3) from 'B' into 4th slot in the result
- L33 _function_ `FORCEINLINE LmVectorRegister LmMakeVectorRegister( uint32 X, uint32 Y, uint32 Z, uint32 W )` — Returns a bitwise equivalent vector based on 4 DWORDs. @param X		1st uint32 component @param Y		2nd uint32 component @param Z		3rd uint32 component @param W		4th uint32 component @return		Bitwise equivalent vector with 4 floats
- L35 _member_ `union { LmVectorRegister v; uint32 f[4]; } Tmp;` (scope `LmMakeVectorRegister::__anon9159637d010a`)
- L35 _member_ `union { LmVectorRegister v; uint32 f[4]; } Tmp;` (scope `LmMakeVectorRegister::__anon9159637d010a`)
- L52 _function_ `FORCEINLINE LmVectorRegister LmMakeVectorRegister( float X, float Y, float Z, float W )` — Returns a vector based on 4 FLOATs. @param X		1st float component @param Y		2nd float component @param Z		3rd float component @param W		4th float component @return		Vector of the 4 FLOATs
- L57 _function_ `FORCEINLINE LmVectorRegister LmMakeVectorRegister( double X, double Y, double Z, double W )`
- L63 _variable_ `static const LmVectorRegister LM_SSE_ONE = LmMakeVectorRegister( 1.0f, 1.0f, 1.0f, 1.0f );` — Vector that represents (1,1,1,1)
- L66 _variable_ `static const LmVectorRegister LM_SSE_XYZ_MASK = LmMakeVectorRegister( (uint32)0xffffffff, (uint32)0xffffffff, (uint32)0xffffffff, (uint32)0x00000000 );` — Bitmask to AND out the XYZ components in a vector
- L69 _macro_ `#define LM_SIGN_BIT (~(1 << 31))` — Bitmask to AND out the sign bit of each components in a vector
- L70 _variable_ `static const LmVectorRegister LM_SSE_SIGN_MASK = LmMakeVectorRegister( (uint32)LM_SIGN_BIT, (uint32)LM_SIGN_BIT, (uint32)LM_SIGN_BIT, (uint32)LM_SIGN_BIT );`
- L82 _macro_ `#define LmVectorZero() _mm_setzero_ps()` — Returns a vector with all zeros. @return		LmVectorRegister(0.0f, 0.0f, 0.0f, 0.0f)
- L89 _macro_ `#define LmVectorOne() LM_SSE_ONE` — Returns a vector with all ones. @return		LmVectorRegister(1.0f, 1.0f, 1.0f, 1.0f)
- L98 _macro_ `#define LmVectorGetComponent( Vec, ComponentIndex ) (((float*) &(Vec))[ComponentIndex])` — Returns an component from a vector. @param Vec				Vector register @param ComponentIndex	Which component to get, X=0, Y=1, Z=2, W=3 @return					The component as a float
- L106 _macro_ `#define LmVectorLoad( Ptr ) _mm_loadu_ps( (float*)(Ptr) )` — Loads 4 FLOATs from unaligned memory. @param Ptr	Unaligned memory pointer to the 4 FLOATs @return		LmVectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
- L114 _macro_ `#define LmVectorLoadFloat3( Ptr ) LmMakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 0.0f )` — Loads 3 FLOATs from unaligned memory and leaves W undefined. @param Ptr	Unaligned memory pointer to the 3 FLOATs @return		LmVectorRegister(Ptr[0], Ptr[1], Ptr[2], undefined)
- L122 _macro_ `#define LmVectorLoadFloat3_W0( Ptr ) LmMakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 0.0f )` — Loads 3 FLOATs from unaligned memory and sets W=0. @param Ptr	Unaligned memory pointer to the 3 FLOATs @return		LmVectorRegister(Ptr[0], Ptr[1], Ptr[2], 0.0f)
- L130 _macro_ `#define LmVectorLoadFloat3_W1( Ptr ) LmMakeVectorRegister( ((const float*)(Ptr))[0], ((const float*)(Ptr))[1], ((const float*)(Ptr))[2], 1.0f )` — Loads 3 FLOATs from unaligned memory and sets W=1. @param Ptr	Unaligned memory pointer to the 3 FLOATs @return		LmVectorRegister(Ptr[0], Ptr[1], Ptr[2], 1.0f)
- L138 _macro_ `#define LmVectorLoadAligned( Ptr ) _mm_load_ps( (float*)(Ptr) )` — Loads 4 FLOATs from aligned memory. @param Ptr	Aligned memory pointer to the 4 FLOATs @return		LmVectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
- L146 _macro_ `#define LmVectorLoadFloat1( Ptr ) _mm_load1_ps( (float*)(Ptr) )` — Loads 1 float from unaligned memory and replicates it to all 4 components. @param Ptr	Unaligned memory pointer to the float @return		LmVectorRegister(Ptr[0], Ptr[0], Ptr[0], Ptr[0])
- L154 _macro_ `#define LmVectorSetFloat1( F ) _mm_set1_ps( F )` — Propagates passed in float to all registers @param F		Float to set @return		LmVectorRegister(F,F,F,F)
- L164 _macro_ `#define LmVectorSetFloat3( X, Y, Z ) LmMakeVectorRegister( X, Y, Z, 0.0f )` — Creates a vector out of three FLOATs and leaves W undefined. @param X		1st float component @param Y		2nd float component @param Z		3rd float component @return		LmVectorRegister(X, Y, Z, undefined)
- L175 _macro_ `#define LmVectorSet( X, Y, Z, W ) LmMakeVectorRegister( X, Y, Z, W )` — Creates a vector out of four FLOATs. @param X		1st float component @param Y		2nd float component @param Z		3rd float component @param W		4th float component @return		LmVectorRegister(X, Y, Z, W)
- L183 _macro_ `#define LmVectorStoreAligned( Vec, Ptr ) _mm_store_ps( (float*)(Ptr), Vec )` — Stores a vector to aligned memory. @param Vec	Vector to store @param Ptr	Aligned memory pointer
- L191 _macro_ `#define LmVectorStore( Vec, Ptr ) _mm_storeu_ps( (float*)(Ptr), Vec )` — Stores a vector to memory (aligned or unaligned). @param Vec	Vector to store @param Ptr	Memory pointer
- L199 _function_ `FORCEINLINE void LmVectorStoreFloat3( const LmVectorRegister& Vec, void* Ptr )` — Stores the XYZ components of a vector to unaligned memory. @param Vec	Vector to store XYZ @param Ptr	Unaligned memory pointer
- L201 _member_ `union { LmVectorRegister v; float f[4]; } Tmp;` (scope `LmVectorStoreFloat3::__anon9159637d020a`)
- L201 _member_ `union { LmVectorRegister v; float f[4]; } Tmp;` (scope `LmVectorStoreFloat3::__anon9159637d020a`)
- L215 _macro_ `#define LmVectorStoreFloat1( Vec, Ptr ) _mm_store_ss((float*)(Ptr), Vec)` — Stores the X component of a vector to unaligned memory. @param Vec	Vector to store X @param Ptr	Unaligned memory pointer
- L223 _macro_ `#define LmVectorTruncate( Vec ) _mm_cvttss_si32( Vec )` — Truncates the X component of a vector and returns it as an integer. @param	Vec		Vector to truncate X component @return	(int32) Truncate( Vec.X )
- L232 _macro_ `#define LmVectorMultiplexHigh( Vec1, Vec2 ) _mm_movehl_ps( Vec1, Vec2 )` — Multiplexes two vectors using upper two floating point values. @param	Vec1	Source vector @param	Vec2	Source vector @param	LmVectorRegister( Vec1.z, Vec1.w, Vec2.z, Vec2.w )
- L241 _macro_ `#define LmVectorMultiplexLow( Vec1, Vec2 ) _mm_movelh_ps( Vec1, Vec2 )` — Multiplexes two vectors using lower two floating point values. @param	Vec1	Source vector @param	Vec2	Source vector @param	LmVectorRegister( Vec1.x, Vec1.y, Vec2.x, Vec2.y )
- L250 _macro_ `#define LmVectorReplicate( Vec, ComponentIndex ) _mm_shuffle_ps( Vec, Vec, LMSHUFFLEMASK(ComponentIndex,ComponentIndex,ComponentIndex,ComponentIndex) )` — Replicates one component into all four components and returns the new vector. @param Vec				Source vector @param ComponentIndex	Index (0-3) of the component to replicate @return					LmVectorRegister( Vec[ComponentIndex], Vec[ComponentIndex], Vec[ComponentIndex], Vec[ComponentIndex] )
- L258 _macro_ `#define LmVectorAbs( Vec ) _mm_and_ps(Vec, LM_SSE_SIGN_MASK)` — Returns the absolute value (component-wise). @param Vec			Source vector @return				LmVectorRegister( abs(Vec.x), abs(Vec.y), abs(Vec.z), abs(Vec.w) )
- L266 _macro_ `#define LmVectorNegate( Vec ) _mm_sub_ps(_mm_setzero_ps(),Vec)` — Returns the negated value (component-wise). @param Vec			Source vector @return				LmVectorRegister( -Vec.x, -Vec.y, -Vec.z, -Vec.w )
- L275 _macro_ `#define LmVectorAdd( Vec1, Vec2 ) _mm_add_ps( Vec1, Vec2 )` — Adds two vectors (component-wise) and returns the result. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( Vec1.x+Vec2.x, Vec1.y+Vec2.y, Vec1.z+Vec2.z, Vec1.w+Vec2.w )
- L284 _macro_ `#define LmVectorSubtract( Vec1, Vec2 ) _mm_sub_ps( Vec1, Vec2 )` — Subtracts a vector from another (component-wise) and returns the result. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( Vec1.x-Vec2.x, Vec1.y-Vec2.y, Vec1.z-Vec2.z, Vec1.w-Vec2.w )
- L293 _macro_ `#define LmVectorMultiply( Vec1, Vec2 ) _mm_mul_ps( Vec1, Vec2 )` — Multiplies two vectors (component-wise) and returns the result. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( Vec1.x*Vec2.x, Vec1.y*Vec2.y, Vec1.z*Vec2.z, Vec1.w*Vec2.w )
- L302 _macro_ `#define LmVectorDivide( Vec1, Vec2 ) _mm_div_ps( Vec1, Vec2 )` — Divides two vectors (component-wise) and returns the result. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( Vec1.x/Vec2.x, Vec1.y/Vec2.y, Vec1.z/Vec2.z, Vec1.w/Vec2.w )
- L312 _macro_ `#define LmVectorMultiplyAdd( Vec1, Vec2, Vec3 ) _mm_add_ps( _mm_mul_ps(Vec1, Vec2), Vec3 )` — Multiplies two vectors (component-wise), adds in the third vector and returns the result. @param Vec1	1st vector @param Vec2	2nd vector @param Vec3	3rd vector @return		LmVectorRegister( Vec1.x*Vec2.x + Vec3.x, Vec1.y*Vec2.y + Vec3.y, Vec1.z*Vec2.z + Vec3.z, Vec1.w*Vec2.w + Vec3.w )
- L322 _function_ `FORCEINLINE LmVectorRegister LmVectorDot3( const LmVectorRegister& Vec1, const LmVectorRegister& Vec2 )` — Calculates the dot3 product of two vectors and returns a vector with the result in all 4 components. Only really efficient on Xbox 360. @param Vec1	1st vector @param Vec2	2nd vector @return		d = dot3(Vec1.xyz, Vec2.xyz), LmVectorRegister( d, d, d, d )
- L336 _function_ `FORCEINLINE LmVectorRegister LmVectorDot4( const LmVectorRegister& Vec1, const LmVectorRegister& Vec2 )` — Calculates the dot4 product of two vectors and returns a vector with the result in all 4 components. Only really efficient on Xbox 360. @param Vec1	1st vector @param Vec2	2nd vector @return		d = dot4(Vec1.xyzw, Vec2.xyzw), LmVectorRegister( d, d, d, d )
- L353 _function_ `FORCEINLINE LmVectorRegister LmVectorCross( const LmVectorRegister& Vec1, const LmVectorRegister& Vec2 )` — Calculates the cross product of two vectors (XYZ components). W is set to 0. @param Vec1	1st vector @param Vec2	2nd vector @return		cross(Vec1.xyz, Vec2.xyz). W is set to 0.
- L369 _function_ `FORCEINLINE LmVectorRegister LmVectorPow( const LmVectorRegister& Base, const LmVectorRegister& Exponent )` — Calculates x raised to the power of y (component-wise). @param Base		Base vector @param Exponent	Exponent vector @return			LmVectorRegister( Base.x^Exponent.x, Base.y^Exponent.y, Base.z^Exponent.z, Base.w^Exponent.w )
- L372 _member_ `union { LmVectorRegister v; float f[4]; } B, E;` (scope `LmVectorPow::__anon9159637d030a`) — @TODO: Optimize
- L372 _member_ `union { LmVectorRegister v; float f[4]; } B, E;` (scope `LmVectorPow::__anon9159637d030a`) — @TODO: Optimize
- L385 _function_ `FORCEINLINE void LmVectorMatrixMultiply( void *Result, const void* Matrix1, const void* Matrix2 )` — Multiplies two 4x4 matrices. @param Result	Pointer to where the result should be stored @param Matrix1	Pointer to the first matrix @param Matrix2	Pointer to the second matrix
- L429 _macro_ `#define LmVectorMatrixInverse( DstMatrix, SrcMatrix ) D3DXMatrixInverse( (D3DXMATRIX*) DstMatrix, NULL, (const D3DXMATRIX*)SrcMatrix )` — Calculate the inverse of an FMatrix44f. @param DstMatrix		FMatrix44f pointer to where the result should be stored @param SrcMatrix		FMatrix44f pointer to the Matrix to be inversed
- L438 _macro_ `#define LmVectorMin( Vec1, Vec2 ) _mm_min_ps( Vec1, Vec2 )` — Returns the minimum values of two vectors (component-wise). @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( min(Vec1.x,Vec2.x), min(Vec1.y,Vec2.y), min(Vec1.z,Vec2.z), min(Vec1.w,Vec2.w) )
- L447 _macro_ `#define LmVectorMax( Vec1, Vec2 ) _mm_max_ps( Vec1, Vec2 )` — Returns the maximum values of two vectors (component-wise). @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( max(Vec1.x,Vec2.x), max(Vec1.y,Vec2.y), max(Vec1.z,Vec2.z), max(Vec1.w,Vec2.w) )
- L457 _macro_ `#define LmVectorMinFloat1( Vec1, Vec2 ) _mm_min_ss( Vec1, Vec2 )` — Returns the minimum values of the first component of two vectors and passes through others from first vectors. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( min(Vec1.x,Vec2.x), Vec1.y, Vec1.z, Vec1.w )
- L467 _macro_ `#define LmVectorMaxFloat1( Vec1, Vec2 ) _mm_max_ss( Vec1, Vec2 )` — Returns the maximum values of the first component of two vectors and passes through others from first vectors. @param Vec1	1st vector @param Vec2	2nd vector @return		LmVectorRegister( max(Vec1.x,Vec2.x), Vec1.y, Vec1.z, Vec1.w )
- L477 _macro_ `#define LmVectorCompareGEFloat1( Vec1, Vec2 ) _mm_comige_ss( Vec1, Vec2 )` — Compares first component of Vec1 to first component of Vec2 and returns true if Vec1 >= Vec2. @param	Vec1	Vector to compare @param	Vec2	Vector to compare @return (Vec1.x >= Vec2.x) ? true : false
- L487 _macro_ `#define LmVectorCompareGE( Vec1, Vec2 ) _mm_cmpge_ps( Vec1, Vec2 )` — Compares Vec1 to Vec2 and returns 0xFFFFFFFF per component if it was GE or 0 if it wasn't. @param	Vec1	Vector to compare @param	Vec2	Vector to compare @return  LmVectorRegister( Vec1.x >= Vec2.x ? 0xFFFFFFFF : 0, Vec1.y >= Vec2.y ? 0xFFFFFFFF : 0, Vec1.z >= Vec2.z ? 0xFFFFFFFF : 0, Vec1.w >= Vec2.w ? 0xFFFFFFFF : 0 )
- L497 _macro_ `#define LmVectorCompareGT( Vec1, Vec2 ) _mm_cmpgt_ps( Vec1, Vec2 )` — Compares Vec1 to Vec2 and returns 0xFFFFFFFF per component if it was GT or 0 if it wasn't. @param	Vec1	Vector to compare @param	Vec2	Vector to compare @return  LmVectorRegister( Vec1.x > Vec2.x ? 0xFFFFFFFF : 0, Vec1.y > Vec2.y ? 0xFFFFFFFF : 0, Vec1.z > Vec2.z ? 0xFFFFFFFF : 0, Vec1.w > Vec2.w ? 0xFFFFFFFF : 0 )
- L506 _macro_ `#define LmVectorBitwiseAND( Vec1, Vec2 ) _mm_and_ps( (Vec1), (Vec2) )` — Returns the bitwise AND. @param	Vec1	Vector to AND @param	Vec2	Vector to AND @return	bitwise per component AND operation.
- L515 _macro_ `#define LmVectorBitwiseOR( Vec1, Vec2 ) _mm_or_ps( (Vec1), (Vec2) )` — Returns the bitwise OR. @param	Vec1	Vector to OR @param	Vec2	Vector to OR @return	bitwise per component OR operation.
- L524 _macro_ `#define LmVectorBitwiseXOR( Vec1, Vec2 ) _mm_xor_ps( (Vec1), (Vec2) )` — Returns the bitwise XOR. @param	Vec1	Vector to XOR @param	Vec2	Vector to XOR @return	bitwise per component XOR operation.
- L533 _macro_ `#define LmVectorBitwiseANDNOT( Vec1, Vec2 ) _mm_andnot_ps( (Vec1), (Vec2) )` — Returns the bitwise AND NOT. @param	Vec1	Vector to NOT AND @param	Vec2	Vector to AND @return	LmVectorRegister( ~Vec1.x & Vec2.x, ~Vec1.y & Vec2.y, ~Vec1.z & Vec2.z, ~Vec1.w & Vec2.w )
- L543 _function_ `FORCEINLINE LmVectorRegister LmVectorSelect( const LmVectorRegister& Vec1, const LmVectorRegister& Vec2, const LmVectorRegister& Mask )` — Selects the passed in vectors based on mask. @param	Vec1	Vector to choose from @param	Vec2	Vector to choose from @param	Mask	Mask to use for chosing. Can be thought of as "alpha" @return	LmVectorRegister( Mask.X == 0xFFFFFFFF ? Vec2.X : Vec1.X, Mask.Y == 0xFFFFFFFF ? Vec2.Y : Vec1.Y, Mask.Z == 0xFFFFFFFF ? Vec2.Z : Vec1.Z, Mask.W == 0xFFFFFFFF ? Vec2.W : Vec1.W );
- L558 _macro_ `#define LmVectorSwizzle( Vec, X, Y, Z, W ) _mm_shuffle_ps( Vec, Vec, LMSHUFFLEMASK(X,Y,Z,W) )` — Swizzles the 4 components of a vector and returns the result. @param Vec		Source vector @param X			Index for which component to use for X (literal 0-3) @param Y			Index for which component to use for Y (literal 0-3) @param Z			Index for which component to use for Z (literal 0-3) @param W			Index for which component to use for W (literal 0-3) @return			The swizzled vector
- L576 _macro_ `#define LmVectorAnyGreaterThan( Vec1, Vec2 ) _mm_movemask_ps( _mm_cmpgt_ps(Vec1, Vec2) )` — Returns non-zero if any component in Vec1 is greater than the corresponding component in Vec2, otherwise 0. @param Vec1			1st source vector @param Vec2			2nd source vector @return				Non-zero integer if (Vec1.x > Vec2.x) || (Vec1.y > Vec2.y) || (Vec1.z > Vec2.z) || (Vec1.w > Vec2.w)
- L585 _macro_ `#define LmVectorAllGreaterThan( Vec1, Vec2 ) (!_mm_movemask_ps( _mm_cmple_ps(Vec1, Vec2) ))` — Returns non-zero if all components in Vec1 are greater than the corresponding components in Vec2, otherwise 0. @param Vec1			1st source vector @param Vec2			2nd source vector @return				Non-zero integer if (Vec1.x > Vec2.x) && (Vec1.y > Vec2.y) && (Vec1.z > Vec2.z) && (Vec1.w > Vec2.w)
- L594 _macro_ `#define LmVectorAnyLessThan( Vec1, Vec2 ) _mm_movemask_ps( _mm_cmplt_ps(Vec1, Vec2) )` — Returns non-zero if any component in Vec1 is less than the corresponding component in Vec2, otherwise 0. @param Vec1			1st source vector @param Vec2			2nd source vector @return				Non-zero integer if (Vec1.x < Vec2.x) || (Vec1.y < Vec2.y) || (Vec1.z < Vec2.z) || (Vec1.w < Vec2.w)
- L603 _macro_ `#define LmVectorAllLessThan( Vec1, Vec2 ) (!_mm_movemask_ps( _mm_cmpge_ps(Vec1, Vec2) ))` — Returns non-zero if all components in Vec1 are less than the corresponding components in Vec2, otherwise 0. @param Vec1			1st source vector @param Vec2			2nd source vector @return				Non-zero integer if (Vec1.x < Vec2.x) && (Vec1.y < Vec2.y) && (Vec1.z < Vec2.z) && (Vec1.w < Vec2.w)
- L613 _macro_ `#define LmVectorMask_LT( Vec1, Vec2 ) _mm_cmplt_ps(Vec1, Vec2)` — These functions return a vector mask to indicate which components pass the comparison. Each component is 0xffffffff if it passes, 0x00000000 if it fails. @param Vec1			1st source vector @param Vec2			2nd source vector @return				Vector with a mask for each component.
- L614 _macro_ `#define LmVectorMask_LE( Vec1, Vec2 ) _mm_cmple_ps(Vec1, Vec2)`
- L615 _macro_ `#define LmVectorMask_GT( Vec1, Vec2 ) _mm_cmpgt_ps(Vec1, Vec2)`
- L616 _macro_ `#define LmVectorMask_GE( Vec1, Vec2 ) _mm_cmpge_ps(Vec1, Vec2)`
- L617 _macro_ `#define LmVectorMask_EQ( Vec1, Vec2 ) _mm_cmpeq_ps(Vec1, Vec2)`
- L618 _macro_ `#define LmVectorMask_NE( Vec1, Vec2 ) _mm_cmpneq_ps(Vec1, Vec2)`
- L627 _macro_ `#define LmVectorShiftRight( Vec1, Count ) _mm_castsi128_ps(_mm_srli_epi32(_mm_castps_si128(Vec1), Count))` — Shifts the 4 signed or unsigned 32-bit integers right by input amount while shifting in zeros. @param Vec1			1st source vector @param Count			Number of bits to shift @return				Shifted vector
- L635 _macro_ `#define LmVectorMaskBits( VecMask ) _mm_movemask_ps( VecMask )` — Returns an integer bit-mask (0x00 - 0x0f) based on the sign-bit for each component in a vector. @param VecMask		Vector @return				Bit 0 = sign(VecMask.x), Bit 1 = sign(VecMask.y), Bit 2 = sign(VecMask.z), Bit 3 = sign(VecMask.w)
- L642 _macro_ `#define LmVectorGetControlRegister() _mm_getcsr()` — Returns the control register. @return			The uint32 control register
- L649 _macro_ `#define LmVectorSetControlRegister(ControlStatus) _mm_setcsr( ControlStatus )` — Sets the control register. @param ControlStatus		The uint32 control status value to set
- L654 _macro_ `#define LM_VECTOR_ROUND_TOWARD_ZERO _MM_ROUND_TOWARD_ZERO` — Control status bit to round all floating point math results towards zero.

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Math/LMOctree.h` (Private)


#### class `Lightmass::FBoxCenterAndExtent`  
`class FBoxCenterAndExtent`  
_L19-75_
- desc: An unquantized bounding box.
- L22 _public member_ `FVector4f Center;`
- L23 _public member_ `FVector4f Extent;`
- L26 _public function_ `FBoxCenterAndExtent()` — Default constructor.
- L29 _public function_ `FBoxCenterAndExtent(const FVector4f& InCenter,const FVector4f& InExtent) : Center(InCenter) , Extent(InExtent)` — Initialization constructor.
- L35 _public function_ `FBoxCenterAndExtent(const FBox3f& Box)` — FBox3f conversion constructor.
- L46 _public function_ `FBoxCenterAndExtent(const FBoxSphereBounds3f& BoxSphere)` — FBoxSphereBounds3f conversion constructor.
- L54 _public function_ `FORCEINLINE FBox3f GetBox() const` — Converts to a FBox3f.

#### class `Lightmass::FOctreeChildNodeRef`  
`class FOctreeChildNodeRef`  
_L78-127_
- desc: A reference to a child of an octree node.
- L95 _public function_ `FOctreeChildNodeRef(int32 InX,int32 InY,int32 InZ) : X(InX) , Y(InY) , Z(InZ) , bNULL(false)` — Initialization constructor.
- L103 _public function_ `FOctreeChildNodeRef(int32 InIndex = 0)` — Initialized the reference with a child index.
- L110 _public function_ `FORCEINLINE void Advance()` — Advances the reference to the next child node.  If this was the last node remain, sets bInvalid=true.
- L123 _public function_ `FORCEINLINE bool IsNULL() const` — @return true if the reference isn't set.

#### union `Lightmass::FOctreeChildNodeRef::(anonymous)`  
``  
_L83-92_

#### struct `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a::(anonymous)`  
``  
_L85-90_

#### class `Lightmass::FOctreeChildNodeSubset`  
`class FOctreeChildNodeSubset`  
_L130-178_
- desc: A subset of an octree node's children that intersect a bounding box.
- L163 _public function_ `FOctreeChildNodeSubset() : AllBits(0)` — Initializes the subset to be empty.
- L168 _public function_ `FOctreeChildNodeSubset(FOctreeChildNodeRef ChildRef) : AllBits(0)` — Initializes the subset to contain a single node.
- L177 _public prototype_ `bool Contains(FOctreeChildNodeRef ChildRef) const;` — Determines whether the subset contains a specific node.
- L640 _function_ `FORCEINLINE bool FOctreeChildNodeSubset::Contains(FOctreeChildNodeRef ChildRef) const`

#### union `Lightmass::FOctreeChildNodeSubset::(anonymous)`  
``  
_L135-160_

#### struct `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::(anonymous)`  
``  
_L137-144_

#### struct `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::(anonymous)`  
``  
_L147-153_

#### class `Lightmass::FOctreeNodeContext`  
`class FOctreeNodeContext`  
_L181-247_
- desc: The context of an octree node, derived from the traversal of the tree.
- L186 _public member_ `FBoxCenterAndExtent Bounds;` — The bounds of the node.
- L189 _public member_ `float ChildExtent;` — The extent of the node's children.
- L192 _public member_ `float ChildCenterOffset;` — The offset of the childrens' centers from the center of this node.
- L195 _public member_ `int32 LoosenessDenominator;` — The node bounds are expanded by their extent divided by LoosenessDenominator.
- L198 _public function_ `FOctreeNodeContext()` — Default constructor.
- L202 _public function_ `FOctreeNodeContext(const FBoxCenterAndExtent& InBounds, int32 InLoosenessDenominator) : Bounds(InBounds) , LoosenessDenominator(InLoosenessDenominator)` — Initialization constructor.
- L215 _public function_ `FORCEINLINE FOctreeNodeContext GetChildContext(FOctreeChildNodeRef ChildRef) const` — Child node initialization constructor.
- L238 _public prototype_ `FOctreeChildNodeSubset GetIntersectingChildren(const FBoxCenterAndExtent& BoundingBox) const;` — Determines which of the octree node's children intersect with a bounding box. @param BoundingBox - The bounding box to check for intersection with. @return A subset of the children's nodes that intersect the bounding box.
- L246 _public prototype_ `FOctreeChildNodeRef GetContainingChild(const FBoxCenterAndExtent& BoundingBox) const;` — Determines which of the octree node's children contain the whole bounding box, if any. @param BoundingBox - The bounding box to check for intersection with. @return The octree's node that the bounding box is farthest from the outside edge of, or an invalid node ref if it's not contained by any of the children.
- L647 _function_ `FORCEINLINE FOctreeChildNodeSubset FOctreeNodeContext::GetIntersectingChildren(const FBoxCenterAndExtent& QueryBounds) const`
- L679 _function_ `FORCEINLINE FOctreeChildNodeRef FOctreeNodeContext::GetContainingChild(const FBoxCenterAndExtent& QueryBounds) const`

#### class `Lightmass::TOctree`  
`template<typename ElementType,typename OctreeSemantics> class TOctree`  
_L251-637_
- desc: An octree.
- L255 _public typedef_ `typedef TArray<ElementType, typename OctreeSemantics::ElementAllocator > ElementArrayType;`
- L257 _public typedef_ `typedef typename ElementArrayType::TIterator ElementIt;` — Note: Care must be taken to not modify any part of the element which would change it's location in the octree using this iterator.
- L258 _public typedef_ `typedef typename ElementArrayType::TConstIterator ElementConstIt;`
- L365 _public typedef_ `typedef TInlineAllocator<7 * (14 - 1) + 8> DefaultStackAllocator;` — The default iterator allocator gives the stack enough inline space to contain a path and its siblings from root to leaf.
- L602 _public prototype_ `void AddElement(typename TTypeTraits<ElementType>::ConstInitType Element);` — Adds an element to the octree. @param Element - The element to add. @return An identifier for the element in the octree.
- L605 _public prototype_ `void DumpStats(bool bDetailed) const;` — Writes stats for the octree to the log.
- L607 _public prototype_ `void GetMemoryUsage(size_t& OutSizeBytes) const;`
- L610 _public prototype_ `TOctree(const FVector4f& InOrigin, float InExtent);` — Initialization constructor.
- L612 _public function_ `void Destroy()`
- L620 _private member_ `FMemStackBase NodeAllocator;` — Lightmass octree is grow-only. Use a stack allocator to coalesce allocations for better allocation performance.
- L623 _private member_ `FNode RootNode;` — The octree's root node.
- L626 _private member_ `FOctreeNodeContext RootNodeContext;` — The octree's root node's context.
- L629 _private member_ `float MinLeafExtent;` — The extent of a leaf at the maximum allowed depth of the tree.
- L632 _private prototype_ `void AddElementToNode( typename TTypeTraits<ElementType>::ConstInitType Element, const FNode& InNode, const FOctreeNodeContext& InContext );` — Adds an element to a node or its children.
- L711 _function_ `template<typename ElementType,typename OctreeSemantics> void TOctree<ElementType,OctreeSemantics>::AddElement(typename TTypeTraits<ElementType>::ConstInitType Element)`
- L717 _function_ `template<typename ElementType,typename OctreeSemantics> void TOctree<ElementType,OctreeSemantics>::AddElementToNode( typename TTypeTraits<ElementType>::ConstInitType Element, const FNode& InNode, const FOctreeNodeContext& InContext )`
- L797 _function_ `template<typename ElementType,typename OctreeSemantics> void TOctree<ElementType,OctreeSemantics>::DumpStats(bool bDetailed) const`
- L867 _function_ `template<typename ElementType,typename OctreeSemantics> void TOctree<ElementType,OctreeSemantics>::GetMemoryUsage(size_t& OutSizeBytes) const`
- L890 _function_ `template<typename ElementType,typename OctreeSemantics> TOctree<ElementType,OctreeSemantics>::TOctree(const FVector4f& InOrigin,float InExtent) : RootNode(NULL) , RootNodeContext(FBoxCenterAndExtent(InOrigin,FVector4f(InExtent,InExtent,InExtent,0)), OctreeSemantics::LoosenessDenominator) , MinLeafExtent(InExtent * FMath::Pow((1.0f + 1.0f / (float)OctreeSemantics::LoosenessDenominator) / 2.0f, (float)OctreeSemantics::MaxNodeDepth))`

#### class `Lightmass::TOctree::FNode`  
`class FNode`  
_L261-320_
- desc: A node in the octree.
- L268 _public function_ `FNode(const FNode* InParent) : Parent(InParent) , bIsLeaf(true)` — Initialization constructor.
- L279 _public function_ `~FNode()` — Destructor.
- L291 _public function_ `FORCEINLINE ElementIt GetElementIt() const` — Accessors.
- L292 _public function_ `FORCEINLINE ElementConstIt GetConstElementIt() const`
- L293 _public function_ `FORCEINLINE bool IsLeaf() const`
- L294 _public function_ `FORCEINLINE bool HasChild(FOctreeChildNodeRef ChildRef) const`
- L298 _public function_ `FORCEINLINE FNode* GetChild(FOctreeChildNodeRef ChildRef) const`
- L302 _public function_ `FORCEINLINE int32 GetElementCount() const`
- L310 _private member_ `mutable ElementArrayType Elements;` — The elements in this node.
- L313 _private member_ `const FNode* Parent;` — The parent of this node.
- L316 _private member_ `mutable FNode* Children[8];` — The children of the node.
- L319 _private member_ `mutable uint32 bIsLeaf : 1;` — true if the meshes should be added directly to the node, rather than subdividing when possible.

#### class `Lightmass::TOctree::FNodeReference`  
`class FNodeReference`  
_L323-341_
- desc: A reference to an octree node and its context.
- L327 _public member_ `FNode* Node;`
- L328 _public member_ `FOctreeNodeContext Context;`
- L331 _public function_ `FNodeReference(): Node(NULL), Context()` — Default constructor.
- L337 _public function_ `FNodeReference(FNode* InNode,const FOctreeNodeContext& InContext): Node(InNode), Context(InContext)` — Initialization constructor.

#### class `Lightmass::TOctree::FConstNodeReference`  
`class FConstNodeReference`  
_L344-362_
- desc: A reference to an octree node, its context, and a read lock.
- L348 _public member_ `const FNode* Node;`
- L349 _public member_ `FOctreeNodeContext Context;`
- L352 _public function_ `FConstNodeReference(): Node(NULL), Context()` — Default constructor.
- L358 _public function_ `FConstNodeReference(const FNode* InNode,const FOctreeNodeContext& InContext): Node(InNode), Context(InContext)` — Initialization constructor.

#### class `Lightmass::TOctree::TConstIterator`  
`template<typename StackAllocator = DefaultStackAllocator> class TConstIterator`  
_L369-430_
- desc: An octree node iterator.
- L374 _public function_ `void PushChild(FOctreeChildNodeRef ChildRef)` — Pushes a child of the current node onto the stack of nodes to visit.
- L384 _public function_ `void Advance()` — Iterates to the next node.
- L398 _public function_ `bool HasPendingNodes() const` — Checks if there are any nodes left to iterate over.
- L404 _public function_ `TConstIterator(const TOctree& Tree) : CurrentNode(FConstNodeReference(&Tree.RootNode,Tree.RootNodeContext))` — Starts iterating at the root of an octree.
- L409 _public function_ `TConstIterator(const FNode& Node,const FOctreeNodeContext& Context): CurrentNode(FConstNodeReference(&Node,Context))` — Starts iterating at a particular node of an octree.
- L414 _public function_ `const FNode& GetCurrentNode() const` — Accessors.
- L418 _public function_ `const FOctreeNodeContext& GetCurrentContext() const`
- L426 _private member_ `FConstNodeReference CurrentNode;` — The node that is currently being visited.
- L429 _private member_ `TArray<FConstNodeReference,StackAllocator> NodeStack;` — The nodes which are pending iteration.

#### class `Lightmass::TOctree::TIterator`  
`template<typename StackAllocator = DefaultStackAllocator> class TIterator`  
_L435-496_
- desc: An octree node iterator.
- L440 _public function_ `void PushChild(FOctreeChildNodeRef ChildRef)` — Pushes a child of the current node onto the stack of nodes to visit.
- L450 _public function_ `void Advance()` — Iterates to the next node.
- L464 _public function_ `bool HasPendingNodes() const` — Checks if there are any nodes left to iterate over.
- L470 _public function_ `TIterator(TOctree& Tree) : CurrentNode(FNodeReference(&Tree.RootNode,Tree.RootNodeContext))` — Starts iterating at the root of an octree.
- L475 _public function_ `TIterator(FNode& Node,const FOctreeNodeContext& Context): CurrentNode(FNodeReference(&Node,Context))` — Starts iterating at a particular node of an octree.
- L480 _public function_ `FNode& GetCurrentNode()` — Accessors.
- L484 _public function_ `const FOctreeNodeContext& GetCurrentContext() const`
- L492 _private member_ `FNodeReference CurrentNode;` — The node that is currently being visited.
- L495 _private member_ `TArray<FNodeReference,StackAllocator> NodeStack;` — The nodes which are pending iteration.

#### class `Lightmass::TOctree::TConstElementBoxIterator`  
`template<typename StackAllocator = DefaultStackAllocator> class TConstElementBoxIterator`  
_L500-595_
- desc: Iterates over the elements in the octree that intersect a bounding box.
- L505 _public function_ `void Advance()` — Iterates to the next element.
- L512 _public function_ `bool HasPendingElements() const` — Checks if there are any elements left to iterate over.
- L518 _public function_ `TConstElementBoxIterator(const TOctree& Tree,const FBoxCenterAndExtent& InBoundingBox) : IteratorBounds(InBoundingBox) , NodeIt(Tree) , ElementIt(Tree.RootNode.GetConstElementIt())` — Initialization constructor.
- L528 _public function_ `const ElementType& GetCurrentElement() const` — Accessors.
- L536 _private member_ `FBoxCenterAndExtent IteratorBounds;` — The bounding box to check for intersection with.
- L539 _private member_ `TConstIterator<StackAllocator> NodeIt;` — The octree node iterator.
- L542 _private member_ `ElementConstIt ElementIt;` — The element iterator for the current node.
- L545 _private function_ `void ProcessChildren()` — Processes the children of the current node.
- L561 _private function_ `void AdvanceToNextIntersectingElement()` — Advances the iterator to the next intersecting primitive, starting at a primitive in the current node.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Lightmass`
- L15 _macro_ `#define FOREACH_OCTREE_CHILD_NODE(ChildRef) \` — A concise iteration over the children of an octree node.
- L63 _function_ `friend bool Intersect(const FBoxCenterAndExtent& A,const FBoxCenterAndExtent& B)` (scope `Lightmass`) — Determines whether two boxes intersect. @return true if the boxes intersect, or false.
- L86 _member_ `uint32 X : 1;` (scope `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a::__anond4b6156a0208`)
- L87 _member_ `uint32 Y : 1;` (scope `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a::__anond4b6156a0208`)
- L88 _member_ `uint32 Z : 1;` (scope `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a::__anond4b6156a0208`)
- L89 _member_ `uint32 bNULL : 1;` (scope `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a::__anond4b6156a0208`)
- L91 _member_ `uint32 Index : 3;` (scope `Lightmass::FOctreeChildNodeRef::__anond4b6156a010a`)
- L138 _member_ `uint32 bPositiveX : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L139 _member_ `uint32 bPositiveY : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L140 _member_ `uint32 bPositiveZ : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L141 _member_ `uint32 bNegativeX : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L142 _member_ `uint32 bNegativeY : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L143 _member_ `uint32 bNegativeZ : 1;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0408`)
- L149 _member_ `uint32 PositiveChildBits : 3;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0508`) — Only the bits for the children on the positive side of the splits.
- L152 _member_ `uint32 NegativeChildBits : 3;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a::__anond4b6156a0508`) — Only the bits for the children on the negative side of the splits.
- L156 _member_ `uint32 ChildBits : 6;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a`) — All the bits corresponding to the child bits.
- L159 _member_ `uint32 AllBits;` (scope `Lightmass::FOctreeChildNodeSubset::__anond4b6156a030a`) — All the bits used to store the subset.

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Math/LMkDOP.h` (Private)


#### struct `Lightmass::FHitResult`  
`struct FHitResult`  
_L25-40_
- L28 _public member_ `FVector4f Normal;` — Normal vector in coordinate system of the returner. Zero==none.
- L30 _public member_ `float Time;` — Time until hit.
- L32 _public member_ `int32 Item;` — Primitive data item which was hit, INDEX_NONE=none
- L34 _public function_ `FHitResult() : Normal (0,0,0,0) , Time (1.0f) , Item (INDEX_NONE)`

#### struct `Lightmass::FVector3SOA`  
`struct FVector3SOA`  
_L45-53_
- desc: Stores XYZ from 4 vectors in one Struct Of Arrays.
- L48 _public member_ `LmVectorRegister X;` — X = (v0.x, v1.x, v2.x, v3.x)
- L50 _public member_ `LmVectorRegister Y;` — Y = (v0.y, v1.y, v2.y, v3.y)
- L52 _public member_ `LmVectorRegister Z;` — Z = (v0.z, v1.z, v2.z, v3.z)

#### struct `Lightmass::FVector4SOA`  
`struct FVector4SOA`  
_L58-68_
- desc: Stores XYZW from 4 vectors in one Struct Of Arrays.
- L61 _public member_ `LmVectorRegister X;` — X = (v0.x, v1.x, v2.x, v3.x)
- L63 _public member_ `LmVectorRegister Y;` — Y = (v0.y, v1.y, v2.y, v3.y)
- L65 _public member_ `LmVectorRegister Z;` — Z = (v0.z, v1.z, v2.z, v3.z)
- L67 _public member_ `LmVectorRegister W;` — W = (v0.w, v1.w, v2.w, v3.w)

#### struct `Lightmass::FTriangleSOA`  
`struct FTriangleSOA`  
_L73-88_
- desc: Stores 4 triangles in one struct (Struct Of Arrays).
- L76 _public member_ `FVector3SOA Positions[3];` — 3 vertex positions for each of the 4 triangles.
- L78 _public member_ `FVector4SOA Normals;` — Triangle normal (including -W for a plane) for each of the 4 triangles.
- L80 _public member_ `LmVectorRegister TwoSidedMask;` — All bits are 1 for two sided triangles, and 0 otherwise.
- L82 _public member_ `LmVectorRegister StaticAndOpaqueMask;` — All bits are 1 for static and opaque triangles, and 0 otherwise.
- L83 _public member_ `LmVectorRegister MeshIndices;`
- L84 _public member_ `LmVectorRegister LODIndices;`
- L85 _public member_ `LmVectorRegister HLODRange;`
- L87 _public member_ `uint32 Payload[4];` — A 32-bit payload value for each of the 4 triangles.

#### struct `Lightmass::TTraversalHistory`  
`template<typename KDOP_IDX_TYPE> struct TTraversalHistory`  
_L92-128_
- desc: Tracks information about a traversal through the kDOP tree.
- L99 _public member_ `KDOP_IDX_TYPE Nodes[NodeHistoryLength];`
- L101 _public function_ `TTraversalHistory()`
- L110 _public function_ `TTraversalHistory AddNode(KDOP_IDX_TYPE NewNodeIndex)`
- L123 _public function_ `KDOP_IDX_TYPE GetOldestNode() const`

#### enum `Lightmass::TTraversalHistory::(anonymous)`  
`enum`  
_L98-98_
- desc: Number of parent nodes to track information for. This has been tweaked for optimal boolean shadow ray performance.

#### class `Lightmass::FRangeChecklessHeapAllocator`  
`class FRangeChecklessHeapAllocator : public FHeapAllocator`  
_L130-136_
- inherits: `FHeapAllocator`

#### enum `Lightmass::FRangeChecklessHeapAllocator::(anonymous)`  
`enum`  
_L135-135_
- desc: Don't want to lose performance on range checks in performance-critical ray tracing code.

#### struct `Lightmass::FkDOPBuildCollisionTriangle`  
`template<typename KDOP_IDX_TYPE> struct FkDOPBuildCollisionTriangle`  
_L389-485_
- desc: This structure is used during the build process. It contains the triangle's centroid for calculating which plane it should be split or not with
- L394 _public member_ `FVector4f V0;` — First vertex in the triangle
- L398 _public member_ `FVector4f V1;` — Second vertex in the triangle
- L402 _public member_ `FVector4f V2;` — Third vertex in the triangle
- L410 _private member_ `FVector4f Centroid;` — Centroid of the triangle used for determining which bounding volume to place the triangle in
- L413 _private member_ `FVector4f LocalNormal;` — Cached local normal used by line/ triangle collision code.
- L418 _public member_ `int32 MeshIndex;` — Index of the mesh this triangle belongs to.
- L421 _public member_ `uint32 LODIndices;` — Index of the LOD this triangle belongs to.
- L424 _public member_ `uint32 HLODRange;` — Range of IDs for HLOD nodes children.
- L427 _public member_ `uint32 bTwoSided : 1;` — True if the triangle is two sided.
- L430 _public member_ `uint32 bStaticAndOpaque : 1;` — True if the triangle is opaque.
- L433 _public member_ `KDOP_IDX_TYPE MaterialIndex;` — The material of this triangle
- L436 _public function_ `FORCEINLINE const FVector4f& GetCentroid() const`
- L440 _public function_ `FORCEINLINE const FVector4f& GetLocalNormal() const`
- L445 _public function_ `inline FVector4f GetCentroid() const`
- L449 _public function_ `inline FVector4f GetLocalNormal() const`
- L461 _public function_ `FkDOPBuildCollisionTriangle( KDOP_IDX_TYPE InMaterialIndex, const FVector4f& vert0,const FVector4f& vert1,const FVector4f& vert2, int32 InMeshIndex, uint32 InLODIndices, uint32 InHLODRange, bool bInTwoSided, bool bInStaticAndOpaque) : V0(vert0), V1(vert1), V2(vert2), MeshIndex(InMeshIndex), LODIndices(InLODIndices), HLODRange(InHLODRange), bTwoSided(bInTwoSided), bStaticAndOpaque(bInStaticAndOpaque), MaterialIndex(InMaterialIndex)` — Sets the indices, material index, calculates the centroid using the specified triangle vertex positions

#### struct `Lightmass::FMultiBox`  
`struct FMultiBox`  
_L496-538_
- desc: Holds the min/max planes that make up a set of 4 bounding volumes.
- L501 _public member_ `MS_ALIGN(16) FVector4f Min[3] GCC_ALIGN(16);` — Min planes for this set of bounding volumes. Array index is X/Y/Z.
- L506 _public member_ `FVector4f Max[3];` — Max planes for this set of bounding volumes. Array index is X/Y/Z.
- L514 _public function_ `void SetBox( int32 BoundingVolumeIndex, const FBox3f& Box )` — Sets the box at the passed in index to the passed in box. @param	BoundingVolumeIndex		Index of box to set @param	Box						Box to set
- L531 _public function_ `FBox3f GetBox( int32 BoundingVolumeIndex )` — Returns the bounding volume at the passed in index. @param	BoundingVolumeIndex		Index of bounding volume to return @return Bounding volume at the passed in index

#### struct `Lightmass::BoxTriangleIntersectionInternal::FTriangle`  
`struct FTriangle`  
_L545-548_
- L547 _public member_ `FVector3f Vertices[3];`

#### struct `Lightmass::BoxTriangleIntersectionInternal::FOverlapInterval`  
`struct FOverlapInterval`  
_L550-554_
- L552 _public member_ `float Min;`
- L553 _public member_ `float Max;`

#### struct `Lightmass::TkDOPNode`  
`template <typename COLL_DATA_PROVIDER, typename KDOP_IDX_TYPE> struct TkDOPNode`  
_L653-1058_
- desc: A node in the kDOP tree. The node contains the kDOP volume that encompasses it's children and/or triangles
- L656 _public typedef_ `typedef COLL_DATA_PROVIDER DataProviderType;` — Exposes data provider type to clients.
- L659 _public typedef_ `typedef TkDOPNode<DataProviderType,KDOP_IDX_TYPE> NodeType;` — Exposes node type to clients.
- L662 _public member_ `FMultiBox BoundingVolumes;` — Set of bounding volumes for child nodes.
- L665 _public member_ `bool bIsLeaf;` — Note this isn't smaller since 4 byte alignment will take over anyway
- L666 _public member_ `uint8 Occupancy;`
- L692 _public function_ `FORCEINLINE TkDOPNode()` — Inits the data to no child nodes and an inverted volume
- L718 _public function_ `FORCEINLINE void LineCheckBounds(TkDOPLineCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>& Check, FVector4f& HitTime, int32 NodeHit[4] ) const` — The slab testing algorithm is based on the following papers. We chose to use the faster final hit determination, which means we'll get some false positives. "A Cross-Platform Framework for Interactive Ray Tracing" Markus Geimer, Stefan Mueller http://www.uni-koblenz.de/~cg/publikationen/cp_raytrace.pdf "Efficiency Issues for Ray Tracing" Brian Smits http://www.cs.utah.edu/~bes/papers/fastRT/paper-node10.html We don't need to handle +/- INF, but we have permission to use Thierry Berger-Perrin trick available below. http://www.flipcode.com/archives/SSE_RayBox_Intersection_Test.shtml @param	Check				Information about the ray to trace @param	HitTime	[out]	Time of hit
- L798 _public function_ `bool LineCheck(TkDOPLineCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>& Check, TTraversalHistory<KDOP_IDX_TYPE> History) const` — Determines the line in the FkDOPLineCollisionCheck intersects this node. It also will check the child nodes if it is not a leaf, otherwise it will check against the triangle data. @param Check -- The aggregated line check data
- L880 _public function_ `bool LineCheckPreCalculated(TkDOPLineCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>& Check, const FVector4f& NodeHitTime, TTraversalHistory<KDOP_IDX_TYPE> History, int32* NodeHit) const` — Determines the line in the FkDOPLineCollisionCheck intersects this node. It also will check the child nodes if it is not a leaf, otherwise it will check against the triangle data. @param Check -- The aggregated line check data
- L956 _public function_ `bool LineCheckTriangles(TkDOPLineCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>& Check, const TTraversalHistory<KDOP_IDX_TYPE>& History) const` — Works through the list of triangles in this node checking each one for a collision. @param Check -- The aggregated line check data
- L985 _public function_ `bool BoxCheckTriangles(TkDOPBoxCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>& Check) const`
- L1017 _public function_ `void BoxCheckBounds(TkDOPBoxCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>& Check, bool NodeHit[2]) const`
- L1031 _public function_ `bool BoxCheck(TkDOPBoxCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>& Check) const`

#### union `Lightmass::TkDOPNode::(anonymous)`  
``  
_L670-687_

#### struct `Lightmass::TkDOPNode::__anon1709d256030a::(anonymous)`  
``  
_L674-677_

#### struct `Lightmass::TkDOPNode::__anon1709d256030a::(anonymous)`  
``  
_L683-686_

#### struct `Lightmass::TkDOPTree`  
`template<typename COLL_DATA_PROVIDER, typename KDOP_IDX_TYPE> struct TkDOPTree`  
_L1065-1412_
- desc: This is the tree of kDOPs that spatially divides the static mesh. It is a binary tree of kDOP nodes.
- L1068 _public typedef_ `typedef COLL_DATA_PROVIDER DataProviderType;` — Exposes data provider type to clients.
- L1071 _public typedef_ `typedef TkDOPNode<DataProviderType,KDOP_IDX_TYPE> NodeType;` — Exposes node type to clients.
- L1075 _public member_ `int32 GKDOPTriangles = 0;` — Number of triangles in the aggregate mesh kDOP.
- L1077 _public member_ `int32 GKDOPNodes = 0;` — Number of internal nodes in the aggregate mesh kDOP.
- L1079 _public member_ `int32 GKDOPNumLeaves = 0;` — Number of leaf nodes in the aggregate mesh kDOP.
- L1081 _public member_ `int32 GKDOPMaxTrisPerLeaf = DEFAULT_MAX_TRIS_PER_LEAF;` — Maximum number of triangles per leaf node during the splitting process
- L1083 _public member_ `volatile uint64 GKDOPParentNodesTraversed = 0;` — Total number of kDOP internal nodes traversed when tracing rays.
- L1085 _public member_ `volatile uint64 GKDOPLeafNodesTraversed = 0;` — Total number of kDOP leaf nodes traversed when tracing rays.
- L1087 _public member_ `volatile uint64 GKDOPTrianglesTraversed = 0;` — Total number of kDOP triangles tested when tracing rays.
- L1088 _public member_ `volatile uint64 GKDOPTrianglesTraversedReal = 0;`
- L1089 _public member_ `size_t kDOPPreallocatedMemory = 0u;`
- L1090 _public member_ `float kDOPBuildTime = 0.0f;`
- L1093 _public member_ `kDOPArray<NodeType, FRangeChecklessHeapAllocator> Nodes;` — The list of nodes contained within this tree. Node 0 is always the root node.
- L1096 _public member_ `kDOPArray<FTriangleSOA, FRangeChecklessHeapAllocator> SOATriangles;` — The list of collision triangles in this tree.
- L1104 _public function_ `void Build(TArray<FkDOPBuildCollisionTriangle<KDOP_IDX_TYPE> >& BuildTriangles)` — Creates the root node and recursively splits the triangles into smaller volumes @param BuildTriangles -- The list of triangles to use for the build process
- L1145 _public function_ `FBox3f SplitTriangleList(KDOP_IDX_TYPE NodeIndex, int32 Start, int32 NumTris, TArray<FkDOPBuildCollisionTriangle<KDOP_IDX_TYPE> >& BuildTriangles)` — Determines if the node is a leaf or not. If it is not a leaf, it subdivides the list of triangles again adding two child nodes and splitting them on the mean (splatter method). Otherwise it sets up the triangle information. @param Start -- The triangle index to start processing with @param NumTris -- The number of triangles to process @param BuildTriangles -- The list of triangles to use for the build process @param Nodes -- The list of nodes in this tree @return bounding box for this node
- L1376 _public function_ `bool LineCheck(TkDOPLineCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>& Check) const` — Figures out whether the check even hits the root node's bounding volume. If it does, it recursively searches for a triangle to hit. @param Check -- The aggregated line check data
- L1384 _public function_ `bool BoxCheck(TkDOPBoxCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>& Check) const`
- L1392 _public function_ `void Dump()` — Dumps the kDOPTree

#### struct `Lightmass::TkDOPCollisionCheck`  
`template <typename COLL_DATA_PROVIDER, typename KDOP_IDX_TYPE> struct TkDOPCollisionCheck`  
_L1419-1457_
- desc: Base struct for all collision checks. Holds a reference to the collision data provider, which is a struct that abstracts out the access to a particular mesh/primitives data
- L1422 _public typedef_ `typedef COLL_DATA_PROVIDER DataProviderType;` — Exposes data provider type to clients.
- L1425 _public typedef_ `typedef TkDOPNode<DataProviderType,KDOP_IDX_TYPE> NodeType;` — Exposes node type to clients.
- L1428 _public typedef_ `typedef TkDOPTree<DataProviderType,KDOP_IDX_TYPE> TreeType;` — Exposes tree type to clients.
- L1433 _public member_ `const DataProviderType& CollDataProvider;` — Used to get access to local->world, vertices, etc. without using virtuals
- L1437 _public member_ `const TreeType& kDOPTree;` — The kDOP tree
- L1441 _public member_ `const kDOPArray<NodeType, FRangeChecklessHeapAllocator>& Nodes;` — The array of the nodes for the kDOP tree
- L1445 _public member_ `const kDOPArray<FTriangleSOA, FRangeChecklessHeapAllocator>& SOATriangles;` — The collision triangle data for the kDOP tree
- L1450 _public function_ `TkDOPCollisionCheck(const DataProviderType& InCollDataProvider) : CollDataProvider(InCollDataProvider), kDOPTree(CollDataProvider.GetkDOPTree()), Nodes(kDOPTree.Nodes), SOATriangles(kDOPTree.SOATriangles)` — Hide the default ctor

#### struct `Lightmass::TkDOPLineCollisionCheck`  
`template <typename COLL_DATA_PROVIDER, typename KDOP_IDX_TYPE> struct TkDOPLineCollisionCheck : public TkDOPCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>`  
_L1464-1580_
- inherits: `TkDOPCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>`
- desc: This struct holds the information used to do a line check against the kDOP tree. The collision provider gives access to various matrices, vertex data etc. without having to use virtual functions.
- L1470 _public member_ `FHitResult* Result;` — Where the collision results get stored
- L1472 _public member_ `const FVector4f& Start;` — Constant input vars
- L1473 _public member_ `const FVector4f& End;`
- L1478 _public member_ `const bool bFindClosestIntersection;` — Flags for optimizing a trace
- L1479 _public member_ `const bool bStaticAndOpaqueOnly;`
- L1480 _public member_ `const bool bTwoSidedCollision;`
- L1481 _public member_ `const bool bFlipSidedness;`
- L1483 _public member_ `FVector4f LocalStart;` — Locally calculated vectors
- L1484 _public member_ `FVector4f LocalEnd;`
- L1485 _public member_ `FVector4f LocalDir;`
- L1486 _public member_ `FVector4f LocalOneOverDir;`
- L1488 _public member_ `FVector4f LocalHitNormal;` — Normal in local space which gets transformed to world at the very end
- L1491 _public member_ `KDOP_IDX_TYPE HitNodeIndex;` — Index into the kDOP tree's nodes of the node that was hit.
- L1494 _public member_ `FVector3SOA StartSOA;` — Start of the line, where each component is replicated into their own vector registers.
- L1496 _public member_ `FVector3SOA EndSOA;` — End of the line, where each component is replicated into their own vector registers.
- L1498 _public member_ `FVector3SOA DirSOA;` — Direction of the line (not normalized, just EndSOA-StartSOA), where each component is replicated into their own vector registers.
- L1500 _public member_ `LmVectorRegister MeshIndexRegister;` — Mesh index of the instigating mesh in every channel.
- L1502 _public member_ `LmVectorRegister LODIndicesRegister;` — LOD indices of the instigating mesh in every channel.
- L1504 _public member_ `LmVectorRegister HLODRangeRegister;` — HLOD tree ranges of the instigating mesh in every channel.
- L1518 _public function_ `TkDOPLineCollisionCheck(const FVector4f& InStart,const FVector4f& InEnd, bool bInbFindClosestIntersection, bool bInStaticAndOpaqueOnly, bool bInTwoSidedCollision, bool bInFlipSidedness, const COLL_DATA_PROVIDER& InCollDataProvider, int32 MeshIndex, uint32 LODIndices, uint32 HLODRange, FHitResult* InResult) : TkDOPCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>(InCollDataProvider), Result(InResult), Start(InStart), End(InEnd), bFindClosestIntersection(bInbFindClosestIntersection), bStaticAndOpaqueOnly(bInStaticAndOpaqueOnly), bTwoSidedCollision(bInTwoSidedCollision), bFlipSidedness(bInFlipSidedness), HitNodeIndex(0xFFFFFFFF)` — Sets up the FkDOPLineCollisionCheck structure for performing line checks against a kDOPTree. Initializes all of the variables that are used throughout the line check. @param InStart -- The starting point of the trace @param InEnd -- The ending point of the trace @param InbFindClosestIntersection -- Whether to stop at the first hit or not @param InCollDataProvider -- The struct that provides access to mesh/primitive specific data, such as L2W, W2L, Vertices, and so on @param InResult -- The out param for hit result information
- L1569 _public function_ `FORCEINLINE FVector4f GetHitNormal(void)` — Transforms the local hit normal into a world space normal using the transpose adjoint and flips the normal if need be

#### struct `Lightmass::TkDOPBoxCollisionCheck`  
`template <typename COLL_DATA_PROVIDER, typename KDOP_IDX_TYPE> struct TkDOPBoxCollisionCheck : public TkDOPCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>`  
_L1582-1595_
- inherits: `TkDOPCollisionCheck<COLL_DATA_PROVIDER,KDOP_IDX_TYPE>`
- L1585 _public member_ `const FBox3f Box;`
- L1586 _public member_ `int32 Item;`
- L1588 _public function_ `TkDOPBoxCollisionCheck( const FBox3f& InBox, const COLL_DATA_PROVIDER& InCollDataProvider) : TkDOPCollisionCheck<COLL_DATA_PROVIDER, KDOP_IDX_TYPE>(InCollDataProvider), Box(InBox), Item(-1)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Lightmass`
- L17 _macro_ `#define NUM_PLANES 3` — Indicates how many "k / 2" there are in the k-DOP. 3 == AABB == 6 DOP. The code relies on this being 3.
- L19 _macro_ `#define SLOW_KDOP_STATS(...)` — Change to 'x' if you want kdop traversal stats at a heavy (usually around 6x) perf hit
- L21 _macro_ `#define CACHE_BUILD_TEMPORARIES 0` — Whether to cache Centroid, LocalNormal and such for build triangles. Peak memory vs. minor build time trade-off.
- L23 _macro_ `#define DEFAULT_MAX_TRIS_PER_LEAF 4` — The default number of triangles to store in each leaf
- L98 _enumerator_ `enum { NodeHistoryLength = 1 }; KDOP_IDX_TYPE Nodes[NodeHistoryLength]; TTraversalHistory() { for (int32 NodeIndex = 0; NodeIndex < NodeHistoryLength; NodeIndex++) {` (scope `Lightmass::TTraversalHistory::__anon1709d2560103`) — Number of parent nodes to track information for. This has been tweaked for optimal boolean shadow ray performance.
- L135 _enumerator_ `enum { RequireRangeCheck = false };` (scope `Lightmass::FRangeChecklessHeapAllocator::__anon1709d2560203`) — Don't want to lose performance on range checks in performance-critical ray tracing code.
- L151 _function_ `FORCEINLINE bool appLineCheckTriangle(const FVector4f& Start, const FVector4f& End, const FVector4f& Dir, const FVector4f& V0, const FVector4f& V1, const FVector4f& V2, const FVector4f& Normal, float& IntersectionTime)` (scope `Lightmass`) — Line vs triangle intersection test. @param Start		Start of the line segment @param End		End of the line segment @param Dir		Direction of the line segment (not normalized, just End-Start) @param V0		First vertex of the triangle @param V1		Second vertex of the triangle @param V2		Third vertex of the triangle @param Normal	Triangle normal (including +W for the plane equation) @param IntersectionTime	[in/out] Best intersection time so far (0..1), as in: IntersectionPoint = Start + IntersectionTime * Dir. @return			true if the line intersected the triangle
- L198 _variable_ `static const LmVectorRegister GSmallNegativeNumber = { -0.0001f, -0.0001f, -0.0001f, -0.0001f };` (scope `Lightmass`) — ( -0.0001f, -0.0001f, -0.0001f, -0.0001f )
- L202 _variable_ `static const LmVectorRegister GSmallNumber = { 0.0001f, 0.0001f, 0.0001f, 0.0001f };` (scope `Lightmass`) — ( 0.0001f, 0.0001f, 0.0001f, 0.0001f )
- L205 _variable_ `static const LmVectorRegister GZeroVectorRegister = { 0, 0, 0, 0 };` (scope `Lightmass`)
- L206 _variable_ `static const LmVectorRegister GFullMaskVectorRegister = LmMakeVectorRegister((uint32)-1, (uint32)-1, (uint32)-1, (uint32)-1);` (scope `Lightmass`)
- L208 _variable_ `static const LmVectorRegister IndexNoneVectorRegister = LmMakeVectorRegister((uint32)INDEX_NONE, (uint32)INDEX_NONE, (uint32)INDEX_NONE, (uint32)INDEX_NONE);` (scope `Lightmass`)
- L209 _variable_ `static const LmVectorRegister VectorNegativeOne = LmMakeVectorRegister( -1.0f, -1.0f, -1.0f, -1.0f );` (scope `Lightmass`)
- L212 _variable_ `static const LmVectorRegister HLODTreeIndexMask = LmMakeVectorRegister((uint32)0xFFFF0000, (uint32)0xFFFF0000, (uint32)0xFFFF0000, (uint32)0xFFFF0000);` (scope `Lightmass`) — LOD masks
- L213 _variable_ `static const LmVectorRegister HLODRangeStartIndexMask = LmMakeVectorRegister((uint32)0xFFFF, (uint32)0xFFFF, (uint32)0xFFFF, (uint32)0xFFFF);` (scope `Lightmass`)
- L214 _variable_ `static const LmVectorRegister HLODRangeEndIndexMask = LmMakeVectorRegister((uint32)0xFFFF0000, (uint32)0xFFFF0000, (uint32)0xFFFF0000, (uint32)0xFFFF0000);` (scope `Lightmass`)
- L215 _variable_ `static const LmVectorRegister HLODTreeIndexNoneRegister = LmMakeVectorRegister(0xFFFF0000 & (uint32)INDEX_NONE, 0xFFFF0000 & (uint32)INDEX_NONE, 0xFFFF0000 & (uint32)INDEX_NONE, 0xFFFF0000 & (uint32)INDEX_NONE);` (scope `Lightmass`)
- L217 _variable_ `static const LmVectorRegister LODIndexMask = LmMakeVectorRegister((uint32)0xFFFF, (uint32)0xFFFF, (uint32)0xFFFF, (uint32)0xFFFF);` (scope `Lightmass`)
- L229 _function_ `FORCEINLINE int32 appLineCheckTriangleSOA(const FVector3SOA& Start, const FVector3SOA& End, const FVector3SOA& Dir, LmVectorRegister MeshIndex, LmVectorRegister LODIndices, LmVectorRegister HLODRange, const FTriangleSOA& Triangle4, bool bStaticAndOpaqueOnly, bool bTwoSidedCollision, bool bFlipSidedness, float& InOutIntersectionTime)` (scope `Lightmass`) — Line vs triangle intersection test. Tests 1 line against 4 triangles at once. @param Start		Start of the line segment @param End		End of the line segment @param Dir		Direction of the line segment (not normalized, just End-Start) @param Triangle4	Four triangles @param IntersectionTime	[in/out] Best intersection time so far (0..1), as in: IntersectionPoint = Start + IntersectionTime * Dir. @return			Index (0-3) to specify which of the 4 triangles the line intersected, or -1 if none was found.
- L540 _macro_ `#define kDOPArray TArray`
- L542 _namespace_ `namespace BoxTriangleIntersectionInternal` (scope `Lightmass`)
- L556 _function_ `FORCEINLINE FOverlapInterval GetInterval(const FTriangle& Triangle, const FVector3f& Vector)` (scope `Lightmass::BoxTriangleIntersectionInternal`)
- L571 _function_ `FORCEINLINE FOverlapInterval GetInterval(const FBox3f& Box, const FVector3f& Vector)` (scope `Lightmass::BoxTriangleIntersectionInternal`)
- L598 _function_ `FORCEINLINE bool OverlapOnAxis(const FBox3f& Box, const FTriangle& Triangle, const FVector3f& Vector)` (scope `Lightmass::BoxTriangleIntersectionInternal`)
- L605 _function_ `FORCEINLINE bool IntersectTriangleAndAABB(const FTriangle& Triangle, const FBox3f& Box)` (scope `Lightmass::BoxTriangleIntersectionInternal`)
- L675 _member_ `KDOP_IDX_TYPE LeftNode;` (scope `Lightmass::TkDOPNode::__anon1709d256030a::__anon1709d2560408`)
- L676 _member_ `KDOP_IDX_TYPE RightNode;` (scope `Lightmass::TkDOPNode::__anon1709d256030a::__anon1709d2560408`)
- L677 _member_ `} n;` (scope `Lightmass::TkDOPNode::__anon1709d256030a`)
- L684 _member_ `KDOP_IDX_TYPE NumTriangles;` (scope `Lightmass::TkDOPNode::__anon1709d256030a::__anon1709d2560508`)
- L685 _member_ `KDOP_IDX_TYPE StartIndex;` (scope `Lightmass::TkDOPNode::__anon1709d256030a::__anon1709d2560508`)
- L686 _member_ `} t;` (scope `Lightmass::TkDOPNode::__anon1709d256030a`)
- L720 _macro_ `#define PLAIN_C 0`

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Misc/LMDebug.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`
- L10 _externvar_ `extern FString InstigatorUserName;` (scope `Lightmass`)
- L15 _prototype_ `void appHandleCriticalError();` (scope `Lightmass`) — Handles critical error. The call only performs anything on the first call.
- L20 _prototype_ `const class FString& appGetCrashReporterURL();` (scope `Lightmass`) — Returns the crash reporter URL after appHandleCriticalError() has been called.

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Misc/LMHelpers.h` (Private)


#### class `Lightmass::FLightmassLog`  
`class FLightmassLog : public FOutputDevice`  
_L10-42_
- inherits: `FOutputDevice`
- L14 _public prototype_ `FLightmassLog();`
- L15 _public prototype_ `~FLightmassLog();`
- L18 _public prototype_ `virtual void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category ) override;` — BEGIN FOutputDevice Interface
- L19 _public prototype_ `virtual void Flush() override;`
- L25 _public function_ `const TCHAR* GetLogFilename() const` — Returns the filename of the log file.
- L33 _public prototype_ `static FLightmassLog* Get();` — Singleton interface.
- L38 _private member_ `FArchive* File;` — Handle to log file
- L41 _private member_ `FString Filename;` — Filename of the log file.

#### class `Lightmass::FSHAHash`  
`class FSHAHash`  
_L45-69_
- desc: Stores an SHA hash generated by FSHA1.
- L48 _public member_ `uint8 Hash[20];`
- L50 _public function_ `inline FString ToString() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`
- L55 _function_ `friend bool operator==(const FSHAHash& X, const FSHAHash& Y)` (scope `Lightmass`)
- L60 _function_ `friend bool operator!=(const FSHAHash& X, const FSHAHash& Y)` (scope `Lightmass`)
- L65 _function_ `friend uint32 GetTypeHash(const FSHAHash& H)` (scope `Lightmass`)

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Misc/LMStats.h` (Private)


#### struct `Lightmass::FRDTSCCycleTimer`  
`struct FRDTSCCycleTimer`  
_L39-138_
- desc: Helper class encapsulating using RDTSC to read the CPU time stamp on x86 CPUs. Limitations: - the cycle counts used cannot be compared with cycle counts from other threads - this won't work right if the OS decides to change the CPU a task is being executed - spread spectrum frequency modulation as required by the FCC is going to add some noise - newer CPUs implement RDTSC as bus clock * multiplier to avoid the above, limiting accuracy Even with all those caveats it is sometimes useful to have a very high resolution timer for low level optimizations to accurately measure the impact of optimizations in cases where there is no reliable reproduction case to benchmark like e.g. gameplay. @warning: do not use outside temporary profiling
- L46 _public function_ `FRDTSCCycleTimer( int64 InOverhead = -1 ) : PreviousCycles(0) , Cycles(0) , Calls(0) , Overhead( InOverhead )` — Constructor, initializing cycle counter and potentially overhead @param	InOverhead	Overhead in cycles or -1 if it should be determined programatically
- L75 _public function_ `void Reset()` — Resets the state of the timer.
- L85 _public function_ `void FORCEINLINE Start()` — Starts the timer capture. This is a very lightweight operation.
- L95 _public function_ `void FORCEINLINE Stop()` — Stops the timer capture. This is a very lightweight operation.
- L116 _public function_ `int64 GetCycleCount()` — @return	number of CPU cycles elapsed while the timer was active
- L124 _public function_ `int64 GetCallCount()` — @return	number of times timer has been started/ stopped
- L131 _private member_ `int64 PreviousCycles;` — Previous cycles, used to warm cache and to avoid negative delta times.
- L133 _private member_ `int64 Cycles;` — Cycle counter used to keep track of timer duration.
- L135 _private member_ `int64 Calls;` — Number of callst o the cycle counter.
- L137 _private member_ `int64 Overhead;` — Timing overhead in cycles. Factored out during capture.

#### class `Lightmass::FScopedRDTSCTimer`  
`class FScopedRDTSCTimer`  
_L152-172_
- L156 _public function_ `FScopedRDTSCTimer(float& InValue) : Timer(0), Value(InValue)`
- L163 _public function_ `~FScopedRDTSCTimer()`
- L170 _private member_ `FRDTSCCycleTimer Timer;`
- L171 _private member_ `float& Value;`

#### class `Lightmass::FManualRDTSCTimer`  
`class FManualRDTSCTimer`  
_L174-200_
- L178 _public function_ `FManualRDTSCTimer(float& InValue) : Timer(0), Value(InValue)`
- L185 _public function_ `void Stop()`
- L191 _public function_ `~FManualRDTSCTimer()`
- L198 _private member_ `FRDTSCCycleTimer Timer;`
- L199 _private member_ `float& Value;`

#### Free symbols / members of external scopes

- L12 _function_ `inline unsigned long long __rdtsc()`
- L21 _namespace_ `namespace Lightmass`
- L141 _externvar_ `extern double CPUFrequency ;` (scope `Lightmass`) — CPU frequency for stats, only used for inner loop timing with rdtsc.
- L144 _externvar_ `extern double GSecondPerCPUCycle ;` (scope `Lightmass`) — Number of CPU clock cycles per second (as counted by __rdtsc).
- L147 _prototype_ `void StartInitCPUFrequency();` (scope `Lightmass`) — Start initializing CPU frequency (as counted by __rdtsc).
- L150 _prototype_ `void FinishInitCPUFrequency();` (scope `Lightmass`) — Finishe initializing CPU frequency (as counted by __rdtsc), and set up CPUFrequency and CPUCyclesPerSecond.

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Misc/LMThreading.h` (Private)


#### class `Lightmass::FSemaphore`  
`class FSemaphore`  
_L21-75_
- desc: This is the Windows version of a semaphore. It works like a thread-safe counter which is considered 'signaled' when non-zero. Trigger() will increment the counter and a successful Wait() will decrement it.
- L27 _public prototype_ `FSemaphore(void);` — Constructor that zeroes the handle
- L32 _public prototype_ `virtual ~FSemaphore(void);` — Cleans up the handle if valid
- L42 _public prototype_ `virtual bool Create(int32 MaxCount);` — Creates the semaphore. Named events share the same underlying event. @apram MaxCount Maximum value of the semaphore. The semaphore will always be [0..MaxCount]. @return Returns true if the event was created, false otherwise
- L48 _public prototype_ `virtual void Trigger(void);` — Increments the semaphore by 1. If multiple threads are waiting, one of them will be released.
- L59 _public prototype_ `virtual bool Wait(uint32 WaitTime = (uint32)-1);` — Waits for the semaphore to be signaled (non-zero value). Upon return, decrement the semaphore by 1 (unless the timeout was reached). @param WaitTime Time in milliseconds to wait before abandoning the event (uint32)-1 is treated as wait infinite @return true if the semaphore was signaled, false if the wait timed out
- L66 _protected member_ `Windows::HANDLE Semaphore;`

#### class `Lightmass::TQueueThreadSafe`  
`template <typename ElementType> class TQueueThreadSafe : private TQueue<ElementType>`  
_L81-136_
- inherits: `TQueue<ElementType>`
- desc: Thread-safe FIFO queue with a fixed maximum size.
- L88 _public function_ `TQueueThreadSafe( int32 InMaxNumElements ) : TQueue<ElementType>( InMaxNumElements )` — Constructor, allocates the buffer. @param InMaxNumElements	- Maximum number of elements in the queue
- L97 _public function_ `volatile int32 Num() const` — Returns the current number of elements stored in the queue. @return	- Current number of elements stored in the queue
- L106 _public function_ `volatile int32 GetMaxNumElements() const` — Returns the maximum number of elements that can be stored in the queue. @return	- Maximum number of elements that can be stored in the queue
- L116 _public function_ `bool Push( const ElementType& Element )` — Adds an element to the head of the queue. @param Element	- Element to be added @return			- true if the element got added, false if the queue was already full
- L127 _public function_ `bool Pop( ElementType& Element )` — Removes and returns the tail of the queue (the 'oldest' element). @param Element	- [out] If successful, contains the element that was removed @return			- true if the element got removed, false if the queue was empty
- L135 _protected member_ `FCriticalSection CriticalSecion;` — Used for synchronizing access to the queue.

#### class `Lightmass::TProducerConsumerQueue`  
`template <typename ElementType> class TProducerConsumerQueue : private TQueueThreadSafe<ElementType>`  
_L144-217_
- inherits: `TQueueThreadSafe<ElementType>`
- desc: Thread-safe Producer/Consumer FIFO queue with a fixed maximum size. It supports multiple producers and multiple consumers.
- L151 _public function_ `TProducerConsumerQueue( int32 InMaxNumElements ) : TQueueThreadSafe<ElementType>( InMaxNumElements )` — Constructor, allocates the buffer. @param InMaxNumElements	- Maximum number of elements in the queue
- L161 _public function_ `volatile int32 Num() const` — Returns the current number of elements stored in the queue. @return	- Current number of elements stored in the queue
- L170 _public function_ `volatile int32 GetMaxNumElements() const` — Returns the maximum number of elements that can be stored in the queue. @return	- Maximum number of elements that can be stored in the queue
- L181 _public function_ `bool Push( const ElementType& Element )` — Adds an element to the head of the queue. @param Element	- Element to be added @return			- true if the element got added, false if the queue was already full
- L199 _public function_ `bool Pop( ElementType& Element, uint32 Timeout )` — Removes and returns the tail of the queue (the 'oldest' element). If the queue is empty, wait for an element to come in. @param Element	- [out] If successful, contains the element that was removed @param Timeout	- How long to wait for new elements if the queue is empty, in milliseconds. -1 means INFINITE. @return			- true if the element got removed, false if the queue was empty
- L206 _public function_ `void TriggerAll()` — Bumps the semaphore to maximum, to release up to 'MaxNumElements' waiting threads right away.
- L216 _protected member_ `FSemaphore Semaphore;` — Used for blocking Pops. The count represents the current number of elements in the queue.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Private/LightmassCore/Templates/LMQueue.h` (Private)


#### class `Lightmass::TQueue`  
`template <typename ElementType> class TQueue`  
_L15-108_
- desc: FIFO queue with a fixed maximum size.
- L22 _public function_ `TQueue( int32 InMaxNumElements ) : HeadIndex(0) , TailIndex(0) , NumElements(0) , MaxNumElements( InMaxNumElements )` — Constructor, allocates the buffer. @param InMaxNumElements	- Maximum number of elements in the queue
- L34 _public function_ `~TQueue()` — Destructor, frees the buffer.
- L43 _public function_ `int32 Num() const` — Returns the current number of elements stored in the queue. @return	- Current number of elements stored in the queue
- L52 _public function_ `int32 GetMaxNumElements() const` — Returns the maximum number of elements that can be stored in the queue. @return	- Maximum number of elements that can be stored in the queue
- L62 _public function_ `bool Push( const ElementType& Element )` — Adds an element to the head of the queue. @param Element	- Element to be added @return			- true if the element got added, false if the queue was already full
- L82 _public function_ `bool Pop( ElementType& Element )` — Removes and returns the tail of the queue (the 'oldest' element). @param Element	- [out] If successful, contains the element that was removed @return			- true if the element got removed, false if the queue was empty
- L99 _protected member_ `int32 HeadIndex;` — Index to where a new element will be added (the head of the queue).
- L101 _protected member_ `int32 TailIndex;` — Index to the least recently added element (the tail of the queue).
- L103 _protected member_ `int32 NumElements;` — Current number of elements stored in the queue.
- L105 _protected member_ `const int32 MaxNumElements;` — Maximum number of elements that can be stored in the queue.
- L107 _protected member_ `ElementType* Elements;` — Array of elements. The allocated size is MaxNumElements.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Public/FluidExport.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Public/ImportExport.h` (Public)


#### enum `Lightmass::ESourceObjectType`  
`enum ESourceObjectType`  
_L92-104_
- desc: Alert source object type identifiers...
- L94 _public enumerator_ `SOURCEOBJECTTYPE_Unknown = 0`
- L95 _public enumerator_ `SOURCEOBJECTTYPE_Scene`
- L96 _public enumerator_ `SOURCEOBJECTTYPE_Material`
- L97 _public enumerator_ `SOURCEOBJECTTYPE_BSP`
- L98 _public enumerator_ `SOURCEOBJECTTYPE_StaticMesh`
- L99 _public enumerator_ `SOURCEOBJECTTYPE_Fluid`
- L100 _public enumerator_ `SOURCEOBJECTTYPE_SpeedTree`
- L101 _public enumerator_ `SOURCEOBJECTTYPE_TextureMapping`
- L102 _public enumerator_ `SOURCEOBJECTTYPE_VertexMapping`
- L103 _public enumerator_ `SOURCEOBJECTTYPE_Mapping`

#### struct `Lightmass::FLightSampleData`  
`struct FLightSampleData`  
_L114-153_
- desc: Incident lighting for a single sample, as produced by a lighting build. FGatheredLightSample is used for gathering lighting instead of this format as FLightSampleData is not additive.
- L116 _public function_ `FLightSampleData()`
- L131 _public member_ `float Coefficients[LM_NUM_STORED_LIGHTMAP_COEF][3];` — Coefficients[0] stores the normalized average color, Coefficients[1] stores the maximum color component in each lightmap basis direction, and Coefficients[2] stores the simple lightmap which is colored incident lighting along the vertex normal.
- L133 _public member_ `float SkyOcclusion[3];`
- L135 _public member_ `float AOMaterialMask;`
- L138 _public member_ `bool bIsMapped;` — True if this sample maps to a valid point on a triangle.  This is only meaningful for texture lightmaps.
- L145 _public function_ `FColor GetColor(int32 Component) const` — Export helper @param Component Which directional lightmap component to retrieve @return An FColor for this component, clamped to White

#### class `Lightmass::FLightSample`  
`class FLightSample : public FLightSampleData`  
_L156-162_
- inherits: `FLightSampleData`
- desc: The light incident for a point on a surface.
- L160 _public function_ `FLightSample() : FLightSampleData()` — Initialization constructor.
- L161 _public function_ `FLightSample(EForceInit) : FLightSampleData()`

#### struct `Lightmass::FQuantizedLightSampleData`  
`struct FQuantizedLightSampleData`  
_L167-173_
- desc: The quantized coefficients for a single light-map texel.
- L169 _public member_ `uint8 Coverage;`
- L170 _public member_ `uint8 Coefficients[LM_NUM_STORED_LIGHTMAP_COEF][4];`
- L171 _public member_ `uint8 SkyOcclusion[4];`
- L172 _public member_ `uint8 AOMaterialMask;`

#### struct `Lightmass::FLightMapDataBase`  
`struct FLightMapDataBase`  
_L175-188_
- L178 _public member_ `uint32 CompressedDataSize;` — Size of compressed lightmap data
- L181 _public member_ `uint32 UncompressedDataSize;` — Size of uncompressed lightmap data
- L184 _public member_ `float Multiply[LM_NUM_STORED_LIGHTMAP_COEF][4];` — Scale applied to the quantized light samples
- L187 _public member_ `float Add[LM_NUM_STORED_LIGHTMAP_COEF][4];` — Bias applied to the quantized light samples

#### struct `Lightmass::FLightMapData2DData`  
`struct FLightMapData2DData : public FLightMapDataBase`  
_L191-205_
- inherits: `FLightMapDataBase`
- desc: LightMap data 2D
- L193 _public function_ `FLightMapData2DData(uint32 InSizeX,uint32 InSizeY): SizeX(InSizeX), SizeY(InSizeY), bHasSkyShadowing(false)`
- L201 _public member_ `uint32 SizeX;` — The width of the light-map.
- L203 _public member_ `uint32 SizeY;` — The height of the light-map.
- L204 _public member_ `bool bHasSkyShadowing;`

#### struct `Lightmass::FShadowMapDataBase`  
`struct FShadowMapDataBase`  
_L207-214_
- L210 _public member_ `uint32 CompressedDataSize;` — Size of compressed shadowmap data
- L213 _public member_ `uint32 UncompressedDataSize;` — Size of uncompressed shadowmap data

#### struct `Lightmass::FShadowSampleData`  
`struct FShadowSampleData`  
_L217-235_
- desc: A sample of the visibility factor between a light and a single point.
- L220 _public member_ `float Visibility;` — The fraction of light that reaches this point from the light, between 0 and 1.
- L222 _public member_ `bool bIsMapped;` — True if this sample maps to a valid point on a surface.
- L229 _public function_ `FColor GetColor(int32 Component) const` — Export helper @param Component Which directional lightmap component to retrieve @return An FColor for this component, clamped to White

#### struct `Lightmass::FQuantizedShadowSampleData`  
`struct FQuantizedShadowSampleData`  
_L238-242_
- desc: The quantized value for a single shadowmap texel
- L240 _public member_ `uint8 Visibility;`
- L241 _public member_ `uint8 Coverage;`

#### struct `Lightmass::FShadowMapData2DData`  
`struct FShadowMapData2DData : public FShadowMapDataBase`  
_L245-257_
- inherits: `FShadowMapDataBase`
- desc: ShadowMap data 2D
- L247 _public function_ `FShadowMapData2DData(uint32 InSizeX,uint32 InSizeY): SizeX(InSizeX), SizeY(InSizeY)`
- L254 _public member_ `uint32 SizeX;` — The width of the shadow-map.
- L256 _public member_ `uint32 SizeY;` — The height of the shadow-map.

#### struct `Lightmass::FSignedDistanceFieldShadowSampleData`  
`struct FSignedDistanceFieldShadowSampleData`  
_L259-267_
- L262 _public member_ `float Distance;` — Normalized and encoded distance to the nearest shadow transition, in the range [0,1], where .5 is the transition.
- L264 _public member_ `float PenumbraSize;` — Normalized penumbra size, in [0,1]
- L266 _public member_ `bool bIsMapped;` — True if this sample maps to a valid point on a surface.

#### struct `Lightmass::FQuantizedSignedDistanceFieldShadowSampleData`  
`struct FQuantizedSignedDistanceFieldShadowSampleData`  
_L270-275_
- desc: The quantized value for a single signed-distance field texel
- L272 _public member_ `uint8 Distance;`
- L273 _public member_ `uint8 PenumbraSize;`
- L274 _public member_ `uint8 Coverage;`

#### struct `Lightmass::FSignedDistanceFieldShadowMapData2DData`  
`struct FSignedDistanceFieldShadowMapData2DData : public FShadowMapData2DData`  
_L278-284_
- inherits: `FShadowMapData2DData`
- desc: 2D distance field data.
- L280 _public function_ `FSignedDistanceFieldShadowMapData2DData(uint32 InSizeX,uint32 InSizeY): FShadowMapData2DData(InSizeX, InSizeY)`

#### class `Lightmass::FVolumeLightingSampleData`  
`class FVolumeLightingSampleData`  
_L287-303_
- desc: Lighting for a point in space.
- L291 _public member_ `FVector4f PositionAndRadius;` — World space position and radius.
- L294 _public member_ `float HighQualityCoefficients[LM_NUM_SH_COEFFICIENTS][3];` — SH coefficients used with high quality lightmaps.
- L297 _public member_ `float LowQualityCoefficients[LM_NUM_SH_COEFFICIENTS][3];` — SH coefficients used with low quality lightmaps.
- L299 _public member_ `FVector3f SkyBentNormal;`
- L302 _public member_ `float DirectionalLightShadowing;` — Shadow factor for the stationary directional light.

#### struct `Lightmass::FIrradianceVoxelImportProcessingData`  
`struct FIrradianceVoxelImportProcessingData`  
_L306-311_
- desc: Data used by the editor import process and not uploaded into textures.
- L308 _public member_ `bool bInsideGeometry;`
- L309 _public member_ `bool bBorderVoxel;`
- L310 _public member_ `float ClosestGeometryDistance;`

#### class `Lightmass::FStaticShadowDepthMapSampleData`  
`class FStaticShadowDepthMapSampleData`  
_L314-318_
- L317 _public member_ `FFloat16 Distance;`

#### class `Lightmass::FStaticShadowDepthMapData`  
`class FStaticShadowDepthMapData`  
_L320-328_
- L324 _public member_ `FMatrix44f WorldToLight;` — Transform from world space to the coordinate space that FStaticShadowDepthMapSampleData's are stored in.
- L326 _public member_ `int32 ShadowMapSizeX;` — Dimensions of the generated shadow map.
- L327 _public member_ `int32 ShadowMapSizeY;`

#### class `Lightmass::FMeshAreaLightData`  
`class FMeshAreaLightData`  
_L334-345_
- L337 _public member_ `FGuid LevelGuid;`
- L338 _public member_ `FVector4f Position;`
- L339 _public member_ `FVector4f Direction;`
- L340 _public member_ `float Radius;`
- L341 _public member_ `float ConeAngle;`
- L342 _public member_ `FColor Color;`
- L343 _public member_ `float Brightness;`
- L344 _public member_ `float FalloffExponent;`

#### struct `Lightmass::FDebugStaticLightingRay`  
`struct FDebugStaticLightingRay`  
_L352-366_
- L354 _public member_ `FVector4f Start;`
- L355 _public member_ `FVector4f End;`
- L356 _public member_ `bool bHit;`
- L357 _public member_ `bool bPositive;`
- L359 _public function_ `FDebugStaticLightingRay()`
- L360 _public function_ `FDebugStaticLightingRay(const FVector4f& InStart, const FVector4f& InEnd, bool bInHit, bool bInPositive = false) : Start(InStart), End(InEnd), bHit(bInHit), bPositive(bInPositive)`

#### struct `Lightmass::FDebugStaticLightingVertex`  
`struct FDebugStaticLightingVertex`  
_L368-372_
- L370 _public member_ `FVector4f VertexNormal;`
- L371 _public member_ `FVector4f VertexPosition;`

#### struct `Lightmass::FDebugLightingCacheRecord`  
`struct FDebugLightingCacheRecord`  
_L374-386_
- L376 _public member_ `bool bNearSelectedTexel;`
- L377 _public member_ `bool bAffectsSelectedTexel;`
- L378 _public member_ `int32 RecordId;`
- L379 _public member_ `FDebugStaticLightingVertex Vertex;`
- L380 _public member_ `float Radius;`
- L382 _public function_ `FDebugLightingCacheRecord() : bNearSelectedTexel(false), bAffectsSelectedTexel(false)`

#### struct `Lightmass::FDebugPhoton`  
`struct FDebugPhoton`  
_L388-405_
- L390 _public member_ `int32 Id;`
- L391 _public member_ `FVector4f Position;`
- L392 _public member_ `FVector4f Direction;`
- L393 _public member_ `FVector4f Normal;`
- L395 _public function_ `FDebugPhoton() : Id(-1)`
- L399 _public function_ `FDebugPhoton(int32 InId, const FVector4f& InPosition, const FVector4f& InDirection, const FVector4f& InNormal) : Id(InId), Position(InPosition), Direction(InDirection), Normal(InNormal)`

#### struct `Lightmass::FDebugOctreeNode`  
`struct FDebugOctreeNode`  
_L407-416_
- L409 _public member_ `FVector4f Center;`
- L410 _public member_ `FVector4f Extent;`
- L412 _public function_ `FDebugOctreeNode(const FVector4f& InCenter, const FVector4f& InExtent) : Center(InCenter), Extent(InExtent)`

#### struct `Lightmass::FDebugLightingOutput`  
`struct FDebugLightingOutput`  
_L424-472_
- desc: Debug output from the static lighting build.
- L427 _public member_ `bool bValid;` — Whether the debug output is valid.
- L429 _public member_ `TArray<FDebugStaticLightingRay> PathRays;` — Final gather, hemisphere sample and path rays
- L431 _public member_ `TArray<FDebugStaticLightingRay> ShadowRays;` — Area shadow rays
- L433 _public member_ `TArray<FDebugStaticLightingRay> IndirectPhotonPaths;` — Photon paths used for guiding indirect photon emission
- L435 _public member_ `TArray<int32> SelectedVertexIndices;` — Indices into Vertices of the selected sample's vertices
- L437 _public member_ `TArray<FDebugStaticLightingVertex> Vertices;` — Vertices near the selected sample
- L439 _public member_ `TArray<FDebugLightingCacheRecord> CacheRecords;` — Lighting cache records
- L441 _public member_ `TArray<FDebugPhoton> DirectPhotons;` — Photons in the direct photon map
- L443 _public member_ `TArray<FDebugPhoton> IndirectPhotons;` — Photons in the indirect photon map
- L445 _public member_ `TArray<FDebugPhoton> IrradiancePhotons;` — Photons in the irradiance photon map
- L447 _public member_ `TArray<FDebugPhoton> GatheredPhotons;` — Normal and irradiance photons that were gathered for the selected sample
- L449 _public member_ `TArray<FDebugPhoton> GatheredImportancePhotons;` — Importance photons that were gathered for the selected sample
- L451 _public member_ `TArray<FDebugOctreeNode> GatheredPhotonNodes;` — Photon map octree nodes gathered during a photon map search.
- L453 _public member_ `bool bDirectPhotonValid;` — Whether GatheredDirectPhoton is valid
- L455 _public member_ `FDebugPhoton GatheredDirectPhoton;` — Direct photon that was found during direct lighting.
- L457 _public member_ `FVector4f TexelCorners[NumTexelCorners];` — Positions of the selected texel's corners
- L459 _public member_ `bool bCornerValid[NumTexelCorners];` — Whether each of the selected texel's corners were valid
- L461 _public member_ `float SampleRadius;` — World space radius of the selected sample
- L463 _public function_ `FDebugLightingOutput() : bValid(false), bDirectPhotonValid(false)`

#### struct `Lightmass::FDebugVolumeLightingSample`  
`struct FDebugVolumeLightingSample`  
_L474-483_
- L476 _public member_ `FVector4f PositionAndRadius;`
- L477 _public member_ `FLinearColor AverageIncidentRadiance;`
- L479 _public function_ `FDebugVolumeLightingSample(const FVector4f& InPositionAndRadius, const FLinearColor& InAverageIncidentRadiance) : PositionAndRadius(InPositionAndRadius), AverageIncidentRadiance(InAverageIncidentRadiance)`

#### struct `Lightmass::FVolumeLightingDebugOutput`  
`struct FVolumeLightingDebugOutput`  
_L485-488_
- L487 _public member_ `TArray<FDebugVolumeLightingSample> VolumeLightingSamples;`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace Lightmass`
- L40 _macro_ `#define LM_COMPRESS_INPUT_DATA 1` — Whether or not to request compression on heavyweight input file types
- L42 _macro_ `#define LM_NUM_SH_COEFFICIENTS 9`
- L45 _variable_ `static const int32 LM_NUM_STORED_LIGHTMAP_COEF = 4;` (scope `Lightmass`) — The number of coefficients that are stored for each light sample.
- L47 _variable_ `static const int32 LM_NUM_HQ_LIGHTMAP_COEF = 2;` (scope `Lightmass`) — The number of high quality coefficients which the lightmap stores for each light sample.
- L49 _variable_ `static const int32 LM_LQ_LIGHTMAP_COEF_INDEX = 2;` (scope `Lightmass`) — The index at which low quality coefficients are stored in any array containing all LM_NUM_STORED_LIGHTMAP_COEF coefficients.
- L52 _variable_ `static const TCHAR LM_TEXTUREMAPPING_EXTENSION[] = TEXT("tma` (scope `Lightmass`) — Output channel types (extensions)
- L53 _variable_ `static const TCHAR LM_VOLUMESAMPLES_EXTENSION[] = TEXT("vol` (scope `Lightmass`)
- L54 _variable_ `static const TCHAR LM_VOLUMEDEBUGOUTPUT_EXTENSION[] = TEXT("vol` (scope `Lightmass`)
- L55 _variable_ `static const TCHAR LM_VOLUMETRICLIGHTMAP_EXTENSION[] = TEXT("irv` (scope `Lightmass`)
- L56 _variable_ `static const TCHAR LM_PRECOMPUTEDVISIBILITY_EXTENSION[] = TEXT("vis` (scope `Lightmass`)
- L57 _variable_ `static const TCHAR LM_DOMINANTSHADOW_EXTENSION[] = TEXT("dom` (scope `Lightmass`)
- L58 _variable_ `static const TCHAR LM_MESHAREALIGHTDATA_EXTENSION[] = TEXT("are` (scope `Lightmass`)
- L59 _variable_ `static const TCHAR LM_DEBUGOUTPUT_EXTENSION[] = TEXT("dbg` (scope `Lightmass`)
- L63 _variable_ `static const TCHAR LM_SCENE_EXTENSION[] = TEXT("sce` (scope `Lightmass`)
- L64 _variable_ `static const TCHAR LM_STATICMESH_EXTENSION[] = TEXT("mes` (scope `Lightmass`)
- L65 _variable_ `static const TCHAR LM_MATERIAL_EXTENSION[] = TEXT("mtr` (scope `Lightmass`)
- L78 _variable_ `static const int32 LM_TEXTUREMAPPING_VERSION = 2;` (scope `Lightmass`)
- L79 _variable_ `static const int32 LM_VOLUMESAMPLES_VERSION = 2;` (scope `Lightmass`)
- L80 _variable_ `static const int32 LM_VOLUMETRICLIGHTMAP_VERSION = 4;` (scope `Lightmass`)
- L81 _variable_ `static const int32 LM_PRECOMPUTEDVISIBILITY_VERSION = 2;` (scope `Lightmass`)
- L82 _variable_ `static const int32 LM_VOLUMEDEBUGOUTPUT_VERSION = 2;` (scope `Lightmass`)
- L83 _variable_ `static const int32 LM_DOMINANTSHADOW_VERSION = 2;` (scope `Lightmass`)
- L84 _variable_ `static const int32 LM_MESHAREALIGHTDATA_VERSION = 2;` (scope `Lightmass`)
- L85 _variable_ `static const int32 LM_DEBUGOUTPUT_VERSION = 2;` (scope `Lightmass`)
- L86 _variable_ `static const int32 LM_SCENE_VERSION = 2;` (scope `Lightmass`)
- L87 _variable_ `static const int32 LM_STATICMESH_VERSION = 2;` (scope `Lightmass`)
- L88 _variable_ `static const int32 LM_MATERIAL_VERSION = 2;` (scope `Lightmass`)
- L330 _variable_ `static const FGuid MeshAreaLightDataGuid = FGuid(0xe11f4760, 0xfa454d2b, 0xa090c388, 0x33326646);` (scope `Lightmass`)
- L332 _variable_ `static const FGuid VolumeDistanceFieldGuid = FGuid(0x4abf306e, 0x4c2f4a6e, 0x9feb5fa4, 0x5b910a8f);` (scope `Lightmass`)
- L419 _variable_ `static const FGuid DebugOutputGuid = FGuid(0x23219c9e, 0xb5934266, 0xb2144a7d, 0x3448abac);` (scope `Lightmass`) — Guid used by Unreal to determine when the debug channel with the same Guid can be opened.
- L491 _variable_ `static const FGuid VolumeLightingDebugOutputGuid = FGuid(0x1e8119ff, 0xa46f48f8, 0x92b18d49, 0x172c5832);` (scope `Lightmass`) — Guid used by Unreal to determine when the volume lighting debug channel with the same Guid can be opened.
- L493 _variable_ `static const FGuid PrecomputedVolumeLightingGuid = FGuid(0xce97c5c3, 0xab614fd3, 0xb2da55c0, 0xe6c33fb4);` (scope `Lightmass`) — Guid used by Unreal to determine when the volume lighting sample channel with the same Guid can be opened.
- L509 _function_ `inline FString CreateChannelNameWithLMExecutableHash(const FGuid& Guid, const int32 Version, const FSHAHash& LMExecutableHash, const FString& Extension)` (scope `Lightmass`) — Creates a standardized channel name based on Guid, version and type @param Guid Unique ID of the channel @param Version Version of the data inside @param LMExecutableHash Hash of UnrealLightmass executable, to avoid stale cache content from a different build @param Extension Type of the data @return Standard channel name
- L513 _function_ `inline FString CreateChannelName(const FGuid& Guid, const int32 Version, const FString& Extension)` (scope `Lightmass`)
- L528 _function_ `inline FString CreateChannelNameWithLMExecutableHash(const FSHAHash& Hash, const int32 Version, const FSHAHash& LMExecutableHash, const FString& Extension)` (scope `Lightmass`) — Creates a standardized channel name based a FSA Hash, version and type. Used for exporting materials @param Hash Unique ID of the channel @param Version Version of the data inside @param LMExecutableHash Hash of UnrealLightmass executable, to avoid stale cache content from a different build @param Extension Type of the data @return Standard channel name

### `Source/Programs/UnrealLightmass/Public/LightmassPublic.h` (Public)
_(no declarations extracted)_

### `Source/Programs/UnrealLightmass/Public/MaterialExport.h` (Public)


#### struct `Lightmass::FMaterialFileHeader`  
`struct FMaterialFileHeader`  
_L23-28_
- L26 _public member_ `uint32 Cookie;` — FourCC cookie: 'MTRL'
- L27 _public member_ `FGuid FormatVersion;`

#### struct `Lightmass::FBaseMaterialData`  
`struct FBaseMaterialData`  
_L33-36_
- L35 _public member_ `FGuid Guid;`

#### enum `Lightmass::EBlendMode`  
`enum EBlendMode`  
_L45-58_
- desc: Material blend mode. MUST MATCH UNREAL EXACTLY!!!
- L47 _public enumerator_ `BLEND_Opaque =0`
- L48 _public enumerator_ `BLEND_Masked =1`
- L49 _public enumerator_ `BLEND_Translucent =2`
- L50 _public enumerator_ `BLEND_Additive =3`
- L51 _public enumerator_ `BLEND_Modulate =4`
- L52 _public enumerator_ `BLEND_AlphaComposite =5`
- L53 _public enumerator_ `BLEND_AlphaHoldout =6`
- L54 _public enumerator_ `BLEND_TranslucentColoredTransmittance =7`
- L55 _public enumerator_ `BLEND_MAX =8` — BLEND_TranslucentColoredTransmittance =7,					 Substrate only
- L56 _public enumerator_ `BLEND_TranslucentGreyTransmittance = BLEND_Translucent`
- L57 _public enumerator_ `BLEND_ColoredTransmittanceOnly = BLEND_Modulate` — BLEND_TranslucentGreyTransmittance    = BLEND_Translucent,	 Substrate only

#### struct `Lightmass::FMaterialData`  
`struct FMaterialData`  
_L60-95_
- L63 _public member_ `EBlendMode BlendMode;` — The BLEND mode of the material
- L65 _public member_ `uint32 bTwoSided:1;` — Whether the material is two-sided or not
- L67 _public member_ `uint32 bIsThinSurface: 1;` — Whether the material is thin-surface or not
- L69 _public member_ `uint32 bCastShadowAsMasked:1;` — Whether the material should cast shadows as masked even though it has a translucent blend mode.
- L70 _public member_ `uint32 bSurfaceDomain:1;`
- L72 _public member_ `float EmissiveBoost;` — Scales the emissive contribution for this material.
- L74 _public member_ `float DiffuseBoost;` — Scales the diffuse contribution for this material.
- L76 _public member_ `float OpacityMaskClipValue;` — The clip value for masked rendering
- L81 _public member_ `int32 EmissiveSize;` — The sizes of the material property samples
- L82 _public member_ `int32 DiffuseSize;`
- L83 _public member_ `int32 TransmissionSize;`
- L84 _public member_ `int32 NormalSize;`
- L86 _public function_ `FMaterialData() : EmissiveBoost(1.0f) , DiffuseBoost(1.0f) , EmissiveSize(0) , DiffuseSize(0) , TransmissionSize(0) , NormalSize(0)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Lightmass`

### `Source/Programs/UnrealLightmass/Public/MeshExport.h` (Public)


#### enum `Lightmass::(anonymous)`  
`enum`  
_L16-16_

#### struct `Lightmass::FMeshFileHeader`  
`struct FMeshFileHeader`  
_L30-51_
- L33 _public member_ `uint32 Cookie;` — FourCC cookie: 'MESH'
- L34 _public member_ `FGuid FormatVersion;`

#### struct `Lightmass::FBaseMeshData`  
`struct FBaseMeshData`  
_L57-60_
- L59 _public member_ `FGuid Guid;`

#### struct `Lightmass::FStaticMeshData`  
`struct FStaticMeshData`  
_L65-69_
- L67 _public member_ `uint32 LightmapCoordinateIndex;`
- L68 _public member_ `uint32 NumLODs;`

#### struct `Lightmass::FStaticMeshLODData`  
`struct FStaticMeshLODData`  
_L74-83_
- L76 _public member_ `uint32 NumElements;`
- L78 _public member_ `uint32 NumTriangles;` — Total number of triangles for all elements in the LOD.
- L80 _public member_ `uint32 NumIndices;` — Total number of indices in the LOD.
- L82 _public member_ `uint32 NumVertices;` — Total number of vertices in the LOD.

#### struct `Lightmass::FStaticMeshElementData`  
`struct FStaticMeshElementData`  
_L88-93_
- L90 _public member_ `uint32 FirstIndex;`
- L91 _public member_ `uint32 NumTriangles;`
- L92 _public member_ `uint32 bEnableShadowCasting : 1;`

#### struct `Lightmass::FStaticMeshVertex`  
`struct FStaticMeshVertex`  
_L98-105_
- L100 _public member_ `FVector4f Position;`
- L101 _public member_ `FVector4f TangentX;`
- L102 _public member_ `FVector4f TangentY;`
- L103 _public member_ `FVector4f TangentZ;`
- L104 _public member_ `FVector2f UVs[MAX_TEXCOORDS];`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Lightmass`
- L16 _enumerator_ `enum { MAX_TEXCOORDS=4 }; #if !PLATFORM_MAC && !PLATFORM_LINUX #pragma pack(push, 1) #endif` (scope `Lightmass::__anon601c1de50103`)

### `Source/Programs/UnrealLightmass/Public/SceneExport.h` (Public)


#### class `Lightmass::FStaticLightingSettings`  
`class FStaticLightingSettings`  
_L38-132_
- desc: General and misc solver settings. Settings prefixed by Debugging are only useful for development, Either because one of the options have been proven superior or because it produces a visualization of an intermediate result. All angles are in Radians, distances are in world space units.
- L42 _public member_ `bool bAllowMultiThreadedStaticLighting;` — Debugging - whether to allow multiple static lighting threads.
- L47 _public member_ `int32 NumUnusedLocalCores;` — Number of local cores to leave unused
- L54 _public member_ `int32 NumIndirectLightingBounces;` — Number of indirect lighting bounces to simulate, 0 is direct lighting only. The first bounce always costs the most in terms of computation time, with the second bounce following. With photon mapping, bounces after the second are nearly free.
- L60 _public member_ `int32 NumSkyLightingBounces;` — Number of skylight and emissive bounces to simulate. Lightmass uses a non-distributable radiosity method for skylight bounces whose cost is proportional to the number of bounces.
- L65 _public member_ `bool bUseEmbree;` — Whether to use Embree for ray tracing or not.
- L70 _public member_ `bool bVerifyEmbree;` — Whether to check for Embree coherency.
- L73 _public member_ `bool bUseEmbreePacketTracing;` — Whether to build Embree data structures for packet tracing. WIP feature - no lightmass algorithms emit packet tracing requests yet.
- L76 _public member_ `bool bUseFastVoxelization;` — Whether to use kDOP trees to accelerate volumetric lightmap voxelization. Useful in scenes like large forest.
- L79 _public member_ `bool bUseEmbreeInstancing;` — Whether to use static mesh instancing to reduce memory consumption in scenes like large forest. Might slow down small scenes.
- L85 _public member_ `int32 MappingSurfaceCacheDownsampleFactor;` — Direct lighting, skylight radiosity and irradiance photons are cached on mapping surfaces to accelerate final gathering. This controls the downsample factor for that cache, relative to the mapping's lightmap resolution.
- L92 _public member_ `float IndirectLightingSmoothness;` — Smoothness factor to apply to indirect lighting.  This is useful in some lighting conditions when Lightmass cannot resolve accurate indirect lighting. 1 is default smoothness tweaked for a variety of lighting situations. Higher values like 3 smooth out the indirect lighting more, but at the cost of indirect shadows losing detail as well.
- L100 _public member_ `float IndirectLightingQuality;` — Warning: Setting this higher than 1 will greatly increase build times! Can be used to increase the GI solver sample counts in order to get higher quality for levels that need it. It can be useful to reduce IndirectLightingSmoothness somewhat (~.75) when increasing quality to get defined indirect shadows. Note that this can't affect compression artifacts or other texture based artifacts.
- L107 _public member_ `int32 ViewSingleBounceNumber;` — Debugging - which single light bounce to view or -1 for all. This setting has been carefully implemented to only affect the final color and not affect any other part of the solver (sample positions, ray directions, etc). Most of the debug visualizations are affected by ViewSingleBounceNumber.
- L113 _public member_ `bool bUseConservativeTexelRasterization;` — Debugging - when enabled, multiple samples will be used to detect all the texels that are mapped to geometry. Otherwise only the center and corner of each texel will be sampled.
- L116 _public member_ `bool bAccountForTexelSize;` — Debugging - whether to use the texel size in various calculations in an attempt to compensate for point sampling a texel.
- L119 _public member_ `bool bUseMaxWeight;` — Debugging - whether to use the sample with the largest weight when rasterizing texels or a linear combination.
- L122 _public member_ `int32 MaxTriangleLightingSamples;` — Maximum lighting samples per triangle for vertex lightmaps.
- L125 _public member_ `int32 MaxTriangleIrradiancePhotonCacheSamples;` — Maximum samples for caching irradiance photons per triangle for vertex lightmaps.
- L128 _public member_ `bool bUseErrorColoring;` — Debugging - whether to color texels when invalid settings are detected.
- L131 _public member_ `FLinearColor UnmappedTexelColor;` — Unmapped texel color

#### class `Lightmass::FStaticLightingSceneConstants`  
`class FStaticLightingSceneConstants`  
_L135-179_
- desc: Scale dependent constants
- L142 _public member_ `float StaticLightingLevelScale;` — Scale of the level being lit. Games using a different scale should use this to convert the defaults into the game-specific scale.
- L148 _public member_ `float VisibilityRayOffsetDistance;` — World space distance to offset the origin of the ray, along the direction of the ray. This is used to prevent incorrect self shadowing due to floating point precision.
- L154 _public member_ `float VisibilityNormalOffsetDistance;` — World space distance to offset the origin of the ray along the direction of the normal. This is used to push triangle shaped self shadowing artifacts onto the backfaces of curved objects.
- L160 _public member_ `float VisibilityNormalOffsetSampleRadiusScale;` — Fraction of the sample radius to offset the origin of the ray along the sample normal. This is applied instead of VisibilityNormalOffsetDistance whenever sample radius is known as it adapts to differently sized texels.
- L166 _public member_ `float VisibilityTangentOffsetSampleRadiusScale;` — Fraction of the sample radius to offset the origin of the ray in the tangent XY plane, based on the direction of the ray. This is only used when bAccountForTexelSize is true.
- L172 _public member_ `float SmallestTexelRadius;` — Smallest texel radius allowed, useful for clamping edge cases where some texels have a radius of 0. This should be smaller than the smallest valid texel radius in the scene.
- L178 _public member_ `int32 LightGridSize;` — Size of the grid that each light will use to cache information. Larger grids take longer to precompute, but result in accelerated light sampling.

#### enum `Lightmass::EViewMaterialAttribute`  
`enum EViewMaterialAttribute`  
_L182-189_
- desc: Settings for which material attribute to visualize
- L184 _public enumerator_ `VMA_None`
- L185 _public enumerator_ `VMA_Emissive`
- L186 _public enumerator_ `VMA_Diffuse`
- L187 _public enumerator_ `VMA_Transmission`
- L188 _public enumerator_ `VMA_Normal`

#### struct `Lightmass::FSceneMaterialSettings`  
`struct FSceneMaterialSettings`  
_L192-223_
- desc: The scenes material settings
- L195 _public member_ `bool bUseDebugMaterial;` — Debugging - Whether to use the debug material
- L198 _public member_ `EViewMaterialAttribute ViewMaterialAttribute;` — Debugging - Indicates which material attribute to visualize.
- L201 _public member_ `int32 EmissiveSize;` — The size of the emissive sample
- L204 _public member_ `int32 DiffuseSize;` — The size of the diffuse sample
- L207 _public member_ `int32 TransmissionSize;` — The size of the Transmission sample
- L210 _public member_ `int32 NormalSize;` — The size of the normal sample
- L213 _public member_ `bool bUseNormalMapsForLighting;` — Whether to use the normal map for lighting, if false the smoothed vertex normal will be used.
- L219 _public member_ `FLinearColor DebugDiffuse;` — Debugging - Amount of incoming light to reflect diffusely (equally in all directions). This is the diffuse term in the modified Phong BRDF, not the original.
- L222 _public member_ `FLinearColor EnvironmentColor;` — Debugging - Emissive value assigned to secondary rays which miss all geometry in the scene.

#### struct `Lightmass::FMeshAreaLightSettings`  
`struct FMeshAreaLightSettings`  
_L226-251_
- desc: Settings for meshes which emit light from their emissive areas.
- L229 _public member_ `bool bVisualizeMeshAreaLightPrimitives;` — Whether to draw debug lines showing the corners of mesh area light primitives when a texel has been selected.
- L232 _public member_ `float EmissiveIntensityThreshold;` — Emissive intensities must be larger than this to contribute toward scene lighting.
- L238 _public member_ `int32 MeshAreaLightGridSize;` — Size of the grid that each mesh area light will use to cache information. Larger grids take longer to precompute, but result in accelerated light sampling.
- L241 _public member_ `float MeshAreaLightSimplifyNormalCosAngleThreshold;` — Cosine of the maximum angle allowed between mesh area light primitives that get merged into the same simplified primitive.
- L244 _public member_ `float MeshAreaLightSimplifyCornerDistanceThreshold;` — Maximum distance allowed between any mesh area light primitive corners that get merged into the same simplified primitive.
- L247 _public member_ `float MeshAreaLightSimplifyMeshBoundingRadiusFractionThreshold;` — Fraction of a mesh's bounds that an emissive texel can be from a simplified primitive and still get merged into that primitive.
- L250 _public member_ `float MeshAreaLightGeneratedDynamicLightSurfaceOffset;` — Distance along the average normal from the bounds origin of the mesh area light to place a light to handle influencing dynamic objects.

#### class `Lightmass::FAmbientOcclusionSettings`  
`class FAmbientOcclusionSettings`  
_L254-300_
- desc: AO settings
- L261 _public member_ `bool bUseAmbientOcclusion;` — Whether to calculate ambient occlusion. When enabled, some final gather rays will be traced even if only direct lighting is being calculated.
- L268 _public member_ `bool bGenerateAmbientOcclusionMaterialMask;` — Whether to generate textures storing the AO computed by Lightmass. These can be accessed through the PrecomputedAmbientOcclusion material node, Which is useful for blending between material layers on environment assets.
- L271 _public member_ `bool bVisualizeAmbientOcclusion;` — Debugging - whether to only show the ambient occlusion term, useful for seeing the impact of AO settings in isolation.
- L277 _public member_ `float DirectIlluminationOcclusionFraction;` — How much of the ambient occlusion term should be applied to direct lighting. A value of 0 will leave the direct lighting untouched, a value of 1 will apply all of the occlusion.
- L280 _public member_ `float IndirectIlluminationOcclusionFraction;` — Same as DirectIlluminationOcclusionFraction, but applied to indirect lighting.
- L287 _public member_ `float OcclusionExponent;` — Controls the ambient occlusion contrast. Higher powers result in more contrast, which effectively shorten the occlusion gradient and push it into corners. An exponent of 1 gives equivalent occlusion as the indirect shadows from a constant environment color, with no other lights in the scene.
- L293 _public member_ `float FullyOccludedSamplesFraction;` — Fraction of the samples taken that have to be occluded before an occlusion value of 1 is reached for that texel. A value of 1 means all the samples in the hemisphere have to be occluded, lower values darken areas that are not fully occluded.
- L299 _public member_ `float MaxOcclusionDistance;` — Maximum distance over which an object can affect the occlusion of a texel. Lowering this cuts off lower frequencies in the ambient occlusion.

#### class `Lightmass::FDynamicObjectSettings`  
`class FDynamicObjectSettings`  
_L303-332_
- desc: Settings related to precomputations used by dynamic objects.
- L307 _public member_ `bool bVisualizeVolumeLightSamples;` — Debugging - Whether to draw points in the editor to visualize volume lighting samples.
- L310 _public member_ `bool bVisualizeVolumeLightInterpolation;` — Debugging - Whether to interpolate indirect lighting for surfaces from the precomputed light volume.
- L313 _public member_ `float NumHemisphereSamplesScale;` — Scales the number of hemisphere samples that should be used for lighting volume samples.
- L315 _public member_ `float SurfaceLightSampleSpacing;` — World space distance between samples placed on upward facing surfaces.
- L317 _public member_ `float FirstSurfaceSampleLayerHeight;` — Height of the first sample layer above the surface.
- L319 _public member_ `float SurfaceSampleLayerHeightSpacing;` — Height difference of successive layers.
- L321 _public member_ `int32 NumSurfaceSampleLayers;` — Number of layers to place above surfaces.
- L323 _public member_ `float DetailVolumeSampleSpacing;` — Distance between samples placed in a 3d uniform grid inside detail volumes.
- L325 _public member_ `float VolumeLightSampleSpacing;` — Distance between samples placed in a 3d uniform grid inside the importance volume.
- L327 _public member_ `int32 MaxVolumeSamples;` — Maximum samples placed in the 3d volume, used to limit memory usage.
- L329 _public member_ `bool bUseMaxSurfaceSampleNum;` — Use Maximum number restriction for Surface Light Sample.
- L331 _public member_ `int32 MaxSurfaceLightSamples;` — Maximum samples placed in the surface light sample(only for Landscape currently), used to limit memory usage.

#### class `Lightmass::FVolumetricLightmapSettings`  
`class FVolumetricLightmapSettings`  
_L335-377_
- desc: Settings for the volumetric lightmap.
- L340 _public member_ `FIntVector TopLevelGridSize;` — Size of the top level grid covering the volumetric lightmap, in bricks.
- L343 _public member_ `FVector3f VolumeMin;` — World space size of the volumetric lightmap.
- L344 _public member_ `FVector3f VolumeSize;`
- L350 _public member_ `int32 BrickSize;` — Size of a brick of unique lighting data.  Must be a power of 2. Smaller values provide more granularity, but waste more memory due to padding.
- L353 _public member_ `int32 MaxRefinementLevels;` — Maximum number of times to subdivide bricks around geometry.
- L359 _public member_ `float VoxelizationCellExpansionForSurfaceGeometry;` — Fraction of a cell's size to expand it by when voxelizing. Larger values add more resolution around geometry, improving the lighting gradients but costing more memory.
- L360 _public member_ `float VoxelizationCellExpansionForVolumeGeometry;`
- L361 _public member_ `float VoxelizationCellExpansionForLights;`
- L364 _public member_ `float MinBrickError;` — Bricks with RMSE below this value are culled.
- L367 _public member_ `float SurfaceLightmapMinTexelsPerVoxelAxis;` — Triangles with fewer lightmap texels than this don't cause refinement.
- L370 _public member_ `bool bCullBricksBelowLandscape;` — Whether to cull bricks entirely below landscape.  This can be an invalid optimization if the landscape has holes and caves that pass under landscape.
- L373 _public member_ `float LightBrightnessSubdivideThreshold;` — Subdivide bricks when a static point or spot light affects some part of the brick with brightness higher than this.
- L376 _public member_ `float WindowingTargetLaplacian;` — Maximum desired curvature in the lighting stored in Volumetric Lightmaps, used to reduce Spherical Harmonic ringing via a windowing filter.

#### class `Lightmass::FPrecomputedVisibilitySettings`  
`class FPrecomputedVisibilitySettings`  
_L380-416_
- desc: Settings for precomputed visibility.
- L385 _public member_ `bool bVisualizePrecomputedVisibility;` — Whether to export debug lines for visibility.
- L388 _public member_ `bool bPlaceCellsOnOpaqueOnly;` — Whether to only place visibility cells on opaque surfaces.
- L391 _public member_ `bool bPlaceCellsOnlyAlongCameraTracks;` — Whether to place visibility cells only along camera tracks or to also include shadow casting surfaces.
- L394 _public member_ `float CellSize;` — World space size of visibility cells in the x and y dimensions.
- L397 _public member_ `int32 NumCellDistributionBuckets;` — Number of tasks that visibility cells are being split up into.
- L400 _public member_ `float PlayAreaHeight;` — World space size of visibility cells in the z dimension.
- L403 _public member_ `float MeshBoundsScale;` — Amount to increase the bounds of meshes when querying their visibility.  Larger scales reduce visibility errors at the cost of less effective culling.
- L406 _public member_ `int32 MinMeshSamples;` — Minimum number of samples on the mesh for each cell - mesh query.  Small meshes use less samples.
- L409 _public member_ `int32 MaxMeshSamples;` — Maximum number of samples on the mesh for each cell - mesh query.  Small meshes use less samples.
- L412 _public member_ `int32 NumCellSamples;` — Number of samples on each cell for each cell - mesh query.
- L415 _public member_ `int32 NumImportanceSamples;` — Number of samples to use when importance sampling each cell - mesh query.

#### class `Lightmass::FVolumeDistanceFieldSettings`  
`class FVolumeDistanceFieldSettings`  
_L419-437_
- desc: Settings for volume distance field generation.
- L424 _public member_ `float VoxelSize;` — World space size of a voxel.  Smaller values use significantly more memory and processing time, but allow more detailed shadows.
- L430 _public member_ `float VolumeMaxDistance;` — Maximum world space distance represented in the distance field, used for normalization. Larger values increase build time and decrease distance field precision, but allow distance field traversal to skip larger areas.
- L433 _public member_ `int32 NumVoxelDistanceSamples;` — Number of distance traces for each voxel.
- L436 _public member_ `int32 MaxVoxels;` — Upper limit on the number of voxels that can be generated.

#### class `Lightmass::FStaticShadowSettings`  
`class FStaticShadowSettings`  
_L440-501_
- desc: Shadow settings
- L444 _public member_ `bool bUseZeroAreaLightmapSpaceFilteredLights;` — Debugging - Whether to filter a single shadow sample per texel in texture space instead of calculating area shadows.
- L447 _public member_ `int32 NumShadowRays;` — Number of shadow rays to trace to each area light for each texel.
- L450 _public member_ `int32 NumPenumbraShadowRays;` — Number of shadow rays to trace to each area light once a texel has been determined to lie in a shadow penumbra.
- L456 _public member_ `int32 NumBounceShadowRays;` — Number of shadow rays to trace to each area light for bounced lighting. This number is divided by bounce number for successive bounces.
- L465 _public member_ `bool bFilterShadowFactor;` — Settings for enabling and adjusting a filter pass on the computed shadow factor. The shadow factor is a value [0,1] that approximates the percentage of an area light visible at a texel. A value of 0 indicates that the texel is completely in shadow and 1 indicates that it is completely lit. The tolerance value is the maximum difference in the absolute shadow factor value allowed between any two adjacent texels before enabling filtering, meant to catch shadow transitions sharper than can be captured in the lightmap.
- L466 _public member_ `float ShadowFactorGradientTolerance;`
- L469 _public member_ `bool bAllowSignedDistanceFieldShadows;` — Whether to allow signed distance field shadows, or fall back on area shadows.
- L475 _public member_ `float MaxTransitionDistanceWorldSpace;` — Maximum world space distance stored from a texel to the shadow transition. Larger distances decrease precision but increase the maximum penumbra size that can be reconstructed from the distance field.
- L481 _public member_ `int32 ApproximateHighResTexelsPerMaxTransitionDistance;` — The number of high resolution samples to calculate per MaxTransitionDistanceWorldSpace. Higher values increase the distance field reconstruction quality, at the cost of longer build times.
- L487 _public member_ `int32 MinDistanceFieldUpsampleFactor;` — The minimum upsample factor to calculate the high resolution samples at. Larger values increase distance field reconstruction quality on small, high resolution meshes, at the cost of longer build times.
- L490 _public member_ `float StaticShadowDepthMapTransitionSampleDistanceX;` — Distance in world space units between dominant light shadow map cells.
- L491 _public member_ `float StaticShadowDepthMapTransitionSampleDistanceY;`
- L494 _public member_ `int32 StaticShadowDepthMapSuperSampleFactor;` — Amount to super sample dominant shadow map generation, in each dimension.  Larger factors increase build time but produce a more conservative shadow map.
- L497 _public member_ `int32 StaticShadowDepthMapMaxSamples;` — Maximum number of dominant shadow samples to generate for one dominant light, used to limit memory used.
- L500 _public member_ `float MinUnoccludedFraction;` — Fraction of valid lighting samples (mapped texels or vertex samples) that must be unoccluded in a precomputed shadowmap for the shadowmap to be kept.

#### class `Lightmass::FImportanceTracingSettings`  
`class FImportanceTracingSettings`  
_L507-556_
- desc: Settings related to solving the light transport equation by starting from the source of importance, as opposed to starting from the source of radiant power.
- L514 _public member_ `bool bUseStratifiedSampling;` — Debugging - whether to stratify hemisphere samples, which reduces variance.
- L520 _public member_ `int32 NumHemisphereSamples;` — Number of hemisphere samples to evaluate from each irradiance cache sample when not using path tracing. When photon mapping is enabled, these are called final gather rays.
- L523 _public member_ `int32 NumAdaptiveRefinementLevels;` — Number of recursive levels allowed for adaptive refinement.  This has a huge impact on build time but also quality.
- L529 _public member_ `float MaxHemisphereRayAngle;` — Largest angle from the sample normal that a hemisphere sample direction can be. Useful for preventing rays nearly perpendicular to the normal which may self intersect a flat surface due to imprecision in the normal.
- L532 _public member_ `float AdaptiveBrightnessThreshold;` — Starting threshold for what relative brightness difference causes a refinement.  At each depth the effective threshold will be reduced.
- L535 _public member_ `float AdaptiveFirstBouncePhotonConeAngle;` — Starting threshold for what angle around a first bounce photon causes a refinement on all cells affected.  At each depth the effective threshold will be reduced.
- L537 _public member_ `float AdaptiveSkyVarianceThreshold;`
- L543 _public member_ `bool bUseRadiositySolverForSkylightMultibounce;` — Whether to use radiosity iterations for solving skylight 2nd bounce and up, plus emissive 1st bounce and up. These light sources are not represented by photons so they need to be handled separately to have multiple bounces.
- L549 _public member_ `bool bCacheFinalGatherHitPointsForRadiosity;` — Whether to cache final gather hit points for the radiosity algorithm, which reduces radiosity iteration time significantly but uses a lot of memory. Memory use is proportional to the lightmap texels in the scene and number of final gather rays.
- L555 _public member_ `bool bUseRadiositySolverForLightMultibounce;` — Whether to use radiosity iterations for point / spot / directional lights, instead of photons. Has lower quality than photons in difficult indoor scenarios but useful as a reference.

#### class `Lightmass::FPhotonMappingSettings`  
`class FPhotonMappingSettings`  
_L559-713_
- desc: Settings controlling photon mapping behavior.
- L566 _public member_ `bool bUsePhotonMapping;` — Debugging - whether to use photon mapping. Photon mapping benefits many parts of the solver so this is mainly for comparing against other methods.
- L573 _public member_ `bool bUseFinalGathering;` — Debugging - whether to estimate the first bounce lighting by tracing rays from the sample point, Which is called final gathering, or by using the density of nearby first bounce photons. Final gathering is slow but gets vastly better results than using first bounce photons.
- L579 _public member_ `bool bUsePhotonDirectLightingInFinalGather;` — Whether to use photons to represent direct lighting in final gathers. This is useful to visualize direct photons.  When false, explicitly sampled direct lighting will be used instead, which has less leaking.
- L586 _public member_ `bool bVisualizeCachedApproximateDirectLighting;` — Debugging - whether to replace direct lighting with direct lighting as seen by the final gather. This will either be direct lighting from photons, or approximate explicitly sampled direct lighting, depending on bUsePhotonDirectLightingInFinalGather. This is mainly useful for debugging what the final gather rays see.
- L589 _public member_ `bool bUseIrradiancePhotons;` — Debugging - whether to use the optimization of caching irradiance calculations in deposited photons (called Irradiance photons).
- L596 _public member_ `bool bCacheIrradiancePhotonsOnSurfaces;` — Debugging - whether to cache the result of the search for the nearest irradiance photon on surfaces. This results in a constant time lookup at the end of each final gather ray instead of a photon map search. Only visible photons are cached, which reduces light leaking.
- L602 _public member_ `bool bVisualizePhotonPaths;` — Debugging - whether to draw lines in the editor representing photon paths. They will only be drawn if a texel is selected and ViewSingleBounceNumber is >= 0.
- L608 _public member_ `bool bVisualizePhotonGathers;` — Debugging - whether to draw the photons gathered for the selected texel or the photons gathered by final gather rays from the selected texel. This includes importance, irradiance and direct photons.
- L615 _public member_ `bool bVisualizePhotonImportanceSamples;` — Debugging - whether to draw lines in the editor showing where rays were traced due to importance photons from the selected texel. If this is false, lines will be drawn for the rays traced with uniform hemisphere sampling instead. Note that when irradiance caching is enabled, rays will only be gathered if the selected texel created an irradiance cache sample.
- L621 _public member_ `bool bVisualizeIrradiancePhotonCalculation;` — Debugging - whether to gather and draw photon map octree nodes that get traversed during the irradiance calculation for the irradiance photon nearest to the select position. Which photon map search the nodes come from depends on ViewSingleBounceNumber.
- L627 _public member_ `bool bEmitPhotonsOutsideImportanceVolume;` — Debugging - whether to emit any photons outside the importance volume, if one exists. If this is false, nothing outside the volume will bounce lighting and will be lit with direct lighting only.
- L630 _public member_ `float ConeFilterConstant;` — Cone filter constant, which characterizes the falloff of the filter applied to photon density estimations.
- L633 _public member_ `int32 NumIrradianceCalculationPhotons;` — Number of photons to find in each photon map when calculating irradiance for an irradiance photon.
- L640 _public member_ `float FinalGatherImportanceSampleFraction;` — Fraction of NumHemisphereSamples to use for importance sampling instead of uniform sampling the final gather. If this fraction is close to 1, no uniform samples will be done and irradiance caching will be forced off as a result. If this is 0, only uniform samples will be taken.
- L643 _public member_ `float FinalGatherImportanceSampleCosConeAngle;` — Cosine of the cone angle from an importance photon direction to generate ray directions for importance sampled final gathering.
- L646 _public member_ `float IndirectPhotonEmitDiskRadius;` — World space radius of the disk around an indirect photon path in which indirect photons will be emitted from directional lights.
- L649 _public member_ `float IndirectPhotonEmitConeAngle;` — Angle around an indirect photon path in which indirect photons will be emitted from point, spot and mesh area lights.
- L652 _public member_ `float MaxImportancePhotonSearchDistance;` — Maximum distance to search for importance photons.
- L659 _public member_ `float MinImportancePhotonSearchDistance;` — Distance to start searching for importance photons at. For some scenes a small start distance (relative to MaxImportancePhotonSearchDistance) will speed up the search Since it can early out once enough photons are found.  For other scenes a small start distance will just cause redundant photon map searches.
- L662 _public member_ `int32 NumImportanceSearchPhotons;` — Number of importance photons to find at each irradiance cache sample that will be used to guide the final gather.
- L665 _public member_ `float OutsideImportanceVolumeDensityScale;` — Scales the density at which to gather photons outside of the importance volume, if one exists.
- L670 _public member_ `float DirectPhotonDensity;` — Density of direct photons to emit per light, in number of photons per million surface area units.
- L673 _public member_ `float DirectIrradiancePhotonDensity;` — Density of direct photons which have irradiance cached at their position, in number of photons per million surface area units.
- L676 _public member_ `float DirectPhotonSearchDistance;` — Distance to use when searching for direct photons.
- L682 _public member_ `float IndirectPhotonPathDensity;` — Target density of indirect photon paths to gather, in number of paths per million surface area units. Densities too small will result in indirect lighting not making it into small pockets.
- L688 _public member_ `float IndirectPhotonDensity;` — Density of indirect photons to emit, in number of photons per million surface area units. This should be high because first bounce photons are used to guide the final gather.
- L691 _public member_ `float IndirectIrradiancePhotonDensity;` — Density of indirect photons which have irradiance cached at their position, in number of photons per million surface area units.
- L694 _public member_ `float IndirectPhotonSearchDistance;` — Distance to use when searching for indirect photons.
- L697 _public member_ `float PhotonSearchAngleThreshold;` — Maximum cosine of the angle between the search normal and the surface normal of a candidate photon for that photon to be a valid search result.
- L700 _public member_ `float MinCosIrradiancePhotonSearchCone;` — Cosine of the angle from the search normal that defines a cone which irradiance photons must be outside of to be valid for that search.
- L706 _public member_ `bool bUsePhotonSegmentsForVolumeLighting;` — Whether to build a photon segment map, to guide importance sampling for volume queries. Currently costs too much memory and queries are too slow to be a net positive.
- L709 _public member_ `float PhotonSegmentMaxLength;` — Maximum world space length of segments that photons are split into for volumetric queries.
- L712 _public member_ `float GeneratePhotonSegmentChance;` — Probability that a first bounce photon will be put into the photon segment map for volumetric queries.

#### class `Lightmass::FIrradianceCachingSettings`  
`class FIrradianceCachingSettings`  
_L716-777_
- desc: Settings controlling irradiance caching behavior.
- L720 _public member_ `bool bAllowIrradianceCaching;` — Debugging - whether to allow irradiance caching.  When this is disabled, indirect lighting will be many times slower.
- L723 _public member_ `bool bUseIrradianceGradients;` — Debugging - whether to use irradiance gradients, which effectively allows higher order irradiance cache interpolation.
- L726 _public member_ `bool bShowGradientsOnly;` — Debugging - whether to only show irradiance gradients.
- L729 _public member_ `bool bVisualizeIrradianceSamples;` — Debugging - whether to draw debug elements in the editor showing which irradiance cache samples were used to shade the selected texel.
- L732 _public member_ `float RecordRadiusScale;` — Scale applied to the radius of irradiance cache records.  This directly affects sample placement and therefore quality.
- L735 _public member_ `float InterpolationMaxAngle;` — Maximum angle between a record and the point being shaded allowed for the record to contribute.
- L741 _public member_ `float PointBehindRecordMaxAngle;` — Maximum angle from the plane defined by the average normal of a record and the point being shaded That the vector from the point to the record can be for that record to contribute.
- L747 _public member_ `float DistanceSmoothFactor;` — How much to increase RecordRadiusScale for the shading pass. This effectively filters the irradiance on flat surfaces.
- L753 _public member_ `float AngleSmoothFactor;` — How much to increase InterpolationMaxAngle for the shading pass. This effectively filters the irradiance on curved surfaces.
- L759 _public member_ `float SkyOcclusionSmoothnessReduction;` — Scale applied to smoothness thresholds for sky occlusion. This is useful because sky occlusion tends to be less noisy than GI, so less smoothing is needed to hide noise.
- L762 _public member_ `float MaxRecordRadius;` — Largest radius an irradiance cache record can have.
- L769 _public member_ `int32 CacheTaskSize;` — Task size for parallelization of irradiance cache population within a mapping.  A mapping will be split into pieces of this size which allows other threads to help. Smaller settings result in more redundant irradiance cache samples, but allow better parallelization. Setting this to a large value like 4096 will effectively make the irradiance caching single threaded for a given mapping, which is useful for debugging.
- L776 _public member_ `int32 InterpolateTaskSize;` — Task size for parallelization of irradiance cache interpolation within a mapping.  A mapping will be split into pieces of this size which allows other threads to help. Smaller settings allow better parallelization. Setting this to a large value like 4096 will effectively make the irradiance cache interpolation single threaded for a given mapping, which is useful for debugging.

#### struct `Lightmass::FDebugLightingInputData`  
`struct FDebugLightingInputData`  
_L779-799_
- L782 _public member_ `bool bRelaySolverStats;` — Whether the solver should send stats back to Unreal
- L784 _public member_ `FGuid MappingGuid;` — Guid of the mapping to debug
- L786 _public member_ `int32 NodeIndex;` — Index of the BSP node to debug if the mapping is a BSP mapping
- L788 _public member_ `FVector4f Position;` — World space position of the position that was clicked to select the debug sample
- L790 _public member_ `int32 LocalX;` — Position in the texture mapping of the texel to debug
- L791 _public member_ `int32 LocalY;`
- L793 _public member_ `int32 MappingSizeX;` — Size of the texture mapping that was selected to debug
- L794 _public member_ `int32 MappingSizeY;`
- L796 _public member_ `FVector4f CameraPosition;` — Position of the camera
- L798 _public member_ `int32 DebugVisibilityId;` — VisibilityId of a component from the currently selected actor or BSP surface.

#### struct `Lightmass::FSceneFileHeader`  
`struct FSceneFileHeader`  
_L804-871_
- L807 _public member_ `uint32 Cookie;` — FourCC cookie: 'SCEN'
- L808 _public member_ `FGuid FormatVersion;`
- L809 _public member_ `FGuid Guid;`
- L812 _public member_ `FStaticLightingSettings GeneralSettings;` — Settings for the GI solver
- L813 _public member_ `FStaticLightingSceneConstants SceneConstants;`
- L814 _public member_ `FSceneMaterialSettings MaterialSettings;`
- L815 _public member_ `FMeshAreaLightSettings MeshAreaLightSettings;`
- L816 _public member_ `FAmbientOcclusionSettings AmbientOcclusionSettings;`
- L817 _public member_ `FDynamicObjectSettings DynamicObjectSettings;`
- L818 _public member_ `FVolumetricLightmapSettings VolumetricLightmapSettings;`
- L819 _public member_ `FPrecomputedVisibilitySettings PrecomputedVisibilitySettings;`
- L820 _public member_ `FVolumeDistanceFieldSettings VolumeDistanceFieldSettings;`
- L821 _public member_ `FStaticShadowSettings ShadowSettings;`
- L822 _public member_ `FImportanceTracingSettings ImportanceTracingSettings;`
- L823 _public member_ `FPhotonMappingSettings PhotonMappingSettings;`
- L824 _public member_ `FIrradianceCachingSettings IrradianceCachingSettings;`
- L826 _public member_ `FDebugLightingInputData DebugInput;`
- L828 _public function_ `FSceneFileHeader()`
- L831 _public prototype_ `FSceneFileHeader(const FSceneFileHeader& Other);` — Copy ctor that doesn't modify padding in FSceneFileHeader.
- L834 _public member_ `uint32 bPadMappings:1;` — If true, pad the mappings (shrink the requested size and then pad)
- L836 _public member_ `uint32 bDebugPadding:1;` — If true, draw a solid border as the padding around mappings
- L838 _public member_ `uint32 bOnlyCalcDebugTexelMappings:1;` — If true, only calculate lighting on debugged texel's mappings
- L840 _public member_ `uint32 bColorByExecutionTime:1;` — If true, color lightmaps based on execution time (brighter red = slower)
- L842 _public member_ `uint32 bUseRandomColors:1;` — If true, color lightmaps a random color
- L844 _public member_ `uint32 bColorBordersGreen:1;` — If true, a green border will be placed around the edges of mappings
- L847 _public member_ `float ExecutionTimeDivisor;` — Amount of time to color full red (Color.R = Time / ExecutionTimeDivisor)
- L849 _public member_ `int32 NumImportanceVolumes;`
- L850 _public member_ `int32 NumCharacterIndirectDetailVolumes;`
- L851 _public member_ `int32 NumVolumetricLightmapDensityVolumes;`
- L852 _public member_ `int32 NumPortals;`
- L853 _public member_ `int32 NumDirectionalLights;`
- L854 _public member_ `int32 NumPointLights;`
- L855 _public member_ `int32 NumSpotLights;`
- L856 _public member_ `int32 NumRectLights;`
- L857 _public member_ `int32 NumSkyLights;`
- L858 _public member_ `int32 NumStaticMeshes;`
- L859 _public member_ `int32 NumStaticMeshInstances;`
- L860 _public member_ `int32 NumFluidSurfaceInstances;`
- L861 _public member_ `int32 NumLandscapeInstances;`
- L862 _public member_ `int32 NumBSPMappings;`
- L863 _public member_ `int32 NumStaticMeshTextureMappings;`
- L864 _public member_ `int32 NumFluidSurfaceTextureMappings;`
- L865 _public member_ `int32 NumLandscapeTextureMappings;`
- L866 _public member_ `int32 NumSpeedTreeMappings;`
- L867 _public member_ `int32 NumVolumeMappings;`
- L868 _public member_ `int32 NumLandscapeVolumeMappings;`
- L869 _public member_ `int32 NumPrecomputedVisibilityBuckets;`
- L870 _public member_ `int32 NumVolumetricLightmapTasks;`

#### enum `Lightmass::EDawnLightFlags`  
`enum EDawnLightFlags`  
_L876-891_
- L879 _public enumerator_ `GI_LIGHT_CASTSHADOWS = 0x00000001` — maps to ULightComponent::CastShadows
- L881 _public enumerator_ `GI_LIGHT_HASSTATICLIGHTING = 0x00000002` — maps to ULightComponent::HasStaticLighting()
- L883 _public enumerator_ `GI_LIGHT_HASSTATICSHADOWING = 0x00000008` — maps to ULightComponent::HasStaticShadowing()
- L885 _public enumerator_ `GI_LIGHT_CASTSTATICSHADOWS = 0x00000010` — maps to ULightComponent::CastStaticShadows
- L886 _public enumerator_ `GI_LIGHT_STORE_SEPARATE_SHADOW_FACTOR = 0x00000020`
- L887 _public enumerator_ `GI_LIGHT_INVERSE_SQUARED = 0x00000080`
- L888 _public enumerator_ `GI_LIGHT_USE_LIGHTPROFILE = 0x00000100`
- L890 _public enumerator_ `GI_LIGHT_USE_AREA_SHADOWS_FOR_SEPARATE_SHADOW_FACTOR = 0x00000200` — Whether a stationary light should generate a standard shadowmap (area shadows) or a distance field shadow map

#### struct `Lightmass::FLightData`  
`struct FLightData`  
_L893-984_
- L895 _public member_ `static const int32 LightProfileTextureDataSize = 256 * 256;`
- L897 _public member_ `FGuid Guid;`
- L899 _public member_ `uint32 LightFlags;` — Bit-wise combination of flags from EDawnLightFlags
- L901 _public member_ `FVector4f Position;` — Homogeneous coordinates
- L902 _public member_ `FVector4f Direction;`
- L903 _public member_ `FLinearColor Color;`
- L904 _public member_ `float Brightness;`
- L906 _public member_ `float LightSourceRadius;` — The radius of the light's surface, not the light's influence.
- L908 _public member_ `float LightSourceLength;` — The length of the light source
- L910 _public member_ `float IndirectLightingScale;` — Scale factor for the indirect lighting
- L912 _public member_ `float IndirectLightingSaturation;` — 0 will be completely desaturated, 1 will be unchanged, 2 will be completely saturated
- L914 _public member_ `float ShadowExponent;` — Controls the falloff of shadow penumbras
- L916 _public member_ `float ShadowResolutionScale;` — Scales resolution of the static shadowmap for this light.
- L922 _public function_ `inline float ComputeLightProfileMultiplier(const TArray< uint8 >& LightProfileTextureData, FVector3f WorldPosition, FVector3f LightPosition, FVector3f LightDirection, FVector3f LightTangent) const` — @param WorldPosition		position of the point to light in the world @param LightPosition		position of the light in the world @param LightDirection	direction at which the light is emitting (x axis) @param LightTangent		tangent to the direction at which the light is emitting (z axis)
- L954 _private function_ `inline float FilterLightProfile(const TArray< uint8 >& LightProfileTextureData, const float X, const float Y) const` — @param X clamped in range 0..1 @return 0..1

#### struct `Lightmass::FDirectionalLightData`  
`struct FDirectionalLightData`  
_L989-993_
- L992 _public member_ `float LightSourceAngle;` — Angle that the directional light's emissive surface extends from any receiver position, in radians.

#### struct `Lightmass::FPointLightData`  
`struct FPointLightData`  
_L998-1004_
- L1000 _public member_ `float Radius;`
- L1001 _public member_ `float FalloffExponent;`
- L1003 _public member_ `FVector3f LightTangent;` — Point lights need an additional axis to specify the direction of IES profiles, also used by spot lights for the direction of tube lights

#### struct `Lightmass::FSpotLightData`  
`struct FSpotLightData`  
_L1009-1015_
- L1012 _public member_ `float InnerConeAngle;` — Unclamped, in degrees
- L1014 _public member_ `float OuterConeAngle;` — Unclamped, in degrees

#### struct `Lightmass::FSkyLightData`  
`struct FSkyLightData`  
_L1020-1029_
- L1026 _public member_ `bool bUseFilteredCubemap;` — Whether to use a filtered cubemap matching the Skylight Component's CubemapResolution to represent the skylight, or a 3rd order Spherical Harmonic. The filtered cubemap is much more accurate than 3rd order SH, especially in mostly shadowed areas.
- L1027 _public member_ `int32 RadianceEnvironmentMapDataSize;`
- L1028 _public member_ `FSHVectorRGB3 IrradianceEnvironmentMap;`

#### struct `Lightmass::FRectLightData`  
`struct FRectLightData`  
_L1031-1036_
- L1033 _public member_ `uint32 SourceTextureSizeX;`
- L1034 _public member_ `uint32 SourceTextureSizeY;`
- L1035 _public member_ `FLinearColor SourceTextureAvgColor;`

#### struct `Lightmass::FMaterialElementData`  
`struct FMaterialElementData`  
_L1042-1087_
- L1045 _public member_ `FSHAHash MaterialHash;` — Used to find Material on import
- L1047 _public member_ `uint32 bUseTwoSidedLighting:1;` — If true, this object will be lit as if it receives light from both sides of its polygons.
- L1049 _public member_ `uint32 bShadowIndirectOnly:1;` — If true, this material element will only shadow indirect lighting.
- L1051 _public member_ `uint32 bUseEmissiveForStaticLighting:1;` — If true, allow using the emissive for static lighting.
- L1056 _public member_ `uint32 bUseVertexNormalForHemisphereGather:1;` — Typically the triangle normal is used for hemisphere gathering which prevents incorrect self-shadowing from artist-tweaked vertex normals. However in the case of foliage whose vertex normal has been setup to match the underlying terrain, gathering in the direction of the vertex normal is desired.
- L1058 _public member_ `float EmissiveLightFalloffExponent;` — Direct lighting falloff exponent for mesh area lights created from emissive areas on this primitive.
- L1064 _public member_ `float EmissiveLightExplicitInfluenceRadius;` — Direct lighting influence radius. The default is 0, which means the influence radius should be automatically generated based on the emissive light brightness. Values greater than 0 override the automatic method.
- L1066 _public member_ `float EmissiveBoost;` — Scales the emissive contribution of this material.
- L1068 _public member_ `float DiffuseBoost;` — Scales the diffuse contribution of this material.
- L1073 _public member_ `float FullyOccludedSamplesFraction;` — Fraction of the samples taken that have to be occluded before an occlusion value of 1 is reached for that texel. A value of 1 means all the samples in the hemisphere have to be occluded, lower values darken areas that are not fully occluded.
- L1075 _public function_ `FMaterialElementData() : bUseTwoSidedLighting(false) , bShadowIndirectOnly(false) , bUseEmissiveForStaticLighting(true) , bUseVertexNormalForHemisphereGather(false) , EmissiveLightFalloffExponent(2.0f) , EmissiveLightExplicitInfluenceRadius(0.0f) , EmissiveBoost(1.0f) , DiffuseBoost(1.0f) , FullyOccludedSamplesFraction(1.0f)`

#### enum `Lightmass::EMeshInstanceLightingFlags`  
`enum EMeshInstanceLightingFlags`  
_L1089-1099_
- L1092 _public enumerator_ `GI_INSTANCE_CASTSHADOW = 1<<0` — Whether the mesh casts a shadow.
- L1094 _public enumerator_ `GI_INSTANCE_TWOSIDED = 1<<1` — Whether the mesh uses a two-sided material.
- L1096 _public enumerator_ `GI_INSTANCE_SELFSHADOWONLY = 1<<2` — Whether the mesh only casts a shadow on itself.
- L1098 _public enumerator_ `GI_INSTANCE_SELFSHADOWDISABLE = 1<<3` — Whether to disable casting a shadow on itself.

#### struct `Lightmass::FStaticLightingMeshInstanceData`  
`struct FStaticLightingMeshInstanceData`  
_L1101-1124_
- L1103 _public member_ `FGuid Guid;`
- L1105 _public member_ `int32 NumTriangles;` — The number of triangles in the mesh, used for visibility testing.
- L1107 _public member_ `int32 NumShadingTriangles;` — The number of shading triangles in the mesh.
- L1109 _public member_ `int32 NumVertices;` — The number of vertices in the mesh, used for visibility testing.
- L1111 _public member_ `int32 NumShadingVertices;` — The number of shading vertices in the mesh.
- L1113 _public member_ `int32 TextureCoordinateIndex;` — The texture coordinate index which is used to parametrize materials.
- L1114 _public member_ `int32 MeshIndex;`
- L1115 _public member_ `FGuid LevelGuid;`
- L1116 _public member_ `uint32 LightingFlags;` — EMeshInstanceLightingFlags
- L1117 _public member_ `bool bCastShadowAsTwoSided;`
- L1119 _public member_ `bool bMovable;` — Whether the mesh can be moved in game or not.
- L1121 _public member_ `int32 NumRelevantLights;` — The lights which affect the mesh's primitive.
- L1123 _public member_ `FBox3f BoundingBox;` — The bounding box of the mesh.

#### enum `Lightmass::ESplineMeshAxis::Type`  
`enum Type`  
_L1128-1133_
- L1130 _public enumerator_ `X`
- L1131 _public enumerator_ `Y`
- L1132 _public enumerator_ `Z`

#### struct `Lightmass::FSplineMeshParams`  
`struct FSplineMeshParams`  
_L1140-1172_
- desc: Parameters used to transform a static mesh based on a spline. Be sure to update this structure if spline functionality changes in Unreal!
- L1143 _public member_ `FVector3f StartPos;` — Start location of spline, in component space
- L1145 _public member_ `FVector3f StartTangent;` — Start tangent of spline, in component space
- L1147 _public member_ `FVector2f StartScale;` — X and Y scale applied to mesh at start of spline
- L1149 _public member_ `float StartRoll;` — Roll around spline applied at start
- L1151 _public member_ `FVector2f StartOffset;` — Offset from the spline at start
- L1153 _public member_ `FVector3f EndPos;` — End location of spline, in component space
- L1155 _public member_ `FVector3f EndTangent;` — End tangent of spline, in component space
- L1157 _public member_ `FVector2f EndScale;` — X and Y scale applied to mesh at end of spline
- L1159 _public member_ `float EndRoll;` — Roll around spline applied at end
- L1161 _public member_ `FVector2f EndOffset;` — Offset from the base spline at end
- L1163 _public member_ `FVector3f SplineUpDir;` — Axis (in component space) that is used to determine X axis for co-ordinates along spline
- L1165 _public member_ `bool bSmoothInterpRollScale;` — Smoothly (cubic) interpolate the Roll and Scale params over spline.
- L1167 _public member_ `float MeshMinZ;` — Minimum Z value of the entire mesh
- L1169 _public member_ `float MeshRangeZ;` — Range of Z values over entire mesh
- L1171 _public member_ `TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;` — Chooses the forward axis for the spline mesh orientation

#### struct `Lightmass::FStaticMeshStaticLightingMeshData`  
`struct FStaticMeshStaticLightingMeshData`  
_L1174-1186_
- L1177 _public member_ `uint32 EncodedLODIndices;` — The LOD this mesh represents.
- L1178 _public member_ `uint32 EncodedHLODRange;`
- L1179 _public member_ `FMatrix44f LocalToWorld;`
- L1181 _public member_ `bool bReverseWinding;` — true if the primitive has a transform which reverses the winding of its triangles.
- L1182 _public member_ `bool bShouldSelfShadow;`
- L1183 _public member_ `FGuid StaticMeshGuid;`
- L1184 _public member_ `bool bIsSplineMesh;`
- L1185 _public member_ `FSplineMeshParams SplineParameters;`

#### struct `Lightmass::FMinimalStaticLightingVertex`  
`struct FMinimalStaticLightingVertex`  
_L1188-1193_
- L1190 _public member_ `FVector4f WorldPosition;`
- L1191 _public member_ `FVector4f WorldTangentZ;`
- L1192 _public member_ `FVector2f TextureCoordinates[MAX_TEXCOORDS];`

#### struct `Lightmass::FStaticLightingVertexData`  
`struct FStaticLightingVertexData : public FMinimalStaticLightingVertex`  
_L1195-1199_
- inherits: `FMinimalStaticLightingVertex`
- L1197 _public member_ `FVector4f WorldTangentX;`
- L1198 _public member_ `FVector4f WorldTangentY;`

#### struct `Lightmass::FBSPSurfaceStaticLightingData`  
`struct FBSPSurfaceStaticLightingData`  
_L1201-1211_
- L1203 _public member_ `FVector4f TangentX;`
- L1204 _public member_ `FVector4f TangentY;`
- L1205 _public member_ `FVector4f TangentZ;`
- L1207 _public member_ `FMatrix44f MapToWorld;`
- L1208 _public member_ `FMatrix44f WorldToMap;`
- L1210 _public member_ `FGuid MaterialGuid;`

#### struct `Lightmass::FStaticLightingMappingData`  
`struct FStaticLightingMappingData`  
_L1213-1217_
- L1215 _public member_ `FGuid Guid;`
- L1216 _public member_ `FGuid StaticLightingMeshInstance;`

#### struct `Lightmass::FStaticLightingTextureMappingData`  
`struct FStaticLightingTextureMappingData`  
_L1219-1229_
- L1222 _public member_ `int32 SizeX;` — The width of the static lighting textures used by the mapping.
- L1224 _public member_ `int32 SizeY;` — The height of the static lighting textures used by the mapping.
- L1226 _public member_ `int32 LightmapTextureCoordinateIndex;` — The lightmap texture coordinate index which is used for the mapping.
- L1228 _public member_ `bool bBilinearFilter;` — Whether to apply a bilinear filter to the sample or not.

#### struct `Lightmass::FStaticLightingVertexMappingData`  
`struct FStaticLightingVertexMappingData`  
_L1231-1237_
- L1234 _public member_ `float SampleToAreaRatio;` — Lighting will be sampled at a random number of samples/surface area proportional to this factor.
- L1236 _public member_ `bool bSampleVertices;` — true to sample at vertices instead of on the surfaces.

#### struct `Lightmass::FFluidSurfaceStaticLightingMeshData`  
`struct FFluidSurfaceStaticLightingMeshData`  
_L1243-1253_
- desc: Fluid surfaces
- L1246 _public member_ `FMatrix44f LocalToWorld;` — The primitive's local to world transform.
- L1248 _public member_ `FMatrix44f LocalToWorldInverseTranspose;` — The inverse transpose of the primitive's local to world transform.
- L1250 _public member_ `FVector4f QuadCorners[4];` — The mesh data of the fluid surface, which is represented as a quad.
- L1251 _public member_ `FVector4f QuadUVCorners[4];`
- L1252 _public member_ `int32 QuadIndices[6];`

#### struct `Lightmass::FLandscapeStaticLightingMeshData`  
`struct FLandscapeStaticLightingMeshData`  
_L1258-1267_
- desc: Landscape
- L1261 _public member_ `FMatrix44f LocalToWorld;` — The primitive's local to world transform.
- L1262 _public member_ `int32 ComponentSizeQuads;`
- L1263 _public member_ `float LightMapRatio;`
- L1265 _public member_ `int32 ExpandQuadsX;` — The number of quads we are expanding to eliminate seams.
- L1266 _public member_ `int32 ExpandQuadsY;`

#### struct `Lightmass::FVolumetricLightmapDensityVolumeData`  
`struct FVolumetricLightmapDensityVolumeData`  
_L1269-1274_
- L1271 _public member_ `FBox3f Bounds;`
- L1272 _public member_ `FIntPoint AllowedMipLevelRange;`
- L1273 _public member_ `int32 NumPlanes;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Lightmass`
- L30 _variable_ `static const int32 NumTexelCorners = 4;` (scope `Lightmass`)
- L1126 _namespace_ `namespace ESplineMeshAxis` (scope `Lightmass`)
