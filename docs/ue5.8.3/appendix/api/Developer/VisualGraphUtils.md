# Developer / VisualGraphUtils

- module root: `Source/Developer/VisualGraphUtils`
- headers: 7; symbols: 109
- symbol kinds: class=6, enum=3, enumerator=19, function=28, macro=5, member=19, prototype=29
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine

### `Source/Developer/VisualGraphUtils/Public/VisualGraph.h` (Public)


#### class `FVisualGraphSubGraph`  
`class FVisualGraphSubGraph : public FVisualGraphElement`  
_L22-44_
- inherits: `FVisualGraphElement`
- L26 _public function_ `FVisualGraphSubGraph() : FVisualGraphElement() , ParentGraphIndex(INDEX_NONE)`
- L31 _public prototype_ `virtual ~FVisualGraphSubGraph() override = default;`
- L33 _public function_ `int32 GetParentGraphIndex() const`
- L34 _public function_ `const TArray<int32>& GetNodes() const`
- L38 _protected prototype_ `virtual FString DumpDot(const FVisualGraph* InGraph, int32 InIndendation) const override;`
- L40 _protected member_ `int32 ParentGraphIndex;`
- L41 _protected member_ `TArray<int32> Nodes;`

#### class `FVisualGraph`  
`class FVisualGraph : public FVisualGraphElement`  
_L46-146_
- inherits: `FVisualGraphElement`
- L50 _public function_ `FVisualGraph() : FVisualGraphElement()`
- L54 _public prototype_ `virtual ~FVisualGraph() override = default;`
- L56 _public prototype_ `FVisualGraph(const FName& InName, const FName& InDisplayName = NAME_None);`
- L58 _public function_ `const TArray<FVisualGraphNode>& GetNodes() const`
- L59 _public function_ `const TArray<FVisualGraphEdge>& GetEdges() const`
- L60 _public function_ `const TArray<FVisualGraphSubGraph>& GetSubGraphs() const`
- L62 _public prototype_ `int32 AddNode( const FName& InName, TOptional<FName> InDisplayName = TOptional<FName>(), TOptional<FLinearColor> InColor = TOptional<FLinearColor>(), TOptional<EVisualGraphShape> InShape = TOptional<EVisualGraphShape>(), TOptional<EVisualGraphStyle> InStyle = TOptional<EVisualGraphStyle>());`
- L69 _public prototype_ `int32 AddEdge( int32 InSourceNode, int32 InTargetNode, EVisualGraphEdgeDirection InDirection, const FName& InName = NAME_None, TOptional<FName> InDisplayName = TOptional<FName>(), TOptional<FLinearColor> InColor = TOptional<FLinearColor>(), TOptional<EVisualGraphStyle> InStyle = TOptional<EVisualGraphStyle>());`
- L78 _public prototype_ `int32 AddSubGraph( const FName& InName, TOptional<FName> InDisplayName = TOptional<FName>(), int32 InParentGraphIndex = INDEX_NONE, TOptional<FLinearColor> InColor = TOptional<FLinearColor>(), TOptional<EVisualGraphStyle> InStyle = TOptional<EVisualGraphStyle>(), const TArray<int32> InNodes = TArray<int32>());`
- L86 _public prototype_ `int32 FindNode(const FName& InName) const;`
- L87 _public prototype_ `int32 FindEdge(const FName& InName) const;`
- L88 _public prototype_ `int32 FindSubGraph(const FName& InName) const;`
- L90 _public prototype_ `bool AddNodeToSubGraph(int32 InNodeIndex, int32 InSubGraphIndex);`
- L91 _public prototype_ `bool RemoveNodeFromSubGraph(int32 InNodeIndex);`
- L93 _public prototype_ `void TransitiveReduction(TFunction<bool(FVisualGraphEdge&)> KeepEdgeFunction);`
- L95 _public function_ `FORCEINLINE FString DumpDot() const`
- L102 _protected prototype_ `virtual FString DumpDot(const FVisualGraph* InGraph, int32 InIndendation) const override;`
- L105 _protected function_ `template<typename T> FORCEINLINE static void RefreshNameMap(const TArray<T>& InElements, TMap<FName, int32>& OutMap)`
- L115 _protected function_ `template<typename T> FORCEINLINE static void RefreshNameMapIfNeeded(const TArray<T>& InElements, TMap<FName, int32>& OutMap)`
- L125 _protected function_ `template<typename T> FORCEINLINE static int32 AddElement(const T& InElement, TArray<T>& OutElements, TMap<FName, int32>& OutMap)`
- L136 _protected prototype_ `static bool IsNameAvailable(const FName& InName, const TMap<FName, int32>& InMap);`
- L137 _protected prototype_ `static FName GetUniqueName(const FName& InName, const TMap<FName, int32>& InMap);`
- L139 _protected member_ `TArray<FVisualGraphNode> Nodes;`
- L140 _protected member_ `TArray<FVisualGraphEdge> Edges;`
- L141 _protected member_ `TArray<FVisualGraphSubGraph> SubGraphs;`
- L143 _protected member_ `TMap<FName,int32> NodeNameMap;`
- L144 _protected member_ `TMap<FName,int32> EdgeNameMap;`
- L145 _protected member_ `TMap<FName,int32> SubGraphNameMap;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API VISUALGRAPHUTILS_API`

