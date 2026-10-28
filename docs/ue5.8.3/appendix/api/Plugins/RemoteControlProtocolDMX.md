# Plugins / RemoteControlProtocolDMX

- module root: `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX`
- headers: 9; symbols: 183
- symbol kinds: class=7, delegate=3, enum=3, enumerator=8, function=18, member=44, namespace=12, prototype=80, struct=5, typedef=3
- PrivateDependencyModuleNames: DMXProtocol, Engine, RemoteControl, RemoteControlProtocol
- PublicDependencyModuleNames: Core, CoreUObject, DMXRuntime

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Internal/Library/RemoteControlDMXControlledProperty.h` (Internal)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXControlledProperty`  
`class FRemoteControlDMXControlledProperty : public TSharedFromThis<FRemoteControlDMXControlledProperty>`  
_L16-49_
- inherits: `TSharedFromThis<FRemoteControlDMXControlledProperty>`
- desc: Defines a Patch in a DMX Library of a Remote Control Preset along with the properties it controls
- L20 _public prototype_ `FRemoteControlDMXControlledProperty(const TSharedRef<const FRemoteControlProperty> InExposedProperty);`
- L23 _public function_ `TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>> GetEntities() const` — Returns the DMX protocol entities as structs on scope
- L26 _public prototype_ `const UObject* GetOwnerActor() const;` — Returns the owner object of this property
- L29 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the fixture patch of this property
- L32 _public prototype_ `int32 GetEntityIndexChecked(const TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>& Entity);` — Returns the index of specified entity. Useful to enumerate attributes. The entity has to be owned by this DMX controlled property, checked.
- L35 _public member_ `const TSharedRef<const FRemoteControlProperty> ExposedProperty;` — The DMX controlled property
- L39 _private prototype_ `void InitializeNewEntities();` — Initializes new entities
- L42 _private prototype_ `void UnifyEntities();` — Makes sure all entities use unfied properties where required.
- L45 _private prototype_ `FString GetSubobjectPath() const;` — Returns the subobject path for this property
- L48 _private member_ `TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>> Entities;` — The entities that control the property

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RemoteControl` (scope `UE`)
- L13 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Internal/Library/RemoteControlDMXControlledPropertyPatch.h` (Internal)


