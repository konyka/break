# Plugins / AvalancheRemoteControl

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl`
- headers: 5; symbols: 19
- symbol kinds: class=3, function=1, member=1, prototype=11, struct=3
- PrivateDependencyModuleNames: RemoteControlComponents, RemoteControlLogic, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RemoteControl

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl/Public/AvaRCControllerId.h` (Public)


#### struct `FAvaRCControllerId`  
`struct FAvaRCControllerId`  
_L13-27_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design RC Controller Id")`
- desc: Struct describing data to identify/find a Controller in a given preset
- L17 _public prototype_ `FAvaRCControllerId() = default;`
- L19 _public prototype_ `explicit FAvaRCControllerId(URCVirtualPropertyBase* InController);`
- L21 _public prototype_ `URCVirtualPropertyBase* FindController(URemoteControlPreset* InPreset) const;`
- L23 _public prototype_ `FText ToText() const;`
- L26 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Remote Control")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl/Public/AvaRCLibrary.h` (Public)


#### class `UAvaRCLibrary`  
`class UAvaRCLibrary : public UBlueprintFunctionLibrary`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `static TArray<AActor*> GetControlledActors(UObject* InWorldContextObject, URCVirtualPropertyBase* InController);` — `UFUNCTION(BlueprintCallable, Category="Remote Control", meta=(WorldContext="InWorldContextObject"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl/Public/AvaRemoteControlRebind.h` (Public)


#### struct `FAvaRemoteControlRebind`  
`struct FAvaRemoteControlRebind`  
_L10-24_
- L17 _public prototype_ `static void RebindUnboundEntities(URemoteControlPreset* InPreset, const ULevel* InLevel = nullptr);` — @brief Resolved the bindings and exposed entities, transient objects are allowed. @param InPreset Preset to rebind. @param InLevel Specify the level to constrain the binding resolution to. Will use the parent world if not specified.
- L23 _public prototype_ `static void ResolveAllFieldPathInfos(URemoteControlPreset* InPreset);` — Ensure all the Remote Control Fields have a properly resolved FieldPathInfo. This must be called after RebindUnboundEntities.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl/Public/AvaRemoteControlUtils.h` (Public)


#### struct `FAvaRemoteControlUtils`  
`struct FAvaRemoteControlUtils`  
_L10-34_
- L20 _public prototype_ `static bool RegisterRemoteControlPreset(URemoteControlPreset* InRemoteControlPreset, bool bInEnsureUniqueId);` — Register the given RemoteControlPreset in the RemoteControl module. Registered RemoteControlPreset are made accessible, by name, to the other systems, like the Web interface. @param InRemoteControlPreset Preset to register @param bInEnsureUniqueId The registered preset will be given a unique id if another preset instance has already been registered. @return whether registration was successful.
- L25 _public prototype_ `static void UnregisterRemoteControlPreset(URemoteControlPreset* InRemoteControlPreset);` — Unregister the given RemoteControlPreset from the RemoteControl module.
- L33 _public prototype_ `static URemoteControlPreset* FindEmbeddedPresetInLevel(ULevel* InLevel);` — Iterates the active Embedded Presets and finds the one that is within the given Level Note: this will not find presets that have not been registered, even if outered to the given Level. @param InLevel the level containing the preset @return the registered preset if found, null otherwise

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheRemoteControl/Public/IAvaRemoteControlInterface.h` (Public)


#### class `UAvaRemoteControlInterface`  
`class UAvaRemoteControlInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, meta=(DisplayName="Motion Design Remote Control Interface"))`
- inherits: `UInterface`
- desc: Interface for runtime remote control events.

#### class `IAvaRemoteControlInterface`  
`class IAvaRemoteControlInterface`  
_L17-29_
- L26 _public prototype_ `void OnValuesApplied();` — `UFUNCTION(BlueprintNativeEvent, Category = "Remote Control")` — Called when the remote control values are applied.
- L28 _public function_ `virtual void OnValuesApplied_Implementation()`
