# CSharp / IncludeTool

- project root: `Source/Programs/IncludeTool/IncludeTool`
- files: 36; symbols: 1002
- symbol kinds: class=70, const=12, ctor=54, enum=18, enumerator=106, field=291, indexer=5, method=388, operator=4, property=48, struct=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/IncludeTool/IncludeTool/BuildTarget.cs` (IncludeTool)


#### enum `IncludeTool.BuildBinaryType`  
`enum BuildBinaryType`  
_internal*; L17-22_
- desc: Type of binary file
- L19 _public* enumerator_ `Executable`
- L20 _public* enumerator_ `StaticLibrary`
- L21 _public* enumerator_ `DynamicLinkLibrary`

#### class `IncludeTool.BuildBinary`  
`class BuildBinary`  
_internal*; L27-37_
- desc: Wrapper class for an target binary exported by UBT
- L29 _public field_ `public FileReference File`
- L30 _public field_ `public BuildBinaryType Type`
- L31 _public field_ `public HashSet<BuildModule> Modules`
- L33-36 _public method_ `public override string ToString()`

#### enum `IncludeTool.BuildModulePCHUsage`  
`enum BuildModulePCHUsage`  
_internal*; L42-49_
- desc: Type of PCH
- L44 _public* enumerator_ `Default`
- L45 _public* enumerator_ `NoPCHs`
- L46 _public* enumerator_ `NoSharedPCHs`
- L47 _public* enumerator_ `UseSharedPCHs`
- L48 _public* enumerator_ `UseExplicitOrSharedPCHs`

#### class `IncludeTool.BuildModule`  
`class BuildModule`  
_internal*; L54-81_
- desc: Wrapper class for a target module exported by UBT
- L56 _public field_ `public string Name`
- L57 _public field_ `public BuildModulePCHUsage PCHUsage`
- L58 _public field_ `public FileReference PrivatePCH`
- L59 _public field_ `public FileReference SharedPCH`
- L60 _public field_ `public DirectoryReference Directory`
- L61 _public field_ `public HashSet<BuildModule> PublicDependencyModules`
- L62 _public field_ `public HashSet<BuildModule> PublicIncludePathModules`
- L63 _public field_ `public HashSet<BuildModule> PrivateDependencyModules`
- L64 _public field_ `public HashSet<BuildModule> PrivateIncludePathModules`
- L65 _public field_ `public HashSet<BuildModule> CircularlyReferencedModules`
- L67-70 _public property_ `public IEnumerable<BuildModule> Dependencies { get; }`
- L72-75 _public property_ `public IEnumerable<BuildModule> NonCircularDependencies { get; }`
- L77-80 _public method_ `public override string ToString()`

#### class `IncludeTool.BuildTarget`  
`class BuildTarget`  
_internal*; L86-157_
- desc: Wrapper class for an build target exported by UBT
- L88 _public field_ `public string Name`
- L89 _public field_ `public string Configuration`
- L90 _public field_ `public string Platform`
- L91 _public field_ `public FileReference ProjectFile`
- L92 _public field_ `public List<BuildBinary> Binaries = new List<BuildBinary>()`
- L93 _public field_ `public List<BuildModule> Modules = new List<BuildModule>()`
- L94 _public field_ `public Dictionary<string, BuildModule> NameToModule = ...`
- L94 _public field_ `public Dictionary< NameToModule = new Dictionary<string, BuildModule>()`
- L96-151 _public method_ `public static BuildTarget Read(FileReference File)`
- L153-156 _public method_ `public override string ToString()`

### `Source/Programs/IncludeTool/IncludeTool/CompileEnvironment.cs` (IncludeTool)


#### enum `IncludeTool.CompilerType`  
`public enum CompilerType`  
_public; L18-23_
- desc: The type of the compiler
- L20 _public* enumerator_ `Unknown`
- L21 _public* enumerator_ `Clang`
- L22 _public* enumerator_ `VisualC`

#### class `IncludeTool.CompileOption`  
`public class CompileOption`  
_public; L29-71_
- attrs: `[Serializable]`
- desc: Encapsulates a compiler option
- L34 _public field_ `public readonly string Name` — The option name
- L39 _public field_ `public readonly string Value` — The option value. May be null.
- L46-50 _public ctor_ `public CompileOption(string InName, string InValue)` — Constructor
- L56-70 _public method_ `public override string ToString()` — Formats the option as it would appear on the command line.

#### class `IncludeTool.CompileEnvironment`  
`class CompileEnvironment`  
_internal*; L77-492_
- attrs: `[Serializable]`
- desc: Environment used to compile a file
- L82 _public field_ `public FileReference Compiler` — Path to the compiler executable
- L87 _public field_ `public CompilerType CompilerType` — The type of compiler
- L92 _public field_ `public List<CompileOption> Options = new List<CompileOption>()` — All the options, with the exception of definitions and include paths
- L97 _public field_ `public List<string> Definitions = new List<string>()` — List of macro definitions
- L102 _public field_ `public List<DirectoryReference> IncludePaths = new List<DirectoryReference>()` — List of include paths
- L107 _public field_ `public List<FileReference> ForceIncludeFiles = new List<FileReference>()` — List of force-included headers
- L112-116 _public ctor_ `public CompileEnvironment(FileReference InCompiler, CompilerType InCompilerType)` — Default constructor
- L122-130 _public ctor_ `public CompileEnvironment(CompileEnvironment Other)` — Clone another compile environment
- L136-153 _public method_ `public string GetCommandLine()` — Gets the full command line to compile with, with the exception of any source files
- L160-169 _public method_ `public IEnumerable<string> GetOptionValues(string InName)` — Enumerates all the options with the given name
- L176-237 _public method_ `public void WriteResponseFile(FileReference ResponseFile, FileReference SourceFile)` — Writes a response file which will compile the given source file
- L244-403 _public method_ `public static void ReadTaskList(FileReference TaskListFile, DirectoryReference BaseDir, out Dictionary<FileReference, CompileEnvironment> FileToEnvironment)` — Reads an exported XGE task list
- L411-429 _private* method_ `static bool GetCompilerType(FileReference Compiler, out CompilerType CompilerType)` — Determine the compiler type
- L437-482 _private* method_ `static void ParseArgumentTokens(CompilerType CompilerType, string Text, List<string> Tokens, DirectoryReference BaseDir)` — Parse a parameter list into a series of tokens, reading response files as appropriate
- L488-491 _public method_ `public override string ToString()` — Returns the full command line for this compile environment

### `Source/Programs/IncludeTool/IncludeTool/IncludeCycle.cs` (IncludeTool)


#### class `IncludeTool.IncludeCycle`  
`class IncludeCycle`  
_internal*; L16-138_
- desc: Stores information about a circular include path. All headers processed by the tool should form a direct hierarchy, whereby one header always includes another. If two headers include each other, we can't reason about what the IWYU derivation for each should be in case they're each included by different files.
- L21 _public field_ `public SourceFile[] Files` — Array of files in this cycle
- L26 _public field_ `public List<KeyValuePair<SourceFile, int>> StartingPoints` — List of observed starting points for this cycle, along with a counter for its number of appearances.
- L26 _public field_ `public List<KeyValuePair< StartingPoints` — List of observed starting points for this cycle, along with a counter for its number of appearances.
- L32-37 _public ctor_ `public IncludeCycle(IEnumerable<SourceFile> InFiles)` — Constructor.
- L43-83 _public method_ `public void AddStartingPoint(SourceFile File)` — Adds a new starting point for this cycle. If the starting point already exists, increases the counter for number of times it's been seen.
- L90-112 _public method_ `public bool Matches(IncludeCycle Other)` — Checks whether an include cycle matches another include cycle, ignoring the start location.
- L118-128 _public method_ `public override int GetHashCode()` — Returns a hash code for the current cycle, independent of the cycle's starting point.
- L134-137 _public method_ `public override string ToString()` — Creates a human-readable representation of the cycle

#### class `IncludeTool.IncludeCycles`  
`static class IncludeCycles`  
_internal*; L143-209_
- desc: Functions to find include cycles
- L150-158 _public method_ `public static List<IncludeCycle> FindAll(IEnumerable<SourceFile> Files)` — Finds all include cycles from the given set of source files
- L167-208 _private* method_ `static void FindCyclesRecursive(SourceFile File, List<SourceFile> Includes, HashSet<SourceFile> VisitedFiles, List<IncludeCycle> Cycles)` — Recurses through the given file and all of its includes, attempting to identify cycles.

### `Source/Programs/IncludeTool/IncludeTool/ManagedProcess.cs` (IncludeTool)


#### enum `IncludeTool.ManagedProcessPriority`  
`enum ManagedProcessPriority`  
_internal*; L18-23_
- desc: Possible priority values for new processes.
- L20 _public* enumerator_ `BelowNormal`
- L21 _public* enumerator_ `Normal`
- L22 _public* enumerator_ `AboveNormal`

#### class `IncludeTool.ManagedProcess`  
`class ManagedProcess : IDisposable`  
_internal*; L30-529_
- inherits: `IDisposable`
- desc: Encapsulates a managed child process, from which we can read the console output. Uses job objects to ensure that the process will be terminated automatically by the O/S if the current process is terminated, and polls pipe reads to avoid blocking on unmanaged code if the calling thread is terminated. Currently only implemented for Windows; makes heavy use of P/Invoke.
- L72 _private* const_ `const UInt32 JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE = 0x00002000`
- L73 _private* const_ `const UInt32 JOB_OBJECT_LIMIT_PROCESS_MEMORY = 0x00000100`
- L112 _private* method_ `static extern SafeFileHandle CreateJobObject(IntPtr SecurityAttributes, IntPtr Name)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L114 _private* const_ `const int JobObjectExtendedLimitInformation = 9`
- L117 _private* method_ `static extern int SetInformationJobObject(SafeFileHandle hJob, int JobObjectInfoClass, IntPtr lpJobObjectInfo, int cbJobObjectInfoLength)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L120 _private* method_ `static extern int AssignProcessToJobObject(SafeFileHandle hJob, IntPtr hProcess)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L123 _private* method_ `static extern int CloseHandle(IntPtr hObject)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L126 _private* method_ `static extern int CreatePipe(out SafeFileHandle hReadPipe, out SafeFileHandle hWritePipe, SECURITY_ATTRIBUTES lpPipeAttributes, uint nSize)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L129 _private* method_ `static extern int SetHandleInformation(SafeFileHandle hObject, int dwMask, int dwFlags)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L131 _private* const_ `const int HANDLE_FLAG_INHERIT = 1`
- L133 _private* const_ `const int STARTF_USESTDHANDLES = 0x00000100`
- L147 _private* method_ `static extern int CreateProcess( string lpApplicationName, StringBuilder lpCommandLine, IntPtr lpProcessAttributes, IntPtr lpThreadAttributes, bool bInheritHandles, ProcessCreationFlags dwCreationFlags, IntPtr lpEnvironment, string lpCurrentDirectory, STARTUPINFO lpStartupInfo, PROCESS_INFORMATION lpProcessInformation)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L150 _private* method_ `static extern int ResumeThread(IntPtr hThread)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L153 _private* method_ `static extern IntPtr GetCurrentProcess()` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L156 _private* method_ `static extern int TerminateProcess(SafeFileHandle hProcess, uint uExitCode)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L159 _private* method_ `static extern uint WaitForSingleObject(SafeFileHandle hHandle, uint dwMilliseconds)` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L161 _private* const_ `const uint INFINITE = 0xFFFFFFFF`
- L163 _private* const_ `const int DUPLICATE_SAME_ACCESS = 2`
- L166 _private* method_ `static extern int DuplicateHandle( IntPtr hSourceProcessHandle, SafeHandle hSourceHandle, IntPtr hTargetProcess, out SafeWaitHandle targetHandle, int dwDesiredAccess, bool bInheritHandle, int dwOptions )` — attrs: `[DllImport("kernel32.dll", SetLastError=true)]`
- L177 _private* method_ `static extern int GetExitCodeProcess(SafeFileHandle hProcess, out int lpExitCode)` — attrs: `[DllImport("kernel32.dll", SetLastError = true)]`
- L182 _private* field_ `SafeFileHandle ProcessHandle` — Handle for the child process.
- L187 _private* field_ `SafeFileHandle StdInWrite` — The write end of the child process' stdin pipe.
- L192 _private* field_ `SafeFileHandle StdOutRead` — The read end of the child process' stdout pipe.
- L197 _private* field_ `FileStream InnerStream` — Output stream for the child process.
- L202 _private* field_ `StreamReader ReadStream` — Reader for the process' output stream.
- L208 _private* field_ `SafeFileHandle JobHandle` — Handle to the native job object that this process is added to. This handle is closed by the Dispose() method (and will automatically be closed by the OS on process exit), resulting in the child process being killed.
- L218-380 _public ctor_ `public ManagedProcess(string FileName, string CommandLine, string WorkingDirectory, IReadOnlyDictionary<string, string> Environment, string Input, ManagedProcessPriority Priority, ulong MemoryLimit)` — Spawns a new managed process.
- L385-407 _public method_ `public void Dispose()` — Free the managed resources for this process
- L413-460 _public method_ `public bool TryReadAllLines(TimeSpan TimeLimit, List<string> OutputLines)` — Read all the output from the process. Does not return until the process terminates.
- L467-479 _public method_ `public bool TryReadLine(out string Line)` — Block until the process outputs a line of text, or terminates.
- L485-489 _public method_ `public void Terminate(uint ExitCode)` — Terminate the process and waits for it to exit
- L494-505 _public property_ `public int ExitCode { get; }` — The exit code of the process. Throws an exception if the process has not terminated.
- L512-528 _private method_ `private static int GetNativePriorityClassFlag(ManagedProcessPriority Priority)` — Gets the native flag for the given priority class, as passed

#### class `IncludeTool.ManagedProcess.SECURITY_ATTRIBUTES`  
`class SECURITY_ATTRIBUTES`  
_private*; L33-38_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L35 _public field_ `public int nLength`
- L36 _public field_ `public IntPtr lpSecurityDescriptor`
- L37 _public field_ `public int bInheritHandle`

#### class `IncludeTool.ManagedProcess.PROCESS_INFORMATION`  
`class PROCESS_INFORMATION`  
_private*; L41-47_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L43 _public field_ `public IntPtr hProcess`
- L44 _public field_ `public IntPtr hThread`
- L45 _public field_ `public uint dwProcessId`
- L46 _public field_ `public uint dwThreadId`

#### class `IncludeTool.ManagedProcess.STARTUPINFO`  
`class STARTUPINFO`  
_private*; L50-70_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L52 _public field_ `public int cb`
- L53 _public field_ `public string lpReserved`
- L54 _public field_ `public string lpDesktop`
- L55 _public field_ `public string lpTitle`
- L56 _public field_ `public uint dwX`
- L57 _public field_ `public uint dwY`
- L58 _public field_ `public uint dwXSize`
- L59 _public field_ `public uint dwYSize`
- L60 _public field_ `public uint dwXCountChars`
- L61 _public field_ `public uint dwYCountChars`
- L62 _public field_ `public uint dwFillAttribute`
- L63 _public field_ `public uint dwFlags`
- L64 _public field_ `public short wShowWindow`
- L65 _public field_ `public short cbReserved2`
- L66 _public field_ `public IntPtr lpReserved2`
- L67 _public field_ `public SafeHandle hStdInput`
- L68 _public field_ `public SafeHandle hStdOutput`
- L69 _public field_ `public SafeHandle hStdError`

#### struct `IncludeTool.ManagedProcess.JOBOBJECT_BASIC_LIMIT_INFORMATION`  
`struct JOBOBJECT_BASIC_LIMIT_INFORMATION`  
_private*; L76-87_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L78 _public field_ `public Int64 PerProcessUserTimeLimit`
- L79 _public field_ `public Int64 PerJobUserTimeLimit`
- L80 _public field_ `public UInt32 LimitFlags`
- L81 _public field_ `public UIntPtr MinimumWorkingSetSize`
- L82 _public field_ `public UIntPtr MaximumWorkingSetSize`
- L83 _public field_ `public UInt32 ActiveProcessLimit`
- L84 _public field_ `public Int64 Affinity`
- L85 _public field_ `public UInt32 PriorityClass`
- L86 _public field_ `public UInt32 SchedulingClass`

#### struct `IncludeTool.ManagedProcess.IO_COUNTERS`  
`struct IO_COUNTERS`  
_private*; L90-98_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L92 _public field_ `public UInt64 ReadOperationCount`
- L93 _public field_ `public UInt64 WriteOperationCount`
- L94 _public field_ `public UInt64 OtherOperationCount`
- L95 _public field_ `public UInt64 ReadTransferCount`
- L96 _public field_ `public UInt64 WriteTransferCount`
- L97 _public field_ `public UInt64 OtherTransferCount`

#### struct `IncludeTool.ManagedProcess.JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
`struct JOBOBJECT_EXTENDED_LIMIT_INFORMATION`  
_private*; L101-109_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L103 _public field_ `public JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation`
- L104 _public field_ `public IO_COUNTERS IoInfo`
- L105 _public field_ `public UIntPtr ProcessMemoryLimit`
- L106 _public field_ `public UIntPtr JobMemoryLimit`
- L107 _public field_ `public UIntPtr PeakProcessMemoryUsed`
- L108 _public field_ `public UIntPtr PeakJobMemoryUsed`

