# Runtime / Navmesh

- module root: `Source/Runtime/Navmesh`
- headers: 30; symbols: 2084
- symbol kinds: class=25, enum=28, enumerator=128, function=359, macro=35, member=782, prototype=545, struct=88, typedef=26, variable=68
- PrivateDependencyModuleNames: Core

### `Source/Runtime/Navmesh/Public/DebugUtils/DebugDraw.h` (Public)


#### enum `duDebugDrawPrimitives`  
`enum duDebugDrawPrimitives`  
_L71-77_
- L73 _public enumerator_ `DU_DRAW_POINTS`
- L74 _public enumerator_ `DU_DRAW_LINES`
- L75 _public enumerator_ `DU_DRAW_TRIS`
- L76 _public enumerator_ `DU_DRAW_QUADS`

#### struct `duDebugDraw`  
`struct duDebugDraw`  
_L80-150_
- desc: Abstract debug draw interface.
- L82 _public prototype_ `virtual ~duDebugDraw() = 0;`
- L84 _public prototype_ `virtual void depthMask(bool state) = 0;`
- L86 _public prototype_ `virtual void texture(bool state) = 0;`
- L91 _public prototype_ `virtual void begin(duDebugDrawPrimitives prim, float size = 1.0f) = 0;` — Begin drawing primitives. @param prim [in] primitive type to draw, one of rcDebugDrawPrimitives. @param size [in] size of a primitive, applies to point size and line width only.
- L96 _public prototype_ `virtual void vertex(const duReal* pos, unsigned int color) = 0;` — Submit a vertex @param pos [in] position of the verts. @param color [in] color of the verts.
- L100 _public function_ `virtual void vertex(const float* pos, unsigned int color) final` — float version of this function is now deprecated
- L107 _public prototype_ `virtual void vertex(const duReal x, const duReal y, const duReal z, unsigned int color) = 0;` — Submit a vertex @param x,y,z [in] position of the verts. @param color [in] color of the verts.
- L111 _public function_ `virtual void vertex(const float x, const float y, const float z, unsigned int color) final` — float version of this function is now deprecated
- L118 _public prototype_ `virtual void vertex(const duReal* pos, unsigned int color, const duReal* uv) = 0;` — Submit a vertex @param pos [in] position of the verts. @param color [in] color of the verts.
- L122 _public function_ `virtual void vertex(const float* pos, unsigned int color, const float* uv) final` — float version of this function is now deprecated
- L129 _public prototype_ `virtual void vertex(const duReal x, const duReal y, const duReal z, unsigned int color, const duReal u, const duReal v) = 0;` — Submit a vertex @param x,y,z [in] position of the verts. @param color [in] color of the verts.
- L133 _public function_ `virtual void vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v) final` — float version of this function is now deprecated
- L140 _public prototype_ `virtual void text(const duReal x, const duReal y, const duReal z, const char* text) = 0;` — Submit a text label @param x,y,z [in] 3D position of the text. @param text  [in] text to display.
- L144 _public function_ `virtual void text(const float x, const float y, const float z, const char* text) final` — float version of this function is now deprecated
- L149 _public prototype_ `virtual void end() = 0;` — End drawing primitives.

#### struct `duColor`  
`struct duColor`  
_L217-243_
- desc: @UE BEGIN
- L220 _public member_ `static unsigned int red;` — Color palette
- L221 _public member_ `static unsigned int pink;`
- L222 _public member_ `static unsigned int purple;`
- L223 _public member_ `static unsigned int deepPurple;`
- L224 _public member_ `static unsigned int indigo;`
- L225 _public member_ `static unsigned int blue;`
- L226 _public member_ `static unsigned int lightBlue;`
- L227 _public member_ `static unsigned int cyan;`
- L228 _public member_ `static unsigned int teal;`
- L229 _public member_ `static unsigned int green;`
- L230 _public member_ `static unsigned int lightGreen;`
- L231 _public member_ `static unsigned int lime;`
- L232 _public member_ `static unsigned int yellow;`
- L233 _public member_ `static unsigned int amber;`
- L234 _public member_ `static unsigned int orange;`
- L235 _public member_ `static unsigned int orangeRed;`
- L236 _public member_ `static unsigned int brown;`
- L238 _public member_ `static unsigned int white;`
- L239 _public member_ `static unsigned int lightGrey;`
- L240 _public member_ `static unsigned int grey;`
- L241 _public member_ `static unsigned int darkGrey;`
- L242 _public member_ `static unsigned int black;`

#### class `duDisplayList`  
`class duDisplayList : public duDebugDraw`  
_L316-339_
- inherits: `duDebugDraw`
- L318 _private member_ `duReal* m_pos;`
- L319 _private member_ `unsigned int* m_color;`
- L320 _private member_ `int m_size;`
- L321 _private member_ `int m_cap;`
- L323 _private member_ `bool m_depthMask;`
- L324 _private member_ `duDebugDrawPrimitives m_prim;`
- L325 _private member_ `float m_primSize;`
- L327 _private prototype_ `void resize(int cap);`
- L330 _public prototype_ `duDisplayList(int cap = 512);`
- L332 _public prototype_ `virtual void depthMask(bool state);`
- L333 _public prototype_ `virtual void begin(duDebugDrawPrimitives prim, float size = 1.0f);`
- L334 _public prototype_ `virtual void vertex(const duReal x, const duReal y, const duReal z, unsigned int color);`
- L335 _public prototype_ `virtual void vertex(const duReal* pos, unsigned int color);`
- L336 _public prototype_ `virtual void end();`
- L337 _public prototype_ `void clear();`
- L338 _public prototype_ `void draw(struct duDebugDraw* dd);`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DEBUGDRAW_H`
- L29 _variable_ `static const duReal DU_PI = 3.14159265358979323846;` — Some math headers don't have PI defined.
- L31 _function_ `inline float duSin(float x)`
- L36 _function_ `inline double duSin(double x)`
- L41 _function_ `inline float duCos(float x)`
- L46 _function_ `inline double duCos(double x)`
- L51 _function_ `inline float duAbs(float x)`
- L56 _function_ `inline double duAbs(double x)`
- L61 _function_ `inline float duSqrt(float x)`
- L66 _function_ `inline double duSqrt(double x)`
- L153 _function_ `inline unsigned int duRGBA(unsigned int rgba)` — Reorder to handle the 0xRRGGBBAA format
- L162 _function_ `inline unsigned int duRGBA(int r, int g, int b, int a)`
- L167 _function_ `inline unsigned int duRGBAf(float fr, float fg, float fb, float fa)`
- L176 _prototype_ `unsigned int duIntToCol(int i, int a);`
- L177 _prototype_ `void duIntToCol(int i, float* col);`
- L179 _function_ `inline unsigned int duMultCol(const unsigned int col, const unsigned int d)`
- L188 _function_ `inline unsigned int duDarkenCol(unsigned int col)`
- L193 _function_ `inline unsigned int duLerpCol(unsigned int ca, unsigned int cb, unsigned int u)`
- L211 _function_ `inline unsigned int duTransCol(unsigned int c, unsigned int a)`
- L246 _prototype_ `void duCalcBoxColors(unsigned int* colors, unsigned int colTop, unsigned int colSide);`
- L248 _prototype_ `void duDebugDrawCylinderWire(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col, const float lineWidth);`
- L251 _prototype_ `void duDebugDrawBoxWire(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col, const float lineWidth);`
- L254 _prototype_ `void duDebugDrawArc(struct duDebugDraw* dd, const duReal x0, const duReal y0, const duReal z0, const duReal x1, const duReal y1, const duReal z1, const duReal h, const duReal as0, const duReal as1, unsigned int col, const float lineWidth);`
- L258 _prototype_ `void duDebugDrawArrow(struct duDebugDraw* dd, const duReal x0, const duReal y0, const duReal z0, const duReal x1, const duReal y1, const duReal z1, const duReal as0, const duReal as1, unsigned int col, const float lineWidth);`
- L262 _prototype_ `void duDebugDrawCircle(struct duDebugDraw* dd, const duReal x, const duReal y, const duReal z, const duReal r, unsigned int col, const float lineWidth);`
- L265 _prototype_ `void duDebugDrawCross(struct duDebugDraw* dd, const duReal x, const duReal y, const duReal z, const duReal size, unsigned int col, const float lineWidth);`
- L268 _prototype_ `void duDebugDrawBox(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, const unsigned int* fcol);`
- L271 _prototype_ `void duDebugDrawCylinder(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col);`
- L274 _prototype_ `void duDebugDrawGridXZ(struct duDebugDraw* dd, const duReal ox, const duReal oy, const duReal oz, const int w, const int h, const duReal size, const unsigned int col, const float lineWidth);`
- L280 _prototype_ `void duAppendCylinderWire(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col);` — Versions without begin/end, can be used to draw multiple primitives.
- L283 _prototype_ `void duAppendBoxWire(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col);`
- L286 _prototype_ `void duAppendBoxPoints(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col);`
- L289 _prototype_ `void duAppendArc(struct duDebugDraw* dd, const duReal x0, const duReal y0, const duReal z0, const duReal x1, const duReal y1, const duReal z1, const duReal h, const duReal as0, const duReal as1, unsigned int col);`
- L293 _prototype_ `void duAppendArcSegment(struct duDebugDraw* dd, const duReal xA0, const duReal yA0, const duReal zA0, const duReal xA1, const duReal yA1, const duReal zA1, const duReal xB0, const duReal yB0, const duReal zB0, const duReal xB1, const duReal yB1, const duReal zB1, const duReal h, unsigned int col);`
- L299 _prototype_ `void duAppendArrow(struct duDebugDraw* dd, const duReal x0, const duReal y0, const duReal z0, const duReal x1, const duReal y1, const duReal z1, const duReal as0, const duReal as1, unsigned int col);`
- L303 _prototype_ `void duAppendCircle(struct duDebugDraw* dd, const duReal x, const duReal y, const duReal z, const duReal r, unsigned int col);`
- L306 _prototype_ `void duAppendCross(struct duDebugDraw* dd, const duReal x, const duReal y, const duReal z, const duReal size, unsigned int col);`
- L309 _prototype_ `void duAppendBox(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, const unsigned int* fcol);`
- L312 _prototype_ `void duAppendCylinder(struct duDebugDraw* dd, duReal minx, duReal miny, duReal minz, duReal maxx, duReal maxy, duReal maxz, unsigned int col);`

### `Source/Runtime/Navmesh/Public/DebugUtils/DebugDrawLargeWorldCoordinates.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DU_LARGE_WORLD_COORDINATES_DISABLED 0`
- L9 _typedef_ `typedef float duReal;`
- L13 _typedef_ `typedef double duReal;`

### `Source/Runtime/Navmesh/Public/DebugUtils/DetourDebugDraw.h` (Public)


#### enum `DrawNavMeshFlags`  
`enum DrawNavMeshFlags`  
_L34-39_
- L36 _public enumerator_ `DU_DRAWNAVMESH_OFFMESHCONS = 0x01`
- L37 _public enumerator_ `DU_DRAWNAVMESH_CLOSEDLIST = 0x02`
- L38 _public enumerator_ `DU_DRAWNAVMESH_COLOR_TILES = 0x04`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURDEBUGDRAW_H`
- L41 _prototype_ `void duDebugDrawNavMesh(struct duDebugDraw* dd, const dtNavMesh& mesh, unsigned char flags);`
- L42 _prototype_ `void duDebugDrawNavMeshWithClosedList(struct duDebugDraw* dd, const dtNavMesh& mesh, const dtNavMeshQuery& query, unsigned char flags);`
- L43 _prototype_ `void duDebugDrawNavMeshNodes(struct duDebugDraw* dd, const dtNavMeshQuery& query);`
- L44 _prototype_ `void duDebugDrawNavMeshBVTree(struct duDebugDraw* dd, const dtNavMesh& mesh);`
- L45 _prototype_ `void duDebugDrawNavMeshPortals(struct duDebugDraw* dd, const dtNavMesh& mesh);`
- L46 _prototype_ `void duDebugDrawNavMeshPolysWithFlags(struct duDebugDraw* dd, const dtNavMesh& mesh, const unsigned short polyFlags, const unsigned int col);`
- L47 _prototype_ `void duDebugDrawNavMeshPoly(struct duDebugDraw* dd, const dtNavMesh& mesh, dtPolyRef ref, const unsigned int col);`
- L51 _prototype_ `void duDebugDrawNavMeshClusters(struct duDebugDraw* dd, const dtNavMesh& mesh);`
- L52 _prototype_ `void duDebugDrawNavMeshCluster(struct duDebugDraw* dd, const dtNavMesh& mesh, dtClusterRef ref, const unsigned int col);`
- L54 _prototype_ `void duDebugDrawTileCacheClusters(duDebugDraw* dd, const struct dtTileCacheClusterSet& lclusters);`
- L58 _prototype_ `void duDebugDrawTileCacheLayerAreas(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const dtReal cs, const dtReal ch);`
- L59 _prototype_ `void duDebugDrawTileCacheLayerDistance(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const dtTileCacheDistanceField& dfield, const dtReal cs, const dtReal ch);`
- L61 _prototype_ `void duDebugDrawTileCacheLayerRegions(struct duDebugDraw* dd, const dtTileCacheLayer& layer, const dtReal cs, const dtReal ch);`
- L62 _prototype_ `void duDebugDrawTileCacheContours(duDebugDraw* dd, const struct dtTileCacheContourSet& lcset, const int32 layerIdx, const dtReal* orig, const dtReal cs, const dtReal ch);`
- L64 _prototype_ `void duDebugDrawTileCachePolyMesh(duDebugDraw* dd, const struct dtTileCachePolyMesh& lmesh, const dtReal* orig, const dtReal cs, const dtReal ch);`
- L66 _prototype_ `void duDebugDrawTileCacheDetailMesh(duDebugDraw* dd, const struct dtTileCachePolyMeshDetail& dmesh);`

### `Source/Runtime/Navmesh/Public/DebugUtils/DetourNavLinkDebugDraw.h` (Public)


#### enum `duNavLinkBuilderDrawFlags`  
`enum duNavLinkBuilderDrawFlags`  
_L11-22_
- L13 _public enumerator_ `DRAW_WALKABLE_SURFACE = 1 << 0`
- L14 _public enumerator_ `DRAW_BORDERS = 1 << 1`
- L15 _public enumerator_ `DRAW_SELECTED_EDGE = 1 << 2`
- L16 _public enumerator_ `DRAW_TRAJECTORY = 1 << 3`
- L17 _public enumerator_ `DRAW_LAND_SAMPLES = 1 << 4`
- L18 _public enumerator_ `DRAW_COLLISION_SLICES = 1 << 5`
- L19 _public enumerator_ `DRAW_COLLISION_SAMPLES = 1 << 6`
- L20 _public enumerator_ `DRAW_LINKS = 1 << 7`
- L21 _public enumerator_ `DRAW_FILTERED_LINKS = 1 << 8`

#### Free symbols / members of external scopes

- L24 _prototype_ `void duDebugDrawNavLinkBuilder(duDebugDraw* dd, const dtNavLinkBuilder& linkBuilder, unsigned int drawFlags, const struct dtNavLinkBuilder::EdgeSampler* es);`
- L26 _prototype_ `void duDebugDrawTrajectorySamples(duDebugDraw* dd, const dtNavLinkBuilder& linkBuilder, const dtReal* pa, const dtReal* pb, const dtNavLinkBuilder::Trajectory2D* trajectory, const dtReal* trajectoryDir);`
- L29 _prototype_ `void duDrawGroundSegment(duDebugDraw* dd, const dtNavLinkBuilder::GroundSegment& segment);`

### `Source/Runtime/Navmesh/Public/DebugUtils/RecastDebugDraw.h` (Public)


#### Free symbols / members of external scopes

- L23 _macro_ `#define RECAST_DEBUGDRAW_H`
- L31 _prototype_ `void duDebugDrawTriMesh(struct duDebugDraw* dd, const duReal* verts, int nverts, const int* tris, const duReal* normals, int ntris, const unsigned char* flags, const duReal texScale);`
- L32 _prototype_ `void duDebugDrawTriMeshSlope(struct duDebugDraw* dd, const duReal* verts, int nverts, const int* tris, const duReal* normals, int ntris, const duReal walkableSlopeAngle, const duReal texScale);`
- L34 _prototype_ `void duDebugDrawHeightfieldSolid(duDebugDraw* dd, const rcHeightfield& hf);`
- L35 _prototype_ `void duDebugDrawHeightfieldWalkable(duDebugDraw* dd, const rcHeightfield& hf);`
- L36 _prototype_ `void duDebugDrawHeightfieldBounds(duDebugDraw* dd, const rcHeightfield& hf);`
- L38 _prototype_ `void duDebugDrawCompactHeightfieldSolid(struct duDebugDraw* dd, const struct rcCompactHeightfield& chf);`
- L39 _prototype_ `void duDebugDrawCompactHeightfieldRegions(struct duDebugDraw* dd, const struct rcCompactHeightfield& chf);`
- L40 _prototype_ `void duDebugDrawCompactHeightfieldDistance(struct duDebugDraw* dd, const struct rcCompactHeightfield& chf);`
- L42 _prototype_ `void duDrawCylinderArea(duDebugDraw* dd, const duReal* pos, const duReal radius, const duReal height, const unsigned int areaRGBAColor);`
- L43 _prototype_ `void duDrawBoxArea(duDebugDraw* dd, const duReal* pos, const duReal* extent, const unsigned int areaRGBAColor);`
- L44 _prototype_ `void duDrawConvexArea(duDebugDraw* dd, const duReal* verts, const int nverts, const duReal hmin, const duReal hmax, const unsigned int areaRGBAColor);`
- L46 _prototype_ `void duDebugDrawHeightfieldLayer(duDebugDraw* dd, const struct rcHeightfieldLayer& layer, const int idx);`
- L47 _prototype_ `void duDebugDrawHeightfieldLayers(duDebugDraw* dd, const struct rcHeightfieldLayerSet& lset);`
- L48 _prototype_ `void duDebugDrawHeightfieldLayersRegions(duDebugDraw* dd, const struct rcHeightfieldLayerSet& lset);`
- L50 _prototype_ `void duDebugDrawLayerContours(duDebugDraw* dd, const struct rcLayerContourSet& lcset);`
- L51 _prototype_ `void duDebugDrawLayerPolyMesh(duDebugDraw* dd, const struct rcLayerPolyMesh& lmesh);`
- L53 _prototype_ `void duDebugDrawRegionConnections(struct duDebugDraw* dd, const struct rcContourSet& cset, const float alpha = 1.0f);`
- L54 _prototype_ `void duDebugDrawRawContours(struct duDebugDraw* dd, const struct rcContourSet& cset, const float alpha = 1.0f);`
- L55 _prototype_ `void duDebugDrawContours(struct duDebugDraw* dd, const struct rcContourSet& cset, const float alpha = 1.0f);`
- L56 _prototype_ `void duDebugDrawPolyMesh(struct duDebugDraw* dd, const struct rcPolyMesh& mesh);`
- L57 _prototype_ `void duDebugDrawPolyMeshDetail(struct duDebugDraw* dd, const struct rcPolyMeshDetail& dmesh);`

### `Source/Runtime/Navmesh/Public/DebugUtils/RecastDump.h` (Public)


#### struct `duFileIO`  
`struct duFileIO`  
_L30-37_
- L32 _public prototype_ `virtual ~duFileIO() = 0;`
- L33 _public prototype_ `virtual bool isWriting() const = 0;`
- L34 _public prototype_ `virtual bool isReading() const = 0;`
- L35 _public prototype_ `virtual bool write(const void* ptr, const size_t size) = 0;`
- L36 _public prototype_ `virtual bool read(void* ptr, const size_t size) = 0;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define RECAST_DUMP_H`
- L39 _prototype_ `bool duDumpPolyMeshToObj(struct rcPolyMesh& pmesh, duFileIO* io);`
- L40 _prototype_ `bool duDumpPolyMeshDetailToObj(struct rcPolyMeshDetail& dmesh, duFileIO* io);`
- L42 _prototype_ `bool duDumpContourSet(struct rcContourSet& cset, duFileIO* io);`
- L43 _prototype_ `bool duReadContourSet(struct rcContourSet& cset, duFileIO* io);`
- L45 _prototype_ `bool duDumpCompactHeightfield(struct rcCompactHeightfield& chf, duFileIO* io);`
- L46 _prototype_ `bool duReadCompactHeightfield(struct rcCompactHeightfield& chf, duFileIO* io);`
- L48 _prototype_ `void duLogBuildTimes(rcContext& ctx, const int totalTileUsec);`

### `Source/Runtime/Navmesh/Public/Detour/DetourAlloc.h` (Public)


#### enum `dtAllocHint`  
`enum dtAllocHint`  
_L30-48_
- desc: @UE BEGIN Adding support for memory tracking. Provides hint values on how the memory is expected to be used. Typically used by external memory allocation and tracking systems.
- L32 _public enumerator_ `DT_ALLOC_TEMP` — Memory used temporarily within a function.
- L33 _public enumerator_ `DT_ALLOC_PERM_AVOIDANCE`
- L34 _public enumerator_ `DT_ALLOC_PERM_CROWD`
- L35 _public enumerator_ `DT_ALLOC_PERM_LOOKUP`
- L36 _public enumerator_ `DT_ALLOC_PERM_NAVMESH`
- L37 _public enumerator_ `DT_ALLOC_PERM_NAVQUERY`
- L38 _public enumerator_ `DT_ALLOC_PERM_NODE_POOL`
- L39 _public enumerator_ `DT_ALLOC_PERM_PATH_CORRIDOR`
- L40 _public enumerator_ `DT_ALLOC_PERM_PATH_QUEUE`
- L41 _public enumerator_ `DT_ALLOC_PERM_PROXIMITY_GRID`
- L42 _public enumerator_ `DT_ALLOC_PERM_TILE_CACHE_LAYER`
- L43 _public enumerator_ `DT_ALLOC_PERM_TILE_DATA`
- L44 _public enumerator_ `DT_ALLOC_PERM_TILE_DYNLINK`
- L45 _public enumerator_ `DT_ALLOC_PERM_TILE_DYNLINK_CLUSTER`
- L46 _public enumerator_ `DT_ALLOC_PERM_TILES`
- L47 _public enumerator_ `DT_ALLOC_PERM_TILE_LINK_BUILDER`

#### class `dtScopedDelete`  
`template<class T> class dtScopedDelete`  
_L88-107_
- desc: A simple helper class used to delete an array when it goes out of scope. @note This class is rarely if ever used by the end user.
- L90 _private member_ `T* ptr;`
- L91 _private prototype_ `inline T* operator=(T* p);`
- L95 _public function_ `inline dtScopedDelete() : ptr(0)` — Constructs an instance with a null pointer.
- L96 _public function_ `inline dtScopedDelete(int n)`
- L100 _public function_ `inline dtScopedDelete(T* p) : ptr(p)` — Constructs an instance with the specified pointer. @param[in]		p	An pointer to an allocated array.
- L101 _public function_ `inline ~dtScopedDelete()`
- L105 _public function_ `inline operator T*()` — The root array pointer. @return The root array pointer.
- L106 _public function_ `inline T* get()`

#### class `dtIntArray`  
`class dtIntArray`  
_L110-163_
- desc: A simple dynamic array of integers.
- L112 _private member_ `int* m_data;`
- L113 _private member_ `int m_size, m_cap;`
- L113 _private member_ `int m_size, m_cap;`
- L114 _private prototype_ `inline dtIntArray(const dtIntArray&);`
- L115 _private prototype_ `inline dtIntArray& operator=(const dtIntArray&);`
- L119 _public function_ `inline dtIntArray() : m_data(0), m_size(0), m_cap(0)` — Constructs an instance with an initial array size of zero.
- L123 _public function_ `inline dtIntArray(int n) : m_data(0), m_size(0), m_cap(0)` — Constructs an instance initialized to the specified size. @param[in]		n	The initial size of the integer array.
- L124 _public function_ `inline ~dtIntArray()`
- L128 _public prototype_ `void resize(int n);` — Specifies the new size of the integer array. @param[in]		n	The new size of the integer array.
- L132 _public function_ `inline void push(int item)` — Push the specified integer onto the end of the array and increases the size by one. @param[in]		item	The new value.
- L136 _public function_ `inline int pop()` — Returns the value at the end of the array and reduces the size by one. @return The value at the end of the array.
- L141 _public function_ `inline const int& operator[](int i) const` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L146 _public function_ `inline int& operator[](int i)` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L149 _public function_ `inline int size() const` — The current size of the integer array.
- L151 _public function_ `inline int* getData() const`
- L153 _public prototype_ `void copy(const dtIntArray& src);`
- L155 _public function_ `bool contains(int v) const`

#### class `dtChunkArray`  
`template<class T, dtAllocHint TAllocHint = DT_ALLOC_TEMP>`  
_L167-208_
- desc: A simple dynamic array of integers.
- L169 _private member_ `T* m_data;`
- L170 _private member_ `int m_size, m_cap;`
- L170 _private member_ `int m_size, m_cap;`
- L172 _private prototype_ `inline dtChunkArray(const dtChunkArray&);`
- L173 _private prototype_ `inline dtChunkArray& operator=(const dtChunkArray&);`
- L177 _public function_ `inline dtChunkArray() : m_data(0), m_size(0), m_cap(0)` — Constructs an instance with an initial array size of zero.
- L181 _public function_ `inline dtChunkArray(int n) : m_data(0), m_size(0), m_cap(0)` — Constructs an instance initialized to the specified size. @param[in]		n	The initial size of the integer array.
- L182 _public function_ `inline ~dtChunkArray()`
- L186 _public prototype_ `void resize(int n);` — Specifies the new size of the integer array. @param[in]		n	The new size of the integer array.
- L190 _public function_ `inline void push(T item)` — Push the specified integer onto the end of the array and increases the size by one. @param[in]		item	The new value.
- L194 _public function_ `inline T pop()` — Returns the value at the end of the array and reduces the size by one. @return The value at the end of the array.
- L199 _public function_ `inline const T& operator[](int i) const` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L204 _public function_ `inline T& operator[](int i)` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L207 _public function_ `inline int size() const` — The current size of the integer array.
- L211 _function_ `template<class T, dtAllocHint TAllocHint> void dtChunkArray<T, TAllocHint>::resize(int n)`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURALLOCATOR_H`
- L56 _typedef_ `typedef void* (dtAllocFunc)(int size, dtAllocHint hint);` — A memory allocation function. @param[in]		size			The size, in bytes of memory, to allocate. @param[in]		rcAllocHint	A hint to the allocator on how long the memory is expected to be in use. @return A pointer to the beginning of the allocated memory block, or null if the allocation failed. @see dtAllocSetCustom
- L62 _typedef_ `typedef void (dtFreeFunc)(void* ptr, dtAllocHint hint);` — A memory deallocation function. @param[in]		ptr		A pointer to a memory block previously allocated using #dtAllocFunc. @see dtAllocSetCustom @UE BEGIN Adding support for memory tracking.
- L68 _prototype_ `void dtAllocSetCustom(dtAllocFunc *allocFunc, dtFreeFunc *freeFunc);` — Sets the base custom allocation functions to be used by Detour. @param[in]		allocFunc	The memory allocation function to be used by #dtAlloc @param[in]		freeFunc	The memory de-allocation function to be used by #dtFree
- L75 _prototype_ `void* dtAlloc(int size, dtAllocHint hint);` — Allocates a memory block. @param[in]		size	The size, in bytes of memory, to allocate. @param[in]		hint	A hint to the allocator on how long the memory is expected to be in use. @return A pointer to the beginning of the allocated memory block, or null if the allocation failed. @see dtFree
- L81 _prototype_ `void dtFree(void* ptr, dtAllocHint hint);` — Deallocates a memory block. @param[in]		ptr		A pointer to a memory block previously allocated using #dtAlloc. @see dtAlloc @UE BEGIN Adding support for memory tracking.
- L84 _prototype_ `void dtMemCpy(void* dst, void* src, int size);`

### `Source/Runtime/Navmesh/Public/Detour/DetourAssert.h` (Public)


#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURASSERT_H`
- L32 _macro_ `# define dtAssert(x) do { (void)sizeof((x)); } while((void)(__LINE__==-1),false)` — From http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/
- L35 _macro_ `# define dtAssert(x) { assert(x); CA_ASSUME(x); } (void)0`

### `Source/Runtime/Navmesh/Public/Detour/DetourCommon.h` (Public)


#### enum `dtRotation`  
`enum dtRotation`  
_L617-623_
- desc: @UE BEGIN
- L619 _public enumerator_ `DT_ROTATE_0`
- L620 _public enumerator_ `DT_ROTATE_90`
- L621 _public enumerator_ `DT_ROTATE_180`
- L622 _public enumerator_ `DT_ROTATE_270`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURCOMMON_H`
- L30 _macro_ `#define DT_STATS STATS` — DT_STATS is set from the UE Stats settings
- L48 _function_ `template<class T> inline void dtSwap(T& a, T& b)` — Swaps the values of the two parameters. @param[in,out]	a	Value A @param[in,out]	b	Value B
- L54 _function_ `template<class T> inline T dtMin(T a, T b)` — Returns the minimum of two values. @param[in]		a	Value A @param[in]		b	Value B @return The minimum of the two values.
- L56 _function_ `inline dtReal dtMin(dtReal a, dtReal b)` — @UE BEGIN Adding support for LWCoords. Overloading allows this to be called where one of the parameters is a double and the other a float.
- L63 _function_ `template<class T> inline T dtMax(T a, T b)` — Returns the maximum of two values. @param[in]		a	Value A @param[in]		b	Value B @return The maximum of the two values.
- L65 _function_ `inline dtReal dtMax(dtReal a, dtReal b)` — @UE BEGIN Adding support for LWCoords. Overloading allows this to be called where one of the parameters is a double and the other a float.
- L71 _function_ `template<class T> inline T dtAbs(T a)` — Returns the absolute value. @param[in]		a	The value. @return The absolute value of the specified value.
- L76 _function_ `template<class T> inline T dtSqr(T a)` — Returns the square of the value. @param[in]		a	The value. @return The square of the value.
- L83 _function_ `template<class T> inline T dtClamp(T v, T mn, T mx)` — Clamps the value to the specified range. @param[in]		v	The value to clamp. @param[in]		mn	The minimum permitted return value. @param[in]		mx	The maximum permitted return value. @return The value, clamped to the specified range.
- L85 _function_ `inline dtReal dtClamp(dtReal v, dtReal mn, dtReal mx)` — @UE BEGIN Adding support for LWCoords. Overloading allows this to be called where one of the parameters is a double and the other a float.
- L88 _function_ `inline float dtFloor(float x)`
- L93 _function_ `inline double dtFloor(double x)`
- L98 _function_ `inline float dtCeil(float x)`
- L103 _function_ `inline double dtCeil(double x)`
- L108 _function_ `inline float dtSin(float x)`
- L113 _function_ `inline double dtSin(double x)`
- L118 _function_ `inline float dtCos(float x)`
- L123 _function_ `inline double dtCos(double x)`
- L128 _function_ `inline float dtAtan2(float x, float y)`
- L133 _function_ `inline double dtAtan2(double x, double y)`
- L138 _function_ `inline float dtSqrt(float x)`
- L143 _function_ `inline double dtSqrt(double x)`
- L148 _function_ `inline float dtfMod(float x, float y)`
- L153 _function_ `inline double dtfMod(double x, double y)`
- L158 _function_ `inline float dtLerp(float a, float b, float t)`
- L171 _function_ `inline void dtVcross(dtReal* dest, const dtReal* v1, const dtReal* v2)` — Derives the cross product of two vectors. (@p v1 x @p v2) @param[out]	dest	The cross product. [(x, y, z)] @param[in]		v1		A Vector [(x, y, z)] @param[in]		v2		A vector [(x, y, z)]
- L182 _function_ `inline dtReal dtVdot(const dtReal* v1, const dtReal* v2)` — Derives the dot product of two vectors. (@p v1 . @p v2) @param[in]		v1	A Vector [(x, y, z)] @param[in]		v2	A vector [(x, y, z)] @return The dot product.
- L192 _function_ `inline void dtVmad(dtReal* dest, const dtReal* v1, const dtReal* v2, const dtReal s)` — Performs a scaled vector addition. (@p v1 + (@p v2 * @p s)) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to scale and add to @p v1. [(x, y, z)] @param[in]		s		The amount to scale @p v2 by before adding to @p v1.
- L204 _function_ `inline void dtVlerp(dtReal* dest, const dtReal* v1, const dtReal* v2, const dtReal t)` — Performs a linear interpolation between two vectors. (@p v1 toward @p v2) @param[out]	dest	The result vector. [(x, y, x)] @param[in]		v1		The starting vector. @param[in]		v2		The destination vector. @param[in]		t		The interpolation factor. [Limits: 0 <= value <= 1.0]
- L215 _function_ `inline void dtVadd(dtReal* dest, const dtReal* v1, const dtReal* v2)` — Performs a vector addition. (@p v1 + @p v2) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to add to @p v1. [(x, y, z)]
- L226 _function_ `inline void dtVsub(dtReal* dest, const dtReal* v1, const dtReal* v2)` — Performs a vector subtraction. (@p v1 - @p v2) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to subtract from @p v1. [(x, y, z)]
- L237 _function_ `inline void dtVscale(dtReal* dest, const dtReal* v, const dtReal t)` — Scales the vector by the specified value. (@p v * @p t) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v		The vector to scale. [(x, y, z)] @param[in]		t		The scaling factor.
- L247 _function_ `inline void dtVmin(dtReal* mn, const dtReal* v)` — Selects the minimum value of each element from the specified vectors. @param[in,out]	mn	A vector.  (Will be updated with the result.) [(x, y, z)] @param[in]	v	A vector. [(x, y, z)]
- L257 _function_ `inline void dtVmax(dtReal* mx, const dtReal* v)` — Selects the maximum value of each element from the specified vectors. @param[in,out]	mx	A vector.  (Will be updated with the result.) [(x, y, z)] @param[in]		v	A vector. [(x, y, z)]
- L269 _function_ `inline void dtVset(dtReal* dest, const dtReal x, const dtReal y, const dtReal z)` — Sets the vector elements to the specified values. @param[out]	dest	The result vector. [(x, y, z)] @param[in]		x		The x-value of the vector. @param[in]		y		The y-value of the vector. @param[in]		z		The z-value of the vector.
- L277 _function_ `inline void dtVcopy(dtReal* dest, const dtReal* a)` — Performs a vector copy. @param[out]	dest	The result. [(x, y, z)] @param[in]		a		The vector to copy. [(x, y, z)]
- L287 _function_ `inline dtReal dtVlen(const dtReal* v)` — Derives the scalar length of the vector. @param[in]		v The vector. [(x, y, z)] @return The scalar length of the vector.
- L295 _function_ `inline dtReal dtVlenSqr(const dtReal* v)` — Derives the square of the scalar length of the vector. (len * len) @param[in]		v The vector. [(x, y, z)] @return The square of the scalar length of the vector.
- L304 _function_ `inline dtReal dtVdist(const dtReal* v1, const dtReal* v2)` — Returns the distance between two points. @param[in]		v1	A point. [(x, y, z)] @param[in]		v2	A point. [(x, y, z)] @return The distance between the two points.
- L316 _function_ `inline dtReal dtVdistSqr(const dtReal* v1, const dtReal* v2)` — Returns the square of the distance between two points. @param[in]		v1	A point. [(x, y, z)] @param[in]		v2	A point. [(x, y, z)] @return The square of the distance between the two points.
- L330 _function_ `inline dtReal dtVdist2D(const dtReal* v1, const dtReal* v2)` — The vectors are projected onto the xz-plane, so the y-values are ignored.
- L341 _function_ `inline dtReal dtVdist2DSqr(const dtReal* v1, const dtReal* v2)` — Derives the square of the distance between the specified points on the xz-plane. @param[in]		v1	A point. [(x, y, z)] @param[in]		v2	A point. [(x, y, z)] @return The square of the distance between the point on the xz-plane.
- L350 _function_ `inline void dtVnormalize(dtReal* v)` — Normalizes the vector. @param[in,out]	v	The vector to normalize. [(x, y, z)]
- L361 _function_ `inline bool dtVisEqual(const unsigned short* a, const unsigned short* b)` — Returns true if the vectors are the same. @param[in]		a	A vector. [(x, y, z)] @param[in]		b	A vector. [(x, y, z)]
- L373 _function_ `inline bool dtVequal(const dtReal* p0, const dtReal* p1)` — Basically, this function will return true if the specified points are close enough to eachother to be considered colocated.
- L386 _function_ `inline dtReal dtVdot2D(const dtReal* u, const dtReal* v)` — The vectors are projected onto the xz-plane, so the y-values are ignored.
- L397 _function_ `inline dtReal dtVperp2D(const dtReal* u, const dtReal* v)` — The vectors are projected onto the xz-plane, so the y-values are ignored.
- L411 _function_ `inline dtReal dtTriArea2D(const dtReal* a, const dtReal* b, const dtReal* c)` — Derives the signed xz-plane area of the triangle ABC, or the relationship of line AB to point C. @param[in]		a		Vertex A. [(x, y, z)] @param[in]		b		Vertex B. [(x, y, z)] @param[in]		c		Vertex C. [(x, y, z)] @return The signed xz-plane area of the triangle.
- L427 _function_ `inline bool dtOverlapQuantBounds(const unsigned short amin[3], const unsigned short amax[3], const unsigned short bmin[3], const unsigned short bmax[3])` — Determines if two axis-aligned bounding boxes overlap. @param[in]		amin	Minimum bounds of box A. [(x, y, z)] @param[in]		amax	Maximum bounds of box A. [(x, y, z)] @param[in]		bmin	Minimum bounds of box B. [(x, y, z)] @param[in]		bmax	Maximum bounds of box B. [(x, y, z)] @return True if the two AABB's overlap. @see dtOverlapBounds
- L444 _function_ `inline bool dtOverlapBounds(const dtReal* amin, const dtReal* amax, const dtReal* bmin, const dtReal* bmax)` — Determines if two axis-aligned bounding boxes overlap. @param[in]		amin	Minimum bounds of box A. [(x, y, z)] @param[in]		amax	Maximum bounds of box A. [(x, y, z)] @param[in]		bmin	Minimum bounds of box B. [(x, y, z)] @param[in]		bmax	Maximum bounds of box B. [(x, y, z)] @return True if the two AABB's overlap. @see dtOverlapQuantBounds
- L460 _prototype_ `void dtClosestPtPointTriangle(dtReal* closest, const dtReal* p, const dtReal* a, const dtReal* b, const dtReal* c);` — Derives the closest point on a triangle from the specified reference point. @param[out]	closest	The closest point on the triangle. @param[in]		p		The reference point from which to test. [(x, y, z)] @param[in]		a		Vertex A of triangle ABC. [(x, y, z)] @param[in]		b		Vertex B of triangle ABC. [(x, y, z)] @param[in]		c		Vertex C of triangle ABC. [(x, y, z)]
- L469 _prototype_ `bool dtClosestHeightPointTriangle(const dtReal* p, const dtReal* a, const dtReal* b, const dtReal* c, dtReal& h);` — Derives the y-axis height of the closest point on the triangle from the specified reference point. @param[in]		p		The reference point from which to test. [(x, y, z)] @param[in]		a		Vertex A of triangle ABC. [(x, y, z)] @param[in]		b		Vertex B of triangle ABC. [(x, y, z)] @param[in]		c		Vertex C of triangle ABC. [(x, y, z)] @param[out]	h		The resulting height.
- L471 _prototype_ `bool dtIntersectSegmentPoly2D(const dtReal* p0, const dtReal* p1, const dtReal* verts, int nverts, dtReal& tmin, dtReal& tmax, int& segMin, int& segMax);`
- L476 _prototype_ `bool dtIntersectSegSeg2D(const dtReal* ap, const dtReal* aq, const dtReal* bp, const dtReal* bq, dtReal& s, dtReal& t);`
- L485 _prototype_ `bool dtPointInPolygon(const dtReal* pt, const dtReal* verts, const int nverts);` — Determines if the specified point is inside the convex polygon on the xz-plane. @param[in]		pt		The point to check. [(x, y, z)] @param[in]		verts	The polygon vertices. [(x, y, z) * @p nverts] @param[in]		nverts	The number of vertices. [Limit: >= 3] @return True if the point is inside the polygon.
- L487 _prototype_ `bool dtDistancePtPolyEdgesSqr(const dtReal* pt, const dtReal* verts, const int nverts, dtReal* ed, dtReal* et);`
- L490 _prototype_ `dtReal dtDistancePtSegSqr2D(const dtReal* pt, const dtReal* p, const dtReal* q, dtReal& t);`
- L491 _prototype_ `dtReal dtDistancePtSegSqr(const dtReal* pt, const dtReal* p, const dtReal* q);`
- L498 _prototype_ `void dtCalcPolyCenter(dtReal* tc, const unsigned short* idx, int nidx, const dtReal* verts);` — Derives the centroid of a convex polygon. @param[out]	tc		The centroid of the polgyon. [(x, y, z)] @param[in]		idx		The polygon indices. [(vertIndex) * @p nidx] @param[in]		nidx	The number of indices in the polygon. [Limit: >= 3] @param[in]		verts	The polygon vertices. [(x, y, z) * vertCount]
- L506 _prototype_ `bool dtOverlapPolyPoly2D(const dtReal* polya, const int npolya, const dtReal* polyb, const int npolyb);` — Determines if the two convex polygons overlap on the xz-plane. @param[in]		polya		Polygon A vertices.	[(x, y, z) * @p npolya] @param[in]		npolya		The number of vertices in polygon A. @param[in]		polyb		Polygon B vertices.	[(x, y, z) * @p npolyb] @param[in]		npolyb		The number of vertices in polygon B. @return True if the two polygons overlap.
- L513 _function_ `inline unsigned int dtNextPow2(unsigned int v)`
- L525 _function_ `inline unsigned int dtIlog2(unsigned int v)`
- L538 _function_ `inline int dtAlign(int x)` — @UE BEGIN Align to 8 byte boundaries when using double precision
- L548 _function_ `inline int dtOppositeTile(int side)`
- L550 _function_ `inline void dtSwapByte(unsigned char* a, unsigned char* b)`
- L557 _function_ `inline void dtSwapEndian(unsigned short* v)`
- L563 _function_ `inline void dtSwapEndian(short* v)`
- L569 _function_ `inline void dtSwapEndian(unsigned int* v)`
- L575 _function_ `inline void dtSwapEndian(int* v)`
- L581 _function_ `inline void dtSwapEndian(unsigned long long int* v)`
- L590 _function_ `inline void dtSwapEndian(long long int* v)`
- L599 _function_ `inline void dtSwapEndian(float* v)`
- L606 _function_ `inline void dtSwapEndian(double* v)` — @UE BEGIN Adding support for LWCoords.
- L613 _prototype_ `void dtRandomPointInConvexPoly(const dtReal* pts, const int npts, dtReal* areas, const dtReal s, const dtReal t, dtReal* out);`
- L628 _prototype_ `dtRotation dtSelectRotation(dtReal rotationDeg);` — Select a 90 degree increment value from an input angle in degree. @param[in]		rotationDeg The desired rotation in degree. @return The rotation enum value.
- L634 _prototype_ `void dtVRot90(dtReal* dest, const dtReal* v, const dtRotation rot);` — Rotate by 90 degree increments. @param[out]	dest	The result position. [(x, y, z)] @param[in]		v		The vector to rotate. [(x, y, z)] @param[in]		rot		The rotation enum value.
- L640 _prototype_ `void dtVRot90(unsigned short* dest, const unsigned short* v, const dtRotation rot);` — Rotate by 90 degree increments. @param[out]	dest	The result position. [(x, y, z)] @param[in]		v		The vector to rotate. [(x, y, z)] @param[in]		rot		The rotation enum value.
- L647 _prototype_ `void dtRotate90(dtReal* dest, const dtReal* v, const dtReal* center, const dtRotation rot);` — Rotate vector around center position by increments of 90 degrees. @param[out]	dest	The result position. [(x, y, z)] @param[in]		v		The vector to rotate. [(x, y, z)] @param[in]		center	The center point. [(x, y, z)] @param[in]		rot		The rotation enum value.
- L654 _prototype_ `void dtRotate90(unsigned short* dest, const unsigned short* v, const unsigned short* center, const dtRotation rot);` — Rotate vector around center position by increments of 90 degrees. @param[out]	dest	The result position. [(x, y, z)] @param[in]		v		The vector to rotate. [(x, y, z)] @param[in]		center	The center point. [(x, y, z)] @param[in]		rot		The rotation enum value.

