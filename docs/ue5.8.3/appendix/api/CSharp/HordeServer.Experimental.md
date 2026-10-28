# CSharp / HordeServer.Experimental

- project root: `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental`
- files: 9; symbols: 251
- symbol kinds: class=16, const=9, ctor=12, field=22, interface=5, method=123, property=62, record struct=1, struct=1
- access marked `*` is implicit (not written in source)

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/ExperimentalConfig.cs` (HordeServer.Experimental)


#### class `HordeServer.ExperimentalConfig`  
`public class ExperimentalConfig : IPluginConfig`  
_public; L14-66_
- inherits: `IPluginConfig`
- desc: Configuration for the experimental plugin
- L19 _public property_ `public List<NotificationConfig> Notifications { get; set; }` — Notifications to be sent on the Horde server
- L21 _private* field_ `readonly Dictionary<NotificationConfigId, NotificationConfig> _notificationConfigLookup = ...`
- L21 _private* field_ `readonly Dictionary< _notificationConfigLookup = new Dictionary<NotificationConfigId, NotificationConfig>()`
- L24-32 _public method_ `public void PostLoad(PluginConfigOptions configOptions)` — (inheritdoc)
- L43-65 _public method_ `public bool TryGetJobNofications(StreamId streamId, TemplateId templateId, [NotNullWhen(true)] out HashSet<JobNotificationConfig>? jobNotificationConfigs, List<StreamTag>? streamTags = null, bool includeDisabledConfigs = false)` — Attempt to get config for a given stream and template

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/ExperimentalPlugin.cs` (HordeServer.Experimental)


#### class `HordeServer.ExperimentalPlugin`  
`public class ExperimentalPlugin : IPluginStartup`  
_public; L17-37_
- attrs: `[Plugin("Experimental", EnabledByDefault = false, GlobalConfigType = typeof(ExperimentalConfig), ServerConfigType = typeof(ExperimentalServerConfig))]`
- inherits: `IPluginStartup`
- desc: Entry point for the experimental plugin
- L22-24 _public ctor_ `public ExperimentalPlugin()` — Constructor
- L27-29 _public method_ `public void Configure(IApplicationBuilder app)` — (inheritdoc)
- L32-36 _public method_ `public void ConfigureServices(IServiceCollection serviceCollection)` — (inheritdoc)

#### class `HordeServer.ExperimentalPluginExtensions`  
`public static class ExperimentalPluginExtensions`  
_public; L42-73_
- desc: Helper methods for experimental plugin config
- L47 _public method_ `public static void AddExperimentalConfig(this IDictionary<PluginName, IPluginConfig> dictionary, ExperimentalConfig experimentalConfig)` — Configures the experimental plugin
- L53 _public method_ `public static ExperimentalConfig GetExperimentalConfig(this IDictionary<PluginName, IPluginConfig> dictionary)` — Gets configuration for the experimental plugin
- L59-72 _public method_ `public static bool TryGetExperimentalConfig(this IDictionary<PluginName, IPluginConfig> dictionary, [NotNullWhen(true)] out ExperimentalConfig? experimentalConfig)` — Gets configuration for the experimental plugin

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/ExperimentalServerConfig.cs` (HordeServer.Experimental)


#### class `HordeServer.ExperimentalServerConfig`  
`public class ExperimentalServerConfig : PluginServerConfig`  
_public; L10-12_
- inherits: `PluginServerConfig`
- desc: Server configuration for the experimental plugin

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/IJobNotification.cs` (HordeServer.Experimental)


#### interface `HordeServer.Experimental.Notifications.IJobNotificationStateRef`  
`public interface IJobNotificationStateRef`  
_public; L12-43_
- desc: A job notification state reference
- L17 _public* property_ `ObjectId Id { get; }` — The job notification state identifier
- L22 _public* property_ `JobId JobId { get; }` — The job identifier
- L27 _public* property_ `TemplateId TemplateId { get; }` — The template identifier
- L32 _public* property_ `string Recipient { get; }` — The recipient of the notification
- L37 _public* property_ `string Channel { get; }` — The channel of the notification
- L42 _public* property_ `string Ts { get; }` — The timestamp of the notification

#### interface `HordeServer.Experimental.Notifications.IJobStepNotificationStateRef`  
`public interface IJobStepNotificationStateRef`  
_public; L48-114_
- desc: A job step notification state reference
- L53 _public* property_ `ObjectId Id { get; }` — The job notification state identifier
- L58 _public* property_ `JobId JobId { get; }` — The job identifier
- L63 _public* property_ `JobStepId JobStepId { get; set; }` — The job step identifier
- L68 _public* property_ `TemplateId TemplateId { get; }` — The template identifier
- L73 _public* property_ `string Recipient { get; }` — The recipient of the notification
- L78 _public* property_ `string Group { get; }` — The associated group of the notification
- L83 _public* property_ `string TargetPlatform { get; }` — The target platform of the notification
- L88 _public* property_ `string Badge { get; }` — The badge of the notification
- L93 _public* property_ `string Channel { get; }` — The channel of the notification
- L98 _public* property_ `string? ThreadTs { get; }` — The timestamp of the threaded notification
- L103 _public* property_ `string Ts { get; }` — The timestamp of the notification
- L108 _public* property_ `JobId? ParentJobId { get; }` — The parent job identifier
- L113 _public* property_ `TemplateId? ParentJobTemplateId { get; }` — The parent job template identifier