#### class `UE::RemoteControl::DMX::FRemoteControlDMXControlledPropertyPatch`  
`class FRemoteControlDMXControlledPropertyPatch : public TSharedFromThis<FRemoteControlDMXControlledPropertyPatch>`  
_L21-49_
- inherits: `TSharedFromThis<FRemoteControlDMXControlledPropertyPatch>`
- desc: A collection of DMX controlled properties that form a DMX fixture patch together
- L26 _public prototype_ `FRemoteControlDMXControlledPropertyPatch( URemoteControlDMXUserData& DMXUserData, const TArray<TSharedRef<FRemoteControlDMXControlledProperty>>& InDMXControlledProperties);` — Constructs the DMX controlled properties patch.
- L30 _public prototype_ `~FRemoteControlDMXControlledPropertyPatch();`
- L33 _public function_ `const TArray<TSharedRef<FRemoteControlDMXControlledProperty>>& GetDMXControlledProperties() const` — Returns the DMX controlled properties that form this patch
- L36 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the fixture patch corresponding to this property patch
- L39 _public prototype_ `const UObject* GetOwnerActor() const;` — Returns the owner actor of this patch, or nullptr if there is no outer Actor.
- L44 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* ChangedFixtureType);` — Called when a fixture type changed. Useful to adopt changed properties from the fixture type.
- L48 _private member_ `TArray<TSharedRef<FRemoteControlDMXControlledProperty>> DMXControlledProperties;` — The DMX controlled properties that form this patch

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RemoteControl` (scope `UE`)
- L16 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Internal/Library/RemoteControlDMXLibraryProxy.h` (Internal)


#### class `URemoteControlDMXLibraryProxy`  
`class URemoteControlDMXLibraryProxy : public UObject`  
_L25-133_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Class responsible to maintain the DMX Library of a Remote Control Preset
- L29 _private typedef_ `using FRemoteControlDMXControlledProperty = UE::RemoteControl::DMX::FRemoteControlDMXControlledProperty;`
- L30 _private typedef_ `using FRemoteControlDMXControlledPropertyPatch = UE::RemoteControl::DMX::FRemoteControlDMXControlledPropertyPatch;`
- L31 _private typedef_ `using FRemoteControlDMXProtocolEntityObserver = UE::RemoteControl::DMX::FRemoteControlDMXProtocolEntityObserver;`
- L35 _public prototype_ `virtual void PostInitProperties() override;`
- L36 _public prototype_ `virtual void PostLoad() override;`
- L40 _public prototype_ `UDMXLibrary* GetDMXLibrary() const;` — Gets the DMX library of this proxy
- L43 _public function_ `TArray<TSharedRef<FRemoteControlDMXControlledPropertyPatch>> GetPropertyPatches() const` — Returns the DMX controlled property patches in this proxy
- L46 _public prototype_ `void RequestRefresh();` — Refreshes the proxy on end frame
- L49 _public prototype_ `void Refresh();` — Refreshes the proxy
- L52 _public prototype_ `void Reset();` — Resets the proxy so it no longer can receive DMX
- L59 _public prototype_ `void ClearFixturePatches();` — Clears Fixture Patches. This should be called after a DMX Library asset in use was force deleted. Remote Control Protocol Entities keep a 'hard' reference to the DMX Library object, so need to be cleared here
- L62 _public prototype_ `TArray<UDMXEntityFixturePatch*> FindPatchesThatExceedUniverseSize() const;` — Finds fixture patches maintained by this proxy that exceed universe size
- L65 _public function_ `static FRemoteControlDMXPrePropertyPatchesChanged& GetOnPrePropertyPatchesChanged()` — Returns a delegate broadcast before property patches are being changed
- L68 _public function_ `static FSimpleMulticastDelegate& GetOnPostPropertyPatchesChanged()` — Returns a delegate broadcast after property patches were changed
- L73 _private prototype_ `void UpdatePropertyPatches();` — Updates the property patches used in this proxy
- L76 _private prototype_ `void BindOnFixturePatchesReceived();` — Binds to the OnFixturePatchReceived event for all patches in use
- L79 _private prototype_ `void UnbindOnFixturePatchesReceived();` — Unbinds from the OnFixturePatchReceived event for all patches in use
- L83 _private prototype_ `void UpdateEntitiesObserver();` — Updates the Entities Observer
- L88 _private prototype_ `void OnFixturePatchReceived(UDMXEntityFixturePatch* FixturePatch, const FDMXNormalizedAttributeValueMap& ValuePerAttribute);` — `UFUNCTION()` — Called when a fixture patch was received
- L91 _private prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatches() const;` — Returns the current fixture patches in use
- L94 _private prototype_ `TArray<TSharedRef<FRemoteControlProperty>> GetExposedProperties() const;` — Returns exposed properties of the preset that owns this proxy
- L97 _private prototype_ `URemoteControlDMXUserData& GetMutableDMXUserDataChecked();` — Returns the user data that holds this object
- L100 _private prototype_ `const URemoteControlDMXUserData& GetDMXUserDataChecked() const;` — Returns the user data that holds this object
- L103 _private prototype_ `void OnPostLoadRemoteControlPreset(URemoteControlPreset* Preset);` — Called when the remote control preset was fully loaded
- L106 _private prototype_ `void OnEntityExposedOrUnexposed(URemoteControlPreset* Preset, const FGuid& EntityId);` — Called when an entity was exposed or unexposed
- L109 _private prototype_ `void OnEntityRebind(const FGuid& EntityId);` — Called when an entity was rebound
- L112 _private prototype_ `void OnEntitiesUpdated(URemoteControlPreset* Preset, const TSet<FGuid>& ModifiedEntities);` — Called when entities changed
- L115 _private prototype_ `void OnPostLoadMapWithWorld(UWorld* World);` — Called when a map was fully loaded
- L118 _private member_ `TArray<TSharedRef<FRemoteControlDMXControlledPropertyPatch>> PropertyPatches;` — Current DMX controlled property patches
- L121 _private member_ `FDelegateHandle RefreshDelegateHandle;` — Handle set when the proxy is about to refresh
- L125 _private member_ `TSharedPtr<FRemoteControlDMXProtocolEntityObserver> EntitiesObserver;` — Observes entites for DMX specific property changes in editor
- L128 _private member_ `static FRemoteControlDMXPrePropertyPatchesChanged OnPrePropertyPatchesChanged;` — Delegate broadcast before property patches are being changed
- L131 _private member_ `static FSimpleMulticastDelegate OnPostPropertyPatchesChanged;` — Delegate broadcast after property patches were changed

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RemoteControl` (scope `UE`)
- L14 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FRemoteControlDMXPrePropertyPatchesChanged, URemoteControlPreset* ) UCLASS(Transient) class URemoteControlDMXLibraryProxy : public UObject { GENERATED_BODY() using FRemoteControlDMXControlledProperty = UE::RemoteControl::DMX::FRemoteControlDMXControlledProperty; using FRemoteControlDMXControlledPropertyPatch = UE::RemoteControl::DMX::FRemoteControlDMXControlledPropertyPatch; using FRemoteControlDMXProtocolEntityObserver = UE::RemoteControl::DMX::FRemoteControlDMXProtocolEntityObserver; public:`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Internal/RemoteControlDMXUserData.h` (Internal)


#### enum `ERemoteControlDMXPatchGroupMode`  
`enum class ERemoteControlDMXPatchGroupMode : uint8`  
_L17-24_
- reflection: `UENUM()`
- desc: Defines how DMX Protocol Entities should be patched
- L20 _public enumerator_ `GroupByProperty` — Creates a patch per property
- L23 _public enumerator_ `GroupByOwner` — Creates a patch per property owner object

#### class `URemoteControlDMXUserData`  
`class URemoteControlDMXUserData : public UObject`  
_L30-121_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: DMX user data for a Remote Control Preset
- L38 _public prototype_ `URemoteControlDMXUserData();`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _public prototype_ `virtual void PostLoad() override;`
- L45 _public prototype_ `virtual void BeginDestroy() override;`
- L49 _public prototype_ `static URemoteControlDMXUserData* GetOrCreateDMXUserData(URemoteControlPreset* InPreset);` — Gets or creates DMX User Data in specified preset.
- L52 _public function_ `UDMXLibrary* GetDMXLibrary() const` — Returns the DMX Library held with this user data
- L55 _public prototype_ `void SetDMXLibrary(UDMXLibrary* NewDMXLibrary);` — Sets the DMX Library held with this user data. Only valid DMX Libraries can be set.
- L58 _public function_ `URemoteControlDMXLibraryProxy* GetDMXLibraryProxy() const` — Returns the DMX Library Proxy
- L61 _public prototype_ `URemoteControlPreset* GetPreset() const;` — Returns the remote control preset this user data resides in
- L64 _public prototype_ `void SetPatchGroupMode(ERemoteControlDMXPatchGroupMode NewPatchGroupMode);` — Sets the patch group mode
- L67 _public function_ `ERemoteControlDMXPatchGroupMode GetPatchGroupMode() const` — Returns the current patch mode
- L70 _public function_ `bool IsAutoPatch() const` — Returns true if patches should be auto assigned to a universe and address, otherwise patches are is editable in editor.
- L73 _public prototype_ `void SetAutoPatchEnabled(bool bEnabled);` — Sets if auto patching is enabled
- L76 _public prototype_ `void SetAutoAssignFromUniverse(const int32 NewAutoAssignFromUniverse);` — Sets the universe from where patches should be generated.
- L79 _public prototype_ `int32 GetAutoAssignFromUniverse() const;` — Returns the universe from where patches should be generated.
- L83 _public function_ `static const FName GetDMXLibraryMemberNameChecked()` — Property name getters
- L84 _public function_ `static const FName GetAutoPatchMemberNameChecked()`
- L89 _private prototype_ `void EnsureValidDMXLibrary();` — Tests if there is a DMX Library, creates a new one if it is null
- L93 _private prototype_ `void TryUpgradeFromLegacy();` — Upgrades assets created before 5.5 that did not use a DMX library
- L98 _private member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The DMX library the remote control preset uses
- L102 _private member_ `ERemoteControlDMXPatchGroupMode PatchGroupMode = ERemoteControlDMXPatchGroupMode::GroupByOwner;` — `UPROPERTY()` — Defines how DMX Protocol Entities should be patched
- L106 _private member_ `TObjectPtr<URemoteControlDMXLibraryProxy> DMXLibraryProxy;` — `UPROPERTY(Transient)` — Proxy to handle the DMX Library
- L110 _private member_ `int32 AutoAssignFromUniverse = 1;` — `UPROPERTY()` — The universe from where patches should be generated.
- L114 _private member_ `bool bAutoPatch = true;` — `UPROPERTY()` — When checked, patches are auto assigned to a universe and address, otherwise the patch is editable in editor.
- L119 _private member_ `TObjectPtr<UObject> PerPresetEditorSettings;` — `UPROPERTY()` — Generic UObject to store editor data per preset, see URemoteControlDMXPerPresetEditorSettings

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_EVENT_OneParam(URemoteControlDMXUserData, FOnRemoteControlDMXUserDataChangedProperty, FPropertyChangedEvent&);`
- L26 _prototype_ `DECLARE_EVENT_OneParam(URemoteControlDMXUserData, FOnRemoteControlDMXUserDataChangedProperty, FPropertyChangedEvent&);`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Private/Library/RemoteControlDMXProtocolEntityObserver.h` (Private)


#### struct `UE::RemoteControl::DMX::FRemoteControlDMXProtocolEntityComparator`  
`struct FRemoteControlDMXProtocolEntityComparator`  
_L17-36_
- L19 _public prototype_ `FRemoteControlDMXProtocolEntityComparator(TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>> InEntity);`
- L22 _public prototype_ `bool DidPropertiesChange() const;` — Returns true if properties changed
- L25 _public member_ `const TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>> Entity;` — The entity to compare
- L29 _private prototype_ `void UpdateCache() const;` — Updates cached values
- L32 _private member_ `mutable bool bUseLSBMode = false;` — Cached LSB Mode
- L35 _private member_ `mutable EDMXFixtureSignalFormat DataType = EDMXFixtureSignalFormat::E8Bit;` — Cached Signal Format

#### class `UE::RemoteControl::DMX::FRemoteControlDMXProtocolEntityObserver`  
`class FRemoteControlDMXProtocolEntityObserver : public FTickableGameObject , public TSharedFromThis<FRemoteControlDMXProtocolEntityObserver>`  
_L44-64_
- inherits: `FTickableGameObject,TSharedFromThis<FRemoteControlDMXProtocolEntityObserver>`
- desc: Class that observes and notifies about DMX protocol entity changes. Required since the related RC event URemoteControlPreset::OnExposedPropertiesModified fires on RC changed properties, however we only want to handle DMX specific property changes.
- L49 _public prototype_ `FRemoteControlDMXProtocolEntityObserver() = default;`
- L50 _public prototype_ `FRemoteControlDMXProtocolEntityObserver(const TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>>& Entities);`
- L54 _private function_ `virtual bool IsTickableInEditor() const override`
- L55 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L56 _private prototype_ `virtual TStatId GetStatId() const override;`
- L60 _private prototype_ `URemoteControlDMXLibraryProxy* GetDMXLibraryProxy(const TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>& Entity) const;` — Returns the DMX Library Proxy for the specified Entity
- L63 _private member_ `TArray<FRemoteControlDMXProtocolEntityComparator> Comparators;` — Per entity comparator to detect changes

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RemoteControl` (scope `UE`)
- L15 _namespace_ `namespace DMX` (scope `UE::RemoteControl`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Private/RemoteControlDMXLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogRemoteControlDMX, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogRemoteControlDMX, Log, All);`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Private/RemoteControlProtocolDMXObjectVersion.h` (Private)


