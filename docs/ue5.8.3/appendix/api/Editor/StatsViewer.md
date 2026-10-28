# Editor / StatsViewer

- module root: `Source/Editor/StatsViewer`
- headers: 24; symbols: 372
- symbol kinds: class=22, delegate=3, enum=9, enumerator=24, externvar=1, function=33, member=112, namespace=2, prototype=163, struct=3
- DynamicallyLoadedModuleNames: PropertyEditor
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, EditorFramework, Engine, InputCore, Landscape, RHI, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: PropertyEditor

### `Source/Editor/StatsViewer/Classes/CookerStats.h` (Public)


#### enum `ECookerStatsObjectSets`  
`enum ECookerStatsObjectSets : int`  
_L13-16_
- reflection: `UENUM()`
- desc: Enum defining the object sets for this stats object
- L15 _public enumerator_ `CookerStatsObjectSets_Default UMETA(DisplayName="Default", ToolTip="View cooker statistics")`

#### class `UCookerStats`  
`class UCookerStats : public UObject`  
_L25-45_
- reflection: `UCLASS(Transient, MinimalAPI, meta=(DisplayName="Cooker Stats", ObjectSetType="ECookerStatsObjectSets"))`
- inherits: `UObject`
- desc: Statistics for a cooked asset. Note: We assume that asset files are not larger than 2GB, because the StatsViewer is still lacking int64 support.
- L32 _private member_ `TArray<TWeakObjectPtr<UObject>> Assets;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=(DisplayName="Asset(s)", ColumnWidth="100"))` — The assets contained in the file.
- L36 _private member_ `float SizeBefore;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=(DisplayName="Size (Original)", ColumnWidth="50", ShowTotal="true", Unit="KB"))` — The size of the assets before cooking.
- L40 _private member_ `float SizeAfter;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=(DisplayName="Size (Cooked)", ColumnWidth="50", ShowTotal="true", Unit="KB"))` — The size of the assets after cooking.
- L44 _private member_ `FString Path;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=(ColumnWidth="300"))` — Asset path without the name "package.[group.]"

### `Source/Editor/StatsViewer/Classes/LightingBuildInfo.h` (Public)


#### enum `ELightingBuildInfoObjectSets`  
`enum ELightingBuildInfoObjectSets : int`  
_L13-16_
- reflection: `UENUM()`
- desc: Enum defining the object sets for this stats object
- L15 _public enumerator_ `LightingBuildInfoObjectSets_Default UMETA( DisplayName = "Default" , ToolTip = "View lighting build statistics" )`

#### class `ULightingBuildInfo`  
`class ULightingBuildInfo : public UObject`  
_L20-64_
- reflection: `UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Lighting Build Info", ObjectSetType = "ELightingBuildInfoObjectSets" ))`
- inherits: `UObject`
- desc: Statistics page for lighting.
- L26 _private member_ `TWeakObjectPtr<UObject> Object;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "150" ))` — The actor and/or object that is related to this info.
- L30 _private member_ `float LightingTime;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "200", ShowTotal = "true", Unit = "s" ))` — The lighting time this object took.
- L34 _private member_ `float UnmappedTexelsPercentage;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Unmapped Texels", ShowTotal = "true", ColumnWidth = "142", Unit = "%" ))` — The percentage of unmapped texels for this object.
- L38 _private member_ `float UnmappedTexelsMemory;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "194", ShowTotal = "true", Unit = "KB" ))` — The memory consumed by unmapped texels for this object, in KB
- L42 _private member_ `float TotalTexelMemory;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "220", ShowTotal = "true", SortMode = "Descending", Unit = "KB" ))` — The memory consumed by all texels for this object, in KB
- L46 _private member_ `FString LevelName;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "168" ))` — The name of the level this object resides in
- L58 _public prototype_ `virtual void Set( TWeakObjectPtr<UObject> Object, double LightingTime, float UnmappedTexelsPercentage, int32 UnmappedTexelsMemory, int32 TotalTexelMemory );` — Set the values for this stats entry @param	Object						The object this lighting info relates to @param	LightingTime				The time in seconds that this objects lighting build took @param	UnmappedTexelsPercentage	The percentage of unmapped texels for this object @param	UnmappedTexelsMemory		The memory consumed by unmapped texels for this object, in bytes @param	TotalTexelMemory			The memory consumed by all texels for this object, in bytes
- L63 _private prototype_ `void UpdateNames();` — Update internal strings

### `Source/Editor/StatsViewer/Classes/PrimitiveStats.h` (Public)


#### enum `EPrimitiveObjectSets`  
`enum EPrimitiveObjectSets : int`  
_L15-20_
- reflection: `UENUM()`
- desc: Enum defining the object sets for this stats object
- L17 _public enumerator_ `PrimitiveObjectSets_AllObjects UMETA( DisplayName = "All Objects" , ToolTip = "View primitive statistics for all objects in all levels" )`
- L18 _public enumerator_ `PrimitiveObjectSets_CurrentLevel UMETA( DisplayName = "Current Level" , ToolTip = "View primitive statistics for objects in the current level" )`
- L19 _public enumerator_ `PrimitiveObjectSets_SelectedObjects UMETA( DisplayName = "Selected Objects" , ToolTip = "View primitive statistics for selected objects" )`