#### enum `IncludeTool.ManagedProcess.ProcessCreationFlags`  
`enum ProcessCreationFlags : int`  
_private*; L136-144_
- attrs: `[Flags]`
- inherits: `int`
- L138 _public* enumerator_ `CREATE_NO_WINDOW = 0x08000000`
- L139 _public* enumerator_ `CREATE_SUSPENDED = 0x00000004`
- L140 _public* enumerator_ `CREATE_BREAKAWAY_FROM_JOB = 0x01000000`
- L141 _public* enumerator_ `BELOW_NORMAL_PRIORITY_CLASS = 0x00004000`
- L142 _public* enumerator_ `NORMAL_PRIORITY_CLASS = 0x00000020`
- L143 _public* enumerator_ `ABOVE_NORMAL_PRIORITY_CLASS = 0x00008000`

### `Source/Programs/IncludeTool/IncludeTool/OutputFile.cs` (IncludeTool)


#### class `IncludeTool.OutputFileReference`  
`class OutputFileReference`  
_internal*; L17-48_
- desc: Reference to an output file, in the context of an include stack
- L22 _public field_ `public readonly OutputFile File` — The file to include
- L27 _public field_ `public readonly SourceFragment[] UniqueFragments` — Fragments which it uniquely provides, which have not been included by a previous file.
- L34-38 _public ctor_ `public OutputFileReference(OutputFile File, IEnumerable<SourceFragment> UniqueFragments)` — Constructor
- L44-47 _public method_ `public override string ToString()` — Convert to a string for the debugger

#### class `IncludeTool.OutputFileInclude`  
`class OutputFileInclude`  
_internal*; L53-95_
- desc: An include directive from an output file
- L58 _public field_ `public readonly int MarkupIdx` — The markup index in the source file
- L63 _public field_ `public readonly OutputFile TargetFile` — The file being included
- L68 _public field_ `public List<OutputFileReference> ExpandedReferences` — The expanded list of unique output files matching the equivalent input file, which have not already been included by the file containing this #include directive
- L73 _public field_ `public List<OutputFile> FinalFiles = new List<OutputFile>()` — The expanded list of output files matching the equivalent input file
- L81-85 _public ctor_ `public OutputFileInclude(int MarkupIdx, OutputFile TargetFile)` — Constructor
- L91-94 _public method_ `public override string ToString()` — Converts this object to a string for the debugger

#### class `IncludeTool.OutputFile`  
`class OutputFile`  
_internal*; L100-171_
- desc: Represents an optimized output file
- L105 _public field_ `public readonly SourceFile InputFile` — The SourceFile that corresponds to this output file
- L110 _public field_ `public readonly List<OutputFileInclude> Includes` — The other output files included from this file
- L115 _public field_ `public HashSet<SourceFragment> Dependencies` — Fragments which this output file has dependencies on
- L120 _public field_ `public List<Symbol> ForwardDeclarations` — Symbols which need explicit forward declarations
- L125 _public field_ `public HashSet<SourceFragment> IncludedFragments` — Fragments which are included through this file
- L130 _public field_ `public HashList<OutputFile> IncludedFiles` — All the files which are included by this file
- L135 _public field_ `public HashList<OutputFile> OriginalIncludedFiles` — All the files which were originally included by this file
- L140-161 _public ctor_ `public OutputFile(SourceFile InputFile, List<OutputFileInclude> Includes, HashSet<SourceFragment> Dependencies, List<Symbol> ForwardDeclarations)` — Constructor
- L167-170 _public method_ `public override string ToString()` — Convert the object to a string for debugging purposes

#### class `IncludeTool.OutputFileBuilder`  
`static class OutputFileBuilder`  
_internal*; L176-696_
- desc: Class to construct output files from optimized input files
- L184-233 _public method_ `public static void PrepareFilesForOutput(IEnumerable<SourceFile> CppFiles, Dictionary<SourceFile, SourceFile> CppFileToHeaderFile, Dictionary<Symbol, SourceFile> FwdSymbolToInputHeader, bool bMakeStandalone, bool bUseOriginalIncludes, LineBasedTextWriter Log)` — Create optimized output files from the given input files
- L243-324 _private* method_ `static OutputFile FindOrCreateOutputFile(List<SourceFile> InputFileStack, Dictionary<SourceFile, SourceFile> CppFileToHeaderFile, HashList<OutputFile> PreviousFiles, Dictionary<SourceFile, OutputFile> OutputFileLookup, Dictionary<Symbol, OutputFile> FwdSymbolToHeader, bool bMakeStandalone, bool bUseOriginalIncludes, LineBasedTextWriter Log)` — Find or create an output file for a corresponding input file
- L337-585 _public method_ `public static OutputFile CreateOptimizedOutputFile(SourceFile InputFile, OutputFile HeaderFile, List<OutputFile> PreviousFiles, List<OutputFileInclude> Includes, List<SourceFile> InputFileStack, Dictionary<Symbol, OutputFile> FwdSymbolToHeader, bool bMakeStandalone, LineBasedTextWriter Log)` — Creates an optimized output file
- L593-624 _public method_ `public static OutputFile CreatePassthroughOutputFile(SourceFile InputFile, List<OutputFileInclude> Includes, LineBasedTextWriter Log)` — Creates an output file which represents the same includes as the inpu tfile
- L633-671 _private* method_ `static void AddForwardDeclarations(SourceFile InputFile, List<Symbol> ForwardDeclarations, HashSet<SourceFragment> Dependencies, Dictionary<Symbol, OutputFile> FwdSymbolToHeader)` — Create forward declarations for the given file
- L680-695 _private* method_ `static void FindExpandedReferences(OutputFile TargetFile, List<OutputFileReference> ExpandedReferences, HashSet<OutputFile> VisitedFiles, HashSet<SourceFragment> VisitedFragments, bool bIsFirstInclude)` — Build a list of included files which can be expanded out, ignoring those which have already been included

### `Source/Programs/IncludeTool/IncludeTool/Preprocessor.cs` (IncludeTool)


#### class `IncludeTool.PreprocessorException`  
`class PreprocessorException : Exception`  
_internal*; L21-32_
- inherits: `Exception`
- desc: Exception class for the preprocessor, which contains the file and position of the code causing an error
- L28-31 _public ctor_ `public PreprocessorException(string Format, params object[] Args) : base(String.Format(Format, Args))` — Constructor

#### class `IncludeTool.PreprocessorMacro`  
`class PreprocessorMacro`  
_internal*; L37-143_
- desc: Stores information about a defined preprocessor macro
- L42 _public field_ `public string Name` — Name of the macro
- L47 _public field_ `public List<string> Parameters` — Parameter names for the macro. The '...' placeholder is represented by the VariadicParameter string.
- L52 _public field_ `public List<Token> Tokens` — Raw list of tokens for this macro
- L57 _public const_ `public const string VariadicParameter = "__VA_ARGS__"` — The parameter name used for the variadic parameter. This appears in place of '...' in the parameters list.
- L65-70 _public ctor_ `public PreprocessorMacro(string InName, List<string> InParameters, List<Token> InTokens)` — Construct a preprocessor macro
- L77-87 _public method_ `public int FindParameterIndex(string Parameter)` — Finds the index of a parameter in the parameter list
- L92-95 _public property_ `public bool IsObjectMacro { get; }` — True if the macro is an object macro
- L100-103 _public property_ `public bool IsFunctionMacro { get; }` — True if the macro is a function macro
- L108-111 _public property_ `public int MinRequiredParameters { get; }` — The number of required parameters. For variadic macros, the last parameter is optional.
- L116-119 _public property_ `public bool HasVariableArgumentList { get; }` — True if the macro has a variable argument list
- L125-142 _public method_ `public override string ToString()` — Converts this macro to a string for debugging

#### class `IncludeTool.PreprocessorFile`  
`class PreprocessorFile`  
_internal*; L148-184_
- desc: Record for a file context within the preprocessor stack
- L153 _public field_ `public string FileName` — Filename as specified when included
- L158 _public field_ `public FileReference Location` — Reference to the current file
- L163 _public field_ `public WorkspaceFile WorkspaceFile` — The workspace file
- L169-174 _public ctor_ `public PreprocessorFile(string FileName, WorkspaceFile WorkspaceFile)` — Construct a new preprocessor file from the given name
- L180-183 _public method_ `public override string ToString()` — Returns the name of this file for visualization in the debugger

#### class `IncludeTool.Preprocessor`  
`class Preprocessor`  
_internal*; L189-1778_
- desc: Implementation of a C++ preprocessor. Should be complete and accurate.
- L258 _private* field_ `Stack<BranchState> Branches = new Stack<BranchState>()` — Stack of conditional branch states
- L263 _private* field_ `Dictionary<string, PreprocessorMacro> NameToMacro = ...` — Mapping of name to macro definition
- L263 _private* field_ `Dictionary< NameToMacro = new Dictionary<string, PreprocessorMacro>()` — Mapping of name to macro definition
- L268 _private* field_ `List<PreprocessorFile> Files = new List<PreprocessorFile>()` — The stack of included source files
- L273 _private* field_ `List<IncludeDirectory> IncludeDirectories = new List<IncludeDirectory>()` — Include paths to look in
- L278 _private* field_ `HashSet<FileReference> PragmaOnceFiles = new HashSet<FileReference>()` — Set of all included files with the #pragma once directive
- L283 _private* field_ `int Counter` — Value of the __COUNTER__ variable
- L290-349 _public ctor_ `public Preprocessor(FileReference PreludeFile, IEnumerable<string> Definitions, IEnumerable<DirectoryReference> IncludePaths)` — Default constructor
- L354-357 _public property_ `public PreprocessorFile CurrentFile { get; }` — Returns the path to the current file
- L363-366 _public method_ `public FileReference[] CaptureIncludeStack()` — Returns an array consisting of the current include stack
- L372-375 _public method_ `public bool IsBranchActive()` — Determines if the branch that the preprocessor is in is active
- L381-393 _public method_ `public bool PushFile(PreprocessorFile File)` — Push a file onto the preprocessor stack
- L398-401 _public method_ `public void PopFile()` — Remove the topmost file from the preprocessor stack
- L408-411 _private* method_ `string FormatLineDirective(int CurrentLine)` — Format a #line directive at the given line
- L419-444 _private* method_ `void AddMacro(string Name, List<string> Parameters, List<Token> Tokens)` — Validate and add a macro using the given parameter and token list
- L453-458 _private* method_ `void AddSingleTokenMacro(string Name, TokenType Type, string Value)` — Set a predefined macro to a given value
- L465-485 _public method_ `public PreprocessorFile ResolveInclude(List<Token> Tokens, int CurrentLine)` — Tries to resolve an include
- L492-515 _public method_ `public PreprocessorFile ResolveQuotedInclude(string IncludeText)` — Try to resolve an quoted include against the list of include directories. Uses search order described by https://msdn.microsoft.com/en-us/library/36k2cdd4.aspx.
- L522-533 _public method_ `public PreprocessorFile ResolveSystemInclude(string IncludeText)` — Try to resolve a system include against the list of include directories
- L541-553 _public method_ `public PreprocessorFile ResolveSystemInclude(string IncludeText, string[] RelativePathFragments)` — Try to resolve a system include against the list of include directories
- L562-574 _private* method_ `static bool TryResolveRelativePath(WorkspaceDirectory BaseDirectory, string[] RelativePathFragments, out WorkspaceFile Result)` — Tries to get a file at the relative path from a base directory
- L582-616 _public method_ `public void ParseMarkup(PreprocessorMarkupType Type, List<Token> Tokens, int CurrentLine)` — Parse a marked up directive from a file
- L622-699 _public method_ `public void ParseDefineDirective(List<Token> Tokens)` — Read a macro definition
- L706-719 _public method_ `public void ParseUndefDirective(List<Token> Tokens)` — Parse an #undef directive
- L725-745 _public method_ `public void ParseIfDirective(List<Token> Tokens, int CurrentLine)` — Parse an #if directive
- L751-772 _public method_ `public void ParseIfdefDirective(List<Token> Tokens)` — Parse an #ifdef directive
- L778-799 _public method_ `public void ParseIfndefDirective(List<Token> Tokens)` — Parse an #ifndef directive
- L806-837 _public method_ `public void ParseElifDirective(List<Token> Tokens, int CurrentLine)` — Parse an #elif directive
- L843-868 _public method_ `public void ParseElseDirective(List<Token> Tokens)` — Parse an #else directive
- L874-884 _public method_ `public void ParseEndifDirective(List<Token> Tokens)` — Parse an #endif directive
- L890-899 _public method_ `public void ParsePragmaDirective(List<Token> Tokens)` — Parse a #pragma directive
- L907-911 _public method_ `public void ExpandMacros(IEnumerable<Token> InputTokens, List<Token> OutputTokens, bool bIsConditional, int CurrentLine)` — Expand macros in the given sequence.
- L921-934 _private* method_ `void ExpandMacrosRecursively(IEnumerable<Token> InputTokens, List<Token> OutputTokens, bool bIsConditional, int CurrentLine, List<PreprocessorMacro> IgnoreMacros)` — Expand macros in the given sequence, ignoring previously expanded macro names from a list.
- L942-950 _private* method_ `Token MergeLeadingSpace(Token Token, bool bHasLeadingSpace)` — Merges an optional leading space flag into the given token (recycling the original token if possible).
- L961-1062 _private* method_ `bool ReadExpandedToken(IEnumerator<Token> InputEnumerator, List<Token> OutputTokens, bool bIsConditional, Func<int> CurrentLine, List<PreprocessorMacro> IgnoreMacros)` — Read a token from an enumerator and substitute it if it's a macro or 'defined' expression (reading more tokens as necessary to complete the expression).
- L1072-1110 _private* method_ `void ExpandObjectMacro(PreprocessorMacro Macro, List<Token> OutputTokens, bool bIsConditional, int CurrentLine, List<PreprocessorMacro> IgnoreMacros)` — Expand an object macro
- L1120-1291 _private* method_ `void ExpandFunctionMacro(PreprocessorMacro Macro, List<Token> ArgumentListTokens, List<Token> OutputTokens, bool bIsConditional, int CurrentLine, List<PreprocessorMacro> IgnoreMacros)` — Expand a function macro
- L1299-1306 _private* method_ `void AppendTokensWithWhitespace(List<Token> OutputTokens, List<Token> InputTokens, bool bHasLeadingSpace)` — Appends a list of tokens to another list, setting the leading whitespace flag to the given value
- L1315-1346 _private* method_ `bool ReadBalancedToken(List<Token> InputTokens, ref int InputIdx, List<Token> OutputTokens)` — Copies a single token from one list of tokens to another, or if it's an opening parenthesis, the entire subexpression until the closing parenthesis.
- L1355-1382 _private* method_ `bool ReadBalancedToken(IEnumerator<Token> InputEnumerator, List<Token> OutputTokens)` — Copies a single token from one list of tokens to another, or if it's an opening parenthesis, the entire subexpression until the closing parenthesis.
- L1391-1451 _public method_ `public static void CreatePreludeFile(FileReference PreludeFile, CompileEnvironment CompileEnvironment, DirectoryReference WorkingDir)` — Create a file which represents the compiler definitions
- L1458-1472 _public method_ `public void PreprocessFile(string InputFileName, FileReference OutputFile, IEnumerable<FileReference> ForceIncludeFiles)` — Preprocess the current file and write it to the given output
- L1479-1633 _private* method_ `bool PreprocessFile(PreprocessorFile InputFile, TextWriter Writer)` — Preprocess the current file to the given output stream
- L1642-1651 _private* method_ `bool WriteInclude(List<Token> Tokens, int CurrentLine, TextWriter Writer)` — Resolve an included file and write it to an output stream
- L1660-1685 _private* method_ `void WriteText(TextBuffer Text, TextLocation Location, TextLocation EndLocation, TextWriter Writer)` — Preprocess the current file to the given output stream
- L1694-1709 _private* method_ `void WriteBlankedText(TextBuffer Text, TextLocation Location, TextLocation EndLocation, TextWriter Writer)` — Preprocess the current file to the given output stream
- L1719-1777 _private* method_ `void WriteExpandedText(string FileName, TextBuffer Text, TextLocation Location, TextLocation EndLocation, TextWriter Writer)` — Write a portion of the given file to the output stream, expanding macros in it

#### enum `IncludeTool.Preprocessor.BranchState`  
`enum BranchState`  
_private*; L195-236_
- attrs: `[Flags]`
- desc: Flags indicating the state of each nested conditional block in a stack.
- L200 _public* enumerator_ `Active = 0x01` — The current conditional branch is active.
- L205 _public* enumerator_ `Taken = 0x02` — A branch within the current conditional block has been taken. Any #else/#elif blocks will not be taken.
- L210 _public* enumerator_ `Complete = 0x04` — The #else directive for this conditional block has been encountered. An #endif directive is expected next.
- L215 _public* enumerator_ `ParentIsActive = 0x08` — This branch is within an active parent branch
- L220 _public* enumerator_ `HasIfDirective = 0x10` — The first condition in this branch was an #if directive (as opposed to an #ifdef or #ifndef directive)
- L225 _public* enumerator_ `HasIfdefDirective = 0x20` — The first condition in this branch was an #if directive (as opposed to an #ifdef or #ifndef directive)
- L230 _public* enumerator_ `HasIfndefDirective = 0x40` — The first condition in this branch was an #ifndef directive (as opposed to an #ifdef or #if directive)
- L235 _public* enumerator_ `HasElifDirective = 0x80` — The branch has an #elif directive

