# Plugins / DMXGDTF

- module root: `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF`
- headers: 81; symbols: 1250
- symbol kinds: class=79, delegate=1, enum=18, enumerator=118, function=126, member=366, namespace=247, prototype=289, struct=4, typedef=2
- PrivateDependencyModuleNames: DMXZip, Engine, XmlParser
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Private/DMXGDTFLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXGDTF, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXGDTF, Log, All);`

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Private/Serialization/DMXGDTFNodeInitializer.h` (Private)


#### class `UE::DMX::GDTF::FDMXGDTFNodeInitializer`  
`template<typename NodeType> class FDMXGDTFNodeInitializer : public FNoncopyable`  
_L28-510_
- inherits: `FNoncopyable`
- desc: Initializer for FDMXGDTF nodes. To parse non-trivial types GetAttribute accepts transforms and predicates.
- L32 _public prototype_ `FDMXGDTFNodeInitializer() = delete;`
- L33 _public function_ `FDMXGDTFNodeInitializer(TSharedRef<NodeType> InUserObject, const FXmlNode& InXmlNode) : UserObject(InUserObject) , XmlNode(InXmlNode)`
- L42 _public function_ `template <typename AttributeType> const FDMXGDTFNodeInitializer& GetAttribute(const TCHAR* InAttribute, AttributeType& OutValue) const` — Initializes an attribute
- L120 _public function_ `template <typename AttributeType, typename UserObject, typename TransformType, typename... Args> const FDMXGDTFNodeInitializer& GetAttribute(const TCHAR* InAttribute, AttributeType& OutValue, TransformType Transform, Args...args) const` — Initializes an attribute, using a static for transformation.
- L135 _public function_ `template <typename AttributeType, typename UserObject, typename TransformType, typename... Args> const FDMXGDTFNodeInitializer& GetAttribute(const TCHAR* InAttribute, AttributeType& OutValue, const UserObject* Object, TransformType Transform, Args...args) const` — Initializes an attribute, using a member function for transformation.
- L153 _public function_ `template <typename AttributeType, typename PredicateType> const FDMXGDTFNodeInitializer& GetAttribute(const TCHAR* InAttribute, AttributeType& OutValue, PredicateType Predicate) const` — Initializes an attribute, using a predicate for transformation.
- L165 _public function_ `template <typename ChildType, typename = std::enable_if_t<std::is_base_of_v<FDMXGDTFNode, ChildType>>> const FDMXGDTFNodeInitializer& CreateChildCollection(const TCHAR* InCollectTag, const TCHAR* InChildTag, TArray<TSharedPtr<ChildType>>& OutChildren) const` — Creates a collection of children nodes, whereas a collection is an xml node that contains these children.
- L185 _public function_ `template <typename ChildType, typename = std::enable_if_t<std::is_base_of_v<FDMXGDTFNode, ChildType>>> const FDMXGDTFNodeInitializer& CreateChildren(const TCHAR* InChildTag, TArray<TSharedPtr<ChildType>>& OutChildren) const` — Creates child nodes for matching tag in OutChildren array.
- L205 _public function_ `template <typename ChildType, typename = std::enable_if_t<std::is_base_of_v<FDMXGDTFNode, ChildType>>> const FDMXGDTFNodeInitializer& CreateOptionalChild(const TCHAR* InChildTag, TSharedPtr<ChildType>& OutChild) const` — Creates a single child node for matching tag in OutChild. Logs a warning if more than one child with this tag are found.
- L234 _public function_ `template <typename ChildType, typename = std::enable_if_t<std::is_base_of_v<FDMXGDTFNode, ChildType>>> const FDMXGDTFNodeInitializer& CreateRequiredChild(const TCHAR* InChildTag, TSharedPtr<ChildType>& OutChild) const` — Creates a single child node for matching tag in OutChild. Creates the child even if the tag does not exist. Logs a warning if none or more than one child with this tag are found.
- L253 _private function_ `template <typename ChildType> TSharedRef<ChildType> ConstructChild(const FXmlNode* InXmlNode) const` — Constructs a node
- L279 _private function_ `template <typename EnumType> bool ParseUEnum(const FString& GDTFString, EnumType& OutEnum) const` — Parses a GDTF string as Enum
- L293 _private function_ `FVector2D ParseVector2D(const FString& GDTFString) const` — Parses a GDTF string as vector2
- L322 _private function_ `FVector ParseVector(const FString& GDTFString) const` — Parses a GDTF string as vector3
- L354 _private function_ `FDMXGDTFColorCIE1931xyY ParseColorCIE(const FString& GDTFString) const` — Parses a GDTF string as color CIE
- L384 _private function_ `FTransform ParseTransform(const FString& GDTFString) const` — Parses a GDTF string as transform
- L410 _private function_ `FDMXGDTFDMXAddress ParseDMXAddress(const FString& GDTFString) const` — Parses a GDTF string as DMX address
- L450 _private function_ `bool ParseGDTFMatrix(const FString& InGDTFString, FMatrix& OutMatrix) const` — Helper to parse 3x3 and 4x4 matrices
- L506 _private member_ `TSharedRef<NodeType> UserObject;` — The object that uses this parser
- L509 _private member_ `const FXmlNode& XmlNode;` — The XML node that needs to be parsed

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DMX` (scope `UE`)
- L20 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L171 _function_ `` (scope `UE::DMX::GDTF::FDMXGDTFNodeInitializer::CreateChildCollection`)
- L189 _function_ `` (scope `UE::DMX::GDTF::FDMXGDTFNodeInitializer::CreateChildren`)
- L218 _function_ `` (scope `UE::DMX::GDTF::FDMXGDTFNodeInitializer::CreateOptionalChild`)
- L469 _function_ `` (scope `UE::DMX::GDTF::FDMXGDTFNodeInitializer::ParseGDTFMatrix`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Private/Serialization/DMXGDTFXmlNodeBuilder.h` (Private)


#### enum `UE::DMX::GDTF::EDMXGDTFMatrixType`  
`enum class EDMXGDTFMatrixType`  
_L21-25_
- L23 _public enumerator_ `Matrix3x3`
- L24 _public enumerator_ `Matrix4x4`

#### class `UE::DMX::GDTF::FDMXGDTFXmlNodeBuilder`  
`class FDMXGDTFXmlNodeBuilder`  
_L27-217_
- L37 _public prototype_ `FDMXGDTFXmlNodeBuilder(FXmlNode& InOutParent, const FDMXGDTFNode& InGDTFNode, FXmlNode* AppendToNode = nullptr);` — Builds a GDTF XML node from an Unreal DMXGDTF node. @param InOutParent		The parent XML node the new node is built in @param InGDTFNode		The DMX GDTF node that from which the XML node is created @param AppendToNode		(optional) If not nullptr, appends to an existing XML node
- L38 _public prototype_ `~FDMXGDTFXmlNodeBuilder();`
- L41 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const TCHAR* CharArray, const TOptional<FString> OptionalDefault = TOptional<FString>());` — Converts a char array to an attribute. If a default value is provided, only sets the attribute if the char array differs from the default value
- L44 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FString& String, const TOptional<FString> OptionalDefault = TOptional<FString>());` — Converts a string to an attribute. If a default value is provided, only sets the attribute if the string differs from the default value
- L47 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FName& Name, const TOptional<FName> OptionalDefault = TOptional<FName>());` — Converts a name to an attribute. If a default value is provided, only sets the attribute if the name differs from the default value
- L50 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const int32 Integer, const TOptional<int32> OptionalDefault = TOptional<int32>());` — Converts an integer to an attribute. If a default value is provided, only sets the attribute if the integer differs from the default value
- L53 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const uint32 UnsignedInteger, const TOptional<uint32> OptionalDefault = TOptional<uint32>());` — Converts an unsigned integer to an attribute. If a default value is provided, only sets the attribute if the unsigned integer differs from the default value
- L56 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const float Float, const TOptional<float> OptionalDefault = TOptional<float>());` — Converts a float to an attribute. If a default value is provided, only sets the attribute if the float differs from the default value
- L59 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FGuid& Guid, const TOptional<FGuid> OptionalDefault = TOptional<FGuid>());` — Converts a guid to an attribute. If a default value is provided, only sets the attribute if the guid differs from the default value
- L62 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FVector2D& Vector2, const TOptional<FVector2D> OptionalDefault = TOptional<FVector2D>());` — Converts a vector2 to an attribute. If a default value is provided, only sets the attribute if the vector2 differs from the default value
- L65 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FVector& Vector3, const TOptional<FVector> OptionalDefault = TOptional<FVector>());` — Converts a vector3 to an attribute. If a default value is provided, only sets the attribute if the vector3 differs from the default value
- L72 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FTransform& Transform, EDMXGDTFMatrixType MatrixType, const TOptional<FTransform> OptionalDefault = TOptional<FTransform>());` — Converts a transform to an attribute. If a default value is provided, only sets the attribute if the transform differs from the default value. This setter requires to set if a 3x3 or 4x4 matrix should be written.
- L75 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FDMXGDTFColorCIE1931xyY& ColorCIE, const TOptional<FDMXGDTFColorCIE1931xyY> OptionalDefault = TOptional<FDMXGDTFColorCIE1931xyY>());` — Converts a color to an attribute. If a default value is provided, only sets the attribute if the color differs from the default value
- L78 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const TArray<FDMXGDTFColorCIE1931xyY>& ColorArray);` — Converts an array of colors to an attribute. If a default value is provided, only sets the attribute if the array of colors differs from the default value
- L81 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FDMXGDTFDMXValue& GDTFValue, const TOptional<FDMXGDTFDMXValue> OptionalDefault = TOptional<FDMXGDTFDMXValue>());` — Converts a GDTF value to an attribute. If a default value is provided, only sets the attribute if the GDTF value differs from the default value
- L84 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FDMXGDTFDMXAddress& GDTFAddress, const TOptional<FDMXGDTFDMXAddress> OptionalDefault = TOptional<FDMXGDTFDMXAddress>());` — Converts a GDTF address to an attribute. If a default value is provided, only sets the attribute if the GDTF address differs from the default value
- L87 _public prototype_ `FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const FDateTime& DateTime, const TOptional<FDateTime> OptionalDefault = TOptional<FDateTime>());` — Converts date time to an attribute. If a default value is provided, only sets the attribute if the date time differs from the default value
- L91 _public function_ `template <typename IntegralType> requires std::is_integral_v<IntegralType> && std::negation_v<std::is_enum<IntegralType>> FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const TArray<IntegralType> ValueArray, const TOptional<FString> OptionalDefault = TOptional<FString>())` — Converts an array of integer to an attribute. If a default value is provided, only sets the attribute if the array of integer differs from the default value
- L119 _public function_ `template <typename EnumType> requires std::is_enum_v<EnumType> && std::is_invocable_v<decltype(&StaticEnum<EnumType>)> && std::negation_v<std::is_integral<EnumType>> FDMXGDTFXmlNodeBuilder& SetAttribute(const FString& AttributeName, const EnumType& EnumValue, const TOptional<EnumType> OptionalDefault = TOptional<EnumType>())` — Converts an enum to an attribute. Note the enum has to be a UEnum value If a default value is provided, only sets the enum if the vector differs from the default value
- L142 _public function_ `template <typename NodeType> requires std::is_base_of_v<FDMXGDTFNode, NodeType> FDMXGDTFXmlNodeBuilder& AppendRequiredChild(const TCHAR* ChildTag, const TSharedPtr<NodeType>& ChildNode)`
- L161 _public function_ `template <typename NodeType> requires std::is_base_of_v<FDMXGDTFNode, NodeType> FDMXGDTFXmlNodeBuilder& AppendOptionalChild(const TCHAR* ChildTag, const TSharedPtr<NodeType>& ChildNode)`
- L174 _public function_ `template <typename NodeType> requires std::is_base_of_v<FDMXGDTFNode, NodeType> FDMXGDTFXmlNodeBuilder& AppendChildren(const TCHAR* ChildTag, const TArray<TSharedPtr<NodeType>>& ChildNodes)`
- L190 _public function_ `template <typename NodeType> requires std::is_base_of_v<FDMXGDTFNode, NodeType> FDMXGDTFXmlNodeBuilder& AppendChildCollection(const TCHAR* CollectName, const TCHAR* ChildTag, const TArray<TSharedPtr<NodeType>>& ChildNodes)`
- L206 _public prototype_ `FXmlNode* GetIntermediateXmlNode() const;` — Returns the intermediate XML node. Note the node will exist, but will not yet contain the XML data
- L210 _private member_ `TArray<FXmlAttribute> Attributes;` — Array of attributes that are pending to be written
- L213 _private member_ `FXmlNode& Parent;` — The parent node in which this node is built
- L216 _private member_ `FXmlNode* NewXmlNode = nullptr;` — The XML node that is being built

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)
- L16 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/DMXGDTF.h` (Public)


#### class `UDMXGDTF`  
`class UDMXGDTF : public UObject`  
_L23-47_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The implementation of the GDTF standard in Unreal Engine. The implementation uses unreal engine types, left-handed z-up coordinate system, centimeters, column-major order matrices. .
- L28 _private typedef_ `using FDMXGDTFDescription = UE::DMX::GDTF::FDMXGDTFDescription;`
- L29 _private typedef_ `using FDMXGDTFFixtureType = UE::DMX::GDTF::FDMXGDTFFixtureType;`
- L33 _public prototype_ `void InitializeFromData(const TArray64<uint8>& Data);` — Initializes this object from .gdtf file data. Returns true on success.
- L36 _public prototype_ `void InitializeFromFixtureType(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);` — Initializes this object from a GDTF fixture type.
- L39 _public prototype_ `TSharedPtr<FXmlFile> ExportAsXml() const;` — Exports an XML file. Returns the XML file or nullptr if no XML file could be generated
- L42 _public function_ `TSharedPtr<FDMXGDTFDescription> GetDescription() const` — Returns the GDTF Description or nullptr if no valid description exists.
- L46 _private member_ `TSharedPtr<FDMXGDTFDescription> Description;` — The GDTF description

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/DMXGDTFColorCIE1931xyY.h` (Public)


#### struct `FDMXGDTFColorCIE1931xyY`  
`struct FDMXGDTFColorCIE1931xyY`  
_L9-44_
- reflection: `USTRUCT(BlueprintType, Category = "DMX")`
- desc: xyY color representation in the CIE 1931 color space, as typically used in GDTF and MVR
- L13 _public prototype_ `FString ToString() const;`
- L17 _public member_ `float X = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Chromaticity coordinate x
- L21 _public member_ `float Y = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Chromaticity coordinate y
- L25 _public member_ `float YY = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX", Meta = (DisplayName = "Luminance"))` — Luminance

#### Free symbols / members of external scopes

