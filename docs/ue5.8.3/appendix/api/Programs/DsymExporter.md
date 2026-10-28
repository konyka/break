# Programs / DsymExporter

- module root: `Source/Programs/Mac/DsymExporter`
- headers: 1; symbols: 1
- symbol kinds: prototype=1
- PrivateDependencyModuleNames: ApplicationCore, Core, Projects
- PrivateIncludePathModuleNames: Launch

### `Source/Programs/Mac/DsymExporter/Public/DsymExporterApp.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `int32 RunDsymExporter(int32 ArgC, TCHAR* Argv[]);` — Export symbol data from Apple's .dSYM format to something that can be parsed on non-Apple platforms
