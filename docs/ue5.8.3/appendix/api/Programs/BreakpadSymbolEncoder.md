# Programs / BreakpadSymbolEncoder

- module root: `Source/Programs/BreakpadSymbolEncoder`
- headers: 1; symbols: 8
- symbol kinds: function=1, member=5, struct=2
- PublicIncludePathModuleNames: Launch

### `Source/Programs/BreakpadSymbolEncoder/Private/BreakpadSymbolEncoder.h` (Private)


#### struct `RecordsHeader`  
`struct RecordsHeader`  
_L18-22_
- L21 _public member_ `uint32_t RecordCount;` — The number of Records encoded in the output file

#### struct `Record`  
`struct Record`  
_L24-42_
- L27 _public member_ `uint64_t Address;` — The Address of the Symbol
- L30 _public member_ `uint32_t LineNumber;` — The Line number of the symbol in the File
- L33 _public member_ `uint32_t FileRelativeOffset;` — The Relative Offset in bytes from the start of the strings to the start of the File name in the output file
- L36 _public member_ `uint32_t SymbolRelativeOffset;` — The Relative Offset in bytes from the start of the strings to the start of the Symbol name in the output file

#### Free symbols / members of external scopes

- L38 _function_ `friend bool operator<(const Record& A, const Record& B)`
