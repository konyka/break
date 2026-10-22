# Plugins / DMXFixtureActorInterface

- module root: `Plugins/VirtualProduction/DMX/DMXModularFeatures/Source/DMXFixtureActorInterface`
- headers: 1; symbols: 3
- symbol kinds: class=2, prototype=1
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/DMX/DMXModularFeatures/Source/DMXFixtureActorInterface/Public/DMXMVRFixtureActorInterface.h` (Public)


#### class `UDMXMVRFixtureActorInterface`  
`class UDMXMVRFixtureActorInterface : public UInterface`  
_L19-24_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`
- desc: When implemented in an actor, MVR will find the Actor and consider it when auto-selecting Fixtures. Note the Actor that implements this is required to have exactly one DMXComponent subobject. It is the DMX Component that will write its MVR UUID to the Actor's MetaData and make the Actor identified as an MVR Actor.

#### class `IDMXMVRFixtureActorInterface`  
`class IDMXMVRFixtureActorInterface`  
_L26-34_
- L33 _public prototype_ `void OnMVRGetSupportedDMXAttributes(TArray<FName>& OutAttributeNames, TArray<FName>& OutMatrixAttributeNames) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DMX", Meta = (DisplayName = "On MVR Get Supported DMX Attributes"))` — Should return the DMX Attributes the Actor supports
