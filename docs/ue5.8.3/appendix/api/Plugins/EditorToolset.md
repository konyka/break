# Plugins / EditorToolset

- module root: `Plugins/Experimental/Toolsets/EditorToolset/Source/EditorToolset`
- headers: 3; symbols: 87
- symbol kinds: class=2, function=1, member=31, namespace=3, prototype=43, struct=7
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowser, ContentBrowserData, CoreUObject, EditorFramework, EditorScriptingUtilities, EditorSubsystem, Engine, Json, JsonUtilities, Kismet, LevelEditor, RHI, RenderCore, Slate, SlateCore, StatusBar, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/EditorToolset/Source/EditorToolset/Private/BitmapAnnotation.h` (Private)


#### struct `UE::ToolsetRegistry::BitmapAnnotation::FBitmapCanvas`  
`struct FBitmapCanvas`  
_L24-59_
- desc: Lightweight view over an in-memory RGBA bitmap. Bundles the pixel buffer with its dimensions so drawing primitives can be called as member functions without the caller re-passing both every time. Holds a reference to the caller's pixel array — it does not own the memory and must not outlive the underlying TArray.
- L26 _public member_ `TArray<FColor>& Pixels;`
- L27 _public member_ `FIntPoint Size;`
- L29 _public function_ `FBitmapCanvas(TArray<FColor>& InPixels, FIntPoint InSize) : Pixels(InPixels) , Size(InSize)`
- L38 _public prototype_ `void SetPixel(int32 X, int32 Y, const FColor& Color);` — Write a single pixel, clipped to the bitmap bounds.
- L41 _public prototype_ `void BlendPixel(int32 X, int32 Y, const FColor& Color, float Alpha = 1.0f);` — Alpha-blend a single pixel over the existing contents.
- L46 _public prototype_ `void DrawLine(int32 X0, int32 Y0, int32 X1, int32 Y1, const FColor& Color, float Alpha = 0.6f);` — Bresenham line with alpha blending and a runaway-iteration cap.
- L49 _public prototype_ `void DrawLineThick(int32 X0, int32 Y0, int32 X1, int32 Y1, const FColor& Color, int32 Thickness = 2, float Alpha = 0.6f);` — Thick line drawn as parallel offset single-pixel lines.
- L52 _public prototype_ `void DrawDot(int32 CX, int32 CY, int32 Radius, const FColor& Color);` — Filled disc (grid intersection marker).
- L55 _public prototype_ `void DrawChar(int32 X, int32 Y, TCHAR Ch, const FColor& Color, int32 Scale = 2);` — Draw a single character at (X, Y) with nearest-neighbour scaling.
- L58 _public prototype_ `void DrawString(int32 X, int32 Y, const FString& Text, const FColor& Color, int32 Scale = 2, bool bDrawBackground = true);` — Draw a string at (X, Y). When bDrawBackground is true, a semi-transparent black plate is drawn behind the text for readability.

#### struct `UE::ToolsetRegistry::BitmapAnnotation::FActorLabelCandidate`  
`struct FActorLabelCandidate`  
_L84-95_
- desc: One labeled point in an actor-label overlay pass. Caller does the actor iteration / projection / culling and fills these in; DrawActorLabels handles the on-screen layout (overlap avoidance, leader lines, text plates).
- L87 _public member_ `FString DisplayLabel;` — Text to draw on the image (typically actor display label + world position).
- L90 _public member_ `int32 ScreenX = 0;` — Pre-projected screen-space position of the actor origin.
- L91 _public member_ `int32 ScreenY = 0;`
- L94 _public member_ `int32 TextScale = 1;` — Pixel scale for the glyph rendering — typically 2 for near, 1 for far.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ToolsetRegistry` (scope `UE`)
- L14 _namespace_ `namespace BitmapAnnotation` (scope `UE::ToolsetRegistry`)
- L66 _prototype_ `int32 GetGlyphWidth();` (scope `UE::ToolsetRegistry::BitmapAnnotation`)
- L67 _prototype_ `int32 GetGlyphHeight();` (scope `UE::ToolsetRegistry::BitmapAnnotation`)
- L70 _prototype_ `int32 GetGlyphAdvance(int32 Scale);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Width in pixels of one character cell (glyph width + 1px inter-char spacing), at the given integer scale.
- L73 _prototype_ `int32 MeasureString(const FString& Text, int32 Scale = 2);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Measured pixel width of a string at the given integer scale.
- L113 _prototype_ `void DrawWorldGrid( FBitmapCanvas& Canvas, const FMatrix& ViewProjectionMatrix, const FVector& CamLoc, const FVector& CamFwd, double GridSpacing, double GridExtent, double GridHeight, double MaxLabelDistance);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Draw a multi-LOD projected world-space grid plus origin marker, axis legend, and per-intersection coordinate labels (in meters) onto Canvas. The grid is drawn in concentric LODs around the camera position so that the close-up density is high without flooding the image with distant intersections. @param Canvas              Target framebuffer. @param ViewProjectionMatrix World-to-clip matrix matching the captured viewport. @param CamLoc              Camera world-space location. @param CamFwd              Camera forward direction (unit vector). @param GridSpacing         World-space distance between grid lines (cm). Caller checks > 0 before invoking. @param GridExtent          How far the grid extends from the origin in each axis (cm). @param GridHeight          Height of the ground-plane grid in world space (Z, or "up" in LUF terms). @param MaxLabelDistance    Maximum distance (cm) for coordinate labels at intersections.
- L134 _prototype_ `void DrawActorLabels(FBitmapCanvas& Canvas, TArrayView<const FActorLabelCandidate> Candidates);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Draw per-actor crosshair, label plate, and leader-line callouts onto Canvas. Performs a simple greedy overlap-avoidance layout — labels are bumped vertically in fixed steps to avoid colliding with already-placed labels. When a label can't sit at its default position above the crosshair, a faint leader line connects the label back to the crosshair. Candidates should already be in the order the caller wants them placed (typically nearest-to-camera first).
- L142 _prototype_ `bool ProjectWorldToScreen(const FVector& WorldPos, const FMatrix& ViewProjectionMatrix, FIntPoint Size, int32& OutX, int32& OutY);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Project a world-space point to screen pixel coordinates. Returns false if the point is behind the camera.
- L152 _prototype_ `bool ProjectLineClipped(const FVector& A, const FVector& B, const FMatrix& ViewProjectionMatrix, FIntPoint Size, int32& OutX0, int32& OutY0, int32& OutX1, int32& OutY1, const FVector& CamPos, const FVector& CamFwd);` (scope `UE::ToolsetRegistry::BitmapAnnotation`) — Project a line segment from A to B to screen space, clipping in world space against a near plane just in front of the camera. World-space clipping (as opposed to clip-space W clipping) preserves line straightness after projection. Returns false if the segment is entirely behind the camera. Output coordinates are clamped to a safe range to prevent Bresenham overflow.

### `Plugins/Experimental/Toolsets/EditorToolset/Source/EditorToolset/Private/EditorAppToolset.h` (Private)


#### struct `FPIESessionOptions`  
`struct FPIESessionOptions`  
_L27-67_
- reflection: `USTRUCT()`
- desc: Options bag for StartPIE. All fields are optional; defaults run a standard Play-In-Editor session inside the active level viewport, with a 2-second warmup after PostPIEStarted to let project initialization settle.
- L39 _public member_ `bool bSimulate = false;` — `UPROPERTY()` — If true, starts Simulate-In-Editor: the world ticks and AI / physics / subsystems run, but no player pawn is spawned or possessed. Useful for observing initialization, autonomous agents, and physics state independently of player input. If false (default), starts standard PIE with the player pawn possessed.
- L48 _public member_ `TEnumAsByte<EPlayModeType> PlayMode = PlayMode_InViewPort;` — `UPROPERTY()` — Editor play mode (in-viewport, floating window, etc.). Out-of-process modes (NewProcess, MobilePreview, VR, QuickLaunch) are downgraded to PlayMode_InViewPort with a log warning since this tool requires in-process PIE for delegate-based completion tracking.
- L57 _public member_ `TOptional<FTransform> StartTransform;` — `UPROPERTY()` — Optional spawn override. When set, the player pawn (PIE) or simulation reference (Simulate) spawns at this transform instead of the level's PlayerStart / GameMode default. To spawn at the editor viewport camera, retrieve the current editor camera properties and use the result here.
- L66 _public member_ `float WarmupSeconds = 2.f;` — `UPROPERTY()` — Seconds to wait after the engine fires PostPIEStarted (BeginPlay called) before this call completes. Heuristic for project-specific initialization (services, authentication, plugin warmup) to settle before the agent inspects state or logs. Pass 0 to complete as soon as PIE is up.

#### struct `FViewportLabel`  
`struct FViewportLabel`  
_L77-104_
- reflection: `USTRUCT(BlueprintType)`
- desc: One labeled actor in a viewport capture's annotation overlay. Name is the canonical object name (unique within the level and stable across captures); Label is the human-readable text drawn on the image (actor label + position). Use Name when referring back to a specific actor, Label for display.
- L83 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Canonical, level-unique name of the actor (AActor::GetName). Use this to reference the actor later.
- L87 _public member_ `FString Label;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Display label that was drawn on the image (actor label + position in meters). Not guaranteed unique.
- L91 _public member_ `TSubclassOf<AActor> Class;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Class of the actor.
- L95 _public member_ `FIntPoint ScreenPosition = FIntPoint(0, 0);` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Screen-space pixel position of the actor origin in the returned image.
- L99 _public member_ `FVector WorldLocation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — World-space location of the actor origin (cm).
- L103 _public member_ `float DistanceCm = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Distance from the camera to the actor origin (cm).

#### struct `FViewportGrid`  
`struct FViewportGrid`  
_L108-123_
- reflection: `USTRUCT(BlueprintType)`
- desc: Grid parameters echoed back from an annotated viewport capture for round-tripping / reporting.
- L114 _public member_ `float SpacingCm = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — World-space distance between grid lines (cm). Zero if the grid was disabled.
- L118 _public member_ `float ExtentCm = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — How far the grid extends from the origin in each axis (cm).
- L122 _public member_ `float Height = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Height of the ground-plane grid in world space.

