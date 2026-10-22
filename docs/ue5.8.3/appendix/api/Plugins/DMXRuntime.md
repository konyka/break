# Plugins / DMXRuntime

- module root: `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime`
- headers: 43; symbols: 1373
- symbol kinds: class=53, delegate=12, enum=23, enumerator=118, function=192, macro=2, member=425, namespace=11, prototype=446, struct=87, typedef=4
- PrivateDependencyModuleNames: AssetRegistry, DMXFixtureActorInterface, Json, MovieScene, Projects, UnrealEd, XmlParser
- PublicDependencyModuleNames: Core, CoreUObject, DMXGDTF, DMXProtocol, DatasmithContent, Engine, JsonUtilities

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Internal/DMXAttributeToDefaultPhyiscalProperties.h` (Internal)


#### struct `UE::DMX::FDMXAttributeToDefaultPhyiscalProperties`  
`struct FDMXAttributeToDefaultPhyiscalProperties`  
_L14-35_
- L17 _public prototype_ `static void ResetToDefaultPhysicalProperties(FDMXFixtureFunction& InOutFunction);` — Returns the value range for specified physical unit
- L34 _private member_ `static const TMap<FName, FDefaultPhyicalProperties> AttributeNameToDefaultPhysicalProperitesMap;` — A map to list all GDTF compliant Physical Units and their matching Physical Value default ranges.

#### struct `UE::DMX::FDMXAttributeToDefaultPhyiscalProperties::FDefaultPhyicalProperties`  
`struct FDefaultPhyicalProperties`  
_L20-31_
- L22 _public function_ `FDefaultPhyicalProperties(EDMXGDTFPhysicalUnit InPhysicalUnit, double InPhysicalFrom, double InPhysicalTo) : PhysicalUnit(InPhysicalUnit) , PhysicalFrom(InPhysicalFrom) , PhysicalTo(InPhysicalTo)`
- L28 _public member_ `const EDMXGDTFPhysicalUnit PhysicalUnit = EDMXGDTFPhysicalUnit::None;`
- L29 _public member_ `const double PhysicalFrom = 0.0;`
- L30 _public member_ `const double PhysicalTo = 1.0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Private/DMXRuntimeMainStreamObjectVersion.h` (Private)


#### struct `FDMXRuntimeMainStreamObjectVersion`  
`struct FDMXRuntimeMainStreamObjectVersion`  
_L8-60_
- desc: Custom serialization version for changes to DMX Runtime Objects in the //Main Stream
- L56 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L59 _private function_ `FDMXRuntimeMainStreamObjectVersion()`

#### enum `FDMXRuntimeMainStreamObjectVersion::Type`  
`enum Type`  
_L10-53_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.26
- L16 _public enumerator_ `DefaultToNormalizedValuesInDMXLibrarySection` — Update to DMX Library Section using normalized values by default
- L19 _public enumerator_ `ReplaceWeakWithStrongFixturePatchReferncesInLibrarySection` — Update to DMX Library Section using normalized values by default
- L22 _public enumerator_ `DMXFixtureTypeAllowMatrixInEachFixtureMode` — Update DMX Entity Fixture Type to allow the Matrix to be enabled/disabled per Mode
- L25 _public enumerator_ `DMXControllersAreRemoved` — DMX Controllers are removed from the pugin
- L28 _public enumerator_ `DMXFixturePatchHasMVRUUID` — Update Fixture Patch to use an MVR UUID
- L31 _public enumerator_ `DMXFixturePatchNoLongerImplementsAutoAssign` — Remove auto assign features from fixture patch (instead it's auto assigned via FDMXEditorUtils where required)
- L34 _public enumerator_ `DMXImportGDTFIsASoftObjectPtr` — Change the DMXImportGDTF asset reference in Fixture Type to a soft object ptr, to avoid loading the data (since UE 5.5)
- L37 _public enumerator_ `DMXFixturePatchHasFixtureID` — Update Fixture Patch to hold the MVR Fixture ID (since UE 5.5)
- L40 _public enumerator_ `DMXFixGDTFImportAssetsWithInvalidNames` — Rename GDTF import assets with invalid names
- L43 _public enumerator_ `DMXUpgradeFixtureFunctionsToUsePhysicalProperties` — Upgrade Fixture Functions to make use of pysical properties where required (e.g. Pan, Tilt, Zoom)
- L46 _public enumerator_ `DMXFixturePatchesHaveDefaultTransform` — Upgrade Fixture Patches to have a Default Transform
- L49 _public enumerator_ `DMXMVRSceneActorSpawnsActorsPerFixtureType` — 5.5 Upgrade MVR Scene Actor to spawn Actors per Fixture Type of per GDTF
- L51 _public enumerator_ `VersionPlusOne`
- L52 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Private/Modulators/DMXModulator_CMYtoRGB.h` (Private)


#### class `UDMXModulator_CMYtoRGB`  
`class UDMXModulator_CMYtoRGB : public UDMXModulator`  
_L12-37_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "DMX Modulator CMY to RGB", AutoExpandCategories = ("DMX"))`
- inherits: `UDMXModulator`
- desc: Converts Attributes from CMY to RGB.
- L18 _public prototype_ `UDMXModulator_CMYtoRGB();`
- L21 _public prototype_ `virtual void Modulate_Implementation(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues) override;` — RGB to CMY implementation
- L24 _public prototype_ `virtual void ModulateMatrix_Implementation(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues) override;` — Matrix RGB to CMY implementation
- L28 _public member_ `FDMXAttributeName AttributeCyanToRed;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CMY to RGB", Meta = (DisplayName = "Cyan to Red", AdvancedDisplay))` — The name of the attribute that is converted from Cyan to Red
- L32 _public member_ `FDMXAttributeName AttributeMagentaToGreen;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CMY to RGB", Meta = (DisplayName = "Magenta to Green", AdvancedDisplay))` — The name of the attribute that is converted from Magenta to Green
- L36 _public member_ `FDMXAttributeName AttributeYellowToBlue;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CMY to RGB", Meta = (DisplayName = "Yellow to Blue", AdvancedDisplay))` — The name of the attribute that is converted from Yellow to Blue

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Private/Modulators/DMXModulator_ExtraAttributes.h` (Private)


#### class `UDMXModulator_ExtraAttributes`  
`class UDMXModulator_ExtraAttributes : public UDMXModulator`  
_L12-27_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "DMX Modulator Extra Attributes", AutoExpandCategories = ("DMX"))`
- inherits: `UDMXModulator`
- desc: Adds attributes that are not received (e.g. because DMX was generated from PixelMapping) to the DMX signal
- L19 _public prototype_ `UDMXModulator_ExtraAttributes();`
- L22 _public prototype_ `virtual void Modulate_Implementation(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues) override;` — Attribute value override implementation
- L26 _public member_ `TMap<FDMXAttributeName, float> ExtraAttributeNameToNormalizedValueMap;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Extra Attributes", Meta = (DisplayName = "Attribute to Normalized Value Map"))` — Adds the attributes with their values to the Output if they don't exist, or replaces them with the values specified

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Private/Modulators/DMXModulator_ExtraCellAttributes.h` (Private)


#### class `UDMXModulator_ExtraCellAttributes`  
`class UDMXModulator_ExtraCellAttributes : public UDMXModulator`  
_L12-27_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "DMX Modulator Extra Cell Attributes", AutoExpandCategories = ("DMX"))`
- inherits: `UDMXModulator`
- desc: Adds matrix attributes that are not received (e.g. because DMX was generated from PixelMapping) to the DMX signal
- L19 _public prototype_ `UDMXModulator_ExtraCellAttributes();`
- L22 _public prototype_ `virtual void ModulateMatrix_Implementation(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues) override;` — Matrix Attribute value override implementation
- L26 _public member_ `TMap<FDMXAttributeName, float> ExtraAttributeNameToNormalizedValueMap;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Extra Cell Attributes", Meta = (DisplayName = "Attribute to Normalized Value Map"))` — Adds the attributes with their values to the Output if they don't exist, or replaces them with the values specified

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Private/Modulators/DMXModulator_RGBtoCMY.h` (Private)


#### class `UDMXModulator_RGBtoCMY`  
`class UDMXModulator_RGBtoCMY : public UDMXModulator`  
_L12-38_
- reflection: `UCLASS(NotBlueprintable, DisplayName = "DMX Modulator RGB to CMY", AutoExpandCategories = ("DMX"))`
- inherits: `UDMXModulator`
- desc: Converts Attributes from RGB to CMY
- L19 _public prototype_ `UDMXModulator_RGBtoCMY();`
- L22 _public prototype_ `virtual void Modulate_Implementation(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues) override;` — RGB to CMY implementation
- L25 _public prototype_ `virtual void ModulateMatrix_Implementation(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues) override;` — Matrix RGB to CMY implementation
- L29 _public member_ `FDMXAttributeName AttributeRedToCyan;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RGB to CMY", Meta = (DisplayName = "Red to Cyan", AdvancedDisplay))` — The name of the attribute that is converted from Red to Cyan
- L33 _public member_ `FDMXAttributeName AttributeGreenToMagenta;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RGB to CMY", Meta = (DisplayName = "Green to Magenta", AdvancedDisplay))` — The name of the attribute that is converted from Green to Magenta
- L37 _public member_ `FDMXAttributeName AttributeBlueToYellow;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RGB to CMY", Meta = (DisplayName = "Blue to Yellow", AdvancedDisplay))` — The name of the attribute that is converted from Blue to Yellow

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/DMXOptionalTypes.h` (Public)


#### struct `FDMXOptionalBool`  
`struct FDMXOptionalBool`  
_L14-65_
- reflection: `USTRUCT()`
- L19 _public member_ `TOptional<bool> Value;` — The Optional Value
- L22 _public function_ `void Reset()` — Resets the optional
- L25 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L28 _public function_ `const bool& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L30 _public function_ `const FDMXOptionalBool& operator=(const bool& Transform)`
- L54 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalBool> : public TStructOpsTypeTraitsBase2<FDMXOptionalBool>`  
_L68-77_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalBool>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-76_

#### struct `FDMXOptionalInt32`  
`struct FDMXOptionalInt32`  
_L80-137_
- reflection: `USTRUCT()`
- L85 _public member_ `TOptional<int32> Value;` — The Optional Value
- L88 _public function_ `void Reset()` — Resets the optional
- L91 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L94 _public function_ `const int32& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L96 _public function_ `const FDMXOptionalInt32& operator=(const int32& Transform)`
- L120 _public function_ `bool Serialize(FArchive& Ar)`
- L126 _public function_ `FArchive& operator<<(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalInt32> : public TStructOpsTypeTraitsBase2<FDMXOptionalInt32>`  
_L140-149_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalInt32>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L144-148_

#### struct `FDMXOptionalFloat`  
`struct FDMXOptionalFloat`  
_L152-203_
- reflection: `USTRUCT()`
- L157 _public member_ `TOptional<float> Value;` — The Optional Value
- L160 _public function_ `void Reset()` — Resets the optional
- L163 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L166 _public function_ `const float& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L168 _public function_ `const FDMXOptionalFloat& operator=(const float& Transform)`
- L192 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalFloat> : public TStructOpsTypeTraitsBase2<FDMXOptionalFloat>`  
_L206-215_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalFloat>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L210-214_

#### struct `FDMXOptionalGuid`  
`struct FDMXOptionalGuid`  
_L218-275_
- reflection: `USTRUCT()`
- L223 _public member_ `TOptional<FGuid> Value;` — The Optional Value
- L226 _public function_ `void Reset()` — Resets the optional
- L229 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L232 _public function_ `const FGuid& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L234 _public function_ `const FDMXOptionalGuid& operator=(const FGuid& Transform)`
- L258 _public function_ `bool Serialize(FArchive& Ar)`
- L264 _public function_ `FArchive& operator<<(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalGuid> : public TStructOpsTypeTraitsBase2<FDMXOptionalGuid>`  
_L278-287_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalGuid>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L282-286_

#### struct `FDMXOptionalVector2D`  
`struct FDMXOptionalVector2D`  
_L291-348_
- reflection: `USTRUCT()`
- L296 _public member_ `TOptional<FVector2D> Value;` — The Optional Value
- L299 _public function_ `void Reset()` — Resets the optional
- L302 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L305 _public function_ `const FVector2D& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L307 _public function_ `const FDMXOptionalVector2D& operator=(const FVector2D& Vector2D)`
- L331 _public function_ `bool Serialize(FArchive& Ar)`
- L337 _public function_ `FArchive& operator<<(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalVector2D> : public TStructOpsTypeTraitsBase2<FDMXOptionalVector2D>`  
_L351-360_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalVector2D>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L355-359_

#### struct `FDMXOptionalTransform`  
`struct FDMXOptionalTransform`  
_L363-420_
- reflection: `USTRUCT()`
- L368 _public member_ `TOptional<FTransform> Value;` — The Optional Value
- L371 _public function_ `void Reset()` — Resets the optional
- L374 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L377 _public function_ `const FTransform& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L379 _public function_ `const FDMXOptionalTransform& operator=(const FTransform& Transform)`
- L403 _public function_ `bool Serialize(FArchive& Ar)`
- L409 _public function_ `FArchive& operator<<(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalTransform> : public TStructOpsTypeTraitsBase2<FDMXOptionalTransform>`  
_L423-432_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalTransform>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L427-431_

#### struct `FDMXOptionalColorCIE1931`  
`struct FDMXOptionalColorCIE1931`  
_L435-486_
- reflection: `USTRUCT()`
- L440 _public member_ `TOptional<FDMXGDTFColorCIE1931xyY> Value;` — The Optional Value
- L443 _public function_ `void Reset()` — Resets the optional
- L446 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L449 _public function_ `const FDMXGDTFColorCIE1931xyY& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L451 _public function_ `const FDMXOptionalColorCIE1931& operator=(const FDMXGDTFColorCIE1931xyY& Transform)`
- L475 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalColorCIE1931> : public TStructOpsTypeTraitsBase2<FDMXOptionalColorCIE1931>`  
_L489-498_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalColorCIE1931>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L493-497_

#### struct `FDMXOptionalString`  
`struct FDMXOptionalString`  
_L501-552_
- reflection: `USTRUCT()`
- L506 _public member_ `TOptional<FString> Value;` — The Optional Value
- L509 _public function_ `void Reset()` — Resets the optional
- L512 _public function_ `bool IsSet() const` — Returns true if the optional is set
- L515 _public function_ `const FString& GetValue() const` — Returns the Value of the optional, only call when the value is set.
- L517 _public function_ `const FDMXOptionalString& operator=(const FString& Transform)`
- L541 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalString> : public TStructOpsTypeTraitsBase2<FDMXOptionalString>`  
_L555-564_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalString>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L559-563_

#### Free symbols / members of external scopes

- L36 _function_ `friend bool operator==(const FDMXOptionalBool& A, const FDMXOptionalBool& B)`
- L49 _function_ `friend bool operator!=(const FDMXOptionalBool& A, const FDMXOptionalBool& B)`
- L60 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalBool& Struct)`
- L73 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0103`)
- L74 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0103`)
- L75 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0103`)
- L102 _function_ `friend bool operator==(const FDMXOptionalInt32& A, const FDMXOptionalInt32& B)`
- L115 _function_ `friend bool operator!=(const FDMXOptionalInt32& A, const FDMXOptionalInt32& B)`
- L132 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalInt32& Struct)`
- L145 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0203`)
- L146 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0203`)
- L147 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0203`)
- L174 _function_ `friend bool operator==(const FDMXOptionalFloat& A, const FDMXOptionalFloat& B)`
- L187 _function_ `friend bool operator!=(const FDMXOptionalFloat& A, const FDMXOptionalFloat& B)`
- L198 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalFloat& Struct)`
- L211 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0303`)
- L212 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0303`)
- L213 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0303`)
- L240 _function_ `friend bool operator==(const FDMXOptionalGuid& A, const FDMXOptionalGuid& B)`
- L253 _function_ `friend bool operator!=(const FDMXOptionalGuid& A, const FDMXOptionalGuid& B)`
- L270 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalGuid& Struct)`
- L283 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0403`)
- L284 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0403`)
- L285 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0403`)
- L313 _function_ `friend bool operator==(const FDMXOptionalVector2D& A, const FDMXOptionalVector2D& B)`
- L326 _function_ `friend bool operator!=(const FDMXOptionalVector2D& A, const FDMXOptionalVector2D& B)`
- L343 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalVector2D& Struct)`
- L356 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0503`)
- L357 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0503`)
- L358 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0503`)
- L385 _function_ `friend bool operator==(const FDMXOptionalTransform& A, const FDMXOptionalTransform& B)`
- L398 _function_ `friend bool operator!=(const FDMXOptionalTransform& A, const FDMXOptionalTransform& B)`
- L415 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalTransform& Struct)`
- L428 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0603`)
- L429 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0603`)
- L430 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0603`)
- L457 _function_ `friend bool operator==(const FDMXOptionalColorCIE1931& A, const FDMXOptionalColorCIE1931& B)`
- L470 _function_ `friend bool operator!=(const FDMXOptionalColorCIE1931& A, const FDMXOptionalColorCIE1931& B)`
- L481 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalColorCIE1931& Struct)`
- L494 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0703`)
- L495 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0703`)
- L496 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0703`)
- L523 _function_ `friend bool operator==(const FDMXOptionalString& A, const FDMXOptionalString& B)`
- L536 _function_ `friend bool operator!=(const FDMXOptionalString& A, const FDMXOptionalString& B)`
- L547 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOptionalString& Struct)`
- L560 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonabb3794e0803`)
- L561 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonabb3794e0803`)
- L562 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonabb3794e0803`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/DMXRuntimeLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXRuntime, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXRuntime, Log, All);`
- L9 _macro_ `#define UE_LOG_DMXRUNTIME(Verbosity, Format, ...) \`
- L14 _macro_ `#define UE_CLOG_DMXRUNTIME(Conditional, Verbosity, Format, ...) \`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/DMXRuntimeUtils.h` (Public)


#### class `FDMXRuntimeUtils`  
`class FDMXRuntimeUtils`  
_L16-374_
- L20 _public prototype_ `static FDMXOptionalTransform ParseGDTFMatrix(const FString& String);` — Parses a GDTF (or MVR) Transformation Matrix from a String. Result is optional and set if parsing succeeded.
- L23 _public prototype_ `static FString ConvertTransformToGDTF4x3MatrixString(FTransform Transform);` — Converts a UE transform to a GDTF style string
- L34 _public prototype_ `static FString GenerateUniqueNameFromExisting(const TSet<FString>& InExistingNames, FString InDesiredName, uint8 NumDigitsInPostfix = 2, bool bAlwaysGeneratePostfix = false);` — Generates a unique name given a base one and a list of existing ones, by appending an index. @param InExistingNames					Set of exiting names the new name should not be using. @param InDesiredName						The desired Name. Note, desired name should not be empty (ensured). Generates 'New' if desired name is empty. @param NumDigitsInPostfix (optional)		The min num digits to generate when appending a post fix. @param bAlwaysGeneratePostfix (optional)	If true, always generates digits as postfix. @return									Returns the unique name.
- L43 _public prototype_ `static FString FindUniqueEntityName(const UDMXLibrary* InLibrary, TSubclassOf<UDMXEntity> InEntityClass, const FString& InBaseName = TEXT(""));` — Creates an unique name for an Entity from a specific type, using the type name as base. @param InLibrary		The DMXLibrary object the entity will belong to. @param InEntityClass	The class of the Entity, to check the name against others from same type. @param InBaseName	Optional base name to use instead of the type name. @return Unique name for an Entity amongst others from the same type.
- L53 _public prototype_ `static bool GetNameAndIndexFromString(const FString& InString, FString& OutName, int32& OutIndex);` — Utility to separate a name from an index at the end. @param InString	The string to be separated. @param OutName	The string without an index at the end. White spaces and '_' are also removed. @param OutIndex	Index that was separated from the name. If there was none, it's zero. Check the return value to know if there was an index on InString. @return True if there was an index on InString.
- L62 _public prototype_ `static TMap<int32, TArray<UDMXEntityFixturePatch*>> MapToUniverses(const TArray<UDMXEntityFixturePatch*>& AllPatches);` — Maps each patch to its universe. @param AllPatches Patches to map @return Key: universe Value: patches in universe with associated key
- L67 _public prototype_ `static FString GenerateUniqueNameForImportFunction(TMap<FString, uint32>& OutPotentialFunctionNamesAndCount, const FString& InBaseName);` — Generates a unique name given a base one and a list of potential ones
- L78 _public function_ `template<typename T> static void PixelMappingDistributionSort(EDMXPixelMappingDistribution InDistribution, int32 InNumXPanels, int32 InNumYPanels, const TArray<T>& InUnorderedList, TArray<T>& OutSortedList)` — Sort a distribution array for widget InDistribution			Distribution schema InNumXPanels				Num columns InNumYPanels				Num rows InUnorderedList			Templated unsorted array input OutSortedList			Templated unsorted array output
- L351 _public function_ `template <typename StructType> static TOptional<FString> SerializeStructToString(const StructType& Struct)` — Serializes a struct to a Sting
- L373 _public prototype_ `FDMXRuntimeUtils() = delete;` — can't instantiate this class

#### Free symbols / members of external scopes

