# Plugins / MQTTCoreEditor

- module root: `Plugins/Protocols/MQTT/Source/MQTTCoreEditor`
- headers: 4; symbols: 7
- symbol kinds: class=2, delegate=2, prototype=3

### `Plugins/Protocols/MQTT/Source/MQTTCoreEditor/Private/MQTTCoreEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMQTTCoreEditor, VeryVerbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMQTTCoreEditor, VeryVerbose, All);`

### `Plugins/Protocols/MQTT/Source/MQTTCoreEditor/Private/MQTTCoreEditorModule.h` (Private)


#### class `FMQTTCoreEditorModule`  
`class FMQTTCoreEditorModule final : public IMQTTCoreEditorModuleInterface`  
_L8-14_
- inherits: `IMQTTCoreEditorModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Protocols/MQTT/Source/MQTTCoreEditor/Private/MQTTCoreEditorStats.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("MQTTCoreEditor"), STATGROUP_MQTTCoreEditor, STAT`

### `Plugins/Protocols/MQTT/Source/MQTTCoreEditor/Public/IMQTTCoreEditorModule.h` (Public)


#### class `IMQTTCoreEditorModuleInterface`  
`class IMQTTCoreEditorModuleInterface : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`
