# Plugins / RemoteControlInterception

- module root: `Plugins/VirtualProduction/RemoteControlInterception/Source/RemoteControlInterception`
- headers: 3; symbols: 80
- symbol kinds: class=5, enum=4, enumerator=14, function=19, member=22, prototype=12, struct=4
- PrivateDependencyModuleNames: Cbor, Core, CoreUObject, Engine, Serialization

### `Plugins/VirtualProduction/RemoteControlInterception/Source/RemoteControlInterception/Private/RemoteControlInterceptionModule.h` (Private)


#### class `FRemoteControlInterceptionModule`  
`class FRemoteControlInterceptionModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- desc: RemoteControlInterception module implementation
- L15 _public prototype_ `FRemoteControlInterceptionModule() = default;`
- L16 _public prototype_ `virtual ~FRemoteControlInterceptionModule() = default;`

### `Plugins/VirtualProduction/RemoteControlInterception/Source/RemoteControlInterception/Public/IRemoteControlInterceptionCommands.h` (Public)


#### enum `ERCIResponse`  
`enum class ERCIResponse : uint8`  
_L15-21_
- desc: Interception flags that define how RemoteControl should behave after a message was intercepted.
- L18 _public enumerator_ `Apply` — Set/reset property on RemoteControl side even though the message was intercepted
- L20 _public enumerator_ `Intercept` — Do not process the RC command on RemoteControl side. An interceptor will decide what to do with it.

#### enum `ERCIPayloadType`  
`enum class ERCIPayloadType : uint8`  
_L26-30_
- desc: Payload serialization type (proxy type for ERCPayloadType to avoid RC module dependency)
- L28 _public enumerator_ `Cbor`
- L29 _public enumerator_ `Json`

#### enum `ERCIAccess`  
`enum class ERCIAccess : uint8`  
_L35-42_
- desc: Remote property access mode  (proxy type for ERCAccess to avoid RC module dependency)
- L37 _public enumerator_ `NO_ACCESS`
- L38 _public enumerator_ `READ_ACCESS`
- L39 _public enumerator_ `WRITE_ACCESS`
- L40 _public enumerator_ `WRITE_TRANSACTION_ACCESS`
- L41 _public enumerator_ `WRITE_MANUAL_TRANSACTION_ACCESS`

#### enum `ERCIModifyOperation`  
`enum class ERCIModifyOperation : uint8`  
_L47-54_
- desc: Type of operation to perform when setting a remote property's value (proxy type for ERCModifyOperation to avoid module dependency)
- L49 _public enumerator_ `EQUAL`
- L50 _public enumerator_ `ADD`
- L51 _public enumerator_ `SUBTRACT`
- L52 _public enumerator_ `MULTIPLY`
- L53 _public enumerator_ `DIVIDE`

#### class `IRemoteControlInterceptionCommands`  
`template <class TResponseType> class IRemoteControlInterceptionCommands`  
_L61-103_
- desc: The list of remote control commands available for interception
- L64 _public prototype_ `virtual ~IRemoteControlInterceptionCommands() = default;`
- L74 _public prototype_ `virtual TResponseType SetObjectProperties(FRCIPropertiesMetadata& InObjectProperties) = 0;` — SetObjectProperty command to process @param InObjectProperties - Metadata of the object and its properties that are going to be modified @return - Return types depends on the interface implementation (template parameter)
- L84 _public prototype_ `virtual TResponseType ResetObjectProperties(FRCIObjectMetadata& InObject) = 0;` — ResetObject command to process @param InObject - Metadata of the object and its properties that are going to be modified @return - Return types depends on the interface implementation (template parameter) @param OutResponse - interception response flag (not required for the handlers)
- L93 _public prototype_ `virtual TResponseType InvokeCall(FRCIFunctionMetadata& InFunction) = 0;` — InvokeCall command to process @param InFunction - Metadata of the UFunction that are going to be modified @return - Return types depends on the interface implementation (template parameter)
- L102 _public prototype_ `virtual TResponseType SetPresetController(FRCIControllerMetadata& InController) = 0;` — SetPresetController command @param InController - Metadata of the controller being manipulated @return - Return types depends on the interface implementation (template parameter)

#### struct `FRCIObjectMetadata`  
`struct FRCIObjectMetadata`  
_L109-174_
- desc: Object metadata for custom interception/replication/processing purposes
- L112 _public function_ `FRCIObjectMetadata()`
- L115 _public function_ `FRCIObjectMetadata(const FString& InObjectPath, const FString& InPropertyPath, const FString& InPropertyPathInfo, const ERCIAccess InAccess) : ObjectPath(InObjectPath) , PropertyPath(InPropertyPath) , PropertyPathInfo(InPropertyPathInfo) , Access(InAccess)`
- L124 _public prototype_ `virtual ~FRCIObjectMetadata() = default;`
- L128 _public function_ `const FName& GetUniquePath() const` — Get Unique Path for Object metadata
- L132 _public function_ `virtual bool IsValid() const` — Returns true if reference is valid
- L156 _public member_ `FString ObjectPath;` — Owner object path
- L159 _public member_ `FString PropertyPath;` — FProperty path
- L162 _public member_ `FString PropertyPathInfo;` — Full property path, including path to inner structs, arrays, maps, etc
- L165 _public member_ `ERCIAccess Access = ERCIAccess::NO_ACCESS;` — Property access type
- L169 _public member_ `static constexpr TCHAR const* Name = TEXT("RCI` — Structure Name
- L173 _private member_ `FName UniquePath;` — Object Path + Property Path

#### struct `FRCIPropertiesMetadata`  
`struct FRCIPropertiesMetadata : public FRCIObjectMetadata`  
_L180-236_
- inherits: `FRCIObjectMetadata`
- desc: Object properties metadata for custom interception/replication/processing purposes
- L183 _public prototype_ `FRCIPropertiesMetadata() = default;`
- L185 _public function_ `FRCIPropertiesMetadata(const FString& InObjectPath, const FString& InPropertyPath, const FString& InPropertyPathInfo, const ERCIAccess InAccess, const ERCIPayloadType InPayloadType, const ERCIModifyOperation InOperation, const TArray<uint8>& InPayload) : FRCIObjectMetadata(InObjectPath, InPropertyPath, InPropertyPathInfo, InAccess) , PayloadType(InPayloadType) , Operation(InOperation) , Payload(InPayload)`
- L192 _public prototype_ `virtual ~FRCIPropertiesMetadata() = default;`
- L196 _public function_ `virtual bool IsValid() const override`
- L225 _public member_ `ERCIPayloadType PayloadType = ERCIPayloadType::Json;` — Intercepted payload type
- L228 _public member_ `ERCIModifyOperation Operation;` — Type of operation to perform on the property
- L231 _public member_ `const TArray<uint8> Payload;` — Property payload to intercept
- L235 _public member_ `static constexpr TCHAR const* Name = TEXT("RCI` — Structure Name

#### struct `FRCIFunctionMetadata`  
`struct FRCIFunctionMetadata`  
_L241-312_
- desc: UFunction metadata for custom interception/replication/processing purposes
- L244 _public function_ `FRCIFunctionMetadata() : bGenerateTransaction(false) , PayloadType(ERCIPayloadType::Json)`
- L249 _public function_ `FRCIFunctionMetadata(const FString& InObjectPath, const FString& InFunctionPath, const bool bInGenerateTransaction, const ERCIPayloadType InPayloadType, const TArray<uint8>& InPayload) : ObjectPath(InObjectPath) , FunctionPath(InFunctionPath) , bGenerateTransaction(bInGenerateTransaction) , PayloadType(InPayloadType) , Payload(InPayload)`
- L261 _public function_ `const FName& GetUniquePath() const` — Get Unique Path for Function metadata
- L265 _public function_ `bool IsValid() const` — Returns true if reference is valid
- L291 _public member_ `FString ObjectPath;` — Owner object path
- L294 _public member_ `FString FunctionPath;` — UFunction object path
- L297 _public member_ `bool bGenerateTransaction;` — Should the call generate transaction
- L300 _public member_ `ERCIPayloadType PayloadType;` — Intercepted payload type
- L303 _public member_ `const TArray<uint8> Payload;` — Property payload to intercept
- L307 _public member_ `static constexpr TCHAR const* Name = TEXT("RCI` — Structure Name
- L311 _private member_ `FName UniquePath;` — Object Path + Function Path

#### struct `FRCIControllerMetadata`  
`struct FRCIControllerMetadata`  
_L317-379_
- desc: Controller properties for interception of Controller get/set operations
- L321 _public prototype_ `FRCIControllerMetadata() = default;`
- L323 _public function_ `FRCIControllerMetadata(const FName InPreset, const FName InController, const TArray<uint8>& InPayload) : Preset(InPreset) , Controller(InController) , Payload(InPayload)`
- L333 _public function_ `const FName& GetUniquePath() const` — Get Unique Path for Controller metadata
- L339 _public function_ `bool IsValid() const` — Returns true if reference is valid
- L363 _public member_ `FName Preset;` — Name of the Remote Control Preset holding the Controller
- L366 _public member_ `FName Controller;` — The Controller being manipulated in the Preset
- L369 _public member_ `const TArray<uint8> Payload;` — Request Payload
- L374 _public member_ `static constexpr TCHAR const* Name = TEXT("FRC` — Structure Name - Used by replication event handlers to deserialize event data into the correct structure for a given event
- L378 _private member_ `FName UniquePath;` — Preset Name + Controller Name

#### Free symbols / members of external scopes

- L145 _function_ `friend FArchive& operator<<(FArchive& Ar, FRCIObjectMetadata& Interception)` — FRCObjectMetadata serialization @param Ar       - The archive @param Interception - Instance to serialize/deserialize @return FArchive instance.
- L210 _function_ `friend FArchive& operator<<(FArchive& Ar, FRCIPropertiesMetadata& Instance)` — FRCObjectPropertiesMetadata serialization @param Ar       - The archive @param Instance - Instance to serialize/deserialize @return FArchive instance.
- L278 _function_ `friend FArchive& operator<<(FArchive& Ar, FRCIFunctionMetadata& Interception)` — FRCObjectMetadata serialization @param Ar				- The archive @param Interception	- Instance to serialize/deserialize @return FArchive instance.
- L352 _function_ `friend FArchive& operator<<(FArchive& Ar, FRCIControllerMetadata& Interception)` — FRCIControllerMetadata serialization @param Ar				- The archive @param Interception	- Instance to serialize/deserialize @return FArchive instance.

### `Plugins/VirtualProduction/RemoteControlInterception/Source/RemoteControlInterception/Public/IRemoteControlInterceptionFeature.h` (Public)


#### class `IRemoteControlInterceptionFeature`  
`template <class TResponseType> class IRemoteControlInterceptionFeature : public IModularFeature , public IRemoteControlInterceptionCommands<TResponseType>`  
_L15-23_
- inherits: `IModularFeature,IRemoteControlInterceptionCommands<TResponseType>`
- desc: Base RCI feature interface
- L22 _public prototype_ `virtual ~IRemoteControlInterceptionFeature() = default;`

#### class `IRemoteControlInterceptionFeatureInterceptor`  
`class IRemoteControlInterceptionFeatureInterceptor : public IRemoteControlInterceptionFeature<ERCIResponse>`  
_L29-38_
- inherits: `IRemoteControlInterceptionFeature<ERCIResponse>`
- desc: RCI command interceptor feature
- L33 _public function_ `static FName GetName()`

#### class `IRemoteControlInterceptionFeatureProcessor`  
`class IRemoteControlInterceptionFeatureProcessor : public IRemoteControlInterceptionFeature<void>`  
_L44-53_
- inherits: `IRemoteControlInterceptionFeature<void>`
- desc: RCI command processor feature
- L48 _public function_ `static FName GetName()`
