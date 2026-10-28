# Plugins / WebAPIOpenAPI

- module root: `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI`
- headers: 15; symbols: 597
- symbol kinds: class=58, delegate=2, function=25, macro=2, member=315, namespace=53, prototype=135, typedef=7
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Core, CoreUObject, EditorStyle, EditorWidgets, Engine, InputCore, Json, JsonUtilities, Projects, Slate, SlateCore, UnrealEd, WebAPI, WebAPIEditor
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, Engine, Json, JsonUtilities

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/Factories/WebAPIOpenAPIFactoryBase.h` (Private)


#### class `UWebAPIOpenAPIFactoryBase`  
`class UWebAPIOpenAPIFactoryBase : public UWebAPIDefinitionFactory`  
_L12-28_
- reflection: `UCLASS(Abstract)`
- inherits: `UWebAPIDefinitionFactory`
- desc: Common base factory between Swagger and OpenAPI factories.
- L18 _public prototype_ `UWebAPIOpenAPIFactoryBase();`
- L20 _public prototype_ `virtual TFuture<bool> ImportWebAPI(UWebAPIDefinition* InDefinition, const FString& InFileName, const FString& InFileContents) override PURE_VIRTUAL(UWebAPIOpenAPIFactoryBase::ImportWebAPI, return MakeFulfilledPromise<bool>(false).GetFuture();) virtual bool IsValidFileExtension(const FString& InFileExtension) const override;`
- L26 _protected member_ `static const FName JsonFileType;`
- L27 _protected member_ `static const FName YamlFileType;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V2/WebAPISwaggerConverter.h` (Private)


#### class `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`  
`class FWebAPISwaggerSchemaConverter`  
_L30-124_
- L33 _public prototype_ `FWebAPISwaggerSchemaConverter( const TSharedPtr<const UE::WebAPI::OpenAPI::V2::FSwagger>& InSwagger, UWebAPISchema* InWebAPISchema, const TSharedRef<FWebAPIMessageLog>& InMessageLog, const FWebAPIProviderSettings& InProviderSettings);`
- L39 _public prototype_ `bool Convert();`
- L42 _public prototype_ `FString NameTransformer(const FWebAPINameVariant& InString) const;`
- L44 _public prototype_ `TObjectPtr<UWebAPITypeInfo> ResolveType(FString InJsonType, FString InTypeHint, FString InDefinitionName, const TSharedPtr<OpenAPI::V2::FSchema>& InSchema = nullptr) const;`
- L47 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPITypeInfo> ResolveType(const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName = {}, FString InJsonType = {});`
- L49 _public prototype_ `TObjectPtr<UWebAPITypeInfo> GetTypeForContentType(const FString& InContentType);`
- L52 _public prototype_ `template <typename StorageType> FString GetDefaultJsonTypeForStorage(const StorageType& InStorage);`
- L55 _public prototype_ `template <typename ObjectType> TSharedPtr<ObjectType> ResolveReference(const FString& InDefinitionName);`
- L59 _public prototype_ `template <typename ObjectType> TSharedPtr<ObjectType> ResolveReference(const Json::TJsonReference<ObjectType>& InJsonReference, FString& OutDefinitionName, bool bInCheck = true);` — Only resolves if necessary.
- L63 _public prototype_ `FWebAPINameVariant ResolvePropertyName(const TObjectPtr<UWebAPIProperty>& InProperty, const FWebAPITypeNameVariant& InPotentialName, const TOptional<bool>& bInIsArray = {});`
- L66 _public prototype_ `template <typename SchemaType> bool IsArray(const TSharedPtr<SchemaType>& InSchema);`
- L69 _public prototype_ `template <typename SchemaType, typename ModelType> static bool ConvertModelBase(const TSharedPtr<SchemaType>& InSchema, ModelType* OutModel);`
- L72 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIEnum> ConvertEnum(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InEnumTypeName = {}) const;`
- L76 _public prototype_ `template <typename SchemaType> bool PatchProperty(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPINameVariant& InPropertyName, UWebAPIProperty* OutProperty);` — Modifies an existing Property using the supplied source object.
- L80 _public prototype_ `template <typename SchemaType> bool PatchProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName, UWebAPIProperty* OutProperty);` — Modifies an existing Property using the supplied source object.
- L83 _public prototype_ `bool PatchProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const FWebAPITypeNameVariant& InPropertyTypeName, UWebAPIProperty* OutProperty);` — Modifies an existing Property using the supplied TypeInfo.
- L87 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIProperty> ConvertProperty(const TSharedPtr<SchemaType>& InSrcSchema, const TObjectPtr<UWebAPIModel>& InModel, const FWebAPINameVariant& InPropertyName = {}, const FString& InDefinitionName = {});` — Creates a new Property from the supplied source object.
- L91 _public prototype_ `template <typename SchemaType> bool PatchModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel);` — Modifies an existing Model using the supplied source object.
- L95 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIModel> ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName = {});` — Creates a new Model from the supplied source object.
- L97 _public prototype_ `bool ConvertOperationParameter(const FWebAPINameVariant& InParameterName, const TSharedPtr<OpenAPI::V2::FParameter>& InParameter, const FString& InDefinitionName, UWebAPIOperationParameter* OutParameter);`
- L99 _public prototype_ `TObjectPtr<UWebAPIParameter> ConvertParameter(const TSharedPtr<OpenAPI::V2::FParameter>& InSrcParameter);`
- L101 _public prototype_ `bool ConvertRequest(const FWebAPITypeNameVariant& InOperationName, const TSharedPtr<OpenAPI::V2::FOperation>& InOperation, UWebAPIOperationRequest* OutRequest);`
- L103 _public prototype_ `bool ConvertResponse(const FWebAPITypeNameVariant& InOperationName, uint32 InResponseCode, const TSharedPtr<OpenAPI::V2::FResponse>& InResponse, UWebAPIOperationResponse* OutResponse);`
- L105 _public prototype_ `TObjectPtr<UWebAPIOperation> ConvertOperation(const FString& InPath, const FString& InVerb, const TSharedPtr<OpenAPI::V2::FOperation>& InSrcOperation, const FWebAPITypeNameVariant& InOperationTypeName = {});`
- L107 _public prototype_ `TObjectPtr<UWebAPIService> ConvertService(const FWebAPINameVariant& InName) const;`
- L108 _public prototype_ `TObjectPtr<UWebAPIService> ConvertService(const TSharedPtr<OpenAPI::V2::FTag>& InTag) const;`
- L110 _public prototype_ `bool ConvertModels(const TMap<FString, TSharedPtr<OpenAPI::V2::FSchema>>& InSchemas, UWebAPISchema* OutSchema);`
- L111 _public prototype_ `bool ConvertParameters(const TMap<FString, TSharedPtr<OpenAPI::V2::FParameter>>& InParameters, UWebAPISchema* OutSchema);`
- L113 _public prototype_ `bool ConvertSecurity(const UE::WebAPI::OpenAPI::V2::FSwagger& InSwagger, UWebAPISchema* OutSchema);`
- L115 _public prototype_ `bool ConvertTags(const TArray<TSharedPtr<OpenAPI::V2::FTag>>& InTags, UWebAPISchema* OutSchema) const;`
- L117 _public prototype_ `bool ConvertPaths(const TMap<FString, TSharedPtr<OpenAPI::V2::FPath>>& InPaths, UWebAPISchema* OutSchema);`
- L120 _private member_ `TSharedPtr<const UE::WebAPI::OpenAPI::V2::FSwagger> InputSchema;`
- L121 _private member_ `TStrongObjectPtr<UWebAPISchema> OutputSchema;`
- L122 _private member_ `TSharedPtr<FWebAPIMessageLog> MessageLog;`
- L123 _private member_ `FWebAPIProviderSettings ProviderSettings;`
- L127 _prototype_ `template <> TSharedPtr<OpenAPI::V2::FSchema> FWebAPISwaggerSchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L130 _prototype_ `template <> TSharedPtr<OpenAPI::V2::FParameter> FWebAPISwaggerSchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L134 _prototype_ `template <> bool FWebAPISwaggerSchemaConverter::PatchModel(const TSharedPtr<OpenAPI::V2::FParameter>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel);` — Modifies an existing Model using the supplied source object.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Json` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace WebAPI` (scope `UE`)
- L20 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L20 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace WebAPI` (scope `UE`)
- L21 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L21 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace WebAPI` (scope `UE`)
- L22 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L22 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace WebAPI` (scope `UE`)
- L23 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L23 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace WebAPI` (scope `UE`)
- L24 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L24 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace WebAPI` (scope `UE`)
- L25 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L25 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace WebAPI` (scope `UE`)
- L26 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L26 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace WebAPI` (scope `UE`)
- L28 _namespace_ `namespace Swagger` (scope `UE::WebAPI`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V2/WebAPISwaggerConverter.inl` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "WebAPISwaggerConverter"`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace WebAPI` (scope `UE`)
- L12 _namespace_ `namespace Swagger` (scope `UE::WebAPI`)
- L15 _function_ `template <typename SchemaType> bool FWebAPISwaggerSchemaConverter::PatchProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName, UWebAPIProperty* OutProperty)` (scope `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`)
- L106 _function_ `template <typename SchemaType> TObjectPtr<UWebAPIProperty> FWebAPISwaggerSchemaConverter::ConvertProperty(const TSharedPtr<SchemaType>& InSrcSchema, const TObjectPtr<UWebAPIModel>& InModel, const FWebAPINameVariant& InPropertyName, const FString& InDefinitionName)` (scope `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`)
- L130 _function_ `template <typename SchemaType> bool FWebAPISwaggerSchemaConverter::PatchModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel)` (scope `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`)
- L203 _function_ `template <> inline bool FWebAPISwaggerSchemaConverter::PatchModel<OpenAPI::V2::FParameter>(const TSharedPtr<OpenAPI::V2::FParameter>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel)` (scope `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`)
- L254 _function_ `template <typename SchemaType> TObjectPtr<UWebAPIModel> FWebAPISwaggerSchemaConverter::ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName)` (scope `UE::WebAPI::Swagger::FWebAPISwaggerSchemaConverter`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V2/WebAPISwaggerFactory.h` (Private)


