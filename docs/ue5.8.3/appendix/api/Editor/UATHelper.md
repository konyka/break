# Editor / UATHelper

- module root: `Source/Editor/UATHelper`
- headers: 2; symbols: 5
- symbol kinds: class=1, function=2, prototype=1, typedef=1
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, EditorFramework, Engine, GameProjectGeneration, InputCore, Json, OutputLog, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: MessageLog

### `Source/Editor/UATHelper/Public/IUATHelperModule.h` (Public)


#### class `IUATHelperModule`  
`class IUATHelperModule : public IModuleInterface`  
_L14-48_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L25 _public function_ `static inline IUATHelperModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _public typedef_ `typedef TFunction<void(FString, double)> UatTaskResultCallack;` — Used to callback into calling code when a UAT task completes. First param is the result type, second param is the runtime in sec.
- L47 _public prototype_ `virtual void CreateUatTask(const FString& CommandLine, const FText& PlatformDisplayName, const FText& TaskName, const FText &TaskShortName, const FSlateBrush* TaskIcon, const TArray<struct FAnalyticsEventAttribute>* OptionalAnalyticsParamArray = nullptr, UatTaskResultCallack ResultCallback = UatTaskResultCallack(), const FString& ResultLocation = FString(), const FText& ExtraSubText = FText::GetEmpty()) = 0;` — Creates and starts up a UAT Task @param	ResultLocation	The folder where the result of the task will be stored @param	ExtraSubText	Optional subtext displayed below the notification title while the task is in progress and on success

### `Source/Editor/UATHelper/UATHelperModule.h` (Other)
_(no declarations extracted)_
