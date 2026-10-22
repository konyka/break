# Plugins / FieldNotificationTrace

- module root: `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTrace`
- headers: 2; symbols: 19
- symbol kinds: class=2, macro=7, namespace=4, prototype=6
- PrivateDependencyModuleNames: GameplayInsights, TraceLog
- PublicDependencyModuleNames: Core, CoreUObject, Engine, FieldNotification

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTrace/Private/FieldNotificationTraceModule.h` (Private)


#### class `UE::FieldNotification::FTraceModule`  
`class FTraceModule : public IModuleInterface`  
_L13-22_
- inherits: `IModuleInterface`
- L16 _public prototype_ `FTraceModule() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Plugins/Developer/FieldNotificationTrace/Source/FieldNotificationTrace/Public/Trace/FieldNotificationTrace.h` (Public)


#### class `UE::FieldNotification::FTrace`  
`class FTrace : public FNoncopyable`  
_L21-30_
- inherits: `FNoncopyable`
- L24 _public prototype_ `static void OutputObjectBegin(TScriptInterface<INotifyFieldValueChanged> Interface);`
- L25 _public prototype_ `static void OutputObjectEnd(TScriptInterface<INotifyFieldValueChanged> Interface);`
- L26 _public prototype_ `static void OutputUpdateField(UObject* Instance, FFieldId Id);`
- L28 _public prototype_ `static void StartTracing();`
- L29 _public prototype_ `static void StopTracing();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_FIELDNOTIFICATION_TRACE_ENABLED (UE_TRACE_ENABLED && !IS_PROGRAM && !UE_BUILD_SHIPPING)`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace FieldNotification` (scope `UE`)
- L34 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_LIFETIME_BEGIN(Interface) \`
- L37 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_LIFETIME_END(Interface) \`
- L40 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_FIELD_VALUE_CHANGED(Object, InField) \`
- L45 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_LIFETIME_BEGIN(Interface)`
- L46 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_LIFETIME_END(Interface)`
- L47 _macro_ `#define UE_TRACE_FIELDNOTIFICATION_FIELD_VALUE_CHANGED(Object, InField)`
