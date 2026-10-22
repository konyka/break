# Runtime / StreamingPauseRendering

- module root: `Source/Runtime/StreamingPauseRendering`
- headers: 1; symbols: 12
- symbol kinds: class=1, member=6, prototype=5
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, RHI, RenderCore, SlateCore
- PublicDependencyModuleNames: Engine, MoviePlayer, Slate

### `Source/Runtime/StreamingPauseRendering/Public/StreamingPauseRendering.h` (Public)


#### class `FStreamingPauseRenderingModule`  
`class FStreamingPauseRenderingModule : public IModuleInterface`  
_L17-62_
- inherits: `IModuleInterface`
- desc: Module handling default behavior for streaming pause rendering. Games can override by calling RegisterBegin/EndStreamingPauseDelegate with their own delegates.
- L23 _public prototype_ `FStreamingPauseRenderingModule();` — Default constructor.
- L28 _public prototype_ `virtual void BeginStreamingPause( class FViewport* Viewport );` — Enqueue the streaming pause to suspend rendering during blocking load.
- L33 _public prototype_ `virtual void EndStreamingPause();` — Enqueue the streaming pause to resume rendering after blocking load is completed.
- L39 _public prototype_ `virtual void StartupModule();`
- L40 _public prototype_ `virtual void ShutdownModule();`
- L45 _public member_ `TSharedPtr<FSceneViewport> SceneViewport;` — Viewport being used to render the scene once to a target while paused
- L47 _public member_ `TSharedPtr<SViewport> ViewportWidget;` — Slate viewport widget used to draw the target
- L49 _public member_ `TSharedPtr<class FBackgroundView> BackgroundView;` — Helper class to translate the RHI render target to Slate
- L52 _public member_ `FBeginStreamingPauseDelegate BeginDelegate;` — Delegate providing default functionality for beginning streaming pause.
- L55 _public member_ `FEndStreamingPauseDelegate EndDelegate;` — Delegate providing default functionality for ending streaming pause.
- L61 _public member_ `bool bMovieWasStarted;` — If a movie was started by BeginStreamingPause. This could be false if a movie was already playing when BeginStreamingPause was called