#### interface `HordeServer.Experimental.Notifications.IJobNotificationStateQueryBuilder`  
`public interface IJobNotificationStateQueryBuilder`  
_public; L119-169_
- desc: Builder to simplify the query generation for job notification states
- L126 _public method_ `public IJobNotificationStateQueryBuilder AddJobFilter(JobId jobId)` — Add the filter for a job
- L133 _public method_ `public IJobNotificationStateQueryBuilder AddJobFilters(List<JobId> jobIds)` — Adds a filter for a list of jobs
- L140 _public method_ `public IJobNotificationStateQueryBuilder AddTemplateFilter(TemplateId templateId)` — Add the filter for a template
- L147 _public method_ `public IJobNotificationStateQueryBuilder AddTemplateFilters(List<TemplateId> templateIds)` — Adds a filter for a list of templates
- L154 _public method_ `public IJobNotificationStateQueryBuilder AddRecipientFilter(string recipient)` — Add the filter for a specific recipient
- L161 _public method_ `public IJobNotificationStateQueryBuilder AddChannelFilter(string channel)` — Add the filter for a specific channel
- L168 _public method_ `public IJobNotificationStateQueryBuilder AddTimestampFilter(string ts)` — Add the filter for a timestamp

#### interface `HordeServer.Experimental.Notifications.IJobStepNotificationStateQueryBuilder`  
`public interface IJobStepNotificationStateQueryBuilder`  
_public; L174-274_
- desc: Builder to simplify the query generation for job step notification states
- L181 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobFilter(JobId jobId)` — Add the filter for a job
- L188 _public method_ `public IJobStepNotificationStateQueryBuilder AddTemplateFilter(TemplateId templateId)` — Add the filter for a template
- L195 _public method_ `public IJobStepNotificationStateQueryBuilder AddRecipientFilter(string recipient)` — Add the filter for a specific recipient
- L202 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobStepFilter(JobStepId jobStepId)` — Add the filter for a job step
- L209 _public method_ `public IJobStepNotificationStateQueryBuilder AddGroupFilter(string group)` — Add the filter for a specific group
- L216 _public method_ `public IJobStepNotificationStateQueryBuilder AddPlatformFilter(string platform)` — Add the filter for a specific platform
- L224 _public method_ `public IJobStepNotificationStateQueryBuilder AddBadgeFilter(string badge, bool shouldMatch)` — Add the filter for a specific badge
- L231 _public method_ `public IJobStepNotificationStateQueryBuilder AddChannelFilter(string channel)` — Add the filter for a specific channel
- L238 _public method_ `public IJobStepNotificationStateQueryBuilder AddThreadTimestampFilter(string threadTs)` — Add the filter for a threaded timestamp
- L245 _public method_ `public IJobStepNotificationStateQueryBuilder AddTimestampFilter(string ts)` — Add the filter for a timestamp
- L252 _public method_ `public IJobStepNotificationStateQueryBuilder AddParentJobFilter(JobId jobId)` — Add the filter for a parent job
- L259 _public method_ `public IJobStepNotificationStateQueryBuilder AddParentJobTemplateFilter(TemplateId templateId)` — Add the filter for a parent template
- L266 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobAndParentJobFilter(JobId jobId)` — Add the filter for either a job or parent job
- L273 _public method_ `public IJobStepNotificationStateQueryBuilder AddTemplateAndParentTemplateFilter(TemplateId templateId)` — Add the filter for either a template or parent template

#### interface `HordeServer.Experimental.Notifications.IJobNotificationCollection`  
`public interface IJobNotificationCollection`  
_public; L279-358_
- desc: Collection of job notification documents
- L290 _public* method_ `Task<IJobNotificationStateRef?> GetJobNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — Fetches a single entity of IJobNotificationStateRef
- L298 _public* method_ `Task<IReadOnlyList<IJobNotificationStateRef>?> GetJobNotificationStatesAsync(IJobNotificationStateQueryBuilder builder, CancellationToken cancellationToken = default)` — Fetches a read only list of IJobNotificationStateRef
- L310 _public* method_ `Task<IJobNotificationStateRef> AddOrUpdateJobNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, string channel, string timestamp, CancellationToken cancellationToken = default)` — Add or update the IJobNotificationStateRef to the collection
- L320 _public* method_ `Task<long> DeleteJobNotificationStatesAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — Deletes a IJobNotificationStateRef from the collection
- L328 _public* method_ `Task<IReadOnlyList<IJobStepNotificationStateRef>?> GetJobStepNotificationStatesAsync(IJobStepNotificationStateQueryBuilder builder, CancellationToken cancellationToken = default)` — Fetches a read only list of IJobStepNotificationStateRef
- L347 _public* method_ `Task<IJobStepNotificationStateRef> AddOrUpdateJobStepNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, JobStepId jobStepId, string group, string platform, string badge, string channel, string ts, string? threadTs = null, JobId? parentJobId = null, TemplateId? parentJobTemplateId = null, CancellationToken cancellationToken = default)` — Add or update the IJobStepNotificationStateRef to the collection
- L357 _public* method_ `Task<long> DeleteJobStepNotificationStatesAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — Deletes IJobStepNotificationStateRef from the collection

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/JobNotificationCollection.cs` (HordeServer.Experimental)


#### class `HordeServer.Experimental.Notifications.JobNotificationCollection`  
`public class JobNotificationCollection : IJobNotificationCollection`  
_public; L17-477_
- inherits: `IJobNotificationCollection`
- desc: Wrapper around the job notifications collection in a Mongo DB
- L292 _private* field_ `readonly IMongoCollection<JobNotificationStateDocument> _jobNotificationStates`
- L293 _private* field_ `readonly IMongoCollection<JobStepNotificationStateDocument> _jobStepNotificationStates`
- L294 _private* field_ `readonly ILogger _logger`
- L299-310 _public ctor_ `public JobNotificationCollection(IMongoService mongoService, ILogger<JobNotificationCollection> logger)` — Constructor
- L318-321 _public method_ `public static IJobNotificationStateQueryBuilder CreateJobNotificationStateQueryBuilder()` — Creates a JobNotificationStateQueryBuilder for creating a JobNotificationStateDocument query filter
- L324-334 _public method_ `public async Task<IReadOnlyList<IJobNotificationStateRef>?> GetJobNotificationStatesAsync(IJobNotificationStateQueryBuilder builder, CancellationToken cancellationToken = default)` — (inheritdoc)
- L337-356 _public method_ `public async Task<IJobNotificationStateRef?> GetJobNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — (inheritdoc)
- L359-384 _public method_ `public async Task<IJobNotificationStateRef> AddOrUpdateJobNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, string channel, string timestamp, CancellationToken cancellationToken = default)` — (inheritdoc)
- L387-399 _public method_ `public async Task<long> DeleteJobNotificationStatesAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — (inheritdoc)
- L409-412 _public method_ `public static IJobStepNotificationStateQueryBuilder CreateJobStepNotificationStateQueryBuilder()` — Creates a JobStepNotificationStateQueryBuilder for creating a JobStepNotificationStateDocument query filter
- L415-428 _public method_ `public async Task<IReadOnlyList<IJobStepNotificationStateRef>?> GetJobStepNotificationStatesAsync(IJobStepNotificationStateQueryBuilder builder, CancellationToken cancellationToken = default)` — (inheritdoc)
- L431-459 _public method_ `public async Task<IJobStepNotificationStateRef> AddOrUpdateJobStepNotificationStateAsync(JobId jobId, TemplateId templateId, string recipient, JobStepId jobStepId, string group, string platform, string badge, string channel, string ts, string? threadTs = null, JobId? parentJobId = null, TemplateId? parentJobTemplateId = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L462-474 _public method_ `public async Task<long> DeleteJobStepNotificationStatesAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — (inheritdoc)

#### class `HordeServer.Experimental.Notifications.JobNotificationCollection.JobNotificationStateDocument`  
`class JobNotificationStateDocument : IJobNotificationStateRef`  
_private*; L22-59_
- inherits: `IJobNotificationStateRef`
- desc: MongoDB document for job notifications
- L25 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonId]`
- L28 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonElement("jid")]`
- L31 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[BsonElement("tid")]`
- L34 _public property_ `public string Recipient { get; set; }` — attrs: `[BsonElement("rcp")]`
- L37 _public property_ `public string Channel { get; set; }` — attrs: `[BsonElement("ch")]`
- L40 _public property_ `public string Ts { get; set; }` — attrs: `[BsonElement("ts")]`
- L43 _public property_ `public SlackMessageId MessageId => ...` — attrs: `[BsonIgnore]`
- L45-48 _private ctor_ `private JobNotificationStateDocument()`
- L50-58 _public ctor_ `public JobNotificationStateDocument(JobId jobId, TemplateId templateId, string recipient, string channel, string ts)`

