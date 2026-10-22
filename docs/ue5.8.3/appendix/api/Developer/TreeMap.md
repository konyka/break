# Developer / TreeMap

- module root: `Source/Developer/TreeMap`
- headers: 5; symbols: 177
- symbol kinds: class=8, delegate=1, enum=1, enumerator=2, function=15, macro=2, member=80, prototype=58, struct=2, typedef=8
- PrivateDependencyModuleNames: InputCore, Slate, XmlParser
- PublicDependencyModuleNames: Core, CoreUObject, SlateCore

### `Source/Developer/TreeMap/Public/ITreeMap.h` (Public)


#### class `FTreeMapAttributeData`  
`class FTreeMapAttributeData`  
_L19-41_
- desc: Stores data for a specific attribute type on a node
- L25 _public member_ `FName Value;` — Value for this data
- L31 _public function_ `FTreeMapAttributeData() : Value( NAME_None )` — Default constructor for FTreeMapAttributeData
- L37 _public function_ `FTreeMapAttributeData( const FName InitValue ) : Value( InitValue )` — Intitialization constructor for FTreeMapAttributeData

#### class `FTreeMapNodeData`  
`class FTreeMapNodeData : public TSharedFromThis<FTreeMapNodeData>`  
_L51-165_
- inherits: `TSharedFromThis<FTreeMapNodeData>`
- desc: Single node in a tree map, which may have any number of child nodes, each with their own children and so on
- L56 _public member_ `FString LogicalName;` — Logical name, if set this is used for comparison
- L59 _public member_ `FString Name;` — Node name display.  When drawing the tree map, this shows up at the top of the inside of the node's rectangle
- L62 _public member_ `FString Name2;` — Node name (line 2).  Left nodes only.  This shows up on the second line of the node, right underneath its name.  Might be drawn in a smaller font by default.
- L65 _public member_ `FString CenterText;` — Center info text.  Leaf nodes only.  This draws right in the center of the node, with a larger font by default
- L73 _public member_ `float Size;` — Size of this node.  This works differently depending on whether the node is a leaf node (no children) or a container node (has children): - Leaf nodes must ALWAYS have a non-zero size. - Container nodes with size of zero will have their size determined automatically by the sum of their child sizes - Container nodes with a non-zero size will override their child sizes and always have the explicitly set size.  Sizes of children will still be used to proportionately scale the size of the child nodes within this container.
- L76 _public member_ `const struct FSlateBrush* BackgroundBrush;` — Background brush for this node's box (optional)
- L79 _public member_ `FLinearColor Color;` — Color for this node.  This will be set automatically unless you use a customization.
- L83 _public member_ `TArray<FString> HashTags;` — Hashtags for this node.  This is just meta-data for the node that may have been loaded from a file.  It is not used by the TreeMap system directly, but you could harvest these tags and convert them into custom attributes if you wanted to!
- L86 _public member_ `TMap< FName, FTreeMapAttributeDataPtr > Attributes;` — Map of attribute name to it's respective bit of data
- L89 _public member_ `FTreeMapNodeData* Parent;` — Back pointer to parent node, or NULL if no parent exists (root node)
- L92 _public member_ `TArray< FTreeMapNodeDataPtr > Children;` — List of child nodes
- L97 _public function_ `FTreeMapNodeData() : Size( 0.0 ), BackgroundBrush( nullptr ), Color( FLinearColor::White ), Parent( NULL )` — Default constructor for FTreeMapNodeData
- L105 _public function_ `bool operator==(const FTreeMapNodeData& Other) const`
- L115 _public function_ `bool operator!=(const FTreeMapNodeData& Other) const`
- L121 _public function_ `bool IsLeafNode() const` — @return Returns true if this is a leaf node
- L127 _public function_ `void CopyNodeInto( FTreeMapNodeData& NodeCopy ) const` — @return Copies this node into another node (not children, though.  The copied node will have no children.)
- L150 _public function_ `FTreeMapNodeDataRef CopyNodeRecursively() const` — @return Returns a copy of this node; all child nodes are copied, too!

