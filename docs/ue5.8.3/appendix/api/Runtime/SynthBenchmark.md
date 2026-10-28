# Runtime / SynthBenchmark

- module root: `Source/Runtime/SynthBenchmark`
- headers: 1; symbols: 6
- symbol kinds: class=1, function=2, prototype=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore
- PublicDependencyModuleNames: Core, RHI, RenderCore

### `Source/Runtime/SynthBenchmark/Public/SynthBenchmark.h` (Public)


#### class `ISynthBenchmark`  
`class ISynthBenchmark : public IModuleInterface`  
_L15-47_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `virtual void Run(FSynthBenchmarkResults& Out, bool bGPUBenchmark = true, float WorkScale = 10.0f) const = 0;` — @param >0, WorkScale 10 for normal precision and runtime of less than a second
- L24 _public prototype_ `virtual void GetRHIDisplay(FGPUAdpater& Out) const = 0;` — could be moved out of SynthBenchmark, it only requires the RHI, only returns valid data after the RHI started up
- L25 _public prototype_ `virtual void GetRHIInfo(FGPUAdpater& Out, FString& RHIName) const = 0;`
- L33 _public function_ `static inline ISynthBenchmark& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L43 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
