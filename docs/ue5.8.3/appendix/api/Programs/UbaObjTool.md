# Programs / UbaObjTool

- module root: `Source/Programs/UnrealBuildAccelerator/ObjTool`
- headers: 2; symbols: 10
- symbol kinds: class=2, namespace=2, prototype=4, variable=2
- PrivateDependencyModuleNames: UbaCommon

### `Source/Programs/UnrealBuildAccelerator/ObjTool/Private/UbaImportLibWriter.h` (Private)


#### class `uba::ImportLibWriter`  
`class ImportLibWriter`  
_L13-18_
- L16 _public prototype_ `bool Write(Logger& logger, const Vector<ObjectFile*>& objFiles, const char* libName, const tchar* libFile);`
- L17 _public prototype_ `bool Write(Logger& logger, const UnorderedExports& exports, const char* libName, const tchar* libFile);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/ObjTool/Private/UbaImportStubWriterElf.h` (Private)


#### class `uba::ImportStubWriterElf`  
`class ImportStubWriterElf`  
_L15-21_
- desc: Writes a Linux "import library": a stub ET_DYN .so carrying only a dynamic symbol table (the defined exports) plus DT_SONAME = the real library's name. Linking a dependent against this stub resolves the exports single-pass and emits a DT_NEEDED for soName, exactly like a Windows COFF import lib. No code/relocations are emitted. Cross-platform (host win/linux/mac).
- L19 _public prototype_ `static bool Write(Logger& logger, MemoryBlock& out, const UnorderedExports& exports, const char* soName, u16 machine);` — machine: EM_X86_64 (62) or EM_AARCH64 (183). exports: name + isData + size per symbol.
- L20 _public prototype_ `static bool Write(Logger& logger, const UnorderedExports& exports, const char* soName, u16 machine, const tchar* outFile);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L23 _variable_ `static constexpr u16 ElfMachine_X86_64 = 62;` (scope `uba`)
- L24 _variable_ `static constexpr u16 ElfMachine_Aarch64 = 183;` (scope `uba`)
