# CSharp / SwarmCommonUtils

- project root: `Source/Programs/UnrealSwarm/SwarmCommonUtils`
- files: 2; symbols: 6
- symbol kinds: class=2, method=4
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealSwarm/SwarmCommonUtils/Properties/AssemblyInfo.cs` (SwarmCommonUtils)
_(no declarations)_


### `Source/Programs/UnrealSwarm/SwarmCommonUtils/Utils.cs` (SwarmCommonUtils)


#### class `SwarmCommonUtils.NetworkUtils`  
`public static class NetworkUtils`  
_public; L16-58_
- L19 _private* method_ `static extern int WINAPI_GetBestInterface(UInt32 DestAddr, out UInt32 BestIfIndex)` — attrs: `[DllImport("iphlpapi.dll", SetLastError = true, EntryPoint = "GetBestInterface")]`
- L21-42 _public method_ `public static NetworkInterface GetBestInterface(IPAddress Address)`
- L44-57 _public method_ `public static IPAddress GetInterfaceIPv4Address(NetworkInterface NetworkInterface)`

#### class `SwarmCommonUtils.ObjectUtils`  
`public static class ObjectUtils`  
_public; L60-77_
- L62-76 _public method_ `public static T Duplicate<T>(T SourceObject)`