#### class `IncludeTool.Preprocessor.IncludeDirectory`  
`class IncludeDirectory`  
_private*; L242-253_
- attrs: `[DebuggerDisplay("{Location}")]`
- desc: A directory to search for include paths
- L247 _public field_ `public DirectoryReference Location` — The directory, as specified as a parameter. We keep the original spelling for formatting the preprocessor output to match MSVC.
- L252 _public field_ `public WorkspaceDirectory WorkspaceDirectory` — The corresponding workspace directory

#### class `IncludeTool.PreprocessorTests`  
`static class PreprocessorTests`  
_internal*; L1783-2268_
- desc: Tests for the preprocessor
- L1785-1952 _public method_ `public static void Run(bool bTestFailureCases)`
- L1959-2011 _private* method_ `static void RunTest(string Fragment, string ExpectedResult)` — Preprocess a fragment of code, and check it results in an expected sequence of tokens
- L2020-2050 _public method_ `public static void WritePreprocessedFiles(DirectoryReference WorkingDir, DirectoryReference PreprocessedDir, IEnumerable<KeyValuePair<FileReference, CompileEnvironment>> FilePairs, LineBasedTextWriter Log)` — Preprocess a set of source files
- L2064-2087 _private* method_ `static void WritePreprocessedFile(FileReference InputFile, CompileEnvironment Environment, FileReference PreludeFile, DirectoryReference WorkingDir, DirectoryReference CompilerDir, DirectoryReference CompilerNormalizedDir, DirectoryReference ToolDir, LineBasedTextWriter Log)` — Preprocess a single file, with this tool and the default compiler
- L2096-2160 _private* method_ `static int NormalizePreprocessedFile(FileReference ToolFile, FileReference CompilerFile, FileReference NormalizedCompilerFile, LineBasedTextWriter Log)` — Takes an output file generated by this tool, and removes any formatting differences from a compiler-generated preprocessed file.
- L2170-2205 _private* method_ `static bool FindMatchingLines(string[] ToolLines, ref int ToolIdx, string[] CompilerLines, ref int CompilerIdx)` — Update indices into two line lists until we find two matching lines
- L2213-2242 _private* method_ `static bool ComparePreprocessedLines(string First, string Second)` — Compares two preprocessed source file lines, and returns true if they are the same. Ignores leading, trailing, and consecutive whitespace.
- L2249-2252 _private* method_ `static bool IsWhitespace(char Character)` — Checks whether the given character is whitespace
- L2260-2267 _private* method_ `static int SkipWhitespace(string Line, int Idx)` — Skips past a sequence of whitespace characters

### `Source/Programs/IncludeTool/IncludeTool/PreprocessorExpression.cs` (IncludeTool)


#### class `IncludeTool.PreprocessorExpression`  
`class PreprocessorExpression`  
_internal*; L15-515_
- desc: Class to allow evaluating a preprocessor expression
- L22-31 _public method_ `public static long Evaluate(List<Token> Tokens)` — Evaluate a preprocessor expression
- L39-62 _private* method_ `static long EvaluateTernary(List<Token> Tokens, ref int Idx)` — Evaluates a ternary expression (a? b :c)
- L70-81 _private* method_ `static long EvaluateLogicalOr(List<Token> Tokens, ref int Idx)` — Evaluates a logical-or expression (||)
- L89-100 _private* method_ `static long EvaluateLogicalAnd(List<Token> Tokens, ref int Idx)` — Evaluates a logical-and expression (&&)
- L108-119 _private* method_ `static long EvaluateBitwiseOr(List<Token> Tokens, ref int Idx)` — Evaluates a bitwise-OR expression (^)
- L127-138 _private* method_ `static long EvaluateBitwiseXor(List<Token> Tokens, ref int Idx)` — Evaluates a bitwise-XOR expression (^)
- L146-157 _private* method_ `static long EvaluateBitwiseAnd(List<Token> Tokens, ref int Idx)` — Evaluates a bitwise-AND expression (&)
- L165-185 _private* method_ `static long EvaluateEquality(List<Token> Tokens, ref int Idx)` — Evaluates an equality expression (==, !=)
- L193-221 _private* method_ `static long EvaluateRelational(List<Token> Tokens, ref int Idx)` — Evaluates a relational expression ( , =)
- L229-249 _private* method_ `static long EvaluateShift(List<Token> Tokens, ref int Idx)` — Evaluates a shift expression ( >)
- L257-277 _private* method_ `static long EvaluateAddition(List<Token> Tokens, ref int Idx)` — Evaluates an additive expression (+, -)
- L285-309 _private* method_ `static long EvaluateMultiplication(List<Token> Tokens, ref int Idx)` — Evaluates a multiplicative expression (*, /, %)
- L317-395 _private* method_ `static long EvaluateUnary(List<Token> Tokens, ref int Idx)` — Evaluates a unary expression (+, -, !, ~)
- L403-431 _private* method_ `static long EvaluatePrimary(List<Token> Tokens, ref int Idx)` — Evaluates a primary expression
- L438-514 _private* method_ `static long ParseNumericLiteral(string Token)` — Parse a numeric literal from the given token

#### class `IncludeTool.PreprocessorExpressionTests`  
`static class PreprocessorExpressionTests`  
_internal*; L520-617_
- desc: Tests for preprocessor expressions
- L525-585 _public method_ `public static void Run()` — Run tests on expression evaluation
- L592-616 _private* method_ `static void RunTest(string Expression, long? ExpectedResult)` — Tokenize the given expression and evaluate it, and check it matches the expected result

### `Source/Programs/IncludeTool/IncludeTool/PreprocessorMarkup.cs` (IncludeTool)


#### enum `IncludeTool.PreprocessorMarkupType`  
`enum PreprocessorMarkupType`  
_internal*; L16-92_
- desc: Possible types of source file markup
- L21 _public* enumerator_ `Text` — A span of tokens which are not preprocessor directives
- L26 _public* enumerator_ `Include` — An #include directive
- L31 _public* enumerator_ `Define` — A #define directive
- L36 _public* enumerator_ `Undef` — An #undef directive
- L41 _public* enumerator_ `If` — An #if directive
- L46 _public* enumerator_ `Ifdef` — An #ifdef directive
- L51 _public* enumerator_ `Ifndef` — An #ifndef directive
- L56 _public* enumerator_ `Elif` — An #elif directive
- L61 _public* enumerator_ `Else` — An #else directive
- L66 _public* enumerator_ `Endif` — An #endif directive
- L71 _public* enumerator_ `Pragma` — A #pragma directive
- L76 _public* enumerator_ `Error` — An #error directive
- L81 _public* enumerator_ `Empty` — An empty '#' on a line of its own
- L86 _public* enumerator_ `IncludeMarkup` — Macros which decorate an include directive (eg. THIRD_PARTY_INCLUDES_START, THIRD_PARTY_INCLUDES_END)
- L91 _public* enumerator_ `OtherDirective` — Some other directive

#### class `IncludeTool.PreprocessorMarkup`  
`class PreprocessorMarkup`  
_internal*; L98-415_
- attrs: `[Serializable]`
- desc: Base class for an annotated section of a source file
- L103 _public field_ `public PreprocessorMarkupType Type` — The directive corresponding to this markup
- L108 _public field_ `public bool IsActive` — Whether this markup is within an active preprocessor condition
- L113 _public field_ `public TextLocation Location` — The start of the annotated text
- L118 _public field_ `public TextLocation EndLocation` — The end of the annotated text
- L123 _public field_ `public List<Token> Tokens` — The tokens parsed for this markup. Set for directives.
- L128 _public field_ `public SourceFile IncludedFile` — For #include directives, specifies the included file that it resolves to
- L133 _public field_ `public List<SourceFile> OutputIncludedFiles` — The output list of included files that this should be replaced with
- L142-148 _public ctor_ `public PreprocessorMarkup(PreprocessorMarkupType Directive, TextLocation Location, TextLocation EndLocation, List<Token> Tokens)` — Construct the annotation with the given range
- L154-157 _public method_ `public bool IsInlineInclude()` — Determines if this markup is for an inline include
- L163-166 _public method_ `public bool IsPreprocessorDirective()` — Determines if this markup indicates a preprocessor directive
- L172-185 _public method_ `public bool IsConditionalPreprocessorDirective()` — Determines if this markup indicates a conditional preprocessor directive
- L190-204 _public method_ `public int GetConditionDepthDelta()` — How this condition modifies the condition depth. Opening "if" statements have a value of +1, "endif" statements have a value of -1, and "else" statements have a value of 0.
- L210-226 _public method_ `public bool SetIncludedFile(SourceFile NewIncludedFile)` — Update the target file which an include resolves to
- L232-248 _public method_ `public override string ToString()` — Generate a string describing this annotation
- L255-372 _public method_ `public static PreprocessorMarkup[] ParseArray(string FileName, TextBuffer Text)` — Create markup for the given text buffer
- L382-414 _public method_ `public static bool IsIncludeMarkup(string FileName, TextBuffer Text, TextLocation StartLocation, TextLocation EndLocation)` — Checks whether the given block of text is an include decoration

### `Source/Programs/IncludeTool/IncludeTool/Program.cs` (IncludeTool)


#### enum `IncludeTool.ToolMode`  
`public enum ToolMode`  
_public; L24-55_
- desc: Operating mode for the tool
- L29 _public* enumerator_ `Scan` — Identify all fragments and scan the workspace, but don't do anything else
- L34 _public* enumerator_ `Verify` — Compile all the fragments to ensure they do not have any external dependencies
- L39 _public* enumerator_ `Optimize` — Optimize the files included by a filter
- L44 _public* enumerator_ `Timing` — Gather timing data for compiling each fragment
- L49 _public* enumerator_ `TestPreprocessor` — Compare the preprocessor output to the MSVC compiler output
- L54 _public* enumerator_ `OptimizePCHs` — Optimize the PCHs used by this target

#### enum `IncludeTool.TargetPlatform`  
`public enum TargetPlatform`  
_public; L60-64_
- desc: The target platform to optimize
- L62 _public* enumerator_ `Linux`
- L63 _public* enumerator_ `Win64`

#### enum `IncludeTool.TargetConfiguration`  
`public enum TargetConfiguration`  
_public; L69-75_
- desc: The target configuration to optimize
- L71 _public* enumerator_ `Debug`
- L72 _public* enumerator_ `Development`
- L73 _public* enumerator_ `Test`
- L74 _public* enumerator_ `Shipping`

#### class `IncludeTool.CommandLineOptions`  
`public class CommandLineOptions`  
_public; L80-237_
- desc: Command line options for the program
- L86 _public field_ `public ToolMode Mode` — attrs: `[CommandLineOption(IsRequired = true)]` — Mode to run the tool in
- L92 _public field_ `public string InputDir` — attrs: `[CommandLineOption]` — Input directory for source files
- L98 _public field_ `public string WorkingDir` — attrs: `[CommandLineOption(IsRequired = true)]` — Working directory for optimization data and reports
- L104 _public field_ `public string Target = "UnrealPak"` — attrs: `[CommandLineOption]` — The target to scrape the compile environment from UBT for
- L110 _public field_ `public TargetPlatform Platform = TargetPlatform.Win64` — attrs: `[CommandLineOption]` — The target platform to scrape the compile environment for
- L116 _public field_ `public TargetConfiguration Configuration = TargetConfiguration.Debug` — attrs: `[CommandLineOption]` — The target configuration to scrape the compile environment for
- L122 _public field_ `public bool Precompile = false` — attrs: `[CommandLineOption]` — Whether to precompile the given target, or just build what's needed to run.
- L128 _public field_ `public string OutputDir` — attrs: `[CommandLineOption]` — Directory for output source files
- L134 _public field_ `public bool CleanTaskList` — attrs: `[CommandLineOption]` — Skip generating a task list for the files to be optimized
- L140 _public field_ `public bool SkipCycleCheck` — attrs: `[CommandLineOption]` — Skip checking for cycles in the source data
- L146 _public field_ `public bool SkipDiagnostics` — attrs: `[CommandLineOption]` — Whether to suppress warnings and diagnostic information for the initial parse
- L152 _public field_ `public bool RemoveForwardDeclarations` — attrs: `[CommandLineOption]` — Filters the list of forward declarations in output files to the ones that the tool identifies as dependencies.
- L158 _public field_ `public string SourceFiles` — attrs: `[CommandLineOption]` — The source files from the target to preprocess and optimize
- L164 _public field_ `public string OptimizeFiles` — attrs: `[CommandLineOption]` — Filter for files which should be optimized
- L170 _public field_ `public string OutputFiles` — attrs: `[CommandLineOption]` — Filter for files that can be output. Every other file will be treated as read-only.
- L176 _public field_ `public bool NotStandalone` — attrs: `[CommandLineOption]` — Don't rewrite the files being optimized to make them standalone
- L182 _public field_ `public bool UseOriginalIncludes` — attrs: `[CommandLineOption]` — Disables code which calculates a new set of includes for each output file.
- L188 _public field_ `public int NumSamples = 3` — attrs: `[CommandLineOption]` — When generating timing data, how many samples to take
- L194 _public field_ `public int MaxParallel = Environment.ProcessorCount` — attrs: `[CommandLineOption]` — Number of optimization workers to spawn in parallel. Defaults to the logical number of processors.
- L200 _public field_ `public int Shard = 1` — attrs: `[CommandLineOption]` — When splitting up work to run in parallel, the index of the current shard
- L206 _public field_ `public int NumShards = 1` — attrs: `[CommandLineOption]` — The total number of shards being run
- L212 _public field_ `public double TimeLimit = -1.0` — attrs: `[CommandLineOption]` — Maximum amount of time to run for. When running a sharded build, this can be used to stop and regroup dependencies before running again.
- L218 _public field_ `public double PchRatio = 0.05` — attrs: `[CommandLineOption]` — Proportion of files which must reference a header for it to be included in the PCH
- L224 _public field_ `public bool Report` — attrs: `[CommandLineOption]` — Whether to output a report containing complexity information
- L230 _public field_ `public bool P4` — attrs: `[CommandLineOption]` — Whether to check out files from p4 before writing
- L236 _public field_ `public bool VerboseFileLog` — attrs: `[CommandLineOption]` — Writes a verbose log per-output file

#### class `IncludeTool.Program`  
`static class Program`  
_internal*; L242-1663_
- desc: The main program class
- L244 _private* field_ `static readonly string[] StandardModuleDirectoryNames = { "Public", "Private", "Classes" }`
- L246 _private* const_ `const uint SEM_FAILCRITICALERRORS = 0x01`
- L247 _private* const_ `const uint SEM_NOGPFAULTERRORBOX = 0x0002`
- L250 _private* method_ `static extern uint SetErrorMode(uint Mode)` — attrs: `[DllImport("kernel32.dll")]`
- L257-845 _private* method_ `static int Main(string[] Args)` — Main entry point for the program
- L853-888 _private* method_ `static FileFilter CreateFilter(DirectoryReference InputDir, string Rules)` — Create a filter from the given settings
- L897-920 _private* method_ `static void GenerateTaskList(DirectoryReference RootDir, string Target, TargetPlatform Platform, TargetConfiguration Configuration, bool Precompile, FileReference TaskListFile, LineBasedTextWriter Log)` — Create a task list for compiling a given target
- L927-930 _private* method_ `static bool IsGeneratedCppFile(FileReference Location)` — Tests whether the given filename is a .generated.cpp file (or .generated.2.cpp, etc..)
- L953-965 _private* method_ `static void PreprocessFiles(DirectoryReference WorkingDir, KeyValuePair<FileReference, CompileEnvironment>[] FilesToCompile, IEnumerable<DirectoryReference> ExtraSystemIncludePaths, LineBasedTextWriter Log)` — Preprocess the given files and update the markup on them to reflect which directives are active, and which files #include directives resolve to.
- L975-1002 _private* method_ `static void PreprocessFile(FileReference Location, FileReference PreludeLocation, CompileEnvironment CompileEnvironment, IEnumerable<DirectoryReference> ExtraSystemIncludePaths, ConcurrentDictionary<SourceFile, MarkupState> FileToActiveMarkup, LineBasedTextWriter Log)` — Preprocess a given file, updating the markup for each included file
- L1011-1158 _private* method_ `static void PreprocessIncludedFile(Preprocessor Preprocessor, PreprocessorFile IncludedFile, ConcurrentDictionary<SourceFile, MarkupState> FileToActiveMarkup, LineBasedTextWriter Log)` — Process an included file with the given preprocessor
- L1165-1177 _private* method_ `static void FindPreprocessedFiles(SourceFile File, HashSet<SourceFile> PreprocessedFiles)` — Find all the preprocessed files included by the given file
- L1183-1190 _private* method_ `static void CreateFragments(IEnumerable<SourceFile> Files)` — Creates all the fragments for files in the given list, and the files they reference
- L1196-1272 _private* method_ `static void CreateFragmentsRecursively(SourceFile File, HashSet<string> UniqueNames)` — Recurses through all the files included by a given file, creating markup for them as necessary
- L1278-1289 _private* method_ `static void WriteFragments(IEnumerable<SourceFile> Files, DirectoryReference OutputDir)` — Write out all the fragments for the given files
- L1297-1334 _private* method_ `static void WriteFragmentsRecursively(SourceFile File, DirectoryReference OutputDir, HashSet<SourceFile> VisitedFiles)` — Recursively write out the fragments for a file
- L1346-1544 _public method_ `public static bool ProcessSequenceTree(SequenceProbeType Type, Dictionary<SourceFile, CompileEnvironment> SourceFileToCompileEnvironment, DirectoryReference IntermediateDir, IEnumerable<DirectoryReference> ExtraSystemIncludePaths, int MaxParallel, int ShardIdx, int NumShards, double TimeLimit, LineBasedTextWriter Log)` — Find dependencies for files in the given dependency tree
- L1551-1568 _private* method_ `static void FixupDependencies(SourceFragment Fragment, HashSet<SourceFragment> VisitedFragments)` — Fixup all the dependencies of the given fragment to ensure it includes all its dependencies recursively
- L1582-1610 _private* method_ `static bool WriteOptimizedFiles(DirectoryReference InputDir, DirectoryReference OutputDir, HashList<DirectoryReference> PublicIncludePaths, Dictionary<BuildModule, HashList<DirectoryReference>> PrivateIncludePaths, HashList<DirectoryReference> SystemIncludePaths, IEnumerable<SourceFile> OutputFiles, bool bWithP4, bool bWithVerboseLog, bool bRemoveForwardDeclarations, LineBasedTextWriter Log)` — Write all the output files
- L1620-1662 _private* method_ `static bool WriteOutputFiles(DirectoryReference OutputDir, Dictionary<FileReference, string> OutputFileContents, bool bWithP4, LineBasedTextWriter Log)` — Write all the output files, optionally checking them out of Perforce

