# Plugins / PaperTiledImporter

- module root: `Plugins/2D/Paper2D/Source/PaperTiledImporter`
- headers: 2; symbols: 141
- symbol kinds: class=1, delegate=1, enum=7, enumerator=23, function=2, member=66, namespace=1, prototype=33, struct=7
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Json, Paper2D, Paper2DEditor, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools

### `Plugins/2D/Paper2D/Source/PaperTiledImporter/Classes/PaperTiledImporterFactory.h` (Public)


#### enum `ETiledLayerType`  
`enum class ETiledLayerType : uint8`  
_L20-25_
- L22 _public enumerator_ `TileLayer`
- L23 _public enumerator_ `ObjectGroup`
- L24 _public enumerator_ `ImageLayer`

#### enum `ETiledOrientation`  
`enum class ETiledOrientation : uint8`  
_L27-34_
- L29 _public enumerator_ `Unknown`
- L30 _public enumerator_ `Orthogonal`
- L31 _public enumerator_ `Isometric`
- L32 _public enumerator_ `Staggered`
- L33 _public enumerator_ `Hexagonal`

#### enum `ETiledObjectLayerDrawOrder`  
`enum class ETiledObjectLayerDrawOrder : uint8`  
_L36-40_
- L38 _public enumerator_ `TopDown`
- L39 _public enumerator_ `Index`

#### enum `ETiledStaggerAxis`  
`enum class ETiledStaggerAxis : uint8`  
_L42-46_
- L44 _public enumerator_ `X`
- L45 _public enumerator_ `Y`

#### enum `ETiledStaggerIndex`  
`enum class ETiledStaggerIndex : uint8`  
_L48-52_
- L50 _public enumerator_ `Odd`
- L51 _public enumerator_ `Even`

#### enum `ETiledRenderOrder`  
`enum class ETiledRenderOrder : uint8`  
_L54-60_
- L56 _public enumerator_ `RightDown`
- L57 _public enumerator_ `RightUp`
- L58 _public enumerator_ `LeftDown`
- L59 _public enumerator_ `LeftUp`

#### enum `ETiledObjectType`  
`enum class ETiledObjectType : uint8`  
_L62-69_
- L64 _public enumerator_ `Box`
- L65 _public enumerator_ `Ellipse`
- L66 _public enumerator_ `Polygon`
- L67 _public enumerator_ `Polyline`
- L68 _public enumerator_ `PlacedTile`

