# Plugins / GeoReferencingEditor

- module root: `Plugins/Runtime/GeoReferencing/Source/GeoReferencingEditor`
- headers: 1; symbols: 5
- symbol kinds: class=1, prototype=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GeoReferencing, InputCore, Projects, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencingEditor/Public/GeoReferencingEditorBPLibrary.h` (Public)


#### class `UGeoReferencingEditorBPLibrary`  
`class UGeoReferencingEditorBPLibrary : public UBlueprintFunctionLibrary`  
_L12-61_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L23 _private prototype_ `static void GetViewportCursorLocation(bool& Focused, FVector2D& ScreenLocation);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Utilities")` — Retrieve the Viewport-Space position of the mouse in the Level Editor Viewport. If the Level editor not are in focus it will return false. @param	Focused			If the Level editor not are in focus it will return false. @param	ScreenLocation	The screen location result.
- L34 _private prototype_ `static void GetViewportCursorInformation(bool& Focused, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Utilities")` — Retrieve information about the viewport under the mouse cursor. @param	Focused			If the Level editor not are in focus it will return false. @param	ScreenLocation	Viewport-Space position of cursor. @param	WorldLocation	Location of viewport origin (camera) in world space. @param	WorldDirection	Direction of viewport (camera) in world space.
- L47 _private prototype_ `static void LineTraceViewport(FVector2D& ScreenLocation, const TArray<AActor*>& ActorsToIgnore, const bool bTraceComplex, const bool bShowTrace, bool& bSuccess, FHitResult& HitResult);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Utilities", meta = (AdvancedDisplay = "TraceComplex, ShowTrace, ActorsToIgnore"))` — LineTrace under mouse cursor and return various information @param	ScreenLocation	Viewport-Space position of cursor. @param	ActorsToIgnore	Collection of actors for this trace to ignore. @param	TraceComplex	Whether we should trace against complex collision. @param	ShowTrace		Whether we should debug draw the trace. @param	Success			If the Level editor not are in focus it will return false, and same if nothing is hit. @param	HitResult		The trace hits result.
- L60 _private prototype_ `static void LineTrace(const FVector WorldLocation, const FVector WorldDirection, const TArray<AActor*>& ActorsToIgnore, const bool TraceComplex, const bool ShowTrace, bool& Success, FHitResult& HitResult);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Utilities", meta = (AdvancedDisplay = "TraceComplex, ShowTrace, ActorsToIgnore"))` — LineTrace at specific location/direction @param	WorldLocation	Location of viewport origin (camera) in world space @param	WorldDirection	Direction of viewport (camera) in world space @param	TraceComplex	Whether we should trace against complex collision @param	ShowTrace		Whether we should debug draw the trace @param	Success			If the Level editor not are in focus it will return false, and same if nothing is hit. @param	HitResult		The trace hits result.
