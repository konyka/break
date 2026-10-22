# Developer / ScriptDisassembler

- module root: `Source/Developer/ScriptDisassembler`
- headers: 1; symbols: 29
- symbol kinds: class=1, function=4, member=3, prototype=21
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/ScriptDisassembler/Public/ScriptDisassembler.h` (Public)


#### class `FKismetBytecodeDisassembler`  
`class FKismetBytecodeDisassembler`  
_L25-99_
- desc: Kismet bytecode disassembler; Can be used to create a human readable version of Kismet bytecode for a specified structure or class.
- L28 _private member_ `TArray<uint8> Script;`
- L29 _private member_ `FString Indents;`
- L30 _private member_ `FOutputDevice& Ar;`
- L37 _public prototype_ `FKismetBytecodeDisassembler(FOutputDevice& InAr);` — Construct a disassembler that will output to the specified archive. @param	InAr	The archive to emit disassembled bytecode to.
- L44 _public prototype_ `void DisassembleStructure(UFunction* Source);` — Disassemble all of the script code in a single structure. @param [in,out]	Source	The structure to disassemble.
- L52 _public prototype_ `static void DisassembleAllFunctionsInClasses(FOutputDevice& Ar, const FString& ClassnameSubstring);` — Disassemble all functions in any classes that have matching names. @param	InAr	The archive to emit disassembled bytecode to. @param	ClassnameSubstring	A class must contain this substring to be disassembled.
- L56 _private prototype_ `int32 ReadINT(int32& ScriptIndex);` — Reading functions
- L57 _private prototype_ `uint64 ReadQWORD(int32& ScriptIndex);`
- L58 _private prototype_ `uint8 ReadBYTE(int32& ScriptIndex);`
- L59 _private prototype_ `FString ReadName(int32& ScriptIndex);`
- L60 _private prototype_ `uint16 ReadWORD(int32& ScriptIndex);`
- L61 _private prototype_ `float ReadFLOAT(int32& ScriptIndex);`
- L62 _private prototype_ `double ReadDOUBLE(int32& ScriptIndex);`
- L63 _private prototype_ `FVector ReadFVECTOR(int32& ScriptIndex);`
- L64 _private prototype_ `FRotator ReadFROTATOR(int32& ScriptIndex);`
- L65 _private prototype_ `FQuat ReadFQUAT(int32& ScriptIndex);`
- L66 _private prototype_ `FTransform ReadFTRANSFORM(int32& ScriptIndex);`
- L67 _private prototype_ `CodeSkipSizeType ReadSkipCount(int32& ScriptIndex);`
- L68 _private prototype_ `FString ReadString(int32& ScriptIndex);`
- L69 _private prototype_ `FString ReadString8(int32& ScriptIndex);`
- L70 _private prototype_ `FString ReadString16(int32& ScriptIndex);`
- L72 _private prototype_ `EExprToken SerializeExpr(int32& ScriptIndex);`
- L73 _private prototype_ `void ProcessCommon(int32& ScriptIndex, EExprToken Opcode);`
- L75 _private prototype_ `void InitTables();`
- L78 _private function_ `template<typename T> void Skip(int32& ScriptIndex)`
- L83 _private function_ `void AddIndent()`
- L88 _private function_ `void DropIndent()`
- L95 _private function_ `template <typename T> T* ReadPointer(int32& ScriptIndex)`
