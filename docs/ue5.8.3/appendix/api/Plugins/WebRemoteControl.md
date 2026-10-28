# Plugins / WebRemoteControl

- module root: `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl`
- headers: 17; symbols: 857
- symbol kinds: class=12, delegate=4, enum=3, enumerator=12, function=138, macro=1, member=309, namespace=8, prototype=271, struct=81, typedef=4, variable=14
- PrivateDependencyModuleNames: AssetRegistry, DeveloperSettings, Engine, HTTP, ImageWrapper, Networking, RemoteControl, RemoteControlCommon, RemoteControlLogic, RemoteControlUI, Settings, SharedSettingsWidgets, Slate, SlateCore, Sockets, SourceControl, UnrealEd, WebSocketNetworking
- PublicDependencyModuleNames: Core, CoreUObject, HTTPServer, Serialization

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlDefaultPreprocessors.h` (Private)


#### enum `UE::WebRemoteControl::EPreprocessorResult`  
`enum class EPreprocessorResult : uint8`  
_L33-37_
- desc: Indicates whether a request has been handled (OnComplete callback called) or if it just passed through the preprocessor.
- L35 _public enumerator_ `RequestPassthrough`
- L36 _public enumerator_ `RequestHandled`

#### struct `UE::WebRemoteControl::FPreprocessorResult`  
`struct FPreprocessorResult`  
_L49-80_
- desc: Result of a preprocessor. When failed, it will automatically respond to the client request. Usage: Deny a request: return FPreprocessorResult::Deny(TEXT("My preprocessor error message")); or let it through: return FPreprocessorResult::Passthrough();
- L52 _public function_ `static FPreprocessorResult Passthrough()` — Let request pass.
- L58 _public function_ `static FPreprocessorResult Deny(const FString& ErrorMessage)` — Deny request and respond with error message.
- L71 _public member_ `EPreprocessorResult Result = EPreprocessorResult::RequestPassthrough;` — Holds the preprocessor result.
- L73 _public member_ `TUniquePtr<FHttpServerResponse> OptionalResponse;` — If denied, holds the response to be sent to the client.
- L76 _private prototype_ `FPreprocessorResult() = default;`
- L77 _private function_ `FPreprocessorResult(EPreprocessorResult InResult, TUniquePtr<FHttpServerResponse> InOptionalResponse) : Result(InResult), OptionalResponse(MoveTemp(InOptionalResponse))`

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "WebRemoteControl"`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace WebRemoteControl` (scope `UE`)
- L82 _typedef_ `using FRCPreprocessorHandler = TFunction<FPreprocessorResult(const FHttpServerRequest& Request)>;` (scope `UE::WebRemoteControl`)
- L85 _prototype_ `FHttpRequestHandler MakeHttpRequestHandler(FRCPreprocessorHandler Handler);` (scope `UE::WebRemoteControl`) — Utility function to wrap a preprocessor handler to a http request handler than the HttpRouter can take.
- L89 _prototype_ `void SaveRemoteControlConfig();` (scope `UE::WebRemoteControl`) — Attempt saving the remote control config, checkouting it if needed.
- L92 _prototype_ `void AddIPToAllowlist(FString IPAddress);` (scope `UE::WebRemoteControl`) — Add IP to the list of IPs that should be let through by RC.
- L95 _prototype_ `void CreatePassphrase();` (scope `UE::WebRemoteControl`) — Prompts the user to create a passphrase.
- L98 _prototype_ `void DisableRemotePassphrases();` (scope `UE::WebRemoteControl`) — Disables remote passphrase enforcement by modifying a RC project setting.
- L102 _prototype_ `FPreprocessorResult RemotePassphraseEnforcementPreprocessor(const FHttpServerRequest& Request);` (scope `UE::WebRemoteControl`) — Notifies the editor if a client tries to access the RC server without a passphrase.
- L105 _prototype_ `FPreprocessorResult PassphrasePreprocessor(const FHttpServerRequest& Request);` (scope `UE::WebRemoteControl`) — Checks whether a request has a valid passphrase when passphrases are enabled for this editor.
- L111 _prototype_ `FPreprocessorResult IPValidationPreprocessor(const FHttpServerRequest& Request);` (scope `UE::WebRemoteControl`) — Checks whether an IP is in a valid range for making remote control requests. Also checks for a valid origin to block malicious requests from web browsers. Can be controlled using the Allowed Origin and AllowedIP remote control settings.

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlModels.h` (Private)


#### struct `FRCObjectDescription`  
`struct FRCObjectDescription`  
_L68-105_
- reflection: `USTRUCT()`
- desc: Short description of an unreal object.
- L72 _public prototype_ `FRCObjectDescription() = default;`
- L74 _public function_ `FRCObjectDescription(UObject* InObject)`
- L96 _public member_ `FString Name;` — `UPROPERTY()` — Name of the object.
- L100 _public member_ `FString Class;` — `UPROPERTY()` — Class of the object.
- L104 _public member_ `FString Path;` — `UPROPERTY()` — Path of the object.

#### struct `FRCPropertyDescription`  
`struct FRCPropertyDescription`  
_L108-236_
- reflection: `USTRUCT()`
- L112 _public prototype_ `FRCPropertyDescription() = default;`
- L114 _public function_ `FRCPropertyDescription(const FProperty* Property)`
- L207 _public member_ `FString Name;` — `UPROPERTY()` — Name of the exposed property
- L211 _public member_ `FText DisplayName;` — `UPROPERTY()` — Display name of the exposed property
- L215 _public member_ `FString Description;` — `UPROPERTY()` — Description of the exposed property
- L219 _public member_ `FString Type;` — `UPROPERTY()` — Type of the property value (If an array, this will be the content of the array)
- L223 _public member_ `FName TypePath;` — `UPROPERTY()` — Type of the property value (If an array, this will be the content of the array)
- L227 _public member_ `FString ContainerType;` — `UPROPERTY()` — Type of the container (TMap, TArray, CArray, TSet) or empty if none
- L231 _public member_ `FString KeyType;` — `UPROPERTY()` — Key type if container is a map
- L235 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY()` — Metadata for this exposed property

#### struct `FRCFunctionDescription`  
`struct FRCFunctionDescription`  
_L239-272_
- reflection: `USTRUCT()`
- L243 _public prototype_ `FRCFunctionDescription() = default;`
- L245 _public function_ `FRCFunctionDescription(const UFunction* Function) : Name(Function->GetName())`
- L263 _public member_ `FString Name;` — `UPROPERTY()` — Name of the function.
- L267 _public member_ `FString Description;` — `UPROPERTY()` — Description for the function.
- L271 _public member_ `TArray<FRCPropertyDescription> Arguments;` — `UPROPERTY()` — The function's arguments.

#### struct `FRCExposedPropertyDescription`  
`struct FRCExposedPropertyDescription`  
_L275-309_
- reflection: `USTRUCT()`
- L279 _public prototype_ `FRCExposedPropertyDescription() = default;`
- L281 _public function_ `FRCExposedPropertyDescription(const FRemoteControlProperty& RCProperty) : DisplayName(RCProperty.GetLabel())`
- L292 _public member_ `FName DisplayName;` — `UPROPERTY()` — The label displayed in the remote control panel for this exposed property.
- L296 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the exposed property.
- L300 _public member_ `FRCPropertyDescription UnderlyingProperty;` — `UPROPERTY()` — The underlying exposed property.
- L304 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY()` — Metadata specific to this exposed property.
- L308 _public member_ `TArray<FRCObjectDescription> OwnerObjects;` — `UPROPERTY()` — The objects that own the underlying property.

#### struct `FRCExposedFunctionDescription`  
`struct FRCExposedFunctionDescription`  
_L312-341_
- reflection: `USTRUCT()`
- L316 _public prototype_ `FRCExposedFunctionDescription() = default;`
- L318 _public function_ `FRCExposedFunctionDescription(const FRemoteControlFunction& Function) : DisplayName(Function.GetLabel()) , ID(Function.GetId().ToString()) , UnderlyingFunction(Function.GetFunction())`
- L328 _public member_ `FName DisplayName;` — `UPROPERTY()` — The label displayed in the remote control panel for this exposed property.
- L332 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the exposed function.
- L336 _public member_ `FRCFunctionDescription UnderlyingFunction;` — `UPROPERTY()` — The underlying exposed function.
- L340 _public member_ `TArray<FRCObjectDescription> OwnerObjects;` — `UPROPERTY()` — The objects that own the underlying function.

#### struct `FRCExposedActorDescription`  
`struct FRCExposedActorDescription`  
_L344-372_
- reflection: `USTRUCT()`
- L348 _public prototype_ `FRCExposedActorDescription() = default;`
- L350 _public function_ `FRCExposedActorDescription(const FRemoteControlActor& InExposedActor) : DisplayName(InExposedActor.GetLabel())`
- L363 _public member_ `FName DisplayName;` — `UPROPERTY()` — The label displayed in the remote control panel for this exposed actor.
- L367 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the exposed actor.
- L371 _public member_ `FRCObjectDescription UnderlyingActor;` — `UPROPERTY()` — The underlying exposed actor.