- L27 _function_ `friend bool operator==(const FDMXGDTFColorCIE1931xyY& A, const FDMXGDTFColorCIE1931xyY& B)`
- L32 _function_ `friend bool operator!=(const FDMXGDTFColorCIE1931xyY& A, const FDMXGDTFColorCIE1931xyY& B)`
- L37 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXGDTFColorCIE1931xyY& ColorCIE1931)`

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFActivationGroup.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFActivationGroup`  
`class FDMXGDTFActivationGroup : public FDMXGDTFNode`  
_L12-29_
- inherits: `FDMXGDTFNode`
- desc: This section defines the activation group Attributes (XML node <ActivationGroup>).
- L16 _public prototype_ `FDMXGDTFActivationGroup(const TSharedRef<FDMXGDTFAttributeDefinitions>& InAttributeDefinitions);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `FName Name;` — The unique name of the activation group.
- L28 _public member_ `const TWeakPtr<FDMXGDTFAttributeDefinitions> OuterAttributeDefinitions;` — The outer attribute definitions

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFAttribute.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFAttribute`  
`class FDMXGDTFAttribute : public FDMXGDTFNode`  
_L19-66_
- inherits: `FDMXGDTFNode`
- L23 _public prototype_ `FDMXGDTFAttribute(const TSharedRef<FDMXGDTFAttributeDefinitions>& InAttributeDefinitions);`
- L26 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L27 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L28 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `FName Name;` — The unique name of the attribute.
- L35 _public member_ `FString Pretty;` — The pretty name of the attribute.
- L38 _public member_ `FString ActivationGroup;` — (Optional) Link to the activation group.
- L41 _public member_ `FString Feature;` — (Optional) Link to the corresponding feature.
- L44 _public member_ `FString MainAttribute;` — (Optional) Link to the main attribute.
- L47 _public member_ `EDMXGDTFPhysicalUnit PhysicalUnit;` — Physical Unit
- L50 _public member_ `FDMXGDTFColorCIE1931xyY Color;` — (Optional) Defines the color for the attribute.
- L53 _public member_ `TArray<TSharedPtr<FDMXGDTFSubphysicalUnit>> SubpyhsicalUnitArray;` — As children the attribute node has a list of a subphysical units.
- L56 _public member_ `const TWeakPtr<FDMXGDTFAttributeDefinitions> OuterAttributeDefinitions;` — The outer attribute definitions
- L59 _public prototype_ `TSharedPtr<FDMXGDTFActivationGroup> ResolveActivationGroup() const;` — Resolves the linked activation group. Returns the activation group or nullptr if no activation group is linked
- L62 _public prototype_ `TSharedPtr<FDMXGDTFFeature> ResolveFeature() const;` — Resolves the linked feature. Returns the feature or nullptr if no feature is linked
- L65 _public prototype_ `TSharedPtr<FDMXGDTFAttribute> ResolveMainAttribute() const;` — Resolves the linked main attribute. Returns the main attribute or nullptr if no main attribute is linked

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L12 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFAttributeDefinitions.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFAttributeDefinitions`  
`class FDMXGDTFAttributeDefinitions : public FDMXGDTFNode`  
_L16-60_
- inherits: `FDMXGDTFNode`
- desc: This section defines the attribute definition collect for the Fixture Type Attributes.
- L20 _public prototype_ `FDMXGDTFAttributeDefinitions(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& InXmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L33 _public member_ `TArray<TSharedPtr<FDMXGDTFActivationGroup>> ActivationGroups;` — (Optional) This section defines groups of Fixture Type Attributes that are intended to be used together. Example: Usually Pan and Tilt are Fixture Type Attributes that shall be activated together to be able to store and recreate any position. The current activation groups node does not have any XML attributes (XML node <ActivationGroups>). As children it can have a list of a activation group.
- L44 _public member_ `TArray<TSharedPtr<FDMXGDTFFeatureGroup>> FeatureGroups;` — (Optional) This section defines the logical grouping of Fixture Type Attributes (XML node <FeatureGroups>). [For example, Gobo 1 and Gobo 2 are grouped in the feature Gobo of the feature group Gobo.] NOTE 1: A feature group can contain more than one logical control unit. A feature group Position shall contain PanTilt and XYZ as separate Feature. NOTE 2: Usually Pan and Tilt create a logical unit to enable position control, so they must be grouped in a Feature PanTilt.
- L47 _public member_ `TArray<TSharedPtr<FDMXGDTFAttribute>> Attributes;` — This section defines the Fixture Type Attributes (XML node <Attributes>). As children the attributes node has a list of a attributes.
- L50 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type
- L53 _public prototype_ `TSharedPtr<FDMXGDTFActivationGroup> FindActivationGroup(const FString& Name) const;` — Finds an activation group by name. Returns the activation group or nullptr if the activation group cannot be found
- L56 _public prototype_ `TSharedPtr<FDMXGDTFAttribute> FindAttribute(const FString& Name) const;` — Finds an attribute by name. Returns the attribute or nullptr if the attribute cannot be found
- L59 _public prototype_ `TSharedPtr<FDMXGDTFFeature> FindFeature(const FString& FeatureGroupName, const FString& FeatureName) const;` — Finds a feature by name. Returns the feature or nullptr if the feature cannot be found

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFFeature.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFeature`  
`class FDMXGDTFFeature : public FDMXGDTFNode`  
_L12-29_
- inherits: `FDMXGDTFNode`
- desc: This section defines the feature.
- L16 _public prototype_ `FDMXGDTFFeature(const TSharedRef<FDMXGDTFFeatureGroup>& InFeatureGroup);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `FName Name;` — The unique name of the feature.
- L28 _public member_ `const TWeakPtr<FDMXGDTFFeatureGroup> OuterFeatureGroup;` — The outer feature group

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFFeatureGroup.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFeatureGroup`  
`class FDMXGDTFFeatureGroup : public FDMXGDTFNode`  
_L13-36_
- inherits: `FDMXGDTFNode`
- desc: This section defines the feature group (XML node <FeatureGroup>).
- L17 _public prototype_ `FDMXGDTFFeatureGroup(const TSharedRef<FDMXGDTFAttributeDefinitions>& InAttributeDefinitions);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `FName Name;` — The unique name of the feature group.
- L29 _public member_ `FString Pretty;` — The pretty name of the feature group.
- L32 _public member_ `TArray<TSharedPtr<FDMXGDTFFeature>> FeatureArray;` — As children the feature group has a list of a feature.
- L35 _public member_ `const TWeakPtr<FDMXGDTFAttributeDefinitions> OuterAttributeDefinitions;` — The outer attribute definitions

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFPhysicalUnit.h` (Public)


#### enum `EDMXGDTFPhysicalUnit`  
`enum class EDMXGDTFPhysicalUnit : uint8`  
_L17-44_
- reflection: `UENUM(BlueprintType)`
- desc: Attribute Pyhsical Unit. The currently defined unit values are: “None”, “Percent”, “Length” (m), “Mass” (kg), “Time” (s), “Temperature” (K), “LuminousIntensity”(cd), “Angle” (degree), “Force” (N), “Frequency” (Hz), “Current” (A), “Voltage” (V), “Power” (W), “Energy” (J), “Area” (m2), “Volume” (m3), “Speed” (m/s), “Acceleration” (m/s2), “AngularSpeed” (degree/s), “AngularAccc” (degree/s2), “WaveLength” (nm), “ColorComponent”. Default: “None”.
- L19 _public enumerator_ `None UMETA(DisplayName = "None")`
- L20 _public enumerator_ `Percent UMETA(DisplayName = "Percent")`
- L21 _public enumerator_ `Length UMETA(DisplayName = "Length")`
- L22 _public enumerator_ `Mass UMETA(DisplayName = "Mass (kg)")`
- L23 _public enumerator_ `Time UMETA(DisplayName = "Time (s)")`
- L24 _public enumerator_ `Temperature UMETA(DisplayName = "Temperature (K)")`
- L25 _public enumerator_ `LuminousIntensity UMETA(DisplayName = "LuminousIntensity (cd)")`
- L26 _public enumerator_ `Angle UMETA(DisplayName = "Angle (degree)")`
- L27 _public enumerator_ `Force UMETA(DisplayName = "Force (N)")`
- L28 _public enumerator_ `Frequency UMETA(DisplayName = "Frequency (Hz)")`
- L29 _public enumerator_ `Current UMETA(DisplayName = "Current (A)")`
- L30 _public enumerator_ `Voltage UMETA(DisplayName = "Voltage (V)")`
- L31 _public enumerator_ `Power UMETA(DisplayName = "Power (W)")`
- L32 _public enumerator_ `Energy UMETA(DisplayName = "Energy (J)")`
- L33 _public enumerator_ `Area UMETA(DisplayName = "Area (m2)")`
- L34 _public enumerator_ `Volume UMETA(DisplayName = "Volume (m3)")`
- L35 _public enumerator_ `Speed UMETA(DisplayName = "Speed (m/s)")`
- L36 _public enumerator_ `Acceleration UMETA(DisplayName = "Acceleration (m/s2)")`
- L37 _public enumerator_ `AngularSpeed UMETA(DisplayName = "AngularSpeed (degree/s)")`
- L38 _public enumerator_ `AngularAccc UMETA(DisplayName = "AngularAccc (degree/s2"), WaveLength UMETA(DisplayName = "WaveLength (nm)"), ColorComponent UMETA(DisplayName = "ColorComponent"), MaxEnumValue UMETA(Hidden) };`
- L39 _public enumerator_ `WaveLength UMETA(DisplayName = "WaveLength (nm)")`
- L40 _public enumerator_ `ColorComponent UMETA(DisplayName = "ColorComponent")`
- L43 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### Free symbols / members of external scopes

- L46 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFPhysicalUnit, EDMXGDTFPhysicalUnit::MaxEnumValue);`

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/AttributeDefinitions/DMXGDTFSubphysicalUnit.h` (Public)


#### enum `EDMXGDTFSubphysicalUnit`  
`enum class EDMXGDTFSubphysicalUnit : uint8`  
_L19-35_
- reflection: `UENUM(BlueprintType)`
- desc: Subphysical Unit Type. The currently defined values are : “PlacementOffset”, “Amplitude”, “AmplitudeMin”, “AmplitudeMax”, “Duration”, “DutyCycle”, “TimeOffset”, “MinimumOpening”, “Value”, “RatioHorizontal”, “RatioVertical”.
- L21 _public enumerator_ `PlacementOffset`
- L22 _public enumerator_ `Amplitude`
- L23 _public enumerator_ `AmplitudeMin`
- L24 _public enumerator_ `AmplitudeMax`
- L25 _public enumerator_ `Duration`
- L26 _public enumerator_ `DutyCycle`
- L27 _public enumerator_ `TimeOffset`
- L28 _public enumerator_ `MinimumOpening`
- L29 _public enumerator_ `Value`
- L30 _public enumerator_ `RatioHorizontal`
- L31 _public enumerator_ `RatioVertical`
- L34 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFSubphysicalUnit`  
`class FDMXGDTFSubphysicalUnit : public FDMXGDTFNode`  
_L44-70_
- inherits: `FDMXGDTFNode`
- L48 _public prototype_ `FDMXGDTFSubphysicalUnit(const TSharedRef<FDMXGDTFAttribute>& InAttribute);`
- L51 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L52 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L53 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L57 _public member_ `EDMXGDTFSubphysicalUnit Type = EDMXGDTFSubphysicalUnit::Value;` — Type of subpyhsical unit
- L60 _public member_ `EDMXGDTFPhysicalUnit PhysicalUnit;` — Phyiscal Unit
- L63 _public member_ `float PhysicalFrom = 0.0;` — The default physical from of the subphysical unit; Unit: as defined in PhysicalUnit; Default value: 0
- L66 _public member_ `float PhysicalTo = 1.0;` — The default physical to of the subphysical unit; Unit: as defined in PhysicalUnit; Default value: 1
- L69 _public member_ `const TWeakPtr<FDMXGDTFAttribute> OuterAttribute;` — The outer attribute

#### Free symbols / members of external scopes