#### class `UPrimitiveStats`  
`class UPrimitiveStats : public UObject`  
_L24-116_
- reflection: `UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Primitive Stats", ObjectSetType = "EPrimitiveObjectSets" ))`
- inherits: `UObject`
- desc: Statistics page for primitives.
- L30 _private member_ `TWeakObjectPtr<UObject> Object;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Object", ColumnWidth = "200" ))` — Resource (e.g. UStaticMesh, USkeletalMesh, UModelComponent, UTerrainComponent, etc
- L34 _private member_ `TArray< TWeakObjectPtr<AActor> > Actors;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Actor(s)", ColumnWidth = "200" ))` — Actor(s) that use the resource - click to select & zoom Actor(s)
- L38 _private member_ `FString Type;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Type", ColumnWidth = "200" ))` — Type name
- L42 _private member_ `int32 Count;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "86", ShowTotal = "true" ))` — Number of occurrences in map
- L46 _private member_ `int32 Sections;` — `UPROPERTY()` — Section count of mesh
- L50 _private member_ `int32 HWInstances;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "102", ShowTotal = "true"))` — Hardware instances
- L54 _private member_ `int32 InstSections;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "102", ShowTotal = "true" ))` — Instanced section count of mesh
- L58 _private member_ `int32 Triangles;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Tris", ColumnWidth = "74", ShowTotal = "true" ))` — Triangle count of mesh
- L62 _private member_ `int32 InstTriangles;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Sum Tris", ColumnWidth = "104", ShowTotal = "true" ))` — Triangle count of all mesh occurances (Count * Tris)
- L66 _private member_ `float ResourceSize;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Size", ColumnWidth = "78", ShowTotal = "true", SortMode = "Descending", Unit = "KB" ))` — Resource size in KB
- L70 _private member_ `float VertexColorMem;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "VC", ColumnWidth = "68", ShowTotal = "true", Unit = "KB" ))` — Vertex color stat for static and skeletal meshes in KB
- L74 _private member_ `float InstVertexColorMem;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Inst VC", ColumnWidth = "94", ShowTotal = "true", Unit = "KB" ))` — Per component vertex color stat for static meshes in KB
- L78 _private member_ `int32 LightsLM;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Avg LM", ColumnWidth = "96", ShowTotal = "true" ))` — Average number of lightmap lights relevant to each instance
- L82 _private member_ `float LightsOther;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Avg OL", ColumnWidth = "94", ShowTotal = "true" ))` — Average number of other lights relevant to each instance
- L86 _private member_ `float LightsTotal;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Sum Avg", ColumnWidth = "104", ShowTotal = "true" ))` — (Avg OL + Avg LM) / Count
- L90 _private member_ `float ObjLightCost;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Cost", ColumnWidth = "78", ShowTotal = "true" ))` — Avg OL * Sections
- L94 _private member_ `float LightMapData;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "LM", ColumnWidth = "70", ShowTotal = "true", Unit = "KB" ))` — Light map data in KB
- L98 _private member_ `float LMSMResolution;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Res", ColumnWidth = "74", ShowTotal = "true" ))` — Light/shadow map resolution
- L102 _private member_ `double RadiusMin;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Min R", ColumnWidth = "84", ShowTotal = "true" ))` — Minimum radius of bounding sphere of instance in map
- L106 _private member_ `double RadiusMax;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Max R", ColumnWidth = "88", ShowTotal = "true" ))` — Maximum radius of bounding sphere of instance in map
- L110 _private member_ `double RadiusAvg;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Avg R", ColumnWidth = "86", ShowTotal = "true" ))` — Average radius of bounding sphere of instance in map
- L115 _public prototype_ `void UpdateNames();` — Update internal strings

### `Source/Editor/StatsViewer/Classes/ShaderCookerStats.h` (Public)


#### enum `EShaderCookerStatsSets`  
`enum EShaderCookerStatsSets : int`  
_L13-16_
- reflection: `UENUM()`
- L15 _public enumerator_ `EShaderCookerStatsSets_Default UMETA(DisplayName = "Default", ToolTip = "Shader Cooker Sets")`

#### class `UShaderCookerStats`  
`class UShaderCookerStats : public UObject`  
_L20-58_
- reflection: `UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Shader Cooker Stats", ObjectSetType = "EShaderCookerStatsSets" ))`
- inherits: `UObject`
- desc: Statistics page for shader cooker stats.
- L26 _private member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "200"))` — Material name
- L30 _private member_ `FString Platform;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "50"))` — Material platform
- L34 _private member_ `FString Category;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "50", ToolTip = "Material Category. Edit Engine/Config/ShaderConfiguration.csv & Engine/Config/ShaderConfiguration.csv to configure"))` — Material Category
- L38 _private member_ `int32 Compiled;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Compiled", ToolTip = "Number of shaders that was actually compiled and not present in the DDC", ColumnWidth = "74", ShowTotal = "true"))` — Number of shaders compilations
- L42 _private member_ `int32 Cooked;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Cooked", ToolTip = "Total number of shaders cooked", ColumnWidth = "74", ShowTotal = "true"))` — Number of shaders cooked
- L46 _private member_ `int32 Permutations;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Permutations", ToolTip = "Number of material permutations generated by switch etc.", ColumnWidth = "74", ShowTotal = "true"))` — Number of permutations
- L50 _private member_ `float CompileTime ;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Compile Time", ToolTip = "Cpu time spent compiling shaders not in DDC", ColumnWidth = "74", ShowTotal = "true"))` — Time spent compiling
- L54 _private member_ `FString Path;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "200"))` — Material path
- L57 _private member_ `int32 CategoryIndex;`

### `Source/Editor/StatsViewer/Classes/StaticMeshLightingInfo.h` (Public)


#### enum `EStaticMeshLightingInfoObjectSets`  
`enum EStaticMeshLightingInfoObjectSets : int`  
_L17-22_
- reflection: `UENUM()`
- desc: Enum defining the object sets for this stats object
- L19 _public enumerator_ `StaticMeshLightingInfoObjectSets_CurrentLevel UMETA( DisplayName = "Current Level" , ToolTip = "View static mesh lighting info for the current level" )`
- L20 _public enumerator_ `StaticMeshLightingInfoObjectSets_SelectedLevels UMETA( DisplayName = "Selected Levels" , ToolTip = "View lighting info for selected levels" )`
- L21 _public enumerator_ `StaticMeshLightingInfoObjectSets_AllLevels UMETA( DisplayName = "All Levels" , ToolTip = "View static mesh lighting info for all levels" )`

#### class `UStaticMeshLightingInfo`  
`class UStaticMeshLightingInfo : public UObject`  
_L26-93_
- reflection: `UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Static Mesh Lighting Info", ObjectSetType = "EStaticMeshLightingInfoObjectSets" ))`
- inherits: `UObject`
- desc: Statistics page for static meshes.
- L32 _private member_ `TWeakObjectPtr<AActor> StaticMeshActor;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Actor", ColumnWidth = "200" ))` — The actor that is related to this error/warning.
- L36 _private member_ `TWeakObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "200" ))` — The source StaticMesh that is related to this info.
- L40 _private member_ `FString LevelName;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Level", ColumnWidth = "150" ))` — Cached version of the level name this object resides in
- L43 _private member_ `TWeakObjectPtr<UStaticMeshComponent> StaticMeshComponent;` — The staticmesh component that is related to this info.
- L47 _private member_ `FString TextureMapping;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Type", ColumnWidth = "82" ))` — Current mapping type string
- L51 _private member_ `bool bTextureMapping;` — `UPROPERTY()` — Current mapping type flag - not displayed
- L55 _private member_ `bool bHasLightmapTexCoords;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "UVs", ColumnWidth = "76" ))` — Does the Lightmap have UVs?
- L59 _private member_ `int32 StaticLightingResolution;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Res", ColumnWidth = "74" ))` — The static lighting resolution the texture mapping was estimated with.
- L63 _private member_ `float TextureLightMapMemoryUsage;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Texture LM", ShowTotal = "true", ColumnWidth = "118", Unit = "KB" ))` — Estimated memory usage in KB for light map texel data.
- L67 _private member_ `float VertexLightMapMemoryUsage;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Vertex LM", ShowTotal = "true", ColumnWidth = "112", Unit = "KB" ))` — Estimated memory usage in KB for light map vertex data.
- L71 _private member_ `int32 LightMapLightCount;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Num LM", ShowTotal = "true", ColumnWidth = "100" ))` — Num lightmap lights
- L75 _private member_ `float TextureShadowMapMemoryUsage;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Texture SM", ShowTotal = "true", ColumnWidth = "120", SortMode = "Descending", Unit = "KB" ))` — Estimated memory usage in KB for shadow map texel data.
- L79 _private member_ `float VertexShadowMapMemoryUsage;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Vertex SM", ShowTotal = "true", ColumnWidth = "112", Unit = "KB" ))` — Estimated memory usage in KB for shadow map vertex data.
- L83 _private member_ `int32 ShadowMapLightCount;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Num SM", ShowTotal = "true", ColumnWidth = "102" ))` — Number of lights generating shadow maps on the primitive.
- L87 _private member_ `TArray<FString> LightmapTextureNames;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (DisplayName = "Lightmap Names", ColumnWidth = "300"))` — The lighting texture names that the static mesh component references.
- L92 _public prototype_ `void UpdateNames();` — Update internal strings