#### enum `ETreeMapType`  
`enum class ETreeMapType`  
_L169-176_
- desc: Type of tree map
- L172 _public enumerator_ `Standard` — Plain tree map
- L175 _public enumerator_ `Squarified` — Squarified tree map

#### struct `FTreeMapOptions`  
`struct FTreeMapOptions`  
_L182-241_
- desc: Configuration for a new tree map
- L185 _public member_ `float DisplayWidth;` — Width of whole display area
- L188 _public member_ `float DisplayHeight;` — Height of whole display area
- L191 _public member_ `ETreeMapType TreeMapType;` — Type of tree map
- L195 _public member_ `FSlateFontInfo NameFont;` — Font to use for titles.  This is needed so that we can calculate the amount of padding space needed.  This font will be used for text titles at the root-most level of the tree.  Nested levels get smaller fonts.  This also affects the amount of space reserved for the title area at the top of each node.
- L198 _public member_ `FSlateFontInfo Name2Font;` — Font for second line of text, under the title.  Leaf nodes only.  Usually a bit smaller.  Works just like NameFont
- L201 _public member_ `FSlateFontInfo CenterTextFont;` — Font for any text that's centered inside the middle of the node.  Leaf nodes only.  Usually a bit larger.  Works just like NameFont
- L204 _public member_ `int32 FontSizeChangeBasedOnDepth;` — Number of font sizes to drop with each depth level of the tree
- L207 _public member_ `float TopLevelContainerOuterPadding;` — Padding around the outside of top-level container nodes in the tree
- L210 _public member_ `float NestedContainerOuterPadding;` — Padding around the outside of nested container nodes in the tree
- L213 _public member_ `float ContainerInnerPadding;` — Padding around a set of children inside of containers, under the container's title area
- L216 _public member_ `float MinimumInteractiveNodeSize;` — Minimize size of a tree node that will be allowed to have a title and padding.  Nodes smaller than this will be a simple rectangle.  Doesn't apply to top level nodes.
- L219 _public member_ `float MinimumVisibleNodeSize;` — Minimize size of a tree node that will be drawn at all, below this size it is invisible
- L223 _public function_ `FTreeMapOptions() : DisplayWidth( 1.0f ), DisplayHeight( 1.0f ), TreeMapType( ETreeMapType::Standard ), NameFont( FCoreStyle::Get().GetFontStyle( TEXT( "NormalText" ) ) ), Name2Font( FCoreStyle::Get().GetFontStyle( TEXT( "NormalText" ) ) ), CenterTextFont( FCoreStyle::Get().GetFontStyle( TEXT( "NormalText" ) ) ), FontSizeChangeBasedOnDepth( 1 ), TopLevelContainerOuterPadding( 0.0f ), NestedContainerOuterPadding( 0.0f ), ContainerInnerPadding( 0.0f ), MinimumInteractiveNodeSize( 0.0f ), MinimumVisibleNodeSize( 0.0f )` — Default constructor for FTreeMapOptions that initializes good defaults

#### struct `FTreeMapNodeVisualInfo`  
`struct FTreeMapNodeVisualInfo`  
_L248-269_
- desc: Visual ID for a node, generated by the tree map system
- L251 _public member_ `class FTreeMapNodeData* NodeData;` — Pointer back to the node data this visual was originally created from
- L254 _public member_ `FVector2D Position;` — Position for this node
- L257 _public member_ `FVector2D Size;` — Size for this node
- L260 _public member_ `FLinearColor Color;` — Node color
- L263 _public member_ `FSlateFontInfo NameFont;` — Node fonts
- L264 _public member_ `FSlateFontInfo Name2Font;`
- L265 _public member_ `FSlateFontInfo CenterTextFont;`
- L268 _public member_ `bool bIsInteractive;` — True if the node is 'interactive'.  That is, we have space for the node's title and for it to be clicked on.

