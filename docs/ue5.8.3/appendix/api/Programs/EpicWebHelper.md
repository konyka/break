# Programs / EpicWebHelper

- module root: `Source/Programs/EpicWebHelper`
- headers: 6; symbols: 66
- symbol kinds: class=6, function=9, macro=1, member=17, prototype=32, struct=1
- PrivateDependencyModuleNames: ApplicationCore, CEF3Utils, Core, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/EpicWebHelper/Private/EpicWebHelper.h` (Private)


#### Free symbols / members of external scopes

- L16 _prototype_ `int32 RunCEFSubProcess(const CefMainArgs& MainArgs);` — The application's main function. @param MainArgs Main Arguments for the process (created differently on each platform). @return Application's exit value.

### `Source/Programs/EpicWebHelper/Private/EpicWebHelperApp.h` (Private)


#### class `FEpicWebHelperApp`  
`class FEpicWebHelperApp : public CefApp , public CefRenderProcessHandler`  
_L17-53_
- inherits: `CefApp,CefRenderProcessHandler`
- desc: Implements CEF App and other Process level interfaces
- L26 _public prototype_ `FEpicWebHelperApp();` — Default Constructor
- L30 _private function_ `virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override` — CefApp methods:
- L33 _private prototype_ `virtual void OnContextCreated( CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefV8Context> Context ) override;` — CefRenderProcessHandler methods:
- L35 _private prototype_ `virtual void OnContextReleased( CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefV8Context> Context ) override;`
- L37 _private prototype_ `virtual bool OnProcessMessageReceived( CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message ) override;`
- L39 _private prototype_ `virtual void OnBrowserCreated(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefDictionaryValue> ExtraInfo) override;`
- L42 _private prototype_ `virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefDOMNode> Node) override;`
- L46 _private member_ `FEpicWebHelperRemoteScripting RemoteScripting;` — Handles remote scripting messages from the frontend process
- L49 _private member_ `TMap<int32, bool> PendingBrowserCreated;` — Stores the browser ID and flag for any browser so we can track if we have told the main process about it
- L52 _private prototype_ `IMPLEMENT_REFCOUNTING(FEpicWebHelperApp);` — Include the default reference counting implementation.

### `Source/Programs/EpicWebHelper/Private/EpicWebHelperCallbackRegistry.h` (Private)


#### struct `FEpicWebHelperCallbackRegistryEntry`  
`struct FEpicWebHelperCallbackRegistryEntry`  
_L13-29_
- desc: Represents information about a JS function that can be called from the browser process.
- L15 _public function_ `FEpicWebHelperCallbackRegistryEntry(CefRefPtr<CefV8Context> InContext, CefRefPtr<CefV8Value> InObject, CefRefPtr<CefV8Value> InFunction, CefRefPtr<CefV8Value> InOnError, bool bInOneShot) : Context(InContext) , Object(InObject) , Function(InFunction) , OnError(InOnError) , bOneShot(bInOneShot)`
- L24 _public member_ `CefRefPtr<CefV8Context> Context;`
- L25 _public member_ `CefRefPtr<CefV8Value> Object;`
- L26 _public member_ `CefRefPtr<CefV8Value> Function;`
- L27 _public member_ `CefRefPtr<CefV8Value> OnError;`
- L28 _public member_ `bool bOneShot;`

#### class `FEpicWebHelperCallbackRegistry`  
`class FEpicWebHelperCallbackRegistry : public TMap<FGuid, FEpicWebHelperCallbackRegistryEntry>`  
_L31-44_
- inherits: `TMap<FGuid,FEpicWebHelperCallbackRegistryEntry>`
- L38 _public prototype_ `FGuid FindOrAdd(CefRefPtr<CefV8Context> Context, CefRefPtr<CefV8Value> Object, CefRefPtr<CefV8Value> Function, CefRefPtr<CefV8Value> OnError=nullptr, bool bOneShot=false);` — Looks for a matching entry in the registry or adds a new one, returning its Id. A matching entry must have the same Context, Object, Function and OnError object. One-shot callbacks will always result in a new entry , even if there is an exact match.
- L43 _public prototype_ `void RemoveByContext(CefRefPtr<CefV8Context> Context);` — Deletes all entries that have a matching context.

### `Source/Programs/EpicWebHelper/Private/EpicWebHelperLibCEFIncludes.h` (Private)


#### Free symbols / members of external scopes

- L6 _macro_ `# define OVERRIDE override`

### `Source/Programs/EpicWebHelper/Private/EpicWebHelperRemoteMethodHandler.h` (Private)


#### class `FEpicWebHelperRemoteObject`  
`class FEpicWebHelperRemoteObject : public CefBaseRefCounted`  
_L34-59_
- inherits: `CefBaseRefCounted`
- L38 _public function_ `FEpicWebHelperRemoteObject(FEpicWebHelperRemoteScripting* InRemoteScripting, CefRefPtr<CefBrowser> InBrowser, CefRefPtr<CefV8Context> InContext, const FGuid& InObjectId) : RemoteScripting(InRemoteScripting) , Browser(InBrowser) , CreationContext(InContext) , ObjectId(InObjectId)`
- L44 _public prototype_ `bool ExecuteMethod(const CefString& MethodName, CefRefPtr<CefV8Value> Object, const CefV8ValueList& Arguments, CefRefPtr<CefV8Value>& Retval, CefString& Exception);`
- L48 _public prototype_ `void ReleaseMethod();`
- L51 _private member_ `FEpicWebHelperRemoteScripting* RemoteScripting;`
- L52 _private member_ `CefRefPtr<CefBrowser> Browser;`
- L53 _private member_ `CefRefPtr<CefV8Context> CreationContext;`
- L54 _private member_ `FGuid ObjectId;`
- L58 _private prototype_ `IMPLEMENT_REFCOUNTING(FEpicWebHelperRemoteObject);` — Include the default reference counting implementation.