- L37 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFSubphysicalUnit, EDMXGDTFSubphysicalUnit::MaxEnumValue);`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace DMX` (scope `UE`)
- L40 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXGDTFDescription.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDescription`  
`class FDMXGDTFDescription : public TSharedFromThis<FDMXGDTFDescription>`  
_L21-40_
- inherits: `TSharedFromThis<FDMXGDTFDescription>`
- desc: The Description of a GDTF, corresponds to the description.xml of the GDTF. The descritpion and all related members in this module shall follow the currently implemented GDTF standard. See DMXGDTFVersion for details.
- L26 _public prototype_ `void InitializeFromDescriptionXml(const TSharedRef<FXmlFile>& DescriptionXml);` — Initializes this node and its chilren from a GDTF Description.xml
- L29 _public prototype_ `void InitializeFromFixtureType(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);` — Initializes this object from a GDTF fixture type.
- L32 _public prototype_ `TSharedPtr<FXmlFile> ExportAsXml() const;` — Exports an Xml file from the node tree in this description. Returns the XML file or nullptr if not a valid XML
- L35 _public function_ `TSharedPtr<FDMXGDTFFixtureType> GetFixtureType() const` — Returns the Fixture Type of this GDTF description
- L39 _private member_ `TSharedPtr<FDMXGDTFFixtureType> FixtureType;` — The Fixture Type Child Node

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXGDTFFixtureType.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFixtureType`  
`class FDMXGDTFFixtureType : public FDMXGDTFNode`  
_L22-111_
- inherits: `FDMXGDTFNode`
- desc: The FixtureType node is the starting point of the description of the fixture type within the XML file.
- L27 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L28 _public prototype_ `virtual void Initialize(const FXmlNode& InXmlNode) override;`
- L29 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L33 _public member_ `FName Name;` — Name of the fixture type. As it is based on Name.
- L36 _public member_ `FString ShortName;` — Shortened name of the fixture type. Non detailed version or an abbreviation. Can use any characters or symbols
- L39 _public member_ `FString LongName;` — Detailed, complete name of the fixture type, can include any characters or extra symbols
- L42 _public member_ `FString Manufacturer;` — Manufacturer of the fixture type.
- L45 _public member_ `FString Description;` — Description of the fixture type.
- L48 _public member_ `FGuid FixtureTypeID;` — Unique number of the fixture type
- L56 _public member_ `FString Thumbnail;` — Optional. File name without extension containing description of the thumbnail. Use the following as a resource file: - png file to provide the rasterized picture. Maximum resolution of picture: 1024x1024 - svg file to provide the vector graphic. - These resource files are located in the root directory of the zip file.
- L59 _public member_ `int32 ThumbnailOffsetX = 0;` — Horizontal offset in pixels from the top left of the viewbox to the insertion point on a label
- L62 _public member_ `int32 ThumbnailOffsetY = 0;` — Vertical offset in pixels from the top left of the viewbox to the insertion point on a label.
- L65 _public member_ `FGuid RefFT;` — GUID of the referenced fixture type
- L72 _public member_ `bool bCanHaveChildren = true;` — Describes if it is possible to mount other devices to this device. Value: “Yes”, “No”. Default value: “Yes” UE Specific: Using a bool instead of a true/false enum.
- L75 _public member_ `TSharedPtr<FDMXGDTFAttributeDefinitions> AttributeDefinitions;` — Defines all Fixture Type Attributes that are used in the fixture type.
- L82 _public member_ `TArray<TSharedPtr<FDMXGDTFWheel>> Wheels;` — This section defines all physical or virtual wheels of the device (XML node <Wheels>). As children wheel collect can have a list of a wheels. Note 1: Physical or virtual wheels represent the changes to the light beam within the device. Typically color, gobo, prism, animation, content and others are described by wheels.
- L85 _public member_ `TSharedPtr<FDMXGDTFPhysicalDescriptions> PhysicalDescriptions;` — Contains additional physical descriptions.
- L92 _public member_ `TArray<TSharedPtr<FDMXGDTFModel>> Models;` — Each device is divided into smaller parts: body, yoke, head and so on. These are called geometries. Each geometry has a separate model description and a physical description. Model collect contains model descriptions of the fixture parts. (XML node <Models>).
- L95 _public member_ `TSharedPtr<FDMXGDTFGeometryCollect> GeometryCollect;` — Describes physically separated parts of the device.
- L101 _public member_ `TArray<TSharedPtr<FDMXGDTFDMXMode>> DMXModes;` — This section is describes all DMX modes of the device. If firmware revisions change a DMX footprint, then such revisions should be specified as new DMX mode (XML node <DMXModes>).
- L104 _public member_ `TArray<TSharedPtr<FDMXGDTFRevision>> Revisions;` — This section defines the history of device type (XML node <Revisions>).
- L107 _public member_ `TArray<TSharedPtr<FDMXGDTFFTPreset>> FTPresets;` — Is used to transfer user-defined and fixture type specific presets to other show files.
- L110 _public member_ `TSharedPtr<FDMXGDTFProtocols> Protocols;` — Is used to specify supported protocols.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXGDTFNode.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFNode`  
`class FDMXGDTFNode : public TSharedFromThis<FDMXGDTFNode>`  
_L16-40_
- inherits: `TSharedFromThis<FDMXGDTFNode>`
- desc: Base class for GDTF nodes.
- L23 _public function_ `virtual ~FDMXGDTFNode()`
- L26 _public prototype_ `virtual const TCHAR* GetXmlTag() const = 0;` — Gets the Xml Tag corresponding to this node
- L29 _public prototype_ `virtual void Initialize(const FXmlNode& InXmlNode) = 0;` — Initializes the node from an Xml node. Called after the node was constructed.
- L32 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) = 0;` — Creates an XML node in the parent node
- L35 _public function_ `TWeakPtr<FDMXGDTFFixtureType> GetFixtureType() const` — Returns the fixture type this node resides in
- L39 _private member_ `TWeakPtr<FDMXGDTFFixtureType> WeakFixtureType;` — The fixture type this node resides in

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXGDTFVersion.h` (Public)


#### struct `UE::DMX::GDTF::FDMXGDTFVersion`  
`struct FDMXGDTFVersion`  
_L11-22_
- desc: Version of the GDTF standard currently being used by the engine
- L13 _public member_ `static const uint8 MajorVersion = 1;`
- L15 _public member_ `static const uint8 MinorVersion = 2;`
- L17 _public prototype_ `static const FString GetMajorVersionAsString();`
- L18 _public prototype_ `static const FString GetMinorVersionAsString();`
- L21 _public prototype_ `static const FString GetAsString();` — Returns the max supported major and minor version as string, in the format of 'Major.Minor', e.g. "1.2"

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFChannelFunction.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFChannelFunction`  
`class FDMXGDTFChannelFunction : public FDMXGDTFNode`  
_L26-149_
- inherits: `FDMXGDTFNode`
- desc: The Fixture Type Attribute is assigned to a Channel Function and defines the function of its DMX Range. (XML node <ChannelFunction>).
- L30 _public prototype_ `FDMXGDTFChannelFunction(const TSharedRef<FDMXGDTFLogicalChannel>& InLogicalChannel);`
- L33 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L34 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L35 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L39 _public member_ `FName Name;` — Unique name; Default value: Name of attribute and number of channel function.
- L42 _public member_ `FString Attribute;` — Link to attribute.
- L45 _public member_ `FString OriginalAttribute;` — The manufacturer’s original name of the attribute; Default: empty
- L51 _public member_ `FDMXGDTFDMXValue DMXFrom;` — Start DMX value; The end DMX value is calculated as a DMXFrom of the next channel function -1 or the maximum value of the DMX channel. Default value: "0/1".
- L54 _public member_ `FDMXGDTFDMXValue Default;` — Default DMX value of channel function when activated by the control system.
- L57 _public member_ `float PhysicalFrom = 0.f;` — Physical start value; Default value : 0
- L60 _public member_ `float PhysicalTo = 1.f;` — Physical end value; Default value : 1
- L63 _public member_ `float RealFade = 0.f;` — Time in seconds to move from min to max of the Channel Function; Default value : 0
- L66 _public member_ `float RealAcceleration = 0.f;` — Time in seconds to accelerate from stop to maximum velocity; Default value : 0
- L69 _public member_ `FString Wheel;` — (Optional) Link to a wheel; Starting point: Wheel Collect
- L72 _public member_ `FString Emitter;` — (Optional) Link to an emitter in the physical description; Starting point: Emitter Collect
- L75 _public member_ `FString Filter;` — (Optional) Link to a filter in the physical description; Starting point: Filter Collect
- L78 _public member_ `FString ColorSpace;` — (Optional) Link to a color space in the physical description; Starting point: Physical Descriptions Collect
- L81 _public member_ `FString Gamut;` — (Optional) Link to a gamut in the physical description; Starting point: Gamut Collect
- L84 _public member_ `FString ModeMaster;` — (Optional) Link to DMX Channel or Channel Function; Starting point DMX mode.
- L87 _public member_ `FDMXGDTFDMXValue ModeFrom = TEXT("0/1` — Only used together with ModeMaster; DMX start value; Default value: 0/1
- L90 _public member_ `FDMXGDTFDMXValue ModeTo = TEXT("0/1` — Only used together with ModeMaster; DMX start value; Default value: 0/1
- L93 _public member_ `FString DMXProfile;` — (Optional) Link to DMX Profile; Starting point: DMX Profile Collect
- L96 _public member_ `float Min = 0.f;` — Minimum Physical Value that will be used for the DMX Profile. Default: Value from PhysicalFrom 1
- L99 _public member_ `float Max = 1.f;` — Maximum Physical Value that will be used for the DMX Profile. Default: Value from PhysicalTo
- L106 _public member_ `FString CustomName;` — Custom Name that can he used do adress this channel function with other command based protocols like OSC. Default: Node Name of the Channel function Example : Head_Dimmer.Dimmer.Dimmer
- L109 _public member_ `TArray<TSharedPtr<FDMXGDTFChannelSet>> ChannelSetArray;` — A list of channel sets
- L112 _public member_ `TArray<TSharedPtr<FDMXGDTFSubchannelSet>> SubchannelSetArray;` — A list of subchannel sets
- L115 _public member_ `const TWeakPtr<FDMXGDTFLogicalChannel> OuterLogicalChannel;` — The outer logical channel
- L118 _public prototype_ `TSharedPtr<FDMXGDTFAttribute> ResolveAttribute() const;` — Resolves the linked attribute. Returns the attribute, or nullptr if no attribute is linked
- L121 _public prototype_ `TSharedPtr<FDMXGDTFWheel> ResolveWheel() const;` — Resolves the linked wheel. Returns the wheel, or nullptr if no wheel is linked
- L124 _public prototype_ `TSharedPtr<FDMXGDTFEmitter> ResolveEmitter() const;` — Resolves the linked emitter. Returns the emitter, or nullptr if no emitter is linked
- L127 _public prototype_ `TSharedPtr<FDMXGDTFFilter> ResolveFilter() const;` — Resolves the linked filter. Returns the filter, or nullptr if no filter is linked
- L130 _public prototype_ `TSharedPtr<FDMXGDTFColorSpace> ResolveColorSpace() const;` — Resolves the linked color space. Returns the color space, or nullptr if no color space is linked
- L133 _public prototype_ `TSharedPtr<FDMXGDTFGamut> ResolveGamut() const;` — Resolves the linked gamut. Returns the gamut, or nullptr if no gamut is linked
- L139 _public prototype_ `void ResolveModeMaster(TSharedPtr<FDMXGDTFDMXChannel>& OutDMXChannel, TSharedPtr<FDMXGDTFChannelFunction>& OutChannelFunction) const;` — Resolves the linked mode master. May be either a DMX channel or a DMX channel function. Returns the mode master, or nullptr if no mode master is linked.
- L142 _public prototype_ `void ResolveModePrimary(TSharedPtr<FDMXGDTFDMXChannel>& OutDMXChannel, TSharedPtr<FDMXGDTFChannelFunction>& OutChannelFunction) const;` — Same as resolve mode master but using inclusive language
- L145 _public prototype_ `TSharedPtr<FDMXGDTFDMXProfile> ResolveDMXProfile() const;` — Resolves the linked DMX profile. Returns the DMX profile, or nullptr if no DMX profile is linked
- L148 _public prototype_ `FDMXGDTFDMXValue ParseDefault(const FString& Value, const FXmlNode* XmlNode) const;` — Parses the default value. Useful to parse legacy GDTFs that store the default in the DMX channel node

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFChannelRelation.h` (Public)


#### enum `EDMXGDTFChannelRelationType`  
`enum class EDMXGDTFChannelRelationType`  
_L12-19_
- reflection: `UENUM()`
- desc: Type of the relation; Values: “Multiply”, “Override”
- L14 _public enumerator_ `Multiply UMETA(DisplayName = "Multiply")`
- L15 _public enumerator_ `Override UMETA(DisplayName = "Override")`
- L18 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFChannelRelation`  
`class FDMXGDTFChannelRelation : public FDMXGDTFNode`  
_L29-61_
- inherits: `FDMXGDTFNode`
- desc: This section defines the relation between the master DMX channel and the following logical channel(XML node <Relation>).
- L33 _public prototype_ `FDMXGDTFChannelRelation(const TSharedRef<FDMXGDTFDMXMode>& InDMXMode);`
- L36 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L37 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L38 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L42 _public member_ `FName Name;` — The unique name of the relation
- L45 _public member_ `FString Master;` — Link to the master DMX channel
- L48 _public member_ `FString Follower;` — Link to the following channel function
- L51 _public member_ `EDMXGDTFChannelRelationType Type = EDMXGDTFChannelRelationType::Multiply;` — Type of the relation
- L54 _public member_ `const TWeakPtr<FDMXGDTFDMXMode> OuterDMXMode;` — The outer DMX mode
- L57 _public prototype_ `TSharedPtr<FDMXGDTFDMXChannel> ResolveMaster() const;` — Resolves the linked master. Returns the master, or nullptr if no master is linked
- L60 _public prototype_ `TSharedPtr<FDMXGDTFChannelFunction> ResolveFollower() const;` — Resolves the linked follower. Returns the follower, or nullptr if no follower is linked

#### Free symbols / members of external scopes

- L20 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFChannelRelationType, EDMXGDTFChannelRelationType::MaxEnumValue);`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DMX` (scope `UE`)
- L22 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFChannelSet.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFChannelSet`  
`class FDMXGDTFChannelSet : public FDMXGDTFNode`  
_L13-51_
- inherits: `FDMXGDTFNode`
- desc: This section defines the channel sets of the channel function (XML node <ChannelSet>).
- L17 _public prototype_ `FDMXGDTFChannelSet(const TSharedRef<FDMXGDTFChannelFunction>& InChannelFunction);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `FName Name;` — The name of the channel set. Default: Empty
- L33 _public member_ `FDMXGDTFDMXValue DMXFrom;` — Start DMX value; The end DMX value is calculated as a DMXFrom of the next channel set — 1 or the maximum value of the current channel function; Default value : 0 / 1
- L36 _public member_ `float PhysicalFrom = 0.f;` — Physical start value
- L39 _public member_ `float PhysicalTo = 1.f;` — Physical end value
- L47 _public member_ `int32 WheelSlotIndex = INDEX_NONE;` — If the channel function has a link to a wheel, a corresponding slot index needs to be specified.The wheel slot index results from the order of slots of the wheel which is linked in the channel function. The wheel slot index is normalized to 1. Size: 4 bytes
- L50 _public member_ `const TWeakPtr<FDMXGDTFChannelFunction> OuterChannelFunction;` — The outer channel function

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFDMXChannel.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDMXChannel`  
`class FDMXGDTFDMXChannel : public FDMXGDTFNode`  
_L21-101_
- inherits: `FDMXGDTFNode`
- desc: This section defines the DMX channel (XML node <DMXChannel>). The name of a DMX channel cannot be user-defined and must consist of a geometry name and the attribute name of the first logical channel with the separator "_". In one DMX Mode, this combination needs to be unique.
- L25 _public prototype_ `FDMXGDTFDMXChannel(const TSharedRef<FDMXGDTFDMXMode>& InDMXMode);`
- L29 _public prototype_ `FDMXGDTFDMXChannel(const FDMXGDTFDMXChannel& Node) = delete;` — Explicit constructors, required to avoid deprecation warnings on Clang with deprecated member Default.
- L30 _public prototype_ `FDMXGDTFDMXChannel& operator=(const FDMXGDTFDMXChannel& Node) = delete;`
- L31 _public prototype_ `FDMXGDTFDMXChannel(FDMXGDTFDMXChannel&& Node) = delete;`
- L32 _public prototype_ `FDMXGDTFDMXChannel& operator=(FDMXGDTFDMXChannel&& Node) = delete;`
- L33 _public prototype_ `~FDMXGDTFDMXChannel() = default;`
- L37 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L38 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L39 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L48 _public member_ `int32 DMXBreak = 1;` — Number of the DMXBreak; Default value: 1; Special value: “Overwrite” – means that this number will be overwritten by Geometry Reference; Size: 4 bytes UE Specific: If negative and a related geometry reference exists, it means the value is set to special value "Overwrite".
- L55 _public member_ `TArray<uint32> Offset;` — Relative addresses of the current DMX channel from highest to least significant; Size per int: 4 bytes UE Specific: Special value "None" is equviavalent to an empty array.
- L61 _public member_ `FString InitialFunction;` — Link to the channel function that will be activated by default for this DMXChannel. Default value is the first channel function of the first logical function of this DMX channel.
- L64 _public member_ `FDMXGDTFDMXValue Highlight;` — Highlight value for current channel; Special value : “None”.Default value : “None”
- L73 _public member_ `FName Geometry;` — Name of the geometry the current channel controls. The Geometry should be the place in the tree of geometries where the function of the DMX Channel (as defined by ChannelFunction) is located either physically or logically. If the DMX channel doesn’t have a location, put it in the top level geometry of the geometry tree. Attributes follow a trickle down principle, so they are inherited from top down
- L76 _public member_ `TArray<TSharedPtr<FDMXGDTFLogicalChannel>> LogicalChannelArray;` — A list of logical channels
- L79 _public member_ `const TWeakPtr<FDMXGDTFDMXMode> OuterDMXMode;` — The outer DMX mode
- L82 _public member_ `FDMXGDTFDMXValue Default;` — `UE_DEPRECATED(5.5, "Deprecated with GDTF 1.1. Instead each channel function can hold its own default. Please refer to DMXGDTFChannelFunction::Default")`
- L85 _public prototype_ `TSharedPtr<FDMXGDTFChannelFunction> ResolveInitialFunction() const;` — Resolves the linked initial function. Returns the initial function, or nullptr if no initial function is linked
- L93 _public prototype_ `TSharedPtr<FDMXGDTFGeometry> ResolveGeometry() const;` — Resolves the linked geometry. Returns the geometry, or nullptr if no geometry is linked. To resolve as geometry references, see ResolveGeometryReferences. Note, GDTFs of older version directly reference a model as geometry. Such models are not considered.
- L96 _public prototype_ `TArray<TSharedPtr<FDMXGDTFGeometryReference>> ResolveGeometryReferences() const;` — Resolves the linked geometry as geometry references. Returns geometry references or an empty array, if no linked geometry references could be found.
- L100 _private prototype_ `TArray<uint32> ParseOffset(const FString& GDTFString) const;` — Converts a GDTF string to an array of offsets

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFDMXMode.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDMXMode`  
`class FDMXGDTFDMXMode : public FDMXGDTFNode`  
_L17-55_
- inherits: `FDMXGDTFNode`
- desc: Each DMX mode describes logical control a part of the device in a specific mode (XML node <DMXMode>).
- L21 _public prototype_ `FDMXGDTFDMXMode(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L24 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L25 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L26 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L30 _public member_ `FName Name;` — The unique name of the DMX mode
- L33 _public member_ `FString Description;` — Description of the DMX mode.
- L36 _public member_ `FName Geometry;` — The first geometry in the device; Only top level geometries are allowed to be linked
- L39 _public member_ `TArray<TSharedPtr<FDMXGDTFDMXChannel>> DMXChannels;` — Description of all DMX channels used in the mode
- L42 _public member_ `TArray<TSharedPtr<FDMXGDTFChannelRelation>> Relations;` — Description of relations between channels
- L45 _public member_ `TArray<TSharedPtr<FDMXGDTFFTMacro>> FTMacros;` — Is used to describe macros of the manufacturer.
- L48 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type
- L51 _public prototype_ `TSharedPtr<FDMXGDTFGeometry> ResolveGeometry() const;` — Resolves the Geometry for this mode
- L54 _public prototype_ `void ResolveChannel(const FString& Link, TSharedPtr<FDMXGDTFDMXChannel>& OutDMXChannel, TSharedPtr<FDMXGDTFChannelFunction>& OutChannelFunction) const;` — Resolves a DMX channel or channel function

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFDMXValue.h` (Public)


