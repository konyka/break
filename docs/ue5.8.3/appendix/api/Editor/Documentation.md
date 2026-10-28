# Editor / Documentation

- module root: `Source/Editor/Documentation`
- headers: 15; symbols: 356
- symbol kinds: class=16, delegate=2, enum=2, enumerator=44, function=57, macro=1, member=104, namespace=1, prototype=117, struct=12
- DynamicallyLoadedModuleNames: MessageLog
- PrivateDependencyModuleNames: Analytics, ContentBrowser, CoreUObject, DesktopPlatform, DeveloperSettings, EditorFramework, Engine, InputCore, Projects, Slate, SlateCore, SourceCodeAccess, SourceControl, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: MessageLog
- PublicDependencyModuleNames: Core, MainFrame

### `Source/Editor/Documentation/Private/Documentation.h` (Private)


#### class `FDocumentation`  
`class FDocumentation : public IDocumentation`  
_L19-99_
- inherits: `IDocumentation`
- L23 _public prototype_ `static TSharedRef< IDocumentation > Create();`
- L27 _public prototype_ `virtual ~FDocumentation();`
- L29 _public prototype_ `virtual bool OpenHome(FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const override;`
- L31 _public prototype_ `virtual bool OpenHome(const FCultureRef& Culture, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const override;`
- L33 _public prototype_ `virtual bool OpenAPIHome(FDocumentationSourceInfo Source = FDocumentationSourceInfo()) const override;`
- L35 _public prototype_ `virtual bool Open( const FString& Link, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const override;`
- L37 _public prototype_ `virtual bool Open( const FString& Link, const FCultureRef& Culture, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const override;`
- L39 _public prototype_ `virtual TSharedRef< SWidget > CreateAnchor( const TAttribute<FString>& Link, const FString& PreviewLink = FString(), const FString& PreviewExcerptName = FString(), const TAttribute<FString>& BaseUrlId = FString()) const override;`
- L41 _public prototype_ `virtual TSharedRef< IDocumentationPage > GetPage( const FString& Link, const TSharedPtr< FParserConfiguration >& Config, const FDocumentationStyle& Style = FDocumentationStyle() ) override;`
- L43 _public prototype_ `virtual bool PageExists(const FString& Link) const override;`
- L45 _public prototype_ `virtual bool PageExists(const FString& Link, const FCultureRef& Culture) const override;`
- L47 _public prototype_ `virtual const TArray < FString >& GetSourcePaths() const override;`
- L49 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip( const TAttribute<FText>& Text, const TSharedPtr<SWidget>& OverrideContent, const FString& Link, const FString& ExcerptName ) const override;`
- L51 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip(const TAttribute<FText>& Text, const TSharedPtr<SWidget>& OverrideContent, const FString& Link, const FString& ExcerptName, const TAttribute<FText>& Shortcut) const override;`
- L53 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip(const TAttribute<FText>& Text, const TSharedRef<SWidget>& OverrideContent, const TSharedPtr<SVerticalBox>& DocVerticalBox, const FString& Link, const FString& ExcerptName) const override;`
- L55 _public prototype_ `virtual bool RegisterBaseUrl(const FString& Id, const FString& Url) override;`
- L57 _public prototype_ `virtual FString GetBaseUrl(const FString& Id) const override;`
- L59 _public prototype_ `virtual bool RegisterRedirect(const FName& Owner, const FDocumentationRedirect& Redirect) override;`
- L61 _public prototype_ `virtual void UnregisterRedirects(const FName& Owner) override;`
- L65 _private prototype_ `FDocumentation();`
- L74 _private prototype_ `bool OpenUrl(const FString& Link, const FCultureRef& Culture, FDocumentationSourceInfo Source, const FString& BaseUrlId) const;` — Builds and opens a documentation url given individual components/parameters @param Link Identifier for the page (could be a full url or individual page id) @param Culture Desired locale for resulting documentation url @param Source Metadata about the page request used by analytics @return Was the documentation url successfully opened?
- L81 _private prototype_ `FDocumentationUrl RedirectUrl(const FDocumentationUrl& OriginalUrl) const;` — Redirects a documentation url @param OriginalUrl Original url @return Redirected documentation url
- L84 _private prototype_ `void RegisterConfigRedirects();` — Registers all redirects from editor config file
- L88 _private member_ `TMap< FString, TWeakPtr< IDocumentationPage > > LoadedPages;`
- L90 _private member_ `TMap< const FString, const FString > RegisteredBaseUrls;`
- L92 _private member_ `FDocumentationRedirectRegistry RedirectRegistry;`
- L94 _private member_ `TArray < FString > SourcePaths;`
- L96 _private prototype_ `void HandleSDKNotInstalled(const FString& PlatformName, const FString& InDocumentationPage);`
- L98 _private prototype_ `bool AddSourcePath(const FString& Path);`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDocumentation, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDocumentation, Log, All);`

### `Source/Editor/Documentation/Private/DocumentationLink.h` (Private)