### `Source/Developer/VisualGraphUtils/Public/VisualGraphEdge.h` (Public)


#### enum `EVisualGraphEdgeDirection`  
`enum class EVisualGraphEdgeDirection : uint8`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `SourceToTarget`
- L20 _public enumerator_ `TargetToSource`
- L21 _public enumerator_ `BothWays`

#### class `FVisualGraphEdge`  
`class FVisualGraphEdge : public FVisualGraphElement`  
_L24-49_
- inherits: `FVisualGraphElement`
- L28 _public function_ `FVisualGraphEdge() : FVisualGraphElement() , Direction(EVisualGraphEdgeDirection::SourceToTarget)`
- L33 _public prototype_ `virtual ~FVisualGraphEdge() override = default;`
- L35 _public function_ `int32 GetSourceNode() const`
- L36 _public function_ `int32 GetTargetNode() const`
- L37 _public function_ `EVisualGraphEdgeDirection GetDirection() const`
- L41 _protected prototype_ `virtual FString DumpDot(const FVisualGraph* InGraph, int32 InIndendation) const override;`
- L43 _protected member_ `int32 SourceNode;`
- L44 _protected member_ `int32 TargetNode;`
- L45 _protected member_ `EVisualGraphEdgeDirection Direction;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API VISUALGRAPHUTILS_API`

### `Source/Developer/VisualGraphUtils/Public/VisualGraphElement.h` (Public)


#### enum `EVisualGraphShape`  
`enum class EVisualGraphShape : uint8`  
_L22-33_
- reflection: `UENUM()`
- L24 _public enumerator_ `Box`
- L25 _public enumerator_ `Polygon`
- L26 _public enumerator_ `Ellipse`
- L27 _public enumerator_ `Circle`
- L28 _public enumerator_ `Triangle`
- L29 _public enumerator_ `PlainText`
- L30 _public enumerator_ `Diamond`
- L31 _public enumerator_ `Parallelogram`
- L32 _public enumerator_ `House`

#### enum `EVisualGraphStyle`  
`enum class EVisualGraphStyle : uint8`  
_L36-45_
- reflection: `UENUM()`
- L38 _public enumerator_ `Filled`
- L39 _public enumerator_ `Diagonals`
- L40 _public enumerator_ `Rounded`
- L41 _public enumerator_ `Dashed`
- L42 _public enumerator_ `Dotted`
- L43 _public enumerator_ `Solid`
- L44 _public enumerator_ `Bold`

