# Plugins / AndroidFileServerEditor

- module root: `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServerEditor`
- headers: 2; symbols: 22
- symbol kinds: class=2, enum=1, enumerator=3, member=12, namespace=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, UnrealEd

### `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServerEditor/Public/AndroidFileServerEditor.h` (Public)


#### class `FAndroidFileServerEditorModule`  
`class FAndroidFileServerEditorModule : public IModuleInterface`  
_L8-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServerEditor/Public/AndroidFileServerRuntimeSettings.h` (Public)


#### enum `EAFSConnectionType::Type`  
`enum Type : int`  
_L14-19_
- L16 _public enumerator_ `USBOnly = 0 UMETA(DisplayName = "USB only")`
- L17 _public enumerator_ `NetworkOnly = 1 UMETA(DisplayName = "Network only")`
- L18 _public enumerator_ `Combined = 2 UMETA(DisplayName = "USB and Network combined")`

#### class `UAndroidFileServerRuntimeSettings`  
`class UAndroidFileServerRuntimeSettings : public UObject`  
_L24-79_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- L30 _private member_ `bool bEnablePlugin;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta = (DisplayName = "Use AndroidFileServer"))` — Enable Android FileServer for packaged builds and quick launch
- L34 _private member_ `bool bAllowNetworkConnection;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta = (EditCondition = "bEnablePlugin"))` — Allow FileServer connection using network
- L38 _private member_ `FString SecurityToken;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta = (EditCondition = "bEnablePlugin"))` — Optional security token required to start FileServer (leave empty to disable)
- L42 _private member_ `bool bIncludeInShipping;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta=(EditCondition = "bEnablePlugin"))` — Embed FileServer in Shipping builds
- L46 _private member_ `bool bAllowExternalStartInShipping;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta = (EditCondition = "bEnablePlugin && bIncludeInShipping"))` — Allow FileServer to be started in Shipping builds with UnrealAndroidFileTool
- L50 _private member_ `bool bCompileAFSProject;` — `UPROPERTY(EditAnywhere, config, Category = Packaging, Meta=(EditCondition = "bEnablePlugin"))` — Compile standalone AFS project
- L54 _private member_ `bool bUseCompression;` — `UPROPERTY(EditAnywhere, config, Category = Deployment, Meta=(EditCondition = "bEnablePlugin"))` — Enable compression during data transfer
- L58 _private member_ `bool bLogFiles;` — `UPROPERTY(EditAnywhere, config, Category = Deployment, Meta=(EditCondition = "bEnablePlugin"))` — Log files transferred
- L62 _private member_ `bool bReportStats;` — `UPROPERTY(EditAnywhere, config, Category = Deployment, Meta=(EditCondition = "bEnablePlugin"))` — Report transfer rate statistics
- L66 _private member_ `TEnumAsByte<EAFSConnectionType::Type> ConnectionType;` — `UPROPERTY(EditAnywhere, config, Category = Connection, Meta=(EditCondition = "bEnablePlugin"))` — How to connect to file server (USB cable, Network, or combined)
- L70 _private member_ `bool bUseManualIPAddress;` — `UPROPERTY(EditAnywhere, config, Category = Connection, Meta=(EditCondition = "ConnectionType == EAFSConnectionType::NetworkOnly || ConnectionType == EAFSConnectionType::Combined"), Meta=(DisplayName = "Use Manual IP Address?"))` — Use manual IP address instead of automatic query from device (only for single device deploys!)
- L74 _private member_ `FString ManualIPAddress;` — `UPROPERTY(EditAnywhere, config, Category = Connection, Meta=(EditCondition = "bUseManualIPAddress"), Meta=(DisplayName = "Manual IP Address"))` — IP address of device to use
- L78 _private prototype_ `virtual void PostInitProperties() override;` — UObject interface

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EAFSConnectionType`