#### class `FDocumentationLink`  
`class FDocumentationLink`  
_L11-259_
- L15 _public function_ `static FString GetUrlRoot(const FString& BaseUrlId = FString())`
- L20 _public function_ `static FString GetHomeUrl()`
- L25 _public function_ `static FString GetHomeUrl(const FCultureRef& Culture)`
- L34 _public function_ `static FString ToUrl(const FString& Link, FDocumentationSourceInfo const& Source, const FString& BaseUrlId = FString())`
- L39 _public function_ `static FString ToUrl(const FString& Link, const FCultureRef& Culture, FDocumentationSourceInfo const& Source, const FString& BaseUrlId = FString())`
- L66 _public function_ `static FString ToFilePath( const FString& Link )`
- L88 _public function_ `static FString ToFilePath(const FString& Link, const FCultureRef& Culture)`
- L100 _public function_ `static FString ToFileUrl(const FString& Link, FDocumentationSourceInfo const& SourceInfo)`
- L123 _public function_ `static FString ToFileUrl(const FString& Link, const FCultureRef& Culture, FDocumentationSourceInfo const& SourceInfo)`
- L135 _public function_ `static FString ToSourcePath(const FString& Link, const FString& BasePath = FString())`
- L157 _public function_ `static FString ToSourcePath(const FString& Link, const FCultureRef& Culture, const FString& BasePath = FString())`
- L187 _private function_ `static void AddSourceInfoToQueryString(FString& QueryString, FDocumentationSourceInfo const& Info)`
- L209 _private function_ `static void SplitLink( const FString& Link, FString& Path, FString& QueryString, FString& Anchor )` — Splits the Link parameter into three parts: - The path, which is everything up to the first ? or # character (or to the end of the link). - The query string, which is everything from the first ? to the first # (or to the end of the link). - The anchor, which is everything from the first # to the end of the link. If the query parameter contains anything already, whatever is found in the link will be appended to the existing value.

### `Source/Editor/Documentation/Private/DocumentationPage.h` (Private)


#### class `FDocumentationPage`  
`class FDocumentationPage : public IDocumentationPage`  
_L13-50_
- inherits: `IDocumentationPage`
- L18 _public prototype_ `static TSharedRef< IDocumentationPage > Create( const FString& Link, const TSharedRef< FUDNParser >& Parser );` — Returns an instance of class containing content from the link argument
- L22 _public prototype_ `virtual ~FDocumentationPage();`
- L23 _public prototype_ `virtual bool HasExcerpt( const FString& ExcerptName ) override;`
- L24 _public prototype_ `virtual int32 GetNumExcerpts() const override;`
- L25 _public prototype_ `virtual bool GetExcerpt( const FString& ExcerptName, FExcerpt& Excerpt) override;`
- L26 _public prototype_ `virtual void GetExcerpts( TArray< FExcerpt >& Excerpts ) override;`
- L27 _public prototype_ `virtual bool GetExcerptContent( FExcerpt& Excerpt ) override;`
- L29 _public prototype_ `virtual FText GetTitle() override;`
- L31 _public prototype_ `virtual void Reload() override;`
- L33 _public prototype_ `virtual void SetTextWrapAt( TAttribute<float> WrapAt ) override;`
- L37 _private prototype_ `FDocumentationPage( const FString& InLink, const TSharedRef< FUDNParser >& InParser );`
- L42 _private member_ `FString Link;` — The string representing the UDN page location
- L44 _private member_ `TSharedRef< FUDNParser > Parser;` — The UDN parser instance used to create this page
- L47 _private member_ `TArray<FExcerpt> StoredExcerpts;` — The excerpts contained in this UDN page
- L49 _private member_ `FUDNPageMetadata StoredMetadata;` — The UDN meta data contained in this page

### `Source/Editor/Documentation/Private/DocumentationRedirectRegistry.h` (Private)


#### class `FDocumentationRedirectRegistry`  
`class FDocumentationRedirectRegistry`  
_L18-60_
- desc: Registry class to manage redirects and associate redirects with a specific documentation link Every redirect is registered under an owning name to make batch registration/unregistration easier. Redirects registered with "None" will be globally owned and can only be unregistered with other global redirects wholesale. Documentation links with multiple redirects is supported and prioritized based on registration order. The last registration is prioritized over earlier ones and prior registrations will be respected in reverse order as higher priority redirects are unregistered. Redirects registered with a valid owner will always be prioritized over global redirects, regardless of registration order. Since prioritization is based on registration order there is no guarantee that re-registered redirects will have the same priority.
- L27 _public prototype_ `bool Register(const FName& Owner, const FDocumentationRedirect& Redirect);` — Registers a new documentation redirect for an owner @param Owner Name of the owner for the redirect @param Redirect Redirect to register @return Was the redirect successfully registered?
- L33 _public prototype_ `void UnregisterAll(const FName& Owner);` — Unregisters all redirects for an owner @param Owner Name of the owner
- L41 _public prototype_ `bool GetRedirect(const FString& Link, FDocumentationRedirect& OutRedirect) const;` — Retrieves the highest priority redirect for a documentation link @param Link Documentation link to get redirect for @param OutRedirect Redirect for the documentation link @return Was there a valid redirect for the documentation link?
- L59 _private member_ `TMap<FString, FDocumentationRedirects> RegisteredRedirects;` — Mapping between documentation link to registered redirects

#### struct `FDocumentationRedirectRegistry::FOwnedDocumentationRedirect`  
`struct FOwnedDocumentationRedirect`  
_L45-49_
- desc: Documentation redirect with ownership information
- L47 _public member_ `FName Owner;`
- L48 _public member_ `FDocumentationRedirect Redirect;`

#### struct `FDocumentationRedirectRegistry::FDocumentationRedirects`  
`struct FDocumentationRedirects`  
_L52-56_
- desc: Container of owned and global redirects for a documentation link
- L54 _public member_ `TArray<FOwnedDocumentationRedirect> Owned;`
- L55 _public member_ `TArray<FDocumentationRedirect> Global;`

### `Source/Editor/Documentation/Private/DocumentationStyleSet.h` (Private)