#### struct `FRemoteControlProtocolDMXObjectVersion`  
`struct FRemoteControlProtocolDMXObjectVersion`  
_L8-28_
- desc: Custom serialization version for changes to Remote Control Protocol DMX Objects
- L24 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L27 _private function_ `FRemoteControlProtocolDMXObjectVersion()`

#### enum `FRemoteControlProtocolDMXObjectVersion::Type`  
`enum Type`  
_L10-21_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.27
- L16 _public enumerator_ `MoveRemoteControlProtocolDMXEntityPropertiesToExtraSettingStruct` — Move Remote Control Protocol DMX Entity Properties to the Extra Setting struct so they can be customized
- L19 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L20 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Public/RemoteControlProtocolDMX.h` (Public)


#### struct `FRemoteControlDMXProtocolEntityExtraSetting`  
`struct FRemoteControlDMXProtocolEntityExtraSetting`  
_L23-97_
- reflection: `USTRUCT()`
- desc: An inner struct holding DMX specific data. Useful to have type customization for the struct.
- L29 _public member_ `FDMXEntityFixturePatchRef FixturePatchReference;` — `UPROPERTY()` — Reference to the fixture patch this binding uses
- L34 _public member_ `bool bRequestClearPatch = false;` — `UPROPERTY(Transient)` — If true clears the patch instead of generating one when the outer DMX entity is invalidated
- L42 _public member_ `bool bIsPrimaryPatch = true;` — `UPROPERTY()` — If true, this entity defines the patch and its fixture type. If false, this entity only follows the patch, but does not update the fixture type.
- L46 _public member_ `int32 FunctionIndex = INDEX_NONE;` — `UPROPERTY()` — The index of the DMX function to receive
- L50 _public member_ `FName AttributeName;` — `UPROPERTY()` — The attribute name of this binding
- L57 _public member_ `bool bUseLSB = false;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Least Significant Byte mode makes the individual bytes (channels) of the function be interpreted with the first bytes being the lowest part of the number.
- L61 _public member_ `EDMXFixtureSignalFormat DataType = EDMXFixtureSignalFormat::E8Bit;` — `UPROPERTY(EditAnywhere, Category = Mapping)` — Defines the used number of channels (bytes)
- L66 _public prototype_ `FRemoteControlDMXProtocolEntityExtraSetting() = default;` — Workaround for clang deprecation warnings for deprecated PackageGuid member in implicit constructors
- L67 _public prototype_ `FRemoteControlDMXProtocolEntityExtraSetting(const FRemoteControlDMXProtocolEntityExtraSetting&) = default;`
- L68 _public prototype_ `FRemoteControlDMXProtocolEntityExtraSetting(FRemoteControlDMXProtocolEntityExtraSetting&&) = default;`
- L69 _public prototype_ `FRemoteControlDMXProtocolEntityExtraSetting& operator=(const FRemoteControlDMXProtocolEntityExtraSetting&) = default;`
- L70 _public prototype_ `FRemoteControlDMXProtocolEntityExtraSetting& operator=(FRemoteControlDMXProtocolEntityExtraSetting&&) = default;`
- L80 _public member_ `int32 Universe_DEPRECATED = -1;` — `UPROPERTY()` — The DMX universe of this entity. -1 in auto patch mode.
- L84 _public member_ `int32 StartingChannel_DEPRECATED = -1;` — `UPROPERTY()` — The starting channel of this entity. -1 in auto patch mode.
- L89 _public member_ `bool bUseDefaultInputPort_DEPRECATED = true;` — `UE_DEPRECATED(5.5, "Remote control now uses a DMX Library internally. Please refer to the Fixture Patch ref instead.")` — `UPROPERTY()` — If set to true, uses the default input port set in Remote Control Protocol project settings
- L94 _public member_ `FGuid InputPortId_DEPRECATED;` — `UE_DEPRECATED(5.5, "Remote control now uses a DMX Library internally. Please refer to the Fixture Patch ref instead.")` — `UPROPERTY()` — Reference of an input DMX port id

