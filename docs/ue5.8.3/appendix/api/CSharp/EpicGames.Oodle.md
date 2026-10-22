# CSharp / EpicGames.Oodle

- project root: `Source/Programs/Shared/EpicGames.Oodle`
- files: 1; symbols: 66
- symbol kinds: class=3, ctor=1, enum=6, enumerator=38, field=8, method=10
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Oodle/Oodle.cs` (EpicGames.Oodle)


#### enum `EpicGames.Compression.OodleCompressorType`  
`public enum OodleCompressorType : int`  
_public; L12-43_
- inherits: `int`
- desc: Compressor type to use
- L17 _public* enumerator_ `None = 3` — None = memcpy, pass through uncompressed bytes
- L22 _public* enumerator_ `Kraken = 8` — Fast decompression and high compression ratios, amazing!
- L27 _public* enumerator_ `Leviathan = 13` — Leviathan = Kraken's big brother with higher compression, slightly slower decompression.
- L32 _public* enumerator_ `Mermaid = 9` — Mermaid is between Kraken and Selkie - crazy fast, still decent compression.
- L37 _public* enumerator_ `Selkie = 11` — Selkie is a super-fast relative of Mermaid. For maximum decode speed.
- L42 _public* enumerator_ `Hydra = 12` — Hydra, the many-headed beast = Leviathan, Kraken, Mermaid, or Selkie (see $OodleLZ_About_Hydra)

#### enum `EpicGames.Compression.OodleCompressionLevel`  
`public enum OodleCompressionLevel : int`  
_public; L49-144_
- inherits: `int`
- desc: Compression level
- L54 _public* enumerator_ `None = 0` — Don't compress, just copy raw bytes
- L59 _public* enumerator_ `SuperFast = 1` — Super fast mode, lower compression ratio
- L64 _public* enumerator_ `VeryFast = 2` — Fastest LZ mode with still decent compression ratio
- L69 _public* enumerator_ `Fast = 3` — Fast - good for daily use
- L74 _public* enumerator_ `Normal = 4` — Standard medium speed LZ mode
- L79 _public* enumerator_ `Optimal1 = 5` — Optimal parse level 1 (faster optimal encoder)
- L84 _public* enumerator_ `Optimal2 = 6` — Optimal parse level 2 (recommended baseline optimal encoder)
- L89 _public* enumerator_ `Optimal3 = 7` — Optimal parse level 3 (slower optimal encoder)
- L94 _public* enumerator_ `Optimal4 = 8` — Optimal parse level 4 (very slow optimal encoder)
- L99 _public* enumerator_ `Optimal5 = 9` — Optimal parse level 5 (don't care about encode speed, maximum compression)
- L104 _public* enumerator_ `HyperFast1 = -1` — Faster than SuperFast, less compression
- L109 _public* enumerator_ `HyperFast2 = -2` — Faster than HyperFast1, less compression
- L114 _public* enumerator_ `HyperFast3 = -3` — Faster than HyperFast2, less compression
- L119 _public* enumerator_ `HyperFast4 = -4` — Fastest, less compression
- L126 _public* enumerator_ `HyperFast = HyperFast1` — Alias hyperfast base level
- L131 _public* enumerator_ `Optimal = Optimal2` — Alias optimal standard level
- L136 _public* enumerator_ `Max = Optimal5` — Maximum compression level
- L141 _public* enumerator_ `Min = HyperFast4` — fastest compression level

#### class `EpicGames.Compression.OodleException`  
`public sealed class OodleException(string message) : Exception(message)`  
_public; L149-151_
- desc: Base class for oodle exceptions

#### class `EpicGames.Compression.Oodle`  
`public sealed partial class Oodle`  
_public; L156-293_
- desc: Wraps an instance of the Oodle compressor
- L208 _private method_ `private static unsafe partial long OodleLZ_Compress(OodleCompressorType compressor, byte* rawBuf, long rawLen, byte* compBuf, OodleCompressionLevel level, long pOptions, byte[]? dictionaryBase, byte[]? lrm, byte* scratchMem, long scratchSize)` — attrs: `[LibraryImport("oo2core")]`
- L211 _private method_ `private static partial long OodleLZ_GetCompressedBufferSizeNeeded(OodleCompressorType compressor, long rawSize)` — attrs: `[LibraryImport("oo2core")]`
- L214 _private method_ `private static partial int OodleLZDecoder_MemorySizeNeeded(OodleCompressorType compressor, long rawLen = -1)` — attrs: `[LibraryImport("oo2core")]`
- L217 _private method_ `private static extern int OodleLZ_GetCompressScratchMemBound(OodleCompressorType compressor, OodleCompressionLevel level, int rawLen, OodleConfigValues configValues)` — attrs: `[DllImport("oo2core")]`
- L220 _private method_ `private static unsafe partial long OodleLZ_Decompress(byte* compBuf, long compBufSize, byte* rawBuf, long rawLen, OodleLZ_FuzzSafe fuzzSafe = OodleLZ_FuzzSafe.OodleLZ_FuzzSafe_Yes, OodleLZ_CheckCRC checkCRC = OodleLZ_CheckCRC.OodleLZ_CheckCRC_No, OodleLZ_Verbosity verbosity = OodleLZ_Verbosity.OodleLZ_Verbosity_None, byte* decBufBase = null, long decBufSize = 0, long fpCallback = 0, long callbackUserData = 0, byte* decoderMemory = null, long decoderMemorySize = 0, OodleLZ_Decode_ThreadPhase threadPhase = OodleLZ_Decode_ThreadPhase.OodleLZ_Decode_Unthreaded)` — attrs: `[LibraryImport("oo2core")]`
- L223 _private method_ `private static extern void Oodle_GetConfigValues(OodleConfigValues configValues)` — attrs: `[DllImport("oo2core")]`
- L226 _private method_ `private static extern void Oodle_SetConfigValues(OodleConfigValues configValues)` — attrs: `[DllImport("oo2core")]`
- L228 _private field_ `private static readonly OodleConfigValues s_configValues = new()`
- L233-238 _private* ctor_ `static Oodle()` — Static constructor. Sets the backwards compatibility version for Oodle.
- L248-260 _public method_ `public static unsafe int Compress(OodleCompressorType compressor, ReadOnlySpan<byte> inputData, Span<byte> outputData, OodleCompressionLevel compressionLevel = OodleCompressionLevel.Normal)` — Compress a block of data
- L268-272 _public method_ `public static int MaximumOutputSize(OodleCompressorType compressor, int uncompressedLength)` — Determines the max size of the compressed buffer
- L280-292 _public method_ `public static unsafe int Decompress(ReadOnlySpan<byte> inputData, Span<byte> outputData)` — Decompresses a block of data

#### enum `EpicGames.Compression.Oodle.OodleLZ_Decode_ThreadPhase`  
`enum OodleLZ_Decode_ThreadPhase`  
_private*; L159-165_
- L161 _public* enumerator_ `OodleLZ_Decode_ThreadPhase1 = 1`
- L162 _public* enumerator_ `OodleLZ_Decode_ThreadPhase2 = 2`
- L163 _public* enumerator_ `OodleLZ_Decode_ThreadPhaseAll = 3`
- L164 _public* enumerator_ `OodleLZ_Decode_Unthreaded = OodleLZ_Decode_ThreadPhaseAll`

#### enum `EpicGames.Compression.Oodle.OodleLZ_FuzzSafe`  
`enum OodleLZ_FuzzSafe`  
_private*; L167-171_
- L169 _public* enumerator_ `OodleLZ_FuzzSafe_No = 0`
- L170 _public* enumerator_ `OodleLZ_FuzzSafe_Yes = 1`

#### enum `EpicGames.Compression.Oodle.OodleLZ_CheckCRC`  
`enum OodleLZ_CheckCRC`  
_private*; L173-178_
- L175 _public* enumerator_ `OodleLZ_CheckCRC_No = 0`
- L176 _public* enumerator_ `OodleLZ_CheckCRC_Yes = 1`
- L177 _public* enumerator_ `OodleLZ_CheckCRC_Force32 = 0x40000000`

#### enum `EpicGames.Compression.Oodle.OodleLZ_Verbosity`  
`enum OodleLZ_Verbosity`  
_private*; L180-187_
- L182 _public* enumerator_ `OodleLZ_Verbosity_None = 0`
- L183 _public* enumerator_ `OodleLZ_Verbosity_Minimal = 1`
- L184 _public* enumerator_ `OodleLZ_Verbosity_Some = 2`
- L185 _public* enumerator_ `OodleLZ_Verbosity_Lots = 3`
- L186 _public* enumerator_ `OodleLZ_Verbosity_Force32 = 0x40000000`

#### class `EpicGames.Compression.Oodle.OodleConfigValues`  
`class OodleConfigValues`  
_private*; L193-204_
- attrs: `[StructLayout(LayoutKind.Sequential)]`
- L195 _public field_ `public int m_OodleLZ_LW_LRM_step`
- L196 _public field_ `public int m_OodleLZ_LW_LRM_hashLength`
- L197 _public field_ `public int m_OodleLZ_LW_LRM_jumpbits`
- L199 _public field_ `public int m_OodleLZ_Decoder_Max_Stack_Size`
- L200 _public field_ `public int m_OodleLZ_Small_Buffer_LZ_Fallback_Size_Unused`
- L201 _public field_ `public int m_OodleLZ_BackwardsCompatible_MajorVersion`
- L203 _public field_ `public int m_oodle_header_version`
