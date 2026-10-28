# Runtime / MoviePlayerProxy

- module root: `Source/Runtime/MoviePlayerProxy`
- headers: 2; symbols: 19
- symbol kinds: class=3, function=3, member=2, prototype=11
- PrivateDependencyModuleNames: Core

### `Source/Runtime/MoviePlayerProxy/Public/MoviePlayerProxy.h` (Public)


#### class `FMoviePlayerProxy`  
`class FMoviePlayerProxy`  
_L17-38_
- desc: This provides a mechanism to connect the engine (the client) to a movie player (the server). Engine code can call BlockingStarted/Tick/Finished around blocking areas. The movie player can call RegisterServer/UnregisterServer so it can receive the calls from the engine.
- L21 _public prototype_ `static void BlockingStarted();` — Call this before doing a blocking operation on the game thread so that the movie player can activate.
- L23 _public prototype_ `static void BlockingTick();` — Call this periodically during a blocking operation on the game thread.
- L25 _public prototype_ `static void BlockingFinished();` — Call this once the blocking operation is done to shut down the movie player.
- L27 _public prototype_ `static void BlockingForceFinished();` — Call this to make sure the movie player is no longer running.
- L29 _public prototype_ `static void SetIsSlateThreadAllowed(bool bInIsSlateThreadAllowed);` — Call this to prevent the movie player from using the Slate thread.
- L31 _public prototype_ `static void RegisterServer(IMoviePlayerProxyServer* InServer);` — Call this to hook up a server.
- L33 _public prototype_ `static void UnregisterServer();` — Call this to unregister the current server.
- L37 _private member_ `static IMoviePlayerProxyServer* Server;` — Our current worker that handles blocks.

#### class `FMoviePlayerProxyBlock`  
`class FMoviePlayerProxyBlock`  
_L51-78_
- desc: This is a helper class for FMoviePlayerProxy. You can just add an instance of this somewhere like FMoviePlayerProxyBlock MoviePlayerBlock; It will automatically call FMoviePlayerProxy::BlockingStarted and then call FMoviePlayerProxy::BlockingFinished when it goes out of scope. You can also manually call Finish if you want to trigger this earlier.
- L54 _public function_ `FMoviePlayerProxyBlock() : bIsBlockDone(false)`
- L60 _public function_ `~FMoviePlayerProxyBlock()`
- L66 _public function_ `void Finish()` — Call this if you want to end the block before this object goes out of scope.
- L77 _private member_ `bool bIsBlockDone;` — If false, then a block is still active and finish needs to be called..

### `Source/Runtime/MoviePlayerProxy/Public/MoviePlayerProxyServer.h` (Public)


#### class `IMoviePlayerProxyServer`  
`class IMoviePlayerProxyServer`  
_L11-22_
- desc: Implement this interface if you want to handle what happens when the engine interacts with the MoviePlayer, etc when the game thread is blocked.
- L15 _public prototype_ `virtual void BlockingStarted() = 0;` — Called before doing a blocking operation on the game thread occurs so that the movie player can activate.
- L17 _public prototype_ `virtual void BlockingTick() = 0;` — Called periodically during a blocking operation on the game thread.
- L19 _public prototype_ `virtual void BlockingFinished() = 0;` — Called once the blocking operation is done to shut down the movie player.
- L21 _public prototype_ `virtual void SetIsSlateThreadAllowed(bool bInIsSlateThreadAllowed) = 0;` — Call this to prevent the movie player from using the Slate thread.
