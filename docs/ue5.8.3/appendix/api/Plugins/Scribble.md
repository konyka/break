# Plugins / Scribble

- module root: `Plugins/Experimental/Animation/Scribble/Source/Scribble`
- headers: 4; symbols: 165
- symbol kinds: class=1, delegate=3, enum=3, enumerator=7, externvar=1, function=43, macro=5, member=35, namespace=1, prototype=59, struct=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: DeveloperSettings

### `Plugins/Experimental/Animation/Scribble/Source/Scribble/Public/ScribbleGraph.h` (Public)


#### struct `FScribbleGraphData`  
`struct FScribbleGraphData : public TSharedFromThis<FScribbleGraphData>`  
_L22-94_
- inherits: `TSharedFromThis<FScribbleGraphData>`
- desc: The backing data for a scribble graph. Given we want this to be used as a TSharedPtr it's separated from the UStruct graph. This is used for the data backend only and corresponds with the UScribbleEdGraphNode as well as the SScribbleGraphNode.
- L26 _public function_ `FScribbleGraphData() : ViewOffset(FVector2f::ZeroVector) , ZoomAmount(1.f) , ChangeBracket(0) , AccumulatedChanges(0)`
- L34 _public prototype_ `void Reset();`
- L35 _public prototype_ `bool IsEmpty() const;`
- L36 _public prototype_ `int32 NumNodes() const;`
- L37 _public prototype_ `FScribbleNode* GetNode(int32 InNodeIndex);`
- L38 _public prototype_ `const FScribbleNode* GetNode(int32 InNodeIndex) const;`
- L39 _public prototype_ `TSharedPtr<FScribbleNode> GetNodePtr(int32 InNodeIndex) const;`
- L40 _public prototype_ `FScribbleNode* FindNode(const FGuid& InId);`
- L41 _public prototype_ `const FScribbleNode* FindNode(const FGuid& InId) const;`
- L42 _public prototype_ `TSharedPtr<FScribbleNode> FindNodePtr(const FGuid& InId) const;`
- L43 _public prototype_ `FScribbleNode* operator[](int32 InNodeIndex);`
- L44 _public prototype_ `const FScribbleNode* operator[](int32 InNodeIndex) const;`
- L45 _public function_ `TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType begin()`
- L46 _public function_ `TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType end()`
- L47 _public function_ `TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType begin() const`
- L48 _public function_ `TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType end() const`
- L50 _public prototype_ `FGuid AddNode(const TSharedPtr<FScribbleNode>& InNode);`
- L51 _public prototype_ `bool RemoveNode(const TSharedPtr<FScribbleNode>& InNode);`
- L52 _public prototype_ `bool RemoveNode(const FGuid& InId);`
- L54 _public prototype_ `bool SupportsAnchors() const;`
- L55 _public prototype_ `FName GetCurrentAnchor() const;`
- L56 _public prototype_ `TOptional<FVector2f> ResolveAnchor(const FName& InName) const;`
- L58 _public prototype_ `TSharedPtr<FScribbleNode> GroupNodes(const TArray<TSharedPtr<FScribbleNode>>& InNodes);`
- L59 _public prototype_ `TArray<TSharedPtr<FScribbleNode>> UngroupNode(const TSharedPtr<FScribbleNode>& InNode);`
- L61 _public function_ `FSimpleMulticastDelegate& OnModify()`
- L62 _public function_ `FSimpleMulticastDelegate& OnChanged()`
- L63 _public function_ `FScribbleGetCurrentAnchor& OnGetCurrentAnchor()`
- L64 _public function_ `FScribbleResolveAnchor& OnResolveAnchor()`
- L66 _public prototype_ `bool Serialize(FArchive& Ar);`
- L67 _public prototype_ `void Modify();`
- L69 _public function_ `const FVector2f& GetViewOffset() const`
- L70 _public function_ `float GetZoomAmount() const`
- L71 _public prototype_ `void SetView(const FVector2f& InViewOffset, float InZoomAmount);`
- L75 _protected prototype_ `void IncrementChangeBracket();`
- L76 _protected prototype_ `void DecrementChangeBracket();`
- L77 _protected prototype_ `void NotifyChanged();`
- L79 _protected member_ `FVector2f ViewOffset;`
- L80 _protected member_ `float ZoomAmount;`
- L82 _protected member_ `TArray<TSharedPtr<FScribbleNode>> Nodes;`
- L83 _protected member_ `TMap<FGuid, TSharedPtr<FScribbleNode>> GuidToNode;`
- L84 _protected member_ `FSimpleMulticastDelegate OnModifyEvent;`
- L85 _protected member_ `FSimpleMulticastDelegate OnChangedEvent;`
- L86 _protected member_ `FScribbleGetCurrentAnchor GetCurrentAnchorDelegate;`
- L87 _protected member_ `FScribbleResolveAnchor ResolveAnchorDelegate;`
- L89 _protected member_ `int32 ChangeBracket;`
- L90 _protected member_ `int32 AccumulatedChanges;`