#### struct `FRCControllerDescription`  
`struct FRCControllerDescription`  
_L375-419_
- reflection: `USTRUCT()`
- L379 _public prototype_ `FRCControllerDescription() = default;`
- L381 _public function_ `FRCControllerDescription(const URCVirtualPropertyBase* InController)`
- L398 _public member_ `FName DisplayName;` — `UPROPERTY()` — The label displayed in the remote control panel for this controller.
- L402 _public member_ `FText Description;` — `UPROPERTY()` — Controller description.
- L406 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the controller.
- L410 _public member_ `FString Type;` — `UPROPERTY()` — Type of the Controller
- L414 _public member_ `FString Path;` — `UPROPERTY()` — Path of the Controller
- L418 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY()` — Metadata of the Controller. Initially Empty.

#### struct `FRCControllerModifiedDescription`  
`struct FRCControllerModifiedDescription`  
_L422-464_
- reflection: `USTRUCT()`
- L426 _public prototype_ `FRCControllerModifiedDescription () = default;`
- L428 _public function_ `FRCControllerModifiedDescription(const URemoteControlPreset* InPreset, const TArray<FGuid>& InModifiedControllers)`
- L445 _public member_ `TArray<FRCControllerDescription> Controllers;` — `UPROPERTY()` — The list of modified RC controllers.
- L448 _public member_ `TArray<FString> ChangedValues;` — `UPROPERTY()`
- L451 _private function_ `void AddModifiedController(const URemoteControlPreset* InPreset, const FGuid& InControllerId)`

#### struct `FRCPresetLayoutGroupDescription`  
`struct FRCPresetLayoutGroupDescription`  
_L467-532_
- reflection: `USTRUCT()`
- L471 _public prototype_ `FRCPresetLayoutGroupDescription() = default;`
- L473 _public function_ `FRCPresetLayoutGroupDescription(const URemoteControlPreset* Preset, const FRemoteControlPresetGroup& Group) : Name(Group.Name)`
- L483 _public function_ `FRCPresetLayoutGroupDescription(const URemoteControlPreset* Preset, const FRemoteControlPresetGroup& Group, const TArray<FGuid>& EntityIds) : Name(Group.Name)`
- L495 _public member_ `FName Name;` — `UPROPERTY()`
- L498 _public member_ `TArray<FRCExposedPropertyDescription> ExposedProperties;` — `UPROPERTY()`
- L501 _public member_ `TArray<FRCExposedFunctionDescription> ExposedFunctions;` — `UPROPERTY()`
- L504 _public member_ `TArray<FRCExposedActorDescription> ExposedActors;` — `UPROPERTY()`
- L508 _private function_ `void AddExposedField(const URemoteControlPreset* Preset, const FGuid& EntityId)` — Add an exposed field to this group description.

#### struct `FRCPresetModifiedEntitiesDescription`  
`struct FRCPresetModifiedEntitiesDescription`  
_L540-594_
- reflection: `USTRUCT()`
- desc: Holds lists of modified RC entities. @Note that this does not mean the underlying property/function/actor was modified, but rather that the entity structure itself was modified in some way.
- L544 _public prototype_ `FRCPresetModifiedEntitiesDescription() = default;`
- L546 _public function_ `FRCPresetModifiedEntitiesDescription(const URemoteControlPreset* Preset, const TArray<FGuid>& EntityIds)`
- L558 _public member_ `TArray<FRCExposedPropertyDescription> ModifiedRCProperties;` — `UPROPERTY()` — The list of modified RC properties.
- L562 _public member_ `TArray<FRCExposedFunctionDescription> ModifiedRCFunctions;` — `UPROPERTY()` — The list of modified RC functions.
- L566 _public member_ `TArray<FRCExposedActorDescription> ModifiedRCActors;` — `UPROPERTY()` — The list of modified RC actors.
- L570 _private function_ `void AddModifiedEntity(const URemoteControlPreset* Preset, const FGuid& EntityId)` — Add an exposed field to this group description.

#### struct `FRCPresetDescription`  
`struct FRCPresetDescription`  
_L597-644_
- reflection: `USTRUCT()`
- L601 _public prototype_ `FRCPresetDescription() = default;`
- L603 _public function_ `FRCPresetDescription(const URemoteControlPreset* Preset)`
- L619 _public member_ `FString Name;` — `UPROPERTY()` — Name of the preset.
- L625 _public member_ `FString Path;` — `UPROPERTY()` — Name of the preset.
- L631 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the preset, can be used to make requests to the API.
- L637 _public member_ `TArray<FRCPresetLayoutGroupDescription> Groups;` — `UPROPERTY()` — The groups containing exposed entities.
- L643 _public member_ `TArray<FRCControllerDescription> Controllers;` — `UPROPERTY()` — The controllers held by the Preset (no groups)

#### struct `FRCShortPresetDescription`  
`struct FRCShortPresetDescription`  
_L647-708_
- reflection: `USTRUCT()`
- L651 _public prototype_ `FRCShortPresetDescription() = default;`
- L653 _public function_ `FRCShortPresetDescription(const FAssetData& PresetAsset)`
- L671 _public function_ `FRCShortPresetDescription(const URemoteControlPreset* InPreset)`
- L681 _public function_ `FRCShortPresetDescription(const TWeakObjectPtr<URemoteControlPreset> InPreset)`
- L695 _public member_ `FName Name;` — `UPROPERTY()` — Name of the preset.
- L701 _public member_ `FString ID;` — `UPROPERTY()` — Unique identifier for the preset, can be used to make requests to the API.
- L707 _public member_ `FName Path;` — `UPROPERTY()` — Object path of the preset.

#### struct `FRCAssetDescription`  
`struct FRCAssetDescription`  
_L711-735_
- reflection: `USTRUCT()`
- L715 _public prototype_ `FRCAssetDescription() = default;`
- L716 _public function_ `FRCAssetDescription(const FAssetData& InAsset) : Name(InAsset.AssetName) , Class(*InAsset.AssetClassPath.ToString()) , Path(*InAsset.GetObjectPathString())`
- L725 _public member_ `FName Name;` — `UPROPERTY()`
- L728 _public member_ `FName Class;` — `UPROPERTY()`
- L731 _public member_ `FName Path;` — `UPROPERTY()`
- L734 _public member_ `TMap<FName, FString> Metadata;` — `UPROPERTY()`

#### struct `FRCPresetFieldRenamed`  
`struct FRCPresetFieldRenamed`  
_L738-755_
- reflection: `USTRUCT()`
- L742 _public prototype_ `FRCPresetFieldRenamed() = default;`
- L744 _public function_ `FRCPresetFieldRenamed(const TTuple<FName, FName>& RenamedField) : OldFieldLabel(RenamedField.Key) , NewFieldLabel(RenamedField.Value)`
- L751 _public member_ `FName OldFieldLabel;` — `UPROPERTY()`
- L754 _public member_ `FName NewFieldLabel;` — `UPROPERTY()`

#### struct `FRCAssetFilter`  
`struct FRCAssetFilter`  
_L758-826_
- reflection: `USTRUCT()`
- L762 _public prototype_ `FRCAssetFilter() = default;`
- L764 _public function_ `FARFilter ToARFilter() const`
- L797 _public member_ `TArray<FName> PackageNames;` — `UPROPERTY()` — The filter component for package names
- L801 _public member_ `TArray<FName> PackagePaths;` — `UPROPERTY()` — The filter component for package paths
- L805 _public member_ `TArray<FName> ClassNames;` — `UPROPERTY()` — The filter component for class names. Instances of the specified classes, but not subclasses (by default), will be included. Derived classes will be included only if bRecursiveClasses is true.
- L809 _public member_ `TSet<FName> RecursiveClassesExclusionSet;` — `UPROPERTY()` — Only if bRecursiveClasses is true, the results will exclude classes (and subclasses) in this list
- L813 _public member_ `TArray<FName> NativeParentClasses;` — `UPROPERTY()` — Only if EnableBlueprintNativeClassFiltering is true, resulting asset will be filtered for dependants of classes in this list.
- L817 _public member_ `bool RecursiveClasses = false;` — `UPROPERTY()` — If true, subclasses of ClassNames will also be included and RecursiveClassesExclusionSet will be excluded.
- L821 _public member_ `bool RecursivePaths = false;` — `UPROPERTY()` — If true, PackagePath components will be recursive
- L825 _public member_ `bool EnableBlueprintNativeClassFiltering = false;` — `UPROPERTY()` — When dealing with blueprint classes, you might want to filter for a base class which can't be picked by asset registry if you derive from a blueprint class

#### struct `FRCActorDescription`  
`struct FRCActorDescription`  
_L832-856_
- reflection: `USTRUCT()`
- desc: A description of an actor that can both uniquely identify it and provide a user-friendly name.
- L836 _public prototype_ `FRCActorDescription() = default;`
- L838 _public function_ `FRCActorDescription(const AActor* InActor) : Name(InActor->GetActorNameOrLabel()) , Path(InActor->GetPathName())`
- L844 _public function_ `inline bool operator==(const FRCActorDescription& Other) const`
- L851 _public member_ `FString Name;` — `UPROPERTY()` — A user-friendly name for the actor.
- L855 _public member_ `FString Path;` — `UPROPERTY()` — The path to the actor.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace RemoteControlModels`
- L19 _variable_ `static FName Name_UIMin("UIM` (scope `RemoteControlModels`) — Names used to sanitize property/function metadata
- L20 _variable_ `static FName Name_UIMax("UIM` (scope `RemoteControlModels`)
- L21 _variable_ `static FName Name_ClampMin("Cla` (scope `RemoteControlModels`)
- L22 _variable_ `static FName Name_ClampMax("Cla` (scope `RemoteControlModels`)
- L23 _variable_ `static FName Name_ToolTip("Too` (scope `RemoteControlModels`)
- L24 _variable_ `static FName Name_EnumValues("Enu` (scope `RemoteControlModels`)
- L27 _variable_ `static FName NAME_FiBData("FiB` (scope `RemoteControlModels`) — Names used to sanitize asset metadata
- L28 _variable_ `static FName NAME_ClassFlags("Cla` (scope `RemoteControlModels`)
- L29 _variable_ `static FName NAME_AssetImportData("Ass` (scope `RemoteControlModels`)
- L31 _function_ `static TMap<FName, FString> SanitizeMetadata(const TMap<FName, FString>& InMetadata)` (scope `RemoteControlModels`)
- L36 _function_ `` (scope `RemoteControlModels::SanitizeMetadata`)
- L44 _function_ `Algo::TransformIf(InMetadata, OutMetadata, IsValid, [](const TTuple<FName, FString>& InTuple) { return InTuple; });` (scope `RemoteControlModels::SanitizeMetadata`)
- L48 _function_ `static TMap<FName, FString> SanitizeAssetMetadata(const FAssetDataTagMap& InAssetMetadata)` (scope `RemoteControlModels`)
- L53 _function_ `` (scope `RemoteControlModels::SanitizeAssetMetadata`)
- L59 _function_ `Algo::TransformIf(InAssetMetadata, OutMetadata, IsValid, [](const TTuple<FName, FString>& InTuple) { return InTuple; });` (scope `RemoteControlModels::SanitizeAssetMetadata`)
- L611 _function_ `Algo::Transform(Preset->Layout.GetGroups(), Groups, [Preset](const FRemoteControlPresetGroup& Group) { return FRCPresetLayoutGroupDescription{ Preset, Group }; });` (scope `FRCPresetDescription::FRCPresetDescription`)
- L612 _function_ `Algo::Transform(Preset->GetControllers(), Controllers, [Preset](const URCVirtualPropertyBase* Controller){ return FRCControllerDescription{ Controller };});` (scope `FRCPresetDescription::FRCPresetDescription`)
- L766 _function_ `auto ToAssetPath = [](FName InClassName)` (scope `FRCAssetFilter::ToARFilter`)

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlReflectionUtils.h` (Private)


#### struct `FWebRCGenerateStructArgs`  
`struct FWebRCGenerateStructArgs`  
_L14-27_
- L17 _public member_ `TArray<FName> StringProperties;` — String properties.
- L20 _public member_ `TArray<TPair<FName, UScriptStruct*>> StructProperties;` — Struct properties.
- L23 _public member_ `TArray<TPair<FName, FProperty*>> GenericProperties;` — Properties with an unknown type at compile time.
- L26 _public member_ `TArray<TPair<FName, UScriptStruct*>> ArrayProperties;` — List of array properties and the type they should hold.

#### class `UWebRCStructRegistry`  
`class UWebRCStructRegistry : public UEngineSubsystem`  
_L31-52_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: A subsystem to provide and cache dynamically created ustructs.
- L42 _public prototype_ `UScriptStruct* GenerateStruct(FName StructureName, const FWebRCGenerateStructArgs& Args);` — Generates a struct based on provided arguments. @param StructureName The name of the structure to generate. @param Args the properties that should populate the structure. @return The generated structure.
- L46 _private prototype_ `UScriptStruct* GenerateStructInternal(FName StructureName, const FWebRCGenerateStructArgs& Args);` — Creates a new struct based on provided arguments.
- L51 _private member_ `TMap<FName, TObjectPtr<UScriptStruct>> CachedStructs;` — `UPROPERTY(Transient)` — Map of cached structs.

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L56 _namespace_ `namespace WebRCReflectionUtils` (scope `UE`)
- L64 _prototype_ `UScriptStruct* GenerateStruct(FName StructureName, const FWebRCGenerateStructArgs& Args);` (scope `UE::WebRCReflectionUtils`) — Generates a struct based on provided arguments. @param StructureName The name of the structure to generate. @param Args the properties that should populate the structure. @return The generated structure.
- L72 _prototype_ `void SetStringPropertyValue(FName PropertyName, const FStructOnScope& TargetStruct, const FString& Value);` (scope `UE::WebRCReflectionUtils`) — Set a string property value in a provided struct on scope. @param PropertyName the name of the property to set. @param TargetStruct the structure that contains the property to modify. @param Value the new property value.
- L80 _prototype_ `void CopyPropertyValue(FName PropertyName, const FStructOnScope& TargetStruct, const FRCObjectReference& SourceObject);` (scope `UE::WebRCReflectionUtils`) — Copy a property value from an object to a struct on scope. @param PropertyName the name of the property to copy. @param TargetStruct the structure that contains the property to overwrite. @param SourceObject the object to copy the property from.
- L88 _prototype_ `void SetStructArrayPropertyValue(FName PropertyName, const FStructOnScope& TargetStruct, const TArray<FStructOnScope>& ArrayElements);` (scope `UE::WebRCReflectionUtils`) — Sets an array of structures in a struct on scope. @param PropertyName the name of the property to set. @param TargetStruct the structure that contains the property to modify. @param ArrayElements the array that should be copied into the target structure.
- L97 _prototype_ `void SetStructPropertyValue(FName PropertyName, const FStructOnScope& TargetStruct, const UScriptStruct* Struct, void* StructData);` (scope `UE::WebRCReflectionUtils`) — Sets a struct property in the target struct. @param PropertyName the name of the property to set. @param TargetStruct the structure that contains the property to modify. @param Struct the type of the structure to set. @param StructData the data that should be copied into the target structure.

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlRequest.h` (Private)


#### struct `FRCRequestWrapper`  
`struct FRCRequestWrapper : public FRCRequest`  
_L12-35_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- L16 _public function_ `FRCRequestWrapper() : RequestId(-1)`
- L25 _public function_ `static FString BodyLabel()` — Get the label for the parameters struct.
- L28 _public member_ `FString URL;` — `UPROPERTY()`
- L31 _public member_ `FName Verb;` — `UPROPERTY()`
- L34 _public member_ `int32 RequestId;` — `UPROPERTY()`

#### struct `FRCBatchRequest`  
`struct FRCBatchRequest : public FRCRequest`  
_L41-50_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request that wraps multiple requests..
- L49 _public member_ `TArray<FRCRequestWrapper> Requests;` — `UPROPERTY()` — The list of batched requests.

#### enum `ERemoteControlEvent`  
`enum class ERemoteControlEvent : uint8`  
_L53-58_
- reflection: `UENUM()`
- L55 _public enumerator_ `PreObjectPropertyChanged = 0`
- L56 _public enumerator_ `ObjectPropertyChanged`
- L57 _public enumerator_ `EventCount`

#### struct `FRemoteControlObjectEventHookRequest`  
`struct FRemoteControlObjectEventHookRequest : public FRCRequest`  
_L64-89_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to create an event hook.
- L68 _public function_ `FRemoteControlObjectEventHookRequest() : EventType(ERemoteControlEvent::EventCount)`
- L76 _public member_ `ERemoteControlEvent EventType;` — `UPROPERTY()` — What type of event should be listened to.
- L82 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The path of the target object.
- L88 _public member_ `FString PropertyName;` — `UPROPERTY()` — The name of the property to watch for changes.

#### struct `FRCCallRequest`  
`struct FRCCallRequest : public FRCRequest`  
_L96-127_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to call a function
- L100 _public function_ `FRCCallRequest()`
- L108 _public function_ `static FString ParametersLabel()` — Get the label for the parameters struct.
- L114 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The path of the target object.
- L120 _public member_ `FString FunctionName;` — `UPROPERTY()` — The name of the function to call.
- L126 _public member_ `bool GenerateTransaction = false;` — `UPROPERTY()` — Whether a transaction should be created for the call.

#### struct `FRCObjectRequest`  
`struct FRCObjectRequest : public FRCRequest`  
_L133-210_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to access an object
- L137 _public function_ `FRCObjectRequest()`
- L145 _public function_ `static FString PropertyValueLabel()` — Get the label for the property value struct.
- L150 _public function_ `ERCAccess GetAccessValue() const` — Get whether the property should be writen or read and if a transaction should be created.
- L178 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The path of the target object.
- L184 _public member_ `FString PropertyName;` — `UPROPERTY()` — The property to read or modify.
- L190 _public member_ `bool ResetToDefault = false;` — `UPROPERTY()` — Whether the property should be reset to default.
- L196 _public member_ `bool GenerateTransaction = false;` — `UPROPERTY()` — Whether a transaction should be created for the call.
- L202 _public member_ `ERCModifyOperation Operation = ERCModifyOperation::EQUAL;` — `UPROPERTY()` — Which type of operation should be performed if this is modifying a property.
- L209 _private member_ `ERCAccess Access = ERCAccess::NO_ACCESS;` — `UPROPERTY()` — Indicates if the property should be read or written to.

#### struct `FRCPresetSetPropertyRequest`  
`struct FRCPresetSetPropertyRequest : public FRCRequest`  
_L216-245_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to set a property on a preset
- L220 _public function_ `FRCPresetSetPropertyRequest()`
- L228 _public function_ `static FString PropertyValueLabel()` — Get the label for the PropertyValue struct.
- L235 _public member_ `ERCModifyOperation Operation = ERCModifyOperation::EQUAL;` — `UPROPERTY()` — Which type of operation should be performed on the value of the property. This will be ignored if ResetToDefault is true.
- L241 _public member_ `bool GenerateTransaction = false;` — `UPROPERTY()` — Whether a transaction should be created for the call.
- L244 _public member_ `bool ResetToDefault = false;` — `UPROPERTY()`

#### struct `FRCPresetCallRequest`  
`struct FRCPresetCallRequest : public FRCRequest`  
_L251-270_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to call a function on a preset
- L255 _public function_ `FRCPresetCallRequest()`
- L263 _public function_ `static FString ParametersLabel()` — Get the label for the parameters struct.
- L269 _public member_ `bool GenerateTransaction = false;` — `UPROPERTY()` — Whether a transaction should be created for the call.

#### struct `FRCPresetExposePropertyRequest`  
`struct FRCPresetExposePropertyRequest : public FRCRequest`  
_L276-309_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to expose a property on a preset
- L284 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The path of the target object.
- L290 _public member_ `FString PropertyName;` — `UPROPERTY()` — The property to expose.
- L296 _public member_ `FString Label;` — `UPROPERTY()` — The label to give the new exposed property (optional).
- L302 _public member_ `FString GroupName;` — `UPROPERTY()` — The name of the group in which to place the new exposed property (optional).
- L308 _public member_ `bool EnableEditCondition = true;` — `UPROPERTY()` — Whether to automatically enable the edit condition for the exposed property.

#### struct `FDescribeObjectRequest`  
`struct FDescribeObjectRequest: public FRCRequest`  
_L315-328_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to describe an object using its path.
- L319 _public function_ `FDescribeObjectRequest()`
- L327 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The target object's path.

#### struct `FSearchAssetRequest`  
`struct FSearchAssetRequest : public FRCRequest`  
_L334-360_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to search for an asset.
- L338 _public function_ `FSearchAssetRequest() : Limit(100)`
- L347 _public member_ `FString Query;` — `UPROPERTY()` — The search query which will be compared with the asset names.
- L353 _public member_ `FRCAssetFilter Filter;` — `UPROPERTY()` — The filter applied to this search.
- L359 _public member_ `int32 Limit;` — `UPROPERTY()` — The maximum number of search results returned.

