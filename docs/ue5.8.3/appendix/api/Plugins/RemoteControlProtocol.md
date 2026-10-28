# Plugins / RemoteControlProtocol

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol`
- headers: 5; symbols: 102
- symbol kinds: class=4, enum=1, enumerator=3, function=11, macro=1, member=17, namespace=1, prototype=51, struct=2, typedef=4, variable=7
- PrivateDependencyModuleNames: Engine, RemoteControl, RemoteControlCommon
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol/Private/RemoteControlProtocolModule.h` (Private)


#### class `FRemoteControlProtocolModule`  
`class FRemoteControlProtocolModule : public IRemoteControlProtocolModule`  
_L11-41_
- inherits: `IRemoteControlProtocolModule`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public function_ `virtual int32 GetProtocolNum() const override`
- L21 _public prototype_ `virtual TArray<FName> GetProtocolNames() const override;`
- L22 _public prototype_ `virtual TSharedPtr<IRemoteControlProtocol> GetProtocolByName(FName InProtocolName) const override;`
- L23 _public prototype_ `virtual bool AddProtocol(FName InProtocolName, TSharedRef<IRemoteControlProtocol> InProtocol) override;`
- L24 _public prototype_ `virtual void RemoveProtocol(FName InProtocolName, TSharedRef<IRemoteControlProtocol> InProtocol) override;`
- L25 _public prototype_ `virtual void EmptyProtocols() override;`
- L26 _public function_ `virtual bool IsRCProtocolsDisable() const override`
- L27 _public prototype_ `virtual void ApplyProtocolBindings(URemoteControlPreset* InPreset) const override;`
- L28 _public prototype_ `virtual void UnapplyProtocolBindings(URemoteControlPreset* InPreset) const override;`
- L33 _private prototype_ `void OnPostLoadRemoteControlPreset(URemoteControlPreset* InPreset) const;` — Called when remote control preset loaded
- L37 _private member_ `TMap<FName, TSharedRef<IRemoteControlProtocol>> Protocols;` — Map with all protocols
- L40 _private member_ `bool bRCProtocolsDisable = false;` — Prevents the Remote Control protocols from starting. Can be set from command line with -RCProtocolsDisable

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlProtocol, Log, All);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol/Public/IRemoteControlProtocol.h` (Public)


#### struct `FProtocolColumn`  
`struct FProtocolColumn`  
_L32-66_
- desc: Simple utility struct to represent a protocol column.
- L34 _public prototype_ `FProtocolColumn() = default;`
- L36 _public function_ `FProtocolColumn(const FName& InColumnName, const FText& InDisplayText, float InColumnSize) : ColumnName(InColumnName) , DisplayText(InDisplayText) , ColumnSize(InColumnSize)`
- L48 _public function_ `bool operator==(const FProtocolColumn& OtherColumn)`
- L53 _public function_ `bool operator==(const FProtocolColumn& OtherColumn) const`
- L59 _public member_ `FName ColumnName;` — Holds the name of the column.
- L62 _public member_ `FText DisplayText;` — Holds the display text of the column.
- L65 _public member_ `float ColumnSize;` — Holds the size of the column.

#### class `IRemoteControlProtocol`  
`class IRemoteControlProtocol : public TSharedFromThis<IRemoteControlProtocol>`  
_L76-139_
- inherits: `TSharedFromThis<IRemoteControlProtocol>`
- desc: Interface for remote control protocol
- L80 _public function_ `virtual ~IRemoteControlProtocol()` — Virtual destructor
- L83 _public prototype_ `virtual void Init() = 0;` — Add custom initializing of the protocol
- L92 _public prototype_ `virtual FRemoteControlProtocolEntityPtr CreateNewProtocolEntity(FProperty* InProperty, URemoteControlPreset* InOwner, FGuid InPropertyId) const = 0;` — Add the new protocol entity. That is created based on protocol specific script struct @param InProperty exposed property @param InOwner The preset that owns this protocol entity. @param InPresetName unique id of exposed property @return A shared pointer protocol entity struct on scope
- L95 _public prototype_ `virtual UScriptStruct* GetProtocolScriptStruct() const = 0;` — Get protocol specific Script Struct class
- L98 _public prototype_ `virtual FProperty* GetRangeInputTemplateProperty() const;` — Get range input template Property
- L104 _public prototype_ `virtual void Bind(FRemoteControlProtocolEntityPtr InEntityPtr) = 0;` — Bind the protocol entity to the protocol @param InEntityPtr protocol entity struct on scope pointer
- L110 _public prototype_ `virtual void Unbind(FRemoteControlProtocolEntityPtr InEntityPtr) = 0;` — Unbind the protocol entity from the protocol @param InEntityPtr protocol entity struct on scope pointer
- L113 _public prototype_ `virtual void UnbindAll() = 0;` — Unbind all protocol entities from the protocol
- L116 _public function_ `virtual void OnBeginFrame()` — Build to core engine delegated and called at the beginning of a frame
- L119 _public function_ `virtual void OnEndFrame()` — Build to core engine delegated and called at the end of a frame
- L128 _public prototype_ `virtual void QueueValue(const FRemoteControlProtocolEntityPtr InProtocolEntity, const double InProtocolValue) = 0;` — Queue protocol entity and value to apply for the protocol It stores only unique tick entities which should be apply next frame. Prevents from applying more then one entity for frame. @param InProtocolEntity Protocol Entity @param InProtocolValue Protocol Value
- L133 _public prototype_ `virtual FProtocolColumnPtr GetRegisteredColumn(const FName& ByColumnName) const = 0;` — Retrieves the column reference by its name.
- L136 _public prototype_ `virtual void GetRegisteredColumns(TSet<FName>& OutColumns) = 0;` — Retrieves the set of columns registered by this protocol.

#### Free symbols / members of external scopes

- L13 _typedef_ `using FRemoteControlProtocolEntityPtr = TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>>;`
- L14 _typedef_ `using FRemoteControlProtocolEntityWeakPtr = TWeakPtr<TStructOnScope<FRemoteControlProtocolEntity>>;`
- L18 _namespace_ `namespace ProtocolColumnConstants`
- L20 _variable_ `static float ColumnSizeMicro = 0.075f;` (scope `ProtocolColumnConstants`)
- L21 _variable_ `static float ColumnSizeMini = 0.15f;` (scope `ProtocolColumnConstants`)
- L22 _variable_ `static float ColumnSizeSmall = 0.21f;` (scope `ProtocolColumnConstants`)
- L23 _variable_ `static float ColumnSizeNormal = 0.3f;` (scope `ProtocolColumnConstants`)
- L24 _variable_ `static float ColumnSizeMedium = 0.5f;` (scope `ProtocolColumnConstants`)
- L25 _variable_ `static float ColumnSizeLarge = 0.8f;` (scope `ProtocolColumnConstants`)
- L26 _variable_ `static float ColumnSizeExtraLarge = 1.f;` (scope `ProtocolColumnConstants`)
- L43 _function_ `friend uint32 GetTypeHash(const FProtocolColumn& OtherColumn)`
- L68 _typedef_ `using FProtocolColumnPtr = TSharedPtr<FProtocolColumn>;`
- L69 _typedef_ `using FProtocolColumnRef = TSharedRef<FProtocolColumn>;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol/Public/IRemoteControlProtocolModule.h` (Public)


#### class `IRemoteControlProtocolModule`  
`class IRemoteControlProtocolModule : public IModuleInterface`  
_L15-65_
- inherits: `IModuleInterface`
- desc: A Remote Control Protocol module. That is base for all remote control protcols
- L24 _public function_ `static IRemoteControlProtocolModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public prototype_ `virtual int32 GetProtocolNum() const = 0;` — Get number of remote control protocols
- L34 _public prototype_ `virtual TArray<FName> GetProtocolNames() const = 0;` — Get array of all remote control protocol names
- L37 _public prototype_ `virtual TSharedPtr<IRemoteControlProtocol> GetProtocolByName(FName InProtocolName) const = 0;` — Get specific remote control protocol by given name
- L45 _public prototype_ `virtual bool AddProtocol(FName InProtocolName, TSharedRef<IRemoteControlProtocol> InProtocol) = 0;` — Register the protocol @param InProtocolName protocol name @param InProtocol protocol shared reference @return true if protocol added
- L52 _public prototype_ `virtual void RemoveProtocol(FName InProtocolName, TSharedRef<IRemoteControlProtocol> InProtocol) = 0;` — Unregister the protocol @param InProtocolName protocol name @param InProtocol protocol instance pointer
- L55 _public prototype_ `virtual void ApplyProtocolBindings(URemoteControlPreset* InPreset) const = 0;` — Applies all the protocol bindings found within the given preset
- L58 _public prototype_ `virtual void UnapplyProtocolBindings(URemoteControlPreset* InPreset) const = 0;` — Unapplies all the protocol bindings found within the given preset
- L61 _public prototype_ `virtual void EmptyProtocols() = 0;` — Unregister all protocols
- L64 _public prototype_ `virtual bool IsRCProtocolsDisable() const = 0;` — Whether protocol disabled

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol/Public/RemoteControlProtocol.h` (Public)


#### class `FRemoteControlProtocol`  
`class FRemoteControlProtocol : public IRemoteControlProtocol`  
_L16-68_
- inherits: `IRemoteControlProtocol`
- desc: Base class implementation for remote control protocol
- L19 _public prototype_ `FRemoteControlProtocol(FName InProtocolName);`
- L20 _public prototype_ `~FRemoteControlProtocol();`
- L23 _public prototype_ `virtual void Init() override;`
- L24 _public prototype_ `virtual FRemoteControlProtocolEntityPtr CreateNewProtocolEntity(FProperty* InProperty, URemoteControlPreset* InOwner, FGuid InPropertyId) const override;`
- L25 _public prototype_ `virtual void QueueValue(const FRemoteControlProtocolEntityPtr InProtocolEntity, const double InProtocolValue) override;`
- L26 _public prototype_ `virtual void OnBeginFrame() override;`
- L30 _public prototype_ `virtual FProtocolColumnPtr GetRegisteredColumn(const FName& ByColumnName) const override;`
- L32 _public prototype_ `virtual void GetRegisteredColumns(TSet<FName>& OutColumns) override;`
- L43 _public prototype_ `static TFunction<bool(FRemoteControlProtocolEntityWeakPtr InProtocolEntityWeakPtr)> CreateProtocolComparator(FGuid InPropertyId);` — Helper function for comparing the Protocol Entity with given Property Id inside returned lambda @param InPropertyId Property unique Id @return Lambda function with ProtocolEntityWeakPtr as argument
- L50 _protected function_ `virtual void RegisterColumns()` — Populates protocol specific columns.
- L56 _protected member_ `FName ProtocolName;` — Current Protocol Name
- L61 _protected member_ `TSet<FProtocolColumnPtr> RegisteredColumns;` — Holds a set of protocol specific columns.
- L67 _private member_ `TMap<FRemoteControlProtocolEntityPtr, double> EntityValuesToApply;` — Map of the entities and protocol values about to apply

#### Free symbols / members of external scopes

- L9 _macro_ `#define REGISTER_COLUMN(ColumnName, DisplayText, ColumnSize) RegisteredColumns.Add(MakeShared<FProtocolColumn>(ColumnName, DisplayText, ColumnSize));`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocol/Public/Signature/RCSignatureProtocolAction.h` (Public)


