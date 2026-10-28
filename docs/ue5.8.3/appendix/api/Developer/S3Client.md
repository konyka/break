# Developer / S3Client

- module root: `Source/Developer/S3Client`
- headers: 1; symbols: 100
- symbol kinds: class=3, function=12, macro=1, member=32, namespace=1, prototype=38, struct=8, typedef=5
- PrivateDependencyModuleNames: Core, Json, SSL, Sockets, XmlParser, libcurl

### `Source/Developer/S3Client/Internal/S3/S3Client.h` (Internal)


#### class `UE::FS3ClientCredentials`  
`class FS3ClientCredentials`  
_L21-71_
- desc: Credentials for creating signed/authenticated requests to S3.
- L25 _public prototype_ `FS3ClientCredentials() = default;` — Default constructor creating invalid credentails.
- L33 _public function_ `FS3ClientCredentials(const FString& InAccessKey, const FString& InSecretKey) : AccessKey(InAccessKey) , SecretKey(InSecretKey)` — Constructor for basic credentials. @param AccessKey			The access key. @param SecretKey			The secret key.
- L46 _public function_ `FS3ClientCredentials(const FString& InAccessKey, const FString& InSecretKey, const FString& InSessionToken) : AccessKey(InAccessKey) , SecretKey(InSecretKey) , SessionToken(InSessionToken)` — Constructor for short termed credentials. @param AccessKey			The access key. @param SecretKey			The secret key. @param SessionToken		Token defining the lifetime of the credentials.
- L53 _public prototype_ `FS3ClientCredentials(const FS3ClientCredentials& Other) = default;`
- L54 _public prototype_ `FS3ClientCredentials(FS3ClientCredentials&&) = default;`
- L55 _public prototype_ `FS3ClientCredentials& operator=(const FS3ClientCredentials&) = default;`
- L56 _public prototype_ `FS3ClientCredentials& operator=(FS3ClientCredentials&&) = default;`
- L59 _public prototype_ `bool IsValid() const;` — Returns whether the access and secret is is valid.
- L61 _public function_ `const FString& GetAccessKey() const` — Returns the access key.
- L63 _public function_ `const FString& GetSecretKey() const` — Returns the secret key.
- L65 _public function_ `const FString& GetSessionToken() const` — Returns the session token.
- L68 _private member_ `FString AccessKey;`
- L69 _private member_ `FString SecretKey;`
- L70 _private member_ `FString SessionToken;`

#### class `UE::FS3CredentialsProfileStore`  
`class FS3CredentialsProfileStore`  
_L76-88_
- desc: Container for named credentials.
- L80 _public prototype_ `FS3ClientCredentials GetDefault() const;` — Returns the first credentials loaded into the profile store.
- L82 _public prototype_ `bool TryGetCredentials(const FString& ProfileName, FS3ClientCredentials& OutCredentials) const;` — Get credentials for the specified profile name.
- L84 _public prototype_ `static FS3CredentialsProfileStore FromFile(const FString& FileName, FString* OutError = nullptr);` — Reads named credentials from an .ini file.
- L87 _private member_ `TMap<FString, FS3ClientCredentials> Credentials;`

#### struct `UE::FS3Object`  
`struct FS3Object`  
_L91-109_
- desc: Describes an object stored in S3.
- L94 _public member_ `FString Key;` — The object identifider.
- L96 _public member_ `FString LastModifiedText;` — Date and time when this object was last modified in text format.
- L98 _public member_ `FDateTime LastModified;` — Date and time when this object was last modified.
- L100 _public member_ `uint64 Size = 0;` — The size of the object.
- L102 _public function_ `bool operator==(const FS3Object& RHS) const`
- L103 _public function_ `bool operator!=(const FS3Object& RHS) const`

