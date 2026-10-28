# Programs / UnrealVersionSelector

- module root: `Source/Programs/UnrealVersionSelector`
- headers: 6; symbols: 26
- symbol kinds: macro=10, prototype=10, struct=3, typedef=3
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DesktopPlatform, Json, Projects, Slate, SlateCore, SlateFileDialogs, StandaloneRenderer, UnixCommonStartup
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealVersionSelector/Private/GenericPlatform/GenericPlatformInstallation.h` (Private)


#### struct `FGenericPlatformInstallation`  
`struct FGenericPlatformInstallation`  
_L7-20_
- L10 _public prototype_ `static bool NormalizeEngineRootDir(FString &RootDir);` — Validate and normalize an engine root directory name
- L13 _public prototype_ `static bool LaunchEditor(const FString& RootDirName, const FString &ExplicitFileName, const FString &Arguments);` — Launches the editor application
- L16 _public prototype_ `static bool SelectEngineInstallation(FString &Identifier);` — Select an engine installation
- L19 _public prototype_ `static void ErrorDialog(const FString &Message, const FString &LogText);` — Shows an error dialog with log output

### `Source/Programs/UnrealVersionSelector/Private/Linux/LinuxPlatformInstallation.h` (Private)


#### struct `FLinuxPlatformInstallation`  
`struct FLinuxPlatformInstallation : FGenericPlatformInstallation`  
_L8-18_
- inherits: `FGenericPlatformInstallation`
- L11 _public prototype_ `static bool LaunchEditor(const FString &RootDirName, const FString& ExplicitFileName, const FString &Arguments);` — Launches the editor application
- L14 _public prototype_ `static bool SelectEngineInstallation(FString &Identifier);` — Select an engine installation
- L17 _public prototype_ `static void ErrorDialog(const FString &Message, const FString &LogText);` — Shows an error dialog with log output

### `Source/Programs/UnrealVersionSelector/Private/PlatformInstallation.h` (Private)


#### Free symbols / members of external scopes

- L7 _typedef_ `typedef FWindowsPlatformInstallation FPlatformInstallation;`
- L10 _typedef_ `typedef FLinuxPlatformInstallation FPlatformInstallation;`
- L13 _typedef_ `typedef FGenericPlatformInstallation FPlatformInstallation;`

### `Source/Programs/UnrealVersionSelector/Private/UnrealVersionSelector.h` (Private)
_(no declarations extracted)_

### `Source/Programs/UnrealVersionSelector/Private/Windows/Resources/Resource.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define IDD_SELECTBUILD 201` — {{NO_DEPENDENCIES}} Microsoft Visual C++ generated include file. Used by Resource.rc
- L8 _macro_ `#define IDD_ERRORDIALOG 205`
- L9 _macro_ `#define IDC_BROWSE 2001`
- L10 _macro_ `#define IDC_BUILDLIST 2002`
- L11 _macro_ `#define IDC_ERRORLOGTEXT 2005`
- L12 _macro_ `#define IDC_ERRORMESSAGE 2006`
- L18 _macro_ `#define _APS_NEXT_RESOURCE_VALUE 206`
- L19 _macro_ `#define _APS_NEXT_COMMAND_VALUE 40001`
- L20 _macro_ `#define _APS_NEXT_CONTROL_VALUE 2007`
- L21 _macro_ `#define _APS_NEXT_SYMED_VALUE 201`

### `Source/Programs/UnrealVersionSelector/Private/Windows/WindowsPlatformInstallation.h` (Private)


#### struct `FWindowsPlatformInstallation`  
`struct FWindowsPlatformInstallation : FGenericPlatformInstallation`  
_L8-18_
- inherits: `FGenericPlatformInstallation`
- L11 _public prototype_ `static bool LaunchEditor(const FString &RootDirName, const FString& ExplicitFileName, const FString &Arguments);` — Launches the editor application
- L14 _public prototype_ `static bool SelectEngineInstallation(FString &Identifier);` — Select an engine installation
- L17 _public prototype_ `static void ErrorDialog(const FString &Message, const FString &LogText);` — Shows an error dialog with log output