#### class `UPaperTiledImporterFactory`  
`class UPaperTiledImporterFactory : public UFactory, public FReimportHandler`  
_L73-101_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- desc: Imports a tile map (and associated textures & tile sets) exported from Tiled (http://www.mapeditor.org/)
- L78 _private prototype_ `virtual FText GetToolTip() const override;` — UFactory interface
- L79 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L80 _private prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L84 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;` — FReimportHandler interface
- L85 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L86 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L87 _private prototype_ `virtual int32 GetPriority() const override;`
- L91 _protected prototype_ `TSharedPtr<FJsonObject> ParseJSON(const FString& FileContents, const FString& NameForErrors, bool bSilent = false);`
- L93 _protected prototype_ `void ParseGlobalInfoFromJSON(TSharedPtr<FJsonObject> Tree, struct FTileMapFromTiled& OutParsedInfo, const FString& NameForErrors, bool bSilent = false);`
- L95 _protected prototype_ `static UObject* CreateNewAsset(UClass* AssetClass, const FString& TargetPath, const FString& DesiredName, EObjectFlags Flags);`
- L96 _protected prototype_ `static UTexture2D* ImportTexture(const FString& SourceFilename, const FString& TargetSubPath);`
- L98 _protected prototype_ `void FinalizeTileMap(FTileMapFromTiled& GlobalInfo, UPaperTileMap* TileMap);`
- L100 _protected prototype_ `bool ConvertTileSets(FTileMapFromTiled& GlobalInfo, const FString& CurrentSourcePath, const FString& LongPackagePath, EObjectFlags Flags);`

#### struct `FTiledStringPair`  
`struct FTiledStringPair`  
_L106-123_
- L108 _public member_ `FString Key;`
- L109 _public member_ `FString Value;`
- L112 _public function_ `FTiledStringPair()`
- L116 _public function_ `FTiledStringPair(const FString& InKey, const FString& InValue) : Key(InKey) , Value(InValue)`
- L122 _public prototype_ `static void ParsePropertyBag(TArray<FTiledStringPair>& OutProperties, TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FTiledObject`  
`struct FTiledObject`  
_L130-183_
- L133 _public member_ `ETiledObjectType TiledObjectType;` — The type of the object
- L136 _public member_ `int32 ID;` — ID of the shape (always 0 for per-tile collision shapes)
- L139 _public member_ `FString Name;` — Arbitrary user-specified name
- L142 _public member_ `FString UserType;` — Arbitrary user-specified type
- L145 _public member_ `bool bVisible;` — Is the shape currently visible?
- L151 _public member_ `double X;` — Position of the shape: Ellipse or Box: The center PlacedTile: Bottom left Polygon or Polyline: Position of first vertex (not their center, the Tiled editor always bakes down rotations for them!)
- L152 _public member_ `double Y;`
- L156 _public member_ `double Width;` — Local-space width/height of the shape (Ellipse, Box) Note: Set to (0,0) for Polygon, Polyline, PlacedTile
- L157 _public member_ `double Height;`
- L162 _public member_ `double RotationDegrees;` — Rotation (in degrees) Note: Always 0 for Polyline and Polygon Note: Includes winding (can be < 0 or > 360)
- L165 _public member_ `TArray<FTiledStringPair> Properties;` — Arbitrary user specified Key-Value pairs
- L169 _public member_ `TArray<FVector2D> Points;` — Points for polygon/polyline shapes, relative to (X,Y), which seems to always be the first point in the polygon Note: Only used when TiledObjectType is Polygon or Polyline
- L173 _public member_ `uint32 TileGID;` — The tile GID for placed tiles Note: Only used when TiledObjectType is PlacedTile
- L176 _public prototype_ `FTiledObject();`
- L178 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent = false);`
- L180 _public prototype_ `static bool ParsePointArray(TArray<FVector2D>& OutPoints, const TArray<TSharedPtr<FJsonValue>>& InArray, const FString& NameForErrors, bool bSilent);`
- L182 _public prototype_ `static void AddToSpriteGeometryCollection(const FVector2D& Offset, const TArray<FTiledObject>& InObjects, FSpriteGeometryCollection& InOutShapes);`

#### struct `FTileLayerFromTiled`  
`struct FTileLayerFromTiled`  
_L190-236_
- L193 _public member_ `FString Name;` — Name of the layer
- L196 _public member_ `TArray<uint32> TileIndices;` — Array of tiles (only used when LayerType is TileLayer)
- L199 _public member_ `int32 Width;` — Width and height in tiles
- L200 _public member_ `int32 Height;`
- L203 _public member_ `FColor Color;` — Color of the layer (only set for object layers, to help distinguish them)
- L206 _public member_ `ETiledObjectLayerDrawOrder ObjectDrawOrder;` — Object draw order (only used for object layers)
- L209 _public member_ `float Opacity;` — Saved layer opacity (only RGB are used, A is ignored)
- L212 _public member_ `bool bVisible;` — Is the layer currently visible?
- L215 _public member_ `ETiledLayerType LayerType;` — Type of the layer
- L218 _public member_ `int32 OffsetX;` — Offset
- L219 _public member_ `int32 OffsetY;`
- L222 _public member_ `TArray<FTiledObject> Objects;` — Placed objects (only used when LayerType is ObjectGroup)
- L225 _public member_ `FString OverlayImagePath;` — Overlay image (only used when LayerType is ImageLayer)
- L228 _public member_ `TArray<FTiledStringPair> Properties;` — Arbitrary user specified Key-Value pairs
- L231 _public prototype_ `FTileLayerFromTiled();`
- L233 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent = false);`
- L235 _public prototype_ `bool IsValid() const;`

#### struct `FTiledTerrain`  
`struct FTiledTerrain`  
_L243-255_
- L246 _public member_ `FString TerrainName;` — The name of this terrain type
- L249 _public member_ `uint32 SolidTileLocalIndex;` — The index of the solid tile for this terrain (local  index to the tile set, not a GID!)
- L252 _public prototype_ `FTiledTerrain();`
- L254 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent = false);`

#### struct `FTiledTileInfo`  
`struct FTiledTileInfo`  
_L262-284_
- L266 _public member_ `int32 TerrainIndices[4];` — The terrain indices (into the TerrainTypes array of the containing tile set, INDEX_NONE if invalid) Order is top-left, top-right, bottom-left, bottom-right
- L270 _public member_ `float Probability;` — The probability of placement of this tile (0..1) Note: Tiled doesn't allow editing of this value right now (at least as of 0.11.0), so it's of limited value/trustworthiness
- L275 _public member_ `TArray<FTiledObject> Objects;` — Collision shapes
- L278 _public member_ `TArray<FTiledStringPair> Properties;` — Arbitrary user specified Key-Value pairs
- L281 _public prototype_ `FTiledTileInfo();`
- L283 _public prototype_ `bool ParseTileInfoFromJSON(int32 TileIndex, TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent = false);`

#### struct `FTileSetFromTiled`  
`struct FTileSetFromTiled`  
_L291-337_
- L293 _public member_ `int32 FirstGID;`
- L294 _public member_ `FString Name;`
- L297 _public member_ `FString ImagePath;` — Source image path
- L300 _public member_ `int32 ImageWidth;` — Source image dimensions
- L301 _public member_ `int32 ImageHeight;`
- L304 _public member_ `bool bRemoveTransparentColor;` — Should we chroma-key remove certain pixels, making them transparent?
- L307 _public member_ `FColor ImageTransparentColor;` — The color to remove if bRemoveTransparentColor is true
- L310 _public member_ `TArray<FTiledStringPair> Properties;` — Arbitrary user specified Key-Value pairs
- L313 _public member_ `TArray<FTiledTerrain> TerrainTypes;` — Terrain types
- L316 _public member_ `TMap<int32, FTiledTileInfo> PerTileData;` — Per-tile info (terrain membership, collision objects, properties, etc...)
- L319 _public member_ `int32 TileOffsetX;` — Offset used when drawing tiles from this tile set
- L320 _public member_ `int32 TileOffsetY;`
- L323 _public member_ `int32 Margin;` — The spacing to ignore around the outer edge of the source image (in pixels)
- L326 _public member_ `int32 Spacing;` — The spacing between each tile in the source image (in pixels)
- L328 _public member_ `int32 TileWidth;`
- L329 _public member_ `int32 TileHeight;`
- L332 _public prototype_ `FTileSetFromTiled();`
- L334 _public prototype_ `void ParseTileSetFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent = false);`
- L336 _public prototype_ `bool IsValid() const;`

#### struct `FTileMapFromTiled`  
`struct FTileMapFromTiled`  
_L344-393_
- L347 _public member_ `int32 FileVersion;` — JSON export file version as defined by Tiled (1 is the only known version)
- L350 _public member_ `int32 Width;` — Dimensions of the tile map (in tiles)
- L351 _public member_ `int32 Height;`
- L354 _public member_ `int32 TileWidth;` — Dimensions of a tile (in pixels)
- L355 _public member_ `int32 TileHeight;`
- L358 _public member_ `ETiledOrientation Orientation;` — Projection mode of the tile map
- L361 _public member_ `int32 HexSideLength;` — Side length (only used in Hexagonal projection mode)
- L364 _public member_ `ETiledStaggerAxis StaggerAxis;` — Stagger axis (only used in Staggered and Hexagonal modes)
- L367 _public member_ `ETiledStaggerIndex StaggerIndex;` — Stagger index (only used in Staggered and Hexagonal modes)
- L370 _public member_ `ETiledRenderOrder RenderOrder;` — Render order
- L373 _public member_ `FColor BackgroundColor;` — Background color
- L376 _public member_ `TArray<FTileSetFromTiled> TileSets;` — Set of source tile sets imported from Tiled
- L379 _public member_ `TArray<UPaperTileSet*> CreatedTileSetAssets;` — Set of destination tile set assets created by this import
- L382 _public member_ `TArray<FTileLayerFromTiled> Layers;` — Layers
- L385 _public member_ `TArray<FTiledStringPair> Properties;` — Arbitrary user specified Key-Value pairs
- L388 _public prototype_ `FPaperTileInfo ConvertTileGIDToPaper2D(uint32 GID) const;`
- L389 _public prototype_ `ETileMapProjectionMode::Type GetOrientationType() const;`
- L391 _public prototype_ `FTileMapFromTiled();`
- L392 _public prototype_ `bool IsValid() const;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ETileMapProjectionMode`

### `Plugins/2D/Paper2D/Source/PaperTiledImporter/Private/PaperTiledImporterLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaperTiledImporter, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaperTiledImporter, Verbose, All);`
