# Plugins / USDPregenPy

- module root: `Plugins/Experimental/USDPregen/Source/USDPregenPy`
- headers: 2; symbols: 42
- symbol kinds: class=3, function=29, member=1, namespace=2, prototype=5, typedef=2
- PrivateDependencyModuleNames: Core, Python3, USDPregenCore, UnrealUSDWrapper

### `Plugins/Experimental/USDPregen/Source/USDPregenPy/Private/wrapperHelpers.h` (Private)


#### class `internal::py::VirtualDispatchHelper`  
`class VirtualDispatchHelper`  
_L95-540_
- L103 _protected function_ `DefaultResultHandler( const PXR_BOOST_PYTHON_NAMESPACE::object& result)`
- L119 _protected function_ `CallPythonOverrideWithResultHandler( WrapperType* wrapper, const char* functionName, DefaultFn defaultFn, ResultFn&& resultFn, Args&&... args)`
- L199 _protected function_ `CallPythonOverride( WrapperType* wrapper, const char* functionName, DefaultFn defaultFn, Args&&... args)`
- L224 _protected function_ `CallPythonPureVirtualWithResultHandler( WrapperType* wrapper, const char* functionName, ResultFn&& resultFn, Args&&... args)`
- L297 _protected function_ `CallPythonPureVirtual( WrapperType* wrapper, const char* functionName, Args&&... args)`
- L312 _protected function_ `GetPythonClassName(const WrapperType& wrapper)`
- L336 _private function_ `_GetPrimPtr(const T&)`
- L342 _private function_ `_GetPrimPtr(const pxr::UsdPrim& prim)`
- L349 _private function_ `_GetStagePtr(const T&)`
- L355 _private function_ `_GetStagePtr(const pxr::UsdStageRefPtr& stage)`
- L362 _private function_ `_GetTargetUidPtr(const T&)`
- L368 _private function_ `_GetTargetUidPtr(const TargetUid& targetUid)`
- L374 _private function_ `_FindPrimInArgs()`
- L381 _private function_ `_FindPrimInArgs(const First& first, const Rest&... rest)`
- L391 _private function_ `_FindStageInArgs()`
- L398 _private function_ `_FindStageInArgs(const First& first, const Rest&... rest)`
- L408 _private function_ `_FindTargetUidInArgs()`
- L415 _private function_ `_FindTargetUidInArgs(const First& first, const Rest&... rest)`
- L435 _private function_ `_GetArgContext(const Args&... args)`
- L489 _private function_ `_BuildExceptionMsg( const WrapperType& wrapper, const char* functionName, const Args&... args)`
- L514 _private function_ `_EmitResultConversionError( const WrapperType& wrapper, const char* functionName, const char* actualType, const Args&... args)`

#### class `internal::py::WrapperFactory`  
`class WrapperFactory`  
_L547-589_
- L552 _public function_ `operator()(CtorArgs... args) const`
- L575 _public function_ `MakeFactory(PXR_BOOST_PYTHON_NAMESPACE::object cls)`
- L583 _private function_ `WrapperFactory(PXR_BOOST_PYTHON_NAMESPACE::object cls) : _cls(cls)`
- L588 _private member_ `PXR_BOOST_PYTHON_NAMESPACE::object _cls;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace internal`
- L27 _namespace_ `namespace py` (scope `internal`)
- L31 _prototype_ `PostRuntimeError(const std::string& msg);` (scope `internal::py`)
- L34 _prototype_ `PostWarning(const std::string& msg);` (scope `internal::py`)
- L37 _prototype_ `GetPythonTraceback();` (scope `internal::py`)
- L49 _function_ `_SetErrorMessage(T& , const std::string& )` (scope `internal::py`)
- L55 _function_ `_SetErrorMessage<ManifestLoadResult>( ManifestLoadResult& result, const std::string& msg)` (scope `internal::py`)
- L68 _function_ `_SetErrorMessage<ManifestSaveResult>( ManifestSaveResult& result, const std::string& msg)` (scope `internal::py`)
- L128 _typedef_ `using ReturnType = decltype((wrapper->*defaultFn)(args...));` (scope `internal::py::VirtualDispatchHelper::CallPythonOverrideWithResultHandler`)
- L135 _function_ `` (scope `internal::py::VirtualDispatchHelper::CallPythonOverrideWithResultHandler`)
- L205 _typedef_ `using ReturnType = decltype((wrapper->*defaultFn)(args...));` (scope `internal::py::VirtualDispatchHelper::CallPythonOverride`)
- L595 _function_ `CreatePythonPluginObject(const RefPtrType& plugin)` (scope `internal::py`)

### `Plugins/Experimental/USDPregen/Source/USDPregenPy/Public/USDPregenPyModule.h` (Public)


#### class `FUSDPregenPyModule`  
`class FUSDPregenPyModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