- L357 _typedef_ `typedef TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FStringWriter;` (scope `FDMXRuntimeUtils::SerializeStructToString`)
- L358 _typedef_ `typedef TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>> FStringWriterFactory;` (scope `FDMXRuntimeUtils::SerializeStructToString`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/DMXSubsystem.h` (Public)


#### class `UDMXSubsystem`  
`class UDMXSubsystem : public UEngineSubsystem`  
_L27-332_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: UDMXSubsystem Collections of DMX context blueprint subsystem functions and internal functions for DMX K2Nodes
- L39 _public prototype_ `static void ClearDMXBuffers();` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DisplayName = "Clear DMX Buffers"))` — Clears all buffered DMX data of Ports and Fixture Patches. Note, this function clears the buffers, it does not zero them out. To reset to default or zero, see Fixture Patch members Send Default Values and Send Zero Values.
- L44 _public prototype_ `void SendDMX(UDMXEntityFixturePatch* FixturePatch, TMap<FDMXAttributeName, int32> AttributeMap, EDMXSendResult& OutResult);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixurePatch::SendDMX instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Use DMXEntityFixurePatch::SendDMX instead"))` — Send DMX using function names and integer values.
- L49 _public prototype_ `void SendDMXRaw(FDMXProtocolName SelectedProtocol, int32 RemoteUniverse, TMap<int32, uint8> AddressValueMap, EDMXSendResult& OutResult);` — `UE_DEPRECATED(4.27, "Use UDMXSubsystem::SendDMXToOutputPort instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Use SendDMXToOutputPort instead."))` — DEPRECATED 4.27
- L53 _public prototype_ `static void SendDMXToOutputPort(FDMXOutputPortReference OutputPortReference, TMap<int32, uint8> ChannelToValueMap, int32 LocalUniverse = 1);` — `UFUNCTION(BlueprintCallable, Category = "DMX", Meta = (DisplayName = "Send DMX To Output Port"))` — Sends DMX via an Output Port.
- L58 _public prototype_ `void GetRawBuffer(FDMXProtocolName SelectedProtocol, int32 RemoteUniverse, TArray<uint8>& DMXBuffer);` — `UE_DEPRECATED(4.27, "Use UDMXSubsystem::GetDMXDataFromInputPort or GetDMXDataFromOutputPort instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Use GetDMXDataFromInputPort or GetDMXDataFromOutputPort instead."))` — DEPRECATED 4.27
- L62 _public prototype_ `static void GetDMXDataFromInputPort(FDMXInputPortReference InputPortReference, TArray<uint8>& DMXData, int32 LocalUniverse = 1);` — `UFUNCTION(BlueprintCallable, Category = "DMX", Meta = (DisplayName = "Get DMX Data From Input Port"))` — Gets latest DMX Values from a DMX Universe of a DMX Input Port. If no DMX was received the resulting array will be empty.
- L66 _public prototype_ `static void GetDMXDataFromOutputPort(FDMXOutputPortReference OutputPortReference, TArray<uint8>& DMXData, int32 LocalUniverse = 1);` — `UFUNCTION(BlueprintCallable, Category = "DMX", Meta = (DisplayName = "Get DMX Data From Output Port"))` — Gets latest DMX Values from a DMX Universe of a DMX Output Port. If no DMX was received the resulting array will be empty.
- L70 _public prototype_ `void GetAllFixturesOfType(const FDMXEntityFixtureTypeRef& FixtureType, TArray<UDMXEntityFixturePatch*>& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (AutoCreateRefTerm = "FixtureType"))` — Return an array of Fixture Patches that use the provided Fixture Type.
- L74 _public prototype_ `void GetAllFixturesOfCategory(const UDMXLibrary* DMXLibrary, FDMXFixtureCategory Category, TArray<UDMXEntityFixturePatch*>& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Return an array of Fixture Patches that use the provided category.
- L78 _public prototype_ `void GetAllFixturesInUniverse(const UDMXLibrary* DMXLibrary, int32 UniverseId, TArray<UDMXEntityFixturePatch*>& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Return an array of Fixture Patches that reside in the provided universe.
- L83 _public prototype_ `void GetFixtureAttributes(const UDMXEntityFixturePatch* InFixturePatch, const TArray<uint8>& DMXBuffer, TMap<FDMXAttributeName, int32>& OutResult);` — `UE_DEPRECATED(5.5, "Instead please call UDMXEntityFixturePatch::GetAttributeValues to retrieve attribute values safely.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 5.5. Instead please call the Fixture Patch function 'Get Attribute Values' to retrieve attribute values safely."))` — Return a map with all DMX functions and their associated values provided DMX buffer and desired universe.
- L87 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetAllFixturesWithTag(const UDMXLibrary* DMXLibrary, FName CustomTag);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Return an array of Fixture Patches that have the custom tag set.
- L91 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetAllFixturesInLibrary(const UDMXLibrary* DMXLibrary);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Return an array of Fixture Patches in the provided DMX Library.
- L95 _public prototype_ `UDMXEntityFixturePatch* GetFixtureByName(const UDMXLibrary* DMXLibrary, const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (AutoCreateRefTerm="Name"))` — Return the Fixture Patch with given name or an invalid object if no Fixture Patch matches the name.
- L99 _public prototype_ `TArray<UDMXEntityFixtureType*> GetAllFixtureTypesInLibrary(const UDMXLibrary* DMXLibrary);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Returns all Fixture Types in a DMX Library.
- L103 _public prototype_ `UDMXEntityFixtureType* GetFixtureTypeByName(const UDMXLibrary* DMXLibrary, const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (AutoCreateRefTerm = "Name"))` — Return the Fixture Type with provided name or an invalid object if no Fixture Type matches the name.
- L108 _public prototype_ `void GetAllUniversesInController(const UDMXLibrary* DMXLibrary, FString ControllerName, TArray<int32>& OutResult);` — `UE_DEPRECATED(4.27, "Controllers are removed in favor of Ports.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are removed in favor of Ports."))` — DEPRECATED 4.27
- L113 _public prototype_ `TArray<UDMXEntityController*> GetAllControllersInLibrary(const UDMXLibrary* DMXLibrary);` — `UE_DEPRECATED(4.27, "Controllers are removed in favor of Ports.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are removed in favor of Ports."))` — DEPRECATED 4.27
- L118 _public prototype_ `UDMXEntityController* GetControllerByName(const UDMXLibrary* DMXLibrary, const FString& Name);` — `UE_DEPRECATED(4.27, "Controllers are removed in favor of Ports.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (AutoCreateRefTerm = "Name"), meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are removed in favor of Ports."))` — DEPRECATED 4.27
- L122 _public prototype_ `TArray<UDMXLibrary*> GetAllDMXLibraries();` — `UE_DEPRECATED(5.5, "Renamed to UDMXSubsystem::LoadAllDMXLibrariesSynchronous. See also UDMXSubsystem::GetDMXLibraries to get soft object ptrs for all DMX Libraries.")` — DEPRECATED 5.5, instead use 'Load All DMX Libraries Synchronous'
- L126 _public prototype_ `TArray<UDMXLibrary*> LoadDMXLibrariesSynchronous() const;` — `UFUNCTION(BlueprintCallable, Category = "DMX", Meta = (DisplayName = "Load DMX Libraries Synchronous"))` — Loads all DMX Libraries in this project synchronous, returns an array of DMX Libraries
- L130 _public prototype_ `TArray<TSoftObjectPtr<UDMXLibrary>> GetDMXLibraries() const;` — `UFUNCTION(BlueprintCallable, Category = "DMX", Meta = (DisplayName = "Get DMX Libraries"))` — Gets all DMX Libraries in this project, returns an array of Soft Object References to the DMX Libraries without loading them.
- L141 _public prototype_ `int32 BytesToInt(const TArray<uint8>& Bytes, bool bUseLSB = false) const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Converts consecutive DMX channel values to a signed 32bit integer value. @param Bytes				The byte array that is converted to a normalized value. Up to 3 bytes (24 bits) are supported. @param bUseLSB			When true, the byte array is interpreted in little endian format (least significant byte first) otherwise big endian. @return					The signed 32bit integer value.
- L152 _public prototype_ `float BytesToNormalizedValue(const TArray<uint8>& Bytes, bool bUseLSB = false) const;` — `UFUNCTION(BlueprintPure, Category = "DMX", meta = (Keywords = "float"))` — Converts consecutive DMX channel values to a normalized value. @param Bytes				The byte array that is converted to a normalized value. Up to 4 bytes (32 bits) are supported. @param bUseLSB			When true, the byte array is returned in little endian format (least significant byte first) otherwise big endian. @return					The normalized value.
- L163 _public prototype_ `void NormalizedValueToBytes(float InValue, EDMXFixtureSignalFormat InSignalFormat, TArray<uint8>& Bytes, bool bUseLSB = false) const;` — `UFUNCTION(BlueprintPure, Category = "DMX", meta = (Keywords = "float"))` — Converts a normalized value to an array of DMX channel values. @param InValue			The normalized floating point value in the range of 0.0 - 1.0. Other values get clamped. @param InSignalFormat	Specifies the resolution of the resulting byte array, hence the precision of resulting data (e.g. 0-65535 for 16bit). @param Bytes				The resulting byte array. @param bUseLSB			When true, the byte array is returned in little endian format (least significant byte first) otherwise big endian.
- L174 _public prototype_ `static void IntValueToBytes(int32 InValue, EDMXFixtureSignalFormat InSignalFormat, TArray<uint8>& Bytes, bool bUseLSB = false);` — `UFUNCTION(BlueprintPure, Category = "DMX", Meta = (DisplayName = "Int To Bytes"))` — Converts a signed 32bit integer value to an array of DMX channel values. @param InValue			The signed 32bit integer value. The value range depends on the signal format. Excess values get clamped. @param InSignalFormat	Specifies the resolution of the resulting byte array, hence the precision of resulting data (e.g. 0-65535 for 16bit). @param Bytes				The resulting byte array. @param bUseLSB			When true, the byte array is returned in little endian format (least significant byte first) otherwise big endian.
- L185 _public prototype_ `float IntToNormalizedValue(int32 InValue, EDMXFixtureSignalFormat InSignalFormat) const;` — `UFUNCTION(BlueprintPure, Category = "DMX", meta = (Keywords = "float"))` — Converts a signed 32bit integer value to a normalized value. @param InValue			The signed 32bit integer value. The value range depends on the signal format (e.g. 0-65535 for 16bit). Excess values get clamped. @param bUseLSB			When true, the byte array is returned in little endian format (least significant byte first) otherwise big endian. @return					The normalized value.
- L194 _public prototype_ `float GetNormalizedAttributeValue(UDMXEntityFixturePatch* InFixturePatch, FDMXAttributeName InFunctionAttribute, int32 InValue) const;` — `UE_DEPRECATED(5.5, "Instead please call the optimized UDMXEntityFixturePatch::GetAttributeValue to retrieve the attribute value.")` — `UFUNCTION(BlueprintPure, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 5.5. Instead please call the optimized Fixture Patch function 'Get Attribute Value' to retrieve the attribute value."))` — Return the normalized value of an Int value from a Fixture Patch function. @return	The normalized value of the passed in Int using the Function's signal format. -1.0 if the Function is not found in the Fixture Patch.
- L203 _public prototype_ `UDMXEntityFixtureType* GetFixtureType(FDMXEntityFixtureTypeRef InFixtureType);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"), Category = "DMX")` — Gets the Fixture Type from a Fixture Type Reference. @param	InFixtureType		Can be used to set the Fixture Type of the reference. @return						The referenced Fixture Type or nullptr if no valid Fixture Type is referenced.
- L212 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch(FDMXEntityFixturePatchRef InFixturePatch);` — `UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"), Category = "DMX")` — Gets the Fixture Patch from a Fixture Patch Reference. @param	InFixturePatch		Can be used to set the referenced Fixture Patch of the reference. @return						The referenced Fixture Patch or nullptr if no valid Fixture Patch is referenced.
- L221 _public prototype_ `bool GetFunctionsMap(UDMXEntityFixturePatch* InFixturePatch, TMap<FDMXAttributeName, int32>& OutAttributesMap);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "TRUE", AutoCreateRefTerm = "SelectedProtocol"), Category = "DMX")` — Gets a function map based on you active mode from FixturePatch @param	InFixturePatch Selected Patch @param	OutAttributesMap Function and Channel value output map @return	True if outputting was successfully
- L232 _public prototype_ `bool GetFunctionsMapForPatch(UDMXEntityFixturePatch* InFixturePatch, TMap<FDMXAttributeName, int32>& OutAttributesMap);` — `UE_DEPRECATED(5.5, "Duplicate of GetFunctionsMap. Instead please call UDMXSubsystem::GetFunctionsMap or UDMXEntityFixturePatch::GetAttributeValue.")` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "TRUE", AutoCreateRefTerm = "SelectedProtocol", DeprecatedFunction, DeprecationMessage = "Duplicate of GetFunctionsMap. Instead please call DMXSubsystem::GetFunctionsMap or DMXEntityFixturePatch::GetAttributeValues."), Category = "DMX")` — Gets a function map based on you active mode from FixturePatch, but instead of passing a Protocol as parameters, it looks for the first Protocol found in the Patch's universe and use that one @param	InFixturePatch Selected Patch @param	OutAttributesMap Function and Channel value output map @return	True if outputting was successfully
- L241 _public prototype_ `int32 GetFunctionsValue(const FName FunctionAttributeName, const TMap<FDMXAttributeName, int32>& InAttributesMap);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "TRUE", AutoCreateRefTerm = "InName, InAttributesMap"), Category = "DMX")` — Gets function channel value by input function name @param	InName Looking fixture function name @param	InAttributesMap Function and Channel value input map @return	Function channel value
- L251 _public prototype_ `bool PatchIsOfSelectedType(UDMXEntityFixturePatch* InFixturePatch, FString RefTypeValue);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "TRUE"), Category = "DMX")` — Returns true if a Fixture Patch is of a given FixtureType @param	InFixturePatch Fixture Patch to check @param	RefTypeValue a FixtureTypeRef to check against the Fixture Patch. @return	Returns true if the Fixture Patch matches the Fixture Type.
- L255 _public prototype_ `static UDMXSubsystem* GetDMXSubsystem_Pure();` — `UFUNCTION(BlueprintPure, Category = "DMX Subsystem", meta = (BlueprintInternalUseOnly = "true"))` — Get the DMX Subsystem, pure.
- L259 _public prototype_ `static UDMXSubsystem* GetDMXSubsystem_Callable();` — `UFUNCTION(BlueprintCallable, Category = "DMX Subsystem", meta = (BlueprintInternalUseOnly = "true"))` — Get the DMX Subsystem, callable.
- L268 _public prototype_ `FName GetAttributeLabel(FDMXAttributeName AttributeName);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Gets the FName of an Attribute Name. @param AttributeName		The Attribute Name struct. @return					The name of the Attribute
- L272 _public member_ `FProtocolReceivedDelegate OnProtocolReceived_DEPRECATED;` — `UE_DEPRECATED(4.26, "Use DMXComponent's OnFixturePatchReceived event or GetRawBuffer instead.")` — `UPROPERTY(BlueprintAssignable, Category = "DMX", meta = (DeprecatedProperty, DeprecationMessage = "WARNING: This can execute faster than tick leading to possible blueprint performance issues. Use DMXComponent's OnFixturePatchReceived event or GetRawBuffer instead."))`
- L277 _public prototype_ `bool SetMatrixCellValue(UDMXEntityFixturePatch* FixturePatch, FIntPoint Coordinate , FDMXAttributeName Attribute, int32 Value);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::SetMatrixCellValue instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::SendMatrixCellValue instead"))` — Set DMX Cell value using matrix coordinates.
- L282 _public prototype_ `bool GetMatrixCellValue(UDMXEntityFixturePatch* FixturePatch, FIntPoint Coordinate , TMap<FDMXAttributeName, int32>& AttributeValueMap);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetMatrixCellValue instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetMatrixCellValues instead"))` — Get DMX Cell value using matrix coordinates.
- L287 _public prototype_ `bool GetMatrixCellChannelsRelative(UDMXEntityFixturePatch* FixturePatch, FIntPoint Coordinate , TMap<FDMXAttributeName, int32>& AttributeChannelMap);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetMatrixCellChannelsRelative instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetMatrixCellChannelsRelative instead"))` — Gets the starting channel of each cell attribute at given coordinate, relative to the Starting Channel of the patch.
- L292 _public prototype_ `bool GetMatrixCellChannelsAbsolute(UDMXEntityFixturePatch* FixturePatch, FIntPoint Coordinate , TMap<FDMXAttributeName, int32>& AttributeChannelMap);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetMatrixCellChannelsAbsolute instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetMatrixCellChannelsAbsolute instead"))` — Gets the absolute starting channel of each cell attribute at given coordinate
- L297 _public prototype_ `bool GetMatrixProperties(UDMXEntityFixturePatch* FixturePatch, FDMXFixtureMatrix& MatrixProperties);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetMatrixProperties instead.")` — `UFUNCTION(BlueprintPure, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetMatrixProperties instead"))` — Get Matrix Fixture properties
- L302 _public prototype_ `bool GetCellAttributes(UDMXEntityFixturePatch* FixturePatch, TArray<FDMXAttributeName>& CellAttributes);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetCellAttributes instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetCellAttributes instead"))` — Get all attributes for the Fixture Patch.
- L307 _public prototype_ `bool GetMatrixCell(UDMXEntityFixturePatch* FixturePatch, FIntPoint Coordinate , FDMXCell& Cell);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetMatrixCell instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetMatrixCell instead"))` — Get data for single cell.
- L312 _public prototype_ `bool GetAllMatrixCells(UDMXEntityFixturePatch* FixturePatch, TArray<FDMXCell>& Cells);` — `UE_DEPRECATED(4.27, "Use UDMXEntityFixturePatch::GetAllMatrixCells instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. DMXEntityFixurePatch::GetAllMatrixCells instead"))` — Get array of all cells and associated data.
- L316 _public prototype_ `void PixelMappingDistributionSort(EDMXPixelMappingDistribution InDistribution, int32 InNumXPanels, int32 InNumYPanels, const TArray<int32>& InUnorderedList, TArray<int32>& OutSortedList);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sort an array according to the selected distribution pattern.
- L321 _public member_ `FSimpleMulticastDelegate OnAllDMXLibraryAssetsLoaded;` — `UE_DEPRECATED(5.5, "DMX Libraries are no longer loaded by default and this delegate is no longer raised. Instead please use UDMXSubsystem::GetDMXLibraries or UDMXSubsystem::LoadDMXLibrariesSynchronous.")` — Delegate broadcast when all DMX Library assets were loaded
- L326 _public member_ `FDMXOnDMXLibraryAssetDelegate OnDMXLibraryAssetAdded;` — `UE_DEPRECATED(5.5, "DMX Libraries are no longer loaded by default and this delegate is no longer raised. Instead please refer to the asset subsystem directly. See IAssetRegistry::OnAssetAdded.")` — Delegate broadcast when a DMX Library asset was added
- L330 _public member_ `FDMXOnDMXLibraryAssetDelegate OnDMXLibraryAssetRemoved;` — `UE_DEPRECATED(5.5, "DMX Libraries are no longer loaded by default and this delegate is no longer raised. Instead please refer to the asset subsystem directly. See IAssetRegistry::OnAssetRemoved.")` — Delegate broadcast when a DMX Library asset was removed

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProtocolReceivedDelegate, FDMXProtocolName, Protocol, int32, RemoteUniverse, const TArray<uint8>&, DMXBuffer);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProtocolReceivedDelegate, FDMXProtocolName, Protocol, int32, RemoteUniverse, const TArray<uint8>&, DMXBuffer);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnDMXLibraryAssetDelegate, UDMXLibrary*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnDMXLibraryAssetDelegate, UDMXLibrary*);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/DMXTypes.h` (Public)


#### struct `FDMXNormalizedAttributeValueMap`  
`struct FDMXNormalizedAttributeValueMap`  
_L18-24_
- reflection: `USTRUCT(BlueprintType, Category = "DMX", meta = (DisplayName = "DMX Normalized Attribute Value Map"))`
- desc: Holds an array Attribute Names with their normalized Values (expand the property to see the map)
- L23 _public member_ `TMap<FDMXAttributeName, float> Map;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")`

#### struct `FDMXByteArray64`  
`struct FDMXByteArray64`  
_L27-65_
- reflection: `USTRUCT()`
- L31 _public member_ `TArray64<uint8> ByteArray;`
- L33 _public function_ `const FDMXByteArray64& operator=(const FDMXByteArray64& Rhs)`
- L38 _public function_ `const FDMXByteArray64& operator=(const TArray64<uint8>& Rhs)`
- L54 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXByteArray64> : public TStructOpsTypeTraitsBase2<FDMXByteArray64>`  
_L68-77_
- inherits: `TStructOpsTypeTraitsBase2<FDMXByteArray64>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-76_

#### struct `FDMXRequestBase`  
`struct FDMXRequestBase`  
_L81-90_
- reflection: `UE_DEPRECATED(5.5, "This stuct had no specific use and is now deprecated.")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Deprecated 5.5. This stuct had no specific use and is now deprecated."))`
- L88 _public member_ `uint8 Value = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX")`

#### struct `FDMXRequest`  
`struct FDMXRequest : public FDMXRequestBase`  
_L95-104_
- reflection: `UE_DEPRECATED(5.5, "This stuct had no specific use and is now deprecated.")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Deprecated 5.5. This stuct had no specific use and is now deprecated."))`
- inherits: `FDMXRequestBase`
- L102 _public member_ `TSubclassOf<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|Request")`

#### struct `FDMXRawArtNetRequest`  
`struct FDMXRawArtNetRequest : public FDMXRequestBase`  
_L110-128_
- reflection: `UE_DEPRECATED(5.5, "This stuct had no specific use and is now deprecated.")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Deprecated 5.5. This stuct had no specific use and is now deprecated."))`
- inherits: `FDMXRequestBase`
- L117 _public member_ `int32 Net = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta=(ClampMin=0, ClampMax=137, UIMin = 0, UIMax = 137))`
- L120 _public member_ `int32 SubNet = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta = (ClampMin = 0, ClampMax = 15, UIMin = 0, UIMax = 15))`
- L123 _public member_ `int32 Universe = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta = (ClampMin = 0, ClampMax = 15, UIMin = 0, UIMax = 15))`
- L126 _public member_ `int32 Address = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta = (ClampMin = 1, ClampMax = 512, UIMin = 1, UIMax = 512))`

#### struct `FDMXRawSACN`  
`struct FDMXRawSACN : public FDMXRequestBase`  
_L134-145_
- reflection: `UE_DEPRECATED(5.5, "This stuct had no specific use and is now deprecated.")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Deprecated 5.5. This stuct had no specific use and is now deprecated."))`
- inherits: `FDMXRequestBase`
- L141 _public member_ `int32 Universe = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta = (ClampMin = 0, ClampMax = 63999, UIMin = 0, UIMax = 63999))`
- L144 _public member_ `int32 Address = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX|RawRequest", meta = (ClampMin = 0, ClampMax = 512, UIMin = 0, UIMax = 512))`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef FDMXGDTFColorCIE1931xyY FDMXColorCIE1931xyY;` — `UE_DEPRECATED(5.5, "FDMXColorCIE1931xyY is deprecated. Please use FDMXGDTFColorCIE1931xyY instead.")`
- L44 _function_ `friend bool operator==(const FDMXByteArray64& A, const FDMXByteArray64& B)`
- L49 _function_ `friend bool operator!=(const FDMXByteArray64& A, const FDMXByteArray64& B)`
- L60 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXByteArray64& Struct)`
- L73 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon0d2ac8680103`)
- L74 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon0d2ac8680103`)
- L75 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon0d2ac8680103`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Game/DMXComponent.h` (Public)


#### class `UDMXComponent`  
`class UDMXComponent : public UActorComponent`  
_L23-93_
- reflection: `UCLASS(ClassGroup=(DMX), meta=(BlueprintSpawnableComponent), HideCategories = ("Variable", "Sockets", "Activation", "Cooking", "ComponentReplication", "Collision", "ComponentTick"))`
- inherits: `UActorComponent`
- desc: Component that receives DMX input each Tick from a fixture patch.
- L28 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDMXComponentFixturePatchReceivedSignature, UDMXEntityFixturePatch*, FixturePatch, const FDMXNormalizedAttributeValueMap&, ValuePerAttribute);`
- L29 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDMXOnDMXComponentTickSignature, float, DeltaTime);`
- L32 _public prototype_ `UDMXComponent();`
- L36 _public member_ `FDMXComponentFixturePatchReceivedSignature OnFixturePatchReceived;` — `UPROPERTY(BlueprintAssignable, Category = "DMX")` — Broadcast when the component's fixture patch received DMX
- L44 _public member_ `FDMXOnDMXComponentTickSignature OnDMXComponentTick;` — `UPROPERTY(BlueprintAssignable, Category = "DMX", Meta = (DisplayName = "On DMX Component Tick"))` — Event raised each tick, when the component has a Fixture Patch set and either: - The assigned fixture patch is set to 'receives DMX in editor'. - Project Settings -> Plugins -> DMX -> 'Fixture Patches receive DMX in Editor' is set to true.
- L48 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the fixture patch used in the component
- L52 _public prototype_ `void SetFixturePatch(UDMXEntityFixturePatch* InFixturePatch);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets the fixture patch used in the component
- L56 _public prototype_ `void SetReceiveDMXFromPatch(bool bReceive);` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DisplayName = "Set Receive DMX From Patch"))` — Sets whether the component receives dmx from the patch. Note, this is saved with the component when called in editor.
- L59 _public member_ `FDMXEntityFixturePatchRef FixturePatchRef;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DMX", Meta = (ShowOnlyInnerProperties))`
- L64 _protected prototype_ `void OnFixturePatchReceivedDMX(UDMXEntityFixturePatch* FixturePatch, const FDMXNormalizedAttributeValueMap& NormalizedValuePerAttribute);` — `UFUNCTION()` — Called when the fixture patch received DMX
- L67 _protected prototype_ `void SetupReceiveDMXBinding();` — Sets up binding for receiving depending on the patch's and the component's properties
- L70 _protected prototype_ `void UpdateTickEnabled();` — Enables or disables the component tick depending of it being required for the OnDXMComponentTick function
- L74 _protected member_ `bool bReceiveDMXFromPatch;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = "DMX", Meta = (DisplayPriority = 0))` — If true, the component will receive DMX from the patch
- L77 _protected prototype_ `virtual void OnRegister() override;`
- L78 _protected prototype_ `virtual void BeginPlay() override;`
- L79 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L80 _protected prototype_ `virtual void DestroyComponent(bool bPromoteChildren) override;`
- L83 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L88 _private prototype_ `virtual void OnAllFixturePatchesReceiveDMXInEditorEnabled(bool bEnabled);` — Called when receive DMX in Editor was enabled or disabled for DMX Components (via DMXProtocolSettings)
- L91 _private prototype_ `void OnFixturePatchPropertiesChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when the fixture patch changed. Can be editor only as we only want to update the component tick

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDMXComponentFixturePatchReceivedSignature, UDMXEntityFixturePatch*, FixturePatch, const FDMXNormalizedAttributeValueMap&, ValuePerAttribute);`
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDMXOnDMXComponentTickSignature, float, DeltaTime);`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntity.h` (Public)


