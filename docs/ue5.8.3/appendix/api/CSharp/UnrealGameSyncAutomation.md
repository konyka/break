# CSharp / UnrealGameSyncAutomation

- project root: `Source/Programs/UnrealGameSync/UnrealGameSyncAutomation`
- files: 2; symbols: 14
- symbol kinds: class=1, enum=2, enumerator=9, method=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealGameSync/UnrealGameSyncAutomation/Program.cs` (UnrealGameSyncAutomation)


#### class `UnrealGameSyncAutomation.Program`  
`class Program`  
_internal*; L12-78_
- L31-45 _private* method_ `static void Main()`
- L47-77 _private* method_ `static Tuple<AutomationRequestResult, byte[]> SendRequest(AutomationRequestType Request, byte[] RequestData)`

#### enum `UnrealGameSyncAutomation.Program.AutomationRequestType`  
`enum AutomationRequestType`  
_private*; L14-19_
- L16 _public* enumerator_ `SyncProject`
- L17 _public* enumerator_ `FindProject`
- L18 _public* enumerator_ `OpenProject`

#### enum `UnrealGameSyncAutomation.Program.AutomationRequestResult`  
`enum AutomationRequestResult`  
_private*; L21-29_
- L23 _public* enumerator_ `Ok`
- L24 _public* enumerator_ `Invalid`
- L25 _public* enumerator_ `Busy`
- L26 _public* enumerator_ `Canceled`
- L27 _public* enumerator_ `Error`
- L28 _public* enumerator_ `NotFound`

### `Source/Programs/UnrealGameSync/UnrealGameSyncAutomation/Properties/AssemblyInfo.cs` (UnrealGameSyncAutomation)
_(no declarations)_

