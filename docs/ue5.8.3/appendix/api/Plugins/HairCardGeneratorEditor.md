# Plugins / HairCardGeneratorEditor

- module root: `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor`
- headers: 13; symbols: 439
- symbol kinds: class=18, enum=4, enumerator=31, function=16, macro=1, member=144, namespace=3, prototype=207, struct=13, typedef=2
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, EditorStyle, Eigen, HairStrandsCore, InputCore, Json, JsonUtilities, MainFrame, MeshDescription, Slate, SlateCore, StaticMeshDescription, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HairCardGeneratorFramework

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenCardSubdivider.h` (Private)


#### class `FHairCardGenCardSubdivider`  
`class FHairCardGenCardSubdivider`  
_L19-46_
- L22 _private member_ `float SubdTolerance;`
- L23 _private member_ `float SubdToleranceInitial;`
- L24 _private member_ `const bool UseAdaptive;`
- L25 _private member_ `const int MaxSubdivisions;`
- L26 _private member_ `const int NumInterpPoints = 1000;`
- L27 _private member_ `float LastDist;`
- L29 _private member_ `MatrixXf MeanCurve;`
- L32 _private prototype_ `static TArray<float> MatrixXfToTArray(const MatrixXf PointMatrix);`
- L33 _private prototype_ `int NextSubdPoint(const int IndStart);`
- L34 _private prototype_ `TArray<float> AdaptiveIter();`
- L35 _private prototype_ `TArray<float> GetAdaptiveSubdPoints();`
- L36 _private prototype_ `static MatrixXf LinearInterpolation(const MatrixXf, const int NumPoints);`
- L39 _public prototype_ `FHairCardGenCardSubdivider(const float SubdTolerance, const bool UseAdaptive, const int MaxSubdivisions);`
- L40 _public prototype_ `void SetSubdTolerance(const float NewSubdTolerance);`
- L41 _public prototype_ `static MatrixXf TArrayToMatrixXf(const TArray<float> Points);`
- L42 _public prototype_ `TArray<float> GetSubdivisionPoints(const MatrixXf Points);`
- L43 _public prototype_ `static float GetCurveLength(const MatrixXf Points);`
- L44 _public prototype_ `static float GetAverageCurvatureRadius(const MatrixXf Points);`
- L45 _public prototype_ `static float GetToleranceFromLengthAndCurvRadius(const float Length, const float CurvRadius, const float Subdivisions);`

#### Free symbols / members of external scopes

- L5 _macro_ `#define EIGEN_MPL2_ONLY`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenControllerBase.h` (Private)


#### struct `FHairCardGen_StrandData`  
`struct FHairCardGen_StrandData`  
_L17-23_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `int GroupID = -1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strand")`

