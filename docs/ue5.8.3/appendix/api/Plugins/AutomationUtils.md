# Plugins / AutomationUtils

- module root: `Plugins/Experimental/AutomationUtils/Source/AutomationUtils`
- headers: 1; symbols: 6
- symbol kinds: class=1, macro=1, prototype=4
- PrivateDependencyModuleNames: Json, RHI, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/AutomationUtils/Source/AutomationUtils/Public/AutomationUtilsBlueprintLibrary.h` (Public)


#### class `UAutomationUtilsBlueprintLibrary`  
`class UAutomationUtilsBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L18 _private prototype_ `static void TakeGameplayAutomationScreenshot(const FString ScreenshotName, float MaxGlobalError = .02, float MaxLocalError = .12, FString MapNameOverride = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L26 _private prototype_ `static void AddAutomationMountPoint(const FString& RootPath = TEXT("/Aut` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Registers a virtual mount point rooted at FPaths::AutomationTransientDir(). Call RemoveAutomationMountPoint to unregister when done. @param RootPath  Virtual root path.
- L33 _private prototype_ `static void RemoveAutomationMountPoint(const FString& RootPath = TEXT("/Aut` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Unregisters a mount point previously registered with AddAutomationMountPoint. @param RootPath  Virtual root path.
- L43 _private prototype_ `static void FinishAllAssetCompilation();` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Blocks the game thread until all in-flight asset compilation finishes and the render thread has drained the followup commands the compile workers posted. Use this in test teardown before deleting assets whose shader compilation might still be in flight; otherwise GC can destroy an FMaterial mid-compile and hit ~FMaterial's RenderingThreadCompilingShaderMapId == 0 assert.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUTOMATIONUTILS_API`