#### struct `FSearchActorRequest`  
`struct FSearchActorRequest : public FRCRequest`  
_L366-392_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to search for an actor.
- L370 _public function_ `FSearchActorRequest() : Limit(100)`
- L379 _public member_ `FString Query;` — `UPROPERTY()` — The search query.
- L385 _public member_ `FString Class;` — `UPROPERTY()` — The target actor's class.
- L391 _public member_ `int32 Limit;` — `UPROPERTY()` — The maximum number of search results returned.

#### struct `FSearchObjectRequest`  
`struct FSearchObjectRequest : public FRCRequest`  
_L398-430_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to search for an asset.
- L402 _public function_ `FSearchObjectRequest() : Limit(100)`
- L411 _public member_ `FString Query;` — `UPROPERTY()` — The search query.
- L417 _public member_ `FString Class;` — `UPROPERTY()` — The target object's class.
- L423 _public member_ `FString Outer;` — `UPROPERTY()` — The search target's outer object.
- L429 _public member_ `int32 Limit;` — `UPROPERTY()` — The maximum number of search results returned.

#### struct `FSetPresetMetadataRequest`  
`struct FSetPresetMetadataRequest : public FRCRequest`  
_L437-448_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to set a metadata field.
- L441 _public prototype_ `FSetPresetMetadataRequest() = default;`
- L447 _public member_ `FString Value;` — `UPROPERTY()` — The new value for the metadata field.

#### struct `FSetEntityMetadataRequest`  
`struct FSetEntityMetadataRequest : public FRCRequest`  
_L454-465_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to set a metadata field.
- L458 _public prototype_ `FSetEntityMetadataRequest() = default;`
- L464 _public member_ `FString Value;` — `UPROPERTY()` — The new value for the metadata field.

#### struct `FSetEntityLabelRequest`  
`struct FSetEntityLabelRequest : public FRCRequest`  
_L471-480_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to set an entity's label.
- L479 _public member_ `FString NewLabel;` — `UPROPERTY()` — The new label to assign.

#### struct `FGetObjectThumbnailRequest`  
`struct FGetObjectThumbnailRequest : public FRCRequest`  
_L486-497_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request to get an asset's thumbnail.
- L490 _public prototype_ `FGetObjectThumbnailRequest() = default;`
- L496 _public member_ `FString ObjectPath;` — `UPROPERTY()` — The target object's path.

#### struct `FRCWebSocketRequest`  
`struct FRCWebSocketRequest : public FRCRequest`  
_L503-534_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made for web socket.
- L507 _public function_ `FRCWebSocketRequest()`
- L515 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L521 _public member_ `FString MessageName;` — `UPROPERTY()` — Name of the websocket message.
- L527 _public member_ `int32 Id = INDEX_NONE;` — `UPROPERTY()` — (Optional) Id of the incoming message, used to identify a deferred response to the clients.
- L533 _public member_ `FString ForwardedFor;` — `UPROPERTY()` — (Optional) If the request was forwared for a remote client, this will contain the forwarded IP.

#### struct `FRCWebSocketBatchRequest`  
`struct FRCWebSocketBatchRequest : public FRCRequest`  
_L540-549_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request that wraps multiple requests..
- L548 _public member_ `TArray<FRCWebSocketRequest> Requests;` — `UPROPERTY()` — The list of batched requests.

#### struct `FRCWebSocketPresetRegisterBody`  
`struct FRCWebSocketPresetRegisterBody : public FRCRequest`  
_L555-578_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to register for events about a given preset.
- L559 _public function_ `FRCWebSocketPresetRegisterBody()`
- L567 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L573 _public member_ `FString PresetName;` — `UPROPERTY()` — Name of the preset its registering.
- L577 _public member_ `bool IgnoreRemoteChanges = false;` — `UPROPERTY()` — Whether changes to properties triggered remotely should fire an event.

#### struct `FRCWebSocketTransientPresetAutoDestroyBody`  
`struct FRCWebSocketTransientPresetAutoDestroyBody : public FRCRequest`  
_L584-603_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to automatically destroy a transient preset when the calling client disconnects.
- L588 _public function_ `FRCWebSocketTransientPresetAutoDestroyBody()`
- L596 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L602 _public member_ `FString PresetName;` — `UPROPERTY()` — Name of the transient preset to mark for automatic destruction.

#### struct `FRCWebSocketActorRegisterBody`  
`struct FRCWebSocketActorRegisterBody : public FRCRequest`  
_L609-628_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to register for spawn/destroy events about a given actor type.
- L613 _public function_ `FRCWebSocketActorRegisterBody()`
- L621 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L627 _public member_ `FName ClassName;` — `UPROPERTY()` — Name of the actor class to register for.

#### struct `FRCWebSocketPresetSetPropertyBody`  
`struct FRCWebSocketPresetSetPropertyBody : public FRCRequest`  
_L634-694_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to modify a property exposed in a preset.
- L638 _public function_ `FRCWebSocketPresetSetPropertyBody()`
- L646 _public function_ `static FString PropertyValueLabel()` — Get the label for the PropertyValue struct.
- L652 _public member_ `FName PresetName;` — `UPROPERTY()` — The name of the remote control preset to which the property belongs.
- L658 _public member_ `FName PropertyLabel;` — `UPROPERTY()` — The label of the property to modify.
- L665 _public member_ `ERCModifyOperation Operation = ERCModifyOperation::EQUAL;` — `UPROPERTY()` — Which type of operation should be performed on the value of the property. This will be ignored if ResetToDefault is true.
- L674 _public member_ `ERCTransactionMode TransactionMode = ERCTransactionMode::NONE;` — `UPROPERTY()` — How to handle generating transactions for this property change. If NONE, don't generate a transaction immediately. If AUTOMATIC, let the Remote Control system automatically start and end the transaction after enough time passes. If MANUAL, TransactionId must also be set and the changes will only be applied if that transaction is still active.
- L680 _public member_ `int32 TransactionId = -1;` — `UPROPERTY()` — The ID of the transaction with which to associate these changes. Must be provided if TransactionMode is Manual.
- L686 _public member_ `bool ResetToDefault = false;` — `UPROPERTY()` — If true, ignore the other parameters and just reset the property to its default value.
- L693 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The sequence number of this change. The highest sequence number received from this client will be sent back to the client in future PresetFieldsChanged events.

#### struct `FRCWebSocketCallBody`  
`struct FRCWebSocketCallBody : public FRCCallRequest`  
_L700-731_
- reflection: `USTRUCT()`
- inherits: `FRCCallRequest`
- desc: Holds a request made via websocket to call an exposed function on an object.
- L704 _public function_ `FRCWebSocketCallBody() : FRCCallRequest()`
- L717 _public member_ `ERCTransactionMode TransactionMode = ERCTransactionMode::NONE;` — `UPROPERTY()` — How to handle generating transactions for this property change. If NONE, don't generate a transaction immediately. If AUTOMATIC, let the Remote Control system automatically start and end the transaction after enough time passes. If MANUAL, TransactionId must also be set and the changes will only be applied if that transaction is still active. If bGenerateTransaction is true, this value will be treated as if it was AUTOMATIC.
- L723 _public member_ `int32 TransactionId = -1;` — `UPROPERTY()` — The ID of the transaction with which to associate these changes. Must be provided if TransactionMode is Manual.
- L730 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The sequence number of this change. The highest sequence number received from this client will be sent back to the client in future PresetFieldsChanged events.

#### struct `FRCWebSocketTransactionStartBody`  
`struct FRCWebSocketTransactionStartBody : public FRCRequest`  
_L737-762_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to start a transaction.
- L741 _public function_ `FRCWebSocketTransactionStartBody()`
- L749 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L755 _public member_ `FString Description;` — `UPROPERTY()` — The description of the transaction.
- L761 _public member_ `int32 TransactionId = -1;` — `UPROPERTY()` — The ID that will be used to refer to the transaction in future messages.

#### struct `FRCWebSocketTransactionEndBody`  
`struct FRCWebSocketTransactionEndBody : public FRCRequest`  
_L769-788_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to end a transaction.
- L773 _public function_ `FRCWebSocketTransactionEndBody()`
- L781 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L787 _public member_ `int32 TransactionId = -1;` — `UPROPERTY()` — The ID of the transaction. If this doesn't match the current editor transaction, it won't be ended.

#### struct `FRCWebSocketCompressionChangeBody`  
`struct FRCWebSocketCompressionChangeBody : public FRCRequest`  
_L794-813_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Holds a request made via websocket to change the compression mode.
- L798 _public function_ `FRCWebSocketCompressionChangeBody()`
- L806 _public function_ `static FString ParametersFieldLabel()` — Get the label for the property value struct.
- L812 _public member_ `ERCWebSocketCompressionMode Mode = ERCWebSocketCompressionMode::NONE;` — `UPROPERTY()` — The compression mode to use.