#### enum `ERCSignatureProtocolActionMappingSpace`  
`enum class ERCSignatureProtocolActionMappingSpace : uint8`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `Additive`
- L18 _public enumerator_ `Multiply`
- L19 _public enumerator_ `Absolute`

#### struct `FRCSignatureProtocolAction`  
`struct FRCSignatureProtocolAction : public FRCSignatureAction`  
_L23-76_
- reflection: `USTRUCT(DisplayName="Protocol Action")`
- inherits: `FRCSignatureAction`
- L28 _public prototype_ `virtual void Initialize(const FRCSignatureField& InField) override;`
- L29 _public prototype_ `virtual bool IsSupported(const FRCSignatureField& InField) const override;`
- L30 _public prototype_ `virtual bool Execute(const FRCSignatureActionContext& InContext) const override;`
- L32 _public prototype_ `virtual void PostEditChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged) override;`
- L33 _public prototype_ `virtual FRCSignatureActionIcon GetIcon() const override;`
- L37 _public prototype_ `void UpdateProtocolEntity();`
- L39 _public prototype_ `void UpdateMappingType();`
- L41 _public prototype_ `TSharedPtr<IRemoteControlProtocol> GetProtocol() const;`
- L43 _public prototype_ `void CreateProtocolEntity(const FRCSignatureActionContext& InContext, IRemoteControlProtocol& InProtocol, uint8 InMask) const;`
- L45 _public prototype_ `void AddMappings(const FRCSignatureActionContext& InContext, const IRemoteControlProtocol& InProtocol, FRemoteControlProtocolBinding& InOutBinding) const;`
- L47 _public prototype_ `const UScriptStruct* GetPropertyStruct() const;`
- L50 _public member_ `FName ProtocolName;` — `UPROPERTY(EditAnywhere, Category="Protocol")`
- L53 _public member_ `TInstancedStruct<FRemoteControlProtocolEntity> ProtocolEntity;` — `UPROPERTY(EditAnywhere, Category="Protocol", meta = (StructTypeConst))`
- L56 _public member_ `uint8 OverrideMask = 0xFF;` — `UPROPERTY(EditAnywhere, Category="Protocol", meta=(EditCondition="PropertyDimension > 1", EditConditionHides))`
- L60 _public member_ `bool bSingleProtocolChannel = false;` — `UPROPERTY(EditAnywhere, Category="Protocol", meta=(EditCondition="PropertyDimension > 1", EditConditionHides))` — Whether to combine all the Masks into a Single Protocol Channel rather than each Mask bit assigned to their own channel
- L63 _public member_ `ERCSignatureProtocolActionMappingSpace MappingSpace = ERCSignatureProtocolActionMappingSpace::Additive;` — `UPROPERTY(EditAnywhere, Category="Protocol")`
- L66 _public member_ `FInstancedPropertyBag Mappings;` — `UPROPERTY(EditAnywhere, Category="Protocol", meta = (FixedLayout))`
- L69 _public member_ `FPropertyBagPropertyDesc MinMappingDesc;` — `UPROPERTY()`
- L72 _public member_ `FPropertyBagPropertyDesc MaxMappingDesc;` — `UPROPERTY()`
- L75 _public member_ `uint8 PropertyDimension = 1;` — `UPROPERTY()`
