# Runtime / XmlParser

- module root: `Source/Runtime/XmlParser`
- headers: 4; symbols: 69
- symbol kinds: class=5, enum=1, enumerator=2, function=7, member=13, namespace=1, prototype=40
- PrivateDependencyModuleNames: Core

### `Source/Runtime/XmlParser/Public/FastXml.h` (Public)


#### class `FFastXml`  
`class FFastXml`  
_L23-45_
- desc: Fast XML parser based on John W. Ratcliff's "FastXml" (see FastXml.tps and http://codesuppository.blogspot.com/2009/02/fastxml-extremely-lightweight-stream.html) This is a simple XML parser that can load XML files very quickly.  The class has a single static method, ParseXmlFile() for loading XML files.  The parser is designed to load files efficiently, but may not support all XML features or be resilient to malformed data.  Unlike the FXmlFile class, FFastXml does not generate an XML node tree.  Instead, you must supply a callback class using IFastXmlCallback and respond to elements and attributes as they are parsed.  Call the ParseXmlFile() function and pass in either the full path to the XML file to parse (XmlFilePath parameter), or load the file yourself and pass the contents using the XmlFileContents parameter.  One of either XmlFilePath or XmlFileContents must be valid for ParseXmlFile() to work. Remember to add a module dependency on "XmlParser" in order to be able to call FFastXml::ParserXmlFile().
- L43 _public prototype_ `static bool ParseXmlFile( class IFastXmlCallback* Callback, const TCHAR* XmlFilePath, TCHAR* XmlFileContents, class FFeedbackContext* FeedbackContext, const bool bShowSlowTaskDialog, const bool bShowCancelButton, FText& OutErrorMessage, int32& OutErrorLineNumber );` — Quickly parse an XML file.  Pass in your implementation of the IFastXmlCallback interface with code to handle parsed elements and attributes, along with either the full path to the XML file to load, or a string with the full XML file content. @param	Callback			As the parser encounters XML elements or attributes, methods on this callback object will be called @param	XmlFilePath			The path on disk to the XML file to load, or an empty string if you'll be passing the XML file content in directly using the XmlFileContents parameter. @param	XmlFileContents		The full contents of the file to parse, or an empty string if you've passed a full path to the file to parse using the XmlFilePath parameter.  Note that this string will be modified during the parsing process, so make a copy of it first if you need it for something else (uncommon.) @param	FeedbackContext		Optional feedback context for reporting warnings or progress (GWarn is typically passed in.)  You can pass nullptr if you don't want any progress reported. @param	bShowSlowTaskDialog	True if we should display a 'please wait' dialog while we parse the file, if the feedback context supports that @param	bShowCancelButton	Whether the user is allowed to cancel the load of this XML file while in progress.  If the user cancels loading, an appropriate error message will be returned.  Only applies when bShowSlowTaskDialog is also enabled, and for feedback contexts that support cancel buttons. @param	OutErrorMessage		If anything went wro

#### class `IFastXmlCallback`  
`class IFastXmlCallback`  
_L54-107_
- desc: Create your own class that implements the IFastXmlCallback interface to process the XML elements as they are loaded by FFastXml::ParseXmlFile().  You'll receive a ProcessElement() call for every XML element that is encountered, along with a corresponding ProcessClose() when that element's scope has ended. ProcessAttribute() will be called for any attributes found within the scope of the current element.
- L67 _public prototype_ `virtual bool ProcessXmlDeclaration( const TCHAR* ElementData, int32 XmlFileLineNumber ) = 0;` — Called after the XML's header is parsed.  This is usually the first call that you'll get back. @param	ElementData			Optional data for this element, nullptr if none @param	XmlFileLineNumber	Line number in the XML file we're on @return	You should return true to continue processing the file, or false to stop processing immediately.
- L79 _public prototype_ `virtual bool ProcessElement( const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber ) = 0;` — Called when a new XML element is encountered, starting a new scope.  You'll receive a call to ProcessClose() when this element's scope has ended. @param	ElementName			The name of the element @param	ElementData			Optional data for this element, nullptr if none @param	XmlFileLineNumber	The line number in the XML file we're on @return	You should return true to continue processing the file, or false to stop processing immediately.
- L89 _public prototype_ `virtual bool ProcessAttribute( const TCHAR* AttributeName, const TCHAR* AttributeValue ) = 0;` — Called when an XML attribute is encountered for the current scope's element. @param	AttributeName	The name of the attribute @param	AttributeValue	The value of the attribute @return	You should return true to continue processing the file, or false to stop processing immediately.
- L98 _public prototype_ `virtual bool ProcessClose( const TCHAR* Element ) = 0;` — Called when an element's scope ends in the XML file @param	ElementName		Name of the element whose scope closed @return	You should return true to continue processing the file, or false to stop processing immediately.
- L105 _public prototype_ `virtual bool ProcessComment( const TCHAR* Comment ) = 0;` — Called when a comment is encountered.  This can happen pretty much anywhere in the file. @param	Comment		The comment text