#### struct `FRemoteControlDMXProtocolEntity`  
`struct FRemoteControlDMXProtocolEntity : public FRemoteControlProtocolEntity`  
_L103-179_
- reflection: `USTRUCT()`
- inherits: `FRemoteControlProtocolEntity`
- desc: DMX protocol entity for remote control binding
- L109 _public prototype_ `uint8 GetNumDMXChannels() const;` — Returns the num DMX channels this setting spans
- L112 _public function_ `virtual FName GetRangePropertyName() const override`
- L113 _public prototype_ `virtual uint8 GetRangePropertySize() const override;`
- L114 _public prototype_ `virtual const FString& GetRangePropertyMaxValue() const override;`
- L118 _public prototype_ `void Invalidate();` — Invalidates this entity. The entity will be updated on the next tick.
- L121 _public prototype_ `static TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>> GetAllDMXProtocolEntitiesInPreset(URemoteControlPreset* Preset);` — Finds remote control protocol DMX entities used by the specified property
- L124 _public prototype_ `static TArray<TSharedRef<TStructOnScope<FRemoteControlProtocolEntity>>> FindEntitiesByProperty(const TSharedRef<FRemoteControlProperty>& Property);` — Finds remote control protocol DMX entities used by the specified property
- L127 _public prototype_ `void BindDMX();` — Binds this entity to DMX
- L130 _public prototype_ `void UnbindDMX();` — Unbinds this entity from DMX
- L139 _public prototype_ `void SetAttributeName(const FName& AttributeName);` — Sets the attribute name of the entity. Use with care, the attribute name needs to exist in the fixture patch's active mode for the entity to be functional. @param AttributeName			The DMX attribute name the entity corresponds to.
- L143 _public prototype_ `bool Serialize(FArchive& Ar);` — Called when the struct is serialized
- L146 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called after the struct is serialized
- L150 _public member_ `FRemoteControlDMXProtocolEntityExtraSetting ExtraSetting;` — `UPROPERTY(EditAnywhere, Category = Mapping, meta = (ShowOnlyInnerProperties))` — Extra protocol settings
- L154 _public member_ `uint32 RangeInputTemplate = 0;` — `UPROPERTY(Transient)` — DMX range input property template, used for binding.
- L158 _private prototype_ `static URemoteControlDMXLibraryProxy* GetDMXLibraryProxy(URemoteControlPreset* Preset);` — Gets or creates the DMX library proxy
- L165 _public member_ `int32 Universe_DEPRECATED = 0;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This Property is deprecated and will be removed in a future release. It was moved to the ExtraSetting struct member so the property can be customized."))` — Deprecated 5.0
- L168 _public member_ `bool bUseLSB_DEPRECATED = false;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This Property is deprecated and will be removed in a future release. It was moved to the ExtraSetting struct member so the property can be customized."))`
- L171 _public member_ `EDMXFixtureSignalFormat DataType_DEPRECATED = EDMXFixtureSignalFormat::E8Bit;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This Property is deprecated and will be removed in a future release. It was moved to the ExtraSetting struct member so the property can be customized."))`
- L174 _public member_ `bool bUseDefaultInputPort_DEPRECATED = true;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This Property is deprecated and will be removed in a future release. It was moved to the ExtraSetting struct member so the property can be customized."))`
- L177 _public member_ `FGuid InputPortId_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This Property is deprecated and will be removed in a future release. It was moved to the ExtraSetting struct member so the property can be customized."))`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRemoteControlDMXProtocolEntity> : public TStructOpsTypeTraitsBase2<FRemoteControlDMXProtocolEntity>`  
_L182-189_
- inherits: `TStructOpsTypeTraitsBase2<FRemoteControlDMXProtocolEntity>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L185-188_