#### class `UDMXEntity`  
`class UDMXEntity : public UDMXObjectBase`  
_L17-85_
- reflection: `UCLASS(abstract, meta = (DisplayName = "DMX Entity"))`
- inherits: `UDMXObjectBase`
- desc: Base class for all entity types
- L24 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity Properties", meta = (DisplayName = "Name", DisplayPriority = "1"))`
- L28 _public prototype_ `UDMXEntity();` — Constructor, for default objects only
- L31 _public prototype_ `UDMXEntity(UDMXLibrary* InParentLibrary);` — Constructor that specifies the outer Library
- L34 _public prototype_ `virtual void PostInitProperties() override;`
- L38 _public prototype_ `void Destroy();` — Destroys the Entity
- L41 _public prototype_ `FString GetDisplayName() const;` — Returns the entity name to be used in UI elements
- L44 _public prototype_ `void SetName(const FString& InNewName);` — Updates this Entity's name and the UI friendly display name
- L51 _public function_ `virtual bool IsValidEntity(FText& OutReason) const` — Checks for Entity correctness for usability with protocols. @param OutReason	Reason for being invalid, if that's the case. @return True if the Entity can be used with protocols.
- L57 _public function_ `virtual bool IsValidEntity() const` — Checks for Entity correctness for usability with protocols. @return True if the Entity can be used with protocols.
- L64 _public prototype_ `void SetParentLibrary(UDMXLibrary* InParent);` — Sets the DMX Library of the entity
- L67 _public function_ `UDMXLibrary* GetParentLibrary() const` — Gets the library the Entity resides in
- L70 _public function_ `const FGuid& GetID() const` — This Entity's unique ID
- L73 _public prototype_ `void RefreshID();` — Used by DMX Library to resolve ID conflicts among entities
- L76 _public prototype_ `void ReplicateID(UDMXEntity* Other);` — Copy another Entity's ID. Used when copying, to not lose the original Entity's reference
- L80 _protected member_ `TWeakObjectPtr<UDMXLibrary> ParentLibrary;` — `UPROPERTY()`
- L84 _protected member_ `FGuid Id;` — `UPROPERTY(DuplicateTransient)` — Uniquely identifies the parameter, used for fixing up Blueprints that reference this Entity when renaming.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntityController.h` (Public)


#### class `UDMXEntityUniverseManaged`  
`class UDMXEntityUniverseManaged : public UDMXEntity`  
_L15-24_
- reflection: `UE_DEPRECATED(4.27, "DMXEntityUniverseManaged and DMXEntityController are deprecated in favor of the DMX Port System. Please refer to FDMXPortManager instead.")`
- reflection: `UCLASS()`
- inherits: `UDMXEntity`
- L23 _public member_ `FDMXProtocolName DeviceProtocol;` — `UE_DEPRECATED(4.27, "UDMXEntityUniverseManaged is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`

#### class `UDMXEntityController`  
`class UDMXEntityController : public UDMXEntityUniverseManaged`  
_L28-83_
- reflection: `UCLASS()`
- inherits: `UDMXEntityUniverseManaged`
- L38 _public member_ `EDMXCommunicationType CommunicationMode;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`
- L42 _public member_ `int32 UniverseLocalStart;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`
- L46 _public member_ `int32 UniverseLocalNum;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`
- L50 _public member_ `int32 UniverseLocalEnd;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`
- L62 _public member_ `int32 RemoteOffset;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))` — Offsets the Universe IDs range on this Controller before communication with other devices. Useful to solve conflicts with Universe IDs from other devices on the same network. All other DMX Library settings use the normal Universe IDs range. This allows the user to change all Universe IDs used by the Fixture Patches and avoid conflicts with other devices by updating only the Controller's Remote Offset.
- L70 _public member_ `int32 UniverseRemoteStart;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))` — First Universe ID on this Controller's range that is sent over the network. Universe Start + Remote Offset
- L78 _public member_ `int32 UniverseRemoteEnd;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))` — Last Universe ID in this Controller's range that is sent over the network. Universe End + Remote Offset
- L82 _public member_ `TArray<FString> AdditionalUnicastIPs;` — `UE_DEPRECATED(4.27, "UDMXEntityController is deprecated. Use Ports instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Controllers are no longer in use. Use Ports instead."))`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntityFixturePatch.h` (Public)


#### struct `FDMXEntityFixturePatchConstructionParams`  
`struct FDMXEntityFixturePatchConstructionParams`  
_L29-64_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Entity Fixture Patch Construction Params"))`
- desc: Parameters to construct a Fixture Patch.
- L35 _public member_ `FDMXEntityFixtureTypeRef FixtureTypeRef;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Fixture Patch", meta = (DisplayName = "Fixture Type"))` — The fixture type of the newly constructed fixture patch
- L39 _public member_ `int32 ActiveMode = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch")` — The index of the mode in the fixture type the fixture patch uses
- L43 _public member_ `int32 UniverseID = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixture Patch", meta = (ClampMin = 0, DisplayName = "Universe"))` — The local universe of the fixture patch
- L47 _public member_ `int32 StartingAddress = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixture Patch", meta = (DisplayName = "Starting Channel", UIMin = "1", UIMax = "512", ClampMin = "1", ClampMax = "512"))` — Starting channel for when auto-assign address is false
- L55 _public member_ `FTransform DefaultTransform = FTransform::Identity;` — The transform used when the DMX Library is spawned in a level. When the DMX Library is exported as an MVR file, this transform is used unless the 'Use Transforms from Level' export option is checked.
- L63 _public member_ `FGuid MVRFixtureUUID;` — When spawning the DMX Library as MVR Scene in Editor, each Fixture Patch has to correspond to a Fixture in the World (if it is desired to export the Scene as MVR later). Mostly useful when importing an MVR into the DMX Library (see DMXLibraryFromMVRFactory). If left '00000000-00000000-00000000-00000000', a Unique ID will be generated for the patch. Ensures the Unique ID is not used by another patch in the DMX Library already.

#### class `UDMXEntityFixturePatch`  
`class UDMXEntityFixturePatch : public UDMXEntity , public FTickableGameObject`  
_L73-531_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "DMX Fixture Patch"))`
- inherits: `UDMXEntity,FTickableGameObject`
- desc: A DMX fixture patch that can be patch to channels in a DMX Universe via the DMX Library Editor. Use in DMXComponent or call SetReceiveDMXEnabled with 'true' to enable receiving DMX.
- L79 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDMXOnFixturePatchReceivedDMXDelegate, UDMXEntityFixturePatch*, FixturePatch, const FDMXNormalizedAttributeValueMap&, ValuePerAttribute);`
- L84 _public prototype_ `UDMXEntityFixturePatch();`
- L88 _public prototype_ `static UDMXEntityFixturePatch* CreateFixturePatchInLibrary(FDMXEntityFixturePatchConstructionParams ConstructionParams, const FString& DesiredName = TEXT(""), bool bMarkDMXLibraryDirty = true);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Creates a new Fixture Patch in the DMX Library using the specified Fixture Type
- L92 _public prototype_ `static void RemoveFixturePatchFromLibrary(FDMXEntityFixturePatchRef FixturePatchRef);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Removes a fixture patch from the DMX Library
- L96 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L99 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L100 _protected prototype_ `virtual void PostInitProperties() override;`
- L101 _protected prototype_ `virtual void PostLoad() override;`
- L104 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L105 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L110 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L111 _protected prototype_ `virtual bool IsTickable() const override;`
- L112 _protected prototype_ `virtual bool IsTickableInEditor() const override;`
- L113 _protected prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L114 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L119 _public prototype_ `static FDMXOnFixturePatchChangedDelegate& GetOnFixturePatchChanged();` — Returns a delegate that is and should be broadcast whenever a Fixture Type changed
- L123 _public prototype_ `void SendDMX(TMap<FDMXAttributeName, int32> AttributeMap);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Send DMX using attribute names and integer values.
- L130 _public prototype_ `void SendDefaultValues();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sends the default value for all attributes, including matrix attributes. Note, calls will not be considered by the DMX Conflict Monitor.
- L137 _public prototype_ `void SendZeroValues();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sends zeroes for all attributes, including matrix attributes. Note, calls will not be considered by the DMX Conflict Monitor.
- L143 _public prototype_ `void RebuildCache();` — Rebuilds the cache. Should be called when relevant properties, for example the starting channel changed. This will not clear cached DMX data.
- L146 _public function_ `const FDMXSignalSharedPtr& GetLastReceivedDMXSignal() const` — Returns the last received DMX signal.
- L155 _public member_ `FDMXOnFixturePatchReceivedDMXDelegateNative OnFixturePatchReceivedDMXNative;` — Delegate broadcast when the fixture patch received DMX. This event only fires when any attribute value changed. Use GetAttributeValues or GetNormalizedAttributeValues to get unchanged values. Native version, should be preferred when binding UObjects in C++ to avoid serializing the reference.
- L163 _public member_ `FDMXOnFixturePatchReceivedDMXDelegate OnFixturePatchReceivedDMX;` — `UPROPERTY(BlueprintAssignable, Category = "DMX")` — Returns a delegate broadcast when the fixture patch received DMX. This event only fires when any attribute value changed. Use GetAttributeValues or GetNormalizedAttributeValues to get unchanged values.
- L167 _private prototype_ `bool UpdateCache();` — Updates the cache. Returns true if the values got updated (if the values changed)
- L170 _private member_ `FDMXSignalSharedPtr LastDMXSignal;` — The last received DMX signal
- L173 _private member_ `FDMXEntityFixturePatchCache Cache;` — Cache of dmx values
- L177 _public prototype_ `virtual bool IsValidEntity(FText& OutReason) const override;`
- L181 _public prototype_ `void ValidateActiveMode();` — Called from Fixture Type to keep ActiveMode in valid range when Modes are removed from the Type
- L184 _public prototype_ `const FDMXFixtureMode* GetActiveMode() const;` — Returns the active mode, or nullptr if there is no valid active mode
- L187 _public function_ `UDMXEntityFixtureType* GetFixtureType() const` — Gets the parent fixture type this was constructed from
- L191 _public prototype_ `void SetFixtureType(UDMXEntityFixtureType* NewFixtureType);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Sets the fixture type this is using
- L194 _public function_ `int32 GetUniverseID() const` — Returns the universe ID of the patch
- L198 _public prototype_ `void SetUniverseID(int32 NewUniverseID);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Sets the Universe ID of the patch
- L202 _public prototype_ `void SetStartingChannel(int32 NewStartingChannel);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Sets the starting channel of the Fixture Patch.
- L206 _public function_ `int32 GetStartingChannel() const` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Return the starting channel
- L210 _public prototype_ `int32 GetChannelSpan() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns the number of channels this Patch occupies with the Fixture functions from its Active Mode or 0 if the patch has no valid Active Mode
- L214 _public prototype_ `int32 GetEndingChannel() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns the last channel of the patch
- L217 _public prototype_ `bool SetActiveModeIndex(int32 NewActiveModeIndex);` — Sets the index of the Mode the Patch uses from its Fixture Type
- L220 _public function_ `int32 GetActiveModeIndex() const` — Returns the index of the Mode the Patch uses from its Fixture Type
- L223 _public function_ `const TArray<FName>& GetCustomTags() const` — Returns custom tags defined for the patch
- L226 _public function_ `const FGuid& GetMVRFixtureUUID() const` — Returns the MVR Fixture UUIDs of this patch
- L229 _public function_ `int32 GetFixtureID() const` — Returns the MVR Fixture ÎD of this patch
- L235 _public prototype_ `void GenerateFixtureID(int32 DesiredFixtureID = -1);` — Generates a unique Fixture ID for this patch. If DesiredFixtureID is > 0, tries to use this fixture ID, generates a unique one if the desired Fixture ID was already in use.
- L242 _public prototype_ `bool FindFixtureID(int32& OutFixtureID) const;` — `UE_DEPRECATED(5.5, "The patches now hold their Fixture ID. Use UDMXEntityFixturePatch::GetFixtureID.")` — Tries to find the fixture ID of the patch. Looks up the general scene description resulting in a relatively slow operation. Returns false if the patch has no fixture ID could be found, typically the case when the patch is no valid MVR Fixture.
- L250 _public function_ `void SetDefaultTransform(const FTransform& NewDefaultTransform)` — Sets The transform used when the DMX Library is spawned in a level. When the DMX Library is exported as an MVR file, this transform is used unless the 'Use Transforms from Level' export option is checked.
- L257 _public function_ `const FTransform& GetDefaultTransform() const` — Returns The transform used when the DMX Library is spawned in a level. When the DMX Library is exported as an MVR file, this transform is used unless the 'Use Transforms from Level' export option is checked.
- L260 _public function_ `static FName GetUniverseIDPropertyNameChecked()` — Property name getters. When accessing the this way, use with care. The patch will need to update its cache after using property setters, use Pre/PostEditChanged events to achieve that.
- L261 _public function_ `static FName GetParentFixtureTypeTemplatePropertyNameChecked()`
- L262 _public function_ `static FName GetActiveModePropertyNameChecked()`
- L263 _public function_ `static FName GetDefaultTransformPropertyNameChecked()`
- L264 _public function_ `static FName GetMVRFixtureUUIDPropertyNameChecked()`
- L265 _public function_ `static FName GetFixtureIDPropertyNameChecked()`
- L266 _public function_ `static FName GetStartingChannelPropertyNameChecked()`
- L272 _protected member_ `int32 UniverseID;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch", meta = (ClampMin = 0))` — The local universe of the patch
- L277 _protected member_ `bool bAutoAssignAddress_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bAutoAssignAddress and related members are deprecated. Auto assign is now only a method in FDMXEditorUtils and should be applied on demand."))` — DEPRECATED 5.1
- L281 _protected member_ `int32 ManualStartingAddress_DEPRECATED = 1;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bAutoAssignAddress and related members are deprecated. Auto assign is now only a method in FDMXEditorUtils and should be applied on demand."))` — DEPRECATED 5.1
- L285 _protected member_ `int32 AutoStartingAddress_DEPRECATED = 1;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bAutoAssignAddress and related members are deprecated. Auto assign is now only a method in FDMXEditorUtils and should be applied on demand."))` — DEPRECATED 5.1
- L290 _protected member_ `int32 StartingChannel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch", meta = (UIMin = "1", UIMax = "512", ClampMin = "1", ClampMax = "512"))` — Starting Channel of the Patch
- L294 _protected member_ `TObjectPtr<UDMXEntityFixtureType> ParentFixtureTypeTemplate;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, BlueprintSetter = SetFixtureType, Category = "Fixture Patch", meta = (DisplayName = "Fixture Type"))` — The Fixture Type that defines the DMX channel layout of this Fixture Patch
- L298 _protected member_ `int32 ActiveMode = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Active Mode Index"), Category = "Fixture Patch")` — The Index of the Mode in the Fixture Type the Patch uses
- L307 _protected member_ `FTransform DefaultTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MVR")` — The transform used when the DMX Library is spawned in a level. When the DMX Library is exported as an MVR file, this transform is used unless the 'Use Transforms from Level' export option is checked.
- L312 _protected member_ `int32 FixtureID = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MVR")` — The Fixture ID of this patch
- L316 _protected member_ `FGuid MVRFixtureUUID;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (DisplayName = "MVR Fixture UUID"), Category = "MVR")` — The MVR Fixture UUID
- L319 _protected member_ `static FDMXOnFixturePatchChangedDelegate OnFixturePatchChangedDelegate;` — Delegate broadcast when a Fixture Patch changed
- L324 _public member_ `TArray<FName> CustomTags;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch")` — Custom tags for filtering patches
- L329 _public member_ `FLinearColor EditorColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch")` — Color when displayed in the fixture patch editor
- L336 _public member_ `bool bReceiveDMXInEditor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Patch")` — If true, the patch receives dmx and raises the OnFixturePatchReceivedDMX events in editor. NOTE: If 'All Fixture Patches receive DMX in editor' is set to true in Project Settings -> Plugins -> DMX, this setting here is ignored.
- L344 _public prototype_ `int32 GetRemoteUniverse() const;` — `UE_DEPRECATED(4.27, "Controllers are replaced with DMX Ports.")` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. No clear remote universe can be deduced from controllers (before 4.27) or ports (from 4.27 on)."))` — DEPRECATED 4.27
- L352 _public prototype_ `TArray<FDMXAttributeName> GetAllAttributesInActiveMode() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns an array of attributes for the currently active mode. Attributes outside the Active Mode's channel span range are ignored.
- L359 _public prototype_ `TMap<FDMXAttributeName, FDMXFixtureFunction> GetAttributeFunctionsMap() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns a map of attributes and function names. Attributes outside the Active Mode's channel span range are ignored.
- L366 _public prototype_ `TMap<FDMXAttributeName, int32> GetAttributeDefaultMap() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns a map of function names and default values. Functions outside the Active Mode's channel span range are ignored.
- L370 _public prototype_ `TMap<FDMXAttributeName, int32> GetAttributeChannelAssignments() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns a map of Attributes and their assigned channels
- L374 _public prototype_ `TMap<FDMXAttributeName, EDMXFixtureSignalFormat> GetAttributeSignalFormats() const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns a map of function names and their Data Types.
- L379 _public prototype_ `TMap<FDMXAttributeName, int32> ConvertRawMapToAttributeMap(const TMap<int32, uint8>& RawMap) const;` — `UE_DEPRECATED(4.27, "Deprecated since it's unclear how to use this function correctly. Use UDMXSubsystem::BytesToInt instead.")` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Please use DMXSubsystem's Bytes to Int instead, then create a map from that with Attribute Names ."))` — DEPRECATED 4.27
- L383 _public prototype_ `TMap<int32, uint8> ConvertAttributeMapToRawMap(const TMap<FDMXAttributeName, int32>& FunctionMap) const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Converts a map of Attribute Names with their DMX values to a map of DMX channels and with their DMX Values.
- L387 _public prototype_ `bool IsMapValid(const TMap<FDMXAttributeName, int32>& FunctionMap) const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns true if the Fixture Patch contains all Attributes in an Attribute Name to DMX Value Map.
- L391 _public prototype_ `bool ContainsAttribute(FDMXAttributeName FunctionAttribute) const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Returns true if the Fixture Patch contains the specified attribute and can use it to send and receive DMX
- L395 _public prototype_ `TMap<FDMXAttributeName, int32> ConvertToValidMap(const TMap<FDMXAttributeName, int32>& FunctionMap) const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Removes any Attribute Name that can not be sent or received by a Fixture Patch from an Attribute Name to DMX Value Map
- L400 _public prototype_ `TArray<UDMXEntityController*> GetRelevantControllers() const;` — `UE_DEPRECATED(4.27, "Controllers are replaced with DMX Ports.")` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are replaced with DMX Ports."))` — DEPRECATED 4.27
- L405 _public function_ `bool IsInControllerRange(const UDMXEntityController* InController) const` — `UE_DEPRECATED(4.27, "Controllers are replaced with DMX Ports.")` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are replaced with DMX Ports."))` — DEPRECATED 4.27
- L410 _public function_ `bool IsInControllersRange(const TArray<UDMXEntityController*>& InControllers) const` — `UE_DEPRECATED(4.27, "Controllers are replaced with DMX Ports.")` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.27. Controllers are replaced with DMX Ports."))` — DEPRECATED 4.27
- L420 _public prototype_ `const FDMXFixtureFunction* GetAttributeFunction(const FDMXAttributeName& Attribute) const;` — Returns the function currently mapped to the passed in Attribute, if any. If no function is mapped to it, returns nullptr. @param Attribute The attribute name to search for. @return			The function mapped to the passed in Attribute or nullptr if no function is mapped to it.
- L430 _public prototype_ `int32 GetAttributeValue(FDMXAttributeName Attribute, bool& bSuccess);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Retrieves the value of an Attribute. Will fail and return 0 if the Attribute doesn't exist. @param Attribute	The Attribute to try to get the value from. @param bSuccess	Whether the Attribute was found in this Fixture Patch @return			The value of the Function mapped to the selected Attribute, if found.
- L440 _public prototype_ `float GetNormalizedAttributeValue(FDMXAttributeName Attribute, bool& bSuccess);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 4.26. Use GetNormalizedAttributeValue instead. Note, new method returns normalized values!"))` — Retrieves the normalized value of an Attribute. Will fail and return 0 if the Attribute doesn't exist. @param Attribute	The Attribute to try to get the value from. @param bSuccess	Whether the Attribute was found in this Fixture Patch @return			The value of the Function mapped to the selected Attribute, if found.
- L445 _public prototype_ `void GetAttributesValues(TMap<FDMXAttributeName, int32>& AttributesValues);` — `UE_DEPRECATED(5.5, "Renamed to UDMXEntityFixturePatch::GetAttributeValues for consistency with similar methods.")` — DEPRECATED 5.5, renamed to GetAttributeValues.
- L453 _public prototype_ `void GetAttributeValues(TMap<FDMXAttributeName, int32>& AttributeValues);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Returns the value of each attribute, or zero if no value was ever received. @param AttributesValues	Out: Resulting map of Attributes with their values
- L457 _public prototype_ `void GetNormalizedAttributesValues(FDMXNormalizedAttributeValueMap& NormalizedAttributeValues);` — `UE_DEPRECATED(5.5, "Renamed to UDMXEntityFixturePatch::GetNormalizedAttributeValues for consistency with similar methods.")` — DEPRECATED 5.5, renamed to GetNormalizedAttributeValues.
- L465 _public prototype_ `void GetNormalizedAttributeValues(FDMXNormalizedAttributeValueMap& NormalizedAttributesValues);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Returns the normalized value of each attribute, or zero if no value was ever received. @param AttributesValues	Out: Resulting map of Attributes with their normalized values
- L469 _public prototype_ `bool SendMatrixCellValue(const FIntPoint& CellCoordinate , const FDMXAttributeName& Attribute, int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Sends the DMX value of the Attribute to specified matrix coordinates
- L474 _public prototype_ `bool SendMatrixCellValueWithAttributeMap(const FIntPoint& CellCoordinate , const FDMXAttributeName& Attribute, int32 Value, const TMap<FDMXAttributeName, int32>& InAttributeNameChannelMap);` — `UE_DEPRECATED(4.27, "Deprecated due to ambigous arguments CellCoordinate and InAttributeNameChannelMap. Use SendMatrixCellValue or SendNormalizedMatrixCellValue instead.")` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated due to ambigous arguments CellCoordinate and InAttributeNameChannelMap. Use SendMatrixCellValue or SendNormalizedMatrixCellValue instead."))` — Sends the DMX value of the Attribute to specified matrix coordinates with given Attribute Name Channel Map
- L478 _public prototype_ `bool SendNormalizedMatrixCellValue(const FIntPoint& CellCoordinate , const FDMXAttributeName& Attribute, float RelativeValue);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Maps the normalized value to the Attribute's full value range and sends it to specified matrix coordinates
- L482 _public prototype_ `bool GetMatrixCellValues(const FIntPoint& CellCoordinate , TMap<FDMXAttributeName, int32>& ValuePerAttribute);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets the DMX Cell value using matrix coordinates
- L486 _public prototype_ `bool GetNormalizedMatrixCellValues(const FIntPoint& CellCoordinate , TMap<FDMXAttributeName, float>& NormalizedValuePerAttribute);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets the DMX Cell value using matrix coordinates.
- L490 _public prototype_ `bool GetMatrixCellChannelsRelative(const FIntPoint& CellCoordinate , TMap<FDMXAttributeName, int32>& AttributeChannelMap);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets the starting channel of each cell attribute at given coordinate, relative to the Starting Channel of the patch.
- L494 _public prototype_ `bool GetMatrixCellChannelsAbsolute(const FIntPoint& CellCoordinate , TMap<FDMXAttributeName, int32>& AttributeChannelMap);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets the absolute starting channel of each cell attribute at given coordinate
- L498 _public prototype_ `bool GetMatrixCellChannelsAbsoluteWithValidation(const FIntPoint& InCellCoordinate , TMap<FDMXAttributeName, int32>& OutAttributeChannelMap);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Validates and gets the absolute starting channel of each cell attribute at given coordinate
- L502 _public prototype_ `bool GetMatrixProperties(FDMXFixtureMatrix& MatrixProperties) const;` — `UFUNCTION(BlueprintPure, Category = "DMX|Fixture Patch")` — Gets the Matrix Fixture properties, returns false if the patch is not using a matrix fixture
- L506 _public prototype_ `bool GetCellAttributes(TArray<FDMXAttributeName>& CellAttributes);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets all attributes names of a cell
- L510 _public prototype_ `bool GetMatrixCell(const FIntPoint& CellCoordinate , FDMXCell& Cell);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets the cell corresponding to the passed in coordinate
- L514 _public prototype_ `bool GetAllMatrixCells(TArray<FDMXCell>& Cells);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Patch")` — Gets all matrix cells
- L521 _private prototype_ `void SendResetDataToAllAttributes(bool bUseDefaultValues);` — Sends reset data to all channels. If bUseDefaultValues is true, sends default values. If it's false it sends zeroes. Note, this call will not raise send DMX traces.
- L524 _private prototype_ `void OnFixtureTypeChanged(const UDMXEntityFixtureType* FixtureType);` — Called when a Fixture Type changed
- L527 _private prototype_ `const FDMXFixtureMatrix* GetFixtureMatrix() const;` — Tries to access the FixtureMatrix config of this patch and logs issues. Returns the matrix of nullptr if it isn't valid.
- L530 _private prototype_ `static bool AreCoordinatesValid(const FDMXFixtureMatrix& FixtureMatrix, const FIntPoint& Coordinate, bool bLogged = true);` — Returns true if the specified coordinates are valid for the specified matrix

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnFixturePatchChangedDelegate, const UDMXEntityFixturePatch* );`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnFixturePatchChangedDelegate, const UDMXEntityFixturePatch* );`
- L79 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDMXOnFixturePatchReceivedDMXDelegate, UDMXEntityFixturePatch*, FixturePatch, const FDMXNormalizedAttributeValueMap&, ValuePerAttribute);`
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMXOnFixturePatchReceivedDMXDelegateNative, UDMXEntityFixturePatch* , const FDMXNormalizedAttributeValueMap& ) public: UDMXEntityFixturePatch();`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntityFixturePatchCache.h` (Public)


#### class `FDMXEntityFixturePatchCache`  
`class FDMXEntityFixturePatchCache`  
_L19-176_
- desc: Cache for fixture patches. This object takes care of handling the fixture patch data in a single point. The fixture patch self is used to define it.
- L23 _public prototype_ `FDMXEntityFixturePatchCache();` — Default constructor
- L32 _public prototype_ `FDMXEntityFixturePatchCache(int32 InStartingChannel, const FDMXFixtureMode* InActiveModePtr, const FDMXFixtureMatrix* InFixtureMatrixPtr);` — Constructs the cache. Arguments are used to determine what's cached. @Param InStartingChannel		The Starting Channel of the patch. @Param InActiveModePtr		Pointer to the Active Mode of the patch, or nullptr if no Active Mode is available. @Param InFixtureMatrixPtr	Pointer to the fixture matrix of the patch, or nullptr if no Fixture Matrix is available
- L35 _public function_ `bool HasValidProperties() const` — Returns true if the cache holds valid properties retrived from mode and matrix. Cached values may be empty if no signal was input yet.
- L38 _public function_ `bool IsFixtureMatrix() const` — Returns true if there is the matrix properties are valid and can ever hold data
- L45 _public prototype_ `bool InputDMXSignal(const FDMXSignalSharedPtr& DMXSignal);` — Inputs a signal into the cache. Returns true if cached data changed.
- L48 _public prototype_ `void Reset();` — Resets cached data
- L51 _public prototype_ `void Modulate(UDMXEntityFixturePatch* FixturePatch, UDMXModulator* Modulator);` — Applies the modulator to the cache
- L57 _public prototype_ `const int32* GetRawAttributeValue(const FDMXAttributeName& AttributeName) const;` — Returns the raw attribute value for the specified Attribute Name. Returns nullptr if the attribute cannot be found.
- L60 _public prototype_ `const TMap<FDMXAttributeName, int32>* GetAllRawAttributeValues() const;` — Returns all raw attribute values. Returns nullptr if there is no data
- L63 _public prototype_ `const float* GetNormalizedAttributeValue(const FDMXAttributeName& AttributeName) const;` — Returns the raw attribute value for the specified Attribute Name. Returns nullptr if the attribute cannot be found
- L66 _public prototype_ `const FDMXNormalizedAttributeValueMap* GetAllNormalizedAttributeValues() const;` — Returns all raw attribute values. Returns nullptr if there is no data
- L69 _public prototype_ `int32 GetDistributedCellIndex(const FIntPoint& CellCoordinate) const;` — Returns a pixel mapping distribution ordered Cell Index from a Cell Coordinate, or INDEX_NONE if not a valid index
- L72 _public prototype_ `int32 GetDistributedCellIndex(int32 CellIndex) const;` — Returns a pixel mapping distribution ordered Cell Index from a Cell Coordinate, or INDEX_NONE if not a valid index
- L75 _public prototype_ `const int32* GetRawMatrixAttributeValueFromCell(int32 CellIndex, const FDMXAttributeName& AttributeName) const;` — Returns the raw attribute value for the specified Attribute Name. Returns nullptr if the attribute cannot be found.
- L78 _public prototype_ `const TMap<FDMXAttributeName, int32>* GetAllRawMatrixAttributeValuesFromCell(int32 CellIndex) const;` — Returns the all raw attribute values for the specified Cell. Returns nullptr if the attribute cannot be found.
- L81 _public prototype_ `const TArray<TMap<FDMXAttributeName, int32>>* GetAllRawMatrixAttributeValues() const;` — Returns all raw matrix attribute values. Returns nullptr if the attribute cannot be accessed or if there is no data.
- L84 _public prototype_ `const float* GetNormalizedMatrixAttributeValueFromCell(int32 CellIndex, const FDMXAttributeName& AttributeName) const;` — Returns the normalized attribute value for the specified Attribute Name. Returns nullptr if the attribute cannot be found.
- L87 _public prototype_ `const FDMXNormalizedAttributeValueMap* GetAllNormalizedMatrixAttributeValuesFromCell(int32 CellIndex) const;` — Returns the all raw attribute values for the specified Cell. Returns nullptr if the attribute cannot be found.
- L90 _public prototype_ `const TArray<FDMXNormalizedAttributeValueMap>* GetAllNormalizedMatrixAttributeValues() const;` — Returns all raw matrix attribute values. Returns nullptr if the attribute cannot be accessed or if there is no data.
- L96 _public function_ `const TArray<FDMXFixtureFunction>& GetFunctions() const` — Returns the functions of the mode
- L99 _public function_ `const TArray<FDMXFixtureCellAttribute>& GetCellAttributes() const` — Returns the cell attributes of the fixture matrix
- L102 _public function_ `const int32 GetMatrixStartingChannelAbsolute() const` — Returns the absolute starting channel of the matrix attributes
- L105 _public function_ `int32 GetMatrixNumXCells() const` — Returns the number of collumns in the matrix. Does not test if the cache is using the matrix.
- L108 _public function_ `int32 GetMatrixNumYCells() const` — Returns the number of rows in the matrix. Does not test if the cache is using the matrix.
- L111 _public function_ `int32 GetCellSize() const` — Returns the data size of a single cell
- L114 _public function_ `int32 GetChannelSpan() const` — Returns the channel span
- L117 _public prototype_ `TArray<FDMXAttributeName> GetAttributeNames() const;` — Returns the attributes of the mode's function, without matrix attributes
- L120 _public prototype_ `TArray<FDMXAttributeName> GetCellAttributeNames() const;` — Returns the attribute names of the fixture matrix' cell attributes, without common function attributes
- L127 _private member_ `bool bValid;` — True if it holds valid properties
- L130 _private member_ `bool bFixtureMatrix;` — True if this is constructed for a matrix fixture
- L133 _private member_ `int32 DataIndex;` — Index where the data of the Patch starts in a Universe
- L136 _private member_ `int32 DataSize;` — Number of DMX channels the patch spans, including the matrix
- L139 _private member_ `int32 MatrixOffset;` — Offset of the fixture matrix from the starting channel. Can exceed the data size.
- L142 _private member_ `int32 NumCells;` — Number of cells in the matrix
- L145 _private member_ `int32 CellDataSize;` — Data Size of a single Cell
- L148 _private member_ `FDMXFixtureMode Mode;` — The mode to use
- L151 _private member_ `FDMXFixtureMatrix FixtureMatrix;` — The matrix to use
- L154 _private member_ `TArray<int32> OrderedCellIndicies;` — Cell indicies ordered by fixture, for fast conversion of a raw cell index
- L163 _private member_ `TArray<uint8> CachedDMXValues;` — Raw cached DMX values, last received. This only contains DMX data relevant to the patch, from starting channel to starting channel + channel span. Matrix values contained here are NOT pixelmapping distribution ordered.
- L166 _private member_ `TMap<FDMXAttributeName, int32> CachedRawValuesPerAttribute;` — Map of latest normalized values per (non-matrix) attribute
- L169 _private member_ `FDMXNormalizedAttributeValueMap CachedNormalizedValuesPerAttribute;` — Map of latest normalized values per (non-matrix) attribute
- L172 _private member_ `TArray<TMap<FDMXAttributeName, int32>> CachedRawValuesPerMatrixCell;` — Map of raw values per matrix attribute
- L175 _private member_ `TArray<FDMXNormalizedAttributeValueMap> CachedNormalizedValuesPerMatrixCell;` — Map of latest normalized values per matrix attributen

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntityFixtureType.h` (Public)