#### struct `UE::DMX::GDTF::FDMXGDTFDMXValue`  
`struct FDMXGDTFDMXValue`  
_L17-54_
- desc: Special type to define DMX value where n is the byte count. The byte count can be individually specified without depending on the resolution of the DMX Channel. By default byte mirroring is used for the conversion. So 255/1 in a 16 bit channel will result in 65535. You can use the byte shifting operator to use byte shifting for the conversion. So 255/1s in a 16 bit channel will result in 65280.
- L19 _public prototype_ `FDMXGDTFDMXValue() = default;`
- L20 _public prototype_ `FDMXGDTFDMXValue(const TCHAR* InValue);`
- L21 _public prototype_ `FDMXGDTFDMXValue(const uint32 InValue, const int32 InNumBytes, const bool bInByteMirroring = true);`
- L24 _public prototype_ `bool Get(const TSharedRef<FDMXGDTFDMXChannel>& InDMXChannel, uint32& OutValue) const;` — Gets the DMX value in the resolution of the specified DMX channel. Returns false if the DMX Value has special value "None"
- L27 _public prototype_ `uint32 GetChecked(const TSharedRef<FDMXGDTFDMXChannel>& InDMXChannel) const;` — Gets the DMX value in the resolution of the specified DMX channel, only valid when not IsSet (checked).
- L30 _public prototype_ `FString AsString() const;` — Returns the DMX value as string. If the DMX value is not set, returns 0/1.
- L33 _public prototype_ `void Reset();` — Resets the DMX value
- L36 _public prototype_ `bool IsSet() const;` — Returns true if the DMX Value is set.
- L38 _public function_ `bool operator==(const FDMXGDTFDMXValue& Other) const`
- L39 _public function_ `bool operator!=(const FDMXGDTFDMXValue& Other) const`
- L44 _private prototype_ `uint32 GetMax(uint8 WordSize) const;` — Returns the Max value of WordSize
- L47 _private member_ `uint32 Value = 0;` — The DMX Value
- L50 _private member_ `uint8 NumBytes = 0;` — The number of bytes of this DMX value
- L53 _private member_ `bool bByteMirroring = true;` — Whether to use byte mirroring or byte shifting when accessing the DMX value

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFFTMacro.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFTMacro`  
`class FDMXGDTFFTMacro : public FDMXGDTFNode`  
_L14-40_
- inherits: `FDMXGDTFNode`
- desc: This section defines a DMX sequence. (XML node <FTMacro>).
- L18 _public prototype_ `FDMXGDTFFTMacro(const TSharedRef<FDMXGDTFDMXMode>& InDMXMode);`
- L21 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L22 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L23 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L27 _public member_ `FName Name;` — The unique name of the macro.
- L30 _public member_ `FString ChannelFunction;` — (Optional) Link to the channel function.
- L33 _public member_ `TArray<TSharedPtr<FDMXGDTFMacroDMX>> MacroDMXArray;` — A list of macros
- L36 _public member_ `const TWeakPtr<FDMXGDTFDMXMode> OuterDMXMode;` — The outer DMX mode
- L39 _public prototype_ `TSharedPtr<FDMXGDTFChannelFunction> ResolveChannelFunction() const;` — Resolves the linked channel function. Returns the channel function, or nullptr if no channel function is linked

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFLogicalChannel.h` (Public)


#### enum `EDMXGDTFLogicalChannelSnap`  
`enum class EDMXGDTFLogicalChannelSnap : uint8`  
_L16-25_
- reflection: `UENUM()`
- desc: If snap is enabled, the logical channel will not fade between values. Instead, it will jump directly to the new value. Value: “Yes”, “No”, “On”, “Off”.Default value : “No”
- L18 _public enumerator_ `Yes UMETA(DisplayName = "Yes")`
- L19 _public enumerator_ `No UMETA(DisplayName = "No")`
- L20 _public enumerator_ `On UMETA(DisplayName = "On")`
- L21 _public enumerator_ `Off UMETA(DisplayName = "Off")`
- L24 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### enum `EDMXGDTFLogicalChannelMaster`  
`enum class EDMXGDTFLogicalChannelMaster : uint8`  
_L34-42_
- reflection: `UENUM()`
- desc: Defines if all the subordinate channel functions react to a Group Control defined by the control system. Values: “None”, “Grand”, “Group”; Default value : “None”.
- L36 _public enumerator_ `None UMETA(DisplayName = "None")`
- L37 _public enumerator_ `Grand UMETA(DisplayName = "Grand")`
- L38 _public enumerator_ `Group UMETA(DisplayName = "Group")`
- L41 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFLogicalChannel`  
`class FDMXGDTFLogicalChannel : public FDMXGDTFNode`  
_L58-104_
- inherits: `FDMXGDTFNode`
- desc: The Fixture Type Attribute is assigned to a LogicalChannel and defines the function of the LogicalChannel. All logical channels that are children of the same DMX channel are mutually exclusive. In a DMX mode, only one logical channel with the same attribute can reference the same geometry at a time. The name of a Logical Channel cannot be user-defined and is equal to the linked attribute name. The XML node of the logical channel is <LogicalChannel>.
- L62 _public prototype_ `FDMXGDTFLogicalChannel(const TSharedRef<FDMXGDTFDMXChannel>& InDMXChannel);`
- L65 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L66 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L67 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L71 _public member_ `FName Attribute;` — Link to the attribute; The starting point is the Attribute Collect.
- L74 _public member_ `EDMXGDTFLogicalChannelSnap Snap = EDMXGDTFLogicalChannelSnap::No;` — If snap is enabled, the logical channel will not fade between values. Instead, it will jump directly to the new value.
- L77 _public member_ `EDMXGDTFLogicalChannelMaster Master = EDMXGDTFLogicalChannelMaster::None;` — Defines if all the subordinate channel functions react to a Group Control defined by the control system.
- L80 _public member_ `float MibFade = 0.f;` — Minimum fade time for moves in black action. MibFade is defined for the complete DMX range. Default value : 0; Unit: second
- L87 _public member_ `float DMXChangeTimeLimit = 0.f;` — Minimum fade time for the subordinate channel functions to change DMX values by the control system.DMXChangeTimeLimit is defined for the complete DMX range.Default value : 0; Unit: second
- L90 _public member_ `TArray<TSharedPtr<FDMXGDTFChannelFunction>> ChannelFunctionArray;` — A list of channel functions
- L93 _public member_ `const TWeakPtr<FDMXGDTFDMXChannel> OuterDMXChannel;` — The outer DMX channel
- L96 _public prototype_ `TSharedPtr<FDMXGDTFAttribute> ResolveAttribute() const;` — Resolves the linked attribute. Returns the attribute, or nullptr if no attribute is linked
- L100 _private prototype_ `EDMXGDTFLogicalChannelSnap ParseSnap(const FString& GDTFString) const;` — Converts a string to a snap enum value. Logs invalid string values.
- L103 _private prototype_ `EDMXGDTFLogicalChannelMaster ParseMaster(const FString& GDTFString) const;` — Converts a string to a master enum value. Logs invalid string values.

#### Free symbols / members of external scopes

- L26 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFLogicalChannelSnap, EDMXGDTFLogicalChannelSnap::MaxEnumValue);`
- L43 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFLogicalChannelMaster, EDMXGDTFLogicalChannelMaster::MaxEnumValue);`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace DMX` (scope `UE`)
- L45 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFMacroDMX.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMacroDMX`  
`class FDMXGDTFMacroDMX : public FDMXGDTFNode`  
_L13-30_
- inherits: `FDMXGDTFNode`
- desc: This section defines the sequence of DMX values which are sent by a control system. (XML node <MacroDMX>).
- L17 _public prototype_ `FDMXGDTFMacroDMX(const TSharedRef<FDMXGDTFFTMacro>& InFTMacro);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `TArray<TSharedPtr<FDMXGDTFMacroDMXStep>> MacroDMXStepArray;` — A list of macro steps
- L29 _public member_ `const TWeakPtr<FDMXGDTFFTMacro> OuterFTMacro;` — The outer macro

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFMacroDMXStep.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMacroDMXStep`  
`class FDMXGDTFMacroDMXStep : public FDMXGDTFNode`  
_L13-33_
- inherits: `FDMXGDTFNode`
- desc: This section defines a DMX step (XML node <MacroDMXStep>).
- L17 _public prototype_ `FDMXGDTFMacroDMXStep(const TSharedRef<FDMXGDTFMacroDMX>& InMacroDMX);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `float Duration = 1.f;` — Duration of a step; Default value : 1; Unit: seconds.
- L29 _public member_ `TArray<TSharedPtr<FDMXGDTFMacroDMXValue>> MacroDMXValueArray;` — A list of macro dmx values
- L32 _public member_ `const TWeakPtr<FDMXGDTFMacroDMX> OuterMacroDMX;` — The outer macro DMX

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFMacroDMXValue.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMacroDMXValue`  
`class FDMXGDTFMacroDMXValue : public FDMXGDTFNode`  
_L13-36_
- inherits: `FDMXGDTFNode`
- desc: This section defines the value for DMX channel (XML node <DMXValue>).
- L17 _public prototype_ `FDMXGDTFMacroDMXValue(const TSharedRef<FDMXGDTFMacroDMXStep>& InMacroDMXStep);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `FString DMXValue;` — Value of the DMX channel
- L29 _public member_ `FString DMXChannel;` — Link to the channel
- L32 _public member_ `TWeakPtr<FDMXGDTFMacroDMXStep> OuterMacroDMXStep;` — The outer macro DMX step
- L35 _public prototype_ `TSharedPtr<FDMXGDTFDMXChannel> ResolveDMXChannel() const;` — Resolves the linked DMX channel. Returns the DMX channel, or nullptr if no DMX channel is linked

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/DMXModes/DMXGDTFSubchannelSet.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFSubchannelSet`  
`class FDMXGDTFSubchannelSet : public FDMXGDTFNode`  
_L15-50_
- inherits: `FDMXGDTFNode`
- desc: This section defines the sub channel sets of the channel function (XML node <ChannelFunction>).
- L19 _public prototype_ `FDMXGDTFSubchannelSet(const TSharedRef<FDMXGDTFChannelFunction>& InChannelFunction);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `FName Name;` — The name of the sub channel set. Default: Empty
- L31 _public member_ `float PhysicalFrom = 0.f;` — Physical start value
- L34 _public member_ `float PhysicalTo = 1.f;` — Physical end value
- L37 _public member_ `FString SubphyiscalUnit;` — (Optional) Link to the sub physical unit; Starting Point: Attribute
- L40 _public member_ `FString DMXProfile;` — (Optional) Link to the DMX Profile; Starting Point: DMX Profile Collect
- L43 _public member_ `const TWeakPtr<FDMXGDTFChannelFunction> OuterChannelFunction;` — The outer channel function
- L46 _public prototype_ `TSharedPtr<FDMXGDTFSubphysicalUnit> ResolveSubphysicalUnit() const;` — Resolves the linked subphysical unit. Returns the subphysical unit, or nullptr if no subphysical unit is linked
- L49 _public prototype_ `TSharedPtr<FDMXGDTFDMXProfile> ResolveDMXProfile() const;` — Resolves the linked DMX profile. Returns the DMX profile, or nullptr if no DMX profile is linked

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/FTPresets/DMXGDTFFTPreset.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFTPreset`  
`class FDMXGDTFFTPreset : public FDMXGDTFNode`  
_L12-26_
- inherits: `FDMXGDTFNode`
- desc: This section defines fixture type specific presets. It currently does not have any XML attributes (XML node FTPresets>).
- L16 _public prototype_ `FDMXGDTFFTPreset(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFAxisGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFAxisGeometry`  
`class FDMXGDTFAxisGeometry : public FDMXGDTFGeometry`  
_L12-23_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry defines device parts with a rotation axis (XML node <Axis>).
- L16 _public function_ `FDMXGDTFAxisGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L21 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFBeamGeometry.h` (Public)


#### enum `EDMXGDTFBeamGeometryLampType`  
`enum class EDMXGDTFBeamGeometryLampType : uint8`  
_L15-24_
- reflection: `UENUM()`
- desc: Defines type of the light source; The currently defined types are: Discharge, Tungsten, Halogen, LED; Default value “Discharge”
- L17 _public enumerator_ `Discharge UMETA(DisplayName = "Discharge")`
- L18 _public enumerator_ `Tungsten UMETA(DisplayName = "Tungsten")`
- L19 _public enumerator_ `Halogen UMETA(DisplayName = "Halogen")`
- L20 _public enumerator_ `LED UMETA(DisplayName = "LED")`
- L23 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### enum `EDMXGDTFBeamGeometryBeamType`  
`enum class EDMXGDTFBeamGeometryBeamType : uint8`  
_L39-51_
- reflection: `UENUM()`
- desc: Beam Type; Specified values: “Wash”, “Spot”, “None”, “Rectangle”; “PC”, “Fresnel”, “Glow”. Default value “Wash” * The <BeamType> describes how the Beam will be rendered. — “Wash”, “Fresnel”, - “PC” — A conical beam with soft edges and softened field projection. — “Spot” — A conical beam with hard edges. — “Rectangle” — A pyramid-shaped beam with hard edges. — “None”, “Glow” — No beam will be drawn, only the geometry will emit light itself.
- L41 _public enumerator_ `Wash UMETA(DisplayName = "Wash")`
- L42 _public enumerator_ `Spot UMETA(DisplayName = "Spot")`
- L43 _public enumerator_ `None UMETA(DisplayName = "None")`
- L44 _public enumerator_ `Rectangle UMETA(DisplayName = "Rectangle")`
- L45 _public enumerator_ `PC UMETA(DisplayName = "PC")`
- L46 _public enumerator_ `Fresnel UMETA(DisplayName = "Fresnel")`
- L47 _public enumerator_ `Glow UMETA(DisplayName = "Glow")`
- L50 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFBeamGeometry`  
`class FDMXGDTFBeamGeometry : public FDMXGDTFGeometry`  
_L63-132_
- inherits: `FDMXGDTFGeometry`
- desc: It is a basic geometry type without specification (XML node <Geometry>). The beam geometry emits its light into negative Z direction (and Y-up)
- L67 _public function_ `FDMXGDTFBeamGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L72 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L73 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L74 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L78 _public member_ `EDMXGDTFBeamGeometryLampType LampType = EDMXGDTFBeamGeometryLampType::Discharge;` — Defines type of the light source
- L81 _public member_ `float PowerConsumption = 1000.f;` — Power consumption; Default value: 1 000; Unit: Watt
- L84 _public member_ `float LuminousFlux = 1000.f;` — Intensity of all the represented light emitters; Default value: 10 000; Unit: lumen
- L87 _public member_ `float ColorTemperature = 1000.f;` — Color temperature; Default value: 6 000; Unit: kelvin
- L90 _public member_ `float BeamAngle = 25.f;` — Beam angle; Default value: 25,0; Unit: degree
- L93 _public member_ `float FieldAngle = 25.f;` — Field angle; Default value: 25,0; Unit: degree
- L96 _public member_ `float ThrowRatio = 1.f;` — Throw Ratio of the lens for BeamType Rectangle; Default value: 1; Unit: None
- L99 _public member_ `float RectangleRatio = 1.7777f;` — Ratio from Width to Height of the Rectangle Type Beam; Default value: 1.7777; Unit: None
- L102 _public member_ `float BeamRadius = 0.05f;` — Beam radius on starting point. Default value: 0,05; Unit: meter.
- L113 _public member_ `EDMXGDTFBeamGeometryBeamType BeamType = EDMXGDTFBeamGeometryBeamType::Wash;` — Beam Type The <BeamType> describes how the Beam will be rendered. — “Wash”, “Fresnel”, - “PC” — A conical beam with soft edges and softened field projection. — “Spot” — A conical beam with hard edges. — “Rectangle” — A pyramid-shaped beam with hard edges. — “None”, “Glow” — No beam will be drawn, only the geometry will emit light itself.
- L120 _public member_ `uint8 ColorRenderingIndex = 100;` — The CRI according to ANSI/IES TM-30 is a quantitative measure of the ability of the light source showing the object color naturally as it does as daylight reference. Size 1 byte. Default value 100
- L128 _public member_ `FString EmitterSpectrum;` — (Optional) Link to emitter in the physical description; use this to define the white light source of a subtractive color mixing system. Starting point: Emitter Collect; Default spectrum is a Black-Body with the defined ColorTemperature.
- L131 _public prototype_ `TSharedPtr<FDMXGDTFEmitter> ResolveEmitterSpectrum() const;` — Resolves the linked emitter spectrum. Returns the emitter spectrum, or nullptr if no emitter spectrum is linked

#### Free symbols / members of external scopes

- L25 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFBeamGeometryLampType, EDMXGDTFBeamGeometryLampType::MaxEnumValue);`
- L52 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFBeamGeometryBeamType, EDMXGDTFBeamGeometryBeamType::MaxEnumValue);`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace DMX` (scope `UE`)
- L54 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFDMXAddress.h` (Public)


#### struct `UE::DMX::GDTF::FDMXGDTFDMXAddress`  
`struct FDMXGDTFDMXAddress`  
_L10-30_
- desc: The container for DMX Addresses
- L12 _public prototype_ `FDMXGDTFDMXAddress() = default;`
- L14 _public function_ `FDMXGDTFDMXAddress(int64 InAbsoluteAddress) : AbsoluteAddress(InAbsoluteAddress)`
- L18 _public function_ `FDMXGDTFDMXAddress(int32 InUniverse, int32 InChannel)`
- L23 _public function_ `int32 GetUniverse() const`
- L25 _public function_ `int32 GetChannel() const`
- L27 _public member_ `int64 AbsoluteAddress = 512;`
- L29 _public member_ `static const uint16 UniverseSize = 512;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFDisplayGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDisplayGeometry`  
`class FDMXGDTFDisplayGeometry : public FDMXGDTFGeometry`  
_L10-26_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe a self-emitting surface which is used to display visual media (XML node <Display>)
- L14 _public function_ `FDMXGDTFDisplayGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `FString Texture;` — Name of the mapped texture in Model file that will be swapped out for the media resource

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFFilterBeamGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFilterBeamGeometry`  
`class FDMXGDTFFilterBeamGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry defines device parts with a beam filter (XML node <FilterBeam>).
- L14 _public function_ `FDMXGDTFFilterBeamGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFFilterColorGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFilterColorGeometry`  
`class FDMXGDTFFilterColorGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe device parts which have a color filter (XML node <FilterColor>).
- L14 _public function_ `FDMXGDTFFilterColorGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFFilterGoboGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFilterGoboGeometry`  
`class FDMXGDTFFilterGoboGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe device parts which have gobo wheels (XML node <FilterGobo>).
- L14 _public function_ `FDMXGDTFFilterGoboGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFFilterShaperGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFilterShaperGeometry`  
`class FDMXGDTFFilterShaperGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe device parts which have a shaper (XML node <FilterShaper>).
- L14 _public function_ `FDMXGDTFFilterShaperGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGeometry`  
`class FDMXGDTFGeometry : public FDMXGDTFGeometryCollectBase`  
_L17-53_
- inherits: `FDMXGDTFGeometryCollectBase`
- desc: It is a basic geometry type without specification (XML node <Geometry>). UE specific: Base class for all geometry nodes.
- L21 _public prototype_ `FDMXGDTFGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect);`
- L24 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L25 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L26 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L30 _public prototype_ `virtual TSharedPtr<FDMXGDTFGeometry> FindGeometryByName(const TCHAR* InName) const override;`
- L34 _public member_ `FName Name;` — The unique name of geometry.
- L37 _public member_ `FTransform Position;` — Relative position of geometry; Default value : Identity Matrix
- L46 _public member_ `FString Model;` — (Optional) Link to the corresponding model. The model only replaces the model of the parent of the referenced geometry. The models of the children of the referenced geometry are not affected. The starting point is Models Collect. If model is not set, the model is taken from the referenced geometry.
- L49 _public member_ `const TWeakPtr<FDMXGDTFGeometryCollectBase> OuterGeometryCollect;` — The outer geometry collect
- L52 _public prototype_ `TSharedPtr<FDMXGDTFModel> ResolveModel() const;` — Resolves the linked model. Returns the model, or nullptr if no model is linked

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFGeometryBreak.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGeometryBreak`  
`class FDMXGDTFGeometryBreak : public FDMXGDTFNode`  
_L13-33_
- inherits: `FDMXGDTFNode`
- desc: This XML node specifies the DMX offset for the DMX channel of the referenced geometry (XML node <Break>)
- L17 _public prototype_ `FDMXGDTFGeometryBreak(const TSharedRef<FDMXGDTFGeometryReference>& InGeometryReference);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `FDMXGDTFDMXAddress DMXOffset;` — DMX offset; Default value:1 (Means no offset for the corresponding DMX Channel)
- L29 _public member_ `uint8 DMXBreak = 1;` — Defines the unique number of the DMX Break for which the Offset is given. Size: 1 byte; Default value 1
- L32 _public member_ `const TWeakPtr<FDMXGDTFGeometryReference> OuterGeometryReference;` — The outer geometry reference

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFGeometryCollect.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGeometryCollect`  
`class FDMXGDTFGeometryCollect : public FDMXGDTFGeometryCollectBase`  
_L15-29_
- inherits: `FDMXGDTFGeometryCollectBase`
- desc: The physical description of the device parts is defined in the geometry collect. Geometry collect can contain a separate geometry or a tree of geometries. The geometry collect currently does not have any XML attributes (XML node <Geometries>).
- L19 _public prototype_ `FDMXGDTFGeometryCollect(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFGeometryCollectBase.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGeometryCollectBase`  
`class FDMXGDTFGeometryCollectBase : public FDMXGDTFNode`  
_L32-230_
- inherits: `FDMXGDTFNode`
- desc: UE specific. Bases class for all classes that have a geometry collect.
- L37 _public prototype_ `virtual const TCHAR* GetXmlTag() const override;`
- L38 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L39 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L43 _public member_ `TArray<TSharedPtr<FDMXGDTFGeometry>> GeometryArray;` — Any General Geometry.
- L46 _public member_ `TArray<TSharedPtr<FDMXGDTFAxisGeometry>> AxisArray;` — Any Geometry with axis.
- L49 _public member_ `TArray<TSharedPtr<FDMXGDTFFilterBeamGeometry>> FilterBeamArray;` — Any Geometry with a beam filter.
- L52 _public member_ `TArray<TSharedPtr<FDMXGDTFFilterColorGeometry>> FilterColorArray;` — Any Geometry with color filter.
- L55 _public member_ `TArray<TSharedPtr<FDMXGDTFFilterGoboGeometry>> FilterGoboArray;` — Any Geometry with gobo.
- L58 _public member_ `TArray<TSharedPtr<FDMXGDTFFilterShaperGeometry>> FilterShaperArray;` — Any Geometry with shaper.
- L61 _public member_ `TArray<TSharedPtr<FDMXGDTFBeamGeometry>> BeamArray;` — ny Geometry that describes a light output to project.
- L64 _public member_ `TArray<TSharedPtr<FDMXGDTFMediaServerLayerGeometry>> MediaServerLayerArray;` — Any Geometry that describes a media representation layer of a media device.
- L67 _public member_ `TArray<TSharedPtr<FDMXGDTFMediaServerCameraGeometry>> MediaServerCameraArray;` — Any Geometry that describes a camera or output layer of a media device.
- L70 _public member_ `TArray<TSharedPtr<FDMXGDTFMediaServerMasterGeometry>> MediaServerMasterArray;` — Any Geometry that describes a master control layer of a media device.
- L73 _public member_ `TArray<TSharedPtr<FDMXGDTFDisplayGeometry>> DisplayArray;` — Any Geometry that describes a surface to display visual media.
- L76 _public member_ `TArray<TSharedPtr<FDMXGDTFGeometryReference>> GeometryReferenceArray;` — Any Reference to already described geometries.
- L79 _public member_ `TArray<TSharedPtr<FDMXGDTFLaserGeometry>> LaserArray;` — Any Geometry with a laser light output.
- L82 _public member_ `TArray<TSharedPtr<FDMXGDTFWiringObjectGeometry>> WiringObjectArray;` — Any General Geometry.
- L85 _public member_ `TArray<TSharedPtr<FDMXGDTFInventoryGeometry>> InventoryArray;` — Any Geometry that describes an additional item that can be used for a fixture (like a rain cover).
- L88 _public member_ `TArray<TSharedPtr<FDMXGDTFStructureGeometry>> StructureArray;` — Any Geometry that describes the internal framing of an object (like members).
- L91 _public member_ `TArray<TSharedPtr<FDMXGDTFSupportGeometry>> SupportArray;` — Any Geometry that describes a support like a base plate or a hoist.
- L94 _public member_ `TArray<TSharedPtr<FDMXGDTFMagnetGeometry>> MagnetArray;` — Any Geometry that describes a point where other geometries should be attached
- L97 _public prototype_ `void GetGeometriesRecursive(TArray<TSharedPtr<FDMXGDTFGeometry>>& OutGeometries, TArray<TSharedPtr<FDMXGDTFGeometryReference>>& OutGeometryReferences);` — Returns all child geometries. Does not include self.
- L100 _public prototype_ `virtual TSharedPtr<FDMXGDTFGeometry> FindGeometryByName(const TCHAR* InName) const;` — Finds the geometry by name.
- L103 _public prototype_ `TSharedPtr<FDMXGDTFGeometryReference> FindGeometryReferenceByName(const TCHAR* InName) const;` — Finds geometry references by name.
- L111 _public function_ `template <typename GeometryType> TSharedPtr<GeometryType> ResolveGeometryLink(const FString& Link) const` — Resolves a string as a link to a geometry. The string needs to be formated in the form of "Geometry1.Geometry2.[...].GeometryN" whereas Geometry1 resides in the geometry collect of the fixture type.
- L148 _public function_ `template <typename GeometryType> void GetGeometriesOfType(TArray<TSharedPtr<GeometryType>>& OutArray) const` — Returns all geometries of a specific type in this collect. Example: TArray<FDMXGDTFBeamGeometry> BeamGeometries; MyGeometryCollect->GetGeometriesOfType(BeamGeometries); // Returns all beam geometries

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFGeometryReference.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGeometryReference`  
`class FDMXGDTFGeometryReference : public FDMXGDTFNode`  
_L19-67_
- inherits: `FDMXGDTFNode`
- desc: The Geometry Type Reference is used to describe multiple instances of the same geometry. Example: LED panel with multiple pixels. (XML node <GeometryReference>).
- L23 _public prototype_ `FDMXGDTFGeometryReference(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect);`
- L26 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L27 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L28 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `FName Name;` — The unique name of geometry.
- L35 _public member_ `FTransform Position;` — Relative position of geometry; Default value : Identity Matrix
- L38 _public member_ `FName Geometry;` — The referenced geometry. Only top level geometries are allowed to be referenced
- L47 _public member_ `FName Model;` — (Optional) Link to the corresponding model. The model only replaces the model of the parent of the referenced geometry. The models of the children of the referenced geometry are not affected. The starting point is Models Collect. If model is not set, the model is taken from the referenced geometry.
- L57 _public member_ `TArray<TSharedPtr<FDMXGDTFGeometryBreak>> BreakArray;` — As children, the Geometry Type Reference has a list of a breaks. The count of the children depends on the number of different breaks in the DMX channels of the referenced geometry. If the referenced geometry, for example, has DMX channels with DMX break 2 and 4, the geometry reference has to have 2 children. The first child with DMX offset for DMX break 2 and the second child for DMX break 4. If one or more of the DMX channels of the referenced geometry have the special value “Overwrite” as a DMX break, the DMX break for those channels and the DMX offsets need to be defined
- L60 _public member_ `const TWeakPtr<FDMXGDTFGeometryCollectBase> OuterGeometryCollect;` — The outer geometry collect
- L63 _public prototype_ `TSharedPtr<FDMXGDTFGeometry> ResolveGeometry() const;` — Resolves the linked geometry. Returns the geometry, or nullptr if no geometry is linked
- L66 _public prototype_ `TSharedPtr<FDMXGDTFModel> ResolveModel() const;` — Resolves the linked model. Returns the model, or nullptr if no model is linked

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFInventoryGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFInventoryGeometry`  
`class FDMXGDTFInventoryGeometry : public FDMXGDTFGeometry`  
_L10-26_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe a geometry used for the inventory (XML node <Inventory>).
- L14 _public function_ `FDMXGDTFInventoryGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `int32 Count = 1;` — The default count for new objects.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFLaserGeometry.h` (Public)


