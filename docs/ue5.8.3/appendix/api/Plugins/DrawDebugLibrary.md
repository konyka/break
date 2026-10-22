# Plugins / DrawDebugLibrary

- module root: `Plugins/Experimental/DrawDebugLibrary/Source/DrawDebugLibrary`
- headers: 2; symbols: 1176
- symbol kinds: class=2, enum=3, enumerator=22, macro=2, member=727, prototype=304, struct=116
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, RigVM
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/DrawDebugLibrary/Source/DrawDebugLibrary/Public/DrawDebugLibrary.h` (Public)


#### class `FDrawDebugLibraryModule`  
`class FDrawDebugLibraryModule : public IModuleInterface`  
_L23-30_
- inherits: `IModuleInterface`
- L28 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L29 _public prototype_ `virtual void ShutdownModule() override;`

#### enum `EDrawDebugLogVerbosity`  
`enum class EDrawDebugLogVerbosity : uint8`  
_L34-68_
- reflection: `UENUM(BlueprintType, Category = "Draw Debug Library")`
- desc: Blueprint accessible version of log verbosity for the Visual Logger Drawer
- L37 _public enumerator_ `Fatal` — Always prints a fatal error to console (and log file) and crashes (even if logging is disabled)
- L43 _public enumerator_ `Error` — Prints an error to console (and log file). Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
- L49 _public enumerator_ `Warning` — Prints a warning to console (and log file). Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
- L52 _public enumerator_ `Display` — Prints a message to console (and log file)
- L55 _public enumerator_ `Log` — Prints a message to a log file (does not print to console)
- L61 _public enumerator_ `Verbose` — Prints a verbose message to a log file (if Verbose logging is enabled for the given category, usually used for detailed logging)
- L67 _public enumerator_ `VeryVerbose` — Prints a verbose message to a log file (if VeryVerbose logging is enabled, usually used for detailed logging that would otherwise spam output)

#### struct `FDrawDebugPointStyle`  
`struct FDrawDebugPointStyle`  
_L73-89_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Style for debug drawing points
- L78 _public prototype_ `FDrawDebugPointStyle( const FLinearColor InColor = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const float InThickness = 0.0f);` — Construct a Point Style
- L84 _public member_ `FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Color of the point. Alpha controls the opacity.
- L88 _public member_ `float Thickness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Thickness of the point. Set to 0.0 for pixel-sized points.

#### enum `EDrawDebugLineType`  
`enum class EDrawDebugLineType : uint8`  
_L94-104_
- reflection: `UENUM(BlueprintType, Category = "Draw Debug Library")`
- desc: Enum for different line types
- L97 _public enumerator_ `Solid` — Normal solid line
- L100 _public enumerator_ `Dashed` — Line made up of multiple dashes
- L103 _public enumerator_ `Dotted` — Line drawn using points

#### struct `FDrawDebugLineStyle`  
`struct FDrawDebugLineStyle`  
_L109-145_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Style for debug drawing lines
- L114 _public prototype_ `FDrawDebugLineStyle( const FLinearColor InColor = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const float InThickness = 0.0f, const EDrawDebugLineType InLineType = EDrawDebugLineType::Solid, const float InDashWidth = 2.5f, const float InDashSpacing = 1.0f, const float InDotSpacing = 1.0f);` — Construct a Line Style
- L124 _public member_ `FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Color of the line. Alpha controls the opacity.
- L128 _public member_ `float Thickness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Thickness of the line. Set to 0.0 for pixel-sized lines.
- L132 _public member_ `EDrawDebugLineType LineType = EDrawDebugLineType::Solid;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Line style to draw with
- L136 _public member_ `float DashWidth = 2.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", AdvancedDisplay, meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Width of the dashes when using dashed style.
- L140 _public member_ `float DashSpacing = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", AdvancedDisplay, meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Spacing of the dashes when using dashed style.
- L144 _public member_ `float DotSpacing = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", AdvancedDisplay, meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Spacing of the dots when using dotted style.

#### enum `EDrawDebugArrowHead`  
`enum class EDrawDebugArrowHead : uint8`  
_L150-187_
- reflection: `UENUM(BlueprintType, Category = "Draw Debug Library")`
- desc: Enum for different arrow head types
- L153 _public enumerator_ `Simple` — Simple pointed arrow
- L156 _public enumerator_ `FourWay` — Four-way arrow head
- L159 _public enumerator_ `TriangularPyramid` — Triangular-based pyramid arrow head
- L162 _public enumerator_ `SquarePyramid` — Square-based pyramid arrow head
- L165 _public enumerator_ `Cone` — Cone arrow head
- L168 _public enumerator_ `Triangle` — Flat triangle arrow head
- L171 _public enumerator_ `Square` — Flat square arrow head
- L174 _public enumerator_ `Diamond` — Flat diamond arrow head
- L177 _public enumerator_ `Circle` — Flat circle arrow head
- L180 _public enumerator_ `Sphere` — 3D sphere arrow head
- L183 _public enumerator_ `Box` — 3D box arrow head
- L186 _public enumerator_ `None` — No arrow head

#### struct `FDrawDebugArrowSettings`  
`struct FDrawDebugArrowSettings`  
_L192-227_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing arrows
- L198 _public member_ `bool bArrowheadOnStart = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw an arrow head on the start of the arrow
- L202 _public member_ `bool bArrowLineEndsAtStartHead = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnStart", HideEditConditionToggle))` — If the line should end at the start arrow head
- L206 _public member_ `float ArrowHeadStartSize = 5.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnStart", HideEditConditionToggle, ClampMin = "0", UIMin = "0", Units = "cm"))` — Size of the start arrow head
- L210 _public member_ `EDrawDebugArrowHead ArrowHeadStartType = EDrawDebugArrowHead::Simple;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnStart", HideEditConditionToggle))` — Type of start arrow head
- L214 _public member_ `bool bArrowheadOnEnd = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw an arrow head on the end of the arrow
- L218 _public member_ `bool bArrowLineEndsAtEndHead = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnEnd", HideEditConditionToggle))` — If the line should end at the end arrow head
- L222 _public member_ `float ArrowHeadEndSize = 5.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnEnd", HideEditConditionToggle, ClampMin = "0", UIMin = "0", Units = "cm"))` — Size of the end arrow head
- L226 _public member_ `EDrawDebugArrowHead ArrowHeadEndType = EDrawDebugArrowHead::Simple;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bArrowheadOnEnd", HideEditConditionToggle))` — Type of end arrow head