#### struct `FScribbleGraph`  
`struct FScribbleGraph`  
_L100-129_
- reflection: `USTRUCT()`
- desc: The Scribbe graph struct used mainly for serialization and as a data type for UPROPERTY macros.
- L106 _public function_ `FScribbleGraph()`
- L110 _public prototype_ `void Reset();`
- L111 _public prototype_ `bool IsValid() const;`
- L112 _public prototype_ `FScribbleGraphData* GetData();`
- L113 _public prototype_ `const FScribbleGraphData* GetData() const;`
- L114 _public function_ `TSharedPtr<FScribbleGraphData> GetDataPtr() const`
- L115 _public prototype_ `TSharedPtr<FScribbleGraphData> GetOrCreateDataPtr();`
- L117 _public prototype_ `bool Serialize(FArchive& Ar);`
- L118 _public prototype_ `bool Identical(const FScribbleGraph* Other, uint32 PortFlags) const;`
- L128 _private member_ `TSharedPtr<FScribbleGraphData> Data;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FScribbleGraph> : public TStructOpsTypeTraitsBase2<FScribbleGraph>`  
_L132-140_
- inherits: `TStructOpsTypeTraitsBase2<FScribbleGraph>`
- L139 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L135-138_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCRIBBLE_API`
- L11 _externvar_ `extern TAutoConsoleVariable<bool> CVarScribbleEnabled;`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal(FName, FScribbleGetCurrentAnchor) DECLARE_DELEGATE_RetVal_OneParam(TOptional<FVector2f>, FScribbleResolveAnchor, const FName&) struct FScribbleGraphData : public TSharedFromThis<FScribbleGraphData> { public: FScribbleGraphData() : ViewOffset(FVector2f::ZeroVector) , ZoomAmount(1.f) , ChangeBracket(0) , AccumulatedChanges(0) { } void Reset(); bool IsEmpty() const; int32 NumNodes() const; FScribbleNode* GetNode(int32 InNodeIndex); const FScribbleNode* GetNode(int32 InNodeIndex) const; TSharedPtr<FScribbleNode> GetNodePtr(int32 InNodeIndex) const; FScribbleNode* FindNode(const FGuid& InId); const FScribbleNode* FindNode(const FGuid& InId) const; TSharedPtr<FScribbleNode> FindNodePtr(const FGuid& InId) const; FScribbleNode* operator[](int32 InNodeIndex); const FScribbleNode* operator[](int32 InNodeIndex) const; TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType begin() { return Nodes.begin(); } TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType end() { return Nodes.end(); } TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType begin() const { return Nodes.begin(); } TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType end() const { return Nodes.end(); } FGuid AddNode(const TSharedPtr<FScribbleNode>& InNode); bool RemoveNode(const TSharedPtr<FScribbleNode>& InNode); bool RemoveNode(const FGuid& InId);`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FVector2f>, FScribbleResolveAnchor, const FName&) struct FScribbleGraphData : public TSharedFromThis<FScribbleGraphData> { public: FScribbleGraphData() : ViewOffset(FVector2f::ZeroVector) , ZoomAmount(1.f) , ChangeBracket(0) , AccumulatedChanges(0) { } void Reset(); bool IsEmpty() const; int32 NumNodes() const; FScribbleNode* GetNode(int32 InNodeIndex); const FScribbleNode* GetNode(int32 InNodeIndex) const; TSharedPtr<FScribbleNode> GetNodePtr(int32 InNodeIndex) const; FScribbleNode* FindNode(const FGuid& InId); const FScribbleNode* FindNode(const FGuid& InId) const; TSharedPtr<FScribbleNode> FindNodePtr(const FGuid& InId) const; FScribbleNode* operator[](int32 InNodeIndex); const FScribbleNode* operator[](int32 InNodeIndex) const; TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType begin() { return Nodes.begin(); } TArray<TSharedPtr<FScribbleNode>>::RangedForIteratorType end() { return Nodes.end(); } TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType begin() const { return Nodes.begin(); } TArray<TSharedPtr<FScribbleNode>>::RangedForConstIteratorType end() const { return Nodes.end(); } FGuid AddNode(const TSharedPtr<FScribbleNode>& InNode); bool RemoveNode(const TSharedPtr<FScribbleNode>& InNode); bool RemoveNode(const FGuid& InId);`
- L120 _function_ `friend FArchive& operator<<(FArchive& Ar, FScribbleGraph& P)`
- L136 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon4679e2590103`) — struct has a Serialize function for serializing its state to an FArchive.
- L137 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon4679e2590103`) — struct can be compared via an Identical(const T* Other, uint32 PortFlags) function.

### `Plugins/Experimental/Animation/Scribble/Source/Scribble/Public/ScribbleNode.h` (Public)


#### enum `EScribbleNodeType::Type`  
`enum Type : uint8`  
_L52-56_
- L54 _public enumerator_ `Invalid`
- L55 _public enumerator_ `LineStrip`

#### struct `FScribbleNode`  
`struct FScribbleNode`  
_L64-220_
- reflection: `USTRUCT()`
- desc: A node in a scribble graph. This is used for the data backend only and corresponds with the UScribbleEdGraphNode as well as the SScribbleGraphNode.
- L70 _public function_ `FScribbleNode() : Type(EScribbleNodeType::Invalid) , Guid(FGuid()) , Anchor(NAME_None) , Position(FVector2f::ZeroVector) , RelativePosition(FVector2f::ZeroVector) , Size(1,1) , ChangeBracket(0) , AccumulatedChanges(0)`
- L82 _public function_ `FScribbleNode(const EScribbleNodeType::Type& InType) : Type(InType) , Guid(FGuid::NewGuid()) , Anchor(NAME_None) , Position(FVector2f::ZeroVector) , RelativePosition(FVector2f::ZeroVector) , Size(1,1) , ChangeBracket(0) , AccumulatedChanges(0)`
- L94 _public function_ `virtual ~FScribbleNode()`
- L98 _public function_ `const EScribbleNodeType::Type GetType() const`
- L99 _public function_ `const FGuid& GetId() const`
- L100 _public function_ `const FName& GetAnchor() const`
- L101 _public prototype_ `void SetAnchor(const FName& InAnchor);`
- L103 _public prototype_ `FVector2f GetPosition(bool bResolveAnchor = true) const;`
- L104 _public function_ `const FVector2f& GetRelativePosition() const`
- L105 _public prototype_ `void SetPosition(const FVector2f& InPosition);`
- L106 _public function_ `virtual void OffsetPosition(const FVector2f& InNewPosition)`
- L107 _public function_ `virtual FBox2f GetContentBounds() const`
- L108 _public function_ `const FVector2f& GetSize() const`
- L109 _public prototype_ `void SetSize(const FVector2f& InSize);`
- L110 _public function_ `virtual bool DownSample(float InPrecision)`
- L112 _public prototype_ `virtual bool Serialize(FArchive& Ar);`
- L113 _public prototype_ `virtual bool Identical(const FScribbleNode* Other, uint32 PortFlags) const;`
- L115 _public function_ `FScribbleNodeDimensionsChanged& OnPositionChanged()`
- L116 _public function_ `FScribbleNodeDimensionsChanged& OnSizeChanged()`
- L119 _public prototype_ `virtual int32 OnPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bSelected, float InZoomAmount) const;`
- L120 _public function_ `virtual bool AppendMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const FVector2f& InPanelPosition)`
- L121 _public function_ `virtual bool IntersectsCursorPosition(const FVector2f& InLocalPosition) const`
- L124 _public function_ `static bool IsClassOf(const FScribbleNode* InNode)`
- L129 _public function_ `virtual UScriptStruct* GetScriptStruct() const`
- L131 _public function_ `bool IsA(const UScriptStruct* InScriptStruct) const`
- L137 _public function_ `template<typename T> bool IsA() const`
- L181 _public prototype_ `const FScribbleGraphData* GetGraph() const;`
- L182 _public prototype_ `FScribbleGraphData* GetGraph();`
- L186 _protected prototype_ `void Modify();`
- L187 _protected prototype_ `void IncrementChangeBracket();`
- L188 _protected prototype_ `void DecrementChangeBracket();`
- L189 _protected prototype_ `void NotifyGraphChanged();`
- L191 _protected prototype_ `void UpdateRelativePosition(const FVector2f& InAbsolutePosition);`
- L194 _protected member_ `TEnumAsByte<EScribbleNodeType::Type> Type;` — `UPROPERTY()`
- L197 _protected member_ `FGuid Guid;` — `UPROPERTY()`
- L200 _protected member_ `FName Anchor;` — `UPROPERTY()`
- L203 _protected member_ `FVector2f Position;` — `UPROPERTY()`
- L206 _protected member_ `FVector2f RelativePosition;` — `UPROPERTY()`
- L209 _protected member_ `FVector2f Size;` — `UPROPERTY()`
- L211 _protected member_ `TWeakPtr<FScribbleGraphData> WeakGraph;`
- L212 _protected member_ `FScribbleNodeDimensionsChanged PositionChangedEvent;`
- L213 _protected member_ `FScribbleNodeDimensionsChanged SizeChangedEvent;`
- L215 _protected member_ `int32 ChangeBracket;`
- L216 _protected member_ `int32 AccumulatedChanges;`

#### struct `FScribbleLineStrip`  
`struct FScribbleLineStrip`  
_L223-252_
- reflection: `USTRUCT()`
- L229 _public function_ `FScribbleLineStrip() : Thickness(1.f) , Color(FLinearColor::White)`
- L236 _public member_ `TArray<FVector2f> Vertices;` — `UPROPERTY(EditAnywhere, Category=Scribble)`
- L239 _public member_ `float Thickness;` — `UPROPERTY(EditAnywhere, Category=Scribble)`
- L242 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category=Scribble)`
- L244 _public prototype_ `bool Serialize(FArchive& Ar);`
- L245 _public prototype_ `bool Identical(const FScribbleLineStrip* Other, uint32 PortFlags) const;`