#### enum `EDMXLaserGeometryColorType`  
`enum class EDMXLaserGeometryColorType`  
_L12-19_
- reflection: `UENUM()`
- desc: Color type of a Laser Geometry. The currently defined unit values are: “RGB”, “SingleWaveLength”, Default: RGB
- L14 _public enumerator_ `RGB`
- L15 _public enumerator_ `SingleWaveLength`
- L18 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFLaserGeometry`  
`class FDMXGDTFLaserGeometry : public FDMXGDTFGeometry`  
_L29-78_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe the position of a laser’s light output (XML node <Laser>)
- L33 _public function_ `FDMXGDTFLaserGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L38 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L39 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L40 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L44 _public member_ `EDMXLaserGeometryColorType ColorType = EDMXLaserGeometryColorType::RGB;` — Color type of a Laser
- L47 _public member_ `float Color = 0.f;` — Required if ColorType is “SingleWaveLength”; Unit:nm (nanometers)
- L50 _public member_ `float OutputStrength = 0.f;` — Output Strength of the Laser; Unit: Watt
- L53 _public member_ `FString Emitter;` — (Optional) link to the emitter group. The starting point is the Emitter Collect.
- L56 _public member_ `float BeamDiameter = 0.f;` — Beam diameter where it leaves the projector; Unit: meter
- L59 _public member_ `float BeamDivergenceMin = 0.f;` — Minimum beam divergence; Unit: mrad (milliradian)
- L62 _public member_ `float BeamDivergenceMax = 0.f;` — Maximum beam divergence; Unit: mrad (milliradian)
- L65 _public member_ `float ScanAnglePan = 0.f;` — Possible Total Scan Angle Pan of the beam. Assumes symmetrical output; Unit: Degree
- L68 _public member_ `float ScanAngleTilt = 0.f;` — Possible Total Scan Angle Tilt of the beam. Assumes symmetrical output; Unit: Degree
- L71 _public member_ `float ScanSpeed = 0.f;` — Speed of the beam; Unit: kilo point per second
- L74 _public member_ `TArray<TSharedPtr<FDMXGDTFLaserProtocol>> ProtocolArray;` — A list of protocols supported by the laser
- L77 _public prototype_ `TSharedPtr<FDMXGDTFEmitter> ResolveEmitter() const;` — Resolves the linked emitter. Returns the emitter, or nullptr if no emitter is linked

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXLaserGeometryColorType, EDMXLaserGeometryColorType::MaxEnumValue);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DMX` (scope `UE`)
- L23 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFLaserProtocol.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFLaserProtocol`  
`class FDMXGDTFLaserProtocol : public FDMXGDTFNode`  
_L12-29_
- inherits: `FDMXGDTFNode`
- desc: This XML node specifies the protocol for a Laser (XML node <Protocol>)
- L16 _public prototype_ `FDMXGDTFLaserProtocol(const TSharedRef<FDMXGDTFLaserGeometry>& InLaserGeometry);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `FString Name;` — Name of the protocol
- L28 _public member_ `const TWeakPtr<FDMXGDTFLaserGeometry> OuterLaserGeometry;` — The outer laser geometry

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFMagnetGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMagnetGeometry`  
`class FDMXGDTFMagnetGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe a magnet, a point where other geometries should be attached (XML node <Magnet>).
- L14 _public function_ `FDMXGDTFMagnetGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFMediaServerCameraGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMediaServerCameraGeometry`  
`class FDMXGDTFMediaServerCameraGeometry : public FDMXGDTFGeometry`  
_L10-17_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe the layer of a media device that is used for representation of media files (XML node <MediaServerLayer>).
- L14 _public function_ `FDMXGDTFMediaServerCameraGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFMediaServerLayerGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMediaServerLayerGeometry`  
`class FDMXGDTFMediaServerLayerGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe the layer of a media device that is used for representation of media files (XML node <MediaServerLayer>).
- L14 _public function_ `FDMXGDTFMediaServerLayerGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFMediaServerMasterGeometry.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMediaServerMasterGeometry`  
`class FDMXGDTFMediaServerMasterGeometry : public FDMXGDTFGeometry`  
_L10-21_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe the master control of one or several media devices (XML node <MediaServerMaster>).
- L14 _public function_ `FDMXGDTFMediaServerMasterGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFStructureGeometry.h` (Public)


