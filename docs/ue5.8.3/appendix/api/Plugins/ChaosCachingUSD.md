# Plugins / ChaosCachingUSD

- module root: `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD`
- headers: 5; symbols: 72
- symbol kinds: class=2, delegate=1, externvar=1, function=3, member=4, namespace=5, prototype=55, struct=1
- PrivateDependencyModuleNames: USDClasses, USDUtilities, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI

### `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD/Private/ChaosCachingUSD/UEUsdGeomTetMesh.h` (Private)


#### class `UEUsdGeomTetMesh`  
`class UEUsdGeomTetMesh : public UsdGeomMesh`  
_L33-101_
- inherits: `UsdGeomMesh`
- desc: \class UEUsdGeomTetMesh A Tetrahedral mesh prim, derived from \c UsdGeomMesh, which is used for drawing the exterior hull of the tetrahedron mesh.  This class adds a topology array for tetrahedra consisting of \c GfVec4i, and an attribute that specifies the tetrahedron orientation/winding order. The constructor defines and sets the subdivision scheme attribute to `none` so that by default the geometry rendered by the \c UsdGeomMesh base class is polygonal.
- L36 _public member_ `static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;`
- L39 _public prototype_ `explicit UEUsdGeomTetMesh(const UsdPrim& Prim=UsdPrim());` — Construct a UEUsdGeomTetMesh from a UsdPrim \p prim.
- L40 _public prototype_ `explicit UEUsdGeomTetMesh(const UsdSchemaBase& SchemaObj);`
- L42 _public prototype_ `virtual ~UEUsdGeomTetMesh();`
- L45 _public prototype_ `GetSchemaAttributeNames(bool bIncludeInherited=true);`
- L48 _public prototype_ `Get(const UsdStagePtr &Stage, const SdfPath &Path);`
- L51 _public prototype_ `Define(const UsdStagePtr &Stage, const SdfPath &Path);`
- L54 _protected prototype_ `UsdSchemaKind _GetSchemaKind() const override;`
- L59 _private prototype_ `static const TfType &_GetStaticTfType();`
- L61 _private prototype_ `static bool _IsTypedSchema();`
- L64 _private prototype_ `virtual const TfType &_GetTfType() const;` — Override SchemaBase virtuals.
- L78 _public prototype_ `UsdAttribute GetTetVertexIndicesAttr() const;` — Tetrahedron indices. Each element of this array contains the indices of the vertices of a tetrahedron. The points are authored into the "points" attribute, just as they are for other PointBased prims. C++ Type: VtArray<GfVec4i> Usd Type: SdfValueTypeNames->Int4Array Variability: SdfVariabilityVarying Fallback Value: No Fallback
- L87 _public prototype_ `UsdAttribute CreateTetVertexIndicesAttr(VtValue const &DefaultValue = VtValue(), bool WriteSparsely=false) const;` — See GetTetVertexIndicesAttr(), and also \ref Usd_Create_Or_Get_Property for when to use Get vs Create. If specified, author \p DefaultValue as the attribute's default, sparsely (when it makes sense to do so) if \p WriteSparsely is \c true - the default for \p writeSparsely is \c false.
- L95 _public prototype_ `UsdAttribute GetTetOrientationAttr() const;` — Tetrahedron orientation. Given [A,B,C,D] if your right hand is at A, if your fingers wrap to A-B, then A-C, and your thumb points at D.
- L100 _public prototype_ `UsdAttribute CreateTetOrientationAttr(VtValue const& DefaultValue = VtValue(), bool WriteSparsely = false) const;` — See GetTetOrientationAttr().

### `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD/Private/ChaosCachingUSD/UEUsdGeomTokens.h` (Private)


#### struct `UEUsdGeomTokensType`  
`struct UEUsdGeomTokensType`  
_L15-29_
- L17 _public prototype_ `UEUsdGeomTokensType();`
- L22 _public member_ `const TfToken tetOrientation;` — UEUsdGeomTetMesh
- L26 _public member_ `const TfToken tetVertexIndices;` — UEUsdGeomTetMesh
- L28 _public member_ `const std::vector<TfToken> allTokens;` — A vector of all of the tokens listed above.