#### class `HordeServer.Experimental.Notifications.JobNotificationCollection.JobStepNotificationStateDocument`  
`class JobStepNotificationStateDocument : IJobStepNotificationStateRef`  
_private*; L64-129_
- inherits: `IJobStepNotificationStateRef`
- desc: MongoDB document for job step notifications
- L67 _public property_ `public ObjectId Id { get; set; }` — attrs: `[BsonId]`
- L70 _public property_ `public JobId JobId { get; set; }` — attrs: `[BsonElement("jid")]`
- L73 _public property_ `public TemplateId TemplateId { get; set; }` — attrs: `[BsonElement("tid")]`
- L76 _public property_ `public string Recipient { get; set; }` — attrs: `[BsonElement("rcp")]`
- L79 _public property_ `public JobStepId JobStepId { get; set; }` — attrs: `[BsonElement("sid")]`
- L82 _public property_ `public string Group { get; set; }` — attrs: `[BsonElement("grp")]`
- L85 _public property_ `public string TargetPlatform { get; set; }` — attrs: `[BsonElement("plt")]`
- L88 _public property_ `public string Badge { get; set; }` — attrs: `[BsonElement("bdg")]`
- L91 _public property_ `public string Channel { get; set; }` — attrs: `[BsonElement("ch")]`
- L94 _public property_ `public string? ThreadTs { get; set; }` — attrs: `[BsonElement("tts")]`
- L97 _public property_ `public string Ts { get; set; }` — attrs: `[BsonElement("ts")]`
- L100 _public property_ `public JobId? ParentJobId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("pjid")]`
- L103 _public property_ `public TemplateId? ParentJobTemplateId { get; set; }` — attrs: `[BsonIgnoreIfNull, BsonElement("ptid")]`
- L106 _public property_ `public SlackMessageId MessageId => ...` — attrs: `[BsonIgnore]`
- L108-111 _private ctor_ `private JobStepNotificationStateDocument()`
- L113-128 _public ctor_ `public JobStepNotificationStateDocument(JobId jobId, TemplateId templateId, string recipient, JobStepId jobStepId, string group, string targetPlatform, string badge, string channel, string ts, string? tts = null, JobId? parentJobId = null, TemplateId? parentTemplateId = null)`