#### enum `EDMXPixelMappingDistribution`  
`enum class EDMXPixelMappingDistribution : uint8`  
_L20-41_
- reflection: `UENUM(BlueprintType, DisplayName = "DMX Pixel Mapping Distribution")`
- L22 _public enumerator_ `TopLeftToRight`
- L23 _public enumerator_ `TopLeftToBottom`
- L24 _public enumerator_ `TopLeftToClockwise`
- L25 _public enumerator_ `TopLeftToAntiClockwise`
- L27 _public enumerator_ `TopRightToLeft`
- L28 _public enumerator_ `BottomLeftToTop`
- L29 _public enumerator_ `TopRightToAntiClockwise`
- L30 _public enumerator_ `BottomLeftToClockwise`
- L32 _public enumerator_ `BottomLeftToRight`
- L33 _public enumerator_ `TopRightToBottom`
- L34 _public enumerator_ `BottomLeftAntiClockwise`
- L35 _public enumerator_ `TopRightToClockwise`
- L37 _public enumerator_ `BottomRightToLeft`
- L38 _public enumerator_ `BottomRightToTop`
- L39 _public enumerator_ `BottomRightToClockwise`
- L40 _public enumerator_ `BottomRightToAntiClockwise`

#### struct `FDMXFixtureFunction`  
`struct FDMXFixtureFunction`  
_L44-176_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Function"))`
- L49 _public function_ `FDMXFixtureFunction() : Attribute()` — Constructor
- L54 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Implementing Serialize to convert UClass to FFieldClass
- L57 _public function_ `uint8 GetNumChannels() const` — Returns the number of channels the function spans, according to its data type
- L60 _public prototype_ `int32 GetLastChannel() const;` — Returns the last channel of the Function
- L64 _public function_ `double GetPhysicalDefaultValue() const` — Gets the Physical Value of the Function
- L67 _public function_ `EDMXGDTFPhysicalUnit GetPhysicalUnit() const` — The Physical Unit this Physical Value is based on
- L70 _public function_ `double GetPhysicalFrom() const` — The starting value of the Physical Value range, based on the Physical Unit
- L73 _public function_ `double GetPhysicalTo() const` — The ending value of the Physical Value range, based on the Physical Unit
- L76 _public function_ `void SetPhysicalUnit(EDMXGDTFPhysicalUnit NewPhysicalUnit)` — Sets the Physical Default Value of the Function.
- L79 _public prototype_ `void SetPhysicalDefaultValue(double InPhysicalDefaultValue);` — Sets the Physical Default Value of the Function.
- L82 _public prototype_ `void SetPhysicalValueRange(double InPhysicalFrom, double InPhysicalTo);` — Sets the Physical Default Value range of the Function.
- L85 _public prototype_ `void UpdatePhysicalDefaultValue();` — Updated the Physica Default Value of the Function by the Default Value.
- L88 _public function_ `static FName GetPhysicalDefaultValuePropertyName()` — Property Name getters
- L89 _public function_ `static FName GetPhysicalUnitPropertyName()`
- L90 _public function_ `static FName GetPhysicalFromPropertyName()`
- L91 _public function_ `static FName GetPhysicalToPropertyName()`
- L102 _public member_ `FDMXAttributeName Attribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Attribute Mapping", DisplayPriority = "11"), Category = "Function Settings")` — The Attribute name to map this Function to. This is used to easily find the Function in Blueprints, using an Attribute list instead of typing the Function name directly. The list of Attributes can be edited on Project Settings->Plugins->DMX Protocol->Fixture Settings->Fixture Function Attributes
- L105 _public member_ `FString FunctionName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "10"), Category = "Function Settings")`
- L108 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "20"), Category = "Function Settings")`
- L112 _public member_ `int64 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "30"), Category = "Function Settings")` — The Default DMX Value of the function
- L116 _public member_ `int32 Channel = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Channel Assignment", DisplayPriority = "2"), Category = "Function Settings")` — This function's starting channel (use editor above to make changes)
- L120 _public member_ `EDMXFixtureSignalFormat DataType = EDMXFixtureSignalFormat::E8Bit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "5"), Category = "Function Settings")` — This function's data type. Defines the used number of channels (bytes)
- L135 _public member_ `bool bUseLSBMode = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use LSB Mode", DisplayPriority = "29"), Category = "Function Settings")` — Least Significant Byte mode makes the individual bytes (channels) of the function be interpreted with the first bytes being the lowest part of the number (endianness). E.g., given a 16 bit function with two channel values set to [0, 1], they would be interpreted as the binary number 0x01 0x00, which means 256. The first byte (0) became the lowest part in binary form and the following byte (1), the highest. Most Fixtures use MSB (Most Significant Byte) mode, which interprets bytes as highest first. In MSB mode, the example above would be interpreted in binary as 0x00 0x01, which means 1. The first byte (0) became the highest part in binary form and the following byte (1), the lowest.
- L141 _private member_ `double PhysicalDefaultValue = 0.0;` — `UPROPERTY(EditAnywhere, Transient, Category = "Physical Properties")` — The Physical Value used by default, based on the Physical Unit
- L145 _private member_ `EDMXGDTFPhysicalUnit PhysicalUnit = EDMXGDTFPhysicalUnit::None;` — `UPROPERTY(EditAnywhere, Category = "Physical Properties")` — The Physical Unit this Physical Value is based on
- L149 _private member_ `double PhysicalFrom = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Physical Properties")` — The starting value of the Physical Value range, based on the Physical Unit
- L153 _private member_ `double PhysicalTo = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Physical Properties")` — The ending value of the Physical Value range, based on the Physical Unit
- L159 _public prototype_ `FDMXFixtureFunction(const FDMXFixtureFunction&) = default;` — Workaround for clang deprecation warnings for any deprecated members in implicitly-defined special member functions
- L160 _public prototype_ `FDMXFixtureFunction(FDMXFixtureFunction&&) = default;`
- L161 _public prototype_ `FDMXFixtureFunction& operator=(const FDMXFixtureFunction&) = default;`
- L162 _public prototype_ `FDMXFixtureFunction& operator=(FDMXFixtureFunction&&) = default;`
- L173 _public member_ `int32 ChannelOffset_DEPRECATED = 0;` — `UE_DEPRECATED(5.0, "Instead please refer to the Channel property")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Deprecated, instead please refer to the Channel property."))` — DEPRECATED 5.0

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXFixtureFunction> : public TStructOpsTypeTraitsBase2<FDMXFixtureFunction>`  
_L179-185_
- inherits: `TStructOpsTypeTraitsBase2<FDMXFixtureFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L182-184_

#### struct `FDMXFixtureCellAttribute`  
`struct FDMXFixtureCellAttribute`  
_L189-241_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Cell Attribute"))`
- L194 _public function_ `FDMXFixtureCellAttribute() : Attribute() , Description() , DefaultValue(0) , DataType(EDMXFixtureSignalFormat::E8Bit) , bUseLSBMode(false)` — Constructor
- L203 _public function_ `uint8 GetNumChannels() const` — Returns the number of channels of the attribute
- L213 _public member_ `FDMXAttributeName Attribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Attribute Mapping", DisplayPriority = "11"), Category = "DMX")` — The Attribute name to map this Function to. This is used to easily find the Function in Blueprints, using an Attribute list instead of typing the Function name directly. The list of Attributes can be edited on Project Settings->Plugins->DMX Protocol->Fixture Settings->Fixture Function Attributes
- L216 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "20", DisplayName = "Description"), Category = "DMX")`
- L220 _public member_ `int64 DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "30", DisplayName = "Default Value"), Category = "DMX")` — Initial value for this function when no value is set
- L224 _public member_ `EDMXFixtureSignalFormat DataType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "5", DisplayName = "Data Type"), Category = "DMX")` — This function's data type. Defines the used number of channels (bytes)
- L240 _public member_ `bool bUseLSBMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Use LSB Mode", DisplayPriority = "29"), Category = "DMX")` — The Endianess of the Attribute: Least Significant Byte mode makes the individual bytes (channels) of the function be interpreted with the first bytes being the lowest part of the number. E.g., given a 16 bit function with two channel values set to [0, 1], they would be interpreted as the binary number 00000001 00000000, which means 256. The first byte (0) became the lowest part in binary form and the following byte (1), the highest. Most Fixtures use MSB (Most Significant Byte) mode, which interprets bytes as highest first. In MSB mode, the example above would be interpreted in binary as 00000000 00000001, which means 1. The first byte (0) became the highest part in binary form and the following byte (1), the lowest.

#### struct `FDMXFixtureMatrix`  
`struct FDMXFixtureMatrix`  
_L244-271_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Matrix"))`
- L249 _public prototype_ `FDMXFixtureMatrix();` — Constructor
- L252 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels of the Matrix
- L255 _public prototype_ `int32 GetLastChannel() const;` — Returns the last channel of the Matrix
- L258 _public member_ `TArray<FDMXFixtureCellAttribute> CellAttributes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "60", DisplayName = "Cell Attributes"), Category = "Mode Settings")`
- L261 _public member_ `int32 FirstCellChannel = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "20", DisplayName = "First Cell Channel", ClampMin = "1", ClampMax = "512"), Category = "Mode Settings")`
- L264 _public member_ `int32 XCells = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "30", DisplayName = "X Cells", ClampMin = "1", ClampMax = "512", UIMin = "1", UIMax = "512"), Category = "Mode Settings")`
- L267 _public member_ `int32 YCells = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "40", DisplayName = "Y Cells", ClampMin = "1", ClampMax = "512", UIMin = "1", UIMax = "512"), Category = "Mode Settings")`
- L270 _public member_ `EDMXPixelMappingDistribution PixelMappingDistribution = EDMXPixelMappingDistribution::TopLeftToRight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "50", DisplayName = "PixelMapping Distribution"), Category = "Mode Settings")`

#### struct `FDMXCell`  
`struct FDMXCell`  
_L274-290_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Cell"))`
- L280 _public member_ `int32 CellID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "20", DisplayName = "Cell ID", ClampMin = "0"), Category = "DMX")` — The cell index in a 1D Array (row order), starting from 0
- L284 _public member_ `FIntPoint Coordinate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "30", DisplayName = "Coordinate"), Category = "DMX")` — The cell coordinate in a 2D Array, starting from (0, 0)
- L286 _public function_ `FDMXCell() : CellID(0) , Coordinate(FIntPoint (-1,-1))`

#### struct `FDMXFixtureMode`  
`struct FDMXFixtureMode`  
_L293-326_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Mode"))`
- L298 _public member_ `FString ModeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "10"), Category = "Mode Settings")`
- L301 _public member_ `TArray<FDMXFixtureFunction> Functions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = "20"), Category = "Mode Settings")`
- L309 _public member_ `bool bAutoChannelSpan = true;` — `UPROPERTY(EditAnywhere, Category = "Mode Settings", meta = (DisplayPriority = "30"))` — When enabled, ChannelSpan is automatically set based on the created functions and their data types. If disabled, ChannelSpan can be manually set and functions and functions' channels beyond the specified span will be ignored.
- L313 _public member_ `int32 ChannelSpan = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode Settings", meta = (ClampMin = "4", ClampMax = "512", DisplayPriority = "40", EditCondition = "!bAutoChannelSpan"))` — Number of channels (bytes) used by this mode's functions
- L316 _public member_ `bool bFixtureMatrixEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode Settings", meta = (DisplayPriority = "60"))`
- L319 _public member_ `FDMXFixtureMatrix FixtureMatrixConfig;` — `UPROPERTY(EditAnywhere, Category = "Mode Settings", meta = (DisplayPriority = "70"))`
- L324 _public prototype_ `int32 AddOrInsertFunction(int32 IndexOfFunction, FDMXFixtureFunction InFunction);` — `UE_DEPRECATED(5.0, "Removed in favor of UDMXEntityFixtureType::AddFunction and UDMXEntityFixtureType::InsertFunction")` — DEPRECATED 5.0

#### struct `FDMXEntityFixtureTypeConstructionParams`  
`struct FDMXEntityFixtureTypeConstructionParams`  
_L331-346_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Entity Fixture Type Construction Params"))`
- desc: Parameters to construct a Fixture Type.
- L337 _public member_ `TObjectPtr<UDMXLibrary> ParentDMXLibrary = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixture Type", meta = (DisplayName = "Parent DMX Library"))` — The DMX Library in which the Fixture Type will be constructed
- L341 _public member_ `FDMXFixtureCategory DMXCategory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixture Type", meta = (DisplayName = "DMX Category"))` — The Category of the Fixture, useful for Filtering
- L345 _public member_ `TArray<FDMXFixtureMode> Modes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixture Type")` — The Modes of the Fixture Type