#### class `UWebAPISwaggerAssetData`  
`class UWebAPISwaggerAssetData : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `FString FileContents;` — `UPROPERTY()`

#### class `UWebAPISwaggerFactory`  
`class UWebAPISwaggerFactory : public UWebAPIOpenAPIFactoryBase`  
_L23-36_
- reflection: `UCLASS()`
- inherits: `UWebAPIOpenAPIFactoryBase`
- desc: Handles importing for Swagger (OpenAPI V2) files.
- L29 _public prototype_ `UWebAPISwaggerFactory();`
- L31 _public prototype_ `virtual bool CanImportWebAPI(const FString& InFileName, const FString& InFileContents) override;`
- L32 _public prototype_ `virtual TFuture<bool> ImportWebAPI(UWebAPIDefinition* InDefinition, const FString& InFileName, const FString& InFileContents) override;`
- L35 _protected member_ `TSharedPtr<FWebAPISwaggerProvider> Provider;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V3/WebAPIOpenAPIConverter.h` (Private)


#### class `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`  
`class FWebAPIOpenAPISchemaConverter`  
_L25-122_
- L28 _public prototype_ `FWebAPIOpenAPISchemaConverter( const TSharedPtr<const UE::WebAPI::OpenAPI::V3::FOpenAPIObject>& InOpenAPI, UWebAPISchema* InWebAPISchema, const TSharedRef<FWebAPIMessageLog>& InMessageLog, const FWebAPIProviderSettings& InProviderSettings);`
- L34 _public prototype_ `bool Convert();`
- L37 _public prototype_ `FString NameTransformer(const FWebAPINameVariant& InString) const;`
- L39 _public prototype_ `TObjectPtr<UWebAPITypeInfo> ResolveMappedType(const FString& InType);`
- L41 _public prototype_ `TObjectPtr<UWebAPITypeInfo> ResolveType(FString InType, FString InFormat, FString InDefinitionName, const TSharedPtr<OpenAPI::V3::FSchemaObject>& InSchema = nullptr);`
- L44 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPITypeInfo> ResolveType(const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName = {}, FString InJsonType = {});`
- L46 _public prototype_ `TObjectPtr<UWebAPITypeInfo> GetTypeForContentType(const FString& InContentType);`
- L49 _public prototype_ `template <typename StorageType> FString GetDefaultJsonTypeForStorage(const StorageType& InStorage);`
- L52 _public prototype_ `template <typename ObjectType> TSharedPtr<ObjectType> ResolveReference(const FString& InDefinitionName);`
- L56 _public prototype_ `template <typename ObjectType> TSharedPtr<ObjectType> ResolveReference(const UE::Json::TJsonReference<ObjectType>& InJsonReference, FString& OutDefinitionName, bool bInCheck = true);` — Only resolves if necessary.
- L60 _public prototype_ `template <typename ObjectType> TSharedPtr<ObjectType> ResolveReference(const UE::Json::TJsonReference<ObjectType>& InJsonReference, bool bInCheck = true);` — Only resolves if necessary.
- L62 _public prototype_ `FWebAPINameVariant ResolvePropertyName(const TObjectPtr<UWebAPIProperty>& InProperty, const FWebAPITypeNameVariant& InPotentialName, const TOptional<bool>& bInIsArray = {});`
- L65 _public prototype_ `template <typename SchemaType> bool IsArray(const TSharedPtr<SchemaType>& InSchema);`
- L68 _public prototype_ `template <typename SchemaType, typename ModelType> static bool ConvertModelBase(const TSharedPtr<SchemaType>& InSchema, ModelType* OutModel);`
- L71 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIEnum> ConvertEnum(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InEnumTypeName = {}) const;`
- L75 _public prototype_ `template <typename SchemaType> bool ConvertProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName, UWebAPIProperty* OutProperty);` — Modifies an existing Property using the supplied source object.
- L78 _public prototype_ `bool ConvertProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const FWebAPITypeNameVariant& InPropertyTypeName, UWebAPIProperty* OutProperty);` — Modifies an existing Property using the supplied TypeInfo.
- L82 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIProperty> ConvertProperty(const TSharedPtr<SchemaType>& InSrcSchema, const TObjectPtr<UWebAPIModel>& InModel, const FWebAPINameVariant& InPropertyName = {}, const FString& InDefinitionName = {});` — Creates a new Property from the supplied source object.
- L86 _public prototype_ `template <typename SchemaType> bool ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel);` — Modifies an existing Model using the supplied source object.
- L90 _public prototype_ `template <typename SchemaType> TObjectPtr<UWebAPIModel> ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName = {});` — Creates a new Model from the supplied source object.
- L92 _public prototype_ `bool ConvertOperationParameter(const FWebAPINameVariant& InParameterName, const TSharedPtr<OpenAPI::V3::FParameterObject>& InParameter, const FString& InDefinitionName, UWebAPIOperationParameter* OutParameter);`
- L94 _public prototype_ `TObjectPtr<UWebAPIParameter> ConvertParameter(const TSharedPtr<OpenAPI::V3::FParameterObject>& InSrcParameter);`
- L96 _public prototype_ `bool ConvertRequest(const FWebAPITypeNameVariant& InOperationName, const TSharedPtr<OpenAPI::V3::FOperationObject>& InOperation, UWebAPIOperationRequest* OutRequest);`
- L98 _public prototype_ `bool ConvertResponse(const FWebAPITypeNameVariant& InOperationName, uint32 InResponseCode, const TSharedPtr<OpenAPI::V3::FResponseObject>& InResponse, UWebAPIOperationResponse* OutResponse);`
- L100 _public prototype_ `TObjectPtr<UWebAPIOperation> ConvertOperation(const FString& InPath, const FString& InVerb, const TSharedPtr<OpenAPI::V3::FOperationObject>& InSrcOperation, const FWebAPITypeNameVariant& InOperationTypeName = {});`
- L102 _public prototype_ `TObjectPtr<UWebAPIService> ConvertService(const FWebAPINameVariant& InName) const;`
- L103 _public prototype_ `TObjectPtr<UWebAPIService> ConvertService(const TSharedPtr<OpenAPI::V3::FTagObject>& InTag) const;`
- L105 _public prototype_ `bool ConvertModels(const TMap<FString, Json::TJsonReference<OpenAPI::V3::FSchemaObject>>& InSchemas, UWebAPISchema* OutSchema);`
- L107 _public prototype_ `bool ConvertParameters(const TArray<Json::TJsonReference<OpenAPI::V3::FParameterObject>>& InParameters, UWebAPISchema* OutSchema);`
- L109 _public prototype_ `bool ConvertParameters(const TMap<FString, TSharedPtr<OpenAPI::V3::FParameterObject>>& InParameters, UWebAPISchema* OutSchema);`
- L111 _public prototype_ `bool ConvertSecurity(const UE::WebAPI::OpenAPI::V3::FOpenAPIObject& InOpenAPI, UWebAPISchema* OutSchema);`
- L113 _public prototype_ `bool ConvertTags(const TArray<TSharedPtr<OpenAPI::V3::FTagObject>>& InTags, UWebAPISchema* OutSchema) const;`
- L115 _public prototype_ `bool ConvertPaths(const TMap<FString, TSharedPtr<OpenAPI::V3::FPathItemObject>>& InPaths, UWebAPISchema* OutSchema);`
- L118 _private member_ `TSharedPtr<const UE::WebAPI::OpenAPI::V3::FOpenAPIObject> InputSchema;`
- L119 _private member_ `TStrongObjectPtr<UWebAPISchema> OutputSchema;`
- L120 _private member_ `TSharedPtr<FWebAPIMessageLog> MessageLog;`
- L121 _private member_ `FWebAPIProviderSettings ProviderSettings;`
- L125 _prototype_ `template <> TSharedPtr<OpenAPI::V3::FSchemaObject> FWebAPIOpenAPISchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L128 _prototype_ `template <> TSharedPtr<OpenAPI::V3::FParameterObject> FWebAPIOpenAPISchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L131 _prototype_ `template <> TSharedPtr<OpenAPI::V3::FResponseObject> FWebAPIOpenAPISchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L134 _prototype_ `template <> TSharedPtr<OpenAPI::V3::FSecuritySchemeObject> FWebAPIOpenAPISchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L137 _prototype_ `template <> TSharedPtr<OpenAPI::V3::FRequestBodyObject> FWebAPIOpenAPISchemaConverter::ResolveReference(const FString& InDefinitionName);`
- L141 _prototype_ `template <> bool FWebAPIOpenAPISchemaConverter::ConvertModel(const TSharedPtr<OpenAPI::V3::FParameterObject>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel);` — Modifies an existing Model using the supplied source object.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Json` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace WebAPI` (scope `UE`)
- L23 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V3/WebAPIOpenAPIConverter.inl` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "WebAPIOpenAPIConverter"`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace WebAPI` (scope `UE`)
- L12 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L15 _function_ `template <> inline FString FWebAPIOpenAPISchemaConverter::GetDefaultJsonTypeForStorage<EWebAPIParameterStorage>(const EWebAPIParameterStorage& InStorage)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L29 _function_ `template <> inline FString FWebAPIOpenAPISchemaConverter::GetDefaultJsonTypeForStorage<EWebAPIResponseStorage>(const EWebAPIResponseStorage& InStorage)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L40 _function_ `template <typename SchemaType> TObjectPtr<UWebAPITypeInfo> FWebAPIOpenAPISchemaConverter::ResolveType(const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName, FString InJsonType)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L126 _function_ `template <> inline TSharedPtr<OpenAPI::V3::FSchemaObject> FWebAPIOpenAPISchemaConverter::ResolveReference<OpenAPI::V3::FSchemaObject>(const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L146 _function_ `template <> inline TSharedPtr<OpenAPI::V3::FParameterObject> FWebAPIOpenAPISchemaConverter::ResolveReference<OpenAPI::V3::FParameterObject>(const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L166 _function_ `template <> inline TSharedPtr<OpenAPI::V3::FResponseObject> FWebAPIOpenAPISchemaConverter::ResolveReference<V3::FResponseObject>(const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L186 _function_ `template <> inline TSharedPtr<OpenAPI::V3::FSecuritySchemeObject> FWebAPIOpenAPISchemaConverter::ResolveReference<V3::FSecuritySchemeObject>(const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L206 _function_ `template <> inline TSharedPtr<OpenAPI::V3::FRequestBodyObject> FWebAPIOpenAPISchemaConverter::ResolveReference<V3::FRequestBodyObject>(const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L221 _function_ `template <typename ObjectType> TSharedPtr<ObjectType> FWebAPIOpenAPISchemaConverter::ResolveReference(const Json::TJsonReference<ObjectType>& InJsonReference, FString& OutDefinitionName, bool bInCheck)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L251 _function_ `template <typename ObjectType> TSharedPtr<ObjectType> FWebAPIOpenAPISchemaConverter::ResolveReference(const UE::Json::TJsonReference<ObjectType>& InJsonReference, bool bInCheck)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L258 _function_ `template <> inline bool FWebAPIOpenAPISchemaConverter::IsArray(const TSharedPtr<UE::WebAPI::OpenAPI::V3::FSchemaObject>& InSchema)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L264 _function_ `template <> inline bool FWebAPIOpenAPISchemaConverter::IsArray(const TSharedPtr<UE::WebAPI::OpenAPI::V3::FParameterObject>& InSchema)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L273 _function_ `template <typename SchemaType, typename ModelType> bool FWebAPIOpenAPISchemaConverter::ConvertModelBase(const TSharedPtr<SchemaType>& InSchema, ModelType* OutModel)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L282 _function_ `template <typename SchemaType> TObjectPtr<UWebAPIEnum> FWebAPIOpenAPISchemaConverter::ConvertEnum(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InEnumTypeName) const` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L327 _function_ `template <> inline bool FWebAPIOpenAPISchemaConverter::ConvertProperty<OpenAPI::V3::FParameterObject>( const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const TSharedPtr<OpenAPI::V3::FParameterObject>& InParameter, const FString& InDefinitionName, UWebAPIProperty* OutProperty)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L390 _function_ `template <typename SchemaType> bool FWebAPIOpenAPISchemaConverter::ConvertProperty(const FWebAPITypeNameVariant& InModelName, const FWebAPINameVariant& InPropertyName, const TSharedPtr<SchemaType>& InSchema, const FString& InDefinitionName, UWebAPIProperty* OutProperty)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L488 _function_ `template <typename SchemaType> TObjectPtr<UWebAPIProperty> FWebAPIOpenAPISchemaConverter::ConvertProperty(const TSharedPtr<SchemaType>& InSrcSchema, const TObjectPtr<UWebAPIModel>& InModel, const FWebAPINameVariant& InPropertyName, const FString& InDefinitionName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L512 _function_ `template <typename SchemaType> bool FWebAPIOpenAPISchemaConverter::ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L583 _function_ `template <> inline bool FWebAPIOpenAPISchemaConverter::ConvertModel<OpenAPI::V3::FParameterObject>(const TSharedPtr<OpenAPI::V3::FParameterObject>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName, UWebAPIModel* OutModel)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)
- L634 _function_ `template <typename SchemaType> TObjectPtr<UWebAPIModel> FWebAPIOpenAPISchemaConverter::ConvertModel(const TSharedPtr<SchemaType>& InSrcSchema, const FWebAPITypeNameVariant& InModelTypeName)` (scope `UE::WebAPI::OpenAPI::FWebAPIOpenAPISchemaConverter`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/V3/WebAPIOpenAPIFactory.h` (Private)


#### class `UWebAPIOpenAPIAssetData`  
`class UWebAPIOpenAPIAssetData : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `FString FileContents;` — `UPROPERTY()`

#### class `UWebAPIOpenAPIFactory`  
`class UWebAPIOpenAPIFactory : public UWebAPIOpenAPIFactoryBase`  
_L23-36_
- reflection: `UCLASS()`
- inherits: `UWebAPIOpenAPIFactoryBase`
- desc: Handles importing for OpenAPI V2 files.
- L29 _public prototype_ `UWebAPIOpenAPIFactory();`
- L31 _public prototype_ `virtual bool CanImportWebAPI(const FString& InFileName, const FString& InFileContents) override;`
- L32 _public prototype_ `virtual TFuture<bool> ImportWebAPI(UWebAPIDefinition* InDefinition, const FString& InFileName, const FString& InFileContents) override;`
- L35 _protected member_ `TSharedPtr<FWebAPIOpenAPIProvider> Provider;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/WebAPIOpenAPILog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPIOpenAPI, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebAPIOpenAPI, Log, All);`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/WebAPIOpenAPIModule.h` (Private)


#### class `FWebAPIOpenAPIModule`  
`class FWebAPIOpenAPIModule final : public IWebAPIOpenAPIModuleInterface`  
_L8-14_
- inherits: `IWebAPIOpenAPIModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Private/WebAPIOpenAPIStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("WebAPIOpenAPI"), STATGROUP_WebAPIOpenAPI, STATC`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Public/IWebAPIOpenAPIModule.h` (Public)


#### class `IWebAPIOpenAPIModuleInterface`  
`class IWebAPIOpenAPIModuleInterface : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Public/V2/WebAPISwaggerProvider.h` (Public)


#### class `FWebAPISwaggerProvider`  
`class FWebAPISwaggerProvider : public IWebAPIProviderInterface`  
_L12-20_
- inherits: `IWebAPIProviderInterface`
- L16 _public prototype_ `virtual TFuture<EWebAPIConversionResult> ConvertToWebAPISchema(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition) override;`
- L19 _public member_ `static constexpr const TCHAR* LogName = TEXT("Swa`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Public/V2/WebAPISwaggerSchema.h` (Public)


#### class `UE::WebAPI::OpenAPI::V2::FReference`  
`class FReference`  
_L24-30_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#referenceObject
- L27 _public member_ `TSharedPtr<FString> $Ref;`
- L29 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FItems`  
`class FItems`  
_L33-55_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#itemsObject
- L36 _public member_ `FString Type;` — will map to EJson enum, if it's string AND enum is set, it's an enum by name
- L37 _public member_ `TOptional<FString> Format;`
- L38 _public member_ `TOptional<TSharedPtr<FItems>> Items;`
- L39 _public member_ `TOptional<FString> CollectionFormat;` — csv, ssv, tsv, pipes
- L40 _public member_ `TOptional<FString> Default;`
- L41 _public member_ `TOptional<float> Maximum;`
- L42 _public member_ `TOptional<float> ExclusiveMaximum;`
- L43 _public member_ `TOptional<float> Minimum;`
- L44 _public member_ `TOptional<float> ExclusiveMinimum;`
- L45 _public member_ `TOptional<int32> MaxLength;`
- L46 _public member_ `TOptional<int32> MinLength;`
- L47 _public member_ `TOptional<FString> Pattern;`
- L48 _public member_ `TOptional<int32> MaxItems;`
- L49 _public member_ `TOptional<int32> MinItems;`
- L50 _public member_ `TOptional<bool> bUniqueItems;` — Array should be a Set (of unique values)
- L51 _public member_ `TOptional<TArray<FString>> Enum;` — All possible values
- L52 _public member_ `TOptional<int32> MultipleOf;`
- L54 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FExternalDocumentation`  
`class FExternalDocumentation`  
_L58-65_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#externalDocumentationObject
- L61 _public member_ `TOptional<FString> Description;`
- L62 _public member_ `FString Url;`
- L64 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FXML`  
`class FXML`  
_L68-78_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#xmlObject
- L71 _public member_ `TOptional<FString> Name;`
- L72 _public member_ `TOptional<FString> Namespace;`
- L73 _public member_ `TOptional<FString> Prefix;`
- L74 _public member_ `TOptional<bool> Attribute;`
- L75 _public member_ `TOptional<bool> Wrapped;`
- L77 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FSchemaBase`  
`class FSchemaBase`  
_L80-103_
- L83 _public member_ `FString Name;`
- L84 _public member_ `TOptional<FString> Description;`
- L85 _public member_ `TOptional<FString> Type;`
- L86 _public member_ `TOptional<FString> Format;` — 'int32' | 'int64' | 'float' | 'double' | 'string' | 'boolean' | 'byte' | 'binary' | 'date' | 'date-time' | 'password';
- L87 _public member_ `TOptional<FString> Default;`
- L88 _public member_ `TOptional<bool> bRequired;`
- L89 _public member_ `TOptional<float> Minimum;`
- L90 _public member_ `TOptional<bool> bExclusiveMinimum;`
- L91 _public member_ `TOptional<float> Maximum;`
- L92 _public member_ `TOptional<bool> bExclusiveMaximum;`
- L93 _public member_ `TOptional<int32> MinLength;`
- L94 _public member_ `TOptional<int32> MaxLength;`
- L95 _public member_ `TOptional<FString> Pattern;`
- L96 _public member_ `TOptional<int32> MinItems;`
- L97 _public member_ `TOptional<int32> MaxItems;`
- L98 _public member_ `TOptional<bool> bUniqueItems;` — Array should be a Set (of unique values)
- L99 _public member_ `TOptional<TArray<FString>> Enum;` — All possible values
- L100 _public member_ `TOptional<Json::TJsonReference<FSchema>> Items;` — Item type (if this is an array)
- L102 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FSchema`  
`class FSchema : public FSchemaBase`  
_L106-126_
- inherits: `FSchemaBase`
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#schemaObject
- L109 _public typedef_ `using Super = FSchemaBase;`
- L111 _public member_ `TOptional<FString> Title;`
- L112 _public member_ `TOptional<int32> MultipleOf;`
- L113 _public member_ `TOptional<int32> MaxProperties;`
- L114 _public member_ `TOptional<int32> MinProperties;`
- L116 _public member_ `TOptional<TArray<Json::TJsonReference<FSchema>>> AllOf;`
- L117 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FSchema>>> Properties;`
- L118 _public member_ `TOptional<FString> AdditionalProperties;`
- L119 _public member_ `TOptional<FString> Discriminator;`
- L120 _public member_ `TOptional<bool> bReadOnly;`
- L121 _public member_ `TOptional<TSharedPtr<FXML>> XML;`
- L122 _public member_ `TOptional<TSharedPtr<FExternalDocumentation>> ExternalDocs;`
- L123 _public member_ `TOptional<FString> Example;`
- L125 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FParameter`  
`class FParameter : public FSchemaBase`  
_L129-143_
- inherits: `FSchemaBase`
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#parameterObject
- L132 _public typedef_ `using Super = FSchemaBase;`
- L134 _public member_ `FString In;` — One of query, header, path, formData or body  'path' | 'query' | 'header' | 'formData' | 'body';
- L135 _public member_ `TOptional<FString> Description;`
- L136 _public member_ `TOptional<Json::TJsonReference<FSchema>> Schema;`
- L137 _public member_ `TOptional<bool> bAllowEmptyValue;`
- L139 _public member_ `TOptional<FString> CollectionFormat;` — TSharedPtr<FItems> Items;
- L140 _public member_ `TOptional<int32> MultipleOf;`
- L142 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FHeader`  
`class FHeader`  
_L146-169_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#headerObject
- L149 _public member_ `TOptional<FString> Description;`
- L150 _public member_ `FString Type;`
- L151 _public member_ `TOptional<FString> Format;`
- L152 _public member_ `TSharedPtr<FItems> Items;`
- L153 _public member_ `TOptional<FString> CollectionFormat;`
- L154 _public member_ `TOptional<FString> Default;`
- L155 _public member_ `TOptional<float> Maximum;`
- L156 _public member_ `TOptional<bool> bExclusiveMaximum;`
- L157 _public member_ `TOptional<float> Minimum;`
- L158 _public member_ `TOptional<bool> bExclusiveMinimum;`
- L159 _public member_ `TOptional<int32> MaxLength;`
- L160 _public member_ `TOptional<int32> MinLength;`
- L161 _public member_ `TOptional<FString> Pattern;`
- L162 _public member_ `TOptional<int32> MaxItems;`
- L163 _public member_ `TOptional<int32> MinItems;`
- L164 _public member_ `TOptional<bool> bUniqueItems;` — Array should be a Set (of unique values)
- L165 _public member_ `TOptional<TArray<FString>> Enum;`
- L166 _public member_ `TOptional<int32> MultipleOf;`
- L168 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FExample`  
`class FExample : public TMap<FString, FString>`  
_L172-177_
- inherits: `TMap<FString,FString>`
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#exampleObject
- L176 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);` — Key is mime-type

#### class `UE::WebAPI::OpenAPI::V2::FResponse`  
`class FResponse`  
_L180-190_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#responseObject
- L183 _public member_ `TOptional<FString> Name;`
- L184 _public member_ `FString Description;`
- L185 _public member_ `TOptional<Json::TJsonReference<FSchema>> Schema;`
- L186 _public member_ `TOptional<TMap<FString, TSharedPtr<FHeader>>> Headers;`
- L187 _public member_ `TOptional<TSharedPtr<FExample>> Examples;`
- L189 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FScopes`  
`class FScopes : public TMap<FString, FString>`  
_L192-196_
- inherits: `TMap<FString,FString>`
- L195 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FSecurityScheme`  
`class FSecurityScheme`  
_L199-212_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#securitySchemeObject
- L202 _public member_ `TOptional<FString> Name;`
- L203 _public member_ `FString Type;` — 'basic' | 'apiKey' | 'oauth2';
- L204 _public member_ `TOptional<FString> Description;`
- L205 _public member_ `TOptional<FString> In;` — 'query' | 'header';
- L206 _public member_ `TOptional<FString> Flow;` — 'implicit' | 'password' | 'application' | 'accessCode';
- L207 _public member_ `TOptional<FString> AuthorizationUrl;`
- L208 _public member_ `TOptional<FString> TokenUrl;`
- L209 _public member_ `TArray<TMap<FString, TSharedPtr<FScopes>>> Scopes;`
- L211 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FSecurityRequirement`  
`class FSecurityRequirement : public TMap<FString, TArray<FString>>`  
_L215-219_
- inherits: `TMap<FString,TArray<FString>>`
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#securityRequirementObject
- L218 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FTag`  
`class FTag`  
_L222-230_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#tagObject
- L225 _public member_ `FString Name;`
- L226 _public member_ `TOptional<FString> Description;`
- L227 _public member_ `TOptional<TSharedPtr<FExternalDocumentation>> ExternalDocs;`
- L229 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FPath`  
`class FPath`  
_L233-247_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#pathItemObject
- L236 _public member_ `TOptional<FString> $Ref;`
- L237 _public member_ `TSharedPtr<FOperation> Get;`
- L238 _public member_ `TSharedPtr<FOperation> Put;`
- L239 _public member_ `TSharedPtr<FOperation> Post;`
- L240 _public member_ `TSharedPtr<FOperation> Delete;`
- L241 _public member_ `TSharedPtr<FOperation> Options;`
- L242 _public member_ `TSharedPtr<FOperation> Head;`
- L243 _public member_ `TSharedPtr<FOperation> Patch;`
- L244 _public member_ `TOptional<TArray<Json::TJsonReference<FParameter>>> Parameters;`
- L246 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FSwagger`  
`class FSwagger`  
_L250-270_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/main/versions/2.0.md#swagger-object
- L253 _public member_ `FString Swagger;`
- L254 _public member_ `TSharedPtr<FInfo> Info;`
- L255 _public member_ `TOptional<FString> Host;`
- L256 _public member_ `TOptional<FString> BasePath;`
- L257 _public member_ `TOptional<TArray<FString>> Schemes;`
- L258 _public member_ `TOptional<TArray<FString>> Consumes;` — mimetypes
- L259 _public member_ `TOptional<TArray<FString>> Produces;` — mimetypes
- L260 _public member_ `TMap<FString, TSharedPtr<FPath>> Paths;`
- L261 _public member_ `TOptional<TMap<FString, TSharedPtr<FSchema>>> Definitions;`
- L262 _public member_ `TOptional<TMap<FString, TSharedPtr<FParameter>>> Parameters;`
- L263 _public member_ `TOptional<TMap<FString, TSharedPtr<FResponse>>> Responses;`
- L264 _public member_ `TOptional<TMap<FString, TSharedPtr<FSecurityScheme>>> SecurityDefinitions;`
- L265 _public member_ `TOptional<TArray<TSharedPtr<FSecurityRequirement>>> Security;`
- L266 _public member_ `TOptional<TArray<TSharedPtr<FTag>>> Tags;`
- L267 _public member_ `TOptional<TSharedPtr<FExternalDocumentation>> ExternalDocs;`
- L269 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FLicense`  
`class FLicense`  
_L273-280_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#licenseObject
- L276 _public member_ `FString Name;`
- L277 _public member_ `TOptional<FString> URL;`
- L279 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FContact`  
`class FContact`  
_L283-291_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#contactObject
- L286 _public member_ `TOptional<FString> Name;`
- L287 _public member_ `TOptional<FString> URL;`
- L288 _public member_ `TOptional<FString> Email;`
- L290 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FInfo`  
`class FInfo`  
_L294-305_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/main/versions/2.0.md#infoObject
- L297 _public member_ `FString Title;`
- L298 _public member_ `TOptional<FString> Description;`
- L299 _public member_ `TOptional<FString> TermsOfService;`
- L300 _public member_ `TOptional<FString> Contact;`
- L301 _public member_ `TOptional<TSharedPtr<FLicense>> License;`
- L302 _public member_ `FString Version;`
- L304 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V2::FOperation`  
`class FOperation`  
_L308-325_
- desc: https://github.com/OAI/OpenAPI-Specification/blob/master/versions/2.0.md#operationObject
- L311 _public member_ `TOptional<TArray<FString>> Tags;`
- L312 _public member_ `TOptional<FString> Summary;`
- L313 _public member_ `TOptional<FString> Description;`
- L314 _public member_ `TOptional<TSharedPtr<FExternalDocumentation>> ExternalDocs;`
- L315 _public member_ `TOptional<FString> OperationId;`
- L316 _public member_ `TOptional<TArray<FString>> Consumes;` — mimetypes
- L317 _public member_ `TOptional<TArray<FString>> Produces;` — mimetypes
- L318 _public member_ `TOptional<TArray<Json::TJsonReference<FParameter>>> Parameters;`
- L319 _public member_ `TMap<FString, TSharedPtr<FResponse>> Responses;`
- L320 _public member_ `TArray<FString> Schemes;` — ('http' | 'https' | 'ws' | 'wss')[];
- L321 _public member_ `TOptional<bool> bDeprecated;`
- L322 _public member_ `TOptional<TArray<TSharedPtr<FSecurityRequirement>>> Security;`
- L324 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace WebAPI` (scope `UE`)
- L13 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L17 _namespace_ `namespace V2` (scope `UE::WebAPI::OpenAPI`)

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Public/V3/WebAPIOpenAPIProvider.h` (Public)


#### class `FWebAPIOpenAPIProvider`  
`class FWebAPIOpenAPIProvider : public IWebAPIProviderInterface`  
_L10-18_
- inherits: `IWebAPIProviderInterface`
- L14 _public prototype_ `virtual TFuture<EWebAPIConversionResult> ConvertToWebAPISchema(const TWeakObjectPtr<UWebAPIDefinition>& InDefinition) override;`
- L17 _public member_ `static constexpr const TCHAR* LogName = TEXT("Ope`

### `Plugins/Experimental/Web/WebAPI/Source/WebAPIOpenAPI/Public/V3/WebAPIOpenAPISchema.h` (Public)


#### class `UE::WebAPI::OpenAPI::V3::FSchemaObjectBase`  
`class FSchemaObjectBase`  
_L63-73_
- L66 _public member_ `FString Name;`
- L67 _public member_ `TOptional<FString> Description;`
- L68 _public member_ `TOptional<bool> bRequired;` — REQUIRED IF "in" i  "path"
- L69 _public member_ `TOptional<bool> bDeprecated;`
- L70 _public member_ `TOptional<FString> Example;`
- L72 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FParameterObject`  
`class FParameterObject : public FSchemaObjectBase`  
_L76-97_
- inherits: `FSchemaObjectBase`
- desc: https://swagger.io/specification/#parameter-object
- L79 _public typedef_ `using Super = FSchemaObjectBase;`
- L81 _public member_ `FString In;` — One of query, header, path or cookie
- L83 _public member_ `TOptional<bool> bAllowEmptyValue;`
- L85 _public member_ `TOptional<FString> Style;`
- L86 _public member_ `TOptional<bool> bExplode;` — if array or object, parameter-per-item, not array/object-as-parameter
- L87 _public member_ `TOptional<bool> bAllowReserved;` — allows: :/?#[]@!$&'()*+,;=
- L89 _public member_ `TOptional<Json::TJsonReference<FSchemaObject>> Schema;`
- L90 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FExampleObject>>> Examples;`
- L92 _public member_ `TOptional<TMap<FString, TSharedPtr<FMediaTypeObject>>> Content;` — only one item
- L96 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FSchemaObject`  
`class FSchemaObject : public FSchemaObjectBase`  
_L100-142_
- inherits: `FSchemaObjectBase`
- desc: https://swagger.io/specification/#schema-object
- L103 _public typedef_ `using Super = FSchemaObjectBase;`
- L106 _public member_ `TOptional<FString> Type;` — MAY be extended with Specification Extensions
- L107 _public member_ `TOptional<FString> Format;` — 'int32' | 'int64' | 'float' | 'double' | 'string' | 'boolean' | 'byte' | 'binary' | 'date' | 'date-time' | 'password';
- L108 _public member_ `TOptional<FString> Default;`
- L109 _public member_ `TOptional<TArray<Json::TJsonReference<FSchemaObject>>> AllOf;`
- L110 _public member_ `TOptional<TArray<Json::TJsonReference<FSchemaObject>>> OneOf;`
- L111 _public member_ `TOptional<TArray<Json::TJsonReference<FSchemaObject>>> AnyOf;`
- L112 _public member_ `TOptional<TArray<Json::TJsonReference<FSchemaObject>>> Not;`
- L114 _public member_ `TOptional<FString> Title;`
- L115 _public member_ `TOptional<int32> MultipleOf;`
- L116 _public member_ `TOptional<float> Minimum;`
- L117 _public member_ `TOptional<bool> bExclusiveMinimum;`
- L118 _public member_ `TOptional<float> Maximum;`
- L119 _public member_ `TOptional<bool> bExclusiveMaximum;`
- L120 _public member_ `TOptional<int32> MinLength;`
- L121 _public member_ `TOptional<int32> MaxLength;`
- L122 _public member_ `TOptional<FString> Pattern;`
- L123 _public member_ `TOptional<int32> MinItems;`
- L124 _public member_ `TOptional<int32> MaxItems;`
- L125 _public member_ `TOptional<bool> bUniqueItems;` — Array should be a Set
- L126 _public member_ `TOptional<int32> MinProperties;`
- L127 _public member_ `TOptional<int32> MaxProperties;`
- L128 _public member_ `TOptional<TArray<FString>> Enum;` — All possible values
- L129 _public member_ `TOptional<Json::TJsonReference<FSchemaObject>> Items;` — Item type (if this is an array)
- L130 _public member_ `TOptional<bool> bNullable;`
- L131 _public member_ `TOptional<Json::TJsonReference<FDiscriminatorObject>> Discriminator;`
- L132 _public member_ `TOptional<bool> bReadOnly;`
- L133 _public member_ `TOptional<bool> bWriteOnly;`
- L134 _public member_ `TOptional<TSharedPtr<FString>> Xml;`
- L135 _public member_ `TOptional<TSharedPtr<FExternalDocumentationObject>> ExternalDocs;`
- L136 _public member_ `TSharedPtr<FJsonObject> Example;`
- L138 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FSchemaObject>>> Properties;`
- L139 _public member_ `TOptional<FString> AdditionalProperties;`
- L141 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FPathItemObject`  
`class FPathItemObject`  
_L145-164_
- desc: https://swagger.io/specification/#path-item-object
- L148 _public member_ `TOptional<FString> $Ref;`
- L149 _public member_ `TOptional<FString> Summary;`
- L150 _public member_ `TOptional<FString> Description;`
- L151 _public member_ `TSharedPtr<FOperationObject> Get;`
- L152 _public member_ `TSharedPtr<FOperationObject> Put;`
- L153 _public member_ `TSharedPtr<FOperationObject> Post;`
- L154 _public member_ `TSharedPtr<FOperationObject> Delete;`
- L155 _public member_ `TSharedPtr<FOperationObject> Options;`
- L156 _public member_ `TSharedPtr<FOperationObject> Head;`
- L157 _public member_ `TSharedPtr<FOperationObject> Patch;`
- L158 _public member_ `TSharedPtr<FOperationObject> Trace;`
- L159 _public member_ `TOptional<TArray<Json::TJsonReference<FServerObject>>> Servers;`
- L160 _public member_ `TArray<Json::TJsonReference<FParameterObject>> Parameters;`
- L163 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FComponentsObject`  
`class FComponentsObject`  
_L167-183_
- desc: https://swagger.io/specification/#components-object
- L171 _public member_ `TMap<FString, Json::TJsonReference<FSchemaObject>> Schemas;` — all keys should match regex ^[a-zA-Z0-9\.\-_]+$
- L172 _public member_ `TMap<FString, Json::TJsonReference<FResponseObject>> Responses;`
- L173 _public member_ `TMap<FString, Json::TJsonReference<FParameterObject>> Parameters;`
- L174 _public member_ `TMap<FString, Json::TJsonReference<FExampleObject>> Examples;`
- L175 _public member_ `TMap<FString, Json::TJsonReference<FRequestBodyObject>> RequestBodies;`
- L176 _public member_ `TMap<FString, Json::TJsonReference<FHeaderObject>> Headers;`
- L177 _public member_ `TMap<FString, Json::TJsonReference<FSecuritySchemeObject>> SecuritySchemes;`
- L178 _public member_ `TMap<FString, Json::TJsonReference<FLinkObject>> Links;`
- L179 _public member_ `TMap<FString, Json::TJsonReference<FCallbackObject>> Callbacks;`
- L182 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FContactObject`  
`class FContactObject`  
_L186-195_
- desc: https://swagger.io/specification/#contact-object
- L189 _public member_ `TOptional<FString> Name;`
- L190 _public member_ `TOptional<FString> Url;`
- L191 _public member_ `TOptional<FString> Email;`
- L194 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FDiscriminatorObject`  
`class FDiscriminatorObject`  
_L198-206_
- desc: https://swagger.io/specification/#discriminator-object
- L201 _public member_ `FString PropertyName;`
- L202 _public member_ `TOptional<TMap<FString, FString>> Mapping;`
- L205 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FEncodingObject`  
`class FEncodingObject`  
_L209-220_
- desc: https://swagger.io/specification/#encoding-object
- L212 _public member_ `TOptional<FString> ContentType;`
- L213 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FHeaderObject>>> Headers;`
- L214 _public member_ `TOptional<FString> Style;`
- L215 _public member_ `TOptional<bool> bExplode;`
- L216 _public member_ `TOptional<bool> bAllowReserved;`
- L219 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FExampleObject`  
`class FExampleObject`  
_L223-233_
- desc: https://swagger.io/specification/#example-object
- L226 _public member_ `TOptional<FString> Summary;`
- L227 _public member_ `TOptional<FString> Description;`
- L228 _public member_ `TSharedPtr<FJsonObject> Value;`
- L229 _public member_ `TOptional<FString> ExternalValue;`
- L232 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FExternalDocumentationObject`  
`class FExternalDocumentationObject`  
_L236-244_
- desc: https://swagger.io/specification/#external-documentation-object
- L239 _public member_ `TOptional<FString> Description;`
- L240 _public member_ `FString Url;`
- L243 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FHeaderObject`  
`class FHeaderObject : public FParameterObject`  
_L247-251_
- inherits: `FParameterObject`
- desc: https://swagger.io/specification/#header-object
- L250 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FInfoObject`  
`class FInfoObject`  
_L254-266_
- desc: https://swagger.io/specification/#info-object
- L257 _public member_ `FString Title;`
- L258 _public member_ `TOptional<FString> Description;`
- L259 _public member_ `TOptional<FString> TermsOfService;`
- L260 _public member_ `TSharedPtr<FContactObject> Contact;`
- L261 _public member_ `TSharedPtr<FLicenseObject> License;`
- L262 _public member_ `FString Version;`
- L265 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FLicenseObject`  
`class FLicenseObject`  
_L269-277_
- desc: https://swagger.io/specification/#license-object
- L272 _public member_ `FString Name;`
- L273 _public member_ `TOptional<FString> Url;`
- L276 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FLinkObject`  
`class FLinkObject`  
_L280-292_
- desc: https://swagger.io/specification/#link-object
- L283 _public member_ `TOptional<FString> OperationRef;`
- L284 _public member_ `TOptional<FString> OperationId;` — mutually exclusive with OperationRef
- L287 _public member_ `TOptional<FString> Description;` — TOptional<TMap<FString, TSharedPtr<TVariant<FVariant, FVariant>>>> Parameters; // @todo: runtime expression object TSharedPtr<TVariant<FVariant, FVariant>> RequestBody; // @todo
- L288 _public member_ `TSharedPtr<FServerObject> Server;`
- L291 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FMediaTypeObject`  
`class FMediaTypeObject`  
_L295-305_
- desc: https://swagger.io/specification/#media-type-object
- L298 _public member_ `Json::TJsonReference<FSchemaObject> Schema;`
- L299 _public member_ `TOptional<FString> Example;`
- L300 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FExampleObject>>> Examples;`
- L301 _public member_ `TOptional<TMap<FString, TSharedPtr<FEncodingObject>>> Encoding;`
- L304 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FOAuthFlowObject`  
`class FOAuthFlowObject`  
_L308-318_
- desc: https://swagger.io/specification/#oauth-flow-object
- L311 _public member_ `FString AuthorizationUrl;`
- L312 _public member_ `FString TokenUrl;`
- L313 _public member_ `TOptional<FString> RefreshUrl;`
- L314 _public member_ `TMap<FString, FString> Scopes;`
- L317 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FOAuthFlowsObject`  
`class FOAuthFlowsObject`  
_L321-331_
- desc: https://swagger.io/specification/#oauth-flows-object
- L324 _public member_ `TSharedPtr<FOAuthFlowObject> Implicit;`
- L325 _public member_ `TSharedPtr<FOAuthFlowObject> Password;`
- L326 _public member_ `TSharedPtr<FOAuthFlowObject> ClientCredentials;`
- L327 _public member_ `TSharedPtr<FOAuthFlowObject> AuthorizationCode;`
- L330 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FOpenAPIObject`  
`class FOpenAPIObject`  
_L334-347_
- desc: https://swagger.io/specification/#openapi-object
- L337 _public member_ `FString OpenAPI;`
- L338 _public member_ `TSharedPtr<FInfoObject> Info;`
- L339 _public member_ `TOptional<TArray<TSharedPtr<FServerObject>>> Servers;` — can be empty
- L340 _public member_ `TMap<FString, TSharedPtr<FPathItemObject>> Paths;`
- L341 _public member_ `TSharedPtr<FComponentsObject> Components;`
- L342 _public member_ `TOptional<TArray<TSharedPtr<FSecurityRequirementObject>>> Security;`
- L343 _public member_ `TOptional<TArray<TSharedPtr<FTagObject>>> Tags;`
- L344 _public member_ `TOptional<TSharedPtr<FExternalDocumentationObject>> ExternalDocs;`
- L346 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FOperationObject`  
`class FOperationObject`  
_L350-368_
- desc: https://swagger.io/specification/#operation-object
- L353 _public member_ `TOptional<TArray<FString>> Tags;`
- L354 _public member_ `TOptional<FString> Summary;`
- L355 _public member_ `TOptional<FString> Description;`
- L356 _public member_ `TSharedPtr<FExternalDocumentationObject> ExternalDocs;`
- L357 _public member_ `TOptional<FString> OperationId;`
- L358 _public member_ `TArray<Json::TJsonReference<FParameterObject>> Parameters;`
- L359 _public member_ `Json::TJsonReference<FRequestBodyObject> RequestBody;`
- L360 _public member_ `TMap<FString, Json::TJsonReference<FResponseObject>> Responses;`
- L361 _public member_ `TMap<FString, Json::TJsonReference<FCallbackObject>> Callbacks;`
- L362 _public member_ `TOptional<bool> bDeprecated;`
- L363 _public member_ `TArray<TSharedPtr<FSecurityRequirementObject>> Security;`
- L364 _public member_ `TArray<TSharedPtr<FServerObject>> Servers;`
- L367 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FReferenceObject`  
`class FReferenceObject`  
_L371-378_
- desc: https://swagger.io/specification/#reference-object
- L374 _public member_ `FString $Ref;`
- L377 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FRequestBodyObject`  
`class FRequestBodyObject`  
_L381-390_
- desc: https://swagger.io/specification/#request-body-object
- L384 _public member_ `TOptional<FString> Description;`
- L385 _public member_ `TMap<FString, TSharedPtr<FMediaTypeObject>> Content;`
- L386 _public member_ `TOptional<bool> bRequired;`
- L389 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FResponseObject`  
`class FResponseObject`  
_L393-405_
- desc: https://swagger.io/specification/#response-object
- L396 _public member_ `TOptional<FString> Name;`
- L397 _public member_ `FString Description;`
- L398 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FHeaderObject>>> Headers;`
- L399 _public member_ `TOptional<TMap<FString, Json::TJsonReference<FMediaTypeObject>>> Content;`
- L404 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FSecuritySchemeObject`  
`class FSecuritySchemeObject`  
_L408-422_
- desc: https://swagger.io/specification/#security-scheme-object
- L411 _public member_ `FString Type;` — any of apiKey, http, oauth2, openIdConnect
- L412 _public member_ `TOptional<FString> Description;`
- L413 _public member_ `FString Name;`
- L414 _public member_ `FString In;`
- L415 _public member_ `FString Scheme;`
- L416 _public member_ `TOptional<FString> BearerFormat;`
- L417 _public member_ `TSharedPtr<FOAuthFlowsObject> Flows;`
- L418 _public member_ `TOptional<FString> OpenIdConnectUrl;`
- L421 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FServerObject`  
`class FServerObject`  
_L425-434_
- desc: https://swagger.io/specification/#server-object
- L428 _public member_ `FString Url;`
- L429 _public member_ `TOptional<FString> Description;`
- L430 _public member_ `TOptional<TMap<FString, TSharedPtr<FServerVariableObject>>> Variables;`
- L433 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FServerVariableObject`  
`class FServerVariableObject`  
_L437-446_
- desc: https://swagger.io/specification/#server-variable-object
- L440 _public member_ `TArray<FString> Enum;` — 1 or items
- L441 _public member_ `FString Default;`
- L442 _public member_ `TOptional<FString> Description;`
- L445 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FTagObject`  
`class FTagObject`  
_L449-458_
- desc: https://swagger.io/specification/#tag-object
- L452 _public member_ `FString Name;`
- L453 _public member_ `TOptional<FString> Description;`
- L454 _public member_ `TOptional<TSharedPtr<FExternalDocumentationObject>> ExternalDocs;`
- L457 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### class `UE::WebAPI::OpenAPI::V3::FXMLObject`  
`class FXMLObject`  
_L461-472_
- desc: https://swagger.io/specification/#xml-object
- L464 _public member_ `TOptional<FString> Name;`
- L465 _public member_ `TOptional<FString> Namespace;`
- L466 _public member_ `TOptional<FString> Prefix;`
- L467 _public member_ `TOptional<bool> bAttribute;`
- L468 _public member_ `TOptional<bool> bWrapped;`
- L471 _public prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJson);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace WebAPI` (scope `UE`)
- L13 _namespace_ `namespace OpenAPI` (scope `UE::WebAPI`)
- L16 _namespace_ `namespace V3` (scope `UE::WebAPI::OpenAPI`)
- L53 _typedef_ `using FPathsObject = TMap<FString, TSharedPtr<FPathItemObject>>;` (scope `UE::WebAPI::OpenAPI::V3`) — https://swagger.io/specification/#paths-object all keys must be relative, and with a leading forward slash MAY be extended with Specification Extensions
- L57 _typedef_ `using FCallbackObject = TMap<FString, FPathItemObject>;` (scope `UE::WebAPI::OpenAPI::V3`) — https://swagger.io/specification/#callback-object MAY be extended with Specification Extensions
- L61 _typedef_ `using FSecurityRequirementObject = TMap<FString, TArray<FString>>;` (scope `UE::WebAPI::OpenAPI::V3`) — https://swagger.io/specification/#security-requirement-object MAY be extended with Specification Extensions
- L477 _namespace_ `namespace Json` (scope `UE`)
- L479 _prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJsonObject, UE::WebAPI::OpenAPI::V3::FPathsObject& OutObject);` (scope `UE::Json`)
- L486 _prototype_ `bool FromJson(const TSharedRef<FJsonObject>& InJsonObject, UE::WebAPI::OpenAPI::V3::FSecurityRequirementObject& OutObject);` (scope `UE::Json`)
