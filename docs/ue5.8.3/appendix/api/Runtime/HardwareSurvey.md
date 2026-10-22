# Runtime / HardwareSurvey

- module root: `Source/Runtime/HardwareSurvey`
- headers: 2; symbols: 5
- symbol kinds: class=1, function=3, prototype=1
- DynamicallyLoadedModuleNames: Analytics
- PrivateIncludePathModuleNames: Analytics
- PublicDependencyModuleNames: ApplicationCore, Core

### `Source/Runtime/HardwareSurvey/Public/HardwareSurvey.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/HardwareSurvey/Public/IHardwareSurveyModule.h` (Public)


#### class `IHardwareSurveyModule`  
`class IHardwareSurveyModule : public IModuleInterface`  
_L13-51_
- inherits: `IModuleInterface`
- desc: Interface for the hardware survey module.
- L24 _public function_ `static inline IHardwareSurveyModule& Get()` — Singleton-like access to this module's interface. Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual void StartHardwareSurvey(IAnalyticsProvider& AnalyticsProvider) = 0;` — Init and begin the async platform hardware survey. @param AnalyticsProvider		The analytics provider to use when sending survey info.
- L50 _public function_ `virtual ~IHardwareSurveyModule()` — Virtual destructor.