### `Source/Editor/StatsViewer/Classes/TextureStats.h` (Public)


#### enum `ETextureObjectSets`  
`enum ETextureObjectSets : int`  
_L18-30_
- reflection: `UENUM()`
- desc: Enum defining the object sets for this stats object
- L20 _public enumerator_ `TextureObjectSet_CurrentStreamingLevel UMETA( DisplayName = "Current Streaming Level" , ToolTip = "Display texture statistics for the current streaming level" )`
- L21 _public enumerator_ `TextureObjectSet_AllStreamingLevels UMETA( DisplayName = "All Streaming Levels" , ToolTip = "Display texture statistics for all streaming levels" )`
- L22 _public enumerator_ `TextureObjectSet_SelectedActors UMETA( DisplayName = "Selected Actor(s)" , ToolTip = "Display texture statistics of selected Actors" )`
- L23 _public enumerator_ `TextureObjectSet_SelectedMaterials UMETA( DisplayName = "Selected Materials(s)" , ToolTip = "Display texture statistics of selected Materials" )`

#### class `UTextureStats`  
`class UTextureStats : public UObject`  
_L34-97_
- reflection: `UCLASS(Transient, MinimalAPI, meta=( DisplayName = "Texture Stats", ObjectSetType = "ETextureObjectSets" ))`
- inherits: `UObject`
- desc: Statistics page for textures.
- L40 _private member_ `TWeakObjectPtr<UTexture> Texture;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Name", ColumnWidth = "100" ))` — Texture - click to go to asset
- L44 _private member_ `TArray< TWeakObjectPtr<AActor> > Actors;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Actor(s)", ColumnWidth = "100" ))` — Actor(s) - click to select & zoom Actor(s)
- L48 _private member_ `FString Type;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "60" ))` — Texture type e.g. 2D, 3D, Cube, "" if not known, ...
- L52 _private member_ `FString Virtual;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Stats", meta = (ColumnWidth = "60"))` — Is the texture virtual? Yes/No
- L56 _private member_ `FVector2D MaxDim;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Max Dimension", ColumnWidth = "90" ))` — Max Dimension e.g. 256x256, not including the format
- L60 _private member_ `FVector2D CurrentDim;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Current Dimension", ColumnWidth = "90" ))` — Current Dimension e.g 256x256
- L64 _private member_ `TEnumAsByte<EPixelFormat> Format;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "96" ))` — The texture format, e.g. PF_DXT1
- L68 _private member_ `TEnumAsByte<TextureGroup> Group;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "94" ))` — The texture group, TEXTUREGROUP_MAX is not used, e.g. TEXTUREGROUP_World
- L72 _private member_ `int32 CombinedLODBias;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "CombinedLODBias", ColumnWidth = "50" ))` — Combined LOD Bias for this texture. (Texture LODBias + Texture group)
- L76 _private member_ `int32 TextureLODBias;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "LODBias", ColumnWidth = "50" ))` — LOD Bias for this texture.
- L80 _private member_ `float CurrentKB;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Current Memory", ColumnWidth = "80", ShowTotal = "true", Unit = "KB" ))` — The memory used currently in KB
- L84 _private member_ `float FullyLoadedKB;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=(DisplayName = "Fully Loaded Memory", ColumnWidth = "110", ShowTotal = "true", SortMode = "Descending", Unit = "KB" ))` — The memory used when the texture is fully loaded in KB
- L88 _private member_ `int32 NumUses;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Uses", ColumnWidth = "74", ShowTotal = "true" ))` — The number of times the texture is used
- L92 _private member_ `float LastTimeRendered;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( DisplayName = "Last Seen", ColumnWidth = "78", Unit = "s" ))` — Relative time it was used for rendering the last time
- L96 _private member_ `FString Path;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category="Stats", meta=( ColumnWidth = "200" ))` — Texture path without the name "package.[group.]"

### `Source/Editor/StatsViewer/Private/ActorArrayHyperlinkColumn.h` (Private)


#### class `FActorArrayHyperlinkColumn`  
`class FActorArrayHyperlinkColumn : public IPropertyTableCustomColumn`  
_L17-25_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to display names of objects that can be clicked on to jump to the objects in the scene or content browser.
- L21 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;` — Begin IPropertyTableCustomColumn interface
- L22 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L23 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`

### `Source/Editor/StatsViewer/Private/ObjectHyperlinkColumn.h` (Private)


