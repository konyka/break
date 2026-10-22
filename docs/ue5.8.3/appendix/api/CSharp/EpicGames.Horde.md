# CSharp / EpicGames.Horde

- project root: `Source/Programs/Shared/EpicGames.Horde`
- files: 282; symbols: 7761
- symbol kinds: class=693, const=140, ctor=467, delegate=1, enum=63, enumerator=290, event=2, field=770, indexer=8, interface=87, method=2309, operator=54, property=2697, record=92, record struct=59, struct=29
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Horde/Accounts/AccountId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Accounts.AccountId`  
`public readonly record struct AccountId(BinaryId Id)`  
_public; L17-40_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<AccountId, AccountIdConverter>))] [BinaryIdConverter(typeof(AccountIdConverter))]`
- desc: Identifier for a user account
- L20 _public method_ `public static AccountId Parse(string text)` — (inheritdoc)
- L23-36 _public method_ `public static bool TryParse(ReadOnlySpan<char> text, out AccountId result)` — (inheritdoc)
- L39 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Accounts.AccountIdConverter`  
`class AccountIdConverter : BinaryIdConverter<AccountId>`  
_internal*; L45-52_
- inherits: `BinaryIdConverter<AccountId>`
- desc: Converter to and from BinaryId instances.
- L48 _public method_ `public override AccountId FromBinaryId(BinaryId id)` — (inheritdoc)
- L51 _public method_ `public override BinaryId ToBinaryId(AccountId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Accounts/AccountMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Accounts.CreateAccountRequest`  
`public record class CreateAccountRequest(string Name, string Login, List<AccountClaimMessage> Claims, string? Description, string? Email, string? Password, bool? Enabled)`  
_public; L21-21_
- desc: Creates a new user account

#### record `EpicGames.Horde.Accounts.CreateAdminAccountRequest`  
`public record class CreateAdminAccountRequest(string Password)`  
_public; L27-27_
- desc: Creates the admin account

#### record `EpicGames.Horde.Accounts.CreateAccountResponse`  
`public record class CreateAccountResponse(AccountId Id)`  
_public; L33-33_
- desc: Response from the request to create a new user account

#### record `EpicGames.Horde.Accounts.UpdateAccountRequest`  
`public record class UpdateAccountRequest(string? Name, string? Login, List<AccountClaimMessage>? Claims, string? Description, string? Email, string? SecretToken, string? Password, bool? Enabled)`  
_public; L46-46_
- desc: Update request for a user account

#### record `EpicGames.Horde.Accounts.UpdateCurrentAccountRequest`  
`public record class UpdateCurrentAccountRequest(string? OldPassword, string? NewPassword)`  
_public; L53-53_
- desc: Update request for the current user account

#### record `EpicGames.Horde.Accounts.GetAccountResponse`  
`public record class GetAccountResponse(AccountId Id, string Name, string Login, List<AccountClaimMessage> Claims, string? Description, string? Email, bool Enabled)`  
_public; L65-65_
- desc: Creates a new user account

#### record `EpicGames.Horde.Accounts.AccountClaimMessage`  
`public record class AccountClaimMessage(string Type, string Value)`  
_public; L72-72_
- desc: Message describing a claim for an account

#### record `EpicGames.Horde.Accounts.DashboardLoginRequest`  
`public record class DashboardLoginRequest(string Username, string? Password, string? ReturnUrl)`  
_public; L80-80_
- desc: Dashboard login request

#### record `EpicGames.Horde.Accounts.GetAccountEntitlementsResponse`  
`public record class GetAccountEntitlementsResponse(bool Administrator, List<GetAccountScopeEntitlementsResponse> Scopes)`  
_public; L87-87_
- desc: Gets all entitlements for an account

#### record `EpicGames.Horde.Accounts.GetAccountScopeEntitlementsResponse`  
`public record class GetAccountScopeEntitlementsResponse(string Name, List<AclAction> Actions)`  
_public; L94-94_
- desc: Creates a new user account

### `Source/Programs/Shared/EpicGames.Horde/Acls/AclAction.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Acls.AclAction`  
`public readonly record struct AclAction(string Name)`  
_public; L19-23_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(AclActionJsonConverter))] [TypeConverter(typeof(AclActionTypeConverter))]`
- desc: Wraps a string used to describe an ACL action
- L22 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Acls.AclActionJsonConverter`  
`sealed class AclActionJsonConverter : JsonConverter<AclAction>`  
_internal*; L28-35_
- inherits: `JsonConverter<AclAction>`
- desc: Type converter for NamespaceId to and from JSON
- L31 _public method_ `public override AclAction Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L34 _public method_ `public override void Write(Utf8JsonWriter writer, AclAction value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Acls.AclActionTypeConverter`  
`sealed class AclActionTypeConverter : TypeConverter`  
_internal*; L40-47_
- inherits: `TypeConverter`
- desc: Type converter from strings to NamespaceId objects
- L43 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L46 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Acls/AclScopeName.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Acls.AclScopeName`  
`public record struct AclScopeName(string Text)`  
_public; L19-43_
- attrs: `[DebuggerDisplay("{Text}")] [JsonConverter(typeof(AclScopeNameJsonConverter))] [TypeConverter(typeof(AclScopeNameTypeConverter))]`
- desc: Name of an ACL scope
- L24 _public property_ `public static AclScopeName Root { get; }` — The root scope name
- L31 _public method_ `public AclScopeName Append(string name)` — Append another name to this scope
- L35 _public method_ `public bool Equals(AclScopeName other)` — (inheritdoc)
- L39 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L42 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Acls.AclScopeNameJsonConverter`  
`class AclScopeNameJsonConverter : JsonConverter<AclScopeName>`  
_internal*; L48-55_
- inherits: `JsonConverter<AclScopeName>`
- desc: Serializes AclScopeName objects to JSON
- L51 _public method_ `public override AclScopeName Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L54 _public method_ `public override void Write(Utf8JsonWriter writer, AclScopeName value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Acls.AclScopeNameTypeConverter`  
`class AclScopeNameTypeConverter : TypeConverter`  
_internal*; L60-93_
- inherits: `TypeConverter`
- desc: Converts AclScopeName objects to strings
- L63-66 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L69-76 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L79-82 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, [NotNullWhen(true)] Type? destinationType)` — (inheritdoc)
- L85-92 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Acls/IAclClaim.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Acls.IAclClaim`  
`public interface IAclClaim`  
_public; L8-19_
- desc: Claim for an ACL
- L13 _public* property_ `string Type { get; }` — Type of the claim
- L18 _public* property_ `string Value { get; }` — Value for the claim

### `Source/Programs/Shared/EpicGames.Horde/Agents/AgentId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Agents.AgentId`  
`public readonly struct AgentId : IEquatable<AgentId>, IComparable<AgentId>`  
_public; L19-123_
- attrs: `[JsonSchemaString] [LogValueType] [TypeConverter(typeof(AgentIdTypeConverter))] [JsonConverter(typeof(AgentIdJsonConverter))]`
- inherits: `IEquatable<AgentId>, IComparable<AgentId>`
- desc: Normalized hostname of an agent
- L24 _private* field_ `readonly string _name` — The text representing this id
- L30-74 _public ctor_ `public AgentId(string name)` — Constructor
- L77-80 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L83-86 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L89 _public method_ `public int CompareTo(AgentId other)` — (inheritdoc)
- L93-96 _public method_ `public bool Equals(AgentId other)` — (inheritdoc)
- L99-102 _public method_ `public override string ToString()` — (inheritdoc)
- L105 _public operator_ `public static bool operator ==(AgentId left, AgentId right)`
- L108 _public operator_ `public static bool operator !=(AgentId left, AgentId right)`
- L111 _public operator_ `public static bool operator <(AgentId left, AgentId right)`
- L114 _public operator_ `public static bool operator <=(AgentId left, AgentId right)`
- L117 _public operator_ `public static bool operator >(AgentId left, AgentId right)`
- L120 _public operator_ `public static bool operator >=(AgentId left, AgentId right)`

#### class `EpicGames.Horde.Agents.AgentIdTypeConverter`  
`sealed class AgentIdTypeConverter : TypeConverter`  
_internal*; L128-160_
- inherits: `TypeConverter`
- desc: Type converter from strings to PropertyFilter objects
- L131-134 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L137-140 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L143-146 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L149-159 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.Agents.AgentIdJsonConverter`  
`public sealed class AgentIdJsonConverter : JsonConverter<AgentId>`  
_public; L165-172_
- inherits: `JsonConverter<AgentId>`
- desc: Class which serializes AgentId objects to JSON
- L168 _public method_ `public override AgentId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L171 _public method_ `public override void Write(Utf8JsonWriter writer, AgentId value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Agents/AgentMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Agents.AgentStatus`  
`public enum AgentStatus`  
_public; L14-45_
- desc: Status of an agent. Must match RpcAgentStatus.
- L19 _public* enumerator_ `Unspecified = 0` — Unspecified state.
- L24 _public* enumerator_ `Ok = 1` — Agent is running normally.
- L29 _public* enumerator_ `Stopping = 2` — Agent is currently shutting down, and should not be assigned new leases.
- L34 _public* enumerator_ `Unhealthy = 3` — Agent is in an unhealthy state and should not be assigned new leases.
- L39 _public* enumerator_ `Stopped = 4` — Agent is currently stopped.
- L44 _public* enumerator_ `Busy = 5` — Agent is busy performing other work (eg. serving an interactive user)

#### record `EpicGames.Horde.Agents.UpdateAgentRequest`  
`public record UpdateAgentRequest(bool? Enabled = null, bool? Ephemeral = null, bool? RequestConform = null, bool? RequestFullConform = null, bool? RequestRestart = null, bool? RequestShutdown = null, bool? RequestForceRestart = null, List<string>? Pools = null, string? Comment = null)`  
_public; L59-59_
- desc: Parameters to update an agent

#### record `EpicGames.Horde.Agents.GetAgentLeaseResponse`  
`public record GetAgentLeaseResponse(LeaseId Id, LeaseId? ParentId, AgentId? AgentId, double? AgentRate, string Name, LogId? LogId, DateTime StartTime, DateTime? FinishTime, bool Executing, Dictionary<string, string>? Details, LeaseOutcome? Outcome, string[] OutcomeReasons, long? OutcomeReasonsFlags, LeaseState? State)`  
_public; L78-78_
- desc: Response for queries to find a particular lease within an agent

#### record `EpicGames.Horde.Agents.GetAgentWorkspaceResponse`  
`public record GetAgentWorkspaceResponse(string? Cluster, string? UserName, string Identifier, string Stream, List<string>? View, bool BIncremental, string? Method, long? MinScratchSpace, long? ConformDiskFreeSpace)`  
_public; L92-92_
- desc: Information about a workspace synced on an agent

#### record `EpicGames.Horde.Agents.GetAgentResponse`  
`public record GetAgentResponse(AgentId Id, string Name, bool Enabled, AgentStatus Status, double? Rate, SessionId? SessionId, bool Ephemeral, bool Online, bool Deleted, bool PendingConform, bool PendingFullConform, bool PendingRestart, bool PendingShutdown, string LastShutdownReason, DateTime LastConformTime, int? ConformAttemptCount, DateTime? NextConformTime, string? Version, List<string> Properties, Dictionary<string, int> Resources, DateTime? UpdateTime, DateTime? LastOnlineTime, List<string>? Pools, object? Capabilities, List<GetAgentLeaseResponse> Leases, List<GetAgentWorkspaceResponse> Workspaces, string? Comment)`  
_public; L124-124_
- desc: Information about an agent

#### record `EpicGames.Horde.Agents.GetAgentTelemetryResponse`  
`public record GetAgentTelemetryResponse(List<GetAgentTelemetrySampleResponse> Samples)`  
_public; L129-129_
- desc: Telemetry data for an agent

#### record `EpicGames.Horde.Agents.GetAgentTelemetrySampleResponse`  
`public record GetAgentTelemetrySampleResponse(DateTime Time, float UserCpu, float IdleCpu, float SystemCpu, int FreeRam, int UsedRam, int TotalRam, long WorkingFreeDisk, long WorkingTotalDisk, long SystemFreeDisk, long SystemTotalDisk)`  
_public; L134-134_
- desc: Telemetry data sample

### `Source/Programs/Shared/EpicGames.Horde/Agents/Enrollment/EnrollmentMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Agents.Enrollment.GetPendingAgentsResponse`  
`public record class GetPendingAgentsResponse(List<GetPendingAgentResponse> Agents)`  
_public; L10-10_
- desc: Updates an existing lease

#### record `EpicGames.Horde.Agents.Enrollment.GetPendingAgentResponse`  
`public record class GetPendingAgentResponse(string Key, string HostName, string Description)`  
_public; L18-18_
- desc: Information about an agent pending admission to the farm

#### record `EpicGames.Horde.Agents.Enrollment.ApproveAgentsRequest`  
`public record class ApproveAgentsRequest(List<ApproveAgentRequest> Agents)`  
_public; L24-24_
- desc: Approve an agent for admission to the farm

#### record `EpicGames.Horde.Agents.Enrollment.ApproveAgentRequest`  
`public record class ApproveAgentRequest(string Key, AgentId? AgentId)`  
_public; L31-31_
- desc: Approve an agent for admission to the farm

### `Source/Programs/Shared/EpicGames.Horde/Agents/KnownPropertyNames.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Agents.KnownPropertyNames`  
`public static class KnownPropertyNames`  
_public; L8-120_
- desc: Well-known property names for agents
- L13 _public const_ `public const string Id = "Id"` — The agent id
- L18 _public const_ `public const string Platform = "Platform"` — The UBT platform enum
- L23 _public const_ `public const string PlatformGroup = "PlatformGroup"` — The UBT platform group enum
- L28 _public const_ `public const string OsFamily = "OSFamily"` — The operating system (Linux, MacOS, Windows)
- L33 _public const_ `public const string OsFamilyCompatibility = "OSFamilyCompatibility"` — Compatible operating system (mainly for Linux WINE agents to advertise Windows support)
- L38 _public const_ `public const string SelfContained = "SelfContained"` — Whether the agent is a .NET self-contained app
- L43 _public const_ `public const string ToolId = "ToolId"` — Self-reported tool ID of an agent. Used by the server when pushing updates to select the correct tool package.
- L48 _public const_ `public const string Pool = "Pool"` — Pools that this agent belongs to
- L53 _public const_ `public const string RequestedPools = "RequestedPools"` — Pools requested by the agent to join when registering with server
- L58 _public const_ `public const string WorkingDiskTotalSize = "WorkingDiskTotalSize"` — The total size of the working drive, in bytes
- L63 _public const_ `public const string WorkingDiskFreeSpace = "WorkingDiskFreeSpace"` — Amount of available free space on the working drive, in bytes
- L68 _public const_ `public const string SystemDiskTotalSize = "SystemDiskTotalSize"` — The total size of the system drive, in bytes
- L73 _public const_ `public const string SystemDiskFreeSpace = "SystemDiskFreeSpace"` — Amount of available free space on the system drive, in bytes
- L78 _public const_ `public const string ComputeIp = "ComputeIp"` — IP address used for sending compute task payloads
- L83 _public const_ `public const string ComputePort = "ComputePort"` — Port used for sending compute task payloads
- L88 _public const_ `public const string ComputeProtocol = "ComputeProtocol"` — Protocol version for compute task payloads
- L93 _public const_ `public const string AwsInstanceId = "aws-instance-id"` — AWS: Instance ID
- L98 _public const_ `public const string AwsInstanceType = "aws-instance-type"` — AWS: Instance type
- L103 _public const_ `public const string WineEnabled = "WineEnabled"` — Whether the Wine compatibility layer is enabled (for running Windows applications on Linux)
- L108 _public const_ `public const string Trusted = "Trusted"` — Whether the agent is trusted (boolean)
- L114 _public const_ `public const string AutoUpdate = "AutoUpdate"` — Whether the agent want to receive software updates from the server (boolean) In some cases, an external script/process will take care of updating the agent (for example, Unreal Toolbox)
- L119 _public const_ `public const string LeaseId = "LeaseId"` — ID of current lease

### `Source/Programs/Shared/EpicGames.Horde/Agents/KnownResourceNames.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Agents.KnownResourceNames`  
`public static class KnownResourceNames`  
_public; L8-24_
- desc: Standard resource names
- L13 _public const_ `public const string LogicalCores = "LogicalCores"` — Number of logical cores including SMT cores (hyper-threading)
- L18 _public const_ `public const string PhysicalCores = "PhysicalCores"` — Number of physical cores
- L23 _public const_ `public const string Ram = "RAM"` — Amount of RAM, in GB

### `Source/Programs/Shared/EpicGames.Horde/Agents/Leases/LeaseId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Agents.Leases.LeaseId`  
`public readonly record struct LeaseId(BinaryId Id)`  
_public; L16-39_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<LeaseId, LeaseIdConverter>))] [BinaryIdConverter(typeof(LeaseIdConverter))]`
- desc: Identifier for a user
- L19-32 _public method_ `public static bool TryParse(string text, out LeaseId leaseId)` — (inheritdoc)
- L35 _public method_ `public static LeaseId Parse(string text)` — (inheritdoc)
- L38 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Leases.LeaseIdConverter`  
`class LeaseIdConverter : BinaryIdConverter<LeaseId>`  
_internal*; L44-51_
- inherits: `BinaryIdConverter<LeaseId>`
- desc: Converter to and from BinaryId instances.
- L47 _public method_ `public override LeaseId FromBinaryId(BinaryId id)` — (inheritdoc)
- L50 _public method_ `public override BinaryId ToBinaryId(LeaseId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Agents/Leases/LeaseMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Agents.Leases.LeaseOutcome`  
`public enum LeaseOutcome`  
_public; L12-33_
- desc: Outcome from a lease. Values must match lease_outcome.proto.
- L17 _public* enumerator_ `Unspecified = 0` — Default value.
- L22 _public* enumerator_ `Success = 1` — The lease was executed successfully
- L27 _public* enumerator_ `Failed = 2` — The lease was not executed succesfully, but cannot be run again.
- L32 _public* enumerator_ `Cancelled = 4` — The lease was cancelled by request

#### enum `EpicGames.Horde.Agents.Leases.LeaseOutcomeReason`  
`public enum LeaseOutcomeReason : long`  
_public; L39-79_
- attrs: `[Flags]`
- inherits: `long`
- desc: Reason for an outcome of a lease. Values must match lease_outcome.proto.
- L42 _public* enumerator_ `None = 0` — No specific reason
- L45 _public* enumerator_ `UnexpectedError = 1` — Lease finished due to an unhandled or unknown error
- L48 _public* enumerator_ `NonZeroExitCode = 2` — Lease finished with a non-zero exit code
- L51 _public* enumerator_ `UserInitiated = 4` — User initiated
- L54 _public* enumerator_ `ServerInitiated = 8` — Server initiated
- L57 _public* enumerator_ `AgentInitiated = 16` — Agent initiated
- L60 _public* enumerator_ `AgentSessionTerminated = 32` — Agent's session was terminated
- L63 _public* enumerator_ `AgentBusy = 64` — Agent became busy during lease (e.g non-Horde related work came up running on a workstation)
- L69 _public* enumerator_ `Duplicate = 128` — Lease deemed to be a duplicate For example two identical jobs executing or too many leases from a single user
- L72 _public* enumerator_ `TimedOut = 256` — Lease execution timed out
- L75 _public* enumerator_ `NoLongerNeeded = 512` — Lease no longer needed despite scheduled/started
- L78 _public* enumerator_ `NoReasonReported = 1024` — Lease was cancelled but no reason was reported by the agent

#### enum `EpicGames.Horde.Agents.Leases.LeaseState`  
`public enum LeaseState`  
_public; L84-110_
- desc: State of a lease. Values must match lease_state.proto.
- L89 _public* enumerator_ `Unspecified = 0` — Default value.
- L94 _public* enumerator_ `Pending = 1` — Set by the server when waiting for an agent to accept the lease. Once processed, the agent should transition the lease state to active.
- L99 _public* enumerator_ `Active = 2` — The agent is actively working on this lease.
- L104 _public* enumerator_ `Completed = 3` — The agent has finished working on this lease.
- L109 _public* enumerator_ `Cancelled = 4` — Set by the server to indicate that the lease should be cancelled.

#### class `EpicGames.Horde.Agents.Leases.UpdateLeaseRequest`  
`public class UpdateLeaseRequest`  
_public; L115-121_
- desc: Updates an existing lease
- L120 _public property_ `public bool? Aborted { get; set; }` — Mark this lease as aborted

### `Source/Programs/Shared/EpicGames.Horde/Agents/Metrics/Metrics.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Agents.Metrics.CpuMetrics`  
`public class CpuMetrics`  
_public; L10-32_
- desc: Metrics for CPU usage
- L15 _public property_ `public float User { get; set; }` — Percentage of time the CPU was busy executing code in user space
- L20 _public property_ `public float System { get; set; }` — Percentage of time the CPU was busy executing code in kernel space
- L25 _public property_ `public float Idle { get; set; }` — Percentage of time the CPU was idling
- L28-31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Metrics.MemoryMetrics`  
`public class MemoryMetrics`  
_public; L37-64_
- desc: Metrics for memory usage
- L42 _public property_ `public uint Total { get; set; }` — Total memory installed (kibibytes)
- L47 _public property_ `public uint Available { get; set; }` — Available memory (kibibytes)
- L52 _public property_ `public uint Used { get; set; }` — Used memory (kibibytes)
- L57 _public property_ `public float UsedPercentage { get; set; }` — Used memory (percentage)
- L60-63 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Metrics.DiskMetrics`  
`public class DiskMetrics`  
_public; L69-86_
- desc: Metrics for free disk space
- L74 _public property_ `public long FreeSpace { get; set; }` — Amount of free space on the drive
- L79 _public property_ `public long TotalSize { get; set; }` — Total size of the drive
- L82-85 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Metrics.CpuTimeMetrics`  
`public class CpuTimeMetrics`  
_public; L91-121_
- desc: Metrics for CPU time spent
- L96 _public property_ `public TimeSpan User { get; set; }` — CPU time spent in user mode
- L101 _public property_ `public TimeSpan System { get; set; }` — CPU time spent in system/kernel mode
- L106 _public property_ `public TimeSpan Idle { get; set; }` — CPU time spent idle
- L111-114 _public method_ `public CpuTimeMetrics Subtract(CpuTimeMetrics other)` — Subtract times from other object passed in
- L117-120 _public method_ `public override string ToString()` — (inheritdoc)

#### interface `EpicGames.Horde.Agents.Metrics.ISystemMetrics`  
`public interface ISystemMetrics`  
_public; L126-157_
- desc: OS-agnostic interface for retrieving system metrics (CPU, memory etc)
- L132 _public* method_ `CpuMetrics? GetCpu()` — Get CPU usage metrics
- L138 _public* method_ `CpuTimeMetrics? GetCpuTime()` — Get cumulative CPU time spent since system start
- L144 _public* method_ `MemoryMetrics? GetMemory()` — Get memory usage metrics
- L150 _public* method_ `DiskMetrics? GetWorkingDisk()` — Gets Working HDD metrics
- L156 _public* method_ `DiskMetrics? GetSystemDisk()` — Gets System HDD metrics

#### enum `EpicGames.Horde.Agents.Metrics.DriveType`  
`public enum DriveType`  
_public; L162-172_
- desc: Enum to handle separate drive types tracked by Horde telemetry
- L167 _public* enumerator_ `System = 0` — System-level drive
- L171 _public* enumerator_ `Working = 1` — Horde Working drive

### `Source/Programs/Shared/EpicGames.Horde/Agents/Pools/PoolId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Agents.Pools.PoolId`  
`public readonly record struct PoolId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<PoolId, PoolIdConverter>))] [StringIdConverter(typeof(PoolIdConverter))] [CbConverter(typeof(StringIdCbConverter<PoolId, PoolIdConverter>))]`
- desc: Identifier for a pool
- L23-25 _public ctor_ `public PoolId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Pools.PoolIdConverter`  
`class PoolIdConverter : StringIdConverter<PoolId>`  
_internal*; L37-44_
- inherits: `StringIdConverter<PoolId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override PoolId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(PoolId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Agents/Sessions/SessionId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Agents.Sessions.SessionId`  
`public readonly record struct SessionId(BinaryId Id)`  
_public; L16-43_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<SessionId, SessionIdConverter>))] [BinaryIdConverter(typeof(SessionIdConverter))]`
- desc: Identifier for a session
- L21 _public property_ `public static SessionId Empty { get; }` — Default empty value for session id
- L24 _public method_ `public static SessionId Parse(string text)` — (inheritdoc)
- L27-39 _public method_ `public static bool TryParse(string text, out SessionId id)` — (inheritdoc)
- L42 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Agents.Sessions.SessionIdConverter`  
`class SessionIdConverter : BinaryIdConverter<SessionId>`  
_internal*; L48-55_
- inherits: `BinaryIdConverter<SessionId>`
- desc: Converter to and from BinaryId instances.
- L51 _public method_ `public override SessionId FromBinaryId(BinaryId id)` — (inheritdoc)
- L54 _public method_ `public override BinaryId ToBinaryId(SessionId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Agents/Sessions/SessionMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Agents.Sessions.GetSessionResponse`  
`public record GetSessionResponse(SessionId Id, DateTime StartTime, DateTime? FinishTime, string? Version)`  
_public; L14-14_
- desc: Information about a session

### `Source/Programs/Shared/EpicGames.Horde/Agents/Utilization/UtilizationMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Agents.Telemetry.GetUtilizationDataResponse`  
`public class GetUtilizationDataResponse`  
_public; L15-46_
- desc: Response data for a utilization request
- L20 _public property_ `public DateTimeOffset StartTime { get; set; }` — Start hour
- L25 _public property_ `public DateTimeOffset FinishTime { get; set; }` — End hour
- L30 _public property_ `public List<GetUtilizationPoolDataResponse> Pools { get; set; }` — List of pools
- L35 _public property_ `public double AdminTime { get; set; }` — Total admin time
- L40 _public property_ `public double HibernatingTime { get; set; }` — Total hibernating time
- L45 _public property_ `public int NumAgents { get; set; }` — Total agents

#### class `EpicGames.Horde.Agents.Telemetry.GetUtilizationPoolDataResponse`  
`public class GetUtilizationPoolDataResponse`  
_public; L51-82_
- desc: Representation of an hour of time
- L56 _public property_ `public PoolId PoolId { get; set; }` — Pool id
- L61 _public property_ `public int NumAgents { get; set; }` — Number of agents in this pool
- L66 _public property_ `public double AdminTime { get; set; }` — Total time spent doing admin work
- L71 _public property_ `public double HibernatingTime { get; set; }` — Time spent hibernating
- L76 _public property_ `public double OtherTime { get; set; }` — Total time agents in this pool were doing work for other pools
- L81 _public property_ `public List<GetUtilizationStreamDataResponse> Streams { get; set; }` — List of streams

#### class `EpicGames.Horde.Agents.Telemetry.GetUtilizationStreamDataResponse`  
`public class GetUtilizationStreamDataResponse`  
_public; L87-98_
- desc: Represents one stream in one pool in one hour of telemetry
- L92 _public property_ `public StreamId StreamId { get; set; }` — Stream Id
- L97 _public property_ `public double Time { get; set; }` — Total time

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/ArtifactDescriptor.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ArtifactBackend`  
`public class ArtifactBackend`  
_public; L17-38_
- desc: Class that defines which backend to use to fetch an artifact
- L37 _public property_ `public BackendTypeEnum Type { get; set; }` — Enum indicating which type of backend it is and thus how these options should be interpreted

#### enum `EpicGames.Horde.Storage.ArtifactBackend.BackendTypeEnum`  
`public enum BackendTypeEnum`  
_public; L22-32_
- desc: The different types of supported backends
- L27 _public* enumerator_ `Horde` — The horde storage backend
- L31 _public* enumerator_ `Zen` — A zen based backend

#### class `EpicGames.Horde.Storage.ArtifactDescriptor`  
`public class ArtifactDescriptor`  
_public; L43-161_
- desc: Class which describes an artifact on Horde which can be serialized to JSON.
- L48 _public property_ `public string? Name { get; set; }` — Name of the artifact
- L53 _public property_ `public string? Type { get; set; }` — Type of the artifact
- L58 _public property_ `public string? Description { get; set; }` — Artifact description
- L63 _public property_ `public Uri BaseUrl { get; set; }` — Base URL for downloading from
- L68 _public property_ `public RefName RefName { get; set; }` — Name of the ref to download
- L73 _public property_ `public Uri? JobUrl { get; set; }` — Optional URL to the job that produced this artifact
- L78 _public property_ `public List<string>? Keys { get; set; }` — Keys associated with the artifact
- L83 _public property_ `public List<string>? Metadata { get; set; }` — Metadata associated with the artifact
- L88 _public property_ `public List<string>? Filter { get; set; }` — Filter for the files selected for download
- L93 _public property_ `public ArtifactBackend Backend { get; set; }` — Information about which backend system to use. Defaults to Horde.
- L98-102 _public ctor_ `public ArtifactDescriptor()` — Default constructor
- L107-115 _public ctor_ `public ArtifactDescriptor(Uri baseUrl, RefName refName, IReadOnlyCollection<string>? filter = null)` — Constructor
- L122-126 _public method_ `public static ArtifactDescriptor Deserialize(ReadOnlySpan<byte> data)` — Deserialize a descriptor from utf8 bytes
- L133-137 _public method_ `public static async Task<ArtifactDescriptor> ReadAsync(FileReference file, CancellationToken cancellationToken)` — Writes this descriptor to storage
- L143-149 _public method_ `public byte[] Serialize()` — Serializes a descriptor
- L156-160 _public method_ `public async Task WriteAsync(FileReference file, CancellationToken cancellationToken)` — Writes this descriptor to storage

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/ArtifactId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Artifacts.ArtifactId`  
`public readonly record struct ArtifactId(BinaryId Id)`  
_public; L16-23_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<ArtifactId, ArtifactIdConverter>))] [BinaryIdConverter(typeof(ArtifactIdConverter))]`
- desc: Unique id for an artifact
- L19 _public method_ `public static ArtifactId Parse(string text)` — (inheritdoc)
- L22 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Artifacts.ArtifactIdConverter`  
`class ArtifactIdConverter : BinaryIdConverter<ArtifactId>`  
_internal*; L28-35_
- inherits: `BinaryIdConverter<ArtifactId>`
- desc: Converter class to and from ObjectId values
- L31 _public method_ `public override ArtifactId FromBinaryId(BinaryId id)` — (inheritdoc)
- L34 _public method_ `public override BinaryId ToBinaryId(ArtifactId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/ArtifactMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Artifacts.CreateArtifactRequest`  
`public record CreateArtifactRequest(ArtifactName Name, ArtifactType Type, string? Description, StreamId? StreamId, List<string> Keys, List<string> Metadata)`  
_public; L24-46_
- desc: Creates a new artifact
- L30-34 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — Legacy Perforce changelist number.
- L35 _private* field_ `int? _change`
- L40-44 _public property_ `public CommitId CommitId { get; set; }` — Commit for the new artifact
- L45 _private* field_ `CommitId? _commitId`

#### record `EpicGames.Horde.Artifacts.CreateArtifactResponse`  
`public record CreateArtifactResponse(ArtifactId ArtifactId, CommitIdWithOrder CommitId, NamespaceId NamespaceId, RefName RefName, RefName? PrevRefName, string Token)`  
_public; L57-57_
- desc: Information about a created artifact

#### enum `EpicGames.Horde.Artifacts.DownloadArtifactFormat`  
`public enum DownloadArtifactFormat`  
_public; L62-73_
- desc: Type of data to download for an artifact
- L67 _public* enumerator_ `Zip` — Download as a zip file
- L72 _public* enumerator_ `Ugs` — Download as a UGS link

#### class `EpicGames.Horde.Artifacts.GetArtifactResponse`  
`public class GetArtifactResponse`  
_public; L78-157_
- desc: Describes an artifact
- L81 _public property_ `public ArtifactId Id { get; set; }` — (inheritdoc)
- L84 _public property_ `public ArtifactName Name { get; set; }` — (inheritdoc)
- L87 _public property_ `public ArtifactType Type { get; set; }` — (inheritdoc)
- L90 _public property_ `public string? Description { get; set; }` — (inheritdoc)
- L93 _public property_ `public StreamId StreamId { get; set; }` — (inheritdoc)
- L99-103 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — Change number
- L104 _private* field_ `int? _change`
- L107-111 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — (inheritdoc)
- L112 _private* field_ `CommitIdWithOrder? _commitId`
- L115 _public property_ `public IReadOnlyList<string> Keys { get; set; }` — (inheritdoc)
- L118 _public property_ `public IReadOnlyList<string> Metadata { get; set; }` — (inheritdoc)
- L121 _public property_ `public NamespaceId NamespaceId { get; set; }` — (inheritdoc)
- L124 _public property_ `public RefName RefName { get; set; }` — (inheritdoc)
- L127 _public property_ `public DateTime CreatedAtUtc { get; set; }` — (inheritdoc)
- L133-137 _public ctor_ `public GetArtifactResponse()` — attrs: `[JsonConstructor]` — Default constructor
- L143-156 _public ctor_ `public GetArtifactResponse(IArtifact artifact)` — Constructor

#### class `EpicGames.Horde.Artifacts.FindArtifactsResponse`  
`public class FindArtifactsResponse`  
_public; L162-168_
- desc: Result of an artifact search
- L167 _public property_ `public List<GetArtifactResponse> Artifacts { get; set; }` — List of artifacts matching the search criteria

#### class `EpicGames.Horde.Artifacts.GetArtifactFileEntryResponse`  
`public class GetArtifactFileEntryResponse`  
_public; L173-199_
- desc: Describes a file within an artifact
- L178 _public property_ `public string Name { get; }` — Name of this file
- L183 _public property_ `public long Length { get; }` — Length of this entry
- L188 _public property_ `public IoHash Hash { get; }` — Hash of the target node
- L193-198 _public ctor_ `public GetArtifactFileEntryResponse(string name, long length, IoHash hash)` — Constructor

#### class `EpicGames.Horde.Artifacts.GetArtifactDirectoryEntryResponse`  
`public class GetArtifactDirectoryEntryResponse : GetArtifactDirectoryResponse`  
_public; L204-230_
- inherits: `GetArtifactDirectoryResponse`
- desc: Describes a file within an artifact
- L209 _public property_ `public string Name { get; }` — Name of this file
- L214 _public property_ `public long Length { get; }` — Length of this entry
- L219 _public property_ `public IoHash Hash { get; }` — Hash of the target node
- L224-229 _public ctor_ `public GetArtifactDirectoryEntryResponse(string name, long length, IoHash hash)` — Constructor

#### class `EpicGames.Horde.Artifacts.GetArtifactDirectoryResponse`  
`public class GetArtifactDirectoryResponse`  
_public; L235-246_
- desc: Describes a directory within an artifact
- L240 _public property_ `public List<GetArtifactDirectoryEntryResponse>? Directories { get; set; }` — Names of sub-directories
- L245 _public property_ `public List<GetArtifactFileEntryResponse>? Files { get; set; }` — Files within the directory

#### class `EpicGames.Horde.Artifacts.CreateZipRequest`  
`public class CreateZipRequest`  
_public; L251-257_
- desc: Request to create a zip file with artifact data
- L256 _public property_ `public List<string> Filter { get; set; }` — Filter lines for the zip. Uses standard FileFilter syntax.

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/ArtifactName.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Artifacts.ArtifactName`  
`public readonly record struct ArtifactName(StringId Id)`  
_public; L15-25_
- attrs: `[JsonSchemaString] [StringIdConverter(typeof(ArtifactNameConverter))] [TypeConverter(typeof(StringIdTypeConverter<ArtifactName, ArtifactNameConverter>))]`
- desc: Name of an artifact
- L21 _public ctor_ `public ArtifactName(string id) : this(new StringId(id))` — Constructor
- L24 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Artifacts.ArtifactNameConverter`  
`class ArtifactNameConverter : StringIdConverter<ArtifactName>`  
_internal*; L30-37_
- inherits: `StringIdConverter<ArtifactName>`
- desc: Converter to and from StringId instances.
- L33 _public method_ `public override ArtifactName FromStringId(StringId id)` — (inheritdoc)
- L36 _public method_ `public override StringId ToStringId(ArtifactName value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/ArtifactType.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Artifacts.ArtifactType`  
`public readonly record struct ArtifactType(StringId Id)`  
_public; L17-52_
- attrs: `[JsonSchemaString] [StringIdConverter(typeof(ArtifactTypeConverter))] [TypeConverter(typeof(StringIdTypeConverter<ArtifactType, ArtifactTypeConverter>))]`
- desc: Type of an artifact
- L22 _public property_ `public static ArtifactType Unknown { get; }` — Default artifact type
- L27 _public property_ `public static ArtifactType StepOutput { get; }` — Output from a build step
- L32 _public property_ `public static ArtifactType StepSaved { get; }` — Captured state from the machine executing a build step
- L37 _public property_ `public static ArtifactType StepTrace { get; }` — Traces from the machine executing a build step
- L42 _public property_ `public static ArtifactType StepTestData { get; }` — Test data generated by a machine executing a build step
- L48 _public ctor_ `public ArtifactType(string id) : this(new StringId(id))` — Constructor
- L51 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Artifacts.ArtifactTypeConverter`  
`class ArtifactTypeConverter : StringIdConverter<ArtifactType>`  
_internal*; L57-64_
- inherits: `StringIdConverter<ArtifactType>`
- desc: Converter to and from StringId instances.
- L60 _public method_ `public override ArtifactType FromStringId(StringId id)` — (inheritdoc)
- L63 _public method_ `public override StringId ToStringId(ArtifactType value)` — (inheritdoc)

#### class `EpicGames.Horde.Artifacts.ArtifactTypeNotFoundException`  
`public sealed class ArtifactTypeNotFoundException : Exception`  
_public; L69-90_
- inherits: `Exception`
- desc: Exception thrown to indicate that an artifact type does not exist
- L74 _public property_ `public StreamId StreamId { get; }` — The stream containing the artifact
- L79 _public property_ `public ArtifactType ArtifactType { get; }` — The missing artifact type
- L84-89 _public ctor_ `public ArtifactTypeNotFoundException(StreamId streamId, ArtifactType artifactType) : base($"Artifact type {artifactType} not found in stream {streamId}")` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/HttpArtifactCollection.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Artifacts.HttpArtifactCollection`  
`class HttpArtifactCollection : IArtifactCollection`  
_internal*; L16-161_
- inherits: `IArtifactCollection`
- L116 _private* field_ `readonly IHordeClient _hordeClient`
- L118 _public ctor_ `public HttpArtifactCollection(IHordeClient hordeClient)`
- L121-125 _private* method_ `IBlobRef<DirectoryNode> Open(Artifact artifact)`
- L128-134 _public method_ `public async Task<IArtifactBuilder> CreateAsync(ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitId commitId, IEnumerable<string> keys, IEnumerable<string> metadata, CancellationToken cancellationToken = default)` — (inheritdoc)
- L137-146 _public method_ `public async IAsyncEnumerable<IArtifact> FindAsync(ArtifactId[]? ids = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — (inheritdoc)
- L148-152 _private* method_ `async Task DeleteAsync(ArtifactId artifactId, CancellationToken cancellationToken = default)`
- L155-160 _public method_ `public async Task<IArtifact?> GetAsync(ArtifactId artifactId, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Artifacts.HttpArtifactCollection.Artifact`  
`class Artifact : IArtifact`  
_private*; L19-61_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IArtifact`
- L21 _private* field_ `readonly HttpArtifactCollection _collection`
- L23-25 _public ctor_ `public Artifact(HttpArtifactCollection collection, GetArtifactResponse response) : this(collection, response.Id, response.Name, response.Type, response.Description, response.StreamId, response.CommitId, response.Keys, response.Metadata, response.NamespaceId, response.RefName, response.CreatedAtUtc)`
- L27-42 _public ctor_ `public Artifact(HttpArtifactCollection collection, ArtifactId id, ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitIdWithOrder commitId, IReadOnlyList<string> keys, IReadOnlyList<string> metadata, NamespaceId namespaceId, RefName refName, DateTime createdAtUtc)`
- L44 _public property_ `public ArtifactId Id { get; }`
- L45 _public property_ `public ArtifactName Name { get; }`
- L46 _public property_ `public ArtifactType Type { get; }`
- L47 _public property_ `public string? Description { get; }`
- L48 _public property_ `public StreamId StreamId { get; }`
- L49 _public property_ `public CommitIdWithOrder CommitId { get; }`
- L50 _public property_ `public IReadOnlyList<string> Keys { get; }`
- L51 _public property_ `public IReadOnlyList<string> Metadata { get; }`
- L52 _public property_ `public NamespaceId NamespaceId { get; }`
- L53 _public property_ `public RefName RefName { get; }`
- L54 _public property_ `public DateTime CreatedAtUtc { get; }`
- L56 _public property_ `public IBlobRef<DirectoryNode> Content => ...`
- L59 _public method_ `public Task DeleteAsync(CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Artifacts.HttpArtifactCollection.ArtifactBuilder`  
`class ArtifactBuilder : IArtifactBuilder`  
_private*; L63-114_
- inherits: `IArtifactBuilder`
- L67 _private* field_ `readonly Artifact _artifact`
- L68 _private* field_ `readonly CreateArtifactResponse _response`
- L69 _private* field_ `readonly IStorageNamespace _namespace`
- L70 _private* field_ `readonly List<AliasInfo> _aliases = []`
- L72 _public property_ `public ArtifactId Id => ...`
- L73 _public property_ `public ArtifactName Name => ...`
- L74 _public property_ `public ArtifactType Type => ...`
- L75 _public property_ `public string? Description => ...`
- L76 _public property_ `public StreamId StreamId => ...`
- L77 _public property_ `public CommitIdWithOrder CommitId => ...`
- L78 _public property_ `public IReadOnlyList<string> Keys => ...`
- L79 _public property_ `public IReadOnlyList<string> Metadata => ...`
- L80 _public property_ `public NamespaceId NamespaceId => ...`
- L81 _public property_ `public RefName RefName => ...`
- L83-88 _public ctor_ `public ArtifactBuilder(HttpArtifactCollection collection, Artifact artifact, CreateArtifactResponse response)`
- L91-95 _public method_ `public Task AddAliasAsync(string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L98-109 _public method_ `public async Task<IArtifact> CompleteAsync(IHashedBlobRef blobRef, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112 _public method_ `public IBlobWriter CreateBlobWriter()` — (inheritdoc)

#### record `EpicGames.Horde.Artifacts.HttpArtifactCollection.ArtifactBuilder.AliasInfo`  
`record class AliasInfo(string Name, IBlobRef BlobRef, int Rank, ReadOnlyMemory<byte> Data)`  
_private*; L65-65_

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/IArtifact.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Artifacts.IArtifact`  
`public interface IArtifact`  
_public; L17-84_
- desc: Information about an artifact
- L22 _public* property_ `ArtifactId Id { get; }` — Identifier for the Artifact. Randomly generated.
- L27 _public* property_ `ArtifactName Name { get; }` — Name of the artifact
- L32 _public* property_ `ArtifactType Type { get; }` — Type of artifact
- L37 _public* property_ `string? Description { get; }` — Description for the artifact
- L42 _public* property_ `StreamId StreamId { get; }` — Identifier for the stream that produced the artifact
- L47 _public* property_ `CommitIdWithOrder CommitId { get; }` — Change that the artifact corresponds to
- L52 _public* property_ `IReadOnlyList<string> Keys { get; }` — Keys used to collate artifacts
- L57 _public* property_ `IReadOnlyList<string> Metadata { get; }` — Metadata for the artifact
- L62 _public* property_ `NamespaceId NamespaceId { get; }` — Storage namespace containing the data
- L67 _public* property_ `RefName RefName { get; }` — Name of the ref containing the root data object
- L72 _public* property_ `DateTime CreatedAtUtc { get; }` — Time at which the artifact was created
- L77 _public* property_ `IBlobRef<DirectoryNode> Content { get; }` — Handle to the artifact data
- L83 _public* method_ `Task DeleteAsync(CancellationToken cancellationToken)` — Deletes this artifact

#### interface `EpicGames.Horde.Artifacts.IArtifactBuilder`  
`public interface IArtifactBuilder`  
_public; L89-143_
- desc: Used to write data into an artifact
- L92 _public* property_ `ArtifactId Id { get; }` — (inheritdoc)
- L95 _public* property_ `ArtifactName Name { get; }` — (inheritdoc)
- L98 _public* property_ `ArtifactType Type { get; }` — (inheritdoc)
- L101 _public* property_ `string? Description { get; }` — (inheritdoc)
- L104 _public* property_ `StreamId StreamId { get; }` — (inheritdoc)
- L107 _public* property_ `CommitIdWithOrder CommitId { get; }` — (inheritdoc)
- L110 _public* property_ `IReadOnlyList<string> Keys { get; }` — (inheritdoc)
- L113 _public* property_ `IReadOnlyList<string> Metadata { get; }` — (inheritdoc)
- L116 _public* property_ `NamespaceId NamespaceId { get; }` — (inheritdoc)
- L119 _public* property_ `RefName RefName { get; }` — (inheritdoc)
- L124 _public* method_ `IBlobWriter CreateBlobWriter()` — Creates a writer for new artifact blobs
- L134 _public* method_ `Task AddAliasAsync(string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — Adds an alias to a given blob
- L142 _public* method_ `Task<IArtifact> CompleteAsync(IHashedBlobRef blobRef, CancellationToken cancellationToken = default)` — Finish writing the artifact data

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/IArtifactCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Artifacts.IArtifactCollection`  
`public interface IArtifactCollection`  
_public; L14-52_
- desc: Interface for a collection of artifacts
- L28 _public* method_ `Task<IArtifactBuilder> CreateAsync(ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitId commitId, IEnumerable<string> keys, IEnumerable<string> metadata, CancellationToken cancellationToken = default)` — Creates a new artifact
- L43 _public* method_ `IAsyncEnumerable<IArtifact> FindAsync(ArtifactId[]? ids = null, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, CancellationToken cancellationToken = default)` — Finds artifacts with the given keys.
- L51 _public* method_ `Task<IArtifact?> GetAsync(ArtifactId artifactId, CancellationToken cancellationToken = default)` — Gets an artifact by ID

#### class `EpicGames.Horde.Artifacts.ArtifactCollectionExtensions`  
`public static class ArtifactCollectionExtensions`  
_public; L57-74_
- desc: Extension methods for artifacts
- L72 _public method_ `public static IAsyncEnumerable<IArtifact> FindAsync(this IArtifactCollection artifactCollection, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, CancellationToken cancellationToken = default)` — Finds artifacts with the given keys.

### `Source/Programs/Shared/EpicGames.Horde/Artifacts/UnsyncMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Artifacts.GetUnsyncDataRequest`  
`public class GetUnsyncDataRequest`  
_public; L14-33_
- desc: Request to return a set of blobs for Unsync
- L20 _public property_ `public string? HashStrong { get; set; }` — attrs: `[JsonPropertyName("hash_strong")]` — The strong hash algorithm
- L26 _public property_ `public List<string> Blocks { get; set; }` — attrs: `[JsonPropertyName("blocks")]` — Files to retrieve
- L32 _public property_ `public List<GetUnsyncFileRequest> Files { get; set; }` — attrs: `[JsonPropertyName("files")]` — Files to retrieve

#### class `EpicGames.Horde.Artifacts.GetUnsyncFileRequest`  
`public class GetUnsyncFileRequest`  
_public; L38-49_
- desc: Requests a set of blobs from a particular file
- L43 _public property_ `public string Name { get; set; }` — Path to the file
- L48 _public property_ `public List<GetUnsyncBlockRequest> Blocks { get; set; }` — Blobs to return

#### class `EpicGames.Horde.Artifacts.GetUnsyncBlockRequest`  
`public class GetUnsyncBlockRequest`  
_public; L54-61_
- desc: Requests a block of data
- L60 _public property_ `public string? Hash { get; set; }` — attrs: `[JsonPropertyName("hash_strong")]` — Hash of the block

### `Source/Programs/Shared/EpicGames.Horde/Auth/AuthExtensions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Auth.HttpServiceClientOptions`  
`public class HttpServiceClientOptions : IOAuthOptions, ITokenAuthOptions`  
_public; L13-46_
- inherits: `IOAuthOptions, ITokenAuthOptions`
- desc: Base class for configuring HTTP service clients
- L19 _public property_ `public Uri Url { get; set; }` — attrs: `[Required]` — Base address for http requests
- L24 _public property_ `public Uri? AuthUrl { get; set; }` — (inheritdoc)
- L27 _public property_ `public string GrantType { get; set; }` — (inheritdoc)
- L30 _public property_ `public string ClientId { get; set; }` — (inheritdoc)
- L33 _public property_ `public string ClientSecret { get; set; }` — (inheritdoc)
- L36 _public property_ `public string Scope { get; set; }` — (inheritdoc)
- L43 _public property_ `public string Token { get; set; }` — (inheritdoc)

#### class `EpicGames.Horde.Auth.AuthExtensions`  
`internal static class AuthExtensions`  
_internal; L48-85_
- L50-68 _public method_ `public static void AddHttpClientWithAuth<TClient, TImplementation>(this IServiceCollection services, Func<IServiceProvider, HttpServiceClientOptions> getOptions) where TClient : class where TImplementation : class, TClient`
- L70-84 _private* method_ `static HttpMessageHandler CreateMessageHandler<TImplementation>(IServiceProvider serviceProvider, HttpServiceClientOptions options)`

### `Source/Programs/Shared/EpicGames.Horde/Auth/HordeAuthConfigProvider.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Auth.HordeAuthConfigProvider`  
`internal sealed class HordeAuthConfigProvider( HttpMessageHandler httpMessageHandler, Uri serverUri, ILogger<HordeAuthConfigProvider> logger ) : IOidcAuthStateConfig, IDisposable`  
_internal; L18-71_
- L24-28 _public method_ `public async Task<string> GetOidcProviderAsync(CancellationToken cancellationToken)`
- L30 _public method_ `public static string GetOidcProvider(GetAuthConfigResponse authConfig)`
- L32-59 _public method_ `public async Task<GetAuthConfigResponse> GetAuthConfigResponseAsync(CancellationToken cancellationToken)`
- L61-64 _public method_ `public void Dispose()`
- L67 _private field_ `private readonly HttpMessageHandler _httpMessageHandler = httpMessageHandler` — attrs: `[SuppressMessage("Usage", "CA2213:Disposable fields should be disposed", Justification = "Lifetime is managed by caller")]`
- L68 _private field_ `private readonly Uri _serverUri = serverUri`
- L69 _private field_ `private readonly ILogger<HordeAuthConfigProvider> _logger = logger`
- L70 _private field_ `private readonly MemoryCache _memoryCache = new(Options.Create(new MemoryCacheOptions()))`

### `Source/Programs/Shared/EpicGames.Horde/Auth/HordeOidcTokenManager.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Auth.HordeOidcTokenManager`  
`internal sealed class HordeOidcTokenManager( HordeAuthConfigProvider hordeAuthConfigProvider, ITokenStore tokenStore, ILogger<HordeOidcTokenManager>? logger = null, ILoggerFactory? loggerFactory = null ) : IOidcTokenManager`  
_internal; L16-120_
- L23-34 _public method_ `public async Task<IOidcTokenInfo> GetAccessToken(string providerIdentifier, CancellationToken cancellationToken)`
- L36-47 _public method_ `public async Task<OidcStatus> GetStatusForProvider(string providerIdentifier, CancellationToken cancellationToken)`
- L49-61 _public method_ `public async Task<IOidcTokenInfo> LoginAsync(string providerIdentifier, CancellationToken cancellationToken)`
- L63-75 _public method_ `public async Task<IOidcTokenInfo?> TryGetAccessToken(string providerIdentifier, CancellationToken cancellationToken)`
- L77 _private field_ `private readonly HordeAuthConfigProvider _hordeAuthConfigProvider = hordeAuthConfigProvider`
- L78 _private field_ `private readonly ITokenStore _tokenStore = tokenStore`
- L79 _private field_ `private readonly ILogger<HordeOidcTokenManager>? _logger = logger`
- L80 _private field_ `private readonly ILoggerFactory? _loggerFactory = loggerFactory`
- L81 _private field_ `private readonly ConcurrentDictionary<string, OidcTokenManager> _cachedManagers = ...`
- L81 _private field_ `private readonly ConcurrentDictionary< _cachedManagers = new(StringComparer.OrdinalIgnoreCase)`
- L83-86 _private method_ `private OidcTokenManager GetOrCreateOidcTokenManager(string providerIdentifier, GetAuthConfigResponse authConfig)`
- L88-119 _private method_ `private OidcTokenManager CreateOidcTokenManager(string providerIdentifier, GetAuthConfigResponse authConfig)`

### `Source/Programs/Shared/EpicGames.Horde/Auth/HordeStaticAccessTokenProvider.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Auth.HordeStaticAccessTokenProvider`  
`internal sealed class HordeStaticAccessTokenProvider(IOptionsSnapshot<HordeOptions> options) : IStaticAccessTokenProvider`  
_internal; L9-42_
- L11-39 _public property_ `public string? AccessToken { get; }`
- L41 _private field_ `private readonly IOptionsSnapshot<HordeOptions> _options = options`

### `Source/Programs/Shared/EpicGames.Horde/Auth/OAuthHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Auth.AuthenticationException`  
`public class AuthenticationException : Exception`  
_public; L18-27_
- inherits: `Exception`
- desc: Exception thrown due to failed authorization
- L23-26 _public ctor_ `public AuthenticationException(string message, Exception? innerException) : base(message, innerException)` — Constructor

#### interface `EpicGames.Horde.Auth.IOAuthOptions`  
`public interface IOAuthOptions`  
_public; L32-58_
- desc: Options for authenticating particular requests
- L37 _public* property_ `Uri? AuthUrl { get; }` — Url of the auth server
- L42 _public* property_ `string GrantType { get; }` — Type of grant
- L47 _public* property_ `string ClientId { get; }` — Client id
- L52 _public* property_ `string ClientSecret { get; }` — Client secret
- L57 _public* property_ `string Scope { get; }` — Scope of the token

#### class `EpicGames.Horde.Auth.OAuthHandler`  
`public class OAuthHandler<T> : HttpClientHandler`  
_public; L63-144_
- inherits: `HttpClientHandler`
- desc: Http message handler which adds an OAuth authorization header using a cached/periodically refreshed bearer token
- L74 _private* field_ `readonly HttpClient _client`
- L75 _private* field_ `readonly IOAuthOptions _options`
- L76 _private* field_ `string _cachedAccessToken = String.Empty`
- L77 _private* field_ `DateTime _expiresAt = DateTime.MinValue`
- L84-88 _public ctor_ `public OAuthHandler(HttpClient client, IOAuthOptions options)` — Constructor
- L91-100 _protected method_ `protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)` — (inheritdoc)
- L106-143 _private* method_ `async Task UpdateAccessTokenAsync(CancellationToken cancellationToken)` — Updates the current access token

#### class `EpicGames.Horde.Auth.OAuthHandler.ClientCredentialsResponse`  
`class ClientCredentialsResponse`  
_private*; L66-72_
- attrs: `[SuppressMessage("Style", "IDE1006:Naming Styles")]`
- L68 _public property_ `public string? access_token { get; set; }`
- L69 _public property_ `public string? token_type { get; set; }`
- L70 _public property_ `public int? expires_in { get; set; }`
- L71 _public property_ `public string? scope { get; set; }`

#### class `EpicGames.Horde.Auth.OAuthHandlerFactory`  
`public class OAuthHandlerFactory`  
_public; L149-168_
- desc: Factory for creating OAuth2AuthProvider instances from a set of options
- L151 _private* field_ `readonly HttpClient _httpClient`
- L157-160 _public ctor_ `public OAuthHandlerFactory(HttpClient httpClient)` — Constructor
- L167 _public method_ `public OAuthHandler<T> Create<T>(IOAuthOptions options)` — Create an instance of the auth provider

### `Source/Programs/Shared/EpicGames.Horde/Auth/TokenHandler.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Auth.ITokenAuthOptions`  
`public interface ITokenAuthOptions`  
_public; L12-18_
- desc: Options for authenticating particular requests
- L17 _public* property_ `string Token { get; }` — Bearer token for auth

#### class `EpicGames.Horde.Auth.TokenHandler`  
`public class TokenHandler<T> : HttpClientHandler`  
_public; L23-42_
- inherits: `HttpClientHandler`
- desc: Http message handler which adds an OAuth authorization header using a cached/periodically refreshed bearer token
- L25 _private* field_ `readonly ITokenAuthOptions _options`
- L31-34 _public ctor_ `public TokenHandler(ITokenAuthOptions options)` — Constructor
- L37-41 _protected method_ `protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/BinaryId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.BinaryId`  
`public readonly struct BinaryId : IEquatable<BinaryId>, IComparable<BinaryId>`  
_public; L20-236_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(BinaryIdJsonConverter))] [TypeConverter(typeof(BinaryIdTypeConverter))]`
- inherits: `IEquatable<BinaryId>, IComparable<BinaryId>`
- desc: Normalized string identifier for a resource
- L22 _private* field_ `readonly int _a`
- L23 _private* field_ `readonly int _b`
- L24 _private* field_ `readonly int _c`
- L29 _public const_ `public const int NumBytes = 12` — Number of bytes in the identifier
- L34 _public const_ `public const int NumChars = NumBytes * 2` — Number of characters when formatted as a string
- L40-45 _public ctor_ `public BinaryId(ReadOnlySpan<byte> bytes)` — Constructor
- L50-58 _public method_ `public static BinaryId Parse(string text)` — Parse a binary id from a string
- L63 _public method_ `public static BinaryId Parse(Utf8String text)` — Parse a binary id from a string
- L68-76 _public method_ `public static BinaryId Parse(ReadOnlySpan<byte> text)` — Parse a binary id from a string
- L81-94 _public method_ `public static bool TryParse(string text, out BinaryId result)` — Attempt to parse a binary id from a string
- L99 _public method_ `public static bool TryParse(Utf8String text, out BinaryId result)` — Attempt to parse a binary id from a string
- L104-117 _public method_ `public static bool TryParse(ReadOnlySpan<byte> text, out BinaryId result)` — Attempt to parse a binary id from a string
- L122-135 _public method_ `public static bool TryParse(ReadOnlySpan<char> text, out BinaryId result)` — Attempt to parse a binary id from a string
- L140 _public property_ `public bool IsEmpty => ...` — Checks whether this BinaryId is set
- L143 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L146 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L149 _public method_ `public bool Equals(BinaryId other)` — (inheritdoc)
- L152-157 _public method_ `public override string ToString()` — (inheritdoc)
- L162-167 _public method_ `public Utf8String ToUtf8String()` — Format this id as a sequence of UTF8 characters
- L172-177 _public method_ `public void ToUtf8String(Span<byte> chars)` — Format this id as a sequence of UTF8 characters
- L182-187 _public method_ `public byte[] ToByteArray()` — Format this id as a sequence of UTF8 characters
- L192-197 _public method_ `public void ToByteArray(Span<byte> bytes)` — Format this id as a sequence of UTF8 characters
- L200-212 _public method_ `public int CompareTo(BinaryId other)` — (inheritdoc)
- L220 _public operator_ `public static bool operator ==(BinaryId left, BinaryId right)` — Compares two binary ids for equality
- L228 _public operator_ `public static bool operator !=(BinaryId left, BinaryId right)` — Compares two binary ids for inequality
- L231 _public operator_ `public static bool operator <(BinaryId left, BinaryId right)`
- L232 _public operator_ `public static bool operator <=(BinaryId left, BinaryId right)`
- L233 _public operator_ `public static bool operator >(BinaryId left, BinaryId right)`
- L234 _public operator_ `public static bool operator >=(BinaryId left, BinaryId right)`

#### class `EpicGames.Horde.BinaryIdJsonConverter`  
`sealed class BinaryIdJsonConverter : JsonConverter<BinaryId>`  
_internal*; L241-253_
- inherits: `JsonConverter<BinaryId>`
- desc: Class which serializes BinaryId types
- L244 _public method_ `public override BinaryId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L247-252 _public method_ `public override void Write(Utf8JsonWriter writer, BinaryId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.BinaryIdTypeConverter`  
`sealed class BinaryIdTypeConverter : TypeConverter`  
_internal*; L258-271_
- inherits: `TypeConverter`
- desc: Class which serializes BinaryId types
- L261 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L264 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L267 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L270 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/BinaryIdConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.BinaryIdConverter`  
`public abstract class BinaryIdConverter<T> where T : struct`  
_public; L18-29_
- constraints: `where T : struct`
- desc: Base class for converting to and from types containing a BinaryId. Useful pattern for reducing boilerplate with strongly typed records.
- L23 _public method_ `public abstract BinaryId ToBinaryId(T value)` — Converts a type to a BinaryId
- L28 _public method_ `public abstract T FromBinaryId(BinaryId id)` — Constructs a type from a BinaryId

#### class `EpicGames.Horde.BinaryIdConverterAttribute`  
`public sealed class BinaryIdConverterAttribute : Attribute`  
_public; L35-46_
- attrs: `[AttributeUsage(AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute declaring a BinaryIdConverter{T} for a particular type
- L40 _public property_ `public Type ConverterType { get; }` — The converter type
- L45 _public ctor_ `public BinaryIdConverterAttribute(Type converterType)` — Constructor

#### class `EpicGames.Horde.BinaryIdCbConverter`  
`public sealed class BinaryIdCbConverter<TValue, TConverter> : CbConverter<TValue> where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`  
_public; L51-72_
- inherits: `CbConverter<TValue>`
- constraints: `where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`
- desc: Converter to compact binary objects
- L53 _private* field_ `readonly TConverter _converter = new()`
- L56-59 _public method_ `public override TValue Read(CbField field)` — (inheritdoc)
- L62-65 _public method_ `public override void Write(CbWriter writer, TValue value)` — (inheritdoc)
- L68-71 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, TValue value)` — (inheritdoc)

#### class `EpicGames.Horde.BinaryIdTypeConverter`  
`public sealed class BinaryIdTypeConverter<TValue, TConverter> : TypeConverter where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`  
_public; L77-117_
- inherits: `TypeConverter`
- constraints: `where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`
- desc: Class which serializes types with a BinaryIdConverter{T} to Json
- L79 _private* field_ `readonly TConverter _converter = new()`
- L82-85 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L88-99 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L102 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L105-116 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.BinaryIdJsonConverter`  
`public sealed class BinaryIdJsonConverter<TValue, TConverter> : JsonConverter<TValue> where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`  
_public; L122-138_
- inherits: `JsonConverter<TValue>`
- constraints: `where TValue : struct where TConverter : BinaryIdConverter<TValue>, new()`
- desc: Class which serializes types with a BinaryIdConverter{T} to Json
- L124 _private* field_ `readonly TConverter _converter = new()`
- L127 _public method_ `public override TValue Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L130-137 _public method_ `public override void Write(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.BinaryIdJsonConverterFactory`  
`public sealed class BinaryIdJsonConverterFactory : JsonConverterFactory`  
_public; L143-158_
- inherits: `JsonConverterFactory`
- desc: Creates constructors for types with a BinaryIdConverter{T} to Json
- L146 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L149-157 _public method_ `public override JsonConverter? CreateConverter(Type type, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/BuildHealth/BuildHealthFilterId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.BuildHealth.BuildHealthFilterId`  
`public readonly record struct BuildHealthFilterId(BinaryId Id)`  
_public; L15-27_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<BuildHealthFilterId, FilterIdConverter>))] [BinaryIdConverter(typeof(FilterIdConverter))]`
- desc: Identifier for a build health filter.
- L20 _public property_ `public static BuildHealthFilterId Empty { get; }` — Constant value for an empty build health filter id.
- L23 _public method_ `public static BuildHealthFilterId Parse(string text)` — (inheritdoc)
- L26 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.BuildHealth.FilterIdConverter`  
`class FilterIdConverter : BinaryIdConverter<BuildHealthFilterId>`  
_internal*; L32-39_
- inherits: `BinaryIdConverter<BuildHealthFilterId>`
- desc: Converter to and from BinaryId instances.
- L35 _public method_ `public override BuildHealthFilterId FromBinaryId(BinaryId id)` — (inheritdoc)
- L38 _public method_ `public override BinaryId ToBinaryId(BuildHealthFilterId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/BuildHealth/BuildHealthFilterMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.BuildHealth.BuildHealthFilterRestrictions`  
`public static class BuildHealthFilterRestrictions`  
_public; L12-28_
- desc: Static class that describes build health filter restrictions.
- L17 _public const_ `public const int MaxFilterNameLength = 250` — The maximum filter name length.
- L22 _public const_ `public const int MaxFilterDescripitonLength = 500` — The maximum filter description length.
- L27 _public const_ `public const int MaxFilterQueryLength = 4500` — The maximum filter query length.

#### record `EpicGames.Horde.BuildHealth.BuildHealthFilterAddRequest`  
`public record BuildHealthFilterAddRequest`  
_public; L33-78_
- desc: DTO used for requests used to add a build health filter.
- L38 _public property_ `public ProjectId FilterProject { get; set; }` — The project the filter belongs to.
- L43 _public property_ `public string FilterName { get; set; }` — The name of the filter.
- L48 _public property_ `public string? FilterDescription { get; init; }` — The description of the filter.
- L53 _public property_ `public string FilterQuery { get; set; }` — The filter query.
- L59 _public method_ `public bool IsValidFilterName()` — Returns whether the filter name request is valid or not.
- L65 _public method_ `public bool IsValidFilterDescription()` — Returns whether the filter description request is valid or not.
- L71 _public method_ `public bool IsValidFilterQuery()` — Returns whether the filter query request is valid or not.
- L77 _public method_ `public bool IsValidAddRequest()` — Returns whether the filter add request is valid.

#### record `EpicGames.Horde.BuildHealth.BuildHealthFilterUpdateRequest`  
`public record BuildHealthFilterUpdateRequest`  
_public; L83-123_
- desc: DTO used for requests used to update a build health filter.
- L88 _public property_ `public string? FilterName { get; set; }` — The name of the filter.
- L93 _public property_ `public string? FilterDescription { get; init; }` — The description of the filter.
- L98 _public property_ `public string? FilterQuery { get; set; }` — The filter query.
- L104 _public method_ `public bool IsValidFilterName()` — Returns whether the filter name request is valid or not.
- L110 _public method_ `public bool IsValidFilterDescription()` — Returns whether the filter description request is valid or not.
- L116 _public method_ `public bool IsValidFilterQuery()` — Returns whether the filter query request is valid or not.
- L122 _public method_ `public bool IsValidUpdateRequest()` — Returns whether the filter update request is valid.

#### class `EpicGames.Horde.BuildHealth.BuildHealthFilterResponse`  
`public class BuildHealthFilterResponse`  
_public; L128-196_
- desc: Response object for build health filters.
- L133 _public property_ `public BuildHealthFilterId Id { get; init; }` — The id of the filter.
- L138 _public property_ `public GetThinUserInfoResponse? Owner { get; init; }` — The owner of the filter.
- L143 _public property_ `public ProjectId FilterProject { get; init; }` — The project the filter belongs to.
- L148 _public property_ `public string FilterName { get; init; }` — The filter name.
- L153 _public property_ `public string? FilterDescription { get; init; }` — The description of the filter.
- L158 _public property_ `public string FilterQuery { get; init; }` — The filter query.
- L163 _public property_ `public DateTime UpdateTimeUtc { get; init; }` — The last updated time of the filter.
- L170-179 _public ctor_ `public BuildHealthFilterResponse(IBuildHealthFilter filter)` — Creates a build health filter response from a provided build health filter.
- L186-195 _public ctor_ `public BuildHealthFilterResponse(IBuildHealthFilter filter, GetThinUserInfoResponse owner)` — Creates a build health filter response from a provided build health filter, and the ownership object.

### `Source/Programs/Shared/EpicGames.Horde/BuildHealth/IBuildHealthFilter.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.BuildHealth.IBuildHealthFilter`  
`public interface IBuildHealthFilter`  
_public; L12-48_
- desc: Describes a build health filter.
- L17 _public* property_ `BuildHealthFilterId Id { get; }` — The id of the filter.
- L22 _public* property_ `UserId? Owner { get; }` — Owner of the filter.
- L27 _public* property_ `string FilterQuery { get; }` — The underyling query of the filter.
- L32 _public* property_ `string FilterName { get; }` — The name of the filter.
- L37 _public* property_ `string? FilterDescription { get; }` — A description of the filter.
- L42 _public* property_ `ProjectId FilterProject { get; }` — The project the filter belongs to.
- L47 _public* property_ `DateTime UpdateTimeUtc { get; }` — The last time this filter was updated (UTC).

### `Source/Programs/Shared/EpicGames.Horde/BuildHealth/IBuildHealthFilterCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.BuildHealth.IBuildHealthFilterCollection`  
`public interface IBuildHealthFilterCollection`  
_public; L14-61_
- desc: Collection interace for managing build heatlh filters.
- L23 _public* method_ `Task<IBuildHealthFilter?> AddBuildHealthFilterAsync(UserId? owner, BuildHealthFilterAddRequest filterRequest, CancellationToken cancellationToken)` — Creates a new filter.
- L34 _public* method_ `Task<IBuildHealthFilter?> UpdateBuildHealthFilterAsync(BuildHealthFilterId filterId, UserId? owner, BuildHealthFilterUpdateRequest filterRequest, CancellationToken cancellationToken)` — Updates the build health filter with the provided updates.
- L42 _public* method_ `Task<IBuildHealthFilter?> GetBuildHealthFilterAsync(BuildHealthFilterId filterId, CancellationToken cancellationToken)` — Gets a filter.
- L50 _public* method_ `Task<IEnumerable<IBuildHealthFilter>> GetBuildHealthFiltersAsync(ProjectId projectId, CancellationToken cancellationToken)` — Gets filters for a given project.
- L60 _public* method_ `Task<bool> DeleteBuildHealthFilterAsync(BuildHealthFilterId filterId, UserId? owner, CancellationToken cancellationToken)` — Deletes a filter.

### `Source/Programs/Shared/EpicGames.Horde/Commits/CommitId.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Commits.CommitId`  
`public class CommitId : IEquatable<CommitId>`  
_public; L18-94_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(CommitIdJsonConverter))] [TypeConverter(typeof(CommitIdTypeConverter))]`
- inherits: `IEquatable<CommitId>`
- desc: Identifier for a commit from an arbitary version control system.
- L23 _public property_ `public static CommitId Empty { get; }` — Commit id with an empty name
- L29 _public property_ `public string Name { get; }` — attrs: `[JsonPropertyOrder(0)]` — Name of this commit. Compared as a case-insensitive string.
- L34 _public ctor_ `public CommitId(string name)` — Constructor
- L40 _public method_ `public static CommitId FromPerforceChange(int change)` — Creates a commit it from a Perforce changelist number. Temporary helper method for migration purposes.
- L46 _public method_ `public static CommitId? FromPerforceChange(int? change)` — Creates a commit it from a Perforce changelist number. Temporary helper method for migration purposes.
- L52 _public method_ `public int GetPerforceChange()` — Gets the Perforce changelist number. Temporary helper method for migration purposes.
- L58 _public method_ `public int GetPerforceChangeOrMinusOne()` — Gets the Perforce changelist number. Temporary helper method for migration purposes.
- L64 _public method_ `public int? TryGetPerforceChange()` — Gets the Perforce changelist number. Temporary helper method for migration purposes.
- L68 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L72 _public method_ `public bool Equals(CommitId? other)` — (inheritdoc)
- L76 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L80 _public method_ `public override string ToString()` — (inheritdoc)
- L86 _public operator_ `public static bool operator ==(CommitId? a, CommitId? b)` — Test two commits for equality
- L92 _public operator_ `public static bool operator !=(CommitId? a, CommitId? b)` — Test two commits for inequality

#### class `EpicGames.Horde.Commits.CommitIdJsonConverter`  
`class CommitIdJsonConverter : JsonConverter<CommitId>`  
_internal*; L96-110_
- inherits: `JsonConverter<CommitId>`
- L99 _public method_ `public override CommitId? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L108 _public method_ `public override void Write(Utf8JsonWriter writer, CommitId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Commits.CommitIdTypeConverter`  
`class CommitIdTypeConverter : TypeConverter`  
_internal*; L112-129_
- inherits: `TypeConverter`
- L115 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L119 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L123 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L127 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.Commits.CommitIdWithOrder`  
`public class CommitIdWithOrder : CommitId, IEquatable<CommitIdWithOrder>, IComparable<CommitIdWithOrder>`  
_public; L134-219_
- inherits: `CommitId, IEquatable<CommitIdWithOrder>, IComparable<CommitIdWithOrder>`
- desc: Variant of CommitId including a value that allows it to be used for ordering.
- L139 _public property_ `public static new CommitIdWithOrder Empty { get; }` — Commit id with an empty name
- L145 _public property_ `public int Order { get; }` — attrs: `[JsonPropertyOrder(1)]` — Value used for ordering commits.
- L150-154 _public ctor_ `public CommitIdWithOrder(string name, int order) : base(name)` — Constructor
- L159 _public method_ `public static new CommitIdWithOrder FromPerforceChange(int change)` — Creates a commit it from a Perforce changelist number. Temporary helper method for migration purposes.
- L165 _public method_ `public static new CommitIdWithOrder? FromPerforceChange(int? change)` — Creates a commit it from a Perforce changelist number. Temporary helper method for migration purposes.
- L172 _public method_ `public int GetPerforceChangeOrOrder()` — Gets the Perforce change number if the commit name is numeric, otherwise falls back to using the Order property.
- L176 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L180 _public method_ `public bool Equals(CommitIdWithOrder? other)` — (inheritdoc)
- L184 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L188-198 _public method_ `public int CompareTo(CommitIdWithOrder? other)` — (inheritdoc)
- L201 _public operator_ `public static bool operator ==(CommitIdWithOrder? a, CommitIdWithOrder? b)`
- L204 _public operator_ `public static bool operator !=(CommitIdWithOrder? a, CommitIdWithOrder? b)`
- L207 _public operator_ `public static bool operator <(CommitIdWithOrder a, CommitIdWithOrder b)`
- L210 _public operator_ `public static bool operator <=(CommitIdWithOrder a, CommitIdWithOrder b)`
- L213 _public operator_ `public static bool operator >(CommitIdWithOrder a, CommitIdWithOrder b)`
- L216 _public operator_ `public static bool operator >=(CommitIdWithOrder a, CommitIdWithOrder b)`

### `Source/Programs/Shared/EpicGames.Horde/Commits/CommitMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Commits.GetCommitResponse`  
`public class GetCommitResponse`  
_public; L14-77_
- desc: Information about a commit
- L19-23 _public property_ `public CommitIdWithOrder Id { get; set; }` — The commit id
- L24 _private* field_ `CommitIdWithOrder? _id`
- L30-34 _public property_ `public int Number { get; set; }` — attrs: `[Obsolete("Use Id instead")]` — The changelist number
- L35 _private* field_ `int? _number`
- L40 _public property_ `public string Author { get; set; }` — Name of the user that authored this change [DEPRECATED]
- L45 _public property_ `public GetThinUserInfoResponse AuthorInfo { get; set; }` — Information about the user that authored this change
- L50 _public property_ `public string Description { get; set; }` — The description text
- L55 _public property_ `public DateTime DateUtc { get; set; }` — Date/time that change was committed
- L60 _public property_ `public List<CommitTag>? Tags { get; set; }` — Tags for this commit
- L65 _public property_ `public List<string>? Files { get; set; }` — List of files that were modified, relative to the stream base
- L70-76 _public ctor_ `public GetCommitResponse(GetThinUserInfoResponse authorInfo, string description, DateTime dateUtc)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Commits/CommitTag.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Commits.RegexExtensions`  
`internal static class RegexExtensions`  
_internal; L11-22_
- L13-16 _public method_ `public static string? ValueOrNull(this Group group)`
- L18-21 _public method_ `public static bool PresenceOf(this Group group)`

#### struct `EpicGames.Horde.Commits.CommitDescriptionTagContainer`  
`public partial struct CommitDescriptionTagContainer`  
_public; L27-137_
- desc: Convinence data structure that contains all tags associated with a provided commit description.
- L33 _private method_ `private static partial Regex RobomergeOwnerRegex()` — attrs: `[GeneratedRegex(@"^#ROBOMERGE-OWNER:\s*([^@\s]+)", RegexOptions.Multiline)]`
- L36 _private method_ `private static partial Regex RobomergeSourceRegex()` — attrs: `[GeneratedRegex(@"^#ROBOMERGE-SOURCE:\s*(.*)", RegexOptions.Multiline)]`
- L39 _private method_ `private static partial Regex RobomergeAuthorRegex()` — attrs: `[GeneratedRegex(@"^#ROBOMERGE-AUTHOR:\s*(\S+)", RegexOptions.Multiline)]`
- L42 _private method_ `private static partial Regex RobomergeBotRegex()` — attrs: `[GeneratedRegex(@"^#ROBOMERGE-BOT:\s*(.*)", RegexOptions.Multiline)]`
- L45 _private method_ `private static partial Regex JiraRegex()` — attrs: `[GeneratedRegex(@"^#jira\s*([^@\s]+)", RegexOptions.Multiline)]`
- L48 _private method_ `private static partial Regex TestsRegex()` — attrs: `[GeneratedRegex(@"^#tests\s*(.*)", RegexOptions.Multiline)]`
- L51 _private method_ `private static partial Regex PreflightRegex()` — attrs: `[GeneratedRegex(@"^#preflight\s*([^@\s]+)", RegexOptions.Multiline)]`
- L54 _private method_ `private static partial Regex ReviewRegex()` — attrs: `[GeneratedRegex(@"^#rb\s+(.+)$", RegexOptions.Multiline)]`
- L57 _private method_ `private static partial Regex Virtualized()` — attrs: `[GeneratedRegex(@"^#virtualized", RegexOptions.Multiline)]`
- L66 _public property_ `public string Description { get; init; }` — The source description of which the tags are extracted from.
- L71 _public property_ `public string? JiraTag { get; init; }` — The jira tag in the commit description.
- L76 _public property_ `public string? ReviewTag { get; set; }` — The review tag in the commit description.
- L81 _public property_ `public string? PresubmitTag { get; init; }` — The presubmit tag in the commit description.
- L86 _public property_ `public string? TestTag { get; init; }` — The test tag in the commit description.
- L91 _public property_ `public string? RobomergeOwnerTag { get; init; }` — The robomerge owner tag in the commit description.
- L96 _public property_ `public string? RobomergeAuthorTag { get; set; }` — The robomerge author tag in the commit description.
- L101 _public property_ `public string? RobomergeSourceTag { get; init; }` — The robomerge source tag in the commit description.
- L106 _public property_ `public string? RobomergeBotTag { get; init; }` — The robomerge bot tag in the commit description.
- L112 _public property_ `public string? VirtualizedTag { get; init; }` — Whether the change was virtualized or not.
- L121-136 _public method_ `public static CommitDescriptionTagContainer Create(string description)` — Creates a new CommitDescriptionTagContainer from a provided description.

#### struct `EpicGames.Horde.Commits.CommitTag`  
`public readonly struct CommitTag : IEquatable<CommitTag>`  
_public; L144-206_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(CommitTagJsonConverter))]`
- inherits: `IEquatable<CommitTag>`
- desc: Constants for known commit tags
- L149 _public property_ `public static CommitTag Code { get; }` — Predefined filter name for commits containing code
- L154 _public property_ `public static CommitTag Content { get; }` — Predefined filter name for commits containing content
- L159 _public property_ `public string Text { get; }` — The tag text
- L165-172 _public ctor_ `public CommitTag(string text)` — Constructor
- L177 _public method_ `public bool IsEmpty()` — Check if the current tag is empty
- L180 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L183 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L186 _public method_ `public bool Equals(CommitTag other)` — (inheritdoc)
- L189 _public method_ `public override string ToString()` — (inheritdoc)
- L197 _public operator_ `public static bool operator ==(CommitTag left, CommitTag right)` — Compares two string ids for equality
- L205 _public operator_ `public static bool operator !=(CommitTag left, CommitTag right)` — Compares two string ids for inequality

#### class `EpicGames.Horde.Commits.CommitTagJsonConverter`  
`public class CommitTagJsonConverter : JsonConverter<CommitTag>`  
_public; L211-224_
- inherits: `JsonConverter<CommitTag>`
- desc: Converts CommitTag values to and from JSON
- L214-217 _public method_ `public override CommitTag Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L220-223 _public method_ `public override void Write(Utf8JsonWriter writer, CommitTag value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Commits/ICommit.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Commits.ICommit`  
`public interface ICommit`  
_public; L16-81_
- desc: Stores metadata about a commit
- L21 _public* property_ `CommitIdWithOrder Id { get; }` — Id for this commit
- L26 _public* property_ `StreamId StreamId { get; }` — Stream containing the commit
- L31 _public* property_ `CommitIdWithOrder OriginalCommitId { get; }` — The change that this commit originates from
- L36 _public* property_ `UserId AuthorId { get; }` — The author user id
- L41 _public* property_ `UserId OwnerId { get; }` — The owner of this change, if different from the author (due to Robomerge)
- L46 _public* property_ `string Description { get; }` — Changelist description
- L51 _public* property_ `string BasePath { get; }` — Base path for all files in the change
- L56 _public* property_ `DateTime DateUtc { get; }` — Date/time that change was committed
- L63 _public* method_ `ValueTask<IReadOnlyList<CommitTag>> GetTagsAsync(CancellationToken cancellationToken)` — Gets the list of tags for the commit
- L71 _public* method_ `ValueTask<bool> MatchesFilterAsync(FileFilter filter, CancellationToken cancellationToken)` — Determine if this commit matches the given filter. Prefer using commit tags rather than this method; the results can be cached.
- L80 _public* method_ `ValueTask<IReadOnlyList<string>> GetFilesAsync(int? minFiles, int? maxFiles, CancellationToken cancellationToken)` — Gets the files for this change, relative to the root of the stream

#### class `EpicGames.Horde.Commits.CommitExtensions`  
`public static class CommitExtensions`  
_public; L86-97_
- desc: Extension methods for operating on commits
- L95 _public method_ `public static ValueTask<IReadOnlyList<string>> GetFilesAsync(this ICommit commit, int files, CancellationToken cancellationToken)` — Gets the files for this change, relative to the root of the stream

### `Source/Programs/Shared/EpicGames.Horde/Commits/ICommitCollection.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Commits.CommitSortOrder`  
`public enum CommitSortOrder`  
_public; L15-26_
- desc: Sort order for commit queries
- L20 _public* enumerator_ `Descending` — Newest commits first (default)
- L25 _public* enumerator_ `Ascending` — Oldest commits first

#### class `EpicGames.Horde.Commits.CommitCollectionException`  
`public class CommitCollectionException(string? message, Exception? innerException) : Exception(message, innerException)`  
_public; L34-34_
- desc: Represents errors that occur during commit collection operations. This exception is thrown when operations on a ICommitCollection fail. Serves as a wrapper for underlying VCS-specific exceptions, providing consistent errors for each VCS implementation

#### interface `EpicGames.Horde.Commits.ICommitCollection`  
`public interface ICommitCollection`  
_public; L39-88_
- desc: VCS abstraction. Provides information about commits to a particular stream.
- L48 _public* method_ `Task<CommitIdWithOrder> CreateNewAsync(string path, string description, CancellationToken cancellationToken = default)` — Creates a new change
- L56 _public* method_ `Task<ICommit> GetAsync(CommitId commitId, CancellationToken cancellationToken = default)` — Gets a commit by id
- L64 _public* method_ `ValueTask<CommitIdWithOrder> GetOrderedAsync(CommitId commitId, CancellationToken cancellationToken = default)` — Gets an ordered commit id
- L78 _public* method_ `IAsyncEnumerable<ICommit> FindAsync(CommitId? minCommitId = null, bool includeMinCommit = true, CommitId? maxCommitId = null, bool includeMaxCommit = true, int? maxResults = null, IReadOnlyList<CommitTag>? tags = null, CommitSortOrder sortOrder = CommitSortOrder.Descending, CancellationToken cancellationToken = default)` — Finds changes submitted to a stream.
- L87 _public* method_ `IAsyncEnumerable<ICommit> SubscribeAsync(CommitId minCommitId, IReadOnlyList<CommitTag>? tags = null, CancellationToken cancellationToken = default)` — Subscribes to changes from this commit source

#### class `EpicGames.Horde.Commits.CommitCollectionExtensions`  
`public static class CommitCollectionExtensions`  
_public; L93-160_
- desc: Extension methods for ICommitCollection
- L102-106 _public method_ `public static Task<CommitIdWithOrder> CreateNewAsync(this ICommitCollection commitCollection, ITemplate template, CancellationToken cancellationToken)` — Creates a new change for a template
- L118 _public method_ `public static IAsyncEnumerable<ICommit> FindAsync(this ICommitCollection commitCollection, CommitId? minCommitId, CommitId? maxCommitId, int? maxResults = null, IReadOnlyList<CommitTag>? tags = null, CancellationToken cancellationToken = default)` — Finds changes submitted to a stream, in reverse order.
- L128-131 _public method_ `public static async ValueTask<ICommit?> GetLastCodeChangeAsync(this ICommitCollection commitCollection, CommitId? maxCommitId, CancellationToken cancellationToken = default)` — Gets the last code code equal or before the given change number
- L139-147 _public method_ `public static async Task<ICommit> GetLatestAsync(this ICommitCollection commitCollection, CancellationToken cancellationToken = default)` — Finds the latest commit from a source
- L155-159 _public method_ `public static async Task<CommitIdWithOrder> GetLastCommitIdAsync(this ICommitCollection commitCollection, CancellationToken cancellationToken = default)` — Finds the latest commit from a source

### `Source/Programs/Shared/EpicGames.Horde/Common/Condition.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Common.TokenType`  
`enum TokenType : byte`  
_internal*; L18-38_
- inherits: `byte`
- L20 _public* enumerator_ `Error`
- L21 _public* enumerator_ `End`
- L22 _public* enumerator_ `Identifier`
- L23 _public* enumerator_ `Scalar`
- L24 _public* enumerator_ `Not`
- L25 _public* enumerator_ `Eq`
- L26 _public* enumerator_ `Neq`
- L27 _public* enumerator_ `LogicalOr`
- L28 _public* enumerator_ `LogicalAnd`
- L29 _public* enumerator_ `Lt`
- L30 _public* enumerator_ `Lte`
- L31 _public* enumerator_ `Gt`
- L32 _public* enumerator_ `Gte`
- L33 _public* enumerator_ `Lparen`
- L34 _public* enumerator_ `Rparen`
- L35 _public* enumerator_ `Regex`
- L36 _public* enumerator_ `True`
- L37 _public* enumerator_ `False`

#### class `EpicGames.Horde.Common.TokenReader`  
`class TokenReader`  
_internal*; L40-287_
- L42 _public property_ `public string Input { get; set; }`
- L43 _public property_ `public int Offset { get; set; }`
- L44 _public property_ `public int Length { get; set; }`
- L46 _public property_ `public StringView Token => ...`
- L47 _public property_ `public TokenType Type { get; set; }`
- L48 _public property_ `public string? Scalar { get; set; }`
- L50-54 _public ctor_ `public TokenReader(string input)`
- L56-61 _private method_ `private void SetCurrent(int length, TokenType type, string? scalar = null)`
- L63-172 _public method_ `public void MoveNext()`
- L174-219 _private* method_ `bool ParseString()`
- L221 _private* field_ `static readonly Dictionary<StringView, ulong> s_sizeSuffixes = ...`
- L221 _private* field_ `static readonly Dictionary< s_sizeSuffixes = new(StringViewComparer.OrdinalIgnoreCase) { ["kb"] = 1024UL, ["Mb"] = 1024UL * 1024, ["Gb"] = 1024UL * 1024 * 1024, ["Tb"] = 1024UL * 1024 * 1024 * 1024, }`
- L229-261 _private* method_ `bool ParseNumber()`
- L263-271 _private* method_ `bool RequireCharacter(string text, int idx, char character)`
- L273-276 _private* method_ `static bool IsNumber(char character)`
- L278-281 _private* method_ `static bool IsIdentifier(char character)`
- L283-286 _private* method_ `static bool IsIdentifierTail(char character)`

#### class `EpicGames.Horde.Common.ConditionException`  
`public class ConditionException : Exception`  
_public; L292-302_
- inherits: `Exception`
- desc: Exception thrown when a condition is not valid
- L298-301 _public ctor_ `public ConditionException(string error) : base(error)` — Constructor

#### class `EpicGames.Horde.Common.Condition`  
`public class Condition`  
_public; L311-637_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(ConditionTypeConverter))] [CbConverter(typeof(ConditionCbConverter))] [JsonConverter(typeof(ConditionJsonConverter))]`
- desc: A conditional expression that can be evaluated against a particular object
- L329 _public property_ `public string Text { get; }` — The condition text
- L334 _public property_ `public string? Error { get; set; }` — Error produced when parsing the condition
- L336 _private* field_ `readonly List<Token> _tokens = []`
- L337 _private* field_ `readonly List<string> _strings = []`
- L339 _private* field_ `static readonly IEnumerable<string> s_trueScalar = ["true"]`
- L340 _private* field_ `static readonly IEnumerable<string> s_falseScalar = ["false"]`
- L342-360 _private ctor_ `private Condition(string text)`
- L366 _public method_ `public bool IsEmpty()` — Determines if the condition is empty
- L371 _public method_ `public bool IsValid()` — Checks if the condition has been parsed correctly
- L378-386 _public method_ `public static Condition Parse(string text)` — Parse the given text as a condition
- L393-396 _public method_ `public static Condition TryParse(string text)` — Attempts to parse the given text as a condition
- L398-411 _private* method_ `string? ParseOrExpr(TokenReader reader)`
- L413-426 _private* method_ `string? ParseAndExpr(TokenReader reader)`
- L428-450 _private* method_ `string? ParseBooleanExpr(TokenReader reader)`
- L452-469 _private* method_ `string? ParseSubExpr(TokenReader reader)`
- L471-495 _private* method_ `string? ParseComparisonExpr(TokenReader reader)`
- L497-519 _private* method_ `string? ParseScalarExpr(TokenReader reader)`
- L526-535 _public method_ `public bool Evaluate(Func<string, IEnumerable<string>> getPropertyValues)` — Evaluate the condition using the given callback to retrieve property values
- L537-592 _private* method_ `bool EvaluateCondition(ref int idx, Func<string, IEnumerable<string>> getPropertyValues)`
- L594-605 _private* method_ `IEnumerable<string> EvaluateScalar(ref int idx, Func<string, IEnumerable<string>> getPropertyValues)`
- L607-616 _private* method_ `static IEnumerable<long> AsIntegers(IEnumerable<string> scalars)`
- L623-633 _public operator_ `public static implicit operator Condition?(string? text)` — attrs: `[return: NotNullIfNotNull(nameof(text))]` — Implicit conversion from string to conditions
- L636 _public method_ `public override string ToString()` — (inheritdoc)

#### struct `EpicGames.Horde.Common.Condition.Token`  
`readonly struct Token`  
_private*; L314-324_
- attrs: `[DebuggerDisplay("{Type}")]`
- L316 _public field_ `public readonly TokenType Type`
- L317 _public field_ `public readonly byte Index`
- L319-323 _public ctor_ `public Token(TokenType type, int index)`

#### class `EpicGames.Horde.Common.ConditionCbConverter`  
`public class ConditionCbConverter : CbConverter<Condition>`  
_public; L642-678_
- inherits: `CbConverter<Condition>`
- desc: Converter from conditions to compact binary objects
- L645-655 _public method_ `public override Condition Read(CbField field)` — (inheritdoc)
- L658-668 _public method_ `public override void Write(CbWriter writer, Condition value)` — (inheritdoc)
- L671-677 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, Condition value)` — (inheritdoc)

#### class `EpicGames.Horde.Common.ConditionTypeConverter`  
`sealed class ConditionTypeConverter : TypeConverter`  
_internal*; L683-696_
- inherits: `TypeConverter`
- desc: Type converter from strings to condition objects
- L686 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L689 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L692 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L695 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type? destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.Common.ConditionJsonConverter`  
`sealed class ConditionJsonConverter : JsonConverter<Condition>`  
_internal*; L701-720_
- inherits: `JsonConverter<Condition>`
- desc: Type converter from Json strings to condition objects
- L704 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L706-714 _public method_ `public override Condition Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)`
- L716-719 _public method_ `public override void Write(Utf8JsonWriter writer, Condition value, JsonSerializerOptions options)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/AgentManagedProcess.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.AgentManagedProcess`  
`public sealed class AgentManagedProcess : IAsyncDisposable`  
_public; L15-136_
- inherits: `IAsyncDisposable`
- desc: Represents a remotely executed process managed by the Horde agent
- L17 _private* field_ `readonly Channel<string> _output`
- L18 _private* field_ `readonly BackgroundTask _backgroundTask`
- L19 _private* field_ `readonly TaskCompletionSource<int> _result = new(TaskCreationOptions.RunContinuationsAsynchronously)`
- L21 _private* field_ `byte[] _buffer = new byte[1024]`
- L22 _private* field_ `int _bufferLength`
- L25 _public property_ `public bool HasExited => ...` — (inheritdoc)
- L30-34 _public ctor_ `public AgentManagedProcess(AgentMessageChannel channel)` — Constructor
- L37 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L40-47 _public method_ `public async ValueTask<string?> ReadLineAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L50 _public method_ `public Task<int> WaitForExitAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L52-64 _private* method_ `async Task RunAsync(AgentMessageChannel channel, CancellationToken cancellationToken)`
- L66-89 _private* method_ `async Task RunInternalAsync(AgentMessageChannel channel, CancellationToken cancellationToken)`
- L91-123 _private* method_ `void AppendData(ReadOnlySpan<byte> data)`
- L125-135 _private* method_ `void AppendToBuffer(ReadOnlySpan<byte> data)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/AgentMessage.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Compute.AgentMessageType`  
`public enum AgentMessageType`  
_public; L21-119_
- desc: Type of a compute message
- L26 _public* enumerator_ `None = 0x00` — No message was received (end of stream)
- L31 _public* enumerator_ `Ping = 0x01` — No-op message sent to keep the connection alive. Remote should reply with the same message.
- L36 _public* enumerator_ `Exception = 0x02` — Sent in place of a regular response if an error occurs on the remote
- L41 _public* enumerator_ `Fork = 0x03` — Fork the message loop into a new channel
- L46 _public* enumerator_ `Attach = 0x04` — Sent as the first message on a channel to notify the remote that the remote end is attached
- L53 _public* enumerator_ `WriteFiles = 0x10` — Extract files on the remote machine (Initiator -> Remote)
- L58 _public* enumerator_ `WriteFilesResponse = 0x11` — Notification that files have been extracted (Remote -> Initiator)
- L63 _public* enumerator_ `DeleteFiles = 0x12` — Deletes files on the remote machine (Initiator -> Remote)
- L68 _public* enumerator_ `ExecuteV1 = 0x16` — Execute a process in a sandbox (Initiator -> Remote)
- L73 _public* enumerator_ `ExecuteV2 = 0x22` — Execute a process in a sandbox (Initiator -> Remote)
- L78 _public* enumerator_ `ExecuteV3 = 0x23` — Execute a process in a sandbox (Initiator -> Remote)
- L83 _public* enumerator_ `ExecuteOutput = 0x17` — Returns output from the child process to the caller (Remote -> Initiator)
- L88 _public* enumerator_ `ExecuteResult = 0x18` — Returns the process exit code (Remote -> Initiator)
- L97 _public* enumerator_ `ReadBlob = 0x20` — Reads a blob from storage
- L102 _public* enumerator_ `ReadBlobResponse = 0x21` — Response to a ReadBlob request.
- L111 _public* enumerator_ `XorRequest = 0xf0` — Xor a block of data with a value
- L116 _public* enumerator_ `XorResponse = 0xf1` — Result from an XorRequest request.

#### enum `EpicGames.Horde.Compute.ExecuteProcessFlags`  
`public enum ExecuteProcessFlags`  
_public; L125-143_
- attrs: `[Flags]`
- desc: Flags describing how to execute a compute task process on the agent
- L130 _public* enumerator_ `None = 0` — No execute flags set
- L136 _public* enumerator_ `UseWine = 1` — Request execution to be wrapped under Wine when running on Linux. Agent still reserves the right to refuse it (e.g no Wine executable configured, mismatching OS etc)
- L142 _public* enumerator_ `ReplaceContainerEntrypoint = 2` — Use compute process executable as entrypoint for container If not set, path to the executable is passed as the first parameter to the container invocation

#### class `EpicGames.Horde.Compute.AgentMessage`  
`public sealed class AgentMessage : IMemoryReader, IDisposable`  
_public; L148-186_
- inherits: `IMemoryReader, IDisposable`
- desc: Standard implementation of a message
- L153 _public property_ `public AgentMessageType Type { get; }` — Type of the message
- L158 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data that was read
- L160 _private* field_ `readonly IMemoryOwner<byte> _memoryOwner`
- L161 _private* field_ `int _position`
- L166-173 _public ctor_ `public AgentMessage(AgentMessageType type, ReadOnlyMemory<byte> data)` — Constructor
- L176-179 _public method_ `public void Dispose()` — (inheritdoc)
- L182 _public method_ `public ReadOnlyMemory<byte> GetMemory(int minSize = 1)` — (inheritdoc)
- L185 _public method_ `public void Advance(int length)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.InvalidAgentMessageException`  
`public sealed class InvalidAgentMessageException : ComputeException`  
_public; L191-200_
- inherits: `ComputeException`
- desc: Exception thrown when an invalid message is received
- L196-199 _public ctor_ `public InvalidAgentMessageException(AgentMessage actualMessage, AgentMessageType? expectedType, ComputeRemoteException? remoteException) : base($"Unexpected message {actualMessage.Type}" + (expectedType != null ? $". Wanted {expectedType}" : ""), remoteException)` — Constructor

#### class `EpicGames.Horde.Compute.ComputeExecutionCancelledException`  
`public sealed class ComputeExecutionCancelledException : ComputeException`  
_public; L205-232_
- inherits: `ComputeException`
- desc: Exception thrown when a compute execution is cancelled
- L207 _private const_ `private const string Text = "Compute execution cancelled"`
- L212-214 _public ctor_ `public ComputeExecutionCancelledException() : base(Text)` — Constructor
- L216-218 _private ctor_ `private ComputeExecutionCancelledException(Exception innerException) : base(Text, innerException)`
- L225-231 _public method_ `public static void TryThrow(ExceptionMessage em)` — Try constructing and throwing if the exception message matches a cancellation exception

#### interface `EpicGames.Horde.Compute.IAgentMessageBuilder`  
`public interface IAgentMessageBuilder : IMemoryWriter, IDisposable`  
_public; L237-243_
- inherits: `IMemoryWriter, IDisposable`
- desc: Writer for compute messages
- L242 _public* method_ `void Send()` — Sends the current message

#### record struct `EpicGames.Horde.Compute.ExceptionMessage`  
`public readonly record struct ExceptionMessage(string Message, string Description)`  
_public; L248-248_
- desc: Message for reporting an error

#### record struct `EpicGames.Horde.Compute.ForkMessage`  
`public readonly record struct ForkMessage(int ChannelId, int BufferSize)`  
_public; L255-255_
- desc: Message requesting that the message loop be forked

#### record struct `EpicGames.Horde.Compute.UploadFilesMessage`  
`public readonly record struct UploadFilesMessage(string Name, BlobLocator Locator)`  
_public; L262-262_
- desc: Extract files from a bundle to a path in the remote sandbox

#### record struct `EpicGames.Horde.Compute.DeleteFilesMessage`  
`public readonly record struct DeleteFilesMessage(IReadOnlyList<string> Filter)`  
_public; L268-268_
- desc: Deletes files or directories in the remote

#### record struct `EpicGames.Horde.Compute.ExecuteProcessMessage`  
`public readonly record struct ExecuteProcessMessage(string Executable, IReadOnlyList<string> Arguments, string? WorkingDir, IReadOnlyDictionary<string, string?> EnvVars, ExecuteProcessFlags Flags, string? ContainerImageUrl)`  
_public; L279-279_
- desc: Message to execute a new child process

#### record struct `EpicGames.Horde.Compute.ExecuteProcessResponseMessage`  
`public readonly record struct ExecuteProcessResponseMessage(int ExitCode)`  
_public; L285-285_
- desc: Response from executing a child process

#### record struct `EpicGames.Horde.Compute.ReadBlobMessage`  
`public readonly record struct ReadBlobMessage(BlobLocator Locator, int Offset, int Length)`  
_public; L290-290_
- desc: Creates a blob read request

#### record struct `EpicGames.Horde.Compute.XorRequestMessage`  
`public readonly record struct XorRequestMessage(ReadOnlyMemory<byte> Data, byte Value)`  
_public; L297-297_
- desc: Message for running an XOR command

#### class `EpicGames.Horde.Compute.AgentMessageExtensions`  
`public static class AgentMessageExtensions`  
_public; L302-796_
- desc: Wraps various requests across compute channels
- L307-311 _public method_ `public static async ValueTask CloseAsync(this AgentMessageChannel channel, CancellationToken cancellationToken = default)` — Closes the remote message loop
- L316-320 _public method_ `public static async ValueTask PingAsync(this AgentMessageChannel channel, CancellationToken cancellationToken = default)` — Sends a ping message to the remote
- L325 _public method_ `public static ValueTask SendExceptionAsync(this AgentMessageChannel channel, Exception ex, CancellationToken cancellationToken = default)` — Sends an exception response to the remote
- L330-336 _public method_ `public static async ValueTask SendExceptionAsync(this AgentMessageChannel channel, string description, string trace, CancellationToken cancellationToken = default)` — Sends an exception response to the remote
- L341-346 _public method_ `public static ExceptionMessage ParseExceptionMessage(this AgentMessage message)` — Parses a message as an ExceptionMessage
- L351-357 _public method_ `public static async ValueTask ForkAsync(this AgentMessageChannel channel, int channelId, int bufferSize, CancellationToken cancellationToken = default)` — Requests that the remote message loop be forked
- L362-367 _public method_ `public static ForkMessage ParseForkMessage(this AgentMessage message)` — Parses a fork request message
- L372-376 _public method_ `public static async ValueTask AttachAsync(this AgentMessageChannel channel, CancellationToken cancellationToken = default)` — Notifies the remote that a buffer has been attached
- L384-388 _public method_ `public static async ValueTask WaitForAttachAsync(this AgentMessageChannel channel, CancellationToken cancellationToken = default)` — Waits until an attached notification is received along the channel
- L395-407 _public method_ `public static void ThrowIfUnexpectedType(this AgentMessage message, AgentMessageType? expectedType = null)` — Throw an exception if message is not of expected type
- L411-431 _private* method_ `static async Task<AgentMessage> RunStorageServerAsync(this AgentMessageChannel channel, IStorageBackend storage, CancellationToken cancellationToken = default)`
- L436-447 _public method_ `public static async Task UploadFilesAsync(this AgentMessageChannel channel, string path, BlobLocator locator, IStorageBackend storage, CancellationToken cancellationToken = default)` — Creates a sandbox on the remote machine
- L452-465 _public method_ `public static UploadFilesMessage ParseUploadFilesMessage(this AgentMessage message)` — Parses a message as a UploadFilesMessage
- L473-478 _public method_ `public static async ValueTask DeleteFilesAsync(this AgentMessageChannel channel, IReadOnlyList<string> paths, CancellationToken cancellationToken)` — Destroys a sandbox on the remote machine
- L483-487 _public method_ `public static DeleteFilesMessage ParseDeleteFilesMessage(this AgentMessage message)` — Parses a message as a DeleteFilesMessage
- L498-509 _public method_ `public static async Task<AgentManagedProcess> ExecuteAsync(this AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, CancellationToken cancellationToken = default)` — Executes a remote process (using ExecuteV1)
- L521-533 _public method_ `public static async Task<AgentManagedProcess> ExecuteAsync(this AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags = ExecuteProcessFlags.None, CancellationToken cancellationToken = default)` — Executes a remote process (using ExecuteV2)
- L546-559 _public method_ `public static async Task<AgentManagedProcess> ExecuteAsync(this AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags, string? containerImageUrl, CancellationToken cancellationToken = default)` — Executes a remote process (using ExecuteV3)
- L564-571 _public method_ `public static ExecuteProcessMessage ParseExecuteProcessV1Message(this AgentMessage message)` — Parses a message as a ExecuteProcessMessage
- L576-584 _public method_ `public static ExecuteProcessMessage ParseExecuteProcessV2Message(this AgentMessage message)` — Parses a message as a ExecuteProcessMessage
- L589-598 _public method_ `public static ExecuteProcessMessage ParseExecuteProcessV3Message(this AgentMessage message)` — Parses a message as a ExecuteProcessMessage
- L603-608 _public method_ `public static async ValueTask SendExecuteOutputAsync(this AgentMessageChannel channel, ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — Sends output from a child process
- L616-621 _public method_ `public static async ValueTask SendExecuteResultAsync(this AgentMessageChannel channel, int exitCode, CancellationToken cancellationToken = default)` — Sends a response from executing a child process
- L626-630 _public method_ `public static ExecuteProcessResponseMessage ParseExecuteProcessResponse(this AgentMessage message)` — Parses a message as a ExecuteProcessMessage
- L641-647 _public method_ `public static ReadBlobMessage ParseReadBlobRequest(this AgentMessage message)`
- L682-721 _public method_ `public static async Task<ReadOnlyMemory<byte>> ReadBlobAsync(this AgentMessageChannel channel, string path, int offset, int length, CancellationToken cancellationToken = default)` — Reads a blob from the remote
- L730-733 _public method_ `public static Task SendBlobDataAsync(this AgentMessageChannel channel, ReadBlobMessage message, IStorageBackend storage, CancellationToken cancellationToken = default)` — Writes blob data to a compute channel
- L744-769 _public method_ `public static async Task SendBlobDataAsync(this AgentMessageChannel channel, BlobLocator locator, int offset, int length, IStorageBackend storage, CancellationToken cancellationToken = default)` — Writes blob data to a compute channel
- L778-784 _public method_ `public static async ValueTask SendXorRequestAsync(this AgentMessageChannel channel, ReadOnlyMemory<byte> data, byte value, CancellationToken cancellationToken = default)` — Send a message to request that a byte string be xor'ed with a particular value
- L789-793 _public method_ `public static XorRequestMessage AsXorRequest(this AgentMessage message)` — Parse a message as an XOR request

#### class `EpicGames.Horde.Compute.AgentMessageExtensions.BlobDataStream`  
`sealed class BlobDataStream : ReadOnlyMemoryStream`  
_private*; L652-671_
- inherits: `ReadOnlyMemoryStream`
- desc: Wraps a compute message containing blob data
- L654 _private* field_ `readonly AgentMessage _message`
- L656-660 _public ctor_ `public BlobDataStream(AgentMessage message) : base(message.Data.Slice(8))`
- L662-670 _protected method_ `protected override void Dispose(bool disposing)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/AgentMessageChannel.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.AgentMessageChannel`  
`public sealed class AgentMessageChannel : IDisposable`  
_public; L18-207_
- inherits: `IDisposable`
- desc: Implementation of a compute channel
- L21 _private* const_ `const int HeaderLength = 5`
- L77 _private* field_ `readonly int _channelId`
- L78 _private* field_ `readonly ComputeProtocol _protocol`
- L79 _private* field_ `readonly ComputeBufferReader _recvBufferReader`
- L80 _private* field_ `readonly ComputeBufferWriter _sendBufferWriter`
- L83 _private* field_ `readonly ILogger _logger`
- L85 _private* field_ `MessageBuilder? _currentBuilder`
- L90 _public property_ `public ComputeProtocol Protocol => ...` — The negotiated compute protocol version number
- L100-107 _public ctor_ `public AgentMessageChannel(int channelId, ComputeProtocol protocol, ComputeBufferReader recvBufferReader, ComputeBufferWriter sendBufferWriter, ILogger logger)` — Constructor
- L117-126 _public ctor_ `public AgentMessageChannel(ComputeSocket socket, int channelId, ComputeBuffer recvBuffer, ComputeBuffer sendBuffer, ILogger logger)` — Constructor
- L131-137 _public method_ `public void Dispose()` — Overridable dispose method
- L142-145 _public method_ `public void MarkComplete()` — Mark the send buffer as complete
- L148-177 _public method_ `public async ValueTask<AgentMessage> ReceiveAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L180-192 _private* method_ `void LogMessageInfo(string verb, AgentMessageType type, ReadOnlySpan<byte> data)` — attrs: `[SuppressMessage("CodeQuality", "IDE0051:Remove unused private members", Justification = "Log calls disabled")]`
- L195-206 _public method_ `public async ValueTask<IAgentMessageBuilder> CreateMessageAsync(AgentMessageType type, int maxSize, CancellationToken cancellationToken)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.AgentMessageChannel.MessageBuilder`  
`class MessageBuilder : IAgentMessageBuilder`  
_private*; L26-75_
- inherits: `IAgentMessageBuilder`
- desc: Allows creating new messages in rented memory
- L28 _private* field_ `readonly AgentMessageChannel _channel`
- L29 _private* field_ `readonly ComputeBufferWriter _sendBufferWriter`
- L30 _private* field_ `readonly AgentMessageType _type`
- L31 _private* field_ `int _length`
- L34 _public property_ `public int Length => ...` — (inheritdoc)
- L36-42 _public ctor_ `public MessageBuilder(AgentMessageChannel channel, ComputeBufferWriter sendBufferWriter, AgentMessageType type)`
- L44-50 _public method_ `public void Dispose()`
- L52-65 _public method_ `public void Send()`
- L68 _public method_ `public void Advance(int count)` — (inheritdoc)
- L71 _public method_ `public Memory<byte> GetMemory(int sizeHint = 0)` — (inheritdoc)
- L74 _public method_ `public Span<byte> GetSpan(int sizeHint = 0)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.AgentMessageChannelExtensions`  
`public static class AgentMessageChannelExtensions`  
_public; L212-285_
- desc: Extension methods to allow creating channels from leases
- L219 _public method_ `public static AgentMessageChannel CreateAgentMessageChannel(this ComputeSocket socket, int channelId)` — Creates a message channel with the given identifier
- L228 _public method_ `public static AgentMessageChannel CreateAgentMessageChannel(this ComputeSocket socket, int channelId, int bufferSize)` — Creates a message channel with the given identifier
- L238-243 _public method_ `public static AgentMessageChannel CreateAgentMessageChannel(this ComputeSocket socket, int channelId, int sendBufferSize, int recvBufferSize)` — Creates a message channel with the given identifier
- L252-257 _public method_ `public static async ValueTask<AgentMessage> ReceiveAsync(this AgentMessageChannel channel, AgentMessageType type, CancellationToken cancellationToken = default)` — Reads a message from the channel
- L266-269 _public method_ `public static ValueTask<IAgentMessageBuilder> CreateMessageAsync(this AgentMessageChannel channel, AgentMessageType type, CancellationToken cancellationToken)` — Creates a new builder for a message
- L277-284 _public method_ `public static async ValueTask SendAsync(this AgentMessageChannel channel, AgentMessage message, CancellationToken cancellationToken)` — Forwards an existing message across a channel

### `Source/Programs/Shared/EpicGames.Horde/Compute/AgentMessageHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.AgentMessageHandler`  
`public class AgentMessageHandler`  
_public; L25-641_
- desc: Implements the remote end of a compute worker.
- L27 _private* field_ `readonly DirectoryReference _sandboxDir`
- L28 _private* field_ `readonly Dictionary<string, string?> _envVars`
- L28 _private* field_ `readonly Dictionary< _envVars`
- L29 _private* field_ `readonly bool _executeInProcess`
- L30 _private* field_ `readonly string? _wineExecutablePath`
- L31 _private* field_ `readonly string? _containerEngineExecutable`
- L32 _private* field_ `readonly ILogger _logger`
- L43-51 _public ctor_ `public AgentMessageHandler(DirectoryReference sandboxDir, Dictionary<string, string?>? envVars, bool executeInProcess, string? wineExecutablePath, string? containerEngineExecutable, ILogger logger)` — Constructor
- L58-82 _public method_ `public async Task RunAsync(ComputeSocket socket, CancellationToken cancellationToken)` — Runs the worker using commands sent along the given socket
- L84-167 _private* method_ `async Task RunAsync(ComputeSocket socket, int channelId, int bufferSize, Func<Exception, Task> postException, CancellationToken cancellationToken)`
- L169-174 _private* method_ `static async ValueTask RunXorAsync(AgentMessageChannel channel, ReadOnlyMemory<byte> source, byte value, CancellationToken cancellationToken)`
- L176-182 _private* method_ `static void XorData(ReadOnlySpan<byte> source, Span<byte> target, byte value)`
- L184-207 _private* method_ `async Task WriteFilesAsync(AgentMessageChannel channel, string path, BlobLocator locator, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default)`
- L209-245 _private* method_ `async Task<bool> VerifyFilesAsync(DirectoryReference outputDir, IBlobRef<DirectoryNode> directoryRef, CancellationToken cancellationToken = default)`
- L247-256 _private* method_ `void DeleteFiles(IReadOnlyList<string> deleteFiles)`
- L258-293 _private* method_ `async Task ExecuteProcessAsync( ComputeSocket socket, AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, string? containerImageUrl, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags, CancellationToken cancellationToken)`
- L295-317 _private* method_ `async Task ExecuteProcessWindowsAsync(ComputeSocket socket, AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags, CancellationToken cancellationToken)`
- L319-385 _internal method_ `internal static async Task ProcessIpcMessagesAsync(ComputeSocket socket, ComputeBufferReader ipcReader, CancellationToken[] cancellationTokens, ILogger logger)`
- L433-471 _private* method_ `async Task ExecuteProcessAssemblyAsync(AgentMessageChannel channel, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, CancellationToken cancellationToken)`
- L473-526 _private* method_ `async Task ExecuteProcessInContainerAsync(AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, string containerImageUrl, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags, CancellationToken cancellationToken)`
- L528-581 _private* method_ `async Task ExecuteProcessInternalAsync(AgentMessageChannel channel, string executable, IReadOnlyList<string> arguments, string? workingDir, IReadOnlyDictionary<string, string?>? envVars, ExecuteProcessFlags flags, CancellationToken cancellationToken)`
- L583-586 _private method_ `private string GetExecutableAbsPath(string relPath)`
- L588-591 _private method_ `private string GetWorkingDirAbsPath(string? relPath)`
- L598-626 _private method_ `private Dictionary<string, string> ResolveEnvVars(IReadOnlyDictionary<string, string?>? envVars)` — Flattens and merges available env vars to be used for compute process execution
- L633 _internal method_ `internal static extern uint getuid()` — attrs: `[DllImport("libc", SetLastError = true)]` — Get user identity (Linux only)
- L640 _internal method_ `internal static extern uint getgid()` — attrs: `[DllImport("libc", SetLastError = true)]` — Get group identity (Linux only)

#### class `EpicGames.Horde.Compute.AgentMessageHandler.ProcessOutputWriter`  
`class ProcessOutputWriter`  
_private*; L388-431_
- L390 _private* field_ `readonly string _prefix`
- L391 _private* field_ `readonly ByteArrayBuilder _lineBuffer = new()`
- L392 _private* field_ `readonly ILogger _logger`
- L394-398 _public ctor_ `public ProcessOutputWriter(string prefix, ILogger logger)`
- L400-430 _public method_ `public void WriteBytes(ReadOnlySpan<byte> span)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/AgentStorageClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.AgentStorageBackend`  
`public sealed class AgentStorageBackend : IStorageBackend, IDisposable`  
_public; L16-143_
- inherits: `IStorageBackend, IDisposable`
- desc: Storage backend which can read bundles over a compute channel
- L18 _private* field_ `readonly AgentMessageChannel _channel`
- L19 _private* field_ `readonly SemaphoreSlim _semaphore`
- L22 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L28-32 _public ctor_ `public AgentStorageBackend(AgentMessageChannel channel)` — Constructor
- L35-38 _public method_ `public void Dispose()` — (inheritdoc)
- L43-47 _public method_ `public async Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L50-54 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L56-68 _private* method_ `async ValueTask<ReadOnlyMemory<byte>> ReadBlobInternalAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)`
- L71 _public method_ `public Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L75 _public method_ `public Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? basePath = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L79 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L83 _public method_ `public ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator>? imports = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L87 _public method_ `public ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator>? imports = null, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L95 _public method_ `public Task AddAliasAsync(string name, BlobLocator locator, int rank, ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — (inheritdoc)
- L98 _public method_ `public Task RemoveAliasAsync(string name, BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L101 _public method_ `public Task<BlobAliasLocator[]> FindAliasesAsync(string name, int? maxResults, CancellationToken cancellationToken = default)` — (inheritdoc)
- L108 _public method_ `public Task<bool> DeleteRefAsync(RefName name, CancellationToken cancellationToken = default)` — (inheritdoc)
- L111 _public method_ `public Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L114 _public method_ `public Task WriteRefAsync(RefName name, HashedBlobRefValue value, RefOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L119-137 _public method_ `public async Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L140-142 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Buffers/PooledBuffer.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Buffers.PooledBuffer`  
`public sealed class PooledBuffer : ComputeBuffer`  
_public; L15-48_
- inherits: `ComputeBuffer`
- desc: In-process buffer used to store compute messages
- L21-24 _public ctor_ `public PooledBuffer(int capacity) : this(2, capacity / 2)` — Constructor
- L32-35 _public ctor_ `public PooledBuffer(int numChunks, int chunkLength, int numReaders = 1) : base(PooledBufferDetail.Create(numChunks, chunkLength, numReaders))` — Constructor
- L37-40 _private ctor_ `private PooledBuffer(ComputeBufferDetail resources) : base(resources)`
- L43-47 _public method_ `public override PooledBuffer AddRef()` — (inheritdoc)

#### class `EpicGames.Horde.Compute.Buffers.PooledBufferDetail`  
`class PooledBufferDetail : ComputeBufferDetail`  
_internal*; L53-115_
- inherits: `ComputeBufferDetail`
- desc: Core implementation of PooledBuffer
- L55 _private* field_ `GCHandle _headerHandle`
- L56 _private* field_ `IMemoryOwner<byte>[] _chunkOwners`
- L58 _private* field_ `readonly AsyncEvent _writerEvent = new()`
- L59 _private* field_ `readonly AsyncEvent _readerEvent = new()`
- L61-66 _internal ctor_ `internal PooledBufferDetail(HeaderPtr headerPtr, GCHandle headerHandle, Memory<byte>[] chunks, IMemoryOwner<byte>[] chunkOwners) : base(headerPtr, chunks)`
- L68-84 _public method_ `public static unsafe PooledBufferDetail Create(int numChunks, int chunkLength, int numReaders)`
- L87-102 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L105 _public method_ `public override void SetReadEvent(int readerIdx)` — (inheritdoc)
- L108 _public method_ `public override Task WaitToReadAsync(int readerIdx, CancellationToken cancellationToken)` — (inheritdoc)
- L111 _public method_ `public override void SetWriteEvent()` — (inheritdoc)
- L114 _public method_ `public override Task WaitToWriteAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Buffers/SharedMemoryBuffer.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Buffers.SharedMemoryBuffer`  
`public sealed class SharedMemoryBuffer : ComputeBuffer`  
_public; L16-60_
- inherits: `ComputeBuffer`
- desc: Core implementation of SharedMemoryBuffer
- L19 _public property_ `public string Name => ...` — (inheritdoc)
- L24-27 _private ctor_ `private SharedMemoryBuffer(ComputeBufferDetail resources) : base(resources)` — Constructor
- L30-34 _public method_ `public override SharedMemoryBuffer AddRef()` — (inheritdoc)
- L41-45 _public method_ `public static SharedMemoryBuffer CreateNew(string? name, long capacity)` — Create a new shared memory buffer
- L53 _public method_ `public static unsafe SharedMemoryBuffer CreateNew(string? name, int numChunks, int chunkLength)` — Create a new shared memory buffer
- L59 _public method_ `public static unsafe SharedMemoryBuffer OpenExisting(string name)` — Open an existing buffer by name

#### class `EpicGames.Horde.Compute.Buffers.SharedMemoryBufferDetail`  
`class SharedMemoryBufferDetail : ComputeBufferDetail`  
_internal*; L65-176_
- inherits: `ComputeBufferDetail`
- desc: Core implementation of SharedMemoryBuffer
- L67 _private* field_ `readonly MemoryMappedFile _memoryMappedFile`
- L68 _private* field_ `readonly MemoryMappedViewAccessor _memoryMappedViewAccessor`
- L69 _private* field_ `readonly MemoryMappedView _memoryMappedView`
- L71 _private* field_ `readonly Native.EventHandle _readerEvent`
- L72 _private* field_ `readonly Native.EventHandle _writerEvent`
- L74 _public property_ `public string Name { get; }`
- L76-87 _internal ctor_ `internal SharedMemoryBufferDetail(string name, HeaderPtr headerPtr, Memory<byte>[] chunks, MemoryMappedFile memoryMappedFile, MemoryMappedViewAccessor memoryMappedViewAccessor, MemoryMappedView memoryMappedView, Native.EventHandle readerEvent, Native.EventHandle writerEvent) : base(headerPtr, chunks)`
- L95-112 _public method_ `public static unsafe SharedMemoryBufferDetail CreateNew(string? name, int numChunks, int chunkLength)` — Create a new shared memory buffer
- L118-136 _public method_ `public static unsafe SharedMemoryBufferDetail OpenExisting(string name)` — Open an existing buffer by name
- L138-147 _private* method_ `static Memory<byte>[] CreateChunks(int numChunks, int chunkLength, MemoryMappedView memoryMappedView)`
- L150-163 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L166 _public method_ `public override void SetReadEvent(int readerIdx)` — (inheritdoc)
- L169 _public method_ `public override Task WaitToReadAsync(int readerIdx, CancellationToken cancellationToken)` — (inheritdoc)
- L172 _public method_ `public override void SetWriteEvent()` — (inheritdoc)
- L175 _public method_ `public override Task WaitToWriteAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Clients/AgentComputeClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Clients.AgentComputeClient`  
`public sealed class AgentComputeClient : IComputeClient`  
_public; L20-163_
- inherits: `IComputeClient`
- desc: Runs a local Horde Agent process to process compute requests without communicating with a server
- L22 _private field_ `private static readonly ClusterId s_cluster = new("_agent")`
- L65 _private* field_ `readonly string _hordeAgentAssembly`
- L66 _private* field_ `readonly int _port`
- L67 _private* field_ `readonly ILogger _logger`
- L75-80 _public ctor_ `public AgentComputeClient(string hordeAgentAssembly, int port, ILogger logger)` — Constructor
- L83-86 _public method_ `public Task<ClusterId> GetClusterAsync(Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L89-103 _public method_ `public async Task<IComputeLease?> TryAssignWorkerAsync(ClusterId? clusterId, Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, bool? useUbaCache, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L106-109 _public method_ `public Task DeclareResourceNeedsAsync(ClusterId clusterId, string pool, Dictionary<string, int> resourceNeeds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112-115 _public method_ `public Task<UbaConfig> AllocateUbaCacheServerAsync(ClusterId clusterId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L117-131 _private* method_ `async IAsyncEnumerable<RemoteComputeSocket> ConnectAsync(ILogger logger, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L133-162 _private* method_ `static async Task RunAgentAsync(string hordeAgentAssembly, int port, ILogger logger, CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Compute.Clients.AgentComputeClient.LeaseImpl`  
`class LeaseImpl : IComputeLease`  
_private*; L24-63_
- inherits: `IComputeLease`
- L26 _private* field_ `readonly IAsyncEnumerator<RemoteComputeSocket> _source`
- L29 _public property_ `public ClusterId Cluster { get; }` — (inheritdoc)
- L32 _public property_ `public IReadOnlyList<string> Properties { get; }` — (inheritdoc)
- L35 _public property_ `public IReadOnlyDictionary<string, int> AssignedResources => ...` — (inheritdoc)
- L38 _public property_ `public RemoteComputeSocket Socket => ...` — (inheritdoc)
- L41 _public property_ `public string Ip => ...` — (inheritdoc)
- L44 _public property_ `public UbaConfig? Uba => ...` — (inheritdoc)
- L47 _public property_ `public ConnectionMode ConnectionMode => ...` — (inheritdoc)
- L50 _public property_ `public IReadOnlyDictionary<string, ConnectionMetadataPort> Ports => ...` — (inheritdoc)
- L52 _public ctor_ `public LeaseImpl(IAsyncEnumerator<RemoteComputeSocket> source)`
- L55-59 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L62 _public method_ `public ValueTask CloseAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Clients/LocalComputeClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Clients.LocalComputeClient`  
`public sealed class LocalComputeClient : IComputeClient, IAsyncDisposable`  
_public; L18-117_
- inherits: `IComputeClient, IAsyncDisposable`
- desc: Implementation of IComputeClient which marshals data over a loopback connection to a method running on a background task in the same process.
- L20 _private field_ `private static readonly ClusterId s_cluster = new("_local")`
- L44 _private* field_ `readonly BackgroundTask _listenerTask`
- L45 _private* field_ `readonly Socket _listener`
- L46 _private* field_ `readonly Socket _socket`
- L47 _private* field_ `readonly bool _executeInProcess`
- L56-68 _public ctor_ `public LocalComputeClient(int port, DirectoryReference sandboxDir, bool executeInProcess, ILogger logger)` — Constructor
- L71-76 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L81-89 _private* method_ `static async Task RunListenerAsync(Socket listener, DirectoryReference sandboxDir, bool executeInProcess, ILogger logger, CancellationToken cancellationToken)` — Sets up the loopback listener and calls the server method
- L92-95 _public method_ `public Task<ClusterId> GetClusterAsync(Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L98-104 _public method_ `public Task<IComputeLease?> TryAssignWorkerAsync(ClusterId? clusterId, Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, bool? useUbaCache, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L107-110 _public method_ `public Task DeclareResourceNeedsAsync(ClusterId clusterId, string pool, Dictionary<string, int> resourceNeeds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L113-116 _public method_ `public Task<UbaConfig> AllocateUbaCacheServerAsync(ClusterId clusterId, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.Clients.LocalComputeClient.LeaseImpl`  
`class LeaseImpl : IComputeLease`  
_private*; L22-42_
- inherits: `IComputeLease`
- L24 _public property_ `public ClusterId Cluster { get; }`
- L25 _public property_ `public IReadOnlyList<string> Properties { get; }`
- L26 _public property_ `public IReadOnlyDictionary<string, int> AssignedResources => ...`
- L27 _public property_ `public RemoteComputeSocket Socket => ...`
- L28 _public property_ `public string Ip => ...`
- L29 _public property_ `public UbaConfig? Uba => ...`
- L30 _public property_ `public ConnectionMode ConnectionMode => ...`
- L31 _public property_ `public IReadOnlyDictionary<string, ConnectionMetadataPort> Ports => ...`
- L33 _private* field_ `readonly RemoteComputeSocket _socket`
- L35 _public ctor_ `public LeaseImpl(RemoteComputeSocket socket)`
- L38 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L41 _public method_ `public ValueTask CloseAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Clients/ServerComputeClient.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Compute.Clients.TunnelHandshakeRequest`  
`public record TunnelHandshakeRequest(string Host, int Port)`  
_public; L25-54_
- desc: Handshake request message for tunneling server
- L27 _private* const_ `const int Version = 1`
- L28 _private* const_ `const string Name = "HANDSHAKE-REQ"`
- L34-37 _public method_ `public string Serialize()` — Serialize the message
- L45-53 _public method_ `public static TunnelHandshakeRequest Deserialize(string? text)` — Deserialize the message

#### record `EpicGames.Horde.Compute.Clients.TunnelHandshakeResponse`  
`public record TunnelHandshakeResponse(bool IsSuccess, string Message)`  
_public; L61-90_
- desc: Handshake response message for tunneling server
- L63 _private* const_ `const int Version = 1`
- L64 _private* const_ `const string Name = "HANDSHAKE-RES"`
- L70-73 _public method_ `public string Serialize()` — Serialize the message
- L81-89 _public method_ `public static TunnelHandshakeResponse Deserialize(string? text)` — Deserialize the message

#### class `EpicGames.Horde.Compute.Clients.ServerComputeClientException`  
`public class ServerComputeClientException : ComputeException`  
_public; L95-106_
- inherits: `ComputeException`
- desc: Exception for ServerComputeClient
- L98-100 _public ctor_ `public ServerComputeClientException(string message) : base(message)` — (inheritdoc)
- L103-105 _public ctor_ `public ServerComputeClientException(string? message, Exception? innerException) : base(message, innerException)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.Clients.ServerComputeClient`  
`public sealed class ServerComputeClient : IComputeClient, IDisposable`  
_public; L111-536_
- inherits: `IComputeClient, IDisposable`
- desc: Helper class to enlist remote resources to perform compute-intensive tasks.
- L116 _public const_ `public const int NonceLength = 64` — Length of the nonce sent as part of handshaking between initiator and remote
- L183 _private* field_ `readonly HttpClient _httpClient`
- L184 _private* field_ `readonly CancellationTokenSource _cancellationSource = new()`
- L185 _private* field_ `readonly string _sessionId`
- L186 _private* field_ `readonly ILogger _logger`
- L193-195 _public ctor_ `public ServerComputeClient(HttpClient httpClient, ILogger logger) : this(httpClient, null, logger)` — Constructor
- L203-208 _public ctor_ `public ServerComputeClient(HttpClient httpClient, string? sessionId, ILogger logger)` — Constructor
- L211-214 _public method_ `public void Dispose()` — (inheritdoc)
- L217-241 _public method_ `public async Task<ClusterId> GetClusterAsync(Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L244-261 _public method_ `public async Task<IComputeLease?> TryAssignWorkerAsync(ClusterId? clusterId, Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, bool? useUbaCache, ILogger logger, CancellationToken cancellationToken)` — (inheritdoc)
- L264-269 _public method_ `public async Task DeclareResourceNeedsAsync(ClusterId clusterId, string pool, Dictionary<string, int> resourceNeeds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L272-298 _public method_ `public async Task<UbaConfig> AllocateUbaCacheServerAsync(ClusterId clusterId, CancellationToken cancellationToken = default)` — (inheritdoc)
- L300-439 _private* method_ `async IAsyncEnumerable<LeaseInfo> ConnectAsync(ClusterId? clusterId, Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, bool? useUbaCache, ILogger workerLogger, [EnumeratorCancellation] CancellationToken cancellationToken)`
- L441-472 _private method_ `private async Task ConnectWithRetryAsync(Socket socket, string host, int port, TimeSpan timeout, int maxRetries, CancellationToken cancellationToken)`
- L474-494 _private method_ `private static async Task<ComputeTransport> CreateTransportAsync(Socket socket, AssignComputeResponse response, CancellationToken cancellationToken)`
- L496-509 _private method_ `private static (string host, int port) ParseHostPort(string address)`
- L511-535 _private method_ `private static async Task TunnelHandshakeAsync(Socket socket, AssignComputeResponse response, CancellationToken cancellationToken)`

#### record `EpicGames.Horde.Compute.Clients.ServerComputeClient.LeaseInfo`  
`record LeaseInfo( ClusterId Cluster, IReadOnlyList<string> Properties, IReadOnlyDictionary<string, int> AssignedResources, RemoteComputeSocket Socket, string Ip, UbaConfig? Uba, ConnectionMode ConnectionMode, IReadOnlyDictionary<string, ConnectionMetadataPort> Ports)`  
_private*; L118-118_

#### class `EpicGames.Horde.Compute.Clients.ServerComputeClient.LeaseImpl`  
`class LeaseImpl : IComputeLease`  
_private*; L128-181_
- inherits: `IComputeLease`
- L130 _public property_ `public ClusterId Cluster => ...`
- L131 _public property_ `public IReadOnlyList<string> Properties => ...`
- L132 _public property_ `public IReadOnlyDictionary<string, int> AssignedResources => ...`
- L133 _public property_ `public RemoteComputeSocket Socket => ...`
- L134 _public property_ `public string Ip => ...`
- L135 _public property_ `public UbaConfig? Uba => ...`
- L136 _public property_ `public ConnectionMode ConnectionMode => ...`
- L137 _public property_ `public IReadOnlyDictionary<string, ConnectionMetadataPort> Ports => ...`
- L139 _private field_ `private readonly IAsyncEnumerator<LeaseInfo> _source`
- L140 _private field_ `private BackgroundTask? _pingTask`
- L142-146 _public ctor_ `public LeaseImpl(IAsyncEnumerator<LeaseInfo> source)`
- L149-159 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L162-171 _public method_ `public async ValueTask CloseAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L173-180 _private* method_ `async Task PingAsync(CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Compute.Clients.NoComputeAgentsFoundException`  
`public sealed class NoComputeAgentsFoundException : ComputeClientException`  
_public; L541-562_
- inherits: `ComputeClientException`
- desc: Exception indicating that no matching compute agents were found
- L546 _public property_ `public ClusterId ClusterId { get; }` — The compute cluster requested
- L551 _public property_ `public Requirements? Requirements { get; }` — Requested agent requirements
- L556-561 _public ctor_ `public NoComputeAgentsFoundException(ClusterId clusterId, Requirements? requirements) : base($"No compute agents found matching '{requirements}' in cluster '{clusterId}'")` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Compute/ClusterId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Compute.ClusterId`  
`public readonly struct ClusterId : IEquatable<ClusterId>`  
_public; L21-54_
- attrs: `[LogValueType] [JsonSchemaString] [CbConverter(typeof(ClusterIdCbConverter))] [JsonConverter(typeof(ClusterIdJsonConverter))] [TypeConverter(typeof(ClusterIdTypeConverter))]`
- inherits: `IEquatable<ClusterId>`
- desc: Identifier for a compute cluster
- L26 _private* field_ `readonly StringId _inner` — The text representing this id
- L32-35 _public ctor_ `public ClusterId(string input)` — Constructor
- L38 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L41 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L44 _public method_ `public bool Equals(ClusterId other)` — (inheritdoc)
- L47 _public method_ `public override string ToString()` — (inheritdoc)
- L50 _public operator_ `public static bool operator ==(ClusterId left, ClusterId right)` — (inheritdoc)
- L53 _public operator_ `public static bool operator !=(ClusterId left, ClusterId right)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ClusterIdCbConverter`  
`sealed class ClusterIdCbConverter : CbConverter<ClusterId>`  
_internal*; L59-69_
- inherits: `CbConverter<ClusterId>`
- desc: Compact binary converter for ClusterId
- L62 _public method_ `public override ClusterId Read(CbField field)` — (inheritdoc)
- L65 _public method_ `public override void Write(CbWriter writer, ClusterId value)` — (inheritdoc)
- L68 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, ClusterId value)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ClusterIdJsonConverter`  
`sealed class ClusterIdJsonConverter : JsonConverter<ClusterId>`  
_internal*; L74-81_
- inherits: `JsonConverter<ClusterId>`
- desc: Type converter for ClusterId to and from JSON
- L77 _public method_ `public override ClusterId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L80 _public method_ `public override void Write(Utf8JsonWriter writer, ClusterId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ClusterIdTypeConverter`  
`sealed class ClusterIdTypeConverter : TypeConverter`  
_internal*; L86-93_
- inherits: `TypeConverter`
- desc: Type converter from strings to ClusterId objects
- L89 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type? sourceType)` — (inheritdoc)
- L92 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object? value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeBuffer.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ComputeBuffer`  
`public abstract class ComputeBuffer : IDisposable`  
_public; L13-79_
- inherits: `IDisposable`
- desc: In-process buffer used to store compute messages
- L18 _public const_ `public const int MaxChunks = 16` — Maximum number of chunks in a buffer
- L23 _public const_ `public const int MaxReaders = 16` — Maximum number of readers
- L25 _internal field_ `internal ComputeBufferDetail _detail`
- L31-34 _internal ctor_ `internal ComputeBuffer(ComputeBufferDetail detail)` — Constructor
- L37-41 _public method_ `public void Dispose()` — (inheritdoc)
- L46-53 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L58-63 _public method_ `public ComputeBufferReader CreateReader()` — Creates a new reader for this buffer
- L68-73 _public method_ `public ComputeBufferWriter CreateWriter()` — Writer for this buffer
- L78 _public method_ `public abstract ComputeBuffer AddRef()` — Creates a new reference to the underlying buffer. The underlying resources will only be destroyed once all instances are disposed of.

#### class `EpicGames.Horde.Compute.ComputeBufferReader`  
`public sealed class ComputeBufferReader : IDisposable`  
_public; L84-169_
- inherits: `IDisposable`
- desc: Read interface for a compute buffer
- L86 _private* field_ `ComputeBufferDetail _buffer`
- L87 _private* field_ `readonly int _readerIdx`
- L89 _internal property_ `internal ComputeBufferDetail Detail => ...`
- L91-95 _internal ctor_ `internal ComputeBufferReader(ComputeBufferDetail buffer, int readerIdx)`
- L100-105 _public method_ `public ComputeBufferReader AddRef()` — Create a new reader instance using the same underlying buffer
- L108-116 _public method_ `public void Dispose()` — (inheritdoc)
- L121 _public method_ `public void Detach()` — Detaches this reader from the underlying buffer
- L126 _public property_ `public bool IsComplete => ...` — Whether this buffer is complete (no more data will be added)
- L132 _public method_ `public void AdvanceReadPosition(int length)` — Updates the read position
- L138 _public method_ `public ReadOnlyMemory<byte> GetReadBuffer()` — Gets the next data to read
- L146-160 _public method_ `public async ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — Read from a buffer into another buffer
- L168 _public method_ `public ValueTask<bool> WaitToReadAsync(int minLength, CancellationToken cancellationToken = default)` — Wait for data to be available, or for the buffer to be marked as complete

#### class `EpicGames.Horde.Compute.ComputeBufferWriter`  
`public sealed class ComputeBufferWriter : IDisposable`  
_public; L174-245_
- inherits: `IDisposable`
- desc: Buffer that can receive data from a remote machine.
- L176 _private* field_ `ComputeBufferDetail _detail`
- L178 _internal property_ `internal ComputeBufferDetail Detail => ...`
- L180 _internal ctor_ `internal ComputeBufferWriter(ComputeBufferDetail detail)`
- L185-190 _public method_ `public ComputeBufferWriter AddRef()` — Create a new writer instance using the same underlying buffer
- L193-201 _public method_ `public void Dispose()` — (inheritdoc)
- L204 _public method_ `public void AdvanceWritePosition(int size)` — (inheritdoc)
- L210 _public method_ `public Memory<byte> GetWriteBuffer()` — Gets memory to write to
- L216 _public method_ `public bool MarkComplete()` — Mark the output to this buffer as complete
- L223-236 _public method_ `public async ValueTask WriteAsync(ReadOnlyMemory<byte> buffer, CancellationToken cancellationToken = default)` — Writes data into a buffer from a memory block
- L244 _public method_ `public ValueTask WaitToWriteAsync(int minLength, CancellationToken cancellationToken = default)` — Gets memory to write to

#### class `EpicGames.Horde.Compute.ComputeBufferDetail`  
`internal abstract class ComputeBufferDetail : IDisposable`  
_internal; L251-927_
- attrs: `[DebuggerTypeProxy(typeof(BufferDebugProxy))]`
- inherits: `IDisposable`
- desc: State shared between buffer instances
- L253 _internal const_ `internal const int HeaderSize = (2 + ComputeBuffer.MaxReaders + ComputeBuffer.MaxChunks) * sizeof(ulong)`
- L470 _private* field_ `HeaderPtr _headerPtr`
- L471 _private* field_ `Memory<byte>[] _chunks`
- L472 _private* field_ `int _refCount = 1`
- L477-481 _protected ctor_ `protected ComputeBufferDetail(HeaderPtr headerPtr, Memory<byte>[] chunks)` — Constructor
- L486-489 _public method_ `public void AddRef()` — Increment the reference count on this object
- L494-500 _public method_ `public void Release()` — Decrement the reference count on this object, and dispose of it once it reaches zero
- L503-507 _public method_ `public void Dispose()` — (inheritdoc)
- L512-516 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L521 _public method_ `public abstract void SetReadEvent(int readerIdx)` — Signals a read event
- L526-532 _public method_ `public void SetAllReadEvents()` — Signals read events for every reader
- L537 _public method_ `public abstract Task WaitToReadAsync(int readerIdx, CancellationToken cancellationToken)` — Waits for a read event to be signalled
- L542 _public method_ `public abstract void SetWriteEvent()` — Signals the write event
- L547 _public method_ `public abstract Task WaitToWriteAsync(CancellationToken cancellationToken)` — Waits for the write event to be signalled
- L552-587 _public method_ `public int CreateReader()` — Allocate a new reader
- L589-604 _public method_ `public void AddReaderRef(int readerIdx)`
- L606-630 _public method_ `public void ReleaseReaderRef(int readerIdx)`
- L632-656 _public method_ `public void CreateWriter()`
- L658-673 _public method_ `public void AddWriterRef()`
- L675-696 _public method_ `public void ReleaseWriterRef()`
- L699-709 _public method_ `public bool IsComplete(int readerIdx)` — (inheritdoc)
- L712-724 _public method_ `public void DetachReader(int readerIdx)` — (inheritdoc)
- L727-739 _public method_ `public void AdvanceReadPosition(int readerIdx, int offset)` — (inheritdoc)
- L742-757 _public method_ `public ReadOnlyMemory<byte> GetReadBuffer(int readerIdx)` — (inheritdoc)
- L760-813 _public method_ `public async ValueTask<bool> WaitToReadAsync(int readerIdx, int minLength, CancellationToken cancellationToken = default)` — (inheritdoc)
- L816-829 _public method_ `public bool MarkComplete()` — (inheritdoc)
- L832-846 _public method_ `public void AdvanceWritePosition(int size)` — (inheritdoc)
- L849-862 _public method_ `public Memory<byte> GetWriteBuffer()` — (inheritdoc)
- L865-926 _public method_ `public async ValueTask WaitToWriteAsync(int minSize, CancellationToken cancellationToken = default)` — (inheritdoc)

#### enum `EpicGames.Horde.Compute.ComputeBufferDetail.WriteState`  
`protected internal enum WriteState`  
_protected internal; L258-274_
- desc: Write state for a chunk
- L263 _public* enumerator_ `MovedToNext = 0` — Writer has moved to the next chunk
- L268 _public* enumerator_ `Writing = 2` — Chunk is still being appended to
- L273 _public* enumerator_ `Complete = 3` — This chunk marks the end of the stream

#### record struct `EpicGames.Horde.Compute.ComputeBufferDetail.ChunkState`  
`protected internal record struct ChunkState(ulong Value)`  
_protected internal; L279-298_
- desc: Stores the state of a chunk in a 64-bit value, which can be updated atomically
- L282 _public property_ `public readonly int Length => ...`
- L285 _public property_ `public readonly int ReaderFlags => ...`
- L288 _public property_ `public readonly WriteState WriteState => ...`
- L291 _public ctor_ `public ChunkState(WriteState writerState, int readerFlags, int length) : this(((ulong)writerState << 62) | ((ulong)readerFlags << 31) | (uint)length)`
- L294 _public method_ `public readonly bool HasReaderFlag(int readerIdx)`
- L297 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### struct `EpicGames.Horde.Compute.ComputeBufferDetail.ChunkStatePtr`  
`protected internal readonly unsafe struct ChunkStatePtr`  
_protected internal; L303-335_
- desc: Wraps a pointer to the state of a chunk
- L305 _private* field_ `readonly ulong* _data`
- L307 _public ctor_ `public ChunkStatePtr(ulong* data)`
- L310 _public method_ `public ChunkState Get()`
- L313 _public method_ `public void Set(ChunkState value)`
- L316 _public method_ `public bool TryUpdate(ChunkState prevState, ChunkState nextState)`
- L319 _public method_ `public void Append(int length)`
- L322 _public method_ `public void MarkComplete()`
- L325 _public method_ `public void StartReading(int readerIdx)`
- L328 _public method_ `public void FinishReading(int readerIdx)`
- L331 _public method_ `public void FinishWriting()`
- L334 _public method_ `public override string ToString()` — (inheritdoc)

#### record struct `EpicGames.Horde.Compute.ComputeBufferDetail.ReaderState`  
`protected internal record struct ReaderState(ulong Value)`  
_protected internal; L340-353_
- desc: State of a reader
- L342-344 _public ctor_ `public ReaderState(int chunkIdx, int offset, int refCount, bool detached) : this((ulong)(uint)offset | ((ulong)(uint)chunkIdx << 32) | ((ulong)(uint)refCount << 40) | ((ulong)((detached ? (1UL << 63) : 0))))`
- L346 _public property_ `public readonly int Offset => ...`
- L347 _public property_ `public readonly int ChunkIdx => ...`
- L348 _public property_ `public readonly int RefCount => ...`
- L349 _public property_ `public readonly bool Detached => ...`
- L352 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### struct `EpicGames.Horde.Compute.ComputeBufferDetail.ReaderStatePtr`  
`protected internal readonly unsafe struct ReaderStatePtr`  
_protected internal; L358-372_
- desc: Wraps a pointer to the state of a writer
- L360 _private* field_ `readonly ulong* _data`
- L362 _public ctor_ `public ReaderStatePtr(ulong* data)`
- L365 _public method_ `public ReaderState Get()`
- L368 _public method_ `public void Set(ReaderState value)`
- L371 _public method_ `public bool TryUpdate(ReaderState prevState, ReaderState nextState)`

#### record struct `EpicGames.Horde.Compute.ComputeBufferDetail.WriterState`  
`protected internal record struct WriterState(ulong Value)`  
_protected internal; L377-390_
- desc: State of the writer
- L379-381 _public ctor_ `public WriterState(int chunkIdx, int readerFlags, int refCount, bool hasWrapped) : this((ulong)(uint)chunkIdx | ((ulong)(uint)readerFlags << 32) | ((ulong)(uint)refCount << 48) | (hasWrapped ? (1UL << 63) : 0))`
- L383 _public property_ `public readonly int ChunkIdx => ...`
- L384 _public property_ `public readonly int ReaderFlags => ...`
- L385 _public property_ `public readonly int RefCount => ...`
- L386 _public property_ `public readonly bool HasWrapped => ...`
- L389 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### struct `EpicGames.Horde.Compute.ComputeBufferDetail.WriterStatePtr`  
`protected internal readonly unsafe struct WriterStatePtr`  
_protected internal; L395-409_
- desc: Wraps a pointer to the state of a writer
- L397 _private* field_ `readonly ulong* _data`
- L399 _public ctor_ `public WriterStatePtr(ulong* data)`
- L402 _public method_ `public WriterState Get()`
- L405 _public method_ `public void Set(WriterState state)`
- L408 _public method_ `public bool TryUpdate(WriterState prevState, WriterState nextState)`

#### struct `EpicGames.Horde.Compute.ComputeBufferDetail.HeaderPtr`  
`protected internal readonly unsafe struct HeaderPtr`  
_protected internal; L414-437_
- desc: Tracked state of the buffer
- L416 _private* field_ `readonly ulong* _data`
- L418 _public ctor_ `public HeaderPtr(ulong* data)`
- L420-426 _public ctor_ `public HeaderPtr(ulong* data, int numReaders, int numChunks, int chunkLength)`
- L428 _public property_ `public int NumReaders => ...`
- L429 _public property_ `public int NumChunks => ...`
- L430 _public property_ `public int ChunkLength => ...`
- L432 _public method_ `public WriterStatePtr GetWriterStatePtr()`
- L434 _public method_ `public ReaderStatePtr GetReaderStatePtr(int readerIdx)`
- L436 _public method_ `public ChunkStatePtr GetChunkStatePtr(int chunkIdx)`

#### class `EpicGames.Horde.Compute.ComputeBufferDetail.BufferDebugProxy`  
`class BufferDebugProxy`  
_private*; L439-468_
- L441 _public property_ `public int ChunkLength { get; }`
- L442 _public property_ `public int RefCount { get; }`
- L443 _public property_ `public WriterState Writer { get; }`
- L444 _public property_ `public ReaderState[] Readers { get; }`
- L445 _public property_ `public ChunkState[] Chunks { get; }`
- L447-467 _public ctor_ `public BufferDebugProxy(ComputeBufferDetail buffer)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeChannel.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ComputeChannel`  
`public sealed class ComputeChannel : IDisposable`  
_public; L13-93_
- inherits: `IDisposable`
- desc: Conventional TCP-like interface for writing data to a socket. Sends are "push", receives are "pull".
- L18 _public property_ `public ComputeBufferReader Reader { get; }` — Reader for the channel
- L23 _public property_ `public ComputeBufferWriter Writer { get; }` — Writer for the channel
- L30-34 _internal ctor_ `internal ComputeChannel(ComputeBufferReader recvBufferReader, ComputeBufferWriter sendBufferWriter)` — Constructor
- L37-41 _public method_ `public void Dispose()` — (inheritdoc)
- L48 _public method_ `public ValueTask SendAsync(ReadOnlyMemory<byte> memory, CancellationToken cancellationToken = default)` — Sends data to a remote channel
- L55 _public method_ `public ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — Marks a channel as complete
- L62-68 _public method_ `public async ValueTask RecvMessageAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — Reads a complete message from the given socket, retrying reads until the buffer is full.
- L75-87 _public method_ `public async ValueTask<bool> TryRecvMessageAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — Reads either a full message or end of stream from the channel
- L92 _public method_ `public void MarkComplete()` — Mark the channel as complete (ie. that no more data will be sent)

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeExceptions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ComputeException`  
`public class ComputeException : Exception`  
_public; L10-21_
- inherits: `Exception`
- desc: Generic class for compute errors
- L13-15 _public ctor_ `public ComputeException(string message) : base(message)` — (inheritdoc)
- L18-20 _public ctor_ `public ComputeException(string? message, Exception? innerException) : base(message, innerException)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ComputeInternalException`  
`public sealed class ComputeInternalException : ComputeException`  
_public; L26-36_
- inherits: `ComputeException`
- desc: Exception thrown for internal reasons
- L32-35 _public ctor_ `public ComputeInternalException(string message) : base(message)` — Constructor

#### class `EpicGames.Horde.Compute.ComputeRemoteException`  
`public sealed class ComputeRemoteException : ComputeException`  
_public; L41-64_
- inherits: `ComputeException`
- desc: Exception thrown on a remote machine
- L43 _private* field_ `readonly string _description`
- L48-51 _public ctor_ `public ComputeRemoteException(ExceptionMessage message) : this("Remote exception: " + message.Message, message.Description)` — Constructor
- L56-60 _public ctor_ `public ComputeRemoteException(string message, string description) : base(message)` — Constructor
- L63 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ConnectionMetadataPort`  
`public class ConnectionMetadataPort`  
_public; L16-44_
- desc: Describes port used by a compute task
- L21 _public const_ `public const string ComputeId = "_horde_compute"` — Built-in port used for agent and compute task communication
- L27 _public property_ `public int Port { get; }` — Externally visible port that is mapped to agent port In direct connection mode, these two are identical.
- L32 _public property_ `public int AgentPort { get; }` — Port the local process on the agent is listening on
- L39-43 _public ctor_ `public ConnectionMetadataPort(int port, int agentPort)` — Constructor

#### class `EpicGames.Horde.Compute.AllocateUbaCacheServerRequest`  
`public class AllocateUbaCacheServerRequest`  
_public; L49-51_
- desc: Request for allocating a UBA cache server/session

#### class `EpicGames.Horde.Compute.UbaConfig`  
`public class UbaConfig(string cacheEndpoint, string cacheSessionKey, bool writeAccess)`  
_public; L57-73_
- desc: Configuration settings for Unreal Build Accelerator (UBA) for a compute task invocation Contains cache server connectivity and other UBA-related settings.
- L62 _public property_ `public string CacheEndpoint { get; }` — Network endpoint (IP address and port) for connecting to the UBA cache server
- L67 _public property_ `public string CacheSessionKey { get; }` — AES encryption key used for secure client-server communication with the UBA cache server
- L72 _public property_ `public bool WriteAccess { get; }` — Session has write access to cache

#### class `EpicGames.Horde.Compute.AssignComputeRequest`  
`public class AssignComputeRequest`  
_public; L78-106_
- desc: Request a machine to execute compute requests
- L83 _public property_ `public int Protocol { get; set; }` — Desired protocol version for the client
- L88 _public property_ `public Requirements? Requirements { get; set; }` — Condition to identify machines that can execute the request
- L94 _public property_ `public string? RequestId { get; set; }` — Arbitrary ID to correlate the same request over multiple calls. It's recommended to pick something globally unique, such as a UUID.
- L99 _public property_ `public ConnectionMetadataRequest? Connection { get; set; }` — Details for making an agent connection
- L105 _public property_ `public bool? UseUbaCache { get; init; }` — Whether to allocate an Unreal Build Accelerator (UBA) cache server session for this compute request. If requested, a UBA cache server must be defined for the compute cluster. Null is treated as false.

#### class `EpicGames.Horde.Compute.ConnectionMetadataRequest`  
`public class ConnectionMetadataRequest`  
_public; L111-149_
- desc: Request details for making an agent connection
- L118 _public property_ `public string? ClientPublicIp { get; set; }` — Public IP of client requesting a compute resource (initiator) As communication between client and Horde server may be on an internal network, the client is responsible for resolving and providing this information.
- L126 _public property_ `public Dictionary<string, int> Ports { get; set; }` — TCP/IP ports the compute resource will listen to. Key = arbitrary name identifying the port Value = actual port number Relay connection mode uses this information to set up port forwarding.
- L131 _public property_ `public ConnectionMode? ModePreference { get; set; }` — Type of connection mode that is preferred by the client. Server can still override.
- L137 _public property_ `public bool? PreferPublicIp { get; set; }` — Prefer connecting to agent over a public IP even if a more optimal route is available. Server can still override. This is useful to avoid sending traffic over VPN tunnels.
- L142 _public property_ `public Encryption? Encryption { get; set; }` — Encryption mode to request. Server can still override.
- L148 _public property_ `public int? InactivityTimeoutMs { get; set; }` — Maximum duration (in milliseconds) that communication can be inactive between the compute client and task-running agent before the connection is terminated.

#### class `EpicGames.Horde.Compute.GetClusterResponse`  
`public class GetClusterResponse`  
_public; L154-160_
- desc: Response to a cluster lookup request
- L159 _public property_ `public ClusterId ClusterId { get; set; }` — Compute cluster ID

#### class `EpicGames.Horde.Compute.AssignComputeResponse`  
`public class AssignComputeResponse`  
_public; L165-255_
- desc: Response to compute allocation request
- L170 _public property_ `public string Ip { get; set; }` — IP address of the remote agent machine running the compute task
- L175 _public property_ `public ConnectionMode ConnectionMode { get; set; }` — How to establish a connection to the remote machine
- L180 _public property_ `public string? ConnectionAddress { get; set; }` — An optional address (host:port) to use when connecting to agent via tunnel or relay mode
- L185 _public property_ `public int Port { get; set; }` — Port number on the remote machine
- L196 _public property_ `public IReadOnlyDictionary<string, ConnectionMetadataPort> Ports { get; set; }` — Assigned ports (externally visible port -> local port on agent) Key is an arbitrary name identifying the port (same as was given in ConnectionMetadataRequest) When relay mode is used, ports can mapped to a different externally visible port. If compute task uses and listens to port 7000, that port can be externally represented as something else. For example, port 32743 can be pointed to port 7000. This makes no difference for the compute task process, but the client/initiator making connections must pay attention to this mapping.
- L201 _public property_ `public Encryption Encryption { get; set; }` — Encryption used
- L206 _public property_ `public string Nonce { get; set; }` — Cryptographic nonce to identify the request, as a hex string
- L211 _public property_ `public string Key { get; set; }` — AES key for the channel, as a hex string
- L216 _public property_ `public string Certificate { get; set; }` — X.509 certificate used for SSL/TLS encryption
- L219 _public property_ `public UbaConfig? Uba { get; set; }` — (inheritdoc)
- L224 _public property_ `public ClusterId ClusterId { get; set; }` — Which cluster this remote machine belongs to
- L229 _public property_ `public AgentId AgentId { get; set; }` — Identifier for the remote machine
- L234 _public property_ `public string? AgentVersion { get; set; }` — Agent version for the remote machine
- L239 _public property_ `public LeaseId LeaseId { get; set; }` — Identifier for the new lease on the remote machine
- L244 _public property_ `public Dictionary<string, int> AssignedResources { get; set; }` — Resources assigned to this machine
- L249 _public property_ `public int Protocol { get; set; }` — Version number for the compute protocol
- L254 _public property_ `public IReadOnlyList<string> Properties { get; set; }` — Properties of the agent assigned to do the work

#### enum `EpicGames.Horde.Compute.ConnectionMode`  
`public enum ConnectionMode`  
_public; L261-280_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- desc: Describe how to connect to the remote machine
- L266 _public* enumerator_ `Direct` — Connection is established directly to remote machine, behaving like a normal TCP/UDP connection
- L273 _public* enumerator_ `Tunnel` — Connection is tunneled through Horde server. When connecting, initiator must send a tunnel handshake request indicating which machine/IP to tunnel to. Once handshake is complete, TCP connection behaves as normal (UDP not supported)
- L279 _public* enumerator_ `Relay` — Connection is established to remote machine via a relay. Forwarding is transparent and behaves like a normal TCP/UDP connection.

#### enum `EpicGames.Horde.Compute.Encryption`  
`public enum Encryption`  
_public; L286-307_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- desc: Describe encryption for the compute resource connection
- L291 _public* enumerator_ `None` — No encryption enabled
- L296 _public* enumerator_ `Aes` — Use custom AES-based encryption transport
- L301 _public* enumerator_ `Ssl` — Use SSL/TLS encryption with RSA 2048-bits
- L306 _public* enumerator_ `SslEcdsaP256` — Use SSL/TLS encryption with ECDSA P-256

#### class `EpicGames.Horde.Compute.ResourceNeedsMessage`  
`public class ResourceNeedsMessage`  
_public; L312-328_
- desc: Resource needs declaration request
- L317 _public property_ `public string SessionId { get; set; }` — Unique session ID performing compute resource requests
- L322 _public property_ `public string Pool { get; set; }` — Pool of agents requesting resources from
- L327 _public property_ `public Dictionary<string, int> ResourceNeeds { get; set; }` — Key/value of resources needed by session (such as CPU or memory, see KnownPropertyNames in Horde.Server)

#### class `EpicGames.Horde.Compute.GetResourceNeedsResponse`  
`public class GetResourceNeedsResponse`  
_public; L333-339_
- desc: Resource needs response
- L338 _public property_ `public List<ResourceNeedsMessage> ResourceNeeds { get; set; }` — List of resource needs

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeProtocol.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Compute.ComputeProtocol`  
`public enum ComputeProtocol`  
_public; L14-35_
- desc: Version number for the compute protocol
- L19 _public* enumerator_ `Unknown` — No version specified
- L24 _public* enumerator_ `Initial` — Initial version number
- L29 _public* enumerator_ `NewCpuEnvVars` — Set new env vars UE_HORDE_CPU_COUNT and UE_HORDE_CPU_MULTIPLIER
- L34 _public* enumerator_ `Latest = (int)NewCpuEnvVars` — Constant for the latest protocol version

#### class `EpicGames.Horde.Compute.ComputeProtocolUtilities`  
`public static class ComputeProtocolUtilities`  
_public; L40-56_
- desc: Helper methods for compute protocol version numbers
- L45-55 _public method_ `public static BundleOptions GetBundleOptions(ComputeProtocol protocol)` — Gets the appropriate bundle options for a compute protocol version number

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeSocket.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ComputeSocket`  
`public abstract class ComputeSocket`  
_public; L21-74_
- desc: Socket for sending and reciving data using a "push" model. The application can attach multiple writers to accept received data.
- L26 _public property_ `public abstract ComputeProtocol Protocol { get; }` — The current protocol number
- L31 _public property_ `public abstract ILogger Logger { get; }` — Logger for diagnostic messages
- L38 _public method_ `public abstract void AttachRecvBuffer(int channelId, ComputeBuffer recvBuffer)` — Attaches a buffer to receive data.
- L45 _public method_ `public abstract void AttachSendBuffer(int channelId, ComputeBuffer sendBuffer)` — Attaches a buffer to send data.
- L51-56 _public method_ `public ComputeChannel CreateChannel(int channelId)` — Creates a channel using a socket and receive buffer
- L64-73 _public method_ `public ComputeChannel CreateChannel(int channelId, ComputeBuffer recvBuffer, ComputeBuffer sendBuffer)` — Creates a channel using a socket and receive buffer

#### enum `EpicGames.Horde.Compute.IpcMessage`  
`internal enum IpcMessage`  
_internal; L76-80_
- L78 _public* enumerator_ `AttachRecvBuffer = 0`
- L79 _public* enumerator_ `AttachSendBuffer = 1`

#### class `EpicGames.Horde.Compute.WorkerComputeSocket`  
`public sealed class WorkerComputeSocket : ComputeSocket, IDisposable`  
_public; L85-173_
- inherits: `ComputeSocket, IDisposable`
- desc: Provides functionality for attaching buffers for compute workers
- L90 _public const_ `public const string IpcEnvVar = "UE_HORDE_COMPUTE_IPC"` — Name of the environment variable for passing the name of the compute channel
- L92 _private* field_ `readonly ComputeBufferWriter _commandBufferWriter`
- L93 _private* field_ `readonly List<ComputeBuffer> _buffers = []`
- L94 _private* field_ `readonly ILogger _logger`
- L97 _public property_ `public override ComputeProtocol Protocol => ...` — (inheritdoc)
- L100 _public property_ `public override ILogger Logger => ...` — (inheritdoc)
- L105-109 _private ctor_ `private WorkerComputeSocket(ComputeBufferWriter commandBufferWriter, ILogger logger)` — Creates a socket for a worker
- L114 _public method_ `public static WorkerComputeSocket Open()` — Opens a socket which allows a worker to communicate with the Horde Agent
- L120-129 _public method_ `public static WorkerComputeSocket Open(ILogger logger)` — Opens a socket which allows a worker to communicate with the Horde Agent
- L136-140 _public method_ `public static WorkerComputeSocket Open(string commandBufferName, ILogger logger)` — Opens a socket which allows a worker to communicate with the Horde Agent
- L143-146 _public method_ `public void Dispose()` — (inheritdoc)
- L149-154 _public method_ `public override void AttachRecvBuffer(int channelId, ComputeBuffer buffer)` — (inheritdoc)
- L157-162 _public method_ `public override void AttachSendBuffer(int channelId, ComputeBuffer buffer)` — (inheritdoc)
- L164-172 _private* method_ `void AttachBuffer(IpcMessage message, int channelId, string bufferName)`

#### class `EpicGames.Horde.Compute.WorkerComputeSocketBridge`  
`public sealed class WorkerComputeSocketBridge : IAsyncDisposable`  
_public; L178-308_
- inherits: `IAsyncDisposable`
- desc: Operates a server that a child process can open a WorkerComputeSocket to.
- L180 _private* field_ `readonly SharedMemoryBuffer _ipcBuffer`
- L181 _private* field_ `readonly ComputeBufferReader _ipcBufferReader`
- L182 _private* field_ `readonly BackgroundTask _backgroundTask`
- L183 _private* field_ `readonly ILogger _logger`
- L188 _public property_ `public string BufferName => ...` — Name of the buffer to pass via WorkerComputeSocket.IpcEnvVar
- L193-199 _private ctor_ `private WorkerComputeSocketBridge(SharedMemoryBuffer ipcBuffer, ComputeBufferReader ipcBufferReader, BackgroundTask backgroundTask, ILogger logger)` — Constructor
- L207-229 _public method_ `public static async Task<WorkerComputeSocketBridge> CreateAsync(ComputeSocket socket, ILogger logger)` — Creates a new server for WorkerComputeSocket
- L232-242 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L244-307 _private* method_ `static async Task ProcessIpcMessagesAsync(ComputeSocket socket, ComputeBufferReader ipcReader, ILogger logger, CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Compute.RemoteComputeSocket`  
`public class RemoteComputeSocket : ComputeSocket, IAsyncDisposable`  
_public; L313-888_
- inherits: `ComputeSocket, IAsyncDisposable`
- desc: Manages a set of readers and writers to buffers across a transport layer
- L377 _private* field_ `readonly Lock _lockObject = new()`
- L379 _private* field_ `bool _complete`
- L380 _private* field_ `bool _isClosing`
- L382 _private* field_ `readonly ComputeTransport _transport`
- L383 _private* field_ `readonly ComputeProtocol _protocol`
- L384 _private* field_ `readonly ILogger _logger`
- L386 _private* field_ `BackgroundTask? _recvTask`
- L387 _private* field_ `readonly Dictionary<int, RecvBuffer> _recvBuffers = ...`
- L387 _private* field_ `readonly Dictionary< _recvBuffers = []`
- L389 _private* field_ `readonly SemaphoreSlim _sendSemaphore = new(1, 1)`
- L390 _private* field_ `readonly Dictionary<int, SendBuffer> _sendBuffers = ...`
- L390 _private* field_ `readonly Dictionary< _sendBuffers = []`
- L393 _public property_ `public override ComputeProtocol Protocol => ...` — (inheritdoc)
- L396 _public property_ `public override ILogger Logger => ...` — (inheritdoc)
- L404-411 _public ctor_ `public RemoteComputeSocket(ComputeTransport transport, ComputeProtocol protocol, ILogger logger)` — Constructor
- L416-447 _public method_ `public async ValueTask CloseAsync(CancellationToken cancellationToken)` — Attempt to gracefully close the current connection and shutdown both ends of the transport
- L450-455 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L461-465 _public method_ `public async Task SendKeepAliveMessageAsync(CancellationToken cancellationToken)` — Sends a keep alive message to the remote machine. Does not wait for a response. Designed to keep a connection open when the remote is eagerly trying to close it.
- L467-543 _private* method_ `async Task RunRecvTaskAsync(ComputeTransport transport, CancellationToken cancellationToken)`
- L545-562 _private* method_ `async Task ReadPacketAsync(ComputeTransport transport, int id, int size, CancellationToken cancellationToken)`
- L564-624 _private* method_ `async ValueTask<bool> TryReadPacketAsync(ComputeTransport transport, int id, int size, CancellationToken cancellationToken)`
- L636 _private* field_ `readonly byte[] _header = new byte[8]`
- L637 _private* field_ `readonly SendSegment _headerSegment = new()`
- L638 _private* field_ `readonly SendSegment _bodySegment = new()`
- L641-647 _private* method_ `async ValueTask SendAsync(int id, ReadOnlyMemory<byte> memory, CancellationToken cancellationToken = default)` — (inheritdoc)
- L650 _public method_ `public ValueTask MarkCompleteAsync(int id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L652-669 _private* method_ `async ValueTask SendInternalAsync(int id, int size, ReadOnlyMemory<byte> memory, CancellationToken cancellationToken)`
- L672-694 _public method_ `public override void AttachRecvBuffer(int channelId, ComputeBuffer recvBuffer)` — (inheritdoc)
- L697-734 _private* method_ `async Task DetachRecvBufferAsync(int id, CancellationToken cancellationToken)` — attrs: `[SuppressMessage("Reliability", "CA2000:Dispose objects before losing scope")]`
- L736-763 _private* method_ `async Task DetachAllBuffersAsync(bool recvBuffers, bool sendBuffers, CancellationToken cancellationToken)`
- L766-780 _public method_ `public override void AttachSendBuffer(int channelId, ComputeBuffer sendBuffer)` — (inheritdoc)
- L783-853 _private* method_ `async Task DetachSendBufferAsync(int channelId, CancellationToken cancellationToken)` — attrs: `[SuppressMessage("Reliability", "CA2000:Dispose objects before losing scope")]`
- L855-887 _private* method_ `async Task SendFromBufferAsync(int channelId, SendBuffer sendBuffer, CancellationToken cancellationToken)`

#### enum `EpicGames.Horde.Compute.RemoteComputeSocket.ControlMessageType`  
`enum ControlMessageType`  
_private*; L315-319_
- L317 _public* enumerator_ `Detach = -2`
- L318 _public* enumerator_ `KeepAlive = -3`

#### class `EpicGames.Horde.Compute.RemoteComputeSocket.RecvBuffer`  
`class RecvBuffer : IDisposable`  
_private*; L321-344_
- inherits: `IDisposable`
- L323 _public field_ `public ComputeBufferWriter? _writer`
- L324 _public field_ `public readonly SemaphoreSlim Semaphore = new(1)`
- L325 _public field_ `public int _refCount = 1`
- L327 _public ctor_ `public RecvBuffer(ComputeBufferWriter writer)`
- L329 _public method_ `public void AddRef()`
- L331-337 _public method_ `public void Release()`
- L339-343 _public method_ `public void Dispose()`

#### class `EpicGames.Horde.Compute.RemoteComputeSocket.SendBuffer`  
`class SendBuffer : IDisposable`  
_private*; L346-375_
- inherits: `IDisposable`
- L348 _public field_ `public ComputeBufferReader? _reader`
- L349 _public field_ `public readonly SemaphoreSlim Semaphore = new(1)`
- L351 _public field_ `public readonly BackgroundTask Task` — attrs: `[SuppressMessage("Usage", "CA2213:Disposable fields should be disposed")]`
- L352 _private* field_ `int _refCount = 1`
- L354-358 _public ctor_ `public SendBuffer(ComputeBufferReader reader, Func<SendBuffer, CancellationToken, Task> func)`
- L360 _public method_ `public void AddRef()`
- L362-368 _public method_ `public void Release()`
- L370-374 _public method_ `public void Dispose()`

#### class `EpicGames.Horde.Compute.RemoteComputeSocket.SendSegment`  
`class SendSegment : ReadOnlySequenceSegment<byte>`  
_private*; L626-634_
- inherits: `ReadOnlySequenceSegment<byte>`
- L628-633 _public method_ `public void Set(ReadOnlyMemory<byte> memory, ReadOnlySequenceSegment<byte>? next, long runningIndex)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/ComputeTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ComputeTransport`  
`public abstract class ComputeTransport : IAsyncDisposable`  
_public; L14-91_
- inherits: `IAsyncDisposable`
- desc: Low-level interface for transferring data
- L21 _public method_ `public abstract ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — Writes data to the underlying transport
- L28 _public method_ `public abstract ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — Reads data from the underlying transport into an output buffer
- L34 _public method_ `public abstract ValueTask MarkCompleteAsync(CancellationToken cancellationToken)` — Indicate that all data has been read and written to the transport layer, and that there will be no more calls to send/recv
- L37 _public method_ `public abstract ValueTask DisposeAsync()` — (inheritdoc)
- L44-56 _public method_ `public async ValueTask RecvFullAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — Fill the given buffer with data
- L63-82 _public method_ `public async ValueTask<bool> RecvOptionalAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — Fill the given buffer with data
- L89 _public method_ `public ValueTask SendAsync(ReadOnlyMemory<byte> buffer, CancellationToken cancellationToken)` — Writes data to the underlying transport

### `Source/Programs/Shared/EpicGames.Horde/Compute/ExternalIpResolver.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.ExternalIpResolverException`  
`public class ExternalIpResolverException : Exception`  
_public; L15-26_
- inherits: `Exception`
- desc: Exception for external IP resolver
- L18-20 _public ctor_ `public ExternalIpResolverException(string? message) : base(message)` — (inheritdoc)
- L23-25 _public ctor_ `public ExternalIpResolverException(string? message, Exception? innerException) : base(message, innerException)` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ExternalIpResolver`  
`public class ExternalIpResolver`  
_public; L31-100_
- desc: Find public IP address of local machine by querying a third-party IP lookup service
- L36 _private field_ `private IPAddress? _resolvedIp` — Cache of last resolved IP address. Once resolved, the address is cached for the lifetime of this class.
- L38 _private field_ `private readonly HttpClient _httpClient`
- L39 _private field_ `private readonly List<string> _ipLookupUrls = [ "http://whatismyip.akamai.com", "http://checkip.amazonaws.com", "http://ifconfig.me/ip" ]`
- L48-51 _public ctor_ `public ExternalIpResolver(HttpClient httpClient)` — Constructor
- L59-82 _public method_ `public async Task<IPAddress> GetExternalIpAddressAsync(CancellationToken cancellationToken = default)` — Get the external, public-facing IP of local machine
- L84-99 _private method_ `private async Task<IPAddress> GetExternalIpAddressAsync(Uri url, CancellationToken cancellationToken = default)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/IComputeClient.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Compute.IComputeClient`  
`public interface IComputeClient`  
_public; L14-55_
- desc: Interface for uploading compute work to remote machines
- L24 _public method_ `public Task<ClusterId> GetClusterAsync(Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, ILogger logger, CancellationToken cancellationToken = default)` — Find the most suitable cluster to execute a given compute assignment request
- L36 _public method_ `public Task<IComputeLease?> TryAssignWorkerAsync(ClusterId? clusterId, Requirements? requirements, string? requestId, ConnectionMetadataRequest? connection, bool? useUbaCache, ILogger logger, CancellationToken cancellationToken = default)` — Adds a new remote request
- L47 _public method_ `public Task DeclareResourceNeedsAsync(ClusterId clusterId, string pool, Dictionary<string, int> resourceNeeds, CancellationToken cancellationToken = default)` — Declare resource needs for current client Helps inform the server about current demand. Can be called as often as necessary to keep needs up-to-date.
- L54 _public method_ `public Task<UbaConfig> AllocateUbaCacheServerAsync(ClusterId clusterId, CancellationToken cancellationToken = default)` — Allocate a session for the UBA cache associated with the given cluster

#### class `EpicGames.Horde.Compute.ComputeClientExtensions`  
`public static class ComputeClientExtensions`  
_public; L60-82_
- desc: Extension methods for IComputeClient
- L63-67 _public method_ `public static Task<IComputeLease?> TryAssignWorkerAsync(this IComputeClient computeClient, ClusterId clusterId, Requirements? requirements, string? requestId, ConnectionMode? connectionPreference, ILogger logger, CancellationToken cancellationToken = default)` — (inheritdoc)
- L71-74 _public method_ `public static Task<IComputeLease?> TryAssignWorkerAsync(this IComputeClient computeClient, ClusterId clusterId, Requirements? requirements, ILogger logger, CancellationToken cancellationToken)` — attrs: `[Obsolete("Prefer taking a requestId parameter")]` — (inheritdoc)
- L78-81 _public method_ `public static Task<IComputeLease?> TryAssignWorkerAsync(this IComputeClient computeClient, ClusterId clusterId, Requirements? requirements, string? requestId, ILogger logger, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Prefer taking a connection parameter")]` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ComputeClientException`  
`public class ComputeClientException : Exception`  
_public; L87-93_
- inherits: `Exception`
- desc: Exception from ComputeClient
- L90-92 _public ctor_ `public ComputeClientException(string? message) : base(message)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/IComputeLease.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Compute.IComputeLease`  
`public interface IComputeLease : IAsyncDisposable`  
_public; L13-66_
- inherits: `IAsyncDisposable`
- desc: Full-duplex channel for sending and receiving messages
- L18 _public* property_ `ClusterId Cluster { get; }` — Compute cluster ID
- L23 _public* property_ `IReadOnlyList<string> Properties { get; }` — Properties of the remote machine
- L28 _public* property_ `IReadOnlyDictionary<string, int> AssignedResources { get; }` — Resources assigned to this lease
- L33 _public* property_ `RemoteComputeSocket Socket { get; }` — Socket to communicate with the remote
- L39 _public property_ `public string Ip { get; }` — IP address of the remote agent machine running the compute task When using relay connection mode, this may be the IP of the relay rather than the remote machine itself.
- L42 _public property_ `public UbaConfig? Uba { get; }` — (inheritdoc)
- L47 _public property_ `public ConnectionMode ConnectionMode { get; }` — How to establish a connection to the remote machine (when not using the default socket)
- L59 _public* property_ `IReadOnlyDictionary<string, ConnectionMetadataPort> Ports { get; }` — Assigned ports (externally visible port -> local port on agent) Key is an arbitrary name identifying the port (same as was given when requesting the lease>) When relay mode is used, ports can mapped to a different externally visible port. If compute task uses and listens to port 7000, that port can be externally represented as something else. For example, port 32743 can be pointed to port 7000. This makes no difference for the compute task process, but the client/initiator making connections must pay attention to this mapping.
- L65 _public* method_ `ValueTask CloseAsync(CancellationToken cancellationToken = default)` — Relinquish the lease gracefully

### `Source/Programs/Shared/EpicGames.Horde/Compute/Native.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Native`  
`internal class Native`  
_internal; L12-88_
- L25 _public method_ `public static extern SafeWaitHandle CreateEvent(SECURITY_ATTRIBUTES lpEventAttributes, bool bManualReset, bool bInitialState, string? lpName)` — attrs: `[DllImport("kernel32.dll")]`
- L28 _public method_ `public static extern SafeWaitHandle OpenEvent(uint dwDesiredAccess, bool bInheritHandle, string lpName)` — attrs: `[DllImport("Kernel32.dll", SetLastError = true)]`
- L31 _public method_ `public static extern bool ResetEvent(SafeWaitHandle hEvent)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L34 _public method_ `public static extern bool SetEvent(SafeWaitHandle hEvent)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L36 _public const_ `public const uint DUPLICATE_SAME_ACCESS = 2`
- L38 _public const_ `public const uint SYNCHRONIZE = 0x00100000`
- L39 _public const_ `public const uint EVENT_MODIFY_STATE = 2`
- L42 _public method_ `public static extern IntPtr GetCurrentProcess()` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L46 _public method_ `public static extern bool DuplicateHandle(IntPtr hSourceProcessHandle, IntPtr hSourceHandle, IntPtr hTargetProcessHandle, out IntPtr lpTargetHandle, uint dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, uint dwOptions)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)] [return: MarshalAs(UnmanagedType.Bool)]`

#### class `EpicGames.Horde.Compute.Native.SECURITY_ATTRIBUTES`  
`public class SECURITY_ATTRIBUTES`  
_public; L16-21_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L18 _public field_ `public int nLength`
- L19 _public field_ `public IntPtr lpSecurityDescriptor`
- L20 _public field_ `public int bInheritHandle`

#### class `EpicGames.Horde.Compute.Native.EventHandle`  
`public class EventHandle : WaitHandle`  
_public; L48-87_
- inherits: `WaitHandle`
- L50-53 _public ctor_ `public EventHandle(SafeWaitHandle handle)`
- L55-67 _public method_ `public static EventHandle CreateNew(string? name, EventResetMode resetMode, bool initialState, HandleInheritability handleInheritability)`
- L69-72 _public ctor_ `public EventHandle(IntPtr handle, bool ownsHandle)`
- L74-82 _public method_ `public static EventHandle OpenExisting(string name)`
- L84 _public method_ `public void Set()`
- L86 _public method_ `public void Reset()`

### `Source/Programs/Shared/EpicGames.Horde/Compute/RequestIdAllocator.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.RequestIdAllocator`  
`public class RequestIdAllocator`  
_public; L13-89_
- desc: Manages and hands out request IDs for compute allocation requests
- L15 _private field_ `private readonly Lock _lock = new()`
- L16 _private field_ `private readonly List<string> _pendingIds = []`
- L17 _private field_ `private readonly List<string> _batchIds = []`
- L18 _private field_ `private readonly string _allocatorId`
- L19 _private field_ `private int _requestCounter`
- L24-27 _public ctor_ `public RequestIdAllocator()` — Constructor
- L33-40 _public method_ `public void StartBatch()` — Starts a new batch of requests. Any requests started during current batch will be reset and marked as unfinished.
- L46-64 _public method_ `public string AllocateId()` — Get or create a request ID and mark it as part of current batch
- L70-76 _public method_ `public void MarkAccepted(string reqId)` — Mark a request Id as accepted. It won't be re-used for any future requests.
- L78-88 _private method_ `private static string GenerateAllocatorId(int length)`

### `Source/Programs/Shared/EpicGames.Horde/Compute/Requirements.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Requirements`  
`public class Requirements`  
_public; L14-79_
- desc: Requirements for a compute task to be assigned an agent
- L19 _public property_ `public string? Pool { get; set; }` — Pool of machines to draw from
- L24 _public property_ `public Condition? Condition { get; set; }` — Condition string to be evaluated against the machine spec, eg. cpu-cores >= 10 && ram.mb >= 200 && pool == 'worker'
- L29 _public property_ `public HashSet<string> Properties { get; set; }` — Properties required from the remote machine
- L34 _public property_ `public Dictionary<string, ResourceRequirements> Resources { get; }` — Resources used by the process
- L39 _public property_ `public bool Exclusive { get; set; }` — Whether we require exclusive access to the device
- L44-46 _public ctor_ `public Requirements()` — Default constructor
- L52-55 _public ctor_ `public Requirements(Condition? condition)` — Construct a requirements object with a condition
- L58-78 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Compute.ResourceRequirements`  
`public class ResourceRequirements`  
_public; L84-95_
- desc: Specifies requirements for resource allocation
- L89 _public property_ `public int Min { get; set; }` — Minimum allocation of the requested resource
- L94 _public property_ `public int? Max { get; set; }` — Maximum allocation of the requested resource. Allocates as much as possible unless capped.

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/AesTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.AesTransport`  
`public sealed class AesTransport : ComputeTransport`  
_public; L16-189_
- inherits: `ComputeTransport`
- desc: Transport layer that adds AES encryption on top of an underlying transport implementation. Key must be exchanged separately (e.g. via the HTTPS request to negotiate a lease with the server).
- L21 _public const_ `public const int KeyLength = 32` — Length of the required encryption key.
- L26 _public const_ `public const int NonceLength = 12` — Length of the nonce. This should be a cryptographically random number, and does not have to be secret.
- L28 _private const_ `private const int TagSize = 16`
- L29 _private const_ `private const int BufferLength = sizeof(int)`
- L30 _private const_ `private const int HeaderLength = BufferLength + NonceLength`
- L31 _private field_ `private readonly ComputeTransport _inner`
- L32 _private field_ `private readonly bool _leaveInnerOpen`
- L33 _private field_ `private readonly AesGcm _aes`
- L34 _private field_ `private readonly SemaphoreSlim _sendSemaphore = new(1, 1)`
- L35 _private field_ `private readonly SemaphoreSlim _recvSemaphore = new(1, 1)`
- L36 _private field_ `private readonly MemoryStream _remainingData`
- L37 _private field_ `private bool _disposed`
- L46-58 _public ctor_ `public AesTransport(ComputeTransport inner, ReadOnlySpan<byte> key, bool leaveInnerOpen = false, int readBufferSize = 256 * 1024)` — Constructor
- L64 _public method_ `public static byte[] CreateKey()` — Create a random key for this transport
- L67-95 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L98-165 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L168-171 _public method_ `public override ValueTask MarkCompleteAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L174-188 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/IdleTimeoutTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.IdleTimeoutTransport`  
`public class IdleTimeoutTransport : ComputeTransport`  
_public; L16-95_
- inherits: `ComputeTransport`
- desc: Compute transport which wraps another transport acting as a watchdog timer for inactivity If no send or receive activity has been seen within specified timeout, the cancellation source will be triggered
- L21 _public property_ `public TimeSpan NoDataTimeout { get; }` — Timeout before triggering a cancellation
- L23 _private field_ `private static readonly double s_ticksToSystemTicks = (double)TimeSpan.TicksPerSecond / Stopwatch.Frequency`
- L24 _private field_ `private readonly ComputeTransport _inner`
- L25 _private field_ `private long _lastPingTicks`
- L32-37 _public ctor_ `public IdleTimeoutTransport(ComputeTransport inner, TimeSpan? noDataTimeout = null)` — Constructor
- L40-44 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L49 _public property_ `public TimeSpan TimeSinceActivity => ...` — Time since last send or receive completed
- L52-60 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L63-67 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L70-73 _public method_ `public override ValueTask MarkCompleteAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L81-94 _public method_ `public async Task StartWatchdogTimerAsync(CancellationTokenSource cts, ILogger logger, CancellationToken cancellationToken)` — Start a loop monitoring activity on the inner transport

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/PipeTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.PipeTransport`  
`public class PipeTransport : ComputeTransport`  
_public; L15-102_
- inherits: `ComputeTransport`
- desc: Implementation of ComputeTransport for communicating over a Pipe. (Note: this uses a .NET in-process pipe, not an IPC pipe).
- L17 _private* field_ `readonly PipeReader _reader`
- L18 _private* field_ `readonly PipeWriter _writer`
- L20 _private* field_ `ReadOnlySequence<byte> _readBuffer = ReadOnlySequence<byte>.Empty`
- L21 _private* field_ `SequencePosition? _readEnd`
- L24 _public property_ `public long Position { get; set; }` — (inheritdoc)
- L31-35 _public ctor_ `public PipeTransport(PipeReader reader, PipeWriter writer)` — Constructor
- L38-42 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L45-85 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L88-95 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L98-101 _public method_ `public override async ValueTask MarkCompleteAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/StreamTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.StreamTransport`  
`class StreamTransport : ComputeTransport`  
_internal*; L14-61_
- inherits: `ComputeTransport`
- desc: Compute transport which wraps an underlying stream
- L16 _private* field_ `readonly Stream _stream`
- L17 _private* field_ `readonly bool _leaveOpen`
- L18 _public property_ `public long Position { get; set; }`
- L25-29 _public ctor_ `public StreamTransport(Stream stream, bool leaveOpen = false)` — Constructor
- L32-39 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L42-47 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L50-57 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L60 _public method_ `public override ValueTask MarkCompleteAsync(CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/TcpSslTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.TcpSslTransport`  
`public sealed class TcpSslTransport : ComputeTransport`  
_public; L17-166_
- inherits: `ComputeTransport`
- desc: Implementation of ComputeTransport for communicating over a socket using SSL/TLS
- L19 _private field_ `private readonly Socket _socket`
- L20 _private field_ `private readonly X509Certificate2 _cert`
- L21 _private field_ `private readonly bool _isServer`
- L22 _private field_ `private readonly NetworkStream _networkStream`
- L23 _private field_ `private readonly SslStream _sslStream`
- L31-33 _public ctor_ `public TcpSslTransport(Socket socket, byte[] certData, bool isServer) : this(socket, X509CertificateLoader.LoadPkcs12(certData, null), isServer)` — Constructor
- L41-48 _public ctor_ `public TcpSslTransport(Socket socket, X509Certificate2 cert, bool isServer)` — Constructor
- L51-56 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L61-71 _public method_ `public async Task AuthenticateAsync(CancellationToken cancellationToken)` — Perform SSL authentication
- L73-85 _private method_ `private async Task AuthenticateAsClientAsync()`
- L87-98 _private method_ `private async Task AuthenticateAsServerAsync(CancellationToken cancellationToken)`
- L108-111 _private method_ `private bool ValidateCert(object sender, X509Certificate? certificate, X509Chain? chain, SslPolicyErrors sslPolicyErrors)` — Checks the certificate returned by the server is indeed the correct one
- L114-117 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L120-127 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L130-134 _public method_ `public override ValueTask MarkCompleteAsync(CancellationToken cancelationToken)` — (inheritdoc)
- L140-165 _public method_ `public static byte[] GenerateCert(Encryption encryption)` — Generate a self-signed certificate to be used for communicating between client and server of this transport

### `Source/Programs/Shared/EpicGames.Horde/Compute/Transports/TcpTransport.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.Transports.TcpTransport`  
`public sealed class TcpTransport : ComputeTransport`  
_public; L15-68_
- inherits: `ComputeTransport`
- desc: Implementation of ComputeTransport for communicating over a socket
- L17 _private* field_ `readonly Socket _socket`
- L20 _public property_ `public long Position { get; set; }` — (inheritdoc)
- L26 _public ctor_ `public TcpTransport(Socket socket)` — Constructor
- L29-32 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L35-48 _public method_ `public override async ValueTask<int> RecvAsync(Memory<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L51-60 _public method_ `public override async ValueTask SendAsync(ReadOnlySequence<byte> buffer, CancellationToken cancellationToken)` — (inheritdoc)
- L63-67 _public method_ `public override ValueTask MarkCompleteAsync(CancellationToken cancelationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Compute/UbaCrypto.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Compute.UbaCrypto`  
`public class UbaCrypto : IDisposable`  
_public; L14-145_
- inherits: `IDisposable`
- desc: Provides AES encryption and decryption functionality compatible with Unreal Build Accelerator (UBA) communication protocol. Uses AES-128 in CBC mode with zero IV and no padding. Thread-safe through thread-local AES instances.
- L16 _private const_ `private const int AesBlockSize = 16`
- L17 _private field_ `private static readonly byte[] s_fixedIvLe = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]`
- L19 _private field_ `private readonly ThreadLocal<Aes> _aes`
- L20 _private field_ `private bool _disposed`
- L27-42 _public ctor_ `public UbaCrypto(byte[] key)` — Constructor
- L52 _public method_ `public byte[] Encrypt(byte[] data)` — Encrypts the specified data
- L62 _public method_ `public byte[] Decrypt(byte[] data)` — Decrypts the specified data.
- L71-122 _private method_ `private byte[] Transform(byte[] src, bool encrypt)` — attrs: `[SuppressMessage("Security", "CA5401:Do not use CreateEncryptor with non-default IV")]` — Decrypt/encrypt method ported from C++ UBA
- L125-129 _public method_ `public void Dispose()` — (inheritdoc)
- L134-144 _protected method_ `protected virtual void Dispose(bool disposing)` — Dispose

### `Source/Programs/Shared/EpicGames.Horde/Dashboard/DashboardMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Dashboard.GetDashboardConfigResponse`  
`public class GetDashboardConfigResponse`  
_public; L16-87_
- desc: Setting information required by dashboard
- L21 _public property_ `public string? ExternalIssueServiceName { get; set; }` — The name of the external issue service
- L26 _public property_ `public string? ExternalIssueServiceUrl { get; set; }` — The url of the external issue service
- L31 _public property_ `public string? PerforceSwarmUrl { get; set; }` — The url of the perforce swarm installation
- L36 _public property_ `public string? RobomergeUrl { get; set; }` — Url of Robomergem installation
- L41 _public property_ `public string? CommitsViewerUrl { get; set; }` — Url of Commits Viewer
- L46 _public property_ `public string? HelpEmailAddress { get; set; }` — Help email address that users can contact with issues
- L51 _public property_ `public string? HelpSlackChannel { get; set; }` — Help slack channel that users can use for issues
- L56 _public property_ `public AuthMethod AuthMethod { get; set; }` — The auth method in use
- L61 _public property_ `public int DeviceProblemCooldownMinutes { get; set; }` — Device problem cooldown in minutes
- L66 _public property_ `public List<GetDashboardAgentCategoryResponse> AgentCategories { get; set; }` — Categories to display on the agents page
- L71 _public property_ `public List<GetDashboardPoolCategoryResponse> PoolCategories { get; set; }` — Categories to display on the pools page
- L76 _public property_ `public List<string> ArtifactTypes { get; set; }` — Configured artifact types
- L81 _public property_ `public List<GetDashboardArtifactTypeResponse> ArtifactTypeInfo { get; set; }` — Configured artifact type info
- L86 _public property_ `public int? ConfigVersion { get; set; }` — The server's global config version number. Maps to the ConfigVersion enum on the server.

#### class `EpicGames.Horde.Dashboard.GetDashboardArtifactTypeResponse`  
`public class GetDashboardArtifactTypeResponse`  
_public; L92-103_
- desc: Describes an artifact type
- L97 _public property_ `public string Type { get; set; }` — Type of the artifact
- L102 _public property_ `public int? KeepDays { get; set; }` — Number of days to retain artifacts of this type

#### class `EpicGames.Horde.Dashboard.GetDashboardPoolCategoryResponse`  
`public class GetDashboardPoolCategoryResponse`  
_public; L108-119_
- desc: Describes a category for the pools page
- L113 _public property_ `public string Name { get; set; }` — Title for the tab
- L118 _public property_ `public Condition? Condition { get; set; }` — Condition for pools to be included in this category

#### class `EpicGames.Horde.Dashboard.GetDashboardAgentCategoryResponse`  
`public class GetDashboardAgentCategoryResponse`  
_public; L124-135_
- desc: Describes a category for the agents page
- L129 _public property_ `public string Name { get; set; }` — Title for the tab
- L134 _public property_ `public Condition? Condition { get; set; }` — Condition for agents to be included in this category

#### class `EpicGames.Horde.Dashboard.CreateDashboardPreviewRequest`  
`public class CreateDashboardPreviewRequest`  
_public; L140-166_
- L145 _public property_ `public string Summary { get; set; }` — A summary of what the preview item changes
- L150 _public property_ `public int? DeployedCL { get; set; }` — The CL the preview was deployed in
- L155 _public property_ `public string? ExampleLink { get; set; }` — An example of the preview site users can view the changes
- L160 _public property_ `public string? DiscussionLink { get; set; }` — Optional Link for discussion the preview item
- L165 _public property_ `public string? TrackingLink { get; set; }` — Optional Link for discussing the preview item

#### class `EpicGames.Horde.Dashboard.UpdateDashboardPreviewRequest`  
`public class UpdateDashboardPreviewRequest`  
_public; L171-207_
- L176 _public property_ `public int Id { get; set; }` — The preview item to update
- L181 _public property_ `public string? Summary { get; set; }` — A summary of what the preview item changes
- L186 _public property_ `public int? DeployedCL { get; set; }` — The CL the preview was deployed in
- L191 _public property_ `public bool? Open { get; set; }` — Whather the preview is under consideration, if false the preview item didn't pass muster
- L196 _public property_ `public string? ExampleLink { get; set; }` — An example of the preview site users can view the changes
- L201 _public property_ `public string? DiscussionLink { get; set; }` — Optional Link for discussion the preview item
- L206 _public property_ `public string? TrackingLink { get; set; }` — Optional Link for discussing the preview item

#### class `EpicGames.Horde.Dashboard.GetDashboardPreviewResponse`  
`public class GetDashboardPreviewResponse`  
_public; L212-253_
- desc: Dashboard preview item response
- L217 _public property_ `public int Id { get; set; }` — The unique ID of the preview item
- L222 _public property_ `public DateTime CreatedAt { get; set; }` — When the preview item was created
- L227 _public property_ `public string Summary { get; set; }` — A summary of what the preview item changes
- L232 _public property_ `public int? DeployedCL { get; set; }` — The CL the preview was deployed in
- L237 _public property_ `public bool Open { get; set; }` — Whather the preview is under consideration, if false the preview item didn't pass muster
- L242 _public property_ `public string? ExampleLink { get; set; }` — An example of the preview site users can view the changes
- L247 _public property_ `public string? DiscussionLink { get; set; }` — Optional Link for discussion the preview item
- L252 _public property_ `public string? TrackingLink { get; set; }` — Optional Link for discussing the preview item

#### class `EpicGames.Horde.Dashboard.GetDashboardChallengeResponse`  
`public class GetDashboardChallengeResponse`  
_public; L258-270_
- desc: Dashboard challenge response
- L263 _public property_ `public bool NeedsFirstTimeSetup { get; set; }` — Whether first time setup needs to run
- L268 _public property_ `public bool NeedsAuthorization { get; set; }` — Whether the user needs to authorize

### `Source/Programs/Shared/EpicGames.Horde/Devices/DeviceId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Devices.DeviceId`  
`public readonly record struct DeviceId(StringId Id)`  
_public; L18-35_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<DeviceId, DeviceIdConverter>))] [StringIdConverter(typeof(DeviceIdConverter))] [CbConverter(typeof(StringIdCbConverter<DeviceId, DeviceIdConverter>))]`
- desc: Identifier for a pool
- L23-25 _public ctor_ `public DeviceId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public static DeviceId Sanitize(string text)` — (inheritdoc)
- L34 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Devices.DeviceIdConverter`  
`class DeviceIdConverter : StringIdConverter<DeviceId>`  
_internal*; L40-47_
- inherits: `StringIdConverter<DeviceId>`
- desc: Converter to and from StringId instances.
- L43 _public method_ `public override DeviceId FromStringId(StringId id)` — (inheritdoc)
- L46 _public method_ `public override StringId ToStringId(DeviceId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Devices/DeviceMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Devices.DevicePoolType`  
`public enum DevicePoolType`  
_public; L15-26_
- desc: The type of device pool
- L20 _public* enumerator_ `Automation` — Available to CIS jobs
- L25 _public* enumerator_ `Shared` — Shared by users with remote checking and checkouts

#### class `EpicGames.Horde.Devices.CreateDevicePlatformRequest`  
`public class CreateDevicePlatformRequest`  
_public; L31-39_
- desc: Create device platform request
- L37 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the platform

#### class `EpicGames.Horde.Devices.CreateDevicePlatformResponse`  
`public class CreateDevicePlatformResponse`  
_public; L44-58_
- desc: Create device platform response object
- L49 _public property_ `public string Id { get; set; }` — Id of newly created platform
- L54-57 _public ctor_ `public CreateDevicePlatformResponse(string id)` — Constructor

#### class `EpicGames.Horde.Devices.UpdateDevicePlatformRequest`  
`public class UpdateDevicePlatformRequest`  
_public; L63-69_
- desc: Update requesty object for a device platform
- L68 _public property_ `public string[] ModelIds { get; set; }` — The vendor model ids for the platform

#### class `EpicGames.Horde.Devices.GetDevicePlatformResponse`  
`public class GetDevicePlatformResponse`  
_public; L74-100_
- desc: Get object response which describes a device platform
- L79 _public property_ `public string Id { get; set; }` — Unique id of device platform
- L84 _public property_ `public string Name { get; set; }` — Friendly name of device platform
- L89 _public property_ `public string[] ModelIds { get; set; }` — Platform vendor models
- L94-99 _public ctor_ `public GetDevicePlatformResponse(string id, string name, string[] modelIds)` — Response constructor

#### class `EpicGames.Horde.Devices.CreateDevicePoolRequest`  
`public class CreateDevicePoolRequest`  
_public; L105-123_
- desc: Device pool creation request object
- L111 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name for the new pool
- L117 _public property_ `public DevicePoolType PoolType { get; set; }` — attrs: `[Required]` — The name for the new pool
- L122 _public property_ `public List<string>? ProjectIds { get; set; }` — Projects associated with this device pool

#### class `EpicGames.Horde.Devices.UpdateDevicePoolRequest`  
`public class UpdateDevicePoolRequest`  
_public; L128-139_
- desc: Device pool update request object
- L133 _public property_ `public string Id { get; set; }` — Id of the device pool to update
- L138 _public property_ `public List<string>? ProjectIds { get; set; }` — Projects associated with this device pool

#### class `EpicGames.Horde.Devices.CreateDevicePoolResponse`  
`public class CreateDevicePoolResponse`  
_public; L144-158_
- desc: Device pool creation response object
- L149 _public property_ `public string Id { get; set; }` — Id of the newly created device pool
- L154-157 _public ctor_ `public CreateDevicePoolResponse(string id)` — Constructor

#### class `EpicGames.Horde.Devices.GetDevicePoolResponse`  
`public class GetDevicePoolResponse`  
_public; L163-195_
- desc: Device pool response object
- L168 _public property_ `public string Id { get; set; }` — Id of the device pool
- L173 _public property_ `public string Name { get; set; }` — Name of the device pool
- L178 _public property_ `public DevicePoolType PoolType { get; set; }` — Type of the device pool
- L183 _public property_ `public bool WriteAccess { get; set; }` — Whether there is write access to the pool
- L188-194 _public ctor_ `public GetDevicePoolResponse(string id, string name, DevicePoolType poolType, bool writeAccess)` — Constructor

#### class `EpicGames.Horde.Devices.CreateDeviceRequest`  
`public class CreateDeviceRequest`  
_public; L202-241_
- desc: Device creation request object
- L208 _public property_ `public string PlatformId { get; set; }` — attrs: `[Required]` — The platform of the device
- L214 _public property_ `public string PoolId { get; set; }` — attrs: `[Required]` — The pool to assign the device
- L220 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The friendly name of the device
- L225 _public property_ `public bool? Enabled { get; set; }` — Whether to create the device in enabled state
- L230 _public property_ `public string? Address { get; set; }` — The network address of the device
- L235 _public property_ `public string? ModelId { get; set; }` — The vendor model id of the device
- L240 _public property_ `public List<string>? Tags { get; set; }` — Any tags associated with the device

#### class `EpicGames.Horde.Devices.CreateDeviceResponse`  
`public class CreateDeviceResponse`  
_public; L246-262_
- desc: Device creation response object
- L252 _public property_ `public string Id { get; set; }` — attrs: `[Required]` — The id of the newly created device
- L258-261 _public ctor_ `public CreateDeviceResponse(string id)` — Constructor

#### class `EpicGames.Horde.Devices.GetDeviceUtilizationResponse`  
`public class GetDeviceUtilizationResponse`  
_public; L267-288_
- desc: Get response object which describes a device (DEPRECATED)
- L272 _public property_ `public string? JobId { get; set; }` — The job id which utilized device
- L277 _public property_ `public string? StepId { get; set; }` — The job's step id
- L282 _public property_ `public DateTime ReservationStartUtc { get; set; }` — The time device was reserved
- L287 _public property_ `public DateTime? ReservationFinishUtc { get; set; }` — The time device was freed

#### class `EpicGames.Horde.Devices.GetDeviceResponse`  
`public class GetDeviceResponse`  
_public; L293-415_
- desc: Get response object which describes a device
- L298 _public property_ `public string Id { get; set; }` — The unique id of the device
- L303 _public property_ `public string PlatformId { get; set; }` — The platform of the device
- L308 _public property_ `public string PoolId { get; set; }` — The pool the device belongs to
- L313 _public property_ `public string Name { get; set; }` — The friendly name of the device
- L318 _public property_ `public bool Enabled { get; set; }` — Whether the device is currently enabled
- L323 _public property_ `public string? Address { get; set; }` — The address of the device (if it allows network connections)
- L328 _public property_ `public string? ModelId { get; set; }` — The vendor model id of the device
- L333 _public property_ `public string? Notes { get; set; }` — Any notes provided for the device
- L338 _public property_ `public List<string>? Tags { get; set; }` — Metadata tags on the device
- L343 _public property_ `public DateTime? ProblemTime { get; set; }` — If the device has a marked problem
- L348 _public property_ `public DateTime? MaintenanceTime { get; set; }` — If the device is in maintenance mode
- L353 _public property_ `public string? CheckedOutByUserId { get; set; }` — The user id that has the device checked out
- L358 _public property_ `public DateTime? CheckOutTime { get; set; }` — The last time the device was checked out
- L363 _public property_ `public DateTime? CheckOutExpirationTime { get; set; }` — When the checkout will expire
- L368 _public property_ `public string? ModifiedByUser { get; set; }` — The last user to modifiy the device
- L373 _public property_ `public DateTime? CleanStartTime { get; set; }` — When the clean pass started
- L378 _public property_ `public DateTime? CleanFinishTime { get; set; }` — When the clean pass finished
- L383 _public property_ `public bool? CleanRequired { get; set; }` — Whether the device requires a cleaning
- L388 _public property_ `public List<GetDeviceUtilizationResponse>? Utilization { get; set; }` — Device Utilization data
- L393-414 _public ctor_ `public GetDeviceResponse(string id, string platformId, string poolId, string name, bool enabled, string? address, string? modelId, string? modifiedByUser, string? notes, DateTime? problemTime, DateTime? maintenanceTime, List<GetDeviceUtilizationResponse>? utilization, string? checkedOutByUserId = null, DateTime? checkOutTime = null, DateTime? checkOutExpirationTime = null, bool? cleanRequired = null, DateTime? cleanStartTime = null, DateTime? cleanFinishTime = null, List<string>? tags = null)` — Device response constructor

#### class `EpicGames.Horde.Devices.UpdateDeviceRequest`  
`public class UpdateDeviceRequest`  
_public; L420-471_
- desc: Device update request object
- L425 _public property_ `public string? PoolId { get; set; }` — The device pool id
- L430 _public property_ `public string? Name { get; set; }` — The device name
- L435 _public property_ `public string? Address { get; set; }` — IP address or hostname of device
- L440 _public property_ `public string? ModelId { get; set; }` — Device vendor model id
- L445 _public property_ `public string? Notes { get; set; }` — Markdown notes
- L450 _public property_ `public bool? Enabled { get; set; }` — Whether device is enabled
- L455 _public property_ `public bool? Maintenance { get; set; }` — Whether the device is in maintenance mode
- L460 _public property_ `public bool? Problem { get; set; }` — Whether to set or clear any device problem state
- L465 _public property_ `public string? Message { get; set; }` — Additional message to attach to this request
- L470 _public property_ `public List<string>? Tags { get; set; }` — Tags on the device

#### class `EpicGames.Horde.Devices.DeviceErrorRequest`  
`public class DeviceErrorRequest`  
_public; L476-482_
- desc: Device error report request object
- L481 _public property_ `public string? Message { get; set; }` — Additional message to attach to this request

#### class `EpicGames.Horde.Devices.CheckoutDeviceRequest`  
`public class CheckoutDeviceRequest`  
_public; L487-493_
- desc: Device checkout request object
- L492 _public property_ `public bool Checkout { get; set; }` — Whether to checkout or in the device

#### class `EpicGames.Horde.Devices.CleanDeviceRequest`  
`public class CleanDeviceRequest`  
_public; L498-504_
- desc: Device clean request object
- L503 _public property_ `public bool Clean { get; set; }` — Whether to set the device as being cleaned, or not

#### class `EpicGames.Horde.Devices.DeviceTagsRequest`  
`public class DeviceTagsRequest`  
_public; L509-557_
- desc: Device tags request object
- L514 _public property_ `public List<string>? RequiredTags { get; set; }` — Only devices with these tags will be considered for reservation
- L519 _public property_ `public List<string>? PreferredTags { get; set; }` — Devices with these tags will be preferred over devices without them, but are not explicitly required
- L524 _public property_ `public List<string>? UndesiredTags { get; set; }` — Devices with these tags will be considered, but only as a last resort
- L529 _public property_ `public List<string>? BlockedTags { get; set; }` — Devices with these tags will not be considered for reservation
- L534-556 _public method_ `public HashSet<string> GetDuplicateEntries()` — Returns any duplicate tag entries

#### class `EpicGames.Horde.Devices.DeviceReservationRequest`  
`public class DeviceReservationRequest`  
_public; L562-584_
- desc: Device reservation request object
- L568 _public property_ `public string PlatformId { get; set; }` — attrs: `[Required]` — Device reservation platform id
- L573 _public property_ `public List<string>? IncludeModels { get; set; }` — The optional vendor model ids to include for this device
- L578 _public property_ `public List<string>? ExcludeModels { get; set; }` — The optional vendor model ids to exclude for this device
- L583 _public property_ `public DeviceTagsRequest? Tags { get; set; }` — Desired device tags for this device

#### class `EpicGames.Horde.Devices.CreateDeviceReservationRequest`  
`public class CreateDeviceReservationRequest`  
_public; L589-602_
- desc: Reservation request object
- L595 _public property_ `public string PoolId { get; set; }` — attrs: `[Required]` — What pool to reserve devices in
- L601 _public property_ `public List<DeviceReservationRequest> Devices { get; set; }` — attrs: `[Required]` — Devices to reserve

#### class `EpicGames.Horde.Devices.CreateDeviceReservationResponse`  
`public class CreateDeviceReservationResponse`  
_public; L607-618_
- desc: Device reservation response object
- L612 _public property_ `public string Id { get; set; }` — The reservation id of newly created reservation
- L617 _public property_ `public List<GetDeviceResponse> Devices { get; set; }` — The devices that were reserved

#### class `EpicGames.Horde.Devices.GetDeviceReservationResponse`  
`public class GetDeviceReservationResponse`  
_public; L623-687_
- desc: A reservation containing one or more devices
- L629 _public property_ `public string Id { get; set; }` — attrs: `[Required]` — Randomly generated unique id for this reservation
- L635 _public property_ `public string PoolId { get; set; }` — attrs: `[Required]` — Which device pool the reservation is in
- L641 _public property_ `public List<string> Devices { get; set; }` — attrs: `[Required]` — The reserved devices
- L646 _public property_ `public string? JobId { get; set; }` — JobID holding reservation
- L651 _public property_ `public string? StepId { get; set; }` — Job step id holding reservation
- L656 _public property_ `public string? JobName { get; set; }` — Job mame holding reservation
- L661 _public property_ `public string? StepName { get; set; }` — Job step holding reservation
- L666 _public property_ `public string? UserId { get; set; }` — Reservations held by a user, requires a token
- L671 _public property_ `public string? Hostname { get; set; }` — The hostname of machine holding reservation
- L676 _public property_ `public string? ReservationDetails { get; set; }` — The optional reservation details
- L681 _public property_ `public DateTime CreateTimeUtc { get; set; }` — The UTC time when the reservation was created
- L686 _public property_ `public string LegacyGuid { get; set; }` — The legacy reservation system guid, to be removed once can update Gauntlet client in all streams

#### class `EpicGames.Horde.Devices.GetTelemetryInfoResponse`  
`public class GetTelemetryInfoResponse`  
_public; L692-739_
- desc: Device telemetry respponse
- L698 _public property_ `public DateTime CreateTimeUtc { get; set; }` — attrs: `[Required]` — The UTC time the telemetry data was created
- L703 _public property_ `public string? StreamId { get; set; }` — The stream id which utilized device
- L708 _public property_ `public string? JobId { get; set; }` — The job id which utilized device
- L713 _public property_ `public string? JobName { get; set; }` — The job name which utilized device
- L718 _public property_ `public string? StepId { get; set; }` — The job's step id
- L723 _public property_ `public string? StepName { get; set; }` — The job name which utilized device
- L728 _public property_ `public DateTime? ReservationStartUtc { get; set; }` — If this telemetry has a reservation, the start time of the reservation
- L733 _public property_ `public DateTime? ReservationFinishUtc { get; set; }` — If this telemetry has a reservation, the finish time of the reservation
- L738 _public property_ `public DateTime? ProblemTimeUtc { get; set; }` — If this telemetry marks a detected device issue, the time of the issue

#### class `EpicGames.Horde.Devices.GetDeviceTelemetryResponse`  
`public class GetDeviceTelemetryResponse`  
_public; L744-768_
- desc: Device telemetry respponse
- L750 _public property_ `public string DeviceId { get; set; }` — attrs: `[Required]` — The device id for the telemetry data
- L756 _public property_ `public List<GetTelemetryInfoResponse> Telemetry { get; set; }` — attrs: `[Required]` — Individual telemetry data points
- L763-767 _public ctor_ `public GetDeviceTelemetryResponse(string deviceId, List<GetTelemetryInfoResponse> telemetry)` — Constructor

#### class `EpicGames.Horde.Devices.GetDevicePoolReservationTelemetryResponse`  
`public class GetDevicePoolReservationTelemetryResponse`  
_public; L773-816_
- desc: Stream device telemetry for pool snapshot
- L778 _public property_ `public string DeviceId { get; set; }` — Device id for reservation
- L783 _public property_ `public string? JobId { get; set; }` — Job id associated with reservation
- L788 _public property_ `public string? StepId { get; set; }` — The step id of reservation
- L793 _public property_ `public string? JobName { get; set; }` — The name of the job holding reservation
- L798 _public property_ `public string? StepName { get; set; }` — The name of the step holding reservation
- L808-815 _public ctor_ `public GetDevicePoolReservationTelemetryResponse(string deviceId, string? jobId, string? stepId, string? jobName, string? stepName)` — constructor

#### class `EpicGames.Horde.Devices.GetDevicePlatformTelemetryResponse`  
`public class GetDevicePlatformTelemetryResponse`  
_public; L821-881_
- desc: Device telemetry respponse
- L826 _public property_ `public string PlatformId { get; set; }` — The corresponding platform id
- L831 _public property_ `public List<string>? Available { get; set; }` — Available devices of this platform
- L836 _public property_ `public List<string>? Maintenance { get; set; }` — Devices in maintenance state
- L841 _public property_ `public List<string>? Problem { get; set; }` — Devices in problem state
- L846 _public property_ `public List<string>? Disabled { get; set; }` — Number of devices in disabled state
- L851 _public property_ `public Dictionary<string, List<GetDevicePoolReservationTelemetryResponse>>? Reserved { get; set; }` — Reserved devices
- L856-880 _public ctor_ `public GetDevicePlatformTelemetryResponse(string platformId, List<string>? available, List<string>? maintenance, List<string>? problem, List<string>? disabled, Dictionary<string, List<GetDevicePoolReservationTelemetryResponse>>? reserved)` — Constructor

#### class `EpicGames.Horde.Devices.GetDevicePoolTelemetryResponse`  
`public class GetDevicePoolTelemetryResponse`  
_public; L886-906_
- desc: Device telemetry respponse
- L891 _public property_ `public DateTime CreateTimeUtc { get; set; }` — The UTC time the telemetry data was created
- L896 _public property_ `public Dictionary<string, List<GetDevicePlatformTelemetryResponse>> Telemetry { get; set; }` — Individual pool telemetry data points
- L901-905 _public ctor_ `public GetDevicePoolTelemetryResponse(DateTime createTimeUtc, Dictionary<string, List<GetDevicePlatformTelemetryResponse>> telemetry)` — Constructor

#### class `EpicGames.Horde.Devices.LegacyCreateReservationRequest`  
`public class LegacyCreateReservationRequest`  
_public; L913-962_
- desc: Reservation request for legacy clients
- L919 _public property_ `public string[] DeviceTypes { get; set; }` — attrs: `[Required]` — The device types to reserve, these are mapped to platforms
- L925 _public property_ `public string Hostname { get; set; }` — attrs: `[Required]` — The hostname of machine reserving devices
- L931 _public property_ `public string Duration { get; set; }` — attrs: `[Required]` — The duration of reservation
- L936 _public property_ `public string? ReservationDetails { get; set; }` — Reservation details string
- L941 _public property_ `public string? PoolId { get; set; }` — The PoolId of reservation request
- L946 _public property_ `public string? JobId { get; set; }` — The JobId of reservation request
- L951 _public property_ `public string? StepId { get; set; }` — The StepId of reservation request
- L956 _public property_ `public string? DeviceName { get; set; }` — A specific device to reserve
- L961 _public property_ `public DeviceTagsRequest? Tags { get; set; }` — Desired metadata of the device

#### class `EpicGames.Horde.Devices.GetLegacyReservationResponse`  
`public class GetLegacyReservationResponse`  
_public; L967-1036_
- desc: Reservation response for legacy clients
- L973 _public property_ `public string[] DeviceNames { get; set; }` — attrs: `[Required]` — The names of the devices that were reserved
- L979 _public property_ `public string[] DevicePerfSpecs { get; set; }` — attrs: `[Required]` — The corresponding perf specs of the reserved devices
- L985 _public property_ `public string[] DeviceModels { get; set; }` — attrs: `[Required]` — The corresponding perf specs of the reserved devices
- L991 _public property_ `public string HostName { get; set; }` — attrs: `[Required]` — The host name of the machine making the reservation
- L997 _public property_ `public string StartDateTime { get; set; }` — attrs: `[Required]` — The start time of the reservation
- L1003 _public property_ `public string Duration { get; set; }` — attrs: `[Required]` — The duration of the reservation (before renew)
- L1008 _public property_ `public string? JobId { get; set; }` — The JobId of reservation request
- L1013 _public property_ `public string? StepId { get; set; }` — The StepId of reservation request
- L1018 _public property_ `public string? JobName { get; set; }` — The job name of reservation request
- L1023 _public property_ `public string? StepName { get; set; }` — The step name of reservation request
- L1029 _public property_ `public string Guid { get; set; }` — attrs: `[Required]` — The legacy guid of the reservation
- L1034 _public property_ `public bool? InstallRequired { get; set; }` — The step name of reservation request

#### class `EpicGames.Horde.Devices.GetLegacyDeviceResponse`  
`public class GetLegacyDeviceResponse`  
_public; L1041-1108_
- desc: Device response for legacy clients
- L1047 _public property_ `public string Id { get; set; }` — attrs: `[Required]` — The id of the reserved device
- L1053 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the reserved device
- L1059 _public property_ `public string Type { get; set; }` — attrs: `[Required]` — The (legacy) type of the device, mapped from platform id
- L1065 _public property_ `public string IPOrHostName { get; set; }` — attrs: `[Required]` — The IP or hostname of device
- L1071 _public property_ `public string PerfSpec { get; set; }` — attrs: `[Required]` — The (legacy) perf spec of the device
- L1077 _public property_ `public string Model { get; set; }` — attrs: `[Required]` — The device model information
- L1083 _public property_ `public string AvailableStartTime { get; set; }` — attrs: `[Required]` — The available start time which is parsed client side
- L1089 _public property_ `public string AvailableEndTime { get; set; }` — attrs: `[Required]` — The available end time which is parsed client side
- L1095 _public property_ `public bool Enabled { get; set; }` — attrs: `[Required]` — Whether device is enabled
- L1101 _public property_ `public string DeviceData { get; set; }` — attrs: `[Required]` — Associated device data
- L1107 _public property_ `public List<string> Tags { get; set; }` — attrs: `[Required]` — Any tags associated with the device

### `Source/Programs/Shared/EpicGames.Horde/Devices/DevicePlatformId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Devices.DevicePlatformId`  
`public readonly record struct DevicePlatformId(StringId Id)`  
_public; L18-35_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<DevicePlatformId, DevicePlatformIdConverter>))] [StringIdConverter(typeof(DevicePlatformIdConverter))] [CbConverter(typeof(StringIdCbConverter<DevicePlatformId, DevicePlatformIdConverter>))]`
- desc: Identifier for a device platform
- L23-25 _public ctor_ `public DevicePlatformId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public static DevicePlatformId Sanitize(string text)` — (inheritdoc)
- L34 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Devices.DevicePlatformIdConverter`  
`class DevicePlatformIdConverter : StringIdConverter<DevicePlatformId>`  
_internal*; L40-47_
- inherits: `StringIdConverter<DevicePlatformId>`
- desc: Converter to and from StringId instances.
- L43 _public method_ `public override DevicePlatformId FromStringId(StringId id)` — (inheritdoc)
- L46 _public method_ `public override StringId ToStringId(DevicePlatformId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Devices/DevicePoolId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Devices.DevicePoolId`  
`public readonly record struct DevicePoolId(StringId Id)`  
_public; L18-35_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<DevicePoolId, DevicePoolIdConverter>))] [StringIdConverter(typeof(DevicePoolIdConverter))] [CbConverter(typeof(StringIdCbConverter<DevicePoolId, DevicePoolIdConverter>))]`
- desc: Identifier for a device pool
- L23-25 _public ctor_ `public DevicePoolId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public static DevicePoolId Sanitize(string text)` — (inheritdoc)
- L34 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Devices.DevicePoolIdConverter`  
`class DevicePoolIdConverter : StringIdConverter<DevicePoolId>`  
_internal*; L40-47_
- inherits: `StringIdConverter<DevicePoolId>`
- desc: Converter to and from StringId instances.
- L43 _public method_ `public override DevicePoolId FromStringId(StringId id)` — (inheritdoc)
- L46 _public method_ `public override StringId ToStringId(DevicePoolId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/HordeApiVersion.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.HordeApiVersion`  
`public enum HordeApiVersion`  
_public; L17-53_
- desc: Version number for the Horde public API. Can be retrieved from the /api/v1/server/info endpoint via the Server.GetServerInfoResponse response. Should be serialized as an integer in messages to allow clients with missing enum names to still parse the result correctly.
- L22 _public* enumerator_ `Unknown = 0` — Unknown version
- L27 _public* enumerator_ `Initial = 1` — Initial version
- L32 _public* enumerator_ `AddLengthsToInteriorNodes = 2` — Interior nodes in chunked data now include the length of chunked data to allow seeking.
- L37 _public* enumerator_ `AddFileModTimes = 3` — Add support for last modified timestamps to file entries in directory nodes
- L42 _public* enumerator_ `AddRollingHashesForLeafNodes = 4` — Interior nodes in chunked data now include the rolling hash of any leaf nodes
- L47 _public* enumerator_ `LatestPlusOne` — One past the latest known version number. Add new version numbers above this point.
- L52 _public* enumerator_ `Latest = (int)(LatestPlusOne - 1)` — Latest API version

#### class `EpicGames.Horde.HordeApiVersionConverter`  
`public class HordeApiVersionConverter : JsonConverter<HordeApiVersion>`  
_public; L59-72_
- inherits: `JsonConverter<HordeApiVersion>`
- desc: Converter for HordeApiVersion which forces serialization as an integer, to override any default JsonStringEnumConverter that may be enabled.
- L62-65 _public method_ `public override HordeApiVersion Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L68-71 _public method_ `public override void Write(Utf8JsonWriter writer, HordeApiVersion value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/HordeClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeClient`  
`public abstract class HordeClient : IHordeClient, IAsyncDisposable`  
_public; L37-264_
- inherits: `IHordeClient, IAsyncDisposable`
- desc: Default implementation of IHordeClient
- L39 _private* field_ `readonly Uri _serverUrl`
- L40 _private* field_ `readonly BundleCache _bundleCache`
- L41 _private* field_ `readonly HordeOptions _hordeOptions`
- L42 _private* field_ `readonly ILoggerFactory _loggerFactory`
- L43 _private* field_ `readonly ILogger _logger`
- L45 _private* field_ `ServerComputeClient? _serverComputeClient`
- L46 _private* field_ `BackgroundTask<GrpcChannel>? _grpcChannel`
- L49 _public property_ `public Uri ServerUrl => ...` — (inheritdoc)
- L52 _public property_ `public IArtifactCollection Artifacts { get; }` — (inheritdoc)
- L55 _public property_ `public IComputeClient Compute => ...` — (inheritdoc)
- L58 _public property_ `public IProjectCollection Projects { get; }` — (inheritdoc)
- L61 _public property_ `public ISecretCollection Secrets { get; }` — (inheritdoc)
- L64 _public property_ `public IToolCollection Tools { get; }` — (inheritdoc)
- L67 _public event_ `public event Action? OnAccessTokenStateChanged` — (inheritdoc)
- L72 _protected property_ `protected ILogger Logger => ...` — Accessor for the logger instance
- L77-89 _protected ctor_ `protected HordeClient(Uri serverUrl, BundleCache bundleCache, IOptionsSnapshot<HordeOptions> hordeOptions, ILoggerFactory loggerFactory)` — Constructor
- L92-103 _public method_ `public virtual async ValueTask DisposeAsync()` — (inheritdoc)
- L108-111 _protected method_ `protected void NotifyAuthStateChanged()` — Notify listeners that the auth state has changed
- L114 _public method_ `public abstract Task<bool> LoginAsync(bool interactive, CancellationToken cancellationToken)` — (inheritdoc)
- L117 _public method_ `public abstract bool HasValidAccessToken()` — (inheritdoc)
- L120 _public method_ `public abstract Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken)` — (inheritdoc)
- L123-127 _public method_ `public async Task<GrpcChannel> CreateGrpcChannelAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L129-194 _private* method_ `async Task<GrpcChannel> CreateGrpcChannelInternalAsync(CancellationToken cancellationToken)`
- L197-202 _public method_ `public async Task<TClient> CreateGrpcClientAsync<TClient>(CancellationToken cancellationToken = default) where TClient : ClientBase<TClient>` — (inheritdoc)
- L205 _public method_ `public HordeHttpClient CreateHttpClient()` — (inheritdoc)
- L209-222 _private* method_ `ServerComputeClient CreateComputeClient()` — (inheritdoc)
- L225-249 _public method_ `public IStorageNamespace GetStorageNamespace(string basePath, string? accessToken = null)` — (inheritdoc)
- L252 _public method_ `public IServerLogger CreateServerLogger(LogId logId, LogLevel minimumLevel = LogLevel.Information)` — (inheritdoc)
- L258 _protected method_ `protected abstract HttpClient CreateAuthenticatedHttpClient()` — Creates an http client for satisfying requests
- L263 _protected method_ `protected abstract HttpClient CreateUnauthenticatedHttpClient()` — Creates an http client for satisfying requests

#### class `EpicGames.Horde.HordeClientWithStaticCredentials`  
`class HordeClientWithStaticCredentials : HordeClient`  
_internal*; L269-328_
- inherits: `HordeClient`
- desc: Default implementation of IHordeClient
- L271 _private* field_ `readonly string? _accessToken`
- L272 _private* field_ `readonly IHordeHttpMessageHandler _httpMessageHandler`
- L277-282 _public ctor_ `public HordeClientWithStaticCredentials(Uri serverUrl, string? accessToken, IHordeHttpMessageHandler httpMessageHandler, BundleCache bundleCache, IOptionsSnapshot<HordeOptions> hordeOptions, ILoggerFactory loggerFactory) : base(serverUrl, bundleCache, hordeOptions, loggerFactory)` — Constructor
- L285-288 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L291-299 _public method_ `public override async Task<bool> LoginAsync(bool allowLogin, CancellationToken cancellationToken)` — (inheritdoc)
- L302 _public method_ `public override bool HasValidAccessToken()` — (inheritdoc)
- L306 _public method_ `public override Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken)` — (inheritdoc)
- L310-319 _protected method_ `protected override HttpClient CreateAuthenticatedHttpClient()` — (inheritdoc)
- L322-327 _protected method_ `protected override HttpClient CreateUnauthenticatedHttpClient()` — (inheritdoc)

#### class `EpicGames.Horde.HordeClientWithDynamicCredentials`  
`class HordeClientWithDynamicCredentials : HordeClient`  
_internal*; L333-430_
- inherits: `HordeClient`
- desc: Default implementation of IHordeClient
- L335 _private const_ `private const string AllowInteractiveLoginHeaderKey = "Horde-AllowInteractiveLogin"`
- L336 _private field_ `private static readonly HttpRequestOptionsKey<bool> s_allowInteractiveLogin = new(AllowInteractiveLoginHeaderKey)`
- L338 _private* field_ `readonly OidcAuthState _authHandlerState`
- L339 _private* field_ `readonly IHordeHttpMessageHandler _baseHttpMessageHandler`
- L340 _private field_ `private readonly ITokenStore _tokenStore`
- L341 _private field_ `private readonly HordeAuthConfigProvider _hordeAuthConfigProvider`
- L344 _private* field_ `readonly HttpMessageHandler _authHttpMessageHandler` — attrs: `[SuppressMessage("Usage", "CA2213:Disposable fields should be disposed", Justification = "Lifetime is managed by caller")]`
- L349-365 _public ctor_ `public HordeClientWithDynamicCredentials(Uri serverUrl, BundleCache bundleCache, IHordeHttpMessageHandler baseHttpMessageHandler, IOptionsSnapshot<HordeOptions> hordeOptions, ILoggerFactory loggerFactory) : base(serverUrl, bundleCache, hordeOptions, loggerFactory)` — Constructor
- L368-376 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L379-393 _public method_ `public override async Task<bool> LoginAsync(bool allowLogin, CancellationToken cancellationToken)` — (inheritdoc)
- L396-406 _public method_ `public override bool HasValidAccessToken()` — (inheritdoc)
- L409 _public method_ `public override Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken)` — (inheritdoc)
- L413-418 _protected method_ `protected override HttpClient CreateAuthenticatedHttpClient()` — (inheritdoc)
- L421-426 _protected method_ `protected override HttpClient CreateUnauthenticatedHttpClient()` — (inheritdoc)
- L428 _private method_ `private static HttpOidcAuthHandlerConfig HordeOptionsToIHttpOidcAuthHandlerConfig(HordeOptions options)`

#### class `EpicGames.Horde.HordeClientFactory`  
`public class HordeClientFactory`  
_public; L435-478_
- desc: Allows creating HordeClient instances
- L437 _private* field_ `readonly BundleCache _bundleCache`
- L438 _private* field_ `readonly IHordeHttpMessageHandler _httpMessageHandler`
- L439 _private* field_ `readonly IOptionsSnapshot<HordeOptions> _hordeOptions`
- L440 _private* field_ `readonly ILoggerFactory _loggerFactory`
- L445-451 _public ctor_ `public HordeClientFactory(BundleCache bundleCache, IHordeHttpMessageHandler httpMessageHandler, IOptionsSnapshot<HordeOptions> hordeOptions, ILoggerFactory loggerFactory)` — Constructor
- L453-461 _private* method_ `Uri GetDefaultServerUrl()`
- L466-477 _public method_ `public HordeClient Create(Uri? serverUrl = null, string? accessToken = null)` — Create a client using the user's default access token

### `Source/Programs/Shared/EpicGames.Horde/HordeExtensions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeExtensions`  
`public static class HordeExtensions`  
_public; L17-55_
- desc: Extension methods for Horde
- L23-43 _public method_ `public static void AddHorde(this IServiceCollection serviceCollection)` — Adds Horde-related services with the default settings
- L50-54 _public method_ `public static void AddHorde(this IServiceCollection serviceCollection, Action<HordeOptions> configureHorde)` — Adds Horde-related services

### `Source/Programs/Shared/EpicGames.Horde/HordeHttpClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeHttpClient`  
`public sealed class HordeHttpClient : IDisposable`  
_public; L49-914_
- inherits: `IDisposable`
- desc: Wraps an Http client which communicates with the Horde server
- L54 _public const_ `public const string HordeUrlEnvVarName = "UE_HORDE_URL"` — Name of an environment variable containing the Horde server URL
- L59 _public const_ `public const string HordeTokenEnvVarName = "UE_HORDE_TOKEN"` — Name of an environment variable containing a token for connecting to the Horde server
- L64 _public const_ `public const string HttpClientName = "HordeHttpClient"` — Name of clients created from the http client factory
- L69 _public const_ `public const string AnonymousHttpClientName = "HordeAnonymousHttpClient"` — Name of clients used for anonymous requests.
- L74 _public const_ `public const string StorageHttpClientName = "HordeStorageHttpClient"` — Name of clients created for storage operations
- L79 _public const_ `public const string UploadRedirectHttpClientName = "HordeUploadRedirectHttpClient"` — Name of clients created from the http client factory for handling upload redirects. Should not contain Horde auth headers.
- L84 _public property_ `public HttpClient HttpClient => ...` — Accessor for the inner http client
- L86 _private* field_ `readonly HttpClient _httpClient`
- L88 _internal property_ `internal static JsonSerializerOptions JsonSerializerOptions => ...`
- L93 _public property_ `public Uri BaseUrl => ...` — Base address for the Horde server
- L99-102 _public ctor_ `public HordeHttpClient(HttpClient httpClient)` — Constructor
- L105-108 _public method_ `public void Dispose()` — (inheritdoc)
- L114 _public method_ `public static void ConfigureJsonSerializer(JsonSerializerOptions options)` — Configures a JSON serializer to read Horde responses
- L121-126 _public method_ `public async Task<bool> CheckConnectionAsync(CancellationToken cancellationToken = default)` — Check account login status.
- L138-147 _public method_ `public Task<List<GetAgentResponse>> GetAgentsAsync(PoolId? poolId = null, bool includeDeleted = false, CancellationToken cancellationToken = default)` — Gets a list of agents matching the specified criteria
- L154-157 _public method_ `public Task<GetAgentResponse> GetAgentAsync(AgentId agentId, CancellationToken cancellationToken = default)` — Gets information about a specific agent
- L175-205 _public method_ `public Task<List<GetAgentLeaseResponse>> GetLeasesAsync(AgentId? agentId = null, SessionId? sessionId = null, DateTime? startTime = null, DateTime? finishTime = null, DateTime? minFinishTime = null, DateTime? maxFinishTime = null, int index = 0, int count = 1000, CancellationToken cancellationToken = default)` — Gets a list of leases matching the specified criteria
- L222-225 _public method_ `public Task<CreateArtifactResponse> CreateArtifactAsync(ArtifactName name, ArtifactType type, string? description, StreamId streamId, CommitId commitId, IEnumerable<string>? keys = null, IEnumerable<string>? metadata = null, CancellationToken cancellationToken = default)` — Creates a new artifact
- L232-235 _public method_ `public async Task DeleteArtifactAsync(ArtifactId id, CancellationToken cancellationToken = default)` — Deletes an artifact
- L242-245 _public method_ `public Task<GetArtifactResponse> GetArtifactAsync(ArtifactId id, CancellationToken cancellationToken = default)` — Gets metadata about an artifact object
- L252-255 _public method_ `public async Task<Stream> GetArtifactZipAsync(ArtifactId id, CancellationToken cancellationToken = default)` — Gets a zip stream for a particular artifact
- L269 _public method_ `public Task<List<GetArtifactResponse>> FindArtifactsAsync(StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, CancellationToken cancellationToken = default)` — Finds artifacts with a certain type with an optional streamId
- L285-331 _public method_ `public async Task<List<GetArtifactResponse>> FindArtifactsAsync(IEnumerable<ArtifactId>? ids, StreamId? streamId = null, CommitId? minCommitId = null, CommitId? maxCommitId = null, ArtifactName? name = null, ArtifactType? type = null, IEnumerable<string>? keys = null, int maxResults = 100, CancellationToken cancellationToken = default)` — Finds artifacts with a certain type with an optional streamId
- L343-346 _public method_ `public Task<GetDashboardPreviewResponse> CreateDashbordPreviewAsync(CreateDashboardPreviewRequest request, CancellationToken cancellationToken = default)` — Create a new dashboard preview item
- L352-355 _public method_ `public Task<GetDashboardPreviewResponse> UpdateDashbordPreviewAsync(UpdateDashboardPreviewRequest request, CancellationToken cancellationToken = default)` — Update a dashboard preview item
- L361-364 _public method_ `public Task<List<GetDashboardPreviewResponse>> GetDashbordPreviewsAsync(bool open = true, CancellationToken cancellationToken = default)` — Query dashboard preview items
- L375-378 _public method_ `public Task<JsonObject> GetParametersAsync(CancellationToken cancellationToken = default)` — Query parameters for other tools
- L386-394 _public method_ `public Task<JsonObject> GetParametersAsync(string? path, CancellationToken cancellationToken = default)` — Query parameters for other tools
- L407-410 _public method_ `public Task<List<GetProjectResponse>> GetProjectsAsync(bool includeStreams = false, bool includeCategories = false, CancellationToken cancellationToken = default)` — Query all the projects
- L418-421 _public method_ `public Task<GetProjectResponse> GetProjectAsync(ProjectId projectId, CancellationToken cancellationToken = default)` — Retrieve information about a specific project
- L432-435 _public method_ `public Task<GetSecretsResponse> GetSecretsAsync(CancellationToken cancellationToken = default)` — Query all the secrets available to the current user
- L443-446 _public method_ `public Task<GetSecretResponse> GetSecretAsync(SecretId secretId, CancellationToken cancellationToken = default)` — Retrieve information about a specific secret
- L455-458 _public method_ `public Task<GetSecretPropertyResponse> ResolveSecretAsync(string value, CancellationToken cancellationToken = default)` — Retrieve information about a specific secret and property
- L469-472 _public method_ `public Task<GetServerInfoResponse> GetServerInfoAsync(CancellationToken cancellationToken = default)` — Gets information about the currently deployed server version
- L484-509 _public method_ `public async Task<ReadRefResponse?> TryReadRefAsync(string path, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Attempts to read a named storage ref from the server
- L526-570 _public method_ `public async Task<HttpResponseMessage> PostTelemetryAsync(string appId, int appVersion, string appEnvironment, object[] payloads, string? sessionId = null, CancellationToken cancellationToken = default)` — Posts telemetry to Horde.
- L579-588 _public method_ `public Task<List<GetUtilizationDataResponse>> GetTelemetryAsync(DateTime endDate, int range, int? tzOffset = null, CancellationToken cancellationToken = default)` — Gets telemetry for Horde within a given range
- L597-600 _public method_ `public Task<GetToolsSummaryResponse> GetToolsAsync(CancellationToken cancellationToken = default)` — Enumerates all the available tools.
- L605-608 _public method_ `public Task<GetToolResponse> GetToolAsync(ToolId id, CancellationToken cancellationToken = default)` — Gets information about a particular tool
- L613-616 _public method_ `public Task<GetToolDeploymentResponse> GetToolDeploymentAsync(ToolId id, ToolDeploymentId deploymentId, CancellationToken cancellationToken = default)` — Gets information about a particular deployment
- L621-631 _public method_ `public async Task<Stream> GetToolDeploymentZipAsync(ToolId id, ToolDeploymentId? deploymentId, CancellationToken cancellationToken = default)` — Gets a zip stream for a particular deployment
- L642-647 _public method_ `public async Task<ToolDeploymentId> CreateToolDeploymentAsync(ToolId id, string? version, double? duration, bool? createPaused, HashedBlobRefValue target, CancellationToken cancellationToken = default)` — Creates a new tool deployment
- L656-659 _public method_ `public Task UpdateToolDeploymentAsync(ToolId id, ToolDeploymentId deploymentId, UpdateDeploymentRequest request, CancellationToken cancellationToken = default)` — Updates a tool deployment (e.g. changing its state)
- L671-702 _public method_ `public async Task<ToolDeploymentId> CreateToolDeploymentFromStreamAsync(ToolId id, string version, Stream content, string fileName, TimeSpan? duration = null, bool createPaused = false, CancellationToken cancellationToken = default)` — Creates a new tool deployment by uploading a zip file via multipart form data (v1 API)
- L713-716 _public method_ `public Task<GetJobResponse> GetJobAsync(JobId id, CancellationToken cancellationToken = default)` — Gets job information for given job ID. Fail response if jobID does not exist.
- L726-729 _public method_ `public Task PutJobMetadataAsync(JobId id, IEnumerable<string>? jobMetaData = null, Dictionary<string, List<string>>? stepMetaData = null, CancellationToken cancellationToken = default)` — Apply metadata tags to jobs and steps
- L745-794 _public method_ `public Task<List<GetJobResponse>> GetJobsAsync( StreamId streamId, IEnumerable<TemplateId>? templateIds = null, List<string>? filters = null, CommitId? minChange = null, CommitId? maxChange = null, DateTimeOffset? minCreateTime = null, DateTimeOffset? maxCreateTime = null, bool includePreflight = false, int count = 100, CancellationToken cancellationToken = default)` — Get a list of job information for given stream ID and template IDs. Returns maximum count results or fewer.
- L807-810 _public method_ `public Task<SearchLogResponse> GetSearchLogAsync(LogId logId, string searchText, int count = 5, CancellationToken cancellationToken = default)` — Get the given log file
- L820-823 _public method_ `public Task<LogLinesResponse> GetLogLinesAsync(LogId logId, int startIndex, int count, CancellationToken cancellationToken = default)` — Get the requested number of lines from given logFileId, starting at index
- L832-835 _public method_ `public Task<GetBatchLogEventsResponse> GetBatchLogEventsAsync(GetBatchLogEventsRequest request, CancellationToken cancellationToken = default)` — Get events for multiple log files in a single request. Set GetBatchLogEventsRequest.Count to 0 to retrieve only the per-log totals without downloading any event payloads.
- L847-850 _public method_ `public Task<GetGraphResponse> GetGraphAsync(JobId jobId, CancellationToken cancellationToken = default)` — Get graph of the given job
- L863-876 _public method_ `public Task<GetUgsMetadataListResponse> GetUgsMetadataAsync(StreamId streamId, CommitId commitId, ProjectId projectId, CancellationToken cancellationToken = default)`
- L886-889 _public method_ `public Task<List<GetDeviceResponse>> GetDevicesAsync(CancellationToken cancellationToken = default)` — Retrieves information about all devices
- L897-900 _public method_ `public Task<GetDeviceResponse> GetDeviceAsync(string deviceId, CancellationToken cancellationToken = default)` — Retrieves information about the specified device
- L909-912 _public method_ `public Task<HttpResponseMessage> PutDeviceUpdateAsync(string deviceId, UpdateDeviceRequest request, CancellationToken cancellationToken = default)` — Updates an individual device with the requested fields

### `Source/Programs/Shared/EpicGames.Horde/HordeHttpMessageHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeHttpMessageHandler`  
`class HordeHttpMessageHandler : IHordeHttpMessageHandler, IDisposable`  
_internal*; L20-101_
- inherits: `IHordeHttpMessageHandler, IDisposable`
- desc: Concrete implementation of IHordeHttpMessageHandler which manages the lifetime of the HttpMessageHandler instance.
- L22 _private* field_ `readonly HttpMessageHandler _instance`
- L25 _public property_ `public HttpMessageHandler Instance => ...` — (inheritdoc)
- L31-36 _public ctor_ `public HordeHttpMessageHandler(ILogger<HordeHttpMessageHandler> logger)` — Constructor
- L39 _public method_ `public void Dispose()` — (inheritdoc)
- L45-65 _private* method_ `static IAsyncPolicy<HttpResponseMessage> CreateDefaultTimeoutRetryPolicy(HttpRequestMessage request, ILogger logger)` — Create a default timeout retry policy
- L70-86 _private* method_ `static IAsyncPolicy<HttpResponseMessage> CreateHordeTransientErrorPolicy(HttpRequestMessage request, ILogger logger)` — Create an error and timeout retry policy taking into account Horde's use of 503 errors
- L91-100 _public method_ `public static IAsyncPolicy<HttpResponseMessage> CreateDefaultTransientErrorPolicy()` — Create a default retry policy

### `Source/Programs/Shared/EpicGames.Horde/HordeHttpRequest.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeHttpRequest`  
`public static class HordeHttpRequest`  
_public; L19-168_
- desc: Static helper methods for implementing Horde HTTP requests with standard semantics
- L21 _private* field_ `static readonly JsonSerializerOptions s_jsonSerializerOptions = CreateJsonSerializerOptions()`
- L22 _internal property_ `internal static JsonSerializerOptions JsonSerializerOptions => ...`
- L27-32 _private* method_ `static JsonSerializerOptions CreateJsonSerializerOptions()` — Create the shared instance of JSON options for HordeHttpClient instances
- L38-49 _public method_ `public static void ConfigureJsonSerializer(JsonSerializerOptions options)` — Configures a JSON serializer to read Horde responses
- L57-61 _public method_ `public static async Task DeleteAsync(HttpClient httpClient, string relativePath, CancellationToken cancellationToken = default)` — Deletes a resource from an HTTP endpoint
- L71-75 _public method_ `public static async Task<TResponse> GetAsync<TResponse>(HttpClient httpClient, string relativePath, CancellationToken cancellationToken = default)` — Gets a resource from an HTTP endpoint and parses it as a JSON object
- L86-89 _internal method_ `internal static async Task<HttpResponseMessage> PostAsync<TRequest>(HttpClient httpClient, string relativePath, TRequest request, CancellationToken cancellationToken = default)` — Posts an object to an HTTP endpoint as a JSON object, and parses the response object
- L101-114 _public method_ `public static async Task<TResponse> PostAsync<TResponse, TRequest>(HttpClient httpClient, string relativePath, TRequest request, CancellationToken cancellationToken = default)` — Posts an object to an HTTP endpoint as a JSON object, and parses the response object
- L125-128 _public method_ `public static async Task<HttpResponseMessage> PutAsync<TRequest>(HttpClient httpClient, string relativePath, TRequest request, CancellationToken cancellationToken)` — Puts an object to an HTTP endpoint as a JSON object
- L140-153 _public method_ `public static async Task<TResponse> PutAsync<TResponse, TRequest>(HttpClient httpClient, string relativePath, TRequest request, CancellationToken cancellationToken)` — Puts an object to an HTTP endpoint as a JSON object
- L163-167 _public method_ `public static async Task PatchAsync<TRequest>(HttpClient httpClient, string relativePath, TRequest request, CancellationToken cancellationToken = default)` — Patches a resource at an HTTP endpoint with a JSON object

### `Source/Programs/Shared/EpicGames.Horde/HordeOptions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.HordeOptions`  
`public class HordeOptions`  
_public; L21-198_
- desc: Options for configuring the Horde connection
- L26 _public property_ `public Uri? ServerUrl { get; set; }` — Address of the Horde server
- L31 _public property_ `public string? AccessToken { get; set; }` — Access token to use for connecting to the server
- L36 _public property_ `public bool AllowAuthPrompt { get; set; }` — Whether to allow opening a browser window to prompt for authentication
- L41 _public property_ `public BundleOptions Bundle { get; }` — Options for creating new bundles
- L46 _public property_ `public BundleCacheOptions BundleCache { get; }` — Options for caching bundles
- L51 _public property_ `public StorageBackendCacheOptions BackendCache { get; }` — Options for the storage backend cache
- L56 _public method_ `public Uri? GetServerUrlOrDefault()` — Gets the configured server URL, or the default value
- L62-70 _public method_ `public static Uri? GetServerUrlFromEnvironment()` — Reads the server URL from the environment
- L76-123 _public method_ `public static Uri? GetDefaultServerUrl()` — Gets the default server URL for the current user
- L129-173 _public method_ `public static void SetDefaultServerUrl(Uri serverUrl)` — Sets the default server url for the current user
- L175-181 _private* method_ `static FileReference? GetConfigFile()`
- L184-197 _private* method_ `static void DeleteRegistryKey(RegistryKey key, string name)` — attrs: `[SupportedOSPlatform("windows")]`

#### class `EpicGames.Horde.StorageBackendCacheOptions`  
`public class StorageBackendCacheOptions`  
_public; L203-214_
- desc: Options for the storage backend cache
- L208 _public property_ `public string? CacheDir { get; set; }` — Directory to store cached data
- L213 _public property_ `public long MaxSize { get; set; }` — Maximum size of the cache, in bytes

### `Source/Programs/Shared/EpicGames.Horde/IHordeClient.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.IHordeClient`  
`public interface IHordeClient`  
_public; L21-95_
- desc: Interface for Horde functionality.
- L26 _public* property_ `Uri ServerUrl { get; }` — URL of the horde server
- L31 _public* property_ `IArtifactCollection Artifacts { get; }` — Accessor for the artifact collection
- L36 _public* property_ `IComputeClient Compute { get; }` — Accessor for the compute client
- L41 _public* property_ `IProjectCollection Projects { get; }` — Accessor for the project collection
- L46 _public* property_ `ISecretCollection Secrets { get; }` — Accessor for the secret collection
- L51 _public* property_ `IToolCollection Tools { get; }` — Accessor for the tools collection
- L56 _public* event_ `event Action? OnAccessTokenStateChanged` — Event triggered whenever the access token state changes
- L64 _public* method_ `Task<bool> LoginAsync(bool interactive, CancellationToken cancellationToken)` — Connect to the Horde server
- L69 _public* method_ `bool HasValidAccessToken()` — Gets the current connection state
- L74 _public* method_ `Task<string?> GetAccessTokenAsync(bool interactive, CancellationToken cancellationToken = default)` — Gets an access token for the server
- L79 _public* method_ `Task<TClient> CreateGrpcClientAsync<TClient>(CancellationToken cancellationToken = default) where TClient : ClientBase<TClient>` — Gets a gRPC client interface
- L84 _public* method_ `HordeHttpClient CreateHttpClient()` — Creates a Horde HTTP client
- L89 _public* method_ `IStorageNamespace GetStorageNamespace(string relativePath, string? accessToken = null)` — Creates a storage namespace for the given base path
- L94 _public* method_ `IServerLogger CreateServerLogger(LogId logId, LogLevel minimumLevel = LogLevel.Information)` — Creates a logger device that writes data to the server

#### interface `EpicGames.Horde.IHordeClientWithLifetime`  
`public interface IHordeClientWithLifetime : IHordeClient, IAsyncDisposable`  
_public; L100-102_
- inherits: `IHordeClient, IAsyncDisposable`
- desc: Interface for a Horde client with a known lifetime

#### class `EpicGames.Horde.HordeClientExtensions`  
`public static class HordeClientExtensions`  
_public; L107-156_
- desc: Extension methods for IHordeClient
- L112 _public method_ `public static IStorageNamespace GetStorageNamespace(this IHordeClient hordeClient, NamespaceId namespaceId, string? accessToken = null)` — Creates a storage namespace for a particular id
- L118 _public method_ `public static IStorageNamespace GetStorageNamespace(this IHordeClient hordeClient, ArtifactId artifactId)` — Creates a storage namespace for a particular artifact
- L124 _public method_ `public static IStorageNamespace GetStorageNamespace(this IHordeClient hordeClient, LogId logId)` — Creates a storage namespace for a particular log
- L130 _public method_ `public static IStorageNamespace GetStorageNamespace(this IHordeClient hordeClient, ToolId toolId)` — Creates a storage namespace for a particular tool
- L136-146 _public method_ `public static async Task<IBlobRef?> TryReadRefAsync(this IHordeClient hordeClient, string path, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Reads a blob storage ref from a path
- L151-155 _public method_ `public static async Task<IBlobRef<T>?> TryReadRefAsync<T>(this IHordeClient hordeClient, string path, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Reads a typed blob storage ref from a path

### `Source/Programs/Shared/EpicGames.Horde/IHordeHttpMessageHandler.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.IHordeHttpMessageHandler`  
`public interface IHordeHttpMessageHandler`  
_public; L10-16_
- desc: Provides access to a HttpMessageHandler instances for Horde with a default resiliance pipeline.
- L15 _public* property_ `HttpMessageHandler Instance { get; }` — Instance of the http message handler

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/BuildGraphIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.BuildGraphIssueHandler`  
`public class BuildGraphIssueHandler : IssueHandler`  
_public; L13-58_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular BuildGraph script error
- L15 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L18 _public property_ `public override int Priority => ...` — (inheritdoc)
- L25-28 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L30 _private* method_ `static bool IsMaskedEventId(EventId id)`
- L33-54 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L57 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/CompileIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.CompileIssueHandler`  
`public class CompileIssueHandler : IssueHandler`  
_public; L13-90_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L18 _private* const_ `const string CompileTypeAnnotation = "CompileType"` — Annotation describing the compile type
- L23 _private* const_ `const string CompileGroupAnnotation = "CompileGroup"` — Annotation specifying a group for compile issues from this node
- L25 _private* field_ `readonly IssueHandlerContext _context`
- L26 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L29 _public property_ `public override int Priority => ...` — (inheritdoc)
- L34-37 _public ctor_ `public CompileIssueHandler(IssueHandlerContext context)` — Constructor
- L44-47 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L49 _private* method_ `static bool IsMaskedEventId(EventId id)`
- L52-86 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L89 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/ContentIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.ContentIssueHandler`  
`public class ContentIssueHandler : IssueHandler`  
_public; L13-49_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L15 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L17 _private* method_ `static bool IsMatchingEventId(EventId eventId)`
- L18 _private* method_ `static bool IsMaskedEventId(EventId eventId)`
- L21 _public property_ `public override int Priority => ...` — (inheritdoc)
- L24-45 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L48 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/CopyrightIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.CopyrightIssueHandler`  
`public class CopyrightIssueHandler : IssueHandler`  
_public; L13-38_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L15 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L18 _public property_ `public override int Priority => ...` — (inheritdoc)
- L21-34 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L37 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/DefaultIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.DefaultIssueHandler`  
`public class DefaultIssueHandler : IssueHandler`  
_public; L12-48_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Default handler for log events not matched by any other handler
- L14 _private* field_ `readonly IssueHandlerContext _context`
- L15 _private* field_ `IssueEventGroup? _issue`
- L18 _public property_ `public override int Priority => ...` — (inheritdoc)
- L23 _public ctor_ `public DefaultIssueHandler(IssueHandlerContext context)` — Constructor
- L26-38 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L41-47 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/ExternalIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.ExternalIssueHandler`  
`public class ExternalIssueHandler : IssueHandler`  
_public; L17-79_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Handler for log events with issue fingerprints embedded in the structured log data itself
- L19 _private* field_ `static readonly JsonNodeOptions s_jsonNodeOptions = new() { PropertyNameCaseInsensitive = true }`
- L20 _private* field_ `static readonly JsonSerializerOptions? s_jsonSerializerOptions = new() { PropertyNameCaseInsensitive = true }`
- L22 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L25 _public property_ `public override int Priority => ...` — (inheritdoc)
- L28-52 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L55 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)
- L58-78 _private* method_ `static IssueFingerprint? ParseIssueFingerprint(JsonLogEvent line)`

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/GauntletIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.GauntletIssueHandler`  
`public class GauntletIssueHandler : IssueHandler`  
_public; L18-360_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular Gauntlet error
- L23 _private* const_ `const string FrameworkPrefix = "test framework"` — Prefix for framework keys
- L28 _private* const_ `const string TestPrefix = "test"` — Prefix for test keys
- L33 _private* const_ `const string DevicePrefix = "device"` — Prefix for device keys
- L38 _private* const_ `const string BuildDropPrefix = "build drop"` — Prefix for build drop keys
- L43 _private* const_ `const string FatalPrefix = "fatal"` — Prefix for fatal failure keys
- L48 _private* const_ `const string CallstackLogType = "Callstack"` — Callstack log type property
- L53 _private* const_ `const string SummaryLogType = "Summary"` — Summary log type property
- L58 _private* const_ `const int MaxLines = 6` — Max Number of lines to consider to hash
- L63 _private* const_ `const int MaxMessageLength = 2000` — Max Message Length to hash
- L68 _private* field_ `bool _wasSevereEventReported = false` — Whether or not a severe event was reported
- L73 _private* field_ `bool _wasTestEventReported = false` — Whether or not a test event was reported
- L78 _private* field_ `bool _wasErrorEventReported = false` — Whether or not at least one error was reported
- L80 _private* field_ `readonly IssueHandlerContext _context`
- L81 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L86 _private* field_ `static readonly Dictionary<EventId, string> s_knownGauntletEvents = ...` — Known Gauntlet events
- L86 _private* field_ `static readonly Dictionary< s_knownGauntletEvents = new() { { KnownLogEvents.Gauntlet, FrameworkPrefix}, { KnownLogEvents.Gauntlet_TestEvent, TestPrefix}, { KnownLogEvents.Gauntlet_DeviceEvent, DevicePrefix}, { KnownLogEvents.Gauntlet_UnrealEngineTestE ...` — Known Gauntlet events
- L99 _private* field_ `static readonly HashSet<EventId> s_knownSevereGauntletEvents = [ KnownLogEvents.Gauntlet_BuildDropEvent, KnownLogEvents.Gauntlet_FatalEvent ]` — Known Gauntlet events associated with the highest severity
- L108 _private* field_ `static readonly HashSet<EventId> s_knownTestGauntletEvents = [ KnownLogEvents.Gauntlet_TestEvent, KnownLogEvents.Gauntlet_UnrealEngineTestEvent ]` — Known Gauntlet events associated with test context
- L117 _private* field_ `static readonly HashSet<EventId> s_skipGauntletEvents = [ KnownLogEvents.Gauntlet_DeviceEvent ]` — Gauntlet events to skip issue generation
- L125 _private* field_ `static readonly string[] s_unspecificSummaries = [ "Unhandled Exception: EXCEPTION_ACCESS_VIOLATION reading address" ]` — Known summaries that are not specific enough
- L130 _public property_ `public override int Priority => ...` — (inheritdoc)
- L135 _public ctor_ `public GauntletIssueHandler(IssueHandlerContext context)` — Constructor
- L142-145 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L152-155 _public method_ `public static string GetEventPrefix(EventId eventId)` — Return the prefix string associate with the event id
- L164-185 _private method_ `private void GetHash(IssueEvent issueEvent, HashSet<IssueKey> keys, HashSet<IssueMetadata> metadata, bool hasCallstack)` — Produce a hash from error message
- L187-214 _private method_ `private static bool TryGetHash(IssueEvent issueEvent, out Md5Hash hash)`
- L216-219 _private method_ `private static bool EventHasCallstackProperty(IssueEvent issueEvent)`
- L221-247 _private method_ `private static string? GetSummaryProperty(IssueEvent issueEvent)`
- L249-270 _private method_ `private static JsonProperty? FindNestedPropertyOfType(JsonLogEvent logEvent, string searchType)`
- L273-356 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L359 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/HashedIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.HashedIssueHandler`  
`public class HashedIssueHandler : IssueHandler`  
_public; L18-309_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L20 _private* field_ `readonly IssueHandlerContext _context`
- L21 _private* field_ `readonly List<IssueEvent> _issueEvents = []`
- L26 _private* field_ `static readonly HashSet<EventId> s_knownGeneralEvents = [KnownLogEvents.Generic, KnownLogEvents.ExitCode, KnownLogEvents.Horde, KnownLogEvents.Horde_InvalidPreflight]` — Known general events
- L31 _public ctor_ `public HashedIssueHandler(IssueHandlerContext context)` — Constructor
- L38-41 _public method_ `public static bool IsGeneralEventId(EventId eventId)` — Determines if the given event is general and should be salted to make it unique
- L44 _public property_ `public override int Priority => ...` — (inheritdoc)
- L47-51 _public method_ `public override bool HandleEvent(IssueEvent logEvent)` — (inheritdoc)
- L57-93 _private* method_ `static string? GetLogChannel(IssueEvent logEvent)` — Get the channel for issue event
- L96-230 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)
- L235-256 _private* method_ `static string? GetStringProperty(IssueEvent logEvent, string propertyName)` — Gets a string property value from the event's JSON properties
- L258-287 _private* method_ `static void AddFileMetadata(IssueEventGroup issue, IssueEvent stepEvent)`
- L289-308 _private* method_ `static bool TryGetHash(string message, out Md5Hash hash)`

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/IgnoredIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.IgnoredIssueHandler`  
`public class IgnoredIssueHandler : IssueHandler`  
_public; L13-56_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular systemic error
- L18 _private* field_ `static readonly HashSet<EventId> s_handledEvents = [KnownLogEvents.Horde_BuildHealth_Ignore]` — Known systemic errors
- L21 _public property_ `public override int Priority => ...` — (inheritdoc)
- L28-31 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L33 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L38 _public ctor_ `public IgnoredIssueHandler()` — Constructor
- L41-52 _public method_ `public override bool HandleEvent(IssueEvent logEvent)` — (inheritdoc)
- L55 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/LocalizationIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.LocalizationIssueHandler`  
`public class LocalizationIssueHandler : IssueHandler`  
_public; L14-293_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of an issue handler for localization warnings/errors
- L38 _private* field_ `readonly IssueHandlerContext _context`
- L39 _private* field_ `readonly IssueEventGroup _issuesWithoutClearSuspects`
- L40 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L43 _public property_ `public override int Priority => ...` — (inheritdoc)
- L48-52 _public ctor_ `public LocalizationIssueHandler(IssueHandlerContext context)` — Constructor
- L59-62 _public method_ `public static bool IsMatchingEventId(EventId? eventId)` — Determines if the given event id matches
- L69-72 _private* method_ `static bool IsMaskedEventId(EventId eventId)` — Determines if an event should be masked by this
- L74-93 _private method_ `private IssueEventGroup CreateNewIssueGroup()`
- L100-116 _private method_ `private static void AddLocalizationIssueKeys(HashSet<IssueKey> keys, LocalizationData data)` — Generate all the IssueKeys with the extracted LocalizationData
- L122-184 _private method_ `private static LocalizationData GetLocalizationData(IssueEvent issueEvent)` — Extracts the localization data from the properties of an IssueEvent
- L190-218 _private method_ `private static void ConvertLocationToFile(LocalizationData data)` — Location data in LocalizationData may contain file information. We can try to parse it.
- L224-244 _private method_ `private static void RemoveFilesExtension(LocalizationData data)` — LocalizationData file paths may contain extensions, remove them
- L247-289 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L292 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

#### class `EpicGames.Horde.Issues.Handlers.LocalizationIssueHandler.LocalizationData`  
`private class LocalizationData`  
_private; L16-36_
- L18 _public field_ `public string _file = ""`
- L19 _public field_ `public int _line = -1`
- L20 _public field_ `public string _location = ""`
- L21 _public field_ `public string _localizationNamespace = ""`
- L22 _public field_ `public string _localizationKey = ""`
- L24 _public field_ `public string _conflictFile = ""`
- L25 _public field_ `public int _conflictLine = -1`
- L26 _public field_ `public string _conflictLocation = ""`
- L27 _public field_ `public string _conflictLocalizationNamespace = ""`
- L28 _public field_ `public string _conflictLocalizationKey = ""`
- L30 _public method_ `public bool HasLocalizationKey()`
- L31 _public method_ `public string GetNamespaceKeyString()`
- L33 _public method_ `public bool HasFile()`
- L34 _public method_ `public bool HasConflictFile()`
- L35 _public method_ `public bool HasAnyFile()`

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/PerforceCaseIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.PerforceCaseIssueHandler`  
`public class PerforceCaseIssueHandler : IssueHandler`  
_public; L13-48_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a Perforce case mismatch error
- L15 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L18 _public property_ `public override int Priority => ...` — (inheritdoc)
- L25-28 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L31-44 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L47 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/SanitizerIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.SanitizerIssueHandler`  
`public class SanitizerIssueHandler : IssueHandler`  
_public; L15-87_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a specific Thread Sanitizer error
- L17 _private* field_ `static readonly Utf8String s_summaryReasonAnnotation = new("SummaryReason")`
- L18 _private* field_ `static readonly Utf8String s_summarySourceFileAnnotation = new("SummarySourceFile")`
- L19 _private* field_ `static readonly Utf8String s_sanitizerNameAnnotation = new("SanitizerName")`
- L20 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L23 _public property_ `public override int Priority => ...` — (inheritdoc)
- L27 _public property_ `public static LogValue SanitizerName => ...` — Log value describing the thread sanitizer error summary reason
- L32 _public property_ `public static LogValue SummaryReason => ...` — Log value describing the thread sanitizer error summary reason
- L37 _public property_ `public static LogValue SummarySourceFile => ...` — Log value describing the thread sanitizer error summary source file
- L39-51 _private* method_ `static bool FindAnnotation(IssueEvent issueEvent, Utf8String annotation, ref string result)`
- L54-83 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L86 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/ScopedIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.ScopedIssueHandler`  
`public class ScopedIssueHandler : IssueHandler`  
_public; L17-99_
- attrs: `[IssueHandler(Tag = "Scoped")]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L19 _private* const_ `const string NodeName = "Node"`
- L20 _private* const_ `const string ScopeName = "Scope"`
- L22 _private* field_ `readonly IssueHandlerContext _context`
- L23 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L26 _public property_ `public override int Priority => ...` — (inheritdoc)
- L30 _public ctor_ `public ScopedIssueHandler(IssueHandlerContext context)` — Constructor
- L33-84 _public method_ `public override bool HandleEvent(IssueEvent logEvent)` — (inheritdoc)
- L87 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)
- L89-98 _private* method_ `static bool TryGetHash(string message, out Md5Hash hash)`

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/ShaderIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.ShaderIssueHandler`  
`public class ShaderIssueHandler : IssueHandler`  
_public; L21-123_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Handles shader compile errors and warnings, creating issue groups for tracking. Grouping behavior: - For "Failed to compile Material" warnings: Groups by material path, so all compilation failures for the same material (across different platforms/shaders) are tracked as one issue. - For other shader errors: Groups by source file, creating separate issues per file. The material path is extracted by ShaderEventMatcher and passed as a "material" property.
- L23 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L25 _private* method_ `static bool IsMatchingEventId(EventId id)`
- L26 _private* method_ `static bool IsMaskedEventId(EventId id)`
- L29 _public property_ `public override int Priority => ...` — (inheritdoc)
- L32-72 _public method_ `public override bool HandleEvent(IssueEvent logEvent)` — (inheritdoc)
- L78-99 _private method_ `private static string? TryGetMaterialPath(IssueEvent logEvent)` — Extracts the material path from the event's "material" property, if present. This property is set by ShaderEventMatcher when it detects "Failed to compile Material" warnings.
- L105-119 _private method_ `private static string GetMaterialDisplayName(string materialPath)` — Extracts a display-friendly material name from the full material path. For example: "/Game/Materials/MyMaterial.MyMaterial" -> "MyMaterial"
- L122 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/SymbolIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.SymbolIssueHandler`  
`public class SymbolIssueHandler : IssueHandler`  
_public; L13-76_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular compile error
- L15 _private* const_ `const string EventIdName = "EventId"`
- L17 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L20 _public property_ `public override int Priority => ...` — (inheritdoc)
- L27-30 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L37-40 _private* method_ `static bool IsMaskedEventId(EventId eventId)` — Determines if an event should be masked by this
- L43-72 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L75 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/SystemicIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.SystemicIssueHandler`  
`public class SystemicIssueHandler : IssueHandler`  
_public; L13-75_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a particular systemic error
- L18 _private* field_ `static readonly HashSet<EventId> s_knownSystemic = [KnownLogEvents.Horde, KnownLogEvents.Horde_InvalidPreflight]` — Known systemic errors
- L21 _public property_ `public override int Priority => ...` — (inheritdoc)
- L28-31 _public method_ `public static bool IsMatchingEventId(EventId eventId)` — Determines if the given event id matches
- L33 _private* field_ `bool _nonSystemicError = false`
- L34 _private* field_ `readonly IssueHandlerContext _context`
- L35 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L40 _public ctor_ `public SystemicIssueHandler(IssueHandlerContext context)` — Constructor
- L43-71 _public method_ `public override bool HandleEvent(IssueEvent logEvent)` — (inheritdoc)
- L74 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/UnacceptableWordsIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.UnacceptableWordsIssueHandler`  
`public class UnacceptableWordsIssueHandler : IssueHandler`  
_public; L13-38_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: Instance of a Perforce case mismatch error
- L15 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L18 _public property_ `public override int Priority => ...` — (inheritdoc)
- L21-34 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L37 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/Handlers/WorldLeakIssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.Handlers.WorldLeakIssueHandler`  
`public class WorldLeakIssueHandler : IssueHandler`  
_public; L15-87_
- attrs: `[IssueHandler]`
- inherits: `IssueHandler`
- desc: World Leak error issue handler
- L17 _private* field_ `static readonly Utf8String s_objectFlagsAnnotation = new("ObjectFlags")`
- L18 _private* field_ `static readonly Utf8String s_objectTextAnnotation = new("ObjectText")`
- L19 _private* field_ `static readonly Utf8String s_lingeringReferenceAnnotation = new("LingeringReference")`
- L20 _private* field_ `readonly List<IssueEventGroup> _issues = []`
- L23 _public property_ `public override int Priority => ...` — (inheritdoc)
- L27 _public property_ `public static LogValue LingeringReference => ...` — Log value describing the object reference preventing garbage collection
- L32 _public property_ `public static LogValue ObjectFlags => ...` — Log value describing the flag on an object in the leak reference chain
- L37 _public property_ `public static LogValue ObjectText => ...` — Log value describing an object in the leak reference chain
- L39-51 _private* method_ `static bool FindAnnotation(IssueEvent issueEvent, Utf8String annotation, ref string result)`
- L54-83 _public method_ `public override bool HandleEvent(IssueEvent issueEvent)` — (inheritdoc)
- L86 _public method_ `public override IEnumerable<IssueEventGroup> GetIssues()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/IIssueFingerprint.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Issues.IIssueFingerprint`  
`public interface IIssueFingerprint`  
_public; L12-43_
- desc: Fingerprint for an issue
- L17 _public property_ `public string Type { get; }` — The type of issue, which defines the handler to use for it
- L22 _public property_ `public string SummaryTemplate { get; }` — Template string for the issue summary
- L27 _public property_ `public IReadOnlySet<IssueKey> Keys { get; }` — List of keys which identify this issue.
- L32 _public property_ `public IReadOnlySet<IssueKey>? RejectKeys { get; }` — Set of keys which should trigger a negative match
- L37 _public property_ `public IReadOnlySet<IssueMetadata>? Metadata { get; }` — Collection of additional metadata added by the handler
- L42 _public property_ `public string ChangeFilter { get; }` — Filter for changes that should be included in this issue

#### class `EpicGames.Horde.Issues.IssueFingerprintExtensions`  
`public static class IssueFingerprintExtensions`  
_public; L48-105_
- desc: Extension methods for IIssueFingerprint
- L56-85 _public method_ `public static bool IsMatch(this IIssueFingerprint fingerprint, IIssueFingerprint other)` — Checks if a fingerprint matches another fingerprint
- L93-104 _public method_ `public static bool IsMatchForNewSpan(this IIssueFingerprint fingerprint, IIssueFingerprint other)` — Checks if a fingerprint matches another fingerprint for creating a new span

### `Source/Programs/Shared/EpicGames.Horde/Issues/IWorkflow.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Issues.IWorkflow`  
`public interface IWorkflow`  
_public; L12-148_
- desc: Configuration for an issue workflow
- L17 _public* property_ `WorkflowId Id { get; }` — Identifier for this workflow
- L22 _public* property_ `IReadOnlyList<TimeSpan> ReportTimes { get; }` — Times of day at which to send a report
- L27 _public* property_ `string? SummaryTab { get; }` — Name of the tab to post summary data to
- L32 _public* property_ `string? ReportChannel { get; }` — Channel to post summary information for these templates.
- L37 _public* property_ `bool ReportWarnings { get; }` — Whether to include issues with a warning status in the summary
- L42 _public* property_ `bool GroupIssuesByTemplate { get; }` — Whether to group issues by template in the report
- L47 _public* property_ `string? TriageChannel { get; }` — Channel to post threads for triaging new issues
- L52 _public* property_ `string? TriagePrefix { get; }` — Prefix for all triage messages
- L57 _public* property_ `string? TriageSuffix { get; }` — Suffix for all triage messages
- L62 _public* property_ `string? TriageInstructions { get; }` — Instructions posted to triage threads
- L67 _public* property_ `string? TriageAlias { get; }` — User id of a Slack user/alias to ping if there is nobody assigned to an issue by default.
- L72 _public* property_ `bool TriageErrors { get; }` — Whether to include issues with an error status in the triage
- L77 _public* property_ `bool TriageWarnings { get; }` — Whether to include issues with a warning status in the triage
- L82 _public* property_ `IReadOnlyDictionary<string, string>? TriageTypeAliases { get; }` — Slack user/alias to ping for specific issue types (such as Systemic), if there is nobody assigned to an issue by default.
- L87 _public* property_ `string? EscalateAlias { get; }` — Alias to ping if an issue has not been resolved for a certain amount of time
- L92 _public* property_ `IReadOnlyList<int> EscalateTimes { get; }` — Times after an issue has been opened to escalate to the alias above, in minutes. Continues to notify on the last interval once reaching the end of the list.
- L97 _public* property_ `IReadOnlyList<int> EscalateRootCauseAnalysisTimes { get; }` — Times after a manual root cause analysis has been opened to escalate to the owner, in minutes. Continues to notify on the last interval once reaching the end of the list.
- L102 _public* property_ `bool AutoRcaEnabled { get; }` — Whether to automatically run RCA processing for issues in this workflow
- L107 _public* property_ `bool AutoRcaSlackEnabled { get; }` — Whether to post auto-RCA results to the issue's Slack triage thread
- L112 _public* property_ `int MaxMentions { get; }` — Maximum number of people to mention on a triage thread
- L117 _public* property_ `bool AllowMentions { get; }` — Whether to mention people on this thread. Useful to disable for testing.
- L122 _public* property_ `bool InviteRestrictedUsers { get; }` — Uses the admin.conversations.invite API to invite users to the channel
- L127 _public* property_ `bool SkipWhenEmpty { get; }` — Skips sending reports when there are no active issues.
- L132 _public* property_ `bool ShowMergeWarnings { get; }` — Whether to show warnings about merging changes into the origin stream.
- L137 _public* property_ `IReadOnlyNodeAnnotations Annotations { get; }` — Additional node annotations implicit in this workflow
- L142 _public* property_ `IWorkflowExternalIssues? ExternalIssues { get; }` — External issue tracking configuration for this workflow
- L147 _public* property_ `IReadOnlyList<string>? IssueHandlers { get; }` — Additional issue handlers enabled for this workflow

#### interface `EpicGames.Horde.Issues.IWorkflowExternalIssues`  
`public interface IWorkflowExternalIssues`  
_public; L153-169_
- desc: External issue tracking configuration for a workflow
- L158 _public* property_ `string ProjectKey { get; }` — Project key in external issue tracker
- L163 _public* property_ `string DefaultComponentId { get; }` — Default component id for issues using workflow
- L168 _public* property_ `string DefaultIssueTypeId { get; }` — Default issue type id for issues using workflow

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueChangeFilter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueChangeFilter`  
`public static class IssueChangeFilter`  
_public; L10-57_
- desc: Set of rules for filtering the list of suspects for an issue
- L15 _public property_ `public static IReadOnlyList<string> None { get; }` — Filter exclude all changes
- L20 _public property_ `public static IReadOnlyList<string> All { get; }` — Filter including all changes
- L25 _public property_ `public static IReadOnlyList<string> Code { get; }` — Set of extensions to treat as code
- L51 _public property_ `public static IReadOnlyList<string> Content { get; }` — Set of file extensions to treat as content

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueEvent.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueEvent`  
`public class IssueEvent`  
_public; L14-60_
- desc: Wraps a log event and allows it to be tagged by issue handlers
- L19 _public property_ `public int LineIndex { get; }` — Index of the line within this log
- L24 _public property_ `public LogLevel Severity { get; }` — Severity of the event
- L29 _public property_ `public EventId? EventId { get; }` — The type of event
- L34 _public property_ `public IReadOnlyList<JsonLogEvent> Lines { get; }` — Gets this event data as a BSON document
- L39 _public property_ `public IssueAuditLogger? AuditLogger { get; set; }` — IssueAuditLogger attached to this event
- L44-50 _public ctor_ `public IssueEvent(int lineIndex, LogLevel severity, EventId? eventId, IReadOnlyList<JsonLogEvent> lines)` — Constructor
- L55 _public method_ `public string Render()` — Renders the entire message of this event
- L59 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Issues.IssueEventGroup`  
`public class IssueEventGroup`  
_public; L65-120_
- desc: A group of IssueEvent objects with their fingerprint
- L70 _public property_ `public string Type { get; set; }` — The type of issue, which defines the handler to use for it
- L75 _public property_ `public string SummaryTemplate { get; set; }` — Template string for the issue summary
- L80 _public property_ `public HashSet<IssueKey> Keys { get; }` — List of keys which identify this issue.
- L85 _public property_ `public HashSet<IssueMetadata> Metadata { get; }` — Collection of additional metadata added by the handler
- L90 _public property_ `public string ChangeFilter { get; set; }` — Filter for changes that should be included in this issue
- L95 _public property_ `public List<IssueEvent> Events { get; }` — Individual log events
- L103-108 _public ctor_ `public IssueEventGroup(string type, string summaryTemplate, string changeFilter)` — Constructor
- L116-119 _public ctor_ `public IssueEventGroup(string type, string summaryTemplate, IReadOnlyList<string> changeFilter) : this(type, summaryTemplate, String.Join(";", changeFilter))` — Constructor

#### class `EpicGames.Horde.Issues.IssueAuditLogger`  
`public class IssueAuditLogger : ILogger`  
_public; L125-185_
- inherits: `ILogger`
- desc: Temporary log buffer to store information about an IssueEvent before it's assigned to a build health issue
- L128 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L131 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L133 _private field_ `private readonly List<IssueAuditLogEntry> _entries`
- L138-141 _public ctor_ `public IssueAuditLogger()` — Constructor
- L147-150 _public method_ `public List<IssueAuditLogEntry> GetEntries()` — Gets list of IssueAuditLogEntry objects in the buffer
- L161-184 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — Stores a IssueAuditLogEntry in the log buffer

#### struct `EpicGames.Horde.Issues.IssueAuditLogEntry`  
`public readonly struct IssueAuditLogEntry(LogLevel logLevel, string messageTemplate, object[]? args) : IEquatable<IssueAuditLogEntry>`  
_public; L193-310_
- desc: Buffered log entry stored in a IssueAuditLogger
- L198 _private field_ `private readonly LogLevel _logLevel = logLevel` — Severity level at which to log the entry
- L203 _private field_ `private readonly string _messageTemplate = messageTemplate` — Message template for structured log entry
- L208 _private field_ `private readonly object[]? _args = args` — Arguments to be injected in the message template of the entry
- L213-216 _public method_ `public readonly LogLevel GetLogLevel()` — Log level accessor
- L221-224 _public method_ `public readonly string? GetMessageTemplate()` — Message template accessor
- L229-232 _public method_ `public readonly object[]? GetArgs()` — Args accessor
- L239-279 _public method_ `public readonly bool Equals(IssueAuditLogEntry otherEntry)` — Compares against another IssueAuditLogEntry object for equality
- L284-287 _public method_ `public override readonly int GetHashCode()` — Returns the underlying value hashcode
- L290-293 _public method_ `public override readonly bool Equals(object? obj)` — (inheritdoc)
- L298-301 _public operator_ `public static bool operator ==(IssueAuditLogEntry left, IssueAuditLogEntry right)` — Compares two IssueAuditLogEntry objects for equality
- L306-309 _public operator_ `public static bool operator !=(IssueAuditLogEntry left, IssueAuditLogEntry right)` — Compares two IssueAuditLogEntry objects for inequality

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueExtensions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueExtensions`  
`public static class IssueExtensions`  
_public; L13-36_
- desc: Extension methods for logging issue data
- L20 _public method_ `public static void AddIssueFingerprint(this LogEvent logEvent, IssueFingerprint fingerprint)` — Adds an issue fingerprint to a log event
- L29-35 _public method_ `public static IDisposable? BeginIssueScope(this ILogger logger, IssueFingerprint fingerprint)` — Enters a scope which annotates log messages with the supplied issue fingerprint

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueFingerprint.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueFingerprint`  
`public class IssueFingerprint : IIssueFingerprint`  
_public; L14-92_
- inherits: `IIssueFingerprint`
- desc: Fingerprint for an issue. Can be embedded into a structured log event under the "$issue" property to guide how Horde should group the event.
- L20 _public property_ `public string Type { get; set; }` — attrs: `[JsonPropertyName("type")]` — The type of issue, which defines the handler to use for it
- L26 _public property_ `public string SummaryTemplate { get; set; }` — attrs: `[JsonPropertyName("summary")]` — Template string for the issue summary
- L32 _public property_ `public HashSet<IssueKey> Keys { get; set; }` — attrs: `[JsonIgnore]` — List of keys which identify this issue.
- L33 _private* property_ `IReadOnlySet<IssueKey> IIssueFingerprint.Keys => ...`
- L39 _public property_ `public HashSet<IssueKey>? RejectKeys { get; set; }` — attrs: `[JsonPropertyName("rejectKeys")]` — Set of keys which should trigger a negative match
- L40 _private* property_ `IReadOnlySet<IssueKey>? IIssueFingerprint.RejectKeys => ...`
- L46 _public property_ `public HashSet<IssueMetadata> Metadata { get; set; }` — attrs: `[JsonIgnore]` — Collection of additional metadata added by the handler
- L47 _private* property_ `IReadOnlySet<IssueMetadata> IIssueFingerprint.Metadata => ...`
- L53 _public property_ `public string ChangeFilter { get; set; }` — attrs: `[JsonPropertyName("filter")]` — Filter for changes that touch files which should be included in this issue
- L60-64 _public property_ `public HashSet<IssueKey>? SerializedKeys { get; set; }` — attrs: `[JsonPropertyName("keys")] [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]` — Keys set which is null when empty
- L71-75 _public property_ `public HashSet<IssueMetadata>? SerializedMetadata { get; set; }` — attrs: `[JsonPropertyName("meta")] [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]` — Metadata set which is null when empty
- L80-82 _public ctor_ `public IssueFingerprint()` — Default constructor
- L87-91 _public ctor_ `public IssueFingerprint(string type, string summaryTemplate)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueHandler.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueHandlerAttribute`  
`public sealed class IssueHandlerAttribute : Attribute`  
_public; L14-20_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Marks an issue handler that should be automatically inserted into the pipeline
- L19 _public property_ `public string? Tag { get; set; }` — Class of handler which can be explicitly enabled via a workflow

#### class `EpicGames.Horde.Issues.IssueHandler`  
`public abstract class IssueHandler`  
_public; L25-44_
- desc: Interface for issue matchers
- L30 _public property_ `public abstract int Priority { get; }` — Priority value for this issue handler. Handlers are processed in order of decreasing priority.
- L37 _public method_ `public abstract bool HandleEvent(IssueEvent issueEvent)` — Attempts to assign a log event to an issue
- L43 _public method_ `public abstract IEnumerable<IssueEventGroup> GetIssues()` — Gets all the issues created by this handler

#### class `EpicGames.Horde.Issues.IssueHandlerContext`  
`public class IssueHandlerContext`  
_public; L49-87_
- desc: Context object for issue handlers
- L54 _public property_ `public StreamId StreamId { get; }` — Identifier for the current stream
- L59 _public property_ `public TemplateId TemplateId { get; }` — Identififer of the template
- L64 _public property_ `public string NodeName { get; }` — Identifier for the current node name
- L69 _public property_ `public IReadOnlyDictionary<string, string> ChannelGroups { get; }` — Log Channel => Channel Grouping
- L74 _public property_ `public IReadOnlyDictionary<string, string> NodeAnnotations { get; }` — Annotations for this node
- L79-86 _public ctor_ `public IssueHandlerContext(StreamId streamId, TemplateId templateId, string nodeName, IReadOnlyDictionary<string, string> channelGroups, IReadOnlyDictionary<string, string> nodeAnnotations)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueKey.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Issues.IssueKeyType`  
`public enum IssueKeyType`  
_public; L18-49_
- desc: Type of a key in an issue, used for grouping.
- L23 _public* enumerator_ `None` — Unknown type
- L28 _public* enumerator_ `File` — Filename
- L33 _public* enumerator_ `Note` — Secondary file
- L38 _public* enumerator_ `Symbol` — Name of a symbol
- L43 _public* enumerator_ `Hash` — Hash of a particular error
- L48 _public* enumerator_ `Step` — Identifier for a particular step

#### class `EpicGames.Horde.Issues.IssueKey`  
`public class IssueKey : IEquatable<IssueKey>`  
_public; L54-135_
- inherits: `IEquatable<IssueKey>`
- desc: Defines a key which can be used to group an issue with other issues
- L59 _public property_ `public string Name { get; }` — Name of the key
- L65 _public property_ `public IssueKeyType Type { get; }` — attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]` — Type of the key
- L71 _public property_ `public string? Scope { get; }` — attrs: `[JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]` — Arbitrary string that can be used to discriminate between otherwise identical keys, limiting the issues that it can merge with.
- L76-80 _public ctor_ `public IssueKey(string name, IssueKeyType type)` — Constructor
- L86-91 _public ctor_ `public IssueKey(string name, IssueKeyType type, string? scope = null)` — attrs: `[JsonConstructor]` — Constructor
- L96 _public method_ `public static IssueKey FromFile(string file, bool note = false)` — Creates an issue key for a file
- L101 _public method_ `public static IssueKey FromSymbol(string name)` — Creates an issue key for a file
- L106 _public method_ `public static IssueKey FromHash(Md5Hash hash)` — Creates an issue key for a particular hash
- L111 _public method_ `public static IssueKey FromStep(StreamId streamId, TemplateId templateId, string nodeName)` — Creates an issue key for a particular step
- L116 _public method_ `public static IssueKey FromStepAndSeverity(StreamId streamId, TemplateId templateId, string nodeName, LogLevel severity)` — Creates an issue key for a particular step and severity
- L119 _public method_ `public bool Equals(IssueKey? other)` — (inheritdoc)
- L122 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L125 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L128 _public method_ `public override string ToString()` — (inheritdoc)
- L131 _public operator_ `public static bool operator ==(IssueKey left, IssueKey right)` — (inheritdoc)
- L134 _public operator_ `public static bool operator !=(IssueKey left, IssueKey right)` — (inheritdoc)

#### class `EpicGames.Horde.Issues.IssueKeyExtensions`  
`public static class IssueKeyExtensions`  
_public; L140-274_
- desc: Extension methods for issue keys
- L145-148 _public method_ `public static void Add(this HashSet<IssueKey> entries, string name, IssueKeyType type, string? scope = null)` — Adds a new entry to a set
- L155-170 _public method_ `public static void AddAssets(this HashSet<IssueKey> keys, IssueEvent issueEvent)` — Adds all the assets from the given log event
- L177-189 _public method_ `public static void AddDepotPaths(this HashSet<IssueKey> keys, IssueEvent issueEvent)` — Extracts a list of source files from an event
- L197-200 _public method_ `public static void AddHash(this HashSet<IssueKey> keys, Md5Hash hash, string? scope = null)` — Extracts a list of source files from an event
- L208-236 _public method_ `public static void AddSourceFiles(this HashSet<IssueKey> keys, IssueEvent issueEvent, string? scope = null)` — Extracts a list of source files from an event
- L245-253 _public method_ `public static void AddSourceFile(this HashSet<IssueKey> keys, string relativePath, IssueKeyType type, string? scope = null)` — Add a new source file to a list of unique source files
- L260-273 _public method_ `public static void AddSymbols(this HashSet<IssueKey> keys, IssueEvent eventData)` — Parses symbol names from a log event

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Issues.IssueSeverity`  
`public enum IssueSeverity`  
_public; L19-35_
- desc: The severity of an issue
- L24 _public* enumerator_ `Unspecified` — Unspecified severity
- L29 _public* enumerator_ `Warning` — This error represents a warning
- L34 _public* enumerator_ `Error` — This issue represents an error

#### class `EpicGames.Horde.Issues.GetIssueStepResponse`  
`public class GetIssueStepResponse`  
_public; L40-97_
- desc: Identifies a particular changelist and job
- L46-50 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use Commit instead")]` — The changelist number
- L51 _private* field_ `int? _change`
- L56-60 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — The commit for this step
- L61 _private* field_ `CommitIdWithOrder? _commitId`
- L66 _public property_ `public IssueSeverity Severity { get; set; }` — Severity of the issue in this step
- L71 _public property_ `public string JobName { get; set; }` — Name of the job containing this step
- L76 _public property_ `public JobId JobId { get; set; }` — The unique job id
- L81 _public property_ `public JobStepBatchId BatchId { get; set; }` — The unique batch id
- L86 _public property_ `public JobStepId StepId { get; set; }` — The unique step id
- L91 _public property_ `public DateTime StepTime { get; set; }` — Time at which the step ran
- L96 _public property_ `public LogId? LogId { get; set; }` — The unique log id

#### class `EpicGames.Horde.Issues.GetIssueSpanResponse`  
`public class GetIssueSpanResponse`  
_public; L102-138_
- desc: Trace of a set of node failures across multiple steps
- L107 _public property_ `public string Id { get; set; }` — Unique id of this span
- L112 _public property_ `public TemplateId TemplateId { get; set; }` — The template containing this step
- L117 _public property_ `public string Name { get; set; }` — Name of the step
- L122 _public property_ `public WorkflowId? WorkflowId { get; set; }` — Workflow that this span belongs to
- L127 _public property_ `public GetIssueStepResponse? LastSuccess { get; set; }` — The previous build
- L132 _public property_ `public List<GetIssueStepResponse> Steps { get; set; }` — The failing builds for a particular event
- L137 _public property_ `public GetIssueStepResponse? NextSuccess { get; set; }` — The following successful build

#### class `EpicGames.Horde.Issues.GetIssueStreamResponse`  
`public class GetIssueStreamResponse`  
_public; L143-196_
- desc: Information about a particular step
- L148 _public property_ `public StreamId StreamId { get; set; }` — Unique id of the stream
- L154-158 _public property_ `public int? MinChange { get; set; }` — attrs: `[Obsolete("Use MinCommitId instead")]` — Minimum commit affected by this issue (ie. last successful build)
- L159 _private* field_ `int? _minChange`
- L165-169 _public property_ `public int? MaxChange { get; set; }` — attrs: `[Obsolete("Use MaxCommitId instead")]` — Maximum commit affected by this issue (ie. next successful build)
- L170 _private* field_ `int? _maxChange`
- L175-179 _public property_ `public CommitIdWithOrder? MinCommitId { get; set; }` — Minimum changelist affected by this issue (ie. last successful build)
- L180 _private* field_ `CommitIdWithOrder? _minCommitId`
- L185-189 _public property_ `public CommitIdWithOrder? MaxCommitId { get; set; }` — Maximum changelist affected by this issue (ie. next successful build)
- L190 _private* field_ `CommitIdWithOrder? _maxCommitId`
- L195 _public property_ `public List<GetIssueSpanResponse> Nodes { get; set; }` — Map of steps to (event signature id -> trace id)

#### enum `EpicGames.Horde.Issues.IssueBuildOutcome`  
`public enum IssueBuildOutcome`  
_public; L201-222_
- desc: Outcome of a particular build
- L206 _public* enumerator_ `Unknown` — Unknown outcome
- L211 _public* enumerator_ `Success` — Build succeeded
- L216 _public* enumerator_ `Error` — Build failed
- L221 _public* enumerator_ `Warning` — Build finished with warnings

#### class `EpicGames.Horde.Issues.GetIssueAffectedTemplateResponse`  
`public class GetIssueAffectedTemplateResponse`  
_public; L227-248_
- desc: Information about a template affected by an issue
- L232 _public property_ `public TemplateId TemplateId { get; set; }` — The template id
- L237 _public property_ `public string TemplateName { get; set; }` — The template name
- L242 _public property_ `public bool Resolved { get; set; }` — Whether it has been resolved or not
- L247 _public property_ `public IssueSeverity Severity { get; set; }` — The issue severity of the affected template

#### class `EpicGames.Horde.Issues.GetIssueAffectedStreamResponse`  
`public class GetIssueAffectedStreamResponse`  
_public; L253-289_
- desc: Summary for the state of a stream in an issue
- L258 _public property_ `public StreamId StreamId { get; set; }` — Id of the stream
- L263 _public property_ `public string StreamName { get; set; }` — Name of the stream
- L268 _public property_ `public bool Resolved { get; set; }` — Whether the issue has been resolved in this stream
- L273 _public property_ `public List<GetIssueAffectedTemplateResponse> AffectedTemplates { get; set; }` — The affected templates
- L278 _public property_ `public List<string> TemplateIds { get; set; }` — List of affected template ids
- L283 _public property_ `public List<string> ResolvedTemplateIds { get; set; }` — List of resolved template ids
- L288 _public property_ `public List<string> UnresolvedTemplateIds { get; set; }` — List of unresolved template ids

#### class `EpicGames.Horde.Issues.GetIssueResponse`  
`public class GetIssueResponse`  
_public; L294-525_
- desc: Stores information about a build health issue
- L299 _public property_ `public int Id { get; set; }` — The unique object id
- L304 _public property_ `public DateTime CreatedAt { get; set; }` — Time at which the issue was created
- L309 _public property_ `public DateTime RetrievedAt { get; set; }` — Time at which the issue was retrieved
- L314 _public property_ `public string? Project { get; set; }` — The associated project for the issue
- L319 _public property_ `public string Summary { get; set; }` — The summary text for this issue
- L324 _public property_ `public string? Description { get; set; }` — Detailed description text
- L329 _public property_ `public string? FingerprintDescription { get; set; }` — Description of the current fingerprint used for issue identification
- L334 _public property_ `public IssueSeverity Severity { get; set; }` — Severity of this issue
- L339 _public property_ `public bool Promoted { get; set; }` — Whether the issue is promoted
- L344 _public property_ `public string? Owner { get; set; }` — Owner of the issue [DEPRECATED]
- L349 _public property_ `public string? OwnerId { get; set; }` — User id of the owner [DEPRECATED]
- L354 _public property_ `public GetThinUserInfoResponse? OwnerInfo { get; set; }` — Owner of the issue
- L359 _public property_ `public string? NominatedBy { get; set; }` — User that nominated the current owner [DEPRECATED]
- L364 _public property_ `public GetThinUserInfoResponse? NominatedByInfo { get; set; }` — Owner of the issue
- L369 _public property_ `public DateTime? AcknowledgedAt { get; set; }` — Time that the issue was acknowledged
- L374-378 _public property_ `public int? FixChange { get; set; }` — Perforce changelist that fixed this issue
- L379 _private* field_ `int? _fixChange`
- L384-388 _public property_ `public CommitId? FixCommitId { get; set; }` — Commit that fixed this issue
- L389 _private* field_ `CommitId? _fixCommitId`
- L394-398 _public property_ `public bool FixSystemic { get; set; }` — Whether the issue is marked fixed as a systemic issue
- L399 _private* field_ `bool? _fixSystemic`
- L404-408 _public property_ `public CommitId? RootCommitId { get; set; }` — Commit that introduced this issue
- L409 _private* field_ `CommitId? _rootCommitId`
- L414 _public property_ `public GetThinUserInfoResponse? RootCauseOwnerInfo { get; set; }` — User that provided the root cause analysis
- L419 _public property_ `public string? RootCauseCategory { get; set; }` — Root Cause Category for this issue
- L424 _public property_ `public string? RootCauseSummary { get; set; }` — Root Cause Summary for this issue
- L429 _public property_ `public int? DuplicateIssueId { get; set; }` — Duplicate issue id
- L434 _public property_ `public DateTime? ResolvedAt { get; set; }` — Time at which the issue was resolved
- L439 _public property_ `public string? ResolvedBy { get; set; }` — Name of the user that resolved the issue [DEPRECATED]
- L444 _public property_ `public string? ResolvedById { get; set; }` — User id of the person that resolved the issue [DEPRECATED]
- L449 _public property_ `public GetThinUserInfoResponse? ResolvedByInfo { get; set; }` — User that resolved the issue
- L454 _public property_ `public DateTime? VerifiedAt { get; set; }` — Time at which the issue was verified
- L459 _public property_ `public DateTime LastSeenAt { get; set; }` — Time that the issue was last seen
- L464 _public property_ `public List<string> Streams { get; set; }` — List of stream paths affected by this issue
- L469 _public property_ `public List<string> ResolvedStreams { get; set; }` — List of affected stream ids
- L474 _public property_ `public List<string> UnresolvedStreams { get; set; }` — List of unresolved streams
- L479 _public property_ `public List<GetIssueAffectedStreamResponse> AffectedStreams { get; set; }` — List of affected streams
- L484 _public property_ `public List<string>? PrimarySuspects { get; set; }` — Most likely suspects for causing this issue [DEPRECATED]
- L489 _public property_ `public List<string>? PrimarySuspectIds { get; set; }` — User ids of the most likely suspects [DEPRECATED]
- L494 _public property_ `public List<GetThinUserInfoResponse> PrimarySuspectsInfo { get; set; }` — Most likely suspects for causing this issue
- L499 _public property_ `public bool ShowDesktopAlerts { get; set; }` — Whether to show alerts for this issue
- L504 _public property_ `public string? ExternalIssueKey { get; set; }` — Key for this issue in external issue tracker
- L509 _public property_ `public GetThinUserInfoResponse? QuarantinedByUserInfo { get; set; }` — User who quarantined the issue
- L514 _public property_ `public DateTime? QuarantineTimeUtc { get; set; }` — The UTC time when the issue was quarantined
- L519 _public property_ `public GetThinUserInfoResponse? ForceClosedByUserInfo { get; set; }` — User who force closed the issue
- L524 _public property_ `public Uri? WorkflowThreadUrl { get; set; }` — The workflow thread url for this issue

#### class `EpicGames.Horde.Issues.FindIssueSpanResponse`  
`public class FindIssueSpanResponse`  
_public; L530-561_
- desc: Information about a span within an issue
- L535 _public property_ `public string Id { get; set; }` — Unique id of this span
- L540 _public property_ `public string TemplateId { get; set; }` — The template containing this step
- L545 _public property_ `public string Name { get; set; }` — Name of the step
- L550 _public property_ `public WorkflowId? WorkflowId { get; set; }` — Workflow for this span
- L555 _public property_ `public GetIssueStepResponse? LastSuccess { get; set; }` — The previous build
- L560 _public property_ `public GetIssueStepResponse? NextSuccess { get; set; }` — The following successful build

#### class `EpicGames.Horde.Issues.FindIssueResponse`  
`public class FindIssueResponse`  
_public; L566-737_
- desc: Stores information about a build health issue
- L571 _public property_ `public int Id { get; set; }` — The unique object id
- L576 _public property_ `public DateTime CreatedAt { get; set; }` — Time at which the issue was created
- L581 _public property_ `public DateTime RetrievedAt { get; set; }` — Time at which the issue was retrieved
- L586 _public property_ `public string? Project { get; set; }` — The associated project for the issue
- L591 _public property_ `public string Summary { get; set; }` — The summary text for this issue
- L596 _public property_ `public string? Description { get; set; }` — Detailed description text
- L601 _public property_ `public IssueSeverity Severity { get; set; }` — Severity of this issue
- L606 _public property_ `public IssueSeverity? StreamSeverity { get; set; }` — Severity of this issue in the stream
- L611 _public property_ `public bool Promoted { get; set; }` — Whether the issue is promoted
- L616 _public property_ `public GetThinUserInfoResponse? Owner { get; set; }` — Owner of the issue
- L621 _public property_ `public GetThinUserInfoResponse? NominatedBy { get; set; }` — Owner of the issue
- L626 _public property_ `public DateTime? AcknowledgedAt { get; set; }` — Time that the issue was acknowledged
- L631-635 _public property_ `public int? FixChange { get; set; }` — Changelist that fixed this issue
- L636 _private* field_ `int? _fixChange`
- L641-645 _public property_ `public CommitId? FixCommitId { get; set; }` — Changelist that fixed this issue
- L646 _private* field_ `CommitId? _fixCommitId`
- L651 _public property_ `public GetThinUserInfoResponse? RootCauseOwner { get; set; }` — User that provided the root cause analysis
- L656 _public property_ `public string? RootCauseCategory { get; set; }` — Root Cause Category for this issue
- L661 _public property_ `public string? RootCauseSummary { get; set; }` — Root Cause Summary for this issue
- L666 _public property_ `public int? DuplicateIssueId { get; set; }` — Duplcate issue id
- L671-675 _public property_ `public bool FixSystemic { get; set; }` — Whether the issue is marked fixed as a systemic issue
- L676 _private* field_ `bool? _fixSystemic`
- L681-685 _public property_ `public CommitId? RootCommitId { get; set; }` — Changelist that introduced this issue
- L686 _private* field_ `CommitId? _rootCommitId`
- L691 _public property_ `public DateTime? ResolvedAt { get; set; }` — Time at which the issue was resolved
- L696 _public property_ `public GetThinUserInfoResponse? ResolvedBy { get; set; }` — User that resolved the issue
- L701 _public property_ `public DateTime? VerifiedAt { get; set; }` — Time at which the issue was verified
- L706 _public property_ `public DateTime LastSeenAt { get; set; }` — Time that the issue was last seen
- L711 _public property_ `public List<FindIssueSpanResponse>? Spans { get; set; }` — Spans for this issue
- L716 _public property_ `public string? ExternalIssueKey { get; set; }` — Key for this issue in external issue tracker
- L721 _public property_ `public GetThinUserInfoResponse? QuarantinedBy { get; set; }` — User who quarantined the issue
- L726 _public property_ `public DateTime? QuarantineTimeUtc { get; set; }` — The UTC time when the issue was quarantined
- L731 _public property_ `public Uri? WorkflowThreadUrl { get; set; }` — The workflow thread url for this issue
- L736 _public property_ `public List<WorkflowId>? OpenWorkflows { get; set; }` — Workflows for which this issue is open

#### class `EpicGames.Horde.Issues.UpdateIssueRequest`  
`public class UpdateIssueRequest`  
_public; L742-869_
- desc: Request an issue to be updated
- L747 _public property_ `public string? Summary { get; set; }` — Summary of the issue
- L752 _public property_ `public string? Description { get; set; }` — Description of the issue
- L757 _public property_ `public bool? Promoted { get; set; }` — Whether the issue is promoted or not
- L762 _public property_ `public string? OwnerId { get; set; }` — New user id for owner of the issue, can be cleared by passing empty string
- L767 _public property_ `public string? NominatedById { get; set; }` — User id that nominated the new owner
- L772 _public property_ `public bool? Acknowledged { get; set; }` — Whether the issue has been acknowledged
- L777 _public property_ `public bool? Declined { get; set; }` — Whether the user has declined this issue
- L783-787 _public property_ `public int? FixChange { get; set; }` — attrs: `[Obsolete("Use FixCommitId and FixSystemic instead")]` — The change at which the issue is claimed fixed. 0 = not fixed, -1 = systemic issue.
- L788 _private* field_ `int? _fixChange`
- L793-797 _public property_ `public CommitId? FixCommitId { get; set; }` — The change at which the issue is claimed fixed. """" = not fixed.
- L798 _private* field_ `CommitId? _fixCommitId`
- L803-807 _public property_ `public bool FixSystemic { get; set; }` — Set to mark the issue as fixed systemically
- L808 _private* field_ `bool? _fixSystemic`
- L813-817 _public property_ `public CommitId? RootCommitId { get; set; }` — The change at which the issue is claimed to have been introduced.
- L818 _private* field_ `CommitId? _rootCommitId`
- L823 _public property_ `public string? RootCauseOwnerId { get; set; }` — New user id for owner of the root cause analysis, can be cleared by passing empty string
- L828 _public property_ `public string? RootCauseCategory { get; set; }` — Root Cause Category for this issue
- L833 _public property_ `public string? RootCauseSummary { get; set; }` — Root Cause Summary for this issue
- L838 _public property_ `public int? DuplicateIssueId { get; set; }` — Duplicate Issue Id
- L843 _public property_ `public bool? Resolved { get; set; }` — Whether the issue should be marked as resolved
- L848 _public property_ `public List<string>? AddSpans { get; set; }` — List of spans to add to this issue
- L853 _public property_ `public List<string>? RemoveSpans { get; set; }` — List of spans to remove from this issue
- L858 _public property_ `public string? ExternalIssueKey { get; set; }` — A key to issue in external tracker
- L863 _public property_ `public string? QuarantinedById { get; set; }` — Id of user quarantining issue
- L868 _public property_ `public string? ForceClosedById { get; set; }` — Id of user who is forcibly closing this issue, skipping verification checks. This is useful for when a failing step has been removed for example

#### class `EpicGames.Horde.Issues.GetExternalIssueProjectResponse`  
`public class GetExternalIssueProjectResponse`  
_public; L874-900_
- desc: External issue project information
- L879 _public property_ `public string ProjectKey { get; set; }` — The project key
- L884 _public property_ `public string Name { get; set; }` — The name of the project
- L889 _public property_ `public string Id { get; set; }` — The id of the project
- L894 _public property_ `public Dictionary<string, string> Components { get; set; }` — component id => name
- L899 _public property_ `public Dictionary<string, string> IssueTypes { get; set; }` — IssueType id => name

#### class `EpicGames.Horde.Issues.MarkFixedViaPerforceRequest`  
`public class MarkFixedViaPerforceRequest`  
_public; L905-916_
- desc: Marks an issue as fixed by another user. Designed for use from a Perforce trigger.
- L910 _public property_ `public string UserName { get; set; }` — Name of the user that fixed the issue
- L915 _public property_ `public int FixChange { get; set; }` — Change that fixed the issue

#### class `EpicGames.Horde.Issues.CreateExternalIssueRequest`  
`public class CreateExternalIssueRequest`  
_public; L921-962_
- desc: Request an issue to be created on external issue tracking system
- L926 _public property_ `public int IssueId { get; set; }` — Horde issue which is linked to external issue
- L931 _public property_ `public string StreamId { get; set; }` — StreamId of a stream with this issue
- L936 _public property_ `public string Summary { get; set; }` — Summary text for external issue
- L941 _public property_ `public string ProjectId { get; set; }` — External issue project id
- L946 _public property_ `public string ComponentId { get; set; }` — External issue component id
- L951 _public property_ `public string IssueTypeId { get; set; }` — External issue type id
- L956 _public property_ `public string? Description { get; set; }` — Optional description text for external issue
- L961 _public property_ `public string? HordeIssueLink { get; set; }` — Optional link to issue on Horde

#### class `EpicGames.Horde.Issues.CreateExternalIssueResponse`  
`public class CreateExternalIssueResponse`  
_public; L967-989_
- desc: Response for externally created issue
- L972 _public property_ `public string Key { get; set; }` — External issue key
- L977 _public property_ `public string? Link { get; set; }` — Link to issue on external tracking site
- L984-988 _public ctor_ `public CreateExternalIssueResponse(string key, string? link)` — Constructor

#### class `EpicGames.Horde.Issues.GetExternalIssueResponse`  
`public class GetExternalIssueResponse`  
_public; L994-1035_
- desc: External issue response object
- L999 _public property_ `public string Key { get; set; }` — The external issue key
- L1004 _public property_ `public string? Link { get; set; }` — The issue link on external tracking site
- L1009 _public property_ `public string? StatusName { get; set; }` — The issue status name, "To Do", "In Progress", etc
- L1014 _public property_ `public string? ResolutionName { get; set; }` — The issue resolution name, "Fixed", "Closed", etc
- L1019 _public property_ `public string? PriorityName { get; set; }` — The issue priority name, "1 - Critical", "2 - Major", etc
- L1024 _public property_ `public string? AssigneeName { get; set; }` — The current assignee's user name
- L1029 _public property_ `public string? AssigneeDisplayName { get; set; }` — The current assignee's display name
- L1034 _public property_ `public string? AssigneeEmailAddress { get; set; }` — The current assignee's email address

### `Source/Programs/Shared/EpicGames.Horde/Issues/IssueMetadata.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.IssueMetadata`  
`public class IssueMetadata : IEquatable<IssueMetadata>`  
_public; L12-45_
- inherits: `IEquatable<IssueMetadata>`
- desc: Entry in an issue's metadata collection. Implemented as a case-insensitive key and value
- L17 _public property_ `public string Key { get; }` — Key for the metadata item
- L22 _public property_ `public string Value { get; }` — Value for the metadata
- L28-32 _public ctor_ `public IssueMetadata(string key, string value)` — attrs: `[JsonConstructor]` — Constructor
- L35 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L38 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L41 _public method_ `public bool Equals(IssueMetadata? entry)` — (inheritdoc)
- L44 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Issues.IssueMetadataEntryExtensions`  
`public static class IssueMetadataEntryExtensions`  
_public; L50-76_
- desc: Extension methods for IssueMetadata
- L55-58 _public method_ `public static void Add(this HashSet<IssueMetadata> entries, string key, string value)` — Adds a new entry to a set
- L66-75 _public method_ `public static IEnumerable<string> FindValues(this IReadOnlySet<IssueMetadata> entries, string key)` — Gets all the metadata values with a given key

### `Source/Programs/Shared/EpicGames.Horde/Issues/WorkflowId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Issues.WorkflowId`  
`public readonly record struct WorkflowId(StringId Id)`  
_public; L17-36_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<WorkflowId, WorkflowIdConverter>))] [StringIdConverter(typeof(WorkflowIdConverter))] [CbConverter(typeof(StringIdCbConverter<WorkflowId, WorkflowIdConverter>))]`
- desc: Identifier for a workflow
- L22 _public property_ `public static WorkflowId Empty { get; }` — Empty workflow id constant
- L27-29 _public ctor_ `public WorkflowId(string id) : this(new StringId(id))` — Constructor
- L32 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L35 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Issues.WorkflowIdConverter`  
`class WorkflowIdConverter : StringIdConverter<WorkflowId>`  
_internal*; L41-48_
- inherits: `StringIdConverter<WorkflowId>`
- desc: Converter to and from StringId instances.
- L44 _public method_ `public override WorkflowId FromStringId(StringId id)` — (inheritdoc)
- L47 _public method_ `public override StringId ToStringId(WorkflowId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Issues/WorkflowMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Issues.GetWorkflowResponse`  
`public class GetWorkflowResponse : IWorkflow`  
_public; L15-149_
- inherits: `IWorkflow`
- desc: Configuration for an issue workflow
- L18 _public property_ `public WorkflowId Id { get; set; }` — (inheritdoc)
- L21 _public property_ `public List<TimeSpan> ReportTimes { get; set; }` — (inheritdoc)
- L22 _private* property_ `IReadOnlyList<TimeSpan> IWorkflow.ReportTimes => ...`
- L25 _public property_ `public string? SummaryTab { get; set; }` — (inheritdoc)
- L28 _public property_ `public string? ReportChannel { get; set; }` — (inheritdoc)
- L31 _public property_ `public bool ReportWarnings { get; set; }` — (inheritdoc)
- L34 _public property_ `public bool GroupIssuesByTemplate { get; set; }` — (inheritdoc)
- L37 _public property_ `public string? TriageChannel { get; set; }` — (inheritdoc)
- L40 _public property_ `public string? TriagePrefix { get; set; }` — (inheritdoc)
- L43 _public property_ `public string? TriageSuffix { get; set; }` — (inheritdoc)
- L46 _public property_ `public string? TriageInstructions { get; set; }` — (inheritdoc)
- L49 _public property_ `public string? TriageAlias { get; set; }` — (inheritdoc)
- L52 _public property_ `public bool TriageErrors { get; set; }` — (inheritdoc)
- L55 _public property_ `public bool TriageWarnings { get; set; }` — (inheritdoc)
- L58 _public property_ `public Dictionary<string, string>? TriageTypeAliases { get; set; }` — (inheritdoc)
- L59 _private* property_ `IReadOnlyDictionary<string, string>? IWorkflow.TriageTypeAliases => ...`
- L62 _public property_ `public string? EscalateAlias { get; set; }` — (inheritdoc)
- L65 _public property_ `public List<int> EscalateTimes { get; set; }` — (inheritdoc)
- L66 _private* property_ `IReadOnlyList<int> IWorkflow.EscalateTimes => ...`
- L69 _public property_ `public List<int> EscalateRootCauseAnalysisTimes { get; set; }` — (inheritdoc)
- L71 _private* property_ `IReadOnlyList<int> IWorkflow.EscalateRootCauseAnalysisTimes => ...`
- L74 _public property_ `public bool AutoRcaEnabled { get; set; }` — (inheritdoc)
- L77 _public property_ `public bool AutoRcaSlackEnabled { get; set; }` — (inheritdoc)
- L80 _public property_ `public int MaxMentions { get; set; }` — (inheritdoc)
- L83 _public property_ `public bool AllowMentions { get; set; }` — (inheritdoc)
- L86 _public property_ `public bool InviteRestrictedUsers { get; set; }` — (inheritdoc)
- L89 _public property_ `public bool SkipWhenEmpty { get; set; }` — (inheritdoc)
- L92 _public property_ `public bool ShowMergeWarnings { get; set; }` — (inheritdoc)
- L95 _public property_ `public NodeAnnotations Annotations { get; set; }` — (inheritdoc)
- L96 _private* property_ `IReadOnlyNodeAnnotations IWorkflow.Annotations => ...`
- L99 _public property_ `public GetWorkflowExternalIssuesResponse? ExternalIssues { get; set; }` — (inheritdoc)
- L100 _private* property_ `IWorkflowExternalIssues? IWorkflow.ExternalIssues => ...`
- L103 _public property_ `public List<string>? IssueHandlers { get; set; }` — (inheritdoc)
- L104 _private* property_ `IReadOnlyList<string>? IWorkflow.IssueHandlers => ...`
- L109-114 _public ctor_ `public GetWorkflowResponse()` — Constructor
- L119-148 _public ctor_ `public GetWorkflowResponse(IWorkflow workflow)` — Constructor

#### class `EpicGames.Horde.Issues.GetWorkflowExternalIssuesResponse`  
`public class GetWorkflowExternalIssuesResponse : IWorkflowExternalIssues`  
_public; L154-184_
- inherits: `IWorkflowExternalIssues`
- desc: External issue tracking configuration for a workflow
- L157 _public property_ `public string ProjectKey { get; set; }` — (inheritdoc)
- L160 _public property_ `public string DefaultComponentId { get; set; }` — (inheritdoc)
- L163 _public property_ `public string DefaultIssueTypeId { get; set; }` — (inheritdoc)
- L168-173 _public ctor_ `public GetWorkflowExternalIssuesResponse()` — Constructor
- L178-183 _public ctor_ `public GetWorkflowExternalIssuesResponse(IWorkflowExternalIssues issues)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Bisect/BisectTaskId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.Bisect.BisectTaskId`  
`public readonly record struct BisectTaskId(BinaryId Id)`  
_public; L16-23_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<BisectTaskId, BisectTaskIdConverter>))] [BinaryIdConverter(typeof(BisectTaskIdConverter))]`
- desc: Identifier for a job
- L19 _public method_ `public static BisectTaskId Parse(string text)` — (inheritdoc)
- L22 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.Bisect.BisectTaskIdConverter`  
`class BisectTaskIdConverter : BinaryIdConverter<BisectTaskId>`  
_internal*; L28-35_
- inherits: `BinaryIdConverter<BisectTaskId>`
- desc: Converter to and from BinaryId instances.
- L31 _public method_ `public override BisectTaskId FromBinaryId(BinaryId id)` — (inheritdoc)
- L34 _public method_ `public override BinaryId ToBinaryId(BisectTaskId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Graphs/GraphMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Jobs.Graphs.GetNodeResponse`  
`public class GetNodeResponse`  
_public; L12-97_
- desc: Information required to create a node
- L17 _public property_ `public string Name { get; set; }` — The name of this node
- L22 _public property_ `public List<string> Inputs { get; set; }` — Inputs for this node
- L27 _public property_ `public List<string> OptionalInputs { get; set; }` — Optional inputs for this node
- L32 _public property_ `public List<string> Outputs { get; set; }` — Output from this node
- L37 _public property_ `public List<string> InputDependencies { get; set; }` — Indices of nodes which must have succeeded for this node to run
- L42 _public property_ `public List<string> OptionalInputDependencies { get; set; }` — Indices of nodes which may have succeeded for this node to run
- L47 _public property_ `public List<string> OrderDependencies { get; set; }` — Indices of nodes which must have completed for this node to run
- L52 _public property_ `public Priority Priority { get; set; }` — The priority of this node
- L57 _public property_ `public bool AllowRetry { get; set; }` — Whether this node can be retried
- L62 _public property_ `public bool RunEarly { get; set; }` — This node can start running early, before dependencies of other nodes in the same group are complete
- L67 _public property_ `public bool Warnings { get; set; }` — Whether to include warnings in diagnostic output
- L72 _public property_ `public float? AverageDuration { get; set; }` — Average time to execute this node based on historical trends
- L77 _public property_ `public IReadOnlyDictionary<string, string>? Credentials { get; set; }` — Credentials required for this node to run. This dictionary maps from environment variable names to a credential property in the format 'CredentialName.PropertyName'.
- L82 _public property_ `public IReadOnlyDictionary<string, string>? Properties { get; set; }` — Properties for this node
- L87 _public property_ `public IReadOnlyDictionary<string, string>? Annotations { get; set; }` — Annotations for this node
- L93-96 _public ctor_ `public GetNodeResponse(string name)` — Constructor

#### class `EpicGames.Horde.Jobs.Graphs.GetGroupResponse`  
`public class GetGroupResponse`  
_public; L102-121_
- desc: Information about a group of nodes
- L107 _public property_ `public string AgentType { get; set; }` — The type of agent to execute this group
- L112 _public property_ `public List<GetNodeResponse> Nodes { get; set; }` — Nodes in the group
- L117-120 _public ctor_ `public GetGroupResponse(string agentType)` — Constructor

#### class `EpicGames.Horde.Jobs.Graphs.GetAggregateResponse`  
`public class GetAggregateResponse`  
_public; L126-145_
- desc: Information about an aggregate
- L131 _public property_ `public string Name { get; set; }` — Name of the aggregate
- L136 _public property_ `public List<string> Nodes { get; set; }` — Nodes which must be part of the job for the aggregate to be shown
- L141-144 _public ctor_ `public GetAggregateResponse(string name)` — Constructor

#### class `EpicGames.Horde.Jobs.Graphs.GetLabelResponse`  
`public class GetLabelResponse`  
_public; L150-191_
- desc: Information about a label
- L155 _public property_ `public string? Category => ...` — Category of the aggregate
- L160 _public property_ `public string? Name => ...` — Label for this aggregate
- L165 _public property_ `public string? DashboardName { get; set; }` — Name to show for this label on the dashboard
- L170 _public property_ `public string? DashboardCategory { get; set; }` — Category to show this label in on the dashboard
- L175 _public property_ `public string? UgsName { get; set; }` — Name to show for this label in UGS
- L180 _public property_ `public string? UgsProject { get; set; }` — Project to display this label for in UGS
- L185 _public property_ `public List<string> RequiredNodes { get; set; }` — Nodes which must be part of the job for the aggregate to be shown
- L190 _public property_ `public List<string> IncludedNodes { get; set; }` — Nodes to include in the status of this aggregate, if present in the job

#### class `EpicGames.Horde.Jobs.Graphs.GetGraphResponse`  
`public class GetGraphResponse`  
_public; L196-225_
- desc: Information about a graph
- L201 _public property_ `public string Hash { get; set; }` — The hash of the graph
- L206 _public property_ `public List<GetGroupResponse>? Groups { get; set; }` — Array of nodes for this job
- L211 _public property_ `public List<GetAggregateResponse>? Aggregates { get; set; }` — List of aggregates
- L216 _public property_ `public List<GetLabelResponse>? Labels { get; set; }` — List of labels for the graph
- L221-224 _public ctor_ `public GetGraphResponse(string hash)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Graphs/IGraph.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Graphs.IGraph`  
`public interface IGraph`  
_public; L18-49_
- desc: A unique dependency graph instance
- L23 _public property_ `public ContentHash Id { get; }` — Hash of this graph
- L28 _public property_ `public int Schema { get; }` — Schema version for this document
- L33 _public property_ `public IReadOnlyList<INodeGroup> Groups { get; }` — List of groups for this graph
- L38 _public property_ `public IReadOnlyList<IAggregate> Aggregates { get; }` — List of aggregates for this graph
- L43 _public property_ `public IReadOnlyList<ILabel> Labels { get; }` — Status labels for this graph
- L48 _public property_ `public IReadOnlyList<IGraphArtifact> Artifacts { get; }` — Artifacts for this graph

#### class `EpicGames.Horde.Jobs.Graphs.GraphExtensions`  
`public static class GraphExtensions`  
_public; L54-161_
- desc: Extension methods for graphs
- L62-65 _public method_ `public static INode GetNode(this IGraph graph, NodeRef nodeRef)` — Gets the node from a node reference
- L74-92 _public method_ `public static bool TryFindNode(this IGraph graph, string nodeName, out NodeRef nodeRef)` — Tries to find a node by name
- L101-114 _public method_ `public static bool TryFindNode(this IGraph graph, string nodeName, [NotNullWhen(true)] out INode? node)` — Tries to find a node by name
- L123-127 _public method_ `public static bool TryFindAggregate(this IGraph graph, string name, out int aggregateIdx)` — Tries to find a node by name
- L136-149 _public method_ `public static bool TryFindAggregate(this IGraph graph, string name, [NotNullWhen(true)] out IAggregate? aggregate)` — Tries to find a node by name
- L157-160 _public method_ `public static IEnumerable<INode> GetDependencies(this IGraph graph, INode node)` — Gets a list of dependencies for the given node

#### interface `EpicGames.Horde.Jobs.Graphs.INode`  
`public interface INode`  
_public; L166-237_
- desc: Represents a node in the graph
- L171 _public property_ `public string Name { get; }` — The name of this node
- L176 _public property_ `public IReadOnlyList<NodeOutputRef> Inputs { get; }` — References to inputs for this node
- L181 _public property_ `public IReadOnlyList<NodeOutputRef> OptionalInputs { get; }` — References to optional inputs for this node
- L186 _public property_ `public IReadOnlyList<string> OutputNames { get; }` — List of output names
- L191 _public property_ `public NodeRef[] InputDependencies { get; }` — Indices of nodes which must have succeeded for this node to run
- L196 _public property_ `public NodeRef[] OptionalInputDependencies { get; }` — Indices of nodes which may have succeeded for this node to run
- L201 _public property_ `public NodeRef[] OrderDependencies { get; }` — Indices of nodes which must have completed for this node to run
- L206 _public property_ `public Priority Priority { get; }` — The priority that this node should be run at, within this job
- L211 _public property_ `public bool AllowRetry { get; }` — Whether this node can be run multiple times
- L216 _public property_ `public bool RunEarly { get; }` — This node can start running early, before dependencies of other nodes in the same group are complete
- L221 _public property_ `public bool Warnings { get; }` — Whether to include warnings in the output (defaults to true)
- L226 _public property_ `public IReadOnlyDictionary<string, string>? Credentials { get; }` — List of credentials required for this node. Each entry maps an environment variable name to a credential in the form "CredentialName.PropertyName".
- L231 _public property_ `public IReadOnlyDictionary<string, string>? Properties { get; }` — Properties for this node
- L236 _public property_ `public IReadOnlyNodeAnnotations Annotations { get; }` — Annotations for this node

#### interface `EpicGames.Horde.Jobs.Graphs.INodeGroup`  
`public interface INodeGroup`  
_public; L242-253_
- desc: Information about a sequence of nodes which can execute on a single agent
- L247 _public property_ `public string AgentType { get; }` — The type of agent to execute this group
- L252 _public property_ `public IReadOnlyList<INode> Nodes { get; }` — Nodes in this group

#### class `EpicGames.Horde.Jobs.Graphs.NodeRef`  
`public class NodeRef`  
_public; L259-313_
- attrs: `[DebuggerDisplay("Group: {GroupIdx}, Node: {NodeIdx}")]`
- desc: Reference to a node within another grup
- L264 _public property_ `public int GroupIdx { get; set; }` — The group index of the referenced node
- L269 _public property_ `public int NodeIdx { get; set; }` — The node index of the referenced node
- L274-278 _private ctor_ `private NodeRef()` — Private constructor for serialization
- L285-289 _public ctor_ `public NodeRef(int groupIdx, int nodeIdx)` — Constructor
- L292-296 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L299-302 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L309-312 _public method_ `public INode ToNode(IReadOnlyList<INodeGroup> groups)` — Converts this reference to a node name

#### class `EpicGames.Horde.Jobs.Graphs.NodeOutputRef`  
`public class NodeOutputRef`  
_public; L319-345_
- attrs: `[DebuggerDisplay("{NodeRef}, Output: {OutputIdx}")]`
- desc: Output from a node
- L324 _public property_ `public NodeRef NodeRef { get; set; }` — Node producing the output
- L329 _public property_ `public int OutputIdx { get; set; }` — Index of the output
- L334-338 _public ctor_ `public NodeOutputRef(NodeRef nodeRef, int outputIdx)` — Constructor
- L341 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L344 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### interface `EpicGames.Horde.Jobs.Graphs.IAggregate`  
`public interface IAggregate`  
_public; L350-361_
- desc: An collection of node references
- L355 _public property_ `public string Name { get; }` — Name of the aggregate
- L360 _public property_ `public IReadOnlyList<NodeRef> Nodes { get; }` — List of nodes for the aggregate to be valid

#### enum `EpicGames.Horde.Jobs.Graphs.LabelChange`  
`public enum LabelChange`  
_public; L366-377_
- desc: Change at which to display a label
- L371 _public* enumerator_ `Current = 0` — The current changelist
- L376 _public* enumerator_ `Code = 1` — The last code changelist

#### interface `EpicGames.Horde.Jobs.Graphs.ILabel`  
`public interface ILabel`  
_public; L382-418_
- desc: Label indicating the status of a set of nodes
- L387 _public property_ `public string? DashboardName { get; }` — Label to show in the dashboard. Null if does not need to be shown.
- L392 _public property_ `public string? DashboardCategory { get; }` — Category for the label. May be null.
- L397 _public property_ `public string? UgsName { get; }` — Name to display for this label in UGS
- L402 _public property_ `public string? UgsProject { get; }` — Project which this label applies to, for UGS
- L407 _public property_ `public LabelChange Change { get; }` — Which change to display the label on
- L412 _public property_ `public List<NodeRef> RequiredNodes { get; }` — List of required nodes for the aggregate to be valid
- L417 _public property_ `public List<NodeRef> IncludedNodes { get; }` — List of optional nodes to include in the aggregate state

#### class `EpicGames.Horde.Jobs.Graphs.LabelExtensions`  
`public static class LabelExtensions`  
_public; L423-442_
- desc: Extension methods for ILabel
- L431-441 _public method_ `public static IEnumerable<INode> GetDependencies(this ILabel label, IReadOnlyList<INodeGroup> groups)` — Enumerate all the required dependencies of this node group

#### interface `EpicGames.Horde.Jobs.Graphs.IGraphArtifact`  
`public interface IGraphArtifact`  
_public; L447-488_
- desc: Artifact produced by a graph
- L452 _public property_ `public ArtifactName Name { get; }` — Name of the artifact
- L457 _public property_ `public ArtifactType Type { get; }` — Type of the artifact
- L462 _public property_ `public string Description { get; }` — Description for the artifact
- L467 _public property_ `public string BasePath { get; }` — Base path for files in the artifact
- L472 _public property_ `public IReadOnlyList<string> Keys { get; }` — Keys for finding the artifact
- L477 _public property_ `public IReadOnlyList<string> Metadata { get; }` — Metadata for the artifact
- L482 _public property_ `public string? NodeName { get; }` — Name of the node producing this artifact
- L487 _public property_ `public string? OutputName { get; }` — Tag for the artifact files

#### class `EpicGames.Horde.Jobs.Graphs.NewNode`  
`public class NewNode`  
_public; L493-612_
- desc: Information required to create a node
- L498 _public property_ `public string Name { get; set; }` — The name of this node
- L503 _public property_ `public List<string>? Inputs { get; set; }` — Input names
- L508 _public property_ `public List<string>? OptionalInputs { get; set; }` — Optional input names
- L513 _public property_ `public List<string>? Outputs { get; set; }` — Output names
- L518 _public property_ `public List<string>? InputDependencies { get; set; }` — List of nodes which must succeed for this node to run
- L523 _public property_ `public List<string>? OptionalInputDependencies { get; set; }` — List of nodes which may have succeeded when this node is run
- L528 _public property_ `public List<string>? OrderDependencies { get; set; }` — List of nodes which must have completed for this node to run
- L533 _public property_ `public Priority? Priority { get; set; }` — The priority of this node
- L538 _public property_ `public bool? AllowRetry { get; set; }` — This node can be run multiple times
- L543 _public property_ `public bool? RunEarly { get; set; }` — This node can start running early, before dependencies of other nodes in the same group are complete
- L548 _public property_ `public bool? Warnings { get; set; }` — Whether to include warnings in the diagnostic output
- L553 _public property_ `public Dictionary<string, string>? Credentials { get; set; }` — Credentials required for this node to run. This dictionary maps from environment variable names to a credential property in the format 'CredentialName.PropertyName'.
- L558 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — Properties for this node
- L563 _public property_ `public NodeAnnotations? Annotations { get; set; }` — Additional user annotations for this node
- L582-601 _public ctor_ `public NewNode(string name, List<string>? inputs = null, List<string>? optionalInputs = null, List<string>? outputs = null, List<string>? inputDependencies = null, List<string>? optionalInputDependencies = null, List<string>? orderDependencies = null, Priority? priority = null, bool? allowRetry = null, bool? runEarly = null, bool? warnings = null, Dictionary<string, string>? credentials = null, Dictionary<string, string>? properties = null, IReadOnlyNodeAnnotations? annotations = null)` — Constructor
- L608-611 _public ctor_ `public NewNode(IGraph graph, INode node) : this(node.Name, [.. node.Inputs.Select(x => graph.GetNode(x.NodeRef).Name)], [.. node.OptionalInputs.Select(x => graph.GetNode(x.NodeRef).Name)], [.. node.OutputNames], [.. node.InputDependencies.Select(x => graph.GetNode(x).Name)], [.. node.OptionalInputDependencies.Select(x => graph.GetNode(x).Name)], [.. node.OrderDependencies.Select(x => graph.GetNode(x).Name)], node.Priority, node.AllowRetry, node.RunEarly, node.Warnings, node.Credentials?.ToDictionary(x => x.Key, x => x.Value), node.Properties?.ToDictionary(x => x.Key, x => x.Value), node.Annotations)` — Constructor

#### class `EpicGames.Horde.Jobs.Graphs.NewGroup`  
`public class NewGroup`  
_public; L617-649_
- desc: Information about a group of nodes
- L622 _public property_ `public string AgentType { get; set; }` — The type of agent to execute this group
- L627 _public property_ `public List<NewNode> Nodes { get; set; }` — Nodes in the group
- L634-638 _public ctor_ `public NewGroup(string agentType, List<NewNode> nodes)` — Constructor
- L645-648 _public ctor_ `public NewGroup(IGraph graph, INodeGroup group) : this(group.AgentType, [.. group.Nodes.Select(x => new NewNode(graph, x))])` — Constructor

#### class `EpicGames.Horde.Jobs.Graphs.NewLabel`  
`public class NewLabel`  
_public; L654-702_
- desc: Information about a group of nodes
- L660 _public property_ `public string? Category => ...` — attrs: `[Obsolete("Use DashboardCategory instead")]` — Category for this label
- L666 _public property_ `public string? Name => ...` — attrs: `[Obsolete("Use DashboardName instead")]` — Name of the aggregate
- L671 _public property_ `public string? DashboardName { get; set; }` — Name of the aggregate
- L676 _public property_ `public string? DashboardCategory { get; set; }` — Category for this label
- L681 _public property_ `public string? UgsName { get; set; }` — Name of the badge in UGS
- L686 _public property_ `public string? UgsProject { get; set; }` — Project to show this label for in UGS
- L691 _public property_ `public LabelChange Change { get; set; }` — Which change the label applies to
- L696 _public property_ `public List<string> RequiredNodes { get; set; }` — Nodes which must be part of the job for the aggregate to be valid
- L701 _public property_ `public List<string> IncludedNodes { get; set; }` — Nodes which must be part of the job for the aggregate to be valid

#### class `EpicGames.Horde.Jobs.Graphs.NewAggregate`  
`public class NewAggregate`  
_public; L707-729_
- desc: Information about a group of nodes
- L712 _public property_ `public string Name { get; set; }` — Name of the aggregate
- L717 _public property_ `public List<string> Nodes { get; set; }` — Nodes which must be part of the job for the aggregate to be valid
- L724-728 _public ctor_ `public NewAggregate(string name, List<string> nodes)` — Constructor

#### record `EpicGames.Horde.Jobs.Graphs.NewGraphArtifact`  
`public record class NewGraphArtifact(ArtifactName Name, ArtifactType Type, string Description, string BasePath, List<string> Keys, List<string> Metadata, string? NodeName, string? OutputName)`  
_public; L734-734_
- desc: Information about an artifact

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Graphs/NodeAnnotations.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Graphs.IReadOnlyNodeAnnotations`  
`public interface IReadOnlyNodeAnnotations : IReadOnlyDictionary<string, string>`  
_public; L13-55_
- inherits: `IReadOnlyDictionary<string, string>`
- desc: Interface which wraps a generic key/value dictionary to provide specific node annotations
- L19 _public* property_ `WorkflowId? WorkflowId { get; }` — Workflow to use for triaging issues from this node
- L24 _public* property_ `bool? CreateIssues { get; }` — Whether to create issues for this node
- L29 _public* property_ `bool? CreateWarningIssues { get; }` — Whether to create warning issues for this node
- L34 _public* property_ `bool? AutoAssign { get; }` — Whether to automatically assign issues that could only be caused by one user, or have a well defined correlation with a modified file.
- L39 _public* property_ `string? AutoAssignToUser { get; }` — Automatically assign any issues to the given user
- L44 _public* property_ `bool? NotifySubmitters { get; }` — Whether to notify all submitters between a build suceeding and failing, allowing them to step forward and take ownership of an issue.
- L49 _public* property_ `string? IssueGroup { get; }` — Key to use for grouping issues together, preventing them being merged with other groups
- L54 _public* property_ `bool? BuildBlocker { get; }` — Whether failures in this node should be flagged as build blockers

#### class `EpicGames.Horde.Jobs.Graphs.NodeAnnotations`  
`public class NodeAnnotations : Dictionary<string, string>, IReadOnlyNodeAnnotations`  
_public; L60-239_
- inherits: `Dictionary<string, string>, IReadOnlyNodeAnnotations`
- desc: Set of annotations for a node
- L65 _public property_ `public static IReadOnlyNodeAnnotations Empty { get; }` — Empty annotation dictionary
- L68 _public const_ `public const string WorkflowKeyName = "Workflow"` — (inheritdoc)
- L71 _public const_ `public const string CreateIssuesKeyName = "CreateIssues"` — (inheritdoc)
- L74 _public const_ `public const string CreateWarningIssuesKeyName = "CreateWarningIssues"` — (inheritdoc)
- L77 _public const_ `public const string AutoAssignKeyName = "AutoAssign"` — (inheritdoc)
- L80 _public const_ `public const string AutoAssignToUserKeyName = "AutoAssignToUser"` — (inheritdoc)
- L83 _public const_ `public const string NotifySubmittersKeyName = "NotifySubmitters"` — (inheritdoc)
- L86 _public const_ `public const string IssueGroupKeyName = "IssueGroup"` — (inheritdoc)
- L89 _public const_ `public const string BuildBlockerKeyName = "BuildBlocker"` — (inheritdoc)
- L94-97 _public ctor_ `public NodeAnnotations() : base(StringComparer.OrdinalIgnoreCase)` — Constructor
- L103-107 _public ctor_ `public NodeAnnotations(IReadOnlyDictionary<string, string> annotations) : this()` — Constructor
- L110-130 _public property_ `public WorkflowId? WorkflowId { get; set; }` — (inheritdoc)
- L133-137 _public property_ `public bool? CreateIssues { get; set; }` — (inheritdoc)
- L140-144 _public property_ `public bool? CreateWarningIssues { get; set; }` — (inheritdoc)
- L147-151 _public property_ `public bool? AutoAssign { get; set; }` — (inheritdoc)
- L154-158 _public property_ `public string? AutoAssignToUser { get; set; }` — (inheritdoc)
- L161-165 _public property_ `public bool? NotifySubmitters { get; set; }` — (inheritdoc)
- L168-172 _public property_ `public string? IssueGroup { get; set; }` — (inheritdoc)
- L175-179 _public property_ `public bool? BuildBlocker { get; set; }` — (inheritdoc)
- L181-196 _private method_ `private bool? GetBoolValue(string key)`
- L198-208 _private method_ `private void SetBoolValue(string key, bool? value)`
- L210-214 _private method_ `private string? GetStringValue(string key)`
- L216-226 _private method_ `private void SetStringValue(string key, string? value)`
- L232-238 _public method_ `public void Merge(IReadOnlyDictionary<string, string> other)` — Merge in entries from another set of annotation

### `Source/Programs/Shared/EpicGames.Horde/Jobs/IJob.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.IJob`  
`public interface IJob`  
_public; L35-408_
- desc: Document describing a job
- L40 _public const_ `public const string TargetArgumentPrefix = "-Target="` — Job argument indicating a target that should be built
- L45 _public const_ `public const string SetupNodeName = "Setup Build"` — Name of the node which parses the buildgraph script
- L50 _public property_ `public JobId Id { get; }` — Identifier for the job. Randomly generated.
- L55 _public property_ `public StreamId StreamId { get; }` — The stream that this job belongs to
- L60 _public property_ `public TemplateId TemplateId { get; }` — The template ref id
- L65 _public property_ `public ContentHash? TemplateHash { get; }` — The template that this job was created from
- L70 _public property_ `public ContentHash GraphHash { get; }` — Hash of the graph definition
- L75 _public property_ `public IGraph Graph { get; }` — Graph for this job
- L80 _public property_ `public UserId? StartedByUserId { get; }` — Id of the user that started this job
- L85 _public property_ `public UserId? AbortedByUserId { get; }` — Id of the user that aborted this job. Set to null if the job is not aborted.
- L90 _public property_ `public string? CancellationReason { get; }` — Optional reason for why the job was canceled
- L95 _public property_ `public BisectTaskId? StartedByBisectTaskId { get; }` — Identifier of the bisect task that started this job
- L100 _public property_ `public string Name { get; }` — Name of the job.
- L105 _public property_ `public CommitIdWithOrder CommitId { get; }` — The commit to build
- L110 _public property_ `public CommitIdWithOrder? CodeCommitId { get; }` — The code commit for this build
- L115 _public property_ `public CommitId? PreflightCommitId { get; }` — The preflight changelist number
- L120 _public property_ `public string? PreflightDescription { get; }` — Description for the shelved change if running a preflight
- L125 _public property_ `public Priority Priority { get; }` — Priority of this job
- L130 _public property_ `public bool AutoSubmit { get; }` — For preflights, submit the change if the job is successful
- L135 _public property_ `public int? AutoSubmitChange { get; }` — The submitted changelist number
- L140 _public property_ `public string? AutoSubmitMessage { get; }` — Message produced by trying to auto-submit the change
- L145 _public property_ `public bool UpdateIssues { get; }` — Whether to update issues based on the outcome of this job
- L150 _public property_ `public bool PromoteIssuesByDefault { get; }` — Whether to promote issues by default based on the outcome of this job
- L155 _public property_ `public DateTime CreateTimeUtc { get; }` — Time that the job was created (in UTC)
- L160 _public property_ `public JobOptions? JobOptions { get; }` — Options for executing the job
- L165 _public property_ `public IReadOnlyList<IAclClaim> Claims { get; }` — Claims inherited from the user that started this job
- L170 _public property_ `public IReadOnlyList<IJobStepBatch> Batches { get; }` — Array of jobstep runs
- L175 _public property_ `public IReadOnlyDictionary<ParameterId, string> Parameters { get; }` — Parameters for the job
- L180 _public property_ `public IReadOnlyList<string> Arguments { get; }` — Optional user-defined properties for this job
- L185 _public property_ `public IReadOnlyList<string>? Targets { get; }` — Custom list of targets for the job. If null or empty, the list of targets is determined from the command line.
- L190 _public property_ `public IReadOnlyList<string> AdditionalArguments { get; }` — Additional arguments for the job, when a set of parameters are applied.
- L195 _public property_ `public IReadOnlyDictionary<string, string> Environment { get; }` — Environment variables for the job
- L200 _public property_ `public IReadOnlyList<int> Issues { get; }` — Issues associated with this job
- L205 _public property_ `public NotificationTriggerId? NotificationTriggerId { get; }` — Unique id for notifications
- L210 _public property_ `public bool ShowUgsBadges { get; }` — Whether to show badges in UGS for this job
- L215 _public property_ `public bool ShowUgsAlerts { get; }` — Whether to show alerts in UGS for this job
- L220 _public property_ `public string? NotificationChannel { get; }` — Notification channel for this job.
- L225 _public property_ `public string? NotificationChannelFilter { get; }` — Notification channel filter for this job.
- L230 _public property_ `public IReadOnlyDictionary<int, NotificationTriggerId> LabelIdxToTriggerId { get; }` — Mapping of label ids to notification trigger ids for notifications
- L235 _public property_ `public IReadOnlyList<IJobReport>? Reports { get; }` — List of reports for this step
- L240 _public property_ `public IReadOnlyList<IChainedJob> ChainedJobs { get; }` — List of downstream job triggers
- L245 _public property_ `public JobId? ParentJobId { get; }` — The job which spawned this job
- L250 _public property_ `public JobStepId? ParentJobStepId { get; }` — The job step which spawned this job
- L255 _public property_ `public DateTime UpdateTimeUtc { get; }` — The last update time
- L260 _public property_ `public List<string> Metadata { get; }` — The job meta data
- L265 _public property_ `public int UpdateIndex { get; }` — Update counter for this document. Any updates should compare-and-swap based on the value of this counter, or increment it in the case of server-side updates.
- L271 _public* method_ `Task<IJob?> RefreshAsync(CancellationToken cancellationToken = default)` — Gets the latest job state
- L279 _public* method_ `bool TryGetBatch(JobStepBatchId batchId, [NotNullWhen(true)] out IJobStepBatch? batch)` — Attempt to get a batch with the given id
- L287 _public* method_ `bool TryGetStep(JobStepId stepId, [NotNullWhen(true)] out IJobStep? step)` — Attempt to get a step with the given id
- L294 _public* method_ `Task<bool> TryDeleteAsync(CancellationToken cancellationToken = default)` — Attempt to delete the job
- L301 _public* method_ `Task<IJob?> TryRemoveFromDispatchQueueAsync(CancellationToken cancellationToken = default)` — Removes a job from the dispatch queue. Ignores the state of any batches still remaining to execute. Should only be used to correct for inconsistent state.
- L319 _public* method_ `Task<IJob?> TryUpdateJobAsync(string? name = null, Priority? priority = null, bool? autoSubmit = null, int? autoSubmitChange = null, string? autoSubmitMessage = null, UserId? abortedByUserId = null, NotificationTriggerId? notificationTriggerId = null, List<JobReport>? reports = null, List<string>? arguments = null, KeyValuePair<int, NotificationTriggerId>? labelIdxToTriggerId = null, KeyValuePair<TemplateId, JobId>? jobTrigger = null, string? cancellationReason = null, CancellationToken cancellationToken = default)` — Updates a new job
- L330 _public* method_ `Task<IJob?> TryUpdateBatchAsync(JobStepBatchId batchId, LogId? newLogId, JobStepBatchState? newState, JobStepBatchError? newError, CancellationToken cancellationToken = default)` — Updates the state of a batch
- L352 _public* method_ `Task<IJob?> TryUpdateStepAsync(JobStepBatchId batchId, JobStepId stepId, JobStepState newState = default, JobStepOutcome newOutcome = default, JobStepError? newError = null, bool? newAbortRequested = null, UserId? newAbortByUserId = null, LogId? newLogId = null, NotificationTriggerId? newNotificationTriggerId = null, UserId? newRetryByUserId = null, Priority? newPriority = null, List<JobReport>? newReports = null, Dictionary<string, string?>? newProperties = null, string? newCancellationReason = null, JobId? newSpawnedJob = null, CancellationToken cancellationToken = default)` — Update a jobstep state
- L360 _public* method_ `Task<IJob?> TryUpdateGraphAsync(IGraph newGraph, CancellationToken cancellationToken = default)` — Attempts to update the node groups to be executed for a job. Fails if another write happens in the meantime.
- L368 _public* method_ `Task<IJob?> TrySkipAllBatchesAsync(JobStepBatchError reason, CancellationToken cancellationToken = default)` — Marks a job as skipped
- L377 _public* method_ `Task<IJob?> TrySkipBatchAsync(JobStepBatchId batchId, JobStepBatchError reason, CancellationToken cancellationToken = default)` — Marks a batch as skipped
- L386 _public* method_ `Task<IJob?> TryFailBatchAsync(int batchIdx, JobStepBatchError reason, CancellationToken cancellationToken = default)` — Abort an agent's lease, and update the payload accordingly
- L399 _public* method_ `Task<IJob?> TryAssignLeaseAsync(int batchIdx, PoolId poolId, AgentId agentId, SessionId sessionId, LeaseId leaseId, LogId logId, CancellationToken cancellationToken = default)` — Attempt to assign a lease to execute a batch
- L407 _public* method_ `Task<IJob?> TryCancelLeaseAsync(int batchIdx, CancellationToken cancellationToken = default)` — Cancel a lease reservation on a batch (before it has started)

#### class `EpicGames.Horde.Jobs.JobExtensions`  
`public static class JobExtensions`  
_public; L413-1269_
- desc: Extension methods for jobs
- L420-445 _public method_ `public static JobState GetState(this IJob job)` — Gets the current job state
- L452-456 _public method_ `public static (JobStepState, JobStepOutcome) GetTargetState(this IJob job)` — Gets the outcome for a particular named target. May be an aggregate or node name.
- L465-506 _public method_ `public static (JobStepState, JobStepOutcome)? GetTargetState(this IJob job, IGraph graph, string? target)` — Gets the outcome for a particular named target. May be an aggregate or node name.
- L513-530 _public method_ `public static (JobStepState, JobStepOutcome) GetTargetState(IEnumerable<IJobStep> steps)` — Gets the outcome for a particular named target. May be an aggregate or node name.
- L539-578 _public method_ `public static JobStepOutcome GetTargetOutcome(this IJob job, IGraph graph, string target)` — Gets the outcome for a particular named target. May be an aggregate or node name.
- L587-604 _public method_ `public static bool TryGetStepForNode(this IJob job, NodeRef nodeRef, [NotNullWhen(true)] out IJobStep? jobStep)` — Gets the job step for a particular node
- L612-624 _public method_ `public static IReadOnlyDictionary<NodeRef, IJobStep> GetStepForNodeMap(this IJob job)` — Gets a dictionary that maps NodeRef objects to their associated IJobStep objects on a IJob.
- L632-650 _public method_ `public static JobStepRefId? FindLatestStepForNode(this IJob job, NodeRef nodeRef)` — Find the latest step executing the given node
- L660-746 _public method_ `public static Dictionary<INode, TimingInfo> GetTimingInfo(this IJob job, IGraph graph, IJobTiming jobTiming, ILogger logger)` — Gets the estimated timing info for all nodes in the job
- L754-794 _public method_ `public static JobStepsCompletionInfo GetStepCompletionInfo(this IJob job)` — Gets the step completion info of the job.
- L804-823 _public method_ `public static TimeSpan? GetAverageWaitTime(IGraph graph, IJobStepBatch batch, IJobTiming jobTiming, ILogger logger)` — Gets the average wait time for this batch
- L833-852 _public method_ `public static TimeSpan? GetAverageInitTime(IGraph graph, IJobStepBatch batch, IJobTiming jobTiming, ILogger logger)` — Gets the average initialization time for this batch
- L859-869 _private* method_ `static TimeSpan? NullableTimeSpanFromSeconds(float? seconds)` — Creates a nullable timespan from a nullable number of seconds
- L879-887 _public method_ `public static bool TryGetStep(this IJob job, JobStepBatchId batchId, JobStepId stepId, [NotNullWhen(true)] out IJobStep? step)` — Attempts to get a batch with the given id
- L896-927 _public method_ `public static HashSet<NodeRef> GetNodesForLabel(this IJob job, IGraph graph, int labelIdx)` — Finds the set of nodes affected by a label
- L936-1025 _public method_ `public static GetDefaultLabelStateResponse? GetLabelStateResponses(this IJob job, IGraph graph, List<GetLabelStateResponse> responses)` — Create a list of aggregate responses, combining the graph definitions with the state of the job
- L1033-1074 _public method_ `public static IReadOnlyList<(LabelState, LabelOutcome)> GetLabelStates(this IJob job, IGraph graph)` — Get the states of all labels for this job
- L1082-1086 _public method_ `public static Dictionary<int, UgsBadgeState> GetUgsBadgeStates(this IJob job, IGraph graph)` — Get the states of all UGS badges for this job
- L1096-1155 _public method_ `public static Dictionary<int, UgsBadgeState> GetUgsBadgeStates(this IJob job, IGraph graph, IReadOnlyList<(LabelState, LabelOutcome)> labelStates)` — Get the states of all UGS badges for this job
- L1164-1175 _public method_ `public static void GetJobState(this IJob job, IReadOnlyDictionary<NodeRef, IJobStep> stepForNode, out LabelState newState, out LabelOutcome newOutcome)` — Gets the state of a job, as a label that includes all steps
- L1184-1210 _public method_ `public static void GetLabelState(IEnumerable<NodeRef> includedNodes, IReadOnlyDictionary<NodeRef, IJobStep> stepForNode, out LabelState newState, out LabelOutcome newOutcome)` — Gets the state of a label
- L1215-1218 _public method_ `public static string GetArtifactKey(this IJob job)` — Gets a key attached to all artifacts produced for a job
- L1223-1226 _public method_ `public static string GetArtifactKey(this IJob job, IJobStep jobStep)` — Gets a key attached to all artifacts produced for a job step
- L1229-1247 _public method_ `public static async Task<IJob?> SkipBatchAsync(this IJob job, JobStepBatchId batchId, JobStepBatchError error, CancellationToken cancellationToken)` — (inheritdoc)
- L1250-1268 _public method_ `public static async Task<IJob?> SkipAllBatchesAsync(this IJob job, JobStepBatchError reason, CancellationToken cancellationToken)` — (inheritdoc)

#### interface `EpicGames.Horde.Jobs.IJobStepBatch`  
`public interface IJobStepBatch`  
_public; L1274-1360_
- desc: Stores information about a batch of job steps
- L1279 _public property_ `public IJob Job { get; }` — Job that this batch belongs to
- L1284 _public property_ `public JobStepBatchId Id { get; }` — Unique id for this group
- L1289 _public property_ `public string AgentType { get; }` — The type of agent to execute this group
- L1294 _public property_ `public LogId? LogId { get; }` — The log file id for this batch
- L1299 _public property_ `public INodeGroup Group { get; }` — The node group for this batch
- L1304 _public property_ `public int GroupIdx { get; }` — Index of the group being executed
- L1309 _public property_ `public JobStepBatchState State { get; }` — The state of this group
- L1314 _public property_ `public JobStepBatchError Error { get; }` — Error associated with this group
- L1319 _public property_ `public IReadOnlyList<IJobStep> Steps { get; }` — Steps within this run
- L1324 _public property_ `public PoolId? PoolId { get; }` — The pool that this agent was taken from
- L1329 _public property_ `public AgentId? AgentId { get; }` — The agent assigned to execute this group
- L1334 _public property_ `public SessionId? SessionId { get; }` — The agent session that is executing this group
- L1339 _public property_ `public LeaseId? LeaseId { get; }` — The lease that's executing this group
- L1344 _public property_ `public int SchedulePriority { get; }` — The weighted priority of this batch for the scheduler
- L1349 _public property_ `public DateTime? ReadyTimeUtc { get; }` — Time at which the group became ready (UTC).
- L1354 _public property_ `public DateTime? StartTimeUtc { get; }` — Time at which the group started (UTC).
- L1359 _public property_ `public DateTime? FinishTimeUtc { get; }` — Time at which the group finished (UTC)

#### class `EpicGames.Horde.Jobs.JobStepBatchExtensions`  
`public static class JobStepBatchExtensions`  
_public; L1365-1467_
- desc: Extension methods for IJobStepBatch
- L1374-1378 _public method_ `public static bool TryGetStep(this IJobStepBatch batch, JobStepId stepId, [NotNullWhen(true)] out IJobStep? step)` — Attempts to get a step with the given id
- L1385-1388 _public method_ `public static bool CanBeAppendedTo(this IJobStepBatch batch)` — Determines if new steps can be appended to this batch. We do not allow this after the last step has been completed, because the agent is shutting down.
- L1395-1405 _public method_ `public static TimeSpan? GetWaitTime(this IJobStepBatch batch)` — Gets the wait time for this batch
- L1412-1425 _public method_ `public static TimeSpan? GetInitTime(this IJobStepBatch batch)` — Gets the initialization time for this batch
- L1433-1437 _public method_ `public static HashSet<INode> GetStartDependencies(this IJobStepBatch batch, IReadOnlyList<INodeGroup> groups)` — Get the dependencies required for this batch to start, taking run-early nodes into account
- L1445-1466 _public method_ `public static HashSet<INode> GetStartDependencies(IEnumerable<INode> batchNodes, IReadOnlyList<INodeGroup> groups)` — Get the dependencies required for this batch to start, taking run-early nodes into account

#### interface `EpicGames.Horde.Jobs.IJobStep`  
`public interface IJobStep`  
_public; L1472-1643_
- desc: Embedded jobstep document
- L1477 _public property_ `public IJob Job { get; }` — Job that this step belongs to
- L1482 _public property_ `public IJobStepBatch Batch { get; }` — Batch that this step belongs to
- L1487 _public property_ `public JobStepId Id { get; }` — Unique ID assigned to this jobstep. A new id is generated whenever a jobstep's order is changed.
- L1492 _public property_ `public INode Node { get; }` — The node for this step
- L1497 _public property_ `public int NodeIdx { get; }` — Index of the node which this jobstep is to execute
- L1502 _public property_ `public string Name { get; }` — The name of this node
- L1507 _public property_ `public IReadOnlyList<JobStepOutputRef> Inputs { get; }` — References to inputs for this node
- L1512 _public property_ `public IReadOnlyList<JobStepOutputRef> OptionalInputs { get; }` — References to optional inputs for this node
- L1517 _public property_ `public IReadOnlyList<string> OutputNames { get; }` — List of output names
- L1522 _public property_ `public IReadOnlyList<JobStepId> InputDependencies { get; }` — Indices of nodes which must have succeeded for this node to run
- L1527 _public property_ `public IReadOnlyList<JobStepId> OptionalInputDependencies { get; }` — Indices of nodes which could have succeeded for this node to run
- L1532 _public property_ `public IReadOnlyList<JobStepId> OrderDependencies { get; }` — Indices of nodes which must have completed for this node to run
- L1537 _public property_ `public bool AllowRetry { get; }` — Whether this node can be run multiple times
- L1542 _public property_ `public bool RunEarly { get; }` — This node can start running early, before dependencies of other nodes in the same group are complete
- L1547 _public property_ `public bool Warnings { get; }` — Whether to include warnings in the output (defaults to true)
- L1552 _public property_ `public IReadOnlyDictionary<string, string>? Credentials { get; }` — List of credentials required for this node. Each entry maps an environment variable name to a credential in the form "CredentialName.PropertyName".
- L1557 _public property_ `public IReadOnlyNodeAnnotations Annotations { get; }` — Annotations for this node
- L1562 _public property_ `public IReadOnlyList<string> Metadata { get; }` — Metadata for this node
- L1567 _public property_ `public JobStepState State { get; }` — Current state of the job step. This is updated automatically when runs complete.
- L1572 _public property_ `public JobStepOutcome Outcome { get; }` — Current outcome of the jobstep
- L1577 _public property_ `public JobStepError Error { get; }` — Error from executing this step
- L1582 _public property_ `public LogId? LogId { get; }` — The log id for this step
- L1587 _public property_ `public NotificationTriggerId? NotificationTriggerId { get; }` — Unique id for notifications
- L1592 _public property_ `public DateTime? ReadyTimeUtc { get; }` — Time at which the batch transitioned to the ready state (UTC).
- L1597 _public property_ `public DateTime? StartTimeUtc { get; }` — Time at which the batch transitioned to the executing state (UTC).
- L1602 _public property_ `public DateTime? FinishTimeUtc { get; }` — Time at which the run finished (UTC)
- L1607 _public property_ `public Priority? Priority { get; }` — Override for the priority of this step
- L1612 _public property_ `public UserId? RetriedByUserId { get; }` — If a retry is requested, stores the name of the user that requested it
- L1617 _public property_ `public bool AbortRequested { get; }` — Signal if a step should be aborted
- L1622 _public property_ `public UserId? AbortedByUserId { get; }` — If an abort is requested, stores the id of the user that requested it
- L1627 _public property_ `public string? CancellationReason { get; }` — Optional reason for why the job step was canceled
- L1632 _public property_ `public IReadOnlyList<IJobReport>? Reports { get; }` — List of reports for this step
- L1637 _public property_ `public IReadOnlyList<JobId>? SpawnedJobs { get; }` — List of jobs this step has spawned
- L1642 _public property_ `public IReadOnlyDictionary<string, string>? Properties { get; }` — Reports for this jobstep.

#### class `EpicGames.Horde.Jobs.JobStepExtensions`  
`public static class JobStepExtensions`  
_public; L1648-1684_
- desc: Extension methods for job steps
- L1654-1657 _public method_ `public static bool IsPendingState(JobStepState state)` — Determines if a jobstep state is completed, skipped, or aborted.
- L1663 _public method_ `public static bool IsPending(this IJobStep step)` — Determines if a jobstep is done by checking to see if it is completed, skipped, or aborted.
- L1672-1683 _public method_ `public static bool HasTimedOut(this IJobStep step, DateTime utcNow)` — Determine if a step should be timed out

#### class `EpicGames.Horde.Jobs.TimingInfo`  
`public class TimingInfo`  
_public; L1689-1819_
- desc: Cumulative timing information to reach a certain point in a job
- L1694 _public property_ `public TimeSpan? TotalWaitTime { get; set; }` — Wait time on the critical path
- L1699 _public property_ `public TimeSpan? TotalInitTime { get; set; }` — Sync time on the critical path
- L1704 _public property_ `public TimeSpan? TotalTimeToComplete { get; set; }` — Duration to this point
- L1709 _public property_ `public TimeSpan? AverageTotalWaitTime { get; set; }` — Average wait time to this point
- L1714 _public property_ `public TimeSpan? AverageTotalInitTime { get; set; }` — Average sync time to this point
- L1719 _public property_ `public TimeSpan? AverageTotalTimeToComplete { get; set; }` — Average duration to this point
- L1724 _public property_ `public IJobStepTiming? StepTiming { get; set; }` — Individual step timing information
- L1729-1738 _public ctor_ `public TimingInfo()` — Constructor
- L1744-1753 _public ctor_ `public TimingInfo(TimingInfo other)` — Copy constructor
- L1759-1780 _public method_ `public void WaitFor(TimingInfo other)` — Modifies this timing to wait for another timing
- L1786-1792 _public method_ `public void WaitForAll(IEnumerable<TimingInfo> others)` — Waits for all the given timing info objects to complete
- L1799-1804 _public method_ `public static TimingInfo Max(IEnumerable<TimingInfo> others)` — Constructs a new TimingInfo object which represents the last TimingInfo to finish
- L1809-1818 _public method_ `public void CopyToResponse(GetTimingInfoResponse response)` — Copies this info to a repsonse object

#### class `EpicGames.Horde.Jobs.JobStepsCompletionInfo`  
`public class JobStepsCompletionInfo`  
_public; L1824-1870_
- desc: Step completion information
- L1829 _public property_ `public int StepPassCount { get; set; }` — The total count of steps passed within a job.
- L1834 _public property_ `public int StepWarningCount { get; set; }` — The total count of steps with a warning result within a job.
- L1839 _public property_ `public int StepFailureCount { get; set; }` — The total count of steps with a failure result within a job.
- L1844 _public property_ `public int StepTotalCount { get; set; }` — The total number of steps within a job.
- L1849 _public property_ `public float JobStepsTotalTime { get; set; }` — The total step time for the job, in seconds.
- L1854 _public property_ `public float PassRatio => ...` — The pass count as compared to the total step count.
- L1859 _public property_ `public float PassWithWarningRatio => ...` — The pass and warning count as compared to the total step count.
- L1864 _public property_ `public float WarningRatio => ...` — The warning count as compared to the total step count.
- L1869 _public property_ `public float FailureRatio => ...` — The failure count as compared to the total step count.

#### interface `EpicGames.Horde.Jobs.IChainedJob`  
`public interface IChainedJob`  
_public; L1875-1896_
- desc: Information about a chained job trigger
- L1880 _public property_ `public string Target { get; }` — The target to monitor
- L1885 _public property_ `public TemplateId TemplateRefId { get; }` — The template to trigger on success
- L1890 _public property_ `public JobId? JobId { get; }` — The triggered job id
- L1895 _public property_ `public bool UseDefaultChangeForTemplate { get; }` — Whether to run the latest change, or default change for the template, when starting the new job. Uses same change as the triggering job by default.

#### interface `EpicGames.Horde.Jobs.IJobReport`  
`public interface IJobReport`  
_public; L1901-1937_
- desc: Report for a job or jobstep
- L1906 _public* property_ `string Name { get; }` — Name of the report
- L1911 _public* property_ `JobReportPlacement Placement { get; }` — Where to render the report
- L1916 _public* property_ `ArtifactId? ArtifactId { get; }` — The artifact id
- L1921 _public* property_ `string? Content { get; }` — Inline data for the report
- L1926 _public* property_ `string? Message { get; }` — The job/step message
- L1931 _public* property_ `string? Severity { get; }` — The message severity
- L1936 _public* property_ `string? Color { get; }` — The message color

#### class `EpicGames.Horde.Jobs.JobReport`  
`public class JobReport : IJobReport`  
_public; L1942-1964_
- inherits: `IJobReport`
- desc: Implementation of IReport
- L1945 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L1948 _public property_ `public JobReportPlacement Placement { get; set; }` — (inheritdoc)
- L1951 _public property_ `public ArtifactId? ArtifactId { get; set; }` — (inheritdoc)
- L1954 _public property_ `public string? Content { get; set; }` — (inheritdoc)
- L1957 _public property_ `public string? Message { get; set; }` — (inheritdoc)
- L1960 _public property_ `public string? Severity { get; set; }` — (inheritdoc)
- L1963 _public property_ `public string? Color { get; set; }` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/IJobStepRef.cs` (EpicGames.Horde)


#### interface `HordeServer.Jobs.IJobStepRef`  
`public interface IJobStepRef`  
_public; L18-142_
- desc: Searchable reference to a jobstep
- L23 _public property_ `public JobStepRefId Id { get; }` — Globally unique identifier for the jobstep being referenced
- L29 _public property_ `public JobId? JobId { get; }` — The job the jobstep belongs to.
- L35 _public property_ `public JobStepBatchId? BatchId { get; }` — The batch the jobstep belongs to.
- L41 _public property_ `public JobStepId? StepId { get; }` — The step the job step represents.
- L46 _public property_ `public string JobName { get; }` — Name of the job
- L51 _public property_ `public string NodeName { get; }` — Name of the node
- L56 _public property_ `public StreamId StreamId { get; }` — Unique id of the stream containing the job
- L61 _public property_ `public TemplateId TemplateId { get; }` — Template for the job being executed
- L66 _public property_ `public CommitIdWithOrder CommitId { get; }` — The change number being built
- L71 _public property_ `public LogId? LogId { get; }` — Log for this step
- L76 _public property_ `public PoolId? PoolId { get; }` — The agent type
- L81 _public property_ `public AgentId? AgentId { get; }` — The agent id
- L86 _public property_ `public JobStepState? State { get; }` — State of the step.
- L91 _public property_ `public JobStepOutcome? Outcome { get; }` — Outcome of the step, once complete.
- L96 _public property_ `public IReadOnlyList<string>? Metadata { get; }` — Metadata for the step
- L101 _public property_ `public IReadOnlyList<int>? IssueIds { get; }` — Issues ids affecting this job step
- L106 _public property_ `public bool UpdateIssues { get; }` — Whether this step should update issues
- L111 _public property_ `public CommitIdWithOrder? LastSuccess { get; }` — The last change that succeeded. Note that this is only set when the ref is updated; it is not necessarily consistent with steps run later.
- L116 _public property_ `public CommitIdWithOrder? LastWarning { get; }` — The last change that succeeded, or completed a warning. See LastSuccess.
- L121 _public property_ `public float BatchWaitTime { get; }` — Time taken for the batch containing this batch to start after it became ready
- L126 _public property_ `public float BatchInitTime { get; }` — Time taken for this batch to initialize
- L131 _public property_ `public DateTime JobStartTimeUtc { get; }` — Time at which the job started
- L136 _public property_ `public DateTime StartTimeUtc { get; }` — Time at which the step started.
- L141 _public property_ `public DateTime? FinishTimeUtc { get; }` — Time at which the step finished.

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.JobId`  
`public readonly record struct JobId(BinaryId Id)`  
_public; L16-28_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<JobId, JobIdConverter>))] [BinaryIdConverter(typeof(JobIdConverter))]`
- desc: Identifier for a job
- L21 _public property_ `public static JobId Empty { get; }` — Constant value for an empty job id
- L24 _public method_ `public static JobId Parse(string text)` — (inheritdoc)
- L27 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.JobIdConverter`  
`class JobIdConverter : BinaryIdConverter<JobId>`  
_internal*; L33-40_
- inherits: `BinaryIdConverter<JobId>`
- desc: Converter to and from BinaryId instances.
- L36 _public method_ `public override JobId FromBinaryId(BinaryId id)` — (inheritdoc)
- L39 _public method_ `public override BinaryId ToBinaryId(JobId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.JobState`  
`public enum JobState`  
_public; L24-40_
- desc: State of the job
- L29 _public* enumerator_ `Waiting` — Waiting for resources
- L34 _public* enumerator_ `Running` — Currently running one or more steps
- L39 _public* enumerator_ `Complete` — All steps have completed

#### interface `EpicGames.Horde.Jobs.IReadOnlyJobOptions`  
`public interface IReadOnlyJobOptions`  
_public; L45-81_
- desc: Read-only interface for job options
- L50 _public* property_ `string? Executor { get; }` — Name of the executor to use
- L55 _public* property_ `bool? UseWine { get; }` — Whether to execute using Wine emulation on Linux
- L60 _public* property_ `bool? RunInSeparateProcess { get; }` — Executes the job lease in a separate process
- L65 _public* property_ `string? WorkspaceMaterializer { get; }` — What workspace materializer to use in WorkspaceExecutor. Will override any value from workspace config.
- L70 _public* property_ `IReadOnlyJobContainerOptions Container { get; }` — Options for executing a job inside a container
- L75 _public* property_ `int? ExpireAfterDays { get; }` — Number of days after which to expire jobs
- L80 _public* property_ `string? Driver { get; }` — Name of the driver to use

#### class `EpicGames.Horde.Jobs.JobOptions`  
`public class JobOptions : IReadOnlyJobOptions`  
_public; L86-124_
- inherits: `IReadOnlyJobOptions`
- desc: Options for executing a job
- L89 _public property_ `public string? Executor { get; set; }` — (inheritdoc)
- L92 _public property_ `public bool? UseWine { get; set; }` — (inheritdoc)
- L95 _public property_ `public bool? RunInSeparateProcess { get; set; }` — (inheritdoc)
- L98 _public property_ `public string? WorkspaceMaterializer { get; set; }` — (inheritdoc)
- L101 _public property_ `public JobContainerOptions Container { get; set; }` — (inheritdoc)
- L104 _public property_ `public int? ExpireAfterDays { get; set; }` — (inheritdoc)
- L107 _public property_ `public string? Driver { get; set; }` — (inheritdoc)
- L109 _private* property_ `IReadOnlyJobContainerOptions IReadOnlyJobOptions.Container => ...`
- L114-123 _public method_ `public void MergeDefaults(JobOptions other)` — Merge defaults from another options object

#### interface `EpicGames.Horde.Jobs.IReadOnlyJobContainerOptions`  
`public interface IReadOnlyJobContainerOptions`  
_public; L129-150_
- desc: Options for a job container
- L134 _public property_ `public bool? Enabled { get; }` — Whether to execute job inside a container
- L139 _public property_ `public string? ImageUrl { get; }` — Image URL to container, such as "quay.io/podman/hello"
- L144 _public property_ `public string? ContainerEngineExecutable { get; }` — Container engine executable (docker or with full path like /usr/bin/podman)
- L149 _public property_ `public string? ExtraArguments { get; }` — Additional arguments to pass to container engine

#### class `EpicGames.Horde.Jobs.JobContainerOptions`  
`public class JobContainerOptions : IReadOnlyJobContainerOptions`  
_public; L155-187_
- inherits: `IReadOnlyJobContainerOptions`
- desc: Options for executing a job inside a container
- L160 _public property_ `public bool? Enabled { get; set; }` — Whether to execute job inside a container
- L165 _public property_ `public string? ImageUrl { get; set; }` — Image URL to container, such as "quay.io/podman/hello"
- L170 _public property_ `public string? ContainerEngineExecutable { get; set; }` — Container engine executable (docker or with full path like /usr/bin/podman)
- L175 _public property_ `public string? ExtraArguments { get; set; }` — Additional arguments to pass to container engine
- L180-186 _public method_ `public void MergeDefaults(JobContainerOptions other)` — Merge defaults from another options object

#### class `EpicGames.Horde.Jobs.ChangeQueryMessage`  
`public class ChangeQueryMessage : IChangeQuery`  
_public; L192-231_
- inherits: `IChangeQuery`
- desc: Query selecting the base changelist to use
- L195 _public property_ `public string? Name { get; set; }` — (inheritdoc)
- L198 _public property_ `public Condition? Condition { get; set; }` — (inheritdoc)
- L201 _public property_ `public TemplateId? TemplateId { get; set; }` — (inheritdoc)
- L204 _public property_ `public string? Target { get; set; }` — (inheritdoc)
- L207 _public property_ `public List<JobStepOutcome>? Outcomes { get; set; }` — (inheritdoc)
- L208 _private* property_ `IReadOnlyList<JobStepOutcome>? IChangeQuery.Outcomes => ...`
- L211 _public property_ `public CommitTag? CommitTag { get; set; }` — (inheritdoc)
- L216-217 _public ctor_ `public ChangeQueryMessage()` — Constructor
- L222-230 _public ctor_ `public ChangeQueryMessage(IChangeQuery other)` — Constructor

#### class `EpicGames.Horde.Jobs.CreateJobRequest`  
`public class CreateJobRequest`  
_public; L236-375_
- desc: Parameters required to create a job
- L242 _public property_ `public StreamId StreamId { get; set; }` — attrs: `[Required]` — The stream that this job belongs to
- L248 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[Required]` — The template for this job
- L253 _public property_ `public string? Name { get; set; }` — Name of the job
- L259-263 _public property_ `public int? Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — The changelist number to build. Can be null for latest.
- L264 _private* field_ `int? _change`
- L269-273 _public property_ `public CommitId? CommitId { get; set; }` — The changelist number to build. Can be null for latest.
- L274 _private* field_ `CommitId? _commitId`
- L280-284 _public property_ `public ChangeQueryMessage? ChangeQuery { get; set; }` — attrs: `[Obsolete("Use ChangeQueries instead")]` — Parameters to use when selecting the change to execute at.
- L289 _public property_ `public List<ChangeQueryMessage>? ChangeQueries { get; set; }` — List of change queries to evaluate
- L295-299 _public property_ `public int? PreflightChange { get; set; }` — attrs: `[Obsolete("Use PreflightCommitId instead")]` — The preflight changelist number
- L300 _private* field_ `int? _preflightChange`
- L305-309 _public property_ `public CommitId? PreflightCommitId { get; set; }` — The preflight commit
- L310 _private* field_ `CommitId? _preflightCommitId`
- L315 _public property_ `public JobOptions? JobOptions { get; set; }` — Job options
- L320 _public property_ `public Priority? Priority { get; set; }` — Priority for the job
- L325 _public property_ `public bool? AutoSubmit { get; set; }` — Whether to automatically submit the preflighted change on completion
- L330 _public property_ `public bool? UpdateIssues { get; set; }` — Whether to update issues based on the outcome of this job
- L335 _public property_ `public Dictionary<ParameterId, string>? Parameters { get; set; }` — Values for the template parameters
- L340 _public property_ `public List<string>? Arguments { get; set; }` — Arguments for the job
- L345 _public property_ `public List<string>? AdditionalArguments { get; set; }` — Additional arguments for the job
- L350 _public property_ `public List<string>? Targets { get; set; }` — Targets for the job. Will override any parameters specified in the Arguments or Parameters section if specified.
- L355 _public property_ `public string? ParentJobId { get; set; }` — The parent job id if any
- L360 _public property_ `public string? ParentJobStepId { get; set; }` — The parent step id if any
- L365 _public property_ `public bool? RunAsScheduler { get; set; }` — Run the job as the scheduler for debugging purposes, requires debugging ACL permission
- L370-374 _public ctor_ `public CreateJobRequest(StreamId streamId, TemplateId templateId)` — Private constructor for serialization

#### class `EpicGames.Horde.Jobs.CreateJobResponse`  
`public class CreateJobResponse`  
_public; L380-395_
- desc: Response from creating a new job
- L385 _public property_ `public string Id { get; set; }` — Unique id for the new job
- L391-394 _public ctor_ `public CreateJobResponse(string id)` — Constructor

#### class `EpicGames.Horde.Jobs.UpdateJobRequest`  
`public class UpdateJobRequest`  
_public; L400-431_
- desc: Updates an existing job
- L405 _public property_ `public string? Name { get; set; }` — New name for the job
- L410 _public property_ `public Priority? Priority { get; set; }` — New priority for the job
- L415 _public property_ `public bool? AutoSubmit { get; set; }` — Set whether the job should be automatically submitted or not
- L420 _public property_ `public bool? Aborted { get; set; }` — Mark this job as aborted
- L425 _public property_ `public string? CancellationReason { get; set; }` — Optional reason the job was canceled
- L430 _public property_ `public List<string>? Arguments { get; set; }` — New list of arguments for the job. Only -Target= arguments can be modified after the job has started.

#### class `EpicGames.Horde.Jobs.PutJobMetadataRequest`  
`public class PutJobMetadataRequest`  
_public; L436-447_
- desc: Job metadata put request
- L441 _public property_ `public List<string>? JobMetaData { get; set; }` — Meta data to append to the job
- L446 _public property_ `public Dictionary<string, List<string>>? StepMetaData { get; set; }` — Step meta data to append, JobStepId => list of meta data strings

#### enum `EpicGames.Horde.Jobs.JobReportPlacement`  
`public enum JobReportPlacement`  
_public; L452-463_
- desc: Placement for a job report
- L457 _public* enumerator_ `Panel = 0` — On a panel of its own
- L462 _public* enumerator_ `Summary = 1` — In the summary panel

#### class `EpicGames.Horde.Jobs.GetJobReportResponse`  
`public class GetJobReportResponse`  
_public; L468-508_
- desc: Information about a report associated with a job
- L473 _public property_ `public string Name { get; set; }` — Name of the report
- L478 _public property_ `public JobReportPlacement Placement { get; set; }` — Report placement
- L483 _public property_ `public string? ArtifactId { get; set; }` — The artifact id
- L488 _public property_ `public string? Content { get; set; }` — Content for the report
- L493 _public property_ `public string? Message { get; set; }` — The job/step message
- L498 _public property_ `public string? Severity { get; set; }` — The job/step message severity
- L503-507 _public ctor_ `public GetJobReportResponse(string name, JobReportPlacement placement)` — Constructor

#### class `EpicGames.Horde.Jobs.GetJobResponse`  
`public class GetJobResponse`  
_public; L513-777_
- desc: Information about a job
- L518 _public property_ `public JobId Id { get; set; }` — Unique Id for the job
- L523 _public property_ `public string Name { get; set; }` — Name of the job
- L528 _public property_ `public StreamId StreamId { get; set; }` — Unique id of the stream containing this job
- L534-538 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — The changelist number to build
- L539 _private* field_ `int? _change`
- L544-548 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — The commit to build
- L549 _private* field_ `CommitIdWithOrder? _commitId`
- L555-559 _public property_ `public int? CodeChange { get; set; }` — attrs: `[Obsolete("Use CodeCommitId instead")]` — The code changelist
- L560 _private* field_ `int? _codeChange`
- L565-569 _public property_ `public CommitIdWithOrder? CodeCommitId { get; set; }` — The code commit to build
- L570 _private* field_ `CommitIdWithOrder? _codeCommitId`
- L576-580 _public property_ `public int? PreflightChange { get; set; }` — attrs: `[Obsolete("Use PreflightCommitId instead")]` — The preflight changelist number
- L581 _private* field_ `int? _preflightChange`
- L586-590 _public property_ `public CommitId? PreflightCommitId { get; set; }` — The preflight commit
- L591 _private* field_ `CommitId? _preflightCommitId`
- L596 _public property_ `public string? PreflightDescription { get; set; }` — Description of the preflight
- L601 _public property_ `public TemplateId TemplateId { get; set; }` — The template type
- L606 _public property_ `public string? TemplateHash { get; set; }` — Hash of the actual template data
- L611 _public property_ `public string? GraphHash { get; set; }` — Hash of the graph for this job
- L616 _public property_ `public string? StartedByUserId { get; set; }` — The user that started this job [DEPRECATED]
- L621 _public property_ `public string? StartedByUser { get; set; }` — The user that started this job [DEPRECATED]
- L626 _public property_ `public GetThinUserInfoResponse? StartedByUserInfo { get; set; }` — The user that started this job
- L631 _public property_ `public BisectTaskId? StartedByBisectTaskId { get; set; }` — Bisection task id that started this job
- L636 _public property_ `public string? AbortedByUser { get; set; }` — The user that aborted this job [DEPRECATED]
- L641 _public property_ `public GetThinUserInfoResponse? AbortedByUserInfo { get; set; }` — The user that aborted this job
- L646 _public property_ `public string? CancellationReason { get; set; }` — Optional reason the job was canceled
- L651 _public property_ `public Priority Priority { get; set; }` — Priority of the job
- L656 _public property_ `public bool AutoSubmit { get; set; }` — Whether the change will automatically be submitted or not
- L661 _public property_ `public int? AutoSubmitChange { get; set; }` — The submitted changelist number
- L666 _public property_ `public string? AutoSubmitMessage { get; set; }` — Message produced by trying to auto-submit the change
- L671 _public property_ `public DateTimeOffset CreateTime { get; set; }` — Time that the job was created
- L676 _public property_ `public JobState State { get; set; }` — The global job state
- L681 _public property_ `public List<GetJobBatchResponse>? Batches { get; set; }` — Array of jobstep batches
- L686 _public property_ `public List<GetLabelStateResponse>? Labels { get; set; }` — List of labels
- L691 _public property_ `public GetDefaultLabelStateResponse? DefaultLabel { get; set; }` — The default label, containing the state of all steps that are otherwise not matched.
- L696 _public property_ `public List<GetJobReportResponse>? Reports { get; set; }` — List of reports
- L701 _public property_ `public List<GetJobArtifactResponse>? Artifacts { get; set; }` — Artifacts produced by this job
- L706 _public property_ `public Dictionary<ParameterId, string> Parameters { get; set; }` — Parameters for the job
- L711 _public property_ `public List<string> Arguments { get; set; }` — Command line arguments for the job
- L716 _public property_ `public List<string> AdditionalArguments { get; set; }` — Additional command line arguments for the job for when using the parameters block
- L721 _public property_ `public List<string>? Targets { get; set; }` — Custom list of targets for the job
- L726 _public property_ `public List<string>? Metadata { get; set; }` — List of metadata for this job
- L731 _public property_ `public DateTimeOffset UpdateTime { get; set; }` — The last update time for this job
- L736 _public property_ `public bool UseArtifactsV2 { get; set; }` — Whether to use the V2 artifacts endpoint
- L741 _public property_ `public bool UpdateIssues { get; set; }` — Whether issues are being updated by this job
- L746 _public property_ `public bool CanUpdate { get; set; }` — Whether the current user is allowed to update this job
- L751 _public property_ `public string? ParentJobId { get; set; }` — The parent job id, if any
- L756 _public property_ `public string? ParentJobStepId { get; set; }` — The parent job step id, if any
- L761-767 _public ctor_ `public GetJobResponse(JobId jobId, StreamId streamId, TemplateId templateId, string name)` — Constructor
- L773-776 _public ctor_ `public GetJobResponse()` — attrs: `[JsonConstructor]` — Default constructor needed for JsonSerializer

#### record `EpicGames.Horde.Jobs.GetJobArtifactResponse`  
`public record class GetJobArtifactResponse ( ArtifactId? Id, ArtifactName Name, ArtifactType Type, string? Description, List<string> Keys, List<string> Metadata, JobStepId StepId )`  
_public; L789-789_
- desc: Response describing an artifact produced during a job

#### class `EpicGames.Horde.Jobs.GetJobTimingResponse`  
`public class GetJobTimingResponse`  
_public; L803-832_
- desc: The timing info for a job
- L808 _public property_ `public GetJobResponse? JobResponse { get; set; }` — The job response
- L813 _public property_ `public Dictionary<string, GetStepTimingInfoResponse> Steps { get; set; }` — Timing info for each step
- L818 _public property_ `public List<GetLabelTimingInfoResponse> Labels { get; set; }` — Timing information for each label
- L826-831 _public ctor_ `public GetJobTimingResponse(GetJobResponse? jobResponse, Dictionary<string, GetStepTimingInfoResponse> steps, List<GetLabelTimingInfoResponse> labels)` — Constructor

#### class `EpicGames.Horde.Jobs.FindJobTimingsResponse`  
`public class FindJobTimingsResponse`  
_public; L837-852_
- desc: The timing info for
- L842 _public property_ `public Dictionary<string, GetJobTimingResponse> Timings { get; set; }` — Timing info for each job
- L848-851 _public ctor_ `public FindJobTimingsResponse(Dictionary<string, GetJobTimingResponse> timings)` — Constructor

#### class `EpicGames.Horde.Jobs.UpdateStepRequest`  
`public class UpdateStepRequest`  
_public; L857-898_
- desc: Request used to update a jobstep
- L862 _public property_ `public JobStepState State { get; set; }` — The new jobstep state
- L867 _public property_ `public JobStepOutcome Outcome { get; set; }` — Outcome from the jobstep
- L872 _public property_ `public bool? AbortRequested { get; set; }` — If the step has been requested to abort
- L877 _public property_ `public string? CancellationReason { get; set; }` — Optional reason the job step was canceled
- L882 _public property_ `public string? LogId { get; set; }` — Specifies the log file id for this step
- L887 _public property_ `public bool? Retry { get; set; }` — Whether the step should be re-run
- L892 _public property_ `public Priority? Priority { get; set; }` — New priority for this step
- L897 _public property_ `public Dictionary<string, string?>? Properties { get; set; }` — Properties to set. Any entries with a null value will be removed.

#### class `EpicGames.Horde.Jobs.UpdateStepResponse`  
`public class UpdateStepResponse`  
_public; L903-914_
- desc: Response object when updating a jobstep
- L908 _public property_ `public string? BatchId { get; set; }` — If a new step is created (due to specifying the retry flag), specifies the batch id
- L913 _public property_ `public string? StepId { get; set; }` — If a step is retried, includes the new step id

#### record struct `EpicGames.Horde.Jobs.JobStepOutputRef`  
`public record struct JobStepOutputRef(JobStepId StepId, int OutputIdx)`  
_public; L921-921_
- desc: Reference to the output of a step within the job

#### class `EpicGames.Horde.Jobs.GetJobStepResponse`  
`public class GetJobStepResponse`  
_public; L926-1082_
- desc: Returns information about a jobstep
- L931 _public property_ `public JobStepId Id { get; set; }` — The unique id of the step
- L936 _public property_ `public int NodeIdx { get; set; }` — Index of the node which this jobstep is to execute
- L941 _public property_ `public string Name { get; set; }` — The name of this node
- L946 _public property_ `public bool AllowRetry { get; set; }` — Whether this node can be run multiple times
- L951 _public property_ `public bool RunEarly { get; set; }` — This node can start running early, before dependencies of other nodes in the same group are complete
- L956 _public property_ `public bool Warnings { get; set; }` — Whether to include warnings in the output (defaults to true)
- L961 _public property_ `public List<JobStepOutputRef>? Inputs { get; set; }` — References to inputs for this node
- L966 _public property_ `public List<JobStepOutputRef>? OptionalInputs { get; set; }` — References to optional inputs for this node
- L971 _public property_ `public List<string>? OutputNames { get; set; }` — List of output names
- L976 _public property_ `public List<JobStepId>? InputDependencies { get; set; }` — Indices of nodes which must have succeeded for this node to run
- L981 _public property_ `public List<JobStepId>? OptionalInputDependencies { get; set; }` — Indices of nodes which may have succeeded for this node to run
- L986 _public property_ `public List<JobStepId>? OrderDependencies { get; set; }` — Indices of nodes which must have completed for this node to run
- L991 _public property_ `public IReadOnlyDictionary<string, string>? Credentials { get; set; }` — List of credentials required for this node. Each entry maps an environment variable name to a credential in the form "CredentialName.PropertyName".
- L996 _public property_ `public IReadOnlyDictionary<string, string>? Annotations { get; set; }` — Annotations for this node
- L1001 _public property_ `public List<string>? Metadata { get; set; }` — List of metadata for this step
- L1006 _public property_ `public JobStepState State { get; set; }` — Current state of the job step. This is updated automatically when runs complete.
- L1011 _public property_ `public JobStepOutcome Outcome { get; set; }` — Current outcome of the jobstep
- L1016 _public property_ `public JobStepError Error { get; set; }` — Error describing additional context for why a step failed to complete
- L1021 _public property_ `public bool AbortRequested { get; set; }` — If the step has been requested to abort
- L1026 _public property_ `public string? AbortByUser { get; set; }` — Name of the user that requested the abort of this step [DEPRECATED]
- L1031 _public property_ `public GetThinUserInfoResponse? AbortedByUserInfo { get; set; }` — The user that requested this step be run again
- L1036 _public property_ `public string? CancellationReason { get; set; }` — Optional reason the job step was canceled
- L1041 _public property_ `public string? RetryByUser { get; set; }` — Name of the user that requested this step be run again [DEPRECATED]
- L1046 _public property_ `public GetThinUserInfoResponse? RetriedByUserInfo { get; set; }` — The user that requested this step be run again
- L1051 _public property_ `public string? LogId { get; set; }` — The log id for this step
- L1056 _public property_ `public DateTimeOffset? ReadyTime { get; set; }` — Time at which the batch was ready (UTC).
- L1061 _public property_ `public DateTimeOffset? StartTime { get; set; }` — Time at which the batch started (UTC).
- L1066 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — Time at which the batch finished (UTC)
- L1071 _public property_ `public List<GetJobReportResponse>? Reports { get; set; }` — List of reports
- L1076 _public property_ `public List<string>? SpawnedJobs { get; set; }` — List of spawned job ids
- L1081 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — User-defined properties for this jobstep.

#### enum `EpicGames.Horde.Jobs.JobStepBatchState`  
`public enum JobStepBatchState`  
_public; L1088-1119_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- desc: The state of a particular run
- L1093 _public* enumerator_ `Waiting = 0` — Waiting for dependencies of at least one jobstep to complete
- L1098 _public* enumerator_ `Ready = 1` — Ready to execute
- L1103 _public* enumerator_ `Starting = 2` — Preparing to execute work
- L1108 _public* enumerator_ `Running = 3` — Executing work
- L1113 _public* enumerator_ `Stopping = 4` — Preparing to stop
- L1118 _public* enumerator_ `Complete = 5` — All steps have finished executing

#### enum `EpicGames.Horde.Jobs.JobStepBatchError`  
`public enum JobStepBatchError`  
_public; L1126-1203_
- attrs: `[JsonConverter(typeof(JsonStringEnumConverter))]`
- desc: Error code for a batch not being executed
- L1131 _public* enumerator_ `None = 0` — No error
- L1136 _public* enumerator_ `UnknownStream = 1` — The stream for this job is unknown
- L1141 _public* enumerator_ `UnknownAgentType = 2` — The given agent type for this batch was not valid for this stream
- L1146 _public* enumerator_ `UnknownPool = 3` — The pool id referenced by the agent type was not found
- L1151 _public* enumerator_ `NoAgentsInPool = 4` — There are no agents in the given pool currently online
- L1156 _public* enumerator_ `NoAgentsOnline = 5` — There are no agents in this pool that are onlinbe
- L1161 _public* enumerator_ `UnknownWorkspace = 6` — Unknown workspace referenced by the agent type
- L1166 _public* enumerator_ `Cancelled = 7` — Cancelled
- L1171 _public* enumerator_ `LostConnection = 8` — Lost connection with the agent machine
- L1176 _public* enumerator_ `Incomplete = 9` — Lease terminated prematurely but can be retried.
- L1181 _public* enumerator_ `ExecutionError = 10` — An error ocurred while executing the lease. Cannot be retried.
- L1186 _public* enumerator_ `UnknownShelf = 11` — The change that the job is running against is invalid
- L1191 _public* enumerator_ `NoLongerNeeded = 12` — Step was no longer needed during a job update
- L1196 _public* enumerator_ `SyncingFailed = 13` — Syncing the branch failed
- L1202 _public* enumerator_ `AgentSetupFailed = SyncingFailed` — attrs: `[Obsolete("Use SyncingFailed instead")]` — Legacy alias for SyncingFailed

#### class `EpicGames.Horde.Jobs.UpdateBatchRequest`  
`public class UpdateBatchRequest`  
_public; L1209-1220_
- desc: Request to update a jobstep batch
- L1214 _public property_ `public string? LogId { get; set; }` — The new log file id
- L1219 _public property_ `public JobStepBatchState? State { get; set; }` — The state of this batch

#### class `EpicGames.Horde.Jobs.GetJobBatchResponse`  
`public class GetJobBatchResponse`  
_public; L1225-1306_
- desc: Information about a jobstep batch
- L1230 _public property_ `public JobStepBatchId Id { get; set; }` — Unique id for this batch
- L1235 _public property_ `public int GroupIdx { get; set; }` — Index of the group being executed
- L1240 _public property_ `public string AgentType { get; set; }` — The agent type
- L1245 _public property_ `public string? AgentId { get; set; }` — The agent assigned to execute this group
- L1250 _public property_ `public double? AgentRate { get; set; }` — Rate for using this agent (per hour)
- L1255 _public property_ `public string? SessionId { get; set; }` — The agent session holding this lease
- L1260 _public property_ `public string? LeaseId { get; set; }` — The lease that's executing this group
- L1265 _public property_ `public string? LogId { get; set; }` — The unique log file id
- L1270 _public property_ `public JobStepBatchState State { get; set; }` — The state of this batch
- L1275 _public property_ `public JobStepBatchError Error { get; set; }` — Error code for this batch
- L1280 _public property_ `public int WeightedPriority { get; set; }` — The priority of this batch
- L1285 _public property_ `public DateTimeOffset? StartTime { get; set; }` — Time at which the group started (UTC).
- L1290 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — Time at which the group finished (UTC)
- L1295 _public property_ `public DateTimeOffset? ReadyTime { get; set; }` — Time at which the group became ready (UTC).
- L1300 _public property_ `public List<string>? LeaseOutcomeReasons { get; set; }` — Human-readable names of lease outcome reasons (only populated when batch has an error)
- L1305 _public property_ `public List<GetJobStepResponse> Steps { get; set; }` — Steps within this run

#### enum `EpicGames.Horde.Jobs.LabelState`  
`public enum LabelState`  
_public; L1311-1327_
- desc: State of an aggregate
- L1316 _public* enumerator_ `Unspecified` — Aggregate is not currently being built (no required nodes are present)
- L1321 _public* enumerator_ `Running` — Steps are still running
- L1326 _public* enumerator_ `Complete` — All steps are complete

#### enum `EpicGames.Horde.Jobs.LabelOutcome`  
`public enum LabelOutcome`  
_public; L1332-1353_
- desc: Outcome of an aggregate
- L1337 _public* enumerator_ `Unspecified` — Aggregate is not currently being built
- L1342 _public* enumerator_ `Failure` — A step dependency failed
- L1347 _public* enumerator_ `Warnings` — A dependency finished with warnings
- L1352 _public* enumerator_ `Success` — Successful

#### class `EpicGames.Horde.Jobs.GetLabelStateResponse`  
`public class GetLabelStateResponse`  
_public; L1358-1394_
- desc: State of a label within a job
- L1363 _public property_ `public string? DashboardName { get; set; }` — Name to show for this label on the dashboard
- L1368 _public property_ `public string? DashboardCategory { get; set; }` — Category to show this label in on the dashboard
- L1373 _public property_ `public string? UgsName { get; set; }` — Name to show for this label in UGS
- L1378 _public property_ `public string? UgsProject { get; set; }` — Project to display this label for in UGS
- L1383 _public property_ `public LabelState? State { get; set; }` — State of the label
- L1388 _public property_ `public LabelOutcome? Outcome { get; set; }` — Outcome of the label
- L1393 _public property_ `public List<JobStepId> Steps { get; set; }` — Steps to include in the status of this label

#### class `EpicGames.Horde.Jobs.GetDefaultLabelStateResponse`  
`public class GetDefaultLabelStateResponse : GetLabelStateResponse`  
_public; L1399-1405_
- inherits: `GetLabelStateResponse`
- desc: Information about the default label (ie. with inlined list of nodes)
- L1404 _public property_ `public List<string> Nodes { get; set; }` — List of nodes covered by default label

#### class `EpicGames.Horde.Jobs.GetTimingInfoResponse`  
`public class GetTimingInfoResponse`  
_public; L1410-1441_
- desc: Information about the timing info for a particular target
- L1415 _public property_ `public float? TotalWaitTime { get; set; }` — Wait time on the critical path
- L1420 _public property_ `public float? TotalInitTime { get; set; }` — Sync time on the critical path
- L1425 _public property_ `public float? TotalTimeToComplete { get; set; }` — Duration to this point
- L1430 _public property_ `public float? AverageTotalWaitTime { get; set; }` — Average wait time by the time the job reaches this point
- L1435 _public property_ `public float? AverageTotalInitTime { get; set; }` — Average sync time to this point
- L1440 _public property_ `public float? AverageTotalTimeToComplete { get; set; }` — Average duration to this point

#### class `EpicGames.Horde.Jobs.GetStepTimingInfoResponse`  
`public class GetStepTimingInfoResponse : GetTimingInfoResponse`  
_public; L1446-1467_
- inherits: `GetTimingInfoResponse`
- desc: Information about the timing info for a particular target
- L1451 _public property_ `public string? Name { get; set; }` — Name of this node
- L1456 _public property_ `public float? AverageStepWaitTime { get; set; }` — Average wait time for this step
- L1461 _public property_ `public float? AverageStepInitTime { get; set; }` — Average init time for this step
- L1466 _public property_ `public float? AverageStepDuration { get; set; }` — Average duration for this step

#### class `EpicGames.Horde.Jobs.GetLabelTimingInfoResponse`  
`public class GetLabelTimingInfoResponse : GetTimingInfoResponse`  
_public; L1472-1505_
- inherits: `GetTimingInfoResponse`
- desc: Information about the timing info for a label
- L1478 _public property_ `public string? Name => ...` — attrs: `[Obsolete("Use DashboardName instead")]` — Name of the label
- L1484 _public property_ `public string? Category => ...` — attrs: `[Obsolete("Use DashboardCategory instead")]` — Category for the label
- L1489 _public property_ `public string? DashboardName { get; set; }` — Name of the label
- L1494 _public property_ `public string? DashboardCategory { get; set; }` — Category for the label
- L1499 _public property_ `public string? UgsName { get; set; }` — Name of the label
- L1504 _public property_ `public string? UgsProject { get; set; }` — Category for the label

#### class `EpicGames.Horde.Jobs.GetJobStepRefResponse`  
`public class GetJobStepRefResponse`  
_public; L1510-1602_
- desc: Describes the history of a step
- L1515 _public property_ `public JobId JobId { get; set; }` — The job id
- L1520 _public property_ `public string? StepName { get; set; }` — The step name.
- L1525 _public property_ `public JobStepBatchId BatchId { get; set; }` — The batch containing the step
- L1530 _public property_ `public JobStepId StepId { get; set; }` — The step identifier
- L1536-1540 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — The change number being built
- L1541 _private* field_ `int? _change`
- L1546-1550 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — The commit being built
- L1551 _private* field_ `CommitIdWithOrder? _commitId`
- L1556 _public property_ `public string? LogId { get; set; }` — The step log id
- L1561 _public property_ `public string? PoolId { get; set; }` — The pool id
- L1566 _public property_ `public string? AgentId { get; set; }` — The agent id
- L1571 _public property_ `public JobStepState? State { get; set; }` — The step state.
- L1576 _public property_ `public JobStepOutcome? Outcome { get; set; }` — Outcome of the step, once complete.
- L1581 _public property_ `public List<int>? IssueIds { get; set; }` — The issues which affected this step
- L1586 _public property_ `public List<string>? Metadata { get; set; }` — The step meta data for this step
- L1591 _public property_ `public DateTimeOffset JobStartTime { get; set; }` — Time at which the job started
- L1596 _public property_ `public DateTimeOffset StartTime { get; set; }` — Time at which the step started.
- L1601 _public property_ `public DateTimeOffset? FinishTime { get; set; }` — Time at which the step finished.

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepBatchId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.JobStepBatchId`  
`public readonly record struct JobStepBatchId(SubResourceId SubResourceId)`  
_public; L16-34_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(SubResourceIdTypeConverter<JobStepBatchId, JobStepBatchIdConverter>))] [SubResourceIdConverter(typeof(JobStepBatchIdConverter))]`
- desc: Identifier for a job step batch
- L21-22 _public ctor_ `public JobStepBatchId(ushort value) : this(new SubResourceId(value))` — Constructor
- L27 _public method_ `public static JobStepBatchId GenerateNewId()` — Creates a new JobId
- L30 _public method_ `public static JobStepBatchId Parse(string text)` — (inheritdoc)
- L33 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.JobStepBatchIdConverter`  
`class JobStepBatchIdConverter : SubResourceIdConverter<JobStepBatchId>`  
_internal*; L39-46_
- inherits: `SubResourceIdConverter<JobStepBatchId>`
- desc: Converter to and from SubResourceId instances.
- L42 _public method_ `public override JobStepBatchId FromSubResourceId(SubResourceId subResourceId)` — (inheritdoc)
- L45 _public method_ `public override SubResourceId ToSubResourceId(JobStepBatchId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepError.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.JobStepError`  
`public enum JobStepError`  
_public; L8-29_
- desc: Systemic error codes for a job step failing
- L13 _public* enumerator_ `None` — No systemic error
- L18 _public* enumerator_ `TimedOut` — Step did not complete in the required amount of time
- L23 _public* enumerator_ `Paused` — Step is in is paused state so was skipped
- L28 _public* enumerator_ `Incomplete` — Step did not complete because the batch exited

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.JobStepId`  
`public readonly record struct JobStepId(SubResourceId Id)`  
_public; L16-49_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(SubResourceIdTypeConverter<JobStepId, JobStepIdConverter>))] [SubResourceIdConverter(typeof(JobStepIdConverter))]`
- desc: Identifier for a jobstep
- L21-22 _public ctor_ `public JobStepId(ushort value) : this(new SubResourceId(value))` — Constructor
- L27 _public method_ `public static JobStepId GenerateNewId()` — Creates a new JobId
- L30 _public method_ `public static JobStepId Parse(string text)` — (inheritdoc)
- L33-45 _public method_ `public static bool TryParse(string text, out JobStepId stepId)` — (inheritdoc)
- L48 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.JobStepIdConverter`  
`class JobStepIdConverter : SubResourceIdConverter<JobStepId>`  
_internal*; L54-61_
- inherits: `SubResourceIdConverter<JobStepId>`
- desc: Converter to and from SubResourceId instances.
- L57 _public method_ `public override JobStepId FromSubResourceId(SubResourceId id)` — (inheritdoc)
- L60 _public method_ `public override SubResourceId ToSubResourceId(JobStepId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepOutcome.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.JobStepOutcome`  
`public enum JobStepOutcome`  
_public; L8-29_
- desc: Outcome for a jobstep
- L13 _public* enumerator_ `Unspecified = 0` — Outcome is not known
- L18 _public* enumerator_ `Failure = 1` — Step failed
- L23 _public* enumerator_ `Warnings = 2` — Step completed with warnings
- L28 _public* enumerator_ `Success = 3` — Step succeeded

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepRefId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Jobs.JobStepRefId`  
`public struct JobStepRefId : IEquatable<JobStepRefId>, IComparable<JobStepRefId>`  
_public; L11-108_
- inherits: `IEquatable<JobStepRefId>, IComparable<JobStepRefId>`
- desc: Unique id struct for JobStepRef objects. Includes a job id, batch id, and step id to uniquely identify the step.
- L16 _public property_ `public JobId JobId { get; set; }` — The job id
- L21 _public property_ `public JobStepBatchId BatchId { get; set; }` — The batch id within the job
- L26 _public property_ `public JobStepId StepId { get; set; }` — The step id
- L34-39 _public ctor_ `public JobStepRefId(JobId jobId, JobStepBatchId batchId, JobStepId stepId)` — Constructor
- L46-50 _public method_ `public static JobStepRefId Parse(string text)` — Parse a job step id from a string
- L56-59 _public method_ `public override string ToString()` — Formats this id as a string
- L62 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L65 _public method_ `public override bool Equals([NotNullWhen(true)] object? obj)` — (inheritdoc)
- L68-71 _public method_ `public bool Equals(JobStepRefId other)` — (inheritdoc)
- L74-89 _public method_ `public int CompareTo(JobStepRefId other)` — (inheritdoc)
- L92 _public operator_ `public static bool operator ==(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)
- L95 _public operator_ `public static bool operator !=(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)
- L98 _public operator_ `public static bool operator <(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)
- L101 _public operator_ `public static bool operator >(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)
- L104 _public operator_ `public static bool operator <=(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)
- L107 _public operator_ `public static bool operator >=(JobStepRefId lhs, JobStepRefId rhs)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/JobStepState.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.JobStepState`  
`public enum JobStepState`  
_public; L8-44_
- desc: State of a job step
- L13 _public* enumerator_ `Unspecified = 0` — Unspecified
- L18 _public* enumerator_ `Waiting = 1` — Waiting for dependencies of this step to complete (or paused)
- L23 _public* enumerator_ `Ready = 2` — Ready to run, but has not been scheduled yet
- L28 _public* enumerator_ `Skipped = 3` — Dependencies of this step failed, so it cannot be executed
- L33 _public* enumerator_ `Running = 4` — There is an active instance of this step running
- L38 _public* enumerator_ `Completed = 5` — This step has been run
- L43 _public* enumerator_ `Aborted = 6` — This step started to execute, but was aborted

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Priority.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.Priority`  
`public enum Priority`  
_public; L8-44_
- desc: Priority of a job or step
- L13 _public* enumerator_ `Unspecified = 0` — Not specified
- L18 _public* enumerator_ `Lowest = 1` — Lowest priority
- L23 _public* enumerator_ `BelowNormal = 2` — Below normal priority
- L28 _public* enumerator_ `Normal = 3` — Normal priority
- L33 _public* enumerator_ `AboveNormal = 4` — Above normal priority
- L38 _public* enumerator_ `High = 5` — High priority
- L43 _public* enumerator_ `Highest = 6` — Highest priority

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Schedules/ISchedule.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Schedules.ISchedule`  
`public interface ISchedule`  
_public; L14-80_
- desc: Schedule for a template
- L19 _public* property_ `bool Enabled { get; }` — Whether the schedule should be enabled
- L24 _public* property_ `int MaxActive { get; }` — Maximum number of builds that can be active at once
- L29 _public* property_ `int MaxChanges { get; }` — Maximum number of changes the schedule can fall behind head revision. If greater than zero, builds will be triggered for every submitted changelist until the backlog is this size.
- L34 _public* property_ `bool RequireSubmittedChange { get; }` — Whether the build requires a change to be submitted
- L39 _public* property_ `IScheduleGate? Gate { get; }` — Gate allowing the schedule to trigger
- L44 _public* property_ `IReadOnlyList<CommitTag> Commits { get; }` — Commit tags for this schedule
- L49 _public* property_ `IReadOnlyList<IScheduleClaim>? Claims { get; }` — Roles to impersonate for this schedule
- L54 _public* property_ `CommitIdWithOrder? LastTriggerCommitId { get; }` — Last changelist number that this was triggered for
- L59 _public* property_ `DateTime LastTriggerTimeUtc { get; }` — Gets the last trigger time, in UTC
- L64 _public* property_ `IReadOnlyList<JobId> ActiveJobs { get; }` — List of jobs that are currently active
- L69 _public* property_ `IReadOnlyList<ISchedulePattern> Patterns { get; }` — Patterns for starting this scheduled job
- L74 _public* property_ `IReadOnlyList<string>? Files { get; }` — Files that should cause the job to trigger
- L79 _public* property_ `IReadOnlyDictionary<string, string> TemplateParameters { get; }` — Parameters for the template

#### interface `EpicGames.Horde.Jobs.Schedules.IScheduleClaim`  
`public interface IScheduleClaim`  
_public; L85-96_
- desc: Claim granted to a schedule
- L90 _public* property_ `string Type { get; }` — The claim type
- L95 _public* property_ `string Value { get; }` — The claim value

#### interface `EpicGames.Horde.Jobs.Schedules.IScheduleGate`  
`public interface IScheduleGate`  
_public; L101-112_
- desc: Required gate for starting a schedule
- L106 _public* property_ `TemplateId TemplateId { get; }` — The template containing the dependency
- L111 _public* property_ `string Target { get; }` — Target to wait for

#### interface `EpicGames.Horde.Jobs.Schedules.ISchedulePattern`  
`public interface ISchedulePattern`  
_public; L117-138_
- desc: Pattern for executing a schedule
- L122 _public* property_ `IReadOnlyList<DayOfWeek>? DaysOfWeek { get; }` — Days of the week to run this schedule on. If null, the schedule will run every day.
- L127 _public* property_ `ScheduleTimeOfDay MinTime { get; }` — Time during the day for the first schedule to trigger. Measured in minutes from midnight.
- L132 _public* property_ `ScheduleTimeOfDay? MaxTime { get; }` — Time during the day for the last schedule to trigger. Measured in minutes from midnight.
- L137 _public* property_ `ScheduleInterval? Interval { get; }` — Interval between each schedule triggering

#### class `EpicGames.Horde.Jobs.Schedules.ScheduleExtensions`  
`public static class ScheduleExtensions`  
_public; L143-224_
- desc: Extension methods for schedules
- L151-154 _public method_ `public static DateTime? GetNextTriggerTimeUtc(this ISchedule schedule, TimeZoneInfo timeZone)` — Gets the next trigger time for a schedule
- L163-175 _public method_ `public static DateTime? GetNextTriggerTimeUtc(this ISchedule schedule, DateTime lastTimeUtc, TimeZoneInfo timeZone)` — Get the next time that the schedule will trigger
- L184-223 _public method_ `public static DateTime GetNextTriggerTimeUtc(this ISchedulePattern pattern, DateTime lastTimeUtc, TimeZoneInfo timeZone)` — Calculates the trigger index based on the given time in minutes

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Schedules/ScheduleInterval.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Jobs.Schedules.ScheduleInterval`  
`public record class ScheduleInterval(int Minutes)`  
_public; L17-25_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(ScheduleIntervalJsonConverter))]`
- desc: Time of day value for a schedule
- L23 _public method_ `public static ScheduleInterval? Parse(string? text)` — attrs: `[return: NotNullIfNotNull(nameof(text))]` — Parse a string as a time of day

#### class `EpicGames.Horde.Jobs.Schedules.ScheduleIntervalJsonConverter`  
`class ScheduleIntervalJsonConverter : JsonConverter<ScheduleInterval>`  
_internal*; L27-47_
- inherits: `JsonConverter<ScheduleInterval>`
- L30-40 _public method_ `public override ScheduleInterval? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L43-46 _public method_ `public override void Write(Utf8JsonWriter writer, ScheduleInterval value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Schedules/ScheduleMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Jobs.Schedules.GetScheduleResponse`  
`public class GetScheduleResponse`  
_public; L17-139_
- desc: Response describing a schedule
- L22 _public property_ `public bool Enabled { get; set; }` — Whether the schedule is currently enabled
- L27 _public property_ `public int MaxActive { get; set; }` — Maximum number of scheduled jobs at once
- L32 _public property_ `public int MaxChanges { get; set; }` — Maximum number of changes the schedule can fall behind head revision. If greater than zero, builds will be triggered for every submitted changelist until the backlog is this size.
- L37 _public property_ `public bool RequireSubmittedChange { get; set; }` — Whether the build requires a change to be submitted
- L42 _public property_ `public GetScheduleGateResponse? Gate { get; set; }` — Gate for this schedule to trigger
- L47 _public property_ `public List<CommitTag>? Commits { get; set; }` — Which commits to run this job for
- L52 _public property_ `public Dictionary<string, string> TemplateParameters { get; set; }` — Parameters for the template
- L57 _public property_ `public List<GetSchedulePatternResponse> Patterns { get; set; }` — New patterns for the schedule
- L63-67 _public property_ `public int LastTriggerChange { get; set; }` — attrs: `[Obsolete("Use LastTriggerCommitId instead")]` — Last changelist number that this was triggered for
- L68 _private* field_ `int? _lastTriggerChange`
- L73-77 _public property_ `public CommitIdWithOrder? LastTriggerCommitId { get; set; }` — Last changelist number that this was triggered for
- L78 _private* field_ `CommitIdWithOrder? _lastTriggerCommitId`
- L83 _public property_ `public DateTimeOffset LastTriggerTime { get; set; }` — Last time that the schedule was triggered
- L88 _public property_ `public List<DateTime> NextTriggerTimesUTC { get; set; }` — Next trigger times for schedule
- L93 _public property_ `public List<JobId> ActiveJobs { get; set; }` — List of active jobs
- L98-104 _public ctor_ `public GetScheduleResponse()` — Default constructor
- L111-138 _public ctor_ `public GetScheduleResponse(ISchedule schedule, TimeZoneInfo schedulerTimeZone)` — Constructor

#### class `EpicGames.Horde.Jobs.Schedules.GetScheduleGateResponse`  
`public class GetScheduleGateResponse`  
_public; L144-172_
- desc: Gate allowing a schedule to trigger.
- L149 _public property_ `public TemplateId TemplateId { get; set; }` — The template containing the dependency
- L154 _public property_ `public string Target { get; set; }` — Target to wait for
- L159-162 _public ctor_ `public GetScheduleGateResponse()` — Default constructor
- L167-171 _public ctor_ `public GetScheduleGateResponse(IScheduleGate gate)` — Constructor

#### class `EpicGames.Horde.Jobs.Schedules.GetSchedulePatternResponse`  
`public class GetSchedulePatternResponse`  
_public; L177-216_
- desc: Parameters to create a new schedule
- L182 _public property_ `public List<DayOfWeek>? DaysOfWeek { get; set; }` — Days of the week to run this schedule on. If null, the schedule will run every day.
- L187 _public property_ `public ScheduleTimeOfDay MinTime { get; set; }` — Time during the day for the first schedule to trigger. Measured in minutes from midnight.
- L192 _public property_ `public ScheduleTimeOfDay? MaxTime { get; set; }` — Time during the day for the last schedule to trigger. Measured in minutes from midnight.
- L197 _public property_ `public ScheduleInterval? Interval { get; set; }` — Interval between each schedule triggering
- L202-204 _public ctor_ `public GetSchedulePatternResponse()` — Constructor
- L209-215 _public ctor_ `public GetSchedulePatternResponse(ISchedulePattern pattern)` — Constructor

#### class `EpicGames.Horde.Jobs.Schedules.GetScheduleForecastResponse`  
`public class GetScheduleForecastResponse`  
_public; L221-236_
- desc: Response describing when a schedule is expected to trigger
- L226 _public property_ `public List<DateTime> Times { get; set; }` — Next trigger times
- L232-235 _public ctor_ `public GetScheduleForecastResponse(List<DateTime> times)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Schedules/ScheduleTimeOfDay.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Jobs.Schedules.ScheduleTimeOfDay`  
`public record class ScheduleTimeOfDay(int Minutes)`  
_public; L17-25_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(ScheduleTimeOfDayJsonConverter))]`
- desc: Time of day value for a schedule
- L23 _public method_ `public static ScheduleTimeOfDay? Parse(string? text)` — attrs: `[return: NotNullIfNotNull(nameof(text))]` — Parse a string as a time of day

#### class `EpicGames.Horde.Jobs.Schedules.ScheduleTimeOfDayJsonConverter`  
`class ScheduleTimeOfDayJsonConverter : JsonConverter<ScheduleTimeOfDay>`  
_internal*; L27-47_
- inherits: `JsonConverter<ScheduleTimeOfDay>`
- L30-40 _public method_ `public override ScheduleTimeOfDay? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L43-46 _public method_ `public override void Write(Utf8JsonWriter writer, ScheduleTimeOfDay value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/SubResourceId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Jobs.SubResourceId`  
`public readonly struct SubResourceId : IEquatable<SubResourceId>`  
_public; L17-131_
- attrs: `[TypeConverter(typeof(SubResourceIdTypeConverter))]`
- inherits: `IEquatable<SubResourceId>`
- desc: Identifier for subresources. Assigning unique ids to subresources prevents against race conditions using indices when subresources are added and removed. Subresource identifiers are stored as 16-bit integers formatted as a 4-digit hex code, in order to keep URLs short. Calling Next() will generate a new identifier with more entropy than just incrementing the value but an identical period before repeating, in order to make URL fragments more distinctive.
- L22 _public property_ `public ushort Value { get; }` — The unique identifier value
- L28-31 _public ctor_ `public SubResourceId(ushort value)` — Constructor
- L37-40 _public method_ `public static SubResourceId GenerateNewId()` — Creates a new random subresource id. We use random numbers for this to increase distinctiveness.
- L46-50 _public method_ `public SubResourceId Next()` — Updates the current value, and returns a copy of the previous value.
- L57-60 _public method_ `public static SubResourceId Parse(string text)` — Parse a subresource id from a string
- L68-81 _public method_ `public static bool TryParse(string text, out SubResourceId subResourceId)` — Attempt to parse a subresource id from a string
- L87-90 _public method_ `public override string ToString()` — Converts this identifier to a string
- L93-96 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L99-102 _public method_ `public bool Equals(SubResourceId other)` — (inheritdoc)
- L105-108 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L116-119 _public operator_ `public static bool operator ==(SubResourceId left, SubResourceId right)` — Equality operator for identifiers
- L127-130 _public operator_ `public static bool operator !=(SubResourceId left, SubResourceId right)` — Inequality operator for identifiers

#### class `EpicGames.Horde.Jobs.SubResourceIdExtensions`  
`public static class SubResourceIdExtensions`  
_public; L136-147_
- desc: Extension methods for manipulating subresource ids
- L143-146 _public method_ `public static SubResourceId ToSubResourceId(this string text)` — Parse a string as a subresource identifier

#### class `EpicGames.Horde.Jobs.SubResourceIdTypeConverter`  
`sealed class SubResourceIdTypeConverter : TypeConverter`  
_internal*; L152-184_
- inherits: `TypeConverter`
- desc: Type converter from strings to SubResourceId objects
- L155-158 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L161-164 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L167-170 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L173-183 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/SubResourceIdConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Jobs.SubResourceIdConverter`  
`public abstract class SubResourceIdConverter<T> where T : struct`  
_public; L16-27_
- constraints: `where T : struct`
- desc: Base class for converting to and from types containing a SubResourceId. Useful pattern for reducing boilerplate with strongly typed records.
- L21 _public method_ `public abstract SubResourceId ToSubResourceId(T value)` — Converts a type to a SubResourceId
- L26 _public method_ `public abstract T FromSubResourceId(SubResourceId id)` — Constructs a type from a SubResourceId

#### class `EpicGames.Horde.Jobs.SubResourceIdConverterAttribute`  
`public sealed class SubResourceIdConverterAttribute : Attribute`  
_public; L33-44_
- attrs: `[AttributeUsage(AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute declaring a SubResourceIdConverter{T} for a particular type
- L38 _public property_ `public Type ConverterType { get; }` — The converter type
- L43 _public ctor_ `public SubResourceIdConverterAttribute(Type converterType)` — Constructor

#### class `EpicGames.Horde.Jobs.SubResourceIdTypeConverter`  
`public sealed class SubResourceIdTypeConverter<TValue, TConverter> : TypeConverter where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`  
_public; L49-89_
- inherits: `TypeConverter`
- constraints: `where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`
- desc: Class which serializes types with a SubResourceIdConverter{T} to Json
- L51 _private* field_ `readonly TConverter _converter = new()`
- L54-57 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L60-71 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L74 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L77-88 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.SubResourceIdJsonConverter`  
`public sealed class SubResourceIdJsonConverter<TValue, TConverter> : JsonConverter<TValue> where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`  
_public; L94-103_
- inherits: `JsonConverter<TValue>`
- constraints: `where TValue : struct where TConverter : SubResourceIdConverter<TValue>, new()`
- desc: Class which serializes types with a SubResourceIdConverter{T} to Json
- L96 _private* field_ `readonly TConverter _converter = new()`
- L99 _public method_ `public override TValue Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L102 _public method_ `public override void Write(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.SubResourceIdJsonConverterFactory`  
`public sealed class SubResourceIdJsonConverterFactory : JsonConverterFactory`  
_public; L108-123_
- inherits: `JsonConverterFactory`
- desc: Creates constructors for types with a SubResourceIdConverter{T} to Json
- L111 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L114-122 _public method_ `public override JsonConverter? CreateConverter(Type type, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Templates/ITemplate.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Templates.ITemplate`  
`public interface ITemplate`  
_public; L16-77_
- desc: Document describing a job template. These objects are considered immutable once created and uniquely referenced by hash, in order to de-duplicate across all job runs.
- L21 _public* property_ `ContentHash Hash { get; }` — Hash of this template
- L26 _public* property_ `string Name { get; }` — Name of the template.
- L31 _public* property_ `string? Description { get; }` — Description for the template
- L36 _public* property_ `Priority? Priority { get; }` — Priority of this job
- L41 _public* property_ `bool AllowPreflights { get; }` — Whether to allow preflights for this job type
- L46 _public* property_ `bool UpdateIssues { get; }` — Whether to always issues for jobs using this template
- L51 _public* property_ `bool PromoteIssuesByDefault { get; }` — Whether to promote issues by default for jobs using this template
- L56 _public* property_ `string? InitialAgentType { get; }` — Agent type to use for parsing the job state
- L61 _public* property_ `string? SubmitNewChange { get; }` — Path to a file within the stream to submit to generate a new changelist for jobs
- L66 _public* property_ `string? SubmitDescription { get; }` — Description for new changelists
- L71 _public* property_ `IReadOnlyList<string> Arguments { get; }` — Optional predefined user-defined properties for this job
- L76 _public* property_ `IReadOnlyList<ITemplateParameter> Parameters { get; }` — Parameters for this template

#### interface `EpicGames.Horde.Jobs.Templates.ITemplateParameter`  
`public interface ITemplateParameter`  
_public; L82-98_
- desc: Base class for parameters used to configure templates via the new build dialog
- L90 _public* method_ `void GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)` — Gets the arguments for a job given a set of parameters
- L97 _public* method_ `void GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)` — Gets the default arguments for this parameter and its children

#### interface `EpicGames.Horde.Jobs.Templates.ITemplateBoolParameter`  
`public interface ITemplateBoolParameter : ITemplateParameter`  
_public; L103-149_
- inherits: `ITemplateParameter`
- desc: Allows the user to toggle an option on or off
- L108 _public* property_ `ParameterId Id { get; }` — Identifier for this parameter
- L113 _public* property_ `string Label { get; }` — Label to display next to this parameter.
- L118 _public* property_ `string? ArgumentIfEnabled { get; }` — Argument to add if this parameter is enabled
- L123 _public* property_ `IReadOnlyList<string>? ArgumentsIfEnabled { get; }` — Arguments to add if this parameter is enabled
- L128 _public* property_ `string? ArgumentIfDisabled { get; }` — Argument to add if this parameter is disabled
- L133 _public* property_ `IReadOnlyList<string>? ArgumentsIfDisabled { get; }` — Arguments to add if this parameter is disabled
- L138 _public* property_ `bool Default { get; }` — Whether this option should be enabled by default
- L143 _public* property_ `bool? ScheduleOverride { get; }` — Whether this option should be enabled by default
- L148 _public* property_ `string? ToolTip { get; }` — Tool tip text to display

#### interface `EpicGames.Horde.Jobs.Templates.ITemplateTextParameter`  
`public interface ITemplateTextParameter : ITemplateParameter`  
_public; L154-200_
- inherits: `ITemplateParameter`
- desc: Free-form text entry parameter
- L159 _public* property_ `ParameterId Id { get; }` — Identifier for this parameter
- L164 _public* property_ `string Label { get; }` — Label to display next to this parameter. Should default to the parameter name.
- L169 _public* property_ `string Argument { get; }` — Argument to add (will have the value of this field appended)
- L174 _public* property_ `string Default { get; }` — Default value for this argument
- L179 _public* property_ `string? ScheduleOverride { get; }` — Override for this argument in scheduled builds.
- L184 _public* property_ `string? Hint { get; }` — Hint text to display when the field is empty
- L189 _public* property_ `string? Validation { get; }` — Regex used to validate values entered into this text field.
- L194 _public* property_ `string? ValidationError { get; }` — Message displayed to explain valid values if validation fails.
- L199 _public* property_ `string? ToolTip { get; }` — Tool tip text to display

#### enum `EpicGames.Horde.Jobs.Templates.TemplateListParameterStyle`  
`public enum TemplateListParameterStyle`  
_public; L205-221_
- desc: Style of list parameter
- L210 _public* enumerator_ `List` — Regular drop-down list. One item is always selected.
- L215 _public* enumerator_ `MultiList` — Drop-down list with checkboxes
- L220 _public* enumerator_ `TagPicker` — Tag picker from list of options

#### interface `EpicGames.Horde.Jobs.Templates.ITemplateListParameter`  
`public interface ITemplateListParameter : ITemplateParameter`  
_public; L226-247_
- inherits: `ITemplateParameter`
- desc: Allows the user to select a value from a constrained list of choices
- L231 _public* property_ `string Label { get; }` — Label to display next to this parameter.
- L236 _public* property_ `TemplateListParameterStyle Style { get; }` — Style of picker parameter to use
- L241 _public* property_ `IReadOnlyList<ITemplateListParameterItem> Items { get; }` — List of values to display in the list
- L246 _public* property_ `string? ToolTip { get; }` — Tool tip text to display

#### interface `EpicGames.Horde.Jobs.Templates.ITemplateListParameterItem`  
`public interface ITemplateListParameterItem`  
_public; L252-298_
- desc: Possible option for a list parameter
- L257 _public* property_ `ParameterId Id { get; }` — Identifier for this parameter
- L262 _public* property_ `string? Group { get; }` — Group to display this entry in
- L267 _public* property_ `string Text { get; }` — Text to display for this option.
- L272 _public* property_ `string? ArgumentIfEnabled { get; }` — Argument to add if this parameter is enabled.
- L277 _public* property_ `IReadOnlyList<string>? ArgumentsIfEnabled { get; }` — Arguments to add if this parameter is enabled.
- L282 _public* property_ `string? ArgumentIfDisabled { get; }` — Argument to add if this parameter is disabled.
- L287 _public* property_ `IReadOnlyList<string>? ArgumentsIfDisabled { get; }` — Arguments to add if this parameter is disabled.
- L292 _public* property_ `bool Default { get; }` — Whether this item is selected by default
- L297 _public* property_ `bool? ScheduleOverride { get; }` — Whether this item is selected by default

#### class `EpicGames.Horde.Jobs.Templates.TemplateExtensions`  
`public static class TemplateExtensions`  
_public; L303-329_
- desc: Extension methods for templates
- L308-316 _public method_ `public static void GetArgumentsForParameters(this ITemplate template, IReadOnlyDictionary<ParameterId, string> parameters, List<string> arguments)` — Gets the full argument list for a template
- L322-328 _public method_ `public static void GetDefaultParameters(this ITemplate template, Dictionary<ParameterId, string> parameters, bool scheduledBuild)` — Gets the arguments for default options in this template. Does not include the standard template arguments.

#### interface `EpicGames.Horde.Jobs.Templates.IChangeQuery`  
`public interface IChangeQuery`  
_public; L334-365_
- desc: Query selecting the base changelist to use
- L339 _public* property_ `string? Name { get; }` — Name of this query, for display on the dashboard.
- L344 _public* property_ `Condition? Condition { get; }` — Condition to evaluate before deciding to use this query. May query tags in a preflight.
- L349 _public* property_ `TemplateId? TemplateId { get; }` — The template id to query
- L354 _public* property_ `string? Target { get; }` — The target to query
- L359 _public* property_ `IReadOnlyList<JobStepOutcome>? Outcomes { get; }` — Whether to match a job that produced warnings
- L364 _public* property_ `CommitTag? CommitTag { get; }` — Finds the last commit with this tag

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Templates/ITemplateCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Templates.ITemplateCollection`  
`public interface ITemplateCollection`  
_public; L11-19_
- desc: Interface for a collection of template documents
- L18 _public* method_ `Task<ITemplate?> GetAsync(ContentHash templateId)` — Gets a template by ID

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Templates/ParameterId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.Templates.ParameterId`  
`public record struct ParameterId(StringId Id)`  
_public; L13-28_
- attrs: `[JsonSchemaString] [StringIdConverter(typeof(ParameterIdConverter))]`
- desc: Identifier for a template parameter
- L18-20 _public ctor_ `public ParameterId(string id) : this(new StringId(id))` — Constructor
- L23 _public method_ `public static ParameterId Sanitize(string name)` — (inheritdoc)
- L27 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.Templates.ParameterIdConverter`  
`class ParameterIdConverter : StringIdConverter<ParameterId>`  
_internal*; L33-40_
- inherits: `StringIdConverter<ParameterId>`
- desc: Converter to and from StringId instances.
- L36 _public method_ `public override ParameterId FromStringId(StringId id)` — (inheritdoc)
- L39 _public method_ `public override StringId ToStringId(ParameterId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Templates/TemplateId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Jobs.Templates.TemplateId`  
`public readonly record struct TemplateId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<TemplateId, TemplateIdConverter>))] [StringIdConverter(typeof(TemplateIdConverter))] [CbConverter(typeof(StringIdCbConverter<TemplateId, TemplateIdConverter>))]`
- desc: Identifier for a job template
- L23-25 _public ctor_ `public TemplateId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Jobs.Templates.TemplateIdConverter`  
`class TemplateIdConverter : StringIdConverter<TemplateId>`  
_internal*; L37-44_
- inherits: `StringIdConverter<TemplateId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override TemplateId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(TemplateId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Templates/TemplateMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Jobs.Templates.GetTemplateResponseBase`  
`public class GetTemplateResponseBase`  
_public; L15-106_
- desc: Response describing a template
- L20 _public property_ `public string Name { get; set; }` — Name of the template
- L25 _public property_ `public string? Description { get; set; }` — Description for the template
- L30 _public property_ `public Priority? Priority { get; set; }` — Default priority for this job
- L35 _public property_ `public bool AllowPreflights { get; set; }` — Whether to allow preflights of this template
- L40 _public property_ `public bool UpdateIssues { get; set; }` — Whether to always update issues on jobs using this template
- L45 _public property_ `public string? InitialAgentType { get; set; }` — The initial agent type to parse the BuildGraph script on
- L50 _public property_ `public string? SubmitNewChange { get; }` — Path to a file within the stream to submit to generate a new changelist for jobs
- L55 _public property_ `public List<string> Arguments { get; set; }` — Parameters for the job.
- L60 _public property_ `public List<GetTemplateParameterResponse> Parameters { get; set; }` — List of parameters for this template
- L65-71 _protected ctor_ `protected GetTemplateResponseBase()` — Parameterless constructor for serialization
- L77-88 _public ctor_ `public GetTemplateResponseBase(ITemplate template)` — Constructor
- L90-105 _private* method_ `static GetTemplateParameterResponse CreateParameterResponse(ITemplateParameter parameter)`

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateResponse`  
`public class GetTemplateResponse : GetTemplateResponseBase`  
_public; L111-136_
- inherits: `GetTemplateResponseBase`
- desc: Response describing a template
- L116 _public property_ `public string Id { get; set; }` — Unique id of the template
- L121-125 _protected ctor_ `protected GetTemplateResponse() : base()` — Parameterless constructor for serialization
- L131-135 _public ctor_ `public GetTemplateResponse(ITemplate template) : base(template)` — Constructor

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateParameterResponse`  
`public abstract class GetTemplateParameterResponse : ITemplateParameter`  
_public; L142-149_
- attrs: `[JsonKnownTypes(typeof(GetTemplateBoolParameterResponse), typeof(GetTemplateTextParameterResponse), typeof(GetTemplateListParameterResponse))]`
- inherits: `ITemplateParameter`
- desc: Base class for template parameters
- L144 _private* method_ `void ITemplateParameter.GetArguments(IReadOnlyDictionary<ParameterId, string> parameters, bool scheduledBuild, List<string> arguments)`
- L147 _private* method_ `void ITemplateParameter.GetDefaultParameters(Dictionary<ParameterId, string> parameters, bool scheduledBuild)`

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateBoolParameterResponse`  
`public class GetTemplateBoolParameterResponse : GetTemplateParameterResponse, ITemplateBoolParameter`  
_public; L155-210_
- attrs: `[JsonDiscriminator("Bool")]`
- inherits: `GetTemplateParameterResponse, ITemplateBoolParameter`
- desc: Allows the user to toggle an option on or off
- L158 _public property_ `public ParameterId Id { get; set; }` — (inheritdoc)
- L161 _public property_ `public string Label { get; set; }` — (inheritdoc)
- L164 _public property_ `public string? ArgumentIfEnabled { get; set; }` — (inheritdoc)
- L167 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — (inheritdoc)
- L170 _public property_ `public string? ArgumentIfDisabled { get; set; }` — (inheritdoc)
- L173 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — (inheritdoc)
- L176 _public property_ `public bool Default { get; set; }` — (inheritdoc)
- L179 _public property_ `public bool? ScheduleOverride { get; set; }` — (inheritdoc)
- L182 _public property_ `public string? ToolTip { get; set; }` — (inheritdoc)
- L184 _private* property_ `IReadOnlyList<string>? ITemplateBoolParameter.ArgumentsIfEnabled => ...`
- L185 _private* property_ `IReadOnlyList<string>? ITemplateBoolParameter.ArgumentsIfDisabled => ...`
- L190-193 _public ctor_ `public GetTemplateBoolParameterResponse()` — Default constructor
- L198-209 _public ctor_ `public GetTemplateBoolParameterResponse(ITemplateBoolParameter parameter)` — Constructor

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateTextParameterResponse`  
`public class GetTemplateTextParameterResponse : GetTemplateParameterResponse, ITemplateTextParameter`  
_public; L216-270_
- attrs: `[JsonDiscriminator("Text")]`
- inherits: `GetTemplateParameterResponse, ITemplateTextParameter`
- desc: Free-form text entry parameter
- L219 _public property_ `public ParameterId Id { get; set; }` — (inheritdoc)
- L222 _public property_ `public string Label { get; set; }` — (inheritdoc)
- L225 _public property_ `public string Argument { get; set; }` — (inheritdoc)
- L228 _public property_ `public string Default { get; set; }` — (inheritdoc)
- L231 _public property_ `public string? ScheduleOverride { get; set; }` — (inheritdoc)
- L234 _public property_ `public string? Hint { get; set; }` — (inheritdoc)
- L237 _public property_ `public string? Validation { get; set; }` — (inheritdoc)
- L240 _public property_ `public string? ValidationError { get; set; }` — (inheritdoc)
- L243 _public property_ `public string? ToolTip { get; set; }` — (inheritdoc)
- L248-253 _public ctor_ `public GetTemplateTextParameterResponse()` — Default constructor
- L258-269 _public ctor_ `public GetTemplateTextParameterResponse(ITemplateTextParameter parameter)` — Constructor

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateListParameterResponse`  
`public class GetTemplateListParameterResponse : GetTemplateParameterResponse, ITemplateListParameter`  
_public; L276-311_
- attrs: `[JsonDiscriminator("List")]`
- inherits: `GetTemplateParameterResponse, ITemplateListParameter`
- desc: Allows the user to select a value from a constrained list of choices
- L279 _public property_ `public string Label { get; }` — (inheritdoc)
- L282 _public property_ `public TemplateListParameterStyle Style { get; }` — (inheritdoc)
- L285 _public property_ `public List<GetTemplateListParameterItemResponse> Items { get; set; }` — (inheritdoc)
- L288 _public property_ `public string? ToolTip { get; }` — (inheritdoc)
- L290 _private* property_ `IReadOnlyList<ITemplateListParameterItem> ITemplateListParameter.Items => ...`
- L295-299 _public ctor_ `public GetTemplateListParameterResponse()` — Default constructor
- L304-310 _public ctor_ `public GetTemplateListParameterResponse(ITemplateListParameter parameter)` — Constructor

#### class `EpicGames.Horde.Jobs.Templates.GetTemplateListParameterItemResponse`  
`public class GetTemplateListParameterItemResponse : ITemplateListParameterItem`  
_public; L316-371_
- inherits: `ITemplateListParameterItem`
- desc: Possible option for a list parameter
- L319 _public property_ `public ParameterId Id { get; set; }` — (inheritdoc)
- L322 _public property_ `public string? Group { get; set; }` — (inheritdoc)
- L325 _public property_ `public string Text { get; set; }` — (inheritdoc)
- L328 _public property_ `public string? ArgumentIfEnabled { get; set; }` — (inheritdoc)
- L331 _public property_ `public List<string>? ArgumentsIfEnabled { get; set; }` — (inheritdoc)
- L334 _public property_ `public string? ArgumentIfDisabled { get; set; }` — (inheritdoc)
- L337 _public property_ `public List<string>? ArgumentsIfDisabled { get; set; }` — (inheritdoc)
- L340 _public property_ `public bool Default { get; set; }` — (inheritdoc)
- L343 _public property_ `public bool? ScheduleOverride { get; set; }` — (inheritdoc)
- L345 _private* property_ `IReadOnlyList<string>? ITemplateListParameterItem.ArgumentsIfEnabled => ...`
- L346 _private* property_ `IReadOnlyList<string>? ITemplateListParameterItem.ArgumentsIfDisabled => ...`
- L351-354 _public ctor_ `public GetTemplateListParameterItemResponse()` — Default constructor
- L359-370 _public ctor_ `public GetTemplateListParameterItemResponse(ITemplateListParameterItem item)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Jobs/TestData/TestDataMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Jobs.TestData.TestOutcome`  
`public enum TestOutcome`  
_public; L15-33_
- desc: Test outcome
- L20 _public* enumerator_ `Success` — The test was successful
- L24 _public* enumerator_ `Failure` — The test failed
- L28 _public* enumerator_ `Skipped` — The test was skipped
- L32 _public* enumerator_ `Unspecified` — The test had an unspecified result

#### enum `EpicGames.Horde.Jobs.TestData.TestPhaseOutcome`  
`public enum TestPhaseOutcome`  
_public; L38-64_
- desc: Test phase outcome
- L43 _public* enumerator_ `Failed` — The phase has failed
- L47 _public* enumerator_ `Success` — The phase was successful
- L51 _public* enumerator_ `NotRun` — The phase was not run
- L55 _public* enumerator_ `Interrupted` — The phase was interrupted in its execution
- L59 _public* enumerator_ `Skipped` — The phase was skipped
- L63 _public* enumerator_ `Unknown` — The phase outcome is unknown

#### class `EpicGames.Horde.Jobs.TestData.CreateTestDataRequest`  
`public class CreateTestDataRequest`  
_public; L69-93_
- desc: Response object describing test data to store
- L75 _public property_ `public JobId JobId { get; set; }` — attrs: `[Required]` — The job which produced the data
- L81 _public property_ `public JobStepId StepId { get; set; }` — attrs: `[Required]` — The step that ran
- L86 _public property_ `public string Key { get; set; }` — Key used to identify the particular data
- L92 _public property_ `public Dictionary<string, object> Data { get; set; }` — attrs: `[Required]` — The data stored for this test

#### class `EpicGames.Horde.Jobs.TestData.CreateTestDataResponse`  
`public class CreateTestDataResponse`  
_public; L98-113_
- desc: Response object describing the created document
- L103 _public property_ `public string Id { get; set; }` — The id for the new document
- L109-112 _public ctor_ `public CreateTestDataResponse(string id)` — Constructor

#### class `EpicGames.Horde.Jobs.TestData.GetJobStepTestDataIDResponse`  
`public class GetJobStepTestDataIDResponse`  
_public; L118-139_
- desc: Response object containing the testdata id and the associated test
- L123 _public property_ `public string TestDataId { get; set; }` — The unique testdata id
- L128 _public property_ `public string TestKey { get; set; }` — The test key related to the testdata
- L133 _public property_ `public string TestName { get; set; }` — The test name related to the testdata
- L138 _public property_ `public string TestNameRef { get; set; }` — The test name reference id related to the testdata

#### class `EpicGames.Horde.Jobs.TestData.GetTestDataResponse`  
`public class GetTestDataResponse`  
_public; L144-206_
- desc: Response object describing test results
- L149 _public property_ `public string Id { get; set; }` — Unique id of the test data
- L154 _public property_ `public string StreamId { get; set; }` — Stream that generated the test data
- L159 _public property_ `public string TemplateRefId { get; set; }` — The template reference id
- L164 _public property_ `public string JobId { get; set; }` — The job which produced the data
- L169 _public property_ `public string StepId { get; set; }` — The step that ran
- L175-179 _public property_ `public int Change { get; set; }` — attrs: `[Obsolete("Use CommitId instead")]` — The changelist number that contained the data
- L180 _private* field_ `int? _change`
- L185-189 _public property_ `public CommitIdWithOrder CommitId { get; set; }` — The changelist number that contained the data
- L190 _private* field_ `CommitIdWithOrder? _commitId`
- L195 _public property_ `public CommitId? PreflightCommitId { get; set; }` — The preflight commit id if any
- L200 _public property_ `public string Key { get; set; }` — Key used to identify the particular data
- L205 _public property_ `public Dictionary<string, object> Data { get; set; }` — The data stored for this test

#### class `EpicGames.Horde.Jobs.TestData.GetTestMetaResponse`  
`public class GetTestMetaResponse`  
_public; L211-247_
- desc: A test environment running in a stream
- L216 _public property_ `public string Id { get; set; }` — Meta unique id for environment
- L221 _public property_ `public List<string> Platforms { get; set; }` — The platforms in the environment
- L226 _public property_ `public List<string> Configurations { get; set; }` — The build configurations being tested
- L231 _public property_ `public List<string> BuildTargets { get; set; }` — The build targets being tested
- L236 _public property_ `public string ProjectName { get; set; }` — The test project name
- L241 _public property_ `public string RHI { get; set; }` — The rendering hardware interface being used with the test
- L246 _public property_ `public string Variation { get; set; }` — The variation of the test meta data, for example address sanitizing

#### class `EpicGames.Horde.Jobs.TestData.GetTestResponse`  
`public class GetTestResponse`  
_public; L252-278_
- desc: A test that runs in a stream
- L257 _public property_ `public string Id { get; set; }` — The id of the test
- L262 _public property_ `public string Name { get; set; }` — The name of the test
- L267 _public property_ `public string? DisplayName { get; set; }` — The name of the test
- L272 _public property_ `public string? SuiteName { get; set; }` — The name of the test suite
- L277 _public property_ `public List<string> Metadata { get; set; }` — The meta data the test runs on

#### class `EpicGames.Horde.Jobs.TestData.GetTestsRequest`  
`public class GetTestsRequest`  
_public; L283-289_
- desc: Get tests request
- L288 _public property_ `public List<string> TestIds { get; set; }` — Test ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetStreamTestsRequest`  
`public class GetStreamTestsRequest`  
_public; L294-300_
- desc: Get Tests for streams request
- L299 _public property_ `public List<string> StreamIds { get; set; }` — Stream ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetMetadataRequest`  
`public class GetMetadataRequest`  
_public; L305-316_
- desc: Get test metadata request
- L310 _public property_ `public List<string>? MetadataIds { get; set; }` — Test metadata ids to get
- L315 _public property_ `public Dictionary<string, string>? Entries { get; set; }` — Matching key/value pair Test metadata to get

#### class `EpicGames.Horde.Jobs.TestData.GetTestTagRequest`  
`public class GetTestTagRequest`  
_public; L321-332_
- desc: Get test tag request
- L326 _public property_ `public List<string>? TagIds { get; set; }` — Test tag ids to get
- L331 _public property_ `public List<string>? TagNames { get; set; }` — Test tag name to get

#### class `EpicGames.Horde.Jobs.TestData.GetTestRecipesRequest`  
`public class GetTestRecipesRequest`  
_public; L337-353_
- desc: Get test recipe request
- L342 _public property_ `public List<string>? RecipeIds { get; set; }` — Test recipe ids to get
- L347 _public property_ `public List<string>? TestIds { get; set; }` — Test ids to get
- L352 _public property_ `public List<string>? StreamIds { get; set; }` — Stream ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetTestPhasesRequest`  
`public class GetTestPhasesRequest`  
_public; L358-369_
- desc: Get test phases from test keys and ids request
- L363 _public property_ `public List<string>? TestKeys { get; set; }` — Test keys to get
- L368 _public property_ `public List<string>? TestIds { get; set; }` — Test ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetTestSessionsRequest`  
`public class GetTestSessionsRequest`  
_public; L374-390_
- desc: Get test sessions from streams, tests and optionally meta ids
- L379 _public property_ `public List<string> StreamIds { get; set; }` — Stream ids to get
- L384 _public property_ `public List<string>? TestIds { get; set; }` — Test ids to get
- L389 _public property_ `public List<string>? MetaIds { get; set; }` — Metadata ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetTestHealthReportRequest`  
`public class GetTestHealthReportRequest`  
_public; L395-406_
- desc: Get test health report from streams and tests
- L400 _public property_ `public List<string> StreamIds { get; set; }` — Stream ids to get
- L405 _public property_ `public List<string>? TestIds { get; set; }` — Test ids to get

#### class `EpicGames.Horde.Jobs.TestData.GetPhaseSessionsRequest`  
`public class GetPhaseSessionsRequest`  
_public; L411-422_
- desc: Get phase sessions from stream and phase ids
- L416 _public property_ `public List<string> StreamIds { get; set; }` — Stream ids to get
- L421 _public property_ `public List<string> PhaseIds { get; set; }` — Phase ids to get

#### class `EpicGames.Horde.Jobs.TestData.AddTestAuditRequest`  
`public class AddTestAuditRequest`  
_public; L427-488_
- desc: Add an audit entry for a test
- L432 _public property_ `public string TestId { get; set; }` — The test name reference id
- L437 _public property_ `public bool? EnableSchedule { get; set; }` — Whether or not the test schedules should be enabled
- L442 _public property_ `public DateTimeOffset? LastAuditDate { get; set; }` — The date of the last audit
- L447 _public property_ `public bool? IsUnderAudit { get; set; }` — Whether or not the test is under audit
- L452 _public property_ `public string? Owner { get; set; }` — The owner id of the related test
- L457 _public property_ `public List<string>? Customers { get; set; }` — The customer ids of the related test
- L462 _public property_ `public Dictionary<string, string>? Notifications { get; set; }` — key/value pairs of stream id mapping to workflow id
- L467 _public property_ `public string? Team { get; set; }` — The team for which the test was intended for
- L472 _public property_ `public string? Harness { get; set; }` — The test harness
- L477 _public property_ `public string? Intent { get; set; }` — The intent of the test
- L482 _public property_ `public string? Profile { get; set; }` — The test profile
- L487 _public property_ `public string? Notes { get; set; }` — Additional notes attached to the test audit

#### class `EpicGames.Horde.Jobs.TestData.GetTestAuditRequest`  
`public class GetTestAuditRequest`  
_public; L493-499_
- desc: Get test audit entries for test ids
- L498 _public property_ `public List<string> TestIds { get; set; }` — The test ids

#### class `EpicGames.Horde.Jobs.TestData.GetTestAuditResponse`  
`public class GetTestAuditResponse`  
_public; L504-575_
- desc: A test audit entry
- L509 _public property_ `public string TestId { get; set; }` — The test id
- L514 _public property_ `public string UserId { get; set; }` — The user id that send the test audit
- L519 _public property_ `public DateTime UserInputDate { get; set; }` — The date at which this audit entry was done
- L524 _public property_ `public bool? EnableSchedule { get; set; }` — Whether or not the test schedules should be enabled
- L529 _public property_ `public DateTime? LastAuditDate { get; set; }` — The date of the last audit
- L534 _public property_ `public bool? IsUnderAudit { get; set; }` — Whether or not the test is under audit
- L539 _public property_ `public string? Owner { get; set; }` — The owner id of the related test
- L544 _public property_ `public List<string>? Customers { get; set; }` — The customer ids of the related test
- L549 _public property_ `public Dictionary<string, string>? Notifications { get; set; }` — key/value pairs of stream id mapping to workflow id
- L554 _public property_ `public string? Team { get; set; }` — The team for which the test was intended for
- L559 _public property_ `public string? Harness { get; set; }` — The test harness
- L564 _public property_ `public string? Intent { get; set; }` — The intent of the test
- L569 _public property_ `public string? Profile { get; set; }` — The test profile
- L574 _public property_ `public string? Notes { get; set; }` — Additional notes attached to the test audit

#### class `EpicGames.Horde.Jobs.TestData.GetTestHealthReportResponse`  
`public class GetTestHealthReportResponse`  
_public; L580-636_
- desc: A test health report
- L585 _public property_ `public string Id { get; set; }` — The report id
- L590 _public property_ `public string TestId { get; set; }` — The test id associated to the report
- L595 _public property_ `public string StreamId { get; set; }` — The stream id associated to the report
- L600 _public property_ `public DateTime LastUpdateDate { get; set; }` — The date of the last update
- L605 _public property_ `public bool IsHealthy { get; set; }` — Whether or not the test healthy
- L610 _public property_ `public string State { get; set; }` — The state associated with the test health
- L615 _public property_ `public int SuccessRate { get; set; }` — The success rate of the test health
- L620 _public property_ `public int FailureRate { get; set; }` — The failure rate of the test health
- L625 _public property_ `public int CatastrophicFailureRate { get; set; }` — The catastrophic rate of the test failure
- L630 _public property_ `public int RedundantErrorRate { get; set; }` — The redundant error rate of the test failure
- L635 _public property_ `public DateTime? NotificationLastDate { get; set; }` — The last date of the notification sent

#### class `EpicGames.Horde.Jobs.TestData.GetTestSuiteResponse`  
`public class GetTestSuiteResponse`  
_public; L641-657_
- desc: A test suite that runs in a stream, contain subtests
- L646 _public property_ `public string Id { get; set; }` — The id of the suite
- L651 _public property_ `public string Name { get; set; }` — The name of the test suite
- L656 _public property_ `public List<string> Metadata { get; set; }` — The meta data the test suite runs on

#### class `EpicGames.Horde.Jobs.TestData.GetTestStreamResponse`  
`public class GetTestStreamResponse`  
_public; L662-683_
- desc: Response object describing test results
- L667 _public property_ `public string StreamId { get; set; }` — The stream id
- L672 _public property_ `public List<GetTestResponse> Tests { get; set; }` — Individual tests which run in the stream
- L677 _public property_ `public List<GetTestSuiteResponse> TestSuites { get; set; }` — Test suites that run in the stream
- L682 _public property_ `public List<GetTestMetaResponse> TestMetadata { get; set; }` — Test suites that run in the stream

#### class `EpicGames.Horde.Jobs.TestData.GetSuiteTestDataResponse`  
`public class GetSuiteTestDataResponse`  
_public; L688-719_
- desc: Suite test data
- L693 _public property_ `public string TestId { get; set; }` — The test id
- L698 _public property_ `public TestOutcome Outcome { get; set; }` — The outcome of the suite test
- L703 _public property_ `public TimeSpan Duration { get; set; }` — How long the suite test ran
- L708 _public property_ `public string UID { get; set; }` — Test UID for looking up in test details
- L713 _public property_ `public int? WarningCount { get; set; }` — The number of test warnings generated
- L718 _public property_ `public int? ErrorCount { get; set; }` — The number of test errors generated

#### class `EpicGames.Horde.Jobs.TestData.GetTestDataDetailsResponse`  
`public class GetTestDataDetailsResponse`  
_public; L724-740_
- desc: Test details
- L729 _public property_ `public string Id { get; set; }` — The corresponding test ref
- L734 _public property_ `public List<string> TestDataIds { get; set; }` — The test documents for this ref
- L739 _public property_ `public List<GetSuiteTestDataResponse>? SuiteTests { get; set; }` — Suite test data

#### class `EpicGames.Horde.Jobs.TestData.GetTestDataRefResponse`  
`public class GetTestDataRefResponse`  
_public; L745-835_
- desc: Data ref
- L750 _public property_ `public string Id { get; set; }` — The test ref id
- L755 _public property_ `public string StreamId { get; set; }` — The associated stream
- L760 _public property_ `public string? JobId { get; set; }` — The associated job id
- L765 _public property_ `public string? StepId { get; set; }` — The associated step id
- L770 _public property_ `public TimeSpan Duration { get; set; }` — How long the test ran
- L776-780 _public property_ `public int BuildChangeList { get; set; }` — attrs: `[Obsolete("Use BuildCommitId instead")]` — The build changelist upon which the test ran, may not correspond to the job changelist
- L781 _private* field_ `int? _buildChangeList`
- L787-791 _public property_ `public CommitId BuildCommitId { get; set; }` — The build changelist upon which the test ran, may not correspond to the job changelist
- L794 _private* field_ `CommitId? _buildCommitId`
- L799 _public property_ `public string MetaId { get; set; }` — The platform the test ran on
- L804 _public property_ `public string? TestId { get; set; }` — The test id in stream
- L809 _public property_ `public TestOutcome? Outcome { get; set; }` — The outcome of the test
- L814 _public property_ `public string? SuiteId { get; set; }` — The if of the stream test suite
- L819 _public property_ `public int? SuiteSkipCount { get; set; }` — Suite tests skipped
- L824 _public property_ `public int? SuiteWarningCount { get; set; }` — Suite test warnings
- L829 _public property_ `public int? SuiteErrorCount { get; set; }` — Suite test errors
- L834 _public property_ `public int? SuiteSuccessCount { get; set; }` — Suite test successes

#### class `EpicGames.Horde.Jobs.TestData.GetTestNameResponse`  
`public class GetTestNameResponse`  
_public; L840-876_
- desc: A test name/key ref
- L845 _public property_ `public string Id { get; set; }` — The id of the test
- L850 _public property_ `public string Name { get; set; }` — The name of the test
- L855 _public property_ `public string Key { get; set; }` — The key of the test
- L860 _public property_ `public string? Team { get; set; }` — The team associated with this test
- L865 _public property_ `public string? Intent { get; set; }` — The intent associated with this test
- L870 _public property_ `public string? Harness { get; set; }` — The harness associated with this test
- L875 _public property_ `public string? Profile { get; set; }` — The profile associated with this test

#### class `EpicGames.Horde.Jobs.TestData.GetTestMetadataResponse`  
`public class GetTestMetadataResponse`  
_public; L881-892_
- desc: A set of environment conditions in which a test was run
- L886 _public property_ `public string Id { get; set; }` — Metadata unique id for environment
- L891 _public property_ `public Dictionary<string, string> Entries { get; set; }` — The set of key/value pairs this environment represent

#### class `EpicGames.Horde.Jobs.TestData.GetTestTagResponse`  
`public class GetTestTagResponse`  
_public; L897-908_
- desc: A test tag ref
- L902 _public property_ `public string Id { get; set; }` — Tag unique id
- L907 _public property_ `public string Name { get; set; }` — The name of the tag

#### class `EpicGames.Horde.Jobs.TestData.GetTestRecipeResponse`  
`public class GetTestRecipeResponse`  
_public; L913-964_
- desc: A test recipe ref
- L918 _public property_ `public string Id { get; set; }` — Recipe unique id
- L923 _public property_ `public string NameRef { get; set; }` — The test ref id associated with this recipe
- L928 _public property_ `public string StreamId { get; set; }` — The stream id associated with this recipe
- L933 _public property_ `public string JobTemplateId { get; set; }` — The job template id associated with this recipe
- L938 _public property_ `public string JobStep { get; set; }` — The job step name associated with this recipe
- L943 _public property_ `public string NodeClass { get; set; }` — The test node class associated with this recipe
- L948 _public property_ `public string Version { get; set; }` — The test version associated with this recipe
- L953 _public property_ `public float TimeoutMinutes { get; set; }` — The test timeout in minutes associated with this recipe
- L958 _public property_ `public string? WorkflowId { get; set; }` — The workflow id associated with this recipe
- L963 _public property_ `public Dictionary<string, object>? Params { get; set; }` — The test parameters associated with this recipe

#### class `EpicGames.Horde.Jobs.TestData.GetPhaseResponse`  
`public class GetPhaseResponse`  
_public; L969-985_
- desc: A test phase from a test
- L974 _public property_ `public string Id { get; set; }` — The id of the test phase
- L979 _public property_ `public string Name { get; set; }` — The name of the test phase
- L984 _public property_ `public string Key { get; set; }` — The key of the test phase

#### class `EpicGames.Horde.Jobs.TestData.GetTestPhaseResponse`  
`public class GetTestPhaseResponse`  
_public; L990-1011_
- desc: All test phases from a test
- L995 _public property_ `public string TestId { get; set; }` — The id of the test phase
- L1000 _public property_ `public string TestName { get; set; }` — The name of the test phase
- L1005 _public property_ `public string TestKey { get; set; }` — The key of the test phase
- L1010 _public property_ `public List<GetPhaseResponse> Phases { get; set; }` — The phases associated with the test

#### class `EpicGames.Horde.Jobs.TestData.GetTestSessionStreamResponse`  
`public class GetTestSessionStreamResponse`  
_public; L1016-1037_
- desc: Response object describing test results
- L1021 _public property_ `public string StreamId { get; set; }` — The stream id
- L1026 _public property_ `public List<GetTestNameResponse> Tests { get; set; }` — Individual tests which run in the stream
- L1031 _public property_ `public List<GetTestMetadataResponse> TestMetadata { get; set; }` — Known test metadata
- L1036 _public property_ `public List<GetTestTagResponse> TestTags { get; set; }` — Known test tags

#### class `EpicGames.Horde.Jobs.TestData.GetTestSessionResponse`  
`public class GetTestSessionResponse`  
_public; L1042-1138_
- desc: Response object for a test session
- L1047 _public property_ `public string Id { get; set; }` — The test session id
- L1052 _public property_ `public string StreamId { get; set; }` — The stream id associated with the test session
- L1057 _public property_ `public string MetadataId { get; set; }` — Test metadata id associated with the test session
- L1062 _public property_ `public string TestDataId { get; set; }` — The test data id associated with the test session
- L1067 _public property_ `public string[]? TagIds { get; set; }` — The list of tag ids associated with the test session
- L1072 _public property_ `public string CommitId { get; set; }` — The commit id associated with the test session
- L1077 _public property_ `public int CommitOrder { get; set; }` — The commit order associated with the test session
- L1082 _public property_ `public double Duration { get; set; }` — The duration of the test session
- L1087 _public property_ `public DateTime StartDateTime { get; set; }` — The date time at which the test session started
- L1092 _public property_ `public string NameRef { get; set; }` — The test name reference associated with the test session
- L1097 _public property_ `public string? RecipeId { get; set; }` — The recipe id associated with the test session
- L1102 _public property_ `public TestOutcome Outcome { get; set; }` — The outcome of the test session
- L1107 _public property_ `public int PhasesTotalCount { get; set; }` — The total count of phases
- L1112 _public property_ `public int PhasesSucceededCount { get; set; }` — The count of succeeded phases
- L1117 _public property_ `public int PhasesUndefinedCount { get; set; }` — The count of undefined phases
- L1122 _public property_ `public int PhasesFailedCount { get; set; }` — The count of failed phases
- L1127 _public property_ `public string JobId { get; set; }` — The job id associated with the test session
- L1132 _public property_ `public string StepId { get; set; }` — The step job id associated with the test session
- L1137 _public property_ `public List<GetErrorFingerprintResponse>? ErrorFingerprints { get; set; }` — The error fingerprints associated with the test session

#### class `EpicGames.Horde.Jobs.TestData.GetErrorFingerprintResponse`  
`public class GetErrorFingerprintResponse`  
_public; L1143-1154_
- desc: Response object for error fingerprints
- L1148 _public property_ `public string Key { get; set; }` — The error fingerprint key
- L1153 _public property_ `public List<string> Phases { get; set; }` — The phase keys associated with the error fingerprint

#### class `EpicGames.Horde.Jobs.TestData.GetTestPhaseSessionResponse`  
`public class GetTestPhaseSessionResponse`  
_public; L1159-1240_
- desc: Response object for a test phase session
- L1164 _public property_ `public string Id { get; set; }` — The phase session id
- L1169 _public property_ `public string StreamId { get; set; }` — The stream id associated with the phase session
- L1174 _public property_ `public string MetadataId { get; set; }` — Test metadata id associated with the phase session
- L1179 _public property_ `public string SessionId { get; set; }` — The test session id associated with the phase session
- L1184 _public property_ `public string[]? TagIds { get; set; }` — The list of tag ids associated with the phase session
- L1189 _public property_ `public string CommitId { get; set; }` — The commit id associated with the phase session
- L1194 _public property_ `public int CommitOrder { get; set; }` — The commit order associated with the phase session
- L1199 _public property_ `public double Duration { get; set; }` — The duration of the phase session
- L1204 _public property_ `public DateTime StartDateTime { get; set; }` — The date time at which the phase session started
- L1209 _public property_ `public string PhaseRef { get; set; }` — The test phase reference associated with the phase session
- L1214 _public property_ `public TestPhaseOutcome Outcome { get; set; }` — The outcome of the phase session
- L1219 _public property_ `public string JobId { get; set; }` — The job id associated with the phase session
- L1224 _public property_ `public string StepId { get; set; }` — The step job id associated with the phase session
- L1229 _public property_ `public string? EventStreamPath { get; set; }` — The path to the event stream
- L1234 _public property_ `public bool? HasWarning { get; set; }` — Whether the test phase encountered at least one warning
- L1239 _public property_ `public string? ErrorFingerprint { get; set; }` — The error fingerprint from the event stream

### `Source/Programs/Shared/EpicGames.Horde/Jobs/Timing/IJobTiming.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Jobs.Timing.IJobTiming`  
`public interface IJobTiming`  
_public; L11-21_
- desc: Timing information for a particular job
- L20 _public method_ `public bool TryGetStepTiming(string name, ILogger logger, [NotNullWhen(true)] out IJobStepTiming? timing)` — Gets timing information for a particular step

#### interface `EpicGames.Horde.Jobs.Timing.IJobStepTiming`  
`public interface IJobStepTiming`  
_public; L26-42_
- desc: Information about the timing for an individual step
- L31 _public property_ `public float? AverageWaitTime { get; }` — Wait time before executing the group containing this node
- L36 _public property_ `public float? AverageInitTime { get; }` — Time taken for the group containing this node to initialize
- L41 _public property_ `public float? AverageDuration { get; }` — Time spent executing this node

### `Source/Programs/Shared/EpicGames.Horde/Logs/IServerLogger.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Logs.IServerLogger`  
`public interface IServerLogger : ILogger, IAsyncDisposable`  
_public; L12-18_
- inherits: `ILogger, IAsyncDisposable`
- desc: Interface for a log device
- L17 _public* method_ `Task StopAsync()` — Flushes the logger with the server and stops the background work

#### class `EpicGames.Horde.Logs.ServerLoggerExtensions`  
`public static class ServerLoggerExtensions`  
_public; L23-70_
- desc: Extension methods for IServerLogger
- L66-69 _public method_ `public static IServerLogger WithLocalLogger(this IServerLogger serverLogger, ILogger localLogger)` — Creates a logger which uploads data to the server

#### class `EpicGames.Horde.Logs.ServerLoggerExtensions.ServerLoggerWithLeaseLogger`  
`sealed class ServerLoggerWithLeaseLogger : IServerLogger`  
_private*; L25-58_
- inherits: `IServerLogger`
- L27 _private* field_ `readonly IServerLogger _serverLogger`
- L28 _private* field_ `readonly ILogger _localLogger`
- L30-34 _public ctor_ `public ServerLoggerWithLeaseLogger(IServerLogger serverLogger, ILogger localLogger)`
- L37 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L41 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L45 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L49-53 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L56 _public method_ `public Task StopAsync()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogChunkNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.LogChunkNode`  
`public class LogChunkNode`  
_public; L18-172_
- attrs: `[BlobConverter(typeof(LogChunkConverter))]`
- desc: Read-only buffer for log text, with indexed line offsets.
- L23 _public property_ `public static BlobType BlobType { get; }` — Type of this blob when serialized
- L56 _public property_ `public static LogChunkNode Empty { get; }` — Empty log chunk
- L61 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — The raw text data. Contains a complete set of lines followed by newline characters.
- L66 _public property_ `public ReadOnlySpan<byte> Span => ...` — Span for the raw text data.
- L71 _public property_ `public IReadOnlyList<Utf8String> Lines { get; }` — Accessor for the lines in this chunk
- L76 _public property_ `public IReadOnlyList<int> LineOffsets { get; }` — Offsets of lines within the data object, including a sentinel for the end of the data (LineCount + 1 entries).
- L81 _public property_ `public int Length => ...` — Length of this chunk
- L86 _public property_ `public int LineCount => ...` — Number of lines in the block (excluding the sentinel).
- L91-94 _public ctor_ `public LogChunkNode() : this(Empty.Data, Empty.LineOffsets)` — Default constructor
- L100-103 _public ctor_ `public LogChunkNode(ReadOnlyMemory<byte> data) : this(data, FindLineOffsets(data.Span))` — Constructor
- L108-113 _internal ctor_ `internal LogChunkNode(ReadOnlyMemory<byte> data, IReadOnlyList<int> lineOffsets)` — Constructor
- L120 _public method_ `public Utf8String GetLine(int idx)` — Accessor for an individual line
- L127 _public method_ `public Utf8String GetLineWithNewline(int idx)` — Accessor for an individual line, including the trailing newline character
- L134-142 _public method_ `public int GetLineIndexForOffset(int offset)` — Find the line index for a particular offset
- L149-154 _public method_ `public static List<int> FindLineOffsets(ReadOnlySpan<byte> data)` — Creates a new list of line offsets for the given text
- L162-171 _public method_ `public static void UpdateLineOffsets(ReadOnlySpan<byte> data, int start, List<int> lineOffsets)` — Updates the length of this chunk, computing all the newline offsets

#### class `EpicGames.Horde.Logs.LogChunkNode.LinesCollection`  
`class LinesCollection : IReadOnlyList<Utf8String>`  
_private*; L28-51_
- inherits: `IReadOnlyList<Utf8String>`
- desc: Provides access to the lines for this chunk through a list interface
- L30 _private* field_ `readonly LogChunkNode _owner`
- L32 _public ctor_ `public LinesCollection(LogChunkNode owner)`
- L35 _public indexer_ `public Utf8String this[int index]` — (inheritdoc)
- L38 _public property_ `public int Count => ...` — (inheritdoc)
- L41-47 _public method_ `public IEnumerator<Utf8String> GetEnumerator()` — (inheritdoc)
- L50 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### class `EpicGames.Horde.Logs.LogChunkConverter`  
`class LogChunkConverter : BlobConverter<LogChunkNode>`  
_internal*; L177-192_
- inherits: `BlobConverter<LogChunkNode>`
- desc: Converter from log chunks to blobs
- L180-184 _public method_ `public override LogChunkNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L187-191 _public method_ `public override BlobType Write(IBlobWriter writer, LogChunkNode value, BlobSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Logs.LogChunkRef`  
`public class LogChunkRef`  
_public; L197-263_
- desc: Reference to a chunk of text, with information about its placement in the larger log file
- L202 _public property_ `public int LineIndex { get; }` — First line within the file
- L207 _public property_ `public int LineCount { get; }` — Number of lines in this block
- L212 _public property_ `public long Offset { get; }` — Offset within the entire log file
- L217 _public property_ `public int Length { get; }` — Length of this chunk
- L222 _public property_ `public IHashedBlobRef<LogChunkNode> Target { get; }` — Handle to the target chunk
- L232-239 _public ctor_ `public LogChunkRef(int lineIndex, int lineCount, long offset, int length, IHashedBlobRef<LogChunkNode> target)` — Constructor
- L245-252 _public ctor_ `public LogChunkRef(IBlobReader reader)` — Deserializing constructor
- L255-262 _public method_ `public void Serialize(IBlobWriter writer)` — (inheritdoc)

#### class `EpicGames.Horde.Logs.LogChunkBuilder`  
`public class LogChunkBuilder`  
_public; L268-558_
- desc: Builder for LogChunkNode objects.
- L273 _private* field_ `byte[] _data` — Accessor for Data
- L278 _private* field_ `int _length` — Current used length of the buffer
- L283 _private* field_ `readonly List<int> _lineOffsets = [0]` — Offsets of the start of each line within the data
- L288 _public property_ `public int Length => ...` — Current length of the buffer
- L293 _public property_ `public int LineCount => ...` — Number of lines in this buffer
- L298 _public property_ `public int Capacity => ...` — Capacity of the buffer
- L303-306 _public ctor_ `public LogChunkBuilder(int maxLength = 64 * 1024)` — Constructor
- L313-316 _public ctor_ `public LogChunkBuilder(byte[] data, int length) : this(data, length, LogChunkNode.FindLineOffsets(data.AsSpan(0, length)))` — Constructor
- L324-329 _private ctor_ `private LogChunkBuilder(byte[] data, int length, List<int> lineOffsets)` — Constructor
- L334-338 _public method_ `public void Clear()` — Clear the contents of the buffer
- L345 _public method_ `public Utf8String GetLine(int index)` — Gets a line at the given index
- L353-362 _public method_ `public void Append(ReadOnlySpan<byte> textData)` — Create a new chunk data object with the given data appended. The internal buffers are reused, with the assumption that there is no contention over writing to the same location in the chunk.
- L367-381 _public method_ `public void AppendJsonAsPlainText(ReadOnlySpan<byte> inputLine, ILogger logger)` — Appends JSON text from another buffer as plain text in this one
- L386-395 _public method_ `public void AppendJsonAsPlainText(LogChunkNode srcText, int srcLineIndex, int srcLineCount, ILogger logger)` — Appends JSON text from another buffer as plain text in this one
- L401-408 _private* method_ `void CreateOutputSpace(int appendLength)` — Ensure there is a certain amount of space in the output buffer
- L415-426 _private* method_ `static bool IsEmptyOrWhitespace(ReadOnlySpan<byte> input)` — Determines if the given line is empty
- L435-469 _private* method_ `static int ConvertToPlainText(ReadOnlySpan<byte> input, byte[] output, int outputOffset)` — Converts a JSON log line to plain text
- L477-526 _private* method_ `static int UnescapeUtf8(ReadOnlySpan<byte> source, Span<byte> target)` — Unescape a json utf8 string
- L531-537 _public method_ `public void Shrink()` — Shrinks the data allocated by this chunk to the minimum required
- L543-551 _public method_ `public Utf8String[] ToArray()` — Create an array of lines from the text
- L557 _public method_ `public LogChunkNode ToLogChunk()` — Create a LogChunkNode object from the current state

#### class `EpicGames.Horde.Logs.LogChunkSequenceBuilder`  
`class LogChunkSequenceBuilder`  
_internal*; L563-720_
- desc: Builds a sequence of log chunks
- L565 _private* field_ `readonly List<LogChunkNode> _chunks = []`
- L566 _private* field_ `readonly LogChunkBuilder _nextChunkBuilder`
- L567 _private* field_ `int _flushedLength`
- L568 _private* field_ `int _flushedLineCount`
- L573 _public property_ `public int ChunkSize { get; }` — Desired size for each chunk
- L578 _public property_ `public IReadOnlyList<LogChunkNode> Chunks => ...` — The complete chunks. Note that this does not include data which has not yet been flushed.
- L583 _public property_ `public int Length => ...` — Total length of the sequence
- L588 _public property_ `public int LineCount => ...` — Number of lines in this builder
- L594-598 _public ctor_ `public LogChunkSequenceBuilder(int chunkSize)` — Constructor
- L603-609 _public method_ `public void Clear()` — Clear the current contents of the buffer
- L615-624 _public method_ `public void Remove(int count)` — Remove a number of chunks from the start of the builder
- L627-647 _public method_ `public void Append(ReadOnlySpan<byte> textData)` — (inheritdoc)
- L650-670 _public method_ `public void AppendJsonAsPlainText(ReadOnlySpan<byte> textData, ILogger logger)` — (inheritdoc)
- L675-685 _public method_ `public void Flush()` — Flushes the current contents of the builder
- L692-707 _public method_ `public IEnumerable<Utf8String> EnumerateLines(int startIdx = 0)` — Enumerate lines starting at the given index
- L713-719 _private* method_ `void CreateOutputSpace(int requiredSpace)` — Flushes the current chunk if necessary to provide the requested space

#### class `EpicGames.Horde.Logs.LogChunkExtensions`  
`public static class LogChunkExtensions`  
_public; L725-771_
- desc: Extension methods for ILogText
- L733-741 _public method_ `public static int GetChunkForOffset(this IReadOnlyList<LogChunkRef> chunks, long offset)` — Gets the chunk index containing the given offset.
- L749-757 _public method_ `public static int GetChunkForLine(this IReadOnlyList<LogChunkRef> chunks, int lineIndex)` — Gets the starting chunk index for the given line
- L765-770 _public method_ `public static LogChunkNode ConvertJsonToPlainText(this LogChunkNode logText, ILogger logger)` — Converts a log text instance to plain text

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogEventMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Logs.LogEventSeverity`  
`public enum LogEventSeverity`  
_public; L13-34_
- desc: Severity of a log event
- L18 _public* enumerator_ `Unspecified = 0` — Severity is not specified
- L23 _public* enumerator_ `Information = 1` — Information severity
- L28 _public* enumerator_ `Warning = 2` — Warning severity
- L33 _public* enumerator_ `Error = 3` — Error severity

#### class `EpicGames.Horde.Logs.GetBatchLogEventsRequest`  
`public class GetBatchLogEventsRequest`  
_public; L39-55_
- desc: Request to get events for multiple logs at once
- L44 _public property_ `public List<string> LogIds { get; set; }` — Log ids to fetch events for
- L49 _public property_ `public int? Count { get; set; }` — Maximum number of events to return per log. If null, returns all events.
- L54 _public property_ `public LogEventSeverity? Severity { get; set; }` — Severity filter. If specified, only events matching this severity are returned.

#### class `EpicGames.Horde.Logs.BatchLogEventsEntry`  
`public class BatchLogEventsEntry`  
_public; L60-71_
- desc: Events for a single log within a batch response
- L65 _public property_ `public int Total { get; set; }` — Total number of matching events in this log (before count limit)
- L70 _public property_ `public List<GetLogEventResponse> Events { get; set; }` — The returned events (may be truncated by count)

#### class `EpicGames.Horde.Logs.GetBatchLogEventsResponse`  
`public class GetBatchLogEventsResponse`  
_public; L76-82_
- desc: Response containing events grouped by log id
- L81 _public property_ `public Dictionary<string, BatchLogEventsEntry> LogEvents { get; set; }` — Events grouped by log id

#### class `EpicGames.Horde.Logs.GetLogEventResponse`  
`public class GetLogEventResponse`  
_public; L87-118_
- desc: Information about an uploaded event
- L92 _public property_ `public LogId LogId { get; set; }` — Unique id of the log containing this event
- L97 _public property_ `public LogEventSeverity Severity { get; set; }` — Severity of this event
- L102 _public property_ `public int LineIndex { get; set; }` — Index of the first line for this event
- L107 _public property_ `public int LineCount { get; set; }` — Number of lines in the event
- L112 _public property_ `public int? IssueId { get; set; }` — The issue id associated with this event
- L117 _public property_ `public List<JsonElement> Lines { get; set; }` — The structured message data for this event

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Logs.LogId`  
`public readonly record struct LogId(BinaryId Id)`  
_public; L16-43_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<LogId, LogIdConverter>))] [BinaryIdConverter(typeof(LogIdConverter))]`
- desc: Identifier for a log
- L21 _public property_ `public static LogId Empty { get; }` — Constant value for empty user id
- L24 _public method_ `public static LogId Parse(string text)` — (inheritdoc)
- L27-39 _public method_ `public static bool TryParse(string text, out LogId id)` — (inheritdoc)
- L42 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Logs.LogIdConverter`  
`class LogIdConverter : BinaryIdConverter<LogId>`  
_internal*; L48-55_
- inherits: `BinaryIdConverter<LogId>`
- desc: Converter to and from BinaryId instances.
- L51 _public method_ `public override LogId FromBinaryId(BinaryId id)` — (inheritdoc)
- L54 _public method_ `public override BinaryId ToBinaryId(LogId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogIndexNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.LogIndexNode`  
`public class LogIndexNode`  
_public; L32-387_
- attrs: `[BlobConverter(typeof(LogIndexNodeConverter))]`
- desc: Index for a log file. The index consists of a sequence of compressed, plain text blocks (see LogChunkRef, and a set of (ngram, block index) pairs encoded as 64-bit integers (see Logs.NgramSet). Each ngram is a 1-4 byte sequence of utf8 bytes, padded out to 32-bits (see Ngram). When performing a text search, the search term is split into a set of ngrams, and the set queried for blocks containing them all. Matching blocks are decompressed and scanned for matches using a simplified Knuth-Morris-Pratt search. Since alignment of ngrams may not match alignment of ngrams in the search term, we offset the search term by 1-4 bytes and include the union of blocks matching at any offset.
- L37 _public property_ `public NgramSet NgramSet { get; }` — Index for tokens into the block list
- L42 _public property_ `public int NumChunkBits { get; }` — Number of bits in the index devoted to the block index
- L47 _private* field_ `readonly LogChunkRef[] _plainTextChunkRefs` — List of text blocks
- L52 _public property_ `public static LogIndexNode Empty { get; }` — Empty index data
- L57 _public property_ `public IReadOnlyList<LogChunkRef> PlainTextChunkRefs => ...` — Public accessor for the plain text chunks
- L62 _public property_ `public int LineCount => ...` — Number of lines covered by the index
- L67 _public property_ `public long Length => ...` — Length of the text data
- L75-80 _public ctor_ `public LogIndexNode(NgramSet ngramSet, int numChunkBits, LogChunkRef[] plainTextChunkRefs)` — Constructor
- L89-142 _public method_ `public async ValueTask<LogIndexNode> AppendAsync(IBlobWriter writer, IReadOnlyList<LogChunkNode> appendPlainTextChunks, CancellationToken cancellationToken)` — Appends a set of text blocks to this index
- L152-206 _public method_ `public async IAsyncEnumerable<int> SearchAsync(int firstLineIndex, SearchTerm text, SearchStats stats, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — Search for the given text in the index
- L214-304 _private* method_ `IEnumerable<int> EnumeratePossibleChunks(ReadOnlyMemory<byte> text, int lineIndex)` — Search for the given text in the index
- L313-326 _private* method_ `void GetAlignedTokenPredicate(ReadOnlySpan<byte> text, bool allowPartialMatch, HashSet<ulong> tokens, List<Predicate<int>> predicates)` — Gets predicates for matching a token that starts
- L334-357 _private* method_ `void GetUnalignedTokenPredicate(ReadOnlySpan<byte> text, bool allowPartialMatch, List<Predicate<int>> predicates)` — Generates a predicate for matching a token which may or may not start on a regular token boundary
- L366-371 _private* method_ `bool ChunkContainsToken(int chunkIdx, ulong token, ulong tokenMask)` — Tests whether a chunk contains a particular token
- L380-386 _private* method_ `IEnumerable<int> ChunksContainingNgram(ReadOnlySpan<byte> text, int offset, bool allowPartialMatch)` — Tests whether a chunk contains a particular ngram

#### class `EpicGames.Horde.Logs.LogIndexNodeConverter`  
`class LogIndexNodeConverter : BlobConverter<LogIndexNode>`  
_internal*; L389-427_
- inherits: `BlobConverter<LogIndexNode>`
- L394 _public property_ `public static BlobType BlobType { get; }` — Type for serializing index nodes
- L399 _private* const_ `const int CurrentVersion = 1` — Version number for serialized data
- L402-415 _public method_ `public override LogIndexNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L418-426 _public method_ `public override BlobType Write(IBlobWriter writer, LogIndexNode value, BlobSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Logs.LogType`  
`public enum LogType`  
_public; L16-27_
- desc: The type of data stored in this log file
- L21 _public* enumerator_ `Text` — Plain text data
- L26 _public* enumerator_ `Json` — Structured json objects, output as one object per line (without trailing commas)

#### class `EpicGames.Horde.Logs.CreateLogRequest`  
`public class CreateLogRequest`  
_public; L32-38_
- desc: Creates a new log file
- L37 _public property_ `public LogType Type { get; set; }` — Type of the log file

#### class `EpicGames.Horde.Logs.CreateLogResponse`  
`public class CreateLogResponse`  
_public; L43-49_
- desc: Response from creating a log file
- L48 _public property_ `public string Id { get; set; }` — Identifier for the created log file

#### class `EpicGames.Horde.Logs.GetLogResponse`  
`public class GetLogResponse`  
_public; L54-85_
- desc: Response describing a log file
- L59 _public property_ `public LogId Id { get; set; }` — Unique id of the log file
- L64 _public property_ `public JobId JobId { get; set; }` — Unique id of the job for this log file
- L69 _public property_ `public LeaseId? LeaseId { get; set; }` — The lease allowed to write to this log
- L74 _public property_ `public SessionId? SessionId { get; set; }` — The session allowed to write to this log
- L79 _public property_ `public LogType Type { get; set; }` — Type of events stored in this log
- L84 _public property_ `public int LineCount { get; set; }` — Number of lines in the file

#### class `EpicGames.Horde.Logs.SearchLogResponse`  
`public class SearchLogResponse`  
_public; L90-101_
- desc: Response describing a log file
- L95 _public property_ `public List<int> Lines { get; set; }` — List of line numbers containing the search text
- L100 _public property_ `public SearchStats? Stats { get; set; }` — Stats for the search

#### class `EpicGames.Horde.Logs.LogLinesResponse`  
`public class LogLinesResponse`  
_public; L106-132_
- desc: Response when querying for specific lines from a log file
- L111 _public property_ `public int Index { get; set; }` — start index of the lines returned
- L116 _public property_ `public int Count { get; set; }` — Number of lines returned
- L121 _public property_ `public int MaxLineIndex { get; set; }` — Last index of the returned messages
- L126 _public property_ `public LogType Format { get; set; }` — Type of response, Json or Text
- L131 _public property_ `public List<LogLineResponse> Lines { get; set; }` — List of lines received

#### class `EpicGames.Horde.Logs.LogLineResponse`  
`public class LogLineResponse`  
_public; L137-163_
- desc: Response object for individual lines
- L142 _public property_ `public DateTime Time { get; set; }` — Timestamp for log line
- L147 _public property_ `public string? Level { get; set; }` — Level of Message (Information, Warning, Error)
- L152 _public property_ `public string? Message { get; set; }` — Message itself
- L157 _public property_ `public string? Format { get; set; }` — Format string for the message
- L162 _public property_ `public Dictionary<string, string>? Properties { get; set; }` — User-defined properties for this jobstep.

### `Source/Programs/Shared/EpicGames.Horde/Logs/LogNode.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Logs.LogFormat`  
`public enum LogFormat`  
_public; L19-30_
- desc: Format for the log file
- L24 _public* enumerator_ `Text = 0` — Text data
- L29 _public* enumerator_ `Json = 1` — Json data

#### class `EpicGames.Horde.Logs.LogNode`  
`public class LogNode`  
_public; L36-80_
- attrs: `[BlobConverter(typeof(LogNodeConverter))]`
- desc: Represents an entire log
- L41 _public property_ `public LogFormat Format { get; }` — Format for this log file
- L46 _public property_ `public int LineCount { get; }` — Total number of lines
- L51 _public property_ `public long Length { get; }` — Length of the log file
- L56 _public property_ `public IReadOnlyList<LogChunkRef> TextChunkRefs { get; }` — Text blocks for this chunk
- L61 _public property_ `public IHashedBlobRef<LogIndexNode> IndexRef { get; }` — Index for this log
- L66 _public property_ `public bool Complete { get; }` — Whether this log is complete
- L71-79 _public ctor_ `public LogNode(LogFormat format, int lineCount, long length, IReadOnlyList<LogChunkRef> textChunkRefs, IHashedBlobRef<LogIndexNode> indexRef, bool complete)` — Deserializing constructor

#### class `EpicGames.Horde.Logs.LogNodeConverter`  
`class LogNodeConverter : BlobConverter<LogNode>`  
_internal*; L85-117_
- inherits: `BlobConverter<LogNode>`
- desc: Serializer for LogNode types
- L90 _public property_ `public static BlobType BlobType { get; }` — Type of blob when serialized to storage
- L93-103 _public method_ `public override LogNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L106-116 _public method_ `public override BlobType Write(IBlobWriter writer, LogNode value, BlobSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Logs.LogBuilder`  
`public class LogBuilder`  
_public; L123-313_
- desc: Assists building log files through trees of LogNode, LogIndexNode and LogChunkNode nodes. This class is designed to be thread safe, and presents a consistent view to readers and writers.
- L128 _public const_ `public const int DefaultTextBlockLength = 256 * 1024` — Default maximum size for a log text block
- L133 _public const_ `public const int DefaultIndexBlockLength = 64 * 1024` — Default maximum size for an index text block
- L138 _public property_ `public int LineCount => ...` — Number of lines written to the log
- L140 _private* field_ `int _lineCount`
- L141 _private* field_ `readonly LogFormat _format`
- L144 _private* field_ `LogNode? _root`
- L145 _private* field_ `LogIndexNode _index = LogIndexNode.Empty`
- L148 _private* field_ `readonly LogChunkSequenceBuilder _textBuilder`
- L149 _private* field_ `readonly LogChunkSequenceBuilder _indexTextBuilder`
- L152 _private* field_ `readonly Lock _lockObject = new()`
- L155 _private* field_ `readonly ILogger _logger`
- L162-165 _public ctor_ `public LogBuilder(LogFormat format, ILogger logger) : this(format, DefaultTextBlockLength, DefaultIndexBlockLength, logger)` — Constructor
- L174-180 _public ctor_ `public LogBuilder(LogFormat format, int maxTextBlockLength, int maxIndexBlockLength, ILogger logger)` — Constructor
- L188-224 _public method_ `public (int LineIdx, ReadOnlyMemory<byte> Data) ReadTailData(int firstLineIdx, int maxLength)` — Read data from the unflushed log tail
- L230-259 _public method_ `public void WriteData(ReadOnlyMemory<byte> data)` — Append JSON data to the end of the log
- L267-312 _public method_ `public async Task<IHashedBlobRef<LogNode>> FlushAsync(IBlobWriter writer, bool complete, CancellationToken cancellationToken)` — Flushes the written data to the log

#### class `EpicGames.Horde.Logs.LogNodeExtensions`  
`public static class LogNodeExtensions`  
_public; L318-362_
- desc: Extension methods
- L326-333 _public method_ `public static async IAsyncEnumerable<ReadOnlyMemory<byte>> ReadLogAsync(this LogNode logNode, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — Reads lines from a line
- L342-361 _public method_ `public static async IAsyncEnumerable<ReadOnlyMemory<byte>> ReadLogLinesAsync(this LogNode logNode, int index, [EnumeratorCancellation] CancellationToken cancellationToken = default)` — Reads lines from a line

### `Source/Programs/Shared/EpicGames.Horde/Logs/LoggerUtils.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.LoggerUtils`  
`public static class LoggerUtils`  
_public; L11-45_
- desc: Helper methods for logger functionality
- L19-27 _public method_ `public static void MultiLog((ILogger? logger, LogLevel logLevel)[] loggerAndLevels, string message, params object?[] args)` — Helper method to fan a single message out to a list loggers
- L36-44 _public method_ `public static void MultiLog((ILogger? logger, LogLevel logLevel)[] loggerAndLevels, Exception exception, string message, params object?[] args)` — Helper method to fan a single message out to a list loggers

### `Source/Programs/Shared/EpicGames.Horde/Logs/Ngram.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.Ngram`  
`public static class Ngram`  
_public; L10-191_
- desc: Functionality for decomposing log text into ngrams.
- L15 _public const_ `public const int MaxBytes = 4` — Maximum number of bytes in each ngram
- L20 _public const_ `public const int MaxBits = MaxBytes * 8` — Number of bits in each ngram
- L25 _private* field_ `static readonly byte[] s_tokenTypes = GetTokenTypes()` — Lookup from input byte to token type
- L30 _private* field_ `static readonly byte[] s_tokenChars = GetTokenChars()` — Lookup from input byte to token char
- L37-42 _public method_ `public static ulong Read(ReadOnlySpan<byte> text)` — Gets a single token
- L49-74 _public method_ `public static void Decompose(ReadOnlySpan<byte> text, Action<ulong> addNgram)` — Decompose a span of text into tokens
- L81-86 _public method_ `public static NgramSet Decompose(ReadOnlySpan<byte> text)` — Decompose a string to a set of ngrams
- L94-104 _public method_ `public static ReadOnlySpan<byte> GetText(ReadOnlySpan<byte> text, int pos)` — Gets the length of the first token in the given span
- L112-125 _public method_ `public static ulong GetWindowedValue(ReadOnlySpan<byte> text, int offset)` — Gets the length of the first token in the given span
- L134-147 _public method_ `public static ulong GetWindowedMask(ReadOnlySpan<byte> text, int offset, bool allowPartialMatch)` — Gets the length of the first token in the given span
- L153-172 _private* method_ `static byte[] GetTokenTypes()` — Build the lookup table for token types
- L178-190 _private* method_ `static byte[] GetTokenChars()` — Build the lookup table for token types

### `Source/Programs/Shared/EpicGames.Horde/Logs/NgramSet.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.NgramSet`  
`public class NgramSet : IEnumerable<ulong>`  
_public; L25-285_
- inherits: `IEnumerable<ulong>`
- desc: A sparse, space-efficient set of 64-bit values. Implemented as a trie backed by a flat lookup table. Each 64-bit value in the set is decomposed into 4-bit fragments, and each node in the trie contains a 2^4=16-bit mask indicating which child nodes exist. The array of nodes is stored in a flat buffer, with a predictable order, with the children of a particular node stored contiguously, breadth first. Doing so allows constructing a lookup table for the first child of each parent node with a single pass of the buffer, allowing efficient traversal of the tree to satisfy queries. In practice, only the top 32-bits of values stored in the trie are used for encoding ngram information. The bottom 32 bits are used to index a block number, allowing querying the existence of ngrams and their rough location.
- L49 _public delegate_ `public delegate bool VisitorDelegate(ulong value, ulong mask)` — Delegate for filtering values during a tree traversal
- L54 _private* const_ `const int Height = sizeof(ulong) * 2` — Height of the tree
- L59 _public property_ `public IReadOnlyList<ushort> NodeData => ...` — Array of bitmasks for each node in the tree
- L64 _private* field_ `readonly ushort[] _nodeData` — Array of bitmasks for each node in the tree
- L69 _private* field_ `readonly int[] _firstChildIndex` — Array of child offsets for each node. Excludes the last layer of the tree.
- L74 _public property_ `public static NgramSet Empty { get; }` — Empty index definition
- L80-84 _public ctor_ `public NgramSet(ushort[] nodeData)` — Constructor
- L91-115 _public method_ `public bool Contains(ulong value)` — Tests whether the given value is in the trie
- L118-121 _public method_ `public IEnumerator<ulong> GetEnumerator()` — (inheritdoc)
- L124 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L131-194 _public method_ `public IEnumerable<ulong> EnumerateValues(VisitorDelegate predicate)` — Enumerate all values matching a given filter
- L202-205 _public method_ `public IEnumerable<ulong> EnumerateRange(ulong minValue, ulong maxValue)` — Enumerates all values in the trie between the given ranges
- L212-239 _private* method_ `static int[] CreateChildLookup(ushort[] nodeData)` — Creates a lookup for child node offsets from raw node data
- L246-254 _private* method_ `static int CountBits(ushort value)` — Count the number of set bits in the given value
- L261-266 _public method_ `public static NgramSet Read(IMemoryReader reader)` — Read a trie from the given buffer
- L272-275 _public method_ `public void Write(IMemoryWriter writer)` — Write this trie to the given buffer
- L281-284 _public method_ `public int GetSerializedSize()` — Gets the serialized size of this trie

#### struct `EpicGames.Horde.Logs.NgramSet.StackItem`  
`struct StackItem`  
_private*; L30-41_
- desc: Stack item for traversing the tree
- L35 _public field_ `public int _index` — The current node index
- L40 _public field_ `public int _value` — Value in the current node (0-15)

#### class `EpicGames.Horde.Logs.NgramSetExtensions`  
`public static class NgramSetExtensions`  
_public; L290-311_
- desc: Extension methods for serializing tries
- L297-300 _public method_ `public static NgramSet ReadNgramSet(this IMemoryReader reader)` — Read a trie from the given buffer
- L307-310 _public method_ `public static void WriteNgramSet(this IMemoryWriter writer, NgramSet set)` — Write this trie to the given buffer

### `Source/Programs/Shared/EpicGames.Horde/Logs/NgramSetBuilder.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.NgramSetBuilder`  
`public class NgramSetBuilder`  
_public; L10-108_
- desc: Structure used for building compact NgramSet instances
- L23 _private* field_ `readonly Node _root` — The root node
- L28-31 _public ctor_ `public NgramSetBuilder()` — Default constructor
- L37-48 _public method_ `public void Add(ulong value)` — Adds a value to the trie
- L54-72 _public method_ `public bool Contains(ulong value)` — Searches for the given item in the trie
- L78-107 _public method_ `public NgramSet ToNgramSet()` — Creates a NgramSet from this data

#### class `EpicGames.Horde.Logs.NgramSetBuilder.Node`  
`class Node`  
_private*; L15-18_
- desc: Node within the trie
- L17 _public field_ `public Node?[]? _children`

### `Source/Programs/Shared/EpicGames.Horde/Logs/SearchStats.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.SearchStats`  
`public class SearchStats`  
_public; L8-34_
- desc: Stats for a search
- L13 _public property_ `public int NumScannedBlocks { get; set; }` — Number of blocks that were scanned
- L18 _public property_ `public int NumScannedBytes { get; set; }` — Number of bytes that had to be scanned for results
- L23 _public property_ `public int NumSkippedBlocks { get; set; }` — Number of blocks that were skipped
- L28 _public property_ `public int NumDecompressedBlocks { get; set; }` — Number of blocks that had to be decompressed
- L33 _public property_ `public int NumFalsePositiveBlocks { get; set; }` — Number of blocks that were searched but did not contain the search term

### `Source/Programs/Shared/EpicGames.Horde/Logs/SearchTerm.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.SearchTerm`  
`public class SearchTerm`  
_public; L12-143_
- desc: Stores cached information about a utf8 search term
- L17 _public property_ `public string Text { get; }` — The search text
- L22 _public property_ `public ReadOnlyMemory<byte> Bytes { get; }` — The utf-8 bytes to search for
- L27 _private* field_ `readonly byte[] _searchBytes` — Normalized (lowercase) utf-8 bytes to search for
- L32 _private* field_ `readonly byte[] _skipTable` — Skip table for comparisons
- L38-76 _public ctor_ `public SearchTerm(string text)` — Constructor
- L84-95 _public method_ `public static IEnumerable<int> FindOcurrences(ReadOnlyMemory<byte> buffer, SearchTerm text)` — Find all ocurrences of the text in the given buffer
- L104-118 _public method_ `public static int FindNextOcurrence(ReadOnlySpan<byte> buffer, int offset, SearchTerm text)` — Perform a case insensitive search for the next occurerence of the search term in a given buffer
- L127-142 _public method_ `public static bool Matches(ReadOnlySpan<byte> buffer, int offset, SearchTerm text)` — Compare the search term against the given buffer

#### class `EpicGames.Horde.Logs.SearchTextExtensions`  
`public static class SearchTextExtensions`  
_public; L148-184_
- desc: Stores cached information about a utf8 search term
- L156-159 _public method_ `public static IEnumerable<int> FindOcurrences(this ReadOnlyMemory<byte> buffer, SearchTerm text)` — Find all ocurrences of the text in the given buffer
- L168-171 _public method_ `public static int FindNextOcurrence(this ReadOnlySpan<byte> buffer, int offset, SearchTerm text)` — Perform a case sensitive search for the next occurerence of the search term in a given buffer
- L180-183 _public method_ `public static bool Matches(this ReadOnlySpan<byte> buffer, int offset, SearchTerm text)` — Compare the search term against the given buffer

### `Source/Programs/Shared/EpicGames.Horde/Logs/ServerLogPacketBuilder.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.ServerLogPacketBuilder`  
`public class ServerLogPacketBuilder`  
_public; L22-353_
- desc: Utility class to split log events into separate lines and buffer them for writing to the server
- L36 _private* field_ `static readonly string s_messagePropertyName = LogEventPropertyName.Message.ToString()`
- L37 _private* field_ `static readonly string s_formatPropertyName = LogEventPropertyName.Format.ToString()`
- L38 _private* field_ `static readonly string s_linePropertyName = LogEventPropertyName.Line.ToString()`
- L39 _private* field_ `static readonly string s_lineCountPropertyName = LogEventPropertyName.LineCount.ToString()`
- L41 _private* field_ `static readonly Utf8String s_escapedNewline = new("\\n")`
- L43 _private* field_ `readonly List<JsonLogEvent> _logEvents = []`
- L44 _private* field_ `readonly ArrayBufferWriter<byte> _lineWriter`
- L45 _private* field_ `readonly ArrayBufferWriter<byte> _packetWriter`
- L46 _private* field_ `int _packetLength`
- L51 _public property_ `public int PacketLength => ...` — Current packet length
- L56 _public property_ `public int MaxLineLength { get; }` — Maximum length of an individual line
- L61 _public property_ `public int MaxPacketLength { get; }` — Maximum size of a packet
- L68-75 _public ctor_ `public ServerLogPacketBuilder(int maxLineLength = 64 * 1024, int maxPacketLength = 256 * 1024)` — Constructor
- L81-100 _public method_ `public (ReadOnlyMemory<byte>, int) CreatePacket()` — Creates a packet from the current data
- L106-136 _public method_ `public int SanitizeAndWriteEvent(JsonLogEvent jsonLogEvent)` — Writes an event
- L138-160 _private* method_ `int SanitizeAndWriteEventInternal(JsonLogEvent jsonLogEvent)`
- L165-264 _private* method_ `int WriteEventWithFormat(JsonLogEvent jsonLogEvent, JsonObject obj, string format)` — Writes an event with a format string, splitting it into multiple lines if necessary
- L266-297 _private* method_ `static bool TryGetNextMultiLineProperty(string format, Dictionary<string, string> properties, [NotNullWhen(true)] out string? prefix, [NotNullWhen(true)] out string? suffix, [NotNullWhen(true)] out string? propertyName, [NotNullWhen(true)] out string[]? propertyLines)`
- L299-307 _private* method_ `int WriteEventWithMessage(JsonLogEvent jsonLogEvent, JsonObject obj, string message)`
- L309-330 _private* method_ `void WriteSingleEvent(JsonLogEvent jsonLogEvent, JsonObject obj, string message, string? format, int line, int lineCount)`
- L332-352 _private* method_ `void WriteEventInternal(JsonLogEvent jsonLogEvent)`

#### class `EpicGames.Horde.Logs.ServerLogPacketBuilder.FormattedLine`  
`class FormattedLine`  
_private*; L25-34_
- attrs: `[DebuggerDisplay("{Format}")]`
- L27 _public property_ `public string Format { get; set; }`
- L28 _public property_ `public Dictionary<string, string> Properties { get; }`
- L30-33 _public ctor_ `public FormattedLine(string format)`

### `Source/Programs/Shared/EpicGames.Horde/Logs/ServerLogger.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Logs.ServerLogger`  
`sealed class ServerLogger : IServerLogger`  
_internal*; L22-520_
- inherits: `IServerLogger`
- desc: Class to handle uploading log data to the server in the background
- L24 _private* const_ `const int FlushLength = 1024 * 1024`
- L26 _private* field_ `readonly IHordeClient _hordeClient`
- L27 _private* field_ `readonly LogId _logId`
- L28 _private* field_ `readonly LogLevel _minimumLevel`
- L29 _private* field_ `readonly ILogger _internalLogger`
- L30 _private* field_ `readonly LogBuilder _builder`
- L31 _private* field_ `readonly IStorageNamespace _store`
- L32 _private* field_ `readonly IBlobWriter _writer`
- L34 _private* field_ `int _bufferLength`
- L35 _private* field_ `readonly Stopwatch _timeSinceFlush = Stopwatch.StartNew()`
- L36 _private* field_ `readonly TimeSpan _flushInterval`
- L37 _private* field_ `string? _closedByStackTrace`
- L39 _private* const_ `const int MaxErrors = 200`
- L40 _private* const_ `const int MaxWarnings = 200`
- L41 _private* field_ `int _numErrors`
- L42 _private* field_ `int _numWarnings`
- L45 _private* field_ `readonly Task _tailTask`
- L46 _private* field_ `AsyncEvent _tailTaskStop`
- L47 _private* field_ `readonly AsyncEvent _newTailDataEvent = new()`
- L49 _private* field_ `readonly Channel<JsonLogEvent> _dataChannel`
- L50 _private* field_ `Task? _dataWriter`
- L60-76 _public ctor_ `public ServerLogger(IHordeClient hordeClient, LogId logId, LogLevel minimumLevel, ILogger internalLogger, TimeSpan? flushInterval = null)` — Constructor
- L79-83 _public method_ `public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception? exception, Func<TState, Exception?, string> formatter)` — (inheritdoc)
- L86 _public method_ `public bool IsEnabled(LogLevel logLevel)` — (inheritdoc)
- L89 _public method_ `public IDisposable? BeginScope<TState>(TState state) where TState : notnull` — (inheritdoc)
- L92-98 _private method_ `private void WriteFormattedEvent(JsonLogEvent jsonLogEvent)`
- L104-113 _public method_ `public async Task StopAsync()` — Stops the log writer's background task
- L118-148 _public method_ `public async ValueTask DisposeAsync()` — Dispose of this object. Call StopAsync() to stop asynchronously.
- L154-208 _private* method_ `async Task RunDataWriterAsync()` — Upload the log data to the server in the background
- L214-244 _private* method_ `async Task<int> ReadEventsIntoBatchAsync(ServerLogPacketBuilder writer, List<RpcCreateLogEventRequest> events, int nextLineIndex)` — Reads events from the data channel into a packet builder, with a 2-second timeout. Returns the updated next line index.
- L250-266 _private* method_ `void ClassifyAndAddEvent(JsonLogEvent jsonLogEvent, int lineIndex, int lineCount, List<RpcCreateLogEventRequest> events)` — Classifies a log event and adds it to the event list if it is a warning or error (up to the configured maximum for each severity).
- L272-322 _private* method_ `async Task<bool> WaitForDataWithPeriodicFlushAsync(long packetOffset)` — Waits for new data on the channel, periodically flushing buffered output while idle. Returns true if more data is available, or false if the channel has been closed.
- L324-334 _private* method_ `void AddEvent(ReadOnlySpan<byte> span, int lineIndex, int lineCount, LogEventSeverity severity, List<RpcCreateLogEventRequest> events)`
- L336-356 _private* method_ `async Task TickTailAsync()`
- L358-406 _private* method_ `async Task TickTailInternalAsync()`
- L408-419 _private* method_ `static int CountLines(ReadOnlySpan<byte> data)`
- L421-429 _private method_ `private async Task WriteEventsAsync(List<RpcCreateLogEventRequest> events, CancellationToken cancellationToken)`
- L431-451 _private method_ `private async Task WriteOutputAsync(ReadOnlyMemory<byte> data, bool flush, CancellationToken cancellationToken)`
- L455-468 _private* method_ `async Task UpdateLogAsync(IHashedBlobRef target, int lineCount, bool complete, CancellationToken cancellationToken)`
- L470-517 _private* method_ `async Task<int> UpdateLogTailAsync(int tailNext, ReadOnlyMemory<byte> tailData, CancellationToken cancellationToken)`

### `Source/Programs/Shared/EpicGames.Horde/Notifications/NotificationTriggerId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Notifications.NotificationTriggerId`  
`public readonly record struct NotificationTriggerId(BinaryId Id)`  
_public; L16-23_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<NotificationTriggerId, NotificationTriggerIdConverter>))] [BinaryIdConverter(typeof(NotificationTriggerIdConverter))]`
- desc: Unique id for a notification trigger id
- L19 _public method_ `public static NotificationTriggerId Parse(string text)` — (inheritdoc)
- L22 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Notifications.NotificationTriggerIdConverter`  
`class NotificationTriggerIdConverter : BinaryIdConverter<NotificationTriggerId>`  
_internal*; L28-35_
- inherits: `BinaryIdConverter<NotificationTriggerId>`
- desc: Converter class to and from ObjectId values
- L31 _public method_ `public override NotificationTriggerId FromBinaryId(BinaryId id)` — (inheritdoc)
- L34 _public method_ `public override BinaryId ToBinaryId(NotificationTriggerId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/PerformanceTrends/IPerformanceBudget.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.PerformanceTrends.IMetricThreshold`  
`public interface IMetricThreshold`  
_public; L12-34_
- desc: Describes a metric threshold within a performance budget.
- L17 _public* property_ `string TestType { get; }` — The test type this threshold applies to (e.g., "Perf test", "GPU Perf").
- L22 _public* property_ `string MetricName { get; }` — The name of the metric this threshold is for (e.g., "gpuTimeAvg", "frametimeAvg").
- L27 _public* property_ `double ThresholdValue { get; }` — The threshold value for this metric.
- L33 _public* property_ `bool LargerIsWorse { get; }` — Indicates whether a larger value is worse for this metric. True for metrics like frame time (higher = worse), false for metrics like FPS (lower = worse).

#### interface `EpicGames.Horde.PerformanceTrends.IPerformanceBudget`  
`public interface IPerformanceBudget`  
_public; L39-88_
- desc: Describes a performance budget group containing multiple metric thresholds.
- L44 _public* property_ `PerformanceBudgetId Id { get; }` — The unique identifier for this budget.
- L49 _public* property_ `string Name { get; }` — The name of this budget group.
- L54 _public* property_ `string? Description { get; }` — Optional description of this budget group.
- L59 _public* property_ `UserId? Owner { get; }` — Owner of the budget.
- L65 _public* property_ `string ComputedStream { get; }` — The computed stream this budget belongs to. This is typically sourced from the performance data's ComputedStream field (e.g., "++Fortnite+Main").
- L71 _public* property_ `string TestProject { get; }` — The test project name this budget applies to. This corresponds to the "testName" field in the performance trends data.
- L77 _public* property_ `IReadOnlyList<string>? Platforms { get; }` — The platforms this budget applies to. Null or empty means applicable to all platforms.
- L82 _public* property_ `IReadOnlyList<IMetricThreshold> Thresholds { get; }` — The metric thresholds defined in this budget group.
- L87 _public* property_ `DateTime UpdateTimeUtc { get; }` — The last time this budget was updated (UTC).

### `Source/Programs/Shared/EpicGames.Horde/PerformanceTrends/IPerformanceBudgetCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.PerformanceTrends.IPerformanceBudgetCollection`  
`public interface IPerformanceBudgetCollection`  
_public; L13-60_
- desc: Collection interface for managing performance budgets.
- L22 _public* method_ `Task<IPerformanceBudget?> AddPerformanceBudgetAsync(UserId? owner, PerformanceBudgetAddRequest request, CancellationToken cancellationToken)` — Creates a new performance budget.
- L32 _public* method_ `Task<IPerformanceBudget?> UpdatePerformanceBudgetAsync(PerformanceBudgetId budgetId, PerformanceBudgetUpdateRequest request, CancellationToken cancellationToken)` — Updates an existing performance budget.
- L40 _public* method_ `Task<IPerformanceBudget?> GetPerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken)` — Gets a single performance budget by ID.
- L50 _public* method_ `Task<IEnumerable<IPerformanceBudget>> GetPerformanceBudgetsAsync(string computedStream, string? testProject = null, string? platform = null, CancellationToken cancellationToken = default)` — Gets performance budgets matching the specified criteria.
- L59 _public* method_ `Task<bool> DeletePerformanceBudgetAsync(PerformanceBudgetId budgetId, CancellationToken cancellationToken)` — Deletes a performance budget.

### `Source/Programs/Shared/EpicGames.Horde/PerformanceTrends/PerformanceBudgetId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.PerformanceTrends.PerformanceBudgetId`  
`public readonly record struct PerformanceBudgetId(BinaryId Id)`  
_public; L15-27_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<PerformanceBudgetId, PerformanceBudgetIdConverter>))] [BinaryIdConverter(typeof(PerformanceBudgetIdConverter))]`
- desc: Identifier for a performance budget.
- L20 _public property_ `public static PerformanceBudgetId Empty { get; }` — Constant value for an empty performance budget id.
- L23 _public method_ `public static PerformanceBudgetId Parse(string text)` — (inheritdoc)
- L26 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.PerformanceTrends.PerformanceBudgetIdConverter`  
`class PerformanceBudgetIdConverter : BinaryIdConverter<PerformanceBudgetId>`  
_internal*; L32-39_
- inherits: `BinaryIdConverter<PerformanceBudgetId>`
- desc: Converter to and from BinaryId instances.
- L35 _public method_ `public override PerformanceBudgetId FromBinaryId(BinaryId id)` — (inheritdoc)
- L38 _public method_ `public override BinaryId ToBinaryId(PerformanceBudgetId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/PerformanceTrends/PerformanceBudgetMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.PerformanceTrends.PerformanceBudgetRestrictions`  
`public static class PerformanceBudgetRestrictions`  
_public; L13-29_
- desc: Static class that describes performance budget restrictions.
- L18 _public const_ `public const int MaxNameLength = 200` — The maximum budget name length.
- L23 _public const_ `public const int MaxDescriptionLength = 1000` — The maximum budget description length.
- L28 _public const_ `public const int MaxThresholdsCount = 100` — The maximum number of thresholds per budget.

#### record `EpicGames.Horde.PerformanceTrends.MetricThresholdRequest`  
`public record MetricThresholdRequest`  
_public; L36-67_
- desc: DTO for a metric threshold within a budget.
- L41 _public property_ `public string TestType { get; set; }` — The test type this threshold applies to (e.g., "Perf test", "GPU Perf").
- L46 _public property_ `public string MetricName { get; set; }` — The name of the metric this threshold is for (e.g., "gpuTimeAvg", "frametimeAvg").
- L51 _public property_ `public double ThresholdValue { get; set; }` — The threshold value for this metric.
- L58 _public property_ `public bool LargerIsWorse { get; set; }` — Indicates whether a larger value is worse for this metric. True for metrics like frame time (higher = worse), false for metrics like FPS (lower = worse). Defaults to true.
- L63 _public method_ `public bool IsValid()` — Returns whether this threshold request is valid.

#### record `EpicGames.Horde.PerformanceTrends.PerformanceBudgetAddRequest`  
`public record PerformanceBudgetAddRequest`  
_public; L72-129_
- desc: DTO used for requests to add a performance budget.
- L77 _public property_ `public string Name { get; set; }` — The name of this budget group.
- L82 _public property_ `public string? Description { get; set; }` — Optional description of this budget group.
- L87 _public property_ `public string ComputedStream { get; set; }` — The computed stream this budget belongs to (e.g., stream-main or "++Stream+Main").
- L93 _public property_ `public string TestProject { get; set; }` — The test project name this budget applies to. This corresponds to the "testName" field in the performance trends data.
- L100 _public property_ `public List<string>? Platforms { get; set; }` — The platforms this budget applies to. Null or empty means applicable to all platforms.
- L107 _public property_ `public List<MetricThresholdRequest> Thresholds { get; set; }` — The metric thresholds for this budget group.
- L113 _public method_ `public bool IsValidName()` — Returns whether the name is valid.
- L118 _public method_ `public bool IsValidDescription()` — Returns whether the description is valid.
- L123 _public method_ `public bool IsValidThresholds()` — Returns whether the thresholds are valid.
- L128 _public method_ `public bool IsValidAddRequest()` — Returns whether the add request is valid.

#### record `EpicGames.Horde.PerformanceTrends.PerformanceBudgetUpdateRequest`  
`public record PerformanceBudgetUpdateRequest`  
_public; L134-186_
- desc: DTO used for requests to update a performance budget.
- L139 _public property_ `public string? Name { get; set; }` — The name of this budget group (optional for update).
- L144 _public property_ `public string? Description { get; set; }` — Optional description of this budget group (optional for update).
- L151 _public property_ `public List<string>? Platforms { get; set; }` — The platforms this budget applies to (optional for update). Empty list clears platforms (applies to all). Null means no change.
- L159 _public property_ `public List<MetricThresholdRequest>? Thresholds { get; set; }` — The metric thresholds for this budget group (optional for update). Replaces all existing thresholds when provided.
- L165 _public method_ `public bool IsValidName()` — Returns whether the name is valid.
- L170 _public method_ `public bool IsValidDescription()` — Returns whether the description is valid.
- L175 _public method_ `public bool IsValidThresholds()` — Returns whether the thresholds are valid.
- L180 _public method_ `public bool IsValidUpdateRequest()` — Returns whether the update request is valid.
- L185 _public method_ `public bool HasUpdates()` — Returns whether the update request has any updates.

#### class `EpicGames.Horde.PerformanceTrends.MetricThresholdResponse`  
`public class MetricThresholdResponse`  
_public; L191-224_
- desc: Response object for a metric threshold.
- L196 _public property_ `public string TestType { get; init; }` — The test type this threshold applies to.
- L201 _public property_ `public string MetricName { get; init; }` — The name of the metric this threshold is for.
- L206 _public property_ `public double ThresholdValue { get; init; }` — The threshold value for this metric.
- L211 _public property_ `public bool LargerIsWorse { get; init; }` — Indicates whether a larger value is worse for this metric.
- L217-223 _public ctor_ `public MetricThresholdResponse(IMetricThreshold threshold)` — Creates a metric threshold response from a provided threshold.

#### class `EpicGames.Horde.PerformanceTrends.PerformanceBudgetResponse`  
`public class PerformanceBudgetResponse`  
_public; L229-311_
- desc: Response object for performance budgets.
- L234 _public property_ `public PerformanceBudgetId Id { get; init; }` — The unique identifier for this budget.
- L239 _public property_ `public string Name { get; init; }` — The name of this budget group.
- L244 _public property_ `public string? Description { get; init; }` — Optional description of this budget group.
- L249 _public property_ `public GetThinUserInfoResponse? Owner { get; init; }` — The owner of the budget.
- L254 _public property_ `public string ComputedStream { get; init; }` — The computed stream this budget belongs to (e.g., stream-main or "++Stream+Main").
- L259 _public property_ `public string TestProject { get; init; }` — The test project name this budget applies to.
- L265 _public property_ `public List<string>? Platforms { get; init; }` — The platforms this budget applies to. Null or empty means applicable to all platforms.
- L270 _public property_ `public List<MetricThresholdResponse> Thresholds { get; init; }` — The metric thresholds defined in this budget group.
- L275 _public property_ `public DateTime UpdateTimeUtc { get; init; }` — The last updated time of the budget.
- L281-292 _public ctor_ `public PerformanceBudgetResponse(IPerformanceBudget budget)` — Creates a performance budget response from a provided budget.
- L299-310 _public ctor_ `public PerformanceBudgetResponse(IPerformanceBudget budget, GetThinUserInfoResponse owner)` — Creates a performance budget response from a provided budget and owner.

### `Source/Programs/Shared/EpicGames.Horde/Projects/HttpProjectCollection.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Projects.HttpProjectCollection`  
`class HttpProjectCollection : IProjectCollection`  
_internal*; L11-65_
- inherits: `IProjectCollection`
- L42 _private* field_ `readonly IHordeClient _hordeClient`
- L47 _public ctor_ `public HttpProjectCollection(IHordeClient hordeClient)` — Constructor
- L51-56 _public method_ `public async Task<IProject> GetAsync(ProjectId projectId, CancellationToken cancellationToken)` — (inheritdoc)
- L59-64 _public method_ `public async Task<IReadOnlyList<IProject>> GetAllAsync(CancellationToken cancellationToken)` — (inheritdoc)

#### class `EpicGames.Horde.Projects.HttpProjectCollection.Project`  
`class Project : IProject`  
_private*; L14-29_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IProject`
- L16 _private* field_ `readonly GetProjectResponse _response`
- L17 _private* field_ `readonly IReadOnlyList<ProjectStream> _projectStreams`
- L19 _public property_ `public ProjectId Id => ...`
- L20 _public property_ `public string Name => ...`
- L21 _public property_ `public int Order => ...`
- L22 _public property_ `public IReadOnlyList<IProjectStream> Streams => ...`
- L24-28 _public ctor_ `public Project(GetProjectResponse response)`

#### class `EpicGames.Horde.Projects.HttpProjectCollection.ProjectStream`  
`class ProjectStream : IProjectStream`  
_private*; L31-40_
- inherits: `IProjectStream`
- L33 _private* field_ `readonly GetProjectStreamResponse _response`
- L35 _public property_ `public StreamId Id => ...`
- L36 _public property_ `public string Name => ...`
- L38 _public ctor_ `public ProjectStream(GetProjectStreamResponse response)`

### `Source/Programs/Shared/EpicGames.Horde/Projects/IProject.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Projects.IProject`  
`public interface IProject`  
_public; L11-32_
- desc: Handle to a Horde project
- L16 _public* property_ `ProjectId Id { get; }` — Unique id of the project
- L21 _public* property_ `string Name { get; }` — Name of the project
- L26 _public* property_ `int Order { get; }` — Order to display this project on the dashboard
- L31 _public* property_ `IReadOnlyList<IProjectStream> Streams { get; }` — List of streams that are in this project

#### interface `EpicGames.Horde.Projects.IProjectStream`  
`public interface IProjectStream`  
_public; L37-48_
- desc: Describes a stream within a project
- L42 _public* property_ `StreamId Id { get; }` — The stream id
- L47 _public* property_ `string Name { get; }` — The stream name

### `Source/Programs/Shared/EpicGames.Horde/Projects/IProjectCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Projects.IProjectCollection`  
`public interface IProjectCollection`  
_public; L12-28_
- desc: Collection of projects
- L20 _public* method_ `Task<IProject> GetAsync(ProjectId projectId, CancellationToken cancellationToken = default)` — Retrieve information about a specific project
- L27 _public* method_ `Task<IReadOnlyList<IProject>> GetAllAsync(CancellationToken cancellationToken = default)` — Query all the projects

### `Source/Programs/Shared/EpicGames.Horde/Projects/ProjectId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Projects.ProjectId`  
`public readonly record struct ProjectId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<ProjectId, ProjectIdConverter>))] [StringIdConverter(typeof(ProjectIdConverter))] [CbConverter(typeof(StringIdCbConverter<ProjectId, ProjectIdConverter>))]`
- desc: Identifier for a pool
- L23-25 _public ctor_ `public ProjectId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Projects.ProjectIdConverter`  
`public class ProjectIdConverter : StringIdConverter<ProjectId>`  
_public; L37-44_
- inherits: `StringIdConverter<ProjectId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override ProjectId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(ProjectId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Projects/ProjectMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Projects.GetProjectResponse`  
`public class GetProjectResponse`  
_public; L14-53_
- attrs: `[DebuggerDisplay("{Id,nq}")]`
- desc: Response describing a project
- L19 _public property_ `public ProjectId Id { get; set; }` — Unique id of the project
- L24 _public property_ `public string Name { get; set; }` — Name of the project
- L29 _public property_ `public int Order { get; set; }` — Order to display this project on the dashboard
- L34 _public property_ `public List<GetProjectStreamResponse>? Streams { get; set; }` — List of streams that are in this project
- L39 _public property_ `public List<GetProjectCategoryResponse>? Categories { get; set; }` — List of stream categories to display
- L47-52 _public ctor_ `public GetProjectResponse(ProjectId id, string name, int order)` — Constructor

#### class `EpicGames.Horde.Projects.GetProjectStreamResponse`  
`public class GetProjectStreamResponse`  
_public; L59-79_
- attrs: `[DebuggerDisplay("{Id,nq} ({Name})")]`
- desc: Information about a stream within a project
- L64 _public property_ `public string Id { get; set; }` — The stream id
- L69 _public property_ `public string Name { get; set; }` — The stream name
- L74-78 _public ctor_ `public GetProjectStreamResponse(string id, string name)` — Constructor

#### class `EpicGames.Horde.Projects.GetProjectCategoryResponse`  
`public class GetProjectCategoryResponse`  
_public; L85-125_
- attrs: `[DebuggerDisplay("{Name}")]`
- desc: Information about a category to display for a stream
- L90 _public property_ `public string Name { get; set; }` — Heading for this column
- L95 _public property_ `public int Row { get; set; }` — Index of the row to display this category on
- L100 _public property_ `public bool ShowOnNavMenu { get; set; }` — Whether to show this category on the nav menu
- L105 _public property_ `public List<string> IncludePatterns { get; init; }` — Patterns for stream names to include
- L110 _public property_ `public List<string> ExcludePatterns { get; init; }` — Patterns for stream names to exclude
- L115 _public property_ `public List<string> Streams { get; init; }` — Streams to include in this category
- L120-124 _public ctor_ `public GetProjectCategoryResponse(string name, int row)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Properties/AssemblyInfo.cs` (EpicGames.Horde)
_(no declarations)_


### `Source/Programs/Shared/EpicGames.Horde/Replicators/ReplicatorId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Replicators.ReplicatorId`  
`public readonly record struct ReplicatorId(StreamId StreamId, StreamReplicatorId StreamReplicatorId)`  
_public; L21-56_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(ReplicatorIdTypeConverter))] [JsonConverter(typeof(ReplicatorIdJsonConverter))]`
- desc: Unique identifier for a replicator across all streams
- L26-34 _public method_ `public static ReplicatorId Parse(string text)` — Parse a replicator id
- L39-52 _public method_ `public static bool TryParse(string text, out ReplicatorId replicatorId)` — Parse a replicator id
- L55 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Replicators.ReplicatorIdJsonConverter`  
`sealed class ReplicatorIdJsonConverter : JsonConverter<ReplicatorId>`  
_internal*; L58-67_
- inherits: `JsonConverter<ReplicatorId>`
- L61 _public method_ `public override ReplicatorId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L65 _public method_ `public override void Write(Utf8JsonWriter writer, ReplicatorId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Replicators.ReplicatorIdTypeConverter`  
`sealed class ReplicatorIdTypeConverter : TypeConverter`  
_internal*; L69-96_
- inherits: `TypeConverter`
- L72 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L75-82 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L85 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L88-95 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### record struct `EpicGames.Horde.Replicators.StreamReplicatorId`  
`public readonly record struct StreamReplicatorId(StringId Id)`  
_public; L107-121_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<StreamReplicatorId, StreamReplicatorIdConverter>))] [StringIdConverter(typeof(StreamReplicatorIdConverter))] [CbConverter(typeof(StringIdCbConverter<StreamReplicatorId, StreamReplicatorIdConverter>))]`
- desc: Identifier for a replicator
- L112-114 _public ctor_ `public StreamReplicatorId(string id) : this(new StringId(id))` — Constructor
- L117 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L120 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Replicators.StreamReplicatorIdConverter`  
`public class StreamReplicatorIdConverter : StringIdConverter<StreamReplicatorId>`  
_public; L126-133_
- inherits: `StringIdConverter<StreamReplicatorId>`
- desc: Converter to and from StringId instances.
- L129 _public method_ `public override StreamReplicatorId FromStringId(StringId id)` — (inheritdoc)
- L132 _public method_ `public override StringId ToStringId(StreamReplicatorId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Replicators/ReplicatorMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Replicators.GetReplicatorResponse`  
`public class GetReplicatorResponse`  
_public; L11-87_
- desc: Information about a replicator
- L16 _public property_ `public ReplicatorId Id { get; set; }` — Identifier for this replicator
- L21 _public property_ `public StreamId StreamId { get; set; }` — Identifier for the stream
- L26 _public property_ `public StreamReplicatorId StreamReplicatorId { get; set; }` — Identifier for this replicator within the stream
- L31 _public property_ `public string Status { get; set; }` — Status description
- L36 _public property_ `public bool? Pause { get; set; }` — Whether to pause replication
- L41 _public property_ `public bool? Clean { get; set; }` — Whether to perform a clean snapshot
- L46 _public property_ `public bool? Reset { get; set; }` — Resets the replication
- L51 _public property_ `public bool? SingleStep { get; set; }` — Pauses replication after the current change
- L56 _public property_ `public int? LastChange { get; set; }` — The last change that was replicated
- L61 _public property_ `public DateTime? LastChangeFinishTime { get; set; }` — Time at which the last change was replicated
- L66 _public property_ `public int? CurrentChange { get; set; }` — The current change being replicated
- L71 _public property_ `public DateTime? CurrentChangeStartTime { get; set; }` — Time at which the current change was replicated
- L76 _public property_ `public long? CurrentSize { get; set; }` — Size of data currently being replicated
- L81 _public property_ `public long? CurrentCopiedSize { get; set; }` — Amount of data copied for the current change
- L86 _public property_ `public string? CurrentError { get; set; }` — Last error with replication, if there is one.

#### class `EpicGames.Horde.Replicators.UpdateReplicatorRequest`  
`public class UpdateReplicatorRequest`  
_public; L92-118_
- desc: Information about a replicator
- L97 _public property_ `public bool? Pause { get; set; }` — Whether to pause replication immediately
- L102 _public property_ `public bool? Clean { get; set; }` — Whether to perform a clean snapshot for the next replicated change
- L107 _public property_ `public bool? Reset { get; set; }` — Discards all replicated changes and starts replication from scratch
- L112 _public property_ `public bool? SingleStep { get; set; }` — Pauses replication after one change has been replicated
- L117 _public property_ `public int? NextChange { get; set; }` — Change that should be replicated. Setting this to a value ahead of the last replicated change will cause changes inbetween to be skipped.

### `Source/Programs/Shared/EpicGames.Horde/Secrets/HttpSecretCollection.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Secrets.HttpSecretCollection`  
`class HttpSecretCollection : ISecretCollection`  
_internal*; L10-64_
- inherits: `ISecretCollection`
- L35 _private* field_ `readonly IHordeClient _hordeClient`
- L40 _public ctor_ `public HttpSecretCollection(IHordeClient hordeClient)` — Constructor
- L44-49 _public method_ `public async Task<ISecret?> GetAsync(SecretId secretId, CancellationToken cancellationToken)` — (inheritdoc)
- L52-55 _public method_ `public Task<ISecret?> GetAsync(SecretId secretId, object config, CancellationToken cancellationToken)` — (inheritdoc)
- L58-63 _public method_ `public async Task<ISecretProperty?> ResolveAsync(string value, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Secrets.HttpSecretCollection.Secret`  
`class Secret : ISecret`  
_private*; L12-21_
- inherits: `ISecret`
- L14 _private* field_ `readonly GetSecretResponse _response`
- L16 _public property_ `public SecretId Id => ...`
- L17 _public property_ `public IReadOnlyDictionary<string, string> Data => ...`
- L19 _public ctor_ `public Secret(GetSecretResponse response)`

#### class `EpicGames.Horde.Secrets.HttpSecretCollection.SecretProperty`  
`class SecretProperty : ISecretProperty`  
_private*; L23-33_
- inherits: `ISecretProperty`
- L25 _private field_ `private readonly GetSecretPropertyResponse _response`
- L27 _public property_ `public SecretId Id => ...`
- L28 _public property_ `public string Name => ...`
- L29 _public property_ `public string Value => ...`
- L31 _public ctor_ `public SecretProperty(GetSecretPropertyResponse response)`

### `Source/Programs/Shared/EpicGames.Horde/Secrets/ISecret.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Secrets.ISecret`  
`public interface ISecret`  
_public; L10-21_
- desc: Information about a secret
- L15 _public* property_ `SecretId Id { get; }` — Identifier for the secret
- L20 _public* property_ `IReadOnlyDictionary<string, string> Data { get; }` — The secret values

#### interface `EpicGames.Horde.Secrets.ISecretProperty`  
`public interface ISecretProperty`  
_public; L26-42_
- desc: Information about a single property of a secret
- L31 _public* property_ `SecretId Id { get; }` — Identifier for the secret
- L36 _public* property_ `string Name { get; }` — The name of the property from the secret
- L41 _public* property_ `string Value { get; }` — The value of the property from the secret

### `Source/Programs/Shared/EpicGames.Horde/Secrets/ISecretCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Secrets.ISecretCollection`  
`public interface ISecretCollection`  
_public; L11-36_
- desc: Collection of secrets
- L18 _public* method_ `Task<ISecret?> GetAsync(SecretId secretId, CancellationToken cancellationToken = default)` — Resolve a secret to concrete values
- L27 _public* method_ `Task<ISecret?> GetAsync(SecretId secretId, object config, CancellationToken cancellationToken = default)` — Resolve a secret to concrete values
- L35 _public* method_ `Task<ISecretProperty?> ResolveAsync(string value, CancellationToken cancellationToken = default)` — Converts the string representation of a secret and property to a concrete value The format of the string is 'horde:secret:secret-id.property-name'

### `Source/Programs/Shared/EpicGames.Horde/Secrets/SecretId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Secrets.SecretId`  
`public readonly record struct SecretId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<SecretId, SecretIdConverter>))] [StringIdConverter(typeof(SecretIdConverter))] [CbConverter(typeof(StringIdCbConverter<SecretId, SecretIdConverter>))]`
- desc: Identifier for a secret
- L23-25 _public ctor_ `public SecretId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Secrets.SecretIdConverter`  
`class SecretIdConverter : StringIdConverter<SecretId>`  
_internal*; L37-44_
- inherits: `StringIdConverter<SecretId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override SecretId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(SecretId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Secrets/SecretMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Secrets.GetSecretsResponse`  
`public class GetSecretsResponse`  
_public; L13-24_
- desc: Response listing all the secrets available to the current user
- L18 _public property_ `public List<SecretId> Ids { get; set; }` — List of secret ids
- L23 _public ctor_ `public GetSecretsResponse(List<SecretId> ids)` — Constructor

#### class `EpicGames.Horde.Secrets.GetSecretResponse`  
`public class GetSecretResponse`  
_public; L30-50_
- attrs: `[DebuggerDisplay("{Id}")]`
- desc: Gets data for a particular secret
- L35 _public property_ `public SecretId Id { get; }` — Id of the secret
- L40 _public property_ `public Dictionary<string, string> Data { get; set; }` — Key value pairs for the secret
- L45-49 _public ctor_ `public GetSecretResponse(SecretId id, Dictionary<string, string> data)` — Constructor

#### class `EpicGames.Horde.Secrets.GetSecretPropertyResponse`  
`public class GetSecretPropertyResponse`  
_public; L56-82_
- attrs: `[DebuggerDisplay("{Id}")]`
- desc: Gets data for a particular secret and property
- L61 _public property_ `public SecretId Id { get; }` — Id of the secret
- L66 _public property_ `public string Name { get; }` — Name of the property in the secret
- L71 _public property_ `public string Value { get; }` — Value of the property in the secret
- L76-81 _public ctor_ `public GetSecretPropertyResponse(SecretId id, string name, string value)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Server/Notices/NoticeMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Server.Notices.CreateNoticeRequest`  
`public class CreateNoticeRequest`  
_public; L12-37_
- desc: Parameters required to create a notice
- L17 _public property_ `public DateTime? StartTime { get; set; }` — Start time to display this message
- L22 _public property_ `public DateTime? FinishTime { get; set; }` — Finish time to display this message
- L28 _public property_ `public string Message { get; set; }` — attrs: `[Required]` — Message to display
- L33-36 _public ctor_ `public CreateNoticeRequest(string message)` — Constructor

#### class `EpicGames.Horde.Server.Notices.UpdateNoticeRequest`  
`public class UpdateNoticeRequest`  
_public; L42-71_
- desc: Parameters required to update a notice
- L47 _public property_ `public string Id { get; set; }` — The id of the notice to update
- L52 _public property_ `public DateTime? StartTime { get; set; }` — Start time to display this message
- L57 _public property_ `public DateTime? FinishTime { get; set; }` — Finish time to display this message
- L62 _public property_ `public string? Message { get; set; }` — Message to display
- L67-70 _public ctor_ `public UpdateNoticeRequest(string id)` — Constructor

#### class `EpicGames.Horde.Server.Notices.GetNoticeResponse`  
`public class GetNoticeResponse`  
_public; L76-112_
- desc: Notice information
- L81 _public property_ `public string? Id { get; set; }` — The id of the notice to update
- L86 _public property_ `public DateTime? StartTime { get; set; }` — Start time to display this message
- L91 _public property_ `public DateTime? FinishTime { get; set; }` — Finish time to display this message
- L96 _public property_ `public bool ScheduledDowntime { get; set; }` — Whether this notice is for scheduled downtime
- L101 _public property_ `public bool Active { get; set; }` — Whether the notice is currently active
- L106 _public property_ `public string? Message { get; set; }` — Message to display
- L111 _public property_ `public GetThinUserInfoResponse? CreatedByUser { get; set; }` — User id who created the notice, otherwise null if a system message

### `Source/Programs/Shared/EpicGames.Horde/Server/ServerMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Server.GetServerInfoResponse`  
`public class GetServerInfoResponse`  
_public; L13-40_
- desc: Server Info
- L19 _public property_ `public HordeApiVersion ApiVersion { get; set; }` — attrs: `[JsonConverter(typeof(HordeApiVersionConverter))]` — Current API version number of the server
- L24 _public property_ `public string ServerVersion { get; set; }` — Server version info
- L29 _public property_ `public string? AgentVersion { get; set; }` — The current agent version string
- L34 _public property_ `public ServerPluginInfoResponse[] Plugins { get; set; }` — List of plugins
- L39 _public property_ `public string? Environment { get; set; }` — The environment that the server is running in (e.g. "Development", "Production")

#### class `EpicGames.Horde.Server.GetConnectionResponse`  
`public class GetConnectionResponse`  
_public; L45-56_
- desc: Gets connection information to the server
- L50 _public property_ `public string? Ip { get; set; }` — Public IP address of the remote machine
- L55 _public property_ `public int Port { get; set; }` — Public port of the connecting machine

#### class `EpicGames.Horde.Server.GetPortsResponse`  
`public class GetPortsResponse`  
_public; L61-77_
- desc: Gets ports configured for this server
- L66 _public property_ `public int? Http { get; set; }` — Port for HTTP communication
- L71 _public property_ `public int? Https { get; set; }` — Port number for HTTPS communication
- L76 _public property_ `public int? UnencryptedHttp2 { get; set; }` — Port number for unencrpyted HTTPS communication

#### enum `EpicGames.Horde.Server.AuthMethod`  
`public enum AuthMethod`  
_public; L82-105_
- desc: Authentication method used for logging users in
- L87 _public* enumerator_ `Anonymous` — No authentication enabled. *Only* for demo and testing purposes.
- L92 _public* enumerator_ `Okta` — OpenID Connect authentication, tailored for Okta
- L97 _public* enumerator_ `OpenIdConnect` — Generic OpenID Connect authentication, recommended for most
- L104 _public* enumerator_ `Horde` — Authenticate using username and password credentials stored in Horde OpenID Connect (OIDC) is first and foremost recommended. But if you have a small installation (less than ~10 users) or lacking an OIDC provider, this is an option.

#### class `EpicGames.Horde.Server.GetAuthConfigResponse`  
`public class GetAuthConfigResponse`  
_public; L110-141_
- desc: Describes the auth config for this server
- L115 _public property_ `public AuthMethod Method { get; set; }` — Issuer for tokens from the auth provider
- L120 _public property_ `public string? ProfileName { get; set; }` — Optional profile name used by OidcToken
- L125 _public property_ `public string? ServerUrl { get; set; }` — Issuer for tokens from the auth provider
- L130 _public property_ `public string? ClientId { get; set; }` — Client id for the OIDC authority
- L135 _public property_ `public string[]? LocalRedirectUrls { get; set; }` — Optional redirect url provided to OIDC login for external tools (typically to a local server)
- L140 _public property_ `public string[]? Scopes { get; set; }` — Optional OIDC scopes for authorizing API requests from external tools

#### class `EpicGames.Horde.Server.PreflightConfigRequest`  
`public class PreflightConfigRequest`  
_public; L146-157_
- desc: Request to validate server configuration with the given files replacing their checked-in counterparts.
- L151 _public property_ `public string? Cluster { get; set; }` — Perforce cluster to retrieve from
- L156 _public property_ `public int ShelvedChange { get; set; }` — Change to test

#### class `EpicGames.Horde.Server.PreflightConfigResponse`  
`public class PreflightConfigResponse`  
_public; L162-183_
- desc: Response from validating config files
- L167 _public property_ `public bool Result { get; set; }` — Whether the files were validated successfully
- L172 _public property_ `public string? Message { get; set; }` — Output message from validation
- L177 _public property_ `public string? Detail { get; set; }` — Detailed response
- L182 _public property_ `public string[] Warnings { get; set; }` — Warnings generated during config processing (e.g. diamond include dependencies)

#### class `EpicGames.Horde.Server.ServerStatusSubsystem`  
`public class ServerStatusSubsystem`  
_public; L188-200_
- desc: Status for a subsystem within Horde
- L194 _public property_ `public string Name { get; init; }` — Name of the subsystem
- L199 _public property_ `public ServerStatusUpdate[] Updates { get; set; }` — List of updates

#### enum `EpicGames.Horde.Server.ServerStatusResult`  
`public enum ServerStatusResult`  
_public; L205-221_
- desc: Type of status result for a single update
- L210 _public* enumerator_ `Unhealthy` — Indicates that the health check determined that the subsystem was unhealthy
- L215 _public* enumerator_ `Degraded` — Indicates that the health check determined that the component was in a subsystem state
- L220 _public* enumerator_ `Healthy` — Indicates that the health check determined that the subsystem was healthy

#### class `EpicGames.Horde.Server.ServerStatusUpdate`  
`public class ServerStatusUpdate`  
_public; L226-242_
- desc: A single status update
- L231 _public property_ `public ServerStatusResult Result { get; set; }` — Result of status update
- L236 _public property_ `public string? Message { get; set; }` — Optional message describing the result
- L241 _public property_ `public DateTimeOffset UpdatedAt { get; set; }` — Time this update was created

#### class `EpicGames.Horde.Server.ServerStatusResponse`  
`public class ServerStatusResponse`  
_public; L247-253_
- desc: Response from server status controller
- L252 _public property_ `public ServerStatusSubsystem[] Statuses { get; set; }` — List of subsystem statuses

#### record `EpicGames.Horde.Server.ServerPluginInfoResponse`  
`public record ServerPluginInfoResponse(string Name, string? Description, bool Loaded, string? Version = null, string[]? UserAcls = null)`  
_public; L263-263_
- desc: Information about a server plugin

### `Source/Programs/Shared/EpicGames.Horde/ServiceAccounts/ServiceAccountId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.ServiceAccounts.ServiceAccountId`  
`public readonly record struct ServiceAccountId(BinaryId Id)`  
_public; L16-23_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<ServiceAccountId, ServiceAccountIdConverter>))] [BinaryIdConverter(typeof(ServiceAccountIdConverter))]`
- desc: Identifier for a user account
- L19 _public method_ `public static ServiceAccountId Parse(string text)` — (inheritdoc)
- L22 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.ServiceAccounts.ServiceAccountIdConverter`  
`class ServiceAccountIdConverter : BinaryIdConverter<ServiceAccountId>`  
_internal*; L28-35_
- inherits: `BinaryIdConverter<ServiceAccountId>`
- desc: Converter to and from BinaryId instances.
- L31 _public method_ `public override ServiceAccountId FromBinaryId(BinaryId id)` — (inheritdoc)
- L34 _public method_ `public override BinaryId ToBinaryId(ServiceAccountId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/ServiceAccounts/ServiceAccountMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.ServiceAccounts.CreateServiceAccountRequest`  
`public record CreateServiceAccountRequest(string Name, string Description, List<AccountClaimMessage> Claims, bool? Enabled = true)`  
_public; L17-17_
- desc: Creates a new user account

#### record `EpicGames.Horde.ServiceAccounts.CreateServiceAccountResponse`  
`public record CreateServiceAccountResponse(ServiceAccountId Id, string SecretToken)`  
_public; L24-24_
- desc: Response from the request to create a new user account

#### record `EpicGames.Horde.ServiceAccounts.UpdateServiceAccountRequest`  
`public record UpdateServiceAccountRequest(string? Name = null, string? Description = null, List<AccountClaimMessage>? Claims = null, bool? ResetToken = null, bool? Enabled = null)`  
_public; L34-34_
- desc: Update request for a user account

#### record `EpicGames.Horde.ServiceAccounts.UpdateServiceAccountResponse`  
`public record UpdateServiceAccountResponse(string? NewSecretToken = null)`  
_public; L39-39_
- desc: Response from updating a user account

#### record `EpicGames.Horde.ServiceAccounts.GetServiceAccountResponse`  
`public record GetServiceAccountResponse(ServiceAccountId Id, List<AccountClaimMessage> Claims, string Description, bool Enabled)`  
_public; L48-48_
- desc: Creates a new user account

### `Source/Programs/Shared/EpicGames.Horde/Storage/Backends/FileStorageBackend.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Backends.FileStorageBackend`  
`public sealed class FileStorageBackend : IStorageBackend`  
_public; L17-211_
- inherits: `IStorageBackend`
- desc: Storage backend that utilizes the local filesystem
- L19 _private* field_ `readonly DirectoryReference _rootDir`
- L20 _private* field_ `readonly FileObjectStore _objectStore`
- L21 _private* field_ `readonly ILogger _logger`
- L24 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L31-36 _public ctor_ `public FileStorageBackend(FileObjectStore objectStore, ILogger logger)` — Constructor
- L41-44 _public ctor_ `public FileStorageBackend(DirectoryReference rootDir, MemoryMappedFileCache memoryMappedFileCache, ILogger logger) : this(new FileObjectStore(rootDir, memoryMappedFileCache), logger)` — Constructor
- L51 _private* method_ `static ObjectKey GetBlobFile(BlobLocator locator)` — Gets the path for storing a file on disk
- L54 _public method_ `public Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L64 _public method_ `public IReadOnlyMemoryOwner<byte> Read(BlobLocator locator, int offset, int? length)` — Maps a file into memory for reading, and returns a handle to it
- L68 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L72 _public method_ `public Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L76-81 _public method_ `public async Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L84 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator path, CancellationToken cancellationToken = default)` — (inheritdoc)
- L88 _public method_ `public ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator path, IReadOnlyCollection<BlobLocator>? imports = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L92 _public method_ `public ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator>? imports = null, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L100-104 _public method_ `public static async ValueTask<BlobLocator> ReadRefAsync(FileReference file)` — Reads a ref from a file on disk
- L106 _private* method_ `FileReference GetRefFile(RefName name)`
- L112-119 _public method_ `public static IEnumerable<RefName> EnumerateRefs(DirectoryReference rootDir)` — Enumerate all the refs in a file store
- L124 _public method_ `public Task AddAliasAsync(string name, BlobLocator locator, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L128 _public method_ `public Task RemoveAliasAsync(string name, BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L132 _public method_ `public Task<BlobAliasLocator[]> FindAliasesAsync(string alias, int? maxResults = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L140-143 _public method_ `public void DeleteRef(RefName name)` — (inheritdoc)
- L146-161 _public method_ `public async Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L164-183 _public method_ `public async Task WriteRefAsync(RefName name, HashedBlobRefValue value, CancellationToken cancellationToken = default)` — (inheritdoc)
- L188-206 _public method_ `public async Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L209 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Backends/HttpStorageBackend.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Backends.HttpStorageBackend`  
`public sealed class HttpStorageBackend : IStorageBackend`  
_public; L24-477_
- inherits: `IStorageBackend`
- desc: Storage backend which communicates with the Horde server over HTTP for content
- L85 _private* field_ `readonly string _basePath`
- L86 _private* field_ `readonly Func<HttpClient> _createClient`
- L87 _private* field_ `readonly Func<HttpClient> _createUploadRedirectClient`
- L88 _private* field_ `readonly ILogger _logger`
- L89 _private* field_ `bool _supportsUploadRedirects = true`
- L91 _private* field_ `long _numBytes`
- L92 _private* field_ `int _numActive`
- L93 _private* field_ `TimeSpan _sequentialReadTime`
- L94 _private* field_ `readonly Stopwatch _readTime = new()`
- L97 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L102-108 _public ctor_ `public HttpStorageBackend(string basePath, Func<HttpClient> createClient, Func<HttpClient> createUploadRedirectClient, ILogger logger)` — Constructor
- L113-197 _public method_ `public async Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L200-207 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L210 _public method_ `public Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L214 _public method_ `public Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L218-267 _public method_ `public async Task<BlobLocator> WriteBlobAsync(BlobLocator? locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L269-318 _private* method_ `async Task<WriteBlobResponse> SendWriteRequestAsync(BlobLocator? locator, StreamContent? streamContent, IReadOnlyCollection<BlobLocator>? imports = null, string? prefix = null, CancellationToken cancellationToken = default)`
- L321-325 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L328-339 _public method_ `public async ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L342-353 _public method_ `public async ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator>? imports = null, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L360-390 _public method_ `public async Task<BlobAliasLocator[]> FindAliasesAsync(string alias, int? maxResults = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L397-432 _public method_ `public async Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L437-454 _public method_ `public async Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L457-466 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)
- L468-476 _private* method_ `async Task EnsureSuccessAsync(HttpResponseMessage message, CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Storage.Backends.HttpStorageBackend.WriteBlobResponse`  
`class WriteBlobResponse`  
_private*; L26-31_
- L28 _public property_ `public string Blob { get; set; }`
- L29 _public property_ `public Uri? UploadUrl { get; set; }`
- L30 _public property_ `public bool? SupportsRedirects { get; set; }`

#### class `EpicGames.Horde.Storage.Backends.HttpStorageBackend.ResponseOwningStream`  
`sealed class ResponseOwningStream(HttpResponseMessage response, Stream inner) : Stream`  
_private*; L37-83_
- desc: Wraps a stream and owns the HttpResponseMessage, disposing it when the stream is disposed. This ensures the underlying TCP connection is returned to the pool promptly.
- L39 _public property_ `public override bool CanRead => ...`
- L40 _public property_ `public override bool CanSeek => ...`
- L41 _public property_ `public override bool CanWrite => ...`
- L42 _public property_ `public override long Length => ...`
- L43 _public property_ `public override long Position { get; set; }`
- L45 _public method_ `public override int Read(byte[] buffer, int offset, int count)`
- L46 _public method_ `public override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)`
- L47 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)`
- L48 _public method_ `public override long Seek(long offset, SeekOrigin origin)`
- L49 _public method_ `public override void SetLength(long value)`
- L50 _public method_ `public override void Write(byte[] buffer, int offset, int count)`
- L51 _public method_ `public override void Flush()`
- L52 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken)`
- L53 _public method_ `public override Task CopyToAsync(Stream destination, int bufferSize, CancellationToken cancellationToken)`
- L55-69 _protected method_ `protected override void Dispose(bool disposing)`
- L71-82 _public method_ `public override async ValueTask DisposeAsync()`

#### class `EpicGames.Horde.Storage.Backends.HttpStorageBackendFactory`  
`public sealed class HttpStorageBackendFactory`  
_public; L482-534_
- desc: Factory for constructing HttpStorageBackend instances
- L484 _private* field_ `readonly IHttpClientFactory _httpClientFactory`
- L485 _private* field_ `readonly StorageBackendCache _backendCache`
- L486 _private* field_ `readonly ILogger<HttpStorageBackend> _backendLogger`
- L491-496 _public ctor_ `public HttpStorageBackendFactory(IHttpClientFactory httpClientFactory, StorageBackendCache backendCache, ILogger<HttpStorageBackend> backendLogger)` — Constructor
- L504-525 _public method_ `public IStorageBackend CreateBackend(string basePath, string? accessToken = null, bool withBackendCache = true)` — Creates a new HTTP storage backend
- L533 _public method_ `public IStorageBackend CreateBackend(NamespaceId namespaceId, string? accessToken = null, bool withBackendCache = true)` — Creates a new HTTP storage backend

### `Source/Programs/Shared/EpicGames.Horde/Storage/Backends/JupiterStorageBackend.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Backends.JupiterStorageBackend`  
`public sealed class JupiterStorageBackend : IStorageBackend`  
_public; L22-491_
- inherits: `IStorageBackend`
- desc: Storage backend which communicates with Jupiter over HTTP
- L24 _private* const_ `const string CompactBinaryMimeType = "application/x-ue-cb"`
- L46 _private* property_ `static Utf8String BinaryExtension { get; }`
- L49 _private* property_ `static Utf8String ObjectExtension { get; }`
- L53 _private* field_ `readonly NamespaceId _namespaceId`
- L54 _private* field_ `readonly string _bucketId`
- L55 _private* field_ `readonly Func<HttpClient> _createClient`
- L56 _private* field_ `readonly ILogger _logger`
- L59 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L64-70 _public ctor_ `public JupiterStorageBackend(NamespaceId namespaceId, string bucketId, Func<HttpClient> createClient, ILogger logger)` — Constructor
- L72-85 _private* method_ `static bool TryGetBinaryAttachment(Utf8String path, out CbBinaryAttachment attachment)`
- L87-100 _private* method_ `static bool TryGetObjectAttachment(Utf8String path, out CbObjectAttachment attachment)`
- L105-109 _public method_ `public async Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112-116 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L118-162 _private* method_ `async Task<ReadOnlyMemory<byte>> ReadBlobDataAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)`
- L165-169 _private* method_ `static ReadOnlyMemory<byte> UnwrapDataFromCbObject(ReadOnlyMemory<byte> encodedData)`
- L172-185 _private* method_ `async Task<byte[]> ReadEncodedBlobDataAsync(IoHash hash, CancellationToken cancellationToken = default)`
- L188-195 _public method_ `public async Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L197-244 _private* method_ `static byte[] CreateCbObject(byte[] payload, IReadOnlyCollection<BlobLocator> imports)`
- L247-286 _public method_ `public async Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L289 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L293 _public method_ `public ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L297 _public method_ `public ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator>? imports = null, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L305 _public method_ `public Task AddAliasAsync(string name, BlobLocator target, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L309 _public method_ `public Task RemoveAliasAsync(string name, BlobLocator target, CancellationToken cancellationToken = default)` — (inheritdoc)
- L313 _public method_ `public Task<BlobAliasLocator[]> FindAliasesAsync(string alias, int? maxResults = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L321-345 _public method_ `public async Task<bool> DeleteRefAsync(RefName name, CancellationToken cancellationToken)` — (inheritdoc)
- L348-412 _public method_ `public async Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L415-454 _public method_ `public async Task WriteRefAsync(RefName name, HashedBlobRefValue value, CancellationToken cancellationToken = default)` — (inheritdoc)
- L459-477 _public method_ `public async Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L480-481 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)
- L483-490 _private* method_ `static async Task EnsureSuccessAsync(HttpResponseMessage message, CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Storage.Backends.JupiterStorageBackend.HeaderNames`  
`static class HeaderNames`  
_private*; L26-29_
- L28 _public const_ `public const string JupiterIoHash = "X-Jupiter-IoHash"`

#### class `EpicGames.Horde.Storage.Backends.JupiterStorageBackend.RefFieldNames`  
`static class RefFieldNames`  
_private*; L32-35_
- L34 _public const_ `public const string Target = "tgt"`

#### class `EpicGames.Horde.Storage.Backends.JupiterStorageBackend.ObjectFieldNames`  
`static class ObjectFieldNames`  
_private*; L38-43_
- L40 _public const_ `public const string Data = "data"`
- L41 _public const_ `public const string BinaryAttachments = "bin"`
- L42 _public const_ `public const string ObjectAttachments = "obj"`

#### record `EpicGames.Horde.Storage.Backends.JupiterStorageBackend.WriteBlobResponse`  
`record class WriteBlobResponse(string Identifier)`  
_private*; L51-51_

### `Source/Programs/Shared/EpicGames.Horde/Storage/Backends/MemoryStorageBackend.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Backends.MemoryStorageBackend`  
`public sealed class MemoryStorageBackend : IStorageBackend`  
_public; L16-220_
- inherits: `IStorageBackend`
- desc: In-memory implementation of a storage backend
- L20 _private* field_ `readonly ConcurrentDictionary<BlobLocator, ReadOnlyMemory<byte>> _blobs = ...`
- L20 _private* field_ `readonly ConcurrentDictionary< _blobs = new()`
- L21 _private* field_ `readonly ConcurrentDictionary<RefName, HashedBlobRefValue> _refs = ...`
- L21 _private* field_ `readonly ConcurrentDictionary< _refs = new()`
- L22 _private* field_ `readonly ConcurrentDictionary<string, AliasListNode?> _aliases = ...`
- L22 _private* field_ `readonly ConcurrentDictionary< _aliases = new(StringComparer.Ordinal)`
- L27 _public property_ `public IReadOnlyDictionary<BlobLocator, ReadOnlyMemory<byte>> Blobs => ...` — All data stored by the client
- L32 _public property_ `public IReadOnlyDictionary<RefName, HashedBlobRefValue> Refs => ...` — Accessor for all refs stored by the client
- L35 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L40-44 _public method_ `public Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L47-51 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L53-65 _private* method_ `ReadOnlyMemory<byte> GetBlob(BlobLocator locator, int offset, int? length)`
- L68-75 _public method_ `public async Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator>? imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L78-83 _public method_ `public async Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator>? imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L86 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L90 _public method_ `public ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — (inheritdoc)
- L94 _public method_ `public ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L102-105 _public method_ `public void AddAlias(string name, BlobLocator locator, int rank = 0, ReadOnlyMemory<byte> data = default)` — (inheritdoc)
- L108-139 _public method_ `public void RemoveAlias(string name, BlobLocator locator)` — (inheritdoc)
- L141-158 _private* method_ `static AliasListNode? RemoveAliasFromList(AliasListNode? entry, BlobLocator locator)`
- L161-172 _public method_ `public Task<BlobAliasLocator[]> FindAliasesAsync(string alias, int? maxResults = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L179-190 _public method_ `public Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L195-214 _public method_ `public Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — (inheritdoc)
- L217-219 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### record `EpicGames.Horde.Storage.Backends.MemoryStorageBackend.AliasListNode`  
`record class AliasListNode(BlobLocator Locator, int Rank, ReadOnlyMemory<byte> Data, AliasListNode? Next)`  
_private*; L18-18_

### `Source/Programs/Shared/EpicGames.Horde/Storage/BatchBlobReader.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Storage.BlobReadRequest`  
`public record class BlobReadRequest(IHashedBlobRef BlobRef)`  
_public; L21-21_
- desc: Request for a blob to be read

#### record struct `EpicGames.Horde.Storage.BlobReadResponse`  
`public record struct BlobReadResponse<TRequest>(TRequest Request, BlobData Data) : IDisposable`  
_public; L26-31_
- inherits: `IDisposable`
- desc: Response from a read request
- L29 _public method_ `public void Dispose()` — (inheritdoc)

#### record `EpicGames.Horde.Storage.BatchReaderStats`  
`public record class BatchReaderStats(int NumRequests, int NumReads, int NumBundles, int NumPackets, long BytesRead, long BytesDecoded)`  
_public; L36-36_
- desc: Stats for a batch read

#### class `EpicGames.Horde.Storage.BatchBlobReader`  
`public abstract class BatchBlobReader<TRequest> : IDisposable where TRequest : BlobReadRequest`  
_public; L41-385_
- inherits: `IDisposable`
- constraints: `where TRequest : BlobReadRequest`
- desc: Implements an efficient pipeline for streaming blob data
- L69 _public property_ `public int MinQueueLength { get; set; }` — Number of items to read from the input queue before partitioning into batches
- L74 _public property_ `public long CoalesceReadsBelowSize { get; set; }` — Maximum gap between reads that should be coalesced and executed together
- L79 _public property_ `public bool VerifyHashes { get; set; }` — Whether to verify hashes of data read from storage
- L81 _private* field_ `readonly Channel<TRequest> _otherRequests`
- L82 _private* field_ `readonly Channel<BundleRequest> _bundleRequests`
- L84 _private* field_ `readonly Channel<BundleResponse> _bundleResponses`
- L85 _private* field_ `readonly Channel<PacketResponse> _packetResponses`
- L87 _private* field_ `int _numRequests`
- L88 _private* field_ `int _numReads`
- L89 _private* field_ `int _numBundles`
- L90 _private* field_ `int _numPackets`
- L91 _private* field_ `long _bytesRead`
- L92 _private* field_ `long _bytesDecoded`
- L97-103 _protected ctor_ `protected BatchBlobReader()` — Constructor
- L106-110 _public method_ `public void Dispose()` — (inheritdoc)
- L115-129 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method
- L134 _public method_ `public BatchReaderStats GetStats()` — Gets stats for the reader
- L140-154 _public method_ `public Task[] AddToPipeline(AsyncPipeline pipeline, int numReadTasks, int numDecodeTasks, ChannelReader<TRequest> requestReader)` — Adds a batch reader to the given pipeline
- L157-175 _private* method_ `async Task HandleOtherRequestsAsync(CancellationToken cancellationToken)`
- L182 _protected method_ `protected abstract ValueTask HandleResponsesAsync(List<BlobReadResponse<TRequest>> responses, CancellationToken cancellationToken)` — Handle responses from the read
- L188-254 _private* method_ `async Task CreateBundleRequestsAsync(ChannelReader<TRequest> requestReader, CancellationToken cancellationToken)`
- L256-285 _private* method_ `async Task WriteBundleRequestsAsync(BundleHandle bundleHandle, List<PacketExport> exports, CancellationToken cancellationToken)`
- L287-299 _private* method_ `static bool TryGetPacketExport(TRequest request, [NotNullWhen(true)] out PacketExport? export)`
- L304-325 _private* method_ `async Task ReadBundlesAsync(CancellationToken cancellationToken)`
- L327-337 _private* method_ `void VerifyHash(IBlobRef blobRef, ReadOnlySpan<byte> data, IoHash hash)`
- L342-382 _private* method_ `async Task ReadPacketsAsync(CancellationToken cancellationToken)`

#### record `EpicGames.Horde.Storage.BatchBlobReader.BundleRequest`  
`record class BundleRequest(BundleHandle Handle, int MinOffset, int MaxOffset, List<PacketRequest> Packets)`  
_private*; L44-44_

#### record `EpicGames.Horde.Storage.BatchBlobReader.BundleResponse`  
`record class BundleResponse(IReadOnlyMemoryOwner<byte> Data, int MinOffset, int MaxOffset, List<PacketRequest> Packets) : IDisposable`  
_private*; L46-50_
- inherits: `IDisposable`
- L48 _public method_ `public void Dispose()`

#### record `EpicGames.Horde.Storage.BatchBlobReader.PacketRequest`  
`record class PacketRequest(FlushedPacketHandle Handle, List<ExportRequest> Exports)`  
_private*; L52-56_
- L54 _public property_ `public int MinOffset => ...`
- L55 _public property_ `public int MaxOffset => ...`

#### record `EpicGames.Horde.Storage.BatchBlobReader.ExportRequest`  
`record class ExportRequest(IoHash Hash, ExportHandle Handle, TRequest OriginalRequest)`  
_private*; L58-58_

#### record `EpicGames.Horde.Storage.BatchBlobReader.PacketResponse`  
`record class PacketResponse(IReadOnlyMemoryOwner<byte> Data, List<ExportRequest> Exports) : IDisposable`  
_private*; L60-64_
- inherits: `IDisposable`
- L62 _public method_ `public void Dispose()`

#### record `EpicGames.Horde.Storage.BatchBlobReader.PacketExport`  
`record class PacketExport(FlushedPacketHandle PacketHandle, IoHash ExportHash, ExportHandle ExportHandle, TRequest OriginalRequest)`  
_private*; L186-186_

### `Source/Programs/Shared/EpicGames.Horde/Storage/BatchChunkReader.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Storage.ChunkReadRequest`  
`record class ChunkReadRequest(OutputFile File, long Offset, IHashedBlobRef Handle) : BlobReadRequest(Handle)`  
_internal*; L17-17_
- inherits: `BlobReadRequest(Handle)`
- desc: Request for a chunk to be read before being written to disk

#### class `EpicGames.Horde.Storage.BatchChunkReader`  
`class BatchChunkReader : BatchBlobReader<ChunkReadRequest>, IDisposable`  
_internal*; L22-70_
- inherits: `BatchBlobReader<ChunkReadRequest>, IDisposable`
- desc: Implementation of BatchBlobReader{TRequest} designed for reading leaf chunks of data from storage
- L24 _public const_ `public const int DefaultMaxBatchSize = 20`
- L29-39 _public property_ `public int MaxBatchSize { get; init; }` — Maximum number of exports to write in a single request
- L41 _private* field_ `readonly int _maxBatchSize = DefaultMaxBatchSize`
- L42 _private* field_ `readonly ChannelWriter<OutputChunk[]> _writer`
- L47-50 _public ctor_ `public BatchChunkReader(ChannelWriter<OutputChunk[]> writer)` — Constructor
- L53-69 _protected method_ `protected override async ValueTask HandleResponsesAsync(List<BlobReadResponse<ChunkReadRequest>> responses, CancellationToken cancellationToken)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/BatchOutputWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.OutputFile`  
`class OutputFile`  
_internal*; L19-118_
- desc: Represents an output file that write requests may be issued against
- L24 _public property_ `public string Path { get; }` — The relative output path
- L29 _public property_ `public FileInfo FileInfo { get; }` — File metadata
- L34 _public property_ `public FileEntry FileEntry { get; }` — File entry with metadata about the target file
- L36 _private* field_ `bool _createdFile`
- L37 _private* field_ `int _remainingChunks`
- L42-47 _public ctor_ `public OutputFile(string path, FileInfo fileInfo, FileEntry fileEntry)` — Constructor
- L49 _public method_ `public int IncrementRemaining()`
- L50 _public method_ `public int DecrementRemaining()`
- L55-111 _public method_ `public FileStream OpenStream()` — Opens the file for writing, setting its length on the first run
- L116 _public method_ `public virtual ValueTask CompleteAsync(CancellationToken cancellationToken)` — Callback for a file having been fully written

#### record `EpicGames.Horde.Storage.OutputChunk`  
`record class OutputChunk(OutputFile File, long Offset, ReadOnlyMemory<byte> Data, object Source, IDisposable? DataOwner) : IDisposable`  
_internal*; L123-128_
- inherits: `IDisposable`
- desc: Request to output a block of data A chunk which needs to be written to an output file
- L126 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.BatchOutputWriter`  
`sealed class BatchOutputWriter : IDisposable`  
_internal*; L133-355_
- inherits: `IDisposable`
- desc: Batches file write requests
- L135 _private* field_ `readonly Channel<OutputChunk[]> _channel`
- L136 _private* field_ `readonly ILogger _logger`
- L138 _private* field_ `int _writtenFiles`
- L139 _private* field_ `long _writtenBytes`
- L144 _public property_ `public int WrittenFiles => ...` — Number of files that have been written
- L150 _public property_ `public long WrittenBytes => ...` — Total number of bytes that have been written
- L156 _public property_ `public int WriteBatchSize { get; set; }` — Number of writes to execute sequentially vs in parallel
- L161 _public property_ `public bool EnableOutput { get; set; }` — If false, disables output to disk. Useful for performance testing.
- L166 _public property_ `public bool VerifyOutput { get; set; }` — If true, hashes output files after writing to verify their integrity
- L171 _public property_ `public bool VerboseOutput { get; set; }` — If true, outputs verbose information to the log
- L176 _public property_ `public ChannelWriter<OutputChunk[]> RequestWriter => ...` — Sink for write requests
- L182-186 _public ctor_ `public BatchOutputWriter(ILogger logger)` — Constructor
- L191-200 _public method_ `public void Dispose()` — Dispose remaining items in the queue
- L207-210 _public method_ `public Task[] AddToPipeline(AsyncPipeline pipeline, int numWriteTasks)` — Adds tasks for the writer to an async pipeline
- L216-237 _public method_ `public async Task ProcessAsync(CancellationToken cancellationToken)` — Processes requests from the given input channel
- L239-266 _private* method_ `async Task WriteChunksAsync(OutputChunk[] chunks, CancellationToken cancellationToken)`
- L268-340 _private* method_ `async Task ExtractChunksToFileAsync(OutputFile outputFile, ArraySegment<OutputChunk> chunks, CancellationToken cancellationToken)`
- L342-354 _private* method_ `static MemoryMappedView CreateMemoryMappedView(MemoryMappedFile memoryMappedFile, OutputFile file)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobAlias.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Storage.BlobAlias`  
`public record class BlobAlias(IBlobRef Target, int Rank, ReadOnlyMemory<byte> Data)`  
_public; L13-13_
- desc: Data for an alias in the storage system. An alias is a named weak reference to a node.

#### record `EpicGames.Horde.Storage.BlobAliasLocator`  
`public record class BlobAliasLocator(BlobLocator Target, int Rank, ReadOnlyMemory<byte> Data)`  
_public; L21-21_
- desc: Data for an alias in the storage system. An alias is a named weak reference to a node.

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.BlobConverterAttribute`  
`public sealed class BlobConverterAttribute : Attribute`  
_public; L11-22_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to denote the converter for an object type
- L16 _public property_ `public Type ConverterType { get; }` — Type of the converter
- L21 _public ctor_ `public BlobConverterAttribute(Type converterType)` — Constructor

#### class `EpicGames.Horde.Storage.BlobConverter`  
`public abstract class BlobConverter`  
_public; L27-35_
- desc: Base class for converter types that can serialize blobs from native C# types. Semantics mirror System.Text.Json.Serialization.JsonConverter.
- L34 _public method_ `public abstract bool CanConvert(Type typeToConvert)` — Determines if the converter can handle the given type

#### class `EpicGames.Horde.Storage.BlobConverter`  
`public abstract class BlobConverter<T> : BlobConverter`  
_public; L40-54_
- inherits: `BlobConverter`
- desc: Serializer for typed values to blob data. Mimics the System.Text.Json.Serialization.JsonConverter{T} interface for familiarity.
- L43 _public method_ `public override bool CanConvert(Type type)` — (inheritdoc)
- L48 _public method_ `public abstract T Read(IBlobReader reader, BlobSerializerOptions options)` — Reads a strongly typed value
- L53 _public method_ `public abstract BlobType Write(IBlobWriter writer, T value, BlobSerializerOptions options)` — Writes a strongly typed value

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobData.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.BlobData`  
`public class BlobData : IDisposable`  
_public; L12-53_
- inherits: `IDisposable`
- desc: Data for an individual node. Must be disposed after use.
- L17 _public property_ `public BlobType Type { get; }` — Type of the blob
- L22 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Raw data for the blob. Lifetime of this data is tied to the lifetime of the BlobData object; consumers must not retain references to it.
- L27 _public property_ `public IReadOnlyList<IBlobRef> Imports { get; }` — Handles to referenced blobs
- L32-37 _public ctor_ `public BlobData(BlobType type, ReadOnlyMemory<byte> data, IReadOnlyList<IBlobRef> imports)` — Constructor
- L40-44 _public method_ `public void Dispose()` — (inheritdoc)
- L50-52 _protected method_ `protected virtual void Dispose(bool disposing)` — Overridable dispose method

#### class `EpicGames.Horde.Storage.BlobDataWithOwner`  
`public class BlobDataWithOwner : BlobData`  
_public; L58-81_
- inherits: `BlobData`
- desc: Implementation of BlobData for IReadOnlyMemoryOwner{Byte} instances.
- L60 _private* field_ `readonly IDisposable _owner`
- L65-69 _public ctor_ `public BlobDataWithOwner(BlobType type, ReadOnlyMemory<byte> data, IReadOnlyList<IBlobRef> imports, IDisposable owner) : base(type, data, imports)` — Constructor
- L72-80 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobLocator.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Storage.BlobLocator`  
`public readonly struct BlobLocator : IEquatable<BlobLocator>`  
_public; L19-149_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(BlobLocatorTypeConverter))] [JsonConverter(typeof(BlobLocatorJsonConverter))]`
- inherits: `IEquatable<BlobLocator>`
- desc: Identifier for a blob within a particular namespace.
- L21 _private* field_ `readonly Utf8String _path`
- L26 _public property_ `public Utf8String Path => ...` — Accessor for the internal path string
- L32 _public ctor_ `public BlobLocator(Utf8String path)` — Constructor
- L38 _public ctor_ `public BlobLocator(string path)` — Constructor
- L45-48 _public ctor_ `public BlobLocator(BlobLocator outer, string fragment) : this(outer, Encoding.UTF8.GetBytes(fragment))` — Constructor
- L55-62 _public ctor_ `public BlobLocator(BlobLocator outer, ReadOnlySpan<byte> fragment)` — Constructor
- L67 _public method_ `public bool IsValid()` — Whether the blob locator is valid
- L72-79 _public property_ `public BlobLocator BaseLocator { get; }` — The base blob locator
- L84-91 _public property_ `public Utf8String Fragment { get; }` — Fragment within the base blob
- L96 _public method_ `public bool CanUnwrap()` — Determines if this locator can be unwrapped into an outer locator/fragment pair
- L104-119 _public method_ `public bool TryUnwrap(out BlobLocator baseLocator, out Utf8String fragment)` — Split this locator into a locator and fragment
- L126-130 _public method_ `public bool WithinFolder(Utf8String folderName)` — Checks whether this blob is within the given folder
- L133 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L136 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L139 _public method_ `public bool Equals(BlobLocator other)` — (inheritdoc)
- L142 _public method_ `public override string ToString()` — (inheritdoc)
- L145 _public operator_ `public static bool operator ==(BlobLocator left, BlobLocator right)` — (inheritdoc)
- L148 _public operator_ `public static bool operator !=(BlobLocator left, BlobLocator right)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.BlobLocatorTypeConverter`  
`sealed class BlobLocatorTypeConverter : TypeConverter`  
_internal*; L154-186_
- inherits: `TypeConverter`
- desc: Type converter from strings to BlobLocator objects
- L157-160 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L163-166 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L169-172 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L175-185 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.BlobLocatorJsonConverter`  
`public sealed class BlobLocatorJsonConverter : JsonConverter<BlobLocator>`  
_public; L191-198_
- inherits: `JsonConverter<BlobLocator>`
- desc: Class which serializes BlobLocator objects to JSON
- L194 _public method_ `public override BlobLocator Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L197 _public method_ `public override void Write(Utf8JsonWriter writer, BlobLocator value, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobPipeline.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Storage.BlobRequest`  
`public record class BlobRequest<TUserData>(IBlobRef Handle, TUserData UserData)`  
_public; L19-19_
- desc: Request to read a blob from storage

#### record `EpicGames.Horde.Storage.BlobResponse`  
`public sealed record class BlobResponse<TUserData>(BlobData BlobData, TUserData UserData) : IDisposable`  
_public; L24-29_
- inherits: `IDisposable`
- desc: Response from reading a blob from storage
- L27 _public method_ `public void Dispose()` — (inheritdoc)

#### record `EpicGames.Horde.Storage.BlobResponseBatch`  
`public sealed record class BlobResponseBatch<TUserData>(BlobResponse<TUserData>[] Responses) : IDisposable`  
_public; L34-44_
- inherits: `IDisposable`
- desc: Batch of responses from the reader
- L37-43 _public method_ `public void Dispose()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.BlobPipelineOptions`  
`public class BlobPipelineOptions`  
_public; L49-65_
- desc: Options for BlobPipeline{TUserData}
- L54 _public property_ `public int ResponseBufferSize { get; set; }` — Maximum number of responses to buffer before pausing.
- L59 _public property_ `public int FlushBatchLength { get; set; }` — Number of requests to enumerate before flushing the current batch
- L64 _public property_ `public int NumFetchTasks { get; set; }` — Number of batches to fetch in parallel

#### class `EpicGames.Horde.Storage.BlobPipeline`  
`public sealed class BlobPipeline<TUserData> : IAsyncDisposable`  
_public; L71-363_
- inherits: `IAsyncDisposable`
- desc: Helper class to sort requested reads for optimal coherency within bundles
- L73 _private* field_ `readonly BlobPipelineOptions _options`
- L74 _private* field_ `readonly CancellationTokenSource _cancellationTokenSource = new()`
- L75 _private* field_ `readonly List<Task> _tasks = []`
- L76 _private* field_ `readonly Channel<BlobRequest<TUserData>> _requestChannel`
- L77 _private* field_ `readonly Channel<BlobRequest<TUserData>[]> _requestBatchChannel`
- L78 _private* field_ `readonly Channel<BlobResponseBatch<TUserData>> _responseBatchChannel`
- L80 _private* field_ `int _writerCount = 1`
- L81 _private* field_ `bool _writerFinished`
- L86-88 _public ctor_ `public BlobPipeline() : this(new BlobPipelineOptions())` — Constructor
- L93-103 _public ctor_ `public BlobPipeline(BlobPipelineOptions options)` — Constructor
- L106-128 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L134-140 _public method_ `public void Add(BlobRequest<TUserData> request)` — Adds a new read request
- L146-150 _public method_ `public void AddSource(Func<CancellationToken, IAsyncEnumerator<BlobRequest<TUserData>>> factory)` — Adds a new request source
- L152-160 _private* method_ `async Task CopyToRequestChannelAsync(Func<CancellationToken, IAsyncEnumerator<BlobRequest<TUserData>>> factory, CancellationToken cancellationToken)`
- L165-172 _public method_ `public void FinishAdding()` — Indicate that we've finished adding new items to the reader
- L174-192 _private* method_ `void AdjustWriterCount(int delta)`
- L197-248 _private* method_ `async Task BatchLoopAsync(CancellationToken cancellationToken)`
- L250-275 _private* method_ `static bool TryAddBundleRequest(BlobRequest<TUserData> request, Queue<BundleBatchRequest> bundleBatchQueue, Dictionary<BundleHandle, BundleBatchRequest> bundleHandleToBatch)`
- L277-294 _private* method_ `async Task FetchLoopAsync(CancellationToken cancellationToken)`
- L296-316 _private* method_ `async Task FetchWorkerAsync(CancellationToken cancellationToken)`
- L322-348 _public method_ `public async IAsyncEnumerable<BlobResponse<TUserData>> ReadAllAsync([EnumeratorCancellation] CancellationToken cancellationToken = default)` — Reads all responses from the reader
- L354 _public method_ `public bool TryReadBatch([NotNullWhen(true)] out BlobResponseBatch<TUserData>? batch)` — Attempts to read a batch from the queue
- L361 _public method_ `public ValueTask<bool> WaitToReadAsync(CancellationToken cancellationToken)` — Waits until there is data available to read

#### record `EpicGames.Horde.Storage.BlobPipeline.BundleRequest`  
`record class BundleRequest(BundleHandle BundleHandle, int PacketOffset, int ExportIdx, BlobRequest<TUserData> OriginalRequest)`  
_private*; L194-194_

#### record `EpicGames.Horde.Storage.BlobPipeline.BundleBatchRequest`  
`record class BundleBatchRequest(BundleHandle BundleHandle, List<BundleRequest> Requests)`  
_private*; L195-195_

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobSerializer.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.BlobSerializer`  
`public static class BlobSerializer`  
_public; L17-45_
- desc: Handles serialization of blobs using BlobConverter instances.
- L25-30 _public method_ `public static T Deserialize<T>(BlobData blobData, BlobSerializerOptions? options = null)` — Deserialize an object
- L40-44 _public method_ `public static BlobType Serialize<T>(IBlobWriter writer, T value, BlobSerializerOptions? options = null)` — Serialize an object into a blob

#### class `EpicGames.Horde.Storage.BlobSerializerOptions`  
`public class BlobSerializerOptions`  
_public; L50-206_
- desc: Options for serializing blobs
- L114 _private* field_ `readonly ConcurrentDictionary<Type, BlobConverter> _cachedConverters = ...`
- L114 _private* field_ `readonly ConcurrentDictionary< _cachedConverters = new()`
- L115 _private* field_ `static readonly ConcurrentDictionary<Type, BlobConverter> s_cachedDefaultConverters = ...`
- L115 _private* field_ `static readonly ConcurrentDictionary< s_cachedDefaultConverters = new()`
- L116 _private* field_ `static readonly Func<Type, BlobConverter> s_createDefaultConverter = ...`
- L116 _private* field_ `static readonly Func< s_createDefaultConverter = CreateDefaultConverter`
- L118 _private* field_ `bool _readOnly`
- L119 _private* field_ `readonly FreezableList<BlobConverter> _converters`
- L124 _public property_ `public IList<BlobConverter> Converters => ...` — Known converter types
- L129 _public property_ `public static BlobSerializerOptions Default { get; }` — Default options instance
- L134-137 _public ctor_ `public BlobSerializerOptions()` — Constructor
- L139-145 _private* method_ `void CheckMutable()`
- L147-152 _private* method_ `static BlobSerializerOptions CreateDefaultOptions()`
- L158 _public method_ `public void MakeReadOnly()` — Create a read-only version of these options
- L163-166 _public method_ `public BlobConverter<T> GetConverter<T>()` — Gets a converter for the given type
- L168-178 _private* method_ `BlobConverter CreateConverter(Type type)`
- L180-193 _private* method_ `static BlobConverter CreateDefaultConverter(Type type)`
- L199-205 _public method_ `public static BlobSerializerOptions Create(HordeApiVersion version)` — Creates options for serializing blobs compatible with a particular server API version

#### class `EpicGames.Horde.Storage.BlobSerializerOptions.FreezableList`  
`class FreezableList<T> : IList<T>`  
_private*; L52-112_
- inherits: `IList<T>`
- L54 _private* field_ `readonly BlobSerializerOptions _owner`
- L55 _private* field_ `readonly List<T> _list`
- L57-61 _public ctor_ `public FreezableList(BlobSerializerOptions owner)`
- L63-71 _public indexer_ `public T this[int index] { get; set; }`
- L73 _public property_ `public int Count => ...`
- L74 _public property_ `public bool IsReadOnly => ...`
- L76-80 _public method_ `public void Add(T item)`
- L82-86 _public method_ `public void Clear()`
- L88 _public method_ `public bool Contains(T item)`
- L89 _public method_ `public void CopyTo(T[] array, int arrayIndex)`
- L90 _public method_ `public IEnumerator<T> GetEnumerator()`
- L91 _public method_ `public int IndexOf(T item)`
- L93-97 _public method_ `public void Insert(int index, T item)`
- L99-103 _public method_ `public bool Remove(T item)`
- L105-109 _public method_ `public void RemoveAt(int index)`
- L111 _private* method_ `IEnumerator IEnumerable.GetEnumerator()`

#### class `EpicGames.Horde.Storage.BlobSerializerExtensions`  
`public static class BlobSerializerExtensions`  
_public; L211-334_
- desc: Extension methods for serializing blob types
- L220-224 _public method_ `public static async ValueTask<T> ReadBlobAsync<T>(this IBlobRef handle, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default)` — Deserialize an object
- L232-236 _public method_ `public static async ValueTask<T> ReadBlobAsync<T>(this IBlobRef<T> handle, CancellationToken cancellationToken = default)` — Deserialize an object
- L244-248 _public method_ `public static async ValueTask<T> ReadBlobAsync<T>(this IHashedBlobRef<T> handle, CancellationToken cancellationToken = default)` — Deserialize an object
- L257-261 _public method_ `public static async ValueTask<IHashedBlobRef<T>> WriteBlobAsync<T>(this IBlobWriter writer, T value, CancellationToken cancellationToken = default)` — Serialize an object to storage
- L272-280 _public method_ `public static async Task<IHashedBlobRef<TNode>?> TryReadRefAsync<TNode>(this IStorageNamespace store, RefName name, DateTime cacheTime = default, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default) where TNode : class` — Reads data for a ref from the store, along with the node's contents.
- L291-299 _public method_ `public static async Task<IHashedBlobRef<TNode>> ReadRefAsync<TNode>(this IStorageNamespace store, RefName name, DateTime cacheTime = default, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default) where TNode : class` — Reads a ref from the store, throwing an exception if it does not exist
- L310-318 _public method_ `public static async Task<TNode?> TryReadRefTargetAsync<TNode>(this IStorageNamespace store, RefName name, DateTime cacheTime = default, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default) where TNode : class` — Reads data for a ref from the store, along with the node's contents.
- L329-333 _public method_ `public static async Task<TNode> ReadRefTargetAsync<TNode>(this IStorageNamespace store, RefName name, DateTime cacheTime = default, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default) where TNode : class` — Reads a ref from the store, throwing an exception if it does not exist

### `Source/Programs/Shared/EpicGames.Horde/Storage/BlobType.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Storage.BlobType`  
`public readonly record struct BlobType(Guid Guid, int Version)`  
_public; L14-51_
- desc: Identifies the type of a blob
- L19 _public const_ `public const int NumBytes = 20` — Number of bytes in a serialized blob type instance
- L24-27 _public ctor_ `public BlobType(string guid, int version) : this(Guid.Parse(guid), version)` — Constructor
- L32-38 _public method_ `public static BlobType Read(ReadOnlySpan<byte> span)` — Deserialize a type from a byte span
- L43-47 _public method_ `public readonly void Write(Span<byte> data)` — Serialize to a byte span
- L50 _public method_ `public override readonly string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/Bundle.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Storage.Bundles.BundleVersion`  
`public enum BundleVersion`  
_public; L13-66_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1027:Mark enums with FlagsAttribute")]`
- desc: Bundle version number
- L18 _public* enumerator_ `Initial = 0` — Initial version number
- L23 _public* enumerator_ `ExportAliases = 1` — Added the BundleExport.Alias property
- L28 _public* enumerator_ `RemoveAliases = 2` — Back out change to include aliases. Will likely do this through an API rather than baked into the data.
- L33 _public* enumerator_ `InPlace = 3` — Use data structures which support in-place reading and writing.
- L38 _public* enumerator_ `ImportHashes = 4` — Add import hashes to imported nodes
- L43 _public* enumerator_ `PacketSequence = 5` — Structure bundles as a sequence of self-contained packets (uses V2 code)
- L48 _public* enumerator_ `LatestPlusOne` — Last item in the enum. Used for Latest
- L54 _public* enumerator_ `Latest = (int)LatestPlusOne - 1` — The current version number
- L59 _public* enumerator_ `LatestV1 = ImportHashes` — Last version using the V1 pipeline
- L64 _public* enumerator_ `LatestV2 = Latest` — Last version using the V2 pipeline

#### record struct `EpicGames.Horde.Storage.Bundles.BundleSignature`  
`public readonly record struct BundleSignature(BundleVersion Version, int HeaderLength)`  
_public; L73-123_
- desc: Signature for a bundle
- L78 _public const_ `public const int NumBytes = 8` — Number of bytes in a signature when serialized
- L85-99 _public method_ `public static BundleSignature Read(ReadOnlySpan<byte> span)` — Validates that the prelude bytes for a bundle header are correct
- L104-122 _public method_ `public void Write(Span<byte> span)` — Writes a signature to the given memory

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/BundleCache.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.BundleCacheOptions`  
`public class BundleCacheOptions`  
_public; L18-44_
- desc: Options for creating a storage cache
- L23 _public property_ `public int PacketReaderCount { get; set; }` — Number of packet readers to keep in the cache
- L28 _public property_ `public int BundlePageSize { get; set; }` — Size of a bundle page
- L33 _public property_ `public int BundlePageCount { get; set; }` — Number of bundle pages to keep in the cache.
- L38 _public property_ `public long HeaderCacheSize { get; set; }` — Size of the header cache
- L43 _public property_ `public long PacketCacheSize { get; set; }` — Size of the packet cache

#### record struct `EpicGames.Horde.Storage.Bundles.BundlePageCacheKey`  
`readonly record struct BundlePageCacheKey(BundleHandle Bundle, int Index)`  
_internal*; L46-50_
- L48 _public method_ `public override string ToString()`

#### class `EpicGames.Horde.Storage.Bundles.BundleCache`  
`public sealed class BundleCache : IAsyncDisposable`  
_public; L55-281_
- inherits: `IAsyncDisposable`
- desc: Cache for reading bundle data.
- L57 _private* field_ `readonly BundleCacheOptions _options`
- L58 _private* field_ `readonly CancellationTokenSource _cancellationSource = new()`
- L60 _private* field_ `readonly IScopedAsyncCache<PacketReaderCacheKey, PacketReader> _packetReaderCache`
- L60 _private* field_ `readonly IScopedAsyncCache< _packetReaderCache`
- L61 _private* field_ `readonly IScopedAsyncCache<BundlePageCacheKey, IReadOnlyMemoryOwner<byte>> _bundlePageCache`
- L61 _private* field_ `readonly IScopedAsyncCache< _bundlePageCache`
- L62 _private* field_ `readonly MemoryCache? _headerCache`
- L63 _private* field_ `readonly MemoryCache? _packetCache`
- L65 _private* field_ `readonly SemaphoreSlim _writeSemaphore`
- L68 _internal property_ `internal IScopedAsyncCache<PacketReaderCacheKey, PacketReader> PacketReaderCache => ...`
- L69 _internal property_ `internal IScopedAsyncCache<BundlePageCacheKey, IReadOnlyMemoryOwner<byte>> BundlePageCache => ...`
- L74 _public property_ `public static BundleCache None { get; }` — Instance of an empty cache
- L79 _public property_ `public IMemoryAllocator<byte> Allocator { get; }` — Accessor for the default allocator
- L84 _public property_ `public int BundlePageSize => ...` — Size of a bundle page to keep in the cache
- L89 _public property_ `public long HeaderCacheSize => ...` — Size of the configured header cache
- L94 _public property_ `public long PacketCacheSize => ...` — Size of the configured packet cache
- L99 _public property_ `public bool HasPacketCache => ...` — Whether there is a packet cache present
- L104 _public property_ `public SemaphoreSlim WriteSemaphore => ...` — Semaphore for writing new data
- L109-112 _public ctor_ `public BundleCache() : this(new BundleCacheOptions())` — Constructor
- L118-121 _public ctor_ `public BundleCache(BundleCacheOptions options) : this(options, PoolAllocator.Shared)` — Constructor
- L128-166 _public ctor_ `public BundleCache(BundleCacheOptions options, IMemoryAllocator<byte> innerAllocator)` — Constructor
- L169-182 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L187-202 _public method_ `public void GetStats(StorageStats stats)` — Gets stats for the cache
- L206-216 _private* method_ `static void AddCachedValue(IMemoryCache? cache, string cacheKey, object value, int size)`
- L218-226 _private* method_ `static bool TryGetCachedValue<T>(IMemoryCache? cache, string cacheKey, [MaybeNull, NotNullWhen(true)] out T value)`
- L228 _private* method_ `static string GetBundleInfoCacheKey(BlobLocator locator)`
- L229 _private* method_ `static string GetEncodedPacketCacheKey(BlobLocator locator, int packetIdx)`
- L230 _private* method_ `static string GetDecodedPacketCacheKey(BlobLocator locator, int packetIdx)`
- L235-238 _public method_ `public void AddCachedHeader(BlobLocator locator, Bundles.V1.BundleInfo bundleInfo)` — Adds a bundle info object to the cache
- L243-246 _public method_ `public bool TryGetCachedHeader(BlobLocator locator, [NotNullWhen(true)] out Bundles.V1.BundleInfo? bundleInfo)` — Try to read a bundle info object from the cache
- L251-254 _public method_ `public void AddCachedEncodedPacket(BlobLocator locator, int packetIdx, ReadOnlyMemory<byte> data)` — Adds an encoded bundle packet to the cache
- L259-262 _public method_ `public bool TryGetCachedEncodedPacket(BlobLocator locator, int packetIdx, out ReadOnlyMemory<byte> data)` — Try to read an encoded bundle packet from the cache
- L267-270 _public method_ `public void AddCachedDecodedPacket(BlobLocator locator, int packetIdx, ReadOnlyMemory<byte> data)` — Adds a decoded bundle packet to the cache
- L275-278 _public method_ `public bool TryGetCachedDecodedPacket(BlobLocator locator, int packetIdx, out ReadOnlyMemory<byte> data)` — Try to read a decoded bundle packet from the cache

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/BundleCompression.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Storage.Bundles.BundleCompressionFormat`  
`public enum BundleCompressionFormat`  
_public; L18-49_
- desc: Indicates the compression format in the bundle
- L23 _public* enumerator_ `None = 0` — Packets are uncompressed
- L28 _public* enumerator_ `LZ4 = 1` — LZ4 compression
- L33 _public* enumerator_ `Gzip = 2` — Gzip compression
- L38 _public* enumerator_ `Oodle = 3` — Oodle compression (Selkie)
- L43 _public* enumerator_ `Brotli = 4` — Brotli compression
- L48 _public* enumerator_ `Zstd = 5` — ZStandard compression

#### class `EpicGames.Horde.Storage.Bundles.BundleData`  
`public static class BundleData`  
_public; L54-224_
- desc: Utility methods for bundles
- L62-67 _public method_ `public static byte[] Compress(BundleCompressionFormat format, ReadOnlyMemory<byte> input)` — Compress a block of data into a newly allocated block of memory
- L76-148 _public method_ `public static int Compress(BundleCompressionFormat format, ReadOnlyMemory<byte> input, IMemoryWriter writer)` — Compress a data packet
- L156-223 _public method_ `public static void Decompress(BundleCompressionFormat format, ReadOnlyMemory<byte> input, Memory<byte> output)` — Decompress a packet of data

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/BundleHandle.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.BundleHandle`  
`public abstract class BundleHandle`  
_public; L13-49_
- desc: Base class for packet handles
- L18 _public property_ `public BlobLocator Locator { get; }` — Locator for this bundle
- L23 _protected ctor_ `protected BundleHandle(BlobLocator locator)` — Constructor
- L29 _public method_ `public abstract ValueTask FlushAsync(CancellationToken cancellationToken = default)` — Flush contents of the bundle to storage
- L34 _public method_ `public abstract Task<Stream> OpenAsync(int offset = 0, int? length = null, CancellationToken cancellationToken = default)` — Open the bundle for reading
- L39 _public method_ `public abstract ValueTask<IReadOnlyMemoryOwner<byte>> ReadAsync(int offset, int? length, CancellationToken cancellationToken = default)` — Get data for a packet of data from the bundle
- L44-48 _public method_ `public bool TryGetLocator(out BlobLocator locator)` — Attempt to get a locator for this bundle

#### class `EpicGames.Horde.Storage.Bundles.FlushedBundleHandle`  
`class FlushedBundleHandle : BundleHandle`  
_internal*; L54-86_
- inherits: `BundleHandle`
- desc: Generic flushed bundle handle; can be either V1 or V2 format.
- L56 _private* field_ `readonly BundleStorageNamespace _storageNamespace`
- L61-65 _public ctor_ `public FlushedBundleHandle(BundleStorageNamespace storageNamespace, BlobLocator locator) : base(locator)` — Constructor
- L68 _public method_ `public override ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L71 _public method_ `public override Task<Stream> OpenAsync(int offset = 0, int? length = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L75 _public method_ `public override async ValueTask<IReadOnlyMemoryOwner<byte>> ReadAsync(int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L79 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L82 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L85 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/BundleOptions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.BundleOptions`  
`public class BundleOptions`  
_public; L8-39_
- desc: Options for configuring a bundle serializer
- L13 _public property_ `public static BundleOptions Default { get; }` — Default options value
- L18 _public property_ `public BundleVersion MaxVersion { get; set; }` — Maximum version number of bundles to write
- L23 _public property_ `public int MaxBlobSize { get; set; }` — Maximum payload size fo a blob
- L28 _public property_ `public BundleCompressionFormat CompressionFormat { get; set; }` — Compression format to use
- L33 _public property_ `public int MinCompressionPacketSize { get; set; }` — Minimum size of a block to be compressed
- L38 _public property_ `public long MaxWriteQueueLength { get; set; }` — Maximum amount of data to store in memory. This includes any background writes as well as bundles being built.

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/BundleStorageNamespace.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.BundleStorageNamespace`  
`public sealed class BundleStorageNamespace : IStorageNamespace`  
_public; L21-258_
- inherits: `IStorageNamespace`
- desc: Base class for an implementation of IStorageNamespace, providing implementations for some common functionality using bundles.
- L37 _private* field_ `readonly IStorageBackend _backend`
- L38 _private* field_ `readonly BundleCache _cache`
- L39 _private* field_ `readonly BundleOptions _options`
- L40 _private* field_ `readonly PacketReaderStats _packetReaderStats = new()`
- L41 _private* field_ `readonly Bundles.V1.BundleReader _bundleReader`
- L42 _private* field_ `readonly ILogger _logger`
- L44 _internal property_ `internal Bundles.V1.BundleReader BundleReader => ...`
- L49 _public property_ `public IMemoryAllocator<byte> Allocator => ...` — Allocator which trims the cache to keep below a maximum size
- L54 _public property_ `public IStorageBackend Backend => ...` — Accessor for the storage backend
- L59 _public property_ `public BundleCache Cache => ...` — Cache for bundle data
- L64 _internal property_ `internal PacketReaderStats PacketReaderStats => ...` — Stats for reading bundles
- L69-76 _public ctor_ `public BundleStorageNamespace(IStorageBackend backend, BundleCache cache, BundleOptions? options, ILogger logger)` — Constructor
- L81 _public method_ `public static BundleStorageNamespace CreateInMemory(ILogger logger)` — Creates a bundle storage namespace around a memory backend
- L87-91 _public method_ `public static BundleStorageNamespace CreateInMemory(BundleOptions? options, ILogger logger)` — Creates a bundle storage namespace around a memory backend
- L96 _public method_ `public static BundleStorageNamespace CreateFromDirectory(DirectoryReference rootDir, BundleCache cache, MemoryMappedFileCache memoryMappedFileCache, ILogger logger)` — Creates a bundle storage namespace around a directory on the filesystem
- L102-106 _public method_ `public static BundleStorageNamespace CreateFromDirectory(DirectoryReference rootDir, BundleCache cache, MemoryMappedFileCache memoryMappedFileCache, BundleOptions? options, ILogger logger)` — Creates a bundle storage namespace around a directory on the filesystem
- L111-115 _public method_ `public async Task<IEnumerable<BlobLocator>> ReadBundleReferencesAsync(BlobLocator locator, CancellationToken cancellationToken)` — Helper method for GC which allows enumerating all references to other bundles
- L120-135 _private* method_ `IEnumerable<BlobLocator> ReadBundleReferences(ReadOnlyMemory<byte> data)` — Helper method for GC which allows enumerating all references to other bundles
- L137-141 _private* method_ `static IEnumerable<BlobLocator> ReadImportsFromDataV1(ReadOnlyMemory<byte> data)`
- L143-163 _private* method_ `IEnumerable<BlobLocator> ReadImportsFromDataV2(ReadOnlyMemory<byte> data)`
- L166 _public method_ `public IStorageWriter CreateWriter(CancellationToken cancellationToken)` — (inheritdoc)
- L172-195 _public method_ `public IBlobRef CreateBlobRef(BlobLocator locator)` — (inheritdoc)
- L198-213 _public method_ `public IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L220-231 _public method_ `public async Task<BlobAlias[]> FindAliasesAsync(string name, int? maxLength = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L238-246 _public method_ `public async Task<IHashedBlobRef?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L251-257 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Bundles.BundleStorageNamespace.StorageWriterImpl`  
`class StorageWriterImpl : StorageWriter`  
_private*; L23-35_
- inherits: `StorageWriter`
- L25 _private* field_ `readonly BundleStorageNamespace _outer`
- L27-31 _public ctor_ `public StorageWriterImpl(BundleStorageNamespace outer, IStorageBackend storageBackend, CancellationToken cancellationToken) : base(storageBackend, cancellationToken)`
- L33 _protected method_ `protected override IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null, CancellationToken cancellationToken = default)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V1/BundleHeader.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Storage.Bundles.V1.BundleSectionType`  
`public enum BundleSectionType`  
_public; L21-52_
- desc: Identifier for the type of a section in the bundle header
- L26 _public* enumerator_ `Types = 0` — List of custom types
- L31 _public* enumerator_ `Imports = 1` — Imports of other bundles
- L36 _public* enumerator_ `ExportHeaders = 2` — List of export headers
- L41 _public* enumerator_ `ExportReferences = 3` — References to exports in other bundles
- L46 _public* enumerator_ `Packets = 4` — Packet headers
- L51 _public* enumerator_ `Exports = 5` — Merged export headers and references

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleHeader`  
`public class BundleHeader`  
_public; L57-415_
- desc: Header for the contents of a bundle.
- L62 _public const_ `public const int MaxSectionSize = 0x1000000` — Maximum size for a section
- L67 _public const_ `public const int MaxExports = 65535` — Maximum number of exports from a single bundle
- L72 _public const_ `public const int MaxExportRefs = MaxSectionSize / BundleExportRef.NumBytes` — Maximum number of export refs from a single bundle
- L77 _public property_ `public static ReadOnlyMemory<byte> Signature { get; }` — Signature bytes
- L82 _public property_ `public BundleTypeCollection Types { get; }` — Types for exports within this bundle
- L87 _public property_ `public BundleImportCollection Imports { get; }` — Bundles that we reference nodes in
- L92 _public property_ `public BundleExportCollection Exports { get; }` — Nodes exported from this bundle
- L97 _public property_ `public BundlePacketCollection Packets { get; }` — List of data packets within this bundle
- L102-108 _public ctor_ `public BundleHeader(BundleTypeCollection types, BundleImportCollection imports, BundleExportCollection exports, BundlePacketCollection packets)` — Constructor
- L113-119 _public ctor_ `public BundleHeader(BlobType[] types, BlobLocator[] imports, BundleExport[] exports, BundlePacket[] packets)` — Constructor
- L124-153 _public method_ `public void AppendTo(ReadOnlySequenceBuilder<byte> builder)` — Writes data for this bundle to a sequence builder
- L158-163 _public method_ `public byte[] ToByteArray()` — Serialize the bundle to a byte array
- L165 _private* const_ `const int SectionHeaderLength = 4`
- L167-174 _private* method_ `static void WriteSectionHeader(IMemoryWriter writer, BundleSectionType type, int length)`
- L184-188 _public method_ `public static BundleHeader Read(ReadOnlyMemory<byte> memory)` — Reads a bundle header from memory
- L197-203 _public method_ `public static async Task<BundleHeader> ReadAsync(Stream stream, CancellationToken cancellationToken = default)` — Reads a bundle header from a stream
- L212-229 _public method_ `public static async Task<BundleHeader> ReadAsync(BundleSignature signature, Stream stream, CancellationToken cancellationToken = default)` — Reads a bundle header from a stream
- L238-290 _private* method_ `static async Task<BundleHeader> ReadLatestAsync(BundleVersion version, Stream stream, int length, CancellationToken cancellationToken)` — Construct a header from the given data encoded in the latest format
- L292-414 _private* method_ `static BundleHeader ReadLegacy(ReadOnlyMemory<byte> memory)`

#### record `EpicGames.Horde.Storage.Bundles.V1.BundleHeader.ExportInfo`  
`record class ExportInfo(int TypeIdx, int Length, List<BundleExportRef> References)`  
_private*; L176-176_

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundleTypeCollection`  
`public readonly struct BundleTypeCollection : IReadOnlyList<BlobType>`  
_public; L420-489_
- inherits: `IReadOnlyList<BlobType>`
- desc: Collection of node types in a bundle
- L422 _private* field_ `readonly BlobType[] _types`
- L425 _public property_ `public int Count => ...` — (inheritdoc)
- L430 _public ctor_ `public BundleTypeCollection() : this([])` — Constructor
- L435 _public ctor_ `public BundleTypeCollection(BlobType[] types)` — Constructor
- L440-449 _public method_ `public static BundleTypeCollection Read(ReadOnlyMemory<byte> data)` — Reads a type collection from a block of memory
- L454-459 _public method_ `public static async Task<BundleTypeCollection> ReadAsync(Stream stream, int length, CancellationToken cancellationToken)` — Reads a type collection from a stream
- L465 _public method_ `public int Measure()` — Gets the size of memory required to serialize a collection of types
- L471-479 _public method_ `public void Write(IMemoryWriter writer)` — Serializes a set of types to a fixed block of memory
- L482 _public indexer_ `public BlobType this[int index]` — (inheritdoc)
- L485 _public method_ `public IEnumerator<BlobType> GetEnumerator()` — (inheritdoc)
- L488 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundleImportCollection`  
`public readonly struct BundleImportCollection : IReadOnlyList<BlobLocator>`  
_public; L494-572_
- inherits: `IReadOnlyList<BlobLocator>`
- desc: Collection of imported node references
- L496 _private* field_ `readonly BlobLocator[] _imports`
- L499 _public property_ `public int Count => ...` — (inheritdoc)
- L504 _public ctor_ `public BundleImportCollection() : this([])` — Constructor
- L509 _public ctor_ `public BundleImportCollection(BlobLocator[] imports)` — Constructor
- L514-528 _public method_ `public static BundleImportCollection Read(ReadOnlyMemory<byte> data)` — Reads a collection from memory
- L533-538 _public method_ `public static async Task<BundleImportCollection> ReadAsync(Stream stream, int length, CancellationToken cancellationToken)` — Reads a collection from a stream
- L541 _public indexer_ `public BlobLocator this[int index]` — (inheritdoc)
- L544 _public method_ `public IEnumerator<BlobLocator> GetEnumerator()` — (inheritdoc)
- L547 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L553 _public method_ `public int Measure()` — Measure the size of memory required to store a collection of import locators
- L559-571 _public method_ `public void Write(IMemoryWriter writer)` — Serialize a collection of locators to memory

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundlePacket`  
`public readonly struct BundlePacket`  
_public; L577-641_
- desc: Descriptor for a compression packet
- L582 _public const_ `public const int NumBytes = 16` — Size of this structure when serialized
- L587 _public property_ `public BundleCompressionFormat CompressionFormat { get; }` — Compression format for this packet
- L592 _public property_ `public int EncodedOffset { get; }` — Offset of the packet within the payload stream
- L597 _public property_ `public int EncodedLength { get; }` — Encoded length of the packet
- L602 _public property_ `public int DecodedLength { get; }` — Decoded length of the packet
- L611-617 _public ctor_ `public BundlePacket(BundleCompressionFormat compressionFormat, int encodedOffset, int encodedLength, int decodedLength)` — Constructor
- L622-629 _public method_ `public static BundlePacket Read(ReadOnlySpan<byte> span)` — Read from a byte array
- L634-640 _public method_ `public void Write(Span<byte> span)` — Serialize the struct to memory

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundlePacketCollection`  
`public readonly struct BundlePacketCollection : IReadOnlyCollection<BundlePacket>`  
_public; L646-717_
- inherits: `IReadOnlyCollection<BundlePacket>`
- desc: Collection of information about packets in a bundle
- L648 _private* field_ `readonly BundlePacket[] _packets`
- L651 _public property_ `public int Count => ...` — (inheritdoc)
- L656 _public ctor_ `public BundlePacketCollection() : this([])` — Constructor
- L661 _public ctor_ `public BundlePacketCollection(BundlePacket[] packets)` — Constructor
- L666-677 _public method_ `public static BundlePacketCollection Read(ReadOnlyMemory<byte> data)` — Reads a collection from memory
- L682-687 _public method_ `public static async Task<BundlePacketCollection> ReadAsync(Stream stream, int length, CancellationToken cancellationToken)` — Reads a collection from a stream
- L690 _public indexer_ `public BundlePacket this[int index]` — (inheritdoc)
- L693 _public method_ `public IEnumerator<BundlePacket> GetEnumerator()` — (inheritdoc)
- L696 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L702 _public method_ `public int Measure()` — Measure the size of memory required to store a collection of packets
- L708-716 _public method_ `public void Write(IMemoryWriter writer)` — Serialize a collection of packets to memory

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundleExport`  
`public readonly struct BundleExport`  
_public; L722-804_
- desc: Entry for a node exported from an object
- L727 _public const_ `public const int NumHeaderBytes = 32` — Number of bytes in a serialized export object
- L732 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Raw data for this export
- L737 _public property_ `public ReadOnlyMemory<byte> HeaderData => ...` — Raw data for the header
- L742 _public property_ `public IoHash Hash => ...` — Hash of the node data
- L747 _public property_ `public int TypeIdx => ...` — Type id of the node. Can be used to look up the type information from the bundle header.
- L752 _public property_ `public int Packet => ...` — Packet containing this export's data
- L757 _public property_ `public int Offset => ...` — Offset within the packet of the node data
- L762 _public property_ `public int Length => ...` — Length of the node
- L767 _public property_ `public BundleExportRefCollection References => ...` — References to other nodes
- L772-775 _public ctor_ `public BundleExport(ReadOnlyMemory<byte> data)` — Constructor
- L780-791 _public ctor_ `public BundleExport(int typeIdx, int packetIdx, int offset, int length, IReadOnlyList<BundleExportRef> references)` — Constructor
- L796-803 _public method_ `public static void WriteHeader(Span<byte> data, int typeIdx, int packet, int offset, int length)` — Writes a new export to a block of memory

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundleExportCollection`  
`public readonly struct BundleExportCollection : IReadOnlyList<BundleExport>`  
_public; L809-1010_
- inherits: `IReadOnlyList<BundleExport>`
- desc: Entry for a node exported from an object
- L811 _private* field_ `readonly BundleExport[] _exports`
- L814 _public property_ `public int Count => ...` — (inheritdoc)
- L819 _public ctor_ `public BundleExportCollection() : this([])` — Constructor
- L824 _public ctor_ `public BundleExportCollection(BundleExport[] exports)` — Constructor
- L829-876 _public method_ `public static BundleExportCollection Read(ReadOnlyMemory<byte> data, ReadOnlyMemory<byte> refs, BundleVersion version)` — Constructor
- L881-940 _public method_ `public static async Task<BundleExportCollection> ReadAsync(Stream stream, int sectionLength, CancellationToken cancellationToken)` — Reads an export collection from a stream
- L943 _public indexer_ `public BundleExport this[int index]` — (inheritdoc)
- L946 _public method_ `public IEnumerator<BundleExport> GetEnumerator()` — (inheritdoc)
- L949 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L954-967 _public method_ `public void Write(IMemoryWriter writer)` — Serializes this collection as a single section
- L973 _public method_ `public int MeasureHeaders()` — Measure the size of memory required to store a collection of exports
- L979-985 _public method_ `public void WriteHeaders(IMemoryWriter writer)` — Serialize a collection of exports to memory
- L991 _public method_ `public int MeasureRefs()` — Measure the size of memory required to store a collection of export refs
- L997-1009 _public method_ `public void WriteRefs(IMemoryWriter writer)` — Serialize a collection of export refs to memory

#### record struct `EpicGames.Horde.Storage.Bundles.V1.BundleExportRef`  
`public readonly record struct BundleExportRef(int ImportIdx, int NodeIdx)`  
_public; L1017-1051_
- desc: Reference to a node in another bundle
- L1022 _public const_ `public const int NumBytes = 4 + IoHash.NumBytes` — Number of bytes in the serialized object
- L1027-1032 _public method_ `public static BundleExportRef Read(ReadOnlySpan<byte> data)` — Deserialize this object from memory
- L1037-1050 _public method_ `public void CopyTo(Span<byte> data)` — Serialize this object to memory

#### struct `EpicGames.Horde.Storage.Bundles.V1.BundleExportRefCollection`  
`public readonly struct BundleExportRefCollection : IReadOnlyList<BundleExportRef>`  
_public; L1056-1107_
- inherits: `IReadOnlyList<BundleExportRef>`
- desc: Collection of information about exported nodes
- L1061 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data used to store this collection
- L1066 _public ctor_ `public BundleExportRefCollection(ReadOnlyMemory<byte> data)` — Constructor
- L1071-1079 _public ctor_ `public BundleExportRefCollection(IReadOnlyList<BundleExportRef> exportRefs)` — Constructor
- L1082 _public property_ `public int Count => ...` — (inheritdoc)
- L1085-1092 _public indexer_ `public BundleExportRef this[int index] { get; }` — (inheritdoc)
- L1095-1103 _public method_ `public IEnumerator<BundleExportRef> GetEnumerator()` — (inheritdoc)
- L1106 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V1/BundleReader.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V1.BundleInfo`  
`public class BundleInfo`  
_public; L18-44_
- desc: Computed information about a bundle
- L23 _public property_ `public BlobLocator Locator { get; }` — Locator for the bundle
- L28 _public property_ `public BundleHeader Header { get; }` — Bundle header
- L33 _public property_ `public int HeaderLength { get; }` — Length of the header. Required to offset packets from the start of the bundle
- L38-43 _public ctor_ `public BundleInfo(BlobLocator locator, BundleHeader header, int headerLength)` — Constructor

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleReader`  
`public class BundleReader`  
_public; L49-602_
- desc: Writes nodes from bundles in an IStorageNamespace instance.
- L123 _private* const_ `const int DefaultFetchSize = 15 * 1024 * 1024`
- L126 _private* const_ `const int DefaultUncachedFetchSize = 1 * 1024 * 1024`
- L128 _private* field_ `readonly BundleStorageNamespace _store`
- L129 _private* field_ `readonly BundleCache _cache`
- L130 _private* field_ `readonly ILogger _logger`
- L132 _private* field_ `readonly Lock _queueLock = new()`
- L133 _private* field_ `readonly List<QueuedBundle> _queuedBundles = []`
- L134 _private* field_ `readonly Dictionary<string, Task<ReadOnlyMemory<byte>>> _decodeTasks = ...`
- L134 _private* field_ `readonly Dictionary< _decodeTasks = new(StringComparer.Ordinal)`
- L136 _private* field_ `int _numHeaderReads`
- L137 _private* field_ `int _numPacketReads`
- L138 _private* field_ `long _numBytesRead`
- L139 _private* field_ `long _decodeTimeTicks`
- L144 _public property_ `public BundleCache Cache => ...` — Accessor for the cache
- L152-157 _public ctor_ `public BundleReader(BundleStorageNamespace store, BundleCache cache, ILogger logger)` — Constructor
- L167-193 _public method_ `public async Task<BundleHeader> ReadHeaderAsync(BlobLocator locator, CancellationToken cancellationToken)` — Reads a bundle header
- L195 _private* method_ `static string GetDecodeTaskKey(BlobLocator locator, int packetIdx)`
- L204-230 _public method_ `public async Task<ReadOnlyMemory<byte>> ReadPacketAsync(BlobLocator locator, int packetIdx, CancellationToken cancellationToken)` — Reads decoded packet data from a bundle
- L232-252 _private* method_ `async Task<ReadOnlyMemory<byte>> ReadAndDecodePacketAsync(BlobLocator locator, int packetIdx, CancellationToken cancellationToken)`
- L261-289 _public method_ `public async Task<ReadOnlyMemory<byte>> ReadEncodedPacketAsync(BlobLocator locator, int packetIdx, CancellationToken cancellationToken)` — Reads encoded packet data from a bundle
- L291-301 _private* method_ `QueuedBundle FindOrAddBundle(BlobLocator locator)`
- L303-395 _private* method_ `async Task HandleBundleRequestsAsync(QueuedBundle bundle)`
- L397-424 _private* method_ `async Task CancelBundleRequestAsync(QueuedBundle bundle, Action updateAction)`
- L435-482 _private* method_ `async Task<BundleInfo> ReadBundleInfoAsync(QueuedBundle bundle, CancellationToken cancellationToken)` — Reads a bundle header from the queue
- L484-506 _private* method_ `async Task ReadEncodedPacketsAsync(QueuedBundle bundle, int minPacketIdx, int maxPacketIdx, CancellationToken cancellationToken)`
- L508-527 _private* method_ `async Task ReadEncodedPacketFromStreamAsync(QueuedBundle bundle, int packetIdx, BundlePacket packet, Stream stream, CancellationToken cancellationToken)`
- L538-578 _public method_ `public async ValueTask<BlobData> ReadNodeDataAsync(BlobLocator bundleLocator, int exportIdx, CancellationToken cancellationToken = default)` — Reads a node from a bundle
- L583-601 _public method_ `public void GetStats(StorageStats stats)` — Gets stats for the reader

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleReader.QueuedBundle`  
`class QueuedBundle`  
_private*; L55-86_
- attrs: `[DebuggerDisplay("{Locator}")]`
- desc: Queued set of requests from a particular bundle
- L57 _public property_ `public BlobLocator Locator { get; }`
- L58 _public property_ `public TaskCompletionSource<BundleInfo> BundleInfo { get; }`
- L59 _public property_ `public List<QueuedPacket> QueuedPackets { get; }`
- L60 _public property_ `public int InfoRefCount { get; set; }`
- L61 _public property_ `public PendingRead? PendingRead { get; set; }`
- L62 _public property_ `public Task? WorkerTask { get; set; }`
- L63 _public property_ `public CancellationTokenSource CancellationSource { get; set; }`
- L64 _public property_ `public bool Complete { get; set; }`
- L66-69 _public ctor_ `public QueuedBundle(BlobLocator locator)`
- L71-83 _public method_ `public QueuedPacket AddPacket(int packetIdx)`
- L85 _public method_ `public void RemovePacket(QueuedPacket packet)`

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleReader.QueuedPacket`  
`class QueuedPacket : IComparable<QueuedPacket>`  
_private*; L91-98_
- inherits: `IComparable<QueuedPacket>`
- desc: Encoded bundle packet queued to be read
- L93 _public field_ `public readonly int PacketIdx`
- L94 _public field_ `public readonly TaskCompletionSource<ReadOnlyMemory<byte>> CompletionSource = new(TaskCreationOptions.RunContinuationsAsynchronously)`
- L96 _public ctor_ `public QueuedPacket(int packetIdx)`
- L97 _public method_ `public int CompareTo(QueuedPacket? other)`

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleReader.PendingRead`  
`sealed class PendingRead : IDisposable`  
_private*; L103-120_
- inherits: `IDisposable`
- desc: Information about a pending read
- L105 _public property_ `public int MinPacketIdx { get; }`
- L106 _public property_ `public int MaxPacketIdx { get; }`
- L107 _public property_ `public CancellationTokenSource CancellationSource { get; }`
- L109-114 _public ctor_ `public PendingRead(int minPacketIdx, int maxPacketIdx, CancellationToken cancellationToken)`
- L116-119 _public method_ `public void Dispose()`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V1/BundleWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V1.FlushedNodeHandle`  
`sealed class FlushedNodeHandle : IBlobRef`  
_internal*; L21-87_
- inherits: `IBlobRef`
- desc: Implementation of IBlobRef for nodes which can be read from storage
- L23 _private* field_ `readonly BundleReader _reader`
- L25 _public property_ `public BlobLocator BundleLocator { get; }`
- L26 _public property_ `public int ExportIdx { get; }`
- L29 _public property_ `public BundleHandle Outer { get; }` — (inheritdoc)
- L31 _public property_ `public IBlobRef Innermost => ...`
- L36-44 _public ctor_ `public FlushedNodeHandle(BundleReader reader, BlobLocator bundleLocator, BundleHandle bundleHandle, int exportIdx)` — Constructor
- L46-60 _public ctor_ `public FlushedNodeHandle(BundleReader reader, BlobLocator bundleLocator, BundleHandle bundleHandle, ReadOnlySpan<byte> fragment)`
- L63-67 _public method_ `public bool TryAppendIdentifier(Utf8StringBuilder builder)` — (inheritdoc)
- L70-74 _public method_ `public bool TryGetLocator(out BlobLocator locator)` — (inheritdoc)
- L77 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L80 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L83 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L86 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleWriter`  
`public sealed class BundleWriter : BlobWriter`  
_public; L93-818_
- inherits: `BlobWriter`
- desc: Writes nodes of a tree to an IStorageNamespace, packed into bundles. Each BundleWriter instance is single threaded, but multiple instances may be written to in parallel.
- L666 _private* field_ `static readonly BundleOptions s_defaultOptions = new()`
- L668 _private* field_ `readonly BundleStorageNamespace _store`
- L669 _private* field_ `readonly BundleReader _reader`
- L670 _private* field_ `readonly BundleOptions _bundleOptions`
- L671 _private* field_ `readonly string? _basePath`
- L673 _private* field_ `readonly WriteQueue _writeQueue`
- L675 _private* field_ `PendingBundle? _currentBundle`
- L677 _private* field_ `bool _disposed`
- L679 _internal property_ `internal ILogger? TraceLogger { get; }`
- L690-693 _public ctor_ `public BundleWriter(BundleStorageNamespace store, BundleReader reader, string? basePath, BundleOptions? bundleOptions = null, BlobSerializerOptions? blobSerializerOptions = null, ILogger? traceLogger = null) : this(store, reader, basePath, bundleOptions, null, blobSerializerOptions, traceLogger)` — Constructor
- L699-703 _public ctor_ `public BundleWriter(BundleWriter other) : this(other._store, other._reader, other._basePath, other._bundleOptions, other._writeQueue, other.Options, other.TraceLogger)` — Copy constructor
- L708-717 _private ctor_ `private BundleWriter(BundleStorageNamespace store, BundleReader reader, string? basePath, BundleOptions? bundleOptions, WriteQueue? writeQueue, BlobSerializerOptions? blobSerializerOptions, ILogger? traceLogger = null) : base(blobSerializerOptions)` — Internal constructor
- L720 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)
- L723-734 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L739-746 _public method_ `public async Task CompleteAsync(CancellationToken cancellationToken)` — Mark this writer as complete, allowing its data to be serialized.
- L754-758 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — Gets an output buffer for writing.
- L769-794 _public method_ `public override async ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken = default)` — Finish writing a node.
- L796-804 _private* method_ `PendingBundle GetCurrentBundle()`
- L811-817 _public method_ `public override async Task FlushAsync(CancellationToken cancellationToken = default)` — Flushes all the current nodes to storage

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleWriter.PendingNode`  
`internal class PendingNode : IHashedBlobRef`  
_internal; L96-204_
- inherits: `IHashedBlobRef`
- L98 _private* field_ `readonly BundleReader _reader`
- L100 _private* property_ `object LockObject => ...`
- L102 _private* field_ `FlushedNodeHandle? _flushedHandle`
- L103 _private* field_ `PendingBundle? _pendingBundle`
- L105 _public field_ `public readonly BlobType BlobType`
- L106 _public property_ `public IoHash Hash { get; }`
- L107 _public field_ `public readonly int Packet`
- L108 _public field_ `public readonly int Offset`
- L109 _public field_ `public readonly int Length`
- L110 _public field_ `public readonly IBlobRef[] Imports`
- L111 _public field_ `public readonly AliasInfo[] Aliases`
- L113 _public property_ `public IBlobRef Innermost => ...`
- L114 _public property_ `public PendingBundle? PendingBundle => ...`
- L115 _public property_ `public FlushedNodeHandle? FlushedNodeHandle => ...`
- L117 _public property_ `public BundleHandle Outer => ...`
- L119-132 _public ctor_ `public PendingNode(BundleReader reader, BlobType blobType, IoHash hash, int packet, int offset, int length, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, PendingBundle pendingBundle)`
- L135-138 _public method_ `public bool TryAppendIdentifier(Utf8StringBuilder builder)` — (inheritdoc)
- L140-148 _public method_ `public void MarkAsWritten(FlushedNodeHandle flushedHandle)`
- L151-166 _public method_ `public async ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L169-186 _public method_ `public async ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L189-197 _public method_ `public bool TryGetLocator(out BlobLocator locator)` — (inheritdoc)
- L200 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L203 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleWriter.PendingBundle`  
`internal class PendingBundle : IDisposable`  
_internal; L207-580_
- inherits: `IDisposable`
- L209 _private* field_ `static int s_lastBundleId = 0`
- L210 _public property_ `public int BundleId { get; }`
- L212 _private* field_ `readonly BundleReader _treeReader`
- L213 _private* field_ `readonly BundleWriter _treeWriter`
- L214 _private* field_ `readonly int _maxPacketSize`
- L215 _private* field_ `readonly BundleCompressionFormat _compressionFormat`
- L217 _private* field_ `readonly Lock _lockObject = new()`
- L220 _private* field_ `IMemoryOwner<byte>? _currentPacket`
- L223 _private* field_ `int _currentPacketIdx`
- L226 _private* field_ `int _currentPacketLength`
- L229 _private* field_ `long _compressedLength`
- L232 _private* field_ `readonly List<PendingNode> _queue = []`
- L235 _private* field_ `int _queuedRefs = 0`
- L238 _private* field_ `readonly List<BundlePacket> _packets = []`
- L241 _private* field_ `readonly ChunkedMemoryWriter _encodedPacketWriter`
- L244 _private* field_ `readonly HashSet<Task> _dependencies = []`
- L247 _public property_ `public long CompressedLength => ...`
- L250 _public property_ `public long UncompressedLength { get; set; }`
- L253 _private* field_ `Task _compressPacketsTask = Task.CompletedTask`
- L256 _private* field_ `readonly TaskCompletionSource<bool> _completeEvent = new(TaskCreationOptions.RunContinuationsAsynchronously)`
- L259 _public property_ `public Task CompleteTask => ...`
- L261-268 _public ctor_ `public PendingBundle(BundleReader treeReader, BundleWriter treeWriter, int maxPacketSize, BundleCompressionFormat compressionFormat)`
- L271-281 _public method_ `public void Dispose()` — (inheritdoc)
- L284 _public method_ `public bool IsFull()`
- L287 _public method_ `public bool IsComplete()`
- L290-299 _public method_ `public void AddDependencyOn(PendingBundle bundle, ILogger? traceLogger)`
- L302-319 _public method_ `public Memory<byte> GetBuffer(int usedSize, int desiredSize)`
- L322-334 _public method_ `public PendingNode WriteNode(BlobType blobType, int size, IReadOnlyList<IBlobRef> refs, IReadOnlyList<AliasInfo> aliases)`
- L336-365 _public method_ `public ReadOnlyMemory<byte> GetNodeData(int packetIdx, int offset, int length)`
- L368-388 _private* method_ `void FlushPacket()`
- L390-403 _private* method_ `void CompressPacket(IMemoryOwner<byte> packetData, int length)`
- L406-423 _public method_ `public async Task FlushDependenciesAsync(ILogger? traceLogger, CancellationToken cancellationToken)`
- L426-481 _public method_ `public async Task WriteAsync(BundleStorageNamespace store, string? basePath, ILogger? traceLogger)`
- L484 _public method_ `public Task FlushAsync(CancellationToken cancellationToken)`
- L487-493 _public method_ `public (BundleHeader, List<ReadOnlyMemory<byte>>) CreateBundle()`
- L495-567 _private* method_ `(BundleHeader, List<ReadOnlyMemory<byte>>) CreateBundleInternal()`
- L569-579 _private* method_ `static int FindOrAddItemIndex<TItem>(TItem item, List<TItem> items, Dictionary<TItem, int> itemToIndex) where TItem : notnull`

#### class `EpicGames.Horde.Storage.Bundles.V1.BundleWriter.WriteQueue`  
`class WriteQueue`  
_private*; L582-664_
- L584 _private* field_ `long _memoryFootprint`
- L585 _private* field_ `readonly BundleStorageNamespace _store`
- L586 _private* field_ `readonly string? _basePath`
- L587 _private* field_ `readonly long _maxMemoryFootprint`
- L588 _private* field_ `readonly ILogger? _traceLogger`
- L589 _private* field_ `readonly AsyncEvent _completeEvent = new()`
- L590 _private* field_ `int _refCount`
- L591 _private* field_ `readonly List<Task> _writeTasks = []`
- L593-600 _public ctor_ `public WriteQueue(BundleStorageNamespace store, string? basePath, long maxMemoryFootprint, ILogger? traceLogger)`
- L602-605 _public method_ `public void AddRef()`
- L607-613 _public method_ `public async ValueTask ReleaseAsync()`
- L615-645 _public method_ `public async Task AddAsync(PendingBundle pendingBundle, CancellationToken cancellationToken)`
- L647-655 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken)`
- L657-663 _private* method_ `async Task WriteAsync(PendingBundle pendingBundle)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/BundleWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.BundleWriter`  
`public sealed class BundleWriter : BlobWriter`  
_public; L20-434_
- inherits: `BlobWriter`
- desc: Implements the primary storage writer interface for V2 bundles. Writes exports into packets, and flushes them to storage in bundles.
- L276 _private* field_ `readonly BundleStorageNamespace _storageNamespace`
- L277 _private* field_ `readonly string? _basePath`
- L278 _private* field_ `readonly BundleOptions _bundleOptions`
- L279 _private* field_ `readonly BundleCache _bundleCache`
- L280 _private* field_ `readonly ILogger _logger`
- L281 _private* field_ `readonly CancellationToken _cancellationToken`
- L283 _private* field_ `readonly string _locatorPrefix`
- L284 _private* field_ `int _locatorSuffix`
- L286 _private* field_ `PendingBundleHandle _currentBundle`
- L288 _private* field_ `readonly Lock _lockObject = new()`
- L289 _private* field_ `Task _flushTask = Task.CompletedTask`
- L294-320 _public ctor_ `public BundleWriter(BundleStorageNamespace storageNamespace, string? basePath, BundleCache bundleCache, BundleOptions bundleOptions, BlobSerializerOptions? blobOptions, ILogger logger, CancellationToken cancellationToken) : base(blobOptions)` — Constructor
- L322 _private* method_ `BlobLocator GetNextLocator()`
- L326-330 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L332-336 _private* method_ `async Task WriteCurrentBundleAsync(CancellationToken cancellationToken = default)`
- L338-362 _private* method_ `async Task<Task> StartWriteAsync(PendingBundleHandle bundle, CancellationToken cancellationToken)`
- L364-389 _private* method_ `async Task HandleBundleWriteAsync(Task lockTask, PendingBundleHandle bundle)`
- L392-403 _public method_ `public override async Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L406 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)
- L410 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — (inheritdoc)
- L414-422 _public method_ `public override async ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> references, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken = default)` — (inheritdoc)
- L427-433 _private* method_ `static void RuntimeAssert([DoesNotReturnIf(false)] bool condition, [CallerArgumentExpression(nameof(condition))] string? message = null)` — Helper method to check a precondition is valid at runtime, regardless of build configuration.

#### class `EpicGames.Horde.Storage.Bundles.V2.BundleWriter.PendingPacketHandle`  
`internal sealed class PendingPacketHandle : PacketHandle`  
_internal; L23-53_
- inherits: `PacketHandle`
- L25 _private* field_ `readonly PendingBundleHandle _bundle`
- L26 _private* field_ `FlushedPacketHandle? _flushedHandle`
- L28 _public property_ `public override BundleHandle Bundle => ...`
- L29 _public property_ `public FlushedPacketHandle? FlushedHandle => ...`
- L31 _public ctor_ `public PendingPacketHandle(PendingBundleHandle bundle)`
- L33 _public method_ `public override ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L36 _public method_ `public void CompletePacket(FlushedPacketHandle flushedHandle)`
- L39-49 _public method_ `public override async ValueTask<BlobData> ReadExportAsync(int exportIdx, CancellationToken cancellationToken = default)`
- L51 _public method_ `public override bool TryAppendIdentifier(Utf8StringBuilder builder)`

#### class `EpicGames.Horde.Storage.Bundles.V2.BundleWriter.PendingBundleHandle`  
`internal sealed class PendingBundleHandle : BundleHandle, IDisposable`  
_internal; L56-274_
- inherits: `BundleHandle, IDisposable`
- L58 _public field_ `public readonly Lock LockObject = new()`
- L60 _private* field_ `readonly BundleWriter _outer`
- L61 _private* field_ `readonly BundleStorageNamespace _storageNamespace`
- L62 _private* field_ `readonly BundleCache _bundleCache`
- L63 _private* field_ `readonly BundleOptions _bundleOptions`
- L65 _private* field_ `FlushedBundleHandle? _flushedHandle`
- L67 _private* field_ `PacketWriter? _packetWriter`
- L68 _private* field_ `PendingPacketHandle? _packetHandle`
- L69 _private* field_ `List<(ExportHandle, AliasInfo)>? _pendingExportAliases`
- L70 _private* field_ `RefCountedMemoryWriter? _encodedPacketWriter`
- L71 _private* field_ `readonly HashSet<BlobLocator> _bundleImports = []`
- L73 _public field_ `public Task? _lockTask`
- L74 _public field_ `public Task? _writeTask`
- L76 _public property_ `public FlushedBundleHandle? FlushedHandle => ...`
- L81 _public property_ `public int Length => ...` — Compressed length of this bundle
- L83-94 _public ctor_ `public PendingBundleHandle(BundleWriter outer, BlobLocator locator) : base(locator)`
- L96 _public method_ `public void Dispose()`
- L98-108 _private* method_ `void ReleaseResources()`
- L110-114 _public method_ `public Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)`
- L116-120 _public method_ `public BlobData GetPendingExport(int exportIdx)`
- L122-145 _public method_ `public HashedExportHandle CompleteExport(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases)`
- L147-154 _private* method_ `void StartPacket()`
- L156-183 _private* method_ `void FinishPacket()`
- L185-192 _public method_ `public override async ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L195-238 _public method_ `public async Task WriteAsync(CancellationToken cancellationToken = default)`
- L241-250 _public method_ `public override async Task<Stream> OpenAsync(int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L253-273 _public method_ `public override async ValueTask<IReadOnlyMemoryOwner<byte>> ReadAsync(int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/ExportHandle.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.ExportHandle`  
`public class ExportHandle : IBlobRef`  
_public; L15-141_
- inherits: `IBlobRef`
- desc: Handle class for blobs exported from a bundle
- L17 _private* field_ `static readonly Utf8String s_fragmentPrefix = new("exp=")`
- L22 _public property_ `public PacketHandle Packet => ...` — Accessor for the packet that this export is in
- L27 _public property_ `public int ExportIdx => ...` — Export index within the packet
- L29 _private* field_ `readonly PacketHandle _packet`
- L30 _private* field_ `readonly int _exportIdx`
- L33 _public property_ `public IBlobRef Innermost => ...` — (inheritdoc)
- L38-42 _public ctor_ `public ExportHandle(PacketHandle packet, int exportIdx)` — Constructor
- L47-54 _public ctor_ `public ExportHandle(PacketHandle packet, ReadOnlySpan<byte> fragment)` — Constructor
- L57 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L61 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L67-83 _public method_ `public static bool TryParse(ReadOnlySpan<byte> fragment, out int exportIdx)` — Attempt to parse an export index from the given fragment
- L88-93 _public method_ `public Utf8String GetIdentifier()` — Get an identifier for this export within the outer packet
- L98-107 _public method_ `public bool TryAppendLocator(Utf8StringBuilder builder)` — Append a locator for this export to the given string builder
- L112-116 _public method_ `public void AppendIdentifier(Utf8StringBuilder builder)` — Appends an export identifier to the given string builder
- L119-132 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)` — (inheritdoc)
- L135 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L139 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Bundles.V2.HashedExportHandle`  
`public class HashedExportHandle : ExportHandle, IHashedBlobRef`  
_public; L146-161_
- inherits: `ExportHandle, IHashedBlobRef`
- desc: Implementation of ExportHandle which also contains a hash
- L148 _private* field_ `readonly IoHash _hash`
- L151 _public property_ `public IoHash Hash => ...` — (inheritdoc)
- L156-160 _public ctor_ `public HashedExportHandle(IoHash hash, PacketHandle packet, int exportIdx) : base(packet, exportIdx)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/Packet.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.Packet`  
`public sealed class Packet`  
_public; L54-232_
- attrs: `[DebuggerTypeProxy(typeof(Packet.DebugProxy))]`
- desc: Accessor for data structures stored into a serialized bundle packet.
- L59 _public property_ `public static BlobType BlobType { get; }` — Type for packet blobs
- L75 _private* field_ `readonly ReadOnlyMemory<byte> _data`
- L81 _public ctor_ `public Packet(ReadOnlyMemory<byte> data)` — Constructor
- L86 _public property_ `public ReadOnlyMemory<byte> Data => ...` — Accessor for the underlying packet data
- L91 _public property_ `public int Length => ...` — Length of this packet
- L96-101 _public method_ `public int GetTypeCount()` — Gets the number of types in this packet
- L106-119 _public method_ `public BlobType GetType(int typeIdx)` — Gets a type from the packet
- L124-129 _public method_ `public int GetImportCount()` — Gets the number of imports in this packet
- L135-152 _public method_ `public PacketImport GetImport(int importIdx)` — Gets the locator for a particular import
- L157-162 _public method_ `public int GetExportCount()` — Gets the number of exports in this packet
- L168-185 _public method_ `public PacketExport GetExport(int exportIdx)` — Gets the bulk data for a particular export
- L192-202 _public method_ `public void Encode(BundleCompressionFormat format, IMemoryWriter writer)` — Encodes a packet
- L207-231 _public method_ `public static IRefCountedHandle<Packet> Decode(ReadOnlyMemory<byte> data, IMemoryAllocator<byte> allocator, object? allocationTag)` — Decodes this packet

#### class `EpicGames.Horde.Storage.Bundles.V2.Packet.DebugProxy`  
`class DebugProxy`  
_private*; L61-73_
- L63 _public property_ `public BlobType[] Types { get; }`
- L64 _public property_ `public PacketImport[] Imports { get; }`
- L65 _public property_ `public PacketExport[] Exports { get; }`
- L67-72 _public ctor_ `public DebugProxy(Packet packet)`

#### record struct `EpicGames.Horde.Storage.Bundles.V2.PacketImport`  
`public readonly record struct PacketImport(int BaseIdx, Utf8String Fragment)`  
_public; L239-271_
- desc: Raw data for an imported node
- L244 _public const_ `public const int Bias = 3` — Bias for indexes into the import table
- L249 _public const_ `public const int InvalidBaseIdx = -1`
- L254 _public const_ `public const int CurrentPacketBaseIdx = -2`
- L259 _public const_ `public const int CurrentBundleBaseIdx = -3`
- L264-270 _public method_ `public static PacketImport Read(ReadOnlyMemory<byte> data)` — Reads an import from a block of memory

#### struct `EpicGames.Horde.Storage.Bundles.V2.PacketExport`  
`public readonly struct PacketExport`  
_public; L277-323_
- attrs: `[DebuggerTypeProxy(typeof(PacketExport.DebugProxy))]`
- desc: Data for an exported node in a packet
- L297 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data for this export
- L302 _public ctor_ `public PacketExport(ReadOnlyMemory<byte> data)` — Constructor
- L307-312 _public method_ `public PacketExportHeader GetHeader()` — Gets the header for this export
- L317-322 _public method_ `public ReadOnlyMemory<byte> GetPayload()` — Gets the payload for this export

#### class `EpicGames.Horde.Storage.Bundles.V2.PacketExport.DebugProxy`  
`class DebugProxy`  
_private*; L279-292_
- L281 _public property_ `public int TypeIdx { get; }`
- L282 _public property_ `public int[] Imports { get; }`
- L283 _public property_ `public ReadOnlyMemory<byte> Payload { get; }`
- L285-291 _public ctor_ `public DebugProxy(PacketExport export)`

#### struct `EpicGames.Horde.Storage.Bundles.V2.PacketExportHeader`  
`public readonly struct PacketExportHeader`  
_public; L328-360_
- desc: Data for an exported node in a bundle
- L333 _public property_ `public int TypeIdx { get; }` — Index of the type for this export
- L338 _public property_ `public int[] Imports { get; }` — Index of imports for this export
- L343-359 _public ctor_ `public PacketExportHeader(ReadOnlySpan<byte> span)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/PacketHandle.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.PacketHandle`  
`public abstract class PacketHandle`  
_public; L18-52_
- desc: Base class for packet handles
- L23 _public property_ `public abstract BundleHandle Bundle { get; }` — Bundle containing this packet
- L26 _public method_ `public abstract ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L31 _public method_ `public abstract ValueTask<BlobData> ReadExportAsync(int exportIdx, CancellationToken cancellationToken = default)` — Reads an export from this packet
- L36 _public method_ `public abstract bool TryAppendIdentifier(Utf8StringBuilder builder)` — Append the identifier for this packet to the given string builder
- L41-51 _public method_ `public bool TryAppendLocator(Utf8StringBuilder builder)` — Appends the locator to the given string builder

#### class `EpicGames.Horde.Storage.Bundles.V2.FlushedPacketHandle`  
`class FlushedPacketHandle : PacketHandle`  
_internal*; L57-296_
- inherits: `PacketHandle`
- desc: Handle to an packet within a bundle.
- L59 _private* field_ `readonly BundleStorageNamespace _storageNamespace`
- L60 _private* field_ `readonly BundleHandle _outer`
- L61 _private* field_ `readonly int _packetOffset`
- L62 _private* field_ `readonly int _packetLength`
- L63 _private* field_ `readonly BundleCache _cache`
- L65 _private* field_ `static readonly Utf8String s_fragmentPrefix = new("pkt=")`
- L68 _public property_ `public override BundleHandle Bundle => ...` — (inheritdoc)
- L73 _public property_ `public int PacketOffset => ...` — Offset of the packet within the bundle
- L78 _public property_ `public int PacketLength => ...` — Length of the packet within the bundle
- L83-91 _public ctor_ `public FlushedPacketHandle(BundleStorageNamespace storageNamespace, BundleHandle outer, int packetOffset, int packetLength, BundleCache cache)` — Constructor
- L96-107 _public ctor_ `public FlushedPacketHandle(BundleStorageNamespace storageNamespace, BundleHandle outer, ReadOnlySpan<byte> fragment, BundleCache cache)` — Constructor
- L112-142 _private* method_ `static bool TryParse(ReadOnlySpan<byte> fragment, out int packetOffset, out int packetLength)` — Parse a fragment containing an offset and length
- L148-156 _private* method_ `Utf8String GetLocator()`
- L159 _public method_ `public override ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L166-187 _public method_ `public override async ValueTask<BlobData> ReadExportAsync(int exportIdx, CancellationToken cancellationToken = default)` — Reads an export from this packet
- L190-194 _public method_ `public override bool TryAppendIdentifier(Utf8StringBuilder builder)` — (inheritdoc)
- L199-205 _public method_ `public static void AppendIdentifier(Utf8StringBuilder builder, int packetOffset, int packetLength)` — Appends an identifier for a packet to the given buffer
- L208 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L212 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L217-221 _private* method_ `async ValueTask<Lifetime<PacketReader>> GetPacketReaderAsync(CancellationToken cancellationToken = default)`
- L223-228 _internal method_ `internal PacketReader CreatePacketReader(ReadOnlyMemory<byte> encodedData)`
- L230-239 _private* method_ `async Task<Scoped<PacketReader>> CreatePacketReaderAsync(PacketReaderCacheKey cacheKey, CancellationToken cancellationToken)`
- L241-267 _private* method_ `async ValueTask<IReadOnlyMemoryOwner<byte>> ReadEncodedPacketAsync(CancellationToken cancellationToken)`
- L269-273 _private* method_ `async ValueTask<Lifetime<IReadOnlyMemoryOwner<byte>>> ReadBundlePageAsync(int pageIdx, CancellationToken cancellationToken)`
- L275-286 _private* method_ `async Task ReadBundlePageAsync(int pageIdx, Memory<byte> targetMemory, CancellationToken cancellationToken)`
- L288-293 _private* method_ `async Task<Scoped<IReadOnlyMemoryOwner<byte>>> ReadBundlePageInternalAsync(BundlePageCacheKey key, CancellationToken cancellationToken)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/PacketReader.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.PacketReaderStats`  
`class PacketReaderStats`  
_internal*; L12-24_
- desc: Counters used for tracking operations performed by a BundleStorageNamespace
- L14 _public field_ `public long _numBytesRead`
- L15 _public field_ `public long _numEncodedBytesRead`
- L16 _public field_ `public long _numDecodedBytesRead`
- L18-23 _public method_ `public void GetStats(StorageStats stats)`

#### record struct `EpicGames.Horde.Storage.Bundles.V2.PacketReaderCacheKey`  
`readonly record struct PacketReaderCacheKey(BundleHandle Bundle, int Offset)`  
_internal*; L26-30_
- L28 _public method_ `public override string ToString()`

#### class `EpicGames.Horde.Storage.Bundles.V2.PacketReader`  
`sealed class PacketReader : IDisposable`  
_internal*; L35-194_
- inherits: `IDisposable`
- desc: Utility class for constructing BlobData objects from a packet, caching any computed handles to other blobs.
- L37 _private* field_ `readonly BundleStorageNamespace _storageNamespace`
- L38 _private* field_ `readonly BundleCache _cache`
- L39 _private* field_ `readonly BundleHandle _bundleHandle`
- L40 _private* field_ `readonly FlushedPacketHandle _packetHandle`
- L42 _private* field_ `Packet _decodedPacket`
- L43 _private* field_ `object?[] _cachedImportHandles`
- L44 _private* field_ `IRefCountedHandle _memoryOwner`
- L49 _public property_ `public Packet Packet => ...` — Accessor for the underlying packet data
- L60-69 _public ctor_ `public PacketReader(BundleStorageNamespace storageNamespace, BundleCache cache, BundleHandle bundleHandle, FlushedPacketHandle packetHandle, Packet decodedPacket, IRefCountedHandle memoryOwner)` — Constructor
- L72-82 _public method_ `public void Dispose()` — (inheritdoc)
- L87-95 _public method_ `public BlobData Read()` — Reads this packet in its entirety
- L101-122 _public method_ `public BlobData ReadExport(int exportIdx)` — Reads an export from this packet
- L128-132 _public method_ `public IReadOnlyMemoryOwner<byte> ReadExportBody(int exportIdx)` — Reads an export from this packet
- L137-152 _private* method_ `IBlobRef GetImportedBlobHandle(int blobIdx)` — Gets an import handle for the packet
- L154-174 _private* method_ `PacketHandle GetImportedPacketHandle(int packetIdx)`
- L176-193 _private* method_ `BundleHandle GetImportedBundleHandle(int bundleIdx)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Bundles/V2/PacketWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Bundles.V2.PacketWriter`  
`public sealed class PacketWriter : IDisposable`  
_public; L17-426_
- inherits: `IDisposable`
- desc: Writes exports into a new bundle packet
- L19 _private* const_ `const string AllocationTag = nameof(PacketWriter)`
- L21 _private* field_ `readonly BundleHandle _bundleHandle`
- L22 _private* field_ `readonly PacketHandle _packetHandle`
- L23 _private* field_ `readonly IMemoryAllocator<byte> _allocator`
- L24 _private* field_ `readonly Lock _lockObject`
- L26 _private* field_ `IRefCountedHandle<Memory<byte>> _bufferHandle`
- L27 _private* field_ `Memory<byte> _buffer`
- L29 _private* field_ `int _length`
- L31 _private* field_ `readonly List<BlobType> _types = []`
- L32 _private* field_ `readonly List<PacketImport> _imports = []`
- L33 _private* field_ `readonly List<object> _importHandles = []`
- L34 _private* field_ `readonly Dictionary<object, int> _importMap = ...`
- L34 _private* field_ `readonly Dictionary< _importMap = []`
- L35 _private* field_ `readonly List<int> _exportOffsets = []`
- L36 _private* field_ `readonly HashSet<int> _bundleImportIndices = []`
- L41 _public property_ `public int Length => ...` — Current length of the packet
- L46 _public property_ `public IEnumerable<BlobLocator> BundleImports => ...` — Enumerate all imported bundle locators
- L52-78 _public ctor_ `public PacketWriter(BundleHandle bundleHandle, PacketHandle packetHandle, IMemoryAllocator<byte> allocator, Lock lockObject)` — Constructor
- L81-90 _public method_ `public void Dispose()` — (inheritdoc)
- L95 _public method_ `public int GetExportCount()` — Gets the number of exports currently in this writer
- L103-113 _public method_ `public int CompleteExport(int size, BlobType type, IReadOnlyList<IBlobRef> imports)` — Writes a new blob to this packet
- L121-144 _internal method_ `internal int CompleteExport(int size, int typeIdx, int[] imports)` — Complete the current export
- L151-171 _public method_ `public BlobData GetExport(int exportIdx)` — Reads data for a blob written to storage
- L178-187 _public method_ `public int FindOrAddType(BlobType type)` — Add a new blob type to be written
- L189-200 _private* method_ `int AddImport(int baseIdx, Utf8String fragment, object handle)`
- L207 _public method_ `public int FindOrAddImport(IBlobRef handle)` — Adds a new imported blob locator
- L209-257 _private* method_ `int FindOrAddImportInternal(object handle)`
- L262 _public method_ `public IBlobRef GetImport(int importIdx)` — Gets the import assigned to a particular index
- L268-273 _public method_ `public BlobLocator GetImportLocator(int importIdx)` — Gets the import assigned to a particular index
- L275-283 _private* method_ `void BuildImportLocator(int importIdx, Utf8StringBuilder builder)`
- L291-301 _public method_ `public Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — Gets data to write new export
- L306 _private* method_ `static int Align(int value, int alignment)` — Aligns an offset to a power-of-2 boundary
- L311-328 _private* method_ `Memory<byte> GetOutputBufferInternal(int usedSize, int desiredSize)` — Gets data to write new export
- L333-338 _private* method_ `Span<byte> GetOutputSpanAndAdvance(int length)` — Gets an output span and updates the length accordingly
- L343-355 _public method_ `public Packet CompletePacket()` — Mark the current packet as complete
- L357-373 _private* method_ `void WriteTypeTable()`
- L375-410 _private* method_ `void WriteImportTable()`
- L412-425 _private* method_ `void WriteExportTable()`

### `Source/Programs/Shared/EpicGames.Horde/Storage/ContentChunker.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ContentChunker`  
`public abstract class ContentChunker`  
_public; L18-31_
- desc: Base class for implementations of a content defined chunker
- L23 _public property_ `public abstract ChannelWriter<ChunkerSource> SourceWriter { get; }` — Source channel.
- L30 _public property_ `public abstract ChannelReader<ChunkerOutput> OutputReader { get; }` — Output channel. The order of items written to the source writer will be preserved in the output reader. Each output item should be read completely (through calls to ChunkerOutput.MoveNextAsync(CancellationToken)) before reading the next.

#### class `EpicGames.Horde.Storage.ChunkerSource`  
`public abstract class ChunkerSource`  
_public; L36-54_
- desc: Base class for input to a ContentChunker. Allows the chunker to read data into a buffer as required.
- L41 _public property_ `public abstract long Length { get; }` — Length of the input data
- L46 _public property_ `public virtual object? UserData { get; }` — Optional user specified data to be propagated to the output
- L53 _public method_ `public abstract Task<Task> StartReadAsync(Memory<byte> memory, CancellationToken cancellationToken = default)` — Starts a task to read the next chunk of data. Note that this task may be called again before the task completes.

#### class `EpicGames.Horde.Storage.FileChunkerSource`  
`public class FileChunkerSource : ChunkerSource`  
_public; L59-100_
- inherits: `ChunkerSource`
- desc: Implementation of ChunkerSource for files on disk
- L61 _private* field_ `readonly FileInfo _fileInfo`
- L62 _private* field_ `readonly object? _userData`
- L63 _private* field_ `long _offset`
- L66 _public property_ `public override object? UserData => ...` — (inheritdoc)
- L72-76 _public ctor_ `public FileChunkerSource(FileInfo fileInfo, object? userData)` — Constructor
- L79 _public property_ `public override long Length => ...` — (inheritdoc)
- L83-88 _public method_ `public override Task<Task> StartReadAsync(Memory<byte> memory, CancellationToken cancellationToken = default)` — (inheritdoc)
- L91-99 _private* method_ `async Task HandleReadAsync(long offset, Memory<byte> memory, CancellationToken cancellationToken)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.MemoryChunkerSource`  
`class MemoryChunkerSource : ChunkerSource`  
_internal*; L105-126_
- inherits: `ChunkerSource`
- desc: Implementation of ChunkerSource for data in memory
- L107 _private* field_ `readonly ReadOnlyMemory<byte> _data`
- L108 _private* field_ `int _offset`
- L111 _public property_ `public override long Length => ...` — (inheritdoc)
- L116 _public ctor_ `public MemoryChunkerSource(Memory<byte> data)` — Constructor
- L120-125 _public method_ `public override Task<Task> StartReadAsync(Memory<byte> memory, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.ChunkerOutput`  
`public abstract class ChunkerOutput`  
_public; L131-154_
- desc: Enumerates chunks from an input file
- L136 _public property_ `public abstract uint RollingHash { get; }` — Rolling hash for this chunk
- L141 _public property_ `public abstract ReadOnlyMemory<byte> Data { get; }` — Accessor for the chunk's data
- L146 _public property_ `public abstract object? UserData { get; }` — User specified data from the ChunkerSource
- L153 _public method_ `public abstract ValueTask<bool> MoveNextAsync(CancellationToken cancellationToken = default)` — Moves to the next output chunk

#### class `EpicGames.Horde.Storage.SerialBuzHashChunker`  
`public class SerialBuzHashChunker : ContentChunker`  
_public; L159-300_
- inherits: `ContentChunker`
- desc: Simple serial implementation of content chunking
- L187 _private* field_ `readonly Memory<byte> _buffer`
- L188 _private* field_ `readonly Channel<ChunkerSource> _sourceChannel`
- L189 _private* field_ `readonly Channel<ChunkerOutput> _outputChannel`
- L190 _private* field_ `readonly LeafChunkedDataNodeOptions _options`
- L191 _private* field_ `readonly Queue<Output> _order = new()`
- L193 _private* field_ `int _bufferOffset`
- L194 _private* field_ `int _bufferLength`
- L195 _private* field_ `int _chunkLength`
- L198 _public property_ `public override ChannelWriter<ChunkerSource> SourceWriter => ...` — (inheritdoc)
- L202 _public property_ `public override ChannelReader<ChunkerOutput> OutputReader => ...` — (inheritdoc)
- L208-216 _public ctor_ `public SerialBuzHashChunker(AsyncPipeline pipeline, Memory<byte> buffer, LeafChunkedDataNodeOptions options)` — Constructor
- L218-240 _private* method_ `async Task ProcessInputAsync(CancellationToken cancellationToken)`
- L242-299 _private* method_ `async ValueTask<bool> MoveNextAsync(ChunkerSource input, Output output, CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Storage.SerialBuzHashChunker.Output`  
`class Output : ChunkerOutput`  
_private*; L161-185_
- inherits: `ChunkerOutput`
- L163 _private* field_ `readonly SerialBuzHashChunker _pipeline`
- L164 _public field_ `public readonly ChunkerSource Input`
- L166 _public field_ `public bool _firstOutput = true`
- L167 _public field_ `public uint _rollingHash`
- L168 _public field_ `public long _inputOffset`
- L169 _public field_ `public long _outputOffset`
- L170 _public field_ `public ReadOnlyMemory<byte> _data`
- L172 _public property_ `public override uint RollingHash => ...`
- L173 _public property_ `public override ReadOnlyMemory<byte> Data => ...`
- L174 _public property_ `public override object? UserData => ...`
- L176-180 _public ctor_ `public Output(SerialBuzHashChunker pipeline, ChunkerSource input)`
- L183 _public method_ `public override ValueTask<bool> MoveNextAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.ParallelBuzHashChunker`  
`public class ParallelBuzHashChunker : ContentChunker`  
_public; L305-655_
- inherits: `ContentChunker`
- desc: Parallel implementation of SerialBuzHashChunker
- L307 _private* const_ `const int ReadBlockSize = 256 * 1024`
- L514 _private* field_ `readonly RingBuffer _ringBuffer`
- L515 _private* field_ `readonly LeafChunkedDataNodeOptions _options`
- L517 _private* field_ `readonly Channel<ChunkerSource> _inputChannel`
- L518 _private* field_ `readonly Channel<ChunkerOutput> _outputChannel`
- L520 _private* field_ `readonly Channel<InputRequest> _inputRequestChannel`
- L521 _private* field_ `readonly Channel<BlockRequest> _blockRequestChannel`
- L524 _public property_ `public override ChannelWriter<ChunkerSource> SourceWriter => ...` — (inheritdoc)
- L528 _public property_ `public override ChannelReader<ChunkerOutput> OutputReader => ...` — (inheritdoc)
- L534-536 _public ctor_ `public ParallelBuzHashChunker(AsyncPipeline pipeline, LeafChunkedDataNodeOptions options) : this(pipeline, new byte[2 * 1024 * 1024], options)` — Constructor
- L541-564 _public ctor_ `public ParallelBuzHashChunker(AsyncPipeline pipeline, Memory<byte> buffer, LeafChunkedDataNodeOptions options)` — Constructor
- L566-583 _private* method_ `async Task ProcessInputAsync(CancellationToken cancellationToken)`
- L585-590 _private* method_ `async Task<ChunkerOutput> AddAsync(ChunkerSource input, CancellationToken cancellationToken = default)`
- L592-633 _private* method_ `async Task ProcessInputRequestsAsync(CancellationToken cancellationToken)`
- L635-654 _private* method_ `async Task ProcessBlockRequestsAsync(CancellationToken cancellationToken)`

#### record `EpicGames.Horde.Storage.ParallelBuzHashChunker.InputRequest`  
`record class InputRequest(ChunkerSource Input, TaskCompletionSource<Block> FirstBlockTcs)`  
_private*; L309-309_

#### record `EpicGames.Horde.Storage.ParallelBuzHashChunker.BlockRequest`  
`record class BlockRequest(int BufferOffset, int Length, Task ReadTask, TaskCompletionSource<Block> BlockTcs, Task<Block>? NextBlock)`  
_private*; L310-310_

#### record `EpicGames.Horde.Storage.ParallelBuzHashChunker.Block`  
`record class Block(int BufferOffset, int Length, List<(int, uint)> Boundaries, Task<Block>? Next)`  
_private*; L311-311_

#### class `EpicGames.Horde.Storage.ParallelBuzHashChunker.RingBuffer`  
`class RingBuffer`  
_private*; L313-397_
- L315 _private* field_ `readonly Lock _lockObject = new()`
- L317 _private* field_ `int _head`
- L318 _private* field_ `int _size`
- L320 _private* field_ `readonly Memory<byte> _data`
- L321 _private* field_ `readonly int _wrapSize`
- L322 _private* field_ `readonly AsyncEvent _freeEvent = new()`
- L324-328 _public ctor_ `public RingBuffer(Memory<byte> data, int wrapSize)`
- L330 _public method_ `public Memory<byte> GetData(int offset, int length)`
- L333-367 _public method_ `public async Task<int> AllocAsync(int blockSize, CancellationToken cancellationToken)`
- L369-396 _public method_ `public void Free(int offset, int length)`

#### class `EpicGames.Horde.Storage.ParallelBuzHashChunker.LatestCdcOutput`  
`class LatestCdcOutput : ChunkerOutput`  
_private*; L399-512_
- inherits: `ChunkerOutput`
- L401 _private* field_ `readonly ParallelBuzHashChunker _pipeline`
- L402 _private* field_ `readonly object? _userData`
- L404 _private* field_ `Task<Block> _blockTask`
- L405 _private* field_ `int _blockOffset`
- L406 _private* field_ `int _boundaryIdx`
- L407 _private* field_ `uint _rollingHash`
- L408 _private* field_ `ReadOnlyMemory<byte> _data`
- L409 _private* field_ `bool _firstChunk = true`
- L411-416 _public ctor_ `public LatestCdcOutput(ParallelBuzHashChunker pipeline, object? userData, Task<Block> blockTask)`
- L418 _public property_ `public override uint RollingHash => ...`
- L421 _public property_ `public override ReadOnlyMemory<byte> Data => ...`
- L424 _public property_ `public override object? UserData => ...`
- L427-511 _public method_ `public override async ValueTask<bool> MoveNextAsync(CancellationToken cancellationToken = default)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/DedupeBlobWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.DedupeBlobWriter`  
`public sealed class DedupeBlobWriter : BlobWriter`  
_public; L16-178_
- inherits: `BlobWriter`
- desc: Index of known nodes that can be used for deduplication.
- L81 _public const_ `public const int DefaultMaxKeys = 512 * 1024` — Default value for maximum number of keys
- L83 _private* field_ `readonly BlobWriter _inner`
- L84 _private* field_ `readonly DedupeCache _cache`
- L86 _private* field_ `int _numHits`
- L87 _private* field_ `long _totalHitsSize`
- L88 _private* field_ `int _numMisses`
- L89 _private* field_ `long _totalMissesSize`
- L90 _private* field_ `int _numCacheAdds`
- L97-102 _public ctor_ `public DedupeBlobWriter(IBlobWriter inner, int maxKeys = DefaultMaxKeys) : base(inner.Options)` — Constructor
- L104-109 _private ctor_ `private DedupeBlobWriter(IBlobWriter inner, DedupeCache cache) : base(inner.Options)`
- L112 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L115 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L118 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)
- L121 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — (inheritdoc)
- L128-132 _public method_ `public void AddToCache(BlobType type, IHashedBlobRef blobRef)` — Add a blob to the cache
- L135-163 _public method_ `public override async ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken = default)` — (inheritdoc)
- L168-177 _public method_ `public StorageStats GetStats()` — Gets stats for the copy operation

#### record `EpicGames.Horde.Storage.DedupeBlobWriter.BlobKey`  
`record BlobKey(IoHash Hash, BlobType Type)`  
_private*; L18-18_

#### class `EpicGames.Horde.Storage.DedupeBlobWriter.DedupeCache`  
`class DedupeCache`  
_private*; L20-44_
- L22 _private* field_ `readonly int _maxKeys`
- L23 _private* field_ `readonly Queue<BlobKey> _blobKeys = new()`
- L24 _private* field_ `readonly Dictionary<BlobKey, IHashedBlobRef> _blobKeyToHandle = ...`
- L24 _private* field_ `readonly Dictionary< _blobKeyToHandle = []`
- L26-31 _public ctor_ `public DedupeCache(int maxKeys)`
- L33-41 _internal method_ `internal void Add(BlobKey key, IHashedBlobRef handle)`
- L43 _internal method_ `internal bool TryGetValue(BlobKey key, [NotNullWhen(true)] out IHashedBlobRef? handle)`

#### class `EpicGames.Horde.Storage.DedupeBlobWriter.WrappedHandle`  
`class WrappedHandle : IHashedBlobRef`  
_private*; L46-76_
- inherits: `IHashedBlobRef`
- L48 _public field_ `public object _lockObject = new()`
- L49 _public field_ `public IHashedBlobRef? _inner`
- L52 _public property_ `public IBlobRef Innermost => ...` — (inheritdoc)
- L56 _public property_ `public IoHash Hash => ...` — (inheritdoc)
- L60 _public method_ `public bool TryGetLocator(out BlobLocator locator)` — (inheritdoc)
- L64 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken)` — (inheritdoc)
- L68 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L72 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L75 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.DedupeBlobWriterExtensions`  
`public static class DedupeBlobWriterExtensions`  
_public; L183-264_
- desc: Extension methods for IBlobWriter
- L188 _public method_ `public static DedupeBlobWriter WithDedupe(this IBlobWriter writer, int maxKeys = DedupeBlobWriter.DefaultMaxKeys)` — Wraps a IBlobWriter with a DedupeBlobWriter
- L195-199 _public method_ `public static DedupeBlobWriter CreateDedupeBlobWriter(this IStorageNamespace store, int maxKeys = DedupeBlobWriter.DefaultMaxKeys)` — Creates a dedupe writer
- L207-211 _public method_ `public static DedupeBlobWriter CreateDedupeBlobWriter(this IStorageNamespace store, RefName refName, int maxKeys = DedupeBlobWriter.DefaultMaxKeys)` — Creates a writer using a refname as a base path
- L219-237 _public method_ `public static async Task AddToCacheAsync(this DedupeBlobWriter dedupeWriter, IBlobRef<DirectoryNode> directoryNodeRef, CancellationToken cancellationToken = default)` — Adds a directory tree to the cache
- L245-263 _public method_ `public static async Task AddToCacheAsync(this DedupeBlobWriter dedupeWriter, ChunkedDataNodeRef dataNodeRef, CancellationToken cancellationToken = default)` — Adds a chunked data stream to the cache

### `Source/Programs/Shared/EpicGames.Horde/Storage/EncodedBlobData.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.EncodedBlobData`  
`public class EncodedBlobData`  
_public; L16-160_
- desc: Stores a BlobData object in a fixed memory buffer for transport over the wire.
- L23 _private* field_ `static readonly Version s_currentVersion = Enum.GetValues(typeof(Version)).Cast<Version>().Max()`
- L37 _private* field_ `readonly LocatorCollection _imports`
- L42 _public property_ `public BlobType Type { get; }` — Type of the blob
- L47 _public property_ `public ReadOnlyMemory<byte> Payload { get; }` — The blob data payload
- L52 _public property_ `public IReadOnlyList<BlobLocator> Imports => ...` — References to other blobs
- L57-83 _public ctor_ `public EncodedBlobData(ReadOnlyMemory<byte> memory)` — Constructor
- L88-97 _public method_ `public static byte[] Create(BlobData blobData)` — Encode a blob data object to a byte aray
- L102-111 _public method_ `public static byte[] Create(BlobType type, BlobLocator[] locators, ReadOnlyMemory<byte> data)` — Encode a blob data object to a byte aray
- L116-124 _public method_ `public static int GetHeaderLength(BlobLocator[] locators)` — Gets the length of an encoded blob data object
- L129-159 _public method_ `public static void WriteHeader(BlobType type, BlobLocator[] locators, Span<byte> output)` — Encodes blob data into an existing buffer

#### enum `EpicGames.Horde.Storage.EncodedBlobData.Version`  
`enum Version`  
_private*; L18-21_
- L20 _public* enumerator_ `Initial`

#### struct `EpicGames.Horde.Storage.EncodedBlobData.LocatorCollection`  
`readonly struct LocatorCollection : IReadOnlyList<BlobLocator>`  
_private*; L25-35_
- inherits: `IReadOnlyList<BlobLocator>`
- L27 _public field_ `public readonly JaggedReadOnlyMemoryArray Array`
- L29 _public ctor_ `public LocatorCollection(JaggedReadOnlyMemoryArray array)`
- L30 _public indexer_ `public BlobLocator this[int index]`
- L31 _public property_ `public int Count => ...`
- L32 _public method_ `public IEnumerator<BlobLocator> GetEnumerator()`
- L34 _private* method_ `IEnumerator IEnumerable.GetEnumerator()`

### `Source/Programs/Shared/EpicGames.Horde/Storage/FileMetadataDb.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.FileMetadataDb`  
`public sealed class FileMetadataDb : IDisposable`  
_public; L19-383_
- inherits: `IDisposable`
- desc: Database of file metadata, storing timestamps for trees of files and hashes for ranges within them. Implemented as a SQLite database.
- L24 _public const_ `public const int RootDirectoryId = 0` — Id value for the root directory
- L40 _private* field_ `static readonly IoHashTypeMapper s_hashTypeMapper = new()`
- L42 _private* field_ `readonly SqliteConnection _connection`
- L44-47 _private* ctor_ `FileMetadataDb(SqliteConnection connection)`
- L50-53 _public method_ `public void Dispose()` — (inheritdoc)
- L58-61 _public method_ `public static async Task<FileMetadataDb> CreateInMemoryAsync(CancellationToken cancellationToken = default)` — Creates a new in-memory database for file metadata
- L66-69 _public method_ `public static async Task<FileMetadataDb> CreateFromFileAsync(FileReference file, CancellationToken cancellationToken = default)` — Creates a new database for metadata backed by a file on disk
- L71-139 _private* method_ `static async Task<FileMetadataDb> CreateAsync(string connectionString, CancellationToken cancellationToken)`
- L146-150 _public method_ `public async Task<int> AddFileAsync(int directoryId, string name, DateTime time, long length)` — Adds a single file to the database
- L155-158 _public method_ `public async Task AddFilesAsync(IEnumerable<FileRow> files)` — Adds a set of files to the database
- L163-166 _public method_ `public Task<FileRow> GetFileAsync(int fileId)` — Finds all the files in a particular directory
- L171-174 _public method_ `public Task<IEnumerable<FileRow>> FindFilesInDirectoryAsync(int directoryId)` — Finds all the files in a particular directory
- L179-182 _public method_ `public Task<IEnumerable<FileRow>> FindFilesInDirectoriesAsync(IEnumerable<int> directoryIds)` — Finds all the files in a particular directory
- L187-192 _public method_ `public async Task<string> GetFilePathAsync(int id)` — Gets the full name of a file
- L197-202 _public method_ `public async Task GetFilePathAsync(int id, StringBuilder builder)` — Gets the full name of a directory
- L207-210 _public method_ `public async Task RemoveFileAsync(int fileId)` — Removes a file and all its chunk metadata
- L219-223 _public method_ `public async Task<int> AddChunkAsync(int fileId, long offset, long length, IoHash hash)` — Adds a record for a new file chunk
- L228-231 _public method_ `public async Task AddChunksAsync(IEnumerable<ChunkRow> chunks)` — Adds multiple file chunk records
- L236-239 _public method_ `public async Task<ChunkRow> GetChunkAsync(int chunkId)` — Gets a chunk row
- L244-247 _public method_ `public async Task<IEnumerable<ChunkRow>> FindChunksAsync(IoHash hash, long length)` — Find all chunks with a particular hash and length
- L252-255 _public method_ `public async Task<IEnumerable<ChunkRow>> FindChunksForFileAsync(int fileId)` — Finds all the chunks within a particular file
- L260-263 _public method_ `public async Task RemoveChunksForFileAsync(int fileId)` — Remove all chunks for a particular file
- L268-271 _public method_ `public async Task RemoveChunksForFilesAsync(IEnumerable<int> fileIds)` — Remove all chunks for a set of files
- L280-284 _public method_ `public async Task<int> AddDirectoryAsync(int parentDirectoryId, string name)` — Adds a new directory to the collection
- L289-292 _public method_ `public async Task AddDirectoriesAsync(IEnumerable<DirectoryRow> dirs)` — Adds multiple directories to the collection
- L297-300 _public method_ `public async Task<DirectoryRow> GetDirectoryAsync(int id)` — Gets the definition for a particular directory
- L305-310 _public method_ `public async Task<string> GetDirectoryPathAsync(int id)` — Gets the full name of a directory
- L315-324 _public method_ `public async Task GetDirectoryPathAsync(int id, StringBuilder builder)` — Gets the full name of a directory
- L329-332 _public method_ `public async Task<IEnumerable<DirectoryRow>> GetDirectoriesAsync(int parentDirectoryId)` — Finds all directories within a given parent directory
- L337-341 _public method_ `public async Task RemoveDirectoryAsync(int directoryId)` — Removes a directory and all its subdirectories
- L346-350 _public method_ `public async Task RemoveDirectoriesAsync(IEnumerable<int> directoryIds)` — Removes a directory and all its subdirectories
- L355-358 _public method_ `public async Task RemoveDirectoryContentsAsync(int directoryId)` — Removes the contents of a directory, without removing the directory itself
- L363-380 _public method_ `public async Task RemoveDirectoryContentsAsync(IEnumerable<int> directoryIds)` — Removes all subdirectories and files starting at the given roots

#### class `EpicGames.Horde.Storage.FileMetadataDb.IoHashTypeMapper`  
`class IoHashTypeMapper : SqlMapper.TypeHandler<IoHash>`  
_private*; L26-38_
- inherits: `SqlMapper.TypeHandler<IoHash>`
- L28-31 _public method_ `public override IoHash Parse(object value)`
- L33-37 _public method_ `public override void SetValue(IDbDataParameter parameter, IoHash value)`

#### record `EpicGames.Horde.Storage.FileRow`  
`public record class FileRow(int Id, int DirectoryId, string Name, DateTime Time, long Length)`  
_public; L393-408_
- desc: Metadata for a file
- L398-400 _public ctor_ `public FileRow() : this(-1, -1, String.Empty, DateTime.MinValue, 0)` — Default constructor
- L405-407 _public ctor_ `public FileRow(int directoryId, string name, DateTime time, long length) : this(-1, directoryId, name, time, length)` — Constructor for new file rows

#### record `EpicGames.Horde.Storage.DirectoryRow`  
`public record class DirectoryRow(int Id, int ParentDirectoryId, string Name)`  
_public; L416-431_
- desc: Metadata for a directory
- L421-423 _public ctor_ `public DirectoryRow() : this(-1, -1, String.Empty)` — Default constructor
- L428-430 _public ctor_ `public DirectoryRow(int parentDirectoryId, string name) : this(-1, parentDirectoryId, name)` — Constructor for new directory rows

#### record `EpicGames.Horde.Storage.ChunkRow`  
`public record class ChunkRow(int Id, int FileId, long Offset, long Length, IoHash Hash)`  
_public; L441-456_
- desc: Metadata for a file chunk
- L446-448 _public ctor_ `public ChunkRow() : this(-1, -1, 0, 0, IoHash.Zero)` — Default constructor
- L453-455 _public ctor_ `public ChunkRow(int fileId, long offset, long length, IoHash hash) : this(-1, fileId, offset, length, hash)` — Constructor for new chunk rows

### `Source/Programs/Shared/EpicGames.Horde/Storage/Git/GitCommit.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Git.GitCommitProperty`  
`public static class GitCommitProperty`  
_public; L14-35_
- desc: Property names for git commits
- L19 _public property_ `public static Utf8String Tree { get; }` — The root of the tree for this commit
- L24 _public property_ `public static Utf8String Author { get; }` — Author of the commit
- L29 _public property_ `public static Utf8String Committer { get; }` — Person that committed the change
- L34 _public property_ `public static Utf8String Parent { get; }` — Parent commit

#### class `EpicGames.Horde.Storage.Git.GitCommit`  
`public class GitCommit`  
_public; L40-153_
- desc: Representation of a Git commit object
- L45 _public property_ `public List<KeyValuePair<Utf8String, Utf8String>> Properties { get; }` — Properties for the commit
- L50 _public property_ `public Utf8String Message { get; set; }` — Commit messages
- L57-61 _public ctor_ `public GitCommit(Sha1Hash tree, Utf8String message)` — Constructor
- L68-71 _public method_ `public void AddProperty(Utf8String name, Utf8String value)` — Adds a new property to the collection
- L78-88 _public method_ `public Utf8String GetProperty(Utf8String name)` — Gets a property value with the given key name
- L95-104 _public method_ `public IEnumerable<Utf8String> FindProperties(Utf8String name)` — Gets property values with the given key name
- L109 _public method_ `public Sha1Hash GetTree()` — The tree for this commit
- L114 _public method_ `public IEnumerable<Sha1Hash> GetParents()` — Parents of this commit
- L120-152 _public method_ `public byte[] Serialize()` — Serializes this object

### `Source/Programs/Shared/EpicGames.Horde/Storage/Git/GitObject.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Git.GitObjectType`  
`public static class GitObjectType`  
_public; L15-31_
- desc: Type fields for git objects
- L20 _public property_ `public static Utf8String Blob { get; }` — Blob objects
- L25 _public property_ `public static Utf8String Tree { get; }` — Tree objects
- L30 _public property_ `public static Utf8String Commit { get; }` — Commit objects

#### class `EpicGames.Horde.Storage.Git.GitObject`  
`public static class GitObject`  
_public; L36-94_
- desc: Utility methods for manipulating Git objects
- L46-51 _public method_ `public static async Task WriteHeaderAsync(Stream stream, Utf8String type, long size, CancellationToken cancellationToken = default)` — Writes the header for an object to a stream
- L59-63 _public method_ `public static void WriteHeader(Utf8String type, long size, IncrementalHash hash)` — Appends data for a header to the hash
- L72-93 _public method_ `public static Span<byte> WriteHeader(Utf8String type, long size, Span<byte> buffer)` — Writes a header for an object

### `Source/Programs/Shared/EpicGames.Horde/Storage/Git/GitTree.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Git.GitFileMode`  
`public static class GitFileMode`  
_public; L13-29_
- desc: Valid file modes for tree entries
- L18 _public property_ `public static Utf8String File { get; }` — Regular file
- L23 _public property_ `public static Utf8String ExecutableFile { get; }` — Executable file
- L28 _public property_ `public static Utf8String Tree { get; }` — Child tree

#### class `EpicGames.Horde.Storage.Git.GitTree`  
`public class GitTree`  
_public; L34-112_
- desc: Representation of a Git tree object
- L39 _public property_ `public List<GitTreeEntry> Entries { get; }` — Entries for this tree. Sort be sorted for consistency.
- L45-70 _public method_ `public Sha1Hash GetHash()` — Gets the hash of this tree object.
- L76-101 _public method_ `public byte[] Serialize()` — Serializes this object
- L103-111 _private* method_ `int GetPayloadSize()`

#### class `EpicGames.Horde.Storage.Git.GitTreeEntry`  
`public class GitTreeEntry`  
_public; L117-143_
- desc: Entry for a Git tree
- L122 _public property_ `public Utf8String Mode { get; }` — Mode for this entry. Can be any values from GitFileMode
- L127 _public property_ `public Utf8String Name { get; }` — Name of this entry
- L132 _public property_ `public Sha1Hash Hash { get; }` — Hash of the object for this entry
- L137-142 _public ctor_ `public GitTreeEntry(Utf8String mode, Utf8String name, Sha1Hash hash)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Storage/HttpStorageClient.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.HttpStorageClient`  
`public sealed class HttpStorageClient : IStorageClient`  
_public; L13-53_
- inherits: `IStorageClient`
- desc: Factory for constructing storage namespace instances with an HTTP backend
- L15 _private* field_ `readonly HttpStorageBackendFactory _backendFactory`
- L16 _private* field_ `readonly BundleCache _bundleCache`
- L17 _private* field_ `readonly IOptionsSnapshot<HordeOptions> _hordeOptions`
- L18 _private* field_ `readonly ILogger<BundleStorageNamespace> _clientLogger`
- L23-29 _public ctor_ `public HttpStorageClient(HttpStorageBackendFactory backendFactory, BundleCache bundleCache, IOptionsSnapshot<HordeOptions> hordeOptions, ILogger<BundleStorageNamespace> clientLogger)` — Constructor
- L37-41 _public method_ `public IStorageNamespace GetNamespaceWithPath(string basePath, string? accessToken = null, bool withBackendCache = true)` — Creates a new HTTP storage namespace
- L49 _public method_ `public IStorageNamespace GetNamespace(NamespaceId namespaceId, string? accessToken = null, bool withBackendCache = true)` — Creates a new HTTP storage namespace
- L52 _private* method_ `IStorageNamespace? IStorageClient.TryGetNamespace(NamespaceId namespaceId)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/IBlobReader.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IBlobReader`  
`public interface IBlobReader : IMemoryReader`  
_public; L14-40_
- inherits: `IMemoryReader`
- desc: Interface for reading nodes from storage
- L19 _public* property_ `BlobType Type { get; }` — Type to deserialize
- L24 _public* property_ `int Version { get; }` — Version of the current node, as specified via BlobType
- L29 _public* property_ `IReadOnlyList<IBlobRef> Imports { get; }` — Locations of all referenced nodes. These handles do not have valid hashes.
- L34 _public* method_ `IHashedBlobRef ReadBlobRef()` — Gets the next serialized blob handle
- L39 _public* method_ `IHashedBlobRef<T> ReadBlobRef<T>()` — Gets the next serialized blob handle

#### class `EpicGames.Horde.Storage.BlobReader`  
`public sealed class BlobReader : MemoryReader, IBlobReader`  
_public; L45-110_
- inherits: `MemoryReader, IBlobReader`
- desc: Reader for blob objects
- L50 _public property_ `public BlobType Type => ...` — Type to deserialize
- L55 _public property_ `public int Version => ...` — Version of the current node, as specified via BlobType
- L60 _public property_ `public int Length => ...` — Total length of the data in this node
- L65 _public property_ `public int RemainingLength => ...` — Amount of data remaining to be read
- L70 _public property_ `public ReadOnlyMemory<byte> Data => ...` — Raw data for this blob
- L75 _public property_ `public IReadOnlyList<IBlobRef> Imports => ...` — Locations of all referenced nodes.
- L77 _private* field_ `readonly BlobData _blobData`
- L78 _private* field_ `readonly BlobSerializerOptions _options`
- L79 _private* field_ `int _importIdx`
- L84-89 _public ctor_ `public BlobReader(BlobData blobData, BlobSerializerOptions? options) : base(blobData.Data)` — Constructor
- L94-99 _public method_ `public IHashedBlobRef ReadBlobRef()` — Gets the next serialized blob reference
- L104-109 _public method_ `public IHashedBlobRef<T> ReadBlobRef<T>()` — Gets the next serialized blob reference

### `Source/Programs/Shared/EpicGames.Horde/Storage/IBlobRef.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IBlobRef`  
`public interface IBlobRef`  
_public; L13-37_
- desc: Reference to another node in storage. This type is similar to IHashedBlobRef, but without a hash.
- L18 _public* property_ `IBlobRef Innermost { get; }` — Accessor for the innermost import
- L23 _public* method_ `ValueTask FlushAsync(CancellationToken cancellationToken = default)` — Flush the referenced data to underlying storage
- L29 _public* method_ `ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — Reads the blob's data
- L36 _public* method_ `bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)` — Attempt to get a path for this blob.

#### interface `EpicGames.Horde.Storage.IBlobRef`  
`public interface IBlobRef<out T> : IBlobRef`  
_public; L43-49_
- inherits: `IBlobRef`
- desc: Typed interface to a particular blob handle
- L48 _public* property_ `BlobSerializerOptions? SerializerOptions { get; }` — Options for deserializing the blob

#### class `EpicGames.Horde.Storage.BlobRefExtensions`  
`public static class BlobRefExtensions`  
_public; L54-103_
- desc: Extension methods for IBlobRef
- L87 _public method_ `public static IBlobRef<T> ForType<T>(this IBlobRef blobRef, BlobSerializerOptions? serializerOptions = null)` — Create a typed blob reference
- L94-102 _public method_ `public static BlobLocator GetLocator(this IBlobRef import)` — Gets a path to this blob that can be used to describe blob references over the wire.

#### class `EpicGames.Horde.Storage.BlobRefExtensions.TypedBlobRef`  
`class TypedBlobRef<T> : IBlobRef<T>`  
_private*; L56-79_
- inherits: `IBlobRef<T>`
- L58 _private* field_ `readonly IBlobRef _inner`
- L61 _public property_ `public BlobSerializerOptions? SerializerOptions { get; }` — (inheritdoc)
- L63 _public property_ `public IBlobRef Innermost => ...`
- L65-69 _public ctor_ `public TypedBlobRef(IBlobRef inner, BlobSerializerOptions? serializerOptions)`
- L71 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L74 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)`
- L77 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/IBlobWriter.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IBlobWriter`  
`public interface IBlobWriter : IMemoryWriter, IAsyncDisposable`  
_public; L17-77_
- inherits: `IMemoryWriter, IAsyncDisposable`
- desc: Interface for a writer of node objects
- L22 _public* property_ `BlobSerializerOptions Options { get; }` — Options for serialization
- L27 _public* property_ `ReadOnlyMemory<byte> WrittenMemory { get; }` — Accessor for the memory written to the current blob
- L35 _public* method_ `void AddAlias(string name, int rank, ReadOnlyMemory<byte> data = default)` — Adds an alias to the blob currently being written
- L41 _public* method_ `Task FlushAsync(CancellationToken cancellationToken = default)` — Flush any pending nodes to storage
- L47 _public* method_ `IBlobWriter Fork()` — Create another writer instance, allowing multiple threads to write in parallel.
- L55 _public* method_ `ValueTask<IHashedBlobRef> CompleteAsync(BlobType type, CancellationToken cancellationToken = default)` — Finish writing a blob that has been written into the output buffer.
- L63 _public* method_ `ValueTask<IHashedBlobRef<T>> CompleteAsync<T>(BlobType type, CancellationToken cancellationToken = default)` — Finish writing a blob that has been written into the output buffer.
- L70 _public* method_ `void WriteBlobHandleDangerous(IBlobRef handle)` — Writes a reference to another blob. NOTE: This does not write anything to the underlying output stream, which prevents the data forming a Merkle tree unless guaranteed uniqueness via a hash being written separately.
- L76 _public* method_ `void WriteBlobRef(IHashedBlobRef blobRef)` — Writes a reference to another blob. The blob's hash is serialized to the output stream.

#### record `EpicGames.Horde.Storage.AliasInfo`  
`public record class AliasInfo(string Name, int Rank, ReadOnlyMemory<byte> Data)`  
_public; L85-85_
- desc: Information about an alias to be added alongside a blob

#### class `EpicGames.Horde.Storage.BlobWriter`  
`public abstract class BlobWriter : IBlobWriter`  
_public; L90-206_
- inherits: `IBlobWriter`
- desc: Base class for IBlobWriter implementations.
- L92 _private* field_ `Memory<byte> _memory`
- L93 _private* field_ `readonly List<AliasInfo> _aliases = []`
- L94 _private* field_ `readonly List<IBlobRef> _imports = []`
- L95 _private* field_ `readonly BlobSerializerOptions _options`
- L96 _private* field_ `int _length`
- L99 _public property_ `public int Length => ...` — (inheritdoc)
- L102 _public property_ `public BlobSerializerOptions Options => ...` — (inheritdoc)
- L105 _public property_ `public ReadOnlyMemory<byte> WrittenMemory => ...` — (inheritdoc)
- L111-114 _protected ctor_ `protected BlobWriter(BlobSerializerOptions? options)` — Constructor
- L119 _public method_ `public IoHash ComputeHash()` — Computes the hash of the written data
- L122-125 _public method_ `public void WriteBlobHandleDangerous(IBlobRef target)` — (inheritdoc)
- L130-134 _public method_ `public void WriteBlobRef(IHashedBlobRef target)` — Writes a handle to another node
- L137 _public method_ `public Span<byte> GetSpan(int sizeHint = 0)` — (inheritdoc)
- L140-149 _public method_ `public Memory<byte> GetMemory(int sizeHint = 0)` — (inheritdoc)
- L152 _public method_ `public void Advance(int length)` — (inheritdoc)
- L160 _public method_ `public abstract Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — Request a new buffer to write to
- L171 _public method_ `public abstract ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken)` — Write the current blob to storage
- L174 _public method_ `public void AddAlias(string name, int rank, ReadOnlyMemory<byte> data)` — (inheritdoc)
- L178 _public method_ `public abstract Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L181 _public method_ `public abstract IBlobWriter Fork()` — (inheritdoc)
- L184-194 _public method_ `public async ValueTask<IHashedBlobRef> CompleteAsync(BlobType type, CancellationToken cancellationToken = default)` — (inheritdoc)
- L197-202 _public method_ `public async ValueTask<IHashedBlobRef<T>> CompleteAsync<T>(BlobType type, CancellationToken cancellationToken = default)` — (inheritdoc)
- L205 _public method_ `public abstract ValueTask DisposeAsync()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.NullBlobWriter`  
`public sealed class NullBlobWriter : BlobWriter`  
_public; L211-277_
- inherits: `BlobWriter`
- desc: Implementation of IBlobWriter which discards any written data
- L236 _private* field_ `readonly ChunkedMemoryWriter _memoryWriter`
- L237 _private* field_ `readonly BlobSerializerOptions _options`
- L242-247 _public ctor_ `public NullBlobWriter(BlobSerializerOptions options) : base(options)` — Constructor
- L250-255 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L258-264 _public method_ `public override ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken)` — (inheritdoc)
- L267 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — (inheritdoc)
- L271 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L275 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.NullBlobWriter.BlobRef`  
`class BlobRef : IHashedBlobRef`  
_private*; L213-234_
- inherits: `IHashedBlobRef`
- L215 _public property_ `public IoHash Hash { get; }`
- L217 _public property_ `public IBlobRef Innermost => ...`
- L220 _public ctor_ `public BlobRef(IoHash hash)`
- L223 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L226 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)`
- L229-233 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)`

#### class `EpicGames.Horde.Storage.MemoryBlobWriter`  
`public class MemoryBlobWriter : BlobWriter`  
_public; L282-367_
- inherits: `BlobWriter`
- desc: Implementation of IBlobWriter which just buffers data in memory
- L316 _private* field_ `readonly ChunkedMemoryWriter _memoryWriter`
- L317 _private* field_ `int _nextIndex`
- L322-326 _public ctor_ `public MemoryBlobWriter(BlobSerializerOptions options) : base(options)` — Constructor
- L329-334 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L339 _public method_ `public void Clear()` — Clears the contents of this writer
- L343 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L347 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)
- L351 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — (inheritdoc)
- L355-360 _public method_ `public override ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken)` — (inheritdoc)
- L365 _public method_ `public static int GetIndex(IHashedBlobRef handle)` — Helper function to get the index of a blob

#### class `EpicGames.Horde.Storage.MemoryBlobWriter.BlobRef`  
`class BlobRef : IHashedBlobRef`  
_private*; L284-314_
- inherits: `IHashedBlobRef`
- L286 _private* field_ `readonly int _index`
- L287 _private* field_ `readonly IoHash _hash`
- L288 _private* field_ `readonly BlobData _data`
- L290-295 _public ctor_ `public BlobRef(int index, BlobData data)`
- L297 _public property_ `public IoHash Hash => ...`
- L300 _public property_ `public int Index => ...`
- L303 _public property_ `public IBlobRef Innermost => ...`
- L306 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L309 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)`
- L312 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/IHashedBlobRef.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IHashedBlobRef`  
`public interface IHashedBlobRef : IBlobRef`  
_public; L13-19_
- inherits: `IBlobRef`
- desc: Handle to a node. Can be used to reference nodes that have not been flushed yet.
- L18 _public* property_ `IoHash Hash { get; }` — Hash of the target node

#### interface `EpicGames.Horde.Storage.IHashedBlobRef`  
`public interface IHashedBlobRef<out T> : IHashedBlobRef, IBlobRef<T>`  
_public; L25-27_
- inherits: `IHashedBlobRef, IBlobRef<T>`
- desc: Typed interface to a particular blob handle

#### record `EpicGames.Horde.Storage.HashedBlobRefValue`  
`public record class HashedBlobRefValue(IoHash Hash, BlobLocator Locator)`  
_public; L32-32_
- desc: Contains the value for a blob ref

#### class `EpicGames.Horde.Storage.HashedBlobRef`  
`public static class HashedBlobRef`  
_public; L37-105_
- desc: Helper methods for creating blob handles
- L82 _public method_ `public static IHashedBlobRef Create(IoHash hash, IBlobRef handle)` — Create an untyped blob handle
- L92 _public method_ `public static IHashedBlobRef<T> Create<T>(IHashedBlobRef blobRef, BlobSerializerOptions? options = null)` — Create a typed blob handle
- L103 _public method_ `public static IHashedBlobRef<T> Create<T>(IoHash hash, IBlobRef handle, BlobSerializerOptions? options = null)` — Create a typed blob handle

#### class `EpicGames.Horde.Storage.HashedBlobRef.HashedBlobRefImpl`  
`class HashedBlobRefImpl : IHashedBlobRef`  
_private*; L39-61_
- inherits: `IHashedBlobRef`
- L41 _private* field_ `readonly IoHash _hash`
- L42 _private* field_ `readonly IBlobRef _handle`
- L44 _public property_ `public IBlobRef Innermost => ...`
- L45 _public property_ `public IoHash Hash => ...`
- L47-51 _public ctor_ `public HashedBlobRefImpl(IoHash hash, IBlobRef handle)`
- L53 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L56 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)`
- L59 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)`

#### class `EpicGames.Horde.Storage.HashedBlobRef.HashedBlobRefImpl`  
`class HashedBlobRefImpl<T> : HashedBlobRefImpl, IHashedBlobRef<T>`  
_private*; L63-74_
- inherits: `HashedBlobRefImpl, IHashedBlobRef<T>`
- L65 _private* field_ `readonly BlobSerializerOptions _options`
- L67 _public property_ `public BlobSerializerOptions SerializerOptions => ...`
- L69-73 _public ctor_ `public HashedBlobRefImpl(IoHash hash, IBlobRef handle, BlobSerializerOptions options) : base(hash, handle)`

#### class `EpicGames.Horde.Storage.HashedBlobRefExtensions`  
`public static class HashedBlobRefExtensions`  
_public; L110-119_
- desc: Extension methods for IHashedBlobRef
- L115-118 _public method_ `public static HashedBlobRefValue GetRefValue(this IHashedBlobRef blobRef)` — Gets a BlobRefValue from an IBlobRef

### `Source/Programs/Shared/EpicGames.Horde/Storage/IObjectStore.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IObjectStore`  
`public interface IObjectStore`  
_public; L14-94_
- desc: Interface for a object storage service.
- L19 _public* property_ `bool SupportsRedirects { get; }` — Whether this storage backend supports HTTP redirects for reads and writes
- L29 _public* method_ `Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — Attempts to open a read stream for the given path.
- L39 _public* method_ `Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — Reads an object into memory and returns a handle to it.
- L48 _public* method_ `Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — Writes a stream to the storage backend. If the stream throws an exception during read, the write will be aborted.
- L56 _public* method_ `Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken = default)` — Tests whether the given path exists
- L64 _public* method_ `Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken = default)` — Gets the size of a particular object
- L72 _public* method_ `Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken = default)` — Deletes a file with the given path
- L80 _public* method_ `ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — Gets a HTTP redirect for a read request
- L88 _public* method_ `ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — Gets a HTTP redirect for a write request
- L93 _public* method_ `void GetStats(StorageStats stats)` — Gets stats for this storage backend

#### interface `EpicGames.Horde.Storage.IObjectStore`  
`public interface IObjectStore<T> : IObjectStore`  
_public; L99-101_
- inherits: `IObjectStore`
- desc: Typed IObjectStore instance for dependency injection

#### class `EpicGames.Horde.Storage.ObjectStoreExtensions`  
`public static class ObjectStoreExtensions`  
_public; L106-167_
- desc: Extension methods for IObjectStore
- L131 _public method_ `public static IObjectStore<T> ForType<T>(this IObjectStore store)` — Creates a typed wrapper around the given object store
- L141 _public method_ `public static Task<Stream> OpenAsync(this IObjectStore store, ObjectKey key, CancellationToken cancellationToken = default)` — Attempts to open a read stream for the given path.
- L151 _public method_ `public static Task<IReadOnlyMemoryOwner<byte>> ReadAsync(this IObjectStore store, ObjectKey key, CancellationToken cancellationToken = default)` — Reads an object into memory and returns a handle to it.
- L162-166 _public method_ `public static async Task WriteAsync(this IObjectStore store, ObjectKey locator, ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — Writes a stream to the storage backend. If the stream throws an exception during read, the write will be aborted.

#### class `EpicGames.Horde.Storage.ObjectStoreExtensions.TypedObjectStore`  
`sealed class TypedObjectStore<T> : IObjectStore<T>`  
_private*; L108-125_
- inherits: `IObjectStore<T>`
- L110 _private* field_ `readonly IObjectStore _inner`
- L112 _public property_ `public bool SupportsRedirects => ...`
- L114 _public ctor_ `public TypedObjectStore(IObjectStore inner)`
- L116 _public method_ `public Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)`
- L117 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)`
- L118 _public method_ `public Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken)`
- L119 _public method_ `public Task DeleteAsync(ObjectKey path, CancellationToken cancellationToken)`
- L120 _public method_ `public Task<bool> ExistsAsync(ObjectKey path, CancellationToken cancellationToken)`
- L121 _public method_ `public Task<long> GetSizeAsync(ObjectKey path, CancellationToken cancellationToken)`
- L122 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey path, CancellationToken cancellationToken = default)`
- L123 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey path, CancellationToken cancellationToken = default)`
- L124 _public method_ `public void GetStats(StorageStats stats)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/IStorageBackend.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IStorageBackend`  
`public interface IStorageBackend`  
_public; L18-133_
- desc: Interface for a low-level storage backend.
- L25 _public* property_ `bool SupportsRedirects { get; }` — Whether this storage backend supports HTTP redirects for reads and writes
- L35 _public* method_ `Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — Attempts to open a read stream for the given path.
- L45 _public* method_ `Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)` — Reads an object into memory and returns a handle to it.
- L55 _public* method_ `Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)` — Writes a stream to the storage backend. If the stream throws an exception during read, the write will be aborted.
- L65 _public* method_ `Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — Writes a stream to the storage backend. If the stream throws an exception during read, the write will be aborted.
- L73 _public* method_ `ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — Gets a HTTP redirect for a read request
- L82 _public* method_ `ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)` — Gets a HTTP redirect for a write request
- L91 _public* method_ `ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)` — Gets a HTTP redirect for a write request
- L104 _public* method_ `Task<BlobAliasLocator[]> FindAliasesAsync(string name, int? maxResults = null, CancellationToken cancellationToken = default)` — Finds blobs with the given alias. Unlike refs, aliases do not serve as GC roots.
- L117 _public* method_ `Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Reads data for a ref from the store
- L127 _public* method_ `Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)` — Batch request to update metadata
- L132 _public* method_ `void GetStats(StorageStats stats)` — Gets stats for this storage backend

#### class `EpicGames.Horde.Storage.StorageHelpers`  
`public static class StorageHelpers`  
_public; L138-166_
- desc: Utility methods for storage backend implementations
- L143 _private* field_ `static readonly string s_sessionPrefix = $"{Guid.NewGuid():n}_"` — Unique session id used for unique ids
- L148 _private* field_ `static int s_increment` — Incremented value used for each supplied id
- L155-165 _public method_ `public static BlobLocator CreateUniqueLocator(string? prefix)` — Creates a unique name with a given prefix

#### class `EpicGames.Horde.Storage.StorageBackendExtensions`  
`public static class StorageBackendExtensions`  
_public; L171-219_
- desc: Extension methods for IStorageBackend
- L180 _public method_ `public static Task<Stream> OpenBlobAsync(this IStorageBackend storageBackend, BlobLocator locator, CancellationToken cancellationToken = default)` — Attempts to open a read stream for the given path.
- L189 _public method_ `public static Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(this IStorageBackend storageBackend, BlobLocator locator, CancellationToken cancellationToken = default)` — Attempts to open a read stream for the given path.
- L198-202 _public method_ `public static async Task<byte[]> ReadBytesAsync(this IStorageBackend storageBackend, BlobLocator locator, CancellationToken cancellationToken = default)` — Reads an object as an array of bytes
- L212-218 _public method_ `public static async Task<BlobLocator> WriteBytesAsync(this IStorageBackend storageBackend, ReadOnlyMemory<byte> data, IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)` — Writes a block of memory to storage

### `Source/Programs/Shared/EpicGames.Horde/Storage/IStorageClient.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IStorageClient`  
`public interface IStorageClient`  
_public; L10-18_
- desc: Client for the storage system
- L17 _public* method_ `IStorageNamespace? TryGetNamespace(NamespaceId namespaceId)` — Creates a storage namespace for the given id

#### class `EpicGames.Horde.Storage.StorageClientExtensions`  
`public static class StorageClientExtensions`  
_public; L23-37_
- desc: Extension methods for IStorageClient
- L28-36 _public method_ `public static IStorageNamespace GetNamespace(this IStorageClient storageClient, NamespaceId namespaceId)` — Creates a new storage namespace, throwing an exception if it does not exist

### `Source/Programs/Shared/EpicGames.Horde/Storage/IStorageNamespace.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Storage.RefOptions`  
`public record class RefOptions(TimeSpan? Lifetime = null, bool? Extend = null)`  
_public; L19-19_
- desc: Options for a new ref

#### interface `EpicGames.Horde.Storage.IStorageNamespace`  
`public interface IStorageNamespace`  
_public; L24-83_
- desc: Interface for the storage system.
- L31 _public* method_ `IStorageWriter CreateWriter(CancellationToken cancellationToken = default)` — Creates a writer for updating the namespace
- L40 _public* method_ `IBlobRef CreateBlobRef(BlobLocator locator)` — Creates a new blob handle by parsing a locator
- L49 _public* method_ `IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null, CancellationToken cancellationToken = default)` — Creates a new writer for storage blobs
- L62 _public* method_ `Task<BlobAlias[]> FindAliasesAsync(string name, int? maxResults = null, CancellationToken cancellationToken = default)` — Finds blobs with the given alias. Unlike refs, aliases do not serve as GC roots.
- L75 _public* method_ `Task<IHashedBlobRef?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Reads data for a ref from the store
- L82 _public* method_ `void GetStats(StorageStats stats)` — Gets a snapshot of the stats for the storage namespace.

#### record struct `EpicGames.Horde.Storage.RefCacheTime`  
`public readonly record struct RefCacheTime(DateTime Utc)`  
_public; L89-123_
- desc: Indicates the maximum age of a entry returned from a cache in the hierarchy
- L94 _public property_ `public readonly TimeSpan MaxAge => ...` — Maximum age for a cached value to be returned
- L100 _public ctor_ `public RefCacheTime(TimeSpan age) : this(DateTime.UtcNow - age)` — Sets the earliest time at which the entry must have been valid
- L105 _public method_ `public readonly bool IsSet()` — Tests whether this value is set
- L112 _public method_ `public static bool IsStaleCacheEntry(DateTime entryTime, RefCacheTime cacheTime)` — Determines if this cache time deems a particular cache entry stale
- L117 _public operator_ `public static implicit operator RefCacheTime(DateTime time)` — Implicit conversion operator from datetime values.
- L122 _public operator_ `public static implicit operator RefCacheTime(TimeSpan age)` — Implicit conversion operator from timespan values.

#### class `EpicGames.Horde.Storage.StorageStats`  
`public class StorageStats`  
_public; L128-167_
- desc: Stats for the storage system
- L133 _public property_ `public List<(string, long)> Values { get; }` — Stat name to value
- L138 _public method_ `public void Add(string name, long value)` — Add a new stat to the list
- L143-149 _public method_ `public void Print(ILogger logger)` — Prints the table of stats to the logger
- L154-166 _public method_ `public static StorageStats GetDelta(StorageStats initial, StorageStats finish)` — Subtract a base set of stats from this one

#### class `EpicGames.Horde.Storage.StorageNamespaceExtensions`  
`public static class StorageNamespaceExtensions`  
_public; L172-404_
- desc: Extension methods for IStorageNamespace
- L183 _public method_ `public static IBlobRef<T> CreateBlobRef<T>(this IStorageNamespace storageNamespace, BlobLocator locator, BlobSerializerOptions? serializerOptions = null)` — Creates a new blob handle by parsing a locator
- L193 _public method_ `public static IHashedBlobRef CreateBlobRef(this IStorageNamespace storageNamespace, IoHash hash, BlobLocator locator)` — Creates a new blob reference from a locator and hash
- L204 _public method_ `public static IHashedBlobRef<T> CreateBlobRef<T>(this IStorageNamespace storageNamespace, IoHash hash, BlobLocator locator, BlobSerializerOptions? serializerOptions = null)` — Creates a new blob reference from a locator and hash
- L210 _public method_ `public static IHashedBlobRef CreateBlobRef(this IStorageNamespace storageNamespace, HashedBlobRefValue refValue)` — Create a blob ref from a RefValue
- L216 _public method_ `public static IHashedBlobRef<T> CreateBlobRef<T>(this IStorageNamespace storageNamespace, HashedBlobRefValue refValue, BlobSerializerOptions? options)` — Create a typed blob ref from a RefValue
- L257 _public method_ `public static IBlobRef CreateBlobRef(this IStorageNamespace storageNamespace, RefName name, RefCacheTime cacheTime = default)` — Creates a new blob ref from a ref name
- L268 _public method_ `public static IBlobRef<T> CreateBlobRef<T>(this IStorageNamespace storageNamespace, RefName name, RefCacheTime cacheTime = default, BlobSerializerOptions? serializerOptions = null)` — Creates a new blob ref from a ref name
- L276 _public method_ `public static IBlobWriter CreateBlobWriter(this IStorageNamespace store, RefName refName)` — Creates a writer using a refname as a base path
- L292-296 _public method_ `public static async Task AddAliasAsync(this IStorageNamespace store, string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — Adds an alias to a given blob
- L305-309 _public method_ `public static async Task RemoveAliasAsync(this IStorageNamespace store, string name, IBlobRef handle, CancellationToken cancellationToken = default)` — Removes an alias from a blob
- L318-322 _public method_ `public static async Task<BlobAlias?> FindAliasAsync(this IStorageNamespace store, string name, CancellationToken cancellationToken = default)` — Finds blobs with the given alias. Unlike refs, aliases do not serve as GC roots.
- L336-340 _public method_ `public static async Task<bool> RefExistsAsync(this IStorageNamespace store, RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Checks if the given ref exists
- L350-354 _public method_ `public static async Task<IHashedBlobRef> ReadRefAsync(this IStorageNamespace store, RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — Reads a ref from the store, throwing an exception if it does not exist
- L365-369 _public method_ `public static async Task AddRefAsync(this IStorageNamespace store, RefName name, IHashedBlobRef target, RefOptions? options = null, CancellationToken cancellationToken = default)` — Writes a new ref to the store
- L377-381 _public method_ `public static async Task RemoveRefAsync(this IStorageNamespace store, RefName name, CancellationToken cancellationToken = default)` — Reads data for a ref from the store
- L385 _public method_ `public static Task WriteRefAsync(this IStorageNamespace store, RefName name, IHashedBlobRef target, RefOptions? options = null, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Use AddRefAsync() instead")]` — (inheritdoc)
- L390 _public method_ `public static Task DeleteRefAsync(this IStorageNamespace store, RefName name, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Use RemoveRefAsync() instead")]` — (inheritdoc)
- L398-403 _public method_ `public static StorageStats GetStats(this IStorageNamespace store)` — Gets a snapshot of the stats for the storage namespace.

#### class `EpicGames.Horde.Storage.StorageNamespaceExtensions.NamedBlobRef`  
`class NamedBlobRef : IBlobRef`  
_private*; L219-248_
- inherits: `IBlobRef`
- L221 _private* field_ `readonly IStorageNamespace _storageNamespace`
- L222 _private* field_ `readonly RefName _name`
- L223 _private* field_ `readonly RefCacheTime _cacheTime`
- L225-230 _public ctor_ `public NamedBlobRef(IStorageNamespace storageNamespace, RefName name, RefCacheTime cacheTime = default)`
- L232 _public property_ `public IBlobRef Innermost => ...`
- L234 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)`
- L237-241 _public method_ `public async ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)`
- L243-247 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/IStorageWriter.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.IStorageWriter`  
`public interface IStorageWriter : IAsyncDisposable`  
_public; L12-74_
- inherits: `IAsyncDisposable`
- desc: Interface for a batching storage writer
- L22 _public* method_ `IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null)` — Creates a new writer for storage blobs
- L36 _public* method_ `Task AddAliasAsync(string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — Adds an alias to a given blob
- L44 _public* method_ `Task RemoveAliasAsync(string name, IBlobRef handle, CancellationToken cancellationToken = default)` — Removes an alias from a blob
- L58 _public* method_ `Task AddRefAsync(RefName name, IHashedBlobRef target, RefOptions? options = null, CancellationToken cancellationToken = default)` — Adds a new ref to the store
- L65 _public* method_ `Task RemoveRefAsync(RefName name, CancellationToken cancellationToken = default)` — Removes a ref from the store
- L73 _public* method_ `Task FlushAsync(CancellationToken cancellationToken = default)` — Flush any buffered writes

#### class `EpicGames.Horde.Storage.StorageWriter`  
`public abstract class StorageWriter : IStorageWriter`  
_public; L79-166_
- inherits: `IStorageWriter`
- desc: Default base implementation of IStorageWriter which combines metadata updates into a UpdateMetadataRequest
- L81 _private* field_ `readonly IStorageBackend _storageBackend`
- L82 _private* field_ `readonly CancellationToken _cancellationToken`
- L83 _private* field_ `UpdateMetadataRequest _request = new()`
- L88-92 _protected ctor_ `protected StorageWriter(IStorageBackend storageBackend, CancellationToken cancellationToken = default)` — Constructor
- L95-99 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L102 _public method_ `public IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null)` — (inheritdoc)
- L106 _protected method_ `protected abstract IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L111-116 _public method_ `public async Task AddAliasAsync(string name, IBlobRef handle, int rank = 0, ReadOnlyMemory<byte> data = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L119-124 _public method_ `public async Task RemoveAliasAsync(string name, IBlobRef handle, CancellationToken cancellationToken = default)` — (inheritdoc)
- L131-137 _public method_ `public async Task AddRefAsync(RefName name, IHashedBlobRef target, RefOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L140-144 _public method_ `public async Task RemoveRefAsync(RefName name, CancellationToken cancellationToken = default)` — (inheritdoc)
- L148-155 _private* method_ `async Task CheckForFlushAsync(CancellationToken cancellationToken = default)`
- L158-165 _public method_ `public async Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/KeyValueStorageNamespace.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Clients.KeyValueStorageNamespace`  
`public sealed class KeyValueStorageNamespace : IStorageNamespace`  
_public; L17-218_
- inherits: `IStorageNamespace`
- desc: Base class for storage namespaces that wrap a diirect key/value type store without any merging/splitting.
- L133 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L135 _private* field_ `readonly IStorageBackend _backend`
- L140-143 _public ctor_ `public KeyValueStorageNamespace(IStorageBackend backend)` — Constructor
- L148 _public method_ `public static KeyValueStorageNamespace CreateInMemory()` — Create an in-memory storage namespace
- L151 _public method_ `public IStorageWriter CreateWriter(CancellationToken cancellationToken)` — (inheritdoc)
- L157 _public method_ `public IBlobRef CreateBlobRef(BlobLocator locator)` — (inheritdoc)
- L161 _public method_ `public IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L165-171 _public method_ `public async ValueTask<BlobData> ReadBlobAsync(BlobLocator locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L174-185 _public method_ `public async ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, Stream stream, IReadOnlyList<IBlobRef> imports, string? basePath = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L192-196 _public method_ `public async Task<BlobAlias[]> FindAliasesAsync(string name, int? maxResults = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L203-211 _public method_ `public async Task<IHashedBlobRef?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)` — (inheritdoc)
- L216 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Clients.KeyValueStorageNamespace.Handle`  
`class Handle : IBlobRef`  
_private*; L19-54_
- inherits: `IBlobRef`
- L21 _private* field_ `readonly KeyValueStorageNamespace _keyValueStorageNamespace`
- L22 _private* field_ `readonly BlobLocator _locator`
- L25 _public property_ `public IBlobRef Innermost => ...` — (inheritdoc)
- L30-34 _public ctor_ `public Handle(KeyValueStorageNamespace keyValueStorageNamespace, BlobLocator locator)` — Constructor
- L37 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L40 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L43-47 _public method_ `public bool TryGetLocator(out BlobLocator locator)` — (inheritdoc)
- L50 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L53 _public method_ `public override int GetHashCode()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Clients.KeyValueStorageNamespace.StorageWriterImpl`  
`class StorageWriterImpl : StorageWriter`  
_private*; L56-69_
- inherits: `StorageWriter`
- L58 _private* field_ `readonly KeyValueStorageNamespace _keyValueStorageNamespace`
- L60-64 _public ctor_ `public StorageWriterImpl(KeyValueStorageNamespace keyValueStorageNamespace, IStorageBackend storageBackend, CancellationToken cancellationToken) : base(storageBackend, cancellationToken)`
- L67 _protected method_ `protected override IBlobWriter CreateBlobWriter(string? basePath = null, BlobSerializerOptions? serializerOptions = null, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Clients.KeyValueStorageNamespace.BlobWriterImpl`  
`class BlobWriterImpl : BlobWriter`  
_private*; L71-130_
- inherits: `BlobWriter`
- L73 _private* field_ `readonly KeyValueStorageNamespace _outer`
- L74 _private* field_ `readonly string _basePath`
- L75 _private* field_ `byte[] _data = []`
- L76 _private* field_ `int _offset`
- L81-91 _public ctor_ `public BlobWriterImpl(KeyValueStorageNamespace outer, string? basePath, BlobSerializerOptions? options) : base(options)` — Constructor
- L94 _public method_ `public override ValueTask DisposeAsync()` — (inheritdoc)
- L97 _public method_ `public override Task FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L100 _public method_ `public override IBlobWriter Fork()` — (inheritdoc)
- L103-113 _public method_ `public override Memory<byte> GetOutputBuffer(int usedSize, int desiredSize)` — (inheritdoc)
- L116-129 _public method_ `public override async ValueTask<IHashedBlobRef> WriteBlobAsync(BlobType type, int size, IReadOnlyList<IBlobRef> imports, IReadOnlyList<AliasInfo> aliases, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/NamespaceId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Storage.NamespaceId`  
`public readonly struct NamespaceId : IEquatable<NamespaceId>`  
_public; L19-61_
- attrs: `[LogValueType] [JsonSchemaString] [JsonConverter(typeof(NamespaceIdJsonConverter))] [TypeConverter(typeof(NamespaceIdTypeConverter))]`
- inherits: `IEquatable<NamespaceId>`
- desc: Identifier for a storage namespace
- L24 _public property_ `public StringId Text { get; }` — The text representing this id
- L30-33 _public ctor_ `public NamespaceId(string text) : this(new Utf8String(text))` — Constructor
- L39-42 _public ctor_ `public NamespaceId(Utf8String text)` — Constructor
- L45 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L48 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L51 _public method_ `public bool Equals(NamespaceId other)` — (inheritdoc)
- L54 _public method_ `public override string ToString()` — (inheritdoc)
- L57 _public operator_ `public static bool operator ==(NamespaceId left, NamespaceId right)` — (inheritdoc)
- L60 _public operator_ `public static bool operator !=(NamespaceId left, NamespaceId right)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.NamespaceIdJsonConverter`  
`sealed class NamespaceIdJsonConverter : JsonConverter<NamespaceId>`  
_internal*; L66-73_
- inherits: `JsonConverter<NamespaceId>`
- desc: Type converter for NamespaceId to and from JSON
- L69 _public method_ `public override NamespaceId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L72 _public method_ `public override void Write(Utf8JsonWriter writer, NamespaceId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.NamespaceIdTypeConverter`  
`sealed class NamespaceIdTypeConverter : TypeConverter`  
_internal*; L78-85_
- inherits: `TypeConverter`
- desc: Type converter from strings to NamespaceId objects
- L81 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L84 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/CbNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.CbNode`  
`public class CbNode`  
_public; L14-41_
- attrs: `[BlobConverter(typeof(CbNodeConverter))]`
- desc: A node containing arbitrary compact binary data
- L19 _public property_ `public static Guid BlobTypeGuid { get; }` — Static accessor for the blob type guid
- L24 _public property_ `public CbObject Object { get; set; }` — The compact binary object
- L29 _public property_ `public IReadOnlyList<IBlobRef> Imports { get; }` — Imported nodes
- L36-40 _public ctor_ `public CbNode(CbObject obj, IReadOnlyList<IBlobRef> imports)` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.CbNodeConverter`  
`class CbNodeConverter : BlobConverter<CbNode>`  
_internal*; L43-60_
- inherits: `BlobConverter<CbNode>`
- L45 _public property_ `public static BlobType BlobType { get; }`
- L48-52 _public method_ `public override CbNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L55-59 _public method_ `public override BlobType Write(IBlobWriter writer, CbNode value, BlobSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/ChunkedDataNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.ChunkedDataNode`  
`public abstract class ChunkedDataNode`  
_public; L24-33_
- attrs: `[BlobConverter(typeof(ChunkedDataNodeConverter))]`
- desc: Representation of a data stream, split into chunks along content-aware boundaries using a rolling hash (BuzHash). Chunks are pushed into a tree hierarchy as data is appended to the root, with nodes of the tree also split along content-aware boundaries with IoHash.NumBytes granularity. Once a chunk has been written to storage, it is treated as immutable.
- L32 _public method_ `public abstract Task CopyToStreamAsync(Stream outputStream, BlobSerializerOptions? options = null, CancellationToken cancellationToken = default)` — Copies the contents of this node and its children to the given output stream

#### class `EpicGames.Horde.Storage.Nodes.ChunkedDataNodeExtensions`  
`public static class ChunkedDataNodeExtensions`  
_public; L38-100_
- desc: Extension methods for chunked data node types
- L45 _public method_ `public static Stream OpenAsStream(this IBlobRef<ChunkedDataNode> handle, long? length = null)` — Copy the contents of the node to the output stream without creating the intermediate FileNodes
- L54-69 _public method_ `public static async Task CopyToStreamAsync(this IBlobRef<ChunkedDataNode> handle, Stream outputStream, CancellationToken cancellationToken = default)` — Copy the contents of the node to the output stream without creating the intermediate FileNodes
- L78-88 _public method_ `public static async Task CopyToFileAsync(this IBlobRef<ChunkedDataNode> handle, FileInfo file, CancellationToken cancellationToken)` — Extracts the contents of this node to a file
- L95-99 _public method_ `public static async Task<byte[]> ReadAllBytesAsync(this IBlobRef<ChunkedDataNode> handle, CancellationToken cancellationToken = default)` — Copy the contents of the node to the output stream without creating the intermediate FileNodes

#### class `EpicGames.Horde.Storage.Nodes.ChunkedDataNodeConverter`  
`class ChunkedDataNodeConverter : BlobConverter<ChunkedDataNode>`  
_internal*; L102-137_
- inherits: `BlobConverter<ChunkedDataNode>`
- L105-119 _public method_ `public override ChunkedDataNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L122-136 _public method_ `public override BlobType Write(IBlobWriter writer, ChunkedDataNode value, BlobSerializerOptions options)` — (inheritdoc)

#### enum `EpicGames.Horde.Storage.Nodes.ChunkedDataNodeType`  
`public enum ChunkedDataNodeType`  
_public; L142-158_
- desc: Type of a chunked data node
- L147 _public* enumerator_ `Unknown` — Unknown node type
- L152 _public* enumerator_ `Leaf` — Leaf node
- L157 _public* enumerator_ `Interior` — An interior node

#### record `EpicGames.Horde.Storage.Nodes.ChunkedDataNodeRef`  
`public record class ChunkedDataNodeRef(ChunkedDataNodeType Type, long Length, uint RollingHash, IHashedBlobRef<ChunkedDataNode> Inner) : IHashedBlobRef<ChunkedDataNode>`  
_public; L167-290_
- inherits: `IHashedBlobRef<ChunkedDataNode>`
- desc: Reference to a chunked data node
- L170 _public property_ `public IoHash Hash => ...` — (inheritdoc)
- L173 _public property_ `public BlobSerializerOptions? SerializerOptions => ...` — (inheritdoc)
- L176 _public property_ `public IBlobRef Innermost => ...` — (inheritdoc)
- L181-184 _public ctor_ `public ChunkedDataNodeRef(long length, uint rollingHash, IHashedBlobRef<LeafChunkedDataNode> handle) : this(ChunkedDataNodeType.Leaf, length, rollingHash, handle)` — Leaf node constructor
- L189-192 _public ctor_ `public ChunkedDataNodeRef(long length, IHashedBlobRef<InteriorChunkedDataNode> handle) : this(ChunkedDataNodeType.Interior, length, 0, handle)` — Interior node constructor
- L197-204 _public method_ `public IHashedBlobRef<InteriorChunkedDataNode> GetInteriorHandle()` — Gets the target interior node handle
- L209-216 _public method_ `public IHashedBlobRef<LeafChunkedDataNode> GetLeafHandle()` — Gets the target leaf node handle
- L221-235 _public method_ `public async ValueTask<ChunkedDataNode> ReadBlobAsync(BlobSerializerOptions? options = null, CancellationToken cancellationToken = default)` — Read the node which is the target of this ref
- L241-277 _public method_ `public async IAsyncEnumerable<LeafChunkedDataNodeRef> EnumerateLeafNodesAsync([EnumeratorCancellation] CancellationToken cancellationToken)` — Enumerates all the leaf nodes for this node
- L280 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L284 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L288 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)` — (inheritdoc)

#### record `EpicGames.Horde.Storage.Nodes.LeafChunkedDataNodeRef`  
`public record class LeafChunkedDataNodeRef(long Length, IHashedBlobRef<LeafChunkedDataNode> Inner) : IHashedBlobRef<LeafChunkedDataNode>`  
_public; L297-319_
- inherits: `IHashedBlobRef<LeafChunkedDataNode>`
- desc: Reference to a LeafChunkedDataNode
- L300 _public property_ `public BlobSerializerOptions? SerializerOptions => ...` — (inheritdoc)
- L303 _public property_ `public IBlobRef Innermost => ...` — (inheritdoc)
- L306 _public property_ `public IoHash Hash => ...` — (inheritdoc)
- L309 _public method_ `public ValueTask FlushAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L313 _public method_ `public ValueTask<BlobData> ReadBlobDataAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L317 _public method_ `public bool TryGetLocator([NotNullWhen(true)] out BlobLocator locator)` — (inheritdoc)

#### record `EpicGames.Horde.Storage.Nodes.LeafChunkedData`  
`public record class LeafChunkedData(IoHash Hash, List<ChunkedDataNodeRef> LeafHandles)`  
_public; L326-326_
- desc: Stores the flat list of chunks produced from chunking a single data stream

#### class `EpicGames.Horde.Storage.Nodes.LeafChunkedDataNode`  
`public sealed class LeafChunkedDataNode : ChunkedDataNode`  
_public; L332-509_
- attrs: `[BlobConverter(typeof(LeafChunkedDataNodeConverter))]`
- inherits: `ChunkedDataNode`
- desc: File node that contains a chunk of data
- L337 _public property_ `public static Guid BlobTypeGuid { get; }` — Guid for the blob type
- L342 _public property_ `public ReadOnlyMemory<byte> Data { get; }` — Data for this node
- L347-350 _public ctor_ `public LeafChunkedDataNode(ReadOnlyMemory<byte> data)` — Create an empty leaf node
- L353-356 _public method_ `public override async Task CopyToStreamAsync(Stream outputStream, BlobSerializerOptions? options, CancellationToken cancellationToken)` — (inheritdoc)
- L364-368 _public method_ `public static async Task CopyToStreamAsync(BlobData nodeData, Stream outputStream, CancellationToken cancellationToken)` — Copy the contents of the node to the output stream without creating the intermediate FileNodes
- L378-384 _public method_ `public static async Task<LeafChunkedData> CreateFromFileAsync(IBlobWriter writer, FileReference file, LeafChunkedDataNodeOptions options, CancellationToken cancellationToken)` — Creates nodes from the given file
- L394-400 _public method_ `public static async Task<LeafChunkedData> CreateFromFileAsync(IBlobWriter writer, FileInfo file, LeafChunkedDataNodeOptions options, CancellationToken cancellationToken)` — Creates nodes from the given file
- L410-413 _public method_ `public static Task<LeafChunkedData> CreateFromStreamAsync(IBlobWriter writer, Stream stream, LeafChunkedDataNodeOptions options, CancellationToken cancellationToken)` — Creates nodes from the given file
- L424-466 _internal method_ `internal static async Task<LeafChunkedData> CreateFromStreamAsync(IBlobWriter writer, Stream stream, LeafChunkedDataNodeOptions options, UpdateStats? updateStats, CancellationToken cancellationToken)` — Creates nodes from the given file
- L468-496 _internal method_ `internal static async Task<LeafChunkedData> CreateFromChunkerOutputAsync(IBlobWriter writer, ChunkerOutput output, UpdateStats? updateStats, CancellationToken cancellationToken)`
- L505-508 _public method_ `public static int GetChunkLength(ReadOnlySpan<byte> inputData, LeafChunkedDataNodeOptions options, out uint rollingHash)` — Determines how much data to append to an existing leaf node

#### class `EpicGames.Horde.Storage.Nodes.LeafChunkedDataNodeConverter`  
`class LeafChunkedDataNodeConverter : BlobConverter<LeafChunkedDataNode>`  
_internal*; L511-529_
- inherits: `BlobConverter<LeafChunkedDataNode>`
- L516 _public property_ `public static BlobType BlobType { get; }` — Static accessor for the blob type
- L518-522 _public method_ `public override LeafChunkedDataNode Read(IBlobReader reader, BlobSerializerOptions options)`
- L524-528 _public method_ `public override BlobType Write(IBlobWriter writer, LeafChunkedDataNode value, BlobSerializerOptions options)`

#### record `EpicGames.Horde.Storage.Nodes.InteriorChunkedDataNodeOptions`  
`public record class InteriorChunkedDataNodeOptions(int MinChildCount, int TargetChildCount, int MaxChildCount, uint SliceThreshold)`  
_public; L538-552_
- desc: Options for creating interior nodes
- L543 _public property_ `public static InteriorChunkedDataNodeOptions Default { get; }` — Default settings
- L548-551 _public ctor_ `public InteriorChunkedDataNodeOptions(int minChildCount, int targetChildCount, int maxChildCount) : this(minChildCount, targetChildCount, maxChildCount, (uint)((1UL << 32) / (uint)targetChildCount))` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.InteriorChunkedDataNode`  
`public class InteriorChunkedDataNode : ChunkedDataNode`  
_public; L558-722_
- attrs: `[BlobConverter(typeof(InteriorChunkedDataNodeConverter))]`
- inherits: `ChunkedDataNode`
- desc: An interior file node
- L563 _public property_ `public static Guid BlobTypeGuid { get; }` — Static accessor for the blob type guid
- L568 _public property_ `public IReadOnlyList<ChunkedDataNodeRef> Children { get; }` — Child nodes
- L574-577 _public ctor_ `public InteriorChunkedDataNode(IReadOnlyList<ChunkedDataNodeRef> children)` — Constructor
- L587-591 _public method_ `public static async Task<ChunkedData> CreateTreeAsync(LeafChunkedData leafChunkedData, InteriorChunkedDataNodeOptions options, IBlobWriter writer, CancellationToken cancellationToken)` — Create a tree of nodes from the given list of handles, splitting nodes in each layer based on the hash of the last node.
- L601-624 _public method_ `public static async Task<ChunkedDataNodeRef> CreateTreeAsync(List<ChunkedDataNodeRef> nodeRefs, InteriorChunkedDataNodeOptions chunkingOptions, IBlobWriter writer, CancellationToken cancellationToken)` — Create a tree of nodes from the given list of handles, splitting nodes in each layer based on the hash of the last node.
- L626-645 _private* method_ `static async Task<ChunkedDataNodeRef> OrderTreeAsync(ChunkedDataNodeRef source, IBlobWriter writer, CancellationToken cancellationToken)`
- L650-680 _private* method_ `static void CreateTreeLayer(List<ChunkedDataNodeRef> nodeRefs, InteriorChunkedDataNodeOptions options, List<(InteriorChunkedDataNode, long)> interiorNodes)` — Split a list of leaf handles into a layer of interior nodes
- L683-690 _public method_ `public override async Task CopyToStreamAsync(Stream outputStream, BlobSerializerOptions? options, CancellationToken cancellationToken)` — (inheritdoc)
- L698-721 _public method_ `public static async Task CopyToStreamAsync(BlobData nodeData, Stream outputStream, CancellationToken cancellationToken)` — Copy the contents of the node to the output stream without creating the intermediate FileNodes

#### class `EpicGames.Horde.Storage.Nodes.InteriorChunkedDataNodeConverter`  
`public class InteriorChunkedDataNodeConverter : BlobConverter<InteriorChunkedDataNode>`  
_public; L727-819_
- inherits: `BlobConverter<InteriorChunkedDataNode>`
- desc: Converter for interior node types
- L729 _private* field_ `readonly HordeApiVersion _writeVersion`
- L734-736 _public ctor_ `public InteriorChunkedDataNodeConverter() : this(HordeApiVersion.Latest)` — Constructor
- L742-745 _public ctor_ `public InteriorChunkedDataNodeConverter(HordeApiVersion writeVersion)` — Constructor
- L748-777 _public method_ `public override InteriorChunkedDataNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L780-797 _public method_ `public override BlobType Write(IBlobWriter writer, InteriorChunkedDataNode value, BlobSerializerOptions options)` — (inheritdoc)
- L802-818 _public method_ `public static BlobType GetBlobType(HordeApiVersion version)` — Gets the blob type for a particular Horde api version

#### class `EpicGames.Horde.Storage.Nodes.ChunkedDataStream`  
`class ChunkedDataStream : Stream`  
_internal*; L824-902_
- inherits: `Stream`
- desc: Stream which returns the content of a chunked data stream
- L827 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L830 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L833 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L836 _public property_ `public override long Length => ...` — (inheritdoc)
- L839 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L841 _private* field_ `readonly Pipe _pipe`
- L842 _private* field_ `readonly Stream _readStream`
- L843 _private* field_ `readonly BackgroundTask _writeTask`
- L844 _private* field_ `readonly long? _length`
- L850-852 _public ctor_ `public ChunkedDataStream(ChunkedDataNodeRef chunkedDataNodeRef) : this(chunkedDataNodeRef, chunkedDataNodeRef.Length)` — Constructor
- L859-865 _public ctor_ `public ChunkedDataStream(IBlobRef<ChunkedDataNode> entry, long? length)` — Constructor
- L868-875 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L877-881 _private* method_ `static async Task WriteDataAsync(IBlobRef<ChunkedDataNode> entry, PipeWriter pipeWriter, CancellationToken cancellationToken)`
- L884 _public method_ `public override ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L887-889 _public method_ `public override void Flush()` — (inheritdoc)
- L892 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L895 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L898 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L901 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/ChunkedDataWriter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.ChunkingOptions`  
`public class ChunkingOptions`  
_public; L16-36_
- desc: Options for creating file nodes
- L21 _public property_ `public LeafChunkedDataNodeOptions LeafOptions { get; set; }` — Options for creating leaf nodes
- L26 _public property_ `public InteriorChunkedDataNodeOptions InteriorOptions { get; set; }` — Options for creating interior nodes
- L31-35 _public ctor_ `public ChunkingOptions()` — Constructor

#### record `EpicGames.Horde.Storage.Nodes.LeafChunkedDataNodeOptions`  
`public record class LeafChunkedDataNodeOptions(int MinSize, int MaxSize, int TargetSize)`  
_public; L44-69_
- desc: Options for creating a specific type of file nodes
- L49 _public property_ `public static LeafChunkedDataNodeOptions Default { get; }` — Default settings
- L54 _public property_ `public int WindowSize => ...` — Window size to use when scanning for split points
- L59 _public property_ `public uint Threshold => ...` — Accessor for the BuzHash chunking threshold
- L65-68 _public ctor_ `public LeafChunkedDataNodeOptions(int size) : this(size, size, size)` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.LeafChunkedDataWriter`  
`public sealed class LeafChunkedDataWriter : IDisposable`  
_public; L74-357_
- inherits: `IDisposable`
- desc: Utility class for generating FileNode data directly into IBlobWriter instances, without constructing node representations first.
- L79 _public const_ `public const int DefaultBufferLength = 32 * 1024` — Default buffer length when calling CreateAsync/AppendAsync
- L81 _private* field_ `readonly IBlobWriter _writer`
- L82 _private* field_ `readonly LeafChunkedDataNodeOptions _leafChunkOptions`
- L83 _private* field_ `readonly Blake3.Hasher _hasher`
- L86 _private* field_ `long _totalLength`
- L87 _private* field_ `readonly List<ChunkedDataNodeRef> _leafHandles = []`
- L90 _private* field_ `uint _leafHash`
- L95 _public property_ `public long Length => ...` — Length of the file so far
- L101-104 _public ctor_ `public LeafChunkedDataWriter(IBlobWriter leafNodeWriter) : this(leafNodeWriter, LeafChunkedDataNodeOptions.Default)` — Constructor
- L111-116 _public ctor_ `public LeafChunkedDataWriter(IBlobWriter leafNodeWriter, LeafChunkedDataNodeOptions leafChunkOptions)` — Constructor
- L119-122 _public method_ `public void Dispose()` — (inheritdoc)
- L127-133 _public method_ `public void Reset()` — Reset the current state
- L138-141 _private* method_ `void ResetLeafState()` — Resets the state of the current leaf node
- L148-151 _public method_ `public async Task<LeafChunkedData> CreateAsync(FileInfo fileInfo, CancellationToken cancellationToken)` — Creates data for the given file
- L159-165 _public method_ `public async Task<LeafChunkedData> CreateAsync(FileInfo fileInfo, int bufferLength, CancellationToken cancellationToken)` — Creates data for the given file
- L172-175 _public method_ `public async Task<LeafChunkedData> CreateAsync(Stream stream, CancellationToken cancellationToken)` — Creates data from the given stream
- L183-188 _public method_ `public async Task<LeafChunkedData> CreateAsync(Stream stream, int bufferLength, CancellationToken cancellationToken)` — Creates data from the given stream
- L195-200 _public method_ `public async Task<LeafChunkedData> CreateAsync(ReadOnlyMemory<byte> data, CancellationToken cancellationToken)` — Creates data from the given data
- L207-210 _public method_ `public async Task AppendAsync(Stream stream, CancellationToken cancellationToken)` — Appends data to the current file
- L218-221 _public method_ `public async Task AppendAsync(Stream stream, int bufferLength, CancellationToken cancellationToken)` — Appends data to the current file
- L228-248 _public method_ `public async Task AppendAsync(ReadOnlyMemory<byte> data, CancellationToken cancellationToken)` — Appends data to the current file
- L258-325 _private* method_ `static int AppendToLeafNode(ReadOnlySpan<byte> currentData, ReadOnlySpan<byte> appendData, ref uint rollingHash, LeafChunkedDataNodeOptions options)` — Determines how much data to append to an existing leaf node
- L332-343 _public method_ `public async Task<LeafChunkedData> CompleteAsync(CancellationToken cancellationToken)` — Complete the current file, and write all open nodes to the underlying writer
- L350-356 _private* method_ `async ValueTask FlushLeafNodeAsync(CancellationToken cancellationToken)` — Writes the contents of the current leaf node to storage

#### record `EpicGames.Horde.Storage.Nodes.ChunkedData`  
`public record class ChunkedData(IoHash StreamHash, ChunkedDataNodeRef Root)`  
_public; L364-390_
- desc: Describes a chunked data stream
- L366 _private* field_ `static readonly ChunkingOptions s_defaultChunkingOptions = new()`
- L374 _public method_ `public static Task<ChunkedData> CreateAsync(IBlobWriter blobWriter, ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — Creates chunked data from a block of memory
- L384-389 _public method_ `public static async Task<ChunkedData> CreateAsync(IBlobWriter blobWriter, ReadOnlyMemory<byte> data, ChunkingOptions chunkingOptions, CancellationToken cancellationToken = default)` — Creates chunked data from a block of memory

#### class `EpicGames.Horde.Storage.Nodes.ChunkedDataWriter`  
`public sealed class ChunkedDataWriter : IDisposable`  
_public; L395-486_
- inherits: `IDisposable`
- desc: Writes chunked data to an output writer
- L397 _private* field_ `readonly IBlobWriter _writer`
- L398 _private* field_ `readonly ChunkingOptions _chunkingOptions`
- L399 _private* field_ `readonly LeafChunkedDataWriter _leafWriter`
- L404 _public property_ `public long Length => ...` — Length of the current stream
- L409-414 _public ctor_ `public ChunkedDataWriter(IBlobWriter writer, ChunkingOptions chunkingOptions)` — Constructor
- L417-420 _public method_ `public void Dispose()` — (inheritdoc)
- L425-428 _public method_ `public void Reset()` — Reset the current state
- L435-440 _public method_ `public async Task<ChunkedData> CreateAsync(FileInfo fileInfo, CancellationToken cancellationToken)` — Creates data for the given file
- L447-452 _public method_ `public async Task<ChunkedData> CreateAsync(ReadOnlyMemory<byte> data, CancellationToken cancellationToken)` — Creates data from the given data
- L459-462 _public method_ `public async Task AppendAsync(ReadOnlyMemory<byte> data, CancellationToken cancellationToken = default)` — Appends data to the current file
- L469-473 _public method_ `public async Task<ChunkedData> CompleteAsync(CancellationToken cancellationToken = default)` — Complete the current file, and write all open nodes to the underlying writer
- L480-485 _public method_ `public async Task<ChunkedData> FlushAsync(CancellationToken cancellationToken = default)` — Complete the current file, and write all open nodes to the underlying writer

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/CommitNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.CommitNode`  
`public class CommitNode`  
_public; L13-86_
- attrs: `[BlobConverter(typeof(CommitNodeConverter))]`
- desc: A node representing commit metadata
- L18 _public property_ `public static Guid BlobTypeGuid { get; }` — Static accessor for the blob type guid
- L23 _public property_ `public int Number { get; set; }` — The commit number
- L28 _public property_ `public IHashedBlobRef<CommitNode>? Parent { get; set; }` — Reference to the parent commit
- L33 _public property_ `public string Author { get; set; }` — Human readable name of the author of this change
- L38 _public property_ `public string? AuthorId { get; set; }` — Optional unique identifier for the author. May be an email address, user id, etc...
- L43 _public property_ `public string? Committer { get; set; }` — Human readable name of the committer of this change
- L48 _public property_ `public string? CommitterId { get; set; }` — Optional unique identifier for the committer. May be an email address, user id, etc...
- L53 _public property_ `public string Message { get; set; }` — Message for this commit
- L58 _public property_ `public DateTime Time { get; set; }` — Time that this commit was created
- L63 _public property_ `public DirectoryNodeRef Contents { get; set; }` — Contents of the tree at this commit
- L68 _public property_ `public Dictionary<Guid, IHashedBlobRef> Metadata { get; }` — Metadata for this commit, keyed by arbitrary GUID
- L73-85 _public ctor_ `public CommitNode(int number, IHashedBlobRef<CommitNode>? parent, string author, string? authorId, string? committer, string? commiterId, string message, DateTime time, DirectoryNodeRef contents, Dictionary<Guid, IHashedBlobRef> metadata)` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.CommitNodeConverter`  
`class CommitNodeConverter : BlobConverter<CommitNode>`  
_internal*; L88-145_
- inherits: `BlobConverter<CommitNode>`
- L90 _private* field_ `static readonly BlobType s_blobType = new(CommitNode.BlobTypeGuid, 1)`
- L92-120 _public method_ `public override CommitNode Read(IBlobReader reader, BlobSerializerOptions options)`
- L123-144 _public method_ `public override BlobType Write(IBlobWriter writer, CommitNode value, BlobSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/DdcRefNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.DdcRefNode`  
`public class DdcRefNode`  
_public; L13-47_
- attrs: `[BlobConverter(typeof(DdcRefNodeConverter))]`
- desc: A node containing ref data
- L18 _public property_ `public static Guid BlobTypeGuid { get; }` — Static accessor for the blob type guid
- L23 _public property_ `public IoHash RootHash { get; }` — Hash of the root node
- L28 _public property_ `public List<IHashedBlobRef> References { get; }` — References to attachments. We embed this in the ref node to ensure any aliased blobs have a hard reference from the root.
- L33-37 _public ctor_ `public DdcRefNode(IoHash rootHash)` — Constructor
- L42-46 _public ctor_ `public DdcRefNode(IoHash rootHash, IEnumerable<IHashedBlobRef> references)` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.DdcRefNodeConverter`  
`class DdcRefNodeConverter : BlobConverter<DdcRefNode>`  
_internal*; L49-66_
- inherits: `BlobConverter<DdcRefNode>`
- L51 _private* field_ `static readonly BlobType s_blobType = new(DdcRefNode.BlobTypeGuid, 1)`
- L53-58 _public method_ `public override DdcRefNode Read(IBlobReader reader, BlobSerializerOptions options)`
- L60-65 _public method_ `public override BlobType Write(IBlobWriter writer, DdcRefNode value, BlobSerializerOptions options)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/DirectoryNode.Extract.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.Nodes.IExtractStats`  
`public interface IExtractStats`  
_public; L18-44_
- desc: Stats reported for copy operations
- L23 _public* property_ `int NumFiles { get; }` — Number of files that have been copied
- L28 _public* property_ `long ExtractSize { get; }` — Total size of data to be copied
- L33 _public* property_ `double ExtractRate { get; }` — Processing speed, in bytes per second
- L38 _public* property_ `long DownloadSize { get; }` — Total size of the data downloaded
- L43 _public* property_ `double DownloadRate { get; }` — Download speed, in bytes per second

#### class `EpicGames.Horde.Storage.Nodes.ExtractStatsLogger`  
`public class ExtractStatsLogger : IProgress<IExtractStats>`  
_public; L49-102_
- inherits: `IProgress<IExtractStats>`
- desc: Progress logger for writing copy stats
- L51 _private* field_ `readonly int _totalCount`
- L52 _private* field_ `readonly long _totalSize`
- L53 _private* field_ `readonly ILogger _logger`
- L58 _public property_ `public bool ShowDownloadStats { get; set; }` — Whether to print out separate stats for download speed
- L63 _public ctor_ `public ExtractStatsLogger(ILogger logger)` — Constructor
- L69-74 _public ctor_ `public ExtractStatsLogger(int totalCount, long totalSize, ILogger logger)` — Constructor
- L77-101 _public method_ `public void Report(IExtractStats stats)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Nodes.ExtractOptions`  
`public class ExtractOptions`  
_public; L107-164_
- desc: Options for extracting data
- L112 _public property_ `public int? NumReadTasks { get; set; }` — Number of async tasks to spawn for reading
- L117 _public property_ `public static int DefaultNumReadTasks { get; }` — Default number of read tasks to use
- L122 _public property_ `public int? NumDecodeTasks { get; set; }` — Number of async tasks to spawn for decoding data
- L127 _public property_ `public static int DefaultNumDecodeTasks { get; }` — Default number of decode tasks to use
- L132 _public property_ `public int? NumWriteTasks { get; set; }` — Number of async tasks to spawn for writing output
- L137 _public method_ `public static int DefaultNumWriteTasks(long downloadSize)` — Default number of write tasks to use
- L143 _public property_ `public IProgress<IExtractStats>? Progress { get; set; }` — Output for progress updates
- L148 _public property_ `public TimeSpan ProgressUpdateFrequency { get; set; }` — Frequency that the progress object is updated
- L153 _public property_ `public bool VerifyOutput { get; set; }` — Whether to hash downloaded data to ensure it's correct
- L158 _public property_ `public bool VerboseOutput { get; set; }` — Output verbose logging about operations being performed
- L163 _public property_ `public int? MaxBatchSize { get; set; }` — Maximum number of exports to write in a single request

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeExtract`  
`public static class DirectoryNodeExtract`  
_public; L169-421_
- desc: Extension methods for extracting data from directory nodes
- L172-175 _private* method_ `static void TraceBlobRead(string type, string path, IBlobRef handle, ILogger logger)`
- L186 _public method_ `public static Task ExtractAsync(this IBlobRef<DirectoryNode> directoryRef, DirectoryInfo directoryInfo, ILogger logger, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Use an ExtractAsync overload that takes an ExtractOptions object")]` — Utility function to allow extracting a packed directory to disk
- L198-201 _public method_ `public static Task ExtractAsync(this IBlobRef<DirectoryNode> directoryRef, DirectoryInfo directoryInfo, IProgress<IExtractStats>? progress, ILogger logger, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Use an ExtractAsync overload that takes an ExtractOptions object")]` — Utility function to allow extracting a packed directory to disk
- L213-217 _public method_ `public static async Task ExtractAsync(this IBlobRef<DirectoryNode> directoryRef, DirectoryInfo directoryInfo, IProgress<IExtractStats>? progress, TimeSpan frequency, ILogger logger, CancellationToken cancellationToken = default)` — attrs: `[Obsolete("Use an ExtractAsync overload that takes an ExtractOptions object")]` — Utility function to allow extracting a packed directory to disk
- L226 _public method_ `public static Task ExtractAsync(this DirectoryNode directoryNode, DirectoryInfo directoryInfo, ILogger logger, CancellationToken cancellationToken = default)` — Utility function to allow extracting a packed directory to disk
- L237-241 _public method_ `public static async Task ExtractAsync(this IBlobRef<DirectoryNode> directoryRef, DirectoryInfo directoryInfo, ExtractOptions? options, ILogger logger, CancellationToken cancellationToken = default)` — Utility function to allow extracting a packed directory to disk
- L251-288 _public method_ `public static async Task ExtractAsync(this DirectoryNode directoryNode, DirectoryInfo directoryInfo, ExtractOptions? options, ILogger logger, CancellationToken cancellationToken = default)` — Utility function to allow extracting a packed directory to disk
- L292-296 _private* method_ `static async Task FindOutputChunksRootAsync(DirectoryInfo rootDir, DirectoryNode node, ChannelWriter<ChunkReadRequest> writer, ExtractOptions options, ILogger logger, CancellationToken cancellationToken)`
- L298-317 _private* method_ `static async Task FindOutputChunksForDirectoryAsync(DirectoryInfo rootDir, string path, DirectoryNode node, ChannelWriter<ChunkReadRequest> writer, ExtractOptions options, ILogger logger, CancellationToken cancellationToken)`
- L319-347 _internal method_ `internal static async Task FindOutputChunksForFileAsync(OutputFile outputFile, ChannelWriter<ChunkReadRequest> writer, ExtractOptions options, ILogger logger, CancellationToken cancellationToken)`
- L362-406 _internal method_ `internal static async Task UpdateStatsAsync(BatchChunkReader chunkReader, BatchOutputWriter outputWriter, Task writeTask, IProgress<IExtractStats> progress, TimeSpan frequency, CancellationToken cancellationToken)`
- L410-420 _private* method_ `static string CombinePaths(string basePath, string nextPath)`

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeExtract.ExtractStats`  
`class ExtractStats : IExtractStats`  
_private*; L353-360_
- inherits: `IExtractStats`
- L355 _public property_ `public int NumFiles { get; set; }`
- L356 _public property_ `public long ExtractSize { get; set; }`
- L357 _public property_ `public double ExtractRate { get; set; }`
- L358 _public property_ `public long DownloadSize { get; set; }`
- L359 _public property_ `public double DownloadRate { get; set; }`

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/DirectoryNode.Update.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Storage.Nodes.IUpdateStats`  
`public interface IUpdateStats`  
_public; L20-36_
- desc: Stats reported for copy operations
- L25 _public* property_ `int Count { get; }` — Number of files that have been copied
- L30 _public* property_ `long Size { get; }` — Total size of data to be copied
- L35 _public* property_ `double Rate { get; }` — Processing speed, in bytes per second

#### class `EpicGames.Horde.Storage.Nodes.UpdateStats`  
`class UpdateStats : IUpdateStats`  
_internal*; L41-92_
- inherits: `IUpdateStats`
- desc: Reports progress info back to callers
- L43 _private* field_ `readonly Lock _lockObject = new()`
- L44 _private* field_ `readonly Stopwatch _timer = Stopwatch.StartNew()`
- L45 _private* field_ `readonly IProgress<IUpdateStats>? _progress`
- L46 _private* field_ `long _lastTotalSize`
- L48 _public property_ `public int Count { get; set; }`
- L49 _public property_ `public long Size { get; set; }`
- L50 _public property_ `public double Rate { get; set; }`
- L52-55 _public ctor_ `public UpdateStats(IProgress<IUpdateStats>? progress)`
- L57-74 _public method_ `public void Update(int count, long size)`
- L76-85 _public method_ `public void Flush()`
- L87-91 _private* method_ `void FlushInternal()`

#### class `EpicGames.Horde.Storage.Nodes.UpdateStatsLogger`  
`public class UpdateStatsLogger : IProgress<IUpdateStats>`  
_public; L97-139_
- inherits: `IProgress<IUpdateStats>`
- desc: Progress logger for writing copy stats
- L99 _private* field_ `readonly int _totalCount`
- L100 _private* field_ `readonly long _totalSize`
- L101 _private* field_ `readonly ILogger _logger`
- L106 _public ctor_ `public UpdateStatsLogger(ILogger logger)` — Constructor
- L112-117 _public ctor_ `public UpdateStatsLogger(int totalCount, long totalSize, ILogger logger)` — Constructor
- L120-138 _public method_ `public void Report(IUpdateStats stats)` — (inheritdoc)

#### record `EpicGames.Horde.Storage.Nodes.FileUpdate`  
`public record class FileUpdate(string Path, FileEntryFlags Flags, long Length, IoHash StreamHash, List<ChunkedDataNodeRef> Nodes, DateTime ModTime = default, ReadOnlyMemory<byte> CustomData = default)`  
_public; L151-181_
- desc: Describes an update to a file in a directory tree
- L156-159 _public ctor_ `public FileUpdate(string path, FileEntryFlags flags, long length, ChunkedData chunkedData, DateTime modTime = default, ReadOnlyMemory<byte> customData = default) : this(path, flags, length, chunkedData.StreamHash, [chunkedData.Root], modTime, customData)` — Constructor
- L164-167 _public ctor_ `public FileUpdate(string path, FileEntryFlags flags, long length, LeafChunkedData chunkedData, DateTime modTime = default, ReadOnlyMemory<byte> customData = default) : this(path, flags, length, chunkedData.Hash, chunkedData.LeafHandles, modTime, customData)` — Constructor
- L172-180 _public method_ `public async ValueTask WriteInteriorNodesAsync(IBlobWriter writer, InteriorChunkedDataNodeOptions interiorNodeOptions, CancellationToken cancellationToken)` — Writes interior node data to the given writer

#### class `EpicGames.Horde.Storage.Nodes.DirectoryUpdate`  
`public class DirectoryUpdate`  
_public; L186-344_
- desc: Describes an update to a directory node
- L199 _public property_ `public SortedDictionary<string, DirectoryUpdate?> Directories { get; }` — Directories to be updated
- L204 _public property_ `public SortedDictionary<string, FileUpdate?> Files { get; }` — Files to be updated
- L209-213 _public method_ `public void Clear()` — Reset this instance
- L220-242 _public method_ `public void AddFile(string path, FileUpdate? fileUpdate)` — Adds a file by path to this object
- L253-268 _public method_ `public FileUpdate AddFile(string path, FileEntryFlags flags, long length, LeafChunkedData chunkedData, DateTime modTime = default, ReadOnlyMemory<byte> customData = default)` — Adds a file to the tree
- L274-281 _public method_ `public void AddFiles(IEnumerable<FileUpdate> files)` — Adds a filtered list of files from disk
- L283-322 _private* method_ `bool AddFiles(ReadOnlySpan<char> prefix, IEnumerator<FileUpdate> files)`
- L327-343 _public method_ `public async ValueTask WriteInteriorNodesAsync(IBlobWriter writer, InteriorChunkedDataNodeOptions interiorNodeOptions, CancellationToken cancellationToken)` — Writes interior node data to the given writer

#### class `EpicGames.Horde.Storage.Nodes.DirectoryUpdate.ReverseStringComparer`  
`class ReverseStringComparer : IComparer<string>`  
_private*; L188-194_
- inherits: `IComparer<string>`
- L190 _public property_ `public static ReverseStringComparer Instance { get; }`
- L192 _public method_ `public int Compare(string? x, string? y)`

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeUpdateExtensions`  
`public static class DirectoryNodeUpdateExtensions`  
_public; L349-639_
- desc: Extension methods for directory node updates
- L354-359 _public method_ `public static async Task<IHashedBlobRef<DirectoryNode>> AddFilesAsync(this IBlobWriter writer, DirectoryReference baseDir, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — Writes a tree of files to a storage writer
- L364-369 _public method_ `public static async Task<IHashedBlobRef<DirectoryNode>> AddFilesAsync(this IBlobWriter writer, DirectoryInfo baseDir, IReadOnlyList<FileInfo> files, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — Writes a tree of files to a storage writer
- L374-379 _public method_ `public static async Task<IHashedBlobRef<DirectoryNode>> AddFilesAsync(this IBlobWriter writer, DirectoryReference baseDir, IReadOnlyList<FileReference> files, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — Writes a tree of files to a storage writer
- L382-385 _public method_ `public static async Task AddFilesAsync(this DirectoryNode directoryNode, DirectoryInfo directoryInfo, IBlobWriter writer, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L388-391 _public method_ `public static Task AddFilesAsync(this DirectoryNode directoryNode, DirectoryReference baseDir, IEnumerable<FileReference> files, IBlobWriter writer, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L394-397 _public method_ `public static Task AddFilesAsync(this DirectoryNode directoryNode, DirectoryInfo baseDir, IEnumerable<FileInfo> files, IBlobWriter writer, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L406-411 _public method_ `public static Task UpdateAsync(this DirectoryNode directoryNode, IEnumerable<FileUpdate> updates, IBlobWriter writer, CancellationToken cancellationToken = default)` — Updates this tree of directory objects
- L420-447 _public method_ `public static async Task UpdateAsync(this DirectoryNode directoryNode, DirectoryUpdate update, IBlobWriter writer, CancellationToken cancellationToken = default)` — Updates this tree of directory objects
- L459-516 _public method_ `public static async Task AddFilesAsync(this DirectoryNode directoryNode, DirectoryReference baseDir, IEnumerable<FileInfo> files, IBlobWriter writer, ChunkingOptions? options = null, IProgress<IUpdateStats>? progress = null, CancellationToken cancellationToken = default)` — Adds files from a directory to the storage
- L518-552 _private* method_ `static List<(int Index, int Count)> ComputePartitions(IReadOnlyList<FileInfo> files, long totalSize)`
- L554-568 _private* method_ `static async ValueTask CreateLeafChunkNodesAsync(IBlobWriter writer, IReadOnlyList<FileInfo> files, LeafChunkedData[] leafChunks, int start, int count, UpdateStats? updateStats, ChunkingOptions options, CancellationToken cancellationToken)`
- L570-578 _private* method_ `static async Task WriteInputsAsync(IReadOnlyList<FileInfo> files, int start, int count, ChannelWriter<ChunkerSource> sourceWriter, CancellationToken cancellationToken)`
- L580-591 _private* method_ `static async Task HandleOutputsAsync(ChannelReader<ChunkerOutput> outputReader, IBlobWriter writerFork, LeafChunkedData[] leafChunks, UpdateStats? updateStats, CancellationToken cancellationToken)`
- L601-638 _public method_ `public static async Task CopyFromZipStreamAsync(this DirectoryNode directoryNode, Stream stream, IBlobWriter writer, ChunkingOptions options, CancellationToken cancellationToken = default)` — Copies entries from a zip file

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/DirectoryNode.ZipStream.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeZipStream`  
`class DirectoryNodeZipStream : Stream`  
_internal*; L18-183_
- inherits: `Stream`
- desc: Stream which zips a directory node tree dynamically
- L20 _private* field_ `readonly Pipe _pipe`
- L21 _private* field_ `readonly ILogger? _logger`
- L22 _private* field_ `readonly BackgroundTask _backgroundTask`
- L24 _private* field_ `long _position`
- L25 _private* field_ `ReadOnlySequence<byte> _current = ReadOnlySequence<byte>.Empty`
- L28 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L31 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L34 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L37 _public property_ `public override long Length => ...` — (inheritdoc)
- L40 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L48-53 _public ctor_ `public DirectoryNodeZipStream(IBlobRef<DirectoryNode> node, FileFilter? filter, ILogger? logger)` — Constructor
- L56-66 _protected method_ `protected override void Dispose(bool disposing)` — (inheritdoc)
- L69-74 _public method_ `public override async ValueTask DisposeAsync()` — (inheritdoc)
- L77-110 _public method_ `public override async ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default)` — (inheritdoc)
- L112-117 _private* method_ `static async Task CopyToPipeAsync(IBlobRef<DirectoryNode> node, FileFilter? filter, PipeWriter writer, ILogger? logger, CancellationToken cancellationToken)`
- L119-163 _private* method_ `static async Task CopyFilesAsync(IBlobRef<DirectoryNode> directoryRef, string prefix, FileFilter? filter, ZipArchive archive, ILogger? logger, CancellationToken cancellationToken)`
- L166-168 _public method_ `public override void Flush()` — (inheritdoc)
- L172 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L176 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L179 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L182 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeZipStreamExtensions`  
`public static class DirectoryNodeZipStreamExtensions`  
_public; L188-199_
- desc: Extension methods for DirectoryNodeZipStream
- L197 _public method_ `public static Stream AsZipStream(this IBlobRef<DirectoryNode> directoryRef, FileFilter? filter = null, ILogger? logger = null)` — Returns a stream containing the zipped contents of this directory

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/DirectoryNode.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Storage.Nodes.DirectoryFlags`  
`public enum DirectoryFlags`  
_public; L19-25_
- desc: Flags for a directory node
- L24 _public* enumerator_ `None = 0` — No flags specified

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNode`  
`public class DirectoryNode`  
_public; L31-339_
- attrs: `[BlobConverter(typeof(DirectoryNodeConverter))]`
- desc: A directory node
- L36 _public property_ `public static Guid BlobTypeGuid { get; }` — Type of serialized directory node blobs
- L38 _private* field_ `readonly SortedDictionary<string, FileEntry> _nameToFileEntry = ...`
- L38 _private* field_ `readonly SortedDictionary< _nameToFileEntry = new(StringComparer.Ordinal)`
- L39 _private* field_ `readonly SortedDictionary<string, DirectoryEntry> _nameToDirectoryEntry = ...`
- L39 _private* field_ `readonly SortedDictionary< _nameToDirectoryEntry = new(StringComparer.Ordinal)`
- L44 _public property_ `public long Length => ...` — Total size of this directory
- L49 _public property_ `public DirectoryFlags Flags { get; }` — Flags for this directory
- L54 _public property_ `public IReadOnlyCollection<FileEntry> Files => ...` — All the files within this directory
- L59 _public property_ `public IReadOnlyDictionary<string, FileEntry> NameToFile => ...` — Map of name to file entry
- L64 _public property_ `public IReadOnlyCollection<DirectoryEntry> Directories => ...` — All the subdirectories within this directory
- L69 _public property_ `public IReadOnlyDictionary<string, DirectoryEntry> NameToDirectory => ...` — Map of name to file entry
- L75-78 _public ctor_ `public DirectoryNode(DirectoryFlags flags = DirectoryFlags.None)` — Constructor
- L83-87 _public method_ `public void Clear()` — Clear the contents of this directory
- L94 _public method_ `public bool Contains(string name)` — Check whether an entry with the given name exists in this directory
- L102-105 _public method_ `public void AddFile(FileEntry entry)` — Adds a new file entry to this directory
- L114-119 _public method_ `public FileEntry AddFile(string name, FileEntryFlags flags, ChunkedData data)` — Adds a new file with the given name
- L126 _public method_ `public FileEntry GetFileEntry(string name)` — Attempts to get a file entry with the given name
- L134 _public method_ `public bool TryGetFileEntry(string name, [NotNullWhen(true)] out FileEntry? entry)` — Attempts to get a file entry with the given name
- L141 _public method_ `public Stream OpenFile(string name)` — Opens a file for reading
- L148-159 _public method_ `public Stream? TryOpenFile(string name)` — Attempts to open a file for reading
- L166 _public method_ `public bool DeleteFile(string name)` — Deletes the file entry with the given name
- L174-200 _public method_ `public async ValueTask<FileEntry?> GetFileEntryByPathAsync(string path, CancellationToken cancellationToken = default)` — Attempts to get a file entry from a path
- L208 _public method_ `public ValueTask<DirectoryNode?> GetDirectoryByPathAsync(string path, CancellationToken cancellationToken = default)` — Attempts to get a directory entry from a path
- L210-237 _private* method_ `static async ValueTask<DirectoryNode?> GetDirectoryByPathAsync(DirectoryNode directoryNode, string path, CancellationToken cancellationToken = default)`
- L245-262 _public method_ `public async ValueTask<bool> DeleteFileByPathAsync(string path, CancellationToken cancellationToken = default)` — Deletes a file with the given path
- L272-280 _public method_ `public void AddDirectory(DirectoryEntry entry)` — Adds a new directory with the given name
- L287 _public method_ `public DirectoryEntry GetDirectoryEntry(string name)` — Get a directory entry with the given name
- L295 _public method_ `public bool TryGetDirectoryEntry(string name, [NotNullWhen(true)] out DirectoryEntry? entry)` — Attempts to get a directory entry with the given name
- L303-311 _public method_ `public async ValueTask<DirectoryNode> OpenDirectoryAsync(string name, CancellationToken cancellationToken = default)` — Tries to get a directory with the given name
- L319-329 _public method_ `public async ValueTask<DirectoryNode?> TryOpenDirectoryAsync(string name, CancellationToken cancellationToken = default)` — Tries to get a directory with the given name
- L336 _public method_ `public bool DeleteDirectory(string name)` — Deletes the file entry with the given name

#### class `EpicGames.Horde.Storage.Nodes.DirectoryNodeConverter`  
`class DirectoryNodeConverter : BlobConverter<DirectoryNode>`  
_internal*; L341-484_
- inherits: `BlobConverter<DirectoryNode>`
- L343 _private* field_ `readonly HordeApiVersion _writeVersion`
- L348-350 _public ctor_ `public DirectoryNodeConverter() : this(HordeApiVersion.AddRollingHashesForLeafNodes)` — Constructor
- L355 _public ctor_ `public DirectoryNodeConverter(HordeApiVersion writeVersion)` — Constructor
- L359-412 _public method_ `public override DirectoryNode Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L415-465 _public method_ `public override BlobType Write(IBlobWriter writer, DirectoryNode value, BlobSerializerOptions options)` — (inheritdoc)
- L467-483 _private* method_ `static BlobType GetBlobType(HordeApiVersion version)`

#### record `EpicGames.Horde.Storage.Nodes.DirectoryNodeRef`  
`public record class DirectoryNodeRef(long Length, IHashedBlobRef<DirectoryNode> Handle)`  
_public; L491-491_
- desc: Reference to a directory node, including the target hash and length

#### record `EpicGames.Horde.Storage.Nodes.DirectoryEntry`  
`public record class DirectoryEntry(string Name, long Length, IHashedBlobRef<DirectoryNode> Handle) : DirectoryNodeRef(Length, Handle)`  
_public; L497-499_
- attrs: `[DebuggerDisplay("{Name}")]`
- inherits: `DirectoryNodeRef(Length, Handle)`
- desc: Entry for a directory within a directory node

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/FileEntry.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Storage.Nodes.FileEntryFlags`  
`public enum FileEntryFlags`  
_public; L16-52_
- attrs: `[Flags]`
- desc: Flags for a file entry
- L21 _public* enumerator_ `None = 0` — No other flags set
- L26 _public* enumerator_ `Executable = 4` — Indicates that the referenced file is executable
- L31 _public* enumerator_ `ReadOnly = 8` — File should be stored as read-only
- L36 _public* enumerator_ `Text = 16` — File contents are utf-8 encoded text. Client may want to replace line-endings with OS-specific format.
- L41 _public* enumerator_ `HasCustomData = 32` — Used to indicate that custom data is included in the output. Used internally for serialization; not exposed to users.
- L46 _public* enumerator_ `Utf16 = 64` — File should be materialized as UTF-16 (but is stored as a UTF-8 source)
- L51 _public* enumerator_ `HasModTime = 128` — Whether the file entry includes a modification time

#### class `EpicGames.Horde.Storage.Nodes.FileEntry`  
`public sealed class FileEntry`  
_public; L57-254_
- desc: Entry for a file within a directory node
- L62 _public property_ `public string Name { get; }` — Name of this file
- L67 _public property_ `public FileEntryFlags Flags { get; set; }` — Flags for this file
- L72 _public property_ `public long Length { get; }` — Length of this entry
- L77 _public property_ `public IoHash Hash { get; }` — Hash of the file as a contiguous stream. This differs from individual node hashes which hash the Merkle tree of chunks forming it.
- L82 _public property_ `public ChunkedDataNodeRef Target { get; }` — Reference to the chunked data for the file
- L87 _public property_ `public DateTime ModTime { get; }` — Last modified time. Only valid if FileEntryFlags.HasModTime is set.
- L92 _public property_ `public ReadOnlyMemory<byte> CustomData { get; set; }` — Custom user data for this file entry
- L97-100 _public ctor_ `public FileEntry(string name, FileEntryFlags flags, ChunkedData chunkedData, DateTime modTime = default, ReadOnlyMemory<byte> customData = default) : this(name, flags, chunkedData.Root.Length, chunkedData.StreamHash, chunkedData.Root, modTime, customData)` — Constructor
- L105-124 _public ctor_ `public FileEntry(string name, FileEntryFlags flags, long length, IoHash hash, ChunkedDataNodeRef target, DateTime modTime = default, ReadOnlyMemory<byte> customData = default)` — Constructor
- L130 _public method_ `public Stream OpenAsStream()` — Creates a stream that returns the contents of this file
- L138 _public method_ `public Task CopyToStreamAsync(Stream outputStream, CancellationToken cancellationToken = default)` — Copies the contents of this node and its children to the given output stream
- L145 _public method_ `public Task<byte[]> ReadAllBytesAsync(CancellationToken cancellationToken = default)` — Reads this entire file as a byte array
- L154-165 _public method_ `public async Task CopyToFileAsync(FileInfo file, CancellationToken cancellationToken)` — Extracts the contents of this node to a file
- L172-197 _public method_ `public static FileEntryFlags GetPermissions(FileInfo fileInfo)` — Get the permission flags from a file on disk
- L204-235 _public method_ `public static void SetPermissions(FileInfo fileInfo, FileEntryFlags flags)` — Applies the correct permissions to a file for a particular set of file entry flags
- L237-250 _private* method_ `static int UpdateFileMode(int mode, FileEntryFlags flags)`
- L253 _public method_ `public override string ToString()` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/Nodes/RedirectNode.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.Nodes.RedirectNode`  
`public static class RedirectNode`  
_public; L10-16_
- desc: Shared definitions for RedirectNode{T}
- L15 _public property_ `public static Guid BlobTypeGuid { get; }` — Static accessor for the blob type guid

#### class `EpicGames.Horde.Storage.Nodes.RedirectNode`  
`public class RedirectNode<T>`  
_public; L22-34_
- attrs: `[BlobConverter(typeof(RedirectNodeConverter<>))]`
- desc: A node containing arbitrary compact binary data
- L27 _public property_ `public IHashedBlobRef<T> Target { get; }` — The target handle
- L33 _public ctor_ `public RedirectNode(IHashedBlobRef<T> handle)` — Constructor

#### class `EpicGames.Horde.Storage.Nodes.RedirectNodeConverter`  
`class RedirectNodeConverter<T> : BlobConverter<RedirectNode<T>>`  
_internal*; L36-53_
- inherits: `BlobConverter<RedirectNode<T>>`
- L38 _private* field_ `static readonly BlobType s_blobType = new(RedirectNode.BlobTypeGuid, 1)`
- L41-45 _public method_ `public override RedirectNode<T> Read(IBlobReader reader, BlobSerializerOptions options)` — (inheritdoc)
- L48-52 _public method_ `public override BlobType Write(IBlobWriter writer, RedirectNode<T> value, BlobSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/ObjectKey.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Storage.ObjectKey`  
`public readonly struct ObjectKey : IEquatable<ObjectKey>`  
_public; L12-139_
- attrs: `[JsonSchemaString]`
- inherits: `IEquatable<ObjectKey>`
- desc: Path to an object within an IObjectStore. Object keys are normalized to lowercase, and may consist of the characters [a-z0-9_./].
- L25 _private* field_ `readonly Utf8String _path`
- L30 _public property_ `public Utf8String Path => ...` — Accessor for the internal path string
- L36-39 _public ctor_ `public ObjectKey(string path) : this(new Utf8String(path))` — Constructor
- L45-79 _public ctor_ `public ObjectKey(Utf8String path)` — Constructor
- L86-90 _public ctor_ `public ObjectKey(Utf8String path, Validate validate)` — Constructor
- L95-115 _public method_ `public static ObjectKey Sanitize(Utf8String path)` — Makes an object key from the given path
- L120 _public method_ `public bool IsValid()` — Whether the blob locator is valid
- L123 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L126 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L129 _public method_ `public bool Equals(ObjectKey other)` — (inheritdoc)
- L132 _public method_ `public override string ToString()` — (inheritdoc)
- L135 _public operator_ `public static bool operator ==(ObjectKey left, ObjectKey right)` — (inheritdoc)
- L138 _public operator_ `public static bool operator !=(ObjectKey left, ObjectKey right)` — (inheritdoc)

#### enum `EpicGames.Horde.Storage.ObjectKey.Validate`  
`public enum Validate`  
_public; L17-23_
- desc: Dummy enum to allow invoking the constructor which takes a sanitized full path
- L22 _public* enumerator_ `None` — Dummy value

### `Source/Programs/Shared/EpicGames.Horde/Storage/ObjectStores/FileObjectStore.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ObjectStores.FileObjectStore`  
`public sealed class FileObjectStore : IObjectStore`  
_public; L14-149_
- inherits: `IObjectStore`
- desc: Storage backend that utilizes the local filesystem
- L16 _private* field_ `readonly DirectoryReference _baseDir`
- L17 _private* field_ `readonly MemoryMappedFileCache _mappedFileCache`
- L22 _public property_ `public DirectoryReference BaseDir => ...` — Accessor for the base directory
- L25 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L32-38 _public ctor_ `public FileObjectStore(DirectoryReference baseDir, MemoryMappedFileCache mappedFileCache)` — Constructor
- L43 _private* method_ `FileReference GetBlobFile(ObjectKey key)` — Gets the path for storing a file on disk
- L46-52 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L61-65 _public method_ `public IReadOnlyMemoryOwner<byte> Read(ObjectKey key, int offset, int? length)` — Maps a file into memory for reading, and returns a handle to it
- L68-71 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L74-101 _public method_ `public async Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L104-108 _public method_ `public Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L111-122 _public method_ `public Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L128-132 _public method_ `public void Delete(ObjectKey key)` — Delete a file from the store
- L135-139 _public method_ `public Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L142 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L145 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L148 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.ObjectStores.FileObjectStoreFactory`  
`public sealed class FileObjectStoreFactory : IDisposable`  
_public; L154-175_
- inherits: `IDisposable`
- desc: Storage backend that utilizes the local filesystem
- L156 _private* field_ `readonly MemoryMappedFileCache _mappedFileCache`
- L161-164 _public ctor_ `public FileObjectStoreFactory()` — Constructor
- L167 _public method_ `public void Dispose()` — (inheritdoc)
- L173 _public method_ `public FileObjectStore CreateStore(DirectoryReference baseDir)` — Create a new store instance with the given base directory

### `Source/Programs/Shared/EpicGames.Horde/Storage/ObjectStores/HttpObjectStore.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ObjectStores.HttpObjectStore`  
`public class HttpObjectStore : IObjectStore`  
_public; L15-123_
- inherits: `IObjectStore`
- desc: Implements an object store utilizing standard HTTP operations
- L17 _private* field_ `readonly Uri _baseUrl`
- L18 _private* field_ `readonly Func<HttpClient> _createHttpClient`
- L21 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L28-32 _public ctor_ `public HttpObjectStore(Uri baseUrl, Func<HttpClient> createHttpClient)` — Constructor
- L34 _private* method_ `Uri GetUri(ObjectKey key)`
- L38-44 _public method_ `public async Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L47-54 _public method_ `public async Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L57-72 _public method_ `public async Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L75-77 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)
- L80-93 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L96-102 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L105 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L109 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L113-122 _public method_ `public async Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/ObjectStores/MemoryObjectStore.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ObjectStores.MemoryObjectStore`  
`public sealed class MemoryObjectStore : IObjectStore`  
_public; L16-95_
- inherits: `IObjectStore`
- desc: In-memory implementation of a storage backend
- L18 _private* field_ `readonly ConcurrentDictionary<ObjectKey, byte[]> _keyToData = ...`
- L18 _private* field_ `readonly ConcurrentDictionary< _keyToData = new()`
- L23 _public property_ `public IReadOnlyDictionary<ObjectKey, byte[]> Blobs => ...` — Read only access to the stored blobs
- L26 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L29-32 _public method_ `public Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L35-38 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken)` — (inheritdoc)
- L40-48 _private* method_ `ReadOnlyMemory<byte> GetData(ObjectKey key, int offset, int? length)`
- L51-58 _public method_ `public async Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L61-64 _public method_ `public Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L67-78 _public method_ `public Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L81-85 _public method_ `public Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken)` — (inheritdoc)
- L88 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L91 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)` — (inheritdoc)
- L94 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/ObjectStores/PrefixedObjectStore.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.ObjectStores.PrefixedObjectStore`  
`public sealed class PrefixedObjectStore : IObjectStore`  
_public; L14-63_
- inherits: `IObjectStore`
- desc: Storage backend wrapper which adds a prefix to the start of each item
- L16 _private* field_ `readonly Utf8String _prefix`
- L17 _private* field_ `readonly IObjectStore _inner`
- L20 _public property_ `public bool SupportsRedirects => ...` — (inheritdoc)
- L22 _private* method_ `ObjectKey GetKeyWithPrefix(ObjectKey key)`
- L27-35 _public ctor_ `public PrefixedObjectStore(string prefix, IObjectStore inner)` — Constructor
- L38 _public method_ `public Task DeleteAsync(ObjectKey locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L41 _public method_ `public Task<bool> ExistsAsync(ObjectKey locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L44 _public method_ `public Task<long> GetSizeAsync(ObjectKey locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L47 _public method_ `public Task<Stream> OpenAsync(ObjectKey locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L50 _public method_ `public Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey locator, int offset, int? length, CancellationToken cancellationToken = default)` — (inheritdoc)
- L53 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L56 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey locator, CancellationToken cancellationToken = default)` — (inheritdoc)
- L59 _public method_ `public Task WriteAsync(ObjectKey locator, Stream stream, CancellationToken cancellationToken = default)` — (inheritdoc)
- L62 _public method_ `public void GetStats(StorageStats stats)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/RefName.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.Storage.RefName`  
`public readonly struct RefName : IEquatable<RefName>, IComparable<RefName>`  
_public; L21-163_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(RefNameJsonConverter))] [TypeConverter(typeof(RefNameTypeConverter))] [CbConverter(typeof(RefNameCbConverter))]`
- inherits: `IEquatable<RefName>, IComparable<RefName>`
- desc: Identifier for a ref in the storage system. Refs serve as GC roots, and are persistent entry points to expanding data structures within the store.
- L26 _public property_ `public static RefName Empty { get; }` — Empty ref name
- L31 _public property_ `public Utf8String Text { get; }` — String for the ref name
- L37-40 _public ctor_ `public RefName(string text) : this(new Utf8String(text))` — Constructor
- L46-50 _public ctor_ `public RefName(Utf8String text)` — Constructor
- L57-102 _public method_ `public static void ValidatePathArgument(ReadOnlySpan<byte> text, string argumentName)` — Validates a given string as a blob id
- L104 _private* field_ `static readonly uint[] s_validChars = CreateValidCharsArray()`
- L106-118 _private* method_ `static uint[] CreateValidCharsArray()`
- L120-123 _private* method_ `static bool IsValidChar(byte character)`
- L126 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L129 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L132 _public method_ `public bool Equals(RefName refName)` — (inheritdoc)
- L135 _public method_ `public int CompareTo(RefName other)` — (inheritdoc)
- L138 _public method_ `public override string ToString()` — (inheritdoc)
- L141 _public operator_ `public static bool operator ==(RefName lhs, RefName rhs)` — (inheritdoc)
- L144 _public operator_ `public static bool operator !=(RefName lhs, RefName rhs)` — (inheritdoc)
- L147 _public operator_ `public static bool operator <(RefName lhs, RefName rhs)` — (inheritdoc)
- L150 _public operator_ `public static bool operator <=(RefName lhs, RefName rhs)` — (inheritdoc)
- L153 _public operator_ `public static bool operator >(RefName lhs, RefName rhs)` — (inheritdoc)
- L156 _public operator_ `public static bool operator >=(RefName lhs, RefName rhs)` — (inheritdoc)
- L162 _public operator_ `public static implicit operator RefName(string name)` — Construct a ref from a string

#### class `EpicGames.Horde.Storage.RefNameJsonConverter`  
`sealed class RefNameJsonConverter : JsonConverter<RefName>`  
_internal*; L168-175_
- inherits: `JsonConverter<RefName>`
- desc: Type converter for IoHash to and from JSON
- L171 _public method_ `public override RefName Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L174 _public method_ `public override void Write(Utf8JsonWriter writer, RefName value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.RefNameTypeConverter`  
`sealed class RefNameTypeConverter : TypeConverter`  
_internal*; L180-193_
- inherits: `TypeConverter`
- desc: Type converter from strings to IoHash objects
- L183-186 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L189-192 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object? value)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.RefNameCbConverter`  
`sealed class RefNameCbConverter : CbConverter<RefName>`  
_internal*; L198-208_
- inherits: `CbConverter<RefName>`
- desc: Type converter to compact binary
- L201 _public method_ `public override RefName Read(CbField field)` — (inheritdoc)
- L204 _public method_ `public override void Write(CbWriter writer, RefName value)` — (inheritdoc)
- L207 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, RefName value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Storage/StorageBackendCache.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.StorageBackendCache`  
`public sealed class StorageBackendCache : IDisposable`  
_public; L20-383_
- inherits: `IDisposable`
- desc: Implementation of a local disk cache which can be shared by multiple backends
- L172 _private field_ `private readonly Lock _lockObject = new()`
- L174 _private* field_ `readonly MemoryMappedFileCache _memoryMappedFileCache`
- L175 _private* field_ `readonly FileObjectStore _objectStore`
- L176 _private* field_ `readonly long _maxSize`
- L177 _private* field_ `readonly ILogger _logger`
- L179 _private* field_ `readonly LinkedList<Item> _items = new()`
- L180 _private* field_ `readonly Dictionary<ObjectKey, Item> _keyToItem = ...`
- L180 _private* field_ `readonly Dictionary< _keyToItem = []`
- L181 _private* field_ `readonly Dictionary<ObjectKey, PendingItem> _keyToPendingItem = ...`
- L181 _private* field_ `readonly Dictionary< _keyToPendingItem = []`
- L183 _private* field_ `long _size`
- L184 _private* field_ `long _cleanCount`
- L185 _private* field_ `long _cleanTimeTicks`
- L186 _private* field_ `long _fetchTimeTicks`
- L187 _private* field_ `long _writeTimeTicks`
- L188 _private* field_ `long _fetchBytes`
- L190 _internal property_ `internal IEnumerable<ObjectKey> Items => ...`
- L192-202 _internal method_ `internal IEnumerable<BlobLocator> GetLocators()`
- L207-210 _public ctor_ `public StorageBackendCache() : this(null, null)` — Constructor
- L215-218 _public ctor_ `public StorageBackendCache(DirectoryReference? cacheDir, long? maxSize) : this(cacheDir, maxSize, NullLogger.Instance)` — Constructor
- L226-235 _public ctor_ `public StorageBackendCache(DirectoryReference? cacheDir, long? maxSize, ILogger logger)` — Constructor
- L238-245 _public method_ `public void Dispose()` — (inheritdoc)
- L252-255 _public method_ `public IObjectStore CreateWrapper(string keyPrefix, IObjectStore store)` — Wraps an onject store in another store that routes requests through the cache
- L262-265 _public method_ `public IStorageBackend CreateWrapper(string keyPrefix, IStorageBackend backend)` — Wraps a storage backend in another backend that routes requests through the cache
- L273-276 _public method_ `public static IStorageBackend CreateWrapper(string keyPrefix, IStorageBackend backend, StorageBackendCache? cache)` — Wraps a storage backend in another backend that routes requests through the cache
- L279-312 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, Func<CancellationToken, Task<Stream>> createStreamAsync, CancellationToken cancellationToken = default)` — (inheritdoc)
- L314-366 _private* method_ `async Task ReadIntoCacheAsync(ObjectKey key, Func<CancellationToken, Task<Stream>> createStreamAsync, CancellationToken cancellationToken)`
- L371-378 _public method_ `public void GetStats(StorageStats stats)` — Get stats for the cache operation
- L381 _public method_ `public void WriteRefStats(ILogger logger)` — (inheritdoc)

#### class `EpicGames.Horde.Storage.StorageBackendCache.Item`  
`class Item`  
_private*; L22-34_
- L24 _public property_ `public ObjectKey Key { get; }`
- L25 _public property_ `public long Length { get; }`
- L26 _public property_ `public LinkedListNode<Item> ListNode { get; }`
- L28-33 _public ctor_ `public Item(ObjectKey key, long length)`

#### class `EpicGames.Horde.Storage.StorageBackendCache.PendingItem`  
`class PendingItem`  
_private*; L36-53_
- L38 _private* field_ `int _refCount`
- L39 _private* field_ `readonly BackgroundTask _readTask`
- L41 _public ctor_ `public PendingItem(BackgroundTask readTask)`
- L42 _public method_ `public void AddRef()`
- L44-50 _public method_ `public async ValueTask ReleaseAsync()`
- L52 _public method_ `public Task WaitAsync(CancellationToken cancellationToken)`

#### class `EpicGames.Horde.Storage.StorageBackendCache.ObjectStoreWrapper`  
`sealed class ObjectStoreWrapper : IObjectStore`  
_private*; L55-96_
- inherits: `IObjectStore`
- L57 _private* field_ `readonly string _keyPrefix`
- L58 _private* field_ `readonly StorageBackendCache _cacheStorage`
- L59 _private* field_ `readonly IObjectStore _inner`
- L61 _public property_ `public bool SupportsRedirects => ...`
- L63-68 _public ctor_ `public ObjectStoreWrapper(string keyPrefix, StorageBackendCache cacheStorage, IObjectStore inner)`
- L70-74 _public method_ `public async Task<Stream> OpenAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)`
- L76-82 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadAsync(ObjectKey key, int offset, int? length, CancellationToken cancellationToken = default)`
- L84 _public method_ `public Task WriteAsync(ObjectKey key, Stream stream, CancellationToken cancellationToken = default)`
- L85 _public method_ `public Task DeleteAsync(ObjectKey key, CancellationToken cancellationToken = default)`
- L86 _public method_ `public Task<bool> ExistsAsync(ObjectKey key, CancellationToken cancellationToken = default)`
- L87 _public method_ `public Task<long> GetSizeAsync(ObjectKey key, CancellationToken cancellationToken = default)`
- L88 _public method_ `public ValueTask<Uri?> TryGetReadRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)`
- L89 _public method_ `public ValueTask<Uri?> TryGetWriteRedirectAsync(ObjectKey key, CancellationToken cancellationToken = default)`
- L91-95 _public method_ `public void GetStats(StorageStats stats)`

#### class `EpicGames.Horde.Storage.StorageBackendCache.BackendWrapper`  
`sealed class BackendWrapper : IStorageBackend`  
_private*; L98-170_
- inherits: `IStorageBackend`
- L100 _public const_ `public const string BlobExtension = ".blob"`
- L102 _private* field_ `readonly string _keyPrefix`
- L103 _private* field_ `readonly StorageBackendCache _cacheStorage`
- L104 _private* field_ `readonly IStorageBackend _inner`
- L106 _public property_ `public bool SupportsRedirects => ...`
- L108-117 _public ctor_ `public BackendWrapper(string keyPrefix, StorageBackendCache cacheStorage, IStorageBackend inner)`
- L119-123 _public method_ `public async Task<Stream> OpenBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)`
- L125-131 _public method_ `public async Task<IReadOnlyMemoryOwner<byte>> ReadBlobAsync(BlobLocator locator, int offset, int? length, CancellationToken cancellationToken = default)`
- L133 _public method_ `public Task<BlobLocator> WriteBlobAsync(Stream stream, IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)`
- L136 _public method_ `public Task WriteBlobAsync(BlobLocator locator, Stream stream, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)`
- L139 _public method_ `public ValueTask<Uri?> TryGetBlobReadRedirectAsync(BlobLocator locator, CancellationToken cancellationToken = default)`
- L142 _public method_ `public ValueTask<Uri?> TryGetBlobWriteRedirectAsync(BlobLocator locator, IReadOnlyCollection<BlobLocator> imports, CancellationToken cancellationToken = default)`
- L145 _public method_ `public ValueTask<(BlobLocator, Uri)?> TryGetBlobWriteRedirectAsync(IReadOnlyCollection<BlobLocator> imports, string? prefix = null, CancellationToken cancellationToken = default)`
- L148-152 _public method_ `public void GetStats(StorageStats stats)`
- L156 _public method_ `public Task<BlobAliasLocator[]> FindAliasesAsync(string name, int? maxResults = null, CancellationToken cancellationToken = default)`
- L163 _public method_ `public Task<HashedBlobRefValue?> TryReadRefAsync(RefName name, RefCacheTime cacheTime = default, CancellationToken cancellationToken = default)`
- L168 _public method_ `public Task UpdateMetadataAsync(UpdateMetadataRequest request, CancellationToken cancellationToken = default)`

### `Source/Programs/Shared/EpicGames.Horde/Storage/StorageExceptions.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.StorageException`  
`public class StorageException : Exception`  
_public; L10-27_
- inherits: `Exception`
- desc: Base exception for the storage service
- L15-18 _public ctor_ `public StorageException(string message) : base(message)` — Constructor
- L23-26 _public ctor_ `public StorageException(string message, Exception? innerException) : base(message, innerException)` — Constructor

#### class `EpicGames.Horde.Storage.ObjectNotFoundException`  
`public sealed class ObjectNotFoundException : StorageException`  
_public; L32-55_
- inherits: `StorageException`
- desc: Exception thrown when an object does not exist
- L37 _public property_ `public ObjectKey Key { get; }` — Path to the object
- L42-45 _public ctor_ `public ObjectNotFoundException(ObjectKey key, Exception? innerException = null) : this(key, $"Object '{key}' was not found", innerException)` — Constructor
- L50-54 _public ctor_ `public ObjectNotFoundException(ObjectKey key, string message, Exception? innerException = null) : base(message, innerException)` — Constructor

#### class `EpicGames.Horde.Storage.RefNameNotFoundException`  
`public sealed class RefNameNotFoundException : StorageException`  
_public; L60-76_
- inherits: `StorageException`
- desc: Exception for a ref not existing
- L65 _public property_ `public RefName Name { get; }` — Name of the missing ref
- L71-75 _public ctor_ `public RefNameNotFoundException(RefName name) : base($"Ref '{name}' not found")` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Storage/StorageMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.WriteBlobResponse`  
`public class WriteBlobResponse`  
_public; L14-30_
- desc: Response from uploading a bundle
- L19 _public property_ `public string Blob { get; set; }` — Path to the uploaded blob
- L24 _public property_ `public Uri? UploadUrl { get; set; }` — URL to upload the blob to.
- L29 _public property_ `public bool? SupportsRedirects { get; set; }` — Flag for whether the client could use a redirect instead (ie. not post content to the server, and get an upload url back).

#### class `EpicGames.Horde.Storage.FindNodeResponse`  
`public class FindNodeResponse`  
_public; L35-69_
- desc: Response object for finding an alias
- L40 _public property_ `public BlobLocator Blob { get; set; }` — Locator for the target blob
- L45 _public property_ `public int Rank { get; set; }` — Rank of this alias
- L50 _public property_ `public byte[] Data { get; set; }` — Inline data associated with this alias
- L55-58 _public ctor_ `public FindNodeResponse()` — Default constructor
- L63-68 _public ctor_ `public FindNodeResponse(BlobLocator blob, int rank, byte[] data)` — Constructor

#### class `EpicGames.Horde.Storage.FindNodesResponse`  
`public class FindNodesResponse`  
_public; L74-80_
- desc: Response object for searching for nodes with a given alias
- L79 _public property_ `public List<FindNodeResponse> Nodes { get; set; }` — Hash of the target node

#### class `EpicGames.Horde.Storage.UpdateMetadataRequest`  
`public class UpdateMetadataRequest`  
_public; L85-106_
- desc: Request to batch update metadata in the database
- L90 _public property_ `public List<AddAliasRequest> AddAliases { get; set; }` — List of aliases to add
- L95 _public property_ `public List<RemoveAliasRequest> RemoveAliases { get; set; }` — List of aliases to remove
- L100 _public property_ `public List<AddRefRequest> AddRefs { get; set; }` — List of refs to add
- L105 _public property_ `public List<RemoveRefRequest> RemoveRefs { get; set; }` — List of refs to remove

#### class `EpicGames.Horde.Storage.AddAliasRequest`  
`public class AddAliasRequest`  
_public; L111-132_
- desc: Request object for adding an alias
- L116 _public property_ `public string Name { get; set; }` — Name of the alias
- L121 _public property_ `public int Rank { get; set; }` — Rank for the new alias
- L126 _public property_ `public byte[]? Data { get; set; }` — Data to store with the ref
- L131 _public property_ `public BlobLocator Target { get; set; }` — Path to the target blob

#### class `EpicGames.Horde.Storage.RemoveAliasRequest`  
`public class RemoveAliasRequest`  
_public; L137-148_
- desc: Request object for removing an alias
- L142 _public property_ `public string Name { get; set; }` — Name of the alias
- L147 _public property_ `public BlobLocator Target { get; set; }` — Path to the target blob

#### class `EpicGames.Horde.Storage.WriteRefRequest`  
`public class WriteRefRequest`  
_public; L153-186_
- desc: Request object for writing a ref
- L158 _public property_ `public IoHash Hash { get; set; }` — Hash of the target blob
- L163 _public property_ `public BlobLocator Target { get; set; }` — Path to the target blob
- L169 _public property_ `public BlobLocator? Blob { get; set; }` — attrs: `[Obsolete("Use Target instead")]` — Locator for the target blob
- L175 _public property_ `public int? ExportIdx { get; set; }` — attrs: `[Obsolete("Use ExportIdx instead")]` — Export index for the ref
- L180 _public property_ `public byte[] Data { get; set; }` — Inline data associated with the ref
- L185 _public property_ `public RefOptions? Options { get; set; }` — Options for the ref

#### class `EpicGames.Horde.Storage.AddRefRequest`  
`public class AddRefRequest : WriteRefRequest`  
_public; L191-197_
- inherits: `WriteRefRequest`
- desc: Request object for removing a ref
- L196 _public property_ `public RefName RefName { get; set; }` — Name of the ref

#### class `EpicGames.Horde.Storage.RemoveRefRequest`  
`public class RemoveRefRequest`  
_public; L202-208_
- desc: Request object for removing a ref
- L207 _public property_ `public RefName RefName { get; set; }` — Name of the ref

#### class `EpicGames.Horde.Storage.ReadRefResponse`  
`public class ReadRefResponse`  
_public; L213-234_
- desc: Response object for reading a ref
- L218 _public property_ `public IoHash Hash { get; set; }` — Hash of the target node
- L223 _public property_ `public BlobLocator Target { get; set; }` — The target blob
- L228 _public property_ `public string Link { get; set; }` — Link to information about the target node
- L233 _public property_ `public string BasePath { get; set; }` — Base path for this storage backend

### `Source/Programs/Shared/EpicGames.Horde/Storage/Workspace.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Storage.WorkspaceException`  
`public class WorkspaceException : Exception`  
_public; L24-31_
- inherits: `Exception`
- desc: Base exception type for workspace errors
- L29-30 _public ctor_ `public WorkspaceException(string message, Exception? innerException = null) : base(message, innerException)` — Constructor

#### class `EpicGames.Horde.Storage.Workspace`  
`public class Workspace`  
_public; L36-2413_
- desc: Provides functionality to extract and patch data in a local workspace
- L538 _private* field_ `readonly DirectoryReference _rootDir`
- L539 _private* field_ `readonly FileReference _stateFile`
- L540 _private* field_ `readonly DirectoryState _rootDirState`
- L541 _private* field_ `readonly DirectoryState _hordeDirState`
- L542 _private* field_ `readonly DirectoryState _cacheDirState`
- L543 _private* field_ `readonly List<LayerState> _customLayers = []`
- L544 _private* field_ `readonly Dictionary<IoHash, HashInfo> _hashes = ...`
- L544 _private* field_ `readonly Dictionary< _hashes = []`
- L545 _private* field_ `readonly ILogger _logger`
- L550 _public const_ `public const string HordeDirName = ".horde"` — Metadata directory name
- L552 _private* const_ `const string CacheDirName = "cache"`
- L553 _private* const_ `const string StateFileName = "contents.dat"`
- L558 _public property_ `public DirectoryReference RootDir => ...` — Root directory for the workspace
- L563 _public property_ `public IReadOnlyList<WorkspaceLayerId> CustomLayers => ...` — Layers current in this workspace
- L572-590 _private ctor_ `private Workspace(DirectoryReference rootDir, FileReference stateFile, IMemoryReader? reader, ILogger logger)` — Constructor
- L599-614 _public method_ `public static async Task<Workspace> CreateAsync(DirectoryReference rootDir, ILogger logger, CancellationToken cancellationToken = default)` — Create a new workspace instance in the given location. Opens the existing instance if it already contains workspace data.
- L623-628 _public method_ `public static async Task<Workspace> CreateOrOpenAsync(DirectoryReference rootDir, ILogger logger, CancellationToken cancellationToken = default)` — Create a new workspace instance in the given location. Opens the existing instance if it already contains workspace data.
- L637-653 _public method_ `public static async Task<Workspace?> TryOpenAsync(DirectoryReference currentDir, ILogger logger, CancellationToken cancellationToken = default)` — Attempts to open an existing workspace for the current directory.
- L662-673 _public method_ `public static async Task<Workspace?> TryFindAndOpenAsync(DirectoryReference currentDir, ILogger logger, CancellationToken cancellationToken = default)` — Attempts to open an existing workspace for the current directory.
- L679-692 _public method_ `public async Task SaveAsync(CancellationToken cancellationToken)` — Save the current state of the workspace
- L694-720 _private* method_ `void Read(IMemoryReader reader)`
- L722-743 _private* method_ `void Write(IMemoryWriter writer)`
- L745-775 _private* method_ `void RemoveUnusedHashInfoObjects()`
- L783-800 _public method_ `public void AddLayer(WorkspaceLayerId id)` — Add or update a layer with the given identifier
- L806-818 _public method_ `public void RemoveLayer(WorkspaceLayerId layerId)` — Removes a layer with the given identifier. Does not remove any files in the workspace.
- L821-833 _private* method_ `List<string> GetLayerNames(LayerFlags layers)`
- L836-850 _private* method_ `LayerFlags GetLayerFlag(WorkspaceLayerId id)`
- L862-879 _public method_ `public async Task AddAsync(WorkspaceLayerId layerId, List<FileInfo> files, CancellationToken cancellationToken = default)` — Adds files to the workspace
- L881-909 _private* method_ `async Task EnumerateFilesToAddAsync(LayerFlags layer, List<FileInfo> files, SemaphoreSlim semaphore, ChannelWriter<ChunkerSource> chunkerSourceWriter, CancellationToken cancellationToken)`
- L921-926 _public method_ `public async Task ForgetAsync(WorkspaceLayerId layerId, FileFilter filter, CancellationToken cancellationToken)` — Filters the contents of a layer
- L928-981 _private* method_ `void ForgetMatchingFiles(LayerFlags layer, DirectoryState dirState, string namePrefix, FileFilter filter)`
- L1030-1057 _public method_ `public async Task CleanAsync(FileFilter? filter = null, WorkspaceStatusFlags flags = WorkspaceStatusFlags.Default, CancellationToken cancellationToken = default)` — Prints the status of files in this workspace based on current filesystem metadata
- L1100-1128 _public method_ `public async Task SyncAsync(WorkspaceLayerId layerId, string? basePath, IBlobRef<DirectoryNode>? contents, ExtractOptions? options = null, WorkspaceSyncStats? stats = null, CancellationToken cancellationToken = default)` — Syncs a layer to the given contents at a given base path
- L1138-1164 _public method_ `public async Task SyncAsync(WorkspaceLayerId layerId, IBlobRef<DirectoryNode>? contents, ExtractOptions? options = null, WorkspaceSyncStats? stats = null, CancellationToken cancellationToken = default)` — Syncs a layer to the given contents
- L1168-1201 _private* method_ `async Task<DirectoryToSync> CreateTreeToSyncAsync(string name, IBlobRef<DirectoryNode>? dirNodeRef, CancellationToken cancellationToken)`
- L1206-1219 _private* method_ `static void CreateManifest(DirectoryState dirState, DirectoryToSync dirToSync, LayerFlags layer)`
- L1222-1307 _private* method_ `static void ScheduleRemoveActions(DirectoryState dirState, DirectoryToSync dirToSync, LayerFlags layer)`
- L1310-1336 _private* method_ `static void ScheduleMoveActions(DirectoryToSync dirToSync, LayerFlags layer)`
- L1338-1353 _private* method_ `static FileState? FindFileToMove(HashInfo hashInfo, LayerFlags layer)`
- L1356-1374 _private* method_ `static void ScheduleCopyActions(DirectoryToSync dirToSync)`
- L1377 _private* method_ `static FileState FindFileForCopy(HashInfo hashInfo)`
- L1383-1401 _private* method_ `static FileState? FindFileForCopy(HashInfo hashInfo, PendingFlags pendingMask, PendingFlags pendingFlag)`
- L1403-1429 _private* method_ `void ValidateManifest(DirectoryState dirState, LayerFlags layer)`
- L1433-1441 _private* method_ `static void CreateNewState(DirectoryToSync dirToSync, LayerFlags layer)`
- L1443-1453 _private* method_ `static void CreateDirectories(DirectoryReference dirRef, DirectoryToSync dirToSync)`
- L1455-1470 _private* method_ `void RemoveIntermediates(DirectoryState dirState)`
- L1472-1511 _private* method_ `void UpdateMetadata(DirectoryToSync dirToSync, DirectoryState dirState, LayerFlags layer)`
- L1513-1563 _private* method_ `void RemoveOldState(DirectoryState dirState, LayerFlags layer)`
- L1565-1597 _private* method_ `async Task MaterializeFilesAsync(DirectoryToSync dirToSync, LayerFlags layer, ExtractOptions options, WorkspaceSyncStats stats, CancellationToken cancellationToken)`
- L1599-1672 _private* method_ `async ValueTask FindChunkActionsAsync(string path, DirectoryToSync dirToSync, DirectoryState dirState, LayerFlags layer, ChannelWriter<ChunkCopyRequest> copyRequests, ChannelWriter<ChunkReadRequest> readRequests, WorkspaceSyncStats stats, CancellationToken cancellationToken)`
- L1676-1729 _private* method_ `async Task CopyChunksAsync(ChannelReader<ChunkCopyRequest> copyRequests, ChannelWriter<OutputChunk[]> outputRequests, CancellationToken cancellationToken)`
- L1738-1749 _private* method_ `SourceChunk? TryGetSourceChunk(IoHash hash)`
- L1751-1768 _private* method_ `static SourceChunk? TryGetSourceChunk(HashInfo hashInfo)`
- L1770-1787 _private* method_ `async Task<bool> TryCopyCachedDataAsync(HashInfo hashInfo, long offset, long length, Stream outputStream, CancellationToken cancellationToken)`
- L1789-1815 _private* method_ `async Task<bool> TryCopyChunkAsync(FileState file, long offset, long length, Stream outputStream, CancellationToken cancellationToken)`
- L1840-1963 _private* method_ `async Task ScanWorkspaceAsync(Visitor visitor, FileFilter filter, WorkspaceStatusFlags flags, ChannelWithRefCount<DirectoryState> channel, CancellationToken cancellationToken)`
- L1973-1987 _public method_ `public async Task StatusAsync(FileFilter? filter = null, WorkspaceStatusFlags flags = WorkspaceStatusFlags.Default, CancellationToken cancellationToken = default)` — Prints the status of files in this workspace based on current filesystem metadata
- L2044 _public method_ `public Task ReconcileAsync(CancellationToken cancellationToken = default)` — Updates the status of files in this workspace based on current filesystem metadata
- L2053-2077 _public method_ `public async Task TrackAsync(WorkspaceLayerId layerId, FileFilter? filter = null, CancellationToken cancellationToken = default)` — Updates the status of files in this workspace based on current filesystem metadata
- L2079 _private* method_ `static bool IsRelativeDir(string name)`
- L2084-2211 _private* method_ `async Task FindFilesToReconcileAsync(FileFilter filter, ChannelWithRefCount<DirectoryState> channel, LayerFlags layer, SemaphoreSlim semaphore, ContentChunker chunker, CancellationToken cancellationToken)`
- L2213-2245 _private* method_ `async ValueTask RegisterChunksAsync(ChunkerOutput output, LayerFlags layer, SemaphoreSlim stateSema, CancellationToken cancellationToken)`
- L2255-2258 _public method_ `public async Task VerifyAsync(CancellationToken cancellationToken = default)` — Checks that all files within the workspace have the correct hash
- L2260-2285 _private* method_ `async Task VerifyAsync(DirectoryState dirState, CancellationToken cancellationToken)`
- L2289-2299 _private* method_ `void AddDirToHashLookup(DirectoryState dirState)`
- L2301-2310 _private* method_ `HashInfo FindOrAddHashInfo(IoHash hash, long length)`
- L2312-2317 _private* method_ `HashInfo AddFileToHashLookup(FileState file)`
- L2319-2326 _private* method_ `void RemoveFileFromHashLookup(FileState file)`
- L2328-2338 _private* method_ `void RemoveDirectoryFromHashLookup(DirectoryState dirState)`
- L2342-2348 _private* method_ `void DeleteDirectory(DirectoryState dirState)`
- L2350-2355 _private* method_ `DirectoryReference GetDirectoryReference(DirectoryState dirState)`
- L2361-2376 _private* method_ `void MoveFileToCache(FileState fileState)`
- L2378-2388 _private* method_ `void MoveFile(FileState fileState, DirectoryState targetDirState, string targetName, LayerFlags targetLayers)`
- L2390-2398 _private* method_ `void DeleteFile(FileState fileState)`
- L2400-2403 _private* method_ `FileInfo GetFileInfo(FileState fileState)`
- L2405-2410 _private* method_ `FileReference GetFileReference(FileState fileState)`

#### enum `EpicGames.Horde.Storage.Workspace.LayerFlags`  
`enum LayerFlags : ulong`  
_private*; L41-61_
- attrs: `[Flags]`
- inherits: `ulong`
- L44 _public* enumerator_ `Cache = 1`
- L47 _public* enumerator_ `Pending = 2`
- L50 _public* enumerator_ `Default = 4`
- L53 _public* enumerator_ `Custom1 = Default << 1`
- L54 _public* enumerator_ `Custom2 = Default << 2`
- L55 _public* enumerator_ `Custom3 = Default << 3`
- L56 _public* enumerator_ `Custom4 = Default << 4`
- L57 _public* enumerator_ `Custom5 = Default << 5`
- L58 _public* enumerator_ `Custom6 = Default << 6`
- L59 _public* enumerator_ `Custom7 = Default << 7`
- L60 _public* enumerator_ `Custom8 = Default << 8`

#### enum `EpicGames.Horde.Storage.Workspace.PendingFlags`  
`enum PendingFlags`  
_private*; L65-84_
- attrs: `[Flags]`
- L68 _public* enumerator_ `None = 0`
- L71 _public* enumerator_ `RemoveFromLayer = 2`
- L74 _public* enumerator_ `RemoveFromDisk = 4`
- L77 _public* enumerator_ `Move = 8`
- L80 _public* enumerator_ `Copy = 16`
- L83 _public* enumerator_ `ForceRenameOrRemove = 32`

#### class `EpicGames.Horde.Storage.Workspace.LayerState`  
`class LayerState`  
_private*; L88-110_
- attrs: `[DebuggerDisplay("{Id}")]`
- L90 _public property_ `public WorkspaceLayerId Id { get; }`
- L91 _public property_ `public LayerFlags Flag { get; }`
- L93-97 _public ctor_ `public LayerState(WorkspaceLayerId id, LayerFlags flag)`
- L99-103 _public ctor_ `public LayerState(IMemoryReader reader)`
- L105-109 _public method_ `public void Write(IMemoryWriter writer)`

#### class `EpicGames.Horde.Storage.Workspace.DirectoryState`  
`class DirectoryState`  
_private*; L114-391_
- attrs: `[DebuggerDisplay("{GetPath()}")]`
- L148 _public property_ `public DirectoryState? Parent { get; set; }`
- L149 _public property_ `public string Name { get; }`
- L150 _public property_ `public IReadOnlyCollection<DirectoryState> Directories => ...`
- L151 _public property_ `public IReadOnlyCollection<FileState> Files => ...`
- L152 _public property_ `public LayerFlags Layers { get; set; }`
- L153 _public property_ `public PendingFlags Pending => ...`
- L155 _private* field_ `PendingFlags _pendingFlags`
- L157 _private* field_ `readonly Dictionary<string, DirectoryState> _directories`
- L157 _private* field_ `readonly Dictionary< _directories`
- L158 _private* field_ `readonly Dictionary<string, FileState> _files`
- L158 _private* field_ `readonly Dictionary< _files`
- L160-167 _public ctor_ `public DirectoryState(DirectoryState? parent, string name)`
- L169-198 _public ctor_ `public DirectoryState(DirectoryState? parent, IMemoryReader reader)`
- L200-222 _public method_ `public void Write(IMemoryWriter writer)`
- L224-238 _public method_ `public void SetPendingAction(PendingFlags pending)`
- L240-257 _public method_ `public void ClearPendingActions()`
- L259-272 _public method_ `public void MarkAsDirty()`
- L274-279 _public method_ `public FileState AddFile(string name, IoHash hash, LayerFlags layers)`
- L281-291 _private* method_ `void AddFileInternal(FileState fileState)`
- L293 _public method_ `public bool ContainsFile(string name)`
- L296 _public method_ `public bool TryGetFileCaseSensitive(string name, [NotNullWhen(true)] out FileState? fileState)`
- L299 _public method_ `public bool TryGetFileCaseInsensitive(string name, [NotNullWhen(true)] out FileState? fileState)`
- L302-306 _public method_ `public DirectoryState? FindDirectory(string name)`
- L308 _public method_ `public bool TryGetDirectoryCaseInsensitive(string name, [NotNullWhen(true)] out DirectoryState? directoryState)`
- L311-323 _public method_ `public bool TryGetDirectoryCaseSensitive(string name, [NotNullWhen(true)] out DirectoryState? directoryState)`
- L325-330 _public method_ `public DirectoryState AddDirectory(string name, LayerFlags layer)`
- L332-344 _public method_ `public DirectoryState FindOrAddDirectory(string name, LayerFlags layer)`
- L346-350 _public method_ `public void Unlink()`
- L352-357 _public method_ `public string GetPath()`
- L359-365 _public method_ `public string GetChildPath(string name)`
- L367-371 _public method_ `public void AppendPath(StringBuilder builder)`
- L373-383 _private* method_ `static void AppendChildPath(StringBuilder builder, string name)`
- L385-390 _public method_ `public DirectoryReference GetDirectoryReference(DirectoryReference baseDir)`

#### class `EpicGames.Horde.Storage.Workspace.DirectoryState.FileStateImpl`  
`sealed class FileStateImpl : FileState`  
_private*; L117-146_
- inherits: `FileState`
- L119-121 _public ctor_ `public FileStateImpl(DirectoryState parent, string name, IoHash hash, LayerFlags layers) : base(parent, name, hash, layers)`
- L123-125 _public ctor_ `public FileStateImpl(DirectoryState parent, IMemoryReader reader) : base(parent, reader)`
- L127-136 _public method_ `public override void MoveTo(DirectoryState newParent, string newName, LayerFlags newLayers)`
- L138-145 _public method_ `public override void Unlink()`

#### class `EpicGames.Horde.Storage.Workspace.FileState`  
`abstract class FileState`  
_private*; L395-489_
- attrs: `[DebuggerDisplay("{GetPath()}")]`
- L397 _public property_ `public DirectoryState Parent { get; set; }`
- L398 _public property_ `public string Name { get; set; }`
- L399 _public property_ `public long Length { get; set; }`
- L400 _public property_ `public long LastModifiedTimeUtc { get; set; }`
- L401 _public property_ `public IoHash Hash { get; }`
- L402 _public property_ `public LayerFlags Layers { get; set; }`
- L403 _public property_ `public PendingFlags Pending { get; set; }`
- L405-411 _protected ctor_ `protected FileState(DirectoryState parent, string name, IoHash hash, LayerFlags layers)`
- L413-426 _public ctor_ `public FileState(DirectoryState parent, IMemoryReader reader)`
- L428-441 _public method_ `public void Write(IMemoryWriter writer)`
- L443-447 _public method_ `public void SetPendingAction(PendingFlags pending)`
- L449-453 _public method_ `public void MarkAsDirty()`
- L455 _public method_ `public bool InLayer(LayerFlags layers)`
- L458 _public method_ `public abstract void MoveTo(DirectoryState newParent, string newName, LayerFlags newLayers)`
- L460 _public method_ `public abstract void Unlink()`
- L462 _public method_ `public bool IsModified(FileInfo fileInfo)`
- L465-469 _public method_ `public void Update(FileInfo fileInfo)`
- L471-476 _public method_ `public string GetPath()`
- L478-488 _public method_ `public void AppendPath(StringBuilder builder)`

#### class `EpicGames.Horde.Storage.Workspace.HashInfo`  
`class HashInfo`  
_private*; L493-516_
- attrs: `[DebuggerDisplay("{Hash}")]`
- L495 _public property_ `public int Index { get; set; }`
- L497 _public property_ `public IoHash Hash { get; }`
- L498 _public property_ `public long Length { get; }`
- L500 _public property_ `public List<FileState> Files { get; }`
- L501 _public property_ `public List<ChunkInfo> Chunks { get; }`
- L503-507 _public ctor_ `public HashInfo(IoHash hash, long length)`
- L509-515 _public method_ `public void AddChunk(ChunkInfo chunk)`

#### record `EpicGames.Horde.Storage.Workspace.ChunkInfo`  
`record class ChunkInfo(HashInfo WithinHashInfo, long Offset, long Length)`  
_private*; L520-536_
- attrs: `[DebuggerDisplay("{Offset}+{Length}->{WithinHashInfo}")]`
- L522-528 _public method_ `public static ChunkInfo Read(IMemoryReader reader, HashInfo[] hashes)`
- L530-535 _public method_ `public void Write(IMemoryWriter writer)`

#### class `EpicGames.Horde.Storage.Workspace.CleanVisitor`  
`class CleanVisitor(ILogger logger) : Visitor`  
_private*; L987-1022_
- L989 _public property_ `public ConcurrentBag<FileState> RemoveFiles { get; }`
- L990 _public property_ `public ConcurrentBag<DirectoryState> RemoveDirs { get; }`
- L992-996 _public method_ `public override void FileAdded(string path, DirectoryState parentDir, FileInfo fileInfo)`
- L998-1003 _public method_ `public override void FileModified(string path, FileState fileState, FileInfo fileInfo)`
- L1005-1009 _public method_ `public override void FileRemoved(string path, FileState fileState)`
- L1011-1015 _public method_ `public override void DirectoryAdded(string path, DirectoryState parentDir, DirectoryInfo subDirInfo)`
- L1017-1021 _public method_ `public override void DirectoryRemoved(string path, DirectoryState dirState)`

#### class `EpicGames.Horde.Storage.Workspace.DirectoryToSync`  
`class DirectoryToSync(string name)`  
_private*; L1063-1075_
- L1065 _public property_ `public string Name { get; }`
- L1066 _public property_ `public DirectoryState? State { get; set; }`
- L1067 _public property_ `public Dictionary<string, DirectoryToSync> Directories { get; }`
- L1068 _public property_ `public Dictionary<string, FileToSync> Files { get; }`
- L1070 _public method_ `public DirectoryToSync? FindDirectoryExactCase(string name)`
- L1073 _public method_ `public FileToSync? FindFileExactCase(string name)`

#### class `EpicGames.Horde.Storage.Workspace.FileToSync`  
`class FileToSync(FileEntry entry)`  
_private*; L1077-1089_
- L1079 _public property_ `public FileEntry Entry => ...`
- L1080 _public property_ `public string Name => ...`
- L1081 _public property_ `public FileState? State { get; set; }`
- L1083 _public property_ `public HashInfo? CopyFrom { get; set; }`
- L1084 _public property_ `public FileState? MoveFrom { get; set; }`
- L1085 _public property_ `public List<LeafChunkedDataNodeRef>? Chunks { get; set; }`
- L1086 _public property_ `public OutputFile? OutputFile { get; set; }`
- L1088 _public property_ `public bool Complete { get; set; }`

#### record `EpicGames.Horde.Storage.Workspace.ChunkCopyRequest`  
`record class ChunkCopyRequest(OutputFile OutputFile, long Offset, SourceChunk SourceChunk)`  
_private*; L1674-1674_

#### record `EpicGames.Horde.Storage.Workspace.SourceChunk`  
`record class SourceChunk(FileState File, long Offset, long Length, IoHash Hash)`  
_private*; L1731-1736_
- L1734 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.Workspace.Visitor`  
`class Visitor`  
_private*; L1819-1838_
- L1821-1822 _public method_ `public virtual void DirectoryAdded(string path, DirectoryState parentDir, DirectoryInfo subDirInfo)`
- L1824-1825 _public method_ `public virtual void DirectoryRemoved(string path, DirectoryState dirState)`
- L1827-1828 _public method_ `public virtual void FileAdded(string path, DirectoryState parentDir, FileInfo fileInfo)`
- L1830-1831 _public method_ `public virtual void FileModified(string path, FileState fileState, FileInfo fileInfo)`
- L1833-1834 _public method_ `public virtual void FileUnmodified(string path, FileState fileState, FileInfo fileInfo)`
- L1836-1837 _public method_ `public virtual void FileRemoved(string path, FileState fileState)`

#### class `EpicGames.Horde.Storage.Workspace.StatusVisitor`  
`class StatusVisitor : Visitor`  
_private*; L1989-2034_
- inherits: `Visitor`
- L1991 _public property_ `public bool AnyChanges { get; set; }`
- L1993 _private* field_ `readonly Lock _lockObject = new()`
- L1995 _public method_ `public override void DirectoryAdded(string path, DirectoryState parentDir, DirectoryInfo subDirInfo)`
- L1998 _public method_ `public override void DirectoryRemoved(string path, DirectoryState dirState)`
- L2001 _public method_ `public override void FileAdded(string path, DirectoryState parentDir, FileInfo fileInfo)`
- L2004 _public method_ `public override void FileModified(string path, FileState fileState, FileInfo fileInfo)`
- L2007 _public method_ `public override void FileUnmodified(string path, FileState fileState, FileInfo fileInfo)`
- L2010 _public method_ `public override void FileRemoved(string path, FileState fileState)`
- L2013 _private* method_ `static string FormatPath(string path)`
- L2016-2033 _private* method_ `void WriteLine(string text, ConsoleColor? color)`

#### record `EpicGames.Horde.Storage.Workspace.FileToAdd`  
`record class FileToAdd(DirectoryState ParentDir, FileInfo FileInfo)`  
_private*; L2082-2082_

#### enum `EpicGames.Horde.Storage.WorkspaceStatusFlags`  
`public enum WorkspaceStatusFlags`  
_public; L2419-2460_
- attrs: `[Flags]`
- desc: Flags for showing modified flags in a workspace
- L2424 _public* enumerator_ `None = 0` — Include nothing
- L2429 _public* enumerator_ `DirectoryAdded = 1` — Directories which have been added
- L2434 _public* enumerator_ `DirectoryRemoved = 2` — Directories which have been removed
- L2439 _public* enumerator_ `FileAdded = 4` — Files which have been added
- L2444 _public* enumerator_ `FileRemoved = 8` — Files which have been removed
- L2449 _public* enumerator_ `FileModified = 16` — Files which have been modified
- L2454 _public* enumerator_ `FileUnmodified = 32` — Files which have not been modified
- L2459 _public* enumerator_ `Default = DirectoryAdded | DirectoryRemoved | FileAdded | FileRemoved | FileModified` — Default flags for status calls

#### class `EpicGames.Horde.Storage.WorkspaceSyncStats`  
`public class WorkspaceSyncStats`  
_public; L2465-2486_
- desc: Stats for a sync
- L2470 _public property_ `public int NumFilesKept { get; set; }` — Number of identical files that were kept
- L2475 _public property_ `public int NumFilesMoved { get; set; }` — Number of files that were moved during a sync operation
- L2480 _public property_ `public long NumBytesReused { get; set; }` — Number of bytes that were copied from elsewhere in the tree
- L2485 _public property_ `public long NumBytesDownloaded { get; set; }` — Number of bytes that were downloaded

### `Source/Programs/Shared/EpicGames.Horde/Storage/WorkspaceLayerId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Storage.WorkspaceLayerId`  
`public readonly record struct WorkspaceLayerId(StringId Id)`  
_public; L16-50_
- attrs: `[LogValueType] [TypeConverter(typeof(StringIdTypeConverter<WorkspaceLayerId, WorkspaceLayerIdConverter>))] [BinaryIdConverter(typeof(WorkspaceLayerIdConverter))]`
- desc: Identifier for a workspace layer
- L21 _public property_ `public static WorkspaceLayerId Default { get; }` — Name of the default layer
- L26-28 _public ctor_ `public WorkspaceLayerId(string id) : this(new StringId(id))` — Constructor
- L33-46 _public method_ `public static bool TryParse(string text, out WorkspaceLayerId id, [NotNullWhen(false)] out string? errorMessage)` — Parse an identifier
- L49 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Storage.WorkspaceLayerIdConverter`  
`class WorkspaceLayerIdConverter : StringIdConverter<WorkspaceLayerId>`  
_internal*; L55-62_
- inherits: `StringIdConverter<WorkspaceLayerId>`
- desc: Converter class to and from ObjectId values
- L58 _public method_ `public override WorkspaceLayerId FromStringId(StringId id)` — (inheritdoc)
- L61 _public method_ `public override StringId ToStringId(WorkspaceLayerId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Streams/IStream.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Streams.InvalidStreamException`  
`public class InvalidStreamException : Exception`  
_public; L22-38_
- inherits: `Exception`
- desc: Exception thrown when stream validation fails
- L25-27 _public ctor_ `public InvalidStreamException()` — (inheritdoc)
- L30-32 _public ctor_ `public InvalidStreamException(string message) : base(message)` — (inheritdoc)
- L35-37 _public ctor_ `public InvalidStreamException(string message, Exception innerEx) : base(message, innerEx)` — (inheritdoc)

#### interface `EpicGames.Horde.Streams.IStream`  
`public interface IStream`  
_public; L43-176_
- desc: Information about a stream
- L48 _public* property_ `StreamId Id { get; }` — Name of the stream.
- L53 _public* property_ `ProjectId ProjectId { get; }` — Project that this stream belongs to
- L58 _public* property_ `string Name { get; }` — Name of the stream
- L63 _public* property_ `string? ConfigPath { get; }` — Path to the config file for this stream
- L68 _public* property_ `string ConfigRevision { get; }` — Current revision of the config file
- L73 _public* property_ `int Order { get; }` — Order for this stream on the dashboard
- L78 _public* property_ `string? NotificationChannel { get; }` — Notification channel for all jobs in this stream
- L83 _public* property_ `string? NotificationChannelFilter { get; }` — Notification channel filter for this template. Can be Success, Failure, or Warnings.
- L88 _public* property_ `string? TriageChannel { get; }` — Channel to post issue triage notifications
- L93 _public* property_ `IReadOnlyList<IStreamTab> Tabs { get; }` — Tabs for this stream on the dashboard
- L98 _public* property_ `IReadOnlyDictionary<string, IAgentType> AgentTypes { get; }` — Agent types configured for this stream
- L103 _public* property_ `IReadOnlyDictionary<string, IWorkspaceType> WorkspaceTypes { get; }` — Workspace types configured for this stream
- L108 _public* property_ `IReadOnlyDictionary<TemplateId, ITemplateRef> Templates { get; }` — List of templates available for this stream
- L113 _public* property_ `IReadOnlyList<IWorkflow> Workflows { get; }` — Workflows configured for this stream
- L119 _public* property_ `IReadOnlyList<IStreamAlias> Aliases { get; }` — Stream aliases configured for this stream. Each alias provides a named subset of the stream's templates.
- L124 _public* property_ `IDefaultPreflight? DefaultPreflight { get; }` — Default settings for preflights against this stream
- L129 _public* property_ `DateTime? PausedUntil { get; }` — Stream is paused for builds until specified time
- L134 _public* property_ `string? PauseComment { get; }` — Comment/reason for why the stream was paused
- L139 _public* property_ `ICommitCollection Commits { get; }` — Commits for this stream
- L146 _public* method_ `Task<IStream?> RefreshAsync(CancellationToken cancellationToken = default)` — Get the latest stream state
- L155 _public* method_ `Task<IStream?> TryUpdatePauseStateAsync(DateTime? newPausedUntil, string? newPauseComment, CancellationToken cancellationToken = default)` — Updates user-facing properties for an existing stream
- L166 _public* method_ `Task<IStream?> TryUpdateScheduleTriggerAsync(TemplateId templateRefId, DateTime? lastTriggerTimeUtc, CommitIdWithOrder? lastTriggerCommitId, List<JobId> newActiveJobs, CancellationToken cancellationToken = default)` — Attempts to update the last trigger time for a schedule
- L175 _public* method_ `Task<IStream?> TryUpdateTemplateRefAsync(TemplateId templateRefId, List<UpdateStepStateRequest>? stepStates = null, CancellationToken cancellationToken = default)` — Attempts to update a stream template ref

#### enum `EpicGames.Horde.Streams.TabStyle`  
`public enum TabStyle`  
_public; L181-192_
- desc: Style for rendering a tab
- L186 _public* enumerator_ `Normal` — Regular job list
- L191 _public* enumerator_ `Compact` — Omit job names, show condensed view

#### interface `EpicGames.Horde.Streams.IStreamTab`  
`public interface IStreamTab`  
_public; L197-238_
- desc: Information about a page to display in the dashboard for a stream
- L202 _public* property_ `string Title { get; }` — Title of this page
- L207 _public* property_ `string Type { get; }` — Type of this tab
- L212 _public* property_ `TabStyle Style { get; }` — Presentation style for this page
- L217 _public* property_ `bool ShowNames { get; }` — Whether to show job names on this page
- L222 _public* property_ `bool? ShowPreflights { get; }` — Whether to show all user preflights
- L227 _public* property_ `IReadOnlyList<string>? JobNames { get; }` — Names of jobs to include on this page. If there is only one name specified, the name column does not need to be displayed.
- L232 _public* property_ `IReadOnlyList<TemplateId>? Templates { get; }` — List of job template names to show on this page.
- L237 _public* property_ `IReadOnlyList<IStreamTabColumn>? Columns { get; }` — Columns to display for different types of aggregates

#### enum `EpicGames.Horde.Streams.TabColumnType`  
`public enum TabColumnType`  
_public; L243-254_
- desc: Type of a column in a jobs tab
- L248 _public* enumerator_ `Labels` — Contains labels
- L253 _public* enumerator_ `Parameter` — Contains parameters

#### interface `EpicGames.Horde.Streams.IStreamTabColumn`  
`public interface IStreamTabColumn`  
_public; L259-285_
- desc: Describes a column to display on the jobs page
- L264 _public* property_ `TabColumnType Type { get; }` — The type of column
- L269 _public* property_ `string Heading { get; }` — Heading for this column
- L274 _public* property_ `string? Category { get; }` — Category of aggregates to display in this column. If null, includes any aggregate not matched by another column.
- L279 _public* property_ `string? Parameter { get; }` — Parameter to show in this column
- L284 _public* property_ `int? RelativeWidth { get; }` — Relative width of this column.

#### interface `EpicGames.Horde.Streams.IAgentType`  
`public interface IAgentType`  
_public; L290-311_
- desc: Mapping from a BuildGraph agent type to a set of machines on the farm
- L295 _public* property_ `PoolId Pool { get; }` — Pool of agents to use for this agent type
- L300 _public* property_ `string? Workspace { get; }` — Name of the workspace to sync
- L305 _public* property_ `string? TempStorageDir { get; }` — Path to the temporary storage dir
- L310 _public* property_ `IReadOnlyDictionary<string, string>? Environment { get; }` — Environment variables to be set when executing the job

#### interface `EpicGames.Horde.Streams.IWorkspaceType`  
`public interface IWorkspaceType`  
_public; L316-379_
- desc: Information about a workspace type
- L321 _public* property_ `string? Cluster { get; }` — Name of the Perforce server cluster to use
- L326 _public* property_ `string? ServerAndPort { get; }` — The Perforce server and port (eg. perforce:1666)
- L331 _public* property_ `string? UserName { get; }` — User to log into Perforce with (defaults to buildmachine)
- L336 _public* property_ `string? Identifier { get; }` — Identifier to distinguish this workspace from other workspaces. Defaults to the workspace type name.
- L341 _public* property_ `string? Stream { get; }` — Override for the stream to sync
- L346 _public* property_ `IReadOnlyList<string>? View { get; }` — Custom view for the workspace
- L351 _public* property_ `bool? Incremental { get; }` — Whether to use an incrementally synced workspace
- L356 _public* property_ `bool? UseAutoSdk { get; }` — Whether to use the AutoSDK
- L361 _public* property_ `IReadOnlyList<string>? AutoSdkView { get; }` — View for the AutoSDK paths to sync. If null, the whole thing will be synced.
- L366 _public* property_ `string? Method { get; }` — Method to use when syncing/materializing data from Perforce
- L372 _public* property_ `long? MinScratchSpace { get; }` — Minimum disk space that must be available *after* syncing this workspace (in megabytes) If not available, the job will be aborted.
- L378 _public* property_ `long? ConformDiskFreeSpace { get; }` — Threshold for when to trigger an automatic conform of agent. Measured in megabytes free on disk. Set to null or 0 to disable.

#### interface `EpicGames.Horde.Streams.IDefaultPreflight`  
`public interface IDefaultPreflight`  
_public; L384-395_
- desc: Specifies defaults for running a preflight
- L389 _public* property_ `TemplateId? TemplateId { get; }` — The template id to query
- L394 _public* property_ `IChangeQuery? Change { get; }` — Query for the change to use

#### interface `EpicGames.Horde.Streams.IStreamAlias`  
`public interface IStreamAlias`  
_public; L400-412_
- desc: Represents a named alias for a stream with a subset of its templates
- L405 _public* property_ `string Name { get; }` — The unique name/identifier for this alias
- L411 _public* property_ `IReadOnlyList<TemplateId> Templates { get; }` — The subset of template IDs available through this alias. These must be a subset of the enclosing IStream's Templates.

#### interface `EpicGames.Horde.Streams.ITemplateRef`  
`public interface ITemplateRef`  
_public; L417-468_
- desc: Job template in a stream
- L422 _public* property_ `TemplateId Id { get; }` — The template id
- L427 _public* property_ `bool ShowUgsBadges { get; }` — Whether to show badges in UGS for these jobs
- L432 _public* property_ `bool ShowUgsAlerts { get; }` — Whether to show alerts in UGS for these jobs
- L437 _public* property_ `string? NotificationChannel { get; }` — Notification channel for this template. Overrides the stream channel if set.
- L442 _public* property_ `string? NotificationChannelFilter { get; }` — Notification channel filter for this template. Can be a combination of "Success", "Failure" and "Warnings" separated by pipe characters.
- L447 _public* property_ `string? TriageChannel { get; }` — Triage channel for this template. Overrides the stream channel if set.
- L452 _public* property_ `ISchedule? Schedule { get; }` — List of schedules for this template
- L457 _public* property_ `IReadOnlyList<IChainedJobTemplate>? ChainedJobs { get; }` — List of chained job triggers
- L462 _public* property_ `IReadOnlyList<ITemplateStep> StepStates { get; }` — List of template step states
- L467 _public* property_ `IReadOnlyList<IChangeQuery>? DefaultChange { get; }` — Default change to use for this job

#### interface `EpicGames.Horde.Streams.IChainedJobTemplate`  
`public interface IChainedJobTemplate`  
_public; L473-489_
- desc: Trigger for another template
- L478 _public* property_ `string Trigger { get; }` — Name of the target that needs to complete before starting the other template
- L483 _public* property_ `TemplateId TemplateId { get; }` — Id of the template to trigger
- L488 _public* property_ `bool UseDefaultChangeForTemplate { get; }` — Whether to use the default change for the template rather than the change for the parent job.

#### interface `EpicGames.Horde.Streams.ITemplateStep`  
`public interface ITemplateStep`  
_public; L494-510_
- desc: Information about a paused template step
- L499 _public* property_ `string Name { get; }` — Name of the step
- L504 _public* property_ `UserId PausedByUserId { get; }` — User who paused the step
- L509 _public* property_ `DateTime PauseTimeUtc { get; }` — The UTC time when the step was paused

#### class `EpicGames.Horde.Streams.StreamExtensions`  
`public static class StreamExtensions`  
_public; L515-596_
- desc: Extension methods for streams
- L525-536 _public method_ `public static async Task<IStream?> TryUpdatePauseStateAsync(this IStream? stream, DateTime? newPausedUntil = null, string? newPauseComment = null, CancellationToken cancellationToken = default)` — Updates an existing stream
- L549-584 _public method_ `public static async Task<IStream?> TryUpdateScheduleTriggerAsync(this IStream stream, TemplateId templateRefId, DateTime? lastTriggerTimeUtc = null, CommitIdWithOrder? lastTriggerCommitId = null, List<JobId>? addJobs = null, List<JobId>? removeJobs = null, CancellationToken cancellationToken = default)` — Attempts to update the last trigger time for a schedule
- L592-595 _public method_ `public static bool IsPaused(this IStream stream, DateTime currentTime)` — Check if stream is paused for new builds

### `Source/Programs/Shared/EpicGames.Horde/Streams/IStreamCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Streams.IStreamCollection`  
`public interface IStreamCollection`  
_public; L12-29_
- desc: Collection of stream documents
- L20 _public* method_ `Task<IStream?> GetAsync(StreamId id, CancellationToken cancellationToken = default)` — Gets a stream by ID
- L28 _public* method_ `Task<IReadOnlyList<IStream>> FindAsync(IReadOnlyList<StreamId>? ids = null, CancellationToken cancellationToken = default)` — Gets a stream by ID

### `Source/Programs/Shared/EpicGames.Horde/Streams/StreamId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Streams.StreamId`  
`public readonly record struct StreamId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<StreamId, StreamIdConverter>))] [StringIdConverter(typeof(StreamIdConverter))] [CbConverter(typeof(StringIdCbConverter<StreamId, StreamIdConverter>))]`
- desc: Identifier for a stream
- L23-25 _public ctor_ `public StreamId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Streams.StreamIdConverter`  
`public class StreamIdConverter : StringIdConverter<StreamId>`  
_public; L37-44_
- inherits: `StringIdConverter<StreamId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override StreamId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(StreamId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Streams/StreamMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Streams.GetStreamResponse`  
`public class GetStreamResponse`  
_public; L23-147_
- desc: Response describing a stream
- L28 _public property_ `public StreamId Id { get; set; }` — Unique id of the stream
- L33 _public property_ `public ProjectId ProjectId { get; set; }` — Unique id of the project containing this stream
- L38 _public property_ `public string Name { get; set; }` — Name of the stream
- L43 _public property_ `public string ConfigPath { get; set; }` — The config file path on the server
- L48 _public property_ `public string ConfigRevision { get; set; }` — Revision of the config file
- L53 _public property_ `public int Order { get; set; }` — Order to display in the list
- L58 _public property_ `public string? NotificationChannel { get; set; }` — Notification channel for all jobs in this stream
- L63 _public property_ `public string? NotificationChannelFilter { get; set; }` — Notification channel filter for this template. Can be a combination of "Success", "Failure" and "Warnings" separated by pipe characters.
- L68 _public property_ `public string? TriageChannel { get; set; }` — Channel to post issue triage notifications
- L73 _public property_ `public string? DefaultPreflightTemplate { get; set; }` — Default template for running preflights
- L78 _public property_ `public DefaultPreflightMessage? DefaultPreflight { get; set; }` — Default template to use for preflights
- L83 _public property_ `public List<GetStreamTabResponse> Tabs { get; set; }` — List of tabs to display for this stream
- L88 _public property_ `public Dictionary<string, GetAgentTypeResponse> AgentTypes { get; set; }` — Map of agent name to type
- L93 _public property_ `public Dictionary<string, GetWorkspaceTypeResponse>? WorkspaceTypes { get; set; }` — Map of workspace name to type
- L98 _public property_ `public List<GetTemplateRefResponse> Templates { get; set; }` — Templates for jobs in this stream
- L103 _public property_ `public DateTime? PausedUntil { get; set; }` — Stream paused for new builds until this date
- L108 _public property_ `public string? PauseComment { get; set; }` — Reason for stream being paused
- L113 _public property_ `public List<GetWorkflowResponse> Workflows { get; set; }` — Workflows for this stream
- L118 _public property_ `public List<GetStreamAliasResponse> Aliases { get; set; }` — Stream aliases for this stream
- L125-146 _public ctor_ `public GetStreamResponse(IStream stream, List<GetTemplateRefResponse> templates)` — Constructor

#### class `EpicGames.Horde.Streams.GetStreamAliasResponse`  
`public class GetStreamAliasResponse : IStreamAlias`  
_public; L152-179_
- inherits: `IStreamAlias`
- desc: Response describing a stream alias
- L155 _public property_ `public string Name { get; set; }` — (inheritdoc)
- L158 _public property_ `public List<TemplateId> Templates { get; set; }` — (inheritdoc)
- L159 _private* property_ `IReadOnlyList<TemplateId> IStreamAlias.Templates => ...`
- L164-168 _public ctor_ `public GetStreamAliasResponse()` — Default constructor for serialization
- L174-178 _public ctor_ `public GetStreamAliasResponse(IStreamAlias alias)` — Constructor

#### class `EpicGames.Horde.Streams.DefaultPreflightMessage`  
`public class DefaultPreflightMessage : IDefaultPreflight`  
_public; L184-207_
- inherits: `IDefaultPreflight`
- desc: Information about the default preflight to run
- L187 _public property_ `public TemplateId? TemplateId { get; set; }` — (inheritdoc)
- L190 _public property_ `public ChangeQueryMessage? Change { get; set; }` — (inheritdoc)
- L191 _private* property_ `IChangeQuery? IDefaultPreflight.Change => ...`
- L196-197 _public ctor_ `public DefaultPreflightMessage()` — Constructor
- L202-206 _public ctor_ `public DefaultPreflightMessage(IDefaultPreflight other)` — Constructor

#### class `EpicGames.Horde.Streams.GetStreamTabResponse`  
`public class GetStreamTabResponse : IStreamTab`  
_public; L212-264_
- inherits: `IStreamTab`
- desc: Information about a page to display in the dashboard for a stream
- L215 _public property_ `public string Title { get; set; }` — (inheritdoc)
- L218 _public property_ `public string Type { get; set; }` — (inheritdoc)
- L221 _public property_ `public TabStyle Style { get; set; }` — (inheritdoc)
- L224 _public property_ `public bool ShowNames { get; set; }` — (inheritdoc)
- L227 _public property_ `public bool? ShowPreflights { get; set; }` — (inheritdoc)
- L230 _public property_ `public List<string>? JobNames { get; set; }` — (inheritdoc)
- L231 _private* property_ `IReadOnlyList<string>? IStreamTab.JobNames => ...`
- L234 _public property_ `public List<TemplateId>? Templates { get; set; }` — (inheritdoc)
- L235 _private* property_ `IReadOnlyList<TemplateId>? IStreamTab.Templates => ...`
- L238 _public property_ `public List<GetStreamTabColumnResponse>? Columns { get; set; }` — (inheritdoc)
- L239 _private* property_ `IReadOnlyList<IStreamTabColumn>? IStreamTab.Columns => ...`
- L244-248 _public ctor_ `public GetStreamTabResponse()` — Constructor
- L253-263 _public ctor_ `public GetStreamTabResponse(IStreamTab other)` — Constructor

#### class `EpicGames.Horde.Streams.GetStreamTabColumnResponse`  
`public class GetStreamTabColumnResponse : IStreamTabColumn`  
_public; L269-305_
- inherits: `IStreamTabColumn`
- desc: Describes a column to display on the jobs page
- L272 _public property_ `public TabColumnType Type { get; set; }` — (inheritdoc)
- L275 _public property_ `public string Heading { get; set; }` — (inheritdoc)
- L278 _public property_ `public string? Category { get; set; }` — (inheritdoc)
- L281 _public property_ `public string? Parameter { get; set; }` — (inheritdoc)
- L284 _public property_ `public int? RelativeWidth { get; set; }` — (inheritdoc)
- L289-292 _public ctor_ `public GetStreamTabColumnResponse()` — Default constructor
- L297-304 _public ctor_ `public GetStreamTabColumnResponse(IStreamTabColumn other)` — Constructor

#### class `EpicGames.Horde.Streams.GetAgentTypeResponse`  
`public class GetAgentTypeResponse`  
_public; L310-348_
- desc: Mapping from a BuildGraph agent type to a set of machines on the farm
- L315 _public property_ `public PoolId Pool { get; set; }` — Pool of agents to use for this agent type
- L320 _public property_ `public string? Workspace { get; set; }` — Name of the workspace to sync
- L325 _public property_ `public string? TempStorageDir { get; set; }` — Path to the temporary storage dir
- L330 _public property_ `public Dictionary<string, string>? Environment { get; set; }` — Environment variables to be set when executing the job
- L335-336 _public ctor_ `public GetAgentTypeResponse()` — Constructor
- L341-347 _public ctor_ `public GetAgentTypeResponse(IAgentType other)` — Constructor

#### class `EpicGames.Horde.Streams.GetWorkspaceTypeResponse`  
`public class GetWorkspaceTypeResponse : IWorkspaceType`  
_public; L353-417_
- inherits: `IWorkspaceType`
- desc: Information about a workspace type
- L356 _public property_ `public string? Cluster { get; set; }` — (inheritdoc)
- L359 _public property_ `public string? ServerAndPort { get; set; }` — (inheritdoc)
- L362 _public property_ `public string? UserName { get; set; }` — (inheritdoc)
- L365 _public property_ `public string? Identifier { get; set; }` — (inheritdoc)
- L368 _public property_ `public string? Stream { get; set; }` — (inheritdoc)
- L371 _public property_ `public List<string>? View { get; set; }` — (inheritdoc)
- L372 _private* property_ `IReadOnlyList<string>? IWorkspaceType.View => ...`
- L375 _public property_ `public bool? Incremental { get; set; }` — (inheritdoc)
- L378 _public property_ `public bool? UseAutoSdk { get; set; }` — (inheritdoc)
- L381 _public property_ `public List<string>? AutoSdkView { get; set; }` — (inheritdoc)
- L382 _private* property_ `IReadOnlyList<string>? IWorkspaceType.AutoSdkView => ...`
- L385 _public property_ `public string? Method { get; set; }` — (inheritdoc)
- L388 _public property_ `public long? MinScratchSpace { get; set; }` — (inheritdoc)
- L391 _public property_ `public long? ConformDiskFreeSpace { get; set; }` — (inheritdoc)
- L396-397 _public ctor_ `public GetWorkspaceTypeResponse()` — Default constructor
- L402-416 _public ctor_ `public GetWorkspaceTypeResponse(IWorkspaceType other)` — Constructor

#### class `EpicGames.Horde.Streams.GetTemplateStepStateResponse`  
`public class GetTemplateStepStateResponse`  
_public; L422-455_
- desc: State information for a step in the stream
- L427 _public property_ `public string Name { get; set; }` — Name of the step
- L432 _public property_ `public GetThinUserInfoResponse? PausedByUserInfo { get; set; }` — User who paused the step
- L437 _public property_ `public DateTime? PauseTimeUtc { get; set; }` — The UTC time when the step was paused
- L442-444 _private ctor_ `private GetTemplateStepStateResponse()` — Default constructor for serialization
- L449-454 _public ctor_ `public GetTemplateStepStateResponse(ITemplateStep state, GetThinUserInfoResponse? pausedByUserInfo)` — Constructor

#### class `EpicGames.Horde.Streams.GetTemplateRefResponse`  
`public class GetTemplateRefResponse : GetTemplateResponseBase`  
_public; L460-546_
- inherits: `GetTemplateResponseBase`
- desc: Information about a template in this stream
- L465 _public property_ `public string Id { get; set; }` — Id of the template ref
- L470 _public property_ `public string Hash { get; set; }` — Hash of the template definition
- L475 _public property_ `public bool ShowUgsBadges { get; set; }` — Whether to show badges in UGS for these jobs
- L480 _public property_ `public bool ShowUgsAlerts { get; set; }` — Whether to show alerts in UGS for these jobs
- L485 _public property_ `public string? NotificationChannel { get; set; }` — Notification channel for this template. Overrides the stream channel if set.
- L490 _public property_ `public string? NotificationChannelFilter { get; set; }` — Notification channel filter for this template. Can be a combination of "Success", "Failure" and "Warnings" separated by pipe characters.
- L495 _public property_ `public string? TriageChannel { get; set; }` — Triage channel for this template. Overrides the stream channel if set.
- L500 _public property_ `public GetScheduleResponse? Schedule { get; set; }` — The schedule for this ref
- L505 _public property_ `public List<GetChainedJobTemplateResponse>? ChainedJobs { get; set; }` — List of templates to trigger
- L510 _public property_ `public List<GetTemplateStepStateResponse>? StepStates { get; set; }` — List of step states
- L515 _public property_ `public List<ChangeQueryMessage>? DefaultChange { get; set; }` — List of queries for the default changelist
- L520 _public property_ `public bool CanRun { get; set; }` — Whether the user is allowed to create jobs from this template
- L531-545 _public ctor_ `public GetTemplateRefResponse(TemplateId id, ITemplateRef templateRef, ITemplate template, List<GetTemplateStepStateResponse>? stepStates, TimeZoneInfo schedulerTimeZone, bool canRun) : base(template)` — Constructor

#### class `EpicGames.Horde.Streams.GetChainedJobTemplateResponse`  
`public class GetChainedJobTemplateResponse : IChainedJobTemplate`  
_public; L551-579_
- inherits: `IChainedJobTemplate`
- desc: Trigger for another template
- L554 _public property_ `public string Trigger { get; set; }` — (inheritdoc)
- L557 _public property_ `public TemplateId TemplateId { get; set; }` — (inheritdoc)
- L560 _public property_ `public bool UseDefaultChangeForTemplate { get; set; }` — (inheritdoc)
- L565-568 _public ctor_ `public GetChainedJobTemplateResponse()` — Constructor
- L573-578 _public ctor_ `public GetChainedJobTemplateResponse(IChainedJobTemplate other)` — Constructor

#### class `EpicGames.Horde.Streams.UpdateStepStateRequest`  
`public class UpdateStepStateRequest`  
_public; L584-596_
- desc: Step state update request
- L590 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of the step
- L595 _public property_ `public string? PausedByUserId { get; set; }` — User who paused the step

#### class `EpicGames.Horde.Streams.UpdateTemplateRefRequest`  
`public class UpdateTemplateRefRequest`  
_public; L601-607_
- desc: Updates an existing stream template ref
- L606 _public property_ `public List<UpdateStepStateRequest>? StepStates { get; set; }` — Step states to update

### `Source/Programs/Shared/EpicGames.Horde/StringId.cs` (EpicGames.Horde)


#### struct `EpicGames.Horde.StringId`  
`public readonly struct StringId : IEquatable<StringId>, IEquatable<string>, IEquatable<ReadOnlyMemory<char>>`  
_public; L20-322_
- attrs: `[JsonSchemaString] [JsonConverter(typeof(StringIdJsonConverter))] [TypeConverter(typeof(StringIdTypeConverter))]`
- inherits: `IEquatable<StringId>, IEquatable<string>, IEquatable<ReadOnlyMemory<char>>`
- desc: Normalized string identifier for a resource
- L36 _public const_ `public const int MaxLength = 64` — Maximum length for a string id
- L41 _public property_ `public Utf8String Text { get; }` — The text representing this id
- L46 _public property_ `public ReadOnlySpan<byte> Span => ...` — Accessor for the string bytes
- L51 _public property_ `public ReadOnlyMemory<byte> Memory => ...` — Accessor for the string bytes
- L57-60 _public ctor_ `public StringId(string text) : this(new Utf8String(text))` — Constructor
- L66-74 _public ctor_ `public StringId(Utf8String text)` — Constructor
- L82-85 _public ctor_ `public StringId(Utf8String text, Validate validate)` — attrs: `[SuppressMessage("Style", "IDE0060:Remove unused parameter")]` — Constructor
- L90 _public property_ `public bool IsEmpty => ...` — Checks whether this StringId is set
- L97-135 _public method_ `public static StringId Sanitize(string text)` — Generates a new string id from the given text
- L143 _public method_ `public static bool TryParse(string text, out StringId id)` — Validates the given string as a StringId, normalizing it if necessary.
- L153 _public method_ `public static bool TryParse(string text, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L162 _public method_ `public static bool TryParse(Utf8String text, out StringId id)` — Validates the given string as a StringId, normalizing it if necessary.
- L172-175 _public method_ `public static bool TryParse(Utf8String text, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L185-223 _public method_ `public static bool TryParse(Utf8String text, int maxLength, out StringId id, [NotNullWhen(false)] out string? errorMessage)` — Validates the given string as a StringId, normalizing it if necessary.
- L230-243 _private* method_ `static Utf8String ToLower(Utf8String text)` — Converts an utf8 string to lowercase
- L250 _public method_ `public static bool IsValidCharacter(char character)` — Checks whether the given character is valid within a string id
- L257-272 _public method_ `public static bool IsValidCharacter(byte character)` — Checks whether the given character is valid within a string id
- L275 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L278 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L281 _public method_ `public bool Equals(StringId other)` — (inheritdoc)
- L284 _public method_ `public bool Equals(string? other)` — (inheritdoc)
- L287-302 _public method_ `public bool Equals(ReadOnlyMemory<char> other)` — (inheritdoc)
- L305 _public method_ `public override string ToString()` — (inheritdoc)
- L313 _public operator_ `public static bool operator ==(StringId left, StringId right)` — Compares two string ids for equality
- L321 _public operator_ `public static bool operator !=(StringId left, StringId right)` — Compares two string ids for inequality

#### enum `EpicGames.Horde.StringId.Validate`  
`public enum Validate`  
_public; L25-31_
- desc: Enum used to disable validation on string arguments
- L30 _public* enumerator_ `None` — No validation required

#### class `EpicGames.Horde.StringIdJsonConverter`  
`sealed class StringIdJsonConverter : JsonConverter<StringId>`  
_internal*; L327-334_
- inherits: `JsonConverter<StringId>`
- desc: Class which serializes StringId types
- L330 _public method_ `public override StringId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L333 _public method_ `public override void Write(Utf8JsonWriter writer, StringId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.StringIdTypeConverter`  
`sealed class StringIdTypeConverter : TypeConverter`  
_internal*; L339-352_
- inherits: `TypeConverter`
- desc: Class which serializes StringId types
- L342 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L345 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L348 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L351 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/StringIdConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.StringIdConverter`  
`public abstract class StringIdConverter<T> where T : struct`  
_public; L18-29_
- constraints: `where T : struct`
- desc: Base class for converting to and from types containing a StringId. Useful pattern for reducing boilerplate with strongly typed records.
- L23 _public method_ `public abstract StringId ToStringId(T value)` — Converts a type to a StringId
- L28 _public method_ `public abstract T FromStringId(StringId id)` — Constructs a type from a StringId

#### class `EpicGames.Horde.StringIdConverterAttribute`  
`public sealed class StringIdConverterAttribute : Attribute`  
_public; L35-46_
- attrs: `[AttributeUsage(AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute declaring a StringIdConverter{T} for a particular type
- L40 _public property_ `public Type ConverterType { get; }` — The converter type
- L45 _public ctor_ `public StringIdConverterAttribute(Type converterType)` — Constructor

#### class `EpicGames.Horde.StringIdCbConverter`  
`public sealed class StringIdCbConverter<TValue, TConverter> : CbConverter<TValue> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L51-72_
- inherits: `CbConverter<TValue>`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Converter to compact binary objects
- L53 _private* field_ `readonly TConverter _converter = new()`
- L56-59 _public method_ `public override TValue Read(CbField field)` — (inheritdoc)
- L62-65 _public method_ `public override void Write(CbWriter writer, TValue value)` — (inheritdoc)
- L68-71 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, TValue value)` — (inheritdoc)

#### class `EpicGames.Horde.StringIdTypeConverter`  
`public sealed class StringIdTypeConverter<TValue, TConverter> : TypeConverter where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L77-117_
- inherits: `TypeConverter`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Class which serializes types with a StringIdConverter{T} to Json
- L79 _private* field_ `readonly TConverter _converter = new()`
- L82-85 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L88-99 _public method_ `public override object? ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
- L102 _public method_ `public override bool CanConvertTo(ITypeDescriptorContext? context, Type? destinationType)` — (inheritdoc)
- L105-116 _public method_ `public override object? ConvertTo(ITypeDescriptorContext? context, CultureInfo? culture, object? value, Type destinationType)` — (inheritdoc)

#### class `EpicGames.Horde.StringIdJsonConverter`  
`public sealed class StringIdJsonConverter<TValue, TConverter> : JsonConverter<TValue> where TValue : struct where TConverter : StringIdConverter<TValue>, new()`  
_public; L122-141_
- inherits: `JsonConverter<TValue>`
- constraints: `where TValue : struct where TConverter : StringIdConverter<TValue>, new()`
- desc: Class which serializes types with a StringIdConverter{T} to Json
- L124 _private* field_ `readonly TConverter _converter = new()`
- L127 _public method_ `public override TValue Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L131 _public method_ `public override void Write(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)
- L135 _public method_ `public override TValue ReadAsPropertyName(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L139 _public method_ `public override void WriteAsPropertyName(Utf8JsonWriter writer, TValue value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Horde.StringIdJsonConverterFactory`  
`public sealed class StringIdJsonConverterFactory : JsonConverterFactory`  
_public; L146-161_
- inherits: `JsonConverterFactory`
- desc: Creates constructors for types with a StringIdConverter{T} to Json
- L149 _public method_ `public override bool CanConvert(Type typeToConvert)` — (inheritdoc)
- L152-160 _public method_ `public override JsonConverter? CreateConverter(Type type, JsonSerializerOptions options)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Symbols/SymStore.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Symbols.SymStore`  
`public static class SymStore`  
_public; L23-282_
- desc: Provides functionality for hashing files to add to a Microsoft Symbol store. * For PE-format files (EXE, DLL), this consists of the * For PDB files, this consists of the PDB GUID followed by its age (the number of times it has been written).
- L32-54 _public method_ `public static Task<string?> GetHashAsync(FileReference file, ILogger logger, CancellationToken cancellationToken = default)` — Gets the hash of a file.
- L63-110 _private* method_ `static async Task<string?> GetExeHashAsync(FileReference file, CancellationToken cancellationToken)` — Gets the hash for a Windows portable executable file, consisting of concatenated hex values for the timestamp and image size fields in the header. Structures referenced below (IMAGE_DOS_HEADER, IMAGE_NT_HEADERS) are defined in Windows headers, but are parsed via offsets into the executable to reduce messy marshalling in C#.
- L115 _private* field_ `static readonly ReadOnlyMemory<byte> s_portablePdbSignature = new byte[] { 0x42, 0x53, 0x4a, 0x42 }`
- L128-162 _private* method_ `static string? GetPdbHash(FileReference file)` — Parse the hash value from a PDB file, consisting of concatenated hex values for the PDB GUID and age (the number of times it has been written). While the fields to obtain are at fairly straightforward offsets in particular data structures, PDBs are internally structured as an MSF file consisting of multiple data streams with non-contiguous pages. There are a few references for parsing this format: * LLVM documentation: https://llvm.org/docs/PDB/MsfFile.html * Microsoft's PDB source code: https://github.com/microsoft/microsoft-pdb (particularly PDB/msf/msf.cpp) This function only handles the BigMSF format.

#### class `EpicGames.Horde.Symbols.SymStore.MsfFile`  
`class MsfFile`  
_private*; L164-279_
- L166 _private* field_ `static readonly byte[] s_msfSignature = Encoding.ASCII.GetBytes("Microsoft C/C++ MSF 7.00\r\n\x1a\x44\x53\0\0\0")`
- L170 _private* field_ `readonly MemoryMappedView _memoryMappedView`
- L171 _private* field_ `readonly int _numPages`
- L172 _private* field_ `readonly int _pageSize`
- L173 _private* field_ `readonly int[] _streamDirectoryPages`
- L174 _private* field_ `readonly MsfStream[] _streams`
- L176-242 _public ctor_ `public MsfFile(MemoryMappedView memoryMappedView)`
- L244 _private* method_ `int GetPageCount(int numBytes)`
- L247-252 _public method_ `public ReadOnlySpan<byte> GetStreamData(int streamIdx, int offset)`
- L254-259 _public method_ `public ReadOnlySpan<int> GetStreamDirectoryData(int offset)`
- L261-266 _public method_ `public Span<byte> GetPage(int pageIdx)`
- L268-272 _private* method_ `ReadOnlySpan<byte> GetStreamPage(int streamIdx, int pageIdx)`
- L274-278 _private* method_ `ReadOnlySpan<int> GetDirectoryPage(int directoryPageIdx)`

#### record struct `EpicGames.Horde.Symbols.SymStore.MsfFile.MsfStream`  
`record struct MsfStream(int Length, int DirectoryPagesIdx)`  
_private*; L168-168_

### `Source/Programs/Shared/EpicGames.Horde/Symbols/SymbolStoreId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Symbols.SymbolStoreId`  
`public record struct SymbolStoreId(StringId Id)`  
_public; L17-31_
- attrs: `[JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<SymbolStoreId, SymbolStoreIdConverter>))] [StringIdConverter(typeof(SymbolStoreIdConverter))] [CbConverter(typeof(StringIdCbConverter<SymbolStoreId, SymbolStoreIdConverter>))]`
- desc: Identifier for a symbol store
- L22-24 _public ctor_ `public SymbolStoreId(string id) : this(new StringId(id))` — Constructor
- L27 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L30 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Symbols.SymbolStoreIdConverter`  
`class SymbolStoreIdConverter : StringIdConverter<SymbolStoreId>`  
_internal*; L36-43_
- inherits: `StringIdConverter<SymbolStoreId>`
- desc: Converter to and from StringId instances.
- L39 _public method_ `public override SymbolStoreId FromStringId(StringId id)` — (inheritdoc)
- L42 _public method_ `public override StringId ToStringId(SymbolStoreId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Telemetry/HordeContextTelemetryRecord.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Telemetry.HordeContextTelemetryRecord`  
`public record HordeContextTelemetryRecord : CorrelatableTelemetryRecord`  
_public; L17-241_
- inherits: `CorrelatableTelemetryRecord`
- desc: Record that describes telemetry that can contain common Horde context (and whether it is within a build context or not).
- L22 _public const_ `public const int InvalidCommitId = -1` — The value for an invalid commit id.
- L30 _public property_ `public bool IsBuildMachine { get; init; }` — attrs: `[Column("is_build_machine")]` — Whether context is build machine, or not.
- L37 _public property_ `public string? HordeUrlStr { get; init; }` — attrs: `[Column("horde_url_str")]` — The Horde URL.
- L44 _public property_ `public StreamId? StreamId { get; init; }` — attrs: `[Column("stream_id")]` — The stream id.
- L50 _public property_ `public TemplateId? TemplateId { get; init; }` — attrs: `[Column("template_id")]` — The template id.
- L56 _public property_ `public JobId? JobId { get; init; }` — attrs: `[Column("job_id")]` — The Horde job id.
- L62 _public property_ `public JobStepId? StepId { get; init; }` — attrs: `[Column("step_id")]` — The Horde step id.
- L68 _public property_ `public int? CommitIdOrdered { get; init; }` — attrs: `[Column("commit_id_ordered")]` — The ordered commit id.
- L74 _public property_ `public string? CommitId { get; init; }` — attrs: `[Column("commit_id")]` — The unordered commit id.
- L84 _protected ctor_ `protected HordeContextTelemetryRecord() : base()` — No arg constructor for ORM construction.
- L101-111 _public ctor_ `public HordeContextTelemetryRecord(string eventName, int schemaVersion, string? sessionId, string? sessionLabel, bool isBuildMachine, Uri? hordeUrlStr, StreamId? streamId, TemplateId? templateId, JobId? jobId, JobStepId? stepId, int? commitIdOrdered, string? commitId) : base(eventName, schemaVersion, sessionId, sessionLabel)` — Constructor for standard Horde context.
- L129-142 _public ctor_ `public HordeContextTelemetryRecord(string eventName, int schemaVersion, string? sessionId, string? sessionLabel, bool isBuildMachine, string? hordeUrlStr, string? streamId, string? templateId, string? jobId, string? stepId, int? commitIdOrdered, string? commitId) : base(eventName, schemaVersion, sessionId, sessionLabel)` — Constructor for standard Horde context.
- L152-177 _public ctor_ `public HordeContextTelemetryRecord(string eventName, int schemaVersion, string? sessionId, string? sessionLabel) : base(eventName, schemaVersion, sessionId, sessionLabel)` — Constructs a standard Horde context from environment variables.
- L184-217 _protected method_ `protected override void WriteProperties(Hashtable hashtable)` — (inheritdoc)
- L223-238 _private method_ `private static T? TryCreate<T>(string? value, Func<string, T> creationDelegate) where T : struct`

### `Source/Programs/Shared/EpicGames.Horde/Telemetry/Metrics/MetricId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Telemetry.Metrics.MetricId`  
`public readonly record struct MetricId(StringId Id)`  
_public; L18-32_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<MetricId, MetricIdConverter>))] [StringIdConverter(typeof(MetricIdConverter))] [CbConverter(typeof(StringIdCbConverter<MetricId, MetricIdConverter>))]`
- desc: Identifier for a particular metric
- L23-25 _public ctor_ `public MetricId(string id) : this(new StringId(id))` — Constructor
- L28 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L31 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Telemetry.Metrics.MetricIdConverter`  
`class MetricIdConverter : StringIdConverter<MetricId>`  
_internal*; L37-44_
- inherits: `StringIdConverter<MetricId>`
- desc: Converter to and from StringId instances.
- L40 _public method_ `public override MetricId FromStringId(StringId id)` — (inheritdoc)
- L43 _public method_ `public override StringId ToStringId(MetricId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Telemetry/TelemetryMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Telemetry.PostTelemetryEventStreamRequest`  
`public class PostTelemetryEventStreamRequest`  
_public; L18-24_
- desc: Generic message for a telemetry event
- L23 _public property_ `public List<System.Text.Json.JsonElement> Events { get; set; }` — List of telemetry events

#### enum `EpicGames.Horde.Telemetry.TelemetryUploadType`  
`public enum TelemetryUploadType`  
_public; L29-35_
- desc: Indicates the type of telemetry data being uploaded
- L34 _public* enumerator_ `EtEventStream` — A batch of PostTelemetryEventStreamRequest objects.

#### class `EpicGames.Horde.Telemetry.GetTelemetryMetricsMetaResponse`  
`public class GetTelemetryMetricsMetaResponse`  
_public; L40-66_
- desc: Metrics meta data for query
- L45 _public property_ `public string MetricId { get; set; }` — The corresponding metric id
- L50 _public property_ `public string GroupBy { get; set; }` — Metric grouping information
- L55 _public property_ `public List<string> Groups { get; set; }` — Metrics groups matching the search terms
- L60 _public property_ `public int TopN { get; set; }` — TopN aggregation
- L65 _public property_ `public int BottomN { get; set; }` — BottomN aggregation

#### class `EpicGames.Horde.Telemetry.GetTelemetryMetricsResponse`  
`public class GetTelemetryMetricsResponse`  
_public; L71-87_
- desc: Metrics matching a particular query
- L76 _public property_ `public string MetricId { get; set; }` — The corresponding metric id
- L81 _public property_ `public string GroupBy { get; set; }` — Metric grouping information
- L86 _public property_ `public List<GetTelemetryMetricResponse> Metrics { get; set; }` — Metrics matching the search terms

#### class `EpicGames.Horde.Telemetry.GetTelemetryMetricResponse`  
`public class GetTelemetryMetricResponse`  
_public; L92-108_
- desc: Information about a particular metric
- L97 _public property_ `public DateTime Time { get; set; }` — Start time for the sample
- L102 _public property_ `public string? Group { get; set; }` — Name of the group
- L107 _public property_ `public double Value { get; set; }` — Value for the metric

#### enum `EpicGames.Horde.Telemetry.TelemetryMetricUnitType`  
`public enum TelemetryMetricUnitType`  
_public; L113-127_
- desc: The units used to present the telemetry
- L118 _public* enumerator_ `Time` — Time duration
- L122 _public* enumerator_ `Ratio` — Ratio 0-100%
- L126 _public* enumerator_ `Value` — Artbitrary numeric value

#### enum `EpicGames.Horde.Telemetry.TelemetryMetricGraphType`  
`public enum TelemetryMetricGraphType`  
_public; L132-142_
- desc: The type of
- L137 _public* enumerator_ `Line` — A line graph
- L141 _public* enumerator_ `Indicator` — Key performance indicator (KPI) chart with thrasholds

#### class `EpicGames.Horde.Telemetry.TelemetryChartMetricConfig`  
`public class TelemetryChartMetricConfig`  
_public; L147-164_
- desc: Metric attached to a telemetry chart
- L153 _public property_ `public MetricId Id { get; set; }` — attrs: `[Required]` — Associated metric id
- L158 _public property_ `public int? Threshold { get; set; }` — The threshold for KPI values
- L163 _public property_ `public string? Alias { get; set; }` — The metric alias for display purposes

#### class `EpicGames.Horde.Telemetry.TelemetryChartConfig`  
`public class TelemetryChartConfig`  
_public; L169-201_
- desc: Telemetry chart configuraton
- L175 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the chart, will be displayed on the dashboard
- L180 _public property_ `public TelemetryMetricUnitType Display { get; set; }` — The unit to display
- L185 _public property_ `public TelemetryMetricGraphType Graph { get; set; }` — The graph type
- L190 _public property_ `public List<TelemetryChartMetricConfig> Metrics { get; set; }` — List of configured metrics
- L195 _public property_ `public int? Min { get; set; }` — The min unit value for clamping chart
- L200 _public property_ `public int? Max { get; set; }` — The max unit value for clamping chart

#### class `EpicGames.Horde.Telemetry.TelemetryCategoryConfig`  
`public class TelemetryCategoryConfig`  
_public; L206-218_
- desc: A chart categody, will be displayed on the dashbord under an associated pivot
- L212 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the category
- L217 _public property_ `public List<TelemetryChartConfig> Charts { get; set; }` — The charts contained within the category

#### class `EpicGames.Horde.Telemetry.TelemetryVariableConfig`  
`public class TelemetryVariableConfig`  
_public; L223-241_
- desc: A telemetry view variable used for filtering the charting data
- L229 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the variable for display purposes
- L235 _public property_ `public string Group { get; set; }` — attrs: `[Required]` — The associated data group attached to the variable
- L240 _public property_ `public List<string> Defaults { get; set; }` — The default values to select

#### class `EpicGames.Horde.Telemetry.TelemetryViewConfig`  
`public class TelemetryViewConfig`  
_public; L246-275_
- desc: A telemetry view of related metrics, divided into categofies
- L252 _public property_ `public TelmetryViewId Id { get; set; }` — attrs: `[Required]` — Identifier for the view
- L258 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — The name of the view
- L264 _public property_ `public TelemetryStoreId TelemetryStoreId { get; set; }` — attrs: `[Required]` — The telemetry store this view uses
- L269 _public property_ `public List<TelemetryVariableConfig> Variables { get; set; }` — The variables used to filter the view data
- L274 _public property_ `public List<TelemetryCategoryConfig> Categories { get; set; }` — The categories contained within the view

#### record struct `EpicGames.Horde.Telemetry.TelmetryViewId`  
`public record struct TelmetryViewId(StringId Id)`  
_public; L286-300_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<TelmetryViewId, TelmetryViewIdConverter>))] [StringIdConverter(typeof(TelmetryViewIdConverter))] [CbConverter(typeof(StringIdCbConverter<TelmetryViewId, TelmetryViewIdConverter>))]`
- desc: Identifier for a particular metric view
- L291-293 _public ctor_ `public TelmetryViewId(string id) : this(new StringId(id))` — Constructor
- L296 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L299 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Telemetry.TelmetryViewIdConverter`  
`class TelmetryViewIdConverter : StringIdConverter<TelmetryViewId>`  
_internal*; L305-312_
- inherits: `StringIdConverter<TelmetryViewId>`
- desc: Converter to and from StringId instances.
- L308 _public method_ `public override TelmetryViewId FromStringId(StringId id)` — (inheritdoc)
- L311 _public method_ `public override StringId ToStringId(TelmetryViewId value)` — (inheritdoc)

#### class `EpicGames.Horde.Telemetry.GetTelemetryChartMetricResponse`  
`public class GetTelemetryChartMetricResponse`  
_public; L317-333_
- desc: Metric attached to a telemetry chart
- L322 _public property_ `public string MetricId { get; set; }` — Associated metric id
- L327 _public property_ `public int? Threshold { get; set; }` — The threshold for KPI values
- L332 _public property_ `public string? Alias { get; set; }` — The metric alias for display purposes

#### class `EpicGames.Horde.Telemetry.GetTelemetryChartResponse`  
`public class GetTelemetryChartResponse`  
_public; L338-369_
- desc: Telemetry chart configuraton
- L343 _public property_ `public string Name { get; set; }` — The name of the chart, will be displayed on the dashboard
- L348 _public property_ `public string Display { get; set; }` — The unit to display
- L353 _public property_ `public string Graph { get; set; }` — The graph type
- L358 _public property_ `public List<GetTelemetryChartMetricResponse> Metrics { get; set; }` — List of configured metrics
- L363 _public property_ `public int? Min { get; set; }` — The min unit value for clamping chart
- L368 _public property_ `public int? Max { get; set; }` — The max unit value for clamping chart

#### class `EpicGames.Horde.Telemetry.GetTelemetryCategoryResponse`  
`public class GetTelemetryCategoryResponse`  
_public; L374-385_
- desc: A chart categody, will be displayed on the dashbord under an associated pivot
- L379 _public property_ `public string Name { get; set; }` — The name of the category
- L384 _public property_ `public List<GetTelemetryChartResponse> Charts { get; set; }` — The charts contained within the category

#### class `EpicGames.Horde.Telemetry.GetTelemetryVariableResponse`  
`public class GetTelemetryVariableResponse`  
_public; L390-406_
- desc: A telemetry view variable used for filtering the charting data
- L395 _public property_ `public string Name { get; set; }` — The name of the variable for display purposes
- L400 _public property_ `public string Group { get; set; }` — The associated data group attached to the variable
- L405 _public property_ `public List<string> Defaults { get; set; }` — The default values to select

#### class `EpicGames.Horde.Telemetry.GetTelemetryViewResponse`  
`public class GetTelemetryViewResponse`  
_public; L411-437_
- desc: A telemetry view of related metrics, divided into categofies
- L416 _public property_ `public string Id { get; set; }` — Identifier for the view
- L421 _public property_ `public string Name { get; set; }` — The name of the view
- L426 _public property_ `public string TelemetryStoreId { get; set; }` — The telemetry store the view uses
- L431 _public property_ `public List<GetTelemetryVariableResponse> Variables { get; set; }` — The variables used to filter the view data
- L436 _public property_ `public List<GetTelemetryCategoryResponse> Categories { get; set; }` — The categories contained within the view

### `Source/Programs/Shared/EpicGames.Horde/Telemetry/TelemetryStoreId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Telemetry.TelemetryStoreId`  
`public readonly record struct TelemetryStoreId(StringId Id)`  
_public; L18-37_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<TelemetryStoreId, TelemetryStoreIdConverter>))] [StringIdConverter(typeof(TelemetryStoreIdConverter))] [CbConverter(typeof(StringIdCbConverter<TelemetryStoreId, TelemetryStoreIdConverter>))]`
- desc: Identifier for a telemetry store
- L23 _public property_ `public static TelemetryStoreId Default { get; }` — Default telemetry store for Horde internal metrics
- L28-30 _public ctor_ `public TelemetryStoreId(string id) : this(new StringId(id))` — Constructor
- L33 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L36 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Telemetry.TelemetryStoreIdConverter`  
`public class TelemetryStoreIdConverter : StringIdConverter<TelemetryStoreId>`  
_public; L42-49_
- inherits: `StringIdConverter<TelemetryStoreId>`
- desc: Converter to and from StringId instances.
- L45 _public method_ `public override TelemetryStoreId FromStringId(StringId id)` — (inheritdoc)
- L48 _public method_ `public override StringId ToStringId(TelemetryStoreId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Tools/HttpToolCollection.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Tools.HttpToolCollection`  
`class HttpToolCollection : IToolCollection`  
_internal*; L16-143_
- inherits: `IToolCollection`
- L97 _private* field_ `readonly IHordeClient _hordeClient`
- L102 _public ctor_ `public HttpToolCollection(IHordeClient hordeClient)` — Constructor
- L106-111 _public method_ `public async Task<ITool?> GetAsync(ToolId id, CancellationToken cancellationToken = default)` — (inheritdoc)
- L114-130 _public method_ `public async Task<IReadOnlyList<ITool>> GetAllAsync(CancellationToken cancellationToken = default)` — (inheritdoc)
- L132-136 _private* method_ `IBlobRef<DirectoryNode> Open(ToolId toolId, BlobLocator locator)`
- L138-142 _private* method_ `async Task<Stream> OpenZipStreamAsync(ToolId id, ToolDeploymentId deploymentId, CancellationToken cancellationToken = default)`

#### class `EpicGames.Horde.Tools.HttpToolCollection.Tool`  
`class Tool : ITool`  
_private*; L19-61_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `ITool`
- L21 _private* field_ `static readonly IReadOnlyDictionary<string, string> s_defaultMetadata = ...`
- L21 _private* field_ `static readonly IReadOnlyDictionary< s_defaultMetadata = new Dictionary<string, string>()`
- L23 _private* field_ `readonly GetToolResponse _response`
- L24 _private* field_ `readonly List<ToolDeployment> _deployments`
- L26 _public property_ `public ToolId Id => ...`
- L28 _private* property_ `string ITool.Name => ...`
- L29 _private* property_ `string ITool.Description => ...`
- L30 _private* property_ `string? ITool.Category => ...`
- L31 _private* property_ `string? ITool.Group => ...`
- L32 _private* property_ `IReadOnlyList<string>? ITool.Platforms => ...`
- L33 _private* property_ `bool ITool.Public => ...`
- L34 _private* property_ `bool ITool.Bundled => ...`
- L35 _private* property_ `bool ITool.ShowInUgs => ...`
- L36 _private* property_ `bool ITool.ShowInDashboard => ...`
- L37 _private* property_ `bool ITool.ShowInToolbox => ...`
- L38 _private* property_ `IReadOnlyDictionary<string, string> ITool.Metadata => ...`
- L39 _private* property_ `IReadOnlyList<IToolDeployment> ITool.Deployments => ...`
- L41-45 _public ctor_ `public Tool(HttpToolCollection collection, GetToolResponse response)`
- L47 _public method_ `public bool Authorize(AclAction action, ClaimsPrincipal principal)`
- L50 _public method_ `public Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, Stream stream, CancellationToken cancellationToken = default)`
- L53 _public method_ `public Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, HashedBlobRefValue target, CancellationToken cancellationToken = default)`
- L56 _public method_ `public IStorageBackend GetStorageBackend()`
- L59 _public method_ `public IStorageNamespace GetStorageNamespace()`

#### class `EpicGames.Horde.Tools.HttpToolCollection.ToolDeployment`  
`class ToolDeployment : IToolDeployment`  
_private*; L64-95_
- attrs: `[DebuggerDisplay("{Id}")]`
- inherits: `IToolDeployment`
- L66 _private* field_ `readonly HttpToolCollection _collection`
- L67 _private* field_ `readonly ToolId _toolId`
- L68 _private* field_ `readonly GetToolDeploymentResponse _response`
- L70 _public property_ `public ToolDeploymentId Id => ...`
- L72 _private* property_ `string IToolDeployment.Version => ...`
- L73 _private* property_ `ToolDeploymentState IToolDeployment.State => ...`
- L74 _private* property_ `double IToolDeployment.Progress => ...`
- L75 _private* property_ `DateTime? IToolDeployment.StartedAt => ...`
- L76 _private* property_ `TimeSpan IToolDeployment.Duration => ...`
- L77 _private* property_ `NamespaceId IToolDeployment.NamespaceId => ...`
- L78 _private* property_ `RefName IToolDeployment.RefName => ...`
- L80 _private* property_ `IBlobRef<DirectoryNode> IToolDeployment.Content => ...`
- L83-88 _public ctor_ `public ToolDeployment(HttpToolCollection collection, ToolId toolId, GetToolDeploymentResponse response)`
- L90 _private* method_ `Task<Stream> IToolDeployment.OpenZipStreamAsync(CancellationToken cancellationToken)`
- L93 _private* method_ `Task<IToolDeployment?> IToolDeployment.UpdateAsync(ToolDeploymentState state, CancellationToken cancellationToken)`

### `Source/Programs/Shared/EpicGames.Horde/Tools/ITool.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Tools.ITool`  
`public interface ITool`  
_public; L21-122_
- desc: Describes a standalone, external tool hosted and deployed by Horde. Provides basic functionality for performing gradual roll-out, versioning, etc...
- L26 _public* property_ `ToolId Id { get; }` — Identifier for the tool
- L31 _public* property_ `string Name { get; }` — Name of the tool
- L36 _public* property_ `string Description { get; }` — Long-form description of the tool
- L41 _public* property_ `string? Category { get; }` — Category for the tool on the dashboard
- L46 _public* property_ `string? Group { get; }` — Grouping key for merging tool versions together on the dashboard
- L51 _public* property_ `IReadOnlyList<string>? Platforms { get; }` — Supported platforms, as a NET runtime identifiers
- L56 _public* property_ `bool Public { get; }` — Whether the tool is available to authenticated users
- L61 _public* property_ `bool Bundled { get; }` — Whether the tool is bundled with the server
- L66 _public* property_ `bool ShowInUgs { get; }` — Whether to show the tool for download in UGS
- L71 _public* property_ `bool ShowInDashboard { get; }` — Whether to show the tool for download in the dashboard
- L76 _public* property_ `bool ShowInToolbox { get; }` — Whether to show the tool for download in the toolbox
- L81 _public* property_ `IReadOnlyDictionary<string, string> Metadata { get; }` — User-defined metadata for this tool
- L86 _public* property_ `IReadOnlyList<IToolDeployment> Deployments { get; }` — Current deployments of this tool, sorted by time.
- L93 _public* method_ `bool Authorize(AclAction action, ClaimsPrincipal principal)` — Authorize a user to perform a particular action
- L102 _public* method_ `Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, Stream stream, CancellationToken cancellationToken = default)` — Adds a new deployment to the given tool. The new deployment will replace the current active deployment.
- L111 _public* method_ `Task<ITool?> CreateDeploymentAsync(ToolDeploymentConfig options, HashedBlobRefValue target, CancellationToken cancellationToken = default)` — Adds a new deployment to the given tool. The new deployment will replace the current active deployment.
- L116 _public* method_ `IStorageBackend GetStorageBackend()` — Gets the storage backend for this tool
- L121 _public* method_ `IStorageNamespace GetStorageNamespace()` — Gets the storage namespace for this particular tool

#### interface `EpicGames.Horde.Tools.IToolDeployment`  
`public interface IToolDeployment`  
_public; L127-188_
- desc: Deployment of a tool
- L132 _public* property_ `ToolDeploymentId Id { get; }` — Identifier for this deployment. A new identifier will be assigned to each created instance, so an identifier corresponds to a unique deployment.
- L137 _public* property_ `string Version { get; }` — Descriptive version string for this tool revision
- L142 _public* property_ `ToolDeploymentState State { get; }` — Current state of this deployment
- L147 _public* property_ `double Progress { get; }` — Current progress of the deployment
- L152 _public* property_ `DateTime? StartedAt { get; }` — Last time at which the progress started. Set to null if the deployment was paused.
- L157 _public* property_ `TimeSpan Duration { get; }` — Length of time over which to make the deployment
- L162 _public* property_ `NamespaceId NamespaceId { get; }` — Namespace containing the tool
- L167 _public* property_ `RefName RefName { get; }` — Reference to this tool in Horde Storage.
- L172 _public* property_ `IBlobRef<DirectoryNode> Content { get; }` — Handle to the tool data
- L180 _public* method_ `Task<IToolDeployment?> UpdateAsync(ToolDeploymentState state, CancellationToken cancellationToken = default)` — Updates the state of the current deployment
- L187 _public* method_ `Task<Stream> OpenZipStreamAsync(CancellationToken cancellationToken = default)` — Opens a stream to the data for a particular deployment

#### class `EpicGames.Horde.Tools.ToolDeploymentConfig`  
`public class ToolDeploymentConfig`  
_public; L193-205_
- desc: Options for a new deployment
- L196 _public property_ `public string Version { get; set; }` — (inheritdoc)
- L199 _public property_ `public TimeSpan Duration { get; set; }` — (inheritdoc)
- L204 _public property_ `public bool CreatePaused { get; set; }` — Whether to create the deployment in a paused state

#### class `EpicGames.Horde.Tools.ToolExtensions`  
`public static class ToolExtensions`  
_public; L210-253_
- desc: Extension methods for tools
- L219-230 _public method_ `public static IToolDeployment? GetCurrentDeployment(this ITool tool, double phase, DateTime utcNow)` — Gets the current deployment
- L238-252 _public method_ `public static double GetProgressValue(this IToolDeployment deployment, DateTime utcNow)` — Get the progress fraction for a particular deployment and time

### `Source/Programs/Shared/EpicGames.Horde/Tools/IToolCollection.cs` (EpicGames.Horde)


#### interface `EpicGames.Horde.Tools.IToolCollection`  
`public interface IToolCollection`  
_public; L12-28_
- desc: Collection of tools
- L20 _public* method_ `Task<ITool?> GetAsync(ToolId id, CancellationToken cancellationToken = default)` — Gets a tool with the given identifier
- L27 _public* method_ `Task<IReadOnlyList<ITool>> GetAllAsync(CancellationToken cancellationToken = default)` — Gets all the available tools

### `Source/Programs/Shared/EpicGames.Horde/Tools/ToolDeploymentId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Tools.ToolDeploymentId`  
`public readonly record struct ToolDeploymentId(BinaryId Id)`  
_public; L18-25_
- attrs: `[LogValueType] [JsonSchemaString] [JsonConverter(typeof(BinaryIdJsonConverter<ToolDeploymentId, ToolDeploymentIdConverter>))] [TypeConverter(typeof(BinaryIdTypeConverter<ToolDeploymentId, ToolDeploymentIdConverter>))] [BinaryIdConverter(typeof(ToolDeploymentIdConverter))]`
- desc: Identifier for a tool deployment
- L21 _public method_ `public static ToolDeploymentId Parse(string text)` — (inheritdoc)
- L24 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Tools.ToolDeploymentIdConverter`  
`class ToolDeploymentIdConverter : BinaryIdConverter<ToolDeploymentId>`  
_internal*; L30-37_
- inherits: `BinaryIdConverter<ToolDeploymentId>`
- desc: Converter class to and from BinaryId values
- L33 _public method_ `public override ToolDeploymentId FromBinaryId(BinaryId id)` — (inheritdoc)
- L36 _public method_ `public override BinaryId ToBinaryId(ToolDeploymentId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Tools/ToolId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Tools.ToolId`  
`public readonly record struct ToolId(StringId Id)`  
_public; L20-34_
- attrs: `[LogValueType] [JsonSchemaString] [JsonConverter(typeof(StringIdJsonConverter<ToolId, ToolIdConverter>))] [TypeConverter(typeof(StringIdTypeConverter<ToolId, ToolIdConverter>))] [StringIdConverter(typeof(ToolIdConverter))] [CbConverter(typeof(StringIdCbConverter<ToolId, ToolIdConverter>))]`
- desc: Identifier for a tool
- L25-27 _public ctor_ `public ToolId(string id) : this(new StringId(id))` — Constructor
- L30 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L33 _public method_ `public override string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Tools.ToolIdConverter`  
`class ToolIdConverter : StringIdConverter<ToolId>`  
_internal*; L39-46_
- inherits: `StringIdConverter<ToolId>`
- desc: Converter to and from StringId instances.
- L42 _public method_ `public override ToolId FromStringId(StringId id)` — (inheritdoc)
- L45 _public method_ `public override StringId ToStringId(ToolId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Tools/ToolMessages.cs` (EpicGames.Horde)


#### record `EpicGames.Horde.Tools.GetToolResponse`  
`public record class GetToolResponse(ToolId Id, string Name, string Description, string? Category, string? Group, List<string>? Platforms, List<GetToolDeploymentResponse> Deployments, bool Public, bool Bundled, bool ShowInUgs, bool ShowInDashboard, bool ShowInToolbox, Dictionary<string, string>? Metadata = null)`  
_public; L26-26_
- desc: Describes a standalone, external tool hosted and deployed by Horde. Provides basic functionality for performing gradual roll-out, versioning, etc...

#### record `EpicGames.Horde.Tools.GetToolSummaryResponse`  
`public record class GetToolSummaryResponse(ToolId Id, string Name, string Description, string? Category, string? Group, List<string>? Platforms, string? Version, ToolDeploymentId? DeploymentId, ToolDeploymentState? DeploymentState, double? DeploymentProgress, bool Bundled, bool ShowInUgs, bool ShowInDashboard, bool ShowInToolbox, Dictionary<string, string>? Metadata = null)`  
_public; L46-46_
- desc: Summary for a particular tool.

#### record `EpicGames.Horde.Tools.GetToolsSummaryResponse`  
`public record GetToolsSummaryResponse(List<GetToolSummaryResponse> Tools)`  
_public; L52-52_
- desc: Response when querying all tools

#### record `EpicGames.Horde.Tools.GetToolDeploymentResponse`  
`public record GetToolDeploymentResponse(ToolDeploymentId Id, string Version, ToolDeploymentState State, double Progress, DateTime? StartedAt, TimeSpan Duration, RefName RefName, BlobLocator Locator)`  
_public; L65-65_
- desc: Response object describing the deployment of a tool

#### record `EpicGames.Horde.Tools.CreateToolDeploymentRequest`  
`public record CreateToolDeploymentRequest(string Version, double? Duration, bool? CreatePaused, HashedBlobRefValue Content)`  
_public; L74-74_
- desc: Request for creating a new deployment

#### record `EpicGames.Horde.Tools.CreateToolDeploymentResponse`  
`public record CreateToolDeploymentResponse(ToolDeploymentId Id)`  
_public; L80-80_
- desc: Response from creating a deployment

#### enum `EpicGames.Horde.Tools.ToolDeploymentState`  
`public enum ToolDeploymentState`  
_public; L85-106_
- desc: Current state of a tool's deployment
- L90 _public* enumerator_ `Active` — The deployment is ongoing
- L95 _public* enumerator_ `Paused` — The deployment should be paused at its current state
- L100 _public* enumerator_ `Complete` — Deployment of this version is complete
- L105 _public* enumerator_ `Cancelled` — The deployment has been cancelled.

#### class `EpicGames.Horde.Tools.UpdateDeploymentRequest`  
`public class UpdateDeploymentRequest`  
_public; L111-117_
- desc: Update an existing deployment
- L116 _public property_ `public ToolDeploymentState? State { get; set; }` — New state for the deployment

#### enum `EpicGames.Horde.Tools.GetToolAction`  
`public enum GetToolAction`  
_public; L122-138_
- desc: Action for a deployment
- L127 _public* enumerator_ `Info` — Query for information about the deployment
- L132 _public* enumerator_ `Download` — Download the deployment data
- L137 _public* enumerator_ `Zip` — Download the deployment data as a zip file

### `Source/Programs/Shared/EpicGames.Horde/Ugs/UgsMessages.cs` (EpicGames.Horde)


#### enum `EpicGames.Horde.Ugs.UgsUserVote`  
`public enum UgsUserVote`  
_public; L15-41_
- desc: Review by a user of a particular change
- L20 _public* enumerator_ `None` — No vote for the current change
- L25 _public* enumerator_ `CompileSuccess` — Succesfully compiled the change
- L30 _public* enumerator_ `CompileFailure` — Failed to compile the change
- L35 _public* enumerator_ `Good` — Manually marked the change as good
- L40 _public* enumerator_ `Bad` — Manually marked the change as bad

#### enum `EpicGames.Horde.Ugs.UgsBadgeState`  
`public enum UgsBadgeState`  
_public; L46-72_
- desc: State of a badge
- L51 _public* enumerator_ `Starting` — Starting work on this badge, outcome currently unknown
- L56 _public* enumerator_ `Failure` — Badge failed
- L61 _public* enumerator_ `Warning` — Badge produced a warning
- L66 _public* enumerator_ `Success` — Badge succeeded
- L71 _public* enumerator_ `Skipped` — Badge was skipped

#### class `EpicGames.Horde.Ugs.AddUgsBadgeRequest`  
`public class AddUgsBadgeRequest`  
_public; L77-94_
- desc: Adds a new badge to the change
- L83 _public property_ `public string Name { get; set; }` — attrs: `[Required]` — Name of the badge
- L88 _public property_ `public Uri? Url { get; set; }` — Url for the badge
- L93 _public property_ `public UgsBadgeState State { get; set; }` — Current status of the badge

#### class `EpicGames.Horde.Ugs.AddUgsMetadataRequest`  
`public class AddUgsMetadataRequest`  
_public; L99-152_
- desc: Request object for adding new metadata to the server
- L105 _public property_ `public string Stream { get; set; }` — attrs: `[Required]` — The stream name
- L111 _public property_ `public int Change { get; set; }` — attrs: `[Required]` — The changelist number
- L116 _public property_ `public string? Project { get; set; }` — The project name
- L121 _public property_ `public string? UserName { get; set; }` — Name of the current user
- L126 _public property_ `public bool? Synced { get; set; }` — Whether this changelist has been synced by the user
- L131 _public property_ `public UgsUserVote? Vote { get; set; }` — State of the user
- L136 _public property_ `public bool? Starred { get; set; }` — New starred state for the issue
- L141 _public property_ `public bool? Investigating { get; set; }` — Whether the user is investigating
- L146 _public property_ `public string? Comment { get; set; }` — Comment for this change
- L151 _public property_ `public List<AddUgsBadgeRequest>? Badges { get; set; }` — List of badges to add

#### class `EpicGames.Horde.Ugs.GetUgsUserResponse`  
`public class GetUgsUserResponse`  
_public; L157-188_
- desc: Information about a user synced to a change
- L162 _public property_ `public string User { get; set; }` — Name of the user
- L167 _public property_ `public long? SyncTime { get; set; }` — Time that the change was synced
- L172 _public property_ `public UgsUserVote? Vote { get; set; }` — State of the user
- L177 _public property_ `public string? Comment { get; set; }` — Comment by this user
- L182 _public property_ `public bool? Investigating { get; set; }` — Whether the user is investigating this change
- L187 _public property_ `public bool? Starred { get; set; }` — Whether this changelist is starred

#### class `EpicGames.Horde.Ugs.GetUgsBadgeResponse`  
`public class GetUgsBadgeResponse`  
_public; L193-209_
- desc: Information about a badge
- L198 _public property_ `public string Name { get; set; }` — Name of the badge
- L203 _public property_ `public Uri? Url { get; set; }` — Url for the badge
- L208 _public property_ `public UgsBadgeState State { get; set; }` — Current status of the badge

#### class `EpicGames.Horde.Ugs.GetUgsMetadataResponse`  
`public class GetUgsMetadataResponse`  
_public; L214-235_
- desc: Response object for querying metadata
- L219 _public property_ `public int Change { get; set; }` — Number of the changelist
- L224 _public property_ `public string? Project { get; set; }` — The project name
- L229 _public property_ `public List<GetUgsUserResponse>? Users { get; set; }` — Information about a user synced to this change
- L234 _public property_ `public List<GetUgsBadgeResponse>? Badges { get; set; }` — Badges for this change

#### class `EpicGames.Horde.Ugs.GetUgsMetadataListResponse`  
`public class GetUgsMetadataListResponse`  
_public; L240-251_
- desc: Response object for querying metadata
- L245 _public property_ `public long SequenceNumber { get; set; }` — Last time that the metadata was modified
- L250 _public property_ `public List<GetUgsMetadataResponse> Items { get; set; }` — List of changes matching the requested criteria

#### enum `EpicGames.Horde.Ugs.UgsIssueBuildOutcome`  
`public enum UgsIssueBuildOutcome`  
_public; L256-277_
- desc: Outcome of a particular build
- L261 _public* enumerator_ `Unknown` — Unknown outcome
- L266 _public* enumerator_ `Success` — Build succeeded
- L271 _public* enumerator_ `Error` — Build failed
- L276 _public* enumerator_ `Warning` — Build finished with warnings

#### class `EpicGames.Horde.Ugs.GetUgsIssueBuildResponse`  
`public class GetUgsIssueBuildResponse`  
_public; L282-341_
- desc: Legacy response describing a build
- L287 _public property_ `public long Id { get; set; }` — Identifier for this build
- L292 _public property_ `public string Stream { get; set; }` — Path to the stream containing this build
- L297 _public property_ `public int Change { get; set; }` — The changelist number for this build
- L302 _public property_ `public string? JobName { get; set; }` — Name of this job
- L307 _public property_ `public Uri? JobUrl { get; set; }` — Link to the job
- L312 _public property_ `public string? JobStepName { get; set; }` — Name of the job step
- L317 _public property_ `public Uri? JobStepUrl { get; set; }` — Link to the job step
- L322 _public property_ `public Uri? ErrorUrl { get; set; }` — Url for this particular error
- L327 _public property_ `public int Outcome { get; set; }` — Outcome of this build (see IssueBuildOutcome)
- L335-340 _public ctor_ `public GetUgsIssueBuildResponse(string stream, int change, IssueBuildOutcome outcome)`

#### class `EpicGames.Horde.Ugs.GetUgsIssueDiagnosticResponse`  
`public class GetUgsIssueDiagnosticResponse`  
_public; L346-375_
- desc: Information about a diagnostic
- L351 _public property_ `public long? BuildId { get; set; }` — The corresponding build id
- L356 _public property_ `public string Message { get; set; }` — Message for the diagnostic
- L361 _public property_ `public Uri Url { get; set; }` — Link to the error
- L369-374 _public ctor_ `public GetUgsIssueDiagnosticResponse(long? buildId, string message, Uri url)` — Constructor

#### class `EpicGames.Horde.Ugs.GetUgsIssueResponse`  
`public class GetUgsIssueResponse`  
_public; L380-456_
- desc: Stores information about a build health issue
- L385 _public property_ `public int Version { get; set; }` — Version number for this response
- L390 _public property_ `public int Id { get; set; }` — The unique object id
- L395 _public property_ `public DateTime CreatedAt { get; set; }` — Time at which the issue was created
- L400 _public property_ `public DateTime RetrievedAt { get; set; }` — Time at which the issue was retrieved
- L405 _public property_ `public string? Project { get; set; }` — The associated project for the issue
- L410 _public property_ `public string Summary { get; set; }` — The summary text for this issue
- L415 _public property_ `public string? Owner { get; set; }` — Owner of the issue
- L420 _public property_ `public string? NominatedBy { get; set; }` — User that nominated the current owner
- L425 _public property_ `public DateTime? AcknowledgedAt { get; set; }` — Time that the issue was acknowledged
- L430 _public property_ `public int? FixChange { get; set; }` — Changelist that fixed this issue
- L435 _public property_ `public DateTime? ResolvedAt { get; set; }` — Time at which the issue was resolved
- L440 _public property_ `public bool BNotify { get; set; }` — Whether to notify the user about this issue
- L445 _public property_ `public bool BWarning { get; set; }` — Whether this issue just contains warnings
- L450 _public property_ `public Uri? BuildUrl { get; set; }` — Link to the last build
- L455 _public property_ `public List<string> Streams { get; set; }` — List of streams affected by this issue

#### class `EpicGames.Horde.Ugs.UpdateUgsIssueRequest`  
`public class UpdateUgsIssueRequest`  
_public; L461-497_
- desc: Request an issue to be updated
- L466 _public property_ `public string? Owner { get; set; }` — New owner of the issue
- L471 _public property_ `public string? NominatedBy { get; set; }` — User than nominates the new owner
- L476 _public property_ `public bool? Acknowledged { get; set; }` — Whether the issue has been acknowledged
- L481 _public property_ `public string? DeclinedBy { get; set; }` — Name of the user that declines the issue
- L486 _public property_ `public int? FixChange { get; set; }` — The change at which the issue is claimed fixed. 0 = not fixed, -1 = systemic issue.
- L491 _public property_ `public bool? Resolved { get; set; }` — Whether the issue should be marked as resolved
- L496 _public property_ `public string? ResolvedBy { get; set; }` — Name of the user that resolved the issue

### `Source/Programs/Shared/EpicGames.Horde/Users/UserId.cs` (EpicGames.Horde)


#### record struct `EpicGames.Horde.Users.UserId`  
`public readonly record struct UserId(BinaryId Id)`  
_public; L16-48_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(BinaryIdTypeConverter<UserId, UserIdConverter>))] [BinaryIdConverter(typeof(UserIdConverter))]`
- desc: Identifier for a user
- L21 _public property_ `public static UserId Empty { get; }` — Constant value for empty user id
- L26 _public property_ `public static UserId Anonymous { get; }` — Special user id for an anonymous administrator
- L29 _public method_ `public static UserId Parse(string text)` — (inheritdoc)
- L32-44 _public method_ `public static bool TryParse(string text, out UserId id)` — (inheritdoc)
- L47 _public method_ `public override readonly string ToString()` — (inheritdoc)

#### class `EpicGames.Horde.Users.UserIdConverter`  
`class UserIdConverter : BinaryIdConverter<UserId>`  
_internal*; L53-60_
- inherits: `BinaryIdConverter<UserId>`
- desc: Converter to and from BinaryId instances.
- L56 _public method_ `public override UserId FromBinaryId(BinaryId id)` — (inheritdoc)
- L59 _public method_ `public override BinaryId ToBinaryId(UserId value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Horde/Users/UserMessages.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Users.GetUserResponse`  
`public class GetUserResponse`  
_public; L14-99_
- desc: Response describing the current user
- L19 _public property_ `public UserId Id { get; set; }` — Id of the user
- L24 _public property_ `public string Name { get; set; }` — Name of the user
- L29 _public property_ `public string? Image24 { get; set; }` — Avatar image URL (24px)
- L34 _public property_ `public string? Image32 { get; set; }` — Avatar image URL (32px)
- L39 _public property_ `public string? Image48 { get; set; }` — Avatar image URL (48px)
- L44 _public property_ `public string? Image72 { get; set; }` — Avatar image URL (72px)
- L49 _public property_ `public string? Email { get; set; }` — Email of the user
- L54 _public property_ `public List<GetUserClaimResponse>? Claims { get; set; }` — Claims for the user
- L59 _public property_ `public bool? EnableExperimentalFeatures { get; set; }` — Whether to enable experimental features for this user
- L64 _public property_ `public bool? AlwaysTagPreflightCL { get; set; }` — Whether to always tag preflight changelists
- L69 _public property_ `public object? DashboardSettings { get; set; }` — Settings for the dashboard
- L74 _public property_ `public GetDashboardFeaturesResponse? DashboardFeatures { get; set; }` — Settings for whether various dashboard features should be shown for the current user
- L79 _public property_ `public List<GetJobTemplateSettingsResponse>? JobTemplateSettings { get; set; }` — User job template preferences
- L84 _public property_ `public List<string>? PinnedJobIds { get; set; }` — List of pinned job ids
- L89 _public property_ `public List<string>? PinnedBisectTaskIds { get; set; }` — List of pinned bisection task ids
- L94-98 _public ctor_ `public GetUserResponse(UserId id, string name)` — Constructor

#### class `EpicGames.Horde.Users.GetUserClaimResponse`  
`public class GetUserClaimResponse`  
_public; L104-124_
- desc: New claim document
- L109 _public property_ `public string Type { get; set; }` — Type of the claim
- L114 _public property_ `public string Value { get; set; }` — Value for the claim
- L119-123 _public ctor_ `public GetUserClaimResponse(string type, string value)` — Constructor

#### class `EpicGames.Horde.Users.UserAclPermission`  
`public class UserAclPermission`  
_public; L129-155_
- desc: Resolved permissions for an action in a given ACL scope
- L134 _public property_ `public string Scope { get; set; }` — Scope name
- L139 _public property_ `public string Action { get; set; }` — Action name
- L144 _public property_ `public bool IsAuthorized { get; set; }` — Whether action is authorized in given scope
- L149-154 _public ctor_ `public UserAclPermission(string scope, string action, bool isAuthorized)` — Constructor

#### class `EpicGames.Horde.Users.GetUserAclPermissionsResponse`  
`public class GetUserAclPermissionsResponse`  
_public; L160-174_
- desc: Resolved permissions for ACL scopes for a given user
- L165 _public property_ `public List<UserAclPermission> AclPermissions { get; set; }` — List of ACL permissions
- L170-173 _public ctor_ `public GetUserAclPermissionsResponse(List<UserAclPermission> aclPermissions)` — Constructor

#### class `EpicGames.Horde.Users.GetJobTemplateSettingsResponse`  
`public class GetJobTemplateSettingsResponse`  
_public; L179-217_
- desc: Job template settings for the current user
- L184 _public property_ `public string StreamId { get; set; }` — The stream the job was run in
- L189 _public property_ `public string TemplateId { get; set; }` — The template id of the job
- L194 _public property_ `public string TemplateHash { get; set; }` — The hash of the template definition
- L199 _public property_ `public List<string> Arguments { get; set; }` — The arguments defined when creating the job
- L204 _public property_ `public DateTimeOffset UpdateTimeUtc { get; set; }` — The last update time of the job template
- L209-216 _public ctor_ `public GetJobTemplateSettingsResponse(string streamId, string templateId, string templateHash, List<string> arguments, DateTime updateTimeUtc)` — Constructor

#### class `EpicGames.Horde.Users.GetDashboardFeaturesResponse`  
`public class GetDashboardFeaturesResponse`  
_public; L222-283_
- desc: Settings for whether various features should be enabled on the dashboard
- L227 _public property_ `public bool ShowLandingPage { get; set; }` — Navigate to the landing page by default
- L232 _public property_ `public string LandingPageRoute { get; set; }` — Custom landing page route to direct users to
- L237 _public property_ `public bool ShowCI { get; set; }` — Enable CI functionality
- L242 _public property_ `public bool ShowAgents { get; set; }` — Whether to show functionality related to agents, pools, and utilization on the dashboard.
- L247 _public property_ `public bool ShowAgentRegistration { get; set; }` — Whether to show the agent registration page. When using registration tokens from elsewhere this is not needed.
- L252 _public property_ `public bool ShowPerforceServers { get; set; }` — Show the Perforce server option on the server menu
- L257 _public property_ `public bool ShowDeviceManager { get; set; }` — Show the device manager on the server menu
- L262 _public property_ `public bool ShowTests { get; set; }` — Show automated tests (legacy) on the server menu
- L267 _public property_ `public bool ShowAccounts { get; set; }` — Whether the remote desktop button should be shown on the agent modal
- L272 _public property_ `public bool ShowNoticeEditor { get; set; }` — Whether the notice editor should be listed in the server menu
- L277 _public property_ `public bool ShowPoolEditor { get; set; }` — Whether controls for modifying pools should be shown
- L282 _public property_ `public bool ShowRemoteDesktop { get; set; }` — Whether the remote desktop button should be shown on the agent modal

#### class `EpicGames.Horde.Users.GetThinUserInfoResponse`  
`public class GetThinUserInfoResponse`  
_public; L288-320_
- desc: Basic information about a user. May be embedded in other responses.
- L293 _public property_ `public UserId Id { get; set; }` — Id of the user
- L298 _public property_ `public string Name { get; set; }` — Name of the user
- L303 _public property_ `public string? Email { get; set; }` — The user's email address
- L308 _public property_ `public string? Login { get; set; }` — The user login [DEPRECATED]
- L313-319 _public ctor_ `public GetThinUserInfoResponse(UserId id, string name, string? email, string? login)` — Constructor

#### class `EpicGames.Horde.Users.UpdateUserRequest`  
`public class UpdateUserRequest`  
_public; L325-361_
- desc: Request to update settings for a user
- L330 _public property_ `public bool? EnableExperimentalFeatures { get; set; }` — Whether to enable experimental features for this user
- L335 _public property_ `public bool? AlwaysTagPreflightCL { get; set; }` — Whether to always tag preflight CL
- L340 _public property_ `public JsonElement? DashboardSettings { get; set; }` — New dashboard settings
- L345 _public property_ `public List<string>? AddPinnedJobIds { get; set; }` — Job ids to add to the pinned list
- L350 _public property_ `public List<string>? RemovePinnedJobIds { get; set; }` — Jobs ids to remove from the pinned list
- L355 _public property_ `public List<string>? AddPinnedBisectTaskIds { get; set; }` — Bisection task ids to add to the pinned list
- L360 _public property_ `public List<string>? RemovePinnedBisectTaskIds { get; set; }` — Bisection task ids to remove from the pinned list

### `Source/Programs/Shared/EpicGames.Horde/Utilities/ConfigDocAttribute.cs` (EpicGames.Horde)


#### class `HordeServer.Utilities.ConfigDocAttribute`  
`public sealed class ConfigDocAttribute : Attribute`  
_public; L11-42_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute indicating that an object should generate a schema doc page
- L16 _public property_ `public string Title { get; }` — Page title
- L21 _public property_ `public string LinkRail { get; }` — Rail to show with breadcrumbs at the top of the page
- L26 _public property_ `public string FileName { get; }` — Output filename
- L31 _public property_ `public string? Introduction { get; set; }` — Optional introductory text on the page
- L36-41 _public ctor_ `public ConfigDocAttribute(string title, string linkRail, string fileName)` — Constructor

### `Source/Programs/Shared/EpicGames.Horde/Utilities/HordeEnvVars.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.HordeEnvKeys`  
`public static class HordeEnvKeys`  
_public; L19-34_
- desc: Contains the environment variable names for common Horde environment variables. These are meant to be used by any and all C# code that is NOT Horde itself. If these keys were used by Horde itself then as soon as a changes to them was committed our tooling would break until Horde was actually deployed.
- L21 _public const_ `public const string BatchId = "UE_HORDE_BATCHID"`
- L22 _public const_ `public const string CleanupScriptPath = "UE_HORDE_CLEANUP"`
- L23 _public const_ `public const string GraphUpdatePath = "UE_HORDE_GRAPH_UPDATE"`
- L24 _public const_ `public const string HordeToken = "UE_HORDE_TOKEN"`
- L25 _public const_ `public const string HordeUrl = "UE_HORDE_URL"`
- L26 _public const_ `public const string JobId = "UE_HORDE_JOBID"`
- L27 _public const_ `public const string LeaseCleanupScriptPath = "UE_HORDE_LEASE_CLEANUP"`
- L28 _public const_ `public const string SharedDirPath = "UE_HORDE_SHARED_DIR"`
- L29 _public const_ `public const string StepId = "UE_HORDE_STEPID"`
- L30 _public const_ `public const string StepName = "UE_HORDE_STEPNAME"`
- L31 _public const_ `public const string StreamId = "UE_HORDE_STREAMID"`
- L32 _public const_ `public const string TemplateId = "UE_HORDE_TEMPLATEID"`
- L33 _public const_ `public const string TemplateName = "UE_HORDE_TEMPLATENAME"`

#### class `EpicGames.Horde.Utilities.HordeEnvVars`  
`public static class HordeEnvVars`  
_public; L45-72_
- desc: Contains static references to common Horde environment variables. Note that for each of these we use expression bodied members so that the value of the environment variable is read again each time. Ideally no one would be changing any of these environment variables and this wouldn't be required, however we have no way to guarantee that doesn't happen (and in fact have seen cases where it does) and so we do this to be safe.
- L47 _public property_ `public static string? BatchId => ...`
- L48 _public property_ `public static string? CleanupScriptPath => ...`
- L49 _public property_ `public static string? GraphUpdatePath => ...`
- L50 _public property_ `public static string? HordeToken => ...`
- L51-63 _public property_ `public static Uri? HordeUrl { get; }`
- L64 _public property_ `public static string? JobId => ...`
- L65 _public property_ `public static string? LeaseCleanupScriptPath => ...`
- L66 _public property_ `public static string? SharedDirPath => ...`
- L67 _public property_ `public static string? StepId => ...`
- L68 _public property_ `public static string? StepName => ...`
- L69 _public property_ `public static string? StreamId => ...`
- L70 _public property_ `public static string? TemplateId => ...`
- L71 _public property_ `public static string? TemplateName => ...`

### `Source/Programs/Shared/EpicGames.Horde/Utilities/HordeRoutes.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.HordeRoutes`  
`public static class HordeRoutes`  
_public; L12-161_
- desc: Provides simple access to different Horde dashboard routes. The primary use case is when adding a link to Horde that is inserted into a log or report.
- L22-27 _public method_ `public static Uri JobPath(Uri hordeUrl, string jobId)` — Returns a System.Uri for a given Horde job. Example: https://horde.example.com/job/690b24e0c619fc760780db81
- L42-51 _public method_ `public static Uri JobPathFromEnv()` — Returns a System.Uri for a given Horde job with details taken from environment variables. Uses the following environment variables: - HordeEnvVars.HordeUrl - HordeEnvVars.JobId Example: https://horde.example.com/job/690b24e0c619fc760780db81
- L61-70 _public method_ `public static Uri StepPath(Uri hordeUrl, string jobId, string stepId)` — Returns a System.Uri for a given Horde step. Example: https://horde.example.com/job/690b24e0c619fc760780db81?step=ab17
- L86-97 _public method_ `public static Uri StepPathFromEnv()` — Returns a System.Uri for a given Horde step with details taken from environment variables. Uses the following environment variables: - HordeEnvVars.HordeUrl - HordeEnvVars.JobId - HordeEnvVars.StepId Example: https://horde.example.com/job/690b24e0c619fc760780db81?step=ab17
- L107-117 _public method_ `public static Uri TestAutomationPath(Uri hordeUrl, string jobId, string stepId)` — Returns a System.Uri for a given Horde test automation. Example: https://horde.example.com/test-automation?job-690b24e0c619fc760780db81&step=ab17
- L134-145 _public method_ `public static Uri TestAutomationPathFromEnv()` — Returns a System.Uri for a given Horde test automation with details taken from environment variables. Uses the following environment variables: - HordeEnvVars.HordeUrl - HordeEnvVars.JobId - HordeEnvVars.StepId Example: https://horde.example.com/test-automation?job-690b24e0c619fc760780db81&step=ab17
- L155-160 _public method_ `public static Uri LogPath(Uri hordeUrl, string logId)` — Returns a System.Uri for a given Horde log. Example: https://horde.example.com/log/690b24e0c619fc760780db81?step=ab17

### `Source/Programs/Shared/EpicGames.Horde/Utilities/IntervalJsonConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.IntervalJsonConverter`  
`public class IntervalJsonConverter : JsonConverter<TimeSpan>`  
_public; L13-109_
- inherits: `JsonConverter<TimeSpan>`
- desc: Converts TimeSpan intervals from formats like "30m", "1h30m", etc...
- L17 _private* field_ `static readonly TimeSuffix[] s_timeSuffixes = [ new TimeSuffix("w", TimeSpan.TicksPerDay * 7), new TimeSuffix("d", TimeSpan.TicksPerDay), new TimeSuffix("h", TimeSpan.TicksPerHour), new TimeSuffix("m", TimeSpan.TicksPerMinute), new TimeSuffix("s" ...`
- L27-30 _public method_ `public override TimeSpan Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L35-88 _public method_ `public static TimeSpan Parse(string? time)` — Parse a string as a time interval
- L91-108 _public method_ `public override void Write(Utf8JsonWriter writer, TimeSpan value, JsonSerializerOptions options)` — (inheritdoc)

#### record struct `EpicGames.Horde.Utilities.IntervalJsonConverter.TimeSuffix`  
`record struct TimeSuffix(string Text, long Ticks)`  
_private*; L15-15_

### `Source/Programs/Shared/EpicGames.Horde/Utilities/OpenTelemetry.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.OpenTelemetrySettings`  
`public class OpenTelemetrySettings`  
_public; L15-56_
- desc: OpenTelemetry configuration for collection and sending of traces and metrics.
- L20 _public property_ `public bool Enabled { get; set; }` — Whether OpenTelemetry exporting is enabled
- L25 _public property_ `public string ServiceName { get; set; }` — Service name
- L30 _public property_ `public string ServiceNamespace { get; set; }` — Service namespace
- L35 _public property_ `public string? ServiceVersion { get; set; }` — Service version
- L40 _public property_ `public bool EnableDatadogCompatibility { get; set; }` — Whether to enrich and format telemetry to fit presentation in Datadog
- L45 _public property_ `public Dictionary<string, string> Attributes { get; set; }` — Extra attributes to set
- L50 _public property_ `public bool EnableConsoleExporter { get; set; }` — Whether to enable the console exporter (for debugging purposes)
- L55 _public property_ `public Dictionary<string, OpenTelemetryProtocolExporterSettings> ProtocolExporters { get; set; }` — Protocol exporters (key is a unique and arbitrary name)

#### class `EpicGames.Horde.Utilities.OpenTelemetryProtocolExporterSettings`  
`public class OpenTelemetryProtocolExporterSettings`  
_public; L61-72_
- desc: Configuration for an OpenTelemetry exporter
- L66 _public property_ `public Uri? Endpoint { get; set; }` — Endpoint URL. Usually differs depending on protocol used.
- L71 _public property_ `public string Protocol { get; set; }` — Protocol for the exporter ('grpc' or 'httpprotobuf')

#### class `EpicGames.Horde.Utilities.OpenTelemetrySettingsExtensions`  
`public static class OpenTelemetrySettingsExtensions`  
_public; L77-108_
- desc: Provides extension methods for serializing and deserializing OpenTelemetrySettings
- L84-88 _public method_ `public static string Serialize(OpenTelemetrySettings settings, bool asBase64 = false)` — Serializes OpenTelemetrySettings to a JSON string, with an option to encode as base64
- L97-107 _public method_ `public static OpenTelemetrySettings Deserialize(string data, bool asBase64 = false)` — Deserializes a JSON string of OpenTelemetrySettings

### `Source/Programs/Shared/EpicGames.Horde/Utilities/PlatformFileLock.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.PlatformFileLock`  
`class PlatformFileLock : IDisposable`  
_internal*; L12-56_
- inherits: `IDisposable`
- desc: Wraps a semaphore controlling the number of open files at any time. Used to prevent exceeding handle limit on MacOS.
- L14 _private* field_ `static readonly SemaphoreSlim? s_semaphore = CreateSemaphore()`
- L16 _private* field_ `bool _locked`
- L18 _private ctor_ `private PlatformFileLock()`
- L25-33 _public method_ `public static async ValueTask<PlatformFileLock?> CreateAsync(CancellationToken cancellationToken)` — Acquire the platform file lock
- L36-43 _public method_ `public void Dispose()` — (inheritdoc)
- L45-55 _private* method_ `static SemaphoreSlim? CreateSemaphore()`

### `Source/Programs/Shared/EpicGames.Horde/Utilities/TimeOfDayJsonConverter.cs` (EpicGames.Horde)


#### class `EpicGames.Horde.Utilities.TimeOfDayJsonConverter`  
`public class TimeOfDayJsonConverter : JsonConverter<TimeSpan>`  
_public; L14-92_
- inherits: `JsonConverter<TimeSpan>`
- desc: Parses a time of day into a number of minutes since midnight
- L17-20 _public method_ `public override TimeSpan Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L23-26 _public method_ `public override void Write(Utf8JsonWriter writer, TimeSpan value, JsonSerializerOptions options)` — (inheritdoc)
- L31-85 _public method_ `public static TimeSpan Parse(string? text)` — Parse a string as a number of minutes since midnight
- L88-91 _private* method_ `static void ThrowInvalidTimeException(string? text)` — attrs: `[DoesNotReturn]`