#### class `FEpicWebHelperRemoteMethodHandler`  
`class FEpicWebHelperRemoteMethodHandler : public CefV8Handler`  
_L61-81_
- inherits: `CefV8Handler`
- L66 _public function_ `FEpicWebHelperRemoteMethodHandler(CefRefPtr<FEpicWebHelperRemoteObject> InRemoteObject, CefString& InMethodName) : RemoteObject(InRemoteObject) , MethodName(InMethodName)`
- L71 _public prototype_ `virtual bool Execute(const CefString& Name, CefRefPtr<CefV8Value> Object, const CefV8ValueList& Arguments, CefRefPtr<CefV8Value>& Retval, CefString& Exception) override;`
- L76 _private member_ `CefRefPtr<FEpicWebHelperRemoteObject> RemoteObject;`
- L77 _private member_ `CefString MethodName;`
- L80 _private prototype_ `IMPLEMENT_REFCOUNTING(FEpicWebHelperRemoteMethodHandler);` — Include the default reference counting implementation.

### `Source/Programs/EpicWebHelper/Private/EpicWebHelperRemoteScripting.h` (Private)


#### class `FEpicWebHelperRemoteScripting`  
`class FEpicWebHelperRemoteScripting`  
_L36-172_
- L41 _public function_ `FEpicWebHelperRemoteScripting()`
- L44 _public prototype_ `CefRefPtr<CefV8Value> CefToV8(CefRefPtr<CefDictionaryValue> Dictionary);`
- L45 _public prototype_ `CefRefPtr<CefV8Value> CefToV8(CefRefPtr<CefListValue> List);`
- L46 _public prototype_ `void CefToV8Arglist(CefRefPtr<CefListValue> List, CefV8ValueList& Values);`
- L49 _public function_ `template<typename ContainerType, typename KeyType> CefRefPtr<CefV8Value> CefToV8(CefRefPtr<ContainerType> Container, KeyType Key)` — Works for CefListValue and CefDictionaryValues
- L74 _public function_ `template<typename ContainerType, typename KeyType> bool V8ToCef(CefRefPtr<ContainerType> Container, CefRefPtr<CefV8Value> Parent, KeyType Key, CefRefPtr<CefV8Value> Value)`
- L125 _public prototype_ `CefRefPtr<CefListValue> V8ArrayToCef(const CefV8ValueList& Values);`
- L126 _public prototype_ `CefRefPtr<CefListValue> V8ArrayToCef(CefRefPtr<CefV8Value> Value);`
- L127 _public prototype_ `CefRefPtr<CefDictionaryValue> V8ObjectToCef(CefRefPtr<CefV8Value> Value);`
- L128 _public prototype_ `CefRefPtr<CefDictionaryValue> V8FunctionToCef(CefRefPtr<CefV8Value> Object, CefRefPtr<CefV8Value> Function);`
- L131 _public prototype_ `bool OnProcessMessageReceived(CefRefPtr<CefBrowser> Browser, CefProcessId SourceProcess, CefRefPtr<CefProcessMessage> Message);`
- L132 _public prototype_ `void OnContextCreated(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefV8Context> Context);`
- L133 _public prototype_ `void OnContextReleased(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefFrame> Frame, CefRefPtr<CefV8Context> Context);`
- L134 _public prototype_ `void InitPermanentBindings(int32 BrowserID, CefRefPtr<CefDictionaryValue> Values);`
- L138 _private prototype_ `bool HandleExecuteJSFunctionMessage(CefRefPtr<CefListValue> MessageArguments);` — Scripting integration message handlers:
- L139 _private prototype_ `bool HandleSetValueMessage(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefListValue> MessageArguments);`
- L140 _private prototype_ `bool HandleDeleteValueMessage(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefListValue> MessageArguments);`
- L144 _private prototype_ `bool HandleUnRegisterUObjectMessage(CefRefPtr<CefListValue> MessageArguments);` — Deletes information about a UObject on the client side.
- L146 _private prototype_ `CefRefPtr<CefV8Value> CefToPlainV8Object(CefRefPtr<CefDictionaryValue> Dictionary);`
- L147 _private prototype_ `CefRefPtr<CefV8Value> CreateUObjectProxy(FGuid ObjectId, CefRefPtr<CefListValue> Methods);`
- L150 _private member_ `FEpicWebHelperCallbackRegistry CallbackRegistry;` — Stores information about functions that can be called from the remote process.
- L152 _private member_ `TMap<int32,CefRefPtr<CefDictionaryValue>> PermanentBindings;`
- L153 _private member_ `TMap<FGuid,CefRefPtr<FEpicWebHelperRemoteObject>> RemoteObjects;`

#### class `FEpicWebHelperRemoteScripting::ScopedV8Context`  
`class ScopedV8Context`  
_L155-169_
- L158 _public function_ `ScopedV8Context(CefRefPtr<CefV8Context> InContext) : Context(InContext)`
- L163 _public function_ `~ScopedV8Context()`
- L168 _private member_ `CefRefPtr<CefV8Context> Context;`
