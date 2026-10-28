# Plugins / AndroidFileServer

- module root: `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServer`
- headers: 2; symbols: 13
- symbol kinds: class=2, enum=1, enumerator=4, namespace=1, prototype=5
- PrivateDependencyModuleNames: CoreUObject, Engine, Launch, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServer/Classes/AndroidFileServerBPLibrary.h` (Public)


#### enum `EAFSActiveType::Type`  
`enum Type : int`  
_L11-17_
- L13 _public enumerator_ `None = 0 UMETA(DisplayName = "None")`
- L14 _public enumerator_ `USBOnly = 1 UMETA(DisplayName = "USB only")`
- L15 _public enumerator_ `NetworkOnly = 2 UMETA(DisplayName = "Network only")`
- L16 _public enumerator_ `Combined = 3 UMETA(DisplayName = "USB and Network combined")`

#### class `UAndroidFileServerBPLibrary`  
`class UAndroidFileServerBPLibrary : public UBlueprintFunctionLibrary`  
_L21-36_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L27 _public prototype_ `static bool StartFileServer(bool bUSB = true, bool bNetwork = false, int32 Port = 57099);` — `UFUNCTION(BlueprintCallable, Category = "AndroidFileServer")` — Request startup of Android FileServer
- L31 _public prototype_ `static bool StopFileServer(bool bUSB = true, bool bNetwork = true);` — `UFUNCTION(BlueprintCallable, Category = "AndroidFileServer")` — Request termination of Android FileServer
- L35 _public prototype_ `static TEnumAsByte<EAFSActiveType::Type> IsFileServerRunning();` — `UFUNCTION(BlueprintCallable, Category = "AndroidFileServer")` — Check if Android FileServer is running

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EAFSActiveType`

### `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServer/Public/AndroidFileServer.h` (Public)


#### class `FAndroidFileServerModule`  
`class FAndroidFileServerModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
