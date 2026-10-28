# Runtime / BuildSettings

- module root: `Source/Runtime/BuildSettings`
- headers: 1; symbols: 24
- symbol kinds: namespace=1, prototype=23
- PrivateIncludePathModuleNames: Core

### `Source/Runtime/BuildSettings/Public/BuildSettings.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildSettings`
- L17 _prototype_ `bool IsLicenseeVersion();` (scope `BuildSettings`) — Determines if the changelist version numbers are from a licensee Perforce server. For the same major/minor/patch release of the engine, licensee changelists are always considered newer than Epic changelists for engine versions. This follows the assumption that content is developed by Epic leading up to a release, and which point we lock compatibility, and any subsequent licensee modifications to the engine will have a superset of its functionality even if the changelist numbers are lower. @return Whether the changelist version numbers are from a licensee Perforce server
- L24 _prototype_ `int GetEngineVersionMajor();` (scope `BuildSettings`) — The major engine version. @return The major part of the engine version
- L31 _prototype_ `int GetEngineVersionMinor();` (scope `BuildSettings`) — The minor engine version. @return The minor part of the engine version
- L38 _prototype_ `int GetEngineVersionHotfix();` (scope `BuildSettings`) — The hotfix engine version. @return The hotfix patch part of the engine version
- L45 _prototype_ `const TCHAR* GetEngineVersionString();` (scope `BuildSettings`) — The engine version. @return The engine version as a string in the format MAJOR.MINOR.HOTFIX-BUILD_VERSION
- L55 _prototype_ `int GetCurrentChangelist();` (scope `BuildSettings`) — The Perforce changelist being compiled. Use this value advisedly; it does not take into account out-of-order commits to engine release branches over development branches, licensee versions, or whether the engine version has been locked to maintain compatibility with a previous engine release. Prefer BUILD_VERSION where a unique, product-specific identifier is required, or FEngineVersion::CompatibleWith() where relational comparisons between two versions is required. @return The changelist number being compiled
- L64 _prototype_ `int GetCompatibleChangelist();` (scope `BuildSettings`) — The compatible changelist version of the engine. This number identifies a particular API revision, and is used to determine module and package backwards compatibility. Hotfixes should retain the compatible version of the original release. This define is parsed by the build tools, and should be a number or BUILT_FROM_CHANGELIST, defined in this particular order for each alternative. @return The changelist number that this engine version is compatible with
- L71 _prototype_ `const TCHAR* GetBranchName();` (scope `BuildSettings`) — The branch that this program is being built from. @return Name of the current branch, with slashes escaped as '+' characters.
- L78 _prototype_ `const TCHAR* GetBuildDate();` (scope `BuildSettings`) — The date timestamp of this build. Derived from the compiler's __DATE__ macro, so only updated when the BuildSettings module is rebuilt (ie. whenever CL changes, etc...) @return String representing the build timestamp
- L85 _prototype_ `const TCHAR* GetBuildTime();` (scope `BuildSettings`) — The time timestamp of this build. Derived from the compiler's __TIME__ macro, so only updated when the BuildSettings module is rebuilt (ie. whenever CL changes, etc...) @return String representing the build timestamp
- L92 _prototype_ `const TCHAR* GetBuildVersion();` (scope `BuildSettings`) — Retrieves the user-defined build version for this application. @return The current build version
- L99 _prototype_ `bool IsPromotedBuild();` (scope `BuildSettings`) — Identifies whether this build is a promoted build; a formal build of the engine from a clean source sync. @return True if this is a promoted build of the engine.
- L104 _prototype_ `bool IsWithDebugInfo();` (scope `BuildSettings`) — Identifies whether this build was compiled with or without debug info. (e.g. pdb files on Microsoft platforms)
- L109 _prototype_ `const TCHAR* GetBuildURL();` (scope `BuildSettings`) — Returns a URL where the job which created these binaries on an automation system (e.g. Horde) can be found, or an empty string.
- L114 _prototype_ `const TCHAR* GetBuildUser();` (scope `BuildSettings`) — Returns the name of the user which created these binaries
- L119 _prototype_ `const TCHAR* GetBuildUserDomain();` (scope `BuildSettings`) — Returns the domain name of the user which created these binaries
- L124 _prototype_ `const TCHAR* GetBuildMachine();` (scope `BuildSettings`) — Returns the name of the machine which created these binaries
- L129 _prototype_ `const TCHAR* GetLiveCodingEngineDir();` (scope `BuildSettings`) — Returns the live coding engine dir. Only set in monolithic builds (live coding engine dir is calculated differently in modular builds)
- L134 _prototype_ `const TCHAR* GetLiveCodingProject();` (scope `BuildSettings`) — Returns the live coding project. Only set in monolithic builds
- L139 _prototype_ `uint64 GetPersistentAllocatorReserveSize();` (scope `BuildSettings`) — Persistent linear allocator reserve size. Stored here to prevent rebuilds of Core when switching between projects
- L144 _prototype_ `const char* GetVfsPaths();` (scope `BuildSettings`) — Semicolon separated string containing virtual;local;virtual;local; paths. Ends with semicolon
- L149 _prototype_ `const TCHAR* GetVfsPathsWide();` (scope `BuildSettings`) — Semicolon separated string containing virtual;local;virtual;local; paths. Ends with semicolon
- L154 _prototype_ `bool GetVariable(const TCHAR* InName, TCHAR* OutValue, int OutValueCapacity);` (scope `BuildSettings`) — Returns true if variable exists. Writes value into OutValue if not null