#### class `ITreeMap`  
`class ITreeMap`  
_L275-311_
- desc: Public tree map interface
- L287 _public prototype_ `virtual TArray<FTreeMapNodeVisualInfo> GetVisuals() = 0;` — Gets the visuals for this tree map.  Be careful not to destroy the original tree while still using the visual objects, otherwise the back pointers to the original tree nodes will be trash!  Visuals are ordered such that nested visuals appear later in the list than their parents (so they can be drawn back to front, etc.) @return List of visuals
- L297 _public prototype_ `static TSharedRef<ITreeMap> CreateTreeMap( const FTreeMapOptions& Options, const FTreeMapNodeDataRef& RootNodeData );` — Static: Creates a tree map object, given tree node source data @param	Options			Configuration options for this tree map @param	RootNodeData	The source data for the root of the tree @return	The newly-created ITreeMap instance
- L307 _public prototype_ `static FTreeMapNodeDataPtr ParseOPMLToTreeMapData( const FString& OPMLFilePath, FString& OutErrorMessage );` — Parses an OPML XML document and converts the outliner content to tree map node data @param	OPMLFilePath		Path to the OPML file on disk @param	OutErrorMessage		Error message string in the case that something went wrong @return	The root tree node for the parsed data, or an invalid pointer if something went wrong
- L310 _public prototype_ `virtual ~ITreeMap() = default;` — Virtual destructor

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedRef< class FTreeMapAttributeData > FTreeMapAttributeDataRef;`
- L13 _typedef_ `typedef TSharedPtr< class FTreeMapAttributeData > FTreeMapAttributeDataPtr;`
- L45 _typedef_ `typedef TSharedRef< class FTreeMapNodeData > FTreeMapNodeDataRef;`
- L46 _typedef_ `typedef TSharedPtr< class FTreeMapNodeData > FTreeMapNodeDataPtr;`

### `Source/Developer/TreeMap/Public/ITreeMapCustomization.h` (Public)


#### class `FTreeMapAttributeValue`  
`class FTreeMapAttributeValue`  
_L18-46_
- desc: Describes a value for an attribute of a tree node
- L24 _public member_ `FName Name;` — Name of this value
- L27 _public member_ `float NodeSize;` — The node size that this value maps to
- L30 _public member_ `FLinearColor NodeColor;` — The node color that this value maps to
- L36 _public function_ `FTreeMapAttributeValue() : Name(), NodeSize( 1.0f ), NodeColor( FLinearColor::White )` — Default constructor
- L45 _public prototype_ `virtual ~FTreeMapAttributeValue() = default;` — Virtual destructor

#### class `FTreeMapAttribute`  
`class FTreeMapAttribute`  
_L56-84_
- desc: Describes a customized attribute of a tree node
- L62 _public member_ `FName Name;` — Name of this attribute
- L65 _public member_ `TMap< FName, FTreeMapAttributeValuePtr > Values;` — Maps a value name to the data that describes that value
- L68 _public member_ `FTreeMapAttributeValuePtr DefaultValue;` — Default value to use when none is specified on a node
- L74 _public function_ `FTreeMapAttribute() : Name(), Values(), DefaultValue()` — Default constructor
- L82 _public prototype_ `virtual ~FTreeMapAttribute() = default;` — Virtual destructor

#### class `ITreeMapCustomization`  
`class ITreeMapCustomization`  
_L91-118_
- desc: Implement ITreeMapCustomization and pass it along when creating your tree map to allow for custom attributes and formatting features!
- L97 _public prototype_ `virtual FName GetName() const = 0;` — @return Returns the name of this customization
- L100 _public prototype_ `virtual const TMap< FName, FTreeMapAttributePtr >& GetAttributes() const = 0;` — @return Returns all of the possible attributes in this customization.  Each attribute defines a set of possible values for that attribute.
- L103 _public function_ `virtual FTreeMapAttributePtr GetDefaultSizeByAttribute() const` — @return Returns the default attribute type to size the nodes based on
- L106 _public function_ `virtual FTreeMapAttributePtr GetDefaultColorByAttribute() const` — @return Returns the default attribute type to color the nodes based on
- L114 _public function_ `virtual void ProcessHashTagsRecursively( const FTreeMapNodeDataRef& Node ) const` — Optional override that can be called to convert hash tags on tree nodes into proper attribute values.  This is useful if you've loaded tree node data from a file and want to take the raw hash tag strings and make values for those. @param	Node	The root node to process
- L117 _public prototype_ `virtual ~ITreeMapCustomization() = default;` — Virtual destructor

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TSharedPtr< class FTreeMapAttributeValue > FTreeMapAttributeValuePtr;`
- L13 _typedef_ `typedef TSharedRef< class FTreeMapAttributeValue > FTreeMapAttributeValueRef;`
- L50 _typedef_ `typedef TSharedPtr< class FTreeMapAttribute > FTreeMapAttributePtr;`
- L51 _typedef_ `typedef TSharedRef< class FTreeMapAttribute > FTreeMapAttributeRef;`

