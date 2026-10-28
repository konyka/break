# Plugins / MLAdapterTestSuite

- module root: `Plugins/AI/MLAdapter/Source/MLAdapterTestSuite`
- headers: 2; symbols: 16
- symbol kinds: class=1, enum=1, enumerator=1, function=6, member=4, namespace=1, prototype=1, struct=1
- PrivateDependencyModuleNames: EditorFramework, RPCLib, UnrealEd
- PublicDependencyModuleNames: AIModule, AITestSuite, Core, CoreUObject, Engine, JsonUtilities, MLAdapter

### `Plugins/AI/MLAdapter/Source/MLAdapterTestSuite/Private/RPCTestBase.h` (Private)


#### struct `FRPCTestBase`  
`struct FRPCTestBase : public FAITestBase`  
_L17-45_
- inherits: `FAITestBase`
- L24 _public member_ `EMLAdapterServerMode Mode = EMLAdapterServerMode::Client;`
- L25 _public member_ `FDelegateHandle BindClientHandle;`
- L26 _public member_ `FDelegateHandle BindServerHandle;`
- L27 _public member_ `rpc::client* RPCClient = nullptr;`
- L29 _public function_ `FRPCTestBase()`
- L41 _public function_ `virtual void SetUpClientBinds(FRPCServer& Server)`
- L42 _public function_ `virtual void SetUpServerBinds(FRPCServer& Server)`
- L44 _public prototype_ `virtual void TearDown() override;`

#### enum `FRPCTestBase::(anonymous)`  
``  
_L20-22_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace rpc`
- L21 _enumerator_ `DefaultServerPort = 10101` (scope `FRPCTestBase::__anone50bb67c0103`)
- L32 _function_ `` (scope `FRPCTestBase::FRPCTestBase`)

### `Plugins/AI/MLAdapter/Source/MLAdapterTestSuite/Public/MLAdapterTestSuiteModule.h` (Public)


#### class `IMLAdapterTestSuiteModule`  
`class IMLAdapterTestSuiteModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IMLAdapterTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