### `Source/Runtime/XmlParser/Public/XmlFile.h` (Public)


#### enum `EConstructMethod::Type`  
`enum Type`  
_L17-21_
- L19 _public enumerator_ `ConstructFromFile`
- L20 _public enumerator_ `ConstructFromBuffer`

#### class `FXmlFile`  
`class FXmlFile`  
_L25-126_
- desc: Class representing an XML file
- L30 _public function_ `FXmlFile() : RootNode(nullptr), bFileLoaded(false)` — Constructs the file without a path
- L37 _public prototype_ `FXmlFile(const FString& InFile, EConstructMethod::Type ConstructMethod = EConstructMethod::ConstructFromFile);` — Constructs the file with the passed path. InFile is either treated as a filename to open, or as a text buffer to load. @param	InFile				The path/text to use @param	ConstructMethod		Whether to load a file of use the string as a buffer of xml data
- L38 _public function_ `~FXmlFile()`
- L40 _public prototype_ `FXmlFile(const FXmlFile& rhs) = delete;`
- L41 _public prototype_ `FXmlFile& operator=(const FXmlFile& rhs) = delete;`
- L49 _public prototype_ `bool LoadFile(const FString& Path, EConstructMethod::Type ConstructMethod = EConstructMethod::ConstructFromFile);` — Loads the file with the passed path. Path is either treated as a filename to open, or as a text buffer to load. @param	Path				The path/text to use @param	ConstructMethod		Whether to load a file of use the string as a buffer of xml data
- L51 _public prototype_ `FString GetLastError() const;` — Gets the last error message from the class
- L53 _public prototype_ `void Clear();` — Clears the file of all internals. Note: Makes any existing pointers to FXmlNode's INVALID
- L55 _public prototype_ `bool IsValid() const;` — Checks to see if a file is loaded
- L62 _public prototype_ `const FXmlNode* GetRootNode() const;` — Returns the root node of the loaded file. nullptr if no file loaded. It is assumed that there will always be one and only one root node. @return						Pointer to root node
- L69 _public prototype_ `FXmlNode* GetRootNode();` — Returns the root node of the loaded file. nullptr if no file loaded. It is assumed that there will always be one and only one root node. @return						Pointer to root node
- L76 _public prototype_ `bool Save(const FString& Path);` — Write to disk, UTF-16 format only at the moment @param	Path				File path to save to @return						Whether writing the XML to a file succeeded
- L85 _public prototype_ `void EnableAttemptToPreserveWhitespaceHack();` — Turns on a specific hack that is only used by the crash report client in order to retain newlines for callstacks. This is important on the server side when we display the callstacks to content creators. Without the content-whitespace, they're bascially illegible. Neither version of the DOM we create is technically true to the XML spec.
- L90 _private prototype_ `void PreProcessInput(TArray<FString>& Input);` — Pre-processes the file doing anything necessary (such as removing comments)
- L92 _private prototype_ `void WhiteOut(TArray<FString>& Input, int32 LineStart, int32 LineEnd, int32 IndexStart, int32 IndexEnd);` — Whites of the text at the specified locations in a passed-in array
- L94 _private prototype_ `void Tokenize(FStringView Input, TArray<FString>& Tokens);` — Converts the passed input into a list of tokens for parsing
- L96 _private prototype_ `TArray<FString> Tokenize(const TArray<FString>& Input);` — Converts the passed input into a list of tokens for parsing
- L101 _private prototype_ `static void AddAttribute(const FString& InToken, TArray<FXmlAttribute>& OutAttributes);` — Add an attribute to the passed-in array. This makes the assumption that an attribute comes in as one 'token' (i.e. no spaces between tag="value").
- L103 _private prototype_ `FXmlNode* CreateRootNode(TArrayView<const FString> Tokens);` — Recursively creates nodes from the list of tokens
- L105 _private prototype_ `void HookUpNextPtrs(FXmlNode* Node);` — Hook next ptrs up recursively
- L107 _private prototype_ `void CreateNodes(const TArray<FString>& Tokens);` — Creates the internal file representation as a bunch of FXmlNode's
- L109 _private prototype_ `static void WriteNodeHierarchy(const FXmlNode& Node, const FString& Indent, FString& Output);` — Writes a node hierarchy at the given root to a string
- L114 _private member_ `FString LoadedFile;` — The passed-in path of the loaded file (might be absolute or relative)
- L116 _private member_ `FString ErrorMessage;` — An error message generated on errors to return to the client
- L118 _private member_ `FXmlNode* RootNode;` — A pointer to the root node
- L120 _private member_ `bool bFileLoaded;` — Flag for whether a file is loaded or not
- L122 _private member_ `bool bCreationFailed;` — Flag for whether the node creation process failed or not
- L125 _private member_ `bool bHackAttemptToPreserveWhitespace = false;` — Flag for the whitespace hack used in the crash report client

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace EConstructMethod`

### `Source/Runtime/XmlParser/Public/XmlNode.h` (Public)


#### class `FXmlAttribute`  
`class FXmlAttribute`  
_L12-33_
- L15 _public function_ `FXmlAttribute(const FString& InTag, const FString& InValue) : Tag(InTag) , Value(InValue)`
- L22 _public prototype_ `const FString& GetTag() const;` — Gets the tag of the attribute
- L25 _public prototype_ `const FString& GetValue() const;` — Gets the value of the attribute
- L29 _private member_ `FString Tag;` — The tag string
- L32 _private member_ `FString Value;` — The value string

#### class `FXmlNode`  
`class FXmlNode`  
_L36-108_
- desc: Xml Node representing a line in an xml file
- L43 _private function_ `FXmlNode() : NextNode(nullptr)` — Default ctor, private for FXmlFile use only
- L45 _private function_ `FXmlNode(const FXmlNode& rhs)` — No copy ctor allowed
- L47 _private function_ `~FXmlNode()` — dtor
- L52 _private prototype_ `void Delete();` — Recursively deletes the nodes for cleanup
- L57 _public prototype_ `const FXmlNode* GetNextNode() const;` — Gets the next node in a list of nodes
- L59 _public prototype_ `const TArray<FXmlNode*>& GetChildrenNodes() const;` — Gets a list of children nodes
- L61 _public prototype_ `const FXmlNode* GetFirstChildNode() const;` — Gets the first child of this node which can be iterated into with GetNextNode
- L63 _public prototype_ `const FXmlNode* FindChildNode(const FString& InTag) const;` — Finds the first child node that contains the specified tag
- L65 _public prototype_ `FXmlNode* FindChildNode(const FString& InTag);` — Finds the first child node that contains the specified tag
- L67 _public prototype_ `const FString& GetTag() const;` — Gets the tag of the node
- L69 _public prototype_ `const FString& GetContent() const;` — Gets the value of the node
- L71 _public prototype_ `void SetContent(const FString& InContent);` — Sets the new value of the node
- L73 _public prototype_ `void SetAttributes(const TArray<FXmlAttribute>& InAttributes);` — Sets the attributes of the node
- L80 _public function_ `const TArray<FXmlAttribute>& GetAttributes() const` — Gets all of the attributes in this node @return	List of attributes in this node
- L86 _public prototype_ `FString GetAttribute(const FString& InTag) const;` — Gets an attribute that corresponds with the passed-in tag
- L94 _public prototype_ `void AppendChildNode(const FString& InTag, const FString& InContent = FString(), const TArray<FXmlAttribute>& InAttributes = TArray<FXmlAttribute>());` — Adds a child node to this node @param	InTag				The tag of the child node @param	InContent			(optional) The content of the child node @param	InAttributes		(optional) An array of attributes of the child node
- L98 _private member_ `TArray<FXmlNode*> Children;` — The list of children nodes
- L100 _private member_ `TArray<FXmlAttribute> Attributes;` — Attributes of this node
- L102 _private member_ `FString Tag;` — Tag of the node
- L104 _private member_ `FString Content;` — Content of the node
- L106 _private member_ `FXmlNode* NextNode;` — Next pointer

### `Source/Runtime/XmlParser/Public/XmlParser.h` (Public)
_(no declarations extracted)_