#### class `UDMXEntityFixtureType`  
`class UDMXEntityFixtureType : public UDMXEntity`  
_L360-631_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "DMX Fixture Type"))`
- inherits: `UDMXEntity`
- desc: Class to describe a type of Fixture. Fixture Patches can be created from Fixture Types (see UDMXEntityFixturePatch::ParentFixtureTypeTemplate).
- L366 _public prototype_ `UDMXEntityFixtureType();`
- L370 _public prototype_ `static UDMXEntityFixtureType* CreateFixtureTypeInLibrary(FDMXEntityFixtureTypeConstructionParams ConstructionParams, const FString& DesiredName = TEXT(""), bool bMarkDMXLibraryDirty = true);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Type")` — Creates a new Fixture Type in the DMX Library
- L374 _public prototype_ `static void RemoveFixtureTypeFromLibrary(FDMXEntityFixtureTypeRef FixtureTypeRef);` — `UFUNCTION(BlueprintCallable, Category = "DMX|Fixture Type")` — Removes a Fixture Type from a DMX Library
- L377 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L379 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L380 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L381 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L382 _public prototype_ `virtual void PostEditUndo() override;`
- L393 _public prototype_ `FString GetCleanGDTFFileNameSynchronous(bool bWithExtension) const;` — Acquires the GDTF file name of this Fixture Type. If bWithExtension is true, appends the .gdtf extension Note this is a slow operation that will load the GDTF Source if required and look up the filename from asset import data. For Fixture Types that do not stem from an imported GDTF, a filename is generated based on the Fixture Type name.
- L397 _public prototype_ `void SetModesFromDMXImport(UDMXImport* DMXImportAsset);` — `UE_DEPRECATED(5.5, "Setting GDTFs this way is not supported. Instead set the GDTFSource and generate the modes via UDMXGDTF.")` — `UFUNCTION(BlueprintCallable, Category = "Fixture Settings", meta = (DeprecatedFunction, DeprecationMessage = "Setting GDTFs from blueprints was never fully supported and now deprecated. Instead please refer to the Create Fixture Type In DMX Library function."))`
- L401 _public prototype_ `static FDMXOnFixtureTypeChangedDelegate& GetOnFixtureTypeChanged();` — Returns a delegate that is and should be broadcast whenever a Fixture Type changed
- L405 _public member_ `FDMXFixtureCategory DMXCategory;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type", meta = (DisplayName = "DMX Category"))` — The Category of the Fixture, useful for Filtering
- L408 _public member_ `TArray<FDMXFixtureMode> Modes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L415 _public member_ `TArray<TObjectPtr<UDMXModulator>> InputModulators;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Fixture Type", meta = (DisplayPriority = "50"))` — Modulators applied right before a patch of this type is received. NOTE: Modulators only affect the patch's normalized values! Untouched values are still available when accesing raw values.
- L419 _private member_ `static FDMXOnFixtureTypeChangedDelegate OnFixtureTypeChangedDelegate;` — Delegate that should be broadcast whenever a Fixture Type changed
- L434 _public prototype_ `int32 AddMode(FString BaseModeName = FString("Mode` — Adds a Mode to the Modes Array @param(optional)						The Base Mode Name when generating a name @return								The Index of the newly added Mode.
- L442 _public prototype_ `void DuplicateModes(TArray<int32> InModeIndicesToDuplicate, TArray<int32>& OutNewModeIndices);` — Duplicates the Modes at specified Indices @param InModeIndices					The indicies of the Modes to duplicate @param OutNewModeIndices				The indices of the newly created Modes.
- L445 _public prototype_ `void RemoveModes(const TArray<int32>& ModeIndicesToDelete);` — Deletes the Modes at specified Indices
- L453 _public prototype_ `void SetModeName(int32 InModeIndex, const FString& InDesiredModeName, FString& OutUniqueModeName);` — Sets a Mode Name for specified Mode @param InModeIndex					The index of the Mode in the Modes array @param InDesiredModeName				The desired Name that should be set @param OutUniqueModeName				The unique Name that was set
- L460 _public prototype_ `void SetFixtureMatrixEnabled(int32 ModeIndex, bool bEnableMatrix);` — Enables or disables the Matrix, reorders Function channels accordingly @param ModeIndex						The index of the Mode for which the Matrix should be enabled or disabled. @param bEnableMatrix					Whether to enable or disable the Matrix
- L467 _public prototype_ `void UpdateChannelSpan(int32 ModeIndex);` — Updates the channel span of the Mode. @param ModeIndex						The Index of the Mode for which the Channel Span should be updated.
- L470 _public prototype_ `void AlignFunctionChannels(int32 InModeIndex);` — Aligns alls channels of the functions in the Mode to be consecutive
- L480 _public prototype_ `int32 AddFunction(int32 InModeIndex);` — Adds a new Function to the Mode's Functions array @param InModeIndex					The index of the Mode, that will have the Function added to its Functions array. @return								The Index of the newly added Function.
- L490 _public prototype_ `int32 InsertFunction(int32 InModeIndex, int32 InInsertAtIndex, FDMXFixtureFunction& InOutNewFunction);` — Inserts a Function to the Mode's Function Array @param InModeIndex					The index of the Mode, that will have the Function added to its Functions array. @param InInsertAtIndex				If a valid Index, the Function will be inserted at this Index, and subsequent Function's Channels will be reodered after it. @param InOutNewFunction				The function that will be inserted. @return								The Index of the newly added Function.
- L499 _public prototype_ `void DuplicateFunctions(int32 InModeIndex, const TArray<int32>& InFunctionIndicesToDuplicate, TArray<int32>& OutNewFunctionIndices);` — Adds a Function to the Mode's Function Array @param InModeIndex					The index of the Mode in which the Functions to duplicate reside. @param InFunctionIndicesToDuplicate	The indices of the Functions to duplicate. @param OutNewFunctionIndices			The Function indices where the newly added Functions reside
- L507 _public prototype_ `void RemoveFunctions(int32 ModeIndex, TArray<int32> FunctionIndicesToDelete);` — Removes Functions from the Mode's Function Array @param InModeIndex					The index of the Mode in which the Functions to remove reside @param FunctionIndicesToDelete		The indices of the Functions to remove.
- L516 _public prototype_ `void ReorderFunction(int32 ModeIndex, int32 FunctionToReorderIndex, int32 InsertAtIndex);` — Reorders a function to reside at the Insert At Index, subsequently reorders other affected Functions @param ModeIndex						The Index of the Mode in which the Functions reside @param FunctionIndex					The Index of the Function that is reorderd @param InsertAtIndex					The Index of the Function where the function is inserted.
- L525 _public prototype_ `void SetFunctionName(int32 InModeIndex, int32 InFunctionIndex, const FString& InDesiredFunctionName, FString& OutUniqueFunctionName);` — Sets a Mode Name for specified Mode @param InModeIndex					The index of the Mode in the Modes array @param InFunctionIndex				The index of the Function in the Mode's Function array @param DesiredFunctionName			The desired Name that should be set @param OutUniqueFunctionName			The unique Name that was set
- L534 _public prototype_ `void SetFunctionStartingChannel(int32 InModeIndex, int32 InFunctionIndex, int32 InDesiredStartingChannel, int32& OutStartingChannel);` — Sets a Starting Channel for the Function, aligns it to other functions @param InModeIndex					The index of the Mode in the Modes array @param InFunctionIndex				The index of the Function in the Mode's Function array @param InDesiredStartingChannel		The desired Starting Channel that should be set @param OutStartingChannel			The resulting Starting Channel that was set
- L543 _public prototype_ `void ClampFunctionDefautValueByDataType(int32 ModeIndex, int32 FunctionIndex);` — `UE_DEPRECATED(5.5, "Removed as physical values were introduced to FDMXFixtureFunction (editor only) . Please handle the default value of the function per use case.")` — Clamps the Default Value of the Function by its Data Type @param ModeIndex						The Index of the Mode in which the Functions reside @param FunctionIndex					The Index of the Function for which the Default Value is clamped
- L548 _public prototype_ `void AddCellAttribute(int32 ModeIndex);` — Adds a new cell attribute to the Mode
- L551 _public prototype_ `void RemoveCellAttribute(int32 ModeIndex, int32 CellAttributeIndex);` — Removes a cell attribute from the Mode
- L560 _public prototype_ `void ReorderMatrix(int32 ModeIndex, int32 InsertAtFunctionIndex);` — Reorders the Fixture Matrix to reside after a function, subsequently reorders other affected Functions @param FixtureType					The Fixture Type in which the Functions reside @param ModeIndex						The Index of the Mode in which the Functions reside @param InsertAfterFunctionIndex		The Index of the Function after which the Matrix is inserted. If an invalid index is specified, the Matrix will added after the last Function Channel.
- L567 _public prototype_ `void UpdateYCellsFromXCells(int32 ModeIndex);` — Updates the channel span of the Mode. @param ModeIndex						The Index of the Mode for which the YCells should be updated
- L574 _public prototype_ `void UpdateXCellsFromYCells(int32 ModeIndex);` — Updates the channel span of the Mode. @param ModeIndex						The Index of the Mode for which the XCells should be updated
- L580 _public prototype_ `static void FunctionValueToBytes(const FDMXFixtureFunction& InFunction, uint32 InValue, uint8* OutBytes);`
- L581 _public prototype_ `static void IntToBytes(EDMXFixtureSignalFormat InSignalFormat, bool bUseLSB, uint32 InValue, uint8* OutBytes);`
- L583 _public prototype_ `static uint32 BytesToFunctionValue(const FDMXFixtureFunction& InFunction, const uint8* InBytes);`
- L584 _public prototype_ `static uint32 BytesToInt(EDMXFixtureSignalFormat InSignalFormat, bool bUseLSB, const uint8* InBytes);`
- L586 _public prototype_ `static void FunctionNormalizedValueToBytes(const FDMXFixtureFunction& InFunction, float InValue, uint8* OutBytes);`
- L587 _public prototype_ `static void NormalizedValueToBytes(EDMXFixtureSignalFormat InSignalFormat, bool bUseLSB, float InValue, uint8* OutBytes);`
- L589 _public prototype_ `static float BytesToFunctionNormalizedValue(const FDMXFixtureFunction& InFunction, const uint8* InBytes);`
- L590 _public prototype_ `static float BytesToNormalizedValue(EDMXFixtureSignalFormat InSignalFormat, bool bUseLSB, const uint8* InBytes);`
- L594 _public member_ `TSoftObjectPtr<UDMXImportGDTF> GDTFSource;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type", meta = (DisplayName = "GDTF Source"))` — The GDTF that initializes this Fixture Type. When changed, reinitializes with data from the GDTF.
- L599 _public member_ `bool bExportGeneratedGDTF = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Fixture Type", meta = (DisplayName = "Generate GDTF (not recommended)"))` — If checked, generates a new GDTF instead of exporting the imported GDTF. This adopts changes in editor but in most cases will result in data loss and is not recommended.
- L609 _public member_ `TSoftClassPtr<AActor> ActorClassToSpawn;` — `UPROPERTY(EditAnywhere, Category = "MVR", Meta = (MustImplement = "/Script/DMXFixtureActorInterface.DMXMVRFixtureActorInterface"))` — The Actor Class that is spawned when the DMX Library dropped onto a Level. Only Actors that implement the MVR Fixture Actor Interface can be used. Can be left blank. If so, any Actor Class with the most matching Attributes will be spawned.
- L614 _public member_ `bool bShowOnlyLatestGDTFModeRevisions = true;` — `UPROPERTY()` — If true only shows latest GDTF mode revisions in editor
- L625 _public member_ `TObjectPtr<UDMXImport> DMXImport;` — `UE_DEPRECATED(5.5, "Changed to a soft object pointer to reduce the memory footprint of Fixture Types. Please refer to GDTFSource instead.")` — `UPROPERTY(BlueprintReadOnly, Category = "Fixture Settings", meta = (DeprecatedProperty, DeprecationMessage = "Changed to a soft object pointer to reduce the memory footprint of Fixture Types. Please use GDTF Source instead."))` — DEPRECATED 5.5 - The GDTF from which this Fixture Type was setup.
- L629 _public member_ `bool bFixtureMatrixEnabled_DEPRECATED = false;` — `UE_DEPRECATED(5.5, "bFixtureMatrixEnabled is deprecated. Instead now each Mode has a FixtureMatrixEnabled property.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "FixtureMatrixEnabled is deprecated. Instead now each Mode has a FixtureMatrixEnabled property."))`

#### Free symbols / members of external scopes

- L183 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonf671fd3d0103`)
- L350 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDataTypeChangeDelegate, const UDMXEntityFixtureType*, const FDMXFixtureMode&);` — Notification when data type changed
- L350 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDataTypeChangeDelegate, const UDMXEntityFixtureType*, const FDMXFixtureMode&);` — Notification when data type changed
- L353 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnFixtureTypeChangedDelegate, const UDMXEntityFixtureType* );`
- L353 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnFixtureTypeChangedDelegate, const UDMXEntityFixtureType* );`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXEntityReference.h` (Public)


#### struct `FDMXEntityReference`  
`struct FDMXEntityReference`  
_L22-87_
- reflection: `USTRUCT(meta = (DisplayName = "DMX Entity Reference"))`
- desc: Represents an Entity from a DMX Library. Used to allow objects outside the DMX Library package to store references to UDMXEntity objects
- L32 _public member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The parent DMX library of the Entity Automatically set when calling SetEntity with a valid Entity.
- L36 _public member_ `bool bDisplayLibraryPicker;` — `UPROPERTY()` — Display the DMX Library asset picker. True by default, for Blueprint variables
- L40 _public prototype_ `FDMXEntityReference();` — Construct with invalid values by default
- L43 _public prototype_ `FDMXEntityReference(UDMXEntity* InEntity);` — Construct as a reference to an existing Entity and its type as EntityType
- L46 _public prototype_ `void SetEntity(UDMXEntity* NewEntity);` — Set the Entity and DMX Library this struct represents
- L49 _public prototype_ `UDMXEntity* GetEntity() const;` — Get the Entity referenced by this struct or nullptr if none was set.
- L52 _public prototype_ `TSubclassOf<UDMXEntity> GetEntityType() const;` — Get the type of entity this reference points to
- L56 _public prototype_ `bool operator==(const FDMXEntityReference& Other) const;` — Comparison operators
- L57 _public prototype_ `bool operator!=(const FDMXEntityReference& Other) const;`
- L78 _protected member_ `TSubclassOf<UDMXEntity> EntityType;` — `UPROPERTY()`
- L83 _private member_ `FGuid EntityId;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The entity's unique ID
- L86 _private member_ `mutable TWeakObjectPtr<UDMXEntity> CachedEntity;` — Cached value this entity stands for, to speed up access instead of looking it up from the library array

#### struct `FDMXEntityControllerRef`  
`struct FDMXEntityControllerRef : public FDMXEntityReference`  
_L95-106_
- reflection: `UE_DEPRECATED(5.5, "Controllers are no longer used and deprecated in favor of the DMX Port System.")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Controllers are no longer used and deprecated in favor of the DMX Port System."))`
- inherits: `FDMXEntityReference`
- desc: Represents a Controller from a DMX Library. Used to store a reference to a Controller outside the DMX Library
- L101 _public prototype_ `FDMXEntityControllerRef();`
- L102 _public prototype_ `FDMXEntityControllerRef(UDMXEntityController* InController);`
- L105 _public prototype_ `UDMXEntityController* GetController() const;` — Specialized GetEntity() to return it already cast

#### struct `FDMXEntityFixtureTypeRef`  
`struct FDMXEntityFixtureTypeRef : public FDMXEntityReference`  
_L113-124_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Type Ref"))`
- inherits: `FDMXEntityReference`
- desc: Represents a Fixture Type from a DMX Library. Used to store a reference to a Fixture Type outside the DMX Library
- L119 _public prototype_ `FDMXEntityFixtureTypeRef();`
- L120 _public prototype_ `FDMXEntityFixtureTypeRef(UDMXEntityFixtureType* InFixtureType);`
- L123 _public prototype_ `UDMXEntityFixtureType* GetFixtureType() const;` — Specialized GetEntity() to return it already cast

