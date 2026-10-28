# Plugins / AndroidPermission

- module root: `Plugins/Runtime/AndroidPermission/Source/AndroidPermission`
- headers: 3; symbols: 18
- symbol kinds: class=3, delegate=2, macro=2, member=2, prototype=9
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Slate, SlateCore
- PublicDependencyModuleNames: Core, Engine
- PublicIncludePathModuleNames: Launch

### `Plugins/Runtime/AndroidPermission/Source/AndroidPermission/Classes/AndroidPermissionCallbackProxy.h` (Public)


#### class `UAndroidPermissionCallbackProxy`  
`class UAndroidPermissionCallbackProxy : public UObject`  
_L13-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public member_ `FAndroidPermissionDynamicDelegate OnPermissionsGrantedDynamicDelegate;` — `UPROPERTY(BlueprintAssignable, Category="AndroidPermission")`
- L20 _public member_ `FAndroidPermissionDelegate OnPermissionsGrantedDelegate;`
- L22 _public prototype_ `static UAndroidPermissionCallbackProxy *GetInstance();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ANDROIDPERMISSION_API`
- L9 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAndroidPermissionDynamicDelegate, const TArray<FString>&, Permissions, const TArray<bool>&, GrantResults);`
- L9 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAndroidPermissionDynamicDelegate, const TArray<FString>&, Permissions, const TArray<bool>&, GrantResults);`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidPermissionDelegate, const TArray<FString>& , const TArray<bool>& );`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAndroidPermissionDelegate, const TArray<FString>& , const TArray<bool>& );`

### `Plugins/Runtime/AndroidPermission/Source/AndroidPermission/Classes/AndroidPermissionFunctionLibrary.h` (Public)


#### class `UAndroidPermissionFunctionLibrary`  
`class UAndroidPermissionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static bool CheckPermission(const FString& permission);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Check Android Permission"), Category="AndroidPermission")` — check if the permission is already granted
- L23 _public prototype_ `static UAndroidPermissionCallbackProxy* AcquirePermissions(const TArray<FString>& permissions);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request Android Permissions"), Category="AndroidPermission")` — try to acquire permissions and return a singleton callback proxy object containing OnPermissionsGranted delegate
- L27 _public prototype_ `static void Initialize();` — initialize java objects and cache them for further usage. called when the module is loaded

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANDROIDPERMISSION_API`

### `Plugins/Runtime/AndroidPermission/Source/AndroidPermission/Public/AndroidPermission.h` (Public)


#### class `FAndroidPermissionModule`  
`class FAndroidPermissionModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidPermission, Log, All);`
