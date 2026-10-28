# Plugins / JsonBlueprintGraph

- module root: `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintGraph`
- headers: 4; symbols: 26
- symbol kinds: class=3, delegate=1, prototype=22
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, Engine, GraphEditor, InputCore, Json, JsonBlueprintUtilities, Kismet, KismetCompiler, KismetWidgets, Projects, PropertyEditor, Slate, SlateCore, UnrealEd

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintGraph/Private/JsonBlueprintGraphLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonBlueprintGraph, VeryVerbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonBlueprintGraph, VeryVerbose, All);`

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintGraph/Private/K2Node_GetJsonField.h` (Private)


#### class `UK2Node_GetJsonField`  
`class UK2Node_GetJsonField : public UK2Node_CallFunction`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- desc: A custom node that gets a JsonObject field.
- L17 _public prototype_ `UK2Node_GetJsonField();`
- L20 _public prototype_ `virtual void AllocateDefaultPins() override;` — //~ Begin UEdGraphNode Interface.
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual bool IsNodePure() const override;`
- L26 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L27 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _protected prototype_ `void NotifyInputChanged() const;`

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintGraph/Private/K2Node_SetJsonField.h` (Private)


#### class `UK2Node_SetJsonField`  
`class UK2Node_SetJsonField : public UK2Node_CallFunction`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- desc: A custom node that sets a JsonObject field.
- L17 _public prototype_ `UK2Node_SetJsonField();`
- L20 _public prototype_ `virtual void AllocateDefaultPins() override;` — //~ Begin UEdGraphNode Interface.
- L21 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public prototype_ `virtual bool IsNodePure() const override;`
- L26 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L27 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L31 _protected prototype_ `void NotifyInputChanged() const;`

### `Plugins/JsonBlueprintUtilities/Source/JsonBlueprintGraph/Private/K2Node_StructToJsonString.h` (Private)


#### class `UK2Node_StructToJsonString`  
`class UK2Node_StructToJsonString : public UK2Node_CallFunction`  
_L9-30_
- reflection: `UCLASS()`
- inherits: `UK2Node_CallFunction`
- L15 _public prototype_ `UK2Node_StructToJsonString();`
- L18 _public prototype_ `virtual void AllocateDefaultPins() override;` — //~ Begin UEdGraphNode Interface.
- L19 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual bool IsNodePure() const override;`
- L24 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L25 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L29 _protected prototype_ `void NotifyInputChanged() const;`