#### struct `FRCPresetSetControllerRequest`  
`struct FRCPresetSetControllerRequest : public FRCRequest`  
_L819-840_
- reflection: `USTRUCT()`
- inherits: `FRCRequest`
- desc: Struct representation of SetPresetController HTTP request
- L823 _public function_ `FRCPresetSetControllerRequest()`
- L831 _public function_ `static FString PropertyValueLabel()` — Get the label for the PropertyValue struct.
- L839 _public member_ `FString ControllerName;` — `UPROPERTY()` — The name of the Controller being set (for a given Remote Control Preset asset)

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlResponse.h` (Private)


#### struct `FAPIInfoResponse`  
`struct FAPIInfoResponse`  
_L16-43_
- reflection: `USTRUCT()`
- L20 _public prototype_ `FAPIInfoResponse() = default;`
- L22 _public function_ `FAPIInfoResponse(const TArray<FRemoteControlRoute>& InRoutes, bool bInPackaged, URemoteControlPreset* InActivePreset) : IsPackaged(bInPackaged) , ActivePreset(InActivePreset)`
- L33 _private member_ `bool IsPackaged = false;` — Whether this is a packaged build or not.
- L39 _private member_ `TArray<FRemoteControlRouteDescription> HttpRoutes;` — `UPROPERTY()` — Descriptions for all the routes that make up the remote control API.
- L42 _private member_ `FRCShortPresetDescription ActivePreset;` — `UPROPERTY()`

#### struct `FListPresetsResponse`  
`struct FListPresetsResponse`  
_L46-63_
- reflection: `USTRUCT()`
- L50 _public prototype_ `FListPresetsResponse() = default;`
- L52 _public function_ `FListPresetsResponse(const TArray<FAssetData>& InPresets, const TArray<TWeakObjectPtr<URemoteControlPreset>> InEmbeddedPresets)`
- L62 _public member_ `TArray<FRCShortPresetDescription> Presets;` — `UPROPERTY()` — The list of available remote control presets.

#### struct `FGetPresetResponse`  
`struct FGetPresetResponse`  
_L66-78_
- reflection: `USTRUCT()`
- L70 _public prototype_ `FGetPresetResponse() = default;`
- L72 _public function_ `FGetPresetResponse(const URemoteControlPreset* InPreset) : Preset(InPreset)`
- L77 _public member_ `FRCPresetDescription Preset;` — `UPROPERTY()`

#### struct `FCheckPassphraseResponse`  
`struct FCheckPassphraseResponse`  
_L81-93_
- reflection: `USTRUCT()`
- L85 _public prototype_ `FCheckPassphraseResponse() = default;`
- L87 _public function_ `FCheckPassphraseResponse(bool bInKeyCorrect) : keyCorrect(bInKeyCorrect)`
- L92 _public member_ `bool keyCorrect = false;` — `UPROPERTY()`

#### struct `FDescribeObjectResponse`  
`struct FDescribeObjectResponse`  
_L96-134_
- reflection: `USTRUCT()`
- L100 _public prototype_ `FDescribeObjectResponse() = default;`
- L102 _public function_ `FDescribeObjectResponse(UObject* Object) : Name(Object->GetName()) , Class(Object->GetClass())`
- L124 _public member_ `FString Name;` — `UPROPERTY()`
- L127 _public member_ `TObjectPtr<UClass> Class = nullptr;` — `UPROPERTY()`
- L130 _public member_ `TArray<FRCPropertyDescription> Properties;` — `UPROPERTY()`
- L133 _public member_ `TArray<FRCFunctionDescription> Functions;` — `UPROPERTY()`

#### struct `FSearchAssetResponse`  
`struct FSearchAssetResponse`  
_L138-151_
- reflection: `USTRUCT()`
- L142 _public prototype_ `FSearchAssetResponse() = default;`
- L144 _public function_ `FSearchAssetResponse(const TArray<FAssetData>& InAssets)`
- L150 _public member_ `TArray<FRCAssetDescription> Assets;` — `UPROPERTY()`

#### struct `FSearchActorResponse`  
`struct FSearchActorResponse`  
_L155-168_
- reflection: `USTRUCT()`
- L159 _public prototype_ `FSearchActorResponse() = default;`
- L161 _public function_ `FSearchActorResponse(const TArray<AActor*>& InActors)`
- L167 _public member_ `TArray<FRCObjectDescription> Actors;` — `UPROPERTY()`

#### struct `FGetMetadataFieldResponse`  
`struct FGetMetadataFieldResponse`  
_L171-184_
- reflection: `USTRUCT()`
- L175 _public prototype_ `FGetMetadataFieldResponse() = default;`
- L177 _public function_ `FGetMetadataFieldResponse(FString InValue) : Value(MoveTemp(InValue))`
- L183 _public member_ `FString Value;` — `UPROPERTY()` — The metadata value for a given key.

#### struct `FGetMetadataResponse`  
`struct FGetMetadataResponse`  
_L188-200_
- reflection: `USTRUCT()`
- L192 _public prototype_ `FGetMetadataResponse() = default;`
- L194 _public function_ `FGetMetadataResponse(TMap<FString, FString> InMetadata) : Metadata(MoveTemp(InMetadata))`
- L199 _public member_ `TMap<FString, FString> Metadata;` — `UPROPERTY()`

#### struct `FSetEntityLabelResponse`  
`struct FSetEntityLabelResponse`  
_L203-217_
- reflection: `USTRUCT()`
- L207 _public prototype_ `FSetEntityLabelResponse() = default;`
- L209 _public function_ `FSetEntityLabelResponse(FString&& InString) : AssignedLabel(MoveTemp(InString))`
- L216 _public member_ `FString AssignedLabel;` — `UPROPERTY()` — The label that was assigned when requesting to modify an entity's label.

#### struct `FRCPresetFieldsRenamedEvent`  
`struct FRCPresetFieldsRenamedEvent`  
_L220-245_
- reflection: `USTRUCT()`
- L224 _public prototype_ `FRCPresetFieldsRenamedEvent() = default;`
- L226 _public function_ `FRCPresetFieldsRenamedEvent(FName InPresetName, FGuid InPresetId, TArray<TTuple<FName, FName>> InRenamedFields) : Type(TEXT("PresetFieldsRenamed")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , RenamedFields(MoveTemp(InRenamedFields))`
- L235 _public member_ `FString Type;` — `UPROPERTY()`
- L238 _public member_ `FName PresetName;` — `UPROPERTY()`
- L241 _public member_ `FString PresetId;` — `UPROPERTY()`
- L244 _public member_ `TArray<FRCPresetFieldRenamed> RenamedFields;` — `UPROPERTY()`

#### struct `FRCPresetMetadataModified`  
`struct FRCPresetMetadataModified`  
_L248-276_
- reflection: `USTRUCT()`
- L252 _public prototype_ `FRCPresetMetadataModified() = default;`
- L254 _public function_ `FRCPresetMetadataModified(URemoteControlPreset* InPreset) : Type(TEXT("PresetMetadataModified"))`
- L266 _public member_ `FString Type;` — `UPROPERTY()`
- L269 _public member_ `FName PresetName;` — `UPROPERTY()`
- L272 _public member_ `FString PresetId;` — `UPROPERTY()`
- L275 _public member_ `TMap<FString, FString> Metadata;` — `UPROPERTY()`

#### struct `FRCPresetLayoutModified`  
`struct FRCPresetLayoutModified`  
_L280-297_
- reflection: `USTRUCT()`
- L284 _public prototype_ `FRCPresetLayoutModified() = default;`
- L286 _public function_ `FRCPresetLayoutModified(URemoteControlPreset* InPreset) : Type(TEXT("PresetLayoutModified")) , Preset(InPreset)`
- L293 _public member_ `FString Type;` — `UPROPERTY()`
- L296 _public member_ `FRCPresetDescription Preset;` — `UPROPERTY()`

#### struct `FRCPresetFieldsRemovedEvent`  
`struct FRCPresetFieldsRemovedEvent`  
_L300-329_
- reflection: `USTRUCT()`
- L304 _public prototype_ `FRCPresetFieldsRemovedEvent() = default;`
- L306 _public function_ `FRCPresetFieldsRemovedEvent(FName InPresetName, FGuid InPresetId, TArray<FName> InRemovedFields, const TArray<FGuid>& InRemovedFieldIDs) : Type(TEXT("PresetFieldsRemoved")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , RemovedFields(MoveTemp(InRemovedFields))`
- L316 _public member_ `FString Type;` — `UPROPERTY()`
- L319 _public member_ `FName PresetName;` — `UPROPERTY()`
- L322 _public member_ `FString PresetId;` — `UPROPERTY()`
- L325 _public member_ `TArray<FName> RemovedFields;` — `UPROPERTY()`
- L328 _public member_ `TArray<FString> RemovedFieldIds;` — `UPROPERTY()`

#### struct `FRCPresetFieldsAddedEvent`  
`struct FRCPresetFieldsAddedEvent`  
_L332-357_
- reflection: `USTRUCT()`
- L336 _public prototype_ `FRCPresetFieldsAddedEvent() = default;`
- L338 _public function_ `FRCPresetFieldsAddedEvent(FName InPresetName, FGuid InPresetId, FRCPresetDescription InPresetAddition) : Type(TEXT("PresetFieldsAdded")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , Description(MoveTemp(InPresetAddition))`
- L347 _public member_ `FString Type;` — `UPROPERTY()`
- L350 _public member_ `FName PresetName;` — `UPROPERTY()`
- L353 _public member_ `FString PresetId;` — `UPROPERTY()`
- L356 _public member_ `FRCPresetDescription Description;` — `UPROPERTY()`

#### struct `FRCPresetEntitiesModifiedEvent`  
`struct FRCPresetEntitiesModifiedEvent`  
_L363-401_
- reflection: `USTRUCT()`
- desc: Event triggered when an exposed entity struct is modified.
- L367 _public prototype_ `FRCPresetEntitiesModifiedEvent() = default;`
- L369 _public function_ `FRCPresetEntitiesModifiedEvent(URemoteControlPreset* InPreset, const TArray<FGuid>& InModifiedEntities) : Type(TEXT("PresetEntitiesModified"))`
- L382 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L388 _public member_ `FName PresetName;` — `UPROPERTY()` — Name of the preset which contains the modified entities.
- L394 _public member_ `FString PresetId;` — `UPROPERTY()` — ID of the preset that contains the modified entities.
- L400 _public member_ `FRCPresetModifiedEntitiesDescription ModifiedEntities;` — `UPROPERTY()` — The entities that were modified in the last frame.

#### struct `FRCPresetControllersRenamedEvent`  
`struct FRCPresetControllersRenamedEvent`  
_L404-429_
- reflection: `USTRUCT()`
- L408 _public prototype_ `FRCPresetControllersRenamedEvent() = default;`
- L410 _public function_ `FRCPresetControllersRenamedEvent(FName InPresetName, FGuid InPresetId, TArray<TTuple<FName, FName>> InRenamedControllers) : Type(TEXT("PresetControllersRenamed")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , RenamedControllers(InRenamedControllers)`
- L419 _public member_ `FString Type;` — `UPROPERTY()`
- L422 _public member_ `FName PresetName;` — `UPROPERTY()`
- L425 _public member_ `FString PresetId;` — `UPROPERTY()`
- L428 _public member_ `TArray<FRCPresetFieldRenamed> RenamedControllers;` — `UPROPERTY()`

#### struct `FRCPresetControllersRemovedEvent`  
`struct FRCPresetControllersRemovedEvent`  
_L432-461_
- reflection: `USTRUCT()`
- L436 _public prototype_ `FRCPresetControllersRemovedEvent() = default;`
- L438 _public function_ `FRCPresetControllersRemovedEvent(FName InPresetName, FGuid InPresetId, TArray<FName> InRemoveControllers, const TArray<FGuid>& InRemovedControllerIds) : Type(TEXT("PresetControllersRemoved")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , RemovedControllers(MoveTemp(InRemoveControllers))`
- L448 _public member_ `FString Type;` — `UPROPERTY()`
- L451 _public member_ `FName PresetName;` — `UPROPERTY()`
- L454 _public member_ `FString PresetId;` — `UPROPERTY()`
- L457 _public member_ `TArray<FName> RemovedControllers;` — `UPROPERTY()`
- L460 _public member_ `TArray<FString> RemovedControllerIds;` — `UPROPERTY()`

#### struct `FRCPresetControllersAddedEvent`  
`struct FRCPresetControllersAddedEvent`  
_L464-489_
- reflection: `USTRUCT()`
- L468 _public prototype_ `FRCPresetControllersAddedEvent() = default;`
- L470 _public function_ `FRCPresetControllersAddedEvent(FName InPresetName, FGuid InPresetId, FRCPresetDescription InPresetDescription) : Type(TEXT("PresetControllersAdded")) , PresetName(InPresetName) , PresetId(InPresetId.ToString()) , Description(MoveTemp(InPresetDescription))`
- L479 _public member_ `FString Type;` — `UPROPERTY()`
- L482 _public member_ `FName PresetName;` — `UPROPERTY()`
- L485 _public member_ `FString PresetId;` — `UPROPERTY()`
- L488 _public member_ `FRCPresetDescription Description;` — `UPROPERTY()`

#### struct `FRCPresetControllersModifiedEvent`  
`struct FRCPresetControllersModifiedEvent`  
_L493-532_
- reflection: `USTRUCT()`
- desc: Event which is triggered whenever a Controller is modified.
- L497 _public prototype_ `FRCPresetControllersModifiedEvent() = default;`
- L499 _public function_ `FRCPresetControllersModifiedEvent(const URemoteControlPreset* InPreset, const TArray<FGuid>& InModifiedControllers) : Type(TEXT("PresetControllersModified"))`
- L513 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L519 _public member_ `FName PresetName;` — `UPROPERTY()` — Name of the preset which contains the modified controller.
- L525 _public member_ `FString PresetId;` — `UPROPERTY()` — ID of the preset that contains the modified controller.
- L531 _public member_ `FRCControllerModifiedDescription ModifiedControllers;` — `UPROPERTY()` — The controllers that were modified in the last frame.

#### struct `FRCActorsChangedData`  
`struct FRCActorsChangedData`  
_L538-553_
- reflection: `USTRUCT()`
- desc: Data about actors that have changed in the scene.
- L544 _public member_ `TArray<FRCActorDescription> AddedActors;` — `UPROPERTY()` — Actors that were added.
- L548 _public member_ `TArray<FRCActorDescription> RenamedActors;` — `UPROPERTY()` — Actors that were renamed.
- L552 _public member_ `TArray<FRCActorDescription> DeletedActors;` — `UPROPERTY()` — Actors that were deleted.

#### struct `FRCActorsChangedEvent`  
`struct FRCActorsChangedEvent`  
_L559-579_
- reflection: `USTRUCT()`
- desc: Event triggered when the list of actors in the current scene (or their names) changes.
- L563 _public function_ `FRCActorsChangedEvent() : Type(TEXT("ActorsChanged"))`
- L572 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L578 _public member_ `TMap<FString, FRCActorsChangedData> Changes;` — `UPROPERTY()` — Map from class name to changes in actors of that type.

#### struct `FRCTransactionEndedEvent`  
`struct FRCTransactionEndedEvent`  
_L585-611_
- reflection: `USTRUCT()`
- desc: Event sent to a client that contributed to a transaction, indicating that the transaction was either cancelled or finalized.
- L589 _public function_ `FRCTransactionEndedEvent() : Type(TEXT("TransactionEnded"))`
- L598 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L604 _public member_ `int32 TransactionId = -1;` — `UPROPERTY()` — The client-specific ID of the transaction that was ended.
- L610 _public member_ `int64 SequenceNumber = -1;` — `UPROPERTY()` — The highest sequence number received from the receiving client at the time that the transaction ended.

#### struct `FRCCompressionChangedEvent`  
`struct FRCCompressionChangedEvent`  
_L618-638_
- reflection: `USTRUCT()`
- desc: Event sent to confirm that the WebSocket compression mode has changed. This will be sent using the previous compression mode, and messages after this point will use the new one indicated in this event.
- L622 _public function_ `FRCCompressionChangedEvent() : Type(TEXT("CompressionChanged"))`
- L631 _public member_ `FString Type;` — `UPROPERTY()` — Type of the event.
- L637 _public member_ `ERCWebSocketCompressionMode Mode = ERCWebSocketCompressionMode::NONE;` — `UPROPERTY()` — The new compression mode which will be used by future messages.

#### Free symbols / members of external scopes

- L312 _function_ `Algo::Transform(InRemovedFieldIDs, RemovedFieldIds, [](const FGuid& Id){ return Id.ToString(); });` (scope `FRCPresetFieldsRemovedEvent::FRCPresetFieldsRemovedEvent`)
- L444 _function_ `Algo::Transform(InRemovedControllerIds, RemovedControllerIds, [](const FGuid& Id){ return Id.ToString();});` (scope `FRCPresetControllersRemovedEvent::FRCPresetControllersRemovedEvent`)

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlRoute.h` (Private)


#### struct `FRemoteControlRoute`  
`struct FRemoteControlRoute`  
_L13-33_
- L15 _public function_ `FRemoteControlRoute(FString InRouteDescription, FHttpPath InPath, EHttpServerRequestVerbs InVerb, FHttpRequestHandler InHandler) : RouteDescription(MoveTemp(InRouteDescription)) , Path(MoveTemp(InPath)) , Verb(InVerb) , Handler(MoveTemp(InHandler))`
- L23 _public member_ `FString RouteDescription;` — A description of how the route should be used.
- L25 _public member_ `FHttpPath Path;` — Relative path (ie. /remote/object)
- L27 _public member_ `EHttpServerRequestVerbs Verb = EHttpServerRequestVerbs::VERB_GET;` — The desired HTTP verb (ie. GET, PUT..)
- L29 _public member_ `FHttpRequestHandler Handler;` — The handler called when the route is accessed.

#### enum `ERemoteControlHttpVerbs`  
`enum class ERemoteControlHttpVerbs : uint16`  
_L36-45_
- reflection: `UENUM()`
- L38 _public enumerator_ `None = 0`
- L39 _public enumerator_ `Get = 1 << 0`
- L40 _public enumerator_ `Post = 1 << 1`
- L41 _public enumerator_ `Put = 1 << 2`
- L42 _public enumerator_ `Patch = 1 << 3`
- L43 _public enumerator_ `Delete = 1 << 4`
- L44 _public enumerator_ `Options = 1 << 5`

#### struct `FRemoteControlRouteDescription`  
`struct FRemoteControlRouteDescription`  
_L51-71_
- reflection: `USTRUCT()`
- desc: Utility struct to create a textual representation of an http route.
- L55 _public prototype_ `FRemoteControlRouteDescription() = default;`
- L57 _public function_ `FRemoteControlRouteDescription(const FRemoteControlRoute& Route) : Path(Route.Path.GetPath()) , Verb((ERemoteControlHttpVerbs)Route.Verb) , Description(Route.RouteDescription)`
- L64 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L67 _public member_ `ERemoteControlHttpVerbs Verb = ERemoteControlHttpVerbs::None;` — `UPROPERTY()`
- L70 _public member_ `FString Description;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L31 _function_ `friend uint32 GetTypeHash(const FRemoteControlRoute& Route)`
- L32 _function_ `friend bool operator==(const FRemoteControlRoute& LHS, const FRemoteControlRoute& RHS)`

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/RemoteControlWebSocketServer.h` (Private)


#### class `FWebsocketMessageRouter`  
`class FWebsocketMessageRouter`  
_L19-71_
- desc: Router used to dispatch messages received by a WebSocketServer.
- L27 _public prototype_ `void BindRoute(const FString& MessageName, FWebSocketMessageDelegate OnMessageReceived);` — Add a handler to the Router's dispatch table. @param MessageName the name of the message to handle. @param FWebSocketMessageDelegate the handler to called upon receiving a message with the right name.
- L33 _public prototype_ `void UnbindRoute(const FString& MessageName);` — Remove a route from the dispatch table. @param MessageName the name of the message handler to remove.
- L40 _public prototype_ `void AddPreDispatch(TFunction<bool(const struct FRemoteControlWebSocketMessage& Message)> WebsocketPreprocessor);` — Adds a Preprocessor called before the Dispatch of the Route @param WebsocketPreprocessor The Preprocessor Function to register @note: If the predispatch returns false, the actual request will not be executed.
- L45 _public prototype_ `void AttemptDispatch(const struct FRemoteControlWebSocketMessage& Message);` — Attempt to dispatch a WebSocket message if its PreDispatch passes.
- L49 _private member_ `TArray<TFunction<bool(const struct FRemoteControlWebSocketMessage& Message)>> DispatchPreProcessor;` — Preprocessors for the Dispatch Function
- L57 _private prototype_ `bool PreDispatch(const struct FRemoteControlWebSocketMessage& Message) const;` — Check if the Message to be dispatched can be executed @param MessageName the name of the message to dispatch, used to find its handler @param TCHARMessage the payload to dispatch. @return true if can be dispatched, false if not
- L64 _private prototype_ `void Dispatch(const struct FRemoteControlWebSocketMessage& Message);` — Invoke the handler bound to a message name. @param MessageName the name of the message to dispatch, used to find its handler. @param TCHARMessage the payload to dispatch.
- L68 _private member_ `TMap<FString, FWebSocketMessageDelegate> DispatchTable;` — The dispatch table used to keep track of message handlers.

#### class `FRCWebSocketServer`  
`class FRCWebSocketServer`  
_L76-215_
- desc: WebSocket server that allows handling and sending WebSocket messages.
- L80 _public prototype_ `FRCWebSocketServer() = default;`
- L81 _public prototype_ `~FRCWebSocketServer();`
- L89 _public prototype_ `bool Start(uint32 Port, TSharedPtr<FWebsocketMessageRouter> InRouter);` — Start listening for WebSocket messages. @param Port the port to listen on. @param InRouter the router used to dispatch received messages. @return whether the server was successfully started.
- L94 _public prototype_ `void Stop();` — Stop listening for WebSocket messages.
- L100 _public prototype_ `void Broadcast(const TArray<uint8>& InUTF8Payload);` — Send a message to all clients currently connected to the server. @param InUTF8Payload the payload to broadcast to connected clients.
- L107 _public prototype_ `void Send(const FGuid& InTargetClientId, const TArray<uint8>& InUTF8Payload);` — Send a message to a client. @param InTargetClientId the target client's id. @param InUTF8Payload the payload to send.
- L110 _public prototype_ `bool IsRunning() const;` — Returns whether the server is currently listening for messages.
- L113 _public function_ `FOnWebSocketConnectionOpened& OnConnectionOpened()` — Callback when a socket is opened
- L116 _public function_ `FOnWebSocketConnectionClosed& OnConnectionClosed()` — Callback when a socket is closed
- L119 _public prototype_ `void SetClientCompressionMode(const FGuid& ClientId, ERCWebSocketCompressionMode Mode);` — Set the compression mode for a client by its GUID.
- L124 _private prototype_ `bool Tick(float DeltaTime);`
- L127 _private prototype_ `void OnWebSocketClientConnected(INetworkingWebSocket* Socket);` — Handles a new client connecting.
- L130 _private prototype_ `void ReceivedRawPacket(void* Data, int32 Size, FGuid ClientId, TSharedPtr<FInternetAddr> PeerAddress);` — Handles sending the received packet to the message router.
- L132 _private prototype_ `void OnSocketClose(INetworkingWebSocket* Socket);`
- L135 _private prototype_ `FWebSocketConnection* GetClientById(const FGuid& Id);` — Given a client ID, find the corresponding client, or null if it's not connected to this server.
- L138 _private prototype_ `void SendOnConnection(FWebSocketConnection& Connection, const TArray<uint8>& InUTF8Payload);` — Send a message on a specific connection
- L141 _private prototype_ `EWebsocketConnectionFilterResult FilterConnection(FString OriginHeader, FString ClientIP) const;` — Handle rejecting the websocket connection if it doesn't respect the user's CORS policy.
- L144 _private prototype_ `bool IsPortAvailable(uint32 Port) const;` — Returns whether the port is available.
- L199 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to the tick delegate.
- L202 _private member_ `TUniquePtr<IWebSocketServer> Server;` — Holds the LibWebSocket wrapper.
- L205 _private member_ `TArray<FWebSocketConnection> Connections;` — Holds all active connections.
- L208 _private member_ `TSharedPtr<FWebsocketMessageRouter> Router;` — Holds the router responsible for dispatching messages received by this server.
- L211 _private member_ `FOnWebSocketConnectionOpened OnConnectionOpenedDelegate;` — Delegate triggered when a connection is opened
- L214 _private member_ `FOnWebSocketConnectionClosed OnConnectionClosedDelegate;` — Delegate triggered when a connection is closed

#### class `FRCWebSocketServer::FWebSocketConnection`  
`class FWebSocketConnection`  
_L148-195_
- desc: Holds a web socket connection to a client.
- L152 _public function_ `explicit FWebSocketConnection(INetworkingWebSocket* InSocket) : Socket(InSocket) , Id(FGuid::NewGuid())`
- L163 _public function_ `FWebSocketConnection(FWebSocketConnection&& WebSocketConnection) : Id(WebSocketConnection.Id)`
- L171 _public function_ `~FWebSocketConnection()`
- L180 _public prototype_ `FWebSocketConnection(const FWebSocketConnection&) = delete;`
- L181 _public prototype_ `FWebSocketConnection& operator=(const FWebSocketConnection&) = delete;`
- L182 _public prototype_ `FWebSocketConnection& operator=(FWebSocketConnection&&) = delete;`
- L185 _public member_ `INetworkingWebSocket* Socket = nullptr;` — Underlying WebSocket.
- L188 _public member_ `FGuid Id;` — Generated ID for this client.
- L191 _public member_ `TSharedPtr<FInternetAddr> PeerAddress;` — IP Address of the client.
- L194 _public member_ `ERCWebSocketCompressionMode CompressionMode = ERCWebSocketCompressionMode::NONE;` — Compression mode to use for this client.

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/Serialization/RCJsonStructDeserializerBackend.h` (Private)


#### class `FRCJsonStructDeserializerBackend`  
`class FRCJsonStructDeserializerBackend : public FJsonStructDeserializerBackend`  
_L11-27_
- inherits: `FJsonStructDeserializerBackend`
- desc: Implements a custom reader for UStruct serialization using Json. Tries to read enum values using the display name.
- L20 _public function_ `FRCJsonStructDeserializerBackend(FArchive& InArchive) : FJsonStructDeserializerBackend(InArchive)` — Initialize the deserializer @param InArchive The archive to deserialize from.
- L26 _public prototype_ `virtual bool ReadProperty(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) override;` — IStructDeserializerBackend interface

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/Serialization/RCJsonStructSerializerBackend.h` (Private)


#### class `FRCJsonStructSerializerBackend`  
`class FRCJsonStructSerializerBackend : public FJsonStructSerializerBackend`  
_L12-31_
- inherits: `FJsonStructSerializerBackend`
- desc: Implements a custom writer for UStruct serialization using Json. Tries to serialize enum values with their display name.
- L17 _public member_ `static const EStructSerializerBackendFlags DefaultSerializerFlags = EStructSerializerBackendFlags::WriteByteArrayAsByteStream;` — Default flags for serializing structures in Web RC.
- L25 _public function_ `FRCJsonStructSerializerBackend(FArchive& InArchive, const EStructSerializerBackendFlags InFlags = DefaultSerializerFlags) : FJsonStructSerializerBackend(InArchive, InFlags)` — Creates and initializes a new instance with the given flags. @param InArchive The archive to serialize into. @param InFlags The flags that control the serialization behavior (typically FRCJsonStructSerializerBackend::DefaultSerializerFlags).
- L30 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;` — IStructSerializerBackend interface

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/WebRemoteControl.h` (Private)


#### class `FWebRemoteControlModule`  
`class FWebRemoteControlModule : public IWebRemoteControlModule`  
_L26-228_
- inherits: `IWebRemoteControlModule`
- desc: A Remote Control module that expose remote function calls through http
- L35 _public function_ `static FWebRemoteControlModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public prototype_ `virtual void StartupModule() override;`
- L43 _public prototype_ `virtual void ShutdownModule() override;`
- L44 _public prototype_ `virtual FDelegateHandle RegisterRequestPreprocessor(FHttpRequestHandler RequestPreprocessor) override;`
- L45 _public prototype_ `virtual void UnregisterRequestPreprocessor(const FDelegateHandle& RequestPreprocessorHandle) override;`
- L46 _public function_ `virtual FOnWebServerStarted& OnHttpServerStarted() override`
- L47 _public function_ `virtual FSimpleMulticastDelegate& OnHttpServerStopped() override`
- L48 _public function_ `virtual bool IsHttpServerRunning() override`
- L49 _public function_ `virtual FOnWebServerStarted& OnWebSocketServerStarted() override`
- L50 _public function_ `virtual FSimpleMulticastDelegate& OnWebSocketServerStopped() override`
- L51 _public function_ `virtual bool IsWebSocketServerRunning() override`
- L52 _public function_ `virtual FOnWebSocketConnectionClosed& OnWebSocketConnectionOpened() override`
- L53 _public function_ `virtual FOnWebSocketConnectionClosed& OnWebSocketConnectionClosed() override`
- L54 _public prototype_ `virtual void RegisterWebsocketRoute(const FRemoteControlWebsocketRoute& Route) override;`
- L55 _public prototype_ `virtual void UnregisterWebsocketRoute(const FRemoteControlWebsocketRoute& Route) override;`
- L56 _public prototype_ `virtual void SendWebsocketMessage(const FGuid& InTargetClientId, const TArray<uint8>& InUTF8Payload) override;`
- L57 _public prototype_ `virtual void SetExternalRemoteWebSocketLoggerConnection(TSharedPtr<class INetworkingWebSocket> WebSocketLoggerConnection) override;`
- L64 _public prototype_ `void RegisterRoute(const FRemoteControlRoute& Route);` — Register a route to the API. @param Route The route to register.
- L70 _public prototype_ `void UnregisterRoute(const FRemoteControlRoute& Route);` — Unregister a route to the API. @param Route The route to unregister.
- L75 _public prototype_ `void StartHttpServer();` — Start the web control server
- L80 _public prototype_ `void StopHttpServer();` — Stop the web control server.
- L85 _public prototype_ `void StartWebSocketServer();` — Start the web control websocket server.
- L90 _public prototype_ `void StopWebSocketServer();` — Stop the web control websocket server.
- L94 _private prototype_ `void StartRoute(const FRemoteControlRoute& Route);` — Bind the route in the http router and add it to the list of active routes.
- L97 _private prototype_ `void RegisterRoutes();` — Register HTTP and Websocket routes.
- L100 _private prototype_ `void RegisterConsoleCommands();` — Register console commands.
- L103 _private prototype_ `void UnregisterConsoleCommands();` — Unregister console commands.
- L106 _private prototype_ `bool HandleInfoRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L107 _private prototype_ `bool HandleBatchRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L108 _private prototype_ `bool HandleOptionsRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L109 _private prototype_ `bool HandleObjectCallRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L110 _private prototype_ `bool HandleObjectPropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L111 _private prototype_ `bool HandleObjectPropertyAppendRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L112 _private prototype_ `bool HandleObjectPropertyInsertRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L113 _private prototype_ `bool HandleObjectPropertyRemoveRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L114 _private prototype_ `bool HandlePresetCallFunctionRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L115 _private prototype_ `bool HandlePresetSetPropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L116 _private prototype_ `bool HandlePresetGetPropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L117 _private prototype_ `bool HandlePresetExposePropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L118 _private prototype_ `bool HandlePresetUnexposePropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L119 _private prototype_ `bool HandlePresetGetExposedActorPropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L120 _private prototype_ `bool HandlePresetGetExposedActorPropertiesRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L121 _private prototype_ `bool HandlePresetSetExposedActorPropertyRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L122 _private prototype_ `bool HandleGetPresetRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L123 _private prototype_ `bool HandleGetPresetsRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L124 _private prototype_ `bool HandleDescribeObjectRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L125 _private prototype_ `bool HandleSearchActorRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L126 _private prototype_ `bool HandleSearchAssetRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L127 _private prototype_ `bool HandleGetMetadataRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L128 _private prototype_ `bool HandleMetadataFieldOperationsRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L129 _private prototype_ `bool HandleSearchObjectRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L130 _private prototype_ `bool HandleEntityMetadataOperationsRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L131 _private prototype_ `bool HandleEntitySetLabelRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L132 _private prototype_ `bool HandlePassphraseRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L133 _private prototype_ `bool HandleCreateTransientPresetRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L134 _private prototype_ `bool HandleDeleteTransientPresetRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L135 _private prototype_ `bool HandlePresetSetControllerRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L136 _private prototype_ `bool HandlePresetGetControllerRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L139 _private prototype_ `void HandleWebSocketHttpMessage(const struct FRemoteControlWebSocketMessage& WebSocketMessage);`
- L140 _private prototype_ `void HandleWebSocketBatchMessage(const FRemoteControlWebSocketMessage& WebSocketMessage);`
- L142 _private prototype_ `void InvokeWrappedRequest(const struct FRCRequestWrapper& Wrapper, FMemoryWriter& OutUTF8PayloadWriter, const FHttpServerRequest* TemplateRequest = nullptr);`
- L145 _private prototype_ `void RegisterDefaultPreprocessors();` — Register the default request preprocessors used by Web RC in the HttpRouter.
- L146 _private prototype_ `void UnregisterAllPreprocessors();`
- L149 _private prototype_ `void RegisterExternalPreprocesors();` — Register the external request preprocessors that were added using RegisterRequestPreprocessor in the HttpRouter.
- L153 _private prototype_ `void RegisterSettings();`
- L154 _private prototype_ `void UnregisterSettings();`
- L155 _private prototype_ `void OnSettingsModified(UObject* Settings, FPropertyChangedEvent& PropertyChangedEvent);`
- L158 _private prototype_ `void LogRequestExternally(int32 RequestId, const TCHAR* Stage);`
- L162 _private member_ `TArray<TUniquePtr<FAutoConsoleCommand>> ConsoleCommands;` — Console commands handles.
- L165 _private member_ `TSharedPtr<IHttpRouter> HttpRouter;` — Http router handle
- L168 _private member_ `TMap<uint32, FHttpRouteHandle> ActiveRouteHandles;` — Mapping of routes to delegate handles
- L171 _private member_ `TSet<FRemoteControlRoute> RegisteredHttpRoutes;` — Set of routes that will be activated on http server start.
- L174 _private member_ `TSet<FRemoteControlWebsocketRoute> RegisteredWebSocketRoutes;` — Set of routes that will be activated on websocket server start.
- L177 _private member_ `uint32 HttpServerPort;` — Port of the remote control http server.
- L180 _private member_ `FString WebsocketServerBindAddress;` — The address the websocket server is currently bound to.
- L183 _private member_ `uint32 WebSocketServerPort;` — Port of the remote control websocket server.
- L186 _private member_ `FWebRemoteControlEditorRoutes EditorRoutes;` — Routes that are editor specific.
- L189 _private member_ `TUniquePtr<FWebSocketMessageHandler> WebSocketHandler;` — Handler processing websocket specific messages
- L192 _private member_ `FRCWebSocketServer WebSocketServer;` — Server that serves websocket requests.
- L195 _private member_ `TSharedPtr<FWebsocketMessageRouter> WebSocketRouter;` — Router used to dispatch websocket messages.
- L198 _private member_ `FGuid ActingClientId;` — Holds the client currently making a request.
- L201 _private member_ `bool bIsHttpServerRunning = false;` — Whether the HTTP server has been started and has not been stopped.
- L204 _private member_ `TMap<FDelegateHandle, FHttpRequestHandler> PreprocessorsToRegister;` — List of preprocessor delegates that need to be registered when the server is started.
- L209 _private member_ `TMap<FDelegateHandle, FDelegateHandle> PreprocessorsHandleMappings;` — Mappings of preprocessors delegate handles generated from the WebRC module to the ones generated from the Http Module.
- L214 _private member_ `TArray<FDelegateHandle> AllRegisteredPreprocessorHandlers;` — List of all registered preprocessor handlers. Used to unregister them on shutdown.
- L217 _private member_ `TUniquePtr<class FWebRemoteControlExternalLogger> ExternalLogger;` — An external web socket logger
- L220 _private member_ `FOnWebServerStarted OnHttpServerStartedDelegate;`
- L221 _private member_ `FSimpleMulticastDelegate OnHttpServerStoppedDelegate;`
- L222 _private member_ `FOnWebServerStarted OnWebSocketServerStartedDelegate;`
- L223 _private member_ `FSimpleMulticastDelegate OnWebSocketServerStoppedDelegate;`
- L227 _private member_ `TMap<FName, FString> ControllersSerializerStructNameCache;` — Name cache for Get Controller Result structs Key: Controller name; Value: Name of the dynamic struct holding our result

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/WebRemoteControlEditorRoutes.h` (Private)


#### class `FWebRemoteControlEditorRoutes`  
`class FWebRemoteControlEditorRoutes`  
_L21-87_
- L25 _public prototype_ `void RegisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Register the editor routes to the web remote control module.
- L28 _public prototype_ `void UnregisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Unregister the editor routes from the module
- L76 _private prototype_ `void AddPendingEvent(FRemoteControlObjectEventHookRequest InRequest, TUniquePtr<FHttpServerResponse> InResponse, FHttpResultCallback OnComplete);` — Create an event dispatcher that waits until a desired event occurs before returning an http response.
- L79 _private prototype_ `bool HandleObjectEventRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Route handlers
- L80 _private prototype_ `bool HandleGetThumbnailRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L84 _private member_ `TArray<FRemoteEventDispatcher> EventDispatchers;` — Remote event mechanism delegate handles.
- L86 _private member_ `TArray<FRemoteControlRoute> Routes;` — Holds all the editor routes.
- L92 _public function_ `void RegisterRoutes(FWebRemoteControlModule*)`
- L93 _public function_ `void UnregisterRoutes(FWebRemoteControlModule*)`

#### struct `FWebRemoteControlEditorRoutes::FRemoteEventHook`  
`struct FRemoteEventHook`  
_L32-43_
- desc: Structure used to hold an object and to handle responding to the pending HTTP request.
- L34 _public function_ `FRemoteEventHook(FRCObjectReference InObjectRef, TUniquePtr<FHttpServerResponse> InResponse, FHttpResultCallback InCompleteCallback) : ObjectRef(MoveTemp(InObjectRef)) , Response(MoveTemp(InResponse)) , CompleteCallback(MoveTemp(InCompleteCallback))`
- L40 _public member_ `FRCObjectReference ObjectRef;`
- L41 _public member_ `TUniquePtr<FHttpServerResponse> Response;`
- L42 _public member_ `FHttpResultCallback CompleteCallback;`

#### struct `FWebRemoteControlEditorRoutes::FRemoteEventDispatcher`  
`struct FRemoteEventDispatcher`  
_L46-73_
- desc: Structure that handles subscribing to events and dispatching the appropriate HTTP response.
- L48 _public function_ `FRemoteEventDispatcher() : DispatcherType(ERemoteControlEvent::EventCount)`
- L52 _public function_ `~FRemoteEventDispatcher()`
- L57 _public function_ `bool IsValid() const`
- L62 _public prototype_ `void Initialize(ERemoteControlEvent Type);`
- L64 _public prototype_ `void Reset();`
- L66 _public prototype_ `void Dispatch(UObject* InObject, FProperty* InProperty);`
- L68 _public prototype_ `void SendResponse(FRemoteEventHook& EventHook);`
- L70 _public member_ `ERemoteControlEvent DispatcherType;`
- L71 _public member_ `FDelegateHandle DelegateHandle;`
- L72 _public member_ `TArray<FRemoteEventHook> PendingEvents;`

#### class `FWebRemoteControlEditorRoutes`  
`class FWebRemoteControlEditorRoutes`  
_L89-94_
- L25 _public prototype_ `void RegisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Register the editor routes to the web remote control module.
- L28 _public prototype_ `void UnregisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Unregister the editor routes from the module
- L76 _private prototype_ `void AddPendingEvent(FRemoteControlObjectEventHookRequest InRequest, TUniquePtr<FHttpServerResponse> InResponse, FHttpResultCallback OnComplete);` — Create an event dispatcher that waits until a desired event occurs before returning an http response.
- L79 _private prototype_ `bool HandleObjectEventRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Route handlers
- L80 _private prototype_ `bool HandleGetThumbnailRoute(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);`
- L84 _private member_ `TArray<FRemoteEventDispatcher> EventDispatchers;` — Remote event mechanism delegate handles.
- L86 _private member_ `TArray<FRemoteControlRoute> Routes;` — Holds all the editor routes.
- L92 _public function_ `void RegisterRoutes(FWebRemoteControlModule*)`
- L93 _public function_ `void UnregisterRoutes(FWebRemoteControlModule*)`

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/WebRemoteControlExternalLogger.h` (Private)


#### class `FWebRemoteControlExternalLogger`  
`class FWebRemoteControlExternalLogger`  
_L9-29_
- L12 _public prototype_ `FWebRemoteControlExternalLogger(TSharedPtr<class INetworkingWebSocket> WebSocketConnection);`
- L13 _public prototype_ `virtual ~FWebRemoteControlExternalLogger();`
- L15 _public prototype_ `void Log(int32 RequestId, const TCHAR* Stage);`
- L18 _private prototype_ `bool OnTick(float DeltaSeconds);`
- L19 _private prototype_ `void OnConnected();`
- L20 _private prototype_ `void OnClosed();`
- L22 _private member_ `bool IsConnected = false;`
- L25 _private member_ `TSharedPtr<class INetworkingWebSocket> WebSocketConnection;` — A WebSocket connection to the logger server
- L28 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — A handle to the ticker callback

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/WebRemoteControlInternalUtils.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace RemotePayloadSerializer`
- L24 _prototype_ `void ReplaceFirstOccurence(TConstArrayView<uint8> InPayload, const FString& From, const FString& To, TArray<uint8>& OutModifiedPayload);` (scope `RemotePayloadSerializer`) — Replaces the first occurrence of a string in a TCHAR binary payload.
- L29 _prototype_ `EHttpServerRequestVerbs ParseHttpVerb(FName InVerb);` (scope `RemotePayloadSerializer`) — Converts a string verb to the enum representation.
- L34 _prototype_ `TSharedRef<FHttpServerRequest> UnwrapHttpRequest(const FRCRequestWrapper& Wrapper, const FHttpServerRequest* TemplateRequest = nullptr);` (scope `RemotePayloadSerializer`) — Unwrap a request wrapper, while copying headers and http version from a template request if available.
- L39 _prototype_ `void SerializeWrappedCallResponse(int32 RequestId, TUniquePtr<FHttpServerResponse> Response, FMemoryWriter& Writer);` (scope `RemotePayloadSerializer`) — @note This will serialize in ANSI directly.
- L41 _prototype_ `bool DeserializeCall(const FHttpServerRequest& InRequest, FRCCall& OutCall, const FHttpResultCallback& InCompleteCallback);` (scope `RemotePayloadSerializer`)
- L43 _prototype_ `bool SerializeCall(const FRCCall& InCall, TArray<uint8>& OutPayload, bool bOnlyReturn = false);` (scope `RemotePayloadSerializer`)
- L45 _prototype_ `bool DeserializeObjectRef(const FHttpServerRequest& InRequest, FRCObjectReference& OutObjectRef, FRCObjectRequest& OutDeserializedRequest, const FHttpResultCallback& InCompleteCallback);` (scope `RemotePayloadSerializer`)
- L49 _namespace_ `namespace WebRemoteControlInternalUtils`
- L51 _variable_ `static const TCHAR* WrappedRequestHeader = TEXT("UE-` (scope `WebRemoteControlInternalUtils`)
- L52 _variable_ `static const FString PassphraseHeader = TEXT("Pas` (scope `WebRemoteControlInternalUtils`)
- L53 _variable_ `static const TCHAR* OriginHeader = TEXT("Ori` (scope `WebRemoteControlInternalUtils`)
- L54 _variable_ `static const TCHAR* ForwardedIPHeader = TEXT("x-f` (scope `WebRemoteControlInternalUtils`)
- L55 _variable_ `static const TCHAR* InvalidPassphraseError = TEXT("Giv` (scope `WebRemoteControlInternalUtils`)
- L62 _prototype_ `TUniquePtr<FHttpServerResponse> CreateHttpResponse(EHttpServerResponseCodes InResponseCode = EHttpServerResponseCodes::BadRequest);` (scope `WebRemoteControlInternalUtils`) — Construct a default http response with CORS headers. @param InResponseCode The response's code. (Defaults to a bad request) @return The constructed server response.
- L67 _prototype_ `TUniquePtr<FHttpServerResponse> CreatedInvalidPassphraseResponse();` (scope `WebRemoteControlInternalUtils`) — Create a http response for a request denied because of an invalid passphrase.
- L78 _prototype_ `void CreateUTF8ErrorMessage(const FString& InMessage, TArray<uint8>& OutUTF8Message);` (scope `WebRemoteControlInternalUtils`) — Create a json structure containing an error message. @param InMessage The desired error message. @param OutUTF8Message The error message wrapped in a json struct, in UTF-8 format. Example output: { errorMessage: "Request content type must be application/json" }
- L87 _prototype_ `bool GetStructParametersDelimiters(TConstArrayView<uint8> InTCHARPayload, TMap<FString, FBlockDelimiters>& InOutStructParameters, FString* OutErrorText = nullptr);` (scope `WebRemoteControlInternalUtils`) — Deserialize a json structure to find the start and end of every struct parameter in the request. @param InTCHARPayload The json payload to deserialize. @param InOutStructParameters A map of struct parameter names to the start and end of the struct in the payload. @param OutErrorText If set, the string pointer will be populated with an error message on error. @return Whether the deserialization was successful.
- L99 _function_ `template <typename RequestType> [[nodiscard]] bool DeserializeRequestPayload(TConstArrayView<uint8> InTCHARPayload, const FHttpResultCallback* InCompleteCallback, RequestType& OutDeserializedRequest)` (scope `WebRemoteControlInternalUtils`) — Deserialize a request into a UStruct. @param InTCHARPayload The json payload to deserialize. @param InCompleteCallback The callback to call error. @param The structure to serialize using the request's content. @return Whether the deserialization was successful. @note InCompleteCallback will be called with an appropriate http response if the deserialization fails.
- L135 _function_ `[[nodiscard]] inline bool DeserializeWrappedRequestPayload(TConstArrayView<uint8> InTCHARPayload, const FHttpResultCallback* InCompleteCallback, FRCRequestWrapper& Wrapper)` (scope `WebRemoteControlInternalUtils`) — Deserialize a wrapped request into a wrapper struct. @param InTCHARPayload The json payload to deserialize. @param InCompleteCallback The callback to call error. @param The wrapper structure to populate with the request's content. @return Whether the deserialization was successful.
- L158 _prototype_ `[[nodiscard]] bool GetBatchRequestStructDelimiters(TConstArrayView<uint8> InTCHARPayload, TMap<int32, FBlockDelimiters>& OutStructParameters, FString* OutErrorText = nullptr);` (scope `WebRemoteControlInternalUtils`) — Get the struct delimiters for all the batched requests. @param InTCHARPayload The json payload to deserialize. @param OutStructParameters A mapping of Request Id to their respective struct delimiters. @param OutErrorText If set, the string pointer will be populated with an error message on error. @return Whether the delimiters were able to be found.
- L167 _prototype_ `[[nodiscard]] bool GetBatchWebSocketRequestStructDelimiters(TConstArrayView<uint8> InTCHARPayload, TArray<FBlockDelimiters>& OutStructParameters, FString* OutErrorText = nullptr);` (scope `WebRemoteControlInternalUtils`) — Get the struct delimiters for all the batched WebSocket requests. @param InTCHARPayload The json payload to deserialize. @param OutStructParameters Delimiters for each request. @param OutErrorText If set, the string pointer will be populated with an error message on error. @return Whether the delimiters were able to be found.
- L180 _function_ `template <> [[nodiscard]] inline bool DeserializeRequestPayload(TConstArrayView<uint8> InTCHARPayload, const FHttpResultCallback* InCompleteCallback, FRCBatchRequest& OutDeserializedRequest)` (scope `WebRemoteControlInternalUtils`) — Specialization of DeserializeRequestPayload that handles Batch requests. This will populate the TCHARBody of all the wrapped requests. @param InTCHARPayload The json payload to deserialize. @param InCompleteCallback The callback to call error. @param The structure to serialize using the request's content. @return Whether the deserialization was successful. @note InCompleteCallback will be called with an appropriate http response if the deserialization fails.
- L231 _function_ `template <> [[nodiscard]] inline bool DeserializeRequestPayload(TConstArrayView<uint8> InTCHARPayload, const FHttpResultCallback* InCompleteCallback, FRCWebSocketBatchRequest& OutDeserializedRequest)` (scope `WebRemoteControlInternalUtils`) — Specialization of DeserializeRequestPayload that handles WebSocket batch requests. This will populate the TCHARBody of all the wrapped requests. @param InTCHARPayload The json payload to deserialize. @param InCompleteCallback The callback to call error. @param The structure to serialize using the request's content. @return Whether the deserialization was successful. @note InCompleteCallback will be called with an appropriate http response if the deserialization fails.
- L284 _prototype_ `void AddWrappedRequestHeader(FHttpServerRequest& Request);` (scope `WebRemoteControlInternalUtils`) — Adds a header indicating that the request is a wrapped request that originated from the engine itself.
- L289 _prototype_ `bool IsWrappedRequest(const FHttpServerRequest& Request);` (scope `WebRemoteControlInternalUtils`) — Get whether the request is a wrapped request.
- L301 _function_ `template <typename RequestType> [[nodiscard]] bool DeserializeRequest(const FHttpServerRequest& InRequest, const FHttpResultCallback* InCompleteCallback, RequestType& OutDeserializedRequest)` (scope `WebRemoteControlInternalUtils`) — Deserialize a request into a UStruct. @param InRequest The incoming http request. @param InCompleteCallback The callback to call error. @param The structure to serialize using the request's content. @return Whether the deserialization was successful. @note InCompleteCallback will be called with an appropriate http response if the deserialization fails.
- L328 _prototype_ `[[nodiscard]] bool ValidateContentType(const FHttpServerRequest& InRequest, FString InContentType, const FHttpResultCallback& InCompleteCallback);` (scope `WebRemoteControlInternalUtils`) — Validate a content-type. @param InRequest The incoming http request. @param InContentType The callback to call error. @param InCompleteCallback The callback to call error. @return Whether the content type was valid or not. @note InCompleteCallback will be called with an appropriate http response if the content type is not valid.
- L335 _prototype_ `[[nodiscard]] bool ValidateFunctionCall(const FRCCall& InRCCall, FString* OutErrorText);` (scope `WebRemoteControlInternalUtils`) — Check if a function call is valid since some objects//functions are disabled remotely for security reasons. @param InRCCall The RC call to validate. @param OutErrorText Optional error text.
- L342 _prototype_ `void AddContentTypeHeaders(FHttpServerResponse* InOutResponse, FString InContentType);` (scope `WebRemoteControlInternalUtils`) — Add the desired content type to the http response headers. @param InResponse The response to add the content type to. @param InContentType The content type header to add.
- L348 _prototype_ `void AddCORSHeaders(FHttpServerResponse* InOutResponse);` (scope `WebRemoteControlInternalUtils`) — Add CORS headers to a http response. @param InOutResponse The http response to add the CORS headers to.
- L357 _prototype_ `bool IsRequestContentType(const FHttpServerRequest& InRequest, const FString& InContentType, FString* OutErrorText);` (scope `WebRemoteControlInternalUtils`) — Validate a request's content type. @param InRequest The request to validate the content type on. @param InContentType The target content type. @param OutErrorText If set, the string pointer will be populated with an error message on error. @return Whether or not the content type matches the target content type.
- L365 _function_ `template <typename SerializerBackendType = FRCJsonStructSerializerBackend> void SerializeStructOnScope(const FStructOnScope& Struct, FMemoryWriter& Writer)` (scope `WebRemoteControlInternalUtils`) — Serialize a struct on scope. @param Struct the struct on scope to serialize. @param Writer the memory archive to write to.
- L382 _function_ `template <typename RequestType> bool ModifyPropertyUsingPayload(FRemoteControlProperty& Property, const RequestType& Request, const TArrayView<uint8>& Payload, const FGuid& ClientId, FWebSocketMessageHandler& WebSocketHandler, ERCAccess Access, FString* OutError = nullptr)` (scope `WebRemoteControlInternalUtils`) — Modify a property as specified by a remote request. @param Property The property to modify. @param Request The request to modify the property, containing additional information about how to modify it. @param Payload The payload from which to deserialize property data. @param ClientId The ID of the client that sent this request. @param WebSocketHandler The WebSocket handler that will be notified of this remote change. @param Access The access mode to use for this operation.
- L466 _prototype_ `bool CheckPassphrase(const FString& HashedPassphrase);` (scope `WebRemoteControlInternalUtils`) — Checking ApiKey using Md5.

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Private/WebSocketMessageHandler.h` (Private)


#### class `FWebSocketMessageHandler`  
`class FWebSocketMessageHandler`  
_L27-454_
- desc: Class handling web socket message. Registers to required callbacks.
- L30 _public prototype_ `FWebSocketMessageHandler(FRCWebSocketServer* InServer, const FGuid& InActingClientId);`
- L33 _public prototype_ `void RegisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Register the custom websocket routes with the module.
- L36 _public prototype_ `void UnregisterRoutes(FWebRemoteControlModule* WebRemoteControl);` — Unregister the custom websocket routes from the module
- L39 _public prototype_ `void NotifyPropertyChangedRemotely(const FGuid& OriginClientId, const FGuid& PresetId, const FGuid& ExposedPropertyId);` — Notify that a property was modified by a web client.
- L84 _private prototype_ `void RegisterRoute(FWebRemoteControlModule* WebRemoteControl, TUniquePtr<FRemoteControlWebsocketRoute> Route);` — Register a WebSocket route
- L87 _private prototype_ `void RegisterEngineEvents();` — Registers events that require the engine to be initialized first.
- L90 _private prototype_ `void HandleWebSocketPresetRegister(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles registration to callbacks to a given preset
- L93 _private prototype_ `void HandleWebSocketPresetUnregister(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles unregistration to callbacks to a given preset
- L96 _private prototype_ `void HandleWebSocketTransientPresetAutoDestroy(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles unregistration to callbacks to a given preset
- L99 _private prototype_ `void HandleWebSocketActorRegister(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles registration to callbacks for creation/destruction/rename of a given actor type
- L102 _private prototype_ `void HandleWebSocketActorUnregister(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles registration to callbacks for creation/destruction/rename of a given actor type
- L105 _private prototype_ `void HandleWebSocketPresetModifyProperty(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles property modification for a given preset
- L108 _private prototype_ `void HandleWebSocketFunctionCall(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles calling a Blueprint function
- L111 _private prototype_ `void HandleWebSocketBeginEditorTransaction(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles beginning a manual editor transaction.
- L114 _private prototype_ `void HandleWebSocketEndEditorTransaction(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles ending a manual editor transaction.
- L117 _private prototype_ `void HandleWebSocketCompressionChange(const FRemoteControlWebSocketMessage& WebSocketMessage);` — Handles changing the compression mode of WebSocket data
- L120 _private prototype_ `void OnPresetExposedPropertiesModified(URemoteControlPreset* Owner, const TSet<FGuid>& ModifiedPropertyIds);` — Preset callbacks
- L121 _private prototype_ `void OnPropertyExposed(URemoteControlPreset* Owner, const FGuid& EntityId);`
- L122 _private prototype_ `void OnPropertyUnexposed(URemoteControlPreset* Owner, const FGuid& EntityId);`
- L123 _private prototype_ `void OnFieldRenamed(URemoteControlPreset* Owner, FName OldFieldLabel, FName NewFieldLabel);`
- L124 _private prototype_ `void OnMetadataModified(URemoteControlPreset* Owner);`
- L125 _private prototype_ `void OnActorPropertyChanged(URemoteControlPreset* Owner, FRemoteControlActor& Actor, UObject* ModifiedObject, FProperty* ModifiedProperty);`
- L126 _private prototype_ `void OnEntitiesModified(URemoteControlPreset* Owner, const TSet<FGuid>& ModifiedEntities);`
- L127 _private prototype_ `void OnLayoutModified(URemoteControlPreset* Owner);`
- L130 _private prototype_ `void OnControllerAdded(URemoteControlPreset* Owner, FName NewControllerName, const FGuid& EntityId);` — Logic callbacks
- L131 _private prototype_ `void OnControllerRemoved(URemoteControlPreset* Owner, const FGuid& EntityId);`
- L132 _private prototype_ `void OnControllerRenamed(URemoteControlPreset* Owner, FName OldControllerLabel, FName NewControllerLabel);`
- L133 _private prototype_ `void OnControllerModified(URemoteControlPreset* Owner, const TSet<FGuid>& ModifiedControllerIds);`
- L136 _private prototype_ `void OnConnectionClosedCallback(FGuid ClientId);` — Callback when a websocket connection was closed. Let us clean out registrations
- L139 _private prototype_ `void OnEndFrame();` — End of frame callback to send cached property changed, preset changed messages
- L142 _private prototype_ `void TimeOutTransactions();` — Check if any transactions have timed out and end them.
- L145 _private prototype_ `void ProcessChangedControllers();` — If controllers have changed during the frame, send out notifications to listeners
- L148 _private prototype_ `void ProcessAddedControllers();` — If a new controller has been added during the frame, send out notifications to listeners
- L151 _private prototype_ `void ProcessRemovedControllers();` — If controllers has been removed during the frame, send out notifications to listeners
- L154 _private prototype_ `void ProcessRenamedControllers();` — If a controller has been renamed during the frame, snd out notifications to listeners
- L157 _private prototype_ `void ProcessChangedProperties();` — If properties have changed during the frame, send out notifications to listeners
- L160 _private prototype_ `void ProcessChangedActorProperties();` — If an exposed actor's properties have changed during the frame, send out notifications to listeners
- L163 _private prototype_ `void ProcessAddedProperties();` — If new properties were exposed to a preset, send out notifications to listeners
- L166 _private prototype_ `void ProcessRemovedProperties();` — If properties were removed from a preset, send out notifications to listeners
- L169 _private prototype_ `void ProcessRenamedFields();` — If fields were renamed, send out notifications to listeners
- L172 _private prototype_ `void ProcessModifiedMetadata();` — If metadata was modified on a preset, notify listeners.
- L175 _private prototype_ `void ProcessModifiedPresetLayouts();` — If a preset layout is modified, notify listeners.
- L178 _private prototype_ `void ProcessActorChanges();` — If actors were added/removed/renamed, notify listeners.
- L187 _private prototype_ `void GatherActorChangesForClass(UClass* ActorClass, TMap<FString, FRCActorsChangedData>& OutChangesByClassPath, TMap<FGuid, TArray<FString>>& OutClientsToNotify);` — Gather all the changes in the last frame for an actor class. @param ActorClass The class of actor for which to gather changes. @param OutChangesByClassPath A map from class path to data about changes to actors of that class. @param OutClientsToNotify A map from client ID to class paths with actor changes the client cares about.
- L196 _private prototype_ `void GatherActorChangesForDeletedClass(const FDeletedActorsData* DeletedActorsData, TMap<FString, FRCActorsChangedData>& OutChangesByClassPath, TMap<FGuid, TArray<FString>>& OutClientsToNotify);` — Gather all the changes in the last frame about an actor class that has already been deleted. @param DeletedActorsData Data about the class and actors that have been deleted. @param OutChangesByClassPath A map from class path to data about changes to actors of that class. @param OutClientsToNotify A map from client ID to class paths with actor changes the client cares about.
- L202 _private prototype_ `void BroadcastToPresetListeners(const FGuid& TargetPresetId, const TArray<uint8>& Payload);` — Send a payload to all clients bound to a certain preset. @note: TargetPresetName must be in the PresetNotificationMap.
- L207 _private prototype_ `bool ShouldProcessEventForPreset(const FGuid& PresetId) const;` — Returns whether an event targeting a particular preset should be processed.
- L212 _private prototype_ `bool WritePropertyChangeEventPayload(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedPropertyIds, int64 InSequenceNumber, TArray<uint8>& OutBuffer);` — Write the provided list of events to a buffer.
- L221 _private prototype_ `void SendBoolProperties(URemoteControlPreset* InPreset, const FGuid& InTargetClientId, const TSet<FGuid>& InModifiedPropertyIds, int64 InSequenceNumber);` — Send a message for each boolean property. This is needed because multiple booleans have problems with the common workflow. @param InPreset The current preset @param InTargetClientId Client Id to send the message @param InModifiedPropertyIds Set of modified properties already divided by type @param InSequenceNumber SequenceNumber of the client
- L226 _private prototype_ `bool WriteControllerChangeEventPayload(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedControllerIds, int64 InSequenceNumber, TArray<uint8>& OutBuffer);` — Write the provided list of controller events to a buffer.
- L231 _private prototype_ `bool WriteActorPropertyChangePayload(URemoteControlPreset* InPreset, const TMap<FRemoteControlActor, TArray<FRCObjectReference>>& InModifications, FMemoryWriter& InWriter);` — Write the provided list of actor modifications to a buffer.
- L236 _private prototype_ `void OnActorAdded(AActor* Actor);` — Called when an actor is added to the current world.
- L241 _private prototype_ `void OnActorDeleted(AActor* Actor);` — Called when an actor is deleted from the current world.
- L246 _private prototype_ `void OnWorldDestroyed(UWorld* World);` — Called when a world is destroyed.
- L251 _private prototype_ `void OnActorListChanged();` — Called when an untracked change to the actor list happens in the editor.
- L256 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, struct FPropertyChangedEvent& Event);` — Called when an object's property is changed in the editor. Used to detect name changes on subscribed actors.
- L261 _private prototype_ `void OnObjectTransacted(UObject* Object, const class FTransactionObjectEvent& TransactionEvent);` — Called when an object is affected by an editor transaction. Used to detect undo/redo of creating/deleting subscribed actors.
- L267 _private prototype_ `void HandleTransactionStateChanged(const FTransactionContext& InTransactionContext, const ETransactionStateEventType InTransactionState);` — Called when the state of an editor transaction changes.
- L273 _private prototype_ `void HandleTransactionEnded(const FGuid& TransactionGuid);` — Handle a transaction ending (either cancelled or finalized).
- L278 _private prototype_ `void StartWatchingActor(AActor* Actor, UClass* WatchedClass);` — Start watching an actor because it's a member of the given class.
- L284 _private prototype_ `void StopWatchingActor(AActor* Actor, UClass* WatchedClass);` — Stop watching an actor because it's a member of the given class. This should only be called if nobody is watching for this class anymore.
- L289 _private prototype_ `void UpdateWatchedActorName(AActor* Actor, FWatchedActorData& ActorData);` — Update our cache of watched actor's name and notify any subscribers.
- L294 _private prototype_ `void UnregisterClientForActorClass(const FGuid& ClientId, TSubclassOf<AActor> ActorClass);` — Unregister a client from messages about the given actor class.
- L299 _private prototype_ `void UpdateSequenceNumber(const FGuid& ClientId, int64 NewSequenceNumber);` — Update the sequence number for a client when a new one is received.
- L304 _private prototype_ `int64 GetSequenceNumber(const FGuid& ClientId) const;` — Get the current sequence number for a client.
- L312 _private prototype_ `bool ContributeToTransaction(const FGuid& ClientId, int32 TransactionId);` — Indicate that a client is going to contribute to the transaction with the given ID. This should be called whenever a change is made that will be part of the transaction, not just at the start. Returns true if the client can contribute to a transaction with that ID.
- L317 _private prototype_ `void EndClientTransaction(const FGuid& ClientId, int32 TransactionId);` — End the transaction with the given ID for the client with the given ID.
- L322 _private prototype_ `FGuid GetTransactionGuid(const FGuid& ClientId, int32 TransactionId) const;` — Converts a client's transaction ID to its editor internal GUID.
- L327 _private prototype_ `int32 GetClientTransactionId(const FGuid& ClientId, const FGuid& TransactionGuid) const;` — Converts an internal transaction GUID to the ID used by the given client to refer to it.
- L333 _private member_ `static const int64 DefaultSequenceNumber;` — Default sequence number for a client that hasn't reported one yet.
- L336 _private member_ `static const int32 InvalidTransactionId;` — Client transaction ID for a transaction that doesn't exist.
- L339 _private typedef_ `typedef TMap<TWeakObjectPtr<UClass>, FWatchedClassData, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UClass>, FWatchedClassData>> FActorNotificationMap;` — Map type from class to Guids of clients listening for changes to actors of that class.
- L342 _private typedef_ `typedef TMap<TWeakObjectPtr<UClass>, TArray<TWeakObjectPtr<AActor>>, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UClass>, TArray<TWeakObjectPtr<AActor>>>> FChangedActorMap;` — Map type from class to array of actors of that class that have changed recently.
- L345 _private typedef_ `typedef TMap<TWeakObjectPtr<UClass>, FDeletedActorsData, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UClass>, FDeletedActorsData>> FDeletedActorMap;` — Map type from class to data about actors of that class that have been deleted recently.
- L348 _private member_ `FRCWebSocketServer* Server = nullptr;` — Web Socket server.
- L350 _private member_ `TArray<TUniquePtr<FRemoteControlWebsocketRoute>> Routes;`
- L353 _private member_ `TMap<FGuid, TArray<FGuid>> PresetNotificationMap;` — All websockets connections associated to a preset notifications
- L356 _private member_ `FActorNotificationMap ActorNotificationMap;` — All websocket client IDs associated with an actor class.
- L366 _private member_ `TMap<FGuid, FRCClientConfig> ClientConfigMap;` — Holds client-specific config if any.
- L369 _private member_ `TMap<FGuid, int64> ClientSequenceNumbers;` — The largest sequence number received from each client.
- L372 _private member_ `TMap<FGuid, TMap<FGuid, TSet<FGuid>>> PerFrameModifiedProperties;` — Properties that changed for a frame, per preset.
- L378 _private member_ `TSet<FGuid> PropertiesManuallyNotifiedThisFrame;` — List of properties modified remotely this frame, used to not trigger a change notification after a post edit change for a property that was modified remotely.
- L381 _private member_ `TMap<FGuid, TMap<FGuid, TMap<FRemoteControlActor, TArray<FRCObjectReference>>>> PerFrameActorPropertyChanged;` — Properties that changed on an exposed actor for a given client, for a frame, per preset.
- L384 _private member_ `TMap<FGuid, TArray<FGuid>> PerFrameAddedProperties;` — Properties that were exposed for a frame, per preset
- L387 _private member_ `TMap<FGuid, TTuple<TArray<FGuid>, TArray<FName>>> CacheUndoRedoAddedRemovedProperties;` — Cache used during Undo/Redo for the Remove to get correctly the Label
- L390 _private member_ `TMap<FGuid, TTuple<TArray<FGuid>, TArray<FName>>> PerFrameRemovedProperties;` — Properties that were unexposed for a frame, per preset
- L393 _private member_ `TMap<FGuid, TArray<TTuple<FName, FName>>> PerFrameRenamedFields;` — Fields that were renamed for a frame, per preset
- L396 _private member_ `TMap<FGuid, TArray<FGuid>> PerFrameAddedControllers;` — Controllers that were Added for a frame, per preset
- L399 _private member_ `TMap<FGuid, TTuple<TArray<FGuid>, TArray<FName>>> PerFrameRemovedControllers;` — Controllers that were Removed for a frame, per preset
- L402 _private member_ `TMap<FGuid, TArray<TTuple<FName, FName>>> PerFrameRenamedControllers;` — Controllers that were Renamed for a frame, per preset
- L405 _private member_ `TMap<FGuid, TMap<FGuid, TSet<FGuid>>> PerFrameModifiedControllers;` — Controllers that were Modified for a frame, per preset
- L408 _private member_ `FChangedActorMap PerFrameActorsAdded;` — Actors that were added for a frame, per watched class.
- L411 _private member_ `FChangedActorMap PerFrameActorsRenamed;` — Actors that were renamed for a frame, per watched class.
- L414 _private member_ `FDeletedActorMap PerFrameActorsDeleted;` — Actors that were removed for a frame, per watched class.
- L417 _private member_ `TSet<FGuid> PerFrameModifiedMetadata;` — Presets that had their metadata modified for a frame
- L420 _private member_ `TSet<FGuid> PerFrameModifiedPresetLayouts;` — Presets that had their layout modified for a frame.
- L423 _private member_ `TMap<FGuid, TArray<FGuid>> TransientPresetAutoDestroyClients;` — Map from transient preset ID to clients which, when all disconnected, will automatically destroy the preset.
- L426 _private member_ `TMap<FGuid, TMap<FGuid, FDateTime>> ClientsByTransactionGuid;` — Map from transasction ID to a map of (contributing client ID, time of last contribution to the transaction).
- L429 _private member_ `TMap<FGuid, TMap<FGuid, int32>> TransactionIdsByClientId;` — Map from client ID to pairs of editor GUID/client ID used to refer to the transaction.
- L432 _private member_ `const FGuid& ActingClientId;` — Holds the ID of the client currently making a request. Used to prevent sending back notifications to it.
- L435 _private member_ `int32 PropertyNotificationFrameCounter = 0;` — Frame counter for delaying property change checks.
- L438 _private member_ `FDelegateHandle OnActorAddedHandle;` — Handle for when an actor is added to the world.
- L441 _private member_ `FDelegateHandle OnActorDeletedHandle;` — Handle for when an actor is deleted from the world.
- L444 _private member_ `FDelegateHandle OnActorListChangedHandle;` — Handle for when the list of actors changes.
- L447 _private member_ `FDelegateHandle OnWorldDestroyedHandle;` — Handle for when a world is destroyed.
- L453 _private member_ `TMap<AActor*, FWatchedActorData> WatchedActors;` — Actors that we are actively watching to send events to subscribers. The key is not a weak pointer, so it shouldn't be accessed in case it's stale. Use the value instead.

#### struct `FWebSocketMessageHandler::FWatchedActorData`  
`struct FWatchedActorData`  
_L44-56_
- desc: Data about a watched actor so we know who to notify and what to send if the actor is garbage-collected before we know it's been deleted.
- L46 _public function_ `FWatchedActorData(AActor* InActor) : Description(InActor)`
- L52 _public member_ `FRCActorDescription Description;` — Description of the actor.
- L55 _public member_ `TArray<TWeakObjectPtr<UClass>> WatchedClasses;` — Which classes this actor is a member of that are causing it to be watched.

#### struct `FWebSocketMessageHandler::FWatchedClassData`  
`struct FWatchedClassData`  
_L61-68_
- desc: Data about a class being watched by one or more clients.
- L64 _public member_ `TArray<FGuid> Clients;` — The clients watching this class.
- L67 _public member_ `FString CachedPath;` — The cached path name of the class so we can still send events about it even if it gets deleted.

#### struct `FWebSocketMessageHandler::FDeletedActorsData`  
`struct FDeletedActorsData`  
_L73-80_
- desc: Data about actors of a shared class that have been deleted recently.
- L76 _public member_ `FString ClassPath;` — The cached path name of the shared class so we can still send events about it even if it gets deleted.
- L79 _public member_ `TArray<FRCActorDescription> Actors;` — Deleted actors, stored as descriptions in case the actor is garbage collected before its name and path can be collected.

#### struct `FWebSocketMessageHandler::FRCClientConfig`  
`struct FRCClientConfig`  
_L359-363_
- desc: Configuration for a given client related to how events should be handled.
- L362 _public member_ `bool bIgnoreRemoteChanges = false;` — Whether the client ignores events that were initiated remotely.

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Public/IWebRemoteControlModule.h` (Public)


#### class `IWebRemoteControlModule`  
`class IWebRemoteControlModule : public IModuleInterface`  
_L18-102_
- inherits: `IModuleInterface`
- desc: A Remote Control module that allows exposing objects and properties from the editor.
- L30 _public prototype_ `virtual FDelegateHandle RegisterRequestPreprocessor(FHttpRequestHandler RequestPreprocessor) = 0;` — Register a request preprocessor. Useful for cases where you want to drop or handle incoming requests before they are handled the the web remote control module. @param RequestPreprocessor The function called to process the incoming request. @return FDelegateHandle The handle to the delegate, used for unregistering preprocessors. @note The request preprocessor should return false if the request should pass through, and true if the request has been handled by the preprocessor. If the request is handled by the preprocessor, you must call the OnComplete callback.
- L36 _public prototype_ `virtual void UnregisterRequestPreprocessor(const FDelegateHandle& RequestPreprocessorHandle) = 0;` — Unregister a request preprocessor. @param RequestPreprocessorHandle The handle to the preprocessor delegate.
- L41 _public prototype_ `virtual FOnWebServerStarted& OnHttpServerStarted() = 0;` — Event triggered when the http server starts.
- L46 _public prototype_ `virtual FSimpleMulticastDelegate& OnHttpServerStopped() = 0;` — Event triggered when the http server stops.
- L51 _public prototype_ `virtual bool IsHttpServerRunning() = 0;` — Returns whether the http server is currently running.
- L57 _public prototype_ `virtual FOnWebServerStarted& OnWebSocketServerStarted() = 0;` — Event triggered when the websocket server starts.
- L62 _public prototype_ `virtual FSimpleMulticastDelegate& OnWebSocketServerStopped() = 0;` — Event triggered when the websocket server stops.
- L67 _public prototype_ `virtual bool IsWebSocketServerRunning() = 0;` — Returns whether the websocket server is currently running.
- L72 _public prototype_ `virtual FOnWebSocketConnectionOpened& OnWebSocketConnectionOpened() = 0;` — Event triggered when a connection to the websocket server is opened.
- L77 _public prototype_ `virtual FOnWebSocketConnectionClosed& OnWebSocketConnectionClosed() = 0;` — Event triggered when a connection to the websocket server is closed.
- L83 _public prototype_ `virtual void RegisterWebsocketRoute(const FRemoteControlWebsocketRoute& Route) = 0;` — Register a websocket route. @param The route to register.
- L89 _public prototype_ `virtual void UnregisterWebsocketRoute(const FRemoteControlWebsocketRoute& Route) = 0;` — Unregister a websocket route. @param The route to unregister.
- L96 _public prototype_ `virtual void SendWebsocketMessage(const FGuid& InTargetClientId, const TArray<uint8>&InUTF8Payload) = 0;` — Send a message through the websocket server. @param InTargetClientId ID of the client to send the message to. @param InUTF8Payload Payload to send with the message.
- L101 _public prototype_ `virtual void SetExternalRemoteWebSocketLoggerConnection(TSharedPtr<class INetworkingWebSocket> WebSocketLoggerConnection) = 0;` — Set Remote Web Socket Logger

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebServerStarted, uint32 );`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebServerStarted, uint32 );`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionOpened, FGuid );`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionOpened, FGuid );`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionClosed, FGuid );`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionClosed, FGuid );`

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Public/RemoteControlWebsocketRoute.h` (Public)


#### struct `FRemoteControlWebSocketMessage`  
`struct FRemoteControlWebSocketMessage`  
_L7-15_
- L9 _public member_ `FString MessageName;`
- L10 _public member_ `int32 MessageId = -1;`
- L11 _public member_ `FGuid ClientId;`
- L12 _public member_ `TSharedPtr<class FInternetAddr> PeerAddress;`
- L13 _public member_ `TArrayView<uint8> RequestPayload;`
- L14 _public member_ `TMap<FString, TArray<FString>> Header;`

#### struct `FRemoteControlWebsocketRoute`  
`struct FRemoteControlWebsocketRoute`  
_L19-36_
- L21 _public function_ `FRemoteControlWebsocketRoute(const FString& InRouteDescription, const FString& InMessageName, const FWebSocketMessageDelegate& InDelegate) : RouteDescription(InRouteDescription) , MessageName(InMessageName) , Delegate(InDelegate)`
- L28 _public member_ `FString RouteDescription;` — A description of how the route should be used.
- L30 _public member_ `FString MessageName;` — The message handled by this route.
- L32 _public member_ `FWebSocketMessageDelegate Delegate;` — The handler called when the route is accessed.

#### struct `FBlockDelimiters`  
`struct FBlockDelimiters`  
_L38-45_
- L40 _public member_ `int64 BlockStart = -1;`
- L41 _public member_ `int64 BlockEnd = -1;`
- L44 _public function_ `int64 GetBlockSize() const` — Get the size of current block

#### struct `FRCRequest`  
`struct FRCRequest`  
_L51-81_
- reflection: `USTRUCT()`
- desc: Holds a request made to the remote control server.
- L55 _public prototype_ `virtual ~FRCRequest() = default;`
- L57 _public function_ `TMap<FString, FBlockDelimiters>& GetStructParameters()`
- L62 _public function_ `FBlockDelimiters& GetParameterDelimiters(const FString& ParameterName)`
- L68 _public member_ `FString Passphrase;` — `UPROPERTY()`
- L71 _public member_ `TArray<uint8> TCHARBody;` — Holds the request's TCHAR payload.
- L74 _protected function_ `void AddStructParameter(FString ParameterName)`
- L80 _protected member_ `TMap<FString, FBlockDelimiters> StructParameters;` — Holds the start and end of struct parameters

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FWebSocketMessageDelegate, const FRemoteControlWebSocketMessage& );`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FWebSocketMessageDelegate, const FRemoteControlWebSocketMessage& );`
- L34 _function_ `friend uint32 GetTypeHash(const FRemoteControlWebsocketRoute& Route)`
- L35 _function_ `friend bool operator==(const FRemoteControlWebsocketRoute& LHS, const FRemoteControlWebsocketRoute& RHS)`

### `Plugins/VirtualProduction/RemoteControl/Source/WebRemoteControl/Public/WebRemoteControlUtils.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace WebRemoteControlUtils`
- L21 _prototype_ `void ConvertToTCHAR(TConstArrayView<uint8> InUTF8Payload, TArray<uint8>& OutTCHARPayload);` (scope `WebRemoteControlUtils`) — Convert a UTF-8 payload to a TCHAR payload. @param InUTF8Payload The UTF-8 payload in binary format. @param OutTCHARPayload The converted TCHAR output in binary format.
- L28 _prototype_ `void ConvertToUTF8(TConstArrayView<uint8> InTCHARPayload, TArray<uint8>& OutUTF8Payload);` (scope `WebRemoteControlUtils`) — Convert a TCHAR payload to UTF-8. @param InTCHARPayload The TCHAR payload in binary format. @param OutUTF8Payload The converted UTF-8 output in binary format.
- L35 _prototype_ `void ConvertToUTF8(const FString& InString, TArray<uint8>& OutUTF8Payload);` (scope `WebRemoteControlUtils`) — Convert a FString to UTF-8. @param InString The string to be converted. @param OutUTF8Payload the converted UTF-8 output in binary format.
- L40 _prototype_ `TSharedRef<IStructSerializerBackend> CreateJsonSerializerBackend(FMemoryWriter& Writer);` (scope `WebRemoteControlUtils`) — Create a JSON serializer backend for use with other WebRemoteControl functions.
- L45 _prototype_ `TSharedRef<IStructDeserializerBackend> CreateJsonDeserializerBackend(FMemoryReaderView& Reader);` (scope `WebRemoteControlUtils`) — Create a JSON deserializer backend for use with other WebRemoteControl functions.
- L53 _function_ `template <typename MessageType> void SerializeMessage(const MessageType& InMessageObject, TArray<uint8>& OutMessagePayload)` (scope `WebRemoteControlUtils`) — Serialize a message object into a UTF-8 Payload. @param InMessageObject the object to serialize. @param OutResponsePayload the resulting UTF-8 payload.
- L69 _function_ `template <typename MessageType> [[nodiscard]] bool DeserializeMessage(TConstArrayView<uint8> InTCHARPayload, MessageType& OutDeserializedMessage)` (scope `WebRemoteControlUtils`) — Deserialize a message payload into a UStruct. @param InTCHARPayload The json payload to deserialize. @param The structure to serialize using the message's content. @return Whether the deserialization was successful.