#### class `FVisualGraphElement`  
`class FVisualGraphElement`  
_L47-87_
- L51 _public function_ `FVisualGraphElement() : Name(NAME_None) , DisplayName() , Index(INDEX_NONE) , Color() , Style()`
- L59 _public prototype_ `virtual ~FVisualGraphElement() = default;`
- L61 _public function_ `FName GetName() const`
- L62 _public function_ `FName GetDisplayName() const`
- L63 _public function_ `TOptional<FString> GetTooltip() const`
- L64 _public function_ `void SetTooltip(const FString& InTooltip) const`
- L65 _public function_ `int32 GetIndex() const`
- L66 _public function_ `TOptional<FLinearColor> GetColor() const`
- L67 _public function_ `void SetColor(FLinearColor InValue)`
- L68 _public function_ `TOptional<EVisualGraphStyle> GetStyle() const`
- L69 _public function_ `void SetStyle(EVisualGraphStyle InValue)`
- L73 _protected prototype_ `virtual FString DumpDot(const FVisualGraph* InGraph, int32 InIndendation) const = 0;`
- L74 _protected prototype_ `static FString DumpDotIndentation(int32 InIndentation);`
- L75 _protected prototype_ `static FString DumpDotColor(const TOptional<FLinearColor>& InColor);`
- L76 _protected prototype_ `static FString DumpDotShape(const TOptional<EVisualGraphShape>& InShape);`
- L77 _protected prototype_ `static FString DumpDotStyle(const TOptional<EVisualGraphStyle>& InStyle);`
- L79 _protected member_ `FName Name;`
- L80 _protected member_ `TOptional<FName> DisplayName;`
- L81 _protected member_ `mutable TOptional<FString> Tooltip;`
- L82 _protected member_ `int32 Index;`
- L83 _protected member_ `TOptional<FLinearColor> Color;`
- L84 _protected member_ `TOptional<EVisualGraphStyle> Style;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API VISUALGRAPHUTILS_API`

### `Source/Developer/VisualGraphUtils/Public/VisualGraphNode.h` (Public)


#### class `FVisualGraphNode`  
`class FVisualGraphNode : public FVisualGraphElement`  
_L15-39_
- inherits: `FVisualGraphElement`
- L19 _public function_ `FVisualGraphNode() : FVisualGraphElement() , Shape() , SubGraphIndex(INDEX_NONE)`
- L25 _public prototype_ `virtual ~FVisualGraphNode() override = default;`
- L27 _public function_ `TOptional<EVisualGraphShape> GetShape() const`
- L28 _public function_ `void SetShape(EVisualGraphShape InValue)`
- L32 _protected prototype_ `virtual FString DumpDot(const FVisualGraph* InGraph, int32 InIndendation) const override;`
- L34 _protected member_ `TOptional<EVisualGraphShape> Shape;`
- L35 _protected member_ `int32 SubGraphIndex;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VISUALGRAPHUTILS_API`

### `Source/Developer/VisualGraphUtils/Public/VisualGraphObjectUtils.h` (Public)


#### class `FVisualGraphObjectUtils`  
`class FVisualGraphObjectUtils`  
_L13-30_
- L17 _public prototype_ `static FVisualGraph TraverseUObjectReferences( const TArray<UObject*>& InObjects, const TArray<UClass*>& InClassesToSkip = TArray<UClass*>(), const TArray<UObject*>& InOutersToSkip = TArray<UObject*>(), const TArray<UObject*>& InOutersToUse = TArray<UObject*>(), bool bTraverseObjectsInOuter = true, bool bCollectReferencesBySerialize = true, bool bRecursive = true );`
- L27 _public prototype_ `static FVisualGraph TraverseTickOrder( const TArray<UObject*>& InObjects );`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VISUALGRAPHUTILS_API`

### `Source/Developer/VisualGraphUtils/Public/VisualGraphUtils.h` (Public)
_(no declarations extracted)_

### `Source/Developer/VisualGraphUtils/Public/VisualGraphUtilsModule.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVisualGraphUtils, Log, All);`