#### class `FDocumentationStyleSet`  
`class FDocumentationStyleSet : public FSlateStyleSet`  
_L7-23_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L13 _public prototype_ `static const FDocumentationStyleSet& Get();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `~FDocumentationStyleSet();`
- L19 _private prototype_ `FDocumentationStyleSet();`
- L21 _private member_ `static FName StyleName;`
- L22 _private member_ `static TUniquePtr<FDocumentationStyleSet> Instance;`

### `Source/Editor/Documentation/Private/SDocumentationAnchor.h` (Private)


#### class `SDocumentationAnchor`  
`class SDocumentationAnchor : public SCompoundWidget`  
_L11-37_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS( SDocumentationAnchor )`
- L16 _public prototype_ `SLATE_ARGUMENT( FString, PreviewLink ) SLATE_ARGUMENT( FString, PreviewExcerptName ) SLATE_ATTRIBUTE( FString, Link ) SLATE_ATTRIBUTE(FString, BaseUrlId) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `FReply OnClicked() const;`
- L33 _private member_ `TAttribute<FString> Link;`
- L34 _private member_ `TAttribute<FString> BaseUrlId;`
- L35 _private member_ `TSharedPtr<class SButton> Button;`
- L36 _private member_ `TSharedPtr<class SImage> ButtonImage;`

### `Source/Editor/Documentation/Private/UDNParser.h` (Private)


#### struct `FUDNPageMetadata`  
`struct FUDNPageMetadata`  
_L22-41_
- desc: Stores all the metadata that a UDN page can have
- L24 _public function_ `FUDNPageMetadata() : Availability() , Title() , Crumbs() , Description() , ExcerptNames() , ExcerptAliases() , BaseUrl()`
- L34 _public member_ `FString Availability;`
- L35 _public member_ `FText Title;`
- L36 _public member_ `FText Crumbs;`
- L37 _public member_ `FText Description;`
- L38 _public member_ `TSet< FString > ExcerptNames;`
- L39 _public member_ `TMap< FString, FString > ExcerptAliases;`
- L40 _public member_ `FString BaseUrl;`

#### enum `EUDNToken::Type`  
`enum Type`  
_L46-68_
- L48 _public enumerator_ `Content`
- L49 _public enumerator_ `Pound`
- L50 _public enumerator_ `OpenBracket`
- L51 _public enumerator_ `CloseBracket`
- L52 _public enumerator_ `OpenParenthesis`
- L53 _public enumerator_ `CloseParenthesis`
- L54 _public enumerator_ `Numbering`
- L55 _public enumerator_ `Bang`
- L56 _public enumerator_ `Excerpt`
- L57 _public enumerator_ `Variable`
- L58 _public enumerator_ `Colon`
- L59 _public enumerator_ `Slash`
- L60 _public enumerator_ `Dash`
- L61 _public enumerator_ `MetadataAvailability`
- L62 _public enumerator_ `MetadataTitle`
- L63 _public enumerator_ `MetadataCrumbs`
- L64 _public enumerator_ `MetadataDescription`
- L65 _public enumerator_ `MetadataBaseUrl`
- L66 _public enumerator_ `Percentage`
- L67 _public enumerator_ `Asterisk`

#### struct `FUDNToken`  
`struct FUDNToken`  
_L72-80_
- desc: A token, which can also have content
- L74 _public function_ `FUDNToken(EUDNToken::Type InTokenType, const FString& InContent = FString()) : TokenType(InTokenType) , Content(InContent)`
- L78 _public member_ `EUDNToken::Type TokenType;`
- L79 _public member_ `FString Content;`

#### struct `FUDNLine`  
`struct FUDNLine`  
_L83-124_
- desc: A UDN line, which, since we parse line by line, will correspond to a single slate widget
- L114 _public member_ `Type ContentType;`
- L117 _public member_ `TArray<FString> AdditionalContent;` — Optional string/path content that is used by this line
- L119 _public function_ `FUDNLine() : ContentType(FUDNLine::Ignored)`
- L122 _public function_ `FUDNLine(FUDNLine::Type InLineType, const FString& InStringContent = FString(), const FString& InPathContent = FString()) : ContentType(InLineType)`

#### enum `FUDNLine::Type`  
`enum Type`  
_L87-113_
- desc: The type of line this is
- L89 _public enumerator_ `Ignored`
- L90 _public enumerator_ `VariableReference`
- L91 _public enumerator_ `Whitespace`
- L92 _public enumerator_ `Content`
- L93 _public enumerator_ `NumberedContent`
- L94 _public enumerator_ `Header1`
- L95 _public enumerator_ `Header2`
- L96 _public enumerator_ `Header3`
- L97 _public enumerator_ `ExcerptOpen`
- L98 _public enumerator_ `ExcerptClose`
- L99 _public enumerator_ `Image`
- L100 _public enumerator_ `Link`
- L101 _public enumerator_ `ImageLink`
- L102 _public enumerator_ `HorizontalRule`
- L103 _public enumerator_ `MetadataAvailability`
- L104 _public enumerator_ `MetadataTitle`
- L105 _public enumerator_ `MetadataCrumbs`
- L106 _public enumerator_ `MetadataDescription`
- L107 _public enumerator_ `MetadataBaseUrl`
- L108 _public enumerator_ `Variable`
- L109 _public enumerator_ `VariableOpen`
- L110 _public enumerator_ `VariableClose`
- L111 _public enumerator_ `BoldContent`
- L112 _public enumerator_ `BulletContent`

#### class `FUDNParser`  
`class FUDNParser : public TSharedFromThis< FUDNParser >`  
_L140-270_
- inherits: `TSharedFromThis<FUDNParser>`
- desc: A Parser for UDN Files, turning them into Slate widgets It only provides a very small subset of what UDN files have to offer: - Text - Headers - Numbering - Horizontal Rules - Images (can't be inline) - Hyperlinks (can't be inline) - Image Hyperlinks - Excerpts (currently, it only parses what's in excerpts) Currently, it parses pages into an array based on the excerpts
- L144 _public prototype_ `static TSharedRef< FUDNParser > Create( const TSharedPtr< FParserConfiguration >& ParserConfig, const FDocumentationStyle& Style );`
- L147 _public prototype_ `~FUDNParser();`
- L154 _public prototype_ `bool Parse(const FString& Link, TArray< FExcerpt >& OutContentSections, FUDNPageMetadata& OutMetadata);` — Parses the UDN page specified by the Path, returning true if successful, and giving back a list of widgets created by the parsing, split based on the beginning and ending of excerpts
- L156 _public prototype_ `bool GetExcerptContent( const FString& Link, FExcerpt& Excerpt );`
- L159 _public prototype_ `void SetWrapAt( TAttribute<float> InWrapAt );` — Allows a TAttribute to be set to control excerpt wrapat values from outside the parser.
- L163 _private prototype_ `FReply OnImageLinkClicked(FString Payload);` — UI Callbacks for the widgets
- L166 _private prototype_ `void AddContentToExcerpt(TSharedPtr<SVerticalBox> Box, const FString& ContentSource, FExcerpt& Excerpt);` — Adds the content text source to the scrollbox
- L169 _private prototype_ `void AddCaptionToExcerpt(TSharedPtr<SVerticalBox> Box, const FString& ContentSource, FExcerpt& Excerpt);` — Adds the content text source to the scrollbox as a caption for an image
- L172 _private prototype_ `void AddListItemToExcerpt(TSharedPtr<SVerticalBox> Box, const FString& LeftContentSource, const FString& RightContentSource, FExcerpt& Excerpt);` — Adds the content text sources to the scrollbox in two columns, emulating a list item with hanging indent
- L175 _private prototype_ `TSharedPtr<FSlateDynamicImageBrush> GetDynamicBrushFromImagePath(FString Filename);` — Gets the dynamic brush for the given filename
- L178 _private prototype_ `void AppendExcerpt(TSharedPtr<SVerticalBox> Box, TSharedRef<SWidget> Content);` — Helper function which appends a content section to the scrollbox
- L181 _private prototype_ `FString ConvertSymbolIntoAString(const FUDNToken& Token);` — Turns a series of symbols (or a single symbol) back to string format
- L182 _private prototype_ `FString ConvertSymbolsIntoAString(const TArray<FUDNToken>& TokenList, int32 StartingAfterIndex = 0);`
- L185 _private prototype_ `bool ParseLineIntoSymbols(int32 LineNumber, const FString& Line, TArray<FUDNToken>& SymbolList);` — Given a line, converts it into UDN tokens, returning true if successful
- L188 _private prototype_ `FUDNLine ParseLineIntoUDNContent(int32 LineNumber, const FString& Line);` — Given a line, convert it into an FUDNLine which can be used by Slate
- L190 _private prototype_ `bool LoadLink( const FString& Link, TArray<FString>& ContentLines );`
- L192 _private prototype_ `TSharedRef< SWidget > GenerateExcerptContent( const FString& Link, FExcerpt& Excerpt, const TArray<FString>& ContentLines, int32 StartingLineIndex );`
- L194 _private prototype_ `bool ParseSymbols( const FString& Link, const TArray<FString>& ContentLines, const FString& FullPath, TArray<FExcerpt>& OutExcerpts, FUDNPageMetadata& OutMetadata );`
- L196 _private prototype_ `void HandleHyperlinkNavigate( FString AdditionalContent );`
- L198 _private prototype_ `void NavigateToLink( FString AdditionalContent );`
- L211 _private prototype_ `bool ParseCodeLink(FString &InternalLink);` — Parses a code link embedded in the doc. Allows us to specify files in code to link to in one of 2 ways. In both cases the last 2 parameters are line and column. [Project based link](CODELINK:Private/[PROJECT]File.cpp, 29, 5) This will attempt to parse the active solution name and replace instances of [PROJECT] within this so (CODELINK:Private/[PROJECT]Ball.cpp, 29, 5) will in a project called marble will equate to <UE4ROOT>Marble/Source/Marble/Private/MarbleBall.cpp [Explicit link](CODELINK:Templates/TP_Rolling/Source/TP_Rolling/Private/TP_Rolling.cpp will equate to <UE4ROOT>Templates/TP_Rolling/Source/TP_Rolling/Private/TP_Rolling.cpp
- L221 _private prototype_ `bool ParseAssetLink(FString &InternalLink);` — Parses an asset link embedded in the doc. Allows us to specify assets to either highlight or edit in the editor (ASSETLINK:SELECT,MyCharacter) This will highlight the MyCharacter asset in the content browser (ASSETLINK:EDIT,MyCharacter) This will edit the given asset in the appropriate editor window type.
- L223 _private prototype_ `FUDNParser( const TSharedRef< FParserConfiguration >& InConfiguration, const FDocumentationStyle& InStyle );`
- L224 _private prototype_ `void Initialize();`
- L226 _private prototype_ `static TOptional<FVector2D> GetImageDesiredSize(TSharedPtr<FSlateDynamicImageBrush> DynamicBrush, float MaxWidth);`
- L229 _private member_ `TArray< TSharedPtr< FSlateDynamicImageBrush > > DynamicBrushesUsed;` — A list of dynamic brushes we are using for the currently loaded tutorial
- L232 _private member_ `TSharedRef< FParserConfiguration > Configuration;` — Configuration details
- L235 _private member_ `FDocumentationStyle Style;` — The styling we apply to generated widgets
- L247 _private member_ `TArray<FTokenPair> TokenLibrary;`
- L265 _private member_ `TArray<FTokenConfiguration> LineLibrary;`
- L267 _private member_ `TAttribute<float> WrapAt;` — Documentation text wrapping control attribute
- L269 _private member_ `TAttribute<FOptionalSize> ContentWidth;` — Documentation optional width control attribute

#### struct `FUDNParser::FTokenPair`  
`struct FTokenPair`  
_L238-246_
- desc: A library of which tokens correspond to which series of strings
- L240 _public function_ `FTokenPair(FString InParseText, EUDNToken::Type InTokenType) : ParseText(InParseText) , TokenType(InTokenType)`
- L244 _public member_ `FString ParseText;`
- L245 _public member_ `EUDNToken::Type TokenType;`

#### struct `FUDNParser::FTokenConfiguration`  
`struct FTokenConfiguration`  
_L250-263_
- desc: A library of which series of tokens correspond to which line types
- L252 _public function_ `FTokenConfiguration(const TArray<EUDNToken::Type>& InTokenTypes, FUDNLine::Type InOutputLineType, bool bInAcceptTrailingContent = false) : TokensAccepted(InTokenTypes) , OutputLineType(InOutputLineType) , bAcceptTrailingSymbolDumpAsContent(bInAcceptTrailingContent)`
- L258 _public prototype_ `int32 CalculatedExpectedContentStrings();` — Tallies the total number of content tokens in this config
- L260 _public member_ `TArray<EUDNToken::Type> TokensAccepted;`
- L261 _public member_ `FUDNLine::Type OutputLineType;`
- L262 _public member_ `bool bAcceptTrailingSymbolDumpAsContent;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace EUDNToken`

### `Source/Editor/Documentation/Public/DocumentationRedirect.h` (Public)


#### struct `FDocumentationRedirect`  
`struct FDocumentationRedirect`  
_L12-29_
- reflection: `USTRUCT()`
- desc: Engine level documentation link redirect
- L24 _public member_ `FString From;` — `UPROPERTY()` — From Key @note Documentation redirects supports redirection using a UnrealEd URL config key or raw documentation link. This key will be checked to see if it's an UnrealEd URL config key or treated as a raw documentation link as a fallback. See examples of UnrealEd URL config keys in the UnrealEd.URLs section of the BaseEditor.ini config file.
- L28 _public member_ `FDocumentationUrl ToUrl;` — `UPROPERTY()` — To Url

### `Source/Editor/Documentation/Public/DocumentationSettings.h` (Public)


#### struct `FDocumentationBaseUrl`  
`struct FDocumentationBaseUrl`  
_L12-34_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Id;` — `UPROPERTY()`
- L21 _public member_ `FString Url;` — `UPROPERTY()`
- L23 _public function_ `FDocumentationBaseUrl()`
- L25 _public function_ `FDocumentationBaseUrl(FString const& InId, FString const& InUrl) : Id(InId), Url(InUrl)`
- L30 _public function_ `bool IsEmpty() const` — Returns true if either the ID or URL is unset.

