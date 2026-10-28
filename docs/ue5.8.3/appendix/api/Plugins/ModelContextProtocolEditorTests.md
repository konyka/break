# Plugins / ModelContextProtocolEditorTests

- module root: `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditorTests`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: AssetDefinition, Blutility, CoreUObject, Engine, HTTP, HTTPServer, Json, JsonUtilities, ModelContextProtocol, ModelContextProtocolEditor, ModelContextProtocolEngine, ModelContextProtocolTests, Slate, SlateCore, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEditorTests/Private/Mocks/MockToolsetDefinition.h` (Private)


#### class `UMockToolsetDefinition`  
`class UMockToolsetDefinition : public UToolsetDefinition`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UToolsetDefinition`
- desc: Mock UToolsetDefinition subclass for testing ToolsetRegistry integration with MCP.
- L20 _public prototype_ `static FString Greet(const FString& Name);` — `UFUNCTION(meta = (AICallable))` — Greets a person by name
- L24 _public prototype_ `static int32 Add(int32 A, int32 B);` — `UFUNCTION(meta = (AICallable))` — Adds two numbers together