#### struct `FDMXEntityFixturePatchRef`  
`struct FDMXEntityFixturePatchRef : public FDMXEntityReference`  
_L131-142_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "DMX Fixture Patch Ref"))`
- inherits: `FDMXEntityReference`
- desc: Represents a Fixture Patch from a DMX Library. Used to store a reference to a Fixture Patch outside the DMX Library
- L137 _public prototype_ `FDMXEntityFixturePatchRef();`
- L138 _public prototype_ `FDMXEntityFixturePatchRef(UDMXEntityFixturePatch* InFixturePatch);`
- L141 _public prototype_ `UDMXEntityFixturePatch* GetFixturePatch() const;` — Specialized GetEntity() to return it already cast

#### class `UDMXEntityReferenceConversions`  
`class UDMXEntityReferenceConversions : public UBlueprintFunctionLibrary`  
_L146-173_
- reflection: `UCLASS(meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Extend type conversions to handle Entity Reference structs
- L154 _public prototype_ `static UDMXEntityController* Conv_ControllerRefToObj(const FDMXEntityControllerRef& InControllerRef);` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "Controllers are no longer used and deprecated in favor of the DMX Port System.", DisplayName = "ToController (ControllerReference)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L158 _public prototype_ `static UDMXEntityFixtureType* Conv_FixtureTypeRefToObj(const FDMXEntityFixtureTypeRef& InFixtureTypeRef);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFixtureType (FixtureTypeReference)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L161 _public prototype_ `static UDMXEntityFixturePatch* Conv_FixturePatchRefToObj(const FDMXEntityFixturePatchRef& InFixturePatchRef);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFixturePatch (FixturePatchReference)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L165 _public prototype_ `static FDMXEntityControllerRef Conv_ControllerObjToRef(UDMXEntityController* InController);` — `UFUNCTION(BlueprintPure, meta = (DeprecatedFunction, DeprecationMessage = "Controllers are no longer used and deprecated in favor of the DMX Port System.", DisplayName = "ToControllerRef (Controller)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L169 _public prototype_ `static FDMXEntityFixtureTypeRef Conv_FixtureTypeObjToRef(UDMXEntityFixtureType* InFixtureType);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFixtureTypeRef (FixtureType)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L172 _public prototype_ `static FDMXEntityFixturePatchRef Conv_FixturePatchObjToRef(UDMXEntityFixturePatch* InFixturePatch);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFixturePatchRef (FixturePatch)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`

#### Free symbols / members of external scopes

- L60 _function_ `FORCEINLINE_DEBUGGABLE friend uint32 GetTypeHash(const FDMXEntityReference& EntityRef)` — Gets a hash from the DMX Library and EntityID values

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXGDTFAssetImportData.h` (Public)


#### class `UDMXGDTFAssetImportData`  
`class UDMXGDTFAssetImportData : public UAssetImportData`  
_L16-46_
- reflection: `UCLASS()`
- inherits: `UAssetImportData`
- L23 _public function_ `const FString& GetFilePathAndName() const` — Returns the imported file path and name
- L27 _public prototype_ `void SetSourceFile(const FString& InFilePathAndName);` — Creates new asset GDTF Asset Import Data from the File. Returns the GDTF Asset Import Data or nullptr if not a valid GDTF File
- L31 _public function_ `const TArray64<uint8>& GetRawSourceData() const` — Returns the source data the asset was generated from
- L35 _protected prototype_ `virtual void PostLoad() override;`
- L41 _private member_ `FString FilePathAndName;` — `UPROPERTY()` — The imported file path and name
- L45 _private member_ `FDMXByteArray64 RawSourceData;` — `UPROPERTY()` — The raw GDTF zip file as byte array

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXImport.h` (Public)


#### struct `FDMXColorCIE`  
`struct UE_DEPRECATED(5.5, "FDMXColorCIE is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") FDMXColorCIE`  
_L26-44_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public function_ `FDMXColorCIE() : X(0.f) , Y(0.f) , YY(0)`
- L37 _public member_ `float X;` — `UPROPERTY(EditAnywhere, Category = Color, meta = (ClampMin = "0", ClampMax = "1.0"))`
- L40 _public member_ `float Y;` — `UPROPERTY(EditAnywhere, Category = Color, meta = (ClampMin = "0", ClampMax = "1.0"))`
- L43 _public member_ `uint8 YY;` — `UPROPERTY(EditAnywhere, Category = Color, meta = (ClampMin = "0", ClampMax = "255"))`

#### class `UDMXImportFixtureType`  
`class UE_DEPRECATED(5.5, "UDMXImportFixtureType is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportFixtureType : public UObject`  
_L47-51_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportAttributeDefinitions`  
`class UE_DEPRECATED(5.5, "UDMXImportAttributeDefinitions is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportAttributeDefinitions : public UObject`  
_L54-58_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportWheels`  
`class UE_DEPRECATED(5.5, "UDMXImportWheels is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportWheels : public UObject`  
_L61-65_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportPhysicalDescriptions`  
`class UE_DEPRECATED(5.5, "UDMXImportPhysicalDescriptions is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportPhysicalDescriptions : public UObject`  
_L68-72_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportModels`  
`class UE_DEPRECATED(5.5, "UDMXImportModels is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportModels : public UObject`  
_L75-79_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportGeometries`  
`class UE_DEPRECATED(5.5, "UDMXImportGeometries is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportGeometries : public UObject`  
_L82-86_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportDMXModes`  
`class UDMXImportDMXModes : public UObject`  
_L91-96_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportDMXModes is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImportProtocols`  
`class UE_DEPRECATED(5.5, "UDMXImportProtocols is deprecated. Please refer to the new GDTF Description in UDMXDeviceType instead") UDMXImportProtocols : public UObject`  
_L100-105_
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UObject`

#### class `UDMXImport`  
`class UDMXImport : public UObject`  
_L108-152_
- reflection: `UCLASS(BlueprintType, Blueprintable, abstract)`
- inherits: `UObject`
- L116 _public function_ `TType* CreateNewObject()` — `UE_DEPRECATED(5.5, "Instead please use NewObject.")`
- L126 _public member_ `TObjectPtr<UDMXImportFixtureType> FixtureType_DEPRECATED;` — `UPROPERTY()`
- L129 _public member_ `TObjectPtr<UDMXImportAttributeDefinitions> AttributeDefinitions_DEPRECATED;` — `UPROPERTY()`
- L132 _public member_ `TObjectPtr<UDMXImportWheels> Wheels_DEPRECATED;` — `UPROPERTY()`
- L135 _public member_ `TObjectPtr<UDMXImportPhysicalDescriptions> PhysicalDescriptions_DEPRECATED;` — `UPROPERTY()`
- L138 _public member_ `TObjectPtr<UDMXImportModels> Models_DEPRECATED;` — `UPROPERTY()`
- L141 _public member_ `TObjectPtr<UDMXImportGeometries> Geometries_DEPRECATED;` — `UPROPERTY()`
- L145 _public member_ `TObjectPtr<UDMXImportDMXModes> DMXModes_DEPRECATED;` — `UPROPERTY()`
- L149 _public member_ `TObjectPtr<UDMXImportProtocols> Protocols_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace DMXImport` (scope `UE::DMX`)
- L9 _namespace_ `namespace Private` (scope `UE::DMX::DMXImport`)
- L13 _function_ `static EnumType GetEnumValueFromString(const FString& String)` (scope `UE::DMX::DMXImport::Private`) — `UE_DEPRECATED(5.5, "Please refer to the new GDTF Description in UDMXDeviceType instead.")`
- L19 _prototype_ `FDMXColorCIE ParseColorCIE(const FString& InColor);` (scope `UE::DMX::DMXImport::Private`) — `UE_DEPRECATED(5.5, "Please refer to the new GDTF Description in UDMXDeviceType instead.")`
- L22 _prototype_ `FMatrix ParseMatrix(FString&& InMatrixStr);` (scope `UE::DMX::DMXImport::Private`) — `UE_DEPRECATED(5.5, "Please refer to the new GDTF Description in UDMXDeviceType instead.")`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXImportGDTF.h` (Public)


#### class `UDMXImportGDTF`  
`class UDMXImportGDTF : public UDMXImport`  
_L21-74_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDMXImport`
- desc: A GDTF imported into Unreal Engine. Note this object holds GDTF source data and may be memory heavy. To access the GDTF description in lightweight fashion, please refer to UDMXGDTF (C++ only).
- L28 _public prototype_ `UDMXImportGDTF();` — Constructor
- L31 _public prototype_ `virtual void PostLoad() override;`
- L35 _public prototype_ `UDMXGDTF* LoadGDTF() const;` — Loads the GDTF stored in this object
- L41 _public function_ `class UDMXImportGDTFDMXModes* GetDMXModes() const` — `UE_DEPRECATED(5.5, "UDMXImportGDTF::GetDMXModes is deprecated in favor of UDMXGDTF. See also newly added UDMXImportGDTF::LoadGDTF to read out GDTF data of this asset.")` — `UFUNCTION(BlueprintPure, Category = "DMXGDTF|Import Data", Meta = (DeprecatedFunction, DeprecationMessage = "This member is deprecated in favor of a DMX Entity Fixture Type based workflow. Please refer to members of DMX Entity Fixture Type instead"))` — DEPRECATED 5.4
- L47 _public member_ `FString SourceFilename_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "Deprecated in favor of GDTFAssetImportData, see UDMXImportGDTF::GetGDTFAssetImportData."))` — DEPRECATED 5.1 in favor of GDTFAssetImportData
- L51 _public function_ `UDMXGDTFAssetImportData* GetGDTFAssetImportData() const` — Returns GDTF Asset Import Data for this GDTF
- L55 _public function_ `const TSoftClassPtr<AActor>& GetActorClass() const` — Returns the Actor Class to spawn when spawned from a DMX Library
- L68 _private member_ `TSoftClassPtr<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category = "MVR", Meta = (MustImplement = "/Script/DMXFixtureActorInterface.DMXMVRFixtureActorInterface", AllowPrivateAccess = true))` — The Actor Class that corresponds to this GDTF. Only Actors that implement the MVR Fixture Actor Interface can be used. In the current Version this set as the Fixture Type Actor Class, when this GDTF is set for the Fixture Type. Can be left blank. If so, any Actor Class with the most matching Attributes will be spawned.
- L73 _private member_ `TObjectPtr<UDMXGDTFAssetImportData> GDTFAssetImportData;` — `UPROPERTY()` — The Asset Import Data used to generate the GDTF asset or nullptr, if not generated from a GDTF file

#### enum `EDMXImportGDTFType`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFType is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFType : uint8`  
_L82-86_
- reflection: `UENUM()`
- L84 _public enumerator_ `Multiply`
- L85 _public enumerator_ `Override`

#### enum `EDMXImportGDTFSnap`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFSnap is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFSnap : uint8`  
_L89-95_
- reflection: `UENUM()`
- L91 _public enumerator_ `Yes`
- L92 _public enumerator_ `No`
- L93 _public enumerator_ `On`
- L94 _public enumerator_ `Off`

#### enum `EDMXImportGDTFMaster`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFMaster is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFMaster : uint8`  
_L98-103_
- reflection: `UENUM()`
- L100 _public enumerator_ `None`
- L101 _public enumerator_ `Grand`
- L102 _public enumerator_ `Group`

#### enum `EDMXImportGDTFDMXInvert`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFDMXInvert is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFDMXInvert : uint8`  
_L106-110_
- reflection: `UENUM()`
- L108 _public enumerator_ `Yes`
- L109 _public enumerator_ `No`

#### enum `EDMXImportGDTFLampType`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFLampType is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFLampType : uint8`  
_L113-119_
- reflection: `UENUM()`
- L115 _public enumerator_ `Discharge`
- L116 _public enumerator_ `Tungsten`
- L117 _public enumerator_ `Halogen`
- L118 _public enumerator_ `LED`

#### enum `EDMXImportGDTFBeamType`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFBeamType is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFBeamType : uint8`  
_L122-127_
- reflection: `UENUM()`
- L124 _public enumerator_ `Wash`
- L125 _public enumerator_ `Spot`
- L126 _public enumerator_ `None`

#### enum `EDMXImportGDTFPrimitiveType`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFPrimitiveType is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFPrimitiveType : uint8`  
_L130-142_
- reflection: `UENUM()`
- L132 _public enumerator_ `Undefined`
- L133 _public enumerator_ `Cube`
- L134 _public enumerator_ `Cylinder`
- L135 _public enumerator_ `Sphere`
- L136 _public enumerator_ `Base`
- L137 _public enumerator_ `Yoke`
- L138 _public enumerator_ `Head`
- L139 _public enumerator_ `Scanner`
- L140 _public enumerator_ `Conventional`
- L141 _public enumerator_ `Pigtail`

#### enum `EDMXImportGDTFPhysicalUnit`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFPhysicalUnit is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFPhysicalUnit : uint8`  
_L145-169_
- reflection: `UENUM()`
- L147 _public enumerator_ `None`
- L148 _public enumerator_ `Percent`
- L149 _public enumerator_ `Length`
- L150 _public enumerator_ `Mass`
- L151 _public enumerator_ `Time`
- L152 _public enumerator_ `Temperature`
- L153 _public enumerator_ `LuminousIntensity`
- L154 _public enumerator_ `Angle`
- L155 _public enumerator_ `Force`
- L156 _public enumerator_ `Frequency`
- L157 _public enumerator_ `Current`
- L158 _public enumerator_ `Voltage`
- L159 _public enumerator_ `Power`
- L160 _public enumerator_ `Energy`
- L161 _public enumerator_ `Area`
- L162 _public enumerator_ `Volume`
- L163 _public enumerator_ `Speed`
- L164 _public enumerator_ `Acceleration`
- L165 _public enumerator_ `AngularSpeed`
- L166 _public enumerator_ `AngularAccc`
- L167 _public enumerator_ `WaveLength`
- L168 _public enumerator_ `ColorComponent`

#### enum `EDMXImportGDTFMode`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFMode is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFMode : uint8`  
_L172-178_
- reflection: `UENUM()`
- L174 _public enumerator_ `Custom`
- L175 _public enumerator_ `sRGB`
- L176 _public enumerator_ `ProPhoto`
- L177 _public enumerator_ `ANSI`

#### enum `EDMXImportGDTFInterpolationTo`  
`enum class UE_DEPRECATED(5.5, "FDMXImportGDTFInterpolationTo is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") EDMXImportGDTFInterpolationTo : uint8`  
_L181-186_
- reflection: `UENUM()`
- L183 _public enumerator_ `Linear`
- L184 _public enumerator_ `Step`
- L185 _public enumerator_ `Log`

#### struct `FDMXImportGDTFActivationGroup`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFActivationGroup is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFActivationGroup`  
_L189-195_
- reflection: `USTRUCT(BlueprintType)`
- L194 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFeature`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFeature is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFeature`  
_L198-204_
- reflection: `USTRUCT(BlueprintType)`
- L203 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFeatureGroup`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFeatureGroup is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFeatureGroup`  
_L207-221_
- reflection: `USTRUCT(BlueprintType)`
- L212 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L215 _public member_ `FString Pretty;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L219 _public member_ `TArray<FDMXImportGDTFFeature> Features;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFAttribute`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFAttribute is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFAttribute`  
_L224-250_
- reflection: `USTRUCT(BlueprintType)`
- L229 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L232 _public member_ `FString Pretty;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L236 _public member_ `FDMXImportGDTFActivationGroup ActivationGroup;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L239 _public member_ `FDMXImportGDTFFeature Feature;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L242 _public member_ `FString MainAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L245 _public member_ `EDMXImportGDTFPhysicalUnit PhysicalUnit = EDMXImportGDTFPhysicalUnit::None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L248 _public member_ `FDMXColorCIE Color;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFilter`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFilter is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFilter`  
_L253-264_
- reflection: `USTRUCT(BlueprintType)`
- L258 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L262 _public member_ `FDMXColorCIE Color;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFWheelSlot`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFWheelSlot is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFWheelSlot`  
_L268-285_
- reflection: `USTRUCT(BlueprintType)`
- L273 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L277 _public member_ `FDMXColorCIE Color;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L280 _public member_ `FDMXImportGDTFFilter Filter;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L284 _public member_ `TObjectPtr<UTexture2D> MediaFileName = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Fixture Type")`

#### struct `FDMXImportGDTFWheel`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFWheel is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFWheel`  
_L288-299_
- reflection: `USTRUCT(BlueprintType)`
- L293 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L297 _public member_ `TArray<FDMXImportGDTFWheelSlot> Slots;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFMeasurementPoint`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFMeasurementPoint is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFMeasurementPoint`  
_L302-311_
- reflection: `USTRUCT(BlueprintType)`
- L307 _public member_ `float WaveLength = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L310 _public member_ `float Energy = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFMeasurement`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFMeasurement is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFMeasurement`  
_L315-335_
- reflection: `USTRUCT(BlueprintType)`
- L320 _public member_ `float Physical = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L323 _public member_ `float LuminousIntensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L326 _public member_ `float Transmission = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L330 _public member_ `EDMXImportGDTFInterpolationTo InterpolationTo = EDMXImportGDTFInterpolationTo::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L333 _public member_ `TArray<FDMXImportGDTFMeasurementPoint> MeasurementPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFEmitter`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFEmitter is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFEmitter`  
_L338-360_
- reflection: `USTRUCT(BlueprintType)`
- L343 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L347 _public member_ `FDMXColorCIE Color;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L351 _public member_ `float DominantWaveLength = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L354 _public member_ `FString DiodePart;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L358 _public member_ `FDMXImportGDTFMeasurement Measurement;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFColorSpace`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFColorSpace is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFColorSpace`  
_L363-388_
- reflection: `USTRUCT(BlueprintType)`
- L369 _public member_ `EDMXImportGDTFMode Mode = EDMXImportGDTFMode::sRGB;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L373 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L377 _public member_ `FDMXColorCIE Red;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L380 _public member_ `FDMXColorCIE Green;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L383 _public member_ `FDMXColorCIE Blue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L386 _public member_ `FDMXColorCIE WhitePoint;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFDMXProfiles`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFDMXProfiles is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFDMXProfiles`  
_L391-394_
- reflection: `USTRUCT(BlueprintType)`

#### struct `FDMXImportGDTFCRIs`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFCRIs is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFCRIs`  
_L397-400_
- reflection: `USTRUCT(BlueprintType)`

#### struct `FDMXImportGDTFModel`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFModel is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFModel`  
_L404-424_
- reflection: `USTRUCT(BlueprintType)`
- L409 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L412 _public member_ `float Length = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L415 _public member_ `float Width = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L418 _public member_ `float Height = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L422 _public member_ `EDMXImportGDTFPrimitiveType PrimitiveType = EDMXImportGDTFPrimitiveType::Undefined;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFGeometryBase`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFGeometryBase is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFGeometryBase`  
_L427-442_
- reflection: `USTRUCT(BlueprintType)`
- L431 _public function_ `FDMXImportGDTFGeometryBase()`
- L435 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L438 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L441 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFBeam`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFBeam is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFBeam`  
_L445-488_
- reflection: `USTRUCT(BlueprintType)`
- L450 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L453 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L456 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L460 _public member_ `EDMXImportGDTFLampType LampType = EDMXImportGDTFLampType::Discharge;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L464 _public member_ `float PowerConsumption = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L467 _public member_ `float LuminousFlux = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L470 _public member_ `float ColorTemperature = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L473 _public member_ `float BeamAngle = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L476 _public member_ `float FieldAngle = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L479 _public member_ `float BeamRadius = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L483 _public member_ `EDMXImportGDTFBeamType BeamType = EDMXImportGDTFBeamType::Wash;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L486 _public member_ `uint8 ColorRenderingIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFTypeAxis`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFTypeAxis is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFTypeAxis`  
_L491-508_
- reflection: `USTRUCT(BlueprintType)`
- L496 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L499 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L502 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L506 _public member_ `TArray<FDMXImportGDTFBeam> Beams;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFGeneralAxis`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFGeneralAxis is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFGeneralAxis`  
_L511-528_
- reflection: `USTRUCT(BlueprintType)`
- L516 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L519 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L522 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L526 _public member_ `TArray<FDMXImportGDTFTypeAxis> Axis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFTypeGeometry`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFTypeGeometry is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFTypeGeometry`  
_L531-543_
- reflection: `USTRUCT(BlueprintType)`
- L536 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L539 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L542 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFilterBeam`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFilterBeam is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFilterBeam`  
_L546-558_
- reflection: `USTRUCT(BlueprintType)`
- L551 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L554 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L557 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFilterColor`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFilterColor is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFilterColor`  
_L561-573_
- reflection: `USTRUCT(BlueprintType)`
- L566 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L569 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L572 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFilterGobo`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFilterGobo is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFilterGobo`  
_L576-588_
- reflection: `USTRUCT(BlueprintType)`
- L581 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L584 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L587 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFilterShaper`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFilterShaper is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFilterShaper`  
_L591-603_
- reflection: `USTRUCT(BlueprintType)`
- L596 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L599 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L602 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFBreak`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFBreak is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFBreak`  
_L606-615_
- reflection: `USTRUCT(BlueprintType)`
- L611 _public member_ `int32 DMXOffset = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L614 _public member_ `uint8 DMXBreak = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFGeometryReference`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFGeometryReference is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFGeometryReference`  
_L618-635_
- reflection: `USTRUCT(BlueprintType)`
- L623 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L626 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L629 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L633 _public member_ `TArray<FDMXImportGDTFBreak> Breaks;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFGeneralGeometry`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFGeneralGeometry is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFGeneralGeometry`  
_L638-673_
- reflection: `USTRUCT(BlueprintType)`
- L643 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L646 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L649 _public member_ `FMatrix Position = FMatrix::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L653 _public member_ `FDMXImportGDTFGeneralAxis Axis;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L656 _public member_ `FDMXImportGDTFTypeGeometry Geometry;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L659 _public member_ `FDMXImportGDTFFilterBeam FilterBeam;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L662 _public member_ `FDMXImportGDTFFilterColor FilterColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L665 _public member_ `FDMXImportGDTFFilterGobo FilterGobo;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L668 _public member_ `FDMXImportGDTFFilterShaper FilterShaper;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L671 _public member_ `FDMXImportGDTFGeometryReference GeometryReference;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFDMXValue`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFDMXValue is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFDMXValue`  
_L676-693_
- reflection: `USTRUCT(BlueprintType)`
- L680 _public function_ `FDMXImportGDTFDMXValue() : Value(0) , ValueSize(1)`
- L686 _public prototype_ `FDMXImportGDTFDMXValue(const FString& InDMXValueStr);`
- L689 _public member_ `int32 Value;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L692 _public member_ `uint8 ValueSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFChannelSet`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFChannelSet is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFChannelSet`  
_L696-716_
- reflection: `USTRUCT(BlueprintType)`
- L701 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L705 _public member_ `FDMXImportGDTFDMXValue DMXFrom;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L709 _public member_ `float PhysicalFrom = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L712 _public member_ `float PhysicalTo = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L715 _public member_ `int32 WheelSlotIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFChannelFunction`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFChannelFunction is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFChannelFunction`  
_L719-778_
- reflection: `USTRUCT(BlueprintType)`
- L724 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L728 _public member_ `FDMXImportGDTFAttribute Attribute;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L732 _public member_ `FString OriginalAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L736 _public member_ `FDMXImportGDTFDMXValue DMXFrom;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L739 _public member_ `FDMXImportGDTFDMXValue DMXValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L743 _public member_ `float PhysicalFrom = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L746 _public member_ `float PhysicalTo = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L749 _public member_ `float RealFade = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L753 _public member_ `FDMXImportGDTFWheel Wheel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L756 _public member_ `FDMXImportGDTFEmitter Emitter;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L759 _public member_ `FDMXImportGDTFFilter Filter;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L762 _public member_ `EDMXImportGDTFDMXInvert DMXInvert = EDMXImportGDTFDMXInvert::No;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L766 _public member_ `FString ModeMaster;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L770 _public member_ `FDMXImportGDTFDMXValue ModeFrom;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L773 _public member_ `FDMXImportGDTFDMXValue ModeTo;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L776 _public member_ `TArray<FDMXImportGDTFChannelSet> ChannelSets;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFLogicalChannel`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFLogicalChannel is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFLogicalChannel`  
_L781-806_
- reflection: `USTRUCT(BlueprintType)`
- L787 _public member_ `FDMXImportGDTFAttribute Attribute;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L790 _public member_ `EDMXImportGDTFSnap Snap = EDMXImportGDTFSnap::No;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L793 _public member_ `EDMXImportGDTFMaster Master = EDMXImportGDTFMaster::None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L797 _public member_ `float MibFade = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L800 _public member_ `float DMXChangeTimeLimit = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L804 _public member_ `FDMXImportGDTFChannelFunction ChannelFunction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFDMXChannel`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFDMXChannel is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFDMXChannel`  
_L809-837_
- reflection: `USTRUCT(BlueprintType)`
- L814 _public prototype_ `bool ParseOffset(const FString& InOffsetStr);` — Parses the offset of the channel. Returns false if no valid offset is specified
- L817 _public member_ `int32 DMXBreak = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L820 _public member_ `TArray<int32> Offset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L824 _public member_ `FDMXImportGDTFDMXValue Default;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L827 _public member_ `FDMXImportGDTFDMXValue Highlight;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L831 _public member_ `FName Geometry;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L835 _public member_ `FDMXImportGDTFLogicalChannel LogicalChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFRelation`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFRelation is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFRelation`  
_L840-857_
- reflection: `USTRUCT(BlueprintType)`
- L845 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L848 _public member_ `FString Master;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L851 _public member_ `FString Follower;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L855 _public member_ `EDMXImportGDTFType Type = EDMXImportGDTFType::Multiply;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFFTMacro`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFFTMacro is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFFTMacro`  
_L860-866_
- reflection: `USTRUCT(BlueprintType)`
- L865 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`

#### struct `FDMXImportGDTFDMXMode`  
`struct UE_DEPRECATED(5.5, "FDMXImportGDTFDMXMode is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.") FDMXImportGDTFDMXMode`  
_L869-889_
- reflection: `USTRUCT(BlueprintType)`
- L874 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L877 _public member_ `FName Geometry;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L881 _public member_ `TArray<FDMXImportGDTFDMXChannel> DMXChannels;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L884 _public member_ `TArray<FDMXImportGDTFRelation> Relations;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`
- L887 _public member_ `TArray<FDMXImportGDTFFTMacro> FTMacros;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFFixtureType`  
`class UDMXImportGDTFFixtureType : public UDMXImportFixtureType`  
_L894-925_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFFixtureType is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportFixtureType`
- L903 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L906 _public member_ `FString ShortName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L909 _public member_ `FString LongName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L912 _public member_ `FString Manufacturer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L915 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L918 _public member_ `FString FixtureTypeID;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`
- L921 _public member_ `TObjectPtr<UTexture2D> Thumbnail = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Fixture Type")`
- L924 _public member_ `FString RefFT;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fixture Type")`

#### class `UDMXImportGDTFAttributeDefinitions`  
`class UDMXImportGDTFAttributeDefinitions : public UDMXImportAttributeDefinitions`  
_L930-951_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFAttributeDefinitions is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportAttributeDefinitions`
- L936 _public prototype_ `bool FindFeature(const FString& InQuery, FDMXImportGDTFFeature& OutFeature) const;`
- L938 _public prototype_ `bool FindAtributeByName(const FName& InName, FDMXImportGDTFAttribute& OutAttribute) const;`
- L942 _public member_ `TArray<FDMXImportGDTFActivationGroup> ActivationGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L945 _public member_ `TArray<FDMXImportGDTFFeatureGroup> FeatureGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L948 _public member_ `TArray<FDMXImportGDTFAttribute> Attributes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFWheels`  
`class UDMXImportGDTFWheels : public UDMXImportWheels`  
_L956-969_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFWheels is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportWheels`
- L962 _public prototype_ `bool FindWeelByName(const FName& InName, FDMXImportGDTFWheel& OutWheel) const;`
- L966 _public member_ `TArray<FDMXImportGDTFWheel> Wheels;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFPhysicalDescriptions`  
`class UDMXImportGDTFPhysicalDescriptions : public UDMXImportPhysicalDescriptions`  
_L974-996_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFPhysicalDescriptions is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportPhysicalDescriptions`
- L980 _public prototype_ `bool FindEmitterByName(const FName& InName, FDMXImportGDTFEmitter& OutEmitter) const;`
- L984 _public member_ `TArray<FDMXImportGDTFEmitter> Emitters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L987 _public member_ `FDMXImportGDTFColorSpace ColorSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L990 _public member_ `FDMXImportGDTFDMXProfiles DMXProfiles;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L993 _public member_ `FDMXImportGDTFCRIs CRIs;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFModels`  
`class UDMXImportGDTFModels : public UDMXImportModels`  
_L1001-1011_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFModels is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportModels`
- L1008 _public member_ `TArray<FDMXImportGDTFModel> Models;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFGeometries`  
`class UDMXImportGDTFGeometries : public UDMXImportGeometries`  
_L1016-1026_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFGeometries is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportGeometries`
- L1023 _public member_ `TArray<FDMXImportGDTFGeneralGeometry> GeneralGeometry;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### class `UDMXImportGDTFDMXModes`  
`class UDMXImportGDTFDMXModes : public UDMXImportDMXModes`  
_L1031-1044_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFDMXModes is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportDMXModes`
- L1038 _public member_ `TArray<FDMXImportGDTFDMXMode> DMXModes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`
- L1041 _public prototype_ `TArray<FDMXImportGDTFChannelFunction> GetDMXChannelFunctions(const FDMXImportGDTFDMXMode& InMode);` — `UFUNCTION(BlueprintPure, Category = "DMXGDTF|Import Data")`

#### class `UDMXImportGDTFProtocols`  
`class UDMXImportGDTFProtocols : public UDMXImportProtocols`  
_L1049-1059_
- reflection: `UE_DEPRECATED(5.5, "UDMXImportGDTFProtocols is deprecated in favor of its corresponding type in the DMXGDTF module. See also UDMXImportGDTF::LoadGDTF.")`
- reflection: `UCLASS(BlueprintType, Blueprintable, Meta = (DeprecatedNode, DeprecationMessage = "This class is now deprecated in favor of a DMXEntityFixtureType based workflow. Please refer to members of DMXEntityFixtureType instead."))`
- inherits: `UDMXImportProtocols`
- L1058 _public member_ `TArray<FName> Protocols;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX")`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXLibrary.h` (Public)


#### struct `FDMXLibraryPortReferences`  
`struct FDMXLibraryPortReferences`  
_L24-36_
- reflection: `USTRUCT(BlueprintType)`
- desc: Custom struct of in put and output port references for custom details customization with an enabled state
- L31 _public member_ `TArray<FDMXInputPortReference> InputPortReferences;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NonTransactional, Category = "DMX", Meta = (DisplayName = "Input Ports"))` — Map of input port references of a Library
- L35 _public member_ `TArray<FDMXOutputPortReference> OutputPortReferences;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NonTransactional, Category = "DMX", Meta = (DisplayName = "Output Ports"))` — Output ports of the Library of a Library

#### class `UDMXLibrary`  
`class UDMXLibrary : public UDMXObjectBase`  
_L50-283_
- reflection: `UCLASS(BlueprintType, Blueprintable, Config = DMXEditor, AutoExpandCategories = DMX)`
- inherits: `UDMXObjectBase`
- desc: DMX Library. Holds Fixture Types and Fixture Patches that can be used to send and receive DMX.
- L60 _public prototype_ `UDMXLibrary();` — Constructor
- L64 _protected prototype_ `virtual void PostInitProperties() override;`
- L65 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L66 _protected prototype_ `virtual void PostLoad() override;`
- L67 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L70 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L75 _protected prototype_ `void RegisterEntity(UDMXEntity* Entity);` — Registers an Entity with this Library
- L78 _protected prototype_ `void UnregisterEntity(UDMXEntity* Entity);` — Unregisters an Entity from this Library
- L82 _public prototype_ `UDMXEntity* GetOrCreateEntityObject(const FString& InName, TSubclassOf<UDMXEntity> DMXEntityClass);` — `UE_DEPRECATED(5.0, "Deprecated in favor of new UDMXEntityFixtureType::CreateFixtureType and UDMXEntityFixturePatch::CreateFixturePatch that support creating patches in blueprints.")`
- L88 _public prototype_ `UDMXEntity* FindEntity(const FString& InSearchName) const;` — Returns an Entity named InSearchName. If none exists, return nullptr This is not very reliable since Entities of different types can have the same name.
- L94 _public prototype_ `UDMXEntity* FindEntity(const FGuid& Id);` — Returns an Entity with the passed in ID. The most reliable method since Entities ID are always unique.
- L100 _public prototype_ `int32 FindEntityIndex(UDMXEntity* InEntity) const;` — The finds the index of an existing entity. @return The index of the entity or INDEX_NONE if not found or the Entity doesn't belong to this Library.
- L104 _public prototype_ `void AddEntity(UDMXEntity* InEntity);` — `UE_DEPRECATED(5.0, "Entites no longer can be added or removed explicitly.")` — Adds an Entity to the library
- L107 _public prototype_ `void SetEntityIndex(UDMXEntity* InEntity, const int32 NewIndex);` — Move an Entity to a specific index in the Entities Array.
- L111 _public prototype_ `void RemoveEntity(const FString& EntityName);` — `UE_DEPRECATED(5.0, "Entites no longer can be added or removed explicitly.")` — Removes an Entity from this DMX Library searching it by name.
- L115 _public prototype_ `void RemoveEntity(UDMXEntity* InEntity);` — `UE_DEPRECATED(5.0, "Entites no longer can be added or removed explicitly.")` — Removes an Entity from this DMX Library.
- L119 _public prototype_ `void RemoveAllEntities();` — `UE_DEPRECATED(5.0, "Entites no longer can be added or removed explicitly.")` — Empties this DMX Library array of Entities
- L122 _public prototype_ `const TArray<UDMXEntity*>& GetEntities() const;` — Returns all Entities in this DMX Library
- L125 _public prototype_ `TArray<UDMXEntity*> GetEntitiesOfType(TSubclassOf<UDMXEntity> InEntityClass) const;` — Get an array with entities from the specified UClass, but not typecast.
- L129 _public function_ `template <typename EntityType> TArray<EntityType*> GetEntitiesTypeCast() const` — Get an array of Entities from the specified template type, already cast.
- L147 _public function_ `template <typename EntityType> void ForEachEntityOfType(TFunction<void(EntityType*)> Predicate) const` — Calls Predicate on all Entities of the template type. This is the version without break.
- L163 _public function_ `template <typename EntityType> void ForEachEntityOfTypeWithBreak(TFunction<bool(EntityType*)> Predicate) const` — Calls Predicate on all Entities of the template type Return false from the predicate to break the iteration loop or true to keep iterating.
- L182 _public prototype_ `void ForEachEntityOfType(TSubclassOf<UDMXEntity> InEntityClass, TFunction<void(UDMXEntity*)> Predicate) const;` — Calls Predicate on all Entities of the passed in type. This is the version without break. Casting is left to the caller.
- L189 _public prototype_ `void ForEachEntityOfTypeWithBreak(TSubclassOf<UDMXEntity> InEntityClass, TFunction<bool(UDMXEntity*)> Predicate) const;` — Calls Predicate on all Entities of the passed in type. Return false from the predicate to break the iteration loop or true to keep iterating. Casting is left to the caller.
- L192 _public prototype_ `static FDMXOnEntityArrayChangedDelegate& GetOnEntitiesAdded();` — Returns a delegate that is broadcast when entities were added to the library
- L195 _public prototype_ `static FDMXOnEntityArrayChangedDelegate& GetOnEntitiesRemoved();` — Returns a delegate that is broadcast when entities were removed from the library
- L199 _public prototype_ `FOnEntitiesUpdated_DEPRECATED& GetOnEntitiesUpdated();` — `UE_DEPRECATED(5.0, "Deprecated in favor of the more expressive UDMXLibrary::GetOnEntitiesAdded() and UDMXLibrary::GetOnEntitiesRemoved() that also forwards the added resp. removed entities")`
- L202 _public prototype_ `TSet<int32> GetAllLocalUniversesIDsInPorts() const;` — Returns all local Universe IDs in Ports
- L205 _public function_ `const TSet<FDMXInputPortSharedRef>& GetInputPorts() const` — Returns the input ports
- L208 _public function_ `const TSet<FDMXOutputPortSharedRef>& GetOutputPorts() const` — Returns the output ports
- L211 _public prototype_ `TSet<FDMXPortSharedRef> GenerateAllPortsSet() const;` — Returns all ports as a set, slower than GetInputPorts and GetOutputPorts.
- L214 _public prototype_ `void UpdatePorts();` — Updates the ports from what's set in the Input and Output Port References arrays
- L221 _public prototype_ `void SetMVRGeneralSceneDescription(UDMXMVRGeneralSceneDescription* NewGeneralSceneDescription);` — Sets the MVR General Scene Description of the Library. Note, this will not add any patches that occur in the new General Scene Description. Note, this will not remove any patches that do not occur in the new General Scene Description.
- L225 _public prototype_ `UDMXMVRGeneralSceneDescription* UpdateGeneralSceneDescription();` — Updates the General Scene Description to reflect the Library
- L233 _public function_ `UDMXMVRGeneralSceneDescription* GetLazyGeneralSceneDescription() const` — Returns the General Scene Description of the Library. May not always represent the state of the library. Use WriteGeneralSceneDescription to update it to get an exact version.
- L236 _public function_ `TWeakObjectPtr<UDMXEntity> GetLastAddedEntity() const` — Returns the Entity that was last added to the Library
- L239 _public function_ `static FName GetPortReferencesPropertyName()`
- L240 _public function_ `static FName GetEntitiesPropertyName()`
- L241 _public function_ `static FName GetGeneralSceneDescriptionPropertyName()`
- L250 _protected prototype_ `void UpgradeFromControllersToPorts();` — Upgrades libraries that use controllers (before 4.27) to use ports instead (from 4.27 on). Creates corresponding ports if they do not exist yet.
- L255 _protected member_ `FDMXLibraryPortReferences PortReferences;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NonTransactional, Category = "DMX", Meta = (ShowOnlyInnerProperties))` — Ports of the Library
- L260 _private member_ `TArray<TObjectPtr<UDMXEntity>> Entities;` — `UPROPERTY()` — All Fixture Types and Fixture Patches in the Library
- L264 _private member_ `TObjectPtr<UDMXMVRGeneralSceneDescription> GeneralSceneDescription;` — `UPROPERTY()` — The General Scene Description of this Library
- L267 _private member_ `TWeakObjectPtr<UDMXEntity> LastAddedEntity;` — The entity that was added last to the Library
- L270 _private member_ `TSet<FDMXInputPortSharedRef> InputPorts;` — The input ports available to the library, according to the InputPortReferences array
- L273 _private member_ `TSet<FDMXOutputPortSharedRef> OutputPorts;` — The output ports available to the library, according to the OutputPortReferences array
- L276 _private member_ `static FDMXOnEntityArrayChangedDelegate OnEntitiesAddedDelegate;` — Delegate broadcast when Entities were added
- L279 _private member_ `static FDMXOnEntityArrayChangedDelegate OnEntitiesRemovedDelegate;` — Delegate broadcast when Entities were removed
- L282 _private member_ `FOnEntitiesUpdated_DEPRECATED OnEntitiesUpdated_DEPRECATED;` — DEPRECATED 5.0

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMXOnEntityArrayChangedDelegate, class UDMXLibrary*, TArray<UDMXEntity*>);`
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMXOnEntityArrayChangedDelegate, class UDMXLibrary*, TArray<UDMXEntity*>);`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntitiesUpdated_DEPRECATED, class UDMXLibrary*);` — DEPRECATED 5.0
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntitiesUpdated_DEPRECATED, class UDMXLibrary*);` — DEPRECATED 5.0

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXObjectBase.h` (Public)