### `Source/Runtime/Navmesh/Public/Detour/DetourLargeWorldCoordinates.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define DT_LARGE_WORLD_COORDINATES_DISABLED 0`
- L11 _typedef_ `typedef float dtReal;`
- L15 _typedef_ `typedef double dtReal;`
- L19 _variable_ `inline constexpr dtReal DT_REAL_MAX = std::numeric_limits<dtReal>::max();`

### `Source/Runtime/Navmesh/Public/Detour/DetourNavLinkBuilder.h` (Public)


#### struct `dtLinkBuilderConfig`  
`struct dtLinkBuilderConfig`  
_L11-20_
- L13 _public member_ `TArray<dtNavLinkBuilderJumpConfig> jumpConfigs;`
- L15 _public member_ `dtReal agentRadius = 0;`
- L16 _public member_ `dtReal agentHeight = 0;`
- L17 _public member_ `dtReal agentClimb = 0;`
- L18 _public member_ `dtReal cellSize = 0;`
- L19 _public member_ `dtReal cellHeight = 0;`

#### struct `dtLinkBuilderData`  
`struct dtLinkBuilderData`  
_L25-28_
- L27 _public member_ `bool generatingLinks = false;`

#### class `dtNavLinkBuilder`  
`class dtNavLinkBuilder`  
_L33-187_
- L35 _private member_ `dtLinkBuilderConfig m_linkBuilderConfig;`
- L37 _private member_ `dtReal m_cs = 0;`
- L38 _private member_ `dtReal m_csSquared = 0;`
- L39 _private member_ `dtReal m_ch = 0;`
- L40 _private member_ `dtReal m_invCs = 0;`
- L41 _private member_ `const rcHeightfield* m_solid = nullptr;`
- L42 _private member_ `const rcCompactHeightfield* m_chf = nullptr;`
- L48 _private member_ `TArray<Edge, TInlineAllocator<32>> m_edges;`
- L51 _public member_ `static constexpr int MAX_SPINE = 8;`
- L52 _public function_ `int getEdgeCount() const`
- L109 _public member_ `static constexpr uint8 INVALID_CONFIG_INDEX = 0xFF;`
- L142 _public member_ `TArray<JumpLink, TInlineAllocator<16>> m_links;`
- L145 _private member_ `int m_debugSelectedEdge = -1;`
- L156 _public prototype_ `bool findEdges(rcContext& ctx, const rcConfig& cfg, const dtLinkBuilderConfig& builderConfig, const struct dtTileCacheContourSet& lcset, const dtReal* orig, const rcHeightfield* solidHF, const rcCompactHeightfield* compactHF);` — Loops through contours to store edge points in world coordinates.
- L161 _public prototype_ `void buildForAllEdges(rcContext& ctx, const dtLinkBuilderConfig& acfg, const dtNavLinkBuilderJumpConfig& jumpConfig);` — For all edges, sample edges (sampleEdge) and add links to m_links
- L163 _public prototype_ `void debugBuildEdge(const dtLinkBuilderConfig& acfg, int edgeIndex, EdgeSampler& sampler, const dtNavLinkBuilderJumpConfig& jumpConfig);`
- L166 _private prototype_ `void initTrajectorySamples(const float groundRange, Trajectory2D* trajectory) const;`
- L167 _private prototype_ `bool isTrajectoryClear(const dtReal* pa, const dtReal* pb, const Trajectory2D* trajectory, const dtReal* trajectoryDir) const;`
- L169 _private prototype_ `void initJumpRig(EdgeSampler* es, const dtReal* sp, const dtReal* sq, const dtNavLinkBuilderJumpConfig& config) const;`
- L172 _private prototype_ `bool getCompactHeightfieldHeight(const dtReal* pt, const dtReal hrange, dtReal* height) const;`
- L173 _private prototype_ `bool checkHeightfieldCollision(const dtReal x, const dtReal ymin, const dtReal ymax, const dtReal z) const;`
- L175 _private prototype_ `void sampleGroundSegment(GroundSegment* seg, const int nsamples, const float groundRange) const;`
- L179 _private prototype_ `void updateTrajectorySamples(EdgeSampler* es) const;` — Update the min height of the trajectory samples from the height of the ground at the start and the end of the trajectories. This method must be called after the segments have been sampled for ground.
- L181 _private prototype_ `void sampleAction(EdgeSampler* es) const;`
- L183 _private prototype_ `void filterOverlappingLinks(const float edgeDistanceThreshold);`
- L185 _private prototype_ `bool sampleEdge(const dtNavLinkBuilderJumpConfig& jumpConfig, const dtReal* sp, const dtReal* sq, dtNavLinkBuilder::EdgeSampler* sampler) const;`
- L186 _private prototype_ `void addEdgeLinks(const dtLinkBuilderConfig& builderConfig, const EdgeSampler* es, const int edgeIndex);`

#### struct `dtNavLinkBuilder::Edge`  
`struct Edge`  
_L44-47_
- L46 _public member_ `dtReal sp[3], sq[3];`
- L46 _public member_ `dtReal sp[3], sq[3];`

#### struct `dtNavLinkBuilder::TrajectorySample`  
`struct TrajectorySample`  
_L54-62_
- L57 _public member_ `float ymin = 0.f;` — Min and max heights relative to the height on the segment between the start and the end point (at the sampling locations).
- L58 _public member_ `float ymax = 0.f;`
- L60 _public member_ `bool floorStart = false;`
- L61 _public member_ `bool floorEnd = false;`

#### struct `dtNavLinkBuilder::Trajectory2D`  
`struct Trajectory2D`  
_L64-72_
- L66 _public member_ `float spine[2*MAX_SPINE];` — [x,y] relative points representing the desired trajectory (one spine with MAX_SPINE points)
- L67 _public member_ `float radiusOverflow = 0.f;` — extra distance at the start and end of the spine to lookup for samples
- L69 _public member_ `TArray<TrajectorySample, TInlineAllocator<8>> samples;` — samples along trajectory slices to check for collision
- L71 _public member_ `unsigned char nspine = 0;` — @todo: remove (use direclty MAX_SPINE) or make relative to trajectory type and config

#### enum `dtNavLinkBuilder::GroundSampleFlag`  
`enum GroundSampleFlag : unsigned char`  
_L75-80_
- L77 _public enumerator_ `UNSET = 0`
- L78 _public enumerator_ `HAS_GROUND = 1`
- L79 _public enumerator_ `UNRESTRICTED = 4`

#### struct `dtNavLinkBuilder::GroundSample`  
`struct GroundSample`  
_L82-86_
- L84 _public member_ `dtReal height;`
- L85 _public member_ `GroundSampleFlag flags;`

#### struct `dtNavLinkBuilder::PotentialSeg`  
`struct PotentialSeg`  
_L88-95_
- L90 _public member_ `unsigned char mark;`
- L91 _public member_ `int idx;`
- L92 _public member_ `float umin, umax;`
- L92 _public member_ `float umin, umax;`
- L93 _public member_ `float dmin, dmax;`
- L93 _public member_ `float dmin, dmax;`
- L94 _public member_ `float sp[3], sq[3];`
- L94 _public member_ `float sp[3], sq[3];`

#### struct `dtNavLinkBuilder::GroundSegment`  
`struct GroundSegment`  
_L97-106_
- L99 _public function_ `GroundSegment() : ngsamples(0)`
- L100 _public prototype_ `~GroundSegment();`
- L102 _public member_ `dtReal p[3], q[3];`
- L102 _public member_ `dtReal p[3], q[3];`
- L103 _public member_ `TArray<GroundSample, TInlineAllocator<16>> gsamples;`
- L104 _public member_ `unsigned short ngsamples;`
- L105 _public member_ `unsigned short npass;`

#### struct `dtNavLinkBuilder::EdgeSampler`  
`struct EdgeSampler`  
_L111-123_
- L113 _public member_ `Trajectory2D trajectory;`
- L115 _public member_ `GroundSegment start;`
- L116 _public member_ `GroundSegment end;`
- L118 _public member_ `dtReal rigp[3], rigq[3];` — edge
- L118 _public member_ `dtReal rigp[3], rigq[3];` — edge
- L119 _public member_ `dtReal ax[3], ay[3], az[3];` — axis along edge
- L119 _public member_ `dtReal ax[3], ay[3], az[3];` — axis along edge
- L119 _public member_ `dtReal ax[3], ay[3], az[3];` — axis along edge
- L121 _public member_ `float groundRange;`
- L122 _public member_ `uint8 configIndex = INVALID_CONFIG_INDEX;`

#### enum `dtNavLinkBuilder::JumpLinkFlag`  
`enum JumpLinkFlag : unsigned char`  
_L125-129_
- L127 _public enumerator_ `FILTERED = 0`
- L128 _public enumerator_ `VALID = 1`

#### struct `dtNavLinkBuilder::JumpLink`  
`struct JumpLink`  
_L131-141_
- L133 _public member_ `dtReal spine0[MAX_SPINE*3];`
- L134 _public member_ `dtReal spine1[MAX_SPINE*3];`
- L135 _public member_ `int nspine = 0;`
- L136 _public member_ `JumpLinkFlag flags = VALID;`
- L137 _public member_ `uint8 configIndex = INVALID_CONFIG_INDEX;`
- L139 _public member_ `short debugSourceEdge = -1;`

### `Source/Runtime/Navmesh/Public/Detour/DetourNavLinkBuilderConfig.h` (Public)


#### enum `dtNavLinkBuilderFlags`  
`enum dtNavLinkBuilderFlags : unsigned short`  
_L6-10_
- L8 _public enumerator_ `DT_NAVLINK_CREATE_CENTER_POINT_LINK = 1 << 0`
- L9 _public enumerator_ `DT_NAVLINK_CREATE_EXTREMITY_LINKS = 1 << 1`

#### struct `dtNavLinkBuilderJumpConfig`  
`struct dtNavLinkBuilderJumpConfig`  
_L13-71_
- desc: Configuration for generated jump links.
- L16 _public member_ `bool enabled = true;` — Should this config be used to generate links.
- L19 _public member_ `float jumpLength = 150.f;` — Horizontal length of the jump. How far from the starting point we will look for ground. [Limit: > 0] [Units: wu]
- L22 _public member_ `float jumpDistanceFromEdge = 10.f;` — How far from the edge is the jump started. [Limit: > 0] [Units: wu]
- L25 _public member_ `float jumpMaxDepth = 150.f;` — How far below the starting height we want to look for landing ground. [Limit: > 0] [Units: wu]
- L28 _public member_ `float jumpHeight = 50.f;` — Peak height relative to the height of the starting point. [Limit: >= 0] [Units: wu]
- L31 _public member_ `float jumpEndsHeightTolerance = 50.f;` — Tolerance at both ends of the jump to find ground. [Limit: > 0] [Units: wu]
- L35 _public member_ `float samplingSeparationFactor = 1.f;` — Value multiplied by CellSize to find the distance between sampling trajectories. Default is 1. Larger values improve generation speed but might introduce sampling errors. [Limit: >= 1]
- L39 _public member_ `float filterDistanceThreshold = 80.f;` — When filtering similar links, distance used to compare between segment endpoints to match similar links. Use greater distance for more filtering (0 to deactivate filtering). [Limit: > 0] [Units: wu]
- L42 _public member_ `unsigned short linkBuilderFlags = DT_NAVLINK_CREATE_CENTER_POINT_LINK;` — Flags used to indicate how links will be added.
- L45 _public member_ `float cachedParabolaConstant = 0;` — Cached parabola constant fitting the configuration parameters.
- L48 _public member_ `float cachedDownRatio = 0;` — Cached value used when computing jump trajectory.
- L51 _public member_ `unsigned long long linkUserId = 0;` — User id used to handle links made from this configuration.
- L54 _public member_ `unsigned short downDirPolyFlag = 0;` — User defined flags assigned to downwards traversal of the off-mesh connections
- L57 _public member_ `unsigned short upDirPolyFlag = 0;` — User defined flags assigned to upwards traversal of the off-mesh connections
- L60 _public member_ `unsigned char downDirArea = 0;` — User defined area id assigned to downards traversal of the off-mesh connections
- L63 _public member_ `unsigned char upDirArea = 0;` — User defined area id assigned to upwards traversal of the off-mesh connections
- L66 _public member_ `static constexpr uint8 INVALID_CONFIG_INDEX = 0xFF;` — Unique index in TArray<dtNavLinkBuilderJumpConfig> identifying this config
- L67 _public member_ `uint8 ConfigIndex = INVALID_CONFIG_INDEX;`
- L70 _public prototype_ `void init();` — Initialize the configuration by computing cached values.

#### struct `dtNavLinkBuilderJumpDownConfig`  
`struct UE_DEPRECATED(5.7, "Use dtNavLinkBuilderJumpConfig instead.") dtNavLinkBuilderJumpDownConfig`  
_L75-129_
- desc: Configuration for generated jump down links.
- L78 _public member_ `bool enabled = true;` — Should this config be used to generate links.
- L81 _public member_ `float jumpLength = 150.f;` — Horizontal length of the jump. How far from the starting point we will look for ground. [Limit: > 0] [Units: wu]
- L84 _public member_ `float jumpDistanceFromEdge = 10.f;` — How far from the edge is the jump started. [Limit: > 0] [Units: wu]
- L87 _public member_ `float jumpMaxDepth = 150.f;` — How far below the starting height we want to look for landing ground. [Limit: > 0] [Units: wu]
- L90 _public member_ `float jumpHeight = 50.f;` — Peak height relative to the height of the starting point. [Limit: >= 0] [Units: wu]
- L93 _public member_ `float jumpEndsHeightTolerance = 50.f;` — Tolerance at both ends of the jump to find ground. [Limit: > 0] [Units: wu]
- L97 _public member_ `float samplingSeparationFactor = 1.f;` — Value multiplied by CellSize to find the distance between sampling trajectories. Default is 1. Larger values improve generation speed but might introduce sampling errors. [Limit: >= 1]
- L101 _public member_ `float filterDistanceThreshold = 80.f;` — When filtering similar links, distance used to compare between segment endpoints to match similar links. Use greater distance for more filtering (0 to deactivate filtering). [Limit: > 0] [Units: wu]
- L104 _public member_ `unsigned short linkBuilderFlags = DT_NAVLINK_CREATE_CENTER_POINT_LINK;` — Flags used to indicate how links will be added.
- L107 _public member_ `float cachedParabolaConstant = 0;` — Cached parabola constant fitting the configuration parameters.
- L110 _public member_ `float cachedDownRatio = 0;` — Cached value used when computing jump trajectory.
- L113 _public member_ `unsigned long long linkUserId = 0;` — User id used to handle links made from this configuration.
- L116 _public member_ `unsigned short downDirPolyFlag = 0;` — User defined flags assigned to downwards traversal of the off-mesh connections
- L119 _public member_ `unsigned short upDirPolyFlag = 0;` — User defined flags assigned to upwards traversal of the off-mesh connections
- L122 _public member_ `unsigned char downDirArea = 0;` — User defined area id assigned to downards traversal of the off-mesh connections
- L125 _public member_ `unsigned char upDirArea = 0;` — User defined area id assigned to upwards traversal of the off-mesh connections
- L128 _public prototype_ `void init();` — Initialize the configuration by computing cached values.

### `Source/Runtime/Navmesh/Public/Detour/DetourNavMesh.h` (Public)


#### enum `dtTileFlags`  
`enum dtTileFlags`  
_L169-172_
- desc: Tile flags used for various functions and fields. For an example, see dtNavMesh::addTile().
- L171 _public enumerator_ `DT_TILE_FREE_DATA = 0x01` — The navigation mesh owns the tile memory and is responsible for freeing it.

#### enum `dtStraightPathFlags`  
`enum dtStraightPathFlags`  
_L175-180_
- desc: Vertex flags returned by dtNavMeshQuery::findStraightPath.
- L177 _public enumerator_ `DT_STRAIGHTPATH_START = 0x01` — The vertex is the start position in the path.
- L178 _public enumerator_ `DT_STRAIGHTPATH_END = 0x02` — The vertex is the end position in the path.
- L179 _public enumerator_ `DT_STRAIGHTPATH_OFFMESH_CONNECTION = 0x04` — The vertex is the start of an off-mesh connection.

#### enum `dtStraightPathOptions`  
`enum dtStraightPathOptions`  
_L183-187_
- desc: Options for dtNavMeshQuery::findStraightPath.
- L185 _public enumerator_ `DT_STRAIGHTPATH_AREA_CROSSINGS = 0x01` — Add a vertex at every polygon edge crossing where area changes.
- L186 _public enumerator_ `DT_STRAIGHTPATH_ALL_CROSSINGS = 0x02` — Add a vertex at every polygon edge crossing.

#### enum `dtPolyTypes`  
`enum dtPolyTypes`  
_L190-203_
- desc: Flags representing the type of a navigation mesh polygon.
- L193 _public enumerator_ `DT_POLYTYPE_GROUND = 0` — The polygon is a standard convex polygon that is part of the surface of the mesh.
- L195 _public enumerator_ `DT_POLYTYPE_OFFMESH_POINT = 1` — The polygon is an off-mesh connection consisting of two vertices.
- L200 _public enumerator_ `DT_POLYTYPE_OFFMESH_SEGMENT = 2` — The polygon is an off-mesh connection consisting of four vertices.

#### struct `dtTileVert`  
`struct dtTileVert`  
_L208-242_
- desc: @UE BEGIN Tile-local vertex: stores a vertex as offsets from the tile's bmin. Use toWorld() to reconstruct the world-space position, and setFromWorld() to write back.
- L210 _public member_ `float x, y, z;`
- L210 _public member_ `float x, y, z;`
- L210 _public member_ `float x, y, z;`
- L213 _public function_ `inline void setFromWorld(const dtReal* bmin, const dtReal* worldPos)` — Encode from world position
- L236 _public function_ `inline void toWorld(const dtReal* bmin, dtReal* out) const` — Decode to world position

