# CSharp / Unreal.TestAdapter

- project root: `Source/Programs/UnrealVS/Unreal.TestAdapter`
- files: 3; symbols: 15
- symbol kinds: class=2, field=3, method=10
- access marked `*` is implicit (not written in source)

### `Source/Programs/UnrealVS/Unreal.TestAdapter/Properties/AssemblyInfo.cs` (Unreal.TestAdapter)
_(no declarations)_


### `Source/Programs/UnrealVS/Unreal.TestAdapter/TestDiscoverer.cs` (Unreal.TestAdapter)


#### class `Unreal.TestAdapter.TestDiscoverer`  
`class TestDiscoverer : ITestDiscoverer`  
_internal*; L17-171_
- attrs: `[FileExtension(".exe")] [DefaultExecutorUri("executor://UnrealTestExecutor")]`
- inherits: `ITestDiscoverer`
- L19 _private* field_ `static readonly Uri ExecutorUri = new Uri("executor://UnrealTestExecutor")`
- L20 _internal field_ `internal static readonly TestProperty DisabledTestProperty = TestProperty.Register("TestDiscoverer.DisabledTestProperty", "DisabledTestProperty", string.Empty, string.Empty, typeof(bool), (object o) => o is bool, TestPropertyAttributes.Hidden, typeof(TestDiscov ...`
- L22-33 _public method_ `public void DiscoverTests(IEnumerable<string> sources, IDiscoveryContext discoveryContext, IMessageLogger logger, ITestCaseDiscoverySink discoverySink)`
- L35-80 _private* method_ `string GetTestCaseXml(string source, IMessageLogger logger)`
- L82-113 _private* method_ `static void ParseXml(string xml, ITestCaseDiscoverySink discoverySink, string source)`
- L114-170 _private* method_ `static bool ParseTestCase(XmlReader xmlReader, string source, out TestCase testCase)`

### `Source/Programs/UnrealVS/Unreal.TestAdapter/TestExecutor.cs` (Unreal.TestAdapter)


#### class `Unreal.TestAdapter.TestExecutor`  
`class TestExecutor : ITestExecutor`  
_internal*; L15-158_
- attrs: `[ExtensionUri("executor://UnrealTestExecutor")]`
- inherits: `ITestExecutor`
- L17 _private* field_ `bool WasCancelled = false`
- L19-22 _public method_ `public void Cancel()`
- L24-26 _public method_ `public void RunTests(IEnumerable<string> sources, IRunContext runContext, IFrameworkHandle frameworkHandle)`
- L28-46 _public method_ `public void RunTests(IEnumerable<TestCase> tests, IRunContext runContext, IFrameworkHandle frameworkHandle)`
- L48-96 _private* method_ `void RunTestCase(TestCase testCase, IFrameworkHandle frameworkHandle, bool debug)`
- L98-124 _private* method_ `void ParseResult(string xmlString, TestResult testResult)`
- L126-157 _private* method_ `void ParseTestCaseResult(XmlReader xml, TestResult testResult)`