#### class `FRemoteControlProtocolDMX`  
`class FRemoteControlProtocolDMX : public FRemoteControlProtocol`  
_L194-231_
- inherits: `FRemoteControlProtocol`
- desc: DMX protocol implementation for Remote Control
- L197 _public function_ `FRemoteControlProtocolDMX() : FRemoteControlProtocol(ProtocolName)`
- L201 _public function_ `TConstArrayView<FRemoteControlProtocolEntityWeakPtr> GetProtocolBindings() const`
- L207 _public prototype_ `virtual void Bind(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InRemoteControlProtocolEntity) override;`
- L208 _public prototype_ `virtual void Unbind(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InRemoteControlProtocolEntity) override;`
- L209 _public prototype_ `virtual void UnbindAll() override;`
- L210 _public function_ `virtual UScriptStruct* GetProtocolScriptStruct() const override`
- L214 _public member_ `static const FName ProtocolName;` — DMX protocol name
- L217 _public member_ `static const FName PatchColumnName;`
- L218 _public member_ `static const FName UniverseColumnName;`
- L219 _public member_ `static const FName ChannelColumnName;`
- L225 _protected prototype_ `virtual void RegisterColumns() override;` — Populates protocol specific columns.
- L230 _private member_ `TArray<FRemoteControlProtocolEntityWeakPtr> WeakProtocolsBindings;` — Binding for the DMX protocol

