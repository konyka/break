# CSharp / ScriptGeneratorUbtPlugin.ubtplugin

- project root: `Plugins/ScriptPlugin/Source/ScriptGeneratorUbtPlugin`
- files: 4; symbols: 44
- symbol kinds: class=6, ctor=3, field=1, method=33, property=1
- access marked `*` is implicit (not written in source)

### `Plugins/ScriptPlugin/Source/ScriptGeneratorUbtPlugin/GenericScriptCodeGenerator.cs` (ScriptGeneratorUbtPlugin.ubtplugin)


#### class `ScriptGeneratorUbtPlugin.GenericScriptCodeGeneratorStringBuilderExtensinos`  
`static class GenericScriptCodeGeneratorStringBuilderExtensinos`  
_internal*; L14-48_
- L16-19 _public method_ `public static StringBuilder AppendGenericWrapperFunctionDeclaration(this StringBuilder builder, UhtClass classObj, string functionName)`
- L21-37 _public method_ `public static StringBuilder AppendGenericFunctionParamDeclaration(this StringBuilder builder, UhtClass _ , UhtProperty property)`
- L39-42 _public method_ `public static StringBuilder AppendGenericObjectDeclarationFromContext(this StringBuilder builder, UhtClass _ )`
- L44-47 _public method_ `public static StringBuilder AppendGenericReturnValueHandler(this StringBuilder builder, UhtClass _1 , UhtProperty? _2 )`

#### class `ScriptGeneratorUbtPlugin.GenericScriptCodeGenerator`  
`internal class GenericScriptCodeGenerator : ScriptCodeGeneratorBase`  
_internal; L50-202_
- inherits: `ScriptCodeGeneratorBase`
- L52-55 _public ctor_ `public GenericScriptCodeGenerator(IUhtExportFactory factory) : base(factory)`
- L57-82 _protected method_ `protected override bool CanExportClass(UhtClass classObj)`
- L84-136 _protected method_ `protected override void ExportClass(StringBuilder builder, UhtClass classObj)`
- L138-146 _protected method_ `protected void ExportFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L148-170 _protected method_ `protected static void ExportProperty(StringBuilder builder, UhtClass classObj, UhtProperty property)`
- L172-201 _protected method_ `protected override void Finish(StringBuilder builder, List<UhtClass> classes)`

### `Plugins/ScriptPlugin/Source/ScriptGeneratorUbtPlugin/LuaScriptCodeGenerator.cs` (ScriptGeneratorUbtPlugin.ubtplugin)


#### class `ScriptGeneratorUbtPlugin.LuaScriptCodeGeneratorStringBuilderExtensinos`  
`static class LuaScriptCodeGeneratorStringBuilderExtensinos`  
_internal*; L14-101_
- L16-19 _public method_ `public static StringBuilder AppendLuaWrapperFunctionDeclaration(this StringBuilder builder, UhtClass classObj, string functionName)`
- L21-24 _public method_ `public static StringBuilder AppendLuaObjectDeclarationFromContext(this StringBuilder builder, UhtClass classObj)`
- L26-100 _public method_ `public static StringBuilder AppendLuaReturnValueHandler(this StringBuilder builder, UhtClass _ , UhtProperty? returnValue, string? returnValueName)`

#### class `ScriptGeneratorUbtPlugin.LuaScriptCodeGenerator`  
`internal class LuaScriptCodeGenerator : ScriptCodeGeneratorBase`  
_internal; L103-485_
- inherits: `ScriptCodeGeneratorBase`
- L105-108 _public ctor_ `public LuaScriptCodeGenerator(IUhtExportFactory factory) : base(factory)`
- L110-142 _protected method_ `protected override bool CanExportClass(UhtClass classObj)`
- L144-162 _protected method_ `protected override bool CanExportFunction(UhtClass classObj, UhtFunction function)`
- L164-167 _protected method_ `protected override bool CanExportProperty(UhtClass classObj, UhtProperty property)`
- L169-201 _private method_ `private static bool IsPropertyTypeSupported(UhtProperty property)`
- L203-300 _protected method_ `protected override void ExportClass(StringBuilder builder, UhtClass classObj)`
- L302-324 _protected method_ `protected void ExportFunction(StringBuilder builder, UhtClass classObj, UhtFunction function)`
- L326-368 _protected method_ `protected void ExportProperty(StringBuilder builder, UhtClass classObj, UhtProperty property)`
- L370-403 _protected method_ `protected override void Finish(StringBuilder builder, List<UhtClass> classes)`
- L405-484 _protected method_ `protected override StringBuilder AppendInitializeFunctionDispatchParam(StringBuilder builder, UhtClass classObj, UhtFunction? function, UhtProperty property, int propertyIndex)`

### `Plugins/ScriptPlugin/Source/ScriptGeneratorUbtPlugin/ScriptCodeGeneratorBase.cs` (ScriptGeneratorUbtPlugin.ubtplugin)


#### class `ScriptGeneratorUbtPlugin.ScriptCodeGeneratorBase`  
`internal abstract class ScriptCodeGeneratorBase`  
_internal; L16-236_
- L18 _public field_ `public readonly IUhtExportFactory Factory`
- L19 _public property_ `public UhtSession Session => ...`
- L21-24 _public ctor_ `public ScriptCodeGeneratorBase(IUhtExportFactory factory)`
- L29-62 _public method_ `public void Generate()` — Export all the classes in all the packages
- L71-85 _private method_ `private void QueueClassExports(UhtPackage package, UhtType type, List<UhtClass> classes, List<Task?> tasks)` — Collect the classes to be exported for the given package and type
- L92-95 _protected method_ `protected virtual bool CanExportClass(UhtClass classObj)` — Test to see if the given class should be exported
- L103-128 _protected method_ `protected virtual bool CanExportFunction(UhtClass classObj, UhtFunction function)` — Test to see if the given function should be exported
- L136-163 _protected method_ `protected virtual bool CanExportProperty(UhtClass classObj, UhtProperty property)` — Test to see if the given property should be exported
- L169-175 _private method_ `private void ExportClass(UhtClass classObj)` — Export the given class
- L177-183 _private method_ `private void Finish(List<UhtClass> classes)`
- L185 _protected method_ `protected abstract void ExportClass(StringBuilder builder, UhtClass classObj)`
- L187 _protected method_ `protected abstract void Finish(StringBuilder builder, List<UhtClass> classes)`
- L189-200 _protected method_ `protected virtual StringBuilder AppendInitializeFunctionDispatchParam(StringBuilder builder, UhtClass classObj, UhtFunction? function, UhtProperty property, int propertyIndex)`
- L202-235 _protected method_ `protected virtual StringBuilder AppendFunctionDispatch(StringBuilder builder, UhtClass classObj, UhtFunction function)`

### `Plugins/ScriptPlugin/Source/ScriptGeneratorUbtPlugin/ScriptGenerator.cs` (ScriptGeneratorUbtPlugin.ubtplugin)


#### class `ScriptGeneratorUbtPlugin.ScriptGenerator`  
`class ScriptGenerator`  
_internal*; L9-38_
- attrs: `[UnrealHeaderTool]`
- L12-37 _private method_ `private static void ScriptGeneratorExporter(IUhtExportFactory Factory)` — attrs: `[UhtExporter(Name = "ScriptPlugin", Description = "Generic Script Plugin Generator", Options = UhtExporterOptions.Default, ModuleName="ScriptPlugin")]`
