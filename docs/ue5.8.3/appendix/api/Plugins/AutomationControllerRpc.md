# Plugins / AutomationControllerRpc

- module root: `Plugins/AutomationControllerRpc/Source/AutomationControllerRpc`
- headers: 2; symbols: 23
- symbol kinds: class=2, enum=1, enumerator=6, member=3, prototype=11
- PrivateDependencyModuleNames: AutomationController, Core, CoreUObject, ExternalRpcRegistry, HTTP, HTTPServer, Json, SessionServices

### `Plugins/AutomationControllerRpc/Source/AutomationControllerRpc/Public/AutomationControllerRpcModule.h` (Public)


#### class `FAutomationControllerRpcModule`  
`class FAutomationControllerRpcModule : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `UAutomationControllerRpcRegistrationComponent* AutomationControllerRpcRegistrationComponent = nullptr;` — RPC registration component around the AutomationController

### `Plugins/AutomationControllerRpc/Source/AutomationControllerRpc/Public/AutomationControllerRpcRegistrationComponent.h` (Public)


#### enum `EAutomationControllerState`  
`enum class EAutomationControllerState : uint8`  
_L16-24_
- reflection: `UENUM()`
- desc: States for the underlying automation controller process
- L18 _public enumerator_ `Uninitialized` — Automation process has not been setup
- L19 _public enumerator_ `Idle` — Automation process is not running
- L20 _public enumerator_ `FindingWorkers` — Find workers to run the tests
- L21 _public enumerator_ `RequestTests` — Find the tests that can be run on the workers
- L22 _public enumerator_ `DoingRequestedWork` — Do whatever was requested
- L23 _public enumerator_ `Complete` — The process is finished

#### class `UAutomationControllerRpcRegistrationComponent`  
`class UAutomationControllerRpcRegistrationComponent : public UExternalRpcRegistrationComponent`  
_L27-69_
- reflection: `UCLASS()`
- inherits: `UExternalRpcRegistrationComponent`
- L33 _public prototype_ `static UAutomationControllerRpcRegistrationComponent* GetInstance();` — Gets the singleton instance of this component.
- L36 _public prototype_ `void RegisterAlwaysOnHttpCallbacks() override;` — Registers the necessary routes to the AutomationController.
- L39 _public prototype_ `void DeregisterHttpCallbacks() override;` — Deregisters all previously registered routes.
- L41 _public prototype_ `void BeginDestroy() override;`
- L47 _private prototype_ `bool HttpAutomationControllerInitializeCommand(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Registers the route to initialize the AutomationController.
- L50 _private prototype_ `bool HttpAutomationControllerGetStateCommand(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Registers the route to get the various states of the AutomationController.
- L53 _private prototype_ `bool HttpAutomationControllerGetAvailableTestsCommand(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Registers the route to fetch all registered tests from the AutomationController.
- L56 _private prototype_ `bool HttpAutomationControllerRunTestsCommand(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Registers the route to trigger test execution from the AutomationController.
- L59 _private prototype_ `bool HttpAutomationControllerGenerateReportsCommand(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Registers the route to generate a report from the previous test execution from the AutomationController.
- L63 _private member_ `static UAutomationControllerRpcRegistrationComponent* ObjectInstance;` — Instance of this RPC component.
- L67 _private member_ `TUniquePtr<FAutomationControllerRpcBridge> AutomationControllerRpcBridge = nullptr;` — Instance of the AutomationController.