#### class `UDocumentationSettings`  
`class UDocumentationSettings : public UDeveloperSettings`  
_L38-50_
- reflection: `UCLASS(config=Editor)`
- inherits: `UDeveloperSettings`
- L45 _public member_ `TArray<FDocumentationBaseUrl> DocumentationBaseUrls;` — `UPROPERTY(Config)` — Array of base URLs for documentation links that are loaded on startup
- L49 _public member_ `TArray<FDocumentationRedirect> DocumentationRedirects;` — `UPROPERTY(Config)` — Array of static documentation redirects registered on startup

### `Source/Editor/Documentation/Public/DocumentationUrl.h` (Public)


#### struct `FDocumentationUrl`  
`struct FDocumentationUrl`  
_L10-28_
- reflection: `USTRUCT()`
- L14 _public prototype_ `FDocumentationUrl() = default;`
- L15 _public function_ `explicit FDocumentationUrl(const FString& Link) : Link(Link)`
- L16 _public function_ `FDocumentationUrl(const FString& Link, const FString& BaseUrlId) : Link(Link), BaseUrlId(BaseUrlId)`
- L20 _public member_ `FString Link;` — `UPROPERTY()` — Link for documentation page (page id, full url)
- L23 _public member_ `FString BaseUrlId;` — `UPROPERTY()`
- L25 _public function_ `bool IsValid() const`
- L27 _public function_ `FString ToString() const`

