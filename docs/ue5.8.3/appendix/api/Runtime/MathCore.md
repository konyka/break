# Runtime / MathCore

- module root: `Source/Runtime/MathCore`
- headers: 1; symbols: 20
- symbol kinds: member=3, namespace=3, prototype=10, struct=2, typedef=2
- PublicDependencyModuleNames: Core

### `Source/Runtime/MathCore/Public/Graph/DirectedGraphUtils.h` (Public)


#### struct `UE::MathCore::Graph::FStronglyConnectedComponent`  
`struct FStronglyConnectedComponent`  
_L18-25_
- desc: A strongly connected component contains a subgraph of strongly connected vertices and their corresponding edges.
- L21 _public member_ `TArray<int32> Vertices;` — Vertices in the strongly connected component.
- L24 _public member_ `TArray<FDirectedEdge> Edges;` — Edges in the strongly connected component.

#### struct `UE::MathCore::Graph::FDirectedTreeElement`  
`struct FDirectedTreeElement`  
_L28-31_
- desc: An element in a directed tree with references to children of a vertex.
- L30 _public member_ `TArray<int32> Children;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MathCore` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::MathCore`)
- L13 _typedef_ `using FDirectedEdge = TTuple<int32, int32>;` (scope `UE::MathCore::Graph`) — A pair of int32s represent a directed edge. The first value represents the source vertex, and the second value represents the destination vertex.
- L34 _typedef_ `using FDirectedTree = TMap<int32, FDirectedTreeElement>;` (scope `UE::MathCore::Graph`) — A directed tree graph representation.
- L42 _prototype_ `void BuildDirectedTree(TArrayView<const FDirectedEdge> InEdges, FDirectedTree& OutTree);` (scope `UE::MathCore::Graph`) — Build a directed tree from an array of edges. @parma InEdges - An array of directed edges. @param OutTree - A tree structure built from the edges.
- L51 _prototype_ `void BuildTransposeDirectedTree(TArrayView<const FDirectedEdge> InEdges, FDirectedTree& OutTree);` (scope `UE::MathCore::Graph`) — Build a transpose directed tree from an array of edges. The transpose of a directed graph is created by reversing each edge. @parma InEdges - An array of directed edges. @param OutTree - A tree structure built from the reversed edges.
- L63 _prototype_ `void DepthFirstNodeTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool(int32)> InVisitFunc);` (scope `UE::MathCore::Graph`) — Traverse a tree in a depth first ordering. Does not traverse the same node twice @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each vertex that is visited. If this function returns true, traversal is continued in a depth first manner. If this function returns false, the children of the current vertex are not visited.
- L75 _prototype_ `void DepthFirstEdgeTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool(int32, int32)> InVisitFunc);` (scope `UE::MathCore::Graph`) — Traverse a tree in a depth first ordering. Does not traverse the same edge twice @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each edge that is visited. If this function returns true, the children of this edge's destination vertex will be visited in the future. If this function returns false, then the children will not be visited (unless reaching the node via another route).
- L88 _prototype_ `void BreadthFirstNodeTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool(int32)> InVisitFunc);` (scope `UE::MathCore::Graph`) — Traverse a tree in a breadth first ordering. Does not traverse the same node twice @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each vertex that is visited. If this function returns true, the children of this vertex will be visited in the future. If this function returns false, then the children of the current vertex will not be visited.
- L100 _prototype_ `void BreadthFirstEdgeTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool(int32, int32)> InVisitFunc);` (scope `UE::MathCore::Graph`) — Traverse a tree in a breadth first ordering. Does not traverse the same edge twice @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each edge that is visited. If this function returns true, the children of this edge's destination vertex will be visited in the future. If this function returns false, then the children will not be visited (unless reaching the node via another route).
- L108 _prototype_ `void FindLeaves(int32 InInitialVertex, const FDirectedTree& InTree, TArray<int32>& OutLeafVertices);` (scope `UE::MathCore::Graph`) — Returns all leaves (vertex with no children) connected with the starting vertex @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param OutLeafVertices - List of all leaf vertices connected to the starting vertex
- L118 _prototype_ `bool DepthFirstTopologicalSort(TArrayView<const int32> InUniqueVertices, TArrayView<const FDirectedEdge> InUniqueEdges, TArray<int32>& OutVertexOrder);` (scope `UE::MathCore::Graph`) — Sort vertices topologically using a depth first sorting algorithm. @param InUniqueVertices - An array of vertices to sort. @param InUniqueEdges - An array of edges describing dependencies. @param OutVertexOrder - An array where ordered vertices are placed. @return True if sorting was successful. False otherwise.
- L128 _prototype_ `bool KahnTopologicalSort(TArrayView<const int32> InUniqueVertices, TArrayView<const FDirectedEdge> InUniqueEdges, TArray<int32>& OutVertexOrder);` (scope `UE::MathCore::Graph`) — Sort vertices topologically using a Kahn's sorting algorithm. @param InUniqueVertices - An array of vertices to sort. @param InUniqueEdges - An array of edges describing dependencies. @param OutVertexOrder - An array where ordered vertices are placed. @return True if sorting was successful. False otherwise.
- L140 _prototype_ `bool TarjanStronglyConnectedComponents(const TSet<FDirectedEdge>& InEdges, TArray<FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` (scope `UE::MathCore::Graph`) — Find strongly connected components given a set of edges using Tarjan algorithm. @param InEdges - Edges in the directed graph. @param OutComponents - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.