### `Source/Developer/TreeMap/Public/STreeMap.h` (Public)


#### class `STreeMap`  
`class STreeMap : public SLeafWidget`  
_L25-358_
- inherits: `SLeafWidget`
- desc: Graphical tree map widget with interactive controls
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnTreeMapNodeInteracted, FTreeMapNodeData&, const FPointerEvent& );` — Delegate used when clicking or interacting with a specific node
- L33 _public function_ `SLATE_BEGIN_ARGS( STreeMap ) : _AllowEditing( false ) , _BackgroundImage( FTreeMapStyle::Get().GetBrush( "TreeMap.Background" ) ) , _NodeBackground( FTreeMapStyle::Get().GetBrush( "TreeMap.NodeBackground" ) ) , _HoveredNodeBackground( FTreeMapStyle::Get().GetBrush( "TreeMap.HoveredNodeBackground" ) ) , _NameFont() , _Name2Font() , _CenterTextFont() , _BorderPadding( FTreeMapStyle::Get().GetVector( "TreeMap.BorderPadding" ) ) , _MinimumInteractiveTreeNodeSize( 64 * 64 ) , _MinimumVisibleTreeNodeSize( 6 * 6 ) , _NavigationTransitionTime( 0.25f ) , _TopLevelContainerOuterPadding( 4.0f ) , _NestedContainerOuterPadding( 0.0f ) , _ContainerInnerPadding( 4.0f ) , _ChildContainerTextPadding( 2.0f )`
- L54 _public prototype_ `SLATE_ATTRIBUTE( bool, AllowEditing ) SLATE_ATTRIBUTE( const FSlateBrush*, BackgroundImage ) SLATE_ATTRIBUTE( const FSlateBrush*, NodeBackground ) SLATE_ATTRIBUTE( const FSlateBrush*, HoveredNodeBackground ) SLATE_ATTRIBUTE( FSlateFontInfo, NameFont ) SLATE_ATTRIBUTE( FSlateFontInfo, Name2Font );` — Sets whether the user can edit the tree map interactively by dragging nodes around and typing new node labels
- L72 _public prototype_ `SLATE_ATTRIBUTE( FSlateFontInfo, CenterTextFont );` — Font for any text that's centered inside the middle of the node.  Leaf nodes only.  Usually a bit larger.  Works just like NameFont
- L75 _public prototype_ `SLATE_ATTRIBUTE( FVector2D, BorderPadding ) SLATE_ARGUMENT( int32, MinimumInteractiveTreeNodeSize );` — Border Padding around fill bar
- L81 _public prototype_ `SLATE_ARGUMENT( int32, MinimumVisibleTreeNodeSize );` — Minimum size in pixels of a tree node that we should bother including in the UI.  Below this size, you'll need to drill down to see the node.
- L84 _public prototype_ `SLATE_ARGUMENT( float, NavigationTransitionTime );` — How many seconds to animate the visual transition when the user navigates to a new tree node, or after a modification of the tree takes place
- L87 _public prototype_ `SLATE_ARGUMENT( float, TopLevelContainerOuterPadding );` — How many pixels of padding around the outside of the root-level tree node box.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L90 _public prototype_ `SLATE_ARGUMENT( float, NestedContainerOuterPadding );` — How many pixels of padding around the outside of a non-root tree node's box.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L93 _public prototype_ `SLATE_ARGUMENT( float, ContainerInnerPadding );` — How many pixels of spacing between the container and its child containers.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L96 _public prototype_ `SLATE_ARGUMENT( float, ChildContainerTextPadding );` — How many pixels to pad text that's drawn inside of a container (not the top-level container, though)
- L100 _public prototype_ `SLATE_EVENT( FOnTreeMapNodeInteracted, OnTreeMapNodeDoubleClicked ) SLATE_EVENT( FOnTreeMapNodeInteracted, OnTreeMapNodeRightClicked ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class FTreeMapNodeData>& InTreeMapNodeData, const TSharedPtr< ITreeMapCustomization >& InCustomization );` — Optional delegate that fires when the node is double-clicked in the tree.  If you don't override this, the tree will use its default handling of double-click, which will re-root the tree on the node under the cursor
- L117 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget overrides
- L118 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L119 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L120 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L121 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L122 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L123 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& InMouseEvent ) override;`
- L124 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L125 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L126 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L127 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent ) override;`
- L136 _public prototype_ `void SetTreeRoot( const FTreeMapNodeDataRef& NewRoot, const bool bShouldPlayTransition );` — Sets a new "active root" for the tree.  This is used to "drill down" to child tree nodes or "climb up" back to the root. This also happens automatically when the user presses the mouse wheel to zoom in and out over nodes. @param	NewRoot						The tree's new root.  This can be any node within the tree @param	bShouldPlayTransition		If enabled, an animation will play
- L139 _public prototype_ `bool CanZoomOut() const;` — Returns true if it is possible to zoom out
- L142 _public prototype_ `bool ZoomOut();` — Zooms out, setting root to it's parent if possible, returns false if not
- L145 _public prototype_ `FTreeMapNodeDataPtr GetTreeRoot() const;` — Returns the current tree root, which is the largest node visible
- L153 _public prototype_ `void RebuildTreeMap( const bool bShouldPlayTransition );` — Refreshes the tree map from its source data.  The current active root will remain as the base of the tree.  Call this after you've changed data in the tree. @param	bShouldPlayTransition		If enabled, an animation will play
- L159 _protected prototype_ `struct FTreeMapNodeVisualInfo* FindNodeVisualUnderCursor( const FGeometry& MyGeometry, const FVector2D& ScreenSpaceCursorPosition );` — Finds the node visual that's under the cursor
- L162 _protected prototype_ `void MakeBlendedNodeVisual( const int32 VisualIndex, const float NavigationAlpha, FTreeMapNodeVisualInfo& OutVisual ) const;` — Blends between the current visual state and the state before the last navigation transition, by the specified amount
- L165 _protected prototype_ `bool IsNavigationTransitionActive() const;` — @return True if we're playing a transition after a navigation action (zoom!)
- L168 _protected prototype_ `void TakeUndoSnapshot();` — Grabs a snapshot of the current tree so we can restore it if the user performs an Undo action
- L171 _protected prototype_ `void Undo();` — Undoes the last action
- L174 _protected prototype_ `void Redo();` — Redoes the last action
- L177 _protected prototype_ `void ReparentNode( const FTreeMapNodeDataRef DroppedNode, const FTreeMapNodeDataRef NewParentNode );` — Reparents DroppedNode to NewParentNode (undoable!)
- L180 _protected prototype_ `FReply DeleteHoveredNode();` — Deletes the node under the mouse cursor, if any (undoable!)
- L183 _protected prototype_ `FReply InsertNewNodeAsChildOfHoveredNode( const FGeometry& MyGeometry );` — Insert a new node as a child of the node under the cursor
- L186 _protected prototype_ `FTreeMapNodeDataPtr FindNodeInCopiedTree( const FTreeMapNodeDataRef& NodeToFind, const FTreeMapNodeDataRef& OriginalNode, const FTreeMapNodeDataRef& CopiedRootNode ) const;` — Searches for the specified node in an identical copy of the node tree.
- L189 _protected prototype_ `void StartRenamingNode( const FGeometry& MyGeometry, const FTreeMapNodeDataRef& NodeData, const FVector2D& RelativePosition, const bool bIsNewNode );` — Pops up a box to allow the user to start renaming a node's title (undoable!)
- L192 _protected prototype_ `void RenamingNode_OnTextCommitted( const FText& NewText, ETextCommit::Type, TSharedRef<FTreeMapNodeData> NodeToRename );` — Called when the user commits a rename change
- L195 _protected prototype_ `void StopRenamingNode();` — Stops renaming a node, committing whatever text was entered
- L198 _protected prototype_ `void ApplyVisualizationToNodes( const FTreeMapNodeDataRef& Node );` — Called to apply the current 'size based on' and 'color based on' settings to the tree
- L201 _protected prototype_ `void ApplyVisualizationToNodesRecursively( const FTreeMapNodeDataRef& Node, const FLinearColor& DefaultColor, const int32 TreeDepth );` — Recursively applies the active visualization to all nodes, such as size by attribute, or color by attribute
- L204 _protected prototype_ `void ShowOptionsMenuAt( const FPointerEvent& InMouseEvent );` — Displays a context menu at the specified location with options for configuring the tree display
- L207 _private prototype_ `void ShowOptionsMenuAtInternal(const FVector2D& ScreenSpacePosition, const FWidgetPath& WidgetPath);`
- L216 _private member_ `TSharedPtr<class ITreeMap> TreeMap;` — The tree map that we're presenting using this widget
- L219 _private member_ `TSharedPtr<class ITreeMapCustomization> Customization;` — Customization for this tree map
- L222 _private member_ `TSharedPtr<class ITreeMap> LastTreeMap;` — The previous tree map for the last view we were looking at
- L225 _private member_ `FTreeMapNodeDataPtr TreeMapNodeData;` — The source data for the tree map
- L228 _private member_ `FTreeMapNodeDataPtr ActiveRootTreeMapNode;` — Current root of the tree that we're visualizing.  The user can re-root the tree by double-clicking on tree map nodes
- L231 _private member_ `FTreeMapAttributePtr SizeNodesByAttribute;` — Which attribute to visualize the size of the nodes based on, or null for default sizes
- L234 _private member_ `FTreeMapAttributePtr ColorNodesByAttribute;` — Which attribute to visualize the color of the nodes based on, or null for automatic colors
- L242 _private member_ `TAttribute< const FSlateBrush* > BackgroundImage;` — Background image to use for the tree map canvas area
- L245 _private member_ `TAttribute< const FSlateBrush* > NodeBackground;` — Background to use for each tree node
- L248 _private member_ `TAttribute< const FSlateBrush* > HoveredNodeBackground;` — Background to use for nodes that the mouse is hovering over
- L251 _private member_ `TAttribute<FVector2D> BorderPadding;` — Border Padding
- L254 _private member_ `TAttribute< FSlateFontInfo > NameFont;` — The font name used to draw the text
- L257 _private member_ `TAttribute< FSlateFontInfo > Name2Font;` — Font for second line of text, under the title.  Leaf nodes only.  Usually a bit smaller.  Works just like NameFont
- L260 _private member_ `TAttribute< FSlateFontInfo > CenterTextFont;` — Font for any text that's centered inside the middle of the node.  Leaf nodes only.  Usually a bit larger.  Works just like NameFont
- L268 _private member_ `FTreeMapNodeVisualInfo* MouseOverVisual;` — The visual that the mouse was over last
- L272 _private member_ `FOnTreeMapNodeInteracted OnTreeMapNodeDoubleClicked;` — Optional delegate that fires when the node is double-clicked in the tree.  If you don't override this, the tree will use its default handling of double-click, which will re-root the tree on the node under the cursor
- L275 _private member_ `FOnTreeMapNodeInteracted OnTreeMapNodeRightClicked;` — Right click event
- L282 _private member_ `int32 MinimumInteractiveTreeNodeSize;` — Minimum size of node that can be interacted with, if small you need to drill down into parent first
- L285 _private member_ `int32 MinimumVisibleTreeNodeSize;` — Minimum size in pixels of a tree node that we should bother including in the UI.  Below this size, you'll need to drill down to see the node.
- L288 _private member_ `FVector2D TreeMapSize;` — Size of our geometry the last time we rebuilt the tree map
- L291 _private member_ `TArray<struct FTreeMapNodeVisualInfo> CachedNodeVisuals;` — Cached set of visuals for the tree map the last time it was generated
- L294 _private member_ `TArray<struct FTreeMapNodeVisualInfo> LastCachedNodeVisuals;` — Cached node visuals for last tree map
- L297 _private member_ `TMap<int32, int32> NodeVisualIndicesToLastIndices;` — Maps node visual indices to their last node visual indices.  This is used for navigation transitions
- L300 _private member_ `TArray<int32> OrphanedLastIndices;` — List of node visual indices which no longer map to a node in the current layout. This is used for navigation transitions
- L303 _private member_ `FCurveSequence NavigateAnimationCurve;` — Time that tree view was changed last after navigation
- L306 _private member_ `float TopLevelContainerOuterPadding;` — How many pixels of padding around the outside of the root-level tree node box.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L309 _private member_ `float NestedContainerOuterPadding;` — How many pixels of padding around the outside of a non-root tree node's box.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L312 _private member_ `float ContainerInnerPadding;` — How many pixels of spacing between the container and its child containers.  Adding padding makes the tree look better, but you lose some sizing accuracy
- L315 _private member_ `float ChildContainerTextPadding;` — How many pixels to pad text that's drawn inside of a container (not the top-level container, though)
- L323 _private member_ `TAttribute<bool> AllowEditing;` — True if we should allow real-time editing right now.  The user can still navigate between nodes even if editing is disbled, so its not exactly "read only"
- L326 _private member_ `FTreeMapNodeVisualInfo* DraggingVisual;` — Node that we're currently dragging around.  This points to an entry in the CachedNodeVisuals array!
- L329 _private member_ `float DragVisualDistance;` — Distance we've LMB+dragged the cursor.  Used to determine if we're ready to start dragging and dropping
- L332 _private member_ `FVector2D RelativeDragStartMouseCursorPos;` — Position of the mouse cursor relative to the widget, where the user picked up a dragged visual
- L335 _private member_ `FVector2D RelativeMouseCursorPos;` — Position of the mouse cursor relative to the widget, the last time it moved.  Used for drag and drop.
- L338 _private member_ `TArray< TSharedPtr< FTreeMapNodeData > > UndoStates;` — Undo history buffer.
- L341 _private member_ `int32 CurrentUndoLevel;` — Current undo level, or INDEX_NONE if we haven't undone anything
- L344 _private member_ `TWeakPtr<SWidget> RenamingNodeWidget;` — Weak pointer to the widget used to rename a node inline.  We might need to close the window in some cases.
- L347 _private member_ `TWeakPtr<FTreeMapNodeData> RenamingNodeData;` — Weak pointer to the node that we're currently renaming, if any
- L350 _private member_ `bool bIsNamingNewNode;` — True if the node we're renaming is a newly-created node that should be added to the tree after we finish naming it
- L353 _private member_ `TWeakPtr<FTreeMapNodeData> HighlightPulseNode;` — Node that we're currently drawing a highlight pulse effect for.  This points to an entry in the CachedNodesVisuals array
- L356 _private member_ `double HighlightPulseStartTime;` — Time that we started playing a highlight pulse effect for the HighlightPulseNode

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TREEMAP_API`
- L31 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnTreeMapNodeInteracted, FTreeMapNodeData&, const FPointerEvent& );` — Delegate used when clicking or interacting with a specific node

### `Source/Developer/TreeMap/Public/TreeMapStyle.h` (Public)


#### class `FTreeMapStyle`  
`class FTreeMapStyle`  
_L13-28_
- desc: Style data for STreeMap
- L16 _public prototype_ `static void Initialize();`
- L17 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static const ISlateStyle& Get();`
- L19 _public prototype_ `static FName GetStyleSetName();`
- L23 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TREEMAP_API`

### `Source/Developer/TreeMap/TreeMapModule.h` (Other)
_(no declarations extracted)_