### `Source/Editor/Documentation/Public/IDocumentation.h` (Public)


#### class `FDocumentationStyle`  
`class FDocumentationStyle`  
_L17-144_
- L20 _public function_ `FDocumentationStyle() : ContentStyleName(TEXT("Documentation.Content")) , BoldContentStyleName(TEXT("Documentation.BoldContent")) , ItalicContentStyleName(TEXT("Documentation.ItalicContent")) , NumberedContentStyleName(TEXT("Documentation.NumberedContent")) , Header1StyleName(TEXT("Documentation.Header1")) , Header2StyleName(TEXT("Documentation.Header2")) , Header3StyleName(TEXT("Documentation.Header3")) , HyperlinkStyleName(TEXT("Documentation.Hyperlink")) , HyperlinkButtonStyleName(TEXT("Documentation.Hyperlink.Button")) , HyperlinkTextStyleName(TEXT("Documentation.Hyperlink.Text")) , SeparatorStyleName(TEXT("Documentation.Separator"))`
- L36 _public function_ `FDocumentationStyle& ContentStyle(const FName& InName)` — Set the content style for this documentation
- L43 _public function_ `FDocumentationStyle& BoldContentStyle(const FName& InName)` — Set the bold content style for this documentation
- L50 _public function_ `FDocumentationStyle& ItalicContentStyle(const FName& InName)` — Set the italic content style for this documentation
- L57 _public function_ `FDocumentationStyle& NumberedContentStyle(const FName& InName)` — Set the numbered content style for this documentation
- L64 _public function_ `FDocumentationStyle& Header1Style(const FName& InName)` — Set the header 1 style for this documentation
- L71 _public function_ `FDocumentationStyle& Header2Style(const FName& InName)` — Set the header 2 style for this documentation
- L78 _public function_ `FDocumentationStyle& Header3Style(const FName& InName)` — Set the header 3 style for this documentation
- L85 _public function_ `FDocumentationStyle& HyperlinkStyle(const FName& InName)` — Set the hyperlink button style for this documentation
- L92 _public function_ `FDocumentationStyle& HyperlinkButtonStyle(const FName& InName)` — Set the hyperlink button style for this documentation
- L99 _public function_ `FDocumentationStyle& HyperlinkTextStyle(const FName& InName)` — Set the hyperlink text style for this documentation
- L106 _public function_ `FDocumentationStyle& SeparatorStyle(const FName& InName)` — Set the separator style for this documentation
- L113 _public member_ `FName ContentStyleName;` — Content text style
- L116 _public member_ `FName BoldContentStyleName;` — Bold content text style
- L119 _public member_ `FName ItalicContentStyleName;` — Italic content text style
- L122 _public member_ `FName NumberedContentStyleName;` — Numbered content text style
- L125 _public member_ `FName Header1StyleName;` — Header1 text style
- L128 _public member_ `FName Header2StyleName;` — Header2 text style
- L131 _public member_ `FName Header3StyleName;` — Header3 text style
- L134 _public member_ `FName HyperlinkStyleName;` — Hyperlink style
- L137 _public member_ `FName HyperlinkButtonStyleName;` — Hyperlink button style
- L140 _public member_ `FName HyperlinkTextStyleName;` — Hyperlink text style
- L143 _public member_ `FName SeparatorStyleName;` — Separator style name