#### class `FObjectHyperlinkColumn`  
`class FObjectHyperlinkColumn : public IPropertyTableCustomColumn`  
_L18-39_
- inherits: `IPropertyTableCustomColumn`
- desc: A property table custom column used to display names of objects that can be clicked on to jump to the objects in the scene or content browser.
- L21 _public prototype_ `FObjectHyperlinkColumn(const FObjectHyperlinkColumnInitializationOptions& InOptions = FObjectHyperlinkColumnInitializationOptions());`
- L24 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;` — Begin IPropertyTableCustomColumn interface
- L25 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L26 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L32 _private member_ `FOnGenerateWidget OnGenerateWidget;` — Delegate called to generate a custom widget
- L35 _private member_ `FOnObjectHyperlinkClicked OnObjectHyperlinkClicked;` — Delegate called when a hyperlink is clicked
- L38 _private member_ `FOnIsClassSupported OnIsClassSupported;` — Delegate used to query whether a UClass is supported

### `Source/Editor/StatsViewer/Private/SStatsViewer.h` (Private)


#### class `SStatsViewer`  
`class SStatsViewer : public IStatsViewer`  
_L19-184_
- inherits: `IStatsViewer`
- desc: Stats Viewer widget
- L23 _public function_ `SLATE_BEGIN_ARGS( SStatsViewer )`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr< FStatsPageManager >, StatsPageManager) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L35 _public prototype_ `SStatsViewer();` — SStatsViewer constructor
- L38 _public prototype_ `virtual ~SStatsViewer();` — SStatsViewer destructor
- L41 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L44 _public prototype_ `virtual void Refresh() override;` — Begin IStatsViewer interface
- L45 _public prototype_ `TSharedPtr< class IPropertyTable > GetPropertyTable() override;`
- L46 _public prototype_ `int32 GetObjectSetIndex() const override;`
- L47 _public prototype_ `void SwitchAndFilterPage(int32 Page, const FString& FilterValue, const FString& FilterProperty) override;`
- L57 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called by the editable text control when the filter text is changed by the user @param	InFilterText	The new text
- L64 _private prototype_ `void OnFilterTextCommitted( const FText& InFilterText, ETextCommit::Type CommitInfo );` — Called by the editable text control when a user presses enter or commits their text change @param	InFilterText	The new text @param	CommitInfo		The type of commit
- L67 _private prototype_ `FText OnGetDisplayMenuLabel() const;` — Generate label for the display combobox
- L70 _private prototype_ `FText OnGetObjectSetMenuLabel() const;` — Generate label for the displayed objects combobox
- L73 _private prototype_ `TSharedRef<SWidget> OnGetDisplayMenuContent() const;` — Build the menu for the display combobox
- L76 _private prototype_ `TSharedRef<SWidget> OnGetObjectSetMenuContent() const;` — Build the menu for the object set combobox
- L79 _private prototype_ `TSharedRef<SWidget> OnGetFilterMenuContent() const;` — Build the menu for the filter combobox
- L82 _private prototype_ `EVisibility OnGetObjectSetsVisibility() const;` — Check whether the object sets combo box is visible for the currently selected stats
- L85 _private prototype_ `EVisibility OnGetStatsVisibility() const;` — Check whether the various UI elements are visible for the currently selected stats
- L91 _private prototype_ `void SetDisplayedStats( TSharedRef< class IStatsPage > StatsPage );` — Set the displayed set of stats @param	StatsPage The stats page to set
- L98 _private prototype_ `bool AreStatsDisplayed( TSharedRef< class IStatsPage > StatsPage ) const;` — Check if the displayed set of stats is currently visible @param	StatsPage The stats page to set @returns true if the page is currently visible
- L101 _private prototype_ `FText OnGetFilterComboButtonLabel() const;` — Get the label for the filter combo button
- L107 _private prototype_ `void SetObjectSet( int32 InSetIndex );` — Set the currently displayed object set @param	InSetIndex	The index of the object set to display
- L114 _private prototype_ `bool IsObjectSetSelected( int32 InSetIndex ) const;` — Check whether the currently displayed object set matches the passed-in index @param	InSetIndex	The index of the object set to check @returns true if the displayed object set matches the passed in index
- L120 _private prototype_ `void SetSearchFilter( int32 InFilterIndex );` — Set the currently selected search filter @param	InFilterIndex	The filter index to set
- L127 _private prototype_ `bool IsSearchFilterSelected( int32 InFilterIndex ) const;` — Check whether the currently displayed search filter matches the passed-in index @param	InFilterIndex	The index of the search filter to check @returns true if the displayed search filter matches the passed in index
- L130 _private prototype_ `FReply OnRefreshClicked();` — We just clicked the refresh button
- L133 _private prototype_ `FReply OnExportClicked();` — We just clicked the export button
- L136 _private prototype_ `FStatsPageManager& GetStatsPageManager() const;` — Get a valid stats page manager
- L141 _private member_ `bool bNeedsRefresh;` — Flag to refresh the table next tick
- L144 _private member_ `bool bNeedsRefreshForFilterChange;` — Flag to refresh the table triggered by a filter change
- L147 _private member_ `float SearchTextUpdateTimer;` — Timer to prevent constant update of the searched items when typing
- L150 _private member_ `TSharedPtr< SSearchBox > FilterTextBoxWidget;` — Widget containing the filtering text box
- L153 _private member_ `TSharedPtr< class IPropertyTable > PropertyTable;` — The property table we are viewing
- L156 _private member_ `TSharedPtr< class IStatsPage > CurrentStats;` — The currently displayed stats factory
- L159 _private member_ `int32 CurrentObjectSetIndex;` — The current object set selected
- L162 _private member_ `FString FilterText;` — The current filter text
- L165 _private member_ `int32 CurrentFilterIndex;` — The current filter selected
- L168 _private member_ `TArray< TWeakObjectPtr<UObject> > CurrentObjects;` — The current set of objects we are viewing
- L171 _private member_ `TArray< TWeakObjectPtr<UObject> > LastGeneratedObjectList;` — The last generated set of objects that will be used when refresh triggered by a filter change
- L174 _private member_ `TSharedRef<class FStatsCustomColumn> CustomColumn;` — The 'total' custom column used for displaying totals for properties that support the feature
- L177 _private member_ `TSharedPtr< SBorder > CustomContent;` — Container for custom content supplied by stats pages
- L180 _private member_ `TSharedPtr< SBorder > CustomFilter;` — Container for custom filters supplied by stats pages
- L183 _private member_ `TSharedPtr < FStatsPageManager > StatsPageManagerPtr;` — The page manager that is managing our pages. Can be invalid, in which case the global one will be used

### `Source/Editor/StatsViewer/Private/StatsCustomColumn.h` (Private)


#### class `FStatsCustomColumn`  
`class FStatsCustomColumn : public TSharedFromThis< FStatsCustomColumn >, public IPropertyTableCustomColumn`  
_L28-68_
- inherits: `TSharedFromThis<FStatsCustomColumn>,IPropertyTableCustomColumn`
- desc: A property table custom column used to display numerical data. Also supports FVector2D UStruct properties Will display totals in the column header if they are supplied in the TotalsMap
- L32 _public prototype_ `virtual bool Supports( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities ) const override;` — Begin IPropertyTableCustomColumn interface
- L33 _public prototype_ `virtual TSharedPtr< SWidget > CreateColumnLabel( const TSharedRef< IPropertyTableColumn >& Column, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L34 _public prototype_ `virtual TSharedPtr< IPropertyTableCellPresenter > CreateCellPresenter( const TSharedRef< IPropertyTableCell >& Cell, const TSharedRef< IPropertyTableUtilities >& Utilities, const FName& Style ) const override;`
- L42 _public prototype_ `static bool SupportsProperty( const FProperty* Property );` — Helper function to check if we can support displaying this property @param	Property	The property to check @returns true if this property is supported for display by this column type
- L49 _public prototype_ `static FText GetPropertyAsText( const TSharedPtr< IPropertyHandle > PropertyHandle, bool bGetRawValue = false);` — Helper function to get the text we would display for this property @param	PropertyHandle	The property handle to retrieve the text from returns a string representation of the properties data, or an empty string if the property is unsupported
- L54 _public member_ `TMap<FString, FText> TotalsMap;` — The map we use to find our totals to display
- L62 _private prototype_ `FText GetTotalText(TSharedRef< IPropertyTableColumn > Column) const;` — Delegate to display the total text @param	Column	The column to get the total text for
- L67 _private member_ `TWeakObjectPtr<UObject> TotalObject;` — The total object, if any

### `Source/Editor/StatsViewer/Private/StatsPageManager.h` (Private)


#### class `FStatsPageManager`  
`class FStatsPageManager`  
_L16-73_
- desc: A class which manages a the collection of known stats pages
- L19 _public function_ `FStatsPageManager(const FName& InName = NAME_None) : Name( InName )`
- L20 _public prototype_ `virtual ~FStatsPageManager() = default;`
- L23 _public prototype_ `static FStatsPageManager& Get();` — Gets the instance of this manager
- L25 _public function_ `const FName& GetName() const`
- L32 _public prototype_ `void RegisterPage( int32 PageId, TSharedRef<class IStatsPage> InPage );` — Register a page with the manager @param	PageId	Use specific page id (must be unique) @param	InPage	The page to register
- L38 _public prototype_ `void RegisterPage( TSharedRef<class IStatsPage> InPage );` — Register a page with the manager @param	InPage	The page to register
- L44 _public prototype_ `void UnregisterPage( TSharedRef<class IStatsPage> InPage );` — Unregister a page from the manager @param	InPage	The page to unregister
- L47 _public prototype_ `void UnregisterAllPages();` — Unregister & delete all registered pages
- L50 _public prototype_ `int32 NumPages() const;` — Get the number of stats pages we have
- L53 _public prototype_ `TSharedRef<class IStatsPage> GetPageByIndex( int32 InPageIndex );` — Get the page at the specified index
- L56 _public prototype_ `TSharedRef<class IStatsPage> GetPage( int32 InPageId );` — Get page by its type
- L59 _public prototype_ `TSharedPtr<class IStatsPage> GetPage( const FName& InPageName );` — Get the factory with the specified name
- L62 _private prototype_ `int GetPageIndex(int32 PageId) const;`
- L63 _private prototype_ `int GetPageIndex(TSharedRef< IStatsPage > InPage) const;`
- L66 _private member_ `static const int32 PageIdNone;` — = -1;
- L69 _private member_ `TArray< TSharedRef<class IStatsPage> > StatsPages;` — The registered pages
- L70 _private member_ `TArray< int32 > StatsPageIds;`
- L72 _private member_ `FName Name;`

### `Source/Editor/StatsViewer/Private/StatsPages/CookerStatsPage.h` (Private)


#### class `FCookerStatsPage`  
`class FCookerStatsPage : public FStatsPage<UCookerStats>`  
_L16-57_
- inherits: `FStatsPage<UCookerStats>`
- desc: Implements a Stats page representing cooker statistics.
- L22 _public prototype_ `static FCookerStatsPage& Get( );` — Singleton accessor.
- L25 _public prototype_ `virtual ~FCookerStatsPage( ) = default;` — Virtual destructor.
- L31 _public prototype_ `virtual void Generate( TArray<TWeakObjectPtr<UObject>>& OutObjects ) const override;`
- L32 _public prototype_ `virtual void GenerateTotals( const TArray<TWeakObjectPtr<UObject>>& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L33 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomFilter( TWeakPtr<class IStatsViewer> InParentStatsViewer ) override;`
- L34 _public prototype_ `virtual void OnShow( TWeakPtr<class IStatsViewer> InParentStatsViewer ) override;`
- L35 _public prototype_ `virtual void OnHide( ) override;`
- L40 _private prototype_ `TSharedRef<SWidget> HandleFilterComboButtonGetMenuContent( ) const;` — Callback for getting the filter combo button's menu content.
- L43 _private prototype_ `FText HandleFilterComboButtonText( ) const;` — Callback for getting the filter combo button's text label.
- L46 _private prototype_ `EVisibility HandleFilterComboButtonVisibility( ) const;` — Callback for getting the filter combo button's visibility.
- L49 _private prototype_ `void HandleFilterMenuEntryExecute( FString PlatformName );` — Callback for executing a filter menu entry.
- L52 _private prototype_ `bool HandleFilterMenuEntryIsChecked( FString PlatformName ) const;` — Callback for determining whether a filter menu entry should be marked checked.
- L56 _private member_ `FString SelectedPlatformName;`

### `Source/Editor/StatsViewer/Private/StatsPages/LightingBuildInfoStatsPage.h` (Private)


#### class `FLightingBuildInfoStatsPage`  
`class FLightingBuildInfoStatsPage : public FStatsPage<ULightingBuildInfo>`  
_L10-34_
- inherits: `FStatsPage<ULightingBuildInfo>`
- desc: Stats page representing lighting build info
- L14 _public prototype_ `static FLightingBuildInfoStatsPage& Get();` — Singleton accessor
- L17 _public prototype_ `virtual void Clear() override;` — Begin IStatsPage interface
- L18 _public prototype_ `virtual void AddEntry( UObject* InEntry ) override;`
- L19 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const override;`
- L20 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L23 _public prototype_ `virtual ~FLightingBuildInfoStatsPage() = default;`
- L32 _private member_ `TArray< TWeakObjectPtr<ULightingBuildInfo> > Entries;` — The list of objects we will display. This stat entry differs from others in that the data it displays is not derived directly from the scene/assets, rather it is collected at build time and stored here

### `Source/Editor/StatsViewer/Private/StatsPages/PrimitiveStatsPage.h` (Private)


#### class `FPrimitiveStatsPage`  
`class FPrimitiveStatsPage : public FStatsPage<UPrimitiveStats>`  
_L11-40_
- inherits: `FStatsPage<UPrimitiveStats>`
- desc: Stats page representing primitive component stats
- L15 _public prototype_ `static FPrimitiveStatsPage& Get();` — Singleton accessor
- L18 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const override;` — Begin IStatsPage interface
- L19 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L20 _public prototype_ `virtual void OnShow( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override;`
- L21 _public prototype_ `virtual void OnHide() override;`
- L24 _public prototype_ `virtual ~FPrimitiveStatsPage() = default;`
- L33 _private prototype_ `void OnEditorSelectionChanged( UObject* NewSelection, TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to allow is to trigger a refresh on object selection @param	NewSelection		The new selected object @param	InParentStatsViewer	The parent stats viewer of this page
- L39 _private prototype_ `void OnEditorNewCurrentLevel( TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to allow is to trigger a refresh on new level @param	InParentStatsViewer	The parent stats viewer of this page

### `Source/Editor/StatsViewer/Private/StatsPages/ShaderCookerStatsPage.h` (Private)


#### class `FShaderCookerStatsPage`  
`class FShaderCookerStatsPage : public FStatsPage<UShaderCookerStats>, public TSharedFromThis<FShaderCookerStatsPage>`  
_L16-52_
- inherits: `FStatsPage<UShaderCookerStats>,TSharedFromThis<FShaderCookerStatsPage>`
- desc: Stats page representing material cooking stats
- L20 _public prototype_ `static FShaderCookerStatsPage& Get();` — Singleton accessor
- L23 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const override;` — Begin IStatsPage interface
- L24 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L25 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomWidget(TWeakPtr< class IStatsViewer > InParentStatsViewer) override;`
- L26 _public prototype_ `virtual void OnShow( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override;`
- L27 _public prototype_ `virtual void OnHide() override;`
- L28 _public prototype_ `virtual int32 GetObjectSetCount() const override;`
- L29 _public prototype_ `virtual FString GetObjectSetName(int32 InObjectSetIndex) const override;`
- L30 _public prototype_ `virtual FString GetObjectSetToolTip(int32 InObjectSetIndex) const override;`
- L34 _public prototype_ `virtual ~FShaderCookerStatsPage() = default;`
- L38 _private prototype_ `FText OnGetPlatformMenuLabel() const;` — Generate label for the displayed objects combobox
- L39 _private prototype_ `void OnPlatformClicked(TWeakPtr<IStatsViewer> InParentStatsViewer, int32 Index);`
- L40 _private prototype_ `bool IsPlatformSetSelected(int32 Index) const;`
- L41 _private prototype_ `TSharedRef<SWidget> OnGetPlatformButtonMenuContent(TWeakPtr< class IStatsViewer > InParentStatsViewer) const;`
- L44 _private member_ `TSharedPtr<SWidget> CustomWidget;` — Custom widget for this page
- L47 _private member_ `TSharedPtr<SComboButton> PlatformComboButton;` — Platform combo button
- L50 _private member_ `int32 SelectedPlatform = 0;` — Current Platform

### `Source/Editor/StatsViewer/Private/StatsPages/StaticMeshLightingInfoStatsPage.h` (Private)


#### struct `ESwapOptions`  
`struct ESwapOptions`  
_L14-21_

#### enum `ESwapOptions::Type`  
`enum Type`  
_L16-20_
- L18 _public enumerator_ `Swap = 0`
- L19 _public enumerator_ `SwapAskRes`

#### struct `ESetToOptions`  
`struct ESetToOptions`  
_L23-31_

#### enum `ESetToOptions::Type`  
`enum Type`  
_L25-30_
- L27 _public enumerator_ `Vertex = 0`
- L28 _public enumerator_ `Texture`
- L29 _public enumerator_ `TextureAskRes`

#### class `FStaticMeshLightingInfoStatsPage`  
`class FStaticMeshLightingInfoStatsPage : public FStatsPage<UStaticMeshLightingInfo>, public TSharedFromThis<FStaticMeshLightingInfoStatsPage>`  
_L34-135_
- inherits: `FStatsPage<UStaticMeshLightingInfo>,TSharedFromThis<FStaticMeshLightingInfoStatsPage>`
- desc: Stats page representing static mesh lighting info
- L38 _public prototype_ `static FStaticMeshLightingInfoStatsPage& Get();` — Singleton accessor
- L41 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const override;` — Begin IStatsPage interface
- L42 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomWidget(TWeakPtr< class IStatsViewer > InParentStatsViewer) override;`
- L44 _public prototype_ `virtual void OnShow( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override;`
- L45 _public prototype_ `virtual void OnHide() override;`
- L48 _public prototype_ `virtual ~FStaticMeshLightingInfoStatsPage() = default;`
- L56 _private prototype_ `TSharedRef<SWidget> OnGetSwapComboButtonMenuContent(TWeakPtr< class IStatsViewer > InParentStatsViewer) const;` — Get the content for the swap combo button menu @param	InParentStatsViewer	The parent stats viewer of this page
- L62 _private prototype_ `TSharedRef<SWidget> OnGetSetToComboButtonMenuContent(TWeakPtr< class IStatsViewer > InParentStatsViewer) const;` — Get the content for the 'set to' combo button menu @param	InParentStatsViewer	The parent stats viewer of this page
- L69 _private prototype_ `void OnSwapClicked(TWeakPtr< class IStatsViewer > InParentStatsViewer, ESwapOptions::Type InSwapOption) const;` — Swap button was clicked @param	InParentStatsViewer	The parent stats viewer of this page @param	InSwapOption		The type to swap to
- L76 _private prototype_ `void OnSetToClicked(TWeakPtr< class IStatsViewer > InParentStatsViewer, ESetToOptions::Type InSetToOption) const;` — 'Set to' button was clicked @param	InParentStatsViewer	The parent stats viewer of this page @param	InSetToOption		The type to set to
- L84 _private prototype_ `void SetMappingMethodOnSelectedComponents(TWeakPtr< class IStatsViewer > InParentStatsViewer, bool bInTextureMapping, int32 InStaticLightingResolution) const;` — Helper function to set the mapping method on selected components @param	InParentStatsViewer			The parent stats viewer of this page @param	bInTextureMapping			Whether to set to texture mode or not @param	InStaticLightingResolution	The lightmap resolution to set the selected components to
- L91 _private prototype_ `void SwapMappingMethodOnSelectedComponents(TWeakPtr< class IStatsViewer > InParentStatsViewer, int32 InStaticLightingResolution) const;` — Helper function to swap the mapping method on selected components @param	InParentStatsViewer			The parent stats viewer of this page @param	InStaticLightingResolution	The lightmap resolution to set the selected components to
- L99 _private prototype_ `void GetUserSetStaticLightmapResolution(TWeakPtr< class IStatsViewer > InParentStatsViewer, bool bSwap) const;` — Helper function to set static lighting resolution - displays a type-in popup that calls back to OnResolutionCommitted when a value is entered @param	InParentStatsViewer	The parent stats viewer of this page @param	bSwap				Whether we are swapping or setting the value
- L108 _private prototype_ `void OnResolutionCommitted(const FText& ResolutionText, ETextCommit::Type CommitInfo, TWeakPtr< class IStatsViewer > InParentStatsViewer, bool bSwap) const;` — Helper function to set static lighting resolution @param	ResolutionText		The text the user typed in @param	CommitInfo			The type of commit @param	InParentStatsViewer	The parent stats viewer of this page @param	bSwap				Whether we are swapping or setting the value
- L114 _private prototype_ `void OnEditorNewCurrentLevel( TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to allow is to trigger a refresh on new level @param	InParentStatsViewer	The parent stats viewer of this page
- L120 _private prototype_ `void OnEditorLevelSelected( TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to allow is to trigger a refresh level selection @param	InParentStatsViewer	The parent stats viewer of this page
- L125 _private member_ `TSharedPtr<SComboButton> SwapComboButton;` — Swap combo button
- L128 _private member_ `TSharedPtr<SComboButton> SetToComboButton;` — 'Set to' combo button
- L131 _private member_ `TSharedPtr<SWidget> CustomWidget;` — Custom widget for this page
- L134 _private member_ `mutable TWeakPtr<class IMenu> ResolutionEntryMenu;` — Reference to owner of the current popup

### `Source/Editor/StatsViewer/Private/StatsPages/TextureStatsPage.h` (Private)


#### class `FTextureStatsPage`  
`class FTextureStatsPage : public FStatsPage<UTextureStats>`  
_L12-37_
- inherits: `FStatsPage<UTextureStats>`
- desc: Stats page representing texture stats
- L16 _public prototype_ `static FTextureStatsPage& Get();` — Singleton accessor
- L19 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const override;` — Begin IStatsPage interface
- L20 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const override;`
- L21 _public prototype_ `virtual void OnShow( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override;`
- L22 _public prototype_ `virtual void OnHide() override;`
- L25 _public prototype_ `virtual ~FTextureStatsPage() = default;`
- L30 _private prototype_ `void OnEditorSelectionChanged( UObject* NewSelection, TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to trigger a refresh on actor selection
- L33 _private prototype_ `void OnEditorNewCurrentLevel( TWeakPtr< class IStatsViewer > InParentStatsViewer );` — Delegate to trigger a refresh on new level
- L36 _private prototype_ `void OnAssetPostCompile( const TArray<FAssetCompileData>& CompiledAssets, TWeakPtr< IStatsViewer > InParentStatsViewer );` — Delegate to trigger a refresh when a texture finishes compiling

### `Source/Editor/StatsViewer/Public/IStatsPage.h` (Public)


#### class `IStatsPage`  
`class IStatsPage`  
_L29-154_
- desc: The public interface for a stats page. A stats page displays a collection of identically-typed objects with columns based around their UPROPERTY()'s The table does its best to display the relevant information. Objects UCLASS metadata required are: DisplayName		- The name displayed in the page selection dropdown. Tooltip			- The tooltip displayed in the page selection dropdown. ObjectSetType	- A text representation of the UENUM used for object set enumeration. The object set UENUM also uses metadata to display certain information. UENUM metadata syntax differs from UCLASS metadata as it is specified via the UMETA() tag, rather than meta=() UPROPERTY subtags. DisplayName		- The name displayed in the object set dropdown. ToolTip			- The tooltip displayed over the object set dropdown. The UI supports the following UPROPERTY metadata: ColumnWidth		- Integer value. The (proportionally-based, not absolute) width of the properties column. ShowTotal		- Either true or false. Whether the column header should attempt to show a total (provided in Generate() via the OutTotals map). SortMode			- Either Ascending or Descending. If this is specified then the properties column will be sorted on table creation. Unit				- Text value displayed next to table entries and totals
- L38 _public function_ `virtual void Clear()` — Clears any entries added via AddEntry() Not all pages have to override this - only ones that accept transient data output from processes that do not persist in the editor
- L45 _public function_ `virtual void AddEntry( UObject* InEntry )` — Adds a stats entry to the page Not all pages have to override this - only ones that accept transient data output from processes that do not persist in the editor
- L51 _public prototype_ `virtual void Show( bool bShow = true ) = 0;` — Tries to switch the currently displayed page to this one @param	bShow	Whether to show the page (passing false will not hide the page)
- L54 _public prototype_ `virtual bool IsShowPending() const = 0;` — Check if this page wants to show itself
- L60 _public prototype_ `virtual void Refresh( bool bRefresh = true ) = 0;` — Sends a requests to the stats page to refresh itself the next chance it gets @param	bRefresh	Whether to refresh the page (the page will refresh on the stats viewers next tick)
- L63 _public prototype_ `virtual bool IsRefreshPending() const = 0;` — Check if this page wants to refresh itself
- L66 _public prototype_ `virtual FName GetName() const = 0;` — Get the name of the entry type
- L69 _public prototype_ `virtual const FText GetDisplayName() const = 0;` — Get the name of the entry type to be displayed in the page selection dropdown
- L72 _public prototype_ `virtual const FText GetToolTip() const = 0;` — Get the tooltip to be displayed over the page selection dropdown
- L75 _public prototype_ `virtual int32 GetObjectSetCount() const = 0;` — Get the number of object sets this page supports
- L81 _public prototype_ `virtual FString GetObjectSetName( int32 InObjectSetIndex ) const = 0;` — Get the name of the object set, to be displayed in the dropdown @param	InObjectSetIndex	The index of the object set to get the name of
- L87 _public prototype_ `virtual FString GetObjectSetToolTip( int32 InObjectSetIndex ) const = 0;` — Get the tooltip of the object set, to be displayed over the object set the dropdown @param	InObjectSetIndex	The index of the object set to get the tooltip for
- L93 _public prototype_ `virtual UClass* GetEntryClass() const = 0;` — Get the class of the entry we handle This is needed to display the search filter's combo button
- L100 _public prototype_ `virtual void Generate( TArray< TWeakObjectPtr<UObject> >& OutObjects ) const = 0;` — Fill the output array with statistic objects to be displayed @param OutObjects	The object array to be filled
- L108 _public prototype_ `virtual void GenerateTotals( const TArray< TWeakObjectPtr<UObject> >& InObjects, TMap<FString, FText>& OutTotals ) const = 0;` — Totals are displayed by mapping the CPP name of the columns property to the total string in the OutTotals map. @param OutTotals		A map of Property->GetNameCPP() -> Total string
- L114 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomFilter( TWeakPtr< class IStatsViewer > InParentStatsViewer ) = 0;` — Get custom filter to display in the top part of the stats viewer, can return nullptr @param	InParentStatsViewer	The parent stats viewer
- L120 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomWidget( TWeakPtr< class IStatsViewer > InParentStatsViewer ) = 0;` — Get custom widget to display in the top part of the stats viewer, can return nullptr @param	InParentStatsViewer	The parent stats viewer
- L126 _public function_ `virtual void OnShow( TWeakPtr< class IStatsViewer > InParentStatsViewer )` — Called back each time the page is shown @param	InParentStatsViewer	The parent stats viewer
- L129 _public function_ `virtual void OnHide()` — Called back each time the page is hidden
- L135 _public prototype_ `virtual void SetSelectedObjectSet( int32 InObjectSetIndex ) = 0;` — Set the currently displayed object set @param	InObjectSetIndex	The object set index to set
- L138 _public prototype_ `virtual int32 GetSelectedObjectSet() const = 0;` — Get the currently displayed object set
- L144 _public prototype_ `virtual void GetCustomColumns(TArray< TSharedRef< class IPropertyTableCustomColumn > >& OutCustomColumns) const = 0;` — Get any column customizations that this page wants to use. @param	OutCustomColumns	The array to be filled in containing column customizations.
- L150 _public prototype_ `virtual void SetWorld(UWorld& InWorld) = 0;` — Set a specific world to use for page statistics. @param	InWorld The world to use.
- L153 _public prototype_ `virtual UWorld* GetWorld() const = 0;` — Get the world used for page statistics.

### `Source/Editor/StatsViewer/Public/IStatsViewer.h` (Public)


#### class `IStatsViewer`  
`class IStatsViewer : public SCompoundWidget`  
_L12-27_
- inherits: `SCompoundWidget`
- desc: The public interface for the Stats Viewer widget
- L18 _public prototype_ `virtual void Refresh() = 0;` — Sends a requests to the Stats Viewer to refresh itself the next chance it gets
- L21 _public prototype_ `virtual TSharedPtr< class IPropertyTable > GetPropertyTable() = 0;` — Get the property table we are displaying
- L24 _public prototype_ `virtual int32 GetObjectSetIndex() const = 0;` — Get the currently selected object set
- L26 _public prototype_ `virtual void SwitchAndFilterPage(int32 Table, const FString& FilterValue, const FString& FilterProperty) = 0;`

### `Source/Editor/StatsViewer/Public/ObjectHyperlinkColumnInitializationOptions.h` (Public)


#### struct `FObjectHyperlinkColumnInitializationOptions`  
`struct FObjectHyperlinkColumnInitializationOptions`  
_L19-40_
- desc: Struct used to further customize object hyperlink custom columns.
- L26 _public member_ `FOnGenerateWidget OnGenerateWidget;` — Delegate called to generate a custom widget for display in a cell of a UObject custom column. Note that overriding this means that the calling code is responsible for handling interactions with the widget, i.e. OnObjectHyperlinkClicked will not be called.
- L32 _public member_ `FOnObjectHyperlinkClicked OnObjectHyperlinkClicked;` — Delegate called when a hyperlink is clicked in a UObject custom column Note that this is not called if OnGenerateWidget is bound.
- L39 _public member_ `FOnIsClassSupported OnIsClassSupported;` — Delegate used to query whether a UClass is supported by a UObject custom column. Use this to implement custom columns that support your weak object type or override an existing internal implementation.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<class SWidget>, FOnGenerateWidget, const FText& , const TWeakObjectPtr< UObject >& );` — Delegate called to generate a custom widget for display in a cell of a UObject custom column
- L8 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<class SWidget>, FOnGenerateWidget, const FText& , const TWeakObjectPtr< UObject >& );` — Delegate called to generate a custom widget for display in a cell of a UObject custom column
- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectHyperlinkClicked, const TWeakObjectPtr< UObject >& );` — Delegate called when a hyperlink is clicked in a UObject custom column
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectHyperlinkClicked, const TWeakObjectPtr< UObject >& );` — Delegate called when a hyperlink is clicked in a UObject custom column
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsClassSupported, const UClass* );` — Delegate used to query whether a UClass is supported by a UObject custom column
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsClassSupported, const UClass* );` — Delegate used to query whether a UClass is supported by a UObject custom column

### `Source/Editor/StatsViewer/Public/StatsCellPresenter.h` (Public)


#### class `FStatsCellPresenter`  
`class FStatsCellPresenter : public IPropertyTableCellPresenter`  
_L12-59_
- inherits: `IPropertyTableCellPresenter`
- desc: Boilerplate implementations of IPropertyTableCellPresenter functions. Here so we dont have to override all these functions each time.
- L16 _public function_ `virtual bool RequiresDropDown() override` — Begin IPropertyTableCellPresenter interface
- L21 _public function_ `virtual TSharedRef< class SWidget > ConstructEditModeCellWidget() override`
- L26 _public function_ `virtual TSharedRef< class SWidget > ConstructEditModeDropDownWidget() override`
- L31 _public function_ `virtual TSharedRef< class SWidget > WidgetToFocusOnEdit() override`
- L36 _public function_ `virtual bool HasReadOnlyEditMode() override`
- L41 _public function_ `virtual FString GetValueAsString() override`
- L46 _public function_ `virtual FText GetValueAsText() override`
- L58 _protected member_ `FText Text;` — The text we display - we just store this as we never need to *edit* properties in the stats viewer, only view them. Therefore we dont need to dynamically update this string.

### `Source/Editor/StatsViewer/Public/StatsPage.h` (Public)


#### class `FStatsPage`  
`template <typename Entry> class FStatsPage : public IStatsPage`  
_L20-161_
- inherits: `IStatsPage`
- desc: Template for all stats pages/factories. These classes generate uniform arrays of identically-typed objects that are displayed in a PropertyTable. Boilerplate implementations are below that all pages in this module currently more-or-less share
- L23 _public function_ `FStatsPage()`
- L34 _public prototype_ `virtual ~FStatsPage() = default;`
- L37 _public function_ `virtual void Show( bool bInShow = true ) override` — Begin IStatsPage interface
- L42 _public function_ `virtual bool IsShowPending() const override`
- L47 _public function_ `virtual void Refresh( bool bInRefresh = true ) override`
- L52 _public function_ `virtual bool IsRefreshPending() const override`
- L57 _public function_ `virtual FName GetName() const override`
- L62 _public function_ `virtual const FText GetDisplayName() const override`
- L67 _public function_ `virtual const FText GetToolTip() const override`
- L72 _public function_ `virtual int32 GetObjectSetCount() const override`
- L81 _public function_ `virtual FString GetObjectSetName( int32 InObjectSetIndex ) const override`
- L93 _public function_ `virtual FString GetObjectSetToolTip( int32 InObjectSetIndex ) const override`
- L105 _public function_ `virtual UClass* GetEntryClass() const override`
- L110 _public function_ `virtual TSharedPtr<SWidget> GetCustomFilter( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override`
- L115 _public function_ `virtual TSharedPtr<SWidget> GetCustomWidget( TWeakPtr< class IStatsViewer > InParentStatsViewer ) override`
- L120 _public function_ `virtual void SetSelectedObjectSet( int32 InObjectSetIndex ) override`
- L125 _public function_ `virtual int32 GetSelectedObjectSet() const override`
- L130 _public function_ `virtual void GetCustomColumns(TArray< TSharedRef< class IPropertyTableCustomColumn > >& OutCustomColumns) const override`
- L134 _public function_ `virtual void SetWorld( UWorld& InWorld ) override`
- L139 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L145 _protected member_ `UEnum* ObjectSetEnum;` — The enum we use for our object set
- L148 _protected member_ `int32 ObjectSetIndex;` — Selected object set index
- L151 _protected member_ `bool bRefresh;` — Flag to refresh the page
- L154 _protected member_ `bool bShow;` — Flag to show the page
- L160 _protected member_ `TWeakObjectPtr< UWorld > StatsWorld;` — The world to use for pages that need to query actors/components. Can be null, in which case GWorld will be used.
- L164 _function_ `template< typename Entry > inline UWorld* FStatsPage< Entry >::GetWorld() const`

### `Source/Editor/StatsViewer/Public/StatsViewerModule.h` (Public)


#### enum `EStatsPage::Type`  
`enum Type`  
_L15-23_
- L17 _public enumerator_ `CookerStats`
- L18 _public enumerator_ `LightingBuildInfo`
- L19 _public enumerator_ `PrimitiveStats`
- L20 _public enumerator_ `StaticMeshLightingInfo`
- L21 _public enumerator_ `TextureStats`
- L22 _public enumerator_ `ShaderCookerStats`

#### class `FStatsViewerModule`  
`class FStatsViewerModule : public IModuleInterface`  
_L26-85_
- inherits: `IModuleInterface`
- L30 _public prototype_ `virtual void StartupModule();` — Begin IModuleInterface interface
- L31 _public prototype_ `virtual void ShutdownModule();`
- L39 _public prototype_ `virtual TSharedRef< IStatsViewer > CreateStatsViewer() const;` — Creates a stats viewer widget @return	New stats viewer widget
- L50 _public prototype_ `virtual TSharedRef< IStatsViewer > CreateStatsViewer( UWorld& InWorld, uint32 EnabledDefaultPagesMask, const FName& ViewerName ) const;` — Creates a customized stats viewer widget. @param InWorld					Use this world (instead of default one) for all statistics @param EnabledDefaultPagesMask	The default pages that will be available for this stats viewer @param ViewerName				A unique name for this stats viewer (used as a configuration settings key) @return	New stats viewer widget
- L57 _public prototype_ `virtual TSharedRef< class IPropertyTableCustomColumn > CreateObjectCustomColumn(const struct FObjectHyperlinkColumnInitializationOptions& InOptions) const;` — Creates a stats viewer custom column, supporting weak object references. @param	InOptions	Options used to configure the custom column. @return	New column customization
- L63 _public prototype_ `virtual void RegisterPage( TSharedRef< IStatsPage > InPage );` — Register a page for this module to use @param	InPage	The page to register
- L69 _public prototype_ `virtual void UnregisterPage( TSharedRef< IStatsPage > InPage );` — Unregister a page for this module to use @param	InPage	The page to unregister
- L74 _public prototype_ `virtual TSharedPtr< IStatsPage > GetPage( EStatsPage::Type InType );` — Get a page of the stats module by enum type
- L79 _public prototype_ `virtual TSharedPtr< IStatsPage > GetPage( const FName& InPageName );` — Get a page of the stats module by name
- L84 _public prototype_ `virtual void Clear();` — Clears all pages

#### Free symbols / members of external scopes

- L10 _externvar_ `extern const FName StatsViewerApp;`
- L13 _namespace_ `namespace EStatsPage`

### `Source/Editor/StatsViewer/Public/StatsViewerUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace StatsViewerUtils`
- L16 _prototype_ `AActor* GetActor( const TWeakObjectPtr<UObject>& InObject );` (scope `StatsViewerUtils`) — Helper function to get an actor from an object @param	InObject	The UObject to try to get an associated AACtor from @returns The AActor object if any or NULL if none can be found
- L23 _prototype_ `FText GetAssetName( const TWeakObjectPtr<UObject>& InObject );` (scope `StatsViewerUtils`) — Helper function used to get an asset name from an object to display @param	InObject	The UObject to try to get a name from @returns The name to display or an empty string if none can be found