#### enum `EDMXGDTFStructureGeometryType`  
`enum class EDMXGDTFStructureGeometryType : uint8`  
_L13-20_
- reflection: `UENUM()`
- desc: The type of structure. Defined values are “CenterLineBased”, “Detail”.
- L15 _public enumerator_ `CenterLineBased`
- L16 _public enumerator_ `Detail`
- L19 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### enum `EDMXGDTFStructureGeometryCrossSectionType`  
`enum class EDMXGDTFStructureGeometryCrossSectionType : uint8`  
_L26-33_
- reflection: `UENUM()`
- desc: The type of cross section. Defined values are “TrussFramework”, “Tube”.
- L28 _public enumerator_ `TrussFramework`
- L29 _public enumerator_ `Tube`
- L32 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFStructureGeometry`  
`class FDMXGDTFStructureGeometry : public FDMXGDTFGeometry`  
_L40-74_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe a structure (XML node <Structure>).
- L44 _public function_ `FDMXGDTFStructureGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L49 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L50 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L51 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L55 _public member_ `FString LinkedGeometry;` — The linked geometry
- L58 _public member_ `EDMXGDTFStructureGeometryType StructureType = EDMXGDTFStructureGeometryType::CenterLineBased;` — The type of structure.
- L61 _public member_ `EDMXGDTFStructureGeometryCrossSectionType CrossSectionType = EDMXGDTFStructureGeometryCrossSectionType::TrussFramework;` — The type of cross section.
- L64 _public member_ `float CrossSectionHeight = 0.f;` — The height of the cross section. Only for Tubes. Unit: meter
- L67 _public member_ `float CrossSectionWallThickness = 0.f;` — The thickness of the wall of the cross section. Only for Tubes. Unit: meter.
- L70 _public member_ `FString TrussCrossSection;` — The name of the truss cross section. Only for Trusses.
- L73 _public prototype_ `TSharedPtr<FDMXGDTFGeometry> ResolveLinkedGeometry() const;` — Resolves the linked geometry. Returns the geometry, or nullptr if no geometry is linked

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFStructureGeometryType, EDMXGDTFStructureGeometryType::MaxEnumValue);`
- L35 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFStructureGeometryCrossSectionType, EDMXGDTFStructureGeometryCrossSectionType::MaxEnumValue);`
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace DMX` (scope `UE`)
- L37 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFSupportGeometry.h` (Public)


#### enum `EDMXGDTFGeometrySupportType`  
`enum class EDMXGDTFGeometrySupportType : uint8`  
_L12-19_
- reflection: `UENUM()`
- desc: The type of support. Defined values are “Rope”, “GroundSupport”.
- L14 _public enumerator_ `Rope`
- L15 _public enumerator_ `GroundSupport`
- L18 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFSupportGeometry`  
`class FDMXGDTFSupportGeometry : public FDMXGDTFGeometry`  
_L26-84_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe a support (XML node <Support>).
- L30 _public function_ `FDMXGDTFSupportGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L35 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L36 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L37 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L41 _public member_ `EDMXGDTFGeometrySupportType SupportType = EDMXGDTFGeometrySupportType::Rope;` — The type of support
- L44 _public member_ `FString RopeCrossSection;` — The name of the rope cross section. Only for Ropes.
- L47 _public member_ `FVector RopeOffset = FVector::ZeroVector;` — The Offset of the rope from bottom to top. Only for Ropes. Unit: meter
- L50 _public member_ `float CapacityX = 0.f;` — The allowable force on the X-Axis applied to the object according to the Eurocode. Unit: N.
- L53 _public member_ `float CapacityY = 0.f;` — The allowable force on the Y-Axis applied to the object according to the Eurocode. Unit: N.
- L56 _public member_ `float CapacityZ = 0.f;` — The allowable force on the Z-Axis applied to the object according to the Eurocode. Unit: N.
- L59 _public member_ `float CapacityXX = 0.f;` — The allowable moment around the X-Axis applied to the object according to the Eurocode. Unit: N/m.
- L62 _public member_ `float CapacityYY = 0.f;` — The allowable moment around the Y-Axis applied to the object according to the Eurocode. Unit: N/m.
- L65 _public member_ `float CapacityZZ = 0.f;` — The allowable moment around the Z-Axis applied to the object according to the Eurocode. Unit: N/m.
- L68 _public member_ `float ResistanceX = 0.f;` — The compression ratio for this support along the X-Axis. Unit N/m. Only for Ground Supports.
- L71 _public member_ `float ResistanceY = 0.f;` — The compression ratio for this support along the Y-Axis. Unit N/m. Only for Ground Supports.
- L74 _public member_ `float ResistanceZ = 0.f;` — The compression ratio for this support along the Z-Axis. Unit N/m. Only for Ground Supports.
- L77 _public member_ `float ResistanceXX = 0.f;` — The compression ratio for this support around the X-Axis. Unit N/m. Only for Ground Supports.
- L80 _public member_ `float ResistanceYY = 0.f;` — The compression ratio for this support around the Y-Axis. Unit N/m. Only for Ground Supports.
- L83 _public member_ `float ResistanceZZ = 0.f;` — The compression ratio for this support around the Z-Axis. Unit N/m. Only for Ground Supports.

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFGeometrySupportType, EDMXGDTFGeometrySupportType::MaxEnumValue);`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DMX` (scope `UE`)
- L23 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFWiringObjectGeometry.h` (Public)


#### enum `EDMXWiringObjectGeometryComponentType`  
`enum class EDMXWiringObjectGeometryComponentType : uint8`  
_L17-31_
- reflection: `UENUM()`
- desc: The type of the electrical component used. Defined values are “Input”, “Output”, “PowerSource”, “Consumer”, “Fuse”, “NetworkProvider”, “NetworkInput”, “NetworkOutput”, “NetworkInOut”.
- L19 _public enumerator_ `Input`
- L20 _public enumerator_ `Output`
- L21 _public enumerator_ `PowerSource`
- L22 _public enumerator_ `Consumer`
- L23 _public enumerator_ `Fuse`
- L24 _public enumerator_ `NetworkProvider`
- L25 _public enumerator_ `NetworkInput`
- L26 _public enumerator_ `NetworkOutput`
- L27 _public enumerator_ `NetworkInOut`
- L30 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### enum `EDMXWiringObjectGeometryFuseRating`  
`enum class EDMXWiringObjectGeometryFuseRating : uint8`  
_L36-46_
- reflection: `UENUM()`
- desc: Fuse Rating.Defined values are “B”, “C”, “D”, “K”, “Z”.
- L38 _public enumerator_ `B`
- L39 _public enumerator_ `C`
- L40 _public enumerator_ `D`
- L41 _public enumerator_ `K`
- L42 _public enumerator_ `Z`
- L45 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### enum `EDMXWiringObjectGeometryOrientation`  
`enum class EDMXWiringObjectGeometryOrientation : uint8`  
_L51-60_
- reflection: `UENUM()`
- desc: Where the pins are placed on the object.Defined values are “Left”, “Right”, “Top”, “Bottom”.
- L53 _public enumerator_ `Left`
- L54 _public enumerator_ `Right`
- L55 _public enumerator_ `Top`
- L56 _public enumerator_ `Bottom`
- L59 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFWiringObjectGeometry`  
`class FDMXGDTFWiringObjectGeometry : public FDMXGDTFGeometry`  
_L68-156_
- inherits: `FDMXGDTFGeometry`
- desc: This type of geometry is used to describe an electrical device that can be wired (XML node <WiringObject>).
- L72 _public function_ `FDMXGDTFWiringObjectGeometry(const TSharedRef<FDMXGDTFGeometryCollectBase>& InGeometryCollect) : FDMXGDTFGeometry(InGeometryCollect)`
- L77 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L78 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L79 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L83 _public member_ `FString Model;` — Link to the corresponding model.
- L90 _public member_ `FName ConnectorType;` — The type of the connector.Find a list of predefined types in Annex D.This is not applicable for Component Types Fuses. Custom type of connector can also be defined, for example “Loose End”.
- L93 _public member_ `FTransform Matrix = FTransform::Identity;` — Relative position of geometry
- L96 _public member_ `EDMXWiringObjectGeometryComponentType ComponentType = EDMXWiringObjectGeometryComponentType::Input;` — The type of the electrical component used
- L103 _public member_ `FString SignalType;` — The type of the signal used.Predefinded values are “Power”, “DMX512”, “Protocol”, “AES”, “AnalogVideo”, “AnalogAudio”.When you have a custom protocol, you can add it here.
- L106 _public member_ `int32 PinCount = 0;` — The number of available pins of the connector type to connect internal wiring to it.
- L109 _public member_ `float ElectricalPayLoad = 0.f;` — The electrical consumption in Watts.Only for Consumers.Unit: Watt.
- L112 _public member_ `float VoltageRangeMax = 0.f;` — The voltage range’s maximum value.Only for Consumers.Unit: volt.
- L115 _public member_ `float VoltageRangeMin = 0.f;` — The voltage range’s minimum value.Only for Consumers.Unit: volt.
- L118 _public member_ `float FrequencyRangeMax = 0.f;` — The Frequency range’s maximum value.Only for Consumers.Unit: hertz.
- L121 _public member_ `float FrequencyRangeMin = 0.f;` — The Frequency range’s minimum value.Only for Consumers.Unit: hertz.
- L124 _public member_ `float MaxPayLoad = 0.f;` — The maximum electrical payload that this power source can handle. Only for Power Sources. Unit: voltampere.
- L127 _public member_ `float Voltage = 0.f;` — he voltage output that this power source can handle. Only for Power Sources.Unit : volt.
- L134 _public member_ `int32 SignalLayer = 0;` — The layer of the Signal Type. In one device, all wiring geometry that use the same Signal Layers are connected.Special value 0 : Connected to all geometries.
- L137 _public member_ `float CosPhi = 0.f;` — The Power Factor of the device. Only for consumers.
- L140 _public member_ `float FuseCurrent = 0.f;` — The fuse value.Only for fuses. Unit: ampere.
- L143 _public member_ `EDMXWiringObjectGeometryFuseRating FuseRating = EDMXWiringObjectGeometryFuseRating::B;` — Fuse Rating
- L146 _public member_ `EDMXWiringObjectGeometryOrientation Orientation = EDMXWiringObjectGeometryOrientation::Left;` — Where the pins are placed on the object
- L149 _public member_ `FString WireGroup;` — Name of the group to which this wiring object belong
- L152 _public member_ `TArray<TSharedPtr<FDMXGDTFWiringObjectPinPatch>> PinPatchArray;` — The wiring object has pin patch children.
- L155 _public prototype_ `TSharedPtr<FDMXGDTFModel> ResolveModel() const;` — Resolves the linked model. Returns the model, or nullptr if no model is linked

#### Free symbols / members of external scopes

- L32 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXWiringObjectGeometryComponentType, EDMXWiringObjectGeometryComponentType::MaxEnumValue);`
- L47 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXWiringObjectGeometryFuseRating, EDMXWiringObjectGeometryFuseRating::MaxEnumValue);`
- L61 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXWiringObjectGeometryOrientation, EDMXWiringObjectGeometryOrientation::MaxEnumValue);`
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace DMX` (scope `UE`)
- L63 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Geometries/DMXGDTFWiringObjectPinPatch.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFWiringObjectPinPatch`  
`class FDMXGDTFWiringObjectPinPatch : public FDMXGDTFNode`  
_L15-41_
- inherits: `FDMXGDTFNode`
- desc: This node (XML node <PinPatch>) specifies how the different sockets of its parent wiring object are connected to the pins of other wiring objects
- L19 _public prototype_ `FDMXGDTFWiringObjectPinPatch(const TSharedRef<FDMXGDTFWiringObjectGeometry>& InWiringObjectGeometry);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `FString ToWiringObject;` — Link to the wiring object connected through this pin patch.
- L31 _public member_ `uint32 FromPin = 0;` — The pin number used by the parent wiring object to connect to the targeted wiring object “ToWiringObject”.
- L34 _public member_ `uint32 ToPin = 0;` — The pin number used by the targeted wiring object “ToWiringObject” to connect to the parent wiring object
- L37 _public member_ `const TWeakPtr<FDMXGDTFWiringObjectGeometry> OuterWiringObjectGeometry;` — The outer wiring object geometry
- L40 _public prototype_ `TSharedPtr<FDMXGDTFWiringObjectGeometry> ResolveToWiringObject() const;` — Resolves the linked to wiring object. Returns the to wiring object, or nullptr if no to wiring object is linked

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Models/DMXGDTFModel.h` (Public)


#### enum `EDMXGDTFModelPrimitiveType`  
`enum class EDMXGDTFModelPrimitiveType : uint8`  
_L18-36_
- reflection: `UENUM()`
- desc: Type of 3D model; The currently defined values are: “Undefined”, “Cube”, “Cylinder”, “Sphere”, “Base”, “Yoke”, “Head”, “Scanner”, “Conventional”, “Pigtail”, “Base1_1”, “Scanner1_1”, “Conventional1_1”; Default value: “Undefined"
- L20 _public enumerator_ `Undefined UMETA(DisplayName = "Undefined")`
- L21 _public enumerator_ `Cube UMETA(DisplayName = "Cube")`
- L22 _public enumerator_ `Cylinder UMETA(DisplayName = "Cylinder")`
- L23 _public enumerator_ `Sphere UMETA(DisplayName = "Sphere")`
- L24 _public enumerator_ `Base UMETA(DisplayName = "Base")`
- L25 _public enumerator_ `Yoke UMETA(DisplayName = "Yoke")`
- L26 _public enumerator_ `Head UMETA(DisplayName = "Head")`
- L27 _public enumerator_ `Scanner UMETA(DisplayName = "Scanner")`
- L28 _public enumerator_ `Conventional UMETA(DisplayName = "Conventional")`
- L29 _public enumerator_ `Pigtail UMETA(DisplayName = "Pigtail")`
- L30 _public enumerator_ `Base1_1 UMETA(DisplayName = "Base1_1")`
- L31 _public enumerator_ `Scanner1_1 UMETA(DisplayName = "Scanner1_1")`
- L32 _public enumerator_ `Conventional1_1 UMETA(DisplayName = "Conventional1_1")`
- L35 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFModel`  
`class FDMXGDTFModel : public FDMXGDTFNode`  
_L48-98_
- inherits: `FDMXGDTFNode`
- desc: Each device is divided into smaller parts: body, yoke, head and so on. These are called geometries. Each geometry has a separate model description and a physical description. Model collect contains model descriptions of the fixture parts. The model collect currently does not have any XML attributes (XML node <Models>).
- L52 _public prototype_ `FDMXGDTFModel(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L55 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L56 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L57 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L61 _public member_ `FName Name;` — The unique name of the model.
- L64 _public member_ `float Length = 0.0;` — Length. Unit: meter; Default value: 0
- L67 _public member_ `float Width = 0.0;` — Width. Unit: meter; Default value: 0
- L70 _public member_ `float Height = 0.0;` — Height. Unit: meter; Default value: 0
- L73 _public member_ `EDMXGDTFModelPrimitiveType PrimitiveType = EDMXGDTFModelPrimitiveType::Undefined;` — Type of 3D model. Default value: “Undefined
- L76 _public member_ `FString File;` — (Optional) File name without extension and without subfolder containing description of the model.
- L79 _public member_ `float SVGOffsetX = 0.f;` — Offset in X from the 0, 0 point to the desired insertion point of the top view svg. Unit based on the SVG. Default value: 0
- L82 _public member_ `float SVGOffsetY = 0.f;` — Offset in Y from the 0, 0 point to the desired insertion point of the top view svg. Unit based on the SVG. Default value: 0
- L85 _public member_ `float SVGSideOffsetX = 0.f;` — Offset in X from the 0,0 point to the desired insertion point of the side view svg. Unit based on the SVG. Default value: 0
- L88 _public member_ `float SVGSideOffsetY = 0.f;` — Offset in Y from the 0,0 point to the desired insertion point of the side view svg. Unit based on the SVG. Default value: 0
- L91 _public member_ `float SVGFrontOffsetX = 0.f;` — Offset in X from the 0,0 point to the desired insertion point of the front view svg. Unit based on the SVG. Default value: 0
- L94 _public member_ `float SVGFrontOffsetY = 0.f;` — Offset in Y from the 0,0 point to the desired insertion point of the front view svg. Unit based on the SVG. Default value: 0
- L97 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L38 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFModelPrimitiveType, EDMXGDTFModelPrimitiveType::MaxEnumValue);`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace DMX` (scope `UE`)
- L40 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFColorRenderingIndex.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFColorRenderingIndex`  
`class FDMXGDTFColorRenderingIndex : public FDMXGDTFNode`  
_L12-39_
- inherits: `FDMXGDTFNode`
- desc: This section defines the DMX ColorRenderingIndex description (XML node <ColorRenderingIndex>).
- L16 _public prototype_ `FDMXGDTFColorRenderingIndex(const TSharedRef<FDMXGDTFColorRenderingIndexGroup>& InColorRenderingIndexGroup);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `uint8 CES = 1;` — Color sample. The defined values are “CES01”, “CES02”, ... “CES99”.Default Value “CES01" UE specific: The integer value instead of an enumeration, wehre e.g. 1 corresponds to "CES01".
- L31 _public member_ `uint8 ColorRenderingIndex = 100;` — The color rendering index for this sample. Default value: 100
- L34 _public member_ `const TWeakPtr<FDMXGDTFColorRenderingIndexGroup> OuterColorRenderingIndexGroup;` — The outer color rendering index group
- L38 _private prototype_ `uint8 ParseCES(const FString& GDTFString) const;` — Parses color sample from a GDTF string

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFColorRenderingIndexGroup.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFColorRenderingIndexGroup`  
`class FDMXGDTFColorRenderingIndexGroup : public FDMXGDTFNode`  
_L15-35_
- inherits: `FDMXGDTFNode`
- desc: This section contains CRIs for a single color temperature (XML node <CRIGroup>).
- L19 _public prototype_ `FDMXGDTFColorRenderingIndexGroup(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `float ColorTemperature = 6000.f;` — Color temperature; Default value: 6000; Unit: Kelvin
- L31 _public member_ `TArray<TSharedPtr<FDMXGDTFColorRenderingIndex>> CRIArray;` — As children, the CRIGroup has an optional list of Color Rendering Index.
- L34 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFColorSpace.h` (Public)