#### class `HordeServer.Experimental.Notifications.JobNotificationCollection.JobNotificationStateQueryBuilder`  
`class JobNotificationStateQueryBuilder : IJobNotificationStateQueryBuilder`  
_private*; L132-185_
- inherits: `IJobNotificationStateQueryBuilder`
- desc: (inheritdoc)
- L134 _public property_ `public FilterDefinition<JobNotificationStateDocument> Filter { get; set; }`
- L136 _private* field_ `readonly FilterDefinitionBuilder<JobNotificationStateDocument> _filterBuilder`
- L138-142 _public ctor_ `public JobNotificationStateQueryBuilder()`
- L144-148 _public method_ `public IJobNotificationStateQueryBuilder AddJobFilter(JobId jobId)`
- L150-154 _public method_ `public IJobNotificationStateQueryBuilder AddJobFilters(List<JobId> jobIds)`
- L156-160 _public method_ `public IJobNotificationStateQueryBuilder AddTemplateFilter(TemplateId templateId)`
- L162-166 _public method_ `public IJobNotificationStateQueryBuilder AddTemplateFilters(List<TemplateId> templateId)`
- L168-172 _public method_ `public IJobNotificationStateQueryBuilder AddRecipientFilter(string recipient)`
- L174-178 _public method_ `public IJobNotificationStateQueryBuilder AddChannelFilter(string channel)`
- L180-184 _public method_ `public IJobNotificationStateQueryBuilder AddTimestampFilter(string ts)`

