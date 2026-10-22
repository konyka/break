# Developer / GraphColor

- module root: `Source/Developer/GraphColor`
- headers: 11; symbols: 193
- symbol kinds: function=19, macro=67, member=42, prototype=41, struct=9, typedef=15
- PrivateDependencyModuleNames: Core

### `Source/Developer/GraphColor/Private/appconst.h` (Private)


#### Free symbols / members of external scopes

- L55 _macro_ `#define OK 1`
- L56 _macro_ `#define NOTOK 0`
- L59 _macro_ `#define TRUE 1`
- L63 _macro_ `#define FALSE 0`
- L69 _macro_ `#define NIL 0` — This definition is used with 1-based array indexing
- L70 _macro_ `#define NIL_CHAR 0x00`

### `Source/Developer/GraphColor/Private/graph.h` (Private)


#### Free symbols / members of external scopes

- L59 _prototype_ `graphP gp_New();`
- L61 _prototype_ `int gp_InitGraph(graphP theGraph, int N);`
- L62 _prototype_ `void gp_ReinitializeGraph(graphP theGraph);`
- L63 _prototype_ `int gp_CopyAdjacencyLists(graphP dstGraph, graphP srcGraph);`
- L64 _prototype_ `int gp_CopyGraph(graphP dstGraph, graphP srcGraph);`
- L66 _prototype_ `void gp_Free(graphP *pGraph);`
- L68 _prototype_ `int gp_IsNeighbor(graphP theGraph, int u, int v);`
- L69 _prototype_ `int gp_GetNeighborEdgeRecord(graphP theGraph, int u, int v);`
- L70 _prototype_ `int gp_GetVertexDegree(graphP theGraph, int v);`
- L72 _prototype_ `int gp_GetArcCapacity(graphP theGraph);`
- L73 _prototype_ `int gp_EnsureArcCapacity(graphP theGraph, int requiredArcCapacity);`
- L75 _prototype_ `int gp_AddEdge(graphP theGraph, int u, int ulink, int v, int vlink);`
- L77 _prototype_ `void gp_HideEdge(graphP theGraph, int e);`
- L78 _prototype_ `void gp_RestoreEdge(graphP theGraph, int e);`
- L79 _prototype_ `int gp_HideVertex(graphP theGraph, int vertex);`
- L81 _prototype_ `int gp_ContractEdge(graphP theGraph, int e);`
- L82 _prototype_ `int gp_IdentifyVertices(graphP theGraph, int u, int v, int eBefore);`
- L83 _prototype_ `int gp_RestoreVertices(graphP theGraph);`

### `Source/Developer/GraphColor/Private/graphColorVertices.h` (Private)


#### Free symbols / members of external scopes

- L54 _macro_ `#define COLORVERTICES_NAME "ColorVertices"`
- L56 _prototype_ `int gp_AttachColorVertices(graphP theGraph);`
- L57 _prototype_ `int gp_DetachColorVertices(graphP theGraph);`
- L59 _prototype_ `int gp_ColorVertices(graphP theGraph);`
- L60 _prototype_ `int gp_GetNumColorsUsed(graphP theGraph);`
- L62 _prototype_ `void gp_CopyColors(graphP theGraph, unsigned char* Colors );`

### `Source/Developer/GraphColor/Private/graphColorVertices.private.h` (Private)


#### struct `(anonymous)`  
``  
_L55-76_

#### Free symbols / members of external scopes

- L57 _member_ `int initialized;` (scope `__anonbc97d64a0108`) — Helps distinguish initialize from re-initialize
- L60 _member_ `graphP theGraph;` (scope `__anonbc97d64a0108`) — The graph that this context augments
- L63 _member_ `graphFunctionTable functions;` (scope `__anonbc97d64a0108`) — Overloaded function pointers
- L68 _member_ `listCollectionP degLists;` (scope `__anonbc97d64a0108`) — Data structures, unique to this extension, for managing lists of vertices by degree (e.g. all vertices of degree K in list K), and for storing each vertex color (e.g. vertex K has color[K])
- L69 _member_ `int *degListHeads;` (scope `__anonbc97d64a0108`)
- L70 _member_ `int *degree;` (scope `__anonbc97d64a0108`)
- L71 _member_ `int *color;` (scope `__anonbc97d64a0108`)
- L72 _member_ `int numVerticesToReduce, highestColorUsed;` (scope `__anonbc97d64a0108`)
- L72 _member_ `int numVerticesToReduce, highestColorUsed;` (scope `__anonbc97d64a0108`)
- L74 _member_ `int *colorDetector;` (scope `__anonbc97d64a0108`)
- L76 _typedef_ `} ColorVerticesContext;`

