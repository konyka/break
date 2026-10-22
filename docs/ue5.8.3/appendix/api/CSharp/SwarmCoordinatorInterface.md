# CSharp / SwarmCoordinatorInterface

- project root: `Source/Programs/UnrealSwarm/SwarmCoordinatorInterface`
- files: 2; symbols: 26
- symbol kinds: class=1, enum=2, enumerator=13, field=4, interface=1, method=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealSwarm/SwarmCoordinatorInterface/Properties/AssemblyInfo.cs` (SwarmCoordinatorInterface)
_(no declarations)_


### `Source/Programs/UnrealSwarm/SwarmCoordinatorInterface/SwarmCoordinatorInterface.cs` (SwarmCoordinatorInterface)


#### enum `SwarmCoordinatorInterface.AgentState`  
`public enum AgentState`  
_public; L16-29_
- attrs: `[Serializable]`
- L18 _public* enumerator_ `Unknown = 0`
- L19 _public* enumerator_ `Available = 1`
- L20 _public* enumerator_ `Working = 2`
- L21 _public* enumerator_ `Blocked = 3`
- L22 _public* enumerator_ `Starving = 4`
- L23 _public* enumerator_ `Dead = 5`
- L24 _public* enumerator_ `Standalone = 6`
- L25 _public* enumerator_ `Closed = 7`
- L26 _public* enumerator_ `Restarting = 8`
- L27 _public* enumerator_ `Restarted = 9`
- L28 _public* enumerator_ `Busy = 10`

#### class `SwarmCoordinatorInterface.AgentInfo`  
`public class AgentInfo`  
_public; L32-39_
- attrs: `[Serializable]`
- L35 _public field_ `public string Name = System.Net.Dns.GetHostName()`
- L36 _public field_ `public AgentState State = AgentState.Unknown`
- L37 _public field_ `public Version Version = new Version( 0, 0, 0, 0 )`
- L38 _public field_ `public Hashtable Configuration = new Hashtable()`

#### enum `SwarmCoordinatorInterface.PingResponse`  
`public enum PingResponse`  
_public; L42-46_
- attrs: `[Serializable]`
- L44 _public* enumerator_ `Success`
- L45 _public* enumerator_ `Restart`

#### interface `SwarmCoordinatorInterface.ISwarmCoordinator`  
`public interface ISwarmCoordinator`  
_public; L48-79_
- L55 _public* method_ `PingResponse Ping( AgentInfo UpdatedInfo )`
- L60 _public* method_ `Int32 GetUniqueHandle()`
- L67 _public* method_ `List<AgentInfo> GetAvailableAgents( Hashtable RequestedConfiguration )`
- L72 _public* method_ `Int32 RestartAgentGroup( string GroupNameToRestart )`
- L78 _public* method_ `Int32 Method( Hashtable InParameters, ref Hashtable OutParameters )`