#### Free symbols / members of external scopes

- L34 _externvar_ `extern TfStaticData<UEUsdGeomTokensType> UEUsdGeomTokens;` — A global variable for access to static tokens.

### `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD/Private/ChaosCachingUSD/Util.h` (Private)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ChaosCachingUSDUtil` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::ChaosCachingUSDUtil`)
- L31 _function_ `template <class T1, class T2> void CastConvert(const pxr::VtArray<T1>& VtArray, TArray<T2>& UEArray)` (scope `UE::ChaosCachingUSDUtil::Private`) — Convert from \c pxr::VtArray<T1> to \c TArray<T2>, where \p T1 and \p T2 are binary compatible. Note that \c VtArray is shared copy-on-write, which makes them trivially copied. This function copies memory, which should be avoided.
- L53 _function_ `template <class T1, class T2> void CastLerp(const pxr::VtArray<T1>& VtArray1, const pxr::VtArray<T1>& VtArray2, TArray<T2>& UEArray, const float Alpha)` (scope `UE::ChaosCachingUSDUtil::Private`) — Linearly interpolate values in \p VtArray1 and \p VtArray2 by interpolant \p Alpha ([0,1]), converting from \p T1 to \p T2, where \p T1 and \p T2 are binary compatible. Note that \c VtArray is shared copy-on-write, which makes them trivially copied. This function copies memory, which should be avoided.
- L93 _prototype_ `void SaveStage(const pxr::UsdStageRefPtr& Stage, const pxr::UsdTimeCode& FirstFrame, const pxr::UsdTimeCode &LastFrame);` (scope `UE::ChaosCachingUSDUtil::Private`)
- L94 _prototype_ `void DefineAncestorTransforms(pxr::UsdStageRefPtr& Stage, const pxr::SdfPath& PrimPath);` (scope `UE::ChaosCachingUSDUtil::Private`)
- L95 _prototype_ `void ComputeExtent(const pxr::VtArray<pxr::GfVec3f>& Points, pxr::VtVec3fArray& Extent);` (scope `UE::ChaosCachingUSDUtil::Private`)
- L96 _prototype_ `bool SetPointsExtentAndPrimXform(pxr::UsdPrim& Prim, const pxr::GfMatrix4d& PrimXf, const pxr::VtArray<pxr::GfVec3f>& Points, const pxr::VtArray<pxr::GfVec3f>& Vels, const pxr::UsdTimeCode& Time = pxr::UsdTimeCode::Default());` (scope `UE::ChaosCachingUSDUtil::Private`)
- L97 _prototype_ `bool SetPointsExtentAndPrimXform(pxr::UsdPrim& Prim, const pxr::GfMatrix4d& PrimXf, const pxr::VtArray<pxr::GfVec3f>& Points, const pxr::UsdTimeCode& Time = pxr::UsdTimeCode::Default());` (scope `UE::ChaosCachingUSDUtil::Private`)
- L98 _prototype_ `bool SetActivations(pxr::UsdPrim& Prim, const pxr::VtArray<float>& Activations, const pxr::UsdTimeCode& Time);` (scope `UE::ChaosCachingUSDUtil::Private`)
- L99 _prototype_ `bool DeletePointsInTimeRange(pxr::UsdPrim& Prim, float StartTime, float EndTime);` (scope `UE::ChaosCachingUSDUtil::Private`)
- L100 _prototype_ `bool DeleteUsdAttributeInTimeRange(pxr::UsdAttribute Attribute, float StartTime, float EndTime);` (scope `UE::ChaosCachingUSDUtil::Private`)

### `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD/Public/ChaosCachingUSD/Module.h` (Public)