#### Free symbols / members of external scopes

- L186 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonab22007e0103`)
- L187 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonab22007e0103`)

### `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Public/RemoteControlProtocolDMXSettings.h` (Public)


#### class `URemoteControlProtocolDMXSettings`  
`class URemoteControlProtocolDMXSettings : public UObject`  
_L15-38_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- desc: DMX Remote Control Settings. This class currently only contains deprecated properties and is not registered with project settings.
- L21 _public prototype_ `FGuid GetOrCreateDefaultInputPortId();` — `UE_DEPRECATED(5.5, "Remote control DMX no longer has an input port, instead please refer to the input port of the DMX library in DMXUserData of the Remote Control Preset")`
- L25 _public prototype_ `static FSimpleMulticastDelegate& GetOnRemoteControlProtocolDMXSettingsChanged();` — `UE_DEPRECATED(5.5, "Currently URemoteControlProtocolDMXSettings has no properties that should signal a change.")` — Returns a delegate broadcast whenever the Remote Control Protocol DMX Settings changed
- L29 _public function_ `static FName GetDefaultInputPortIdPropertyNameChecked()` — `UE_DEPRECATED(5.5, "The DefaultInputPortId property is deprecated and should no longer be accessed")`
- L35 _private member_ `FGuid DefaultInputPortId_DEPRECATED;` — `UPROPERTY()` — DMX Default Device
- L37 _private member_ `static FSimpleMulticastDelegate OnRemoteControlProtocolDMXSettingsChangedDelegate_DEPRECATED;`