#### struct `dtPoly`  
`struct dtPoly`  
_L247-280_
- desc: Defines a polygon within a dtMeshTile object. @ingroup detour
- L250 _public member_ `unsigned int firstLink;` — Index to first link in linked list. (Or #DT_NULL_LINK if there is no link.)
- L254 _public member_ `unsigned short verts[DT_VERTS_PER_POLYGON];` — The indices of the polygon's vertices. The actual vertices are located in dtMeshTile::verts.
- L257 _public member_ `unsigned short neis[DT_VERTS_PER_POLYGON];` — Packed data representing neighbor polygons references and flags for each edge.
- L260 _public member_ `unsigned short flags;` — The user defined polygon flags.
- L263 _public member_ `unsigned char vertCount;` — The number of vertices in the polygon.
- L267 _public member_ `unsigned char areaAndtype;` — The bit packed area id and polygon type. @note Use the structure's set and get methods to acess this value.
- L270 _public function_ `inline void setArea(unsigned char a)` — Sets the user defined area id. [Limit: < #DT_MAX_AREAS]
- L273 _public function_ `inline void setType(unsigned char t)` — Sets the polygon type. (See: #dtPolyTypes.)
- L276 _public function_ `inline unsigned char getArea() const` — Gets the user defined area id.
- L279 _public function_ `inline unsigned char getType() const` — Gets the polygon type. (See: #dtPolyTypes)

#### struct `dtPolyDetail`  
`struct dtPolyDetail`  
_L283-289_
- desc: Defines the location of detail sub-mesh data within a dtMeshTile.
- L285 _public member_ `unsigned short vertBase;` — The offset of the vertices in the dtMeshTile::detailVerts array.
- L286 _public member_ `unsigned short triBase;` — The offset of the triangles in the dtMeshTile::detailTris array.
- L287 _public member_ `unsigned char vertCount;` — The number of vertices in the sub-mesh.
- L288 _public member_ `unsigned char triCount;` — The number of triangles in the sub-mesh.

#### struct `dtLink`  
`struct dtLink`  
_L294-302_
- desc: Defines a link between polygons. @note This structure is rarely if ever used by the end user. @see dtMeshTile
- L296 _public member_ `dtPolyRef ref;` — Neighbour reference. (The neighbor that is linked to.)
- L297 _public member_ `unsigned int next;` — Index of the next link.
- L298 _public member_ `unsigned char edge;` — Index of the polygon edge that owns this link.
- L299 _public member_ `unsigned char side;` — If a boundary link, defines on which side the link is.
- L300 _public member_ `unsigned char bmin;` — If a boundary link, defines the minimum sub-edge area.
- L301 _public member_ `unsigned char bmax;` — If a boundary link, defines the maximum sub-edge area.

#### struct `dtBVNode`  
`struct dtBVNode`  
_L307-312_
- desc: Bounding volume node. @note This structure is rarely if ever used by the end user. @see dtMeshTile
- L309 _public member_ `unsigned short bmin[3];` — Minimum bounds of the node's AABB. [(x, y, z)]
- L310 _public member_ `unsigned short bmax[3];` — Maximum bounds of the node's AABB. [(x, y, z)]
- L311 _public member_ `int i;` — The node's index. (Negative for escape sequence.)

#### struct `dtOffMeshSegmentConnection`  
`struct dtOffMeshSegmentConnection`  
_L317-347_
- desc: This is an experimental feature and has not been finished to production quality.
- L319 _public member_ `dtReal startA[3];` — Start point of segment A
- L320 _public member_ `dtReal endA[3];` — End point of segment A
- L321 _public member_ `dtReal startB[3];` — Start point of segment B
- L322 _public member_ `dtReal endB[3];` — End point of segment B
- L325 _public member_ `dtReal rad;` — The radius of the endpoints. [Limit: >= 0]
- L328 _public member_ `unsigned int userId;` — The id of the offmesh connection. (User assigned when the navigation mesh is built.)
- L331 _public member_ `unsigned short firstPoly;` — First poly in segment pool (+ header->offMeshSegPolyBase)
- L334 _public member_ `unsigned char npolys;` — Number of created polys
- L337 _public member_ `unsigned char flags;` — Link flags.
- L340 _public function_ `inline void setFlags(unsigned char conFlags)` — Sets link flags
- L346 _public function_ `inline bool getBiDirectional() const` — Gets the link direction

#### struct `dtOffMeshConnection`  
`struct dtOffMeshConnection`  
_L353-401_
- desc: Defines an navigation mesh off-mesh connection within a dtMeshTile object. An off-mesh connection is a user defined traversable connection made up to two vertices.
- L356 _public member_ `dtReal pos[6];` — The endpoints of the connection. [(ax, ay, az, bx, by, bz)]
- L359 _public member_ `dtReal rad;` — The radius of the endpoints. [Limit: >= 0]
- L363 _public member_ `dtReal height;` — @UE BEGIN The snap height of endpoints (less than 0 = use step height)
- L367 _public member_ `unsigned long long int userId;` — The id of the offmesh connection. (User assigned when the navigation mesh is built.)
- L370 _public member_ `unsigned short poly;` — The polygon reference of the connection within the tile.
- L373 _public member_ `unsigned char side;` — End point side.
- L376 _public member_ `unsigned char flags;` — Link flags.
- L380 _public function_ `inline void setFlags(unsigned char conTypeFlags)` — @UE BEGIN Sets link flags
- L389 _public function_ `inline bool getBiDirectional() const` — Gets the link direction
- L392 _public function_ `inline bool getSnapToCheapestArea() const` — Gets the link snap mode
- L395 _public function_ `inline bool getIsGenerated() const` — Indicates if the link was automatically generated
- L398 _public function_ `inline bool getIsReversed() const` — Indicates if the link is reversed

#### struct `dtCluster`  
`struct dtCluster`  
_L406-411_
- desc: Cluster of polys
- L408 _public member_ `dtReal center[3];` — Center pos of cluster
- L409 _public member_ `unsigned int firstLink;` — Link in dtMeshTile.links array
- L410 _public member_ `unsigned int numLinks;` — Number of cluster links

#### struct `dtClusterLink`  
`struct dtClusterLink`  
_L414-419_
- desc: Links between clusters
- L416 _public member_ `dtClusterRef ref;` — Destination tile and cluster
- L417 _public member_ `unsigned int next;` — Next link in dtMeshTile.links array
- L418 _public member_ `unsigned char flags;` — Link traversing data

#### struct `dtMeshHeader`  
`struct dtMeshHeader`  
_L425-464_
- desc: Provides high level information related to a dtMeshTile object. @ingroup detour
- L427 _public member_ `unsigned short version;` — Tile data format version number.
- L428 _public member_ `unsigned short layer;` — The layer of the tile within the dtNavMesh tile grid. (x, y, layer)
- L430 _public member_ `unsigned short polyCount;` — The number of polygons in the tile.
- L431 _public member_ `unsigned short vertCount;` — The number of vertices in the tile.
- L433 _public member_ `int x;` — The x-position of the tile within the dtNavMesh tile grid. (x, y, layer)
- L434 _public member_ `int y;` — The y-position of the tile within the dtNavMesh tile grid. (x, y, layer)
- L436 _public member_ `unsigned short maxLinkCount;` — The number of allocated links.
- L437 _public member_ `unsigned short detailMeshCount;` — The number of sub-meshes in the detail mesh.
- L440 _public member_ `unsigned short detailVertCount;` — The number of unique vertices in the detail mesh. (In addition to the polygon vertices.)
- L442 _public member_ `unsigned short detailTriCount;` — The number of triangles in the detail mesh.
- L443 _public member_ `unsigned short bvNodeCount;` — The number of bounding volume nodes. (Zero if bounding volumes are disabled.)
- L444 _public member_ `unsigned short offMeshConCount;` — The number of point type off-mesh connections.
- L445 _public member_ `unsigned short offMeshBase;` — The index of the first polygon which is a point type off-mesh connection.
- L449 _public member_ `unsigned short offMeshSegConCount;` — The number of segment type off-mesh connections.
- L450 _public member_ `unsigned short offMeshSegPolyBase;` — The index of the first polygon which is an segment type off-mesh connection
- L451 _public member_ `unsigned short offMeshSegVertBase;` — The index of the first vertex used by segment type off-mesh connection
- L455 _public member_ `unsigned short clusterCount;` — Number of clusters
- L458 _public member_ `unsigned char resolution;` — The resolution index used for the tile.
- L462 _public member_ `dtReal bmin[3];` — These should be at the bottom, as they are less often used than the rest of the data. The rest will fit in one cache line.
- L463 _public member_ `dtReal bmax[3];` — The maximum bounds of the tile's AABB. [(x, y, z)]

#### struct `dtMeshTile`  
`struct dtMeshTile`  
_L468-516_
- desc: Defines a navigation mesh tile. @ingroup detour
- L470 _public member_ `unsigned int salt;` — Counter describing modifications to the tile.
- L472 _public member_ `unsigned int linksFreeList;` — Index to the next free link.
- L473 _public member_ `dtMeshHeader* header;` — The tile header.
- L474 _public member_ `dtPoly* polys;` — The tile polygons. [Size: dtMeshHeader::polyCount]
- L475 _public member_ `dtTileVert* verts;` — The tile vertices. Local offsets from dtMeshHeader::bmin. [Size: dtMeshHeader::vertCount] //@UE
- L476 _public member_ `dtLink* links;` — The tile links. [Size: dtMeshHeader::maxLinkCount]
- L477 _public member_ `dtPolyDetail* detailMeshes;` — The tile's detail sub-meshes. [Size: dtMeshHeader::detailMeshCount]
- L480 _public member_ `dtTileVert* detailVerts;` — The detail mesh's unique vertices. [Size: dtMeshHeader::detailVertCount] Local offsets from dtMeshHeader::bmin. //@UE
- L483 _public member_ `unsigned char* detailTris;` — The detail mesh's triangles. [(vertA, vertB, vertC) * dtMeshHeader::detailTriCount]
- L487 _public member_ `dtBVNode* bvTree;` — The tile bounding volume nodes. [Size: dtMeshHeader::bvNodeCount] (Will be null if bounding volumes are disabled.)
- L489 _public member_ `dtOffMeshConnection* offMeshCons;` — The tile off-mesh connections. [Size: dtMeshHeader::offMeshConCount]
- L491 _public member_ `unsigned char* data;` — The tile data. (Not directly accessed under normal situations.)
- L492 _public member_ `int dataSize;` — Size of the tile data.
- L493 _public member_ `int flags;` — Tile flags. (See: #dtTileFlags)
- L494 _public member_ `dtMeshTile* next;` — The next free tile, or the next tile in the spatial grid.
- L498 _public member_ `dtOffMeshSegmentConnection* offMeshSeg;` — The tile off-mesh connections. [Size: dtMeshHeader::offMeshSegConCount]
- L502 _public member_ `dtCluster* clusters;` — Cluster data
- L503 _public member_ `unsigned short* polyClusters;` — Cluster Id for each ground type polygon [Size: dtMeshHeader::polyCount]
- L505 _public member_ `dtChunkArray<dtClusterLink, DT_ALLOC_PERM_TILE_DYNLINK_CLUSTER> dynamicLinksC;` — Dynamic links array (indices starting from DT_CLINK_FIRST)
- L508 _public member_ `dtChunkArray<dtLink, DT_ALLOC_PERM_TILE_DYNLINK> dynamicLinks;` — Dynamic links array (indices starting from dtMeshHeader::maxLinkCount)	//@UE
- L509 _public member_ `unsigned int dynamicFreeList;` — Index of the next free dynamic link //@UE
- L512 _public member_ `unsigned int dynamicFreeListC;` — Index of the next free dynamic link

#### struct `dtNavMeshResParams`  
`struct dtNavMeshResParams`  
_L520-523_
- desc: @UE BEGIN Configuration parameters depending on navmesh resolution.
- L522 _public member_ `dtReal bvQuantFactor;` — The bounding volume quantization factor.

#### struct `dtNavMeshParams`  
`struct dtNavMeshParams`  
_L530-545_
- desc: Configuration parameters used to define multi-tile navigation meshes. The values are used to allocate space during the initialization of a navigation mesh. @see dtNavMesh::init() @ingroup detour
- L533 _public member_ `dtReal walkableHeight;` — @UE BEGIN
- L534 _public member_ `dtReal walkableRadius;` — The radius of the agents using the tile.
- L535 _public member_ `dtReal walkableClimb;` — The maximum climb height of the agents using the tile.
- L537 _public member_ `dtNavMeshResParams resolutionParams[DT_RESOLUTION_COUNT];` — Parameters depending on resolutions.
- L540 _public member_ `dtReal orig[3];` — The world space origin of the navigation mesh's tile space. [(x, y, z)]
- L541 _public member_ `dtReal tileWidth;` — The width of each tile. (Along the x-axis.)
- L542 _public member_ `dtReal tileHeight;` — The height of each tile. (Along the z-axis.)
- L543 _public member_ `int maxTiles;` — The maximum number of tiles the navigation mesh can contain.
- L544 _public member_ `int maxPolys;` — The maximum number of polygons each tile can contain.

#### class `dtNavMesh`  
`class dtNavMesh`  
_L549-1045_
- desc: A navigation mesh based on tiles of convex polygons. @ingroup detour
- L552 _public prototype_ `dtNavMesh();`
- L553 _public prototype_ `~dtNavMesh();`
- L561 _public prototype_ `dtStatus init(const dtNavMeshParams* params);` — Initializes the navigation mesh for tiled use. @param[in]	params		Initialization parameters. @return The status flags for the operation.
- L569 _public prototype_ `dtStatus init(unsigned char* data, const int dataSize, const int flags);` — Initializes the navigation mesh for single tile use. @param[in]	data		Data of the new tile. (See: #dtCreateNavMeshData) @param[in]	dataSize	The data size of the new tile. @param[in]	flags		The tile flags. (See: #dtTileFlags) @return The status flags for the operation. @see dtCreateNavMeshData
- L572 _public prototype_ `const dtNavMeshParams* getParams() const;` — The navigation mesh initialization params.
- L581 _public prototype_ `dtStatus addTile(unsigned char* data, int dataSize, int flags, dtTileRef lastRef, dtTileRef* result);` — Adds a tile to the navigation mesh. @param[in]		data		Data for the new tile mesh. (See: #dtCreateNavMeshData) @param[in]		dataSize	Data size of the new tile mesh. @param[in]		flags		Tile flags. (See: #dtTileFlags) @param[in]		lastRef		The desired reference for the tile. (When reloading a tile.) [opt] [Default: 0] @param[out]	result		The tile reference. (If the tile was succesfully added.) [opt] @return The status flags for the operation.
- L589 _public prototype_ `void processSegmentLinksForTile(dtTileRef tileRef, unsigned int maxSkippedNeighborTiles, dtTileRef* skippedNeighborTiles, unsigned int& numSkippedNeighborTiles);` — Create segment link connections within a tile. @param[in]		tileRef						The tileRef of the tile owning the segment link connections. @param[in]		maxSkippedNeighborTiles		The max number of neighbor indices that can be held in skippedNeighborTiles. @param[out]	skippedNeighborTiles		Array containing the indices of the neighbor tiles processed. @param[out]	numSkippedNeighborTiles		The number of neighbor tiles skipped during link connection.
- L597 _public prototype_ `dtStatus removeTile(dtTileRef ref, unsigned char** data, int* dataSize);` — Removes the specified tile from the navigation mesh. @param[in]		ref			The reference of the tile to remove. @param[out]	data		Data associated with deleted tile. @param[out]	dataSize	Size of the data associated with deleted tile. @return The status flags for the operation.
- L608 _public prototype_ `void calcTileLoc(const dtReal* pos, int* tx, int* ty) const;` — Calculates the tile grid location for the specified world position. @param[in]	pos  The world position for the query. [(x, y, z)] @param[out]	tx		The tile's x-location. (x, y) @param[out]	ty		The tile's y-location. (x, y)
- L614 _public prototype_ `bool isTileLocInValidRange(const dtReal* pos) const;` — Calculates whether the tile grid location for the specified world position can fit in the tile indices type (currently an int) @param[in]	pos			The world position for the query. [(x, y, z)]
- L621 _public prototype_ `const dtMeshTile* getTileAt(const int x, const int y, const int layer) const;` — Gets the tile at the specified grid location. @param[in]	x		The tile's x-location. (x, y, layer) @param[in]	y		The tile's y-location. (x, y, layer) @param[in]	layer	The tile's layer. (x, y, layer) @return The tile, or null if the tile does not exist.
- L628 _public prototype_ `int getTileCountAt(const int x, const int y) const;` — @UE BEGIN Gets number of tiles at the specified grid location. (All layers.) @param[in]		x			The tile's x-location. (x, y) @param[in]		y			The tile's y-location. (x, y) @return The number of tiles in grid.
- L637 _public prototype_ `int getTilesAt(const int x, const int y, dtMeshTile const** tiles, const int maxTiles) const;` — Gets all tiles at the specified grid location. (All layers.) @param[in]		x			The tile's x-location. (x, y) @param[in]		y			The tile's y-location. (x, y) @param[out]	tiles		A pointer to an array of tiles that will hold the result. @param[in]		maxTiles	The maximum tiles the tiles parameter can hold. @return The number of tiles returned in the tiles array.
- L645 _public prototype_ `dtTileRef getTileRefAt(int x, int y, int layer) const;` — Gets the tile reference for the tile at specified grid location. @param[in]	x		The tile's x-location. (x, y, layer) @param[in]	y		The tile's y-location. (x, y, layer) @param[in]	layer	The tile's layer. (x, y, layer) @return The tile reference of the tile, or 0 if there is none.
- L650 _public prototype_ `dtTileRef getTileRef(const dtMeshTile* tile) const;` — Gets the tile reference for the specified tile. @param[in]	tile	The tile. @return The tile reference of the tile.
- L656 _public prototype_ `const dtMeshTile* getTileByRef(dtTileRef ref) const;` — Gets the tile for the specified tile reference. @param[in]	ref		The tile reference of the tile to retrieve. @return The tile for the specified reference, or null if the reference is invalid.
- L662 _public prototype_ `dtMeshTile* getMutableTileByRef(dtTileRef ref) const;` — Gets the tile for the specified tile reference. @param[in]	ref		The tile reference of the tile to retrieve. @return The tile for the specified reference, or null if the reference is invalid.
- L666 _public prototype_ `int getMaxTiles() const;` — The maximum number of tiles supported by the navigation mesh. @return The maximum number of tiles supported by the navigation mesh.
- L671 _public prototype_ `const dtMeshTile* getTile(int i) const;` — Gets the tile at the specified index. @param[in]	i		The tile index. [Limit: 0 >= index < #getMaxTiles()] @return The tile at the specified index.
- L678 _public prototype_ `dtStatus getTileAndPolyByRef(const dtPolyRef ref, const dtMeshTile** tile, const dtPoly** poly) const;` — Gets the tile and polygon for the specified polygon reference. @param[in]		ref		The reference for the a polygon. @param[out]	tile	The tile containing the polygon. @param[out]	poly	The polygon. @return The status flags for the operation.
- L684 _public prototype_ `void getTileAndPolyByRefUnsafe(const dtPolyRef ref, const dtMeshTile** tile, const dtPoly** poly) const;` — Returns the tile and polygon for the specified polygon reference. @param[in]		ref		A known valid reference for a polygon. @param[out]	tile	The tile containing the polygon. @param[out]	poly	The polygon.
- L689 _public prototype_ `bool isValidPolyRef(dtPolyRef ref) const;` — Checks the validity of a polygon reference. @param[in]	ref		The polygon reference to check. @return True if polygon reference is valid for the navigation mesh.
- L694 _public prototype_ `dtPolyRef getPolyRefBase(const dtMeshTile* tile) const;` — Gets the polygon reference for the tile's base polygon. @param[in]	tile		The tile. @return The polygon reference for the base polygon in the specified tile.
- L699 _public prototype_ `dtClusterRef getClusterRefBase(const dtMeshTile* tile) const;` — Gets the cluster reference for the tile's base cluster. @param[in]	tile		The tile. @return The cluster reference for the base cluster in the specified tile.
- L708 _public prototype_ `dtStatus getOffMeshConnectionPolyEndPoints(dtPolyRef prevRef, dtPolyRef polyRef, const dtReal* currentPos, dtReal* startPos, dtReal* endPos) const;` — Gets the endpoints for an off-mesh connection, ordered by "direction of travel". @param[in]		prevRef		The reference of the polygon before the connection. @param[in]		polyRef		The reference of the off-mesh connection polygon. @param[in]		currentPos	Position before entering off-mesh connection [(x, y, z)] @param[out]	startPos	The start position of the off-mesh connection. [(x, y, z)] @param[out]	endPos		The end position of the off-mesh connection. [(x, y, z)] @return The status flags for the operation.
- L713 _public prototype_ `const dtOffMeshConnection* getOffMeshConnectionByRef(dtPolyRef ref) const;` — Gets the specified off-mesh connection: point type. @param[in]	ref		The polygon reference of the off-mesh connection. @return The specified off-mesh connection, or null if the polygon reference is not valid.
- L718 _public prototype_ `void updateOffMeshConnectionByUserId(unsigned long long int userId, unsigned char newArea, unsigned short newFlags);` — Updates area and flags for specified off-mesh connection: point type @param[in] userId	User Id of connection @param[in] newArea	Area code to apply
- L725 _public prototype_ `const dtOffMeshSegmentConnection* getOffMeshSegmentConnectionByRef(dtPolyRef ref) const;` — Gets the specified off-mesh connection: segment type @param[in]	ref		The polygon reference of the off-mesh connection. @return The specified off-mesh connection, or null if the polygon reference is not valid.
- L730 _public prototype_ `void updateOffMeshSegmentConnectionByUserId(unsigned int userId, unsigned char newArea, unsigned short newFlags);` — Updates area and flags for specified off-mesh connection: segment type @param[in] userId	User Id of connection @param[in] newArea	Area code to apply
- L744 _public prototype_ `dtStatus setPolyFlags(dtPolyRef ref, unsigned short flags);` — Sets the user defined flags for the specified polygon. @param[in]	ref		The polygon reference. @param[in]	flags	The new flags for the polygon. @return The status flags for the operation.
- L750 _public prototype_ `dtStatus getPolyFlags(dtPolyRef ref, unsigned short* resultFlags) const;` — Gets the user defined flags for the specified polygon. @param[in]		ref				The polygon reference. @param[out]	resultFlags		The polygon flags. @return The status flags for the operation.
- L756 _public prototype_ `dtStatus setPolyArea(dtPolyRef ref, unsigned char area);` — Sets the user defined area for the specified polygon. @param[in]	ref		The polygon reference. @param[in]	area	The new area id for the polygon. [Limit: < #DT_MAX_AREAS] @return The status flags for the operation.
- L762 _public prototype_ `dtStatus getPolyArea(dtPolyRef ref, unsigned char* resultArea) const;` — Gets the user defined area for the specified polygon. @param[in]		ref			The polygon reference. @param[out]	resultArea	The area id for the polygon. @return The status flags for the operation.
- L767 _public prototype_ `int getTileStateSize(const dtMeshTile* tile) const;` — Gets the size of the buffer required by #storeTileState to store the specified tile's state. @param[in]	tile	The tile. @return The size of the buffer required to store the state.
- L774 _public prototype_ `dtStatus storeTileState(const dtMeshTile* tile, unsigned char* data, const int maxDataSize) const;` — Stores the non-structural state of the tile in the specified buffer. (Flags, area ids, etc.) @param[in]		tile			The tile. @param[out]	data			The buffer to store the tile's state in. @param[in]		maxDataSize		The size of the data buffer. [Limit: >= #getTileStateSize] @return The status flags for the operation.
- L781 _public prototype_ `dtStatus restoreTileState(dtMeshTile* tile, const unsigned char* data, const int maxDataSize);` — Restores the state of the tile. @param[in]	tile			The tile. @param[in]	data			The new state. (Obtained from #storeTileState.) @param[in]	maxDataSize		The size of the state within the data buffer. @return The status flags for the operation.
- L794 _public function_ `inline dtPolyRef encodePolyId(unsigned int salt, unsigned int it, unsigned int ip) const` — Derives a standard polygon reference. @note This function is generally meant for internal use only. @param[in]	salt	The tile's salt value. @param[in]	it		The index of the tile. @param[in]	ip		The index of the polygon within the tile.
- L806 _public function_ `inline void decodePolyId(dtPolyRef ref, unsigned int& salt, unsigned int& it, unsigned int& ip) const` — Decodes a standard polygon reference. @note This function is generally meant for internal use only. @param[in]	ref   The polygon reference to decode. @param[out]	salt	The tile's salt value. @param[out]	it		The index of the tile. @param[out]	ip		The index of the polygon within the tile. @see #encodePolyId
- L820 _public function_ `inline unsigned int decodePolyIdSalt(dtPolyRef ref) const` — Extracts a tile's salt value from the specified polygon reference. @note This function is generally meant for internal use only. @param[in]	ref		The polygon reference. @see #encodePolyId
- L830 _public function_ `inline unsigned int decodePolyIdTile(dtPolyRef ref) const` — Extracts the tile's index from the specified polygon reference. @note This function is generally meant for internal use only. @param[in]	ref		The polygon reference. @see #encodePolyId
- L840 _public function_ `inline unsigned int decodePolyIdPoly(dtPolyRef ref) const` — Extracts the polygon's index (within its tile) from the specified polygon reference. @note This function is generally meant for internal use only. @param[in]	ref		The polygon reference. @see #encodePolyId
- L849 _public function_ `inline unsigned int decodeClusterIdTile(dtClusterRef ref) const` — Extracts the tile's index from the specified cluster reference. @note This function is generally meant for internal use only. @param[in]	ref		The cluster reference.
- L859 _public function_ `inline unsigned int decodeClusterIdCluster(dtClusterRef ref) const` — Extracts the cluster's index (within its tile) from the specified cluster reference. @note This function is generally meant for internal use only. @param[in]	ref		The cluster reference.
- L866 _public prototype_ `void applyWorldOffset(const dtReal* offset);` — Shift navigation mesh by provided offset
- L869 _public function_ `inline dtLink& getLink(dtMeshTile* tile, unsigned int linkIdx)` — Helper for accessing links
- L874 _public function_ `inline const dtLink& getLink(const dtMeshTile* tile, unsigned int linkIdx) const`
- L881 _public function_ `inline dtClusterLink& getClusterLink(dtMeshTile* tile, unsigned int linkIdx)` — Helper for accessing cluster links
- L886 _public function_ `inline const dtClusterLink& getClusterLink(const dtMeshTile* tile, unsigned int linkIdx) const`
- L893 _public prototype_ `void linkOffMeshHelper(dtMeshTile* tile0, unsigned int polyIdx0, const dtMeshTile* tile1, unsigned int polyIdx1, unsigned char side, unsigned char edge);` — Helper for creating links in off-mesh connections
- L895 _public function_ `inline bool isEmpty() const`
- L901 _public function_ `inline unsigned int getSaltBits() const`
- L906 _public prototype_ `void applyAreaCostOrder(unsigned char* costOrder);`
- L910 _public function_ `void setDeferOffMeshLinking(bool bDefer)` — Defers off-mesh point link connection during addTile. Call connectDeferredOffMeshLinks() after all tiles are loaded.
- L911 _public function_ `bool isDeferringOffMeshLinking() const`
- L915 _public prototype_ `void connectDeferredOffMeshLinks();` — Connects off-mesh point links for all tiles. Used after batch loading when off-mesh linking was deferred via setDeferOffMeshLinking(true).
- L918 _public prototype_ `int getNeighbourTilesCountAt(const int x, const int y, const int side) const;` — Returns neighbour tile count based on side of given tile.
- L920 _public function_ `bool getNeighbourCoords(const int x, const int y, const int side, int& outX, int& outY) const`
- L939 _public function_ `unsigned int getTileIndex(const dtMeshTile* tile) const`
- L947 _public function_ `dtReal getWalkableHeight() const` — @UE Begin LWCoords
- L948 _public function_ `dtReal getWalkableRadius() const`
- L949 _public function_ `dtReal getWalkableClimb() const`
- L950 _public function_ `dtReal getBVQuantFactor(const unsigned char resolution) const`
- L964 _private prototype_ `dtMeshTile* getTile(int i);` — Returns pointer to tile in the tile array.
- L967 _private prototype_ `int getTilesAt(const int x, const int y, dtMeshTile** tiles, const int maxTiles) const;` — Returns the tile at the coordinates.
- L971 _private prototype_ `int getNeighbourTilesAt(const int x, const int y, const int side, dtMeshTile** tiles, const int maxTiles) const;` — Returns neighbour tile based on side.
- L975 _private prototype_ `int findConnectingPolys(const dtReal* va, const dtReal* vb, const dtMeshTile* fromTile, int fromPolyIdx, const dtMeshTile* tile, int side, dtChunkArray<FConnectingPolyData>& cons) const;` — [UE] Returns all polygons in neighbour tile based on portal defined by the segment.
- L981 _private prototype_ `void connectIntLinks(dtMeshTile* tile);` — Builds internal polygons links for a tile.
- L983 _private prototype_ `void baseOffMeshLinks(dtMeshTile* tile);` — Builds internal polygons links for a tile.
- L986 _private prototype_ `void connectExtLinks(dtMeshTile* tile, dtMeshTile* target, int side, bool updateCLinks);` — Builds external polygon links for a tile.
- L988 _private prototype_ `void connectExtOffMeshLinks(dtMeshTile* tile, dtMeshTile* target, int side, bool updateCLinks);` — Builds external polygon links for a tile.
- L991 _private prototype_ `void unconnectExtLinks(dtMeshTile* tile, dtMeshTile* target);` — Removes external links at specified side.
- L996 _private prototype_ `void connectClusterLink(dtMeshTile* tile0, unsigned int cluster0, dtMeshTile* tile1, unsigned int cluster1, unsigned char flags, bool bCheckExisting = true);` — Try to connect clusters
- L1001 _private prototype_ `void unconnectClusterLinks(dtMeshTile* tile, dtMeshTile* target);` — Removes cluster links at specified side.
- L1008 _private prototype_ `int queryPolygonsInTile(const dtMeshTile* tile, const dtReal* qmin, const dtReal* qmax, dtPolyRef* polys, const int maxPolys, bool bExcludeUnwalkable = false) const;` — Queries polygons within a tile.
- L1011 _private prototype_ `dtPolyRef findNearestPolyInTile(const dtMeshTile* tile, const dtReal* center, const dtReal* extents, dtReal* nearestPt, bool bExcludeUnwalkable = false) const;` — Find nearest polygon within a tile.
- L1013 _private prototype_ `dtPolyRef findCheapestNearPolyInTile(const dtMeshTile* tile, const dtReal* center, const dtReal* extents, dtReal* nearestPt) const;`
- L1016 _private prototype_ `void closestPointOnPolyInTile(const dtMeshTile* tile, unsigned int ip, const dtReal* pos, dtReal* closest) const;` — Returns closest point on polygon.
- L1023 _private prototype_ `bool isTileLocInValidRange(const dtReal tx, const dtReal ty) const;` — Calculates whether the tile grid location can fit in the tile indices type (currently an int) @param[in]	tx			Tile X coord @param[in]	ty			Tile Y coord
- L1024 _private prototype_ `void calcTileLoc(const dtReal* pos, dtReal* tx, dtReal* ty) const;`
- L1027 _public member_ `dtNavMeshParams m_params;` — Current initialization params.
- L1028 _public member_ `dtReal m_orig[3];` — Origin of the tile (0,0)
- L1029 _public member_ `dtReal m_tileWidth, m_tileHeight;` — Dimensions of each tile.
- L1029 _public member_ `dtReal m_tileWidth, m_tileHeight;` — Dimensions of each tile.
- L1031 _public member_ `int m_maxTiles;` — Max number of tiles.
- L1032 _public member_ `int m_tileLutSize;` — Tile hash lookup size (must be pot).
- L1033 _public member_ `int m_tileLutMask;` — Tile hash lookup mask.
- L1035 _public member_ `unsigned char m_areaCostOrder[DT_MAX_AREAS];`
- L1036 _public member_ `bool m_bDeferOffMeshLinking;`
- L1038 _public member_ `dtMeshTile** m_posLookup;` — Tile hash lookup.
- L1039 _public member_ `dtMeshTile* m_nextFree;` — Freelist of tiles.
- L1040 _public member_ `dtMeshTile* m_tiles;` — List of tiles.
- L1042 _public member_ `unsigned int m_saltBits;` — Number of salt bits in the tile ID.
- L1043 _public member_ `unsigned int m_tileBits;` — Number of tile bits in the tile ID.
- L1044 _public member_ `unsigned int m_polyBits;` — Number of poly bits in the tile ID.

#### struct `dtNavMesh::FConnectingPolyData`  
`struct FConnectingPolyData`  
_L956-961_
- desc: [UE] result struct for findConnectingPolys
- L958 _public member_ `dtReal min;`
- L959 _public member_ `dtReal max;`
- L960 _public member_ `dtPolyRef ref;`

#### struct `ReadTilesHelper`  
`struct ReadTilesHelper`  
_L1058-1088_
- desc: @UE BEGIN: helper for reading tiles
- L1060 _public member_ `static const int MaxTiles = 32;`
- L1061 _public member_ `dtMeshTile* Tiles[MaxTiles];`
- L1063 _public member_ `int NumAllocated;`
- L1064 _public member_ `dtMeshTile** AllocatedTiles;`
- L1066 _public function_ `ReadTilesHelper() : NumAllocated(0), AllocatedTiles(nullptr)`
- L1067 _public function_ `~ReadTilesHelper()`
- L1072 _public function_ `dtMeshTile** PrepareArray(int RequestedSize)`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURNAVMESH_H`
- L32 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDetour, Log, All);`
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSegmentLink, Warning, All);`
- L42 _macro_ `#define USE_64BIT_ADDRESS 1`
- L49 _typedef_ `typedef unsigned long long UEType_uint64;` — LP64 (Linux/OS X): UE will define its uint64 type as "unsigned long long" so we need to match this
- L52 _typedef_ `typedef uint64_t UEType_uint64;`
- L57 _typedef_ `typedef UEType_uint64 dtPolyRef;` — A handle to a polygon within a navigation mesh tile. @ingroup detour
- L61 _typedef_ `typedef UEType_uint64 dtTileRef;` — A handle to a tile within a navigation mesh. @ingroup detour
- L64 _typedef_ `typedef UEType_uint64 dtClusterRef;` — A handle to a cluster within a navigation mesh tile.
- L70 _typedef_ `typedef unsigned int dtPolyRef;` — A handle to a polygon within a navigation mesh tile. @ingroup detour
- L74 _typedef_ `typedef unsigned int dtTileRef;` — A handle to a tile within a navigation mesh. @ingroup detour
- L77 _typedef_ `typedef unsigned int dtClusterRef;` — A handle to a cluster within a navigation mesh tile.
- L83 _variable_ `static const int DT_VERTS_PER_POLYGON = 6;` — The maximum number of vertices per navigation polygon. @ingroup detour
- L96 _variable_ `static const int DT_NAVMESH_VERSION = 8;` — A version number used to detect compatibility of navigation tile data.
- L99 _variable_ `static const int DT_NAVMESH_STATE_MAGIC = 'D'<<24 | 'N'<<16 | 'M'<<8 | 'S';` — A magic number used to detect the compatibility of navigation tile states.
- L102 _variable_ `static const int DT_NAVMESH_STATE_VERSION = 1;` — A version number used to detect compatibility of navigation tile states.
- L108 _variable_ `static const unsigned short DT_EXT_LINK = 0x8000;` — A flag that indicates that an entity links to an external entity. (E.g. A polygon edge is a portal that links to another polygon.)
- L111 _variable_ `inline const unsigned int DT_NULL_LINK = 0xffffffff;` — A value that indicates the entity does not link to anything.
- L114 _variable_ `static const unsigned char DT_OFFMESH_CON_BIDIR = 0x01;` — A flag that indicates that an off-mesh connection can be traversed in both directions. (Is bidirectional.)
- L115 _variable_ `static const unsigned char DT_OFFMESH_CON_POINT = 0x02;` — UE
- L116 _variable_ `static const unsigned char DT_OFFMESH_CON_SEGMENT = 0x04;` — UE
- L117 _variable_ `static const unsigned char DT_OFFMESH_CON_CHEAPAREA = 0x08;` — UE
- L118 _variable_ `static const unsigned char DT_OFFMESH_CON_GENERATED = 0x10;` — UE
- L120 _variable_ `static const unsigned char DT_OFFMESH_CON_REVERSED = 0x20;` — A flag that indicates whether the direction of travel along the one-way off-mesh connection is actually reversed.
- L124 _variable_ `static const int DT_MAX_AREAS = 64;` — The maximum number of user defined area ids. @ingroup detour
- L128 _variable_ `static const int DT_MIN_SALT_BITS = 5;` — @UE BEGIN Navmesh tiles' salt will have at least this much bits
- L129 _variable_ `static const int DT_SALT_BASE = 1;`
- L131 _variable_ `static const int DT_RESOLUTION_COUNT = 3;`
- L135 _variable_ `static const int DT_MAX_OFFMESH_SEGMENT_PARTS = 4;` — Max segment parts for segment-to-segment off mesh connection
- L136 _variable_ `static const int DT_INVALID_SEGMENT_PART = 0xffff;`
- L140 _variable_ `static const unsigned char DT_CONNECTION_INTERNAL = (1 << 7);` — flags use to annotate dtLink::side with addotional data
- L141 _variable_ `static const unsigned char DT_LINK_FLAG_OFFMESH_CON = (1 << 6);`
- L142 _variable_ `static const unsigned char DT_LINK_FLAG_OFFMESH_CON_BIDIR = (1 << 5);`
- L143 _variable_ `static const unsigned char DT_LINK_FLAG_OFFMESH_CON_BACKTRACKER = (1 << 4);`
- L144 _variable_ `static const unsigned char DT_LINK_FLAG_OFFMESH_CON_ENABLED = (1 << 3);`
- L145 _variable_ `static const unsigned char DT_LINK_FLAG_SIDE_MASK = 7;`
- L149 _variable_ `static const unsigned char DT_CLINK_VALID_FWD = 0x01;` — flags used to annotate dtClusterLink::flags with additional data
- L150 _variable_ `static const unsigned char DT_CLINK_VALID_BCK = 0x02;`
- L153 _variable_ `static const unsigned int DT_CLINK_FIRST = 0x80000000;` — Index of first cluster link within tile
- L160 _typedef_ `typedef void (dtStatsPostAddTileFunc)(const dtMeshTile& TileAdd);`
- L162 _typedef_ `typedef void (dtStatsPreRemoveTileFunc)(const dtMeshTile& tileRemove);`
- L164 _prototype_ `void dtStatsSetCustom(dtStatsPostAddTileFunc* addFunc, dtStatsPreRemoveTileFunc* removeFunc);`
- L1050 _prototype_ `dtNavMesh* dtAllocNavMesh();` — Allocates a navigation mesh object using the Detour allocator. @return A navigation mesh that is ready for initialization, or null on failure. @ingroup detour
- L1055 _prototype_ `void dtFreeNavMesh(dtNavMesh* navmesh);` — Frees the specified navigation mesh object using the Detour allocator. @param[in]	navmesh		A navigation mesh allocated using #dtAllocNavMesh @ingroup detour

### `Source/Runtime/Navmesh/Public/Detour/DetourNavMeshBuilder.h` (Public)


#### struct `dtOffMeshLinkCreateParams`  
`struct dtOffMeshLinkCreateParams`  
_L29-48_
- L32 _public member_ `dtReal vertsA0[3];` — Off-mesh connection vertices (point-point = A0 <> B0, segment-segment = A0-A1 <> B0-B1 ) [Unit: wu]
- L33 _public member_ `dtReal vertsA1[3];`
- L34 _public member_ `dtReal vertsB0[3];`
- L35 _public member_ `dtReal vertsB1[3];`
- L37 _public member_ `dtReal snapRadius;` — Off-mesh connection radii. [Unit: wu]
- L39 _public member_ `dtReal snapHeight;` — Off-mesh connection height, less than 0 = use step height [Unit: wu]
- L41 _public member_ `unsigned long long int userID;` — The user defined ids of the off-mesh connection.
- L43 _public member_ `unsigned short polyFlag;` — User defined flags assigned to the polys of off-mesh connections
- L45 _public member_ `unsigned char area;` — User defined area ids assigned to the off-mesh connections
- L47 _public member_ `unsigned char type;` — Off-mesh connection type (point to point, segment to segment, bidirectional)

#### struct `dtDynamicAreaCreateParams`  
`struct dtDynamicAreaCreateParams`  
_L51-60_
- desc: @todo: This appears unused
- L54 _public member_ `unsigned char area;` — Area id
- L56 _public member_ `dtReal minH;` — Covex min,max height
- L57 _public member_ `dtReal maxH;`
- L59 _public member_ `dtChunkArray<dtReal> verts;` — X,Z coords of covex

#### struct `dtNavMeshCreateParams`  
`struct dtNavMeshCreateParams`  
_L64-158_
- desc: Represents the source data used to build an navigation mesh tile. @ingroup detour
- L72 _public member_ `const unsigned short* verts;` — The polygon mesh vertices. [(x, y, z) * #vertCount] [Unit: vx]
- L73 _public member_ `int vertCount;` — The number vertices in the polygon mesh. [Limit: >= 3]
- L74 _public member_ `const unsigned short* polys;` — The polygon data. [Size: #polyCount * 2 * #nvp]
- L75 _public member_ `const unsigned short* polyFlags;` — The user defined flags assigned to each polygon. [Size: #polyCount]
- L76 _public member_ `const unsigned char* polyAreas;` — The user defined area ids assigned to each polygon. [Size: #polyCount]
- L77 _public member_ `int polyCount;` — Number of polygons in the mesh. [Limit: >= 1]
- L78 _public member_ `int nvp;` — Number maximum number of vertices per polygon. [Limit: >= 3]
- L85 _public member_ `unsigned short* polyClusters;` — @} @name Cluster Attributes @{
- L86 _public member_ `unsigned short clusterCount;` — Number of unique clusters
- L95 _public member_ `const unsigned int* detailMeshes;` — The height detail sub-mesh data. [Size: 4 * #polyCount]
- L96 _public member_ `const dtReal* detailVerts;` — The detail mesh vertices. [Size: 3 * #detailVertsCount] [Unit: wu]
- L97 _public member_ `int detailVertsCount;` — The number of vertices in the detail mesh.
- L98 _public member_ `const unsigned char* detailTris;` — The detail mesh triangles. [Size: 4 * #detailTriCount]
- L99 _public member_ `int detailTriCount;` — The number of triangles in the detail mesh.
- L109 _public member_ `const dtOffMeshLinkCreateParams* offMeshCons;` — Off-mesh connection data. [Size: #offMeshConCount] [Unit: wu]
- L111 _public member_ `int offMeshConCount;` — The number of off-mesh connections. [Limit: >= 0]
- L119 _public member_ `const dtDynamicAreaCreateParams* dynamicAreas;` — Dynamic Area data. [Size: #dynamicAreaCount] [Unit: wu]
- L121 _public member_ `int dynamicAreaCount;` — The number of dynamic areas. [Limit: >= 0]
- L129 _public member_ `unsigned int userId;` — The user defined id of the tile.
- L130 _public member_ `int tileX;` — The tile's x-grid location within the multi-tile destination mesh. (Along the x-axis.)
- L131 _public member_ `int tileY;` — The tile's y-grid location within the multi-tile destination mesh. (Along the z-axis.)
- L132 _public member_ `int tileLayer;` — The tile's layer within the layered destination mesh. (Along the y-axis.) [Limit: >= 0]
- L133 _public member_ `dtReal bmin[3];` — The minimum bounds of the tile. [(x, y, z)] [Unit: wu]
- L134 _public member_ `dtReal bmax[3];` — The maximum bounds of the tile. [(x, y, z)] [Unit: wu]
- L140 _public member_ `dtReal walkableHeight;` — The agent height. [Unit: wu]
- L141 _public member_ `dtReal walkableRadius;` — The agent radius. [Unit: wu]
- L142 _public member_ `dtReal walkableClimb;` — The agent maximum traversable ledge. (Up/Down) [Unit: wu]
- L143 _public member_ `dtReal cs;` — The xz-plane cell size of the polygon mesh. [Limit: > 0] [Unit: wu]
- L144 _public member_ `dtReal ch;` — The y-axis cell height of the polygon mesh. [Limit: > 0] [Unit: wu]
- L146 _public member_ `unsigned char tileResolutionLevel;` — Tile resolution index 		//@UE
- L150 _public member_ `bool buildBvTree;` — True if a bounding volume tree should be built for the tile. @note The BVTree is not normally needed for layered navigation meshes.
- L154 _public member_ `bool bMinimizeLinkPoolSize;` — @UE BEGIN If true, minimize base link pool size else use previous larger base pool.

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURNAVMESHBUILDER_H`
- L166 _prototype_ `bool dtCreateNavMeshData(dtNavMeshCreateParams* params, unsigned char** outData, int* outDataSize);` — Builds navigation mesh tile data from the provided tile creation data. @ingroup detour @param[in]		params		Tile creation data. @param[out]	outData		The resulting tile data. @param[out]	outDataSize	The size of the tile data array. @return True if the tile data was successfully created.
- L171 _prototype_ `bool dtNavMeshHeaderSwapEndian(unsigned char* data, const int dataSize);` — Swaps the endianess of the tile data's header (#dtMeshHeader). @param[in,out]	data		The tile data array. @param[in]		dataSize	The size of the data array.
- L176 _prototype_ `bool dtNavMeshDataSwapEndian(unsigned char* data, const int dataSize);` — Swaps endianess of the tile data. @param[in,out]	data		The tile data array. @param[in]		dataSize	The size of the data array.
- L187 _prototype_ `bool dtTransformTileData(unsigned char* data, const int dataSize, const int offsetX, const int offsetY, const dtReal tileWidth, const dtReal tileHeight, const dtReal rotationDeg, const dtReal bvQuantFactor);` — @UE BEGIN Offset and rotate around center the data in the tile @param[in,out]	data			Data of the tile mesh. (See: #dtCreateNavMeshData) @param[in]		dataSize		Data size of the tile mesh. @param[in]		offsetX			X offset in tile coordinates. @param[in]		offsetY			Y offset in tile coordinates. @param[in]		tileWidth		Tile width. @param[in]		tileHeight		Tile height. @param[in]		rotationDeg		Rotation in degrees.
- L197 _prototype_ `void dtComputeTileOffsetFromRotation(const dtReal* position, const dtReal* rotationCenter, const dtReal rotationDeg, const dtReal tileWidth, const dtReal tileHeight, int& deltaX, int& deltaY);` — Compute XY offset caused by the given rotation @param[in]		position		Position to rotate. [(x, y, z)] @param[in]		rotationCenter	Rotation center. [(x, y, z)] @param[in]		rotationDeg		Rotation in degrees. @param[in]		tileWidth		Tile width. @param[in]		tileHeight		Tile height. @param[out]	deltaX			Offset X in tile coordinates. @param[out]	deltaY			Offset Y in tile coordinates.

### `Source/Runtime/Navmesh/Public/Detour/DetourNavMeshQuery.h` (Public)


#### struct `dtQuerySpecialLinkFilter`  
`struct dtQuerySpecialLinkFilter`  
_L49-63_
- desc: Special link filter is custom filter run only for offmesh links with assigned UserId Used by smart navlinks in UE
- L51 _public prototype_ `virtual ~dtQuerySpecialLinkFilter() = default;`
- L56 _public function_ `virtual bool isLinkAllowed(const unsigned long long int UserId) const`
- L59 _public function_ `virtual bool isLinkAllowed(const int UserId) const final` — `UE_DEPRECATED(5.3, "LinkIds are now based on a 64 bit uint. Use the version of this function that takes an unsigned long long int")`
- L62 _public function_ `virtual void initialize()` — Called before accessing in A* loop (can be called multiple time for updateSlicedFindPath)

#### struct `dtQueryFilterData`  
`struct dtQueryFilterData`  
_L66-91_
- desc: [UE: moved all filter variables to struct, DO NOT mess with virtual functions here!]
- L68 _public member_ `dtReal m_areaCost[DT_MAX_AREAS];` — Cost per area type. (Used by default implementation.)
- L70 _public member_ `dtReal m_areaFixedCost[DT_MAX_AREAS];` — Fixed cost for entering an area type (Used by default implementation.)
- L72 _public member_ `dtReal heuristicScale;` — Search heuristic scale.
- L73 _public member_ `dtReal lowestAreaCost;`
- L75 _public member_ `unsigned short m_includeFlags;` — Flags for polygons that can be visited. (Used by default implementation.)
- L76 _public member_ `unsigned short m_excludeFlags;` — Flags for polygons that should not be visited. (Used by default implementation.)
- L78 _public member_ `bool m_isBacktracking;`
- L84 _public member_ `bool m_shouldIgnoreClosedNodes;` — @UE BEGIN whether to ignore neighbour nodes that have already been visited. FALSE by default but you might want to set it to true if using heuristic scale much larger than 1 or experiencing cycles in our paths for any other reason
- L87 _public prototype_ `dtQueryFilterData();`
- L89 _public prototype_ `bool equals(const dtQueryFilterData* other) const;`
- L90 _public prototype_ `void copyFrom(const dtQueryFilterData* source);`

#### class `dtQueryFilter`  
`class dtQueryFilter`  
_L95-302_
- desc: Defines polygon filtering and traversal costs for navigation mesh query operations. @ingroup detour
- L98 _protected member_ `dtQueryFilterData data;`
- L99 _protected member_ `bool isVirtual;`
- L102 _public function_ `dtQueryFilter(bool inIsVirtual = true) : isVirtual(inIsVirtual)`
- L104 _public prototype_ `virtual ~dtQueryFilter() = default;`
- L109 _protected function_ `inline bool passInlineFilter(const dtPolyRef ref, const dtMeshTile* tile, const dtPoly* poly) const` — inlined filter implementation. @see passFilter for parameter description
- L122 _protected function_ `virtual bool passVirtualFilter(const dtPolyRef ref, const dtMeshTile* tile, const dtPoly* poly) const` — virtual filter implementation (defaults to passInlineFilter). @see passFilter for parameter description
- L131 _public function_ `bool getIsVirtual() const` — Returns true if it's a virtual filter.
- L137 _public function_ `inline bool passFilter(const dtPolyRef ref, const dtMeshTile* tile, const dtPoly* poly) const` — Returns true if the polygon can be visited.  (I.e. Is traversable.) @param[in]		ref		The reference id of the polygon test. @param[in]		tile	The tile containing the polygon. @param[in]		poly  The polygon to test.
- L147 _protected function_ `inline dtReal getInlineCost(const dtReal* pa, const dtReal* pb, const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly, const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly, const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const` — inlined scoring function. @see getCost for parameter description
- L163 _protected function_ `virtual dtReal getVirtualCost(const dtReal* pa, const dtReal* pb, const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly, const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly, const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const` — virtual scoring function implementation (defaults to getInlineCost). @see getCost for parameter description
- L177 _protected function_ `virtual float getVirtualCost(const float* pa, const float* pb, const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly, const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly, const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const final` — This function is deprecated call the version on this function that takes FReal
- L202 _public function_ `inline dtReal getCost(const dtReal* pa, const dtReal* pb, const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly, const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly, const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const` — Returns cost to move from the beginning to the end of a line segment that is fully contained within a polygon. @param[in]		pa			The start position on the edge of the previous and current polygon. [(x, y, z)] @param[in]		pb			The end position on the edge of the current and next polygon. [(x, y, z)] @param[in]		prevRef		The reference id of the previous polygon. [opt] @param[in]		prevTile	The tile containing the previous polygon. [opt] @param[in]		prevPoly	The previous polygon. [opt] @param[in]		curRef		The reference id of the current polygon. @param[in]		curTile		The tile containing the current polygon. @param[in]		curPoly		The current polygon. @param[in]		nextRef		The reference id of the next polygon. [opt] @param[in]		nextTile	The tile containing the next polygon. [opt] @param[in]		nextPoly	The next polygon. [opt]
- L217 _public function_ `inline dtReal getAreaCost(const int i) const` — Returns the traversal cost of the area. @param[in]		i		The id of the area. @returns The traversal cost of the area.
- L222 _public function_ `inline void setAreaCost(const int i, const dtReal cost)` — Sets the traversal cost of the area. @param[in]		i		The id of the area. @param[in]		cost	The new cost of traversing the area.
- L225 _public function_ `inline const dtReal* getAllAreaCosts() const` — @UE BEGIN
- L231 _public function_ `inline dtReal getAreaFixedCost(const int i) const` — Returns the fixed cost for entering an area. @param[in]		i		The id of the area. @returns The fixed cost of the area.
- L236 _public function_ `inline void setAreaFixedCost(const int i, const dtReal cost)` — Sets the fixed cost for entering an area. @param[in]		i		The id of the area. @param[in]		cost	The new fixed cost of entering the area polygon.
- L238 _public function_ `inline const dtReal* getAllFixedAreaCosts() const`
- L241 _public function_ `inline dtReal getModifiedHeuristicScale() const`
- L245 _public function_ `inline dtReal getHeuristicScale() const` — Retrieves euclidean distance heuristic scale @returns heuristic scale
- L248 _public function_ `inline void setHeuristicScale(const dtReal newScale)` — Set euclidean distance heuristic scale
- L252 _public function_ `inline bool isValidLinkSide(const unsigned char side) const` — Filters link in regards to its side. Used for backtracking. @returns should link with this side be accepted
- L260 _public function_ `inline void setIsBacktracking(const bool isBacktracking)` — Sets up filter for backtracking
- L264 _public function_ `inline bool getIsBacktracking() const` — Retrieves information whether this filter is set up for backtracking @returns is backtracking
- L267 _public function_ `inline void setShouldIgnoreClosedNodes(const bool shouldIgnore)` — Instruct filter whether it can reopen nodes already on closed list
- L271 _public function_ `inline bool getShouldIgnoreClosedNodes() const` — Retrieves information whether this filter allows reopening closed nodes @returns should consider reopening nodes already on closed list
- L277 _public function_ `inline unsigned short getIncludeFlags() const` — Returns the include flags for the filter. Any polygons that include one or more of these flags will be included in the operation.
- L281 _public function_ `inline void setIncludeFlags(const unsigned short flags)` — Sets the include flags for the filter. @param[in]		flags	The new flags.
- L286 _public function_ `inline unsigned short getExcludeFlags() const` — Returns the exclude flags for the filter. Any polygons that include one ore more of these flags will be excluded from the operation.
- L290 _public function_ `inline void setExcludeFlags(const unsigned short flags)` — Sets the exclude flags for the filter. @param[in]		flags		The new flags.
- L295 _public function_ `inline bool equals(const dtQueryFilter* other) const` — Check if two filters have the same data values
- L296 _public function_ `inline bool equals(const dtQueryFilter& other) const`
- L299 _public function_ `inline void copyFrom(const dtQueryFilter* other)` — Copy data values from source filter
- L300 _public function_ `inline void copyFrom(const dtQueryFilter& other)`

#### struct `dtQueryResultPack`  
`struct dtQueryResultPack`  
_L304-313_
- L306 _public member_ `dtPolyRef ref;`
- L307 _public member_ `dtReal cost;`
- L308 _public member_ `dtReal pos[3];`
- L309 _public member_ `unsigned int flag;`
- L311 _public function_ `dtQueryResultPack() : ref(0), cost(0), flag(0)`
- L312 _public prototype_ `dtQueryResultPack(dtPolyRef inRef, dtReal inCost, const dtReal* inPos, unsigned int inFlag);`

#### struct `dtQueryResult`  
`struct dtQueryResult`  
_L315-343_
- L317 _public function_ `inline void reserve(int n)`
- L318 _public function_ `inline int size() const`
- L320 _public function_ `inline dtPolyRef getRef(int idx) const`
- L321 _public function_ `inline dtReal getCost(int idx) const`
- L322 _public function_ `inline const dtReal* getPos(int idx) const`
- L323 _public function_ `inline unsigned int getFlag(int idx) const`
- L324 _public prototype_ `void getPos(int idx, dtReal* pos);`
- L326 _public prototype_ `void copyRefs(dtPolyRef* refs, int nmax);`
- L327 _public prototype_ `void copyCosts(dtReal* costs, int nmax);`
- L328 _public prototype_ `void copyPos(dtReal* pos, int nmax);`
- L329 _public prototype_ `void copyFlags(unsigned char* flags, int nmax);`
- L330 _public prototype_ `void copyFlags(unsigned int* flags, int nmax);`
- L333 _protected member_ `dtChunkArray<dtQueryResultPack> data;`
- L335 _protected function_ `inline int addItem(dtPolyRef ref, dtReal cost, const dtReal* pos, unsigned int flag)`
- L337 _protected function_ `inline void setRef(int idx, dtPolyRef ref)`
- L338 _protected function_ `inline void setCost(int idx, dtReal cost)`
- L339 _protected function_ `inline void setFlag(int idx, unsigned int flag)`
- L340 _protected prototype_ `void setPos(int idx, const dtReal* pos);`

#### class `dtNavMeshQuery`  
`class dtNavMeshQuery`  
_L348-853_
- desc: Provides the ability to perform pathfinding related queries against a navigation mesh. @ingroup detour
- L351 _public prototype_ `dtNavMeshQuery();`
- L352 _public prototype_ `~dtNavMeshQuery();`
- L359 _public prototype_ `dtStatus init(const dtNavMesh* nav, const int maxNodes, dtQuerySpecialLinkFilter* linkFilter = 0);` — Initializes the query object. @param[in]		nav			Pointer to the dtNavMesh object to use for all queries. @param[in]		maxNodes	Maximum number of search nodes. [Limits: 0 < value <= 65536] @param[in]		linkFilter	Special link filter used for every query @returns The status flags for the query.
- L362 _public prototype_ `void updateLinkFilter(dtQuerySpecialLinkFilter* linkFilter);` — UE: updates special link filter for this query
- L376 _public prototype_ `dtStatus findPath(dtPolyRef startRef, dtPolyRef endRef, const dtReal* startPos, const dtReal* endPos, const dtReal costLimit,` — Finds a path from the start polygon to the end polygon. @param[in]		startRef	The reference id of the start polygon. @param[in]		endRef		The reference id of the end polygon. @param[in]		startPos	A position within the start polygon. [(x, y, z)] @param[in]		endPos		A position within the end polygon. [(x, y, z)] @param[in]		costLimit	Cost limit of nodes allowed to be added to the open list	//@UE @param[in]		filter		The polygon filter to apply to the query. @param[out]	result		Results for path corridor, fills in refs and costs for each poly from start to end @param[out]	totalCost			If provided will get filled will total cost of path
- L389 _public prototype_ `dtStatus findStraightPath(const dtReal* startPos, const dtReal* endPos, const dtPolyRef* path, const int pathSize, dtQueryResult& result, const int options = 0) const;` — Finds the straight path from the start to the end position within the polygon corridor. @param[in]		startPos			Path start position. [(x, y, z)] @param[in]		endPos				Path end position. [(x, y, z)] @param[in]		path				An array of polygon references that represent the path corridor. @param[in]		pathSize			The number of polygons in the @p path array. @param[out]	result				Fills in positions, refs and flags @param[in]		options				Query options. (see: #dtStraightPathOptions) @returns The status flags for the query.
- L410 _public prototype_ `dtStatus initSlicedFindPath(dtPolyRef startRef, dtPolyRef endRef, const dtReal* startPos, const dtReal* endPos, const dtReal costLimit, const bool requireNavigableEndLocation,` — Initializes a sliced path query. @param[in]		startRef					The refrence id of the start polygon. @param[in]		endRef						The reference id of the end polygon. @param[in]		startPos					A position within the start polygon. [(x, y, z)] @param[in]		endPos						A position within the end polygon. [(x, y, z)] @param[in]		costLimit					Cost limit of nodes allowed to be added to the open list	//@UE @param[in]		requireNavigableEndLocation	Define if the end location is required to be a valid navmesh polygon //@UE @param[in]		filter						The polygon filter to apply to the query. @returns The status flags for the query.
- L418 _public prototype_ `dtStatus updateSlicedFindPath(const int maxIter, int* doneIters);` — Updates an in-progress sliced path query. @param[in]		maxIter		The maximum number of iterations to perform. @param[out]	doneIters	The actual number of iterations completed. [opt] @returns The status flags for the query.
- L426 _public prototype_ `dtStatus finalizeSlicedFindPath(dtPolyRef* path, int* pathCount, const int maxPath);` — Finalizes and returns the results of a sliced path query. @param[out]	path		An ordered list of polygon references representing the path. (Start to end.) [(polyRef) * @p pathCount] @param[out]	pathCount	The number of polygons returned in the @p path array. @param[in]		maxPath		The max number of polygons the path array can hold. [Limit: >= 1] @returns The status flags for the query.
- L437 _public prototype_ `dtStatus finalizeSlicedFindPathPartial(const dtPolyRef* existing, const int existingSize, dtPolyRef* path, int* pathCount, const int maxPath);` — Finalizes and returns the results of an incomplete sliced path query, returning the path to the furthest polygon on the existing path that was visited during the search. @param[out]	existing		An array of polygon references for the existing path. @param[out]	existingSize	The number of polygon in the @p existing array. @param[out]	path			An ordered list of polygon references representing the path. (Start to end.) [(polyRef) * @p pathCount] @param[out]	pathCount		The number of polygons returned in the @p path array. @param[in]		maxPath			The max number of polygons the @p path array can hold. [Limit: >= 1] @returns The status flags for the query.
- L456 _public prototype_ `dtStatus findPolysAroundCircle(dtPolyRef startRef, const dtReal* centerPos, const dtReal radius, const dtQueryFilter* filter, dtPolyRef* resultRef, dtPolyRef* resultParent, dtReal* resultCost, int* resultCount, const int maxResult) const;` — Finds the polygons along the navigation graph that touch the specified circle. @param[in]		startRef		The reference id of the polygon where the search starts. @param[in]		centerPos		The center of the search circle. [(x, y, z)] @param[in]		radius			The radius of the search circle. @param[in]		filter			The polygon filter to apply to the query. @param[out]	resultRef		The reference ids of the polygons touched by the circle. [opt] @param[out]	resultParent	The reference ids of the parent polygons for each result. Zero if a result polygon has no parent. [opt] @param[out]	resultCost		The search cost from @p centerPos to the polygon. [opt] @param[out]	resultCount		The number of polygons found. @param[in]		maxResult		The maximum number of polygons the result arrays can hold. @returns The status flags for the query.
- L474 _public prototype_ `dtStatus findPolysAroundShape(dtPolyRef startRef, const dtReal* verts, const int nverts, const dtQueryFilter* filter, dtPolyRef* resultRef, dtPolyRef* resultParent, dtReal* resultCost, int* resultCount, const int maxResult) const;` — Finds the polygons along the naviation graph that touch the specified convex polygon. @param[in]		startRef		The reference id of the polygon where the search starts. @param[in]		verts			The vertices describing the convex polygon. (CCW) [(x, y, z) * @p nverts] @param[in]		nverts			The number of vertices in the polygon. @param[in]		filter			The polygon filter to apply to the query. @param[out]	resultRef		The reference ids of the polygons touched by the search polygon. [opt] @param[out]	resultParent	The reference ids of the parent polygons for each result. Zero if a result polygon has no parent. [opt] @param[out]	resultCost		The search cost from the centroid point to the polygon. [opt] @param[out]	resultCount		The number of polygons found. @param[in]		maxResult		The maximum number of polygons the result arrays can hold. @returns The status flags for the query.
- L489 _public prototype_ `dtStatus findPolysInPathDistance(dtPolyRef startRef, const dtReal* centerPos, const dtReal pathDistance, const dtQueryFilter* filter, dtPolyRef* resultRef, int* resultCount, const int maxResult) const;` — @UE BEGIN Finds the polygons along the navigation graph that are no more than given path length away from centerPos. @param[in]		startRef		The reference id of the polygon where the search starts. @param[in]		centerPos		The center of the search circle. [(x, y, z)] @param[in]		pathDistance	The path distance limit of the search @param[in]		filter			The polygon filter to apply to the query. @param[out]	resultRef		The reference ids of the polygons touched by the circle. [opt] @param[out]	resultCount		The number of polygons found. [opt] @param[in]		maxResult		The maximum number of polygons the result arrays can hold. @returns The status flags for the querydtReal
- L505 _public prototype_ `dtStatus findNearestPoly(const dtReal* center, const dtReal* extents, const dtQueryFilter* filter, dtPolyRef* nearestRef, dtReal* nearestPt, const dtReal* referencePt = 0) const;` — Finds the polygon nearest to the specified center point. @param[in]		center		The center of the search box. [(x, y, z)] @param[in]		extents		The search distance along each axis. [(x, y, z)] @param[in]		filter		The polygon filter to apply to the query. @param[out]	nearestRef	The reference id of the nearest polygon. @param[out]	nearestPt	The nearest point on the polygon. [opt] [(x, y, z)] @param[in]		referencePt	If supplied replaces @param center in terms of distance measurements. Note that extents are not precise when using a referencePt. [opt] [(x, y, z)] @returns The status flags for the query.
- L518 _public prototype_ `dtStatus findNearestPoly2D(const dtReal* center, const dtReal* extents, const dtQueryFilter* filter, dtPolyRef* outProjectedRef, dtReal* outProjectedPt, const dtReal* referencePt = 0, dtReal tolerance = 0) const;` — Finds the polygon 2D-nearest to the specified center point. @param[in]		center		The center of the search box. [(x, y, z)] @param[in]		extents		The search distance along each axis. [(x, y, z)] @param[in]		filter		The polygon filter to apply to the query. @param[out]	nearestRef	The reference id of the nearest polygon. @param[out]	nearestPt	The nearest point on the polygon. [opt] [(x, y, z)] @param[in]		referencePt	If supplied replaces @param center in terms of distance measurements. Note that extents are not precise when using a referencePt. [opt] [(x, y, z)] @param[in]		tolerance	Radius around best 2D point for picking vertical match @returns The status flags for the query.
- L530 _public prototype_ `dtStatus findNearestContainingPoly(const dtReal* center, const dtReal* extents, const dtQueryFilter* filter, dtPolyRef* nearestRef, dtReal* nearestPt) const;` — Finds the nearest polygon in height containing the specified center point. @param[in]		center		The center of the search box. [(x, y, z)] @param[in]		extents		The search distance along each axis. [(x, y, z)] @param[in]		filter		The polygon filter to apply to the query. @param[out]	nearestRef	The reference id of the nearest polygon. @param[out]	nearestPt	The nearest point on the polygon. [opt] [(x, y, z)] @returns The status flags for the query.
- L543 _public prototype_ `dtStatus queryPolygons(const dtReal* center, const dtReal* extents, const dtQueryFilter* filter, dtPolyRef* polys, int* polyCount, const int maxPolys) const;` — Finds polygons that overlap the search box. @param[in]		center		The center of the search box. [(x, y, z)] @param[in]		extents		The search distance along each axis. [(x, y, z)] @param[in]		filter		The polygon filter to apply to the query. @param[out]	polys		The reference ids of the polygons that overlap the query box. @param[out]	polyCount	The number of polygons in the search result. @param[in]		maxPolys	The maximum number of polygons the search result can hold. @returns The status flags for the query.
- L558 _public prototype_ `dtStatus findLocalNeighbourhood(dtPolyRef startRef, const dtReal* centerPos, const dtReal radius, const dtQueryFilter* filter, dtPolyRef* resultRef, dtPolyRef* resultParent, int* resultCount, const int maxResult) const;` — Finds the non-overlapping navigation polygons in the local neighbourhood around the center position. @param[in]		startRef		The reference id of the polygon where the search starts. @param[in]		centerPos		The center of the query circle. [(x, y, z)] @param[in]		radius			The radius of the query circle. @param[in]		filter			The polygon filter to apply to the query. @param[out]	resultRef		The reference ids of the polygons touched by the circle. @param[out]	resultParent	The reference ids of the parent polygons for each result. Zero if a result polygon has no parent. [opt] @param[out]	resultCount		The number of polygons found. @param[in]		maxResult		The maximum number of polygons the result arrays can hold. @returns The status flags for the query.
- L564 _public prototype_ `dtStatus findWallsInNeighbourhood(dtPolyRef startRef, const dtReal* centerPos, const dtReal radius, const dtQueryFilter* filter, dtPolyRef* neiRefs, int* neiCount, const int maxNei, dtReal* resultWalls, dtPolyRef* resultRefs, int* resultCount, const int maxResult) const;` — [UE] Finds the wall segments in local neighbourhood
- L571 _public prototype_ `dtStatus findWallsOverlappingShape(dtPolyRef startRef, const dtReal* verts, const int nverts, const dtQueryFilter* filter, dtPolyRef* neiRefs, int* neiCount, const int maxNei, dtReal* resultWalls, dtPolyRef* resultRefs, int* resultCount, const int maxResult) const;` — [UE] Finds the wall segments that overlap the polygon shape.
- L577 _public prototype_ `dtStatus findWallsAroundPath(const dtPolyRef* path, const int pathCount, const dtReal* searchAreaPoly, const int searchAreaPolyCount, const dtReal maxAreaEnterCost, const dtQueryFilter* filter, dtPolyRef* neiRefs, int* neiCount, const int maxNei, dtReal* resultWalls, dtPolyRef* resultRefs, int* resultCount, const int maxResult) const;` — [UE] Finds the wall segments that overlap the polygon shape.
- L592 _public prototype_ `dtStatus moveAlongSurface(dtPolyRef startRef, const dtReal* startPos, const dtReal* endPos, const dtQueryFilter* filter, dtReal* resultPos, dtPolyRef* visited, int* visitedCount, const int maxVisitedSize) const;` — Moves from the start to the end position constrained to the navigation mesh. @param[in]		startRef		The reference id of the start polygon. @param[in]		startPos		A position of the mover within the start polygon. [(x, y, x)] @param[in]		endPos			The desired end position of the mover. [(x, y, z)] @param[in]		filter			The polygon filter to apply to the query. @param[out]	resultPos		The result position of the mover. [(x, y, z)] @param[out]	visited			The reference ids of the polygons visited during the move. @param[out]	visitedCount	The number of polygons visited during the move. @param[in]		maxVisitedSize	The maximum number of polygons the @p visited array can hold. @returns The status flags for the query.
- L610 _public prototype_ `dtStatus raycast(dtPolyRef startRef, const dtReal* startPos, const dtReal* endPos, const dtQueryFilter* filter, dtReal* t, dtReal* hitNormal, dtPolyRef* path, int* pathCount, const int maxPath) const;` — Casts a 'walkability' ray along the surface of the navigation mesh from the start position toward the end position. @param[in]		startRef	The reference id of the start polygon. @param[in]		startPos	A position within the start polygon representing the start of the ray. [(x, y, z)] @param[in]		endPos		The position to cast the ray toward. [(x, y, z)] @param[out]	t			The hit parameter. (DT_REAL_MAX if no wall hit.) @param[out]	hitNormal	The normal of the nearest wall hit. [(x, y, z)] @param[in]		filter		The polygon filter to apply to the query. @param[out]	path		The reference ids of the visited polygons. [opt] @param[out]	pathCount	The number of visited polygons. [opt] @param[in]		maxPath		The maximum number of polygons the @p path array can hold. @param[in]		walkableArea Specific area that can be visited or 255 to skip it and test all areas. @returns The status flags for the query.
- L624 _public prototype_ `dtStatus findDistanceToWall(dtPolyRef startRef, const dtReal* centerPos, const dtReal maxRadius, const dtQueryFilter* filter, dtReal* hitDist, dtReal* hitPos, dtReal* hitNormal) const;` — Finds the distance from the specified position to the nearest polygon wall. @param[in]		startRef		The reference id of the polygon containing @p centerPos. @param[in]		centerPos		The center of the search circle. [(x, y, z)] @param[in]		maxRadius		The radius of the search circle. @param[in]		filter			The polygon filter to apply to the query. @param[out]	hitDist			The distance to the nearest wall from @p centerPos. @param[out]	hitPos			The nearest position on the wall that was hit. [(x, y, z)] @param[out]	hitNormal		The normalized ray formed from the wall point to the source point. [(x, y, z)] @returns The status flags for the query.
- L637 _public prototype_ `dtStatus getPolyWallSegments(dtPolyRef ref, const dtQueryFilter* filter, dtReal* segmentVerts, dtPolyRef* segmentRefs, int* segmentCount, const int maxSegments) const;` — Returns the segments for the specified polygon, optionally including portals. @param[in]		ref				The reference id of the polygon. @param[in]		filter			The polygon filter to apply to the query. @param[out]	segmentVerts	The segments. [(ax, ay, az, bx, by, bz) * segmentCount] @param[out]	segmentRefs		The reference ids of each segment's neighbor polygon. Or zero if the segment is a wall. [opt] [(parentRef) * @p segmentCount] @param[out]	segmentCount	The number of segments returned. @param[in]		maxSegments		The maximum number of segments the result arrays can hold. @returns The status flags for the query.
- L648 _public prototype_ `dtStatus findRandomPoint(const dtQueryFilter* filter, float(*frand)(), dtPolyRef* randomRef, dtReal* randomPt) const;` — Returns random location on navmesh. Polygons are chosen weighted by area. The search runs in linear related to number of polygon. @param[in]		filter			The polygon filter to apply to the query. @param[in]		frand			Function returning a random number [0..1). @param[out]	randomRef		The reference id of the random location. @param[out]	randomPt		The random location. @returns The status flags for the query.
- L661 _public prototype_ `dtStatus findRandomPointAroundCircle(dtPolyRef startRef, const dtReal* centerPos, const dtReal maxRadius, const dtQueryFilter* filter, float(*frand)(), dtPolyRef* randomRef, dtReal* randomPt) const;` — Returns random location on navmesh within the reach of specified location. Polygons are chosen weighted by area. The search runs in linear related to number of polygon. The location is not exactly constrained by the circle, but it limits the visited polygons. @param[in]		startRef		The reference id of the polygon where the search starts. @param[in]		centerPos		The center of the search circle. [(x, y, z)] @param[in]		filter			The polygon filter to apply to the query. @param[in]		frand			Function returning a random number [0..1). @param[out]	randomRef		The reference id of the random location. @param[out]	randomPt		The random location. [(x, y, z)] @returns The status flags for the query.
- L670 _public prototype_ `dtStatus findRandomPointInPoly(dtPolyRef ref, float(*frand)(), dtReal* randomPt) const;` — Returns random location inside the specified polygon. @param[in]		ref				The reference id of the polygon. @param[in]		frand			Function returning a random number [0..1). @param[out]	randomPt		The random location. [(x, y, z)] @returns The status flags for the query.
- L678 _public prototype_ `dtStatus testClusterPath(dtPolyRef startRef, dtPolyRef endRef) const;` — Check if there is a path from start polygon to the end polygon using cluster graph (cheap, does not care about link costs) @param[in]		startRef			The reference id of the start polygon. @param[in]		endRef				The reference id of the end polygon.
- L685 _public prototype_ `dtStatus findRandomPointInCluster(dtClusterRef clusterRef, float(*frand)(), dtPolyRef* randomRef, dtReal* randomPt) const;` — Returns random location on navmesh within specified cluster. @param[in]		frand			Function returning a random number [0..1). @param[out]	randomRef		The reference id of the random location. @param[out]	randomPt		The random location. @returns The status flags for the query.
- L692 _public prototype_ `dtStatus getPolyCluster(dtPolyRef polyRef, dtClusterRef& clusterRef) const;` — Gets the cluster containing given polygon @param[in]		polyRef		The reference id of the polygon. @param[out]	clusterRef	The reference id of the cluster @returns The status flags for the query.
- L701 _public prototype_ `dtStatus closestPointOnPoly(dtPolyRef ref, const dtReal* pos, dtReal* closest) const;` — Finds the closest point on the specified polygon. @param[in]		ref			The reference id of the polygon. @param[in]		pos			The position to check. [(x, y, z)] @param[out]	closest		The closest point on the polygon. [(x, y, z)] @returns The status flags for the query.
- L709 _public prototype_ `dtStatus closestPointOnPolyBoundary(dtPolyRef ref, const dtReal* pos, dtReal* closest) const;` — Returns a point on the boundary closest to the source point if the source point is outside the polygon's xz-bounds. @param[in]		ref			The reference id to the polygon. @param[in]		pos			The position to check. [(x, y, z)] @param[out]	closest		The closest point. [(x, y, z)] @returns The status flags for the query.
- L716 _public prototype_ `dtStatus projectedPointOnPoly(dtPolyRef ref, const dtReal* pos, dtReal* projected) const;` — Finds the point's projection on the specified polygon. @param[in]		ref			The reference id of the polygon. @param[in]		pos			The position to check. [(x, y, z)] @param[out]	closest		The projected point on the polygon. [(x, y, z)] @returns The status flags for the query.
- L723 _public prototype_ `dtStatus isPointInsidePoly(dtPolyRef ref, const dtReal* pos, bool& result) const;` — Checks if specified pos is inside given polygon specified by ref @param[in]		ref			The reference id of the polygon. @param[in]		pos			The position to check. [(x, y, z)] @param[out]	result		The result of the check, whether the point is inside (true) or not (false) @returns The status flags for the query.
- L730 _public prototype_ `dtStatus getPolyHeight(dtPolyRef ref, const dtReal* pos, dtReal* height) const;` — Gets the height of the polygon at the provided position using the height detail. (Most accurate.) @param[in]		ref			The reference id of the polygon. @param[in]		pos			A position within the xz-bounds of the polygon. [(x, y, z)] @param[out]	height		The height at the surface of the polygon. @returns The status flags for the query.
- L739 _public prototype_ `bool isValidPolyRef(dtPolyRef ref, const dtQueryFilter* filter) const;` — Returns true if the polygon reference is valid and passes the filter restrictions. @param[in]		ref			The polygon reference to check. @param[in]		filter		The filter to apply.
- L744 _public prototype_ `bool isInClosedList(dtPolyRef ref) const;` — Returns true if the polygon reference is in the closed list. @param[in]		ref		The reference id of the polygon to check. @returns True if the polygon is in closed list.
- L750 _public prototype_ `bool wasClusterLinkSearched(dtPolyRef cFrom, dtPolyRef cTo) const;` — Returns true if the cluster link was used in previous search. @param[in]		cFrom		The reference id of the start cluster. @param[in]		cto			The reference id of the end cluster. @returns True if the cluster link was searched.
- L754 _public function_ `class dtNodePool* getNodePool() const` — Gets the node pool. @returns The node pool.
- L758 _public function_ `const dtNavMesh* getAttachedNavMesh() const` — Gets the navigation mesh the query object is using. @return The navigation mesh the query object is using.
- L761 _public function_ `void getCurrentBestResult(struct dtNode*& bestNode, dtReal& bestCost) const` — Gets best node ref and cost from sliced pathfinding data
- L763 _public function_ `int getQueryNodes() const`
- L769 _private prototype_ `dtMeshTile* getNeighbourTileAt(int x, int y, int side) const;` — Returns neighbour tile based on side.
- L772 _private prototype_ `int queryPolygonsInTile(const dtMeshTile* tile, const dtReal* qmin, const dtReal* qmax, const dtQueryFilter* filter, dtPolyRef* polys, const int maxPolys) const;` — Queries polygons within a tile.
- L775 _private prototype_ `dtPolyRef findNearestPolyInTile(const dtMeshTile* tile, const dtReal* center, const dtReal* extents, const dtQueryFilter* filter, dtReal* nearestPt) const;` — Find nearest polygon within a tile.
- L778 _private prototype_ `void closestPointOnPolyInTile(const dtMeshTile* tile, const dtPoly* poly, const dtReal* pos, dtReal* closest) const;` — Returns closest point on polygon.
- L781 _private prototype_ `dtStatus projectedPointOnPolyInTile(const dtMeshTile* tile, const dtPoly* poly, const dtReal* pos, dtReal* projected) const;` — Returns projected point on polygon.
- L785 _private prototype_ `static void dtApplyEpsilon(dtReal* extents);` — @UE BEGIN Handle 0 extents by having the vector components set to a minimum value.
- L790 _public prototype_ `dtStatus getPortalPoints(dtPolyRef from, dtPolyRef to, dtReal* left, dtReal* right, unsigned char& fromType, unsigned char& toType) const;` — Returns portal points between two polygons.
- L792 _public prototype_ `dtStatus getPortalPoints(dtPolyRef from, const dtPoly* fromPoly, const dtMeshTile* fromTile, dtPolyRef to, const dtPoly* toPoly, const dtMeshTile* toTile, dtReal* left, dtReal* right) const;`
- L797 _public prototype_ `dtStatus getEdgeMidPoint(dtPolyRef from, dtPolyRef to, dtReal* mid) const;` — Returns edge mid point between two polygons.
- L798 _public prototype_ `dtStatus getEdgeMidPoint(dtPolyRef from, const dtPoly* fromPoly, const dtMeshTile* fromTile, dtPolyRef to, const dtPoly* toPoly, const dtMeshTile* toTile, dtReal* mid) const;`
- L804 _public prototype_ `dtStatus appendVertex(const dtReal* pos, const unsigned char flags, const dtPolyRef ref, dtQueryResult& result, const bool bOverrideIdenticalPosition = true) const;` — Appends vertex to a straight path
- L808 _public prototype_ `dtStatus appendPortals(const int startIdx, const int endIdx, const dtReal* endPos, const dtPolyRef* path, dtQueryResult& result, const int options) const;` — Appends intermediate portal points to a straight path.
- L811 _public function_ `inline bool passLinkFilterByRef(const dtMeshTile* tile, const dtPolyRef ref) const`
- L816 _public function_ `inline bool passLinkFilter(const dtMeshTile* tile, const int polyIdx) const`
- L827 _public function_ `inline void setRequireNavigableEndLocation(const bool value)` — @UE BEGIN
- L828 _public function_ `inline bool isRequiringNavigableEndLocation() const`
- L832 _private member_ `const dtNavMesh* m_nav;` — Pointer to navmesh data.
- L833 _private member_ `dtQuerySpecialLinkFilter* m_linkFilter;` — Pointer to optional special link filter
- L846 _private member_ `dtQueryData m_query;` — Sliced query state.
- L848 _private member_ `class dtNodePool* m_tinyNodePool;` — Pointer to small node pool.
- L849 _private member_ `class dtNodePool* m_nodePool;` — Pointer to node pool.
- L850 _private member_ `class dtNodeQueue* m_openList;` — Pointer to open list queue.
- L852 _private member_ `mutable int m_queryNodes;`

#### struct `dtNavMeshQuery::dtQueryData`  
`struct dtQueryData`  
_L835-845_
- L837 _public member_ `dtStatus status;`
- L838 _public member_ `struct dtNode* lastBestNode;`
- L839 _public member_ `dtReal lastBestNodeCost;`
- L840 _public member_ `dtPolyRef startRef, endRef;`
- L840 _public member_ `dtPolyRef startRef, endRef;`
- L841 _public member_ `dtReal startPos[3], endPos[3];`
- L841 _public member_ `dtReal startPos[3], endPos[3];`
- L842 _public member_ `dtReal costLimit;` — @UE ///< Cost limit of nodes allowed to be added to the open list
- L843 _public member_ `const dtQueryFilter* filter;`
- L844 _public member_ `unsigned char requireNavigableEndLocation : 1;` — @UE

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURNAVMESHQUERY_H`
- L34 _macro_ `#define WITH_FIXED_AREA_ENTERING_COST 1` — @UE BEGIN
- L37 _macro_ `#define DT_UNWALKABLE_POLY_COST FLT_MAX` — Note poly costs are still floats in UE so we are using FLT_MAX as unwalkable still.
- L858 _prototype_ `dtNavMeshQuery* dtAllocNavMeshQuery();` — Allocates a query object using the Detour allocator. @return An allocated query object, or null on failure. @ingroup detour
- L863 _prototype_ `void dtFreeNavMeshQuery(dtNavMeshQuery* query);` — Frees the specified query object using the Detour allocator. @param[in]		query		A query object allocated using #dtAllocNavMeshQuery @ingroup detour

### `Source/Runtime/Navmesh/Public/Detour/DetourNode.h` (Public)


#### enum `dtNodeFlags`  
`enum dtNodeFlags`  
_L29-33_
- L31 _public enumerator_ `DT_NODE_OPEN = 0x01`
- L32 _public enumerator_ `DT_NODE_CLOSED = 0x02`

#### struct `dtNode`  
`struct dtNode`  
_L38-46_
- L40 _public member_ `dtReal pos[3];` — Position of the node.
- L41 _public member_ `dtReal cost;` — Cost from previous node to current node.
- L42 _public member_ `dtReal total;` — Cost up to the node.
- L43 _public member_ `unsigned int pidx : 30;` — Index to parent node.
- L44 _public member_ `unsigned int flags : 2;` — Node flags 0/open/closed.
- L45 _public member_ `dtPolyRef id;` — Polygon ref the node corresponds to.

#### class `dtNodePool`  
`class dtNodePool`  
_L49-114_
- L52 _public prototype_ `dtNodePool(int maxNodes, int hashSize);`
- L53 _public prototype_ `~dtNodePool();`
- L54 _public function_ `inline void operator=(const dtNodePool&)`
- L55 _public prototype_ `void clear();`
- L56 _public prototype_ `dtNode* getNode(dtPolyRef id);`
- L57 _public prototype_ `dtNode* findNode(dtPolyRef id);`
- L59 _public function_ `inline unsigned int getNodeIdx(const dtNode* node) const`
- L65 _public function_ `inline dtNode* getNodeAtIdx(unsigned int idx)`
- L71 _public function_ `inline const dtNode* getNodeAtIdx(unsigned int idx) const`
- L77 _public function_ `inline int getMemUsed() const`
- L85 _public function_ `inline int getMaxNodes() const`
- L90 _public function_ `inline int getMaxRuntimeNodes() const` — @UE BEGIN If using a shared query instance it's possible that m_maxNodes is greater than pool size requested by callee. There's no point in reallocating the pool so we artificially limit the number of available nodes
- L92 _public function_ `inline int getNodeCount() const` — @UE END
- L94 _public function_ `inline int getHashSize() const`
- L95 _public function_ `inline dtNodeIndex getFirst(int bucket) const`
- L96 _public function_ `inline dtNodeIndex getNext(int i) const`
- L100 _public function_ `inline void setMaxRuntimeNodes(const int newMaxRuntimeNodes)` — @UE BEGIN overrides m_maxNodes for runtime purposes
- L105 _private member_ `dtNode* m_nodes;`
- L106 _private member_ `dtNodeIndex* m_first;`
- L107 _private member_ `dtNodeIndex* m_next;`
- L108 _private member_ `const int m_maxNodes;`
- L109 _private member_ `const int m_hashSize;`
- L111 _private member_ `int m_maxRuntimeNodes;` — @UE BEGIN
- L113 _private member_ `int m_nodeCount;` — @UE END

#### class `dtNodeQueue`  
`class dtNodeQueue`  
_L116-176_
- L119 _public prototype_ `dtNodeQueue(int n);`
- L120 _public prototype_ `~dtNodeQueue();`
- L121 _public function_ `inline void operator=(dtNodeQueue&)`
- L123 _public function_ `inline void clear()`
- L128 _public function_ `inline dtNode* top()`
- L133 _public function_ `inline dtNode* pop()`
- L141 _public function_ `inline void push(dtNode* node)`
- L147 _public function_ `inline void modify(dtNode* node)`
- L159 _public function_ `inline bool empty() const`
- L161 _public function_ `inline int getMemUsed() const`
- L167 _public function_ `inline int getCapacity() const`
- L170 _private prototype_ `void bubbleUp(int i, dtNode* node);`
- L171 _private prototype_ `void trickleDown(int i, dtNode* node);`
- L173 _private member_ `dtNode** m_heap;`
- L174 _private member_ `const int m_capacity;`
- L175 _private member_ `int m_size;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURNODE_H`
- L35 _typedef_ `typedef unsigned short dtNodeIndex;`
- L36 _variable_ `static const dtNodeIndex DT_NULL_IDX = (dtNodeIndex)~0;`

### `Source/Runtime/Navmesh/Public/Detour/DetourStatus.h` (Public)


#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURSTATUS_H`
- L27 _typedef_ `typedef unsigned int dtStatus;`
- L30 _variable_ `static const unsigned int DT_FAILURE = 1u << 31;` — High level status.
- L31 _variable_ `static const unsigned int DT_SUCCESS = 1u << 30;` — Operation succeed.
- L32 _variable_ `static const unsigned int DT_IN_PROGRESS = 1u << 29;` — Operation still in progress.
- L35 _variable_ `static const unsigned int DT_STATUS_DETAIL_MASK = 0x0ffffff;` — Detail information for status.
- L37 _variable_ `static const unsigned int DT_WRONG_VERSION = 1 << 1;` — static const unsigned int DT_WRONG_MAGIC = 1 << 0;		// Input data is not recognized. NOTE: UE magic removed to save memory
- L38 _variable_ `static const unsigned int DT_OUT_OF_MEMORY = 1 << 2;` — Operation ran out of memory.
- L39 _variable_ `static const unsigned int DT_INVALID_PARAM = 1 << 3;` — An input parameter was invalid.
- L40 _variable_ `static const unsigned int DT_BUFFER_TOO_SMALL = 1 << 4;` — Result buffer for the query was too small to store all results.
- L41 _variable_ `static const unsigned int DT_OUT_OF_NODES = 1 << 5;` — Query ran out of nodes during search.
- L42 _variable_ `static const unsigned int DT_PARTIAL_RESULT = 1 << 6;` — Query did not reach the end location, returning best guess.
- L43 _variable_ `static const unsigned int DT_INVALID_CYCLE_PATH = 1 << 7;` — Query found a path containing a cycle
- L47 _function_ `inline bool dtStatusSucceed(dtStatus status)` — Returns true of status is success.
- L53 _function_ `inline bool dtStatusFailed(dtStatus status)` — Returns true of status is failure.
- L59 _function_ `inline bool dtStatusInProgress(dtStatus status)` — Returns true of status is in progress.
- L65 _function_ `inline bool dtStatusDetail(dtStatus status, unsigned int detail)` — Returns true if specific detail is set.

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourCrowd.h` (Public)


#### struct `dtCrowdNeighbour`  
`struct dtCrowdNeighbour`  
_L66-70_
- desc: Provides neighbor data for agents managed by the crowd. @ingroup crowd @see dtCrowdAgent::neis, dtCrowd
- L68 _public member_ `int idx;` — The index of the neighbor in the crowd.
- L69 _public member_ `dtReal dist;` — The distance between the current agent and the neighbor.

#### enum `CrowdAgentState`  
`enum CrowdAgentState`  
_L74-80_
- desc: The type of navigation mesh polygon the agent is currently traversing. @ingroup crowd
- L76 _public enumerator_ `DT_CROWDAGENT_STATE_INVALID` — The agent is not in a valid state.
- L77 _public enumerator_ `DT_CROWDAGENT_STATE_WALKING` — The agent is traversing a normal navigation mesh polygon.
- L78 _public enumerator_ `DT_CROWDAGENT_STATE_OFFMESH` — The agent is traversing an off-mesh connection.
- L79 _public enumerator_ `DT_CROWDAGENT_STATE_WAITING` — [UE] The agent is waiting for external movement to finish

#### struct `dtCrowdAgentParams`  
`struct dtCrowdAgentParams`  
_L84-125_
- desc: Configuration parameters for a crowd agent. @ingroup crowd
- L87 _public member_ `void* userData;` — User defined data attached to the agent.
- L90 _public member_ `TSharedPtr<dtQuerySpecialLinkFilter> linkFilter;` — UE: special link filter used by this agent
- L92 _public member_ `dtReal radius;` — Agent radius. [Limit: >= 0]
- L93 _public member_ `dtReal height;` — Agent height. [Limit: > 0]
- L94 _public member_ `dtReal maxAcceleration;` — Maximum allowed acceleration. [Limit: >= 0]
- L95 _public member_ `dtReal maxSpeed;` — Maximum allowed speed. [Limit: >= 0]
- L98 _public member_ `dtReal collisionQueryRange;` — Defines how close a collision element must be before it is considered for steering behaviors. [Limits: > 0]
- L100 _public member_ `dtReal pathOptimizationRange;` — The path visibility optimization range. [Limit: > 0]
- L103 _public member_ `dtReal separationWeight;` — How aggresive the agent manager should be at avoiding collisions with this agent. [Limit: >= 0]
- L106 _public member_ `dtReal avoidanceQueryMultiplier;` — [UE] Mutliplier for avoidance velocities
- L109 _public member_ `unsigned int avoidanceGroup;` — [UE] Groups flags attached to the agent
- L111 _public member_ `unsigned int groupsToAvoid;` — [UE] Avoid agents when they group is matching mask
- L113 _public member_ `unsigned int groupsToIgnore;` — [UE] Don't avoid agents when they group is matching mask
- L116 _public member_ `unsigned short updateFlags;` — Flags that impact steering behavior. (See: #UpdateFlags)
- L120 _public member_ `unsigned char obstacleAvoidanceType;` — The index of the avoidance configuration to use for the agent. [Limits: 0 <= value <= #DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS]
- L124 _public member_ `unsigned char filter;` — UE: Id of navigation filter used by this agent [Limits: 0 <= value <= #DT_CROWD_MAX_FILTERS]

#### enum `MoveRequestState`  
`enum MoveRequestState`  
_L127-136_
- L129 _public enumerator_ `DT_CROWDAGENT_TARGET_NONE = 0`
- L130 _public enumerator_ `DT_CROWDAGENT_TARGET_FAILED`
- L131 _public enumerator_ `DT_CROWDAGENT_TARGET_VALID`
- L132 _public enumerator_ `DT_CROWDAGENT_TARGET_REQUESTING`
- L133 _public enumerator_ `DT_CROWDAGENT_TARGET_WAITING_FOR_QUEUE`
- L134 _public enumerator_ `DT_CROWDAGENT_TARGET_WAITING_FOR_PATH`
- L135 _public enumerator_ `DT_CROWDAGENT_TARGET_VELOCITY`

#### struct `dtCrowdAgent`  
`struct dtCrowdAgent`  
_L140-194_
- desc: Represents an agent managed by a #dtCrowd object. @ingroup crowd
- L143 _public member_ `dtPathCorridor corridor;` — The path corridor the agent is using.
- L146 _public member_ `dtLocalBoundary boundary;` — The local boundary data for the agent.
- L149 _public member_ `dtReal topologyOptTime;` — Time since the agent's path corridor was optimized.
- L152 _public member_ `dtCrowdNeighbour neis[DT_CROWDAGENT_MAX_NEIGHBOURS];` — The known neighbors of the agent.
- L155 _public member_ `dtReal desiredSpeed;` — The desired speed.
- L157 _public member_ `dtReal npos[3];` — The current agent position. [(x, y, z)]
- L158 _public member_ `dtReal disp[3];`
- L159 _public member_ `dtReal dvel[3];` — The desired velocity of the agent. [(x, y, z)]
- L160 _public member_ `dtReal nvel[3];`
- L161 _public member_ `dtReal vel[3];` — The actual velocity of the agent. [(x, y, z)]
- L164 _public member_ `dtCrowdAgentParams params;` — The agent's configuration parameters.
- L167 _public member_ `dtReal cornerVerts[DT_CROWDAGENT_MAX_CORNERS*3];` — The local path corridor corners for the agent. (Staight path.) [(x, y, z) * #ncorners]
- L170 _public member_ `dtPolyRef cornerPolys[DT_CROWDAGENT_MAX_CORNERS];` — The reference id of the polygon being entered at the corner. [(polyRef) * #ncorners]
- L172 _public member_ `dtReal targetReplanTime;` — <Time since the agent's target was replanned.
- L173 _public member_ `dtReal targetPos[3];` — Target position of the movement request (or velocity in case of DT_CROWDAGENT_TARGET_VELOCITY).
- L174 _public member_ `dtPolyRef targetRef;` — Target polyref of the movement request.
- L175 _public member_ `dtPathQueueRef targetPathqRef;` — Path finder ref.
- L178 _public member_ `int nneis;` — The number of neighbors.
- L181 _public member_ `unsigned char cornerFlags[DT_CROWDAGENT_MAX_CORNERS];` — The local path corridor corner flags. (See: #dtStraightPathFlags) [(flags) * #ncorners]
- L184 _public member_ `int ncorners;` — The number of corners.
- L186 _public member_ `unsigned char targetReplan;` — Flag indicating that the current path is being replanned.
- L187 _public member_ `unsigned char targetState;` — State of the movement request.
- L190 _public member_ `unsigned char active;` — 1 if the agent is active, or 0 if the agent is in an unused slot in the agent pool.
- L193 _public member_ `unsigned char state;` — The type of mesh polygon the agent is traversing. (See: #CrowdAgentState)

#### struct `dtCrowdAgentAnimation`  
`struct dtCrowdAgentAnimation`  
_L196-202_
- L198 _public member_ `dtReal initPos[3], startPos[3], endPos[3];`
- L198 _public member_ `dtReal initPos[3], startPos[3], endPos[3];`
- L198 _public member_ `dtReal initPos[3], startPos[3], endPos[3];`
- L199 _public member_ `dtPolyRef polyRef;`
- L200 _public member_ `dtReal t, tmax;`
- L200 _public member_ `dtReal t, tmax;`
- L201 _public member_ `unsigned char active;`

#### enum `UpdateFlags`  
`enum UpdateFlags`  
_L207-217_
- desc: Crowd agent update flags. @ingroup crowd @see dtCrowdAgentParams::updateFlags
- L209 _public enumerator_ `DT_CROWD_ANTICIPATE_TURNS = 1 << 0`
- L210 _public enumerator_ `DT_CROWD_OBSTACLE_AVOIDANCE = 1 << 1`
- L211 _public enumerator_ `DT_CROWD_SEPARATION = 1 << 2`
- L212 _public enumerator_ `DT_CROWD_OPTIMIZE_VIS = 1 << 3` — Use #dtPathCorridor::optimizePathVisibility() to optimize the agent path.
- L213 _public enumerator_ `DT_CROWD_OPTIMIZE_TOPO = 1 << 4` — Use dtPathCorridor::optimizePathTopology() to optimize the agent path.
- L214 _public enumerator_ `DT_CROWD_OPTIMIZE_VIS_MULTI = 1 << 5` — [UE] Multiple calls for optimizePathVisibility instead of checking last point
- L215 _public enumerator_ `DT_CROWD_OFFSET_PATH = 1 << 6` — [UE] Offset path points from corners by agent radius
- L216 _public enumerator_ `DT_CROWD_SLOWDOWN_AT_GOAL = 1 << 7` — [UE] Slowdown before reaching goal

#### enum `CrowdBoundaryFlags`  
`enum CrowdBoundaryFlags`  
_L220-223_
- desc: [UE] Flags used by boundary segments (dtLocalBoundary::Segment)
- L222 _public enumerator_ `DT_CROWD_BOUNDARY_IGNORE = 1 << 0`

#### struct `dtCrowdAgentDebugInfo`  
`struct dtCrowdAgentDebugInfo`  
_L225-231_
- L227 _public member_ `int idx;`
- L228 _public member_ `dtReal optStart[3], optEnd[3];`
- L228 _public member_ `dtReal optStart[3], optEnd[3];`
- L229 _public member_ `dtObstacleAvoidanceDebugData* vod;`
- L230 _public member_ `TMap<int32, FString> agentLog;`

#### class `dtCrowd`  
`class dtCrowd`  
_L235-535_
- desc: Provides local steering behaviors for a group of agents. @ingroup crowd
- L237 _private member_ `int m_maxAgents;`
- L238 _private member_ `int m_numActiveAgents;`
- L239 _private member_ `dtCrowdAgent* m_agents;`
- L240 _private member_ `dtCrowdAgent** m_activeAgents;`
- L241 _private member_ `dtCrowdAgentAnimation* m_agentAnims;`
- L243 _private member_ `dtPathQueue m_pathq;`
- L244 _private member_ `dtSharedBoundary m_sharedBoundary;`
- L246 _private member_ `dtObstacleAvoidanceParams m_obstacleQueryParams[DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS];`
- L247 _private member_ `dtObstacleAvoidanceQuery* m_obstacleQuery;`
- L249 _private member_ `dtProximityGrid* m_grid;`
- L251 _private member_ `dtPolyRef* m_pathResult;`
- L253 _private member_ `dtReal m_ext[3];`
- L254 _private member_ `dtQueryFilter m_filters[DT_CROWD_MAX_FILTERS];`
- L255 _private member_ `dtQueryFilter m_raycastFilter;`
- L257 _private member_ `dtReal m_maxAgentRadius;`
- L260 _private member_ `dtReal m_agentStateCheckInterval;` — [UE] time between attempts to restore agents state
- L263 _private member_ `dtReal m_pathOffsetRadiusMultiplier;` — [UE] radius multiplier for offseting path around corners
- L266 _private member_ `dtReal m_separationDirFilter;` — [UE] separation filter
- L268 _private member_ `int m_maxPathResult;`
- L270 _private member_ `int m_velocitySampleCount;`
- L272 _private member_ `dtNavMeshQuery* m_navquery;`
- L275 _private member_ `bool m_raycastSingleArea;` — [UE] if set, path visibility optimization can't leave current area type
- L277 _private member_ `bool m_keepOffmeshConnections;` — [UE] if set, offmesh connections won't be cut from corridor
- L279 _private member_ `bool m_earlyReachTest;` — [UE] if set, crowd agents will use early reach test
- L281 _private prototype_ `void updateTopologyOptimization(dtCrowdAgent** agents, const int nagents, const dtReal dt);`
- L282 _private prototype_ `void updateMoveRequest(const dtReal dt);`
- L283 _private prototype_ `void checkPathValidity(dtCrowdAgent** agents, const int nagents, const dtReal dt);`
- L285 _private prototype_ `bool requestMoveTargetReplan(const int idx, dtPolyRef ref, const dtReal* pos);`
- L287 _private prototype_ `void purge();`
- L290 _public prototype_ `dtCrowd();`
- L291 _public prototype_ `~dtCrowd();`
- L298 _public prototype_ `bool init(const int maxAgents, const dtReal maxAgentRadius, dtNavMesh* nav);` — Initializes the crowd. @param[in]		maxAgents		The maximum number of agents the crowd can manage. [Limit: >= 1] @param[in]		maxAgentRadius	The maximum radius of any agent that will be added to the crowd. [Limit: > 0] @param[in]		nav				The navigation mesh to use for planning. @return True if the initialization succeeded.
- L305 _public prototype_ `bool initAvoidance(const int maxNeighbors, const int maxWalls, const int maxCustomPatterns);` — [UE] Initializes the avoidance query. @param[in]		maxNeighbors		The maximum number of processed neighbors @param[in]		maxWalls			The maximum number of processed wall segments @param[in]		maxCustomPatterns	The maximum number of custom sampling patterns @return True if the initialization succeeded.
- L310 _public prototype_ `void setObstacleAvoidanceParams(const int idx, const dtObstacleAvoidanceParams* params);` — Sets the shared avoidance configuration for the specified index. @param[in]		idx		The index. [Limits: 0 <= value < #DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS] @param[in]		params	The new configuration.
- L316 _public prototype_ `const dtObstacleAvoidanceParams* getObstacleAvoidanceParams(const int idx) const;` — Gets the shared avoidance configuration for the specified index. @param[in]		idx		The index of the configuration to retreive. [Limits:  0 <= value < #DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS] @return The requested configuration.
- L323 _public prototype_ `void setObstacleAvoidancePattern(int idx, const dtReal* angles, const dtReal* radii, int nsamples);` — [UE] Sets the shared avoidance sampling pattern for the specified index. @param[in]		idx			The index. @param[in]		angles		radians from direction of desired velocity [Count: nsamples] @param[in]		radii		normalized radii (0..1) for each sample [Count: nsamples] @param[in]		nsamples	The number of samples
- L331 _public prototype_ `bool getObstacleAvoidancePattern(int idx, dtReal* angles, dtReal* radii, int* nsamples);` — [UE] Gets the shared avoidance sampling pattern for the specified index. @param[in]		idx			The index. @param[in]		angles		radians from direction of desired velocity [Count: nsamples] @param[in]		radii		normalized radii (0..1) for each sample [Count: nsamples] @param[in]		nsamples	The number of samples @return true if pattern was found
- L336 _public prototype_ `const dtCrowdAgent* getAgent(const int idx);` — Gets the specified agent from the pool. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @return The requested agent.
- L340 _public prototype_ `const int getAgentCount() const;` — The maximum number of agents that can be managed by the object. @return The maximum number of agents.
- L347 _public prototype_ `int addAgent(const dtReal* pos, const dtCrowdAgentParams& params, const dtQueryFilter* filter);` — Adds a new agent to the crowd. @param[in]		pos		The requested position of the agent. [(x, y, z)] @param[in]		params	The configutation of the agent. @param[in]		filter	[UE] query filter used by agent @return The index of the agent in the agent pool. Or -1 if the agent could not be added.
- L352 _public prototype_ `void updateAgentParameters(const int idx, const dtCrowdAgentParams& params);` — Updates the specified agent's configuration. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		params	The new agent configuration.
- L358 _public prototype_ `bool updateAgentFilter(const int idx, const dtQueryFilter* filter);` — [UE] Updates the specified agent's query filter. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		filter	The new filter. @return True if the request was successfully submitted.
- L363 _public prototype_ `void updateAgentState(const int idx, bool repath);` — [UE] Refresh state of agent, used after completing movement through offmesh links @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		repath	If set, agent will invalidate its path
- L367 _public prototype_ `void removeAgent(const int idx);` — Removes the agent from the crowd. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()]
- L374 _public prototype_ `bool requestMoveTarget(const int idx, dtPolyRef ref, const dtReal* pos);` — Submits a new move request for the specified agent. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		ref		The position's polygon reference. @param[in]		pos		The position within the polygon. [(x, y, z)] @return True if the request was successfully submitted.
- L380 _public prototype_ `bool requestMoveVelocity(const int idx, const dtReal* vel);` — Submits a new move request for the specified agent. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		vel		The movement velocity. [(x, y, z)] @return True if the request was successfully submitted.
- L385 _public prototype_ `bool resetMoveTarget(const int idx);` — Resets any request for the specified agent. @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @return True if the request was successfully reseted.
- L389 _public prototype_ `bool setAgentWaiting(const int idx);` — [UE] Switch to waiting state @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()]
- L393 _public prototype_ `bool setAgentBackOnLink(const int idx);` — [UE] Switch to offmesh link state @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()]
- L397 _public prototype_ `bool resetAgentVelocity(const int idx);` — [UE] Resets agent's velocity @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()]
- L403 _public prototype_ `int getActiveAgents(dtCrowdAgent** agents, const int maxAgents);` — Gets the active agents int the agent pool. @param[out]	agents		An array of agent pointers. [(#dtCrowdAgent *) * maxAgents] @param[in]		maxAgents	The size of the crowd agent array. @return The number of agents returned in @p agents.
- L407 _public prototype_ `int cacheActiveAgents();` — Cache list of active agents @return The number of active agents
- L412 _public prototype_ `void update(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — Updates the steering and positions of all agents. @param[in]		dt		The time, in seconds, to update the simulation. [Limit: > 0] @param[out]	debug	A debug object to load with debug information. [Opt]
- L417 _public prototype_ `void updateStepPaths(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: path validity, path cache and path optimizations @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L422 _public prototype_ `void updateStepProximityData(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: neighbors and boundaries @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L427 _public prototype_ `void updateStepNextMovePoint(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: next corner for move, trigger offmesh links @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L432 _public prototype_ `void updateStepSteering(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: steering @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L437 _public prototype_ `void updateStepAvoidance(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: avoidance @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L442 _public prototype_ `void updateStepMove(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: integrate velocities and handle collisions @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L447 _public prototype_ `void updateStepCorridor(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: corridor updates at new position @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L452 _public prototype_ `void updateStepOffMeshAnim(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: offmesh anims @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L457 _public prototype_ `void updateStepOffMeshVelocity(const dtReal dt, dtCrowdAgentDebugInfo* debug);` — [UE] Split update into several smaller components: offmesh link velocity (instead of playing animation) @param[in]		dt		Delta time in seconds @param[in]		nagents	Number of active agents
- L461 _public prototype_ `void setAgentCheckInterval(const dtReal t);` — [UE] Set time between attempts to restore agents state @param[in]		t		Time in seconds
- L469 _public prototype_ `bool setAgentCorridor(const int idx, const dtPolyRef* path, const int npath);` — [UE] Set agent corridor, works only just after requesting move target when agent didn't start any pathfinding operations yet Use with caution! @param[in]		idx		The agent index. [Limits: 0 <= value < #getAgentCount()] @param[in]		path	The path corridor. [(polyRef) * @p npolys] @param[in]		npath	The number of polygons in the path.
- L475 _public prototype_ `void setSingleAreaVisibilityOptimization(bool bEnable);` — [UE] Set visibility optimization to use single area raycasts This will prevent from cutting through polys marked as different area which could have been avoided in corridor's path @param[in]		bEnable	New state of single area raycast mode
- L480 _public prototype_ `void setPruneStartedOffmeshConnections(bool bRemoveFromCorridor);` — [UE] Set offmesh connection pruning This will allow removing offmesh connection poly ref from corridor as soon as offmesh connection anim is triggered (default behavior)
- L483 _public prototype_ `void setEarlyReachTestOptimization(bool bEnable);` — [UE]
- L486 _public prototype_ `void setPathOffsetRadiusMultiplier(dtReal RadiusMultiplier);` — [UE] Set agent radius multiplier for offseting path from corners
- L489 _public prototype_ `void setSeparationFilter(dtReal InFilter);` — [UE] Set separation filter param
- L492 _public prototype_ `bool isOutsideCorridor(const int idx) const;` — [UE] Check if agent moved away from its path corridor
- L497 _public prototype_ `const dtQueryFilter* getFilter(const int idx) const;` — Gets the filter used by the crowd. @param[in]		idx		[UE] The agent index. [Limits: 0 <= value < #getAgentCount()] @return The filter used by the crowd.
- L502 _public prototype_ `dtQueryFilter* getEditableFilter(const int idx);` — Gets the filter used by the crowd. @param[in]		idx		[UE] The agent index. [Limits: 0 <= value < #getAgentCount()] @return The filter used by the crowd.
- L506 _public function_ `const dtReal* getQueryExtents() const` — Gets the search extents [(x, y, z)] used by the crowd for query operations. @return The search extents used by the crowd. [(x, y, z)]
- L510 _public function_ `inline int getVelocitySampleCount() const` — Gets the velocity sample count. @return The velocity sample count.
- L514 _public function_ `const dtProximityGrid* getGrid() const` — Gets the crowd's proximity grid. @return The crowd's proximity grid.
- L518 _public function_ `const dtPathQueue* getPathQueue() const` — Gets the crowd's path request queue. @return The crowd's path request queue.
- L521 _public function_ `const dtNavMeshQuery* getNavMeshQuery() const` — Gets the query object used by the crowd.
- L524 _public function_ `const dtSharedBoundary* getSharedBoundary() const` — Gets shared boundary cache
- L527 _public function_ `dtCrowdAgent** getActiveAgents() const` — Gets all cached active agents
- L529 _public function_ `inline int getNumActiveAgents() const`
- L531 _public function_ `inline int getAgentIndex(const dtCrowdAgent* agent) const`
- L534 _public function_ `const dtCrowdAgentAnimation* getAgentAnims() const` — Gets all agent animations

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURCROWD_H`
- L44 _variable_ `static const int DT_CROWDAGENT_MAX_NEIGHBOURS = 6;` — The maximum number of neighbors that a crowd agent can take into account for steering decisions. @ingroup crowd
- L51 _variable_ `static const int DT_CROWDAGENT_MAX_CORNERS = 4;` — The maximum number of corners a crowd agent will look ahead in the path. This value is used for sizing the crowd agent corner buffers. Due to the behavior of the crowd manager, the actual number of useful corners will be one less than this number. @ingroup crowd
- L58 _variable_ `static const int DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS = 8;` — The maximum number of crowd avoidance configurations supported by the crowd manager. @ingroup crowd @see dtObstacleAvoidanceParams, dtCrowd::setObstacleAvoidanceParams(), dtCrowd::getObstacleAvoidanceParams(), dtCrowdAgentParams::obstacleAvoidanceType
- L61 _variable_ `static const int DT_CROWD_MAX_FILTERS = 16;` — UE: The maximum number of unique filters used by crowd agents
- L540 _prototype_ `dtCrowd* dtAllocCrowd();` — Allocates a crowd object using the Detour allocator. @return A crowd object that is ready for initialization, or null on failure. @ingroup crowd
- L545 _prototype_ `void dtFreeCrowd(dtCrowd* ptr);` — Frees the specified crowd object using the Detour allocator. @param[in]		ptr		A crowd object allocated using #dtAllocCrowd @ingroup crowd

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourLocalBoundary.h` (Public)


#### class `dtLocalBoundary`  
`class dtLocalBoundary`  
_L33-78_
- L35 _private member_ `static const int MAX_LOCAL_SEGS = 8;`
- L36 _private member_ `static const int MAX_LOCAL_POLYS = 16;`
- L45 _private member_ `dtPolyRef m_polys[MAX_LOCAL_POLYS];`
- L46 _private member_ `dtReal m_center[3];`
- L47 _private member_ `Segment m_segs[MAX_LOCAL_SEGS];`
- L48 _private member_ `int m_nsegs;`
- L49 _private member_ `int m_npolys;`
- L51 _private prototype_ `void addSegment(const dtReal dist, const dtReal* seg, int flags = 0);`
- L54 _public prototype_ `dtLocalBoundary();`
- L55 _public prototype_ `~dtLocalBoundary();`
- L57 _public prototype_ `void reset();`
- L60 _public prototype_ `void update(dtPolyRef ref, const dtReal* pos, const dtReal collisionQueryRange, const bool bIgnoreAtEnd, const dtReal* endPos, const dtPolyRef* path, const int npath, const dtReal* moveDir, dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — [UE: new sections: link removal, path corridor, direction]
- L66 _public prototype_ `void update(const dtSharedBoundary* sharedData, const int sharedIdx, const dtReal* pos, const dtReal collisionQueryRange, const bool bIgnoreAtEnd, const dtReal* endPos, const dtPolyRef* path, const int npath, const dtReal* moveDir, dtNavMeshQuery* navquery, const dtQueryFilter* filter);`
- L72 _public prototype_ `bool isValid(dtNavMeshQuery* navquery, const dtQueryFilter* filter);`
- L74 _public function_ `inline const dtReal* getCenter() const`
- L75 _public function_ `inline int getSegmentCount() const`
- L76 _public function_ `inline const dtReal* getSegment(int i) const`
- L77 _public function_ `inline const int getSegmentFlags(int i) const`

#### struct `dtLocalBoundary::Segment`  
`struct Segment`  
_L38-43_
- L40 _public member_ `dtReal s[6];` — Segment start/end
- L41 _public member_ `dtReal d;` — Distance for pruning.
- L42 _public member_ `int flags;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURLOCALBOUNDARY_H`

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourObstacleAvoidance.h` (Public)


#### struct `dtObstacleCircle`  
`struct dtObstacleCircle`  
_L28-35_
- L30 _public member_ `dtReal p[3];` — Position of the obstacle
- L31 _public member_ `dtReal vel[3];` — Velocity of the obstacle
- L32 _public member_ `dtReal dvel[3];` — Velocity of the obstacle
- L33 _public member_ `dtReal rad;` — Radius of the obstacle
- L34 _public member_ `dtReal dp[3], np[3];` — Use for side selection during sampling.
- L34 _public member_ `dtReal dp[3], np[3];` — Use for side selection during sampling.

#### struct `dtObstacleSegment`  
`struct dtObstacleSegment`  
_L37-42_
- L39 _public member_ `dtReal p[3], q[3];` — End points of the obstacle segment
- L39 _public member_ `dtReal p[3], q[3];` — End points of the obstacle segment
- L40 _public member_ `unsigned char touch : 1;`
- L41 _public member_ `unsigned char canIgnore : 1;`

#### class `dtObstacleAvoidanceDebugData`  
`class dtObstacleAvoidanceDebugData`  
_L44-76_
- L47 _public prototype_ `dtObstacleAvoidanceDebugData();`
- L48 _public prototype_ `~dtObstacleAvoidanceDebugData();`
- L50 _public prototype_ `bool init(const int maxSamples);`
- L51 _public prototype_ `void reset();`
- L52 _public prototype_ `void addSample(const dtReal* vel, const dtReal ssize, const dtReal pen, const dtReal vpen, const dtReal vcpen, const dtReal spen, const dtReal tpen);`
- L55 _public prototype_ `void normalizeSamples();`
- L57 _public function_ `inline int getSampleCount() const`
- L58 _public function_ `inline const dtReal* getSampleVelocity(const int i) const`
- L59 _public function_ `inline dtReal getSampleSize(const int i) const`
- L60 _public function_ `inline dtReal getSamplePenalty(const int i) const`
- L61 _public function_ `inline dtReal getSampleDesiredVelocityPenalty(const int i) const`
- L62 _public function_ `inline dtReal getSampleCurrentVelocityPenalty(const int i) const`
- L63 _public function_ `inline dtReal getSamplePreferredSidePenalty(const int i) const`
- L64 _public function_ `inline dtReal getSampleCollisionTimePenalty(const int i) const`
- L67 _private member_ `int m_nsamples;`
- L68 _private member_ `int m_maxSamples;`
- L69 _private member_ `dtReal* m_vel;`
- L70 _private member_ `dtReal* m_ssize;`
- L71 _private member_ `dtReal* m_pen;`
- L72 _private member_ `dtReal* m_vpen;`
- L73 _private member_ `dtReal* m_vcpen;`
- L74 _private member_ `dtReal* m_spen;`
- L75 _private member_ `dtReal* m_tpen;`

#### struct `dtObstacleAvoidanceParams`  
`struct dtObstacleAvoidanceParams`  
_L86-100_
- L88 _public member_ `dtReal velBias;`
- L89 _public member_ `dtReal weightDesVel;`
- L90 _public member_ `dtReal weightCurVel;`
- L91 _public member_ `dtReal weightSide;`
- L92 _public member_ `dtReal weightToi;`
- L93 _public member_ `dtReal horizTime;`
- L94 _public member_ `dtReal sideBiasThreshold;` — Threshold for side selection in prepare(), widens the dead zone for head-on encounters //@UE
- L95 _public member_ `dtReal weightRightBias;` — Weight for preferring right-side passing (reduces head-on oscillation) //@UE
- L96 _public member_ `unsigned char patternIdx;` — [UE] index of custom sampling pattern or 0xff for adaptive
- L97 _public member_ `unsigned char adaptiveDivs;` — adaptive
- L98 _public member_ `unsigned char adaptiveRings;` — adaptive
- L99 _public member_ `unsigned char adaptiveDepth;` — adaptive

#### struct `dtObstacleAvoidancePattern`  
`struct dtObstacleAvoidancePattern`  
_L103-108_
- desc: [UE] custom sampling patterns
- L105 _public member_ `dtReal angles[DT_MAX_CUSTOM_SAMPLES];` — sample's angle (radians) from desired velocity direction
- L106 _public member_ `dtReal radii[DT_MAX_CUSTOM_SAMPLES];` — sample's radius (0...1)
- L107 _public member_ `int nsamples;` — Number of samples

#### class `dtObstacleAvoidanceQuery`  
`class dtObstacleAvoidanceQuery`  
_L110-193_
- L113 _public prototype_ `dtObstacleAvoidanceQuery();`
- L114 _public prototype_ `~dtObstacleAvoidanceQuery();`
- L116 _public prototype_ `bool init(const int maxCircles, const int maxSegments, const int maxCustomPatterns);`
- L118 _public prototype_ `void reset();`
- L120 _public prototype_ `void addCircle(const dtReal* pos, const dtReal rad, const dtReal* vel, const dtReal* dvel);`
- L123 _public prototype_ `void addSegment(const dtReal* p, const dtReal* q, int flags = 0);`
- L126 _public prototype_ `bool setCustomSamplingPattern(int idx, const dtReal* angles, const dtReal* radii, int nsamples);` — [UE] store new sampling pattern
- L129 _public prototype_ `bool getCustomSamplingPattern(int idx, dtReal* angles, dtReal* radii, int* nsamples);` — [UE] get custom sampling pattern
- L132 _public prototype_ `int sampleVelocityCustom(const dtReal* pos, const dtReal rad, const dtReal vmax, const dtReal vmult, const dtReal* vel, const dtReal* dvel, dtReal* nvel, const dtObstacleAvoidanceParams* params, dtObstacleAvoidanceDebugData* debug = 0);` — [UE] sample velocity using custom patterns
- L138 _public prototype_ `int sampleVelocityAdaptive(const dtReal* pos, const dtReal rad, const dtReal vmax, const dtReal vmult, const dtReal* vel, const dtReal* dvel, dtReal* nvel, const dtObstacleAvoidanceParams* params, dtObstacleAvoidanceDebugData* debug = 0);`
- L145 _public function_ `inline int sampleVelocity(const dtReal* pos, const dtReal rad, const dtReal vmax, const dtReal vmult, const dtReal* vel, const dtReal* dvel, dtReal* nvel, const dtObstacleAvoidanceParams* params, dtObstacleAvoidanceDebugData* debug = 0)` — [UE] main sampling function
- L156 _public function_ `inline int getObstacleCircleCount() const`
- L157 _public function_ `const dtObstacleCircle* getObstacleCircle(const int i)`
- L159 _public function_ `inline int getObstacleSegmentCount() const`
- L160 _public function_ `const dtObstacleSegment* getObstacleSegment(const int i)`
- L163 _public function_ `inline int getCustomPatternCount() const` — [UE] sampling pattern count accessors
- L167 _private prototype_ `void prepare(const dtReal* pos, const dtReal* dvel);`
- L169 _private prototype_ `dtReal processSample(const dtReal* vcand, const dtReal cs, const dtReal* pos, const dtReal rad, const dtReal* vel, const dtReal* dvel, dtObstacleAvoidanceDebugData* debug);`
- L174 _private prototype_ `dtObstacleCircle* insertCircle(const dtReal dist);`
- L175 _private prototype_ `dtObstacleSegment* insertSegment(const dtReal dist);`
- L177 _private member_ `dtObstacleAvoidanceParams m_params;`
- L178 _private member_ `dtReal m_invHorizTime;`
- L179 _private member_ `dtReal m_vmax;`
- L180 _private member_ `dtReal m_invVmax;`
- L182 _private member_ `dtObstacleAvoidancePattern* m_customPatterns;`
- L183 _private member_ `dtObstacleCircle* m_circles;`
- L184 _private member_ `dtObstacleSegment* m_segments;`
- L186 _private member_ `int m_maxPatterns;`
- L188 _private member_ `int m_maxCircles;`
- L189 _private member_ `int m_ncircles;`
- L191 _private member_ `int m_maxSegments;`
- L192 _private member_ `int m_nsegments;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOUROBSTACLEAVOIDANCE_H`
- L78 _prototype_ `dtObstacleAvoidanceDebugData* dtAllocObstacleAvoidanceDebugData();`
- L79 _prototype_ `void dtFreeObstacleAvoidanceDebugData(dtObstacleAvoidanceDebugData* ptr);`
- L82 _variable_ `static const int DT_MAX_PATTERN_DIVS = 32;` — Max numver of adaptive divs.
- L83 _variable_ `static const int DT_MAX_PATTERN_RINGS = 4;` — Max number of adaptive rings.
- L84 _variable_ `static const int DT_MAX_CUSTOM_SAMPLES = 16;` — Max number of custom samples in single pattern
- L195 _prototype_ `dtObstacleAvoidanceQuery* dtAllocObstacleAvoidanceQuery();`
- L196 _prototype_ `void dtFreeObstacleAvoidanceQuery(dtObstacleAvoidanceQuery* ptr);`

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourPathCorridor.h` (Public)


#### class `dtPathCorridor`  
`class dtPathCorridor`  
_L35-171_
- desc: Represents a dynamic polygon corridor used to plan agent movement. @ingroup crowd, detour
- L37 _private member_ `dtReal m_pos[3];`
- L38 _private member_ `dtReal m_target[3];`
- L39 _private member_ `dtReal m_prevMovePoint[3];`
- L40 _private member_ `dtReal m_nextExpectedCorner[3];`
- L41 _private member_ `dtReal m_nextExpectedCorner2[3];`
- L42 _private member_ `dtReal m_moveSegAngle;`
- L43 _private member_ `uint32 m_hasNextExpectedCorner : 1;`
- L44 _private member_ `uint32 m_hasNextExpectedCorner2 : 1;`
- L45 _private member_ `uint32 m_isInSkipRange : 1;`
- L46 _private member_ `uint32 m_enableEarlyReach : 1;`
- L48 _private member_ `dtPolyRef* m_path;`
- L49 _private member_ `int m_npath;`
- L50 _private member_ `int m_maxPath;`
- L53 _public prototype_ `dtPathCorridor();`
- L54 _public prototype_ `~dtPathCorridor();`
- L59 _public prototype_ `bool init(const int maxPath);` — Allocates the corridor's path buffer. @param[in]		maxPath		The maximum path size the corridor can handle. @return True if the initialization succeeded.
- L64 _public prototype_ `void reset(dtPolyRef ref, const dtReal* pos);` — Resets the path corridor to the specified position. @param[in]		ref		The polygon reference containing the position. @param[in]		pos		The new position in the corridor. [(x, y, z)]
- L78 _public prototype_ `int findCorners(dtReal* cornerVerts, unsigned char* cornerFlags, dtPolyRef* cornerPolys, const int maxCorners, dtNavMeshQuery* navquery, const dtQueryFilter* filter, dtReal pathOffsetDistance, dtReal earlyReachDistance, bool bAllowEarlyReach = true);` — Finds the corners in the corridor from the position toward the target. (The straightened path.) @param[out]	cornerVerts		The corner vertices. [(x, y, z) * cornerCount] [Size: <= maxCorners] @param[out]	cornerFlags		The flag for each corner. [(flag) * cornerCount] [Size: <= maxCorners] @param[out]	cornerPolys		The polygon reference for each corner. [(polyRef) * cornerCount] [Size: <= @p maxCorners] @param[in]		maxCorners		The maximum number of corners the buffers can hold. @param[in]		navquery		The query object used to build the corridor. @param[in]		filter			The filter to apply to the operation. @param[in]		pathOffsetDistance	[UE] Radius for path offsetting @param[in]		earlyReachDistance	[UE] Radius for early reach detection @param[in]		bAllowEarlyReach [UE] Check if corner skipping for EarlyReachTest is available now @return The number of corners returned in the corner buffers. [0 <= value <= @p maxCorners]
- L88 _public prototype_ `bool optimizePathVisibility(const dtReal* next, const dtReal pathOptimizationRange, dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — Attempts to optimize the path if the specified point is visible from the current position. @param[in]		next					The point to search toward. [(x, y, z]) @param[in]		pathOptimizationRange	The maximum range to search. [Limit: > 0] @param[in]		navquery				The query object used to build the corridor. @param[in]		filter					The filter to apply to the operation.
- L94 _public prototype_ `bool optimizePathTopology(dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — Attempts to optimize the path using a local area search. (Partial replanning.) @param[in]		navquery	The query object used to build the corridor. @param[in]		filter		The filter to apply to the operation.
- L96 _public prototype_ `bool moveOverOffmeshConnection(dtPolyRef offMeshConRef, dtPolyRef* refs, const dtReal* agentPos, dtReal* startPos, dtReal* endPos, dtNavMeshQuery* navquery);`
- L102 _public prototype_ `bool canMoveOverOffmeshConnection(dtPolyRef offMeshConRef, dtPolyRef* refs, const dtReal* agentPos, dtReal* startPos, dtReal* endPos, dtNavMeshQuery* navquery) const;` — [UE] check if offmesh connection can be traversed, but don't modify corridor yet
- L107 _public prototype_ `void pruneOffmeshConenction(dtPolyRef offMeshConRef);` — [UE] remove offmesh connection from corridor
- L109 _public prototype_ `bool fixPathStart(dtPolyRef safeRef, const dtReal* safePos);`
- L111 _public prototype_ `bool trimInvalidPath(dtPolyRef safeRef, const dtReal* safePos, dtNavMeshQuery* navquery, const dtQueryFilter* filter);`
- L118 _public prototype_ `bool isValid(const int maxLookAhead, dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — Checks the current corridor path to see if its polygon references remain valid. @param[in]		maxLookAhead	The number of polygons from the beginning of the corridor to search. @param[in]		navquery		The query object used to build the corridor. @param[in]		filter			The filter to apply to the operation.
- L125 _public prototype_ `bool movePosition(const dtReal* npos, dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — Moves the position from the current location to the desired location, adjusting the corridor as needed to reflect the change. @param[in]		npos		The desired new position. [(x, y, z)] @param[in]		navquery	The query object used to build the corridor. @param[in]		filter		The filter to apply to the operation.
- L132 _public prototype_ `void moveTargetPosition(const dtReal* npos, dtNavMeshQuery* navquery, const dtQueryFilter* filter);` — Moves the target from the curent location to the desired location, adjusting the corridor as needed to reflect the change. @param[in]		npos		The desired new target position. [(x, y, z)] @param[in]		navquery	The query object used to build the corridor. @param[in]		filter		The filter to apply to the operation.
- L138 _public prototype_ `void setCorridor(const dtReal* target, const dtPolyRef* polys, const int npath);` — Loads a new path and target into the corridor. @param[in]		target		The target location within the last polygon of the path. [(x, y, z)] @param[in]		path		The path corridor. [(polyRef) * @p npolys] @param[in]		npath		The number of polygons in the path.
- L142 _public function_ `inline const dtReal* getPos() const` — Gets the current position within the corridor. (In the first polygon.) @return The current position within the corridor.
- L146 _public function_ `inline const dtReal* getTarget() const` — Gets the current target within the corridor. (In the last polygon.) @return The current target within the corridor.
- L150 _public function_ `inline dtPolyRef getFirstPoly() const` — The polygon reference id of the first polygon in the corridor, the polygon containing the position. @return The polygon reference id of the first polygon in the corridor. (Or zero if there is no path.)
- L154 _public function_ `inline dtPolyRef getLastPoly() const` — The polygon reference id of the last polygon in the corridor, the polygon containing the target. @return The polygon reference id of the last polygon in the corridor. (Or zero if there is no path.)
- L158 _public function_ `inline const dtPolyRef* getPath() const` — The corridor's path. @return The corridor's path. [(polyRef) * #getPathCount()]
- L162 _public function_ `inline int getPathCount() const` — The number of polygons in the current corridor path. @return The number of polygons in the current corridor path.
- L164 _public function_ `inline void setEarlyReachTest(bool enable)`
- L166 _public function_ `inline dtReal getSegmentAngle() const`
- L167 _public function_ `inline const dtReal* getNextFixedCorner() const`
- L168 _public function_ `inline const dtReal* getNextFixedCorner2() const`
- L169 _public function_ `inline bool hasNextFixedCorner() const`
- L170 _public function_ `inline bool hasNextFixedCorner2() const`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOUTPATHCORRIDOR_H`
- L173 _prototype_ `int dtMergeCorridorStartMoved(dtPolyRef* path, const int npath, const int maxPath, const dtPolyRef* visited, const int nvisited);`
- L176 _prototype_ `int dtMergeCorridorEndMoved(dtPolyRef* path, const int npath, const int maxPath, const dtPolyRef* visited, const int nvisited);`
- L179 _prototype_ `int dtMergeCorridorStartShortcut(dtPolyRef* path, const int npath, const int maxPath, const dtPolyRef* visited, const int nvisited);`

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourPathQueue.h` (Public)


#### class `dtPathQueue`  
`class dtPathQueue`  
_L40-88_
- L60 _private member_ `static const int MAX_QUEUE = 8;`
- L61 _private member_ `PathQuery m_queue[MAX_QUEUE];`
- L62 _private member_ `dtNavMeshQuery* m_navquery;`
- L63 _private member_ `dtPathQueueRef m_nextHandle;`
- L64 _private member_ `int m_maxPathSize;`
- L65 _private member_ `int m_queueHead;`
- L67 _private prototype_ `void purge();`
- L70 _public prototype_ `dtPathQueue();`
- L71 _public prototype_ `~dtPathQueue();`
- L73 _public prototype_ `bool init(const int maxPathSize, const int maxSearchNodeCount, dtNavMesh* nav);`
- L75 _public prototype_ `void update(const int maxIters);`
- L77 _public prototype_ `dtPathQueueRef request(dtPolyRef startRef, dtPolyRef endRef, const dtReal* startPos, const dtReal* endPos, const dtReal costLimit, const bool requireNavigableEndLocation,`
- L82 _public prototype_ `dtStatus getRequestStatus(dtPathQueueRef ref) const;`
- L84 _public prototype_ `dtStatus getPathResult(dtPathQueueRef ref, dtPolyRef* path, int* pathSize, const int maxPath);`
- L86 _public function_ `inline const dtNavMeshQuery* getNavQuery() const`

#### struct `dtPathQueue::PathQuery`  
`struct PathQuery`  
_L42-58_
- L44 _public member_ `dtPathQueueRef ref;`
- L46 _public member_ `dtReal startPos[3], endPos[3];` — Path find start and end location.
- L46 _public member_ `dtReal startPos[3], endPos[3];` — Path find start and end location.
- L47 _public member_ `dtPolyRef startRef, endRef;`
- L47 _public member_ `dtPolyRef startRef, endRef;`
- L48 _public member_ `dtReal costLimit;`
- L49 _public member_ `unsigned char requireNavigableEndLocation : 1;` — @UE
- L51 _public member_ `dtPolyRef* path;` — Result.
- L52 _public member_ `const dtQueryFilter* filter;`
- L53 _public member_ `TSharedPtr<dtQuerySpecialLinkFilter> linkFilter;`
- L54 _public member_ `int npath;`
- L56 _public member_ `dtStatus status;` — State.
- L57 _public member_ `int keepAlive;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURPATHQUEUE_H`
- L36 _variable_ `static const unsigned int DT_PATHQ_INVALID = 0;`
- L38 _typedef_ `typedef unsigned int dtPathQueueRef;`

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourProximityGrid.h` (Public)


#### class `dtProximityGrid`  
`class dtProximityGrid`  
_L28-68_
- L30 _private member_ `dtReal m_cellSize;`
- L31 _private member_ `dtReal m_invCellSize;`
- L39 _private member_ `Item* m_pool;`
- L40 _private member_ `int m_poolHead;`
- L41 _private member_ `int m_poolSize;`
- L43 _private member_ `unsigned short* m_buckets;`
- L44 _private member_ `int m_bucketsSize;`
- L46 _private member_ `int m_bounds[4];`
- L49 _public prototype_ `dtProximityGrid();`
- L50 _public prototype_ `~dtProximityGrid();`
- L52 _public prototype_ `bool init(const int maxItems, const dtReal cellSize);`
- L54 _public prototype_ `void clear();`
- L56 _public prototype_ `void addItem(const unsigned short id, const dtReal minx, const dtReal miny, const dtReal maxx, const dtReal maxy);`
- L60 _public prototype_ `int queryItems(const dtReal minx, const dtReal miny, const dtReal maxx, const dtReal maxy, unsigned short* ids, const int maxIds) const;`
- L64 _public prototype_ `int getItemCountAt(const int x, const int y) const;`
- L66 _public function_ `inline const int* getBounds() const`
- L67 _public function_ `inline const dtReal getCellSize() const`

#### struct `dtProximityGrid::Item`  
`struct Item`  
_L33-38_
- L35 _public member_ `unsigned short id;`
- L36 _public member_ `short x,y;`
- L36 _public member_ `short x,y;`
- L37 _public member_ `unsigned short next;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURPROXIMITYGRID_H`
- L70 _prototype_ `dtProximityGrid* dtAllocProximityGrid();`
- L71 _prototype_ `void dtFreeProximityGrid(dtProximityGrid* ptr);`

### `Source/Runtime/Navmesh/Public/DetourCrowd/DetourSharedBoundary.h` (Public)


#### struct `dtSharedBoundaryEdge`  
`struct dtSharedBoundaryEdge`  
_L14-20_
- L16 _public member_ `dtReal v0[3];`
- L17 _public member_ `dtReal v1[3];`
- L18 _public member_ `dtPolyRef p0;`
- L19 _public member_ `dtPolyRef p1;`

#### struct `dtSharedBoundaryData`  
`struct dtSharedBoundaryData`  
_L22-34_
- L24 _public member_ `dtReal Center[3];`
- L25 _public member_ `dtReal Radius;`
- L26 _public member_ `dtReal AccessTime;`
- L27 _public member_ `dtQueryFilter* Filter;`
- L28 _public member_ `uint8 SingleAreaId;`
- L30 _public member_ `TArray<dtSharedBoundaryEdge> Edges;`
- L31 _public member_ `TSet<dtPolyRef> Polys;`
- L33 _public function_ `dtSharedBoundaryData() : Filter(nullptr)`

#### class `dtSharedBoundary`  
`class dtSharedBoundary`  
_L36-59_
- L39 _public member_ `TSparseArray<dtSharedBoundaryData> Data;`
- L40 _public member_ `dtQueryFilter SingleAreaFilter;`
- L41 _public member_ `dtReal CurrentTime;`
- L42 _public member_ `dtReal NextClearTime;`
- L44 _public prototype_ `void Initialize();`
- L45 _public prototype_ `void Tick(dtReal DeltaTime);`
- L47 _public prototype_ `int32 FindData(dtReal* Center, dtReal Radius, dtPolyRef ReqPoly, dtQueryFilter* NavFilter) const;`
- L48 _public prototype_ `int32 FindData(dtReal* Center, dtReal Radius, dtPolyRef ReqPoly, uint8 SingleAreaId) const;`
- L50 _public prototype_ `int32 CacheData(dtReal* Center, dtReal Radius, dtPolyRef CenterPoly, dtNavMeshQuery* NavQuery, dtQueryFilter* NavFilter);`
- L51 _public prototype_ `int32 CacheData(dtReal* Center, dtReal Radius, dtPolyRef CenterPoly, dtNavMeshQuery* NavQuery, uint8 SingleAreaId);`
- L53 _public prototype_ `void FindEdges(dtSharedBoundaryData& Data, dtPolyRef CenterPoly, dtNavMeshQuery* NavQuery, dtQueryFilter* NavFilter);`
- L54 _public prototype_ `bool HasSample(int32 Idx) const;`
- L58 _private prototype_ `bool IsValid(int32 Idx, dtNavMeshQuery* NavQuery, dtQueryFilter* NavFilter) const;`

### `Source/Runtime/Navmesh/Public/DetourTileCache/DetourTileCache.h` (Public)


#### enum `dtCompressedTileFlags`  
`enum dtCompressedTileFlags`  
_L37-40_
- desc: Flags for addTile
- L39 _public enumerator_ `DT_COMPRESSEDTILE_FREE_DATA = 0x01` — Navmesh owns the tile memory and should free it.

#### struct `dtCompressedTile`  
`struct dtCompressedTile`  
_L42-52_
- L44 _public member_ `unsigned int salt;` — Counter describing modifications to the tile.
- L45 _public member_ `struct dtTileCacheLayerHeader* header;`
- L46 _public member_ `unsigned char* compressed;`
- L47 _public member_ `int compressedSize;`
- L48 _public member_ `unsigned char* data;`
- L49 _public member_ `int dataSize;`
- L50 _public member_ `unsigned int flags;`
- L51 _public member_ `dtCompressedTile* next;`

#### enum `ObstacleState`  
`enum ObstacleState`  
_L54-60_
- L56 _public enumerator_ `DT_OBSTACLE_EMPTY`
- L57 _public enumerator_ `DT_OBSTACLE_PROCESSING`
- L58 _public enumerator_ `DT_OBSTACLE_PROCESSED`
- L59 _public enumerator_ `DT_OBSTACLE_REMOVING`

#### struct `dtTileCacheObstacle`  
`struct dtTileCacheObstacle`  
_L63-74_
- L65 _public member_ `dtReal pos[3];`
- L66 _public member_ `dtReal radius, height;`
- L66 _public member_ `dtReal radius, height;`
- L67 _public member_ `dtCompressedTileRef touched[DT_MAX_TOUCHED_TILES];`
- L68 _public member_ `dtCompressedTileRef pending[DT_MAX_TOUCHED_TILES];`
- L69 _public member_ `unsigned short salt;`
- L70 _public member_ `unsigned char state;`
- L71 _public member_ `unsigned char ntouched;`
- L72 _public member_ `unsigned char npending;`
- L73 _public member_ `dtTileCacheObstacle* next;`

#### struct `dtTileCacheParams`  
`struct dtTileCacheParams`  
_L76-97_
- L78 _public member_ `dtReal orig[3];`
- L79 _public member_ `dtReal cs, ch;`
- L79 _public member_ `dtReal cs, ch;`
- L80 _public member_ `int width, height;`
- L80 _public member_ `int width, height;`
- L81 _public member_ `dtReal walkableHeight;`
- L82 _public member_ `dtReal walkableRadius;`
- L83 _public member_ `dtReal walkableClimb;`
- L84 _public member_ `dtReal maxSimplificationError;`
- L85 _public member_ `dtReal simplificationElevationRatio;` — UE
- L86 _public member_ `int maxTiles;`
- L87 _public member_ `int maxObstacles;`
- L89 _public member_ `dtReal detailSampleDist;` — @UE BEGIN
- L90 _public member_ `dtReal detailSampleMaxError;`
- L91 _public member_ `int minRegionArea;`
- L92 _public member_ `int mergeRegionArea;`
- L93 _public member_ `int regionChunkSize;`
- L94 _public member_ `int regionPartitioning;`
- L95 _public member_ `bool bMinimizeLinkPoolSize;`

#### struct `dtTileCacheMeshProcess`  
`struct dtTileCacheMeshProcess`  
_L99-112_
- L101 _public prototype_ `virtual void markAreas(struct dtTileCacheLayer* layer, const dtReal* orig, const dtReal cs, const dtReal ch) = 0;`
- L106 _public function_ `virtual void markAreas(struct dtTileCacheLayer* layer, const float* orig, const float cs, const float ch) final` — This function is deprecated use the version that uses dtReal
- L110 _public prototype_ `virtual void process(struct dtNavMeshCreateParams* params, unsigned char* polyAreas, unsigned short* polyFlags) = 0;`

#### class `dtTileCache`  
`class dtTileCache`  
_L115-250_
- L118 _public prototype_ `dtTileCache();`
- L119 _public prototype_ `~dtTileCache();`
- L121 _public function_ `struct dtTileCacheAlloc* getAlloc()`
- L122 _public function_ `struct dtTileCacheCompressor* getCompressor()`
- L123 _public function_ `struct dtTileCacheMeshProcess* getProcessor()`
- L124 _public function_ `const dtTileCacheParams* getParams() const`
- L126 _public function_ `inline int getTileCount() const`
- L127 _public function_ `inline const dtCompressedTile* getTile(const int i) const`
- L129 _public function_ `inline int getObstacleCount() const`
- L130 _public function_ `inline const dtTileCacheObstacle* getObstacle(const int i) const`
- L132 _public prototype_ `const dtTileCacheObstacle* getObstacleByRef(dtObstacleRef ref);`
- L134 _public prototype_ `dtObstacleRef getObstacleRef(const dtTileCacheObstacle* obmin) const;`
- L136 _public prototype_ `dtStatus init(const dtTileCacheParams* params, struct dtTileCacheAlloc* talloc, struct dtTileCacheCompressor* tcomp, struct dtTileCacheMeshProcess* tmproc);`
- L141 _public prototype_ `int getTilesAt(const int tx, const int ty, dtCompressedTileRef* tiles, const int maxTiles) const ;`
- L143 _public prototype_ `dtCompressedTile* getTileAt(const int tx, const int ty, const int tlayer);`
- L144 _public prototype_ `dtCompressedTileRef getTileRef(const dtCompressedTile* tile) const;`
- L145 _public prototype_ `const dtCompressedTile* getTileByRef(dtCompressedTileRef ref) const;`
- L147 _public prototype_ `dtStatus addTile(unsigned char* data, const int dataSize, unsigned char flags, dtCompressedTileRef* result);`
- L149 _public prototype_ `dtStatus removeTile(dtCompressedTileRef ref, unsigned char** data, int* dataSize);`
- L151 _public prototype_ `dtStatus addObstacle(const dtReal* pos, const dtReal radius, const dtReal height, dtObstacleRef* result);`
- L152 _public prototype_ `dtStatus removeObstacle(const dtObstacleRef ref);`
- L154 _public prototype_ `dtStatus queryTiles(const dtReal* bmin, const dtReal* bmax, dtCompressedTileRef* results, int* resultCount, const int maxResults) const;`
- L157 _public prototype_ `dtStatus update(const dtReal , class dtNavMesh* navmesh);`
- L159 _public prototype_ `dtStatus buildNavMeshTilesAt(const int tx, const int ty, class dtNavMesh* navmesh);`
- L161 _public prototype_ `dtStatus buildNavMeshTile(const dtCompressedTileRef ref, class dtNavMesh* navmesh);`
- L163 _public prototype_ `void calcTightTileBounds(const struct dtTileCacheLayerHeader* header, dtReal* bmin, dtReal* bmax) const;`
- L165 _public prototype_ `void getObstacleBounds(const struct dtTileCacheObstacle* ob, dtReal* bmin, dtReal* bmax) const;`
- L169 _public function_ `inline dtCompressedTileRef encodeTileId(unsigned int salt, unsigned int it) const` — Encodes a tile id.
- L175 _public function_ `inline unsigned int decodeTileIdSalt(dtCompressedTileRef ref) const` — Decodes a tile salt.
- L182 _public function_ `inline unsigned int decodeTileIdTile(dtCompressedTileRef ref) const` — Decodes a tile id.
- L189 _public function_ `inline dtObstacleRef encodeObstacleId(unsigned int salt, unsigned int it) const` — Encodes an obstacle id.
- L195 _public function_ `inline unsigned int decodeObstacleIdSalt(dtObstacleRef ref) const` — Decodes an obstacle salt.
- L202 _public function_ `inline unsigned int decodeObstacleIdObstacle(dtObstacleRef ref) const` — Decodes an obstacle id.
- L223 _private member_ `int m_tileLutSize;` — Tile hash lookup size (must be pot).
- L224 _private member_ `int m_tileLutMask;` — Tile hash lookup mask.
- L226 _private member_ `dtCompressedTile** m_posLookup;` — Tile hash lookup.
- L227 _private member_ `dtCompressedTile* m_nextFreeTile;` — Freelist of tiles.
- L228 _private member_ `dtCompressedTile* m_tiles;` — List of tiles.
- L230 _private member_ `unsigned int m_saltBits;` — Number of salt bits in the tile ID.
- L231 _private member_ `unsigned int m_tileBits;` — Number of tile bits in the tile ID.
- L233 _private member_ `dtTileCacheParams m_params;`
- L235 _private member_ `dtTileCacheAlloc* m_talloc;`
- L236 _private member_ `dtTileCacheCompressor* m_tcomp;`
- L237 _private member_ `dtTileCacheMeshProcess* m_tmproc;`
- L239 _private member_ `dtTileCacheObstacle* m_obstacles;`
- L240 _private member_ `dtTileCacheObstacle* m_nextFreeObstacle;`
- L242 _private member_ `static const int MAX_REQUESTS = 64;`
- L243 _private member_ `ObstacleRequest m_reqs[MAX_REQUESTS];`
- L244 _private member_ `int m_nreqs;`
- L246 _private member_ `static const int MAX_UPDATE = 64;`
- L247 _private member_ `dtCompressedTileRef m_update[MAX_UPDATE];`
- L248 _private member_ `int m_nupdate;`

#### enum `dtTileCache::ObstacleRequestAction`  
`enum ObstacleRequestAction`  
_L211-215_
- L213 _public enumerator_ `REQUEST_ADD`
- L214 _public enumerator_ `REQUEST_REMOVE`

#### struct `dtTileCache::ObstacleRequest`  
`struct ObstacleRequest`  
_L217-221_
- L219 _public member_ `int action;`
- L220 _public member_ `dtObstacleRef ref;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURTILECACHE_H`
- L32 _typedef_ `typedef unsigned int dtObstacleRef;`
- L34 _typedef_ `typedef unsigned int dtCompressedTileRef;`
- L62 _variable_ `static const int DT_MAX_TOUCHED_TILES = 8;`
- L252 _prototype_ `dtTileCache* dtAllocTileCache();`
- L253 _prototype_ `void dtFreeTileCache(dtTileCache* tc);`

### `Source/Runtime/Navmesh/Public/DetourTileCache/DetourTileCacheBuilder.h` (Public)


#### struct `dtTileCacheLayerHeader`  
`struct dtTileCacheLayerHeader`  
_L38-47_
- L40 _public member_ `short version;` — Data version
- L41 _public member_ `int tx,ty,tlayer;`
- L41 _public member_ `int tx,ty,tlayer;`
- L41 _public member_ `int tx,ty,tlayer;`
- L42 _public member_ `unsigned short hmin, hmax;` — Height min/max range (@todo: remove)
- L42 _public member_ `unsigned short hmin, hmax;` — Height min/max range (@todo: remove)
- L43 _public member_ `unsigned short width, height;` — Dimension of the layer.
- L43 _public member_ `unsigned short width, height;` — Dimension of the layer.
- L44 _public member_ `unsigned short minx, maxx, miny, maxy;` — Usable sub-region.
- L44 _public member_ `unsigned short minx, maxx, miny, maxy;` — Usable sub-region.
- L44 _public member_ `unsigned short minx, maxx, miny, maxy;` — Usable sub-region.
- L44 _public member_ `unsigned short minx, maxx, miny, maxy;` — Usable sub-region.
- L46 _public member_ `dtReal bmin[3], bmax[3];` — These should be at the bottom, as they are less often used than the rest of the data.
- L46 _public member_ `dtReal bmin[3], bmax[3];` — These should be at the bottom, as they are less often used than the rest of the data.

#### struct `dtTileCacheLayer`  
`struct dtTileCacheLayer`  
_L49-57_
- L51 _public member_ `dtTileCacheLayerHeader* header;`
- L52 _public member_ `unsigned short regCount;` — Region count.
- L53 _public member_ `unsigned short* heights;`
- L54 _public member_ `unsigned char* areas;`
- L55 _public member_ `unsigned char* cons;`
- L56 _public member_ `unsigned short* regs;`

#### struct `dtTileCacheContour`  
`struct dtTileCacheContour`  
_L59-65_
- L61 _public member_ `unsigned short* verts;` — x, y, z, portal direction.
- L62 _public member_ `int nverts;`
- L63 _public member_ `unsigned short reg;`
- L64 _public member_ `unsigned char area;`

#### struct `dtTileCacheContourSet`  
`struct dtTileCacheContourSet`  
_L67-71_
- L69 _public member_ `int nconts;`
- L70 _public member_ `dtTileCacheContour* conts;`

#### struct `dtTileCachePolyMesh`  
`struct dtTileCachePolyMesh`  
_L73-83_
- L75 _public member_ `int nvp;`
- L76 _public member_ `int nverts;` — Number of vertices.
- L77 _public member_ `int npolys;` — Number of polygons.
- L78 _public member_ `unsigned short* verts;` — Vertices of the mesh, 3 elements per vertex.
- L79 _public member_ `unsigned short* polys;` — Polygons of the mesh, nvp*2 elements per polygon.
- L80 _public member_ `unsigned short* flags;` — Per polygon flags.
- L81 _public member_ `unsigned char* areas;` — Area ID of polygons.
- L82 _public member_ `unsigned short* regs;` — Region ID of polygon

#### struct `dtTileCacheClusterSet`  
`struct dtTileCacheClusterSet`  
_L87-94_
- L89 _public member_ `int nclusters;` — The number of clusters
- L90 _public member_ `int nregs;` — The number of regions
- L91 _public member_ `int npolys;` — The number of polys
- L92 _public member_ `unsigned short* regMap;` — Cluster Id for each region [size: #nregs]
- L93 _public member_ `unsigned short* polyMap;` — Cluster Id for each poly [size: #npolys]

#### struct `dtTileCachePolyMeshDetail`  
`struct dtTileCachePolyMeshDetail`  
_L97-105_
- L99 _public member_ `int nmeshes;` — The number of sub-meshes defined by #meshes.
- L100 _public member_ `int nverts;` — The number of vertices in #verts.
- L101 _public member_ `int ntris;` — The number of triangles in #tris.
- L102 _public member_ `unsigned int* meshes;` — The sub-mesh data. [Size: 4*#nmeshes]
- L103 _public member_ `dtReal* verts;` — The mesh vertices. [Size: 3*#nverts]
- L104 _public member_ `unsigned char* tris;` — The mesh triangles. [Size: 4*#ntris]

#### struct `dtTileCacheDistanceField`  
`struct dtTileCacheDistanceField`  
_L107-111_
- L109 _public member_ `unsigned short maxDist;` — Max distance
- L110 _public member_ `unsigned short* data;` — distance for every cell in layer

#### class `dtTileCacheLogContext`  
`class dtTileCacheLogContext`  
_L113-128_
- L119 _public prototype_ `void dtLog(const char* format, ...);` — Logs a message. @param[in]		category	The category of the message. @param[in]		format		The message.
- L127 _protected function_ `virtual void doDtLog(const char* , const int )` — Logs a message. @param[in]		category	The category of the message. @param[in]		msg			The formatted message. @param[in]		len			The length of the formatted message.

#### struct `dtTileCacheAlloc`  
`struct dtTileCacheAlloc`  
_L132-149_
- L134 _public prototype_ `virtual ~dtTileCacheAlloc() = default;`
- L136 _public function_ `virtual void reset()`
- L140 _public function_ `virtual void* alloc(const int size)`
- L145 _public function_ `virtual void free(void* ptr)`

#### struct `dtTileCacheCompressor`  
`struct dtTileCacheCompressor`  
_L151-158_
- L153 _public prototype_ `virtual int maxCompressedSize(const int bufferSize) = 0;`
- L154 _public prototype_ `virtual dtStatus compress(const unsigned char* buffer, const int bufferSize, unsigned char* compressed, const int maxCompressedSize, int* compressedSize) = 0;`
- L156 _public prototype_ `virtual dtStatus decompress(const unsigned char* compressed, const int compressedSize, unsigned char* buffer, const int maxBufferSize, int* bufferSize) = 0;`

#### class `dtFixedArray`  
`template<class T> class dtFixedArray`  
_L161-175_
- desc: @UE BEGIN: moved from DetourTileCacheBuilder.cpp
- L163 _private member_ `dtTileCacheAlloc* m_alloc;`
- L164 _private member_ `T* m_ptr;`
- L165 _private member_ `const int m_size;`
- L166 _private prototype_ `inline T* operator=(T* p);`
- L167 _private prototype_ `inline void operator=(dtFixedArray<T>& p);`
- L168 _private prototype_ `inline dtFixedArray();`
- L170 _public function_ `inline dtFixedArray(dtTileCacheAlloc* a, const int s) : m_alloc(a), m_ptr((T*)a->alloc(sizeof(T)*s)), m_size(s)`
- L171 _public function_ `inline ~dtFixedArray()`
- L172 _public function_ `inline operator T*()`
- L173 _public function_ `inline int size() const`
- L174 _public function_ `inline void set(unsigned char v)`

#### Free symbols / members of external scopes

- L23 _macro_ `#define DETOURTILECACHEBUILDER_H`
- L31 _variable_ `static const int DT_TILECACHE_MAGIC = 'D'<<24 | 'T'<<16 | 'L'<<8 | 'R';` — 'DTLR';
- L32 _variable_ `static const int DT_TILECACHE_VERSION = 1;`
- L34 _variable_ `static const unsigned char DT_TILECACHE_NULL_AREA = 0;`
- L35 _variable_ `static const unsigned char DT_TILECACHE_WALKABLE_AREA = 63;`
- L36 _variable_ `static const unsigned short DT_TILECACHE_NULL_IDX = 0xffff;`
- L177 _function_ `inline int getDirOffsetX(int dir)`
- L183 _function_ `inline int getDirOffsetY(int dir)`
- L190 _prototype_ `dtStatus dtBuildTileCacheLayer(dtTileCacheCompressor* comp, dtTileCacheLayerHeader* header, const unsigned short* heights, const unsigned char* areas, const unsigned char* cons, unsigned char** outData, int* outDataSize);`
- L197 _prototype_ `void dtFreeTileCacheLayer(dtTileCacheAlloc* alloc, dtTileCacheLayer* layer);`
- L199 _prototype_ `dtStatus dtDecompressTileCacheLayer(dtTileCacheAlloc* alloc, dtTileCacheCompressor* comp, const unsigned char* compressed, const int compressedSize, dtTileCacheLayer** layerOut);`
- L203 _prototype_ `dtTileCacheContourSet* dtAllocTileCacheContourSet(dtTileCacheAlloc* alloc);`
- L204 _prototype_ `void dtFreeTileCacheContourSet(dtTileCacheAlloc* alloc, dtTileCacheContourSet* cset);`
- L206 _prototype_ `dtTileCachePolyMesh* dtAllocTileCachePolyMesh(dtTileCacheAlloc* alloc);`
- L207 _prototype_ `void dtFreeTileCachePolyMesh(dtTileCacheAlloc* alloc, dtTileCachePolyMesh* lmesh);`
- L211 _prototype_ `dtTileCacheClusterSet* dtAllocTileCacheClusterSet(dtTileCacheAlloc* alloc);`
- L212 _prototype_ `void dtFreeTileCacheClusterSet(dtTileCacheAlloc* alloc, dtTileCacheClusterSet* clusters);`
- L215 _prototype_ `dtTileCachePolyMeshDetail* dtAllocTileCachePolyMeshDetail(dtTileCacheAlloc* alloc);`
- L216 _prototype_ `void dtFreeTileCachePolyMeshDetail(dtTileCacheAlloc* alloc, dtTileCachePolyMeshDetail* dmesh);`
- L218 _prototype_ `dtTileCacheDistanceField* dtAllocTileCacheDistanceField(dtTileCacheAlloc* alloc);`
- L219 _prototype_ `void dtFreeTileCacheDistanceField(dtTileCacheAlloc* alloc, dtTileCacheDistanceField* dfield);`
- L222 _prototype_ `dtStatus dtMarkCylinderArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* pos, const dtReal radius, const dtReal height, const unsigned char areaId);`
- L226 _prototype_ `dtStatus dtMarkBoxArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* pos, const dtReal* extent, const unsigned char areaId);` — @UE BEGIN: more shapes
- L229 _prototype_ `dtStatus dtMarkConvexArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* verts, const int nverts, const dtReal hmin, const dtReal hmax, const unsigned char areaId);`
- L232 _prototype_ `dtStatus dtReplaceCylinderArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* pos, const dtReal radius, const dtReal height, const unsigned char areaId, const unsigned char filterAreaId);`
- L236 _prototype_ `dtStatus dtReplaceBoxArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* pos, const dtReal* extent, const unsigned char areaId, const unsigned char filterAreaId);`
- L239 _prototype_ `dtStatus dtReplaceConvexArea(dtTileCacheLayer& layer, const dtReal* orig, const dtReal cs, const dtReal ch, const dtReal* verts, const int nverts, const dtReal hmin, const dtReal hmax, const unsigned char areaId, const unsigned char filterAreaId);`
- L243 _prototype_ `dtStatus dtReplaceArea(dtTileCacheLayer& layer, const unsigned char areaId, const unsigned char filterAreaId);`
- L249 _prototype_ `dtStatus dtBuildTileCacheDistanceField(dtTileCacheAlloc* alloc, dtTileCacheLayer& layer, dtTileCacheDistanceField& dfield);` — @UE BEGIN: renamed building regions to dtBuildTileCacheRegionsMonotone, added new region generation
- L251 _prototype_ `dtStatus dtBuildTileCacheRegions(dtTileCacheAlloc* alloc, const int minRegionArea, const int mergeRegionArea, dtTileCacheLayer& layer, dtTileCacheDistanceField dfield);`
- L255 _prototype_ `dtStatus dtBuildTileCacheRegionsMonotone(dtTileCacheAlloc* alloc, const int minRegionArea, const int mergeRegionArea, dtTileCacheLayer& layer);`
- L259 _prototype_ `dtStatus dtBuildTileCacheRegionsChunky(dtTileCacheAlloc* alloc, const int minRegionArea, const int mergeRegionArea, dtTileCacheLayer& layer, int regionChunkSize);`
- L264 _prototype_ `dtStatus dtBuildTileCacheContours(dtTileCacheAlloc* alloc, dtTileCacheLayer& layer, const int walkableClimb, const dtReal maxError, const dtReal simplificationElevationRatio,`
- L277 _prototype_ `dtStatus dtBuildTileCachePolyMesh(dtTileCacheAlloc* alloc, dtTileCacheLogContext* ctx, dtTileCacheContourSet& lcset, dtTileCachePolyMesh& mesh, const int walkableClimb);`
- L284 _prototype_ `dtStatus dtBuildTileCachePolyMeshDetail(dtTileCacheAlloc* alloc, const dtReal cs, const dtReal ch, const dtReal sampleDist, const dtReal sampleMaxError, dtTileCacheLayer& layer, dtTileCachePolyMesh& lmesh, dtTileCachePolyMeshDetail& dmesh);` — @UE BEGIN
- L292 _prototype_ `dtStatus dtBuildTileCacheClusters(dtTileCacheAlloc* alloc, dtTileCacheClusterSet& lclusters, dtTileCachePolyMesh& lmesh);`
- L303 _prototype_ `bool dtTileCacheHeaderSwapEndian(unsigned char* data, const int dataSize);` — Swaps the endianess of the compressed tile data's header (#dtTileCacheLayerHeader). Tile layer data does not need endian swapping as it consist only of bytes. UE: not anymore, there are short types as well now @param[in,out]	data		The tile data array. @param[in]		dataSize	The size of the data array.

### `Source/Runtime/Navmesh/Public/Recast/Recast.h` (Public)


#### enum `rcLogCategory`  
`enum rcLogCategory`  
_L86-91_
- desc: Recast log categories. @see rcContext
- L88 _public enumerator_ `RC_LOG_PROGRESS = 1` — A progress log entry.
- L89 _public enumerator_ `RC_LOG_WARNING` — A warning log entry.
- L90 _public enumerator_ `RC_LOG_ERROR` — An error log entry.

#### enum `rcTimerLabel`  
`enum rcTimerLabel`  
_L95-157_
- desc: Recast performance timer categories. @see rcContext
- L98 _public enumerator_ `RC_TIMER_TOTAL` — The user defined total time of the build.
- L100 _public enumerator_ `RC_TIMER_TEMP` — A user defined build time.
- L102 _public enumerator_ `RC_TIMER_RASTERIZE_TRIANGLES` — The time to rasterize the triangles. (See: #rcRasterizeTriangle)
- L104 _public enumerator_ `RC_TIMER_BUILD_COMPACTHEIGHTFIELD` — The time to build the compact heightfield. (See: #rcBuildCompactHeightfield)
- L106 _public enumerator_ `RC_TIMER_BUILD_CONTOURS` — The total time to build the contours. (See: #rcBuildContours)
- L108 _public enumerator_ `RC_TIMER_BUILD_CONTOURS_TRACE` — The time to trace the boundaries of the contours. (See: #rcBuildContours)
- L110 _public enumerator_ `RC_TIMER_BUILD_CONTOURS_SIMPLIFY` — The time to simplify the contours. (See: #rcBuildContours)
- L112 _public enumerator_ `RC_TIMER_BUILD_CLUSTERS` — The time to link clusters from contours. (See: #rcBuildClusters)
- L114 _public enumerator_ `RC_TIMER_FILTER_BORDER` — The time to filter ledge spans. (See: #rcFilterLedgeSpans)
- L116 _public enumerator_ `RC_TIMER_FILTER_WALKABLE` — The time to filter low height spans. (See: #rcFilterWalkableLowHeightSpans)
- L118 _public enumerator_ `RC_TIMER_MEDIAN_AREA` — The time to apply the median filter. (See: #rcMedianFilterWalkableArea)
- L120 _public enumerator_ `RC_TIMER_FILTER_LOW_OBSTACLES` — The time to filter low obstacles. (See: #rcFilterLowHangingWalkableObstacles)
- L122 _public enumerator_ `RC_TIMER_BUILD_POLYMESH` — The time to build the polygon mesh. (See: #rcBuildPolyMesh)
- L124 _public enumerator_ `RC_TIMER_MERGE_POLYMESH` — The time to merge polygon meshes. (See: #rcMergePolyMeshes)
- L126 _public enumerator_ `RC_TIMER_ERODE_AREA` — The time to erode the walkable area. (See: #rcErodeWalkableArea)
- L128 _public enumerator_ `RC_TIMER_MARK_BOX_AREA` — The time to mark a box area. (See: #rcMarkBoxArea)
- L130 _public enumerator_ `RC_TIMER_MARK_CYLINDER_AREA` — The time to mark a cylinder area. (See: #rcMarkCylinderArea)
- L132 _public enumerator_ `RC_TIMER_MARK_CONVEXPOLY_AREA` — The time to mark a convex polygon area. (See: #rcMarkConvexPolyArea)
- L134 _public enumerator_ `RC_TIMER_BUILD_DISTANCEFIELD` — The total time to build the distance field. (See: #rcBuildDistanceField)
- L136 _public enumerator_ `RC_TIMER_BUILD_DISTANCEFIELD_DIST` — The time to build the distances of the distance field. (See: #rcBuildDistanceField)
- L138 _public enumerator_ `RC_TIMER_BUILD_DISTANCEFIELD_BLUR` — The time to blur the distance field. (See: #rcBuildDistanceField)
- L140 _public enumerator_ `RC_TIMER_BUILD_REGIONS` — The total time to build the regions. (See: #rcBuildRegions, #rcBuildRegionsMonotone)
- L142 _public enumerator_ `RC_TIMER_BUILD_REGIONS_WATERSHED` — The total time to apply the watershed algorithm. (See: #rcBuildRegions)
- L144 _public enumerator_ `RC_TIMER_BUILD_REGIONS_EXPAND` — The time to expand regions while applying the watershed algorithm. (See: #rcBuildRegions)
- L146 _public enumerator_ `RC_TIMER_BUILD_REGIONS_FLOOD` — The time to flood regions while applying the watershed algorithm. (See: #rcBuildRegions)
- L148 _public enumerator_ `RC_TIMER_BUILD_REGIONS_FILTER` — The time to filter out small regions. (See: #rcBuildRegions, #rcBuildRegionsMonotone)
- L150 _public enumerator_ `RC_TIMER_BUILD_LAYERS` — The time to build heightfield layers. (See: #rcBuildHeightfieldLayers)
- L152 _public enumerator_ `RC_TIMER_BUILD_POLYMESHDETAIL` — The time to build the polygon mesh detail. (See: #rcBuildPolyMeshDetail)
- L154 _public enumerator_ `RC_TIMER_MERGE_POLYMESHDETAIL` — The time to merge polygon mesh details. (See: #rcMergePolyMeshDetails)
- L156 _public enumerator_ `RC_MAX_TIMERS` — The maximum number of timers.  (Used for iterating timers.)

#### class `rcContext`  
`class rcContext`  
_L164-237_
- desc: Provides an interface for optional logging and performance tracking of the Recast build process. @ingroup recast
- L170 _public function_ `inline rcContext(bool state = true) : m_logEnabled(state), m_timerEnabled(state)` — Contructor. @param[in]		state	TRUE if the logging and performance timers should be enabled.  [Default: true]
- L171 _public prototype_ `virtual ~rcContext() = default;`
- L175 _public function_ `inline void enableLog(bool state)` — Enables or disables logging. @param[in]		state	TRUE if logging should be enabled.
- L178 _public function_ `inline void resetLog()` — Clears all log entries.
- L183 _public prototype_ `void log(const rcLogCategory category, const char* format, ...);` — Logs a message. @param[in]		category	The category of the message. @param[in]		format		The message.
- L187 _public function_ `inline void enableTimer(bool state)` — Enables or disables the performance timers. @param[in]		state	TRUE if timers should be enabled.
- L190 _public function_ `inline void resetTimers()` — Clears all peformance timers. (Resets all to unused.)
- L194 _public function_ `inline void startTimer(const rcTimerLabel label)` — Starts the specified performance timer. @param	label	The category of timer.
- L198 _public function_ `inline void stopTimer(const rcTimerLabel label)` — Stops the specified performance timer. @param	label	The category of the timer.
- L203 _public function_ `inline int getAccumulatedTime(const rcTimerLabel label) const` — Returns the total accumulated time of the specified performance timer. @param	label	The category of the timer. @return The accumulated time of the timer, or -1 if timers are disabled or the timer has never been started.
- L208 _protected function_ `virtual void doResetLog()` — Clears all log entries.
- L214 _protected function_ `virtual void doLog(const rcLogCategory , const char* , const int )` — Logs a message. @param[in]		category	The category of the message. @param[in]		msg			The formatted message. @param[in]		len			The length of the formatted message.
- L217 _protected function_ `virtual void doResetTimers()` — Clears all timers. (Resets all to unused.)
- L221 _protected function_ `virtual void doStartTimer(const rcTimerLabel )` — Starts the specified performance timer. @param[in]		label	The category of timer.
- L225 _protected function_ `virtual void doStopTimer(const rcTimerLabel )` — Stops the specified performance timer. @param[in]		label	The category of the timer.
- L230 _protected function_ `virtual int doGetAccumulatedTime(const rcTimerLabel ) const` — Returns the total accumulated time of the specified performance timer. @param[in]		label	The category of the timer. @return The accumulated time of the timer, or -1 if timers are disabled or the timer has never been started.
- L233 _protected member_ `bool m_logEnabled;` — True if logging is enabled.
- L236 _protected member_ `bool m_timerEnabled;` — True if the performance timers are enabled.

#### enum `rcRegionPartitioning`  
`enum rcRegionPartitioning`  
_L241-246_
- desc: Region partitioning methods @see rcConfig
- L243 _public enumerator_ `RC_REGION_MONOTONE` — monotone partitioning
- L244 _public enumerator_ `RC_REGION_WATERSHED` — watershed partitioning
- L245 _public enumerator_ `RC_REGION_CHUNKY` — monotone partitioning on small chunks

#### struct `rcBorderSize`  
`struct rcBorderSize`  
_L250-254_
- desc: @UE BEGIN Specifies the size of borders around the heightfield.
- L252 _public member_ `int low;` — Size of the border in the negative direction of the axis [Limit: >= 0] [Units: vx]
- L253 _public member_ `int high;` — Size of the border in the positive direction of the axis [Limit: >= 0] [Units: vx]

#### struct `rcConfig`  
`struct rcConfig`  
_L259-337_
- desc: Specifies a configuration to use when performing Recast builds. @ingroup recast
- L262 _public member_ `int width;` — The width of the field along the x-axis. [Limit: >= 0] [Units: vx]
- L265 _public member_ `int height;` — The height of the field along the z-axis. [Limit: >= 0] [Units: vx]
- L268 _public member_ `int tileSize;` — The width/height size of tile's on the xz-plane. [Limit: >= 0] [Units: vx]
- L271 _public member_ `rcBorderSize borderSize;` — The size of the non-navigable border around the heightfield.
- L274 _public member_ `rcReal cs;` — The xz-plane cell size to use for fields. [Limit: > 0] [Units: wu]
- L277 _public member_ `rcReal ch;` — The y-axis cell size to use for fields. [Limit: > 0] [Units: wu]
- L280 _public member_ `rcReal bmin[3];` — The minimum bounds of the field's AABB. [(x, y, z)] [Units: wu]
- L283 _public member_ `rcReal bmax[3];` — The maximum bounds of the field's AABB. [(x, y, z)] [Units: wu]
- L286 _public member_ `rcReal walkableSlopeAngle;` — The maximum slope that is considered walkable. [Limits: 0 <= value < 90] [Units: Degrees]
- L290 _public member_ `int walkableHeight;` — Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx]
- L293 _public member_ `int walkableClimb;` — Maximum ledge height that is considered to still be traversable. [Limit: >=0] [Units: vx]
- L297 _public member_ `int walkableRadius;` — The distance to erode/shrink the walkable area of the heightfield away from obstructions.  [Limit: >=0] [Units: vx]
- L300 _public member_ `rcReal maxStepFromWalkableSlope;` — Maximum step height in relation to cs and walkableSlopeAngle [Limit: >=0] [Units: wu]
- L303 _public member_ `int maxEdgeLen;` — The maximum allowed length for contour edges along the border of the mesh. [Limit: >=0] [Units: vx]
- L307 _public member_ `rcReal maxSimplificationError;` — The maximum distance a simplified contour's border edges should deviate the original raw contour. [Limit: >=0] [Units: wu]
- L311 _public member_ `rcReal simplificationElevationRatio;` — When simplifying contours, how much is the vertical error taken into account when comparing with MaxSimplificationError. [Limit: >=0] Use 0 to deactivate (Recast behavior), use 1 as a typical value.
- L314 _public member_ `int minRegionArea;` — The minimum number of cells allowed to form isolated island areas. [Limit: >=0] [Units: vx]
- L318 _public member_ `int mergeRegionArea;` — Any regions with a span count smaller than this value will, if possible, be merged with larger regions. [Limit: >=0] [Units: vx]
- L321 _public member_ `int regionChunkSize;` — Size of region chunk [Units: vx]
- L324 _public member_ `int regionPartitioning;` — Region partitioning method: creating poly mesh
- L328 _public member_ `int maxVertsPerPoly;` — The maximum number of vertices allowed for polygons generated during the contour to polygon conversion process. [Limit: >= 3]
- L332 _public member_ `rcReal detailSampleDist;` — Sets the sampling distance to use when generating the detail mesh. (For height detail only.) [Limits: 0 or >= 0.9] [Units: wu]
- L336 _public member_ `rcReal detailSampleMaxError;` — The maximum distance the detail mesh surface should deviate from heightfield data. (For height detail only.) [Limit: >=0] [Units: wu]

#### struct `rcSpanData`  
`struct rcSpanData`  
_L356-361_
- desc: Represents data of span in a heightfield. @see rcHeightfield
- L358 _public member_ `rcSpanUInt smin : RC_SPAN_HEIGHT_BITS;` — The lower limit of the span. [Limit: < #smax]
- L359 _public member_ `rcSpanUInt smax : RC_SPAN_HEIGHT_BITS;` — The upper limit of the span. [Limit: <= #RC_SPAN_MAX_HEIGHT]
- L360 _public member_ `unsigned int area : 6;` — The area id assigned to the span.

#### struct `rcSpanCache`  
`struct rcSpanCache`  
_L363-368_
- L365 _public member_ `unsigned short x;`
- L366 _public member_ `unsigned short y;`
- L367 _public member_ `rcSpanData data;`

#### struct `rcSpan`  
`struct rcSpan`  
_L372-376_
- desc: Represents a span in a heightfield. @see rcHeightfield
- L374 _public member_ `rcSpanData data;` — Span data.
- L375 _public member_ `rcSpan* next;` — The next span higher up in column.

#### struct `rcSpanPool`  
`struct rcSpanPool`  
_L380-384_
- desc: A memory pool used for quick allocation of spans within a heightfield. @see rcHeightfield
- L382 _public member_ `rcSpanPool* next;` — The next span pool.
- L383 _public member_ `rcSpan items[RC_SPANS_PER_POOL];` — Array of spans in the pool.

#### struct `rcRowExt`  
`struct rcRowExt`  
_L390-394_
- L392 _public member_ `int MinCol;`
- L393 _public member_ `int MaxCol;`

#### struct `rcEdgeHit`  
`struct rcEdgeHit`  
_L395-398_
- L397 _public member_ `unsigned char Hits[2];`

#### struct `rcTempSpan`  
`struct rcTempSpan`  
_L399-402_
- L401 _public member_ `int sminmax[2];` — The lower and upper limit of the span. [Limit: < #smax]

#### struct `rcHeightfield`  
`struct rcHeightfield`  
_L407-426_
- desc: A dynamic heightfield representing obstructed space. @ingroup recast
- L409 _public member_ `int width;` — The width of the heightfield. (Along the x-axis in cell units.)
- L410 _public member_ `int height;` — The height of the heightfield. (Along the z-axis in cell units.)
- L411 _public member_ `rcReal bmin[3];` — The minimum bounds in world space. [(x, y, z)]
- L412 _public member_ `rcReal bmax[3];` — The maximum bounds in world space. [(x, y, z)]
- L413 _public member_ `rcReal cs;` — The size of each cell. (On the xz-plane.)
- L414 _public member_ `rcReal ch;` — The height of each cell. (The minimum increment along the y-axis.)
- L415 _public member_ `rcSpan** spans;` — Heightfield of spans (width*height).
- L416 _public member_ `rcSpanPool* pools;` — Linked list of span pools.
- L417 _public member_ `rcSpan* freelist;` — The next free span.
- L420 _public member_ `rcEdgeHit* EdgeHits;` — h + 1 bit flags that indicate what edges cross the z cell boundaries
- L421 _public member_ `rcRowExt* RowExt;` — h structs that give the current x range for this z row
- L422 _public member_ `rcTempSpan* tempspans;` — Heightfield of temp spans (width*height).
- L423 _public member_ `rcSpanData* tempSpanColumns;` — Heightfield of 1 span per cell for vertical column rasterization //UE

#### struct `rcCompactCell`  
`struct rcCompactCell`  
_L429-433_
- desc: Provides information on the content of a cell column in a compact heightfield.
- L431 _public member_ `unsigned int index : 24;` — Index to the first span in the column.
- L432 _public member_ `unsigned int count : 8;` — Number of spans in the column.

#### struct `rcCompactSpan`  
`struct rcCompactSpan`  
_L436-442_
- desc: Represents a span of unobstructed space within a compact heightfield.
- L438 _public member_ `rcSpanUInt y;` — The lower extent of the span. (Measured from the heightfield's base.)
- L439 _public member_ `unsigned int con;` — Packed neighbor connection data.
- L440 _public member_ `unsigned short reg;` — The id of the region the span belongs to. (Or zero if not in a region.)
- L441 _public member_ `unsigned char h;` — The height of the span.  (Measured from #y.)

#### struct `rcCompactHeightfield`  
`struct rcCompactHeightfield`  
_L446-464_
- desc: A compact, static heightfield representing unobstructed space. @ingroup recast
- L448 _public member_ `int width;` — The width of the heightfield. (Along the x-axis in cell units.)
- L449 _public member_ `int height;` — The height of the heightfield. (Along the z-axis in cell units.)
- L450 _public member_ `int spanCount;` — The number of spans in the heightfield.
- L451 _public member_ `int walkableHeight;` — The walkable height used during the build of the field.  (See: rcConfig::walkableHeight)
- L452 _public member_ `int walkableClimb;` — The walkable climb used during the build of the field. (See: rcConfig::walkableClimb)
- L453 _public member_ `rcBorderSize borderSize;` — The AABB border size used during the build of the field. (See: rcConfig::borderSize)		//@UE
- L454 _public member_ `unsigned short maxDistance;` — The maximum distance value of any span within the field.
- L455 _public member_ `unsigned short maxRegions;` — The maximum region id of any span within the field.
- L456 _public member_ `rcReal bmin[3];` — The minimum bounds in world space. [(x, y, z)]
- L457 _public member_ `rcReal bmax[3];` — The maximum bounds in world space. [(x, y, z)]
- L458 _public member_ `rcReal cs;` — The size of each cell. (On the xz-plane.)
- L459 _public member_ `rcReal ch;` — The height of each cell. (The minimum increment along the y-axis.)
- L460 _public member_ `rcCompactCell* cells;` — Array of cells. [Size: #width*#height]
- L461 _public member_ `rcCompactSpan* spans;` — Array of spans. [Size: #spanCount]
- L462 _public member_ `unsigned short* dist;` — Array containing border distance data. [Size: #spanCount]
- L463 _public member_ `unsigned char* areas;` — Array containing area id data. [Size: #spanCount]

#### struct `rcHeightfieldLayer`  
`struct rcHeightfieldLayer`  
_L468-485_
- desc: Represents a heightfield layer within a layer set. @see rcHeightfieldLayerSet
- L470 _public member_ `rcReal bmin[3];` — The minimum bounds in world space. [(x, y, z)]
- L471 _public member_ `rcReal bmax[3];` — The maximum bounds in world space. [(x, y, z)]
- L472 _public member_ `rcReal cs;` — The size of each cell. (On the xz-plane.)
- L473 _public member_ `rcReal ch;` — The height of each cell. (The minimum increment along the y-axis.)
- L474 _public member_ `int width;` — The width of the heightfield. (Along the x-axis in cell units.)
- L475 _public member_ `int height;` — The height of the heightfield. (Along the z-axis in cell units.)
- L476 _public member_ `int minx;` — The minimum x-bounds of usable data.
- L477 _public member_ `int maxx;` — The maximum x-bounds of usable data.
- L478 _public member_ `int miny;` — The minimum y-bounds of usable data. (Along the z-axis.)
- L479 _public member_ `int maxy;` — The maximum y-bounds of usable data. (Along the z-axis.)
- L480 _public member_ `int hmin;` — The minimum height bounds of usable data. (Along the y-axis.)	// @todo: remove
- L481 _public member_ `int hmax;` — The maximum height bounds of usable data. (Along the y-axis.)
- L482 _public member_ `unsigned short* heights;` — The heightfield. [Size: (width - borderSize*2) * (h - borderSize*2)]
- L483 _public member_ `unsigned char* areas;` — Area ids. [Size: Same as #heights]
- L484 _public member_ `unsigned char* cons;` — Packed neighbor connection information. [Size: Same as #heights]

#### struct `rcHeightfieldLayerSet`  
`struct rcHeightfieldLayerSet`  
_L490-494_
- desc: Represents a set of heightfield layers. @ingroup recast @see rcAllocHeightfieldLayerSet, rcFreeHeightfieldLayerSet
- L492 _public member_ `rcHeightfieldLayer* layers;` — The layers in the set. [Size: #nlayers]
- L493 _public member_ `int nlayers;` — The number of layers in the set.

#### struct `rcContour`  
`struct rcContour`  
_L497-505_
- desc: Represents a simple, non-overlapping contour in field space.
- L499 _public member_ `int* verts;` — Simplified contour vertex and connection data. [Size: 4 * #nverts]
- L500 _public member_ `int nverts;` — The number of vertices in the simplified contour.
- L501 _public member_ `int* rverts;` — Raw contour vertex and connection data. [Size: 4 * #nrverts]
- L502 _public member_ `int nrverts;` — The number of vertices in the raw contour.
- L503 _public member_ `unsigned short reg;` — The region id of the contour.
- L504 _public member_ `unsigned char area;` — The area id of the contour.

#### struct `rcContourSet`  
`struct rcContourSet`  
_L509-520_
- desc: Represents a group of related contours. @ingroup recast
- L511 _public member_ `rcContour* conts;` — An array of the contours in the set. [Size: #nconts]
- L512 _public member_ `int nconts;` — The number of contours in the set.
- L513 _public member_ `rcReal bmin[3];` — The minimum bounds in world space. [(x, y, z)]
- L514 _public member_ `rcReal bmax[3];` — The maximum bounds in world space. [(x, y, z)]
- L515 _public member_ `rcReal cs;` — The size of each cell. (On the xz-plane.)
- L516 _public member_ `rcReal ch;` — The height of each cell. (The minimum increment along the y-axis.)
- L517 _public member_ `int width;` — The width of the set. (Along the x-axis in cell units.)
- L518 _public member_ `int height;` — The height of the set. (Along the z-axis in cell units.)
- L519 _public member_ `rcBorderSize borderSize;` — The AABB border size used to generate the source data from which the contours were derived.		//@UE

#### struct `rcClusterSet`  
`struct rcClusterSet`  
_L526-532_
- desc: Represents group of clusters @ingroup recast
- L528 _public member_ `int nclusters;` — The number of clusters
- L529 _public member_ `rcReal* center;` — Center points per clusters [Size: 3 * #nclusters]
- L530 _public member_ `unsigned short* nlinks;` — Number of links per cluster [Size: #nclusters]
- L531 _public member_ `unsigned short* links;` — Neighbor Ids per cluster [Size: sum of #nlinks]

#### struct `rcPolyMesh`  
`struct rcPolyMesh`  
_L538-554_
- desc: Represents a polygon mesh suitable for use in building a navigation mesh. @ingroup recast
- L540 _public member_ `unsigned short* verts;` — The mesh vertices. [Form: (x, y, z) * #nverts]
- L541 _public member_ `unsigned short* polys;` — Polygon and neighbor data. [Length: #maxpolys * 2 * #nvp]
- L542 _public member_ `unsigned short* regs;` — The region id assigned to each polygon. [Length: #maxpolys]
- L543 _public member_ `unsigned short* flags;` — The user defined flags for each polygon. [Length: #maxpolys]
- L544 _public member_ `unsigned char* areas;` — The area id assigned to each polygon. [Length: #maxpolys]
- L545 _public member_ `int nverts;` — The number of vertices.
- L546 _public member_ `int npolys;` — The number of polygons.
- L547 _public member_ `int maxpolys;` — The number of allocated polygons.
- L548 _public member_ `int nvp;` — The maximum number of vertices per polygon.
- L549 _public member_ `rcReal bmin[3];` — The minimum bounds in world space. [(x, y, z)]
- L550 _public member_ `rcReal bmax[3];` — The maximum bounds in world space. [(x, y, z)]
- L551 _public member_ `rcReal cs;` — The size of each cell. (On the xz-plane.)
- L552 _public member_ `rcReal ch;` — The height of each cell. (The minimum increment along the y-axis.)
- L553 _public member_ `rcBorderSize borderSize;` — The AABB border size used to generate the source data from which the mesh was derived.		//@UE

#### struct `rcPolyMeshDetail`  
`struct rcPolyMeshDetail`  
_L559-567_
- desc: Contains triangle meshes that represent detailed height data associated with the polygons in its associated polygon mesh object. @ingroup recast
- L561 _public member_ `unsigned int* meshes;` — The sub-mesh data. [Size: 4*#nmeshes]
- L562 _public member_ `rcReal* verts;` — The mesh vertices. [Size: 3*#nverts]
- L563 _public member_ `unsigned char* tris;` — The mesh triangles. [Size: 4*#ntris]
- L564 _public member_ `int nmeshes;` — The number of sub-meshes defined by #meshes.
- L565 _public member_ `int nverts;` — The number of vertices in #verts.
- L566 _public member_ `int ntris;` — The number of triangles in #tris.

#### enum `rcBuildContoursFlags`  
`enum rcBuildContoursFlags`  
_L689-693_
- desc: Contour build flags. @see rcBuildContours
- L691 _public enumerator_ `RC_CONTOUR_TESS_WALL_EDGES = 0x01` — Tessellate solid (impassable) edges during contour simplification.
- L692 _public enumerator_ `RC_CONTOUR_TESS_AREA_EDGES = 0x02` — Tessellate edges between areas during contour simplification.

#### enum `rcFilterLowAreaFlags`  
`enum rcFilterLowAreaFlags`  
_L696-700_
- desc: UE
- L698 _public enumerator_ `RC_LOW_FILTER_SEED_SPANS = 0x01` — initial seeding on spans
- L699 _public enumerator_ `RC_LOW_FILTER_POST_PROCESS = 0x02` — additional filtering at the end

#### enum `rcRasterizationFlags`  
`enum rcRasterizationFlags`  
_L703-707_
- desc: UE
- L705 _public enumerator_ `RC_PROJECT_TO_BOTTOM = 1 << 0` — Will create spans from the triangle surface to the bottom of the heightfield
- L706 _public enumerator_ `RC_RASTERIZE_AS_FILLED_CONVEX = 1 << 1` — Will rasterize all the triangles of a list into a single span for each (x,z) and then add all those spans in the heightfield //UE

#### enum `rcNeighborSlopeFilterMode`  
`enum rcNeighborSlopeFilterMode`  
_L710-715_
- desc: UE
- L712 _public enumerator_ `RC_SLOPE_FILTER_RECAST` — Use walkableClimb value to filter
- L713 _public enumerator_ `RC_SLOPE_FILTER_NONE` — Skip slope filtering
- L714 _public enumerator_ `RC_SLOPE_FILTER_USE_HEIGHT_FROM_WALKABLE_SLOPE` — Use maximum step height computed from walkableSlopeAngle

#### Free symbols / members of external scopes

- L23 _macro_ `#define RECAST_H`
- L31 _variable_ `static const rcReal RC_PI = 3.14159265358979323846;` — @UE BEGIN Adding support for LWCoords. The value of PI used by Recast.
- L33 _function_ `inline float rcSin(float x)`
- L38 _function_ `inline double rcSin(double x)`
- L43 _function_ `inline float rcCos(float x)`
- L48 _function_ `inline double rcCos(double x)`
- L53 _function_ `inline float rcFloor(float x)`
- L58 _function_ `inline double rcFloor(double x)`
- L63 _function_ `inline float rcCeil(float x)`
- L68 _function_ `inline double rcCeil(double x)`
- L73 _function_ `inline float rcAbs(float x)`
- L78 _function_ `inline double rcAbs(double x)`
- L159 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRecast, Log, All);`
- L343 _variable_ `static constexpr int RC_SPAN_HEIGHT_BITS = 29;` — Defines the number of bits allocated to rcSpanData::smin and rcSpanData::smax. Using 29 bits increases the size of rcSpanData to 8 bytes but it does not impact the size of rcSpan since padding was already present. It also increases the size of rcSpanCache to 12 bytes. Size of rcTempSpan also increases to 8 bytes.
- L346 _variable_ `static const int RC_SPAN_MAX_HEIGHT = (1<<RC_SPAN_HEIGHT_BITS)-1;` — Defines the maximum value for rcSpanData::smin and rcSpanData::smax.
- L350 _variable_ `static const int RC_SPANS_PER_POOL = 2048;` — The number of spans allocated per span spool. @see rcSpanPool
- L352 _typedef_ `typedef unsigned int rcSpanUInt;`
- L387 _macro_ `#define EPIC_ADDITION_USE_NEW_RECAST_RASTERIZER 1`
- L578 _prototype_ `rcHeightfield* rcAllocHeightfield();` — Allocates a heightfield object using the Recast allocator. @return A heightfield that is ready for initialization, or null on failure. @ingroup recast @see rcCreateHeightfield, rcFreeHeightField
- L584 _prototype_ `void rcFreeHeightField(rcHeightfield* hf);` — Frees the specified heightfield object using the Recast allocator. @param[in]		hf	A heightfield allocated using #rcAllocHeightfield @ingroup recast @see rcAllocHeightfield
- L590 _prototype_ `rcCompactHeightfield* rcAllocCompactHeightfield();` — Allocates a compact heightfield object using the Recast allocator. @return A compact heightfield that is ready for initialization, or null on failure. @ingroup recast @see rcBuildCompactHeightfield, rcFreeCompactHeightfield
- L596 _prototype_ `void rcFreeCompactHeightfield(rcCompactHeightfield* chf);` — Frees the specified compact heightfield object using the Recast allocator. @param[in]		chf		A compact heightfield allocated using #rcAllocCompactHeightfield @ingroup recast @see rcAllocCompactHeightfield
- L602 _prototype_ `rcHeightfieldLayerSet* rcAllocHeightfieldLayerSet();` — Allocates a heightfield layer set using the Recast allocator. @return A heightfield layer set that is ready for initialization, or null on failure. @ingroup recast @see rcBuildHeightfieldLayers, rcFreeHeightfieldLayerSet
- L608 _prototype_ `void rcFreeHeightfieldLayerSet(rcHeightfieldLayerSet* lset);` — Frees the specified heightfield layer set using the Recast allocator. @param[in]		lset	A heightfield layer set allocated using #rcAllocHeightfieldLayerSet @ingroup recast @see rcAllocHeightfieldLayerSet
- L614 _prototype_ `rcContourSet* rcAllocContourSet();` — Allocates a contour set object using the Recast allocator. @return A contour set that is ready for initialization, or null on failure. @ingroup recast @see rcBuildContours, rcFreeContourSet
- L620 _prototype_ `void rcFreeContourSet(rcContourSet* cset);` — Frees the specified contour set using the Recast allocator. @param[in]		cset	A contour set allocated using #rcAllocContourSet @ingroup recast @see rcAllocContourSet
- L628 _prototype_ `rcClusterSet* rcAllocClusterSet();` — Allocates a cluster set object using the Recast allocator. @return A cluster set that is ready for initialization, or null on failure. @ingroup recast @see rcBuildClusters, rcFreeClusterSet
- L634 _prototype_ `void rcFreeClusterSet(rcClusterSet* clset);` — Frees the specified cluster set using the Recast allocator. @param[in]		clset	A cluster set allocated using #rcAllocClusterSet @ingroup recast @see rcAllocClusterSet
- L642 _prototype_ `rcPolyMesh* rcAllocPolyMesh();` — Allocates a polygon mesh object using the Recast allocator. @return A polygon mesh that is ready for initialization, or null on failure. @ingroup recast @see rcBuildPolyMesh, rcFreePolyMesh
- L648 _prototype_ `void rcFreePolyMesh(rcPolyMesh* pmesh);` — Frees the specified polygon mesh using the Recast allocator. @param[in]		pmesh	A polygon mesh allocated using #rcAllocPolyMesh @ingroup recast @see rcAllocPolyMesh
- L654 _prototype_ `rcPolyMeshDetail* rcAllocPolyMeshDetail();` — Allocates a detail mesh object using the Recast allocator. @return A detail mesh that is ready for initialization, or null on failure. @ingroup recast @see rcBuildPolyMeshDetail, rcFreePolyMeshDetail
- L660 _prototype_ `void rcFreePolyMeshDetail(rcPolyMeshDetail* dmesh);` — Frees the specified detail mesh using the Recast allocator. @param[in]		dmesh	A detail mesh allocated using #rcAllocPolyMeshDetail @ingroup recast @see rcAllocPolyMeshDetail
- L669 _variable_ `static const unsigned short RC_BORDER_REG = 0x8000;` — Heighfield border flag. If a heightfield region ID has this bit set, then the region is a border region and its spans are considered unwalkable. (Used during the region and contour build process.) @see rcCompactSpan::reg
- L678 _variable_ `static const int RC_BORDER_VERTEX = 0x10000;` — Border vertex flag. If a region ID has this bit set, then the associated element lies on a tile border. If a contour vertex's region ID has this bit set, the vertex will later be removed in order to match the segments and vertices at tile boundaries. (Used during the build process.) @see rcCompactSpan::reg, #rcContour::verts, #rcContour::rverts
- L685 _variable_ `static const int RC_AREA_BORDER = 0x20000;` — Area border flag. If a region ID has this bit set, then the associated element lies on the border of an area. (Used during the region and contour build process.) @see rcCompactSpan::reg, #rcContour::verts, #rcContour::rverts
- L721 _variable_ `static const int RC_CONTOUR_REG_MASK = 0xffff;` — Applied to the region id field of contour vertices in order to extract the region id. The region id field of a vertex may have several flags applied to it.  So the fields value can't be used directly. @see rcContour::verts, rcContour::rverts
- L726 _variable_ `static const unsigned short RC_MESH_NULL_IDX = 0xffff;` — An value which indicates an invalid index within a mesh. @note This does not necessarily indicate an error. @see rcPolyMesh::polys
- L731 _variable_ `static const unsigned char RC_NULL_AREA = 0;` — Represents the null area. When a data element is given this value it is considered to no longer be assigned to a usable area.  (E.g. It is unwalkable.)
- L736 _variable_ `static const unsigned char RC_WALKABLE_AREA = 63;` — The default area id used to indicate a walkable polygon. This is also the maximum allowed area id, and the only non-null area id recognized by some steps in the build process.
- L740 _variable_ `static const int RC_NOT_CONNECTED = 0xff;` — The value returned by #rcGetCon if the specified direction is not connected to another span. (Has no neighbor.)
- L748 _function_ `template<class T> inline void rcSwap(T& a, T& b)` — Swaps the values of the two parameters. @param[in,out]	a	Value A @param[in,out]	b	Value B
- L754 _function_ `template<class T> inline T rcMin(T a, T b)` — Returns the minimum of two values. @param[in]		a	Value A @param[in]		b	Value B @return The minimum of the two values.
- L756 _function_ `inline rcReal rcMin(rcReal a, rcReal b)` — When used with a mixture of rcReal and other types (in practice floats and doubles mixed here) this overridden function will be preferred by the compiler.
- L762 _function_ `template<class T> inline T rcMax(T a, T b)` — Returns the maximum of two values. @param[in]		a	Value A @param[in]		b	Value B @return The maximum of the two values.
- L764 _function_ `inline rcReal rcMax(rcReal a, rcReal b)` — When used with a mixture of rcReal and other types (in practice floats and doubles mixed here) this overridden function will be preferred by the compiler.
- L769 _function_ `template<class T> inline T rcAbs(T a)` — Returns the absolute value. @param[in]		a	The value. @return The absolute value of the specified value.
- L774 _function_ `template<class T> inline T rcSqr(T a)` — Returns the square of the value. @param[in]		a	The value. @return The square of the value.
- L781 _function_ `template<class T> inline T rcClamp(T v, T mn, T mx)` — Clamps the value to the specified range. @param[in]		v	The value to clamp. @param[in]		mn	The minimum permitted return value. @param[in]		mx	The maximum permitted return value. @return The value, clamped to the specified range.
- L783 _function_ `inline rcReal rcClamp(rcReal v, rcReal mn, rcReal mx)` — When used with a mixture of rcReal and other types (in practice floats and doubles mixed here) this overridden function will be preferred by the compiler.
- L788 _prototype_ `rcReal rcSqrt(rcReal x);` — Returns the square root of the value. @param[in]		x	The value. @return The square root of the vlaue.
- L798 _function_ `inline void rcVcross(rcReal* dest, const rcReal* v1, const rcReal* v2)` — Derives the cross product of two vectors. (@p v1 x @p v2) @param[out]	dest	The cross product. [(x, y, z)] @param[in]		v1		A Vector [(x, y, z)] @param[in]		v2		A vector [(x, y, z)]
- L809 _function_ `inline rcReal rcVdot(const rcReal* v1, const rcReal* v2)` — Derives the dot product of two vectors. (@p v1 . @p v2) @param[in]		v1	A Vector [(x, y, z)] @param[in]		v2	A vector [(x, y, z)] @return The dot product.
- L819 _function_ `inline void rcVmad(rcReal* dest, const rcReal* v1, const rcReal* v2, const rcReal s)` — Performs a scaled vector addition. (@p v1 + (@p v2 * @p s)) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to scale and add to @p v1. [(x, y, z)] @param[in]		s		The amount to scale @p v2 by before adding to @p v1.
- L830 _function_ `inline void rcVadd(rcReal* dest, const rcReal* v1, const rcReal* v2)` — Performs a vector addition. (@p v1 + @p v2) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to add to @p v1. [(x, y, z)]
- L841 _function_ `inline void rcVsub(rcReal* dest, const rcReal* v1, const rcReal* v2)` — Performs a vector subtraction. (@p v1 - @p v2) @param[out]	dest	The result vector. [(x, y, z)] @param[in]		v1		The base vector. [(x, y, z)] @param[in]		v2		The vector to subtract from @p v1. [(x, y, z)]
- L851 _function_ `inline void rcVmin(rcReal* mn, const rcReal* v)` — Selects the minimum value of each element from the specified vectors. @param[in,out]	mn	A vector.  (Will be updated with the result.) [(x, y, z)] @param[in]		v	A vector. [(x, y, z)]
- L861 _function_ `inline void rcVmax(rcReal* mx, const rcReal* v)` — Selects the maximum value of each element from the specified vectors. @param[in,out]	mx	A vector.  (Will be updated with the result.) [(x, y, z)] @param[in]		v	A vector. [(x, y, z)]
- L871 _function_ `inline void rcVcopy(rcReal* dest, const rcReal* v)` — Performs a vector copy. @param[out]	dest	The result. [(x, y, z)] @param[in]		v		The vector to copy. [(x, y, z)]
- L882 _function_ `inline rcReal rcVdist(const rcReal* v1, const rcReal* v2)` — Returns the distance between two points. @param[in]		v1	A point. [(x, y, z)] @param[in]		v2	A point. [(x, y, z)] @return The distance between the two points.
- L894 _function_ `inline rcReal rcVdistSqr(const rcReal* v1, const rcReal* v2)` — Returns the square of the distance between two points. @param[in]		v1	A point. [(x, y, z)] @param[in]		v2	A point. [(x, y, z)] @return The square of the distance between the two points.
- L904 _function_ `inline void rcVnormalize(rcReal* v)` — Normalizes the vector. @param[in,out]	v	The vector to normalize. [(x, y, z)]
- L920 _prototype_ `void rcCalcTriNormals(const rcReal* verts, const int nv, const int* tris, const int nt, rcReal* norms);` — @UE BEGIN Calculates the normals of each triangles in an array @ingroup recast @param[in]		verts	An array of vertices. [(x, y, z) * @p nv] @param[in]		nv		The number of vertices in the @p verts array. @param[in]		tris	The triangle vertex indices. [(vertA, vertB, vertC) * @p nt] @param[in]		nt		The number of triangles. @param[out]	norms	The normal vector of each triangle. [(x, y, z) * @p nt]
- L934 _prototype_ `void rcCalcBounds(const rcReal* verts, int nv, rcReal* bmin, rcReal* bmax);` — Calculates the bounding box of an array of vertices. @ingroup recast @param[in]		verts	An array of vertices. [(x, y, z) * @p nv] @param[in]		nv		The number of vertices in the @p verts array. @param[out]	bmin	The minimum bounds of the AABB. [(x, y, z)] [Units: wu] @param[out]	bmax	The maximum bounds of the AABB. [(x, y, z)] [Units: wu]
- L943 _prototype_ `void rcCalcGridSize(const rcReal* bmin, const rcReal* bmax, rcReal cs, int* w, int* h);` — Calculates the grid size based on the bounding box and grid cell size. @ingroup recast @param[in]		bmin	The minimum bounds of the AABB. [(x, y, z)] [Units: wu] @param[in]		bmax	The maximum bounds of the AABB. [(x, y, z)] [Units: wu] @param[in]		cs		The xz-plane cell size. [Limit: > 0] [Units: wu] @param[out]	w		The width along the x-axis. [Limit: >= 0] [Units: vx] @param[out]	h		The height along the z-axis. [Limit: >= 0] [Units: vx]
- L956 _prototype_ `bool rcCreateHeightfield(rcContext* ctx, rcHeightfield& hf, int width, int height, const rcReal* bmin, const rcReal* bmax, rcReal cs, rcReal ch, bool bAllocateTempSpanColumns = false);` — Initializes a new heightfield. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in,out]	hf		The allocated heightfield to initialize. @param[in]		width	The width of the field along the x-axis. [Limit: >= 0] [Units: vx] @param[in]		height	The height of the field along the z-axis. [Limit: >= 0] [Units: vx] @param[in]		bmin	The minimum bounds of the field's AABB. [(x, y, z)] [Units: wu] @param[in]		bmax	The maximum bounds of the field's AABB. [(x, y, z)] [Units: wu] @param[in]		cs		The xz-plane cell size to use for the field. [Limit: > 0] [Units: wu] @param[in]		ch		The y-axis cell size to use for field. [Limit: > 0] [Units: wu] @param[in]		bAllocateTempSpanColumns	Indicate if we need to allocate the heightfield's tempSpanColumns.
- L967 _prototype_ `void rcResetHeightfield(rcHeightfield& hf);` — Resets all spans of heightfield. @ingroup recast @param[in,out]	hf		The heightfield to reset. @param[in]		bmin	The minimum bounds of the field's AABB. [(x, y, z)] [Units: wu] @param[in]		bmax	The maximum bounds of the field's AABB. [(x, y, z)] [Units: wu] @param[in,out]	hf		The heightfield toreset.
- L980 _prototype_ `void rcMarkWalkableTriangles(rcContext* ctx, const rcReal walkableSlopeAngle, const rcReal* verts, int nv, const int* tris, int nt, unsigned char* areas);` — Sets the area id of all triangles with a slope below the specified value to #RC_WALKABLE_AREA. @ingroup recast @param[in,out]	ctx					The build context to use during the operation. @param[in]		walkableSlopeAngle	The maximum slope that is considered walkable. [Limits: 0 <= value < 90] [Units: Degrees] @param[in]		verts				The vertices. [(x, y, z) * @p nv] @param[in]		nv					The number of vertices. @param[in]		tris				The triangle vertex indices. [(vertA, vertB, vertC) * @p nt] @param[in]		nt					The number of triangles. @param[out]	areas				The triangle area ids. [Length: >= @p nt]
- L994 _prototype_ `void rcMarkWalkableTrianglesCos(rcContext* ctx, const rcReal walkableSlopeCos, const rcReal* verts, int nv, const int* tris, int nt, unsigned char* areas);` — Sets the area id of all triangles with a slope below the specified value to #RC_WALKABLE_AREA. @ingroup recast @param[in,out]	ctx					The build context to use during the operation. @param[in]		walkableSlopeCos	The cosine of maximum slope that is considered walkable. [Limits: 0 <= value < 1] @param[in]		verts				The vertices. [(x, y, z) * @p nv] @param[in]		nv					The number of vertices. @param[in]		tris				The triangle vertex indices. [(vertA, vertB, vertC) * @p nt] @param[in]		nt					The number of triangles. @param[out]	areas				The triangle area ids. [Length: >= @p nt]
- L1005 _prototype_ `void rcApplyAreaToTriangles(unsigned char* areas, const int nt, const unsigned char areaId);` — @UE BEGIN Replaces all RC_WALKABLE_AREA triangles with a area id. @ingroup recast @param[in,out]	areas				The triangle area ids. [Length: >= @p nt] @param[in]		nt					The number of triangles. @param[in]		areaId				The area id to assign instead of RC_WALKABLE_AREA. @par Used to apply an area id to all walkable triangles. Only replaces RC_WALKABLE_AREA, leaving other area ids unchanged.
- L1018 _prototype_ `void rcClearUnwalkableTriangles(rcContext* ctx, const rcReal walkableSlopeAngle, const rcReal* verts, int nv, const int* tris, int nt, unsigned char* areas);` — Sets the area id of all triangles with a slope greater than or equal to the specified value to #RC_NULL_AREA. @ingroup recast @param[in,out]	ctx					The build context to use during the operation. @param[in]		walkableSlopeAngle	The maximum slope that is considered walkable. [Limits: 0 <= value < 90] [Units: Degrees] @param[in]		verts				The vertices. [(x, y, z) * @p nv] @param[in]		nv					The number of vertices. @param[in]		tris				The triangle vertex indices. [(vertA, vertB, vertC) * @p nt] @param[in]		nt					The number of triangles. @param[out]	areas				The triangle area ids. [Length: >= @p nt]
- L1033 _prototype_ `void rcAddSpan(rcContext* ctx, rcHeightfield& hf, const int x, const int y, const unsigned short smin, const unsigned short smax, const unsigned char area, const int flagMergeThr);` — Adds a span to the specified heightfield. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in,out]	hf				An initialized heightfield. @param[in]		x				The width index where the span is to be added. [Limits: 0 <= value < rcHeightfield::width] @param[in]		y				The height index where the span is to be added. [Limits: 0 <= value < rcHeightfield::height] @param[in]		smin			The minimum height of the span. [Limit: < @p smax] [Units: vx] @param[in]		smax			The maximum height of the span. [Limit: <= #RC_SPAN_MAX_HEIGHT] [Units: vx] @param[in]		area			The area id of the span. [Limit: <= #RC_WALKABLE_AREA) @param[in]		flagMergeThr	The merge theshold. [Limit: >= 0] [Units: vx]
- L1037 _prototype_ `void rcAddSpans(rcContext* ctx, rcHeightfield& hf, const int flagMergeThr, const rcSpanCache* cachedSpans, const int nspans);`
- L1040 _prototype_ `int rcCountSpans(rcContext* ctx, rcHeightfield& hf);`
- L1041 _prototype_ `void rcCacheSpans(rcContext* ctx, rcHeightfield& hf, rcSpanCache* cachedSpans);`
- L1055 _prototype_ `void rcRasterizeTriangle(rcContext* ctx, const rcReal* v0, const rcReal* v1, const rcReal* v2, const unsigned char area, rcHeightfield& solid, const int flagMergeThr = 1, const int rasterizationFlags = 0, const int* rasterizationMasks = nullptr);` — Rasterizes a triangle into the specified heightfield. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		v0				Triangle vertex 0 [(x, y, z)] @param[in]		v1				Triangle vertex 1 [(x, y, z)] @param[in]		v2				Triangle vertex 2 [(x, y, z)] @param[in]		area			The area id of the triangle. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	solid			An initialized heightfield. @param[in]		flagMergeThr	The distance where the walkable flag is favored over the non-walkable flag. [Limit: >= 0] [Units: vx] @param[in]     rtzFlags		Flags to change the rasterization behavior			//UE @param[in]     rtzMasks		Mask for the rasterization flags [Size: hf.w*hf.h]	//UE
- L1075 _prototype_ `void rcRasterizeTriangles(rcContext* ctx, const rcReal* verts, const int nv, const int* tris, const unsigned char* areas, const int nt, rcHeightfield& solid, const int flagMergeThr = 1, const int rasterizationFlags = 0, const int* rasterizationMasks = nullptr,` — Rasterizes an indexed triangle mesh into the specified heightfield. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		verts			The vertices. [(x, y, z) * @p nv] @param[in]		nv				The number of vertices. @param[in]		tris			The triangle indices. [(vertA, vertB, vertC) * @p nt] @param[in]		areas			The area id's of the triangles. [Limit: <= #RC_WALKABLE_AREA] [Size: @p nt] @param[in]		nt				The number of triangles. @param[in,out]	solid			An initialized heightfield. @param[in]		flagMergeThr	The distance where the walkable flag is favored over the non-walkable flag. [Limit: >= 0] [Units: vx] @param[in]     rtzFlags		Flags to change the rasterization behavior			//UE @param[in]     rtzMasks		Mask for the rasterization flags [Size: hf.w*hf.h]	//UE @param[in]     vertsbmin		Min location of the bounding box of verts [(x, y, z)] //UE @param[in]     vertsbmax		Max location of the bounding box of verts [(x, y, z)] //UE
- L1096 _prototype_ `void rcRasterizeTriangles(rcContext* ctx, const rcReal* verts, const int nv, const unsigned short* tris, const unsigned char* areas, const int nt, rcHeightfield& solid, const int flagMergeThr = 1, const int rasterizationFlags = 0, const int* rasterizationMasks = nullptr,` — Rasterizes an indexed triangle mesh into the specified heightfield. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		verts			The vertices. [(x, y, z) * @p nv] @param[in]		nv				The number of vertices. @param[in]		tris			The triangle indices. [(vertA, vertB, vertC) * @p nt] @param[in]		areas			The area id's of the triangles. [Limit: <= #RC_WALKABLE_AREA] [Size: @p nt] @param[in]		nt				The number of triangles. @param[in,out]	solid			An initialized heightfield. @param[in]		flagMergeThr	The distance where the walkable flag is favored over the non-walkable flag. [Limit: >= 0] [Units: vx] @param[in]     rtzFlags		Flags to change the rasterization behavior			//UE @param[in]     rtzMasks		Mask for the rasterization flags [Size: hf.w*hf.h]	//UE @param[in]     vertsbmin		Min location of the bounding box of verts [(x, y, z)] //UE @param[in]     vertsbmax		Max location of the bounding box of verts [(x, y, z)] //UE
- L1115 _prototype_ `void rcRasterizeTriangles(rcContext* ctx, const rcReal* verts, const unsigned char* areas, const int nt, rcHeightfield& solid, const int flagMergeThr = 1, const int rasterizationFlags = 0, const int* rasterizationMasks = nullptr,` — Rasterizes triangles into the specified heightfield. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		verts			The triangle vertices. [(ax, ay, az, bx, by, bz, cx, by, cx) * @p nt] @param[in]		areas			The area id's of the triangles. [Limit: <= #RC_WALKABLE_AREA] [Size: @p nt] @param[in]		nt				The number of triangles. @param[in,out]	solid			An initialized heightfield. @param[in]		flagMergeThr	The distance where the walkable flag is favored over the non-walkable flag. [Limit: >= 0] [Units: vx] @param[in]     rtzFlags		Flags to change the rasterization behavior			//UE @param[in]     rtzMasks		Mask for the rasterization flags [Size: hf.w*hf.h]	//UE @param[in]     vertsbmin		Min location of the bounding box of verts [(x, y, z)] //UE @param[in]     vertsbmax		Max location of the bounding box of verts [(x, y, z)] //UE
- L1126 _prototype_ `void rcFilterLowHangingWalkableObstacles(rcContext* ctx, const int walkableClimb, rcHeightfield& solid);` — Marks non-walkable spans as walkable if their maximum is within @p walkableClimp of a walkable neighbor. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		walkableClimb	Maximum ledge height that is considered to still be traversable. [Limit: >=0] [Units: vx] @param[in,out]	solid			A fully built heightfield.  (All spans have been added.)
- L1140 _prototype_ `void rcFilterLedgeSpans(rcContext* ctx, const int walkableHeight, const int walkableClimb, const rcNeighborSlopeFilterMode neighborSlopeFilterMode, const rcReal maxStepFromWalkableSlope, const rcReal ch, const int yStart, const int maxYProcess, rcHeightfield& solid);` — Marks spans that are ledges as not-walkable, by a number of y coords at a time. @ingroup recast @param[in,out]	ctx							The build context to use during the operation. @param[in]		walkableHeight				Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[in]		walkableClimb				Maximum ledge height that is considered to still be traversable. [Limit: >=0] [Units: vx] @param[in]		neighborSlopeFilterMode		Change the way neighbors slope filtering is done. //UE @param[in]		maxStepFromWalkableSlope	Maximum step height in relation to cs and the walkable angle. [Limit: >= 0] [Units: wu] //UE @param[in]		ch							Cell height. [Limit: >= 0] [Units: wu] //UE @param[in,out]	solid						A fully built heightfield.  (All spans have been added.) @param[in]		yStart						y coord to start at @param[in]		maxYProcess					Max y coords to process (yStart + maxYProcess can be more than solid.height and will be capped to solid.height)
- L1153 _prototype_ `void rcFilterLedgeSpans(rcContext* ctx, const int walkableHeight, const int walkableClimb, const rcNeighborSlopeFilterMode neighborSlopeFilterMode, const rcReal maxStepFromWalkableSlope, const rcReal ch, rcHeightfield& solid);` — Marks spans that are ledges as not-walkable. @ingroup recast @param[in,out]	ctx							The build context to use during the operation. @param[in]		walkableHeight				Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[in]		walkableClimb				Maximum ledge height that is considered to still be traversable. [Limit: >=0] [Units: vx] @param[in]		neighborSlopeFilterMode		Change the way neighbors slope filtering is done. //UE @param[in]		maxStepFromWalkableSlope	Maximum step height in relation to cs and the walkable angle. [Limit: >= 0] [Units: wu] //UE @param[in]		ch							Cell height. [Limit: >= 0] [Units: wu] //UE @param[in,out]	solid						A fully built heightfield.  (All spans have been added.)
- L1162 _prototype_ `void rcFilterWalkableLowHeightSpans(rcContext* ctx, int walkableHeight, rcHeightfield& solid);` — Marks walkable spans as not walkable if the clearance above the span is less than the specified height. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		walkableHeight	Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[in,out]	solid			A fully built heightfield.  (All spans have been added.)
- L1163 _prototype_ `void rcFilterWalkableLowHeightSpansSequences(rcContext* ctx, int walkableHeight, rcHeightfield& solid);`
- L1170 _prototype_ `int rcGetHeightFieldSpanCount(rcContext* ctx, rcHeightfield& hf);` — Returns the number of spans contained in the specified heightfield. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		hf		An initialized heightfield. @returns The number of spans in the heightfield.
- L1187 _prototype_ `bool rcBuildCompactHeightfield(rcContext* ctx, const int walkableHeight, const int walkableClimb, rcHeightfield& hf, rcCompactHeightfield& chf);` — Builds a compact heightfield representing open space, from a heightfield representing solid space. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		walkableHeight	Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[in]		walkableClimb	Maximum ledge height that is considered to still be traversable. [Limit: >=0] [Units: vx] @param[in]		hf				The heightfield to be compacted. @param[out]	chf				The resulting compact heightfield. (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1196 _prototype_ `bool rcErodeWalkableArea(rcContext* ctx, int radius, rcCompactHeightfield& chf);` — Erodes the walkable area within the heightfield by the specified radius. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		radius	The radius of erosion. [Limits: 0 < value < 255] [Units: vx] @param[in,out]	chf		The populated compact heightfield to erode. @returns True if the operation completed successfully.
- L1208 _prototype_ `bool rcErodeWalkableAndLowAreas(rcContext* ctx, int radius, unsigned int height, unsigned char areaId, unsigned char filterFlags, rcCompactHeightfield& chf);` — Erodes the walkable area within the heightfield by the specified radius. Additionally, it will mark all spans that are too low (rcMarkLowAreas) @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		radius	The radius of erosion. [Limits: 0 < value < 255] [Units: vx] @param[in]		height	Height threshold [Units: vx] @param[in]		areaId	The area id to apply [Limit: <= @RC_WALKABLE_AREA] @param[in]		filterFlags	See: rcFilterLowAreaFlags @param[in,out]	chf		The populated compact heightfield to erode. @returns True if the operation completed successfully.
- L1217 _prototype_ `bool rcMedianFilterWalkableArea(rcContext* ctx, rcCompactHeightfield& chf);` — Applies a median filter to walkable area types (based on area id), removing noise. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in,out]	chf		A populated compact heightfield. @returns True if the operation completed successfully.
- L1226 _prototype_ `bool rcMarkLowAreas(rcContext* ctx, unsigned int height, unsigned char areaId, rcCompactHeightfield& chf);` — Marks all spans that have insufficient free space above @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in,out]	chf		A populated compact heightfield. @param[in]		height	Height threshold [Units: vx] @param[in]		areaId	The area id to apply [Limit: <= @RC_WALKABLE_AREA] @returns True if the operation completed successfully.
- L1235 _prototype_ `void rcMarkBoxArea(rcContext* ctx, const rcReal* bmin, const rcReal* bmax, unsigned char areaId, rcCompactHeightfield& chf);` — Applies an area id to all spans within the specified bounding box. (AABB) @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		bmin	The minimum of the bounding box. [(x, y, z)] @param[in]		bmax	The maximum of the bounding box. [(x, y, z)] @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf		A populated compact heightfield.
- L1247 _prototype_ `void rcMarkConvexPolyArea(rcContext* ctx, const rcReal* verts, const int nverts, const rcReal hmin, const rcReal hmax, unsigned char areaId, rcCompactHeightfield& chf);` — Applies the area id to the all spans within the specified convex polygon. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		verts	The vertices of the polygon [Fomr: (x, y, z) * @p nverts] @param[in]		nverts	The number of vertices in the polygon. @param[in]		hmin	The height of the base of the polygon. @param[in]		hmax	The height of the top of the polygon. @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf		A populated compact heightfield.
- L1258 _prototype_ `int rcOffsetPoly(const rcReal* verts, const int nverts, const rcReal offset, rcReal* outVerts, const int maxOutVerts);` — Helper function to offset voncex polygons for rcMarkConvexPolyArea. @ingroup recast @param[in]		verts		The vertices of the polygon [Form: (x, y, z) * @p nverts] @param[in]		nverts		The number of vertices in the polygon. @param[out]	outVerts	The offset vertices (should hold up to 2 * @p nverts) [Form: (x, y, z) * return value] @param[in]		maxOutVerts	The max number of vertices that can be stored to @p outVerts. @returns Number of vertices in the offset polygon or 0 if too few vertices in @p outVerts.
- L1269 _prototype_ `void rcMarkCylinderArea(rcContext* ctx, const rcReal* pos, const rcReal r, const rcReal h, unsigned char areaId, rcCompactHeightfield& chf);` — Applies the area id to all spans within the specified cylinder. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		pos		The center of the base of the cylinder. [Form: (x, y, z)] @param[in]		r		The radius of the cylinder. @param[in]		h		The height of the cylinder. @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf	A populated compact heightfield.
- L1280 _prototype_ `void rcReplaceBoxArea(rcContext* ctx, const rcReal* bmin, const rcReal* bmax, unsigned char areaId, unsigned char filterAreaId, rcCompactHeightfield& chf);` — Replaces an area id in spans with matching filter area within the specified bounding box. (AABB) @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		bmin	The minimum of the bounding box. [(x, y, z)] @param[in]		bmax	The maximum of the bounding box. [(x, y, z)] @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf		A populated compact heightfield.
- L1293 _prototype_ `void rcReplaceConvexPolyArea(rcContext* ctx, const rcReal* verts, const int nverts, const rcReal hmin, const rcReal hmax, unsigned char areaId, unsigned char filterAreaId, rcCompactHeightfield& chf);` — Replaces an area id in spans with matching filter area within the specified convex polygon. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		verts	The vertices of the polygon [Fomr: (x, y, z) * @p nverts] @param[in]		nverts	The number of vertices in the polygon. @param[in]		hmin	The height of the base of the polygon. @param[in]		hmax	The height of the top of the polygon. @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf		A populated compact heightfield.
- L1305 _prototype_ `void rcReplaceCylinderArea(rcContext* ctx, const rcReal* pos, const rcReal r, const rcReal h, unsigned char areaId, unsigned char filterAreaId, rcCompactHeightfield& chf);` — Replaces an area id in spans with matching filter area within the specified cylinder. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		pos		The center of the base of the cylinder. [Form: (x, y, z)] @param[in]		r		The radius of the cylinder. @param[in]		h		The height of the cylinder. @param[in]		areaId	The area id to apply. [Limit: <= #RC_WALKABLE_AREA] @param[in,out]	chf	A populated compact heightfield.
- L1314 _prototype_ `bool rcBuildDistanceField(rcContext* ctx, rcCompactHeightfield& chf);` — Builds the distance field for the specified compact heightfield. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in,out]	chf		A populated compact heightfield. @returns True if the operation completed successfully.
- L1327 _prototype_ `bool rcBuildRegions(rcContext* ctx, rcCompactHeightfield& chf, const int borderSize, const int minRegionArea, const int mergeRegionArea);` — Builds region data for the heightfield using watershed partitioning. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in,out]	chf				A populated compact heightfield. @param[in]		borderSize		The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		minRegionArea	The minimum number of cells allowed to form isolated island areas. [Limit: >=0] [Units: vx]. @param[in]		mergeRegionArea		Any regions with a span count smaller than this value will, if possible, be merged with larger regions. [Limit: >=0] [Units: vx] @returns True if the operation completed successfully.
- L1341 _prototype_ `bool rcBuildRegionsMonotone(rcContext* ctx, rcCompactHeightfield& chf, const rcBorderSize borderSize, const int minRegionArea, const int mergeRegionArea);` — Builds region data for the heightfield using simple monotone partitioning. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in,out]	chf				A populated compact heightfield. @param[in]		borderSize		The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		minRegionArea	The minimum number of cells allowed to form isolated island areas. [Limit: >=0] [Units: vx]. @param[in]		mergeRegionArea	Any regions with a span count smaller than this value will, if possible, be merged with larger regions. [Limit: >=0] [Units: vx] @returns True if the operation completed successfully.
- L1356 _prototype_ `bool rcBuildRegionsChunky(rcContext* ctx, rcCompactHeightfield& chf, const rcBorderSize borderSize, const int minRegionArea, const int mergeRegionArea,` — Builds region data for the heightfield using simple monotone partitioning. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in,out]	chf				A populated compact heightfield. @param[in]		borderSize		The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		minRegionArea	The minimum number of cells allowed to form isolated island areas. [Limit: >=0] [Units: vx]. @param[in]		mergeRegionArea	Any regions with a span count smaller than this value will, if possible, be merged with larger regions. [Limit: >=0] [Units: vx] @param[in]		chunkSize		Size of subregion [Units: vx] @returns True if the operation completed successfully.
- L1364 _function_ `inline void rcSetCon(rcCompactSpan& s, int dir, int i)` — Sets the neighbor connection data for the specified direction. @param[in]		s		The span to update. @param[in]		dir		The direction to set. [Limits: 0 <= value < 4] @param[in]		i		The index of the neighbor span.
- L1376 _function_ `inline int rcGetCon(const rcCompactSpan& s, int dir)` — Gets neighbor connection data for the specified direction. @param[in]		s		The span to check. @param[in]		dir		The direction to check. [Limits: 0 <= value < 4] @return The neighbor connection data for the specified direction, or #RC_NOT_CONNECTED if there is no connection.
- L1386 _function_ `inline int rcGetDirOffsetX(int dir)` — Gets the standard width (x-axis) offset for the specified direction. @param[in]		dir		The direction. [Limits: 0 <= value < 4] @return The width offset to apply to the current cell position to move in the direction.
- L1396 _function_ `inline int rcGetDirOffsetY(int dir)` — Gets the standard height (z-axis) offset for the specified direction. @param[in]		dir		The direction. [Limits: 0 <= value < 4] @return The height offset to apply to the current cell position to move in the direction.
- L1419 _prototype_ `bool rcBuildHeightfieldLayers(rcContext* ctx, rcCompactHeightfield& chf, const rcBorderSize borderSize, const int walkableHeight,` — Builds a layer set from the specified compact heightfield. @ingroup recast @param[in,out]	ctx			The build context to use during the operation. @param[in]		chf			A fully built compact heightfield. @param[in]		borderSize	The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		walkableHeight	Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[out]	lset		The resulting layer set. (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1433 _prototype_ `bool rcBuildHeightfieldLayersMonotone(rcContext* ctx, rcCompactHeightfield& chf, const rcBorderSize borderSize, const int walkableHeight,` — Builds a layer set from the specified compact heightfield. @ingroup recast @param[in,out]	ctx			The build context to use during the operation. @param[in]		chf			A fully built compact heightfield. @param[in]		borderSize	The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		walkableHeight	Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[out]	lset		The resulting layer set. (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1448 _prototype_ `bool rcBuildHeightfieldLayersChunky(rcContext* ctx, rcCompactHeightfield& chf, const rcBorderSize borderSize, const int walkableHeight,` — Builds a layer set from the specified compact heightfield. @ingroup recast @param[in,out]	ctx			The build context to use during the operation. @param[in]		chf			A fully built compact heightfield. @param[in]		borderSize	The size of the non-navigable border around the heightfield. [Limit: >=0] [Units: vx] @param[in]		walkableHeight	Minimum floor to 'ceiling' height that will still allow the floor area to be considered walkable. [Limit: >= 3] [Units: vx] @param[in]		chunkSize	Size of chunk of subregion [Units: vx] @param[out]	lset		The resulting layer set. (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1466 _prototype_ `bool rcBuildContours(rcContext* ctx, rcCompactHeightfield& chf, const rcReal maxError, const int maxEdgeLen, rcContourSet& cset, const int flags = RC_CONTOUR_TESS_WALL_EDGES);` — Builds a contour set from the region outlines in the provided compact heightfield. @ingroup recast @param[in,out]	ctx			The build context to use during the operation. @param[in]		chf			A fully built compact heightfield. @param[in]		maxError	The maximum distance a simplfied contour's border edges should deviate the original raw contour. [Limit: >=0] [Units: wu] @param[in]		maxEdgeLen	The maximum allowed length for contour edges along the border of the mesh. [Limit: >=0] [Units: vx] @param[out]	cset		The resulting contour set. (Must be pre-allocated.) @param[in]		buildFlags	The build flags. (See: #rcBuildContoursFlags) @returns True if the operation completed successfully.
- L1477 _prototype_ `bool rcBuildClusters(rcContext* ctx, rcContourSet& cset, rcClusterSet& clusters);` — Builds a cluster set from contours @ingroup recast @param[in,out]	ctx			The build context to use during the operation @param[in]		cset		Contour set @param[out]		clusters	Resulting cluster set
- L1489 _prototype_ `bool rcBuildPolyMesh(rcContext* ctx, rcContourSet& cset, const int nvp, rcPolyMesh& mesh);` — Builds a polygon mesh from the provided contours. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		cset	A fully built contour set. @param[in]		nvp		The maximum number of vertices allowed for polygons generated during the contour to polygon conversion process. [Limit: >= 3] @param[out]	mesh	The resulting polygon mesh. (Must be re-allocated.) @returns True if the operation completed successfully.
- L1498 _prototype_ `bool rcMergePolyMeshes(rcContext* ctx, rcPolyMesh** meshes, const int nmeshes, rcPolyMesh& mesh);` — Merges multiple polygon meshes into a single mesh. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		meshes	An array of polygon meshes to merge. [Size: @p nmeshes] @param[in]		nmeshes	The number of polygon meshes in the meshes array. @param[in]		mesh	The resulting polygon mesh. (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1510 _prototype_ `bool rcBuildPolyMeshDetail(rcContext* ctx, const rcPolyMesh& mesh, const rcCompactHeightfield& chf, const rcReal sampleDist, const rcReal sampleMaxError, rcPolyMeshDetail& dmesh);` — Builds a detail mesh from the provided polygon mesh. @ingroup recast @param[in,out]	ctx				The build context to use during the operation. @param[in]		mesh			A fully built polygon mesh. @param[in]		chf				The compact heightfield used to build the polygon mesh. @param[in]		sampleDist		Sets the distance to use when samping the heightfield. [Limit: >=0] [Units: wu] @param[in]		sampleMaxError	The maximum distance the detail mesh surface should deviate from heightfield data. [Limit: >=0] [Units: wu] @param[out]	dmesh			The resulting detail mesh.  (Must be pre-allocated.) @returns True if the operation completed successfully.
- L1520 _prototype_ `bool rcCopyPolyMesh(rcContext* ctx, const rcPolyMesh& src, rcPolyMesh& dst);` — Copies the poly mesh data from src to dst. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		src		The source mesh to copy from. @param[out]	dst		The resulting detail mesh. (Must be pre-allocated, must be empty mesh.) @returns True if the operation completed successfully.
- L1529 _prototype_ `bool rcMergePolyMeshDetails(rcContext* ctx, rcPolyMeshDetail** meshes, const int nmeshes, rcPolyMeshDetail& mesh);` — Merges multiple detail meshes into a single detail mesh. @ingroup recast @param[in,out]	ctx		The build context to use during the operation. @param[in]		meshes	An array of detail meshes to merge. [Size: @p nmeshes] @param[in]		nmeshes	The number of detail meshes in the meshes array. @param[out]	mesh	The resulting detail mesh. (Must be pre-allocated.) @returns True if the operation completed successfully.

### `Source/Runtime/Navmesh/Public/Recast/RecastAlloc.h` (Public)


#### enum `rcAllocHint`  
`enum rcAllocHint`  
_L29-33_
- desc: Provides hint values to the memory allocator on how long the memory is expected to be used.
- L31 _public enumerator_ `RC_ALLOC_PERM` — Memory will persist after a function call.
- L32 _public enumerator_ `RC_ALLOC_TEMP` — Memory used temporarily within a function.

#### class `rcIntArray`  
`class rcIntArray`  
_L67-111_
- desc: A simple dynamic array of integers.
- L69 _private member_ `int* m_data;`
- L70 _private member_ `int m_size, m_cap;`
- L70 _private member_ `int m_size, m_cap;`
- L71 _private prototype_ `inline rcIntArray(const rcIntArray&);`
- L72 _private prototype_ `inline rcIntArray& operator=(const rcIntArray&);`
- L76 _public function_ `inline rcIntArray() : m_data(0), m_size(0), m_cap(0)` — Constructs an instance with an initial array size of zero.
- L80 _public function_ `inline rcIntArray(int n) : m_data(0), m_size(0), m_cap(0)` — Constructs an instance initialized to the specified size. @param[in]		n	The initial size of the integer array.
- L81 _public function_ `inline ~rcIntArray()`
- L85 _public prototype_ `void resize(int n);` — Specifies the new size of the integer array. @param[in]		n	The new size of the integer array.
- L89 _public function_ `inline void push(int item)` — Push the specified integer onto the end of the array and increases the size by one. @param[in]		item	The new value.
- L93 _public function_ `inline int pop()` — Returns the value at the end of the array and reduces the size by one. @return The value at the end of the array.
- L98 _public function_ `inline const int& operator[](int i) const` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L103 _public function_ `inline int& operator[](int i)` — The value at the specified array index. @warning Does not provide overflow protection. @param[in]		i	The index of the value.
- L106 _public function_ `inline int size() const` — The current size of the integer array.
- L109 _public prototype_ `bool contains(int n) const;` — @UE BEGIN: added contains()

#### class `rcScopedDelete`  
`template<class T> class rcScopedDelete`  
_L115-137_
- desc: A simple helper class used to delete an array when it goes out of scope. @note This class is rarely if ever used by the end user.
- L117 _private member_ `T* ptr;`
- L118 _private member_ `int size;`
- L119 _private prototype_ `inline T* operator=(T* p);`
- L123 _public function_ `inline rcScopedDelete() : ptr(0)` — Constructs an instance with a null pointer.
- L124 _public function_ `inline rcScopedDelete(int n)`
- L128 _public function_ `inline rcScopedDelete(T* p) : ptr(p)` — Constructs an instance with the specified pointer. @param[in]		p	An pointer to an allocated array.
- L129 _public function_ `inline ~rcScopedDelete()`
- L133 _public function_ `inline operator T*()` — The root array pointer. @return The root array pointer.
- L136 _public prototype_ `bool resizeGrow(int n);` — UE: resize and copy existing memory (n = element count), doesn't destruct elements!
- L140 _function_ `template<class T> bool rcScopedDelete<T>::resizeGrow(int n)`

#### class `rcScopedStructArrayDelete`  
`template<class T> class rcScopedStructArrayDelete`  
_L159-183_
- desc: A simple helper class used to delete an array of instances of structs, that require cleaning up by calling destructor on every instance before release. Releasing is taking place when rcScopedStructArrayDelete instance goes out of scope. @note if T doesn't require a destructor to be called use rcScopedDelete instead.
- L161 _private member_ `int itemCount;`
- L162 _private member_ `T* ptr;`
- L165 _private prototype_ `inline T* operator=(T* p);` — on purpose made private to restrict copying
- L169 _public function_ `inline rcScopedStructArrayDelete(const int n) : itemCount(n)` — Constructs an array of instances of T
- L171 _public function_ `~rcScopedStructArrayDelete()`
- L182 _public function_ `inline operator T*()` — The root array pointer. @return The root array pointer.

#### Free symbols / members of external scopes

- L23 _macro_ `#define RECASTALLOC_H`
- L40 _typedef_ `typedef void* (rcAllocFunc)(int size, rcAllocHint hint);` — A memory allocation function. @param[in]		size			The size, in bytes of memory, to allocate. @param[in]		rcAllocHint	A hint to the allocator on how long the memory is expected to be in use. @return A pointer to the beginning of the allocated memory block, or null if the allocation failed. @see rcAllocSetCustom
- L45 _typedef_ `typedef void (rcFreeFunc)(void* ptr);` — A memory deallocation function. @param[in]		ptr		A pointer to a memory block previously allocated using #rcAllocFunc. @see rcAllocSetCustom
- L50 _prototype_ `void rcAllocSetCustom(rcAllocFunc *allocFunc, rcFreeFunc *freeFunc);` — Sets the base custom allocation functions to be used by Recast. @param[in]		allocFunc	The memory allocation function to be used by #rcAlloc @param[in]		freeFunc	The memory de-allocation function to be used by #rcFree
- L57 _prototype_ `void* rcAlloc(int size, rcAllocHint hint);` — Allocates a memory block. @param[in]		size	The size, in bytes of memory, to allocate. @param[in]		hint	A hint to the allocator on how long the memory is expected to be in use. @return A pointer to the beginning of the allocated memory block, or null if the allocation failed. @see rcFree
- L62 _prototype_ `void rcFree(void* ptr);` — Deallocates a memory block. @param[in]		ptr		A pointer to a memory block previously allocated using #rcAlloc. @see rcAlloc
- L64 _prototype_ `void rcMemCpy(void* dst, void* src, int size);`

### `Source/Runtime/Navmesh/Public/Recast/RecastAssert.h` (Public)


#### Free symbols / members of external scopes

- L23 _macro_ `#define RECASTASSERT_H`
- L32 _macro_ `# define rcAssert(x) do { (void)sizeof((x)); } while((void)(__LINE__==-1),false)` — From http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/
- L35 _macro_ `# define rcAssert(x) { assert(x); CA_ASSUME(x); } (void)0`

### `Source/Runtime/Navmesh/Public/Recast/RecastLargeWorldCoordinates.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define RC_LARGE_WORLD_COORDINATES_DISABLED 0`
- L12 _typedef_ `typedef float rcReal;`
- L16 _typedef_ `typedef double rcReal;`
- L20 _variable_ `constexpr rcReal RC_REAL_MAX = std::numeric_limits<rcReal>::max();`