#### struct `FViewportAnnotationConfig`  
`struct FViewportAnnotationConfig`  
_L129-156_
- reflection: `USTRUCT()`
- desc: Annotation overlay configuration for CaptureViewport.
- L135 _public member_ `float GridSpacing = 500.f;` — `UPROPERTY()` — World-space distance between grid lines (cm). Pass 0 to disable the grid overlay while still drawing actor labels.
- L139 _public member_ `float GridExtent = 5000.f;` — `UPROPERTY()` — How far the grid extends from the origin in each axis (cm).
- L143 _public member_ `float GridHeight = 0.f;` — `UPROPERTY()` — Height of the ground-plane grid in world space.
- L147 _public member_ `float MaxLabelDistance = 5000.f;` — `UPROPERTY()` — Maximum distance (cm) for labeling actors and grid coordinates. Pass 0 to disable actor labels while still drawing the grid.
- L151 _public member_ `TSubclassOf<AActor> ClassFilter = nullptr;` — `UPROPERTY()` — If non-null, only actors of this class (or a subclass) are labeled.
- L155 _public member_ `int32 MaxLabels = 12;` — `UPROPERTY()` — Maximum number of actor labels to draw. Nearest-to-camera wins. Don't draw too many or the image becomes incoherent.

#### struct `FViewportCapture`  
`struct FViewportCapture`  
_L164-191_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes the results of a viewport capture. Includes a screenshot of the level viewport plus structured metadata describing the camera. When annotations are enabled, the associated metadata will be populated and the image will include a projected world-space grid and per-actor labels.
- L170 _public member_ `FToolsetImage Image;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — The captured screenshot (PNG encoded as base64). Empty on failure. Pixel dimensions are available via FToolsetImage.
- L174 _public member_ `FVector CameraLocation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Level viewport camera location (world space, cm).
- L178 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Level viewport camera rotation (world space).
- L182 _public member_ `float CameraFOV = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Level viewport camera field of view, in degrees.
- L186 _public member_ `FViewportGrid Grid;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — Grid parameters used for the annotation. SpacingCm is zero when the grid was disabled.
- L190 _public member_ `TArray<FViewportLabel> LabeledActors;` — `UPROPERTY(BlueprintReadOnly, Category = "EditorAppToolset")` — One entry per labeled actor in the image.

