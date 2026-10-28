# CSharp / XLocLocalization.Automation

- project root: `Source/Programs/AutomationTool/XLocLocalization`
- files: 4; symbols: 428
- symbol kinds: class=24, ctor=14, enum=3, enumerator=28, field=126, interface=4, method=111, property=116, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/XLocLocalization/Properties/AssemblyInfo.cs` (XLocLocalization.Automation)
_(no declarations)_


### `Source/Programs/AutomationTool/XLocLocalization/XLocLocalizationProvider.cs` (XLocLocalization.Automation)


#### struct `EpicGames.XLocLocalization.XLocConfig`  
`public struct XLocConfig`  
_public; L23-29_
- L25 _public field_ `public string Server`
- L26 _public field_ `public string APIKey`
- L27 _public field_ `public string APISecret`
- L28 _public field_ `public string LocalizationId`

#### struct `EpicGames.XLocLocalization.XLocUtils`  
`public struct XLocUtils`  
_public; L31-57_
- L33-43 _public method_ `public static string MD5HashString(string Str)`
- L45-56 _public method_ `public static WebResponse GetWebResponse(WebRequest Request)`

#### class `EpicGames.XLocLocalization.XLocLocalizationProvider`  
`public abstract class XLocLocalizationProvider : LocalizationProvider`  
_public; L59-450_
- inherits: `LocalizationProvider`
- L61-65 _public ctor_ `public XLocLocalizationProvider(LocalizationProviderArgs InArgs) : base(InArgs)`
- L67-97 _public method_ `public async override Task DownloadProjectFromLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectImportInfo)`
- L99-238 _private method_ `private void DownloadLatestPOFile(XLocApiClient XLocApiClient, string AuthToken, string Culture, string Platform, ProjectImportExportInfo ProjectImportInfo)`
- L240-280 _public method_ `public async override Task UploadProjectToLocalizationProvider(string ProjectName, ProjectImportExportInfo ProjectExportInfo)`
- L282-318 _private method_ `private void UploadLatestPOFile(TransferServiceClient TransferServiceClient, string AuthToken, string Culture, string Platform, ProjectImportExportInfo ProjectExportInfo)`
- L320-345 _protected method_ `protected XLocApiClient CreateXLocApiClient()`
- L347-357 _protected method_ `protected TransferServiceClient CreateTransferServiceClient()`
- L359-362 _protected method_ `protected string RequestAuthToken(XLocApiClient XLocApiClient)`
- L364-387 _protected method_ `protected string RequestAuthTokenWithRetry(XLocApiClient XLocApiClient)`
- L389-392 _protected method_ `protected string RequestLatestBuild(XLocApiClient XLocApiClient, string AuthToken, string LanguageId, string RemoteFilename)`
- L394-415 _private method_ `private string GetXLocFilename(string BaseFilename, string Platform)`
- L417 _protected field_ `protected XLocConfig Config`
- L419-449 _protected method_ `virtual protected Dictionary<string, string> GetEpicCultureToXLocLanguageId()`

### `Source/Programs/AutomationTool/XLocLocalization/XLocService/TransferService.cs` (XLocLocalization.Automation)


#### class `XLoc.Contracts.GameFileUploadInfo`  
`public partial class GameFileUploadInfo : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L19-125_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="GameFileUploadInfo", Namespace="http://schemas.datacontract.org/2004/07/XLoc.Contracts")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L22 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L24 _private field_ `private bool CaseSensitiveField`
- L26 _private field_ `private string FileNameField`
- L28 _private field_ `private bool HistoricalTranslationField`
- L30 _private field_ `private string LanguageIdField`
- L32 _private field_ `private string LocalizationIdField`
- L34 _private field_ `private string PlatformIdField`
- L36-46 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L49-59 _public property_ `public bool CaseSensitive { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L62-72 _public property_ `public string FileName { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L75-85 _public property_ `public bool HistoricalTranslation { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L88-98 _public property_ `public string LanguageId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L101-111 _public property_ `public string LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L114-124 _public property_ `public string PlatformId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### interface `ITransferService`  
`public interface ITransferService`  
_public; L131-140_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")] [System.ServiceModel.ServiceContractAttribute(Namespace="urn:XLoc.Services", ConfigurationName="ITransferService")]`
- L136 _public* method_ `UploadGameFileResponse UploadGameFile(GameFileUploadMessage request)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/ITransferService/UploadGameFile", ReplyAction="urn:XLoc.Services/ITransferService/UploadGameFileResponse")]`
- L139 _public* method_ `System.Threading.Tasks.Task<UploadGameFileResponse> UploadGameFileAsync(GameFileUploadMessage request)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/ITransferService/UploadGameFile", ReplyAction="urn:XLoc.Services/ITransferService/UploadGameFileResponse")]`

#### class `GameFileUploadMessage`  
`public partial class GameFileUploadMessage`  
_public; L146-176_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")] [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)] [System.ServiceModel.MessageContractAttribute(WrapperName="GameFileUploadMessage", WrapperNamespace="urn:XLoc.Services", IsWrapped=true)]`
- L150 _public field_ `public string ApiKey` — attrs: `[System.ServiceModel.MessageHeaderAttribute(Namespace="urn:XLoc.Services")]`
- L153 _public field_ `public string AuthToken` — attrs: `[System.ServiceModel.MessageHeaderAttribute(Namespace="urn:XLoc.Services")]`
- L156 _public field_ `public XLoc.Contracts.GameFileUploadInfo FileMetaData` — attrs: `[System.ServiceModel.MessageHeaderAttribute(Namespace="urn:XLoc.Services")]`
- L159 _public field_ `public long Length` — attrs: `[System.ServiceModel.MessageHeaderAttribute(Namespace="urn:XLoc.Services")]`
- L162 _public field_ `public System.IO.Stream FileByteStream` — attrs: `[System.ServiceModel.MessageBodyMemberAttribute(Namespace="urn:XLoc.Services", Order=0)]`
- L164-166 _public ctor_ `public GameFileUploadMessage()`
- L168-175 _public ctor_ `public GameFileUploadMessage(string ApiKey, string AuthToken, XLoc.Contracts.GameFileUploadInfo FileMetaData, long Length, System.IO.Stream FileByteStream)`

#### class `UploadGameFileResponse`  
`public partial class UploadGameFileResponse`  
_public; L182-188_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")] [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)] [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]`
- L185-187 _public ctor_ `public UploadGameFileResponse()`

#### interface `ITransferServiceChannel`  
`public interface ITransferServiceChannel : ITransferService, System.ServiceModel.IClientChannel`  
_public; L191-193_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]`
- inherits: `ITransferService, System.ServiceModel.IClientChannel`

#### class `TransferServiceClient`  
`public partial class TransferServiceClient : System.ServiceModel.ClientBase<ITransferService>, ITransferService`  
_public; L197-257_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]`
- inherits: `System.ServiceModel.ClientBase<ITransferService>, ITransferService`
- L200-202 _public ctor_ `public TransferServiceClient()`
- L204-207 _public ctor_ `public TransferServiceClient(string endpointConfigurationName) : base(endpointConfigurationName)`
- L209-212 _public ctor_ `public TransferServiceClient(string endpointConfigurationName, string remoteAddress) : base(endpointConfigurationName, remoteAddress)`
- L214-217 _public ctor_ `public TransferServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : base(endpointConfigurationName, remoteAddress)`
- L219-222 _public ctor_ `public TransferServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : base(binding, remoteAddress)`
- L225-228 _private* method_ `UploadGameFileResponse ITransferService.UploadGameFile(GameFileUploadMessage request)` — attrs: `[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]`
- L230-239 _public method_ `public void UploadGameFile(string ApiKey, string AuthToken, XLoc.Contracts.GameFileUploadInfo FileMetaData, long Length, System.IO.Stream FileByteStream)`
- L242-245 _private* method_ `System.Threading.Tasks.Task<UploadGameFileResponse> ITransferService.UploadGameFileAsync(GameFileUploadMessage request)` — attrs: `[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]`
- L247-256 _public method_ `public System.Threading.Tasks.Task<UploadGameFileResponse> UploadGameFileAsync(string ApiKey, string AuthToken, XLoc.Contracts.GameFileUploadInfo FileMetaData, long Length, System.IO.Stream FileByteStream)`

