# Developer / EditorAnalyticsSession

- module root: `Source/Developer/EditorAnalyticsSession`
- headers: 2; symbols: 4
- symbol kinds: class=2, prototype=1, struct=1
- PrivateDependencyModuleNames: Core

### `Source/Developer/EditorAnalyticsSession/Public/EditorAnalyticsSession.h` (Public)


#### struct `FEditorAnalyticsSession`  
`struct FEditorAnalyticsSession`  
_L12-14_

#### class `FEditorAnalyticsSessionModule`  
`class FEditorAnalyticsSessionModule : public IModuleInterface`  
_L20-22_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L17 _prototype_ `void CleanupDeprecatedAnalyticSessions(const FTimespan& MaxAge);` — This function removes expired sessions that were created by the deprecated system.

### `Source/Developer/EditorAnalyticsSession/Public/EditorSessionSummarySender.h` (Public)


#### class `FEditorSessionSummarySender`  
`class FEditorSessionSummarySender`  
_L9-11_
- reflection: `UE_DEPRECATED(5.0, "Deprecated. This class was replaced by FAnalyticsSessionSummarySender")`