#### struct `FLineStripScribbleNode`  
`struct FLineStripScribbleNode : public FScribbleNode`  
_L255-282_
- reflection: `USTRUCT()`
- inherits: `FScribbleNode`
- L260 _public function_ `FLineStripScribbleNode() : FScribbleNode(EScribbleNodeType::LineStrip)`
- L266 _public member_ `TArray<FScribbleLineStrip> LineStrips;` — `UPROPERTY(EditAnywhere, Category=Scribble)`
- L268 _public prototype_ `virtual bool Serialize(FArchive& Ar) override;`
- L269 _public prototype_ `virtual bool Identical(const FScribbleNode* Other, uint32 PortFlags) const override;`
- L270 _public prototype_ `virtual void OffsetPosition(const FVector2f& InNewPosition) override;`
- L271 _public prototype_ `virtual bool DownSample(float InPrecision) override;`
- L272 _public prototype_ `virtual FBox2f GetContentBounds() const override;`
- L275 _public prototype_ `virtual int32 OnPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bSelected, float InZoomAmount) const override;`
- L276 _public prototype_ `virtual bool AppendMouseEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const FVector2f& InPanelPosition) override;`
- L277 _public prototype_ `virtual bool IntersectsCursorPosition(const FVector2f& InLocalPosition) const override;`
- L279 _public member_ `mutable TArray<FSlateVertex> VertexBuffer;`
- L280 _public member_ `mutable TArray<SlateIndex> IndexBuffer;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SCRIBBLE_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FScribbleNodeDimensionsChanged, const FVector2f&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FScribbleNodeDimensionsChanged, const FVector2f&);`
- L22 _macro_ `#define DECLARE_SCRIBBLE_NODE_METHODS(ScribbleNodeType) \`
- L50 _namespace_ `namespace EScribbleNodeType`
- L140 _function_ `template<typename T> friend const T* Cast(const FScribbleNode* InNode)`
- L153 _function_ `template<typename T> friend T* Cast(FScribbleNode* InNode)`
- L166 _function_ `template<typename T> friend const T* CastChecked(const FScribbleNode* InNode)`
- L174 _function_ `template<typename T> friend T* CastChecked(FScribbleNode* InNode)`
- L247 _function_ `friend FArchive& operator<<(FArchive& Ar, FScribbleLineStrip& P)`

### `Plugins/Experimental/Animation/Scribble/Source/Scribble/Public/ScribbleObjectVersion.h` (Public)


#### struct `FScribbleObjectVersion`  
`struct FScribbleObjectVersion`  
_L10-27_
- desc: Custom serialization version for scribble plugin
- L23 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L26 _private function_ `FScribbleObjectVersion()`

#### enum `FScribbleObjectVersion::Type`  
`enum Type`  
_L12-20_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded` — Before any version changes were made
- L18 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L19 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCRIBBLE_API`

### `Plugins/Experimental/Animation/Scribble/Source/Scribble/Public/ScribbleSettings.h` (Public)


#### class `UScribbleEditorSettings`  
`class UScribbleEditorSettings : public UDeveloperSettings`  
_L20-70_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta=(DisplayName="Scribble"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Default Scribble settings.
- L30 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, config, Category = Scribble)` — The color used for shapes
- L34 _public member_ `FLinearColor SelectionColor;` — `UPROPERTY(EditAnywhere, config, Category = Scribble)` — The color used to represent selection
- L38 _public member_ `FLinearColor AnchorColor;` — `UPROPERTY(EditAnywhere, config, Category = Scribble)` — The color used to draw the anchor line
- L42 _public member_ `float Thickness;` — `UPROPERTY(EditAnywhere, config, Category = Scribble)` — The thickness used for lines
- L46 _public member_ `float Precision;` — `UPROPERTY(EditAnywhere, config, Category = Scribble)` — Defines how exact lines are - and how small the smallest possible node is going to be
- L52 _public prototype_ `float GetSmoothing() const;`
- L53 _public prototype_ `void SetSmoothing(float InValue);`
- L55 _public function_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)`
- L69 _public function_ `static UScribbleEditorSettings* Get()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCRIBBLE_API`