#### struct `FHairCardGen_GroomData`  
`struct FHairCardGen_GroomData`  
_L27-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: With "Guide" data stipped out (since it isn't used as part of the mesh generation algorithm)
- L32 _public member_ `FString BasisType;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")`
- L35 _public member_ `FString CurveType;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")`
- L39 _public member_ `TArray<FHairCardGen_StrandData> Strands;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")` — Array of index buffers. Each buffer defines a distinct hair strand in the groom.
- L43 _public member_ `TArray<float> VertexPositions;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")` — Flattened Array of 3D vetex positions
- L46 _public member_ `TArray<float> VertexWidths;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")`
- L49 _public member_ `TArray<float> VertexOcclusions;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")`
- L52 _public member_ `int32 HairlineGroupID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom")`

#### class `UHairCardGenControllerBase`  
`class UHairCardGenControllerBase : public UObject`  
_L63-183_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- L68 _public prototype_ `UHairCardGenControllerBase();`
- L71 _public prototype_ `int GetPointsPerCurve();` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L74 _public prototype_ `bool LoadGroomData(const FHairCardGen_GroomData& GroomData, const FString& Name, const FString& CachedGroomsPath, const bool SaveCached = false);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L77 _public prototype_ `bool LoadSettings(const UHairCardGeneratorPluginSettings* GeneratorSettings);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L83 _public prototype_ `bool GenerateClumps(int32 GroupId, FHairCardClumpData& OutClumpData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Returns clump assignment via OutClumpData (bool-first + pure-out).
- L87 _public prototype_ `bool SetOptimizations(int32 GroupId, const FHairCardClumpData& ClumpData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Builds in-memory geometry_opt state from clump data.
- L91 _public prototype_ `bool GenerateCardsGeometry(FHairCardGeomData& OutGeomData, FHairCardMeshData& OutMeshData, int32& OutCardCount);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Returns card geometry via OutGeomData (bool-first + pure-out).
- L95 _public prototype_ `bool ClusterTextures(int32 GroupId, const FHairCardGeomData& GeomData, const FHairCardMeshData& MeshData, FHairCardTextureClusterData& OutClusterData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Returns texture cluster assignment via OutClusterData (bool-first + pure-out).
- L102 _public prototype_ `bool GenerateTextureLayout(const TArray<FHairCardGeomData>& AllGeomData, const TArray<FHairCardMeshData>& AllMeshData, const TArray<FHairCardTextureClusterData>& AllClusterData, FHairCardAtlasLayoutData& OutLayoutData, FHairCardAtlasBinpackData& OutBinpackData, FHairCardAtlasUVData& OutAtlasUVData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Receives all-group data; returns atlas layout and per-vertex atlas UVs (bool-first + pure-out).
- L111 _public prototype_ `bool GenerateTextureAtlases(const TArray<FHairCardGeomData>& AllGeomData, const TArray<FHairCardMeshData>& AllMeshData, const TArray<FHairCardTextureClusterData>& AllClusterData, const FHairCardAtlasLayoutData& LayoutData, const FHairCardAtlasBinpackData& BinpackData, const float WidthScale = -1);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Renders texture atlases to disk.
- L120 _public prototype_ `bool GenerateMesh(UStaticMesh* StaticMesh, const TArray<FHairCardGeomData>& AllGeomData, const TArray<FHairCardMeshData>& AllMeshData, const TArray<FHairCardTextureClusterData>& AllClusterData, const FHairCardAtlasLayoutData& LayoutData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Pure compute. Writes the static mesh asset.
- L130 _public prototype_ `TArray<int32> GetNumCardsPerClump();` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Returns num sub-cards per clump optimizer; available after SetOptimizations.
- L133 _public prototype_ `TArray<float> GetAverageCurve(const int Id, const int Cid);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L136 _public prototype_ `void SetInterpolatedAvgCurve(const int Id, const int Cid, const TArray<float>& Points);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L141 _public prototype_ `bool SaveClumpData(int32 GroupId, const FHairCardClumpData& ClumpData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L144 _public prototype_ `bool LoadClumpData(int32 GroupId, FHairCardClumpData& OutClumpData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L147 _public prototype_ `bool SaveCardData(int32 GroupId, const FHairCardGeomData& GeometryData, const FHairCardMeshData& MeshData, int32 CardCount);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L150 _public prototype_ `bool LoadCardData(int32 GroupId, FHairCardGeomData& OutGeomData, FHairCardMeshData& OutMeshData, int32& OutCardCount);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L153 _public prototype_ `bool SaveTextureClusterData(int32 GroupId, const FHairCardTextureClusterData& TexClusterData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L156 _public prototype_ `bool LoadTextureClusterData(int32 GroupId, FHairCardTextureClusterData& OutTexClusterData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L159 _public prototype_ `bool SaveAtlasLayoutData(const FHairCardAtlasLayoutData& LayoutData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L162 _public prototype_ `bool LoadAtlasLayoutData(FHairCardAtlasLayoutData& OutLayoutData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L165 _public prototype_ `bool SaveAtlasBinpackData(const FHairCardAtlasBinpackData& BinpackData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L168 _public prototype_ `bool LoadAtlasBinpackData(FHairCardAtlasBinpackData& OutBinpackData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)`
- L172 _public prototype_ `void CreateCardsStaticMesh(UStaticMesh* StaticMesh, const TArray<float>& verts, const TArray<int32>& faces, const TArray<float>& normals, const TArray<float>& uvs, const TArray<int32>& groups);` — `UFUNCTION(BlueprintCallable, Category = Python)` — Helper C++ function for building a static mesh from verts/faces, etc.
- L175 _public prototype_ `TObjectPtr<UHairCardGeneratorPluginSettings>& GetGroomSettings(TObjectPtr<UGroomAsset> Groom, int LODIndex);`
- L176 _public prototype_ `void UpdateGroomSettings(TObjectPtr<UGroomAsset> Groom, int LODIndex, int GroupID, TObjectPtr<UHairCardGeneratorPluginSettings> NewSettings);`
- L182 _private member_ `TMap<FString,TObjectPtr<UHairCardGeneratorPluginSettings>> GroomSettingsMap;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenNaturalCubicSplines.h` (Private)


#### class `FHairCardGenNaturalCubicSplines`  
`class FHairCardGenNaturalCubicSplines`  
_L7-31_
- L16 _private member_ `TArray<SplineData> Splines;`
- L17 _private member_ `TArray<int> Bins;`
- L18 _private member_ `float LowerBound;`
- L19 _private member_ `float UpperBound;`
- L20 _private member_ `float BinInterval;`
- L23 _private prototype_ `void MakeSpline(const TArray<float>& Knots, const TArray<float>& Values);`
- L24 _private prototype_ `void MakeBins();`
- L25 _private prototype_ `SplineData const& FindSpline(float t) const;`
- L26 _private prototype_ `void SolveTridiagonalSystem(TArray<float>& Lower, TArray<float>& Diag, TArray<float>& Upper, TArray<float>& RHS);`
- L29 _public prototype_ `FHairCardGenNaturalCubicSplines(const TArray<float>& Knots, const TArray<float>& Values);`
- L30 _public prototype_ `float operator()(float t) const;`

#### struct `FHairCardGenNaturalCubicSplines::SplineData`  
`struct SplineData`  
_L10-14_
- L12 _public member_ `double Knot;`
- L13 _public member_ `double Coefficients[4];`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenOptionsWindow.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace HairCardGenWindow_Utils`
- L20 _prototype_ `bool PromptUserWithHairCardGenDialog(UHairCardGeneratorPluginSettings* OptionsObject);` (scope `HairCardGenWindow_Utils`) — Opens a modal dialog, prompting the user to run hair card generation. @param  OptionsObject	Settings structure defining the settings the user wants to run the generation with (may be modified on return) @raturn True if the user specified they want to run the generation, false if they canceled the process.

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenSettingsDetail.h` (Private)


#### class `FHairCardSettingsDetailCustomization`  
`class FHairCardSettingsDetailCustomization : public IDetailCustomization`  
_L16-38_
- inherits: `IDetailCustomization`
- desc: Detail panel customization for HairCardGeneratorPluginSettings
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Function that customizes the Details Panel.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Returns a static instance of the Details Panel customization.
- L26 _private prototype_ `ECheckBoxState GetCheckValue(const TSharedPtr<IPropertyHandle> Property) const;`
- L27 _private prototype_ `void SetCheckValue(ECheckBoxState NewState, const TSharedPtr<IPropertyHandle> Property) const;`
- L29 _private prototype_ `bool IsEnabledReduceFromLOD(const TSharedPtr<IPropertyHandle> Property) const;`
- L30 _private prototype_ `FText ToolTipReduceFromLOD(const TSharedPtr<IPropertyHandle> Property) const;`
- L31 _private prototype_ `bool CheckReduceFromLOD(const TSharedPtr<IPropertyHandle> Property, FText& OutTooltipInfo) const;`
- L33 _private prototype_ `bool IsEnabledUseReservedTx(const TSharedPtr<IPropertyHandle> Property) const;`
- L34 _private prototype_ `FText ToolUseReservedTx(const TSharedPtr<IPropertyHandle> Property) const;`
- L35 _private prototype_ `bool CheckUseReservedTx(const TSharedPtr<IPropertyHandle> Property, FText& OutTooltipInfo) const;`
- L37 _private member_ `TWeakObjectPtr<UHairCardGeneratorPluginSettings> SettingsPtr;`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenStrandFilter.h` (Private)


#### class `FHairStrandAttribsRefProxy`  
`class FHairStrandAttribsRefProxy`  
_L15-78_
- L20 _public prototype_ `bool IsValid() const;`
- L22 _public prototype_ `bool IsGuideStrand() const;`
- L24 _public prototype_ `bool HasGroupID() const;`
- L25 _public prototype_ `const int& GetGroupID() const;`
- L27 _public prototype_ `bool HasStrandWidth() const;`
- L28 _public prototype_ `const float& GetStrandWidth() const;`
- L30 _public prototype_ `bool HasCardGroupName() const;`
- L31 _public prototype_ `const FName& GetCardGroupName() const;`
- L33 _public prototype_ `bool HasBasisType() const;`
- L34 _public prototype_ `EGroomBasisType GetBasisType() const;`
- L36 _public prototype_ `bool HasCurveType() const;`
- L37 _public prototype_ `EGroomCurveType GetCurveType() const;`
- L39 _public prototype_ `bool HasKnots() const;`
- L40 _public prototype_ `TArrayAttribute<const float> GetKnots() const;`
- L43 _public prototype_ `int NumVerts() const;` — Per-strand vertex info
- L44 _public prototype_ `const FVector3f& GetVertexPosition(int Index) const;`
- L45 _public prototype_ `TArrayView<const FVector3f> GetVertexPositions() const;`
- L47 _public prototype_ `bool HasVertexWidths() const;`
- L48 _public prototype_ `const float& GetVertexWidth(int Index) const;`
- L49 _public prototype_ `TArrayView<const float> GetVertexWidths() const;`
- L51 _public prototype_ `bool HasVertexAO() const;`
- L52 _public prototype_ `const float& GetVertexAO(int Index) const;`
- L53 _public prototype_ `TArrayView<const float> GetVertexAOs() const;`
- L57 _private prototype_ `FHairStrandAttribsRefProxy() = delete;`
- L58 _private prototype_ `FHairStrandAttribsRefProxy(const FHairDescription& InHairDescription);`
- L60 _private prototype_ `void SetStrand(int InStrandIndex);`
- L62 _private member_ `int StrandIndex;`
- L63 _private member_ `int StartVertIndex;`
- L65 _private member_ `TStrandAttributesConstRef<int> GuideStrands;`
- L66 _private member_ `TStrandAttributesConstRef<int> StrandGroupIds;`
- L67 _private member_ `TStrandAttributesConstRef<float> StrandWidths;`
- L68 _private member_ `TStrandAttributesConstRef<FName> StrandGroupCardsNames;`
- L70 _private member_ `TStrandAttributesConstRef<FName> StrandBasisType;`
- L71 _private member_ `TStrandAttributesConstRef<FName> StrandCurveType;`
- L72 _private member_ `TStrandAttributesConstRef<TArrayAttribute<float>> StrandKnots;`
- L74 _private member_ `TStrandAttributesConstRef<int> StrandVertCounts;`
- L75 _private member_ `TVertexAttributesConstRef<FVector3f> VertexPositions;`
- L76 _private member_ `TVertexAttributesConstRef<float> VertexWidths;`
- L77 _private member_ `TVertexAttributesConstRef<float> VertexAOs;`

#### class `FHairStrandAttribsIteratorEnd`  
`class FHairStrandAttribsIteratorEnd`  
_L82-91_
- desc: Helper iterator clases to make it easier to iterate through strands and get access to per-strand attributes
- L86 _public prototype_ `FHairStrandAttribsIteratorEnd(const FHairDescription& InHairDescription, int32 InEndIndex = INDEX_NONE);`
- L89 _private member_ `int32 EndIndex;`
- L90 _private member_ `const FHairDescription& HairDescription;`

#### class `FHairStrandAttribsConstIterator`  
`class FHairStrandAttribsConstIterator`  
_L93-129_
- L111 _public prototype_ `FHairStrandAttribsConstIterator(const FHairDescription& InHairDescription, int32 InStartIndex = 0, EIgnoreStrandFlags InIgnoreFlags = EIgnoreStrandFlags::DefaultIgnore);`
- L113 _public prototype_ `const FHairStrandAttribsRefProxy& operator*() const;`
- L114 _public prototype_ `const FHairStrandAttribsRefProxy* operator->() const;`
- L115 _public prototype_ `FHairStrandAttribsConstIterator& operator++();`
- L116 _public prototype_ `bool operator!=(const FHairStrandAttribsConstIterator& Iter) const;`
- L117 _public prototype_ `bool operator!=(const FHairStrandAttribsIteratorEnd& Iter) const;`
- L120 _private prototype_ `FHairStrandAttribsConstIterator() = delete;`
- L122 _private prototype_ `void FindFiltered();`
- L124 _private member_ `int32 StrandIndex;`
- L125 _private member_ `EIgnoreStrandFlags IgnoreFlags;`
- L126 _private member_ `const FHairDescription& HairDescription;`
- L128 _private member_ `FHairStrandAttribsRefProxy AttribsProxy;`

#### enum `FHairStrandAttribsConstIterator::EIgnoreStrandFlags`  
`enum EIgnoreStrandFlags`  
_L96-108_
- L99 _public enumerator_ `IgnoreNone = 0x0` — Don't ignore anything
- L102 _public enumerator_ `IgnoreGuides = 0x01` — Ignore guide strands in traversal
- L104 _public enumerator_ `IgnoreEmpty = 0x02` — Ignore empty (NumVerts==0) strands in traversal
- L107 _public enumerator_ `DefaultIgnore = IgnoreGuides | IgnoreEmpty` — Default setting is to ignore guide and empty strands

#### class `FStrandAttributesRange`  
`class FStrandAttributesRange`  
_L132-151_
- desc: Helper traversal class allows use of range-for syntax for getting per-strand attributes
- L138 _public prototype_ `FStrandAttributesRange(const FHairDescription& HairDesc, FHairStrandAttribsConstIterator::EIgnoreStrandFlags InIgnoreFlags = FHairStrandAttribsConstIterator::DefaultIgnore);` — Creates a helper class which will return iterator over each strand in a hair description with an attribute proxy to make it relatively easy to access per-strand attributes @param HairDesc FHairDescription for the groom @param InIgnoreFlags Flags indicating what strands to ignore during traversal (defaults to ignore guide strands and empty (vert) strands)
- L140 _public prototype_ `bool IsValid() const;`
- L141 _public prototype_ `int NumStrands() const;`
- L142 _public prototype_ `int NumVerts() const;`
- L144 _public prototype_ `const FHairStrandAttribsRefProxy& First() const;`
- L146 _public prototype_ `FHairStrandAttribsConstIterator begin() const;`
- L147 _public prototype_ `FHairStrandAttribsIteratorEnd end() const;`
- L149 _private member_ `const FHairDescription& HairDescription;`
- L150 _private member_ `const FHairStrandAttribsConstIterator BeginIter;`

#### class `FComposableStrandFilterOp`  
`class FComposableStrandFilterOp`  
_L155-163_
- desc: Base class for all strand filters
- L158 _public prototype_ `virtual bool FilterStrand(const FHairStrandAttribsRefProxy& StrandAttributes) = 0;`
- L160 _public prototype_ `virtual ~FComposableStrandFilterOp() = default;`
- L162 _protected prototype_ `FComposableStrandFilterOp() = default;`

#### class `FStrandFilterOp_And`  
`class FStrandFilterOp_And : public FComposableStrandFilterOp`  
_L165-174_
- inherits: `FComposableStrandFilterOp`
- L168 _public prototype_ `FStrandFilterOp_And(TUniquePtr<FComposableStrandFilterOp> InLeftOp, TUniquePtr<FComposableStrandFilterOp> InRightOp);`
- L169 _public prototype_ `virtual bool FilterStrand(const FHairStrandAttribsRefProxy& StrandAttributes) override;`
- L172 _private member_ `TUniquePtr<FComposableStrandFilterOp> LeftOp;`
- L173 _private member_ `TUniquePtr<FComposableStrandFilterOp> RightOp;`

#### class `FStrandFilterOp_Or`  
`class FStrandFilterOp_Or : public FComposableStrandFilterOp`  
_L176-185_
- inherits: `FComposableStrandFilterOp`
- L179 _public prototype_ `FStrandFilterOp_Or(TUniquePtr<FComposableStrandFilterOp> InLeftOp, TUniquePtr<FComposableStrandFilterOp> InRightOp);`
- L180 _public prototype_ `virtual bool FilterStrand(const FHairStrandAttribsRefProxy& StrandAttributes) override;`
- L183 _private member_ `TUniquePtr<FComposableStrandFilterOp> LeftOp;`
- L184 _private member_ `TUniquePtr<FComposableStrandFilterOp> RightOp;`

#### class `FStrandFilterOp_InCardGroup`  
`class FStrandFilterOp_InCardGroup : public FComposableStrandFilterOp`  
_L187-195_
- inherits: `FComposableStrandFilterOp`
- L190 _public prototype_ `FStrandFilterOp_InCardGroup(const TSet<FName>& InCardGroupIds);`
- L191 _public prototype_ `virtual bool FilterStrand(const FHairStrandAttribsRefProxy& StrandAttributes) override;`
- L194 _private member_ `TSet<FName> CardGroupNames;`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGenStrandNCSInterpolator.h` (Private)


#### class `FHairCardGenStrandNSCInterpolator`  
`class FHairCardGenStrandNSCInterpolator`  
_L9-25_
- L12 _private member_ `TArray<FHairCardGenNaturalCubicSplines> Splines;`
- L23 _public prototype_ `FHairCardGenStrandNSCInterpolator(const TArray<FVector>& Positions, const TArray<float>& Widths, const TArray<float>& AOs);`
- L24 _public prototype_ `StrandInterpolationResult GetInterpolatedStrand(const int NumInterpolatedPoints);`

#### struct `FHairCardGenStrandNSCInterpolator::StrandInterpolationResult`  
`struct StrandInterpolationResult`  
_L15-20_
- L17 _public member_ `TArray<float> Positions;`
- L18 _public member_ `TArray<float> Widths;`
- L19 _public member_ `TArray<float> AOs;`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorEditorSettings.h` (Private)


#### class `UHairCardGeneratorEditorSettings`  
`class UHairCardGeneratorEditorSettings : public UObject`  
_L14-26_
- reflection: `UCLASS(config = Editor)`
- inherits: `UObject`
- L19 _public prototype_ `UHairCardGeneratorEditorSettings();`
- L22 _public member_ `FString HairCardAssetNameFormat;` — `UPROPERTY(Config)`
- L25 _public member_ `FString HairCardAssetPathFormat;` — `UPROPERTY(Config)`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorLog.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorPluginSettings.h` (Private)


#### enum `EHairCardAtlasSize`  
`enum class EHairCardAtlasSize : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Uninitialized = 0 UMETA(Hidden)`
- L22 _public enumerator_ `AtlasSize1024 = 10 UMETA(DisplayName = "1024 x 1024")`
- L23 _public enumerator_ `AtlasSize2048 = 11 UMETA(DisplayName = "2048 x 2048")`
- L24 _public enumerator_ `AtlasSize4096 = 12 UMETA(DisplayName = "4096 x 4096")`
- L25 _public enumerator_ `AtlasSize8192 = 13 UMETA(DisplayName = "8192 x 8192")`

#### enum `EHairCardGenerationPipeline`  
`enum class EHairCardGenerationPipeline : uint8`  
_L30-62_
- reflection: `UENUM()`
- desc: Helper enumeration for settings dirty bits for pipeline steps
- L32 _public enumerator_ `None = 0x0`
- L34 _public enumerator_ `StrandClustering = 0x01` — Pipeline Steps
- L35 _public enumerator_ `GeometryGeneration = 0x02` — 2. Geometry generation from strand clusters (clumps)
- L36 _public enumerator_ `TextureClustering = 0x04` — 3. Cluster clumps into num_texures, and find the clump that's closest to cluster mean
- L37 _public enumerator_ `TextureLayout = 0x08` — 4. Layout representative clumps in texture atlas
- L38 _public enumerator_ `TextureRendering = 0x10` — 5. Render representative clumps to texture atlas
- L39 _public enumerator_ `GenerateMesh = 0x20` — 6. Generate a mesh from all clumps (card) geometry
- L40 _public enumerator_ `ImportTextures = 0x40` — 7. Import textures and assign to card asset slots
- L45 _public enumerator_ `All = StrandClustering | GeometryGeneration | TextureClustering | TextureLayout | TextureRendering | GenerateMesh | ImportTextures` — HACK: These flag combos should probably be in a separate enum Useful shorthand for flag update checks Some update required
- L53 _public enumerator_ `GroupUpdate = StrandClustering | GeometryGeneration | TextureClustering` — Group pipeline stage update required
- L57 _public enumerator_ `TextureUpdate = TextureLayout | TextureRendering` — Textures will be updated
- L60 _public enumerator_ `ImportUpdate = GenerateMesh | ImportTextures` — Asset import/mesh regen required

#### enum `EHairCardGenerationSettingsCategories`  
`enum class EHairCardGenerationSettingsCategories : uint8`  
_L67-99_
- reflection: `UENUM()`
- L70 _public enumerator_ `None = 0x0` — Settings Categories
- L71 _public enumerator_ `All = (uint8)EHairCardGenerationPipeline::StrandClustering | (uint8)EHairCardGenerationPipeline::GeometryGeneration | (uint8)EHairCardGenerationPipeline::TextureClustering | (uint8)EHairCardGenerationPipeline::TextureLayout | (uint8)EHairCardGenerationPipeline::TextureRendering | (uint8)EHairCardGenerationPipeline::GenerateMesh | (uint8)EHairCardGenerationPipeline::ImportTextures`
- L78 _public enumerator_ `Asset = All`
- L79 _public enumerator_ `LevelOfDetail = All`
- L80 _public enumerator_ `Randomness = All`
- L81 _public enumerator_ `Cards = All`
- L82 _public enumerator_ `Geometry = (uint8)EHairCardGenerationPipeline::GeometryGeneration | (uint8)EHairCardGenerationPipeline::TextureClustering | (uint8)EHairCardGenerationPipeline::TextureLayout | (uint8)EHairCardGenerationPipeline::TextureRendering | (uint8)EHairCardGenerationPipeline::GenerateMesh | (uint8)EHairCardGenerationPipeline::ImportTextures`
- L88 _public enumerator_ `Textures = (uint8)EHairCardGenerationPipeline::TextureClustering | (uint8)EHairCardGenerationPipeline::TextureLayout | (uint8)EHairCardGenerationPipeline::TextureRendering | (uint8)EHairCardGenerationPipeline::GenerateMesh | (uint8)EHairCardGenerationPipeline::ImportTextures`
- L93 _public enumerator_ `TextureRendering = (uint8)EHairCardGenerationPipeline::TextureLayout | (uint8)EHairCardGenerationPipeline::TextureRendering | (uint8)EHairCardGenerationPipeline::GenerateMesh | (uint8)EHairCardGenerationPipeline::ImportTextures`
- L97 _public enumerator_ `Import = (uint8)EHairCardGenerationPipeline::GenerateMesh | (uint8)EHairCardGenerationPipeline::ImportTextures`

#### class `UHairCardGeneratorPluginSettings`  
`class UHairCardGeneratorPluginSettings : public UHairCardGenerationSettings`  
_L122-353_
- reflection: `UCLASS(BlueprintType, config=Editor)`
- inherits: `UHairCardGenerationSettings`
- desc: Self contained hair card generation settings. Separated/Duplicated from the groom asset to: (1) constrain the prompt window's details view, and (2) let the user modify it without mutating the original groom (settings should only be applied/saved when the process is done). UHairCardGenerationPluginSettings holds all the generation settings required to regenerate hair cards for a particular groom asset. Implements the UHairCardGenerationSettings interface so that it can be used with the hair card generation extension module (see IHairCardGenerator API).
- L129 _public member_ `FDirectoryPath DestinationPath;` — `UPROPERTY(EditAnywhere, Category="Import", meta=(ContentDir))` — Destination content path for generated mesh/texture assets
- L133 _public member_ `FString BaseFilename;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Asset")` — Base filename of generated mesh/texture assets
- L137 _public member_ `bool bReduceCardsFromPreviousLOD = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level Of Detail")` — Use previous LOD generated cards and textures but reduce triangle count and flyaways
- L141 _public member_ `bool bGenerateGeometryForAllGroups = true;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadonly, Category="Asset", meta=(AllowPrivateAccess))` — Generate geometry for all groom groups on group 0
- L145 _public member_ `int RandomSeed = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Randomness", meta=(ClampMin="0", ClampMax="10000"))` — Seed value for pseudo-random number generation (set to a specific value for repeatable results)
- L149 _public member_ `bool bUseReservedSpaceFromPreviousLOD = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering")` — Place new card textures in reserved space from previous LOD
- L153 _public member_ `EHairCardAtlasSize AtlasSize = EHairCardAtlasSize::AtlasSize4096;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering")` — Size of hair card texture atlases
- L157 _public member_ `EHairTextureLayout ChannelLayout = EHairTextureLayout::Layout0;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering")` — Texture layout selected (NOTE: This automatically pulls from group 0)
- L161 _public member_ `int ReserveTextureSpaceLOD = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering", meta=(ClampMin="0", ClampMax="75"))` — Percentage of texture atlas space to reserve for higher LODs
- L165 _public member_ `bool bUseGroomAssetStrandWidth = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering")` — Use strand width
- L168 _public member_ `bool bOverrideHairWidth;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering")`
- L171 _public member_ `TArray<float> HairWidths;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering")`
- L174 _public member_ `TArray<float> RootScales;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering")`
- L177 _public member_ `TArray<float> TipScales;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering")`
- L181 _public member_ `float DepthMinimum = -2.0f;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering|Advanced", meta=(ClampMin="-10.0", ClampMax="0.0"))` — Minimum strand depth value (mapped to 0 in depth texture)
- L185 _public member_ `float DepthMaximum = 2.0f;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering|Advanced", meta=(ClampMin="0.0", ClampMax="10.0"))` — Maximum strand depth value (mapped to 1 in depth texture)
- L189 _public member_ `int32 UVSmoothingIterations = 25;` — `UPROPERTY(BlueprintReadOnly, Category="Texture Rendering|Advanced", meta=(ClampMin="0", ClampMax="50"))` — Number of iterations for smoothing strand UVs
- L192 _public member_ `FString OutputPath;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Asset")`
- L194 _public prototype_ `void SetSource(TObjectPtr<UGroomAsset> SourceObject, int32 GenLODIndex = 0, int32 PhysGroupIndex = 0);`
- L196 _public prototype_ `void ResetFromSourceDescription(const FHairGroupsCardsSourceDescription& SourceDesc, const FString& DefaultDirectory, const FString& DefaultName);` — Load last-run values for options from card source description or defaults if no last-run info
- L198 _public prototype_ `bool ResetFromSettingsJson(const FString& DefaultDirectory, const FString& DefaultName);` — Load settings from Json file if one exists
- L200 _public prototype_ `void ResetToDefault(const FString& DefaultDirectory, const FString& DefaultName);` — Load default values for all options
- L201 _public prototype_ `void ResetFilterGroupSettingsToDefault(int FilterGroupIndex);`
- L204 _public prototype_ `void AddNewSettingsFilterGroup();` — UI Hooks for adding/removing settings groups
- L205 _public prototype_ `void RemoveSettingsFilterGroup(TObjectPtr<UHairCardGeneratorGroupSettings> SettingsGroup);`
- L208 _public prototype_ `void MakeSingleFilterGroupSettings();` — Make filter settings for each groups
- L211 _public prototype_ `void BuildFilterGroupSettings(const TArray<TArray<FName>>& FilterCardGroups, const TArray<FName>& FilterGroupNames);` — Build the filter group settings according to a list of valid card groups and names
- L214 _public prototype_ `void WriteGenerationSettings();` — Output settings to json file
- L217 _public prototype_ `static bool CheckGenerationFlags(uint8 NeedsGenFlags, const EHairCardGenerationPipeline PipelineStage);` — Handle mapping settings differences to regeneration requirements
- L218 _public prototype_ `uint8 GetAllPipelineGeneratedDifferences() const;`
- L219 _public prototype_ `uint8 GetPipelineGeneratedDifferences() const;`
- L220 _public prototype_ `void ClearPipelineGenerated() const;`
- L221 _public prototype_ `void WritePipelineGenerated();`
- L222 _public prototype_ `uint8 GetPipelineFilterGroupDifferences(int FilterGroupIndex) const;`
- L223 _public prototype_ `void ClearPipelineGeneratedFilterGroup(int FilterGroupIndex) const;`
- L224 _public prototype_ `void WritePipelineGeneratedFilterGroup(int FilterGroupIndex);`
- L227 _public prototype_ `bool ValidateStrandFilters(TMap<uint32,uint32>& ErrorCountMap);` — Handle checking and applying group settings strand filters
- L228 _public prototype_ `void UpdateStrandFilterAssignment();`
- L231 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L232 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L236 _public prototype_ `virtual void BuildDDCKey(FArchive& Ar) override;`
- L239 _public prototype_ `static bool IsCompatibleSettings(UHairCardGenerationSettings* SettingsObject);`
- L241 _public prototype_ `static FString GetIntermediatePath();`
- L242 _public prototype_ `static FString GetMetadataPath();`
- L243 _public prototype_ `static FString GetGeneratedSettingsPath();`
- L245 _public prototype_ `FString GetTextureImportBaseName() const;`
- L246 _public prototype_ `FString GetTextureImportPath() const;`
- L247 _public prototype_ `FString GetTextureContentPath() const;`
- L249 _public prototype_ `TSharedPtr<FJsonObject> GetFullParent() const;`
- L250 _public prototype_ `bool HasDerivedTextureSettings() const;`
- L251 _public prototype_ `int GetDerivedReservedTextureSize() const;`
- L252 _public prototype_ `FString GetDerivedTextureChannelLayout() const;`
- L254 _public prototype_ `FString GetGroomName() const;`
- L256 _public function_ `UGroomAsset* GetGroomAsset() const`
- L257 _public function_ `int32 GetLODIndex() const`
- L258 _public function_ `int32 GetGenerateForGroomGroup() const`
- L259 _public function_ `void SetGenerateForGroomGroup(int GroupIndex)`
- L260 _public function_ `EHairTextureLayout GetChannelLayout() const`
- L261 _public function_ `bool ValidChannelLayouts() const`
- L263 _public prototype_ `bool CanReduceFromLOD(FText* OutInvalidInfo = nullptr) const;`
- L264 _public prototype_ `bool CanUseReservedTx(FText* OutInvalidInfo = nullptr) const;`
- L266 _public function_ `bool GetForceRegenerate() const`
- L267 _public function_ `void SetForceRegenerate(bool bForceRegenerate)`
- L269 _public function_ `TArray<TObjectPtr<UHairCardGeneratorGroupSettings>>& GetFilterGroupSettings()`
- L270 _public function_ `const TArray<TObjectPtr<UHairCardGeneratorGroupSettings>>& GetFilterGroupSettings() const`
- L272 _public function_ `TObjectPtr<UHairCardGeneratorGroupSettings>& GetFilterGroupSettings(int Index)`
- L273 _public function_ `const TObjectPtr<UHairCardGeneratorGroupSettings>& GetFilterGroupSettings(int Index) const`
- L275 _public prototype_ `void PostResetUpdates();`
- L278 _private prototype_ `void UpdateOutputPaths();`
- L280 _private prototype_ `void UpdateChannelLayout();`
- L282 _private prototype_ `void UpdateParentInfo();`
- L283 _private prototype_ `void UpdateHairWidths();`
- L285 _private prototype_ `void EnforceValidLODSettings();`
- L287 _private prototype_ `bool FindDerivedTextureSettings();`
- L288 _private prototype_ `TSharedPtr<FJsonObject> GetParentTextureSettings() const;`
- L290 _private prototype_ `static TSharedPtr<FJsonObject> TraverseSettingsParents(const FString& SettingsName, TFunction<bool(const TSharedPtr<FJsonObject>&)> StopCond);`
- L292 _private prototype_ `static FString GetSettingsFileFromBase(const FString& SettingsName);`
- L293 _private prototype_ `FString GetSettingsFilename() const;`
- L294 _private prototype_ `FString GetGeneratedSettingsFilename() const;`
- L295 _private prototype_ `FString GetGeneratedGroupSettingsFilename(int GroupIndex) const;`
- L296 _private prototype_ `void ResetFromJson();`
- L297 _private prototype_ `void WriteToJson();`
- L299 _private prototype_ `void SerializeEditableSettings(FArchive& Ar);`
- L301 _private prototype_ `void ResetNumFilterGroups(int Count);`
- L302 _private prototype_ `void ResetFilterGroupSettings(int FilterGroupIndex, TObjectPtr<UHairCardGeneratorGroupSettings> OptionsTemplate);`
- L303 _private prototype_ `void ResetFilterGroupSettings(int FilterGroupIndex, const TSharedPtr<FJsonObject>& OptionsTemplate);`
- L305 _private prototype_ `void ValidateStrandFiltersInternal();`
- L306 _private prototype_ `int32 AssignStrandToFilterGroup(const FHairStrandAttribsRefProxy& StrandAttribs);`
- L307 _private prototype_ `uint32 CheckAllStrandAssignments(const FHairStrandAttribsRefProxy& StrandAttribs);`
- L310 _private member_ `int32 LODIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess))`
- L314 _private member_ `FString Version = TEXT("0.4` — `UPROPERTY(BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess))` — Static HCS version number to force regeneration on tool updates
- L317 _private member_ `TArray<TObjectPtr<UHairCardGeneratorGroupSettings>> FilterGroupGenerationSettings;` — `UPROPERTY(BlueprintReadOnly, Category="Settings Groups", meta=(AllowPrivateAccess))`
- L321 _private member_ `int32 GenerateForGroomGroup = INDEX_NONE;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadonly, Category="Asset", meta=(AllowPrivateAccess))` — The groom group for which geometry will be generated
- L324 _private member_ `FString IntermediatePath;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess))`
- L328 _private member_ `FString BaseParentName;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Level Of Detail", meta=(AllowPrivateAccess))` — The base name of direct parent LOD level, used for resubdividing geometry or writing to reserved texture layout regions
- L332 _private member_ `FString DerivedTextureSettingsName;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Level Of Detail", meta=(AllowPrivateAccess))` — The base name of LOD from which texture info/outputs will be pulled (for writing to reserved texture layouts)
- L335 _private member_ `TArray<FName> CardGroupIds;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Settings Groups", meta=(AllowPrivateAccess))`
- L338 _private member_ `TArray<int> StrandFilterGroupIndexMap;` — `UPROPERTY(Transient,BlueprintReadOnly, Category="Settings Groups", meta=(AllowPrivateAccess))`
- L342 _private member_ `bool bValidChannelLayouts;` — `UPROPERTY(Transient)` — All group texture layouts are the same (required for current texture generation)
- L345 _private member_ `TObjectPtr<UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(Transient)`
- L348 _private member_ `TObjectPtr<const UStaticMesh> OldGeneratedMesh = nullptr;` — `UPROPERTY(Transient)`
- L350 _private member_ `bool bForceRegen;`
- L351 _private member_ `uint32 UnassignedStrandsCount;`
- L352 _private member_ `TMap<uint32,uint32> StrandErrorCountMap;`

#### class `UHairCardGeneratorGroupSettings`  
`class UHairCardGeneratorGroupSettings : public UObject`  
_L361-470_
- reflection: `UCLASS(BlueprintType, config=Editor)`
- inherits: `UObject`
- desc: Actual generation settings. Held in TArray, with strand filters applied to determine which settings apply to each strand (See FComposableStrandFilter).
- L368 _private member_ `int32 StrandCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings Group", meta=(AllowPrivateAccess))`
- L371 _private member_ `FString GenerateFilename;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess))`
- L374 _private member_ `int32 LODIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Asset", meta=(AllowPrivateAccess))`
- L377 _private member_ `FString ParentName;` — `UPROPERTY(Transient, BlueprintReadOnly, Category="Level Of Detail", meta=(AllowPrivateAccess))`
- L380 _private member_ `TObjectPtr<const UGroomAsset> GroomAsset = nullptr;` — `UPROPERTY(Transient)`
- L382 _private member_ `bool StrandFilterChecksDirty = false;`
- L383 _private member_ `TUniquePtr<FComposableStrandFilterOp> StrandsFilter;`
- L386 _private member_ `FName FilterName;` — `UPROPERTY(EditAnywhere, Category="Cards")`
- L391 _public member_ `TSet<FName> ApplyToCardGroups = {NAME_None};` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")` — Specify which strands (card group ids) this settings group applies to
- L395 _public member_ `int32 TargetNumberOfCards = 2000;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards", meta=(ClampMin="1", ClampMax="100000"))` — Total number of cards to generate for this settings group
- L399 _public member_ `int32 TargetTriangleCount = 20000;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Geometry", meta=(ClampMin="2", ClampMax="1000000"))` — Target number of triangles of the final mesh, only for adaptive subdivision
- L403 _public member_ `int MaxNumberOfFlyaways = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards", meta=(ClampMin="0", ClampMax="1000"))` — Maximum number of cards to assign to flyaway strands
- L407 _public member_ `bool UseMultiCardClumps = true;` — `UPROPERTY(BlueprintReadOnly, Category="Geometry")` — Generate multiple cards (3) per strand clump to give the appearance of volume
- L411 _public member_ `bool UseAdaptiveSubdivision = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Geometry|Advanced")` — Use adaptive subdivision when generating card geometry
- L415 _public member_ `int32 MaxVerticalSegmentsPerCard = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Geometry|Advanced", meta=(ClampMin="1", ClampMax="15"))` — Maximum number of segments along each card (aligned with the strands), ignored for adaptive subdivision
- L419 _public member_ `int32 NumberOfTexturesInAtlas = 75;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Textures", meta=(ClampMin="1", ClampMax="300"))` — Number of strand clump textures per atlas
- L423 _public member_ `float StrandWidthScalingFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering", meta=(ClampMin="0.0", ClampMax="300.0"))` — Scaling factor mapping strand-width to pixel-size for coverage texture
- L428 _public member_ `bool UseOptimizedCompressionFactor = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Texture Rendering")` — Compress textures along strand direction to save vertical redolution, if strands are all moving in nearly the same direction
- L431 _public prototype_ `void Reset(TObjectPtr<UHairCardGeneratorGroupSettings> TemplateObject);`
- L432 _public prototype_ `void Reset(const TSharedPtr<FJsonObject>& TemplateSettings);`
- L433 _public prototype_ `void ResetFilterDefault(const TArray<FName>& CardGroupIds);`
- L434 _public prototype_ `void UpdateStrandFilter();`
- L435 _public prototype_ `void UpdateGenerateFilename(const FString& BaseFilename, int index);`
- L436 _public prototype_ `void UpdateParentName(const FString& BaseParentName, int index);`
- L438 _public prototype_ `void RemoveSettingsFilterGroup();`
- L441 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L442 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L445 _public prototype_ `uint8 GetFilterGroupGeneratedFlags() const;`
- L446 _public prototype_ `bool GetReduceFromPreviousLOD() const;`
- L448 _public prototype_ `void BuildDDCSubKey(FArchive& Ar);`
- L450 _public function_ `int32 GetStrandCount()`
- L453 _public function_ `const FName& GetFilterName() const` — Get the filter name
- L456 _public function_ `void SetFilterName(const FName& InFilterName)` — Set the filter name with a given identifier
- L459 _private prototype_ `void SetSource(TObjectPtr<const UGroomAsset> SourceGroom, int32 GenLODIndex = 0);`
- L461 _private prototype_ `FString GetGeneratedFilterGroupSettingsFilename() const;`
- L463 _private prototype_ `void SerializeGroupSettings(FArchive& Ar);`
- L465 _private prototype_ `uint8 GetPipelineFilterGroupDifferences() const;`
- L466 _private prototype_ `void ClearPipelineGeneratedFilterGroup() const;`
- L467 _private prototype_ `void WritePipelineGeneratedFilterGroup();`
- L469 _private prototype_ `void SetStrandStats();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace HairCardSettings_Helpers`
- L15 _prototype_ `void GetStrandCardGroupInfo(TObjectPtr<const UGroomAsset> GroomAsset, TArray<FName>& OutGrpIds, TArray<int32>& OutGrpCount);` (scope `HairCardSettings_Helpers`)
- L101 _namespace_ `namespace HairCardSettings_Helpers`
- L103 _prototype_ `FString GetGroomDirectoryForHairCards(TObjectPtr<const UGroomAsset> GroomAsset);` (scope `HairCardSettings_Helpers`)
- L104 _prototype_ `FString GetGroomNameForHairCards(TObjectPtr<const UGroomAsset> GroomAsset);` (scope `HairCardSettings_Helpers`)
- L105 _prototype_ `FString GetDefaultBaseNameForHairCards(TObjectPtr<const UGroomAsset> GroomAsset, int LODIndex, const FString& DefaultName);` (scope `HairCardSettings_Helpers`)
- L106 _prototype_ `FString GetDefaultDestinationPathForHairCards(TObjectPtr<const UGroomAsset> GroomAsset, int LODIndex, const FString& DefaultDirectory, const FString& DefaultName);` (scope `HairCardSettings_Helpers`)

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Public/HairCardGenTypes.h` (Public)


#### struct `FHairCardClumpData`  
`struct FHairCardClumpData`  
_L12-23_
- reflection: `USTRUCT(BlueprintType)`
- desc: Output of GenerateClumps / input to SetOptimizations. Per-settings-group; saved and loaded by SaveClumpData / LoadClumpData.
- L18 _public member_ `TArray<int32> StrandLabels;` — `UPROPERTY(BlueprintReadWrite, Category="Clustering")` — (N_strands,) clump label index per strand
- L22 _public member_ `int32 MaxMainClump = 0;` — `UPROPERTY(BlueprintReadWrite, Category="Clustering")` — Largest main-clump index; used to separate flyaway from standard clumps in label list

#### struct `FHairCardMeshData`  
`struct FHairCardMeshData`  
_L32-63_
- reflection: `USTRUCT(BlueprintType)`
- desc: Card mesh geometry for one settings group, stored as flat concatenated arrays. All cards are concatenated; use CardVertOffsets/CardFaceOffsets to slice per card. Embedded in FHairCardGeomData. Replaces per-card OBJ files in the Dataflow path (Layer 5B).
- L38 _public member_ `TArray<float> Verts;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (TotalVerts * 3,) flattened xyz — all cards concatenated
- L42 _public member_ `TArray<int32> Faces;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (TotalFaces * 3,) flattened vertex indices — card-local, use offsets to get global
- L46 _public member_ `TArray<float> SurfaceUvs;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (TotalVerts * 2,) flattened uv — card surface parameterisation used for strand projection
- L50 _public member_ `TArray<int32> CardVertOffsets;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (N_cards,) start vert index per card into Verts/SurfaceUVs
- L54 _public member_ `TArray<int32> CardVertCounts;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (N_cards,) vert count per card
- L58 _public member_ `TArray<int32> CardFaceOffsets;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (N_cards,) start face index per card into Faces
- L62 _public member_ `TArray<int32> CardFaceCounts;` — `UPROPERTY(BlueprintReadWrite, Category="Mesh")` — (N_cards,) face count per card

#### struct `FHairCardGeomData`  
`struct FHairCardGeomData`  
_L72-109_
- reflection: `USTRUCT(BlueprintType)`
- desc: Output of GenerateCardsGeometry / input to ClusterTextures and all cross-group stages. Per-settings-group; saved and loaded by SaveGeomData / LoadGeomData. CardCount is used by cross-group stages to compute global card ID offsets.
- L78 _public member_ `TArray<float> CardsLength;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards,) card length
- L82 _public member_ `TArray<float> CardsWidth;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards,) card width
- L86 _public member_ `TArray<float> CardsLrRatio;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards,) left/right border ratio
- L90 _public member_ `TArray<float> CardsTopVec;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards * 3,) flattened card top-vector (used for orientation)
- L100 _public member_ `TArray<int32> CardsType;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards,) card type id. Separates flyaway cards from standard cards for texture clustering. Stored in card_type.npy (formerly cards_texture_group.npy). 0 - standard card 1 - flyaway card
- L104 _public member_ `TArray<int32> CardsLabel;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_strands,) card index per strand (global card ID in cross-group context)
- L108 _public member_ `TArray<uint8> CardsPhysGrpIdx;` — `UPROPERTY(BlueprintReadWrite, Category="Geometry")` — (N_cards,) physics group label per card

#### struct `FHairCardTextureClusterData`  
`struct FHairCardTextureClusterData`  
_L117-132_
- reflection: `USTRUCT(BlueprintType)`
- desc: Output of ClusterTextures / input to all cross-group stages. Per-settings-group; saved and loaded by SaveClusterData / LoadClusterData.
- L123 _public member_ `TArray<int32> ClustersLabel;` — `UPROPERTY(BlueprintReadWrite, Category="TextureCluster")` — (N_cards,) cluster index per card
- L127 _public member_ `TArray<int32> ClustersCenterId;` — `UPROPERTY(BlueprintReadWrite, Category="TextureCluster")` — (N_clusters,) center card index per cluster
- L131 _public member_ `TArray<bool> CardsFlipped;` — `UPROPERTY(BlueprintReadWrite, Category="TextureCluster")` — (N_cards,) flip flag per card

#### struct `FHairCardAtlasLayoutData`  
`struct FHairCardAtlasLayoutData`  
_L139-158_
- reflection: `USTRUCT(BlueprintType)`
- desc: Texture atlas layout information for each texture to render
- L145 _public member_ `TArray<int32> TxtSize;` — `UPROPERTY(BlueprintReadWrite, Category="TextureLayout")` — (N_centers * 2,) flattened [width, height] texture size for each cluster center
- L149 _public member_ `TArray<int32> TxtCoords;` — `UPROPERTY(BlueprintReadWrite, Category="TextureLayout")` — (N_centers * 2,) flattened [x, y] atlas coordinate per cluster center
- L153 _public member_ `TArray<int32> CenterCardsId;` — `UPROPERTY(BlueprintReadWrite, Category="TextureLayout")` — (N_centers,) global card id per cluster center

#### struct `FHairCardAtlasBinpackData`  
`struct FHairCardAtlasBinpackData`  
_L165-188_
- reflection: `USTRUCT(BlueprintType)`
- desc: Binary partition info used internally for current atlas layout algorithm
- L171 _public member_ `TArray<int32> Children;` — `UPROPERTY(BlueprintReadWrite, Category="Binpack")` — (N_nodes * 2,) flattened child node indices; -1 = None (leaf)
- L175 _public member_ `TArray<int32> Bounds;` — `UPROPERTY(BlueprintReadWrite, Category="Binpack")` — (N_nodes * 4,) flattened [min_x, min_y, max_x, max_y] bounds per node
- L179 _public member_ `TArray<bool> IsFull;` — `UPROPERTY(BlueprintReadWrite, Category="Binpack")` — (N_nodes,) node full flag
- L183 _public member_ `TArray<bool> IsReserved;` — `UPROPERTY(BlueprintReadWrite, Category="Binpack")` — (N_nodes,) node reserved flag
- L187 _public member_ `int32 MarginPx = 0;` — `UPROPERTY(BlueprintReadWrite, Category="Binpack")` — Margin in pixels; invariant across all nodes

#### struct `FHairCardAtlasUVData`  
`struct FHairCardAtlasUVData`  
_L196-203_
- reflection: `USTRUCT(BlueprintType)`
- desc: Per-vertex atlas UV coordinates, produced by GenerateTextureLayout alongside the layout data. Flat array parallel to FHairCardMeshData.SurfaceUvs — same vertex ordering, no sentinels.
- L202 _public member_ `TArray<float> VertexUvs;` — `UPROPERTY(BlueprintReadWrite, Category="TextureLayout")` — (TotalVerts * 2,) flattened [u, v] atlas UV per vertex

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Public/HairCardGeneratorEditorModule.h` (Public)


#### struct `FCardsGenerationAdvancedOptions`  
`struct FCardsGenerationAdvancedOptions`  
_L13-41_
- L16 _public member_ `bool bReduceCardsFromPreviousLOD = false;` — Use previous LOD generated cards and textures but reduce triangle count and flyaways
- L19 _public member_ `bool bGenerateGeometryForAllGroups = true;` — Generate geometry for all groom groups on group 0
- L22 _public member_ `int32 RandomSeed = 0;` — Seed value for pseudo-random number generation (set to a specific value for repeatable results)
- L25 _public member_ `bool bUseReservedSpaceFromPreviousLOD = false;` — Place new card textures in reserved space from previous LOD
- L28 _public member_ `uint8 AtlasSize = 12;` — Size of hair card texture atlases
- L31 _public member_ `int32 ReserveTextureSpaceLOD = 0;` — Percentage of texture atlas space to reserve for higher LODs
- L34 _public member_ `bool bUseGroomAssetStrandWidth = true;` — Use strand width
- L37 _public member_ `FString DefaultDirectory = "";` — Default directory to be used if defined
- L40 _public member_ `FString DefaultName = "";` — Default name to be used if defined

#### struct `FHairCardGeneratorUtils`  
`struct FHairCardGeneratorUtils`  
_L44-81_
- desc: FHairCardGeneratorUtils has static interface functions to be used in other modules
- L46 _public typedef_ `using FGeneratorFunction = std::function<bool(const TObjectPtr<const UHairCardGeneratorPluginSettings>&, const int32, const uint8)>;`
- L47 _public typedef_ `using FBuilderFunction = std::function<void(TArray<TArray<FVector>>&)>;`
- L50 _public prototype_ `static bool BuildGenerationSettings(const bool bQuerySettings, UGroomAsset* GroomAsset, FHairGroupsCardsSourceDescription& CardsDesc, TObjectPtr<UHairCardGeneratorPluginSettings>& GenerationSettings, uint8& GenerationFlags, uint8& PipelineFlags, const FCardsGenerationAdvancedOptions& AdvancedOptions);` — Build the generation settings for a given grom asset and a cards description
- L54 _public prototype_ `static bool LoadGenerationSettings(const TObjectPtr<UHairCardGeneratorPluginSettings>& GenerationSettings);` — Load the generation settings for a given grom asset and a cards description
- L57 _public prototype_ `static bool GenerateCardsClumps(const TObjectPtr<const UHairCardGeneratorPluginSettings>& GenerationSettings, const int32 FilterIndex, const uint8 GenFlags, FHairCardClumpData& OutClumpData);` — Generate the cards clumps based on the settings given a filter index
- L60 _public prototype_ `static bool GenerateCardsGeometry(const TObjectPtr<const UHairCardGeneratorPluginSettings>& GenerationSettings, const int32 FilterIndex, const uint8 GenFlags, FHairCardGeomData& OutGeomData, FHairCardMeshData& OutMeshData, int32& OutCardCount);` — Generate the cards geometry based on the settings given a filter index
- L63 _public prototype_ `static bool GenerateCardsTexturesClusters(const TObjectPtr<const UHairCardGeneratorPluginSettings>& GenerationSettings, const int32 FilterIndex, const uint8 GenFlags, FHairCardTextureClusterData& OutClusterData);` — Generate the cards texture clusters based on the settings given a filter index
- L67 _public prototype_ `static bool GenerateTexturesLayoutAndAtlases(const TObjectPtr<const UHairCardGeneratorPluginSettings>& GenerationSettings, const uint8 GenFlags, FHairCardAtlasLayoutData& OutLayoutData, FHairCardAtlasUVData& OutAtlasUVData);` — Generate the cards texture layout and atlases. OutLayoutData is populated from layout generation or loaded from disk. OutAtlasUVData is populated when layout is generated; empty when layout is skipped (only rendering reruns).
- L70 _public prototype_ `static bool RunCardsGeneration(const TObjectPtr<UHairCardGeneratorPluginSettings>& GenerationSettings, const uint8 PipelineFlags, const FGeneratorFunction& PipelineFunction, const bool bCheckFlags = true);` — Run the cards generation function
- L73 _public prototype_ `static bool BuildCardsAssets(UGroomAsset* NewGroomAsset, FHairGroupsCardsSourceDescription& CardsDesc, const TObjectPtr<UHairCardGeneratorPluginSettings>& GenerationSettings, const uint8 GenFlags);` — Build and save the cards assets to disk
- L77 _public prototype_ `static bool LoadGroomStrands(const UGroomAsset* GroomAsset, const FBuilderFunction& BuilderFunction);` — Load the groom strands
- L80 _public prototype_ `static void BuildCardsGroups(TObjectPtr<const UGroomAsset> GroomAsset, TArray<FName>& GroupNames, TArray<int32>& GroupCount);` — Build the cards group names

#### class `FHairCardGeneratorEditorModule`  
`class FHairCardGeneratorEditorModule : public IHairCardGeneratorEditor`  
_L84-96_
- inherits: `IHairCardGeneratorEditor`
- desc: FHairCardGeneratorEditorModule
- L88 _public prototype_ `virtual void StartupModule() override;`
- L89 _public prototype_ `virtual void ShutdownModule() override;`
- L93 _public prototype_ `virtual bool GenerateHairCardsForLOD(UGroomAsset* Groom, FHairGroupsCardsSourceDescription& CardsDesc) override;`
- L94 _public prototype_ `virtual bool IsCompatibleSettings(UHairCardGenerationSettings* OldSettings) override;`

### `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Public/IHairCardGeneratorEditor.h` (Public)


#### class `IHairCardGeneratorEditor`  
`class IHairCardGeneratorEditor : public IModuleInterface, public IHairCardGenerator`  
_L9-16_
- inherits: `IModuleInterface,IHairCardGenerator`
- L12 _public function_ `static inline IHairCardGeneratorEditor& Get()`