#### class `UDMXObjectBase`  
`class UDMXObjectBase : public UObject`  
_L10-14_
- reflection: `UCLASS(abstract)`
- inherits: `UObject`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRAssetImportData.h` (Public)


#### class `UDMXMVRAssetImportData`  
`class UDMXMVRAssetImportData : public UAssetImportData`  
_L17-49_
- reflection: `UCLASS()`
- inherits: `UAssetImportData`
- L24 _public function_ `const FString& GetFilePathAndName() const` — Returns the imported file path and name
- L28 _public prototype_ `void SetSourceFile(const FString& InFilePathAndName);` — Sets the source file and initializes members from it
- L31 _public function_ `const TArray64<uint8>& GetRawSourceData() const` — Returns the raw source file as byte array, as it was imported
- L36 _protected prototype_ `virtual void PostLoad() override;`
- L42 _private member_ `FString FilePathAndName;` — `UPROPERTY()` — The imported file path and name
- L47 _private member_ `FDMXByteArray64 RawSourceData;` — `UPROPERTY()` — The raw source file as byte array, as it was imported

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRAssetUserData.h` (Public)


#### class `UDMXMVRAssetUserData`  
`class UDMXMVRAssetUserData : public UAssetUserData`  
_L13-37_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- desc: Asset user data for Actors in an MVR Scene
- L20 _public prototype_ `static UDMXMVRAssetUserData* GetMVRAssetUserData(const AActor& Actor);` — Returns MVR Asset User Data for the Actor, or nullptr if there is no asset user data
- L23 _public prototype_ `static FString GetMVRAssetUserDataValueForKey(const AActor& Actor, const FName Key);` — Returns the Value in Meta data given a Key, or an empty String if the Key doesn't exist
- L26 _public prototype_ `static bool SetMVRAssetUserDataValueForKey(AActor& InOutActor, FName InKey, const FString& InValue);` — Sets the Value for Key in Meta Data. Creates the Key if it doesn't exist.
- L30 _public member_ `TMap<FName, FString> MetaData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "MVR")` — MVR Meta Data for the Actor
- L33 _public member_ `static const FName MVRFixtureUUIDMetaDataKey;` — The key for the MVR UUID meta data
- L36 _public member_ `static const FName FixturePatchMetaDataKey;` — The key for the Fixture Patch meta data

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRFixtureActorLibrary.h` (Public)


#### class `FDMXMVRFixtureActorLibrary`  
`class FDMXMVRFixtureActorLibrary : public FGCObject , public TSharedFromThis<FDMXMVRFixtureActorLibrary>`  
_L17-40_
- inherits: `FGCObject,TSharedFromThis<FDMXMVRFixtureActorLibrary>`
- L23 _public prototype_ `FDMXMVRFixtureActorLibrary();` — Constructor
- L26 _public prototype_ `UClass* FindMostAppropriateActorClassForPatch(const UDMXEntityFixturePatch* Patch) const;` — Returns the Actor that can represent the patch best
- L30 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L31 _protected function_ `virtual FString GetReferencerName() const override`
- L39 _private member_ `TArray<TObjectPtr<AActor>> MVRActors;` — Array of actors that implement the MVR Actor Interface

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRGeneralSceneDescription.h` (Public)


#### struct `UE::DMX::FDMXMVRGeneralSceneDescriptionWorldParams`  
`struct FDMXMVRGeneralSceneDescriptionWorldParams`  
_L23-35_
- L25 _public member_ `UWorld* World = nullptr;`
- L28 _public member_ `bool bExportPatchesNotPresentInWorld = false;` — If checked, exports patches that are not in use in the level
- L31 _public member_ `bool bCreateMultiPatchFixtures = false;` — If checked, creates individual MVR Fixtures for each Fixture that uses the same Patch in the Level.
- L34 _public member_ `bool bUseTransformsFromLevel = true;` — If checked, exports the fixtures with transforms as in the current level

#### class `UDMXMVRGeneralSceneDescription`  
`class UDMXMVRGeneralSceneDescription : public UObject`  
_L41-122_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: MVR General Scene Description Object
- L46 _private typedef_ `using FDMXMVRGeneralSceneDescriptionWorldParams = UE::DMX::FDMXMVRGeneralSceneDescriptionWorldParams;`
- L50 _public prototype_ `UDMXMVRGeneralSceneDescription();` — Constructor
- L53 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Gets the MVR Fixture Nodes in this General Scene Description
- L56 _public prototype_ `UDMXMVRFixtureNode* FindFixtureNode(const FGuid& FixtureUUID) const;` — Returns the Fixture Node corresponding to the UUID, or nullptr if it cannot be found
- L60 _public prototype_ `static UDMXMVRGeneralSceneDescription* CreateFromXmlFile(TSharedRef<FXmlFile> GeneralSceneDescriptionXml, UObject* Outer, FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags);` — Creates an MVR General Scene Description from an Xml File
- L63 _public prototype_ `static UDMXMVRGeneralSceneDescription* CreateFromDMXLibrary(const UDMXLibrary& DMXLibrary, UObject* Outer, FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags);` — Creates an MVR General Scene Description from a DMX Library
- L67 _public prototype_ `void WriteDMXLibraryToGeneralSceneDescription(const UDMXLibrary& DMXLibrary);` — `UE_DEPRECATED(5.5, "Changed to WriteDMXLibrary for better readability and consitency with new members.")` — DEPRECATED 5.5
- L75 _public prototype_ `void WriteDMXLibrary(const UDMXLibrary& DMXLibrary, FDMXMVRGeneralSceneDescriptionWorldParams WorldParams = FDMXMVRGeneralSceneDescriptionWorldParams());` — Writes the Library to the General Scene Description, effectively removing inexisting and adding new MVR Fixtures, according to what MVR Fixture UUIDs the Fixture Patches of the Library contain. If world params are specified, considers these.
- L78 _public prototype_ `void RemoveFixtureNode(const FGuid& FixtureUUID);` — Removes a fixture node from the General Scene Description.
- L81 _public prototype_ `bool CanCreateXmlFile(FText& OutReason) const;` — Returns true if an Xml File can be created. Gives a reason if no MVR can be exported
- L84 _public prototype_ `TSharedPtr<FXmlFile> CreateXmlFile() const;` — Creates an General Scene Description Xml File from this.
- L87 _public function_ `UDMXMVRAssetImportData* GetMVRAssetImportData() const` — Returns MVR Asset Import Data for this asset
- L98 _private prototype_ `void WriteFixturePatch(const UDMXEntityFixturePatch& FixturePatch, const FTransform& Transform, const FGuid& MultiPatchUUID = FGuid());` — Writes the Fixture Patch to the General Scene Description. Optionally a transform can be specified for the patch. Optionally a MultiPatch UUID can be passed so the patch is added as a multi patch. When a MultiPatch UUID is provided, the parent with related UUID is expected to exist already.
- L101 _private prototype_ `void SanetizeFixtureNode(UDMXMVRFixtureNode& FixtureNode);` — Makes sure the node has a unique MVR UUID and Fixture ID
- L104 _private prototype_ `[[nodiscard]] bool ParseGeneralSceneDescriptionXml(const TSharedRef<FXmlFile>& GeneralSceneDescriptionXml);` — Parses a General Scene Description Xml File. Only ment to be used for initialization (ensured)
- L107 _private prototype_ `TMap<const UDMXComponent*, const AActor*> GetDMXComponentToActorMap(const UWorld* World) const;` — Returns a map of DMX components with their actor from a world
- L111 _private prototype_ `TArray<int32> GetNumericalFixtureIDsInUse(const UDMXLibrary& DMXLibrary);` — Returns the Fixture IDs currently in use, as number, sorted from lowest to highest
- L115 _private member_ `TObjectPtr<UDMXMVRRootNode> RootNode;` — `UPROPERTY()` — The Root Node of the General Scene Description
- L120 _private member_ `TObjectPtr<UDMXMVRAssetImportData> MVRAssetImportData;` — `UPROPERTY()` — Import Data for this asset

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRSceneActor.h` (Public)


#### struct `FDMXMVRSceneFixtureTypeToActorClassPair`  
`struct FDMXMVRSceneFixtureTypeToActorClassPair`  
_L19-30_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `TSoftObjectPtr<UDMXEntityFixtureType> FixtureType;` — `UPROPERTY(VisibleAnywhere, Category = "MVR")` — The Fixture Type of the Actor.
- L29 _public member_ `TSoftClassPtr<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MVR, NoClear, meta = (MustImplement = "/Script/DMXFixtureActorInterface.DMXMVRFixtureActorInterface"))` — The Actor Class that should be or was spawned. Only Actors that implement the MVR Fixture Actor Interface can be used.

#### struct `FDMXMVRSceneGDTFToActorClassPair`  
`struct FDMXMVRSceneGDTFToActorClassPair`  
_L34-45_
- reflection: `UE_DEPRECATED(5.5, "Instead use FDMXMVRSceneFixtureTypeToActorClassPair")`
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "Deprecated 5.5. Instead use DMXMVRSceneFixtureTypeToActorClassPair"))`
- L40 _public member_ `TSoftObjectPtr<UDMXImportGDTF> GDTF;` — `UPROPERTY(VisibleAnywhere, Category = "MVR")` — The GDTF of the Actor.
- L44 _public member_ `TSoftClassPtr<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MVR, NoClear, meta = (MustImplement = "/Script/DMXFixtureActorInterface.DMXMVRFixtureActorInterface"))` — The Actor Class that should be or was spawned. Only Actors that implement the MVR Fixture Actor Interface can be used.

#### class `ADMXMVRSceneActor`  
`class ADMXMVRSceneActor : public AActor`  
_L48-180_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `AActor`
- L54 _public prototype_ `ADMXMVRSceneActor();`
- L55 _public prototype_ `~ADMXMVRSceneActor();`
- L58 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L59 _public prototype_ `virtual void PostLoad() override;`
- L60 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L62 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L63 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L67 _public prototype_ `void SetDMXLibrary(UDMXLibrary* NewDMXLibrary);` — Sets the dmx library for this MVR actor. Should only be called once, further calls will have no effect and hit an ensure condition
- L70 _public prototype_ `void RefreshFromDMXLibrary();` — Refreshes the scene from the DMX Library
- L73 _public prototype_ `TArray<AActor*> GetActorsSpawnedForFixtureType(const UDMXEntityFixtureType* FixtureType) const;` — Returns an array of actors that are currently spawned in the scene for the specified Fixture Type
- L77 _public prototype_ `TArray<AActor*> GetActorsSpawnedForGDTF(const UDMXImportGDTF* GDTF) const;` — `UE_DEPRECATED(5.5, "MVRSceneActor now spawns actors for all Fixture Types, not only those that have a GDTF asset. Instead now use GetActorsSpawnedForFixtureType")` — Returns an array of actors that are currently spawned in the scene for specified GDTF
- L81 _public function_ `UDMXLibrary* GetDMXLibrary() const` — Returns the DMX Library of this MVR Scene Actor
- L84 _public function_ `const TArray<TSoftObjectPtr<AActor>>& GetRelatedActors() const` — Returns the MVR UUID To Related Actor Map
- L89 _public member_ `bool bRespawnDeletedActorsOnRefresh = false;` — `UPROPERTY(EditAnywhere, Category = "MVR", meta = (DisplayName = "Respawn Deleted Actors"))` — If checked, respawns Fixture Actors deleted from the MVR Scene
- L93 _public member_ `bool bUpdateTransformsOnRefresh = false;` — `UPROPERTY(EditAnywhere, Category = "MVR", meta = (DisplayName = "Update Transforms"))` — If checked, updates transforms from the DMX Library
- L98 _public function_ `static FName GetDMXLibraryPropertyNameChecked()` — Property name getters
- L99 _public function_ `static FName GetRelatedAcctorsPropertyNameChecked()`
- L100 _public function_ `static FName GetFixtureTypeToActorClassesPropertyNameChecked()`
- L101 _public function_ `static FName GetMVRSceneRootPropertyNameChecked()`
- L104 _public function_ `static FName GetGDTFToDefaultActorClassesPropertyNameChecked()` — `UE_DEPRECATED(5.5, "GDTFToDefaultActorClasses is no longer used as all Fixture Types can generate GDTFs. To upgrade please refer to FixtureTypeToActorClasses.")`
- L113 _private prototype_ `void EnsureMVRUUIDsForRelatedActors();` — Set MVR UUIDs for related Actors
- L117 _private prototype_ `void UpdateFixtureTypeToDefaultActorClasses(const TSharedRef<FDMXMVRFixtureActorLibrary>& MVRFixtureActorLibrary);` — Updates the FixtureTypeToDefaultActorClasses map so it only contains those entries present both in the DMX Library and the MVR Scene
- L121 _private prototype_ `UDMXEntityFixturePatch* GetFixturePatchFromActor(AActor* Actor) const;` — Gets the Fixture Patch of an Actor, or nullptr if the Fixture Patch cannot be retrieved anymore
- L124 _private prototype_ `void SetFixturePatchOnActor(AActor* Actor, UDMXEntityFixturePatch* FixturePatch);` — Sets the Fixture Patch on an Actor if possible or fails silently
- L128 _private prototype_ `void OnMapChange(uint32 MapChangeFlags);` — Called when a sub-level is loaded
- L131 _private prototype_ `void OnActorDeleted(AActor* DeletedActor);` — Called when an actor got deleted in editor
- L134 _private prototype_ `void OnAssetPostImport(UFactory* InFactory, UObject* ActorAdded);` — Called when an asset was imported
- L137 _private prototype_ `void HandleDefaultActorClassForFixtureTypeChanged();` — Replaces related Actors that use the Default Actor Class for the Fixture Type with an instance of the new Default Actor Class
- L140 _private prototype_ `AActor* SpawnMVRActor(const TSubclassOf<AActor>& ActorClass, UDMXEntityFixturePatch * FixturePatch, const FTransform & Transform, AActor * Template = nullptr);` — Spawns an MVR Actor in this Scene. Returns the newly spawned Actor, or nullptr if no Actor could be spawned.
- L143 _private prototype_ `AActor* ReplaceMVRActor(AActor* ActorToReplace, const TSubclassOf<AActor>& ClassOfNewActor);` — Replaces an MVR Actor in this Scene with another. Returns the newly spawned Actor, or nullptr if no Actor could be spawned.
- L146 _private prototype_ `void UpgradeToFixtureTypeToActorClasses();` — Upgrades this Actor created before 5.5 to use the FixtureTypeToActorClasses array instead of the deprecated GDTFToDefaultActorClasses array
- L151 _private member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MVR", meta = (AllowPrivateAccess = true))` — The DMX Library this Scene Actor uses
- L155 _private member_ `TArray<TSoftObjectPtr<AActor>> RelatedActors;` — `UPROPERTY(VisibleAnywhere, Category = "Actor", AdvancedDisplay, meta = (AllowPrivateAccess = true))` — The actors that created along with this scene
- L160 _private member_ `TArray<FDMXMVRSceneGDTFToActorClassPair> GDTFToDefaultActorClasses_DEPRECATED;` — `UPROPERTY()` — DEPRECATED 5.5, instead use FixtureTypeToActorClasses
- L165 _private member_ `TArray<FDMXMVRSceneFixtureTypeToActorClassPair> FixtureTypeToActorClasses;` — `UPROPERTY(EditAnywhere, Category = "MVR", meta = (DispayName = "Fixture Type to Spawned Actor"))` — The actor class that is spawned for a specific Fixture Type by default (can be overriden per MVR UUID, see below)
- L169 _private member_ `TArray<FGuid> DeletedMVRFixtureUUIDs;` — `UPROPERTY()` — Array holding MVR Fixture UUIDs that were explicitly removed from the scene
- L174 _private member_ `TArray<FDMXMVRSceneFixtureTypeToActorClassPair> FixtureTypeToActorClasses_PreEditChange;` — `UPROPERTY(Transient)` — The FixtureTypeToActorClasses cached of PreEditChange, to find changes.
- L179 _private member_ `TObjectPtr<USceneComponent> MVRSceneRoot;` — `UPROPERTY(VisibleAnywhere, Category = "Actor", AdvancedDisplay, meta = (AllowPrivateAccess = true))` — The root component to which all actors are attached initially

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/DMXMVRVersion.h` (Public)


#### struct `FDMXMVRVersion`  
`struct FDMXMVRVersion`  
_L9-25_
- desc: Version of the MVR standard currently being used by the engine
- L11 _public member_ `static const int32 MajorVersion = 1;`
- L13 _public member_ `static const int32 MinorVersion = 5;`
- L15 _public prototype_ `static const FString GetMajorVersionAsString();`
- L16 _public prototype_ `static const FString GetMinorVersionAsString();`
- L19 _public function_ `static bool IsLatest(int32 InMajorVersion, int32 InMinorVersion)` — Returns true if the provided version is the latest version

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRChildListNode.h` (Public)


#### class `UDMXMVRChildListNode`  
`class UDMXMVRChildListNode : public UObject`  
_L17-58_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This node defines a generic graphical object.
- L24 _public prototype_ `void InitializeFromChildListXmlNode(const FXmlNode& ChildListXmlNode);` — Initializes the Child List Node and its Children from a Child List Xml Node. Does not merge, clears previous entries.
- L27 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L30 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Returns the Fixture Nodes contained in this Layer. Note, does not clear the array.
- L33 _public prototype_ `bool Contains(UDMXMVRParametricObjectNodeBase* ParametricObjectNode);` — Returns true if the Parametric Object Node is contained in this Child List
- L36 _public prototype_ `TObjectPtr<UDMXMVRParametricObjectNodeBase>* FindParametricObjectNodeByUUID(const FGuid& UUID);` — Returns a pointer ot the Parametric Object Node that corresponds to the UUID, or nullptr if there is no corresponding Parametric Object Node
- L40 _public function_ `template<typename ParametricObjectNodeClass, typename TEnableIf<TIsDerivedFrom<ParametricObjectNodeClass, UDMXMVRParametricObjectNodeBase>::Value, bool>::Type = true> ParametricObjectNodeClass* CreateParametricObject()` — Creates a Parametric Object Node as a Child in the Child List Node
- L49 _public prototype_ `bool RemoveParametricObject(UDMXMVRParametricObjectNodeBase* ParametricObjectNodeToRemove);` — Removes a Parametric Object Child from the Child List. Returns true if the Parametric Object Node was contained and Removed
- L52 _public function_ `const TArray<TObjectPtr<UDMXMVRParametricObjectNodeBase>>& GetParametricObjectNodes() const` — Returns the Parametric Object Node Children of this Child List Node
- L57 _private member_ `TArray<TObjectPtr<UDMXMVRParametricObjectNodeBase>> ParametricObjectNodes;` — `UPROPERTY()` — A list of geometrical representation objects that are part of the object.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRFixtureNode.h` (Public)


#### struct `FDMXMVRFixtureAddresses`  
`struct FDMXMVRFixtureAddresses`  
_L20-42_
- reflection: `USTRUCT()`
- desc: The container for DMX Addresses for this fixture.
- L24 _public function_ `FDMXMVRFixtureAddresses() : Universe(1) , Address(1)`
- L29 _public function_ `FDMXMVRFixtureAddresses(int32 InUniverse, int32 InAddress) : Universe(InUniverse) , Address(InAddress)`
- L35 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L38 _public member_ `int32 Universe;` — `UPROPERTY()`
- L41 _public member_ `int32 Address;` — `UPROPERTY()`

#### struct `FDMXMVRFixtureMapping`  
`struct FDMXMVRFixtureMapping`  
_L46-70_
- reflection: `USTRUCT()`
- desc: Defines a Mapping
- L51 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L54 _public member_ `FGuid LinkedDef;` — The unique identifier of the MappingDefinition node that will be the source of the mapping.
- L57 _public member_ `TOptional<int32> UX;` — The offset in pixels in x direction from top left corner of the source that will be used for the mapped object.
- L60 _public member_ `TOptional<int32> UY;` — The offset in pixels in y direction from top left corner of the source that will be used for the mapped object.
- L63 _public member_ `TOptional<int32> OX;` — The size in pixels in x direction from top left of the starting point.
- L66 _public member_ `TOptional<int32> OY;` — The size in pixels in y direction from top left of the starting point.
- L69 _public member_ `TOptional<float> RZ;` — The rotation around the middle point of the defined rectangle in degree. Positive direction is counter cock wise.

#### struct `FDMXMVRFixtureGobo`  
`struct FDMXMVRFixtureGobo`  
_L74-93_
- reflection: `USTRUCT()`
- desc: The Gobo used for the fixture. The image ressource must apply to the GDTF standard.
- L80 _public member_ `FString Value;` — `UPROPERTY()` — The node value is the Gobo used for the fixture. The image ressource must apply to the GDTF standard. Use a FileName to specify.
- L84 _public member_ `FDMXOptionalFloat Rotation;` — `UPROPERTY()` — The roation of the Gobo in degree.

#### struct `FDMXOptionalMVRFixtureGobo`  
`struct FDMXOptionalMVRFixtureGobo`  
_L96-130_
- reflection: `USTRUCT()`
- L101 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L103 _public member_ `TOptional<FDMXMVRFixtureGobo> Value;`
- L105 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXOptionalMVRFixtureGobo> : public TStructOpsTypeTraitsBase2<FDMXOptionalMVRFixtureGobo>`  
_L133-141_
- inherits: `TStructOpsTypeTraitsBase2<FDMXOptionalMVRFixtureGobo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L137-140_

#### class `UDMXMVRFixtureNode`  
`class UDMXMVRFixtureNode : public UDMXMVRParametricObjectNodeBase`  
_L146-242_
- reflection: `UCLASS()`
- inherits: `UDMXMVRParametricObjectNodeBase`
- desc: This node defines a light fixture object.
- L153 _public prototype_ `bool InitializeFromFixtureXmlNode(const FXmlNode& FixtureXmlNode);` — Initializes the Fixture Node and its Children from a Fixture Xml Node. Does not merge, clears previous entries.
- L156 _public prototype_ `virtual void CreateXmlNodeInParent(FXmlNode& ParentNode) const override;`
- L160 _public prototype_ `bool IsValid(bool bLogInvalidReason) const;` — Returns true if the data is sufficient to fullfill the mvr standard. If bLogInvalidReason is set to true, logs the reason for the fixture being invalid
- L164 _public member_ `FString Name;` — `UPROPERTY()` — The name of the object.
- L171 _public member_ `FDMXOptionalGuid MultiPatch;` — `UPROPERTY()` — The unique identifier of the parent multipatch fixture. When this value is set, you may not define a FixtureID or CustomID for this fixture. The FixtureID and CustomID from the object defined as multi parent also applies to this object.
- L175 _public member_ `FDMXOptionalGuid Classing;` — `UPROPERTY()` — The Class the object belongs to.
- L179 _public member_ `FString GDTFSpec;` — `UPROPERTY()` — The name of the file containing the GDTF information for this light fixture.
- L183 _public member_ `FString GDTFMode;` — `UPROPERTY()` — The name of the used DMX mode. This has to match the name of a DMXMode in the GDTF file.
- L187 _public member_ `FDMXOptionalGuid Focus;` — `UPROPERTY()` — A focus point reference that this lighting fixture aims at if this reference exists.
- L191 _public member_ `FDMXOptionalBool CastShadow;` — `UPROPERTY()` — Defines if a Object cast Shadow.
- L195 _public member_ `FDMXOptionalGuid Position;` — `UPROPERTY()` — A position reference that this lighting fixture belongs to if this reference exists.
- L199 _public member_ `FString FixtureID;` — `UPROPERTY()` — The Fixture Id of the lighting fixture. This is the short name of the fixture.
- L203 _public member_ `int32 UnitNumber = 0;` — `UPROPERTY()` — The unit number of the lighting fixture in a position.
- L206 _public function_ `void SetUniverseID(int32 UniverseID)` — Sets the Universe ID, in UE form (Index 0 is ID 1)
- L209 _public function_ `int32 GetUniverseID() const` — Returns the Universe ID, in UE form (Index 0 is ID 1)
- L212 _public function_ `void SetStartingChannel(int32 Address)` — Sets the Address of the MVR Fixture
- L215 _public function_ `int32 GetStartingChannel() const` — Returns the Address of the MVR Fixture
- L220 _private member_ `FDMXMVRFixtureAddresses Addresses;` — `UPROPERTY()` — The container for DMX Addresses for this fixture.
- L225 _public member_ `FDMXOptionalColorCIE1931 CIEColor;` — `UPROPERTY()` — A color assigned to a fixture. If it is not defined, there is no color for the fixture.
- L229 _public member_ `FDMXOptionalInt32 FixtureTypeId;` — `UPROPERTY()` — The Fixture Type ID is a value that can be used as a short name of the Fixture Type. This does not have to be unique. The default value is 0.
- L233 _public member_ `FDMXOptionalInt32 CustomId;` — `UPROPERTY()` — The Custom ID is a value that can be used as a short name of the Fixture Instance. This does not have to be unique. The default value is 0.
- L237 _public member_ `TArray<FDMXMVRFixtureMapping> Mappings;` — `UPROPERTY()` — The container for Mappings for this fixture.
- L241 _public member_ `FDMXOptionalMVRFixtureGobo Gobo;` — `UPROPERTY()` — The Gobo used for the fixture. The image ressource must apply to the GDTF standard.

#### Free symbols / members of external scopes

- L86 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXMVRFixtureGobo& Gobo)`
- L111 _function_ `friend bool operator==(const FDMXOptionalMVRFixtureGobo& A, const FDMXOptionalMVRFixtureGobo& B)`
- L126 _function_ `friend bool operator!=(const FDMXOptionalMVRFixtureGobo& A, const FDMXOptionalMVRFixtureGobo& B)`
- L138 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon4f1ffa3d0103`)
- L139 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon4f1ffa3d0103`)

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRGroupObjectNode.h` (Public)


#### class `UDMXMVRGroupObjectNode`  
`class UDMXMVRGroupObjectNode : public UDMXMVRParametricObjectNodeBase`  
_L22-63_
- reflection: `UCLASS()`
- inherits: `UDMXMVRParametricObjectNodeBase`
- desc: This node defines logical group of objects. The child objects are located inside a local coordinate system.
- L29 _public prototype_ `UDMXMVRGroupObjectNode();` — Constructor
- L32 _public prototype_ `void InitializeFromGroupObjectXmlNode(const FXmlNode& GroupObjectXmlNode);` — Initializes the Child List Node and its Children from a Group Object Xml Node. Does not merge, clears previous entries.
- L35 _public prototype_ `virtual void CreateXmlNodeInParent(FXmlNode& ParentNode) const override;`
- L39 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Returns the Fixture Nodes contained in this Layer. Note, does not clear the array.
- L42 _public prototype_ `bool Contains(UDMXMVRParametricObjectNodeBase* ParametricObjectNode);` — Returns true if the Parametric Object Node is contained in this Group Object Node
- L45 _public prototype_ `TObjectPtr<UDMXMVRParametricObjectNodeBase>* FindParametricObjectNodeByUUID(const FGuid& InUUID);` — Returns a pointer ot the Parametric Object Node that corresponds to the UUID, or nullptr if there is no corresponding Parametric Object Node
- L48 _public prototype_ `bool RemoveParametricObjectNode(UDMXMVRParametricObjectNodeBase* ParametricObjectNode);` — Removes the Parametric Object Node from Child List. Returns true if the Node was removed.
- L51 _public function_ `UDMXMVRChildListNode* GetChildListNode() const` — Returns a list of graphic objects that are part of the group.
- L57 _public member_ `FDMXOptionalString Name;` — `UPROPERTY()` — The name of the GroupObject
- L62 _private member_ `TObjectPtr<UDMXMVRChildListNode> ChildListNode;` — `UPROPERTY()` — A list of graphic objects that are part of the group.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRLayerNode.h` (Public)