#### class `UEditorAppToolset`  
`class UEditorAppToolset : public UToolsetDefinition`  
_L197-385_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Tools for querying and modifying Unreal Editor state: console variables, asset imaging, actor and asset selection, viewport camera, content browser navigation, and Play-In-Editor session control.
- L207 _public prototype_ `static FString SearchCVars(const FString& Name);` — `UFUNCTION(meta = (AICallable))` — Finds all console variables that contain a given name. @param Name The partial or full name to search for. @return A JSON dict with info about matching cvars.
- L216 _public prototype_ `static UToolCallAsyncResultImage* CaptureAssetImage(const FString& AssetPath);` — `UFUNCTION(meta = (AICallable))` — Renders a thumbnail for the specified asset (e.g. static meshes, skeletal meshes, skeletons, animations, montages, materials, textures). @param AssetPath The path to the asset, e.g. '/Game/Meshes/SM_Cube'. @return An image of the asset.
- L223 _public prototype_ `static FToolsetImage CaptureEditorImage();` — `UFUNCTION(meta = (AICallable))` — Captures an image of the entire editor application as the user sees it. @return An image of editor windows as they appear on the users' desktop.
- L246 _public prototype_ `static FViewportCapture CaptureViewport( TOptional<FTransform> CaptureTransform, TOptional<FViewportAnnotationConfig> Annotations, bool bShowUI = false);` — `UFUNCTION(meta = (AICallable), Category = "EditorAppToolset")` — Captures the level viewport with optional annotations. Annotations rendering overlays a projected 3D world-space grid plus name + position labels on visible actors. The grid is drawn at a configurable ground-plane Z and projected through the camera, with coordinate numbers at intersections (shown in meters). Each labeled actor gets a crosshair at its projected screen position with a leader-line callout placed to avoid overlap. This gives a vision-capable agent spatial awareness: it can reference grid coordinates to direct placement and identify scene contents by label. @param CaptureTransform Optional pose to capture from. If unset, uses the viewport's current camera. @param Annotations Optional annotation overlay configuration. Only use this when you need the information in order to perform spatial actions. @param bShowUI If false (default), editor UI overlays such as transform gizmos and selection outlines are hidden in the captured image. Set true to capture exactly what's on screen, gizmos and all. @return The captured image and associated metadata.
- L256 _public prototype_ `static TArray<AActor*> GetSelectedActors();` — `UFUNCTION(meta = (AICallable))` — Gets the currently selected actors in the level editor. @return A list of the currently selected actors.
- L263 _public prototype_ `static void SelectActors(const TArray<AActor*>& Actors);` — `UFUNCTION(meta = (AICallable))` — Selects the specified actors in the current scene. @param Actors The actors to select.
- L270 _public prototype_ `static FTransform GetCameraTransform();` — `UFUNCTION(meta = (AICallable))` — Returns the position and rotation of the level viewport camera. @return The transform for the level viewport camera.
- L277 _public prototype_ `static void SetCameraTransform(const FTransform& Transform);` — `UFUNCTION(meta = (AICallable))` — Sets the position and rotation of the level viewport camera. @param Transform The transform to apply to the viewport camera.
- L285 _public prototype_ `static void FocusOnActors(const TArray<AActor*>& Actors);` — `UFUNCTION(meta = (AICallable))` — Repositions the level editor camera to focus on the specified actors. Cannot be called while PIE is active. @param Actors The actors to focus the level camera on.
- L292 _public prototype_ `static TArray<AActor*> GetVisibleActors();` — `UFUNCTION(meta = (AICallable))` — Returns all actors in the current level whose bounds intersect the viewport frustum. @return The actors that are at least partially in view.
- L300 _public prototype_ `static FVector2D WorldPosToScreenCoords(FVector Position);` — `UFUNCTION(meta = (AICallable))` — Converts a world-space position into normalized screen space based on the editor viewport camera. @param Position The world space position to convert. @return The normalized screen-space coordinates for the position if it is in view.
- L309 _public prototype_ `static FVector ScreenCoordsToWorld(FVector2D Coords, float TraceDistance = 100000.f);` — `UFUNCTION(meta = (AICallable))` — Finds the world position of the nearest solid object at a given set of normalized view space coords. @param Coords The normalized screen-space coordinates to trace from. @param TraceDistance The maximum distance to trace within the scene. @return The world-space coordinates of the intersection point.
- L316 _public prototype_ `static TArray<FString> GetSelectedAssets();` — `UFUNCTION(meta = (AICallable))` — Gets the list of assets selected in the content browser. @return A list of package paths to the assets selected in the content browser.
- L324 _public prototype_ `static UToolCallAsyncResultVoid* SelectAssets(const TArray<FString>& AssetPaths);` — `UFUNCTION(meta = (AICallable))` — Selects the specified assets in the content browser. Completes once the content browser has applied the selection. @param AssetPaths The package paths of the assets to select.
- L331 _public prototype_ `static FString GetContentBrowserPath();` — `UFUNCTION(meta = (AICallable))` — Gets the current path of the active content browser. @return The path to the folder currently shown in the content browser.
- L338 _public prototype_ `static void SetContentBrowserPath(const FString& Path);` — `UFUNCTION(meta = (AICallable))` — Navigates the active content browser to the specified folder path. @param Path The internal path to navigate to, e.g. '/Game/Meshes'.
- L345 _public prototype_ `static void OpenEditorForAsset(const FString& AssetPath);` — `UFUNCTION(meta = (AICallable))` — Opens an asset editor for the specified asset. @param AssetPath The path to the asset to open, e.g. '/Game/Meshes/SM_Cube'.
- L352 _public prototype_ `static TArray<FString> GetOpenAssets();` — `UFUNCTION(meta = (AICallable))` — Gets the list of assets currently open in asset editors. @return A list of package paths to the assets open in asset editors.
- L365 _public prototype_ `static UToolCallAsyncResultVoid* StartPIE(const FPIESessionOptions& Options);` — `UFUNCTION(meta = (AICallable))` — Starts a Play-In-Editor or Simulate-In-Editor session using the current level. Completes after the engine fires PostPIEStarted (session fully started, BeginPlay called) and Options.WarmupSeconds have elapsed, giving project- specific initialization (services, authentication, plugin warmup) time to settle before the agent inspects state or logs. Raises an error if a play session is already running. @param Options Session configuration: PIE vs Simulate, play mode, optional spawn transform override, warmup duration. See FPIESessionOptions.
- L372 _public prototype_ `static UToolCallAsyncResultVoid* StopPIE();` — `UFUNCTION(meta = (AICallable))` — Stops the currently running play session (PIE or Simulate). Raises an error if no play session is running.
- L379 _public prototype_ `static bool IsPIERunning();` — `UFUNCTION(meta = (AICallable))` — Returns whether a Play In Editor session is currently running. @return True if PIE is active, false otherwise.
- L382 _private prototype_ `static TSharedPtr<FJsonObject> CVarToJson(IConsoleObject* CVar);`