#### class `HordeServer.Experimental.Notifications.JobNotificationCollection.JobStepNotificationStateQueryBuilder`  
`class JobStepNotificationStateQueryBuilder : IJobStepNotificationStateQueryBuilder`  
_private*; L188-290_
- inherits: `IJobStepNotificationStateQueryBuilder`
- desc: (inheritdoc)
- L190 _public property_ `public FilterDefinition<JobStepNotificationStateDocument> Filter { get; set; }`
- L192 _private* field_ `readonly FilterDefinitionBuilder<JobStepNotificationStateDocument> _filterBuilder`
- L194-198 _public ctor_ `public JobStepNotificationStateQueryBuilder()`
- L200-204 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobFilter(JobId jobId)`
- L206-210 _public method_ `public IJobStepNotificationStateQueryBuilder AddTemplateFilter(TemplateId templateId)`
- L212-216 _public method_ `public IJobStepNotificationStateQueryBuilder AddRecipientFilter(string recipient)`
- L218-222 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobStepFilter(JobStepId jobStepId)`
- L224-228 _public method_ `public IJobStepNotificationStateQueryBuilder AddGroupFilter(string group)`
- L230-234 _public method_ `public IJobStepNotificationStateQueryBuilder AddPlatformFilter(string platform)`
- L236-247 _public method_ `public IJobStepNotificationStateQueryBuilder AddBadgeFilter(string badge, bool shouldMatch)`
- L249-253 _public method_ `public IJobStepNotificationStateQueryBuilder AddChannelFilter(string channel)`
- L255-259 _public method_ `public IJobStepNotificationStateQueryBuilder AddThreadTimestampFilter(string threadTs)`
- L261-265 _public method_ `public IJobStepNotificationStateQueryBuilder AddTimestampFilter(string ts)`
- L267-271 _public method_ `public IJobStepNotificationStateQueryBuilder AddParentJobFilter(JobId jobId)`
- L273-277 _public method_ `public IJobStepNotificationStateQueryBuilder AddParentJobTemplateFilter(TemplateId templateId)`
- L279-283 _public method_ `public IJobStepNotificationStateQueryBuilder AddJobAndParentJobFilter(JobId jobId)`
- L285-289 _public method_ `public IJobStepNotificationStateQueryBuilder AddTemplateAndParentTemplateFilter(TemplateId templateId)`

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/NotificationConfig.cs` (HordeServer.Experimental)


#### class `HordeServer.NotificationFormatConfig`  
`public class NotificationFormatConfig`  
_public; L17-33_
- desc: Configuration for the format of the notification group
- L22 _public property_ `public string Group { get; set; }` — Name of the group
- L27 _public property_ `public string StepPattern { get; set; }` — Regex pattern to determine if a job step belongs within the group
- L32 _public property_ `public string? AlternativeNamePattern { get; set; }` — Optional regex pattern to override the JobNotificationConfig.NamePattern

#### class `HordeServer.JobNotificationConfig`  
`public class JobNotificationConfig`  
_public; L38-97_
- desc: Configuration for the job notification
- L43 _public property_ `public bool Enabled { get; set; }` — Whether or not the current configuration is enabled
- L48 _public property_ `public TemplateId Template { get; set; }` — Identifier of the template this notification applies to
- L53 _public property_ `public string NamePattern { get; set; }` — Regex pattern used to extract name of the step this notification will use for display
- L58 _public property_ `public List<NotificationFormatConfig> NotificationFormats { get; set; }` — List of formats to be applied for this notification
- L63 _public property_ `public List<string> Channels { get; set; }` — List of Slack channel or user identifiers the notification will be sent to
- L72-96 _public method_ `public bool GetStepDetails(string stepName, out string? group, out string? name)` — Gets the group and platform information of the corresponding step within the list of notification formats

#### class `HordeServer.NotificationStreamConfig`  
`public class NotificationStreamConfig`  
_public; L102-147_
- desc: Config for the notifications based on the streams
- L107 _public property_ `public List<StreamId> Streams { get; set; }` — List of streams for this notification
- L112 _public property_ `public List<string> EnabledStreamTags { get; set; }` — List of enabled tags for a stream for this notification
- L117 _public property_ `public List<JobNotificationConfig> JobNotifications { get; set; }` — Configuration for sending experimental Job Summary Slack notifications
- L119 _private* field_ `readonly Dictionary<TemplateId, List<JobNotificationConfig>> _notificationLookup = ...`
- L119 _private* field_ `readonly Dictionary< _notificationLookup = new Dictionary<TemplateId, List<JobNotificationConfig>>()`
- L124-137 _public method_ `public void PostLoad()` — Called after the store has been deserialized to compute cached values
- L145 _public method_ `public bool TryGetTemplateConfigs(TemplateId templateId, [NotNullWhen(true)] out List<JobNotificationConfig>? notificationConfigList)` — Attempt to get config for a given template

#### class `HordeServer.NotificationConfig`  
`public class NotificationConfig`  
_public; L157-291_
- attrs: `[JsonSchema("https://unrealengine.com/horde/notification")] [JsonSchemaCatalog("Horde Notifications", "Horde notification configuration file", new[] { "*.notification.json", "Notifications/*.json" })] [ConfigDoc("*.notification.json", "[Horde](../../../README.md) > [Configuration](../../Config.md)", "Config/Schema/Notification.md")] [ConfigIncludeRoot] [ConfigMacroScope]`
- desc: Config for notifications
- L162 _public property_ `public NotificationConfigId Id { get; set; }` — Identifier for this store
- L167 _public property_ `public List<NotificationStreamConfig> NotificationStreams { get; set; }` — Streams for the notifications to be sent on the Horde server
- L172 _public property_ `public List<ConfigInclude> Include { get; set; }` — Includes for other configuration files
- L174 _private* field_ `readonly Dictionary<StreamId, HashSet<NotificationStreamConfig>> _streamLookup = ...`
- L174 _private* field_ `readonly Dictionary< _streamLookup = new Dictionary<StreamId, HashSet<NotificationStreamConfig>>()`
- L175 _private* field_ `readonly Dictionary<string, HashSet<NotificationStreamConfig>> _streamTagLookup = ...`
- L175 _private* field_ `readonly Dictionary< _streamTagLookup = new Dictionary<string, HashSet<NotificationStreamConfig>>()`
- L180-210 _public method_ `public void PostLoad()` — Called after the store has been deserialized to compute cached values
- L220-246 _public method_ `public bool TryGetJobNofications(StreamId streamId, TemplateId templateId, [NotNullWhen(true)] out HashSet<JobNotificationConfig>? jobNotificationConfigs, bool includeDisabledConfigs = false)` — Attempt to get config for a given stream and template
- L256-290 _public method_ `public bool TryGetJobNofications(List<StreamTag> streamTags, TemplateId templateId, [NotNullWhen(true)] out HashSet<JobNotificationConfig>? jobNotificationConfigs, bool includeDisabledConfigs = false)` — Attempt to get config for a given list of stream tags and template

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/NotificationConfigId.cs` (HordeServer.Experimental)


