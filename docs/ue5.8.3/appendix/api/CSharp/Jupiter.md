# CSharp / Jupiter

- project root: `Source/Programs/UnrealCloudDDC/Jupiter`
- files: 112; symbols: 3149
- symbol kinds: class=324, const=18, ctor=289, enum=21, enumerator=71, event=3, field=545, interface=30, method=1198, operator=6, property=633, record=5, record struct=3, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealCloudDDC/Jupiter/AssemblyInfo.cs` (Jupiter)
_(no declarations)_


### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/AdminController.cs` (Jupiter)


#### class `Jupiter.Controllers.AdminController`  
`public class AdminController : Controller`  
_public; L19-105_
- attrs: `[ApiController] [Route("api/v1/admin")] [Authorize]`
- inherits: `Controller`
- L21 _private field_ `private readonly IRefCleanup _refCleanup`
- L22 _private field_ `private readonly IConfiguration _configuration`
- L23 _private field_ `private readonly IRequestHelper _requestHelper`
- L25-30 _public ctor_ `public AdminController(IRefCleanup refCleanup, IConfiguration configuration, IRequestHelper requestHelper)`
- L40-50 _public method_ `public async Task<IActionResult> RefCleanupAsync()` — attrs: `[HttpPost("refCleanup")]` — Manually run the refs cleanup
- L57-104 _public method_ `public async Task<IActionResult> SettingsAsync()` — attrs: `[HttpGet("settings")]` — Dumps all settings currently in use

#### class `Jupiter.Controllers.RemovedBlobRecords`  
`public class RemovedBlobRecords`  
_public; L107-115_
- L109 _public property_ `public BlobId[] Blobs { get; }`
- L111-114 _public ctor_ `public RemovedBlobRecords(IEnumerable<BlobId> blobs)`

#### class `Jupiter.Controllers.RemovedRefRecordsResponse`  
`public class RemovedRefRecordsResponse`  
_public; L117-125_
- L119-122 _public ctor_ `public RemovedRefRecordsResponse(int countOfRemovedRecords)`
- L124 _public property_ `public int CountOfRemovedRecords { get; }`

#### class `Jupiter.Controllers.UpdatedRecordsResponse`  
`public class UpdatedRecordsResponse`  
_public; L127-148_
- L129-132 _public ctor_ `public UpdatedRecordsResponse(List<UpdatedRecord> updatedRecords)`
- L147 _public property_ `public List<UpdatedRecord> UpdatedRecords { get; }`

#### class `Jupiter.Controllers.UpdatedRecordsResponse.UpdatedRecord`  
`public class UpdatedRecord`  
_public; L135-145_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "Only used by serialization")]`
- L137-141 _public ctor_ `public UpdatedRecord(LastAccessRecord record, DateTime time)`
- L143 _public property_ `public LastAccessRecord Record { get; }`
- L144 _public property_ `public DateTime Time { get; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/AuthController.cs` (Jupiter)


#### class `Jupiter.Controllers.AuthController`  
`public class AuthController : ControllerBase`  
_public; L27-162_
- attrs: `[ApiController] [Route("api/v1/auth")] [Authorize]`
- inherits: `ControllerBase`
- L29 _private field_ `private readonly IRequestHelper _requestHelper`
- L30 _private field_ `private readonly IOptionsMonitor<AuthSettings> _authSettings`
- L32-36 _public ctor_ `public AuthController(IRequestHelper requestHelper, IOptionsMonitor<AuthSettings> authSettings)`
- L43-69 _public method_ `public async Task<ActionResult> GetConfigAsync()` — attrs: `[HttpGet("oidc-configuration")] [AllowAnonymous] [Produces(MediaTypeNames.Application.Octet)]`
- L72-81 _public method_ `public async Task<IActionResult> VerifyAsync([FromRoute][Required] NamespaceId ns)` — attrs: `[HttpGet("{ns}")]`
- L84-108 _public method_ `public IActionResult Actions([FromRoute][Required] NamespaceId ns)` — attrs: `[HttpGet("{ns}/actions")]`
- L111-161 _public method_ `public IActionResult Actions([FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromQuery] string? claims = null)` — attrs: `[HttpGet("{ns}/{bucket}/actions")]`

#### class `Jupiter.Controllers.ActionsResult`  
`public class ActionsResult`  
_public; L164-177_
- L168 _public property_ `public List<JupiterAclAction> Actions { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("actions")]`
- L172 _public property_ `public List<string> LogOutput { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("logOutput")]`
- L176 _public property_ `public List<MatchedPolicy> MatchedPolicies { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("matchedPolicies")]`

#### class `Jupiter.Controllers.MatchedPolicy`  
`public class MatchedPolicy`  
_public; L179-191_
- L183 _public property_ `public List<JupiterAclAction> Actions { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("actions")]`
- L187 _public property_ `public List<string> Claims { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("claims")]`
- L190 _public property_ `public string Name { get; set; }` — attrs: `[CbField("name")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/BlobController.cs` (Jupiter)


#### class `Jupiter.Controllers.BlobsController`  
`public class BlobsController : ControllerBase`  
_public; L30-456_
- attrs: `[ApiController] [Route("api/v1/s", Order = 1)] [Route("api/v1/blobs", Order = 0)] [Authorize]`
- inherits: `ControllerBase`
- L32 _private field_ `private readonly IBlobService _storage`
- L33 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L34 _private field_ `private readonly IRequestHelper _requestHelper`
- L35 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L36 _private field_ `private readonly NginxRedirectHelper _nginxRedirectHelper`
- L37 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L39-47 _public ctor_ `public BlobsController(IBlobService storage, IDiagnosticContext diagnosticContext, IRequestHelper requestHelper, BufferedPayloadFactory bufferedPayloadFactory, NginxRedirectHelper nginxRedirectHelper, INamespacePolicyResolver namespacePolicyResolver)`
- L51-90 _public method_ `public async Task<IActionResult> GetAsync( [Required] NamespaceId ns, [Required] BlobId id, [FromQuery] List<string>? storageLayers = null, [FromQuery] bool supportsRedirect = false, [FromQuery] bool allowOndemandReplication = true)` — attrs: `[HttpGet("{ns}/{id}")] [ProducesDefaultResponseType]`
- L94-120 _public method_ `public async Task<IActionResult> HeadAsync( [Required] NamespaceId ns, [Required] BlobId id, [FromQuery] List<string>? storageLayers = null)` — attrs: `[HttpHead("{ns}/{id}")] [ProducesDefaultResponseType]`
- L124-146 _public method_ `public async Task<IActionResult> ExistsMultipleAsync( [Required] NamespaceId ns, [Required][FromQuery] List<BlobId> id)` — attrs: `[HttpPost("{ns}/exists")] [ProducesDefaultResponseType]`
- L150-172 _public method_ `public async Task<IActionResult> ExistsBodyAsync( [Required] NamespaceId ns, [FromBody] BlobId[] bodyIds)` — attrs: `[HttpPost("{ns}/exist")] [ProducesDefaultResponseType]`
- L174-189 _private method_ `private async Task<BlobContents> GetImplAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool supportsRedirectUri = false, bool allowOndemandReplication = true)`
- L194-232 _public method_ `public async Task<IActionResult> PutAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpPut("{ns}/{id}")] [RequiredContentType(MediaTypeNames.Application.Octet)] [DisableRequestSizeLimit]`
- L237-267 _public method_ `public async Task<IActionResult> PostAsync( [Required] NamespaceId ns)` — attrs: `[HttpPost("{ns}")] [RequiredContentType(MediaTypeNames.Application.Octet)] [DisableRequestSizeLimit]`
- L270-290 _public method_ `public async Task<IActionResult> DeleteAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpDelete("{ns}/{id}")]`
- L293-312 _public method_ `public async Task<IActionResult> DeleteNamespaceAsync( [Required] NamespaceId ns)` — attrs: `[HttpDelete("{ns}")]`
- L314-317 _private method_ `private async Task DeleteImplAsync(NamespaceId ns, BlobId id)`
- L351-455 _public method_ `public async Task<IActionResult> PostAsync([FromBody] BatchCall batch)` — attrs: `[HttpPost("")]`

#### class `Jupiter.Controllers.BlobsController.BatchOp`  
`public class BatchOp`  
_public; L322-341_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "Used by serialization")]`
- L334 _public property_ `public NamespaceId? Namespace { get; set; }` — attrs: `[Required]`
- L336 _public property_ `public BlobId? Id { get; set; }`
- L338 _public property_ `public Operation Op { get; set; }` — attrs: `[Required]`
- L340 _public property_ `public byte[]? Content { get; set; }`

#### enum `Jupiter.Controllers.BlobsController.BatchOp.Operation`  
`public enum Operation`  
_public; L325-332_
- L327 _public* enumerator_ `INVALID`
- L328 _public* enumerator_ `GET`
- L329 _public* enumerator_ `PUT`
- L330 _public* enumerator_ `DELETE`
- L331 _public* enumerator_ `HEAD`

#### class `Jupiter.Controllers.BlobsController.BatchCall`  
`public class BatchCall`  
_public; L344-347_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "Used by serialization")]`
- L346 _public property_ `public BatchOp[]? Operations { get; set; }`

#### class `Jupiter.Controllers.BlobUploadResponse`  
`public class BlobUploadResponse`  
_public; L458-472_
- L460-463 _public ctor_ `public BlobUploadResponse()`
- L465-468 _public ctor_ `public BlobUploadResponse(BlobId identifier)`
- L471 _public property_ `public BlobId Identifier { get; set; }` — attrs: `[CbField("identifier")]`

#### class `Jupiter.Controllers.BlobUploadUriResponse`  
`public class BlobUploadUriResponse`  
_public; L474-492_
- L476-479 _public ctor_ `public BlobUploadUriResponse()`
- L481-485 _public ctor_ `public BlobUploadUriResponse(BlobId identifier, Uri redirectUri)`
- L488 _public property_ `public BlobId Identifier { get; set; }` — attrs: `[CbField("identifier")]`
- L491 _public property_ `public Uri? RedirectUri { get; set; }` — attrs: `[CbField("redirectUri")]`

#### class `Jupiter.Controllers.HeadMultipleResponse`  
`public class HeadMultipleResponse`  
_public; L494-498_
- L497 _public property_ `public BlobId[] Needs { get; set; }` — attrs: `[CbField("needs")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/BuildsController.cs` (Jupiter)


#### class `Jupiter.Controllers.BuildsController`  
`public class BuildsController : ControllerBase`  
_public; L54-2518_
- attrs: `[ApiController] [Route("api/v2/builds", Order = 0)] [Authorize] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [FormatFilter]`
- inherits: `ControllerBase`
- L56 _private field_ `private readonly IRefService _refService`
- L57 _private field_ `private readonly IBlobService _blobStore`
- L58 _private field_ `private readonly IBlockStore _blockStore`
- L59 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L60 _private field_ `private readonly FormatResolver _formatResolver`
- L61 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L62 _private field_ `private readonly NginxRedirectHelper _nginxRedirectHelper`
- L63 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L64 _private field_ `private readonly IRequestHelper _requestHelper`
- L65 _private field_ `private readonly Tracer _tracer`
- L66 _private field_ `private readonly ILogger<BuildsController> _logger`
- L67 _private field_ `private readonly IBuildStore _buildStore`
- L68 _private field_ `private readonly IBlobIndex _blobIndex`
- L69 _private field_ `private readonly IReferenceResolver _referenceResolver`
- L70 _private field_ `private readonly ILogger? _auditLogger`
- L75 _private const_ `private const string BuildPartType = "parts"` — Constant used for access control of parts
- L77-94 _public ctor_ `public BuildsController(IRefService refService, IBlobService blobStore, IBlockStore blockStore, IBuildStore buildStore, IBlobIndex blobIndex, IReferenceResolver referenceResolver, IDiagnosticContext diagnosticContext, FormatResolver formatResolver, BufferedPayloadFactory bufferedPayloadFactory, NginxRedirectHelper nginxRedirectHelper, INamespacePolicyResolver namespacePolicyResolver, IRequestHelper requestHelper, Tracer tracer, ILogger<BuildsController> logger, IOptionsMonitor<BuildsSettings> settings)`
- L100-181 _public method_ `public async Task<IActionResult> PutBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}.{format?}")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L183 _private const_ `private const int DefaultChunkSize = 32 * 1024 * 1024`
- L187-233 _public method_ `public async Task<IActionResult> FinalizeBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/finalize")] [ProducesDefaultResponseType]`
- L237-262 _public method_ `public async Task<IActionResult> GetTTLAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/ttl")] [ProducesDefaultResponseType]`
- L266-297 _public method_ `public async Task<IActionResult> UpdateTTLAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, [FromBody] UpdateTTLRequest request)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/updateTTL")] [ProducesDefaultResponseType]`
- L301-338 _public method_ `public async Task<IActionResult> DeleteBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)` — attrs: `[HttpDelete("{ns}/{bucket}/{buildId}")] [ProducesDefaultResponseType]`
- L342-422 _public method_ `public async Task<IActionResult> GetBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string? format = null)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}.{format?}")] [ProducesDefaultResponseType]`
- L427-514 _public method_ `public async Task<IActionResult> SearchBuildAsync(NamespaceId ns, BucketId bucket, [FromBody] SearchRequest searchRequest)` — attrs: `[HttpPost("{ns}/{bucket}/search")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L520-702 _public method_ `public async Task<IActionResult> SearchBucketsAsync(NamespaceId ns, [FromBody] SearchBucketsRequest searchBucketRequest)` — attrs: `[HttpPost("{ns}/search")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L707-893 _public method_ `public async Task<IActionResult> CopyBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, [FromBody] CopyBuildRequest request)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/copyBuild")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L900-1009 _public method_ `public async Task<IActionResult> GetBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string partId, [FromRoute] string? format = null)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/parts/{partId}.{format?}")] [Produces(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L1015-1115 _public method_ `public async Task<IActionResult> PutBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, string partName)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/{partName}.{format?}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L1117-1166 _private method_ `private async Task<List<ContentHash>> PutBuildPartRefAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, BlockContext blockContext, CbObject payloadObject, BlobId payloadHash)`
- L1170-1253 _public method_ `public async Task<IActionResult> FinalizeBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, BlobId hash)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/parts/{partId}/finalize/{hash}.{format?}")] [ProducesDefaultResponseType]`
- L1255-1277 _private method_ `private async Task<BuildRecord?> GetBuildWithRetriesAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L1279-1286 _private method_ `private async Task DoFinalizeBuildPartAsync(NamespaceId ns, BlockContext blockContext, List<BlobId> blockMetadataIds, CancellationToken cancellationToken)`
- L1292-1436 _public method_ `public async Task<IActionResult> GetAppendixFileAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixFileName)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/appendix/{appendixFileName}")] [Produces(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L1442-1579 _public method_ `public async Task<IActionResult> PutAppendixFileAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixFileName)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/appendix/{appendixFileName}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json, CustomMediaTypeNames.UnrealCompressedBuffer, MediaTyp`
- L1583-1620 _public method_ `public async Task<IActionResult> DeleteAppendixFileAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixFileName)` — attrs: `[HttpDelete("{ns}/{bucket}/{buildId}/appendix/{appendixFileName}")] [ProducesDefaultResponseType]`
- L1625-1652 _public method_ `public async Task<IActionResult> ListAppendixFilesAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/appendix")] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L1658-1738 _public method_ `public async Task<IActionResult> GetBuildPartFileListAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/parts/{partId}/fileList")] [ProducesDefaultResponseType]`
- L1744-1783 _public method_ `public async Task<IActionResult> PutBuildPartStatsAsync( NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, [Required] [FromBody] BuildPartStatsRequest statsRequest)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/stats")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)] [ProducesDefaultResponseType]`
- L1795-1852 _public method_ `public async Task<IActionResult> GetBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [Required] ContentId id, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/parts/{partId}/blobs/{id}")] [HttpGet("{ns}/{bucket}/{buildId}/blobs/{id}")] [ProducesResponseType(type: typeof(byte[]), 200)] [ProducesResponseType(type: typeof(ValidationProblemDetails), 400)] [Produces(C`
- L1859-1925 _public method_ `public async Task<IActionResult> PutBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [Required] BlobId id)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/blobs/{id}.{format?}")] [HttpPut("{ns}/{bucket}/{buildId}/blobs/{id}.{format?}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Ap`
- L1931-1957 _public method_ `public async Task<IActionResult> StartBlobMultipartUploadAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromBody] [Required] StartMultipartUploadRequest request)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/parts/{partId}/blobs/{id}/startMultipartUpload")] [HttpPost("{ns}/{bucket}/{buildId}/blobs/{id}/startMultipartUpload")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Applica`
- L1964-1997 _public method_ `public async Task<IActionResult> PutBlobMultipartPartAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromQuery] [Required] string blobName, [FromQuery] [Required] string uploadId, [FromQuery] [Required] string partId, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/blobs/{id}/uploadMultipart")] [HttpPut("{ns}/{bucket}/{buildId}/blobs/{id}/uploadMultipart")] [DisableRequestSizeLimit] [RequiredContentType(MediaTypeNames.Application.Octet)]`
- L2001-2047 _public method_ `public async Task<IActionResult> CompleteBlobMultipartUploadAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute] [Required] BlobId id, [FromBody] [Required] CompleteMultipartUploadRequest request)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/parts/{partId}/blobs/{id}/completeMultipart")] [HttpPost("{ns}/{bucket}/{buildId}/blobs/{id}/completeMultipart")]`
- L2056-2059 _public method_ `public async Task<IActionResult> PutBlockAsync(NamespaceId ns, BucketId bucket, BlobId id)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/blocks/{id}.{format?}")] [HttpPut("{ns}/{bucket}/{buildId}/blocks/{id}.{format?}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.`
- L2066-2133 _public method_ `public async Task<IActionResult> PutBlockMetadataAsync(NamespaceId ns, BucketId bucket, BlobId id)` — attrs: `[HttpPut("{ns}/{bucket}/{buildId}/parts/{partId}/blocks/{id}/metadata")] [HttpPut("{ns}/{bucket}/{buildId}/blocks/{id}/metadata")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary)] [ProducesDefaultRes`
- L2135-2143 _private method_ `private ActionResult? VerifyBlockMetadata(CbObject metadataObject)`
- L2148-2151 _public method_ `public async Task<IActionResult> GetBlockAsync(NamespaceId ns, BucketId bucket, ContentId blockIdentifier, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/parts/{partId}/blocks/{blockIdentifier}")] [HttpGet("{ns}/{bucket}/{buildId}/blocks/{blockIdentifier}")] [Produces(MediaTypeNames.Application.Octet, CustomMediaTypeNames.UnrealCompressedBuffer)]`
- L2156-2251 _public method_ `public async Task<IActionResult> GetBlockMetadataAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, GetBlockMetadataRequest request)` — attrs: `[HttpPost("{ns}/{bucket}/{buildId}/parts/{partId}/blocks/getBlockMetadata")] [HttpPost("{ns}/{bucket}/{buildId}/blocks/getBlockMetadata")] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)]`
- L2256-2394 _public method_ `public async Task<IActionResult> ListBlockAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string? format = null, [FromQuery] int count = 5000, [FromQuery] int skip = 0, [FromQuery] int maxConsidered = 25_000, [FromQuery] bool sort = true)` — attrs: `[HttpGet("{ns}/{bucket}/{buildId}/parts/{partId}/blocks/listBlocks")] [HttpGet("{ns}/{bucket}/{buildId}/blocks/listBlocks")] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)]`
- L2406-2410 _public method_ `public async Task<IActionResult> EmptyOptionsAsync()` — attrs: `[HttpOptions("")] [HttpOptions("{ns}")] [HttpOptions("{ns}/{bucket}/search")] [ProducesDefaultResponseType]`
- L2414-2440 _public method_ `public async Task<IActionResult> GetNamespacesAsync()` — attrs: `[HttpGet("")] [ProducesDefaultResponseType]`
- L2444-2469 _public method_ `public async Task<IActionResult> GetBucketsAsync(NamespaceId ns)` — attrs: `[HttpGet("{ns}")] [ProducesDefaultResponseType]`
- L2473-2494 _private method_ `private void LogAuditEntry(HttpMethod method, string endpoint, NamespaceId? ns, BucketId? bucketId, CbObjectId? buildId, string? partId)`
- L2496-2517 _private method_ `private void LogAuditEntry(HttpMethod method, string endpoint, string sessionHeader, string username, string userAgent, string ip, string jti, NamespaceId? ns, BucketId? bucketId, CbObjectId? buildId, string? partId)`

#### class `Jupiter.Controllers.FileList`  
`public class FileList`  
_public; L2520-2537_
- L2523 _public property_ `public ulong TotalSize { get; set; }` — attrs: `[CbField("totalSize")]`
- L2526 _public property_ `public string[] Paths { get; set; }` — attrs: `[CbField("paths")]`
- L2529 _public property_ `public IoHash[] RawHashes { get; set; }` — attrs: `[CbField("rawHashes")]`
- L2532 _public property_ `public ulong[] RawSizes { get; set; }` — attrs: `[CbField("rawSizes")]`
- L2534 _public property_ `public uint[] Attributes { get; set; }` — attrs: `[CbField("attributes")]`
- L2536 _public property_ `public uint[] Modes { get; set; }` — attrs: `[CbField("modes")]`

#### class `Jupiter.Controllers.BuildsSettings`  
`public class BuildsSettings`  
_public; L2539-2542_
- L2541 _public property_ `public bool EnableAuditLog { get; set; }`

#### class `Jupiter.Controllers.GetBlockMetadataRequest`  
`public class GetBlockMetadataRequest`  
_public; L2544-2550_
- L2548 _public property_ `public List<IoHash> Blocks { get; set; }` — attrs: `[CbField("blocks")]`

#### class `Jupiter.Controllers.BuildPartStatsRequest`  
`public class BuildPartStatsRequest`  
_public; L2552-2558_
- L2556 _public property_ `public Dictionary<string, double> FloatStats { get; set; }` — attrs: `[CbField("floatStats")]`

#### class `Jupiter.Controllers.PutBuildResponse`  
`public class PutBuildResponse`  
_public; L2560-2564_
- L2563 _public property_ `public uint ChunkSize { get; set; }` — attrs: `[CbField("chunkSize")]`

#### class `Jupiter.Controllers.StartMultipartUploadRequest`  
`public class StartMultipartUploadRequest`  
_public; L2566-2570_
- L2569 _public property_ `public ulong BlobLength { get; set; }` — attrs: `[CbField("blobLength")]`

#### class `Jupiter.Controllers.CompleteMultipartUploadRequest`  
`public class CompleteMultipartUploadRequest`  
_public; L2572-2587_
- L2575 _public property_ `public string BlobName { get; set; }` — attrs: `[CbField("blobName")]`
- L2578 _public property_ `public string UploadId { get; set; }` — attrs: `[CbField("uploadId")]`
- L2581 _public property_ `public bool IsCompressed { get; set; }` — attrs: `[CbField("isCompressed")]`
- L2585 _public property_ `public List<string> PartIds { get; set; }` — attrs: `[CbField("partIds")]`

#### class `Jupiter.Controllers.CompleteMultipartUploadResponse`  
`public class CompleteMultipartUploadResponse`  
_public; L2589-2605_
- L2591-2593 _public ctor_ `public CompleteMultipartUploadResponse()`
- L2595-2598 _public ctor_ `public CompleteMultipartUploadResponse(List<string> missingParts)`
- L2602 _public property_ `public List<string> MissingParts { get; set; }` — attrs: `[CbField("missingParts")]`

#### class `Jupiter.Controllers.MultipartUploadIdResponse`  
`public class MultipartUploadIdResponse`  
_public; L2607-2619_
- L2610 _public property_ `public string UploadId { get; set; }` — attrs: `[CbField("uploadId")]`
- L2613 _public property_ `public string BlobName { get; set; }` — attrs: `[CbField("blobName")]`
- L2617 _public property_ `public List<MultipartPartDescription> Parts { get; set; }` — attrs: `[CbField("parts")]`

#### class `Jupiter.Controllers.MultipartPartDescription`  
`public class MultipartPartDescription`  
_public; L2621-2631_
- L2624 _public property_ `public ulong FirstByte { get; set; }` — attrs: `[CbField("firstByte")]`
- L2626 _public property_ `public ulong LastByte { get; set; }` — attrs: `[CbField("lastByte")]`
- L2628 _public property_ `public string PartId { get; set; }` — attrs: `[CbField("partId")]`
- L2630 _public property_ `public string QueryString { get; set; }` — attrs: `[CbField("queryString")]`

#### class `Jupiter.Controllers.GetTTLResponse`  
`public class GetTTLResponse`  
_public; L2633-2637_
- L2636 _public property_ `public uint TTL { get; set; }` — attrs: `[CbField("ttl")]`

#### class `Jupiter.Controllers.UpdateTTLRequest`  
`public class UpdateTTLRequest`  
_public; L2639-2648_
- L2647 _public property_ `public uint TTL { get; set; }` — attrs: `[Range(120, 31536000)] [Required] [CbField("ttl")]` — New TTL to set in seconds, lowest valid value is 120 seconds and max is 1 year (31536000 seconds)

#### class `Jupiter.Controllers.CopyBuildResponse`  
`public class CopyBuildResponse`  
_public; L2650-2654_
- L2653 _public property_ `public CbObjectId BuildId { get; set; }` — attrs: `[CbField("buildId")]`

#### class `Jupiter.Controllers.CopyBuildRequest`  
`public class CopyBuildRequest`  
_public; L2656-2672_
- L2659 _public property_ `public BucketId NewBucket { get; set; }` — attrs: `[CbField("bucketId")]`
- L2662 _public property_ `public NamespaceId? NewNamespace { get; set; }` — attrs: `[CbField("newNamespace")]`
- L2665 _public property_ `public string? NewBranch { get; set; }` — attrs: `[CbField("newBranch")]`
- L2668 _public property_ `public string? NewProject { get; set; }` — attrs: `[CbField("newProject")]`
- L2671 _public property_ `public string? NewPlatform { get; set; }` — attrs: `[CbField("newPlatform")]`

#### class `Jupiter.Controllers.ListAppendixFileResponse`  
`public class ListAppendixFileResponse`  
_public; L2674-2680_
- L2678 _public property_ `public List<string> Appendices { get; set; }` — attrs: `[CbField("appendices")]`

#### class `Jupiter.Controllers.BuildSearchResult`  
`public class BuildSearchResult`  
_public; L2682-2694_
- L2685 _public property_ `public CbObjectId BuildId { get; set; }` — attrs: `[CbField("buildId")]`
- L2688 _public property_ `public uint? TTL { get; set; }` — attrs: `[CbField("ttl")]`
- L2690 _public property_ `public CbObject Metadata { get; set; }` — attrs: `[CbField("metadata")]`
- L2693 _public property_ `public bool IsFinalized { get; set; }` — attrs: `[CbField("isFinalized")]`

#### class `Jupiter.Controllers.SearchResult`  
`public class SearchResult`  
_public; L2696-2718_
- L2701 _public property_ `public List<BuildSearchResult> Results { get; set; }` — attrs: `[CbField("results")] [CbConverter(typeof(CbUniformObjectListConverter<BuildSearchResult>))]`
- L2705 _public property_ `public bool PartialResult { get; set; }` — attrs: `[CbField("partialResult")]`
- L2707-2711 _public ctor_ `public SearchResult()`
- L2713-2717 _public ctor_ `public SearchResult(List<BuildMetadata> foundResults, bool partialResult)`

#### class `Jupiter.Controllers.SearchOptions`  
`public class SearchOptions`  
_public; L2720-2741_
- L2723 _public property_ `public int Limit { get; set; }` — attrs: `[CbField("limit")]`
- L2726 _public property_ `public int Skip { get; set; }` — attrs: `[CbField("skip")]`
- L2729 _public property_ `public int Max { get; set; }` — attrs: `[CbField("max")]`
- L2732 _public property_ `public uint MaxTimeMs { get; set; }` — attrs: `[CbField("maxTimeMS")]`
- L2735 _public property_ `public bool IncludeTTL { get; set; }` — attrs: `[CbField("includeTTL")]`
- L2740 _public property_ `public bool IncludePartial { get; set; }` — attrs: `[CbField("includePartial")]`

#### class `Jupiter.Controllers.SearchRequest`  
`public class SearchRequest`  
_public; L2743-2780_
- L2747 _public property_ `public CbObject? QueryCB { get; set; }` — attrs: `[CbField("query")] [JsonIgnore]`
- L2753 _public property_ `public object Query { get; set; }` — attrs: `[CbIgnore]`
- L2757 _public property_ `public SearchOptions Options { get; set; }` — attrs: `[CbField("options")]`
- L2759-2779 _internal method_ `internal List<ISearchOp> ToSearchOps()`

#### class `Jupiter.Controllers.SearchBucketsRequest`  
`public class SearchBucketsRequest : SearchRequest`  
_public; L2781-2785_
- inherits: `SearchRequest`
- L2784 _public property_ `public string BucketRegex { get; set; }` — attrs: `[CbField("bucketRegex")]`

#### class `Jupiter.Controllers.BuildSearchResultBucket`  
`public class BuildSearchResultBucket`  
_public; L2787-2800_
- L2790 _public property_ `public CbObjectId BuildId { get; set; }` — attrs: `[CbField("buildId")]`
- L2793 _public property_ `public BucketId BucketId { get; set; }` — attrs: `[CbField("bucketId")]`
- L2796 _public property_ `public uint? TTL { get; set; }` — attrs: `[CbField("ttl")]`
- L2799 _public property_ `public CbObject Metadata { get; set; }` — attrs: `[CbField("metadata")]`

#### class `Jupiter.Controllers.SearchMultipleBucketsResult`  
`public class SearchMultipleBucketsResult`  
_public; L2802-2824_
- L2807 _public property_ `public List<BuildSearchResultBucket> Results { get; set; }` — attrs: `[CbField("results")] [CbConverter(typeof(CbUniformObjectListConverter<BuildSearchResultBucket>))]`
- L2811 _public property_ `public bool PartialResult { get; set; }` — attrs: `[CbField("partialResult")]`
- L2813-2817 _public ctor_ `public SearchMultipleBucketsResult()`
- L2819-2823 _public ctor_ `public SearchMultipleBucketsResult(List<BuildMetadata> foundResults, bool partialResult)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/CompressedBlobController.cs` (Jupiter)


#### class `Jupiter.Controllers.CompressedBlobController`  
`public class CompressedBlobController : ControllerBase`  
_public; L30-354_
- attrs: `[ApiController] [Authorize] [Route("api/v1/compressed-blobs")]`
- inherits: `ControllerBase`
- L32 _private field_ `private readonly IBlobService _storage`
- L33 _private field_ `private readonly IContentIdStore _contentIdStore`
- L34 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L35 _private field_ `private readonly IRequestHelper _requestHelper`
- L36 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L37 _private field_ `private readonly NginxRedirectHelper _nginxRedirectHelper`
- L38 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L40-49 _public ctor_ `public CompressedBlobController(IBlobService storage, IContentIdStore contentIdStore, IDiagnosticContext diagnosticContext, IRequestHelper requestHelper, BufferedPayloadFactory bufferedPayloadFactory, NginxRedirectHelper nginxRedirectHelper, INamespacePolicyResolver namespacePolicyResolver)`
- L56-109 _public method_ `public async Task<IActionResult> GetAsync( [Required] NamespaceId ns, [Required] ContentId id, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpGet("{ns}/{id}")] [ProducesResponseType(type: typeof(byte[]), 200)] [ProducesResponseType(type: typeof(ValidationProblemDetails), 400)] [Produces(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Application.Octet)]`
- L113-145 _public method_ `public async Task<IActionResult> HeadAsync( [Required] NamespaceId ns, [Required] ContentId id)` — attrs: `[HttpHead("{ns}/{id}")] [ProducesDefaultResponseType]`
- L149-187 _public method_ `public async Task<IActionResult> ExistsMultipleAsync( [Required] NamespaceId ns, [Required][FromQuery] List<ContentId> id)` — attrs: `[HttpPost("{ns}/exists")] [ProducesDefaultResponseType]`
- L191-228 _public method_ `public async Task<IActionResult> ExistsBodyAsync( [Required] NamespaceId ns, [FromBody] ContentId[] bodyIds)` — attrs: `[HttpPost("{ns}/exist")] [ProducesDefaultResponseType]`
- L233-271 _public method_ `public async Task<IActionResult> PutAsync( [Required] NamespaceId ns, [Required] ContentId id)` — attrs: `[HttpPut("{ns}/{id}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer)]`
- L276-315 _public method_ `public async Task<IActionResult> PostAsync( [Required] NamespaceId ns)` — attrs: `[HttpPost("{ns}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer)]`
- L318-353 _public method_ `public async Task<IActionResult> DeleteAsync( [Required] NamespaceId ns, [Required] ContentId id)` — attrs: `[HttpDelete("{ns}/{id}")]`

#### class `Jupiter.Controllers.ExistCheckMultipleContentIdResponse`  
`public class ExistCheckMultipleContentIdResponse`  
_public; L356-360_
- L359 _public property_ `public ContentId[] Needs { get; set; }` — attrs: `[CbField("needs")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ContentIdController.cs` (Jupiter)


#### class `Jupiter.Controllers.ContentIdController`  
`public class ContentIdController : ControllerBase`  
_public; L20-94_
- attrs: `[ApiController] [FormatFilter] [Produces(MediaTypeNames.Application.Json, MediaTypeNames.Application.Octet, CustomMediaTypeNames.UnrealCompactBinary)] [Route("api/v1/content-id")] [Authorize]`
- inherits: `ControllerBase`
- L22 _private field_ `private readonly IRequestHelper _requestHelper`
- L23 _private field_ `private readonly IContentIdStore _contentIdStore`
- L25-29 _public ctor_ `public ContentIdController(IRequestHelper requestHelper, IContentIdStore contentIdStore)`
- L39-62 _public method_ `public async Task<IActionResult> ResolveAsync(NamespaceId ns, ContentId contentId)` — attrs: `[HttpGet("{ns}/{contentId}.{format?}", Order = 500)] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]` — Returns which blobs a content id maps to
- L75-93 _public method_ `public async Task<IActionResult> UpdateContentIdMappingAsync(NamespaceId ns, ContentId contentId, BlobId blobIdentifier, ulong compressedSize, ulong rawSize)` — attrs: `[HttpPut("{ns}/{contentId}/update/{blobIdentifier}/{compressedSize}/{rawSize}", Order = 500)] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]` — Update a content id mapping

#### class `Jupiter.Controllers.ResolvedContentIdResponse`  
`public class ResolvedContentIdResponse`  
_public; L96-104_
- L98 _public property_ `public BlobId[] Blobs { get; set; }`
- L100-103 _public ctor_ `public ResolvedContentIdResponse(BlobId[] blobs)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/DebugController.cs` (Jupiter)


#### class `Jupiter.Controllers.DebugController`  
`public class DebugController : Controller`  
_public; L14-85_
- attrs: `[ApiController] [Route("api/v1/c/_debug")]`
- inherits: `Controller`
- L16 _private field_ `private readonly IOptionsMonitor<DebugSettings> _settings`
- L17 _private field_ `private int _currentConcurrentCalls`
- L19-22 _public ctor_ `public DebugController(IOptionsMonitor<DebugSettings> settings)`
- L29-50 _public method_ `public IActionResult GetBytes([FromQuery] int length = 1)` — attrs: `[HttpGet("getBytes")] [Authorize]` — Return bytes of specified length with auth, used for testing only
- L57-77 _public method_ `public IActionResult GetBytesWithoutAuth([FromQuery] int length = 1)` — attrs: `[HttpGet("getBytesWithoutAuth")]` — Return bytes of specified length without auth, used for testing only
- L79-84 _private method_ `private FileContentResult GenerateByteResponse(int length)`

#### class `Jupiter.Controllers.DebugSettings`  
`public class DebugSettings`  
_public; L87-91_
- L89 _public property_ `public bool EnableDebugEndpoints { get; set; }`
- L90 _public property_ `public int MaxConcurrentCalls { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/FormatResolver.cs` (Jupiter)


#### class `Jupiter.Controllers.FormatResolver`  
`public class FormatResolver`  
_public; L14-75_
- L16 _private field_ `private readonly IOptionsMonitor<MvcOptions> _mvcOptions`
- L18 _private field_ `private readonly string[] _validContentTypes = { MediaTypeNames.Application.Octet, MediaTypeNames.Application.Json, CustomMediaTypeNames.UnrealCompactBinary, CustomMediaTypeNames.JupiterInlinedPayload, CustomMediaTypeNames.UnrealCompressedBuffer,  ...`
- L27-30 _public ctor_ `public FormatResolver(IOptionsMonitor<MvcOptions> mvcOptions)`
- L32-74 _public method_ `public string GetResponseType(HttpRequest request, string? format, string defaultContentType)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/IRequestHelper.cs` (Jupiter)


#### interface `Jupiter.Controllers.IRequestHelper`  
`public interface IRequestHelper`  
_public; L11-17_
- L13 _public method_ `public Task<ActionResult?> HasAccessToScopeAsync(ClaimsPrincipal user, HttpRequest request, AccessScope scope, JupiterAclAction[] aclActions)`
- L15 _public method_ `public bool IsPublicPort(HttpContext context)`
- L16 _public* method_ `IActionResult? EnsureSingleRangeRequest(HttpContext context)`

#### class `Jupiter.Controllers.AuthorizationException`  
`public class AuthorizationException : Exception`  
_public; L19-27_
- inherits: `Exception`
- L21 _public property_ `public ActionResult Result { get; }`
- L23-26 _public ctor_ `public AuthorizationException(ActionResult result, string errorMessage) : base(errorMessage)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ObjectController.cs` (Jupiter)


#### class `Jupiter.Controllers.ObjectController`  
`public class ObjectController : ControllerBase`  
_public; L30-296_
- attrs: `[ApiController] [Route("api/v1/objects", Order = 0)] [Authorize] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Json)]`
- inherits: `ControllerBase`
- L32 _private field_ `private readonly IBlobService _storage`
- L33 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L34 _private field_ `private readonly IRequestHelper _requestHelper`
- L35 _private field_ `private readonly IReferenceResolver _referenceResolver`
- L36 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L38 _private field_ `private readonly ILogger _logger`
- L40-48 _public ctor_ `public ObjectController(IBlobService storage, IDiagnosticContext diagnosticContext, IRequestHelper requestHelper, IReferenceResolver referenceResolver, BufferedPayloadFactory bufferedPayloadFactory, ILogger<ObjectController> logger)`
- L52-76 _public method_ `public async Task<IActionResult> GetAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpGet("{ns}/{id}")] [ProducesDefaultResponseType]`
- L80-105 _public method_ `public async Task<IActionResult> HeadAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpHead("{ns}/{id}")] [ProducesDefaultResponseType]`
- L109-131 _public method_ `public async Task<IActionResult> ExistsMultipleAsync( [Required] NamespaceId ns, [Required][FromQuery] List<BlobId> id)` — attrs: `[HttpPost("{ns}/exists")] [ProducesDefaultResponseType]`
- L135-157 _public method_ `public async Task<IActionResult> ExistsBodyAsync( [Required] NamespaceId ns, [FromBody] BlobId[] bodyIds)` — attrs: `[HttpPost("{ns}/exist")] [ProducesDefaultResponseType]`
- L161-187 _public method_ `public async Task<IActionResult> PutAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpPut("{ns}/{id}")] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary)]`
- L190-247 _public method_ `public async Task<IActionResult> ResolveReferencesAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpGet("{ns}/{id}/references")]`
- L250-273 _public method_ `public async Task<IActionResult> DeleteAsync( [Required] NamespaceId ns, [Required] BlobId id)` — attrs: `[HttpDelete("{ns}/{id}")]`
- L276-295 _public method_ `public async Task<IActionResult> DeleteNamespaceAsync( [Required] NamespaceId ns)` — attrs: `[HttpDelete("{ns}")]`

#### class `Jupiter.Controllers.PutBlobResponse`  
`public class PutBlobResponse`  
_public; L298-312_
- L300-303 _public ctor_ `public PutBlobResponse()`
- L305-308 _public ctor_ `public PutBlobResponse(BlobId identifier)`
- L311 _public property_ `public BlobId Identifier { get; set; }` — attrs: `[CbField("identifier")]`

#### class `Jupiter.Controllers.DeletedResponse`  
`public class DeletedResponse`  
_public; L314-317_
- L316 _public property_ `public int DeletedCount { get; set; }`

#### class `Jupiter.Controllers.ResolvedReferencesResult`  
`public class ResolvedReferencesResult`  
_public; L319-333_
- L321-324 _public ctor_ `public ResolvedReferencesResult()`
- L326-329 _public ctor_ `public ResolvedReferencesResult(BlobId[] references)`
- L332 _public property_ `public BlobId[] References { get; set; }` — attrs: `[CbField("references")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ProblemTypes.cs` (Jupiter)


#### class `Jupiter.Controllers.ProblemTypes`  
`public static class ProblemTypes`  
_public; L5-10_
- L7 _public property_ `public static string UseSnapshot { get; set; }`
- L8 _public property_ `public static string NoDataFound { get; set; }`
- L9 _public property_ `public static string HashMismatchError { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ReferencesController.cs` (Jupiter)


#### class `Jupiter.Controllers.ReferencesController`  
`public class ReferencesController : ControllerBase`  
_public; L45-1587_
- attrs: `[ApiController] [FormatFilter] [Produces(MediaTypeNames.Application.Json, MediaTypeNames.Application.Octet, CustomMediaTypeNames.UnrealCompactBinary)] [Route("api/v1/refs")] [Authorize]`
- inherits: `ControllerBase`
- L47 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L48 _private field_ `private readonly FormatResolver _formatResolver`
- L49 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L50 _private field_ `private readonly IReferenceResolver _referenceResolver`
- L51 _private field_ `private readonly NginxRedirectHelper _nginxRedirectHelper`
- L52 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L53 _private field_ `private readonly IRequestHelper _requestHelper`
- L54 _private field_ `private readonly Tracer _tracer`
- L56 _private field_ `private readonly ILogger _logger`
- L57 _private field_ `private readonly IRefService _refService`
- L58 _private field_ `private readonly IBlobService _blobStore`
- L59 _private field_ `private readonly IBlobIndex _blobIndex`
- L60 _private field_ `private readonly IPeerStatusService _peerStatusService`
- L62-77 _public ctor_ `public ReferencesController(IRefService refService, IBlobService blobStore, IBlobIndex blobIndex, IPeerStatusService peerStatusService, IDiagnosticContext diagnosticContext, FormatResolver formatResolver, BufferedPayloadFactory bufferedPayloadFactory, IReferenceResolver referenceResolver, NginxRedirectHelper nginxRedirectHelper, INamespacePolicyResolver namespacePolicyResolver, IRequestHelper requestHelper, Tracer tracer, ILogger<ReferencesController> logger)`
- L86-114 _public method_ `public async Task<IActionResult> GetNamespacesAsync()` — attrs: `[HttpGet("")] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]` — Returns all the known namespace the token has access to
- L126-466 _public method_ `public async Task<IActionResult> GetAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [FromRoute] string? format = null, [FromHeader(Name = CommonHeaders.ForceConsistentRead)] bool forceConsistentRead = false)` — attrs: `[HttpGet("{ns}/{bucket}/{key}.{format?}", Order = 500)] [Produces(MediaTypeNames.Application.Json, MediaTypeNames.Application.Octet, CustomMediaTypeNames.UnrealCompactBinary, CustomMediaTypeNames.JupiterInlinedPayload, CustomMediaTypeNames.` — Returns a refs key
- L476-510 _public method_ `public async Task<IActionResult> GetMetadataAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [FromQuery] string[] fields)` — attrs: `[HttpGet("{ns}/{bucket}/{key}/metadata", Order = 500)]` — Returns the metadata about a ref key
- L519-569 _public method_ `public async Task<IActionResult> GetReplicationStateAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key)` — attrs: `[HttpGet("{ns}/{bucket}/{key}/replicationState", Order = 500)]` — Returns the replicated state of this ref across all known cloud ddc regions
- L578-656 _public method_ `public async Task<IActionResult> GetReferencedBlobsAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key)` — attrs: `[HttpGet("{ns}/{bucket}/{key}/references", Order = 500)]` — Returns the blobs referenced by this ref
- L668-745 _public method_ `public async Task<IActionResult> HeadAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key)` — attrs: `[HttpHead("{ns}/{bucket}/{key}", Order = 500)] [ProducesResponseType(type: typeof(OkResult), 200)] [ProducesResponseType(type: typeof(ValidationProblemDetails), 400)]` — Checks if a object exists
- L749-829 _public method_ `public async Task<IActionResult> ExistsMultipleAsync( [FromRoute][Required] NamespaceId ns, [FromQuery][Required] List<string> names)` — attrs: `[HttpGet("{ns}/exists")] [ProducesDefaultResponseType]`
- L833-999 _public method_ `public async Task<IActionResult> PutObjectAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [FromHeader(Name = CommonHeaders.AllowOverwrite)] bool allowOverwrite = false)` — attrs: `[HttpPut("{ns}/{bucket}/{key}.{format?}", Order = 500)] [DisableRequestSizeLimit]`
- L1004-1074 _public method_ `public async Task<IActionResult> PutPackageAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key)` — attrs: `[HttpPut("{ns}/{bucket}/{key}", Order = 300)] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinaryPackage)]`
- L1077-1113 _public method_ `public async Task<IActionResult> FinalizeObjectAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [FromRoute][Required] BlobId hash)` — attrs: `[HttpPost("{ns}/{bucket}/{key}/finalize/{hash}.{format?}")]`
- L1120-1175 _public method_ `public async Task<IActionResult> GetBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [Required] ContentId id, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpGet("{ns}/{bucket}/{key}/blobs/{id}")] [ProducesResponseType(type: typeof(byte[]), 200)] [ProducesResponseType(type: typeof(ValidationProblemDetails), 400)] [Produces(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Applicat`
- L1181-1246 _public method_ `public async Task<IActionResult> PutBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key, [Required] BlobId id)` — attrs: `[HttpPut("{ns}/{bucket}/{key}/blobs/{id}")] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Application.Octet)]`
- L1252-1456 _public method_ `public async Task<IActionResult> BatchAsync( [FromRoute][Required] NamespaceId ns, [FromBody][Required] BatchOps ops)` — attrs: `[HttpPost("{ns}")] [Consumes(CustomMediaTypeNames.UnrealCompactBinary)] [Produces(CustomMediaTypeNames.UnrealCompactBinary)] [ApiExplorerSettings(IgnoreApi = true)]`
- L1458-1471 _private method_ `private static (CbObject, HttpStatusCode) ToErrorResult(Exception exception, HttpStatusCode statusCode = HttpStatusCode.InternalServerError, bool includeStacktrace = true)`
- L1473-1481 _private method_ `private static (CbObject, HttpStatusCode) ToErrorResult(string message, HttpStatusCode statusCode = HttpStatusCode.InternalServerError)`
- L1489-1513 _public method_ `public async Task<IActionResult> DeleteNamespaceAsync( [FromRoute][Required] NamespaceId ns )` — attrs: `[HttpDelete("{ns}", Order = 500)] [ProducesResponseType(204)]` — Drop all refs records in the namespace
- L1522-1547 _public method_ `public async Task<IActionResult> DeleteBucketAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket)` — attrs: `[HttpDelete("{ns}/{bucket}", Order = 500)] [ProducesResponseType(200)]` — Drop all refs records in the bucket
- L1558-1586 _public method_ `public async Task<IActionResult> DeleteAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] BucketId bucket, [FromRoute][Required] RefId key)` — attrs: `[HttpDelete("{ns}/{bucket}/{key}", Order = 500)] [ProducesResponseType(200)] [ProducesResponseType(404)]` — Delete a individual refs key

#### class `Jupiter.Controllers.RefReplicationStateResponse`  
`public class RefReplicationStateResponse`  
_public; L1589-1603_
- L1591-1597 _public ctor_ `public RefReplicationStateResponse(NamespaceId ns, BucketId bucket, RefId key, Dictionary<string, Dictionary<string, bool>> blobsPerRegion)`
- L1599 _public property_ `public NamespaceId Ns { get; set; }`
- L1600 _public property_ `public BucketId Bucket { get; set; }`
- L1601 _public property_ `public RefId Key { get; set; }`
- L1602 _public property_ `public Dictionary<string, Dictionary<string, bool>> BlobsPerRegion { get; init; }`

#### class `Jupiter.Controllers.RefDeletedResponse`  
`public class RefDeletedResponse`  
_public; L1605-1619_
- L1607-1610 _public ctor_ `public RefDeletedResponse()`
- L1612-1615 _public ctor_ `public RefDeletedResponse(int deletedCount)`
- L1618 _public property_ `public int DeletedCount { get; set; }` — attrs: `[CbField("deletedCount")]`

#### class `Jupiter.Controllers.BucketDeletedResponse`  
`public class BucketDeletedResponse`  
_public; L1621-1635_
- L1623-1626 _public ctor_ `public BucketDeletedResponse()`
- L1628-1631 _public ctor_ `public BucketDeletedResponse(long countOfDeletedRecords)`
- L1634 _public property_ `public long CountOfDeletedRecords { get; set; }` — attrs: `[CbField("countOfDeletedRecords")]`

#### class `Jupiter.Controllers.BatchOps`  
`public class BatchOps`  
_public; L1637-1697_
- L1639-1642 _public ctor_ `public BatchOps()`
- L1696 _public property_ `public BatchOp[] Ops { get; set; }` — attrs: `[CbField("ops")]`

#### class `Jupiter.Controllers.BatchOps.BatchOp`  
`public class BatchOp`  
_public; L1645-1693_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "For serialization only")]`
- L1647-1651 _public ctor_ `public BatchOp()`
- L1663 _public property_ `public uint OpId { get; set; }` — attrs: `[Required] [CbField("opId")]`
- L1668-1672 _public property_ `public string OpString { get; set; }` — attrs: `[CbField("op")] [JsonIgnore] [UsedImplicitly]`
- L1675 _public property_ `public Operation Op { get; set; }` — attrs: `[Required]`
- L1679 _public property_ `public BucketId Bucket { get; set; }` — attrs: `[Required] [CbField("bucket")]`
- L1683 _public property_ `public RefId Key { get; set; }` — attrs: `[Required] [CbField("key")]`
- L1686 _public property_ `public bool? ResolveAttachments { get; set; }` — attrs: `[CbField("resolveAttachments")]`
- L1689 _public property_ `public CbObject? Payload { get; set; }` — attrs: `[CbField("payload")]`
- L1692 _public property_ `public ContentHash? PayloadHash { get; set; }` — attrs: `[CbField("payloadHash")]`

#### enum `Jupiter.Controllers.BatchOps.BatchOp.Operation`  
`public enum Operation`  
_public; L1653-1659_
- L1655 _public* enumerator_ `INVALID`
- L1656 _public* enumerator_ `GET`
- L1657 _public* enumerator_ `PUT`
- L1658 _public* enumerator_ `HEAD`

#### class `Jupiter.Controllers.BatchOpsResponse`  
`public class BatchOpsResponse`  
_public; L1699-1726_
- L1701-1704 _public ctor_ `public BatchOpsResponse()`
- L1725 _public property_ `public List<OpResponses> Results { get; set; }` — attrs: `[CbField("results")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.BatchOpsResponse.OpResponses`  
`public class OpResponses`  
_public; L1707-1721_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "For serialization only")]`
- L1709-1712 _public ctor_ `public OpResponses()`
- L1714 _public property_ `public uint OpId { get; set; }` — attrs: `[CbField("opId")]`
- L1717 _public property_ `public CbObject Response { get; set; }` — attrs: `[CbField("response")]`
- L1720 _public property_ `public int StatusCode { get; set; }` — attrs: `[CbField("statusCode")]`

#### class `Jupiter.Controllers.RefMetadataResponse`  
`public class RefMetadataResponse`  
_public; L1728-1779_
- L1730-1734 _public ctor_ `public RefMetadataResponse()`
- L1737-1746 _public ctor_ `public RefMetadataResponse(NamespaceId ns, BucketId bucket, RefId name, BlobId payloadIdentifier, DateTime lastAccess, bool isFinalized, byte[]? inlinePayload)` — attrs: `[JsonConstructor]`
- L1748-1757 _public ctor_ `public RefMetadataResponse(RefRecord objectRecord)`
- L1760 _public property_ `public NamespaceId Ns { get; set; }` — attrs: `[CbField("ns")]`
- L1763 _public property_ `public BucketId Bucket { get; set; }` — attrs: `[CbField("bucket")]`
- L1766 _public property_ `public RefId Name { get; set; }` — attrs: `[CbField("name")]`
- L1769 _public property_ `public BlobId PayloadIdentifier { get; set; }` — attrs: `[CbField("payloadIdentifier")]`
- L1772 _public property_ `public DateTime LastAccess { get; set; }` — attrs: `[CbField("lastAccess")]`
- L1775 _public property_ `public bool IsFinalized { get; set; }` — attrs: `[CbField("isFinalized")]`
- L1778 _public property_ `public byte[]? InlinePayload { get; set; }` — attrs: `[CbField("inlinePayload")]`

#### class `Jupiter.Controllers.EnumerateBucketResponse`  
`public class EnumerateBucketResponse`  
_public; L1781-1796_
- L1783-1786 _public ctor_ `public EnumerateBucketResponse()`
- L1789-1792 _public ctor_ `public EnumerateBucketResponse(RefId[] refIds)` — attrs: `[JsonConstructor]`
- L1795 _public property_ `public RefId[] RefIds { get; set; }` — attrs: `[CbField("refs")]`

#### class `Jupiter.Controllers.PutObjectResponse`  
`public class PutObjectResponse`  
_public; L1798-1812_
- L1800-1803 _public ctor_ `public PutObjectResponse()`
- L1805-1808 _public ctor_ `public PutObjectResponse(ContentHash[] missingReferences)`
- L1811 _public property_ `public ContentHash[] Needs { get; set; }` — attrs: `[CbField("needs")]`

#### class `Jupiter.Controllers.ExistCheckMultipleRefsResponse`  
`public class ExistCheckMultipleRefsResponse`  
_public; L1814-1848_
- L1816-1827 _public ctor_ `public ExistCheckMultipleRefsResponse(List<(BucketId, RefId)> missing)`
- L1830-1833 _public ctor_ `public ExistCheckMultipleRefsResponse(List<MissingReference> missing)` — attrs: `[JsonConstructor]`
- L1837 _public property_ `public List<MissingReference> Missing { get; set; }` — attrs: `[CbField("missing")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.ExistCheckMultipleRefsResponse.MissingReference`  
`public class MissingReference`  
_public; L1840-1847_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1034:Nested types should not be visible", Justification = "For serialization only")]`
- L1843 _public property_ `public BucketId Bucket { get; set; }` — attrs: `[CbField("bucket")]`
- L1846 _public property_ `public RefId Key { get; set; }` — attrs: `[CbField("key")]`

#### class `Jupiter.Controllers.GetNamespacesResponse`  
`public class GetNamespacesResponse`  
_public; L1850-1865_
- L1852-1855 _public ctor_ `public GetNamespacesResponse()`
- L1858-1861 _public ctor_ `public GetNamespacesResponse(NamespaceId[] namespaces)` — attrs: `[JsonConstructor]`
- L1864 _public property_ `public NamespaceId[] Namespaces { get; set; }` — attrs: `[CbField("namespaces")]`

#### class `Jupiter.Controllers.GetBucketsResponse`  
`public class GetBucketsResponse`  
_public; L1867-1881_
- L1869-1872 _public ctor_ `public GetBucketsResponse()`
- L1875-1878 _public ctor_ `public GetBucketsResponse(BucketId[] buckets)` — attrs: `[JsonConstructor]`
- L1880 _public property_ `public BucketId[] Buckets { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ReplicationController.cs` (Jupiter)


#### class `Jupiter.Controllers.ReplicationController`  
`public class ReplicationController : ControllerBase`  
_public; L20-185_
- attrs: `[ApiController] [FormatFilter] [Route("api/v1/g")] [Authorize] [InternalApiFilter]`
- inherits: `ControllerBase`
- L22 _private field_ `private readonly ReplicationService _replicationService`
- L23 _private field_ `private readonly IRequestHelper _requestHelper`
- L25-29 _public ctor_ `public ReplicationController(ReplicationService replicationService, IRequestHelper requestHelper)`
- L33-70 _public method_ `public async Task<IActionResult> GetAsync( [Required] NamespaceId ns )` — attrs: `[HttpGet("{ns}")] [ProducesDefaultResponseType]`
- L74-108 _public method_ `public async Task<IActionResult> SetReplicationOffsetAsync( [Required] NamespaceId ns, [Required] string replicatorName, [Required] long offset )` — attrs: `[HttpPost("{ns}/{replicatorName}/{offset}")] [ProducesDefaultResponseType]`
- L112-153 _public method_ `public async Task<IActionResult> SetReplicationStateAsync( [Required] NamespaceId ns, [Required] string replicatorName, [Required][FromBody] NewReplicationState replicationState )` — attrs: `[HttpPost("refs/{ns}/{replicatorName}")] [ProducesDefaultResponseType]`
- L157-184 _public method_ `public async Task<IActionResult> DeleteAsync( [Required] NamespaceId ns )` — attrs: `[HttpDelete("{ns}")] [ProducesDefaultResponseType]`

#### class `Jupiter.Controllers.NewReplicationState`  
`public class NewReplicationState`  
_public; L187-191_
- L189 _public property_ `public string? LastBucket { get; set; }`
- L190 _public property_ `public Guid? LastEvent { get; set; }`

#### class `Jupiter.Controllers.ReplicatorStateResponse`  
`public class ReplicatorStateResponse`  
_public; L193-203_
- L195 _public property_ `public string? Name { get; set; }`
- L196 _public property_ `public NamespaceId? Namespace { get; set; }`
- L197 _public property_ `public long? Offset { get; set; }`
- L198 _public property_ `public Guid? Generation { get; set; }`
- L199 _public property_ `public DateTime LastReplicationRun { get; set; }`
- L200 _public property_ `public int CountOfRunningReplications { get; set; }`
- L201 _public property_ `public string? LastBucket { get; set; }`
- L202 _public property_ `public Guid LastEvent { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/ReplicationLogController.cs` (Jupiter)


#### class `Jupiter.Controllers.ReplicationLogController`  
`public class ReplicationLogController : ControllerBase`  
_public; L26-211_
- attrs: `[ApiController] [Route("api/v1/replication-log")] [InternalApiFilter] [Authorize]`
- inherits: `ControllerBase`
- L28 _private field_ `private readonly IServiceProvider _provider`
- L29 _private field_ `private readonly IRequestHelper _requestHelper`
- L30 _private field_ `private readonly IReplicationLog _replicationLog`
- L31 _private field_ `private readonly IOptionsMonitor<SnapshotSettings> _snapshotSettings`
- L33-39 _public ctor_ `public ReplicationLogController(IServiceProvider provider, IRequestHelper requestHelper, IReplicationLog replicationLog, IOptionsMonitor<SnapshotSettings> snapshotSettings)`
- L44-62 _public method_ `public async Task<IActionResult> GetSnapshotsAsync( [Required] NamespaceId ns )` — attrs: `[HttpGet("snapshots/{ns}")] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]`
- L67-87 _public method_ `public async Task<IActionResult> CreateSnapshotAsync( [Required] NamespaceId ns )` — attrs: `[HttpPost("snapshots/{ns}/create")] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]`
- L92-154 _public method_ `public async Task<IActionResult> GetIncrementalEventsAsync( [Required] NamespaceId ns, [FromQuery] string? lastBucket, [FromQuery] Guid? lastEvent, [FromQuery] int count = 1000 )` — attrs: `[HttpGet("incremental/{ns}")] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]`
- L159-210 _public method_ `public async Task<IActionResult> GetBlobLogAsync( [Required] NamespaceId ns, [Required] string replicationBucket )` — attrs: `[HttpGet("blobs/{ns}/{replicationBucket}")] [ProducesDefaultResponseType] [ProducesResponseType(type: typeof(ProblemDetails), 400)]`

#### class `Jupiter.Controllers.SnapshotCreatedResponse`  
`public class SnapshotCreatedResponse`  
_public; L213-227_
- L215-218 _public ctor_ `public SnapshotCreatedResponse()`
- L220-223 _public ctor_ `public SnapshotCreatedResponse(BlobId snapshotBlob)`
- L226 _public property_ `public BlobId SnapshotBlobId { get; set; }` — attrs: `[CbField("snapshotBlobId")]`

#### class `Jupiter.Controllers.ReplicationLogSnapshots`  
`public class ReplicationLogSnapshots`  
_public; L229-244_
- L231-234 _public ctor_ `public ReplicationLogSnapshots()`
- L237-240 _public ctor_ `public ReplicationLogSnapshots(List<SnapshotInfo> snapshots)` — attrs: `[JsonConstructor]`
- L243 _public property_ `public List<SnapshotInfo> Snapshots { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.ReplicationLogEvents`  
`public class ReplicationLogEvents`  
_public; L246-261_
- L248-251 _public ctor_ `public ReplicationLogEvents()`
- L254-257 _public ctor_ `public ReplicationLogEvents(List<ReplicationLogEvent> events)` — attrs: `[JsonConstructor]`
- L260 _public property_ `public List<ReplicationLogEvent> Events { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.BlobReplicationLogEvents`  
`public class BlobReplicationLogEvents`  
_public; L263-278_
- L265-268 _public ctor_ `public BlobReplicationLogEvents()`
- L271-274 _public ctor_ `public BlobReplicationLogEvents(List<BlobReplicationLogEvent> events)` — attrs: `[JsonConstructor]`
- L277 _public property_ `public List<BlobReplicationLogEvent> Events { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/RequestHelper.cs` (Jupiter)


#### class `Jupiter.Controllers.RequestHelper`  
`public class RequestHelper : IRequestHelper`  
_public; L18-204_
- inherits: `IRequestHelper`
- L20 _private field_ `private readonly IAuthorizationService _authorizationService`
- L21 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L22 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _settings`
- L23 _private field_ `private readonly IOptionsMonitor<AuthSettings> _authSettings`
- L24 _private field_ `private readonly Tracer _tracer`
- L26-33 _public ctor_ `public RequestHelper(IAuthorizationService authorizationService, INamespacePolicyResolver namespacePolicyResolver, IOptionsMonitor<JupiterSettings> settings, IOptionsMonitor<AuthSettings> authSettings, Tracer tracer)`
- L35-91 _public method_ `public async Task<ActionResult?> HasAccessToScopeAsync(ClaimsPrincipal user, HttpRequest request, AccessScope scope, JupiterAclAction[] aclActions)`
- L93-142 _public method_ `public async Task<ActionResult?> HasAccessToNamespaceAsync(ClaimsPrincipal user, HttpRequest request, NamespaceId ns, JupiterAclAction[] aclActions)`
- L144-158 _public method_ `public async Task<ActionResult?> HasAccessForGlobalOperationsAsync(ClaimsPrincipal user, JupiterAclAction[] aclActions)`
- L160-192 _public method_ `public bool IsPublicPort(HttpContext context)`
- L194-203 _public method_ `public IActionResult? EnsureSingleRangeRequest(HttpContext context)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/StatusController.cs` (Jupiter)


#### class `Jupiter.Controllers.StatusController`  
`public class StatusController : Controller`  
_public; L22-177_
- attrs: `[ApiController] [Route("api/v1/status")] [Authorize]`
- inherits: `Controller`
- L24 _private field_ `private readonly VersionFile _versionFile`
- L25 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L26 _private field_ `private readonly IOptionsMonitor<ClusterSettings> _clusterSettings`
- L27 _private field_ `private readonly IPeerStatusService _statusService`
- L28 _private field_ `private readonly ILogger<StatusController> _logger`
- L30-37 _public ctor_ `public StatusController(VersionFile versionFile, IOptionsMonitor<JupiterSettings> jupiterSettings, IOptionsMonitor<ClusterSettings> clusterSettings, IPeerStatusService statusService, ILogger<StatusController> logger)`
- L48-66 _public method_ `public IActionResult Status()` — attrs: `[HttpGet("")] [ProducesResponseType(type: typeof(StatusResponse), 200)]` — Fetch information about Jupiter
- L68-75 _private method_ `private static string[] GetCapabilities()`
- L86-89 _public method_ `public IActionResult Peers([FromQuery] bool includeInternalEndpoints = false)` — attrs: `[HttpGet("peers")] [ProducesResponseType(type: typeof(PeersResponse), 200)]` — Fetch information about other deployments
- L99-111 _public method_ `public IActionResult Servers([FromQuery] IPAddress? asIp = null)` — attrs: `[HttpGet("servers")] [ProducesResponseType(type: typeof(PeersResponse), 200)]` — Get a list of which servers you can talk to based on the ip used to call the endpoint
- L113-158 _private method_ `private (List<EndpointDefinition>, List<EndpointDefinition>) DetermineBestEndpoints(IPAddress? ip, DiscoverySettings discoverySettings)`
- L160-176 _private method_ `private List<EndpointDefinition> ResolveEndpoints(DiscoverySettings discoverySettings, IEnumerable<string> endpoints)`

#### class `Jupiter.Controllers.PeersResponse`  
`public class PeersResponse`  
_public; L179-205_
- L181-184 _public ctor_ `public PeersResponse()`
- L187-191 _public ctor_ `public PeersResponse(string currentSite, List<KnownPeer> peers)` — attrs: `[JsonConstructor]`
- L193-197 _public ctor_ `public PeersResponse(IOptionsMonitor<JupiterSettings> jupiterSettings, IOptionsMonitor<ClusterSettings> clusterSettings, bool includeInternalEndpoints, IPeerStatusService peerStatusService)`
- L200 _public property_ `public string CurrentSite { get; set; }` — attrs: `[CbField("currentSite")]`
- L204 _public property_ `public List<KnownPeer> Peers { get; set; }` — attrs: `[CbField("peers")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.ServersResponse`  
`public class ServersResponse`  
_public; L207-227_
- L209-212 _public ctor_ `public ServersResponse()`
- L216 _public property_ `public List<EndpointDefinition> CacheEndpoints { get; set; }` — attrs: `[CbField("cacheEndpoints")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L220 _public property_ `public List<EndpointDefinition> ServerEndpoints { get; set; }` — attrs: `[CbField("serverEndpoints")] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L222-226 _public ctor_ `public ServersResponse(List<EndpointDefinition> cacheEndpoints, List<EndpointDefinition> serverEndpoints)`

#### class `Jupiter.Controllers.EndpointDefinition`  
`public class EndpointDefinition`  
_public; L229-241_
- L233 _public property_ `public string Name { get; set; }` — attrs: `[Required] [CbField("name")]`
- L237 _public property_ `public Uri BaseUrl { get; set; }` — attrs: `[Required] [CbField("baseUrl")]`
- L240 _public property_ `public bool AssumeHttp2 { get; set; }` — attrs: `[CbField("assumeHttp2")]`

#### class `Jupiter.Controllers.RoutingRule`  
`public class RoutingRule`  
_public; L243-260_
- L246 _public property_ `public string Name { get; set; }` — attrs: `[Required]`
- L249 _public property_ `public string Description { get; set; }` — attrs: `[Required]`
- L253 _public property_ `public List<string> Subnets { get; set; }` — attrs: `[Required] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L256 _public property_ `public List<string> CacheIds { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L259 _public property_ `public List<string> ServerIds { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.DiscoverySettings`  
`public class DiscoverySettings`  
_public; L262-274_
- L266 _public property_ `public Dictionary<string , EndpointDefinition> EndpointDefinitions { get; set; }` — attrs: `[Required] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L269 _public property_ `public RoutingRule DefaultRule { get; set; }` — attrs: `[Required]`
- L273 _public property_ `public List<RoutingRule> Rules { get; set; }` — attrs: `[Required] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Controllers.KnownPeer`  
`public class KnownPeer`  
_public; L276-325_
- L278-283 _public ctor_ `public KnownPeer()`
- L286-292 _public ctor_ `public KnownPeer(string site, string fullName, List<Uri> endpoints, int latency)` — attrs: `[JsonConstructor]`
- L294-311 _public ctor_ `public KnownPeer(PeerSettings peerSettings, bool includeInternalEndpoints, IPeerStatusService statusService)`
- L314 _public property_ `public string Site { get; set; }` — attrs: `[CbField("site")]`
- L317 _public property_ `public string FullName { get; set; }` — attrs: `[CbField("fullName")]`
- L320 _public property_ `public int Latency { get; set; }` — attrs: `[CbField("latency")]`
- L324 _public property_ `public List<Uri> Endpoints { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")] [CbField("endpoints")]`

#### class `Jupiter.Controllers.StatusResponse`  
`public class StatusResponse`  
_public; L327-349_
- L329-335 _public ctor_ `public StatusResponse()`
- L337-343 _public ctor_ `public StatusResponse(string version, string gitHash, string[] capabilities, string siteIdentifier)`
- L345 _public property_ `public string Version { get; set; }`
- L346 _public property_ `public string GitHash { get; set; }`
- L347 _public property_ `public string[] Capabilities { get; set; }`
- L348 _public property_ `public string SiteIdentifier { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Controllers/SymbolsController.cs` (Jupiter)


#### class `Jupiter.Controllers.SymbolsController`  
`public class SymbolsController : ControllerBase`  
_public; L40-619_
- attrs: `[ApiController] [Produces(MediaTypeNames.Application.Json, MediaTypeNames.Application.Octet, CustomMediaTypeNames.UnrealCompactBinary)] [Route("api/v1/symbols")] [Authorize]`
- inherits: `ControllerBase`
- L42 _private field_ `private readonly IRefService _refService`
- L43 _private field_ `private readonly IBlobService _blobStore`
- L44 _private field_ `private readonly IDiagnosticContext _diagnosticContext`
- L45 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L46 _private field_ `private readonly FormatResolver _formatResolver`
- L47 _private field_ `private readonly NginxRedirectHelper _nginxRedirectHelper`
- L48 _private field_ `private readonly IRequestHelper _requestHelper`
- L49 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L50 _private field_ `private readonly Tracer _tracer`
- L51 _private field_ `private readonly ILogger<SymbolsController> _logger`
- L52 _private field_ `private readonly ILogger? _auditLogger`
- L54-67 _public ctor_ `public SymbolsController(IRefService refService, IBlobService blobStore, IDiagnosticContext diagnosticContext, BufferedPayloadFactory bufferedPayloadFactory, FormatResolver formatResolver, NginxRedirectHelper nginxRedirectHelper, IRequestHelper requestHelper, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer, ILogger<SymbolsController> logger, IOptionsMonitor<SymbolsSettings> symbolSettings)`
- L79-202 _public method_ `public async Task<IActionResult> GetAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] string moduleName, [FromRoute][Required] string identifier, [FromRoute][Required] string fileName)` — attrs: `[HttpGet("{ns}/{moduleName}/{identifier}/{fileName}", Order = 500)] [Produces(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Octet)] [ProducesDefaultResponseType]` — Fetch a symbol file
- L207-283 _public method_ `public async Task<IActionResult> PutSymbolsAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] string moduleName)` — attrs: `[HttpPut("{ns}/{moduleName}", Order = 500)] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompactBinary, MediaTypeNames.Application.Octet)]`
- L285-300 _private method_ `private async Task<List<ContentHash>> PutSymbolsRefAsync(NamespaceId ns, BucketId bucket, string moduleName, string identifier, int age, string fileName, CbObject payloadObject, BlobId payloadHash)`
- L302-319 _private method_ `private static byte[] CreateCompactBinaryForSymbol(IoHash attachmentIoHash, string moduleName, string pdbIdentifier, int pdbAge, long pdbSize)`
- L327-380 _public method_ `public async Task<IActionResult> GetBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] string moduleName, [Required] ContentId id, [FromQuery] bool supportsRedirect = false)` — attrs: `[HttpGet("{ns}/{moduleName}/blobs/{id}")] [ProducesResponseType(type: typeof(byte[]), 200)] [ProducesResponseType(type: typeof(ValidationProblemDetails), 400)] [Produces(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Applicatio`
- L385-452 _public method_ `public async Task<IActionResult> PutBlobAsync( [FromRoute][Required] NamespaceId ns, [FromRoute][Required] string moduleName, [Required] BlobId id)` — attrs: `[HttpPut("{ns}/{moduleName}/blobs/{id}", Order = 500)] [DisableRequestSizeLimit] [RequiredContentType(CustomMediaTypeNames.UnrealCompressedBuffer, MediaTypeNames.Application.Octet)]`
- L455-458 _private method_ `private void LogAuditEntry(HttpMethod method, NamespaceId ns, string moduleName, string identifier, string fileName)`
- L460-471 _private method_ `private static (string, int) ExtractModuleInformation(string moduleName, IBufferedPayload decompressedContent)`
- L473-618 _private method_ `private static (string, int) ExtractModuleInformationPdb(Stream s)`

#### class `Jupiter.Controllers.SymbolsSettings`  
`public class SymbolsSettings`  
_public; L621-624_
- L623 _public property_ `public bool EnableAuditLog { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/HealthChecks.cs` (Jupiter)


#### class `Jupiter.RefCleanupServiceCheck`  
`public class RefCleanupServiceCheck : IHealthCheck`  
_public; L12-30_
- inherits: `IHealthCheck`
- L14 _private field_ `private readonly RefCleanupService _refCleanupService`
- L16-19 _public ctor_ `public RefCleanupServiceCheck(RefCleanupService refCleanupService)`
- L21-29 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

#### class `Jupiter.BlobCleanupServiceCheck`  
`public class BlobCleanupServiceCheck : IHealthCheck`  
_public; L32-50_
- inherits: `IHealthCheck`
- L34 _private field_ `private readonly BlobCleanupService _blobCleanupService`
- L36-39 _public ctor_ `public BlobCleanupServiceCheck(BlobCleanupService blobCleanupService)`
- L41-49 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

#### class `Jupiter.KubernetesLeaderServiceCheck`  
`public class KubernetesLeaderServiceCheck : IHealthCheck`  
_public; L52-70_
- inherits: `IHealthCheck`
- L54 _private field_ `private readonly KubernetesLeaderElection _leaderElectionService`
- L56-59 _public ctor_ `public KubernetesLeaderServiceCheck(KubernetesLeaderElection leaderElectionService)`
- L61-69 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

#### class `Jupiter.LastAccessServiceCheck`  
`public class LastAccessServiceCheck : IHealthCheck`  
_public; L72-90_
- inherits: `IHealthCheck`
- L74 _private field_ `private readonly LastAccessServiceReferences _lastAccessService`
- L76-79 _public ctor_ `public LastAccessServiceCheck(LastAccessServiceReferences lastAccessService)`
- L81-89 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

#### class `Jupiter.ReplicationSnapshotServiceCheck`  
`public class ReplicationSnapshotServiceCheck : IHealthCheck`  
_public; L92-117_
- inherits: `IHealthCheck`
- L94 _private field_ `private readonly ReplicationSnapshotService _replicationSnapshotService`
- L95 _private field_ `private readonly IOptionsMonitor<SnapshotSettings> _snapshotSettings`
- L97-101 _public ctor_ `public ReplicationSnapshotServiceCheck(ReplicationSnapshotService replicationSnapshotService, IOptionsMonitor<SnapshotSettings> snapshotSettings)`
- L103-116 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

#### class `Jupiter.ReplicatorServiceCheck`  
`public class ReplicatorServiceCheck : IHealthCheck`  
_public; L119-145_
- inherits: `IHealthCheck`
- L121 _private field_ `private readonly ReplicationService _replicationService`
- L122 _private field_ `private readonly IOptionsMonitor<ReplicationSettings> _replicationSetting`
- L124-128 _public ctor_ `public ReplicatorServiceCheck(ReplicationService replicationService, IOptionsMonitor<ReplicationSettings> replicationSetting)`
- L130-144 _public method_ `public Task<HealthCheckResult> CheckHealthAsync(HealthCheckContext context, CancellationToken cancellationToken = new CancellationToken())`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/AnyRequirement.cs` (Jupiter)


#### class `Jupiter.AnyRequirement`  
`public class AnyRequirement : AuthorizationHandler<AnyRequirement>, IAuthorizationRequirement`  
_public; L18-51_
- inherits: `AuthorizationHandler<AnyRequirement>, IAuthorizationRequirement`
- desc: An implementation of IAuthorizationRequirement that combines multiple requirements such that if any of those inner requirements are met, this requirement is met. This only supports requirements that handle themselves, i.e. implement both IAuthorizationRequirement and the corresponding AuthorizationHandler{TRequirement}.
- L20-23 _public ctor_ `public AnyRequirement(params IAuthorizationRequirement[] innerRequirements)`
- L25 _public property_ `public IEnumerable<IAuthorizationRequirement> InnerRequirements { get; }`
- L27-44 _protected method_ `protected override async Task HandleRequirementAsync(AuthorizationHandlerContext context, AnyRequirement requirement)`
- L46-50 _public method_ `public override string ToString()`

#### class `Jupiter.AnyRequirementBuilder`  
`public class AnyRequirementBuilder`  
_public; L56-77_
- desc: A helper class to build an instance of AnyRequirement.
- L58 _private field_ `private readonly List<IAuthorizationRequirement> _innerRequirements = new List<IAuthorizationRequirement>()`
- L59 _private field_ `private readonly AuthorizationPolicyBuilder _policyBuilder`
- L61-64 _public ctor_ `public AnyRequirementBuilder(AuthorizationPolicyBuilder policyBuilder)`
- L66-70 _public method_ `public AnyRequirementBuilder AddRequirement(IAuthorizationRequirement requirement)`
- L72-76 _public method_ `public AuthorizationPolicyBuilder AddAny()`

#### class `Jupiter.AnyRequirementExtensions`  
`public static class AnyRequirementExtensions`  
_public; L82-109_
- desc: Helpful extensions related to AnyRequirement
- L90-93 _public method_ `public static AnyRequirementBuilder BeginAnyContext(this AuthorizationPolicyBuilder policyBuilder)` — Starts a building context to add requirements that will be combined as an AnyRequirement and added to the policy builder when AnyRequirementBuilder.AddAny is called later.
- L95-98 _public method_ `public static AnyRequirementBuilder IncludeClaim(this AnyRequirementBuilder builder, string claimType, params string[] allowedValues)`
- L100-103 _public method_ `public static AnyRequirementBuilder IncludeClaim(this AnyRequirementBuilder builder, string claimType)`
- L105-108 _public method_ `public static AnyRequirementBuilder IncludeRole(this AnyRequirementBuilder builder, params string[] roles)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/AmazonS3Store.cs` (Jupiter)


#### class `Jupiter.Implementation.AmazonS3Store`  
`public class AmazonS3Store : IBlobStore, IMultipartBlobStore, IDataStoreObjectStore`  
_public; L34-538_
- inherits: `IBlobStore, IMultipartBlobStore, IDataStoreObjectStore`
- L36 _private field_ `private readonly IAmazonS3 _amazonS3`
- L37 _private field_ `private IBlobIndex? _blobIndex = null`
- L38 _private field_ `private readonly Lock _blobIndexLock = new Lock()`
- L39 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L40 _private field_ `private readonly ILogger<AmazonS3Store> _logger`
- L41 _private field_ `private readonly IServiceProvider _provider`
- L42 _private field_ `private readonly S3Settings _settings`
- L43 _private field_ `private readonly JupiterSettings _jupiterSettings`
- L44 _private field_ `private readonly ConcurrentDictionary<string, AmazonStorageBackend> _backends = ...`
- L44 _private field_ `private readonly ConcurrentDictionary< _backends = new ConcurrentDictionary<string, AmazonStorageBackend>()`
- L46-54 _public ctor_ `public AmazonS3Store(IAmazonS3 amazonS3, IOptionsMonitor<S3Settings> settings, IOptionsMonitor<JupiterSettings> jupiterSettings, INamespacePolicyResolver namespacePolicyResolver, ILogger<AmazonS3Store> logger, IServiceProvider provider)`
- L56-60 _private method_ `private AmazonStorageBackend GetBackend(NamespaceId ns, string? region = null)`
- L62-88 _private method_ `private AmazonStorageBackend GetBackend(KeyspaceId keyspace, string? region = null)`
- L90-95 _public method_ `public async Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L97-106 _public method_ `public async Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L108-111 _public method_ `public async Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L113-118 _public method_ `public async Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L120-124 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> content, BlobId objectName, CancellationToken cancellationToken = default)`
- L126-130 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, Stream stream, BlobId objectName, CancellationToken cancellationToken = default)`
- L132-136 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] content, BlobId objectName, CancellationToken cancellationToken = default)`
- L138-172 _private method_ `private string GetBucketName(NamespaceId ns, string site)`
- L174-206 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L208-228 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blobIdentifier, bool forceCheck, CancellationToken cancellationToken = default)`
- L230-248 _public method_ `public async Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L250-263 _public method_ `public async IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L265-269 _public method_ `public async Task DeleteObjectAsync(NamespaceId ns, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L271-282 _public method_ `public async Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L287 _private const_ `private const string TempMultipartPrefix = "Temp/Multipart"`
- L288-291 _public method_ `public Task<string> StartMultipartUploadAsync(NamespaceId ns, string blobName, CancellationToken cancellationToken = default)`
- L293-296 _public method_ `public Task CompleteMultipartUploadAsync(NamespaceId ns, string blobName, string uploadId, List<string> partIds, CancellationToken cancellationToken = default)`
- L298-301 _public method_ `public Task<Uri?> GetWriteRedirectForPartAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, CancellationToken cancellationToken = default)`
- L303-306 _public method_ `public async Task<BlobContents?> GetMultipartObjectByNameAsync(NamespaceId ns, string blobName, CancellationToken cancellationToken = default)`
- L308-311 _public method_ `public async Task RenameMultipartBlobAsync(NamespaceId ns, string blobName, BlobId blobId, CancellationToken cancellationToken = default)`
- L312-315 _public method_ `public Task PutMultipartPartAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, byte[] blob, CancellationToken cancellationToken = default)`
- L317-341 _public method_ `public List<MultipartByteRange> GetMultipartRanges(NamespaceId ns, string uploadId, ulong blobLength, CancellationToken cancellationToken = default)`
- L343-346 _public method_ `public MultipartLimits GetMultipartLimits(NamespaceId ns, CancellationToken cancellationToken = default)`
- L348 _private const_ `private const ulong MaxS3Chunks = 10_000`
- L349 _private const_ `private const int IdealS3ChunkSize = 32 * 1024 * 1024`
- L355-359 _public method_ `public async Task PutFileAsync(KeyspaceId keyspaceId, FileInfo localPath, string remotePath, CancellationToken cancellationToken)`
- L361-432 _public method_ `public async IAsyncEnumerable<(KeyspaceId keyspace, string prefix)> EnumeratePrefixesAsync(TableType typeName, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L434-465 _public method_ `public async Task<bool> GetFileAsync(KeyspaceId keyspaceId, string remotePath, FileInfo localFile, CancellationToken cancellationToken)`
- L467-500 _public method_ `public async IAsyncEnumerable<DataStoreFile> EnumerateFilesAsync(KeyspaceId keyspaceId, string remotePath, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L502-535 _public method_ `public async Task DeleteFilesAsync(KeyspaceId keyspaceId, string remotePath, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.AmazonStorageBackend`  
`public class AmazonStorageBackend : IStorageBackend`  
_public; L540-1228_
- inherits: `IStorageBackend`
- L542 _private field_ `private readonly IAmazonS3 _amazonS3`
- L543 _private field_ `private readonly string _bucketName`
- L544 _private field_ `private readonly IOptionsMonitor<S3Settings> _settings`
- L545 _private field_ `private readonly Tracer _tracer`
- L546 _private field_ `private readonly ILogger<AmazonStorageBackend> _logger`
- L547 _private field_ `private readonly BufferedPayloadFactory _payloadFactory`
- L548 _private field_ `private bool _bucketExistenceChecked`
- L549 _private field_ `private bool _bucketAccessPolicyApplied`
- L551-559 _public ctor_ `public AmazonStorageBackend(IAmazonS3 amazonS3, string bucketName, IOptionsMonitor<S3Settings> settings, Tracer tracer, ILogger<AmazonStorageBackend> logger, BufferedPayloadFactory payloadFactory)`
- L561-625 _public method_ `public async Task EnsureBucketExistsAsync(CancellationToken cancellationToken = default)`
- L627-667 _public method_ `public async Task WriteAsync(string path, Stream stream, CancellationToken cancellationToken = default)`
- L669-785 _private method_ `private async Task WriteMultipartAsync(string path, Stream stream, CancellationToken cancellationToken = default)`
- L787-892 _private method_ `private async Task<BlobContents?> GetMultipartAsync(string path, CancellationToken cancellationToken = default)`
- L894-922 _public method_ `public async Task<BlobContents?> TryReadAsync(string path, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, CancellationToken cancellationToken = default)`
- L924-942 _public method_ `public async Task<bool> ExistsAsync(string path, CancellationToken cancellationToken = default)`
- L944-1012 _public method_ `public async IAsyncEnumerable<(string, DateTime)> ListAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L1014-1017 _public method_ `public async Task DeleteAsync(string path, CancellationToken cancellationToken = default)`
- L1019-1022 _public method_ `public ValueTask<Uri?> GetReadRedirectAsync(string path)`
- L1024-1027 _public method_ `public ValueTask<Uri?> GetWriteRedirectAsync(string path)`
- L1032-1064 _private* method_ `Uri? GetPresignedUrl(string path, HttpVerb verb, int? partNumber = null, string? uploadId = null)` — Helper method to generate a presigned URL for a request
- L1066-1096 _public method_ `public async Task<BlobMetadata?> GetMetadataAsync(string path, CancellationToken cancellationToken = default)`
- L1098-1103 _public method_ `public async Task<string> StartMultipartUploadAsync(string path, CancellationToken cancellationToken = default)`
- L1105-1142 _public method_ `public async Task CompleteMultipartUploadAsync(string path, string uploadId, List<string> partIds, CancellationToken cancellationToken = default)`
- L1144-1147 _public method_ `public async Task PutMultipartPartAsync(string path, string uploadId, string partIdentifier, byte[] data, CancellationToken cancellationToken = default)`
- L1149-1159 _public method_ `public Uri? GetWriteRedirectForPart(string path, string uploadId, string partIdentifier)`
- L1161-1166 _public method_ `public async Task RenameMultipartBlobAsync(string blobName, string targetBlobName, CancellationToken cancellationToken = default)`
- L1168-1171 _internal method_ `internal string GetBucketName()`
- L1173-1227 _public method_ `public async Task<ulong> CopyBlobAsync(AmazonStorageBackend source, string sourcePath, string destinationPath, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.BlobIdentifierExtensions`  
`public static class BlobIdentifierExtensions`  
_public; L1230-1238_
- L1232-1237 _public method_ `public static string AsS3Key(this BlobId blobIdentifier)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/AzureBlobStore.cs` (Jupiter)


#### class `Jupiter.Implementation.AzureBlobStore`  
`public class AzureBlobStore : IBlobStore`  
_public; L25-191_
- inherits: `IBlobStore`
- L27 _private field_ `private readonly IOptionsMonitor<AzureSettings> _settings`
- L28 _private field_ `private readonly ISecretResolver _secretResolver`
- L29 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L30 _private field_ `private readonly IServiceProvider _provider`
- L31 _private field_ `private readonly ConcurrentDictionary<NamespaceId, AzureStorageBackend> _backends = ...`
- L31 _private field_ `private readonly ConcurrentDictionary< _backends = new ConcurrentDictionary<NamespaceId, AzureStorageBackend>()`
- L33-39 _public ctor_ `public AzureBlobStore(IOptionsMonitor<AzureSettings> settings, ISecretResolver secretResolver, INamespacePolicyResolver namespacePolicyResolver, IServiceProvider provider)`
- L41-44 _private method_ `private AzureStorageBackend GetBackend(NamespaceId ns)`
- L46-57 _private method_ `private string GetContainerName(NamespaceId ns)`
- L59-70 _private method_ `private string GetConnectionString(NamespaceId ns)`
- L72 _private method_ `private static string GetPath(BlobId blobIdentifier)`
- L74-79 _public method_ `public async Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L81-91 _public method_ `public async Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L93-97 _public method_ `public Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L99-104 _public method_ `public async Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L106-111 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L113-117 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, Stream content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L119-123 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L125-143 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blobIdentifier, LastAccessTrackingFlags flags, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L145-148 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blobIdentifier, bool forceCheck, CancellationToken cancellationToken = default)`
- L150-153 _public method_ `public async Task DeleteObjectAsync(NamespaceId ns, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L155-166 _public method_ `public async Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L168-177 _public method_ `public async Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L179-185 _public method_ `public async IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L187-190 _private method_ `private static string SanitizeContainerName(string containerName)`

#### class `Jupiter.Implementation.AzureStorageBackend`  
`public class AzureStorageBackend : IStorageBackend`  
_public; L193-374_
- inherits: `IStorageBackend`
- L195 _private field_ `private readonly NamespaceId _namespaceId`
- L196 _private field_ `private readonly ILogger<AzureStorageBackend> _logger`
- L197 _private field_ `private readonly Tracer _tracer`
- L198 _private field_ `private readonly BlobContainerClient _blobContainer`
- L200 _private const_ `private const string LastTouchedKey = "Io_LastTouched"`
- L201 _private const_ `private const string NamespaceKey = "Io_Namespace"`
- L203-209 _public ctor_ `public AzureStorageBackend(string connectionString, NamespaceId namespaceId, string containerName, ILogger<AzureStorageBackend> logger, Tracer tracer)`
- L211-239 _public method_ `public async Task WriteAsync(string path, Stream content, CancellationToken cancellationToken = default)`
- L241-251 _private method_ `private static async Task TouchBlobAsync(BlobClient blob, CancellationToken cancellationToken = default)`
- L253-276 _public method_ `public async Task<BlobContents?> TryReadAsync(string path, LastAccessTrackingFlags flags, CancellationToken cancellationToken = default)`
- L278-287 _public method_ `public async Task<bool> ExistsAsync(string path, CancellationToken cancellationToken = default)`
- L289-297 _public method_ `public async Task DeleteAsync(string path, CancellationToken cancellationToken = default)`
- L299-311 _public method_ `public async IAsyncEnumerable<(string, DateTime)> ListAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L313-321 _public method_ `public async ValueTask<Uri?> GetReadRedirectAsync(string path, CancellationToken cancellationToken = default)`
- L323-331 _public method_ `public async ValueTask<Uri?> GetWriteRedirectAsync(string path, CancellationToken cancellationToken = default)`
- L336-356 _private* method_ `Uri? GetPresignedUrl(string path, BlobSasPermissions permissions)` — Helper method to generate a presigned URL for a request
- L358-373 _public method_ `public async Task<BlobMetadata?> GetMetadataAsync(string path, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/BlobIndexConsistencyCheckService.cs` (Jupiter)


#### class `Jupiter.Implementation.BlobIndexConsistencyState`  
`public class BlobIndexConsistencyState`  
_public; L15-17_

#### class `Jupiter.Implementation.BlobIndexConsistencyCheckService`  
`public class BlobIndexConsistencyCheckService : PollingService<BlobIndexConsistencyState>`  
_public; L20-243_
- inherits: `PollingService<BlobIndexConsistencyState>`
- L22 _private field_ `private readonly IOptionsMonitor<ConsistencyCheckSettings> _settings`
- L23 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L24 _private field_ `private readonly ILeaderElection _leaderElection`
- L25 _private field_ `private readonly IBlobIndex _blobIndex`
- L26 _private field_ `private readonly IBlobService _blobService`
- L27 _private field_ `private readonly Tracer _tracer`
- L28 _private field_ `private readonly ILogger _logger`
- L30-33 _protected method_ `protected override bool ShouldStartPolling()`
- L35-44 _public ctor_ `public BlobIndexConsistencyCheckService(IOptionsMonitor<ConsistencyCheckSettings> settings, IOptionsMonitor<JupiterSettings> jupiterSettings, ILeaderElection leaderElection, IBlobIndex blobIndex, IBlobService blobService, Tracer tracer, ILogger<BlobIndexConsistencyCheckService> logger) : base(serviceName: nameof(BlobIndexConsistencyCheckService), TimeSpan.FromSeconds(settings.CurrentValue.ConsistencyCheckPollFrequencySeconds), new BlobIndexConsistencyState(), logger)`
- L46-71 _public method_ `public override async Task<bool> OnPollAsync(BlobIndexConsistencyState state, CancellationToken cancellationToken)`
- L73-125 _public method_ `public async Task RunConsistencyCheckBlobReferencesAsync(CancellationToken cancellationToken)`
- L127-237 _private method_ `private async Task RunConsistencyCheckAsync(CancellationToken cancellationToken)`
- L239-242 _protected method_ `protected override Task OnStopping(BlobIndexConsistencyState state)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/BlobService.cs` (Jupiter)


#### class `Jupiter.Implementation.BlobService`  
`public class BlobService : IBlobService`  
_public; L29-1287_
- inherits: `IBlobService`
- L31 _private field_ `private List<IBlobStore> _blobStores`
- L32 _private field_ `private readonly IServiceProvider _provider`
- L33 _private field_ `private readonly IOptionsMonitor<UnrealCloudDDCSettings> _settings`
- L34 _private field_ `private readonly IBlobIndex _blobIndex`
- L35 _private field_ `private readonly IReplicationLog _replicationLog`
- L36 _private field_ `private readonly IPeerStatusService _peerStatusService`
- L37 _private field_ `private readonly IHttpClientFactory _httpClientFactory`
- L38 _private field_ `private readonly IServiceCredentials _serviceCredentials`
- L39 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L40 _private field_ `private readonly IHttpContextAccessor _httpContextAccessor`
- L41 _private field_ `private readonly IRequestHelper? _requestHelper`
- L42 _private field_ `private readonly Tracer _tracer`
- L43 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L44 _private field_ `private readonly ILogger _logger`
- L45 _private field_ `private readonly Counter<long>? _storeGetHitsCounter`
- L46 _private field_ `private readonly Counter<long>? _storeGetAttemptsCounter`
- L47 _private field_ `private readonly string _currentSite`
- L49-53 _internal property_ `internal IEnumerable<IBlobStore> BlobStore { get; set; }`
- L55-76 _public ctor_ `public BlobService(IServiceProvider provider, IOptionsMonitor<UnrealCloudDDCSettings> settings, IOptionsMonitor<JupiterSettings> jupiterSettings, IBlobIndex blobIndex, IReplicationLog replicationLog, IPeerStatusService peerStatusService, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials, INamespacePolicyResolver namespacePolicyResolver, IHttpContextAccessor httpContextAccessor, IRequestHelper? requestHelper, Tracer tracer, BufferedPayloadFactory bufferedPayloadFactory, ILogger<BlobService> logger, Meter? meter)`
- L78-81 _public method_ `public static IEnumerable<IBlobStore> GetBlobStores(IServiceProvider provider, IOptionsMonitor<UnrealCloudDDCSettings> settings)`
- L83-101 _private method_ `private static IBlobStore ToStorageImplementation(IServiceProvider provider, UnrealCloudDDCSettings.StorageBackendImplementations impl)`
- L103-117 _public method_ `public async Task<ContentHash> VerifyContentMatchesHashAsync(Stream content, ContentHash identifier, CancellationToken cancellationToken = default)`
- L119-135 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, IBufferedPayload payload, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L137-153 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] payload, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L155-190 _public method_ `public async Task<Uri?> MaybePutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`
- L192-204 _public method_ `public async Task<BlobId> PutObjectKnownHashAsync(NamespaceId ns, IBufferedPayload content, BlobId identifier, BucketId? bucketHint, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L206-241 _private method_ `private async Task<BlobId> PutObjectToStoresAsync(NamespaceId ns, IBufferedPayload bufferedPayload, BlobId identifier, BucketId? bucketHint, bool? bypassCache, CancellationToken cancellationToken = default)`
- L243-248 _private method_ `private async Task<BlobId> PutObjectToStoresAsync(NamespaceId ns, byte[] payload, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L250-343 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool supportsRedirectUri = false, bool allowOndemandReplication = true, BucketId? bucketHint = null, bool bypassCache = false, CancellationToken cancellationToken = default)`
- L345-519 _private method_ `private async Task<BlobContents> GetObjectFromStoresAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L521-596 _public method_ `public async Task<Uri?> GetObjectWithRedirectAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, CancellationToken cancellationToken = default)`
- L598-645 _public method_ `public async Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken)`
- L647-734 _public method_ `public async Task<BlobContents> ReplicateObjectAsync(NamespaceId ns, BlobId blob, bool supportsRedirectUri = false, bool force = false, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`
- L736-739 _public method_ `public bool ShouldFetchBlobOnDemand(NamespaceId ns)`
- L741-752 _public method_ `public bool IsMultipartUploadSupported(NamespaceId ns)`
- L754-775 _public method_ `public async Task<(string?, string?)> StartMultipartUploadAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L777-797 _public method_ `public async Task CompleteMultipartUploadAsync(NamespaceId ns, string blobName, string uploadId, List<string> partIds, CancellationToken cancellationToken = default)`
- L799-819 _public method_ `public async Task PutMultipartUploadAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, byte[] blobData, CancellationToken cancellationToken = default)`
- L821-839 _public method_ `public async Task<Uri?> MaybePutMultipartUploadWithRedirectAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, CancellationToken cancellationToken = default)`
- L841-892 _public method_ `public async Task<(ContentId, BlobId)> VerifyMultipartUpload(NamespaceId ns, BlobId id, string blobName, bool isCompressed, CancellationToken cancellationToken = default)`
- L894-918 _public method_ `public List<MultipartByteRange> GetMultipartRanges(NamespaceId ns, string uploadId, string blobName, ulong blobLength, CancellationToken cancellationToken = default)`
- L920-937 _public method_ `public MultipartLimits? GetMultipartLimits(NamespaceId ns)`
- L939-947 _public method_ `public async Task CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`
- L949-959 _private method_ `private async Task<HttpRequestMessage> BuildHttpRequestAsync(HttpMethod httpMethod, Uri uri, CancellationToken cancellationToken)`
- L961-981 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool ignoreRemoteBlobs = false, CancellationToken cancellationToken = default)`
- L983-1042 _private method_ `private async Task<bool> ExistsInStoresAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, CancellationToken cancellationToken = default)`
- L1044-1081 _public method_ `public async Task<bool> ExistsInRemoteAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`
- L1083-1099 _public method_ `public async Task<bool> ExistsInRootStoreAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L1101-1150 _public method_ `public async Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L1152-1178 _public method_ `public async Task DeleteObjectAsync(List<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L1180-1207 _public method_ `public async Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L1209-1213 _public method_ `public IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L1215-1235 _public method_ `public async Task<BlobId[]> FilterOutKnownBlobsAsync(NamespaceId ns, IEnumerable<BlobId> blobs, CancellationToken cancellationToken)`
- L1237-1264 _public method_ `public async Task<BlobId[]> FilterOutKnownBlobsAsync(NamespaceId ns, IAsyncEnumerable<BlobId> blobs, CancellationToken cancellationToken)`
- L1266-1286 _public method_ `public async Task<BlobContents> GetObjectsAsync(NamespaceId ns, BlobId[] blobs, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/BlobStoreConsistencyCheckService.cs` (Jupiter)


#### class `Jupiter.Implementation.ConsistencyState`  
`public class ConsistencyState`  
_public; L17-19_

#### class `Jupiter.Implementation.BlobStoreConsistencyCheckService`  
`public class BlobStoreConsistencyCheckService : PollingService<ConsistencyState>`  
_public; L22-160_
- inherits: `PollingService<ConsistencyState>`
- L24 _private field_ `private readonly IOptionsMonitor<ConsistencyCheckSettings> _settings`
- L25 _private field_ `private readonly IOptionsMonitor<UnrealCloudDDCSettings> _unrealCloudDDCSettings`
- L26 _private field_ `private readonly IServiceProvider _provider`
- L27 _private field_ `private readonly ILeaderElection _leaderElection`
- L28 _private field_ `private readonly IReferencesStore _referencesStore`
- L29 _private field_ `private readonly IBlobIndex _blobIndex`
- L30 _private field_ `private readonly Tracer _tracer`
- L31 _private field_ `private readonly ILogger _logger`
- L32 _private field_ `private readonly INamespacePolicyResolver _policyResolver`
- L34-37 _protected method_ `protected override bool ShouldStartPolling()`
- L39-50 _public ctor_ `public BlobStoreConsistencyCheckService(IOptionsMonitor<ConsistencyCheckSettings> settings, IOptionsMonitor<UnrealCloudDDCSettings> unrealCloudDDCSettings, IServiceProvider provider, ILeaderElection leaderElection, IReferencesStore referencesStore, IBlobIndex blobIndex, Tracer tracer, ILogger<BlobStoreConsistencyCheckService> logger, INamespacePolicyResolver policyResolver) : base(serviceName: nameof(BlobStoreConsistencyCheckService), TimeSpan.FromSeconds(settings.CurrentValue.ConsistencyCheckPollFrequencySeconds), new ConsistencyState(), logger)`
- L52-63 _public method_ `public override async Task<bool> OnPollAsync(ConsistencyState state, CancellationToken cancellationToken)`
- L65-138 _private method_ `private async Task RunConsistencyCheckAsync(CancellationToken cancellationToken)`
- L140-154 _private method_ `private bool RunConsistencyCheckOnBlobStore(IBlobStore blobStore)`
- L156-159 _protected method_ `protected override Task OnStopping(ConsistencyState state)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/CachedBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.CachedBlobIndex`  
`public class CachedBlobIndex : IBlobIndex`  
_public; L11-95_
- inherits: `IBlobIndex`
- L13 _private field_ `private readonly FileSystemStore _fileSystemStore`
- L15-18 _public ctor_ `public CachedBlobIndex(FileSystemStore fileSystemStore)`
- L20-25 _public method_ `public async Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L27-31 _public method_ `public async Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L33-37 _public method_ `public async Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L39-42 _public method_ `public IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync(CancellationToken cancellationToken = default)`
- L44-47 _public method_ `public IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken)`
- L49-52 _public method_ `public async Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId blobIdentifier, string? region = null, CancellationToken cancellationToken = default)`
- L54-58 _public method_ `public async Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken)`
- L60-63 _public method_ `public IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync(CancellationToken cancellationToken)`
- L65-69 _public method_ `public Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken)`
- L71-74 _public method_ `public Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`
- L76-79 _public method_ `public Task AddBlobReferencesAsync(NamespaceId ns, BlobId sourceBlob, BlobId targetBlob, CancellationToken cancellationToken)`
- L81-84 _public method_ `public Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken)`
- L86-89 _public method_ `public Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken)`
- L91-94 _public method_ `public Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/DataStoreBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.DataStoreBlobIndex`  
`public class DataStoreBlobIndex : IBlobIndex`  
_public; L14-111_
- inherits: `IBlobIndex`
- L16 _private field_ `private readonly INamespacePolicyResolver _policyResolver`
- L17 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L18 _private field_ `private readonly DataStoreTable<DataStoreBlobRecord> _blobTable`
- L20-25 _public ctor_ `public DataStoreBlobIndex(IDataStoreTableService tableService, INamespacePolicyResolver policyResolver, IOptionsMonitor<JupiterSettings> jupiterSettings)`
- L26-29 _public method_ `public async Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L31-34 _private method_ `private KeyspaceId GetKeyspace(NamespaceId ns)`
- L36-39 _internal method_ `internal static string CalculatePrefix(BlobId id)`
- L41-44 _public method_ `public Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L46-49 _public method_ `public async Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L51-55 _public method_ `public async Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L57-60 _public method_ `public IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync(CancellationToken cancellationToken = default)`
- L62-65 _public method_ `public IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync(CancellationToken cancellationToken = default)`
- L67-70 _public method_ `public IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L72-75 _public method_ `public Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken = default)`
- L77-80 _public method_ `public Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken = default)`
- L82-90 _public method_ `public async Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L92-95 _public method_ `public async Task AddBlobReferencesAsync(NamespaceId ns, BlobId blob, BlobId blobThatReferences, CancellationToken cancellationToken = default)`
- L97-100 _public method_ `public async Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken = default)`
- L102-105 _public method_ `public async Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken = default)`
- L107-110 _public method_ `public async Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`

#### record struct `Jupiter.Implementation.Blob.DataStoreBlobRecord`  
`internal record struct DataStoreBlobRecord : IDataStoreTableObject<DataStoreBlobRecord>`  
_internal; L113-180_
- inherits: `IDataStoreTableObject<DataStoreBlobRecord>`
- L115 _public property_ `public IoHash ContentId { get; set; }`
- L117 _public property_ `public ulong UncompressedSize { get; set; }`
- L119 _public property_ `public ulong CompressedSize { get; set; }`
- L121-126 _public ctor_ `public DataStoreBlobRecord(ContentId contentId, ulong uncompressedSize, ulong compressedSize)`
- L128-133 _public ctor_ `public DataStoreBlobRecord(IoHash contentId, ulong uncompressedSize, ulong compressedSize)`
- L135-138 _public method_ `public static DataStorePartitionKey GetPartitionKey(BlobId blobId)`
- L140-147 _public method_ `public static DataStorePartitionKey? MaybeGetPartitionKey(BlobId? blobId)`
- L149-159 _public method_ `public static byte[] Serialize(DataStoreBlobRecord self)`
- L161-169 _public method_ `public static void Deserialize(byte[] payload, out DataStoreBlobRecord record)`
- L171-174 _public method_ `public static bool HasSortKey()`
- L176-179 _public method_ `public static byte[] GetSortKey(DataStoreBlobRecord self)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/FileSystemStore.cs` (Jupiter)


#### class `Jupiter.Implementation.FileSystemStore`  
`public class FileSystemStore : IBlobStore, IBlobCleanup`  
_public; L21-396_
- inherits: `IBlobStore, IBlobCleanup`
- L23 _private field_ `private readonly IServiceProvider _provider`
- L24 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L25 _private field_ `private readonly IOptionsMonitor<FilesystemSettings> _settings`
- L26 _private field_ `private readonly Tracer _tracer`
- L27 _private field_ `private readonly ILogger<FileSystemStore> _logger`
- L28 _private field_ `private readonly ConcurrentDictionary<NamespaceId, FileStorageBackend> _backends = ...`
- L28 _private field_ `private readonly ConcurrentDictionary< _backends = new ConcurrentDictionary<NamespaceId, FileStorageBackend>()`
- L30-37 _public ctor_ `public FileSystemStore(IOptionsMonitor<FilesystemSettings> settings, Tracer tracer, ILogger<FileSystemStore> logger, IServiceProvider provider, INamespacePolicyResolver namespacePolicyResolver)`
- L39-42 _private method_ `private FileStorageBackend GetBackend(NamespaceId ns)`
- L44-47 _private method_ `private string GetRootDir()`
- L49-58 _public method_ `public static string GetFilesystemPath(BlobId blob)`
- L60-63 _public method_ `public static FileInfo GetFilesystemPath(string rootDir, NamespaceId ns, BlobId blob)`
- L65-68 _public method_ `public DirectoryReference GetFilesystemPath(NamespaceId ns)`
- L70-74 _public method_ `public Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L76-87 _public method_ `public Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L89-92 _public method_ `public Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L94-98 _public method_ `public Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L99-103 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L105-110 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, Stream content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L112-116 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] content, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L118-129 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L131-135 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, bool forceCheck, CancellationToken cancellationToken = default)`
- L137-141 _public method_ `public async Task DeleteObjectAsync(NamespaceId ns, BlobId objectName, CancellationToken cancellationToken = default)`
- L143-150 _public method_ `public async Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId objectName, CancellationToken cancellationToken = default)`
- L152-161 _public method_ `public Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L163-171 _public method_ `public async IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L173-176 _public method_ `public bool ShouldRun()`
- L178-181 _public method_ `public async Task<ulong> CleanupAsync(CancellationToken cancellationToken = default)`
- L190-212 _public method_ `public async Task<ulong> CleanupInternalAsync(CancellationToken cancellationToken = default)` — Clean the store from expired files Uses the configuration to remove the least recently accessed (modified) blobs
- L214-292 _private method_ `private async Task<ulong> RunGCAsync(NamespaceId? ns, CancellationToken cancellationToken = default)`
- L294-315 _private method_ `private (long triggerSize, long targetSize) GetTriggerAndTargetSize(NamespaceId? ns)`
- L317-326 _public method_ `public IEnumerable<FileInfo> GetObjectsOlderThen(DateTime cutoff, NamespaceId? ns = null)`
- L336-347 _public method_ `public IEnumerable<FileInfo> GetLeastRecentlyAccessedObjects(NamespaceId? ns = null, int maxResults = 10_000, int maxCountOfObjectsScanned = 40_000_000)` — Get least recently accessed objects Assumes files on disk have the their last access timestamp up-to-date
- L354-378 _public method_ `public async Task<long> CalculateDiskSpaceUsedAsync(NamespaceId? ns = null)` — Calculate the total size of blobs on disk for given namespace
- L380-389 _public method_ `public IAsyncEnumerable<NamespaceId> ListNamespaces()`
- L391-395 _public method_ `public async Task MoveBufferedPayloadAsync(NamespaceId ns, BlobId blobId, FilesystemBufferedPayload bufferedPayload, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.FileStorageBackend`  
`public class FileStorageBackend : IStorageBackend`  
_public; L398-588_
- inherits: `IStorageBackend`
- L400 _private field_ `private readonly ILogger _logger`
- L401 _private field_ `private readonly DirectoryReference _baseDir`
- L402 _private field_ `private readonly NamespaceId _namespaceId`
- L403 _private field_ `private readonly IOptionsMonitor<FilesystemSettings> _settings`
- L405 _private const_ `private const int DefaultBufferSize = 4096`
- L407-413 _public ctor_ `public FileStorageBackend(DirectoryReference baseDir, NamespaceId ns, ILogger<FileStorageBackend> logger, IOptionsMonitor<FilesystemSettings> settings)`
- L415-418 _private method_ `private string GetRootDir()`
- L420-429 _public method_ `public static FileInfo GetFilesystemPath(string rootDir, NamespaceId ns, BlobId blob)`
- L431-434 _public method_ `public FileInfo GetFilesystemPath(string path)`
- L436-439 _public method_ `public DirectoryInfo GetFilesystemPath(NamespaceId ns)`
- L441 _private* field_ `static readonly string s_processSuffix = Guid.NewGuid().ToString()`
- L442 _private* field_ `static int s_uniqueId = 0`
- L444-480 _public method_ `public async Task WriteAsync(string path, Stream content, CancellationToken cancellationToken = default)`
- L493-503 _private method_ `private static void UpdateLastWriteTime(string filePath, DateTime lastAccessed)` — Update the last modified/write time that is used for determining when file was last accessed Using access time is tricky as many file systems disable that for performance reasons. A new blob written to disk should be set with the oldest possible write time. This will ensure sorting of least recently accessed files during garbage collection works as intended. The write time update will happen async without any waiting to prevent blocking the critical path as it's best-effort only.
- L505-521 _public method_ `public Task<BlobContents?> TryReadAsync(string path, LastAccessTrackingFlags flags, CancellationToken cancellationToken = default)`
- L523-528 _public method_ `public Task<bool> ExistsAsync(string path, CancellationToken cancellationToken = default)`
- L530-538 _public method_ `public Task DeleteAsync(string path, CancellationToken cancellationToken = default)`
- L540-543 _public method_ `public IAsyncEnumerable<(string, DateTime)> ListAsync(CancellationToken cancellationToken = default)`
- L545-558 _private method_ `private IEnumerable<(string, DateTime)> DoListOldObjects()`
- L560-564 _public method_ `public Task<BlobMetadata> GetMetadata(string path)`
- L566-587 _public method_ `public Task MoveBufferedPayloadAsync(string path, FilesystemBufferedPayload bufferedPayload, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/IBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.BucketStats`  
`public class BucketStats`  
_public; L11-21_
- L13 _public property_ `public NamespaceId Namespace { get; set; }`
- L14 _public property_ `public BucketId Bucket { get; set; }`
- L15 _public property_ `public long CountOfRefs { get; set; }`
- L16 _public property_ `public long CountOfBlobs { get; set; }`
- L17 _public property_ `public long TotalSize { get; set; }`
- L18 _public property_ `public double AvgSize { get; set; }`
- L19 _public property_ `public long LargestBlob { get; set; }`
- L20 _public property_ `public long SmallestBlobFound { get; set; }`

#### interface `Jupiter.Implementation.Blob.IBlobIndex`  
`public interface IBlobIndex`  
_public; L23-43_
- L25 _public* method_ `Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L27 _public* method_ `Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L28 _public* method_ `Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L29 _public* method_ `Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId blobIdentifier, string? region = null, CancellationToken cancellationToken = default)`
- L30 _public* method_ `IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync(CancellationToken cancellationToken = default)`
- L32 _public* method_ `IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync(CancellationToken cancellationToken = default)`
- L33 _public* method_ `IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L34 _public* method_ `Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken = default)`
- L36 _public* method_ `Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken = default)`
- L37 _public* method_ `Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L38 _public* method_ `Task AddBlobReferencesAsync(NamespaceId ns, BlobId blob, BlobId blobThatReferences, CancellationToken cancellationToken = default)`
- L40 _public* method_ `Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken = default)`
- L41 _public* method_ `Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken = default)`
- L42 _public* method_ `Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.Blob.BaseBlobReference`  
`public abstract class BaseBlobReference : IEquatable<BaseBlobReference>`  
_public; L45-78_
- inherits: `IEquatable<BaseBlobReference>`
- L47-50 _protected ctor_ `protected BaseBlobReference(BlobId sourceBlob)`
- L52 _public property_ `public BlobId SourceBlob { get; init; }`
- L54-62 _public method_ `public override bool Equals(object? o)`
- L64-67 _public method_ `public override int GetHashCode()`
- L69-77 _public method_ `public virtual bool Equals(BaseBlobReference? other)`

#### class `Jupiter.Implementation.Blob.RefBlobReference`  
`public class RefBlobReference : BaseBlobReference`  
_public; L80-99_
- inherits: `BaseBlobReference`
- L82-86 _public ctor_ `public RefBlobReference(BlobId sourceBlob, BucketId bucket, RefId key) : base(sourceBlob)`
- L88 _public property_ `public BucketId Bucket { get; set; }`
- L89 _public property_ `public RefId Key { get; set; }`
- L90-98 _public method_ `public override bool Equals(BaseBlobReference? other)`

#### class `Jupiter.Implementation.Blob.BlobToBlobReference`  
`public class BlobToBlobReference : BaseBlobReference`  
_public; L101-118_
- inherits: `BaseBlobReference`
- L103-106 _public ctor_ `public BlobToBlobReference(BlobId sourceBlob, BlobId blob) : base(sourceBlob)`
- L108 _public property_ `public BlobId Blob { get; set; }`
- L109-117 _public method_ `public override bool Equals(BaseBlobReference? other)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/IBlobService.cs` (Jupiter)


#### interface `Jupiter.Implementation.IBlobService`  
`public interface IBlobService`  
_public; L18-75_
- L20 _public* method_ `Task<ContentHash> VerifyContentMatchesHashAsync(Stream content, ContentHash identifier, CancellationToken cancellationToken = default)`
- L21 _public* method_ `Task<BlobId> PutObjectKnownHashAsync(NamespaceId ns, IBufferedPayload content, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L22 _public* method_ `Task<BlobId> PutObjectAsync(NamespaceId ns, IBufferedPayload payload, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L23 _public* method_ `Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] payload, BlobId identifier, BucketId? bucketHint = null, bool? bypassCache = null, CancellationToken cancellationToken = default)`
- L24 _public* method_ `Task<Uri?> MaybePutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`
- L26 _public* method_ `Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool supportsRedirectUri = false, bool allowOndemandReplication = true, BucketId? bucketHint = null, bool bypassCache = false, CancellationToken cancellationToken = default)`
- L28 _public* method_ `Task<Uri?> GetObjectWithRedirectAsync(NamespaceId ns, BlobId blobIdentifier, List<string>? storageLayers = null, CancellationToken cancellationToken = default)`
- L30 _public* method_ `Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L32 _public* method_ `Task<BlobContents> ReplicateObjectAsync(NamespaceId ns, BlobId blob, bool supportsRedirectUri = false, bool force = false, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`
- L34 _public* method_ `Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, List<string>? storageLayers = null, bool ignoreRemoteBlobs = false, CancellationToken cancellationToken = default)`
- L43 _public* method_ `Task<bool> ExistsInRootStoreAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)` — Checks that the blob exists in the root store, the store which is last in the list and thus is intended to have every blob in it
- L46 _public* method_ `Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L54 _public* method_ `Task DeleteObjectAsync(List<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)` — Delete the object from multiple namespaces at once, extra efficient if they are all in the same storage pool
- L57 _public* method_ `Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L59 _public* method_ `IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L60 _public* method_ `Task<BlobId[]> FilterOutKnownBlobsAsync(NamespaceId ns, IEnumerable<BlobId> blobs, CancellationToken cancellationToken = default)`
- L61 _public* method_ `Task<BlobId[]> FilterOutKnownBlobsAsync(NamespaceId ns, IAsyncEnumerable<BlobId> blobs, CancellationToken cancellationToken = default)`
- L62 _public* method_ `Task<BlobContents> GetObjectsAsync(NamespaceId ns, BlobId[] refRequestBlobReferences, CancellationToken cancellationToken = default)`
- L64 _public* method_ `bool ShouldFetchBlobOnDemand(NamespaceId ns)`
- L66 _public* method_ `bool IsMultipartUploadSupported(NamespaceId ns)`
- L67 _public* method_ `Task<(string?, string?)> StartMultipartUploadAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L68 _public* method_ `Task CompleteMultipartUploadAsync(NamespaceId ns, string blobName, string uploadId, List<string> partIds, CancellationToken cancellationToken = default)`
- L69 _public* method_ `Task PutMultipartUploadAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, byte[] blobData, CancellationToken cancellationToken = default)`
- L70 _public* method_ `Task<Uri?> MaybePutMultipartUploadWithRedirectAsync(NamespaceId ns, string blobName, string uploadId, string partId, CancellationToken cancellationToken = default)`
- L71 _public* method_ `Task<(ContentId, BlobId)> VerifyMultipartUpload(NamespaceId ns, BlobId blobId, string blobName, bool isCompressed, CancellationToken cancellationToken = default)`
- L72 _public* method_ `List<MultipartByteRange> GetMultipartRanges(NamespaceId ns, string blobName, string uploadId, ulong blobLength, CancellationToken cancellationToken = default)`
- L73 _public* method_ `MultipartLimits? GetMultipartLimits(NamespaceId ns)`
- L74 _public* method_ `Task CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, BucketId? bucketHint = null, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.BlobMetadata`  
`public class BlobMetadata`  
_public; L77-87_
- L79-83 _public ctor_ `public BlobMetadata(long length, DateTime creationTime)`
- L85 _public property_ `public long Length { get; set; }`
- L86 _public property_ `public DateTime CreationTime { get; set; }`

#### class `Jupiter.Implementation.BlobServiceExtensions`  
`public static class BlobServiceExtensions`  
_public; L89-200_
- L91-139 _public method_ `public static async Task<(ContentId, BlobId)> PutCompressedObjectMetadataAsync(this IBlobService blobService, NamespaceId ns, IBufferedPayload payload, ContentId? id, IServiceProvider provider, CancellationToken cancellationToken)`
- L141-150 _public method_ `public static async Task<ContentId> PutCompressedObjectAsync(this IBlobService blobService, NamespaceId ns, IBufferedPayload payload, ContentId? id, IServiceProvider provider, CancellationToken cancellationToken, BucketId? bucketHint = null, bool? bypassCache = null)`
- L152-199 _public method_ `public static async Task<(BlobContents, string, BlobId?)> GetCompressedObjectAsync(this IBlobService blobService, NamespaceId ns, ContentId contentId, IServiceProvider provider, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.HashMismatchException`  
`public class HashMismatchException : Exception`  
_public; L202-212_
- inherits: `Exception`
- L204 _public property_ `public ContentHash SuppliedHash { get; }`
- L205 _public property_ `public ContentHash ContentHash { get; }`
- L207-211 _public ctor_ `public HashMismatchException(ContentHash suppliedHash, ContentHash contentHash) : base($"ID was not a hash of the content uploaded. Supplied hash was: {suppliedHash} but hash of content was {contentHash}")`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/IBlobStore.cs` (Jupiter)


#### enum `Jupiter.Implementation.LastAccessTrackingFlags`  
`public enum LastAccessTrackingFlags`  
_public; L12-16_
- L14 _public* enumerator_ `DoTracking = 0`
- L15 _public* enumerator_ `SkipTracking = 1`

#### interface `Jupiter.Implementation.IBlobStore`  
`public interface IBlobStore`  
_public; L18-42_
- L20 _public* method_ `Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L21 _public* method_ `Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L22 _public* method_ `Task<BlobId> PutObjectAsync(NamespaceId ns, Stream content, BlobId identifier, CancellationToken cancellationToken = default)`
- L24 _public* method_ `Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L25 _public* method_ `Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, bool forceCheck = false, CancellationToken cancellationToken = default)`
- L28 _public* method_ `Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L31 _public* method_ `Task DeleteObjectAsync(IEnumerable<NamespaceId> ns, BlobId blob, CancellationToken cancellationToken = default)`
- L34 _public* method_ `Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L36 _public* method_ `IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L37 _public* method_ `Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L38 _public* method_ `Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L39 _public* method_ `Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L41 _public* method_ `Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`

#### interface `Jupiter.Implementation.IMultipartBlobStore`  
`public interface IMultipartBlobStore`  
_public; L44-54_
- L46 _public* method_ `Task<string> StartMultipartUploadAsync(NamespaceId ns, string blobName, CancellationToken cancellationToken = default)`
- L47 _public* method_ `Task CompleteMultipartUploadAsync(NamespaceId ns, string path, string uploadId, List<string> partIds, CancellationToken cancellationToken = default)`
- L48 _public* method_ `Task PutMultipartPartAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, byte[] blob, CancellationToken cancellationToken = default)`
- L49 _public* method_ `Task<Uri?> GetWriteRedirectForPartAsync(NamespaceId ns, string blobName, string uploadId, string partIdentifier, CancellationToken cancellationToken = default)`
- L50 _public* method_ `Task<BlobContents?> GetMultipartObjectByNameAsync(NamespaceId ns, string blobName, CancellationToken cancellationToken = default)`
- L51 _public* method_ `Task RenameMultipartBlobAsync(NamespaceId ns, string blobName, BlobId blobId, CancellationToken cancellationToken = default)`
- L52 _public* method_ `List<MultipartByteRange> GetMultipartRanges(NamespaceId ns, string uploadId, ulong blobLength, CancellationToken cancellationToken = default)`
- L53 _public* method_ `MultipartLimits GetMultipartLimits(NamespaceId ns, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.MissingMultipartPartsException`  
`public class MissingMultipartPartsException : Exception`  
_public; L56-64_
- inherits: `Exception`
- L58-61 _public ctor_ `public MissingMultipartPartsException(List<string> missingParts)`
- L63 _public property_ `public List<string> MissingParts { get; init; }`

#### record `Jupiter.Implementation.MultipartLimits`  
`public record MultipartLimits`  
_public; L66-71_
- L68 _public property_ `public uint MinChunkSize { get; set; }`
- L69 _public property_ `public uint IdealChunkSize { get; set; }`
- L70 _public property_ `public int MaxCountOfChunks { get; set; }`

#### record `Jupiter.Implementation.MultipartByteRange`  
`public record MultipartByteRange`  
_public; L72-77_
- L74 _public property_ `public ulong FirstByte { get; set; }`
- L75 _public property_ `public ulong LastByte { get; set; }`
- L76 _public property_ `public string PartId { get; set; }`

#### interface `Jupiter.Implementation.IStorageBackend`  
`public interface IStorageBackend`  
_public; L79-86_
- L81 _public* method_ `Task WriteAsync(string path, Stream content, CancellationToken cancellationToken = default)`
- L82 _public* method_ `Task<BlobContents?> TryReadAsync(string path, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, CancellationToken cancellationToken = default)`
- L83 _public* method_ `Task<bool> ExistsAsync(string path, CancellationToken cancellationToken = default)`
- L84 _public* method_ `Task DeleteAsync(string path, CancellationToken cancellationToken = default)`
- L85 _public* method_ `IAsyncEnumerable<(string, DateTime)> ListAsync(CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.BlobNotFoundException`  
`public class BlobNotFoundException : Exception`  
_public; L88-104_
- inherits: `Exception`
- L90 _public property_ `public NamespaceId Ns { get; }`
- L91 _public property_ `public BlobId Blob { get; }`
- L93-97 _public ctor_ `public BlobNotFoundException(NamespaceId ns, BlobId blob) : base($"No Blob in Namespace {ns} with id {blob}")`
- L99-103 _public ctor_ `public BlobNotFoundException(NamespaceId ns, BlobId blob, string message) : base(message)`

#### class `Jupiter.Implementation.BlobReplicationException`  
`public class BlobReplicationException : BlobNotFoundException`  
_public; L106-111_
- inherits: `BlobNotFoundException`
- L108-110 _public ctor_ `public BlobReplicationException(NamespaceId ns, BlobId blob, string message) : base(ns, blob, message)`

#### class `Jupiter.Implementation.BlobToLargeException`  
`public class BlobToLargeException : Exception`  
_public; L113-121_
- inherits: `Exception`
- L115 _public property_ `public BlobId Blob { get; }`
- L117-120 _public ctor_ `public BlobToLargeException(BlobId blob) : base($"Blob {blob} was to large to cache")`

#### class `Jupiter.Implementation.ResourceHasToManyRequestsException`  
`public class ResourceHasToManyRequestsException : Exception`  
_public; L123-128_
- inherits: `Exception`
- L125-127 _public ctor_ `public ResourceHasToManyRequestsException(Exception originalException) : base($"To many requests to resource", originalException)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/MemoryBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.MemoryBlobIndex`  
`public class MemoryBlobIndex : IBlobIndex`  
_public; L15-295_
- inherits: `IBlobIndex`
- L50 _private field_ `private readonly ConcurrentDictionary<NamespaceId, ConcurrentDictionary<BlobId, MemoryBlobInfo>> _index = ...`
- L50 _private field_ `private readonly ConcurrentDictionary< BlobId`
- L50 _private field_ `private readonly ConcurrentDictionary< _index = new()`
- L51 _private field_ `private readonly ConcurrentDictionary<NamespaceId, ConcurrentDictionary<BucketId, MemoryBucketInfo>> _bucketIndex = ...`
- L51 _private field_ `private readonly ConcurrentDictionary< BucketId`
- L51 _private field_ `private readonly ConcurrentDictionary< _bucketIndex = new()`
- L52 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L54-57 _public ctor_ `public MemoryBlobIndex(IOptionsMonitor<JupiterSettings> settings)`
- L59-62 _private method_ `private ConcurrentDictionary<BlobId, MemoryBlobInfo> GetNamespaceContainer(NamespaceId ns)`
- L64-70 _public method_ `public Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L72-82 _private method_ `private Task<MemoryBlobInfo?> GetBlobInfo(NamespaceId ns, BlobId id)`
- L84-99 _public method_ `public Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L101-107 _public method_ `public Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L109-114 _public method_ `public async Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId blobIdentifier, string? region = null, CancellationToken cancellationToken = default)`
- L116-130 _public method_ `public async IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L132-143 _public method_ `public async IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L145-164 _public method_ `public Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken)`
- L166-177 _public method_ `public async IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L179-199 _public method_ `public Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken)`
- L201-211 _public method_ `public async Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`
- L213-223 _public method_ `public async Task AddBlobReferencesAsync(NamespaceId ns, BlobId sourceBlob, BlobId targetBlob, CancellationToken cancellationToken)`
- L225-232 _public method_ `public Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken)`
- L234-245 _public method_ `public Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken)`
- L247-282 _public method_ `public Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L284-294 _private method_ `private static MemoryBlobInfo NewBlobInfo(NamespaceId ns, BlobId blob, string region)`

#### class `Jupiter.Implementation.Blob.MemoryBlobIndex.MemoryBlobInfo`  
`private class MemoryBlobInfo`  
_private; L17-23_
- L19 _public property_ `public HashSet<string> Regions { get; init; }`
- L20 _public property_ `public NamespaceId Namespace { get; init; }`
- L21 _public property_ `public BlobId BlobIdentifier { get; init; }`
- L22 _public property_ `public List<BaseBlobReference> References { get; init; }`

#### class `Jupiter.Implementation.Blob.MemoryBlobIndex.MemoryBucketInfo`  
`private class MemoryBucketInfo`  
_private; L25-48_
- L27 _public property_ `public List<(RefId, BlobId, long)> Entries { get; init; }`
- L29-42 _public method_ `public void AddEntry(RefId refId, BlobId blobId, long value)`
- L44-47 _public method_ `public void RemoveEntriesForRef(RefId refId)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/MemoryBlobStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryBlobStore`  
`internal class MemoryBlobStore : IBlobStore`  
_internal; L16-150_
- inherits: `IBlobStore`
- L18 _private field_ `private readonly ConcurrentDictionary<NamespaceId, MemoryStorageBackend> _backends = ...`
- L18 _private field_ `private readonly ConcurrentDictionary< _backends = new ConcurrentDictionary<NamespaceId, MemoryStorageBackend>()`
- L25 _private field_ `private readonly bool _throwOnOverwrite` — Throw an exception when putting an object that already exists Primarily used for testing.
- L27-30 _public ctor_ `public MemoryBlobStore(bool throwOnOverwrite = false)`
- L32-35 _internal method_ `internal MemoryStorageBackend GetBackend(NamespaceId ns)`
- L37 _private method_ `private static string GetPath(BlobId blob)`
- L39-43 _public method_ `public Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L44-48 _public method_ `public Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L50-59 _public method_ `public async Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L61-78 _public method_ `public async Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L80-84 _public method_ `public Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L86-89 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L91-96 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, Stream blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L98-106 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L108 _public method_ `public Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L110-118 _public method_ `public Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L120 _public method_ `public Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, bool forceCheck = false, CancellationToken cancellationToken = default)`
- L122-129 _public method_ `public Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L131-138 _public method_ `public async IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L140-143 _internal method_ `internal IEnumerable<BlobId> GetIdentifiers(NamespaceId ns)`
- L146-149 _internal method_ `internal void SetLastModifiedTime(NamespaceId ns, BlobId blob, DateTime modifiedTime)`

#### class `Jupiter.Implementation.MemoryStorageBackend`  
`internal class MemoryStorageBackend : IStorageBackend`  
_internal; L152-248_
- inherits: `IStorageBackend`
- L168 _private field_ `private readonly ConcurrentDictionary<string, BlobContainer> _blobs = ...`
- L168 _private field_ `private readonly ConcurrentDictionary< _blobs = new ConcurrentDictionary<string, BlobContainer>(StringComparer.Ordinal)`
- L175 _private field_ `private readonly bool throwOnOverwrite` — Throw an exception when putting an object that already exists Primarily used for testing.
- L177-180 _public ctor_ `public MemoryStorageBackend(bool throwOnOverwrite = false)`
- L182-194 _public method_ `public async Task WriteAsync(string path, Stream stream, CancellationToken cancellationToken = default)`
- L196-205 _public method_ `public Task<BlobContents?> TryReadAsync(string path, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, CancellationToken cancellationToken = default)`
- L207-211 _public method_ `public Task DeleteAsync(string path, CancellationToken cancellationToken = default)`
- L213-216 _public method_ `public Task<bool> ExistsAsync(string path, CancellationToken cancellationToken = default)`
- L218-225 _public method_ `public async IAsyncEnumerable<(string, DateTime)> ListAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L227 _public method_ `public IEnumerable<string> GetIdentifiers()`
- L230-236 _public method_ `public void SetLastModifiedTime(string path, DateTime modifiedTime)`
- L238-247 _public method_ `public Task<BlobMetadata?> GetObjectMetadataAsync(string path)`

#### class `Jupiter.Implementation.MemoryStorageBackend.BlobContainer`  
`private class BlobContainer`  
_private; L154-166_
- L156 _public property_ `public string Path { get; }`
- L157 _public property_ `public byte[] Contents { get; }`
- L158 _public property_ `public DateTime LastModified { get; set; }`
- L160-165 _public ctor_ `public BlobContainer(string path, byte[] contents)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/MongoBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.MongoBlobIndex`  
`public class MongoBlobIndex : MongoStore, IBlobIndex`  
_public; L17-317_
- inherits: `MongoStore, IBlobIndex`
- L19 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L21-41 _public ctor_ `public MongoBlobIndex(IOptionsMonitor<JupiterSettings> jupiterSettings, IOptionsMonitor<MongoSettings> settings) : base(settings)`
- L43-54 _private method_ `private async Task<MongoBlobIndexModelV0?> GetBlobInfoAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken)`
- L56-69 _public method_ `public async Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L71-88 _public method_ `public async Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L90-95 _public method_ `public async Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L97-128 _public method_ `public async IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L130-156 _public method_ `public async IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L158-162 _public method_ `public async Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId blobIdentifier, string? region = null, CancellationToken cancellationToken = default)`
- L164-183 _public method_ `public async Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken)`
- L185-197 _public method_ `public async IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L199-237 _public method_ `public async Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken)`
- L239-247 _public method_ `public async Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`
- L249-259 _public method_ `public async Task AddBlobReferencesAsync(NamespaceId ns, BlobId sourceBlob, BlobId targetBlob, CancellationToken cancellationToken)`
- L261-267 _public method_ `public async Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken)`
- L269-275 _public method_ `public async Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken)`
- L277-316 _public method_ `public async Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.Blob.MongoBlobIndexModelV0`  
`class MongoBlobIndexModelV0`  
_internal*; L322-350_
- attrs: `[BsonDiscriminator("blob-index.v0")] [BsonIgnoreExtraElements] [MongoCollectionName("BlobIndex")]`
- L325-331 _public ctor_ `public MongoBlobIndexModelV0(string ns, string blobId, List<string> regions, List<Dictionary<string, string>> references)` — attrs: `[BsonConstructor]`
- L333-337 _public ctor_ `public MongoBlobIndexModelV0(NamespaceId ns, BlobId blobId)`
- L340 _public property_ `public string Ns { get; set; }` — attrs: `[BsonRequired]`
- L343 _public property_ `public string BlobId { get; set; }` — attrs: `[BsonRequired]`
- L345 _public property_ `public List<string> Regions { get; set; }`
- L348 _public property_ `public List<Dictionary<string, string>> References { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.Document)]`

#### class `Jupiter.Implementation.Blob.MongoBucketBlobV0`  
`class MongoBucketBlobV0`  
_internal*; L355-390_
- attrs: `[BsonDiscriminator("bucket-blob.v0")] [BsonIgnoreExtraElements] [MongoCollectionName("BucketBlob")]`
- L358-365 _public ctor_ `public MongoBucketBlobV0(string ns, string bucketId, string refId, string blobId, long size)` — attrs: `[BsonConstructor]`
- L367-374 _public ctor_ `public MongoBucketBlobV0(NamespaceId ns, BucketId bucketId, RefId refId, BlobId blobId, long size)`
- L377 _public property_ `public string Ns { get; set; }` — attrs: `[BsonRequired]`
- L380 _public property_ `public string BucketId { get; set; }` — attrs: `[BsonRequired]`
- L383 _public property_ `public string RefId { get; set; }` — attrs: `[BsonRequired]`
- L386 _public property_ `public string BlobId { get; set; }` — attrs: `[BsonRequired]`
- L389 _public property_ `public long Size { get; set; }` — attrs: `[BsonRequired]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/PathUtil.cs` (Jupiter)


#### class `Jupiter.Implementation.PathUtil`  
`public static class PathUtil`  
_public; L9-16_
- L11-15 _public method_ `public static string ResolvePath(string path)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/PeerBlobStore.cs` (Jupiter)


#### class `Jupiter.Implementation.PeerBlobStore`  
`public class PeerBlobStore : IBlobStore`  
_public; L22-233_
- inherits: `IBlobStore`
- L24 _private field_ `private readonly IPeerServiceDiscovery _serviceDiscovery`
- L25 _private field_ `private readonly IHttpClientFactory _httpClientFactory`
- L26 _private field_ `private readonly IServiceCredentials _serviceCredentials`
- L27 _private field_ `private readonly ILogger _logger`
- L29-35 _public ctor_ `public PeerBlobStore(IPeerServiceDiscovery serviceDiscovery, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials, ILogger<PeerBlobStore> logger)`
- L37-47 _private method_ `private async Task<HttpRequestMessage> BuildHttpRequestAsync(HttpMethod method, Uri uri, CancellationToken cancellationToken = default)`
- L49-81 _private method_ `private async Task<BlobContents?> DoGetObjectAsync(string instance, NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L83-106 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags = LastAccessTrackingFlags.DoTracking, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L108-132 _private method_ `private async Task<bool?> DoExistsAsync(string instance, NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L134-157 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, bool forceCheck = false, CancellationToken cancellationToken = default)`
- L159-167 _private method_ `private HttpClient GetHttpClient(string instance)`
- L169-173 _public method_ `public Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L175-179 _public method_ `public Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L181-184 _public method_ `public Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L186-190 _public method_ `public Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L192-196 _public method_ `public Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L198-202 _public method_ `public Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L204-208 _public method_ `public Task<BlobId> PutObjectAsync(NamespaceId ns, Stream content, BlobId identifier, CancellationToken cancellationToken = default)`
- L210-214 _public method_ `public Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L216-220 _public method_ `public Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L222-226 _public method_ `public Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L228-232 _public method_ `public IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`

#### interface `Jupiter.Implementation.IPeerServiceDiscovery`  
`public interface IPeerServiceDiscovery`  
_public; L235-238_
- L237 _public method_ `public IAsyncEnumerable<string> FindOtherInstances(CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.StaticPeerServiceDiscoverySettings`  
`public class StaticPeerServiceDiscoverySettings`  
_public; L240-244_
- L243 _public property_ `public List<string> Peers { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.Implementation.StaticPeerServiceDiscovery`  
`public sealed class StaticPeerServiceDiscovery : IPeerServiceDiscovery`  
_public; L246-263_
- inherits: `IPeerServiceDiscovery`
- L248 _private field_ `private readonly IOptionsMonitor<StaticPeerServiceDiscoverySettings> _settings`
- L250-253 _public ctor_ `public StaticPeerServiceDiscovery(IOptionsMonitor<StaticPeerServiceDiscoverySettings> settings)`
- L255-262 _public method_ `public async IAsyncEnumerable<string> FindOtherInstances([EnumeratorCancellation] CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.KubernetesPeerServiceDiscovery`  
`public sealed class KubernetesPeerServiceDiscovery : IPeerServiceDiscovery, IDisposable`  
_public; L265-340_
- inherits: `IPeerServiceDiscovery, IDisposable`
- L267 _private field_ `private readonly IOptionsMonitor<KubernetesLeaderElectionSettings> _leaderSettings`
- L268 _private field_ `private readonly Kubernetes _client`
- L269 _private field_ `private DateTime _podEnumerationValidUntil = DateTime.Now`
- L270 _private field_ `private List<string>? _lastPodEnumeration`
- L272-277 _public ctor_ `public KubernetesPeerServiceDiscovery(IOptionsMonitor<KubernetesLeaderElectionSettings> leaderSettings)`
- L279-297 _public method_ `public async IAsyncEnumerable<string> FindOtherInstances([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L299-325 _private method_ `private async IAsyncEnumerable<string> EnumeratePodsAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L327-333 _private method_ `private void Dispose(bool disposing)`
- L335-339 _public method_ `public void Dispose()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/RefStoreConsistencyCheckService.cs` (Jupiter)


#### class `Jupiter.Implementation.RefConsistencyState`  
`public class RefConsistencyState`  
_public; L16-18_

#### class `Jupiter.Implementation.RefStoreConsistencyCheckService`  
`public class RefStoreConsistencyCheckService : PollingService<ConsistencyState>`  
_public; L21-215_
- inherits: `PollingService<ConsistencyState>`
- L23 _private field_ `private readonly IOptionsMonitor<ConsistencyCheckSettings> _settings`
- L24 _private field_ `private readonly ILeaderElection _leaderElection`
- L25 _private field_ `private readonly IRefService _refService`
- L26 _private field_ `private readonly IReferencesStore _referencesStore`
- L27 _private field_ `private readonly IPeerStatusService _peerStatusService`
- L28 _private field_ `private readonly IBlobIndex _blobIndex`
- L29 _private field_ `private readonly Tracer _tracer`
- L30 _private field_ `private readonly ILogger _logger`
- L32-35 _protected method_ `protected override bool ShouldStartPolling()`
- L37-47 _public ctor_ `public RefStoreConsistencyCheckService(IOptionsMonitor<ConsistencyCheckSettings> settings, ILeaderElection leaderElection, IRefService refService, IBlobIndex blobIndex, Tracer tracer, ILogger<RefStoreConsistencyCheckService> logger, IReferencesStore referencesStore, IPeerStatusService peerStatusService) : base(serviceName: nameof(RefStoreConsistencyCheckService), TimeSpan.FromSeconds(settings.CurrentValue.ConsistencyCheckPollFrequencySeconds), new ConsistencyState(), logger)`
- L49-67 _public method_ `public override async Task<bool> OnPollAsync(ConsistencyState state, CancellationToken cancellationToken = default)`
- L69-144 _public method_ `public async Task RunConsistencyCheckAsync(CancellationToken cancellationToken = default)`
- L146-209 _private method_ `private async Task<bool> VerifyRegionalConsistencyAsync(NamespaceId ns, BucketId bucket, RefId refId)`
- L211-214 _protected method_ `protected override Task OnStopping(ConsistencyState state)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/RelayBlobStore.cs` (Jupiter)


#### class `Jupiter.Implementation.RelayBlobStore`  
`public class RelayBlobStore : RelayStore, IBlobStore`  
_public; L17-134_
- inherits: `RelayStore, IBlobStore`
- L19-21 _public ctor_ `public RelayBlobStore(IOptionsMonitor<UpstreamRelaySettings> settings, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials) : base(settings, httpClientFactory, serviceCredentials)`
- L23-27 _public method_ `public Task<Uri?> GetObjectByRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L29-33 _public method_ `public Task<BlobMetadata> GetObjectMetadataAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken = default)`
- L35-38 _public method_ `public Task<ulong> CopyBlobAsync(NamespaceId ns, NamespaceId targetNamespace, BlobId blobId, CancellationToken cancellationToken = default)`
- L40-45 _public method_ `public Task<Uri?> PutObjectWithRedirectAsync(NamespaceId ns, BlobId identifier, CancellationToken cancellationToken = default)`
- L47-60 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, byte[] blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L62-65 _public method_ `public Task<BlobId> PutObjectAsync(NamespaceId ns, ReadOnlyMemory<byte> blob, BlobId identifier, CancellationToken cancellationToken = default)`
- L67-78 _public method_ `public async Task<BlobId> PutObjectAsync(NamespaceId ns, Stream content, BlobId identifier, CancellationToken cancellationToken = default)`
- L80-99 _public method_ `public async Task<BlobContents> GetObjectAsync(NamespaceId ns, BlobId blob, LastAccessTrackingFlags flags, bool supportsRedirectUri = false, CancellationToken cancellationToken = default)`
- L101-113 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BlobId blob, bool forceCheck, CancellationToken cancellationToken = default)`
- L115-118 _public method_ `public Task DeleteObjectAsync(IEnumerable<NamespaceId> namespaces, BlobId blob, CancellationToken cancellationToken = default)`
- L120-123 _public method_ `public Task DeleteObjectAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken = default)`
- L125-128 _public method_ `public Task DeleteNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L130-133 _public method_ `public IAsyncEnumerable<(BlobId, DateTime)> ListObjectsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Blob/ScyllaBlobIndex.cs` (Jupiter)


#### class `Jupiter.Implementation.Blob.ScyllaBlobIndex`  
`public class ScyllaBlobIndex : IBlobIndex`  
_public; L19-670_
- inherits: `IBlobIndex`
- L21 _private field_ `private readonly IScyllaSessionManager _scyllaSessionManager`
- L22 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L23 _private field_ `private readonly IOptionsMonitor<ScyllaSettings> _scyllaSettings`
- L24 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L25 _private field_ `private readonly Tracer _tracer`
- L26 _private field_ `private readonly ISession _session`
- L27 _private field_ `private readonly Mapper _mapper`
- L28 _private field_ `private readonly PreparedStatement? _getBucketStatsStatement`
- L29 _private field_ `private readonly PreparedStatement? _getBucketStatsRefsStatement`
- L31 _private field_ `private readonly PreparedStatement _getBlobReferenceStatement`
- L33-101 _public ctor_ `public ScyllaBlobIndex(IScyllaSessionManager scyllaSessionManager, IOptionsMonitor<JupiterSettings> jupiterSettings, IOptionsMonitor<ScyllaSettings> scyllaSettings, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer)`
- L103-117 _public method_ `public async Task AddBlobToIndexAsync(NamespaceId ns, BlobId id, ulong rawSize, string? region = null, CancellationToken cancellationToken = default)`
- L119-142 _private method_ `private async Task<List<string>?> GetOldBlobRegionsAsync(NamespaceId ns, BlobId id)`
- L144-167 _private method_ `private async Task<List<ScyllaObjectReference>?> GetOldBlobReferencesAsync(NamespaceId ns, BlobId id)`
- L169-182 _public method_ `public async Task RemoveBlobFromRegionAsync(NamespaceId ns, BlobId id, string? region = null, CancellationToken cancellationToken = default)`
- L184-196 _public method_ `public async Task RemoveBlobFromAllRegionsAsync(NamespaceId ns, BlobId id, CancellationToken cancellationToken = default)`
- L198-235 _public method_ `public async Task<bool> BlobExistsInRegionAsync(NamespaceId ns, BlobId blobIdentifier, string? region = null, CancellationToken cancellationToken = default)`
- L236-256 _public method_ `public async IAsyncEnumerable<(NamespaceId, BlobId)> GetAllBlobsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L258-302 _public method_ `public async IAsyncEnumerable<(NamespaceId, BaseBlobReference)> GetAllBlobReferencesAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L304-346 _public method_ `public async Task<List<string>> GetBlobRegionsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`
- L348-363 _public method_ `public async Task AddBlobReferencesAsync(NamespaceId ns, BlobId sourceBlob, BlobId targetBlob, CancellationToken cancellationToken)`
- L365-444 _public method_ `public async IAsyncEnumerable<BaseBlobReference> GetBlobReferencesAsync(NamespaceId ns, BlobId id, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L446-477 _public method_ `public async Task AddRefToBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId[] blobs, CancellationToken cancellationToken)`
- L479-522 _public method_ `public async Task RemoveReferencesAsync(NamespaceId ns, BlobId id, List<BaseBlobReference>? referencesToRemove, CancellationToken cancellationToken)`
- L524-544 _public method_ `public async Task AddBlobToBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobId, long blobSize, CancellationToken cancellationToken)`
- L546-563 _public method_ `public async Task RemoveBlobFromBucketListAsync(NamespaceId ns, BucketId bucket, RefId key, List<BlobId> blobIds, CancellationToken cancellationToken)`
- L565-669 _public method_ `public async Task<BucketStats> CalculateBucketStatisticsAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.Blob.ScyllaBlobIndexTable`  
`class ScyllaBlobIndexTable`  
_internal*; L673-703_
- attrs: `[Cassandra.Mapping.Attributes.Table("blob_index")]`
- L675-681 _public ctor_ `public ScyllaBlobIndexTable()`
- L683-689 _public ctor_ `public ScyllaBlobIndexTable(string @namespace, BlobId blobId, HashSet<string> regions, List<ScyllaObjectReference> references)`
- L692 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L696 _public property_ `public ScyllaBlobIdentifier BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("blob_id")]`
- L699 _public property_ `public HashSet<string>? Regions { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("regions")]`
- L702 _public property_ `public List<ScyllaObjectReference>? References { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("references")]`

#### class `Jupiter.Implementation.Blob.CassandraBlobIndexTable`  
`class CassandraBlobIndexTable`  
_internal*; L706-736_
- attrs: `[Cassandra.Mapping.Attributes.Table("blob_index")]`
- L708-714 _public ctor_ `public CassandraBlobIndexTable()`
- L716-722 _public ctor_ `public CassandraBlobIndexTable(string @namespace, BlobId blobId, HashSet<string> regions, List<ScyllaObjectReference> references)`
- L725 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L729 _public property_ `public byte[] BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("blob_id")]`
- L732 _public property_ `public HashSet<string>? Regions { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("regions")]`
- L735 _public property_ `public List<ScyllaObjectReference>? References { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("references")]`

#### class `Jupiter.Implementation.Blob.ScyllaBlobIndexEntry`  
`class ScyllaBlobIndexEntry`  
_internal*; L739-765_
- attrs: `[Cassandra.Mapping.Attributes.Table("blob_index_v2")]`
- L741-746 _public ctor_ `public ScyllaBlobIndexEntry()`
- L748-753 _public ctor_ `public ScyllaBlobIndexEntry(string @namespace, BlobId blobId, string region)`
- L756 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L760 _public property_ `public byte[] BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("blob_id")]`
- L764 _public property_ `public string Region { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("region")]`

#### class `Jupiter.Implementation.Blob.ScyllaBlobIncomingReference`  
`class ScyllaBlobIncomingReference`  
_internal*; L768-816_
- attrs: `[Cassandra.Mapping.Attributes.Table("blob_incoming_references")]`
- L772-778 _public ctor_ `public ScyllaBlobIncomingReference()`
- L780-788 _public ctor_ `public ScyllaBlobIncomingReference(string @namespace, BlobId blobId, BlobId referenceId)`
- L790-798 _public ctor_ `public ScyllaBlobIncomingReference(string @namespace, BlobId blobId, RefId referenceId, BucketId bucketId)`
- L801 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L805 _public property_ `public byte[] BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("blob_id")]`
- L809 _public property_ `public byte[] ReferenceId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("reference_id")]`
- L812 _public property_ `public string? BucketId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket_id")]`
- L815 _public property_ `public short ReferenceType { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("reference_type")]`

#### enum `Jupiter.Implementation.Blob.ScyllaBlobIncomingReference.BlobReferenceType`  
`public enum BlobReferenceType`  
_public; L770-770_
- L770 _public* enumerator_ `Ref = 0`
- L770 _public* enumerator_ `Blob = 1`

#### class `Jupiter.Implementation.Blob.ScyllaBucketReferencedBlob`  
`class ScyllaBucketReferencedBlob`  
_internal*; L819-865_
- attrs: `[Cassandra.Mapping.Attributes.Table("bucket_referenced_blobs")]`
- L821-828 _public ctor_ `public ScyllaBucketReferencedBlob()`
- L830-837 _public ctor_ `public ScyllaBucketReferencedBlob(string @namespace, BucketId bucket, BlobId blobId)`
- L839-846 _public ctor_ `public ScyllaBucketReferencedBlob(string @namespace, BucketId bucket, BlobId blobId, long blobSize)`
- L849 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L853 _public property_ `public string Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("bucket_id")]`
- L857 _public property_ `public string HashPrefix { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("hash_prefix")]`
- L861 _public property_ `public byte[] BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("blob_id")]`
- L864 _public property_ `public long Size { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("size")]`

#### class `Jupiter.Implementation.Blob.ScyllaBucketReferencedRef`  
`class ScyllaBucketReferencedRef`  
_internal*; L868-900_
- attrs: `[Cassandra.Mapping.Attributes.Table("bucket_referenced_ref")]`
- L870-876 _public ctor_ `public ScyllaBucketReferencedRef()`
- L878-884 _public ctor_ `public ScyllaBucketReferencedRef(string @namespace, BucketId bucket, RefId refId)`
- L887 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L891 _public property_ `public string Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("bucket_id")]`
- L895 _public property_ `public string HashPrefix { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("hash_prefix")]`
- L899 _public property_ `public string ReferenceId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("reference_id")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/BuildStoreConsistencyCheckService.cs` (Jupiter)


#### class `Jupiter.Implementation.BuildStoreConsistencyState`  
`public class BuildStoreConsistencyState`  
_public; L15-17_

#### class `Jupiter.Implementation.BuildStoreConsistencyCheckService`  
`public class BuildStoreConsistencyCheckService : PollingService<BuildStoreConsistencyState>`  
_public; L20-204_
- inherits: `PollingService<BuildStoreConsistencyState>`
- L22 _private field_ `private readonly IOptionsMonitor<ConsistencyCheckSettings> _settings`
- L23 _private field_ `private readonly ILeaderElection _leaderElection`
- L24 _private field_ `private readonly IBuildStore _buildStore`
- L25 _private field_ `private readonly IBlobService _blobService`
- L26 _private field_ `private readonly IBlockStore _blockStore`
- L27 _private field_ `private readonly IRefService _refService`
- L28 _private field_ `private readonly IReferenceResolver _referenceResolver`
- L29 _private field_ `private readonly Tracer _tracer`
- L30 _private field_ `private readonly ILogger _logger`
- L32-35 _protected method_ `protected override bool ShouldStartPolling()`
- L37-48 _public ctor_ `public BuildStoreConsistencyCheckService(IOptionsMonitor<ConsistencyCheckSettings> settings, ILeaderElection leaderElection, IBuildStore buildStore, IBlobService blobService, IBlockStore blockStore, IRefService refService, IReferenceResolver referenceResolver, Tracer tracer, ILogger<BuildStoreConsistencyCheckService> logger) : base(serviceName: nameof(BuildStoreConsistencyCheckService), TimeSpan.FromSeconds(settings.CurrentValue.ConsistencyCheckPollFrequencySeconds), new BuildStoreConsistencyState(), logger)`
- L50-68 _public method_ `public override async Task<bool> OnPollAsync(BuildStoreConsistencyState state, CancellationToken cancellationToken)`
- L70-198 _private method_ `private async Task RunConsistencyCheckAsync(CancellationToken cancellationToken)`
- L200-203 _protected method_ `protected override Task OnStopping(BuildStoreConsistencyState state)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/IBlockStore.cs` (Jupiter)


#### class `Jupiter.Implementation.BlockMetadata`  
`public class BlockMetadata`  
_public; L12-16_
- L14 _public property_ `public DateTime LastUpdate { get; set; }`
- L15 _public property_ `public BlobId MetadataBlobId { get; set; }`

#### class `Jupiter.Implementation.RequiredFieldMissingException`  
`public class RequiredFieldMissingException : Exception`  
_public; L18-26_
- inherits: `Exception`
- L20 _public property_ `public List<string> MissingFields { get; init; }`
- L22-25 _public ctor_ `public RequiredFieldMissingException(List<string> missingFields) : base($"The following required fields were missing or empty: {string.Join(",", missingFields)}")`

#### class `Jupiter.Implementation.BlockContext`  
`public class BlockContext`  
_public; L28-81_
- L30 _private field_ `private readonly string _context`
- L32-35 _public ctor_ `public BlockContext(string context)`
- L37-75 _public method_ `public static BlockContext FromObject(CbObject o, bool useBaseBranch = false)`
- L77-80 _public method_ `public override string ToString()`

#### interface `Jupiter.Implementation.IBlockStore`  
`public interface IBlockStore`  
_public; L83-90_
- L85 _public* method_ `IAsyncEnumerable<BlockMetadata> ListBlockIndexAsync(NamespaceId ns, BlockContext blockContext)`
- L86 _public* method_ `Task AddBlockToContextAsync(NamespaceId ns, BlockContext blockContext, BlobId metadataBlockId)`
- L87 _public* method_ `Task PutBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier, BlobId metadataObjectId)`
- L88 _public* method_ `Task<BlobId?> GetBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier)`
- L89 _public* method_ `Task DeleteBlockAsync(NamespaceId ns, BlobId blockIdentifier)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/IBuildStore.cs` (Jupiter)


#### interface `Jupiter.Implementation.IBuildStore`  
`public interface IBuildStore`  
_public; L11-29_
- L13 _public* method_ `Task PutBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObject buildObject, uint ttl)`
- L14 _public* method_ `Task FinalizeBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L15 _public* method_ `Task<BuildRecord?> GetBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L16 _public* method_ `IAsyncEnumerable<BuildMetadata> ListBuildsAsync(NamespaceId ns, BucketId bucket, bool includeTTL = false)`
- L18 _public* method_ `Task PutBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, string partName, uint ttl)`
- L19 _public* method_ `IAsyncEnumerable<(string, CbObjectId)> GetBuildPartsAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L21 _public* method_ `Task PutBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixName, uint ttl)`
- L22 _public* method_ `IAsyncEnumerable<string> GetBuildAppendixesAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L23 _public* method_ `Task DeleteBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixFileName)`
- L25 _public* method_ `Task UpdateTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L26 _public* method_ `Task DeleteBuild(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L27 _public* method_ `Task<uint?> GetTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L28 _public* method_ `IAsyncEnumerable<(NamespaceId, BucketId, CbObjectId, bool)> ListAllBuildsAsync(CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.BuildMetadata`  
`public class BuildMetadata`  
_public; L31-47_
- L33-40 _public ctor_ `public BuildMetadata(CbObjectId buildId, BucketId bucket, CbObject metadata, bool isFinalized, uint? ttl)`
- L42 _public property_ `public CbObjectId BuildId { get; set; }`
- L43 _public property_ `public CbObject Metadata { get; set; }`
- L44 _public property_ `public bool IsFinalized { get; set; }`
- L45 _public property_ `public uint? Ttl { get; set; }`
- L46 _public property_ `public BucketId Bucket { get; set; }`

#### class `Jupiter.Implementation.BuildRecord`  
`public class BuildRecord`  
_public; L49-54_
- L51 _public property_ `public bool IsFinalized { get; set; }`
- L52 _public property_ `public CbObject BuildObject { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/MemoryBlockStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryBlockStore`  
`public class MemoryBlockStore : IBlockStore`  
_public; L12-79_
- inherits: `IBlockStore`
- L14 _private field_ `private readonly ConcurrentDictionary<string, MemoryBlockContext> _blockContext = ...`
- L14 _private field_ `private readonly ConcurrentDictionary< _blockContext = new()`
- L15 _private field_ `private readonly ConcurrentDictionary<string, BlobId> _blockMetadata = ...`
- L15 _private field_ `private readonly ConcurrentDictionary< _blockMetadata = new()`
- L17-28 _public method_ `public async IAsyncEnumerable<BlockMetadata> ListBlockIndexAsync(NamespaceId ns, BlockContext blockContext)`
- L30-45 _public method_ `public Task AddBlockToContextAsync(NamespaceId ns, BlockContext blockContext, BlobId metadataBlockId)`
- L47-54 _public method_ `public Task PutBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier, BlobId metadataObjectId)`
- L56-61 _public method_ `public Task<BlobId?> GetBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier)`
- L63-68 _public method_ `public Task DeleteBlockAsync(NamespaceId ns, BlobId blockIdentifier)`
- L70-73 _private method_ `private static string BuildKey(NamespaceId ns, BlockContext blockContext)`
- L75-78 _private method_ `private static string BuildKeyBlockMetadata(NamespaceId ns, BlobId blobId)`

#### class `Jupiter.Implementation.MemoryBlockContext`  
`public class MemoryBlockContext`  
_public; L81-84_
- L83 _public property_ `public ConcurrentDictionary<BlobId, BlockMetadata> Blocks { get; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/MemoryBuildStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryBuildStore`  
`public class MemoryBuildStore : IBuildStore`  
_public; L15-177_
- inherits: `IBuildStore`
- L17 _private field_ `private readonly ConcurrentDictionary<string, MemoryBuildRecord> _builds = ...`
- L17 _private field_ `private readonly ConcurrentDictionary< _builds = new()`
- L19-36 _public method_ `public Task PutBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObject buildObject, uint ttl)`
- L38-48 _public method_ `public Task FinalizeBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L50-53 _public method_ `public Task<BuildRecord?> GetBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L55-60 _public method_ `public Task DeleteBuild(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L62-74 _public method_ `public async IAsyncEnumerable<BuildMetadata> ListBuildsAsync(NamespaceId ns, BucketId bucket, bool includeTTL = false)`
- L76-88 _public method_ `public Task PutBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, string partName, uint ttl)`
- L90-103 _public method_ `public async IAsyncEnumerable<(string, CbObjectId)> GetBuildPartsAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L105-116 _public method_ `public Task PutBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixName, uint ttl)`
- L118-131 _public method_ `public async IAsyncEnumerable<string> GetBuildAppendixesAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L133-143 _public method_ `public Task DeleteBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixFileName)`
- L145-155 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L157-162 _public method_ `public Task<uint?> GetTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L164-171 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, CbObjectId, bool)> ListAllBuildsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L173-176 _private method_ `private static string BuildKey(NamespaceId ns, BucketId bucket, CbObjectId buildId)`

#### class `Jupiter.Implementation.MemoryBuildPart`  
`internal class MemoryBuildPart`  
_internal; L179-183_
- L181 _public property_ `public CbObjectId PartId { get; init; }`
- L182 _public property_ `public string PartName { get; init; }`

#### class `Jupiter.Implementation.MemoryBuildRecord`  
`internal class MemoryBuildRecord`  
_internal; L185-201_
- L187 _public property_ `public bool IsFinalized { get; set; }`
- L188 _public property_ `public DateTime ExpireTime { get; set; }`
- L189 _public property_ `public CbObject BuildObject { get; set; }`
- L190 _public property_ `public ConcurrentDictionary<string, MemoryBuildPart> BuildParts { get; set; }`
- L191 _public property_ `public ConcurrentDictionary<string, string> BuildAppendix { get; set; }`
- L192 _public property_ `public NamespaceId Namespace { get; set; }`
- L193 _public property_ `public BucketId Bucket { get; set; }`
- L194 _public property_ `public CbObjectId BuildId { get; set; }`
- L195 _public property_ `public DateTime CreationDate { get; set; }`
- L197-200 _public method_ `public BuildRecord ToBuildRecord()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/ScyllaBlockStore.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaBlockStore`  
`public class ScyllaBlockStore : IBlockStore`  
_public; L14-141_
- inherits: `IBlockStore`
- L16 _private field_ `private readonly Tracer _tracer`
- L17 _private field_ `private readonly ISession _session`
- L18 _private field_ `private readonly Mapper _mapper`
- L20-49 _public ctor_ `public ScyllaBlockStore(IScyllaSessionManager scyllaSessionManager, IOptionsMonitor<ScyllaSettings> scyllaSettings, Tracer tracer)`
- L51-61 _public method_ `public async IAsyncEnumerable<BlockMetadata> ListBlockIndexAsync(NamespaceId ns, BlockContext blockContext)`
- L63-75 _public method_ `public async Task AddBlockToContextAsync(NamespaceId ns, BlockContext blockContext, BlobId metadataBlockId)`
- L77-89 _public method_ `public async Task PutBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier, BlobId metadataObjectId)`
- L91-111 _public method_ `public async Task<BlobId?> GetBlockMetadataAsync(NamespaceId ns, BlobId blockIdentifier)`
- L113-140 _public method_ `public async Task DeleteBlockAsync(NamespaceId ns, BlobId blockIdentifier)`

#### class `Jupiter.Implementation.ScyllaBlockIndexEntry`  
`public class ScyllaBlockIndexEntry`  
_public; L144-169_
- attrs: `[Cassandra.Mapping.Attributes.Table("block_index")]`
- L146-151 _public ctor_ `public ScyllaBlockIndexEntry()`
- L153-158 _public ctor_ `public ScyllaBlockIndexEntry(NamespaceId @namespace, BlobId blockId, BlobId metadataBlobId)`
- L161 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L165 _public property_ `public byte[] BlockId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("block_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L168 _public property_ `public byte[] MetadataBlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("metadata_blob_id")]`

#### class `Jupiter.Implementation.ScyllaBlockContextEntry`  
`public class ScyllaBlockContextEntry`  
_public; L172-203_
- attrs: `[Cassandra.Mapping.Attributes.Table("block_context")]`
- L174-180 _public ctor_ `public ScyllaBlockContextEntry()`
- L182-188 _public ctor_ `public ScyllaBlockContextEntry(NamespaceId @namespace, BlockContext context, DateTime lastUpdate, BlobId blockId)`
- L191 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L195 _public property_ `public string BlockContext { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("block_context")]`
- L199 _public property_ `public DateTime LastUpdate { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("last_update")]`
- L202 _public property_ `public byte[] MetadataBlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("block_id")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/ScyllaBuildStore.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaBuildStore`  
`public class ScyllaBuildStore : IBuildStore`  
_public; L17-345_
- inherits: `IBuildStore`
- L19 _private field_ `private readonly IScyllaSessionManager _scyllaSessionManager`
- L20 _private field_ `private readonly Tracer _tracer`
- L21 _private field_ `private readonly ISession _session`
- L22 _private field_ `private readonly Mapper _mapper`
- L23 _private field_ `private readonly PreparedStatement _getTtlStatement`
- L25-67 _public ctor_ `public ScyllaBuildStore(IScyllaSessionManager scyllaSessionManager, IOptionsMonitor<ScyllaSettings> scyllaSettings, Tracer tracer)`
- L69-100 _public method_ `public async IAsyncEnumerable<BuildMetadata> ListBuildsAsync(NamespaceId ns, BucketId bucket, bool includeTTL = false)`
- L102-114 _public method_ `public async Task PutBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObject buildObject, uint ttl)`
- L116-126 _public method_ `public async Task FinalizeBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L128-145 _public method_ `public async Task<BuildRecord?> GetBuildAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L147-159 _public method_ `public async Task PutBuildPartAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, CbObjectId partId, string partName, uint ttl)`
- L161-180 _public method_ `public async IAsyncEnumerable<(string, CbObjectId)> GetBuildPartsAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L182-194 _public method_ `public async Task PutBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixName, uint ttl)`
- L196-215 _public method_ `public async IAsyncEnumerable<string> GetBuildAppendixesAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L217-229 _public method_ `public async Task DeleteBuildAppendixAsync(NamespaceId ns, BucketId bucket, CbObjectId buildId, string appendixName)`
- L231-255 _public method_ `public async Task<uint?> GetTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId)`
- L257-277 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, CbObjectId, bool)> ListAllBuildsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L279-330 _public method_ `public async Task UpdateTTL(NamespaceId ns, BucketId bucket, CbObjectId buildId, uint ttl)`
- L332-344 _public method_ `public async Task DeleteBuild(NamespaceId ns, BucketId bucket, CbObjectId buildId)`

#### class `Jupiter.Implementation.ScyllaBuildEntry`  
`public class ScyllaBuildEntry`  
_public; L348-396_
- attrs: `[Cassandra.Mapping.Attributes.Table("builds")]`
- L350-357 _public ctor_ `public ScyllaBuildEntry()`
- L359-366 _public ctor_ `public ScyllaBuildEntry(NamespaceId @namespace, BucketId bucketId, CbObjectId buildId, CbObject buildObject)`
- L369 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L373 _public property_ `public string BucketId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L377 _public property_ `public byte[] BuildId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("build_id")] [Cassandra.Mapping.Attributes.ClusteringKey]`
- L380 _public property_ `public byte[]? BuildObject { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("build_object")]`
- L383 _public property_ `public bool IsFinalized { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("is_finalized")]`
- L384-395 _public method_ `public BuildMetadata? ToBuildMetadata()`

#### class `Jupiter.Implementation.ScyllaBuildPartEntry`  
`public class ScyllaBuildPartEntry`  
_public; L399-436_
- attrs: `[Cassandra.Mapping.Attributes.Table("build_parts")]`
- L401-408 _public ctor_ `public ScyllaBuildPartEntry()`
- L410-417 _public ctor_ `public ScyllaBuildPartEntry(NamespaceId @namespace, BucketId bucketId, CbObjectId buildId, CbObjectId partId, string partName)`
- L420 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L424 _public property_ `public string BucketId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L428 _public property_ `public byte[] BuildId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("build_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L431 _public property_ `public string PartName { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("part_name")]`
- L435 _public property_ `public byte[] PartId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("part_id")] [Cassandra.Mapping.Attributes.ClusteringKey]`

#### class `Jupiter.Implementation.ScyllaBuildAppendixEntry`  
`public class ScyllaBuildAppendixEntry`  
_public; L439-471_
- attrs: `[Cassandra.Mapping.Attributes.Table("build_appendixes")]`
- L441-447 _public ctor_ `public ScyllaBuildAppendixEntry()`
- L449-455 _public ctor_ `public ScyllaBuildAppendixEntry(NamespaceId @namespace, BucketId bucketId, CbObjectId buildId, string appendixName)`
- L458 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L462 _public property_ `public string BucketId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L466 _public property_ `public byte[] BuildId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("build_id")] [Cassandra.Mapping.Attributes.PartitionKey]`
- L470 _public property_ `public string AppendixName { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("appendix_name")] [Cassandra.Mapping.Attributes.ClusteringKey]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Builds/SearchOp.cs` (Jupiter)


#### interface `Jupiter.Implementation.Builds.ISearchOp`  
`interface ISearchOp`  
_internal*; L15-18_
- L17 _public* method_ `bool Matches(CbObjectId buildId, CbObject o, ILogger logger)`

#### class `Jupiter.Implementation.Builds.CompareOp`  
`class CompareOp : ISearchOp`  
_internal*; L20-588_
- inherits: `ISearchOp`
- L22 _private field_ `private readonly string _fieldName`
- L23 _private field_ `private readonly OpType _opType`
- L24 _private field_ `private readonly JsonElement? _expectedFieldJson`
- L25 _private field_ `private readonly CbField? _expectedField`
- L27-33 _private ctor_ `private CompareOp(string fieldName, OpType opType, JsonElement expectedFieldJson)`
- L35-41 _private ctor_ `private CompareOp(string fieldName, OpType opType, CbField expectedField)`
- L55-201 _private method_ `private static bool MatchesJson(CbField field, JsonElement expectedField, OpType op, ILogger logger)`
- L203-252 _private method_ `private static bool CbFieldEquals(CbField cbField, CbField expectedField)`
- L254-305 _private method_ `private static bool FieldEquals(CbField field, JsonElement jsonElement, ILogger logger)`
- L307-472 _private method_ `private static bool MatchesCB(CbField field, CbField expectedField, OpType op, ILogger logger)`
- L474-506 _public method_ `public bool Matches(CbObjectId buildId, CbObject o, ILogger logger)`
- L508-538 _private method_ `private static CbField FindField(string fieldName, CbObject cbObject)`
- L540-550 _public method_ `public static IEnumerable<CompareOp> Parse(string fieldName, JsonElement jsonElement)`
- L552-562 _public method_ `public static IEnumerable<CompareOp> Parse(string fieldName, CbObject cbObject)`
- L564-587 _private method_ `private static OpType? FindOpType(string key)`

#### enum `Jupiter.Implementation.Builds.CompareOp.OpType`  
`enum OpType`  
_private*; L43-53_
- L45 _public* enumerator_ `Equals`
- L46 _public* enumerator_ `GreaterThen`
- L47 _public* enumerator_ `GreaterThenOrEquals`
- L48 _public* enumerator_ `In`
- L49 _public* enumerator_ `LessThen`
- L50 _public* enumerator_ `LessThenOrEquals`
- L51 _public* enumerator_ `NotEquals`
- L52 _public* enumerator_ `NotIn`

#### class `Jupiter.Implementation.Builds.LogicalOp`  
`abstract class LogicalOp : ISearchOp`  
_internal*; L590-600_
- inherits: `ISearchOp`
- L592-595 _protected ctor_ `protected LogicalOp(List<ISearchOp> childOps)`
- L597 _protected field_ `protected readonly List<ISearchOp> ChildOps`
- L599 _public method_ `public abstract bool Matches(CbObjectId buildId, CbObject o, ILogger logger)`

#### class `Jupiter.Implementation.Builds.AndOp`  
`class AndOp : LogicalOp`  
_internal*; L602-640_
- inherits: `LogicalOp`
- L604-606 _private ctor_ `private AndOp(List<ISearchOp> childOps) : base(childOps)`
- L608-619 _public method_ `public override bool Matches(CbObjectId buildId, CbObject o, ILogger logger)`
- L621-629 _public method_ `public static AndOp Parse(CbObject o)`
- L631-639 _public method_ `public static AndOp Parse(JsonElement element)`

#### class `Jupiter.Implementation.Builds.OrOp`  
`class OrOp : LogicalOp`  
_internal*; L642-680_
- inherits: `LogicalOp`
- L644-646 _private ctor_ `private OrOp(List<ISearchOp> childOps) : base(childOps)`
- L648-659 _public method_ `public override bool Matches(CbObjectId buildId, CbObject o, ILogger logger)`
- L661-669 _public method_ `public static OrOp Parse(CbObject o)`
- L671-679 _public method_ `public static OrOp Parse(JsonElement element)`

#### class `Jupiter.Implementation.Builds.SearchOpHelpers`  
`static class SearchOpHelpers`  
_internal*; L682-753_
- L684-715 _internal method_ `internal static IEnumerable<ISearchOp> Parse(JsonProperty prop)`
- L717-752 _internal method_ `internal static IEnumerable<ISearchOp> Parse(CbField field)`

#### class `Jupiter.Implementation.Builds.InvalidSyntaxException`  
`public class InvalidSyntaxException : Exception`  
_public; L754-759_
- inherits: `Exception`
- L756-758 _public ctor_ `public InvalidSyntaxException(string key, object value): base( $"Invalid syntax for key ({key}) with value {value}")`

#### class `Jupiter.Implementation.Builds.UnsupportedOperationException`  
`public class UnsupportedOperationException : Exception`  
_public; L761-766_
- inherits: `Exception`
- L763-765 _public ctor_ `public UnsupportedOperationException(string s) :base(s)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/CombinedStream.cs` (Jupiter)


#### class `Jupiter.Controllers.CombinedStream`  
`internal class CombinedStream : Stream`  
_internal; L10-76_
- inherits: `Stream`
- L12 _private field_ `private readonly List<Stream> _streams`
- L13 _private field_ `private readonly long _length`
- L15-19 _public ctor_ `public CombinedStream(IEnumerable<Stream> streams)`
- L20-48 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L50-53 _public method_ `public override void Flush()`
- L54-57 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L59-62 _public method_ `public override void SetLength(long value)`
- L64-67 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L69 _public property_ `public override bool CanRead { get; }`
- L70 _public property_ `public override bool CanSeek { get; }`
- L71 _public property_ `public override bool CanWrite { get; }`
- L73 _public property_ `public override long Length => ...`
- L75 _public property_ `public override long Position { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/CommonHeaders.cs` (Jupiter)


#### class `Jupiter.Implementation.CommonHeaders`  
`public static class CommonHeaders`  
_public; L5-16_
- L7 _public const_ `public const string HashHeaderSHA1Name = "X-Jupiter-Sha1"`
- L8 _public const_ `public const string HashHeaderName = "X-Jupiter-IoHash"`
- L10 _public const_ `public const string LastAccessHeaderName = "X-Jupiter-LastAccess"`
- L12 _public const_ `public const string InlinePayloadHash = "X-Jupiter-InlinePayloadHash"`
- L14 _public const_ `public const string AllowOverwrite = "X-Jupiter-Allow-Overwrite"`
- L15 _public const_ `public const string ForceConsistentRead = "X-Jupiter-Force-Consistent-Read"`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/CacheContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.CacheContentIdStore`  
`public class CacheContentIdStore : RelayStore, IContentIdStore`  
_public; L16-58_
- inherits: `RelayStore, IContentIdStore`
- L19-21 _public ctor_ `public CacheContentIdStore(IOptionsMonitor<UpstreamRelaySettings> settings, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials) : base(settings, httpClientFactory, serviceCredentials)`
- L23-41 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId, CancellationToken cancellationToken)`
- L43-52 _public method_ `public async Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken)`
- L54-57 _public method_ `public IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId identifier, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/CompressedBufferUtils.cs` (Jupiter)


#### class `Jupiter.Implementation.CompressedBufferUtils`  
`public class CompressedBufferUtils`  
_public; L14-70_
- L16 _private field_ `private readonly Tracer _tracer`
- L17 _private field_ `private readonly BufferedPayloadFactory _payloadFactory`
- L19-23 _public ctor_ `public CompressedBufferUtils(Tracer tracer, BufferedPayloadFactory payloadFactory)`
- L25-69 _public method_ `public async Task<(IBufferedPayload, IoHash)> DecompressContentAsync(Stream sourceStream, ulong streamSize, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/DataStoreContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.DataStoreContentIdStore`  
`public class DataStoreContentIdStore : IContentIdStore`  
_public; L15-110_
- inherits: `IContentIdStore`
- L17 _private field_ `private readonly IBlobService _blobService`
- L18 _private field_ `private readonly INamespacePolicyResolver _policyResolver`
- L19 _private field_ `private readonly DataStoreTable<DataStoreCidRecord> _cidTable`
- L21-26 _public ctor_ `public DataStoreContentIdStore(IDataStoreTableService tableService, IBlobService blobService, INamespacePolicyResolver policyResolver)`
- L28-75 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId = false, CancellationToken cancellationToken = default)`
- L77-86 _public method_ `public async Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken = default)`
- L88-99 _public method_ `public async IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId contentId, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L101-104 _private method_ `private static string CalculatePrefix(ContentId id)`
- L106-109 _private method_ `private KeyspaceId GetKeyspace(NamespaceId ns)`

#### record struct `Jupiter.Implementation.DataStoreCidRecord`  
`internal record struct DataStoreCidRecord : IDataStoreTableObject<DataStoreCidRecord>`  
_internal; L112-166_
- inherits: `IDataStoreTableObject<DataStoreCidRecord>`
- L114 _public property_ `public IoHash Blob { get; set; }`
- L116 _public property_ `public int Weight { get; set; }`
- L118-121 _public ctor_ `public DataStoreCidRecord(BlobId blob)`
- L123-126 _public method_ `public static DataStorePartitionKey GetPartitionKey(ContentId cid)`
- L128-135 _public method_ `public static DataStorePartitionKey? MaybeGetPartitionKey(ContentId? cid)`
- L137-146 _public method_ `public static byte[] Serialize(DataStoreCidRecord self)`
- L148-155 _public method_ `public static void Deserialize(byte[] payload, out DataStoreCidRecord record)`
- L157-160 _public method_ `public static bool HasSortKey()`
- L162-165 _public method_ `public static byte[] GetSortKey(DataStoreCidRecord self)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/IContentIdStore.cs` (Jupiter)


#### interface `Jupiter.Implementation.IContentIdStore`  
`public interface IContentIdStore`  
_public; L11-43_
- L21 _public* method_ `Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId = false, CancellationToken cancellationToken = default)` — Resolve a content id from its hash into the actual blob (that can in turn be chunked into a set of blobs)
- L33 _public* method_ `Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken = default)` — Add a mapping from contentId to a chunked set of blobIdentifiers
- L42 _public* method_ `IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId identifier, CancellationToken cancellationToken = default)` — Retrieve the underlying content id mapping structure

#### class `Jupiter.Implementation.ContentIdMapping`  
`public class ContentIdMapping`  
_public; L45-55_
- L47-51 _public ctor_ `public ContentIdMapping(int weight, BlobId[] referencedBlobs)`
- L53 _public property_ `public int Weight { get; set; }`
- L54 _public property_ `public BlobId[] ReferencedBlobs { get; set; }`

#### class `Jupiter.Implementation.InvalidContentIdException`  
`public class InvalidContentIdException : Exception`  
_public; L57-63_
- inherits: `Exception`
- L59-62 _public ctor_ `public InvalidContentIdException(ContentId contentId) : base($"Unknown content id {contentId}")`

#### class `Jupiter.Implementation.ContentIdResolveException`  
`public class ContentIdResolveException : Exception`  
_public; L65-73_
- inherits: `Exception`
- L67 _public property_ `public ContentId ContentId { get; }`
- L69-72 _public ctor_ `public ContentIdResolveException(ContentId contentId) : base($"Unable to find any mapping of contentId {contentId} that has all blobs present")`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/MemoryCachedContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryCachedContentIdStore`  
`public class MemoryCachedContentIdStore : IContentIdStore`  
_public; L14-90_
- inherits: `IContentIdStore`
- L16 _private field_ `private readonly IContentIdStore _actualContentIdStore`
- L17 _private field_ `private readonly ConcurrentDictionary<NamespaceId, MemoryCache> _contentIdCaches = ...`
- L17 _private field_ `private readonly ConcurrentDictionary< _contentIdCaches = new ConcurrentDictionary<NamespaceId, MemoryCache>()`
- L18 _private field_ `private readonly IOptionsMonitor<MemoryCacheContentIdSettings> _options`
- L20-24 _public ctor_ `public MemoryCachedContentIdStore(IContentIdStore actualContentIdStore, IOptionsMonitor<MemoryCacheContentIdSettings> options)`
- L26-29 _public method_ `public IContentIdStore GetUnderlyingContentIdStore()`
- L31-34 _public method_ `public void Clear()`
- L36-54 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId, CancellationToken cancellationToken)`
- L56-59 _public method_ `public IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId identifier, CancellationToken cancellationToken)`
- L61-66 _public method_ `public Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken)`
- L68-84 _private method_ `private void AddCacheEntry(NamespaceId ns, ContentId contentId, BlobId[] blobs)`
- L86-89 _private method_ `private MemoryCache GetCacheForNamespace(NamespaceId ns)`

#### class `Jupiter.Implementation.CachedContentIdEntry`  
`class CachedContentIdEntry`  
_internal*; L92-97_
- L94 _public method_ `public int GetSize()`
- L96 _public property_ `public BlobId[] ReferencedBlobs { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/MemoryContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryContentIdStore`  
`public class MemoryContentIdStore : IContentIdStore`  
_public; L12-101_
- inherits: `IContentIdStore`
- L14 _private field_ `private readonly IBlobService _blobStore`
- L15 _private field_ `private readonly ConcurrentDictionary<NamespaceId, ConcurrentDictionary<ContentId, SortedList<int, BlobId[]>>> _contentIds = ...`
- L15 _private field_ `private readonly ConcurrentDictionary< ContentId`
- L15 _private field_ `private readonly ConcurrentDictionary< int`
- L15 _private field_ `private readonly ConcurrentDictionary< _contentIds = new ConcurrentDictionary<NamespaceId, ConcurrentDictionary<ContentId, SortedList<int, BlobId[]>>>()`
- L17-20 _public ctor_ `public MemoryContentIdStore(IBlobService blobStore)`
- L22-48 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId, CancellationToken cancellationToken)`
- L50-82 _public method_ `public Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken)`
- L84-100 _public method_ `public async IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId identifier, [EnumeratorCancellation] CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/MongoContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MongoContentIdStore`  
`public class MongoContentIdStore : MongoStore, IContentIdStore`  
_public; L16-102_
- inherits: `MongoStore, IContentIdStore`
- L18 _private field_ `private readonly IBlobService _blobStore`
- L20-38 _public ctor_ `public MongoContentIdStore(IBlobService blobStore, IOptionsMonitor<MongoSettings> settings) : base(settings)`
- L40-74 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId, CancellationToken cancellationToken)`
- L76-87 _public method_ `public async Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken)`
- L89-101 _public method_ `public async IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId contentId, [EnumeratorCancellation] CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.MongoContentIdModelV0`  
`public class MongoContentIdModelV0`  
_public; L107-137_
- attrs: `[BsonDiscriminator("content-id.v0")] [BsonIgnoreExtraElements] [MongoCollectionName("ContentId")]`
- L110-115 _public ctor_ `public MongoContentIdModelV0(string ns, string contentId, Dictionary<int, string[]> contentWeightToBlobsMap)` — attrs: `[BsonConstructor]`
- L117-126 _public ctor_ `public MongoContentIdModelV0(NamespaceId ns, ContentId contentId, int contentWeight, BlobId[] blobs)`
- L129 _public property_ `public string Ns { get; set; }` — attrs: `[BsonRequired]`
- L132 _public property_ `public string ContentId { get; set; }` — attrs: `[BsonRequired]`
- L136 _public property_ `public Dictionary<int, string[]> ContentWeightToBlobsMap { get; set; }` — attrs: `[BsonDictionaryOptions(DictionaryRepresentation.ArrayOfDocuments)] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ContentId/ScyllaContentIdStore.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaContentIdStore`  
`public class ScyllaContentIdStore : IContentIdStore`  
_public; L17-200_
- inherits: `IContentIdStore`
- L19 _private field_ `private readonly ISession _session`
- L20 _private field_ `private readonly IBlobService _blobStore`
- L21 _private field_ `private readonly Tracer _tracer`
- L22 _private field_ `private readonly IOptionsMonitor<ScyllaSettings> _settings`
- L23 _private field_ `private readonly Mapper _mapper`
- L24 _private field_ `private readonly IScyllaSessionManager _scyllaSessionManager`
- L26-47 _public ctor_ `public ScyllaContentIdStore(IScyllaSessionManager scyllaSessionManager, IBlobService blobStore, Tracer tracer, IOptionsMonitor<ScyllaSettings> settings)`
- L49-144 _public method_ `public async Task<BlobId[]?> ResolveAsync(NamespaceId ns, ContentId contentId, bool mustBeContentId, CancellationToken cancellationToken)`
- L146-176 _public method_ `public async IAsyncEnumerable<ContentIdMapping> GetContentIdMappingsAsync(NamespaceId ns, ContentId contentId, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L178-199 _public method_ `public async Task PutAsync(NamespaceId ns, ContentId contentId, BlobId[] blobIdentifiers, ulong compressedSize, ulong rawSize, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.ScyllaContentId`  
`public class ScyllaContentId`  
_public; L203-226_
- attrs: `[Cassandra.Mapping.Attributes.Table("content_id")]`
- L205-208 _public ctor_ `public ScyllaContentId()`
- L210-215 _public ctor_ `public ScyllaContentId(BlobId contentId, BlobId[] chunks, int contentWeight)`
- L219 _public property_ `public ScyllaBlobIdentifier? ContentId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("content_id")]`
- L223 _public property_ `public int? ContentWeight { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("content_weight")]`
- L225 _public property_ `public ScyllaBlobIdentifier[] Chunks { get; set; }`

#### class `Jupiter.Implementation.CassandraContentId`  
`public class CassandraContentId`  
_public; L229-252_
- attrs: `[Cassandra.Mapping.Attributes.Table("content_id")]`
- L231-234 _public ctor_ `public CassandraContentId()`
- L236-241 _public ctor_ `public CassandraContentId(BlobId contentId, BlobId[] chunks, int contentWeight)`
- L245 _public property_ `public byte[]? ContentId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("content_id")]`
- L249 _public property_ `public int? ContentWeight { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey] [Cassandra.Mapping.Attributes.Column("content_weight")]`
- L251 _public property_ `public byte[][] Chunks { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStore.cs` (Jupiter)


#### class `Jupiter.DataStore.DataStoreSettings`  
`public class DataStoreSettings`  
_public; L11-15_
- L13 _public property_ `public string RootDir { get; set; }`
- L14 _public property_ `public bool Enabled { get; set; }`

#### record `Jupiter.DataStore.DataStoreFile`  
`public record DataStoreFile(string Path, long Size, DateTime LastModifiedUtc)`  
_public; L17-19_

#### interface `Jupiter.DataStore.IDataStoreObjectStore`  
`public interface IDataStoreObjectStore`  
_public; L21-28_
- L23 _public* method_ `Task PutFileAsync(KeyspaceId keyspace, FileInfo localPath, string remotePath, CancellationToken cancellationToken)`
- L24 _public* method_ `IAsyncEnumerable<(KeyspaceId keyspace, string prefix)> EnumeratePrefixesAsync(TableType typeName, CancellationToken cancellationToken)`
- L25 _public* method_ `Task<bool> GetFileAsync(KeyspaceId keyspace, string remotePath, FileInfo localFile, CancellationToken token)`
- L26 _public* method_ `IAsyncEnumerable<DataStoreFile> EnumerateFilesAsync(KeyspaceId keyspace, string remotePath, CancellationToken cancellationToken)`
- L27 _public* method_ `Task DeleteFilesAsync(KeyspaceId keyspace, string remotePath, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreObjectStreamReader.cs` (Jupiter)


#### record `Jupiter.DataStore.CbObjectStreamHeader`  
`public record CbObjectStreamHeader`  
_public; L16-68_
- L18 _private const_ `private const uint ExpectedMagic = 0xb7756362`
- L19 _private const_ `private const uint CurrentVersion = 2`
- L21-25 _public ctor_ `public CbObjectStreamHeader()`
- L27-35 _public method_ `public void WriteToStream(Stream s)`
- L37-63 _public method_ `public static CbObjectStreamHeader ReadHeader(Stream s)`
- L65 _public property_ `public uint Version { get; set; }`
- L67 _public property_ `public uint Magic { get; set; }`

#### class `Jupiter.DataStore.DataStoreObjectStreamReader`  
`internal class DataStoreObjectStreamReader(FileStream fs, int bufferSize) : IDisposable, IAsyncDisposable`  
_internal; L70-203_
- L72-75 _public method_ `public void Dispose()`
- L77-80 _public method_ `public async ValueTask DisposeAsync()`
- L82-202 _public method_ `public async IAsyncEnumerable<(DataStorePartitionKey, byte[])> GetObjectBuffersAsync([EnumeratorCancellation] CancellationToken cancellationToken)`

#### class `Jupiter.DataStore.InvalidStreamException`  
`internal class InvalidStreamException(string msg) : Exception(msg)`  
_internal; L205-205_

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreSegmentId.cs` (Jupiter)


#### struct `Jupiter.DataStore.DataStoreSegmentId`  
`public readonly struct DataStoreSegmentId(uint a, uint b, uint c, uint d) : IEquatable<DataStoreSegmentId>, IComparer<DataStoreSegmentId>, IComparable<DataStoreSegmentId>`  
_public; L25-235_
- attrs: `[JsonConverter(typeof(DataStoreSegmentIdJsonConverter))] [TypeConverter(typeof(DataStoreSegmentIdTypeConverter))]`
- desc: SegmentId similar to an uuid type 4, also similar to CbObjectId but with a bigger time component to prevent overflows
- L28 _private field_ `private readonly uint _a = a`
- L29 _private field_ `private readonly uint _b = b`
- L30 _private field_ `private readonly uint _c = c`
- L31 _private field_ `private readonly uint _d = d`
- L34 _private field_ `private static uint s_objectIdSerial = CalculateRunId()`
- L39 _public property_ `public static DataStoreSegmentId Zero { get; }` — The zero value
- L45-47 _public ctor_ `public DataStoreSegmentId(ReadOnlySpan<byte> payload) : this(BinaryPrimitives.ReadUInt32BigEndian(payload[0..4]), BinaryPrimitives.ReadUInt32BigEndian(payload[4..8]), BinaryPrimitives.ReadUInt32BigEndian(payload[8..12]), BinaryPrimitives.ReadUInt32BigEndian(payload[12..16]))` — Constructor
- L54-66 _public method_ `public static DataStoreSegmentId Parse(string text)` — Parses a segment id from the given hex string
- L68-71 _private method_ `private static DataStoreSegmentId FromObjectId(ReadOnlySpan<byte> payload)`
- L79-98 _public method_ `public static bool TryParse(string text, out DataStoreSegmentId objectId)` — Parses a digest from the given hex string
- L104-118 _public method_ `public static DataStoreSegmentId NewId()` — Generates a new object id
- L120 _private property_ `private static uint RunId { get; }`
- L122-126 _private method_ `private static uint CalculateRunId()`
- L132-138 _public method_ `public void CopyTo(Span<byte> span)` — Copies this segment id into a span
- L144-149 _public method_ `public byte[] ToByteArray()` — Converts this object id to a byte array
- L155-158 _public method_ `public Utf8String ToUtf8String()` — Creates an utf8string of the segment id
- L161-164 _public method_ `public override string ToString()` — (inheritdoc)
- L167 _public method_ `public bool Equals(DataStoreSegmentId other)` — (inheritdoc)
- L170 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L173-176 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L181 _public operator_ `public static bool operator ==(DataStoreSegmentId a, DataStoreSegmentId b)` — Test two segment ids for equality
- L186 _public operator_ `public static bool operator !=(DataStoreSegmentId a, DataStoreSegmentId b)` — Test two segment ids for equality
- L191-212 _public method_ `public int Compare(DataStoreSegmentId x, DataStoreSegmentId y)` — Compare two segment ids by comparing their components
- L217-220 _public method_ `public int CompareTo(DataStoreSegmentId other)` — Compare two object ids by comparing their components
- L222-234 _public method_ `public DateTimeOffset AsTimeOffset()`

#### class `Jupiter.DataStore.DataStoreSegmentIdReverseComparer`  
`public sealed class DataStoreSegmentIdReverseComparer : IComparer<DataStoreSegmentId>`  
_public; L240-249_
- inherits: `IComparer<DataStoreSegmentId>`
- desc: A comparer for inverse comparisons of a cb object (newest first)
- L245-248 _public method_ `public int Compare(DataStoreSegmentId x, DataStoreSegmentId y)` — Compare two segment ids returning the newest first

#### class `Jupiter.DataStore.DataStoreSegmentIdJsonConverter`  
`internal sealed class DataStoreSegmentIdJsonConverter : JsonConverter<DataStoreSegmentId>`  
_internal; L254-261_
- inherits: `JsonConverter<DataStoreSegmentId>`
- desc: Type converter for DataStoreSegmentId to and from JSON
- L257 _public method_ `public override DataStoreSegmentId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L260 _public method_ `public override void Write(Utf8JsonWriter writer, DataStoreSegmentId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `Jupiter.DataStore.DataStoreSegmentIdTypeConverter`  
`internal sealed class DataStoreSegmentIdTypeConverter : TypeConverter`  
_internal; L266-272_
- inherits: `TypeConverter`
- desc: Type converter for DataStoreSegmentId
- L268 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)`
- L271 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreTable.cs` (Jupiter)


#### class `Jupiter.DataStore.DataStoreTable`  
`public class DataStoreTable<TObjectType> where TObjectType : struct, IDataStoreTableObject<TObjectType>`  
_public; L13-157_
- constraints: `where TObjectType : struct, IDataStoreTableObject<TObjectType>`
- L15 _private field_ `private readonly IServiceProvider _provider`
- L16 _private field_ `private readonly TableType _typeName`
- L17 _private field_ `private readonly Func<KeyspaceId, TObjectType, Task>? _onObjectWritten`
- L17 _private field_ `private readonly Func< TObjectType`
- L17 _private field_ `private readonly Func< _onObjectWritten`
- L19 _private field_ `private readonly ConcurrentDictionary<KeyspaceId, ConcurrentDictionary<string, DataStoreTablePartition<TObjectType>>> _partitions = ...`
- L19 _private field_ `private readonly ConcurrentDictionary< string`
- L19 _private field_ `private readonly ConcurrentDictionary< _partitions = new ConcurrentDictionary<KeyspaceId, ConcurrentDictionary<string, DataStoreTablePartition<TObjectType>>>()`
- L20 _private field_ `private readonly IDataStoreTableLogService _tableLogService`
- L22-29 _public ctor_ `public DataStoreTable(IServiceProvider provider, TableType typeName, Func<KeyspaceId, TObjectType, Task>? onObjectWritten = null)`
- L31-37 _public method_ `public async Task InsertAsync(KeyspaceId keyspace, string prefix, DataStorePartitionKey key, TObjectType record, bool isFinalized, CancellationToken cancellationToken)`
- L39-43 _public method_ `public async Task EnsureRefreshAsync(KeyspaceId keyspace, string prefix, DataStorePartitionKey key, CancellationToken cancellationToken)`
- L45-50 _public method_ `public async Task<DataStorePartitionValue?> FindAsync(KeyspaceId keyspace, string prefix, DataStorePartitionKey key, CancellationToken cancellationToken)`
- L52-56 _private method_ `private ConcurrentDictionary<string, DataStoreTablePartition<TObjectType>> GetPartitionsForKeyspace(KeyspaceId keyspace)`
- L58-69 _private method_ `private Task<DataStoreTablePartition<TObjectType>> GetPartitionForPrefixAsync(KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L71-90 _public method_ `public IEnumerable<KeyspaceId> GetKeyspacesAsync(CancellationToken cancellationToken)`
- L92-104 _public method_ `public IEnumerable<string> GetPrefixesForNamespaceAsync(KeyspaceId keyspace, CancellationToken cancellationToken)`
- L106-110 _public method_ `public async Task HydratePrefixAsync(KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L112-119 _public method_ `public async IAsyncEnumerable<(DataStorePartitionKey, DataStorePartitionValue)> EnumerateRecordsAsync(KeyspaceId keyspace, string prefix, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L121-125 _public method_ `public async Task DeleteAsync(KeyspaceId keyspace, string prefix, DataStorePartitionKey key, CancellationToken cancellationToken)`
- L127-144 _public method_ `public async Task<long> DropKeyspaceAsync(KeyspaceId keyspace, CancellationToken cancellationToken)`
- L146-150 _public method_ `public async Task<long> DropPrefixAsync(KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L152-156 _public method_ `public async Task RunGarbageCollectionAsync(KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreTableLogService.cs` (Jupiter)


#### interface `Jupiter.DataStore.IDataStoreTableLog`  
`public interface IDataStoreTableLog`  
_public; L14-26_
- L16 _public method_ `public Task InsertAsync(DataStorePartitionKey key, byte[] data, CancellationToken cancellationToken = default)`
- L17 _public method_ `public IAsyncEnumerable<(DataStoreSegmentId, DataStorePartitionKey, byte[])> GetEntriesAsync(DataStoreSegmentId? startSegment = null, CancellationToken cancellationToken = default)`
- L18 _public method_ `public Task FlushAsync(CancellationToken cancellationToken)`
- L19 _public method_ `public Task ReconcileLogEntriesAsync(CancellationToken cancellationToken)`
- L20 _public method_ `public Task DropPartitionAsync(CancellationToken cancellationToken)`
- L21 _public method_ `public Task<bool> RunGarbageCollectionAsync(CancellationToken cancellationToken)`
- L23 _public* property_ `TableType Type { get; }`
- L24 _public* property_ `KeyspaceId Keyspace { get; }`
- L25 _public* property_ `string Prefix { get; }`

#### interface `Jupiter.DataStore.IDataStoreTableLogService`  
`public interface IDataStoreTableLogService`  
_public; L28-32_
- L30 _public method_ `public IDataStoreTableLog GetLogFor(KeyspaceId keyspaceId, TableType type, string prefix)`
- L31 _public method_ `public Task DropKeyspaceAsync(KeyspaceId keyspace, CancellationToken cancellationToken)`

#### class `Jupiter.DataStore.DataStoreTableLogServicePollingState`  
`public class DataStoreTableLogServicePollingState`  
_public; L34-36_

#### class `Jupiter.DataStore.DataStoreTableLogService`  
`public class DataStoreTableLogService : PollingService<DataStoreTableLogServicePollingState>, IDataStoreTableLogService`  
_public; L38-265_
- inherits: `PollingService<DataStoreTableLogServicePollingState>, IDataStoreTableLogService`
- L40 _private field_ `private readonly IServiceProvider _provider`
- L41 _private field_ `private readonly IDataStoreObjectStore _objectStore`
- L42 _private field_ `private readonly IOptionsMonitor<DataStoreSettings> _settings`
- L43 _private field_ `private readonly ILogger<DataStoreTableLogService> _logger`
- L45 _private field_ `private readonly ConcurrentDictionary<string, IDataStoreTableLog> _instances = ...`
- L45 _private field_ `private readonly ConcurrentDictionary< _instances = new ConcurrentDictionary<string, IDataStoreTableLog>()`
- L47-53 _public ctor_ `public DataStoreTableLogService(IServiceProvider provider, IDataStoreObjectStore objectStore, IOptionsMonitor<DataStoreSettings> settings, ILogger<DataStoreTableLogService> logger) : base("DataStoreTableLogService", TimeSpan.FromMinutes(5), new DataStoreTableLogServicePollingState(), logger)`
- L55-58 _public method_ `public IDataStoreTableLog GetLogFor(KeyspaceId keyspaceId, TableType type, string prefix)`
- L60-78 _public method_ `public Task DropKeyspaceAsync(KeyspaceId keyspace, CancellationToken cancellationToken)`
- L80-83 _public method_ `public IEnumerable<IDataStoreTableLog> GetAllLogs()`
- L85-88 _protected method_ `protected override bool ShouldStartPolling()`
- L90-183 _public method_ `public async Task ReconcilePrefixesAsync(CancellationToken cancellationToken)`
- L185-188 _private method_ `private static string GetKey(KeyspaceId keyspace, TableType type, string prefix)`
- L190-204 _protected method_ `protected override async Task OnStartingAsync(DataStoreTableLogServicePollingState state)`
- L206-210 _private method_ `private async Task HydratePrefixAsync(TableType type, KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L212-232 _protected method_ `protected override async Task OnStopping(DataStoreTableLogServicePollingState state)`
- L234-264 _public method_ `public override async Task<bool> OnPollAsync(DataStoreTableLogServicePollingState state, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreTablePartition.cs` (Jupiter)


#### struct `Jupiter.DataStore.DataStorePartitionKey`  
`public readonly struct DataStorePartitionKey : IEquatable<DataStorePartitionKey>`  
_public; L14-58_
- inherits: `IEquatable<DataStorePartitionKey>`
- L16 _private field_ `private static readonly ByteArrayComparer s_comparer = new ByteArrayComparer()`
- L17 _public property_ `public byte[] Bytes { get; }`
- L19-22 _public ctor_ `public DataStorePartitionKey(byte[] key)`
- L24-27 _public ctor_ `public DataStorePartitionKey(ReadOnlyMemory<byte> mem)`
- L29-32 _public method_ `public bool Equals(DataStorePartitionKey other)`
- L34-37 _public method_ `public override bool Equals(object? obj)`
- L39-42 _public method_ `public override int GetHashCode()`
- L44-47 _public method_ `public override string ToString()`
- L49-52 _public operator_ `public static bool operator ==(DataStorePartitionKey left, DataStorePartitionKey right)`
- L54-57 _public operator_ `public static bool operator !=(DataStorePartitionKey left, DataStorePartitionKey right)`

#### record `Jupiter.DataStore.DataStorePartitionValue`  
`public record DataStorePartitionValue`  
_public; L60-120_
- L62-72 _public ctor_ `public DataStorePartitionValue(byte[] bytes, bool isFinalized, byte[]? sortKey = null)`
- L74-77 _public ctor_ `public DataStorePartitionValue(byte[] bytes, bool isFinalized, DateTime creationTime, byte[]? sortKey = null) : this(bytes, isFinalized, sortKey)`
- L79-90 _public method_ `public void AsObject<TObjectType>(out TObjectType record) where TObjectType : struct, IDataStoreTableObject<TObjectType>`
- L92-103 _public method_ `public byte[]? GetRow(byte[] sortKey)`
- L105-111 _public method_ `public byte[] GetFirstRow()`
- L113 _private property_ `private bool HasSingleValue => ...`
- L115 _public property_ `public DateTime CreationTime { get; init; }`
- L116 _private property_ `private SortedList<byte[], byte[]> Values { get; init; }`
- L117 _public property_ `public bool IsFinalized { get; init; }`
- L119 _private field_ `private readonly Lock _valueLock = new Lock()`

#### interface `Jupiter.DataStore.IDataStoreTableObject`  
`public interface IDataStoreTableObject<TObjectType>`  
_public; L122-128_
- L124 _public* method_ `static abstract byte[] Serialize(TObjectType self)`
- L125 _public* method_ `static abstract void Deserialize(byte[] payload, out TObjectType record)`
- L126 _public* method_ `static abstract bool HasSortKey()`
- L127 _public* method_ `static abstract byte[] GetSortKey(TObjectType self)`

#### class `Jupiter.DataStore.DataStoreTablePartition`  
`internal class DataStoreTablePartition<TObjectType> : IDisposable where TObjectType : struct, IDataStoreTableObject<TObjectType>`  
_internal; L130-417_
- inherits: `IDisposable`
- constraints: `where TObjectType : struct, IDataStoreTableObject<TObjectType>`
- L132 _private field_ `private readonly ILogger<DataStoreTablePartition<TObjectType>> _logger`
- L133 _private field_ `private readonly KeyspaceId _keyspaceId`
- L134 _private field_ `private readonly TableType _type`
- L135 _private field_ `private readonly string _prefix`
- L136 _private field_ `private readonly Func<KeyspaceId, TObjectType, Task>? _onObjectWritten`
- L136 _private field_ `private readonly Func< TObjectType`
- L136 _private field_ `private readonly Func< _onObjectWritten`
- L137 _private field_ `private readonly ConcurrentDictionary<DataStorePartitionKey, DataStorePartitionValue> _values = ...`
- L137 _private field_ `private readonly ConcurrentDictionary< _values = new ConcurrentDictionary<DataStorePartitionKey, DataStorePartitionValue>(Environment.ProcessorCount, capacity: 4096)`
- L138 _private field_ `private readonly IDataStoreTableLog _tableLog`
- L139 _private field_ `private DataStoreSegmentId? _lastHydratedSegment`
- L140 _private field_ `private bool _isHydrated`
- L141 _private field_ `private readonly ManualResetEventSlim _hydrationInProgress = new ManualResetEventSlim(false)`
- L143-151 _public ctor_ `public DataStoreTablePartition(IServiceProvider provider, KeyspaceId keyspaceId, TableType type, string prefix, Func<KeyspaceId, TObjectType, Task>? onObjectWritten = null)`
- L153 _public property_ `public bool IsEmpty => ...`
- L155-188 _public method_ `public async Task EnsureHydrationAsync(CancellationToken token)`
- L190-196 _private method_ `private async Task RehydratePartitionAsync(CancellationToken token)`
- L198-224 _private method_ `private async Task HydratePartitionAsync(CancellationToken token)`
- L226-280 _public method_ `public async Task InsertAsync(DataStorePartitionKey key, TObjectType record, bool isFinalized, CancellationToken cancellationToken)`
- L282-319 _private method_ `private async Task RefreshAsync(DataStorePartitionKey key, DataStorePartitionValue partitionValue, bool isFinalized, CancellationToken cancellationToken)`
- L321-330 _private method_ `private static bool ShouldRefresh(DateTime creationTime)`
- L332-339 _public method_ `public async Task EnsureRefreshAsync(DataStorePartitionKey key, CancellationToken cancellationToken)`
- L341-366 _public method_ `public async Task<DataStorePartitionValue?> FindAsync(DataStorePartitionKey key, CancellationToken cancellationToken)`
- L368-375 _public method_ `public async Task DeleteAsync(DataStorePartitionKey key, CancellationToken cancellationToken)`
- L377-380 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken)`
- L382-393 _public method_ `public async IAsyncEnumerable<(DataStorePartitionKey, DataStorePartitionValue)> EnumerateRecordsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L395-401 _public method_ `public async Task<long> DropPartitionAsync(CancellationToken cancellationToken)`
- L403-411 _public method_ `public async Task RunGarbageCollectionAsync(CancellationToken cancellationToken)`
- L413-416 _public method_ `public void Dispose()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/DataStoreTableService.cs` (Jupiter)


#### enum `Jupiter.DataStore.TableType`  
`public enum TableType`  
_public; L17-20_
- L19 _public* enumerator_ `Blob`
- L19 _public* enumerator_ `Ref`
- L19 _public* enumerator_ `Cid`

#### interface `Jupiter.DataStore.IDataStoreTableService`  
`public interface IDataStoreTableService`  
_public; L22-29_
- L24 _public* method_ `DataStoreTable<T> GetTableByType<T>() where T : struct, IDataStoreTableObject<T>`
- L25 _public* method_ `IEnumerable<TableType> GetTableTypes()`
- L27 _public* method_ `Task HydratePrefixAsync(TableType type, KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L28 _public* method_ `Task RunGarbageCollectionAsync(TableType type, KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`

#### class `Jupiter.DataStore.DataStoreTableService`  
`public class DataStoreTableService : IDataStoreTableService`  
_public; L31-166_
- inherits: `IDataStoreTableService`
- L33 _private field_ `private readonly IServiceProvider _provider`
- L34 _private field_ `private readonly ConcurrentDictionary<TableType, object> _tables = ...`
- L34 _private field_ `private readonly ConcurrentDictionary< _tables = new ConcurrentDictionary<TableType, object>()`
- L35 _private field_ `private readonly ConcurrentDictionary<string, TableType> _typeToName = ...`
- L35 _private field_ `private readonly ConcurrentDictionary< _typeToName = new ConcurrentDictionary<string, TableType>()`
- L37 _private field_ `private readonly DataStoreTable<DataStoreBlobRecord> _blobTable`
- L38 _private field_ `private IReferenceResolver? _referenceResolver = null`
- L39 _private field_ `private IBlobService? _blobService = null`
- L41-49 _public ctor_ `public DataStoreTableService(IServiceProvider provider)`
- L51-76 _private method_ `private async Task OnRefWrittenAsync(KeyspaceId keyspace, DataStoreRefRecord record)`
- L78-94 _public method_ `public async Task HydratePrefixAsync(TableType type, KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L96-111 _private method_ `private DataStoreTable<T> AddTableOfType<T>(TableType key, Func<KeyspaceId, T, Task>? onRecordUpdated = null) where T : struct, IDataStoreTableObject<T>`
- L113-117 _private method_ `private Task HydrateTableByTypeAsync<T>(KeyspaceId keyspace, string prefix, CancellationToken cancellationToken) where T : struct, IDataStoreTableObject<T>`
- L119-136 _public method_ `public DataStoreTable<T> GetTableByType<T>() where T : struct, IDataStoreTableObject<T>`
- L138-160 _public method_ `public async Task RunGarbageCollectionAsync(TableType type, KeyspaceId keyspace, string prefix, CancellationToken cancellationToken)`
- L162-165 _public method_ `public IEnumerable<TableType> GetTableTypes()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/FilesystemDataStoreTableLog.cs` (Jupiter)


#### class `Jupiter.DataStore.FilesystemDataStoreTableLog`  
`internal class FilesystemDataStoreTableLog : IDataStoreTableLog, IDisposable`  
_internal; L17-454_
- inherits: `IDataStoreTableLog, IDisposable`
- L19 _private field_ `private readonly IOptionsMonitor<DataStoreSettings> _settings`
- L20 _private field_ `private readonly IOptionsMonitor<GCSettings> _gcSettings`
- L21 _private field_ `private readonly IDataStoreObjectStore _objectStore`
- L22 _private field_ `private readonly ILogger<FilesystemDataStoreTableLog> _logger`
- L23 _private field_ `private readonly KeyspaceId _keyspaceId`
- L24 _private field_ `private readonly TableType _type`
- L25 _private field_ `private readonly string _prefix`
- L26 _private field_ `private readonly ReaderWriterLockSlim _rwLock`
- L29 _private field_ `private DataStoreSegmentId _currentSegmentId`
- L30 _private field_ `private FileStream? _currentLogWriter`
- L32 _internal const_ `internal const int MaxObjectSize = 65536`
- L34-45 _public ctor_ `public FilesystemDataStoreTableLog(IOptionsMonitor<DataStoreSettings> settings, IOptionsMonitor<GCSettings> gcSettings, IDataStoreObjectStore objectStore, ILogger<FilesystemDataStoreTableLog> logger, KeyspaceId keyspaceId, TableType type, string prefix)`
- L47-51 _public method_ `public void Dispose()`
- L53-70 _private method_ `private FileStream GetLogFileStream()`
- L71-99 _public method_ `public Task InsertAsync(DataStorePartitionKey key, byte[] data, CancellationToken cancellationToken = default)`
- L101-111 _private method_ `private static void WriteObjectEntry(Stream s, DataStorePartitionKey key, byte[] data)`
- L142-145 _private method_ `private static string GetRootDir(IOptionsMonitor<DataStoreSettings> settings)`
- L147-150 _private method_ `private DirectoryInfo GetStateDirectory()`
- L152-156 _private method_ `private FileInfo GetFilePath(DataStoreSegmentId segment)`
- L164-226 _public method_ `public async IAsyncEnumerable<(DataStoreSegmentId, DataStorePartitionKey, byte[])> GetEntriesAsync(DataStoreSegmentId? startSegment = null, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L228-255 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken)`
- L257-346 _public method_ `public async Task ReconcileLogEntriesAsync(CancellationToken cancellationToken)`
- L348-360 _public method_ `public async Task DropPartitionAsync(CancellationToken cancellationToken)`
- L362-402 _public method_ `public async Task<bool> RunGarbageCollectionAsync(CancellationToken cancellationToken)`
- L404 _public property_ `public TableType Type => ...`
- L406 _public property_ `public KeyspaceId Keyspace => ...`
- L407 _public property_ `public string Prefix => ...`
- L409-417 _private method_ `private bool IsLocalFileAlive(DateTime lastAccessTimeUtc)`
- L419-432 _public method_ `public static IEnumerable<KeyspaceId> GetKeyspaces(IOptionsMonitor<DataStoreSettings> settings, TableType type)`
- L434-453 _public method_ `public static IEnumerable<(KeyspaceId, string)> EnumeratePrefixes(IOptionsMonitor<DataStoreSettings> settings, TableType type, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/DataStore/KeyspaceId.cs` (Jupiter)


#### struct `Jupiter.DataStore.KeyspaceId`  
`public readonly struct KeyspaceId : IEquatable<KeyspaceId>`  
_public; L9-69_
- inherits: `IEquatable<KeyspaceId>`
- L14 _private property_ `private StringId Text { get; }` — The text representing this id
- L20-23 _public ctor_ `public KeyspaceId(string text) : this(new Utf8String(text))` — Constructor
- L29-32 _public ctor_ `public KeyspaceId(Utf8String text)` — Constructor
- L35 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L38 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L41 _public method_ `public bool Equals(KeyspaceId other)` — (inheritdoc)
- L44 _public method_ `public override string ToString()` — (inheritdoc)
- L47 _public operator_ `public static bool operator ==(KeyspaceId left, KeyspaceId right)` — (inheritdoc)
- L50 _public operator_ `public static bool operator !=(KeyspaceId left, KeyspaceId right)` — (inheritdoc)
- L51-54 _public method_ `public static KeyspaceId FromNamespace(NamespaceId ns)`
- L56-63 _public method_ `public static KeyspaceId FromStoragePool(string storagePool)`
- L65-68 _public method_ `public NamespaceId ToNamespaceId()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/GC/BlobCleanupService.cs` (Jupiter)


#### interface `Jupiter.Implementation.IBlobCleanup`  
`public interface IBlobCleanup`  
_public; L13-17_
- L15 _public* method_ `bool ShouldRun()`
- L16 _public* method_ `Task<ulong> CleanupAsync(CancellationToken none)`

#### class `Jupiter.Implementation.BlobCleanupState`  
`public class BlobCleanupState`  
_public; L19-22_
- L21 _public property_ `public List<IBlobCleanup> BlobCleanups { get; }`

#### class `Jupiter.Implementation.BlobCleanupService`  
`public class BlobCleanupService : PollingService<BlobCleanupState>`  
_public; L24-104_
- inherits: `PollingService<BlobCleanupState>`
- L26 _private field_ `private readonly IOptionsMonitor<GCSettings> _settings`
- L27 _private field_ `private volatile bool _alreadyPolling`
- L28 _private field_ `private readonly ILogger _logger`
- L30-33 _protected method_ `protected override bool ShouldStartPolling()`
- L35-54 _public ctor_ `public BlobCleanupService(IServiceProvider provider, IOptionsMonitor<GCSettings> settings, ILogger<BlobCleanupService> logger) : base(serviceName: nameof(BlobCleanupService), settings.CurrentValue.BlobCleanupPollFrequency, new BlobCleanupState(), logger)`
- L56-59 _public method_ `public void RegisterCleanup(IBlobCleanup cleanup)`
- L61-78 _public method_ `public override async Task<bool> OnPollAsync(BlobCleanupState state, CancellationToken cancellationToken)`
- L80-103 _public method_ `public async Task CleanupAsync(BlobCleanupState state, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/GC/CacheCleanup.cs` (Jupiter)


#### interface `Jupiter.Implementation.IRefCleanup`  
`public interface IRefCleanup`  
_public; L16-19_
- L18 _public* method_ `Task<int> Cleanup(CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.RefLastAccessCleanup`  
`public class RefLastAccessCleanup : IRefCleanup`  
_public; L21-206_
- inherits: `IRefCleanup`
- L23 _private field_ `private readonly IOptionsMonitor<GCSettings> _settings`
- L24 _private field_ `private readonly IReferencesStore _referencesStore`
- L25 _private field_ `private readonly IRefService _objectService`
- L26 _private field_ `private readonly IBlobIndex _blobIndex`
- L27 _private field_ `private readonly IRefService _refService`
- L28 _private field_ `private readonly IReplicationLog _replicationLog`
- L29 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L30 _private field_ `private readonly Tracer _tracer`
- L31 _private field_ `private readonly ILogger _logger`
- L32 _private field_ `private readonly Gauge<long> _cleanupRefsConsidered`
- L33 _private field_ `private readonly IOptionsMonitor<UnrealCloudDDCSettings> _cloudDDCSettings`
- L35-51 _public ctor_ `public RefLastAccessCleanup(IOptionsMonitor<GCSettings> settings, IOptionsMonitor<UnrealCloudDDCSettings> cloudDDCSettings, IReferencesStore referencesStore, IRefService objectService, IBlobIndex blobIndex, IRefService refService, IReplicationLog replicationLog, INamespacePolicyResolver namespacePolicyResolver, Meter meter, Tracer tracer, ILogger<RefLastAccessCleanup> logger)`
- L53-90 _private method_ `private bool ShouldGCNamespace(NamespaceId ns)`
- L92-163 _public method_ `public async Task<int> Cleanup(CancellationToken cancellationToken)`
- L165-205 _private method_ `private async Task<bool> DeleteRefAsync(NamespaceId ns, BucketId bucket, RefId name, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/GC/OrphanBlobCleanupRefs.cs` (Jupiter)


#### class `Jupiter.Implementation.OrphanBlobCleanupRefs`  
`public class OrphanBlobCleanupRefs : IBlobCleanup`  
_public; L17-283_
- inherits: `IBlobCleanup`
- L19 _private field_ `private readonly IOptionsMonitor<GCSettings> _gcSettings`
- L20 _private field_ `private readonly IBlobService _blobService`
- L21 _private field_ `private readonly IRefService _refService`
- L22 _private field_ `private readonly IBlobIndex _blobIndex`
- L23 _private field_ `private readonly IBlockStore _blockStore`
- L24 _private field_ `private readonly ILeaderElection _leaderElection`
- L25 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L26 _private field_ `private readonly Tracer _tracer`
- L27 _private field_ `private readonly ILogger _logger`
- L29 _private field_ `private readonly Counter<long> _consideredBlobCounter`
- L30 _private field_ `private readonly Counter<long> _deletedBlobCounter`
- L33-46 _public ctor_ `public OrphanBlobCleanupRefs(IOptionsMonitor<GCSettings> gcSettings, IBlobService blobService, IRefService refService, IBlobIndex blobIndex, IBlockStore blockStore, ILeaderElection leaderElection, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer, ILogger<OrphanBlobCleanupRefs> logger, Meter meter)`
- L48-56 _public method_ `public bool ShouldRun()`
- L58-121 _public method_ `public async Task<ulong> CleanupAsync(CancellationToken cancellationToken)`
- L123-277 _private method_ `private async Task<bool> GCBlobAsync(string storagePool, List<NamespaceId> namespacesThatSharePool, BlobId blob, DateTime lastModifiedTime, CancellationToken cancellationToken)`
- L279-282 _private method_ `private IAsyncEnumerable<NamespaceId> ListNamespaces()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/GC/RefCleanupService.cs` (Jupiter)


#### class `Jupiter.Implementation.RefCleanupState`  
`public class RefCleanupState`  
_public; L11-20_
- L13-16 _public ctor_ `public RefCleanupState(IRefCleanup refCleanup)`
- L18 _public property_ `public IRefCleanup RefCleanup { get; }`
- L19 _public property_ `public Task? RunningCleanupTask { get; set; }`

#### class `Jupiter.Implementation.RefCleanupService`  
`public class RefCleanupService : PollingService<RefCleanupState>`  
_public; L22-90_
- inherits: `PollingService<RefCleanupState>`
- L24 _private field_ `private readonly IOptionsMonitor<GCSettings> _settings`
- L25 _private field_ `private readonly ILeaderElection _leaderElection`
- L26 _private field_ `private volatile bool _alreadyPolling`
- L27 _private field_ `private readonly ILogger _logger`
- L29-34 _public ctor_ `public RefCleanupService(IOptionsMonitor<GCSettings> settings, IRefCleanup refCleanup, ILeaderElection leaderElection, ILogger<RefCleanupService> logger) : base(serviceName: nameof(RefCleanupService), settings.CurrentValue.RefCleanupPollFrequency, new RefCleanupState(refCleanup), logger, startAtRandomTime: false)`
- L36-39 _protected method_ `protected override bool ShouldStartPolling()`
- L41-75 _public method_ `public override async Task<bool> OnPollAsync(RefCleanupState state, CancellationToken cancellationToken)`
- L77-89 _private method_ `private async Task DoCleanupAsync(RefCleanupState state, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/GC/TempCleanupService.cs` (Jupiter)


#### class `Jupiter.Implementation.TempCleanupService`  
`public class TempCleanupService : PollingService<object>`  
_public; L15-106_
- inherits: `PollingService<object>`
- L17 _private field_ `private readonly IOptionsMonitor<GCSettings> _gcSettings`
- L18 _private field_ `private readonly IOptionsMonitor<BufferedPayloadOptions> _bufferedPayloadOptions`
- L19 _private field_ `private volatile bool _alreadyPolling`
- L20 _private field_ `private readonly ILogger _logger`
- L22-27 _public ctor_ `public TempCleanupService(IOptionsMonitor<GCSettings> gcSettings, IOptionsMonitor<BufferedPayloadOptions> bufferedPayloadOptions, ILogger<TempCleanupService> logger) : base(serviceName: nameof(TempCleanupService), gcSettings.CurrentValue.TempCleanupPollFrequency, new object(), logger)`
- L29-32 _protected method_ `protected override bool ShouldStartPolling()`
- L34-56 _public method_ `public override async Task<bool> OnPollAsync(object state, CancellationToken cancellationToken)`
- L58-93 _private method_ `private void Cleanup(CancellationToken cancellationToken)`
- L95-105 _private method_ `private IEnumerable<FileInfo> GetObjectsOlderThan(DateTime cutoff)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/IRefService.cs` (Jupiter)


#### interface `Jupiter.Implementation.IRefService`  
`public interface IRefService`  
_public; L12-29_
- L14 _public* method_ `Task<(RefRecord, BlobContents?)> GetAsync(NamespaceId ns, BucketId bucket, RefId key, string[]? fields = null, bool consistentRead = false, bool doLastAccessTracking = true, CancellationToken cancellationToken = default)`
- L16 _public* method_ `Task<(ContentId[], BlobId[])> PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, CbObject payload, Action<BlobId>? onBlobFound = null, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L17 _public* method_ `Task<(ContentId[], BlobId[])> FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, Action<BlobId>? onBlobFound = null, CancellationToken cancellationToken = default)`
- L19 _public* method_ `IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken = default)`
- L20 _public* method_ `IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L22 _public* method_ `Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L23 _public* method_ `Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L24 _public* method_ `Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`
- L26 _public* method_ `Task<bool> ExistsAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L27 _public* method_ `Task<List<BlobId>> GetReferencedBlobsAsync(NamespaceId ns, BucketId bucket, RefId key, bool ignoreMissingBlobs, CancellationToken cancellationToken = default)`
- L28 _public* method_ `Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.ObjectHashMismatchException`  
`public class ObjectHashMismatchException : Exception`  
_public; L31-36_
- inherits: `Exception`
- L33-35 _public ctor_ `public ObjectHashMismatchException(NamespaceId ns, BucketId bucket, RefId name, BlobId suppliedHash, BlobId actualHash) : base($"Object {name} in bucket {bucket} and namespace {ns} did not reference hash {suppliedHash} was referencing {actualHash}")`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/IReferenceResolver.cs` (Jupiter)


#### class `Jupiter.Implementation.Attachment`  
`public abstract class Attachment`  
_public; L19-22_
- L21 _public method_ `public abstract IoHash AsIoHash()`

#### class `Jupiter.Implementation.BlobAttachment`  
`public class BlobAttachment : Attachment`  
_public; L24-37_
- inherits: `Attachment`
- L26 _public property_ `public BlobId Identifier { get; }`
- L28-31 _public ctor_ `public BlobAttachment(BlobId blobIdentifier)`
- L33-36 _public method_ `public override IoHash AsIoHash()`

#### class `Jupiter.Implementation.ObjectAttachment`  
`public class ObjectAttachment : Attachment`  
_public; L39-52_
- inherits: `Attachment`
- L41 _public property_ `public BlobId Identifier { get; }`
- L43-46 _public ctor_ `public ObjectAttachment(BlobId blobIdentifier)`
- L48-51 _public method_ `public override IoHash AsIoHash()`

#### class `Jupiter.Implementation.ContentIdAttachment`  
`public class ContentIdAttachment : Attachment`  
_public; L54-69_
- inherits: `Attachment`
- L56 _public property_ `public ContentId Identifier { get; }`
- L57 _public property_ `public BlobId[] ReferencedBlobs { get; }`
- L59-63 _public ctor_ `public ContentIdAttachment(ContentId contentId, BlobId[] referencedBlobs)`
- L65-68 _public method_ `public override IoHash AsIoHash()`

#### interface `Jupiter.Implementation.IReferenceResolver`  
`public interface IReferenceResolver`  
_public; L71-103_
- L83 _public* method_ `IAsyncEnumerable<BlobId> GetReferencedBlobsAsync(NamespaceId ns, CbObject cb, bool ignoreMissingBlobs = false, CancellationToken cancellationToken = default)` — Returns the blobs referenced from the cb object and any children These blobs are guaranteed to exist, if any blob is missing PartialReferenceResolveException or ReferenceIsMissingBlobsException are raised
- L93 _public* method_ `IAsyncEnumerable<Attachment> GetAttachmentsAsync(NamespaceId ns, CbObject cb, CancellationToken cancellationToken)` — Returns which attachments exist in the cb object or any children These attachments are not guaranteed to reference blobs that actually exist
- L102 _public* method_ `Task<BlobId[]?> ResolveIdAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken)` — Resolve a blob id that might or might not be a content id into the blob it would reference

#### class `Jupiter.Implementation.ReferenceResolver`  
`public class ReferenceResolver : IReferenceResolver`  
_public; L105-519_
- inherits: `IReferenceResolver`
- L107 _private field_ `private readonly IBlobService _blobStore`
- L108 _private field_ `private readonly IContentIdStore _contentIdStore`
- L109 _private field_ `private readonly IOptionsMonitor<ReferenceResolverSettings> _settings`
- L110 _private field_ `private readonly Tracer _tracer`
- L112-118 _public ctor_ `public ReferenceResolver(IBlobService blobStore, IContentIdStore contentIdStore, IOptionsMonitor<ReferenceResolverSettings> settings, Tracer tracer)`
- L120-136 _public method_ `public async IAsyncEnumerable<Attachment> GetAttachmentsAsync(NamespaceId ns, CbObject cb, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L138-150 _public method_ `public async Task<BlobId[]?> ResolveIdAsync(NamespaceId ns, BlobId blobId, CancellationToken cancellationToken)`
- L152-238 _private method_ `private async IAsyncEnumerable<Attachment> GetAttachmentsV2Async(NamespaceId ns, CbObject cb, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L240-337 _private method_ `private async IAsyncEnumerable<Attachment> GetAttachmentsOldAsync(NamespaceId ns, CbObject cb, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L339-364 _private method_ `private static async Task ProcessCompactBinaryAttachmentsAsync(List<Task<CbObject>> pendingCompactBinaryAttachments, Queue<CbObject> objectsToVisit, List<BlobId> unresolvedBlobReferences)`
- L366-411 _private method_ `private static async Task ProcessContentIdsAsync(List<Attachment> list, List<Task<(ContentId, BlobId[]?)>> pendingContentIdResolves, List<BlobId> unresolvedBlobReferences)`
- L413-478 _public method_ `public async IAsyncEnumerable<BlobId> GetReferencedBlobsAsync(NamespaceId ns, CbObject cb, bool ignoreMissingBlobs = false, [EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L480-495 _private method_ `private async Task<(ContentIdAttachment, bool)> CheckContentIdExistsAsync(NamespaceId ns, ContentIdAttachment contentIdAttachment, CancellationToken cancellationToken)`
- L497-504 _private method_ `private async Task<CbObject> ParseCompactBinaryAttachmentAsync(NamespaceId ns, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L506-513 _private method_ `private async Task<(ContentId, BlobId[]?)> ResolveContentIdAsync(NamespaceId ns, ContentId contentId, CancellationToken cancellationToken)`
- L515-518 _private method_ `private async Task<(BlobId, bool)> CheckBlobExistsAsync(NamespaceId ns, BlobId blob, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.ReferenceResolverSettings`  
`public class ReferenceResolverSettings`  
_public; L521-525_
- L523 _public property_ `public bool UseV2ReferenceResolving { get; set; }`
- L524 _public property_ `public int ChunkSize { get; set; }`

#### class `Jupiter.Implementation.PartialReferenceResolveException`  
`public class PartialReferenceResolveException : Exception`  
_public; L527-535_
- inherits: `Exception`
- L529 _public property_ `public List<ContentId> UnresolvedReferences { get; }`
- L531-534 _public ctor_ `public PartialReferenceResolveException(List<ContentId> unresolvedReferences) : base($"References missing: {string.Join(',', unresolvedReferences)}")`

#### class `Jupiter.Implementation.ReferenceIsMissingBlobsException`  
`public class ReferenceIsMissingBlobsException : Exception`  
_public; L537-545_
- inherits: `Exception`
- L539 _public property_ `public List<BlobId> MissingBlobs { get; }`
- L541-544 _public ctor_ `public ReferenceIsMissingBlobsException(List<BlobId> missingBlobs) : base($"References is missing these blobs: {string.Join(',', missingBlobs)}")`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/LastAccess/LastAccessServiceReferences.cs` (Jupiter)


#### class `Jupiter.Implementation.LastAccessServiceReferences`  
`public class LastAccessServiceReferences : IHostedService, IDisposable`  
_public; L16-127_
- inherits: `IHostedService, IDisposable`
- L18 _private field_ `private readonly ILastAccessCache<LastAccessRecord> _lastAccessCacheRecord`
- L19 _private field_ `private readonly IReferencesStore _referencesStore`
- L20 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L21 _private field_ `private readonly Tracer _tracer`
- L22 _private field_ `private readonly ILogger _logger`
- L23 _private field_ `private Timer? _timer`
- L24 _private field_ `private readonly UnrealCloudDDCSettings _settings`
- L26 _public property_ `public bool Running { get; set; }`
- L28-36 _public ctor_ `public LastAccessServiceReferences(IOptionsMonitor<UnrealCloudDDCSettings> settings, ILastAccessCache<LastAccessRecord> lastAccessCache, IReferencesStore referencesStore, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer, ILogger<LastAccessServiceReferences> logger)`
- L38-47 _public method_ `public Task StartAsync(CancellationToken cancellationToken)`
- L49-58 _public method_ `public async Task StopAsync(CancellationToken cancellationToken)`
- L60-77 _private method_ `private void OnUpdate(object? state)`
- L79-100 _internal method_ `internal async Task<List<(LastAccessRecord, DateTime)>> ProcessLastAccessRecordsAsync(CancellationToken cancellationToken)`
- L102-111 _private method_ `private bool ShouldTrackLastAccess(NamespaceId ns)`
- L113-117 _public method_ `public void Dispose()`
- L119-126 _protected method_ `protected virtual void Dispose(bool disposing)`

#### class `Jupiter.Implementation.LastAccessBackgroundService`  
`public class LastAccessBackgroundService : BackgroundService`  
_public; L130-206_
- inherits: `BackgroundService`
- L132 _private field_ `private readonly ILastAccessCache<LastAccessRecord> _lastAccessCacheRecord`
- L133 _private field_ `private readonly IReferencesStore _referencesStore`
- L134 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L135 _private field_ `private readonly Tracer _tracer`
- L136 _private field_ `private readonly ILogger _logger`
- L137 _private field_ `private readonly UnrealCloudDDCSettings _settings`
- L139-147 _public ctor_ `public LastAccessBackgroundService(IOptionsMonitor<UnrealCloudDDCSettings> settings, ILastAccessCache<LastAccessRecord> lastAccessCache, IReferencesStore referencesStore, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer, ILogger<LastAccessServiceReferences> logger)`
- L149-171 _protected method_ `protected override async Task ExecuteAsync(CancellationToken stoppingToken)`
- L173-194 _private method_ `private async Task<List<(LastAccessRecord, DateTime)>> ProcessLastAccessRecordsAsync(CancellationToken cancellationToken)`
- L196-205 _private method_ `private bool ShouldTrackLastAccess(NamespaceId ns)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/LastAccess/LastAccessTracker.cs` (Jupiter)


#### class `Jupiter.Implementation.LastAccessRecord`  
`public class LastAccessRecord`  
_public; L16-28_
- L18-23 _public ctor_ `public LastAccessRecord(NamespaceId ns, BucketId bucket, RefId key)`
- L25 _public property_ `public NamespaceId Namespace { get; set; }`
- L26 _public property_ `public BucketId Bucket { get; set; }`
- L27 _public property_ `public RefId Key { get; set; }`

#### class `Jupiter.Implementation.LastAccessTrackerReference`  
`public class LastAccessTrackerReference : LastAccessTracker<LastAccessRecord>`  
_public; L30-40_
- inherits: `LastAccessTracker<LastAccessRecord>`
- L32-34 _public ctor_ `public LastAccessTrackerReference(IOptionsMonitor<UnrealCloudDDCSettings> settings, Tracer tracer, ILogger<LastAccessTrackerReference> logger) : base(settings, tracer, logger)`
- L36-39 _protected method_ `protected override string BuildCacheKey(LastAccessRecord record)`

#### class `Jupiter.Implementation.LastAccessTracker`  
`public abstract class LastAccessTracker<T> : ILastAccessTracker<T>, ILastAccessCache<T>`  
_public; L42-129_
- inherits: `ILastAccessTracker<T>, ILastAccessCache<T>`
- L44 _private field_ `private readonly IOptionsMonitor<UnrealCloudDDCSettings> _settings`
- L45 _private field_ `private readonly Tracer _tracer`
- L46 _private field_ `private readonly ILogger _logger`
- L48 _private field_ `private ConcurrentDictionary<string, LastAccessRecord> _cache = ...`
- L48 _private field_ `private ConcurrentDictionary< _cache = new ConcurrentDictionary<string, LastAccessRecord>()`
- L51 _private field_ `private readonly ReaderWriterLock _rwLock = new ReaderWriterLock()`
- L53-58 _protected ctor_ `protected LastAccessTracker(IOptionsMonitor<UnrealCloudDDCSettings> settings, Tracer tracer, ILogger logger)`
- L60 _protected method_ `protected abstract string BuildCacheKey(T record)`
- L62-91 _public method_ `public Task TrackUsed(T record)`
- L93-116 _public method_ `public async Task<List<(T, DateTime)>> GetLastAccessedRecords()`

#### class `Jupiter.Implementation.LastAccessTracker.LastAccessRecord`  
`private class LastAccessRecord`  
_private; L118-128_
- L120 _public property_ `public T Record { get; }`
- L121 _public property_ `public DateTime LastAccessTime { get; set; }`
- L123-127 _public ctor_ `public LastAccessRecord(T record, in DateTime lastAccessTime)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/LeaderElection/ILeaderElection.cs` (Jupiter)


#### class `Jupiter.Implementation.OnLeaderChangedEventArgs`  
`public class OnLeaderChangedEventArgs`  
_public; L7-17_
- L9 _public property_ `public bool IsLeader { get; }`
- L10 _public property_ `public string LeaderName { get; }`
- L12-16 _public ctor_ `public OnLeaderChangedEventArgs(bool isLeader, string leaderName)`

#### interface `Jupiter.Implementation.ILeaderElection`  
`public interface ILeaderElection`  
_public; L19-24_
- L21 _public* method_ `bool IsThisInstanceLeader()`
- L23 _public* event_ `event EventHandler<OnLeaderChangedEventArgs>? OnLeaderChanged`

#### class `Jupiter.Implementation.LeaderElectionStub`  
`public class LeaderElectionStub : ILeaderElection`  
_public; L26-43_
- inherits: `ILeaderElection`
- L28 _private field_ `private readonly bool _isLeader`
- L30-35 _public ctor_ `public LeaderElectionStub(bool isLeader)`
- L37-40 _public method_ `public bool IsThisInstanceLeader()`
- L42 _public event_ `public event EventHandler<OnLeaderChangedEventArgs>? OnLeaderChanged`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/LeaderElection/KubernetesLeaderElection.cs` (Jupiter)


#### class `Jupiter.Implementation.LeaderElection.KubernetesLeaderElectionSettings`  
`public class KubernetesLeaderElectionSettings`  
_public; L17-31_
- L20 _public property_ `public TimeSpan LeaseDuration { get; set; }`
- L21 _public property_ `public TimeSpan RetryPeriod { get; set; }`
- L22 _public property_ `public TimeSpan RenewDeadline { get; set; }`
- L24 _public property_ `public string ConfigMapName { get; set; }`
- L27 _public property_ `public string Namespace { get; set; }` — attrs: `[Required]`
- L28 _public property_ `public string PodName { get; set; }` — attrs: `[Required]`
- L30 _public property_ `public string PeerPodLabelSelector { get; set; }`

#### class `Jupiter.Implementation.LeaderElection.KubernetesLeaderElectionState`  
`public class KubernetesLeaderElectionState`  
_public; L33-36_

#### class `Jupiter.Implementation.LeaderElection.KubernetesLeaderElection`  
`public class KubernetesLeaderElection : PollingService<KubernetesLeaderElectionState>, ILeaderElection`  
_public; L38-120_
- inherits: `PollingService<KubernetesLeaderElectionState>, ILeaderElection`
- L40 _private field_ `private readonly ILogger _logger`
- L42 _private field_ `private readonly Kubernetes _client`
- L43 _private field_ `private readonly LeaderElector _leaderElector`
- L44 _private field_ `private readonly ConfigMapLock _configMapLock`
- L45 _private field_ `private readonly string _identity`
- L47-71 _public ctor_ `public KubernetesLeaderElection(IOptionsMonitor<KubernetesLeaderElectionSettings> leaderSettings, ILogger<KubernetesLeaderElection> logger) : base("Kubernetes Leader Election", TimeSpan.FromSeconds(1), new KubernetesLeaderElectionState(), logger, startAtRandomTime: true)`
- L73-79 _private method_ `private void OnLeaderElectorNewLeader(string leaderName)`
- L81-84 _public method_ `public bool IsThisInstanceLeader()`
- L86 _public event_ `public event EventHandler<OnLeaderChangedEventArgs>? OnLeaderChanged`
- L88-94 _protected method_ `protected override Task OnStopping(KubernetesLeaderElectionState state)`
- L96-119 _public method_ `public override async Task<bool> OnPollAsync(KubernetesLeaderElectionState state, CancellationToken cancellationToken)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/MetricsService.cs` (Jupiter)


#### class `Jupiter.Implementation.MetricsState`  
`public class MetricsState`  
_public; L17-20_
- L19 _public property_ `public Task? CalculateMetricsTask { get; set; }`

#### class `Jupiter.Implementation.MetricsServiceSettings`  
`public class MetricsServiceSettings`  
_public; L22-30_
- L27 _public property_ `public bool Enabled { get; set; }` — Set to enable calculation of metrics in the background. Adds load to database so only enable these if you intend to use it.
- L29 _public property_ `public TimeSpan PollFrequency { get; set; }`

#### class `Jupiter.Implementation.MetricsService`  
`public class MetricsService : PollingService<MetricsState>`  
_public; L32-109_
- inherits: `PollingService<MetricsState>`
- L34 _private field_ `private readonly IOptionsMonitor<MetricsServiceSettings> _settings`
- L35 _private field_ `private readonly IReferencesStore _referencesStore`
- L36 _private field_ `private volatile bool _alreadyPolling`
- L38 _private field_ `private readonly ILogger _logger`
- L39 _private field_ `private readonly IServiceProvider _provider`
- L41-47 _public ctor_ `public MetricsService(IOptionsMonitor<MetricsServiceSettings> settings, IReferencesStore referencesStore, ILogger<MetricsService> logger, IServiceProvider provider) : base(serviceName: nameof(MetricsService), settings.CurrentValue.PollFrequency, new MetricsState(), logger, startAtRandomTime: false)`
- L49-52 _protected method_ `protected override bool ShouldStartPolling()`
- L54-82 _public method_ `public override async Task<bool> OnPollAsync(MetricsState state, CancellationToken cancellationToken)`
- L84-108 _private method_ `private async Task DoCalculateMetricsAsync(MetricsState _, CancellationToken cancellationToken)`

#### class `Jupiter.Implementation.MetricsCalculator`  
`public class MetricsCalculator`  
_public; L111-159_
- L113 _private field_ `private readonly IBlobIndex _blobIndex`
- L115 _private field_ `private readonly ILogger _logger`
- L116 _private field_ `private readonly Tracer _tracer`
- L117 _private field_ `private readonly Gauge<double> _blobSizeAvgGauge`
- L118 _private field_ `private readonly Gauge<long> _blobSizeMinGauge`
- L119 _private field_ `private readonly Gauge<long> _blobSizeMaxGauge`
- L120 _private field_ `private readonly Gauge<long> _refsInBucketGauge`
- L121 _private field_ `private readonly Gauge<long> _blobSizeCountGauge`
- L122 _private field_ `private readonly Gauge<long> _blobSizeTotalGauge`
- L124-136 _public ctor_ `public MetricsCalculator(IBlobIndex blobIndex, Meter meter, ILogger<MetricsService> logger, Tracer tracer)`
- L138-158 _public method_ `public async Task<BucketStats?> CalculateStatsForBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/MongoStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MongoStore`  
`public class MongoStore`  
_public; L12-84_
- L14 _private field_ `private readonly string? _overrideDatabaseName`
- L15 _private field_ `private readonly MongoClient _client`
- L17-29 _public ctor_ `public MongoStore(IOptionsMonitor<MongoSettings> settings, string? overrideDatabaseName = null)`
- L31-55 _protected method_ `protected async Task CreateCollectionIfNotExistsAsync<T>()`
- L57-66 _private method_ `private string GetCollectionName<T>()`
- L68-71 _protected method_ `protected IMongoIndexManager<T> AddIndexFor<T>()`
- L73-78 _protected method_ `protected IMongoCollection<T> GetCollection<T>()`
- L80-83 _internal method_ `internal string GetDatabaseName()`

#### class `Jupiter.Implementation.MongoCollectionNameAttribute`  
`public sealed class MongoCollectionNameAttribute : Attribute`  
_public; L87-95_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- L89 _public property_ `public string CollectionName { get; }`
- L91-94 _public ctor_ `public MongoCollectionNameAttribute(string collectionName)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/NginxRedirectHelper.cs` (Jupiter)


#### class `Jupiter.Implementation.NginxRedirectHelper`  
`public class NginxRedirectHelper`  
_public; L12-60_
- L14 _private field_ `private readonly IOptionsMonitor<NginxSettings> _nginxSettings`
- L16-19 _public ctor_ `public NginxRedirectHelper(IOptionsMonitor<NginxSettings> nginxSettings)`
- L21-32 _public method_ `public IActionResult CreateActionResult(BlobContents blobContents, string contentType)`
- L34-59 _public method_ `public bool CanRedirect(HttpRequest request, BlobContents blobContents)`

#### class `Jupiter.Implementation.NginxSettings`  
`public class NginxSettings`  
_public; L62-67_
- L64 _public property_ `public bool UseNginxRedirect { get; set; }`
- L65 _public property_ `public string NginxRootPath { get; set; }`
- L66 _public property_ `public string RequiredNginxHeader { get; set; }`

#### class `Jupiter.Implementation.NginxRedirectOkResult`  
`public class NginxRedirectOkResult : OkResult`  
_public; L69-88_
- inherits: `OkResult`
- L71 _private field_ `private readonly string _nginxRedirectPath`
- L72 _private field_ `private readonly string _contentType`
- L74-78 _public ctor_ `public NginxRedirectOkResult(string nginxRedirectPath, string contentType)`
- L80-87 _public method_ `public override Task ExecuteResultAsync(ActionContext context)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/CacheReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.CacheReferencesStore`  
`public class CacheReferencesStore : IReferencesStore`  
_public; L22-143_
- inherits: `IReferencesStore`
- L24 _private field_ `private readonly MongoReferencesStore _mongoReferenceStore`
- L25 _private field_ `private readonly UpstreamReferenceStore _upstreamReferenceStore`
- L27-33 _public ctor_ `public CacheReferencesStore(IServiceProvider provider)`
- L35-51 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L53-59 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L61-67 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L69-87 _public method_ `public async Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L89-95 _public method_ `public async Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken)`
- L97-101 _public method_ `public Task CleanupTrackedStateAsync()`
- L103-106 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync(CancellationToken cancellationToken)`
- L108-111 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync(CancellationToken cancellationToken)`
- L113-116 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken)`
- L118-121 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L123-126 _public method_ `public Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L128-132 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L134-137 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L139-142 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`

#### class `Jupiter.Implementation.UpstreamReferenceStore`  
`class UpstreamReferenceStore : RelayStore, IReferencesStore`  
_internal*; L145-290_
- inherits: `RelayStore, IReferencesStore`
- L147-149 _public ctor_ `public UpstreamReferenceStore(IOptionsMonitor<UpstreamRelaySettings> settings, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials) : base(settings, httpClientFactory, serviceCredentials)`
- L151-169 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L171-193 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L195-224 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L226-237 _public method_ `public async Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L239-243 _public method_ `public async Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken)`
- L245-249 _public method_ `public Task CleanupTrackedStateAsync()`
- L251-254 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync(CancellationToken cancellationToken)`
- L256-259 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync(CancellationToken cancellationToken)`
- L261-264 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken)`
- L266-269 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L271-274 _public method_ `public Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L276-279 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L281-284 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L286-289 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/DataStoreReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.DataStoreReferencesStore`  
`public class DataStoreReferencesStore : IReferencesStore`  
_public; L16-160_
- inherits: `IReferencesStore`
- L18 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L19 _private field_ `private readonly DataStoreTable<DataStoreRefRecord> _refTable`
- L21-25 _public ctor_ `public DataStoreReferencesStore(IDataStoreTableService tableService, INamespacePolicyResolver namespacePolicyResolver)`
- L27-37 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken = default)`
- L39-60 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L62-73 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L75-79 _public method_ `public Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L81-85 _public method_ `public Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken = default)`
- L87-101 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L103-117 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)`
- L119-122 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken = default)`
- L124-127 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L129-134 _public method_ `public async Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L136-139 _public method_ `public async Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L141-144 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`
- L146-149 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L151-154 _public method_ `public Task CleanupTrackedStateAsync()`
- L156-159 _private method_ `private static KeyspaceId GetKeyspace(NamespaceId ns)`

#### record struct `Jupiter.Implementation.DataStoreRefRecord`  
`internal record struct DataStoreRefRecord : IDataStoreTableObject<DataStoreRefRecord>`  
_internal; L162-231_
- inherits: `IDataStoreTableObject<DataStoreRefRecord>`
- L164 _public property_ `public IoHash BlobHash { get; set; }`
- L166 _public property_ `public byte[] Blob { get; set; }`
- L168-172 _public ctor_ `public DataStoreRefRecord(BlobId blobHash, byte[] blob)`
- L174-177 _public method_ `public static DataStorePartitionKey GetPartitionKey(RefId refId)`
- L179-186 _public method_ `public static DataStorePartitionKey? MaybeGetPartitionKey(RefId? refId)`
- L188-197 _public method_ `public RefRecord ToRefRecord(NamespaceId ns, BucketId bucket, RefId key, bool isFinalized, IReferencesStore.FieldFlags fieldFlags = IReferencesStore.FieldFlags.All)`
- L199-209 _public method_ `public static byte[] Serialize(DataStoreRefRecord self)`
- L211-220 _public method_ `public static void Deserialize(byte[] payload, out DataStoreRefRecord record)`
- L222-225 _public method_ `public static bool HasSortKey()`
- L227-230 _public method_ `public static byte[] GetSortKey(DataStoreRefRecord self)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/GalileoReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.GalileoReferencesStore`  
`public class GalileoReferencesStore : IReferencesStore`  
_public; L16-141_
- inherits: `IReferencesStore`
- desc: Temporary storage layer for coordinating data between scylla and data store
- L18 _private field_ `private readonly ILogger<GalileoReferencesStore> _logger`
- L19 _private field_ `private readonly ScyllaReferencesStore _scyllaReferenceStore`
- L20 _private field_ `private readonly DataStoreReferencesStore _datastoreReferenceStore`
- L22-27 _public ctor_ `public GalileoReferencesStore(IServiceProvider provider, ILogger<GalileoReferencesStore> logger)`
- L29-51 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken = default)`
- L53-68 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L70-85 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L87-90 _public method_ `public Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L92-95 _public method_ `public Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken = default)`
- L97-100 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync(CancellationToken cancellationToken = default)`
- L102-105 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync(CancellationToken cancellationToken = default)`
- L107-110 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken = default)`
- L112-115 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L117-120 _public method_ `public Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L122-125 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L127-130 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`
- L132-135 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L137-140 _public method_ `public Task CleanupTrackedStateAsync()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/ILastAccessTracker.cs` (Jupiter)


#### interface `Jupiter.Implementation.ILastAccessTracker`  
`public interface ILastAccessTracker<T>`  
_public; L9-12_
- L11 _public* method_ `Task TrackUsed(T record)`

#### interface `Jupiter.Implementation.ILastAccessCache`  
`public interface ILastAccessCache<T>`  
_public; L14-17_
- L16 _public* method_ `Task<List<(T, DateTime)>> GetLastAccessedRecords()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/IReferencesStore.cs` (Jupiter)


#### interface `Jupiter.Implementation.IReferencesStore`  
`public interface IReferencesStore`  
_public; L11-46_
- L13 _public* method_ `Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, FieldFlags fieldFlags, OperationFlags opFlags, CancellationToken cancellationToken = default)`
- L30 _public* method_ `Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L31 _public* method_ `Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken = default)`
- L33 _public* method_ `Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L34 _public* method_ `Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken = default)`
- L35 _public* method_ `IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync(CancellationToken cancellationToken = default)`
- L37 _public* method_ `IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync(CancellationToken cancellationToken = default)`
- L39 _public* method_ `IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken = default)`
- L40 _public* method_ `IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L41 _public* method_ `Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken = default)`
- L42 _public* method_ `Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L43 _public* method_ `Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken = default)`
- L44 _public* method_ `Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L45 _public* method_ `Task CleanupTrackedStateAsync()`

#### enum `Jupiter.Implementation.IReferencesStore.FieldFlags`  
`public enum FieldFlags`  
_public; L16-21_
- attrs: `[Flags]`
- L18 _public* enumerator_ `None = 0`
- L19 _public* enumerator_ `IncludePayload = 1`
- L20 _public* enumerator_ `All = IncludePayload`

#### enum `Jupiter.Implementation.IReferencesStore.OperationFlags`  
`public enum OperationFlags`  
_public; L24-28_
- attrs: `[Flags]`
- L26 _public* enumerator_ `None = 0`
- L27 _public* enumerator_ `BypassCache = 1`

#### class `Jupiter.Implementation.RefRecord`  
`public class RefRecord`  
_public; L48-68_
- L50-59 _public ctor_ `public RefRecord(NamespaceId ns, BucketId bucket, RefId name, DateTime lastAccess, byte[]? inlinePayload, BlobId blobIdentifier, bool isFinalized)`
- L61 _public property_ `public NamespaceId Namespace { get; }`
- L62 _public property_ `public BucketId Bucket { get; }`
- L63 _public property_ `public RefId Name { get; }`
- L64 _public property_ `public DateTime LastAccess { get; }`
- L65 _public property_ `public byte[]? InlinePayload { get; set; }`
- L66 _public property_ `public BlobId BlobIdentifier { get; set; }`
- L67 _public property_ `public bool IsFinalized { get; }`

#### class `Jupiter.Implementation.RefNotFoundException`  
`public class RefNotFoundException : Exception`  
_public; L70-82_
- inherits: `Exception`
- L72-77 _public ctor_ `public RefNotFoundException(NamespaceId ns, BucketId bucket, RefId key) : base($"Object not found {key} in bucket {bucket} namespace {ns}")`
- L79 _public property_ `public NamespaceId Namespace { get; }`
- L80 _public property_ `public BucketId Bucket { get; }`
- L81 _public property_ `public RefId Key { get; }`

#### class `Jupiter.Implementation.RefAlreadyExistsException`  
`public class RefAlreadyExistsException : Exception`  
_public; L84-99_
- inherits: `Exception`
- L86-92 _public ctor_ `public RefAlreadyExistsException(NamespaceId ns, BucketId bucket, RefId key, RefRecord oldObject) : base($"Object already found {key} in bucket {bucket} namespace {ns}")`
- L94 _public property_ `public RefRecord OldObject { get; set; }`
- L96 _public property_ `public NamespaceId Namespace { get; }`
- L97 _public property_ `public BucketId Bucket { get; }`
- L98 _public property_ `public RefId Key { get; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/MemoryCachedReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.Objects.MemoryCachedReferencesStore`  
`public class MemoryCachedReferencesStore : IReferencesStore`  
_public; L15-176_
- inherits: `IReferencesStore`
- L17 _private field_ `private readonly IReferencesStore _actualStore`
- L18 _private field_ `private readonly ConcurrentDictionary<NamespaceId, MemoryCache> _referenceCaches = ...`
- L18 _private field_ `private readonly ConcurrentDictionary< _referenceCaches = new ConcurrentDictionary<NamespaceId, MemoryCache>()`
- L19 _private field_ `private readonly IOptionsMonitor<MemoryCacheReferencesSettings> _options`
- L20 _private field_ `private readonly Tracer _tracer`
- L22-27 _public ctor_ `public MemoryCachedReferencesStore(IReferencesStore actualStore, IOptionsMonitor<MemoryCacheReferencesSettings> options, Tracer tracer)`
- L29-43 _private method_ `private void AddCacheEntry(NamespaceId ns, BucketId bucket, RefId key, RefRecord record)`
- L45-48 _private method_ `private MemoryCache GetCacheForNamespace(NamespaceId ns)`
- L50-80 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L82-88 _public method_ `public Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L90-94 _public method_ `public Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L96-99 _public method_ `public Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L101-109 _private method_ `private void FinalizeCacheEntry(NamespaceId ns, BucketId bucket, RefId key)`
- L111-114 _public method_ `public Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken)`
- L116-119 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync(CancellationToken cancellationToken)`
- L121-124 _public method_ `public IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync(CancellationToken cancellationToken)`
- L126-129 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken)`
- L131-134 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L136-141 _public method_ `public Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L143-147 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L149-155 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L157-160 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L162-165 _public method_ `public void Clear()`
- L167-170 _public method_ `public Task CleanupTrackedStateAsync()`
- L172-175 _public method_ `public IReferencesStore GetUnderlyingStore()`

#### class `Jupiter.Implementation.Objects.CachedReferenceKey`  
`class CachedReferenceKey : IEquatable<CachedReferenceKey>`  
_internal*; L178-228_
- inherits: `IEquatable<CachedReferenceKey>`
- L180 _private field_ `private readonly BucketId _bucket`
- L181 _private field_ `private readonly RefId _key`
- L183-187 _public ctor_ `public CachedReferenceKey(BucketId bucket, RefId key)`
- L189-202 _public method_ `public bool Equals(CachedReferenceKey? other)`
- L204-222 _public method_ `public override bool Equals(object? obj)`
- L224-227 _public method_ `public override int GetHashCode()`

#### class `Jupiter.Implementation.Objects.CachedReferenceEntry`  
`class CachedReferenceEntry`  
_internal*; L230-260_
- L232-235 _private method_ `private int GetSize()`
- L237-246 _public ctor_ `public CachedReferenceEntry(RefRecord record)`
- L248 _public property_ `public NamespaceId Namespace { get; }`
- L249 _public property_ `public BucketId Bucket { get; }`
- L250 _public property_ `public RefId Name { get; }`
- L251 _public property_ `public byte[]? Blob { get; }`
- L252 _public property_ `public BlobId BlobIdentifier { get; }`
- L253 _public property_ `public int Size { get; }`
- L254 _public property_ `public bool IsFinalized { get; set; }`
- L256-259 _public method_ `public RefRecord ToRefRecord(IReferencesStore.FieldFlags fieldFlags)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/MemoryReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryReferencesStore`  
`public class MemoryReferencesStore : IReferencesStore`  
_public; L14-218_
- inherits: `IReferencesStore`
- L16 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L17 _private field_ `private readonly ConcurrentDictionary<string, MemoryStoreObject> _objects = ...`
- L17 _private field_ `private readonly ConcurrentDictionary< _objects = new ConcurrentDictionary<string, MemoryStoreObject>()`
- L18 _private field_ `private readonly HashSet<NamespaceId> _namespaces = new HashSet<NamespaceId>()`
- L20-23 _public ctor_ `public MemoryReferencesStore(INamespacePolicyResolver namespacePolicyResolver)`
- L25-33 _public method_ `public Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L35-66 _public method_ `public Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L68-77 _public method_ `public Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L79-88 _public method_ `public Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L90-99 _public method_ `public Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime lastAccessTime, CancellationToken cancellationToken)`
- L101-108 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L110-117 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L119-122 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken)`
- L124-137 _public method_ `public async IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L139-147 _public method_ `public Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L149-176 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L178-200 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L202-206 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L208-212 _public method_ `public Task CleanupTrackedStateAsync()`
- L214-217 _private method_ `private static string BuildKey(NamespaceId ns, BucketId bucket, RefId name)`

#### class `Jupiter.Implementation.MemoryStoreObject`  
`public class MemoryStoreObject`  
_public; L220-256_
- L222-231 _public ctor_ `public MemoryStoreObject(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[] blob, bool isFinalized)`
- L233 _public property_ `public NamespaceId Namespace { get; }`
- L234 _public property_ `public BucketId Bucket { get; }`
- L235 _public property_ `public RefId Name { get; }`
- L236 _public property_ `public byte[] Blob { get; }`
- L237 _public property_ `public BlobId BlobHash { get; }`
- L239 _public property_ `public DateTime LastAccessTime { get; set; }`
- L240 _public property_ `public bool IsFinalized { get; set; }`
- L242-245 _public method_ `public void FinalizeObject()`
- L246-249 _public method_ `public void SetLastAccessTime(DateTime lastAccessTime)`
- L251-255 _public method_ `public RefRecord ToRefRecord(IReferencesStore.FieldFlags fieldFlags)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/MongoReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.MongoReferencesStore`  
`public class MongoReferencesStore : MongoStore, IReferencesStore`  
_public; L15-281_
- inherits: `MongoStore, IReferencesStore`
- L17 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L19-49 _public ctor_ `public MongoReferencesStore(IOptionsMonitor<MongoSettings> settings, INamespacePolicyResolver namespacePolicyResolver, string? overrideDatabaseName = null) : base(settings, overrideDatabaseName)`
- L51-69 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId key, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L71-113 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, byte[]? blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L115-124 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L126-133 _public method_ `public async Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L135-144 _public method_ `public async Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime newLastAccessTime, CancellationToken cancellationToken)`
- L146-158 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L160-166 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L168-178 _public method_ `public async Task AddNamespaceIfNotExistAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L180-192 _public method_ `public async IAsyncEnumerable<NamespaceId> GetNamespacesAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L194-213 _public method_ `public async IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L215-224 _public method_ `public async Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L226-243 _public method_ `public async Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L245-259 _public method_ `public async Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L261-264 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`
- L266-274 _public method_ `public void SetLastAccessTTLDuration(TimeSpan duration)`
- L276-280 _public method_ `public Task CleanupTrackedStateAsync()`

#### class `Jupiter.Implementation.MongoReferencesModelV0`  
`public class MongoReferencesModelV0`  
_public; L287-337_
- attrs: `[BsonDiscriminator("ref.v0")] [BsonIgnoreExtraElements] [MongoCollectionName("References")]`
- L290-299 _public ctor_ `public MongoReferencesModelV0(string ns, string bucket, string key, string blobIdentifier, byte[] inlineBlob, bool isFinalized, DateTime lastAccessTime)` — attrs: `[BsonConstructor]`
- L301-310 _public ctor_ `public MongoReferencesModelV0(NamespaceId ns, BucketId bucket, RefId key, BlobId blobIdentifier, byte[]? blob, bool isFinalized, DateTime lastAccessTime)`
- L313 _public property_ `public string Ns { get; set; }` — attrs: `[BsonRequired]`
- L316 _public property_ `public string Bucket { get; set; }` — attrs: `[BsonRequired]`
- L319 _public property_ `public string Key { get; set; }` — attrs: `[BsonRequired]`
- L321 _public property_ `public string BlobIdentifier { get; set; }`
- L323 _public property_ `public bool IsFinalized { get; set; }`
- L326 _public property_ `public DateTime LastAccessTime { get; set; }` — attrs: `[BsonRequired]`
- L328 _public property_ `public byte[]? InlineBlob { get; set; }`
- L329 _public property_ `public DateTime ExpireAt { get; set; }`
- L331-336 _public method_ `public RefRecord ToRefRecord()`

#### class `Jupiter.Implementation.MongoNamespacesModelV0`  
`public class MongoNamespacesModelV0`  
_public; L342-357_
- attrs: `[MongoCollectionName("Namespaces")] [BsonDiscriminator("namespace.v0")] [BsonIgnoreExtraElements]`
- L345 _public property_ `public string Ns { get; set; }` — attrs: `[BsonRequired]`
- L348-351 _public ctor_ `public MongoNamespacesModelV0(string ns)` — attrs: `[BsonConstructor]`
- L353-356 _public ctor_ `public MongoNamespacesModelV0(NamespaceId ns)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/ScyllaReferencesStore.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaReferencesStore`  
`public class ScyllaReferencesStore : IReferencesStore`  
_public; L20-837_
- inherits: `IReferencesStore`
- L22 _private field_ `private readonly ISession _session`
- L23 _private field_ `private readonly IMapper _mapper`
- L24 _private field_ `private readonly IScyllaSessionManager _scyllaSessionManager`
- L25 _private field_ `private readonly IOptionsMonitor<ScyllaSettings> _settings`
- L26 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L27 _private field_ `private readonly Tracer _tracer`
- L28 _private field_ `private readonly ILogger _logger`
- L29 _private field_ `private readonly PreparedStatement _getObjectsStatement`
- L30 _private field_ `private readonly PreparedStatement _getObjectsLastAccessStatement`
- L31 _private field_ `private readonly PreparedStatement _getNamespacesStatement`
- L32 _private field_ `private readonly PreparedStatement _getNamespacesOldStatement`
- L33 _private field_ `private readonly PreparedStatement _getObjectsForPartitionRangeStatement`
- L34 _private field_ `private readonly PreparedStatement _getObjectsBucketsStatement`
- L35 _private field_ `private readonly PreparedStatement _getObjectsLastAccessForPartitionRangeStatement`
- L37 _private field_ `private readonly ConcurrentDictionary<NamespaceId, ConcurrentDictionary<BucketId, DateTime>> _addedBuckets = ...`
- L37 _private field_ `private readonly ConcurrentDictionary< BucketId`
- L37 _private field_ `private readonly ConcurrentDictionary< _addedBuckets = new ConcurrentDictionary<NamespaceId, ConcurrentDictionary<BucketId, DateTime>>()`
- L39-98 _public ctor_ `public ScyllaReferencesStore(IScyllaSessionManager scyllaSessionManager, IOptionsMonitor<ScyllaSettings> settings, INamespacePolicyResolver namespacePolicyResolver, Tracer tracer, ILogger<ScyllaReferencesStore> logger)`
- L100-149 _public method_ `public async Task<RefRecord> GetAsync(NamespaceId ns, BucketId bucket, RefId name, IReferencesStore.FieldFlags fieldFlags, IReferencesStore.OperationFlags opFlags, CancellationToken cancellationToken)`
- L151-218 _public method_ `public async Task PutAsync(NamespaceId ns, BucketId bucket, RefId name, BlobId blobHash, byte[] blob, bool isFinalized, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L220-247 _public method_ `public async Task FinalizeAsync(NamespaceId ns, BucketId bucket, RefId name, BlobId blobIdentifier, CancellationToken cancellationToken)`
- L249-262 _public method_ `public async Task<DateTime?> GetLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L264-284 _public method_ `public async Task UpdateLastAccessTimeAsync(NamespaceId ns, BucketId bucket, RefId name, DateTime lastAccessTime, CancellationToken cancellationToken)`
- L286-362 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L364-436 _public method_ `public async IAsyncEnumerable<(NamespaceId, BucketId, RefId)> GetRecordsWithoutAccessTimeAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L443-532 _private method_ `private async IAsyncEnumerable<(NamespaceId, BucketId, RefId, DateTime)> GetRecordsPerShardAsync(bool? forceUseLastAccessTable = null)` — This implements a more efficient scanning where we fetch objects based on which shard it is in. It scans the entire database and thus returns all namespaces. See https://www.scylladb.com/2017/03/28/parallel-efficient-full-table-scan-scylla/
- L534-614 _public method_ `public async IAsyncEnumerable<NamespaceId> GetNamespacesAsync([EnumeratorCancellation] CancellationToken cancellationToken)`
- L616-638 _public method_ `public async IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L640-658 _public method_ `public async Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L660-688 _public method_ `public async Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L690-715 _public method_ `public async Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L717-733 _public method_ `public async Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId key, uint ttl, CancellationToken cancellationToken = default)`
- L735-760 _private method_ `private async Task AddBucketAsync(NamespaceId ns, BucketId bucket)`
- L762-836 _public method_ `public async Task CleanupTrackedStateAsync()`

#### class `Jupiter.Implementation.ScyllaBlobIdentifier`  
`public class ScyllaBlobIdentifier`  
_public; L839-857_
- L841-844 _public ctor_ `public ScyllaBlobIdentifier()`
- L846-849 _public ctor_ `public ScyllaBlobIdentifier(ContentHash hash)`
- L851 _public property_ `public byte[]? Hash { get; set; }`
- L853-856 _public method_ `public BlobId AsBlobIdentifier()`

#### class `Jupiter.Implementation.ScyllaObjectReference`  
`public class ScyllaObjectReference`  
_public; L859-881_
- L862-866 _public ctor_ `public ScyllaObjectReference()`
- L868-872 _public ctor_ `public ScyllaObjectReference(BucketId bucket, RefId key)`
- L874 _public property_ `public string Bucket { get; set; }`
- L875 _public property_ `public string Key { get; set; }`
- L877-880 _public method_ `public (BucketId, RefId) AsTuple()`

#### class `Jupiter.Implementation.ScyllaObject`  
`public class ScyllaObject`  
_public; L884-953_
- attrs: `[Cassandra.Mapping.Attributes.Table("objects")]`
- L886-889 _public ctor_ `public ScyllaObject()`
- L891-902 _public ctor_ `public ScyllaObject(NamespaceId ns, BucketId bucket, RefId name, byte[] payload, BlobId payloadHash, bool isFinalized)`
- L905 _public property_ `public string? Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(0)]`
- L908 _public property_ `public string? Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(1)]`
- L911 _public property_ `public string? Name { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(2)]`
- L914 _public property_ `public ScyllaBlobIdentifier? PayloadHash { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("payload_hash")]`
- L917 _public property_ `public byte[]? InlinePayload { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("inline_payload")]`
- L920 _public property_ `public bool? IsFinalized { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("is_finalized")]`
- L922 _public property_ `public DateTime LastAccessTime { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("last_access_time")]`
- L924-952 _public method_ `public bool IsRequiredFieldIsMissing()`

#### class `Jupiter.Implementation.ScyllaBucket`  
`public class ScyllaBucket`  
_public; L956-973_
- attrs: `[Cassandra.Mapping.Attributes.Table("buckets_v2")]`
- L958-960 _public ctor_ `public ScyllaBucket()`
- L962-966 _public ctor_ `public ScyllaBucket(NamespaceId ns, BucketId bucket)`
- L969 _public property_ `public string? Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L972 _public property_ `public string? Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey]`

#### class `Jupiter.Implementation.ScyllaObjectLastAccess`  
`public class ScyllaObjectLastAccess`  
_public; L976-1003_
- attrs: `[Cassandra.Mapping.Attributes.Table("object_last_access_v2")]`
- L978-981 _public ctor_ `public ScyllaObjectLastAccess()`
- L983-990 _public ctor_ `public ScyllaObjectLastAccess(NamespaceId ns, BucketId bucket, RefId name, DateTime lastAccessTime)`
- L993 _public property_ `public string? Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(0)]`
- L996 _public property_ `public string? Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(1)]`
- L999 _public property_ `public string? Name { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey(2)]`
- L1002 _public property_ `public DateTime LastAccessTime { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("last_access_time")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Objects/ScyllaSettings.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaSettings`  
`public class ScyllaSettings : IValidatableObject`  
_public; L10-150_
- inherits: `IValidatableObject`
- L12 _public property_ `public string ConnectionString { get; set; }`
- L13 _public property_ `public int MaxSnapshotsPerNamespace { get; set; }`
- L21 _public property_ `public Dictionary<string, string>? KeyspaceReplicationStrategy { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]` — Set to override the replication strategy used to create keyspace Note that this only applies when creating the keyspace To modify a existing keyspace see https://docs.datastax.com/en/dse/6.7/dse-admin/datastax_enterprise/operations/opsChangeKSStrategy.html
- L29 _public property_ `public Dictionary<string, string>? LocalKeyspaceReplicationStrategy { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]` — Set to override the replication strategy used to create the local keyspace Note that this only applies when creating the keyspace To modify a existing keyspace see https://docs.datastax.com/en/dse/6.7/dse-admin/datastax_enterprise/operations/opsChangeKSStrategy.html
- L35 _public property_ `public string LocalDatacenterName { get; set; }` — attrs: `[Required]` — Used to configure the load balancing policy to stick to this specified datacenter
- L38 _public property_ `public string LocalKeyspaceSuffix { get; set; }` — attrs: `[Required]`
- L44 _public property_ `public int MaxConnectionForLocalHost { get; set; }` — Max number of connections opened, so the max amount of scylla nodes connected to. See https://docs.datastax.com/en/developer/nodejs-driver/4.6/features/connection-pooling/
- L49 _public property_ `public int MaxRequestsPerConnection { get; set; }` — Fixed maximum amount of requests in flight for a connection before a new connection is used (thus max requests per node)
- L54 _public property_ `public TimeSpan ReplicationLogTimeToLive { get; set; }` — The time for a replication log event to live in the incremental state before being deleted, assumption is that the snapshot will have processed the event within this time
- L59 _public property_ `public bool UseAzureCosmosDB { get; set; }` — Whether a Cosmos DB Cassandra layer from Azure should be used.
- L64 _public property_ `public bool UseAWSKeyspace { get; set; }` — Whether a AWS Keyspace is used, adjusts requests to be compatible with this flavor of Cassandra.
- L69 _public property_ `public bool UseSSL { get; set; }` — Set to false to disable use of SSL, this is only used when connecting to a CosmosDB instance or a AWS Keyspace instance
- L74 _public property_ `public bool ListObjectsFromLastAccessTable { get; set; }` — Toggle to enable reading objects from the object_last_access_time_v2 table
- L79 _public property_ `public bool UpdateLegacyLastAccessField { get; set; }` — Set to update the last access field in the object table, this is legacy and causes extra compaction work on the database
- L85 _public property_ `public int ReadTimeout { get; set; }` — Read timeout in milliseconds Set to -1 to get the default timeout, set to 0 to disable timeouts
- L90 _public property_ `public bool UsePerShardScanning { get; set; }` — Enable to scan database per shard, this requires setting more information about your cluster
- L96 _public property_ `public uint CountOfCoresPerNode { get; set; }` — attrs: `[Range(1, 128)]` — Count of cores each nodes has, only used when UsePerShardScanning is set
- L102 _public property_ `public uint CountOfNodes { get; set; }` — attrs: `[Range(1, 64)]` — Count of nodes in the DC, only used when UsePerShardScanning is set
- L107 _public property_ `public bool MigrateFromOldBlobIndex { get; set; }` — Enable to migrate data from blob_index table to blob_index_v2 table
- L112 _public property_ `public bool ListObjectsFromOldNamespaceTable { get; set; }` — Enable to use list namespaces from the old table, this can set for a period while migration from old to new table happens
- L117 _public property_ `public bool AvoidSchemaChanges { get; set; }` — Set to disable any modifications to cassandra schema from Unreal Cloud DDC
- L122 _public property_ `public bool AllowParallelRecordFetch { get; set; }` — Runs the record fetching in parallel (up to CountOfNodes) - experimental change that only applies when UsePerShardScanning is active
- L127 _public property_ `public bool CleanupOldTrackedState { get; set; }` — Can be used to disable the cleanup of unused namespaces and buckets
- L132 _public property_ `public ConsistencyLevel DefaultConsistencyLevel { get; set; }` — Used to override the consistency level for requests
- L137 _public property_ `public bool UseConsistentContentIdResolve { get; set; }` — When enabled uses a more consistent read level for content ids which solves intermittent issues as the cost of worse performance
- L139-149 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/PeerStatusService.cs` (Jupiter)


#### class `Jupiter.Implementation.PeerStatus`  
`public class PeerStatus`  
_public; L16-26_
- L18-21 _public ctor_ `public PeerStatus(PeerSettings peerSettings)`
- L23 _public property_ `public List<PeerEndpoints> Endpoints { get; }`
- L24 _public property_ `public int Latency { get; set; }`
- L25 _public property_ `public bool Reachable { get; set; }`

#### interface `Jupiter.Implementation.IPeerStatusService`  
`public interface IPeerStatusService`  
_public; L28-49_
- L34 _public* method_ `IEnumerable<string> GetRegions()` — Lists all known regions
- L41 _public* method_ `PeerStatus? GetPeerStatus(string regionName)` — Returns all the information about a particular region
- L48 _public* method_ `List<(int, string)> GetPeersByLatency(IEnumerable<string> peerNames)` — Returns possible peers sorted by latency to them

#### class `Jupiter.Implementation.PeerStatusServiceState`  
`public class PeerStatusServiceState`  
_public; L51-53_

#### class `Jupiter.Implementation.PeerStatusService`  
`public class PeerStatusService : PollingService<PeerStatusServiceState>, IPeerStatusService`  
_public; L55-203_
- inherits: `PollingService<PeerStatusServiceState>, IPeerStatusService`
- L57 _private field_ `private readonly IOptionsMonitor<ClusterSettings> _clusterSettings`
- L58 _private field_ `private readonly IOptionsMonitor<JupiterSettings> _jupiterSettings`
- L59 _private field_ `private readonly IHttpClientFactory _clientFactory`
- L60 _private field_ `private readonly Dictionary<string, PeerStatus> _peers = ...`
- L60 _private field_ `private readonly Dictionary< _peers = new Dictionary<string, PeerStatus>(StringComparer.InvariantCultureIgnoreCase)`
- L61 _private field_ `private volatile bool _alreadyPolling = false`
- L62 _private field_ `private readonly ILogger _logger`
- L64-67 _public method_ `public IEnumerable<string> GetRegions()`
- L69-77 _public method_ `public PeerStatus? GetPeerStatus(string regionName)`
- L79-101 _public method_ `public List<(int, string)> GetPeersByLatency(IEnumerable<string> peerNames)`
- L103-123 _public ctor_ `public PeerStatusService(IOptionsMonitor<ClusterSettings> clusterSettings, IOptionsMonitor<JupiterSettings> jupiterSettings, IHttpClientFactory clientFactory, ILogger<PeerStatusService> logger) : base("PeerStatus", TimeSpan.FromMinutes(15), new PeerStatusServiceState(), logger)`
- L125-136 _public method_ `public override async Task<bool> OnPollAsync(PeerStatusServiceState state, CancellationToken cancellationToken)`
- L138-167 _public method_ `public async Task UpdatePeerStatusAsync(CancellationToken cancellationToken)`
- L169-202 _private method_ `private async Task<int> MeasureLatencyAsync(PeerEndpoints endpoint)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/RefService.cs` (Jupiter)


#### class `Jupiter.Implementation.ObjectService`  
`public class ObjectService : IRefService`  
_public; L21-358_
- inherits: `IRefService`
- L23 _private field_ `private readonly IHttpContextAccessor _httpContextAccessor`
- L24 _private field_ `private readonly IReferencesStore _referencesStore`
- L25 _private field_ `private readonly IBlobService _blobService`
- L26 _private field_ `private readonly IReferenceResolver _referenceResolver`
- L27 _private field_ `private readonly IReplicationLog _replicationLog`
- L28 _private field_ `private readonly IBlobIndex _blobIndex`
- L29 _private field_ `private readonly INamespacePolicyResolver _namespacePolicyResolver`
- L30 _private field_ `private readonly ILastAccessTracker<LastAccessRecord> _lastAccessTracker`
- L31 _private field_ `private readonly Tracer _tracer`
- L32 _private field_ `private readonly ILogger _logger`
- L33 _private field_ `private readonly IOptionsMonitor<UnrealCloudDDCSettings> _cloudDDCSettings`
- L35-48 _public ctor_ `public ObjectService(IHttpContextAccessor httpContextAccessor, IReferencesStore referencesStore, IBlobService blobService, IReferenceResolver referenceResolver, IReplicationLog replicationLog, IBlobIndex blobIndex, INamespacePolicyResolver namespacePolicyResolver, ILastAccessTracker<LastAccessRecord> lastAccessTracker, Tracer tracer, ILogger<ObjectService> logger, IOptionsMonitor<UnrealCloudDDCSettings> cloudDDCSettings)`
- L50-118 _public method_ `public async Task<(RefRecord, BlobContents?)> GetAsync(NamespaceId ns, BucketId bucket, RefId key, string[]? fields = null, bool consistentRead = false, bool doLastAccessTracking = true, CancellationToken cancellationToken = default)`
- L120-162 _public method_ `public async Task<(ContentId[], BlobId[])> PutAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, CbObject payload, Action<BlobId>? onBlobFound = null, bool allowOverwrite = false, CancellationToken cancellationToken = default)`
- L164-193 _private method_ `private bool HasAttachments(CbObject payload)`
- L195-213 _public method_ `public async Task<(ContentId[], BlobId[])> FinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, Action<BlobId>? onBlobFound = null, CancellationToken cancellationToken = default)`
- L215-275 _private method_ `private async Task<(ContentId[], BlobId[])> DoFinalizeAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blobHash, CbObject payload, Action<BlobId>? onBlobFound = null, CancellationToken cancellationToken = default)`
- L277-280 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync(CancellationToken cancellationToken)`
- L282-285 _public method_ `public IAsyncEnumerable<BucketId> GetBucketsAsync(NamespaceId ns, CancellationToken cancellationToken = default)`
- L287-292 _public method_ `public async Task<bool> DeleteAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L294-297 _public method_ `public Task<long> DropNamespaceAsync(NamespaceId ns, CancellationToken cancellationToken)`
- L299-302 _public method_ `public Task<long> DeleteBucketAsync(NamespaceId ns, BucketId bucket, CancellationToken cancellationToken)`
- L304-332 _public method_ `public async Task<bool> ExistsAsync(NamespaceId ns, BucketId bucket, RefId key, CancellationToken cancellationToken)`
- L334-352 _public method_ `public async Task<List<BlobId>> GetReferencedBlobsAsync(NamespaceId ns, BucketId bucket, RefId name, bool ignoreMissingBlobs = false, CancellationToken cancellationToken = default)`
- L354-357 _public method_ `public Task UpdateTTL(NamespaceId ns, BucketId bucket, RefId refId, uint ttl, CancellationToken cancellationToken = default)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/RelayStore.cs` (Jupiter)


#### class `Jupiter.Implementation.RelayStore`  
`public abstract class RelayStore`  
_public; L10-38_
- L12 _private field_ `private readonly IOptionsMonitor<UpstreamRelaySettings> _settings`
- L13 _private field_ `private readonly IServiceCredentials _serviceCredentials`
- L14 _private field_ `private readonly HttpClient _httpClient`
- L16 _protected property_ `protected HttpClient HttpClient => ...`
- L18-25 _protected ctor_ `protected RelayStore(IOptionsMonitor<UpstreamRelaySettings> settings, IHttpClientFactory httpClientFactory, IServiceCredentials serviceCredentials)`
- L27-37 _protected method_ `protected async Task<HttpRequestMessage> BuildHttpRequestAsync(HttpMethod method, Uri uri)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/BlobsReplicator.cs` (Jupiter)


#### class `Jupiter.Implementation.BlobsReplicator`  
`public class BlobsReplicator : IReplicator`  
_public; L25-921_
- inherits: `IReplicator`
- L27 _private field_ `private readonly string _name`
- L28 _private field_ `private readonly ILogger _logger`
- L29 _private field_ `private readonly ManualResetEvent _replicationFinishedEvent = new ManualResetEvent(true)`
- L30 _private field_ `private readonly ReplicatorSettings _replicatorSettings`
- L31 _private field_ `private readonly IBlobService _blobService`
- L32 _private field_ `private readonly IReplicationLog _replicationLog`
- L33 _private field_ `private readonly IServiceCredentials _serviceCredentials`
- L34 _private field_ `private readonly Tracer _tracer`
- L35 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L36 _private field_ `private readonly HttpClient _httpClient`
- L37 _private field_ `private readonly NamespaceId _namespace`
- L38 _private field_ `private BlobsState _replicationState`
- L39 _private field_ `private bool _replicationRunning`
- L40 _private field_ `private CancellationTokenSource _replicationTokenSource = new CancellationTokenSource()`
- L41 _private field_ `private bool _disposed = false`
- L43 _private field_ `private static Histogram<long>? s_replicatedCounter`
- L44 _private field_ `private static Histogram<long>? s_replicationBehindCounter`
- L45 _private field_ `private static Counter<long>? s_replicationAttempts`
- L47 _private field_ `private static readonly JsonSerializerOptions DefaultSerializerSettings = ConfigureJsonOptions()`
- L48-111 _public ctor_ `public BlobsReplicator(ReplicatorSettings replicatorSettings, ClusterSettings clusterSettings, IBlobService blobService, IHttpClientFactory httpClientFactory, IReplicationLog replicationLog, IServiceCredentials serviceCredentials, Tracer tracer, BufferedPayloadFactory bufferedPayloadFactory,ILogger<BlobsReplicator> logger, Meter meter)`
- L113-118 _private method_ `private static JsonSerializerOptions ConfigureJsonOptions()`
- L120-124 _public method_ `public void Dispose()`
- L126-143 _protected method_ `protected virtual void Dispose(bool disposing)`
- L155-170 _private method_ `private async Task<bool> SaveStateAsync(BlobsState newState, BlobsState? expectedOldState = null)` — Updates the state of the current replicator using the provided new state. If an expected old state is provided, then ensures that the existing state matches prior to saving the new state. This allows the admin endpoints to rewind or fast-forward the replicator's state without worrying about being overwritten. If an existing state does not exist at all, then the new state will be inserted regardless of the provided expected old state.
- L172-249 _public method_ `public async Task<bool> TriggerNewReplicationsAsync()`
- L251-254 _private method_ `private void LogReplicationHeartbeat()`
- L256-266 _private method_ `private async Task<HttpRequestMessage> BuildHttpRequestAsync(HttpMethod httpMethod, Uri uri)`
- L268-366 _private method_ `private async Task<int> ReplicateIncrementallyAsync(NamespaceId ns, string lastBucket, CancellationToken replicationToken)`
- L368-475 _private method_ `private async IAsyncEnumerable<BlobReplicationLogEvent> GetBlobEventsAsync(NamespaceId ns, string refBucket, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L477-496 _private method_ `private static IEnumerable<string> GetRefBuckets(string bucket, CancellationToken cancellationToken)`
- L498-516 _private method_ `private async Task<bool> ReplicateBlobAsync(NamespaceId ns, BlobId blob, BucketId? bucketHint, CancellationToken cancellationToken)`
- L518-701 _private method_ `private async Task<bool> ReplicateMultipartBlobAsync(NamespaceId ns, BlobId blob, BucketId? bucketHint, CancellationToken cancellationToken)`
- L703-786 _private method_ `private async Task<IBufferedPayload?> ReplicateMultipartBlobRangeHttpAsync(NamespaceId ns, BlobId blob, MultipartByteRange range, CancellationToken cancellationToken)`
- L788-875 _private method_ `private async Task<bool> ReplicateBlobHttpAsync(NamespaceId ns, BlobId blob, BucketId? bucketHint, CancellationToken cancellationToken)`
- L877-880 _private method_ `private async Task AddToBlobReplicationLogAsync(NamespaceId ns, BlobId blob, BucketId? bucketHint)`
- L882-893 _public method_ `public void SetReplicationOffset(long? state)`
- L895-904 _public method_ `public async Task StopReplicatingAsync()`
- L906 _public property_ `public ReplicatorState State => ...`
- L908 _public property_ `public ReplicatorInfo Info { get; set; }`
- L910-914 _public method_ `public Task DeleteStateAsync()`
- L916-920 _public method_ `public void SetRefState(string lastBucket)`

#### class `Jupiter.Implementation.ToOldTimeBucketException`  
`public class ToOldTimeBucketException : Exception`  
_public; L923-931_
- inherits: `Exception`
- L925 _public property_ `public string TimeBucket { get; }`
- L927-930 _public ctor_ `public ToOldTimeBucketException(string timeBucket)`

#### class `Jupiter.Implementation.BlobsState`  
`public class BlobsState : ReplicatorState`  
_public; L933-943_
- inherits: `ReplicatorState`
- L935-942 _public ctor_ `public BlobsState()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/IReplicator.cs` (Jupiter)


#### class `Jupiter.Implementation.ReplicatorState`  
`public class ReplicatorState`  
_public; L9-15_
- L11 _public property_ `public long? ReplicatorOffset { get; set; }`
- L12 _public property_ `public Guid? ReplicatingGeneration { get; set; }`
- L13 _public property_ `public string? LastBucket { get; set; }`
- L14 _public property_ `public Guid? LastEvent { get; set; }`

#### class `Jupiter.Implementation.ReplicatorInfo`  
`public class ReplicatorInfo`  
_public; L16-34_
- L18-26 _public ctor_ `public ReplicatorInfo(string replicatorName, NamespaceId namespaceToReplicate, ReplicatorState state)`
- L28 _public property_ `public string ReplicatorName { get; }`
- L29 _public property_ `public NamespaceId NamespaceToReplicate { get; }`
- L30 _public property_ `public ReplicatorState State { get; }`
- L32 _public property_ `public DateTime LastRun { get; set; }`
- L33 _public property_ `public int CountOfRunningReplications { get; set; }`

#### interface `Jupiter.Implementation.IReplicator`  
`public interface IReplicator : IDisposable`  
_public; L36-62_
- inherits: `IDisposable`
- L42 _public* method_ `Task<bool> TriggerNewReplicationsAsync()` — Attempt to run a new replication, if a replication is already in flight for this replicator this will early exist.
- L47 _public* method_ `void SetReplicationOffset(long? state)` — Forcefully set the replication offset to a new value, should only be used to recover a replicator stuck in a bad state
- L49 _public* method_ `Task StopReplicatingAsync()`
- L51-54 _public property_ `public ReplicatorState State { get; }`
- L56-59 _public property_ `public ReplicatorInfo Info { get; }`
- L61 _public* method_ `Task DeleteStateAsync()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/MemoryCachedReplicationLog.cs` (Jupiter)


#### class `Jupiter.Implementation.Replication.MemoryCachedReplicationLog`  
`public class MemoryCachedReplicationLog : IReplicationLog`  
_public; L15-139_
- inherits: `IReplicationLog`
- L17 _private field_ `private readonly IReplicationLog _inner`
- L18 _private field_ `private readonly IOptionsMonitor<MemoryCacheReplicationLogSettings> _options`
- L19 _private field_ `private readonly Tracer _tracer`
- L21 _private field_ `private readonly ConcurrentDictionary<NamespaceId, MemoryCache> _replicationLogCache = ...`
- L21 _private field_ `private readonly ConcurrentDictionary< _replicationLogCache = new ConcurrentDictionary<NamespaceId, MemoryCache>()`
- L22-27 _public ctor_ `public MemoryCachedReplicationLog(IReplicationLog inner, IOptionsMonitor<MemoryCacheReplicationLogSettings> options, Tracer tracer)`
- L29-41 _private method_ `private void AddCacheEntry(NamespaceId ns, string timeBucket, List<BlobReplicationLogEvent> logEvents)`
- L43-46 _private method_ `private MemoryCache GetCacheForNamespace(NamespaceId ns)`
- L48-51 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync()`
- L53-56 _public method_ `public Task<(string, Guid)> InsertAddEventAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId objectBlob, DateTime? timeBucket = null)`
- L58-61 _public method_ `public Task<(string, Guid)> InsertDeleteEventAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime? timeBucket = null)`
- L63-67 _public method_ `public IAsyncEnumerable<ReplicationLogEvent> GetAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent)`
- L69-72 _public method_ `public Task AddSnapshotAsync(SnapshotInfo snapshotHeader)`
- L74-77 _public method_ `public Task<SnapshotInfo?> GetLatestSnapshotAsync(NamespaceId ns)`
- L79-82 _public method_ `public IAsyncEnumerable<SnapshotInfo> GetSnapshotsAsync(NamespaceId ns)`
- L84-87 _public method_ `public Task UpdateReplicatorStateAsync(NamespaceId ns, string replicatorName, ReplicatorState newState)`
- L89-92 _public method_ `public Task<ReplicatorState?> GetReplicatorStateAsync(NamespaceId ns, string replicatorName)`
- L94-97 _public method_ `public Task<(string, Guid)> InsertAddBlobEventAsync(NamespaceId ns, BlobId objectBlob, DateTime? timeBucket = null, BucketId? bucketHint = null)`
- L99-133 _public method_ `public async IAsyncEnumerable<BlobReplicationLogEvent> GetBlobEventsAsync(NamespaceId ns, string replicationBucket)`
- L135-138 _public method_ `public IReplicationLog GetUnderlyingContentIdStore()`

#### class `Jupiter.Implementation.Replication.MemoryCacheReplicationLogSettings`  
`public class MemoryCacheReplicationLogSettings : MemoryCacheOptions`  
_public; L141-147_
- inherits: `MemoryCacheOptions`
- L143 _public property_ `public bool Enabled { get; set; }`
- L145 _public property_ `public bool EnableSlidingExpiry { get; set; }`
- L146 _public property_ `public int SlidingExpirationMinutes { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/RefsReplicator.cs` (Jupiter)


#### class `Jupiter.Implementation.RefsReplicator`  
`public class RefsReplicator : IReplicator`  
_public; L27-776_
- inherits: `IReplicator`
- L29 _private field_ `private readonly string _name`
- L30 _private field_ `private readonly ILogger _logger`
- L31 _private field_ `private readonly ManualResetEvent _replicationFinishedEvent = new ManualResetEvent(true)`
- L32 _private field_ `private readonly ReplicatorSettings _replicatorSettings`
- L33 _private field_ `private readonly IBlobService _blobService`
- L34 _private field_ `private readonly IReplicationLog _replicationLog`
- L35 _private field_ `private readonly IServiceCredentials _serviceCredentials`
- L36 _private field_ `private readonly Tracer _tracer`
- L37 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L38 _private field_ `private readonly ReplicationLogFactory _replicationLogFactory`
- L39 _private field_ `private readonly HttpClient _httpClient`
- L40 _private field_ `private readonly NamespaceId _namespace`
- L41 _private field_ `private RefsState _refsState`
- L42 _private field_ `private bool _replicationRunning`
- L43 _private field_ `private CancellationTokenSource _replicationTokenSource = new CancellationTokenSource()`
- L44 _private field_ `private bool _disposed = false`
- L46 _private field_ `private static Histogram<long>? s_replicatedCounter`
- L47 _private field_ `private static readonly JsonSerializerOptions DefaultSerializerSettings = ConfigureJsonOptions()`
- L48-84 _public ctor_ `public RefsReplicator(ReplicatorSettings replicatorSettings, IBlobService blobService, IHttpClientFactory httpClientFactory, IReplicationLog replicationLog, IServiceCredentials serviceCredentials, Tracer tracer, BufferedPayloadFactory bufferedPayloadFactory, ReplicationLogFactory replicationLogFactory, ILogger<RefsReplicator> logger, Meter meter)`
- L86-91 _private method_ `private static JsonSerializerOptions ConfigureJsonOptions()`
- L93-97 _public method_ `public void Dispose()`
- L99-116 _protected method_ `protected virtual void Dispose(bool disposing)`
- L118-121 _private method_ `private async Task SaveStateAsync(RefsState newState)`
- L123-277 _public method_ `public async Task<bool> TriggerNewReplicationsAsync()`
- L279-365 _private method_ `private async Task<(string, Guid, int)> ReplicateFromSnapshotAsync(NamespaceId ns, CancellationToken cancellationToken, BlobId? snapshotBlob = null, NamespaceId? blobNamespace = null)`
- L367-377 _private method_ `private async Task<HttpRequestMessage> BuildHttpRequestAsync(HttpMethod httpMethod, Uri uri)`
- L379-479 _private method_ `private async Task<int> ReplicateIncrementallyAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent, CancellationToken replicationToken)`
- L481-612 _private method_ `private async Task<bool> ReplicateOpAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId objectToReplicate, CancellationToken cancellationToken)`
- L614-729 _private method_ `private async IAsyncEnumerable<ReplicationLogEvent> GetRefEventsAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L731-737 _private method_ `private void LogReplicationHeartbeat(int countOfCurrentReplications)`
- L739-742 _private method_ `private async Task AddToReplicationLogAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId blob)`
- L744-747 _public method_ `public void SetReplicationOffset(long? state)`
- L749-758 _public method_ `public async Task StopReplicatingAsync()`
- L760 _public property_ `public ReplicatorState State => ...`
- L762 _public property_ `public ReplicatorInfo Info { get; set; }`
- L764-768 _public method_ `public Task DeleteStateAsync()`
- L770-775 _public method_ `public void SetRefState(string? lastBucket, Guid? lastEvent)`

#### class `Jupiter.Implementation.UseSnapshotException`  
`public class UseSnapshotException : Exception`  
_public; L778-788_
- inherits: `Exception`
- L780 _public property_ `public BlobId SnapshotBlob { get; }`
- L781 _public property_ `public NamespaceId BlobNamespace { get; }`
- L783-787 _public ctor_ `public UseSnapshotException(BlobId snapshotBlob, NamespaceId blobNamespace)`

#### class `Jupiter.Implementation.NoSnapshotAvailableException`  
`public class NoSnapshotAvailableException : Exception`  
_public; L790-795_
- inherits: `Exception`
- L792-794 _public ctor_ `public NoSnapshotAvailableException(string message) : base(message)`

#### class `Jupiter.Implementation.RefsState`  
`public class RefsState : ReplicatorState`  
_public; L797-807_
- inherits: `ReplicatorState`
- L799-806 _public ctor_ `public RefsState()`

#### class `Jupiter.Implementation.ProblemDetailsWithSnapshots`  
`public class ProblemDetailsWithSnapshots : ProblemDetails`  
_public; L809-813_
- inherits: `ProblemDetails`
- L811 _public property_ `public BlobId SnapshotId { get; set; }`
- L812 _public property_ `public NamespaceId? BlobNamespace { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/ReplicationService.cs` (Jupiter)


#### class `Jupiter.Implementation.ReplicationState`  
`public class ReplicationState`  
_public; L15-18_
- L17 _public property_ `public List<IReplicator> Replicators { get; }`

#### class `Jupiter.Implementation.ReplicationService`  
`public class ReplicationService : PollingService<ReplicationState>`  
_public; L21-180_
- inherits: `PollingService<ReplicationState>`
- L23 _private field_ `private readonly IOptionsMonitor<ReplicationSettings> _settings`
- L24 _private field_ `private readonly ILeaderElection _leaderElection`
- L25 _private field_ `private readonly ILogger _logger`
- L26 _private field_ `private readonly Dictionary<string, PendingReplication> _currentReplications = ...`
- L26 _private field_ `private readonly Dictionary< _currentReplications = new Dictionary<string, PendingReplication>()`
- L28-31 _protected method_ `protected override bool ShouldStartPolling()`
- L33-52 _public ctor_ `public ReplicationService(IOptionsMonitor<ReplicationSettings> settings, IOptionsMonitor<ClusterSettings> clusterSettings, IServiceProvider provider, ILeaderElection leaderElection, ILogger<ReplicationService> logger) : base(serviceName: nameof(ReplicationService), TimeSpan.FromSeconds(settings.CurrentValue.ReplicationPollFrequencySeconds), new ReplicationState(), logger, startAtRandomTime: true)`
- L54-66 _private method_ `private void OnLeaderChanged(object? sender, OnLeaderChangedEventArgs e)`
- L68-79 _private method_ `private static IReplicator CreateReplicator(ReplicatorSettings replicatorSettings, ClusterSettings clusterSettings, IServiceProvider provider)`
- L81-155 _public method_ `public override async Task<bool> OnPollAsync(ReplicationState state, CancellationToken cancellationToken)`
- L163-172 _protected method_ `protected override async Task OnStopping(ReplicationState state)`
- L174-179 _public method_ `public IEnumerable<IReplicator> GetReplicators(NamespaceId ns)`

#### class `Jupiter.Implementation.ReplicationService.PendingReplication`  
`private class PendingReplication`  
_private; L157-161_
- L159 _public property_ `public Task<bool> Task { get; init; }`
- L160 _public property_ `public DateTime LastForceRun { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/Replication/ReplicationSettings.cs` (Jupiter)


#### class `Jupiter.ReplicationSettings`  
`public class ReplicationSettings : IValidatableObject`  
_public; L10-41_
- inherits: `IValidatableObject`
- L15 _public property_ `public bool Enabled { get; set; }` — Enable to start a replicating another Jupiter instance into this one
- L22 _public property_ `public int ReplicationPollFrequencySeconds { get; set; }` — attrs: `[Required] [Range(15, int.MaxValue)]` — The frequency at which to poll for new replication events
- L27 _public property_ `public List<ReplicatorSettings> Replicators { get; set; }` — attrs: `[Required] [System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L29-40 _public method_ `public IEnumerable<ValidationResult> Validate(ValidationContext validationContext)`

#### class `Jupiter.ReplicatorSettings`  
`public class ReplicatorSettings`  
_public; L43-90_
- L49 _public property_ `public string NamespaceToReplicate { get; set; }` — attrs: `[Required]` — The namespace which this replicator is replicating, will be used both on the source and destination side
- L56 _public property_ `public string ReplicatorName { get; set; }` — attrs: `[Required] [Key]` — Name of this replicator instance, should be unique within the cluster
- L61 _public property_ `public string? SourceSite { get; set; }` — The site name of the peer which will be replicated
- L67 _public property_ `public string ConnectionString { get; set; }` — attrs: `[Url]` — The connection string to the remote jupiter instance which will be replicated
- L69 _public property_ `public ReplicatorVersion Version { get; set; }`
- L74 _public property_ `public int MaxParallelReplications { get; set; }` — Max number of replications that can run in parallel, set to -1 to for it to be one per CPU (can easily be oversubscribed)
- L79 _public property_ `public bool EnableMultipartReplications { get; set; }` — Whether to enable multipart transfers, when using blob stores that support it.
- L84 _public property_ `public bool SkipSnapshot { get; set; }` — Do not read in old history using a snapshot, instead just start replicating the new incremental state. Means we will only have partial state but we will also get going quicker on relatively useful blobs.
- L89 _public property_ `public int PageSize { get; set; }` — The number of records returned in a single response (page) if available, this needs to be bumped as you increase `MaxParallelReplications`

#### enum `Jupiter.ReplicatorVersion`  
`public enum ReplicatorVersion`  
_public; L92-96_
- L94 _public* enumerator_ `Refs`
- L95 _public* enumerator_ `Blobs`

#### class `Jupiter.ServiceCredentialSettings`  
`public class ServiceCredentialSettings`  
_public; L98-129_
- L103 _public property_ `public string OAuthClientId { get; set; }` — The client id to use for communication with other services
- L108 _public property_ `public string OAuthClientSecret { get; set; }` — The client secret to use for communication with other services
- L113 _public property_ `public Uri? OAuthLoginUrl { get; set; }` — The url to login for a token to use to connect to the other services. Set to empty to disable login, assuming a unprotected service.
- L118 _public property_ `public string OAuthScope { get; set; }` — The scope to request
- L123 _public property_ `public string SchemeName { get; set; }` — The authentication scheme to use for this token
- L128 _public property_ `public string? AccessToken { get; set; }` — The access token to use if not using OIDC. Can be resolved using a secret string.

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ScyllaSessionManager.cs` (Jupiter)


#### interface `Jupiter.Implementation.IScyllaSessionManager`  
`public interface IScyllaSessionManager`  
_public; L9-28_
- L11 _public* method_ `ISession GetSessionForReplicatedKeyspace()`
- L12 _public* method_ `ISession GetSessionForLocalKeyspace()`
- L17 _public* property_ `bool IsScylla { get; }` — True if scylla specific features can be used
- L22 _public* property_ `bool IsCassandra { get; }` — True when using a base cassandra protocol
- L27 _public* property_ `bool IsAWSKeyspace { get; }` — True when AWS Keyspace is being used

#### class `Jupiter.Implementation.ScyllaSessionManager`  
`public class ScyllaSessionManager : IScyllaSessionManager`  
_public; L30-58_
- inherits: `IScyllaSessionManager`
- L32 _private field_ `private readonly ISession _replicatedSession`
- L33 _private field_ `private readonly ISession _localSession`
- L35-42 _public ctor_ `public ScyllaSessionManager(ISession replicatedSession, ISession localSession, bool isScylla, bool isCassandra, bool isKeyspace)`
- L44-48 _public method_ `public ISession GetSessionForReplicatedKeyspace()`
- L50-53 _public method_ `public ISession GetSessionForLocalKeyspace()`
- L55 _public property_ `public bool IsScylla { get; }`
- L56 _public property_ `public bool IsCassandra { get; }`
- L57 _public property_ `public bool IsAWSKeyspace { get; }`

#### class `Jupiter.Implementation.ScyllaUtils`  
`public static class ScyllaUtils`  
_public; L60-83_
- L62-82 _public method_ `public static IEnumerable<(long, long)> GetTableRanges(uint nodesInCluster, uint coresPerNode, uint smudgeFactor)`

#### class `Jupiter.Implementation.ScyllaTraceExtensions`  
`public static class ScyllaTraceExtensions`  
_public; L85-96_
- L87 _private field_ `private static readonly Tracer ScyllaTracer = TracerProvider.Default.GetTracer(ScyllaServiceName)`
- L89 _private const_ `private const string ScyllaServiceName = "ScyllaDB"`
- L92-95 _public method_ `public static TelemetrySpan BuildScyllaSpan(this Tracer tracer, string spanName)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter", Justification = "Useful to create from the tracer in case we want to use that context")]`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/ServiceCredentials.cs` (Jupiter)


#### interface `Jupiter.Implementation.IServiceCredentials`  
`public interface IServiceCredentials`  
_public; L12-17_
- L14 _public* method_ `Task<string?> GetTokenAsync(CancellationToken cancellationToken = default)`
- L16 _public* method_ `string GetAuthenticationScheme()`

#### class `Jupiter.Implementation.ServiceCredentials`  
`public class ServiceCredentials : IServiceCredentials`  
_public; L19-74_
- inherits: `IServiceCredentials`
- L21 _private field_ `private readonly ClientCredentialOAuthAuthenticator? _authenticator`
- L22 _private field_ `private readonly IOptionsMonitor<ServiceCredentialSettings> _settings`
- L23 _private field_ `private readonly ISecretResolver _secretResolver`
- L25-45 _public ctor_ `public ServiceCredentials(IServiceProvider provider, IOptionsMonitor<ServiceCredentialSettings> settings, ISecretResolver secretResolver)`
- L47-54 _public method_ `public string? GetToken()`
- L56-68 _public method_ `public async Task<string?> GetTokenAsync(CancellationToken cancellationToken)`
- L70-73 _public method_ `public string GetAuthenticationScheme()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TaskUtils.cs` (Jupiter)


#### class `Jupiter.TaskUtils`  
`internal static class TaskUtils`  
_internal; L9-24_
- L11-23 _public method_ `public static byte[] CombineIntoSingleBuffer(Task<byte[]>[] tasks)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/IReplicationLog.cs` (Jupiter)


#### interface `Jupiter.Implementation.IReplicationLog`  
`public interface IReplicationLog`  
_public; L11-28_
- L13 _public* method_ `IAsyncEnumerable<NamespaceId> GetNamespacesAsync()`
- L15 _public* method_ `Task<(string, Guid)> InsertAddEventAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId objectBlob, DateTime? timeBucket = null)`
- L16 _public* method_ `Task<(string, Guid)> InsertDeleteEventAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime? timeBucket = null)`
- L17 _public* method_ `IAsyncEnumerable<ReplicationLogEvent> GetAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent)`
- L19 _public* method_ `Task AddSnapshotAsync(SnapshotInfo snapshotHeader)`
- L20 _public* method_ `Task<SnapshotInfo?> GetLatestSnapshotAsync(NamespaceId ns)`
- L21 _public* method_ `IAsyncEnumerable<SnapshotInfo> GetSnapshotsAsync(NamespaceId ns)`
- L23 _public* method_ `Task UpdateReplicatorStateAsync(NamespaceId ns, string replicatorName, ReplicatorState newState)`
- L24 _public* method_ `Task<ReplicatorState?> GetReplicatorStateAsync(NamespaceId ns, string replicatorName)`
- L26 _public* method_ `Task<(string, Guid)> InsertAddBlobEventAsync(NamespaceId ns, BlobId objectBlob, DateTime? timeBucket = null, BucketId? bucketHint = null)`
- L27 _public* method_ `IAsyncEnumerable<BlobReplicationLogEvent> GetBlobEventsAsync(NamespaceId ns, string replicationBucket)`

#### class `Jupiter.Implementation.SnapshotInfo`  
`public class SnapshotInfo`  
_public; L30-45_
- L33-39 _public ctor_ `public SnapshotInfo(NamespaceId snapshottedNamespace, NamespaceId blobNamespace, BlobId snapshotBlob, DateTime timestamp)` — attrs: `[JsonConstructor]`
- L41 _public property_ `public NamespaceId SnapshottedNamespace { get; set; }`
- L42 _public property_ `public NamespaceId BlobNamespace { get; set; }`
- L43 _public property_ `public BlobId SnapshotBlob { get; set; }`
- L44 _public property_ `public DateTime Timestamp { get; set; }`

#### class `Jupiter.Implementation.ReplicationLogEvent`  
`public class ReplicationLogEvent`  
_public; L47-84_
- L50-60 _public ctor_ `public ReplicationLogEvent(NamespaceId @namespace, BucketId bucket, RefId key, BlobId? blob, Guid eventId, string timeBucket, DateTime timestamp, OpType op)` — attrs: `[JsonConstructor]`
- L69 _public property_ `public NamespaceId Namespace { get; }`
- L71 _public property_ `public BucketId Bucket { get; }`
- L73 _public property_ `public RefId Key { get; }`
- L75 _public property_ `public OpType Op { get; }`
- L77 _public property_ `public DateTime Timestamp { get; }`
- L79 _public property_ `public string TimeBucket { get; }`
- L81 _public property_ `public Guid EventId { get; }`
- L83 _public property_ `public BlobId? Blob { get; }`

#### enum `Jupiter.Implementation.ReplicationLogEvent.OpType`  
`public enum OpType`  
_public; L63-67_
- L65 _public* enumerator_ `Added = 0`
- L66 _public* enumerator_ `Deleted = 1`

#### class `Jupiter.Implementation.BlobReplicationLogEvent`  
`public class BlobReplicationLogEvent`  
_public; L86-113_
- L89-98 _public ctor_ `public BlobReplicationLogEvent(NamespaceId @namespace, BlobId blob, Guid eventId, string timeBucket, DateTime timestamp, OpType op, BucketId? bucketHint)` — attrs: `[JsonConstructor]`
- L106 _public property_ `public NamespaceId Namespace { get; }`
- L107 _public property_ `public BlobId Blob { get; }`
- L108 _public property_ `public OpType Op { get; }`
- L109 _public property_ `public DateTime Timestamp { get; }`
- L110 _public property_ `public string TimeBucket { get; }`
- L111 _public property_ `public Guid EventId { get; }`
- L112 _public property_ `public BucketId? BucketHint { get; }`

#### enum `Jupiter.Implementation.BlobReplicationLogEvent.OpType`  
`public enum OpType`  
_public; L100-104_
- L102 _public* enumerator_ `Added = 0`
- L103 _public* enumerator_ `Deleted = 1`

#### class `Jupiter.Implementation.IncrementalLogNotAvailableException`  
`public class IncrementalLogNotAvailableException : Exception`  
_public; L115-117_
- inherits: `Exception`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/MemoryReplicationLog.cs` (Jupiter)


#### class `Jupiter.Implementation.MemoryReplicationLog`  
`internal class MemoryReplicationLog : IReplicationLog`  
_internal; L14-277_
- inherits: `IReplicationLog`
- L16 _private field_ `private readonly ConcurrentDictionary<NamespaceId, SortedList<string, List<(TimeUuid, ReplicationLogEvent)>>> _replicationEvents = ...`
- L16 _private field_ `private readonly ConcurrentDictionary< string`
- L16 _private field_ `private readonly ConcurrentDictionary< _replicationEvents = new()`
- L17 _private field_ `private readonly ConcurrentDictionary<NamespaceId, SortedList<string, List<(TimeUuid, BlobReplicationLogEvent)>>> _blobReplicationEvents = ...`
- L17 _private field_ `private readonly ConcurrentDictionary< string`
- L17 _private field_ `private readonly ConcurrentDictionary< _blobReplicationEvents = new()`
- L18 _private field_ `private readonly ConcurrentDictionary<NamespaceId, List<SnapshotInfo>> _snapshots = ...`
- L18 _private field_ `private readonly ConcurrentDictionary< _snapshots = new()`
- L20 _private field_ `private readonly ConcurrentDictionary<NamespaceId, ConcurrentDictionary<string, ReplicatorState>> _replicatorState = ...`
- L20 _private field_ `private readonly ConcurrentDictionary< string`
- L20 _private field_ `private readonly ConcurrentDictionary< _replicatorState = new()`
- L22 _private field_ `private readonly ConcurrentDictionary<NamespaceId, bool> _namespaces = ...`
- L22 _private field_ `private readonly ConcurrentDictionary< _namespaces = new()`
- L24-27 _public method_ `public IAsyncEnumerable<NamespaceId> GetNamespacesAsync()`
- L29-32 _public method_ `public Task<(string, Guid)> InsertAddEventAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId objectBlob, DateTime? timestamp)`
- L34-73 _private method_ `private async Task<(string, Guid)> DoInsertAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId? hash, ReplicationLogEvent.OpType op, DateTime? lastTimestamp)`
- L75-78 _public method_ `public Task<(string, Guid)> InsertDeleteEventAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime? timestamp)`
- L80-146 _public method_ `public async IAsyncEnumerable<ReplicationLogEvent> GetAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent)`
- L148-164 _public method_ `public Task AddSnapshotAsync(SnapshotInfo snapshotHeader)`
- L166-174 _public method_ `public Task<SnapshotInfo?> GetLatestSnapshotAsync(NamespaceId ns)`
- L176-189 _public method_ `public async IAsyncEnumerable<SnapshotInfo> GetSnapshotsAsync(NamespaceId ns)`
- L191-207 _public method_ `public Task UpdateReplicatorStateAsync(NamespaceId ns, string replicatorName, ReplicatorState newState)`
- L209-218 _public method_ `public Task<ReplicatorState?> GetReplicatorStateAsync(NamespaceId ns, string replicatorName)`
- L220-256 _public method_ `public Task<(string, Guid)> InsertAddBlobEventAsync(NamespaceId ns, BlobId objectBlob, DateTime? timestamp = null, BucketId? bucketHint = null)`
- L258-276 _public method_ `public async IAsyncEnumerable<BlobReplicationLogEvent> GetBlobEventsAsync(NamespaceId ns, string replicationBucket)`

#### class `Jupiter.Implementation.DateTimeUtils`  
`public static class DateTimeUtils`  
_public; L279-310_
- L281-284 _public method_ `public static DateTime ToHourlyBucket(this DateTime timestamp)`
- L286-292 _public method_ `public static DateTime ToReplicationBucket(this DateTime timestamp)`
- L294-297 _public method_ `public static string ToReplicationBucketIdentifier(this DateTime timestamp)`
- L299-309 _public method_ `public static DateTime FromReplicationBucketIdentifier(this string replicationBucketIdentifier)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/ReplicationLogSnapshot.cs` (Jupiter)


#### class `Jupiter.Implementation.TransactionLog.ReplicationLogSnapshotState`  
`public class ReplicationLogSnapshotState`  
_public; L17-27_
- attrs: `[UsedImplicitly]`
- L19-23 _public ctor_ `public ReplicationLogSnapshotState(SnapshotHeader header, List<SnapshotLiveObject> liveObjects)`
- L25 _public property_ `public SnapshotHeader Header { get; set; }`
- L26 _public property_ `public List<SnapshotLiveObject> LiveObjects { get; }`

#### class `Jupiter.Implementation.TransactionLog.JsonReplicationLogSnapshot`  
`public class JsonReplicationLogSnapshot : ReplicationLogSnapshot`  
_public; L29-53_
- inherits: `ReplicationLogSnapshot`
- L31 _private field_ `private readonly List<SnapshotLiveObject> _liveObjects`
- L32-35 _private* ctor_ `JsonReplicationLogSnapshot(ReplicationLogSnapshotState snapshotState) : base(snapshotState.Header.Namespace, snapshotState.Header.LastBucket!, snapshotState.Header.LastEvent, (ulong)snapshotState.LiveObjects.Count)`
- L37-47 _public method_ `public static ReplicationLogSnapshot FromStream(Stream stream)`
- L49-52 _public method_ `public override IEnumerable<SnapshotLiveObject> GetLiveObjects()`

#### class `Jupiter.Implementation.TransactionLog.BinaryReplicationLogSnapshot`  
`public class BinaryReplicationLogSnapshot : ReplicationLogSnapshot`  
_public; L55-144_
- inherits: `ReplicationLogSnapshot`
- L57 _private field_ `private IBufferedPayload? _bufferedPayload`
- L59-62 _private ctor_ `private BinaryReplicationLogSnapshot(NamespaceId ns, string lastBucket, Guid lastEvent, ulong countOfObjects, IBufferedPayload payload) : base(ns, lastBucket, lastEvent, countOfObjects)`
- L64-67 _private ctor_ `private BinaryReplicationLogSnapshot(NamespaceId ns) : base(ns)`
- L69-81 _protected method_ `protected override void Dispose(bool disposing)`
- L83-91 _public method_ `public static ReplicationLogSnapshot FromStream(BufferedPayloadFactory payloadFactory, Stream stream)`
- L93-115 _private method_ `private static (NamespaceId, string, Guid, ulong) ReadHeader(Stream stream)`
- L117-138 _public method_ `public override IEnumerable<SnapshotLiveObject> GetLiveObjects()`
- L140-143 _public method_ `public static ReplicationLogSnapshot CreateEmptySnapshot(NamespaceId ns)`

#### class `Jupiter.Implementation.TransactionLog.ReplicationLogFactory`  
`public class ReplicationLogFactory`  
_public; L146-184_
- L148 _private field_ `private readonly BufferedPayloadFactory _payloadFactory`
- L150-153 _public ctor_ `public ReplicationLogFactory(BufferedPayloadFactory payloadFactory)`
- L155-178 _public method_ `public ReplicationLogSnapshot DeserializeSnapshotFromStream(Stream stream)`
- L180-183 _public method_ `public static ReplicationLogSnapshot CreateEmptySnapshot(NamespaceId ns)`

#### class `Jupiter.Implementation.TransactionLog.SnapshotHeader`  
`public class SnapshotHeader`  
_public; L186-191_
- L188 _public property_ `public NamespaceId Namespace { get; set; }`
- L189 _public property_ `public string LastBucket { get; set; }`
- L190 _public property_ `public Guid LastEvent { get; set; }`

#### class `Jupiter.Implementation.TransactionLog.SnapshotLiveObject`  
`public class SnapshotLiveObject`  
_public; L193-205_
- L195-200 _public ctor_ `public SnapshotLiveObject(BucketId bucket, RefId key, BlobId blob)`
- L202 _public property_ `public BucketId Bucket { get; set; }`
- L203 _public property_ `public RefId Key { get; set; }`
- L204 _public property_ `public BlobId Blob { get; set; }`

#### class `Jupiter.Implementation.TransactionLog.ReplicationLogSnapshot`  
`public abstract class ReplicationLogSnapshot : IDisposable`  
_public; L207-335_
- inherits: `IDisposable`
- L209 _private field_ `private readonly List<SnapshotLiveObject> _addedObjects = new List<SnapshotLiveObject>()`
- L210 _private field_ `private readonly HashSet<(BucketId, RefId)> _removedObjects = new HashSet<(BucketId, RefId)>()`
- L212-215 _protected ctor_ `protected ReplicationLogSnapshot(NamespaceId ns)`
- L217-223 _protected ctor_ `protected ReplicationLogSnapshot(NamespaceId ns, string lastBucket, Guid lastEvent, ulong liveObjectsCount)`
- L225 _public property_ `public NamespaceId Namespace { get; init; }`
- L226 _public property_ `public Guid? LastEvent { get; set; }`
- L227 _public property_ `public string? LastBucket { get; set; }`
- L228 _public property_ `public ulong LiveObjectsCount { get; set; }`
- L230 _public method_ `public abstract IEnumerable<SnapshotLiveObject> GetLiveObjects()`
- L232-297 _public method_ `public void Serialize(Stream stream)`
- L299-315 _public method_ `public void ProcessEvent(ReplicationLogEvent entry)`
- L317-320 _private method_ `private void ProcessAddEvent(BucketId bucket, RefId key, BlobId blob)`
- L321-324 _private method_ `private void ProcessDeleteEvent(BucketId bucket, RefId key)`
- L326-328 _protected method_ `protected virtual void Dispose(bool disposing)`
- L330-334 _public method_ `public void Dispose()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/ReplicationLogSnapshotBuilder.cs` (Jupiter)


#### class `Jupiter.Implementation.TransactionLog.ReplicationLogSnapshotBuilder`  
`public class ReplicationLogSnapshotBuilder`  
_public; L15-153_
- L17 _private field_ `private readonly IReplicationLog _replicationLog`
- L18 _private field_ `private readonly IBlobService _blobService`
- L19 _private field_ `private readonly IRefService _refService`
- L20 _private field_ `private readonly BufferedPayloadFactory _bufferedPayloadFactory`
- L21 _private field_ `private readonly ReplicationLogFactory _replicationLogFactory`
- L23-30 _public ctor_ `public ReplicationLogSnapshotBuilder(IReplicationLog replicationLog, IBlobService blobService, IRefService refService, BufferedPayloadFactory bufferedPayloadFactory, ReplicationLogFactory replicationLogFactory)`
- L32-152 _public method_ `public async Task<BlobId> BuildSnapshotAsync(NamespaceId ns, NamespaceId storeInNamespace, CancellationToken cancellationToken = default(CancellationToken))`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/ReplicationSnapshotService.cs` (Jupiter)


#### class `Jupiter.Implementation.SnapshotState`  
`public class SnapshotState`  
_public; L14-16_

#### class `Jupiter.Implementation.ReplicationSnapshotService`  
`public class ReplicationSnapshotService : PollingService<SnapshotState>`  
_public; L19-102_
- inherits: `PollingService<SnapshotState>`
- L21 _private field_ `private readonly IServiceProvider _provider`
- L22 _private field_ `private readonly IOptionsMonitor<SnapshotSettings> _settings`
- L23 _private field_ `private readonly IReplicationLog _replicationLog`
- L24 _private field_ `private readonly ILeaderElection _leaderElection`
- L25 _private field_ `private readonly ILogger _logger`
- L26 _private field_ `private readonly CancellationTokenSource _cancellationTokenSource = new CancellationTokenSource()`
- L27 _private field_ `private Task? _snapshotBuildTask = null`
- L29-32 _protected method_ `protected override bool ShouldStartPolling()`
- L34-41 _public ctor_ `public ReplicationSnapshotService(IServiceProvider provider, IOptionsMonitor<SnapshotSettings> settings, IReplicationLog replicationLog, ILeaderElection leaderElection, ILogger<ReplicationSnapshotService> logger) : base(serviceName: nameof(ReplicationSnapshotService), TimeSpan.FromMinutes(15), new SnapshotState(), logger)`
- L43-91 _public method_ `public override async Task<bool> OnPollAsync(SnapshotState state, CancellationToken cancellationToken)`
- L93-101 _protected method_ `protected override async Task OnStopping(SnapshotState state)`

#### class `Jupiter.Implementation.SnapshotSettings`  
`public class SnapshotSettings`  
_public; L104-113_
- L109 _public property_ `public bool Enabled { get; set; }` — Enable to start a replicating another Jupiter instance into this one
- L111 _public property_ `public NamespaceId SnapshotStorageNamespace { get; set; }`
- L112 _public property_ `public int MaxCountOfNamespacesToSnapshotInParallel { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/TransactionLog/ScyllaReplicationLog.cs` (Jupiter)


#### class `Jupiter.Implementation.ScyllaReplicationLog`  
`class ScyllaReplicationLog : IReplicationLog`  
_internal*; L15-477_
- inherits: `IReplicationLog`
- L17 _private field_ `private readonly IOptionsMonitor<ScyllaSettings> _settings`
- L18 _private field_ `private readonly Tracer _tracer`
- L19 _private field_ `private readonly ISession _session`
- L20 _private field_ `private readonly Mapper _mapper`
- L22-79 _public ctor_ `public ScyllaReplicationLog(IScyllaSessionManager scyllaSessionManager, IOptionsMonitor<ScyllaSettings> settings, Tracer tracer)`
- L81-98 _public method_ `public async IAsyncEnumerable<NamespaceId> GetNamespacesAsync()`
- L100-119 _public method_ `public async Task<(string, Guid)> InsertAddEventAsync(NamespaceId ns, BucketId bucket, RefId key, BlobId objectBlob, DateTime? timestamp)`
- L121-140 _public method_ `public async Task<(string, Guid)> InsertDeleteEventAsync(NamespaceId ns, BucketId bucket, RefId key, DateTime? timestamp)`
- L142-152 _private method_ `private async Task PotentiallyAddNamespaceAsync(NamespaceId ns)`
- L154-240 _public method_ `public async IAsyncEnumerable<ReplicationLogEvent> GetAsync(NamespaceId ns, string? lastBucket, Guid? lastEvent)`
- L242-295 _private method_ `private async IAsyncEnumerable<long> FindReplicationBucketsAsync(NamespaceId ns, string? lastBucket)`
- L297-307 _private method_ `private static long FromReplicationBucketIdentifier(string bucket)`
- L309-320 _public method_ `public async Task AddSnapshotAsync(SnapshotInfo snapshotHeader)`
- L322-347 _public method_ `public async Task CleanupSnapshotsAsync(NamespaceId ns)`
- L349-354 _public method_ `public async Task<SnapshotInfo?> GetLatestSnapshotAsync(NamespaceId ns)`
- L356-372 _public method_ `public async IAsyncEnumerable<SnapshotInfo> GetSnapshotsAsync(NamespaceId ns)`
- L374-384 _public method_ `public async Task UpdateReplicatorStateAsync(NamespaceId ns, string replicatorName, ReplicatorState newState)`
- L386-400 _public method_ `public async Task<ReplicatorState?> GetReplicatorStateAsync(NamespaceId ns, string name)`
- L402-421 _public method_ `public async Task<(string, Guid)> InsertAddBlobEventAsync(NamespaceId ns, BlobId objectBlob, DateTime? timestamp = null, BucketId? bucketHint = null)`
- L423-476 _public method_ `public async IAsyncEnumerable<BlobReplicationLogEvent> GetBlobEventsAsync(NamespaceId ns, string replicationBucket)`

#### class `Jupiter.Implementation.ScyllaReplicationLogEvent`  
`class ScyllaReplicationLogEvent`  
_internal*; L480-539_
- attrs: `[Cassandra.Mapping.Attributes.Table("replication_log")]`
- L488-493 _public ctor_ `public ScyllaReplicationLogEvent()`
- L495-504 _public ctor_ `public ScyllaReplicationLogEvent(string @namespace, string bucket, string key, DateTime lastTimestamp, OpType opType, BlobId? objectIdentifier)`
- L507 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L512 _public property_ `public long ReplicationBucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("replication_bucket")]`
- L515 _public property_ `public TimeUuid ReplicationId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("replication_id")]`
- L518 _public property_ `public string Bucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket")]`
- L521 _public property_ `public string Key { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("key")]`
- L524 _public property_ `public int Type { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("type")]`
- L527 _public property_ `public ScyllaBlobIdentifier? ObjectIdentifier { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("object_identifier")]`
- L529-533 _public method_ `public string GetReplicationBucketIdentifier()`
- L535-538 _public method_ `public DateTime GetReplicationBucketTimestamp()`

#### enum `Jupiter.Implementation.ScyllaReplicationLogEvent.OpType`  
`public enum OpType`  
_public; L482-486_
- L484 _public* enumerator_ `Added`
- L485 _public* enumerator_ `Deleted`

#### class `Jupiter.Implementation.ScyllaBlobReplicationLogEvent`  
`class ScyllaBlobReplicationLogEvent`  
_internal*; L542-596_
- attrs: `[Cassandra.Mapping.Attributes.Table("blob_replication_log")]`
- L550-554 _public ctor_ `public ScyllaBlobReplicationLogEvent()`
- L556-564 _public ctor_ `public ScyllaBlobReplicationLogEvent(string @namespace, BlobId blobId, DateTime lastTimestamp, OpType opType, BucketId? bucketHint)`
- L567 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L572 _public property_ `public long ReplicationBucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey] [Cassandra.Mapping.Attributes.Column("replication_bucket")]`
- L575 _public property_ `public TimeUuid ReplicationId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("replication_id")]`
- L578 _public property_ `public byte[] BlobId { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("blob_id")]`
- L581 _public property_ `public int Type { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("type")]`
- L584 _public property_ `public string? BucketHint { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("bucket_hint")]`
- L586-590 _public method_ `public string GetReplicationBucketIdentifier()`
- L592-595 _public method_ `public DateTime GetReplicationBucketTimestamp()`

#### enum `Jupiter.Implementation.ScyllaBlobReplicationLogEvent.OpType`  
`public enum OpType`  
_public; L544-548_
- L546 _public* enumerator_ `Added`
- L547 _public* enumerator_ `Deleted`

#### class `Jupiter.Implementation.ScyllaSnapshot`  
`class ScyllaSnapshot`  
_internal*; L599-628_
- attrs: `[Cassandra.Mapping.Attributes.Table("replication_snapshot")]`
- L601-606 _public ctor_ `public ScyllaSnapshot()`
- L608-614 _public ctor_ `public ScyllaSnapshot(string @namespace, string blobNamespace, TimeUuid id, BlobId objectIdentifier)`
- L617 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L621 _public property_ `public TimeUuid Id { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("id")] [Cassandra.Mapping.Attributes.ClusteringKey]`
- L624 _public property_ `public ScyllaBlobIdentifier BlobSnapshot { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("blob_snapshot")]`
- L627 _public property_ `public string BlobNamespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("blob_namespace")]`

#### class `Jupiter.Implementation.ScyllaNamespace`  
`class ScyllaNamespace`  
_internal*; L631-645_
- attrs: `[Cassandra.Mapping.Attributes.Table("replication_namespace")]`
- L633-636 _public ctor_ `public ScyllaNamespace()`
- L638-641 _public ctor_ `public ScyllaNamespace(string @namespace)`
- L644 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`

#### class `Jupiter.Implementation.ScyllaReplicationState`  
`class ScyllaReplicationState`  
_internal*; L648-685_
- attrs: `[Cassandra.Mapping.Attributes.Table("replication_state")]`
- L650-655 _public ctor_ `public ScyllaReplicationState()`
- L657-663 _public ctor_ `public ScyllaReplicationState(NamespaceId ns, string name, string? lastBucket, Guid? lastEvent)`
- L666 _public property_ `public string Namespace { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.PartitionKey]`
- L669 _public property_ `public string Name { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.ClusteringKey]`
- L672 _public property_ `public string? LastBucket { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("last_bucket")]`
- L675 _public property_ `public Guid? LastEvent { get; set; }` — attrs: `[Cassandra.Mapping.Attributes.Column("last_event")]`
- L677-684 _public method_ `public ReplicatorState ToReplicatorState()`

### `Source/Programs/UnrealCloudDDC/Jupiter/Implementation/VersionFile.cs` (Jupiter)


#### interface `Jupiter.Implementation.IVersionFile`  
`public interface IVersionFile`  
_public; L9-12_
- L11 _public property_ `public string? VersionString { get; }`

#### class `Jupiter.Implementation.VersionFile`  
`public class VersionFile : IVersionFile`  
_public; L14-36_
- inherits: `IVersionFile`
- L16 _private field_ `private readonly VersionFileContents _versionFileContents`
- L23-33 _public ctor_ `public VersionFile()`
- L35 _public property_ `public string? VersionString => ...`

#### class `Jupiter.Implementation.VersionFile.VersionFileContents`  
`private class VersionFileContents`  
_private; L18-21_
- L20 _public property_ `public string? Version { get; set; }`

### `Source/Programs/UnrealCloudDDC/Jupiter/Jupiter.Startup.cs` (Jupiter)


#### class `Jupiter.JupiterStartup`  
`public class JupiterStartup : BaseStartup`  
_public; L36-698_
- inherits: `BaseStartup`
- L38-41 _public ctor_ `public JupiterStartup(IConfiguration configuration) : base(configuration, CreateLogger<JupiterStartup>())`
- L43-46 _protected method_ `protected override void OnAddAuthorization(AuthorizationOptions authorizationOptions, List<string> defaultSchemes)`
- L48-235 _protected method_ `protected override void OnAddService(IServiceCollection services)`
- L237-249 _private method_ `private IBlockStore BlockIndexFactory(IServiceProvider provider)`
- L251-263 _private method_ `private IBuildStore BuildStoreFactory(IServiceProvider provider)`
- L265-283 _private method_ `private IBlobIndex BlobIndexFactory(IServiceProvider provider)`
- L285-297 _private method_ `private IPeerServiceDiscovery ServiceDiscoveryFactory(IServiceProvider provider)`
- L299-307 _private method_ `private IAmazonSecretsManager CreateAWSSecretsManager(IServiceProvider provider)`
- L309-312 _private method_ `private CompressedBufferUtils CreateCompressedBufferUtils(IServiceProvider provider)`
- L314-340 _private method_ `private object ContentIdStoreFactory(IServiceProvider provider)`
- L342-502 _private method_ `private IScyllaSessionManager ScyllaFactory(IServiceProvider provider)`
- L504-529 _private method_ `private IReferencesStore ObjectStoreFactory(IServiceProvider provider)`
- L531-552 _private method_ `private ILeaderElection CreateLeaderElection(IServiceProvider provider)`
- L554-604 _private method_ `private IAmazonS3 CreateS3(IServiceProvider provider)`
- L606-626 _private method_ `private IReplicationLog ReplicationLogFactory(IServiceProvider provider)`
- L628-697 _protected method_ `protected override void OnAddHealthChecks(IServiceCollection services, IHealthChecksBuilder healthChecks)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Program.cs` (Jupiter)


#### class `Jupiter.Program`  
`public static class Program`  
_public; L8-19_
- L10-13 _public method_ `public static int Main(string[] args)`
- L15-18 _public method_ `public static IHostBuilder CreateHostBuilder(string[] Args)`

### `Source/Programs/UnrealCloudDDC/Jupiter/Settings.cs` (Jupiter)


#### class `Jupiter.UnrealCloudDDCSettings`  
`public class UnrealCloudDDCSettings`  
_public; L14-153_
- L100 _public property_ `public string[]? StorageImplementations { get; set; }` — attrs: `[ValidStorageBackend] [System.Diagnostics.CodeAnalysis.SuppressMessage("Naming", "CA1721:Property names should not match get methods", Justification = "This pattern is used to work around limitations in dotnet configurations support for enu`
- L102-110 _public method_ `public IEnumerable<UnrealCloudDDCSettings.StorageBackendImplementations> GetStorageImplementations()`
- L112 _public property_ `public ReplicationLogWriterImplementations ReplicationLogWriterImplementation { get; set; }` — attrs: `[Required]`
- L115 _public property_ `public ReferencesDbImplementations ReferencesDbImplementation { get; set; }` — attrs: `[Required]`
- L117 _public property_ `public LeaderElectionImplementations LeaderElectionImplementation { get; set; }`
- L118 _public property_ `public ContentIdStoreImplementations ContentIdStoreImplementation { get; set; }`
- L119 _public property_ `public BlobIndexImplementations BlobIndexImplementation { get; set; }`
- L120 _public property_ `public BuildStoreImplementations BuildStoreImplementation { get; set; }`
- L121 _public property_ `public ServiceDiscoveryImplementations ServiceDiscoveryImplementation { get; set; }`
- L123 _public property_ `public int? MaxSingleBlobSize { get; set; }`
- L125 _public property_ `public int LastAccessRollupFrequencySeconds { get; set; }`
- L126 _public property_ `public bool EnableLastAccessTracking { get; set; }`
- L127 _public property_ `public bool EnableOnDemandReplication { get; set; }`
- L129 _public property_ `public bool EnableBucketStatsTracking { get; set; }`
- L130 _public property_ `public bool EnableInlineSmallBlobs { get; set; }`
- L135 _public property_ `public bool EnableForceSubmitRefBlobToBlobStore { get; set; }` — Forces the inlined blobs to also be submitted into the blob store, is the old behavior and is not recommended.
- L137 _public property_ `public long InlineBlobMaxSize { get; set; }`
- L142 _public property_ `public int RefFinalizeResolveMaxParallel { get; set; }` — Used to force a more parallel resolve than normal (which has no limits). Can be used to go wider then the number of processors which improves how quickly the finalize for a ref can be done, especially useful for refs with a lot of dependencies
- L147 _public property_ `public bool UseLastAccessBackgroundService { get; set; }` — Set to enable using the new last access service which is registered as a background service
- L152 _public property_ `public bool RemoveReferencesOnBlobDeletion { get; set; }` — Remove the incoming blob references when the blob is deleted

#### enum `Jupiter.UnrealCloudDDCSettings.ReplicationLogWriterImplementations`  
`public enum ReplicationLogWriterImplementations`  
_public; L16-21_
- L18 _public* enumerator_ `Memory`
- L19 _public* enumerator_ `Scylla`
- L20 _public* enumerator_ `Mongo`

#### enum `Jupiter.UnrealCloudDDCSettings.StorageBackendImplementations`  
`public enum StorageBackendImplementations`  
_public; L23-31_
- L25 _public* enumerator_ `S3`
- L26 _public* enumerator_ `Azure`
- L27 _public* enumerator_ `FileSystem`
- L28 _public* enumerator_ `Memory`
- L29 _public* enumerator_ `Relay`
- L30 _public* enumerator_ `Peer`

#### enum `Jupiter.UnrealCloudDDCSettings.ReferencesDbImplementations`  
`public enum ReferencesDbImplementations`  
_public; L33-41_
- L35 _public* enumerator_ `Memory`
- L36 _public* enumerator_ `Scylla`
- L37 _public* enumerator_ `Mongo`
- L38 _public* enumerator_ `Cache`
- L39 _public* enumerator_ `Galileo`
- L40 _public* enumerator_ `DataStore`

#### enum `Jupiter.UnrealCloudDDCSettings.ContentIdStoreImplementations`  
`public enum ContentIdStoreImplementations`  
_public; L43-50_
- L45 _public* enumerator_ `Memory`
- L46 _public* enumerator_ `Scylla`
- L47 _public* enumerator_ `Mongo`
- L48 _public* enumerator_ `Cache`
- L49 _public* enumerator_ `DataStore`

#### enum `Jupiter.UnrealCloudDDCSettings.BlobIndexImplementations`  
`public enum BlobIndexImplementations`  
_public; L52-59_
- L54 _public* enumerator_ `Memory`
- L55 _public* enumerator_ `Scylla`
- L56 _public* enumerator_ `Mongo`
- L57 _public* enumerator_ `Cache`
- L58 _public* enumerator_ `DataStore`

#### enum `Jupiter.UnrealCloudDDCSettings.BuildStoreImplementations`  
`public enum BuildStoreImplementations`  
_public; L61-65_
- L63 _public* enumerator_ `Memory`
- L64 _public* enumerator_ `Scylla`

#### enum `Jupiter.UnrealCloudDDCSettings.LeaderElectionImplementations`  
`public enum LeaderElectionImplementations`  
_public; L67-72_
- L69 _public* enumerator_ `Static`
- L70 _public* enumerator_ `Kubernetes`
- L71 _public* enumerator_ `Disabled`

#### enum `Jupiter.UnrealCloudDDCSettings.ServiceDiscoveryImplementations`  
`public enum ServiceDiscoveryImplementations`  
_public; L74-78_
- L76 _public* enumerator_ `Static`
- L77 _public* enumerator_ `Kubernetes`

#### class `Jupiter.UnrealCloudDDCSettings.ValidStorageBackend`  
`private sealed class ValidStorageBackend : ValidationAttribute`  
_private; L80-96_
- inherits: `ValidationAttribute`
- L82-85 _public method_ `public override string FormatErrorMessage(string name)`
- L87-95 _public method_ `public override bool IsValid(object? value)`

#### class `Jupiter.MongoSettings`  
`public class MongoSettings`  
_public; L155-161_
- L157 _public property_ `public string ConnectionString { get; set; }` — attrs: `[Required]`
- L159 _public property_ `public bool RequireTls12 { get; set; }`
- L160 _public property_ `public bool CreateDatabaseIfMissing { get; set; }`

#### class `Jupiter.MemoryCacheContentIdSettings`  
`public class MemoryCacheContentIdSettings : MemoryCacheOptions`  
_public; L163-169_
- inherits: `MemoryCacheOptions`
- L165 _public property_ `public bool Enabled { get; set; }`
- L167 _public property_ `public bool EnableSlidingExpiry { get; set; }`
- L168 _public property_ `public int SlidingExpirationMinutes { get; set; }`

#### class `Jupiter.MemoryCacheReferencesSettings`  
`public class MemoryCacheReferencesSettings : MemoryCacheOptions`  
_public; L171-177_
- inherits: `MemoryCacheOptions`
- L173 _public property_ `public bool Enabled { get; set; }`
- L175 _public property_ `public bool EnableSlidingExpiry { get; set; }`
- L176 _public property_ `public int SlidingExpirationMinutes { get; set; }`

#### class `Jupiter.AzureSettings`  
`public class AzureSettings`  
_public; L179-190_
- L181 _public property_ `public string ConnectionString { get; set; }` — attrs: `[Required]`
- L185 _public property_ `public Dictionary<string, string> StoragePoolConnectionStrings { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Modified by settings")]`
- L189 _public property_ `public Dictionary<string, string> StoragePoolContainerOverride { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Modified by settings")]`

#### class `Jupiter.FilesystemSettings`  
`public class FilesystemSettings`  
_public; L192-204_
- L194 _public property_ `public string RootDir { get; set; }` — attrs: `[Required]`
- L195 _public property_ `public ulong MaxSizeBytes { get; set; }`
- L196 _public property_ `public double TriggerThresholdPercentage { get; set; }`
- L197 _public property_ `public double TargetThresholdPercentage { get; set; }`
- L203 _public property_ `public bool PerNamespaceGC { get; set; }` — Enable to switch garbage collection to per namespace mode where every namespace has their own dedicated amount of space they can use This allows you to specify the MaxFilesystemStorageBytes option per namespace, the MaxSizeBytes in the Filesystem settings is considered the default value for namespaces that to not override it

#### class `Jupiter.S3Settings`  
`public class S3Settings`  
_public; L206-259_
- L208 _public property_ `public string ConnectionString { get; set; }` — attrs: `[Required]`
- L211 _public property_ `public Dictionary<string, Dictionary<string, string>> SiteBucketsPerStoragePool { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Modified by settings")]`
- L213 _public property_ `public string BucketName { get; set; }`
- L215 _public property_ `public bool ForceAWSPathStyle { get; set; }`
- L216 _public property_ `public bool AssumeHttpForRedirectUri { get; set; }`
- L217 _public property_ `public bool CreateBucketIfMissing { get; set; }`
- L220 _public property_ `public bool SetBucketPolicies { get; set; }`
- L222 _public property_ `public bool UseBlobIndexForExistsCheck { get; set; }`
- L226 _public property_ `public Dictionary<string, string> StoragePoolBucketOverride { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Modified by settings")]`
- L228 _public property_ `public bool? UseArnRegion { get; set; }`
- L229 _public property_ `public bool UseMultiPartUpload { get; set; }`
- L230 _public property_ `public bool UseMultiPartDownload { get; set; }`
- L235 _public property_ `public bool UseChunkEncoding { get; set; }` — Allows you to override S3 behavior with chunk encoding, this needs to be set to false for uploads against GCS
- L241 _public property_ `public bool PerPrefixListing { get; set; }` — Keeps S3 list queries within one prefix (first 2 bytes in the hash) - can help reduce errors from S3 about to many operations Is also a speed up on larger datasets
- L246 _public property_ `public int PerPrefixMaxKeys { get; set; }` — Max number of keys returned in a single request when listing S3
- L252 _public property_ `public int MultiPartMaxMemoryBufferSize { get; set; }` — Max size of bytes that is buffered into memory before switching to filesystem buffers Larger value means more RAM used but less load on the filesystem.
- L258 _public property_ `public bool? DisablePayloadChecksums { get; set; }` — Set this to disable payload signing and checksum generation during S3 uploads, saves cpu load when uploading large objects at some consistency risk and a requirement to use https connections see https://docs.aws.amazon.com/sdkfornet/v3/apidocs/items/S3/TTransferUtilityUploadRequest.html

#### class `Jupiter.GCSettings`  
`public class GCSettings`  
_public; L261-286_
- L263 _public property_ `public bool BlobCleanupServiceEnabled { get; set; }`
- L265 _public property_ `public bool CleanOldRefRecords { get; set; }`
- L266 _public property_ `public bool CleanOldBlobs { get; set; }`
- L267 _public property_ `public bool CleanTempFiles { get; set; }`
- L268 _public property_ `public bool RunFilesystemCleanup { get; set; }`
- L270 _public property_ `public TimeSpan LastAccessCutoff { get; set; }`
- L272 _public property_ `public TimeSpan BlobCleanupPollFrequency { get; set; }`
- L273 _public property_ `public TimeSpan RefCleanupPollFrequency { get; set; }`
- L274 _public property_ `public TimeSpan TempCleanupPollFrequency { get; set; }`
- L275 _public property_ `public TimeSpan TempCleanupMaximumAge { get; set; }`
- L276 _public property_ `public int OrphanGCMaxParallelOperations { get; set; }`
- L277 _public property_ `public int OrphanRefMaxParallelOperations { get; set; }`
- L278 _public property_ `public bool WriteDeleteToReplicationLog { get; set; }`
- L279 _public property_ `public NamespacePolicy.StoragePoolGCMethod DefaultGCPolicy { get; set; }`
- L280 _public property_ `public bool AllowBlockMetadataCleanup { get; set; }`
- L285 _public property_ `public int OrphanBlobCutoffDurationMinutes { get; set; }` — How long a blob needs to be around before its considered for potential GC

#### class `Jupiter.UpstreamRelaySettings`  
`public class UpstreamRelaySettings`  
_public; L288-291_
- L290 _public property_ `public string ConnectionString { get; set; }` — attrs: `[Required]`

#### class `Jupiter.ClusterSettings`  
`public class ClusterSettings`  
_public; L293-299_
- L296 _public property_ `public List<PeerSettings> Peers { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`
- L298 _public property_ `public DiscoverySettings? Discovery { get; set; }`

#### class `Jupiter.PeerSettings`  
`public class PeerSettings`  
_public; L301-309_
- L303 _public property_ `public string Name { get; set; }` — attrs: `[Required]`
- L305 _public property_ `public string FullName { get; set; }` — attrs: `[Required]`
- L308 _public property_ `public List<PeerEndpoints> Endpoints { get; set; }` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Usage", "CA2227:Collection properties should be read only", Justification = "Used by serialization")]`

#### class `Jupiter.PeerEndpoints`  
`public class PeerEndpoints`  
_public; L311-316_
- L313 _public property_ `public Uri Url { get; set; }` — attrs: `[Required]`
- L315 _public property_ `public bool IsInternal { get; set; }`

#### class `Jupiter.ConsistencyCheckSettings`  
`public class ConsistencyCheckSettings`  
_public; L318-338_
- L320 _public property_ `public bool EnableBlobStoreChecks { get; set; }`
- L321 _public property_ `public bool EnableBlobIndexChecks { get; set; }`
- L322 _public property_ `public bool EnableRefStoreChecks { get; set; }`
- L323 _public property_ `public double ConsistencyCheckPollFrequencySeconds { get; set; }`
- L324 _public property_ `public int BlobIndexMaxParallelOperations { get; set; }`
- L325 _public property_ `public bool AllowDeletesInBlobIndex { get; set; }`
- L326 _public property_ `public bool RunBlobStoreConsistencyCheckOnRootStore { get; set; }`
- L327 _public property_ `public bool CheckRefStoreLastAccessTimeConsistency { get; set; }`
- L328 _public property_ `public bool CheckRefStoreRegionalConsistency { get; set; }`
- L329 _public property_ `public bool CheckRefStorePartialObjects { get; set; }`
- L330 _public property_ `public string[] RegionalConsistencyCheckNamespaces { get; set; }`
- L331 _public property_ `public bool EnableBlobReferenceChecks { get; set; }`
- L332 _public property_ `public bool EnableBuildStoreConsistencyCheck { get; set; }`
- L333 _public property_ `public bool AllowDeletesInBuildStore { get; set; }`
- L334 _public property_ `public bool CheckBuildStorePartialObjects { get; set; }`
- L335 _public property_ `public bool CheckBuildStoreMissingBlobs { get; set; }`
- L336 _public property_ `public int BuildStoreConsistencyMaxParallelBuilds { get; set; }`
- L337 _public property_ `public int BuildStoreConsistencyMaxParallelBlobs { get; set; }`