### `Source/Developer/GraphColor/Private/graphExtensions.h` (Private)


#### Free symbols / members of external scopes

- L54 _prototype_ `int gp_AddExtension(graphP theGraph, int *pModuleID, void *context, void *(*dupContext)(void *, void *), void (*freeContext)(void *), graphFunctionTableP overloadTable);`
- L61 _prototype_ `int gp_FindExtension(graphP theGraph, int moduleID, void **pContext);`
- L62 _prototype_ `void *gp_GetExtension(graphP theGraph, int moduleID);`
- L64 _prototype_ `int gp_RemoveExtension(graphP theGraph, int moduleID);`
- L66 _prototype_ `int gp_CopyExtensions(graphP dstGraph, graphP srcGraph);`
- L68 _prototype_ `void gp_FreeExtensions(graphP theGraph);`

### `Source/Developer/GraphColor/Private/graphExtensions.private.h` (Private)


#### struct `graphExtension`  
`struct graphExtension`  
_L54-64_
- L56 _public member_ `int moduleID;`
- L57 _public member_ `void *context;`
- L58 _public member_ `void *(*dupContext)(void *, void *);`
- L59 _public member_ `void (*freeContext)(void *);`
- L61 _public member_ `graphFunctionTableP functions;`
- L63 _public member_ `graphExtension *next;`

#### Free symbols / members of external scopes

- L66 _typedef_ `typedef graphExtension * graphExtensionP;`

### `Source/Developer/GraphColor/Private/graphFunctionTable.h` (Private)


#### struct `(anonymous)`  
``  
_L61-70_

#### Free symbols / members of external scopes

- L53 _typedef_ `typedef baseGraphStructure* graphP;`
- L64 _member_ `int (*fpInitGraph)(graphP, int);` (scope `__anonb337344b0108`) — These function pointers allow extension modules to overload some of the behaviors of gp_* function in the public API
- L66 _member_ `void (*fpHideEdge)(graphP, int);` (scope `__anonb337344b0108`)
- L67 _member_ `int (*fpRestoreVertex)(graphP);` (scope `__anonb337344b0108`)
- L68 _member_ `int (*fpIdentifyVertices)(graphP,int,int,int);` (scope `__anonb337344b0108`)
- L70 _typedef_ `} graphFunctionTable;`
- L72 _typedef_ `typedef graphFunctionTable * graphFunctionTableP;`

### `Source/Developer/GraphColor/Private/graphStructures.h` (Private)


#### struct `(anonymous)`  
``  
_L85-88_

#### struct `(anonymous)`  
``  
_L163-167_

#### struct `baseGraphStructure`  
`struct baseGraphStructure`  
_L256-270_
- L258 _public member_ `vertexRecP V;`
- L260 _public member_ `int N, NV;`
- L260 _public member_ `int N, NV;`
- L262 _public member_ `edgeRecP E;`
- L263 _public member_ `int M, arcCapacity;`
- L263 _public member_ `int M, arcCapacity;`
- L264 _public member_ `stackP edgeHoles;`
- L266 _public member_ `stackP theStack;`
- L268 _public member_ `graphExtensionP extensions;`
- L269 _public member_ `graphFunctionTable functions;`

#### Free symbols / members of external scopes