### `Source/Programs/AutomationTool/XLocLocalization/XLocService/XLocApiService.cs` (XLocLocalization.Automation)


#### class `XLoc.Xml.Types.Version`  
`public partial class Version : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L24-85_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="Version", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L27 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L29 _private field_ `private System.Guid LocalizationIdField`
- L31 _private field_ `private System.Guid VersionIdField`
- L33 _private field_ `private string VersionNameField`
- L35-45 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L48-58 _public property_ `public System.Guid LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L61-71 _public property_ `public System.Guid VersionId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L74-84 _public property_ `public string VersionName { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.Language`  
`public partial class Language : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L90-136_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="Language", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L93 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L95 _private field_ `private string LanguageIdField`
- L97 _private field_ `private string LanguageNameField`
- L99-109 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L112-122 _public property_ `public string LanguageId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L125-135 _public property_ `public string LanguageName { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.Session`  
`public partial class Session : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L141-187_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="Session", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L144 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L146 _private field_ `private System.Guid AuthTokenField`
- L148 _private field_ `private XLoc.Xml.Types.UserAccount UserField`
- L150-160 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L163-173 _public property_ `public System.Guid AuthToken { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L176-186 _public property_ `public XLoc.Xml.Types.UserAccount User { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.UserAccount`  
`public partial class UserAccount : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L192-313_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="UserAccount", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L195 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L197 _private field_ `private string EmailField`
- L199 _private field_ `private string LanguageField`
- L201 _private field_ `private System.Guid LocalizationIdField`
- L203 _private field_ `private string NameField`
- L205 _private field_ `private string RoleField`
- L207 _private field_ `private int TimeZoneField`
- L209 _private field_ `private System.Guid UserIdField`
- L211-221 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L224-234 _public property_ `public string Email { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L237-247 _public property_ `public string Language { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L250-260 _public property_ `public System.Guid LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L263-273 _public property_ `public string Name { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L276-286 _public property_ `public string Role { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L289-299 _public property_ `public int TimeZone { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L302-312 _public property_ `public System.Guid UserId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.Localization`  
`public partial class Localization : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L318-409_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="Localization", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L321 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L323 _private field_ `private string DescriptionField`
- L325 _private field_ `private System.Guid LocalizationIdField`
- L327 _private field_ `private string NameField`
- L329 _private field_ `private string StatusField`
- L331 _private field_ `private XLoc.Xml.Types.LocalizationType TypeField`
- L333-343 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L346-356 _public property_ `public string Description { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L359-369 _public property_ `public System.Guid LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L372-382 _public property_ `public string Name { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L385-395 _public property_ `public string Status { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L398-408 _public property_ `public XLoc.Xml.Types.LocalizationType Type { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.LocalizationType`  
`public partial class LocalizationType : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L414-475_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="LocalizationType", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L417 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L419 _private field_ `private string DescriptionField`
- L421 _private field_ `private string NameField`
- L423 _private field_ `private System.Guid TypeIdField`
- L425-435 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L438-448 _public property_ `public string Description { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L451-461 _public property_ `public string Name { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L464-474 _public property_ `public System.Guid TypeId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.SearchRequest`  
`public partial class SearchRequest : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L480-751_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="SearchRequest", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L483 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L485 _private field_ `private string AuthTokenField`
- L487 _private field_ `private bool CaseSensitiveField`
- L489 _private field_ `private string FileField`
- L491 _private field_ `private bool FilterByPlatformField`
- L493 _private field_ `private XLoc.Xml.Types.FileGroup[] GroupField`
- L495 _private field_ `private bool IncludeContextField`
- L497 _private field_ `private string LanguageIdField`
- L499 _private field_ `private System.Guid LocalizationIdField`
- L501 _private field_ `private int MaxResultsField`
- L503 _private field_ `private XLoc.Xml.Types.OrderBy OrderByField`
- L505 _private field_ `private string PlatformField`
- L507 _private field_ `private bool SearchEnglishField`
- L509 _private field_ `private bool SearchRSIDField`
- L511 _private field_ `private string SearchStringField`
- L513 _private field_ `private bool SearchTranslationsField`
- L515 _private field_ `private int StartRowField`
- L517 _private field_ `private bool WildcardSearchField`
- L519-529 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L532-542 _public property_ `public string AuthToken { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L545-555 _public property_ `public bool CaseSensitive { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L558-568 _public property_ `public string File { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L571-581 _public property_ `public bool FilterByPlatform { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L584-594 _public property_ `public XLoc.Xml.Types.FileGroup[] Group { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L597-607 _public property_ `public bool IncludeContext { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L610-620 _public property_ `public string LanguageId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L623-633 _public property_ `public System.Guid LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L636-646 _public property_ `public int MaxResults { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L649-659 _public property_ `public XLoc.Xml.Types.OrderBy OrderBy { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L662-672 _public property_ `public string Platform { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L675-685 _public property_ `public bool SearchEnglish { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L688-698 _public property_ `public bool SearchRSID { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L701-711 _public property_ `public string SearchString { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L714-724 _public property_ `public bool SearchTranslations { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L727-737 _public property_ `public int StartRow { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L740-750 _public property_ `public bool WildcardSearch { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.FileGroup`  
`public partial class FileGroup : XLoc.Xml.Types.ActiveMember`  
_public; L756-833_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="FileGroup", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `XLoc.Xml.Types.ActiveMember`
- L759 _private field_ `private string DescriptionField`
- L761 _private field_ `private System.Guid FileGroupIdField`
- L763 _private field_ `private XLoc.Xml.Types.Localization LocalizationField`
- L765 _private field_ `private string NameField`
- L767 _private field_ `private bool SelectedField`
- L770-780 _public property_ `public string Description { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L783-793 _public property_ `public System.Guid FileGroupId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L796-806 _public property_ `public XLoc.Xml.Types.Localization Localization { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L809-819 _public property_ `public string Name { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L822-832 _public property_ `public bool Selected { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### enum `XLoc.Xml.Types.OrderBy`  
`public enum OrderBy : int`  
_public; L837-860_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="OrderBy", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `int`
- L841 _public* enumerator_ `Normal = 0` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L844 _public* enumerator_ `Unfinished = 1` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L847 _public* enumerator_ `LastChanged = 2` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L850 _public* enumerator_ `LastModifiedSource = 3` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L853 _public* enumerator_ `HighPriority = 4` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L856 _public* enumerator_ `UnrevisedStrings = 5` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L859 _public* enumerator_ `StringNumber = 6` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`

#### class `XLoc.Xml.Types.ActiveMember`  
`public partial class ActiveMember : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L867-898_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="ActiveMember", Namespace="urn:XLoc.Xml.Types")] [System.Runtime.Serialization.KnownTypeAttribute(typeof(XLoc.Xml.Types.GameFile))] [System.Runtime.Serialization.KnownTypeAttribute(typeof(XLoc.Xml.Ty`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L870 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L872 _private field_ `private bool IsActiveField`
- L874-884 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L887-897 _public property_ `public bool IsActive { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.GameFile`  
`public partial class GameFile : XLoc.Xml.Types.ActiveMember`  
_public; L903-1010_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="GameFile", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `XLoc.Xml.Types.ActiveMember`
- L906 _private field_ `private System.Guid GameFileIdField`
- L908 _private field_ `private XLoc.Xml.Types.Localization LocalizationField`
- L910 _private field_ `private string NameField`
- L912 _private field_ `private string NotesField`
- L914 _private field_ `private XLoc.Xml.Types.Platform PlatformField`
- L916 _private field_ `private string ResourcePrefixField`
- L918 _private field_ `private int WordCountField`
- L921-931 _public property_ `public System.Guid GameFileId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L934-944 _public property_ `public XLoc.Xml.Types.Localization Localization { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L947-957 _public property_ `public string Name { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L960-970 _public property_ `public string Notes { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L973-983 _public property_ `public XLoc.Xml.Types.Platform Platform { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L986-996 _public property_ `public string ResourcePrefix { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L999-1009 _public property_ `public int WordCount { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.Platform`  
`public partial class Platform : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1015-1106_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="Platform", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1018 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1020 _private field_ `private string DescriptionField`
- L1022 _private field_ `private XLoc.Xml.Types.Localization[] LocalizationsField`
- L1024 _private field_ `private System.Guid PlatformIdField`
- L1026 _private field_ `private string ReferenceField`
- L1028 _private field_ `private string TitleField`
- L1030-1040 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1043-1053 _public property_ `public string Description { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1056-1066 _public property_ `public XLoc.Xml.Types.Localization[] Localizations { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1069-1079 _public property_ `public System.Guid PlatformId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1082-1092 _public property_ `public string Reference { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1095-1105 _public property_ `public string Title { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.SearchResult`  
`public partial class SearchResult : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1111-1172_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="SearchResult", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1114 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1116 _private field_ `private ContextListData[] ContextField`
- L1118 _private field_ `private int RecordCountField`
- L1120 _private field_ `private XLoc.Xml.Types.LocalizedString[] StringsField`
- L1122-1132 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1135-1145 _public property_ `public ContextListData[] Context { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1148-1158 _public property_ `public int RecordCount { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1161-1171 _public property_ `public XLoc.Xml.Types.LocalizedString[] Strings { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.LocalizedString`  
`public partial class LocalizedString : XLoc.Xml.Types.BaseContract`  
_public; L1177-1404_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="LocalizedString", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `XLoc.Xml.Types.BaseContract`
- L1180 _private field_ `private string EditLinkField`
- L1182 _private field_ `private System.DateTime EnglishLastModifiedField`
- L1184 _private field_ `private string EnglishStringField`
- L1186 _private field_ `private string FileGroupNameField`
- L1188 _private field_ `private string LanguageField`
- L1190 _private field_ `private string LocalizationField`
- L1192 _private field_ `private System.Guid LocalizationIdField`
- L1194 _private field_ `private string LocalizedStringMemberField`
- L1196 _private field_ `private string PlatformTitleField`
- L1198 _private field_ `private string PriorityField`
- L1200 _private field_ `private int ResourceIdField`
- L1202 _private field_ `private string ResourceStringIdField`
- L1204 _private field_ `private string ResourceStringNumberField`
- L1206 _private field_ `private string StringIdField`
- L1208 _private field_ `private System.DateTime TranslationLastModifiedField`
- L1211-1221 _public property_ `public string EditLink { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1224-1234 _public property_ `public System.DateTime EnglishLastModified { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1237-1247 _public property_ `public string EnglishString { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1250-1260 _public property_ `public string FileGroupName { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1263-1273 _public property_ `public string Language { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1276-1286 _public property_ `public string Localization { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1289-1299 _public property_ `public System.Guid LocalizationId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1302-1312 _public property_ `public string LocalizedStringMember { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(Name="LocalizedString", IsRequired=true)]`
- L1315-1325 _public property_ `public string PlatformTitle { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1328-1338 _public property_ `public string Priority { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1341-1351 _public property_ `public int ResourceId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1354-1364 _public property_ `public string ResourceStringId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1367-1377 _public property_ `public string ResourceStringNumber { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1380-1390 _public property_ `public string StringId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1393-1403 _public property_ `public System.DateTime TranslationLastModified { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`

#### class `XLoc.Xml.Types.SessionFault`  
`public partial class SessionFault : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1409-1440_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="SessionFault", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1412 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1414 _private field_ `private string MessageField`
- L1416-1426 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1429-1439 _public property_ `public string Message { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `XLoc.Xml.Types.BaseContract`  
`public partial class BaseContract : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1446-1477_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="BaseContract", Namespace="urn:XLoc.Xml.Types")] [System.Runtime.Serialization.KnownTypeAttribute(typeof(XLoc.Xml.Types.LocalizedString))]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1449 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1451 _private field_ `private bool EncodedField`
- L1453-1463 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1466-1476 _public property_ `public bool Encoded { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### enum `XLoc.Xml.Types.ContextType`  
`public enum ContextType : int`  
_public; L1481-1531_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="ContextType", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `int`
- L1485 _public* enumerator_ `ItemSet = 0` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1488 _public* enumerator_ `Ability = 1` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1491 _public* enumerator_ `Statics = 2` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1494 _public* enumerator_ `Monster = 3` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1497 _public* enumerator_ `Quest = 4` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1500 _public* enumerator_ `Inventory = 5` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1503 _public* enumerator_ `Objective = 6` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1506 _public* enumerator_ `Zone = 7` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1509 _public* enumerator_ `ZoneArea = 8` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1512 _public* enumerator_ `Condition = 9` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1515 _public* enumerator_ `OCondition = 10` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1518 _public* enumerator_ `Waypoint = 11` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1521 _public* enumerator_ `ETalk = 12` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1524 _public* enumerator_ `ETalkString = 13` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1527 _public* enumerator_ `OQuest = 14` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1530 _public* enumerator_ `Unknown = 15` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`

#### class `XLoc.Xml.Types.SearchCriteria`  
`public partial class SearchCriteria : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1536-1642_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="SearchCriteria", Namespace="urn:XLoc.Xml.Types")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1539 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1541 _private field_ `private XLoc.Xml.Types.FileGroup[] FileGroupsField`
- L1543 _private field_ `private XLoc.Xml.Types.GameFile[] GamesField`
- L1545 _private field_ `private bool IsCacheExpiredField`
- L1547 _private field_ `private XLoc.Xml.Types.Language[] LanguagesField`
- L1549 _private field_ `private XLoc.Xml.Types.Localization[] LocalizationsField`
- L1551 _private field_ `private XLoc.Xml.Types.Platform[] PlatformsField`
- L1553-1563 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1566-1576 _public property_ `public XLoc.Xml.Types.FileGroup[] FileGroups { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1579-1589 _public property_ `public XLoc.Xml.Types.GameFile[] Games { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1592-1602 _public property_ `public bool IsCacheExpired { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1605-1615 _public property_ `public XLoc.Xml.Types.Language[] Languages { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1618-1628 _public property_ `public XLoc.Xml.Types.Localization[] Localizations { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1631-1641 _public property_ `public XLoc.Xml.Types.Platform[] Platforms { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `ContextListData`  
`public partial class ContextListData : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1649-1710_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="ContextListData", Namespace="")]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1652 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1654 _private field_ `private ContextListLine[] LinesField`
- L1656 _private field_ `private int ResourceIdField`
- L1658 _private field_ `private System.Guid StringIdField`
- L1660-1670 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1673-1683 _public property_ `public ContextListLine[] Lines { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1686-1696 _public property_ `public int ResourceId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1699-1709 _public property_ `public System.Guid StringId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### class `ContextListLine`  
`public partial class ContextListLine : object, System.Runtime.Serialization.IExtensibleDataObject`  
_public; L1744-1880_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="ContextListLine", Namespace="")] [System.Runtime.Serialization.KnownTypeAttribute(typeof(XLoc.Xml.Types.Version[]))] [System.Runtime.Serialization.KnownTypeAttribute(typeof(XLoc.Xml.Types.Version))]`
- inherits: `object, System.Runtime.Serialization.IExtensibleDataObject`
- L1747 _private field_ `private System.Runtime.Serialization.ExtensionDataObject extensionDataField`
- L1749 _private field_ `private XLoc.Xml.Types.ContextType ContextTypeField`
- L1751 _private field_ `private object DataField`
- L1753 _private field_ `private ContextLineType LineTypeField`
- L1755 _private field_ `private string LinkTextField`
- L1757 _private field_ `private string LocalizedTextField`
- L1759 _private field_ `private XLoc.Xml.Types.LocalizedString ReferencedStringField`
- L1761 _private field_ `private string StringIdField`
- L1763 _private field_ `private string TextField`
- L1765-1775 _public property_ `public System.Runtime.Serialization.ExtensionDataObject ExtensionData { get; set; }`
- L1778-1788 _public property_ `public XLoc.Xml.Types.ContextType ContextType { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1791-1801 _public property_ `public object Data { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1804-1814 _public property_ `public ContextLineType LineType { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]`
- L1817-1827 _public property_ `public string LinkText { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1830-1840 _public property_ `public string LocalizedText { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1843-1853 _public property_ `public XLoc.Xml.Types.LocalizedString ReferencedString { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1856-1866 _public property_ `public string StringId { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`
- L1869-1879 _public property_ `public string Text { get; set; }` — attrs: `[System.Runtime.Serialization.DataMemberAttribute()]`

#### enum `ContextLineType`  
`public enum ContextLineType : int`  
_public; L1884-1901_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")] [System.Runtime.Serialization.DataContractAttribute(Name="ContextLineType", Namespace="")]`
- inherits: `int`
- L1888 _public* enumerator_ `Link = 0` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1891 _public* enumerator_ `Text = 1` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1894 _public* enumerator_ `Context = 2` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1897 _public* enumerator_ `Header = 3` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`
- L1900 _public* enumerator_ `NewLine = 4` — attrs: `[System.Runtime.Serialization.EnumMemberAttribute()]`

#### interface `IXLocApi`  
`public interface IXLocApi`  
_public; L1905-2057_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")] [System.ServiceModel.ServiceContractAttribute(Namespace="urn:XLoc.Services", ConfigurationName="IXLocApi", SessionMode=System.ServiceModel.SessionMode.NotAllowed)]`
- L1909 _public* method_ `string GetTopVersionedBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id, string max_records)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetTopVersionedBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetTopVersionedBuildsResponse")]`
- L1912 _public* method_ `System.Threading.Tasks.Task<string> GetTopVersionedBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id, string max_records)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetTopVersionedBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetTopVersionedBuildsResponse")]`
- L1915 _public* method_ `string GetVersionedBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetVersionedBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetVersionedBuildsResponse")]`
- L1918 _public* method_ `System.Threading.Tasks.Task<string> GetVersionedBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetVersionedBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetVersionedBuildsResponse")]`
- L1921 _public* method_ `string GetLatestVersionedBuild(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestVersionedBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestVersionedBuildResponse")]`
- L1924 _public* method_ `System.Threading.Tasks.Task<string> GetLatestVersionedBuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestVersionedBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestVersionedBuildResponse")]`
- L1928 _public* method_ `XLoc.Xml.Types.Version[] GetVersionsByLocalization(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetVersionsByLocalization", ReplyAction="urn:XLoc.Services/IXLocApi/GetVersionsByLocalizationResponse")] [System.ServiceModel.FaultContractAttribute(typeof(X`
- L1931 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Version[]> GetVersionsByLocalizationAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetVersionsByLocalization", ReplyAction="urn:XLoc.Services/IXLocApi/GetVersionsByLocalizationResponse")]`
- L1935 _public* method_ `XLoc.Xml.Types.Language[] GetLanguagesByLocalization(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLanguagesByLocalization", ReplyAction="urn:XLoc.Services/IXLocApi/GetLanguagesByLocalizationResponse")] [System.ServiceModel.FaultContractAttribute(typeof`
- L1938 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Language[]> GetLanguagesByLocalizationAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLanguagesByLocalization", ReplyAction="urn:XLoc.Services/IXLocApi/GetLanguagesByLocalizationResponse")]`
- L1941 _public* method_ `System.Guid GetLastUploadedGameFile(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLastUploadedGameFile", ReplyAction="urn:XLoc.Services/IXLocApi/GetLastUploadedGameFileResponse")]`
- L1944 _public* method_ `System.Threading.Tasks.Task<System.Guid> GetLastUploadedGameFileAsync(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLastUploadedGameFile", ReplyAction="urn:XLoc.Services/IXLocApi/GetLastUploadedGameFileResponse")]`
- L1947 _public* method_ `string GetBuild(string api_key, string auth_token, string api_sig, string build_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetBuildResponse")]`
- L1950 _public* method_ `System.Threading.Tasks.Task<string> GetBuildAsync(string api_key, string auth_token, string api_sig, string build_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetBuildResponse")]`
- L1953 _public* method_ `string GetBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetBuildsResponse")]`
- L1956 _public* method_ `System.Threading.Tasks.Task<string> GetBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetBuilds", ReplyAction="urn:XLoc.Services/IXLocApi/GetBuildsResponse")]`
- L1959 _public* method_ `byte[] DownloadBuild(string api_key, string auth_token, string api_sig, string build_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/DownloadBuild", ReplyAction="urn:XLoc.Services/IXLocApi/DownloadBuildResponse")]`
- L1962 _public* method_ `System.Threading.Tasks.Task<byte[]> DownloadBuildAsync(string api_key, string auth_token, string api_sig, string build_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/DownloadBuild", ReplyAction="urn:XLoc.Services/IXLocApi/DownloadBuildResponse")]`
- L1965 _public* method_ `string GetLatestBuild(string api_key, string auth_token, string api_sig, string localization_id, string language_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestBuildResponse")]`
- L1968 _public* method_ `System.Threading.Tasks.Task<string> GetLatestBuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestBuild", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestBuildResponse")]`
- L1971 _public* method_ `string GetLatestBuildByFile(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string filename)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestBuildByFile", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestBuildByFileResponse")]`
- L1974 _public* method_ `System.Threading.Tasks.Task<string> GetLatestBuildByFileAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string filename)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLatestBuildByFile", ReplyAction="urn:XLoc.Services/IXLocApi/GetLatestBuildByFileResponse")]`
- L1977 _public* method_ `string Build(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string platform_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/Build", ReplyAction="urn:XLoc.Services/IXLocApi/BuildResponse")]`
- L1980 _public* method_ `System.Threading.Tasks.Task<string> BuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string platform_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/Build", ReplyAction="urn:XLoc.Services/IXLocApi/BuildResponse")]`
- L1983 _public* method_ `bool IsSessionActive(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/IsSessionActive", ReplyAction="urn:XLoc.Services/IXLocApi/IsSessionActiveResponse")]`
- L1986 _public* method_ `System.Threading.Tasks.Task<bool> IsSessionActiveAsync(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/IsSessionActive", ReplyAction="urn:XLoc.Services/IXLocApi/IsSessionActiveResponse")]`
- L1990 _public* method_ `string GetAuthToken(string api_key, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetAuthToken", ReplyAction="urn:XLoc.Services/IXLocApi/GetAuthTokenResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFault`
- L1993 _public* method_ `System.Threading.Tasks.Task<string> GetAuthTokenAsync(string api_key, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetAuthToken", ReplyAction="urn:XLoc.Services/IXLocApi/GetAuthTokenResponse")]`
- L1997 _public* method_ `XLoc.Xml.Types.Session GetAuthTokenByUser(string api_key, string user_name, string pwd, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetAuthTokenByUser", ReplyAction="urn:XLoc.Services/IXLocApi/GetAuthTokenByUserResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.`
- L2000 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Session> GetAuthTokenByUserAsync(string api_key, string user_name, string pwd, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetAuthTokenByUser", ReplyAction="urn:XLoc.Services/IXLocApi/GetAuthTokenByUserResponse")]`
- L2004 _public* method_ `XLoc.Xml.Types.Localization[] GetLocalizations(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLocalizations", ReplyAction="urn:XLoc.Services/IXLocApi/GetLocalizationsResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.Sess`
- L2007 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Localization[]> GetLocalizationsAsync(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLocalizations", ReplyAction="urn:XLoc.Services/IXLocApi/GetLocalizationsResponse")]`
- L2011 _public* method_ `XLoc.Xml.Types.Localization[] GetLocalizationsWithContext(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLocalizationsWithContext", ReplyAction="urn:XLoc.Services/IXLocApi/GetLocalizationsWithContextResponse")] [System.ServiceModel.FaultContractAttribute(type`
- L2014 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Localization[]> GetLocalizationsWithContextAsync(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLocalizationsWithContext", ReplyAction="urn:XLoc.Services/IXLocApi/GetLocalizationsWithContextResponse")]`
- L2018 _public* method_ `XLoc.Xml.Types.Language[] GetLanguages(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLanguages", ReplyAction="urn:XLoc.Services/IXLocApi/GetLanguagesResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFault`
- L2021 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.Language[]> GetLanguagesAsync(string api_key, string auth_token, string api_sig)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetLanguages", ReplyAction="urn:XLoc.Services/IXLocApi/GetLanguagesResponse")]`
- L2025 _public* method_ `string GetGameFiles(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetGameFiles", ReplyAction="urn:XLoc.Services/IXLocApi/GetGameFilesResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFault`
- L2028 _public* method_ `System.Threading.Tasks.Task<string> GetGameFilesAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetGameFiles", ReplyAction="urn:XLoc.Services/IXLocApi/GetGameFilesResponse")]`
- L2032 _public* method_ `string GetPlatforms(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetPlatforms", ReplyAction="urn:XLoc.Services/IXLocApi/GetPlatformsResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFault`
- L2035 _public* method_ `System.Threading.Tasks.Task<string> GetPlatformsAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetPlatforms", ReplyAction="urn:XLoc.Services/IXLocApi/GetPlatformsResponse")]`
- L2039 _public* method_ `string GetFileGroups(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetFileGroups", ReplyAction="urn:XLoc.Services/IXLocApi/GetFileGroupsResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFau`
- L2042 _public* method_ `System.Threading.Tasks.Task<string> GetFileGroupsAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetFileGroups", ReplyAction="urn:XLoc.Services/IXLocApi/GetFileGroupsResponse")]`
- L2046 _public* method_ `XLoc.Xml.Types.SearchResult GetStrings(string api_key, string auth_token, string api_sig, XLoc.Xml.Types.SearchRequest oSearchRequest)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetStrings", ReplyAction="urn:XLoc.Services/IXLocApi/GetStringsResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.SessionFault), A`
- L2049 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.SearchResult> GetStringsAsync(string api_key, string auth_token, string api_sig, XLoc.Xml.Types.SearchRequest oSearchRequest)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetStrings", ReplyAction="urn:XLoc.Services/IXLocApi/GetStringsResponse")]`
- L2053 _public* method_ `XLoc.Xml.Types.SearchCriteria GetSearchCriteria(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetSearchCriteria", ReplyAction="urn:XLoc.Services/IXLocApi/GetSearchCriteriaResponse")] [System.ServiceModel.FaultContractAttribute(typeof(XLoc.Xml.Types.Se`
- L2056 _public* method_ `System.Threading.Tasks.Task<XLoc.Xml.Types.SearchCriteria> GetSearchCriteriaAsync(string api_key, string auth_token, string api_sig, string localization_id)` — attrs: `[System.ServiceModel.OperationContractAttribute(Action="urn:XLoc.Services/IXLocApi/GetSearchCriteria", ReplyAction="urn:XLoc.Services/IXLocApi/GetSearchCriteriaResponse")]`

#### interface `IXLocApiChannel`  
`public interface IXLocApiChannel : IXLocApi, System.ServiceModel.IClientChannel`  
_public; L2060-2062_
- attrs: `[System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]`
- inherits: `IXLocApi, System.ServiceModel.IClientChannel`

#### class `XLocApiClient`  
`public partial class XLocApiClient : System.ServiceModel.ClientBase<IXLocApi>, IXLocApi`  
_public; L2066-2322_
- attrs: `[System.Diagnostics.DebuggerStepThroughAttribute()] [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]`
- inherits: `System.ServiceModel.ClientBase<IXLocApi>, IXLocApi`
- L2069-2071 _public ctor_ `public XLocApiClient()`
- L2073-2076 _public ctor_ `public XLocApiClient(string endpointConfigurationName) : base(endpointConfigurationName)`
- L2078-2081 _public ctor_ `public XLocApiClient(string endpointConfigurationName, string remoteAddress) : base(endpointConfigurationName, remoteAddress)`
- L2083-2086 _public ctor_ `public XLocApiClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : base(endpointConfigurationName, remoteAddress)`
- L2088-2091 _public ctor_ `public XLocApiClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : base(binding, remoteAddress)`
- L2093-2096 _public method_ `public string GetTopVersionedBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id, string max_records)`
- L2098-2101 _public method_ `public System.Threading.Tasks.Task<string> GetTopVersionedBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id, string max_records)`
- L2103-2106 _public method_ `public string GetVersionedBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)`
- L2108-2111 _public method_ `public System.Threading.Tasks.Task<string> GetVersionedBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)`
- L2113-2116 _public method_ `public string GetLatestVersionedBuild(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)`
- L2118-2121 _public method_ `public System.Threading.Tasks.Task<string> GetLatestVersionedBuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string version_id)`
- L2123-2126 _public method_ `public XLoc.Xml.Types.Version[] GetVersionsByLocalization(string api_key, string auth_token, string api_sig, string localization_id)`
- L2128-2131 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Version[]> GetVersionsByLocalizationAsync(string api_key, string auth_token, string api_sig, string localization_id)`
- L2133-2136 _public method_ `public XLoc.Xml.Types.Language[] GetLanguagesByLocalization(string api_key, string auth_token, string api_sig, string localization_id)`
- L2138-2141 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Language[]> GetLanguagesByLocalizationAsync(string api_key, string auth_token, string api_sig, string localization_id)`
- L2143-2146 _public method_ `public System.Guid GetLastUploadedGameFile(string api_key, string auth_token, string api_sig)`
- L2148-2151 _public method_ `public System.Threading.Tasks.Task<System.Guid> GetLastUploadedGameFileAsync(string api_key, string auth_token, string api_sig)`
- L2153-2156 _public method_ `public string GetBuild(string api_key, string auth_token, string api_sig, string build_id)`
- L2158-2161 _public method_ `public System.Threading.Tasks.Task<string> GetBuildAsync(string api_key, string auth_token, string api_sig, string build_id)`
- L2163-2166 _public method_ `public string GetBuilds(string api_key, string auth_token, string api_sig, string localization_id, string language_id)`
- L2168-2171 _public method_ `public System.Threading.Tasks.Task<string> GetBuildsAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id)`
- L2173-2176 _public method_ `public byte[] DownloadBuild(string api_key, string auth_token, string api_sig, string build_id)`
- L2178-2181 _public method_ `public System.Threading.Tasks.Task<byte[]> DownloadBuildAsync(string api_key, string auth_token, string api_sig, string build_id)`
- L2183-2186 _public method_ `public string GetLatestBuild(string api_key, string auth_token, string api_sig, string localization_id, string language_id)`
- L2188-2191 _public method_ `public System.Threading.Tasks.Task<string> GetLatestBuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id)`
- L2193-2196 _public method_ `public string GetLatestBuildByFile(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string filename)`
- L2198-2201 _public method_ `public System.Threading.Tasks.Task<string> GetLatestBuildByFileAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string filename)`
- L2203-2206 _public method_ `public string Build(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string platform_id)`
- L2208-2211 _public method_ `public System.Threading.Tasks.Task<string> BuildAsync(string api_key, string auth_token, string api_sig, string localization_id, string language_id, string platform_id)`
- L2213-2216 _public method_ `public bool IsSessionActive(string api_key, string auth_token, string api_sig)`
- L2218-2221 _public method_ `public System.Threading.Tasks.Task<bool> IsSessionActiveAsync(string api_key, string auth_token, string api_sig)`
- L2223-2226 _public method_ `public string GetAuthToken(string api_key, string api_sig)`
- L2228-2231 _public method_ `public System.Threading.Tasks.Task<string> GetAuthTokenAsync(string api_key, string api_sig)`
- L2233-2236 _public method_ `public XLoc.Xml.Types.Session GetAuthTokenByUser(string api_key, string user_name, string pwd, string api_sig)`
- L2238-2241 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Session> GetAuthTokenByUserAsync(string api_key, string user_name, string pwd, string api_sig)`
- L2243-2246 _public method_ `public XLoc.Xml.Types.Localization[] GetLocalizations(string api_key, string auth_token, string api_sig)`
- L2248-2251 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Localization[]> GetLocalizationsAsync(string api_key, string auth_token, string api_sig)`
- L2253-2256 _public method_ `public XLoc.Xml.Types.Localization[] GetLocalizationsWithContext(string api_key, string auth_token, string api_sig)`
- L2258-2261 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Localization[]> GetLocalizationsWithContextAsync(string api_key, string auth_token, string api_sig)`
- L2263-2266 _public method_ `public XLoc.Xml.Types.Language[] GetLanguages(string api_key, string auth_token, string api_sig)`
- L2268-2271 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.Language[]> GetLanguagesAsync(string api_key, string auth_token, string api_sig)`
- L2273-2276 _public method_ `public string GetGameFiles(string api_key, string auth_token, string api_sig, string localization_id)`
- L2278-2281 _public method_ `public System.Threading.Tasks.Task<string> GetGameFilesAsync(string api_key, string auth_token, string api_sig, string localization_id)`
- L2283-2286 _public method_ `public string GetPlatforms(string api_key, string auth_token, string api_sig, string localization_id)`
- L2288-2291 _public method_ `public System.Threading.Tasks.Task<string> GetPlatformsAsync(string api_key, string auth_token, string api_sig, string localization_id)`
- L2293-2296 _public method_ `public string GetFileGroups(string api_key, string auth_token, string api_sig, string localization_id)`
- L2298-2301 _public method_ `public System.Threading.Tasks.Task<string> GetFileGroupsAsync(string api_key, string auth_token, string api_sig, string localization_id)`
- L2303-2306 _public method_ `public XLoc.Xml.Types.SearchResult GetStrings(string api_key, string auth_token, string api_sig, XLoc.Xml.Types.SearchRequest oSearchRequest)`
- L2308-2311 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.SearchResult> GetStringsAsync(string api_key, string auth_token, string api_sig, XLoc.Xml.Types.SearchRequest oSearchRequest)`
- L2313-2316 _public method_ `public XLoc.Xml.Types.SearchCriteria GetSearchCriteria(string api_key, string auth_token, string api_sig, string localization_id)`
- L2318-2321 _public method_ `public System.Threading.Tasks.Task<XLoc.Xml.Types.SearchCriteria> GetSearchCriteriaAsync(string api_key, string auth_token, string api_sig, string localization_id)`
