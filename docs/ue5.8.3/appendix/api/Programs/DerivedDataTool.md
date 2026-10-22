# Programs / DerivedDataTool

- module root: `Source/Programs/DerivedDataTool`
- headers: 1; symbols: 25
- symbol kinds: class=1, delegate=1, function=6, member=8, namespace=3, prototype=4, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, DerivedDataCache, DesktopPlatform, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/DerivedDataTool/Private/DerivedDataToolCommand.h` (Private)


#### class `UE::DerivedData::Tool::FCommand`  
`class FCommand final`  
_L13-72_
- L16 _public typedef_ `using FFunction = int32 (const TCHAR* Tokens, const TCHAR* Options);`
- L18 _public function_ `explicit FCommand(const TCHAR* InName) : Name(InName)`
- L23 _public function_ `constexpr FCommand&& SetUsage(const ANSICHAR* InUsage) &&`
- L29 _public function_ `constexpr FCommand&& SetDescription(const ANSICHAR* InDescription) &&`
- L35 _public function_ `FCommand&& AddSwitch(const ANSICHAR* InSwitch, const ANSICHAR* InDescription = nullptr) &&`
- L41 _public function_ `FCommand&& AddCommand(FCommand&& Command) &&`
- L47 _public function_ `constexpr FCommand&& OnExecute(FFunction* InFunction) &&`
- L53 _public prototype_ `int32 Execute(const TCHAR* Command) const;`
- L56 _private prototype_ `int32 Execute(const TCHAR* Tokens, const TCHAR* Options, TArray<const FCommand*>& Stack) const;`
- L58 _private prototype_ `int32 Help(TConstArrayView<const FCommand*> Stack) const;`
- L66 _private member_ `const TCHAR* Name = nullptr;`
- L67 _private member_ `const ANSICHAR* Usage = nullptr;`
- L68 _private member_ `const ANSICHAR* Description = nullptr;`
- L69 _private member_ `TArray<FSwitch> Switches;`
- L70 _private member_ `TArray<FCommand> Commands;`
- L71 _private member_ `FFunction* Function = nullptr;`

#### struct `UE::DerivedData::Tool::FCommand::FSwitch`  
`struct FSwitch`  
_L60-64_
- L62 _public member_ `const ANSICHAR* Name = nullptr;`
- L63 _public member_ `const ANSICHAR* Description = nullptr;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataTool, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDerivedDataTool, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DerivedData` (scope `UE`)
- L10 _namespace_ `namespace Tool` (scope `UE::DerivedData`)