#### record struct `HordeServer.NotificationConfigId`  
`public readonly record struct NotificationConfigId(StringId Id)`  
_public; L19-38_
- attrs: `[LogValueType] [JsonSchemaString] [TypeConverter(typeof(StringIdTypeConverter<NotificationConfigId, NotificationStoreIdConverter>))] [StringIdConverter(typeof(NotificationStoreIdConverter))] [CbConverter(typeof(StringIdCbConverter<NotificationConfigId, NotificationStoreIdConverter>))]`
- desc: Identifier for a notification configuration
- L24 _public property_ `public static NotificationConfigId Default { get; }` — Default notification configuration identifier
- L29-31 _public ctor_ `public NotificationConfigId(string id) : this(new StringId(id))` — Constructor
- L34 _public property_ `public bool IsEmpty => ...` — (inheritdoc)
- L37 _public method_ `public override string ToString()` — (inheritdoc)

#### class `HordeServer.NotificationStoreIdConverter`  
`public class NotificationStoreIdConverter : StringIdConverter<NotificationConfigId>`  
_public; L43-50_
- inherits: `StringIdConverter<NotificationConfigId>`
- desc: Converter to and from StringId instances.
- L46 _public method_ `public override NotificationConfigId FromStringId(StringId id)` — (inheritdoc)
- L49 _public method_ `public override StringId ToStringId(NotificationConfigId value)` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/Sinks/ExperimentalSlackNotificationSink.cs` (HordeServer.Experimental)


#### class `HordeServer.Notifications.Sinks.ExperimentalSlackNotificationSink`  
`public sealed class ExperimentalSlackNotificationSink : INotificationSink, IDisposable`  
_public; L25-142_
- inherits: `INotificationSink, IDisposable`
- desc: Maintains a connection to Slack, in order to receive socket-mode notifications of user interactions
- L27 _private* field_ `readonly SlackNotificationProcessor _slackNotificationProcessor`
- L40-50 _public ctor_ `public ExperimentalSlackNotificationSink(IOptions<BuildServerConfig> buildServerConfig, IOptionsMonitor<BuildConfig> buildConfig, IOptionsMonitor<ExperimentalConfig> experimentalConfig, IJobNotificationCollection jobNotificationCollection, IJobCollection jobCollection, IUserCollection userCollection, IServerInfo serverInfo, ILogger<ExperimentalSlackNotificationSink> logger)` — Constructor
- L53 _public method_ `public Task NotifyConfigUpdateAsync(ConfigUpdateInfo info, CancellationToken cancellationToken)` — (inheritdoc)
- L57 _public method_ `public Task NotifyConfigUpdateFailureAsync(string errorMessage, string fileName, int? change = null, IUser? author = null, string? description = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L61 _public method_ `public Task NotifyDeviceServiceAsync(string message, IDevice? device = null, IDevicePool? pool = null, StreamConfig? streamConfig = null, IJob? job = null, IJobStep? step = null, INode? node = null, IUser? user = null, CancellationToken cancellationToken = default)` — (inheritdoc)
- L65 _public method_ `public Task NotifyIssueUpdatedAsync(IIssue issue, CancellationToken cancellationToken)` — (inheritdoc)
- L69-72 _public method_ `public async Task NotifyJobCompleteAsync(IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — (inheritdoc)
- L75 _public method_ `public Task NotifyJobCompleteAsync(IUser user, IJob job, IGraph graph, LabelOutcome outcome, CancellationToken cancellationToken)` — (inheritdoc)
- L79 _public method_ `public Task NotifyJobScheduledAsync(List<JobScheduledNotification> notifications, CancellationToken cancellationToken)` — (inheritdoc)
- L83-92 _public method_ `public async Task NotifyJobStepAbortedAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — (inheritdoc)
- L95-104 _public method_ `public async Task NotifyJobStepCompleteAsync(IEnumerable<IUser>? usersToNotify, IJob job, IJobStepBatch batch, IJobStep step, INode node, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken)` — (inheritdoc)
- L107 _public method_ `public Task NotifyLabelCompleteAsync(IUser user, IJob job, ILabel label, int labelIdx, LabelOutcome outcome, List<(string, JobStepOutcome, Uri)> stepData, CancellationToken cancellationToken)` — (inheritdoc)
- L111 _public method_ `public Task SendAgentReportAsync(AgentReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L116 _public method_ `public Task SendSessionConflictReportAsync(IReadOnlyList<(AgentId Id, int Count)> conflicts, CancellationToken cancellationToken)` — (inheritdoc)
- L120 _public method_ `public Task SendDeviceIssueReportAsync(DeviceIssueReport report, CancellationToken cancellationToken)` — (inheritdoc)
- L124 _public method_ `public Task SendIssueReportAsync(IssueReportGroup report, CancellationToken cancellationToken)` — (inheritdoc)
- L128 _public method_ `public Task NotifyTestHealthReportAsync(ITestHealthReport report, string recipient, string[]? carbonCopies, CancellationToken cancellationToken)` — (inheritdoc)
- L132 _public method_ `public Task<string?> GetDirectMessageLinkAsync(IReadOnlyList<UserId> userIds, CancellationToken cancellationToken = default)` — (inheritdoc)
- L136 _public method_ `public Task<string?> GetChannelLinkAsync(string channel, CancellationToken cancellationToken = default)` — (inheritdoc)
- L140 _public method_ `public void Dispose()` — (inheritdoc)

### `Source/Programs/Horde/Plugins/Experimental/HordeServer.Experimental/Notifications/SlackNotificationProcessor.cs` (HordeServer.Experimental)


#### class `HordeServer.Experimental.Notifications.SlackNotificationProcessor`  
`public sealed class SlackNotificationProcessor : IDisposable`  
_public; L22-1553_
- inherits: `IDisposable`
- desc: Processes notifications to be sent through the Slack API
- L41 _private* field_ `readonly IOptionsMonitor<BuildConfig> _buildConfig`
- L42 _private* field_ `readonly IOptionsMonitor<ExperimentalConfig> _experimentalConfig`
- L43 _private* field_ `readonly IJobNotificationCollection _jobNotificationCollection`
- L44 _private* field_ `readonly IJobCollection _jobCollection`
- L45 _private* field_ `readonly IUserCollection _userCollection`
- L46 _private* field_ `readonly IServerInfo _serverInfo`
- L47 _private* field_ `readonly ILogger _logger`
- L48 _private* field_ `readonly SlackClient? _slackClient`
- L54 _private* const_ `const string PendingBadge = ":large_blue_square:"` — Slack emoji used to emphasize state
- L55 _private* const_ `const string WarningBadge = ":large_yellow_square:"`
- L56 _private* const_ `const string FailureBadge = ":large_red_square:"`
- L57 _private* const_ `const string SkippedBadge = ":black_square:"`
- L58 _private* const_ `const string PassingBadge = ":large_green_square:"`
- L63 _private* const_ `const string AlertBadge = ":rotating_light:"` — Slack emoji used to emphasize an aborted job
- L68 _private* const_ `const int MaxEventMessages = 5` — Limit of logs to be provided in a Slack notification
- L73 _private* const_ `const int MaxBlockCharacterLength = 2048` — Length limit to avoid character limit on each individual block container from Slack
- L79 _private* const_ `const int MaxSlackBlocks = 10` — Block limit per Slack Context before an exception is thrown
- L92-113 _public ctor_ `public SlackNotificationProcessor(IOptions<BuildServerConfig> buildServerConfig, IOptionsMonitor<BuildConfig> buildConfig, IOptionsMonitor<ExperimentalConfig> experimentalConfig, IJobNotificationCollection jobNotificationCollection, IJobCollection jobCollection, IUserCollection userCollection, IServerInfo serverInfo, ILogger logger)` — Constructor
- L116 _public method_ `public void Dispose()` — (inheritdoc)
- L124-168 _public method_ `public async Task ProcessJobCompleteAsync(IJob job, CancellationToken cancellationToken = default)` — Processes a Job complete notification
- L177-196 _public method_ `public async Task ProcessJobStepAbortedAsync(IJob job, IJobStep step, CancellationToken cancellationToken = default)` — Processes a notification for a job step that has been canceled
- L206-210 _public method_ `public async Task ProcessJobStepCompleteAsync(IJob job, IJobStep step, List<ILogEventData> jobStepEventData, CancellationToken cancellationToken = default)` — Process a job step that has been completed
- L221-245 _private* method_ `async Task ProcessJobAsync(IJob job, JobNotificationConfig config, IJob? parentJob = null, CancellationToken cancellationToken = default)` — Search the job for steps to be included in the notifications based on the experimental plugin's global config
- L253-289 _private* method_ `async Task<bool> TryProcessSpawnJobCompleteNotificationAsync(IJob job, CancellationToken cancellationToken = default)` — Try to process the job complete notification as a spawned job
- L299-388 _private* method_ `async Task<bool> TryProcessSpawnJobSetupNotificationAsync(IJob job, IJobStep step, List<LogData> jobStepEventData, CancellationToken cancellationToken = default)` — Try to process the job setup notification as a spawned job
- L397-437 _private* method_ `async Task ProcessJobSetupNotificationAsync(IJob job, IJobStep step, List<LogData> jobStepEventData, CancellationToken cancellationToken = default)` — Process the job setup notification
- L446-546 _private* method_ `async Task ProcessJobStepCompleteNotificationAsync(IJob job, IJobStep step, List<LogData> jobStepEventData, CancellationToken cancellationToken = default)` — Process the job step completed notification
- L555-640 _private* method_ `async Task<HashSet<JobStepId>?> FindDependentJobStepIdsAsync(IJob job, JobStepId underlyingStepId, CancellationToken cancellationToken = default)` — Finds all dependent steps of the IJobStepNotificationStateRef
- L650-692 _private* method_ `async Task<bool> UpdatePendingJobStepNotificationsAsync(JobId jobId, TemplateId templateId, string recipient, CancellationToken cancellationToken = default)` — Syncs up the main job information with our current recorded steps
- L700-747 _private* method_ `async Task TryNotificationCleanupAsync(IJob job, string recipient, CancellationToken cancellationToken = default)` — Clean up notification states once all notifications have been sent
- L755-759 _private* method_ `static StreamConfig? GetStreamConfig(BuildConfig buildConfig, StreamId streamId)` — Fetch the latest stream config
- L766-769 _private* method_ `static string GetBranchFromStream(StreamConfig? streamConfig)` — Fetch the branch name from the stream
- L777-782 _private* method_ `static string GetBranchFromStream(BuildConfig buildConfig, StreamId streamId)` — Fetch the branch name from the stream
- L789-841 _private* method_ `static string GetBadgeForStep(IJobStep step)` — Determines the badge based on the job step's state and outcome
- L848-867 _private* method_ `static IJobStep? GetSetupStepFromJob(IJob? job)` — Fetch the setup job step
- L875-883 _private* method_ `static List<LogData> ExtractLogInformation(IJobStep step, List<ILogEventData> jobStepEventData)` — Parses list of ILogEventData into the generic LogData structure
- L899-929 _private* method_ `async Task<SlackMessage?> GenerateSlackSummaryMessageAsync(IJob job, string branch, string recipient, IJob? parentJob = null, string? abortedByUserName = null, CancellationToken cancellationToken = default)` — Create the job's summary message
- L940-993 _private* method_ `async Task SendSetupFailedSlackMessageAsync(IJob job, IJobStep step, string branch, List<LogData> jobStepEventData, HashSet<JobNotificationConfig> jobNotificationConfigs, CancellationToken cancellationToken = default)` — Send a notification on a job setup failure
- L1004-1034 _private* method_ `async Task SendSetupFailedSlackMessageToThreadAsync(IJob job, IJobStep step, List<LogData> jobStepEventData, string channel, string timestamp, CancellationToken cancellationToken = default)` — Send a threaded message on a job setup failure
- L1046-1099 _private* method_ `async Task SendSlackSummaryMessageAsync(IJob job, string branch, string recipient, IJobNotificationStateRef? jobNotificationState = null, IJob? parentJob = null, string? abortedByUserName = null, CancellationToken cancellationToken = default)` — Sends a Slack notification for the specified job
- L1109-1136 _private* method_ `async Task<SlackMessageId?> SendSlackThreadMessageAsync(SlackMessageId jobMessageId, IJobStepNotificationStateRef jobStepNotificationState, SlackMessage threadMessage, CancellationToken cancellationToken = default)` — Sends a Slack message to a new or existing thread
- L1147-1207 _private* method_ `async Task<bool> UpdateAndSendSlackNotificationsForStepAsync(IJob job, IJobStep step, List<LogData> jobStepEventData, IJobStep? underlyingStep = null, CancellationToken cancellationToken = default)` — Sends a Slack notification for the specified job step
- L1218-1344 _private* method_ `async Task<SlackMessage> CreateSlackSummaryNotificationAsync(IJob job, string branch, IReadOnlyList<IJobStepNotificationStateRef> jobStepNotificationStateDocuments, string? abortedByUserName = null, CancellationToken cancellationToken = default)` — Create the job's summary message
- L1352-1376 _private* method_ `void AddLogDataContext(ISlackBlockContainer slackBlockContainer, List<LogData> logData, LogId? logId = null)` — Adds a context to the Slack message with log details
- L1387-1440 _private* method_ `SlackMessage? GenerateSlackThreadMessage(IJobStep step, string badge, List<LogData> logData, string? headerOverride = null, IJobStep? underlyingStep = null)` — Create the job step informational threaded message
- L1448-1489 _private* method_ `void TryAddSpawnedJobSlackContext(SlackMessage message, string header, List<IJob> spawnedJobs)` — Attempts to add a Slack context to the SlackMessage
- L1498-1512 _private* method_ `static string GenerateSlackMessageTitle(IJob job, string branch, string? hordeJobURL = null)` — Generates the title for the summary messages
- L1519-1526 _private* method_ `static string SanitizeQuoteText(string text, int maxLength = MaxBlockCharacterLength)` — Sanitizes the text for a Slack quote message
- L1534-1550 _private* method_ `static void AddCancelledJobSlackContext(SlackMessage message, string text, string? cancellationReason = null)` — Adds a context to the Slack message with cancellation details

#### struct `HordeServer.Experimental.Notifications.SlackNotificationProcessor.LogData`  
`internal struct LogData`  
_internal; L28-39_
- desc: Structure for generic use of log reporting
- L30 _public property_ `public LogEventSeverity Severity { get; }`
- L31 _public property_ `public string Message { get; }`
- L32 _public property_ `public LogId? LogId { get; }`
- L33-38 _public ctor_ `public LogData(LogEventSeverity severity, string message, LogId? logId = null)`
