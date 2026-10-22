# Plugins / TargetDeviceServicesScripting

- module root: `Plugins/Experimental/TargetDeviceServicesScripting/Source/TargetDeviceServicesScripting`
- headers: 1; symbols: 13
- symbol kinds: class=1, member=9, prototype=1, struct=2
- PrivateDependencyModuleNames: CoreUObject, TargetDeviceServices
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Experimental/TargetDeviceServicesScripting/Source/TargetDeviceServicesScripting/Public/TargetDeviceServicesBPFunctionLibrary.h` (Public)


#### struct `FDeviceSnapshot`  
`struct FDeviceSnapshot`  
_L13-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: The struct is designed to store device information
- L21 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's name.
- L25 _public member_ `FString HostName;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's hostname.
- L29 _public member_ `FString DeviceType;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's type.
- L33 _public member_ `FString ModelId;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's model identifier.
- L37 _public member_ `FString DeviceConnectionType;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's connection type.
- L41 _public member_ `FString DeviceId;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's identifier.
- L45 _public member_ `FString OperatingSystem;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's operating system name.
- L52 _public member_ `bool IsConnected = false;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores device's flag that is used to detect whether device is connected (true) or disconnected (false).

#### struct `FDeviceSnapshots`  
`struct FDeviceSnapshots`  
_L60-69_
- reflection: `USTRUCT(BlueprintType)`
- desc: The struct is a container class that stores instances of FDeviceSnapshot instances. It is a helper class to be used in blueprints as a value of TMap container.
- L68 _public member_ `TArray<FDeviceSnapshot> Entries;` — `UPROPERTY(BlueprintReadOnly, Category = "TargetDeviceServicesScripting")` — Stores array of device snapshots.

#### class `UTargetDeviceServicesBPFunctionLibrary`  
`class UTargetDeviceServicesBPFunctionLibrary : public UBlueprintFunctionLibrary`  
_L75-87_
- reflection: `UCLASS(meta = (ScriptName = "TargetDeviceServices"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: The class declares a set of functions to be exposed to blueprints.
- L86 _public prototype_ `static TMap<FString, FDeviceSnapshots> GetDeviceSnapshots();` — `UFUNCTION(BlueprintCallable, Category = "TargetDeviceServicesScripting")` — Fetches snapshots of devices that are available in the network. @return A dictionary of devices' informational snapshots that are grouped by device type (device type string is used as a key).
