# CSharp / Mutable.Automation

- project root: `Source/Programs/AutomationTool/Mutable`
- files: 1; symbols: 7
- symbol kinds: class=1, ctor=1, field=3, method=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/AutomationTool/Mutable/RunMutableCommandlet.cs` (Mutable.Automation)


#### class `RunMutableCommandlet.Automation.RunMutableCommandlet`  
`public sealed class RunMutableCommandlet : UnrealTestNode<UnrealTestConfiguration>`  
_public; L11-83_
- inherits: `UnrealTestNode<UnrealTestConfiguration>`
- desc: Simple UnrealTestNode designed to allow the caller to specify a timeout value for the execution of the targetted mutable commandlet
- L16 _private* field_ `string CommandletName = ""` — The name of the commandlet to run
- L21 _private* field_ `string CommandletArguments = ""` — The arguments that will get fed to the comandlet.
- L26 _private* field_ `float CommandletTimeoutTime = 600f` — The max amount of time (seconds) that the commandlet will be allowed to run.
- L29-39 _public ctor_ `public RunMutableCommandlet(UnrealTestContext InContext) : base(InContext)`
- L42-68 _public method_ `public override UnrealTestConfiguration GetConfiguration()`
- L70-82 _protected method_ `protected override UnrealProcessResult GetExitCodeAndReason(StopReason InReason, UnrealLog InLog, UnrealRoleArtifacts InArtifacts, out string ExitReason, out int ExitCode)`
