# CSharp / PostBadgeStatus

- project root: `Source/Programs/UnrealGameSync/PostBadgeStatus`
- files: 2; symbols: 20
- symbol kinds: class=2, enum=1, enumerator=5, field=7, method=3, property=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/PostBadgeStatus/Program.cs` (PostBadgeStatus)


#### class `WriteBadgeStatus.Program`  
`class Program`  
_internal*; L13-181_
- L15-79 _private* method_ `static int Main(string[] Args)`
- L81-94 _private* method_ `static string? ParseParam(List<string> Arguments, string ParamName)`
- L120-180 _private* method_ `static int SendRequest(string URI, string Resource, string Method, string? RequestBody = null, params string[] QueryParams)`

#### class `WriteBadgeStatus.Program.BuildData`  
`class BuildData`  
_private*; L96-118_
- L107 _public field_ `public int ChangeNumber`
- L108 _public field_ `public required string BuildType`
- L109 _public field_ `public BuildDataResult Result`
- L110 _public field_ `public required string Url`
- L111 _public field_ `public required string Project`
- L112 _public field_ `public required string ArchivePath`
- L113 _public field_ `public JsonElement? Metadata`
- L115 _public property_ `public bool IsSuccess => ...`
- L117 _public property_ `public bool IsFailure => ...`

#### enum `WriteBadgeStatus.Program.BuildData.BuildDataResult`  
`public enum BuildDataResult`  
_public; L98-105_
- L100 _public* enumerator_ `Starting`
- L101 _public* enumerator_ `Failure`
- L102 _public* enumerator_ `Warning`
- L103 _public* enumerator_ `Success`
- L104 _public* enumerator_ `Skipped`

### `Source/Programs/UnrealGameSync/PostBadgeStatus/Properties/AssemblyInfo.cs` (PostBadgeStatus)
_(no declarations)_

