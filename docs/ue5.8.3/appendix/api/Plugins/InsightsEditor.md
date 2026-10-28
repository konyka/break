# Plugins / InsightsEditor

- module root: `Plugins/TraceUtilities/Source/InsightsEditor`
- headers: 2; symbols: 15
- symbol kinds: class=2, delegate=1, function=3, member=1, namespace=4, prototype=4
- PrivateDependencyModuleNames: Engine, InputCore, Slate, SlateCore, ToolMenus, TraceLog
- PublicDependencyModuleNames: Core, TraceInsights

### `Plugins/TraceUtilities/Source/InsightsEditor/Private/InsightsEditorModule.h` (Private)


#### class `UE::InsightsEditor::FInsightsEditorModule`  
`class FInsightsEditorModule : public IInsightsEditorModule`  
_L12-27_
- inherits: `IInsightsEditorModule`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public function_ `virtual void SetStartAnalysisOnInsightsWindowCreated(bool InValue)`
- L23 _private prototype_ `void StartTraceAnalysis();`
- L26 _private member_ `bool bStartAnalysisOnInsightsWindowCreated = true;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInsightsEditor, Log, All) namespace UE::InsightsEditor { class FInsightsEditorModule : public IInsightsEditorModule { public:`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace InsightsEditor` (scope `UE`)

### `Plugins/TraceUtilities/Source/InsightsEditor/Public/IInsightsEditorModule.h` (Public)


#### class `UE::InsightsEditor::IInsightsEditorModule`  
`class IInsightsEditorModule : public IModuleInterface`  
_L10-38_
- inherits: `IModuleInterface`
- L20 _public function_ `static inline IInsightsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L37 _public prototype_ `virtual void SetStartAnalysisOnInsightsWindowCreated(bool InValue) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace InsightsEditor` (scope `UE`)