#### class `IncludeTool.Program.MarkupState`  
`class MarkupState`  
_private*; L935-946_
- desc: Class used to record
- L940 _public field_ `public BitArray Flags` — Flags for each markup item in the stack
- L945 _public field_ `public FileReference[] IncludeStack` — Include stack which was used to create these flags

### `Source/Programs/IncludeTool/IncludeTool/Properties/AssemblyInfo.cs` (IncludeTool)
_(no declarations)_


### `Source/Programs/IncludeTool/IncludeTool/Properties/Resources.Designer.cs` (IncludeTool)


#### class `IncludeTool.Properties.Resources`  
`internal class Resources`  
_internal; L25-100_
- attrs: `[global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0")] [global::System.Diagnostics.DebuggerNonUserCodeAttribute()] [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]`
- L27 _private field_ `private static global::System.Resources.ResourceManager resourceMan`
- L29 _private field_ `private static global::System.Globalization.CultureInfo resourceCulture`
- L32-33 _internal ctor_ `internal Resources()` — attrs: `[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]`
- L39-47 _internal property_ `internal static global::System.Resources.ResourceManager ResourceManager { get; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Returns the cached ResourceManager instance used by this class.
- L54-61 _internal property_ `internal static global::System.Globalization.CultureInfo Culture { get; set; }` — attrs: `[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]` — Overrides the current thread's CurrentUICulture property for all resource lookups using this strongly typed resource class.
- L95-99 _internal property_ `internal static string Prelude { get; }` — Looks up a localized string similar to ; This file is used to generate Prelude.h, which sets up the initial environment for the preprocessor. ; Standard macros __STDC__ __STDC_VERSION__ __STDC_HOSTED__ __cplusplus __TIMESTAMP__ ; Microsoft defines, taken from https://msdn.microsoft.com/en-us/library/b0084kay.aspx _ATL_VER __AVX__ __AVX2__ _CHAR_UNSIGNED __CLR_VER __cplusplus_cli __cplusplus_winrt _CPPRTTI _CPPUNWIND _DEBUG _DLL _INTEGRAL_MAX_BITS _M_AMD64 _M_ARM _M_CEE _M_CEE_PURE _M_CEE_SAFE _M_IX86 _M_ARM_FP _M_I [rest of string was truncated]&quot;;.

### `Source/Programs/IncludeTool/IncludeTool/Reports/ComplexityReport.cs` (IncludeTool)


#### class `IncludeTool.Reports.ComplexityData`  
`class ComplexityData`  
_internal*; L18-34_
- desc: Class containing information about a source file's complexity
- L23 _public field_ `public int NumPreprocessedLines` — The number of preprocessed lines in this source file, were it to be preprocessed in isolation
- L28 _public field_ `public HashSet<SourceFile> IncludedBy = new HashSet<SourceFile>()` — Set of files which directly or indirectly include this file
- L33 _public field_ `public HashSet<SourceFile> DirectlyIncludedBy = new HashSet<SourceFile>()` — Set of files which directly include this file

#### class `IncludeTool.Reports.ComplexityReport`  
`static class ComplexityReport`  
_internal*; L39-165_
- desc: Utility functions to generate a report detailing the complexity of each preprocessed file
- L47-94 _public method_ `public static void Generate(FileReference ReportFileLocation, IEnumerable<SourceFile> Files, LineBasedTextWriter Log)` — Generate a report showing the number of preprocessed lines in the selected files
- L101-105 _private* method_ `static string GetDisplayName(SourceFile File)` — Get the simple display name for a source file
- L113-123 _private* method_ `static ComplexityData FindOrAddComplexityData(SourceFile SourceFile, Dictionary<SourceFile, ComplexityData> FileToComplexityData)` — Gets a ComplexityData object for the given source file, or creates it if it does not exist.
- L129-135 _private* method_ `static List<SourceFile> FindIncludedFiles(SourceFile File)` — Recurse through this file and all the files it includes.
- L142-164 _private* method_ `static void FindIncludedFilesInternal(SourceFile File, List<SourceFile> IncludedFiles, HashSet<SourceFile> UniqueIncludedFiles)` — Recurse through this file and all the files it includes, invoking a delegate for each file on entering and leaving each file.

### `Source/Programs/IncludeTool/IncludeTool/Reports/FragmentTimingReport.cs` (IncludeTool)


#### struct `IncludeTool.Reports.FragmentTimingSample`  
`struct FragmentTimingSample`  
_internal*; L18-34_
- desc: Timing data for a single compile
- L23 _public field_ `public double TotalTime` — The total compile time
- L28 _public field_ `public double FrontendTime` — The total frontend compile time
- L33 _public field_ `public double BackendTime` — The total backend compile time

#### class `IncludeTool.Reports.FragmentTimingData`  
`class FragmentTimingData`  
_internal*; L39-243_
- desc: Stores timing data for compiling a fragment
- L44 _public field_ `public string UniqueName` — The unique name for this path
- L49 _public field_ `public string Digest` — The unique digest for this sequence
- L54 _public field_ `public FragmentTimingData PrevFragmentData` — Data for compiling the previous fragment
- L59 _public field_ `public SourceFragment Fragment` — The current fragment
- L64 _public field_ `public FileReference IntermediateFile` — Path to the intermediate file
- L69 _public field_ `public CompileEnvironment CompileEnvironment` — The compile environment for this fragment
- L74 _public field_ `public List<FragmentTimingSample> Samples = new List<FragmentTimingSample>()` — List of samples
- L84-132 _public ctor_ `public FragmentTimingData(string UniqueName, string Digest, FragmentTimingData PrevFragmentData, SourceFragment[] Fragments, List<Tuple<int, SourceFile>> IncludeHistory, FileReference IntermediateFile, CompileEnvironment CompileEnvironment)` — Constructor
- L137-223 _public method_ `public void Compile(DirectoryReference IntermediateDir, int SampleIdx)` — Compiles the fragment and adds the compile time to the list
- L225-242 _private* method_ `static bool TryParseCompileTime(string Line, string ModuleName, out double Time)`

#### class `IncludeTool.Reports.FragmentTimingReport`  
`static class FragmentTimingReport`  
_internal*; L248-442_
- desc: Generates timing data for compiling each fragment
- L258-441 _public method_ `public static void Generate(DirectoryReference InputDir, DirectoryReference WorkingDir, Dictionary<SourceFile, CompileEnvironment> FileToCompileEnvironment, int NumSamples, int Shard, int NumShards, int MaxParallel, LineBasedTextWriter Log)` — Gather compile time telemetry for the given files

### `Source/Programs/IncludeTool/IncludeTool/Reports/PchReport.cs` (IncludeTool)


#### class `IncludeTool.Reports.PchInfo`  
`class PchInfo`  
_internal*; L14-25_
- L16 _public field_ `public FileReference PchFile`
- L17 _public field_ `public HashList<BuildModule> PublicIncludePathModules = new HashList<BuildModule>()`
- L18 _public field_ `public HashSet<FileReference> SourceFiles = new HashSet<FileReference>()`
- L19 _public field_ `public Dictionary<SourceFile, int> IncludedFiles = ...`
- L19 _public field_ `public Dictionary< IncludedFiles = new Dictionary<SourceFile, int>()`
- L21-24 _public ctor_ `public PchInfo(FileReference PchFile)`

#### class `IncludeTool.Reports.PchReport`  
`static class PchReport`  
_internal*; L30-267_
- desc: Generates a report listing the most frequently referenced headers in the codebase
- L40-64 _public method_ `public static void Generate(FileReference ReportFileLocation, DirectoryReference InputDir, BuildTarget Target, Dictionary<SourceFile, CompileEnvironment> SourceFileToCompileEnvironment, LineBasedTextWriter Log)` — Generate a report showing the number of preprocessed lines in the selected files
- L76-131 _public method_ `public static void GeneratePCHs(BuildTarget Target, Dictionary<SourceFile, CompileEnvironment> SourceFileToCompileEnvironment, IEnumerable<DirectoryReference> IncludePaths, IEnumerable<DirectoryReference> SystemIncludePaths, Dictionary<FileReference, string> OutputFileContents, float MinRatio, LineBasedTextWriter Log)` — Generate optimized PCHs which include headers used by a ratio of the source files
- L139-221 _private* method_ `static void FindPchInfo(BuildTarget Target, Dictionary<SourceFile, CompileEnvironment> SourceFileToCompileEnvironment, Dictionary<FileReference, PchInfo> FileToPchInfo, LineBasedTextWriter Log)` — Find a mapping from PCH to the most included files by the files using it
- L229-244 _private* method_ `static void FindModuleOrder(IEnumerable<BuildModule> Modules, Dictionary<BuildModule, int> ModuleToIndex, HashSet<BuildModule> VisitedModules)` — Find a module ordering for output PCH files
- L251-266 _private* method_ `static void FindIncludedFiles(SourceFile File, HashSet<SourceFile> IncludedFiles)` — Recurse through this file and all the files it includes, invoking a delegate for each file on entering and leaving each file.

### `Source/Programs/IncludeTool/IncludeTool/Reports/SymbolReport.cs` (IncludeTool)


#### class `IncludeTool.SymbolReport`  
`static class SymbolReport`  
_internal*; L17-87_
- desc: Generates a report listing the most frequently referenced symbols in each module
- L25-86 _public method_ `public static void Generate(FileReference ReportFileLocation, DirectoryReference InputDir, HashSet<SourceFile> PreprocessedFiles, LineBasedTextWriter Log)` — Generates a report listing the most frequently referenced opaque symbols in each module

### `Source/Programs/IncludeTool/IncludeTool/Rules.cs` (IncludeTool)


#### class `IncludeTool.RulesMutator`  
`abstract class RulesMutator`  
_internal*; L17-23_
- desc: Class which can modify the rules object at runtime
- L22 _public method_ `public abstract void Run()` — Allows a platform specific hook to modify the rules class

#### class `IncludeTool.Rules`  
`static class Rules`  
_internal*; L28-720_
- desc: Contains callback functions to disambiguate and provide metadata for files in this branch
- L33 _private* field_ `static readonly string[] IgnoredSearchDirectories = { "/engine/extras/notforlicensees/doxygen/", "/engine/plugins/editor/pluginbrowser/templates/", "/engine/source/runtime/engine/classes/intrinsic/", "/engine/source/thirdparty/llvm/", "/engine/source/p ...` — List of directories to ignore when scanning the branch for source files
- L50-74 _public method_ `public static bool SearchDirectoryForSource(string NormalizedPath)` — Callback to filter which directories are searched when looking for source code
- L79 _private* field_ `static readonly string[] ExternalFileIncludePaths = { "binkplugin.h", "egttypes.h", "oodle.h", "oodle2.h", "xg.h", "xmem.h", "nvtess.h", "jemalloc.h", "target/include/json2.h", "fios2.h", "SDL.h", "SDL_timer.h", "SDL3/", "zlib.h", "sqlite3.h", "emscrip ...` — List of include tokens which are external files, and do not need to be resolved
- L185-188 _public method_ `public static bool IsExternalInclude(string IncludePath)` — Determine whether the given include token is to an external file. If so, it doesn't need to be resolved.
- L195-237 _public method_ `public static bool IsExternalHeaderPath(string NormalizedPath)` — Determine if the given path is to an external file. If so, it doesn't need to be resolved.
- L243-246 _public method_ `public static bool ShouldIgnoreExports(string NormalizedPath)` — Determines whether to ignore parsing exported symbols from a file
- L253-256 _public method_ `public static bool IsSourceFile(string NormalizedPath)` — Determines if the given file path is to a C++ source (or header) file
- L261 _private* field_ `static string[,] IgnoreIncludePatterns = new string[,] { { "/portal/source/layers/", "/engine/source/editor/unrealed/" }, { "/portal/source/layers/", "/engine/source/runtime/online/icmp/" }, { "/engine/source/programs/unreallightmass/", "/en ...` — List of include paths to ignore. Files under paths in the first entry do NOT include any files under paths in the second entry.
- L274-284 _public method_ `public static bool IsExternalIncludeMacro(List<Token> Tokens)` — Checks to see if the given token is a known include macro
- L289 _private* field_ `static readonly HashSet<string> PinnedFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Runtime/Core/Public/GenericPlatform/GenericPlatform.h", "/Engine/Source/Runtime/Core/Public/Math/UnrealMatrix.h", "/Engine/Sourc ...` — List of files whose includes are pinned to the file they are included from
- L378 _private* field_ `static readonly HashSet<string> NotStandaloneFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Runtime/Core/Public/Delegates/DelegateCombinations.h", "/Engine/Source/Runtime/Core/Public/Containers/LockFreeListImpl.h", "/Eng ...` — List of files whose includes are pinned to the file they are included from
- L397 _private* field_ `static readonly HashSet<string> AggregateFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Runtime/Slate/Public/SlateBasics.h", "/Engine/Source/Editor/UnrealEd/Public/UnrealEd.h" }` — List of files whose includes are pinned to the file they are included from
- L407 _private* field_ `static readonly HashSet<string> NonAggregateFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Runtime/RHI/Public/RHI.h", }` — List of files whose includes are pinned to the file they are included from
- L415 _private* field_ `static readonly HashSet<string> AllowMultipleFragmentFileNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Runtime/Sockets/Private/BSDSockets/SocketSubsystemBSD.h", "/Engine/Source/Runtime/Sockets/Private/BSDSockets/SocketsBSD.h", "/En ...` — List of files which are ok to split into multiple fragments
- L429 _private* field_ `static readonly HashSet<string> IgnoreFwdHeaders = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { "/Engine/Source/Developer/DerivedDataCache/Public/DerivedDataSharedStringFwd.h", "/Engine/Source/Runtime/Core/Public/Internationalization/TextNa ...` — Files which should not be treated as containing purely forward declarations, despite a "fwd.h" suffix
- L478-552 _public method_ `public static SourceFileFlags GetSourceFileFlags(WorkspaceFile File)` — Gets the flags for a new source file
- L558-572 _public method_ `public static void ApplyAdditionalRules(DirectoryReference BranchRoot)` — Apply any additional markup to files in the branch
- L580-585 _private* method_ `static void AddCounterpart(DirectoryReference BranchRoot, string FirstFileName, string SecondFileName)` — Adds one file as a counterpart to the other
- L593-643 _public method_ `public static bool AllowDifferentMarkup(SourceFile File, int MarkupIdx)` — Override to allow a block of markup to be be different between two derivations
- L645 _private* field_ `static readonly string[] PathsToIgnoreForOldStyleHeaders = new string[] { "/Engine/Source/Runtime/Navmesh/Public/DebugUtils/", "/Engine/Source/Runtime/Navmesh/Public/Detour/", "/Engine/Source/Runtime/Navmesh/Public/DetourCrowd/", "/Engine/Source/Runtime/Navme ...`
- L682-686 _public method_ `public static bool IgnoreOldStyleHeaderGuards(FileReference Location)` — Whether to ignore old-style header guards
- L693-700 _public method_ `public static bool AllowSymbol(string Name)` — Allow overriding whether a symbol should be forward-declared
- L703 _private* field_ `static readonly string[] PathsToIgnoreConflictingSymbols = new string[] { "/Engine/Source/Runtime/Core/Public/Async/TaskGraphInterfaces.h", "/Engine/Source/Runtime/Core/Public/Async/TaskGraphFwd.h", "/Engine/Source/Runtime/Core/Public/Delegates/DelegateAccess ...`
- L715-719 _public method_ `public static bool ReportConflictingSymbolsForFile(FileReference Location)` — Returns true if the file given should be included in report about conflicting symbols.

### `Source/Programs/IncludeTool/IncludeTool/SequenceProbe.cs` (IncludeTool)


#### enum `IncludeTool.SequenceProbeType`  
`enum SequenceProbeType`  
_internal*; L18-29_
- desc: Type of probe to create
- L23 _public* enumerator_ `Verify` — Compile the sequence without optimizing to ensure that it is valid
- L28 _public* enumerator_ `Optimize` — Find the minimal set of dependencies for the fragments

#### enum `IncludeTool.SequenceProbeResult`  
`enum SequenceProbeResult`  
_internal*; L34-55_
- desc: Return code for a probe iteration
- L39 _public* enumerator_ `Failed` — The worker failed with a fatal error
- L44 _public* enumerator_ `FailedAllowRetry` — The worker failed due to a potentially intermittent error
- L49 _public* enumerator_ `Updated` — The worker was updated
- L54 _public* enumerator_ `Completed` — The fragment has been optimized

#### class `IncludeTool.SequenceProbe`  
`class SequenceProbe : IDisposable`  
_internal*; L60-691_
- inherits: `IDisposable`
- desc: Worker class for finding dependencies of a given source file
- L65 _public field_ `public readonly SequenceProbeType Type` — What mode to run this worker in
- L70 _public field_ `public readonly SourceFragment[] Fragments` — The full list of fragments from the root of the tree
- L75 _public field_ `public readonly SourceFragment LastFragment` — The fragment we're finding dependencies for
- L80 _private* field_ `SequenceWorker Worker` — The current task state
- L85 _private* field_ `ManagedTask ActiveInstance` — Instance of the executing task
- L90 _private* field_ `DirectoryReference IntermediateDir` — Output directory for intermediate files
- L95 _private* field_ `string UniqueName` — Unique name assigned to
- L100 _private* field_ `FileReference TaskStateFile` — Path to the file storing the serialized task
- L105 _private* field_ `FileReference SummaryLogFile` — Path to the summary log file
- L110 _private* field_ `FileReference CompileLogFile` — Path to the compiler log file
- L115 _private* field_ `HashSet<SourceFragment> WarnedMissingDependencies = new HashSet<SourceFragment>()`
- L124-322 _public ctor_ `public SequenceProbe(SequenceProbeType Type, SourceFragment[] Fragments, Tuple<int, SourceFile>[] IncludeHistory, CompileEnvironment CompileEnvironment, DirectoryReference IntermediateDir, IEnumerable<DirectoryReference> ExtraSystemIncludePaths, string UniqueName)` — Constructor
- L330-367 _private* method_ `static void AddDependency(SequenceWorker Worker, SourceFragment[] Fragments, int FragmentIdx)` — Adds a known dependency to the given task
- L375-403 _private* method_ `static string CreateDigest(SequenceWorker Worker, HashSet<string> IgnoreFragments)` — Creates a string representing a context-free representation of the task, for using in comparing whether the task parameters have changed.
- L408-415 _public method_ `public void Dispose()` — Dispose of any executing task object
- L420-423 _public property_ `public bool IsComplete { get; }` — Checks whether the worker is complete
- L428-431 _public property_ `public int FragmentCount { get; }` — The number of fragments in the node being optimized
- L436-439 _public property_ `public int CompletedFragmentCount { get; }` — The number of completed fragments in the node being optimized
- L445-492 _private* method_ `void UpdateDependencies(LineBasedTextWriter Log)` — Update the list of known dependencies to include dependencies of our already known dependencies
- L497-530 _public method_ `public void Start(LineBasedTextWriter Log)` — Start this worker
- L538-544 _private* method_ `static int Verify(string StateFile, LineBasedTextWriter Writer)` — Checks that the given permutation compiles
- L552-558 _private* method_ `static int FindNextDependency(string StateFile, LineBasedTextWriter Writer)` — Runs the FindDependencyTask with the given state file
- L565-667 _public method_ `public SequenceProbeResult Join(LineBasedTextWriter Writer)` — Wait for this worker to complete
- L672-680 _private* method_ `void SetCompletedDependencies()` — Updates the dependencies on the target fragment if we're done
- L687-690 _public method_ `public static int WaitForAny(SequenceProbe[] Workers, int TimeoutMilliseconds)` — Wait for any of the given tasks to complete

### `Source/Programs/IncludeTool/IncludeTool/SequenceWorker.cs` (IncludeTool)


#### class `IncludeTool.SequenceWorker`  
`class SequenceWorker`  
_internal*; L21-617_
- desc: Encapsulates the state of a sequence of fragments being optimized
- L26 _public field_ `public string PermutationFileName` — Path to the temporary file to write out permutations of the source file to try compiling
- L31 _public field_ `public string ResponseFileName` — Path to the response file passed to the compiler
- L36 _public field_ `public string ResponseFileDigest` — Digest of the response file; for determining validity of the task data
- L41 _public field_ `public string[] FragmentFileNames` — Array of filenames that we're optimizing. Used for display of initial state and output state; the actual file contents being optimized is stored in Lines.
- L46 _public field_ `public string[] FragmentDigests` — Digest for each fragment
- L51 _public field_ `public Tuple<int, string>[] Lines` — Array of lines in the source file to analyze. The accompanying integer indicates the
- L51 _public field_ `public Tuple< Lines` — Array of lines in the source file to analyze. The accompanying integer indicates the
- L56 _public field_ `public string CompilerExe` — Path to the compiler executable
- L61 _public field_ `public int FragmentCount` — The total number of fragments
- L66 _public field_ `public int RemainingFragmentCount` — The number of fragments from the start of the array which have not yet been checked, so are assumed to be required dependencies (in addition to the Dependencies set).
- L71 _public field_ `public SortedSet<int> KnownDependencies = new SortedSet<int>()` — Set of indices into the array of fragments of known dependencies.
- L76 _public field_ `public int CompileCount` — The number of compiles that have been performed
- L81 _public field_ `public List<string> SummaryLog = new List<string>()` — Output lines for the summary log file
- L86 _public field_ `public List<string> CompileLog = new List<string>()` — Output lines for the compiler log file
- L91 _public field_ `public bool bSingleStepMode = false`
- L96 _public field_ `public bool bResult = true`
- L101-103 _private* ctor_ `SequenceWorker()` — Private constructor. Used when deserializing from disk.
- L115-148 _public ctor_ `public SequenceWorker(string PermutationFileName, string ResponseFileName, string ResponseFileDigest, string[] FragmentFileNames, string[] FragmentDigests, Tuple<int, string>[] Lines, string CompilerExe)` — Construct a new worker instance
- L156-159 _private* method_ `static void Log(List<string> LogLines, string Format, params object[] Args)` — Adds a line to the given log
- L165-219 _public method_ `public void Serialize(string FileName)` — Serialize this worker to a file
- L226-283 _public method_ `public static SequenceWorker Deserialize(string FileName)` — Deserialize a worker from a file
- L289-292 _public method_ `public void Verify(LineBasedTextWriter Writer)` — Compiles the permutation in its current state
- L298-383 _public method_ `public void FindNextDependency(LineBasedTextWriter Writer)` — Find the next dependency
- L393-421 _private* method_ `bool CompilePermutation(List<int> PotentialDependencyCounts, int MinRequired, int Pivot, int MaxRequired)` — Try to compile a given permutation
- L429-453 _private* method_ `bool Compile(List<string> Output)` — Invokes the compiler with the given arguments, capturing the output to an array of strings. Retries if the compiler fails with an XGE error.
- L455 _private* const_ `const uint SEM_FAILCRITICALERRORS = 0x01`
- L456 _private* const_ `const uint SEM_NOGPFAULTERRORBOX = 0x0002`
- L459 _private* method_ `static extern uint SetErrorMode(uint Mode)` — attrs: `[DllImport("kernel32.dll")]`
- L466-486 _private* method_ `bool CompileInternal(List<string> Output)` — Invokes the compiler with the given arguments, capturing the output to an array of strings
- L495-517 _private* method_ `static BitArray CreatePermutationArray(int Length, IEnumerable<int> Dependencies, int PivotCount)` — Create a permutation array for the known dependencies and given pivot
- L526-568 _private* method_ `static void WritePermutation(string PermutationFileName, Tuple<int, string>[] Lines, BitArray Permutation)` — Writes a file containing the given permutation
- L585-616 _private* method_ `static string GetCurrentIterationRow(List<int> PotentialDependencyCounts, int MinRequired, int Pivot, int MaxRequired, SortedSet<int> Dependencies, BitArray Permutation)` — Formats a string containing an ASCII chart representing the permutation being compiled. Key is as follows: 'x' Known dependency ' ' Known non-dependency 'o' Outside current search range, treating as a required dependency '-' Unknown dependency, currently testing as enabled '.' Unknown dependency, currently testing as disabled

### `Source/Programs/IncludeTool/IncludeTool/SourceFile.cs` (IncludeTool)


#### enum `IncludeTool.SourceFileFlags`  
`enum SourceFileFlags`  
_internal*; L20-110_
- attrs: `[Flags]`
- desc: Flags which apply to a source file
- L25 _public* enumerator_ `External = 0x01` — This file is external, and cannot be optimized by the tool
- L30 _public* enumerator_ `GeneratedHeader = 0x02` — This file is a .generated.h file
- L35 _public* enumerator_ `GeneratedClassesHeader = 0x04` — This file is a generated classes.h file
- L42 _public* enumerator_ `Inline = 0x08` — Includes of this file are context-specific to the location that they are included from, and are forced to be inlined into a fragment rather than being treated as an optional dependency. Typically for headers which rely on mutating the processor environment which can occur inside other declarations (eg. ScriptSerialization.h). NOTE: These files will be included from their original location, and must NOT include other files.
- L49 _public* enumerator_ `Pinned = 0x10` — Includes of this file must be kept in the files that currently include them. Platform-specific headers are typically marked like this. Unlike the inline flag, pinned files may contain multiple fragments and includes of other files which need optimizing, but they should not be included outside their current location. Pinned files are given a node in the sequence tree, and are forced to be included.
- L54 _public* enumerator_ `Standalone = 0x20` — This file is meant to compile in isolation
- L59 _public* enumerator_ `Aggregate = 0x80` — This file should not be optimized, and is meant to retain all its original includes (eg. Core.h)
- L64 _public* enumerator_ `Optimize = 0x100` — This file should be optimized
- L69 _public* enumerator_ `Monolithic = 0x200` — This is a monolithic header
- L74 _public* enumerator_ `TranslationUnit = 0x400` — This file is a translation unit
- L79 _public* enumerator_ `AllowMultipleFragments = 0x800` — Whether this file is allowed to have multiple fragments
- L84 _public* enumerator_ `IsCoreTypes = 0x1000` — Special flag to mark the CoreTypes.h header, so it can be included as a monolithic header.
- L89 _public* enumerator_ `IsCoreMinimal = 0x2000` — Special flag to mark the CoreMinimal.h header, so it can be included as a monolithic header.
- L94 _public* enumerator_ `Public = 0x4000` — This file is in a public directory (eg. ModuleName/Public or ModuleName/Classes).
- L99 _public* enumerator_ `FwdHeader = 0x8000` — This header consists of forward declarations
- L104 _public* enumerator_ `Output = 0x10000` — This file should be output
- L109 _public* enumerator_ `IgnoreExportedSymbols = 0x20000` — Do not scan this file for exported symbols

#### class `IncludeTool.SourceFile`  
`class SourceFile`  
_internal*; L116-828_
- attrs: `[Serializable]`
- desc: Encapsulates metadata for a C++ source file
- L121 _public field_ `public readonly FileReference Location` — The location of the file on disk
- L126 _public field_ `public readonly TextBuffer Text` — The contents of the file. May be null for opaque files.
- L131 _public field_ `public readonly PreprocessorMarkup[] Markup` — Markup dividing up this source file
- L136 _public field_ `public readonly int BodyMinIdx` — Index into the Markup array of the first item after any header guards and/or #pragma once directives
- L141 _public field_ `public readonly int BodyMaxIdx` — Index into the Markup array one past the last item not part of a header guard
- L146 _public field_ `public BuildModule Module` — The module that this source file belongs to.
- L151 _public field_ `public SourceFileFlags Flags` — Properties of this file
- L156 _public field_ `public SourceFragment[] Fragments` — Parsed fragments in this file. Only set for files which are being optimized.
- L161-165 _public property_ `public SourceFile Counterpart { get; set; }` — For files that occur in matched pairs (eg. PreWindowsApi.h, PostWindowsApi.h), references the counterpart to this file. Otherwise null.
- L170 _public field_ `public List<SourceFile> MissingIncludes = new List<SourceFile>()` — Files inserted at the start of this file to make it possible to include this file on its own
- L175 _public field_ `public HashList<string> ForwardDeclarations = new HashList<string>()` — Forward declarations which are inserted prior to optimization
- L180 _public field_ `public List<string> VerboseOutput = new List<string>()` — Verbose per-file log lines
- L185 _private* field_ `static Regex OptionsPattern = new Regex(@"^\s*//\s*\[\[\s*IncludeTool\s*:\s*([a-zA-Z, \t]+)\]\]", RegexOptions.IgnoreCase)` — Regex for additional options
- L193-260 _public ctor_ `public SourceFile(FileReference Location, TextBuffer Text, SourceFileFlags Flags)` — Construct a SourceFile from the given arguments
- L267-270 _public method_ `public void LogVerbose(string Format, params object[] Args)` — Appends to the per-file log
- L277-295 _public method_ `public void SetCounterpart(SourceFile OtherFile)` — Sets the counterpart on a file, and checks that it meets the requirements for doing so
- L303-312 _private* method_ `static bool SkipPragmaOnce(PreprocessorMarkup[] Markup, ref int BodyMinIdx)` — Checks whether the markup matches a #pragma once directive
- L321-365 _private* method_ `static bool SkipHeaderGuard(PreprocessorMarkup[] Markup, ref int BodyMinIdx, ref int BodyMaxIdx)` — Checks whether the markup matches a C-style header guard
- L371-376 _public method_ `public List<SourceFragment> FindIncludedFragments()` — Build a flat list of fragments included by this file
- L384-403 _public method_ `public void FindIncludedFragments(List<SourceFragment> IncludedFragments, List<Tuple<int, SourceFile>> IncludeStackChanges, HashSet<SourceFile> UniqueIncludedFiles)` — Build a flat list of included fragments
- L408-411 _public property_ `public bool HasHeaderGuard { get; }` — Whether the file has a header guard that prevents it being included more than once in a single translation unit
- L419-601 _public method_ `public void Write(IEnumerable<DirectoryReference> IncludePaths, IEnumerable<DirectoryReference> SystemIncludePaths, TextWriter Writer, bool bRemoveForwardDeclarations, LineBasedTextWriter Log)` — Write out an optimized file to the given location
- L608-626 _private* method_ `int GetForwardDeclarationSortKey(string ForwardDeclaration)` — Returns a sort key for the type of forward declaration. Used to ensure a stable output.
- L633-644 _private* method_ `string GetIndent(int MarkupIdx)` — Returns the whitespace indent for the markup at the given index
- L653-660 _private* method_ `static IEnumerable<Token> TokenizeLine(string FileName, TextBuffer Text, int LineIdx)` — Split the given line into tokens
- L667-685 _private* method_ `static bool IsIdentifier(string Token)` — Tests whether the given token is an identifier
- L692-702 _private* method_ `static void WriteBlankLine(TextBuffer Text, ref TextLocation LastLocation, TextWriter Writer)` — Writes a blank line, if the previous line is not already a blank line
- L711-719 _private* method_ `static void WriteLines(TextBuffer Text, TextLocation Location, TextLocation EndLocation, TextWriter Writer)` — Copies a sequence of lines into an output writer
- L729-738 _public method_ `public static string FormatInclude(DirectoryReference FromDirectory, FileReference IncludeFile, IEnumerable<DirectoryReference> IncludePaths, IEnumerable<DirectoryReference> SystemIncludePaths, LineBasedTextWriter Log)` — Format an include of the given file
- L748-818 _public method_ `public static bool TryFormatInclude(DirectoryReference FromDirectory, FileReference IncludeFile, IEnumerable<DirectoryReference> IncludePaths, IEnumerable<DirectoryReference> SystemIncludePaths, out string IncludeText)` — Format an include of the given file
- L824-827 _public method_ `public override string ToString()` — Converts a source file to a string for debugging

### `Source/Programs/IncludeTool/IncludeTool/SourceFragment.cs` (IncludeTool)


#### class `IncludeTool.SourceFragment`  
`class SourceFragment`  
_internal*; L18-226_
- attrs: `[Serializable]`
- desc: Represents an fragment of a source file consisting of a sequence of includes followed by some arbitrary directives or source code.
- L23 _public field_ `public SourceFile File` — The file that this fragment is part of
- L28 _public field_ `public int MarkupMin` — Index into the file's markup array of the start of this fragment (inclusive)
- L33 _public field_ `public int MarkupMax` — Index into the file's markup array of the end of this fragment (exclusive). Set to zero for external files.
- L38 _public field_ `public string UniqueName` — Unique name assigned to this fragment.
- L43 _public field_ `public FileReference Location` — Location of this fragment on disk. May be the original file in the case the single fragment for an external file, or a written out extract corresponding to the markup range.
- L48 _public field_ `public HashSet<SourceFragment> Dependencies` — Set of fragments which this fragment is dependent on
- L53 _public field_ `public Dictionary<Symbol, SymbolReferenceType> ReferencedSymbols` — All the imported symbols for this fragment
- L53 _public field_ `public Dictionary< ReferencedSymbols` — All the imported symbols for this fragment
- L58 _public field_ `public string Digest` — SHA1 digest of this fragment's text on disk
- L66-71 _public ctor_ `public SourceFragment(SourceFile File, int MarkupMin, int MarkupMax)` — Constructor
- L77-82 _public method_ `public List<SourceFragment> FindIncludedFragments()` — Find a flat list of fragments included by this file
- L90-111 _public method_ `public void FindIncludedFragments(List<SourceFragment> IncludedFragments, List<Tuple<int, SourceFile>> IncludeStackChanges, HashSet<SourceFile> UniqueIncludedFiles)` — Find all the fragments included by this fragment, including the current one
- L116-119 _public property_ `public TextLocation MinLocation { get; }` — The text location of the start of this fragment
- L124-127 _public property_ `public TextLocation MaxLocation { get; }` — The text location of the end of this fragment
- L133-170 _public method_ `public void Write(TextWriter Writer)` — Writes this fragment to a file
- L179-187 _private* method_ `static void WriteLines(TextWriter Writer, TextBuffer Text, TextLocation Location, TextLocation EndLocation)` — Utility function to write out a portion of a TextBuffer to a TextWriter
- L196-205 _private* method_ `static void WriteLinesCommented(TextWriter Writer, TextBuffer Text, TextLocation Location, TextLocation EndLocation)` — Utility function to write out a portion of a TextBuffer to a TextWriter as comments
- L211-225 _public method_ `public override string ToString()` — Summarize this fragment for the debugger

### `Source/Programs/IncludeTool/IncludeTool/Support/BinarySerializer.cs` (IncludeTool)


#### class `IncludeTool.Support.BinarySerializer`  
`static class BinarySerializer`  
_internal*; L17-398_
- desc: Fast, forward-only binary serializer which can handle arbitrary object hierarchies (including circular references).
- L22 _private* field_ `static Dictionary<Type, FieldInfo[]> AllFieldsMap = ...` — Cached lookup of type to field array for serialized types
- L22 _private* field_ `static Dictionary< AllFieldsMap = new Dictionary<Type, FieldInfo[]>()` — Cached lookup of type to field array for serialized types
- L29-35 _public method_ `public static void Serialize(object RootObject, string FileName)` — Serialize an object hierarchy to a file, starting at the given root object
- L42-50 _public method_ `public static void Serialize(object RootObject, Stream OutputStream)` — Serialize an object hierarchy to a stream, starting at the given root object
- L57-63 _public method_ `public static object Deserialize(string FileName)` — Deserialize an object hierarchy from the given file
- L70-78 _public method_ `public static object Deserialize(Stream InputStream)` — Deserialize an object hierarchy from the given stream
- L88-129 _private* method_ `static void SerializeInstance(object ThisObject, HashList<Type> Types, HashList<object> Instances, BinaryWriter Writer)` — Serialize an object instance to a BinaryWriter
- L138-188 _private* method_ `static object DeserializeInstance(List<Type> Types, List<object> Instances, BinaryReader Reader)` — Deserialize an object instance from a binary stream.
- L198-205 _private* method_ `static void SerializeObjectFields(object Instance, FieldInfo[] Fields, HashList<Type> Types, HashList<object> Instances, BinaryWriter Writer)` — Serialize fields within an object instance
- L215-222 _private* method_ `static void DeserializeObjectFields(object Instance, FieldInfo[] Fields, List<Type> Types, List<object> Instances, BinaryReader Reader)` — Deserialize fields into an object instance
- L232-279 _private* method_ `static void SerializeElement(Type ElementType, object ElementValue, HashList<Type> Types, HashList<object> Instances, BinaryWriter Writer)` — Serialize a single value or array element
- L290-335 _private* method_ `static object DeserializeElement(Type ElementType, List<Type> Types, List<object> Instances, BinaryReader Reader)` — Deserialize a single value or array element
- L342-359 _private* method_ `static IEnumerable<int[]> EnumerateArrayIndices(Array ThisArrayObject)` — Enumerate all the indices of an array, regardless of its rank.
- L366-375 _private* method_ `static FieldInfo[] FindAllFields(Type InType)` — Gets an array of serialized fields for the given type
- L382-397 _private* method_ `static FieldInfo[] FindAllFieldsUncached(Type InType)` — Gets an array of serialized fields for the given type, without using the field cache

### `Source/Programs/IncludeTool/IncludeTool/Support/BufferedTextWriter.cs` (IncludeTool)


#### class `IncludeTool.Support.BufferedTextWriter`  
`class BufferedTextWriter : LineBasedTextWriter`  
_internal*; L15-75_
- inherits: `LineBasedTextWriter`
- desc: Implementation of a TextWriter which buffers characters written to it, and can be copied to another TextWriter at a later time.
- L20 _private* field_ `List<string> Lines = new List<string>()` — List of buffered lines
- L25-27 _public ctor_ `public BufferedTextWriter()` — Default constructor
- L33-36 _public ctor_ `public BufferedTextWriter(string[] InLines)` — Construct a BufferedTextWriter with the given initial array of lines
- L41-44 _public method_ `public void Clear()` — Clear out the contents of the buffer
- L50-56 _public method_ `public void CopyTo(LineBasedTextWriter Other, string Prefix)` — Copies the current contents of the BufferedTextWriter to another TextWriter
- L62-65 _public method_ `public override void WriteLine(string Line)` — Write a single character to the buffer
- L71-74 _public method_ `public override string ToString()` — Returns the current buffered contents of the TextWriter as a string

### `Source/Programs/IncludeTool/IncludeTool/Support/CommandLine.cs` (IncludeTool)


#### class `IncludeTool.Support.CommandLineOptionAttribute`  
`public class CommandLineOptionAttribute : Attribute`  
_public; L16-32_
- inherits: `Attribute`
- desc: Attribute to markup fields which can be set by command line argument
- L21 _public field_ `public string Name` — The argument name. Uses the field name if not set.
- L26 _public field_ `public bool IsRequired` — If set, marks that the argument is required.
- L31 _public field_ `public char Separator` — For multi-value fields, indicates a separator character between arguments

#### class `IncludeTool.Support.CommandLine`  
`static class CommandLine`  
_internal*; L37-161_
- desc: Utility functions for parsing command line options
- L45-160 _public method_ `public static bool Parse(string[] Args, object Options)` — Parse the options from the given command line into the given options, using CommandLineOption attributes.

### `Source/Programs/IncludeTool/IncludeTool/Support/HashList.cs` (IncludeTool)


#### class `IncludeTool.Support.HashList`  
`class HashList<T> : IList<T>, ICollection<T>, IReadOnlyList<T>, IReadOnlyCollection<T>, IEnumerable<T>`  
_internal*; L20-260_
- attrs: `[Serializable] [DebuggerDisplay("Count = {Count}")] [DebuggerTypeProxy("System.Collections.Generic.Mscorlib_CollectionDebugView'1, mscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089")]`
- inherits: `IList<T>, ICollection<T>, IReadOnlyList<T>, IReadOnlyCollection<T>, IEnumerable<T>`
- desc: Implements an ordered list of unique elements which can quickly be queried for the existence and index of an existing item
- L25 _private* field_ `List<T> Items = new List<T>()` — Ordered list of items
- L30 _private* field_ `Dictionary<T, int> ItemToIndex = ...` — Map from element to its index
- L30 _private* field_ `Dictionary< ItemToIndex = new Dictionary<T, int>()` — Map from element to its index
- L35-37 _public ctor_ `public HashList()` — Construct an empty HashList
- L43-49 _public ctor_ `public HashList(IEnumerable<T> Collection)` — Construct a HashList from the given input collection
- L54-57 _public property_ `public int Count { get; }` — The number of elements in the collection
- L64-76 _public indexer_ `public T this[int Index] { get; set; }` — Get or set an element at the given index. Throws an exception if the item already exists.
- L81-84 _public property_ `public bool IsReadOnly { get; }` — Returns false.
- L89-93 _public method_ `public void Clear()` — Clear the list of items.
- L99-102 _private* method_ `void ICollection<T>.Add(T Item)` — Adds an item to the end of the list
- L108-117 _public method_ `public bool Add(T Item)` — Add an item to the end of the list
- L124-130 _public method_ `public void Insert(int Index, T Item)` — Insert an item at the given index
- L137-146 _public method_ `public bool Remove(T Item)` — Removes the given item from the container
- L152-156 _public method_ `public void RemoveAt(int Index)` — Removes an item at the given index
- L162-172 _public method_ `public void RemoveWhere(Predicate<T> Predicate)` — Remove all items matching a predicate
- L178-185 _private* method_ `void RenumberAfter(int FirstIndex)` — Renumber all the elements at the given index or above. Required after reordering the item list.
- L192-195 _public method_ `public bool Contains(T Item)` — Checks whether a given item belongs to the container
- L202-210 _public method_ `public int IndexOf(T Item)` — Gets the index of the given item.
- L216-219 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — Gets an ordered enumerator of the containers contents.
- L225-228 _public method_ `public IEnumerator<T> GetEnumerator()` — Gets an ordered enumerator of the containers contents.
- L234-240 _public method_ `public void UnionWith(IEnumerable<T> Items)` — Add all the given items into the list
- L246-249 _public method_ `public T[] ToArray()` — Converts the list to an array.
- L256-259 _public method_ `public void CopyTo(T[] TargetArray, int TargetIndex)` — Copy the container to an array

### `Source/Programs/IncludeTool/IncludeTool/Support/JsonWriter.cs` (IncludeTool)


#### class `IncludeTool.Support.JsonWriter`  
`public class JsonWriter : IDisposable`  
_public; L12-226_
- inherits: `IDisposable`
- L14 _private* field_ `StreamWriter Writer`
- L15 _private* field_ `bool bRequiresComma`
- L16 _private* field_ `string Indent`
- L18-22 _public ctor_ `public JsonWriter(string FileName)`
- L24-27 _public method_ `public void Dispose()`
- L29-38 _public method_ `public void WriteObjectStart()`
- L40-49 _public method_ `public void WriteObjectStart(string ObjectName)`
- L51-60 _public method_ `public void WriteObjectEnd()`
- L62-70 _public method_ `public void WriteArray(string ArrayName, IEnumerable<string> Values)`
- L72-80 _public method_ `public void WriteArray(string ArrayName, IEnumerable<int> Values)`
- L82-91 _public method_ `public void WriteArrayStart(string ArrayName)`
- L93-101 _public method_ `public void WriteArrayEnd()`
- L103-111 _public method_ `public void WriteValue(string Value)`
- L113-118 _public method_ `public void WriteValue(int Value)`
- L120-125 _public method_ `public void WriteValue(double Value)`
- L127-132 _public method_ `public void WriteValue(bool Value)`
- L134-142 _public method_ `public void WriteValue(string Name, string Value)`
- L144-147 _public method_ `public void WriteValue(string Name, int Value)`
- L149-152 _public method_ `public void WriteValue(string Name, double Value)`
- L154-157 _public method_ `public void WriteValue(string Name, bool Value)`
- L159-169 _private* method_ `void WriteCommaNewline()`
- L171-178 _private* method_ `void WriteValueInternal(string Name, string Value)`
- L180-225 _private* method_ `void WriteEscapedString(string Value)`

### `Source/Programs/IncludeTool/IncludeTool/Support/LineBasedTextWriter.cs` (IncludeTool)


#### class `IncludeTool.Support.LineBasedTextWriter`  
`abstract class LineBasedTextWriter`  
_internal*; L15-40_
- desc: Implements similar functionality to TextWriter, but outputs an entire line at a time. Used as a base class for logging.
- L17 _public method_ `public abstract void WriteLine(string Text)`
- L19-22 _public method_ `public void WriteLine()`
- L24-27 _public method_ `public void WriteLine(string Format, params object[] Args)`
- L29 _public method_ `public void WriteWarning(FileReference File, string Message)`
- L32 _public method_ `public void WriteWarning(FileReference File, int LineNumber, string Message)`
- L35 _public method_ `public void WriteWarning(FileReference File, string Message, params object[] Args)`
- L38 _public method_ `public void WriteWarning(FileReference File, int LineNumber, string Message, params object[] Args)`

### `Source/Programs/IncludeTool/IncludeTool/Support/LineBasedTextWriterWrapper.cs` (IncludeTool)


#### class `IncludeTool.Support.LineBasedTextWriterWrapper`  
`class LineBasedTextWriterWrapper : LineBasedTextWriter`  
_internal*; L16-29_
- inherits: `LineBasedTextWriter`
- desc: Implementation of LineBasedTextWriter which forwards data to a TextWriter instance.
- L18 _private* field_ `TextWriter Inner`
- L20-23 _public ctor_ `public LineBasedTextWriterWrapper(TextWriter Inner)`
- L25-28 _public method_ `public override void WriteLine(string Line)`

### `Source/Programs/IncludeTool/IncludeTool/Support/LogWriter.cs` (IncludeTool)


#### class `IncludeTool.Support.LogWriter`  
`class LogWriter : LineBasedTextWriter, IDisposable`  
_internal*; L15-53_
- inherits: `LineBasedTextWriter, IDisposable`
- desc: Provides for writing log messages to a log file and the display, as well as setting status messages
- L20 _private* field_ `StreamWriter FileWriter` — Output stream for log text
- L26-30 _public ctor_ `public LogWriter(string FileName)` — Construct a log writer backed by the given file
- L35-42 _public method_ `public void Dispose()` — Dispose of the current object, and its resources
- L48-52 _public method_ `public override void WriteLine(string Text)` — Writes a character to the output stream

### `Source/Programs/IncludeTool/IncludeTool/Support/ManagedTask.cs` (IncludeTool)


#### class `IncludeTool.Support.ManagedTask`  
`abstract class ManagedTask : IDisposable`  
_internal*; L18-143_
- inherits: `IDisposable`
- desc: Base class for a managed task, which may be executed as a thread or in a separate process
- L23 _private* field_ `ManualResetEvent FinishedEvent` — Event which is set when the task completes
- L28 _private* field_ `BufferedTextWriter BufferedWriter = new BufferedTextWriter()` — Output from the task
- L33-35 _protected ctor_ `protected ManagedTask()` — Constructor
- L40-43 _public method_ `public void Dispose()` — Disposes of the task
- L48-53 _public method_ `public void Start()` — Start the task
- L60 _protected method_ `protected abstract void InternalStart(ManualResetEvent FinishedEvent, LineBasedTextWriter Writer)` — When implemented by a derived class, implements the starting of the task
- L67-80 _public method_ `public int Join(LineBasedTextWriter Writer)` — Waits for the task to complete and returns
- L86 _protected method_ `protected abstract int InternalJoin()` — When implemented by a derived class, implements joining with the calling thread
- L91-102 _public method_ `public void Abort()` — Abort the task
- L107 _protected method_ `protected abstract void InternalAbort()` — When implemented by a derived class, aborts the running task.
- L115-142 _public method_ `public static int WaitForAny(ManagedTask[] Tasks, int TimeoutMilliseconds)` — Waits for any of the given tasks to complete

#### class `IncludeTool.Support.ManagedTaskThread`  
`class ManagedTaskThread : ManagedTask`  
_internal*; L148-220_
- inherits: `ManagedTask`
- desc: Implements a managed task using another thread
- L153 _private* field_ `Thread Worker` — The worker thread instance
- L158 _private* field_ `Func<LineBasedTextWriter, int> Action` — The action to execute
- L158 _private* field_ `Func< Action` — The action to execute
- L163 _private* field_ `int Result` — Stores the result of executing the action
- L169-172 _public ctor_ `public ManagedTaskThread(Func<LineBasedTextWriter, int> Action)` — Construct a managed task thread
- L179-183 _protected method_ `protected override void InternalStart(ManualResetEvent Event, LineBasedTextWriter Writer)` — Overridden from ManagedTask. Executes the given action.
- L189-194 _protected method_ `protected override int InternalJoin()` — Overridden from ManagedTask. Waits for the task to complete.
- L199-208 _protected method_ `protected override void InternalAbort()` — Aborts the running task
- L215-219 _private* method_ `void ExecuteAction(ManualResetEvent Event, LineBasedTextWriter Writer)` — Internal callback to execute the action

#### class `IncludeTool.Support.ManagedTaskProcess`  
`class ManagedTaskProcess : ManagedTask`  
_internal*; L225-305_
- inherits: `ManagedTask`
- desc: Implements a managed task using a separate process
- L230 _private* field_ `string FileName` — Executable to run
- L235 _private* field_ `string Arguments` — Arguments for the child process
- L240 _private* field_ `Process InnerProcess` — The process object
- L247-251 _public ctor_ `public ManagedTaskProcess(string FileName, string Arguments)` — Constructor
- L258-280 _protected method_ `protected override void InternalStart(ManualResetEvent Event, LineBasedTextWriter Writer)` — Overridden from ManagedTask. Executes the given action.
- L286-293 _protected method_ `protected override int InternalJoin()` — Overridden from ManagedTask. Waits for the task to complete.
- L298-304 _protected method_ `protected override void InternalAbort()` — Aborts the running task

### `Source/Programs/IncludeTool/IncludeTool/Support/MultiValueDictionary.cs` (IncludeTool)


#### class `IncludeTool.Support.MultiValueDictionary`  
`public class MultiValueDictionary<TKey, TValue> : IDictionary<TKey, IReadOnlyCollection<TValue>>, IReadOnlyDictionary<TKey, IReadOnlyCollection<TValue>>, IEnumerable<KeyValuePair<TKey, TValue>>`  
_public; L21-467_
- attrs: `[Serializable] [DebuggerDisplay("Count = {Count}")] [DebuggerTypeProxy(typeof(MultiValueDictionary<,>.DebuggerProxy))]`
- inherits: `IDictionary<TKey, IReadOnlyCollection<TValue>>, IReadOnlyDictionary<TKey, IReadOnlyCollection<TValue>>, IEnumerable<KeyValuePair<TKey, TValue>>`
- desc: Implements an unordered mapping from a key to a number of different values
- L112 _private* field_ `Dictionary<TKey, ValueSet> Contents` — The base mapping of key to set of values
- L112 _private* field_ `Dictionary< Contents` — The base mapping of key to set of values
- L117 _private* field_ `IEqualityComparer<TValue> ValueComparer` — The default value comparer
- L122-125 _public ctor_ `public MultiValueDictionary()` — Default constructor
- L131-134 _public ctor_ `public MultiValueDictionary(IEqualityComparer<TKey> KeyComparer)` — Construct a multi-value dictionary with the given key comparison class
- L141-145 _public ctor_ `public MultiValueDictionary(IEqualityComparer<TKey> KeyComparer, IEqualityComparer<TValue> ValueComparer)` — Construct a multi-value dictionary with the given key and value comparison class
- L151-154 _public property_ `public bool IsReadOnly { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — Always returns false.
- L160-163 _public property_ `public int Count { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — The number of keys in the container.
- L168-171 _public property_ `public ICollection<TKey> Keys { get; }` — The unique keys in the container.
- L177-180 _private* property_ `IEnumerable<TKey> IReadOnlyDictionary<TKey, IReadOnlyCollection<TValue>>.Keys { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — The unique keys in the container
- L185-188 _public property_ `public ICollection<IReadOnlyCollection<TValue>> Values { get; }` — The values in the dictionary.
- L194-197 _private* property_ `IEnumerable<IReadOnlyCollection<TValue>> IReadOnlyDictionary<TKey, IReadOnlyCollection<TValue>>.Values { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — The values in the container
- L204-214 _public method_ `public IEnumerable<TValue> WithKey(TKey Key)` — Enumerates all the values matching the given key. Does not fail if the key doesn't exist.
- L221-225 _public indexer_ `public IReadOnlyCollection<TValue> this[TKey Key] { get; set; }` — Allows retrieval of a set of values for each key. Throws an exception if the key does not exist.
- L230-233 _public method_ `public void Clear()` — Clears the dictionary
- L241-250 _public method_ `public bool Add(TKey Key, TValue Value)` — Adds a key with the given value
- L258-261 _public method_ `public void Add(TKey Key, IEnumerable<TValue> Values)` — Adds a key with the given values
- L269-272 _private* method_ `void IDictionary<TKey, IReadOnlyCollection<TValue>>.Add(TKey Key, IReadOnlyCollection<TValue> Values)` — Adds a key with the given values
- L278-281 _private* method_ `void ICollection<KeyValuePair<TKey, IReadOnlyCollection<TValue>>>.Add(KeyValuePair<TKey, IReadOnlyCollection<TValue>> Pair)` — Adds a key/value pair
- L289-304 _public method_ `public bool Remove(TKey Key, TValue Value)` — Removes a key/value pair from the dictionary
- L311-314 _public method_ `public bool Remove(TKey Key)` — Remove all values associated with a key
- L321-325 _private* method_ `bool ICollection<KeyValuePair<TKey, IReadOnlyCollection<TValue>>>.Remove(KeyValuePair<TKey, IReadOnlyCollection<TValue>> Pair)` — Remove a given key/value pair from the collection
- L333-337 _public method_ `public bool Contains(TKey Key, TValue Value)` — Checks whether the given key/value pair exists in the container
- L344-348 _private* method_ `bool ICollection<KeyValuePair<TKey, IReadOnlyCollection<TValue>>>.Contains(KeyValuePair<TKey, IReadOnlyCollection<TValue>> Pair)` — Checks whether the given key/value pair exists in the container
- L355-358 _public method_ `public bool ContainsKey(TKey Key)` — Checks whether the given key exists in the container
- L366-369 _private* method_ `bool IDictionary<TKey, IReadOnlyCollection<TValue>>.TryGetValue(TKey Key, out IReadOnlyCollection<TValue> Values)` — Tries to get the collection of values for the given key
- L377-380 _private* method_ `bool IReadOnlyDictionary<TKey, IReadOnlyCollection<TValue>>.TryGetValue(TKey Key, out IReadOnlyCollection<TValue> Values)` — Tries to get the collection of values for the given key
- L388-401 _public method_ `public bool TryGetValues(TKey Key, out IReadOnlyCollection<TValue> Values)` — Tries to get the collection of values for the given key
- L408-417 _public method_ `public void CopyTo(KeyValuePair<TKey, TValue>[] Array, int ArrayIndex)` — Copy the key/value pairs to an array
- L424-430 _private* method_ `void ICollection<KeyValuePair<TKey, IReadOnlyCollection<TValue>>>.CopyTo(KeyValuePair<TKey, IReadOnlyCollection<TValue>>[] Array, int ArrayIndex)` — Copies the contents of this dictionary to an array of key/collection pairs
- L436-445 _public method_ `public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()` — Gets an enumerator for the collection
- L451-457 _private* method_ `IEnumerator<KeyValuePair<TKey, IReadOnlyCollection<TValue>>> IEnumerable<KeyValuePair<TKey, IReadOnlyCollection<TValue>>>.GetEnumerator()` — Gets an enumerator for the collection
- L463-466 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — Gets an enumerator for the collection

#### class `IncludeTool.Support.MultiValueDictionary.ValueSet`  
`class ValueSet : HashSet<TValue>, IReadOnlyCollection<TValue>`  
_private*; L26-42_
- inherits: `HashSet<TValue>, IReadOnlyCollection<TValue>`
- desc: Helper class which adds the IReadOnlyCollection interface to HashSet
- L31-33 _public ctor_ `public ValueSet(IEqualityComparer<TValue> ValueComparer) : base(ValueComparer)` — Default constructor
- L39-41 _public ctor_ `public ValueSet(IEnumerable<TValue> Values, IEqualityComparer<TValue> ValueComparer) : base(Values, ValueComparer)` — Construct a value set from a sequence of values

#### class `IncludeTool.Support.MultiValueDictionary.DebuggerProxyItem`  
`public class DebuggerProxyItem`  
_public; L47-77_
- desc: Item to display in the debugger
- L52 _public field_ `public TKey Key` — The item key
- L58 _public field_ `public TValue[] Values` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]` — The item values, displayed as an inline list
- L63-67 _public ctor_ `public DebuggerProxyItem(TKey InKey, IEnumerable<TValue> InValues)` — Construct a proxy item
- L73-76 _public method_ `public override string ToString()` — Get the summary string to display for this item

#### class `IncludeTool.Support.MultiValueDictionary.DebuggerProxy`  
`class DebuggerProxy`  
_private*; L82-107_
- desc: Helper class to allow the container to be visualized as an array
- L88-96 _public ctor_ `public DebuggerProxy(IEnumerable<KeyValuePair<TKey, IReadOnlyCollection<TValue>>> Dictionary)` — Construct a proxy from a dictionary
- L102-106 _public property_ `public DebuggerProxyItem[] Items { get; set; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]` — Return the items to display in the debugger.

### `Source/Programs/IncludeTool/IncludeTool/Support/TextBuffer.cs` (IncludeTool)


#### struct `IncludeTool.Support.TextLocation`  
`struct TextLocation`  
_internal*; L16-117_
- attrs: `[Serializable]`
- desc: The line/column of a character in a text file
- L21 _public field_ `public int LineIdx` — The zero-based line index
- L26 _public field_ `public int ColumnIdx` — The zero-based column index
- L31-34 _public property_ `public static TextLocation Origin { get; }` — Property for the start of any text document
- L41-45 _public ctor_ `public TextLocation(int InLineIdx, int InColumnIdx)` — Construct a text location from the given line and column index
- L51-54 _public method_ `public TextLocation GetStartOfNextLine()` — Gets a text location representing the start of next line
- L62-65 _public operator_ `public static bool operator <(TextLocation A, TextLocation B)` — Checks if one TextLocation object is before another
- L73-76 _public operator_ `public static bool operator <=(TextLocation A, TextLocation B)` — Checks if one TextLocation object is before or equal to another
- L84-87 _public operator_ `public static bool operator >(TextLocation A, TextLocation B)` — Checks if one TextLocation object is after another
- L95-98 _public operator_ `public static bool operator >=(TextLocation A, TextLocation B)` — Checks if one TextLocation object is after or equal to another
- L104-107 _public method_ `public string GetSuffixForIDE()` — Formats a TextLocation as a string as displayed in an IDE, in parentheses with line and column indices starting at one.
- L113-116 _public method_ `public override string ToString()` — Returns the zero-based line/column

#### class `IncludeTool.Support.TextBuffer`  
`class TextBuffer`  
_internal*; L123-382_
- attrs: `[Serializable]`
- desc: Contains the contents of a text file, as an array of lines
- L128 _public field_ `public readonly string[] Lines` — The lines in the file
- L134-137 _public ctor_ `public TextBuffer(string[] InLines)` — Constructor
- L144-147 _public method_ `public static TextBuffer FromFile(string InFileName)` — Read a text file from a file
- L154-157 _public method_ `public static TextBuffer FromString(string Text)` — Construct a text buffer from a string
- L162-165 _public property_ `public TextLocation Start { get; }` — Property for the start of the text file
- L170-173 _public property_ `public TextLocation End { get; }` — Property for the end of the text file. This is one character beyond the last character in the file.
- L183-211 _public method_ `public string ExtractString(int BeginLineIdx, int BeginColumnIdx, int EndLineIdx, int EndColumnIdx)` — Extract a portion of the file as a string
- L221-253 _public method_ `public string[] Extract(int BeginLineIdx, int BeginColumnIdx, int EndLineIdx, int EndColumnIdx)` — Extract a portion of the file as an array of strings
- L261-264 _public method_ `public string[] Extract(TextLocation Begin, TextLocation End)` — Extract a portion of the file as an array of strings
- L271-284 _public indexer_ `public string this[int LineIdx] { get; }` — Access a single line within the file
- L292-309 _public indexer_ `public char this[int LineIdx, int ColumnIdx] { get; }` — Access a single character within the file, by line and column
- L316-319 _public indexer_ `public char this[TextLocation Location] { get; }` — Access a single character within the file
- L327-332 _public method_ `public char ReadCharacter(ref int LineIdx, ref int ColumnIdx)` — Reads a single character from a text buffer, and updates the current position
- L339-342 _public method_ `public char ReadCharacter(ref TextLocation Location)` — Reads a single character from a text buffer, and updates the current position
- L349-363 _public method_ `public bool MoveNext(ref int LineIdx, ref int ColumnIdx)` — Updates a line and column index to contain the index of the next character
- L369-372 _public method_ `public void MoveNext(ref TextLocation Location)` — Updates a location to point to the next character
- L378-381 _public method_ `public override string ToString()` — Converts the text file to a string for debugging

### `Source/Programs/IncludeTool/IncludeTool/Support/Utility.cs` (IncludeTool)


#### class `IncludeTool.Support.Utility`  
`static class Utility`  
_internal*; L17-348_
- L25-41 _public method_ `public static bool TryFindProgramInPath(string ProgramExe, out FileReference Location)` — Tries to find the given program executable in one of the PATH directories
- L48-51 _public method_ `public static string QuoteArgument(string Argument)` — Quotes an argument for passing on the command line, if necessary.
- L58-66 _public method_ `public static string FormatSHA(byte[] Hash)` — Formats a SHA digest as a string
- L73-77 _public method_ `public static string ComputeDigest(string Text)` — Computes the SHA1 digest for the given text
- L84-88 _public method_ `public static string ComputeDigest(FileReference FileLocation)` — Computes the SHA1 digest for the file at the given location
- L97-119 _public method_ `public static int Run(FileReference ExecutableFile, string Arguments, DirectoryReference WorkingDir, LineBasedTextWriter Log)` — Execute an external process, writing its output to the log.
- L128-136 _public method_ `public static void CopyExcerpt(TextBuffer Text, TextLocation Location, TextLocation EndLocation, TextWriter Writer)` — Copies a portion of the file to the given text writer
- L145-154 _public method_ `public static void CopyCommentedExcerpt(TextWriter Writer, TextBuffer Text, TextLocation Location, TextLocation EndLocation)` — Copies an excerpt from a file to a TextWriter, commenting each output line
- L161-189 _public method_ `public static string RemoveRelativePaths(string FileName)` — Remove relative path separators from a string, without normalizing slashes
- L263-266 _public method_ `public static void ParallelForWithStatus(string Message, int BeginValue, int EndValue, Action<int> Action, LineBasedTextWriter Log)` — Execute a Parallel.For loop, but output status messages showing progress every 5 seconds
- L276-284 _public method_ `public static void ParallelForWithStatus(string Message, int BeginValue, int EndValue, ParallelOptions Options, Action<int> Action, LineBasedTextWriter Log)` — Execute a Parallel.For loop, but output status messages showing progress every 5 seconds
- L289-321 _private method_ `private static string DetermineClangVersionDir(string ClangExecutable)` — Queries compiler for the version and returns string like "3.9.0" or such.
- L326-347 _public method_ `public static void GetSystemIncludeDirectories(CompileEnvironment CompileEnv, DirectoryReference InputDir, List<DirectoryReference> ExtraSystemIncludePaths)` — Gets include directories that the compiler knows about.

#### class `IncludeTool.Support.Utility.ParallelForState`  
`class ParallelForState`  
_private*; L194-253_
- desc: Helper class for maintaining the state of a parallel for loop, and outputting status update messages
- L199 _public field_ `public int CompletedCount` — The number of completed iterations
- L204 _public field_ `public Stopwatch Timer` — Timer for outputting messages
- L209 _public field_ `public TimeSpan NextUpdateTime` — The last UTC time that a status message was output
- L214-218 _public ctor_ `public ParallelForState()` — Constructor
- L226-241 _public method_ `public void Increment(int TotalCount, string Message, LineBasedTextWriter Log)` — Increment the number of iterations, and output a status update message if 5 seconds have elapsed
- L249-252 _public method_ `public void Complete(int TotalCount, string Message, LineBasedTextWriter Log)` — Print the last message showing 100%

### `Source/Programs/IncludeTool/IncludeTool/SymbolTable.cs` (IncludeTool)


#### enum `IncludeTool.SymbolType`  
`enum SymbolType`  
_internal*; L18-54_
- desc: Type of a defined symbol
- L23 _public* enumerator_ `Macro` — A macro definition
- L28 _public* enumerator_ `Class` — Class declaration
- L33 _public* enumerator_ `Struct` — Struct declaration
- L38 _public* enumerator_ `Enumeration` — Enum declaration
- L43 _public* enumerator_ `Typedef` — A typedef declaration
- L48 _public* enumerator_ `TemplateClass` — A template class declaration
- L53 _public* enumerator_ `TemplateStruct` — A template struct declaration

#### class `IncludeTool.Symbol`  
`class Symbol`  
_internal*; L60-112_
- attrs: `[Serializable]`
- desc: Represents a symbol name, scraped from a source fragment
- L65 _public field_ `public readonly string Name` — The symbol name
- L70 _public field_ `public readonly SymbolType Type` — Type of the symbol
- L75 _public field_ `public readonly string ForwardDeclaration` — Text for a forward declaration of this symbol
- L80 _public field_ `public readonly SourceFragment Fragment` — Fragment that this symbol is defined in
- L85 _public field_ `public readonly TextLocation Location` — The location within the file that this symbol is declared
- L95-102 _public ctor_ `public Symbol(string Name, SymbolType Type, string ForwardDeclaration, SourceFragment Fragment, TextLocation Location)` — Constructor
- L108-111 _public method_ `public override string ToString()` — Returns a string representation of the symbol for debugging purposes

#### enum `IncludeTool.SymbolReferenceType`  
`enum SymbolReferenceType`  
_internal*; L117-128_
- desc: The type of a symbol reference
- L122 _public* enumerator_ `Opaque` — The symbol is only referenced in an opaque manner (ie. via a pointer or reference), and can be forward-declared.
- L127 _public* enumerator_ `RequiresDefinition` — The symbol is referenced in some other way

#### class `IncludeTool.UnbalancedScopeException`  
`class UnbalancedScopeException : Exception`  
_internal*; L130-136_
- inherits: `Exception`
- L132-135 _public ctor_ `public UnbalancedScopeException(string Message) : base(Message)`

#### class `IncludeTool.SymbolTable`  
`class SymbolTable`  
_internal*; L141-1136_
- desc: Registry of symbol names to definitions
- L146 _private* field_ `MultiValueDictionary<string, Symbol> Lookup = ...` — Mapping of name to symbol definition
- L146 _private* field_ `MultiValueDictionary< Lookup = new MultiValueDictionary<string,Symbol>()` — Mapping of name to symbol definition
- L152-164 _public method_ `public void AddExports(SourceFile File)` — Add all the exported symbols from the given source file
- L171-196 _public method_ `public void PrintConflicts(DirectoryReference InputDir, LineBasedTextWriter Log)` — Prints all the symbols with conflicting definitions
- L204-284 _private* method_ `void ReadExportedSymbols(SourceFile File, ref int MarkupIdx, ref int Scope)` — Read all the exported symbol definitions from a file
- L292-322 _private* method_ `void ParseDeclarations(SourceFile File, SourceFragment Fragment, PreprocessorMarkup Markup, ref int Scope)` — Parse declarations from the reader
- L329-410 _private* method_ `bool ReadEnumClassHeader(TokenReader OriginalReader, SourceFragment Fragment)` — Parse an "enum class" declaration, and add a symbol for it
- L417-470 _private* method_ `bool ReadClassOrStructHeader(TokenReader OriginalReader, SourceFragment Fragment)` — Try to read a class or struct header
- L477-541 _private* method_ `bool ReadTypedefHeader(TokenReader OriginalReader, SourceFragment Fragment)` — Try to skip over a template header
- L548-642 _private* method_ `bool ReadTemplateClassOrStructHeader(TokenReader OriginalReader, SourceFragment Fragment)` — Try to read a template class or struct header
- L649-669 _private* method_ `bool SkipTemplateHeader(TokenReader OriginalReader)` — Try to skip over a template header
- L679-694 _private* method_ `Symbol AddSymbol(string Name, SymbolType Type, string ForwardDeclaration, SourceFragment Fragment, TextLocation Location)` — Adds a symbol to the lookup. If the symbol already exists and is marked as a different type, mark it as ambiguous.
- L702-711 _private* method_ `SourceFragment FindFragment(SourceFile File, int MarkupIdx)` — Find the fragment corresponding to a given markup index
- L719-737 _public method_ `public bool ReadForwardDeclarations(SourceFile HeaderFile, Dictionary<Symbol, SourceFile> SymbolToHeader, LineBasedTextWriter Log)` — Read all the forward declarations from a file
- L747-778 _private* method_ `bool ReadClassOrStructForwardDeclaration(TokenReader OriginalReader, SourceFile HeaderFile, Dictionary<Symbol, SourceFile> SymbolToHeader, LineBasedTextWriter Log)` — Parse the forward declaration of a class or struct
- L788-821 _private* method_ `bool ReadEnumClassForwardDeclaration(TokenReader OriginalReader, SourceFile HeaderFile, Dictionary<Symbol, SourceFile> SymbolToHeader, LineBasedTextWriter Log)` — Parse the forward declaration of an enum class
- L831-878 _private* method_ `bool ReadTemplateClassOrStructForwardDeclaration(TokenReader OriginalReader, SourceFile HeaderFile, Dictionary<Symbol, SourceFile> SymbolToHeader, LineBasedTextWriter Log)` — Parse the forward declaration of a template class or struct
- L886-913 _private* method_ `static bool SkipTemplateArguments(TokenReader Reader, ref bool bMoveNext)` — Skip past a template argument list
- L920-953 _private* method_ `bool SkipAliasDeclaration(TokenReader OriginalReader)` — Skip over the declaration of an alias
- L963-980 _private* method_ `void AddForwardDeclaration(SourceFile HeaderFile, string SymbolName, SymbolType Type, Dictionary<Symbol, SourceFile> SymbolToHeader, LineBasedTextWriter Log)` — Adds a forward declaration to a map
- L987-1006 _public method_ `public Dictionary<Symbol, SymbolReferenceType> FindReferences(SourceFragment Fragment)` — Finds all the imported symbols from the given fragment
- L1008-1106 _public method_ `public void FindReferences(TokenReader Reader, SourceFragment Fragment, Dictionary<Symbol, SymbolReferenceType> References)`
- L1115-1125 _private* method_ `static bool IgnoreSymbol(Symbol Symbol, SourceFragment Fragment, TextLocation Location)` — Determines whether a symbol reference should be ignored, because it's to an item defined above in the same file
- L1132-1135 _private* method_ `static bool IsSmartPointerClass(string Token)` — Heuristic to determine if the given token looks like the name of a smart pointer class

### `Source/Programs/IncludeTool/IncludeTool/Token.cs` (IncludeTool)


#### enum `IncludeTool.TokenFlags`  
`enum TokenFlags`  
_internal*; L16-32_
- attrs: `[Flags]`
- desc: Flags for a single token
- L21 _public* enumerator_ `None = 0x00` — No flags
- L26 _public* enumerator_ `HasLeadingSpace = 0x01` — The token has space before it
- L31 _public* enumerator_ `DisableExpansion = 0x02` — Do not replace any instances of this token with the corresponding macro.

#### enum `IncludeTool.TokenType`  
`enum TokenType`  
_internal*; L37-51_
- desc: Enumeration for token types
- L39 _public* enumerator_ `LeftParen`
- L40 _public* enumerator_ `RightParen`
- L41 _public* enumerator_ `Comma`
- L42 _public* enumerator_ `Identifier`
- L43 _public* enumerator_ `NumericLiteral`
- L44 _public* enumerator_ `StringLiteral`
- L45 _public* enumerator_ `CharacterLiteral`
- L46 _public* enumerator_ `Symbol`
- L47 _public* enumerator_ `StringOfTokens`
- L48 _public* enumerator_ `SystemInclude`
- L49 _public* enumerator_ `Placemarker`
- L50 _public* enumerator_ `Unknown`

#### struct `IncludeTool.Token`  
`struct Token`  
_internal*; L57-169_
- attrs: `[DebuggerDisplay("{Text}")]`
- desc: Single lexical token
- L62 _public field_ `public readonly string Text` — Contents of this token
- L67 _public field_ `public readonly TokenType Type` — The type of this token
- L72 _public field_ `public readonly TokenFlags Flags` — Properties of this token
- L77-82 _public ctor_ `public Token(string InText, TokenType InType, TokenFlags InFlags)` — Constructor
- L87-90 _public property_ `public bool HasLeadingSpace { get; }` — Accessor for whether this token has leading whitespace
- L97-100 _public method_ `public bool Is(string Token)` — Tests whether this token matches the given string
- L106-109 _public method_ `public bool IsString()` — Tests whether this token is a string
- L115-118 _public method_ `public bool IsSystemInclude()` — Tests whether this token represents a system includes, in angle brackets
- L125-148 _public method_ `public static string Format(IEnumerable<Token> Tokens)` — Concatenate a sequence of tokens into a string
- L156-168 _public method_ `public static Token Concatenate(Token FirstToken, Token SecondToken)` — Concatenate two tokens together

### `Source/Programs/IncludeTool/IncludeTool/TokenReader.cs` (IncludeTool)


#### enum `IncludeTool.TokenReaderContext`  
`enum TokenReaderContext`  
_internal*; L17-38_
- attrs: `[Flags]`
- desc: Flags to control the type of valid tokens read
- L22 _public* enumerator_ `Default = 0x0` — Allow any normal tokens
- L27 _public* enumerator_ `IncludeDirective = 0x01` — Allow system include tokens in this context
- L32 _public* enumerator_ `TokenString = 0x02` — An string of tokens suitable for the #error directive
- L37 _public* enumerator_ `IgnoreNewlines = 0x04` — Don't return newline tokens

#### class `IncludeTool.TokenException`  
`class TokenException : Exception`  
_internal*; L43-54_
- inherits: `Exception`
- desc: Exception thrown when an invalid token is encountered
- L45 _public property_ `public string FileName { get; }`
- L46 _public property_ `public TextLocation Location { get; }`
- L47 _public property_ `public string Description { get; }`
- L49-53 _public ctor_ `public TokenException(string FileName, TextLocation Location, string Description) : base($"{FileName}({Location.LineIdx + 1}): error: {Description}")`

#### class `IncludeTool.TokenReader`  
`class TokenReader : IEnumerator<Token>`  
_internal*; L59-590_
- inherits: `IEnumerator<Token>`
- desc: Tokenizer for C++ source files. Provides functions for navigating a source file skipping whitespace, comments, and so on when required.
- L64 _public property_ `public string FileName { get; }` — The current file
- L69 _private* field_ `TextBuffer Text` — The current text buffer being read from
- L74 _private* field_ `Token CurrentToken` — The current token
- L79 _private* field_ `TextLocation EndLocation` — The location at which to stop reading
- L85-88 _public ctor_ `public TokenReader(string FileName, string Text) : this(FileName, TextBuffer.FromString(Text), TextLocation.Origin)` — Constructor
- L95-98 _public ctor_ `public TokenReader(string FileName, TextBuffer Text, TextLocation Location) : this(FileName, Text, Location, Text.End)` — Constructor
- L106-114 _public ctor_ `public TokenReader(string FileName, TextBuffer Text, TextLocation Location, TextLocation EndLocation)` — Constructor
- L120-123 _public ctor_ `public TokenReader(TokenReader Other)` — Copy constructor
- L129-137 _public method_ `public void Set(TokenReader Other)` — Sets the state of this reader to the same as another reader
- L142-145 _public property_ `public Token Current { get; }` — Returns the current token
- L150-153 _public property_ `public int CurrentLine { get; }` — Returns the current line
- L158-161 _public property_ `public TextLocation TokenWhitespaceLocation { get; set; }` — Returns the start location of the whitespace before the current token
- L166-169 _public property_ `public TextLocation TokenLocation { get; set; }` — The location of the current token
- L174-177 _public property_ `public TextLocation TokenEndLocation { get; set; }` — The position at the end of the token
- L182-185 _private* property_ `object IEnumerator.Current { get; }` — Untyped implementation of Current for IEnumerator.
- L190-192 _private* method_ `void IDisposable.Dispose()` — Override of IEnumerator.Dispose. Not required.
- L198-201 _public method_ `public bool MoveNext()` — Move to the next token
- L208-231 _public method_ `public bool MoveNext(TokenReaderContext Context)` — Move to the next token
- L237-250 _public method_ `public bool MoveToNextLine()` — Move past the next token after a newline
- L255-258 _private* method_ `void IEnumerator.Reset()` — Definition of IEnumerator.Reset(). Not supported.
- L263 _private* field_ `static readonly string[] SymbolicTokens = { "==", "!=", "<=", ">=", "++", "--", "->", "::", "&&", "||", "##", "<<", ">>", "...", }` — List of multi-character symbolic tokens that we want to parse out
- L288-335 _private* method_ `static bool SkipWhitespace(TextBuffer Text, ref int LineIdx, ref int ColumnIdx, bool bIncludingNewlines)` — Advances the given position past any horizontal whitespace or comments
- L346-513 _private* method_ `static bool ReadToken(string FileName, TextBuffer Text, ref int LineIdx, ref int ColumnIdx, TokenFlags Flags, TokenReaderContext Context, out Token Result)` — Reads a single token from a text buffer
- L523-545 _private* method_ `static void SkipTextLiteral(string FileName, TextBuffer Text, ref int LineIdx, ref int ColumnIdx, char LastCharacter)` — Skip past a text literal (a quoted character literal or string literal)
- L554-589 _private* method_ `static void SkipRawStringLiteral(string FileName, TextBuffer Text, ref int LineIdx, ref int ColumnIdx)` — Skip past a text literal (a quoted character literal or string literal)

### `Source/Programs/IncludeTool/IncludeTool/Workspace.cs` (IncludeTool)


#### class `IncludeTool.WorkspaceFile`  
`class WorkspaceFile`  
_internal*; L21-97_
- desc: Represents a file in the workspace
- L26 _public field_ `public readonly FileReference Location` — Location of the file
- L31 _public field_ `public readonly WorkspaceDirectory Directory` — The directory containing this file
- L36 _public field_ `public readonly string NormalizedPathFromBranchRoot` — Lowercase path from the root of the branch
- L41 _private* field_ `SourceFile CachedSourceFile` — The cached source file corresponding to this file
- L48-57 _public ctor_ `public WorkspaceFile(string Name, WorkspaceDirectory Directory)` — Constructor
- L62-65 _public property_ `public WorkspaceDirectory ProjectDirectory { get; }` — The project directory containing this file
- L70-73 _public property_ `public SourceFile SourceFile { get; }` — Returns the cached source file object corresponding to this file. Call ReadSourceFile() to return this value, populating it if necessary.
- L79-87 _public method_ `public SourceFile ReadSourceFile()` — Returns
- L93-96 _public method_ `public override string ToString()` — Provide a string representation of this object for debugging

#### class `IncludeTool.WorkspaceDirectory`  
`class WorkspaceDirectory`  
_internal*; L102-320_
- desc: Caches the contents of a workspace directory
- L107 _public field_ `public readonly DirectoryReference Location` — The location of this directory
- L112 _public field_ `public readonly WorkspaceDirectory ParentDirectory` — The parent directory
- L117 _private* field_ `DirectoryInfo Info` — The directory info for this directory
- L122 _private* field_ `Dictionary<string, WorkspaceFile> NameToFile` — Files within this directory
- L122 _private* field_ `Dictionary< NameToFile` — Files within this directory
- L127 _private* field_ `Dictionary<string, WorkspaceDirectory> NameToDirectory` — Subdirectories within this directory
- L127 _private* field_ `Dictionary< NameToDirectory` — Subdirectories within this directory
- L134-144 _public ctor_ `public WorkspaceDirectory(DirectoryInfo Info)` — Construct a directory object with the given DirectoryInfo as the root
- L151-161 _private* ctor_ `WorkspaceDirectory(DirectoryInfo Info, WorkspaceDirectory ParentDirectory)` — Construct a directory object, as a child of the given parent directory
- L166-200 _public method_ `public void CacheFiles()` — Caches the contents of this directory
- L205-217 _public method_ `public void CacheDirectories()` — Caches the directories in this directory
- L225-229 _public method_ `public bool TryGetFile(string Name, out WorkspaceFile Result)` — Tries to get a file of the given name from this directory
- L237-254 _public method_ `public bool TryGetDirectory(string Name, out WorkspaceDirectory Result)` — Tries to get a directory of the given name from this directory
- L259-266 _public method_ `public void SetAsBranchRoot()` — Marks a directory as the root of a branch. This sets the NormalizedPathFromBranchRoot property to "/", and child directories will be updated with subpaths.
- L272-279 _public property_ `public IEnumerable<WorkspaceFile> Files { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — Returns the files within this directory
- L285-292 _public property_ `public IEnumerable<WorkspaceDirectory> Directories { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.Never)]` — Returns the child directories within this directory
- L297-301 _public property_ `public WorkspaceDirectory ProjectDirectory { get; set; }` — Gets the project directory corresponding to the current directory
- L306-310 _public property_ `public string NormalizedPathFromBranchRoot { get; set; }` — The normalized (ie. lowercase/invariant, separated by forward slashes, with a trailing slash) path of this directory from the branch root. Null if the path is outside the branch.
- L316-319 _public method_ `public override string ToString()` — Returns a string representation of this directory for debugging

#### class `IncludeTool.WorkspaceScanner`  
`class WorkspaceScanner`  
_internal*; L325-373_
- desc: Worker class to find files in the workspace
- L330 _private* field_ `WorkspaceDirectory Directory` — The current directory being searched
- L336-339 _public ctor_ `public WorkspaceScanner(WorkspaceDirectory Directory)` — Constructor
- L345-372 _public method_ `public void Run(ThreadPoolWorkQueue Queue)` — Callback from the thread pool worker

#### class `IncludeTool.WorkspaceReferenceScanner`  
`class WorkspaceReferenceScanner`  
_internal*; L378-432_
- desc: Worker class to find files in the workspace
- L383 _private* field_ `WorkspaceDirectory ParentDirectory` — The current directory being searched
- L388 _private* field_ `ConcurrentBag<WorkspaceFile> FoundFiles` — The set of files that have been found
- L395-399 _public ctor_ `public WorkspaceReferenceScanner(WorkspaceDirectory ParentDirectory, ConcurrentBag<WorkspaceFile> FoundFiles)` — Constructor
- L405-431 _public method_ `public void Run(ThreadPoolWorkQueue Queue)` — Callback from the thread pool worker

#### class `IncludeTool.Workspace`  
`static class Workspace`  
_internal*; L437-554_
- desc: Utility functions for finding files in the workspace
- L442-446 _public property_ `public static WorkspaceDirectory BranchRoot { get; set; }` — The branch root directory
- L451 _private* field_ `static ConcurrentDictionary<DirectoryReference, WorkspaceDirectory> RootDirectories = ...` — List of root directories to search in
- L451 _private* field_ `static ConcurrentDictionary< RootDirectories = new ConcurrentDictionary<DirectoryReference, WorkspaceDirectory>()` — List of root directories to search in
- L458-473 _public method_ `public static void SetBranchRoot(DirectoryReference Location)` — Sets the location of the branch root directory
- L479-485 _public method_ `public static void CacheFiles(WorkspaceDirectory Directory)` — Caches all the files under the given directory
- L492-504 _public method_ `public static WorkspaceFile GetFile(FileReference Location)` — Gets a WorkspaceFile object for the file at the given location. Throws an exception if the file does not exist.
- L511-519 _public method_ `public static WorkspaceDirectory GetDirectory(DirectoryReference Location)` — Gets a WorkspaceDirectory object representing the given location
- L527-553 _private* method_ `static bool TryGetDirectoryInternal(DirectoryInfo Info, out WorkspaceDirectory Result)` — Tries to get the path to a directory, recursively adding all the directories above it if necessary