#### class `FParserConfiguration`  
`class FParserConfiguration`  
_L146-161_
- L149 _public function_ `static TSharedRef< FParserConfiguration > Create()`
- L155 _public prototype_ `~FParserConfiguration() = default;`
- L157 _public member_ `FOnNavigate OnNavigate;`
- L160 _private function_ `FParserConfiguration()`

#### struct `FDocumentationSourceInfo`  
`struct FDocumentationSourceInfo`  
_L164-184_
- L167 _public member_ `FString Source;`
- L168 _public member_ `FString Medium;`
- L169 _public member_ `FString Campaign;`
- L171 _public function_ `FDocumentationSourceInfo()`
- L172 _public function_ `FDocumentationSourceInfo(FString const& InCampaign) : Source(TEXT("editor")), Medium(TEXT("docs")), Campaign(InCampaign)`
- L175 _public function_ `FDocumentationSourceInfo(FString const& InSource, FString const& InMedium, FString const& InCampaign) : Source(InSource), Medium(InMedium), Campaign(InCampaign)`
- L180 _public function_ `bool IsEmpty() const` — Returns true if there is NO valid source info in the struct, false otherwise.

#### class `IDocumentation`  
`class IDocumentation`  
_L187-247_
- L191 _public function_ `static inline TSharedRef< IDocumentation > Get()`
- L197 _public function_ `static inline bool IsAvailable()`
- L204 _public prototype_ `virtual bool OpenHome(FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const = 0;`
- L206 _public prototype_ `virtual bool OpenHome(const FCultureRef& Culture, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString & BaseUrlId = FString()) const = 0;`
- L208 _public prototype_ `virtual bool OpenAPIHome(FDocumentationSourceInfo Source = FDocumentationSourceInfo()) const = 0;`
- L210 _public prototype_ `virtual bool Open(const FString& Link, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const = 0;`
- L212 _public prototype_ `virtual bool Open(const FString& Link, const FCultureRef& Culture, FDocumentationSourceInfo Source = FDocumentationSourceInfo(), const FString& BaseUrlId = FString()) const = 0;`
- L214 _public prototype_ `virtual TSharedRef< class SWidget > CreateAnchor( const TAttribute<FString>& Link, const FString& PreviewLink = FString(), const FString& PreviewExcerptName = FString(), const TAttribute<FString>& BaseUrlId = FString()) const = 0;`
- L216 _public prototype_ `virtual TSharedRef< class IDocumentationPage > GetPage( const FString& Link, const TSharedPtr< FParserConfiguration >& Config, const FDocumentationStyle& Style = FDocumentationStyle() ) = 0;`
- L218 _public prototype_ `virtual bool PageExists(const FString& Link) const = 0;`
- L220 _public prototype_ `virtual bool PageExists(const FString& Link, const FCultureRef& Culture) const = 0;`
- L222 _public prototype_ `virtual const TArray < FString >& GetSourcePaths() const = 0;`
- L224 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip( const TAttribute<FText>& Text, const TSharedPtr<SWidget>& OverrideContent, const FString& Link, const FString& ExcerptName ) const = 0;`
- L226 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip(const TAttribute<FText>& Text, const TSharedPtr<SWidget>& OverrideContent, const FString& Link, const FString& ExcerptName, const TAttribute<FText>& Shortcut) const = 0;`
- L228 _public prototype_ `virtual TSharedRef< class SToolTip > CreateToolTip(const TAttribute<FText>& Text, const TSharedRef<SWidget>& OverrideContent, const TSharedPtr<class SVerticalBox>& DocVerticalBox, const FString& Link, const FString& ExcerptName) const = 0;`
- L230 _public prototype_ `virtual bool RegisterBaseUrl(const FString& Id, const FString& Url) = 0;`
- L232 _public prototype_ `virtual FString GetBaseUrl(const FString& Id) const = 0;`
- L240 _public prototype_ `virtual bool RegisterRedirect(const FName& Owner, const FDocumentationRedirect& Redirect) = 0;` — Registers a documentation redirect for an owner @param Owner Name of owner for redirect @param Redirect Redirect to register @return Was the redirect successfully registered?
- L246 _public prototype_ `virtual void UnregisterRedirects(const FName& Owner) = 0;` — Unregisters all redirects owned by a specific owner @param Owner Name of owner to unregister for

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam( FOnNavigate, const FString& ) class FDocumentationStyle { public: FDocumentationStyle() : ContentStyleName(TEXT("Documentation.Content")) , BoldContentStyleName(TEXT("Documentation.BoldContent")) , ItalicContentStyleName(TEXT("Documentation.ItalicContent")) , NumberedContentStyleName(TEXT("Documentation.NumberedContent")) , Header1StyleName(TEXT("Documentation.Header1")) , Header2StyleName(TEXT("Documentation.Header2")) , Header3StyleName(TEXT("Documentation.Header3")) , HyperlinkStyleName(TEXT("Documentation.Hyperlink")) , HyperlinkButtonStyleName(TEXT("Documentation.Hyperlink.Button")) , HyperlinkTextStyleName(TEXT("Documentation.Hyperlink.Text")) , SeparatorStyleName(TEXT("Documentation.Separator")) { } FDocumentationStyle& ContentStyle(const FName& InName) { ContentStyleName = InName; return *this; } FDocumentationStyle& BoldContentStyle(const FName& InName) { BoldContentStyleName = InName; return *this; } FDocumentationStyle& ItalicContentStyle(const FName& InName) { ItalicContentStyleName = InName; return *this; }` — Invoked when someone clicks on a hyperlink.

### `Source/Editor/Documentation/Public/IDocumentationModule.h` (Public)


#### class `IDocumentationModule`  
`class IDocumentationModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IDocumentationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L40 _public prototype_ `virtual class TSharedRef< class IDocumentation > GetDocumentation() const = 0;`

### `Source/Editor/Documentation/Public/IDocumentationPage.h` (Public)


#### struct `FExcerpt`  
`struct FExcerpt`  
_L9-45_
- L12 _public function_ `FExcerpt() : LineNumber( INDEX_NONE )` — FExcerpt constructor
- L17 _public function_ `FExcerpt( const FString& InName, const TSharedPtr< SWidget >& InContent, const TMap< FString, FString >& InVariables, int32 InLineNumber ) : Name( InName ) , Content( InContent ) , Variables( InVariables ) , LineNumber( InLineNumber )` — FExcerpt overloaded constructor
- L24 _public function_ `FExcerpt(const FString& InName, const TSharedPtr< SWidget >& InContent, const TMap< FString, FString >& InVariables, int32 InLineNumber, const FString& InSourcePath) : Name(InName) , Content(InContent) , Variables(InVariables) , LineNumber(InLineNumber) , SourcePath(InSourcePath)`
- L33 _public member_ `FString Name;` — The name of the excerpt, as specified in the line at the top of the excerpt.
- L35 _public member_ `TSharedPtr<SWidget> Content;` — The Slate content generated for the excerpt.
- L38 _public member_ `TMap< FString, FString > Variables;` — The content of the [VAR] sections read from the excerpt. The keys are the names from the [VAR:NAME] lines that start the variables, and the value for each key is the text inside the [VAR:NAME].....[/VAR] block.
- L40 _public member_ `int32 LineNumber;` — The line number that this excerpt begins within its source file.
- L42 _public member_ `FString RichText;` — A rich text version of the excerpt content.
- L44 _public member_ `FString SourcePath;` — The path to the file that this excerpt was read from.

#### class `IDocumentationPage`  
`class IDocumentationPage`  
_L47-71_
- L52 _public prototype_ `virtual bool HasExcerpt( const FString& ExcerptName ) = 0;` — Returns true if this page contains a match for the ExcerptName
- L54 _public prototype_ `virtual int32 GetNumExcerpts() const = 0;` — Return the number of excerpts this page holds
- L56 _public prototype_ `virtual bool GetExcerpt( const FString& ExcerptName, FExcerpt& Excerpt) = 0;` — Populates the argument excerpt with this content found using the excer
- L58 _public prototype_ `virtual void GetExcerpts( TArray< FExcerpt >& Excerpts ) = 0;` — Populates the argument TArray with Excerpts this page contains
- L60 _public prototype_ `virtual bool GetExcerptContent( FExcerpt& Excerpt ) = 0;` — Builds the Excerpt content using the excerpt name from the argument
- L63 _public prototype_ `virtual FText GetTitle() = 0;` — Returns the title of the excerpt
- L66 _public prototype_ `virtual void Reload() = 0;` — Rebuilds the excerpt content
- L69 _public prototype_ `virtual void SetTextWrapAt( TAttribute<float> WrapAt ) = 0;` — Sets the argument as the width control for text wrap in the excerpt widgets

### `Source/Editor/Documentation/Public/SDocumentationToolTip.h` (Public)


#### class `SDocumentationToolTip`  
`class SDocumentationToolTip : public SCompoundWidget`  
_L28-182_
- inherits: `SCompoundWidget`
- L33 _public function_ `SLATE_BEGIN_ARGS( SDocumentationToolTip ) : _Text() , _Shortcut() , _Style( TEXT("Documentation.SDocumentationTooltip") ) , _SubduedStyle( TEXT("Documentation.SDocumentationTooltipSubdued") ) , _HyperlinkTextStyle( TEXT("Documentation.SDocumentationTooltipHyperlinkText") ) , _HyperlinkButtonStyle( TEXT("Documentation.SDocumentationTooltipHyperlinkButton") ) , _ColorAndOpacity( FLinearColor::Black ) , _AddDocumentation( true ) , _DocumentationMargin(0) , _OverrideExtendedToolTipContent(nullptr) , _OverridePromptContent(nullptr) , _AlwaysExpandTooltip(false) , _Content()`
- L50 _public prototype_ `SLATE_ATTRIBUTE( FText, Text ) SLATE_ATTRIBUTE(FText, Shortcut) SLATE_ARGUMENT( FName, Style ) SLATE_ARGUMENT( FName, SubduedStyle ) SLATE_ARGUMENT( FName, HyperlinkTextStyle ) SLATE_ARGUMENT( FName, HyperlinkButtonStyle ) SLATE_ATTRIBUTE( FSlateColor, ColorAndOpacity ) SLATE_ARGUMENT( bool, AddDocumentation ) SLATE_ARGUMENT( FMargin, DocumentationMargin ) SLATE_ARGUMENT( FString, DocumentationLink ) SLATE_ARGUMENT( FString, ExcerptName ) SLATE_ARGUMENT(TSharedPtr<SWidget>, OverrideExtendedToolTipContent) SLATE_ARGUMENT(TSharedPtr<SWidget>, OverridePromptContent) SLATE_ATTRIBUTE(bool, AlwaysExpandTooltip)` — The text displayed in this tool tip
- L102 _public prototype_ `void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime );`
- L104 _public prototype_ `bool IsInteractive() const;`
- L106 _public function_ `virtual const FText& GetTextTooltip() const`
- L117 _public prototype_ `void AddDocumentation(TSharedPtr< SVerticalBox > VerticalBox);` — Adds slots to the provided Vertical Box containing the documentation information. If you specify not to add it (AddDocumentation = false) you may call this externally to do custom tooltip layout @param	VerticalBox	The vertical box to add it to
- L119 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L123 _private prototype_ `EVisibility GetOverriddenFullToolTipVisibility() const;`
- L125 _private prototype_ `void ConstructSimpleTipContent();`
- L127 _private prototype_ `void ConstructFullTipContent();`
- L129 _private prototype_ `FReply ReloadDocumentation();`
- L131 _private prototype_ `void CreateExcerpt( FString FileSource, FString ExcerptName );`
- L133 _private prototype_ `EVisibility GetPromptVisibility() const;`
- L134 _private prototype_ `EVisibility GetFullTipVisibility() const;`
- L135 _private prototype_ `FOptionalSize GetPromptHeight() const;`
- L136 _private prototype_ `EVisibility GetControlVisibility() const;`
- L137 _private prototype_ `EVisibility GetShortcutVisibility() const;`
- L139 _private prototype_ `bool ShouldAlwaysExpand() const;`
- L143 _private member_ `TAttribute< FText > TextContent;` — Text block widget
- L144 _private member_ `TAttribute< FText > Shortcut;`
- L145 _private member_ `TSharedPtr< SWidget > OverrideContent;`
- L146 _private member_ `TSharedPtr< SWidget > OverrideFullTooltipContent;`
- L147 _private member_ `TSharedPtr< SWidget > OverridePromptContent;`
- L148 _private member_ `FTextBlockStyle StyleInfo;`
- L149 _private member_ `FTextBlockStyle SubduedStyleInfo;`
- L150 _private member_ `FTextBlockStyle HyperlinkTextStyleInfo;`
- L151 _private member_ `FTextBlockStyle KeybindStyleInfo;`
- L152 _private member_ `FButtonStyle HyperlinkButtonStyleInfo;`
- L153 _private member_ `TAttribute< FSlateColor > ColorAndOpacity;`
- L156 _private member_ `FString DocumentationLink;` — The link to the documentation
- L157 _private member_ `FString ExcerptName;`
- L160 _private member_ `TSharedPtr< SBox > WidgetContent;` — Content widget
- L162 _private member_ `TSharedPtr< SBox > SimpleTipContent;`
- L163 _private member_ `bool IsDisplayingDocumentationLink;`
- L165 _private member_ `TSharedPtr< SBox > FullTipContent;`
- L166 _private member_ `TSharedPtr< SBox > PromptContent;`
- L167 _private member_ `TSharedPtr< SBox > DocumentationControlBox;`
- L168 _private member_ `TSharedPtr< SHorizontalBox > DocumentationControls;`
- L170 _private member_ `TSharedPtr< IDocumentationPage > DocumentationPage;`
- L171 _private member_ `bool IsShowingFullTip;`
- L173 _private member_ `bool bAddDocumentation;`
- L174 _private member_ `FMargin DocumentationMargin;`
- L176 _private member_ `double TransitionStartTime;`
- L177 _private member_ `float TransitionLength;`
- L179 _private member_ `bool bFullTipContentIsReady;`
- L180 _private member_ `bool bIsPromptVisible;`
- L181 _private member_ `TAttribute< bool > AlwaysExpandTooltip;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API DOCUMENTATION_API`

### `Source/Editor/Documentation/Public/TutorialMetaData.h` (Public)


#### class `FTutorialMetaData`  
`class FTutorialMetaData : public FTagMetaData`  
_L9-30_
- inherits: `FTagMetaData`
- L12 _public function_ `SLATE_METADATA_TYPE(FTutorialMetaData, FTagMetaData) FTutorialMetaData(FName InTag, FString InTabType, FString InFriendlyName = FString()) : FTagMetaData(InTag) , TabTypeToOpen(InTabType) , FriendlyName(InFriendlyName)`
- L21 _public function_ `FTutorialMetaData(FName InTag) : FTagMetaData(InTag)`
- L26 _public member_ `FString TabTypeToOpen;` — The type of tab we want to open for this widget where relevant.
- L29 _public member_ `FString FriendlyName;` — User friendly display name

#### class `FGraphNodeMetaData`  
`class FGraphNodeMetaData : public FTutorialMetaData`  
_L32-49_
- inherits: `FTutorialMetaData`
- L35 _public function_ `SLATE_METADATA_TYPE(FGraphNodeMetaData, FTutorialMetaData) FGraphNodeMetaData(FName InTag, FString InFriendlyName = FString(), FString InOuterName = FString(), FString InTabType = FString()) : FTutorialMetaData(InTag, InTabType, InFriendlyName) , OuterName(InOuterName)`
- L44 _public member_ `FGuid GUID;` — GUID for the node
- L47 _public member_ `FString OuterName;` — Name of the outer (which should be the blueprint)
