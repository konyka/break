# Plugins / SwitchboardCommon

- module root: `Plugins/VirtualProduction/Switchboard/Source/SwitchboardCommon`
- headers: 1; symbols: 9
- symbol kinds: macro=2, namespace=3, prototype=4
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/Switchboard/Source/SwitchboardCommon/Public/SwitchboardListenerAutolaunch.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `# define SWITCHBOARD_LISTENER_AUTOLAUNCH 1`
- L11 _macro_ `# define SWITCHBOARD_LISTENER_AUTOLAUNCH 0`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SwitchboardListener` (scope `UE`)
- L18 _namespace_ `namespace Autolaunch` (scope `UE::SwitchboardListener`)
- L21 _prototype_ `FString GetInvocation(FLogCategoryBase& InLogCategory);` (scope `UE::SwitchboardListener::Autolaunch`)
- L22 _prototype_ `FString GetInvocationExecutable(FLogCategoryBase& InLogCategory);` (scope `UE::SwitchboardListener::Autolaunch`)
- L23 _prototype_ `bool SetInvocation(const FString& InNewInvocation, FLogCategoryBase& InLogCategory);` (scope `UE::SwitchboardListener::Autolaunch`)
- L24 _prototype_ `bool RemoveInvocation(FLogCategoryBase& InLogCategory);` (scope `UE::SwitchboardListener::Autolaunch`)