#### struct `UE::FS3Response`  
`struct FS3Response`  
_L112-164_
- desc: Basic response parameters.
- L116 _public prototype_ `FS3Response() = default;`
- L118 _public prototype_ `FS3Response(const FS3Response& Other);`
- L119 _public prototype_ `FS3Response(FS3Response&& Other);`
- L121 _public prototype_ `FS3Response(uint32 InHttpStatusCode, uint32 InApiStatusCode);`
- L122 _public prototype_ `FS3Response(uint32 InHttpStatusCode, uint32 InApiStatusCode, FSharedBuffer&& InBody);`
- L123 _public prototype_ `FS3Response(uint32 InHttpStatusCode, FS3Response&& Other);`
- L127 _public prototype_ `~FS3Response() = default;`
- L129 _public prototype_ `FS3Response& operator=(const FS3Response& Other);`
- L130 _public prototype_ `FS3Response& operator=(FS3Response&& Other);`
- L133 _public prototype_ `bool IsOk() const;` — Returns whether the request is considered successful or not.
- L136 _public prototype_ `FString ToString() const;` — Returns the body as text.
- L139 _public prototype_ `FSharedBuffer GetBody() const;` — Returns the body as a raw buffer
- L146 _public prototype_ `void GetErrorResponse(FStringBuilderBase& OutErrorMsg) const;` — Returns an error message comprised of the api/http status code and any error that might have been returned as part of the response body. If there response had no errors it the message will be "Success"
- L152 _public prototype_ `FString GetErrorStatus() const;` — Returns a short error message comprised of the api/http status code If there response had no errors it the message will be "Success"
- L157 _private member_ `uint32 HttpStatusCode = 0;` — Status code returned by the HTTP request.
- L160 _private member_ `uint32 ApiStatusCode = 0;` — Status code returned by the API
- L163 _private member_ `FSharedBuffer Body;` — HTTP response body.

#### struct `UE::FS3GetObjectRequest`  
`struct FS3GetObjectRequest`  
_L167-173_
- desc: Request parameters for retrieving objects.
- L170 _public member_ `FString BucketName;` — The bucket name.
- L172 _public member_ `FString Key;` — The object key.

#### struct `UE::FS3HeadObjectRequest`  
`struct FS3HeadObjectRequest`  
_L179-185_
- desc: Request parameters for retrieving object meta data.
- L182 _public member_ `FString BucketName;` — The bucket name.
- L184 _public member_ `FString Key;` — The object key.

#### struct `UE::FS3PutObjectRequest`  
`struct FS3PutObjectRequest`  
_L191-199_
- desc: Request parameters for uploading objects.
- L194 _public member_ `FString BucketName;` — The bucket name.
- L196 _public member_ `FString Key;` — The object key.
- L198 _public member_ `FMemoryView ObjectData;` — The object data.

#### struct `UE::FS3ListObjectsRequest`  
`struct FS3ListObjectsRequest`  
_L205-217_
- desc: Request parameters for listing objects.
- L208 _public member_ `FString BucketName;` — The bucket name.
- L210 _public member_ `FString Prefix;` — The object prefix, i.e. the path.
- L212 _public member_ `TCHAR Delimiter;` — The path delimiter, i.e. '/'.
- L214 _public member_ `int32 MaxKeys = INDEX_NONE;` — Max key(s).
- L216 _public member_ `FString Marker;` — Marker from where to list objects.

#### struct `UE::FS3ListObjectResponse`  
`struct FS3ListObjectResponse : public FS3Response`  
_L220-245_
- inherits: `FS3Response`
- desc: Response parameters when listing objects.
- L223 _public prototype_ `FS3ListObjectResponse() = default;`
- L225 _public function_ `FS3ListObjectResponse(FS3Response&& Other) : FS3Response(MoveTemp(Other))`
- L229 _public function_ `FS3ListObjectResponse(FS3Response&& Other, FString&& InBucketName, TArray<FS3Object>&& InObjects, FString InNextMarker = FString(), bool bInIsTruncated = false) : FS3Response(MoveTemp(Other)) , BucketName(MoveTemp(InBucketName)) , Objects(MoveTemp(InObjects)) , NextMarker(MoveTemp(InNextMarker)) , bIsTruncated(bInIsTruncated)`
- L238 _public member_ `FString BucketName;` — The bucket name.
- L240 _public member_ `TArray<FS3Object> Objects;` — The list of object(s).
- L242 _public member_ `FString NextMarker;` — Marker to use for paginated requests.
- L244 _public member_ `bool bIsTruncated = false;` — Whether the response is truncated.

