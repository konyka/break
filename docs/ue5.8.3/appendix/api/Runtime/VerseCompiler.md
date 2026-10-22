# Runtime / VerseCompiler

- module root: `Source/Runtime/VerseCompiler`
- headers: 78; symbols: 5112
- symbol kinds: class=222, enum=73, enumerator=320, externvar=3, function=2121, macro=64, member=1060, namespace=95, prototype=878, struct=151, typedef=71, union=4, variable=50
- PublicDependencyModuleNames: Core, uLangCore, uLangJSON

### `Source/Runtime/VerseCompiler/Private/uLang/SemanticAnalyzer/Desugarer.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L13 _prototype_ `TSRef<CAstProject> DesugarVstToAst(const Verse::Vst::Project& VstProject, CSymbolTable& Symbols, CDiagnostics& Diagnostics);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/ApiLayerInjections.h` (Public)


#### struct `uLang::SIntraSemInjectArgs`  
`struct SIntraSemInjectArgs`  
_L20-28_
- L22 _public function_ `SIntraSemInjectArgs(const TSRef<CSemanticProgram>& Program) : _Program(Program)`
- L25 _public member_ `const TSRef<CSemanticProgram>& _Program;`
- L27 _public member_ `ESemanticPass _InjectionPass = ESemanticPass::SemanticPass_Invalid;`

#### class `uLang::TApiLayerInjection`  
`template<class FeatureType, typename... InjectionArgsType> class TApiLayerInjection : public TModularFeature<FeatureType>`  
_L31-36_
- inherits: `TModularFeature<FeatureType>`
- L35 _public prototype_ `virtual bool Ingest(InjectionArgsType... Args, const SBuildContext& BuildContext) = 0;` — @return True to halt the toolchain from continuing to build -- NOTE: could be ignored (depending on current build settings).

#### class `uLang::IPreParseInjection`  
`class IPreParseInjection : public TApiLayerInjection<IPreParseInjection, const CUTF8StringView&>`  
_L38-38_
- inherits: `TApiLayerInjection<IPreParseInjection,constCUTF8StringView&>`
- L38 _private prototype_ `class IPreParseInjection : public TApiLayerInjection<IPreParseInjection, const CUTF8StringView&>`

#### class `uLang::IPostParseInjection`  
`class IPostParseInjection : public TApiLayerInjection<IPostParseInjection, const Verse::Vst::TNodeRef<Verse::Vst::Snippet>&>`  
_L39-39_
- inherits: `TApiLayerInjection<IPostParseInjection,constVerse::Vst::TNodeRef<Verse::Vst::Snippet>&>`
- L39 _private prototype_ `class IPostParseInjection : public TApiLayerInjection<IPostParseInjection, const Verse::Vst::TNodeRef<Verse::Vst::Snippet>&>`

#### class `uLang::IPreSemAnalysisInjection`  
`class IPreSemAnalysisInjection : public TApiLayerInjection<IPreSemAnalysisInjection, const Verse::Vst::TNodeRef<Verse::Vst::Project>&, const SProgramContext&>`  
_L40-40_
- inherits: `TApiLayerInjection<IPreSemAnalysisInjection,constVerse::Vst::TNodeRef<Verse::Vst::Project>&,constSProgramContext&>`
- L40 _private prototype_ `class IPreSemAnalysisInjection : public TApiLayerInjection<IPreSemAnalysisInjection, const Verse::Vst::TNodeRef<Verse::Vst::Project>&, const SProgramContext&>`

#### class `uLang::IIntraSemAnalysisInjection`  
`class IIntraSemAnalysisInjection : public TApiLayerInjection<IIntraSemAnalysisInjection, const SIntraSemInjectArgs&, const SProgramContext&>`  
_L41-41_
- inherits: `TApiLayerInjection<IIntraSemAnalysisInjection,constSIntraSemInjectArgs&,constSProgramContext&>`
- L41 _private prototype_ `class IIntraSemAnalysisInjection : public TApiLayerInjection<IIntraSemAnalysisInjection, const SIntraSemInjectArgs&, const SProgramContext&>`

#### class `uLang::IPostSemAnalysisInjection`  
`class IPostSemAnalysisInjection : public TApiLayerInjection<IPostSemAnalysisInjection, const TSRef<CSemanticProgram>&, const SProgramContext&>`  
_L42-42_
- inherits: `TApiLayerInjection<IPostSemAnalysisInjection,constTSRef<CSemanticProgram>&,constSProgramContext&>`
- L42 _private prototype_ `class IPostSemAnalysisInjection : public TApiLayerInjection<IPostSemAnalysisInjection, const TSRef<CSemanticProgram>&, const SProgramContext&>`

#### class `uLang::IPreTranslateInjection`  
`class IPreTranslateInjection : public TApiLayerInjection<IPreTranslateInjection, const TSRef<CSemanticProgram>&, const SProgramContext&>`  
_L43-43_
- inherits: `TApiLayerInjection<IPreTranslateInjection,constTSRef<CSemanticProgram>&,constSProgramContext&>`
- L43 _private prototype_ `class IPreTranslateInjection : public TApiLayerInjection<IPreTranslateInjection, const TSRef<CSemanticProgram>&, const SProgramContext&>`

#### class `uLang::IPreLinkInjection`  
`class IPreLinkInjection : public TApiLayerInjection<IPreLinkInjection, const SProgramContext&>`  
_L44-44_
- inherits: `TApiLayerInjection<IPreLinkInjection,constSProgramContext&>`
- L44 _private prototype_ `class IPreLinkInjection : public TApiLayerInjection<IPreLinkInjection, const SProgramContext&>`

#### class `uLang::IPostLinkInjection`  
`class IPostLinkInjection : public TApiLayerInjection<IPostLinkInjection, const SProgramContext&>`  
_L45-45_
- inherits: `TApiLayerInjection<IPostLinkInjection,constSProgramContext&>`
- L45 _private prototype_ `class IPostLinkInjection : public TApiLayerInjection<IPostLinkInjection, const SProgramContext&>`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L9 _namespace_ `namespace Vst` (scope `Verse`)
- L11 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/CompilerTypes.h` (Public)


#### struct `uLang::SToolchainInjections`  
`struct SToolchainInjections`  
_L15-25_
- desc: Collection of all injection types for the toolchain -- conveniently bundled up for portability.
- L17 _public member_ `TSRefArray<IPreParseInjection> _PreParseInjections;`
- L18 _public member_ `TSRefArray<IPostParseInjection> _PostParseInjections;`
- L19 _public member_ `TSRefArray<IPreSemAnalysisInjection> _PreSemAnalysisInjections;`
- L20 _public member_ `TSRefArray<IIntraSemAnalysisInjection> _IntraSemAnalysisInjections;`
- L21 _public member_ `TSRefArray<IPostSemAnalysisInjection> _PostSemAnalysisInjections;`
- L22 _public member_ `TSRefArray<IPreTranslateInjection> _PreTranslateInjections;`
- L23 _public member_ `TSRefArray<IPreLinkInjection> _PreLinkInjections;`
- L24 _public member_ `TSRefArray<IPostLinkInjection> _PostLinkInjections;`

#### struct `uLang::FSolFingerprint`  
`struct FSolFingerprint`  
_L30-68_
- desc: Abstraction for versioning objects used in compilation
- L32 _public member_ `alignas(uint32_t) uint8_t Bytes[20]{};`
- L33 _public member_ `static const FSolFingerprint Zero;`
- L35 _public function_ `void Reset()`
- L50 _public function_ `CUTF8String ToCUTF8String() const`
- L69 _member_ `inline const FSolFingerprint FSolFingerprint::Zero;`

#### struct `uLang::FSolFingerprintDiagnostics`  
`struct FSolFingerprintDiagnostics : public CSharedMix`  
_L71-74_
- inherits: `CSharedMix`
- L73 _public member_ `TArray<CUTF8String> _Updates;`

#### class `uLang::ISolFingerprintGenerator`  
`class ISolFingerprintGenerator : public CSharedMix`  
_L79-90_
- inherits: `CSharedMix`
- desc: Abstraction for generating fingerprints
- L82 _public prototype_ `virtual ~ISolFingerprintGenerator() = default;`
- L85 _public prototype_ `virtual void Reset() = 0;` — Clears existing generator state. Useful when re-using generators.
- L87 _public prototype_ `virtual void Update(const void* Data, uint64_t Size, const char* DebugContext = nullptr) = 0;` — Updates the generator state with a buffer of data to be used for fingerprint creation
- L89 _public prototype_ `virtual FSolFingerprint Finalize(const char* DebugContext = nullptr) = 0;` — Generates a fingerprint from the generators current state.

#### struct `uLang::SCommandLine`  
`struct SCommandLine`  
_L93-98_
- L95 _public member_ `TArray<CUTF8String> _Tokens;`
- L96 _public member_ `TArray<CUTF8String> _Switches;`
- L97 _public member_ `CUTF8String _Unparsed;`

#### struct `uLang::SPackageUsageEntry`  
`struct SPackageUsageEntry`  
_L101-105_
- desc: Per package, remember what dependencies it uses
- L103 _public member_ `CUTF8String _PackageName;`
- L104 _public member_ `TArray<CUTF8String> _UsedDependencies;` — Only _directly_ used dependencies, not transitive closure

#### struct `uLang::SPackageUsage`  
`struct SPackageUsage`  
_L108-111_
- desc: Remember what packages use which dependencies
- L110 _public member_ `TArray<SPackageUsageEntry> _Packages;`

#### struct `uLang::SBuildParams`  
`struct SBuildParams`  
_L114-176_
- desc: Build parameters. This is the `uLang` equivalent of `FSolIdeBuildSettings` with some additional fields.
- L122 _public member_ `uint32_t _UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest;` — This allows us to determine when a package was uploaded for a given Fortnite release version. It is a HACK that conditionally enables/disables behaviour in the compiler in order to support previous mistakes allowed to slip through in previous Verse langauge releases  but now need to be supported for backwards compatability. When we can confirm that all Fortnite packages that are currently uploaded are beyond this version being used in all instances of the codebase, this can then be removed.
- L125 _public member_ `int32_t _MaxNumPersistentVars = 0;` — Maximum number of allowed persistent `var` definitions
- L128 _public member_ `int32_t _MaxNumConcreteEntitlementSubclasses = 0;` — Maximum number of concrete entitlement subclasses
- L138 _public member_ `ELinkParam _LinkType = ELinkParam::Default;`
- L151 _public member_ `EWhichVM _TargetVM = EWhichVM::BPVM;`
- L153 _public member_ `EWhichVM _TargetVM = EWhichVM::VerseVM;`
- L157 _public member_ `bool _bSemanticAnalysisOnly : 1 = false;` — If true, we'll run the build only up to semantic analysis
- L160 _public member_ `bool _bGenerateDigests : 1 = true;` — If to generate digests when possible
- L163 _public member_ `bool _bGenerateCode : 1 = true;` — If to generate bytecode
- L166 _public member_ `bool _bUObjectLeniency : 1 = false;` — True if the CVar verse.UObjectLeniency is enabled in VerseTestScriptCmd.
- L169 _public member_ `bool _bQualifyIdentifiers : 1 = false;` — Whether to qualify all unidentified qualifiers in-place in the VST.
- L172 _public member_ `bool _bPrintQualifiedCode : 1 = false;` — If true, print the qualified code to the log.
- L175 _public member_ `bool _bVerbose : 1 = false;` — Get more information

#### enum `uLang::SBuildParams::ELinkParam`  
`enum class ELinkParam`  
_L131-136_
- desc: Link-step settings
- L133 _public enumerator_ `RequireComplete` — Require complete link
- L134 _public enumerator_ `Skip` — Skip link step
- L135 _public enumerator_ `Default`

#### enum `uLang::SBuildParams::EWhichVM`  
`enum class EWhichVM`  
_L145-149_
- desc: HACK_VMSWITCH - remove this once VerseVM is fully brought up Specifies the VM we are compiling the code for We need a variable for this, since even though in most cases WITH_VERSE_BPVM will select the correct value, in the VNI tool we take this information from the command line
- L147 _public enumerator_ `VerseVM`
- L148 _public enumerator_ `BPVM`

#### struct `uLang::SBuildContext`  
`struct SBuildContext`  
_L179-200_
- desc: Settings pertaining to individual runs through the toolchain (build flags, etc.)
- L182 _public member_ `TSRef<CDiagnostics> _Diagnostics;` — Accumulated issues/glitches over all compile phases
- L184 _public member_ `SToolchainInjections _AddedInjections;` — Additional API injections for the individual build pass only
- L186 _public member_ `TArray<CUTF8String> _BuiltInPackageNames = {"Sol` — Name of package providing built-in functionality
- L188 _public member_ `TUPtr<SPackageUsage> _PackageUsage;` — Optional database of dependencies actually used by packages
- L190 _public member_ `SBuildParams _Params;` — Params passed into the Build command
- L193 _public member_ `bool bCloneValidSnippetVsts = false;` — Allow the toolchain to reuse VSTs for files that haven't changed
- L195 _public function_ `explicit SBuildContext(TSRef<CDiagnostics> Diagnostics) : _Diagnostics(Move(Diagnostics))`
- L197 _public function_ `SBuildContext() : _Diagnostics(TSRef<CDiagnostics>::New())`

#### struct `uLang::SProgramContext`  
`struct SProgramContext`  
_L203-211_
- desc: Persistent data from consecutive toolchain runs -- provides a holistic view of the entire program.
- L206 _public member_ `TSRef<CSemanticProgram> _Program;` — Whole view of checked program ready for conversion to runtime equivalent - its types, routines and code bodies of expressions
- L208 _public function_ `SProgramContext(const TSRef<CSemanticProgram>& Program) : _Program(Program)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L40 _function_ `friend inline bool operator==(const FSolFingerprint& A, const FSolFingerprint& B)` (scope `uLang`)
- L45 _function_ `friend inline bool operator!=(const FSolFingerprint& A, const FSolFingerprint& B)` (scope `uLang`)
- L52 _function_ `const auto NibbleToHex = [](uint8_t Value)` (scope `uLang::FSolFingerprint::ToCUTF8String`)

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IAssemblerPass.h` (Public)


#### enum `uLang::ELinkerResult`  
`enum class ELinkerResult`  
_L10-17_
- L12 _public enumerator_ `Link_Skipped = -1`
- L13 _public enumerator_ `Link_Success = 0`
- L14 _public enumerator_ `Link_Failure`
- L15 _public enumerator_ `Link_Skipped_ByInjection`
- L16 _public enumerator_ `Link_Skipped_ByEmptyPass`

#### class `uLang::IAssemblerPass`  
`class IAssemblerPass : public TModularFeature<IAssemblerPass>`  
_L21-28_
- inherits: `TModularFeature<IAssemblerPass>`
- L23 _private prototype_ `ULANG_FEATURE_ID_DECL(IAssemblerPass);`
- L26 _public prototype_ `virtual void TranslateExpressions(const TSRef<CSemanticProgram>& SemanticResult, const SBuildContext& BuildContext, const SProgramContext& ProgramContext) const = 0;`
- L27 _public prototype_ `virtual ELinkerResult Link(const SBuildContext& BuildContext, const SProgramContext& ProgramContext) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L18 _function_ `inline bool operator! (ELinkerResult E)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IIRGeneratorPass.h` (Public)


#### class `uLang::IIrGeneratorPass`  
`class IIrGeneratorPass : public TModularFeature<IIrGeneratorPass>`  
_L10-18_
- inherits: `TModularFeature<IIrGeneratorPass>`
- L12 _private prototype_ `ULANG_FEATURE_ID_DECL(IIrGeneratorPass);`
- L15 _public prototype_ `virtual void Initialize(const SBuildContext& BuildContext, const SProgramContext& ProgramContext) = 0;`
- L16 _public prototype_ `virtual void CleanUp(void) = 0;`
- L17 _public prototype_ `virtual void ProcessAst() const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IParserPass.h` (Public)


#### class `uLang::IParserPass`  
`class IParserPass : public TModularFeature<IParserPass>`  
_L12-18_
- inherits: `TModularFeature<IParserPass>`
- L14 _private prototype_ `ULANG_FEATURE_ID_DECL(IParserPass);`
- L17 _public prototype_ `virtual void ProcessSnippet(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& OutVst, const CUTF8String& TextSnippet, const SBuildContext& BuildContext, const uint32_t VerseVersion, const uint32_t UploadedAtFNVersion) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IPostIrFilter.h` (Public)


#### class `uLang::IPostIrFilter`  
`class IPostIrFilter : public TModularFeature<IPostIrFilter>`  
_L11-17_
- inherits: `TModularFeature<IPostIrFilter>`
- L13 _private prototype_ `ULANG_FEATURE_ID_DECL(IPostIrFilter);`
- L16 _public prototype_ `virtual void FilterIr(const TSRef<CSemanticProgram>& IrResult, const SBuildContext& BuildContext, const SProgramContext& ProgramContext) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IPostSemanticAnalysisFilter.h` (Public)


#### class `uLang::IPostSemanticAnalysisFilter`  
`class IPostSemanticAnalysisFilter : public TModularFeature<IPostSemanticAnalysisFilter>`  
_L11-17_
- inherits: `TModularFeature<IPostSemanticAnalysisFilter>`
- L13 _private prototype_ `ULANG_FEATURE_ID_DECL(IPostSemanticAnalysisFilter);`
- L16 _public prototype_ `virtual void FilterAst(const TSRef<CSemanticProgram>& SemanticResult, const Verse::Vst::TNodeRef<Verse::Vst::Project>& VstProject, const SBuildContext& BuildContext, const SProgramContext& ProgramContext) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/IPostVstFilter.h` (Public)


#### class `uLang::IPostVstFilter`  
`class IPostVstFilter : public TModularFeature<IPostVstFilter>`  
_L10-16_
- inherits: `TModularFeature<IPostVstFilter>`
- L12 _private prototype_ `ULANG_FEATURE_ID_DECL(IPostVstFilter);`
- L15 _public prototype_ `virtual void Filter(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& VstSnippet, const SBuildContext& BuildContext) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/ISemanticAnalyzerPass.h` (Public)


#### class `uLang::ISemanticAnalyzerPass`  
`class ISemanticAnalyzerPass : public TModularFeature<ISemanticAnalyzerPass>`  
_L12-20_
- inherits: `TModularFeature<ISemanticAnalyzerPass>`
- L14 _private prototype_ `ULANG_FEATURE_ID_DECL(ISemanticAnalyzerPass);`
- L17 _public prototype_ `virtual void Initialize(const SBuildContext& BuildContext, const SProgramContext& ProgramContext) = 0;`
- L18 _public prototype_ `virtual void CleanUp(void) = 0;`
- L19 _public prototype_ `virtual TSRef<CSemanticProgram> ProcessVst(const Verse::Vst::Project& Vst, const ESemanticPass Pass) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/CompilerPasses/SemanticAnalyzerPassUtils.h` (Public)


#### enum `uLang::ESemanticPass`  
`enum class ESemanticPass`  
_L6-16_
- L8 _public enumerator_ `SemanticPass_Invalid = 0`
- L10 _public enumerator_ `SemanticPass_Types`
- L11 _public enumerator_ `SemanticPass_Attributes`
- L12 _public enumerator_ `SemanticPass_Code`
- L14 _public enumerator_ `SemanticPass__MinValid = SemanticPass_Types`
- L15 _public enumerator_ `SemanticPass__MaxValid = SemanticPass_Code`

#### Free symbols / members of external scopes

- L4 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Diagnostics/Diagnostics.h` (Public)


#### enum `uLang::EBuildPhase`  
`enum class EBuildPhase : uint8_t`  
_L13-21_
- L15 _public enumerator_ `Parse`
- L16 _public enumerator_ `SemanticAnalysis`
- L17 _public enumerator_ `Localization`
- L18 _public enumerator_ `IrGeneration`
- L19 _public enumerator_ `CodeGen`
- L20 _public enumerator_ `Link`

#### enum `uLang::EBuildEvent`  
`enum class EBuildEvent`  
_L23-34_
- L25 _public enumerator_ `PersistentWeakMapDefinition`
- L26 _public enumerator_ `EntitlementSubclassDefinition`
- L27 _public enumerator_ `FunctionDefinition`
- L28 _public enumerator_ `ClassDefinition`
- L29 _public enumerator_ `TopLevelDefinition`
- L30 _public enumerator_ `UseOfExperimentalDefinition`
- L31 _public enumerator_ `MissingEntitlement`
- L32 _public enumerator_ `PhaseStarted`
- L33 _public enumerator_ `PhaseCompleted`

#### struct `uLang::SBuildEventInfo`  
`struct SBuildEventInfo`  
_L36-78_
- L38 _public function_ `SBuildEventInfo(EBuildEvent Type, uint32_t Int32) : Type`
- L44 _public function_ `SBuildEventInfo(EBuildEvent Type, CUTF8String String) : Type`
- L50 _public prototype_ `SBuildEventInfo() = delete;`
- L52 _public prototype_ `SBuildEventInfo(const SBuildEventInfo&) = delete;`
- L54 _public prototype_ `SBuildEventInfo(SBuildEventInfo&&) = delete;`
- L56 _public prototype_ `SBuildEventInfo& operator=(const SBuildEventInfo&) = delete;`
- L58 _public prototype_ `SBuildEventInfo& operator=(SBuildEventInfo&&) = delete;`
- L60 _public function_ `~SBuildEventInfo()`
- L72 _public member_ `EBuildEvent Type;`

#### union `uLang::SBuildEventInfo::(anonymous)`  
``  
_L74-77_

#### struct `uLang::SBuildStatistics`  
`struct SBuildStatistics`  
_L81-90_
- desc: Various statistics for a given build that can be used in analytics.
- L83 _public member_ `uint32_t NumPersistentWeakMaps = 0;`
- L84 _public member_ `uint32_t NumEntitlementSubclasses = 0;`
- L85 _public member_ `uint32_t NumFunctions = 0;`
- L86 _public member_ `uint32_t NumClasses = 0;`
- L87 _public member_ `uint32_t NumTopLevelDefinitions = 0;`
- L88 _public member_ `TArray<CUTF8String> UsesOfExperimentalDefinitions;`
- L89 _public member_ `TArray<CUTF8String> MissingEntitlements;`

#### class `uLang::CDiagnostics`  
`class CDiagnostics : public CSharedMix`  
_L93-254_
- inherits: `CSharedMix`
- desc: Accumulated issues for full set of compilation passes
- L98 _public function_ `bool HasWarnings() const` — Just warnings (no info or errors)
- L99 _public prototype_ `int32_t GetWarningNum() const;`
- L102 _public function_ `bool HasErrors() const` — Just errors (no info or warnings)
- L103 _public prototype_ `int32_t GetErrorNum() const;`
- L106 _public function_ `bool HasGlitches() const` — Any type of glitch including info, warnings and errors
- L107 _public function_ `int32_t GetGlitchNum() const`
- L108 _public function_ `const TSRefArray<SGlitch>& GetGlitches() const`
- L109 _public function_ `bool IsGlitchWithId(uintptr_t VstIdentifier) const`
- L111 _public function_ `bool HasUseOfExperimentalDefinition() const`
- L112 _public function_ `const SBuildStatistics& GetStatistics() const`
- L117 _public function_ `void Reset()`
- L122 _public function_ `void AppendGlitch(const TSRef<SGlitch>& Glitch)`
- L128 _public function_ `void AppendGlitch(const TSPtr<SGlitch>& Glitch)`
- L133 _public function_ `void AppendGlitch(SGlitchResult&& Result, SGlitchLocus&& Locus)`
- L138 _public function_ `void AppendGlitch(SGlitchResult&& Result)`
- L143 _public function_ `void AppendGlitches(TSRefArray<SGlitch>& Glitches)`
- L152 _public function_ `void Append(CDiagnostics&& Other)`
- L188 _public function_ `void AppendPersistentWeakMap()`
- L194 _public function_ `void AppendEntitlementSubclasses(uint32_t Count)`
- L200 _public function_ `void AppendFunctionDefinition(const uint32_t Count)`
- L206 _public function_ `void AppendClassDefinition(const uint32_t Count)`
- L212 _public function_ `void AppendTopLevelDefinition(const uint32_t Count)`
- L218 _public function_ `void AppendUseOfExperimentalDefinition(CUTF8String UseOfExperimentalDefinition)`
- L224 _public function_ `void AppendMissingEntitlement(CUTF8String MissingEntitlement)`
- L230 _public function_ `void BeginPhase(EBuildPhase Phase)`
- L235 _public function_ `void EndPhase(EBuildPhase Phase)`
- L240 _public typedef_ `using COnGlitchEvent = TEvent<const TSRef<SGlitch>&>;`
- L241 _public function_ `COnGlitchEvent::Registrar& OnGlitchEvent()`
- L243 _public typedef_ `using COnBuildStatisticEvent = TEvent<const SBuildEventInfo&>;`
- L244 _public function_ `COnBuildStatisticEvent::Registrar& OnBuildStatisticEvent()`
- L248 _protected member_ `TSRefArray<SGlitch> _Glitches;` — All the issues encountered across all the phases (Parser and SemanticAnalyzer)
- L250 _protected member_ `SBuildStatistics _Statistics;`
- L252 _protected member_ `COnGlitchEvent _OnGlitchEvent;`
- L253 _protected member_ `COnBuildStatisticEvent _OnBuildStatisticEvent;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L75 _member_ `uint32_t Int32;` (scope `uLang::SBuildEventInfo::__anon29a5e981010a`)
- L76 _member_ `CUTF8String String;` (scope `uLang::SBuildEventInfo::__anon29a5e981010a`)
- L98 _function_ `bool HasWarnings() const` (scope `uLang::CDiagnostics::HasWarnings`) — Just warnings (no info or errors)
- L102 _function_ `bool HasErrors() const` (scope `uLang::CDiagnostics::HasErrors`) — Just errors (no info or warnings)
- L109 _function_ `bool IsGlitchWithId(uintptr_t VstIdentifier) const` (scope `uLang::CDiagnostics::IsGlitchWithId`)

### `Source/Runtime/VerseCompiler/Public/uLang/Diagnostics/Glitch.h` (Public)


#### enum `uLang::EDiagnosticSeverity`  
`enum class EDiagnosticSeverity : uint8_t`  
_L21-27_
- desc: The severity of a diagnostic.
- L23 _public enumerator_ `Ok`
- L24 _public enumerator_ `Info`
- L25 _public enumerator_ `Warning`
- L26 _public enumerator_ `Error`

#### enum `uLang::EDiagnostic`  
`enum class EDiagnostic : uint16_t`  
_L317-322_
- desc: Possible errors, warnings, intermediary states and Okay diagnostic/analysis results.
- L320 _public enumerator_ `VERSE_ENUM_DIAGNOSTICS(VISIT_DIAGNOSTIC) #undef VISIT_DIAGNOSTIC`

#### struct `uLang::SDiagnosticInfo`  
`struct SDiagnosticInfo`  
_L327-332_
- desc: Information about a diagnostic: a reference code, a severity, and a description.
- L329 _public member_ `uint16_t ReferenceCode;`
- L330 _public member_ `EDiagnosticSeverity Severity;`
- L331 _public member_ `const char* Description;`

#### struct `uLang::SGlitchResult`  
`struct SGlitchResult`  
_L340-356_
- desc: Information about the result of a glitch.
- L343 _public member_ `EDiagnostic _Id;` — Id for issue - static so it can be used in online searching/etc.
- L348 _public member_ `CUTF8String _Message;` — String describing the result - either built custom at the time the issue was encountered or generated after the fact using _Result and other info contained in this structure and the associated SArgs and CParser objects.
- L350 _public prototype_ `SGlitchResult(EDiagnostic ResultId);`
- L351 _public function_ `SGlitchResult(EDiagnostic ResultId, CUTF8String&& Message) : _Id(ResultId), _Message(Move(Message))`
- L353 _public function_ `const SDiagnosticInfo& GetInfo() const`
- L354 _public function_ `bool IsError() const`
- L355 _public function_ `bool IsWarning() const`

#### struct `uLang::SGlitchLocus`  
`struct SGlitchLocus`  
_L361-393_
- desc: Information about the location of a glitch.
- L364 _public member_ `CUTF8String _SnippetPath;` — Path of the text snippet where the glitch occurred (this is usually the fully qualified path of a file)
- L370 _public member_ `STextRange _Range;` — The range of the code being parsed (relative to specific parse text) with GetBegin() being the start of the most recent syntax element having issues and GetEnd() being the best guess for the end of that syntax element (or the end index of the code being parsed).
- L374 _public member_ `Verse::Vst::TNodePtr<Verse::Vst::Node> _VstIdentifier;` — Unique identifier for abstract syntax tree element where glitch occurred or 0 if general error without associated Vst element.
- L376 _public function_ `SGlitchLocus()`
- L377 _public function_ `SGlitchLocus(const CUTF8String& SnippetPath, const STextRange& Range, const Verse::Vst::TNodePtr<Verse::Vst::Node> VstIdentifier) : _SnippetPath(SnippetPath), _Range(Range), _VstIdentifier(VstIdentifier)`
- L378 _public function_ `SGlitchLocus(const CUTF8String& SnippetPath, const STextRange& Range) : _SnippetPath(SnippetPath), _Range(Range)`
- L379 _public prototype_ `SGlitchLocus(const Verse::Vst::Node* VstNode);`
- L380 _public prototype_ `SGlitchLocus(const CAstNode* AstNode);`
- L392 _public prototype_ `CUTF8String AsFormattedString() const;` — Returns a human-readable message describing a locus formatted for Visual Studio that will jump to the file and the specified lines/columns when double-clicked in the VS Output log. See https://docs.microsoft.com/en-us/cpp/build/formatting-the-output-of-a-custom-build-step-or-build-event filename(line#,column#, line#,column#]) Example: C:\sourcefile.Verse(134,10, 134,16)

#### struct `uLang::SGlitch`  
`struct SGlitch : public CSharedMix`  
_L398-426_
- inherits: `CSharedMix`
- desc: Info describing a syntax error/warning that was encountered during parse.
- L403 _public member_ `SGlitchResult _Result;` — What happened
- L406 _public member_ `SGlitchLocus _Locus;` — Where it happened
- L410 _public function_ `SGlitch(SGlitchResult&& Result, SGlitchLocus&& Locus) : _Result(Move(Result)), _Locus(Move(Locus))`
- L423 _public function_ `CUTF8String AsFormattedString() const` — Returns a human-readable message describing a Glitch formatted for Visual Studio that will jump to the file and the specified lines/columns when double-clicked in the VS Output log. See https://docs.microsoft.com/en-us/cpp/build/formatting-the-output-of-a-custom-build-step-or-build-event {filename(line#,column#, line#,column#]) | toolname} : [ any text ] {error | warning} code+number:localizable string [ any text ] Example: C:\sourcefile.Verse(134,10, 134,16): Verse compile error V3510: The return value of `SomeClass.some_function` is of type `int` which is incompatible with the expected type `string`.
- L424 _public prototype_ `static CUTF8String FormattedString(const char* Message, const char* Path, const STextRange& Range, EDiagnosticSeverity Severity = EDiagnosticSeverity::Error, EDiagnostic Diagnostic = EDiagnostic::Ok);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uLang`
- L32 _macro_ `#define VERSE_ENUM_DIAGNOSTICS(v) \` — Applies the given visitor macro for each diagnostic.
- L319 _macro_ `#define VISIT_DIAGNOSTIC(Code, Severity, EnumName, Description) EnumName,`
- L334 _prototype_ `const SDiagnosticInfo& GetDiagnosticInfo(EDiagnostic Diagnostic);` (scope `uLang`)
- L335 _prototype_ `EDiagnostic GetDiagnosticFromReferenceCode(uint16_t ReferenceCode);` (scope `uLang`)
- L429 _prototype_ `TOptional<int32_t> ScanToRowCol(CUTF8StringView const& Source, const STextPosition& Position);` (scope `uLang`) — Convert a Row/Col offset to a byte offset from beginning of 'Source'
- L430 _prototype_ `TOptional<int32_t> ScanToRowCol(const SIndexedSourceText& SourceText, const STextPosition& Position);` (scope `uLang`)
- L433 _prototype_ `CUTF8StringView TextRangeToStringView(CUTF8StringView const& Source, STextRange const& Range);` (scope `uLang`) — Given a 'Range', return a corresponding string subview of 'Source'
- L434 _prototype_ `CUTF8StringView TextRangeToStringView(const SIndexedSourceText& SourceText, STextRange const& Range);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Parser/ParserPass.h` (Public)


#### class `uLang::CParserPass`  
`class CParserPass : public IParserPass`  
_L10-20_
- inherits: `IParserPass`
- L15 _public prototype_ `ProcessSnippet(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& OutVst, const CUTF8String& TextSnippet, const SBuildContext& BuildContext, const uint32_t VerseVersion, const uint32_t UploadedAtFNVersion) const override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API VERSECOMPILER_API`
- L8 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Parser/ReservedSymbols.h` (Public)


#### enum `uLang::EIsReservedSymbolResult`  
`enum class EIsReservedSymbolResult : uint8_t`  
_L14-19_
- L16 _public enumerator_ `NotReserved`
- L17 _public enumerator_ `Reserved`
- L18 _public enumerator_ `ReservedFuture`

#### enum `uLang::EReservedSymbol`  
`enum class EReservedSymbol : uint32_t`  
_L26-29_
- desc: Represents the set of reserved symbols in the semantic analyzer (not the parser!)
- L28 _public enumerator_ `VERSE_ENUMERATE_RESERVED_SYMBOLS(VISIT_RESERVED_SYMBOL)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L21 _macro_ `#define VISIT_RESERVED_SYMBOL(Name, Symbol, Reservation, VerseVersion, \`
- L34 _prototype_ `GetReservedSymbol(const EReservedSymbol Identifier);` (scope `uLang`)
- L37 _prototype_ `EIsReservedSymbolResult GetReservationForSymbol( const EReservedSymbol Identifier, const uint32_t CurrentVerseVersion, const uint32_t CurrentUploadedAtFNVersion);` (scope `uLang`) — Gets the type of reservation this symbol has.
- L41 _prototype_ `EIsReservedSymbolResult GetReservationForSymbol( const CSymbol& Identifier, const uint32_t CurrentVerseVersion, const uint32_t CurrentUploadedAtFNVersion);` (scope `uLang`) — @overload
- L47 _prototype_ `GetReservedSymbols(const uint32_t CurrentVerseVersion, const uint32_t CurrentUploadedAtFNVersion);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Parser/ReservedSymbols.inl` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define VERSE_ENUMERATE_RESERVED_SYMBOLS(DECLARE_RESERVED_SYMBOL) \` — Identifiers added here should be identifiers that are reserved purely for implementation reasons. For identifiers that are reserved at the Verse language-level, that should be in the parser `VerseGrammar.h` token list instead. Adding a keyword in this list automatically reserves it in the semantic analyzer. Keep in mind that just because an identifier isn't listed as reserved here, that does not mean it isn't actually reserved - it may be gated behind a version check. TODO: This isn't yet exhaustive and the entire codebase isn't yet converted to using this.

### `Source/Runtime/VerseCompiler/Public/uLang/Parser/VerseGrammar.h` (Public)


#### struct `Verse::Grammar::SNothing`  
`struct SNothing`  
_L52-54_
- desc: Trivial type.

#### enum `Verse::Grammar::EPrec`  
`enum class EPrec : uint8_t`  
_L57-80_
- desc: Precedence.
- L59 _public enumerator_ `Never`
- L60 _public enumerator_ `List`
- L61 _public enumerator_ `Commas`
- L62 _public enumerator_ `Expr`
- L63 _public enumerator_ `Fun`
- L64 _public enumerator_ `Def`
- L65 _public enumerator_ `Or`
- L66 _public enumerator_ `And`
- L67 _public enumerator_ `Not`
- L68 _public enumerator_ `Eq`
- L69 _public enumerator_ `NotEq`
- L70 _public enumerator_ `Less`
- L71 _public enumerator_ `Greater`
- L72 _public enumerator_ `Choose`
- L73 _public enumerator_ `To`
- L74 _public enumerator_ `Add`
- L75 _public enumerator_ `Mul`
- L76 _public enumerator_ `Prefix`
- L77 _public enumerator_ `Call`
- L78 _public enumerator_ `Base`
- L79 _public enumerator_ `Nothing`

#### enum `Verse::Grammar::EAssoc`  
`enum class EAssoc : uint8_t`  
_L83-89_
- desc: Associativity.
- L85 _public enumerator_ `None`
- L86 _public enumerator_ `Postfix`
- L87 _public enumerator_ `InfixLeft`
- L88 _public enumerator_ `InfixRight`

#### enum `Verse::Grammar::EForm`  
`enum class EForm : uint8_t`  
_L92-96_
- desc: Block form.
- L94 _public enumerator_ `List`
- L95 _public enumerator_ `Commas`

#### enum `Verse::Grammar::EPunctuation`  
`enum class EPunctuation : uint8_t`  
_L99-110_
- desc: Block punctuation.
- L101 _public enumerator_ `None`
- L102 _public enumerator_ `Braces`
- L103 _public enumerator_ `Parens`
- L104 _public enumerator_ `Brackets`
- L105 _public enumerator_ `AngleBrackets`
- L106 _public enumerator_ `Qualifier`
- L107 _public enumerator_ `Dot`
- L108 _public enumerator_ `Colon`
- L109 _public enumerator_ `Ind`

#### enum `Verse::Grammar::EPlace`  
`enum class EPlace : uint16_t`  
_L113-123_
- desc: Places specializing capture generation.
- L115 _public enumerator_ `UTF8`
- L116 _public enumerator_ `Printable`
- L117 _public enumerator_ `BlockCmt`
- L118 _public enumerator_ `LineCmt`
- L119 _public enumerator_ `IndCmt`
- L120 _public enumerator_ `Space`
- L121 _public enumerator_ `String`
- L122 _public enumerator_ `Content`

#### enum `Verse::Grammar::EMode`  
`enum class EMode`  
_L127-133_
- desc: Modes for calling: none (error if instantiated), of (failure disallowed), at (failure allowed), with (macro).
- L129 _public enumerator_ `None`
- L130 _public enumerator_ `Open`
- L131 _public enumerator_ `Closed`
- L132 _public enumerator_ `With`

#### struct `Verse::Grammar::TScopedGuard`  
`template <typename GuardVariableType> struct TScopedGuard`  
_L138-156_
- desc: Sets a variable on construction, and restores its previous value on destruction.
- L140 _public function_ `TScopedGuard(GuardVariableType& InGuardVariable, const GuardVariableType& NewValue) : _GuardVariable(&InGuardVariable) , _OldValue(InGuardVariable)`
- L147 _public function_ `~TScopedGuard()`
- L154 _private member_ `GuardVariableType* _GuardVariable;`
- L155 _private member_ `GuardVariableType _OldValue;`

#### struct `Verse::Grammar::SText`  
`struct SText`  
_L159-190_
- desc: Text spans passed around by the parser.
- L161 _public member_ `const char8_t *Start, *Stop;`
- L161 _public member_ `const char8_t *Start, *Stop;`
- L162 _public function_ `constexpr SText() : Start(nullptr) , Stop(nullptr)`
- L165 _public function_ `constexpr SText(const char8_t* Start0, const char8_t* Stop0) : Start(Start0) , Stop(Stop0)`
- L171 _public function_ `constexpr SText(const char8_t* Start0) : SText(Start0, Start0)`
- L177 _public function_ `SText(const char* Start0) : SText(reinterpret_cast<const char8_t*>(Start0), (const char8_t*)Start0)`
- L184 _public function_ `constexpr char8_t operator[](uint64_t i) const`
- L189 _public function_ `explicit operator bool() const`

#### struct `Verse::Grammar::SSnippet`  
`struct SSnippet`  
_L210-234_
- desc: A snippet of text describing its location.
- L212 _public member_ `SText Text;`
- L213 _public member_ `uint64_t StartLine, StopLine;`
- L213 _public member_ `uint64_t StartLine, StopLine;`
- L214 _public member_ `uint64_t StartColumn, StopColumn;`
- L214 _public member_ `uint64_t StartColumn, StopColumn;`
- L215 _public function_ `SSnippet() : Text(nullptr, nullptr) , StartLine(0) , StopLine(0) , StartColumn(0) , StopColumn(0)`
- L221 _public function_ `explicit operator bool() const`
- L227 _private function_ `SSnippet(const char8_t* Start0, const char8_t* End0, uint64_t StartLine0, uint64_t StopLine0, uint64_t StartColumn0, uint64_t StopColumn0) : Text(Start0, End0) , StartLine(StartLine0) , StopLine(StopLine0) , StartColumn(StartColumn0) , StopColumn(StopColumn0)`

#### struct `Verse::Grammar::SBlock`  
`template <class SyntaxesType, class CaptureType> struct SBlock`  
_L238-260_
- desc: Verse blocks.
- L240 _public function_ `SBlock(const SSnippet& BlockSnippet0 = SSnippet{}, const SyntaxesType& Elements0 = SyntaxesType(), EForm Form0 = EForm::List) : BlockSnippet(BlockSnippet0) , Punctuation(EPunctuation::None) , Form(Form0) , Elements(Elements0)`
- L247 _public member_ `SSnippet BlockSnippet;` — Snippet of the whole block.
- L248 _public member_ `SyntaxesType Specifiers;` — Specifiers.
- L249 _public member_ `CaptureType TokenLeading;` — If Token, the Scan before it.
- L250 _public member_ `SText Token;` — Token preceding opening EPunctuation.
- L251 _public member_ `CaptureType PunctuationLeading;` — After SToken, before opening EPunctuation;
- L253 _public member_ `EPunctuation Punctuation;` — present only if Punctuation.
- L254 _public member_ `EForm Form;` — Commas or List.
- L255 _public member_ `SyntaxesType Elements;` — Elements.
- L256 _public member_ `CaptureType ElementsTrailing;` — Scan between elements and closing
- L258 _public member_ `CaptureType PunctuationTrailing;` — EPunctuation or end.

#### struct `Verse::Grammar::TResult`  
`template <class ValueType, class ErrorType> struct TResult`  
_L264-336_
- desc: Results consisting of either a value or an error.
- L268 _public function_ `TResult(const SourceType& Value0) : Value(Value0) , Success(true)`
- L273 _public function_ `TResult(SourceType&& Value0) : Value(std::move(Value0)) , Success(true)`
- L278 _public function_ `TResult() : Error() , Success(false)`
- L281 _public function_ `TResult(const ErrorType& Error0) : Error(Error0) , Success(false)`
- L284 _public function_ `TResult(const TResult& Other) : Success(Other.Success)`
- L292 _public function_ `~TResult()`
- L303 _public function_ `operator bool() const`
- L304 _public function_ `TResult& operator=(const TResult& R)`
- L313 _public function_ `const ValueType& operator*() const`
- L318 _public function_ `ValueType* operator->()`
- L323 _public function_ `const ErrorType& GetError() const`
- L335 _private member_ `bool Success;`

#### union `Verse::Grammar::TResult::(anonymous)`  
``  
_L331-334_

#### struct `Verse::Grammar::EncodedLength::SJumpTable`  
`struct SJumpTable final`  
_L419-565_
- L421 _public typedef_ `using JumpTableFunctionType = uint64_t (*)(const char8_t* const S);`
- L422 _public member_ `JumpTableFunctionType JumpTable[256];`
- L424 _public function_ `constexpr SJumpTable()`

#### struct `Verse::Grammar::SEncoding`  
`struct SEncoding`  
_L577-591_
- desc: Grammar output SEncoding.
- L579 _public member_ `EPrec Prec;`
- L580 _public member_ `bool AllowIn, FollowingIn;`
- L580 _public member_ `bool AllowIn, FollowingIn;`
- L581 _public function_ `SEncoding(EPrec Prec0 = EPrec::List, bool AllowIn0 = false, bool FollowingIn0 = false) : Prec(Prec0) , AllowIn(AllowIn0) , FollowingIn(FollowingIn0)`
- L586 _public function_ `SEncoding Fresh(EPrec Prec1, bool AllowIn1 = false, bool FollowingIn0 = false) const`

#### struct `Verse::Grammar::STokenInfo`  
`struct STokenInfo`  
_L608-644_
- desc: Token information.
- L610 _public member_ `const char8_t* Symbol;`
- L611 _public member_ `EPrec PrefixPrec;`
- L612 _public member_ `EMode PrefixMode;`
- L613 _public member_ `EPrec PostfixTokenPrec;`
- L614 _public member_ `EPrec PostfixPrec;`
- L615 _public member_ `EAssoc PostfixAssoc;`
- L616 _public member_ `EMode PostfixMode;`
- L617 _public member_ `const STokenSet& PostfixAllowMask;`
- L618 _public function_ `SEncoding PostfixLeftEncoding(const SEncoding& Encoding, bool Parens) const`
- L627 _public function_ `SEncoding PostfixRightEncoding(const SEncoding& Encoding, bool Parens) const`
- L637 _public function_ `EPrec PostfixRightPrec() const`

#### struct `Verse::Grammar::SToken`  
`struct SToken`  
_L799-824_
- desc: Tokens.
- L801 _public member_ `uint8_t Index;`
- L802 _public function_ `explicit constexpr SToken(uint8_t Index0) : Index(Index0)`
- L804 _public function_ `constexpr SToken(const char8_t* Op) : Index(uint8_t(ArraySize(Tokens) - 1))`
- L815 _public function_ `constexpr operator uint8_t() const`
- L816 _public function_ `static constexpr SToken None()`
- L817 _public function_ `static constexpr SToken End()`
- L818 _public function_ `static constexpr SToken NewLine()`
- L819 _public function_ `static constexpr SToken Alpha()`
- L820 _public function_ `static constexpr SToken Digit()`
- L821 _public function_ `static constexpr SToken FirstParse()`
- L822 _public function_ `explicit operator bool() const`
- L823 _public function_ `constexpr const STokenInfo* operator->() const`

#### struct `Verse::Grammar::STokenSet`  
`struct STokenSet`  
_L827-863_
- desc: A set of tokens.
- L829 _public function_ `constexpr STokenSet() : Bits`
- L832 _public function_ `template <class... RestTokenTypes> explicit constexpr STokenSet(SToken Token, RestTokenTypes... RestTokens) : STokenSet(RestTokens...)`
- L838 _public function_ `template <class... RestTokenTypes> explicit constexpr STokenSet(const char8_t* TokenStr, RestTokenTypes... RestTokens) : STokenSet(SToken(TokenStr), RestTokens...)`
- L841 _public function_ `constexpr bool Has(SToken T) const`
- L845 _public function_ `constexpr explicit operator bool() const`
- L846 _public function_ `constexpr STokenSet operator&(const STokenSet& Other) const`
- L850 _public function_ `constexpr STokenSet operator|(const STokenSet& Other) const`
- L854 _public function_ `constexpr STokenSet operator~() const`
- L860 _private function_ `constexpr STokenSet(uint64_t Bits0, uint64_t Bits1) : Bits`
- L862 _private member_ `uint64_t Bits[2];`

#### struct `Verse::Grammar::CParserBase`  
`struct CParserBase`  
_L891-1077_
- desc: Generator-independent base class of parser.
- L954 _private member_ `uint8_t FirstToken[256];` — Tokens.
- L955 _private member_ `uint8_t NextToken[ArraySize(Tokens)];` — Next candidate token per token.
- L956 _private function_ `SToken ParseToken(const char8_t* Start, uint64_t& Size)`
- L976 _private member_ `SCursor Cursor;` — State and constructor.
- L977 _private member_ `SContext Context;`
- L978 _private member_ `uint32_t ExprDepth{0};`
- L979 _private member_ `uint32_t CommentDepth{0};`
- L980 _private member_ `const uint64_t InputLength;`
- L981 _private member_ `const char8_t* InputString;`
- L982 _private function_ `CParserBase(uint64_t InputLength0, const char8_t* InputString0, uint64_t Line0 = 1) : FirstToken`
- L1010 _private function_ `void Next(uint64_t n)` — Consumption.
- L1018 _private function_ `bool Eat(const char8_t* s)`
- L1026 _private function_ `void EatToken()`
- L1029 _private function_ `static SSnippet Snip(const SPoint& Start, const SPoint& Stop)` — Snippets.
- L1034 _private function_ `SSnippet Snip(const SPoint& Start) const`
- L1035 _private function_ `SSnippet Snip() const`
- L1036 _private function_ `SText CursorQuote()`
- L1042 _private function_ `SText CursorText()`

#### struct `Verse::Grammar::CParserBase::SCursor`  
`struct SCursor`  
_L899-909_
- desc: A cursor tracks a parsing position in accordance with the Verse grammar, and a snipping position that attributes NewLine to the Space preceding it.
- L901 _public member_ `const char8_t* Pos;` — Pointer to current parse position.
- L902 _public member_ `const char8_t* LineStart;` — Pointer to start of line.
- L903 _public member_ `const char8_t* NextLineStart;` — If >Pos, indicates we've snipped the NewLine at Pos.
- L904 _public member_ `SToken Token;` — Token here.
- L905 _public member_ `uint64_t TokenSize;` — Length of token.
- L906 _public member_ `uint64_t Line;` — Zero-based line number.
- L907 _public function_ `char8_t operator[](int64_t Offset) const`
- L908 _public function_ `bool SnippedNewLine() const`

#### struct `Verse::Grammar::CParserBase::SPoint`  
`struct SPoint`  
_L912-934_
- desc: A point for producing snippets.
- L914 _public member_ `const char8_t* Pos;`
- L915 _public member_ `uint64_t Line, Column;`
- L915 _public member_ `uint64_t Line, Column;`
- L916 _public function_ `SPoint(const char8_t* Pos0, uint64_t Line0, uint64_t Column0) : Pos(Pos0) , Line(Line0) , Column(Column0)`
- L920 _public function_ `SPoint(const SCursor& Cursor) : Pos(Cursor.SnippedNewLine() ? Cursor.NextLineStart : Cursor.Pos) , Line(Cursor.SnippedNewLine() ? Cursor.Line + 1 : Cursor.Line) , Column(Cursor.SnippedNewLine() ? 1 : uint64_t(Cursor.Pos - Cursor.LineStart + 1))`
- L926 _public function_ `static SPoint Start(const SSnippet& Snippet)`
- L930 _public function_ `static SPoint Stop(const SSnippet& Snippet)`

#### struct `Verse::Grammar::CParserBase::SContext`  
`struct SContext`  
_L937-951_
- desc: Grammar SContext coinciding with "push" and "pop" in the specification.
- L939 _public member_ `const char8_t* BlockInd;` — Start of the line that initiated our current
- L941 _public member_ `const char8_t* TrimInd;` — indentation, or nullptr.
- L943 _public member_ `bool Nest;` — further text trimming.
- L944 _public member_ `bool LinePrefix;` — Whether subsequent ScanKey and Commas lines should be
- L946 _public function_ `SContext() : BlockInd` — prefixed with '&'.

#### struct `Verse::Grammar::CParser`  
`template <class GeneratorType> struct CParser : CParserBase`  
_L1081-4155_
- inherits: `CParserBase`
- desc: Generator-dependent parser.
- L1084 _private typedef_ `using SyntaxType = typename GeneratorType::SyntaxType;`
- L1085 _private typedef_ `using SyntaxesType = typename GeneratorType::SyntaxesType;`
- L1086 _private typedef_ `using ErrorType = typename GeneratorType::ErrorType;`
- L1087 _private typedef_ `using CaptureType = typename GeneratorType::CaptureType;`
- L1089 _private typedef_ `template <class ResultValueType> using ResultOf = TResult<ResultValueType, ErrorType>;`
- L1092 _private member_ `const GeneratorType& Gen;` — Constructor.
- L1093 _private function_ `CParser(const GeneratorType& Gen0, uint64_t n, const char8_t* Source0, uint64_t StartLine = 1) :`
- L1173 _private function_ `void UpdateToken()` — Token management.
- L1191 _private function_ `bool CheckToken()`
- L1199 _private function_ `ResultOf<SNothing> Require(const char8_t* Value, ErrorType (CParser::*OnError)(SText What))` — Errors.
- L1206 _private function_ `ResultOf<SNothing> RequireClose(SCursor Start, const char8_t* Open, const char8_t* Close, ErrorType (CParser::*OnError)(SText))`
- L1219 _private function_ `SSnippet SnipFinished(const SCursor& Start, const SExpr& End)` — Snippets.
- L1223 _private function_ `SSnippet SnipFinished(const SCursor& Start, const SBlockInternal& End)`
- L1229 _private function_ `ResultOf<SNothing> SpaceTrailing(STrailing& Trailing)` — Trailing capture and SSnippet management.
- L1236 _private function_ `ResultOf<SNothing> UpdateFrom(SExpr& Target, STrailing& Source, const ResultOf<SyntaxType>& SyntaxResult)`
- L1246 _private function_ `UpdateSpaceTrailing(SExpr& Target, const ResultOf<SyntaxType>& SyntaxResult)`
- L1254 _private function_ `SyntaxType ApplyTrailing(SExpr& Target, bool FinishingNow = false)`
- L1262 _private function_ `void ApplyTrailing(SBlockInternal& Block0, const SPoint& TrailingEnd)`
- L1275 _private function_ `auto S01()` — Character set and comment and errors:
- L1280 _private function_ `auto S02()`
- L1285 _private function_ `auto S03()`
- L1290 _private function_ `auto S04()`
- L1295 _private function_ `auto S05()`
- L1299 _private function_ `auto S06()`
- L1306 _private function_ `auto S15()` — Numeric and numbered character constant errors.
- L1311 _private function_ `auto S16()`
- L1316 _private function_ `auto S18()`
- L1322 _private function_ `auto S19()`
- L1330 _private function_ `auto S20(SText What)` — Identifier errors.
- L1336 _private function_ `auto S23(SText What)`
- L1341 _private function_ `auto S24(SText What)`
- L1347 _private function_ `auto S25(SText What)`
- L1352 _private function_ `auto S26(SText What)`
- L1359 _private function_ `auto S30()` — Text errors.
- L1364 _private function_ `auto S31(SText)`
- L1368 _private function_ `auto S32(SText)`
- L1373 _private function_ `auto S34()`
- L1380 _private function_ `auto S40()` — Markup errors.
- L1385 _private function_ `auto S41()`
- L1390 _private function_ `auto S42()`
- L1395 _private function_ `auto S43(SText Tag, SText Id)`
- L1400 _private function_ `auto S44(SText What)`
- L1406 _private function_ `auto S46()`
- L1414 _private function_ `auto S51(SText What)` — Markup content errors.
- L1419 _private function_ `auto S52(SText)`
- L1424 _private function_ `auto S54()`
- L1429 _private function_ `auto S57()`
- L1436 _private function_ `auto S58()`
- L1444 _private function_ `auto S60(SText What, SText Op)` — Precedence errors.
- L1449 _private function_ `auto S61(SText Op)`
- L1453 _private function_ `auto S62()`
- L1458 _private function_ `auto S64(SText, SText Op)`
- L1463 _private function_ `auto S65()`
- L1467 _private function_ `auto S66(SText Op)`
- L1472 _private function_ `auto S67()`
- L1478 _private function_ `auto S68()`
- L1484 _private function_ `auto S70(SText)` — Bad or missing expression, block, keyword errors.
- L1489 _private function_ `auto S71(SText What)`
- L1494 _private function_ `auto S74(SText)`
- L1499 _private function_ `auto S76(SText What)`
- L1504 _private function_ `auto S77()`
- L1509 _private function_ `auto S78()`
- L1513 _private function_ `auto S79()`
- L1520 _private function_ `auto S80(SText What)` — Expression grouping errors:
- L1525 _private function_ `auto S81(SText What)`
- L1531 _private function_ `auto S82(SText What)`
- L1537 _private function_ `auto S83(SText What)`
- L1543 _private function_ `auto S84(SText What)`
- L1549 _private function_ `auto S85(SText What)`
- L1555 _private function_ `auto S86(SText What)`
- L1561 _private function_ `auto S88(SText)`
- L1566 _private function_ `auto S88void()`
- L1571 _private function_ `auto S89()`
- L1580 _private function_ `auto S97()` — Parser limitations versus spec.
- L1581 _private function_ `auto S98()`
- L1585 _private function_ `auto S99()`
- L1591 _private function_ `void SnipNewLine(CaptureType& Capture, EPlace Place = EPlace::Space)` — Blank space and indentation.
- L1603 _private function_ `bool NewLine(CaptureType& Capture, EPlace Place = EPlace::Space)`
- L1616 _private function_ `bool Ending()`
- L1621 _private function_ `ResultOf<SNothing> Space(CaptureType& Capture, EPlace Place = EPlace::Space, bool DoSnipNewLine = true)`
- L1630 _private function_ `ResultOf<CaptureType> Space(EPlace Place = EPlace::Space)`
- L1636 _private function_ `ResultOf<SContext> Ind()`
- L1647 _private function_ `ResultOf<SNothing> Ded(const SContext& SavedContext, ErrorType (CParser::*OnError)())`
- L1656 _private function_ `ResultOf<bool> Line(CaptureType& Capture, EPlace Place)`
- L1757 _private function_ `ResultOf<SNothing> Scan(CaptureType& Capture, EPlace Place = EPlace::Space)`
- L1774 _private function_ `ResultOf<SToken> ScanKey(CaptureType& Capture, STokenSet TokenSet)`
- L1800 _private function_ `ResultOf<uint64_t> ParseHex(uint64_t MaxDigits, uint64_t MaxValue, ErrorType (CParser::*OnError)())` — Constants and base expressions.
- L1820 _private function_ `ResultOf<SNothing> DisallowDotAlnum()`
- L1827 _private function_ `ResultOf<SNothing> DisallowDotNum()`
- L1834 _private function_ `ResultOf<SyntaxType> Num()`
- L1899 _private function_ `ResultOf<SyntaxType> CharLit()`
- L1932 _private function_ `ResultOf<char8_t> Char8()`
- L1942 _private function_ `ResultOf<char32_t> Char32()`
- L1952 _private function_ `ResultOf<SText> Ident()`
- L1969 _private function_ `ResultOf<SText> Path()`
- L1999 _private function_ `ResultOf<SText> Label(SText What)`
- L2014 _private function_ `ResultOf<CaptureType> LineCmt()` — Text processing.
- L2026 _private function_ `ResultOf<CaptureType> BlockCmt()`
- L2041 _private function_ `ResultOf<CaptureType> IndCmt()`
- L2070 _private function_ `template <EPlace ParsePlace> ResultOf<SNothing> Text(CaptureType& Capture, EPlace GenPlace = ParsePlace)`
- L2163 _private function_ `ResultOf<SBlockInternal> Interp()`
- L2174 _private function_ `ResultOf<SBlockInternal> Ampersand()`
- L2204 _private function_ `template <EPlace Place> ResultOf<SyntaxesType> String(SCursor TextStart, CaptureType Leading = CaptureType())`
- L2257 _private function_ `ResultOf<SyntaxType> Contents(bool TrimLeading)` — Markup content.
- L2291 _private function_ `ResultOf<SyntaxType> Trimmed(bool TrimLeading)`
- L2305 _private function_ `SingletonBlock(const SSnippet& Snippet, const SyntaxType& Syntax, const CaptureType& PunctuationLeading = CaptureType(), EPunctuation Punctuation = EPunctuation::None)`
- L2316 _private function_ `SingletonBlock(const SCursor& BlockStart, SExpr& Expr, const CaptureType& PunctuationLeading = CaptureType(), EPunctuation Punctuation = EPunctuation::None)`
- L2325 _private function_ `ResultOf<SBlockInternal> IndList(SCursor Start, const CaptureType& PunctuationLeading, EPunctuation Punctuation, SCursor LeadingStart, const CaptureType& Leading = CaptureType())`
- L2341 _private function_ `BlockHelper(SText What, EPrec Prec, SExpr& OuterExpr, SCursor BlockStart, CaptureType PunctuationLeading, bool AllowOpen, bool AllowInd, bool AllowCommas, bool* Fails = nullptr)`
- L2429 _private function_ `ResultOf<SBlockInternal> Block(SText What, SExpr& OuterExpr, SCursor BlockStart, const CaptureType& PunctuationLeading, bool& Fails)`
- L2439 _private function_ `ResultOf<SBlockInternal> BraceInd(SText What, EPrec Prec, SExpr& OuterExpr)`
- L2447 _private function_ `ResultOf<SBlockInternal> KeyBlock(EPrec Prec, SExpr& OuterExpr, SCursor BlockStart, const CaptureType& TokenLeading, SText Token, const CaptureType& PunctuationLeading)`
- L2461 _private function_ `ResultOf<SBlockInternal> KeyBlockDefs(SExpr& OuterExpr, SCursor BlockStart, const CaptureType& TokenLeading, SText Token)`
- L2475 _private function_ `template <class CallableType> ResultOf<SNothing> WhenBraceCall(const char8_t* What, EPrec Prec, SExpr& OuterExpr, const CallableType& Func)`
- L2499 _private function_ `ResultOf<SyntaxType> QualIdentQualified(SExpr& Target, const SCursor& Start, SBlockInternal& Block0)` — Qualified identifiers.
- L2514 _private function_ `ResultOf<SyntaxType> QualIdent(SText What, SExpr& Target, bool AllowParenthesis)`
- L2662 _private function_ `InvokeClause(SInvoke& Target, uint64_t WhichClause, SCursor BlockStart, SBlockInternal& Block0, SCursor NextBlockStart, const CaptureType& NextTokenLeading = CaptureType())`
- L2714 _private function_ `ResultOf<SNothing> InvokeParens(SInvoke& Target, const SCursor& BlockStart)`
- L2749 _private function_ `ResultOf<SNothing> InvokeLess(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2828 _private function_ `ResultOf<SNothing> InvokeBlock(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2850 _private function_ `ResultOf<SNothing> InvokeDoThen(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2866 _private function_ `ResultOf<SNothing> InvokeUntil(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2880 _private function_ `ResultOf<SNothing> InvokeCatch(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2908 _private function_ `ResultOf<SNothing> InvokeElse(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L2941 _private function_ `template <SToken PostfixToken> ResultOf<SNothing> InvokeSeq(SInvoke& Target, const SCursor& BlockStart, const CaptureType& TokenLeading)`
- L3020 _private function_ `ResultOf<SNothing> InvokeNewLine(SInvoke& Target, const SCursor& BlockStart, CaptureType& TokenLeading)`
- L3032 _private function_ `ResultOf<SNothing> Invoke(SInvoke& Target, SCursor BlockStart, CaptureType TokenLeading = CaptureType())`
- L3111 _private function_ `ResultOf<SNothing> InvokeMarkup(SInvoke& InvokeTarget, const CaptureType& TokenLeading, const CaptureType& PreContent, SyntaxType& Content, const CaptureType& PostContent)` — Markup.
- L3129 _private function_ `ResultOf<SyntaxType> Markup()`
- L3147 _private function_ `ResultOf<SNothing> InChoose(SExpr& PostfixExpr, SCursor Start, const SIns* Ins = nullptr)`
- L3185 _private function_ `ResultOf<SNothing> DefPostfix(SExpr& Target)`
- L3203 _private function_ `ResultOf<SyntaxType> Digit(SExpr& Target)`
- L3219 _private function_ `ResultOf<SyntaxType> Quote(SExpr& Target)`
- L3228 _private function_ `ResultOf<SNothing> Attribute(SText What, EPrec Prec, SExpr& Target)`
- L3271 _private function_ `ResultOf<SyntaxType> Path(SExpr& Target)`
- L3278 _private function_ `ResultOf<SNothing> In(SExpr& Target)`
- L3303 _private function_ `ResultOf<SNothing> VarKeyword(SExpr& Target)`
- L3367 _private function_ `ResultOf<SNothing> Not(SExpr& Target)`
- L3387 _private function_ `ResultOf<SNothing> Ampersand(SExpr& Target)`
- L3402 _private function_ `ResultOf<SNothing> Arithmetic(SExpr& Target)`
- L3419 _private function_ `ResultOf<SNothing> LeftBracket(SExpr& Target)`
- L3437 _private function_ `ResultOf<SNothing> If(SExpr& Target)`
- L3455 _private function_ `ResultOf<SNothing> ControlFlowKeyword(SExpr& Target)`
- L3474 _private function_ `ResultOf<SNothing> Base(SText What, EPrec Prec, SExpr& Target, ErrorType (CParser::*OnTokenError)(SText), ErrorType (CParser::*OnPrecError)(SText, SText))`
- L3588 _private function_ `ResultOf<SNothing> PostfixBinaryOperator(const SToken PostfixToken, SExpr& Target)`
- L3618 _private function_ `ResultOf<SNothing> PostfixRef(const SToken PostfixToken, SExpr& Target)`
- L3629 _private function_ `ResultOf<SNothing> PostfixLeftBracket(const SCursor& PostfixStart, SExpr& Target)`
- L3645 _private function_ `ResultOf<SNothing> PostfixAttribute(const SToken PostfixToken, SExpr& Target)`
- L3660 _private function_ `ResultOf<SNothing> PostfixAtOf(const SCursor& PostfixStart, const SToken PostfixToken, SExpr& Target)`
- L3676 _private function_ `ResultOf<SNothing> PostfixArrow(const SToken PostfixToken, SExpr& Target)`
- L3690 _private function_ `ResultOf<SNothing> PostfixDotBlock(CaptureType& TokenLeading, const SToken PostfixToken, SExpr& Target)`
- L3704 _private function_ `ResultOf<SNothing> PostfixIs(const SCursor& PostfixStart, CaptureType& TokenLeading, SExpr& Target)`
- L3718 _private function_ `ResultOf<SNothing> PostfixWhere(const SCursor& PostfixStart, CaptureType& TokenLeading, const SToken PostfixToken, SExpr& Target)`
- L3734 _private function_ `ResultOf<SNothing> PostfixMacroInvoke(const SCursor& PostfixStart, CaptureType& TokenLeading, const SToken PostfixToken, EPrec Prec, SExpr& Target)`
- L3769 _private function_ `ResultOf<SNothing> Postfix( SText , EPrec Prec, SExpr& Target, ErrorType (CParser::* )(SText) = &CParser::S71, ErrorType (CParser::* )(SText, SText) = &CParser::S60)`
- L3926 _private function_ `ResultOf<SExpr*> FinishExpr(SToken Token, EPrec FinishPrec, SExpr& SourceExpr)`
- L3984 _private prototype_ `template <class CallableType> SWhenExpr(EPrec, SExpr*, STokenSet, const SCursor&, const CaptureType&, const CallableType&, SExpr* e = nullptr, bool b = false) -> SWhenExpr<CallableType>;`
- L3989 _private function_ `WhenExpr(SText What, EPrec ParsePrec, EPrec FinishPrec, SExpr* OuterExpr, const CaptureType& ExprLeading, const CallableType& Func, STokenSet AllowPostfixes = AllTokens, ErrorType (CParser::*OnTokenError)(SText) = &CParser::S71, SExpr* QualIdentTarget0 = nullptr)`
- L4003 _private function_ `ResultOf<SyntaxType> MarkupExpr(SExpr* OuterMarkup, SCursor MarkupStart)`
- L4024 _private function_ `ResultOf<SBlockInternal> Commas(SText What, EPrec Prec, SCursor Start, CaptureType& Leading, ErrorType (CParser::*OnTokenError)(SText))` — Separated expressions.
- L4053 _private function_ `ResultOf<SBlockInternal> List(SText What, ErrorType (CParser::*OnTokenError)(SText), SCursor BlockStart, const CaptureType& PunctuationLeading, EPunctuation Punctuation, SCursor CommasStart, const CaptureType& Leading = CaptureType())`
- L4125 _private function_ `ResultOf<SyntaxType> File()`
- L4140 _private function_ `ResultOf<SyntaxType> CheckResult(const ResultOf<SyntaxType>& Result)`

#### struct `Verse::Grammar::CParser::STrailing`  
`struct STrailing`  
_L1104-1116_
- desc: Tracking STrailing captures across expressions and their postfixes so we can assign them to the lexically outermost generator.
- L1106 _public member_ `TResult<SCursor, SNothing> TrailingStart;`
- L1107 _public member_ `CaptureType TrailingCapture;`
- L1108 _public function_ `explicit operator bool() const`
- L1109 _public function_ `void MoveFrom(STrailing& Source)`

#### struct `Verse::Grammar::CParser::SBlockInternal`  
`struct SBlockInternal : public SBlock<SyntaxesType, CaptureType>`  
_L1119-1123_
- inherits: `SBlock<SyntaxesType,CaptureType>`
- desc: Our extended internal block structure tracking block's trailing captures.
- L1122 _public member_ `STrailing BlockTrailing;`

#### struct `Verse::Grammar::CParser::SExpr`  
`struct SExpr`  
_L1132-1170_
- desc: We track a stack of expressions and postfixes at increasing precedence so that we can insert multi-precedence postfix operators like '<' and stop subsequent parsing there. An SExpr is in one of three states (except mid-update when these invariants don't hold): - Uninitialized: no ExprSyntax, no Trailing, not Finished. - Initialized:   has ExprSyntax, has Trailing, not Finished. - Finished:      has ExprSyntax, no Trailing, is Finished.
- L1134 _public member_ `SCursor Start;`
- L1135 _public member_ `EPrec FinishPrec;`
- L1136 _public member_ `TResult<SCursor, SNothing> Finished;`
- L1137 _public member_ `SExpr* OuterExpr;`
- L1138 _public member_ `STokenSet AllowPostfixes;`
- L1139 _public member_ `TResult<SyntaxType, SNothing> ExprSyntax;`
- L1140 _public member_ `CaptureType ExprLeading;`
- L1141 _public member_ `STrailing Trailing;` — -V730_NOINIT
- L1142 _public member_ `TResult<SCursor, SNothing> MarkupStart;`
- L1143 _public member_ `bool MarkupFinished, ExprStop;`
- L1143 _public member_ `bool MarkupFinished, ExprStop;`
- L1144 _public member_ `struct SExpr* OuterMarkup;`
- L1145 _public member_ `SText MarkupTag;`
- L1146 _public member_ `SExpr* QualIdentTarget;`
- L1147 _public function_ `SExpr(EPrec FinishPrec0, const SCursor& Start0, SExpr* OuterExpr0, STokenSet AllowPostfixes0 = STokenSet{}, SExpr* QualIdentTarget0 = nullptr) : Start(Start0) , FinishPrec(FinishPrec0) , OuterExpr(OuterExpr0) , AllowPostfixes(AllowPostfixes0) , MarkupFinished(false) , ExprStop(false) , OuterMarkup(nullptr) , QualIdentTarget(QualIdentTarget0)`
- L1158 _public function_ `SyntaxType operator*() const`
- L1161 _public prototype_ `virtual ~SExpr() = default;` — Needs a virtual destructor since it has virtual methods or various static analysis will complain
- L1162 _public function_ `virtual ResultOf<SNothing> OnFinish(CParser& )`

#### struct `Verse::Grammar::CParser::SCall`  
`struct SCall`  
_L2549-2556_
- desc: Macro invocations and constructs that lead with same syntax like '(', '<', 'with'.
- L2551 _public member_ `SText CallWhat;`
- L2552 _public member_ `SCursor CallTrailingStop;`
- L2553 _public member_ `EMode CallMode;`
- L2554 _public member_ `SBlockInternal& CallParameter;`
- L2555 _public member_ `SCall* OuterCall = nullptr;` — Initialized to keep static analysis happy

#### struct `Verse::Grammar::CParser::SInvoke`  
`struct SInvoke : SExpr`  
_L2557-2660_
- inherits: `SExpr`
- L2559 _public member_ `SText What;`
- L2560 _public member_ `SToken StartToken;`
- L2561 _public member_ `STokenSet InTokens, PostTokens;`
- L2561 _public member_ `STokenSet InTokens, PostTokens;`
- L2562 _public member_ `SCall *FirstCall, *LastCall;`
- L2562 _public member_ `SCall *FirstCall, *LastCall;`
- L2563 _public member_ `SCall* Of;`
- L2564 _public member_ `SBlockInternal* Clauses[3];`
- L2565 _public member_ `SBlockInternal* PriorClause;`
- L2566 _public function_ `SInvoke(SText What0, SExpr& OuterExpr0, SCursor Start0, SToken StartToken0, STokenSet InTokens0, STokenSet PostTokens0, SCall* FirstCall0 = nullptr, SCall* LastCall0 = nullptr) : SExpr(EPrec::Base, Start0, &OuterExpr0, OuterExpr0.MarkupStart ? InvokePostfixes | MarkupPostfixes : InvokePostfixes) , What(What0) , StartToken(StartToken0) , InTokens(InTokens0) , PostTokens(PostTokens0) , FirstCall(FirstCall0) , LastCall(LastCall0) , Of(nullptr) , Clauses`
- L2581 _public function_ `void UpdateLastCall(SCall* NewCall)`
- L2589 _public function_ `ResultOf<SNothing> OnFinish(CParser& Parser) override`

#### struct `Verse::Grammar::CParser::SIns`  
`struct SIns`  
_L3139-3146_
- desc: Expressions.
- L3141 _public member_ `SCursor Start;`
- L3142 _public member_ `SToken InToken;`
- L3143 _public member_ `SCursor NextStart;`
- L3144 _public member_ `CaptureType NextLeading;`
- L3145 _public member_ `const SIns* NextIns;`

#### struct `Verse::Grammar::CParser::SWhenExpr`  
`template <class CallableType> struct SWhenExpr : SExpr`  
_L3946-3982_
- inherits: `SExpr`
- L3948 _public typedef_ `using ResultType = decltype((*(CallableType*)nullptr)(*(SExpr*)nullptr));`
- L3949 _public member_ `CallableType _Func;`
- L3950 _public member_ `ResultType Result;`
- L3951 _public function_ `SWhenExpr(EPrec FinishPrec0, SExpr* OuterExpr0, STokenSet PostfixAllow0, const SCursor& Start0, const CaptureType& ExprLeading0, const CallableType& Callable0, SExpr* QualIdentTarget0 = nullptr) : SExpr(FinishPrec0, Start0, OuterExpr0, PostfixAllow0, QualIdentTarget0) , _Func(Callable0)`
- L3960 _public function_ `ResultOf<SNothing> Parse(CParser& Parser, SText What, EPrec ParsePrec, ErrorType (CParser::*OnTokenError)(SText), ErrorType (CParser::*OnPrecError)(SText, SText))`
- L3974 _public function_ `ResultOf<SNothing> OnFinish(CParser& Parser) override`

#### struct `Verse::Grammar::TGenerate`  
`template <class GeneratorType> struct TGenerate : GeneratorType`  
_L4161-4418_
- inherits: `GeneratorType`
- L4163 _public typedef_ `using SyntaxType = typename GeneratorType::SyntaxType;`
- L4164 _public typedef_ `using SyntaxesType = typename GeneratorType::SyntaxesType;`
- L4165 _public typedef_ `using ErrorType = typename GeneratorType::ErrorType;`
- L4166 _public typedef_ `using CaptureType = typename GeneratorType::CaptureType;`
- L4167 _public typedef_ `using SBlockInternal = SBlock<SyntaxesType, CaptureType>;`
- L4169 _public typedef_ `template <class ResultValueType> using ResultOf = TResult<ResultValueType, ErrorType>;`
- L4173 _public function_ `template <class... ArgTypes> TGenerate(const ArgTypes&... Args) : GeneratorType(Args...)` — Passthrough constructor.
- L4179 _public function_ `Units(const SSnippet& Snippet, const SyntaxType& Num, SText Units) const`
- L4188 _public function_ `ResultOf<SyntaxType> Parenthesis(const SBlockInternal& Block) const`
- L4198 _public function_ `ResultOf<SyntaxType> StringInterpolate(const SSnippet& Snippet, EPlace Place, bool , const SBlockInternal& Block) const`
- L4209 _public function_ `ResultOf<SyntaxType> String(const SSnippet& Snippet, const SyntaxesType& Splices) const`
- L4221 _public function_ `ResultOf<SyntaxType> Content(const SSnippet& Snippet, const SyntaxesType& Splices) const`
- L4226 _public function_ `ResultOf<SyntaxType> Contents(const SSnippet& Snippet, const CaptureType& , const SyntaxesType& Splices) const`
- L4235 _public function_ `InvokeMarkup(const SSnippet& Snippet, SText , const CaptureType& , const SyntaxType& Macro, SBlockInternal* Clause, SBlockInternal* DoClause, const CaptureType& , const CaptureType& , const SyntaxType& Content, const CaptureType& ) const`
- L4260 _public function_ `PrefixToken(const SSnippet& Snippet, EMode Mode, SText Symbol, const SBlockInternal& Block, bool Lift, const SyntaxesType& = {}) const`
- L4278 _public function_ `ResultOf<SyntaxType> PrefixBrackets(const SSnippet& Snippet, const SBlockInternal& Left, const SBlockInternal& Right) const`
- L4300 _public function_ `ResultOf<SyntaxType> PostfixToken(const SSnippet& Snippet, EMode Mode, const SyntaxType& Left, SText Symbol) const`
- L4315 _public function_ `ResultOf<SyntaxType> InfixToken(const SSnippet& Snippet, EMode Mode, const SyntaxType& Left, SText Symbol, const SyntaxType& Right) const`
- L4334 _public function_ `ResultOf<SyntaxType> InfixBlock(const SSnippet& Snippet, const SyntaxType& LeftSyntax, SText Symbol, const SBlockInternal& Right) const`
- L4346 _public function_ `SyntaxType Leading(const CaptureType& , const SyntaxType& Syntax) const`
- L4351 _public function_ `SyntaxType Trailing(const SyntaxType& Syntax, const CaptureType& ) const`
- L4356 _public function_ `TResult<SyntaxType, ErrorType> File(const SBlockInternal& Block) const`
- L4364 _public function_ `void Text(CaptureType& Capture, const SSnippet& Snippet, EPlace Place) const` — String callbacks that can contribute to abstract syntax. In all string callbacks, every non-empty Snippet's text span is guaranteed to be inside the parser's input string.
- L4369 _public function_ `void NewLine(CaptureType& Capture, const SSnippet& , EPlace Place) const`
- L4380 _public function_ `void StringBackslash(CaptureType& Capture, const SSnippet& , EPlace Place, char8_t Backslashed) const`
- L4397 _public function_ `void LineCmt(CaptureType& , const SSnippet& , EPlace , const CaptureType& ) const` — Optional string callbacks which don't contribute to abstract syntax.
- L4399 _public function_ `void BlockCmt(CaptureType& , const SSnippet& , EPlace , const CaptureType& ) const`
- L4401 _public function_ `void IndCmt(CaptureType& , const SSnippet& , EPlace , const CaptureType& ) const`
- L4403 _public function_ `void Indent(CaptureType& , const SSnippet& , EPlace ) const`
- L4405 _public function_ `void BlankLine(CaptureType& , const SSnippet& , EPlace ) const`
- L4407 _public function_ `void Semicolon(CaptureType& , const SSnippet& ) const`
- L4409 _public function_ `void MarkupTrim(CaptureType& Capture) const`
- L4410 _public function_ `void MarkupStart(CaptureType& , const SSnippet& ) const`
- L4412 _public function_ `void MarkupTag(CaptureType& , const SSnippet& ) const`
- L4414 _public function_ `void MarkupStop(CaptureType& , const SSnippet& ) const`
- L4416 _public function_ `void LinePrefix(CaptureType& , const SSnippet& ) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L13 _namespace_ `namespace Grammar` (scope `Verse`)
- L17 _macro_ `#define VERSE_MAX_EXPR_DEPTH 100`
- L21 _macro_ `#define VERSE_MAX_INDCMT_DEPTH 3`
- L25 _macro_ `#define ULANG_GRAMMAR_RUN(e) \` — Macros.
- L31 _macro_ `#define ULANG_GRAMMAR_SET(r, e) \`
- L38 _macro_ `#define ULANG_GRAMMAR_LET(r, e) \`
- L46 _function_ `template <class ElementType, uint64_t ArrayLength> constexpr uint64_t ArraySize(ElementType (&)[ArrayLength])` (scope `Verse::Grammar`) — Basic functions.
- L191 _function_ `constexpr uint64_t Length(const SText& Text)` (scope `Verse::Grammar`)
- L195 _function_ `inline bool operator==(const SText& as, const SText& bs)` (scope `Verse::Grammar`)
- L204 _function_ `inline bool operator!=(const SText& as, const SText& bs)` (scope `Verse::Grammar`)
- L332 _member_ `ValueType Value;` (scope `Verse::Grammar::TResult::__anonb394e38a010a`)
- L333 _member_ `ErrorType Error;` (scope `Verse::Grammar::TResult::__anonb394e38a010a`)
- L342 _function_ `constexpr bool IsSpace(char8_t c)` (scope `Verse::Grammar`) — Verse grammar character classification functions.
- L346 _function_ `constexpr bool IsNewLine(char8_t c)` (scope `Verse::Grammar`)
- L350 _function_ `constexpr bool IsEnding(char8_t c)` (scope `Verse::Grammar`)
- L354 _function_ `constexpr bool IsAlpha(char8_t c)` (scope `Verse::Grammar`)
- L358 _function_ `constexpr bool IsDigit(char8_t c)` (scope `Verse::Grammar`)
- L362 _function_ `constexpr bool IsAlnum(char8_t c)` (scope `Verse::Grammar`)
- L366 _function_ `constexpr bool IsHex(char8_t c)` (scope `Verse::Grammar`)
- L370 _function_ `constexpr uint8_t DigitValue(char8_t c)` (scope `Verse::Grammar`)
- L377 _function_ `constexpr bool IsIdentifierQuotable(char8_t c0, char8_t c1)` (scope `Verse::Grammar`)
- L381 _function_ `constexpr bool IsStringBackslashLiteral(char8_t c0, char8_t c1)` (scope `Verse::Grammar`)
- L387 _function_ `inline char32_t EncodedChar32(const char8_t* s, uint64_t Count)` (scope `Verse::Grammar`) — Convert valid UTF-8 sequence with valid length to its Unicode Code Point.
- L417 _function_ `template <EPlace Place> uint64_t EncodedLength(const char8_t* const S)` (scope `Verse::Grammar`) — Get length of internal lexical unit recognized for Place. U8        := 0o80..0oBF UTF8      :=                                      0o00..0o7F |                                       0oC2..0oDF U8 |  !(0oE0 0o80..0o9F | 0oED 0oA0..0oBF) 0oE0..0oEF U8 U8 |  !(0oF0 0o80..0o8F | 0oF4 0o90..0oBF) 0oF0..0oF4 U8 U8 U8 Printable := 0o09 | !("<#" | "#>" | 0o0..0o1F | 0o7F | 0oC2 0o80..0o9F | 0oE2 0o80 0oA8..0oA9 ) UTF8 | .. Special   := '\'|'{'|'}'|'#'|'<'|'>'|'&'|'~' String    := .. !('\'|'{'|'}'|'"') Text .. Content   := .. !Special Text ..
- L426 _function_ `JumpTableFunctionType ReturnOne = [](const char8_t* const) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L433 _function_ `JumpTable[Index] = [](const char8_t* const) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L462 _function_ `JumpTable[static_cast<int>('<')] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L473 _function_ `JumpTable[static_cast<int>('#')] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L501 _function_ `JumpTable[0xC2] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L509 _function_ `JumpTable[Index] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L516 _function_ `JumpTable[0xE0] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L522 _function_ `JumpTable[0xE2] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L537 _function_ `JumpTable[0xED] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L543 _function_ `JumpTable[0xF0] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L558 _function_ `JumpTable[0xF4] = [](const char8_t* const S) -> uint64_t` (scope `Verse::Grammar::EncodedLength::SJumpTable::SJumpTable`)
- L592 _function_ `inline bool ParenthesizePrefix(const SEncoding& Encoding, EPrec StringPrec)` (scope `Verse::Grammar`)
- L596 _function_ `inline bool ParenthesizePostfix(const SEncoding& Encoding, EPrec StringPrec)` (scope `Verse::Grammar`)
- L605 _externvar_ `extern const struct STokenSet AllTokens, AllowLess, AllowNotEq;` (scope `Verse::Grammar`) — Forward declared tokens.
- L605 _externvar_ `extern const struct STokenSet AllTokens, AllowLess, AllowNotEq;` (scope `Verse::Grammar`) — Forward declared tokens.
- L605 _externvar_ `extern const struct STokenSet AllTokens, AllowLess, AllowNotEq;` (scope `Verse::Grammar`) — Forward declared tokens.
- L645 _variable_ `constexpr STokenInfo Tokens[] = { { u8"", EPrec::Never, EMode::None, EPrec::Never, EPrec::Never,EAssoc::None, EMode::None, AllTokens },` (scope `Verse::Grammar`)
- L2186 _function_ `u8"&", EPrec::Def, EPrec::Def, nullptr, Leading, [&](SExpr& Expr) -> ResultOf<SBlockInternal>` (scope `Verse::Grammar::CParser::Ampersand`)
- L2387 _function_ `return WhenExpr(What, EPrec::Def, EPrec::Def, &OuterExpr, Middle, [&](SExpr& Right) -> ResultOf<SBlockInternal> { return SingletonBlock(BlockStart, Right, PunctuationLeading, EPunctuation::Dot); });` (scope `Verse::Grammar::CParser::BlockHelper`) — if(Ending()) return IndList(BlockStart,PunctuationLeading,EPunctuation::Dot,MiddleStart,Middle);
- L2418 _function_ `return WhenExpr(What, Prec, Prec, &OuterExpr, PunctuationLeading, [&](SExpr& Right) -> ResultOf<SBlockInternal> { return SingletonBlock(BlockStart, Right); });` (scope `Verse::Grammar::CParser::BlockHelper`)
- L2492 _function_ `return WhenExpr(What, Prec, Prec, &OuterExpr, PunctuationLeading, [&](SExpr& RightExpr) -> ResultOf<SNothing> { auto RightBlock = SingletonBlock(BlockStart, RightExpr); return Func(RightBlock); });` (scope `Verse::Grammar::CParser::WhenBraceCall`)
- L2777 _function_ `SWhenExpr(EPrec::Less, &Target, AllowLess, Cursor, Leading, [&](SExpr& LessExpr) -> ResultOf<SNothing> {` (scope `Verse::Grammar::CParser::InvokeLess`)
- L2792 _function_ `u8"<", EPrec::Choose, EPrec::Less, &LessExpr, CaptureType(), [&](SExpr& RightExpr) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::InvokeLess`)
- L2889 _function_ `SWhenExpr(EPrec::Base, &Target, AllTokens, BlockStart, TokenLeading, [&](SExpr& CatchExpr) -> ResultOf<SNothing> { auto Block0 = SingletonBlock(BlockStart, CatchExpr); return InvokeClause(Target, 2, BlockStart, Block0, *CatchExpr.Finished); });` (scope `Verse::Grammar::CParser::InvokeCatch`)
- L2923 _function_ `u8"else if", EPrec::Base, EPrec::Base, &Target, PunctuationLeading, [&](SExpr& ElseExpr) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::InvokeElse`)
- L3168 _function_ `InToken->Symbol, EPrec::Choose, EPrec::Choose, &PostfixExpr, CaptureType(), [&](SExpr& Right) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::InChoose`)
- L3238 _function_ `SWhenExpr(EPrec::Expr, &Target, AllTokens, Cursor, CaptureType(), [&](SExpr& RightExpr) { return UpdateFrom(Target, RightExpr.Trailing, Gen.PrefixAttribute( SnipFinished(Target.Start, RightExpr), *AttrSyntax, *RightExpr)); });` (scope `Verse::Grammar::CParser::Attribute`)
- L3249 _function_ `u8"@", EPrec::Call, EPrec::Prefix, nullptr, AttrLeading, [&](SExpr& AttrExpr) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::Attribute`)
- L3289 _function_ `EPrec::Def, &Target, AllTokens, Cursor, CaptureType(), [&](SExpr& PostfixExpr) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::In`)
- L3330 _function_ `ULANG_GRAMMAR_RUN(WhenExpr(u8"<", EPrec::Choose, EPrec::Less, &Target, StartingSpace, [&](SExpr& Expr) -> ResultOf<SNothing> { ApplyTrailing(Expr, true); Gen.SyntaxesAppend(Attributes, *Expr); return SNothing{}; }));` (scope `Verse::Grammar::CParser::VarKeyword`)
- L3353 _function_ `BaseToken->Symbol, EPrec::Choose, EPrec::Choose, &Target, Middle, [&](SExpr& Choose) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::VarKeyword`)
- L3377 _function_ `BaseToken->Symbol, BaseToken->PrefixPrec, BaseToken->PrefixPrec, &Target, Middle, [&](SExpr& RightExpr)` (scope `Verse::Grammar::CParser::Not`)
- L3395 _function_ `u8"&", BaseToken->PrefixPrec, BaseToken->PrefixPrec, &Target, Middle, [&](SExpr& Right)` (scope `Verse::Grammar::CParser::Ampersand`)
- L3409 _function_ `BaseToken->Symbol, BaseToken->PrefixPrec, Target, [&](SBlockInternal& RightBlock) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::Arithmetic`)
- L3429 _function_ `u8"[]", BaseToken->PrefixPrec, Target, [&](SBlockInternal& Right) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::LeftBracket`)
- L3608 _function_ `PostfixToken->Symbol, PostfixToken->PostfixRightPrec(), PostfixToken->PostfixRightPrec(), &Target, Leading, [&](SExpr& Right) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::PostfixBinaryOperator`)
- L3652 _function_ `return WhenExpr(PostfixToken->Symbol, EPrec::Call, EPrec::Call, &Target, Leading, [&](SExpr& Right) -> ResultOf<SNothing> { return UpdateFrom(Target, Right.Trailing, Gen.PostfixAttribute( SnipFinished(Target.Start, Right), ApplyTrailing(Target), *Right)); });` (scope `Verse::Grammar::CParser::PostfixAttribute`)
- L3758 _function_ `WhenExpr(PostfixToken->Symbol, EPrec::Def, EPrec::Def, &Target, CaptureType(), [&](SExpr& InExpr) { auto InBlock = SingletonBlock(InExpr.Start, InExpr); return UpdateFrom( Target, InBlock.BlockTrailing, Gen.InfixBlock(SnipFinished(Target.Start, InExpr), ApplyTrailing(Target), u8"", InBlock)); }));` (scope `Verse::Grammar::CParser::PostfixMacroInvoke`)
- L4010 _function_ `auto Expr = SWhenExpr(EPrec::Call, nullptr, AllTokens, Cursor, Leading, [&](SExpr& Expr) -> ResultOf<SNothing> { Expr.Trailing = STrailing{}; return SNothing{}; });` (scope `Verse::Grammar::CParser::MarkupExpr`)
- L4035 _function_ `What, Prec, Prec, nullptr, Leading, [&](SExpr& Expr) -> ResultOf<SNothing>` (scope `Verse::Grammar::CParser::Commas`)
- L4425 _function_ `File(GeneratorType& Gen, uint64_t n, const char8_t* s, uint64_t Line = 1)` (scope `Verse::Grammar`)

### `Source/Runtime/VerseCompiler/Public/uLang/SemanticAnalyzer/DigestGenerator.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L17 _namespace_ `namespace DigestGenerator` (scope `uLang`)
- L21 _prototype_ `bool Generate( CSemanticProgram& Program, const CAstPackage& Package, bool bIncludeInternalDefinitions, bool bIncludeEpicInternalDefinitions, const TSRef<CDiagnostics>& Diagnostics, const CUTF8String* Notes, CUTF8String& OutDigestCode, TArray<const CAstPackage*>& OutDigestPackageDependencies);` (scope `uLang::DigestGenerator`) — Generates a text digest for a given program and a package within it

### `Source/Runtime/VerseCompiler/Public/uLang/SemanticAnalyzer/IRGenerator.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace uLang`
- L22 _prototype_ `bool GenerateIr(const TSRef<CSemanticProgram>& Program, const TSRef<CDiagnostics>& Diagnostics, SBuildParams::EWhichVM TargetVM);` (scope `uLang`) — Stand-alone IR generator, use _AstProject to fill in _IrProject in CSemanticProgram

### `Source/Runtime/VerseCompiler/Public/uLang/SemanticAnalyzer/IRGeneratorPass.h` (Public)


#### class `uLang::CIrGeneratorPass`  
`class CIrGeneratorPass : public IIrGeneratorPass`  
_L13-48_
- inherits: `IIrGeneratorPass`
- desc: Generates an IR from the Ast in the CSemanticProgram. The CSemanticProgram is updated with the generated IR.
- L17 _public function_ `~CIrGeneratorPass()`
- L22 _public function_ `virtual void Initialize(const SBuildContext& BuildContext, const SProgramContext& ProgramContext) override`
- L30 _public function_ `virtual void CleanUp(void) override`
- L37 _public function_ `virtual void ProcessAst() const override`
- L45 _private member_ `TSPtr<CSemanticProgram> _Program;`
- L46 _private member_ `TSPtr<CDiagnostics> _Diagnostics;`
- L47 _private member_ `SBuildParams::EWhichVM _TargetVM;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SemanticAnalyzer/SemanticAnalyzer.h` (Public)


#### class `uLang::CSemanticAnalyzer`  
`class CSemanticAnalyzer`  
_L24-36_
- desc: Stand-alone semantic analyzer, converts from a syntax program to a semantic program
- L27 _public prototype_ `CSemanticAnalyzer(const TSRef<CSemanticProgram>&, const SBuildContext&);`
- L28 _public prototype_ `~CSemanticAnalyzer();`
- L30 _public prototype_ `bool ProcessVst(const Verse::Vst::Project& Vst, const ESemanticPass Stage) const;`
- L32 _public prototype_ `const TSRef<CSemanticProgram>& GetSemanticProgram() const;`
- L35 _private member_ `TURef<CSemanticAnalyzerImpl> _SemaImpl;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L11 _namespace_ `namespace Vst` (scope `Verse`)
- L13 _namespace_ `namespace uLang`
- L19 _variable_ `constexpr int32_t MaxNumPersistentVarsDefault = 4;` (scope `uLang`)
- L21 _variable_ `constexpr int32_t MaxNumConcreteEntitlementSubclassesDefault = 100;` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/SemanticAnalyzer/SemanticAnalyzerPass.h` (Public)


#### class `uLang::CSemanticAnalyzerPass`  
`class CSemanticAnalyzerPass : public ISemanticAnalyzerPass`  
_L13-44_
- inherits: `ISemanticAnalyzerPass`
- desc: Converts a CSyntaxProgram to a CSemanticProgram and identifies any semantic issues
- L17 _public function_ `~CSemanticAnalyzerPass()`
- L22 _public function_ `virtual void Initialize(const SBuildContext& BuildContext, const SProgramContext& ProgramContext) override`
- L28 _public function_ `virtual void CleanUp(void) override`
- L34 _public function_ `virtual TSRef<CSemanticProgram> ProcessVst(const Verse::Vst::Project& Vst, const ESemanticPass Pass) const override`
- L43 _private member_ `TUPtr<CSemanticAnalyzer> _Context;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/AccessLevel.h` (Public)


#### struct `uLang::SAccessLevel`  
`struct SAccessLevel`  
_L14-69_
- desc: Mostly a wrapper around SAccessLevel::EKind with the addition of an optional list of modules for the 'scoped' access level
- L33 _public member_ `EKind _Kind;`
- L37 _public member_ `uLang::TArray<const CScope*> _Scopes;` — Only used when _Kind == SAccessLevel::EKind::Scoped Access is considered internal to all listed scopes.
- L39 _public function_ `SAccessLevel() : _Kind(SAccessLevel::EKind::Internal)`
- L42 _public function_ `SAccessLevel(SAccessLevel::EKind Kind) : _Kind(Kind)`
- L45 _public prototype_ `SAccessLevel(const SAccessLevel&) = default;`
- L46 _public prototype_ `SAccessLevel& operator=(const SAccessLevel&) = default;`
- L54 _public prototype_ `CUTF8String AsCode() const;`
- L56 _public function_ `static const char* KindAsCString(SAccessLevel::EKind AccessLevelKind)`

#### enum `uLang::SAccessLevel::EKind`  
`enum class EKind : int8_t`  
_L16-31_
- L19 _public enumerator_ `Public` — Unrestricted access
- L21 _public enumerator_ `Internal` — Access limited to current module (default)
- L23 _public enumerator_ `Protected` — Access limited to current class and any subclasses
- L25 _public enumerator_ `Private` — Access limited to current class
- L27 _public enumerator_ `Scoped` — Access is internal to a code-specified list of module references
- L30 _public enumerator_ `EpicInternal` — Access limited to Epic code.  This is a temporary access level to be replaced by `scoped` access

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L48 _function_ `friend bool operator!=(const SAccessLevel& Lhs, const SAccessLevel& Rhs)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/AccessibilityScope.h` (Public)


#### struct `uLang::SDigestScope`  
`struct SDigestScope`  
_L18-22_
- L20 _public member_ `bool bEpicInternal{false};`
- L21 _public member_ `bool bInternal{false};`

#### struct `uLang::SAccessibilityScope`  
`struct SAccessibilityScope`  
_L24-56_
- L33 _public member_ `EKind _Kind{ EKind::Universal };`
- L34 _public member_ `TArray<const CScope*> _Scopes;`
- L35 _public member_ `const CTypeBase* _SuperType{ nullptr };`
- L37 _public function_ `bool IsUniversal() const`
- L38 _public function_ `bool IsEpicInternal() const`
- L40 _public function_ `bool IsVisibleInDigest(SDigestScope DigestScope) const`
- L52 _public function_ `bool IsMoreAccessibleThan(const SAccessibilityScope& Other, const uint32_t UploadedAtFnVersion) const`
- L53 _public function_ `bool IsLessAccessibleThan(const SAccessibilityScope& Other, const uint32_t UploadedAtFnVersion) const`
- L54 _public prototype_ `bool IsSubsetOf(const SAccessibilityScope& Other, const uint32_t UploadedAtFnVersion) const;`
- L55 _public prototype_ `CUTF8String Describe() const;`

#### enum `uLang::SAccessibilityScope::EKind`  
`enum class EKind`  
_L26-31_
- L28 _public enumerator_ `Universal`
- L29 _public enumerator_ `EpicInternal`
- L30 _public enumerator_ `Scope`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L58 _prototype_ `SAccessibilityScope GetAccessibilityScope(const CDefinition& Definition, const SAccessLevel& InitialAccessLevel);` (scope `uLang`)
- L59 _prototype_ `SAccessibilityScope GetAccessibilityScope(const CDefinition& Definition);` (scope `uLang`)
- L61 _prototype_ `SAccessibilityScope GetConstructorAccessibilityScope(const CClassDefinition& Class);` (scope `uLang`)
- L62 _prototype_ `SAccessibilityScope GetConstructorAccessibilityScope(const CInterface& Interface);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/AstPrinter.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L12 _prototype_ `CUTF8String PrintAst(const CSemanticProgram& Program, const CAstNode& RootNode);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Attributable.h` (Public)


#### struct `uLang::SAttribute`  
`struct SAttribute`  
_L19-31_
- L27 _public member_ `TSRef<CExpressionBase> _Expression;`
- L28 _public member_ `EType _Type;`
- L30 _public prototype_ `TOptional<CUTF8String> GetTextValue() const;`

#### enum `uLang::SAttribute::EType`  
`enum class EType`  
_L21-25_
- L23 _public enumerator_ `Attribute` — Attribute which is used with prefix @attr syntax
- L24 _public enumerator_ `Specifier` — Attribute which is used with suffix <spec> syntax

#### class `uLang::CAttributable`  
`class CAttributable`  
_L50-114_
- desc: Base class for everything that can have attributes attached to it (classes, expressions, etc.)
- L53 _public member_ `TArray<SAttribute> _Attributes;`
- L55 _public function_ `bool HasAttributes() const`
- L56 _public prototype_ `bool HasAttributeClass(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L57 _public prototype_ `bool HasAttributeSubclass(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L59 _public prototype_ `int32_t GetAttributeClassCount(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L61 _public prototype_ `TArray<const CExpressionBase*> GetAttributesWithAttribute(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L63 _public prototype_ `const CExpressionBase* FindAttributeExpr(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L64 _public prototype_ `const CExpressionBase* FindAttributeSubclassExpr(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L65 _public prototype_ `const TArray<CExpressionBase*> FindAttributeExprs(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L66 _public prototype_ `const TArray<CExpressionBase*> FindAttributeSubclassExprs(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L68 _public prototype_ `TOptional<SAttribute> FindAttribute(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L69 _public prototype_ `TOptional<SAttribute> FindAttributeHack(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L70 _public prototype_ `TArray<SAttribute> FindAttributes(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L72 _public prototype_ `void AddAttributeClass(const CClass* AttributeClass);`
- L73 _public prototype_ `void AddAttribute(SAttribute Attribute);`
- L74 _public prototype_ `void RemoveAttributeClass(const CClass* AttributeClass, const CSemanticProgram& Program);`
- L77 _public prototype_ `TOptional<CUTF8String> GetAttributeTextValue(const CClass* AttributeClass, const CSemanticProgram& Program) const;` — @HACK: SOL-972, We need full proper support for compile-time evaluation of attribute types
- L78 _public prototype_ `static TOptional<CUTF8String> GetAttributeTextValue(const TArray<SAttribute>& Attributes, const CClass* AttributeClass, const CSemanticProgram& Program);`
- L100 _public prototype_ `CAttributable& operator=(const CAttributable& Other) = delete;`
- L101 _public prototype_ `CAttributable& operator=(CAttributable&& Other) = delete;`
- L103 _public prototype_ `bool HasAttributeClassHack(const CClass* AttributeClass, const CSemanticProgram&) const;`
- L104 _public prototype_ `bool HasAttributeFunctionHack(const CFunction* AttributeFunction, const CSemanticProgram&) const;`
- L109 _private prototype_ `template<EFindAttributeMode Mode> bool IsAttributeClassImpl(const SAttribute& Attr, const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L111 _private prototype_ `template<EFindAttributeMode Mode> TOptional<int32_t> FindAttributeImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L113 _private prototype_ `template<EFindAttributeMode Mode> TArray<int32_t> FindAttributesImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const;`

#### enum `uLang::CAttributable::EAttributableScope`  
`enum class EAttributableScope : uint8_t`  
_L81-98_
- desc: Specifies the attribute scope for expressions (e.g. should only respect class-scoped attributes, etc.)
- L83 _public enumerator_ `Module`
- L84 _public enumerator_ `Class`
- L85 _public enumerator_ `Struct`
- L86 _public enumerator_ `Data`
- L87 _public enumerator_ `Function`
- L88 _public enumerator_ `Enum`
- L89 _public enumerator_ `Enumerator`
- L90 _public enumerator_ `AttributeClass`
- L91 _public enumerator_ `Interface`
- L92 _public enumerator_ `Expression`
- L93 _public enumerator_ `TypeDefinition`
- L94 _public enumerator_ `ScopedAccessLevel`
- L95 _public enumerator_ `ClassTypeFunction`
- L96 _public enumerator_ `AttributeClassTypeFunction`
- L97 _public enumerator_ `InterfaceTypeFunction`

#### enum `uLang::CAttributable::EFindAttributeMode`  
`enum class EFindAttributeMode`  
_L107-107_
- L107 _public enumerator_ `enum class EFindAttributeMode { Exact, IncludeSubtypes }; template<EFindAttributeMode Mode> bool IsAttributeClassImpl(const SAttribute& Attr, const CClass* AttributeClass, const CSemanticProgram& Program) const; template<EFindAttributeMode Mode> TOptional<int32_t> FindAttributeImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const; template<EFindAttributeMode Mode> TArray<int32_t> FindAttributesImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const;`
- L107 _public enumerator_ `enum class EFindAttributeMode { Exact, IncludeSubtypes }; template<EFindAttributeMode Mode> bool IsAttributeClassImpl(const SAttribute& Attr, const CClass* AttributeClass, const CSemanticProgram& Program) const; template<EFindAttributeMode Mode> TOptional<int32_t> FindAttributeImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const; template<EFindAttributeMode Mode> TArray<int32_t> FindAttributesImpl(const CClass* AttributeClass, const CSemanticProgram& Program) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API VERSECOMPILER_API`
- L12 _namespace_ `namespace uLang`
- L33 _prototype_ `bool IsAttributeHack(const SAttribute&, const CClass* AttributeClass, const CSemanticProgram&);` (scope `uLang`)
- L34 _prototype_ `bool IsAttributeHack(const SAttribute&, const CFunction* AttributeFunction, const CSemanticProgram&);` (scope `uLang`)
- L37 _function_ `template <typename TIterator, typename ClassOrFunction> TIterator FindAttributeHack(TIterator First, TIterator Last, const ClassOrFunction* AttributeClassOrFunction, const CSemanticProgram& Program)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/AvailableAttributeUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`
- L17 _prototype_ `TOptional<uint64_t> GetAvailableAttributeVersion(const SAttribute& AvailableAttribute, const CSemanticProgram& SemanticProgram);` (scope `uLang`)
- L18 _prototype_ `TOptional<uint64_t> GetAvailableAttributeVersion(const CDefinition& Definition, const CSemanticProgram& SemanticProgram);` (scope `uLang`)
- L19 _prototype_ `TOptional<uint64_t> CalculateCombinedAvailableAttributeVersion(const CDefinition& Definition, const CSemanticProgram& SemanticProgram);` (scope `uLang`)
- L20 _prototype_ `bool IsDefinitionAvailableAtVersion(const CDefinition& Definition, uint64_t Version, const CSemanticProgram& SemanticProgram);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/CaptureControlScope.h` (Public)


#### class `uLang::CCaptureControlScope`  
`class CCaptureControlScope : public CControlScope, public CCaptureScope`  
_L11-27_
- inherits: `CControlScope,CCaptureScope`
- L14 _public function_ `CCaptureControlScope(CScope* Parent, CSemanticProgram& Program) : CControlScope`
- L19 _public function_ `virtual CScope* AsScope() override`
- L21 _public function_ `virtual const CCaptureScope* AsCaptureScopeNullable() const override`
- L23 _public function_ `virtual CCaptureScope* GetParentCaptureScope() const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/CaptureScope.h` (Public)


#### class `uLang::CCaptureScope`  
`class CCaptureScope`  
_L13-68_
- L16 _public prototype_ `virtual ~CCaptureScope() = default;`
- L18 _public prototype_ `virtual CScope* AsScope() = 0;`
- L20 _public prototype_ `virtual CCaptureScope* GetParentCaptureScope() const = 0;`
- L22 _public function_ `bool HasEmptyTransitiveCaptures() const`
- L27 _public function_ `uint32_t NumCaptures() const`
- L32 _public function_ `TArray<const CDefinition*> GetCaptures() const`
- L42 _public function_ `const uint32_t* GetCapture(const CDefinition& Definition) const`
- L50 _public prototype_ `void MaybeAddCapture(const CDefinition&);` — Add a definition to the captures of the ancestor capture scope where the argument definition is free, but not free in the ancestor capture scopes's enclosing capture scope.
- L52 _public prototype_ `void AddAncestorCapture(const CDefinition& Definition, const CCaptureScope& DefinitionCaptureScope);`
- L55 _private function_ `void AddCapture(const CDefinition& Definition)`
- L63 _private member_ `bool _bEmptyTransitiveCaptures{true};` — `true` if this capture scope or any enclosed capture scope references definitions free in this capture scope, i.e. if the corresponding function needs a valid scope.
- L67 _private member_ `TMap<const CDefinition*, uint32_t> _Captures;` — Definitions free in this capture scope and not free in the enclosing capture scope.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/ControlScope.h` (Public)


#### class `uLang::CControlScope`  
`class CControlScope : public CLogicalScope, public CSharedMix`  
_L14-27_
- inherits: `CLogicalScope,CSharedMix`
- desc: Represents a function body or a nested scope within a function body.
- L17 _public function_ `CControlScope(CScope* Parent, CSemanticProgram& Program) : CLogicalScope`
- L23 _public function_ `virtual CSymbol GetScopeName() const override`
- L26 _public function_ `virtual const CCaptureScope* AsCaptureScopeNullable() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/DataDefinition.h` (Public)


#### struct `uLang::SClassVarAccessorFunctions`  
`struct SClassVarAccessorFunctions`  
_L26-38_
- L28 _public member_ `TMap<int, const CFunction*> Getters;`
- L29 _public member_ `TMap<int, const CFunction*> Setters;`
- L31 _public member_ `CSymbol GetterName;`
- L32 _public member_ `CSymbol SetterName;`
- L34 _public function_ `explicit operator bool() const`

#### enum `uLang::EPersistenceExternalAccess`  
`enum struct EPersistenceExternalAccess : std::uint8_t`  
_L41-47_
- desc: The enumerator values must match `Verse::EPersistenceExternalAccess`.
- L43 _public enumerator_ `Internal = 0`
- L44 _public enumerator_ `Read = 1 << 0`
- L45 _public enumerator_ `Write = 1 << 1`
- L46 _public enumerator_ `ReadWrite = Read | Write`

#### class `uLang::CDataDefinition`  
`class CDataDefinition : public CDefinition`  
_L64-232_
- inherits: `CDefinition`
- desc: Joining structure, making data-members attributable.
- L67 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Data;`
- L70 _public member_ `bool _bNamed = false;` — Named member - must be explicitly ?named rather than determined by index
- L73 _public member_ `const CTypeBase* _NegativeType = nullptr;` — The type of this data definition in the negative position.
- L77 _public member_ `const CTypeVariable* _ImplicitParam = nullptr;` — A parameter `X` of type `type` is encoded as `:type(X, X) where X:type`. `_ImplicitParam` points to the corresponding type variable.
- L79 _public function_ `CDataDefinition(const CSymbol& IdentName, CScope& EnclosingScope) : CDataDefinition(IdentName, EnclosingScope, nullptr)`
- L84 _public function_ `CDataDefinition(const CSymbol& IdentName, CScope& EnclosingScope, const CTypeBase* Type) : CDefinition(StaticDefinitionKind, EnclosingScope, IdentName) , _Type(Type)`
- L91 _public function_ `void SetPrototypeDefinition(const CDataDefinition& PrototypeDefinition)` — CDefinition interface.
- L92 _public function_ `const CDataDefinition* GetPrototypeDefinition() const`
- L94 _public prototype_ `void SetAstNode(CExprDefinition* AstNode);`
- L95 _public prototype_ `CExprDefinition* GetAstNode() const;`
- L97 _public prototype_ `void SetIrNode(CExprDefinition* AstNode);`
- L98 _public prototype_ `CExprDefinition* GetIrNode(bool bForce = false) const;`
- L100 _public prototype_ `bool IsNativeRepresentation() const;`
- L102 _public function_ `void SetType(const CTypeBase* Type)`
- L103 _public function_ `const CTypeBase* GetType() const`
- L105 _public prototype_ `void GetScopePath(uLang::CUTF8StringBuilder& OutBuilder, uLang::UTF8Char SeparatorChar = '.', CScope::EPathMode Mode = CScope::EPathMode::Default) const;`
- L106 _public prototype_ `CUTF8String GetScopePath(uLang::UTF8Char SeparatorChar = '.', CScope::EPathMode Mode = CScope::EPathMode::Default) const;`
- L108 _public function_ `void SetOverriddenDefinition(const CDataDefinition& OverriddenDefinition)`
- L109 _public function_ `const CDataDefinition* GetOverriddenDefinition() const`
- L114 _public function_ `const CDataDefinition& GetBaseOverriddenDefinition() const`
- L118 _public function_ `const CDataDefinition& GetBaseClassOverriddenDefinition() const`
- L123 _public function_ `void SetHasInitializer()`
- L128 _public function_ `bool HasInitializer() const`
- L133 _public function_ `void SetVarAccessLevel(TOptional<SAccessLevel>&& AccessLevel)`
- L140 _public function_ `void SetIsVar()`
- L146 _public function_ `void SetValueDomainEffects(SEffectSet ValueDomainEffects)`
- L151 _public function_ `void SetIsLiveValue(bool bIsLiveValue)`
- L156 _public function_ `const TOptional<SAccessLevel>& SelfVarAccessLevel() const`
- L162 _public function_ `bool IsVar() const`
- L167 _public function_ `SEffectSet ValueDomainEffects() const`
- L172 _public function_ `bool IsLive() const`
- L178 _public function_ `bool IsLiveValueDomain() const`
- L183 _public function_ `bool IsLiveValue() const`
- L188 _public function_ `SAccessLevel DerivedVarAccessLevel() const`
- L194 _public prototype_ `bool IsVarWritableFrom(const CScope&) const;`
- L196 _public function_ `const CDataDefinition& GetDefinitionVarAccessibilityRoot() const`
- L201 _public prototype_ `bool IsModuleScopedVar() const;`
- L203 _public prototype_ `EPersistenceExternalAccess GetPersistenceExternalAccess() const;`
- L205 _public prototype_ `void MarkPersistenceCompatConstraint() const;`
- L207 _public prototype_ `virtual bool IsPersistenceCompatConstraint() const override;`
- L209 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L211 _public member_ `SClassVarAccessorFunctions _OptionalAccessors;`
- L212 _public prototype_ `bool CanHaveCustomAccessors() const;`
- L214 _public prototype_ `bool HasPredictsAttribute() const;`
- L215 _public prototype_ `bool CanBeAccessedFromPredicts() const;`
- L217 _public prototype_ `void InstantiateDefinition(CScope& InstPositiveScope, CScope& InstNegativeScope, const CNormalType& InstType, const TArray<STypeVariableSubstitution>& Substitutions) const override;`
- L218 _public prototype_ `void CreateNegativeDefinition(CScope& NegativeScope) const override;`
- L221 _public member_ `TSPtr<CExpressionBase> DefaultValue;` — Used for default value of data definitions in interfaces.
- L222 _public member_ `TSPtr<CExpressionBase> DefaultFunction;`
- L225 _private member_ `TOptional<SAccessLevel> _VarAccessLevel;`
- L226 _private member_ `const CTypeBase* _Type{nullptr};`
- L227 _private member_ `mutable bool _bPersistenceCompatConstraint{false};`
- L228 _private member_ `bool _bIsVar{false};`
- L229 _private member_ `SEffectSet _ValueDomainEffects;`
- L230 _private member_ `bool _bIsLiveValue{false};`
- L231 _private member_ `bool _bHasInitializer{false};`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API VERSECOMPILER_API`
- L18 _namespace_ `namespace uLang`
- L24 _variable_ `static SAccessLevel::EKind DefaultVarAccessLevelKind = SAccessLevel::EKind::Public;` (scope `uLang`)
- L49 _function_ `inline bool IsExternallyWritable(EPersistenceExternalAccess Arg)` (scope `uLang`)
- L54 _function_ `inline bool IsExternallyReadable(EPersistenceExternalAccess Arg)` (scope `uLang`)
- L59 _prototype_ `EPersistenceExternalAccess GetPersistenceExternalAccess(const CAttributable&, const CSemanticProgram&);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Definition.h` (Public)


#### struct `uLang::SQualifier`  
`struct SQualifier`  
_L36-108_
- desc: Information about a given qualifier.
- L50 _public member_ `} U;`
- L52 _public member_ `EType _Type;`
- L54 _public prototype_ `SQualifier GetConstrainedQualifier() const;`
- L56 _public function_ `const CNominalType* GetNominalType() const`
- L64 _public function_ `const CLogicalScope* GetLogicalScope() const`
- L71 _public function_ `static SQualifier NominalType(const CNominalType* NominalType)`
- L75 _public function_ `static SQualifier LogicalScope(const CLogicalScope* LogicalScope)`
- L79 _public function_ `static SQualifier Local()`
- L83 _public function_ `static SQualifier Unknown()`
- L88 _public function_ `bool IsUnspecified() const`
- L93 _public function_ `bool IsLocal() const`
- L98 _public function_ `bool operator==(const SQualifier& Other) const`
- L104 _public function_ `bool operator!=(const SQualifier& Other) const`

#### enum `uLang::SQualifier::EType`  
`enum class EType : uint8_t`  
_L38-44_
- L40 _public enumerator_ `Local` — i.e. `(local:)`, which is limited to a function's enclosing scopes.
- L41 _public enumerator_ `NominalType` — This encompasses any nominal type or module.
- L42 _public enumerator_ `LogicalScope` — This encompasses any parameterized type.
- L43 _public enumerator_ `Unknown` — Sentinel value for invalid/unresolved qualifiers.

#### union `uLang::SQualifier::(anonymous)`  
`union`  
_L47-50_
- desc: The definition that the qualifier is referring to.

#### class `uLang::TAstNodeRef`  
`template<class AstNodeType> class TAstNodeRef`  
_L114-125_
- desc: Reference to a pair of AST and IR nodes
- L117 _public function_ `AstNodeType* GetAstNode() const`
- L118 _public function_ `AstNodeType* GetIrNode(bool bForce = false) const`
- L119 _public function_ `void SetAstNode(AstNodeType* AstNode)`
- L120 _public function_ `void SetIrNode(AstNodeType* IrNode)`
- L123 _private member_ `AstNodeType* _AstNode{ nullptr };`
- L124 _private member_ `AstNodeType* _IrNode{ nullptr };`

#### class `uLang::CDefinition`  
`class CDefinition : public CNamed, public TAstNodeRef<CExpressionBase>, public CSharedMix`  
_L132-401_
- inherits: `CNamed,TAstNodeRef<CExpressionBase>,CSharedMix`
- desc: The base class of scoped definitions.
- L143 _public member_ `CScope& _EnclosingScope;`
- L148 _public member_ `const int32_t _ParentScopeOrdinal;` — An integer that represents the order the definition occurred in the parent scope: The absolute value shouldn't be used, but if this value is greater than another definition from the same scope, this definition occurred after the other.
- L151 _public member_ `SQualifier _Qualifier;` — If the definition overrides via an explicit qualifier, this is the qualifier type
- L153 _public prototype_ `CDefinition(EKind Kind, CScope& EnclosingScope, const CSymbol& Name);`
- L155 _public prototype_ `~CDefinition();`
- L160 _public function_ `bool TryMarkOverriddenAndConstrainedDefinitionsVisited(CVisitSet& VisitSet) const` — If this definition is in the given visit set, return false. Otherwise, add this definition *and all definitions it overrides* to the visit set and return true.
- L185 _public function_ `EKind GetKind() const` — Casts
- L188 _public prototype_ `template<typename TDefinition> TDefinition& AsChecked();`
- L191 _public prototype_ `template<typename TDefinition> TDefinition const& AsChecked() const;`
- L194 _public function_ `template<typename TDefinition> bool IsA() const`
- L197 _public function_ `template<typename TDefinition> TDefinition* AsNullable()`
- L200 _public function_ `template<typename TDefinition> TDefinition const* AsNullable() const`
- L203 _public function_ `const CDefinition* GetOverriddenDefinition() const` — Accessors
- L207 _public function_ `const CDefinition& GetBaseOverriddenDefinition() const`
- L218 _public function_ `const CAttributable& GetAttributes() const` — Attribute accessors.
- L224 _public function_ `CAttributable& GetAttributes()`
- L230 _public function_ `bool HasAttributeClass(const CClass* AttributeClass, const CSemanticProgram& Program) const`
- L235 _public function_ `bool HasAttributeSubclass(const CClass* AttributeClass, const CSemanticProgram& Program) const`
- L240 _public function_ `void AddAttributeClass(const CClass* AttributeClass)`
- L246 _public prototype_ `const CDefinition& GetBaseClassOverriddenDefinition() const;` — As above but will stop before interface.
- L248 _public function_ `const CDefinition* GetPrototypeDefinition() const`
- L250 _public function_ `void SetConstrainedDefinition(const CDefinition& ConstrainedDefinition)`
- L255 _public function_ `const CDefinition* GetConstrainedDefinition() const`
- L260 _public function_ `CExpressionBase* GetAstNode() const`
- L261 _public function_ `CExpressionBase* GetIrNode(bool bForce = false) const`
- L263 _public function_ `void SetAccessLevel(const TOptional<SAccessLevel>& AccessLevel)`
- L269 _public function_ `const TOptional<SAccessLevel>& SelfAccessLevel() const` — AccessLevel declared on this specific definition.
- L272 _public prototype_ `SAccessLevel DerivedAccessLevel() const;` — This is the true AccessLevel of this definition. This is what you want to use most of the time when checking if it's accessible.
- L275 _public prototype_ `bool IsInstanceMember() const;` — Returns whether this is a member of some instantiated type like a class or interface.
- L278 _public prototype_ `bool IsDeprecated() const;` — Returns whether this definition has the deprecated attribute.
- L281 _public prototype_ `bool IsExperimental() const;` — Returns whether this definition has the experimental attribute.
- L284 _public prototype_ `bool IsFinal(uint32_t UploadedAtFNVersion) const;` — Returns whether this is a final field of an inheritable type like a class or interface.
- L287 _public prototype_ `const CExpressionBase* GetNativeSpecifierExpression() const;` — If the definition is native, returns the native specifier expression.
- L290 _public prototype_ `bool IsNative() const;` — Returns whether this is a native definition.
- L293 _public prototype_ `bool IsBuiltIn() const;` — Returns whether this is a built-in definition.
- L296 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const` — If this definition has a corresponding scope, yield it.
- L314 _public function_ `const CDefinition& GetDefinitionAccessibilityRoot() const` — These classes of functions are helpers to get to the scope of where the definition or definition's var access scope is defined. In Verse, access scopes are inherited when not explicitly defined. Note, this isn't the same as saying the same specifier is passed along the inheritance chain. For example: M1<public> := module { Base<public> := class { Field<internal>:int = 42 } M2<public> := module: Child<public> := class(Base) { Field<override>:int = 50 } } M2.Child's Field property is still accessible as internal to M1, not internal to M2.
- L319 _public prototype_ `bool IsAccessibleFrom(const CScope&) const;`
- L321 _public prototype_ `virtual bool IsPersistenceCompatConstraint() const = 0;`
- L323 _public prototype_ `virtual bool IsEntitlementCompatConstraint() const = 0;`
- L325 _public function_ `void SetOverriddenDefinition(const CDefinition& OverriddenDefinition)`
- L329 _public function_ `void SetOverriddenDefinition(const CDefinition* OverriddenDefinition)`
- L336 _public prototype_ `const CDefinition* GetEnclosingDefinition() const;` — Find a definition that corresponds to the nearest enclosing scope with a corresponding definition. If there is none, returns nullptr.
- L339 _public prototype_ `bool IsExplicitlyLocallyQualified() const;` — If the definition is explicitly qualified with the `(local:)` identifier.
- L342 _public prototype_ `bool IsLocallyQualified() const;` — If the definition is implicitly local by virtue of being a definition within a function body/explicitly qualified as `(local:)`.
- L345 _public prototype_ `SQualifier GetImplicitQualifier() const;` — Determines the qualifier for this definition, even if not explicitly specified (from the original source).
- L347 _public prototype_ `void SetName(const CSymbol& NewName);`
- L349 _public prototype_ `void SetInstantiatedOverriddenDefinition(const CNormalType& InstType, const CDefinition& GeneralizedDefinition);`
- L351 _public function_ `virtual void InstantiateDefinition(CScope& InstPositiveScope, CScope& InstNegativeScope, const CNormalType& InstType, const TArray<STypeVariableSubstitution>& Substitutions) const`
- L356 _public function_ `virtual void CreateNegativeDefinition(CScope& NegativeScope) const`
- L364 _protected function_ `void SetPrototypeDefinition(const CDefinition& PrototypeDefinition)` — Setters that should be wrapped by a subclass to restrict the parameter type.
- L369 _protected function_ `void SetAstNode(CExpressionBase* AstNode)`
- L374 _protected function_ `void SetIrNode(CExpressionBase* IrNode)`
- L381 _private member_ `const EKind _Kind;`
- L384 _private member_ `CVisitKey _LastOverridingVisitKey{};` — The visit key used to identify whether this definition or an overriding definition is in a visit set.
- L388 _private member_ `const CDefinition* _PrototypeDefinition{ this };` — If the definition was instantiated from a polymorphic prototype, this will reference the prototype definition. Otherwise, it will reference this definition.
- L391 _private member_ `const CDefinition* _OverriddenDefinition{ nullptr };` — If the definition overrides an inherited definition, this will reference the inherited definition.
- L394 _private member_ `const CDefinition* _ConstrainedDefinition{ nullptr };` — If this definition is a constraint on some other definition, this will reference the constrained definition.
- L397 _private member_ `TOptional<SAccessLevel> _AccessLevel;` — The definition's access level.
- L400 _private member_ `CAttributable _Attributes;` — The attributes for the definition. Only valid if GetPrototypeDefinition() == this.
- L408 _function_ `template<typename TDefinition> TDefinition& CDefinition::AsChecked()`
- L415 _function_ `template<typename TDefinition> TDefinition const& CDefinition::AsChecked() const`

#### enum `uLang::CDefinition::EKind`  
`enum class EKind : uint8_t`  
_L136-141_
- L139 _public enumerator_ `VERSE_ENUM_DEFINITION_KINDS(VISIT_KIND) #undef VISIT_KIND`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API VERSECOMPILER_API`
- L15 _namespace_ `namespace uLang`
- L23 _macro_ `#define VERSE_ENUM_DEFINITION_KINDS(v) \`
- L48 _member_ `const CNominalType* _NominalType;` (scope `uLang::SQualifier::__anona5a16541010a`)
- L49 _member_ `const CLogicalScope* _LogicalScope;` (scope `uLang::SQualifier::__anona5a16541010a`)
- L127 _typedef_ `using CAstNodeRef = TAstNodeRef<CExpressionBase>;` (scope `uLang`)
- L138 _macro_ `#define VISIT_KIND(Name, ...) Name,`
- L403 _prototype_ `CUTF8String GetQualifiedNameString(const CDefinition& Definition);` (scope `uLang`)
- L404 _prototype_ `CUTF8String GetCrcNameString(const CDefinition& Definition);` (scope `uLang`)
- L405 _prototype_ `const char* DefinitionKindAsCString(CDefinition::EKind Kind);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Effects.h` (Public)


#### enum `uLang::EEffect`  
`enum class EEffect : uint8_t`  
_L23-28_
- L26 _public enumerator_ `VERSE_ENUM_EFFECTS(VISIT_EFFECT) #undef VISIT_EFFECT`

#### struct `uLang::SEffectInfo`  
`struct SEffectInfo`  
_L34-38_
- L36 _public member_ `const char* _AttributeName;`
- L37 _public member_ `EEffect _Effect;`

#### struct `uLang::SEffectSetBase`  
`struct SEffectSetBase`  
_L43-43_

#### struct `uLang::SEffectSet`  
`struct SEffectSet : private SEffectSetBase`  
_L45-201_
- inherits: `SEffectSetBase`
- L47 _public function_ `constexpr SEffectSet() : SEffectSetBase() #define VISIT_EFFECT(Name) , _##Name(false) VERSE_ENUM_EFFECTS(VISIT_EFFECT) #undef VISIT_EFFECT`
- L53 _public function_ `constexpr SEffectSet(EEffect SingleEffect) : SEffectSetBase() #define VISIT_EFFECT(Name) , _##Name(SingleEffect == EEffect::Name) VERSE_ENUM_EFFECTS(VISIT_EFFECT) #undef VISIT_EFFECT`
- L69 _public function_ `SEffectSet& operator|=(SEffectSet Rhs)`
- L85 _public function_ `SEffectSet& operator&=(SEffectSet Rhs)`
- L101 _public function_ `SEffectSet& operator^=(SEffectSet Rhs)`
- L117 _public function_ `bool operator[](EEffect Effect) const`
- L122 _public function_ `constexpr bool HasAny(SEffectSet Rhs) const`
- L131 _public function_ `constexpr bool HasAll(SEffectSet Rhs) const`
- L158 _public function_ `SEffectSet With(EEffect SingleEffect, bool bEnable = true) const`
- L166 _public function_ `int32_t Num() const` — The number of bits set - used for some ordering in effect decomposition
- L177 _private function_ `VERSE_ENUM_EFFECTS(VISIT_EFFECT) #undef VISIT_EFFECT bool Get(EEffect Effect) const`
- L191 _private function_ `void Set(EEffect Effect, bool Enable)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L13 _macro_ `#define VERSE_ENUM_EFFECTS(v) \` — If you change this enum macro, you must keep things in sync with both VVMVerseEffectSet.h and MakeEffectSet
- L25 _macro_ `#define VISIT_EFFECT(Name) Name,`
- L30 _macro_ `#define VISIT(Name) 1 +`
- L31 _variable_ `inline constexpr int32_t EEffectNum = VERSE_ENUM_EFFECTS(VISIT) 0;` (scope `uLang`)
- L40 _prototype_ `TRangeView<SEffectInfo*, SEffectInfo*> AllEffectInfos();` (scope `uLang`)
- L41 _prototype_ `SEffectInfo GetEffectInfo(EEffect Effect);` (scope `uLang`)
- L49 _macro_ `#define VISIT_EFFECT(Name) , _##Name(false)`
- L55 _macro_ `#define VISIT_EFFECT(Name) , _##Name(SingleEffect == EEffect::Name)`
- L60 _function_ `friend constexpr SEffectSet operator~(const SEffectSet Operand)` (scope `uLang`)
- L63 _macro_ `#define VISIT_EFFECT(Name) Result._##Name = !Operand._##Name;`
- L71 _macro_ `#define VISIT_EFFECT(Name) _##Name = _##Name || Rhs._##Name;`
- L76 _function_ `friend constexpr SEffectSet operator|(const SEffectSet Lhs, const SEffectSet Rhs)` (scope `uLang`)
- L79 _macro_ `#define VISIT_EFFECT(Name) Result._##Name = Lhs._##Name || Rhs._##Name;`
- L87 _macro_ `#define VISIT_EFFECT(Name) _##Name = _##Name && Rhs._##Name;`
- L92 _function_ `friend constexpr SEffectSet operator&(const SEffectSet Lhs, const SEffectSet Rhs)` (scope `uLang`)
- L95 _macro_ `#define VISIT_EFFECT(Name) Result._##Name = Lhs._##Name && Rhs._##Name;`
- L103 _macro_ `#define VISIT_EFFECT(Name) _##Name = (!_##Name && Rhs._##Name) || (_##Name && !Rhs._##Name);`
- L108 _function_ `friend constexpr SEffectSet operator^(const SEffectSet Lhs, const SEffectSet Rhs)` (scope `uLang`)
- L111 _macro_ `#define VISIT_EFFECT(Name) Result._##Name = (!Lhs._##Name && Rhs._##Name) || (Lhs._##Name && !Rhs._##Name);`
- L125 _macro_ `#define VISIT_EFFECT(Name) Result = Result || (_##Name && Rhs._##Name);`
- L134 _macro_ `#define VISIT_EFFECT(Name) Result = Result && (!Rhs._##Name || _##Name);`
- L140 _function_ `friend constexpr bool operator==(const SEffectSet Lhs, const SEffectSet Rhs)` (scope `uLang`)
- L143 _macro_ `#define VISIT_EFFECT(Name) Result = Result && (Lhs._##Name == Rhs._##Name);`
- L149 _function_ `friend constexpr bool operator!=(const SEffectSet Lhs, const SEffectSet Rhs)` (scope `uLang`)
- L152 _macro_ `#define VISIT_EFFECT(Name) Result = Result || (Lhs._##Name != Rhs._##Name);`
- L169 _macro_ `#define VISIT_EFFECT(Name) + (_##Name ? 1 : 0)`
- L176 _macro_ `#define VISIT_EFFECT(Name) bool _##Name : 1;`
- L184 _macro_ `#define VISIT_EFFECT(Name) case EEffect::Name: return _##Name;`
- L195 _macro_ `#define VISIT_EFFECT(Name) case EEffect::Name: _##Name = Enable; break;`
- L203 _function_ `constexpr SEffectSet operator|(const EEffect Lhs, const EEffect Rhs)` (scope `uLang`)
- L208 _function_ `inline uint32_t GetTypeHash(const SEffectSet& Effects)` (scope `uLang`)
- L214 _macro_ `#define VISIT(Name) if (Effects[EEffect::Name]) { Hash |= (1 << I); } ++I;`
- L220 _namespace_ `namespace EffectSets` (scope `uLang`)
- L222 _variable_ `constexpr SEffectSet Bot{};` (scope `uLang::EffectSets`)
- L223 _variable_ `constexpr SEffectSet Top = Bot #define VISIT(Name) | EEffect::Name VERSE_ENUM_EFFECTS(VISIT);` (scope `uLang::EffectSets`)
- L224 _macro_ `#define VISIT(Name) | EEffect::Name`
- L229 _variable_ `constexpr SEffectSet Converges = Bot;` (scope `uLang::EffectSets`) — Singular effects
- L230 _variable_ `constexpr SEffectSet Suspends = EEffect::suspends;` (scope `uLang::EffectSets`)
- L231 _variable_ `constexpr SEffectSet Computes = EEffect::diverges;` (scope `uLang::EffectSets`)
- L232 _variable_ `constexpr SEffectSet NoRollback = EEffect::no_rollback;` (scope `uLang::EffectSets`)
- L233 _variable_ `constexpr SEffectSet Decides = EEffect::decides;` (scope `uLang::EffectSets`)
- L234 _variable_ `constexpr SEffectSet Dictates = EEffect::dictates;` (scope `uLang::EffectSets`)
- L237 _variable_ `constexpr SEffectSet Reads = EEffect::reads | EEffect::dictates;` (scope `uLang::EffectSets`) — Aggregate effects
- L238 _variable_ `constexpr SEffectSet Writes = EEffect::writes | EEffect::dictates;` (scope `uLang::EffectSets`)
- L239 _variable_ `constexpr SEffectSet Allocates = EEffect::allocates | EEffect::dictates;` (scope `uLang::EffectSets`)
- L240 _variable_ `constexpr SEffectSet Transacts = EEffect::diverges | EEffect::reads | EEffect::writes | EEffect::allocates | EEffect::dictates;` (scope `uLang::EffectSets`)
- L241 _variable_ `constexpr SEffectSet VariesDeprecated = Transacts;` (scope `uLang::EffectSets`)
- L244 _variable_ `constexpr SEffectSet ClassAndInterfaceDefault = Transacts;` (scope `uLang::EffectSets`) — Contextual defaults
- L245 _variable_ `constexpr SEffectSet FunctionDefault = Transacts | EEffect::no_rollback;` (scope `uLang::EffectSets`)
- L246 _variable_ `constexpr SEffectSet ParametricTypeDefault = Converges;` (scope `uLang::EffectSets`)
- L247 _variable_ `constexpr SEffectSet ModuleDefault = EEffect::allocates | EEffect::dictates | EEffect::diverges;` (scope `uLang::EffectSets`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Expression.h` (Public)


#### enum `uLang::EAstNodeType`  
`enum class EAstNodeType : uint8_t`  
_L188-193_
- desc: This is used to differentiate between different types of AST nodes when it is only known that an instance is of type CAstNode, but not the specific subclass. It is returned by the method CAstNode::GetNodeType()
- L191 _public enumerator_ `VERSE_VISIT_AST_NODE_TYPES(VISIT_AST_NODE_TYPE) #undef VISIT_AST_NODE_TYPE`

#### struct `uLang::SAstNodeTypeInfo`  
`struct SAstNodeTypeInfo`  
_L195-199_
- L197 _public member_ `const char* _EnumeratorName;`
- L198 _public member_ `const char* _CppClassName;`

#### enum `uLang::EInvokeTime`  
`enum class EInvokeTime : uint8_t`  
_L207-212_
- desc: Indicates whether an expression should return immediately - such as functions, after a duration (including immediately) such as coroutines or either.
- L209 _public enumerator_ `Immediate = 1 << 0` — May only call an immediate expression (such as a function call) and any async expression (such as a coroutine call) should result in an error.
- L210 _public enumerator_ `Async = 1 << 1` — May only call an async expression (such as a coroutine call) and any immediate expression (such as a function call) should result in an error. Only true within one of the pre-defined calling contexts (`sync{}`, `race{}`, etc.).
- L211 _public enumerator_ `Any_ = Immediate | Async` — Calling either immediate or async expressions is allowed.

#### struct `uLang::SAstVisitor`  
`struct SAstVisitor`  
_L229-292_
- desc: Abstract base for applying some operation / iterating through AST structures. @see CAstNode::VisitChildren()
- L232 _public function_ `virtual void VisitImmediate(const char* FieldName, CUTF8StringView Value)` — Called when visiting an AST node
- L233 _public function_ `virtual void VisitImmediate(const char* FieldName, int64_t Value)`
- L234 _public function_ `virtual void VisitImmediate(const char* FieldName, double Value)`
- L235 _public function_ `virtual void VisitImmediate(const char* FieldName, bool Value)`
- L236 _public function_ `virtual void VisitImmediate(const char* FieldName, const CTypeBase* Type)`
- L237 _public function_ `virtual void VisitImmediate(const char* FieldName, const CDefinition& Definition)`
- L238 _public function_ `virtual void VisitImmediate(const char* FieldName, const Verse::Vst::Node& VstNode)`
- L240 _public function_ `void VisitImmediate(const char* FieldName, const char* CString)`
- L242 _public prototype_ `virtual void Visit(const char* FieldName, CAstNode& AstNode) = 0;`
- L243 _public function_ `virtual void BeginArray(const char* FieldName, intptr_t Num)`
- L244 _public prototype_ `virtual void VisitElement(CAstNode& AstNode) = 0;`
- L245 _public function_ `virtual void EndArray()`
- L248 _public function_ `template<typename NodeType, bool bAllowNull, typename AllocatorType, typename... AllocatorArgTypes> void Visit(const char* FieldName, const TSPtrG<NodeType, bAllowNull, AllocatorType, AllocatorArgTypes...>& NodePointer)`
- L257 _public function_ `template<typename NodeType, bool bAllowNull, typename AllocatorType, typename... AllocatorArgTypes> void VisitElement(const TSPtrG<NodeType, bAllowNull, AllocatorType, AllocatorArgTypes...>& NodePointer)`
- L266 _public function_ `template<typename NodeType, bool bAllowNull, typename NodeAllocatorType, typename ElementAllocatorType, typename... ElementAllocatorArgTypes> void VisitArray(const char* FieldName, const TArrayG<TSPtrG<NodeType, bAllowNull, NodeAllocatorType>, ElementAllocatorType, ElementAllocatorArgTypes...>& Array)`
- L280 _public function_ `template<typename NodeType, bool bAllowNull, typename ElementAllocatorType, typename... RawAllocatorArgTypes> void VisitArray(const char* FieldName, const TSPtrArrayG<NodeType, bAllowNull, ElementAllocatorType, RawAllocatorArgTypes...>& Array)`

#### enum `uLang::EVstMappingType`  
`enum class EVstMappingType`  
_L294-297_
- L296 _public enumerator_ `Ast`
- L296 _public enumerator_ `Ast`
- L296 _public enumerator_ `Ast`

#### class `uLang::CAstNode`  
`class AUTORTFM_DISABLE CAstNode : public CSharedMix`  
_L302-386_
- inherits: `CSharedMix`
- desc: Abstract base class for AST nodes.
- L305 _public function_ `CAstNode(EVstMappingType VstMappingType = EVstMappingType::Ast) : _VstMappingType(VstMappingType)`
- L307 _public prototype_ `virtual ~CAstNode();`
- L309 _public prototype_ `virtual EAstNodeType GetNodeType() const = 0;`
- L310 _public function_ `virtual const CExpressionBase* AsExpression() const`
- L311 _public function_ `virtual CExpressionBase* AsExpression()`
- L312 _public function_ `virtual bool MayHaveAttributes() const`
- L313 _public function_ `virtual const CExprIdentifierBase* AsIdentifierBase() const`
- L318 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const` — Iterates over this AST node's immediate fields, calling Visitor.VisitImmediate for each immediate field.
- L338 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const` — Iterates over this AST node's direct children, calling Visitor.Visit for each child.
- L346 _public prototype_ `template<typename FunctionType> void VisitChildrenLambda(FunctionType&& Function) const;` — Wrapper for VisitChildren that takes a lambda that is called for each child. The signature for the lambda should be (const SAstVisitor& RecurseVisitor, CAstNode&) You can use RecurseVisitor to recursively call VisitChildren with the same lambda.
- L350 _public prototype_ `virtual CUTF8String GetErrorDesc() const = 0;` — Text methods
- L354 _public function_ `const Verse::Vst::Node* GetMappedVstNode() const` — Syntax <> Semantic Mapping
- L356 _public function_ `void SetNonReciprocalMappedVstNode(const Verse::Vst::Node* VstNode)`
- L362 _public function_ `void SetIrMappedVstNode(const Verse::Vst::Node* VstNode)`
- L370 _public function_ `bool IsIrNode() const` — True if this AstNode is used to represent an IrNode. Needed to disable some asserts and clean up code. Will be removed when IrNodes have their own type.
- L375 _public function_ `bool IsVstMappingReciprocal() const`
- L384 _protected member_ `mutable EVstMappingType _VstMappingType;` — Syntax<>Semantic mapping
- L385 _protected member_ `mutable const Verse::Vst::Node* _MappedVstNode{nullptr};`
- L3601 _function_ `template<typename FunctionType> void CAstNode::VisitChildrenLambda(FunctionType&& Function) const`

#### class `uLang::CExpressionBase`  
`class AUTORTFM_DISABLE CExpressionBase : public CAstNode, public CAttributable`  
_L392-474_
- inherits: `CAstNode,CAttributable`
- desc: Abstract base class for AST expressions. Created from abstract syntax tree (CExpressionBase and CSemanticProgram) generated by semantic analyzer.
- L396 _public function_ `explicit CExpressionBase(EVstMappingType VstMappingType = EVstMappingType::Ast) : CAstNode(VstMappingType)`
- L397 _public function_ `explicit CExpressionBase(const CTypeBase* InResultType) : _Report(SAnalysisResult{InResultType})`
- L401 _public function_ `virtual const CExpressionBase* AsExpression() const override`
- L402 _public function_ `virtual CExpressionBase* AsExpression() override`
- L403 _public function_ `virtual bool MayHaveAttributes() const override`
- L405 _public typedef_ `using TMacroSymbols = TArrayG<CSymbol, TInlineElementAllocator<3>>;`
- L408 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const` — True if this expression can be path of a segment. It works at all times, i.e., also before macro expression have been processed. The MacroSymbols argument is used in the latter case.
- L409 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L423 _public function_ `EInvokeTime DetermineInvokeTime(const CSemanticProgram& Program) const` — Determines if expression is immediate (completes within the current update/frame) or async (completes within the current update/frame or later). @TODO: SOL-1423, DetermineInvokeTime() re-traverses the expression tree, which could add up time wise (approaching on n^2) -- there should be a beter way to check this on the initial ProcessExpression()
- L426 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const` — Returns itself or the first async sub-expression or return nullptr if it and all its sub-expressions are immediate.
- L429 _public function_ `virtual bool CanFail(const CAstPackage* Package) const` — Returns whether the expression may fail.
- L433 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const;` — Type methods
- L434 _public prototype_ `void SetResultType(const CTypeBase* InResultType);`
- L435 _public prototype_ `void RefineResultType(const CTypeBase* RefinedResultType);`
- L437 _public function_ `bool IsAnalyzed() const`
- L439 _public function_ `const CTypeBase* IrGetResultType() const`
- L440 _public function_ `void IrSetResultType(const CTypeBase* TypeBase)`
- L459 _public member_ `SEffectSet Effects;` — We begin by collecting each node's individual effects during SemanticAnalysis. During AST IR generation, we do a pass to sum up the aggregate effects representing each node and the code reachable within it. These effects are conservative. We may say a node has some effects that it doesn't actually have. For example, we'll propagate the <decides> effect outside of a failure context, even though the failure context will eat the <decides> effect. It will be easy to make this mor precise if we ever need it to be.
- L472 _protected member_ `TOptional<SAnalysisResult> _Report;`

#### struct `uLang::CExpressionBase::SAnalysisResult`  
`struct SAnalysisResult`  
_L465-470_
- desc: Analysis Results
- L467 _public function_ `bool operator==(const SAnalysisResult& Other) const`
- L469 _public member_ `const CTypeBase* ResultType;` — The type to which this node evaluates.

#### class `uLang::CExprCompoundBase`  
`class AUTORTFM_DISABLE CExprCompoundBase : public CExpressionBase`  
_L481-530_
- inherits: `CExpressionBase`
- desc: Base for expressions that have an array of subexpressions Subclasses: CExprMakeArray, CExprMakeMap, CExprMakeTuple, CExprCodeBlock, CExprConcurrentBlockBase, CExprAwait
- L486 _public function_ `explicit CExprCompoundBase(int32_t ReserveSubExprNum, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType)`
- L492 _public function_ `explicit CExprCompoundBase(TArray<TSRef<CExpressionBase>>&& SubExprs, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType) , _SubExprs(Move(SubExprs))`
- L497 _public function_ `explicit CExprCompoundBase(TSRef<CExpressionBase>&& SubExpr1, TSRef<CExpressionBase>&& SubExpr2) : CExprCompoundBase(2)`
- L504 _public prototype_ `CExprCompoundBase() = default;`
- L506 _public function_ `bool IsEmpty() const`
- L507 _public function_ `int32_t SubExprNum() const`
- L508 _public function_ `const uLang::CExpressionBase* GetLastSubExpr() const`
- L509 _public function_ `const TArray<TSRef<CExpressionBase>>& GetSubExprs() const`
- L510 _public function_ `TArray<TSRef<CExpressionBase>>& GetSubExprs()`
- L511 _public function_ `TArray<TSRef<CExpressionBase>>&& TakeSubExprs()`
- L512 _public function_ `void AppendSubExpr(TSRef<CExpressionBase> SubExpr)`
- L513 _public function_ `void PrependSubExpr(TSRef<CExpressionBase> SubExpr)`
- L514 _public function_ `void SetSubExprs(TArray<TSRef<CExpressionBase>>&& AnalyzedExprs)`
- L515 _public function_ `void ReplaceSubExpr(TSRef<CExpressionBase> SubExpr, int32_t Index)`
- L521 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`
- L522 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L523 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L529 _protected member_ `TArray<TSRef<CExpressionBase>> _SubExprs;`

#### class `uLang::CExprBinaryOp`  
`class AUTORTFM_DISABLE CExprBinaryOp : public CExpressionBase`  
_L536-555_
- inherits: `CExpressionBase`
- desc: Base class of binary operators.
- L540 _private member_ `TSPtr<CExpressionBase> _Lhs;` — Operands
- L541 _private member_ `TSPtr<CExpressionBase> _Rhs;`
- L545 _public function_ `const TSPtr<CExpressionBase>& Lhs() const`
- L546 _public function_ `const TSPtr<CExpressionBase>& Rhs() const`
- L547 _public function_ `TSPtr<CExpressionBase>&& TakeRhs()`
- L548 _public function_ `void SetLhs(TSPtr<CExpressionBase>&& NewLhs)`
- L549 _public function_ `void SetRhs(TSPtr<CExpressionBase>&& NewRhs)`
- L551 _public function_ `CExprBinaryOp(TSPtr<CExpressionBase>&& Lhs, TSPtr<CExpressionBase>&& Rhs) : _Lhs(Move(Lhs)), _Rhs(Move(Rhs))`
- L553 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L554 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`

#### class `uLang::CNoop`  
`class AUTORTFM_DISABLE CNoop : public CExpressionBase`  
_L560-567_
- inherits: `CExpressionBase`
- desc: Nice to have when something should be ignored
- L563 _public prototype_ `explicit CNoop(const CSemanticProgram& Program);`
- L565 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L566 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprExternal`  
`class AUTORTFM_DISABLE CExprExternal : public CExpressionBase`  
_L576-585_
- inherits: `CExpressionBase`
- desc: Expression for external{} macro used in digests - should never reach the code generator
- L581 _public prototype_ `explicit CExprExternal(const CSemanticProgram& Program);`
- L583 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L584 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprLogic`  
`class AUTORTFM_DISABLE CExprLogic : public CExpressionBase`  
_L591-603_
- inherits: `CExpressionBase`
- desc: Logic literal - true/false
- L595 _public member_ `bool _Value;`
- L597 _public prototype_ `explicit CExprLogic(const CSemanticProgram& Program, bool Value);`
- L599 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L600 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L602 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprNumber`  
`class AUTORTFM_DISABLE CExprNumber : public CExpressionBase`  
_L609-651_
- inherits: `CExpressionBase`
- desc: Integer literal - 42, 0, -123, 123_456_789, 0x12fe, 0b101010
- L617 _private member_ `bool _bIsFloat : 1;`
- L621 _public function_ `explicit CExprNumber() : _IntValue(0) , _bIsFloat(false)`
- L626 _public prototype_ `explicit CExprNumber(CSemanticProgram&, Integer);`
- L628 _public prototype_ `explicit CExprNumber(CSemanticProgram&, Float);`
- L630 _public function_ `bool IsFloat() const`
- L631 _public function_ `Integer GetIntValue() const`
- L632 _public prototype_ `void SetIntValue(CSemanticProgram&, Integer);`
- L633 _public function_ `Float GetFloatValue() const`
- L634 _public prototype_ `void SetFloatValue(CSemanticProgram&, Float);`
- L636 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L637 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L639 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### union `uLang::CExprNumber::(anonymous)`  
``  
_L613-616_

#### class `uLang::CExprChar`  
`class AUTORTFM_DISABLE CExprChar : public CExpressionBase`  
_L657-702_
- inherits: `CExpressionBase`
- desc: Character literal - 'H' '\n' '{0o00}' '{0u1f600}'
- L666 _public member_ `uint32_t _CodePoint;`
- L667 _public member_ `EType _Type;`
- L669 _public function_ `explicit CExprChar(uint32_t CodePoint, EType Type) : _CodePoint(CodePoint) , _Type(Type)`
- L679 _public function_ `CUTF8String AsString() const`
- L698 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L699 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L701 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### enum `uLang::CExprChar::EType`  
`enum class EType`  
_L660-664_
- L662 _public enumerator_ `UTF8CodeUnit`
- L663 _public enumerator_ `UnicodeCodePoint`

#### class `uLang::CExprString`  
`class AUTORTFM_DISABLE CExprString : public CExpressionBase`  
_L708-723_
- inherits: `CExpressionBase`
- desc: String literal - "Hello, world!", "Line 1\nLine2"
- L714 _public member_ `CUTF8String _String;` — Ready to use string with any escaped characters translated
- L716 _public function_ `explicit CExprString(CUTF8String String) : _String(Move(String))`
- L719 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L720 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L722 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprPath`  
`class AUTORTFM_DISABLE CExprPath : public CExpressionBase`  
_L728-741_
- inherits: `CExpressionBase`
- desc: Path literal - /unrealengine.com/UnrealEngine
- L732 _public member_ `CUTF8String _Path;` — Ready to use path with any escaped characters translated
- L734 _public function_ `explicit CExprPath(CUTF8String Path) : _Path(Move(Path))`
- L737 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L738 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L740 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprPathPlusSymbol`  
`class AUTORTFM_DISABLE CExprPathPlusSymbol : public CExpressionBase`  
_L746-756_
- inherits: `CExpressionBase`
- desc: Expression that evaluates to the path of the current scope, plus a given symbol, semantic analysis replaces this node with a CExprString
- L749 _public member_ `const CSymbol _Symbol;`
- L751 _public function_ `explicit CExprPathPlusSymbol(const CSymbol& Symbol) : _Symbol(Symbol)`
- L754 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L755 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprIdentifierBase`  
`class AUTORTFM_DISABLE CExprIdentifierBase : public CExpressionBase`  
_L761-815_
- inherits: `CExpressionBase`
- desc: The base class of identifiers expressions.
- L765 _public function_ `CExprIdentifierBase(TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : _Context(Move(Context)), _Qualifier(Move(Qualifier))`
- L769 _public function_ `const TSPtr<CExpressionBase>& Context() const`
- L770 _public function_ `const TSPtr<CExpressionBase>& Qualifier() const`
- L772 _public function_ `TSPtr<CExpressionBase>&& TakeContext()`
- L773 _public function_ `TSPtr<CExpressionBase>&& TakeQualifier()`
- L775 _public function_ `void SetContext(TSPtr<CExpressionBase> Context)`
- L780 _public function_ `void SetQualifier(TSPtr<CExpressionBase> Qualifier)`
- L786 _public function_ `virtual bool MayHaveAttributes() const override` — CAstNode interface.
- L789 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override` — CExpressionBase interface.
- L790 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L798 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L804 _public function_ `virtual const CDefinition* IdentifierDefinition() const` — This is specifically named as such to avoid shadowing other virtual methods (such as on `CNominalType`).
- L810 _public function_ `virtual const CExprIdentifierBase* AsIdentifierBase() const override` — This node contains an identifier
- L813 _private member_ `TSPtr<CExpressionBase> _Context;`
- L814 _private member_ `TSPtr<CExpressionBase> _Qualifier;`

#### class `uLang::CExprEnumLiteral`  
`class AUTORTFM_DISABLE CExprEnumLiteral : public CExprIdentifierBase`  
_L821-837_
- inherits: `CExprIdentifierBase`
- desc: Enumerator - #GlobalEnum.enumeration, #.enumeration, MyType#Confirm.yes, #Confirm.yes, #.yes, MyType@set_size#size.medium, #size.medium, #.medium, #position.upper, #.upper
- L825 _public member_ `const CEnumerator* _Enumerator;` — Specific enumerator this represents - note that it also contains a pointer to its enumeration type.
- L827 _public function_ `explicit CExprEnumLiteral(const CEnumerator* Enumerator, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierBase(Move(Context), Move(Qualifier)) , _Enumerator(Enumerator)`
- L832 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L833 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L834 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L835 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`
- L836 _public prototype_ `virtual const CDefinition* IdentifierDefinition() const override;`

#### class `uLang::CExprType`  
`class AUTORTFM_DISABLE CExprType : public CExpressionBase`  
_L842-868_
- inherits: `CExpressionBase`
- desc: Type expression - type{<expr>}
- L846 _public member_ `const TSRef<CExpressionBase> _AbstractValue;`
- L848 _public function_ `CExprType(TSRef<CExpressionBase>&& AbstractValue, const CTypeType& TypeType) : _AbstractValue(Move(AbstractValue))`
- L854 _public function_ `const CTypeType* GetTypeType() const`
- L859 _public function_ `const CTypeBase* GetType() const`
- L865 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L866 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L867 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`

#### class `uLang::CExprFunctionLiteral`  
`class AUTORTFM_DISABLE CExprFunctionLiteral : public CExpressionBase`  
_L873-895_
- inherits: `CExpressionBase`
- desc: Function literal - a=>b or function(a){b}
- L877 _public function_ `CExprFunctionLiteral(TSRef<CExpressionBase>&& Domain, TSRef<CExpressionBase>&& Range) : _Domain(Move(Domain)) , _Range(Move(Range))`
- L882 _public function_ `const TSRef<CExpressionBase>& Domain() const`
- L883 _public function_ `const TSRef<CExpressionBase>& Range () const`
- L885 _public function_ `void SetDomain(TSRef<CExpressionBase>&& NewDomain)`
- L886 _public function_ `void SetRange(TSRef<CExpressionBase>&& NewRange )`
- L888 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L889 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L890 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L893 _private member_ `TSRef<CExpressionBase> _Domain;`
- L894 _private member_ `TSRef<CExpressionBase> _Range;`

#### class `uLang::CExprSelf`  
`class AUTORTFM_DISABLE CExprSelf : public CExprIdentifierBase`  
_L900-916_
- inherits: `CExprIdentifierBase`
- desc: Access to the instance the current function is being invoked on.
- L903 _public function_ `CExprSelf(const CTypeBase* Type, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierBase(nullptr, Move(Qualifier))`
- L909 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L910 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L911 _public function_ `virtual const CDefinition* IdentifierDefinition() const override`

#### class `uLang::CExprLocal`  
`class AUTORTFM_DISABLE CExprLocal : public CExprIdentifierBase`  
_L919-942_
- inherits: `CExprIdentifierBase`
- desc: Represents the `(local:) qualifier`.
- L922 _public function_ `CExprLocal(const CScope& Scope) : CExprIdentifierBase(), _Scope(Scope)`
- L925 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L930 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L935 _public function_ `const CScope& GetScope() const`
- L941 _private member_ `const CScope& _Scope;`

#### class `uLang::CExprIdentifierBuiltInMacro`  
`class AUTORTFM_DISABLE CExprIdentifierBuiltInMacro : public CExprIdentifierBase`  
_L948-963_
- inherits: `CExprIdentifierBase`
- desc: Represents a name of a a compiler built-in macro; e.g. option, array. These should always be resolved by analysis and never make their way into code gen.
- L951 _public member_ `const CSymbol _Symbol;`
- L953 _public function_ `CExprIdentifierBuiltInMacro(const CSymbol Symbol, const CTypeBase* Type) : CExprIdentifierBase(nullptr, nullptr) , _Symbol(Symbol)`
- L960 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L961 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L962 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprIdentifierUnresolved`  
`class AUTORTFM_DISABLE CExprIdentifierUnresolved : public CExprIdentifierBase`  
_L968-995_
- inherits: `CExprIdentifierBase`
- desc: An unresolved type identifier that is produced by desugaring, and consumed by analysis.
- L971 _public member_ `const CSymbol _Symbol;`
- L976 _public member_ `bool _bAllowUnrestrictedAccess;` — Used for some internal compiler-generated code that is allowed to lookup identifiers that are otherwise restricted (private, internal, ...)
- L978 _public member_ `const bool _bAllowReservedOperators;`
- L980 _public function_ `CExprIdentifierUnresolved(const CSymbol& Symbol, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr, bool bAllowReservedOperators = false) : CExprIdentifierBase( Move(Context), Move(Qualifier)) , _Symbol(Symbol) , _bAllowUnrestrictedAccess(false) , _bAllowReservedOperators(bAllowReservedOperators)`
- L989 _public function_ `void GrantUnrestrictedAccess()` — Use with extreme caution! Setting this allows this identifier lookup to succeed where it would otherwise fail due to not having permission
- L991 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L992 _public function_ `virtual bool MayHaveAttributes() const override`
- L993 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L994 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprIdentifierClass`  
`class AUTORTFM_DISABLE CExprIdentifierClass : public CExprIdentifierBase`  
_L1001-1012_
- inherits: `CExprIdentifierBase`
- desc: Type identifier - MyType
- L1005 _public prototype_ `CExprIdentifierClass(const CTypeType* Type, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr);`
- L1007 _public prototype_ `const CTypeType* GetTypeType(const CSemanticProgram& Program) const;`
- L1008 _public prototype_ `const CClass* GetClass(const CSemanticProgram& Program) const;`
- L1010 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1011 _public prototype_ `virtual CUTF8String GetErrorDesc() const override;`

#### class `uLang::CExprIdentifierModule`  
`class AUTORTFM_DISABLE CExprIdentifierModule : public CExprIdentifierBase`  
_L1017-1027_
- inherits: `CExprIdentifierBase`
- desc: Module identifier
- L1021 _public prototype_ `CExprIdentifierModule(const CModule* Module, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr);`
- L1023 _public prototype_ `CModule const* GetModule(const CSemanticProgram& Program) const;`
- L1025 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1026 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprIdentifierModuleAlias`  
`class AUTORTFM_DISABLE CExprIdentifierModuleAlias : public CExprIdentifierBase`  
_L1032-1045_
- inherits: `CExprIdentifierBase`
- desc: Module alias identifier
- L1036 _public member_ `const CModuleAlias& _ModuleAlias;`
- L1038 _public function_ `CExprIdentifierModuleAlias(const CModuleAlias& ModuleAlias, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierBase(Move(Context), Move(Qualifier)) , _ModuleAlias(ModuleAlias)`
- L1043 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1044 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprEnumerationType`  
`class AUTORTFM_DISABLE CExprEnumerationType : public CExprIdentifierBase`  
_L1051-1066_
- inherits: `CExprIdentifierBase`
- desc: Enum identifier @jira SOL-1013 : Shouldn't this inherit from CExprIdentifierClass?
- L1055 _public function_ `CExprEnumerationType(const CTypeType* TypeType, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierBase(Move(Context), Move(Qualifier))`
- L1061 _public prototype_ `const CTypeType* GetTypeType(const CSemanticProgram& Program) const;`
- L1062 _public prototype_ `const CEnumeration* GetEnumeration(const CSemanticProgram& Program) const;`
- L1064 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1065 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprInterfaceType`  
`class AUTORTFM_DISABLE CExprInterfaceType : public CExprIdentifierBase`  
_L1072-1089_
- inherits: `CExprIdentifierBase`
- desc: Interface identifier @jira SOL-1013 : Shouldn't this inherit from CExprIdentifierClass?
- L1078 _public function_ `CExprInterfaceType(const CTypeType* TypeType, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierBase(Move(Context), Move(Qualifier))`
- L1084 _public function_ `const CTypeType* GetTypeType(const CSemanticProgram& Program) const`
- L1085 _public prototype_ `const CInterface* GetInterface(const CSemanticProgram& Program) const;`
- L1087 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1088 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprIdentifierData`  
`class AUTORTFM_DISABLE CExprIdentifierData : public CExprIdentifierBase`  
_L1095-1110_
- inherits: `CExprIdentifierBase`
- desc: Local or class identifier - temp, arg, captured
- L1100 _public member_ `const CDataDefinition& _DataDefinition;` — The variable this expression is referring to
- L1102 _public prototype_ `CExprIdentifierData(const CSemanticProgram& Program, const CDataDefinition& DataDefinition, TSPtr<CExpressionBase> Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr);`
- L1104 _public function_ `virtual const CSymbol& GetName() const`
- L1106 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1107 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1108 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L1109 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprIdentifierTypeAlias`  
`class AUTORTFM_DISABLE CExprIdentifierTypeAlias : public CExprIdentifierBase`  
_L1115-1128_
- inherits: `CExprIdentifierBase`
- desc: Access to a type alias
- L1120 _public member_ `const CTypeAlias& _TypeAlias;` — The type alias this expression is referring to
- L1122 _public prototype_ `CExprIdentifierTypeAlias(const CTypeAlias& TypeAlias, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr);`
- L1124 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1125 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1126 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L1127 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprIdentifierTypeVariable`  
`class AUTORTFM_DISABLE CExprIdentifierTypeVariable : public CExprIdentifierBase`  
_L1133-1145_
- inherits: `CExprIdentifierBase`
- desc: Access to a type variable
- L1138 _public member_ `const CTypeVariable& _TypeVariable;` — The type variable this expression is referring to
- L1140 _public prototype_ `CExprIdentifierTypeVariable(const CTypeVariable& TypeVariable, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr);`
- L1142 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1143 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1144 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprIdentifierFunction`  
`class AUTORTFM_DISABLE CExprIdentifierFunction : public CExprIdentifierBase`  
_L1150-1182_
- inherits: `CExprIdentifierBase`
- desc: Access to instance function members
- L1154 _public member_ `const CFunction& _Function;`
- L1156 _public member_ `TArray<SInstantiatedTypeVariable> _InstantiatedTypeVariables;` — `CFlowType`s created as part of instantiating `_Function`.
- L1157 _public member_ `const CTypeBase* _ConstructorNegativeReturnType;`
- L1158 _public member_ `CCaptureScope* _ConstructorCaptureScope = nullptr;`
- L1159 _public member_ `const bool _bSuperQualified;`
- L1161 _public function_ `CExprIdentifierFunction( const CFunction& Function, const CTypeBase* ResultType, TSPtr<CExpressionBase>&& Context = nullptr, TSPtr<CExpressionBase>&& Qualifier = nullptr) : CExprIdentifierFunction(Function, {}, ResultType, nullptr, nullptr, Move(Context), Move(Qualifier), false)`
- L1169 _public prototype_ `CExprIdentifierFunction( const CFunction& Function, TArray<SInstantiatedTypeVariable> InstTypeVariables, const CTypeBase* ResultType, const CTypeBase* ConstructorNegativeReturnType, CCaptureScope* ConstructorCaptureScope, TSPtr<CExpressionBase>&& Context, TSPtr<CExpressionBase>&& Qualifier, bool bSuperQualified);`
- L1179 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1180 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1181 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprIdentifierOverloadedFunction`  
`class AUTORTFM_DISABLE CExprIdentifierOverloadedFunction : public CExprIdentifierBase`  
_L1187-1213_
- inherits: `CExprIdentifierBase`
- desc: An overloaded function identifier that hasn't been resolved to a specific overload.
- L1191 _public member_ `const TArray<const CFunction*> _FunctionOverloads;`
- L1192 _public member_ `bool _bConstructor;`
- L1193 _public member_ `const CSymbol _Symbol;`
- L1194 _public member_ `const CTypeBase* _TypeOverload;`
- L1199 _public member_ `bool _bAllowUnrestrictedAccess;` — Used for some internal compiler-generated code that is allowed to lookup identifiers that are otherwise restricted (private, internal, ...)
- L1201 _public prototype_ `CExprIdentifierOverloadedFunction( TArray<const CFunction*>&& OverloadedFunctions, bool bConstructor, const CSymbol Symbol, const CTypeBase* OverloadedType, TSPtr<CExpressionBase>&& Context, TSPtr<CExpressionBase>&& Qualifier, const CTypeBase* Type);`
- L1210 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1211 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1212 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprDefinition`  
`class AUTORTFM_DISABLE CExprDefinition : public CExpressionBase`  
_L1222-1271_
- inherits: `CExpressionBase`
- desc: Represents all definitions (and assignments) supported by Verse. They are: element:valueDomain=value   e.g. x:int=5     e.g. f(x:int):int=x*x element:valueDomain         e.g. x:int       e.g. f(x:int):int element=value               e.g. x=5         e.g. f(x:int)=x*x
- L1225 _public function_ `CExprDefinition(TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType)`
- L1233 _public function_ `explicit CExprDefinition(EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType)`
- L1235 _public function_ `const TSPtr<CExpressionBase>& Element() const`
- L1236 _public function_ `void SetElement(TSRef<CExpressionBase>&& Element)`
- L1237 _public function_ `TSPtr<CExpressionBase> TakeElement()`
- L1239 _public function_ `void SetName(CSymbol Name)`
- L1240 _public function_ `CSymbol GetName() const`
- L1241 _public function_ `bool IsNamed() const`
- L1243 _public function_ `const TSPtr<CExpressionBase>& ValueDomain() const`
- L1244 _public function_ `void SetValueDomain(TSRef<CExpressionBase>&& ValueDomain)`
- L1245 _public function_ `TSPtr<CExpressionBase> TakeValueDomain()`
- L1247 _public function_ `const TSPtr<CExpressionBase>& Value() const`
- L1248 _public function_ `void SetValue(TSRef<CExpressionBase>&& Value)`
- L1249 _public function_ `TSPtr<CExpressionBase> TakeValue()`
- L1251 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`
- L1257 _public function_ `virtual EAstNodeType GetNodeType() const override` — CAstNode interface.
- L1258 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1259 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1260 _public function_ `virtual bool MayHaveAttributes() const override`
- L1263 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;` — CExpressionBase interface.
- L1264 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L1267 _protected member_ `TSPtr<CExpressionBase> _Element;`
- L1268 _protected member_ `TSPtr<CExpressionBase> _ValueDomain;`
- L1269 _protected member_ `TSPtr<CExpressionBase> _Value;`
- L1270 _protected member_ `CSymbol _Name;` — If non-null, then usage requires being ?named and presence of `_Value` indicates that it has a default

#### enum `uLang::EMacroClauseTag`  
`enum class EMacroClauseTag : uint32_t`  
_L1274-1279_
- L1276 _public enumerator_ `None = 0x1 << 0`
- L1277 _public enumerator_ `Of = 0x1 << 1`
- L1278 _public enumerator_ `Do = 0x1 << 2`

#### class `uLang::CExprMacroCall`  
`class AUTORTFM_DISABLE CExprMacroCall : public CExpressionBase`  
_L1311-1419_
- inherits: `CExpressionBase`
- desc: A macro call of the form m1{}, m2(){}, or more generally m(){}keyword_1{}keyword_2{}...keyword_N{}
- L1342 _public function_ `CExprMacroCall( TSRef<CExpressionBase>&& Name, int32_t NumClauses = 0 ) : _Name(Move(Name)) , _Clauses()`
- L1352 _public function_ `void AppendClause(CClause&& Clause)`
- L1357 _public function_ `TSRef<CExpressionBase> const & Name() const`
- L1358 _public function_ `TSRef<CExpressionBase> & Name()`
- L1359 _public function_ `void SetName(TSRef<CExpressionBase>&& NewName)`
- L1361 _public function_ `TSRef<CExpressionBase>&& TakeName()`
- L1363 _public function_ `TArray<CClause> const& Clauses() const`
- L1364 _public function_ `TArray<CClause> & Clauses()`
- L1366 _public function_ `TArray<CClause>&& TakeClauses()`
- L1368 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`
- L1391 _private function_ `virtual EAstNodeType GetNodeType() const override` — Inherited via CExpressionBase
- L1392 _private function_ `virtual CUTF8String GetErrorDesc() const override`
- L1394 _private function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1404 _private function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1417 _private member_ `TSRef<CExpressionBase> _Name;`
- L1418 _private member_ `TArray<CClause> _Clauses;`

#### class `uLang::CExprMacroCall::CClause`  
`class CClause`  
_L1317-1338_
- desc: A macro is an identifier followed by any number of tagged clauses. This class represents a single clause.
- L1320 _public typedef_ `using EForm = Verse::Vst::Clause::EForm;`
- L1322 _public function_ `CClause(EMacroClauseTag Tag, EForm Form, TArray<TSRef<CExpressionBase>>&& Exprs) : _Tag(Tag) , _Form(Form) , _Exprs(Move(Exprs))`
- L1328 _public function_ `EMacroClauseTag Tag() const`
- L1329 _public function_ `EForm Form() const`
- L1330 _public function_ `TArray<TSRef<CExpressionBase>> const & Exprs() const`
- L1331 _public function_ `TArray<TSRef<CExpressionBase>> & Exprs()`
- L1335 _private member_ `EMacroClauseTag _Tag;`
- L1336 _private member_ `Verse::Vst::Clause::EForm _Form;`
- L1337 _private member_ `TArray<TSRef<CExpressionBase>> _Exprs;`

#### class `uLang::CExprInvocation`  
`class AUTORTFM_DISABLE CExprInvocation : public CExpressionBase`  
_L1425-1514_
- inherits: `CExpressionBase`
- desc: Routine call - expr1.call(expr2, expr3)
- L1435 _public member_ `EBracketingStyle _CallsiteBracketStyle = EBracketingStyle::Undefined;`
- L1438 _public function_ `template<typename TCallee, typename TArgument> CExprInvocation(EBracketingStyle CallsiteBracketStyle, TCallee&& Callee, TArgument&& Argument) : _CallsiteBracketStyle(CallsiteBracketStyle) , _Callee(ForwardArg<TCallee>(Callee)) , _Argument(ForwardArg<TArgument>(Argument))`
- L1445 _public function_ `template<typename TCallee, typename TArgument> CExprInvocation(EBracketingStyle CallsiteBracketStyle, TCallee&& Callee, TArgument&& Argument, const CFunctionType* ResolvedCalleeType, const CTypeBase* ResultType) : CExprInvocation(CallsiteBracketStyle, ForwardArg<TCallee>(Callee), ForwardArg<TArgument>(Argument))`
- L1456 _public function_ `explicit CExprInvocation(TSRef<CExpressionBase>&& Argument) : _Argument(Move(Argument))`
- L1460 _public function_ `CExprInvocation(CExprInvocation&& Rhs) : _Callee(Move(Rhs._Callee)) , _Argument(Move(Rhs._Argument)) , _ResolvedCalleeType(Rhs._ResolvedCalleeType)`
- L1466 _public function_ `const TSPtr<CExpressionBase>& GetCallee() const`
- L1467 _public function_ `TSPtr<CExpressionBase>&& TakeCallee()`
- L1468 _public function_ `void SetCallee(TSPtr<CExpressionBase>&& Callee)`
- L1470 _public function_ `const TSRef<CExpressionBase>& GetArgument() const`
- L1471 _public function_ `TSRef<CExpressionBase>&& TakeArgument()`
- L1472 _public function_ `void SetArgument(TSRef<CExpressionBase>&& Arguments)`
- L1474 _public prototype_ `const CFunctionType* GetResolvedCalleeType() const;`
- L1475 _public function_ `void SetResolvedCalleeType(const CFunctionType* ResolvedCalleeType)`
- L1478 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;` — Get the function that this invocation calls
- L1480 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`
- L1481 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1482 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1483 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1484 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1503 _public member_ `bool bResultUsed { true };` — We conservatively say true. But some optimizations rely on us proving this is false.
- L1506 _private member_ `TSPtr<CExpressionBase> _Callee;` — Callee subexpression - The function to call.
- L1509 _private member_ `TSRef<CExpressionBase> _Argument;` — Argument - possibly a tuple of expressions, included named expressions
- L1513 _private member_ `const CFunctionType* _ResolvedCalleeType{nullptr};` — More often than not, the function type could be inferred from _Callee, but in the case of generics, you want to store the function type of the resolved generic.

#### enum `uLang::CExprInvocation::EBracketingStyle`  
`enum class EBracketingStyle`  
_L1429-1434_
- L1431 _public enumerator_ `Undefined`
- L1432 _public enumerator_ `Parentheses`
- L1433 _public enumerator_ `SquareBrackets`

#### class `uLang::CExprTupleElement`  
`class AUTORTFM_DISABLE CExprTupleElement : public CExpressionBase`  
_L1527-1562_
- inherits: `CExpressionBase`
- desc: Tuple element access `TupleExpr(Idx)`
- L1532 _public member_ `TSPtr<CExpressionBase> _TupleExpr;` — Expression that results in tuple to access element from
- L1535 _public member_ `Integer _ElemIdx;` — Index resolved from `_ElemIdxExpr`
- L1539 _public member_ `TSPtr<CExpressionBase> _ElemIdxExpr;` — Expression used to determine index - currently must be an integer literal CExprNumber. `_ElemIdx` is resolved form.
- L1541 _public function_ `CExprTupleElement(CExprInvocation& Invocation) : _TupleExpr(Invocation.TakeCallee()), _ElemIdx(-1)`
- L1542 _public function_ `CExprTupleElement(TSPtr<CExpressionBase> TupleExpr, Integer ElemIdx, const Verse::Vst::Node* MappedVstNode) : _TupleExpr(TupleExpr), _ElemIdx(ElemIdx)`
- L1544 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`
- L1545 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1546 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1547 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1548 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1550 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`

#### class `uLang::CExprAssignment`  
`class AUTORTFM_DISABLE CExprAssignment : public CExpressionBase`  
_L1568-1601_
- inherits: `CExpressionBase`
- desc: Assignment -- expr1 = expr2, expr1 := expr2, expr1 += expr2, etc.
- L1571 _public typedef_ `using EOp = Verse::Vst::Assignment::EOp;`
- L1573 _public function_ `CExprAssignment(EOp Op, TSRef<CExpressionBase>&& Lhs, TSRef<CExpressionBase>&& Rhs) : _Op(Op), _Lhs(Move(Lhs)), _Rhs(Move(Rhs))`
- L1577 _public function_ `EOp Op() const`
- L1578 _public function_ `const TSRef<CExpressionBase>& Lhs() const`
- L1579 _public function_ `const TSRef<CExpressionBase>& Rhs() const`
- L1581 _public function_ `TSRef<CExpressionBase>&& TakeLhs()`
- L1582 _public function_ `TSRef<CExpressionBase>&& TakeRhs()`
- L1584 _public function_ `void SetLhs(TSRef<CExpressionBase>&& Lhs)`
- L1585 _public function_ `void SetRhs(TSRef<CExpressionBase>&& Rhs)`
- L1588 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L1589 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1590 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1592 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1593 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1594 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1598 _private member_ `const EOp _Op;`
- L1599 _private member_ `TSRef<CExpressionBase> _Lhs;`
- L1600 _private member_ `TSRef<CExpressionBase> _Rhs;`

#### struct `uLang::SAssignmentLhsIdentifier`  
`struct SAssignmentLhsIdentifier`  
_L1603-1607_
- L1605 _public member_ `TSPtr<CExprPointerToReference> PointerToReference;`
- L1606 _public member_ `TSPtr<CExprIdentifierData> IdentifierData;`

#### class `uLang::CExprUnaryOp`  
`class AUTORTFM_DISABLE CExprUnaryOp : public CExpressionBase`  
_L1616-1635_
- inherits: `CExpressionBase`
- desc: Base class of unary operators.
- L1619 _public function_ `explicit CExprUnaryOp(TSPtr<CExpressionBase>&& Operand, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType)`
- L1625 _public function_ `const TSPtr<CExpressionBase>& Operand() const`
- L1626 _public function_ `TSPtr<CExpressionBase>&& TakeOperand()`
- L1627 _public function_ `void SetOperand(TSPtr<CExpressionBase>&& Operand)`
- L1629 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L1630 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1634 _private member_ `TSPtr<CExpressionBase> _Operand;`

#### class `uLang::CExprUnaryArithmetic`  
`class AUTORTFM_DISABLE CExprUnaryArithmetic : public CExprInvocation`  
_L1638-1664_
- inherits: `CExprInvocation`
- L1646 _public function_ `CExprUnaryArithmetic(EOp Op, TSRef<CExpressionBase>&& Rhs) : CExprInvocation(Move(Rhs)) , _Op(Op)`
- L1652 _public function_ `TSRef<CExpressionBase> Operand() const`
- L1653 _public function_ `void SetOperand(TSRef<CExpressionBase>&& NewOperand)`
- L1654 _public function_ `TSRef<CExpressionBase>&& TakeOperand()`
- L1656 _public function_ `EOp Op() const`
- L1659 _private function_ `virtual EAstNodeType GetNodeType() const override`
- L1660 _private function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1661 _private function_ `virtual CUTF8String GetErrorDesc() const override`
- L1663 _private member_ `EOp _Op;`

#### enum `uLang::CExprUnaryArithmetic::EOp`  
`enum class EOp`  
_L1641-1644_
- L1643 _public enumerator_ `Negate`

#### class `uLang::CExprBinaryArithmetic`  
`class AUTORTFM_DISABLE CExprBinaryArithmetic : public CExprInvocation`  
_L1667-1715_
- inherits: `CExprInvocation`
- L1678 _public function_ `CExprBinaryArithmetic(EOp Op, TSRef<CExpressionBase>&& Argument) : CExprInvocation(Move(Argument)) , _Op(Op)`
- L1684 _public function_ `EOp Op() const`
- L1687 _private function_ `virtual EAstNodeType GetNodeType() const override`
- L1688 _private function_ `virtual CUTF8String GetErrorDesc() const override`
- L1699 _private function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1714 _private member_ `EOp _Op;`

#### enum `uLang::CExprBinaryArithmetic::EOp`  
`enum class EOp`  
_L1670-1676_
- L1672 _public enumerator_ `Add`
- L1673 _public enumerator_ `Sub`
- L1674 _public enumerator_ `Mul`
- L1675 _public enumerator_ `Div`

#### class `uLang::CExprShortCircuitAnd`  
`class AUTORTFM_DISABLE CExprShortCircuitAnd : public CExprBinaryOp`  
_L1720-1730_
- inherits: `CExprBinaryOp`
- desc: Short-circuit evaluation of a Boolean and
- L1724 _public function_ `CExprShortCircuitAnd(TSPtr<CExpressionBase>&& Lhs, TSPtr<CExpressionBase>&& Rhs) : CExprBinaryOp(Move(Lhs), Move(Rhs))`
- L1726 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1727 _public function_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override`
- L1728 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1729 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprShortCircuitOr`  
`class AUTORTFM_DISABLE CExprShortCircuitOr : public CExprBinaryOp`  
_L1736-1755_
- inherits: `CExprBinaryOp`
- desc: Short-circuit evaluation of a Boolean or
- L1740 _public function_ `CExprShortCircuitOr(TSPtr<CExpressionBase>&& Lhs, TSPtr<CExpressionBase>&& Rhs, const CTypeBase* JoinType = nullptr) : CExprBinaryOp(Move(Lhs), Move(Rhs))`
- L1749 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1750 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1751 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprLogicalNot`  
`class AUTORTFM_DISABLE CExprLogicalNot : public CExprUnaryOp`  
_L1761-1771_
- inherits: `CExprUnaryOp`
- desc: Logical not operator
- L1765 _public function_ `CExprLogicalNot(TSPtr<CExpressionBase>&& Operand): CExprUnaryOp(Move(Operand))`
- L1767 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1768 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L1769 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1770 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprComparison`  
`class AUTORTFM_DISABLE CExprComparison : public CExprInvocation`  
_L1777-1797_
- inherits: `CExprInvocation`
- desc: Comparison operators.
- L1780 _public typedef_ `using EOp = Verse::Vst::BinaryOpCompare::op;`
- L1782 _public function_ `CExprComparison(EOp Op, TSRef<CExpressionBase>&& Argument) : CExprInvocation(Move(Argument)) , _Op(Op)`
- L1789 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1790 _public prototype_ `virtual CUTF8String GetErrorDesc() const override;`
- L1791 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L1793 _public function_ `EOp Op() const`
- L1796 _private member_ `EOp _Op;`

#### class `uLang::CExprQueryValue`  
`class AUTORTFM_DISABLE CExprQueryValue : public CExprInvocation`  
_L1803-1815_
- inherits: `CExprInvocation`
- desc: Query the value of a boolean or option value.
- L1807 _public function_ `CExprQueryValue(TSRef<CExpressionBase>&& Operand) : CExprInvocation(Move(Operand))`
- L1813 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1814 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprMakeOption`  
`class AUTORTFM_DISABLE CExprMakeOption : public CExprUnaryOp`  
_L1821-1840_
- inherits: `CExprUnaryOp`
- desc: Box an option value
- L1825 _public function_ `CExprMakeOption(const CTypeBase* Type, TSPtr<CExpressionBase>&& Operand) : CExprUnaryOp(Move(Operand))`
- L1831 _public function_ `COptionType const* GetOptionType(const CSemanticProgram& Program) const`
- L1837 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1838 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1839 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprMakeArray`  
`class AUTORTFM_DISABLE CExprMakeArray : public CExprCompoundBase`  
_L1847-1861_
- inherits: `CExprCompoundBase`
- desc: Create an array value Can have zero or more subexpressions
- L1850 _public function_ `CExprMakeArray(int32_t ReserveSubExprNum) : CExprCompoundBase(ReserveSubExprNum)`
- L1852 _public function_ `const CArrayType* GetArrayType(const CSemanticProgram& Program) const`
- L1858 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1859 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprMakeMap`  
`class AUTORTFM_DISABLE CExprMakeMap : public CExprCompoundBase`  
_L1867-1882_
- inherits: `CExprCompoundBase`
- desc: Create a map value Can have zero or more subexpressions
- L1870 _public function_ `explicit CExprMakeMap(int32_t ReserveSubExprNum = 0) : CExprCompoundBase(ReserveSubExprNum)`
- L1872 _public function_ `const CMapType* GetMapType(const CSemanticProgram& Program) const`
- L1878 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1879 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1880 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`

#### class `uLang::CExprMakeTuple`  
`class AUTORTFM_DISABLE CExprMakeTuple : public CExprCompoundBase`  
_L1887-1901_
- inherits: `CExprCompoundBase`
- desc: Create a tuple value
- L1892 _public function_ `const CTupleType* GetTupleType(const CSemanticProgram& Program) const`
- L1898 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1899 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprMakeRange`  
`class AUTORTFM_DISABLE CExprMakeRange : public CExpressionBase`  
_L1907-1932_
- inherits: `CExpressionBase`
- desc: Create a range value
- L1910 _public member_ `TSRef<CExpressionBase> _Lhs;`
- L1911 _public member_ `TSRef<CExpressionBase> _Rhs;`
- L1913 _public function_ `CExprMakeRange(TSRef<CExpressionBase>&& Lhs, TSRef<CExpressionBase>&& Rhs) : _Lhs(Move(Lhs)) , _Rhs(Move(Rhs))`
- L1918 _public function_ `void SetLhs(TSRef<CExpressionBase>&& Lhs)`
- L1919 _public function_ `void SetRhs(TSRef<CExpressionBase>&& Rhs)`
- L1922 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1923 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1924 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1927 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`

#### class `uLang::CExprInvokeType`  
`class AUTORTFM_DISABLE CExprInvokeType : public CExpressionBase`  
_L1938-1961_
- inherits: `CExpressionBase`
- desc: Invoke a type as a function on a value - type(expr) or type[expr].
- L1941 _public member_ `const CTypeBase* _NegativeType;`
- L1942 _public member_ `const bool _bIsFallible;`
- L1943 _public member_ `const TSPtr<CExpressionBase> _TypeAst;`
- L1944 _public member_ `const TSRef<CExpressionBase> _Argument;`
- L1946 _public prototype_ `CExprInvokeType(const CTypeBase* NegativeType, const CTypeBase* PositiveType, bool bIsFallible, TSPtr<CExpressionBase>&& TypeAst, TSRef<CExpressionBase>&& Argument);`
- L1949 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L1950 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1951 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1952 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1953 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L1954 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprPointerToReference`  
`class AUTORTFM_DISABLE CExprPointerToReference : public CExprUnaryOp`  
_L1967-1985_
- inherits: `CExprUnaryOp`
- desc: Read the value of a variable.
- L1970 _public function_ `CExprPointerToReference(TSRef<CExpressionBase>&& Variable, bool bWritable = true) : CExprUnaryOp(Move(Variable)) , _bWritable(bWritable)`
- L1977 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L1978 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L1979 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L1980 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L1984 _private member_ `bool _bWritable;`

#### class `uLang::CExprSet`  
`class AUTORTFM_DISABLE CExprSet : public CExprUnaryOp`  
_L1990-2011_
- inherits: `CExprUnaryOp`
- desc: Evaluate operand to an l-expression.
- L1993 _public function_ `CExprSet(bool bIsLive, TSPtr<CExpressionBase> Operand, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprSet`
- L1998 _public function_ `CExprSet(bool bIsLive, CCaptureControlScope* LiveScope, TSPtr<CExpressionBase> Operand, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprUnaryOp`
- L2005 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2006 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2007 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2009 _public member_ `bool _bIsLive;`
- L2010 _public member_ `CCaptureControlScope* _LiveScope = nullptr;`

#### class `uLang::CExprNewPointer`  
`class AUTORTFM_DISABLE CExprNewPointer : public CExpressionBase`  
_L2016-2036_
- inherits: `CExpressionBase`
- desc: Create a new pointer from an initial value.
- L2019 _public member_ `CCaptureControlScope* _LiveScope;`
- L2020 _public member_ `const TSRef<CExpressionBase> _Value;`
- L2022 _public function_ `CExprNewPointer(const CPointerType* PointerType, CCaptureControlScope* LiveScope, TSRef<CExpressionBase> Value) : CExpressionBase(PointerType) , _LiveScope(LiveScope) , _Value(Move(Value))`
- L2030 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2031 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2032 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2033 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2034 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`

#### class `uLang::CExprReferenceToValue`  
`class AUTORTFM_DISABLE CExprReferenceToValue : public CExprUnaryOp`  
_L2041-2051_
- inherits: `CExprUnaryOp`
- desc: Evaluates the value of an expression yielding a reference type.
- L2044 _public prototype_ `explicit CExprReferenceToValue(TSPtr<CExpressionBase> Operand);`
- L2047 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2048 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2049 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprCodeBlock`  
`class AUTORTFM_DISABLE CExprCodeBlock : public CExprCompoundBase`  
_L2057-2071_
- inherits: `CExprCompoundBase`
- desc: Code block - `{expr1; expr2}` or `do {expr1; expr2}` Can have zero or more subexpressions
- L2061 _public member_ `TSPtr<CControlScope> _AssociatedScope;` — The scope containing locals for this block
- L2065 _public function_ `explicit CExprCodeBlock(int32_t ReserveSubExprNum = 0) : CExprCompoundBase(ReserveSubExprNum)`
- L2066 _public function_ `explicit CExprCodeBlock(TArray<TSRef<CExpressionBase>>&& SubExprs) : CExprCompoundBase(Move(SubExprs))`
- L2068 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2069 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2070 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`

#### class `uLang::CExprLet`  
`class AUTORTFM_DISABLE CExprLet : public CExprCompoundBase`  
_L2073-2079_
- inherits: `CExprCompoundBase`
- L2076 _private function_ `virtual EAstNodeType GetNodeType() const override`
- L2077 _private function_ `virtual CUTF8String GetErrorDesc() const override`
- L2078 _private prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`

#### class `uLang::CExprReturn`  
`class AUTORTFM_DISABLE CExprReturn : public CExpressionBase`  
_L2084-2117_
- inherits: `CExpressionBase`
- desc: Return statement - return expr
- L2088 _public function_ `CExprReturn()`
- L2089 _public function_ `CExprReturn(TSPtr<CExpressionBase>&& Result, const CFunction* Function = nullptr)`
- L2095 _public function_ `const TSPtr<CExpressionBase>& Result() const`
- L2096 _public function_ `void SetResult(TSPtr<CExpressionBase>&& Result)`
- L2098 _public function_ `const CFunction* Function() const`
- L2099 _public function_ `void SetFunction(const CFunction* Function)`
- L2101 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2102 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2103 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2104 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2105 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L2106 _public function_ `virtual bool MayHaveAttributes() const override`
- L2108 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2113 _private member_ `TSPtr<CExpressionBase> _Result;` — Result expression
- L2116 _private member_ `const CFunction* _Function{nullptr};` — The function being returned from.

#### class `uLang::CExprIf`  
`class AUTORTFM_DISABLE CExprIf : public CExpressionBase`  
_L2123-2156_
- inherits: `CExpressionBase`
- desc: Conditional with failable tests- if (test[]) {clause1}, if (test[]) {clause1} else {else_clause}
- L2127 _public function_ `CExprIf(TSRef<CExprCodeBlock>&& Condition, TSPtr<CExpressionBase>&& ThenClause, TSPtr<CExpressionBase>&& ElseClause = nullptr) : _Condition(Move(Condition)) , _ThenClause(Move(ThenClause)) , _ElseClause(Move(ElseClause))`
- L2133 _public function_ `const TSRef<CExprCodeBlock>& GetCondition() const`
- L2134 _public function_ `void SetCondition(TSRef<CExprCodeBlock>&& Condition)`
- L2136 _public function_ `const TSPtr<CExpressionBase>& GetThenClause() const`
- L2137 _public function_ `void SetThenClause(TSPtr<CExpressionBase>&& ThenClause)`
- L2139 _public function_ `const TSPtr<CExpressionBase>& GetElseClause() const`
- L2140 _public function_ `void SetElseClause(TSPtr<CExpressionBase>&& ElseClause)`
- L2142 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L2143 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`
- L2144 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2145 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2146 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2147 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L2150 _public member_ `bool _bIsFilter{ false };` — If can be used as a filter in a for(..) { }. Code generation need to know.
- L2153 _private member_ `TSRef<CExprCodeBlock> _Condition;`
- L2154 _private member_ `TSPtr<CExpressionBase> _ThenClause;`
- L2155 _private member_ `TSPtr<CExpressionBase> _ElseClause;`

#### class `uLang::CExprIteration`  
`class AUTORTFM_DISABLE CExprIteration : public CExpressionBase`  
_L2162-2186_
- inherits: `CExpressionBase`
- desc: Bounded iteration
- L2166 _public function_ `CExprIteration()`
- L2167 _public function_ `CExprIteration(TSPtr<CExprCodeBlock>&& Filters) : _Filters(Move(Filters))`
- L2169 _public function_ `void SetBody(TSPtr<CExpressionBase>&& Body)`
- L2170 _public function_ `void AddFilter(TSRef<CExpressionBase>&& Filter)`
- L2175 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L2176 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2177 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2178 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2179 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2182 _public member_ `TSPtr<CExprCodeBlock> _Filters;`
- L2185 _public member_ `TSPtr<CExpressionBase> _Body;` — Expression to evaluate for every iteration that gets past the filters step

#### class `uLang::CExprFirst`  
`class AUTORTFM_DISABLE CExprFirst : public CExprIteration`  
_L2191-2197_
- inherits: `CExprIteration`
- desc: First - first(item:collection; pred(item)) {item}
- L2194 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2195 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2196 _public function_ `virtual EAstNodeType GetNodeType() const override`

#### class `uLang::CExprConcurrentIteratedBase`  
`class AUTORTFM_DISABLE CExprConcurrentIteratedBase : public CExprIteration`  
_L2202-2206_
- inherits: `CExprIteration`
- desc: Iteration based concurrency primitives - sync(item:collection){}, rush(item:collection){} or race(item:collection){}
- L2205 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`

#### class `uLang::CExprSyncIterated`  
`class AUTORTFM_DISABLE CExprSyncIterated : public CExprConcurrentIteratedBase`  
_L2212-2217_
- inherits: `CExprConcurrentIteratedBase`
- desc: Iterated Sync (collection form) concurrency primitive - sync(item:collection) {_coro1() _coro2()}
- L2215 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2216 _public function_ `virtual EAstNodeType GetNodeType() const override`

#### class `uLang::CExprRushIterated`  
`class AUTORTFM_DISABLE CExprRushIterated : public CExprConcurrentIteratedBase`  
_L2223-2228_
- inherits: `CExprConcurrentIteratedBase`
- desc: Iterated Rush (collection form) concurrency primitive - rush(item:collection) {_coro1() _coro2()}
- L2226 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2227 _public function_ `virtual EAstNodeType GetNodeType() const override`

#### class `uLang::CExprRaceIterated`  
`class AUTORTFM_DISABLE CExprRaceIterated : public CExprConcurrentIteratedBase`  
_L2234-2239_
- inherits: `CExprConcurrentIteratedBase`
- desc: Iterated Race (collection form) concurrency primitive - race(item:collection) {_coro1() _coro2()}
- L2237 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2238 _public function_ `virtual EAstNodeType GetNodeType() const override`

#### class `uLang::CExprTypeFormer`  
`class AUTORTFM_DISABLE CExprTypeFormer : public CExpressionBase`  
_L2243-2253_
- inherits: `CExpressionBase`
- desc: Base class for all expressions that form a type out of input type(s)
- L2248 _public member_ `const CTypeType* _TypeType{nullptr};` — Metatype of the actual type formed.
- L2250 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2251 _public function_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override`
- L2252 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprUnaryTypeFormer`  
`class AUTORTFM_DISABLE CExprUnaryTypeFormer : public CExprTypeFormer`  
_L2256-2274_
- inherits: `CExprTypeFormer`
- L2260 _public function_ `CExprUnaryTypeFormer(TSRef<CExpressionBase>&& InnerTypeAst): _InnerTypeAst(Move(InnerTypeAst))`
- L2262 _public function_ `const TSRef<CExpressionBase>& GetInnerTypeAst() const`
- L2263 _public function_ `void SetInnerTypeAst(TSRef<CExpressionBase>&& InnerTypeAst)`
- L2266 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override` — CExpressionBase interface.
- L2269 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override` — CAstNode interface.
- L2273 _private member_ `TSRef<CExpressionBase> _InnerTypeAst;`

#### class `uLang::CExprArrayTypeFormer`  
`class AUTORTFM_DISABLE CExprArrayTypeFormer : public CExprUnaryTypeFormer`  
_L2277-2291_
- inherits: `CExprUnaryTypeFormer`
- L2281 _public function_ `CExprArrayTypeFormer(TSRef<CExpressionBase>&& InnerTypeAst): CExprUnaryTypeFormer(Move(InnerTypeAst))`
- L2283 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2284 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2286 _public function_ `const CArrayType* GetArrayType() const`

#### class `uLang::CExprGeneratorTypeFormer`  
`class AUTORTFM_DISABLE CExprGeneratorTypeFormer : public CExprUnaryTypeFormer`  
_L2293-2308_
- inherits: `CExprUnaryTypeFormer`
- L2298 _public function_ `CExprGeneratorTypeFormer(TSRef<CExpressionBase>&& InnerTypeAst) : CExprUnaryTypeFormer(Move(InnerTypeAst))` — Construct an expression that takes the `ValueType` and forms an Generator of `ValueType`.
- L2300 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2301 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2303 _public function_ `const CGeneratorType* GetGeneratorType() const`

#### class `uLang::CExprMapTypeFormer`  
`class AUTORTFM_DISABLE CExprMapTypeFormer : public CExprTypeFormer`  
_L2310-2345_
- inherits: `CExprTypeFormer`
- L2314 _public function_ `CExprMapTypeFormer(TArray<TSRef<CExpressionBase>>&& KeyTypeAsts, TSRef<CExpressionBase>&& ValueTypeAst) : CExprTypeFormer() , _KeyTypeAsts(KeyTypeAsts) , _ValueTypeAst(ValueTypeAst)`
- L2320 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2321 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2323 _public function_ `const TArray<TSRef<CExpressionBase>>& KeyTypeAsts() const`
- L2324 _public function_ `void SetKeyTypeAst(TSRef<CExpressionBase>&& KeyTypeAst, int32_t Index)`
- L2326 _public function_ `const TSRef<CExpressionBase>& ValueTypeAst() const`
- L2327 _public function_ `void SetValueTypeAst(TSRef<CExpressionBase>&& ValueTypeAst)`
- L2329 _public function_ `const CMapType* GetMapType() const`
- L2336 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;` — CExpressionBase interface.
- L2339 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override` — CAstNode interface.
- L2343 _private member_ `TArray<TSRef<CExpressionBase>> _KeyTypeAsts;`
- L2344 _private member_ `TSRef<CExpressionBase> _ValueTypeAst;`

#### class `uLang::CExprOptionTypeFormer`  
`class AUTORTFM_DISABLE CExprOptionTypeFormer : public CExprUnaryTypeFormer`  
_L2347-2361_
- inherits: `CExprUnaryTypeFormer`
- L2351 _public function_ `CExprOptionTypeFormer(TSRef<CExpressionBase>&& InnerTypeAst): CExprUnaryTypeFormer(Move(InnerTypeAst))`
- L2353 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2354 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2356 _public function_ `const COptionType* GetOptionType() const`

#### class `uLang::CExprSubtype`  
`class AUTORTFM_DISABLE CExprSubtype : public CExprUnaryTypeFormer`  
_L2363-2375_
- inherits: `CExprUnaryTypeFormer`
- L2367 _public function_ `CExprSubtype(TSRef<CExpressionBase>&& InnerTypeAst): CExprUnaryTypeFormer(Move(InnerTypeAst))` — Construct an expression that takes the `ValueType` and forms an option of `ValueType`.
- L2369 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2370 _public prototype_ `virtual CUTF8String GetErrorDesc() const override;`
- L2372 _public prototype_ `const CTypeType& GetSubtypeType() const;`
- L2374 _public member_ `ETypeConstraintFlags _SubtypeConstraint = ETypeConstraintFlags::None;`

#### class `uLang::CExprTupleType`  
`class AUTORTFM_DISABLE CExprTupleType : public CExprTypeFormer`  
_L2378-2405_
- inherits: `CExprTypeFormer`
- desc: Get or create a tuple based on `tuple(type1, type2, ...)`
- L2382 _public function_ `CExprTupleType(int32_t ReserveTypeExprNum = 0)`
- L2384 _public function_ `const TSPtrArray<CExpressionBase>& GetElementTypeExprs() const`
- L2385 _public function_ `TSPtrArray<CExpressionBase>& GetElementTypeExprs()`
- L2386 _public function_ `void ReplaceElementTypeExpr(TSPtr<CExpressionBase>&& TypeExpr, int32_t Index)`
- L2392 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2393 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2394 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2396 _public function_ `const CTupleType* GetTupleType() const`
- L2404 _protected member_ `TSPtrArray<CExpressionBase> _ElementTypeExprs;`

#### class `uLang::CExprArrow`  
`class AUTORTFM_DISABLE CExprArrow : public CExprTypeFormer`  
_L2411-2439_
- inherits: `CExprTypeFormer`
- desc: Create a function type from a parameter and return type. Also used on the LHS of a definition as a pattern for iteration pairs.
- L2415 _public function_ `CExprArrow(TSRef<CExpressionBase>&& Domain, TSRef<CExpressionBase>&& Range) : _Domain(Move(Domain)) , _Range(Move(Range))`
- L2420 _public function_ `const TSRef<CExpressionBase>& Domain() const`
- L2421 _public function_ `const TSRef<CExpressionBase>& Range() const`
- L2423 _public function_ `void SetDomain(TSRef<CExpressionBase>&& NewDomain)`
- L2424 _public function_ `void SetRange(TSRef<CExpressionBase>&& NewRange)`
- L2426 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2427 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2428 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2430 _public function_ `const CFunctionType* GetFunctionType() const`
- L2437 _private member_ `TSRef<CExpressionBase> _Domain;`
- L2438 _private member_ `TSRef<CExpressionBase> _Range;`

#### class `uLang::CExprArchetypeInstantiation`  
`class AUTORTFM_DISABLE CExprArchetypeInstantiation : public CExpressionBase`  
_L2445-2500_
- inherits: `CExpressionBase`
- desc: Represents an initializer-list style construction for certain object types; i.e.: Type{expr1, id=expr2, ...}
- L2448 _public prototype_ `CExprArchetypeInstantiation(TSRef<CExpressionBase>&& ClassAst, CExprMacroCall::CClause&& BodyAst, const CTypeBase* ResultType, const bool bIsDynamicConcreteType);`
- L2450 _public prototype_ `const CNominalType* GetClassOrInterface(const CSemanticProgram& Program) const;`
- L2452 _public function_ `const TSRefArray<CExpressionBase>& Arguments() const`
- L2454 _public function_ `int32_t AppendArgument(TSRef<CExpressionBase>&& Argument)`
- L2459 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2471 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2473 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2475 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2487 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L2494 _public member_ `TSRef<CExpressionBase> _ClassAst;`
- L2495 _public member_ `CExprMacroCall::CClause _BodyAst;`
- L2496 _public member_ `const bool _bIsDynamicConcreteType;`
- L2499 _private member_ `TSRefArray<CExpressionBase> _Arguments;`

#### class `uLang::CExprConcurrentBlockBase`  
`class AUTORTFM_DISABLE CExprConcurrentBlockBase : public CExprCompoundBase`  
_L2506-2512_
- inherits: `CExprCompoundBase`
- desc: Block based concurrency primitives - sync{}, rush{} or race{} Can have two or more async subexpressions - 0 or 1 is a warning or error.
- L2509 _public function_ `explicit CExprConcurrentBlockBase(int32_t ReserveSubExprNum = 0) : CExprCompoundBase(ReserveSubExprNum)`
- L2511 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`

#### class `uLang::CExprSync`  
`class AUTORTFM_DISABLE CExprSync : public CExprConcurrentBlockBase`  
_L2522-2527_
- inherits: `CExprConcurrentBlockBase`
- desc: Sync concurrency primitive - sync {_coro1() _coro2()} 2+ Async expressions run concurrently and next expression executed when *all* expressions completed. Its overall result is the result of the last expression in the block to complete (using most specific common compatible result type of all expressions or no result if there is no common type). Expressions may only be async (such as coroutines).
- L2525 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2526 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprRace`  
`class AUTORTFM_DISABLE CExprRace : public CExprConcurrentBlockBase`  
_L2537-2542_
- inherits: `CExprConcurrentBlockBase`
- desc: Race concurrency primitive - race {_coro1() _coro2()} 2+ Async expressions run concurrently and next expression executed when *fastest/first* expression completed and all other expressions are aborted. Its overall result is result of first expression in block to complete (using most specific common compatible result type of all expressions or no result if there is no common type).
- L2540 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2541 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprRush`  
`class AUTORTFM_DISABLE CExprRush : public CExprConcurrentBlockBase`  
_L2553-2558_
- inherits: `CExprConcurrentBlockBase`
- desc: Rush concurrency primitive - rush {_coro1() _coro2()} 2+ Async expressions run concurrently and next expression executed when *fastest/first* expression completed and all other expressions continue independently until each is fully completed. Its overall result is the result of the first expression in the block to complete (using most specific common compatible result type of all expressions or no result if there is no common type).
- L2556 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2557 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprSubBlockBase`  
`class AUTORTFM_DISABLE CExprSubBlockBase : public CExpressionBase`  
_L2564-2577_
- inherits: `CExpressionBase`
- desc: Expressions with a sub-block - branch, spawn, loop, defer
- L2568 _protected member_ `TSPtr<CExpressionBase> _BlockExpr;` — Sub-expression from block - either single expression or block of expressions
- L2572 _public function_ `void SetExpr(TSPtr<CExpressionBase>&& Expr)`
- L2573 _public function_ `const TSPtr<CExpressionBase>& Expr() const`
- L2575 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2576 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`

#### class `uLang::CExprBranch`  
`class AUTORTFM_DISABLE CExprBranch : public CExprSubBlockBase`  
_L2587-2594_
- inherits: `CExprSubBlockBase`
- desc: Branch concurrency primitive - branch {Coro()} One async expression started and next expression executed immediately while the started expression continues independently until completion or the surrounding context (such as a coroutine) completes in which case it aborts early. Result is a handle to the invoked coroutine / invoked expression (also known as a future or promise) tracking the expression.
- L2590 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2591 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2593 _public member_ `CCaptureControlScope* _Scope{nullptr};`

#### class `uLang::CExprSpawn`  
`class AUTORTFM_DISABLE CExprSpawn : public CExprSubBlockBase`  
_L2604-2611_
- inherits: `CExprSubBlockBase`
- desc: Spawn concurrency primitive - spawn {Coro()}  [future: spawn {Expr1; Expr2}] Async expression treated as a closure/lambda with next expression executed immediately while the started async expression continues independently. Has no result. spawn essentially makes any async expression an immediate expression. This also means that it can allow async expressions / coroutines to be called within immediate functions.
- L2607 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2608 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2610 _public member_ `CCaptureControlScope* _Scope{nullptr};`

#### class `uLang::CExprAwait`  
`class AUTORTFM_DISABLE CExprAwait : public CExprCompoundBase`  
_L2613-2630_
- inherits: `CExprCompoundBase`
- L2616 _public function_ `explicit CExprAwait(int32_t ReserveSubExprNum) : CExprCompoundBase(ReserveSubExprNum)`
- L2621 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2623 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2625 _public function_ `virtual bool MayHaveAttributes() const override`
- L2627 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2629 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`

#### class `uLang::CExprBatch`  
`class AUTORTFM_DISABLE CExprBatch : public CExprCompoundBase`  
_L2632-2647_
- inherits: `CExprCompoundBase`
- L2635 _public function_ `explicit CExprBatch(int32_t ReserveSubExprNum) : CExprCompoundBase(ReserveSubExprNum)`
- L2640 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2642 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2644 _public function_ `virtual bool MayHaveAttributes() const override`
- L2646 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram&) const override`

#### class `uLang::CExprBinaryAwaitOp`  
`class AUTORTFM_DISABLE CExprBinaryAwaitOp : public CExpressionBase`  
_L2649-2705_
- inherits: `CExpressionBase`
- L2652 _public function_ `CExprBinaryAwaitOp(TSRefArray<CExpressionBase> DomainExprs, TSRefArray<CExpressionBase> RangeExprs) : _DomainExprs(Move(DomainExprs)) , _RangeExprs(Move(RangeExprs))`
- L2658 _public function_ `CExprBinaryAwaitOp(int32_t NumReservedDomainExprs, int32_t NumReservedRangeExprs)`
- L2664 _public function_ `virtual bool MayHaveAttributes() const override`
- L2666 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L2668 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2680 _public function_ `const TSRefArray<CExpressionBase>& GetDomainExprs() const`
- L2685 _public function_ `const TSRefArray<CExpressionBase>& GetRangeExprs() const`
- L2690 _public function_ `void AppendDomainExpr(TSRef<CExpressionBase> Expr)`
- L2695 _public function_ `void AppendRangeExpr(TSRef<CExpressionBase> Expr)`
- L2700 _public member_ `CCaptureControlScope* _DomainScope{nullptr};`
- L2703 _private member_ `TSRefArray<CExpressionBase> _DomainExprs;`
- L2704 _private member_ `TSRefArray<CExpressionBase> _RangeExprs;`

#### class `uLang::CExprUpon`  
`class AUTORTFM_DISABLE CExprUpon : public CExprBinaryAwaitOp`  
_L2707-2715_
- inherits: `CExprBinaryAwaitOp`
- L2712 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2714 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprWhen`  
`class AUTORTFM_DISABLE CExprWhen : public CExprBinaryAwaitOp`  
_L2717-2725_
- inherits: `CExprBinaryAwaitOp`
- L2722 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2724 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprLoop`  
`class AUTORTFM_DISABLE CExprLoop : public CExprSubBlockBase`  
_L2733-2743_
- inherits: `CExprSubBlockBase`
- desc: Loop flow/concurrency primitive/macro - loop {Expr1; Expr2} Loops one or more expressions. For safety/security it *must* have at least one async expression, `break`, or `return` so it is less likely to have an infinite loop within a single update.
- L2736 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2737 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2738 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2740 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`

#### class `uLang::CExprDefer`  
`class AUTORTFM_DISABLE CExprDefer : public CExprSubBlockBase`  
_L2750-2756_
- inherits: `CExprSubBlockBase`
- desc: defer macro - defer {Expr1; Expr2} Defers expressions until end of current scope. Only called if encountered in flow and called in reverse order encountered.
- L2753 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L2754 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2755 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprBreak`  
`class AUTORTFM_DISABLE CExprBreak : public CExpressionBase`  
_L2766-2776_
- inherits: `CExpressionBase`
- desc: Control flow early exit loop: if (IsEarlyExit[]): break DoLoopStuff()
- L2769 _public member_ `const CExpressionBase* _AssociatedControlFlow{nullptr};`
- L2771 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2772 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2773 _public function_ `virtual bool MayHaveAttributes() const override`
- L2775 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`

#### class `uLang::CMemberDefinitions`  
`class AUTORTFM_DISABLE CMemberDefinitions`  
_L2781-2797_
- desc: Represents members of a class/interface/module/snippet definition node
- L2784 _public function_ `CMemberDefinitions()`
- L2785 _public function_ `CMemberDefinitions(TArray<TSRef<CExpressionBase>>&& Members) : _Members(Move(Members))`
- L2787 _public function_ `const TArray<TSRef<CExpressionBase>>& Members() const`
- L2788 _public function_ `void SetMembers(TArray<TSRef<CExpressionBase>>&& Members)`
- L2789 _public function_ `void AppendMember(TSRef<CExpressionBase>&& Member)`
- L2790 _public function_ `void PrependMember(TSRef<CExpressionBase>&& Member)`
- L2791 _public function_ `void SetMember(TSRef<CExpressionBase>&& Member, int32_t Index)`
- L2793 _public function_ `void VisitMembers(SAstVisitor& Visitor) const`
- L2796 _private member_ `TArray<TSRef<CExpressionBase>> _Members;`

#### class `uLang::CExprSnippet`  
`class AUTORTFM_DISABLE CExprSnippet : public CExpressionBase, public CMemberDefinitions`  
_L2802-2815_
- inherits: `CExpressionBase,CMemberDefinitions`
- desc: Represents a snippet in the AST.
- L2805 _public member_ `CUTF8String _Path;`
- L2806 _public member_ `CSnippet* _SemanticSnippet{ nullptr };`
- L2808 _public function_ `CExprSnippet(const CUTF8StringView& Path) : _Path(Path)`
- L2810 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2811 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2812 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L2813 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2814 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprModuleDefinition`  
`class AUTORTFM_DISABLE CExprModuleDefinition : public CExpressionBase, public CMemberDefinitions`  
_L2820-2840_
- inherits: `CExpressionBase,CMemberDefinitions`
- desc: Represents a module definition in the AST.
- L2823 _public member_ `CUTF8String _Name;`
- L2824 _public member_ `CModulePart* _SemanticModule{ nullptr };` — You can get the CModule from this as well
- L2825 _public member_ `bool _bLegacyPublic = false;` — To emulate legacy behavior while vmodule files are allowed
- L2827 _public function_ `CExprModuleDefinition(const CUTF8StringView& Name, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExpressionBase(VstMappingType) , _Name(Name)`
- L2831 _public prototype_ `CExprModuleDefinition(CModulePart& Module, TArray<TSRef<CExpressionBase>>&& Members);`
- L2832 _public prototype_ `~CExprModuleDefinition();`
- L2834 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2835 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2836 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L2837 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2838 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L2839 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`

#### class `uLang::CExprEnumDefinition`  
`class AUTORTFM_DISABLE CExprEnumDefinition : public CExpressionBase`  
_L2845-2861_
- inherits: `CExpressionBase`
- desc: Represents an enum definition in the AST.
- L2848 _public member_ `CEnumeration& _Enum;`
- L2850 _public member_ `const TArray<TSRef<CExpressionBase>> _Members;`
- L2852 _public prototype_ `CExprEnumDefinition(CEnumeration& Enum, TArray<TSRef<CExpressionBase>>&& Members, EVstMappingType = EVstMappingType::Ast);`
- L2853 _public prototype_ `~CExprEnumDefinition();`
- L2855 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2856 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2857 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L2858 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2859 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`
- L2860 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`

#### class `uLang::CExprScopedAccessLevelDefinition`  
`class AUTORTFM_DISABLE CExprScopedAccessLevelDefinition : public CExpressionBase`  
_L2868-2881_
- inherits: `CExpressionBase`
- desc: Represents both named and anonymous scoped access level definitions in the AST. e.g. foo_scope := scoped{A,B,C}  #named foo<scoped{A,B,C}> := 42 # anonymous
- L2871 _public member_ `TSRef<CScopedAccessLevelDefinition> _AccessLevelDefinition;`
- L2872 _public member_ `TArray<TSRef<CExpressionBase>> _ScopeReferenceExprs;`
- L2874 _public prototype_ `CExprScopedAccessLevelDefinition(TSRef<CScopedAccessLevelDefinition>& AccessLevelDefinition, EVstMappingType VstMappingType = EVstMappingType::Ast);`
- L2875 _public prototype_ `~CExprScopedAccessLevelDefinition();`
- L2877 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2878 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2879 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2880 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprInterfaceDefinition`  
`class AUTORTFM_DISABLE CExprInterfaceDefinition : public CExpressionBase, public CMemberDefinitions`  
_L2886-2912_
- inherits: `CExpressionBase,CMemberDefinitions`
- desc: Represents a interface definition in the AST.
- L2889 _public member_ `CInterface& _Interface;`
- L2891 _public function_ `const TArray<TSRef<CExpressionBase>>& SuperInterfaces() const`
- L2892 _public function_ `void SetSuperInterfaces(TArray<TSRef<CExpressionBase>>&& SuperInterfaces)`
- L2893 _public function_ `void SetSuperInterface(TSRef<CExpressionBase>&& SuperInterface, int32_t Index)`
- L2895 _public prototype_ `CExprInterfaceDefinition(CInterface& Interface, TArray<TSRef<CExpressionBase>>&& SuperInterfaces, TArray<TSRef<CExpressionBase>>&& Members, EVstMappingType = EVstMappingType::Ast);`
- L2897 _public function_ `CExprInterfaceDefinition(CInterface& Interface, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprInterfaceDefinition(Interface, {}, {}, VstMappingType)`
- L2901 _public prototype_ `~CExprInterfaceDefinition();`
- L2903 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2904 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2905 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2906 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`
- L2907 _public function_ `virtual bool MayHaveAttributes() const override`
- L2908 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`
- L2911 _private member_ `TArray<TSRef<CExpressionBase>> _SuperInterfaces;`

#### class `uLang::CExprClassDefinition`  
`class AUTORTFM_DISABLE CExprClassDefinition : public CExpressionBase, public CMemberDefinitions`  
_L2917-2942_
- inherits: `CExpressionBase,CMemberDefinitions`
- desc: Represents a class definition in the AST.
- L2920 _public member_ `CClass& _Class;`
- L2922 _public prototype_ `CExprClassDefinition(CClass& Class, TArray<TSRef<CExpressionBase>>&& SuperTypes, TArray<TSRef<CExpressionBase>>&& Members, EVstMappingType = EVstMappingType::Ast);`
- L2924 _public function_ `CExprClassDefinition(CClass& Class, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprClassDefinition(Class, {}, {}, VstMappingType)`
- L2929 _public prototype_ `~CExprClassDefinition();`
- L2931 _public function_ `const TArray<TSRef<CExpressionBase>>& SuperTypes() const`
- L2932 _public function_ `void SetSuperTypes(TArray<TSRef<CExpressionBase>>&& SuperTypes)`
- L2933 _public function_ `void SetSuperType(TSRef<CExpressionBase>&& SuperType, int32_t Index)`
- L2935 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2936 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2937 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L2938 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`
- L2939 _public function_ `virtual bool CanBePathSegment(const TMacroSymbols& MacroSymbols) const override`
- L2941 _private member_ `TArray<TSRef<CExpressionBase>> _SuperTypes;`

#### class `uLang::CExprDataDefinition`  
`class AUTORTFM_DISABLE CExprDataDefinition : public CExprDefinition`  
_L2947-2959_
- inherits: `CExprDefinition`
- desc: Represents a data definition in the AST.
- L2950 _public member_ `const TSRef<CDataDefinition> _DataMember;`
- L2952 _public prototype_ `CExprDataDefinition(const TSRef<CDataDefinition>& DataMember, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value, EVstMappingType = EVstMappingType::Ast);`
- L2953 _public prototype_ `~CExprDataDefinition();`
- L2955 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2956 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2957 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L2958 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CExprIterationPairDefinition`  
`class AUTORTFM_DISABLE CExprIterationPairDefinition : public CExprDefinition`  
_L2964-2982_
- inherits: `CExprDefinition`
- desc: Represents a map pair definition in the AST: (Key=>Value):Map
- L2967 _public member_ `const TSRef<CDataDefinition> _KeyDefinition;`
- L2968 _public member_ `const TSRef<CDataDefinition> _ValueDefinition;`
- L2970 _public prototype_ `CExprIterationPairDefinition( TSRef<CDataDefinition>&& KeyDefinition, TSRef<CDataDefinition>&& ValueDefinition, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value, EVstMappingType VstMappingType = EVstMappingType::Ast);`
- L2977 _public prototype_ `~CExprIterationPairDefinition();`
- L2979 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2980 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L2981 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`

#### class `uLang::CIrArrayAdd`  
`class AUTORTFM_DISABLE CIrArrayAdd : public CExpressionBase`  
_L2990-3006_
- inherits: `CExpressionBase`
- desc: Add an item to an array The array itself is not included in the node, instead the result destination in the code generator is used. In the future this will be explicit in the IR, but for now it's inside code generation.
- L2993 _public function_ `CIrArrayAdd(TSRef<CExpressionBase>&& Source) : CExpressionBase(EVstMappingType::Ir) , _Source(Move(Source))`
- L2998 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L2999 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3001 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L3002 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3003 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3005 _public member_ `TSRef<CExpressionBase> _Source;`

#### class `uLang::CIrMapAdd`  
`class AUTORTFM_DISABLE CIrMapAdd : public CExpressionBase`  
_L3009-3027_
- inherits: `CExpressionBase`
- desc: @see CIrArrayAdd
- L3012 _public function_ `CIrMapAdd(TSRef<CExpressionBase>&& Key, TSRef<CExpressionBase>&& Value) : CExpressionBase(EVstMappingType::Ir) , _Key(Move(Key)) , _Value(Move(Value))`
- L3019 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3020 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3021 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram&) const override;`
- L3022 _public prototype_ `virtual bool CanFail(const CAstPackage* Package) const override;`
- L3023 _public prototype_ `virtual void VisitChildren(SAstVisitor& Visitor) const override;`
- L3025 _public member_ `TSRef<CExpressionBase> _Key;`
- L3026 _public member_ `TSRef<CExpressionBase> _Value;`

#### class `uLang::CIrArrayUnsafeCall`  
`class AUTORTFM_DISABLE CIrArrayUnsafeCall : public CExpressionBase`  
_L3029-3062_
- inherits: `CExpressionBase`
- L3032 _public function_ `CIrArrayUnsafeCall(TSRef<CExpressionBase>&& Callee, TSRef<CExpressionBase>&& Arguments) : _Callee(Move(Callee)) , _Argument(Move(Arguments))`
- L3038 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3040 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3042 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L3047 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3054 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3060 _public member_ `TSRef<CExpressionBase> _Callee;`
- L3061 _public member_ `TSRef<CExpressionBase> _Argument;`

#### class `uLang::CIrConvertToDynamic`  
`class AUTORTFM_DISABLE CIrConvertToDynamic : public CExprUnaryOp`  
_L3067-3077_
- inherits: `CExprUnaryOp`
- desc: Converts a value to a dynamically typed value. Only present in the IR, not the AST.
- L3070 _public prototype_ `CIrConvertToDynamic(const CTypeBase* ResultType, TSRef<CExpressionBase>&& Value);`
- L3073 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3074 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3075 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CIrDataOfDynamic`  
`class AUTORTFM_DISABLE CIrDataOfDynamic : public CExprUnaryOp`  
_L3082-3095_
- inherits: `CExprUnaryOp`
- desc: Access data pointer of dynamically typed value. Only present in the IR, not the AST.
- L3085 _public function_ `CIrDataOfDynamic(TSRef<CExpressionBase> Operand) : CExprUnaryOp(Move(Operand), EVstMappingType::Ir)`
- L3091 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3092 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3093 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CIrConvertFromDynamic`  
`class AUTORTFM_DISABLE CIrConvertFromDynamic : public CExprUnaryOp`  
_L3100-3110_
- inherits: `CExprUnaryOp`
- desc: Converts a value to a dynamically typed value. Only present in the IR, not the AST.
- L3103 _public prototype_ `CIrConvertFromDynamic(const CTypeBase* ResultType, TSRef<CExpressionBase>&& Value);`
- L3106 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3107 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3108 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CIrAllOne`  
`class AUTORTFM_DISABLE CIrAllOne : public CExpressionBase`  
_L3115-3142_
- inherits: `CExpressionBase`
- desc: Used to represent either an all or a one.
- L3118 _public function_ `CIrAllOne(TSRef<CExprCodeBlock>&& Iteration, bool bInAll = true) : CExpressionBase(EVstMappingType::Ir) , _bAll(bInAll) , _Iteration(Move(Iteration))`
- L3124 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L3125 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3126 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3129 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3135 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3136 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3138 _public member_ `bool _bAll;`
- L3139 _public member_ `bool _bCanFail{ false };`
- L3140 _public member_ `bool _bGenerateResult{ true };`
- L3141 _public member_ `TSRef<CExprCodeBlock> _Iteration;`

#### class `uLang::CIrFor`  
`class AUTORTFM_DISABLE CIrFor : public CExpressionBase`  
_L3144-3190_
- inherits: `CExpressionBase`
- L3147 _public member_ `bool _bCanFail{ false };`
- L3149 _public member_ `const TSPtr<CDataDefinition> _KeyMember;`
- L3150 _public member_ `const TSRef<CDataDefinition> _DataMember;`
- L3151 _public member_ `const TSRef<CExprDefinition> _Definition;`
- L3153 _public function_ `CIrFor(const TSRef<CDataDefinition>& DataMember, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value) : CExpressionBase(EVstMappingType::Ir) , _KeyMember() , _DataMember(DataMember) , _Definition(TSRef<CExprDefinition>::New(Move(Element), Move(ValueDomain), Move(Value), EVstMappingType::Ir))`
- L3159 _public function_ `CIrFor(const TSRef<CDataDefinition>& KeyMember, const TSRef<CDataDefinition>& DataMember, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value) : CExpressionBase(EVstMappingType::Ir) , _KeyMember(KeyMember) , _DataMember(DataMember) , _Definition(TSRef<CExprDefinition>::New(Move(Element), Move(ValueDomain), Move(Value), EVstMappingType::Ir))`
- L3166 _public function_ `void SetBody(TSPtr<CExpressionBase>&& Body)`
- L3168 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L3169 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3170 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3171 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3181 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3182 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3186 _public member_ `TSPtr<CControlScope> _AssociatedScope;` — The scope containing the variables used for iterating
- L3189 _public member_ `TSPtr<CExpressionBase> _Body;` — Expression to evaluate for every iteration that gets past the filters step

#### class `uLang::CIrIteratedBody`  
`class AUTORTFM_DISABLE CIrIteratedBody : public CExpressionBase`  
_L3196-3219_
- inherits: `CExpressionBase`
- desc: Wraps the innermost body of CIrFor It wraps the code not inside the failure context of CIrFor.
- L3199 _public function_ `CIrIteratedBody(TSPtr<CExpressionBase>&& Body, bool bIsFor = true) : CExpressionBase(EVstMappingType::Ir) , _bIsFor(bIsFor) , _Body(Body)`
- L3205 _public function_ `void SetBody(TSPtr<CExpressionBase>&& Body)`
- L3207 _public prototype_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override;`
- L3208 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3209 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3210 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3212 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3213 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3217 _public member_ `bool _bIsFor;` — Expression to evaluate outside the failure contexts of the enclosing CIrFor
- L3218 _public member_ `TSPtr<CExpressionBase> _Body;`

#### class `uLang::CExprFunctionDefinition`  
`class AUTORTFM_DISABLE CExprFunctionDefinition : public CExprDefinition`  
_L3224-3237_
- inherits: `CExprDefinition`
- desc: Represents a function definition in the AST.
- L3227 _public member_ `const TSRef<CFunction> _Function;`
- L3229 _public prototype_ `CExprFunctionDefinition(const TSRef<CFunction>& Function, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value, EVstMappingType = EVstMappingType::Ast);`
- L3230 _public prototype_ `~CExprFunctionDefinition();`
- L3232 _public prototype_ `bool HasUserAddedPredictsEffect(const CSemanticProgram& Program) const;`
- L3234 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3235 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3236 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`

#### class `uLang::CExprTypeAliasDefinition`  
`class AUTORTFM_DISABLE CExprTypeAliasDefinition : public CExprDefinition`  
_L3242-3252_
- inherits: `CExprDefinition`
- desc: Represents a type alias definition in the AST.
- L3245 _public member_ `const TSRef<CTypeAlias> _TypeAlias;`
- L3247 _public prototype_ `CExprTypeAliasDefinition(const TSRef<CTypeAlias>& TypeAlias, TSPtr<CExpressionBase>&& Element, TSPtr<CExpressionBase>&& ValueDomain, TSPtr<CExpressionBase>&& Value, EVstMappingType = EVstMappingType::Ast);`
- L3248 _public prototype_ `~CExprTypeAliasDefinition();`
- L3250 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3251 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprUsing`  
`class AUTORTFM_DISABLE CExprUsing : public CExpressionBase`  
_L3257-3272_
- inherits: `CExpressionBase`
- desc: Represents a using declaration in the AST.
- L3261 _public member_ `const CModule* _Module = nullptr;` — Note that not all `using` refer to a module
- L3263 _public member_ `TSRef<CExpressionBase> _Context;`
- L3265 _public function_ `CExprUsing(TSRef<CExpressionBase>&& Context) : _Context(Move(Context))`
- L3267 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3268 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3269 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L3270 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3271 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprProfileBlock`  
`class AUTORTFM_DISABLE CExprProfileBlock : public CExprSubBlockBase`  
_L3277-3304_
- inherits: `CExprSubBlockBase`
- desc: Represents a profile block macro invocation in the AST.
- L3280 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3281 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3282 _public function_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override`
- L3283 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L3285 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3291 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3297 _public member_ `TSPtr<uLang::CExpressionBase> _UserTag;` — Must resolve to a string type
- L3300 _public member_ `const uLang::CTupleType* _ProfileLocusType;`
- L3301 _public member_ `const uLang::CTupleType* _ProfileDataType;`

#### class `uLang::CExprImport`  
`class AUTORTFM_DISABLE CExprImport : public CExpressionBase`  
_L3309-3323_
- inherits: `CExpressionBase`
- desc: Represents a import declaration in the AST.
- L3312 _public member_ `const TSRef<CModuleAlias> _ModuleAlias;`
- L3313 _public member_ `const TSRef<CExpressionBase> _Path;`
- L3315 _public prototype_ `CExprImport(const TSRef<CModuleAlias>& ModuleAlias, TSRef<CExpressionBase>&& Path, EVstMappingType VstMappingType = EVstMappingType::Ast);`
- L3316 _public prototype_ `~CExprImport();`
- L3318 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3319 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3320 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L3321 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3322 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`

#### class `uLang::CExprWhere`  
`class AUTORTFM_DISABLE CExprWhere : public CExpressionBase`  
_L3325-3372_
- inherits: `CExpressionBase`
- L3328 _public function_ `CExprWhere(TSRef<CExpressionBase>&& Lhs, TSPtrArray<CExpressionBase>&& Rhs) : _Lhs(Move(Lhs)) , _Rhs(Move(Rhs))`
- L3334 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3336 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3338 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3344 _public function_ `const TSPtr<CExpressionBase>& Lhs() const`
- L3349 _public function_ `const TSPtrArray<CExpressionBase>& Rhs() const`
- L3354 _public function_ `TSPtrArray<CExpressionBase>& Rhs()`
- L3359 _public function_ `void SetLhs(TSPtr<CExpressionBase> NewLhs)`
- L3364 _public function_ `void SetRhs(TSPtrArray<CExpressionBase> NewRhs)`
- L3370 _private member_ `TSPtr<CExpressionBase> _Lhs;`
- L3371 _private member_ `TSPtrArray<CExpressionBase> _Rhs;`

#### class `uLang::CExprVar`  
`class AUTORTFM_DISABLE CExprVar : public CExprUnaryOp`  
_L3374-3388_
- inherits: `CExprUnaryOp`
- L3377 _public function_ `CExprVar(bool bIsLive, TSPtr<CExpressionBase> Operand, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprUnaryOp`
- L3383 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3384 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3385 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3387 _public member_ `bool _bIsLive;`

#### class `uLang::CExprLive`  
`class AUTORTFM_DISABLE CExprLive : public CExprUnaryOp`  
_L3391-3402_
- inherits: `CExprUnaryOp`
- L3394 _public function_ `explicit CExprLive(TSPtr<CExpressionBase> Operand, EVstMappingType VstMappingType = EVstMappingType::Ast) : CExprUnaryOp`
- L3399 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3400 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3401 _public function_ `virtual CUTF8String GetErrorDesc() const override`

#### class `uLang::CExprMakeNamed`  
`class AUTORTFM_DISABLE CExprMakeNamed : public CExpressionBase`  
_L3407-3460_
- inherits: `CExpressionBase`
- desc: Represents a named value / default value placeholder in the AST.
- L3410 _public function_ `explicit CExprMakeNamed(const CSymbol Name) : _Name(Name)`
- L3415 _public function_ `CExprMakeNamed(const CSymbol Name, TSPtr<CExpressionBase>&& NameIdentifier, TSPtr<CExpressionBase>&& Argument) : _Name(Name) , _NameIdentifier(Move(NameIdentifier)) , _Value(Move(Argument))`
- L3422 _public function_ `const CSymbol& GetName() const`
- L3423 _public function_ `const TSPtr<CExpressionBase>& GetNameIdentifier() const`
- L3424 _public function_ `void SetNameIdentifier(TSPtr<CExpressionBase> NameIdentifier)`
- L3425 _public function_ `const TSPtr<CExpressionBase>& GetValue() const`
- L3426 _public function_ `void SetValue(TSPtr<CExpressionBase> Value)`
- L3427 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L3428 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3430 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3436 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3442 _public function_ `virtual const CExpressionBase* FindFirstAsyncSubExpr(const CSemanticProgram& Program) const override`
- L3447 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L3453 _private member_ `CSymbol _Name;`
- L3458 _private member_ `TSPtr<CExpressionBase> _NameIdentifier;` — Optional pointer to the original identifier for the name. This can be used to preserve the AST information about the original source text from where the identifier came from and provide context. (i.e. for qualifying purposes).
- L3459 _private member_ `TSPtr<CExpressionBase> _Value;`

#### class `uLang::CAstPackage`  
`class AUTORTFM_DISABLE CAstPackage : public CAstNode, public CMemberDefinitions`  
_L3465-3532_
- inherits: `CAstNode,CMemberDefinitions`
- desc: Represents a package in the AST.
- L3468 _public member_ `CUTF8String _Name;`
- L3470 _public member_ `CUTF8String _VersePath;` — Verse path of the root module of this package
- L3471 _public member_ `CModulePart* _RootModule = nullptr;` — Root module representing this package's Verse path
- L3473 _public member_ `TArray<const CAstPackage*> _Dependencies;` — As specified in package settings
- L3474 _public member_ `TArray<const CAstPackage*> _UsedDependencies;` — Dependencies actually used
- L3476 _public member_ `EVerseScope _VerseScope;` — Origin/visibility of Verse code in this package
- L3477 _public member_ `EPackageRole _Role;` — The role this package plays
- L3478 _public member_ `uint32_t _EffectiveVerseVersion;` — The effective language version the package targets.
- L3486 _public member_ `uint32_t _UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest;` — This allows us to determine when a package was uploaded for a given Fortnite release version. It is a HACK that conditionally enables/disables behaviour in the compiler in order to support previous mistakes allowed to slip through in previous Verse langauge releases  but now need to be supported for backwards compatability. When we can confirm that all Fortnite packages that are currently uploaded are beyond this version being used in all instances of the codebase, this can then be removed.
- L3489 _public member_ `int32_t _NumPersistentVars = 0;` — Track the number of persistent values found per-package.
- L3492 _public member_ `int32_t _NumConcreteEntitlementSubclasses = 0;` — Track the number of concrete entitlement subclasses found per-package.
- L3494 _public member_ `bool _bAllowNative;` — If the native attribute is allowed
- L3495 _public member_ `bool _bTreatModulesAsImplicit;` — If true, module macros in this package's source and digest will be treated as implicit
- L3497 _public member_ `bool _bAllowExperimental;` — Whether to allow the use of experimental definitions in this package.
- L3499 _public member_ `CAstCompilationUnit* _CompilationUnit = nullptr;` — Reverse pointer to our owner
- L3501 _public function_ `CAstPackage(const CUTF8String& Name, const CUTF8String& VersePath, const EVerseScope VerseScope, const EPackageRole Role, const uint32_t EffectiveVerseVersion, const uint32_t UploadedAtFNVersion, const bool bAllowNative, const bool bTreatDefinitionsAsImplicit, const bool bAllowExperimental) : _Name(Name) , _VersePath(VersePath) , _VerseScope(VerseScope) , _Role(Role) , _EffectiveVerseVersion(EffectiveVerseVersion) , _UploadedAtFNVersion(UploadedAtFNVersion) , _bAllowNative(bAllowNative) , _bTreatModulesAsImplicit(bTreatDefinitionsAsImplicit) , _bAllowExperimental(bAllowExperimental)`
- L3522 _public function_ `virtual EAstNodeType GetNodeType() const override` — CAstNode interface.
- L3523 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3524 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3525 _public prototype_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override;`
- L3528 _public prototype_ `bool CanSeePackage(const CAstPackage& DependencyPackage) const;` — Determine if code in this package can see definitions in a different package.
- L3531 _public prototype_ `bool CanSeeDefinition(const CDefinition& Definition) const;` — Determine if the definition originates from this package or any of our dependencies

#### class `uLang::CAstCompilationUnit`  
`class AUTORTFM_DISABLE CAstCompilationUnit : public CAstNode`  
_L3537-3556_
- inherits: `CAstNode`
- desc: A group of packages that must be compiled as a unit (= a strongly connected component (SCC) in the dependency graph)
- L3541 _public function_ `const TSRefArray<CAstPackage>& Packages() const`
- L3542 _public function_ `void ReservePackages(int32_t Num)`
- L3543 _public function_ `void AppendPackage(TSRef<CAstPackage>&& Package)`
- L3545 _public prototype_ `EPackageRole GetRole() const;`
- L3546 _public prototype_ `bool IsAllowNative() const;`
- L3549 _public function_ `virtual EAstNodeType GetNodeType() const override` — CAstNode interface.
- L3550 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3551 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3555 _private member_ `TSRefArray<CAstPackage> _Packages;`

#### class `uLang::CAstProject`  
`class AUTORTFM_DISABLE CAstProject : public CAstNode`  
_L3561-3585_
- inherits: `CAstNode`
- desc: Represents a project in the AST.
- L3565 _public member_ `CUTF8String _Name;`
- L3567 _public function_ `CAstProject(const CUTF8StringView& Name) : _Name(Name)`
- L3569 _public function_ `const TSRefArray<CAstCompilationUnit>& OrderedCompilationUnits() const` — Guaranteed to be sorted in order of dependency
- L3570 _public function_ `void ReserveCompilationUnits(int32_t Num)`
- L3571 _public function_ `void AppendCompilationUnit(TSRef<CAstCompilationUnit>&& CompilationUnit)`
- L3573 _public prototype_ `const CAstPackage* FindPackageByName(const CUTF8String& PackageName) const;`
- L3574 _public prototype_ `int32_t GetNumPackages() const;`
- L3577 _public function_ `virtual EAstNodeType GetNodeType() const override` — CAstNode interface.
- L3578 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L3579 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L3580 _public function_ `virtual void VisitImmediates(SAstVisitor& Visitor) const override`
- L3584 _private member_ `TSRefArray<CAstCompilationUnit> _OrderedCompilationUnits;` — Guaranteed to be sorted in order of dependency

#### struct `uLang::TAstFunctionVisitor`  
`template<typename FunctionType> struct AUTORTFM_DISABLE TAstFunctionVisitor : public SAstVisitor`  
_L3592-3598_
- inherits: `SAstVisitor`
- L3594 _public member_ `FunctionType _Function;`
- L3595 _public function_ `TAstFunctionVisitor(FunctionType&& Function) : _Function(ForwardArg<FunctionType>(Function))`
- L3596 _public function_ `virtual void Visit(const char* FieldName, CAstNode& AstNode) override`
- L3597 _public function_ `virtual void VisitElement(CAstNode& AstNode) override`

#### struct `uLang::TAsNullableTraitsOf`  
`template <typename TOut> struct TAsNullableTraitsOf<TSPtr<CExpressionBase>, TOut>`  
_L3612-3616_
- L3614 _public typedef_ `using TResult = TSPtr<TOut>;`
- L3615 _public function_ `static TResult Cast(TSPtr<CExpressionBase> X)`
- L3622 _public function_ `static TResult Cast(TSRef<CExpressionBase> X)`
- L3628 _public typedef_ `using TResult = TOut*;`
- L3629 _public function_ `static TResult Cast(CExpressionBase* X)`
- L3635 _public typedef_ `using TResult = const TOut*;`
- L3636 _public function_ `static TResult Cast(const CExpressionBase* X)`

#### struct `uLang::TAsNullableTraitsOf`  
`template <typename TOut> struct TAsNullableTraitsOf<TSRef<CExpressionBase>, TOut>`  
_L3619-3623_
- L3614 _public typedef_ `using TResult = TSPtr<TOut>;`
- L3615 _public function_ `static TResult Cast(TSPtr<CExpressionBase> X)`
- L3622 _public function_ `static TResult Cast(TSRef<CExpressionBase> X)`
- L3628 _public typedef_ `using TResult = TOut*;`
- L3629 _public function_ `static TResult Cast(CExpressionBase* X)`
- L3635 _public typedef_ `using TResult = const TOut*;`
- L3636 _public function_ `static TResult Cast(const CExpressionBase* X)`

#### struct `uLang::TAsNullableTraitsOf`  
`template <typename TOut> struct TAsNullableTraitsOf<CExpressionBase*, TOut>`  
_L3626-3630_
- L3614 _public typedef_ `using TResult = TSPtr<TOut>;`
- L3615 _public function_ `static TResult Cast(TSPtr<CExpressionBase> X)`
- L3622 _public function_ `static TResult Cast(TSRef<CExpressionBase> X)`
- L3628 _public typedef_ `using TResult = TOut*;`
- L3629 _public function_ `static TResult Cast(CExpressionBase* X)`
- L3635 _public typedef_ `using TResult = const TOut*;`
- L3636 _public function_ `static TResult Cast(const CExpressionBase* X)`

#### struct `uLang::TAsNullableTraitsOf`  
`template <typename TOut> struct TAsNullableTraitsOf<const CExpressionBase*, TOut>`  
_L3633-3637_
- L3614 _public typedef_ `using TResult = TSPtr<TOut>;`
- L3615 _public function_ `static TResult Cast(TSPtr<CExpressionBase> X)`
- L3622 _public function_ `static TResult Cast(TSRef<CExpressionBase> X)`
- L3628 _public typedef_ `using TResult = TOut*;`
- L3629 _public function_ `static TResult Cast(CExpressionBase* X)`
- L3635 _public typedef_ `using TResult = const TOut*;`
- L3636 _public function_ `static TResult Cast(const CExpressionBase* X)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API VERSECOMPILER_API`
- L20 _namespace_ `namespace uLang`
- L45 _macro_ `#define VERSE_VISIT_AST_NODE_TYPES(v) \` — NOTE: (YiLiangSiew) Currently, Visual Verse relies on the numerical values of these enumerations. If you change this, be sure to update `BaseVisualVerseSettings.ini` as well.
- L179 _macro_ `#define FORWARD_DECLARE(_, Class) class Class;`
- L190 _macro_ `#define VISIT_AST_NODE_TYPE(Name, Class) Name,`
- L202 _prototype_ `SAstNodeTypeInfo GetAstNodeTypeInfo(uLang::EAstNodeType Type);` (scope `uLang`) — Returns the name of an AST node type.
- L214 _function_ `inline const char* InvokeTimeAsCString(EInvokeTime InvokeTime)` (scope `uLang`)
- L614 _member_ `Integer _IntValue;` (scope `uLang::CExprNumber::__anonae6095c8010a`)
- L615 _member_ `Float _FloatValue;` (scope `uLang::CExprNumber::__anonae6095c8010a`)
- L1281 _function_ `constexpr EMacroClauseTag operator| (EMacroClauseTag A, EMacroClauseTag B)` (scope `uLang`)
- L1282 _function_ `constexpr bool HasAnyTags(EMacroClauseTag A, EMacroClauseTag B)` (scope `uLang`)
- L1283 _function_ `constexpr bool HasAllTags(EMacroClauseTag A, EMacroClauseTag RequiredTags)` (scope `uLang`)
- L1287 _function_ `inline const char* MacroClauseTagAsCString(EMacroClauseTag Tag)` (scope `uLang`)
- L1297 _function_ `inline const char* MacroClauseFormAsCString(Verse::Vst::Clause::EForm Form)` (scope `uLang`)
- L1516 _prototype_ `const CExprIdentifierFunction* GetConstructorInvocationCallee(const CExprInvocation&);` (scope `uLang`)
- L1518 _prototype_ `const CExprIdentifierFunction* GetConstructorInvocationCallee(const CExpressionBase&);` (scope `uLang`)
- L1520 _prototype_ `bool IsConstructorInvocation(const CExprInvocation&);` (scope `uLang`)
- L1522 _prototype_ `bool IsConstructorInvocation(const CExpressionBase&);` (scope `uLang`)
- L1608 _prototype_ `TOptional<SAssignmentLhsIdentifier> IdentifierOfAssignmentLhs(const CExprAssignment* Assignment );` (scope `uLang`)
- L1609 _prototype_ `bool HasImplicitClassSelf(const CExprIdentifierData* Expr );` (scope `uLang`)
- L1610 _prototype_ `bool IsClassMemberAccess(const CExprIdentifierData* Expr );` (scope `uLang`)
- L3643 _function_ `typename Traits::TResult AsNullable(TIn Expr)` (scope `uLang`)
- L3645 _macro_ `#define VISIT_AST_NODE_TYPE(Name, Class) \`
- L3658 _function_ `inline const char* AsStringLiteral(EAstNodeType Node)` (scope `uLang`)
- L3660 _macro_ `#define VISIT_AST_NODE_TYPE(Name, Class) if (Node == EAstNodeType::Name) { return #Name; }`
- L3668 _prototype_ `const CExprInvocation* AsSubscriptCall( const CExpressionBase* Expr , const CSemanticProgram& Program);` (scope `uLang`) — if Expr is a CallOp like X[A][B]...[Z] then return Expr as a CExprInvocation, otherwise return nullptr
- L3673 _prototype_ `const CExpressionBase* RemoveSubscripts( const CExpressionBase* Expr , const CSemanticProgram& Program);` (scope `uLang`) — if Expr is X[A][B]...[Z] then return X, otherwise return Expr

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/FilteredDefinitionRange.h` (Public)


#### class `uLang::TFilteredDefinitionRange`  
`template<typename FilterClass> class TFilteredDefinitionRange`  
_L15-86_
- desc: Filters a range of definitions to only include definitions of the kind corresponding to FilterClass.
- L30 _public function_ `friend bool operator==(const Iterator& Lhs, const Iterator& Rhs)`
- L36 _public function_ `friend bool operator!=(const Iterator& Lhs, const Iterator& Rhs)`
- L77 _public function_ `TFilteredDefinitionRange(const TSRef<CDefinition>* Begin, const TSRef<CDefinition>* End) : _Begin(Begin), _End(End)`
- L80 _public function_ `Iterator begin() const`
- L81 _public function_ `Iterator end() const`
- L84 _private member_ `const TSRef<CDefinition>* _Begin;`
- L85 _private member_ `const TSRef<CDefinition>* _End;`

#### class `uLang::TFilteredDefinitionRange::Iterator`  
`class Iterator`  
_L20-75_
- desc: An iterator in a filtered definition range.
- L23 _public function_ `Iterator(const TSRef<CDefinition>* Current, const TSRef<CDefinition>* End) : _Current(Current) , _End(End)`
- L42 _public function_ `Iterator& operator++()`
- L52 _public function_ `const TSRef<FilterClass>& operator*() const`
- L58 _public function_ `const FilterClass* operator->() const`
- L65 _private member_ `const TSRef<CDefinition>* _Current;`
- L66 _private member_ `const TSRef<CDefinition>* _End;`
- L68 _private function_ `void FindNext()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/IntOrInfinity.h` (Public)


#### enum `uLang::EInfinitySign`  
`enum class EInfinitySign`  
_L12-16_
- desc: Encodes either an integer or positive/negative infinity.
- L14 _public enumerator_ `Negative`
- L15 _public enumerator_ `Positive`

#### struct `uLang::TIntOrInfinity`  
`template <EInfinitySign InfinitySign> struct TIntOrInfinity`  
_L23-75_
- L25 _public function_ `TIntOrInfinity(int64_t InFiniteInt) : MaybeFiniteInt(InFiniteInt)`
- L30 _public function_ `static TIntOrInfinity Infinity()`
- L56 _public function_ `bool IsInfinity() const`
- L57 _public function_ `bool IsFinite() const`
- L58 _public function_ `int64_t GetFiniteInt() const`
- L60 _public function_ `bool IsSafeToNegate() const`
- L70 _private member_ `TOptional<int64_t> MaybeFiniteInt;`
- L72 _private function_ `TIntOrInfinity()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L17 _function_ `constexpr EInfinitySign operator-(EInfinitySign Sign)` (scope `uLang`)
- L32 _function_ `friend bool operator==(int64_t Lhs, const TIntOrInfinity& Rhs)` (scope `uLang`)
- L36 _function_ `friend bool operator<(int64_t Lhs, const TIntOrInfinity& Rhs)` (scope `uLang`)
- L42 _function_ `friend bool operator>(int64_t Lhs, const TIntOrInfinity& Rhs)` (scope `uLang`)
- L48 _function_ `friend bool operator<=(int64_t Lhs, const TIntOrInfinity& Rhs)` (scope `uLang`)
- L49 _function_ `friend bool operator>=(int64_t Lhs, const TIntOrInfinity& Rhs)` (scope `uLang`)
- L51 _function_ `friend bool operator<(const TIntOrInfinity& Lhs, int64_t Rhs)` (scope `uLang`)
- L52 _function_ `friend bool operator>(const TIntOrInfinity& Lhs, int64_t Rhs)` (scope `uLang`)
- L53 _function_ `friend bool operator<=(const TIntOrInfinity& Lhs, int64_t Rhs)` (scope `uLang`)
- L54 _function_ `friend bool operator>=(const TIntOrInfinity& Lhs, int64_t Rhs)` (scope `uLang`)
- L77 _typedef_ `using FIntOrNegativeInfinity = TIntOrInfinity<EInfinitySign::Negative>;` (scope `uLang`)
- L78 _typedef_ `using FIntOrPositiveInfinity = TIntOrInfinity<EInfinitySign::Positive>;` (scope `uLang`)
- L81 _function_ `template<EInfinitySign LhsSign, EInfinitySign RhsSign> inline bool operator==(const TIntOrInfinity<LhsSign>& Lhs, const TIntOrInfinity<RhsSign>& Rhs)` (scope `uLang`)
- L94 _function_ `template<EInfinitySign LhsSign, EInfinitySign RhsSign> inline bool operator<(const TIntOrInfinity<LhsSign>& Lhs, const TIntOrInfinity<RhsSign>& Rhs)` (scope `uLang`)
- L115 _function_ `template<EInfinitySign LhsSign, EInfinitySign RhsSign> inline bool operator<=(const TIntOrInfinity<LhsSign>& Lhs, const TIntOrInfinity<RhsSign>& Rhs)` (scope `uLang`)
- L120 _function_ `template<EInfinitySign LhsSign, EInfinitySign RhsSign> inline bool operator>(const TIntOrInfinity<LhsSign>& Lhs, const TIntOrInfinity<RhsSign>& Rhs)` (scope `uLang`)
- L125 _function_ `template<EInfinitySign LhsSign, EInfinitySign RhsSign> inline bool operator>=(const TIntOrInfinity<LhsSign>& Lhs, const TIntOrInfinity<RhsSign>& Rhs)` (scope `uLang`)
- L131 _function_ `template<EInfinitySign OperandSign> inline TIntOrInfinity<-OperandSign> operator-(const TIntOrInfinity<OperandSign>& Operand)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/MemberOrigin.h` (Public)


#### enum `uLang::EMemberOrigin`  
`enum class EMemberOrigin`  
_L9-14_
- desc: Specifies whether to find only member definitions originating in the current type, or inherited, or either.
- L11 _public enumerator_ `Original`
- L12 _public enumerator_ `InheritedOrOriginal`
- L13 _public enumerator_ `Inherited`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/ModuleAlias.h` (Public)


#### class `uLang::CModuleAlias`  
`class CModuleAlias : public CDefinition`  
_L16-42_
- inherits: `CDefinition`
- desc: An imported module: Alias := import(...)
- L19 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::ModuleAlias;`
- L21 _public function_ `CModuleAlias(const CSymbol& Name, CScope& EnclosingScope) : CDefinition(StaticDefinitionKind, EnclosingScope, Name)`
- L25 _public function_ `const CModule* Module() const`
- L26 _public function_ `void SetModule(const CModule* Module)`
- L29 _public function_ `void SetAstNode(CExprImport* AstNode)` — CDefinition interface.
- L30 _public function_ `CExprImport* GetAstNode() const`
- L32 _public function_ `void SetIrNode(CExprImport* AstNode)`
- L33 _public function_ `CExprImport* GetIrNode(bool bForce = false) const`
- L35 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L37 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L41 _private member_ `const CModule* _Module{ nullptr };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/QualifierUtils.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace uLang`
- L7 _prototype_ `TArray<Verse::Vst::TNodeRef<Verse::Vst::Node>> QualifyAllAnalyzedIdentifiers(bool bVerbose, const TSRef<CSemanticProgram>& Program, Verse::Vst::TNodeRef<Verse::Vst::Node>& Root);` (scope `uLang`)
- L9 _prototype_ `TArray<const CExpressionBase*> FindUnresolvedIdentifiers(const TSRef<CSemanticProgram>& , const CAstNode& RootNode);` (scope `uLang`)
- L12 _prototype_ `bool VerifyAllQualified(const TSRef<CSemanticProgram>& Program);` (scope `uLang`)
- L14 _prototype_ `TArray<const CExpressionBase*> FindResolvedIdentifiersWithoutDefinitions(const TSRef<CSemanticProgram>&, const CAstNode& RootNode);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Revision.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L11 _typedef_ `using SemanticRevision = uint32_t;` (scope `uLang`) — For storing revisions of functions, classes etc.

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/ScopedAccessLevelType.h` (Public)


#### class `uLang::CScopedAccessLevelDefinition`  
`class CScopedAccessLevelDefinition : public CClassDefinition`  
_L23-39_
- inherits: `CClassDefinition`
- desc: HACK! This is convoluted, but attributes need to be CClass types because the semantic attribute processing demands it right now HACK! CClass expects its associated definition to be a CClassDefinition type, so our CScopedAccessLevelDefinition also needs to be a CClassDefinition type HACK! Ordinarily, we could just use CClassDefinition directly without this extra child type, except the CClassDefinition linkage to the AST demands HACK! that the CExpr* type be CExprClassDefinition even though it ultimately relaxes to CExpressionBase.
- L26 _public prototype_ `CScopedAccessLevelDefinition(TOptional<CSymbol> ClassName, CScope& EnclosingScope);`
- L28 _public member_ `TArray<const CScope*> _Scopes;`
- L29 _public member_ `bool _IsAnonymous;`
- L32 _public prototype_ `void SetAstNode(CExprScopedAccessLevelDefinition* AstNode);` — CDefinition interface glue.
- L33 _public prototype_ `CExprScopedAccessLevelDefinition* GetAstNode() const;`
- L35 _public prototype_ `void SetIrNode(CExprScopedAccessLevelDefinition* AstNode);`
- L36 _public prototype_ `CExprScopedAccessLevelDefinition* GetIrNode(bool bForce = false) const;`
- L38 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VERSECOMPILER_API`
- L11 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticClass.h` (Public)


#### class `uLang::CClass`  
`class CClass : public CNominalType, public CLogicalScope`  
_L32-250_
- inherits: `CNominalType,CLogicalScope`
- desc: Class defining a class instance / object [Might break off CStructType to differentiate stack based types.]
- L35 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Class;`
- L36 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Class;`
- L40 _public member_ `CClassDefinition* const _Definition;` — Public data
- L41 _public member_ `const EStructOrClass _StructOrClass;`
- L42 _public member_ `CClass* _Superclass;`
- L44 _public member_ `TArray<CInterface*> _SuperInterfaces;`
- L47 _public member_ `TArray<CInterface*> _AllInheritedInterfaces;` — Flattened array of all interfaces this class inherits (including interfaces from its super-class). Not initially filled out -- cached after we've fully constructed the whole type hierarchy.
- L49 _public member_ `SEffectSet _ConstructorEffects;`
- L54 _public member_ `TArray<CExprCodeBlock*> _IrBlockClauses;` — Kept alive via _Definition's IrNode's (CExprClassDefinition) Members field. We don't hold a shared reference to this because the Ir tree has to be destroyed before the AST.
- L56 _public member_ `CClass* _GeneralizedClass{this};`
- L58 _public member_ `TArray<STypeVariableSubstitution> _TypeVariableSubstitutions;`
- L64 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L70 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L76 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L82 _public function_ `operator Key() const`
- L87 _public member_ `TURefSet<CClass, CClass::Key> _InstantiatedClasses;`
- L89 _public member_ `TUPtr<CClass> _OwnedNegativeClass;`
- L91 _public member_ `CClass* _NegativeClass;`
- L93 _public member_ `bool _bHasCyclesBroken{false};`
- L99 _public prototype_ `CClass( CClassDefinition*, CScope& EnclosingScope, CClass* Superclass = nullptr, TArray<CInterface*>&& SuperInterfaces = {}, EStructOrClass = EStructOrClass::Class, SEffectSet ConstructorEffects = EffectSets::ClassAndInterfaceDefault);` — Construct a generalized positive class
- L108 _public prototype_ `CClass( CScope* ParentScope, CClassDefinition*, EStructOrClass, CClass* Superclass, TArray<CInterface*>&& SuperInterfaces, SEffectSet ConstructorEffects, CClass* GeneralizedClass, TArray<STypeVariableSubstitution>);` — Construct a positive class instantiation
- L119 _public prototype_ `explicit CClass(CClass* PositiveClass);` — Construct a negative class from a positive class
- L123 _public prototype_ `const CTypeType* GetTypeType() const;`
- L125 _public prototype_ `void SetSuperclass(CClass* SuperClass);`
- L128 _public prototype_ `bool IsClass(const CClass& Class) const;` — Determine if current class is the same class or a subclass of the specified `Class`
- L131 _public prototype_ `bool IsSubclassOf(const CClass& Superclass) const;` — Determine if current class is a subclass / descendant / child of the specified `Class` (and not the same class!)
- L134 _public prototype_ `bool IsSuperclassOf(const CClass& Subclass) const;` — Determine if current class is a superclass / ancestor / parent of the specified `Class` (and not the same class!)
- L137 _public prototype_ `bool ImplementsInterface(const CInterface& Interface) const;` — Determine if current class implements `Interface`
- L140 _public function_ `bool IsStruct() const` — Is this class a struct?
- L142 _public function_ `bool IsNative() const`
- L144 _public prototype_ `bool IsNativeRepresentation() const;`
- L146 _public prototype_ `bool IsAbstract() const;`
- L148 _public prototype_ `bool IsPersistent() const;`
- L150 _public prototype_ `bool IsModuleScopedVarWeakMapKey() const;`
- L152 _public prototype_ `bool IsUnique() const;`
- L154 _public prototype_ `bool HasOrInheritsVar(CVisitSet& VisitSet) const;`
- L156 _public function_ `bool HasOrInheritsVar() const`
- L163 _public prototype_ `bool HasConcreteAttribute() const;` — Does this class hold a concrete attribute?
- L166 _public prototype_ `const CClass* FindConcreteBase() const;` — Return first class in the inheritance chain that contains the concrete attribute or null
- L169 _public prototype_ `const CClass* FindInitialConcreteBase() const;` — Return topmost class in the inheritance chain that contains the concrete attribute or null
- L172 _public function_ `bool IsExplicitlyConcrete() const override` — Is this class concrete either by having a concrete attribute or inheriting one
- L175 _public prototype_ `bool HasCastableAttribute() const;` — Does this class hold a castable attribute?
- L178 _public prototype_ `const CNominalType* FindExplicitlyCastableBase() const;` — Return first class in the inheritance chain that contains the castable attribute. Otherwise null
- L181 _public function_ `bool IsExplicitlyCastable() const override` — Is this class castable either by having a castable attribute or inheriting one
- L184 _public prototype_ `bool HasFinalSuperBaseAttribute() const;` — Does this class hold a <final_super_base> attribute?
- L187 _public prototype_ `bool HasFinalSuperAttribute() const;` — Does this class hold a <final_super> attribute?
- L190 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface
- L191 _public function_ `virtual const CTypeBase* ScopeAsType() const override`
- L192 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L193 _public prototype_ `virtual SAccessLevel GetDefaultDefinitionAccessLevel() const override;`
- L194 _public function_ `virtual CScope* GetNegativeScope() const override`
- L197 _public prototype_ `virtual SmallDefinitionArray FindDefinitions( const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;` — CLogicalScope interface.
- L204 _public prototype_ `virtual void ForAllDefinitions( EMemberOrigin Origin, const TFunction<void(const CDefinition&)>& Functor, CVisitSet& VisitSet) const override;`
- L210 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — CTypeBase interface.
- L211 _public prototype_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;`
- L212 _public prototype_ `virtual EComparability GetComparability() const override;`
- L213 _public prototype_ `EComparability GetComparability(CVisitSet&) const;`
- L214 _public prototype_ `bool IsPersistable() const override;`
- L215 _public prototype_ `virtual void SetRevision(SemanticRevision Revision) override;`
- L216 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L217 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L220 _public prototype_ `virtual const CDefinition* Definition() const override;` — CNominalType interface.
- L223 _public function_ `template<typename TFunc> void ForEachAncestorClassOrInterface(const TFunc& Func)`
- L235 _public prototype_ `const CAttributable& GetAttributes() const;`
- L236 _public prototype_ `CAttributable& GetAttributes();`
- L238 _public prototype_ `bool HasCyclesBroken() const;`
- L240 _public function_ `bool IsParametric() const`
- L245 _public prototype_ `bool IsPersonaConstructible() const;`
- L249 _private prototype_ `bool IsClassSlowPath(const CClass& Class) const;` — The slow-path for `IsClass`, used when `HasCyclesBroken` is false.
- L324 _function_ `inline const CDefinition* CClass::Definition() const`
- L330 _function_ `inline void CClass::SetSuperclass(CClass* Superclass)`
- L337 _function_ `inline bool CClass::IsClass(const CClass& Class) const`
- L350 _function_ `inline bool CClass::IsSubclassOf(const CClass& Superclass) const`
- L368 _function_ `inline bool CClass::IsSuperclassOf(const CClass& Subclass) const`
- L386 _function_ `inline void CClass::SetRevision(SemanticRevision Revision)`
- L402 _function_ `inline const CAttributable& CClass::GetAttributes() const`
- L407 _function_ `inline CAttributable& CClass::GetAttributes()`
- L412 _function_ `inline bool CClass::HasCyclesBroken() const`

#### struct `uLang::CClass::Key`  
`struct Key final`  
_L60-80_
- L62 _public member_ `const TArray<STypeVariableSubstitution>& _TypeVariableSubstitutions;`

#### class `uLang::CClassDefinition`  
`class CClassDefinition : public CDefinition, public CClass`  
_L252-296_
- inherits: `CDefinition,CClass`
- L255 _public member_ `CAttributable _EffectAttributable;`
- L256 _public member_ `TOptional<SAccessLevel> _ConstructorAccessLevel;`
- L258 _public function_ `CClassDefinition(const CSymbol& ClassName, CScope& EnclosingScope, CClass* Superclass = nullptr, TArray<CInterface*>&& SuperInterfaces = {}, EStructOrClass StructOrClass = EStructOrClass::Class) : CDefinition(StaticDefinitionKind, EnclosingScope, ClassName) , CClass(this, EnclosingScope, Superclass, Move(SuperInterfaces), StructOrClass)`
- L269 _public function_ `SAccessLevel DerivedConstructorAccessLevel() const`
- L275 _public prototype_ `void SetAstNode(CExprClassDefinition* AstNode);` — CDefinition interface.
- L276 _public prototype_ `CExprClassDefinition* GetAstNode() const;`
- L278 _public prototype_ `void SetIrNode(CExprClassDefinition* AstNode);`
- L279 _public prototype_ `CExprClassDefinition* GetIrNode(bool bForce = false) const;`
- L281 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const override`
- L283 _public prototype_ `TArray<TSRef<CExpressionBase>> FindMembersWithPredictsAttribute(bool bIncludeSupers = false) const;`
- L285 _public function_ `bool IsPersistenceCompatConstraint() const override`
- L287 _public prototype_ `void MarkPersistenceCompatConstraint() const;`
- L289 _public function_ `bool IsEntitlementCompatConstraint() const override`
- L291 _public prototype_ `void MarkEntitlementCompatConstraint() const;`
- L294 _private member_ `mutable bool _bPersistenceCompatConstraint{false};`
- L295 _private member_ `mutable bool _bEntitlementCompatConstraint{false};`

#### class `uLang::CInstantiatedClass`  
`class CInstantiatedClass : public CInstantiatedType`  
_L298-314_
- inherits: `CInstantiatedType`
- L301 _public function_ `CInstantiatedClass(CSemanticProgram& Program, const CClass& Class, ETypePolarity Polarity, TArray<STypeVariableSubstitution> Arguments) : CInstantiatedType(Program, Polarity, Move(Arguments)) , _Class(&Class)`
- L307 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L310 _protected prototype_ `virtual const CNormalType& CreateNormalType() const override;`
- L313 _private member_ `const CClass* _Class;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API VERSECOMPILER_API`
- L22 _namespace_ `namespace uLang`
- L317 _prototype_ `CClass* InstantiateClass(const CClass&, ETypePolarity, const TArray<STypeVariableSubstitution>&);` (scope `uLang`) — Eagerly instantiate a class.

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticEnumeration.h` (Public)


#### class `uLang::CEnumerator`  
`class CEnumerator : public CDefinition`  
_L26-52_
- inherits: `CDefinition`
- desc: Description for a single enumerator
- L30 _public member_ `static constexpr EKind StaticDefinitionKind = EKind::Enumerator;`
- L33 _public member_ `const int32_t _IntValue;` — The integer value denoting this enumerator for native representation.
- L36 _public member_ `CEnumeration* _Enumeration{nullptr};` — Type this enumerator belongs to
- L38 _public prototype_ `CEnumerator(CEnumeration& Enumeration, const CSymbol& Name, int32_t Value);`
- L40 _public prototype_ `CUTF8String AsCode() const;`
- L43 _public prototype_ `void SetAstNode(CExprEnumLiteral* AstNode);` — CDefinition interface.
- L44 _public prototype_ `CExprEnumLiteral* GetAstNode() const;`
- L46 _public prototype_ `void SetIrNode(CExprEnumLiteral* AstNode);`
- L47 _public prototype_ `CExprEnumLiteral* GetIrNode(bool bForce = false) const;`
- L49 _public prototype_ `virtual bool IsPersistenceCompatConstraint() const override;`
- L51 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`

#### class `uLang::CEnumeration`  
`class CEnumeration : public CDefinition, public CLogicalScope, public CNominalType`  
_L59-114_
- inherits: `CDefinition,CLogicalScope,CNominalType`
- desc: Enumeration type @jira SOL-1013 : Make enums derive from Class?
- L62 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Enumeration;`
- L63 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Enumeration;`
- L65 _public member_ `CAttributable _EffectAttributable;`
- L67 _public prototype_ `CEnumeration(const CSymbol& Name, CScope& EnclosingScope);`
- L69 _public prototype_ `CEnumerator& CreateEnumerator(const CSymbol& EnumeratorName, int32_t Value);`
- L73 _public prototype_ `virtual SmallDefinitionArray FindTypeMember(const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, CVisitSet& VisitSet) const override;`
- L74 _public function_ `virtual EComparability GetComparability() const override`
- L75 _public prototype_ `virtual bool IsPersistable() const override;`
- L76 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L77 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L78 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L79 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L82 _public function_ `virtual const CDefinition* Definition() const override` — CNominalType interface.
- L85 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface.
- L86 _public function_ `virtual const CTypeBase* ScopeAsType() const override`
- L87 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L88 _public prototype_ `virtual SAccessLevel GetDefaultDefinitionAccessLevel() const override;`
- L91 _public prototype_ `void SetAstNode(CExprEnumDefinition* AstNode);` — CDefinition interface.
- L92 _public prototype_ `CExprEnumDefinition* GetAstNode() const;`
- L94 _public prototype_ `void SetIrNode(CExprEnumDefinition* AstNode);`
- L95 _public prototype_ `CExprEnumDefinition* GetIrNode(bool bForce = false) const;`
- L97 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const override`
- L99 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L101 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L103 _public function_ `bool IsOpen() const`
- L104 _public function_ `bool IsClosed() const`
- L113 _public prototype_ `EEnumOpenness GetOpenness() const;`

#### enum `uLang::CEnumeration::EEnumOpenness`  
`enum class EEnumOpenness`  
_L106-111_
- L108 _public enumerator_ `Closed`
- L109 _public enumerator_ `Open`
- L110 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API VERSECOMPILER_API`
- L17 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticFunction.h` (Public)


#### enum `uLang::EFunctionStringFlag`  
`enum class EFunctionStringFlag : uint16_t`  
_L21-28_
- L23 _public enumerator_ `Simple = 0x0` — function(:Type1,:Type2)
- L24 _public enumerator_ `Qualified = 1<<1` — Prepends the scope `(/MyModule:)` (unless async or native) and then the name of the function
- L25 _public enumerator_ `QualifiedParams = 1<<2` — Preform similar qualification of parameters
- L26 _public enumerator_ `QualifiedVersion1 = Qualified`
- L27 _public enumerator_ `QualifiedVersion2 = Qualified|QualifiedParams`

#### enum `uLang::EExtensionFieldAccessorKind`  
`enum class EExtensionFieldAccessorKind`  
_L62-67_
- desc: Distinguishes extension field accessor functions from other functions.
- L64 _public enumerator_ `Function`
- L65 _public enumerator_ `ExtensionDataMember`
- L66 _public enumerator_ `ExtensionMethod`

#### class `uLang::CFunction`  
`class CFunction : public CDefinition, public CLogicalScope, public CCaptureScope`  
_L74-251_
- inherits: `CDefinition,CLogicalScope,CCaptureScope`
- desc: Function scope, signature and body. All sub-expressions have their code text indexes relative to this containing context.
- L77 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Function;`
- L81 _public member_ `SSignature _Signature;` — Signature - parameter interface
- L83 _public member_ `EExtensionFieldAccessorKind _ExtensionFieldAccessorKind = EExtensionFieldAccessorKind::Function;`
- L85 _public member_ `const CFunctionType* _NegativeType = nullptr;`
- L91 _public member_ `TArray<const CFunction*> _LowerIdenticalFunctions;` — Functions whose types have a more precise result than `this` function for a given parameter type.  If both `this` function and any of `_LowerIdenticalFunctions` are in the same overload set, `this` function should removed from the set.
- L93 _public prototype_ `CFunction(const int32_t Index, const CSymbol& FunctionName, CScope& EnclosingScope);`
- L95 _public prototype_ `int32_t Index() const;`
- L98 _public function_ `virtual CSymbol GetScopeName() const override`
- L99 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L102 _public function_ `void SetOverriddenDefinition(const CFunction& OverriddenDefinition)`
- L103 _public function_ `void SetOverriddenDefinition(const CFunction* OverriddenDefinition)`
- L104 _public function_ `const CFunction* GetOverriddenDefinition() const`
- L109 _public function_ `const CFunction& GetBaseOverriddenDefinition() const`
- L114 _public function_ `const CFunction& GetBaseCoercedOverriddenFunction() const`
- L133 _public prototype_ `void SetSignature(SSignature&& Signature, SemanticRevision NextRevision);`
- L134 _public prototype_ `void MapSignature(const CFunctionType& FuncType, SemanticRevision NextRevision);`
- L136 _public function_ `TSPtr<CExpressionBase> GetBodyAst() const`
- L138 _public prototype_ `TSPtr<CExprClassDefinition> GetBodyClassDefinitionAst() const;`
- L140 _public prototype_ `TSPtr<CExprInterfaceDefinition> GetBodyInterfaceDefinitionAst() const;`
- L142 _public function_ `TSPtr<CExpressionBase> GetReturnTypeAst() const`
- L144 _public function_ `TSPtr<CExpressionBase> GetDefineeAst() const`
- L146 _public function_ `CExpressionBase* GetBodyIr() const`
- L148 _public prototype_ `CExprClassDefinition* GetBodyClassDefinitionIr() const;`
- L150 _public prototype_ `CExprInterfaceDefinition* GetBodyInterfaceDefinitionIr() const;`
- L152 _public function_ `CExpressionBase* GetReturnTypeIr() const`
- L154 _public function_ `SemanticRevision GetRevision() const`
- L155 _public function_ `SemanticRevision GetSignatureRevision() const`
- L156 _public function_ `SemanticRevision GetBodyRevision() const`
- L166 _public prototype_ `TOptional<const CClass*> GetMaybeClassScope() const;` — This is a holdover from old semantics, where functions were assumed to be a member of a class. THIS IS NO LONGER THE CASE, and we should forgo continued use of this function (we use it in the few places where this assumption still holds true). @TODO: SOL-1567, we should never need to explicitly query for a function's class, when functions could belong to a module, interface, other function etc.
- L167 _public prototype_ `TOptional<const CModule*> GetMaybeModuleScope() const;`
- L168 _public prototype_ `TOptional<const CNominalType*> GetMaybeContextType() const;`
- L171 _public prototype_ `CUTF8String GetDecoratedName(uint16_t StrFlags = uint16_t(EFunctionStringFlag::QualifiedVersion2)) const;` — Returns a decorated name for this function that includes its signature, for use in overloading.
- L174 _public prototype_ `CUTF8String GetQualifier() const;` — Returns the qualifier in canonical form
- L176 _public function_ `void MarkCoercion(const CFunction& CoercedFrom)`
- L178 _public function_ `bool IsCoercion() const`
- L180 _public function_ `void MarkCoercedOverride()`
- L182 _public function_ `bool IsCoercedOverride() const`
- L184 _public prototype_ `bool HasImplementation() const;`
- L186 _public prototype_ `bool IsNative() const;`
- L188 _public prototype_ `bool IsConstructor() const;`
- L191 _public function_ `void SetPrototypeDefinition(const CFunction& PrototypeDefinition)` — CDefinition interface.
- L192 _public function_ `const CFunction* GetPrototypeDefinition() const`
- L194 _public prototype_ `void SetAstNode(CExprFunctionDefinition* AstNode);`
- L195 _public prototype_ `CExprFunctionDefinition* GetAstNode() const;`
- L197 _public prototype_ `void SetIrNode(CExprFunctionDefinition* AstNode);`
- L198 _public prototype_ `CExprFunctionDefinition* GetIrNode(bool bForce = false) const;`
- L200 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const override`
- L202 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L204 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L206 _public function_ `virtual CScope* AsScope() override`
- L208 _public function_ `virtual CCaptureScope* GetParentCaptureScope() const override`
- L213 _public member_ `mutable bool _bIsAccessorOfSomeClassVar = false;` — HACK: using mutable here to set this after the fact
- L215 _public function_ `bool GetTrackLinkDependecies() const`
- L216 _public function_ `void SetTrackLinkDependecies(bool bTrackLinkDependecies)`
- L218 _public function_ `bool GetDontCall() const`
- L219 _public function_ `void SetDontCall(bool DontCall) const`
- L221 _public prototype_ `bool CanBeCalledFromPredicts() const;`
- L222 _public prototype_ `const CFunction* GetPredictsCoercedOriginalFunction() const;`
- L224 _public prototype_ `void InstantiateDefinition(CScope& InstPositiveScope, CScope& InstNegativeScope, const CNormalType& InstType, const TArray<STypeVariableSubstitution>& Substitutions) const override;`
- L225 _public prototype_ `void CreateNegativeDefinition(CScope& NegativeScope) const override;`
- L228 _private member_ `const int32_t _Index;`
- L232 _private member_ `const CFunction* _CoercedOriginalFunction{nullptr};` — non-null if this function was generated by the IR generator to apply coercions to the argument to and result of some other function.
- L237 _private member_ `bool _bCoercedOverride{false};` — `true` if this function needed a coercion to be generated to match an overridden function.  Note both this function and the coercion will have their overridden definition set.
- L240 _private member_ `bool _bTrackLinkDependencies{ false };` — `true` if this function must track link dependencies, i.e., it is used to create a default value in a class/interface.
- L244 _private member_ `mutable bool _bDontCall{ false };` — Only used if _bTrackLinkDependencies is `true` and the function can not be found. Will be true for the default function of a data field with accessors in an interface read from a digest.
- L247 _private member_ `SemanticRevision _SignatureRevision;` — Revision of the signature
- L250 _private member_ `SemanticRevision _BodyRevision;` — Revision of the body

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API VERSECOMPILER_API`
- L18 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticInterface.h` (Public)


#### class `uLang::CInterface`  
`class CInterface : public CDefinition, public CNominalType, public CLogicalScope`  
_L25-168_
- inherits: `CDefinition,CNominalType,CLogicalScope`
- desc: A interface: a named set of function signatures that can be implemented for other types.
- L28 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Interface;`
- L29 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Interface;`
- L32 _public member_ `CAttributable _EffectAttributable;` — Attributes on the interface macro, like "interface<unique>"
- L33 _public member_ `TOptional<SAccessLevel> _ConstructorAccessLevel;`
- L35 _public member_ `TArray<CInterface*> _SuperInterfaces;`
- L37 _public member_ `SEffectSet _ConstructorEffects;`
- L39 _public member_ `CInterface* _GeneralizedInterface{this};`
- L41 _public member_ `TArray<STypeVariableSubstitution> _TypeVariableSubstitutions;`
- L43 _public member_ `TURefArray<CInterface> _InstantiatedInterfaces;`
- L45 _public member_ `TUPtr<CInterface> _OwnedNegativeInterface;`
- L47 _public member_ `CInterface* _NegativeInterface;`
- L49 _public member_ `bool _bHasCyclesBroken { false };`
- L52 _public function_ `CInterface(const CSymbol& Name, CScope& EnclosingScope, const TArray<CInterface*>& SuperInterfaces = {}, SEffectSet ConstructorEffects = EffectSets::ClassAndInterfaceDefault) : CInterface(EnclosingScope, Name, SuperInterfaces, ConstructorEffects, this, {}, false)` — Construct a generalized positive interface
- L58 _public function_ `CInterface( CScope& EnclosingScope, const CSymbol& Name, const TArray<CInterface*>& SuperInterfaces, SEffectSet ConstructorEffects, CInterface* GeneralizedInterface, TArray<STypeVariableSubstitution> TypeVariableSubstitutions, bool bHasCyclesBroken) : CDefinition(StaticDefinitionKind, EnclosingScope, Name) , CNominalType(StaticTypeKind, EnclosingScope.GetProgram()) , CLogicalScope(CScope::EKind::Interface, &EnclosingScope, EnclosingScope.GetProgram()) , _SuperInterfaces(SuperInterfaces) , _ConstructorEffects(ConstructorEffects) , _GeneralizedInterface(GeneralizedInterface) , _TypeVariableSubstitutions(Move(TypeVariableSubstitutions)) , _OwnedNegativeInterface(TUPtr<CInterface>::New(this)) , _NegativeInterface(_OwnedNegativeInterface.Get()) , _bHasCyclesBroken(bHasCyclesBroken)` — construct a positive interface instantiation
- L80 _public prototype_ `explicit CInterface(CInterface* PositiveInterface);` — Construct a negative interface from a positive interface
- L82 _public function_ `SAccessLevel DerivedConstructorAccessLevel() const`
- L90 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — CTypeBase interface.
- L91 _public prototype_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;`
- L92 _public prototype_ `virtual EComparability GetComparability() const override;`
- L93 _public prototype_ `EComparability GetComparability(CVisitSet&) const;`
- L94 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L95 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L98 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface.
- L99 _public function_ `virtual const CTypeBase* ScopeAsType() const override`
- L100 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L101 _public function_ `virtual CScope* GetNegativeScope() const override`
- L104 _public prototype_ `virtual SmallDefinitionArray FindDefinitions( const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;` — CLogicalScope interface.
- L111 _public prototype_ `virtual void ForAllDefinitions( EMemberOrigin Origin, const TFunction<void(const CDefinition&)>& Functor, CVisitSet& VisitSet) const override;`
- L117 _public function_ `virtual const CDefinition* Definition() const override` — CNominalType interface.
- L120 _public function_ `void SetAstNode(CExprInterfaceDefinition* AstNode)` — CDefinition interface.
- L121 _public function_ `CExprInterfaceDefinition* GetAstNode() const`
- L123 _public function_ `void SetIrNode(CExprInterfaceDefinition* AstNode)`
- L124 _public function_ `CExprInterfaceDefinition* GetIrNode(bool bForce = false) const`
- L126 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const override`
- L128 _public function_ `bool HasCyclesBroken() const`
- L130 _public function_ `bool IsParametric() const`
- L135 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L137 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L139 _public prototype_ `bool IsUnique() const;`
- L141 _public prototype_ `bool HasOrInheritsVar(CVisitSet&) const;`
- L143 _public function_ `bool HasOrInheritsVar() const`
- L150 _public prototype_ `bool HasCastableAttribute() const;` — Does this interface hold a castable attribute?
- L153 _public prototype_ `const CNominalType* FindExplicitlyCastableBase() const;` — Return first class in the inheritance chain that contains the castable attribute. Otherwise null
- L155 _public function_ `virtual bool IsPersistable() const override`
- L158 _public function_ `virtual bool IsExplicitlyCastable() const override` — Is this interface castable either by having a castable attribute or inheriting one
- L161 _public function_ `virtual bool IsExplicitlyConcrete() const override` — Interfaces are never explicitly concrete
- L164 _public prototype_ `bool HasFinalSuperBaseAttribute() const;` — Does this interface hold a <final_super_base> attribute?
- L167 _public prototype_ `bool IsInterface(const CInterface& Interface) const;` — Determine if current interface is the same interface or a sub interface of the specified `Interface`

#### class `uLang::CInstantiatedInterface`  
`class CInstantiatedInterface : public CInstantiatedType`  
_L170-186_
- inherits: `CInstantiatedType`
- L173 _public function_ `CInstantiatedInterface(CSemanticProgram& Program, const CInterface& Interface, ETypePolarity Polarity, TArray<STypeVariableSubstitution> Arguments) : CInstantiatedType(Program, Polarity, Move(Arguments)) , _Interface(&Interface)`
- L179 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L182 _protected prototype_ `virtual const CNormalType& CreateNormalType() const override;`
- L185 _private member_ `const CInterface* _Interface;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API VERSECOMPILER_API`
- L22 _namespace_ `namespace uLang`
- L189 _prototype_ `CInterface* InstantiateInterface( const CInterface&, ETypePolarity, const TArray<STypeVariableSubstitution>&);` (scope `uLang`) — Eagerly instantiate an interface.
- L194 _prototype_ `CInterface* InstantiatePositiveInterface( const CInterface&, const TArray<STypeVariableSubstitution>&);` (scope `uLang`)
- L198 _prototype_ `TArray<STypeVariableSubstitution> InstantiateTypeVariableSubstitutions( const TArray<STypeVariableSubstitution>&, const TArray<STypeVariableSubstitution>&);` (scope `uLang`)
- L202 _prototype_ `TArray<CInterface*> InstantiatePositiveInterfaces( const TArray<CInterface*>&, const TArray<STypeVariableSubstitution>&);` (scope `uLang`)
- L206 _prototype_ `TArray<CInterface*> GetNegativeInterfaces(const TArray<CInterface*>& Interfaces);` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticProgram.h` (Public)


#### struct `uLang::SEffectDescriptor`  
`struct SEffectDescriptor`  
_L26-32_
- L28 _public member_ `SEffectSet _EffectSet;` — If we get this effect-set...
- L29 _public member_ `SEffectSet _RescindFromDefault;` — ...we trim these from the default
- L30 _public member_ `uLang::TArray<const CClass*> _MutualExclusions;` — ...but this effect set is not allowed with these others
- L31 _public member_ `bool _AllowInDecomposition = true;` — When decomposing an effect set, allow this class to be used. Needed when deprecating an effect.

#### struct `uLang::SDecompositionMapping`  
`struct SDecompositionMapping`  
_L34-38_
- L36 _public member_ `SEffectSet Effects;`
- L37 _public member_ `const CClass* Class;`

#### struct `uLang::SCachedEffectSetToEffectClassesKey`  
`struct SCachedEffectSetToEffectClassesKey`  
_L40-49_
- L42 _public member_ `SEffectSet TargetEffects;`
- L43 _public member_ `SEffectSet Default;`
- L45 _public function_ `bool operator==(const SCachedEffectSetToEffectClassesKey& Other) const`

#### struct `uLang::SConvertEffectClassesToEffectSetError`  
`struct SConvertEffectClassesToEffectSetError`  
_L51-61_
- L59 _public member_ `TArray<SMutuallyExclusiveEffectClassPair> InvalidPairs;`
- L60 _public member_ `SEffectSet ResultSet;`

#### struct `uLang::SConvertEffectClassesToEffectSetError::SMutuallyExclusiveEffectClassPair`  
`struct SMutuallyExclusiveEffectClassPair`  
_L53-57_
- L55 _public member_ `const CClass* First{};`
- L56 _public member_ `const CClass* Second{};`

#### class `uLang::CAstPackageRef`  
`class CAstPackageRef`  
_L72-83_
- desc: Encapsulates a reference to an AST/IR package
- L75 _public function_ `void SetAstPackage(CAstPackage* AstPackage)`
- L76 _public function_ `CAstPackage* GetAstPackage() const`
- L77 _public function_ `void SetIrPackage(CAstPackage* IrPackage)`
- L78 _public function_ `CAstPackage* GetIrPackage() const`
- L81 _private member_ `CAstPackage* _AstPackage{ nullptr };`
- L82 _private member_ `CAstPackage* _IrPackage{ nullptr };`

#### class `uLang::CModule`  
`class CModule : public CDefinition, public CNominalType, public CLogicalScope, public CAstPackageRef`  
_L88-148_
- inherits: `CDefinition,CNominalType,CLogicalScope,CAstPackageRef`
- desc: Semantically represents a module
- L91 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Module;`
- L92 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::Module;`
- L93 _public typedef_ `using PartArray = TUPtrArrayG<CModulePart, false, TInlineElementAllocator<1>>;`
- L95 _public prototype_ `CModule(const CSymbol& Name, CScope& EnclosingScope);`
- L98 _public function_ `bool HasParts() const` — Handling of partial module definitions
- L99 _public function_ `const PartArray& GetParts() const`
- L100 _public prototype_ `CModulePart& CreatePart(CScope* ParentScope, bool bExplicitDefinition);`
- L101 _public prototype_ `bool IsExplicitDefinition() const;`
- L104 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface
- L105 _public function_ `virtual const CTypeBase* ScopeAsType() const override`
- L106 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L109 _public prototype_ `virtual SmallDefinitionArray FindDefinitions( const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;` — CLogicalScope interface
- L115 _public prototype_ `virtual void ForAllDefinitions(EMemberOrigin, const TFunction<void(const CDefinition&)>&, CVisitSet&) const override;`
- L118 _public prototype_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override;` — CTypeBase interface.
- L119 _public function_ `virtual bool IsPersistable() const override`
- L120 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L121 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L122 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L125 _public function_ `virtual const CDefinition* Definition() const override` — CNominalType interface.
- L128 _public function_ `virtual const CLogicalScope* DefinitionAsLogicalScopeNullable() const override` — CDefinition interface.
- L129 _public function_ `void SetAstNode(CExprModuleDefinition* AstNode)`
- L130 _public function_ `CExprModuleDefinition* GetAstNode() const`
- L131 _public function_ `void SetIrNode(CExprModuleDefinition* AstNode)`
- L132 _public function_ `CExprModuleDefinition* GetIrNode(bool bForce = false) const`
- L134 _public prototype_ `void MarkPersistenceCompatConstraint() const;`
- L136 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L138 _public prototype_ `void MarkEntitlementCompatConstraint() const;`
- L140 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L144 _private member_ `PartArray _Parts;` — The partial modules that make up this module (in 99% of cases there will be just one)
- L146 _private member_ `mutable bool _bPersistenceCompatConstraint{false};`
- L147 _private member_ `mutable bool _bEntitlementCompatConstraint{false};`

#### class `uLang::CModulePart`  
`class CModulePart : public CScope, public TAstNodeRef<CExprModuleDefinition>, public CAstPackageRef`  
_L155-179_
- inherits: `CScope,TAstNodeRef<CExprModuleDefinition>,CAstPackageRef`
- desc: Semantically represents a partial module aka a module definition either via vmodule file or module macro Always is directly parented to a CModule
- L158 _public function_ `CModulePart(CModule& Module, CScope* ParentScope, bool bExplicitDefinition, CSemanticProgram& Program) : CScope(EKind::ModulePart, ParentScope, Program), _Module(Module), _bExplicitDefinition(bExplicitDefinition)`
- L161 _public function_ `const CModule* GetModule() const` — This statically overrides CScope::GetModule() for efficiency, calling either override will return the same result
- L162 _public function_ `CModule* GetModule()`
- L163 _public function_ `bool IsExplicitDefinition() const`
- L164 _public function_ `void SetAvailableVersion(TOptional<uint64_t> InAvailableVersion)`
- L165 _public function_ `const TOptional<uint64_t>& GetAvailableVersion() const`
- L168 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface
- L169 _public function_ `virtual const CTypeBase* ScopeAsType() const override`
- L170 _public function_ `virtual const CDefinition* ScopeAsDefinition() const override`
- L172 _public function_ `virtual const CLogicalScope* AsLogicalScopeNullable() const override`
- L173 _public function_ `virtual CLogicalScope* AsLogicalScopeNullable() override`
- L176 _private member_ `CModule& _Module;` — The module this part belongs to
- L177 _private member_ `bool _bExplicitDefinition;` — True for definition via module macro, false for definition via directory or VersePath component
- L178 _private member_ `TOptional<uint64_t> _AvailableVersion;` — Used to ensure that all multi-part module parts have the same version. That is currently a requirement.

#### class `uLang::CSnippet`  
`class CSnippet : public CScope, public CNamed`  
_L184-191_
- inherits: `CScope,CNamed`
- desc: Semantically represents a snippet
- L187 _public function_ `CSnippet(const CSymbol& Path, CScope* ParentScope, CSemanticProgram& Program) : CScope(EKind::Snippet, ParentScope, Program), CNamed(Path)`
- L190 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface

#### class `uLang::CIntrinsicSymbols`  
`class CIntrinsicSymbols`  
_L196-259_
- desc: Container structure for the various pre-defined, intrinsic symbols.
- L199 _public prototype_ `void Initialize(CSymbolTable&);`
- L201 _public prototype_ `CSymbol GetArithmeticOpName(CExprBinaryArithmetic::EOp) const;`
- L203 _public prototype_ `CSymbol GetComparisonOpName(CExprComparison::EOp) const;`
- L205 _public prototype_ `CSymbol GetAssignmentOpName(CExprAssignment::EOp) const;`
- L207 _public prototype_ `CUTF8String MakeExtensionFieldOpName(CSymbol FieldName) const;`
- L208 _public prototype_ `CUTF8StringView StripExtensionFieldOpName(CSymbol FieldName) const;`
- L210 _public prototype_ `bool IsOperatorOpName(CSymbol) const;`
- L212 _public prototype_ `bool IsPrefixOpName(CSymbol) const;`
- L214 _public prototype_ `bool IsPostfixOpName(CSymbol) const;`
- L216 _public member_ `CSymbol _OpNameNegate;`
- L217 _public member_ `CSymbol _OpNameAdd;`
- L218 _public member_ `CSymbol _OpNameSub;`
- L219 _public member_ `CSymbol _OpNameMul;`
- L220 _public member_ `CSymbol _OpNameDiv;`
- L221 _public member_ `CSymbol _OpNameLess;`
- L222 _public member_ `CSymbol _OpNameLessEqual;`
- L223 _public member_ `CSymbol _OpNameGreater;`
- L224 _public member_ `CSymbol _OpNameGreaterEqual;`
- L225 _public member_ `CSymbol _OpNameEqual;`
- L226 _public member_ `CSymbol _OpNameNotEqual;`
- L227 _public member_ `CSymbol _OpNameAddRMW;`
- L228 _public member_ `CSymbol _OpNameSubRMW;`
- L229 _public member_ `CSymbol _OpNameMulRMW;`
- L230 _public member_ `CSymbol _OpNameDivRMW;`
- L231 _public member_ `CSymbol _OpNameCall;`
- L232 _public member_ `CSymbol _OpNameQuery;`
- L234 _public member_ `CSymbol _FuncNameAbs;`
- L235 _public member_ `CSymbol _FuncNameCeil;`
- L236 _public member_ `CSymbol _FuncNameFloor;`
- L237 _public member_ `CSymbol _FuncNameWeakMap;`
- L238 _public member_ `CSymbol _FuncNameFitsInPlayerMap;`
- L240 _public member_ `CSymbol _FieldNameLength;`
- L242 _public member_ `CSymbol _Wildcard;` — `_`
- L244 _public member_ `CSymbol _Inf;`
- L245 _public member_ `CSymbol _NaN;`
- L248 _public member_ `CSymbol _MinUploadedAtFNVersion;` — @available symbols
- L250 _public member_ `CSymbol _VersePath;`
- L253 _private member_ `CUTF8StringView _OperatorOpNamePrefix;`
- L254 _private member_ `CUTF8StringView _PrefixOpNamePrefix;`
- L255 _private member_ `CUTF8StringView _PostfixOpNamePrefix;`
- L256 _private member_ `CUTF8StringView _OpNameSuffix;`
- L257 _private member_ `CUTF8StringView _ExtensionFieldPrefix;`
- L258 _private member_ `CUTF8StringView _ExtensionFieldSuffix;`

#### class `uLang::CCompatConstraintRoot`  
`class CCompatConstraintRoot : public CSharedMix, public CLogicalScope`  
_L264-276_
- inherits: `CSharedMix,CLogicalScope`
- desc: Serves as an alternate root scope for definitions in packages that define compatibility constraints.
- L267 _public function_ `CCompatConstraintRoot(CSemanticProgram& Program) : CLogicalScope(CScope::EKind::CompatConstraintRoot, nullptr, Program)`
- L272 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface
- L274 _public prototype_ `virtual SmallDefinitionArray FindDefinitions(const CSymbol& Name, EMemberOrigin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet&) const override;`
- L275 _public prototype_ `virtual void ForAllDefinitions(EMemberOrigin, const TFunction<void(const CDefinition&)>&, CVisitSet&) const override;`

#### class `uLang::CSemanticProgram`  
`class CSemanticProgram : public CSharedMix, public CLogicalScope`  
_L283-783_
- inherits: `CSharedMix,CLogicalScope`
- desc: Stores whole parsed semantic hierarchy/infrastructure
- L289 _public member_ `TSPtr<CCompatConstraintRoot> _GeneralCompatConstraintRoot;` — An optional root module for a compatible ancestor of the current code.
- L290 _public member_ `TSPtr<CCompatConstraintRoot> _PersistenceCompatConstraintRoot;`
- L291 _public member_ `TSPtr<CCompatConstraintRoot> _PersistenceSoftCompatConstraintRoot;`
- L294 _public member_ `TSPtr<CAstPackage> _BuiltInPackage;` — The notional package that is created to contain the built-in definitions.
- L297 _public member_ `CModule* _VerseModule{nullptr};` — The /Verse.org/Verse module.
- L300 _public member_ `CFalseType _falseType {*this};` — Global types for the program.
- L301 _public member_ `CTrueType _trueType {*this};`
- L302 _public member_ `CVoidType _voidType {*this};`
- L303 _public member_ `CAnyType _anyType {*this};`
- L304 _public member_ `CComparableType _comparableType {*this};`
- L305 _public member_ `CPersistableType _persistableType {*this};`
- L306 _public member_ `CLogicType _logicType {*this};`
- L307 _public member_ `CRationalType _rationalType {*this};`
- L308 _public member_ `CChar8Type _char8Type {*this};`
- L309 _public member_ `CChar32Type _char32Type {*this};`
- L310 _public member_ `CPathType _pathType {*this};`
- L311 _public member_ `CRangeType _rangeType {*this};`
- L312 _public member_ `CTupleType _EmptyTupleType {*this, {}, 0};`
- L315 _public member_ `const CTypeType* _typeType{nullptr};` — Non-globalTypes that have an alias
- L316 _public member_ `const CIntType* _intType{nullptr};`
- L317 _public member_ `const CFloatType* _floatType{nullptr};`
- L319 _public member_ `CTypeAlias* _falseAlias{nullptr};`
- L320 _public member_ `CTypeAlias* _trueAlias{nullptr};`
- L321 _public member_ `CTypeAlias* _voidAlias{nullptr};`
- L322 _public member_ `CTypeAlias* _anyAlias{nullptr};`
- L323 _public member_ `CTypeAlias* _comparableAlias{nullptr};`
- L324 _public member_ `CTypeAlias* _logicAlias{nullptr};`
- L325 _public member_ `CTypeAlias* _intAlias{nullptr};`
- L326 _public member_ `CTypeAlias* _rationalAlias{nullptr};`
- L327 _public member_ `CTypeAlias* _floatAlias{nullptr};`
- L328 _public member_ `CTypeAlias* _char8Alias{nullptr};`
- L329 _public member_ `CTypeAlias* _char32Alias{nullptr};`
- L330 _public member_ `CTypeAlias* _stringAlias{nullptr};`
- L331 _public member_ `CTypeAlias* _typeAlias{nullptr};`
- L334 _public prototype_ `const CFunction* GetTaskFunction() const;` — Task class
- L335 _public prototype_ `const CClass* GetTaskClass() const;`
- L336 _public prototype_ `const CTypeBase* InstantiateTaskType(const CTypeBase* TypeArgument);`
- L339 _public prototype_ `const CClassDefinition* GetLeaderboardClassDefinition() const;` — Leaderboard class
- L342 _public prototype_ `const CClassDefinition* GetEntitlementClassDefinition() const;` — Entitlement class
- L345 _public member_ `CClass* _attributeClass{nullptr};` — Attribute classes
- L346 _public member_ `CClass* _abstractClass{nullptr};` — <abstract> - class: cannot be instantiated - only its subclasses
- L347 _public member_ `CClass* _finalClass{nullptr};` — <final> - class: cannot be used as superclass; routine: cannot be overridden
- L348 _public member_ `CClass* _concreteClass{nullptr};` — <concrete> - class: all properties, including superclasses, must have initializers.
- L349 _public member_ `CClass* _uniqueClass{nullptr};` — <unique> - class: comparable with only the same instances equal
- L350 _public member_ `CClass* _intrinsicClass{nullptr};` — <intrinsic> - implementation is generated inline by backend
- L351 _public member_ `CClass* _nativeClass{nullptr};` — <native> - native body/implementation in C++
- L352 _public member_ `CClass* _nativeCallClass{nullptr};` — <native_callable> - script function which can be called from C++
- L353 _public member_ `CClass* _castableClass{nullptr};` — <castable> - enforces that a class or interface is castable - effectively non-parametric
- L354 _public member_ `CClass* _finalSuperClass{ nullptr };` — <final_super> - enforces that this class is always a direct descendant of its original class or interface through back compat
- L355 _public member_ `CClass* _finalSuperBaseClass{nullptr};` — <final_super_base> - enforces that any type published as a direct subtype of this class will always be a direct subtype through back compat checking
- L357 _public member_ `CClass* _suspendsClass{nullptr};` — <suspends> - a durational, coroutine function
- L358 _public member_ `CClass* _decidesClass{nullptr};` — <decides> - failure effect
- L359 _public member_ `CClass* _variesClassDeprecated{nullptr};` — <varies> - impure meta-effect: non-referentially transparent
- L360 _public member_ `CClass* _computesClass{nullptr};` — <computes> - pure meta-effect: referentially transparent
- L361 _public member_ `CClass* _convergesClass{nullptr};` — <converges> - converges meta-effect: function is guaranteed to return in finite time
- L362 _public member_ `CClass* _transactsClass{nullptr};` — <transacts> - equivalent to computes+reads+writes+allocates
- L363 _public member_ `CClass* _readsClass{nullptr};` — <reads> - pointer reading. Part of transacts.
- L364 _public member_ `CClass* _writesClass{nullptr};` — <writes> - pointer writing. Part of transacts.
- L365 _public member_ `CClass* _allocatesClass{nullptr};` — <allocates> - adds some finer granularity on <varies> for unique classes and mutable values
- L367 _public member_ `CClass* _constructorClass{nullptr};` — <constructor> - this function is a constructor for the result class
- L368 _public member_ `CClass* _openClass{nullptr};` — <open> - used for open enumerations
- L369 _public member_ `CClass* _closedClass{nullptr};` — <closed> - default for enumerations - opposite of open
- L370 _public member_ `CClass* _overrideClass{nullptr};` — <override> - this function overrides an inherited function
- L371 _public member_ `CClass* _publicClass{nullptr};` — <public> - member which can be accessed from anywhere
- L372 _public member_ `CClass* _privateClass{nullptr};` — <private> - member which can only be accessed by the owning class
- L373 _public member_ `CClass* _protectedClass{nullptr};` — <protected> - member which can only be accessed by the owning class and sub-classes
- L374 _public member_ `CClass* _internalClass{nullptr};` — <internal> - member which can only be accessed by the current module
- L375 _public member_ `CClass* _scopedClass{ nullptr };` — <scoped> - member which can only be accessed by a code-specified list of modules
- L376 _public member_ `CClass* _epicInternalClass{nullptr};` — <epic_internal> - member which can only be accessed in Epic code
- L377 _public member_ `CClass* _localizes{nullptr};` — <localizes> - data definition or function that should resolve to a 'message' at runtime
- L378 _public member_ `CClass* _ignore_unreachable{nullptr};` — @ignore_unreachable - unreachable code that can be ignored
- L379 _public member_ `CClass* _deprecatedClass{nullptr};` — @deprecated - this definition is deprecated
- L380 _public member_ `CClass* _experimentalClass{nullptr};` — @experimental - this definition is experimental
- L381 _public member_ `CClass* _persistentClass{nullptr};` — <persistent> - specify a `module_scoped_var_weak_map_key`'s related value is persistent
- L382 _public member_ `CClass* _persistableClass{nullptr};` — <persistable> - `struct` may be stored in a module-scoped `var` with `persistent` key
- L383 _public member_ `CClass* _moduleScopedVarWeakMapKeyClass{nullptr};` — <module_scoped_var_weak_map_key> - allow use as module-scoped `var` `weak_map` key
- L384 _public member_ `CClass* _rtfmAlwaysOpen{nullptr};` — @rtfm_always_open - this native function can always run in the open
- L385 _public member_ `CClass* _vmNoEffectToken{nullptr};` — @vm_no_effect_token - this native function can run without a concrete effect token
- L386 _public member_ `CClass* _getterClass{nullptr};`
- L387 _public member_ `CClass* _setterClass{nullptr};`
- L388 _public member_ `CClass* _predictsClass{nullptr};` — <predicts> - data definition that should be accessible from <predicts> contexts
- L389 _public member_ `CClass* _uhtComparableClass{nullptr};` — <uht_comparable> - native UHT structure that supports equality
- L391 _public member_ `CClass* _attributeScopeAttribute{ nullptr };` — @attribscope_attribute - attribute which can be used with prefix @attr syntax
- L392 _public member_ `CClass* _attributeScopeSpecifier{ nullptr };` — @attribscope_specifier - attribute which can be used with suffix <spec> syntax
- L393 _public member_ `CClass* _attributeScopeModule{nullptr};` — @attribscope_module - attribute which can be used on the module definition scope
- L394 _public member_ `CClass* _attributeScopeClass{nullptr};` — @attribscope_class - attribute which can be used on the class definition scope
- L395 _public member_ `CClass* _attributeScopeStruct{nullptr};` — @attribscope_struct - attribute which can be used on the struct definition scope
- L396 _public member_ `CClass* _attributeScopeData{nullptr};` — @attribscope_data - attribute which can be used on defining data members within a class
- L397 _public member_ `CClass* _attributeScopeFunction{nullptr};` — @attribscope_function - attribute which can be used on functions
- L398 _public member_ `CClass* _attributeScopeEnum{nullptr};` — @attribscope_enum - attribute which can be used on enumerations
- L399 _public member_ `CClass* _attributeScopeEnumerator{nullptr};` — @attribscope_enumerator - attribute which can be used on a single enumeration value
- L400 _public member_ `CClass* _attributeScopeAttributeClass{nullptr};` — @attribscope_attribclass - attribute which can be used on attribute classes
- L401 _public member_ `CClass* _attributeScopeInterface{nullptr};` — @attribscope_interface - attribute which can be used on interfaces
- L402 _public member_ `CClass* _attributeScopeIdentifier{nullptr};` — @attribscope_identifier - attribute which can be used on identifier expressions
- L403 _public member_ `CClass* _attributeScopeExpression{nullptr};` — @attribscope_expression - attribute which can be used on expressions
- L404 _public member_ `CClass* _attributeScopeClassMacro{nullptr};` — @attribscope_classmacro - attribute which can be used class<here>{}
- L405 _public member_ `CClass* _attributeScopeStructMacro{nullptr};` — @attribscope_structmacro - attribute which can be used struct<here>{}
- L406 _public member_ `CClass* _attributeScopeInterfaceMacro{nullptr};` — @attribscope_interfacemacro - attribute which can be used interface<here>{}
- L407 _public member_ `CClass* _attributeScopeEnumMacro{nullptr};` — @attribscope_enummacro - attribute which can be used enum<here>{}
- L408 _public member_ `CClass* _attributeScopeVar{nullptr};` — @attribscope_var - attribute which can be used var<here>
- L409 _public member_ `CClass* _attributeScopeName{nullptr};` — @attribscope_name - attribute which can be used on names
- L410 _public member_ `CClass* _attributeScopeEffect{nullptr};` — @attribscope_effect - attribute which can be used as an effect
- L411 _public member_ `CClass* _attributeScopeTypeDefinition{nullptr};` — @attribscope_typedefinition - attribute which can be on type definitions
- L412 _public member_ `CClass* _attributeScopeScopedDefinition{nullptr};` — @attribscope_scopeddefinition - attribute which can be on scoped access level definitions
- L413 _public member_ `CClass* _customAttributeHandler{nullptr};` — @customattribhandler - attribute has a native custom handler to process
- L415 _public member_ `CClass* _availableClass{nullptr};` — @available - this definition is only available in certain versions
- L417 _public member_ `CClass* _expose_to_web_data_sync_service_reads{nullptr};`
- L418 _public member_ `CClass* _expose_to_web_data_sync_service_writes{nullptr};`
- L440 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _editable{ *this, "/Ver`
- L441 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _editable_non_concrete{ *this, "/Ver`
- L443 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _import_as_attribute{ *this, "/Ver`
- L444 _public member_ `TCachedIntrinsicDefinition<CFunction> _import_as{ *this, "/Ver`
- L446 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _cpp_name_attribute{ *this, "/Ver`
- L447 _public member_ `TCachedIntrinsicDefinition<CFunction> _cpp_name{ *this, "/Ver`
- L449 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _doc_attribute{ *this, "/Ver`
- L451 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _message_class{ *this, "/Ver`
- L453 _public member_ `TCachedIntrinsicDefinition<CFunction> _taskFunction{ *this, "/Ver`
- L455 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _leaderboardClassDefinition{ *this, "/Ver`
- L457 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _entitlementClassDefinition{ *this, "/For`
- L459 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _agent_class{ *this, "/Ver`
- L461 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _replicated{ *this, "/Ver`
- L463 _public member_ `TCachedIntrinsicDefinition<CClassDefinition> _preload{ *this, "/Ver`
- L465 _public member_ `TCachedIntrinsicDefinition<CFunction> _MakeMessageInternalFunction{ *this, "/Ver`
- L466 _public member_ `TCachedIntrinsicDefinition<CFunction> _MakeAssetFunction{ *this, "/Ver`
- L467 _public member_ `TCachedIntrinsicDefinition<CFunction> _MakeCollisionProfileFunction{ *this, "/Ver`
- L468 _public member_ `TCachedIntrinsicDefinition<CFunction> _InitializeComponentFieldFunction{ *this, "/Ver`
- L471 _public member_ `CFunction* _ComparableEqualOp{nullptr};` — Intrinsic functions.
- L472 _public member_ `CFunction* _ComparableNotEqualOp{nullptr};`
- L474 _public member_ `CFunction* _IntNegateOp{nullptr};`
- L475 _public member_ `CFunction* _IntAddOp{nullptr};`
- L476 _public member_ `CFunction* _IntSubtractOp{nullptr};`
- L477 _public member_ `CFunction* _IntMultiplyOp{nullptr};`
- L478 _public member_ `CFunction* _IntDivideOp{nullptr};`
- L479 _public member_ `CFunction* _IntAddAssignOp{nullptr};`
- L480 _public member_ `CFunction* _IntSubtractAssignOp{nullptr};`
- L481 _public member_ `CFunction* _IntMultiplyAssignOp{nullptr};`
- L482 _public member_ `CFunction* _IntAbs{nullptr};`
- L484 _public member_ `CFunction* _IntGreaterOp{nullptr};`
- L485 _public member_ `CFunction* _IntGreaterEqualOp{nullptr};`
- L486 _public member_ `CFunction* _IntLessOp{nullptr};`
- L487 _public member_ `CFunction* _IntLessEqualOp{nullptr};`
- L489 _public member_ `CFunction* _MakeRationalFromInt{nullptr};`
- L490 _public member_ `CFunction* _RationalCeil{nullptr};`
- L491 _public member_ `CFunction* _RationalFloor{nullptr};`
- L493 _public member_ `CFunction* _FloatNegateOp{nullptr};`
- L494 _public member_ `CFunction* _FloatAddOp{nullptr};`
- L495 _public member_ `CFunction* _FloatSubtractOp{nullptr};`
- L496 _public member_ `CFunction* _FloatMultiplyOp{nullptr};`
- L497 _public member_ `CFunction* _FloatDivideOp{nullptr};`
- L498 _public member_ `CFunction* _FloatAddAssignOp{nullptr};`
- L499 _public member_ `CFunction* _FloatSubtractAssignOp{nullptr};`
- L500 _public member_ `CFunction* _FloatMultiplyAssignOp{nullptr};`
- L501 _public member_ `CFunction* _FloatDivideAssignOp{nullptr};`
- L502 _public member_ `CFunction* _FloatAbs{nullptr};`
- L504 _public member_ `CFunction* _IntMultiplyFloatOp{nullptr};`
- L505 _public member_ `CFunction* _FloatMultiplyIntOp{nullptr};`
- L507 _public member_ `CFunction* _FloatGreaterOp{nullptr};`
- L508 _public member_ `CFunction* _FloatGreaterEqualOp{nullptr};`
- L509 _public member_ `CFunction* _FloatLessOp{nullptr};`
- L510 _public member_ `CFunction* _FloatLessEqualOp{nullptr};`
- L512 _public member_ `CFunction* _ArrayAddOp{nullptr};`
- L513 _public member_ `CFunction* _ArrayAddAssignOp{nullptr};`
- L514 _public member_ `CFunction* _ArrayLength{nullptr};`
- L515 _public member_ `CFunction* _ArrayCallOp{nullptr};`
- L516 _public member_ `CFunction* _ArrayRefCallOp0{nullptr};`
- L518 _public member_ `CFunction* _ArrayRefCallOp1{nullptr};`
- L521 _public member_ `CFunction* _MapRefCallOp{nullptr};`
- L522 _public member_ `CFunction* _MapLength{nullptr};`
- L523 _public member_ `CFunction* _MapConcatenateMaps{nullptr};`
- L525 _public member_ `CFunction* _WeakMapCallOp{nullptr};`
- L526 _public member_ `CFunction* _WeakMapRefCallOp0{nullptr};`
- L528 _public member_ `CFunction* _WeakMapRefCallOp1{nullptr};`
- L530 _public member_ `CFunction* _WeakMapOp{nullptr};`
- L532 _public member_ `CFunction* _LogicQueryOp{nullptr};`
- L534 _public member_ `CFunction* _OptionQueryOp{nullptr};`
- L536 _public member_ `CFunction* _FitsInPlayerMap{nullptr};`
- L538 _public member_ `CDataDefinition* _InfDefinition{nullptr};`
- L539 _public member_ `CDataDefinition* _NaNDefinition{nullptr};`
- L541 _public member_ `CFunction* _Getter{nullptr};`
- L542 _public member_ `CFunction* _Setter{nullptr};`
- L543 _public member_ `CFunction* _UnsafeCast{nullptr};`
- L545 _public member_ `CFunction* _PredictsGetDataValue{nullptr};`
- L546 _public member_ `CFunction* _PredictsGetDataRef{nullptr};`
- L549 _public member_ `CIntrinsicSymbols _IntrinsicSymbols;` — Quick access names
- L551 _public member_ `TArray<CUTF8String> _EpicInternalModulePrefixes;`
- L553 _public member_ `TSPtr<CAstProject> _AstProject;`
- L556 _private member_ `TSPtr<CAstProject> _IrProject;`
- L562 _public function_ `TSPtr<CAstProject>& GetIrProject()` — The get-method is written to work even if no IR is generated. This is to make it easier to run with and without IR, a useful feature while developing the IR. It's temporary and won't work after IrNode is its own type distinct from AstNode.
- L563 _public function_ `void SetIrProject(const TSPtr<CAstProject>& project)`
- L567 _public function_ `CSemanticProgram() : CLogicalScope(CScope::EKind::Program, nullptr, *this)`
- L570 _public function_ `~CSemanticProgram()`
- L580 _public prototype_ `void Initialize(TSPtr<CSymbolTable> Symbols = TSPtr<CSymbolTable>());`
- L582 _public function_ `const TSPtr<CSymbolTable>& GetSymbols() const`
- L584 _public prototype_ `CSnippet& GetOrCreateSnippet(const CSymbol& Path, CScope* ParentScope);`
- L585 _public prototype_ `CSnippet* FindSnippet(const CUTF8StringView& NameStr) const;`
- L587 _public prototype_ `CArrayType& GetOrCreateArrayType(const CTypeBase* ElementType);`
- L589 _public prototype_ `CGeneratorType& GetOrCreateGeneratorType(const CTypeBase* ElementType);`
- L591 _public prototype_ `CMapType& GetOrCreateMapType(const CTypeBase* KeyType, const CTypeBase* ValueType);`
- L592 _public prototype_ `CMapType& GetOrCreateWeakMapType(const CTypeBase& KeyType, const CTypeBase& ValueType);`
- L593 _public prototype_ `CMapType& GetOrCreateMapType(const CTypeBase& KeyType, const CTypeBase& ValueType, bool bWeak);`
- L595 _public prototype_ `CPointerType& GetOrCreatePointerType(const CTypeBase* NegativeValueType, const CTypeBase* PositiveValueType);`
- L597 _public prototype_ `CReferenceType& GetOrCreateReferenceType(const CTypeBase* NegativeValueType, const CTypeBase* PositiveValueType);`
- L599 _public prototype_ `COptionType& GetOrCreateOptionType(const CTypeBase* ValueType);`
- L601 _public prototype_ `CTypeType& GetOrCreateTypeType(const CTypeBase* NegativeType, const CTypeBase* PositiveType);`
- L602 _public prototype_ `CTypeType& GetOrCreateSubtypeType(const CTypeBase* PositiveType);`
- L604 _public prototype_ `CCastableType& GetOrCreateCastableType(const CTypeBase& SuperType);`
- L605 _public prototype_ `CConcreteType& GetOrCreateConcreteType(const CTypeBase& SuperType);`
- L607 _public prototype_ `CTupleType& GetOrCreateTupleType(CTupleType::ElementArray&& Elements);`
- L608 _public prototype_ `CTupleType& GetOrCreateTupleType( CTupleType::ElementArray&& Elements, int32_t FirstNamedIndex);`
- L612 _public prototype_ `CNamedType& GetOrCreateNamedType( CSymbol Name, const CTypeBase* ValueType, bool HasValue);`
- L616 _public prototype_ `const CFunctionType& GetOrCreateFunctionType( const CTypeBase& ParamsType, const CTypeBase& ReturnType, SEffectSet Effects = EffectSets::FunctionDefault, bool bClosed = false, TArray<const CTypeVariable*> TypeVariables = {}, bool ImplicitlySpecialized = false);`
- L624 _public prototype_ `const CIntType& GetOrCreateConstrainedIntType(FIntOrNegativeInfinity Min, FIntOrPositiveInfinity Max);`
- L625 _public prototype_ `const CFloatType& GetOrCreateConstrainedFloatType(double Min, double Max);`
- L627 _public prototype_ `CFlowType& CreateFlowType(ETypePolarity);`
- L628 _public prototype_ `CFlowType& CreateFlowType(ETypePolarity, const CTypeBase*);`
- L629 _public function_ `CFlowType& CreateNegativeFlowType()`
- L630 _public function_ `CFlowType& CreatePositiveFlowType()`
- L632 _public prototype_ `CInstantiatedClass& CreateInstantiatedClass(const CClass&, ETypePolarity, TArray<STypeVariableSubstitution>);`
- L634 _public prototype_ `CInstantiatedInterface& CreateInstantiatedInterface(const CInterface&, ETypePolarity, TArray<STypeVariableSubstitution>);`
- L643 _public prototype_ `SExplicitTypeParam CreateExplicitTypeParam( CFunction*, CSymbol DataName, CSymbol TypeName, CSymbol NegativeTypeName, const CTypeType* Type);`
- L650 _public prototype_ `void AddStandardAccessLevelAttributes(CAttributable* NewAccessLevel) const;`
- L652 _public function_ `const CUnknownType* GetDefaultUnknownType() const`
- L656 _public function_ `template<class T> T* FindDefinitionByVersePath(CUTF8StringView VersePath) const` — Find definition by Verse path
- L663 _public function_ `SemanticRevision GetNextRevision() const` — Get next revision to use when creating new functions etc.
- L667 _public prototype_ `void PopulateCoreAPI();` — Add common classes and bindings TODO-Verse: This might be always done, though it may be done solely by converting a CSyntaxProgram
- L670 _public function_ `virtual CSymbol GetScopeName() const override` — Program has no name
- L673 _public function_ `int32_t NextFunctionIndex()`
- L679 _public prototype_ `const SEffectDescriptor& FindEffectDescriptorChecked(const CClass* effectKey, uint32_t UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest) const;` — Construct the effects descriptor table against this instance of the program's notion of the effect classes
- L680 _public function_ `inline const TArray<const CClass*>& GetAllEffectClasses() const`
- L682 _public prototype_ `TOptional<SEffectSet> ConvertEffectClassesToEffectSet( const TArray<const CClass*>& EffectClasses, const SEffectSet& DefaultEffectSet, SConvertEffectClassesToEffectSetError* OutError = nullptr, uint32_t UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest) const;`
- L688 _public prototype_ `TOptional<TArray<const CClass*>> ConvertEffectSetToEffectClasses(const SEffectSet& EffectSet, const SEffectSet& DefaultEffectSet) const;`
- L690 _public prototype_ `const SSymbolDefinitionArray* GetGlobalDefinitionsBySymbol(CSymbol Symbol) const;`
- L693 _public prototype_ `const CTupleType* GetProfileLocusType();`
- L694 _public prototype_ `const CTupleType* GetProfileDataType();`
- L703 _private member_ `TURefSet<CSnippet, CSymbol> _Snippets;` — Snippets
- L706 _private member_ `TURefSet<CArrayType, const CTypeBase*> _ArrayTypes;` — Array types
- L709 _private member_ `TURefSet<CGeneratorType, const CTypeBase*> _GeneratorTypes;` — Generator types
- L712 _private member_ `TURefSet<CMapType, CMapType::SKey> _MapTypes;` — Map types
- L715 _private member_ `TURefSet<CPointerType, CPointerType::Key> _PointerTypes;` — Pointer types
- L718 _private member_ `TURefSet<CReferenceType, CReferenceType::Key> _ReferenceTypes;` — Reference types
- L721 _private member_ `TURefSet<COptionType, const CTypeBase*> _OptTypes;` — Option types
- L724 _private member_ `TURefSet<CTypeType, CTypeType::Key> _TypeTypes;` — Type types
- L727 _private member_ `TURefSet<CCastableType, CCastableType::Key> _CastableTypes;` — Castable types
- L730 _private member_ `TURefSet<CConcreteType, CConcreteType::Key> _ConcreteTypes;` — Concrete types
- L733 _private member_ `TURefSet<CNamedType, CNamedType::Key> _NamedTypes;` — Named argument types
- L736 _private member_ `TURefArray<CFlowType> _FlowTypes;` — Flow types
- L739 _private member_ `TURefSet<CIntType, CIntType::Key> _ConstrainedIntTypes;` — Ints constrained with the 'where' clause (the top int also happens to be retained here for easy hash-consing).
- L742 _private member_ `TURefSet<CFloatType, CFloatType::Key> _ConstrainedFloatTypes;` — Floats constrained with the 'where' clause (the top float also happens to be retained here for easy hash-consing).
- L745 _private member_ `TURefArray<CInstantiatedClass> _InstantiatedClasses;` — Instantiated classes
- L748 _private member_ `TURefArray<CInstantiatedInterface> _InstantiatedInterfaces;` — Instantiated interfaces
- L751 _private member_ `TUPtr<CUnknownType> _DefaultUnknownType;` — Default unknown type
- L755 _private member_ `TSPtr<CSymbolTable> _Symbols;` — Shared symbol table for this program. It can be the same table as other areas too though all structures storing a symbol in this program must use this table.
- L757 _private member_ `int32_t _NumFunctions{0};`
- L761 _private member_ `TMap<const CClass*, SEffectDescriptor> _EffectDescriptorTable;` — We choose between these effects tables based on the UploadedAtFNVersion. If we end up versioning this further, we should consider some more expandable structure to put them all in.
- L762 _private member_ `TMap<const CClass*, SEffectDescriptor> _EffectDescriptorTable_Pre3100;`
- L764 _private member_ `TArray<const CClass*> _AllEffectClasses;`
- L765 _private member_ `TArray<SDecompositionMapping> _OrderedEffectDecompositionData;`
- L766 _private member_ `TMap<const CClass*, int32_t> _OrderedEffectDecompositionDataIndexFromClass;`
- L768 _private member_ `bool bEffectsTablePopulated{ false };`
- L769 _private prototype_ `void PopulateEffectDescriptorTable();`
- L770 _private prototype_ `void ValidateEffectDescriptorTable(const TMap<const CClass*, SEffectDescriptor>& DescriptorTable) const;`
- L771 _private prototype_ `CDefinition* FindDefinitionByVersePathInternal(CUTF8StringView VersePath) const;`
- L772 _private prototype_ `const TMap<const CClass*, SEffectDescriptor>& GetEffectDescriptorTableForVersion(uint32_t UploadedAtFNVersion) const;`
- L774 _private member_ `mutable TMap<SCachedEffectSetToEffectClassesKey, TArray<const CClass*>> _CachedEffectSetToEffectClasses;`
- L776 _private member_ `TMap<CSymbol, SSymbolDefinitionArray> _GlobalSymbolMap;`
- L780 _private member_ `const CTupleType* _ProfileDataType = nullptr;` — Caches of some profiling data structures
- L781 _private member_ `const CTupleType* _ProfileLocusType = nullptr;`

#### struct `uLang::CSemanticProgram::TCachedIntrinsicDefinition`  
`template<typename DefinitionType> struct TCachedIntrinsicDefinition`  
_L422-438_
- desc: Cached references to some attributes that are defined in code, but commonly interpreted by the compiler.
- L424 _public function_ `TCachedIntrinsicDefinition(CSemanticProgram& Program, CUTF8StringView Path) : _Program(Program), _Path(Path)`
- L425 _public function_ `DefinitionType* Get() const`
- L435 _private member_ `CSemanticProgram& _Program;`
- L436 _private member_ `CUTF8String _Path;`
- L437 _private member_ `mutable TOptional<DefinitionType*> _CachedValue;`

#### struct `uLang::CSemanticProgram::SExplicitTypeParam`  
`struct SExplicitTypeParam`  
_L636-641_
- L638 _public member_ `CDataDefinition* DataDefinition;`
- L639 _public member_ `CTypeVariable* TypeVariable;`
- L640 _public member_ `CTypeVariable* NegativeTypeVariable;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API VERSECOMPILER_API`
- L21 _namespace_ `namespace uLang`
- L63 _function_ `inline uint32_t GetTypeHash(const SCachedEffectSetToEffectClassesKey& Key)` (scope `uLang`)
- L278 _typedef_ `using SSymbolDefinitionArray = TArrayG<const CDefinition*, TInlineElementAllocator<1>>;` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticScope.h` (Public)


#### struct `uLang::SResolvedDefinition`  
`struct SResolvedDefinition`  
_L54-61_
- desc: Stores a resolved definition and the context that it was resolved from
- L56 _public member_ `CDefinition* _Definition;`
- L57 _public member_ `const CDataDefinition* _Context;`
- L59 _public function_ `SResolvedDefinition(CDefinition* Definition) : _Definition(Definition), _Context(nullptr)`
- L60 _public function_ `SResolvedDefinition(CDefinition* Definition, const CDataDefinition* Context) : _Definition(Definition), _Context(Context)`

#### enum `uLang::EPathMode`  
`enum class EPathMode : uint8_t`  
_L68-68_
- L68 _public enumerator_ `enum class EPathMode : uint8_t { Default, PrefixSeparator, PackageRelative, PackageRelativeWithRoot }; /** * A nested scope - program`
- L68 _public enumerator_ `enum class EPathMode : uint8_t { Default, PrefixSeparator, PackageRelative, PackageRelativeWithRoot }; /** * A nested scope - program`
- L68 _public enumerator_ `enum class EPathMode : uint8_t { Default, PrefixSeparator, PackageRelative, PackageRelativeWithRoot }; /** * A nested scope - program`
- L68 _public enumerator_ `enum class EPathMode : uint8_t { Default, PrefixSeparator, PackageRelative, PackageRelativeWithRoot }; /** * A nested scope - program`

#### class `uLang::CScope`  
`class CScope`  
_L73-238_
- desc: A nested scope - program, module or class
- L91 _public prototype_ `static const char* KindToCString(EKind Kind);`
- L93 _public function_ `CScope(EKind Kind, CScope* Parent, CSemanticProgram& Program) : _Kind(Kind), _Parent(Parent), _Program(Program)`
- L94 _public prototype_ `virtual ~CScope();`
- L97 _public prototype_ `CScope(const CScope&) = delete;` — Delete the generated move/copy constructors so that they don't require full definitions of the types referenced by TSRefArray.
- L98 _public prototype_ `CScope(CScope&&) = delete;`
- L100 _public prototype_ `virtual CSymbol GetScopeName() const = 0;`
- L101 _public function_ `virtual const CTypeBase* ScopeAsType() const`
- L102 _public function_ `virtual const CDefinition* ScopeAsDefinition() const`
- L104 _public function_ `virtual SAccessLevel GetDefaultDefinitionAccessLevel() const`
- L106 _public function_ `EKind GetKind() const`
- L107 _public function_ `CScope* GetParentScope() const`
- L108 _public prototype_ `CScope* GetScopeOfKind(EKind);`
- L109 _public prototype_ `const CScope* GetScopeOfKind(EKind) const;`
- L110 _public typedef_ `using EPathMode = uLang::EPathMode;`
- L111 _public prototype_ `void GetScopePath(uLang::CUTF8StringBuilder& OutBuilder, uLang::UTF8Char SeparatorChar = '.', EPathMode Mode = EPathMode::Default) const;`
- L112 _public prototype_ `CUTF8String GetScopePath(uLang::UTF8Char SeparatorChar = '.', EPathMode Mode = EPathMode::Default) const;`
- L113 _public prototype_ `const CModule* GetModule() const;`
- L114 _public prototype_ `CModule* GetModule();`
- L115 _public prototype_ `const CModulePart* GetModulePart() const;`
- L116 _public prototype_ `CModulePart* GetModulePart();`
- L117 _public prototype_ `CAstPackage* GetPackage() const;`
- L118 _public prototype_ `CAstCompilationUnit* GetCompilationUnit() const;`
- L119 _public prototype_ `const CSnippet* GetSnippet() const;`
- L120 _public prototype_ `CCaptureScope* GetCaptureScope();`
- L121 _public prototype_ `const CCaptureScope* GetCaptureScope() const;`
- L122 _public prototype_ `const TSPtr<CSymbolTable>& GetSymbols() const;`
- L123 _public function_ `CSemanticProgram& GetProgram() const`
- L126 _public prototype_ `const CScope& GetParametricTypeScope() const;` — If this is a parametric type, get the scope of those parameters; otherwise returns this scope.
- L129 _public prototype_ `const CLogicalScope& GetLogicalScope() const;` — Get the innermost logical scope that is or contains this scope.
- L130 _public function_ `CLogicalScope& GetLogicalScope()`
- L133 _public function_ `virtual const CLogicalScope* AsLogicalScopeNullable() const` — Iff this scope is a logical scope, return it a pointer to it. Otherwise, return null.
- L134 _public function_ `virtual CLogicalScope* AsLogicalScopeNullable()`
- L136 _public function_ `bool IsLogicalScope() const`
- L138 _public function_ `const CLogicalScope* GetEnclosingClassOrInterface() const`
- L139 _public prototype_ `CLogicalScope* GetEnclosingClassOrInterface();`
- L141 _public function_ `virtual CScope* GetNegativeScope() const`
- L144 _public prototype_ `bool IsSameOrChildOf(const CScope* Other) const;` — Check if this module is the same or a child of another
- L147 _public function_ `bool IsControlScope() const` — Determines if this is either a function body or a nested scope within a function body
- L150 _public prototype_ `bool IsInsideTypeScope() const;` — Determines if inside a type scope, ignoring control scope
- L153 _public function_ `bool IsModuleOrSnippet() const` — Determines if this is a module or snippet scope.
- L156 _public prototype_ `bool IsBuiltInScope() const;` — Determines if the definitions in this scope are built-in.
- L158 _public prototype_ `CModule& CreateModule(const CSymbol& ModuleName);`
- L159 _public prototype_ `CClassDefinition& CreateClass(const CSymbol& ClassName, CClass* Superclass = nullptr, TArray<CInterface*>&& SuperInterfaces = {}, EStructOrClass StructOrClass = EStructOrClass::Class);`
- L160 _public prototype_ `CEnumeration& CreateEnumeration(const CSymbol& EnumerationName);`
- L161 _public prototype_ `CInterface& CreateInterface(const CSymbol& InterfaceName, const TArray<CInterface*>& SuperInterfaces = {});`
- L162 _public prototype_ `TSRef<CFunction> CreateFunction(const CSymbol FunctionName);`
- L163 _public prototype_ `TSRef<CDataDefinition> CreateDataDefinition(const CSymbol VarName);`
- L164 _public prototype_ `TSRef<CDataDefinition> CreateDataDefinition(const CSymbol VarName, const CTypeBase* Type);`
- L165 _public prototype_ `TSRef<CTypeAlias> CreateTypeAlias(const CSymbol Name);`
- L166 _public prototype_ `TSRef<CTypeVariable> CreateTypeVariable(const CSymbol Name, const CTypeBase* NegativeType, const CTypeBase* PositiveType);`
- L167 _public prototype_ `TSRef<CModuleAlias> CreateModuleAlias(const CSymbol Name);`
- L168 _public prototype_ `TSRef<CScopedAccessLevelDefinition> CreateScopedAccessLevelDefinition(TOptional<CSymbol> ClassName);`
- L171 _public function_ `void AddUsingScope(const CLogicalScope* UsingScope)` — Using declarations
- L172 _public function_ `const TArray<const CLogicalScope*>& GetUsingScopes() const`
- L175 _public prototype_ `const CDataDefinition* AddUsingInstance(const CDataDefinition* UsingContext);` — Add a local context to infer from a using declaration - return nullptr if added and conflicting context if type/value domain was already previously added
- L176 _public function_ `const TArray<const CDataDefinition*>& GetUsingInstances() const`
- L178 _public prototype_ `static void ResolvedDefnsAppend(SResolvedDefinitionArray* ResolvedDefns, const SmallDefinitionArray& Definitions);`
- L179 _public prototype_ `static void ResolvedDefnsAppendWithContext(SResolvedDefinitionArray* ResolvedDefns, const SmallDefinitionArray& Definitions, const CDataDefinition* Context);`
- L182 _public prototype_ `SResolvedDefinitionArray ResolveDefinition(const CSymbol& Name, const SQualifier& Qualifier = SQualifier::Unknown(), const CAstPackage* ContextPackage = nullptr) const;` — Look for a definition in this scope and all parent scopes and aliases
- L184 _public prototype_ `TSRef<CControlScope> CreateNestedControlScope();`
- L186 _public prototype_ `TSRef<CCaptureControlScope> CreateNestedCaptureControlScope();`
- L188 _public function_ `const TSRefArray<CControlScope>& GetNestedControlScopes() const`
- L190 _public prototype_ `TSRef<CTypeScope> CreateNestedTypeScope();`
- L193 _public prototype_ `bool IsAuthoredByEpic() const;` — Determines whether this scope was authored by Epic
- L197 _public prototype_ `bool CanAccessEpicInternal() const;` — Determines whether this scope can access Epic-internal definitions. This differs from IsAuthoredByEpic by allowing packages with Scope=InternalUser to access epic-internal definitions.
- L199 _public member_ `bool _bIsParametricTypeScope = false;`
- L201 _public member_ `mutable uint64_t _NextUniqueSymbolId = 0;`
- L209 _protected prototype_ `bool CanAccess(const CDefinition& Definition, const SAccessLevel& DefinitionAccessLevel) const;` — Returns whether some definition is accessible from this scope. When checking accessibility, you probably want to use CDefinition::IsAccessibleFrom instead of this.
- L212 _protected member_ `EKind _Kind;` — If we are a program, module etc.
- L215 _protected member_ `CScope* _Parent;` — The enclosing scope for this scope
- L218 _protected member_ `CSemanticProgram& _Program;` — The semantic program these types belongs to
- L221 _protected member_ `TArray<const CLogicalScope*> _UsingScopes;` — `using` declarations referring to other scopes / modules
- L224 _protected member_ `TArray<const CDataDefinition*> _UsingInstances;` — `using` declarations referring to implied contexts / receivers
- L227 _protected member_ `TSRefArray<CControlScope> _NestedControlScopes;` — Nested control scopes
- L230 _protected member_ `TSRefArray<CTypeScope> _NestedTypeScopes;` — Nested type scopes
- L234 _private prototype_ `template <typename T> static T* GetScopeOfKind(T* This, EKind Kind);`
- L237 _private prototype_ `template <typename T, typename U> static T* GetCaptureScope(U* This);`

#### enum `uLang::CScope::EKind`  
`enum class EKind : uint8_t`  
_L76-89_
- L78 _public enumerator_ `Program`
- L79 _public enumerator_ `CompatConstraintRoot`
- L80 _public enumerator_ `Module`
- L81 _public enumerator_ `ModulePart`
- L82 _public enumerator_ `Snippet`
- L83 _public enumerator_ `Class`
- L84 _public enumerator_ `Function`
- L85 _public enumerator_ `ControlScope` — A nested scope within a function body
- L86 _public enumerator_ `Interface`
- L87 _public enumerator_ `Type`
- L88 _public enumerator_ `Enumeration`

#### class `uLang::CLogicalScope`  
`class CLogicalScope : public CScope`  
_L243-371_
- inherits: `CScope`
- desc: A scope that can contain definitions
- L247 _public function_ `CLogicalScope(EKind Kind, CScope* Parent, CSemanticProgram& Program) : CScope(Kind, Parent, Program)`
- L248 _public prototype_ `virtual ~CLogicalScope();`
- L251 _public prototype_ `CLogicalScope(const CLogicalScope&) = delete;` — Delete the generated move/copy constructors so that they don't require full definitions of the types referenced by TSRefArray.
- L252 _public prototype_ `CLogicalScope(CLogicalScope&&) = delete;`
- L255 _public prototype_ `EIterateResult IterateRecurseLogicalScopes(const TFunction<EVisitResult(const CLogicalScope&)>& Functor) const;` — Iterates through all the logical scopes nested inside this scope
- L256 _public prototype_ `EIterateResult IterateRecurseLogicalScopes(TFunction<EVisitResult(const CLogicalScope&)>&& Functor) const;`
- L258 _public function_ `const TArray<TSRef<CDefinition>>& GetDefinitions() const`
- L259 _public function_ `TMap<CSymbol, SmallDefinitionArray>& GetDefinitionNameMap()`
- L262 _public prototype_ `template<typename FilterClass> TFilteredDefinitionRange<FilterClass> GetDefinitionsOfKind() const;`
- L264 _public prototype_ `virtual SmallDefinitionArray FindDefinitions( const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const;`
- L271 _public function_ `SmallDefinitionArray FindDefinitions( const CSymbol& Name, EMemberOrigin Origin = EMemberOrigin::InheritedOrOriginal, const SQualifier& Qualifier = SQualifier::Unknown(), const CAstPackage* ContextPackage = nullptr) const`
- L281 _public prototype_ `virtual void ForAllDefinitions( EMemberOrigin Origin, const TFunction<void(const CDefinition&)>& Functor, CVisitSet& VisitSet) const;`
- L286 _public function_ `void ForAllDefinitions( EMemberOrigin Origin, const TFunction<void(const CDefinition&)>& Functor) const`
- L295 _public prototype_ `template<typename FilterClass> FilterClass* FindFirstDefinitionOfKind( const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const;`
- L303 _public function_ `template<typename FilterClass> FilterClass* FindFirstDefinitionOfKind( const CSymbol& Name, EMemberOrigin Origin = EMemberOrigin::InheritedOrOriginal, const SQualifier& Qualifier = SQualifier::Unknown(), const CAstPackage* ContextPackage = nullptr) const`
- L313 _public prototype_ `virtual void SetRevision(SemanticRevision Revision);`
- L314 _public function_ `SemanticRevision GetRevision() const`
- L318 _public function_ `bool TryMarkVisited(CVisitSet& VisitSet) const` — If this scope is in the given visit set, return false. Otherwise, add this scope to the visit set and return true.
- L324 _public function_ `int32_t AllocateNextDefinitionOrdinal()` — Allocates an ordinal for the next definition in this scope.
- L330 _public prototype_ `const CDefinition* FindOverrideFor(const CDefinition& Definition) const;` — Get the matching override definition in this class for the argument, if there is any
- L333 _public function_ `virtual const CLogicalScope* AsLogicalScopeNullable() const override` — CScope interface.
- L334 _public function_ `virtual CLogicalScope* AsLogicalScopeNullable() override`
- L336 _public prototype_ `SQualifier AsQualifier() const;`
- L340 _public prototype_ `void AddDefinitionToLogicalScope(TSRef<CDefinition>&& NewDefinition);`
- L342 _public prototype_ `bool HasVar() const;`
- L344 _public prototype_ `void InstantiateMembers( CLogicalScope& InstantiatedPositiveScope, CLogicalScope& InstantiatedNegativeScope, const CNormalType& InstantiatedType, const TArray<STypeVariableSubstitution>& Substitutions) const;`
- L350 _public prototype_ `void SetNegativeMemberTypes(CLogicalScope& InstantiatedNegativeScope) const;`
- L354 _protected member_ `SemanticRevision _CumulativeRevision = 1;` — When anything in this class (methods, data members etc.) or its subclasses was last modified/deleted
- L357 _protected member_ `CVisitKey _LastVisitKey;` — To make sure we don't visit the same scope twice during an iteration
- L361 _private member_ `TArray<TSRef<CDefinition>> _Definitions;` — All definitions in this scope.
- L365 _private member_ `TMap<CSymbol, SmallDefinitionArray> _DefinitionNameMap;` — These definition references depend on the _Definitions array to manage lifetimes: All the definitions mapped by name since that's how we often look them up
- L367 _private member_ `TArray<const CLogicalScope*> _LogicalSubScopes;` — A collection of the _Definitions that are also logical scopes
- L370 _private member_ `int32_t _NextDefinitionOrdinal{ 0 };` — The next ordinal to assign to definitions within this scope.
- L374 _function_ `template<typename FilterClass> TFilteredDefinitionRange<FilterClass> CLogicalScope::GetDefinitionsOfKind() const`
- L380 _function_ `template<typename FilterClass> FilterClass* CLogicalScope::FindFirstDefinitionOfKind(const CSymbol& Name, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API VERSECOMPILER_API`
- L22 _namespace_ `namespace uLang`
- L66 _typedef_ `using SResolvedDefinitionArray = TArrayG<SResolvedDefinition, TInlineElementAllocator<1>>;` (scope `uLang`) — An array of resolved definitions and their associated contexts

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SemanticTypes.h` (Public)


#### enum `uLang::ETypeKind`  
`enum class ETypeKind : uint8_t`  
_L91-96_
- L94 _public enumerator_ `VERSE_ENUM_SEMANTIC_TYPE_KINDS(VISIT_KIND) #undef VISIT_KIND`

#### enum `uLang::ETypeSyntaxPrecedence`  
`enum class ETypeSyntaxPrecedence : uint8_t`  
_L99-107_
- L101 _public enumerator_ `Min = 0`
- L102 _public enumerator_ `List = 0` — a,b or a;b
- L103 _public enumerator_ `Definition = 1` — a:=b or a:b
- L104 _public enumerator_ `Comparison = 2` — a<=b
- L105 _public enumerator_ `To = 3` — a->b
- L106 _public enumerator_ `Call = 4` — a()

#### enum `uLang::EComparability`  
`enum class EComparability : uint8_t`  
_L112-117_
- desc: Characterizes whether a type is comparable and hashable, just comparable, or incomparable. The comparable and hashable vs just comparable distinction is necessary as a temporary limitation of the FProperty-based implementation, which doesn't implement hashing for all the types it implements comparison for.
- L114 _public enumerator_ `Incomparable`
- L115 _public enumerator_ `Comparable`
- L116 _public enumerator_ `ComparableAndHashable`

#### enum `uLang::ETypeStringFlag`  
`enum class ETypeStringFlag : uint8_t`  
_L120-124_
- desc: See EFunctionStringFlag.
- L122 _public enumerator_ `Simple`
- L123 _public enumerator_ `Qualified`

#### enum `uLang::ETypeConstraintFlags`  
`enum class ETypeConstraintFlags : uint8_t`  
_L126-131_
- L128 _public enumerator_ `None = 0`
- L129 _public enumerator_ `Castable = 1 << 0`
- L130 _public enumerator_ `Concrete = 1 << 1`

#### class `uLang::CTypeBase`  
`class CTypeBase`  
_L137-227_
- desc: Base class for all types
- L140 _public function_ `CTypeBase(CSemanticProgram& Program): _Program(Program)`
- L141 _public prototype_ `virtual ~CTypeBase() = default;`
- L143 _public function_ `CSemanticProgram& GetProgram() const`
- L146 _public prototype_ `virtual const CNormalType& GetNormalType() const = 0;` — Normalizes generic types to head-normal types.
- L148 _public function_ `virtual CNamedType* AsNamedType()`
- L150 _public function_ `virtual const CNamedType* AsNamedType() const`
- L152 _public function_ `virtual CFlowType* AsFlowType()`
- L154 _public function_ `virtual const CFlowType* AsFlowType() const`
- L156 _public function_ `virtual const CAliasType* AsAliasType() const`
- L158 _public prototype_ `virtual bool CanBeCustomAccessorDataType() const = 0;`
- L160 _public function_ `virtual bool CanBePredictsVarDataType() const`
- L167 _public function_ `CUTF8String AsCode(ETypeSyntaxPrecedence OuterPrecedence = ETypeSyntaxPrecedence::Min, ETypeStringFlag Flag = ETypeStringFlag::Simple) const` — Converts this class into its source code string equivalent, for use in error messages. This is essentially a disassembly of the internal language data-structures into source code. @Notes: The code generated may not round-trip to an equivalent CTypeBase.
- L173 _public prototype_ `virtual CUTF8String AsCodeRecursive( ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const = 0;`
- L182 _public function_ `CUTF8String AsParamsCode(ETypeSyntaxPrecedence OuterPrecedence = ETypeSyntaxPrecedence::Min, ETypeStringFlag Flag = ETypeStringFlag::Simple) const` — As above, but if it's a tuple then doesn't write the enclosing parenthesis, and : before the type.
- L188 _public function_ `virtual CUTF8String AsParamsCode(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool WithColon, ETypeStringFlag Flag = ETypeStringFlag::Simple) const`
- L202 _public function_ `CUTF8String AsLinkableCode() const` — As above, but sacrifices readability to ensure that it will not collide with other CTypes.
- L210 _private member_ `CSemanticProgram& _Program;`
- L218 _private member_ `mutable TSet<CUniqueTupleTypeWithPointeeEquality> _TupleTypesStartingWithThisType;`
- L226 _private member_ `mutable TSet<CUniqueFunctionTypeWithPointeeEquality> _FunctionTypesWithThisParameterType;`
- L1570 _function_ `friend uint32_t GetTypeHash(const CUniqueTupleTypeWithPointeeEquality& TupleType)`
- L1609 _function_ `friend uint32_t GetTypeHash(const CUniqueFunctionTypeWithPointeeEquality& FunctionType)`

#### class `uLang::CNormalType`  
`class CNormalType : public CTypeBase`  
_L230-289_
- inherits: `CTypeBase`
- desc: A normal type: a head normal form of types where the head is not a parametric type instantiation.
- L233 _public function_ `CNormalType(ETypeKind Kind, CSemanticProgram& Program): CTypeBase(Program), _Kind(Kind)`
- L235 _public function_ `ETypeKind GetKind() const`
- L238 _public function_ `template<typename TType> TType& AsChecked()`
- L241 _public function_ `template<typename TType> TType const& AsChecked() const`
- L244 _public function_ `template<typename TType> bool IsA() const`
- L247 _public function_ `template<typename TType> TType* AsNullable()`
- L250 _public function_ `template<typename TType> TType const* AsNullable() const`
- L256 _public function_ `virtual const CTypeBase* GetReferenceValueType() const` — If this type is a CReferenceType, this gets the non-reference value type, otherwise returns itself
- L261 _public function_ `virtual const CTypeBase* GetInnerType() const` — Gets the innermost type of this type
- L264 _public function_ `virtual const CNominalType* AsNominalType() const` — @return `this` as a `CNominalType`, or `nullptr` if `this` is not a `CNominalType`
- L267 _public function_ `virtual EComparability GetComparability() const` — Returns whether this type is comparable for equality
- L270 _public prototype_ `virtual bool IsPersistable() const = 0;` — Returns whether this type is `persistable`
- L272 _public prototype_ `virtual bool IsExplicitlyCastable() const = 0;`
- L274 _public prototype_ `virtual bool IsExplicitlyConcrete() const = 0;`
- L279 _public prototype_ `SmallDefinitionArray FindInstanceMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage = nullptr) const;` — Look up a member in this type.
- L280 _public function_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const`
- L281 _public prototype_ `SmallDefinitionArray FindTypeMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier) const;`
- L282 _public function_ `virtual SmallDefinitionArray FindTypeMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, CVisitSet& VisitSet) const`
- L285 _public function_ `virtual const CNormalType& GetNormalType() const override` — CTypeBase interface.
- L288 _private member_ `const ETypeKind _Kind;`

#### class `uLang::CGlobalType`  
`template<ETypeKind Kind> class CGlobalType : public CNormalType`  
_L293-379_
- inherits: `CNormalType`
- desc: Global type: used for various kinds of types of which there are one per program: false, unit, void, any.
- L296 _public member_ `static const ETypeKind StaticTypeKind = Kind;`
- L299 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L317 _public function_ `virtual EComparability GetComparability() const override` — CNormalType interface.
- L338 _public function_ `virtual bool IsPersistable() const override`
- L348 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L353 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L358 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L368 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L376 _private function_ `CGlobalType(CSemanticProgram& Program): CNormalType(StaticTypeKind, Program)`

#### class `uLang::CTypeType`  
`class CTypeType : public CNormalType`  
_L394-471_
- inherits: `CNormalType`
- L397 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Type;`
- L399 _public function_ `CTypeType(CSemanticProgram& Program, const CTypeBase* NegativeType, const CTypeBase* PositiveType) : CNormalType(StaticTypeKind, Program) , _NegativeType(NegativeType) , _PositiveType(PositiveType)`
- L406 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;`
- L408 _public function_ `virtual SmallDefinitionArray FindInstanceMember( const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override`
- L418 _public function_ `const CTypeBase* NegativeType() const`
- L420 _public function_ `const CTypeBase* PositiveType() const`
- L422 _public function_ `bool IsPersistable() const override`
- L424 _public function_ `bool IsExplicitlyCastable() const override`
- L426 _public function_ `bool IsCastableSubtype() const`
- L428 _public function_ `bool IsExplicitlyConcrete() const override`
- L430 _public function_ `bool IsConcreteSubtype() const`
- L437 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L444 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L451 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L461 _public function_ `operator Key() const`
- L466 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L469 _private member_ `const CTypeBase* _NegativeType;`
- L470 _private member_ `const CTypeBase* _PositiveType;`

#### struct `uLang::CTypeType::Key`  
`struct Key`  
_L432-459_
- L434 _public member_ `const CTypeBase* NegativeType;`
- L435 _public member_ `const CTypeBase* PositiveType;`

#### class `uLang::CCastableType`  
`class CCastableType : public CNormalType`  
_L473-544_
- inherits: `CNormalType`
- L476 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Castable;`
- L478 _public function_ `CCastableType(CSemanticProgram& Program, const CTypeBase& SuperType) : CNormalType(StaticTypeKind, Program), _SuperType(&SuperType)`
- L483 _public function_ `virtual const CTypeBase* GetInnerType() const override`
- L488 _public function_ `const CTypeBase& SuperType() const`
- L498 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L503 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L508 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L514 _public function_ `operator Key() const`
- L516 _public function_ `virtual CUTF8String AsCodeRecursive( ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const`
- L525 _public function_ `virtual bool IsPersistable() const override`
- L527 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L529 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L531 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L533 _public function_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override`
- L537 _public function_ `virtual SmallDefinitionArray FindTypeMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, CVisitSet& VisitSet) const override`
- L543 _protected member_ `const CTypeBase* _SuperType;`

#### struct `uLang::CCastableType::Key`  
`struct Key`  
_L494-512_
- desc: Needed for map insertion
- L496 _public member_ `const CTypeBase* SuperType;`

#### class `uLang::CConcreteType`  
`class CConcreteType : public CNormalType`  
_L546-617_
- inherits: `CNormalType`
- L549 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Concrete;`
- L551 _public function_ `CConcreteType(CSemanticProgram& Program, const CTypeBase& SuperType) : CNormalType(StaticTypeKind, Program), _SuperType(&SuperType)`
- L556 _public function_ `virtual const CTypeBase* GetInnerType() const override`
- L561 _public function_ `const CTypeBase& SuperType() const`
- L571 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L576 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L581 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L587 _public function_ `operator Key() const`
- L589 _public function_ `virtual CUTF8String AsCodeRecursive( ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const`
- L598 _public function_ `virtual bool IsPersistable() const override`
- L600 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L602 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L604 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L606 _public function_ `virtual SmallDefinitionArray FindInstanceMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, const CAstPackage* ContextPackage, CVisitSet& VisitSet) const override`
- L610 _public function_ `virtual SmallDefinitionArray FindTypeMember(const CSymbol& MemberName, EMemberOrigin Origin, const SQualifier& Qualifier, CVisitSet& VisitSet) const override`
- L616 _protected member_ `const CTypeBase* _SuperType;`

#### struct `uLang::CConcreteType::Key`  
`struct Key`  
_L567-585_
- desc: Needed for map insertion
- L569 _public member_ `const CTypeBase* SuperType;`

#### class `uLang::CNominalType`  
`class CNominalType : public CNormalType`  
_L621-633_
- inherits: `CNormalType`
- desc: Class defining instance and class objects
- L624 _public function_ `CNominalType(ETypeKind Kind, CSemanticProgram& Program): CNormalType(Kind, Program)`
- L626 _public prototype_ `virtual const CDefinition* Definition() const = 0;`
- L629 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — CTypeBase interface.
- L632 _public function_ `virtual const CNominalType* AsNominalType() const override` — CNormalType interface.

#### class `uLang::CInvariantValueType`  
`class CInvariantValueType : public CNormalType`  
_L635-693_
- inherits: `CNormalType`
- L638 _public function_ `CInvariantValueType(ETypeKind Kind, CSemanticProgram& Program, const CTypeBase* NegativeValueType, const CTypeBase* PositiveValueType) : CNormalType(Kind, Program) , _NegativeValueType(NegativeValueType) , _PositiveValueType(PositiveValueType)`
- L645 _public function_ `const CTypeBase* NegativeValueType() const`
- L647 _public function_ `const CTypeBase* PositiveValueType() const`
- L650 _public function_ `virtual const CTypeBase* GetInnerType() const override` — CNormalType interface.
- L657 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L664 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L671 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L685 _public function_ `operator Key() const`
- L691 _protected member_ `const CTypeBase* _NegativeValueType;`
- L692 _protected member_ `const CTypeBase* _PositiveValueType;`

#### struct `uLang::CInvariantValueType::Key`  
`struct Key`  
_L652-683_
- L654 _public member_ `const CTypeBase* NegativeValueType;`
- L655 _public member_ `const CTypeBase* PositiveValueType;`

#### class `uLang::CPointerType`  
`class CPointerType : public CInvariantValueType`  
_L698-720_
- inherits: `CInvariantValueType`
- desc: Represents a pointer to mutable inner type.
- L701 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Pointer;`
- L703 _public prototype_ `CPointerType(CSemanticProgram&, const CTypeBase* NegativeValueType, const CTypeBase* PositiveValueType);`
- L706 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L713 _public function_ `virtual bool IsPersistable() const override`
- L715 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L717 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L719 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`

#### class `uLang::CReferenceType`  
`class CReferenceType : public CInvariantValueType`  
_L725-750_
- inherits: `CInvariantValueType`
- desc: Represents a reference to (possibly mutable) inner type.
- L728 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Reference;`
- L730 _public prototype_ `CReferenceType(CSemanticProgram&, const CTypeBase* NegativeValueType, const CTypeBase* PositiveValueType);`
- L733 _public function_ `virtual const CTypeBase* GetReferenceValueType() const override` — CNormalType interface.
- L736 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L743 _public function_ `virtual bool IsPersistable() const override`
- L745 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L747 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L749 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`

#### class `uLang::CValueType`  
`class CValueType : public CNormalType`  
_L755-768_
- inherits: `CNormalType`
- desc: Abstract type that has an additional sub-type representing a value (ex: List)
- L758 _public function_ `CValueType(ETypeKind Kind, CSemanticProgram& Program, const CTypeBase* ValueType) : CNormalType(Kind, Program), _ValueType(ValueType)`
- L761 _public function_ `virtual const CTypeBase* GetInnerType() const override` — CNormalType interface.
- L764 _public function_ `operator CTypeBase const* () const` — Needed for map insertion
- L767 _protected member_ `const CTypeBase* _ValueType;`

#### class `uLang::COptionType`  
`class COptionType : public CValueType`  
_L773-796_
- inherits: `CValueType`
- desc: Option type
- L776 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Option;`
- L778 _public prototype_ `COptionType(CSemanticProgram& Program, const CTypeBase* ValueType);`
- L780 _public function_ `const CTypeBase* GetValueType() const`
- L783 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L788 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L789 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L792 _public function_ `virtual EComparability GetComparability() const override` — CNormalType interface.
- L793 _public function_ `virtual bool IsPersistable() const override`
- L794 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L795 _public function_ `virtual bool IsExplicitlyConcrete() const override`

#### class `uLang::CArrayType`  
`class CArrayType : public CValueType`  
_L801-860_
- inherits: `CValueType`
- desc: A parametric type of arrays with a specific element type: []t where t:type
- L804 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Array;`
- L806 _public function_ `CArrayType(CSemanticProgram& Program, const CTypeBase* ElementType) : CValueType(ETypeKind::Array, Program, ElementType)`
- L810 _public function_ `const CTypeBase* GetElementType() const`
- L813 _public function_ `bool IsStringType() const` — Returns whether the type is string, i.e. []char8.
- L819 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L823 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L824 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L827 _public function_ `virtual EComparability GetComparability() const override` — CNormalType interface.
- L846 _public function_ `virtual bool IsPersistable() const override`
- L851 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L856 _public function_ `virtual bool IsExplicitlyConcrete() const override`

#### class `uLang::CGeneratorType`  
`class CGeneratorType : public CValueType`  
_L865-889_
- inherits: `CValueType`
- desc: A parametric type of generators with a specific element type: generator(t) where t:type
- L868 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Generator;`
- L870 _public function_ `CGeneratorType(CSemanticProgram& Program, const CTypeBase* ElementType) : CValueType(ETypeKind::Generator, Program, ElementType)`
- L874 _public function_ `const CTypeBase* GetElementType() const`
- L877 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L882 _public function_ `virtual bool IsPersistable() const override`
- L884 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L886 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L888 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`

#### class `uLang::CMapType`  
`class CMapType : public CNormalType`  
_L894-1020_
- inherits: `CNormalType`
- desc: A parametric type of maps with specific key and value types: [t]u where t&u:type
- L897 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Map;`
- L899 _public function_ `CMapType(CSemanticProgram& Program, const CTypeBase& KeyType, const CTypeBase& ValueType, bool bWeak) : CNormalType(ETypeKind::Map, Program) , _KeyType(&KeyType) , _ValueType(&ValueType) , _bWeak(bWeak)`
- L907 _public function_ `const CTypeBase* GetKeyType() const`
- L912 _public function_ `const CTypeBase* GetValueType() const`
- L917 _public function_ `bool IsWeak() const`
- L922 _public function_ `virtual EComparability GetComparability() const override`
- L937 _public function_ `virtual bool IsPersistable() const override`
- L945 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L950 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L956 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L971 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L979 _public function_ `friend bool operator==(const SKey& Left, const SKey& Right)`
- L984 _public function_ `friend bool operator!=(const SKey& Left, const SKey& Right)`
- L989 _public function_ `friend bool operator<(const SKey& Left, const SKey& Right)`
- L1011 _public function_ `operator SKey() const`
- L1017 _private member_ `const CTypeBase* _KeyType;`
- L1018 _private member_ `const CTypeBase* _ValueType;`
- L1019 _private member_ `bool _bWeak;`

#### struct `uLang::CMapType::SKey`  
`struct SKey`  
_L973-1009_
- L975 _public member_ `const CTypeBase* _KeyType;`
- L976 _public member_ `const CTypeBase* _ValueType;`
- L977 _public member_ `bool _bWeak;`

#### class `uLang::CTupleType`  
`class CTupleType : public CNormalType`  
_L1022-1066_
- inherits: `CNormalType`
- L1025 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Tuple;`
- L1027 _public typedef_ `using ElementArray = TArrayG<const CTypeBase*, TInlineElementAllocator<4>>;`
- L1029 _public function_ `CTupleType(CSemanticProgram& Program, ElementArray&& Elements, int32_t FirstNamedIndex) : CNormalType(ETypeKind::Tuple, Program) , _Elements(Move(Elements)) , _FirstNamedIndex(FirstNamedIndex)`
- L1035 _public function_ `bool TryMarkVisited(CVisitSet& VisitSet) const`
- L1037 _public function_ `int32_t Num() const`
- L1038 _public function_ `const CTypeBase* operator[](int32_t Index) const`
- L1039 _public function_ `const ElementArray& GetElements() const`
- L1040 _public prototype_ `ElementArray ElementsWithSortedNames() const;`
- L1042 _public prototype_ `const CNamedType* FindNamedType(CSymbol Name) const;`
- L1044 _public function_ `int32_t GetFirstNamedIndex() const`
- L1045 _public function_ `int32_t NumNonNamedElements() const`
- L1048 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — CTypeBase interface.
- L1049 _public prototype_ `virtual CUTF8String AsParamsCode(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool WithColon, ETypeStringFlag Flag) const override;`
- L1050 _public prototype_ `CUTF8String AsParamsCode(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool WithColon, bool bLinkable, ETypeStringFlag Flag) const;`
- L1051 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1054 _public prototype_ `virtual EComparability GetComparability() const override;` — CNormalType interface.
- L1055 _public prototype_ `virtual bool IsPersistable() const override;`
- L1056 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L1057 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L1060 _private member_ `ElementArray _Elements;`
- L1062 _private member_ `int32_t _FirstNamedIndex;`
- L1065 _private member_ `CVisitKey _LastVisitKey;` — Used to detect reentrant visits to a tuple.

#### class `uLang::CFunctionType`  
`class CFunctionType : public CNormalType`  
_L1068-1152_
- inherits: `CNormalType`
- L1071 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Function;`
- L1073 _public typedef_ `using ParamTypes = TRangeView<CTypeBase const* const*, CTypeBase const* const*>;`
- L1075 _public function_ `CFunctionType( CSemanticProgram& Program, const CTypeBase& ParamsType, const CTypeBase& ReturnType, const SEffectSet Effects, bool bClosed, TArray<const CTypeVariable*>&& TypeVariables = {}, bool bImplicitlySpecialized = false) : CNormalType(ETypeKind::Function, Program) , _ParamsType(&ParamsType) , _ReturnType(ReturnType) , _Effects(Effects) , _bClosed(bClosed) , _TypeVariables(Move(TypeVariables)) , _bImplicitlySpecialized(bImplicitlySpecialized)`
- L1097 _public function_ `const CTypeBase& GetParamsType() const`
- L1098 _public function_ `const CTypeBase& GetReturnType() const`
- L1099 _public function_ `SEffectSet GetEffects() const`
- L1100 _public function_ `bool IsClosed() const`
- L1101 _public function_ `bool ImplicitlySpecialized() const`
- L1102 _public function_ `const TArray<const CTypeVariable*>& GetTypeVariables() const`
- L1104 _public prototype_ `static const CTypeBase* GetOrCreateParamType(CSemanticProgram&, CTupleType::ElementArray&& ParamTypes);`
- L1106 _public prototype_ `static const CTypeBase* GetOrCreateParamType(CSemanticProgram&, CTupleType::ElementArray&& ParamTypes, int32_t FirstNamedIndex);`
- L1108 _public function_ `static ParamTypes AsParamTypes(CTypeBase const* const& Type)`
- L1117 _public function_ `ParamTypes GetParamTypes() const`
- L1122 _public prototype_ `void BuildTypeVariableCode(CUTF8StringBuilder& Builder, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const;`
- L1123 _public function_ `void BuildTypeVariableCode(CUTF8StringBuilder& Builder, ETypeStringFlag Flag = ETypeStringFlag::Simple) const`
- L1129 _public prototype_ `void BuildEffectAttributeCode(CUTF8StringBuilder& Builder) const;`
- L1130 _public prototype_ `void BuildParameterBlockCode(CUTF8StringBuilder& Builder, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const;`
- L1133 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — CTypeBase interface.
- L1135 _public function_ `virtual bool IsPersistable() const override`
- L1137 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L1139 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L1141 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1143 _public prototype_ `bool CanBeCalledFromPredicts() const;`
- L1146 _private member_ `const CTypeBase* _ParamsType;`
- L1147 _private member_ `const CTypeBase& _ReturnType;`
- L1148 _private member_ `SEffectSet _Effects;`
- L1149 _private member_ `bool _bClosed;`
- L1150 _private member_ `TArray<const CTypeVariable*> _TypeVariables;`
- L1151 _private member_ `bool _bImplicitlySpecialized;`

#### enum `uLang::ETypePolarity`  
`enum class ETypePolarity : char`  
_L1154-1154_
- L1154 _public enumerator_ `enum class ETypePolarity : char { Negative, Positive }; inline ETypePolarity FlipPolarity(ETypePolarity Polarity) { switch (Polarity) { case ETypePolarity::Negative: return ETypePolarity::Positive; case ETypePolarity::Positive: return ETypePolarity::Negative;`
- L1154 _public enumerator_ `enum class ETypePolarity : char { Negative, Positive }; inline ETypePolarity FlipPolarity(ETypePolarity Polarity) { switch (Polarity) { case ETypePolarity::Negative: return ETypePolarity::Positive; case ETypePolarity::Positive: return ETypePolarity::Negative;`

#### class `uLang::CFlowType`  
`class CFlowType : public CTypeBase`  
_L1166-1205_
- inherits: `CTypeBase`
- L1169 _public function_ `CFlowType(CSemanticProgram& Program, ETypePolarity Polarity, const CTypeBase* Child) : CTypeBase(Program) , _Polarity(Polarity) , _Child(Child)`
- L1176 _public prototype_ `ETypePolarity Polarity() const;`
- L1178 _public prototype_ `const CTypeBase* GetChild() const;`
- L1180 _public prototype_ `void SetChild(const CTypeBase*) const;`
- L1182 _public function_ `TSet<const CFlowType*>& FlowEdges() const`
- L1187 _public prototype_ `void AddFlowEdge(const CFlowType*) const;`
- L1189 _public prototype_ `void EmptyFlowEdges() const;`
- L1191 _public prototype_ `virtual const CNormalType& GetNormalType() const override;`
- L1193 _public function_ `virtual CFlowType* AsFlowType() override`
- L1195 _public function_ `virtual const CFlowType* AsFlowType() const override`
- L1197 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;`
- L1199 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1202 _private member_ `ETypePolarity _Polarity;`
- L1203 _private member_ `mutable const CTypeBase* _Child;`
- L1204 _private member_ `mutable TSet<const CFlowType*> _FlowEdges;`

#### struct `uLang::STypeVariableSubstitution`  
`struct STypeVariableSubstitution`  
_L1207-1250_
- L1209 _public member_ `const CTypeVariable* _TypeVariable;`
- L1210 _public member_ `const CTypeBase* _NegativeType;`
- L1211 _public member_ `const CTypeBase* _PositiveType;`
- L1213 _public function_ `STypeVariableSubstitution(const CTypeVariable* TypeVariable, const CTypeBase* NegativeType, const CTypeBase* PositiveType) : _TypeVariable(TypeVariable) , _NegativeType(NegativeType) , _PositiveType(PositiveType)`

#### struct `uLang::SInstantiatedTypeVariable`  
`struct SInstantiatedTypeVariable`  
_L1252-1269_
- L1254 _public member_ `const CTypeBase* _NegativeType;`
- L1255 _public member_ `const CTypeBase* _PositiveType;`
- L1257 _public function_ `SInstantiatedTypeVariable(const CTypeBase* NegativeType, const CTypeBase* PositiveType) : _NegativeType(NegativeType) , _PositiveType(PositiveType)`

#### class `uLang::CInstantiatedType`  
`class CInstantiatedType : public CTypeBase`  
_L1273-1312_
- inherits: `CTypeBase`
- desc: Type representing an instantiation of some underlying type.  This is used to lazily evaluate expensive type instantiation.
- L1275 _private function_ `virtual const CNormalType& GetNormalType() const override`
- L1285 _private function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L1291 _protected function_ `CInstantiatedType(CSemanticProgram& Program, ETypePolarity Polarity, TArray<STypeVariableSubstitution> Arguments) : CTypeBase(Program) , _Polarity(Polarity) , _Substitutions(Move(Arguments))`
- L1298 _protected prototype_ `virtual ~CInstantiatedType() = default;`
- L1300 _protected prototype_ `virtual const CNormalType& CreateNormalType() const = 0;`
- L1302 _protected function_ `ETypePolarity GetPolarity() const`
- L1304 _protected function_ `const TArray<STypeVariableSubstitution>& GetSubstitutions() const`
- L1307 _private member_ `ETypePolarity _Polarity;`
- L1309 _private member_ `TArray<STypeVariableSubstitution> _Substitutions;`
- L1311 _private member_ `mutable const CNormalType* _NormalType = nullptr;`

#### class `uLang::CNamedType`  
`class CNamedType : public CValueType`  
_L1314-1400_
- inherits: `CValueType`
- L1317 _public member_ `static constexpr ETypeKind StaticTypeKind = ETypeKind::Named;`
- L1319 _public function_ `CNamedType(CSemanticProgram& Program, CSymbol Name, const CTypeBase* ValueType, bool HasDefault) : CValueType(ETypeKind::Named, Program, ValueType) , _Name(Name) , _HasValue(HasDefault)`
- L1326 _public function_ `CSymbol GetName() const`
- L1328 _public function_ `const CTypeBase* GetValueType() const`
- L1330 _public function_ `bool HasValue() const`
- L1332 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;`
- L1334 _public prototype_ `const CTupleType& ToTupleType() const;`
- L1336 _public function_ `virtual CNamedType* AsNamedType() override`
- L1338 _public function_ `virtual const CNamedType* AsNamedType() const override`
- L1346 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L1354 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L1362 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L1384 _public function_ `operator Key() const`
- L1389 _public function_ `virtual bool IsPersistable() const override`
- L1391 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L1393 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L1395 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1398 _private member_ `CSymbol _Name;`
- L1399 _private member_ `bool _HasValue;`

#### struct `uLang::CNamedType::Key`  
`struct Key`  
_L1340-1382_
- L1342 _public member_ `CSymbol Name;`
- L1343 _public member_ `const CTypeBase* ValueType;`
- L1344 _public member_ `bool HasValue;`

#### class `uLang::CIntType`  
`class CIntType : public CNormalType`  
_L1402-1470_
- inherits: `CNormalType`
- L1405 _public member_ `static constexpr ETypeKind StaticTypeKind = ETypeKind::Int;`
- L1407 _public function_ `CIntType(CSemanticProgram& Program, const FIntOrNegativeInfinity& Min, const FIntOrPositiveInfinity& Max) : CNormalType(StaticTypeKind, Program) , _MinInclusive(Min) , _MaxInclusive(Max)`
- L1414 _public function_ `const FIntOrNegativeInfinity& GetMin() const`
- L1415 _public function_ `const FIntOrPositiveInfinity& GetMax() const`
- L1417 _public function_ `bool IsInhabitable() const`
- L1419 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;`
- L1421 _public function_ `virtual EComparability GetComparability() const override`
- L1423 _public function_ `virtual bool IsPersistable() const override`
- L1424 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L1425 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L1427 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1428 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L1435 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L1441 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L1447 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L1462 _public function_ `operator Key() const`
- L1468 _private member_ `FIntOrNegativeInfinity _MinInclusive;`
- L1469 _private member_ `FIntOrPositiveInfinity _MaxInclusive;`

#### struct `uLang::CIntType::Key`  
`struct Key final`  
_L1430-1460_
- L1432 _public member_ `const FIntOrNegativeInfinity& _MinInclusive;`
- L1433 _public member_ `const FIntOrPositiveInfinity& _MaxInclusive;`

#### class `uLang::CFloatType`  
`class CFloatType : public CNormalType`  
_L1474-1549_
- inherits: `CNormalType`
- desc: the float type is a special form of CFloatType where _MaxInclusive is NaN. The only other way NaN can be encoded is for the NaN literal intrinsic. Given these constraints on NaN, we simpify our implementation by turning all doubles into a total order via CMath::FloatRanking.
- L1477 _public member_ `static constexpr ETypeKind StaticTypeKind = ETypeKind::Float;`
- L1479 _public function_ `CFloatType(CSemanticProgram& Program, double Min, double Max, int64_t MinRanking, int64_t MaxRanking) : CNormalType(StaticTypeKind, Program) , _MinInclusive(Min) , _MaxInclusive(Max) , _MinRanking(MinRanking) , _MaxRanking(MaxRanking)`
- L1488 _public function_ `double GetMin() const`
- L1489 _public function_ `double GetMax() const`
- L1490 _public function_ `int64_t MinRanking() const`
- L1491 _public function_ `int64_t MaxRanking() const`
- L1493 _public function_ `bool IsInhabitable() const`
- L1494 _public function_ `bool IsIntrinsicFloatType() const`
- L1497 _public prototype_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override;` — The only reason we preserve the "original" doubles is for AsCode.
- L1499 _public function_ `virtual EComparability GetComparability() const override`
- L1500 _public function_ `virtual bool IsPersistable() const override`
- L1501 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L1502 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L1504 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L1505 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L1512 _public function_ `friend bool operator==(const Key& Left, const Key& Right)`
- L1518 _public function_ `friend bool operator!=(const Key& Left, const Key& Right)`
- L1524 _public function_ `friend bool operator<(const Key& Left, const Key& Right)`
- L1539 _public function_ `operator Key() const`
- L1545 _private member_ `double _MinInclusive;`
- L1546 _private member_ `double _MaxInclusive;`
- L1547 _private member_ `int64_t _MinRanking;`
- L1548 _private member_ `int64_t _MaxRanking;`

#### struct `uLang::CFloatType::Key`  
`struct Key final`  
_L1507-1537_
- L1509 _public member_ `int64_t _MinRanking;`
- L1510 _public member_ `int64_t _MaxRanking;`

#### struct `uLang::CTypeBase::CUniqueTupleTypeWithPointeeEquality`  
`struct CTypeBase::CUniqueTupleTypeWithPointeeEquality final`  
_L1551-1584_
- L1554 _public function_ `template<typename... CtorArgsType> CUniqueTupleTypeWithPointeeEquality(CtorArgsType&&... CtorArgs) : Payload(TUPtr<CTupleType>::New(uLang::ForwardArg<CtorArgsType>(CtorArgs)...))`
- L1558 _public function_ `operator CTupleType& () const`
- L1563 _public function_ `bool operator==(const CUniqueTupleTypeWithPointeeEquality& Other) const`
- L1583 _private member_ `TUPtr<CTupleType> Payload;`

#### struct `uLang::CTypeBase::CUniqueFunctionTypeWithPointeeEquality`  
`struct CTypeBase::CUniqueFunctionTypeWithPointeeEquality final`  
_L1586-1632_
- L1589 _public function_ `template<typename... CtorArgsType> CUniqueFunctionTypeWithPointeeEquality(CtorArgsType&&... CtorArgs) : Payload(TUPtr<CFunctionType>::New(uLang::ForwardArg<CtorArgsType>(CtorArgs)...))`
- L1593 _public function_ `operator CFunctionType& () const`
- L1598 _public function_ `bool operator==(const CUniqueFunctionTypeWithPointeeEquality& Other) const`
- L1631 _private member_ `TUPtr<CFunctionType> Payload;`

#### struct `uLang::TPair`  
`template <typename T, typename U> struct TPair`  
_L1635-1644_
- L1637 _public member_ `T First;`
- L1638 _public member_ `U Second;`

#### struct `uLang::STypeVariablePolarity`  
`struct STypeVariablePolarity`  
_L1646-1663_
- L1648 _public member_ `const CTypeVariable* TypeVariable;`
- L1649 _public member_ `ETypePolarity Polarity;`

#### struct `uLang::SNormalTypePolarity`  
`struct SNormalTypePolarity`  
_L1667-1676_
- L1669 _public member_ `const CNormalType* NormalType;`
- L1670 _public member_ `const ETypePolarity Polarity;`

#### enum `uLang::SemanticTypeUtils::EIsEditable`  
`enum class EIsEditable`  
_L1788-1796_
- desc: Returns whether a type can be used with @editable. An enum is used instead of a bool to make it possible to produce a more informative error message.
- L1790 _public enumerator_ `Yes`
- L1791 _public enumerator_ `NotEditableType`
- L1792 _public enumerator_ `MissingConcrete`
- L1793 _public enumerator_ `CastableTypesNotEditable`
- L1795 _public enumerator_ `ClassifiableSubsetParametricArgumentInvalid` — @HACK: corresponds to hack in SemanticTypeUtils::IsEditableClassType

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API VERSECOMPILER_API`
- L25 _namespace_ `namespace uLang`
- L56 _macro_ `#define VERSE_ENUM_SEMANTIC_TYPE_KINDS(v) \` — NOTE: (YiLiangSiew) Currently, Visual Verse relies on the numerical values of these enumerations. If you change this, be sure to update `BaseVisualVerseSettings.ini` as well. Ensure to update uLangToolchainDependencies.natvis if the numerical values of these enumerations are changed.
- L93 _macro_ `#define VISIT_KIND(Name, CppType) Name,`
- L97 _prototype_ `const char* TypeKindAsCString(ETypeKind Type);` (scope `uLang`)
- L132 _prototype_ `ULANG_ENUM_BIT_FLAGS(ETypeConstraintFlags, inline);` (scope `uLang`)
- L134 _prototype_ `const char* GetConstraintTypeAsCString(ETypeConstraintFlags TypeConstraints, bool bIsSubtype);` (scope `uLang`)
- L381 _typedef_ `using CFalseType = CGlobalType<ETypeKind::False>;` (scope `uLang`)
- L382 _typedef_ `using CTrueType = CGlobalType<ETypeKind::True>;` (scope `uLang`)
- L383 _typedef_ `using CVoidType = CGlobalType<ETypeKind::Void>;` (scope `uLang`)
- L384 _typedef_ `using CAnyType = CGlobalType<ETypeKind::Any>;` (scope `uLang`)
- L385 _typedef_ `using CComparableType = CGlobalType<ETypeKind::Comparable>;` (scope `uLang`)
- L386 _typedef_ `using CLogicType = CGlobalType<ETypeKind::Logic>;` (scope `uLang`)
- L387 _typedef_ `using CRationalType = CGlobalType<ETypeKind::Rational>;` (scope `uLang`)
- L388 _typedef_ `using CChar8Type = CGlobalType<ETypeKind::Char8>;` (scope `uLang`)
- L389 _typedef_ `using CChar32Type = CGlobalType<ETypeKind::Char32>;` (scope `uLang`)
- L390 _typedef_ `using CPathType = CGlobalType<ETypeKind::Path>;` (scope `uLang`)
- L391 _typedef_ `using CRangeType = CGlobalType<ETypeKind::Range>;` (scope `uLang`)
- L392 _typedef_ `using CPersistableType = CGlobalType<ETypeKind::Persistable>;` (scope `uLang`)
- L1156 _function_ `inline ETypePolarity FlipPolarity(ETypePolarity Polarity)` (scope `uLang`)
- L1220 _function_ `friend bool operator==(const STypeVariableSubstitution& Left, const STypeVariableSubstitution& Right)` (scope `uLang`)
- L1228 _function_ `friend bool operator<(const STypeVariableSubstitution& Left, const STypeVariableSubstitution& Right)` (scope `uLang`)
- L1263 _function_ `friend bool operator==(const SInstantiatedTypeVariable& Left, const SInstantiatedTypeVariable& Right)` (scope `uLang`)
- L1640 _function_ `friend bool operator==(const TPair& Left, const TPair& Right)` (scope `uLang`)
- L1651 _function_ `friend bool operator<(const STypeVariablePolarity& Left, const STypeVariablePolarity& Right)` (scope `uLang`)
- L1665 _typedef_ `using STypeVariablePolarities = TArray<STypeVariablePolarity>;` (scope `uLang`)
- L1672 _function_ `friend bool operator==(const SNormalTypePolarity& Left, const SNormalTypePolarity& Right)` (scope `uLang`)
- L1681 _namespace_ `namespace SemanticTypeUtils` (scope `uLang`)
- L1683 _prototype_ `const CClass* AsSingleClass(const CNormalType& NegativeType, const CNormalType& PositiveType);` (scope `uLang::SemanticTypeUtils`)
- L1685 _prototype_ `const CInterface* AsSingleInterface(const CNormalType& NegativeType, const CNormalType& PositiveType);` (scope `uLang::SemanticTypeUtils`)
- L1687 _prototype_ `TArray<STypeVariableSubstitution> Instantiate(const TArray<const CTypeVariable*>& TypeVariables, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`)
- L1689 _prototype_ `const CTypeBase* Substitute(const CTypeBase&, ETypePolarity Polarity, const TArray<STypeVariableSubstitution>& InstTypeVariables);` (scope `uLang::SemanticTypeUtils`)
- L1691 _prototype_ `const CFunctionType* Instantiate(const CFunctionType* FunctionType, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`)
- L1696 _prototype_ `const CTypeBase& Canonicalize(const CTypeBase&);` (scope `uLang::SemanticTypeUtils`) — Replace all types with equivalent representations with a single canonical type - the type used when emitting code.  In particular, type variables are erased.
- L1698 _prototype_ `const CTypeBase& Canonicalize(const CTypeBase&, ETypePolarity);` (scope `uLang::SemanticTypeUtils`)
- L1700 _prototype_ `const CFunctionType& Canonicalize(const CFunctionType&);` (scope `uLang::SemanticTypeUtils`)
- L1702 _prototype_ `const CFunctionType& Canonicalize(const CFunctionType&, ETypePolarity);` (scope `uLang::SemanticTypeUtils`)
- L1704 _prototype_ `const CTupleType& Canonicalize(const CTupleType&);` (scope `uLang::SemanticTypeUtils`)
- L1706 _prototype_ `const CTupleType& Canonicalize(const CTupleType&, ETypePolarity);` (scope `uLang::SemanticTypeUtils`)
- L1708 _prototype_ `const CTypeBase& AsPolarity(const CTypeBase&, const TArray<SInstantiatedTypeVariable>&, ETypePolarity);` (scope `uLang::SemanticTypeUtils`)
- L1709 _prototype_ `const CTypeBase& AsPositive(const CTypeBase&, const TArray<SInstantiatedTypeVariable>&);` (scope `uLang::SemanticTypeUtils`)
- L1710 _prototype_ `const CTypeBase& AsNegative(const CTypeBase&, const TArray<SInstantiatedTypeVariable>&);` (scope `uLang::SemanticTypeUtils`)
- L1713 _prototype_ `bool Constrain(const CTypeBase* PositiveType1, const CTypeBase* NegativeType2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Constrain `PositiveType1` to be a subtype of `NegativeType2`
- L1716 _prototype_ `bool IsSubtype(const CTypeBase* PositiveType1, const CTypeBase* PositiveType2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Determine if `PositiveType1` is a subtype of `PositiveType2`
- L1719 _prototype_ `bool IsEquivalent(const CTypeBase* PositiveType1, const CTypeBase* PositiveType2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Determine if `PositiveType1` is equivalent to `PositiveType2`
- L1722 _prototype_ `bool Matches(const CTypeBase* PositiveType1, const CTypeBase* NegativeType2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Determine if argument `PositiveType1` is a match for parameter `NegativeType2`
- L1724 _prototype_ `const CTypeBase& SkipIdentityFlowType(const CFlowType&, ETypePolarity, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`)
- L1726 _prototype_ `const CTypeBase& SkipIdentityFlowType(const CTypeBase&, ETypePolarity, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`)
- L1728 _prototype_ `const CTypeBase& SkipEmptyFlowType(const CTypeBase&);` (scope `uLang::SemanticTypeUtils`)
- L1731 _prototype_ `const CTypeBase* Join(const CTypeBase* Type1, const CTypeBase* Type2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Compute the join of Type1 and Type2: the "least" type that contains all values contained by either Type1 or Type2.
- L1734 _prototype_ `const CTypeBase* Meet(const CTypeBase* Type1, const CTypeBase* Type2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Compute the meet of Type1 and Type2: the "greatest" type that contains only values contained by both Type1 and Type2.
- L1737 _prototype_ `bool AreDomainsDistinct(const CTypeBase* DomainType1, const CTypeBase* DomainType2, const uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Determine whether there two types are distinct; i.e. that there are no values that are members of both types.
- L1739 _prototype_ `bool IsUnknownType(const CTypeBase* Type);` (scope `uLang::SemanticTypeUtils`)
- L1741 _prototype_ `bool IsAttributeType(const CTypeBase* Type);` (scope `uLang::SemanticTypeUtils`)
- L1743 _prototype_ `void ForEachType( const CTypeBase*, ETypePolarity, const TFunction<void(const CTypeBase*, ETypePolarity)>&);` (scope `uLang::SemanticTypeUtils`)
- L1747 _prototype_ `void ForEachTypeRecursive( TArray<TPair<const CTypeBase*, ETypePolarity>>& Visited, const CTypeBase*, ETypePolarity, const TFunction<void(const CTypeBase*, ETypePolarity)>&);` (scope `uLang::SemanticTypeUtils`)
- L1752 _prototype_ `void ForEachTypeRecursive( const CTypeBase*, ETypePolarity, const TFunction<void(const CTypeBase*, ETypePolarity)>&);` (scope `uLang::SemanticTypeUtils`)
- L1756 _prototype_ `void VisitAllDefinitions(const CTypeBase* Type, const CAstPackage* VisitorPackage, const TFunction<void(const CDefinition&,const CSymbol&)>& Functor);` (scope `uLang::SemanticTypeUtils`)
- L1761 _prototype_ `void ForEachDataType(const CTypeBase*, const TFunction<void(const CTypeBase*)>&);` (scope `uLang::SemanticTypeUtils`) — Apply a function to each immediately possibly contained value's type. Note for `CFunctionType`, the function is not applied, as values of a given function type do not contain parameter or result values.
- L1765 _prototype_ `void ForEachDataTypeRecursive(const CTypeBase*, const TFunction<void(const CTypeBase*)>&);` (scope `uLang::SemanticTypeUtils`) — `ForEachDataType`, but recursive, and depth-first, top-down, including the immediately passed type.
- L1768 _function_ `inline bool IsStringType(const CNormalType& NormalType)` (scope `uLang::SemanticTypeUtils`) — Returns whether the type is string, i.e. []char8.
- L1775 _prototype_ `bool IsMessageType(const CTypeBase*, uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Returns whether the type is a localizable message type
- L1778 _prototype_ `bool IsAgentTypeExclusive(const CTypeBase* Type);` (scope `uLang::SemanticTypeUtils`) — Returns whether the type is agent
- L1781 _prototype_ `bool IsLeaderboardType(const CTypeBase*, uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Returns whether the type is a leaderboard type
- L1784 _prototype_ `bool IsEntitlementType(const CTypeBase*, uint32_t UploadedAtFnVersion);` (scope `uLang::SemanticTypeUtils`) — Returns whether the type is an entitlement type
- L1797 _prototype_ `const char* IsEditableToCMessage(EIsEditable IsEditable);` (scope `uLang::SemanticTypeUtils`)
- L1798 _prototype_ `EIsEditable IsEditableType(const uLang::CTypeBase* Type, const CAstPackage* ContextPackage);` (scope `uLang::SemanticTypeUtils`)
- L1799 _prototype_ `EIsEditable IsEditableClassType(const uLang::CTypeBase* Type);` (scope `uLang::SemanticTypeUtils`)
- L1801 _prototype_ `const CTypeBase* RemovePointer(const CTypeBase* Type , ETypePolarity Polarity);` (scope `uLang::SemanticTypeUtils`)
- L1802 _prototype_ `const CTypeBase* RemoveReference(const CTypeBase* Type , ETypePolarity Polarity);` (scope `uLang::SemanticTypeUtils`)
- L1803 _prototype_ `const CTypeBase& StripCastableAndConcrete(const CTypeBase&, ETypeConstraintFlags&);` (scope `uLang::SemanticTypeUtils`)
- L1804 _prototype_ `const CNormalType& StripVariableAndConstraints(const CNormalType&);` (scope `uLang::SemanticTypeUtils`)
- L1805 _prototype_ `const CNormalType& StripVariableAndConstraints(const CNormalType&, ETypeConstraintFlags& OutConstraintFlags);` (scope `uLang::SemanticTypeUtils`)
- L1806 _prototype_ `CClassDefinition* EnclosingClassOfDataDefinition(const CDataDefinition* Def );` (scope `uLang::SemanticTypeUtils`)
- L1808 _prototype_ `const CTypeBase* DecayReference(const CTypeBase*);` (scope `uLang::SemanticTypeUtils`)
- L1809 _prototype_ `const CTypeBase* DecayReference(const CTypeBase&);` (scope `uLang::SemanticTypeUtils`)
- L1811 _prototype_ `void FillTypeVariablePolarities( const CTypeBase*, ETypePolarity, STypeVariablePolarities&);` (scope `uLang::SemanticTypeUtils`)
- L1815 _prototype_ `void FillTypeVariablePolaritiesImpl( const CTypeBase*, ETypePolarity, STypeVariablePolarities&, TArray<SNormalTypePolarity>& Visited);` (scope `uLang::SemanticTypeUtils`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/Signature.h` (Public)


#### struct `uLang::SSignature`  
`struct SSignature`  
_L16-99_
- desc: Type signature / parameter interface for routines/invokables
- L18 _public typedef_ `using ParamDefinitions = TArray<CDataDefinition*>;`
- L22 _public function_ `SSignature(const CFunctionType& FunctionType, ParamDefinitions&& Params) : _FunctionType(&FunctionType) , _Params(Move(Params))`
- L29 _public prototype_ `SSignature() = default;` — @TODO: This represents an invalid signature (likely, yet to be fully analyzed) -- we should promote this invalid state up to the use sites (say, have an TOptional<SSignature> instead)
- L31 _public function_ `void SetFunctionType(const CFunctionType* FunctionType)`
- L32 _public function_ `void SetParams(ParamDefinitions&& Params)`
- L33 _public function_ `void EmptyParams()`
- L35 _public function_ `bool HasParams() const`
- L40 _public function_ `int32_t NumParams() const`
- L45 _public function_ `const ParamDefinitions& GetParams() const`
- L50 _public function_ `const CTypeBase* GetParamType(int32_t ParamIndex) const`
- L60 _public function_ `const CTypeBase* GetParamsType() const`
- L67 _public function_ `const CTypeBase* GetReturnType() const`
- L74 _public function_ `const CFunctionType* GetFunctionType() const`
- L79 _public function_ `SEffectSet GetEffects() const`
- L97 _private member_ `const CFunctionType* _FunctionType = nullptr;`
- L98 _private member_ `ParamDefinitions _Params;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L84 _function_ `friend bool operator==(const SSignature& Left, const SSignature& Right)` (scope `uLang`)
- L89 _function_ `friend bool operator!=(const SSignature& Left, const SSignature& Right)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/SmallDefinitionArray.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L12 _typedef_ `using SmallDefinitionArray = TArrayG<CDefinition*, TInlineElementAllocator<1>>;` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/StructOrClass.h` (Public)


#### enum `uLang::EStructOrClass`  
`enum class EStructOrClass`  
_L8-8_
- L8 _public enumerator_ `enum class EStructOrClass { Class, Struct };`
- L8 _public enumerator_ `enum class EStructOrClass { Class, Struct };`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/TypeAlias.h` (Public)


#### class `uLang::CAliasType`  
`class CAliasType : public CTypeBase`  
_L18-51_
- inherits: `CTypeBase`
- desc: Encodes a type alias as a non-normal CTypeBase.
- L22 _public function_ `CAliasType(CTypeAlias& Definition, const CTypeBase* AliasedType) : CTypeBase(AliasedType->GetProgram()), _Definition(Definition), _AliasedType(AliasedType)`
- L25 _public function_ `CTypeAlias& GetDefinition() const`
- L26 _public function_ `const CTypeBase* GetAliasedType() const`
- L29 _public function_ `virtual const CNormalType& GetNormalType() const override` — CTypeBase interface.
- L34 _public function_ `virtual const CAliasType* AsAliasType() const override`
- L39 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L40 _public function_ `virtual bool CanBePredictsVarDataType() const override`
- L42 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override`
- L49 _private member_ `CTypeAlias& _Definition;`
- L50 _private member_ `const CTypeBase* _AliasedType;`

#### class `uLang::CTypeAlias`  
`class CTypeAlias : public CDefinition`  
_L54-140_
- inherits: `CDefinition`
- desc: Maps a name to a type
- L57 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::TypeAlias;`
- L59 _public function_ `CTypeAlias(const CSymbol& Name, CScope& EnclosingScope) : CDefinition(StaticDefinitionKind, EnclosingScope, Name)`
- L64 _public function_ `bool IsInitialized() const`
- L69 _public function_ `const CTypeType* GetTypeType() const`
- L74 _public function_ `const CTypeBase* GetType() const`
- L83 _public function_ `const CTypeBase* GetPositiveAliasedType() const`
- L89 _public function_ `void InitType(const CTypeBase* NegativeAliasedType, const CTypeBase* PositiveAliasedType)`
- L103 _public function_ `void SetAstNode(CExprTypeAliasDefinition* AstNode)` — CDefinition interface.
- L104 _public function_ `CExprTypeAliasDefinition* GetAstNode() const`
- L106 _public function_ `void SetIrNode(CExprTypeAliasDefinition* AstNode)`
- L107 _public function_ `CExprTypeAliasDefinition* GetIrNode(bool bForce = false) const`
- L109 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L111 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L113 _public function_ `void GetPath(uLang::CUTF8StringBuilder& OutBuilder, const uLang::UTF8Char SeparatorChar, const uLang::EPathMode Mode) const`
- L127 _public function_ `CUTF8String GetPath(const uLang::UTF8Char SeparatorChar, const uLang::EPathMode Mode) const`
- L136 _private member_ `const CTypeType* _TypeType{ nullptr };`
- L138 _private member_ `TUPtr<CAliasType> _NegativeAliasType;`
- L139 _private member_ `TUPtr<CAliasType> _PositiveAliasType;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/TypeScope.h` (Public)


#### class `uLang::CTypeScope`  
`class CTypeScope : public CLogicalScope, public CSharedMix`  
_L14-24_
- inherits: `CLogicalScope,CSharedMix`
- desc: The implicit scope of a type.
- L18 _public function_ `CTypeScope(CScope& EnclosingScope) : CLogicalScope(CScope::EKind::Type, &EnclosingScope, EnclosingScope.GetProgram())`
- L23 _public function_ `virtual CSymbol GetScopeName() const override` — CScope interface.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/TypeVariable.h` (Public)


#### class `uLang::CTypeVariable`  
`class CTypeVariable : public CDefinition, public CNominalType`  
_L20-129_
- inherits: `CDefinition,CNominalType`
- L23 _public member_ `static const CDefinition::EKind StaticDefinitionKind = CDefinition::EKind::TypeVariable;`
- L24 _public member_ `static const ETypeKind StaticTypeKind = ETypeKind::Variable;`
- L42 _public member_ `const CDataDefinition* _ExplicitParam = nullptr;` — A parameter `X` of type `type(A, B)` is encoded as @code :type(Y, Y) where Y:type(A, Z), Z:type(Y, B) @endcode with all uses resolving to `Z`.  Upon instantiation, @code :type(Y, Y) @endcode is rewritten to effectively @code :type(Y, Z) @endcode Any negative uses (outside of the negative use above) is replaced with `Y`, while positive uses (again, outside of the above) are replaced with `Z`. `_ExplicitParam` points to the corresponding data definition. of the original explicit argument.
- L45 _public member_ `const CTypeVariable* _NegativeTypeVariable = nullptr;` — `_NegativeTypeVariable` points to `Y` in the original encoding. `_ExplicitParam->_ImplicitParam` can be used to access `Z`.
- L47 _public function_ `CTypeVariable(const CSymbol& Name, const CTypeBase* NegativeType, const CTypeBase* PositiveType, CScope& EnclosingScope) : CDefinition`
- L55 _public function_ `const CTypeBase* GetNegativeType() const`
- L56 _public function_ `void SetNegativeType(const CTypeBase* NegativeType)`
- L58 _public function_ `const CTypeBase* GetPositiveType() const`
- L59 _public function_ `void SetPositiveType(const CTypeBase* PositiveType)`
- L61 _public function_ `virtual EComparability GetComparability() const override`
- L68 _public function_ `virtual const CDefinition* Definition() const override` — CNominalType interface.
- L71 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence OuterPrecedence, TArray<const CFlowType*>& VisitedFlowTypes, bool bLinkable, ETypeStringFlag Flag) const override` — CTypeBase interface.
- L75 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L78 _public function_ `void SetAstNode(CExprDefinition* AstNode)` — CDefinition interface.
- L79 _public function_ `CExprDefinition* GetAstNode() const`
- L81 _public function_ `void SetIrNode(CExprDefinition* AstNode)`
- L82 _public function_ `CExprDefinition* GetIrNode(bool bForce = false) const`
- L84 _public function_ `virtual bool IsPersistenceCompatConstraint() const override`
- L86 _public function_ `virtual bool IsEntitlementCompatConstraint() const override`
- L88 _public function_ `virtual bool IsPersistable() const override`
- L90 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L108 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L127 _private member_ `const CTypeBase* _NegativeType = nullptr;`
- L128 _private member_ `const CTypeBase* _PositiveType = nullptr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/UnknownType.h` (Public)


#### class `uLang::CUnknownType`  
`class CUnknownType : public CNormalType`  
_L19-41_
- inherits: `CNormalType`
- desc: An unknown type - can optionally contain a list of possibly valid types
- L22 _public member_ `static constexpr ETypeKind StaticTypeKind = ETypeKind::Unknown;`
- L25 _public member_ `mutable TArray<const CTypeBase *> _SuggestedTypes;` — Valid replacements for this type (if any)
- L27 _public function_ `CUnknownType(const CSymbol& Name, CScope& EnclosingScope) : CNormalType(ETypeKind::Unknown, EnclosingScope.GetProgram()), _Name(Name)`
- L29 _public function_ `virtual CUTF8String AsCodeRecursive(ETypeSyntaxPrecedence , TArray<const CFlowType*>& , bool bLinkable, ETypeStringFlag Flag) const override`
- L31 _public function_ `virtual bool IsPersistable() const override`
- L33 _public function_ `virtual bool IsExplicitlyCastable() const override`
- L35 _public function_ `virtual bool IsExplicitlyConcrete() const override`
- L37 _public function_ `virtual bool CanBeCustomAccessorDataType() const override`
- L40 _public member_ `const CSymbol& _Name;` — The name of the unknown type.

#### class `uLang::CExprError`  
`class CExprError : public CExpressionBase`  
_L46-66_
- inherits: `CExpressionBase`
- desc: Error expression - "~er~" produced when an expression couldn't be analyzed due to an error.
- L49 _public prototype_ `CExprError(TUPtr<CUnknownType>&& ExprType = nullptr, bool bCanFail = false);`
- L51 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L52 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L53 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L54 _public function_ `virtual bool CanFail(const CAstPackage* Package) const override`
- L58 _public function_ `void AppendChild(TSPtr<CAstNode>&& Child)` — We hold onto child expressions in service of semantic analysis -- we may want info for nested expressions, which may be well-formed, even if this parent was not fully formed.
- L60 _public function_ `virtual void VisitChildren(SAstVisitor& Visitor) const override`
- L63 _private member_ `TUPtr<CUnknownType> _ExprType;`
- L64 _private member_ `TSPtrArray<CAstNode> _UnknownChildren;`
- L65 _private member_ `bool _bCanFail;`

#### class `uLang::CExprPlaceholder`  
`class CExprPlaceholder : public CExpressionBase`  
_L71-82_
- inherits: `CExpressionBase`
- desc: Placeholder expression - "~ph~" produced by placeholder nodes in the Vst.
- L74 _public prototype_ `CExprPlaceholder(TUPtr<CUnknownType>&& ExprType = nullptr);`
- L76 _public function_ `virtual EAstNodeType GetNodeType() const override`
- L77 _public function_ `virtual CUTF8String GetErrorDesc() const override`
- L78 _public prototype_ `virtual const CTypeBase* GetResultType(const CSemanticProgram& Program) const override;`
- L81 _private member_ `TUPtr<CUnknownType> _ExprType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VERSECOMPILER_API`
- L13 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Semantics/VisitSet.h` (Public)


#### class `uLang::CVisitKey`  
`class CVisitKey`  
_L11-11_

#### class `uLang::CVisitSet`  
`class CVisitSet`  
_L13-27_
- L16 _public function_ `bool TryVisit(const CVisitKey& Key)`
- L26 _private member_ `TSet<const CVisitKey*> Set;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/IFileSystem.h` (Public)


#### class `uLang::IFileSystem`  
`class IFileSystem : public CSharedMix`  
_L12-78_
- inherits: `CSharedMix`
- L21 _public prototype_ `virtual ~IFileSystem() = default;`
- L27 _public typedef_ `using CFileDirectoryVisitor = TFunction<bool(const char* , const char* , bool )>;` — CFileDirectoryVisitor @return True to keep iterating, false to abort.
- L29 _public prototype_ `virtual bool IterateDirectory(const char* Directory, bool bRecurse, const CFileDirectoryVisitor& Visitor, bool bIsVisitorThreadSafe = false) = 0;`
- L35 _public typedef_ `using CFileMemAllocator = TFunction<void*(size_t )>;` — CFileMemAllocator @return Buffer pointer to fill, null if the requested memory allocation failed or is disallowed.
- L37 _public prototype_ `virtual bool FileRead(const char* FilePath, const CFileMemAllocator& Allocator) = 0;`
- L38 _public prototype_ `virtual bool FileWrite(const char* FilePath, const char* Output, const size_t ByteSize, const EWriteFlags WriteFlags = EWriteFlags::None) = 0;`
- L39 _public prototype_ `virtual bool DeleteFile(const char* FilePath) = 0;`
- L40 _public prototype_ `virtual bool IsFileNewer(const char* FilePath, const char* ComparisonPath) = 0;`
- L41 _public prototype_ `virtual bool CopyFile(const char* SourcePath, const char* DestinationPath) = 0;`
- L42 _public prototype_ `virtual bool DoesFileExist(const char* FilePath) = 0;`
- L43 _public prototype_ `virtual bool GetFilenameOnDisk(const char* FilePath, CUTF8String& OutFilenameOnDisk) = 0;`
- L44 _public prototype_ `virtual bool CreateDirectory(const char* DirPath) = 0;`
- L45 _public prototype_ `virtual bool DeleteDirectory(const char* DirPath) = 0;`
- L46 _public prototype_ `virtual bool DoesDirectoryExist(const char* DirPath) = 0;`
- L55 _public prototype_ `virtual bool FindTempDir(CUTF8String& OutDir) const = 0;` — Retrieves the path of the directory designated for temporary files. @param OutDirectory    Storage for the directory path. @return    `true` if the directory was retrieved successfully, `false` otherwise.
- L64 _public prototype_ `virtual bool MakeTempFile(CUTF8String& OutFilename) = 0;` — Creates a temporary file. The name is guaranteed to be unique. @param OutFilename 		Storage for the temporary filename. @return 				`true` if the temporary file was created successfully, `false` otherwise.
- L66 _public prototype_ `virtual bool GetCurrentWorkingDirectory(CUTF8String& OutWorkingDirectory) = 0;`
- L71 _public function_ `virtual bool SetCurrentWorkingDirectory(const char* DirPath)` — Note that SetCurrentWorkingDirectory may not be implemented in some embeddings (e.g. Unreal).
- L76 _public prototype_ `virtual bool IsReadOnly(const char* Filename) = 0;`
- L77 _public prototype_ `virtual bool SetReadOnly(const char* Filename, const bool bReadOnly) = 0;`

#### enum `uLang::IFileSystem::EWriteFlags`  
`enum EWriteFlags`  
_L15-19_
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `EvenIfReadOnly`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/IndexedSourceText.h` (Public)


#### struct `uLang::SIndexedSourceText`  
`struct SIndexedSourceText`  
_L12-17_
- L14 _public member_ `const CUTF8String _SourceText;`
- L15 _public member_ `TArray<int64_t>& _LineIndexCache;`
- L16 _public prototype_ `int64_t CalculateOffsetForLine(const int32_t TargetLine) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/PackageRole.h` (Public)


#### enum `uLang::EPackageRole`  
`enum class EPackageRole : uint8_t`  
_L14-21_
- desc: Describes the role a package plays in a Verse project Note: EPackageRole must mirror EVersePackageRole
- L16 _public enumerator_ `Source`
- L17 _public enumerator_ `External`
- L18 _public enumerator_ `GeneralCompatConstraint`
- L19 _public enumerator_ `PersistenceCompatConstraint`
- L20 _public enumerator_ `PersistenceSoftCompatConstraint`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`
- L23 _variable_ `constexpr auto ExternalPackageRole = Cases< EPackageRole::External, EPackageRole::GeneralCompatConstraint, EPackageRole::PersistenceCompatConstraint, EPackageRole::PersistenceSoftCompatConstraint>;` (scope `uLang`)
- L29 _variable_ `constexpr auto ConstraintPackageRole = Cases< EPackageRole::GeneralCompatConstraint, EPackageRole::PersistenceCompatConstraint, EPackageRole::PersistenceSoftCompatConstraint>;` (scope `uLang`)
- L34 _function_ `static inline const char* ToString(EPackageRole Role)` (scope `uLang`)
- L47 _function_ `static inline TOptional<EPackageRole> ToPackageRole(const CUTF8StringView& String)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/SourceDataProject.h` (Public)


#### class `uLang::CSourceDataSnippet`  
`class CSourceDataSnippet : public ISourceSnippet`  
_L13-34_
- inherits: `ISourceSnippet`
- desc: A source snippet in memory
- L16 _public function_ `CSourceDataSnippet(CUTF8String&& Path, CUTF8String&& Text) : _Path(Move(Path)) , _Text(Move(Text))`
- L22 _public function_ `virtual CUTF8String GetPath() const override`
- L23 _public function_ `virtual void SetPath(const CUTF8String& Path) override`
- L24 _public function_ `virtual TOptional<CUTF8String> GetText() const override`
- L25 _public function_ `virtual TOptional<Verse::Vst::TNodeRef<Verse::Vst::Snippet>> GetVst() const override`
- L26 _public function_ `virtual void SetVst(Verse::Vst::TNodeRef<Verse::Vst::Snippet> Snippet) override`
- L30 _private member_ `CUTF8String _Path;` — Original path of this snippet (usually on disk)
- L31 _private member_ `CUTF8String _Text;` — UTF8 encoded content of this snippet
- L33 _private member_ `TOptional<Verse::Vst::TNodeRef<Verse::Vst::Snippet>> _Vst;`

#### class `uLang::CSourceDataPackage`  
`class CSourceDataPackage : public CSourcePackage`  
_L39-56_
- inherits: `CSourcePackage`
- desc: A source package in memory
- L43 _public function_ `CSourceDataPackage(const CUTF8String& Name, const CUTF8String& DirPath, const CSourcePackage::SSettings& Settings) : CSourcePackage(Name, TSRef<CSourceModule>::New("")) , _DirPath(DirPath)`
- L50 _public function_ `virtual const CUTF8String& GetDirPath() const override`
- L51 _public function_ `virtual EOrigin GetOrigin() const override`
- L55 _private member_ `CUTF8String _DirPath;` — The directory where the contained snippets will be saved

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/SourceFileProject.h` (Public)


#### class `uLang::CSourceFileSnippet`  
`class CSourceFileSnippet : public ISourceSnippet`  
_L17-72_
- inherits: `ISourceSnippet`
- desc: A source snippet on disk
- L20 _public function_ `CSourceFileSnippet(CUTF8String&& FilePath, const TSRef<IFileSystem>& FileSystem) : _FilePath(Move(FilePath)) , _FileSystem(FileSystem)`
- L28 _public member_ `static constexpr char _InvalidSnippetCharacters[] = "\\` — This mimics what Unreal allows for package names, except that we allow periods in filenames as well.
- L31 _public function_ `virtual CUTF8String GetPath() const override`
- L32 _public function_ `virtual void SetPath(const CUTF8String& Path) override`
- L33 _public prototype_ `virtual TOptional<CUTF8String> GetText() const override;`
- L34 _public function_ `virtual TOptional<Verse::Vst::TNodeRef<Verse::Vst::Snippet>> GetVst() const override`
- L35 _public function_ `virtual void SetVst(Verse::Vst::TNodeRef<Verse::Vst::Snippet> Snippet) override`
- L38 _public function_ `const CUTF8StringView& GetFilePath() const`
- L40 _public function_ `bool HasModifiedText() const`
- L41 _public function_ `const CUTF8StringView& GetModifiedText() const`
- L42 _public function_ `void SetModifiedText(const CUTF8StringView& Text)`
- L43 _public function_ `void UnsetModifiedText()`
- L45 _public function_ `operator const CUTF8String&() const` — For set/map lookup
- L47 _public prototype_ `TOptional<SIndexedSourceText> GetIndexedSourceText();`
- L51 _public function_ `void MarkDirty(int32_t MinDeadLine)` — DeadLine represents the first line we know is invalid. Lines before that are still ok for the offset cache.
- L57 _public function_ `bool IsSnippetValid(Verse::Vst::Snippet& Snippet) const override`
- L58 _public function_ `uint64_t GetSourceVersion() const override`
- L61 _private function_ `void ClearLineIndexCache()`
- L62 _private function_ `void TruncateLineIndexCache(int32_t DeadLine)`
- L64 _private member_ `CUTF8String _FilePath;` — Path on disk
- L65 _private member_ `TOptional<CUTF8String> _ModifiedText;` — Version of the file content that was edited in memory, if exists
- L66 _private member_ `TSRef<IFileSystem> _FileSystem;`
- L68 _private member_ `TOptional<Verse::Vst::TNodeRef<Verse::Vst::Snippet>> _Vst;`
- L69 _private member_ `uint64_t _SnippetVersion = 1;` — This is analogous to the LSP file version, but not the same thing. The protocol doesn't version file changes to closed files
- L71 _private member_ `TArray<int64_t> _LineIndexCache;` — File offset cache for each line in the file.

#### class `uLang::CSourceFileModule`  
`class CSourceFileModule : public CSourceModule`  
_L77-105_
- inherits: `CSourceModule`
- desc: A module of source snippets on disk
- L80 _public function_ `CSourceFileModule(const CUTF8StringView& ModuleName, const CUTF8StringView& ModuleFilePath) : CSourceModule(ModuleName), _FilePath(ModuleFilePath)`
- L83 _public function_ `CSourceFileModule(const CUTF8StringView& ModuleName, CUTF8String&& ModuleFilePath) : CSourceModule(ModuleName), _FilePath(Move(ModuleFilePath))`
- L87 _public function_ `virtual const CUTF8String& GetFilePath() const override`
- L88 _public prototype_ `CUTF8StringView GetDirPath() const;`
- L90 _public prototype_ `TOptional<TSRef<CSourceFileModule>> FindSubmodule(const CUTF8StringView& ModuleName) const;`
- L91 _public prototype_ `TSRef<CSourceFileModule> FindOrAddSubmodule(const CUTF8StringView& ModuleName, const CUTF8StringView& DirPath);`
- L93 _public prototype_ `TOptional<TSRef<CSourceFileSnippet>> FindSnippetByFilePath(const CUTF8StringView& FilePath, bool bRecursive) const;`
- L94 _public function_ `void AddSnippet(const uLang::TSRef<ISourceSnippet>& Snippet)`
- L95 _public function_ `bool RemoveSnippet(const uLang::TSRef<ISourceSnippet>& Snippet, bool bRecursive)`
- L103 _private member_ `CUTF8String _FilePath;` — Path to the module file on disk If no module file exists, this is the module directory with a slash `/` at the end

#### class `uLang::CSourceFilePackage`  
`class CSourceFilePackage : public CSourcePackage`  
_L110-136_
- inherits: `CSourcePackage`
- desc: A package of source modules/snippets on disk
- L114 _public prototype_ `CSourceFilePackage(const CUTF8String& PackageFilePath, const TSRef<IFileSystem>& FileSystem, const TSRef<CDiagnostics>& Diagnostics);`
- L115 _public prototype_ `CSourceFilePackage(const SPackageDesc& PackageDesc, const TSRef<IFileSystem>& FileSystem, const TSRef<CDiagnostics>& Diagnostics);`
- L117 _public function_ `virtual const CUTF8String& GetDirPath() const override`
- L118 _public function_ `virtual const CUTF8String& GetFilePath() const override`
- L119 _public function_ `virtual EOrigin GetOrigin() const override`
- L121 _public prototype_ `CSourceFileModule* GetModuleForFilePath(const CUTF8StringView& FilePath);`
- L122 _public prototype_ `TOptional<TSRef<CSourceFileSnippet>> FindSnippetByFilePath(const CUTF8StringView& FilePath) const;`
- L123 _public prototype_ `TOptional<TSRef<CSourceFileSnippet>> AddSnippet(const CUTF8StringView& FilePath);` — Look up module by file path and add snippet to it - might fail if file path is not under root path
- L124 _public prototype_ `bool RemoveSnippet(const CUTF8StringView& FilePath);` — Look up module by file path and remove snippet from it
- L127 _private prototype_ `void ReadPackageFile(const CUTF8String& PackageFilePath, const TSRef<CDiagnostics>& Diagnostics);`
- L128 _private prototype_ `TSRef<CSourceFileModule> ResolveModuleForRelativeVersePath(const CUTF8String& RelativeVersePath, const TSRef<CDiagnostics>& Diagnostics) const;`
- L129 _private prototype_ `void GatherPackageSourceFiles(const CUTF8String& PackageFilePath, const TSRef<IFileSystem>& FileSystem, const TSRef<CDiagnostics>& Diagnostics);`
- L131 _private member_ `CUTF8String _PackageFilePath;`
- L132 _private member_ `CUTF8String _DirPath;` — Can be the containing folder of the package file, or point somewhere else
- L133 _private member_ `TOptional<TArray<CUTF8String>> _FilePaths;` — If set, use these _FilePaths for compilation instead of _DirPath (all _FilePaths must be under _DirPath)
- L135 _private member_ `const TSRef<IFileSystem> _FileSystem;`

#### class `uLang::CSourceFileProject`  
`class CSourceFileProject : public CSourceProject`  
_L141-174_
- inherits: `CSourceProject`
- desc: A project of source packages on disk
- L147 _public prototype_ `CSourceFileProject(const CUTF8String& ProjectFilePath, const TSRef<IFileSystem>& FileSystem, const TSRef<CDiagnostics>& Diagnostics);` — This ctor will load the vproject given a path
- L152 _public prototype_ `CSourceFileProject(const CUTF8String& Name, const TSRef<IFileSystem>& FileSystem, const TArray<SPackageDesc>& Packages, const TSRef<CDiagnostics>& Diagnostics, const bool bValkyrieSource);` — This ctor will create vproject given the path and packages
- L154 _public function_ `virtual const CUTF8String& GetFilePath() const override`
- L156 _public prototype_ `bool WriteProjectFile(const CUTF8String& ProjectFilePath, const TSRef<CDiagnostics>& Diagnostics);`
- L157 _public prototype_ `bool WriteVSCodeWorkspaceFile(const CUTF8String& WorkspaceFilePath, const CUTF8String& ProjectFilePath, const TSRef<CDiagnostics>& Diagnostics);`
- L159 _public prototype_ `TOptional<TSRef<CSourceFileSnippet>> FindSnippetByFilePath(const CUTF8StringView& FilePath) const;`
- L160 _public prototype_ `TOptional<TSRef<CSourceFileSnippet>> AddSnippet(const CUTF8StringView& FilePath);` — Look up module by file path and add snippet to it - might fail if file path is not under root path
- L161 _public prototype_ `bool RemoveSnippet(const CUTF8StringView& FilePath);` — Look up module by file path and remove snippet from it
- L163 _public prototype_ `static bool IsSnippetFile(const CUTF8StringView& FilePath);`
- L164 _public prototype_ `static bool IsModuleFile(const CUTF8StringView& FilePath);`
- L165 _public prototype_ `static bool IsPackageFile(const CUTF8StringView& FilePath);`
- L166 _public prototype_ `static bool IsProjectFile(const CUTF8StringView& FilePath);`
- L167 _public prototype_ `static bool IsValidModuleName(const CUTF8StringView& ModuleName);`
- L168 _public prototype_ `static bool IsValidSnippetFileName(const CUTF8StringView& FileName);`
- L172 _private member_ `CUTF8String _FilePath;`
- L173 _private member_ `const TSRef<IFileSystem> _FileSystem;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/SourceProject.h` (Public)


#### class `uLang::ISourceSnippet`  
`class ISourceSnippet : public CSharedMix`  
_L20-53_
- inherits: `CSharedMix`
- desc: Abstraction of a source file
- L24 _public prototype_ `virtual ~ISourceSnippet() = default;`
- L29 _public prototype_ `virtual CUTF8String GetPath() const = 0;` — Globally unique path of this snippet, e.g. a fully qualified file path
- L30 _public prototype_ `virtual void SetPath(const CUTF8String& Path) = 0;`
- L37 _public prototype_ `virtual TOptional<CUTF8String> GetText() const = 0;` — Get text representation of this snippet When the result is EResult::Unspecified, no text representation exists When the result is EResult::Error, text representation exists, but an error occurred retrieving it
- L44 _public prototype_ `virtual TOptional<Verse::Vst::TNodeRef<Verse::Vst::Snippet>> GetVst() const = 0;` — Get Vst representation of this snippet When the result is EResult::Unspecified, no Vst representation exists When the result is EResult::Error, Vst representation exists, but an error occurred retrieving it
- L45 _public prototype_ `virtual void SetVst(Verse::Vst::TNodeRef<Verse::Vst::Snippet> Snippet) = 0;`
- L51 _public function_ `virtual bool IsSnippetValid(Verse::Vst::Snippet& Snippet) const` — Source version tracking to facilitate some VST reuse across compiles By default, all cached snippet VSTs are invalid so we won't reuse them.
- L52 _public function_ `virtual uint64_t GetSourceVersion() const`

#### class `uLang::CSourceModule`  
`class CSourceModule : public CSharedMix`  
_L58-97_
- inherits: `CSharedMix`
- desc: A module
- L63 _public member_ `TSRefArray<ISourceSnippet> _SourceSnippets;` — The source files contained in the module
- L66 _public member_ `TSRefArray<CSourceModule> _Submodules;` — Submodules of this module
- L69 _public function_ `CSourceModule(const CUTF8StringView& Name) : _Name(Name)` — Construct from name
- L70 _public prototype_ `virtual ~CSourceModule() = default;`
- L72 _public function_ `const CUTF8String& GetName() const`
- L73 _public function_ `virtual const CUTF8String& GetFilePath() const`
- L74 _public prototype_ `CUTF8StringView GetNameFromFile() const;`
- L75 _public prototype_ `static CUTF8StringView GetNameFromFile(const CUTF8StringView& ModuleFilePath);`
- L77 _public prototype_ `TOptional<TSRef<CSourceModule>> FindSubmodule(const CUTF8StringView& ModuleName) const;`
- L79 _public prototype_ `void AddSnippet(const uLang::TSRef<ISourceSnippet>& Snippet);`
- L80 _public prototype_ `bool RemoveSnippet(const uLang::TSRef<ISourceSnippet>& Snippet, bool bRecursive);`
- L86 _public prototype_ `template<typename FunctionType> bool VisitAll(FunctionType&& Lambda) const;` — Visit this module and all its submodules Lambda returns true to continue visiting, false to terminate search Returns true if all modules have been visited, false if search was terminated early
- L88 _public prototype_ `template<typename FunctionType> bool VisitAll(FunctionType&& Lambda);` — non-const version
- L91 _public function_ `bool operator==(const CUTF8StringView& Name) const` — For lookup by name
- L96 _protected member_ `CUTF8String _Name;` — Name of this module
- L321 _function_ `template<typename FunctionType> bool CSourceModule::VisitAll(FunctionType&& Lambda) const`
- L339 _function_ `template<typename FunctionType> bool CSourceModule::VisitAll(FunctionType&& Lambda)` — non-const version

#### class `uLang::CSourcePackage`  
`class CSourcePackage : public CSharedMix`  
_L102-271_
- inherits: `CSharedMix`
- desc: A package of modules
- L222 _public member_ `TSRef<CSourceModule> _RootModule;` — The root module of this package, equivalent to the _VersePath specified in _Settings
- L225 _public member_ `TOptional<SVersionedDigest> _Digest;` — Optional digest to be used instead of source if desired
- L228 _public member_ `TOptional<SVersionedDigest> _PublicDigest;` — The public-only digest, if it exists.
- L231 _public function_ `CSourcePackage(const CUTF8StringView& Name, const TSRef<CSourceModule>& RootModule) : _RootModule(RootModule), _Name(Name)` — Construct from name
- L232 _public prototype_ `virtual ~CSourcePackage() = default;`
- L234 _public function_ `const CUTF8String& GetName() const`
- L235 _public function_ `const SSettings& GetSettings() const`
- L236 _public function_ `virtual EOrigin GetOrigin() const`
- L237 _public function_ `virtual const CUTF8String& GetDirPath() const`
- L238 _public function_ `virtual const CUTF8String& GetFilePath() const`
- L239 _public prototype_ `int32_t GetNumSnippets() const;`
- L240 _public function_ `const FSolFingerprint& GetFingerprint() const`
- L242 _public prototype_ `void GenerateFingerprint(TSRef<ISolFingerprintGenerator>& Generator) const;`
- L244 _public function_ `void SetName(const CUTF8StringView& NewName)`
- L245 _public function_ `void SetVersePath(const CUTF8StringView& VersePath)`
- L246 _public function_ `void SetVerseScope(const EVerseScope VerseScope)`
- L247 _public function_ `void SetVerseVersion(const TOptional<uint32_t> VerseVersion)`
- L248 _public function_ `void SetAllowExperimental(const bool bAllowExperimental)`
- L249 _public function_ `void SetRole(const EPackageRole Role)`
- L250 _public function_ `void SetTreatDefinitionsAsImplicit(bool bTreatAsImplicit)`
- L251 _public function_ `void SetFingerprint(FSolFingerprint Fingerprint)`
- L252 _public prototype_ `void SetDependencyPackages(TArray<CUTF8String>&& PackageNames);`
- L253 _public prototype_ `void AddDependencyPackage(const CUTF8StringView& PackageName);`
- L254 _public prototype_ `void TruncateVniDestDir();` — Strip parent path from VniDestDir
- L256 _public prototype_ `bool RemoveSnippet(const uLang::TSRef<ISourceSnippet>& Snippet);`
- L261 _private member_ `CUTF8String _Name;` — Name of this package
- L264 _private member_ `FSolFingerprint _Fingerprint;` — Fingerprint of this package
- L269 _protected member_ `SSettings _Settings;` — Settings, e.g. parsed from .vpackage file

#### struct `uLang::CSourcePackage::SSettings`  
`struct SSettings`  
_L107-174_
- desc: Settings of a package This mirrors FVersePackageSettings in the runtime
- L109 _public member_ `CUTF8String _VersePath;` — Verse path of the root module of this package
- L110 _public member_ `EVerseScope _VerseScope = EVerseScope::PublicUser;` — Origin/visibility of Verse code in this package
- L111 _public member_ `EPackageRole _Role = EPackageRole::Source;` — The role this package plays in the project.
- L112 _public member_ `TOptional<uint32_t> _VerseVersion;` — The language version the package targets. Note that this value is ignored for digests, which are assumed to target the latest unstable version.
- L113 _public member_ `TOptional<uint32_t> _UploadedAtFNVersion;` — Only set for constraint `_Role`.
- L114 _public member_ `bool _bTreatModulesAsImplicit = false;` — If true, module macros in this package's source and digest will be treated as implicit
- L115 _public member_ `TArray<CUTF8String> _DependencyPackages;` — Names of packages this package is dependent on
- L116 _public member_ `TOptional<CUTF8String> _VniDestDir;` — Destination directory for VNI generated C++ code (fully qualified)
- L117 _public member_ `bool _bAllowExperimental = false;` — If true, this package can use experimental definitions (but cannot publish in UEFN).
- L118 _public member_ `bool _bEnableSceneGraph = false;` — If true, Scene Graph is enabled. This impacts the asset digest that is generated.
- L119 _public member_ `bool _bEnableSceneGraphAnimation = false;` — If true, Scene Graph Animation is enabled. This impacts the asset digest that is generated.
- L120 _public member_ `bool _bDefsInClassesInAssetManifests = true;` — See FVersePackageSettings::_bDefsInClassesInAssetManifests
- L122 _public function_ `uint32_t GetUploadedAtFNVersion(uint32_t Default) const`
- L127 _public function_ `void GenerateFingerprint(TSRef<ISolFingerprintGenerator>& Generator) const`

#### struct `uLang::CSourcePackage::SVersionedDigest`  
`struct SVersionedDigest`  
_L176-210_
- L178 _public member_ `TSRef<ISourceSnippet> _Snippet;`
- L179 _public member_ `uint32_t _EffectiveVerseVersion;`
- L180 _public member_ `TArray<CUTF8String> _DependencyPackages;`
- L182 _public function_ `void GenerateFingerprint(TSRef<ISolFingerprintGenerator>& Generator) const`

#### enum `uLang::CSourcePackage::EOrigin`  
`enum EOrigin : uint8_t`  
_L213-218_
- desc: Where the source code of this package originates
- L215 _public enumerator_ `Unknown`
- L216 _public enumerator_ `Memory`
- L217 _public enumerator_ `FileSystem`

#### class `uLang::CSourceProject`  
`class CSourceProject : public CSharedMix`  
_L276-315_
- inherits: `CSharedMix`
- desc: A project, holding packages and other information
- L289 _public member_ `TArray<SPackage> _Packages;` — The packages contained in this project
- L292 _public function_ `CSourceProject(const CUTF8StringView& Name) : _Name(Name)` — Construct from name
- L294 _public prototype_ `CSourceProject(const CSourceProject& Other);` — Construct from other project by making a shallow copy
- L295 _public prototype_ `virtual ~CSourceProject() = default;`
- L297 _public function_ `const CUTF8String& GetName() const`
- L298 _public function_ `virtual const CUTF8String& GetFilePath() const`
- L299 _public prototype_ `int32_t GetNumSnippets() const;`
- L301 _public prototype_ `const SPackage* FindPackage(const CUTF8StringView& PackageName, const CUTF8StringView& PackageVersePath) const;`
- L302 _public prototype_ `const SPackage& FindOrAddPackage(const CUTF8StringView& PackageName, const CUTF8StringView& PackageVersePath);`
- L303 _public prototype_ `void AddSnippet(const uLang::TSRef<ISourceSnippet>& Snippet, const CUTF8StringView& PackageName, const CUTF8StringView& PackageVersePath);`
- L304 _public prototype_ `bool RemoveSnippet(const uLang::TSRef<ISourceSnippet>& Snippet);`
- L306 _public prototype_ `void TruncateVniDestDirs();` — Strip parent path from all VniDestDirs
- L308 _public prototype_ `void PopulateTransitiveDependencyMap(uLang::TMap<const CSourcePackage*, uLang::TArray<const CSourcePackage*>>& OutMap);` — Only exposed for testing purposes
- L309 _public prototype_ `void GeneratePackageFingerprints(TSRef<ISolFingerprintGenerator>& Generator);`
- L314 _private member_ `CUTF8String _Name;` — Name of this project

#### struct `uLang::CSourceProject::SPackage`  
`struct SPackage`  
_L281-286_
- desc: Entry for a package contained in this project
- L283 _public member_ `TSPtr<CSourcePackage> _Package;`
- L284 _public member_ `bool _bReadonly = false;`
- L285 _public member_ `bool _bValkyrieSource = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uLang`
- L155 _function_ `` (scope `uLang::CSourcePackage::SSettings::GenerateFingerprint`)
- L201 _function_ `` (scope `uLang::CSourcePackage::SVersionedDigest::GenerateFingerprint`)

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/SourceProjectUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uLang`
- L10 _namespace_ `namespace (anonymous)` (scope `uLang`)
- L12 _variable_ `const CUTF8StringView SnippetExt(".ve` (scope `uLang::__anon8a6a28920111`)
- L13 _variable_ `const CUTF8StringView ModuleExt(".vm` (scope `uLang::__anon8a6a28920111`)
- L14 _variable_ `const CUTF8StringView PackageExt(".vp` (scope `uLang::__anon8a6a28920111`)
- L15 _variable_ `const CUTF8StringView ProjectExt(".vp` (scope `uLang::__anon8a6a28920111`)

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/SourceProjectWriter.h` (Public)


#### struct `uLang::SPackageDesc`  
`struct SPackageDesc`  
_L16-22_
- desc: Specification of a package embedded in a project file This mirrors FVersePackageDesc in the runtime
- L18 _public member_ `CUTF8String _Name;`
- L19 _public member_ `CUTF8String _DirPath;` — To be used for VSCode workspace. Also for compilation unless _FilePaths is specified.
- L20 _public member_ `TOptional<TArray<CUTF8String>> _FilePaths;` — Optional array, so we can distinguish between absence of array vs absence of files
- L21 _public member_ `CSourcePackage::SSettings _Settings;`

#### struct `uLang::SPackageRef`  
`struct SPackageRef`  
_L25-31_
- desc: A package as represented in a Verse project file
- L27 _public member_ `TOptional<CUTF8String> _FilePath;` — Path to the vpackage file
- L28 _public member_ `TOptional<SPackageDesc> _Desc;` — Or, alternatively, directly embedded package desc
- L29 _public member_ `bool _ReadOnly = false;`
- L30 _public member_ `bool _Build = true;`

#### struct `uLang::SProjectDesc`  
`struct SProjectDesc`  
_L34-37_
- desc: The contents of a Verse project file
- L36 _public member_ `TArray<SPackageRef> _Packages;`

#### struct `uLang::SWorkspacePackageRef`  
`struct SWorkspacePackageRef`  
_L40-45_
- desc: A root folder inside a VSCode workspace
- L42 _public member_ `CUTF8String _Name;`
- L43 _public member_ `CUTF8String _DirPath;`
- L44 _public member_ `CUTF8String _VersePath;`

#### struct `uLang::SWorkspaceDesc`  
`struct SWorkspaceDesc`  
_L48-53_
- desc: A VSCode workspace
- L50 _public member_ `TArray<SWorkspacePackageRef> _Folders;`
- L51 _public member_ `CUTF8String _WorkspaceFilePath;`
- L52 _public member_ `bool (*_AddSettingsFunc)(uLang::JSONDocument*, const CUTF8StringView& WorkspaceFilePath);`

#### class `uLang::CSourceProjectWriter`  
`class CSourceProjectWriter`  
_L59-129_
- desc: Helper class to write a source project to disk This can either be a copy from one location to another, or save an in-memory project to the file system
- L68 _public function_ `CSourceProjectWriter(const TSRef<IFileSystem>& FileSystem, const TSRef<CDiagnostics>& Diagnostics) : _FileSystem(FileSystem) , _Diagnostics(Diagnostics)`
- L77 _public prototype_ `bool WriteProject(const CSourceProject& Project, const CUTF8String& DestinationDir, CUTF8String* ResultProjectFilePath = nullptr, const EWriteFlags WriteFlags = EWriteFlags::All) const;` — Write the entire given source project to disk If ResultProjectFilePath is given, a vproject file will be generated and the path to it returned
- L85 _public prototype_ `bool WriteProjectFile(const SProjectDesc& ProjectDesc, const CUTF8String& ProjectFilePath) const;` — Write only a vproject file to the given file path
- L90 _public prototype_ `bool WriteVSCodeWorkspaceFile(const SWorkspaceDesc& WorkspaceDesc, const CUTF8String& WorkspaceFilePath) const;` — Write a .code-workspace file to the given file path
- L95 _public prototype_ `static SProjectDesc GetProjectDesc(const CSourceProject& Project);` — Derive a project desc from a source project
- L100 _public prototype_ `static SWorkspaceDesc GetWorkspaceDesc(const CSourceProject& Project, const CUTF8String& ProjectFilePath);` — Derive a workspace desc from a source project
- L107 _private prototype_ `bool WritePackage(const CSourcePackage& Package, const CUTF8String& DestinationDir, const EWriteFlags WriteFlags, SPackageDesc* OutPackageDesc = nullptr) const;` — Write a given source package to disk.
- L112 _private prototype_ `bool WriteSourceSnippet(const CSourceModule& Module, const TSRef<ISourceSnippet>& Snippet, const CUTF8String& ContainingDir) const;` — Write a single snippet to the given directory
- L117 _private prototype_ `bool WriteDigestSnippet(const TSRef<ISourceSnippet>& Snippet, const CUTF8String& ContainingDir, const CUTF8String& FlatPackageName) const;` — Write a single digest-snippet to the given directory
- L119 _private prototype_ `bool WriteSnippetInternal(const TSRef<ISourceSnippet>& Snippet, const CUTF8String& Path) const;`
- L125 _private prototype_ `template<class T> bool WriteJSONFile(const T& Object, bool (*ToJSON)(const T& Value, JSONDocument* JSON), EDiagnostic SerializationError, const CUTF8String& DestinationPath) const;` — Serialize to JSON and write a given struct of type T to a file
- L127 _private member_ `TSRef<IFileSystem> _FileSystem;`
- L128 _private member_ `TSRef<CDiagnostics> _Diagnostics;`

#### enum `uLang::CSourceProjectWriter::EWriteFlags`  
`enum class EWriteFlags`  
_L62-66_
- L64 _public enumerator_ `All`
- L65 _public enumerator_ `UserSources`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/UploadedAtFNVersion.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace VerseFN`
- L9 _namespace_ `namespace UploadedAtFNVersion` (scope `VerseFN`)
- L14 _variable_ `static constexpr uint32_t Latest = UINT32_MAX - 0xFF;` (scope `VerseFN::UploadedAtFNVersion`) — Leave a few "versions" that occur *after* Latest. The default version in test situations is always Latest. This will give us some room for testing.
- L15 _variable_ `static constexpr uint32_t Primordial = 0;` (scope `VerseFN::UploadedAtFNVersion`)
- L16 _variable_ `static constexpr uint32_t FixSubtypingIgnoringInheritedFieldsVersion = Latest + 1;` (scope `VerseFN::UploadedAtFNVersion`)
- L17 _function_ `inline bool CheckSuperQualifiers(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L18 _function_ `inline bool EnforceDontMixCommaAndSemicolonInBlocks(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L19 _function_ `inline bool EnableGenerators(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L20 _function_ `inline bool EnableFinalSpecifierFixes(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L21 _function_ `inline bool EnableNamedParametersForLocalize(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L22 _function_ `inline bool EnableProfileMacro(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L23 _function_ `inline bool EnforceUnambiguousEnumerators(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L24 _function_ `inline bool StricterCheckForDefaultInConcreteClasses(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L25 _function_ `inline bool SortSourceFilesLexicographically(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L26 _function_ `inline bool DeprecateVariesEffect(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L27 _function_ `inline bool ConcurrencyAddScope(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L28 _function_ `inline bool DecidesEffectNoLongerImpliesComputes(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L29 _function_ `inline bool StricterEditableOverrideCheck(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L30 _function_ `inline bool OptionTypeDoesntIgnoreValueHashability(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L31 _function_ `inline bool SortSourceSubmodulesLexicographically(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L32 _function_ `inline bool EnforceSnippetNameValidity(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L33 _function_ `inline bool EnableCastableSubtype(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L34 _function_ `inline bool EnforceCorrectQualifiedNames(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L35 _function_ `inline bool StrictConstructorFunctionInvocation(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L36 _function_ `inline bool EnforceUECaseInsensitiveNames(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L37 _function_ `inline bool AttributesRequireComputes(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L38 _function_ `inline bool DisallowNonClassEditableSubtypes(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L39 _function_ `inline bool DetectInaccessibleTypeDependenciesLate(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L40 _function_ `inline bool DisallowInstanceInAttributeExpression(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L41 _function_ `inline bool EnforceConcreteInterfaceData(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L42 _function_ `inline bool PersistableClassesMustNotImplementInterfaces(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L43 _function_ `inline bool RelaxInstancedReferenceSemantics(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L44 _function_ `inline bool DisallowSetExprOutsideAssignment(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L45 _function_ `inline bool EnforceNoReservedWordsAsEnumerators(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L46 _function_ `inline bool AllowEnumeratorsToAliasBuiltinDefinitions(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L47 _function_ `inline bool DetectInaccessibleTypeArguments(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L48 _function_ `inline bool EnforceTupleElementExprFallibility(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L49 _function_ `inline bool LocalQualifiers(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L50 _function_ `inline bool AllowRedirectorReflection(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L51 _function_ `inline bool EnforceCastableSubtype(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L52 _function_ `inline bool ImprovedCheckForIncorrectUseOfLocal(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L53 _function_ `inline bool ImprovedCheckForIncorrectUseOfLocalized(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L54 _function_ `inline bool EnableConcreteSubtype(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L55 _function_ `inline bool EnableAwaitMacro(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L56 _function_ `inline bool EnforceCastableTag(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L57 _function_ `inline bool ForcePublicInternalTransformsOnTransformComponent(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L58 _function_ `inline bool EnforceConvergesInDefaultInitializers(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L59 _function_ `inline bool ScopeDefinitionsToDefaultInitializers(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L60 _function_ `inline bool AgentInheritsFromEntity(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L61 _function_ `inline bool EnforceAllInitializersBeforeDelegatingConstructor(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L62 _function_ `inline bool FixAllowReadsInComputesDefaultExpressions(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L63 _function_ `inline bool EnforceAuroraMessageMaxLength(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L64 _function_ `inline bool DisallowGlobalInstancesOfInterfaceVars(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L65 _function_ `inline bool EnableBatchMacro(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L66 _function_ `inline bool EnforceInterfaceConstructionEffects(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L67 _function_ `inline bool EnforceInterfaceDataMustBeInitializedOrAccessible(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L68 _function_ `inline bool FixOverrideOfParametricFinalFields(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L69 _function_ `inline bool FixSubtypingIgnoringInheritedFields(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L70 _function_ `inline bool DisableParametricTypeEffectSpecifiers(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L71 _function_ `inline bool IfWithVerseInputUpgrade(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L72 _function_ `inline bool DisallowEditableInstancesOfTypeVariables(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L73 _function_ `inline bool RejectCaseInsensitiveOverrides(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L74 _function_ `inline bool EnableCastableConcreteSubtype(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L75 _function_ `inline bool EnforceEffects(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)
- L76 _function_ `inline bool EnableFirstMacro(const uint32_t CurrentVersion)` (scope `VerseFN::UploadedAtFNVersion`)

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/VerseScope.h` (Public)


#### enum `uLang::EVerseScope`  
`enum class EVerseScope : uint8_t`  
_L13-19_
- desc: Describes the origin and visibility of Verse code This mirrors EVerseScope in VerseScope.h in the Projects module.
- L15 _public enumerator_ `PublicAPI` — Created by Epic and only public definitions will be visible to public users
- L16 _public enumerator_ `InternalAPI` — Created by Epic and is entirely hidden from public users
- L17 _public enumerator_ `PublicUser` — Created by a public user
- L18 _public enumerator_ `InternalUser` — Created by an Epic internal user

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L21 _function_ `static inline bool IsPublicScope(EVerseScope VerseScope)` (scope `uLang`)
- L33 _function_ `static inline const char* ToString(EVerseScope VerseScope)` (scope `uLang`)
- L45 _function_ `static inline TOptional<EVerseScope> ToVerseScope(const CUTF8StringView& String)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/SourceProject/VerseVersion.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Verse`
- L8 _namespace_ `namespace Version` (scope `Verse`)
- L10 _variable_ `static constexpr uint32_t Primordial = 0;` (scope `Verse::Version`) — A retroactively defined version for pre-versioned Verse.
- L12 _variable_ `static constexpr uint32_t V1 = 1;` (scope `Verse::Version`)
- L14 _variable_ `static constexpr uint32_t SetMutatesFallibility = V1;` (scope `Verse::Version`) — Changes in V1:
- L15 _variable_ `static constexpr uint32_t MapLiteralKeysHandleIterationAndFailure = V1;` (scope `Verse::Version`)
- L16 _variable_ `static constexpr uint32_t DontMixCommaAndSemicolonInBlocks = V1;` (scope `Verse::Version`)
- L17 _variable_ `static constexpr uint32_t UniqueAttributeRequiresAllocatesEffect = V1;` (scope `Verse::Version`)
- L18 _variable_ `static constexpr uint32_t LocalQualifiers = V1;` (scope `Verse::Version`)
- L19 _variable_ `static constexpr uint32_t StructFieldsMustBePublic = V1;` (scope `Verse::Version`)
- L22 _variable_ `static constexpr uint32_t V2 = 2;` (scope `Verse::Version`)
- L24 _variable_ `static constexpr uint32_t CommentsAreNotContentInStrings = V2;` (scope `Verse::Version`) — Changes in V2 (note that more may be added as long as LatestStable < V2):
- L25 _variable_ `static constexpr uint32_t NoOctalLiterals = V2;` (scope `Verse::Version`)
- L27 _variable_ `static constexpr uint32_t LatestStable = V1;` (scope `Verse::Version`)
- L28 _variable_ `static constexpr uint32_t LatestUnstable = V2;` (scope `Verse::Version`)
- L30 _variable_ `static constexpr uint32_t Default = LatestStable;` (scope `Verse::Version`)
- L33 _variable_ `static constexpr uint32_t Minimum = Primordial;` (scope `Verse::Version`) — The minimum and maximum defined Verse versions: note that this is distinct from the minimum and maximum *allowed* Verse versions.
- L34 _variable_ `static constexpr uint32_t Maximum = LatestUnstable;` (scope `Verse::Version`)

### `Source/Runtime/VerseCompiler/Public/uLang/Syntax/NodeDecls.inl` (Public)


#### Free symbols / members of external scopes

- L4 _macro_ `#define VERSE_ENUM_VSTNODES(DECL_NODE) \` — Name               | RequiredChildren | Precedence | ESupportsManyChildren | EChildDeletionBehavior | IsCAtom

### `Source/Runtime/VerseCompiler/Public/uLang/Syntax/VstNode.h` (Public)


#### struct `Verse::Vst::TNodePtrG`  
`template<class NodeType, bool AllowNull, class AllocatorType, typename... AllocatorArgsType> struct TNodePtrG final`  
_L36-198_
- desc: Reference-counted smart pointer to a Vst::Node or any type descended from it. Use TNodeRef<T> (non-nullable) and TNodePtr<T> (nullable) aliases below rather than instantiating TNodePtrG directly.
- L41 _private typedef_ `using TMutableNodeType = std::remove_const_t<NodeType>;` — Store as non-const internally so Deallocate works with void*. Const-correctness is enforced through the public interface (operator->, operator*, Get).
- L44 _private member_ `TMutableNodeType* _Object;`
- L48 _private function_ `explicit TNodePtrG(TMutableNodeType* InObject) : _Object(InObject)` — Construct from raw pointer, incrementing its reference count. Used only by New() and MakeSharedFromThis().
- L53 _private function_ `void ReleaseObject()`
- L67 _public function_ `TNodePtrG(const TNodePtrG& Other) : _Object(Other._Object)` — Copy construction
- L70 _public function_ `template<class OtherNodeType, bool OtherAllowNull> requires (std::is_convertible_v<OtherNodeType*, NodeType*> && (AllowNull || !OtherAllowNull)) TNodePtrG(const TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>& Other) : _Object(Other._Object)`
- L74 _public function_ `TNodePtrG(TNodePtrG&& Other) : _Object(Other._Object)` — Move construction
- L77 _public function_ `template<class OtherNodeType, bool OtherAllowNull> requires (std::is_convertible_v<OtherNodeType*, NodeType*> && (AllowNull || !OtherAllowNull)) TNodePtrG(TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>&& Other) : _Object(Other._Object)`
- L81 _public function_ `TNodePtrG() : _Object(nullptr)` — Default / nullptr construction (only for AllowNull=true)
- L82 _public function_ `TNodePtrG(uLang::NullPtrType) : _Object(nullptr)`
- L84 _public function_ `~TNodePtrG()`
- L88 _public function_ `template <typename... CtorArgsType> static TNodePtrG New(CtorArgsType&&... CtorArgs)` — Factory methods
- L95 _public function_ `static TNodePtrG MakeSharedFromThis(const NodeType* const Node)`
- L103 _public function_ `TNodePtrG& operator=(const TNodePtrG& Other)` — Copy assignment
- L115 _public function_ `template<class OtherNodeType, bool OtherAllowNull> requires (std::is_convertible_v<OtherNodeType*, NodeType*> && (AllowNull || !OtherAllowNull)) TNodePtrG& operator=(const TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>& Other)`
- L127 _public function_ `TNodePtrG& operator=(TNodePtrG&& Other)` — Move assignment
- L140 _public function_ `template<class OtherNodeType, bool OtherAllowNull> requires (std::is_convertible_v<OtherNodeType*, NodeType*> && (AllowNull || !OtherAllowNull)) TNodePtrG& operator=(TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>&& Other)`
- L149 _public function_ `TNodePtrG& operator=(uLang::NullPtrType)` — Nullptr assignment (only for AllowNull=true)
- L152 _public function_ `NodeType* operator->() const` — Accessors
- L153 _public function_ `NodeType& operator*() const`
- L154 _public function_ `NodeType* Get() const`
- L155 _public function_ `operator NodeType* () const`
- L156 _public function_ `void Reset()`
- L157 _public function_ `bool IsValid() const`
- L160 _public function_ `operator bool() const` — Bool / validation
- L161 _public function_ `bool operator!() const`
- L165 _public function_ `template<class OtherNodeType> TNodePtrG<OtherNodeType, AllowNull, AllocatorType, AllocatorArgsType...>& As()` — Type cast (reinterpret the pointer to a different node type)
- L167 _public function_ `template<class OtherNodeType> const TNodePtrG<OtherNodeType, AllowNull, AllocatorType, AllocatorArgsType...>& As() const`
- L170 _public function_ `TNodePtrG<NodeType, false, AllocatorType, AllocatorArgsType...>& AsRef()` — AsRef: convert nullable TNodePtr to non-null TNodeRef
- L177 _public function_ `const TNodePtrG<NodeType, false, AllocatorType, AllocatorArgsType...>& AsRef() const`
- L185 _public function_ `bool operator==(uLang::NullPtrType) const` — Comparison operators
- L186 _public function_ `bool operator!=(uLang::NullPtrType) const`
- L187 _public function_ `bool operator==(NodeType* Other) const`
- L188 _public function_ `bool operator!=(NodeType* Other) const`
- L189 _public function_ `bool operator==(const TNodePtrG& Other) const`
- L190 _public function_ `bool operator!=(const TNodePtrG& Other) const`
- L192 _public function_ `template<class OtherNodeType, bool OtherAllowNull> bool operator==(const TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>& Other) const`
- L194 _public function_ `template<class OtherNodeType, bool OtherAllowNull> bool operator!=(const TNodePtrG<OtherNodeType, OtherAllowNull, AllocatorType, AllocatorArgsType...>& Other) const`

#### struct `uLang::LocusDistanceResult`  
`struct LocusDistanceResult`  
_L216-220_
- desc: This is used as a helper struct for storing the result of a signed distance check.
- L218 _public member_ `Verse::Vst::TNodeRef<Verse::Vst::Node> Node;`
- L219 _public member_ `int32_t Distance;`

#### enum `Verse::Vst::EChildDeletionBehavior`  
`enum class EChildDeletionBehavior : uint8_t`  
_L258-263_
- L260 _public enumerator_ `CreatePlaceholder`
- L261 _public enumerator_ `Delete`
- L262 _public enumerator_ `Default`

#### enum `Verse::Vst::ESupportsManyChildren`  
`enum class ESupportsManyChildren : uint8_t`  
_L265-270_
- L267 _public enumerator_ `Anywhere`
- L268 _public enumerator_ `TrailingOnly`
- L269 _public enumerator_ `Nowhere`

#### enum `Verse::Vst::NodeType`  
`#define VISIT_VSTNODE(NodeName, RequiredChildren, SupportsManyChildren, Precedence, ChildDeletionBehavior, IsCAtom) NodeName, enum class NodeType : uint8_t`  
_L273-276_
- L275 _public enumerator_ `VERSE_ENUM_VSTNODES(VISIT_VSTNODE)`

#### struct `Verse::Vst::NodeInfo`  
`#define VISIT_VSTNODE(NodeName, RequiredChildren, Precedence, SupportsManyChildren, ChildDeletionBehavior, IsCAtom)`  
_L280-288_
- L282 _public member_ `const char* FormalName;`
- L283 _public member_ `int32_t RequiredChildren;`
- L284 _public member_ `int32_t Precedence;`
- L285 _public member_ `ESupportsManyChildren SupportsManyChildren;`
- L286 _public member_ `EChildDeletionBehavior ChildDeletionBehavior;`
- L287 _public member_ `bool bIsCAtom;`

#### struct `Verse::Vst::Node`  
`struct Node`  
_L321-933_
- L323 _public typedef_ `using NodeArray = LArray<TNodeRef<Node>>;`
- L325 _public function_ `Node() : _Children() , _Parent(nullptr) , _Aux() , _PreComments() , _PostComments() , _NumNewLinesBefore(0) , _NumNewLinesAfter(0) , _Tag(0) , _Type(static_cast<NodeType>(0)) , _MappedAstNode(nullptr) , _Tile(nullptr)`
- L339 _public prototype_ `Node(const Node&) = delete;`
- L340 _public prototype_ `Node& operator=(const Node&) = delete;`
- L342 _public function_ `uint32_t GetRefCount() const`
- L344 _public function_ `Node(NodeType in_type) : Node()`
- L355 _public function_ `Node(NodeType in_type, const SLocus& whence) : Node()`
- L362 _public prototype_ `virtual ~Node();`
- L364 _public function_ `static SLocus CombineLocii(const NodeArray& Nodes)`
- L379 _public function_ `template<typename TNodeType> TNodeType& As()`
- L382 _public function_ `template<typename TNodeType> const TNodeType& As() const`
- L385 _public function_ `template <typename TNodeType> TNodeType* AsNullable()`
- L388 _public function_ `template <typename TNodeType> const TNodeType* AsNullable() const`
- L391 _public function_ `template<typename TNodeType> bool IsA() const`
- L393 _public function_ `int GetChildCount() const`
- L394 _public function_ `NodeType GetElementType() const`
- L395 _public function_ `int32_t GetElementTypeInt() const`
- L397 _public function_ `template<typename OpType> OpType GetTag() const`
- L399 _public function_ `template<typename OpType=uint8_t> void SetTag(OpType in_op)`
- L401 _public prototype_ `bool HasAttributes() const;`
- L402 _public prototype_ `const Identifier* GetAttributeIdentifier(const CUTF8StringView& AttributeName) const;`
- L403 _public prototype_ `bool IsAttributePresent(const CUTF8StringView& AttributeName) const;`
- L405 _public prototype_ `const Node* TryGetFirstAttributeOfType(NodeType Type) const;`
- L408 _public function_ `template<typename TNodeType> const TNodeType* TryGetFirstAttributeOfType() const`
- L420 _public prototype_ `void PrependAux(const TNodeRef<Node>& AuxChild);`
- L421 _public prototype_ `void PrependAux(const NodeArray& AuxChildren);`
- L422 _public prototype_ `void AppendAux(const TNodeRef<Node>& AuxChild);`
- L423 _public prototype_ `void AppendAux(const NodeArray& AuxChildren);`
- L424 _public prototype_ `void AppendAuxAt(const TNodeRef<Node>& AuxChild, int32_t Idx);`
- L425 _public function_ `const TNodePtr<Clause>& GetAux() const`
- L426 _public prototype_ `void SetAux(const TNodeRef<Clause>& Aux);`
- L427 _public function_ `void RemoveAux()`
- L429 _public prototype_ `void AppendPrefixComment(const TNodeRef<Node>& CommentNode);`
- L430 _public prototype_ `void AppendPrefixComment(TNodeRef<Node>&& CommentNode);`
- L431 _public prototype_ `void AppendPrefixComments(const NodeArray& CommentNodes);`
- L432 _public prototype_ `void AppendPostfixComment(const TNodeRef<Node>& CommentNode);`
- L433 _public prototype_ `void AppendPostfixComment(TNodeRef<Node>&& CommentNode);`
- L434 _public prototype_ `void AppendPostfixComments(const NodeArray& CommentNodes);`
- L435 _public function_ `const NodeArray& GetPrefixComments() const`
- L436 _public function_ `const NodeArray& GetPostfixComments() const`
- L437 _public function_ `NodeArray& AccessPrefixComments()`
- L438 _public function_ `NodeArray& AccessPostfixComments()`
- L440 _public function_ `void SetWhence(const SLocus& Whence)`
- L441 _public function_ `void CombineWhenceWith(const SLocus& Whence)`
- L442 _public function_ `const SLocus& Whence() const`
- L443 _public prototype_ `const CUTF8String& GetSnippetPath() const;`
- L444 _public prototype_ `const Snippet* FindSnippetByFilePath(const CUTF8StringView& FilePath) const;`
- L445 _public prototype_ `const Node* FindChildByPosition(const SPosition& TextPosition) const;`
- L446 _public prototype_ `const TNodeRef<Node> FindChildClosestToPosition(const SPosition& TextPosition, const SIndexedSourceText& SourceText) const;`
- L448 _public prototype_ `template<class VisitPolicy, typename ReturnType = void > static void VisitWith(const TNodeRef<Node>& node, VisitPolicy& visit_policy);`
- L450 _public function_ `const NodeInfo& GetElementInfo() const`
- L451 _public function_ `const ChType* GetElementName() const`
- L452 _public function_ `int32_t GetPrecedence() const`
- L453 _public function_ `int32_t NumRequiredChildren() const`
- L457 _public function_ `ESupportsManyChildren IsManyChildrenSupported() const`
- L462 _public function_ `int32_t NumNewLinesBefore() const`
- L467 _public function_ `void SetNumNewLinesBefore(const int32_t Num)`
- L472 _public function_ `int32_t NumNewLinesAfter() const`
- L477 _public function_ `void SetNumNewLinesAfter(const int32_t Num)`
- L482 _public function_ `void SetNewLineAfter(const bool bNewLineAfter)`
- L502 _public function_ `bool HasNewLinesAfter() const`
- L507 _public function_ `bool HasNewLinesBefore() const`
- L512 _public function_ `bool IsEmpty() const`
- L513 _public function_ `const NodeArray& GetChildren() const`
- L514 _public function_ `NodeArray& AccessChildren()`
- L515 _public function_ `NodeArray TakeChildren()`
- L523 _public function_ `TNodePtr<Node> GetRightmostChild() const`
- L529 _public function_ `Node* AccessParent()`
- L530 _public function_ `TNodeRef<Node> GetSharedSelf()`
- L531 _public function_ `TNodeRef<Node> GetSharedSelf() const`
- L532 _public function_ `const Node* GetParent() const`
- L533 _public function_ `void SetParentInternal(TNodeRef<Node> InParent)`
- L534 _public function_ `bool HasParent() const`
- L539 _public function_ `template<class Type> const Type* GetParentOfType() const`
- L552 _public function_ `bool IsElementType(NodeType InType) const`
- L554 _public prototype_ `const CAtom* AsAtomNullable() const;`
- L556 _public function_ `bool IsChildElementType(int32_t idx, NodeType InType) const`
- L558 _public function_ `bool IsError() const`
- L560 _public function_ `void DebugOrphanCheck()`
- L568 _public function_ `bool Contains(const Node& Target, const bool bRecursive = true) const`
- L617 _public function_ `int32_t FindPreviousSibling()`
- L641 _public function_ `const TNodeRef<Node>& AppendChild(const TNodeRef<Node>& child)`
- L650 _public function_ `const TNodeRef<Node>& AppendChild(const TNodeRef<Node>&& child)`
- L659 _public function_ `const TNodeRef<Node>& AppendChildAt(const TNodeRef<Node>& child, int32_t idx)`
- L668 _public function_ `void SetChildAt(int32_t Index, TNodeRef<Node> Child)`
- L676 _public function_ `TNodeRef<Node> TakeChildAt(int32_t idx, const TNodePtr<Node> Replacement = TNodePtr<Node>())`
- L692 _public function_ `void AppendChildren(const NodeArray& Children, int32_t NumToAppend = -1)`
- L705 _public function_ `void PrependChildren(const uLang::TArray<TNodeRef<Node>>& Children, int32_t NumToAppend = -1)` — Prepend the given nodes to this node's child list in reverse order i.e. the last node in the given list will end up as the first child of this node.
- L716 _public prototype_ `void ReplaceSelfWith(const TNodeRef<Node>& replacement);`
- L719 _public prototype_ `bool RemoveFromParent(int32_t idx = uLang::IndexNone);` — Supply an index if you have one
- L721 _public function_ `void Empty()`
- L734 _public function_ `const Snippet* FindSnippet() const`
- L739 _public function_ `Node* FindRoot()`
- L750 _public function_ `static void TransferChildren(const TNodeRef<Node>& From, const TNodeRef<Node>& To, int32_t First, int32_t Last)`
- L766 _public function_ `static void TransferChildren(const TNodeRef<Node>& From, const TNodeRef<Node>& To)`
- L771 _public function_ `static void TransferPrefixComments(const TNodeRef<Node>& From, const TNodeRef<Node>& To)`
- L784 _public function_ `static void TransferPostfixComments(const TNodeRef<Node>& From, const TNodeRef<Node>& To)`
- L797 _public function_ `const uLang::CAstNode* GetMappedAstNode() const`
- L798 _public prototype_ `void AddMapping(uLang::CAstNode* AstNode) const;`
- L799 _public prototype_ `static void RemoveMapping( uLang::CAstNode* AstNode );`
- L801 _public prototype_ `void EnsureAuxAllocated();`
- L803 _public function_ `void SetTile(FTile* Tile)`
- L808 _public function_ `FTile* GetTile()`
- L813 _public prototype_ `virtual TNodeRef<Node> CloneNode() const;`
- L814 _public prototype_ `void CloneNodeFields(Node* DestOther) const;`
- L828 _protected function_ `static const Node* FindOrphanedNode(const Node& InNode)` — Checks for any nodes that have their parent set incorrectly within the hierarchy. @param Root 	A pointer to the root of the tree to inspect for any orphaned nodes. @return 		A  pointer to the first node that was found to have an incorrect parent set. If no such node was found, returns `nullptr`.
- L861 _protected function_ `void DropParent(const TNodeRef<Node>& Child)` — Validates that the child being added to this node is currently orphaned. If the child has a parent, then two nodes would own the same child, which is impossible.
- L873 _protected function_ `void AppendChildInternal(const TNodeRef<Node>& child)`
- L883 _protected function_ `void AppendChildInternal(TNodeRef<Node>&& child)`
- L893 _protected member_ `NodeArray _Children;`
- L895 _protected member_ `Node* _Parent;` — VstNodes point at their parent. We guarantee that a VstNode can only exist in one place in the Vst tree at a time, so the Parent<->Child relationship is unique.
- L897 _protected member_ `TNodePtr<Clause> _Aux;` — Auxiliary data such as attributes associated with this VstNode. The transaction system addresses this via child index -1.
- L900 _protected member_ `NodeArray _PreComments;` — list of comment nodes that appear before or after this node
- L901 _protected member_ `NodeArray _PostComments;`
- L909 _protected member_ `SLocus _Whence;` — Text location from whence this node was parsed. (1) must be contained in (= not be partially outside of) parent's _Whence; (2) must not overlap any sibling's _Whence; (3) snippets (text files), programs, and some modules will not have a valid locus
- L912 _protected member_ `int32_t _NumNewLinesBefore;` — The number of trailing newlines that should follow this node.
- L913 _protected member_ `int32_t _NumNewLinesAfter;`
- L916 _protected member_ `uint8_t _Tag;` — Describes the role of this node in the context of its parent. e.g. Children of BinaryOpAddSub are tagged as `Operator` or `Operand`
- L918 _protected member_ `NodeType _Type;` — Runtime type information about this node
- L919 _protected member_ `mutable uint32_t _RefCount = 0;`
- L920 _protected member_ `mutable const uLang::CAstNode* _MappedAstNode;`
- L921 _protected member_ `FTile* _Tile;`
- L927 _private function_ `void Reference() const`
- L928 _private function_ `bool Dereference() const`
- L2202 _function_ `template <class VisitPolicy, typename ReturnType> void Node::VisitWith(const TNodeRef<Node>& node, VisitPolicy& visit_policy)`

#### struct `Verse::Vst::Node::Contains::FVstContains_Visitor`  
`struct FVstContains_Visitor`  
_L570-594_
- L572 _public function_ `static bool Contains(const TNodeRef<Node>& Root, const Node& RecursiveTarget)`

#### struct `Verse::Vst::Node::FindOrphanedNode::SChildParent`  
`struct SChildParent`  
_L830-834_
- L832 _public member_ `const Node* _Child;`
- L833 _public member_ `const Node* _Parent;`

#### struct `Verse::Vst::Clause`  
`struct Clause : public Node`  
_L937-1008_
- inherits: `Node`
- L939 _public member_ `static const Vst::NodeType StaticType = NodeType::Clause;`
- L962 _public function_ `Clause(const SLocus& Whence, const EForm Form, const EPunctuation Punctuation) : Node(StaticType, Whence), _Form(Form), _Punctuation(Punctuation)`
- L964 _public function_ `Clause(const SLocus& Whence, const EForm Form) : Node(StaticType, Whence), _Form(Form), _Punctuation(EPunctuation::Unknown)`
- L966 _public function_ `Clause(uint8_t ClauseType, const SLocus& Whence, EForm Form) : Node(StaticType, Whence), _Form(Form), _Punctuation(EPunctuation::Unknown)`
- L971 _public function_ `Clause(const TNodeRef<Node>& Child, const SLocus& Whence, EForm Form) : Clause(0, Whence, Form)`
- L976 _public function_ `Clause(const NodeArray& Children, const SLocus& Whence, EForm Form) : Clause(0, Whence, Form)`
- L981 _public function_ `Clause(const NodeArray& Children, int32_t NumToAdd, const SLocus& Whence, EForm Form) : Clause(0, Whence, Form)`
- L986 _public function_ `EForm GetForm() const`
- L987 _public function_ `void SetForm(const EForm InForm)`
- L992 _public function_ `EPunctuation GetPunctuation() const`
- L996 _public function_ `void SetPunctuation(const EPunctuation InPunctuation)`
- L1001 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1004 _private member_ `EForm _Form;`
- L1007 _private member_ `EPunctuation _Punctuation;` — Tells us whether the clause should be using either colon and newlines, or curly braces and semicolons to separate expressions.

#### enum `Verse::Vst::Clause::EForm`  
`enum class EForm : int8_t`  
_L940-952_
- L942 _public enumerator_ `Synthetic` — The clause doesn't occur in source, but is instead used as a way to group multiple subexpressions.
- L943 _public enumerator_ `NoSemicolonOrNewline` — The clause does not contains a semicolon or a newline: x or {x} or {x,y} but not {x;}
- L944 _public enumerator_ `HasSemicolonOrNewline` — The clause does contain a semicolon or a newline: {x;} or {x;y,z} or \n\tx
- L948 _public enumerator_ `IsPrependAttributeHolder` — Used for clauses that have a single attribute identifier VST node within it. This means the clause should use angle brackets (i.e. `<`/`>`) instead of curly braces. This also means that the clause is before the identifier (i.e. `<@custom_attribute>identifier`).
- L951 _public enumerator_ `IsAppendAttributeHolder` — Used for clauses that have a single attribute identifier VST node within it. This means the clause should use angle brackets (i.e. `<`/`>`) instead of curly braces. This also means that the clause is after the identifier (i.e. `class<pure>`).

#### enum `Verse::Vst::Clause::EPunctuation`  
`enum class EPunctuation : int8_t`  
_L954-960_
- L956 _public enumerator_ `Unknown`
- L957 _public enumerator_ `Braces`
- L958 _public enumerator_ `Colon`
- L959 _public enumerator_ `Indentation`

#### class `Verse::Vst::CAtom`  
`class CAtom : public Node`  
_L1016-1031_
- inherits: `Node`
- desc: Syntax element that does not need children. These nodes do not have a structure (i.e. no children), but rather are leaves in the hierarchy.
- L1022 _public member_ `CUTF8String _OriginalCode;`
- L1026 _public function_ `CAtom(const uLang::CUTF8StringView& CodeStr, NodeType InType, const SLocus& Whence) : Node(InType, Whence), _OriginalCode(CodeStr)`
- L1028 _public function_ `const string& GetStringValue() const`
- L1029 _public function_ `const CUTF8String& GetSourceText() const`
- L1030 _public function_ `const char* GetSourceCStr() const`

#### struct `Verse::Vst::Comment`  
`struct Comment : public CAtom`  
_L1033-1044_
- inherits: `CAtom`
- L1037 _public member_ `static const Vst::NodeType StaticType = NodeType::Comment;`
- L1039 _public function_ `Comment(EType Type, const CUTF8StringView& InText, const SLocus& Whence) : CAtom(InText, StaticType, Whence), _Type(Type)`
- L1041 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1043 _public member_ `EType _Type;`

#### enum `Verse::Vst::Comment::EType`  
`enum class EType : uint8_t`  
_L1035-1035_
- L1035 _public enumerator_ `enum class EType : uint8_t { block, line, ind, frag }; static const Vst::NodeType StaticType = NodeType::Comment; Comment(EType Type, const CUTF8StringView& InText, const SLocus& Whence) : CAtom(InText, StaticType, Whence)`
- L1035 _public enumerator_ `enum class EType : uint8_t { block, line, ind, frag }; static const Vst::NodeType StaticType = NodeType::Comment; Comment(EType Type, const CUTF8StringView& InText, const SLocus& Whence) : CAtom(InText, StaticType, Whence)`
- L1035 _public enumerator_ `enum class EType : uint8_t { block, line, ind, frag }; static const Vst::NodeType StaticType = NodeType::Comment; Comment(EType Type, const CUTF8StringView& InText, const SLocus& Whence) : CAtom(InText, StaticType, Whence)`
- L1035 _public enumerator_ `enum class EType : uint8_t { block, line, ind, frag }; static const Vst::NodeType StaticType = NodeType::Comment; Comment(EType Type, const CUTF8StringView& InText, const SLocus& Whence) : CAtom(InText, StaticType, Whence)`

#### struct `Verse::Vst::Snippet`  
`struct Snippet : public Node`  
_L1049-1085_
- inherits: `Node`
- desc: A collection of sub trees that are stored in the same source, e.g. a text file or UProperty
- L1051 _public member_ `static const Vst::NodeType StaticType = NodeType::Snippet;`
- L1052 _public function_ `Snippet() : Node(StaticType)`
- L1053 _public function_ `Snippet(const CUTF8StringView& Path) : Node(StaticType), _Path(Path)`
- L1054 _public function_ `Snippet(const CUTF8StringView& Path, const TNodeRef<Node>& FirstChild) : Node(StaticType, FirstChild->Whence()), _Path(Path)`
- L1055 _public function_ `Snippet(const TNodeRef<Node>& FirstChild) : Node(StaticType, FirstChild->Whence())`
- L1057 _public function_ `bool HasErrors() const`
- L1071 _public function_ `Clause::EForm GetForm() const`
- L1072 _public function_ `void SetForm(Clause::EForm Form)`
- L1074 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1075 _public prototype_ `void CloneNodeFields(Snippet* DestNode) const;`
- L1078 _public member_ `uint64_t _SnippetVersion = 0;` — A place to remember what source version this snippet represents.
- L1081 _public member_ `CUTF8String _Path;` — Where this snippet came from - usually this is the fully qualified path of the associated text file
- L1084 _private member_ `Clause::EForm _Form{Clause::EForm::Synthetic};`

#### struct `Verse::Vst::Module`  
`struct Module : public Node`  
_L1088-1101_
- inherits: `Node`
- desc: A collection of snippets
- L1090 _public member_ `static const Vst::NodeType StaticType = NodeType::Module;`
- L1091 _public function_ `Module(const CUTF8StringView& Name) : Node(StaticType), _Name(Name)`
- L1093 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1094 _public prototype_ `void CloneNodeFields(Module* DestNode) const;`
- L1097 _public member_ `CUTF8String _Name;` — The name of this module
- L1100 _public member_ `CUTF8String _FilePath;` — File path of vmodule file if exists, or directory path with trailing slash

#### struct `Verse::Vst::Package`  
`struct Package : public Node`  
_L1104-1163_
- inherits: `Node`
- desc: A collection of Module nodes
- L1106 _public member_ `static const Vst::NodeType StaticType = NodeType::Package;`
- L1108 _public function_ `Package(const CUTF8StringView& Name) : Node(StaticType), _Name(Name), _DependencyPackages()`
- L1112 _public member_ `CUTF8String _Name;` — The name of this package
- L1115 _public member_ `CUTF8String _DirPath;` — Directory path where the source files are located
- L1118 _public member_ `CUTF8String _FilePath;` — File path of vpackage file if exists, empty otherwise
- L1121 _public member_ `CUTF8String _VersePath;` — Verse path of the root module of this package
- L1124 _public member_ `LArray<CUTF8String> _DependencyPackages;` — Names of packages this package is dependent on
- L1127 _public member_ `uLang::TOptional<CUTF8String> _VniDestDir;` — Destination directory for VNI generated C++ code (fully qualified)
- L1130 _public member_ `uLang::EPackageRole _Role = uLang::EPackageRole::Source;` — The role this package plays in the project.
- L1133 _public member_ `EVerseScope _VerseScope = EVerseScope::PublicUser;` — Origin/visibility of Verse code in this package
- L1136 _public member_ `uLang::TOptional<uint32_t> _VerseVersion;` — The language version targetted by the Verse code in this package.
- L1144 _public member_ `uint32_t _UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest;` — This allows us to determine when a package was uploaded for a given Fortnite release version. It is a HACK that conditionally enables/disables behaviour in the compiler in order to support previous mistakes allowed to slip through in previous Verse langauge releases but now need to be supported for backwards compatability. When we can confirm that all Fortnite packages that are currently uploaded are beyond this version being used in all instances of the codebase, this can then be removed.
- L1147 _public member_ `bool _bTreatModulesAsImplicit = false;` — If true, module macros in this package's source and digest will be treated as implicit
- L1150 _public member_ `bool _bAllowExperimental = false;` — Whether to allow the use of experimental definitions in this package.
- L1153 _public member_ `bool _bEnableSceneGraph = false;` — Whether Scene Graph is enabled or not. Impacts the asset digest generated.
- L1156 _public member_ `bool _bEnableSceneGraphAnimation = false;` — Whether Scene Graph Animation is enabled or not. Impacts the asset digest generated.
- L1158 _public prototype_ `TNodeRef<Module> FindOrAddModule(const CUTF8StringView& ModuleName, const CUTF8StringView& ParentModuleName = CUTF8StringView());`
- L1159 _public prototype_ `static uLang::TOptional<TNodeRef<Module>> FindModule(const Node& ModuleContainer, const CUTF8StringView& ModuleName);`
- L1161 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1162 _public prototype_ `void CloneNodeFields(Package* DestNode) const;`

#### struct `Verse::Vst::Project`  
`struct Project : public Node`  
_L1167-1266_
- inherits: `Node`
- desc: A collection of Package nodes Packages (children) are sorted in dependency order (i.e. dependents always follow their dependencies)
- L1169 _public member_ `static const Vst::NodeType StaticType = NodeType::Project;`
- L1170 _public function_ `Project(const CUTF8StringView& Name) : Node(StaticType), _Name(Name)`
- L1173 _public member_ `CUTF8String _Name;` — The name of this project
- L1176 _public member_ `CUTF8String _FilePath;` — File path of vproject file if exists, empty otherwise
- L1178 _public prototype_ `const TNodeRef<Module>& FindOrAddModule(const CUTF8StringView& ModuleName, const CUTF8StringView& FilePath, const CUTF8StringView& ParentModuleName = CUTF8StringView());`
- L1179 _public prototype_ `static uLang::TOptional<TNodeRef<Module>> FindModule(const Node& ModuleContainer, const CUTF8StringView& ModuleName);`
- L1189 _public function_ `bool RemovePackagesWithName(const CUTF8StringView& PackageName)` — Removes any packages from the project that have the given name. @param PackageName   Any package that has this name in the project will be removed. @return              `true` if any packages were removed, `false` if no packages with the name were found or another error occurred.
- L1216 _public function_ `bool ReplaceSnippet(const CUTF8StringView& PathOfOldSnippetToReplace, TNodeRef<Snippet> NewSnippet, TNodePtr<Snippet>* OutOldSnippet = nullptr)`
- L1264 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1265 _public prototype_ `void CloneNodeFields(Project* DestNode) const;`

#### struct `Verse::Vst::Definition`  
`struct Definition : public Node`  
_L1298-1318_
- inherits: `Node`
- desc: Corresponds to `$1:$2 = $3` syntax, where the `$2` is optional.  If and only if `$2` is present, the left-hand side is a `TypeSpec`.  For example, @code X:int = Y @endcode becomes @code Definition TypeSpec Identifier X Identifier int Identifier Y @endcode whereas @code X := Y @endcode becomes @code Definition Identifier X Identifier Y @endcode
- L1300 _public member_ `static const Vst::NodeType StaticType = NodeType::Definition;`
- L1302 _public function_ `Definition(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1310 _public function_ `Definition(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1314 _public function_ `const TNodeRef<Node>& GetOperandLeft() const`
- L1315 _public function_ `const TNodeRef<Node>& GetOperandRight() const`
- L1317 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Assignment`  
`struct Assignment : public Node`  
_L1338-1361_
- inherits: `Node`
- desc: Corresponds to `set $1 $op $2` syntax.  The left-hand side will always be a `Mutation` node.  `$op` may be `=`, `+=`, `-=`, `*=`, or `/=` - importantly, not `:=`.  For example, @code set X = Y @endcode becomes @code Assignment Mutation Set Identifier X Identifier Y @endcode
- L1340 _public member_ `static const Vst::NodeType StaticType = NodeType::Assignment;`
- L1343 _public function_ `Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence)`
- L1353 _public function_ `Assignment(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1357 _public function_ `const TNodeRef<Node>& GetOperandLeft() const`
- L1358 _public function_ `const TNodeRef<Node>& GetOperandRight() const`
- L1360 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::Assignment::EOp`  
`enum class EOp : uint8_t`  
_L1341-1341_
- L1341 _public enumerator_ `enum class EOp : uint8_t { assign, addAssign, subAssign, mulAssign, divAssign }; Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); rhs->SetTag(static_cast<uint8_t>(InOp));`
- L1341 _public enumerator_ `enum class EOp : uint8_t { assign, addAssign, subAssign, mulAssign, divAssign }; Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); rhs->SetTag(static_cast<uint8_t>(InOp));`
- L1341 _public enumerator_ `enum class EOp : uint8_t { assign, addAssign, subAssign, mulAssign, divAssign }; Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); rhs->SetTag(static_cast<uint8_t>(InOp));`
- L1341 _public enumerator_ `enum class EOp : uint8_t { assign, addAssign, subAssign, mulAssign, divAssign }; Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); rhs->SetTag(static_cast<uint8_t>(InOp));`
- L1341 _public enumerator_ `enum class EOp : uint8_t { assign, addAssign, subAssign, mulAssign, divAssign }; Assignment(const SLocus& Whence, const TNodeRef<Node>& lhs, EOp InOp, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); rhs->SetTag(static_cast<uint8_t>(InOp));`

#### struct `Verse::Vst::FlowIf`  
`struct FlowIf : public Node`  
_L1404-1419_
- inherits: `Node`
- desc: Conditional flow control with failure context in test condition. Children are Clause block nodes in the following order: - if_identifier ] - condition      |- Repeating - [then_body]   ] - [else_body]   -- Optional last node If Identifier blocks - must be present and is simply an empty Clause meant to hold information about comments surrounding the 'if' identifier in the original source code Condition blocks - must be present (they cannot be omitted - there must be at least 1) and they must have 1 or more expressions where 1 or more of the expressions can fail. Any local variables within it's top scope are made available to any immediately following then block. Then blocks - are optional (they can be omitted) and when present must follow a conditional block and may have zero (can be empty) or more expressions. Else block - is optional (it can be omitted) and when present must follow a conditional or then block (it cannot be the only block), must be the last block and it may have zero (can be empty) or more expressions. Chained `else if` are automatically flattened into a single FlowIf node with multiple condition/[then] block pairs followed by an optional else block. An `if` may be used as an expression with a result if all the control flow paths have a common result - i.e. it will have a result if every condition is paired with a then block and there is an ending else block and all the then blocks and else block have a most common result type.
- L1406 _public member_ `static const Vst::NodeType StaticType = NodeType::FlowIf;`
- L1411 _public function_ `FlowIf(const SLocus& Whence) : Node(StaticType, Whence)`
- L1413 _public function_ `void AddIfIdentifier(const TNodeRef<Node>& Child)`
- L1414 _public function_ `void AddCondition(const TNodeRef<Node>& Child)`
- L1415 _public function_ `void AddBody(const TNodeRef<Node>& Child)`
- L1416 _public function_ `void AddElseBody(const TNodeRef<Node>& Child)`
- L1418 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::FlowIf::ClauseTag`  
`enum class ClauseTag : uint8_t`  
_L1409-1409_
- desc: Tags for different kinds of clause block children.
- L1409 _public enumerator_ `enum class ClauseTag : uint8_t { if_identifier, condition, then_body, else_body }; FlowIf(const SLocus& Whence) : Node(StaticType, Whence) {} void AddIfIdentifier(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::if_identifier)); AppendChildInternal(Child); } void AddCondition(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::condition)); AppendChildInternal(Child); } void AddBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::then_body)); AppendChildInternal(Child); } void AddElseBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::else_body)); AppendChildInternal(Child); }` — Tags for different kinds of clause block children.
- L1409 _public enumerator_ `enum class ClauseTag : uint8_t { if_identifier, condition, then_body, else_body }; FlowIf(const SLocus& Whence) : Node(StaticType, Whence) {} void AddIfIdentifier(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::if_identifier)); AppendChildInternal(Child); } void AddCondition(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::condition)); AppendChildInternal(Child); } void AddBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::then_body)); AppendChildInternal(Child); } void AddElseBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::else_body)); AppendChildInternal(Child); }` — Tags for different kinds of clause block children.
- L1409 _public enumerator_ `enum class ClauseTag : uint8_t { if_identifier, condition, then_body, else_body }; FlowIf(const SLocus& Whence) : Node(StaticType, Whence) {} void AddIfIdentifier(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::if_identifier)); AppendChildInternal(Child); } void AddCondition(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::condition)); AppendChildInternal(Child); } void AddBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::then_body)); AppendChildInternal(Child); } void AddElseBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::else_body)); AppendChildInternal(Child); }` — Tags for different kinds of clause block children.
- L1409 _public enumerator_ `enum class ClauseTag : uint8_t { if_identifier, condition, then_body, else_body }; FlowIf(const SLocus& Whence) : Node(StaticType, Whence) {} void AddIfIdentifier(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::if_identifier)); AppendChildInternal(Child); } void AddCondition(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::condition)); AppendChildInternal(Child); } void AddBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::then_body)); AppendChildInternal(Child); } void AddElseBody(const TNodeRef<Node>& Child) { Child->SetTag(static_cast<uint8_t>(ClauseTag::else_body)); AppendChildInternal(Child); }` — Tags for different kinds of clause block children.

#### struct `Verse::Vst::BinaryOpLogicalOr`  
`struct BinaryOpLogicalOr : public Node`  
_L1421-1441_
- inherits: `Node`
- L1423 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpLogicalOr;`
- L1424 _public function_ `BinaryOpLogicalOr(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1433 _public function_ `BinaryOpLogicalOr(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1438 _public function_ `void AppendChild(const TNodeRef<Node>& Rhs)`
- L1440 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOpLogicalAnd`  
`struct BinaryOpLogicalAnd : public Node`  
_L1443-1463_
- inherits: `Node`
- L1445 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpLogicalAnd;`
- L1446 _public function_ `BinaryOpLogicalAnd(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1455 _public function_ `BinaryOpLogicalAnd(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1460 _public function_ `void AppendChild(const TNodeRef<Node>& Rhs)`
- L1462 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::PrefixOpLogicalNot`  
`struct PrefixOpLogicalNot : public Node`  
_L1465-1483_
- inherits: `Node`
- L1467 _public member_ `static const Vst::NodeType StaticType = NodeType::PrefixOpLogicalNot;`
- L1468 _public function_ `PrefixOpLogicalNot( const SLocus& Whence, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1475 _public function_ `PrefixOpLogicalNot(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1480 _public function_ `const TNodeRef<Node>& GetInnerNode() const`
- L1482 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOpCompare`  
`struct BinaryOpCompare : public Node`  
_L1485-1511_
- inherits: `Node`
- L1487 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpCompare;`
- L1491 _public function_ `BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence)`
- L1501 _public function_ `BinaryOpCompare(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1506 _public function_ `TNodeRef<Node> GetOperandLeft() const`
- L1507 _public function_ `TNodeRef<Node> GetOperandRight() const`
- L1508 _public function_ `op GetOp() const`
- L1510 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::BinaryOpCompare::op`  
`enum class op : uint8_t`  
_L1489-1489_
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`
- L1489 _public enumerator_ `enum class op : uint8_t { lt, lteq, gt, gteq, eq, noteq }; BinaryOpCompare(const SLocus& Whence, const TNodeRef<Node>& lhs, op in_op, const TNodeRef<Node>& rhs) : Node(StaticType, Whence) { _Children.Reserve(2); AppendChildInternal(lhs); AppendChildInternal(rhs);`

#### struct `Verse::Vst::Where`  
`struct Where : Node`  
_L1541-1580_
- inherits: `Node`
- L1543 _public member_ `static const NodeType StaticType = NodeType::Where;`
- L1545 _public typedef_ `using RhsView = uLang::TRangeView<const TNodeRef<Node>*, const TNodeRef<Node>*>;`
- L1547 _public function_ `Where(const SLocus& Whence, const TNodeRef<Node>& Lhs, const NodeArray& RhsArray) : Node(StaticType, Whence)`
- L1559 _public function_ `Where(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1564 _public function_ `TNodeRef<Node> GetLhs() const`
- L1569 _public function_ `void SetLhs(TNodeRef<Node> Lhs)`
- L1574 _public function_ `RhsView GetRhs() const`
- L1579 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Mutation`  
`struct Mutation : Node`  
_L1582-1620_
- inherits: `Node`
- L1584 _public member_ `static const NodeType StaticType = NodeType::Mutation;`
- L1593 _public function_ `Mutation(const SLocus& Whence, const TNodeRef<Node>& Child, EKeyword Keyword, bool bLive) : Node(StaticType, Whence) , _Keyword(Keyword) , _bLive(bLive)`
- L1603 _public function_ `Mutation(const SLocus& Whence, EKeyword Keyword, bool bLive) : Node(StaticType, Whence) , _Keyword(Keyword) , _bLive(bLive)` — cloning
- L1610 _public function_ `TNodeRef<Node> Child() const`
- L1615 _public member_ `EKeyword _Keyword;`
- L1617 _public member_ `bool _bLive;`
- L1619 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::Mutation::EKeyword`  
`enum class EKeyword : uint8_t`  
_L1586-1591_
- L1588 _public enumerator_ `Var`
- L1589 _public enumerator_ `Set`
- L1590 _public enumerator_ `Live`

#### struct `Verse::Vst::TypeSpec`  
`struct TypeSpec : public Node`  
_L1622-1674_
- inherits: `Node`
- L1624 _public member_ `static const Vst::NodeType StaticType = NodeType::TypeSpec;`
- L1627 _public member_ `NodeArray _TypeSpecComments;` — comments that go after the ':' of the typespec
- L1629 _public function_ `TypeSpec(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(NodeType::TypeSpec, Whence) , _TypeSpecComments()`
- L1638 _public function_ `TypeSpec(const SLocus& Whence, const TNodeRef<Node>& Rhs) : Node(NodeType::TypeSpec, Whence) , _TypeSpecComments()`
- L1647 _public function_ `TypeSpec(const SLocus& Whence) : Node(NodeType::TypeSpec, Whence) , _TypeSpecComments()` — cloning
- L1654 _public function_ `bool HasLhs() const`
- L1655 _public function_ `TNodeRef<Node> GetLhs() const`
- L1656 _public function_ `TNodeRef<Node> TakeLhs()`
- L1657 _public function_ `TNodeRef<Node> GetRhs() const`
- L1658 _public function_ `TNodeRef<Node> TakeRhs()`
- L1660 _public function_ `void AppendTypeSpecComment(const TNodeRef<Node>& NewComment)`
- L1666 _public function_ `void AppendTypeSpecComment(TNodeRef<Node>&& NewComment)`
- L1672 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1673 _public prototype_ `void CloneNodeFields(TypeSpec* DestNode) const;`

#### struct `Verse::Vst::Identifier`  
`struct Identifier : public CAtom`  
_L1676-1716_
- inherits: `CAtom`
- L1678 _public member_ `static const Vst::NodeType StaticType = NodeType::Identifier;`
- L1681 _public member_ `NodeArray _QualifierPostComments;` — Comments that are to be suffixed to the qualifiers of this identifier.
- L1684 _public member_ `NodeArray _QualifierPreComments;` — Comments that are to be prefixed to the qualifiers of this identifier.
- L1686 _public function_ `Identifier(const CUTF8StringView& InName, const SLocus& Whence, const bool bCanBeQualified) : CAtom(InName, StaticType, Whence) , _QualifierPostComments() , _QualifierPreComments() , _bCanBeQualified(bCanBeQualified)`
- L1691 _public function_ `Identifier(const CUTF8StringView& InName, const SLocus& Whence) : CAtom(InName, StaticType, Whence) , _QualifierPostComments() , _QualifierPreComments() , _bCanBeQualified(true)`
- L1697 _public function_ `void SetCanBeQualified(const bool bCanBeQualified)`
- L1698 _public function_ `bool CanBeQualified() const`
- L1699 _public function_ `bool IsQualified() const`
- L1700 _public function_ `const TNodeRef<Node>& GetQualification() const`
- L1709 _public prototype_ `bool AddQualifier(const uLang::CUTF8StringView& InQualifier);` — Adds a qualifier if un-qualified. @param InQualifier 	The text of the qualification to add. @return 			`true` if the qualification succeeded, or `false` if a qualifier was already present.
- L1711 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1712 _public prototype_ `void CloneNodeFields(Identifier* DestNode) const;`
- L1715 _private member_ `bool _bCanBeQualified;`

#### struct `Verse::Vst::Operator`  
`struct Operator : public CAtom`  
_L1718-1726_
- inherits: `CAtom`
- L1720 _public member_ `static const Vst::NodeType StaticType = NodeType::Operator;`
- L1722 _public function_ `Operator(const CUTF8StringView& InSourceText, const SLocus& Whence) : CAtom(InSourceText, StaticType, Whence)`
- L1725 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOp`  
`struct BinaryOp : public Node`  
_L1728-1755_
- inherits: `Node`
- L1732 _public function_ `BinaryOp(const SLocus& Whence, Vst::NodeType NodeType) : Node(NodeType, Whence)`
- L1733 _public function_ `BinaryOp(const SLocus& Whence, const TNodeRef<Node>& LhsOperand, Vst::NodeType NodeType) : Node(NodeType, Whence)`
- L1740 _public function_ `void AppendChild(op in_op, const TNodeRef<Node> in_child)`
- L1747 _protected function_ `void AppendOperation_Internal(const TNodeRef<Node>& InOperator, const TNodeRef<Node>& Operand)`

#### enum `Verse::Vst::BinaryOp::op`  
`enum class op : uint8_t`  
_L1730-1730_
- L1730 _public enumerator_ `enum class op : uint8_t { Operator, Operand }; BinaryOp(const SLocus& Whence, Vst::NodeType NodeType) : Node(NodeType, Whence) {} BinaryOp(const SLocus& Whence, const TNodeRef<Node>& LhsOperand, Vst::NodeType NodeType) : Node(NodeType, Whence) { LhsOperand->SetTag((uint8_t)op::Operand); AppendChildInternal(LhsOperand);`
- L1730 _public enumerator_ `enum class op : uint8_t { Operator, Operand }; BinaryOp(const SLocus& Whence, Vst::NodeType NodeType) : Node(NodeType, Whence) {} BinaryOp(const SLocus& Whence, const TNodeRef<Node>& LhsOperand, Vst::NodeType NodeType) : Node(NodeType, Whence) { LhsOperand->SetTag((uint8_t)op::Operand); AppendChildInternal(LhsOperand);`

#### struct `Verse::Vst::BinaryOpAddSub`  
`struct BinaryOpAddSub : public BinaryOp`  
_L1757-1771_
- inherits: `BinaryOp`
- L1759 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpAddSub;`
- L1761 _public function_ `BinaryOpAddSub(const SLocus& Whence) : BinaryOp(Whence, StaticType)`
- L1762 _public function_ `BinaryOpAddSub(const SLocus& Whence, const TNodeRef<Node>& LhsOperand) : BinaryOp(Whence, LhsOperand, StaticType)`
- L1767 _public prototype_ `void AppendAddOperation(const SLocus& AddWhence, const TNodeRef<Node>& RhsOperand);`
- L1768 _public prototype_ `void AppendSubOperation(const SLocus& SubWhence, const TNodeRef<Node>& RhsOperand);`
- L1770 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOpMulDivInfix`  
`struct BinaryOpMulDivInfix : public BinaryOp`  
_L1773-1792_
- inherits: `BinaryOp`
- L1775 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpMulDivInfix;`
- L1777 _public function_ `BinaryOpMulDivInfix(const SLocus& Whence) : BinaryOp(Whence, StaticType)`
- L1778 _public function_ `BinaryOpMulDivInfix(const SLocus& Whence, const TNodeRef<Node>& LhsOperand) : BinaryOp(Whence, LhsOperand, StaticType)`
- L1783 _public function_ `void AppendInfixOperation(const TNodeRef<Identifier>& OpIdentifier, const TNodeRef<Node>& RhsOperand)`
- L1788 _public prototype_ `void AppendMulOperation(const SLocus& MulWhence, const TNodeRef<Node>& RhsOperand);`
- L1789 _public prototype_ `void AppendDivOperation(const SLocus& DivWhence, const TNodeRef<Node>& RhsOperand);`
- L1791 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOpRange`  
`struct BinaryOpRange : public Node`  
_L1794-1814_
- inherits: `Node`
- L1796 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpRange;`
- L1797 _public function_ `BinaryOpRange(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1806 _public function_ `BinaryOpRange(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1811 _public function_ `void AppendChild(const TNodeRef<Node>& Rhs)`
- L1813 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::BinaryOpArrow`  
`struct BinaryOpArrow : public Node`  
_L1816-1833_
- inherits: `Node`
- L1818 _public member_ `static const Vst::NodeType StaticType = NodeType::BinaryOpArrow;`
- L1819 _public function_ `BinaryOpArrow(const SLocus& Whence, const TNodeRef<Node>& Lhs, const TNodeRef<Node>& Rhs) : Node(StaticType, Whence)`
- L1828 _public function_ `BinaryOpArrow(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L1832 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::PrePostCall`  
`struct PrePostCall : public Node`  
_L1835-1896_
- inherits: `Node`
- L1837 _public member_ `static const Vst::NodeType StaticType = NodeType::PrePostCall;`
- L1841 _public function_ `PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence)`
- L1846 _public function_ `PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1850 _public function_ `bool IsSimpleCall() const`
- L1857 _public function_ `bool IsPostHat() const`
- L1864 _public function_ `bool IsPreQMark() const`
- L1872 _public prototype_ `TNodeRef<Clause> PrependQMark(const SLocus& Whence);`
- L1875 _public prototype_ `TNodeRef<Clause> PrependHat(const SLocus& Whence);`
- L1878 _public prototype_ `void PrependCallArgs(bool bCanFail, const TNodeRef<Clause>& Args);`
- L1881 _public prototype_ `void AppendQMark(const SLocus& Whence);`
- L1884 _public prototype_ `void AppendHat(const SLocus& Whence);`
- L1887 _public prototype_ `void AppendCallArgs(bool bCanFail, const TNodeRef<Clause>& Args);`
- L1890 _public prototype_ `void AppendDotIdent(const SLocus& Whence, const TNodeRef<Identifier>& Ident);`
- L1893 _public prototype_ `TNodePtr<Clause> TakeLastArgs();`
- L1895 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::PrePostCall::Op`  
`enum Op`  
_L1839-1839_
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`
- L1839 _public enumerator_ `enum Op { Expression, Option, Pointer, DotIdentifier, SureCall, FailCall }; PrePostCall(const TNodeRef<Node>& FirstChild, const SLocus& Whence) : Node(StaticType, Whence) { AppendChild(FirstChild); } PrePostCall(const SLocus& Whence) : Node(StaticType, Whence)`

#### struct `Verse::Vst::IntLiteral`  
`struct IntLiteral : public CAtom`  
_L1898-1905_
- inherits: `CAtom`
- L1900 _public member_ `static const Vst::NodeType StaticType = NodeType::IntLiteral;`
- L1902 _public function_ `IntLiteral(const CUTF8StringView& InSourceText, const SLocus& Whence) : CAtom(InSourceText, StaticType, Whence)`
- L1904 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::FloatLiteral`  
`struct FloatLiteral : public CAtom`  
_L1907-1927_
- inherits: `CAtom`
- L1909 _public member_ `static const Vst::NodeType StaticType = NodeType::FloatLiteral;`
- L1919 _public member_ `EFormat _Format;`
- L1921 _public function_ `FloatLiteral(const CUTF8StringView& InSourceText, EFormat Format, const SLocus& Whence) : CAtom(InSourceText, StaticType, Whence) , _Format(Format)`
- L1926 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### enum `Verse::Vst::FloatLiteral::EFormat`  
`enum class EFormat`  
_L1911-1917_
- L1913 _public enumerator_ `Unspecified`
- L1914 _public enumerator_ `F16`
- L1915 _public enumerator_ `F32`
- L1916 _public enumerator_ `F64`

#### struct `Verse::Vst::CharLiteral`  
`struct CharLiteral : public Node`  
_L1929-1954_
- inherits: `Node`
- L1931 _public member_ `static const Vst::NodeType StaticType = NodeType::CharLiteral;`
- L1942 _public member_ `EFormat _Format;`
- L1943 _public member_ `uint32_t _Value;`
- L1945 _public function_ `CharLiteral(EFormat Format, char32_t Value, const SLocus& Whence) : Node(StaticType, Whence) , _Format(Format) , _Value(Value)`
- L1951 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L1953 _public prototype_ `CUTF8String ToString() const;`

#### enum `Verse::Vst::CharLiteral::EFormat`  
`enum class EFormat`  
_L1933-1940_
- L1935 _public enumerator_ `ASCII` — 'a'
- L1936 _public enumerator_ `UnicodeScalar` — '😀'
- L1937 _public enumerator_ `UTF8CodeUnit` — 0oXX
- L1938 _public enumerator_ `UnicodeScalarCode` — 0uXXXXX
- L1939 _public enumerator_ `EscapedCode` — \t \r ...

#### struct `Verse::Vst::StringLiteral`  
`struct StringLiteral : public CAtom`  
_L1956-1965_
- inherits: `CAtom`
- L1958 _public member_ `static const Vst::NodeType StaticType = NodeType::StringLiteral;`
- L1960 _public function_ `StringLiteral( const SLocus& Whence, const CUTF8StringView& SyntaxSource) : CAtom(SyntaxSource, StaticType, Whence)`
- L1964 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::PathLiteral`  
`struct PathLiteral : public CAtom`  
_L1967-1974_
- inherits: `CAtom`
- L1969 _public member_ `static const Vst::NodeType StaticType = NodeType::PathLiteral;`
- L1971 _public function_ `PathLiteral(const CUTF8StringView& InPath, const SLocus& Whence) : CAtom(InPath, StaticType, Whence)`
- L1973 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Interpolant`  
`struct Interpolant : public CAtom`  
_L1976-1985_
- inherits: `CAtom`
- L1978 _public member_ `static const Vst::NodeType StaticType = NodeType::Interpolant;`
- L1980 _public function_ `Interpolant(const SLocus& Whence, const CUTF8StringView& SyntaxSource) : CAtom(SyntaxSource, StaticType, Whence)`
- L1984 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::InterpolatedString`  
`struct InterpolatedString : public CAtom`  
_L1987-1996_
- inherits: `CAtom`
- L1989 _public member_ `static const Vst::NodeType StaticType = NodeType::InterpolatedString;`
- L1991 _public function_ `InterpolatedString(const SLocus& Whence, const CUTF8StringView& SyntaxSource) : CAtom(SyntaxSource, StaticType, Whence)`
- L1995 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Lambda`  
`struct Lambda : public Node`  
_L1998-2020_
- inherits: `Node`
- L2000 _public member_ `static const Vst::NodeType StaticType = NodeType::Lambda;`
- L2002 _public function_ `Lambda(const SLocus& Whence, const TNodeRef<Node>& Domain, const TNodeRef<Node>& Range) : Node(StaticType, Whence)`
- L2011 _public function_ `Lambda(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L2016 _public function_ `const TNodeRef<Node>& GetDomain() const`
- L2017 _public function_ `const TNodeRef<Clause>& GetRange() const`
- L2019 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Control`  
`struct Control : public Node`  
_L2022-2049_
- inherits: `Node`
- L2024 _public member_ `static const Vst::NodeType StaticType = NodeType::Control;`
- L2034 _public function_ `Control(const SLocus& Whence, Control::EKeyword Keyword) : Node(StaticType, Whence), _Keyword(Keyword)`
- L2038 _public function_ `Control(const TNodeRef<Node>& Child, const SLocus& Whence, EKeyword Keyword) : Control(Whence, Keyword)`
- L2044 _public function_ `const TNodeRef<Node>& GetReturnExpression() const`
- L2046 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L2048 _public member_ `EKeyword _Keyword;`

#### enum `Verse::Vst::Control::EKeyword`  
`enum class EKeyword : uint8_t`  
_L2026-2032_
- L2028 _public enumerator_ `Return`
- L2029 _public enumerator_ `Break`
- L2030 _public enumerator_ `Yield`
- L2031 _public enumerator_ `Continue`

#### struct `Verse::Vst::Macro`  
`struct Macro : public Node`  
_L2053-2086_
- inherits: `Node`
- L2055 _public member_ `static const Vst::NodeType StaticType = NodeType::Macro;`
- L2057 _public function_ `Macro(SLocus Whence, const TNodeRef<Node>& MacroName, const uLang::TArray<TNodeRef<Clause>>& InChildren) : Node(StaticType, Whence)`
- L2068 _public function_ `Macro(SLocus Whence) : Node(StaticType, Whence)` — cloning
- L2072 _public function_ `const TNodeRef<Node>& GetName() const`
- L2073 _public function_ `const TNodeRef<Clause>& GetClause(int32_t ClauseIndex) const`
- L2074 _public function_ `TNodeRef<Clause> TakeClause(int32_t ClauseIndex, const TNodePtr<Node> Replacement = TNodePtr<Clause>())`
- L2079 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L2081 _public function_ `void ReplaceWith(const TNodeRef<Node>& MacroName, const TNodeRef<Clause>& Child)`

#### struct `Verse::Vst::Parens`  
`struct Parens : public Node`  
_L2088-2108_
- inherits: `Node`
- L2090 _public member_ `static const Vst::NodeType StaticType = NodeType::Parens;`
- L2092 _public function_ `Parens(SLocus Whence, Clause::EForm Form, const NodeArray& InChildren = {}) : Node(StaticType, Whence), _Form(Form)`
- L2102 _public function_ `Clause::EForm GetForm() const`
- L2104 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L2107 _private member_ `Clause::EForm _Form;`

#### struct `Verse::Vst::Commas`  
`struct Commas : Node`  
_L2110-2121_
- inherits: `Node`
- L2112 _public member_ `static const Vst::NodeType StaticType = NodeType::Commas;`
- L2114 _public function_ `Commas(SLocus Whence, const NodeArray& InChildren = {}) : Node(StaticType, Whence)`
- L2120 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::Placeholder`  
`struct Placeholder : public CAtom`  
_L2123-2131_
- inherits: `CAtom`
- L2125 _public member_ `static const Vst::NodeType StaticType = NodeType::Placeholder;`
- L2127 _public function_ `Placeholder(const SLocus& Whence) : CAtom("", StaticType, Whence)`
- L2128 _public function_ `Placeholder(const uLang::CUTF8StringView& CodeStr, const SLocus& Whence) : CAtom(CodeStr, StaticType, Whence)`
- L2130 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::Vst::ParseError`  
`struct ParseError : public Node`  
_L2133-2153_
- inherits: `Node`
- L2136 _public member_ `static const Vst::NodeType StaticType = NodeType::ParseError;`
- L2138 _public function_ `ParseError(const char* Error, const SLocus& Whence) : Node(NodeType::ParseError, Whence) , _Error(Error)`
- L2144 _public function_ `const char* GetError() const`
- L2146 _public function_ `void AddChild(const TNodeRef<Node>& InnerError)`
- L2148 _public prototype_ `TNodeRef<Node> CloneNode() const override;`
- L2151 _private member_ `const char* _Error;`

#### struct `Verse::Vst::Escape`  
`struct Escape : public Node`  
_L2155-2172_
- inherits: `Node`
- L2157 _public member_ `static const Vst::NodeType StaticType = NodeType::Escape;`
- L2159 _public function_ `Escape(const SLocus& Whence, const TNodeRef<Node>& Child) : Node(StaticType, Whence)`
- L2166 _public function_ `Escape(const SLocus& Whence) : Node(StaticType, Whence)` — cloning
- L2171 _public prototype_ `TNodeRef<Node> CloneNode() const override;`

#### struct `Verse::SPathToNode`  
`struct SPathToNode`  
_L2226-2234_
- L2228 _public member_ `LArray<int32_t> Path;`
- L2229 _public member_ `LArray<int32_t> AuxPath;`
- L2231 _public member_ `int32_t PreCommentIndex;`
- L2232 _public member_ `int32_t PostCommentIndex;`

#### enum `Verse::EPrettyPrintBehaviour`  
`enum class EPrettyPrintBehaviour : uint32_t`  
_L2236-2243_
- L2238 _public enumerator_ `Default = 0`
- L2239 _public enumerator_ `NewlinesAfterDefinitions = 1 << 0`
- L2240 _public enumerator_ `NewlinesAfterAttributes = 1 << 1`
- L2241 _public enumerator_ `NewlinesBetweenModuleMembers = 1 << 2`
- L2242 _public enumerator_ `UseVerticalFormForEnumerations = 1 << 3`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API VERSECOMPILER_API`
- L23 _namespace_ `namespace Verse`
- L25 _namespace_ `namespace Vst` (scope `Verse`)
- L197 _function_ `friend void Swap(TNodePtrG& A, TNodePtrG& B)` (scope `Verse::Vst`) — Swap support
- L201 _typedef_ `template<typename NodeType> using TNodeRef = TNodePtrG<NodeType, false, uLang::CHeapRawAllocator>;` (scope `Verse::Vst`) — Non-nullable shared reference to a Vst node. Guarantees the pointee is always valid.
- L204 _typedef_ `template<typename NodeType> using TNodePtr = TNodePtrG<NodeType, true, uLang::CHeapRawAllocator>;` (scope `Verse::Vst`) — Nullable shared pointer to a Vst node. May be null -- check before dereferencing.
- L209 _namespace_ `namespace uLang`
- L223 _namespace_ `namespace Verse`
- L227 _typedef_ `using string = uLang::CUTF8String;` (scope `Verse`)
- L228 _typedef_ `using CUTF8String = uLang::CUTF8String;` (scope `Verse`)
- L229 _typedef_ `using CUTF8StringView = uLang::CUTF8StringView;` (scope `Verse`)
- L230 _typedef_ `using CUTF8StringBuilder = uLang::CUTF8StringBuilder;` (scope `Verse`)
- L232 _typedef_ `using SIndexedSourceText = uLang::SIndexedSourceText;` (scope `Verse`)
- L234 _typedef_ `using ChType = uLang::UTF8Char;` (scope `Verse`)
- L238 _typedef_ `template<typename T> using LArray = uLang::TArray<T>;` (scope `Verse`) — uLang Types
- L240 _typedef_ `using EResult = uLang::EResult;` (scope `Verse`)
- L241 _typedef_ `using CSharedMix = uLang::CSharedMix;` (scope `Verse`)
- L242 _typedef_ `using SLocus = uLang::STextRange;` (scope `Verse`)
- L243 _typedef_ `using SPosition = uLang::STextPosition;` (scope `Verse`)
- L244 _typedef_ `using EVerseScope = uLang::EVerseScope;` (scope `Verse`)
- L246 _function_ `inline SLocus NullWhence()` (scope `Verse`)
- L251 _namespace_ `namespace Vst` (scope `Verse`)
- L272 _macro_ `#define VISIT_VSTNODE(NodeName, RequiredChildren, SupportsManyChildren, Precedence, ChildDeletionBehavior, IsCAtom) NodeName,`
- L279 _macro_ `#define VISIT_VSTNODE(NodeName, RequiredChildren, Precedence, SupportsManyChildren, ChildDeletionBehavior, IsCAtom) {#NodeName, RequiredChildren, Precedence, ESupportsManyChildren::SupportsManyChildren, EChildDeletionBehavior::ChildDeletion`
- L288 _variable_ `} NodeInfos[] = { VERSE_ENUM_VSTNODES(VISIT_VSTNODE)};` (scope `Verse::Vst`)
- L292 _variable_ `static constexpr uint8_t NumNodeTypes = static_cast<uint8_t>(ULANG_COUNTOF(NodeInfos));` (scope `Verse::Vst`)
- L294 _variable_ `static const uint8_t TagNone = 255;` (scope `Verse::Vst`)
- L296 _function_ `inline const char* GetNodeTypeName(const NodeType TypeOfNode)` (scope `Verse::Vst`)
- L301 _function_ `inline int32_t GetNumRequiredChildren(const NodeType TypeOfNode)` (scope `Verse::Vst`)
- L306 _function_ `inline int32_t GetOperatorPrecedence(const NodeType TypeOfNode)` (scope `Verse::Vst`)
- L311 _function_ `inline ESupportsManyChildren GetSupportsManyChildren(const NodeType TypeOfNode)` (scope `Verse::Vst`)
- L316 _function_ `inline EChildDeletionBehavior GetChildDeletionBehavior(const NodeType TypeOfNode)` (scope `Verse::Vst`)
- L935 _typedef_ `using NodeArray = Node::NodeArray;` (scope `Verse::Vst`)
- L1010 _prototype_ `const TNodeRef<Node> MakeStub(const SLocus& Whence);` (scope `Verse::Vst`)
- L1046 _prototype_ `const char* CommentTypeToString(Comment::EType Type);` (scope `Verse::Vst`)
- L1363 _function_ `inline const char* AssignmentOpAsCString(Assignment::EOp Op)` (scope `Verse::Vst`)
- L1513 _function_ `inline const char* BinaryCompareOpAsCString(BinaryOpCompare::op Op)` (scope `Verse::Vst`)
- L1527 _function_ `inline BinaryOpCompare::op BinaryCompareOpFlip(BinaryOpCompare::op Op)` (scope `Verse::Vst`)
- L2051 _typedef_ `using ClauseArray = LArray<TNodeRef<Clause>>;` (scope `Verse::Vst`)
- L2207 _macro_ `#define VISIT_VSTNODE(NodeName, RequiredChildren, SupportsManyChildren, Precedence, ChildDeletionBehavior, IsCAtom) \`
- L2220 _macro_ `#define VISIT_VSTNODE(NodeName, RequiredChildren, SupportsManyChildren, Precedence, ChildDeletionBehavior, IsCAtom) static_assert(NodeName::StaticType == NodeType::NodeName, #NodeName "::StaticType must be Vst::NodeType::" #NodeName);` — Verify all Vst::Node::StaticType are valid
- L2244 _prototype_ `ULANG_ENUM_BIT_FLAGS(EPrettyPrintBehaviour, inline);` (scope `Verse`)
- L2251 _prototype_ `void VstPrintAppend(const Vst::TNodeRef<Vst::Node>& VstNode, CUTF8StringBuilder& Source);` (scope `Verse`) — Appends the text code version of this syntax snippet as compilable source. @param Source string to append to @see VstSnippetAsCodeSourceChain(), VstSnippetAsCodeSource(), VstAsCodeSourceAppend()
- L2252 _function_ `inline CUTF8String PrintVst(const Vst::TNodeRef<Vst::Node>& VstNode)` (scope `Verse`)
- L2265 _prototype_ `void VstAsCodeSourceAppend(const Vst::TNodeRef<Vst::Node>& VstNode, CUTF8StringBuilder& Source);` (scope `Verse`) — Appends the text code version of this syntax snippet as closely as possible to how it was originally authored and if it was not authored in text originally (such as added via a VPL) then in as human readable canonical form as possible. @param Source string to append to @see VstSnippetAsCodeSourceChain(), VstSnippetAsCodeSource(), VstAsCodeSourceAppend()
- L2266 _prototype_ `void VstAsCodeSourceAppend(const Vst::TNodeRef<Vst::Node>& VstNode, const EPrettyPrintBehaviour Flags, CUTF8StringBuilder& Source);` (scope `Verse`)
- L2267 _prototype_ `void VstAsCodeSourceAppend(const Vst::TNodeRef<Vst::PrePostCall>& VstNode, CUTF8StringBuilder& OutSource, int32_t FirstChildIndex, int32_t LastChildIndex);` (scope `Verse`)
- L2268 _prototype_ `void VstAsCodeSourceAppend(const Vst::TNodeRef<Vst::Clause>& VstClause, CUTF8StringBuilder& OutSource, int32_t InitialIndent, CUTF8String const& Separator);` (scope `Verse`)
- L2270 _function_ `inline CUTF8String PrettyPrintVst(const Vst::TNodeRef<Vst::Node>& VstNode)` (scope `Verse`)
- L2275 _function_ `inline CUTF8String PrettyPrintVst(const Vst::TNodeRef<Vst::Node>& VstNode, const EPrettyPrintBehaviour Flags)` (scope `Verse`)
- L2280 _function_ `inline CUTF8String PrettyPrintVst(const Vst::TNodeRef<Vst::PrePostCall>& VstNode, int32_t FirstChildIndex, int32_t LastChildIndex)` (scope `Verse`)
- L2285 _function_ `inline CUTF8String PrettyPrintClause(const Vst::TNodeRef<Vst::Clause>& VstClause, int32_t InitialIndent, CUTF8String const& Separator)` (scope `Verse`)
- L2292 _prototype_ `bool GeneratePathToNode(const Vst::TNodeRef<Vst::Node>& Node, const Vst::TNodeRef<Vst::Snippet>& VstSnippet, SPathToNode& PathToNode);` (scope `Verse`)
- L2293 _prototype_ `Vst::TNodePtr<Vst::Node> GetNodeFromPath(const Vst::TNodeRef<Vst::Snippet>& VstSnippet, const SPathToNode& Path, bool bReturnParent=false);` (scope `Verse`)
- L2304 _prototype_ `int32_t GetSignedDistanceBetweenPositionAndLocus(const SLocus& A, const SPosition& B, const SIndexedSourceText& SourceText);` (scope `Verse`) — Gets the signed distance between a locus and a row/column text position. The closest distance to the locus range is used. @param A 			The locus range to compare. @param B 			The text position to compare. @param SourceText 	The original source text that both the locus and position refer to ranges of. @return 			The signed distance between the two. If A comes before B, the result is positive and vice versa.

### `Source/Runtime/VerseCompiler/Public/uLang/Syntax/vsyntax_types.h` (Public)


#### enum `vsyntax::res_t`  
`enum res_t : uint8_t`  
_L9-9_
- desc: Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum
- L9 _public enumerator_ `enum res_t : uint8_t { res_none = 0, res_of, res_if, res_else, res_upon, res_where, res_catch, res_do, res_then, res_until, res_return, res_yield, res_break, res_continue, res_at, res_var, res_set, res_and, res_or, res_not, res_max }; struct scan_reserved_t { constexpr const char* operator[](uint8_t res) const { constexpr const char* strings[] = { "", "of", "if", "else", "upon", "where", "catch", "do", "then", "until", "return", "yield", "break", "continue", "at", "var", "set", "and", "or", "not", 0}; static_assert(sizeof(strings) / sizeof(char*) == res_max + 1, "scan_reserved string table must match res_t");` — Reserved keyword enum

#### struct `vsyntax::scan_reserved_t`  
`struct scan_reserved_t`  
_L10-19_
- L12 _public function_ `constexpr const char* operator[](uint8_t res) const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace vsyntax`

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/AvailableAttributeVstFilter.h` (Public)


#### struct `uLang::SBuildVersionInfo`  
`struct SBuildVersionInfo`  
_L14-17_
- L16 _public member_ `uint32_t UploadedAtFNVersion;`

#### class `uLang::CAvailableAttributeVstFilter`  
`class CAvailableAttributeVstFilter final : public IPostVstFilter`  
_L20-38_
- inherits: `IPostVstFilter`
- desc: Filter out any symbol with a version attribute that would exclude it from the compile
- L23 _public function_ `CAvailableAttributeVstFilter()`
- L26 _public function_ `virtual void Filter(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& VstSnippet, const SBuildContext& BuildContext) override`
- L32 _public prototype_ `static void StaticFilter(const Verse::Vst::TNodeRef<Verse::Vst::Node>& VstNode, const SBuildContext& BuildContext);`
- L35 _private prototype_ `static void StaticFilterHelper(const Verse::Vst::TNodeRef<Verse::Vst::Node>& VstNode, const SBuildContext& BuildContext, const SBuildVersionInfo& BuildVersion);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VERSECOMPILER_API`
- L11 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/CommandLine.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L10 _namespace_ `namespace CommandLine` (scope `uLang`)
- L12 _prototype_ `void Init(int ArgC, char* ArgV[]);` (scope `uLang::CommandLine`)
- L13 _prototype_ `void Init(const SCommandLine& Rhs);` (scope `uLang::CommandLine`)
- L15 _prototype_ `bool IsSet();` (scope `uLang::CommandLine`)
- L16 _prototype_ `const SCommandLine& Get();` (scope `uLang::CommandLine`)

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/ModularFeature.h` (Public)


#### class `uLang::Private::IModularFeature`  
`class IModularFeature : public CSharedMix`  
_L17-22_
- inherits: `CSharedMix`
- desc: Base class for the ModularFeatures -- marked as "Private" to discourage directly sub-classing this (use TModularFeature<> instead).
- L20 _public prototype_ `virtual ~IModularFeature() = default;`
- L21 _public prototype_ `virtual int32_t GetPriority() const = 0;`

#### class `uLang::TModularFeature`  
`template<typename FeatureType> class TModularFeature : public Private::IModularFeature`  
_L30-36_
- inherits: `Private::IModularFeature`
- desc: ModularFeature base class -- all modular feature interfaces should derive from this base.
- L34 _public function_ `virtual int32_t GetPriority() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L11 _namespace_ `namespace Private` (scope `uLang`)
- L40 _macro_ `#define ULANG_FEATURE_ID_DECL(FeatureType) \` — Required to fully declare your feature class. Intended to be declared inside your class declaration. Defines the feature's name, which is used to generate its UID.

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/ModularFeatureManager.h` (Public)


#### class `uLang::TModularFeatureRegHandle`  
`template<class FeatureType> class AUTORTFM_DISABLE TModularFeatureRegHandle`  
_L18-54_
- desc: RAII style handle that wraps a ModularFeature TSPtr<>. Authoritative control for a features' registration lifetime -- sole controller for registering features. Use this to spawn and manage the lifetime of your module's ModularFeature instances.
- L22 _public prototype_ `template<typename... Args_t> TModularFeatureRegHandle(Args_t&&... Args);`
- L24 _public prototype_ `~TModularFeatureRegHandle();`
- L27 _public prototype_ `TModularFeatureRegHandle(const TModularFeatureRegHandle&) = delete;` — Prevent copying/assignment to properly control registration lifetime (since this unregisters on destruction)
- L28 _public prototype_ `TModularFeatureRegHandle& operator=(const TModularFeatureRegHandle&) = delete;`
- L30 _public function_ `TModularFeatureRegHandle(TModularFeatureRegHandle&& Other) : _ModularFeatureRef(Move(Other._ModularFeatureRef))`
- L35 _public function_ `TModularFeatureRegHandle& operator=(TModularFeatureRegHandle&& Other)`
- L42 _public function_ `operator TSRef<FeatureType>() const` — Conversion methods
- L43 _public function_ `operator FeatureType*() const`
- L44 _public function_ `FeatureType& operator*() const`
- L45 _public function_ `FeatureType* operator->() const`
- L49 _public function_ `TSRef<FeatureType>& ToSharedRef()`
- L50 _public function_ `const TSRef<FeatureType>& ToSharedRef() const`
- L53 _private member_ `TSRef<FeatureType> _ModularFeatureRef;`

#### class `uLang::TModularFeatureIterator`  
`template<class FeatureType> class TModularFeatureIterator`  
_L91-105_
- desc: Mechanism for iterating over all registered modular features of a certain type.
- L94 _public prototype_ `explicit operator bool() const;`
- L95 _public prototype_ `bool operator!() const;`
- L97 _public prototype_ `TSRef<FeatureType> Get() const;`
- L98 _public prototype_ `FeatureType& operator*() const;`
- L99 _public prototype_ `FeatureType* operator->() const;`
- L101 _public prototype_ `void operator++();`
- L104 _private member_ `int32_t _Index = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
- L63 _prototype_ `template<class FeatureType> int32_t GetModularFeatureCount();` (scope `uLang`) — Returns the number of registered implementations of the specified feature type.
- L73 _prototype_ `template<class FeatureType> TOptional< TSRef<FeatureType> > GetModularFeature(const int32_t Index = 0);` (scope `uLang`) — Queries for a specific modular feature. Returns an empty TOptional<> if the feature is not available. Does not assert. @return An optional (which could be empty if no features of the specified type are registered), wrapping a shared ModularFeature pointer.
- L82 _prototype_ `template<class FeatureType> TSRefArray<FeatureType> GetModularFeaturesOfType();` (scope `uLang`) — Queries for a specific modular feature. Returns an empty array if the feature is not available. Does not assert. @return An array of all registered features of a single type -- sorted in priority order.

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/ModularFeatureManager.inl` (Public)


#### class `uLang::Private::IModularFeatureRegistry`  
`class IModularFeatureRegistry : public CSharedMix`  
_L21-26_
- inherits: `CSharedMix`
- L25 _private function_ `IModularFeatureRegistry()`

#### class `uLang::Private::CModularFeatureRegistrar`  
`class CModularFeatureRegistrar`  
_L29-41_
- desc: Private base class for sharing registration functionality only with our templatized RAII handles.
- L34 _public prototype_ `static const TSRef<IModularFeatureRegistry>& GetRegistry();`
- L35 _public prototype_ `static void SetRegistry(const TSRef<IModularFeatureRegistry>& NewRegistry);`
- L37 _public prototype_ `static void Register(const TSRef<IModularFeature>& NewFeature, const RegistryId FeatureId);`
- L38 _public prototype_ `static bool Unregister(const TSRef<IModularFeature>& Feature);`
- L40 _public prototype_ `static RegistryId GetRegistryId(const char* FeatureName);`

#### struct `uLang::Private::VoidType`  
`template<typename T> struct VoidType`  
_L47-50_
- desc: SFINAE utility helpers for catching mis-implemented ModularFeature classes.
- L49 _public typedef_ `using Type = void;`

#### struct `uLang::Private::TFeatureHasUid`  
`template<typename FeatureType, typename = void> struct TFeatureHasUid`  
_L52-55_
- L59 _public typedef_ `using CFeatureType = typename FeatureType::CFeatureType;`

#### enum `uLang::Private::TFeatureHasUid::(anonymous)`  
`enum`  
_L54-54_

#### struct `uLang::Private::TFeatureHasUid`  
`template<typename FeatureType> struct TFeatureHasUid<FeatureType, typename VoidType<typename FeatureType::CFeatureType>::Type>`  
_L57-61_
- L59 _public typedef_ `using CFeatureType = typename FeatureType::CFeatureType;`

#### enum `uLang::Private::TFeatureHasUid::(anonymous)`  
`enum`  
_L60-60_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uLang`
- L17 _namespace_ `namespace Private` (scope `uLang`)
- L19 _typedef_ `using RegistryId = SymbolId;` (scope `uLang::Private`)
- L54 _enumerator_ `enum { Value = false };` (scope `uLang::Private::TFeatureHasUid::__anon68ed02480103`)
- L60 _enumerator_ `enum { Value = true };` (scope `uLang::Private::TFeatureHasUid::__anon68ed02480203`)
- L64 _function_ `template<class FeatureType> RegistryId GetUidForFeature()` (scope `uLang::Private`)
- L73 _function_ `template<class FeatureType> template<typename... Args_t> TModularFeatureRegHandle<FeatureType>::TModularFeatureRegHandle(Args_t&&... Args) : _ModularFeatureRef(TSRef<FeatureType>::New(uLang::ForwardArg<Args_t>(Args)...))` (scope `uLang::TModularFeatureRegHandle`)
- L80 _function_ `template<class FeatureType> uLang::TModularFeatureRegHandle<FeatureType>::~TModularFeatureRegHandle()` (scope `uLang::uLang::TModularFeatureRegHandle`)
- L88 _namespace_ `namespace Private` (scope `uLang`)
- L90 _prototype_ `int32_t GetModularFeatureCount(const RegistryId FeatureId);` (scope `uLang::Private`)
- L91 _prototype_ `TSPtr<IModularFeature> GetModularFeature(const RegistryId FeatureId, const int32_t Index);` (scope `uLang::Private`)
- L94 _function_ `template<class FeatureType> RegistryId GetUidForFeatureQuery()` (scope `uLang::Private`)
- L104 _function_ `template<class FeatureType> int32_t GetModularFeatureCount()` (scope `uLang`)
- L110 _function_ `template<class FeatureType> TOptional< TSRef<FeatureType> > GetModularFeature(const int32_t Index)` (scope `uLang`)
- L125 _function_ `template<class FeatureType> TSRefArray<FeatureType> GetModularFeaturesOfType()` (scope `uLang`)
- L139 _function_ `template<class FeatureType> TModularFeatureIterator<FeatureType>::operator bool() const` (scope `uLang::TModularFeatureIterator`)
- L145 _function_ `template<class FeatureType> bool TModularFeatureIterator<FeatureType>::operator!() const` (scope `uLang::TModularFeatureIterator`)
- L151 _function_ `template<class FeatureType> TSRef<FeatureType> TModularFeatureIterator<FeatureType>::Get() const` (scope `uLang::TModularFeatureIterator`)
- L160 _function_ `template<class FeatureType> FeatureType& TModularFeatureIterator<FeatureType>::operator*() const` (scope `uLang::TModularFeatureIterator`)
- L166 _function_ `template<class FeatureType> FeatureType* TModularFeatureIterator<FeatureType>::operator->() const` (scope `uLang::TModularFeatureIterator`)
- L172 _function_ `template<class FeatureType> void TModularFeatureIterator<FeatureType>::operator++()` (scope `uLang::TModularFeatureIterator`)

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/ProgramBuildManager.h` (Public)


#### struct `uLang::SToolchainOverrides`  
`struct SToolchainOverrides`  
_L18-35_
- L20 _public member_ `TOptional<TSPtr<IParserPass>> Parser;`
- L21 _public member_ `TOptional<TSRefArray<IPostVstFilter>> PostVstFilters;`
- L22 _public member_ `TOptional<TSPtr<ISemanticAnalyzerPass>> SemanticAnalyzer;`
- L23 _public member_ `TOptional<TSRefArray<IPostSemanticAnalysisFilter>> PostSemanticAnalysisFilters;`
- L24 _public member_ `TOptional<TSRefArray<IPostIrFilter>> PostIrFilters;`
- L25 _public member_ `TOptional<TSPtr<IAssemblerPass>> Assembler;`
- L27 _public member_ `TOptional<TSRefArray<IPreParseInjection>> PreParseInjections;`
- L28 _public member_ `TOptional<TSRefArray<IPostParseInjection>> PostParseInjections;`
- L29 _public member_ `TOptional<TSRefArray<IPreSemAnalysisInjection>> PreSemAnalysisInjections;`
- L30 _public member_ `TOptional<TSRefArray<IIntraSemAnalysisInjection>> IntraSemAnalysisInjections;`
- L31 _public member_ `TOptional<TSRefArray<IPostSemAnalysisInjection>> PostSemAnalysisInjections;`
- L32 _public member_ `TOptional<TSRefArray<IPreTranslateInjection>> PreTranslateInjections;`
- L33 _public member_ `TOptional<TSRefArray<IPreLinkInjection>> PreLinkInjections;`
- L34 _public member_ `TOptional<TSRefArray<IPostLinkInjection>> PostLinkInjections;`

#### struct `uLang::SBuildManagerParams`  
`struct SBuildManagerParams`  
_L37-46_
- L42 _public member_ `SToolchainOverrides _ToolchainOverrides;` — For the pieces of this that are set, the toolchain will be constructed using those specified parts -- for the other toolchain pieces, the build-manager will perform auto-discovery to fill the rest out.
- L45 _public member_ `TSPtr<CSemanticProgram> _ExistingProgram;` — SToolchainParams _ToolchainParams;

#### class `uLang::CProgramBuildManager`  
`class CProgramBuildManager : public CSharedMix`  
_L48-94_
- inherits: `CSharedMix`
- L51 _public prototype_ `CProgramBuildManager(const SBuildManagerParams& Params);`
- L52 _public prototype_ `~CProgramBuildManager();`
- L54 _public prototype_ `void SetSourceProject(const TSRef<CSourceProject>& Project);`
- L55 _public prototype_ `void AddSourceSnippet(const TSRef<ISourceSnippet>& Snippet, const CUTF8StringView& PackageName, const CUTF8StringView& PackageVersePath);`
- L56 _public prototype_ `void RemoveSourceSnippet(const TSRef<ISourceSnippet>& Snippet);`
- L57 _public prototype_ `const CSourceProject::SPackage& FindOrAddSourcePackage(const CUTF8StringView& PackageName, const CUTF8StringView& PackageVersePath);`
- L59 _public prototype_ `SBuildResults Build(const SBuildParams& Params, TSRef<CDiagnostics> Diagnostics);`
- L61 _public function_ `const TSRef<CToolchain>& GetToolchain() const`
- L62 _public function_ `const SProgramContext& GetProgramContext() const`
- L63 _public function_ `const TSRef<CSourceProject>& GetSourceProject() const`
- L64 _public function_ `const TUPtr<SPackageUsage>& GetPackageUsage() const`
- L65 _public function_ `TArray<FSolLocalizationInfo> TakeLocalizationInfo()`
- L66 _public function_ `TArray<FSolLocalizationInfo> TakeStringInfo()`
- L67 _public function_ `void SetPathToSource(uLang::TMap<uLang::CUTF8String, uLang::CUTF8String>* PathToSource)`
- L69 _public prototype_ `SBuildResults BuildProject(const CSourceProject& SourceProject, const SBuildContext& BuildContext);`
- L70 _public prototype_ `ECompilerResult ParseSnippet(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& OutVst, const CUTF8String& TextSnippet, const SBuildContext& BuildContext);`
- L71 _public prototype_ `ECompilerResult SemanticAnalyzeVst(TOptional<TSRef<CSemanticProgram>>& OutProgram, const Verse::Vst::TNodeRef<Verse::Vst::Project>& Vst, const SBuildContext& BuildContext);`
- L72 _public prototype_ `ECompilerResult IrGenerateProgram(const TSRef<CSemanticProgram>& Program, const SBuildContext& BuildContext);`
- L73 _public prototype_ `ECompilerResult AssembleProgram(const TSRef<CSemanticProgram>& Program, const SBuildContext& BuildContext);`
- L74 _public prototype_ `ELinkerResult Link(const SBuildContext& BuildContext);`
- L76 _public prototype_ `void ResetSemanticProgram();`
- L77 _public function_ `const Verse::Vst::TNodePtr<Verse::Vst::Project>& GetProjectVst() const`
- L78 _public function_ `void SetProjectVst(const Verse::Vst::TNodeRef<Verse::Vst::Project>& NewProject)`
- L83 _public prototype_ `void EnablePackageUsage(bool bEnable = true);`
- L86 _private prototype_ `void OnBuildDiagnostic(const TSRef<SGlitch>& Diagnostic);`
- L87 _private prototype_ `void OnBuildStatistic(const SBuildEventInfo& EventInfo);`
- L89 _private member_ `TSRef<CToolchain> _Toolchain;`
- L90 _private member_ `SProgramContext _ProgramContext;`
- L91 _private member_ `TSRef<CSourceProject> _SourceProject;`
- L92 _private member_ `TUPtr<SPackageUsage> _PackageUsage;`
- L93 _private member_ `bool bEnablePackageUsage = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API VERSECOMPILER_API`
- L13 _namespace_ `namespace uLang`

### `Source/Runtime/VerseCompiler/Public/uLang/Toolchain/Toolchain.h` (Public)


#### struct `uLang::SToolchainParams`  
`struct SToolchainParams`  
_L30-90_
- L38 _public member_ `TOptional<TSRef<IParserPass>> Parser;` — --- Parser -------------------------------- The parser is responsible for ingesting a source file, parsing and tokenizing it, and generating an abstract syntax tree (Vst) for the rest of the compiler to consume.  It should not need to worry about semantics, just syntax
- L48 _public member_ `TSRefArray<IPostVstFilter> PostVstFilters;` — --- Post Vst Filters ---------------------- The post Vst filters take an Vst, and transform it in any way it deems fit.  Applications of this stage can include optimizers (operation reduction, constant folding, etc.), or metadata stripping or remapping.  There can be as many filters as needed, and are called in array order, starting at 0.  It is the loader's responsibility for establishing that order.
- L56 _public member_ `TOptional<TSRef<ISemanticAnalyzerPass>> SemanticAnalyzer;` — --- Semantic Analyzer ------------------ The semantic analyzer consumes the generated and optimized VST, transforms it to an AST, and semantically analyzes the AST, annotating the AST with inferred types and other analysis products.
- L63 _public member_ `TSRefArray<IPostSemanticAnalysisFilter> PostSemanticAnalysisFilters;` — --- Post Semantic Analysis Filters --------------- This stage takes the semantically analyzed AST, and performs operations on the result before passing along to the IR generator.
- L70 _public member_ `TSRefArray<IPostIrFilter> PostIrFilters;` — --- Post IR generation Filters --------------- This stage takes the generated IR, and performs operations on the result before passing along to the assembler.
- L76 _public member_ `TOptional<TSRef<IIrGeneratorPass>> IrGenerator;` — --- IR (Intermediate Representation) ------- The IrGenerator creates an intermediate representation intended for lenient analysis and code generation.
- L84 _public member_ `TOptional<TSRef<IAssemblerPass>> Assembler;` — --- Assembler ----------------------------- The assembler is responsible both for code-gen and linking (resolving any symbols between language objects). Note that there may be runtime bindings that can't be resolved at this stage, but all uLang internal bindings should be validated and linked here.
- L89 _public member_ `SToolchainInjections LayerInjections;` — --- API Layer Injections ---------------

#### enum `uLang::ECompilerResult`  
`enum class ECompilerResult : uint32_t`  
_L94-116_
- L96 _public enumerator_ `Compile_NoOp = (0x00)`
- L98 _public enumerator_ `Compile_RanSyntaxPass = (1<<0)`
- L99 _public enumerator_ `Compile_RanSemanticPass = (1<<1)`
- L100 _public enumerator_ `Compile_RanLocalizationPass = (1<<2)`
- L101 _public enumerator_ `Compile_RanIrPass = (1<<3)`
- L102 _public enumerator_ `Compile_RanCodeGenPass = (1<<4)`
- L104 _public enumerator_ `Compile_SkippedByInjection = (1<<5)`
- L105 _public enumerator_ `Compile_SkippedByEmptyPass = (1<<6)`
- L107 _public enumerator_ `Compile_SyntaxError = (1<<7)`
- L108 _public enumerator_ `Compile_SemanticError = (1<<8)`
- L109 _public enumerator_ `Compile_IrError = (1<<9)`
- L110 _public enumerator_ `Compile_LocalizationError = (1<<10)`
- L111 _public enumerator_ `Compile_CodeGenError = (1<<11)`
- L113 _public enumerator_ `CompileMask_Failure = (Compile_SyntaxError | Compile_SemanticError | Compile_IrError | Compile_LocalizationError | Compile_CodeGenError)`
- L114 _public enumerator_ `CompileMask_Skipped = (Compile_SkippedByInjection | Compile_SkippedByEmptyPass)`
- L115 _public enumerator_ `CompileMask_Aborted = (CompileMask_Failure | CompileMask_Skipped)`

#### struct `uLang::SBuildResults`  
`struct SBuildResults`  
_L124-134_
- L126 _public prototype_ `bool HasFailure() const;`
- L127 _public prototype_ `SBuildResults& operator |= (const SBuildResults& Other);`
- L129 _public member_ `SBuildStatistics _Statistics = {};`
- L131 _public member_ `bool _IOErrorsFound = false;`
- L132 _public member_ `ECompilerResult _CompilerResult = ECompilerResult::Compile_NoOp;`
- L133 _public member_ `ELinkerResult _LinkerResult = ELinkerResult::Link_Skipped;`

#### class `uLang::CToolchain`  
`class CToolchain : public CSharedMix`  
_L149-281_
- inherits: `CSharedMix`
- desc: The compiler toolchain, which has five stages of compilation.  It's structured as a layered, multi-stage compiler API.  Each stage is interchangeable, which means the frontend and the backend are retargetable. This class needs to be assembled by the Toolchain Loader, which uses the Modular Features to find a module or modules that implement the five stages of the compiler.  This also lets the user mix in various optimizing passes (post-Vst filters), or bytecode packing (post-expression filters) from any source.
- L155 _public prototype_ `SBuildResults BuildProject(const CSourceProject& SourceProject, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Compile and link all text snippets in the given project
- L165 _public prototype_ `ECompilerResult ParseSnippet(const Verse::Vst::TNodeRef<Verse::Vst::Snippet>& OutVst, const CUTF8String& TextSnippet, const SBuildContext& BuildContext, const uint32_t VerseVersion = Verse::Version::Default, const uint32_t UploadedAtFNVersion = VerseFN::UploadedAtFNVersion::Latest);` — Parse a snippet of text and return the resulting Vst snippet Steps: 1. Pre parse injections (from both toolchain and build context) 2. Parse 3. Post Vst filters 4. Post parse injections (from both toolchain and build context)
- L174 _public prototype_ `ECompilerResult CompileVst(const Verse::Vst::TNodeRef<Verse::Vst::Project>& Vst, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Run SemanticAnalyzeVst and AssembleProgram on an Vst.
- L184 _public prototype_ `ECompilerResult SemanticAnalyzeVst(TOptional<TSRef<CSemanticProgram>>& OutProgram, const Verse::Vst::TNodeRef<Verse::Vst::Project>& Vst, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Run semantic analysis on a given Vst snippet Steps: 1. Pre semantic analysis injections (from both toolchain and build context) 2. Semantic analysis 3. Post expression filters 4. Post semantic analysis injections (from both toolchain and build context)
- L189 _public prototype_ `ECompilerResult ExtractLocalization(const TSRef<CSemanticProgram>& Program, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Extract localization information.
- L197 _public prototype_ `ECompilerResult IrGenerateProgram(const TSRef<CSemanticProgram>& Program, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Run IR generation on a given Ast snippet. Steps: 1. IR generation 2. (future lenient analysis)
- L205 _public prototype_ `ECompilerResult AssembleProgram(const TSRef<CSemanticProgram>& Program, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Run semantic analysis and code generation on a given Vst snippet Steps: 1. Pre translate injections 2. Assembler (code generation)
- L210 _public prototype_ `ELinkerResult Link(const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Run linker (not currently used)
- L217 _public function_ `const TOptional<TSRef<IParserPass>>& GetParser() const` — Accessors for the various stages of the compiler.  Most users will never actually need to grab these stages individual, but in the cases where you need to do partial compilation, they can be useful to manually run
- L218 _public function_ `const TSRefArray<IPostVstFilter>& GetPostVstFilters() const`
- L219 _public function_ `const TOptional<TSRef<ISemanticAnalyzerPass>>& GetSemanticAnalyzer() const`
- L220 _public function_ `const TSRefArray<IPostSemanticAnalysisFilter>& GetPostSemanticAnalysisFilters() const`
- L221 _public function_ `const TSRefArray<IPostIrFilter>& GetPostIrFilters() const`
- L222 _public function_ `const TOptional<TSRef<IAssemblerPass>>& GetAssembler() const`
- L223 _public function_ `const Verse::Vst::TNodePtr<Verse::Vst::Project>& GetProjectVst() const`
- L235 _public function_ `void SetProjectVst(const Verse::Vst::TNodeRef<Verse::Vst::Project>& NewProject)` — Directly sets the cached VST project to the new project specified. Warning: doing this will cause the previously cached VST project's destructor to be called, which means that any AST nodes that still hold references to the VST nodes within will now have those references be invalidated. The only time you should use this is if you don't care about the previous VST project anymore and its accompanying AST either. @param NewProject    The new project to store.
- L241 _public prototype_ `TArray<FSolLocalizationInfo> TakeLocalizationInfo();` — Take localization information, i.e, it removes it from this object.
- L244 _public prototype_ `TArray<FSolLocalizationInfo> TakeStringInfo();` — Take string information, i.e, it removes it from this object.
- L250 _public prototype_ `void SetPathToSource(uLang::TMap<uLang::CUTF8String, uLang::CUTF8String>* PathToSource);` — Add a storage for modified source code, e.g., auto qualified code. If set then the modified source will be added to the map, keyed by path. No need to set unless the modified source is needed after compiling, e.g., by the assert_roundtrip macro in VerseTestScriptCmd.
- L255 _private prototype_ `CToolchain(const SToolchainParams& Params);` — use CreateToolchain() to construct
- L258 _private prototype_ `void FillInVst(Verse::Vst::Project* VstProject, SBuildResults& BuildResults, const CSourceProject& SourceProject, const SBuildContext& BuildContext, const SProgramContext& ProgramContext);` — Extend VstProject with the vst created from SourceProject.
- L268 _private prototype_ `bool BuildOrderedPackageList(const CSourceProject& SourceProject, const SBuildContext& BuildContext, TArray<SOrderedPackage>& OutOrderedPackageList) const;` — Build a list of packages ordered by dependency depth Returns true if successful, or false if glitches were encountered
- L270 _private member_ `SToolchainParams _Params;`
- L272 _private member_ `Verse::Vst::TNodePtr<Verse::Vst::Project> _ProjectVst;`
- L275 _private member_ `TArray<FSolLocalizationInfo> _LocalizationInfo;` — Localization and string information stored here, see SetPathToSource for usage.
- L276 _private member_ `TArray<FSolLocalizationInfo> _StringInfo;`
- L280 _private member_ `uLang::TMap<uLang::CUTF8String, uLang::CUTF8String>* _PathToSource{ nullptr };` — Storage for modified source, keyed by path. The source stored here takes precedence over the one in SourceSnippet.

#### struct `uLang::CToolchain::SOrderedPackage`  
`struct SOrderedPackage`  
_L260-264_
- L262 _public member_ `const CSourcePackage* _Package = nullptr;`
- L263 _public member_ `int32_t _DependencyDepth = -1;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API VERSECOMPILER_API`
- L23 _namespace_ `namespace uLang`
- L92 _prototype_ `TSRef<CToolchain> CreateToolchain(const SToolchainParams& Params);` (scope `uLang`)
- L117 _prototype_ `ULANG_ENUM_BIT_FLAGS(ECompilerResult, inline);` (scope `uLang`)
- L119 _function_ `inline bool IsCompileFailure(ECompilerResult E)` (scope `uLang`)
- L120 _function_ `inline bool IsAbortedCompile(ECompilerResult E)` (scope `uLang`)
- L121 _function_ `inline bool IsCompileIncomplete(ECompilerResult E)` (scope `uLang`)
- L122 _function_ `inline bool IsCompileComplete(ECompilerResult E)` (scope `uLang`)

### `Source/Runtime/VerseCompiler/Public/uLang/VerseLocalizationGen.h` (Public)


#### struct `uLang::FSolLocalizationInfo`  
`struct FSolLocalizationInfo`  
_L10-28_
- L12 _public function_ `FSolLocalizationInfo(const CUTF8String& Path, const CUTF8String& Default, const CUTF8String& Where) : Path(Path) , Default(Default) , Where(Where)`
- L19 _public function_ `FSolLocalizationInfo(const CUTF8String& Default, const CUTF8String& Where) : Path("") , Default(Default) , Where(Where)`
- L25 _public member_ `CUTF8String Path;`
- L26 _public member_ `CUTF8String Default;`
- L27 _public member_ `CUTF8String Where;`

#### struct `uLang::FVerseLocalizationGen`  
`struct FVerseLocalizationGen`  
_L30-36_
- L32 _public prototype_ `void operator()(const uLang::CSemanticProgram& Program, uLang::CDiagnostics& Diagnostics, TArray<FSolLocalizationInfo>& LocalizationInfo, TArray<FSolLocalizationInfo>& StringInfo) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uLang`