#### class `UDMXMVRLayerNode`  
`class UDMXMVRLayerNode : public UObject`  
_L20-69_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A Layer node in the Layers Node of a Scene.
- L27 _public prototype_ `UDMXMVRLayerNode();` — Constructor
- L30 _public prototype_ `void InitializeFromLayerXmlNode(const FXmlNode& LayerXmlNode);` — Initializes the Layer Node and its Children from a Layer Xml Node. Does not merge, clears previous entries.
- L33 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L36 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Returns the Fixture Nodes contained in this Layer. Note, does not clear the array.
- L39 _public prototype_ `bool Contains(UDMXMVRParametricObjectNodeBase* ParametricObjectNode);` — Returns true if the Parametric Object Node is contained in this layer
- L42 _public prototype_ `TObjectPtr<UDMXMVRParametricObjectNodeBase>* FindParametricObjectNodeByUUID(const FGuid& InUUID) const;` — Returns a pointer ot the Parametric Object Node that corresponds to the UUID, or nullptr if there is no corresponding Parametric Object Node
- L45 _public function_ `UDMXMVRChildListNode* GetChildListNode() const` — Returns a list of graphic objects that are part of the layer.
- L49 _public member_ `FGuid UUID;` — `UPROPERTY()` — The unique identifier of the object.
- L53 _public member_ `FDMXOptionalString Name;` — `UPROPERTY()` — The name of the object
- L63 _public member_ `FDMXOptionalTransform Matrix;` — `UPROPERTY()` — The transformation matrix that defines the location and orientation of this the layer inside its global coordinate space. This effectively defines local coordinate space for the objects inside. The Matrix of the Layer is only allowed to have an elevation, but no rotation. UE specific: Note, we do not use an FVector since the standard clearly specifies a transformation matrix, even tho it also forbids any rotation. While it makes the code more readable and future proof, the user of this struct is responsible to follow the standard directly.
- L68 _private member_ `TObjectPtr<UDMXMVRChildListNode> ChildListNode;` — `UPROPERTY()` — A list of graphic objects that are part of the group.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRLayersNode.h` (Public)


#### class `UDMXMVRLayersNode`  
`class UDMXMVRLayersNode : public UObject`  
_L19-50_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This node defines a list of layers inside the scene. The layer is a container of graphical objects defining a local coordinate system.
- L26 _public prototype_ `void InitializeFromLayersXmlNode(const FXmlNode& LayersXmlNode);` — Initializes the Layers Node and its Children from a Layers Xml Node. Does not merge, clears previous entries.
- L29 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L32 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Returns the Fixture Nodes contained in this Layer. Note, does not clear the array.
- L35 _public prototype_ `TObjectPtr<UDMXMVRParametricObjectNodeBase>* FindParametricObjectNodeByUUID(const FGuid& UUID) const;` — Returns a pointer ot the Parametric Object Node that corresponds to the UUID, or nullptr if there is no corresponding Parametric Object Node
- L38 _public prototype_ `UDMXMVRLayerNode* CreateLayer();` — Creates a new Layer. Returns the newly created Layer
- L41 _public prototype_ `void RemoveLayer(UDMXMVRLayerNode* LayerNodeToRemove);` — Removes a Layer. Ensures the Layer is contained in the Layers of this Node
- L44 _public function_ `const TArray<UDMXMVRLayerNode*>& GetLayerNodes() const` — Returns the Layers of this Node
- L49 _private member_ `TArray<TObjectPtr<UDMXMVRLayerNode>> LayerNodes;` — `UPROPERTY()` — A[n array of] layer representation[s].

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRParametricObjectNodeBase.h` (Public)


#### class `UDMXMVRParametricObjectNodeBase`  
`class UDMXMVRParametricObjectNodeBase : public UObject`  
_L21-58_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: UE specific: The base class for all Children in a Child List Node, whereas the standard refers to them as 'Parametric Objects'.
- L28 _public prototype_ `UDMXMVRParametricObjectNodeBase();` — Constructor
- L31 _public prototype_ `virtual void CreateXmlNodeInParent(FXmlNode& ParentNode) const PURE_VIRTUAL(UDMXMVRParametricObjectNodeBase::CreateXmlNodeInParent, return;);` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L34 _public prototype_ `UDMXMVRLayerNode* GetLayer();` — Returns the Layer this Node resides in
- L37 _public prototype_ `const UDMXMVRLayerNode* GetLayer() const;` — Returns the Layer this Node resides in
- L40 _public prototype_ `UDMXMVRGroupObjectNode* GetGroup();` — Returns the Group this Node resides in, or null if not in a Group
- L43 _public prototype_ `const UDMXMVRGroupObjectNode* GetGroup() const;` — Returns the Group this Node resides in, or null if not in a Group
- L46 _public prototype_ `FTransform GetTransformAbsolute() const;` — Gets the Transform in the absolute coordinate system
- L49 _public prototype_ `void SetTransformAbsolute(FTransform NewTransform);` — Sets the Transform in the absolute coordinate system
- L53 _public member_ `FGuid UUID;` — `UPROPERTY()` — The unique identifier of the object.
- L57 _public member_ `FDMXOptionalTransform Matrix;` — `UPROPERTY(VisibleAnywhere, Category = "DMX")` — The location of the object inside the parent coordinate system.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRRootNode.h` (Public)


#### class `UDMXMVRRootNode`  
`class UDMXMVRRootNode : public UObject`  
_L25-67_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The root node of an MVR General Scene Description as typically held in an MVR's GeneralSceneDescription.xml. UE specific: Note, while properties follow the standard closely, only children relevant to the Engine are implemented.
- L32 _public prototype_ `UDMXMVRRootNode();` — Constructor
- L39 _public prototype_ `[[nodiscard]] bool InitializeFromGeneralSceneDescriptionXml(const TSharedRef<FXmlFile>& GeneralSceneDescriptionXml);` — Initializes the Object and its children from a General Scene Description Xml File. Does not merge, clears previous entries. Returns false if not a valid MVR General Scene Description Xml
- L42 _public prototype_ `TSharedPtr<FXmlFile> CreateXmlFile();` — Creates a DMX Xml Node as per MVR standard, returns nullptr if the Xml File cannot be created.
- L45 _public prototype_ `void GetFixtureNodes(TArray<UDMXMVRFixtureNode*>& OutFixtureNodes) const;` — Returns the Fixture Nodes contained in this Layer. Note, does not clear the array.
- L48 _public prototype_ `UDMXMVRChildListNode& GetOrCreateFirstChildListNode();` — Returns the first Child List Node in the Scene
- L51 _public prototype_ `TObjectPtr<UDMXMVRParametricObjectNodeBase>* FindParametricObjectNodeByUUID(const FGuid& UUID) const;` — Returns a pointer ot the Parametric Object Node that corresponds to the UUID, or nullptr if there is no corresponding Parametric Object Node
- L54 _public prototype_ `bool RemoveParametricObjectNode(UDMXMVRParametricObjectNodeBase* ParametricObjectNode);` — Removes the Parametric Object Node from the General Scene Description. Returns true if the Node was removed.
- L57 _public function_ `UDMXMVRSceneNode* GetSceneNode() const` — Returns the node that contains information about the mvr scene
- L62 _private member_ `TObjectPtr<UDMXMVRUserDataNode> UserDataNode;` — `UPROPERTY()` — This node contains a collection of user data nodes defined and used by provider applications if required.
- L66 _private member_ `TObjectPtr<UDMXMVRSceneNode> SceneNode;` — `UPROPERTY()` — This node contains information about the scene.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRSceneNode.h` (Public)


#### class `UDMXMVRSceneNode`  
`class UDMXMVRSceneNode : public UObject`  
_L20-42_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This node contains information about the scene. UE Specific: Note, while properties follow the standard closely, only properties relevant to the Engine are implemented.
- L27 _public prototype_ `UDMXMVRSceneNode();` — Constructor
- L30 _public prototype_ `void InitializeFromSceneXmlNode(const FXmlNode& SceneXmlNode);` — Initializes the Scene Node andd its Children from a Scene Xml Node. Does not merge, clears previous entries.
- L33 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L36 _public function_ `UDMXMVRLayersNode* GetLayersNode() const` — Returns the node that defines a list of layers inside the scene. The layer is a container of graphical objects defining a local coordinate system.
- L41 _private member_ `TObjectPtr<UDMXMVRLayersNode> LayersNode;` — `UPROPERTY()` — This node defines a list of layers inside the scene. The layer is a container of graphical objects defining a local coordinate system.

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRUnrealEngineDataNode.h` (Public)


#### class `UDMXMVRUnrealEngineDataNode`  
`class UDMXMVRUnrealEngineDataNode : public UObject`  
_L17-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This node contains a collection of data specified by the provider application. UE sepecific: Used to add UE specific meta data
- L24 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L27 _public member_ `static constexpr TCHAR ProviderNameUnrealEngine[] = TEXT("Unr` — The Provider Name when the Data node is provided by Unreal Engine

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/MVR/Types/DMXMVRUserDataNode.h` (Public)


#### class `UDMXMVRUserDataNode`  
`class UDMXMVRUserDataNode : public UObject`  
_L17-33_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This node contains a collection of user data nodes defined and used by provider applications if required.
- L24 _public prototype_ `UDMXMVRUserDataNode();` — Constructor
- L27 _public prototype_ `void CreateXmlNodeInParent(FXmlNode& ParentNode) const;` — Creates a DMX Xml Node as per MVR standard in parent, or logs warnings if no compliant Node can be created.
- L32 _private member_ `TObjectPtr<UDMXMVRUnrealEngineDataNode> UnrealEngineDataNode;` — `UPROPERTY()` — UE Specific: The UE's proprietary data node

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Modulators/DMXModulator.h` (Public)


#### class `UDMXModulator`  
`class UDMXModulator : public UObject`  
_L20-34_
- reflection: `UCLASS(BlueprintType, Blueprintable, EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Base class for custom modulators. Override Modulate and ModulateMatrix functions in the blueprints to implement functionality. Input maps hold all attribute values of the patch. Output Maps can be freely defined, but Attributes not present in the patch will be ignored.
- L28 _public prototype_ `void Modulate(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues);` — `UFUNCTION(BlueprintNativeEvent, Category = "DMX")`
- L29 _public function_ `virtual void Modulate_Implementation(UDMXEntityFixturePatch* FixturePatch, const TMap<FDMXAttributeName, float>& InNormalizedAttributeValues, TMap<FDMXAttributeName, float>& OutNormalizedAttributeValues)`
- L32 _public prototype_ `void ModulateMatrix(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues);` — `UFUNCTION(BlueprintNativeEvent, Category = "DMX")`
- L33 _public function_ `virtual void ModulateMatrix_Implementation(UDMXEntityFixturePatch* FixturePatch, const TArray<FDMXNormalizedAttributeValueMap>& InNormalizedMatrixAttributeValues, TArray<FDMXNormalizedAttributeValueMap>& OutNormalizedMatrixAttributeValues)`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Sequencer/MovieSceneDMXLibrarySection.h` (Public)


#### struct `FDMXFixtureFunctionChannel`  
`struct FDMXFixtureFunctionChannel`  
_L16-48_
- reflection: `USTRUCT()`
- L22 _public member_ `FName AttributeName = NAME_None;` — `UPROPERTY()` — Attribute Name of the function
- L26 _public member_ `FMovieSceneFloatChannel Channel;` — `UPROPERTY()` — Function animation curve.
- L33 _public member_ `FIntPoint CellCoordinate = FIntPoint(-1, -1);` — `UPROPERTY()` — For Cell Functions the coordinate of the cell For common functions -1.
- L37 _public member_ `uint32 DefaultValue = 0;` — `UPROPERTY()` — Default value to use when this Function is disabled in the track.
- L44 _public member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether or not to display this Function in the Patch's group If false, the Function's default value is sent to DMX protocols.
- L47 _public function_ `bool IsCellFunction() const` — True if the function is a cell function

#### struct `FDMXFixturePatchChannel`  
`struct FDMXFixturePatchChannel`  
_L51-78_
- reflection: `USTRUCT()`
- L57 _public member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY()` — The outer library of the channel
- L61 _public member_ `FDMXEntityFixturePatchRef Reference;` — `UPROPERTY()` — Points to the Fixture Patch
- L65 _public member_ `TArray<FDMXFixtureFunctionChannel> FunctionChannels;` — `UPROPERTY()` — Fixture function float channels
- L72 _public member_ `int32 ActiveMode = INDEX_NONE;` — `UPROPERTY()` — Allows Sequencer to animate the fixture using a mode and not have it break simply by the user changing the active mode in the DMX Library.
- L74 _public prototype_ `void SetFixturePatch(UDMXEntityFixturePatch* InPatch);`
- L77 _public prototype_ `void UpdateNumberOfChannels(bool bResetDefaultValues = false);` — Makes sure the number of Float Channels matches the number of functions in the selected Patch mode

#### struct `FDMXCachedFunctionChannelInfo`  
`struct FDMXCachedFunctionChannelInfo`  
_L93-139_
- desc: Cached info of fixture function channels. Exists to streamline performance. Without this class, data for all tracks would have to be prepared each tick, leading to significant overhead. Besides caching values, the instance deduces how the track should be evaluated: 1. bNeedsEvaluation - These channels need update each tick 2. bNeedsInitialization - These channels need update only in the first tick! 3. Other tracks - These do not need update ever. Profiled, issues were apparent in 4.26 with a great number of sequencer channels (attributes).
- L95 _public prototype_ `FDMXCachedFunctionChannelInfo() = delete;`
- L97 _public prototype_ `FDMXCachedFunctionChannelInfo(const TArray<FDMXFixturePatchChannel>& FixturePatchChannels, int32 InPatchChannelIndex, int32 InFunctionChannelIndex);`
- L100 _public prototype_ `const FDMXFixtureFunctionChannel* TryGetFunctionChannel(const TArray<FDMXFixturePatchChannel>& FixturePatchChannels) const;` — Returns the function channel, or nullptr if it got moved or deleted
- L102 _public function_ `bool NeedsInitialization() const`
- L104 _public function_ `bool NeedsEvaluation() const`
- L106 _public function_ `int32 GetUniverseID() const`
- L108 _public function_ `int32 GetStartingChannel() const`
- L110 _public function_ `EDMXFixtureSignalFormat GetSignalFormat() const`
- L112 _public function_ `bool ShouldUseLSBMode() const`
- L119 _private prototype_ `void GetMatrixCellChannelsAbsoluteNoSorting(UDMXEntityFixturePatch* FixturePatch, const FIntPoint& CellCoordinate, TMap<FName, int32>& OutAttributeToAbsoluteChannelMap) const;` — Gets the cell channels, but unlike subsystem's methods doesn't sort channels by pixel mapping distribution. If the cell coordinate would be sorted here, it would be sorted on receive again causing doubly sorting.
- L121 _private member_ `bool bNeedsInitialization;`
- L122 _private member_ `bool bNeedsEvaluation;`
- L124 _private member_ `int32 PatchChannelIndex;`
- L126 _private member_ `int32 FunctionChannelIndex;`
- L128 _private member_ `int32 NumFunctionChannels;`
- L130 _private member_ `FName AttributeName;`
- L132 _private member_ `int32 UniverseID;`
- L134 _private member_ `int32 StartingChannel;`
- L136 _private member_ `EDMXFixtureSignalFormat SignalFormat;`
- L138 _private member_ `bool bLSBMode;`

#### class `UMovieSceneDMXLibrarySection`  
`class UMovieSceneDMXLibrarySection : public UMovieSceneSection`  
_L143-280_
- reflection: `UCLASS()`
- inherits: `UMovieSceneSection`
- desc: A DMX Fixture Patch section
- L150 _public prototype_ `UMovieSceneDMXLibrarySection();`
- L154 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L155 _public prototype_ `virtual void PostLoad() override;`
- L156 _public prototype_ `virtual void PostEditImport() override;`
- L158 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L163 _public prototype_ `void RefreshChannels();` — Refreshes the channels. Useful e.g. when underlying DMX Library changes
- L173 _public member_ `bool bUseNormalizedValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movie Scene")` — If true, all values are interpreted as normalized values (0.0 to 1.0) and are mapped to the actual value range of a patch automatically. If false, values are interpreted as absolute values, depending on the data type of a patch: 0-255 for 8bit, 0-65'536 for 16bit, 0-16'777'215 for 24bit. 32bit is not fully supported in this mode.
- L177 _public prototype_ `void AddFixturePatch(UDMXEntityFixturePatch* InPatch);` — `UFUNCTION(BlueprintCallable, Category = "Movie Scene")` — Adds a single patch to the section
- L181 _public prototype_ `void AddFixturePatches(const TArray<FDMXEntityFixturePatchRef>& InFixturePatchRefs);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds all patches to the secion
- L185 _public prototype_ `void RemoveFixturePatch(UDMXEntityFixturePatch* InPatch);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Remove all Functions of a Fixture Patch
- L188 _public prototype_ `void RemoveFixturePatch(const FName& InPatchName);` — Remove all Functions of a Fixture Patch, searching it by name
- L192 _public prototype_ `bool ContainsFixturePatch(UDMXEntityFixturePatch* InPatch) const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Check if this Section animates a Fixture Patch's Functions
- L196 _public prototype_ `void SetFixturePatchActiveMode(UDMXEntityFixturePatch* InPatch, int32 InActiveMode);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Sets the active mode for a Fixture Patch
- L203 _public prototype_ `void ToggleFixturePatchChannel(UDMXEntityFixturePatch* InPatch, int32 InChannelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Toggle the visibility and evaluation of a Fixture Patch's Function. When invisible, the Function won't send its data to DMX Protocol.
- L210 _public prototype_ `void ToggleFixturePatchChannel(const FName& InPatchName, const FName& InChannelName);` — Toggle the visibility and evaluation of a Fixture Patch's Function searching both the Patch and Function by name. When invisible, the Function won't send its data to DMX Protocol.
- L214 _public prototype_ `bool GetFixturePatchChannelEnabled(UDMXEntityFixturePatch* InPatch, int32 InChannelIndex) const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Returns whether a Fixture Patch's Function curve channel is currently enabled
- L218 _public prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatches() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Get a list of the Fixture Patches being animated by this Section
- L221 _public prototype_ `FDMXFixturePatchChannel* GetPatchChannel(UDMXEntityFixturePatch* Patch);` — Returns the channel for specified patch or nullptr if the patch is not in use
- L225 _public function_ `int32 GetNumPatches() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Get the list of animated Fixture Patches and their curve channels
- L227 _public function_ `const TArray<FDMXFixturePatchChannel>& GetFixturePatchChannels() const`
- L229 _public function_ `TArray<FDMXFixturePatchChannel>& GetMutableFixturePatchChannels()`
- L235 _public function_ `void SetIsRecording(bool bNewState)` — Used only by the Take Recorder to prevent Track evaluation from sending DMX data while recording it.
- L241 _public function_ `bool GetIsRecording() const` — Checked in evaluation to prevent sending DMX data while recording it with the Take Recorder.
- L244 _public prototype_ `void RebuildPlaybackCache() const;` — Precaches data for playback
- L247 _public prototype_ `void EvaluateAndSendDMX(const FFrameTime& InFrameTime) const;` — Evaluates DMX at given fame time and sends it
- L251 _protected prototype_ `void SendDMXForChannelsToInitialize() const;` — Sends DMX for channels that need initialization (one time evaluation) only
- L254 _protected prototype_ `void UpdateChannelProxy(bool bResetDefaultChannelValues = false);` — Update the displayed Patches and Function channels in the section
- L258 _protected member_ `TArray<FDMXFixturePatchChannel> FixturePatchChannels;` — `UPROPERTY()` — The Fixture Patches being controlled by this section and their respective chosen mode
- L264 _protected member_ `bool bIsRecording;` — When recording DMX data into this track, this is set to true to prevent track evaluation from sending data to DMX simultaneously.
- L270 _private member_ `mutable bool bNeedsSendChannelsToInitialize;` — True if the cache was updated
- L273 _private member_ `mutable TArray<FDMXCachedFunctionChannelInfo> CachedChannelsToInitialize;` — Cached channel info for functions that need initialization (one time evaluation) only
- L276 _private member_ `mutable TArray<FDMXCachedFunctionChannelInfo> CachedChannelsToEvaluate;` — Cached channel info for functions that need continous evaluation
- L279 _private member_ `mutable TSet<FDMXOutputPortSharedRef> CachedOutputPorts;` — The output ports which should be used during playback

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Sequencer/MovieSceneDMXLibraryTemplate.h` (Public)


#### struct `FMovieSceneDMXLibraryTemplate`  
`struct FMovieSceneDMXLibraryTemplate : public FMovieSceneEvalTemplate`  
_L20-41_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- desc: Template that performs evaluation of Fixture Patch sections
- L25 _public function_ `FMovieSceneDMXLibraryTemplate() : Section(nullptr)`
- L26 _public prototype_ `FMovieSceneDMXLibraryTemplate(const UMovieSceneDMXLibrarySection& InSection);`
- L29 _private function_ `virtual void SetupOverrides() override`
- L34 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L35 _private prototype_ `virtual void Setup(FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) const override;`
- L36 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L40 _private member_ `TObjectPtr<const UMovieSceneDMXLibrarySection> Section;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Sequencer/MovieSceneDMXLibraryTrack.h` (Public)


#### class `UMovieSceneDMXLibraryTrack`  
`class UMovieSceneDMXLibraryTrack : public UMovieSceneNameableTrack, public IMovieSceneTrackTemplateProducer`  
_L17-51_
- reflection: `UCLASS()`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles manipulation of DMX Libraries in a movie scene.
- L23 _public function_ `UDMXLibrary* GetDMXLibrary() const`
- L24 _public prototype_ `void SetDMXLibrary(UDMXLibrary* InLibrary);`
- L27 _public prototype_ `UMovieSceneDMXLibraryTrack();`
- L30 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L31 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L32 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L33 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L34 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L35 _public prototype_ `virtual bool IsEmpty() const override;`
- L36 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L37 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L38 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L39 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L40 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L46 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The sections owned by this track .
- L50 _private member_ `TObjectPtr<UDMXLibrary> Library;` — `UPROPERTY()` — The DMX Library to manipulate