#### struct `UE::FS3ClientConfig`  
`struct FS3ClientConfig`  
_L254-258_
- desc: S3 client configuration with region and service URL.
- L256 _public member_ `FString Region;`
- L257 _public member_ `FString ServiceUrl;`

#### class `UE::FS3Client`  
`class FS3Client`  
_L263-303_
- desc: A simple HTTP(s) client for down, uploading and listing data objects from Amazon S3.
- L270 _public prototype_ `explicit FS3Client(const FS3ClientConfig& ClientConfig, const FS3ClientCredentials& BasicCredentials);` — Creates a new instance from the specified configuration and credentials.
- L271 _public prototype_ `FS3Client(const FS3Client&) = delete;`
- L272 _public prototype_ `FS3Client(FS3Client&&) = delete;`
- L273 _public prototype_ `~FS3Client();`
- L275 _public prototype_ `FS3Client& operator=(const FS3Client&) = delete;`
- L276 _public prototype_ `FS3Client& operator=(FS3Client&&) = delete;`
- L279 _public function_ `const FS3ClientCredentials& GetCredentials() const` — Returns the credentials.
- L281 _public function_ `const FS3ClientConfig& GetConfig() const` — Returns the client configuration.
- L284 _public prototype_ `FS3GetObjectResponse GetObject(const FS3GetObjectRequest& Request);` — Download an object associated with the specified request parameters.
- L286 _public prototype_ `FS3HeadObjectResponse HeadObject(const FS3HeadObjectRequest& Request);` — Download object meta data.
- L288 _public prototype_ `FS3ListObjectResponse ListObjects(const FS3ListObjectsRequest& Request);` — List all objects described by the specified request parameters.
- L290 _public prototype_ `FS3PutObjectResponse PutObject(const FS3PutObjectRequest& Request);` — Upload an object described by the specified request parameters.
- L292 _public prototype_ `FS3PutObjectResponse TryPutObject(const FS3PutObjectRequest& Request, int32 MaxAttempts = 3, float Delay = 0.5f);` — Retries uploading an object until succeeded or max attempts has been reached.
- L294 _public prototype_ `FS3DeleteObjectResponse DeleteObject(const FS3DeleteObjectRequest& Request);` — Delete an object associated with the specified request parameters.
- L297 _private prototype_ `void Setup(FS3Request& Request);`
- L298 _private prototype_ `void Teardown(FS3Request& Request);`
- L300 _private member_ `FS3ClientConfig Config;`
- L301 _private member_ `FS3ClientCredentials Credentials;`
- L302 _private member_ `TUniquePtr<FConnectionPool> ConnectionPool;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API S3CLIENT_API`
- L17 _namespace_ `namespace UE`
- L105 _function_ `friend inline uint32 GetTypeHash(const FS3Object& Object)` (scope `UE`)
- L176 _typedef_ `using FS3GetObjectResponse = FS3Response;` (scope `UE`) — Response parameters when retrieving objects.
- L188 _typedef_ `using FS3HeadObjectResponse = FS3Response;` (scope `UE`) — Response parameters when retrieving object meta data.
- L202 _typedef_ `using FS3PutObjectResponse = FS3Response;` (scope `UE`) — Response parameters when uploading objects.
- L248 _typedef_ `using FS3DeleteObjectRequest = FS3GetObjectRequest;` (scope `UE`) — Request parameters for deleting objects.
- L251 _typedef_ `using FS3DeleteObjectResponse = FS3Response;` (scope `UE`) — Response parameters when deleting objects.