- L61 _macro_ `#define NONEMBEDDABLE -1` — A return value to indicate success prior to completely processing a graph, whereas OK signifies EMBEDDABLE (no unreducible obstructions) and NOTOK signifies an exception.
- L68 _macro_ `#define DEFAULT_EDGE_LIMIT 3` — The initial setting for the edge storage capacity expressed as a constant factor of N, which is the number of vertices in the graph. By default, array E is allocated enough space to contain 3N edges, which is 6N arcs (half edges), but this initial setting can be overridden using gp_EnsureArcCapacity(), which is especially efficient if done before calling gp_InitGraph() or gp_Read().
- L86 _member_ `int link[2];` (scope `__anon113889010108`)
- L87 _member_ `int neighbor;` (scope `__anon113889010108`)
- L88 _typedef_ `} edgeRec;`
- L90 _typedef_ `typedef edgeRec * edgeRecP;`
- L93 _macro_ `#define gp_IsArc(e) (e)`
- L94 _macro_ `#define gp_IsNotArc(e) (!(e))`
- L95 _macro_ `#define gp_GetFirstEdge(theGraph) (2)`
- L97 _macro_ `#define gp_IsArc(e) ((e) != NIL)`
- L98 _macro_ `#define gp_IsNotArc(e) ((e) == NIL)`
- L99 _macro_ `#define gp_GetFirstEdge(theGraph) (0)`
- L104 _macro_ `#define gp_EdgeInUse(theGraph, e) (gp_IsVertex(gp_GetNeighbor(theGraph, e)))`
- L105 _macro_ `#define gp_EdgeNotInUse(theGraph, e) (gp_IsNotVertex(gp_GetNeighbor(theGraph, e)))`
- L106 _macro_ `#define gp_EdgeIndexBound(theGraph) (gp_GetFirstEdge(theGraph) + (theGraph)->arcCapacity)`
- L107 _macro_ `#define gp_EdgeInUseIndexBound(theGraph) (gp_GetFirstEdge(theGraph) + (((theGraph)->M + sp_GetCurrentSize((theGraph)->edgeHoles)) << 1))`
- L111 _macro_ `#define gp_GetTwinArc(theGraph, Arc) ((Arc) ^ 1)` — An edge is represented by two consecutive edge records (arcs) in the edge array E. If an even number, xor 1 will add one; if an odd number, xor 1 will subtract 1
- L114 _macro_ `#define gp_GetNextArc(theGraph, e) (theGraph->E[e].link[0])` — Access to adjacency list pointers
- L115 _macro_ `#define gp_GetPrevArc(theGraph, e) (theGraph->E[e].link[1])`
- L116 _macro_ `#define gp_GetAdjacentArc(theGraph, e, theLink) (theGraph->E[e].link[theLink])`
- L118 _macro_ `#define gp_SetNextArc(theGraph, e, newNextArc) (theGraph->E[e].link[0] = newNextArc)`
- L119 _macro_ `#define gp_SetPrevArc(theGraph, e, newPrevArc) (theGraph->E[e].link[1] = newPrevArc)`
- L120 _macro_ `#define gp_SetAdjacentArc(theGraph, e, theLink, newArc) (theGraph->E[e].link[theLink] = newArc)`
- L123 _macro_ `#define gp_GetNeighbor(theGraph, e) (theGraph->E[e].neighbor)` — Access to vertex 'neighbor' member indicated by arc
- L124 _macro_ `#define gp_SetNeighbor(theGraph, e, v) (theGraph->E[e].neighbor = v)`
- L126 _macro_ `#define gp_CopyEdgeRec(dstGraph, edst, srcGraph, esrc) (dstGraph->E[edst] = srcGraph->E[esrc])`
- L164 _member_ `int link[2];` (scope `__anon113889010208`)
- L165 _member_ `int index;` (scope `__anon113889010208`)
- L166 _member_ `unsigned flags;` (scope `__anon113889010208`)
- L167 _typedef_ `} vertexRec;`
- L169 _typedef_ `typedef vertexRec * vertexRecP;`
- L172 _macro_ `#define gp_GetFirstArc(theGraph, v) (theGraph->V[v].link[0])` — Accessors for vertex adjacency list links
- L173 _macro_ `#define gp_GetLastArc(theGraph, v) (theGraph->V[v].link[1])`
- L174 _macro_ `#define gp_GetArc(theGraph, v, theLink) (theGraph->V[v].link[theLink])`
- L176 _macro_ `#define gp_SetFirstArc(theGraph, v, newFirstArc) (theGraph->V[v].link[0] = newFirstArc)`
- L177 _macro_ `#define gp_SetLastArc(theGraph, v, newLastArc) (theGraph->V[v].link[1] = newLastArc)`
- L178 _macro_ `#define gp_SetArc(theGraph, v, theLink, newArc) (theGraph->V[v].link[theLink] = newArc)`
- L182 _macro_ `#define gp_IsVertex(v) (v)`
- L183 _macro_ `#define gp_IsNotVertex(v) (!(v))`
- L185 _macro_ `#define gp_GetFirstVertex(theGraph) (1)`
- L186 _macro_ `#define gp_GetLastVertex(theGraph) ((theGraph)->N)`
- L187 _macro_ `#define gp_VertexInRange(theGraph, v) ((v) <= (theGraph)->N)`
- L188 _macro_ `#define gp_VertexInRangeDescending(theGraph, v) (v)`
- L190 _macro_ `#define gp_PrimaryVertexIndexBound(theGraph) (gp_GetFirstVertex(theGraph) + (theGraph)->N)`
- L191 _macro_ `#define gp_VertexIndexBound(theGraph) (gp_PrimaryVertexIndexBound(theGraph) + (theGraph)->N)`
- L193 _macro_ `#define gp_GetFirstVirtualVertex(theGraph) (theGraph->N + 1)`
- L194 _macro_ `#define gp_VirtualVertexInRange(theGraph, v) ((v) <= theGraph->N + theGraph->NV)`
- L197 _macro_ `#define gp_IsVertex(v) ((v) != NIL)`
- L198 _macro_ `#define gp_IsNotVertex(v) ((v) == NIL)`
- L200 _macro_ `#define gp_GetFirstVertex(theGraph) (0)`
- L201 _macro_ `#define gp_GetLastVertex(theGraph) ((theGraph)->N - 1)`
- L202 _macro_ `#define gp_VertexInRange(theGraph, v) ((v) < (theGraph)->N)`
- L203 _macro_ `#define gp_VertexInRangeDescending(theGraph, v) ((v) >= 0)`
- L208 _macro_ `#define gp_GetFirstVirtualVertex(theGraph) (theGraph->N)`
- L209 _macro_ `#define gp_VirtualVertexInRange(theGraph, v) ((v) < theGraph->N + theGraph->NV)`
- L216 _macro_ `#define gp_GetVertexIndex(theGraph, v) (theGraph->V[v].index)` — Accessors for vertex index
- L217 _macro_ `#define gp_SetVertexIndex(theGraph, v, theIndex) (theGraph->V[v].index = theIndex)`
- L220 _macro_ `#define gp_InitVertexFlags(theGraph, v) (theGraph->V[v].flags = 0)` — Initializer for vertex flags
- L223 _macro_ `#define VERTEX_VISITED_MASK 1` — Definitions and accessors for vertex flags
- L224 _macro_ `#define gp_GetVertexVisited(theGraph, v) (theGraph->V[v].flags&VERTEX_VISITED_MASK)`
- L225 _macro_ `#define gp_ClearVertexVisited(theGraph, v) (theGraph->V[v].flags &= ~VERTEX_VISITED_MASK)`
- L226 _macro_ `#define gp_SetVertexVisited(theGraph, v) (theGraph->V[v].flags |= VERTEX_VISITED_MASK)`
- L228 _macro_ `#define gp_CopyVertexRec(dstGraph, vdst, srcGraph, vsrc) (dstGraph->V[vdst] = srcGraph->V[vsrc])`
- L229 _macro_ `#define gp_SwapVertexRec(dstGraph, vdst, srcGraph, vsrc) \`
- L272 _typedef_ `typedef baseGraphStructure * graphP;`
- L277 _prototype_ `void gp_AttachArc(graphP theGraph, int v, int e, int link, int newArc);` — Methods for attaching an arc into the adjacency list or detaching an arc from it. The terms AddArc, InsertArc and DeleteArc are not used because the arcs are not inserted or added to or deleted from storage (only whole edges are inserted or deleted)
- L278 _prototype_ `void gp_DetachArc(graphP theGraph, int arc);`

### `Source/Developer/GraphColor/Private/listcoll.h` (Private)


#### struct `(anonymous)`  
``  
_L56-58_

#### struct `(anonymous)`  
``  
_L61-64_

#### Free symbols / members of external scopes

- L57 _member_ `int prev, next;` (scope `__anonbc1eb8710108`)
- L57 _member_ `int prev, next;` (scope `__anonbc1eb8710108`)
- L58 _typedef_ `} lcnode;`
- L62 _member_ `int N;` (scope `__anonbc1eb8710208`)
- L63 _member_ `lcnode *List;` (scope `__anonbc1eb8710208`)
- L64 _typedef_ `} listCollectionRec;`
- L66 _typedef_ `typedef listCollectionRec * listCollectionP;`
- L68 _prototype_ `listCollectionP LCNew(int N);`
- L69 _prototype_ `void LCFree(listCollectionP *pListColl);`
- L71 _prototype_ `void LCInsertAfter(listCollectionP listColl, int theAnchor, int theNewNode);`
- L72 _prototype_ `void LCInsertBefore(listCollectionP listColl, int theAnchor, int theNewNode);`
- L78 _function_ `inline void LCReset(listCollectionP listColl)`
- L90 _function_ `inline void LCCopy(listCollectionP dst, listCollectionP src)`
- L105 _function_ `inline int LCGetNext(listCollectionP listColl, int theList, int theNode)`
- L118 _function_ `inline int LCGetPrev(listCollectionP listColl, int theList, int theNode)`
- L130 _function_ `inline int LCAppend(listCollectionP listColl, int theList, int theNode)`
- L163 _function_ `inline int LCPrepend(listCollectionP listColl, int theList, int theNode)`
- L176 _function_ `inline int LCDelete(listCollectionP listColl, int theList, int theNode)`

### `Source/Developer/GraphColor/Private/stack.h` (Private)


#### struct `(anonymous)`  
``  
_L56-59_

#### Free symbols / members of external scopes

- L57 _member_ `int *S;` (scope `__anon26bd43610108`)
- L58 _member_ `int size, capacity;` (scope `__anon26bd43610108`)
- L58 _member_ `int size, capacity;` (scope `__anon26bd43610108`)
- L59 _typedef_ `} stack;`
- L61 _typedef_ `typedef stack * stackP;`
- L63 _prototype_ `stackP sp_New(int);`
- L64 _prototype_ `void sp_Free(stackP *);`
- L66 _prototype_ `int sp_Copy(stackP, stackP);`
- L68 _prototype_ `int sp_CopyContent(stackP stackDst, stackP stackSrc);`
- L69 _prototype_ `stackP sp_Duplicate(stackP theStack);`
- L71 _macro_ `#define sp_GetCapacity(theStack) (theStack->capacity)`
- L73 _macro_ `#define sp_Push(theStack, a) { if (sp__Push(theStack, (a)) != OK) return NOTOK; }`
- L74 _macro_ `#define sp_Push2(theStack, a, b) { if (sp__Push2(theStack, (a), (b)) != OK) return NOTOK; }`
- L76 _macro_ `#define sp_Pop(theStack, a) { if (sp__Pop(theStack, &(a)) != OK) return NOTOK; }`
- L77 _macro_ `#define sp_Pop2(theStack, a, b) { if (sp__Pop2(theStack, &(a), &(b)) != OK) return NOTOK; }`
- L79 _function_ `inline int sp_ClearStack(stackP theStack)`
- L85 _function_ `inline int sp_GetCurrentSize(stackP theStack)`
- L90 _function_ `inline int sp_SetCurrentSize(stackP theStack, int size)`
- L95 _function_ `inline int sp_IsEmpty(stackP theStack)`
- L100 _function_ `inline int sp_NonEmpty(stackP theStack)`
- L105 _function_ `inline int sp__Push(stackP theStack, int a)`
- L114 _function_ `inline int sp__Push2(stackP theStack, int a, int b)`
- L124 _function_ `inline int sp__Pop(stackP theStack, int *pA)`
- L133 _function_ `inline int sp__Pop2(stackP theStack, int *pA, int *pB)`
- L144 _function_ `inline int sp_Top(stackP theStack)`
- L149 _function_ `inline int sp_Get(stackP theStack, int pos)`
- L157 _function_ `inline int sp_Set(stackP theStack, int pos, int val)`

### `Source/Developer/GraphColor/Public/GraphColor.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `void GraphColorMesh( TArray< uint8 >& VertColors, const TArray< uint32 >& Indexes );`