#### enum `EDMXGDTFColorSpaceMode`  
`enum class EDMXGDTFColorSpaceMode : uint8`  
_L19-28_
- reflection: `UENUM(BlueprintType)`
- desc: Measurement interpolation to The currently defined unit values are:  "Linear", "Step", "Log"; Default: Linear
- L21 _public enumerator_ `Custom`
- L22 _public enumerator_ `sRGB`
- L23 _public enumerator_ `ProPhoto`
- L24 _public enumerator_ `ANSI`
- L27 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFColorSpace`  
`class FDMXGDTFColorSpace : public FDMXGDTFNode`  
_L37-75_
- inherits: `FDMXGDTFNode`
- desc: This section defines the description of the ColorSpace (XML node <ColorSpace>).
- L41 _public prototype_ `FDMXGDTFColorSpace(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L44 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L45 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L46 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L53 _public member_ `FName Name = "";` — Unique Name of the Color Space. Default Value : "Default". Note that the name need to be unique for the default colorspace and all color spaces in the AdditionalColorSpaces node.
- L59 _public member_ `EDMXGDTFColorSpaceMode Mode = EDMXGDTFColorSpaceMode::sRGB;` — Definition of the Color Space that used for the indirect color mixing. The defined values are "Custom", "sRGB", "ProPhoto" and "ANSI".Default Value : "sRGB"
- L62 _public member_ `FDMXGDTFColorCIE1931xyY Red;` — (Optional) CIE xyY of the Red Primary; this is used only if the ColorSpace is "Custom".
- L65 _public member_ `FDMXGDTFColorCIE1931xyY Green;` — (Optional) CIE xyY of the Green Primary; this is used only if the ColorSpace is "Custom".
- L68 _public member_ `FDMXGDTFColorCIE1931xyY Blue;` — (Optional) CIE xyY of the Blue Primary; this is used only if the ColorSpace is "Custom".
- L71 _public member_ `FDMXGDTFColorCIE1931xyY WhitePoint;` — (Optional) CIE xyY of the White Point; this is used only if the ColorSpace is "Custom".
- L74 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L30 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFColorSpaceMode, EDMXGDTFColorSpaceMode::MaxEnumValue);`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace DMX` (scope `UE`)
- L32 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFDMXProfile.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDMXProfile`  
`class FDMXGDTFDMXProfile : public FDMXGDTFNode`  
_L15-35_
- inherits: `FDMXGDTFNode`
- desc: This section defines the DMX profile description (XML node <DMXProfile>).
- L19 _public prototype_ `FDMXGDTFDMXProfile(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `FName Name;` — Unique name of the DMX profile
- L31 _public member_ `TArray<TSharedPtr<FDMXGDTFDMXProfilePoint>> PointArray;` — As children a DMX Profile has a list of point.
- L34 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFDMXProfilePoint.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFDMXProfilePoint`  
`class FDMXGDTFDMXProfilePoint : public FDMXGDTFNode`  
_L19-48_
- inherits: `FDMXGDTFNode`
- desc: This section contains points to define the DMX profile (XML node <Point>). Find the Point with the biggest DMXPercentage below or equal x. If there is none, the output is expected to be 0. Output(x) = CFC3 * (x - DMXPercent)³ + CFC2 * (x - DMXPercent)² + CFC1 * (x - DMXPercent) + CFC0
- L23 _public prototype_ `FDMXGDTFDMXProfilePoint(const TSharedRef<FDMXGDTFDMXProfile>& InDMXProfile);`
- L26 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L27 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L28 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `float DMXPercentage = 0.f;` — DMX percentage of the point; Unit: Percentage; Default value : 0
- L35 _public member_ `float CFC0 = 0.f;` — Cubic Function Coefficient for x⁰; Default value : 0
- L38 _public member_ `float CFC1 = 0.f;` — Cubic Function Coefficient for x; Default value : 0
- L41 _public member_ `float CFC2 = 0.f;` — Cubic Function Coefficient for x²; Default value : 0
- L44 _public member_ `float CFC3 = 0.f;` — Cubic Function Coefficient for x³; Default value : 0
- L47 _public member_ `const TWeakPtr<FDMXGDTFDMXProfile> OuterDMXProfile;` — The outer DMX profile

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFEmitter.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFEmitter`  
`class FDMXGDTFEmitter : public FDMXGDTFNode`  
_L16-48_
- inherits: `FDMXGDTFNode`
- desc: This section defines the description of the emitter (XML node <Emitter>).
- L20 _public prototype_ `FDMXGDTFEmitter(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `FName Name;` — Unique Name of the emitter
- L35 _public member_ `FDMXGDTFColorCIE1931xyY Color;` — Approximate absolute color point if applicable.Omit for non - visible emitters (eg., UV). For Y give relative value compared to overall output defined in property Luminous Flux of related Beam Geometry (transmissive case).
- L38 _public member_ `float DominantWaveLength;` — Required if color is omitted, otherwise it is optional. Dominant wavelength of the LED.
- L41 _public member_ `FString DiodePart;` — (Optional) Manufacturer’s part number of the diode.
- L44 _public member_ `TArray<TSharedPtr<FDMXGDTFEmitterMeasurement>> Measurements;` — As children, the Emitter has a list of measurements.
- L47 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFFilter.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFFilter`  
`class FDMXGDTFFilter : public FDMXGDTFNode`  
_L16-42_
- inherits: `FDMXGDTFNode`
- desc: This section defines the description of the filter (XML node <Filter>).
- L20 _public prototype_ `FDMXGDTFFilter(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `FName Name;` — Unique Name of the filter
- L35 _public member_ `FDMXGDTFColorCIE1931xyY Color;` — Approximate absolute color point when this filter is the only item fully inserted into the beam and the fixture is at maximum intensity. For Y give relative value compared to overall output defined in property Luminous Flux of related Beam Geometry(transmissive case).
- L38 _public member_ `TArray<TSharedPtr<FDMXGDTFFilterMeasurement>> Measurements;` — As children the Filter has a list of measurements.
- L41 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFGamut.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFGamut`  
`class FDMXGDTFGamut : public FDMXGDTFNode`  
_L15-39_
- inherits: `FDMXGDTFNode`
- desc: This section defines the color gamut of the fixture (XML node <Gamut>), which is the set of attainable colors by the fixture.
- L19 _public prototype_ `FDMXGDTFGamut(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `FName Name;` — Unique Name of the Gamut.
- L31 _public member_ `TArray<FDMXGDTFColorCIE1931xyY> Points;` — Set of points defining the vertice of the gamut's polygon.
- L34 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions
- L38 _private prototype_ `TArray<FDMXGDTFColorCIE1931xyY> ParsePoints(const FString& GDTFString) const;` — Parses points from a GDTF string

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFLegHeight.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFLegHeight`  
`class FDMXGDTFLegHeight : public FDMXGDTFNode`  
_L12-29_
- inherits: `FDMXGDTFNode`
- desc: This section defines the height of the legs (XML node <LegHeight>).
- L16 _public prototype_ `FDMXGDTFLegHeight(const TSharedRef<FDMXGDTFProperties>& InProperties);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `float Value = 0.f;` — Defines height of the legs - distance between the floor and the bottom base plate. Unit: meter. Default value: 0
- L28 _public member_ `const TWeakPtr<FDMXGDTFProperties> OuterProperties;` — The outer properties

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFMeasurement.h` (Public)


#### enum `EDMXGDTFMeasurementInterpolationTo`  
`enum class EDMXGDTFMeasurementInterpolationTo : uint8`  
_L16-24_
- reflection: `UENUM(BlueprintType)`
- desc: Measurement interpolation to The currently defined unit values are:  "Linear", "Step", "Log"; Default: Linear
- L18 _public enumerator_ `Linear`
- L19 _public enumerator_ `Step`
- L20 _public enumerator_ `Log`
- L23 _public enumerator_ `MaxEnumValue UMETA(Hidden)` — Max value. Add further elements above.

#### class `UE::DMX::GDTF::FDMXGDTFMeasurementBase`  
`class FDMXGDTFMeasurementBase : public FDMXGDTFNode`  
_L44-71_
- inherits: `FDMXGDTFNode`
- desc: The measurement defines the relation between the requested output by a control channel and the physically achieved intensity. XML node for measurement is <Measurement>. The order of the measurements corresponds to their ascending physical values. Additional definition for additive color mixing: It is assumed that the physical value 0 exists and has zero output. Additional definition for subtractive color mixing: The flag is removed with physical value 0 and it does not affect the beam. Physical value 100 is maximally inserted and affects the beam. Note 1: Some fixtures may vary in color response. These fixtures define multiple measurement points and corresponding interpolations.
- L49 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L50 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L51 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L58 _public member_ `float Physical = 0.f;` — For additive color mixing: uniquely given emitter intensity DMX percentage. Value range between > 0 and <= 100. For subtractive color mixing: uniquely given flag insertion DMX percentage. Value range between 0 and 100.
- L61 _public member_ `float LuminousIntensity = 0.f;` — Used for additive color mixing: overall candela value for the enclosed set of measurement.
- L64 _public member_ `float Transmission = 0.f;` — Used for subtractive color mixing: total amount of lighting energy passed at this insertion percentage.
- L67 _public member_ `EDMXGDTFMeasurementInterpolationTo InterpolationTo = EDMXGDTFMeasurementInterpolationTo::Linear;` — Interpolation scheme from the previous value.The currently defined values are : "Linear", "Step", "Log"; Default: Linear
- L70 _public member_ `TArray<TSharedPtr<FDMXGDTFMeasurementPoint>> MeasurementPointArray;` — As children the Measurement Collect has an optional list of a measurement point.

#### class `UE::DMX::GDTF::FDMXGDTFEmitterMeasurement`  
`class FDMXGDTFEmitterMeasurement : public FDMXGDTFMeasurementBase`  
_L74-82_
- inherits: `FDMXGDTFMeasurementBase`
- desc: Measurement for emitters
- L78 _public prototype_ `FDMXGDTFEmitterMeasurement(const TSharedRef<FDMXGDTFEmitter>& InEmitter);`
- L81 _public member_ `const TWeakPtr<FDMXGDTFEmitter> OuterEmitter;` — The outer emitter

#### class `UE::DMX::GDTF::FDMXGDTFFilterMeasurement`  
`class FDMXGDTFFilterMeasurement : public FDMXGDTFMeasurementBase`  
_L85-93_
- inherits: `FDMXGDTFMeasurementBase`
- desc: Measurement for filters
- L89 _public prototype_ `FDMXGDTFFilterMeasurement(const TSharedRef<FDMXGDTFFilter>& InEmitter);`
- L92 _public member_ `const TWeakPtr<FDMXGDTFFilter> OuterFilter;` — The outer filter

#### Free symbols / members of external scopes

- L26 _prototype_ `ENUM_RANGE_BY_COUNT(EDMXGDTFMeasurementInterpolationTo, EDMXGDTFMeasurementInterpolationTo::MaxEnumValue);`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DMX` (scope `UE`)
- L28 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFMeasurementPoint.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFMeasurementPoint`  
`class FDMXGDTFMeasurementPoint : public FDMXGDTFNode`  
_L17-37_
- inherits: `FDMXGDTFNode`
- desc: The measurement point defines the energy of a specific wavelength of a spectrum. The XML node for measurement point is <MeasurementPoint>. It is recommended, but not required, that measurement points are evenly spaced. Regions with minimal light energy can be omitted, but the decisive range of spectrum must be included. Recommended measurement spacing is 1 nm. Measurement spacing should not exceed 4 nm.
- L21 _public prototype_ `FDMXGDTFMeasurementPoint(const TSharedRef<FDMXGDTFMeasurementBase>& InMeasurement);`
- L24 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L25 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L26 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L30 _public member_ `float WaveLength;` — Center wavelength of measurement(nm).
- L33 _public member_ `float Energy;` — Lighting energy(W / m2 / nm)
- L36 _public member_ `const TWeakPtr<FDMXGDTFMeasurementBase> OuterMeasurement;` — The outer measurement

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFOperatingTemperature.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFOperatingTemperature`  
`class FDMXGDTFOperatingTemperature : public FDMXGDTFNode`  
_L12-32_
- inherits: `FDMXGDTFNode`
- desc: This section defines the description of the OperatingTemperature (XML node <OperatingTemperature>).
- L16 _public prototype_ `FDMXGDTFOperatingTemperature(const TSharedRef<FDMXGDTFProperties>& InProperties);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `float Low = 0.f;` — Lowest temperature the device can be operated.Unit: °C. Default value: 0
- L28 _public member_ `float High = 40.f;` — Highest temperature the device can be operated.Unit: °C. Default value: 40
- L31 _public member_ `const TWeakPtr<FDMXGDTFProperties> OuterProperties;` — The outer properties

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFPhysicalDescriptions.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFPhysicalDescriptions`  
`class FDMXGDTFPhysicalDescriptions : public FDMXGDTFNode`  
_L20-66_
- inherits: `FDMXGDTFNode`
- desc: This section describes the physical constitution of the device. It currently does not have any XML Attributes (XML node <PhysicalDescriptions>).
- L24 _public prototype_ `FDMXGDTFPhysicalDescriptions(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L27 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L28 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L29 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L37 _public member_ `TArray<TSharedPtr<FDMXGDTFEmitter>> Emitters;` — This section contains the description of the emitters. Emitter Collect defines additive mixing of light sources, such as LEDs and tungsten lamps with permanently fitted filters. It currently does not have any XML Attributes (XML node <Emitters>).
- L44 _public member_ `TArray<TSharedPtr<FDMXGDTFFilter>> Filters;` — This section contains the description of the filters. The Filter Collect defines subtractive mixing of light sources by filters, such as subtractive mixing flags and media used in physical or virtual Color Wheels. It currently does not have any XML Attributes (XML node <Filters>).
- L47 _public member_ `TSharedPtr<FDMXGDTFColorSpace> ColorSpaces;` — This section defines color spaces. Currently it does not have any XML attributes (XML node <AdditionalColorSpaces>).
- L50 _public member_ `TArray<TSharedPtr<FDMXGDTFColorSpace>> AdditionalColorSpaces;` — Describes additional device color spaces.
- L53 _public member_ `TArray<TSharedPtr<FDMXGDTFGamut>> Gamuts;` — This section defines gamuts.
- L56 _public member_ `TArray<TSharedPtr<FDMXGDTFDMXProfile>> DMXProfiles;` — This section defines DMX profile descriptions.
- L59 _public member_ `TArray<TSharedPtr<FDMXGDTFColorRenderingIndexGroup>> CRIs;` — This section contains TM-30-15 Fidelity Index (Rf) for 99 color samples. Currently it does not have any XML attributes (XML node <CRIs>).
- L62 _public member_ `TSharedPtr<FDMXGDTFProperties> Properties;` — Describes physical properties of the device.
- L65 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFProperties.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFProperties`  
`class FDMXGDTFProperties : public FDMXGDTFNode`  
_L19-42_
- inherits: `FDMXGDTFNode`
- desc: This section defines the description of the Properties (XML node <Properties>). Connectors are obsolete as of GDTF 1.2 and are not implemented.
- L23 _public prototype_ `FDMXGDTFProperties(const TSharedRef<FDMXGDTFPhysicalDescriptions>& InPhysicalDescriptions);`
- L26 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L27 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L28 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `TSharedPtr<FDMXGDTFOperatingTemperature> OperatingTemperature;` — (optional) Temperature range in which the device can be operated.
- L35 _public member_ `TSharedPtr<FDMXGDTFWeight> Weight;` — (optional) Weight of the device including all accessories.
- L38 _public member_ `TSharedPtr<FDMXGDTFLegHeight> LegHeight;` — (optional) Height of the legs.
- L41 _public member_ `const TWeakPtr<FDMXGDTFPhysicalDescriptions> OuterPhysicalDescriptions;` — The outer physcial descriptions

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/PhysicalDescriptions/DMXGDTFWeight.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFWeight`  
`class FDMXGDTFWeight : public FDMXGDTFNode`  
_L12-29_
- inherits: `FDMXGDTFNode`
- desc: This section defines the overall weight of the device (XML node <Weight>).
- L16 _public prototype_ `FDMXGDTFWeight(const TSharedRef<FDMXGDTFProperties>& InProperties);`
- L19 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L20 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L21 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L25 _public member_ `float Value = 0.f;` — Weight of the device including all accessories. Unit: kilogram. Default value: 0
- L28 _public member_ `const TWeakPtr<FDMXGDTFProperties> OuterProperties;` — The outer properties

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/ArtNet/DMXGDTFProtocolArtNet.h` (Public)


#### class `UE::DMX::GDTF::ArtNet::FDMXGDTFProtocolArtNet`  
`class FDMXGDTFProtocolArtNet : public FDMXGDTFNode`  
_L16-33_
- inherits: `FDMXGDTFNode`
- desc: If the device supports the Art-Net protocol, this section defines the corresponding information (XML node <Art-Net>).
- L20 _public prototype_ `FDMXGDTFProtocolArtNet(const TSharedRef<FDMXGDTFProtocols>& InProtocols);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `TArray<TSharedPtr<FDMXGDTFProtocolArtNetDMXMap>> Maps;` — As children the Art-Net has a list of Maps.
- L32 _public member_ `const TWeakPtr<FDMXGDTFProtocols> OuterProtocols;` — The outer protocols

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L11 _namespace_ `namespace ArtNet` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/DMXGDTFProtocolDMXMap.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFProtocolDMXMapBase`  
`class FDMXGDTFProtocolDMXMapBase : public FDMXGDTFNode`  
_L13-28_
- inherits: `FDMXGDTFNode`
- desc: To define a custom mapping between Streaming ACN values and DMX Stream values you can add an XML node <Map> as a child. By default, it is assumed that all the values are mapped 1:1, so only when you differ from that you can add a custom map.
- L18 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L19 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L20 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L24 _public member_ `uint16 Key = 0;` — Value of the protocol value.
- L27 _public member_ `uint16 Value = 0;` — Value of the DMX value.

#### class `UE::DMX::GDTF::ArtNet::FDMXGDTFProtocolArtNetDMXMap`  
`class FDMXGDTFProtocolArtNetDMXMap : public FDMXGDTFProtocolDMXMapBase`  
_L34-41_
- inherits: `FDMXGDTFProtocolDMXMapBase`
- L38 _public prototype_ `FDMXGDTFProtocolArtNetDMXMap(const TSharedRef<ArtNet::FDMXGDTFProtocolArtNet>& InProtocolArtNet);`
- L40 _public member_ `const TWeakPtr<FDMXGDTFProtocolArtNet> OuterProtocolArtNet;`

#### class `UE::DMX::GDTF::SACN::FDMXGDTFProtocolSACNDMXMap`  
`class FDMXGDTFProtocolSACNDMXMap : public FDMXGDTFProtocolDMXMapBase`  
_L48-55_
- inherits: `FDMXGDTFProtocolDMXMapBase`
- L52 _public prototype_ `FDMXGDTFProtocolSACNDMXMap(const TSharedRef<FDMXGDTFProtocolSACN>& InProtocolArtNet);`
- L54 _public member_ `const TWeakPtr<FDMXGDTFProtocolSACN> OuterProtocolSACN;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L30 _namespace_ `namespace ArtNet` (scope `UE::DMX::GDTF`)
- L44 _namespace_ `namespace SACN` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/DMXGDTFProtocols.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFProtocols`  
`class FDMXGDTFProtocols : public FDMXGDTFNode`  
_L15-38_
- inherits: `FDMXGDTFNode`
- desc: This section defines the overall Protocols of the device (XML node <Protocols>).
- L19 _public prototype_ `FDMXGDTFProtocols(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L28 _public member_ `TSharedPtr<RDM::FDMXGDTFProtocolFTRDM> RDM;` — Describes RDM information
- L31 _public member_ `TSharedPtr<ArtNet::FDMXGDTFProtocolArtNet> ArtNet;` — Describes Art-Net information
- L34 _public member_ `TSharedPtr<SACN::FDMXGDTFProtocolSACN> sACN;` — Describes sACN information
- L37 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L10 _namespace_ `namespace RDM` (scope `UE::DMX::GDTF`)
- L11 _namespace_ `namespace ArtNet` (scope `UE::DMX::GDTF`)
- L12 _namespace_ `namespace SACN` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/RDM/DMXGDTFDMXPersonality.h` (Public)


#### class `UE::DMX::GDTF::RDM::FDMXGDTFDMXPersonality`  
`class FDMXGDTFDMXPersonality : public FDMXGDTFNode`  
_L16-39_
- inherits: `FDMXGDTFNode`
- desc: For each supported software version add an XML node <DMXPersonality>..
- L20 _public prototype_ `FDMXGDTFDMXPersonality(const TSharedRef<FDMXGDTFSoftwareVersionID>& InSoftwareVersionID);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `uint32 Value = 0;` — Hex Value of the DMXPersonality
- L32 _public member_ `FName DMXMode;` — Link to the DMX Mode that can be used with this software version.
- L35 _public prototype_ `TSharedPtr<FDMXGDTFDMXMode> ResolveDMXMode() const;` — Resolves the linked DMX mode. Returns the DMX mode, or nullptr if no DMX mode is linked.
- L38 _public member_ `const TWeakPtr<FDMXGDTFSoftwareVersionID> OuterSoftwareVersionID;` — The outer protocols

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L11 _namespace_ `namespace RDM` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/RDM/DMXGDTFProtocolFTRDM.h` (Public)


#### class `UE::DMX::GDTF::RDM::FDMXGDTFProtocolFTRDM`  
`class FDMXGDTFProtocolFTRDM : public FDMXGDTFNode`  
_L14-37_
- inherits: `FDMXGDTFNode`
- desc: This section defines the overall ProtocolRDM of the device (XML node <ProtocolRDM>).
- L18 _public prototype_ `FDMXGDTFProtocolFTRDM(const TSharedRef<FDMXGDTFProtocols>& InProtocols);`
- L21 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L22 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L23 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L27 _public member_ `uint32 ManufacturerID = 0;` — Manufacturer ESTA ID
- L30 _public member_ `uint32 DeviceModelID = 0;` — Unique device model ID
- L33 _public member_ `TArray<TSharedPtr<FDMXGDTFSoftwareVersionID>> SoftwareVersionIDArray;` — As children the FTRDM has a list of SoftwareVersionID.
- L36 _public member_ `const TWeakPtr<FDMXGDTFProtocols> OuterProtocols;` — The outer protocols

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L9 _namespace_ `namespace RDM` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/RDM/DMXGDTFSoftwareVersionID.h` (Public)


#### class `UE::DMX::GDTF::RDM::FDMXGDTFSoftwareVersionID`  
`class FDMXGDTFSoftwareVersionID : public FDMXGDTFNode`  
_L13-33_
- inherits: `FDMXGDTFNode`
- desc: For each supported software version add an XML node <SoftwareVersionID>..
- L17 _public prototype_ `FDMXGDTFSoftwareVersionID(const TSharedRef<FDMXGDTFProtocolFTRDM>& InProtocolRDM);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L26 _public member_ `uint32 Value = 0;` — Software version ID
- L29 _public member_ `TArray<TSharedPtr<FDMXGDTFDMXPersonality>> DMXPersonalityArray;` — As children the SoftwareVersionID has a list of DMXPersonality.
- L32 _public member_ `const TWeakPtr<FDMXGDTFProtocolFTRDM> OuterProtocolRDM;` — The outer protocols

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L7 _namespace_ `namespace RDM` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Protocols/sACN/DMXGDTFProtocolSACN.h` (Public)


#### class `UE::DMX::GDTF::SACN::FDMXGDTFProtocolSACN`  
`class FDMXGDTFProtocolSACN : public FDMXGDTFNode`  
_L16-33_
- inherits: `FDMXGDTFNode`
- desc: If the device supports the Art-Net protocol, this section defines the corresponding information (XML node <Art-Net>).
- L20 _public prototype_ `FDMXGDTFProtocolSACN(const TSharedRef<FDMXGDTFProtocols>& InProtocols);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `TArray<TSharedPtr<FDMXGDTFProtocolSACNDMXMap>> Maps;` — As children the Art-Net has a list of Maps.
- L32 _public member_ `const TWeakPtr<FDMXGDTFProtocols> OuterProtocols;` — The outer protocols

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)
- L11 _namespace_ `namespace SACN` (scope `UE::DMX::GDTF`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Revisions/DMXGDTFRevision.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFRevision`  
`class FDMXGDTFRevision : public FDMXGDTFNode`  
_L17-47_
- inherits: `FDMXGDTFNode`
- desc: This section defines one revision of a the device type (XML node Revision>). Revisions are optional. Every time a GDTF file is uploaded to the database, a revision with the actual time and UserID is created by the database.
- L21 _public prototype_ `FDMXGDTFRevision(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L24 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L25 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L26 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L30 _public member_ `FString Text;` — User-defined text for this revision; Default value: empty
- L33 _public member_ `FDateTime Date;` — Revision date and time
- L36 _public member_ `uint32 UserID = 0;` — UserID of the user that has uploaded the GDTF file to the database; Default value: 0
- L39 _public member_ `FString ModifiedBy;` — Name of the software that modified this revision; Default value: empty
- L42 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type
- L46 _private prototype_ `FDateTime ParseDateTime(const FString& GDTFString) const;` — Parses a GDTF string as date time

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Wheels/DMXGDTFAnimationSystem.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFAnimationSystem`  
`class FDMXGDTFAnimationSystem : public FDMXGDTFNode`  
_L13-60_
- inherits: `FDMXGDTFNode`
- desc: This section can only be defined for the animation system disk and it describes the animation system behavior (XML node <AnimationSystem>).
- L17 _public prototype_ `FDMXGDTFAnimationSystem(const TSharedRef<FDMXGDTFWheelSlot>& InWheelSlot);`
- L20 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L21 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L22 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `FVector2D P1;` — First Point of the Spline describing the path of animation system in the beam in relation to the middle of the Media File; Array of two floats; Seperator of values is “,”;First Float is X-axis and second is Y-axis. UE specific: Using a FVector2D instead of an array of floats with two elements.
- L41 _public member_ `FVector2D P2;` — Second Point of the Spline describing the path of animation system in the beam in relation to the middle of the Media File; Array of two floats; Seperator of values is “,”; First Float is X-axis and second is Y-axis. UE specific: Using a FVector2D instead of an array of floats with two elements.
- L50 _public member_ `FVector2D P3;` — Third Point of the Spline describing the path of animation system in the beam in relation to the middle of the Media File; Array of two floats; Seperator of values is “,”; First Float is X-axis and second is Y-axis. UE specific: Using a FVector2D instead of an array of floats with two elements.
- L56 _public member_ `float Radius = 0.0;` — Radius of the circle that defines the section of the animation system which will be shown in the beam
- L59 _public member_ `const TWeakPtr<FDMXGDTFWheelSlot> OuterWheelSlot;` — The outer wheel slot

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L8 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Wheels/DMXGDTFPrismFacet.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFPrismFacet`  
`class FDMXGDTFPrismFacet : public FDMXGDTFNode`  
_L15-39_
- inherits: `FDMXGDTFNode`
- desc: This section can only be defined for the prism wheel slot and has a description for the prism facet (XML node <Facet>).
- L19 _public prototype_ `FDMXGDTFPrismFacet(const TSharedRef<FDMXGDTFWheelSlot>& InWheelSlot);`
- L22 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L23 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L24 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L32 _public member_ `FDMXGDTFColorCIE1931xyY Color = { 0.3127f, 0.3290f, 100.0f };` — Color of prism facet. UE specific: Using a Vector3d to store the xyY color.
- L35 _public member_ `FTransform Rotation = FTransform::Identity;` — Specify the rotation, translation and scaling for the facet.
- L38 _public member_ `const TWeakPtr<FDMXGDTFWheelSlot> OuterWheelSlot;` — The outer wheel slot

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)
- L10 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Wheels/DMXGDTFWheel.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFWheel`  
`class FDMXGDTFWheel : public FDMXGDTFNode`  
_L16-36_
- inherits: `FDMXGDTFNode`
- desc: Each wheel describes a single physical or virtual wheel of the fixture type. If the real device has wheels you can change, then all wheel configurations have to be described. Wheel has the following XML node: <Wheel>.
- L20 _public prototype_ `FDMXGDTFWheel(const TSharedRef<FDMXGDTFFixtureType>& InFixtureType);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `FName Name;` — The unique name of the wheel
- L32 _public member_ `TArray<TSharedPtr<FDMXGDTFWheelSlot>> WheelSlotArray;` — As children, Wheel has a list of wheel slots.
- L35 _public member_ `const TWeakPtr<FDMXGDTFFixtureType> OuterFixtureType;` — The outer fixture type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DMX` (scope `UE`)
- L7 _namespace_ `namespace GDTF` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXGDTF/Public/GDTF/Wheels/DMXGDTFWheelSlot.h` (Public)


#### class `UE::DMX::GDTF::FDMXGDTFWheelSlot`  
`class FDMXGDTFWheelSlot : public FDMXGDTFNode`  
_L16-56_
- inherits: `FDMXGDTFNode`
- desc: The wheel slot represents a slot on the wheel (XML node <Slot>).
- L20 _public prototype_ `FDMXGDTFWheelSlot(const TSharedRef<FDMXGDTFWheel>& InWheel);`
- L23 _public function_ `virtual const TCHAR* GetXmlTag() const override`
- L24 _public prototype_ `virtual void Initialize(const FXmlNode& XmlNode) override;`
- L25 _public prototype_ `virtual FXmlNode* CreateXmlNode(FXmlNode& Parent) override;`
- L29 _public member_ `FName Name;` — The unique name of the wheel slot
- L36 _public member_ `FDMXGDTFColorCIE1931xyY Color;` — Color of the wheel slot, Default value: {0.3127, 0.3290, 100.0} (white). For Y give relative value compared to overall output defined in property Luminous Flux of related Beam Geometry (transmissive case).
- L46 _public member_ `FString MediaFileName;` — (Optional) PNG file name without extension containing image for specific gobos etc. — Maximum resolution of picture: 1024 × 1024; — Recommended resolution of gobo: 256 × 256; — Recommended resolution of animation wheel: 256 × 256 These resource files are located in a folder called ./wheels in the zip archive. Default value: empty.
- L49 _public member_ `TArray<TSharedPtr<FDMXGDTFPrismFacet>> PrismFacetArray;` — If the wheel slot has a prism, it has to have one or several children called prism facet.
- L52 _public member_ `TSharedPtr<FDMXGDTFAnimationSystem> AnimationWheel;` — If the wheel slot has an AnimationWheel, it has to have one child called Animation Wheel.
- L55 _public member_ `const TWeakPtr<FDMXGDTFWheel> OuterWheel;` — The outer wheel

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DMX` (scope `UE`)
- L9 _namespace_ `namespace GDTF` (scope `UE::DMX`)