#### struct `FDrawDebugChairSettings`  
`struct FDrawDebugChairSettings`  
_L231-250_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing chairs
- L237 _public member_ `float Width = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Width of the chair
- L241 _public member_ `float SeatHeight = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Height of the seat of the chair off the ground
- L245 _public member_ `float BackHeight = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Height of the back of the chair off the seat
- L249 _public member_ `float BackTilt = 10.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "cm"))` — Tilt of the chair backwards in cm

#### struct `FDrawDebugBackpackSettings`  
`struct FDrawDebugBackpackSettings`  
_L254-289_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing backpacks
- L260 _public member_ `float Width = 30.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Width of the backpack
- L264 _public member_ `float Height = 45.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Height of the backpack
- L268 _public member_ `float Depth = 15.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Depth of the backpack
- L272 _public member_ `float StrapDistance = 25.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Distance the straps extend outward
- L276 _public member_ `float StrapContactHeight = 25.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "cm"))` — The height at which the straps are in contact
- L280 _public member_ `float StrapWidth = 2.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "cm"))` — Width of the straps
- L284 _public member_ `float StrapHorizontalInset = 5.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "cm"))` — Inset of the straps horizontally
- L288 _public member_ `float StrapVerticalInset = 2.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "cm"))` — Inset of the straps vertically

#### struct `FDrawDebugBriefcaseSettings`  
`struct FDrawDebugBriefcaseSettings`  
_L293-312_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing briefcases
- L299 _public member_ `FVector HalfExtents = FVector(20.0f, 5.0f, 15.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Half-extents of the briefcase
- L303 _public member_ `float HandleLength = 10.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Length of the handle
- L307 _public member_ `float HandleHeight = 5.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — The height of the handle above the briefcase
- L311 _public member_ `float HandleWidth = 2.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Width of the handle

#### struct `FDrawDebugDoorSettings`  
`struct FDrawDebugDoorSettings`  
_L316-367_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing doors
- L322 _public member_ `float Width = 100.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Width of the door
- L326 _public member_ `float Height = 200.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Height of the door
- L330 _public member_ `float Inset = 5.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — How much the door is inset from the frame
- L334 _public member_ `float HandleHeight = 90.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — The height of the handle off the ground
- L338 _public member_ `float HandleOffset = 20.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — The offset of the handle into the door
- L342 _public member_ `float HandleRadius = 3.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — The radius of the handle
- L346 _public member_ `float HandleExtension = 2.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — How far the handle extends outward from the door
- L350 _public member_ `bool bOuterHandle = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to place a handle on the outside entrance of the door
- L354 _public member_ `bool bInnerHandle = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to place a handle on the inside entrance of the door
- L358 _public member_ `bool bHandleOnLeft = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to place the handle on the left-hand-side or the right-hand-side of the door from the perspective of entering
- L362 _public member_ `bool bDrawEntryArrow = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw an arrow on the floor showing the natural door entry direction
- L366 _public member_ `float OpenAngle = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (Units = "deg"))` — How open the door is in degrees

#### struct `FDrawDebugSkeletonSettings`  
`struct FDrawDebugSkeletonSettings`  
_L371-398_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing skeletons
- L377 _public member_ `bool bDrawSimpleSkeleton = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws a simple skeleton made up of lines rather than the full skeleton
- L381 _public member_ `float BoneRadius = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Radius of the bones
- L385 _public member_ `int32 BoneSegmentNum = 10;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "!bDrawSimpleSkeleton", HideEditConditionToggle, ClampMin = "0", UIMin = "0"))` — Number of segments in the spheres drawn for the bones
- L389 _public member_ `bool bDrawTransforms = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "!bDrawSimpleSkeleton", HideEditConditionToggle))` — If to draw small transforms inside the bone spheres
- L393 _public member_ `bool bDrawRoot = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw a bone going to the root/component transform
- L397 _public member_ `FLinearColor RootBoneColor = FLinearColor::Red;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bDrawRoot", HideEditConditionToggle))` — Color of the root bone when drawn

#### struct `FDrawDebugStringSettings`  
`struct FDrawDebugStringSettings`  
_L402-437_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing strings
- L408 _public member_ `float Height = 10.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Height of the text
- L412 _public member_ `bool bMonospaced = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw using a monospaced font
- L416 _public member_ `float WidthScale = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0"))` — Scaling factor for the width of the characters
- L420 _public member_ `float HeightScale = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0"))` — Scaling factor for the height of the characters
- L424 _public member_ `float LineSpacing = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0"))` — Scaling factor for the spacing between lines
- L428 _public member_ `float CharacterSpacing = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))` — Gaps between characters in cm
- L432 _public member_ `bool bCenterVertically = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws the string centered vertically rather than starting from the top left
- L436 _public member_ `bool bCenterHorizontally = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws the string centered horizontally rather than starting from the top left

#### struct `FDrawDebugGraphAxesSettings`  
`struct FDrawDebugGraphAxesSettings`  
_L441-472_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing graphs axes
- L447 _public member_ `FString Title;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Title of the graph
- L451 _public member_ `FDrawDebugStringSettings TitleSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Settings for the title
- L455 _public member_ `FString XaxisLabel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Label for the X axis
- L459 _public member_ `FString YaxisLabel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Label for the Y axis
- L463 _public member_ `FDrawDebugArrowSettings AxisArrowSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Settings for the axis arrows
- L467 _public member_ `FDrawDebugStringSettings AxisLabelSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Settings for the axis labels
- L471 _public member_ `bool bDrawAxesBox = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws the axes as a box instead of two arrows

#### struct `FDrawDebugCanvasTextSettings`  
`struct FDrawDebugCanvasTextSettings`  
_L476-523_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library")`
- desc: Settings for debug drawing canvas text
- L482 _public member_ `bool bMonospaced = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "!Font", HideEditConditionToggle))` — If to draw using a monospaced font
- L486 _public member_ `TObjectPtr<UFont> Font = nullptr;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Custom font to use
- L490 _public member_ `float WidthScale = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0"))` — Scaling factor for the width of the characters
- L494 _public member_ `float HeightScale = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (ClampMin = "0", UIMin = "0"))` — Scaling factor for the height of the characters
- L498 _public member_ `bool bShadow = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw a shadow under the text
- L502 _public member_ `FLinearColor ShadowColor = FLinearColor::Black;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bShadow", HideEditConditionToggle))` — Color of the shadow
- L506 _public member_ `FVector2D ShadowOffset = FVector2D(1.0f, 1.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bShadow", HideEditConditionToggle))` — Offset of the shadow
- L510 _public member_ `bool bOutline = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — If to draw an outline around the text
- L514 _public member_ `FLinearColor OutlineColor = FLinearColor::White;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library", meta = (EditCondition = "bOutline", HideEditConditionToggle))` — Color of the outline
- L518 _public member_ `bool bCenterVertically = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws the text centered vertically rather than starting from the top left
- L522 _public member_ `bool bCenterHorizontally = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Draw Debug Library")` — Draws the text centered horizontally rather than starting from the top left

#### struct `FDebugDrawerCanvasBuffer`  
`struct FDebugDrawerCanvasBuffer`  
_L526-563_
- desc: This buffers debug drawing calls, which can later be dispatched to draw on a canvas using either the bound delegate or via manual flushing
- L529 _public prototype_ `~FDebugDrawerCanvasBuffer();` — Destructor will un-bind the delegate if it is still bound
- L532 _public prototype_ `void Flush(FCanvas* Canvas);` — Flushes the buffer and draws to the canvas
- L535 _public member_ `FDelegateHandle Delegate;` — Delegate used to draw to a canvas somewhere
- L538 _public member_ `float Scale = 1.0f;` — Scale to draw to the screen
- L541 _public member_ `TArray<uint8> PrimitiveTypes;` — Buffered primitive types. 0 - points, 1 - lines, 2 - text
- L544 _public member_ `TArray<int32> PrimitiveNums;` — Number of primitives to draw for each buffered call
- L547 _public member_ `TArray<FLinearColor> Colors;` — Color of each buffered call
- L550 _public member_ `TArray<float> Thicknesses;` — Thickness of each buffered call
- L553 _public member_ `TArray<FVector> Points;` — Array of point data
- L556 _public member_ `TArray<TPair<FVector, FVector>> LineSegments;` — Array of line segment data
- L559 _public member_ `TArray<TPair<FVector2D, FText>> Texts;` — Array of text data including draw location
- L562 _public member_ `TArray<FDrawDebugCanvasTextSettings> TextSettings;` — Array of text setting data

#### struct `FDebugDrawer`  
`struct FDebugDrawer`  
_L571-729_
- reflection: `USTRUCT(BlueprintType, Category = "Draw Debug Library", meta = (HasNativeMake = "/Script/DrawDebugLibrary.DrawDebugLibrary.MakeDebugDrawer"))`
- desc: A simple Blueprint wrapper around different objects that are capable of debug drawing. This allows us to use the same blueprint interface and functions for debug drawing if we are drawing using a UWorld object or a FPrimitiveDrawInterface object (for example). Since this contains raw pointers it should not be stored anywhere as these could become stale. It should always be treated as a temporary object.
- L578 _public prototype_ `FDebugDrawer();` — Make a null debug drawer which ignores draw commands
- L581 _public prototype_ `FDebugDrawer(UObject* InObject);` — Make a debug drawer for a UObject
- L584 _public prototype_ `FDebugDrawer(UWorld* InWorld);` — Make a debug drawer for a UWorld
- L587 _public prototype_ `FDebugDrawer(UAnimInstance* InAnimInstance);` — Make a debug drawer for an AnimInstance
- L590 _public prototype_ `FDebugDrawer(FAnimInstanceProxy* InAnimInstanceProxy);` — Make a debug drawer for an AnimInstanceProxy
- L593 _public prototype_ `FDebugDrawer(FPrimitiveDrawInterface* InPrimitiveDrawInterface);` — Make a debug drawer for a FPrimitiveDrawInterface
- L596 _public prototype_ `FDebugDrawer(FRigVMDrawInterface* InRigVMDrawInterface, const USceneComponent* InRigVMComponent = nullptr);` — Make a debug drawer for a FRigVMDrawInterface
- L599 _public prototype_ `FDebugDrawer(FCanvas* InCanvas);` — Make a debug drawer for a FCanvas
- L602 _public prototype_ `FDebugDrawer(UCanvas* InCanvas);` — Make a debug drawer for a UCanvas
- L605 _public prototype_ `FDebugDrawer(const TSharedPtr<FDebugDrawerCanvasBuffer>& InCanvasBuffer);` — Make a debug drawer for the given canvas buffer.
- L608 _public prototype_ `~FDebugDrawer();` — Forward declaration of destructor
- L611 _public prototype_ `static FDebugDrawer MakeDebugDrawer();` — Make a null debug drawer which ignores draw commands
- L614 _public prototype_ `static FDebugDrawer MakeDebugDrawer(UObject* Object);` — Make a debug drawer for a UObject
- L617 _public prototype_ `static FDebugDrawer MakeDebugDrawer(UWorld* World);` — Make a debug drawer for a UWorld
- L620 _public prototype_ `static FDebugDrawer MakeDebugDrawer(UAnimInstance* AnimInstance);` — Make a debug drawer for an AnimInstance
- L623 _public prototype_ `static FDebugDrawer MakeDebugDrawer(FAnimInstanceProxy* AnimInstanceProxy);` — Make a debug drawer for an AnimInstanceProxy
- L626 _public prototype_ `static FDebugDrawer MakeDebugDrawer(FPrimitiveDrawInterface* PrimitiveDrawInterface);` — Make a debug drawer for a FPrimitiveDrawInterface
- L629 _public prototype_ `static FDebugDrawer MakeDebugDrawer(FRigVMDrawInterface* InRigVMDrawInterface, const USceneComponent* InRigVMComponent = nullptr);` — Make a debug drawer for a FRigVMDrawInterface
- L632 _public prototype_ `static FDebugDrawer MakeDebugDrawer(FCanvas* InCanvas, const float InCanvasScale = 1.0f);` — Make a debug drawer for a FCanvas
- L635 _public prototype_ `static FDebugDrawer MakeDebugDrawer(UCanvas* InCanvas, const float InCanvasScale = 1.0f);` — Make a debug drawer for a UCanvas
- L638 _public prototype_ `static FDebugDrawer MakeDebugDrawer(const TSharedPtr<FDebugDrawerCanvasBuffer>& CanvasBuffer);` — Make a debug drawer for the given canvas buffer.
- L641 _public prototype_ `static FDebugDrawer MakeVisualLoggerDebugDrawer( const UObject* Object, const FName Category = TEXT("LogDrawDebugLibrary"), const EDrawDebugLogVerbosity Verbosity = EDrawDebugLogVerbosity::Display, const bool bDrawToScene = true, const bool bDrawToSceneWhileRecording = true);` — Make a debug drawer for the Visual Logger
- L649 _public prototype_ `static FDebugDrawer MakeVisualLoggerDebugDrawer( const UObject* Object, const FLogCategoryBase& Category, const ELogVerbosity::Type Verbosity = ELogVerbosity::Display, const bool bDrawToScene = true, const bool bDrawToSceneWhileRecording = true);` — Make a debug drawer for the Visual Logger
- L657 _public prototype_ `static FDebugDrawer MakeScreenDebugDrawer(const float Scale = 1.0f);` — Make a debug drawer for the default viewport canvas. This can be expensive so should be called once and stored.
- L660 _public prototype_ `static FDebugDrawer MakeMergedDebugDrawer(const TArrayView<const FDebugDrawer> DebugDrawers);` — Make a debug drawer by merging multiple other debug drawers of different types
- L664 _public prototype_ `void DrawPoints(const TArrayView<const FVector> Locations, const FLinearColor& Color, const float Thickness, const bool bDepthTest) const;`
- L665 _public prototype_ `void DrawLines(const TArrayView<const TPair<FVector, FVector>> Segments, const FLinearColor& Color, const float Thickness, const bool bDepthTest) const;`
- L667 _public prototype_ `void VisualLoggerLogString(const FStringView String, const FLinearColor& Color) const;`
- L668 _public prototype_ `void VisualLoggerDrawString(const FStringView String, const FVector& Location, const FLinearColor& Color) const;`
- L670 _public prototype_ `void CanvasDrawText(const FVector2D& Location, const FText& Text, const FLinearColor& Color, const FDrawDebugCanvasTextSettings& Settings) const;`
- L675 _private member_ `FPrimitiveDrawInterface* PDI = nullptr;` — Primitive Draw Interface - used for drawing in editor viewports.
- L680 _private member_ `FRigVMDrawInterface* RigVM = nullptr;` — RigVM Draw Interface - used for drawing in a RigVM context.
- L684 _private member_ `TObjectPtr<const USceneComponent> RigVMComponent = nullptr;` — `UPROPERTY()` — Component which the RigVM context is attached to
- L690 _private member_ `TObjectPtr<UWorld> World = nullptr;` — `UPROPERTY()` — World object - used for normal debug drawing.
- L696 _private member_ `TObjectPtr<UAnimInstance> AnimInstance = nullptr;` — `UPROPERTY()` — Anim Instance Object - used for debug drawing in an AnimBlueprints.
- L699 _private member_ `FAnimInstanceProxy* AnimInstanceProxy = nullptr;` — Anim Instance Proxy Object - used for debug drawing in an AnimNode.
- L705 _private member_ `TObjectPtr<const UObject> VisualLoggerObject = nullptr;` — `UPROPERTY()` — Visual Logger Object - used for writing to the visual logger.
- L708 _private member_ `FName VisualLoggerCategory = NAME_None;` — Visual Logger Category.
- L711 _private member_ `ELogVerbosity::Type VisualLoggerVerbosity = ELogVerbosity::Display;` — Visual Logger Verbosity.
- L714 _private member_ `bool bVisualLoggerDrawToScene = true;` — Visual Logger if to also draw to scene
- L717 _private member_ `bool bVisualLoggerDrawToSceneWhileRecording = true;` — Visual Logger if to also draw while recording
- L722 _private member_ `FCanvas* Canvas = nullptr;` — Canvas pointer - used for writing to a 2D canvas
- L725 _private member_ `float CanvasScale = 1.0f;` — Canvas Scale
- L728 _private member_ `TSharedPtr<FDebugDrawerCanvasBuffer> CanvasBuffer;` — Canvas buffer used for writing to a canvas at a later point

#### class `UDrawDebugLibrary`  
`class UDrawDebugLibrary : public UBlueprintFunctionLibrary`  
_L740-1570_
- reflection: `UCLASS(BlueprintType, Category = "Draw Debug Library", meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: A blueprint library of additional debug draw functions that unifies drawing between different debug drawing interfaces. Also includes a number of helper functions and other convenience functions that are useful for debug drawing such as functions for recording histories. General parameter structure for these functions is: Required Inputs, Style, bDepthTest, Settings
- L748 _public prototype_ `static FDebugDrawer MakeNullDebugDrawer();` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Make a null debug drawer which ignores draw commands
- L752 _public prototype_ `static FDebugDrawer MakeDebugDrawer(UObject* Object);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, DefaultToSelf = "Object", HidePin = "Object"))` — Make a debug debugger from the current "Self" object
- L756 _public prototype_ `static FDebugDrawer MakeObjectDebugDrawer(UObject* Object);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly))` — Make a debug drawer for a UObject
- L759 _public prototype_ `static FDebugDrawer MakeWorldDebugDrawer(UWorld* World);` — Make a debug drawer for a UWorld
- L763 _public prototype_ `static FDebugDrawer MakeAnimInstanceDebugDrawer(UAnimInstance* AnimInstance);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, DefaultToSelf = "AnimInstance"))` — Make a debug drawer for an AnimInstance
- L766 _public prototype_ `static FDebugDrawer MakeAnimInstanceProxyDebugDrawer(FAnimInstanceProxy* AnimInstanceProxy);` — Make a debug drawer for an AnimInstanceProxy
- L769 _public prototype_ `static FDebugDrawer MakePDIDebugDrawer(FPrimitiveDrawInterface* PrimitiveDrawInterface);` — Make a debug drawer for a FPrimitiveDrawInterface
- L772 _public prototype_ `static FDebugDrawer MakeRigVMDebugDrawer(FRigVMDrawInterface* InRigVMDrawInterface, const USceneComponent* InRigVMComponent = nullptr);` — Make a debug drawer for a FRigVMDrawInterface
- L775 _public prototype_ `static FDebugDrawer MakeCanvasStructDebugDrawer(FCanvas* InCanvas, const float InScale = 1.0f);` — Make a debug drawer for a FCanvas
- L779 _public prototype_ `static FDebugDrawer MakeCanvasDebugDrawer(UCanvas* InCanvas, const float InScale = 1.0f);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly))` — Make a debug drawer for a UCanvas
- L782 _public prototype_ `static FDebugDrawer MakeCanvasDebugDrawerFromBuffer(const TSharedPtr<FDebugDrawerCanvasBuffer>& CanvasBuffer);` — Make a debug drawer for the given buffer.
- L786 _public prototype_ `static FDebugDrawer MakeVisualLoggerDebugDrawer( const UObject* Object, const FName Category = TEXT("LogDrawDebugLibrary"), const EDrawDebugLogVerbosity Verbosity = EDrawDebugLogVerbosity::Display, const bool bDrawToScene = true, const bool bDrawToSceneWhileRecording = true);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, DefaultToSelf = "Object", HidePin = "Object"))` — Make a debug drawer for the Visual Logger from the current "Self" object
- L795 _public prototype_ `static FDebugDrawer MakeVisualLoggerDebugDrawerFromObject( const UObject* Object, const FName Category = TEXT("LogDrawDebugLibrary"), const EDrawDebugLogVerbosity Verbosity = EDrawDebugLogVerbosity::Display, const bool bDrawToScene = true, const bool bDrawToSceneWhileRecording = true);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly))` — Make a debug drawer for the Visual Logger
- L802 _public prototype_ `static FDebugDrawer MakeVisualLoggerDebugDrawerFromObjectWithCategory( const UObject* Object, const FLogCategoryBase& Category, const ELogVerbosity::Type Verbosity = ELogVerbosity::Display, const bool bDrawToScene = true, const bool bDrawToSceneWhileRecording = true);`
- L811 _public prototype_ `static FDebugDrawer MakeScreenDebugDrawer(const float Scale = 1.0f);` — `UFUNCTION(BlueprintPure = false, Category = "Draw Debug Library", meta = (DevelopmentOnly))` — Make a debug drawer for the default viewport canvas. This is expensive so should be called once and stored.
- L815 _public prototype_ `static FDebugDrawer MakeMergedDebugDrawer(const TArray<FDebugDrawer>& DebugDrawers);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly))` — Make a debug drawer by merging multiple other debug drawers of different types
- L816 _public prototype_ `static FDebugDrawer MakeMergedDebugDrawerArrayView(const TArrayView<const FDebugDrawer> DebugDrawers);`
- L822 _public prototype_ `static void VisualLoggerLogString(const FDebugDrawer& Drawer, const FString& String, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String"))` — Log a string to the visual logger. Only does anything with a VisualLoggerDebugDrawer.
- L823 _public prototype_ `static void VisualLoggerLogStringView(const FDebugDrawer& Drawer, const FStringView String, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));`
- L827 _public prototype_ `static void VisualLoggerLogText(const FDebugDrawer& Drawer, const FText& Text, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text"))` — Log some text to the visual logger. Only does anything with a VisualLoggerDebugDrawer.
- L833 _public prototype_ `static void DrawDebugCanvasText(const FDebugDrawer& Drawer, const FVector2D& Location, const FText& Text, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const FDrawDebugCanvasTextSettings& Settings = FDrawDebugCanvasTextSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Text, Settings"))` — Draw some text on the canvas. Only does anything with a ScreenDebugDrawer or CanvasDebugDrawer.
- L837 _public prototype_ `static void DrawDebugCanvasString(const FDebugDrawer& Drawer, const FVector2D& Location, const FString& String, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const FDrawDebugCanvasTextSettings& Settings = FDrawDebugCanvasTextSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, String, Settings"))` — Draw a string on the canvas. Only does anything with a ScreenDebugDrawer or CanvasDebugDrawer.
- L838 _public prototype_ `static void DrawDebugCanvasStringView(const FDebugDrawer& Drawer, const FVector2D& Location, const FStringView String, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const FDrawDebugCanvasTextSettings& Settings = FDrawDebugCanvasTextSettings());`
- L842 _public prototype_ `static void DrawDebugCanvasName(const FDebugDrawer& Drawer, const FVector2D& Location, const FName& Name, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const FDrawDebugCanvasTextSettings& Settings = FDrawDebugCanvasTextSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Name, Settings"))` — Draw a name on the canvas. Only does anything with a ScreenDebugDrawer or CanvasDebugDrawer.
- L849 _public prototype_ `static void MakeLinearlySpacedFloatArray(TArray<float>& OutValues, const float Start = 0.0f, const float Stop = 1.0f, const int32 Num = 10);` — `UFUNCTION(BlueprintPure = true, Category = "Draw Debug Library")` — Convenience function for making an array of linearly spaced float values
- L850 _public prototype_ `static void MakeLinearlySpacedFloatArrayView(TArrayView<float> OutValues, const float Start = 0.0f, const float Stop = 1.0f);`
- L854 _public prototype_ `static void AddToFloatHistoryArray(UPARAM(ref) TArray<float>& InOutValues, const float NewValue = 0.0f, const int32 MaxHistoryNum = 60);` — `UFUNCTION(BlueprintPure = false, Category = "Draw Debug Library", meta = (NotBlueprintThreadSafe))` — Convenience function that adds a float to the end of an array, popping values from the front once the max is reached
- L858 _public prototype_ `static void AddToVectorHistoryArray(UPARAM(ref) TArray<FVector>& InOutValues, const FVector NewValue = FVector::ZeroVector, const int32 MaxHistoryNum = 60);` — `UFUNCTION(BlueprintPure = false, Category = "Draw Debug Library", meta = (NotBlueprintThreadSafe))` — Convenience function that adds a vector to the end of an array, popping values from the front once the max is reached
- L862 _public prototype_ `static void AddToNameHistoryArray(UPARAM(ref) TArray<FName>& InOutValues, const FName NewValue = NAME_None, const int32 MaxHistoryNum = 60);` — `UFUNCTION(BlueprintPure = false, Category = "Draw Debug Library", meta = (NotBlueprintThreadSafe))` — Convenience function that adds a name to the end of an array, popping values from the front once the max is reached
- L866 _public prototype_ `static void DrawDebugLocalOffset( FVector& OutLocation, FRotator& OutRotation, const FVector DrawLocation, const FRotator DrawRotation, const FVector DrawOffset);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Returns a new location and rotation after applying a local offset to the input draw location and rotation
- L875 _public prototype_ `static void DrawDebugOrientUprightToFloor( FVector& OutLocation, FRotator& OutRotation, const FVector DrawWorldLocation, const FVector DrawUprightOffset);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Create a new location and rotation that orients debug drawing of upright objects such as text onto the floor
- L883 _public prototype_ `static void DrawDebugOrientFloorToUpright( FVector& OutLocation, FRotator& OutRotation, const FVector DrawWorldLocation, const FVector DrawFloorOffset);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Create a new location and rotation that orients debug drawing of floor objects such as shapes upright
- L891 _public prototype_ `static void DrawDebugOrientUprightToCamera( FVector& OutLocation, FRotator& OutRotation, const FVector DrawWorldLocation, const FVector DrawUprightOffset, const FRotator CameraRotation, const bool bUseOnlyYaw = false);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Create a new location and rotation that orients debug drawing of upright objects such as text to face the camera
- L901 _public prototype_ `static void DrawDebugOrientFloorToCamera( FVector& OutLocation, FRotator& OutRotation, const FVector DrawWorldLocation, const FVector DrawFloorOffset, const FRotator CameraRotation, const bool bUseOnlyYaw = false);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Create a new location and rotation that orients debug drawing of floor objects such as shapes to face the camera
- L911 _public prototype_ `static void DrawDebugOrientUprightToCanvas( FVector& OutLocation, FRotator& OutRotation, const FVector2D DrawCanvasLocation);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Create a new location and rotation that orients debug drawing of upright objects such as text and graphs to a canvas
- L920 _public prototype_ `static FDrawDebugPointStyle MakeDrawDebugPointStyleFromColor(const FLinearColor& Color);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "Color"))` — Make a point style from a color
- L924 _public prototype_ `static FDrawDebugPointStyle MakeDrawDebugPointStyleFromColorAndThickness(const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const float Thickness = 0.0f);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Make a point style from a color and thickness
- L928 _public prototype_ `static FDrawDebugLineStyle MakeDrawDebugLineStyleFromColor(const FLinearColor& Color);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "Color"))` — Make a line style from a color
- L932 _public prototype_ `static FDrawDebugLineStyle MakeDrawDebugLineStyleFromColorAndThickness(const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const float Thickness = 0.0f);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Make a line style from a color and thickness
- L936 _public prototype_ `static FDrawDebugPointStyle DrawDebugPointStyleFromLineStyle(const FDrawDebugLineStyle& LineStyle);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "LineStyle"))` — Get a point style from a line style
- L940 _public prototype_ `static FDrawDebugLineStyle DrawDebugLineStyleFromPointStyle(const FDrawDebugPointStyle& PointStyle);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "PointStyle"))` — Get a line style from a point style
- L944 _public prototype_ `static FLinearColor DrawDebugPointStyleColor(const FDrawDebugPointStyle& PointStyle);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "PointStyle"))` — Get the color from a point style
- L948 _public prototype_ `static FLinearColor DrawDebugLineStyleColor(const FDrawDebugLineStyle& LineStyle);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (BlueprintAutocast, CompactNodeTitle = "->", AutoCreateRefTerm = "LineStyle"))` — Get the color from a line style
- L952 _public prototype_ `static FDrawDebugLineStyle DrawDebugLineStyleWithColor(const FDrawDebugLineStyle& LineStyle, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (AutoCreateRefTerm = "LineStyle"))` — Get a line style with the color changed
- L956 _public prototype_ `static FDrawDebugLineStyle DrawDebugLineStyleWithColorNoOpacity(const FDrawDebugLineStyle& LineStyle, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (AutoCreateRefTerm = "LineStyle"))` — Get a line style with the color (excluding the opacity) changed
- L960 _public prototype_ `static FDrawDebugLineStyle DrawDebugLineStyleWithThickness(const FDrawDebugLineStyle& LineStyle, const float Thickness = 0.0f);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (AutoCreateRefTerm = "LineStyle"))` — Get a line style with the thickness changed
- L964 _public prototype_ `static FDrawDebugLineStyle DrawDebugLineStyleWithType(const FDrawDebugLineStyle& LineStyle, const EDrawDebugLineType LineType = EDrawDebugLineType::Solid);` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (AutoCreateRefTerm = "LineStyle"))` — Get a line style with the type changed
- L970 _public prototype_ `static void DrawDebugPoint(const FDebugDrawer& Drawer, const FVector& Location, const FDrawDebugPointStyle& PointStyle = FDrawDebugPointStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, PointStyle"))` — Debug Draw a point
- L974 _public prototype_ `static void DrawDebugPoints(const FDebugDrawer& Drawer, const TArray<FVector>& Locations, const FDrawDebugPointStyle& PointStyle = FDrawDebugPointStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Locations, PointStyle"))` — Debug Draw points. These should be preferred over DrawDebugPoint where possible as it will batch drawing when required such as when using the visual logger.
- L975 _public prototype_ `static void DrawDebugPointsArrayView(const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const FDrawDebugPointStyle& PointStyle = FDrawDebugPointStyle(), const bool bDepthTest = true);`
- L981 _public prototype_ `static void DrawDebugLine(const FDebugDrawer& Drawer, const FVector& StartLocation, const FVector& EndLocation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "StartLocation, EndLocation, LineStyle"))` — Debug Draw a line
- L985 _public prototype_ `static void DrawDebugLines(const FDebugDrawer& Drawer, const TArray<FVector>& StartLocations, const TArray<FVector>& EndLocations, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "StartLocations, EndLocations, LineStyle"))` — Debug Draw lines. These should be preferred over DrawDebugLine where possible as it will batch drawing when required such as when using the visual logger.
- L986 _public prototype_ `static void DrawDebugLinesArrayView(const FDebugDrawer& Drawer, const TArrayView<const FVector> StartLocations, const TArrayView<const FVector> EndLocations, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);`
- L987 _public prototype_ `static void DrawDebugLinesPairsArrayView(const FDebugDrawer& Drawer, const TArrayView<const TPair<FVector, FVector>> Segments, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);`
- L993 _public prototype_ `static void DrawDebugTriangularBasePyramid(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 20.0f, const float Width = 20.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a triangular base pyramid
- L997 _public prototype_ `static void DrawDebugSquareBasePyramid(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 20.0f, const float Width = 20.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a square base pyramid
- L1001 _public prototype_ `static void DrawDebugCone(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 20.0f, const float Radius = 10.0f, const int32 Segments = 9);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a cone
- L1005 _public prototype_ `static void DrawDebugConeLookAt(const FDebugDrawer& Drawer, const FVector& Location, const FVector& Direction = FVector::ForwardVector, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 20.0f, const float Angle = 10.0f, const int32 Segments = 9);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Direction, LineStyle"))` — Debug Draw a cone starting from the point oriented on the forward axis, with the given angle
- L1009 _public prototype_ `static void DrawDebugArc(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Angle = 360.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an arc around the XY axis
- L1013 _public prototype_ `static void DrawDebugCircle(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an circle around the XY axis
- L1017 _public prototype_ `static void DrawDebugCircleTick(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Angle, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const float Length = 2.5f, bool bInside = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an tick on a circle at a given angle
- L1021 _public prototype_ `static void DrawDebugCircleTicks(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArray<float>& Angles, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const float Length = 5.0f, bool bInside = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, Angles, LineStyle"))` — Debug Draw ticks on a circle at the given angles
- L1022 _public prototype_ `static void DrawDebugCircleTicksArrayView(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArrayView<const float> Angles, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const float Length = 5.0f, bool bInside = true);`
- L1026 _public prototype_ `static void DrawDebugCircleOutline(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float InnerRadius = 10.0f, const float OuterRadius = 15.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw the outline of a circle (two circles) around the XY axis
- L1030 _public prototype_ `static void DrawDebugTriangle(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a triangle on the XY axis
- L1034 _public prototype_ `static void DrawDebugSquare(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float HalfLength = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a square on the XY axis
- L1038 _public prototype_ `static void DrawDebugCross(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float HalfLength = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a cross on the XY axis
- L1042 _public prototype_ `static void DrawDebugDiamond(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a diamond on the XY axis
- L1046 _public prototype_ `static void DrawDebugPentagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a pentagon on the XY axis
- L1050 _public prototype_ `static void DrawDebugHexagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a hexagon on the XY axis
- L1054 _public prototype_ `static void DrawDebugHeptagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a heptagon on the XY axis
- L1058 _public prototype_ `static void DrawDebugOctagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a octagon on the XY axis
- L1062 _public prototype_ `static void DrawDebugNonagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a nonagon on the XY axis
- L1066 _public prototype_ `static void DrawDebugDecagon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a decagon on the XY axis
- L1070 _public prototype_ `static void DrawDebugRegularPolygon(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Sides = 11);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a flat regular polygon on the XY axis
- L1074 _public prototype_ `static void DrawDebugCheckMark(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a check mark on the XY axis
- L1078 _public prototype_ `static void DrawDebugCheckBox(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float HalfLength = 10.0f, const bool bChecked = false, const float TickRatio = 1.75f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a checkbox on the XY axis
- L1082 _public prototype_ `static void DrawDebugCrossBox(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float HalfLength = 10.0f, const bool bCrossed = false, const float CrossRatio = 1.0);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a cross box on the XY axis
- L1086 _public prototype_ `static void DrawDebugRadioButton(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const bool bSelected = false, const float InnerButtonRatio = 0.5f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a radio button on the XY axis
- L1090 _public prototype_ `static void DrawDebugLocator(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an axis-aligned cross
- L1094 _public prototype_ `static void DrawDebugCrossLocator(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an axis-aligned cross rotated by 45 degrees
- L1098 _public prototype_ `static void DrawDebugBox(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FVector HalfExtents = FVector(10.0f, 10.0f, 10.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an oriented box
- L1102 _public prototype_ `static void DrawDebugBoxStruct(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FBox& Box = FBox());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, Box"))` — Debug Draw an FBox
- L1106 _public prototype_ `static void DrawDebugBoxSphereBounds(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FBoxSphereBounds& Bounds = FBoxSphereBounds());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, Bounds"))` — Debug Draw a FBoxSphereBounds
- L1110 _public prototype_ `static void DrawDebugSphere(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 8);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a sphere
- L1114 _public prototype_ `static void DrawDebugSimpleSphere(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 13);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a simple sphere made up of three circles one of each axis
- L1118 _public prototype_ `static void DrawDebugCapsule(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const float HalfLength = 10.0f, const int32 Segments = 8);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw a capsule
- L1122 _public prototype_ `static void DrawDebugCapsuleLine(const FDebugDrawer& Drawer, const FVector& StartLocation, const FVector& EndLocation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 8);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "StartLocation, EndLocation, LineStyle"))` — Debug Draw a capsule using the start and end location
- L1126 _public prototype_ `static void DrawDebugFrustum(const FDebugDrawer& Drawer, const FMatrix& FrustumToWorld, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "FrustumToWorld, LineStyle"))` — Debug Draw a Frustum
- L1132 _public prototype_ `static void DrawDebugArrowHead(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const EDrawDebugArrowHead Type = EDrawDebugArrowHead::Simple, const float Size = 5.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an arrow head
- L1136 _public prototype_ `static void DrawDebugArrow(const FDebugDrawer& Drawer, const FVector& StartLocation, const FVector& EndLocation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugArrowSettings& Settings = FDrawDebugArrowSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "StartLocation, EndLocation, LineStyle, Settings"))` — Debug Draw an arrow
- L1140 _public prototype_ `static void DrawDebugOrientedArrow(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Length = 100.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugArrowSettings& Settings = FDrawDebugArrowSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug Draw an arrow with an orientation
- L1144 _public prototype_ `static void DrawDebugGroundTargetArrow(const FDebugDrawer& Drawer, const FVector& Location, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 100.0f, const float ArrowHeadSize = 20.0f, const float Radius = 10.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, LineStyle"))` — Draws an arrow pointing down at the location surrounded by a circle
- L1148 _public prototype_ `static void DrawDebugFlatArrow(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Length = 20.0f, const float Width = 20.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Draws a flat 2d arrow motif
- L1152 _public prototype_ `static void DrawDebugCircleArrow(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Angle, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const float Length = 20.0f, const FDrawDebugArrowSettings& Settings = FDrawDebugArrowSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug Draw an arrow coming off a circle at a given angle
- L1156 _public prototype_ `static void DrawDebugArcArrow(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Angle = 90.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 10.0f, const int32 Segments = 17, const FDrawDebugArrowSettings& Settings = FDrawDebugArrowSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug Draw an arc around the XY axis with arrow heads
- L1162 _public prototype_ `static void DrawDebugCatmullRomSplineStart(const FDebugDrawer& Drawer, const FVector& V0, const FVector& V1, const FVector& V2, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const bool bMonotonic = false, const int32 Segments = 15);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "V0, V1, V2, LineStyle"))` — Debug Draw the start section of a catmull rom spline
- L1166 _public prototype_ `static void DrawDebugCatmullRomSplineEnd(const FDebugDrawer& Drawer, const FVector& V0, const FVector& V1, const FVector& V2, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const bool bMonotonic = false, const int32 Segments = 15);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "V0, V1, V2, LineStyle"))` — Debug Draw the end section of a catmull rom spline
- L1170 _public prototype_ `static void DrawDebugCatmullRomSplineSection(const FDebugDrawer& Drawer, const FVector& V0, const FVector& V1, const FVector& V2, const FVector& V3, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const bool bMonotonic = false, const int32 Segments = 15);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "V0, V1, V2, V3, LineStyle"))` — Debug Draw a full segment of a catmull rom spline
- L1174 _public prototype_ `static void DrawDebugCatmullRomSpline(const FDebugDrawer& Drawer, const TArray<FVector>& Points, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const bool bMonotonic = false, const int32 Segments = 15);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Points, LineStyle"))` — Debug Draw a catmull rom spline
- L1175 _public prototype_ `static void DrawDebugCatmullRomSplineArrayView(const FDebugDrawer& Drawer, const TArrayView<const FVector> Points, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const bool bMonotonic = false, const int32 Segments = 15);`
- L1181 _public prototype_ `static void DrawDebugAngle(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float Angle = 0.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float LineLength = 10.0f, const float AngleRadius = 5.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug Draw an angle
- L1185 _public prototype_ `static void DrawDebugAngleBetween(const FDebugDrawer& Drawer, const FVector& P0, const FVector& P1, const FVector& P2, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float AngleRadius = 5.0f, const int32 Segments = 17);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "P0, P1, P2, LineStyle"))` — Debug Draw the angle between the vectors P0 - P1 and P2 - P1
- L1189 _public prototype_ `static void DrawDebugLocation(const FDebugDrawer& Drawer, const FVector& Location, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f, const int32 Segments = 8);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, LineStyle"))` — Debug Draw a sphere at the given location
- L1193 _public prototype_ `static void DrawDebugLocations(const FDebugDrawer& Drawer, const TArray<FVector>& Locations, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f, const int32 Segments = 8);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Locations, LineStyle"))` — Debug Draw spheres at the given locations
- L1194 _public prototype_ `static void DrawDebugLocationsArrayView(const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f, const int32 Segments = 8);`
- L1198 _public prototype_ `static void DrawDebugRotation(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Draws a rotation
- L1201 _public prototype_ `static void DrawDebugRotationsQuatArrayView( const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const TArrayView<const FQuat4f> Rotations, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f);` — Draws an array of transforms
- L1211 _public prototype_ `static void DrawDebugDirection(const FDebugDrawer& Drawer, const FVector& Location, const FVector& Direction = FVector::ForwardVector, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawArrowLength = 100.0f, const float ArrowHeadScale = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Direction, LineStyle"))` — Debug Draw an arrow at the given location facing in the given direction
- L1215 _public prototype_ `static void DrawDebugVelocity(const FDebugDrawer& Drawer, const FVector& Location, const FVector& Velocity, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawVelocityLineScale = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Velocity, LineStyle"))` — Debug Draw a line at the given location scaled by the given velocity
- L1219 _public prototype_ `static void DrawDebugVelocities(const FDebugDrawer& Drawer, const TArray<FVector>& Locations, const TArray<FVector>& Velocities, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawVelocityLineScale = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Locations, Velocities, LineStyle"))` — Debug draw velocities
- L1220 _public prototype_ `static void DrawDebugVelocitiesArrayView(const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const TArrayView<const FVector> Velocities, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawVelocityLineScale = 1.0f);`
- L1224 _public prototype_ `static void DrawDebugTransform(const FDebugDrawer& Drawer, const FTransform& Transform, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Transform, LineStyle"))` — Debug Draw a set of axes at the given transform
- L1227 _public prototype_ `static void DrawDebugTransformsArrayView( const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const TArrayView<const FQuat4f> Rotations, const TArrayView<const FVector3f> Scales, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawRadius = 10.0f);` — Draws an array of transforms
- L1238 _public prototype_ `static void DrawDebugEvent(const FDebugDrawer& Drawer, bool bTimeUntilEventKnown, const float TimeUntilEvent, const FVector& Location, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Size = 20.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, LineStyle"))` — Debug draw a phase-representation of an event at a location
- L1244 _public prototype_ `static void DrawDebugChair(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugChairSettings& Settings = FDrawDebugChairSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug draw a basic chair shape
- L1248 _public prototype_ `static void DrawDebugDoor(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugDoorSettings& Settings = FDrawDebugDoorSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug draw a basic door shape
- L1252 _public prototype_ `static void DrawDebugCamera(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Scale = 10.0f, const float FOVDegrees = 30.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Debug draw a camera shape
- L1256 _public prototype_ `static void DrawDebugBackpack(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugBackpackSettings& Settings = FDrawDebugBackpackSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug draw a backpack
- L1260 _public prototype_ `static void DrawDebugBriefcase(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugBriefcaseSettings& Settings = FDrawDebugBriefcaseSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Debug draw a briefcase
- L1264 _public prototype_ `static void DrawDebugTrajectory(const FDebugDrawer& Drawer, const TArray<FVector>& Locations, const TArray<FVector>& Directions, const FTransform& RelativeTransform = FTransform(), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawArrowLength = 100.0f, const float PointRadius = 5.0f, const float ArrowHeadScale = 1.0f, const int32 Segments = 9, const float VerticalOffset = 2.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Locations, Directions, RelativeTransform, LineStyle"))` — Debug Draw a trajectory of locations and directions
- L1265 _public prototype_ `static void DrawDebugTrajectoryFromArrayViews(const FDebugDrawer& Drawer, const TArrayView<const FVector> Locations, const TArrayView<const FVector> Directions, const FTransform& RelativeTransform = FTransform(), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawArrowLength = 100.0f, const float PointRadius = 5.0f, const float ArrowHeadScale = 1.0f, const int32 Segments = 9, const float VerticalOffset = 2.0f);`
- L1269 _public prototype_ `static void DrawDebugTransformTrajectory(const FDebugDrawer& Drawer, UPARAM(ref) const FTransformTrajectory& TransformTrajectory, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float Radius = 5.0f, const float VerticalOffset = 2.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "TransformTrajectory, LineStyle"))` — Debug Draw a transform trajectory
- L1272 _public prototype_ `static void DrawDebugRangeTrajectoryArrayView( const FDebugDrawer& Drawer, const TArrayView<const FVector> TrajectoryLocations, const TArrayView<const FQuat4f> TrajectoryRotations, const bool bDepthTest = true, const FVector& ForwardVector = FVector::ForwardVector, const bool bDrawOrientations = false, const bool bDrawStartingAtOrigin = false, const FVector& OriginOffset = FVector::ZeroVector);` — Draws a trajectory in the style of trajectory drawing in persona
- L1284 _public prototype_ `static void DrawDebugMoverOrientation(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FVector ForwardVector = FVector::ForwardVector, const float Scale = 30.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle"))` — Draws a flat 2d motif representing mover position and rotation
- L1290 _public prototype_ `static FLinearColor GetDefaultBoneColor();` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Gets the default debug draw bone color
- L1294 _public prototype_ `static float GetDefaultBoneRadius();` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library")` — Gets the default debug draw bone radius
- L1298 _public prototype_ `static void DrawDebugBone(const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f), const bool bDepthTest = true, const float Radius = 5.0f, const int32 Segments = 10, const bool bDrawTransform = false);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation"))` — Debug Draw a bone
- L1302 _public prototype_ `static void DrawDebugBoneLink(const FDebugDrawer& Drawer, const FVector& ChildLocation, const FVector& ParentLocation, const FRotator& ParentRotation, const FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f), const bool bDepthTest = true, const float Radius = 5.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "ChildLocation, ParentLocation, ParentRotation"))` — Debug Draw a link between a child and parent bone
- L1306 _public prototype_ `static void DrawDebugSkeletonFromSkinnedMeshComponent( const FDebugDrawer& Drawer, const USkinnedMeshComponent* SkinnedMeshComponent, const FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f), const bool bDepthTest = false, const FDrawDebugSkeletonSettings& Settings = FDrawDebugSkeletonSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Settings"))` — Draws a skeleton from a skinned mesh component
- L1314 _public prototype_ `static void DrawDebugSkeletonArrayView( const FDebugDrawer& Drawer, const FVector RootLocation, const FQuat4f RootRotation, const TArrayView<const FVector> BoneLocations, const TArrayView<const FQuat4f> BoneRotations, const TArrayView<const int32> BoneIndices, const TArrayView<const int32> BoneParents, const FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f), const bool bDepthTest = false, const FDrawDebugSkeletonSettings& Settings = FDrawDebugSkeletonSettings());` — Draws a skeleton made up of the given bone transforms
- L1327 _public prototype_ `static void DrawDebugBoneVelocitiesArrayView( const FDebugDrawer& Drawer, const TArrayView<const FVector> BoneLocations, const TArrayView<const FVector3f> BoneVelocities, const TArrayView<const int32> BoneIndices, const FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f), const float Thickness = 1.0f, const bool bDepthTest = false, const float Scale = 100.0f);` — Draws lines representing bone velocities
- L1339 _public prototype_ `static void DrawDebugPose(const FDebugDrawer& Drawer, const TArray<FVector>& BoneLocations, const TArray<FVector>& BoneLinearVelocities, const FTransform& RelativeTransform = FTransform(), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawVelocityLineScale = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "BoneLocations, BoneLinearVelocities, RelativeTransform, LineStyle"))` — Debug Draw a pose made up of bone locations and velocities
- L1340 _public prototype_ `static void DrawDebugPoseFromArrayViews(const FDebugDrawer& Drawer, const TArrayView<const FVector> BoneLocations, const TArrayView<const FVector> BoneLinearVelocities, const FTransform& RelativeTransform = FTransform(), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const float DrawVelocityLineScale = 1.0f);`
- L1344 _public prototype_ `static void DrawDebugCurvesFromSkeletalMeshComponent( const FDebugDrawer& Drawer, const USkeletalMeshComponent* SkeletalMeshComponent, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LineStyle, Settings"))` — Draws all of the active curve values from a skeletal mesh component
- L1355 _public prototype_ `static void DrawDebugCurvesToCanvasFromSkeletalMeshComponent( const FDebugDrawer& Drawer, const USkeletalMeshComponent* SkeletalMeshComponent, const FVector2D& Location, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), const FDrawDebugCanvasTextSettings& Settings = FDrawDebugCanvasTextSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Settings"))` — Draws all of the active curve values from a skeletal mesh component as CanvasText. Only does anything with Screen or Canvas drawers.
- L1366 _public prototype_ `static void DrawDebugStaticMeshBoundingBox(const FDebugDrawer& Drawer, const UStaticMesh* StaticMesh, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation"))` — Debug Draw the bounding box of a static mesh
- L1373 _public prototype_ `static int32 DrawDebugStringSegmentNum(const FString& String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String, Settings"))` — Get the number of line segments required to draw debug a string.
- L1374 _public prototype_ `static int32 DrawDebugStringViewSegmentNum(const FStringView String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());`
- L1378 _public prototype_ `static int32 DrawDebugTextSegmentNum(const FText& Text, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text, Settings"))` — Get the number of line segments required to draw debug text.
- L1382 _public prototype_ `static int32 DrawDebugNameSegmentNum(const FName& Name, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Name, Settings"))` — Get the number of line segments required to draw debug a name.
- L1386 _public prototype_ `static FVector DrawDebugStringDimensions(const FString& String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String, Settings"))` — Get the dimensions of a draw debug string. Useful for aligning or centering text.
- L1387 _public prototype_ `static FVector DrawDebugStringViewDimensions(const FStringView String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());`
- L1391 _public prototype_ `static FVector DrawDebugTextDimensions(const FText& Text, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text, Settings"))` — Get the dimensions of a draw debug text. Useful for aligning or centering text.
- L1395 _public prototype_ `static FVector DrawDebugNameDimensions(const FName& Name, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Name, Settings"))` — Get the dimensions of a draw debug name. Useful for aligning or centering text.
- L1399 _public prototype_ `static FVector DrawDebugStringCenteringOffset(const FString& String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String, Settings"))` — Get the local offset required to center a draw debug string.
- L1400 _public prototype_ `static FVector DrawDebugStringViewCenteringOffset(const FStringView String, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());`
- L1404 _public prototype_ `static FVector DrawDebugTextCenteringOffset(const FText& Text, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text, Settings"))` — Get the local offset required to center a draw debug text.
- L1408 _public prototype_ `static FVector DrawDebugNameCenteringOffset(const FName& Name, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintPure, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Name, Settings"))` — Get the local offset required to center a draw debug name.
- L1412 _public prototype_ `static void DrawDebugString(const FDebugDrawer& Drawer, const FString& String, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String, Location, Rotation, LineStyle, Settings"))` — Debug Draw a string. Will only render ASCII characters.
- L1413 _public prototype_ `static void DrawDebugStringView(const FDebugDrawer& Drawer, const FStringView String, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());`
- L1417 _public prototype_ `static void DrawDebugName(const FDebugDrawer& Drawer, const FName& Name, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Name, Location, Rotation, LineStyle, Settings"))` — Debug Draw a name
- L1421 _public prototype_ `static void DrawDebugNames(const FDebugDrawer& Drawer, const TArray<FName>& Names, const FVector& Location, const FRotator& Rotation, const FString& Separator = TEXT(", "), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings()` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Names, Location, Rotation, LineStyle, Settings"))` — Debug Draw several names
- L1422 _public prototype_ `static void DrawDebugNamesArrayView(const FDebugDrawer& Drawer, const TArrayView<const FName> Names, const FVector& Location, const FRotator& Rotation, const FStringView Separator = TEXT(", "), const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings()`
- L1426 _public prototype_ `static void DrawDebugText(const FDebugDrawer& Drawer, const FText& Text, const FVector& Location, const FRotator& Rotation, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugStringSettings& Settings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text, Location, Rotation, LineStyle, Settings"))` — Debug Draw some text. Will only render ASCII characters.
- L1432 _public prototype_ `static void VisualLoggerDrawString(const FDebugDrawer& Drawer, const FString& String, const FVector& Location, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "String, Location"))` — Debug Draw a string to the visual logger. Will do nothing if not using a VisualLoggerDrawer. Will not display on-screen during recording.
- L1433 _public prototype_ `static void VisualLoggerDrawStringView(const FDebugDrawer& Drawer, const FStringView String, const FVector& Location, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));`
- L1437 _public prototype_ `static void VisualLoggerDrawName(const FDebugDrawer& Drawer, const FName& Name, const FVector& Location, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Name, Location"))` — Debug Draw a name to the visual logger. Will do nothing if not using a VisualLoggerDrawer. Will not display on-screen during recording.
- L1441 _public prototype_ `static void VisualLoggerDrawText(const FDebugDrawer& Drawer, const FText& Text, const FVector& Location, const FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Text, Location"))` — Debug Draw some text to the visual logger. Will do nothing if not using a VisualLoggerDrawer. Will not display on-screen during recording.
- L1447 _public prototype_ `static void DrawDebugGraph( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArray<float>& Xvalues, const TArray<float>& Yvalues, const float Xmin = 0.0f, const float Xmax = 1.0f, const float Ymin = 0.0f, const float Ymax = 1.0f, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& AxesLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& PlotLineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugGraphAxesSettings& AxesSettings = FDrawDebugGraphAxesSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, TextLineStyle, AxesLineStyle, PlotLineStyle, AxesSettings"))` — Debug Draw a simple graph.
- L1465 _public prototype_ `static void DrawDebugGraphArrayView( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArrayView<const float> Xvalues, const TArrayView<const float> Yvalues, const float Xmin = 0.0f, const float Xmax = 1.0f, const float Ymin = 0.0f, const float Ymax = 1.0f, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& AxesLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& PlotLineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugGraphAxesSettings& AxesSettings = FDrawDebugGraphAxesSettings());`
- L1485 _public prototype_ `static void DrawDebugGraphAxesLabels( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugGraphAxesSettings& AxesSettings = FDrawDebugGraphAxesSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, TextLineStyle, AxesSettings"))` — Debug Draw a simple graph axes labels.
- L1497 _public prototype_ `static void DrawDebugGraphAxes( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& AxesLineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true, const FDrawDebugGraphAxesSettings& AxesSettings = FDrawDebugGraphAxesSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, TextLineStyle, AxesLineStyle, AxesSettings"))` — Debug Draw a simple graph axes.
- L1510 _public prototype_ `static void DrawDebugGraphLine( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArray<float>& Xvalues, const TArray<float>& Yvalues, const float Xmin = 0.0f, const float Xmax = 1.0f, const float Ymin = 0.0f, const float Ymax = 1.0f, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, Xvalues, Yvalues, LineStyle"))` — Debug Draw a line on a simple graph.
- L1525 _public prototype_ `static void DrawDebugGraphLineArrayView( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArrayView<const float> Xvalues, const TArrayView<const float> Yvalues, const float Xmin = 0.0f, const float Xmax = 1.0f, const float Ymin = 0.0f, const float Ymax = 1.0f, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& LineStyle = FDrawDebugLineStyle(), const bool bDepthTest = true);`
- L1542 _public prototype_ `static void DrawDebugGraphLegend( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArray<FLinearColor>& LegendColors, const TArray<FString>& LegendLabels, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& IconLineStyle = FDrawDebugLineStyle(), const float IconSize = 2.5f, const bool bDepthTest = true, const FDrawDebugStringSettings& LegendSettings = FDrawDebugStringSettings());` — `UFUNCTION(BlueprintCallable, Category = "Draw Debug Library", meta = (DevelopmentOnly, AutoCreateRefTerm = "Location, Rotation, LegendColors, LegendLabels, TextLineStyle, IconLineStyle, LegendSettings"))` — Debug Draw a simple graph legend.
- L1556 _public prototype_ `static void DrawDebugGraphLegendArrayView( const FDebugDrawer& Drawer, const FVector& Location, const FRotator& Rotation, const TArrayView<const FLinearColor> LegendColors, const TArrayView<const FString> LegendLabels, const float XaxisLength = 100.0f, const float YaxisLength = 100.0f, const FDrawDebugLineStyle& TextLineStyle = FDrawDebugLineStyle(), const FDrawDebugLineStyle& IconLineStyle = FDrawDebugLineStyle(), const float IconSize = 2.5f, const bool bDepthTest = true, const FDrawDebugStringSettings& LegendSettings = FDrawDebugStringSettings());`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DRAWDEBUGLIBRARY_API`

### `Plugins/Experimental/DrawDebugLibrary/Source/DrawDebugLibrary/Public/RigUnit_DrawDebugLibrary.h` (Public)


#### struct `FRigVMFunction_DrawDebugLibraryBase`  
`struct FRigVMFunction_DrawDebugLibraryBase : public FRigVMStruct`  
_L17-20_
- reflection: `USTRUCT(meta = (Abstract, Category = "Draw Debug Library", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: The base class for all draw debug library functions

#### struct `FRigUnit_DrawDebugLibraryBase`  
`struct FRigUnit_DrawDebugLibraryBase : public FRigVMStruct`  
_L26-33_
- reflection: `USTRUCT(meta=(Abstract, ExecuteContext = "FRigVMExecuteContext", Category="Draw Debug Library", NodeColor = "0.83077 0.846873 0.049707", DocumentationPolicy = "Strict"))`
- inherits: `FRigVMStruct`
- desc: Base class for all draw debug library rig units
- L32 _public member_ `FRigVMExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

#### struct `FRigVMFunction_MakeNullDebugDrawer`  
`struct FRigVMFunction_MakeNullDebugDrawer : public FRigVMFunction_DrawDebugLibraryBase`  
_L37-47_
- reflection: `USTRUCT(meta = (DisplayName = "Make Null Debug Drawer"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Makes a null debug drawer
- L41 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L46 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Output))` — Debug Drawer

#### struct `FRigVMFunction_MakeDebugDrawer`  
`struct FRigVMFunction_MakeDebugDrawer : public FRigVMFunction_DrawDebugLibraryBase`  
_L51-61_
- reflection: `USTRUCT(meta = (DisplayName = "Make Debug Drawer"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Makes a normal RigVM debug drawer
- L55 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L60 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Output))` — Debug Drawer

#### struct `FRigVMFunction_MakeVisualLoggerDebugDrawer`  
`struct FRigVMFunction_MakeVisualLoggerDebugDrawer : public FRigVMFunction_DrawDebugLibraryBase`  
_L65-83_
- reflection: `USTRUCT(meta = (DisplayName = "Make Visual Logger Debug Drawer"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Makes a debug drawer for the visual logger.
- L69 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L74 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Output))` — Debug Drawer
- L78 _public member_ `FName Category = TEXT("Log` — `UPROPERTY(meta = (Input))` — Log Category
- L82 _public member_ `EDrawDebugLogVerbosity Verbosity = EDrawDebugLogVerbosity::Display;` — `UPROPERTY(meta = (Input))` — Log Verbosity

#### struct `FRigVMFunction_MakeMergedDebugDrawer`  
`struct FRigVMFunction_MakeMergedDebugDrawer : public FRigVMFunction_DrawDebugLibraryBase`  
_L87-101_
- reflection: `USTRUCT(meta = (DisplayName = "Make Merged Debug Drawer"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Makes a merged debug drawer
- L91 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L96 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Output))` — Debug Drawer
- L100 _public member_ `TArray<FDebugDrawer> Drawers;` — `UPROPERTY(meta = (Input))` — Input Drawers

#### struct `FRigUnit_VisualLoggerLogString`  
`struct FRigUnit_VisualLoggerLogString : public FRigUnit_DrawDebugLibraryBase`  
_L105-123_
- reflection: `USTRUCT(meta = (DisplayName = "Visual Logger Log Strong"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Log a string to the visual logger. Only does anything with a VisualLoggerDebugDrawer
- L109 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L114 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L118 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to log
- L122 _public member_ `FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(meta = (Input))` — Log Color

#### struct `FRigVMFunction_MakeLinearlySpacedFloatArray`  
`struct FRigVMFunction_MakeLinearlySpacedFloatArray : public FRigVMFunction_DrawDebugLibraryBase`  
_L127-149_
- reflection: `USTRUCT(meta = (DisplayName = "Make Linearly Spaced Float Array"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Convenience function for making an array of linearly spaced float values
- L131 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L136 _public member_ `float Start = 0.0f;` — `UPROPERTY(meta = (Input))` — Start Value
- L140 _public member_ `float Stop = 1.0f;` — `UPROPERTY(meta = (Input))` — Stop Value
- L144 _public member_ `float Num = 10;` — `UPROPERTY(meta = (Input))` — Value Num
- L148 _public member_ `TArray<float> Values;` — `UPROPERTY(meta = (Output))` — Output Values

#### struct `FRigUnit_AddToFloatHistoryArray`  
`struct FRigUnit_AddToFloatHistoryArray : public FRigUnit_DrawDebugLibraryBase`  
_L153-171_
- reflection: `USTRUCT(meta = (DisplayName = "Add to Float History Array"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Convenience function that adds a float to the end of an array, popping values from the front once the max is reached
- L157 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L162 _public member_ `float NewValue = 0.0f;` — `UPROPERTY(meta = (Input))` — New value to add
- L166 _public member_ `int32 MaxHistoryNum = 60;` — `UPROPERTY(meta = (Input))` — Maximum number of values
- L170 _public member_ `TArray<float> Values;` — `UPROPERTY(meta = (Input, Output))` — Log Color

#### struct `FRigUnit_AddToVectorHistoryArray`  
`struct FRigUnit_AddToVectorHistoryArray : public FRigUnit_DrawDebugLibraryBase`  
_L175-193_
- reflection: `USTRUCT(meta = (DisplayName = "Add to Vector History Array"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Convenience function that adds a vector to the end of an array, popping values from the front once the max is reached
- L179 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L184 _public member_ `FVector NewValue = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — New value to add
- L188 _public member_ `int32 MaxHistoryNum = 60;` — `UPROPERTY(meta = (Input))` — Maximum number of values
- L192 _public member_ `TArray<FVector> Values;` — `UPROPERTY(meta = (Input, Output))` — Log Color

#### struct `FRigUnit_AddToNameHistoryArray`  
`struct FRigUnit_AddToNameHistoryArray : public FRigUnit_DrawDebugLibraryBase`  
_L197-215_
- reflection: `USTRUCT(meta = (DisplayName = "Add to Name History Array"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Convenience function that adds a name to the end of an array, popping values from the front once the max is reached
- L201 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L206 _public member_ `FName NewValue = NAME_None;` — `UPROPERTY(meta = (Input))` — New value to add
- L210 _public member_ `int32 MaxHistoryNum = 60;` — `UPROPERTY(meta = (Input))` — Maximum number of values
- L214 _public member_ `TArray<FName> Values;` — `UPROPERTY(meta = (Input, Output))` — Log Color

#### struct `FRigVMFunction_DrawDebugLocalOffset`  
`struct FRigVMFunction_DrawDebugLocalOffset : public FRigVMFunction_DrawDebugLibraryBase`  
_L219-245_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Local Offset"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Returns a new location and rotation after applying a local offset to the input draw location and rotation
- L223 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L228 _public member_ `FVector DrawLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Input Draw Location
- L232 _public member_ `FRotator DrawRotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Input Draw Rotation
- L236 _public member_ `FVector DrawOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Offset in the local space
- L240 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Location
- L244 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Output))` — Output Rotation

#### struct `FRigVMFunction_DrawDebugOrientUprightToFloor`  
`struct FRigVMFunction_DrawDebugOrientUprightToFloor : public FRigVMFunction_DrawDebugLibraryBase`  
_L249-271_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Orient Upright to Floor"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Returns a new location and rotation after applying a local offset to the input draw location and rotation
- L253 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L258 _public member_ `FVector DrawWorldLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw location
- L262 _public member_ `FVector DrawUprightOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw offset in local space
- L266 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Location
- L270 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Output))` — Output Rotation

#### struct `FRigVMFunction_DrawDebugOrientFloorToUpright`  
`struct FRigVMFunction_DrawDebugOrientFloorToUpright : public FRigVMFunction_DrawDebugLibraryBase`  
_L275-297_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Orient Floor to Upright"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Create a new location and rotation that orients debug drawing of floor objects such as shapes upright
- L279 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L284 _public member_ `FVector DrawWorldLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw location
- L288 _public member_ `FVector DrawFloorOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw offset in local space
- L292 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Location
- L296 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Output))` — Output Rotation

#### struct `FRigVMFunction_DrawDebugOrientUprightToCamera`  
`struct FRigVMFunction_DrawDebugOrientUprightToCamera : public FRigVMFunction_DrawDebugLibraryBase`  
_L301-331_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Orient Upright to Camera"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Create a new location and rotation that orients debug drawing of upright objects such as text to face the camera
- L305 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L310 _public member_ `FVector DrawWorldLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw location
- L314 _public member_ `FVector DrawUprightOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw offset in local space
- L318 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Camera Rotation
- L322 _public member_ `bool bUseOnlyYaw = false;` — `UPROPERTY(meta = (Input))` — If to only oriented to the camera yaw
- L326 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Location
- L330 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Output))` — Output Rotation

#### struct `FRigVMFunction_DrawDebugOrientFloorToCamera`  
`struct FRigVMFunction_DrawDebugOrientFloorToCamera : public FRigVMFunction_DrawDebugLibraryBase`  
_L335-365_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Orient Floor to Camera"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Create a new location and rotation that orients debug drawing of floor objects such as shapes to face the camera
- L339 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L344 _public member_ `FVector DrawWorldLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw location
- L348 _public member_ `FVector DrawFloorOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw offset in local space
- L352 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Camera Rotation
- L356 _public member_ `bool bUseOnlyYaw = false;` — `UPROPERTY(meta = (Input))` — If to only oriented to the camera yaw
- L360 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Location
- L364 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Output))` — Output Rotation

#### struct `FRigUnit_DrawDebugPoint`  
`struct FRigUnit_DrawDebugPoint : public FRigUnit_DrawDebugLibraryBase`  
_L369-391_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Point"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a point
- L373 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L378 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L382 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Point Location
- L386 _public member_ `FDrawDebugPointStyle PointStyle;` — `UPROPERTY(meta = (Input))` — Point Style
- L390 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugPoints`  
`struct FRigUnit_DrawDebugPoints : public FRigUnit_DrawDebugLibraryBase`  
_L395-417_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Points"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw points. These should be preferred over DrawDebugPoint where possible as it will batch drawing when required such as when using the visual logger.
- L399 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L404 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L408 _public member_ `TArray<FVector> Locations;` — `UPROPERTY(meta = (Input))` — Point Locations
- L412 _public member_ `FDrawDebugPointStyle PointStyle;` — `UPROPERTY(meta = (Input))` — Point Style
- L416 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugLine`  
`struct FRigUnit_DrawDebugLine : public FRigUnit_DrawDebugLibraryBase`  
_L421-447_
- reflection: `USTRUCT(meta=(DisplayName="Draw Debug Line"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draws a line
- L425 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L430 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L434 _public member_ `FVector StartLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Line Start Location
- L438 _public member_ `FVector EndLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Line End Location
- L442 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L446 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugLines`  
`struct FRigUnit_DrawDebugLines : public FRigUnit_DrawDebugLibraryBase`  
_L451-477_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Lines"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draws lines. These should be preferred over DrawDebugLine where possible as it will batch drawing when required such as when using the visual logger.
- L455 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L460 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L464 _public member_ `TArray<FVector> StartLocations;` — `UPROPERTY(meta = (Input))` — Line Start Locations
- L468 _public member_ `TArray<FVector> EndLocations;` — `UPROPERTY(meta = (Input))` — Line End Locations
- L472 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L476 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugTriangularBasePyramid`  
`struct FRigUnit_DrawDebugTriangularBasePyramid : public FRigUnit_DrawDebugLibraryBase`  
_L481-515_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Triangular Base Pyramid"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a triangular base pyramid
- L485 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L490 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L494 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L498 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L502 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L506 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L510 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Pyramid Length
- L514 _public member_ `float Width = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Pyramid Width

#### struct `FRigUnit_DrawDebugSquareBasePyramid`  
`struct FRigUnit_DrawDebugSquareBasePyramid : public FRigUnit_DrawDebugLibraryBase`  
_L519-553_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Square Base Pyramid"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a square base pyramid
- L523 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L528 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L532 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L536 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L540 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L544 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L548 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Pyramid Length
- L552 _public member_ `float Width = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Pyramid Width

#### struct `FRigUnit_DrawDebugCone`  
`struct FRigUnit_DrawDebugCone : public FRigUnit_DrawDebugLibraryBase`  
_L557-595_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Cone"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a cone
- L561 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L566 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L570 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L574 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L578 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L582 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L586 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Cone Length
- L590 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Cone Radius
- L594 _public member_ `int32 Segments = 9;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugConeLookAt`  
`struct FRigUnit_DrawDebugConeLookAt : public FRigUnit_DrawDebugLibraryBase`  
_L599-637_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Cone Look At"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a cone starting from the point oriented on the forward axis, with the given angle
- L603 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L608 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L612 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L616 _public member_ `FVector Direction = FVector::ForwardVector;` — `UPROPERTY(meta = (Input))` — Draw Direction
- L620 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L624 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L628 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Cone Length
- L632 _public member_ `float Angle = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Cone Angle
- L636 _public member_ `int32 Segments = 9;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugArc`  
`struct FRigUnit_DrawDebugArc : public FRigUnit_DrawDebugLibraryBase`  
_L641-679_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Arc"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arc around the XY axis
- L645 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L650 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L654 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L658 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L662 _public member_ `float Angle = 360.0f;` — `UPROPERTY(meta = (Input, ForceUnits="deg"))` — Arc Angle
- L666 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L670 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L674 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Arc Radius
- L678 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugCircle`  
`struct FRigUnit_DrawDebugCircle : public FRigUnit_DrawDebugLibraryBase`  
_L683-717_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Circle"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an circle around the XY axis
- L687 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L692 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L696 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L700 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L704 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L708 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L712 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Circle Radius
- L716 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugCircleTick`  
`struct FRigUnit_DrawDebugCircleTick : public FRigUnit_DrawDebugLibraryBase`  
_L721-763_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Circle Tick"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an tick on a circle at a given angle
- L725 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L730 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L734 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L738 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L742 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Tick Angle
- L746 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L750 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L754 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Circle Radius
- L758 _public member_ `float Length = 2.5f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Tick Length Radius
- L762 _public member_ `bool bInside = true;` — `UPROPERTY(meta = (Input))` — If to draw the tick on the inside or outside

#### struct `FRigUnit_DrawDebugCircleTicks`  
`struct FRigUnit_DrawDebugCircleTicks : public FRigUnit_DrawDebugLibraryBase`  
_L767-809_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Circle Ticks"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw ticks on a circle at the given angles
- L771 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L776 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L780 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L784 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L788 _public member_ `TArray<float> Angles;` — `UPROPERTY(meta = (Input))` — Tick Angles
- L792 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L796 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L800 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Circle Radius
- L804 _public member_ `float Length = 2.5f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Tick Length Radius
- L808 _public member_ `bool bInside = true;` — `UPROPERTY(meta = (Input))` — If to draw the tick on the inside or outside

#### struct `FRigUnit_DrawDebugCircleOutline`  
`struct FRigUnit_DrawDebugCircleOutline : public FRigUnit_DrawDebugLibraryBase`  
_L814-852_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Circle Outline"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw the outline of a circle (two circles) around the XY axis
- L818 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L823 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L827 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L831 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L835 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L839 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L843 _public member_ `float InnerRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Inner Circle Radius
- L847 _public member_ `float OuterRadius = 15.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Outer Circle Radius
- L851 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugTriangle`  
`struct FRigUnit_DrawDebugTriangle : public FRigUnit_DrawDebugLibraryBase`  
_L856-886_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Triangle"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a triangle on the XY axis
- L860 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L865 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L869 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L873 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L877 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L881 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L885 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Triangle Radius

#### struct `FRigUnit_DrawDebugSquare`  
`struct FRigUnit_DrawDebugSquare : public FRigUnit_DrawDebugLibraryBase`  
_L890-920_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Square"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a square on the XY axis
- L894 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L899 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L903 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L907 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L911 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L915 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L919 _public member_ `float HalfLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-length of the square

#### struct `FRigUnit_DrawDebugCross`  
`struct FRigUnit_DrawDebugCross : public FRigUnit_DrawDebugLibraryBase`  
_L924-954_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Cross"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a cross on the XY axis
- L928 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L933 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L937 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L941 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L945 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L949 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L953 _public member_ `float HalfLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-length of the cross

#### struct `FRigUnit_DrawDebugDiamond`  
`struct FRigUnit_DrawDebugDiamond : public FRigUnit_DrawDebugLibraryBase`  
_L958-988_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Diamond"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a diamond on the XY axis
- L962 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L967 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L971 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L975 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L979 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L983 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L987 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugPentagon`  
`struct FRigUnit_DrawDebugPentagon : public FRigUnit_DrawDebugLibraryBase`  
_L992-1022_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Pentagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a pentagon on the XY axis
- L996 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1001 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1005 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1009 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1013 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1017 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1021 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugHexagon`  
`struct FRigUnit_DrawDebugHexagon : public FRigUnit_DrawDebugLibraryBase`  
_L1026-1056_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Hexagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a hexagon on the XY axis
- L1030 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1035 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1039 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1043 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1047 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1051 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1055 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugHeptagon`  
`struct FRigUnit_DrawDebugHeptagon : public FRigUnit_DrawDebugLibraryBase`  
_L1060-1090_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Heptagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a heptagon on the XY axis
- L1064 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1069 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1073 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1077 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1081 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1085 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1089 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugOctagon`  
`struct FRigUnit_DrawDebugOctagon : public FRigUnit_DrawDebugLibraryBase`  
_L1094-1124_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Octagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a octagon on the XY axis
- L1098 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1103 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1107 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1111 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1115 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1119 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1123 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugNonagon`  
`struct FRigUnit_DrawDebugNonagon : public FRigUnit_DrawDebugLibraryBase`  
_L1128-1158_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Nonagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a nonagon on the XY axis
- L1132 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1137 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1141 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1145 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1149 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1153 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1157 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugDecagon`  
`struct FRigUnit_DrawDebugDecagon : public FRigUnit_DrawDebugLibraryBase`  
_L1162-1192_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Decagon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a decagon on the XY axis
- L1166 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1171 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1175 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1179 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1183 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1187 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1191 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugRegularPolygon`  
`struct FRigUnit_DrawDebugRegularPolygon : public FRigUnit_DrawDebugLibraryBase`  
_L1196-1230_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Regular Polygon"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a flat regular polygon on the XY axis
- L1200 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1205 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1209 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1213 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1217 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1221 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1225 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape
- L1229 _public member_ `int32 Sides = 11;` — `UPROPERTY(meta = (Input))` — Number of sides

#### struct `FRigUnit_DrawDebugCheckMark`  
`struct FRigUnit_DrawDebugCheckMark : public FRigUnit_DrawDebugLibraryBase`  
_L1234-1264_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Check Mark"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a check mark on the XY axis
- L1238 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1243 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1247 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1251 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1255 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1259 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1263 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the shape

#### struct `FRigUnit_DrawDebugCheckBox`  
`struct FRigUnit_DrawDebugCheckBox : public FRigUnit_DrawDebugLibraryBase`  
_L1268-1306_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Check Box"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a checkbox on the XY axis
- L1272 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1277 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1281 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1285 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1289 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1293 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1297 _public member_ `float HalfLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-length of the check box
- L1301 _public member_ `bool bChecked = false;` — `UPROPERTY(meta = (Input))` — If the check box is checked
- L1305 _public member_ `float TickRatio = 1.75f;` — `UPROPERTY(meta = (Input))` — Size of the tick mark in proportion to the box

#### struct `FRigUnit_DrawDebugCrossBox`  
`struct FRigUnit_DrawDebugCrossBox : public FRigUnit_DrawDebugLibraryBase`  
_L1310-1348_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Cross Box"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a cross box on the XY axis
- L1314 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1319 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1323 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1327 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1331 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1335 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1339 _public member_ `float HalfLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-length of the cross box
- L1343 _public member_ `bool bCrossed = false;` — `UPROPERTY(meta = (Input))` — If the cross box is marked
- L1347 _public member_ `float CrossRatio = 1.0f;` — `UPROPERTY(meta = (Input))` — Size of the cross mark in proportion to the box

#### struct `FRigUnit_DrawDebugRadioButton`  
`struct FRigUnit_DrawDebugRadioButton : public FRigUnit_DrawDebugLibraryBase`  
_L1352-1394_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Radio Button"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a radio button on the XY axis
- L1356 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1361 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1365 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1369 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1373 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1377 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1381 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the radio button
- L1385 _public member_ `bool bSelected = false;` — `UPROPERTY(meta = (Input))` — If the radio button is selected marked
- L1389 _public member_ `float InnerButtonRatio = 0.5f;` — `UPROPERTY(meta = (Input))` — Ratio of the inner button compared to the outer circle
- L1393 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugLocator`  
`struct FRigUnit_DrawDebugLocator : public FRigUnit_DrawDebugLibraryBase`  
_L1398-1428_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Locator"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an axis-aligned cross
- L1402 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1407 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1411 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1415 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1419 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1423 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1427 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the radio button

#### struct `FRigUnit_DrawDebugCrossLocator`  
`struct FRigUnit_DrawDebugCrossLocator : public FRigUnit_DrawDebugLibraryBase`  
_L1432-1462_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Cross Locator"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an axis-aligned cross rotated by 45 degrees
- L1436 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1441 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1445 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1449 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1453 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1457 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1461 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the radio button

#### struct `FRigUnit_DrawDebugBox`  
`struct FRigUnit_DrawDebugBox : public FRigUnit_DrawDebugLibraryBase`  
_L1466-1496_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Box"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an oriented box
- L1470 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1475 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1479 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1483 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1487 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1491 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1495 _public member_ `FVector HalfExtents = FVector(10.0f, 10.0f, 10.0f);` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-extents of the box

#### struct `FRigUnit_DrawDebugSphere`  
`struct FRigUnit_DrawDebugSphere : public FRigUnit_DrawDebugLibraryBase`  
_L1500-1534_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Sphere"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a sphere
- L1504 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1509 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1513 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1517 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1521 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1525 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1529 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere
- L1533 _public member_ `int32 Segments = 8;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugSimpleSphere`  
`struct FRigUnit_DrawDebugSimpleSphere : public FRigUnit_DrawDebugLibraryBase`  
_L1538-1572_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Simple Sphere"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a simple sphere made up of three circles one of each axis
- L1542 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1547 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1551 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1555 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1559 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1563 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1567 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere
- L1571 _public member_ `int32 Segments = 13;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugCapsule`  
`struct FRigUnit_DrawDebugCapsule : public FRigUnit_DrawDebugLibraryBase`  
_L1576-1614_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Capsule"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a capsule
- L1580 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1585 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1589 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1593 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1597 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1601 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1605 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere
- L1609 _public member_ `float HalfLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Half-Length of the capsule
- L1613 _public member_ `int32 Segments = 8;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugCapsuleLine`  
`struct FRigUnit_DrawDebugCapsuleLine : public FRigUnit_DrawDebugLibraryBase`  
_L1618-1652_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Capsule Line"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a capsule using the start and end location
- L1622 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1627 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1631 _public member_ `FVector StartLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Start Location
- L1635 _public member_ `FVector EndLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw End Location
- L1639 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1643 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1647 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere
- L1651 _public member_ `int32 Segments = 8;` — `UPROPERTY(meta = (Input))` — Number of segments

#### struct `FRigUnit_DrawDebugFrustum`  
`struct FRigUnit_DrawDebugFrustum : public FRigUnit_DrawDebugLibraryBase`  
_L1656-1678_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Frustum"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a Frustum
- L1660 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1665 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1669 _public member_ `FMatrix FrustumToWorld = FMatrix::Identity;` — `UPROPERTY(meta = (Input))` — Frustum Matrix
- L1673 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1677 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugArrowHead`  
`struct FRigUnit_DrawDebugArrowHead : public FRigUnit_DrawDebugLibraryBase`  
_L1682-1716_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Arrow Head"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arrow head
- L1686 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1691 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1695 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1699 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1703 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1707 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1711 _public member_ `EDrawDebugArrowHead Type = EDrawDebugArrowHead::Simple;` — `UPROPERTY(meta = (Input))` — Arrow Head Type
- L1715 _public member_ `float Size = 5.0f;` — `UPROPERTY(meta = (Input))` — Arrow Head Size

#### struct `FRigUnit_DrawDebugArrow`  
`struct FRigUnit_DrawDebugArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1720-1750_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arrow
- L1724 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1729 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1733 _public member_ `FVector StartLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Start Location
- L1737 _public member_ `FVector EndLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw End Location
- L1741 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1745 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1749 _public member_ `FDrawDebugArrowSettings Settings;` — `UPROPERTY(meta = (Input))` — Arrow Settings

#### struct `FRigUnit_DrawDebugOrientedArrow`  
`struct FRigUnit_DrawDebugOrientedArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1754-1788_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Oriented Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arrow with an orientation
- L1758 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1763 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1767 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1771 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1775 _public member_ `float Length = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow
- L1779 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1783 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1787 _public member_ `FDrawDebugArrowSettings Settings;` — `UPROPERTY(meta = (Input))` — Arrow Settings

#### struct `FRigUnit_DrawDebugGroundTargetArrow`  
`struct FRigUnit_DrawDebugGroundTargetArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1792-1830_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Ground Target Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Draws an arrow pointing down at the location surrounded by a circle
- L1796 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1801 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1805 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1809 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1813 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1817 _public member_ `float Length = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow
- L1821 _public member_ `float ArrowHeadSize = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Size of the arrow head
- L1825 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the target circle
- L1829 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments of the target circle

#### struct `FRigUnit_DrawDebugFlatArrow`  
`struct FRigUnit_DrawDebugFlatArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1834-1868_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Flat Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Draws a flat 2d arrow motif
- L1838 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1843 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1847 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1851 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1855 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1859 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1863 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow
- L1867 _public member_ `float Width = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Width of the arrow

#### struct `FRigUnit_DrawDebugCircleArrow`  
`struct FRigUnit_DrawDebugCircleArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1872-1914_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Circle Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arrow coming off a circle at a given angle
- L1876 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1881 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1885 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1889 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1893 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Angle at which to draw the arrow
- L1897 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1901 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1905 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the circle
- L1909 _public member_ `float Length = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow
- L1913 _public member_ `FDrawDebugArrowSettings Settings;` — `UPROPERTY(meta = (Input))` — Arrow Settings

#### struct `FRigUnit_DrawDebugArcArrow`  
`struct FRigUnit_DrawDebugArcArrow : public FRigUnit_DrawDebugLibraryBase`  
_L1918-1960_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Arc Arrow"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arc around the XY axis with arrow heads
- L1922 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1927 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1931 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L1935 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L1939 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Angle at which to draw the arrow
- L1943 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1947 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1951 _public member_ `float Radius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the circle
- L1955 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments in the arc
- L1959 _public member_ `FDrawDebugArrowSettings Settings;` — `UPROPERTY(meta = (Input))` — Arrow Settings

#### struct `FRigUnit_DrawDebugCatmullRomSplineStart`  
`struct FRigUnit_DrawDebugCatmullRomSplineStart : public FRigUnit_DrawDebugLibraryBase`  
_L1964-2002_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Catmull Rom Spline Start"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw the start section of a catmull rom spline
- L1968 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L1973 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L1977 _public member_ `FVector V0 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 0
- L1981 _public member_ `FVector V1 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 1
- L1985 _public member_ `FVector V2 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 2
- L1989 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L1993 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L1997 _public member_ `bool bMonotonic = false;` — `UPROPERTY(meta = (Input))` — If to draw a monotonic spline
- L2001 _public member_ `int32 Segments = 15;` — `UPROPERTY(meta = (Input))` — Number of segments in the spline segment

#### struct `FRigUnit_DrawDebugCatmullRomSplineEnd`  
`struct FRigUnit_DrawDebugCatmullRomSplineEnd : public FRigUnit_DrawDebugLibraryBase`  
_L2006-2044_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Catmull Rom Spline End"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw the end section of a catmull rom spline
- L2010 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2015 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2019 _public member_ `FVector V0 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 0
- L2023 _public member_ `FVector V1 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 1
- L2027 _public member_ `FVector V2 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 2
- L2031 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2035 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2039 _public member_ `bool bMonotonic = false;` — `UPROPERTY(meta = (Input))` — If to draw a monotonic spline
- L2043 _public member_ `int32 Segments = 15;` — `UPROPERTY(meta = (Input))` — Number of segments in the spline segment

#### struct `FRigUnit_DrawDebugCatmullRomSplineSection`  
`struct FRigUnit_DrawDebugCatmullRomSplineSection : public FRigUnit_DrawDebugLibraryBase`  
_L2048-2090_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Catmull Rom Spline Section"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a full segment of a catmull rom spline
- L2052 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2057 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2061 _public member_ `FVector V0 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 0
- L2065 _public member_ `FVector V1 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 1
- L2069 _public member_ `FVector V2 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 2
- L2073 _public member_ `FVector V3 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Vertex 3
- L2077 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2081 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2085 _public member_ `bool bMonotonic = false;` — `UPROPERTY(meta = (Input))` — If to draw a monotonic spline
- L2089 _public member_ `int32 Segments = 15;` — `UPROPERTY(meta = (Input))` — Number of segments in the spline segment

#### struct `FRigUnit_DrawDebugCatmullRomSpline`  
`struct FRigUnit_DrawDebugCatmullRomSpline : public FRigUnit_DrawDebugLibraryBase`  
_L2094-2124_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Catmull Rom Spline"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a catmull rom spline
- L2098 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2103 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2107 _public member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (Input))` — Spline Points
- L2111 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2115 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2119 _public member_ `bool bMonotonic = false;` — `UPROPERTY(meta = (Input))` — If to draw a monotonic spline
- L2123 _public member_ `int32 Segments = 15;` — `UPROPERTY(meta = (Input))` — Number of segments in the spline segment

#### struct `FRigUnit_DrawDebugAngle`  
`struct FRigUnit_DrawDebugAngle : public FRigUnit_DrawDebugLibraryBase`  
_L2129-2171_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Angle"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an angle
- L2133 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2138 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2142 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2146 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2150 _public member_ `float Angle = 0.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Angle to draw
- L2154 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2158 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2162 _public member_ `float LineLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the line
- L2166 _public member_ `float AngleRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the angular arc
- L2170 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments in the arc

#### struct `FRigUnit_DrawDebugAngleBetween`  
`struct FRigUnit_DrawDebugAngleBetween : public FRigUnit_DrawDebugLibraryBase`  
_L2175-2213_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Angle Between"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw the angle between the vectors P0 - P1 and P2 - P1
- L2179 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2184 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2188 _public member_ `FVector P0 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Point P0
- L2192 _public member_ `FVector P1 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Point P1
- L2196 _public member_ `FVector P2 = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Point P2
- L2200 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2204 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2208 _public member_ `float AngleRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the angular arc
- L2212 _public member_ `int32 Segments = 17;` — `UPROPERTY(meta = (Input))` — Number of segments in the arc

#### struct `FRigUnit_DrawDebugLocation`  
`struct FRigUnit_DrawDebugLocation : public FRigUnit_DrawDebugLibraryBase`  
_L2217-2247_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Location"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a sphere at the given location
- L2221 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2226 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2230 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2234 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2238 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2242 _public member_ `float DrawRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere to draw
- L2246 _public member_ `int32 Segments = 8;` — `UPROPERTY(meta = (Input))` — Number of segments in the sphere

#### struct `FRigUnit_DrawDebugLocations`  
`struct FRigUnit_DrawDebugLocations : public FRigUnit_DrawDebugLibraryBase`  
_L2251-2281_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Locations"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw spheres at the given locations
- L2255 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2260 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2264 _public member_ `TArray<FVector> Locations;` — `UPROPERTY(meta = (Input))` — Draw Locations
- L2268 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2272 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2276 _public member_ `float DrawRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere to draw
- L2280 _public member_ `int32 Segments = 8;` — `UPROPERTY(meta = (Input))` — Number of segments in the sphere

#### struct `FRigUnit_DrawDebugRotation`  
`struct FRigUnit_DrawDebugRotation : public FRigUnit_DrawDebugLibraryBase`  
_L2286-2316_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Rotation"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Draws a rotation
- L2290 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2295 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2299 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2303 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2307 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2311 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2315 _public member_ `float DrawRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the sphere to draw

#### struct `FRigUnit_DrawDebugDirection`  
`struct FRigUnit_DrawDebugDirection : public FRigUnit_DrawDebugLibraryBase`  
_L2320-2354_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Direction"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw an arrow at the given location facing in the given direction
- L2324 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2329 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2333 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2337 _public member_ `FVector Direction = FVector::ForwardVector;` — `UPROPERTY(meta = (Input))` — Direction to Draw
- L2341 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2345 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2349 _public member_ `float DrawArrowLength = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow to draw
- L2353 _public member_ `float ArrowHeadScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Scale of the arrow head to draw

#### struct `FRigUnit_DrawDebugVelocity`  
`struct FRigUnit_DrawDebugVelocity : public FRigUnit_DrawDebugLibraryBase`  
_L2358-2388_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Velocity"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a line at the given location scaled by the given velocity
- L2362 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2367 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2371 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2375 _public member_ `FVector Velocity = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Velocity to draw
- L2379 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2383 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2387 _public member_ `float DrawVelocityLineScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Scale of the line to draw

#### struct `FRigUnit_DrawDebugVelocities`  
`struct FRigUnit_DrawDebugVelocities : public FRigUnit_DrawDebugLibraryBase`  
_L2392-2422_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Velocities"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw lines at the given locations scaled by the given velocities
- L2396 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2401 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2405 _public member_ `TArray<FVector> Locations;` — `UPROPERTY(meta = (Input))` — Draw Locations
- L2409 _public member_ `TArray<FVector> Velocities;` — `UPROPERTY(meta = (Input))` — Velocities to draw
- L2413 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2417 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2421 _public member_ `float DrawVelocityLineScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Scale of the line to draw

#### struct `FRigUnit_DrawDebugTransform`  
`struct FRigUnit_DrawDebugTransform : public FRigUnit_DrawDebugLibraryBase`  
_L2427-2453_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Transform"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a set of axes at the given transform
- L2431 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2436 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2440 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(meta = (Input))` — Transform to draw
- L2444 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2448 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2452 _public member_ `float DrawRadius = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the transform axis

#### struct `FRigUnit_DrawDebugEvent`  
`struct FRigUnit_DrawDebugEvent : public FRigUnit_DrawDebugLibraryBase`  
_L2457-2491_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Event"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a phase-representation of an event at a location
- L2461 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2466 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2470 _public member_ `bool bTimeUntilEventKnown = false;` — `UPROPERTY(meta = (Input))` — If the time until the event is known
- L2474 _public member_ `float TimeUntilEvent = 0.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "s"))` — The time until the event
- L2478 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2482 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2486 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2490 _public member_ `float Size = 20.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Size of the event representation to draw

#### struct `FRigUnit_DrawDebugChair`  
`struct FRigUnit_DrawDebugChair : public FRigUnit_DrawDebugLibraryBase`  
_L2495-2525_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Chair"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a basic chair shape
- L2499 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2504 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2508 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2512 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2516 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2520 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2524 _public member_ `FDrawDebugChairSettings Settings;` — `UPROPERTY(meta = (Input))` — Chair settings

#### struct `FRigUnit_DrawDebugDoor`  
`struct FRigUnit_DrawDebugDoor : public FRigUnit_DrawDebugLibraryBase`  
_L2529-2559_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Door"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a basic door shape
- L2533 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2538 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2542 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2546 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2550 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2554 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2558 _public member_ `FDrawDebugDoorSettings Settings;` — `UPROPERTY(meta = (Input))` — Door settings

#### struct `FRigUnit_DrawDebugCamera`  
`struct FRigUnit_DrawDebugCamera : public FRigUnit_DrawDebugLibraryBase`  
_L2563-2597_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Camera"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a camera shape
- L2567 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2572 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2576 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2580 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2584 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2588 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2592 _public member_ `float Scale = 10.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Camera Scale
- L2596 _public member_ `float FOVDegrees = 30.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "deg"))` — Camera FOV

#### struct `FRigUnit_DrawDebugBackpack`  
`struct FRigUnit_DrawDebugBackpack : public FRigUnit_DrawDebugLibraryBase`  
_L2601-2631_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Backpack"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a backpack
- L2605 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2610 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2614 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2618 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2622 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2626 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2630 _public member_ `FDrawDebugBackpackSettings Settings;` — `UPROPERTY(meta = (Input))` — Backpack settings

#### struct `FRigUnit_DrawDebugBriefcase`  
`struct FRigUnit_DrawDebugBriefcase : public FRigUnit_DrawDebugLibraryBase`  
_L2636-2666_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Briefcase"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draw a briefcase
- L2640 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2645 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2649 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2653 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2657 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2661 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2665 _public member_ `FDrawDebugBriefcaseSettings Settings;` — `UPROPERTY(meta = (Input))` — Briefcase settings

#### struct `FRigUnit_DrawDebugTrajectory`  
`struct FRigUnit_DrawDebugTrajectory : public FRigUnit_DrawDebugLibraryBase`  
_L2670-2720_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Trajectory"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a trajectory of locations and directions
- L2674 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2679 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2683 _public member_ `TArray<FVector> Locations;` — `UPROPERTY(meta = (Input))` — Trajectory Locations
- L2687 _public member_ `TArray<FVector> Directions;` — `UPROPERTY(meta = (Input))` — Trajectory Directions
- L2691 _public member_ `FTransform RelativeTransform = FTransform::Identity;` — `UPROPERTY(meta = (Input))` — Relative Transform to apply to the locations and directions
- L2695 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2699 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2703 _public member_ `float DrawArrowLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Length of the arrow to draw for directions
- L2707 _public member_ `float PointRadius = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Radius of the location spheres to draw
- L2711 _public member_ `float ArrowHeadScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Scale of the arrow head to draw
- L2715 _public member_ `int32 Segments = 9;` — `UPROPERTY(meta = (Input))` — Number of segments in the location spheres
- L2719 _public member_ `float VerticalOffset = 2.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Vertical offset to apply to the trajectory to avoid it clipping with the ground

#### struct `FRigUnit_DrawDebugTransformTrajectory`  
`struct FRigUnit_DrawDebugTransformTrajectory : public FRigUnit_DrawDebugLibraryBase`  
_L2724-2754_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Transform Trajectory"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draws a transform trajectory
- L2728 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2733 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2737 _public member_ `FTransformTrajectory TransformTrajectory;` — `UPROPERTY(meta = (Input))` — Transform Trajectory
- L2741 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2745 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2749 _public member_ `float Radius = 5.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Sample sphere radius
- L2753 _public member_ `float VerticalOffset = 2.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Vertical offset to apply to prevent clipping with ground plane

#### struct `FRigUnit_DrawDebugMoverOrientation`  
`struct FRigUnit_DrawDebugMoverOrientation : public FRigUnit_DrawDebugLibraryBase`  
_L2758-2792_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Mover Orientation"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Draws a flat 2d motif representing mover position and rotation
- L2762 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2767 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2771 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2775 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2779 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2783 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2787 _public member_ `FVector ForwardVector = FVector::ForwardVector;` — `UPROPERTY(meta = (Input))` — Forward Direction Vector Location
- L2791 _public member_ `float Scale = 30.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Motif Scale

#### struct `FRigVMFunction_DrawDebugGetDefaultBoneColor`  
`struct FRigVMFunction_DrawDebugGetDefaultBoneColor : public FRigVMFunction_DrawDebugLibraryBase`  
_L2796-2806_
- reflection: `USTRUCT(meta = (DisplayName = "Get Default Bone Color"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Gets the default bone color
- L2800 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2805 _public member_ `FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f);` — `UPROPERTY(meta = (Output))` — Default Bone Color

#### struct `FRigVMFunction_DrawDebugGetDefaultBoneRadius`  
`struct FRigVMFunction_DrawDebugGetDefaultBoneRadius : public FRigVMFunction_DrawDebugLibraryBase`  
_L2810-2820_
- reflection: `USTRUCT(meta = (DisplayName = "Get Default Bone Radius"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Gets the default bone radius
- L2814 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2819 _public member_ `float Radius = 1.0f;` — `UPROPERTY(meta = (Output))` — Default Bone Radius

#### struct `FRigUnit_DrawDebugBone`  
`struct FRigUnit_DrawDebugBone : public FRigUnit_DrawDebugLibraryBase`  
_L2824-2862_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Bone"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a bone
- L2828 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2833 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2837 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L2841 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L2845 _public member_ `FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f);` — `UPROPERTY(meta = (Input))` — Draw Color
- L2849 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2853 _public member_ `float Radius = 5.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Bone Radius
- L2857 _public member_ `int32 Segments = 10;` — `UPROPERTY(meta = (Input))` — Number of segments
- L2861 _public member_ `bool bDrawTransform = false;` — `UPROPERTY(meta = (Input))` — If to draw the bone transform

#### struct `FRigUnit_DrawDebugBoneLink`  
`struct FRigUnit_DrawDebugBoneLink : public FRigUnit_DrawDebugLibraryBase`  
_L2866-2900_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Bone Link"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a link between a child and parent bone
- L2870 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2875 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2879 _public member_ `FVector ChildLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Child Location
- L2883 _public member_ `FVector ParentLocation = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Parent Location
- L2887 _public member_ `FRotator ParentRotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Parent Rotation
- L2891 _public member_ `FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f);` — `UPROPERTY(meta = (Input))` — Draw Color
- L2895 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2899 _public member_ `float Radius = 5.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Bone Radius

#### struct `FRigUnit_DrawDebugSkeletonFromSkinnedMeshComponent`  
`struct FRigUnit_DrawDebugSkeletonFromSkinnedMeshComponent : public FRigUnit_DrawDebugLibraryBase`  
_L2904-2930_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Skeleton from Skinned Mesh Component"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Draws a skeleton from a skinned mesh component
- L2908 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2913 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2917 _public member_ `TObjectPtr<USkinnedMeshComponent> SkinnedMeshComponent = nullptr;` — `UPROPERTY(meta = (Input))` — Skinned Mesh
- L2921 _public member_ `FLinearColor Color = FLinearColor(0.0f, 0.0f, 0.025f, 1.0f);` — `UPROPERTY(meta = (Input))` — Draw Color
- L2925 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2929 _public member_ `FDrawDebugSkeletonSettings Settings;` — `UPROPERTY(meta = (Input))` — Bone Settings

#### struct `FRigUnit_DrawDebugPose`  
`struct FRigUnit_DrawDebugPose : public FRigUnit_DrawDebugLibraryBase`  
_L2934-2968_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Pose"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a pose made up of bone locations and velocities
- L2938 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2943 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L2947 _public member_ `TArray<FVector> BoneLocations;` — `UPROPERTY(meta = (Input))` — Draw Locations
- L2951 _public member_ `TArray<FVector> BoneLinearVelocities;` — `UPROPERTY(meta = (Input))` — Draw Linear Velocities
- L2955 _public member_ `FTransform RelativeTransform = FTransform::Identity;` — `UPROPERTY(meta = (Input))` — Relative Transform to apply to the locations and velocities
- L2959 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L2963 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L2967 _public member_ `float DrawVelocityLineScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Scale for drawing velocities

#### struct `FRigVMFunction_DrawDebugStringSegmentNum`  
`struct FRigVMFunction_DrawDebugStringSegmentNum : public FRigVMFunction_DrawDebugLibraryBase`  
_L2973-2991_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug String Segment Num"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the number of line segments required to draw debug a string.
- L2977 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L2982 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to draw
- L2986 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L2990 _public member_ `int32 SegmentNum = 0;` — `UPROPERTY(meta = (Output))` — Output Segment Num

#### struct `FRigVMFunction_DrawDebugNameSegmentNum`  
`struct FRigVMFunction_DrawDebugNameSegmentNum : public FRigVMFunction_DrawDebugLibraryBase`  
_L2995-3013_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Name Segment Num"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the number of line segments required to draw debug a name.
- L2999 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3004 _public member_ `FName Name = TEXT("");` — `UPROPERTY(meta = (Input))` — Name to draw
- L3008 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L3012 _public member_ `int32 SegmentNum = 0;` — `UPROPERTY(meta = (Output))` — Output Segment Num

#### struct `FRigVMFunction_DrawDebugStringDimensions`  
`struct FRigVMFunction_DrawDebugStringDimensions : public FRigVMFunction_DrawDebugLibraryBase`  
_L3017-3035_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug String Dimensions"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the dimensions of a draw debug string. Useful for aligning or centering text.
- L3021 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3026 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to draw
- L3030 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L3034 _public member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Dimensions

#### struct `FRigVMFunction_DrawDebugNameDimensions`  
`struct FRigVMFunction_DrawDebugNameDimensions : public FRigVMFunction_DrawDebugLibraryBase`  
_L3039-3057_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Name Dimensions"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the dimensions of a draw debug name. Useful for aligning or centering text.
- L3043 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3048 _public member_ `FName Name = TEXT("");` — `UPROPERTY(meta = (Input))` — Name to draw
- L3052 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L3056 _public member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Dimensions

#### struct `FRigVMFunction_DrawDebugStringCenteringOffset`  
`struct FRigVMFunction_DrawDebugStringCenteringOffset : public FRigVMFunction_DrawDebugLibraryBase`  
_L3061-3079_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug String Centering Offset"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the local offset required to center a draw debug string.
- L3065 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3070 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to draw
- L3074 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L3078 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Offset

#### struct `FRigVMFunction_DrawDebugNameCenteringOffset`  
`struct FRigVMFunction_DrawDebugNameCenteringOffset : public FRigVMFunction_DrawDebugLibraryBase`  
_L3083-3101_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Name Centering Offset"))`
- inherits: `FRigVMFunction_DrawDebugLibraryBase`
- desc: Get the local offset required to center a draw debug name.
- L3087 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3092 _public member_ `FName Name = TEXT("");` — `UPROPERTY(meta = (Input))` — Name to draw
- L3096 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings
- L3100 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(meta = (Output))` — Output Offset

#### struct `FRigUnit_DrawDebugString`  
`struct FRigUnit_DrawDebugString : public FRigUnit_DrawDebugLibraryBase`  
_L3105-3139_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug String"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draws a string
- L3109 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3114 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3118 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to draw
- L3122 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3126 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3130 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L3134 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3138 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings

#### struct `FRigUnit_DrawDebugName`  
`struct FRigUnit_DrawDebugName : public FRigUnit_DrawDebugLibraryBase`  
_L3143-3177_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Name"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draws a name
- L3147 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3152 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3156 _public member_ `FName Name = NAME_None;` — `UPROPERTY(meta = (Input))` — Name to draw
- L3160 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3164 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3168 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L3172 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3176 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings

#### struct `FRigUnit_DrawDebugNames`  
`struct FRigUnit_DrawDebugNames : public FRigUnit_DrawDebugLibraryBase`  
_L3181-3219_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Names"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug draws several names
- L3185 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3190 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3194 _public member_ `TArray<FName> Names;` — `UPROPERTY(meta = (Input))` — Names to draw
- L3198 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3202 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3206 _public member_ `FString Separator = TEXT(", "` — `UPROPERTY(meta = (Input))` — Separator to put between names
- L3210 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Line Style
- L3214 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3218 _public member_ `FDrawDebugStringSettings Settings;` — `UPROPERTY(meta = (Input))` — String Settings

#### struct `FRigUnit_DrawDebugVisualLoggerDrawString`  
`struct FRigUnit_DrawDebugVisualLoggerDrawString : public FRigUnit_DrawDebugLibraryBase`  
_L3223-3245_
- reflection: `USTRUCT(meta = (DisplayName = "Visual Logger Draw String"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a string to the visual logger. Will do nothing if not using a VisualLoggerDrawer. Will not display on-screen during recording.
- L3227 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3232 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3236 _public member_ `FString String = TEXT("");` — `UPROPERTY(meta = (Input))` — String to draw
- L3240 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3244 _public member_ `FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(meta = (Input))` — Draw Color

#### struct `FRigUnit_DrawDebugVisualLoggerDrawName`  
`struct FRigUnit_DrawDebugVisualLoggerDrawName : public FRigUnit_DrawDebugLibraryBase`  
_L3249-3271_
- reflection: `USTRUCT(meta = (DisplayName = "Visual Logger Draw Name"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a name to the visual logger. Will do nothing if not using a VisualLoggerDrawer. Will not display on-screen during recording.
- L3253 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3258 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3262 _public member_ `FName Name = NAME_None;` — `UPROPERTY(meta = (Input))` — Name to draw
- L3266 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3270 _public member_ `FLinearColor Color = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(meta = (Input))` — Draw Color

#### struct `FRigUnit_DrawDebugGraph`  
`struct FRigUnit_DrawDebugGraph : public FRigUnit_DrawDebugLibraryBase`  
_L3275-3345_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Graph"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a simple graph.
- L3279 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3284 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3288 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3292 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3296 _public member_ `TArray<float> Xvalues;` — `UPROPERTY(meta = (Input))` — X Values
- L3300 _public member_ `TArray<float> Yvalues;` — `UPROPERTY(meta = (Input))` — Y Values
- L3304 _public member_ `float Xmin = 0.0f;` — `UPROPERTY(meta = (Input))` — X min
- L3308 _public member_ `float Xmax = 1.0f;` — `UPROPERTY(meta = (Input))` — X max
- L3312 _public member_ `float Ymin = 0.0f;` — `UPROPERTY(meta = (Input))` — Y min
- L3316 _public member_ `float Ymax = 1.0f;` — `UPROPERTY(meta = (Input))` — Y max
- L3320 _public member_ `float XaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — X axis length
- L3324 _public member_ `float YaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Y axis length
- L3328 _public member_ `FDrawDebugLineStyle TextLineStyle;` — `UPROPERTY(meta = (Input))` — Text line style
- L3332 _public member_ `FDrawDebugLineStyle AxesLineStyle;` — `UPROPERTY(meta = (Input))` — Axes line style
- L3336 _public member_ `FDrawDebugLineStyle PlotLineStyle;` — `UPROPERTY(meta = (Input))` — Plot line style
- L3340 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3344 _public member_ `FDrawDebugGraphAxesSettings AxesSettings;` — `UPROPERTY(meta = (Input))` — Axes Settings

#### struct `FRigUnit_DrawDebugGraphAxesLabels`  
`struct FRigUnit_DrawDebugGraphAxesLabels : public FRigUnit_DrawDebugLibraryBase`  
_L3349-3387_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Graph Axes Labels"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a simple graph axes labels.
- L3353 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3358 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3362 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3366 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3370 _public member_ `float XaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — X axis length
- L3374 _public member_ `float YaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Y axis length
- L3378 _public member_ `FDrawDebugLineStyle TextLineStyle;` — `UPROPERTY(meta = (Input))` — Text line style
- L3382 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3386 _public member_ `FDrawDebugGraphAxesSettings AxesSettings;` — `UPROPERTY(meta = (Input))` — Axes Settings

#### struct `FRigUnit_DrawDebugGraphAxes`  
`struct FRigUnit_DrawDebugGraphAxes : public FRigUnit_DrawDebugLibraryBase`  
_L3391-3433_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Graph Axes"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a simple graph axes.
- L3395 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3400 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3404 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3408 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3412 _public member_ `float XaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — X axis length
- L3416 _public member_ `float YaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Y axis length
- L3420 _public member_ `FDrawDebugLineStyle TextLineStyle;` — `UPROPERTY(meta = (Input))` — Text line style
- L3424 _public member_ `FDrawDebugLineStyle AxesLineStyle;` — `UPROPERTY(meta = (Input))` — Axes line style
- L3428 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3432 _public member_ `FDrawDebugGraphAxesSettings AxesSettings;` — `UPROPERTY(meta = (Input))` — Axes Settings

#### struct `FRigUnit_DrawDebugGraphLine`  
`struct FRigUnit_DrawDebugGraphLine : public FRigUnit_DrawDebugLibraryBase`  
_L3437-3495_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Graph Line"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a line on a simple graph.
- L3441 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3446 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3450 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3454 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3458 _public member_ `TArray<float> Xvalues;` — `UPROPERTY(meta = (Input))` — X Values
- L3462 _public member_ `TArray<float> Yvalues;` — `UPROPERTY(meta = (Input))` — Y Values
- L3466 _public member_ `float Xmin = 0.0f;` — `UPROPERTY(meta = (Input))` — X min
- L3470 _public member_ `float Xmax = 1.0f;` — `UPROPERTY(meta = (Input))` — X max
- L3474 _public member_ `float Ymin = 0.0f;` — `UPROPERTY(meta = (Input))` — Y min
- L3478 _public member_ `float Ymax = 1.0f;` — `UPROPERTY(meta = (Input))` — Y max
- L3482 _public member_ `float XaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — X axis length
- L3486 _public member_ `float YaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Y axis length
- L3490 _public member_ `FDrawDebugLineStyle LineStyle;` — `UPROPERTY(meta = (Input))` — Plot line style
- L3494 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing

#### struct `FRigUnit_DrawDebugGraphLegend`  
`struct FRigUnit_DrawDebugGraphLegend : public FRigUnit_DrawDebugLibraryBase`  
_L3500-3554_
- reflection: `USTRUCT(meta = (DisplayName = "Draw Debug Graph Legend"))`
- inherits: `FRigUnit_DrawDebugLibraryBase`
- desc: Debug Draw a simple graph legend.
- L3504 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L3509 _public member_ `FDebugDrawer Drawer;` — `UPROPERTY(meta = (Input))` — Debug Drawer
- L3513 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — Draw Location
- L3517 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(meta = (Input))` — Draw Rotation
- L3521 _public member_ `TArray<FLinearColor> LegendColors;` — `UPROPERTY(meta = (Input))` — Legend Colors
- L3525 _public member_ `TArray<FString> LegendLabels;` — `UPROPERTY(meta = (Input))` — Legend Labels
- L3529 _public member_ `float XaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — X axis length
- L3533 _public member_ `float YaxisLength = 100.0f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Y axis length
- L3537 _public member_ `FDrawDebugLineStyle TextLineStyle;` — `UPROPERTY(meta = (Input))` — Text line style
- L3541 _public member_ `FDrawDebugLineStyle IconLineStyle;` — `UPROPERTY(meta = (Input))` — Icon line style
- L3545 _public member_ `float IconSize = 2.5f;` — `UPROPERTY(meta = (Input, ForceUnits = "cm"))` — Icon Size
- L3549 _public member_ `bool bDepthTest = true;` — `UPROPERTY(meta = (Input))` — If to use depth testing while drawing
- L3553 _public member_ `FDrawDebugStringSettings LegendSettings;` — `UPROPERTY(meta = (Input))` — Legend string settings

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DRAWDEBUGLIBRARY_API`