#### class `FChaosCachingUSDModule`  
`class FChaosCachingUSDModule : public IModuleInterface`  
_L12-18_
- inherits: `IModuleInterface`
- L15 _private prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCacheUSD, Verbose, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCacheUSD, Verbose, All);` — `UE_DEPRECATED(5.7, "Use LogUsd instead")`

### `Plugins/Experimental/ChaosCachingUSD/Source/ChaosCachingUSD/Public/ChaosCachingUSD/Operations.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ChaosCachingUSD` (scope `UE`)
- L21 _function_ `inline bool ValuesDiffer(const pxr::VtArray<pxr::GfVec3f>& A, const pxr::VtArray<pxr::GfVec3f>& B, const float Tolerance = 1.0e-8, const uint64 stride = 1)` (scope `UE::ChaosCachingUSD`)
- L36 _prototype_ `bool NewStage(const FString& StageName, UE::FUsdStage& Stage);` (scope `UE::ChaosCachingUSD`) — Create a new stage, resident in the USD stage cache.
- L38 _prototype_ `bool OpenStage(const FString& StageName, UE::FUsdStage& Stage);` (scope `UE::ChaosCachingUSD`) — Opens an existing stage, resident in the USD stage cache.
- L41 _prototype_ `bool SaveStage(UE::FUsdStage& Stage, const double FirstFrame, const double LastFrame);` (scope `UE::ChaosCachingUSD`) — Save the stage and update the frame range (if not -DBL_MAX).
- L44 _prototype_ `bool CloseStage(const UE::FUsdStage& Stage);` (scope `UE::ChaosCachingUSD`) — Close and remove a stage from the USD stage cache.
- L45 _prototype_ `bool CloseStage(const FString& StageName);` (scope `UE::ChaosCachingUSD`)
- L62 _prototype_ `GenerateValueClipStageNames(const FString& ParentName, FString& TopologyName, FString& TimeVaryingTemplate);` (scope `UE::ChaosCachingUSD`)
- L65 _prototype_ `GenerateValueClipTimeVaryingStageName(const FString& TimeVaryingTemplate, const double Time);` (scope `UE::ChaosCachingUSD`)
- L69 _prototype_ `NewValueClipsStages( const FString& ParentStageName, const FString& TopologyStageName, UE::FUsdStage& ParentStage, UE::FUsdStage& TopologyStage);` (scope `UE::ChaosCachingUSD`)
- L76 _prototype_ `NewValueClipsFrameStage( const FString& TimeVaryingStageTemplate, const double Time, FString& FrameStageName, UE::FUsdStage& FrameStage);` (scope `UE::ChaosCachingUSD`)
- L96 _prototype_ `InitValueClipsTemplate( UE::FUsdStage& ParentStage, UE::FUsdStage& TopologyStage, const FString& ParentStageName, const FString& TopologyStageName, const FString& TimeVaryingStageTemplate, const TArray<FString>& PrimPaths, const double StartTime, const double EndTime, const double Stride);` (scope `UE::ChaosCachingUSD`)
- L108 _prototype_ `InitValueClipsTemplate( const FString& ParentStageName, const FString& TopologyStageName, const FString& TimeVaryingStageTemplate, const TArray<FString>& PrimPaths, const double StartTime, const double EndTime, const double Stride);` (scope `UE::ChaosCachingUSD`)
- L121 _prototype_ `bool WriteTetMesh(UE::FUsdStage& Stage, const FString& PrimPath, const FManagedArrayCollection& Collection, const int32 StructureIndex = INDEX_NONE);` (scope `UE::ChaosCachingUSD`) — Define \c UEUsdGeomTetMesh at \c PrimPath with ancenstor transforms, and authors points at usd "default" time from tet mesh \p StructureIndex (or all if \c INDEX_NONE) from \c Collection.
- L128 _prototype_ `bool WritePoints(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, const FManagedArrayCollection& Collection, const int32 StructureIndex = INDEX_NONE);` (scope `UE::ChaosCachingUSD`) — Define \c UsdGeomPointBased at \c PrimPath with ancestor transforms, and author points at \p Time (or usd "default" time if \c -DBL_MAX) from \p Collection vertices from geometry \p StructureIndex (or all if \c StructureIndex == \c INDEX_NONE).
- L130 _prototype_ `bool WritePoints(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, pxr::VtArray<pxr::GfVec3f>& VtPoints, pxr::VtArray<pxr::GfVec3f>& VtVels);` (scope `UE::ChaosCachingUSD`) — Write points and velocities to \c UsdGeomPointBased at \c PrimPath.
- L132 _prototype_ `bool WritePoints(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, const TArray<Chaos::TVector<float, 3>>& Points, const TArray<Chaos::TVector<float, 3>>& Vels);` (scope `UE::ChaosCachingUSD`) — Copy \p Points and \p Vels to \c VtArray (with USD memory allocator), then write to USD stage.
- L135 _prototype_ `bool WritePoints(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, const TArray<Chaos::TVector<float, 3>>& Points, const TArray<Chaos::TVector<float, 3>>& Vels, const Chaos::FRange& PointsRange);` (scope `UE::ChaosCachingUSD`) — Copy \p Points and \p Vels within the specified indices range to \c VtArray (with USD memory allocator), then write to USD stage.
- L137 _prototype_ `bool WriteActivations(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, pxr::VtArray<float>& VtActivations);` (scope `UE::ChaosCachingUSD`)
- L138 _prototype_ `bool WriteActivations(UE::FUsdStage& Stage, const FString& PrimPath, const double Time, const TArray<float>& Activations, const Chaos::FRange& PointsRange);` (scope `UE::ChaosCachingUSD`)
- L141 _prototype_ `bool ReadTimeSamples(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrName, TArray<double>& TimeSamples);` (scope `UE::ChaosCachingUSD`) — Get time samples for an attribute.
- L143 _prototype_ `bool ReadTimeSamples(const UE::FUsdStage& Stage, const FString& PrimPath, TArray<double>& TimeSamples);` (scope `UE::ChaosCachingUSD`) — Get time samples for the points attribute.
- L144 _prototype_ `uint64 GetNumTimeSamples(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrName);` (scope `UE::ChaosCachingUSD`)
- L146 _prototype_ `FString GetPointsAttrName();` (scope `UE::ChaosCachingUSD`)
- L147 _prototype_ `FString GetVelocityAttrName();` (scope `UE::ChaosCachingUSD`)
- L148 _prototype_ `bool GetBracketingTimeSamples(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrName, const double TargetTime, double* Lower, double* Upper);` (scope `UE::ChaosCachingUSD`)
- L151 _prototype_ `bool ReadPoints(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrPath, const double Time, pxr::VtArray<pxr::GfVec3f>& Points);` (scope `UE::ChaosCachingUSD`) — Get points from an attribute. Default time is used if \p Time is \c -DBL_MAX.
- L152 _prototype_ `bool ReadPoints(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrPath, const double Time, TArray<Chaos::TVector<Chaos::FRealSingle,3>>& Points);` (scope `UE::ChaosCachingUSD`)
- L155 _prototype_ `bool ReadPoints(const UE::FUsdStage& Stage, const FString& PrimPath, const double Time, pxr::VtArray<pxr::GfVec3f>& Points, pxr::VtArray<pxr::GfVec3f>& VtVels);` (scope `UE::ChaosCachingUSD`) — Get points from the points attribute. Default time is used if \p Time is \c -DBL_MAX.
- L157 _prototype_ `bool ReadMuscleActivation(const UE::FUsdStage& Stage, const FString& PrimPath, const FString& AttrName, const double Time, pxr::VtArray<float>& VtActivations);` (scope `UE::ChaosCachingUSD`)
- L158 _prototype_ `bool ReadMuscleActivation(const UE::FUsdStage& Stage, const FString& PrimPath, const double Time, pxr::VtArray<float>& VtActivations);` (scope `UE::ChaosCachingUSD`)
- L160 _prototype_ `bool DeletePointsInTimeRange(UE::FUsdStage& Stage, const FString& PrimPath, const double StartTime, const double EndTime);` (scope `UE::ChaosCachingUSD`)