### `Plugins/Experimental/Toolsets/EditorToolset/Source/EditorToolset/Private/LogsToolset.h` (Private)


#### class `ULogsToolset`  
`class ULogsToolset : public UToolsetDefinition`  
_L14-65_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for reading the Unreal Engine output log and controlling log category verbosity.
- L29 _public prototype_ `static TArray<FString> GetLogEntries( const FString& Category = TEXT(""), const FString& Pattern = TEXT(""), int32 MaxEntries = 1000);` — `UFUNCTION(meta = (AICallable), Category = "LogsToolset")` — Returns log entries from the current session's log file. @param Category If non-empty, only returns entries from this log category (e.g. "LogTemp"). @param Pattern If non-empty, only returns entries whose text matches this regular expression. @param MaxEntries Maximum number of entries to return, taken from the end of the log. Pass 0 for no limit. Defaults to 1000. @return A list of matching log entries in chronological order.
- L39 _public prototype_ `static TArray<FString> GetLogCategories(const FString& Filter = TEXT(""));` — `UFUNCTION(meta = (AICallable), Category = "LogsToolset")` — Returns a sorted list of registered log categories. @param Filter If non-empty, only returns categories whose name contains this substring. @return A sorted list of log category names (e.g. ["LogBlueprint", "LogTemp"]).
- L49 _public prototype_ `static FString GetVerbosity(const FString& Category);` — `UFUNCTION(meta = (AICallable), Category = "LogsToolset")` — Returns the current verbosity level for a log category. @param Category The log category name, e.g. "LogTemp". @return The verbosity level as a string: one of "NoLogging", "Fatal", "Error", "Warning", "Display", "Log", "Verbose", or "VeryVerbose". Raises a script error if the category is not found.
- L58 _public prototype_ `static void SetVerbosity(const FString& Category, const FString& Verbosity);` — `UFUNCTION(meta = (AICallable), Category = "LogsToolset")` — Sets the verbosity level for a log category. @param Category The log category name, e.g. "LogTemp". @param Verbosity The verbosity level: one of "NoLogging", "Fatal", "Error", "Warning", "Display", "Log", "Verbose", or "VeryVerbose".
- L61 _private prototype_ `static FString GetLogFilePath();`
- L62 _private prototype_ `static TArray<FString> ReadLogLines();`
